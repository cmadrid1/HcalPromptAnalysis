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
#include "TArrayD.h"

TH1F* defineHist(const char *file="",const char *branch=""){
  Double_t norm = 1;
  Double_t min  = -0.5;
  Double_t max  = 9.5;

  TFile *f = new TFile(file);
  TH1F *h = (TH1F*)f->Get(branch);
  h->Scale(norm/h->Integral(min,max));
  return h;
}

double errorResidual(int j, TH1F* hdata, TH1F* hmc){
  double a     = hdata->GetBinContent(j);
  double b     = hmc->GetBinContent(j);
  double A     = a - b;
  double da    = hdata->GetBinError(j);
  double db    = hmc->GetBinError(j);
  double dA    = sqrt(da*da + db*db);
 
  double error = (A/a)*sqrt((dA/A)*(dA/A)+(db/b)*(db/b)); 
  return error;
}

TH1F* fillResidual(int j,TH1F* h,TH1F* H1,TH1F* H2,TH1F* H3,TH1F* H4,TH1F* H5,TH1F* H6,TH1F* H7,TH1F* H8,TH1F* H9,TH1F* H10,TH1F* H11,TH1F* H12,TH1F* H13,TH1F* H14,TH1F* H15,TH1F* H16){
  h->SetBinContent(1,0);
  h->SetBinContent(2,((H1->Integral(j+1,j+1))-(H9->Integral(j+1,j+1)))/(H9->Integral(j+1,j+1)));
  h->SetBinContent(3,((H2->Integral(j+1,j+1))-(H10->Integral(j+1,j+1)))/(H10->Integral(j+1,j+1)));
  h->SetBinContent(4,((H3->Integral(j+1,j+1))-(H11->Integral(j+1,j+1)))/(H11->Integral(j+1,j+1)));
  h->SetBinContent(5,((H4->Integral(j+1,j+1))-(H12->Integral(j+1,j+1)))/(H12->Integral(j+1,j+1)));
  h->SetBinContent(6,((H5->Integral(j+1,j+1))-(H13->Integral(j+1,j+1)))/(H13->Integral(j+1,j+1)));
  h->SetBinContent(7,((H6->Integral(j+1,j+1))-(H14->Integral(j+1,j+1)))/(H14->Integral(j+1,j+1)));
  h->SetBinContent(8,((H7->Integral(j+1,j+1))-(H15->Integral(j+1,j+1)))/(H15->Integral(j+1,j+1)));
  h->SetBinContent(9,((H8->Integral(j+1,j+1))-(H16->Integral(j+1,j+1)))/(H16->Integral(j+1,j+1)));

  h->SetBinError(2,errorResidual(j+1,H1,H9));
  h->SetBinError(3,errorResidual(j+1,H2,H10));
  h->SetBinError(4,errorResidual(j+1,H3,H11));
  h->SetBinError(5,errorResidual(j+1,H4,H12));
  h->SetBinError(6,errorResidual(j+1,H5,H13));
  h->SetBinError(7,errorResidual(j+1,H6,H14));
  h->SetBinError(8,errorResidual(j+1,H7,H15));
  h->SetBinError(9,errorResidual(j+1,H8,H16));
  return h;
}

void residual(const char *c0_Save = "TS4_residual.pdf",const char *c1_Save = "TS5_residual.pdf",const char *c2_Save = "TS6_residual.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  //Set the plots max and min y-value
  Double_t ymin =-0.4001;
  Double_t ymax =0.4001;

  //Define/Get the Histos to be plotted  
  
  TH1F* h1  = NULL;
  TH1F* h2  = NULL;
  TH1F* h3  = NULL;
  TH1F* h4  = NULL;
  TH1F* h5  = NULL;
  TH1F* h6  = NULL;
  TH1F* h7  = NULL;
  TH1F* h8  = NULL;
  TH1F* h9  = NULL;
  TH1F* h10 = NULL;
  TH1F* h11 = NULL;
  TH1F* h12 = NULL;
  TH1F* h13 = NULL;
  TH1F* h14 = NULL;
  TH1F* h15 = NULL;
  TH1F* h16 = NULL;
  TH1F* h17 = NULL;
  TH1F* h18 = NULL;
  TH1F* h19 = NULL;
  TH1F* h20 = NULL;
  TH1F* h21 = NULL;
  TH1F* h22 = NULL;
  TH1F* h23 = NULL;
  TH1F* h24 = NULL;
  TH1F* h25 = NULL;
  TH1F* h26 = NULL;
  TH1F* h27 = NULL;
  TH1F* h28 = NULL;
  TH1F* h29 = NULL;
  TH1F* h30 = NULL;
  TH1F* h31 = NULL;
  TH1F* h32 = NULL;
  TH1F* h33 = NULL;
  TH1F* h34 = NULL;
  TH1F* h35 = NULL;
  TH1F* h36 = NULL;
  TH1F* h37 = NULL;
  TH1F* h38 = NULL;
  TH1F* h39 = NULL;
  TH1F* h40 = NULL;
  TH1F* h41 = NULL;
  TH1F* h42 = NULL;
  TH1F* h43 = NULL;
  TH1F* h44 = NULL;
  TH1F* h45 = NULL;
  TH1F* h46 = NULL;
  TH1F* h47 = NULL;
  TH1F* h48 = NULL;
  
  //HB
  h1 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHB_SiPM");
  h2 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHB_SiPM");
  h3 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHB_SiPM");
  h4 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHB_SiPM");
  h5 = defineHist("Output_Histo_standard_100_150.root"          ,"pulseShape_DigiHB_SiPM");
  h6 = defineHist("Output_Histo_standard_150_200.root"          ,"pulseShape_DigiHB_SiPM");
  h7 = defineHist("Output_Histo_standard_200_300.root"          ,"pulseShape_DigiHB_SiPM");
  h8 = defineHist("Output_Histo_standard_300_inf.root"          ,"pulseShape_DigiHB_SiPM");

  h9  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_10_25.root"   ,"pulseShape_DigiHB_SiPM");
  h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_25_50.root"   ,"pulseShape_DigiHB_SiPM");
  h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_50_75.root"   ,"pulseShape_DigiHB_SiPM");
  h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_75_100.root"  ,"pulseShape_DigiHB_SiPM");
  h13 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHB_SiPM");
  h14 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHB_SiPM");
  h15 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHB_SiPM");
  h16 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHB_SiPM");

  h17 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHB_SiPM");
  h18 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHB_SiPM");
  h19 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHB_SiPM");
  h20 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHB_SiPM");  
  h21 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"        ,"pulseShape_DigiHB_SiPM");
  h22 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"        ,"pulseShape_DigiHB_SiPM");
  h23 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"        ,"pulseShape_DigiHB_SiPM");
  h24 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"        ,"pulseShape_DigiHB_SiPM");
  
  //HE
  h25 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHE_SiPM");
  h26 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHE_SiPM");
  h27 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHE_SiPM");
  h28 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHE_SiPM");
  h29 = defineHist("Output_Histo_standard_100_150.root"          ,"pulseShape_DigiHE_SiPM");
  h30 = defineHist("Output_Histo_standard_150_200.root"          ,"pulseShape_DigiHE_SiPM");
  h31 = defineHist("Output_Histo_standard_200_300.root"          ,"pulseShape_DigiHE_SiPM");
  h32 = defineHist("Output_Histo_standard_300_inf.root"          ,"pulseShape_DigiHE_SiPM");

  h33 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_10_25.root"   ,"pulseShape_DigiHE_SiPM");
  h34 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_25_50.root"   ,"pulseShape_DigiHE_SiPM");
  h35 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_50_75.root"   ,"pulseShape_DigiHE_SiPM");
  h36 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_75_100.root"  ,"pulseShape_DigiHE_SiPM");
  h37 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHE_SiPM");
  h38 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHE_SiPM");
  h39 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHE_SiPM");
  h40 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHE_SiPM");

  h41 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHE_SiPM");
  h42 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHE_SiPM");
  h43 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHE_SiPM");
  h44 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHE_SiPM");
  h45 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"        ,"pulseShape_DigiHE_SiPM");
  h46 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"        ,"pulseShape_DigiHE_SiPM");
  h47 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"        ,"pulseShape_DigiHE_SiPM");
  h48 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"        ,"pulseShape_DigiHE_SiPM");

  Float_t bins[] = {0,10,25,50,75,100,150,200,300,600};
  Int_t binnum   = sizeof(bins)/sizeof(Float_t)-1;

  TH1F *HBTS4  = new TH1F("HBTS4","HBTS4",binnum,bins);
  TH1F *HBTS5  = new TH1F("HBTS5","HBTS5",binnum,bins);
  TH1F *HBTS6  = new TH1F("HBTS6","HBTS6",binnum,bins);

  TH1F *HETS4  = new TH1F("HETS4","HETS4",binnum,bins);
  TH1F *HETS5  = new TH1F("HETS5","HETS5",binnum,bins);
  TH1F *HETS6  = new TH1F("HETS6","HETS6",binnum,bins);

  TH1F *HBTS4old  = new TH1F("HBTS4old","HBTS4old",binnum,bins);
  TH1F *HBTS5old  = new TH1F("HBTS5old","HBTS5old",binnum,bins);
  TH1F *HBTS6old  = new TH1F("HBTS6old","HBTS6old",binnum,bins);

  TH1F *HETS4old  = new TH1F("HETS4old","HETS4old",binnum,bins);
  TH1F *HETS5old  = new TH1F("HETS5old","HETS5old",binnum,bins);
  TH1F *HETS6old  = new TH1F("HETS6old","HETS6old",binnum,bins);

  fillResidual(4,HBTS4,h17,h18,h19,h20,h21,h22,h23,h24,h1,h2,h3,h4,h5,h6,h7,h8);
  fillResidual(5,HBTS5,h17,h18,h19,h20,h21,h22,h23,h24,h1,h2,h3,h4,h5,h6,h7,h8);
  fillResidual(6,HBTS6,h17,h18,h19,h20,h21,h22,h23,h24,h1,h2,h3,h4,h5,h6,h7,h8);

  fillResidual(4,HETS4,h41,h42,h43,h44,h45,h46,h47,h48,h25,h26,h27,h28,h29,h30,h31,h32);
  fillResidual(5,HETS5,h41,h42,h43,h44,h45,h46,h47,h48,h25,h26,h27,h28,h29,h30,h31,h32);
  fillResidual(6,HETS6,h41,h42,h43,h44,h45,h46,h47,h48,h25,h26,h27,h28,h29,h30,h31,h32);

  fillResidual(4,HBTS4old,h17,h18,h19,h20,h21,h22,h23,h24,h9,h10,h11,h12,h13,h14,h15,h16);
  fillResidual(5,HBTS5old,h17,h18,h19,h20,h21,h22,h23,h24,h9,h10,h11,h12,h13,h14,h15,h16);
  fillResidual(6,HBTS6old,h17,h18,h19,h20,h21,h22,h23,h24,h9,h10,h11,h12,h13,h14,h15,h16);

  fillResidual(4,HETS4old,h41,h42,h43,h44,h45,h46,h47,h48,h33,h34,h35,h36,h37,h38,h39,h40);
  fillResidual(5,HETS5old,h41,h42,h43,h44,h45,h46,h47,h48,h33,h34,h35,h36,h37,h38,h39,h40);
  fillResidual(6,HETS6old,h41,h42,h43,h44,h45,h46,h47,h48,h33,h34,h35,h36,h37,h38,h39,h40);

  //Define the canvas and Legends
  TLegend* catLeg0 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c0 = new TCanvas("c0","c0",1000,800);
  
  TLegend* catLeg1 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c1 = new TCanvas("c1","c1",1000,800);

  TLegend* catLeg2 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c2 = new TCanvas("c2","c2",1000,800);

  ////////////////////////////////////////////////////////////////////
  //   Plotting
  ////////////////////////////////////////////////////////////////////

  //HB TS4
  c0->cd();
  //gPad->SetLogy();
  gPad->SetGrid();

  HBTS4->SetLineColor(1);
  HBTS4->Draw("E1"); 
  HBTS4->SetMinimum(ymin);
  HBTS4->SetMaximum(ymax);
  HBTS4->SetTitle("TS4 Residual");
  HBTS4->GetXaxis()->SetTitle("Charge[fC]");
  HBTS4->GetYaxis()->SetTitle("(Data/MC)-1");
  HBTS4->SetTitleOffset(1.5,"Y");
  HBTS4->SetTitleOffset(1.5,"X");
  HBTS4->SetLabelSize(0.05,"Y");
  HBTS4->SetLabelSize(0.05,"X");
  //HBTS4->SetTitleSize(0.001);
  HBTS4->SetName("");
  HBTS4->SetStats(false);

  HBTS4old->SetLineColor(1);
  HBTS4old->SetLineStyle(2);
  HBTS4old->Draw("E1 same");
  HETS4->SetLineColor(2);
  HETS4->Draw("E1 same");
  HETS4old->SetLineColor(2);
  HETS4old->SetLineStyle(2);
  HETS4old->Draw("E1 same");

  catLeg0->SetTextSize(0.03);
  catLeg0->AddEntry(HBTS4,"HB new standard" ,"l");  
  catLeg0->AddEntry(HBTS4old,"HB current standard" ,"l");  
  catLeg0->AddEntry(HETS4,"HE new standard" ,"l");  
  catLeg0->AddEntry(HETS4old,"HE current standard" ,"l");  
  catLeg0->Draw();

  //HB TS5
  c1->cd();
  //gPad->SetLogy();
  gPad->SetGrid();

  HBTS5->SetLineColor(1);
  HBTS5->Draw("E1"); 
  HBTS5->SetMinimum(ymin);
  HBTS5->SetMaximum(ymax);
  HBTS5->SetTitle("TS5 Residual");
  HBTS5->GetXaxis()->SetTitle("Charge[fC]");
  HBTS5->GetYaxis()->SetTitle("(Data/MC)-1");
  HBTS5->SetTitleOffset(1.5,"Y");
  HBTS5->SetTitleOffset(1.5,"X");
  HBTS5->SetLabelSize(0.05,"Y");
  HBTS5->SetLabelSize(0.05,"X");
  //HBTS5->SetTitleSize(0.001);
  HBTS5->SetName("");
  HBTS5->SetStats(false);

  HBTS5old->SetLineColor(1);
  HBTS5old->SetLineStyle(2);
  HBTS5old->Draw("E1 same");
  HETS5->SetLineColor(2);
  HETS5->Draw("E1 same");
  HETS5old->SetLineColor(2);
  HETS5old->SetLineStyle(2);
  HETS5old->Draw("E1 same");

  catLeg1->SetTextSize(0.03);
  catLeg1->AddEntry(HBTS5,"HB new standard" ,"l");  
  catLeg1->AddEntry(HBTS5old,"HB current standard" ,"l");  
  catLeg1->AddEntry(HETS5,"HE new standard" ,"l");  
  catLeg1->AddEntry(HETS5old,"HE current standard" ,"l");  
  catLeg1->Draw();

  //HE TS6
  c2->cd();
  //gPad->SetLogy();
  gPad->SetGrid();

  HBTS6->SetLineColor(1);
  HBTS6->Draw("E1"); 
  HBTS6->SetMinimum(ymin);
  HBTS6->SetMaximum(ymax);
  HBTS6->SetTitle("TS6 Residual");
  HBTS6->GetXaxis()->SetTitle("Charge[fC]");
  HBTS6->GetYaxis()->SetTitle("(Data/MC)-1");
  HBTS6->SetTitleOffset(1.5,"Y");
  HBTS6->SetTitleOffset(1.5,"X");
  HBTS6->SetLabelSize(0.05,"Y");
  HBTS6->SetLabelSize(0.05,"X");
  //HBTS6->SetTitleSize(0.001);
  HBTS6->SetName("");
  HBTS6->SetStats(false);

  HBTS6old->SetLineColor(1);
  HBTS6old->Draw("E1 same");
  HBTS6old->SetLineStyle(2);
  HETS6->SetLineColor(2);
  HETS6->Draw("E1 same");
  HETS6old->SetLineColor(2);
  HETS6old->SetLineStyle(2);
  HETS6old->Draw("E1 same");

  catLeg2->SetTextSize(0.03);
  catLeg2->AddEntry(HBTS6,"HB new standard" ,"l");  
  catLeg2->AddEntry(HBTS6old,"HB current standard" ,"l");  
  catLeg2->AddEntry(HETS6,"HE new standard" ,"l");  
  catLeg2->AddEntry(HETS6old,"HE current standard" ,"l");  
  catLeg2->Draw();

  //Save Plot
  c0->SaveAs(c0_Save);
  c1->SaveAs(c1_Save);
  c2->SaveAs(c2_Save);

}//End of Macro
