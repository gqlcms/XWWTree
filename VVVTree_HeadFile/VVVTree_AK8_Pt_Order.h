#ifndef _VVVTree_AK8_Pt_Order_
#define _VVVTree_AK8_Pt_Order_

/*
jetAK8puppi_sdJEC
jetAK8puppi_sdJEC_2
*/

void EDBR2PKUTree::AK8_Pt_Ordered() {
    AK8_Pt_Ordered_p4();
}

void EDBR2PKUTree::AK8_Pt_Ordered_p4(){

    PTj    = Float_t(jetAK8puppi_pt);
    PTj_2  = Float_t(jetAK8puppi_pt_2);
    PTj_3  = Float_t(jetAK8puppi_pt_3);

    Etaj   = jetAK8puppi_eta;
    Etaj_2 = jetAK8puppi_eta_2;
    Etaj_3 = jetAK8puppi_eta_3;

    Phij   = jetAK8puppi_phi;
    Phij_2 = jetAK8puppi_phi_2;
    Phij_3 = jetAK8puppi_phi_3;
    
    Mj   = jetAK8puppi_sd ; 
    Mj_2 = jetAK8puppi_sd_2 ; 
    Mj_3 = jetAK8puppi_sd_3 ; 

}


#endif