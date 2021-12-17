#ifndef _VVVTree_MJJ_MJJJ_
#define _VVVTree_MJJ_MJJJ_

void EDBR2PKUTree::EventLevel() {
    Nj4_Nj8();
    MJJ_MJJJf();
    HT_ST();
    NAK4();
    Nbtagf();
}

void EDBR2PKUTree::Weightf(Double_t XS, Int_t Nevents, Double_t LUMI) {

	Double_t nn;
	Float_t Identical_lumiWeight = XS;//All the events inside a sample are same lumiweight

    trigger_eff=1.0;
    IDweight=1.0;
    IDweightISO=1.0;
    IDweighttrk=1.0;
    ToppTweight=1.0;
    if(genWeight>0) nn=1;    else nn= -1;
    lumiWeight=Identical_lumiWeight/abs(Nevents);
    lumiWeight=lumiWeight*LUMI;
    weight=lumiWeight*nn;

    if (IsData==2 ) weight = weight*1.21*1.06684;weight_deep = weight_deep*1.21*1.06684;
    if (IsData==3 ) weight = weight*1.21*1.046;weight_deep = weight_deep*1.21*1.046;
    if (IsData==4 ) weight = weight*1.21*0.99246;weight_deep = weight_deep*1.21*0.99246;
    if (IsData==5 ) weight = weight*1.21*0.9155;weight_deep = weight_deep*1.21*0.9155;
    if (IsData==6 ) weight = weight*1.21*0.8093;weight_deep = weight_deep*1.21*0.8093;
    if (IsData==7 ) weight = weight*1.21*0.6498;weight_deep = weight_deep*1.21*0.6498;
    if (IsData==8 ) weight = weight*1.21*0.4843;weight_deep = weight_deep*1.21*0.4843;
    if ( IsData==0 ) weight=1;weight_deep = 1;
}

void EDBR2PKUTree::MJJ_MJJJf() {
    
    if(Nj8==2){
        AK81.SetPtEtaPhiM(PTj_max,Etaj_max,Phij_max,Mj_max);
        AK82.SetPtEtaPhiM(PTj_min,Etaj_min,Phij_min,Mj_min);
        MJJ=(AK81+AK82).M();
        if(MJJ>100000||MJJ<-99){
            cout<<"MJJ:"<<MJJ<<endl;
        }
    }

    if(Nj8==3){
        AK81.SetPtEtaPhiM(PTj_max,Etaj_max,Phij_max,Mj_max);
        AK82.SetPtEtaPhiM(PTj_mid,Etaj_mid,Phij_mid,Mj_mid);
        AK83.SetPtEtaPhiM(PTj_min,Etaj_min,Phij_min,Mj_min);
        MJJJ=(AK81+AK82+AK83).M();
        MJJ=-99;
    }

}

void EDBR2PKUTree::HT_ST() {

    HT = (jetAK8puppi_pt>0)*jetAK8puppi_pt+(jetAK8puppi_pt_2>0)*jetAK8puppi_pt_2+(jetAK8puppi_pt_3>0)*jetAK8puppi_pt_3;

    ST=Float_t(HT+MET_et);
                
}

void EDBR2PKUTree::Nj4_Nj8() {
    Nj4=(ak4jet_pt[0]>0)+(ak4jet_pt[1]>0)+(ak4jet_pt[2]>0)+(ak4jet_pt[3]>0)+(ak4jet_pt[4]>0)+(ak4jet_pt[5]>0)+(ak4jet_pt[6]>0)+(ak4jet_pt[7]>0)+(ak4jet_pt[8]>0)+(ak4jet_pt[9]>0)+(ak4jet_pt[10]>0)+(ak4jet_pt[11]>0)+(ak4jet_pt[12]>0)+(ak4jet_pt[13]>0)+(ak4jet_pt[14]>0);

    Nj8=(jetAK8puppi_pt>0)+(jetAK8puppi_pt_2>0)+(jetAK8puppi_pt_3>0);
}

void EDBR2PKUTree::NAK4() {


    AK41.SetPtEtaPhiM(0,-99,-99,-99);
    AK42.SetPtEtaPhiM(0,-99,-99,-99);
    AK43.SetPtEtaPhiM(0,-99,-99,-99);
    AK44.SetPtEtaPhiM(0,-99,-99,-99);
    AK45.SetPtEtaPhiM(0,-99,-99,-99);
    AK46.SetPtEtaPhiM(0,-99,-99,-99);

for(Int_t i=0;i<15;i++){
deltaRak4sj[i]=sqrt(pow(fabs(ak4jet_eta[i]-Etaj),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-Phij),2*Pi-fabs(ak4jet_phi[i]-Phij)),2));
deltaRak4sj2[i]=sqrt(pow(fabs(ak4jet_eta[i]-Etaj_2),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-Phij_2),2*Pi-fabs(ak4jet_phi[i]-Phij_2)),2));
       if(Nj8==3){
deltaRak4sj3[i]=sqrt(pow(fabs(ak4jet_eta[i]-Etaj_3),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-Phij_3),2*Pi-fabs(ak4jet_phi[i]-Phij_3)),2));
           }
       else{
deltaRak4sj3[i]=10000;
           }     
       if(Nj8==4){
deltaRak4sj4[i]=sqrt(pow(fabs(ak4jet_eta[i]-Etaj_4),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-Phij_4),2*Pi-fabs(ak4jet_phi[i]-Phij_4)),2));
           }
       else{
deltaRak4sj4[i]=10000;
           }
}

num_ak4jetsex=0;
num_ak4jetsin=0;

Double_t DR=0.8;

for(Int_t i=0; i<15; i++) {

ex_ak4jet_pt[i]=-99;
ex_ak4jet_eta[i]=-99;

}

for(Int_t ii=0; ii<15; ii++) {
bool cutsj=0;
bool cutsj2=0;
bool cutsj3=0;
bool cutsj4=0;
bool cutsjin=0; 
bool cutsjin2=0;
bool cutsjin3=0;
bool cutsjin4=0;
bool sjout=1,sjin=0;

cutsj=(ak4jet_pt[ii]>0)&&(deltaRak4sj[ii]>DR);
cutsjin=(ak4jet_pt[ii]>0)&&(deltaRak4sj[ii]<DR);

cutsj2=(ak4jet_pt[ii]>0)&&(deltaRak4sj2[ii]>DR);
cutsjin2=(ak4jet_pt[ii]>0)&&(deltaRak4sj2[ii]<DR);

cutsj3=(ak4jet_pt[ii]>0)&&(deltaRak4sj3[ii]>DR);
cutsjin3=(ak4jet_pt[ii]>0)&&(deltaRak4sj3[ii]<DR);

cutsj4=(ak4jet_pt[ii]>0)&&(deltaRak4sj4[ii]>DR);
cutsjin4=(ak4jet_pt[ii]>0)&&(deltaRak4sj4[ii]<DR);

sjout*=cutsj*cutsj2*cutsj3*cutsj4;
sjin+=cutsjin+cutsjin2+cutsjin3+cutsjin4;

if(sjout==1) 
              {num_ak4jetsex++;
                   if(num_ak4jetsex==1) {
         AK41.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[0]=ak4jet_pt[ii];
                               ex_ak4jet_eta[0]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==2) {
         AK42.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[1]=ak4jet_pt[ii];
                               ex_ak4jet_eta[1]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==3) {
         AK43.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[2]=ak4jet_pt[ii];
                               ex_ak4jet_eta[2]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==4) {
         AK44.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[3]=ak4jet_pt[ii];
                               ex_ak4jet_eta[3]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==5) {
         AK45.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[4]=ak4jet_pt[ii];
                               ex_ak4jet_eta[4]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==6) {
         AK46.SetPtEtaPhiE(ak4jet_pt[ii],ak4jet_eta[ii],ak4jet_phi[ii],ak4jet_e[ii]);
                               ex_ak4jet_pt[5]=ak4jet_pt[ii];
                               ex_ak4jet_eta[5]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==7) {
                               ex_ak4jet_pt[6]=ak4jet_pt[ii];
                               ex_ak4jet_eta[6]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==8) {
                               ex_ak4jet_pt[7]=ak4jet_pt[ii];
                               ex_ak4jet_eta[7]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==9) {
                               ex_ak4jet_pt[8]=ak4jet_pt[ii];
                               ex_ak4jet_eta[8]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==10) {
                               ex_ak4jet_pt[9]=ak4jet_pt[ii];
                               ex_ak4jet_eta[9]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==11) {
                               ex_ak4jet_pt[10]=ak4jet_pt[ii];
                               ex_ak4jet_eta[10]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==12) {
                               ex_ak4jet_pt[11]=ak4jet_pt[ii];
                               ex_ak4jet_eta[11]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==13) {
                               ex_ak4jet_pt[12]=ak4jet_pt[ii];
                               ex_ak4jet_eta[12]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==14) {
                               ex_ak4jet_pt[13]=ak4jet_pt[ii];
                               ex_ak4jet_eta[13]=ak4jet_eta[ii];
                                        }
                   if(num_ak4jetsex==15) {
                               ex_ak4jet_pt[14]=ak4jet_pt[ii];
                               ex_ak4jet_eta[14]=ak4jet_eta[ii];
                                        }
              }
if(sjin>=1) num_ak4jetsin++;
}


}

void EDBR2PKUTree::Nbtagf() {
    //number of bjet calculation
		num_bJet=0.;
		num_bJet_loose=0.;
		num_bJet_tight=0.;
        num_bJet_deep=0.;
        num_bJet_loose_deep=0.;
        num_bJet_tight_deep=0.;
               
		for(Int_t i=0; i<15; i++)  {
                deltaRAK4AK8_new[i]=99;
                deltaRAK4AK8_new_2[i]=99;
                deltaRAK4AK8_new_3[i]=99;
                deltaRAK4AK8_new_4[i]=99;
                        if(Nj8>=1) deltaRAK4AK8_new[i]=sqrt(pow(fabs(ak4jet_eta[i]-jetAK8puppi_eta),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-jetAK8puppi_phi),2*Pi-fabs(ak4jet_phi[i]-jetAK8puppi_phi)),2));
                        if(Nj8>=2) deltaRAK4AK8_new_2[i]=sqrt(pow(fabs(ak4jet_eta[i]-jetAK8puppi_eta_2),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-jetAK8puppi_phi_2),2*Pi-fabs(ak4jet_phi[i]-jetAK8puppi_phi_2)),2));
                        if(Nj8>=3) deltaRAK4AK8_new_3[i]=sqrt(pow(fabs(ak4jet_eta[i]-jetAK8puppi_eta_3),2)+pow(TMath::Min(fabs(ak4jet_phi[i]-jetAK8puppi_phi_3),2*Pi-fabs(ak4jet_phi[i]-jetAK8puppi_phi_3)),2));
			if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.8484 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet=num_bJet+1;}
			if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.5426 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet_loose=num_bJet_loose+1;}
			if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.9535 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet_tight=num_bJet_tight+1;}
//deep
                        if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.6324 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet_deep=num_bJet_deep+1;}
                        if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.2219 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet_loose_deep=num_bJet_loose_deep+1;}
                        if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.8958 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 && deltaRAK4AK8_new[i]>=0.8&& deltaRAK4AK8_new_2[i]>=0.8&& deltaRAK4AK8_new_3[i]>=0.8&& deltaRAK4AK8_new_4[i]>=0.8 ) {num_bJet_tight_deep=num_bJet_tight_deep+1;}
		}
		nbtag=num_bJet;
        nbtag_deep=num_bJet_deep;
        nbtag_deep_loose=num_bJet_loose_deep;
        nbtag_deep_tight=num_bJet_tight_deep;

        // gKK 21.9.7 adding inclusive b jets

        num_bJet_in = 0;
        num_bJet_loose_in = 0;
        num_bJet_tight_in = 0;
        num_bJet_deep_in = 0;
        num_bJet_loose_deep_in = 0;
        num_bJet_tight_deep_in = 0;
        for(Int_t i=0; i<15; i++)  {
            if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.8484 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 ) {num_bJet_in=num_bJet_in+1;}
            if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.5426 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 ) {num_bJet_loose_in=num_bJet_loose_in+1;}
            if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.9535 && fabs(ak4jet_eta[i])<2.4 && ak4jet_IDLoose[i]>0 ) {num_bJet_tight_in=num_bJet_tight_in+1;}
            //deep
            if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.6324 && fabs(ak4jet_eta[i])<2.4 ) {num_bJet_deep_in=num_bJet_deep_in+1;}
            if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.2219 && fabs(ak4jet_eta[i])<2.4 ) {num_bJet_loose_deep_in=num_bJet_loose_deep_in+1;}
            if(ak4jet_pt[i]>30 && (ak4jet_deepcsvb[i]+ak4jet_deepcsvbb[i])>0.8958 && fabs(ak4jet_eta[i])<2.4 ) {num_bJet_tight_deep_in=num_bJet_tight_deep_in+1;}
		}

		//number of bjet calculation Done
}


#endif