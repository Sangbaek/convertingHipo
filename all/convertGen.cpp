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

    TLorentzVector p4_proton;
    TLorentzVector p4_electron;
    TLorentzVector p4_gamma[2];

   // =====  proton =====
    Float_t GenPe;
    Float_t GenPp;
    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    Float_t GenPtheta;
    Float_t GenPphi;

    // ==== electron =====
    Float_t GenEe;
    Float_t GenEp;
    Float_t GenEpx;
    Float_t GenEpy;
    Float_t GenEpz;
    Float_t GenEvx;
    Float_t GenEvy;
    Float_t GenEvz;
    Float_t GenEtheta;
    Float_t GenEphi;
    
    // ==== gammas =====
    Int_t nmG;
    Float_t GenGe[2];
    Float_t GenGp[2];
    Float_t GenGpx[2];
    Float_t GenGpy[2];
    Float_t GenGpz[2];
    Float_t GenGtheta[2];
    Float_t GenGphi[2];

// ===============    Electrons ==============    
    T->Branch("GenEp",&GenEp,"GenEp/F");
    T->Branch("GenEpx",&GenEpx,"GenEpx/F");
    T->Branch("GenEpy",&GenEpy,"GenEpy/F");
    T->Branch("GenEpz",&GenEpz,"GenEpz/F");
    T->Branch("GenEvx",&GenEvx,"GenEvx/F");
    T->Branch("GenEvy",&GenEvy,"GenEvy/F");
    T->Branch("GenEvz",&GenEvz,"GenEvz/F");
    T->Branch("GenEtheta",&GenEtheta,"GenEtheta/F");
    T->Branch("GenEphi",&GenEphi,"GenEphi/F");

// ===============    Protons ================================== 
    T->Branch("GenPp",&GenPp,"GenPp/F");
    T->Branch("GenPpx",&GenPpx,"GenPpx/F");
    T->Branch("GenPpy",&GenPpy,"GenPpy/F");
    T->Branch("GenPpz",&GenPpz,"GenPpz/F");
    T->Branch("GenPtheta",&GenPtheta,"GenPtheta/F");
    T->Branch("GenPphi",&GenPphi,"GenPphi/F");


// ================   Gammas  ===============    
    T->Branch("nmG",&nmG,"nmG/I");
    T->Branch("GenGp",&GenGp,"GenGp[nmG]/F");
    T->Branch("GenGpx",&GenGpx,"GenGpx[nmG]/F");
    T->Branch("GenGpy",&GenGpy,"GenGpy[nmG]/F");
    T->Branch("GenGpz",&GenGpz,"GenGpz[nmG]/F");
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
      auto iVx  = c12.getBankOrder(idx_GenPart,"vx");
      auto iVy  = c12.getBankOrder(idx_GenPart,"vy");
      auto iVz  = c12.getBankOrder(idx_GenPart,"vz");

      while(c12.next() == true){
    
          nmG=0;

          for(auto ipa=0;ipa<c12.getBank(idx_GenPart)->getRows();ipa++){
            
              auto tPx = c12.getBank(idx_GenPart)->getFloat(iPx,ipa);
              auto tPy = c12.getBank(idx_GenPart)->getFloat(iPy,ipa);
              auto tPz = c12.getBank(idx_GenPart)->getFloat(iPz,ipa);
              auto tVx = c12.getBank(idx_GenPart)->getFloat(iVx,ipa);
              auto tVy = c12.getBank(idx_GenPart)->getFloat(iVy,ipa);
              auto tVz = c12.getBank(idx_GenPart)->getFloat(iVz,ipa);

              if( (c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 11  ){  // electrons
                p4_electron.SetXYZM(tPx,tPy,tPz,0.5109989461 * 0.001);
                GenEp = p4_electron.P();
                GenEpx = p4_electron.Px();
                GenEpy = p4_electron.Py();
                GenEpz = p4_electron.Pz();
                GenEtheta = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
                GenEphi   = TMath::ATan2(tPy,tPx);
                GenEvx = tVx;
                GenEvy = tVy;
                GenEvz = tVz;
              }
            
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 2212  ){  // protons
                p4_proton.SetXYZM(tPx,tPy,tPz,0.938272081);
                GenPp = p4_proton.P();
                GenPpx = p4_proton.Px();
                GenPpy = p4_proton.Py();
                GenPpz = p4_proton.Pz();
                GenPtheta = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
                GenPphi   = TMath::ATan2(tPy,tPx);
                
              } // if for protons
                
              if((c12.getBank(idx_GenPart)->getInt(iPid,ipa)) == 22  ){  // photons
                p4_gamma[nmG].SetXYZM(tPx,tPy,tPz,0.938272081);
                GenGp[nmG]  = p4_gamma[nmG].P();
                GenGpx[nmG] = p4_gamma[nmG].Px();
                GenGpy[nmG] = p4_gamma[nmG].Py();
                GenGpz[nmG] = p4_gamma[nmG].Pz();
                GenGtheta[nmG] = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
                GenGphi[nmG]   = TMath::ATan2(tPy,tPx);
                nmG++;
              }
          }

          T->Fill();

        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}