#define EDBR2PKUTree_cxx
#include "EDBR2PKUTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#define Pi 3.141593
#include "TLorentzVector.h"
//#include "BTagCalibrationStandalone.h"


#include "VVVTree_HeadFile/VVVTree_DeepW_Rank_Variable.h"
#include "VVVTree_HeadFile/VVVTree_Added_Variables.h"
#include "VVVTree_HeadFile/VVVTree_MET.h"
#include "VVVTree_HeadFile/VVVTree_EventLevel.h"
// #include "VVVTree_HeadFile/VVVTree_Unknown.h"
#include "VVVTree_HeadFile/VVVTree_MET_AK8.h"
#include "VVVTree_HeadFile/VVVTree_Rank_AK8.h"
#include "VVVTree_HeadFile/VVVTree_DR_DPhi_M2J.h"
#include "VVVTree_HeadFile/VVVTree_AK8_Mass_Order.h"
#include "VVVTree_HeadFile/VVVTree_AK8_Pt_Order.h"
#include "VVVTree_HeadFile/VVVTree_AK8_deep_W_Order.h"


void EDBR2PKUTree::Loop(TString channelname, Double_t XS, Int_t IsData_, Int_t Nevents,  Double_t LUMI) {
    IsData = IsData_;

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	//for (Long64_t jentry=0; jentry<10;jentry++)
	for (Long64_t jentry=0; jentry<nentries;jentry++) 
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
        if (jentry%100000==0)   {std::cout<<jentry<<std::endl;}
		nb = fChain->GetEntry(jentry); 
		nbytes += nb;
        if(event<0){event=event+pow(2,32);}

        AK81.SetPtEtaPhiM(0,-99,-99,-99);
        AK82.SetPtEtaPhiM(0,-99,-99,-99);
        AK83.SetPtEtaPhiM(0,-99,-99,-99);
        AK84.SetPtEtaPhiM(0,-99,-99,-99);
                
		Int_t nLooseLep=nLooseEle+nLooseMu;

        AK8_Pt_Ordered();
        METf();
        MJJ_MJJJf();
        DeepAK8_Mass_Ordered_init();
        DeepAK8_Mass_Ordered_P4();
        Rank_AK8();
        METAK8_DPhi();
        METRecovery();
        MET_AK8_MT();
        DR_DPhi_M2J();
        DeepAK8_Mass_Ordered();
        Deep_W_Ordered();
        EventLevel();
        Weightf(XS, Nevents, LUMI);

        if ( Nj8 == 2 || Nj8 == 3 ){
            ExTree->Fill();
        }
    }
	
    std::cout << "transfertree finished" << std::endl;

}
