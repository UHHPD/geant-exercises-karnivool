#ifndef TUTORIALMAINFRAME_HH
#define TUTORIALMAINFRAME_HH
#include "TGFrame.h"

class TutorialApplication;
class TRootEmbeddedCanvas;
class TGTextEntry;
class TGHSlider;

class TutorialMainFrame : public TGMainFrame {
 public:
  // construction / destruction
  TutorialMainFrame(TutorialApplication* app);
  virtual ~TutorialMainFrame();

  // member functions
 public:
  void HandleMomentumSlider(int pos);
  void HandleMomentumText();
  void HandleType(int kf);
  void HandleNextEvent();
  void HandleExit();

  // member data
 private:
  TRootEmbeddedCanvas* fCanvas;
  TutorialApplication* fApp;
  TGTextEntry* fMomentumText;
  TGHSlider* fMomentumSlider;
};

#endif
