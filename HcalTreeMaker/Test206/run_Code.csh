#cd /uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/CMSSW_9_2_3_203Fix/src/HcalPromptAnalysis/HcalTreeMaker/203Fix/50GeV
#cmsenv
cmsRun SinglePiE50HCAL_pythia8_cfi_GEN_SIM_seed.py
#cmsRun step2_DIGI_L1_DIGI2RAW_HLT.py

####################################################################################
#cmsRun testSiPMs.py         PS=True PW=True TS=True         CT=True NL=True
#mv debugcalosamples.root debugcalosamples_GT.root
#mv step2_noGT_PS_PW_TS_noDC_CT_NL.root step2_GT.root
#
#cmsRun testSiPMs.py GT=True         PW=True TS=True         CT=True NL=True
#mv debugcalosamples.root debugcalosamples_PS.root
#mv step2_GT_noPS_PW_TS_noDC_CT_NL.root step2_PS.root
#
#cmsRun testSiPMs.py GT=True PS=True         TS=True         CT=True NL=True
#mv debugcalosamples.root debugcalosamples_PW.root
#mv step2_GT_PS_noPW_TS_noDC_CT_NL.root step2_PW.root
#
#cmsRun testSiPMs.py GT=True PS=True PW=True                 CT=True NL=True
#mv debugcalosamples.root debugcalosamples_TS.root
#mv step2_GT_PS_PW_noTS_noDC_CT_NL.root step2_TS.root
#
#cmsRun testSiPMs.py GT=True PS=True PW=True TS=True         CT=True NL=True
#mv debugcalosamples.root debugcalosamples_DC.root
#mv step2_GT_PS_PW_TS_noDC_CT_NL.root step2_DC.root
###################################################################################

#cmsRun testSiPMs.py GT=True PS=True PW=True TS=True DC=True CT=True NL=True
#mv step2_GT_PS_PW_TS_DC_CT_NL.root step2.root

#cmsRun testSiPMs.py          PS=True PW=True         DC=True CT=True NL=True
#mv step2_noGT_PS_PW_noTS_DC_CT_NL.root step2.root
cmsRun step2_DIGI_L1_DIGI2RAW_HLT.py
cmsRun step3_RAW2DIGI_L1Reco_RECO_EI_PAT_VALIDATION_DQM.py

cmsRun Conf_HcalDigiTreeMaker.py
#cmsRun Conf_DC.py 
#cmsRun Conf_TS.py
#cmsRun Conf_PW.py
#cmsRun Conf_PS.py
#cmsRun Conf_GT.py
source FillHisto_HcalRecHit.csh
source FillHisto_HcalDigis.csh
