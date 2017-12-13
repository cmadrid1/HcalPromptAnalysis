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

void plot_compare_MC_energy_residual(const char *Data_File, const char *MC1_File, const char *MC2_File, const char *Data_Type = "<Data_Type>", const char *MC1_Type = "<MC1_Type>" , const char *MC2_Type = "<MC2_Type>", const char *Name_Save = "MC_data_Hand_residual.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  //Set the plots max and min y-value
  Double_t ymin =0.00000001;
  Double_t ymax =0.75;

  Double_t ymin_SiPM = 0.0001;
  Double_t ymax_SiPM = 0.7;

  Double_t ymin_HF =0.;
  Double_t ymax_HF =1;

  Double_t rymin = -0.9;//1.9
  Double_t rymax =  2.8;

  //Define/Get the Histos to be plotted
  TFile *f1 = new TFile(Data_File);
  if(f1->IsZombie()){
    cout << "Root file: " << Data_File << " not found!" << endl;
    return;
  }
  TFile *f2 = new TFile(MC1_File);
  if(f2->IsZombie()){
    cout << "Root file: " << MC1_File << " not found!" << endl;
    return;
  }
  TFile *f3 = new TFile(MC2_File);
  if(f3->IsZombie()){
    cout << "Root file: " << MC2_File << " not found!" << endl;
    return;
  }

  TH1F *h1 = (TH1F*)f1->Get("pulseShape_DigiHB_HPD");
  TH1F *h2 = (TH1F*)f2->Get("pulseShape_DigiHB_HPD");
  TH1F *h3 = (TH1F*)f3->Get("pulseShape_DigiHB_HPD");

  TH1F *h4 = (TH1F*)f1->Get("pulseShape_DigiHE_HPD");
  TH1F *h5 = (TH1F*)f2->Get("pulseShape_DigiHE_HPD");
  TH1F *h6 = (TH1F*)f3->Get("pulseShape_DigiHE_HPD");

  TH1F *h7 = (TH1F*)f1->Get("pulseShape_DigiHE_SiPM");
  TH1F *h8 = (TH1F*)f2->Get("pulseShape_DigiHE_SiPM");
  TH1F *h9 = (TH1F*)f3->Get("pulseShape_DigiHE_SiPM");

  TH1F *h10 = (TH1F*)f1->Get("pulseShape_DigiHF_QIE10");
  TH1F *h11 = (TH1F*)f2->Get("pulseShape_DigiHF_QIE10");
  TH1F *h12 = (TH1F*)f3->Get("pulseShape_DigiHF_QIE10");

  ////////////////////////////////////////////////////////////////////
  //                Normalizing                                     //
  ////////////////////////////////////////////////////////////////////
  Double_t norm = 1;
  Double_t min  = -0.5;
  Double_t max  = 9.5;
  h1->Scale(norm/h1->Integral(min,max));
  h2->Scale(norm/h2->Integral(min,max));
  h3->Scale(norm/h3->Integral(min,max));
  h4->Scale(norm/h4->Integral(min,max));
  h5->Scale(norm/h5->Integral(min,max));
  h6->Scale(norm/h6->Integral(min,max));
  h7->Scale(norm/h7->Integral(min,max));
  h8->Scale(norm/h8->Integral(min,max));
  h9->Scale(norm/h9->Integral(min,max));
  h10->Scale(norm/h10->Integral(min,max));
  h11->Scale(norm/h11->Integral(min,max));
  h12->Scale(norm/h12->Integral(min,max));

  //Define Residuals HB HPD
  TH1F *r1MC = new TH1F("r1MC","r1MC",10,-0.5,9.5);
  TH1F *r1Hand = new TH1F("r1Hand","r1Hand",10,-0.5,9.5);

  for(int j=1; j<=10; j++){
    r1MC->SetBinContent(j,((h1->Integral(j,j))-(h2->Integral(j,j)))/(h2->Integral(j,j)));
    r1MC->SetBinError(j,errorResidual(j,h1,h2));
  }
  for(int j=1; j<=10; j++){
    r1Hand->SetBinContent(j,((h1->Integral(j,j))-(h3->Integral(j,j)))/(h3->Integral(j,j)));
    r1Hand->SetBinError(j,errorResidual(j,h1,h3));
  }

  //Define Residuals HE HPD
  TH1F *r2MC = new TH1F("r2MC","r2MC",10,-0.5,9.5);
  TH1F *r2Hand = new TH1F("r2Hand","r2Hand",10,-0.5,9.5);

  for(int j=1; j<=10; j++){
    r2MC->SetBinContent(j,((h4->Integral(j,j))-(h5->Integral(j,j)))/(h5->Integral(j,j)));
    r2MC->SetBinError(j,errorResidual(j,h4,h5));
  }
  for(int j=1; j<=10; j++){
    r2Hand->SetBinContent(j,((h4->Integral(j,j))-(h6->Integral(j,j)))/(h6->Integral(j,j)));
    r2Hand->SetBinError(j,errorResidual(j,h4,h6));
  }

  //Define Residuals HE SiPM
  TH1F *r3MC = new TH1F("r3MC","r3MC",10,-0.5,9.5);
  TH1F *r3Hand = new TH1F("r3Hand","r3Hand",10,-0.5,9.5);

  for(int j=1; j<=10; j++){
    r3MC->SetBinContent(j,((h7->Integral(j,j))-(h8->Integral(j,j)))/(h8->Integral(j,j)));
    r3MC->SetBinError(j,errorResidual(j,h7,h8));
  }
  for(int j=1; j<=10; j++){
    r3Hand->SetBinContent(j,((h7->Integral(j,j))-(h9->Integral(j,j)))/(h9->Integral(j,j)));
    r3Hand->SetBinError(j,errorResidual(j,h7,h9));
  }

  //Define Residuals HF PMT
  TH1F *r4MC = new TH1F("r4MC","r4MC",10,-0.5,9.5);
  TH1F *r4Hand = new TH1F("r4Hand","r4Hand",10,-0.5,9.5);

  for(int j=1; j<=3; j++){
    r4MC->SetBinContent(j,((h10->Integral(j,j))-(h11->Integral(j,j)))/(h11->Integral(j,j)));
    r4MC->SetBinError(j,errorResidual(j,h10,h11));
  }
  for(int j=1; j<=3; j++){
    r4Hand->SetBinContent(j,((h10->Integral(j,j))-(h12->Integral(j,j)))/(h12->Integral(j,j)));
    r4Hand->SetBinError(j,errorResidual(j,h10,h12));
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

  //gBenchmark->Start("MC_test");

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
  //   Plotting MC Digi vs MC Hand Integrated  for  HB HPD          //
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up1->cd();

  //Data
  h1->SetLineColor(4);
  h1->Draw("hist"); 
  h1->SetMinimum(ymin);
  h1->SetMaximum(ymax);
  //h1->GetXaxis()->SetTitle("Time Step");
  h1->GetYaxis()->SetTitle("A.U.");
  h1->SetTitleOffset(1.5,"Y");
  h1->SetTitle("MC vs MC Hand Integrated  HB_HPD");
  h1->SetName("");
  h1->SetStats(false);

  catLeg0->SetTextSize(0.03);
  catLeg0->AddEntry(h1, Data_Type ,"l");  
  catLeg0->Draw();

  //MC1 
  h2->SetLineColor(2);
  h2->Draw("hist same");
  catLeg0->AddEntry(h2,MC1_Type,"l");

  //MC2
  h3->SetLineColor(1);
  h3->Draw("hist same");
  catLeg0->AddEntry(h3,MC2_Type,"l");

  //Down
  pad_dw1->cd();
  gPad->SetGrid();
  r1MC->SetLineColor(2);
  r1Hand->SetLineColor(1);

  r1MC->GetXaxis()->SetTitle("Time Step");
  r1MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r1MC->SetTitle("");
  r1MC->SetName("");
  r1MC->SetMinimum(rymin);
  r1MC->SetMaximum(rymax);
  r1MC->SetTitleSize(0.001);
  r1MC->SetTitleSize(0.17,"X");
  r1MC->SetTitleSize(0.16,"Y");
  r1MC->SetTitleOffset(0.65,"X");
  r1MC->SetTitleOffset(0.35,"Y");
  r1MC->SetLabelSize(0.12,"X");
  r1MC->SetLabelSize(0.12,"Y");
  r1MC->SetStats(false);

  r1MC->Draw("E1");
  r1Hand->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //   Plotting MC Digi vs MC Hand Integrated  for  HE HPD          //
  ////////////////////////////////////////////////////////////////////
  
  //Up
  pad_up2->cd();
  
  //Data
  h4->SetLineColor(4);
  h4->Draw("hist"); 
  h4->SetMinimum(ymin);
  h4->SetMaximum(ymax);
  //h4->GetXaxis()->SetTitle("Time Step");
  h4->GetYaxis()->SetTitle("A.U.");
  h4->SetTitleOffset(1.5,"Y");
  h4->SetTitle("MC vs MC Hand Integrated  HE_HPD");
  h4->SetName("");
  h4->SetStats(false);

  catLeg1->SetTextSize(0.03);
  catLeg1->AddEntry(h4,Data_Type,"l");  
  catLeg1->Draw();

  //MC1 
  h5->SetLineColor(2);
  h5->Draw("hist same");
  catLeg1->AddEntry(h5,MC1_Type,"l");

  //MC2
  h6->SetLineColor(1);
  h6->Draw("hist same");
  catLeg1->AddEntry(h6,MC2_Type,"l");

  //Down
  pad_dw2->cd();
  gPad->SetGrid();
  r2MC->SetLineColor(2);
  r2Hand->SetLineColor(1);

  r2MC->GetXaxis()->SetTitle("Time Step");
  r2MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r2MC->SetTitle("");
  r2MC->SetName("");
  r2MC->SetMinimum(rymin);
  r2MC->SetMaximum(rymax);
  r2MC->SetTitleSize(0.001);
  r2MC->SetTitleSize(0.17,"X");
  r2MC->SetTitleSize(0.16,"Y");
  r2MC->SetTitleOffset(0.65,"X");
  r2MC->SetTitleOffset(0.35,"Y");
  r2MC->SetLabelSize(0.12,"X");
  r2MC->SetLabelSize(0.12,"Y");
  r2MC->SetStats(false);

  r2MC->Draw("E1");
  r2Hand->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //     Plotting MC Digi vs MC Hand Integrated  for  HE SiPM       //
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up3->cd();
  
  //Data
  h7->SetLineColor(4);
  h7->Draw("hist"); 
  h7->SetMinimum(ymin_SiPM);
  h7->SetMaximum(ymax_SiPM);
  //h7->GetXaxis()->SetTitle("Time Step");
  h7->GetYaxis()->SetTitle("A.U.");
  h7->SetTitleOffset(1.4,"Y");
  h7->SetTitle("Data vs MC HE_SiPM");
  h7->SetName("");
  h7->SetStats(false);

  catLeg2->SetTextSize(0.03);
  catLeg2->AddEntry(h7,Data_Type,"l");  
  catLeg2->Draw();

  //MC1
  h8->SetLineColor(2);
  h8->Draw("hist same");
  catLeg2->AddEntry(h8,MC1_Type,"l");

  //MC2
  h9->SetLineColor(1);
  h9->Draw("hist same");
  catLeg2->AddEntry(h9,MC2_Type,"l");

  //Down
  pad_dw3->cd();
  gPad->SetGrid();
  r3MC->SetLineColor(2);
  r3Hand->SetLineColor(1);

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
  r3MC->SetTitleOffset(0.32,"Y");
  r3MC->SetLabelSize(0.12,"X");
  r3MC->SetLabelSize(0.12,"Y");
  r3MC->SetStats(false);

  r3MC->Draw("E1");
  r3Hand->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //      Plotting MC Digi vs MC Hand Integrated  for  Hf_QIE10     //
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up4->cd();
  
  //Data
  h10->SetLineColor(4);
  h10->Draw("hist"); 
  h10->SetMinimum(ymin_HF);
  h10->SetMaximum(ymax_HF);
  //h10->GetXaxis()->SetTitle("Time Step");
  h10->GetYaxis()->SetTitle("A.U.");
  h10->SetTitleOffset(1.5,"Y");
  h10->SetTitle("MC vs MC Hand Integrated  HF_QIE10");
  h10->SetName("");
  h10->SetStats(false);

  catLeg3->SetTextSize(0.03);
  catLeg3->AddEntry(h10,Data_Type,"l");  
  catLeg3->Draw();

  //MC1
  h11->SetLineColor(2);
  h11->Draw("hist same");
  catLeg3->AddEntry(h11,MC1_Type,"l");

  //MC2
  h12->SetLineColor(1);
  h12->Draw("hist same");
  catLeg3->AddEntry(h12,MC2_Type,"l");

  //Down
  pad_dw4->cd();
  gPad->SetGrid();
  r4MC->SetLineColor(2);
  r4Hand->SetLineColor(1);

  r4MC->GetXaxis()->SetTitle("Time Step");
  r4MC->GetYaxis()->SetTitle("(Data/MC)-1");
  r4MC->SetTitle("");
  r4MC->SetName("");
  r4MC->SetTitleSize(0.001);
  r4MC->SetMinimum(rymin);
  r4MC->SetMaximum(rymax);
  r4MC->SetTitleSize(0.17,"X");
  r4MC->SetTitleSize(0.16,"Y");
  r4MC->SetTitleOffset(0.65,"X");
  r4MC->SetTitleOffset(0.35,"Y");
  r4MC->SetLabelSize(0.12,"X");
  r4MC->SetLabelSize(0.12,"Y");
  r4MC->SetStats(false);

  r4MC->Draw("E1");
  r4Hand->Draw("E1 same");

  h7->Print("all");
  h8->Print("all");
  h9->Print("all");
  r3MC->Print("all");
  r3Hand->Print("all");

  //Save Plot
  canvas->SaveAs(Name_Save);

}//End of Macro
