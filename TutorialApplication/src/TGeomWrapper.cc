////////////////////////////////////////////////////////////////////////////////
//
// TGeomWrapper
// ------------
//
////////////////////////////////////////////////////////////////////////////////

#include "TGeomWrapper.hh"
#include "TVirtualMC.h"

////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
TGeomWrapper::TGeomWrapper()
    : TVirtualMCGeometry(),
      first(true),
      fVacuum(1),
      fArGas(2),
      fPb(3),
      fFe(4),
      fU(5),
      fScint(6) {
  fGeoMCGeometry = new TGeoMCGeometry("geomcgeom", "geant copy");

  Float_t* junk(0);
  // Define the materials
  // gMC->Material(index,name,A,Z,density,rad. lenght[cm],junk,
  Material(fPb, "Pb", 207.2, 82, 11.35, 0.56, 0., junk, 0);
  Material(fArGas, "Argon gas", 39.95, 18, 1.782e-03, 14.0, 0, junk, 0);
  Material(fVacuum, "vacuum", 1.0e-16, 1.0e-16, 1.0e-16, 1.0e+16, 0, junk, 0);
  Material(fFe, "Fe", 55.845, 26, 7.87, 1.76, 0., junk, 0);
  Material(fU, "U", 238.0289, 92, 18.95, 0.32, 0., junk, 0);
  Material(fScint, "scintillator", 1.847, 1, 1.032, 42.5, 0., junk, 0);

  Int_t ifield = 0;         // No magnetic field
  Double_t fieldm = 0.;     //
  Double_t epsil = .001;    // Tracking precision,
  Double_t stemax = -0.01;  // Maximum displacement for multiple scat
  Double_t tmaxfd = -20.;   // Maximum angle due to field deflection
  Double_t deemax = -.3;    // Maximum fractional energy loss, DLS
  Double_t stmin = -.8;

  // and declare the media
  Medium(fPb, "Pb", fPb, 0, ifield, fieldm, tmaxfd, stemax, deemax, epsil,
         stmin, junk, 0);
  Medium(fArGas, "Argon gas", fArGas, 0, ifield, fieldm, tmaxfd, stemax, deemax,
         epsil, stmin, junk, 0);
  Medium(fVacuum, "vacuum", fVacuum, 0, ifield, fieldm, tmaxfd, stemax, deemax,
         epsil, stmin, junk, 0);
  Medium(fFe, "Fe", fFe, 0, ifield, fieldm, tmaxfd, stemax, deemax, epsil,
         stmin, junk, 0);
  Medium(fU, "U", fU, 0, ifield, fieldm, tmaxfd, stemax, deemax, epsil, stmin,
         junk, 0);
  Medium(fScint, "scintillator", fScint, 0, ifield, fieldm, tmaxfd, stemax,
         deemax, epsil, stmin, junk, 0);
}

//______________________________________________________________________________
TGeomWrapper::~TGeomWrapper() {
  // gMC->FinishGeometry();
  // gMC->Gsatt("*", "seen",0);
  gGeoManager->CloseGeometry();
  gGeoManager->SetVisLevel(4);
}

////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void TGeomWrapper::Gsbool(const char* onlyVolName, const char* manyVolName) {
  gMC->Gsbool(onlyVolName, manyVolName);
  fGeoMCGeometry->Gsbool(onlyVolName, manyVolName);
}

//______________________________________________________________________________
void TGeomWrapper::Gsdvn(const char* name, const char* mother, Int_t ndiv,
                         Int_t iaxis) {
  gMC->Gsdvn(name, mother, ndiv, iaxis);
  fGeoMCGeometry->Gsdvn(name, mother, ndiv, iaxis);
}

//______________________________________________________________________________
void TGeomWrapper::Gsdvn2(const char* name, const char* mother, Int_t ndiv,
                          Int_t iaxis, Double_t c0i, Int_t numed) {
  gMC->Gsdvn2(name, mother, ndiv, iaxis, c0i, numed);
  fGeoMCGeometry->Gsdvn2(name, mother, ndiv, iaxis, c0i, numed);
}

//______________________________________________________________________________
void TGeomWrapper::Gsdvt(const char* name, const char* mother, Double_t step,
                         Int_t iaxis, Int_t numed, Int_t ndvmx) {
  gMC->Gsdvt(name, mother, step, iaxis, numed, ndvmx);
  fGeoMCGeometry->Gsdvt(name, mother, step, iaxis, numed, ndvmx);
}

//______________________________________________________________________________
void TGeomWrapper::Gsdvt2(const char* name, const char* mother, Double_t step,
                          Int_t iaxis, Double_t c0, Int_t numed, Int_t ndvmx) {
  gMC->Gsdvt2(name, mother, step, iaxis, c0, numed, ndvmx);
  fGeoMCGeometry->Gsdvt2(name, mother, step, iaxis, c0, numed, ndvmx);
}

//______________________________________________________________________________
void TGeomWrapper::Gsord(const char* name, Int_t iax) {
  gMC->Gsord(name, iax);
  fGeoMCGeometry->Gsord(name, iax);
}

//______________________________________________________________________________
void TGeomWrapper::Gspos(const char* name, Int_t nr, const char* mother,
                         Double_t x, Double_t y, Double_t z, Int_t irot,
                         const char* konly) {
  gMC->Gspos(name, nr, mother, x, y, z, irot, konly);
  fGeoMCGeometry->Gspos(name, nr, mother, x, y, z, irot, konly);
}

//______________________________________________________________________________
void TGeomWrapper::Gsposp(const char* name, Int_t nr, const char* mother,
                          Double_t x, Double_t y, Double_t z, Int_t irot,
                          const char* konly, Float_t* upar, Int_t np) {
  fGeoMCGeometry->Gsposp(name, nr, mother, x, y, z, irot, konly, upar, np);
  gMC->Gsposp(name, nr, mother, x, y, z, irot, konly, upar, np);
}

//______________________________________________________________________________
void TGeomWrapper::Gsposp(const char* name, Int_t nr, const char* mother,
                          Double_t x, Double_t y, Double_t z, Int_t irot,
                          const char* konly, Double_t* upar, Int_t np) {
  fGeoMCGeometry->Gsposp(name, nr, mother, x, y, z, irot, konly, upar, np);
  gMC->Gsposp(name, nr, mother, x, y, z, irot, konly, upar, np);
}

//______________________________________________________________________________
Int_t TGeomWrapper::Gsvolu(const char* name, const char* shape, Int_t nmed,
                           Float_t* upar, Int_t np) {
  fGeoMCGeometry->Gsvolu(name, shape, nmed, upar, np);
  if (first) {
    gGeoManager->SetTopVolume(gGeoManager->GetVolume(name));
    first = false;
  } else {
    gGeoManager->GetVolume(name)->SetVisibility(kTRUE);
  }
  return gMC->Gsvolu(name, shape, nmed, upar, np);
}

//______________________________________________________________________________
Int_t TGeomWrapper::Gsvolu(const char* name, const char* shape, Int_t nmed,
                           Double_t* upar, Int_t np) {
  fGeoMCGeometry->Gsvolu(name, shape, nmed, upar, np);
  if (first) {
    gGeoManager->SetTopVolume(gGeoManager->GetVolume(name));
    first = false;
  } else {
    gGeoManager->GetVolume(name)->SetVisibility(kTRUE);
  }
  return gMC->Gsvolu(name, shape, nmed, upar, np);
}

//______________________________________________________________________________
void TGeomWrapper::Material(Int_t& kmat, const char* name, Double_t a,
                            Double_t z, Double_t dens, Double_t radl,
                            Double_t absl, Float_t* buf, Int_t nwbuf) {
  // std::cout << "material  :" << fGeoMCGeometry << " , " << gMC << std::endl;
  fGeoMCGeometry->Material(kmat, name, a, z, dens, radl, absl, buf, nwbuf);
  gMC->Material(kmat, name, a, z, dens, radl, absl, buf, nwbuf);
}

//______________________________________________________________________________
void TGeomWrapper::Material(Int_t& kmat, const char* name, Double_t a,
                            Double_t z, Double_t dens, Double_t radl,
                            Double_t absl, Double_t* buf, Int_t nwbuf) {
  // std::cout << "material  :" << fGeoMCGeometry << " , " << gMC << std::endl;
  fGeoMCGeometry->Material(kmat, name, a, z, dens, radl, absl, buf, nwbuf);
  gMC->Material(kmat, name, a, z, dens, radl, absl, buf, nwbuf);
}

//______________________________________________________________________________
void TGeomWrapper::Matrix(Int_t& krot, Double_t thetaX, Double_t phiX,
                          Double_t thetaY, Double_t phiY, Double_t thetaZ,
                          Double_t phiZ) {
  fGeoMCGeometry->Matrix(krot, thetaX, phiX, thetaY, phiY, thetaZ, phiZ);
  gMC->Matrix(krot, thetaX, phiX, thetaY, phiY, thetaZ, phiZ);
}

//______________________________________________________________________________
void TGeomWrapper::Medium(Int_t& kmed, const char* name, Int_t nmat,
                          Int_t isvol, Int_t ifield, Double_t fieldm,
                          Double_t tmaxfd, Double_t stemax, Double_t deemax,
                          Double_t epsil, Double_t stmin, Float_t* ubuf,
                          Int_t nbuf) {
  fGeoMCGeometry->Medium(kmed, name, nmat, isvol, ifield, fieldm, tmaxfd,
                         stemax, deemax, epsil, stmin, ubuf, nbuf);
  gMC->Medium(kmed, name, nmat, isvol, ifield, fieldm, tmaxfd, stemax, deemax,
              epsil, stmin, ubuf, nbuf);
}

//______________________________________________________________________________
void TGeomWrapper::Medium(Int_t& kmed, const char* name, Int_t nmat,
                          Int_t isvol, Int_t ifield, Double_t fieldm,
                          Double_t tmaxfd, Double_t stemax, Double_t deemax,
                          Double_t epsil, Double_t stmin, Double_t* ubuf,
                          Int_t nbuf) {
  fGeoMCGeometry->Medium(kmed, name, nmat, isvol, ifield, fieldm, tmaxfd,
                         stemax, deemax, epsil, stmin, ubuf, nbuf);
  gMC->Medium(kmed, name, nmat, isvol, ifield, fieldm, tmaxfd, stemax, deemax,
              epsil, stmin, ubuf, nbuf);
}

//______________________________________________________________________________
void TGeomWrapper::Mixture(Int_t& kmat, const char* name, Float_t* a,
                           Float_t* z, Double_t dens, Int_t nlmat,
                           Float_t* wmat) {
  fGeoMCGeometry->Mixture(kmat, name, a, z, dens, nlmat, wmat);
  gMC->Mixture(kmat, name, a, z, dens, nlmat, wmat);
}

//______________________________________________________________________________
void TGeomWrapper::Mixture(Int_t& kmat, const char* name, Double_t* a,
                           Double_t* z, Double_t dens, Int_t nlmat,
                           Double_t* wmat) {
  fGeoMCGeometry->Mixture(kmat, name, a, z, dens, nlmat, wmat);
  gMC->Mixture(kmat, name, a, z, dens, nlmat, wmat);
}

//______________________________________________________________________________
Int_t TGeomWrapper::NofVolumes() const { return gMC->NofVolumes(); }

//______________________________________________________________________________
Int_t TGeomWrapper::VolId(const Text_t* volName) const {
  return gMC->VolId(volName);
}

//______________________________________________________________________________
Int_t TGeomWrapper::VolId2Mate(Int_t id) const { return gMC->VolId2Mate(id); }

//______________________________________________________________________________
const char* TGeomWrapper::VolName(Int_t id) const { return gMC->VolName(id); }

////////////////////////////////////////////////////////////////////////////////
// ROOT ClassImp Macro
////////////////////////////////////////////////////////////////////////////////

ClassImp(TGeomWrapper)
