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

    TString mode = "pi0";
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

   // =====  proton =====
    Int_t nmb;
    Float_t Ppx[100];
    Float_t Ppy[100];
    Float_t Ppz[100];
    Float_t Pvz[100];
    Int_t Pstat[100];
    Int_t Psector[100];

    // ==== electron =====
    Float_t Epx;
    Float_t Epy;
    Float_t Epz;
    Float_t Evx;
    Float_t Evy;
    Float_t Evz;
    Int_t Estat;
    Int_t Esector;
    // ==== gammas =====
    Int_t nmg;
    Float_t Gpx[100];
    Float_t Gpy[100];
    Float_t Gpz[100];
    Int_t Gstat[100];
    Int_t Gsector[100];

    Int_t PcalSector[100];
    Int_t Ftof1aSector[100];
    Int_t Ftof1bSector[100];
    Int_t Ftof2Sector[100];

 ///   protons ================================== 
    T->Branch("nmb",&nmb,"nmb/I");
    T->Branch("Ppx",&Ppx,"Ppx[nmb]/F");
    T->Branch("Ppy",&Ppy,"Ppy[nmb]/F");
    T->Branch("Ppz",&Ppz,"Ppz[nmb]/F");
    T->Branch("Pvz",&Pvz,"Pvz[nmb]/F");
    T->Branch("Pstat",&Pstat,"Pstat[nmb]/I");
    T->Branch("Psector",&Psector,"Psector[nmb]/I");


// ===============    Electrons ==============    
    T->Branch("Epx",&Epx,"Epx/F");
    T->Branch("Epy",&Epy,"Epy/F");
    T->Branch("Epz",&Epz,"Epz/F");
    T->Branch("Evx",&Evx,"Evx/F");
    T->Branch("Evy",&Evy,"Evy/F");
    T->Branch("Evz",&Evz,"Evz/F");
    T->Branch("Estat",&Estat,"Estat/I");
    T->Branch("Esector",&Esector,"Esector/I");

// ================   Gamma  ===============    
    T->Branch("nmg",&nmg,"nmg/I");
    T->Branch("Gpx",&Gpx,"Gpx[nmg]/F");
    T->Branch("Gpy",&Gpy,"Gpy[nmg]/F");
    T->Branch("Gpz",&Gpz,"Gpz[nmg]/F");
    T->Branch("Gstat",&Gstat,"Gstat[nmg]/I");
    T->Branch("Gsector",&Gsector,"Gsector[nmg]/I");
//=================  
//

     T->Branch("beamQ",&beamQ,"beamQ/F");
     T->Branch("liveTime",&liveTime,"liveTime/F");
     T->Branch("startTime",&startTime,"startTime/F");
     T->Branch("RFTime",&RFTime,"RFTime/F");
     T->Branch("helicity",&helicity,"helicity/I");
     T->Branch("helicityRaw",&helicityRaw,"helicityRaw/I");
     T->Branch("EventNum",&EventNum,"EventNum/L");
     T->Branch("RunNum",&RunNum,"RunNum/L");

    //
    //loop over files
    //
    for(int ifile=0; ifile<chain.GetNFiles();++ifile){
        clas12::clas12reader c12{chain.GetFileName(ifile).Data()};


//  Event bank
//

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



// main particle bank ========
        auto idx_RECPart = c12.addBank("REC::Particle");
        auto iPid = c12.getBankOrder(idx_RECPart,"pid");
        auto iPx  = c12.getBankOrder(idx_RECPart,"px");
        auto iPy  = c12.getBankOrder(idx_RECPart,"py");
        auto iPz  = c12.getBankOrder(idx_RECPart,"pz");
        auto iVx  = c12.getBankOrder(idx_RECPart,"vx");
        auto iVy  = c12.getBankOrder(idx_RECPart,"vy");
        auto iVz  = c12.getBankOrder(idx_RECPart,"vz");
        auto iB  = c12.getBankOrder(idx_RECPart,"beta");
        auto iStat = c12.getBankOrder(idx_RECPart,"status");
//===================


//  Filter bank created by Sangbaek
        auto idx_FILTER = c12.addBank("FILTER::Index");
        auto iPcalSector = c12.getBankOrder(idx_FILTER, "pcal_sector");
        auto iFtof1aSector = c12.getBankOrder(idx_FILTER, "ftof1a_sector");
        auto iFtof1bSector = c12.getBankOrder(idx_FILTER, "ftof1b_sector");
        auto iFtof2Sector = c12.getBankOrder(idx_FILTER, "ftof2_sector");
//=========

        while(c12.next() == true){
        
            nmb=0;
            nmg=0;

            for(auto ipa = 0;ipa<c12.getBank(idx_FILTER)->getRows();ipa++){
                auto tempPcalSector = c12.getBank(idx_FILTER)->getInt(iPcalSector,ipa);
                auto tempFtof1aSector = c12.getBank(idx_FILTER)->getInt(iFtof1aSector,ipa);
                auto tempFtof1bSector = c12.getBank(idx_FILTER)->getInt(iFtof1bSector,ipa);
                auto tempFtof2Sector = c12.getBank(idx_FILTER)->getInt(iFtof2Sector,ipa);
                PcalSector[ipa] = tempPcalSector;
                Ftof1aSector[ipa] = tempFtof1aSector;
                Ftof1bSector[ipa] = tempFtof1bSector;
                Ftof2Sector[ipa] = tempFtof2Sector;
            }

            for(auto ipa=0;ipa<c12.getBank(idx_RECPart)->getRows();ipa++){
            
                auto tPx = c12.getBank(idx_RECPart)->getFloat(iPx,ipa);
                auto tPy = c12.getBank(idx_RECPart)->getFloat(iPy,ipa);
                auto tPz = c12.getBank(idx_RECPart)->getFloat(iPz,ipa);
                auto tVx = c12.getBank(idx_RECPart)->getFloat(iVx,ipa);
                auto tVy = c12.getBank(idx_RECPart)->getFloat(iVy,ipa);
                auto tVz = c12.getBank(idx_RECPart)->getFloat(iVz,ipa);
                auto tStat = c12.getBank(idx_RECPart)->getInt(iStat,ipa);

 
                if( (c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 11  ){  // electrons
                    Epx = tPx;
                    Epy = tPy;
                    Epz = tPz;
                    Evx = tVx;
                    Evy = tVy;
                    Evz = tVz;
                    Esector = PcalSector[ipa];
                }
                
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 2212 ){  // protons, FD
             
                    Ppx[nmb] = tPx;
                    Ppy[nmb] = tPy;
                    Ppz[nmb] = tPz;
                    Pvz[nmb] = tVz;
                    Pstat[nmb] = tStat;
                    if (Pstat[nmb] >4000) Psector[nmb] = Pstat[nmb];
                    else if (Ftof1aSector[ipa]>0) Psector[nmb] = Ftof1aSector[ipa]; 
                    else if (Ftof1bSector[ipa]>0) Psector[nmb] = Ftof1bSector[ipa]; 
                    else if (Ftof2Sector[ipa]>0) Psector[nmb] = Ftof2Sector[ipa];   
                    nmb++;
                    
                } // if for protons
                    
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 22  ){  // photons

                    Gpx[nmg] = tPx;
                    Gpy[nmg] = tPy;
                    Gpz[nmg] = tPz;
                    Gstat[nmg] = tStat;
                    if (Gstat[nmg]<2000) Gsector[nmg] = Gstat[nmg];
                    else Gsector[nmg] = PcalSector[ipa];
                    nmg++;
                    
                }
            }


// event bank ====
//
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
                
                EventNum = tempE;
                RunNum = tempR;
            }

            bool condition = (nmb>0) && (nmg>0);
            if (mode == "pi0") condition = nmb>0 && nmg>1;
            if (condition) T->Fill();

        }

    }

    rFile->Write();
    rFile->Close();

    return 1;
}
