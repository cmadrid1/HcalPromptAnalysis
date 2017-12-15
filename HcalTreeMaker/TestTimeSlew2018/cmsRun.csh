#!/bin/tcsh
echo "hostname: `hostname`"
source /cvmfs/cms.cern.ch/cmsset_default.csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018.tgz .
tar -xf CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018.tgz
rm CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018.tgz
cd CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/src
scramv1 b ProjectRename
cmsenv
cd HcalPromptAnalysis/HcalTreeMaker/TestTimeSlew2018
setenv RUNNUMBER ${11}

source run_Code_2017.csh
#source run_Code_2018.csh

#xrdcp OutputTree_standard.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${1}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${2}
xrdcp Output_Histo_standard_10_25.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${2}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${3}
xrdcp Output_Histo_standard_25_50.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${3}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${4}
xrdcp Output_Histo_standard_50_75.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${4}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${5}
xrdcp Output_Histo_standard_75_100.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${5}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${6}
xrdcp Output_Histo_standard_100_150.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${6}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${7}
xrdcp Output_Histo_standard_150_200.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${7}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${8}
xrdcp Output_Histo_standard_200_300.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${8}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${9}
xrdcp Output_Histo_standard_300_inf.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${9}
eosrm store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${10}
xrdcp Output_Histo_RecHit.root root://cmseos.fnal.gov//store/user/cmadrid/CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018/${10}


cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_0_X_2017-12-13-1100_HBHETimeSlew2018
