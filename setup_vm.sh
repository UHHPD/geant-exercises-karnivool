#setup root
source /usr/local/root532/bin/thisroot.sh
# set PATH to geant installation
# Absolute path to this script. /home/user/bin/foo.sh
SCRIPT=$(readlink -f $0)
# Absolute path this script is in. /home/user/bin
SCRIPTPATH=`dirname $SCRIPT`
export G4PATH=/usr/local/geant4
export VGM_INSTALL=/usr/local/geant4/vgm.3.05
export VGM_SYSTEM=Linux-g++#
export LD_LIBRARY_PATH=/usr/lib:/usr/local/geant4/geant4.9.5.p02-install/lib/:/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
export G4INSTALL="/usr/local/geant4/geant4.9.5.p02-install/"
#source  /usr/share/geant4/env.sh
source /usr/local/geant4/geant4.9.5.p02-install//bin/geant4.sh
export G4LEVELGAMMADATA=`readlink -e $G4PATH/PhotonEvaporation2.2/`
export G4LEDATA=`readlink -e $G4PATH/G4EMLOW6.23/`
export USE_VGM=1

export LD_LIBRARY_PATH=/usr/local/geant4/vgm.3.05/lib/Linux-g++:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/geant4/geant4_vmc/lib/tgt_linux:$LD_LIBRARY_PATH
# path to geant4 
