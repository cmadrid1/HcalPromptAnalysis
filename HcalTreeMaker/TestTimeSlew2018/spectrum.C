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
  TFile *f = new TFile(file);
  TH1F *h = (TH1F*)f->Get(branch);
  return h;
}

void spectrum(const char *c0_Save = "spectrum_HBMC.pdf",const char *c1_Save = "spectrum_HBData.pdf",const char *c2_Save = "spectrum_HEMC.pdf",const char *c3_Save = "spectrum_HEData.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  //Set the plots max and min y-value
  Double_t ymin =0.;
  Double_t ymax =1000;

  //Define/Get the Histos to be plotted  
  //HB
  TH1F* h1 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHB_HPD");
  TH1F* h2 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHB_HPD");
  TH1F* h3 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHB_HPD");
  TH1F* h4 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHB_HPD");
  TH1F* h5 = defineHist("Output_Histo_standard_100_150.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h6 = defineHist("Output_Histo_standard_150_200.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h7 = defineHist("Output_Histo_standard_200_300.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h8 = defineHist("Output_Histo_standard_300_inf.root"          ,"pulseShape_DigiHB_HPD");
  
  TH1F* h9  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_10_25.root"   ,"pulseShape_DigiHB_HPD");
  TH1F* h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_25_50.root"   ,"pulseShape_DigiHB_HPD");
  TH1F* h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_50_75.root"   ,"pulseShape_DigiHB_HPD");
  TH1F* h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_75_100.root"  ,"pulseShape_DigiHB_HPD");
  TH1F* h13 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHB_HPD");
  TH1F* h14 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHB_HPD");
  TH1F* h15 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHB_HPD");
  TH1F* h16 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHB_HPD");
  
  TH1F* h17 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h18 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h19 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHB_HPD");
  TH1F* h20 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHB_HPD");  
  TH1F* h21 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"        ,"pulseShape_DigiHB_HPD");
  TH1F* h22 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"        ,"pulseShape_DigiHB_HPD");
  TH1F* h23 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"        ,"pulseShape_DigiHB_HPD");
  TH1F* h24 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"        ,"pulseShape_DigiHB_HPD");

  //HE
  TH1F* h25 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHE_HPD");
  TH1F* h26 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHE_HPD");
  TH1F* h27 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHE_HPD");
  TH1F* h28 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHE_HPD");
  TH1F* h29 = defineHist("Output_Histo_standard_100_150.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h30 = defineHist("Output_Histo_standard_150_200.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h31 = defineHist("Output_Histo_standard_200_300.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h32 = defineHist("Output_Histo_standard_300_inf.root"          ,"pulseShape_DigiHE_HPD");

  TH1F* h33 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_10_25.root"   ,"pulseShape_DigiHE_HPD");
  TH1F* h34 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_25_50.root"   ,"pulseShape_DigiHE_HPD");
  TH1F* h35 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_50_75.root"   ,"pulseShape_DigiHE_HPD");
  TH1F* h36 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_75_100.root"  ,"pulseShape_DigiHE_HPD");
  TH1F* h37 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHE_HPD");
  TH1F* h38 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHE_HPD");
  TH1F* h39 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHE_HPD");
  TH1F* h40 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/500GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHE_HPD");

  TH1F* h41 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h42 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h43 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHE_HPD");
  TH1F* h44 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHE_HPD");
  TH1F* h45 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"        ,"pulseShape_DigiHE_HPD");
  TH1F* h46 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"        ,"pulseShape_DigiHE_HPD");
  TH1F* h47 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"        ,"pulseShape_DigiHE_HPD");
  TH1F* h48 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"        ,"pulseShape_DigiHE_HPD");

  Float_t bins[] = {0,10,25,50,75,100,150,200,300,600};
  Int_t binnum   = sizeof(bins)/sizeof(Float_t)-1;

  TH1F *HBnew  = new TH1F("HBnew","HBnew",binnum,bins);
  TH1F *HBold  = new TH1F("HBold","HBold",binnum,bins);
  TH1F *HBdata = new TH1F("HBdata","HBdata",binnum,bins);

  TH1F *HEnew  = new TH1F("HEnew","HEnew",binnum,bins);
  TH1F *HEold  = new TH1F("HEold","HEold",binnum,bins);
  TH1F *HEdata = new TH1F("HEdata","HEdata",binnum,bins);

  HBnew->SetBinContent(1,0);
  HBnew->SetBinContent(2,h1->GetEntries());
  HBnew->SetBinContent(3,h2->GetEntries());
  HBnew->SetBinContent(4,h3->GetEntries());
  HBnew->SetBinContent(5,h4->GetEntries());  
  HBnew->SetBinContent(6,h5->GetEntries());
  HBnew->SetBinContent(7,h6->GetEntries());
  HBnew->SetBinContent(8,h7->GetEntries());
  HBnew->SetBinContent(9,h8->GetEntries());

  HBold->SetBinContent(1,0);
  HBold->SetBinContent(2,h9->GetEntries());
  HBold->SetBinContent(3,h10->GetEntries());
  HBold->SetBinContent(4,h11->GetEntries());
  HBold->SetBinContent(5,h12->GetEntries());
  HBold->SetBinContent(6,h13->GetEntries());
  HBold->SetBinContent(7,h14->GetEntries());
  HBold->SetBinContent(8,h15->GetEntries());
  HBold->SetBinContent(9,h16->GetEntries());

  HBdata->SetBinContent(1,0);
  HBdata->SetBinContent(2,h17->GetEntries());
  HBdata->SetBinContent(3,h18->GetEntries());
  HBdata->SetBinContent(4,h19->GetEntries());
  HBdata->SetBinContent(5,h20->GetEntries());
  HBdata->SetBinContent(6,h21->GetEntries());
  HBdata->SetBinContent(7,h22->GetEntries());
  HBdata->SetBinContent(8,h23->GetEntries());
  HBdata->SetBinContent(9,h24->GetEntries());

  HEnew->SetBinContent(1,0);
  HEnew->SetBinContent(2,h25->GetEntries());
  HEnew->SetBinContent(3,h26->GetEntries());
  HEnew->SetBinContent(4,h27->GetEntries());
  HEnew->SetBinContent(5,h28->GetEntries());  
  HEnew->SetBinContent(6,h29->GetEntries());
  HEnew->SetBinContent(7,h30->GetEntries());
  HEnew->SetBinContent(8,h31->GetEntries());
  HEnew->SetBinContent(9,h32->GetEntries());

  HEold->SetBinContent(1,0);
  HEold->SetBinContent(2,h33->GetEntries());
  HEold->SetBinContent(3,h34->GetEntries());
  HEold->SetBinContent(4,h35->GetEntries());
  HEold->SetBinContent(5,h36->GetEntries());
  HEold->SetBinContent(6,h37->GetEntries());
  HEold->SetBinContent(7,h38->GetEntries());
  HEold->SetBinContent(8,h39->GetEntries());
  HEold->SetBinContent(9,h40->GetEntries());

  HEdata->SetBinContent(1,0);
  HEdata->SetBinContent(2,h41->GetEntries());
  HEdata->SetBinContent(3,h42->GetEntries());
  HEdata->SetBinContent(4,h43->GetEntries());
  HEdata->SetBinContent(5,h44->GetEntries());
  HEdata->SetBinContent(6,h45->GetEntries());
  HEdata->SetBinContent(7,h46->GetEntries());
  HEdata->SetBinContent(8,h47->GetEntries());
  HEdata->SetBinContent(9,h48->GetEntries());


  //Define the canvas and Legends
  TLegend* catLeg0 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c0 = new TCanvas("c0","c0",1000,800);

  TLegend* catLeg1 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c1 = new TCanvas("c1","c1",1000,800);

  TLegend* catLeg2 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c2 = new TCanvas("c2","c2",1000,800);

  TLegend* catLeg3 = new TLegend(0.55,0.7,0.9,0.9);
  TCanvas *c3 = new TCanvas("c3","c3",1000,800);
  
  ////////////////////////////////////////////////////////////////////
  //   Plotting
  ////////////////////////////////////////////////////////////////////

  //HB MC
  c0->cd();
  gPad->SetLogy();

  HBnew->SetLineColor(1);
  HBnew->Draw("hist"); 
  //HBnew->SetMinimum(ymin);
  //HBnew->SetMaximum(ymax);
  HBnew->SetTitle("HB Old and New standard");
  HBnew->GetXaxis()->SetTitle("Charge [fC]");
  HBnew->GetYaxis()->SetTitle("Entries");
  HBnew->SetTitleOffset(1.5,"Y");
  HBnew->SetTitleOffset(1.5,"X");
  HBnew->SetLabelSize(0.05,"Y");
  HBnew->SetLabelSize(0.05,"X");
  //HBnew->SetTitleSize(0.001);
  HBnew->SetName("");
  HBnew->SetStats(false);

  HBold->Draw("hist same");
  HBold->SetLineColor(2);
  
  catLeg0->SetTextSize(0.03);
  catLeg0->AddEntry(HBnew,"HB new standard" ,"l");  
  catLeg0->AddEntry(HBold,"HB old standard" ,"l");  
  catLeg0->Draw();

  //HB data
  c1->cd();
  gPad->SetLogy();

  HBdata->SetLineColor(1);
  HBdata->Draw("hist"); 
  //HBdata->SetMinimum(ymin);
  //HBdata->SetMaximum(ymax);
  HBdata->SetTitle("HB Data");
  HBdata->GetXaxis()->SetTitle("Charge [fC]");
  HBdata->GetYaxis()->SetTitle("Entries");
  HBdata->SetTitleOffset(1.5,"Y");
  HBdata->SetTitleOffset(1.5,"X");
  HBdata->SetLabelSize(0.05,"Y");
  HBdata->SetLabelSize(0.05,"X");
  //HBdata->SetTitleSize(0.001);
  HBdata->SetName("");
  HBdata->SetStats(false);

  catLeg1->SetTextSize(0.03);
  catLeg1->AddEntry(HBdata,"HB data" ,"l");  
  catLeg1->Draw();

  //HE MC
  c2->cd();
  gPad->SetLogy();

  HEnew->SetLineColor(1);
  HEnew->Draw("hist"); 
  //HEnew->SetMinimum(ymin);
  //HEnew->SetMaximum(ymax);
  HEnew->SetTitle("HE Old and New standard");
  HEnew->GetXaxis()->SetTitle("Charge [fC]");
  HEnew->GetYaxis()->SetTitle("Entries");
  HEnew->SetTitleOffset(1.5,"Y");
  HEnew->SetTitleOffset(1.5,"X");
  HEnew->SetLabelSize(0.05,"Y");
  HEnew->SetLabelSize(0.05,"X");
  //HEnew->SetTitleSize(0.001);
  HEnew->SetName("");
  HEnew->SetStats(false);

  HEold->Draw("hist same");
  HEold->SetLineColor(2);
  
  catLeg2->SetTextSize(0.03);
  catLeg2->AddEntry(HEnew,"HE new standard" ,"l");  
  catLeg2->AddEntry(HEold,"HE old standard" ,"l");  
  catLeg2->Draw();

  //HE data
  c3->cd();
  gPad->SetLogy();

  HEdata->SetLineColor(1);
  HEdata->Draw("hist"); 
  //HEdata->SetMinimum(ymin);
  //HEdata->SetMaximum(ymax);
  HEdata->SetTitle("HE Data");
  HEdata->GetXaxis()->SetTitle("Charge [fC]");
  HEdata->GetYaxis()->SetTitle("Entries");
  HEdata->SetTitleOffset(1.5,"Y");
  HEdata->SetTitleOffset(1.5,"X");
  HEdata->SetLabelSize(0.05,"Y");
  HEdata->SetLabelSize(0.05,"X");
  //HEdata->SetTitleSize(0.001);
  HEdata->SetName("");
  HEdata->SetStats(false);

  catLeg3->SetTextSize(0.03);
  catLeg3->AddEntry(HEdata,"HE data" ,"l");  
  catLeg3->Draw();

  //Save Plot
  c0->SaveAs(c0_Save);
  c1->SaveAs(c1_Save);
  c2->SaveAs(c2_Save);
  c3->SaveAs(c3_Save);

}//End of Macro
