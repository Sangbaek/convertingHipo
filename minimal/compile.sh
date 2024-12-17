#!/usr/bin/bash

source /cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/setup.sh
module load clas12

g++ -o convertEP convertEP.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertEPEbar convertEPEbar.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertEPG convertEPG.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertEPPiPPiMGG convertEPPiPPiMGG.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertEPKPKMGG convertEPKPKMGG.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertGen convertGen.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertRec convertRec.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertGen2 convertGen2.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertRec2 convertRec2.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertRec_ep convertRec_ep.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`
g++ -o convertRec_epebar convertRec_epebar.cpp -Wl,--copy-dt-needed-entries -I$PATH -I$CLAS12ROOT/Clas12Root/ -I$CLAS12ROOT/Clas12Banks/ -I$HIPO/include/ -L$CLAS12ROOT/lib/ -L$HIPO/lib/ -lClas12Banks -lClas12Root  `root-config --cflags --glibs`