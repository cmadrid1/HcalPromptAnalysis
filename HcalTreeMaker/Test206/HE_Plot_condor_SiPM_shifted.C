#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TDirectory.h>

//pulse shape vectors
#include "pulses.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

TH1F* makePulseHisto(vector<double>& pulse, int bstart, string name){
	//make pulse template histo (from convolution)
	TH1F* htempT = new TH1F(name.c_str(),"",250,0,250);
	for(unsigned b = 0; b < pulse.size(); ++b){
		htempT->SetBinContent(b+bstart,pulse[b]);
	}
	htempT->Scale(1.0/htempT->Integral(0,htempT->GetNbinsX()+1));
	htempT->SetMarkerColor(kBlack);
	htempT->SetMarkerSize(0.75);
	htempT->GetXaxis()->SetTitle("time [ns]");
	htempT->GetYaxis()->SetTitle("a.u.");
	
	return htempT;

}

void HE_Plot_condor_SiPM_shifted(string fname="step2prec_HcalSiPMntuple.root", string name="step2prec", int depth=0, bool hpd=true){
	//get and check histos from file
	string hpre = "signalTotPrecise";
	vector<double> emin = {0,100,200,300,400,500};
	vector<double> emax = {100,200,300,400,500,600};
	//KH TFile* file = TFile::Open(fname.c_str());
	vector<TH1F*> hists;
	vector<string> hist_leg;

	//make pulse template histo (from convolution)
	TH1F* htempT = NULL;
	TH1F* htempT2 = NULL;
	if(hpd){
	        //htempT = makePulseHisto(s105,70,"reco");
		//htempT->SetLineColor(2);
		//leg->AddEntry(htempT,"105 [HPD RECO]","l");
		//htempT2 = makePulseHisto(s125,70,"sim");
		//htempT2->SetMarkerColor(kGray+1);
		//htempT2->SetLineColor(4);
		//leg->AddEntry(htempT2,"125 [HPD SIM]","l");
		htempT  = makePulseHisto(s203,1,"old");//////
		htempT2 = makePulseHisto(s205,1,"new");
	}
	//else {
	//	if(name.find("250")!=string::npos) htempT = makePulseHisto(s203,1,"reco");
	//	else htempT = makePulseHisto(s203,95,"reco");
	//	leg->AddEntry(htempT,"203 [Conv(SiPM,Y11)]","p");
	//}
	//double ymax = max(htempT->GetMaximum(),htempT2?htempT2->GetMaximum():0.0);
	//double ymin = min(htempT->GetMinimum(0),htempT2?htempT2->GetMinimum(0):yminmin);
	
	// Compare to Standard vs No All

	// Drawing Standard vs No All Histos

	TFile *_file0 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples.root");
	TFile *_file1 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples_GT.root");
	TFile *_file2 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples_PS.root");
	TFile *_file3 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples_PW.root");
	TFile *_file4 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples_TS.root");
	TFile *_file5 = TFile::Open("root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/debugcalosamples_DC.root");

	TTree *t0b = (TTree*)_file0->Get("tree");
	TTree *t1b = (TTree*)_file1->Get("tree");
	TTree *t2b = (TTree*)_file2->Get("tree");
	TTree *t3b = (TTree*)_file3->Get("tree");
	TTree *t4b = (TTree*)_file4->Get("tree");
	TTree *t5b = (TTree*)_file5->Get("tree");

	TH1F* htemp0 = new TH1F("htemp0","htemp0",250,0.,250.);
	TH1F* htemp1 = new TH1F("htemp1","htemp1",250,0.,250.);
	TH1F* htemp2 = new TH1F("htemp2","htemp2",250,0.,250.);
	TH1F* htemp3 = new TH1F("htemp3","htemp3",250,0.,250.);
	TH1F* htemp4 = new TH1F("htemp4","htemp4",250,0.,250.);
	TH1F* htemp5 = new TH1F("htemp5","htemp5",250,0.,250.);

	//double min_SiPMEnergy = 2.5;

	t0b->Draw("Iteration$*0.5>>htemp0","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");
	t1b->Draw("Iteration$*0.5>>htemp1","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");
	t2b->Draw("Iteration$*0.5>>htemp2","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");
	t3b->Draw("Iteration$*0.5>>htemp3","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");
	t4b->Draw("Iteration$*0.5>>htemp4","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");
	t5b->Draw("Iteration$*0.5>>htemp5","signalTotPrecise[]*(subdet==2)*(simHitToPhotoelectrons>6000)*(simHitToPhotoelectrons<16000)*(((signalTot[4]+signalTot[5])*fCtoGeV*photoelectronsToAnalog)>2.5)","hist");

	TH1F *hnew1 = new TH1F("hnew1","hnew1",251,0,251);
	TH1F *hnew2 = new TH1F("hnew2","hnew2",251,0,251);
	
        int ishift1=87; //to be tuned.              
	int ishift2=91; //to be tuned.              
 
        //int shift1 = htemp0->GetMaximumBin();                                                                                                                                                             
        //int shift2 = hnew1->GetMaximumBin();                                                                                                                                                              
        //int ishift = shift1-shift2;                                                                                                                                                                       

        for(int j=0; j<=251-ishift1; j++){
          hnew1->SetBinContent(j+ishift1,htempT->GetBinContent(j));
        }

	for(int j=0; j<=251-ishift2; j++){
          hnew2->SetBinContent(j+ishift2,htempT2->GetBinContent(j));
        }

	// Defining the Canvas

	TCanvas *c0 = new TCanvas("PulseShape","",1600,800);
	TCanvas *c2 = new TCanvas("LogPulseShape","",1600,800);
	TLegend* catLeg0 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeg1 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeg2 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeg3 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeg4 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeg5 = new TLegend(0.62,0.62,0.99,1.0);
        TLegend* catLeglog0 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeglog1 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeglog2 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeglog3 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeglog4 = new TLegend(0.62,0.82,0.99,1.0);
        TLegend* catLeglog5 = new TLegend(0.62,0.62,0.99,1.0);

	c0->Divide(3,2);
	c2->Divide(3,2);

	//Linear plots

	//Standard vs No Geant Time       
	c0->cd(1);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp1->GetXaxis()->SetTitle("time (ns)");
	htemp1->GetYaxis()->SetTitle("a.u.");
	htemp1->SetTitle("");
	htemp1->SetName("");
	htemp1->SetTitleSize(0.001);
	htemp1->SetTitleSize(0.07,"X");
	htemp1->SetTitleSize(0.06,"Y");
	htemp1->SetTitleOffset(1.0,"X");
	htemp1->SetTitleOffset(1.5,"Y");
	htemp1->SetLabelSize(0.05,"X");
	htemp1->SetLabelSize(0.05,"Y");
	htemp1->SetStats(false);

	htemp1->Draw("hist l");
	hnew1->Draw("hist l same");
	hnew2->Draw("hist l same");
	htemp0->Draw("hist l same");                                                               
                                                                                                    
	catLeg0->SetTextSize(0.04);
	catLeg0->SetTextFont(42);
	catLeg0->SetLineColor(1);
	catLeg0->SetFillColor(0);

	//catLeg0->SetHeader("Pulse Shape");
	catLeg0->AddEntry(htemp1,"No GeantTime","l");
	catLeg0->AddEntry(htemp0,"Standard","l");
	catLeg0->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg0->AddEntry(hnew2,"205","l");
	catLeg0->Draw();

	//Standard vs No PhotoStatistics       
	c0->cd(2);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp2->GetXaxis()->SetTitle("time (ns)");
	htemp2->GetYaxis()->SetTitle("a.u.");
	htemp2->SetTitle("");
	htemp2->SetName("");
	htemp2->SetTitleSize(0.001);
	htemp2->SetTitleSize(0.07,"X");
	htemp2->SetTitleSize(0.06,"Y");
	htemp2->SetTitleOffset(1.0,"X");
	htemp2->SetTitleOffset(1.0,"Y");
	htemp2->SetLabelSize(0.05,"X");
	htemp2->SetLabelSize(0.05,"Y");
	htemp2->SetStats(false);

	htemp2->Draw("hist l");
	hnew1->Draw("hist l same");                                                                                                          
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                                                                                         
        		
	catLeg1->SetTextSize(0.04);
	catLeg1->SetTextFont(42);
	catLeg1->SetLineColor(1);
	catLeg1->SetFillColor(0);

	//catLeg1->SetHeader("Pulse Shape");
	catLeg1->AddEntry(htemp2,"No Photostats","l");
	catLeg1->AddEntry(htemp0,"Standard","l");
	catLeg1->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg1->AddEntry(hnew2,"205","l");
	//catLeg1->AddEntry(htempT2,"125 HPD sim","l");
	catLeg1->Draw();

	//Standard vs No Noise       
	c0->cd(3);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp3->GetXaxis()->SetTitle("time (ns)");
	htemp3->GetYaxis()->SetTitle("a.u.");
	htemp3->SetTitle("");
	htemp3->SetName("");
	htemp3->SetTitleSize(0.001);
	htemp3->SetTitleSize(0.07,"X");
	htemp3->SetTitleSize(0.06,"Y");
	htemp3->SetTitleOffset(1.0,"X");
	htemp3->SetTitleOffset(1.0,"Y");
	htemp3->SetLabelSize(0.05,"X");
	htemp3->SetLabelSize(0.05,"Y");
	htemp3->SetStats(false);

	htemp3->Draw("hist l");
	hnew1->Draw("hist l same");                                                                
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                          
        		
	catLeg2->SetTextSize(0.04);
	catLeg2->SetTextFont(42);
	catLeg2->SetLineColor(1);
	catLeg2->SetFillColor(0);

	//catLeg2->SetHeader("Pulse Shape");
	catLeg2->AddEntry(htemp3,"No Noise","l");
	catLeg2->AddEntry(htemp0,"Standard","l");
	catLeg2->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg2->AddEntry(hnew2,"205","l");
	catLeg2->Draw();

	//Standard vs No Time Slew
	c0->cd(4);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp4->GetXaxis()->SetTitle("time (ns)");
	htemp4->GetYaxis()->SetTitle("a.u.");
	htemp4->SetTitle("");
	htemp4->SetName("");
	htemp4->SetTitleSize(0.001);
	htemp4->SetTitleSize(0.07,"X");
	htemp4->SetTitleSize(0.06,"Y");
	htemp4->SetTitleOffset(1.0,"X");
	htemp4->SetTitleOffset(1.0,"Y");
	htemp4->SetLabelSize(0.05,"X");
	htemp4->SetLabelSize(0.05,"Y");
	htemp4->SetStats(false);

	htemp4->Draw("hist l");
	hnew1->Draw("hist l same");                                                                                                          
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                                                                                         
                                                            
	catLeg3->SetTextSize(0.04);
	catLeg3->SetTextFont(42);
	catLeg3->SetLineColor(1);
	catLeg3->SetFillColor(0);

	//catLeg3->SetHeader("Pulse Shape");
	catLeg3->AddEntry(htemp4,"No Time Slew","l");
	catLeg3->AddEntry(htemp0,"Standard","l");
	catLeg3->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg3->AddEntry(hnew2,"205","l");
	catLeg3->Draw();

	//Standard vs No Dark Current
	c0->cd(5);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp5->GetXaxis()->SetTitle("time (ns)");
	htemp5->GetYaxis()->SetTitle("a.u.");
	htemp5->SetTitle("");
	htemp5->SetName("");
	htemp5->SetTitleSize(0.001);
	htemp5->SetTitleSize(0.07,"X");
	htemp5->SetTitleSize(0.06,"Y");
	htemp5->SetTitleOffset(1.0,"X");
	htemp5->SetTitleOffset(1.0,"Y");
	htemp5->SetLabelSize(0.05,"X");
	htemp5->SetLabelSize(0.05,"Y");
	htemp5->SetStats(false);

	htemp5->Draw("hist l");
	hnew1->Draw("hist l same");                                                                                                          
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                                                                                         
                                                          
	catLeg4->SetTextSize(0.04);
	catLeg4->SetTextFont(42);
	catLeg4->SetLineColor(1);
	catLeg4->SetFillColor(0);

	//catLeg4->SetHeader("Pulse Shape");
	catLeg4->AddEntry(htemp5,"No DarkCurrent","l");
	catLeg4->AddEntry(htemp0,"Standard","l");
	catLeg4->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg4->AddEntry(hnew2,"205","l");
	catLeg4->Draw();

	//Standard vs No (Geant Time, Photo Statistics, Noise, Time Slew, Dark Current)
	c0->cd(6);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();

	htemp1->GetXaxis()->SetTitle("time (ns)");
	htemp1->GetYaxis()->SetTitle("a.u.");
	htemp1->SetTitle("");
	htemp1->SetName("");
	htemp1->SetTitleSize(0.001);
	htemp1->SetTitleSize(0.07,"X");
	htemp1->SetTitleSize(0.06,"Y");
	htemp1->SetTitleOffset(1.0,"X");
	htemp1->SetTitleOffset(1.0,"Y");
	htemp1->SetLabelSize(0.05,"X");
	htemp1->SetLabelSize(0.05,"Y");
	htemp1->SetStats(false);

	htemp1->Draw("hist l");
	hnew1->Draw("hist l same");                                                         
	hnew2->Draw("hist l same");                                                                                                          
	htemp2->Draw("hist l same");
	htemp3->Draw("hist l same");
	htemp4->Draw("hist l same");
	htemp5->Draw("hist l same");                                                                                        
	htemp0->Draw("hist l same");                    

	catLeg5->SetTextSize(0.04);
	catLeg5->SetTextFont(42);
	catLeg5->SetLineColor(1);
	catLeg5->SetFillColor(0);

	//catLeg5->SetHeader("Pulse Shape");
	catLeg5->AddEntry(htemp0,"Standard","l");
	catLeg5->AddEntry(htemp1,"No GeantTime","l");
	catLeg5->AddEntry(htemp2,"No PhotoStats","l");
	catLeg5->AddEntry(htemp3,"No Noise","l");
	catLeg5->AddEntry(htemp4,"No TimeSlew","l");
	catLeg5->AddEntry(htemp5,"No DarkCurrent","l");
	catLeg5->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeg5->AddEntry(hnew2,"205","l");
	catLeg5->Draw();


	//Log plots

	//Standard vs No Geant Time       
	c2->cd(1);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp1->GetXaxis()->SetTitle("time (ns)");
	htemp1->GetYaxis()->SetTitle("a.u.");
	htemp1->SetTitle("");
	htemp1->SetName("");
	htemp1->SetTitleSize(0.001);
	htemp1->SetTitleSize(0.07,"X");
	htemp1->SetTitleSize(0.06,"Y");
	htemp1->SetTitleOffset(1.0,"X");
	htemp1->SetTitleOffset(2.0,"Y");
	htemp1->SetLabelSize(0.05,"X");
	htemp1->SetLabelSize(0.05,"Y");
	htemp1->SetStats(false);

	htemp1->Draw("hist l");
	hnew1->Draw("hist l same");
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                                               
                                                                                                    
	catLeglog0->SetTextSize(0.04);
	catLeglog0->SetTextFont(42);
	catLeglog0->SetLineColor(1);
	catLeglog0->SetFillColor(0);

	//catLeglog0->SetHeader("Pulse Shape");
	catLeglog0->AddEntry(htemp1,"No GeantTime","l");
	catLeglog0->AddEntry(htemp0,"Standard","l");
	catLeglog0->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog0->AddEntry(hnew2,"205","l");
	catLeglog0->Draw();

	//Standard vs No PhotoStatistics       
	c2->cd(2);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp2->GetXaxis()->SetTitle("time (ns)");
	htemp2->GetYaxis()->SetTitle("a.u.");
	htemp2->SetTitle("");
	htemp2->SetName("");
	htemp2->SetTitleSize(0.001);
	htemp2->SetTitleSize(0.07,"X");
	htemp2->SetTitleSize(0.06,"Y");
	htemp2->SetTitleOffset(1.0,"X");
	htemp2->SetTitleOffset(1.0,"Y");
	htemp2->SetLabelSize(0.05,"X");
	htemp2->SetLabelSize(0.05,"Y");
	htemp2->SetStats(false);

	htemp2->Draw("hist l");
	hnew1->Draw("hist l same");                                                                                  
	hnew2->Draw("hist l same");                                                                   
	htemp0->Draw("hist l same");                                    
                                                            
	catLeglog1->SetTextSize(0.04);
	catLeglog1->SetTextFont(42);
	catLeglog1->SetLineColor(1);
	catLeglog1->SetFillColor(0);

	//catLeglog1->SetHeader("Pulse Shape");
	catLeglog1->AddEntry(htemp2,"No Photostats","l");
	catLeglog1->AddEntry(htemp0,"Standard","l");
	catLeglog1->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog1->AddEntry(hnew2,"205","l");
	catLeglog1->Draw();

	//Standard vs No Noise       
	c2->cd(3);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp3->GetXaxis()->SetTitle("time (ns)");
	htemp3->GetYaxis()->SetTitle("a.u.");
	htemp3->SetTitle("");
	htemp3->SetName("");
	htemp3->SetTitleSize(0.001);
	htemp3->SetTitleSize(0.07,"X");
	htemp3->SetTitleSize(0.06,"Y");
	htemp3->SetTitleOffset(1.0,"X");
	htemp3->SetTitleOffset(1.0,"Y");
	htemp3->SetLabelSize(0.05,"X");
	htemp3->SetLabelSize(0.05,"Y");
	htemp3->SetStats(false);

	htemp3->Draw("hist l");
	hnew1->Draw("hist l same");                                                                
	hnew2->Draw("hist l same");                                                                         
	htemp0->Draw("hist l same");                                          
                                                                                                    
	catLeglog2->SetTextSize(0.04);
	catLeglog2->SetTextFont(42);
	catLeglog2->SetLineColor(1);
	catLeglog2->SetFillColor(0);

	//catLeglog2->SetHeader("Pulse Shape");
	catLeglog2->AddEntry(htemp3,"No Noise","l");
	catLeglog2->AddEntry(htemp0,"Standard","l");
	catLeglog2->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog2->AddEntry(hnew2,"205","l");
	catLeglog2->Draw();

	//Standard vs No Time Slew
	c2->cd(4);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp4->GetXaxis()->SetTitle("time (ns)");
	htemp4->GetYaxis()->SetTitle("a.u.");
	htemp4->SetTitle("");
	htemp4->SetName("");
	htemp4->SetTitleSize(0.001);
	htemp4->SetTitleSize(0.07,"X");
	htemp4->SetTitleSize(0.06,"Y");
	htemp4->SetTitleOffset(1.0,"X");
	htemp4->SetTitleOffset(1.0,"Y");
	htemp4->SetLabelSize(0.05,"X");
	htemp4->SetLabelSize(0.05,"Y");
	htemp4->SetStats(false);

	htemp4->Draw("hist l");
	hnew1->Draw("hist l same");                                                                                                          
	hnew2->Draw("hist l same");                                                                                                          
	htemp0->Draw("hist l same");                                                                                                         
                                                            
	catLeglog3->SetTextSize(0.04);
	catLeglog3->SetTextFont(42);
	catLeglog3->SetLineColor(1);
	catLeglog3->SetFillColor(0);

	//catLeglog3->SetHeader("Pulse Shape");
	catLeglog3->AddEntry(htemp4,"No Time Slew","l");
	catLeglog3->AddEntry(htemp0,"Standard","l");
	catLeglog3->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog3->AddEntry(hnew2,"205","l");
	catLeglog3->Draw();

	//Standard vs No Dark Current
	c2->cd(5);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp5->GetXaxis()->SetTitle("time (ns)");
	htemp5->GetYaxis()->SetTitle("a.u.");
	htemp5->SetTitle("");
	htemp5->SetName("");
	htemp5->SetTitleSize(0.001);
	htemp5->SetTitleSize(0.07,"X");
	htemp5->SetTitleSize(0.06,"Y");
	htemp5->SetTitleOffset(1.0,"X");
	htemp5->SetTitleOffset(1.0,"Y");
	htemp5->SetLabelSize(0.05,"X");
	htemp5->SetLabelSize(0.05,"Y");
	htemp5->SetStats(false);

	htemp5->Draw("hist l");
	hnew1->Draw("hist l same");
        hnew2->Draw("hist l same");
        htemp0->Draw("hist l same");
                                                          
	catLeglog4->SetTextSize(0.04);
	catLeglog4->SetTextFont(42);
	catLeglog4->SetLineColor(1);
	catLeglog4->SetFillColor(0);

	//catLeglog4->SetHeader("Pulse Shape");
	catLeglog4->AddEntry(htemp5,"No DarkCurrent","l");
	catLeglog4->AddEntry(htemp0,"Standard","l");
	catLeglog4->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog4->AddEntry(hnew2,"205","l");
	catLeglog4->Draw();

	//Standard vs No (Geant Time, Photo Statistics, Noise, Time Slew, Dark Current)
	c2->cd(6);
	
	gPad->SetTopMargin(0.06);
	gPad->SetBottomMargin(0.16);
	gPad->SetRightMargin(0.04);
	gPad->SetLeftMargin(0.16);
	//gPad->SetGrid();
	gPad->SetLogy();

	htemp1->GetXaxis()->SetTitle("time (ns)");
	htemp1->GetYaxis()->SetTitle("a.u.");
	htemp1->SetTitle("");
	htemp1->SetName("");
	htemp1->SetTitleSize(0.001);
	htemp1->SetTitleSize(0.07,"X");
	htemp1->SetTitleSize(0.06,"Y");
	htemp1->SetTitleOffset(1.0,"X");
	htemp1->SetTitleOffset(1.0,"Y");
	htemp1->SetLabelSize(0.05,"X");
	htemp1->SetLabelSize(0.05,"Y");
	htemp1->SetStats(false);

	htemp1->Draw("hist l");
	hnew1->Draw("hist l same");                                                         
	hnew2->Draw("hist l same");                                                                                                          
	htemp2->Draw("hist l same");
	htemp3->Draw("hist l same");
	htemp4->Draw("hist l same");
	htemp5->Draw("hist l same");
	htemp0->Draw("hist l same");                    

	catLeglog5->SetTextSize(0.04);
	catLeglog5->SetTextFont(42);
	catLeglog5->SetLineColor(1);
	catLeglog5->SetFillColor(0);

/*	//catLeglog5->SetHeader("Pulse Shape");
	catLeglog5->AddEntry(htemp0,"Standard","l");
	catLeglog5->AddEntry(htemp1,"No GeantTime","l");
	catLeglog5->AddEntry(htemp2,"No PhotoStats","l");
	catLeglog5->AddEntry(htemp3,"No Noise","l");
	catLeglog5->AddEntry(htemp4,"No TimeSlew","l");
	catLeglog5->AddEntry(htemp5,"No DarkCurrent","l");
	catLeglog5->AddEntry(hnew1,"203Conv(SiPM,Y11)","l");
	catLeglog5->AddEntry(hnew2,"205","l");
	catLeglog5->Draw();
*/
	//Set Line Color
	htemp0->SetLineColor(1);
	htemp1->SetLineColor(2);
	htemp2->SetLineColor(3);
	htemp3->SetLineColor(4);
	htemp4->SetLineColor(6);
	htemp5->SetLineColor(8);
        hnew1->SetLineColor(9);
	hnew2->SetLineColor(11);

	//Normalize plots 
	
	
	//std::cout<<htemp0->GetMaximumBin()<<std::endl;
        
	Double_t norm =1;
	Double_t bmin0 = htemp0->GetMaximumBin();
	Double_t bmax0 = htemp0->GetMaximumBin();
	Double_t bmin1 = htemp1->GetMaximumBin();
	Double_t bmax1 = htemp1->GetMaximumBin();
	Double_t bmin2 = htemp2->GetMaximumBin();
	Double_t bmax2 = htemp2->GetMaximumBin();
	Double_t bmin3 = htemp3->GetMaximumBin();
	Double_t bmax3 = htemp3->GetMaximumBin();
	Double_t bmin4 = htemp4->GetMaximumBin();
	Double_t bmax4 = htemp4->GetMaximumBin();
	Double_t bmin5 = htemp5->GetMaximumBin();
	Double_t bmax5 = htemp5->GetMaximumBin();
	Double_t hminT = hnew1->GetMaximumBin();
	Double_t hmaxT = hnew1->GetMaximumBin();
	Double_t hminT2 = hnew2->GetMaximumBin();
	Double_t hmaxT2 = hnew2->GetMaximumBin();

	htemp0->Scale(norm/htemp0->Integral(bmin0,bmax0));
	htemp1->Scale(norm/htemp1->Integral(bmin1,bmax1));
	htemp2->Scale(norm/htemp2->Integral(bmin2,bmax2));
	htemp3->Scale(norm/htemp3->Integral(bmin3,bmax3));
	htemp4->Scale(norm/htemp4->Integral(bmin4,bmax4));
	htemp5->Scale(norm/htemp5->Integral(bmin5,bmax5));
	hnew1->Scale(norm/hnew1->Integral(hminT,hmaxT));
	hnew2->Scale(norm/hnew2->Integral(hminT2,hmaxT2));

	//htemp0->Print("all");
	//hnew1->Print("all");
	std::cout<<htemp0->GetMaximumBin()<<std::endl;
	std::cout<<htemp1->GetMaximumBin()<<std::endl;
	std::cout<<htemp2->GetMaximumBin()<<std::endl;
	std::cout<<htemp3->GetMaximumBin()<<std::endl;
	std::cout<<htemp4->GetMaximumBin()<<std::endl;
	std::cout<<htemp5->GetMaximumBin()<<std::endl;
	std::cout<<hnew1->GetMaximumBin()<<std::endl;
	std::cout<<hnew2->GetMaximumBin()<<std::endl;

	//Set Y axis
	
	Double_t ymin =0.0001;
	Double_t ymax =1.2;

	htemp1->SetMinimum(ymin);
	htemp1->SetMaximum(ymax);

	htemp2->SetMinimum(ymin);
	htemp2->SetMaximum(ymax);

	htemp3->SetMinimum(ymin);
	htemp3->SetMaximum(ymax);

	htemp4->SetMinimum(ymin);
	htemp4->SetMaximum(ymax);

	htemp5->SetMinimum(ymin);
	htemp5->SetMaximum(ymax);

	//Save Plots
        c0->SaveAs("HE_2017_Shifted_10000Events_PulseShape_SiPM_vsSiPM_Standard_no_GT_PS_PW_TS_DC.pdf");

        c2->SaveAs("HE_2017_Shifted_10000Events_logPulseShape_SiPM_vsSiPM_Standard_no_GT_PS_PW_TS_DC.pdf");

	//can->Print((sout.str()+".png").c_str(),"png");
}
