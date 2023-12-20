////////////////////////////////////////////////////////////////////////////////
//
// TutorialMainFrame
// -----------------
//
//                                                                Hartmut Stadie
////////////////////////////////////////////////////////////////////////////////

#include "TutorialMainFrame.hh"
#include "TutorialApplication.hh"

#include <TApplication.h>
#include <TCanvas.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGClient.h>
#include <TGComboBox.h>
#include <TGFrame.h>
#include <TGLabel.h>
#include <TGSlider.h>
#include <TGTextBuffer.h>
#include <TGTextEntry.h>
#include <TRootEmbeddedCanvas.h>
#include <TROOT.h>

#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
TutorialMainFrame::TutorialMainFrame(TutorialApplication* app) : TGMainFrame(gClient->GetRoot(), 250, 250), fApp(app) {
  SetCleanup(kDeepCleanup);

  TGGroupFrame* hframe =
      new TGGroupFrame(this, "Primary particle", kHorizontalFrame);
  {
    TGLabel* primlab = new TGLabel(hframe, "Type:");
    hframe->AddFrame(primlab, new TGLayoutHints(kLHintsLeft, 5, 5, 5, 5));

    TGComboBox* primcombo = new TGComboBox(hframe, 10);
    primcombo->AddEntry("e^{-}", 11);
    primcombo->AddEntry("e^{+}", -11);
    primcombo->AddEntry("#mu^{-}", 13);
    primcombo->AddEntry("#mu^{+}", -13);
    primcombo->AddEntry("#gamma", 22);
    primcombo->AddEntry("#pi^{+}", 211);
    primcombo->AddEntry("#pi^{0}", 111);
    primcombo->AddEntry("#pi^{-}", -211);
    primcombo->AddEntry("p", 2212);
    primcombo->AddEntry("#bar p", -2212);
    primcombo->AddEntry("n", 2112);
    primcombo->Select(-13);
    primcombo->Resize(100, 20);
    hframe->AddFrame(primcombo, new TGLayoutHints(kLHintsLeft, 0, 5, 5, 5));

    primcombo->Connect("Selected(Int_t)", "TutorialMainFrame", this,
                       "HandleType(int)");

    TGLabel* momlab = new TGLabel(hframe, "Momentum:");
    hframe->AddFrame(momlab, new TGLayoutHints(kLHintsLeft, 10, 5, 5, 5));

    fMomentumSlider = new TGHSlider(hframe, 200, kSlider1 | kScaleDownRight);
    fMomentumSlider->SetRange(0, 200);
    fMomentumSlider->SetPosition(10);
    fMomentumSlider->SetScale(10);
    hframe->AddFrame(
        fMomentumSlider,
        new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 0, 10, 5, 5));

    fMomentumText = new TGTextEntry(hframe, new TGTextBuffer(10));
    fMomentumText->Resize(50, 20);
    fMomentumText->SetAlignment(kTextRight);
    hframe->AddFrame(fMomentumText, new TGLayoutHints(kLHintsLeft, 0, 0, 5, 5));

    fMomentumSlider->Connect("PositionChanged(Int_t)", "TutorialMainFrame",
                             this, "HandleMomentumSlider(int)");
    fMomentumText->Connect("ReturnPressed()", "TutorialMainFrame", this,
                           "HandleMomentumText()");

    TGLabel* gevlab = new TGLabel(hframe, "GeV");
    hframe->AddFrame(gevlab, new TGLayoutHints(kLHintsLeft, 0, 5, 5, 5));
  }
  AddFrame(hframe, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX, 10,
                                            10, 10, 10));

  TGGroupFrame* hframe2 =
      new TGGroupFrame(this, "Detector view", kHorizontalFrame);

  fCanvas = new TRootEmbeddedCanvas("view", hframe2, 300, 300);
  hframe2->AddFrame(fCanvas, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX |
                                                   kLHintsExpandY,
                                               5, 5, 5, 5));

  AddFrame(hframe2, new TGLayoutHints(
                               kLHintsCenterX | kLHintsExpandX | kLHintsExpandY,
                               10, 10, 10, 10));

  TGHorizontalFrame* hframe3 = new TGHorizontalFrame(this, 300, 20);

  TGButton* run = new TGTextButton(hframe3, "Next Event");
  hframe3->AddFrame(run, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

  TGButton* exit = new TGTextButton(hframe3, "Quit");
  hframe3->AddFrame(exit, new TGLayoutHints(kLHintsRight, 5, 5, 3, 4));

  AddFrame(hframe3, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX,
                                             10, 10, 5, 5));

  run->Connect("Clicked()", "TutorialMainFrame", this, "HandleNextEvent()");
  exit->Connect("Clicked()", "TutorialMainFrame", this, "HandleExit()");
  Connect("CloseWindow()", "TutorialMainFrame", this, "HandleExit()");

  SetWindowName("Geant4 Tutorial GUI");
  MapSubwindows();
  Resize(GetDefaultSize());
  MapWindow();

  fCanvas->GetCanvas()->cd();
  fApp->SetDrawPad(fCanvas->GetCanvas());
  fMomentumSlider->SetPosition(80);
  HandleMomentumSlider(80);
}

//______________________________________________________________________________
TutorialMainFrame::~TutorialMainFrame() {}

////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void TutorialMainFrame::HandleMomentumSlider(int pos) {
  double p = pow(10, (pos / 40.0) - 2);

  char buffer[10];

  sprintf(buffer, "%2.2f", p);
  fMomentumText->SetText(buffer);
  fApp->SetPrimaryMomentum(p);
}

//______________________________________________________________________________
void TutorialMainFrame::HandleMomentumText() {
  std::istringstream s(fMomentumText->GetText());

  double p;
  s >> p;

  // if((p >= 0 ) && ( p < 20))
  fMomentumSlider->SetPosition((int)(40 * (2 + log(p) / log(10))));
  fApp->SetPrimaryMomentum(p);
}

//______________________________________________________________________________
void TutorialMainFrame::HandleType(int kf) { fApp->SetPrimaryPDG(kf); }

//______________________________________________________________________________
void TutorialMainFrame::HandleNextEvent() { fApp->RunMC(); }

//______________________________________________________________________________
void TutorialMainFrame::HandleExit() { gApplication->Terminate(); }
