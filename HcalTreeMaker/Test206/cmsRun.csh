#!/bin/tcsh
echo "hostname: `hostname`"
source /cvmfs/cms.cern.ch/cmsset_default.csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/CMSSW_9_2_3_203Fix.tgz .
tar -xf CMSSW_9_2_3_203Fix.tgz
rm CMSSW_9_2_3_203Fix.tgz
cd CMSSW_9_2_3_203Fix/src
scramv1 b ProjectRename
cmsenv
cd HcalPromptAnalysis/HcalTreeMaker/203Fix/50GeV
setenv RUNNUMBER ${9}

source run_Code.csh

xrdcp Output_Histo_standard.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${1}
xrdcp Output_Histo_RecHit.root   root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${2}
xrdcp debugcalosamples.root     root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${3}
#xrdcp debugcalosamples_DC.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${4}
#xrdcp debugcalosamples_GT.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${5}
#xrdcp debugcalosamples_TS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${6}
#xrdcp debugcalosamples_PW.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${7}
#xrdcp debugcalosamples_PS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_9_2_3_203Fix/${8}

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_9_2_3_203Fix
