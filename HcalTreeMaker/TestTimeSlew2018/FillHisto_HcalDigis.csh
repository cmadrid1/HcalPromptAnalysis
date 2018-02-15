#!/bin/tcsh

rm Output_Histo_standard_10_25.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_10_25.root","single",10,25 )'

rm Output_Histo_standard_25_50.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_25_50.root","single",25,50 )'

rm Output_Histo_standard_50_75.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_50_75.root","single",50,75 )'

rm Output_Histo_standard_75_100.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_75_100.root","single",75,100 )'

rm Output_Histo_standard_100_150.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_100_150.root","single",100,150 )'

rm Output_Histo_standard_150_200.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_150_200.root","single",150,200 )'

rm Output_Histo_standard_200_300.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_200_300.root","single",200,300 )'

rm Output_Histo_standard_300_inf.root
root -b -q 'fillHisto_HcalDigis.C ( "OutputTree_standard.root"," Output_Histo_standard_300_inf.root","single",300,99999 )'
