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
    Float_t BornWeight;
    Int_t nmG;
    Int_t radMode;
    Float_t helicity;

    Long_t crossRef;
    Long_t nFile;
    Long_t EventNumPre;
    Long_t EventNumCur;

    Long_t config;

   // =====  proton =====
    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    
    // ==== gammas =====
    Float_t GenGpx;
    Float_t GenGpy;
    Float_t GenGpz;

    Float_t GenPtheta;
    Float_t GenGtheta;

// ===============    xB ==============    
    T->Branch("GenxB",&GenxB,"GenxB/F");
    T->Branch("GenQ2",&GenQ2,"GenQ2/F");
    T->Branch("Gent",&Gent,"Gent/F");
    T->Branch("Genphi",&Genphi,"Genphi/F");
    T->Branch("GenWeight",&GenWeight,"GenWeight/F");
    T->Branch("BornWeight",&BornWeight,"BornWeight/F");
    T->Branch("radMode",&radMode,"radMode/I");
    T->Branch("helicity",&helicity,"helicity/F");
    T->Branch("crossRef",&crossRef,"crossRef/L");
    T->Branch("config",&config,"config/L");
  //
  //loop over files
  //
  for(int ifile=0; ifile<chain.GetNFiles();++ifile){
      clas12::clas12reader c12{chain.GetFileName(ifile).Data()};
      
      // MC Lund bank ========
      auto idx_GenLund = c12.addBank("MC::Lund");
      auto iInd = c12.getBankOrder(idx_GenLund,"index");
      auto iLifetime  = c12.getBankOrder(idx_GenLund,"lifetime");
      auto iEnergy  = c12.getBankOrder(idx_GenLund,"energy");
      auto iMass  = c12.getBankOrder(idx_GenLund,"mass");
      auto iMode  = c12.getBankOrder(idx_GenLund,"daughter");


      // MC particle bank ========
      auto idx_GenPart = c12.addBank("MC::Particle");
      auto iPid = c12.getBankOrder(idx_GenPart,"pid");
      auto iPx  = c12.getBankOrder(idx_GenPart,"px");
      auto iPy  = c12.getBankOrder(idx_GenPart,"py");
      auto iPz  = c12.getBankOrder(idx_GenPart,"pz");

      auto idx_GenEvent = c12.addBank("MC::Event");
      // auto iInd = c12.getBankOrder(idx_GenEvent,"index");
      auto iWeight  = c12.getBankOrder(idx_GenEvent,"weight");
      auto iHelic = c12.getBankOrder(idx_GenEvent,"pbeam");

      //  Config Bank
      auto idx_RUNCon = c12.addBank("RUN::config");
      auto bevent = c12.getBankOrder(idx_RUNCon,"event");

      nFile = 0;
      EventNumPre = 0;
      crossRef = 0;

        while(c12.next() == true){

          nmG=0;
          crossRef++;

          for(auto ipa=1;ipa<3;ipa++){
            
              auto tPx = c12.getBank(idx_GenPart)->getFloat(iPx,ipa);
              auto tPy = c12.getBank(idx_GenPart)->getFloat(iPy,ipa);
              auto tPz = c12.getBank(idx_GenPart)->getFloat(iPz,ipa);
            
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 2212  ){  // protons
                  GenPpx = tPx;
                  GenPpy = tPy;
                  GenPpz = tPz;
              }
                
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 22  ){  // photons
                  GenGpx = tPx;
                  GenGpy = tPy;
                  GenGpz = tPz;
              }
          }

          GenPtheta = TMath::ATan2(TMath::Sqrt(GenPpx*GenPpx+GenPpy*GenPpy),GenPpz);
          GenGtheta = TMath::ATan2(TMath::Sqrt(GenGpx*GenGpx+GenGpy*GenGpy),GenGpz);

          if (GenPtheta<40 && GenGtheta<5) config = 0; // FDFT
          else if (GenPtheta<40 && (GenGtheta>=5)) config = 1; //FDFD
          else if (GenPtheta>=40 && (GenGtheta>=5)) config = 2; //CDFD
          else if ((GenPtheta>=40) && (GenGtheta<5)) config = 3; //CDFT
          else config = -1;//errorneous bit
    
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
              if( ipa == 2 ){  // protons
                  BornWeight = tMass;
              }
              nmG++;

          }
          for(auto ipa=0;ipa<c12.getBank(idx_GenEvent)->getRows();ipa++){

              auto tWeight = c12.getBank(idx_GenEvent)->getFloat(iWeight,ipa);
              auto tHelic = c12.getBank(idx_GenEvent)->getFloat(iHelic,ipa);

              if( ipa == 0 ){  
                  GenWeight = tWeight; //diff x-sec
                  helicity = tHelic; //pol.
              }
          }

          // Run config bank
          for(auto ipa1 = 0; ipa1<c12.getBank(idx_RUNCon)->getRows();ipa1++){
              auto tempE = c12.getBank(idx_RUNCon)->getInt(bevent,ipa1);
              
              EventNumCur = tempE;
          }

          if (EventNumCur<EventNumPre)  nFile++;
          crossRef = nFile * 10000 + EventNumCur;
          EventNumPre = EventNumCur;


          if (nmG>0) T->Fill();

        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}