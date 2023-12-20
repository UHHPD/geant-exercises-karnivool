////////////////////////////////////////////////////////////////////////////////
// Implementation of TVirtualMCStack for Geant4 VMC.
// -------------------------------------------------
//
// Tracks are added to TGeoManager and stack and storage
// operations are improved for speed. This is an adaption
// of the TGeantStack class written by Hartmut Stadie which
// is an adaption of the Ex01MCStack class written by
// Ivana Hrivnacova.
//
//                    11/02/2008 Philipp Schieferdecker <philipp.schieferdecker>
////////////////////////////////////////////////////////////////////////////////

#ifndef APPLICATIONSTACK_H
#define APPLICATIONSTACK_H

#include "TVirtualMCStack.h"

#include <TClonesArray.h>
#include <TGeoManager.h>
#include <TObjArray.h>
#include <TParticle.h>
#include <TVirtualGeoTrack.h>

#include <stack>

class TutorialStack : public TVirtualMCStack {
 public:
  //
  // construction/destruction
  //
  TutorialStack();
  virtual ~TutorialStack();

  //
  // member functions
  //
  void PushTrack(Int_t toBeDone, Int_t parent, Int_t pdg, Double_t px,
                 Double_t py, Double_t pz, Double_t e, Double_t vx, Double_t vy,
                 Double_t vz, Double_t tof, Double_t polx, Double_t poly,
                 Double_t polz, TMCProcess mech, Int_t& ntr, Double_t weight,
                 Int_t is);
  TParticle* PopNextTrack(Int_t& track);
  TParticle* PopPrimaryForTracking(Int_t i) {
    return GetParticle(fCurrentId = i);
  }

  void SetCurrentTrack(Int_t track) { fCurrentId = track; }

  Int_t GetNtrack() const { return fParticles->GetEntriesFast(); }
  Int_t GetNprimary() const { return fNPrimary; }
  TParticle* GetCurrentTrack() const { return GetParticle(fCurrentId); }
  Int_t GetCurrentTrackNumber() const { return fCurrentId; }
  Int_t GetCurrentParentTrackNumber() const {
    return GetParticle(fCurrentId)->GetFirstMother();
  }

  void Clear(const Option_t* option = "");

 private:
  TParticle* GetParticle(Int_t id) const {
    return (TParticle*)fParticles->At(id);
  }

  //
  // member data
  //
  TClonesArray* fParticles;
  std::stack<Int_t> fStack;  //!

  Int_t fCurrentId;
  Int_t fNPrimary;

  ClassDef(TutorialStack, 0)  // TutorialStack
};

#endif
