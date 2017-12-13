#!/bin/tcsh
echo "hostname: `hostname`"
source /cvmfs/cms.cern.ch/cmsset_default.csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/CMSSW_9_2_3_Timeslew2_50GeV_RecHit.tgz .
tar -xf CMSSW_9_2_3_Timeslew2_50GeV_RecHit.tgz
rm CMSSW_9_2_3_Timeslew2_50GeV_RecHit.tgz
cd CMSSW_9_2_3_Timeslew2/src
scramv1 b ProjectRename
cmsenv
cd HcalPromptAnalysis/HcalTreeMaker/TimeSlew2/50GeV/condor
setenv RUNNUMBER ${11}

cmsRun SinglePiE50HCAL_pythia8_cfi_GEN_SIM_seed.py
cmsRun step2_DIGI_L1_DIGI2RAW_HLT.py
cmsRun step3_RAW2DIGI_L1Reco_RECO_EI_PAT_VALIDATION_DQM.py
cmsRun Conf_HcalDigiTreeMaker.py
source FillHisto_HcalRecHit.csh
source FillHisto_HcalDigis.csh

xrdcp OutputTree_standard.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${1}
xrdcp Output_Histo_standard_10_25.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${2}
xrdcp Output_Histo_standard_25_50.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${3}
xrdcp Output_Histo_standard_50_75.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${4}
xrdcp Output_Histo_standard_75_100.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${5}
xrdcp Output_Histo_standard_100_150.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${6}
xrdcp Output_Histo_standard_150_200.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${7}
xrdcp Output_Histo_standard_200_300.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${8}
xrdcp Output_Histo_standard_300_inf.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${9}
xrdcp Output_Histo_RecHit.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_Timeslew2_50GeV_RecHit/${10}


cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_9_2_3_Timeslew2
