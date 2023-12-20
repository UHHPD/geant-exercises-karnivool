//
// Script to define a simple geometry, a lead box, for TGeantApplication
//
void tracker2(double pos1 = -45.0, double pos2 = -30,double pos3 = 45.0, double pitch = 0.0150, double materialLength = 0.6, double Bfield = 2.0)
{
  double layerpos[] = { pos1,pos2,pos3};
  TVirtualMagField *B = new TGeoUniformMagField(0.0,Bfield*10,0);
  gMC->SetMagField(B);
 
  //
  // TRACKING MEDIA
  //
  Int_t    ifield =     2;  // magnetic field
  Double_t fieldm =    20;  //
  Double_t epsil  =  .001;  // Tracking precision,
  Double_t stemax = -0.01;  // Maximum displacement for multiple scat
  Double_t tmaxfd =  -90.;  // Maximum angle due to field deflection
  Double_t deemax =   -.3;  // Maximum fractional energy loss, DLS
  Double_t stmin  =   -.0001;
  
  TGeoMedium *vac =gGeoManager->Medium("Vacuum2", 10, 1,
					     0, ifield, fieldm, tmaxfd, stemax, deemax, epsil, stmin); 
  epsil  =  .0001;
  stemax = -0.01;
  Double_t a = 28.0855;
  Double_t z = 14;
  Double_t density = 2.33;
  Double_t radl = 9.36;
  Double_t absl = 0;
  gGeoManager->Material("Si", a, z, density, 11, radl, absl);
  
  TGeoMedium *si = gGeoManager->Medium("Si",11, 11,
					     0, ifield, fieldm, tmaxfd, stemax, deemax, epsil, stmin); 
  TGeoMedium *fe = gGeoManager->Medium("Fe2",12, 4,
					     0, ifield, fieldm, tmaxfd, stemax, deemax, epsil, stmin); 
  

  //half lengths!!! Defines a 22 cm x 20 cm x 20 cm box
  Double_t exphXYZ[3] = { 51.,50.,50. };
  Double_t structureXYZ[3] = { materialLength/4,50.,50. };
  const double thickness = 0.0400;

  Double_t* ubuf(0);
  
  // experimental hall, "world volume"
  TGeoVolume* top = gGeoManager->MakeBox("EXPH",vac,exphXYZ[0],exphXYZ[1],exphXYZ[2]);
  gGeoManager->SetTopVolume(top);
  
  //box for layer
  TGeoVolume* layer = gGeoManager->MakeBox("Layer",vac,thickness/2+2*structureXYZ[0],exphXYZ[1],exphXYZ[2]);
  
  
  // box made of Pb 
  TGeoVolume* struc = gGeoManager->MakeBox("Structure",fe,structureXYZ[0],structureXYZ[1],structureXYZ[2]); 
  TGeoVolume* silayer = gGeoManager->MakeBox("SiLayer",si,thickness/2,structureXYZ[1],structureXYZ[2]); 
  //TGeoVolume* strips = silayer->Divide("Strips",3,2*structureXYZ[2]/pitch,-structureXYZ[2]+pitch/2,pitch);
  TGeoVolume* strips = silayer->Divide("Strips",3,-1,0,pitch,0,"S");
  //layer->AddNode(silayer,1,new TGeoTranslation(2*structureXYZ[0]+0.5*thickness,0,0));
  layer->AddNode(struc,0,new TGeoTranslation(-structureXYZ[0]-thickness/2,0,0));
  layer->AddNode(silayer,1,new TGeoTranslation(0,0,0));
  layer->AddNode(struc,2,new TGeoTranslation(structureXYZ[0]+thickness/2,0,0));


  for(int i = 0 ; i < 3 ; ++i) {
    top->AddNode(layer,i,new TGeoTranslation(layerpos[i],0,0));
  }
}
    
