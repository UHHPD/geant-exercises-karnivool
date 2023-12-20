////////////////////////////////////////////////////////////////////////////////
//
// TutorialStack
// -------------
//
// Hartmut Stadie
////////////////////////////////////////////////////////////////////////////////

#include "TutorialStack.hh"

#include "TError.h"
#include "TFolder.h"
#include "TROOT.h"

#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// ROOT ClassImp macro
////////////////////////////////////////////////////////////////////////////////

ClassImp(TutorialStack)

    ////////////////////////////////////////////////////////////////////////////////
    // construction / destruction
    ////////////////////////////////////////////////////////////////////////////////

    //______________________________________________________________________________
    TutorialStack::TutorialStack()
    : fCurrentId(-1), fNPrimary(0) {
  fParticles = new TClonesArray("TParticle", 200);
  TFolder* top = (TFolder*)gROOT->FindObjectAny("Geant4");
  top->Add(fParticles);
}

//______________________________________________________________________________
TutorialStack::~TutorialStack() { delete fParticles; }

////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void TutorialStack::PushTrack(Int_t toBeDone, Int_t parent, Int_t pdg,
                              Double_t px, Double_t py, Double_t pz, Double_t e,
                              Double_t vx, Double_t vy, Double_t vz,
                              Double_t tof, Double_t polx, Double_t poly,
                              Double_t polz, TMCProcess mech, Int_t& ntr,
                              Double_t weight, Int_t is) {
  // std::cout <<"adding track " << parent << " " << pdg << std::endl;
  ntr = GetNtrack();

  TParticle* particle = new (fParticles->operator[](ntr))
      TParticle(pdg, is, parent, -1, -1, -1, px, py, pz, e, vx, vy, vz, tof);

  particle->SetPolarisation(polx, poly, polz);
  particle->SetWeight(weight);
  particle->SetUniqueID(mech);

  if (parent >= 0) {
    TVirtualGeoTrack* p = gGeoManager->GetTrackOfId(parent);
    p->AddDaughter(ntr, pdg, particle);

    TParticle* mother = (TParticle*)p->GetParticle();

    if (mother->GetFirstDaughter() != -1)
      mother->SetFirstDaughter(ntr);
    else
      mother->SetLastDaughter(ntr);
  } else {
    ++fNPrimary;
  }

  gGeoManager->AddTrack(ntr, pdg, particle);

  TVirtualGeoTrack* t = gGeoManager->GetTrackOfId(ntr);
  t->SetName(particle->GetName());

  if (toBeDone) fStack.push(ntr);
}

//______________________________________________________________________________
TParticle* TutorialStack::PopNextTrack(Int_t& itrack) {
  // std::cout << "TutorialStack::PopNextTrack" << std::endl;
  if (fStack.empty()) {
    fCurrentId = -1;
    itrack = -1;
    return NULL;
  }
  itrack = fStack.top();
  fStack.pop();
  fCurrentId = itrack;
  return GetParticle(fCurrentId);
}

//______________________________________________________________________________
void TutorialStack::Clear(const Option_t* /* option */) {
  fCurrentId = -1;
  gGeoManager->ClearTracks();
  fParticles->Delete();
  fNPrimary = 0;
}
