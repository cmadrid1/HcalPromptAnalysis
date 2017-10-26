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


void CombineTree(const char *infile, const char *outfile){ 
   
  ifstream in;
  in.open(infile);
  if(!in.is_open()){
    cout << "Cannot open list file: " << infile << endl;
    return;  
  }

  TChain *chain = new TChain("CaloSamplesAnalyzer/tree");
    
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


  chain->Merge(outfile);

   
}
