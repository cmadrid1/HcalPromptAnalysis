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

TH1F* defineTH1F(const char *file="",const char *branch=""){
  TFile *f = new TFile(file);
  TH1F *h = (TH1F*)f->Get(branch);
  return h;
}
TH2F* defineTH2F(const char *file="",const char *branch=""){
  TFile *f = new TFile(file);
  TH2F *h = (TH2F*)f->Get(branch);
  return h;
}
void plot_RecHit(const char *HB_Title = "HB_Title",const char *HE_Title = "HE_Title",const char *HB_Name_Save = "HB_NewTimeSlew_Reco.pdf",const char *HE_Name_Save = "HB_NewTimeSlew_Reco.pdf"){

  ////////////////////////////////////////////////////////////////////
  //                 Define everything that is needed               //
  ////////////////////////////////////////////////////////////////////

  double ychi_min =   0.0;
  double ychi_max =   5.0;

  double ytime_min =  -5.0;
  double ytime_max =  25.0;

  //Define/Get the Histos to be plotted  
  TH1F* h1  = NULL;
  TH2F* h2  = NULL;
  TH2F* h3  = NULL;
  TH2F* h4  = NULL;
  TH1F* h5  = NULL;
  TH2F* h6  = NULL;
  TH2F* h7  = NULL;
  TH2F* h8  = NULL;
  TH2F* h9  = NULL;
  TH2F* h10 = NULL;
  
  h1 = defineTH1F("Output_Histo_RecHit.root","chi2_energyHB");
  h2 = defineTH2F("Output_Histo_RecHit.root","TH2_chi2_energyHB");
  h3 = defineTH2F("Output_Histo_RecHit.root","M2vsM0_HB");
  h3 = defineTH2F("Output_Histo_RecHit.root","M3vsM0_HB");
  h3 = defineTH2F("Output_Histo_RecHit.root","M3vsM2_HB");
  h4 = defineTH2F("Output_Histo_RecHit.root","TH2_time_energyHB");
  h5 = defineTH1F("Output_Histo_RecHit.root","chi2_energyHEQIE11");
  h6 = defineTH2F("Output_Histo_RecHit.root","TH2_chi2_energyHEQIE11");
  h7 = defineTH2F("Output_Histo_RecHit.root","M2vsM0_HEQIE11");
  h8 = defineTH2F("Output_Histo_RecHit.root","TH2_time_energyHEQIE11");
  h9 = defineTH2F("Output_Histo_RecHit.root","M3vsM0_HEQIE11");
  h10 = defineTH2F("Output_Histo_RecHit.root","M3vsM2_HEQIE11");

  ////////HB//////////
  TCanvas *c0 = new TCanvas("c0","c0",1200,800);
  c0->Divide(2,2);

  //HB chi2 vs M2 energy
  c0->cd(1);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h1->SetLineColor(2);
  h1->Draw("COLZ"); 
  h1->SetMinimum(ychi_min);
  h1->SetMaximum(ychi_max);
  h1->SetName("");
  h1->SetTitle(HB_Title);
  h1->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h1->GetYaxis()->SetTitle("Log10(chi2)");
  h1->SetTitleSize(0.001);
  h1->SetTitleSize(0.05,"Y");
  h1->SetTitleSize(0.05,"X");
  h1->SetTitleOffset(1.0,"Y");
  h1->SetTitleOffset(1.0,"X");
  h1->SetLabelSize(0.03,"Y");
  h1->SetLabelSize(0.03,"X");
  h1->SetStats(false);

  //catLeg0->SetTextSize(0.03);
  //catLeg0->AddEntry(h1,"","l");  
  //catLeg0->Draw();

  //HB TH2F chi2 vs M2 energy
  c0->cd(2);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h2->SetLineColor(2);
  h2->Draw("COLZ"); 
  h2->GetYaxis()->SetRangeUser(ychi_min,ychi_max);
  h2->SetName("");
  h2->SetTitle(HB_Title);
  h2->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h2->GetYaxis()->SetTitle("Log10(chi2)");
  h2->SetTitleSize(0.001);
  h2->SetTitleSize(0.05,"Y");
  h2->SetTitleSize(0.05,"X");
  h2->SetTitleOffset(1.0,"Y");
  h2->SetTitleOffset(1.0,"X");
  h2->SetLabelSize(0.03,"Y");
  h2->SetLabelSize(0.03,"X");
  h2->SetStats(false);

  //HB M0 energy vs M2 energy
  c0->cd(3);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h3->SetLineColor(2);
  h3->Draw("COLZ"); 
  //h3->SetMinimum(ymin);
  //h3->SetMaximum(ymax);
  h3->SetName("");
  h3->SetTitle(HB_Title);
  h3->GetXaxis()->SetTitle("M0 Energy [GeV]");
  h3->GetYaxis()->SetTitle("M2 Energy [GeV]");
  h3->SetTitleSize(0.001);
  h3->SetTitleSize(0.05,"Y");
  h3->SetTitleSize(0.05,"X");
  h3->SetTitleOffset(1.0,"Y");
  h3->SetTitleOffset(1.0,"X");
  h3->SetLabelSize(0.03,"Y");
  h3->SetLabelSize(0.03,"X");
  h3->SetStats(false);

  //HB time vs M2 energy
  c0->cd(4);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h4->SetLineColor(2);
  h4->Draw("COLZ"); 
  h4->GetYaxis()->SetRangeUser(ytime_min,ytime_max);
  h4->SetName("");
  h4->SetTitle(HB_Title);
  h4->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h4->GetYaxis()->SetTitle("Time [ns]");
  h4->SetTitleSize(0.001);
  h4->SetTitleSize(0.05,"Y");
  h4->SetTitleSize(0.05,"X");
  h4->SetTitleOffset(1.0,"Y");
  h4->SetTitleOffset(1.0,"X");
  h4->SetLabelSize(0.03,"Y");
  h4->SetLabelSize(0.03,"X");
  h4->SetStats(false);

  ////////HEQIE11//////////
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(2,2);

  //HEQIE11 chi2 vs M2 energy
  c1->cd(1);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  
  //h5->SetLineColor(2);
  h5->Draw("COLZ"); 
  h5->SetMinimum(ychi_min);
  h5->SetMaximum(ychi_max);
  h5->SetName("");
  h5->SetTitle(HE_Title);
  h5->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h5->GetYaxis()->SetTitle("Log10(chi2)");
  h5->SetTitleSize(0.001);
  h5->SetTitleSize(0.05,"Y");
  h5->SetTitleSize(0.05,"X");
  h5->SetTitleOffset(1.0,"Y");
  h5->SetTitleOffset(1.0,"X");
  h5->SetLabelSize(0.03,"Y");
  h5->SetLabelSize(0.03,"X");
  h5->SetStats(false);

  //catLeg0->SetTextSize(0.03);
  //catLeg0->AddEntry(h5,"","l");  
  //catLeg0->Draw();

  //HE TH2F chi2 vs M2 energy
  c1->cd(2);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h6->SetLineColor(2);
  h6->Draw("COLZ"); 
  h6->GetYaxis()->SetRangeUser(ychi_min,ychi_max);
  h6->SetName("");
  h6->SetTitle(HE_Title);
  h6->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h6->GetYaxis()->SetTitle("Log10(chi2)");
  h6->SetTitleSize(0.001);
  h6->SetTitleSize(0.05,"Y");
  h6->SetTitleSize(0.05,"X");
  h6->SetTitleOffset(1.0,"Y");
  h6->SetTitleOffset(1.0,"X");
  h6->SetLabelSize(0.03,"Y");
  h6->SetLabelSize(0.03,"X");
  h6->SetStats(false);

  //HE M0 energy vs M2 energy
  c1->cd(3);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h7->SetLineColor(2);
  h7->Draw("COLZ"); 
  //h7->SetMinimum(ymin);
  //h7->SetMaximum(ymax);
  h7->SetName("");
  h7->SetTitle(HE_Title);
  h7->GetXaxis()->SetTitle("M0 Energy [GeV]");
  h7->GetYaxis()->SetTitle("M2 Energy [GeV]");
  h7->SetTitleSize(0.001);
  h7->SetTitleSize(0.05,"Y");
  h7->SetTitleSize(0.05,"X");
  h7->SetTitleOffset(1.0,"Y");
  h7->SetTitleOffset(1.0,"X");
  h7->SetLabelSize(0.03,"Y");
  h7->SetLabelSize(0.03,"X");
  h7->SetStats(false);

  //HE time vs M2 energy
  c1->cd(4);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  //h8->SetLineColor(2);
  h8->Draw("COLZ"); 
  h8->GetYaxis()->SetRangeUser(ytime_min,ytime_max);
  h8->SetName("");
  h8->SetTitle(HE_Title);
  h8->GetXaxis()->SetTitle("M2 Energy [GeV]");
  h8->GetYaxis()->SetTitle("Time [ns]");
  h8->SetTitleSize(0.001);
  h8->SetTitleSize(0.05,"Y");
  h8->SetTitleSize(0.05,"X");
  h8->SetTitleOffset(1.0,"Y");
  h8->SetTitleOffset(1.0,"X");
  h8->SetLabelSize(0.03,"Y");
  h8->SetLabelSize(0.03,"X");
  h8->SetStats(false);

  TCanvas *c2 = new TCanvas("c2","c2",600,800);
  c2->Divide(1,2);

  c2->cd(1);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  h9->Draw("COLZ"); 
  //h9->SetMinimum(ymin);
  //h9->SetMaximum(ymax);
  h9->SetName("");
  h9->SetTitle(HE_Title);
  h9->GetXaxis()->SetTitle("M3 Energy [GeV]");
  h9->GetYaxis()->SetTitle("M0 Energy [GeV]");
  h9->SetTitleSize(0.001);
  h9->SetTitleSize(0.05,"Y");
  h9->SetTitleSize(0.05,"X");
  h9->SetTitleOffset(1.0,"Y");
  h9->SetTitleOffset(1.0,"X");
  h9->SetLabelSize(0.03,"Y");
  h9->SetLabelSize(0.03,"X");
  h9->SetStats(false);

  c2->cd(2);
  gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(0.16);
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetLogz();
  //gPad->SetGrid();
  gStyle->SetPalette(kRainBow);

  h10->Draw("COLZ"); 
  //h10->SetMinimum(ymin);
  //h10->SetMaximum(ymax);
  h10->SetName("");
  h10->SetTitle(HE_Title);
  h10->GetXaxis()->SetTitle("M3 Energy [GeV]");
  h10->GetYaxis()->SetTitle("M2 Energy [GeV]");
  h10->SetTitleSize(0.001);
  h10->SetTitleSize(0.05,"Y");
  h10->SetTitleSize(0.05,"X");
  h10->SetTitleOffset(1.0,"Y");
  h10->SetTitleOffset(1.0,"X");
  h10->SetLabelSize(0.03,"Y");
  h10->SetLabelSize(0.03,"X");
  h10->SetStats(false);
  
  //Save Plot
  c0->SaveAs(HB_Name_Save);
  c1->SaveAs(HE_Name_Save);
  c2->SaveAs("M3_Plots.pdf");

}//End of Macro
