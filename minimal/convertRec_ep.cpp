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
#include <math.h>

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

    TString mode = "ep";
    if (argc==2) mode = argv[1];
    std::cout<<"The mode is "<<mode<<"."<<std::endl;

    TFile *rFile = TFile::Open("recwithgen.root","RECREATE");
    TTree *T=new TTree("T","Rec");

    Float_t beamQ;
    Float_t liveTime;
    Float_t startTime;
    Float_t RFTime;
    Int_t   helicity;
    Int_t   helicityRaw;

    // =====  proton =====
    Int_t nmb;
    Float_t Ppx[100];
    Float_t Ppy[100];
    Float_t Ppz[100];
    Int_t Pstat[100];

    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    // ==== electron =====
    Int_t nml;
    Float_t Epx[100];
    Float_t Epy[100];
    Float_t Epz[100];
    Int_t Estat[100];

    Float_t GenEpx;
    Float_t GenEpy;
    Float_t GenEpz;

    Int_t nmp;
    Int_t nmlbar;
    Int_t nma;
    Int_t nmc;
    Int_t nmLBAR;
    Int_t GenPid[100];

    Int_t  triggered;

    ///   protons ================================== 
    T->Branch("nmb",&nmb,"nmb/I");
    T->Branch("Ppx",&Ppx,"Ppx[nmb]/F");
    T->Branch("Ppy",&Ppy,"Ppy[nmb]/F");
    T->Branch("Ppz",&Ppz,"Ppz[nmb]/F");
    T->Branch("Pstat",&Pstat,"Pstat[nmb]/I");

    // ===============    Electrons ==============    
    T->Branch("nml",&nml,"nml/I");
    T->Branch("Epx",&Epx,"Epx[nml]/F");
    T->Branch("Epy",&Epy,"Epy[nml]/F");
    T->Branch("Epz",&Epz,"Epz[nml]/F");
    T->Branch("Estat",&Estat,"Estat[nml]/I");

    //=================  Logs =============
    T->Branch("beamQ",&beamQ,"beamQ/F");
    T->Branch("liveTime",&liveTime,"liveTime/F");
    T->Branch("startTime",&startTime,"startTime/F");
    T->Branch("RFTime",&RFTime,"RFTime/F");
    T->Branch("helicity",&helicity,"helicity/I");
    T->Branch("helicityRaw",&helicityRaw,"helicityRaw/I");


    // MC bank
    T->Branch("GenEpx",&GenEpx,"GenEpx/F");
    T->Branch("GenEpy",&GenEpy,"GenEpy/F");
    T->Branch("GenEpz",&GenEpz,"GenEpz/F");
    T->Branch("GenPpx",&GenPpx,"GenPpx/F");
    T->Branch("GenPpy",&GenPpy,"GenPpy/F");
    T->Branch("GenPpz",&GenPpz,"GenPpz/F");
    T->Branch("nmp",&nmp,"nmp/I"); 
    T->Branch("GenPid",&GenPid,"GenPid[nmp]/I"); 

    T->Branch("nmlbar",&nmlbar,"nmlbar/I");
    T->Branch("nmLBAR",&nmLBAR,"nmLBAR/I");
    T->Branch("nma",&nma,"nma/I");
    T->Branch("nmc",&nmc,"nmc/I");

    //loop over files
    for(int ifile=0; ifile<chain.GetNFiles();++ifile){
        clas12::clas12reader c12{chain.GetFileName(ifile).Data()};

        //  Event bank
        auto idx_RECEv = c12.addBank("REC::Event");
        auto aBeamQ = c12.getBankOrder(idx_RECEv,"beamCharge");
        auto aLiveT = c12.getBankOrder(idx_RECEv,"liveTime");
        auto aStarT = c12.getBankOrder(idx_RECEv,"startTime");
        auto aRFTim = c12.getBankOrder(idx_RECEv,"RFTime");
        auto aHelic = c12.getBankOrder(idx_RECEv,"helicity");
        auto aHeRaw = c12.getBankOrder(idx_RECEv,"helicityRaw");

        // main particle bank ========
        auto idx_RECPart = c12.addBank("REC::Particle");
        auto iPid = c12.getBankOrder(idx_RECPart,"pid");
        auto iPx  = c12.getBankOrder(idx_RECPart,"px");
        auto iPy  = c12.getBankOrder(idx_RECPart,"py");
        auto iPz  = c12.getBankOrder(idx_RECPart,"pz");
        auto iVx  = c12.getBankOrder(idx_RECPart,"vx");
        auto iVy  = c12.getBankOrder(idx_RECPart,"vy");
        auto iVz  = c12.getBankOrder(idx_RECPart,"vz");
        auto iCharge  = c12.getBankOrder(idx_RECPart,"charge");
        auto iB  = c12.getBankOrder(idx_RECPart,"beta");
        auto iStat = c12.getBankOrder(idx_RECPart,"status");
        auto iChi2pid = c12.getBankOrder(idx_RECPart,"chi2pid");
        //===================

        // MC bank
        auto idx_GenPart = c12.addBank("MC::Particle");
        auto iGenPid = c12.getBankOrder(idx_GenPart,"pid");
        auto iGenPx  = c12.getBankOrder(idx_GenPart,"px");
        auto iGenPy  = c12.getBankOrder(idx_GenPart,"py");
        auto iGenPz  = c12.getBankOrder(idx_GenPart,"pz");
        auto iGenVx  = c12.getBankOrder(idx_GenPart,"vx");
        auto iGenVy  = c12.getBankOrder(idx_GenPart,"vy");
        auto iGenVz  = c12.getBankOrder(idx_GenPart,"vz");

        while(c12.next() == true){

            nml=0;
            nmb=0;
            nmp=0;
            nmlbar=0;
            nmLBAR=0;
            triggered = 0;

            //MC::Particle
            for(auto ipa=0;ipa<c12.getBank(idx_GenPart)->getRows();ipa++){
                auto tGenPx = c12.getBank(idx_GenPart)->getFloat(iGenPx,ipa);
                auto tGenPy = c12.getBank(idx_GenPart)->getFloat(iGenPy,ipa);
                auto tGenPz = c12.getBank(idx_GenPart)->getFloat(iGenPz,ipa);
                auto tGenVx = c12.getBank(idx_GenPart)->getFloat(iGenVx,ipa);
                auto tGenVy = c12.getBank(idx_GenPart)->getFloat(iGenVy,ipa);
                auto tGenVz = c12.getBank(idx_GenPart)->getFloat(iGenVz,ipa);
                auto tGenPid= c12.getBank(idx_GenPart)->getInt(iGenPid,ipa);

                if( tGenPid == 11  ){  // electrons
                    GenEpx = tGenPx;
                    GenEpy = tGenPy;
                    GenEpz = tGenPz;
                }

                if( tGenPid == 2212  ){  // protons
                    GenPpx = tGenPx;
                    GenPpy = tGenPy;
                    GenPpz = tGenPz;
                }
                if( tGenPid == -11  ){  // positrons
                    nmLBAR++;
                }
                GenPid[ipa] = tGenPid;
                nmp++;
            }

            // REC::Particle

            nma = c12.getBank(idx_RECPart)->getRows();
            for(auto ipa=0;ipa<nma;ipa++){

                auto tPx = c12.getBank(idx_RECPart)->getFloat(iPx,ipa);
                auto tPy = c12.getBank(idx_RECPart)->getFloat(iPy,ipa);
                auto tPz = c12.getBank(idx_RECPart)->getFloat(iPz,ipa);
                auto tVx = c12.getBank(idx_RECPart)->getFloat(iVx,ipa);
                auto tVy = c12.getBank(idx_RECPart)->getFloat(iVy,ipa);
                auto tVz = c12.getBank(idx_RECPart)->getFloat(iVz,ipa);
                auto tCharge = c12.getBank(idx_RECPart)->getInt(iCharge,ipa);
                auto tB = c12.getBank(idx_RECPart)->getFloat(iB,ipa);
                auto tStat = c12.getBank(idx_RECPart)->getInt(iStat,ipa);
                auto tChi2pid = c12.getBank(idx_RECPart)->getFloat(iChi2pid,ipa);

                if (tCharge != 0) nmc++;

                if( (c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 11  ){  // electrons
                    Epx[nml] = tPx;
                    Epy[nml] = tPy;
                    Epz[nml] = tPz;
                    Estat[nml] = tStat;
                    if (Estat[nml]<0) triggered = 1;
                    nml++;
                }// end of electrons
                    
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 2212 ){  // protons

                    Ppx[nmb] = tPx;
                    Ppy[nmb] = tPy;
                    Ppz[nmb] = tPz;
                    Pstat[nmb] = tStat;

                    nmb++;
                } // end of protons                    
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == -11 ){  // positrons
                    nmlbar++;
                }
            } //end of REC::Particle

            // event bank ====
            for(auto ipa1 = 0; ipa1<c12.getBank(idx_RECEv)->getRows();ipa1++){
                auto tempB = c12.getBank(idx_RECEv)->getFloat(aBeamQ,ipa1);
                auto tempL = c12.getBank(idx_RECEv)->getDouble(aLiveT,ipa1);
                auto tempS = c12.getBank(idx_RECEv)->getFloat(aStarT,ipa1);
                auto tempR = c12.getBank(idx_RECEv)->getFloat(aRFTim,ipa1);
                auto tempH = c12.getBank(idx_RECEv)->getInt(aHelic,ipa1);
                auto tempHR = c12.getBank(idx_RECEv)->getInt(aHeRaw,ipa1);

                beamQ = tempB;
                liveTime = tempL;
                startTime = tempS;
                RFTime = tempR;
                helicity = tempH;
                helicityRaw = tempHR;
            }

            bool condition = (nmb>0) && (nml>0);
            if (condition) T->Fill();
        }
    }

	rFile->Write();
	rFile->Close();

    return 1;
}