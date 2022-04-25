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

    Int_t crossRef;

// ===============    xB ==============    
    T->Branch("GenxB",&GenxB,"GenxB/F");
    T->Branch("GenQ2",&GenQ2,"GenQ2/F");
    T->Branch("Gent",&Gent,"Gent/F");
    T->Branch("Genphi",&Genphi,"Genphi/F");
    T->Branch("GenWeight",&GenWeight,"GenWeight/F");
    T->Branch("BornWeight",&BornWeight,"BornWeight/F");
    T->Branch("radMode",&radMode,"radMode/I");
    T->Branch("helicity",&helicity,"helicity/F");
    T->Branch("crossRef",&crossRef,"crossRef/I");
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
      auto iHelic = c12.getBankOrder(idx_GenEvent,"pbeam");

        //  Filter bank created by Sangbaek
        auto idx_FILTER = c12.addBank("FILTER::Index");
        auto iInd = c12.getBankOrder(idx_FILTER,"before");
        auto iPcalSector = c12.getBankOrder(idx_FILTER, "pcal_sector");
        auto iFtof1aSector = c12.getBankOrder(idx_FILTER, "ftof1a_sector");
        auto iFtof1bSector = c12.getBankOrder(idx_FILTER, "ftof1b_sector");
        auto iFtof2Sector = c12.getBankOrder(idx_FILTER, "ftof2_sector");
        //=========

        // Read banks: with DC, CVT, FTOF, LTCC, HTCC, ECAL, CTOF, CND 
        auto idx_Traj = c12.addBank("REC::Traj");
        auto iPindex = c12.getBankOrder(idx_Traj,"pindex");
        auto iDetector = c12.getBankOrder(idx_Traj,"detector");
        auto iLayer = c12.getBankOrder(idx_Traj,"layer");
        auto iX = c12.getBankOrder(idx_Traj,"x");
        auto iY = c12.getBankOrder(idx_Traj,"y");
        auto iZ = c12.getBankOrder(idx_Traj,"z");
        // ========================

        // Scintillator bank
        auto idx_RECScint = c12.addBank("REC::Scintillator");
        auto jPindex = c12.getBankOrder(idx_RECScint,"pindex");
        auto jDet = c12.getBankOrder(idx_RECScint,"detector");
        auto jSec = c12.getBankOrder(idx_RECScint,"sector");
        auto jLay = c12.getBankOrder(idx_RECScint,"layer");
        auto jTim = c12.getBankOrder(idx_RECScint,"time");
        auto jPat = c12.getBankOrder(idx_RECScint,"path");
        auto jX   = c12.getBankOrder(idx_RECScint,"x");
        auto jY = c12.getBankOrder(idx_RECScint,"y");
        auto jZ = c12.getBankOrder(idx_RECScint,"z");

        // REC::Track 
        auto ldx_Track = c12.addBank("REC::Track");
        auto lPindex = c12.getBankOrder(ldx_Track,"pindex");
        auto lDetector = c12.getBankOrder(ldx_Track,"detector");
        auto lsector = c12.getBankOrder(ldx_Track,"sector");
        auto lq = c12.getBankOrder(ldx_Track,"q");
        auto lchi2 = c12.getBankOrder(ldx_Track,"chi2");
        auto lNDF = c12.getBankOrder(ldx_Track,"NDF");
        // ========================

        // Read banks: Calorimeter
        auto mdx_Calo = c12.addBank("REC::Calorimeter");
        auto mPindex = c12.getBankOrder(mdx_Calo,"pindex");
        auto mDetector = c12.getBankOrder(mdx_Calo,"detector");
        auto msector = c12.getBankOrder(mdx_Calo,"sector");
        auto mLayer = c12.getBankOrder(mdx_Calo,"layer");
        auto menergy = c12.getBankOrder(mdx_Calo,"energy");
        auto mtime = c12.getBankOrder(mdx_Calo,"time");
        auto mpath = c12.getBankOrder(mdx_Calo,"path");
        auto mchi2 = c12.getBankOrder(mdx_Calo,"chi2");
        auto mx = c12.getBankOrder(mdx_Calo,"x");
        auto my = c12.getBankOrder(mdx_Calo,"y");
        auto mz = c12.getBankOrder(mdx_Calo,"z");
        auto mu = c12.getBankOrder(mdx_Calo,"lu");
        auto mv = c12.getBankOrder(mdx_Calo,"lv");
        auto mw = c12.getBankOrder(mdx_Calo,"lw");

        // Read banks: Cherenkov (HTCC)
        auto hdx_Cherenkov = c12.addBank("REC::Cherenkov");
        auto hPindex = c12.getBankOrder(hdx_Cherenkov,"pindex");
        auto hDetector = c12.getBankOrder(hdx_Cherenkov,"detector");
        auto hnphe = c12.getBankOrder(hdx_Cherenkov,"nphe");

        // Read banks: FT
        auto ndx_FT = c12.addBank("REC::ForwardTagger");
        auto nPindex = c12.getBankOrder(ndx_FT,"pindex");
        auto nDetector = c12.getBankOrder(ndx_FT,"detector");
        auto nLayer = c12.getBankOrder(ndx_FT,"layer");
        auto nenergy = c12.getBankOrder(ndx_FT,"energy");
        auto ntime = c12.getBankOrder(ndx_FT,"time");
        auto npath = c12.getBankOrder(ndx_FT,"path");
        auto nchi2 = c12.getBankOrder(ndx_FT,"chi2");
        auto nradius = c12.getBankOrder(ndx_FT,"radius");
        auto nx = c12.getBankOrder(ndx_FT,"x");
        auto ny = c12.getBankOrder(ndx_FT,"y");
        auto nz = c12.getBankOrder(ndx_FT,"z");

        // MC bank
        auto idx_GenPart = c12.addBank("MC::Particle");
        auto iGenPid = c12.getBankOrder(idx_GenPart,"pid");
        auto iGenPx  = c12.getBankOrder(idx_GenPart,"px");
        auto iGenPy  = c12.getBankOrder(idx_GenPart,"py");
        auto iGenPz  = c12.getBankOrder(idx_GenPart,"pz");
        auto iGenVx  = c12.getBankOrder(idx_GenPart,"vx");
        auto iGenVy  = c12.getBankOrder(idx_GenPart,"vy");
        auto iGenVz  = c12.getBankOrder(idx_GenPart,"vz");

      crossRef = 0;

        while(c12.next() == true){

          nmG=0;
          crossRef++;
    
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

          if (nmG>0) T->Fill();

        }

    }

  rFile->Write();
  rFile->Close();

  return 1;
}