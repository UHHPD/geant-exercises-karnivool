
//#include "$G4PATH/geant4_vmc/examples/macro/basiclibs.C"
#include "TROOT.h"
//#include "TSystem.h"
//#include "include/TutorialApplication.hh"
//#include "include/TutorialMainFrame.hh"

void run_g4() {
  // Load basic libraries
  //gROOT->ProcessLine(".x $G4PATH/geant4_vmc/share/Geant4VMC-3.6.3/examples/macro/basiclibs.C");
  // Load Geant4 libraries
  //gROOT->ProcessLine(".x $G4PATH/geant4_vmc/share/Geant4VMC-3.6.3/examples/macro/g4libs.C");

  gROOT->ProcessLine(".x $G4PATH/geant4_vmc/examples/macro/basiclibs.C");
  gROOT->ProcessLine(".x $G4PATH/geant4_vmc/examples/macro/g4libs.C");


  // Load the tutorial application library
  // gSystem->Load("libTutorialApplication");
  gSystem->SetIncludePath("-I/usr/include -I$G4PATH/geant4_vmc/include/geant4vmc -I/usr/include/geant4 -I$G4PATH/geant4/include -Iinclude -I$G4INSTALL/include/Geant4");
  gInterpreter->AddIncludePath("include");
  gROOT->ProcessLine(".L src/TutorialStack.cxx+g");
  gROOT->ProcessLine(".L src/TGeomWrapper.cc+g");
  gROOT->ProcessLine(".L src/TutorialApplication.cxx+g");
  gROOT->ProcessLine(".L src/TutorialMainFrame.cxx+g");

  // MC application
  gROOT->ProcessLine("TutorialApplication* app = new TutorialApplication()");

  // configure Geant4
  gROOT->ProcessLine(".x g4Config.C");

  // instantiate graphical user interface for tutorial application
  gROOT->ProcessLine("new TutorialMainFrame(app)");
}
