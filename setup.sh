
# set PATH to geant installation
# Absolute path to this script. /home/user/bin/foo.sh
#SCRIPT=$(readlink -f $0)
# Absolute path this script is in. /home/user/bin
#SCRIPTPATH=$PWD
export G4PATH=/afs/physnet.uni-hamburg.de/users/ex_ba/hstadie
#setup root
source $G4PATH/root/bin/thisroot.sh
export VGM_INSTALL=$G4PATH/vgm
#export VGM_SYSTEM=Linux-g++#
export LD_LIBRARY_PATH==$G4PATH/geant4/lib:$LD_LIBRARY_PATH
export G4INSTALL=$G4PATH/geant4
source  $G4INSTALL/bin/geant4.sh
#source /usr/local/geant4/geant4.9.5.p02-install//bin/geant4.sh
#export G4LEVELGAMMADATA=`readlink -e $G4PATH/PhotonEvaporation2.2/`
#export G4LEDATA=`readlink -e $G4PATH/G4EMLOW6.23/`
export USE_VGM=1

export LD_LIBRARY_PATH=$G4PATH/vgm/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$G4PATH/geant4_vmc/lib:$LD_LIBRARY_PATH
# path to geant4 
