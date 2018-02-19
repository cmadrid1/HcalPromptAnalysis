#!/bin/tcsh
echo "hostname: `hostname`"
source /cvmfs/cms.cern.ch/cmsset_default.csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/CMSSW_10_0_2_FinalPRsTest.tgz .
tar -xf CMSSW_10_0_2_FinalPRsTest.tgz
rm CMSSW_10_0_2_FinalPRsTest.tgz
cd CMSSW_10_0_2_FinalPRsTest/src
scramv1 b ProjectRename
cmsenv
cd HcalPromptAnalysis/HcalTreeMaker/Test206/
setenv RUNNUMBER ${9}

./run_Code.csh

xrdcp Output_Histo_standard.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${1}
xrdcp Output_Histo_RecHit.root   root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${2}
xrdcp debugcalosamples.root      root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${3}
#xrdcp debugcalosamples_DC.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${4}
#xrdcp debugcalosamples_GT.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${5}
#xrdcp debugcalosamples_TS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${6}
#xrdcp debugcalosamples_PW.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${7}
#xrdcp debugcalosamples_PS.root  root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_2_FinalPRsTest/Test206/${8}

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_0_2_FinalPRsTest
