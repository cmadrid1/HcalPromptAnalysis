#!/bin/tcsh
echo "hostname: `hostname`"
source /cvmfs/cms.cern.ch/cmsset_default.csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/CMSSW_9_4_0_pre2_NewY11PulseShape.tgz .
tar -xf CMSSW_9_4_0_pre2_NewY11PulseShape.tgz
rm CMSSW_9_4_0_pre2_NewY11PulseShape.tgz
cd CMSSW_9_4_0_pre2_NewY11PulseShape/src
scramv1 b ProjectRename
cmsenv
cd HcalPromptAnalysis/HcalTreeMaker/Test206/
setenv RUNNUMBER ${9}

source run_Code.csh

xrdcp Output_Histo_standard.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${1}
xrdcp Output_Histo_RecHit.root   root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${2}
xrdcp debugcalosamples.root     root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${3}
#xrdcp debugcalosamples_DC.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${4}
#xrdcp debugcalosamples_GT.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${5}
#xrdcp debugcalosamples_TS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${6}
#xrdcp debugcalosamples_PW.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${7}
#xrdcp debugcalosamples_PS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_4_0_pre2_NewY11PulseShape/${8}

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_9_4_0_pre2_NewY11PulseShape
