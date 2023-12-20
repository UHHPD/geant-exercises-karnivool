////////////////////////////////////////////////////////////////////////////////
//
// tutorial application using geant4_vmc via TVirutalMCApplication
// ---------------------------------------------------------------
//
// This is an adaption of the TGeantApplication class written by
// Hartmut Stadie, which is an adaption of the Ex01MCApplication class
// written by Ivana Hrivnacova.
//
//            11/03/2008 Philipp Schieferdecker <philipp.schieferdecker@cern.ch>
//
// added magnetic field, store energy deposited per detector node
//            07/14/2014 Hartmut Stadie <hartmut.stadie@desy.de>
////////////////////////////////////////////////////////////////////////////////

#ifndef TUTORIALAPPLICATION_H
#define TUTORIALAPPLICATION_H

#include "TDatabasePDG.h"
#include "TFolder.h"
#include "TGeoMCGeometry.h"
#include "TGeoManager.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"
#include "TVirtualMCGeometry.h"
#include "TVirtualMCStack.h"
#include "TVirtualPad.h"

#include <iostream>
#include <map>
#include <string>

class TVirtualGeoTrack;
class TGeoNode;

class TutorialApplication : public TVirtualMCApplication {
 public:
  //
  // construction / destruction
  //
  TutorialApplication(const char* name = "TutorialApplication",
                      const char* title = "MC using Geant4@KIT/UHH");
  virtual ~TutorialApplication();

 public:
  //
  // member functions
  //
  void InitMC(const char* setup = "geometry/g1");
  void RunMC(Int_t nofEvents = 1, bool draw = true);
  void FinishRun();

  // static access method
  static TutorialApplication* Instance();

  // construct materials & volumes
  void ConstructMaterials();
  void ConstructVolumes();

  // functions from TVirtualMCApplication
  virtual void ConstructGeometry();
  virtual void InitGeometry();
  virtual void GeneratePrimaries();
  virtual void BeginEvent();
  virtual void BeginPrimary() { ; }
  virtual void PreTrack();
  virtual void Stepping();
  virtual void PostTrack();
  virtual void FinishPrimary() { ; }
  virtual void FinishEvent();
  virtual void Field(const Double_t* x, Double_t* b) const;

  Double_t TrackingRmax() const { return std::numeric_limits<double>::max(); }
  Double_t TrackingZmax() const { return std::numeric_limits<double>::max(); }

  void SetPrimaryMomentum(Double_t p) {
    fPrimaryMomentum.SetXYZM(
        p, 0, 0, TDatabasePDG::Instance()->GetParticle(fPrimaryPDG)->Mass());
  }
  void SetPrimaryMomentum(TVector3 p) {
    fPrimaryMomentum.SetXYZM(
        p.X(), p.Y(), p.Z(),
        TDatabasePDG::Instance()->GetParticle(fPrimaryPDG)->Mass());
  }
  void SetPrimaryVertex(Double_t x, Double_t y, Double_t z) {
    fPrimaryVertex.SetXYZ(x, y, z);
  }
  void SetPrimaryPDG(Int_t pdg) {
    fPrimaryPDG = pdg;
    fPrimaryMomentum.SetXYZM(
        fPrimaryMomentum.X(), fPrimaryMomentum.Y(), fPrimaryMomentum.Z(),
        TDatabasePDG::Instance()->GetParticle(fPrimaryPDG)->Mass());
  }
  void SetPrimaryGeant(Int_t geant);
  void SetDrawPad(TVirtualPad* pad) { fPad = pad; }

  TVirtualPad* GetDrawPad() const { return fPad;}

  void DrawEvent();
  void Help();

  double depEinNode(const std::string& nodename) const {
    std::map<std::string, double>::const_iterator i =
        fDepEinNode.find(nodename);
    return i != fDepEinNode.end() ? i->second : 0;
  }
  // double depEinNode(Int_t nodeid) const {
  // std::map<Int_t,double>::const_iterator i =  fDepEinNode.find(nodeid);
  // return i != fDepEinNode.end() ? i->second : 0;}
  // double depE(TGeoNode* n) const { std::map<TGeoNode*,double>::const_iterator
  // i =  fDepEinVol.find(n); return i != fDepEinVol.end() ? i->second : 0;}
  const std::map<std::string, double>& depEMap() const { return fDepEinNode; }

  TLorentzVector finalPrimaryMomentum() const { return fFinalPrimaryMomentum;}
  //
  // member data
  //
 private:
  TVirtualMCStack* fStack;
  TFolder* fTopFolder;
  TFolder* fHistFolder;

  TLorentzVector fPrimaryMomentum;
  TLorentzVector fFinalPrimaryMomentum;
  TVector3 fPrimaryVertex;
  Int_t fPrimaryPDG;

  TVirtualGeoTrack* fCurrentTrack;  // !
  TString fGeoName;                 // !
  Bool_t fInit;                     // !
  TVirtualPad* fPad;                //!

  // histograms
  TH1F* hEdepLong;
  TH1F* hEdepTrans;
  TProfile* hPrimaryEnergy;

  std::map<std::string, double> fDepEinNode;

  ClassDef(TutorialApplication, 1);
};

//
// implementation of inline functions
//

//______________________________________________________________________________
inline TutorialApplication* TutorialApplication::Instance() {
  return (TutorialApplication*)(TVirtualMCApplication::Instance());
}

//______________________________________________________________________________
inline void TutorialApplication::BeginEvent() {
  fStack->Clear();
  fDepEinNode.clear();
}

//______________________________________________________________________________
inline void TutorialApplication::Field(const Double_t* x, Double_t* b) const {
  return gMC->GetMagField()->Field(x, b);
}

//______________________________________________________________________________
inline void TutorialApplication::PostTrack() { fCurrentTrack = NULL; }

//______________________________________________________________________________
inline void TutorialApplication::SetPrimaryGeant(Int_t geant) {
  fPrimaryPDG = TDatabasePDG::Instance()->ConvertGeant3ToPdg(geant);
}

#endif
