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

    Float_t GenxB;
    Float_t GenQ2;
    Float_t Gent;
    Float_t Genphi;
    Float_t GenWeight;
    Int_t nmG;
    Int_t radMode;

// ===============    xB ==============    
    T->Branch("GenxB",&GenxB,"GenxB/F");
    T->Branch("GenQ2",&GenQ2,"GenQ2/F");
    T->Branch("Gent",&Gent,"Gent/F");
    T->Branch("Genphi",&Genphi,"Genphi/F");
    T->Branch("GenWeight",&GenWeight,"GenWeight/F");
    T->Branch("radMode",&radMode,"radMode/I");
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
      auto iMode  = c12.getBankOrder(idx_GenLund,"daughter");

      auto idx_GenEvent = c12.addBank("MC::Event");
      // auto iInd = c12.getBankOrder(idx_GenEvent,"index");
      auto iWeight  = c12.getBankOrder(idx_GenEvent,"weight");

        while(c12.next() == true){

          nmG=0;
    
          for(auto ipa=0;ipa<c12.getBank(idx_GenLund)->getRows();ipa++){
            
              auto tLifetime = c12.getBank(idx_GenLund)->getFloat(iLifetime,ipa);
              auto tEnergy = c12.getBank(idx_GenLund)->getFloat(iEnergy,ipa);
              auto tMass = c12.getBank(idx_GenLund)->getFloat(iMass,ipa);
              auto tMode = c12.getBank(idx_GenLund)->getInt(iMode,ipa);

              if( ipa == 0 ){  // electrons
                  GenxB = tLifetime;
                  GenQ2 = tEnergy;
                  Gent = tMass;
                  radMode = tMode;
              }
            
              if( ipa == 1 ){  // protons
                  Genphi = (M_PI-tLifetime)*180.0/M_PI; 
              }
              nmG++;

          }
          for(auto ipa=0;ipa<c12.getBank(idx_GenEvent)->getRows();ipa++){

              auto tWeight = c12.getBank(idx_GenEvent)->getFloat(iWeight,ipa);

              if( ipa == 0 ){  
                  GenWeight = tWeight; //diff x-sec
              }
          }

          if (nmG>0) T->Fill();

        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}