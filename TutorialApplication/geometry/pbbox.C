//
// Script to define a simple geometry, a lead box, for TGeantApplication
//
void pbbox()
{
  // identifier of tracking media
  Int_t indVac = gGeoManager->GetMedium("Vacuum")->GetId();
  Int_t indPb  = gGeoManager->GetMedium("Pb")->GetId();
  
  //half lengths!!! Defines a 22 cm x 20 cm x 20 cm box
  Double_t exphXYZ[3] = { 11.,10.,10. };
  Double_t caloXYZ[3] = { 10.,10.,10. };

  Double_t* ubuf(0);
  
  // experimental hall, "world volume"
  TGeoVolume* top = gGeoManager->Volume("EXPH","BOX",indVac,exphXYZ,3);
  gGeoManager->SetTopVolume(top);
  
  // box made of Pb 
  gGeoManager->Volume("CALB","BOX",indPb,caloXYZ,3);
  gGeoManager->Node("CALB",1,"EXPH",12.0,0.0,0.0,0,kTRUE,ubuf);
  
}
    
