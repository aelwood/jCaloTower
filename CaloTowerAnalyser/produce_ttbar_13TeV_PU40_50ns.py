import FWCore.ParameterSet.Config as cms

process = cms.Process("jadtest")
process.load("FWCore.MessageService.MessageLogger_cfi")


process.MessageLogger = cms.Service("MessageLogger",
####                     destinations       =  cms.untracked.vstring('/dev/null/file.txt'),
threshold  = cms.untracked.string('ERROR')
)



process.source = cms.Source("PoolSource",
 fileNames = cms.untracked.vstring(
    #ttbar13 PU40 50ns
   #  'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/00E707E5-0D75-E311-B109-003048678BAE.root',
   #  'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/00EE7C4E-A976-E311-AFE2-003048678BEA.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/02732ACE-4175-E311-ACDE-003048679266.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/02B61C65-F874-E311-96DB-003048678B92.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/02BA8038-1C75-E311-9228-0025905A60F2.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/02C80318-0175-E311-895C-0026189438FA.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/02ECF824-4E75-E311-BB0F-0026189438CE.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/040974D0-3A75-E311-B258-002590596484.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/04A84408-3975-E311-9724-002618943856.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/0636E18D-5975-E311-85AB-00261894386A.root'
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/0696C6C5-FD76-E311-81EF-003048678E8A.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/08427EB7-3475-E311-9360-00261894398B.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/08C3DA9B-5975-E311-9D7F-00261894395B.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/08CF202A-F774-E311-9F22-0025905A6132.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/08D540FE-4775-E311-B9CC-002618FDA21D.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/08DC0110-5A75-E311-9050-0025905A48D6.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/0ADDCD85-0175-E311-9B1E-0025905A48EC.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/0C00F3D5-4375-E311-B632-0025905A60BE.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/1073CC0F-3C75-E311-8543-0025905A60FE.root',
     'root://xrootd.unl.edu//store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx50_POSTLS162_V2-v1/00000/1214DA45-FB74-E311-9784-0025905A6110.root',          
   ),


   # RAW files
   secondaryFileNames = cms.untracked.vstring(
   )
)



process.o1 = cms.OutputModule("PoolOutputModule",
  fileName = cms.untracked.string('/afs/cern.ch/work/m/mcitron/public/TriggerTowers_TTbar_13TeV_PU40_50ns_1-10_skimmed_v3.root'),
#   fileName = cms.untracked.string('output.root'),
    #SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('trigger_')),
    outputCommands = cms.untracked.vstring(
#    'keep *_*_*_*',
     'drop *_*_*_*',
#     'keep *_SLHCL1ExtraParticles_*_*',
#     'keep *_PUsubAK5CaloJetProducer_*_*',
#     # Test Pattern
#     'keep *_L1TestPatternCaloTowerProducer_*_*',

#     'keep *_hcalDigis_*_*',
     
     'keep *_valHcalTriggerPrimitiveDigis_*_*',
     'keep *_ecalDigis_EcalTriggerPrimitives_*',  
     'keep *_L1CaloTowerProducer_*_*',
     'keep *_ak4GenJets_*_*',
     'keep PileupSummaryInfos_*_*_*',
     'keep *_genParticles_*_*',
     'keep *_valGctDigis_*_*',
     'keep *_gctDigis_*_*'

#     'keep *_L1RingSubtractionProducer_*_*',
#     'keep *_L1TowerJetProducer_*_*',
#     'keep *_L1TowerJetCentralityFilter_*_*',
#     'keep *_L1TowerJetFilter1D_*_*',
#     'keep *_L1TowerJetPUEstimator_*_*',
#     'keep *_L1TowerJetPUSubtractedProducer_*_*',
#     'keep *_L1CalibFilterTowerJetProducer_*_*',
    
#     #kt6 jets for rho
#     'keep *_kt6CaloJets_*_RECO',
    
#     'keep *_ak5CaloJets_*_RECO',
#     'drop *_ak5CaloJets_rho_RECO',
#     'keep *_ak5CaloJets_rho_RCTofflineTEST',
#     'keep *_ak5PFJets_*_RECO',
#     'drop *_ak5PFJets_rho_RECO',
#     'keep *_ak5PFJets_rho_RCTofflineTEST',
#     'keep *_l1extraParticles_*_*',
#     'keep *_offlinePrimaryVertices_*_*',
#     'keep *_ak5JetID_*_*',
),
)


process.maxEvents = cms.untracked.PSet(
    # restrict number of events to 1000
    #input = cms.untracked.int32(10)
    # run over all events
    input = cms.untracked.int32(-1)
)

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = 'POSTLS161_V12::All'
process.GlobalTag.globaltag = 'POSTLS162_V5::All'

process.load("Configuration.Geometry.GeometryIdeal_cff")

#switch line depending on data or simulation
#process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

#process.load("Configuration.StandardSequences.Reconstruction_Data_cff")
#process.load("RecoParticleFlow.PFProducer.particleFlow_cff") 
#process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
process.load("SLHCUpgradeSimulations.L1CaloTrigger.SLHCCaloTrigger_cff")
# process.load("L1Trigger.L1ExtraFromDigis.l1extraParticles_cfi")
# process.load("Configuration.StandardSequences.Services_cff")

process.load("Configuration.StandardSequences.L1HwVal_cff")

#import FWCore.ParameterSet.Config as cms
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.Configuration.RecoGenJets_cff')

process.ak4GenJets = process.ak5GenJets.clone(
        rParam = cms.double(0.4)
            )

process.antiktGenJets = cms.Sequence(process.genJetParticles*process.ak4GenJets)


process.load('L1TriggerConfig.GctConfigProducers.L1GctConfig_cff')
process.L1GctConfigProducers.CalibrationStyle = cms.string('None')

# #create collection of PU corrected AK5 Calo Jets
# process.PUsubAK5CaloJetProducer = cms.EDProducer('CalCaloProducer',
#                                    CaloJets = cms.InputTag("ak5CaloJets"),
#                                    JetCorrector = cms.string('ak5CaloL1FastL2L3Residual'), #jet corrections residual for data
# )

# from RecoJets.JetProducers.JetIDParams_cfi import *

# process.ak5JetID = cms.EDProducer('JetIDProducer', JetIDParams,
#         src = cms.InputTag('ak5CaloJets')

# )

# process.ak5PFJets.doRhoFastjet = cms.bool(True)

# process.ak5CaloJets.doRhoFastjet = cms.bool(True)


process.p1 = cms.Path(
    process.RawToDigi
    #+process.hcalDigis
    #+process.ecalDigis
    +process.valRctDigis
    +process.valGctDigis
    +process.SLHCCaloTrigger
    +process.antiktGenJets
#                       +process.ak5CaloJets
#                       +process.ak5PFJets
#                       +process.PUsubAK5CaloJetProducer
#                       +process.ak5JetID
)

process.p1.insert(1, process.valHcalTriggerPrimitiveDigis)
from SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff import HcalTPGCoderULUT
HcalTPGCoderULUT.LUTGenerationMode = cms.bool(True)
process.valRctDigis.hcalDigis             = cms.VInputTag(cms.InputTag('valHcalTriggerPrimitiveDigis'))
process.L1CaloTowerProducer.HCALDigis =  cms.InputTag("valHcalTriggerPrimitiveDigis")


process.outpath = cms.EndPath(process.o1)

# Make the job crash in case of missing product
#process.options = cms.untracked.PSet( Rethrow = cms.untracked.vstring('ProductNotFound') )
process.options = cms.untracked.PSet(

    SkipEvent = cms.untracked.vstring('ProductNotFound')
    # Make the job crash in case of missing product
    #Rethrow = cms.untracked.vstring('ProductNotFound')
    
)

    
