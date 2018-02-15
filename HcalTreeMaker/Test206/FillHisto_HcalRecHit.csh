#!/bin/tcsh

rm Output_Histo_RecHit.root
root -b -q 'fillHisto_HcalRecHit.C( "OutputTree_standard.root"," Output_Histo_RecHit.root")'

