g++ -o convertMC convertMC.cpp -I$PATH -I/group/clas12/packages/clas12root/1.6/Clas12Root/ -I/group/clas12/packages/clas12root/1.6/Clas12Banks/ -I/group/clas12/packages/clas12root/1.6/hipo4/ -L/group/clas12/packages/clas12root/1.6/lib/ -lClas12Banks -lClas12Root -lHipo4 `root-config --cflags --glibs`

