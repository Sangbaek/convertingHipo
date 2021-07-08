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
    if (argc==2) mode = argv[1];
    std::cout<<"The mode is "<<mode<<"."<<std::endl;

    TFile *rFile = TFile::Open("recwithgen.root","RECREATE");
    TTree *T=new TTree("T","Rec");

   // =====  proton =====
    Int_t nmb;
    Float_t Ppx[100];
    Float_t Ppy[100];
    Float_t Ppz[100];
    Float_t Pvz[100];
    Int_t Pstat[100];
    Int_t Psector[100];
    Int_t PPcalSector[100];
    Int_t PFtof1aSector[100];
    Int_t PFtof1aHitx[100];
    Int_t PFtof1aHity[100];
    Int_t PFtof1aHitz[100];
    Int_t PFtof1aTime[100];
    Int_t PFtof1aPath[100];
    Int_t PFtof1bSector[100];
    Int_t PFtof1bHitx[100];
    Int_t PFtof1bHity[100];
    Int_t PFtof1bHitz[100];
    Int_t PFtof1bTime[100];
    Int_t PFtof1bPath[100];
    Int_t PFtof2Sector[100];
    Int_t PFtof2Hitx[100];
    Int_t PFtof2Hity[100];
    Int_t PFtof2Hitz[100];
    Int_t PFtof2Time[100];
    Int_t PFtof2Path[100];
    Int_t PCtofHitx[100];
    Int_t PCtofHity[100];
    Int_t PCtofHitz[100];
    Int_t PCtofTime[100];
    Int_t PCtofPath[100];

    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    // ==== electron =====
    Float_t Epx;
    Float_t Epy;
    Float_t Epz;
    Float_t Evx;
    Float_t Evy;
    Float_t Evz;
    Int_t Estat;
    Int_t Esector;
    
    Float_t GenEpx;
    Float_t GenEpy;
    Float_t GenEpz;
    Float_t GenEvx;
    Float_t GenEvy;
    Float_t GenEvz;
    
    // ==== gammas =====
    Int_t nmg;
    Float_t Gpx[100];
    Float_t Gpy[100];
    Float_t Gpz[100];
    Int_t Gstat[100];
    Int_t Gsector[100];

    Int_t nmG;
    Float_t GenGpx[2];
    Float_t GenGpy[2];
    Float_t GenGpz[2];

    Int_t Before[100];
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
    T->Branch("PPcalSector",&PPcalSector,"PPcalSector[nmb]/I");
    T->Branch("PFtof1aSector",&PFtof1aSector,"PFtof1aSector[nmb]/I");
    T->Branch("PFtof1aHitx",&PFtof1aHitx,"PFtof1aHitx[nmb]/I");
    T->Branch("PFtof1aHity",&PFtof1aHity,"PFtof1aHity[nmb]/I");
    T->Branch("PFtof1aHitz",&PFtof1aHitz,"PFtof1aHitz[nmb]/I");
    T->Branch("PFtof1aTime",&PFtof1aTime,"PFtof1aTime[nmb]/I");
    T->Branch("PFtof1aPath",&PFtof1aPath,"PFtof1aPath[nmb]/I");
    T->Branch("PFtof1bSector",&PFtof1bSector,"PFtof1bSector[nmb]/I");
    T->Branch("PFtof1bHitx",&PFtof1bHitx,"PFtof1bHitx[nmb]/I");
    T->Branch("PFtof1bHity",&PFtof1bHity,"PFtof1bHity[nmb]/I");
    T->Branch("PFtof1bHitz",&PFtof1bHitz,"PFtof1bHitz[nmb]/I");
    T->Branch("PFtof1bTime",&PFtof1bTime,"PFtof1bTime[nmb]/I");
    T->Branch("PFtof1bPath",&PFtof1bPath,"PFtof1bPath[nmb]/I");
    T->Branch("PFtof2Sector",&PFtof2Sector,"PFtof2Sector[nmb]/I");
    T->Branch("PFtof2Hitx",&PFtof2Hitx,"PFtof2Hitx[nmb]/I");
    T->Branch("PFtof2Hity",&PFtof2Hity,"PFtof2Hity[nmb]/I");
    T->Branch("PFtof2Hitz",&PFtof2Hitz,"PFtof2Hitz[nmb]/I");
    T->Branch("PFtof2Time",&PFtof2Time,"PFtof2Time[nmb]/I");
    T->Branch("PFtof2Path",&PFtof2Path,"PFtof2Path[nmb]/I");
    T->Branch("PCtofHitx",&PCtofHitx,"PCtofHitx[nmb]/I");
    T->Branch("PCtofHity",&PCtofHity,"PCtofHity[nmb]/I");
    T->Branch("PCtofHitz",&PCtofHitz,"PCtofHitz[nmb]/I");
    T->Branch("PCtofTime",&PCtofTime,"PCtofTime[nmb]/I");
    T->Branch("PCtofPath",&PCtofPath,"PCtofPath[nmb]/I");


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

// MC bank
    T->Branch("GenEpx",&GenEpx,"GenEpx/F");
    T->Branch("GenEpy",&GenEpy,"GenEpy/F");
    T->Branch("GenEpz",&GenEpz,"GenEpz/F");
    T->Branch("GenEvx",&GenEvx,"GenEvx/F");
    T->Branch("GenEvy",&GenEvy,"GenEvy/F");
    T->Branch("GenEvz",&GenEvz,"GenEvz/F");
    T->Branch("GenPpx",&GenPpx,"GenPpx/F");
    T->Branch("GenPpy",&GenPpy,"GenPpy/F");
    T->Branch("GenPpz",&GenPpz,"GenPpz/F");
    T->Branch("nmG", &nmG, "nmG/I");
    T->Branch("GenGpx",&GenGpx,"GenGpx[nmG]/F");
    T->Branch("GenGpy",&GenGpy,"GenGpy[nmG]/F");
    T->Branch("GenGpz",&GenGpz,"GenGpz[nmG]/F");
 
    //
    //loop over files
    //
    for(int ifile=0; ifile<chain.GetNFiles();++ifile){
        clas12::clas12reader c12{chain.GetFileName(ifile).Data()};


// main particle bank ========
    	auto idx_RECPart = c12.addBank("REC::Particle");
       	auto iPid = c12.getBankOrder(idx_RECPart,"pid");
    	auto iPx  = c12.getBankOrder(idx_RECPart,"px");
    	auto iPy  = c12.getBankOrder(idx_RECPart,"py");
       	auto iPz  = c12.getBankOrder(idx_RECPart,"pz");
        auto iVx  = c12.getBankOrder(idx_RECPart,"vx");
        auto iVy  = c12.getBankOrder(idx_RECPart,"vy");
        auto iVz  = c12.getBankOrder(idx_RECPart,"vz");
        auto iStat = c12.getBankOrder(idx_RECPart,"status");
//===================


//  Filter bank created by Sangbaek
    	auto idx_FILTER = c12.addBank("FILTER::Index");
        auto iInd = c12.getBankOrder(idx_FILTER,"before");
    	auto iPcalSector = c12.getBankOrder(idx_FILTER, "pcal_sector");
    	auto iFtof1aSector = c12.getBankOrder(idx_FILTER, "ftof1a_sector");
    	auto iFtof1bSector = c12.getBankOrder(idx_FILTER, "ftof1b_sector");
    	auto iFtof2Sector = c12.getBankOrder(idx_FILTER, "ftof2_sector");
//=========

// Scintillator bank
    auto idx_RECScint = c12.addBank("REC::Scintillator");
    auto jPnd = c12.getBankOrder(idx_RECScint,"pindex");
    auto jDet = c12.getBankOrder(idx_RECScint,"detector");
    auto jSec = c12.getBankOrder(idx_RECScint,"sector");
    auto jLay = c12.getBankOrder(idx_RECScint,"layer");
    auto jTim = c12.getBankOrder(idx_RECScint,"time");
    auto jPat = c12.getBankOrder(idx_RECScint,"path");
    auto jX   = c12.getBankOrder(idx_RECScint,"x");
    auto jY = c12.getBankOrder(idx_RECScint,"y");
    auto jZ = c12.getBankOrder(idx_RECScint,"z");


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
		
	        nmb=0;
        	nmg=0;
    		nmG=0;

            for(auto ipa = 0;ipa<c12.getBank(idx_FILTER)->getRows();ipa++){
               auto val = c12.getBank(idx_FILTER)->getInt(iInd,ipa);
               auto tempPcalSector = c12.getBank(idx_FILTER)->getInt(iPcalSector,ipa);
               auto tempFtof1aSector = c12.getBank(idx_FILTER)->getInt(iFtof1aSector,ipa);
               auto tempFtof1bSector = c12.getBank(idx_FILTER)->getInt(iFtof1bSector,ipa);
               auto tempFtof2Sector = c12.getBank(idx_FILTER)->getInt(iFtof2Sector,ipa);
               Before[ipa] = val;
               PcalSector[ipa] = tempPcalSector;
               Ftof1aSector[ipa] = tempFtof1aSector;
               Ftof1bSector[ipa] = tempFtof1bSector;
               Ftof2Sector[ipa] = tempFtof2Sector;
            }

        	for(auto ipa=0;ipa<c12.getBank(idx_GenPart)->getRows();ipa++){
                
            	auto tGenPx = c12.getBank(idx_GenPart)->getFloat(iGenPx,ipa);
            	auto tGenPy = c12.getBank(idx_GenPart)->getFloat(iGenPy,ipa);
            	auto tGenPz = c12.getBank(idx_GenPart)->getFloat(iGenPz,ipa);
                auto tGenVx = c12.getBank(idx_GenPart)->getFloat(iGenVx,ipa);
                auto tGenVy = c12.getBank(idx_GenPart)->getFloat(iGenVy,ipa);
                auto tGenVz = c12.getBank(idx_GenPart)->getFloat(iGenVz,ipa);
 
            	if( (c12.getBank(idx_GenPart)->getInt(iGenPid,ipa)) == 11  ){  // electrons
    				GenEpx = tGenPx;
    				GenEpy = tGenPy;
    				GenEpz = tGenPz;
                    GenEvx = tGenVx;
                    GenEvy = tGenVy;
                    GenEvz = tGenVz;
            	}
                
                if((c12.getBank(idx_GenPart)->getInt(iGenPid,ipa)) == 2212  ){  // protons
            		GenPpx = tGenPx;
            		GenPpy = tGenPy;
            		GenPpz = tGenPz;
            	}
                    
            	if((c12.getBank(idx_GenPart)->getInt(iGenPid,ipa)) == 22  ){  // photons
            		GenGpx[nmG] = tGenPx;
            		GenGpy[nmG] = tGenPy;
            		GenGpz[nmG] = tGenPz;
				    nmG++;
                }
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
                
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 2212 ){  // protons
         
            		Ppx[nmb] = tPx;
            		Ppy[nmb] = tPy;
            		Ppz[nmb] = tPz;
                    Pvz[nmb] = tVz;
    				Pstat[nmb] = tStat;
    				if (Pstat[nmb] >4000) Psector[nmb] = Pstat[nmb];
    				else if (Ftof1aSector[ipa]>0) Psector[nmb] = Ftof1aSector[ipa];	
    				else if (Ftof1bSector[ipa]>0) Psector[nmb] = Ftof1bSector[ipa];	
    				else if (Ftof2Sector[ipa]>0) Psector[nmb] = Ftof2Sector[ipa];	
                    PPcalSector[nmb] = PcalSector[ipa];
                    PFtof1aSector[nmb] = Ftof1aSector[ipa];
                    PFtof1bSector[nmb] = Ftof1bSector[ipa];
                    PFtof2Sector[nmb] = Ftof2Sector[ipa];

                    // Scintillaror Bank        //
                    for(auto ipa1 = 0; ipa1<c12.getBank(idx_RECScint)->getRows();ipa1++){

                        auto tempPnd = c12.getBank(idx_RECScint)->getInt(jPnd,ipa1);
                        auto tempDet = c12.getBank(idx_RECScint)->getInt(jDet,ipa1);    
                        auto tempLay = c12.getBank(idx_RECScint)->getInt(jLay,ipa1); 
                        auto tempTim = c12.getBank(idx_RECScint)->getFloat(jTim,ipa1); 
                        auto tempPat = c12.getBank(idx_RECScint)->getFloat(jPat,ipa1); 
                        auto tempX= c12.getBank(idx_RECScint)->getFloat(jX,ipa1); 
                        auto tempY = c12.getBank(idx_RECScint)->getFloat(jY,ipa1); 
                        auto tempZ = c12.getBank(idx_RECScint)->getFloat(jZ,ipa1);

                        if (tempPnd == Before[ipa]){

                            if (tempDet == 12 ){// ftof{
                                if (tempLay == 1){
                                    PFtof1aHitx[nmb] = tempX;
                                    PFtof1aHity[nmb] = tempY;
                                    PFtof1aHitz[nmb] = tempZ;
                                    PFtof1aTime[nmb] = tempTim;
                                    PFtof1aPath[nmb] = tempPat;
                                }

                                if (tempLay == 2){
                                    PFtof1bHitx[nmb] = tempX;
                                    PFtof1bHity[nmb] = tempY;
                                    PFtof1bHitz[nmb] = tempZ;
                                    PFtof1bTime[nmb] = tempTim;
                                    PFtof1bPath[nmb] = tempPat;
                                }

                                if (tempLay == 3){
                                    PFtof2Hitx[nmb] = tempX;
                                    PFtof2Hity[nmb] = tempY;
                                    PFtof2Hitz[nmb] = tempZ;
                                    PFtof2Time[nmb] = tempTim;
                                    PFtof2Path[nmb] = tempPat;
                                }
                            }
                            if (tempDet == 4 ){// ctof{
                                PCtofHitx[nmb] = tempX
                                PCtofHity[nmb] = tempY
                                PCtofHitz[nmb] = tempZ
                                PCtofTime[nmb] = tempTim
                                PCtofPath[nmb] = tempPat
                            }

                        }
                    }
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

            bool condition = (nmb>0) && (nmg>0) && (nmG>0);
            if (mode == "pi0") condition = (nmb>0) && (nmg>1) && (nmG>0);
            if (condition) T->Fill();
        }

    }

	rFile->Write();
	rFile->Close();

    return 1;
}
