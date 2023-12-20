#ifndef TGEOMWRAPPER_HH
#define TGEOMWRAPPER_HH 1

////////////////////////////////////////////////////////////////////////////////
//
// class to clone the geometry.
// This allows to register the geometry in Geant as well as
// in the TGeoManager.
//
////////////////////////////////////////////////////////////////////////////////

#include <TGeoMCGeometry.h>
#include <TGeoManager.h>
#include <TVirtualMCGeometry.h>

//#include <TGeant3.h>

class TGeomWrapper : public TVirtualMCGeometry {
 public:
  //
  // construction / destruction
  //
  TGeomWrapper();
  virtual ~TGeomWrapper();

  //
  // member functions
  //
  void Gsbool(const char* onlyVolName, const char* manyVolName);
  void Gsdvn(const char* name, const char* mother, Int_t ndiv, Int_t iaxis);
  void Gsdvn2(const char* name, const char* mother, Int_t ndiv, Int_t iaxis,
              Double_t c0i, Int_t numed);
  void Gsdvt(const char* name, const char* mother, Double_t step, Int_t iaxis,
             Int_t numed, Int_t ndvmx);
  void Gsdvt2(const char* name, const char* mother, Double_t step, Int_t iaxis,
              Double_t c0, Int_t numed, Int_t ndvmx);
  void Gsord(const char* name, Int_t iax);
  void Gspos(const char* name, Int_t nr, const char* mother, Double_t x,
             Double_t y, Double_t z, Int_t irot, const char* konly = "ONLY");
  void Gsposp(const char* name, Int_t nr, const char* mother, Double_t x,
              Double_t y, Double_t z, Int_t irot, const char* konly,
              Float_t* upar, Int_t np);
  void Gsposp(const char* name, Int_t nr, const char* mother, Double_t x,
              Double_t y, Double_t z, Int_t irot, const char* konly,
              Double_t* upar, Int_t np);
  Int_t Gsvolu(const char* name, const char* shape, Int_t nmed, Float_t* upar,
               Int_t np);
  Int_t Gsvolu(const char* name, const char* shape, Int_t nmed, Double_t* upar,
               Int_t np);

  void Material(Int_t& kmat, const char* name, Double_t a, Double_t z,
                Double_t dens, Double_t radl, Double_t absl, Float_t* buf,
                Int_t nwbuf);
  void Material(Int_t& kmat, const char* name, Double_t a, Double_t z,
                Double_t dens, Double_t radl, Double_t absl, Double_t* buf,
                Int_t nwbuf);

  void Matrix(Int_t& krot, Double_t thetaX, Double_t phiX, Double_t thetaY,
              Double_t phiY, Double_t thetaZ, Double_t phiZ);

  void Medium(Int_t& kmed, const char* name, Int_t nmat, Int_t isvol,
              Int_t ifield, Double_t fieldm, Double_t tmaxfd, Double_t stemax,
              Double_t deemax, Double_t epsil, Double_t stmin, Float_t* ubuf,
              Int_t nbuf);
  void Medium(Int_t& kmed, const char* name, Int_t nmat, Int_t isvol,
              Int_t ifield, Double_t fieldm, Double_t tmaxfd, Double_t stemax,
              Double_t deemax, Double_t epsil, Double_t stmin, Double_t* ubuf,
              Int_t nbuf);

  void Mixture(Int_t& kmat, const char* name, Float_t* a, Float_t* z,
               Double_t dens, Int_t nlmat, Float_t* wmat);
  void Mixture(Int_t& kmat, const char* name, Double_t* a, Double_t* z,
               Double_t dens, Int_t nlmat, Double_t* wmat);

  Int_t NofVolumes() const;
  Int_t VolId(const Text_t* volName) const;
  Int_t VolId2Mate(Int_t id) const;
  const char* VolName(Int_t id) const;

  // Materials
  Int_t Vacuum() const { return fVacuum; }
  Int_t ArGas() const { return fArGas; }
  Int_t Pb() const { return fPb; }
  Int_t Fe() const { return fFe; }
  Int_t U() const { return fU; }
  Int_t Scint() const { return fScint; }

 private:
  //
  // member data
  //
  TGeoMCGeometry* fGeoMCGeometry;
  Bool_t first;

  Int_t fVacuum;
  Int_t fArGas;
  Int_t fPb;
  Int_t fFe;
  Int_t fU;
  Int_t fScint;

  ClassDef(TGeomWrapper, 0);
};

#endif
