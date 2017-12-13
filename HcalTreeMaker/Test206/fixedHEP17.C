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

void fixedHEP17(const char *Data_File, const char *MC1_File, const char *MC2_File, const char *Data_Type = "<Data_Type>", const char *MC1_Type = "<MC1_Type>" , const char *MC2_Type = "<MC2_Type>", const char *Name_Save = "MC_data_Hand_residual.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  //Set the plots max and min y-value
  Double_t ymin_SiPM = 0.0001;
  Double_t ymax_SiPM = 0.7;

  Double_t ymin_SiPM_log = 0.0001;
  Double_t ymax_SiPM_log = 10;

  Double_t rymin = -0.39;//1.9
  Double_t rymax =  0.39;

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

  TH1F *h1 = (TH1F*)f1->Get("pulseShape_DigiHE_SiPM");
  TH1F *h2 = (TH1F*)f2->Get("pulseShape_DigiHE_SiPM");
  TH1F *h3 = (TH1F*)f3->Get("pulseShape_DigiHE_SiPM");

  ////////////////////////////////////////////////////////////////////
  //                Normalizing                                     //
  ////////////////////////////////////////////////////////////////////
  Double_t norm = 1;
  Double_t min  = -0.5;
  Double_t max  = 9.5;
  h1->Scale(norm/h1->Integral(min,max));
  h2->Scale(norm/h2->Integral(min,max));
  h3->Scale(norm/h3->Integral(min,max));

  //Define Residuals HE SiPM
  TH1F *rMCold = new TH1F("rMCold","rMCold",10,-0.5,9.5);
  TH1F *rMCnew = new TH1F("rMCnew","rMCnew",10,-0.5,9.5);

  for(int j=1; j<=10; j++){
    rMCold->SetBinContent(j,((h1->Integral(j,j))-(h2->Integral(j,j)))/(h2->Integral(j,j)));
    rMCold->SetBinError(j,errorResidual(j,h1,h2));
  }
  for(int j=1; j<=10; j++){
    rMCnew->SetBinContent(j,((h1->Integral(j,j))-(h3->Integral(j,j)))/(h3->Integral(j,j)));
    rMCnew->SetBinError(j,errorResidual(j,h1,h3));
  }

  //Define the Legends
  TLegend* catLeg1 = new TLegend(0.55,0.7,0.9,0.9);

  //
  // Define canvas/pads
  //
  
  TCanvas *canvas = new TCanvas("canvas","canvas",1200,600);

  //gBenchmark->Start("MC_test");


  TPad *pad1 = new TPad("pad2","This is pad2",0.,0.,0.5,1.);
  TPad *pad2 = new TPad("pad1","This is pad1",0.5,0,1.,1.);
  pad1->Draw();
  pad2->Draw();

  //
  //define the size for the individual pads
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height     = (1. - up_height) * dw_correction;
  double dw_height_offset = -0.025; // KH, added to put the bottom one closer to the top panel

  //Pad 1
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

  //Pad 2
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
  
  ////////////////////////////////////////////////////////////////////
  //     Plotting MC Digi vs MC Hand Integrated  for  HE SiPM       //
  ////////////////////////////////////////////////////////////////////

  //Up
  pad_up1->cd();
  
  //Data
  h1->SetLineColor(4);
  h1->Draw("hist"); 
  h1->SetMinimum(ymin_SiPM);
  h1->SetMaximum(ymax_SiPM);
  //h1->GetXaxis()->SetTitle("Time Step");
  h1->GetYaxis()->SetTitle("A.U.");
  h1->SetTitleOffset(1.4,"Y");
  h1->SetTitle("Data vs MC HE_SiPM");
  h1->SetName("");
  h1->SetStats(false);

  catLeg1->SetTextSize(0.03);
  catLeg1->AddEntry(h1,Data_Type,"l");  
  catLeg1->Draw();

  //MC Old
  h2->SetLineColor(2);
  h2->Draw("hist same");
  catLeg1->AddEntry(h2,MC1_Type,"l");

  //MC New
  h3->SetLineColor(1);
  h3->Draw("hist same");
  catLeg1->AddEntry(h3,MC2_Type,"l");

  //Down
  pad_dw1->cd();
  gPad->SetGrid();
  rMCold->SetLineColor(2);
  rMCnew->SetLineColor(1);

  rMCold->GetXaxis()->SetTitle("Time Step");
  rMCold->GetYaxis()->SetTitle("(Data/MC)-1");
  rMCold->SetTitle("");
  rMCold->SetName("");
  rMCold->SetMinimum(rymin);
  rMCold->SetMaximum(rymax);
  rMCold->SetTitleSize(0.001);
  rMCold->SetTitleSize(0.17,"X");
  rMCold->SetTitleSize(0.16,"Y");
  rMCold->SetTitleOffset(0.7,"X");
  rMCold->SetTitleOffset(0.32,"Y");
  rMCold->SetLabelSize(0.12,"X");
  rMCold->SetLabelSize(0.12,"Y");
  rMCold->SetStats(false);

  rMCold->Draw("E1");
  rMCnew->Draw("E1 same");

  ////////////////////////////////////////////////////////////////////
  //     Plotting MC Digi vs MC Hand Integrated  for  Log HE SiPM   //
  ////////////////////////////////////////////////////////////////////
  
  //Up
  pad_up2->cd();
  gPad->SetLogy();

  //MC Old
  h2->Draw("hist");
  h2->SetMinimum(ymin_SiPM_log);
  h2->SetMaximum(ymax_SiPM_log);
  h2->GetYaxis()->SetTitle("A.U.");
  h2->SetTitleOffset(1.4,"Y");
  h2->SetTitle("Data vs MC HE_SiPM");
  h2->SetName("");
  h2->SetStats(false);

  catLeg1->Draw();

  //Data
  h1->Draw("hist same"); 

  //MC New
  h3->Draw("hist same");

  //Down
  pad_dw2->cd();
  gPad->SetGrid();

  rMCold->Draw("E1");
  rMCnew->Draw("E1 same");

  //h1->Print("all");
  //h2->Print("all");
  //h3->Print("all");
  //rMCold->Print("all");
  //rMCnew->Print("all");

  //Save Plot
  canvas->SaveAs(Name_Save);

}//End of Macro
