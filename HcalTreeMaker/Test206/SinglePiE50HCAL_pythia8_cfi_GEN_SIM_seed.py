# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SinglePiE50HCAL_pythia8_cfi --conditions auto:phase1_2017_realistic -n 100 --era Run2_2017 --eventcontent FEVTDEBUG --relval 10000,100 -s GEN,SIM --datatier GEN-SIM --beamspot Realistic50ns13TeVCollision --geometry DB:Extended --fileout file:step1.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Run2_2017)
#process = cms.Process('SIM',eras.Run2_2017,eras.hcalHardcodeConditions)


import os
myRunNumber = int(os.environ.get('RUNNUMBER',' 12345'))+1
import uuid
import random
import sys

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2017Collision_cfi')
#process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#####
#process.es_hardcode.toGet = cms.untracked.vstring('GainWidths','MCParams','RecoParams')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('SinglePiE50HCAL_pythia8_cfi nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    #eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('file:step1.root'),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.XMLFromDBSource.label = cms.string("Extended")
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

process.generator = cms.EDFilter("Pythia8EGun",
    PGunParameters = cms.PSet(
        AddAntiParticle = cms.bool(True),
        MaxE = cms.double(500.01),
        MaxEta = cms.double(5.0),
        MaxPhi = cms.double(3.14159265359),
        MinE = cms.double(499.99),
        MinEta = cms.double(-5.0),
        MinPhi = cms.double(-3.14159265359),
        ParticleID = cms.vint32(211)
    ),
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring()
    ),
    Verbosity = cms.untracked.int32(0),
    firstRun = cms.untracked.uint32(1),
    psethack = cms.string('single pi E 50 HCAL')
)

#process.RandomNumberGeneratorService.generator.initialSeed = seed
process.RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.generator.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.simMuonRPCDigis.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.hiSignal.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.mix.initialSeed =random.randint(10000,9999999)
#process.RandomNumberGeneratorService.simCastorDigis.initialSeed = random.randint(10000,9999999)
#process.RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed = random.randint(10000,9999999)
#process.RandomNumberGeneratorService.simSiStripDigis.initialSeed = random.randint(10000,9999999)
#process.RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed = random.randint(10000,9999999)
#process.RandomNumberGeneratorService.simSiPixelDigis.initialSeed =random.randint(10000,9999999)
process.RandomNumberGeneratorService.LHCTransport.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.simMuonCSCDigis.initialSeed =random.randint(10000,9999999)
process.RandomNumberGeneratorService.mixData.initialSeed =random.randint(10000,9999999)
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.g4SimHits.initialSeed =random.randint(10000,9999999)
process.RandomNumberGeneratorService.simMuonDTDigis.initialSeed = random.randint(10000,9999999)
process.RandomNumberGeneratorService.hiSignalLHCTransport.initialSeed = random.randint(10000,9999999)
 
process.source = cms.Source("EmptySource",
                             firstRun = cms.untracked.uint32(myRunNumber)
                             )

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.FEVTDEBUGoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
