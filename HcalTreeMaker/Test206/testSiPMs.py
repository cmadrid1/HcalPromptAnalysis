import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing("analysis")
# geant time, photostatistics, pedestal width (noise), timeslew, dark current, crosstalk, nonlinearity
_params = ["GT", "PS", "PW", "TS", "DC", "CT", "NL"]
for p in _params:
    options.register(p, False, VarParsing.multiplicity.singleton, VarParsing.varType.bool)
options.register("outpre", "step2", VarParsing.multiplicity.singleton, VarParsing.varType.string)
options.register("output", "FEVTDEBUGHLToutput", VarParsing.multiplicity.singleton, VarParsing.varType.string)
options.register("config", "step2_DIGI_L1_DIGI2RAW_HLT", VarParsing.multiplicity.singleton, VarParsing.varType.string)
options.parseArguments()

if len(options.inputFiles)==0:
    options.inputFiles = "file:step1.root"

# output name definition
_outname = options.outpre
for p in _params:
    if getattr(options,p):
        _outname += "_"+p
    else:
        _outname += "_no"+p
_outname += ".root"

# import process
process = getattr(__import__(options.config,fromlist=["process"]),"process")

# settings
process.maxEvents.input = cms.untracked.int32(options.maxEvents)
process.source.fileNames = cms.untracked.vstring(options.inputFiles)
getattr(process,options.output).fileName = cms.untracked.string('file:'+_outname)

# customization
from SLHCUpgradeSimulations.Configuration.HCalCustoms import load_HcalHardcode
process = load_HcalHardcode(process)
process.es_hardcode.useHFUpgrade = cms.bool(True)
#process.es_hardcode.useHEUpgrade = cms.bool(True)
process.es_hardcode.testHEPlan1 = cms.bool(True)
process.es_hardcode.toGet = cms.untracked.vstring('GainWidths','SiPMParameters','SiPMCharacteristics')

if not options.GT:
    process.mix.digitizers.hcal.ignoreGeantTime = cms.bool(True)
if not options.PS:
    process.mix.digitizers.hcal.he.doPhotoStatistics = cms.bool(False)
    process.mix.digitizers.hcal.hb.doPhotoStatistics = cms.bool(False)
if not options.PW:
    process.mix.digitizers.hcal.doNoise = cms.bool(False)
if not options.TS:
    process.mix.digitizers.hcal.doTimeSlew = cms.bool(False)
    if hasattr(process,"hbheprereco"): process.hbheprereco.algorithm.applyTimeSlew = cms.bool(False)
if not options.DC:
    process.es_hardcode.heUpgrade.darkCurrent = cms.vdouble(0,0)
if not options.CT:
    process.es_hardcode.SiPMCharacteristics[2].crosstalk = cms.double(0.0)
    process.es_hardcode.SiPMCharacteristics[3].crosstalk = cms.double(0.0)
if not options.NL:
    process.mix.digitizers.hcal.he.sipmTau = cms.double(0.0)
    process.es_hardcode.SiPMCharacteristics[2].nonlin1 = cms.double(1.0)
    process.es_hardcode.SiPMCharacteristics[3].nonlin1 = cms.double(1.0)
    process.es_hardcode.SiPMCharacteristics[2].nonlin2 = cms.double(0.0)
    process.es_hardcode.SiPMCharacteristics[3].nonlin2 = cms.double(0.0)
    process.es_hardcode.SiPMCharacteristics[2].nonlin3 = cms.double(0.0)
    process.es_hardcode.SiPMCharacteristics[3].nonlin3 = cms.double(0.0)
