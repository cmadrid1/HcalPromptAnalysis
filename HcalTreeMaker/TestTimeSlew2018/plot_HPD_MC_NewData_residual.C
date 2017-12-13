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
  double A     = a -b;
  double da    = hdata->GetBinError(j);
  double db    = hmc->GetBinError(j);
  double dA    = sqrt(da*da + db*db);
 
  double error = (A/a)*sqrt((dA/A)*(dA/A)+(db/b)*(db/b)); 
  return error;
}

void plot_HPD_MC_NewData_residual(bool Low=true, bool HB=true,  const char *MC1_Type = "standard", const char *MC2_Type = "No TS",const char *Data_Type = "<Data_Type>",const char *Name_Save = "MC_data_residual.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  //Set the plots max and min y-value
  Double_t ymin =0.;
  Double_t ymax =0.8;

  Double_t rymin = -0.35;//1.9
  Double_t rymax =  0.35;

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
 
  if(Low&&HB){
    h1 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHB_HPD");
    h2 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHB_HPD");
    h3 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHB_HPD");
    h4 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHB_HPD");
    h5  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_10_25.root" ,"pulseShape_DigiHB_HPD");
    h6  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_25_50.root" ,"pulseShape_DigiHB_HPD");
    h7  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_50_75.root" ,"pulseShape_DigiHB_HPD");
    h8  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_75_100.root","pulseShape_DigiHB_HPD");
    h9  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHB_HPD");
    h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHB_HPD");
    h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHB_HPD");
    h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHB_HPD");

    h1->SetTitle("HB: 10 < Charge TS4+TS5 < 25 [fC]");
    h2->SetTitle("HB: 25 < Charge TS4+TS5 < 50 [fC]");
    h3->SetTitle("HB: 50 < Charge TS4+TS5 < 75 [fC]");
    h4->SetTitle("HB: 75 < Charge TS4+TS5 < 100 [fC]");
  }     
  if(Low&&!HB){
    h1 = defineHist("Output_Histo_standard_10_25.root"            ,"pulseShape_DigiHE_HPD");
    h2 = defineHist("Output_Histo_standard_25_50.root"            ,"pulseShape_DigiHE_HPD");
    h3 = defineHist("Output_Histo_standard_50_75.root"            ,"pulseShape_DigiHE_HPD");
    h4 = defineHist("Output_Histo_standard_75_100.root"           ,"pulseShape_DigiHE_HPD");
    h5 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_10_25.root"  ,"pulseShape_DigiHE_HPD");
    h6 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_25_50.root"  ,"pulseShape_DigiHE_HPD");
    h7 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_50_75.root"  ,"pulseShape_DigiHE_HPD");
    h8 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_75_100.root" ,"pulseShape_DigiHE_HPD");
    h9  = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_10_25.root"          ,"pulseShape_DigiHE_HPD");
    h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_25_50.root"          ,"pulseShape_DigiHE_HPD");
    h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_50_75.root"          ,"pulseShape_DigiHE_HPD");
    h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_75_100.root"         ,"pulseShape_DigiHE_HPD");

    h1->SetTitle("HE: 10 < Charge TS4+TS5 < 25 [fC]");
    h2->SetTitle("HE: 25 < Charge TS4+TS5 < 50 [fC]");
    h3->SetTitle("HE: 50 < Charge TS4+TS5 < 75 [fC]");
    h4->SetTitle("HE: 75 < Charge TS4+TS5 < 100 [fC]");
  }
  if(!Low&&HB){
    h1 = defineHist("Output_Histo_standard_100_150.root"           ,"pulseShape_DigiHB_HPD");
    h2 = defineHist("Output_Histo_standard_150_200.root"           ,"pulseShape_DigiHB_HPD");
    h3 = defineHist("Output_Histo_standard_200_300.root"           ,"pulseShape_DigiHB_HPD");
    h4 = defineHist("Output_Histo_standard_300_inf.root"           ,"pulseShape_DigiHB_HPD");
    h5 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHB_HPD");
    h6 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHB_HPD");
    h7 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHB_HPD");
    h8 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHB_HPD");
    h9 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"          ,"pulseShape_DigiHB_HPD");
    h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"         ,"pulseShape_DigiHB_HPD");
    h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"         ,"pulseShape_DigiHB_HPD");
    h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"         ,"pulseShape_DigiHB_HPD");

    h1->SetTitle("HB: 100 < Charge TS4+TS5 < 150 [fC]");
    h2->SetTitle("HB: 150 < Charge TS4+TS5 < 200 [fC]");
    h3->SetTitle("HB: 200 < Charge TS4+TS5 < 300 [fC]");
    h4->SetTitle("HB: 300 < Charge TS4+TS5 < inf [fC]");
  } 
  if(!Low&&!HB){
    h1 = defineHist("Output_Histo_standard_100_150.root"           ,"pulseShape_DigiHE_HPD");
    h2 = defineHist("Output_Histo_standard_150_200.root"           ,"pulseShape_DigiHE_HPD");
    h3 = defineHist("Output_Histo_standard_200_300.root"           ,"pulseShape_DigiHE_HPD");
    h4 = defineHist("Output_Histo_standard_300_inf.root"           ,"pulseShape_DigiHE_HPD");
    h5 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_100_150.root" ,"pulseShape_DigiHE_HPD");
    h6 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_150_200.root" ,"pulseShape_DigiHE_HPD");
    h7 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_200_300.root" ,"pulseShape_DigiHE_HPD");
    h8 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_PulseShape_DatavsMC/src/HcalPromptAnalysis/HcalTreeMaker/chi2/50GeV/Output_Histo_standard_300_inf.root" ,"pulseShape_DigiHE_HPD");
    h9 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_100_150.root"          ,"pulseShape_DigiHE_HPD");
    h10 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_150_200.root"         ,"pulseShape_DigiHE_HPD");
    h11 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_200_300.root"         ,"pulseShape_DigiHE_HPD");
    h12 = defineHist("/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_Data_TimeSlew_Fix/src/HcalPromptAnalysis/HcalTreeMaker/TimeSlew/Data/Histo_NewData_300_inf.root"         ,"pulseShape_DigiHE_HPD");

    h1->SetTitle("HE: 100 < Charge TS4+TS5 < 150 [fC]");
    h2->SetTitle("HE: 150 < Charge TS4+TS5 < 200 [fC]");
    h3->SetTitle("HE: 200 < Charge TS4+TS5 < 300 [fC]");
    h4->SetTitle("HE: 300 < Charge TS4+TS5 < inf [fC]");
  }
  //Define Residuals Top Left
  TH1F *r1MC = new TH1F("r1MC","r1MC",10,-0.5,9.5);
  TH1F *r1TS = new TH1F("r1TS","r1TS",10,-0.5,9.5);

  for(int j=1; j<=10; j++){
    r1MC->SetBinContent(j,((h9->GetBinContent(j))-(h1->GetBinContent(j)))/(h1->GetBinContent(j)));
    r1MC->SetBinError(j,errorResidual(j,h9,h1));
    //std::cout<<errorResidual(j,h9,h1)<<endl;
  }
  for(int j=0; j<=11; j++){
    r1TS->SetBinContent(j,((h9->GetBinContent(j))-(h5->GetBinContent(j)))/(h5->GetBinContent(j)));
    r1TS->SetBinError(j,errorResidual(j,h9,h5));
  }

  //Define Residuals Top Right
  TH1F *r2MC = new TH1F("r2MC","r2MC",10,-0.5,9.5);
  TH1F *r2TS = new TH1F("r2TS","r2TS",10,-0.5,9.5);

  for(int j=0; j<=11; j++){
    r2MC->SetBinContent(j,((h10->Integral(j,j))-(h2->Integral(j,j)))/(h2->Integral(j,j)));
    r2MC->SetBinError(j,errorResidual(j,h10,h2));
  }
  for(int j=0; j<=11; j++){
    r2TS->SetBinContent(j,((h10->Integral(j,j))-(h6->Integral(j,j)))/(h6->Integral(j,j)));
    r2TS->SetBinError(j,errorResidual(j,h10,h6));
  }

  //Define Residuals Bottom Left
  TH1F *r3MC = new TH1F("r3MC","r3MC",10,-0.5,9.5);
  TH1F *r3TS = new TH1F("r3TS","r3TS",10,-0.5,9.5);

  for(int j=0; j<=11; j++){
    r3MC->SetBinContent(j,((h11->Integral(j,j))-(h3->Integral(j,j)))/(h3->Integral(j,j)));
    r3MC->SetBinError(j,errorResidual(j,h11,h3));
  }
  for(int j=0; j<=11; j++){
    r3TS->SetBinContent(j,((h11->Integral(j,j))-(h7->Integral(j,j)))/(h7->Integral(j,j)));
    r3TS->SetBinError(j,errorResidual(j,h11,h7));
  }

  //Define Residuals Bottom Right
  TH1F *r4MC = new TH1F("r4MC","r4MC",10,-0.5,9.5);
  TH1F *r4TS = new TH1F("r4TS","r4TS",10,-0.5,9.5);

  for(int j=0; j<=11; j++){
    r4MC->SetBinContent(j,((h12->Integral(j,j))-(h4->Integral(j,j)))/(h4->Integral(j,j)));
    r4MC->SetBinError(j,errorResidual(j,h12,h4));
  }
  for(int j=0; j<=11; j++){
    r4TS->SetBinContent(j,((h12->Integral(j,j))-(h8->Integral(j,j)))/(h8->Integral(j,j)));
    r4TS->SetBinError(j,errorResidual(j,h12,h8));
  }

  //Define the Legends
  TLegend* catLeg0 = new TLegend(0.55,0.7,0.9,0.9);
  TLegend* catLeg1 = new TLegend(0.55,0.7,0.9,0.9);
  TLegend* catLeg2 = new TLegend(0.55,0.7,0.9,0.9);
  TLegend* catLeg3 = new TLegend(0.55,0.7,0.9,0.9);

  //
  // Define canvas/pads
  //
  
  TCanvas *canvas = new TCanvas("canvas","canvas",1000,800);

  TPad *pad1 = new TPad("pad1","This is pad1",0.,0.5,0.5,1.);
  TPad *pad2 = new TPad("pad2","This is pad2",0.5,0.5,1.,1.);
  TPad *pad3 = new TPad("pad3","This is pad3",0.,0.,0.5,0.5);
  TPad *pad4 = new TPad("pad4","This is pad4",0.5,0.,1.,0.5);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();
  pad4->Draw();

  //
  //define the size for the individual pads
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height     = (1. - up_height) * dw_correction;
  double dw_height_offset = -0.025; // KH, added to put the bottom one closer to the top panel

  //Pads1
  pad1->cd();
  TPad *pad_up1 = new TPad("pad_up1","pad_up1",0., 1. - up_height,1., 1.);
  TPad *pad_dw1 = new TPad("pad_dw1","pad_dw1",0.,0.,1., dw_height+dw_height_offset);
  pad_up1->Draw();
  pad_dw1->Draw();
  
  pad_up1->SetFrameFillColor(0);
  pad_up1->SetFillColor(0);
  pad_up1->SetTopMargin(0.12);
  pad_up1->SetLeftMargin(0.1);
  
  pad_dw1->SetFillColor(0);
  pad_dw1->SetFrameFillColor(0);
  pad_dw1->SetBottomMargin(0.35);
  pad_dw1->SetTopMargin(0);
  pad_dw1->SetLeftMargin(0.1);

  //Pads2
  pad2->cd();
  TPad *pad_up2 = new TPad("pad_up2","pad_up2",0., 1. - up_height,1., 1.);
  TPad *pad_dw2 = new TPad("pad_dw2","pad_dw2",0.,0.,1., dw_height+dw_height_offset);
  pad_up2->Draw();
  pad_dw2->Draw();
  
  pad_up2->SetFrameFillColor(0);
  pad_up2->SetFillColor(0);
  pad_up2->SetTopMargin(0.12);
  pad_up2->SetLeftMargin(0.1);
  
  pad_dw2->SetFillColor(0);
  pad_dw2->SetFrameFillColor(0);
  pad_dw2->SetBottomMargin(0.35);
  pad_dw2->SetTopMargin(0);
  pad_dw2->SetLeftMargin(0.1);

  //Pads3
  pad3->cd();
  TPad *pad_up3 = new TPad("pad_up3","pad_up3",0., 1. - up_height,1., 1.);
  TPad *pad_dw3 = new TPad("pad_dw3","pad_dw3",0.,0.,1., dw_height+dw_height_offset);
  pad_up3->Draw();
  pad_dw3->Draw();
  
  pad_up3->SetFrameFillColor(0);
  pad_up3->SetFillColor(0);
  pad_up3->SetTopMargin(0.12);
  pad_up3->SetLeftMargin(0.1);
  
  pad_dw3->SetFillColor(0);
  pad_dw3->SetFrameFillColor(0);
  pad_dw3->SetBottomMargin(0.35);
  pad_dw3->SetTopMargin(0);
  pad_dw3->SetLeftMargin(0.1);

  //Pads4
  pad4->cd();
  TPad *pad_up4 = new TPad("pad_up4","pad_up4",0., 1. - up_height,1., 1.);
  TPad *pad_dw4 = new TPad("pad_dw4","pad_dw4",0.,0.,1., dw_height+dw_height_offset);
  pad_up4->Draw();
  pad_dw4->Draw();
  
  pad_up4->SetFrameFillColor(0);
  pad_up4->SetFillColor(0);
  pad_up4->SetTopMargin(0.12);
  pad_up4->SetLeftMargin(0.1);
  
  pad_dw4->SetFillColor(0);
  pad_dw4->SetFrameFillColor(0);
  pad_dw4->SetBottomMargin(0.35);
  pad_dw4->SetTopMargin(0);
  pad_dw4->SetLeftMargin(0.1);
  
  ////////////////////////////////////////////////////////////////////
  //   Plotting Top Left
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up1->cd();

  //MC1
  h1->SetLineColor(2);
  h1->Draw("hist"); 
  //h1->Draw("e same"); 
  h1->SetMinimum(ymin);
  h1->SetMaximum(ymax);
  //h1->GetXaxis()->SetTitle("Time Step");
  h1->GetYaxis()->SetTitle("A.U.");
  h1->SetTitleOffset(1.5,"Y");
  h1->SetTitleOffset(1.5,"X");
  //h1->SetLabelSize(0.05,"Y");
  //h1->SetLabelSize(0.05,"X");
  h1->SetTitleSize(0.001);
  h1->SetName("");
  h1->SetStats(false);

  catLeg0->SetTextSize(0.03);
  catLeg0->Draw();

  //Data
  h9->SetLineColor(4);
  h9->SetLineStyle(2);
  h9->Draw("hist same");

  //MC2 
  h5->SetLineColor(1);
  h5->Draw("hist same");

  catLeg0->AddEntry(h1,MC1_Type ,"l");  
  catLeg0->AddEntry(h5,MC2_Type,"l");
  catLeg0->AddEntry(h9,Data_Type,"l");

  //Down
  pad_dw1->cd();
  gPad->SetGrid();
  r1MC->SetLineColor(2);
  r1TS->SetLineColor(1);

  r1MC->GetXaxis()->SetTitle("Time Step");
  r1MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r1MC->SetTitle("");
  r1MC->SetName("");
  r1MC->SetMinimum(rymin);
  r1MC->SetMaximum(rymax);
  r1MC->SetTitleSize(0.001);
  r1MC->SetTitleSize(0.17,"X");
  r1MC->SetTitleSize(0.16,"Y");
  r1MC->SetTitleOffset(0.7,"X");
  r1MC->SetTitleOffset(0.3,"Y");
  r1MC->SetLabelSize(0.12,"X");
  r1MC->SetLabelSize(0.12,"Y");
  r1MC->SetStats(false);

  r1MC->Draw("E1");
  r1TS->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //   Plotting Top Right
  ////////////////////////////////////////////////////////////////////
  
  //Up
  pad_up2->cd();
  
  //MC1
  h2->SetLineColor(2);
  h2->Draw("hist"); 
  h2->SetMinimum(ymin);
  h2->SetMaximum(ymax);
  //h2->GetXaxis()->SetTitle("Time Step");
  h2->GetYaxis()->SetTitle("A.U.");
  h2->SetTitleOffset(1.5,"Y");
  h2->SetTitleOffset(1.5,"X");
  //h2->SetLabelSize(0.05,"Y");
  //h2->SetLabelSize(0.05,"X");
  h2->SetTitleSize(0.001);
  h2->SetName("");
  h2->SetStats(false);

  catLeg1->SetTextSize(0.03);
  catLeg1->Draw();

  //Data
  h10->SetLineColor(4);
  h10->SetLineStyle(2);
  h10->Draw("hist same");

  //MC2 
  h6->SetLineColor(1);
  h6->Draw("hist same");

  catLeg1->AddEntry(h2,MC1_Type,"l");  
  catLeg1->AddEntry(h6,MC2_Type,"l");
  catLeg1->AddEntry(h10,Data_Type,"l");

  //Down
  pad_dw2->cd();
  gPad->SetGrid();
  r2MC->SetLineColor(2);
  r2TS->SetLineColor(1);

  r2MC->GetXaxis()->SetTitle("Time Step");
  r2MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r2MC->SetTitle("");
  r2MC->SetName("");
  r2MC->SetMinimum(rymin);
  r2MC->SetMaximum(rymax);
  r2MC->SetTitleSize(0.001);
  r2MC->SetTitleSize(0.17,"X");
  r2MC->SetTitleSize(0.16,"Y");
  r2MC->SetTitleOffset(0.7,"X");
  r2MC->SetTitleOffset(0.3,"Y");
  r2MC->SetLabelSize(0.12,"X");
  r2MC->SetLabelSize(0.12,"Y");
  r2MC->SetStats(false);

  r2MC->Draw("E1");
  r2TS->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //     Plotting Bottom Left
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up3->cd();
  
  //MC1
  h3->SetLineColor(2);
  h3->Draw("hist"); 
  h3->SetMinimum(ymin);
  h3->SetMaximum(ymax);
  //h3->GetXaxis()->SetTitle("Time Step");
  h3->GetYaxis()->SetTitle("A.U.");
  h3->SetTitleOffset(1.5,"X");
  //h3->SetLabelSize(0.05,"Y");
  //h3->SetLabelSize(0.05,"X");
  h3->SetTitleSize(0.001);
  h3->SetTitleOffset(1.5,"Y");
  h3->SetName("");
  h3->SetStats(false);

  catLeg2->SetTextSize(0.03);
  catLeg2->Draw();

  //Data
  h11->SetLineColor(4);
  h11->SetLineStyle(2);
  h11->Draw("hist same");

  //MC2
  h7->SetLineColor(1);
  h7->Draw("hist same");

  catLeg2->AddEntry(h3,MC1_Type,"l");  
  catLeg2->AddEntry(h7,MC2_Type,"l");
  catLeg2->AddEntry(h11,Data_Type,"l");

  //Down
  pad_dw3->cd();
  gPad->SetGrid();
  r3MC->SetLineColor(2);
  r3TS->SetLineColor(1);

  r3MC->GetXaxis()->SetTitle("Time Step");
  r3MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r3MC->SetTitle("");
  r3MC->SetName("");
  r3MC->SetMinimum(rymin);
  r3MC->SetMaximum(rymax);
  r3MC->SetTitleSize(0.001);
  r3MC->SetTitleSize(0.17,"X");
  r3MC->SetTitleSize(0.16,"Y");
  r3MC->SetTitleOffset(0.7,"X");
  r3MC->SetTitleOffset(0.3,"Y");
  r3MC->SetLabelSize(0.12,"X");
  r3MC->SetLabelSize(0.12,"Y");
  r3MC->SetStats(false);

  r3MC->Draw("E1");
  r3TS->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //      Plotting Bottom Right
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up4->cd();
  
  //MC1
  h4->SetLineColor(2);
  h4->Draw("hist"); 
  h4->SetMinimum(ymin);
  h4->SetMaximum(ymax);
  //h4->GetXaxis()->SetTitle("Time Step");
  h4->GetYaxis()->SetTitle("A.U.");
  h4->SetTitleOffset(1.5,"Y");
  h4->SetTitleOffset(1.5,"X");
  //h4->SetLabelSize(0.05,"Y");
  //h4->SetLabelSize(0.05,"X");
  h4->SetTitleSize(0.001);
  h4->SetName("");
  h4->SetStats(false);

  catLeg3->SetTextSize(0.03);
  catLeg3->Draw();

  //Data
  h12->SetLineColor(4);
  h12->SetLineStyle(2);
  h12->Draw("hist same");

  //MC2
  h8->SetLineColor(1);
  h8->Draw("hist same");

  catLeg3->AddEntry(h4,MC1_Type,"l");  
  catLeg3->AddEntry(h8,MC2_Type,"l");
  catLeg3->AddEntry(h12,Data_Type,"l");

  //Down
  pad_dw4->cd();
  gPad->SetGrid();
  r4MC->SetLineColor(2);
  r4TS->SetLineColor(1);

  r4MC->GetXaxis()->SetTitle("Time Step");
  r4MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r4MC->SetTitle("");
  r4MC->SetName("");
  r4MC->SetTitleSize(0.001);
  r4MC->SetMinimum(rymin);
  r4MC->SetMaximum(rymax);
  r4MC->SetTitleSize(0.17,"X");
  r4MC->SetTitleSize(0.16,"Y");
  r4MC->SetTitleOffset(0.7,"X");
  r4MC->SetTitleOffset(0.3,"Y");
  r4MC->SetLabelSize(0.12,"X");
  r4MC->SetLabelSize(0.12,"Y");
  r4MC->SetStats(false);

  r4MC->Draw("E1");
  r4TS->Draw("E1 same");

  //h1->Print("all");
  //h2->Print("all");

  //Save Plot
  canvas->SaveAs(Name_Save);

}//End of Macro
