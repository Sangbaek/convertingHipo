#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include <string>
#include <iostream>
#include <vector>
#include "HipoChain.h"
#include "clas12reader.h"
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
    clas12root::HipoChain chain;

    char File[200];
    system("ls -1 *.hipo > dataFiles.txt");
    ifstream in("dataFiles.txt", ios::in);
    if(!in){
      cerr<< "File Not Opened!" <<endl;
      exit(1);
    }
    while( in >> File){
      cout<<" File Name = "<<File<<endl;
      chain.Add(File);  
    }

    TFile *rFile = TFile::Open("genOnly.root","RECREATE");
    TTree *T=new TTree("T","Gen");

   // =====  proton =====
    Float_t xB;
    Float_t Q2;
    Float_t t2;
    Float_t phi2;

// ===============    xB ==============    
    T->Branch("xB",&xB,"xB/F");
    T->Branch("Q2",&Q2,"Q2/F");
    T->Branch("t2",&t2,"t2/F");
    T->Branch("phi2",&phi2,"phi2/F");

  //
  //loop over files
  //
  for(int ifile=0; ifile<chain.GetNFiles();++ifile){
      clas12::clas12reader c12{chain.GetFileName(ifile).Data()};
      
      // MC particle bank ========
      auto idx_GenLund = c12.addBank("MC::Lund");
      auto iInd = c12.getBankOrder(idx_GenLund,"index");
      auto iLifetime  = c12.getBankOrder(idx_GenLund,"lifetime");
      auto iEnergy  = c12.getBankOrder(idx_GenLund,"energy");
      auto iMass  = c12.getBankOrder(idx_GenLund,"mass");

        while(c12.next() == true){
    
          for(auto ipa=0;ipa<c12.getBank(idx_GenLund)->getRows();ipa++){
            
              auto tLifetime = c12.getBank(idx_GenLund)->getFloat(iLifetime,ipa);
              auto tEnergy = c12.getBank(idx_GenLund)->getFloat(iEnergy,ipa);
              auto tMass = c12.getBank(idx_GenLund)->getFloat(iMass,ipa);

              if( ipa == 0 ){  // electrons
                  xB = tLifetime;
                  Q2 = tEnergy;
                  t2 = tMass;
              }
            
              if( ipa == 1 ){  // protons
                  phi2 = (M_PI-tLifetime)*180.0/M_PI;
                
              } // if for protons

          }

          T->Fill();

        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}