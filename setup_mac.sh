#setup root
#source /usr/local/root/bin/thisroot.sh
# set PATH to geant installation
# Absolute path to this script. /home/user/bin/foo.sh
#SCRIPT=$(readlink -f $0)
# Absolute path this script is in. /home/user/bin
SCRIPTPATH=$PWD
export G4PATH=$SCRIPTPATH
export VGM_INSTALL=$SCRIPTPATH/vgm430
export VGM_SYSTEM=Linux-g++#
export DYLD_LIBRARY_PATH=/usr/lib:/usr/lib/geant4/:/usr/lib/x86_64-linux-gnu:$DYLD_LIBRARY_PATH
source  /usr/local/Cellar/geant/4.10.02/bin/geant4.sh 
export G4LEVELGAMMADATA=/usr/local/Cellar/geant/4.10.02/share/Geant4-10.2.0/data/PhotonEvaporation3.2
export G4LEDATA=/usr/local/Cellar/geant/4.10.02/share/Geant4-10.2.0/data/G4EMLOW6.48
export USE_VGM=1
export DYLD_LIBRARY_PATH=$SCRIPTPATH/vgm430/lib:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$SCRIPTPATH/geant4_vmc/lib:$DYLD_LIBRARY_PATH
# path to geant4 
