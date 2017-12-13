#include "TROOT.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TList.h"
#include "TLegendEntry.h"
#include "string.h"
#include <iostream>
#include "TTreeReader.h"
#include "TChain.h"
#include "TProfile.h"
#include <cmath>
#include "TProfile2D.h"
#include "TH2D.h"
#include "TTree.h"

void fillHisto_HcalRecHit(const char *infile, const char *outfile, const char *flag = "single"){
   
  TTreeReader *tReader;
 
  if(!strcmp(flag,"single")){

    TFile *f1 = new TFile(infile);
    if(f1->IsZombie()){
      cout << "Root file: " << infile << " not found!" << endl;
      return;
    }
    tReader = new TTreeReader("hcalRecHitTree/HcalRecHit",f1);

  } 
  else if(!strcmp(flag,"list")){
    
    ifstream in;
    in.open(infile);
    if(!in.is_open()){
      cout << "Cannot open list file: " << infile << endl;
      return;  
    }

    TChain *chain = new TChain("HcalRecHit");
    
    string line;
    while(in.good()){
      if(!std::getline(in,line)) break; // We read a line from the file
      if(!chain->Add(line.c_str())){
	cout << "Problem loading tree from " << line << endl;
      }else{
	cout << "Adding file: " << line << "..." << endl;
      }
    }
    
    in.close();
    
    tReader = new TTreeReader((TTree *)chain);
    cout << "Finished loading files." << endl;
  } else {
    cout << "Unknown option: " << flag << endl;
    return;
  }

  TFile *f2 = new TFile(outfile, "NEW");
  if(f2->IsZombie()){
    cout << "Root file: " << outfile << " cannot be created!" << endl;
    return;
  }
  f2->cd();
      
  //Define the branchs to be read
  TTreeReaderValue<Int_t> eventID(*tReader, "event");
  TTreeReaderValue<Int_t> lumiID(*tReader, "lumi");
  TTreeReaderValue<Int_t> runID(*tReader, "run");  

  TTreeReaderValue<std::vector<Int_t>> recHitHB_ieta(*tReader, "recHitHB_ieta");
  TTreeReaderValue<std::vector<Int_t>> recHitHB_iphi(*tReader, "recHitHB_iphi");
  TTreeReaderValue<std::vector<Int_t>> recHitHB_depth(*tReader, "recHitHB_depth");

  TTreeReaderValue<std::vector<Int_t>> recHitHE_ieta(*tReader, "recHitHE_ieta");
  TTreeReaderValue<std::vector<Int_t>> recHitHE_iphi(*tReader, "recHitHE_iphi");
  TTreeReaderValue<std::vector<Int_t>> recHitHE_depth(*tReader, "recHitHE_depth");

  TTreeReaderValue<std::vector<float>> recHitHB_En(*tReader, "recHitHB_En");
  TTreeReaderValue<std::vector<float>> recHitHB_EnRAW(*tReader, "recHitHB_EnRAW");
  TTreeReaderValue<std::vector<float>> recHitHB_time(*tReader, "recHitHB_time");
  TTreeReaderValue<std::vector<float>> chi2HB(*tReader, "chi2HB");

  TTreeReaderValue<std::vector<float>> recHitHE_En(*tReader, "recHitHE_En");
  TTreeReaderValue<std::vector<float>> recHitHE_EnRAW(*tReader, "recHitHE_EnRAW");
  TTreeReaderValue<std::vector<float>> recHitHE_time(*tReader, "recHitHE_time");
  TTreeReaderValue<std::vector<float>> chi2HE(*tReader, "chi2HE");

  //Define the Histograms to be filled
  TProfile *chi2_energyHB = new TProfile("chi2_energyHB","chi2_energyHB",100,0,500);
  TH2F *TH2_chi2_energyHB = new TH2F("TH2_chi2_energyHB","TH2_chi2_energyHB",100,0,500,100,-5,5);
  TH2F *M2vsM0_HB         = new TH2F("M2vsM0_HB","M2vsM0_HB",100,0,500,100,0,500);
  TH2F *TH2_time_energyHB = new TH2F("TH2_time_energyHB","TH2_time_energyHB",100,0,500,400,-20,20);

  TProfile *chi2_energyHE = new TProfile("chi2_energyHE","chi2_energyHE",100,0,500);
  TH2F *TH2_chi2_energyHE = new TH2F("TH2_chi2_energyHE","TH2_chi2_energyHE",100,0,500,100,-5,5);
  TH2F *M2vsM0_HE         = new TH2F("M2vsM0_HE","M2vsM0_HE",100,0,500,100,0,500);
  TH2F *TH2_time_energyHE = new TH2F("TH2_time_energyHE","TH2_time_energyHE",100,0,500,400,-20,20);
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                           While loop over all of the events and fills the histograms                                         //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  while(tReader->Next()){
    
    for(int rechit = 0; rechit < (*chi2HB).size(); rechit++){
      double chi2     = (*chi2HB).at(rechit);
      double energyM2 = (*recHitHB_En).at(rechit);
      double energyM0 = (*recHitHB_EnRAW).at(rechit);
      double time     = (*recHitHB_time).at(rechit);
      int ieta        = (*recHitHB_ieta).at(rechit);
      int iphi        = (*recHitHB_iphi).at(rechit);
      int depth       = (*recHitHB_depth).at(rechit);
      
      if(chi2 > 0){
	chi2_energyHB->Fill(energyM2,log10(chi2));
	TH2_chi2_energyHB->Fill(energyM2,log10(chi2));
	M2vsM0_HB->Fill(energyM0,energyM2);
	TH2_time_energyHB->Fill(energyM2,time);
      }

    }//HB RecHit Loop

    for(int rechit = 0; rechit < (*chi2HE).size(); rechit++){
      double chi2     = (*chi2HE).at(rechit);
      double energyM2 = (*recHitHE_En).at(rechit);
      double energyM0 = (*recHitHE_EnRAW).at(rechit);
      double time     = (*recHitHE_time).at(rechit);	
      int ieta        = (*recHitHE_ieta).at(rechit);
      int iphi        = (*recHitHE_iphi).at(rechit);
      int depth       = (*recHitHE_depth).at(rechit);
      
      if(ieta > 0 && iphi >= 63 && iphi <= 66){
	//In HEP17
      }//In HEP17
      else{
	if(chi2 > 0){
	  chi2_energyHE->Fill(energyM2,log10(chi2));
	  TH2_chi2_energyHE->Fill(energyM2,log10(chi2));
	  M2vsM0_HE->Fill(energyM0,energyM2);
	  TH2_time_energyHE->Fill(energyM2,time);
	}
	
      }//Cut on HEP17
      
    }//HE RecHit Loop

  }//End of While Loop
  
  //Fill Histograms
  f2->Write();

}//End of Macro
