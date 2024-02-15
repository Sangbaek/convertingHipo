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

    TString mode = "epebar";
    TString ext = ".root";
    if (argc==2) mode = argv[1];
    std::cout<<"The mode is "<<mode<<"."<<std::endl;


    TFile *rFile = TFile::Open(mode + ext,"RECREATE");
    TTree *T=new TTree("T", mode);

    Float_t beamQ;
    Float_t liveTime;
    Float_t startTime;
    Float_t RFTime;
    Int_t   helicity;
    Int_t   helicityRaw;
    Long_t  EventNum;
    Long_t  RunNum;
    Long_t  TriggerBit;
    Int_t   TriggerPid;

    // =====  proton =====
    Int_t nmb;
    Float_t Ppx[100];
    Float_t Ppy[100];
    Float_t Ppz[100];
    Int_t Pstat[100];

    // ==== electron =====
    Int_t nml;
    Float_t Epx[100];
    Float_t Epy[100];
    Float_t Epz[100];
    Int_t Estat[100];
    Int_t Epa[100];

    // ==== positron =====
    Int_t nmlbar;
    Float_t Ebarpx[100];
    Float_t Ebarpy[100];
    Float_t Ebarpz[100];
    Int_t Ebarstat[100];

    Int_t nma;
    Int_t nmc;

    Int_t  electron_triggered;
    Int_t  positron_triggered;
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
    T->Branch("Epa",&Epa,"Epa[nml]/I");

    // ===============    Positrons ==============    
    T->Branch("nmlbar",&nmlbar,"nmlbar/I");
    T->Branch("Ebarpx",&Ebarpx,"Ebarpx[nmlbar]/F");
    T->Branch("Ebarpy",&Ebarpy,"Ebarpy[nmlbar]/F");
    T->Branch("Ebarstat",&Ebarstat,"Ebarstat[nmlbar]/I");
    T->Branch("Ebarpz",&Ebarpz,"Ebarpz[nmlbar]/F");

    T->Branch("nma",&nma,"nma/I");
    T->Branch("nmc",&nmc,"nmc/I");

    //=================  Logs =============
    T->Branch("beamQ",&beamQ,"beamQ/F");
    T->Branch("liveTime",&liveTime,"liveTime/F");
    T->Branch("startTime",&startTime,"startTime/F");
    T->Branch("RFTime",&RFTime,"RFTime/F");
    T->Branch("helicity",&helicity,"helicity/I");
    T->Branch("helicityRaw",&helicityRaw,"helicityRaw/I");
    T->Branch("EventNum",&EventNum,"EventNum/L");
    T->Branch("RunNum",&RunNum,"RunNum/L");
    T->Branch("TriggerBit",&TriggerBit,"TriggerBit/L");
    T->Branch("TriggerPid",&TriggerPid,"TriggerPid/I");

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

        //  Config Bank
        auto idx_RUNCon = c12.addBank("RUN::config");
        auto brun = c12.getBankOrder(idx_RUNCon,"run");
        auto bevent = c12.getBankOrder(idx_RUNCon,"event");
        auto btrigger = c12.getBankOrder(idx_RUNCon,"trigger");

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

        while(c12.next() == true){

            nml=0;
            nmb=0;
            nmlbar=0;
            electron_triggered = 0;
            positron_triggered = 0;
            nma = c12.getBank(idx_RECPart)->getRows();
            nmc = 0;

            // REC::Particle
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

                if (tStat<0) TriggerPid = c12.getBank(idx_RECPart)->getInt(iPid,ipa);

                if (tCharge != 0) nmc++;

                if( (c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 11  ){  // electrons
                    Epx[nml] = tPx;
                    Epy[nml] = tPy;
                    Epz[nml] = tPz;
                    Estat[nml] = tStat;
                    Epa[nml] = ipa;
                    if (Estat[nml]<0) electron_triggered = 1;
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

                    Ebarpx[nmlbar] = tPx;
                    Ebarpy[nmlbar] = tPy;
                    Ebarpz[nmlbar] = tPz;
                    Ebarstat[nmlbar] = tStat;
                    if (Ebarstat[nmlbar] <0) positron_triggered = 1;

                    nmlbar++;
                } // end of positrons
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


            // Run config bank
            for(auto ipa1 = 0; ipa1<c12.getBank(idx_RUNCon)->getRows();ipa1++){
                auto tempR = c12.getBank(idx_RUNCon)->getInt(brun,ipa1);
                auto tempE = c12.getBank(idx_RUNCon)->getInt(bevent,ipa1);
                auto tempT = c12.getBank(idx_RUNCon)->getLong(btrigger,ipa1);
                
                EventNum = tempE;
                RunNum = tempR;
                TriggerBit = tempT;
            }

            bool condition = (nml*nmb>0) || (nml*nmlbar>0); // if ep or e+e-
            if (condition) T->Fill();

        }

    }

    rFile->Write();
    rFile->Close();

    return 1;
}
