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

    TLorentzVector p4_proton[100];
    TLorentzVector p4_electron;
    TLorentzVector p4_gamma[100];
    TLorentzVector p4_pi0;
    TLorentzVector p4_beam;
    TLorentzVector p4_target;
    
    p4_beam.SetXYZM(0,0,10.604,0.5109989461 * 0.001);
    p4_target.SetXYZM(0,0,0,0.938272081);
    
    TFile *rFile = TFile::Open("recwithgen.root","RECREATE");
    TTree *T=new TTree("T","Rec");


    // Define variables

    Float_t mp  =0.938272081;
    // === beam ======
    // incoming Beam energy
   Float_t Q2;
   Float_t Nu;
   Float_t xB;
   Float_t t[100];
   Float_t q;
   Float_t qx;
   Float_t qy;
   Float_t qz;
   Float_t W2;
//   Event and run parameters

	Float_t beamQ;
	Float_t liveTime;
	Float_t startTime;
	Float_t RFTime;
	Int_t   helicity;
	Int_t   helicityRaw;
	Long_t  EventNum;
	Long_t  RunNum;
// Physics quantities
//
//
    Int_t combint;
    Float_t meG[1000] ;
    Float_t meP[1000] ;
    Float_t me[1000]  ;
    Float_t tE[1000]  ;
    Float_t mmG[1000] ;
    Float_t mm[1000]  ;
    Float_t mmP[1000] ;
    Float_t Mpx[1000] ;
    Float_t Mpy[1000] ;
    Float_t Mpz[1000] ;
    Float_t Mp[1000]  ;
    Float_t mGpx[1000];
    Float_t mGpy[1000];
    Float_t mGpz[1000];
    Float_t mGp[1000];
    Int_t pIndex[1000];
    Int_t gIndex[1000]; 
    Float_t theta1[1000];
    Float_t theta2[1000];
    Float_t trento[1000];
    Float_t trento2[1000];

   // =====  proton =====
    Int_t nmb;
    Float_t Pp[100];
    Float_t Ppx[100];
    Float_t Ppy[100];
    Float_t Ppz[100];
    Float_t Ptheta[100];
    Float_t Pphi[100];
    Float_t Pvx[100];
    Float_t Pvy[100];
    Float_t Pvz[100];
    Float_t Pvt[100];
    Float_t Pbeta[100];
    Int_t Pstat[100];
    Int_t PorigIndx[100];
    Int_t Psector[100];

    Float_t GenPpx;
    Float_t GenPpy;
    Float_t GenPpz;
    // ==== electron =====
    Float_t Ep;
    Float_t Epx;
    Float_t Epy;
    Float_t Epz;
    Float_t Etheta;
    Float_t Ephi;
    Float_t Evx;
    Float_t Evy;
    Float_t Evz;
    Float_t Evt;
    Float_t Ebeta;
    Int_t Estat;
    Int_t EorigIndx;
    Int_t Esector;
    
    Float_t GenEpx;
    Float_t GenEpy;
    Float_t GenEpz;
    Float_t GenEvx;
    Float_t GenEvy;
    Float_t GenEvz;
    
    // ==== gammas =====
    Int_t nmg;
    Float_t Gp[100];
    Float_t Gpx[100];
    Float_t Gpy[100];
    Float_t Gpz[100];
//    Float_t Gtheta[100];
//    Float_t Gphi[100];
    Float_t Gvx[100];
    Float_t Gvy[100];
    Float_t Gvz[100];
    Float_t Gvt[100];
    Float_t Gbeta[100];
    Int_t Gstat[100];
    Int_t GorigIndx[100];
    Int_t Gsector[100];

    Int_t nmG;
    Float_t GenGpx[100];
    Float_t GenGpy[100];
    Float_t GenGpz[100];

vector<Int_t> vScInd;
vector<Int_t> vScPnd;
vector<Int_t> vScDet;
vector<Int_t> vScSet;
vector<Int_t> vScLay;
vector<Int_t> vScCom;
vector<Double_t> vScEne;
vector<Double_t> vScTim;
vector<Double_t> vScPat;
vector<Double_t> vScX;
vector<Double_t> vScY;
vector<Double_t> vScZ;
vector<Int_t> vScStat;

 
    //===========   additional missing masses ======
   Int_t Before[100];
   Int_t PcalSector[100];
   Int_t Ftof1aSector[100];
   Int_t Ftof1bSector[100];
   Int_t Ftof2Sector[100];

    //=========== Tree branches ===============

    
   
 ///   protons ================================== 
    T->Branch("nmb",&nmb,"nmb/I");
    T->Branch("Pp",&Pp,"Pp[nmb]/F");
    T->Branch("Ppx",&Ppx,"Ppx[nmb]/F");
    T->Branch("Ppy",&Ppy,"Ppy[nmb]/F");
    T->Branch("Ppz",&Ppz,"Ppz[nmb]/F");
    T->Branch("Ptheta",&Ptheta,"Ptheta[nmb]/F");
    T->Branch("Pphi",&Pphi,"Pphi[nmb]/F");
    T->Branch("Ptime",&Ptime,"Ptime[nmb]/F");
    T->Branch("Pvx",&Pvx,"Pvx[nmb]/F");
    T->Branch("Pvy",&Pvy,"Pvy[nmb]/F");
    T->Branch("Pvz",&Pvz,"Pvz[nmb]/F");
    T->Branch("Pvt",&Pvy,"Pvt[nmb]/F");
    T->Branch("Pbeta",&Pbeta,"Pbeta[nmb]/F");
    T->Branch("Pstat",&Pstat,"Pstat[nmb]/I");
    T->Branch("PorigIndx",&PorigIndx,"PorigIndx[nmb]/I");
    T->Branch("Psector",&Psector,"Psector[nmb]/I");


// ===============    Electrons ==============    
    T->Branch("Ep",&Ep,"Ep/F");
    T->Branch("Epx",&Epx,"Epx/F");
    T->Branch("Epy",&Epy,"Epy/F");
    T->Branch("Epz",&Epz,"Epz/F");
    T->Branch("Etheta",&Etheta,"Etheta/F");
    T->Branch("Ephi",&Ephi,"Ephi/F");
    T->Branch("Etime",&Etime,"Etime/F");
    T->Branch("Evx",&Evx,"Evx/F");
    T->Branch("Evy",&Evy,"Evy/F");
    T->Branch("Evz",&Evz,"Evz/F");
    T->Branch("Evt",&Evy,"Evt/F");
    T->Branch("Ebeta",&Ebeta,"Ebeta/F");
    T->Branch("Estat",&Estat,"Estat/I");
    T->Branch("EorigIndx",&EorigIndx,"EorigIndx/I");
    T->Branch("Esector",&Esector,"Esector/I");


// ================   Gamma  ===============    
    T->Branch("nmg",&nmg,"nmg/I");
    T->Branch("Gp",&Gp,"Gp[nmg]/F");
    T->Branch("Gpx",&Gpx,"Gpx[nmg]/F");
    T->Branch("Gpy",&Gpy,"Gpy[nmg]/F");
    T->Branch("Gpz",&Gpz,"Gpz[nmg]/F");
    T->Branch("Gtheta",&Gtheta,"Gtheta[nmg]/F");
    T->Branch("Gphi",&Gphi,"Gphi[nmg]/F");
    T->Branch("Gtime",&Gtime,"Gtime[nmg]/F");
    T->Branch("Gvx",&Gvx,"Gvx[nmg]/F");
    T->Branch("Gvy",&Gvy,"Gvy[nmg]/F");
    T->Branch("Gvz",&Gvz,"Gvz[nmg]/F");
    T->Branch("Gvt",&Gvy,"Gvt[nmg]/F");
    T->Branch("Gbeta",&Gbeta,"Gbeta[nmg]/F");
    T->Branch("Gstat",&Gstat,"Gstat[nmg]/I");
    T->Branch("GorigIndx",&GorigIndx,"GorigIndx[nmg]/I");
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

    // Define Q2, omega, xB, -t etc ...
    T->Branch("Q2",&Q2,"Q2/F");
    T->Branch("Nu",&Nu,"Nu/F");
    T->Branch("q",&q,"q/F");
    T->Branch("qx",&qx,"qx/F");
    T->Branch("qy",&qy,"qy/F");
    T->Branch("qz",&qz,"qz/F");
    T->Branch("W2",&W2,"W2/F");
    T->Branch("xB",&xB,"xB/F");
    T->Branch("t",&t,"t[nmb]/F");

    T->Branch("combint",&combint,"combint/I");
    T->Branch("meG",&meG,"meG[combint]/F");
    T->Branch("meP", &meP,"meP[combint]/F");
    T->Branch("me", &me,"me[combint]/F");
    T->Branch("tE",&tE,"tE[combint]/F");
    T->Branch("mmG",&mmG,"mmG[combint]/F");
    T->Branch("mm",&mm,"mm[combint]/F");
    T->Branch("mmP",&mmP,"mmP[combint]/F");
    T->Branch("Mpx",&Mpx,"Mpx[combint]/F");
    T->Branch("Mpy",&Mpy,"Mpy[combint]/F");
    T->Branch("Mpz",&Mpz,"Mpz[combint]/F");
    T->Branch("Mp",&Mp,"Mp[combint]/F");
    T->Branch("mGpx",&mGpx,"mGpx[combint]/F");
    T->Branch("mGpy",&mGpy,"mGpy[combint]/F");
    T->Branch("mGpz",&mGpz,"mGpz[combint]/F");
    T->Branch("mGp",&mGp,"mGp[combint]/F");
    T->Branch("pIndex",&pIndex,"pIndex[combint]/I");
    T->Branch("gIndex",&gIndex,"gIndex[combint]/I");
    T->Branch("trento",&trento,"trento[combint]/F");
    T->Branch("trento2",&trento2,"trento[combint]/F");
    T->Branch("theta1",&theta1,"theta1[combint]/F");
    T->Branch("theta2",&theta2,"theta2[combint]/F");

/*
//  =====  Scintillator branching ======

    T->Branch("ScInd",&vScInd);
      T->Branch("ScPnd",&vScPnd);
      T->Branch("ScDet",&vScDet);
      T->Branch("ScSet",&vScSet);
      T->Branch("ScLay",&vScLay);
      T->Branch("ScCom",&vScCom);
      T->Branch("ScEne",&vScEne);
      T->Branch("ScTim",&vScTim);
      T->Branch("ScPat",&vScPat);
      T->Branch("ScX",&vScX);
      T->Branch("ScY",&vScY);
      T->Branch("ScZ",&vScZ);
      T->Branch("ScStat",&vScStat);
*/
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
 
    TLorentzVector vgs;
    TLorentzVector vmP;
    TLorentzVector vmG;
    TLorentzVector vM;



    TVector3 v1;
    TVector3 v2;
    TVector3 Vlept;
    TVector3 Vhadr;
    TVector3 Vhadr2;
    TVector3 vtemp1;
    TVector3 vtemp2;
    TVector3 v3l;
    TVector3 v3h;
    
    
    
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
    	auto iVt  = c12.getBankOrder(idx_RECPart,"vt");
    	auto iCh  = c12.getBankOrder(idx_RECPart,"charge");
    	auto iB  = c12.getBankOrder(idx_RECPart,"beta");
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


// Read banks: with DC, CVT, FTOF, LTCC, HTCC, ECAL, CTOF, CND 
/*	auto idx_Traj = c12.addBank("REC::Traj");
	auto iPindex = c12.getBankOrder(idx_Traj,"pindex");
	auto iDetector = c12.getBankOrder(idx_Traj,"detector");
	auto iLayer = c12.getBankOrder(idx_Traj,"layer");
	auto iX = c12.getBankOrder(idx_Traj,"x");
        auto iY = c12.getBankOrder(idx_Traj,"y");
        auto iZ = c12.getBankOrder(idx_Traj,"z");
// ========================

// Scintillator bank
	auto idx_RECScint = c12.addBank("REC::Scintillator");
	auto jInd = c12.getBankOrder(idx_RECScint,"index");
	auto jPnd = c12.getBankOrder(idx_RECScint,"pindex");
	auto jDet = c12.getBankOrder(idx_RECScint,"detector");
	auto jSec = c12.getBankOrder(idx_RECScint,"sector");
	auto jLay = c12.getBankOrder(idx_RECScint,"layer");
	auto jCom = c12.getBankOrder(idx_RECScint,"component");
	auto jEne = c12.getBankOrder(idx_RECScint,"energy");
	auto jTim = c12.getBankOrder(idx_RECScint,"time");
	auto jPat = c12.getBankOrder(idx_RECScint,"path");
	auto jX   = c12.getBankOrder(idx_RECScint,"x");
	auto jY = c12.getBankOrder(idx_RECScint,"y");
	auto jZ = c12.getBankOrder(idx_RECScint,"z");
	auto jStat = c12.getBankOrder(idx_RECScint,"status");
*/

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
            /*
            		vScInd.clear();
            		vScPnd.clear();
            		vScDet.clear();
            		vScSet.clear();
            		vScLay.clear();
            		vScCom.clear();
            		vScEne.clear();
            		vScTim.clear();
            		vScPat.clear();
            		vScX.clear();
            		vScY.clear();
            		vScZ.clear();
            		vScStat.clear();
            */
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
            	} // if for protons
                    
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
    			auto tVt = c12.getBank(idx_RECPart)->getFloat(iVt,ipa);
    			auto tB = c12.getBank(idx_RECPart)->getFloat(iB,ipa);
    			auto tStat = c12.getBank(idx_RECPart)->getInt(iStat,ipa);

 
            	if( (c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 11  ){  // electrons
            		p4_electron.SetXYZM(tPx,tPy,tPz,0.5109989461 * 0.001);
    				Ep = p4_electron.P();
    				Epx = p4_electron.Px();
    				Epy = p4_electron.Py();
    				Epz = p4_electron.Pz();
    				Etheta = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
    				Ephi   = TMath::ATan2(Epy,Epx);
    				Evx = tVx;
    				Evy = tVy;
    				Evz = tVz;
    				Evt = tVt;
    				Ebeta = tB;

    				EorigIndx = Before[ipa];  // Original row index before skiming 
    				Esector = PcalSector[ipa];
            	}
                
                if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 2212  ){  // protons
             
        	    	p4_proton[nmb].SetXYZM(tPx,tPy,tPz,0.938272081);
	            	Pp[nmb] = p4_proton[nmb].P();
            		Ppx[nmb] = p4_proton[nmb].Px();
            		Ppy[nmb] = p4_proton[nmb].Py();
            		Ppz[nmb] = p4_proton[nmb].Pz();
               		Ptheta[nmb] = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
               		Pphi[nmb]   = TMath::ATan2(tPy,tPx);
    				Pvx[nmb] = tVx;
    				Pvy[nmb] = tVy;
    				Pvz[nmb] = tVz;
    				Pvt[nmb] = tVt;
    				Pbeta[nmb] = tB;
    				Pstat[nmb] = tStat;
		    		int status = tStat;

                    PorigIndx[nmb] = Before[ipa];  // Original row index before skiming 
    				if (Pstat[nmb] >4000) Psector[nmb] = Pstat[nmb];
    				else if (Ftof1aSector[ipa]>0) Psector[nmb] = Ftof1aSector[ipa];	
    				else if (Ftof1bSector[ipa]>0) Psector[nmb] = Ftof1bSector[ipa];	
    				else if (Ftof2Sector[ipa]>0) Psector[nmb] = Ftof2Sector[ipa];	


               		nmb++;
                    
            	} // if for protons
                    
            	if((c12.getBank(idx_RECPart)->getInt(iPid,ipa)) == 22  ){  // photons

            		p4_gamma[nmg].SetXYZM(tPx,tPy,tPz,0);
            		Gp[nmg] = p4_gamma[nmg].P();
            		Gpx[nmg] = p4_gamma[nmg].Px();
            		Gpy[nmg] = p4_gamma[nmg].Py();
            		Gpz[nmg] = p4_gamma[nmg].Pz();
               		Gtheta[nmg] = TMath::ATan2( TMath::Sqrt(tPx*tPx + tPy*tPy), tPz);
               		Gphi[nmg]   = TMath::ATan2(tPy,tPx);
                    Gvx[nmg] = tVx;
                    Gvy[nmg] = tVy;
                    Gvz[nmg] = tVz;
                    Gvt[nmg] = tVt;
                    Gbeta[nmg] = tB;
                    Gstat[nmg] = tStat;

                    GorigIndx[nmg] = Before[ipa];  // Original row index before skiming 
    				if (Gstat[nmg]<2000) Gsector[nmg] = Gstat[nmg];
    				else Gsector[nmg] = PcalSector[ipa];

            		nmg++;
                    
            	}
        	}


/*
// Scintillaror Bank 		//
    		for(auto ipa1 = 0; ipa1<c12.getBank(idx_RECScint)->getRows();ipa1++){

    			auto tempInd = c12.getBank(idx_RECScint)->getInt(jInd,ipa1);
    			auto tempPnd = c12.getBank(idx_RECScint)->getInt(jPnd,ipa1);
    			auto tempDet = c12.getBank(idx_RECScint)->getInt(jDet,ipa1); 	
    			auto tempSec = c12.getBank(idx_RECScint)->getInt(jSec,ipa1); 
    			auto tempLay = c12.getBank(idx_RECScint)->getInt(jLay,ipa1); 
    			auto tempCom = c12.getBank(idx_RECScint)->getInt(jCom,ipa1); 
    			auto tempEne = c12.getBank(idx_RECScint)->getFloat(jEne,ipa1);
    			auto tempTim = c12.getBank(idx_RECScint)->getFloat(jTim,ipa1); 
    			auto tempPat = c12.getBank(idx_RECScint)->getFloat(jPat,ipa1); 
    			auto tempX= c12.getBank(idx_RECScint)->getFloat(jX,ipa1); 
    			auto tempY = c12.getBank(idx_RECScint)->getFloat(jY,ipa1); 
    			auto tempZ = c12.getBank(idx_RECScint)->getFloat(jZ,ipa1);
    			auto tempStat = c12.getBank(idx_RECScint)->getInt(jStat,ipa1);

                vScInd.push_back(tempInd);
    			vScPnd.push_back(tempPnd);
    			vScDet.push_back(tempDet);
    			vScSet.push_back(tempSec);
    			vScLay.push_back(tempLay);
    			vScCom.push_back(tempCom);
    			vScEne.push_back(tempEne);
    			vScTim.push_back(tempTim);
    			vScPat.push_back(tempPat);
    			vScX.push_back(tempX);
    			vScY.push_back(tempY);
    			vScZ.push_back(tempZ);
    			vScStat.push_back(tempStat);
    		}// scintillator bank 
    */

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
    // Physics quantities
    		vgs = p4_beam - p4_electron;
    		Q2 = -vgs.M2();
    		Nu = vgs.E();
    		xB = Q2/(2*0.938272081*Nu);
    		W2 = (p4_beam + p4_target - p4_electron).M2();
    		qx = vgs.X();
    		qy = vgs.Y();
    		qz = vgs.Z();
            q = TMath::Sqrt(qx*qx + qy*qy + qz*qz);
    	
    		for(int i=0;i<nmb;i++){
    			t[i] = 2*0.938272081*(p4_proton[i].E() - 0.938272081);
    		}
    		
    		combint = 0;
    		for(int i=0;i<nmb;i++){
    			vgs = p4_beam - p4_electron[0];

    			for(int j=0;j<nmg;j++){

                    auto temp1 = vgs.Px()*p4_gamma[j].Px() + vgs.Py()*p4_gamma[j].Py() + vgs.Pz()*p4_gamma[j].Pz();
                    auto temp2 = TMath::Sqrt( vgs.Px() * vgs.Px() + vgs.Py() * vgs.Py() + vgs.Pz() * vgs.Pz());
        	        auto temp3 = TMath::Sqrt( p4_gamma[j].Px() * p4_gamma[j].Px() + p4_gamma[j].Py() * p4_gamma[j].Py() + p4_gamma[j].Pz() * p4_gamma[j].Pz());
                	auto costheta = temp1/(temp2 * temp3);


                    tE[combint] =   (mp*Q2[0] + 2 *mp*Nu[0]*( Nu[0] - TMath::Sqrt(Nu[0]*Nu[0] + Q2[0]) *costheta ))/(mp + Nu[0] - TMath::Sqrt(Nu[0]*Nu[0] + Q2[0])*costheta);
                    vmP = p4_beam + p4_target - p4_electron[0] - p4_gamma[j];
                    vmG = p4_beam + p4_target - p4_electron[0] - p4_proton[i];

        	        vM = p4_beam + p4_target - p4_electron[0] - p4_proton[i] - p4_gamma[j];
        	        mmG[combint] = vmG.M2();
                	meG[combint] = vmG.E();
                    mmP[combint] = vmP.M2();
                    meP[combint] = vmP.E();
        	        mm[combint] = vM.M2();
                	me[combint] = vM.E();


                    mGpx[combint] = vmG.Px();
                    mGpy[combint] = vmG.Py();
        	        mGpz[combint] = vmG.Pz();
                	mGp[combint]  = vmG.P();

                    Mpx[combint] = vM.Px();
                    Mpy[combint] = vM.Py();
        	        Mpz[combint] = vM.Pz();
                	Mp[combint]  = vM.P();

    				pIndex[combint] = i;
    				gIndex[combint] = j;

    				v1.SetXYZ(p4_gamma[j].Px(),p4_gamma[j].Py(),p4_gamma[j].Pz());
                	v2.SetXYZ(vmG.Px(),vmG.Py(),vmG.Pz());
        	        theta1[combint] = TMath::ACos(v1.Dot(v2)/(v1.Mag()*v2.Mag()) )*180./TMath::Pi(); // from Sangbaek code

    				v2.SetXYZ(vgs.Px(),vgs.Py(),vgs.Pz());
    				v1.SetXYZ(p4_proton[i].Px(),p4_proton[i].Py(),p4_proton[i].Pz());
            		Vhadr = v1.Cross(v2);

            		v1.SetXYZ(p4_gamma[j].Px(),p4_gamma[j].Py(),p4_gamma[j].Pz());
            		Vhadr2 = v2.Cross(v1);


    			// trento 1
                    v1.SetXYZ(p4_beam.Px(),p4_beam.Py(),p4_beam.Pz());
                    v2.SetXYZ(p4_electron[0].Px(),p4_electron[0].Py(),p4_electron[0].Pz());
                    v3l = v1.Cross(v2);

                    v1.SetXYZ(p4_proton[i].Px(),p4_proton[i].Py(),p4_proton[i].Pz());
                    v2.SetXYZ(vgs.Px(),vgs.Py(),vgs.Pz());
                    v3h = v1.Cross(v2);

                    if( v1.Mag() * v2.Mag() !=0 && v1.Dot(v2)<v1.Mag()*v2.Mag() ) {
                        trento[combint] = TMath::ACos(v3l.Dot(v3h)/(v3l.Mag()*v3h.Mag()) ) * 180./TMath::Pi();
                    }
                    else trento[combint] =0;

                    if(v3l.Dot(v1) >0 ) trento[combint] = 360 - trento[combint];

    			// trento 2

                    v2.SetXYZ(p4_electron[0].Px(),p4_electron[0].Py(),p4_electron[0].Pz());
                    v1.SetXYZ(vgs.Px(),vgs.Py(),vgs.Pz());

                    vtemp1 = v1.Cross(v2);
                    v2.SetXYZ(p4_gamma[j].Px(),p4_gamma[j].Py(),p4_gamma[j].Pz());

                    vtemp2 = v1.Cross(v2);

                    if( vtemp1.Mag() * vtemp2.Mag() !=0 && vtemp1.Dot(vtemp2)<vtemp1.Mag()*vtemp2.Mag() ) {
                        trento2[combint] = TMath::ACos(vtemp1.Dot(vtemp2)/(vtemp1.Mag()*vtemp2.Mag()) ) * 180./TMath::Pi();
                    }
                    else trento2[combint] =0;

                    if (v1.Dot(vtemp1.Cross(vtemp2))<0) trento2[combint] = 360 - trento2[combint];

    				combint++;
    			}
    		}

            if(nmb>0 && nmg>=nmG)   T->Fill();

        }

    }

	rFile->Write();
	rFile->Close();

    return 1;
}
