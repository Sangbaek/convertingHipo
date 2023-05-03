#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include <string>
#include <iostream>
#include <vector>
#include "HipoChain.h"
#include "clas12reader.h"
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

   // === xB, Q2, t, phi====
    TVector3 beam(0, 0, 10.604);
    TVector3 ele;
    TVector3 pro;
    TVector3 v3l;
    TVector3 v3h;
    TVector3 VGS;
    Float_t nu;

    Float_t me = 0.5109989461 * 0.001;
    Float_t M = 0.938272081;

    Float_t GenxB;
    Float_t GenQ2;
    Float_t Gent;
    Float_t Genphi;

   // =====  proton =====
    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    Float_t GenPp;
    Float_t GenPtheta;
    Float_t GenPphi;

    // ==== electron =====
    Float_t GenEpx;
    Float_t GenEpy;
    Float_t GenEpz;

    Float_t GenEp;
    Float_t GenEtheta;
    Float_t GenEphi;
    
    // ==== gammas =====
    Int_t nmG;
    Float_t GenGpx[2];
    Float_t GenGpy[2];
    Float_t GenGpz[2];

    Float_t GenGp[2];
    Float_t GenGptheta[2];
    Float_t GenGphi[2];

    // =====  pion =====
    Int_t nmpi;

    Float_t GenPipx;
    Float_t GenPipy;
    Float_t GenPipz;

    Float_t GenPip;
    Float_t GenPitheta;
    Float_t GenPiphi;
    

    T->Branch("GenxB",&GenxB,"GenxB/F");
    T->Branch("GenQ2",&GenQ2,"GenQ2/F");
    T->Branch("Gent",&Gent,"Gent/F");
    T->Branch("Genphi",&Genphi,"Genphi/F");

// ===============    Electrons ==============    
    T->Branch("GenEpx",&GenEpx,"GenEpx/F");
    T->Branch("GenEpy",&GenEpy,"GenEpy/F");
    T->Branch("GenEpz",&GenEpz,"GenEpz/F");

    T->Branch("GenEp",&GenEp,"GenEp/F");
    T->Branch("GenEtheta",&GenEtheta,"GenEtheta/F");
    T->Branch("GenEphi",&GenEphi,"GenEphi/F");

// ===============    Protons ================================== 
    T->Branch("GenPpx",&GenPpx,"GenPpx/F");
    T->Branch("GenPpy",&GenPpy,"GenPpy/F");
    T->Branch("GenPpz",&GenPpz,"GenPpz/F");

    T->Branch("GenPp",&GenPp,"GenPp/F");
    T->Branch("GenPtheta",&GenPtheta,"GenPtheta/F");
    T->Branch("GenPphi",&GenPphi,"GenPphi/F");

// ===============    Pions ================================== 
    T->Branch("GenPipx",&GenPipx,"GenPipx/F");
    T->Branch("GenPipy",&GenPipy,"GenPipy/F");
    T->Branch("GenPipz",&GenPipz,"GenPipz/F");

    T->Branch("GenPip",&GenPip,"GenPip/F");
    T->Branch("GenPitheta",&GenPitheta,"GenPitheta/F");
    T->Branch("GenPiphi",&GenPiphi,"GenPiphi/F");


// ================   Gammas  ===============    
    T->Branch("nmG",&nmG,"nmG/I");
    T->Branch("GenGpx",&GenGpx,"GenGpx[nmG]/F");
    T->Branch("GenGpy",&GenGpy,"GenGpy[nmG]/F");
    T->Branch("GenGpz",&GenGpz,"GenGpz[nmG]/F");

    T->Branch("GenGp",&GenGp,"GenGp/F");
    T->Branch("GenGtheta",&GenGtheta,"GenGtheta/F");
    T->Branch("GenGphi",&GenGphi,"GenGphi/F");

  //
  //loop over files
  //
  for(int ifile=0; ifile<chain.GetNFiles();++ifile){
      clas12::clas12reader c12{chain.GetFileName(ifile).Data()};
      
      // MC particle bank ========
      auto idx_GenPart = c12.addBank("MC::Particle");
      auto iPid = c12.getBankOrder(idx_GenPart,"pid");
      auto iPx  = c12.getBankOrder(idx_GenPart,"px");
      auto iPy  = c12.getBankOrder(idx_GenPart,"py");
      auto iPz  = c12.getBankOrder(idx_GenPart,"pz");

        while(c12.next() == true){
    
          nmG=0;

          for(auto ipa=0;ipa<c12.getBank(idx_GenPart)->getRows();ipa++){

            
              auto tPx = c12.getBank(idx_GenPart)->getFloat(iPx,ipa);
              auto tPy = c12.getBank(idx_GenPart)->getFloat(iPy,ipa);
              auto tPz = c12.getBank(idx_GenPart)->getFloat(iPz,ipa);


              if( (c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 11  ){  // electrons
                  GenEpx = tPx;
                  GenEpy = tPy;
                  GenEpz = tPz;

                  GenEp     = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz);
                  GenEtheta = (180.0/TMath::Pi())*TMath::ATan2(TMath::Sqrt(tPx*tPx+tPy*tPy),tPz);
                  GenEphi   = (180.0/TMath::Pi())*TMath::ATan2(tPy,tPx);
              }
            
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 2212  ){  // protons
                  GenPpx = tPx;
                  GenPpy = tPy;
                  GenPpz = tPz;

                  GenPp     = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz);
                  GenPtheta = (180.0/TMath::Pi())*TMath::ATan2(TMath::Sqrt(tPx*tPx+tPy*tPy),tPz);
                  GenPphi   = (180.0/TMath::Pi())*TMath::ATan2(tPy,tPx);
            	}

              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 111  ){  // pions
                  GenPipx = tPx;
                  GenPipy = tPy;
                  GenPipz = tPz;
                
                  GenPip     = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz);
                  GenPitheta = (180.0/TMath::Pi())*TMath::ATan2(TMath::Sqrt(tPx*tPx+tPy*tPy),tPz);
                  GenPiphi   = (180.0/TMath::Pi())*TMath::ATan2(tPy,tPx);
              } // if for protons
                
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 22  ){  // photons
                  GenGpx[nmG] = tPx;
                  GenGpy[nmG] = tPy;
                  GenGpz[nmG] = tPz;

                  GenGp[nmG]     = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz);
                  GenGtheta[nmG] = (180.0/TMath::Pi())*TMath::ATan2(TMath::Sqrt(tPx*tPx+tPy*tPy),tPz);
                  GenGphi[nmG]   = (180.0/TMath::Pi())*TMath::ATan2(tPy,tPx);

                  nmG++;
              }
          }

          ele.setXYZ(GenEpx, GenEpy, GenEpz);
          pro.setXYZ(GenPpx, GenPpy, GenPpz);
          VGS.SetXYZ(-GenEpx, -GenEpy, 10.604 - GenEpz);

          nu     = 10.604 - TMath::Sqrt(GenEp*GenEp + me*me);
          GenQ2  = -(nu*nu - VGS.Mag2());
          GenxB  = GenQ2 / 2.0 / M / nu;
          Gent   = 2 * M * (TMath::Sqrt(GenPp*GenPp+M*M) - M);

          v3l = beam.Cross(ele);
          v3h = pro.Cross(VGS);
          Genphi = v3l.Angle(v3h);
          if (v3l.Dot(pro) > 0) {
            Genphi = 2*TMath::Pi() - Genphi;
          }
          Genphi = (180.0/TMath::Pi())*Genphi;

          if (nmG>0) T->Fill();
        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}