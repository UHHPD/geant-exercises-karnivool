#setup root
#source /usr/local/root/bin/thisroot.sh
source /usr/local/root532/bin/thisroot.sh
# set PATH to geant installation
export G4PATH="/usr/local/geant4"
export VGM_INSTALL=$G4PATH/vgm.3.05
export VGM_SYSTEM=Linux-g++
export G4INSTALL="/usr/local/geant4/geant4.9.5.p02-install/"

source /usr/local/geant4/geant4.9.5.p02-install//bin/geant4.sh
export G4LEVELGAMMADATA=`readlink -e $G4PATH/PhotonEvaporation2.2/`
export G4LEDATA=`readlink -e $G4PATH/G4EMLOW6.23/`
export USE_VGM=1

export LD_LIBRARY_PATH=`readlink -e $G4PATH/vgm.3.05/lib/Linux-g++/`:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=`readlink -e $G4PATH/geant4_vmc/lib/tgt_linux`:$LD_LIBRARY_PATH
# path to geant4 
