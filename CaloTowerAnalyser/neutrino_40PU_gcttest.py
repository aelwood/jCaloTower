import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'WARNING'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
                                                                    
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_12345_skimmed.root',
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_678910_skimmed.root'
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_PU40_25ns_1-10_skimmed_v2.root'
    #'file:/afs/cern.ch/work/j/jad/public/TriggerTowers_TTbar_13TeV_noPU_test2_v3.root'
    #'file:/afs/cern.ch/work/m/mcitron/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root'    
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_10_1_oyf.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_11_1_Ae7.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_12_1_kfy.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_13_1_lFz.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_14_1_0Nc.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_15_1_WFG.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_16_1_gwj.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_18_1_OeO.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_19_1_GlL.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_1_1_lGc.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_20_1_Zf0.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_21_1_x9u.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_22_1_Re2.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_23_1_cB9.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_24_1_Kr3.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_25_1_95c.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_27_1_mtA.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_28_1_eyx.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_29_1_ZqI.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_2_1_riR.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_30_1_lKa.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_31_1_khm.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_32_1_ray.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_33_1_kDy.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_34_1_Tmx.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_35_1_qy6.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_36_1_yYD.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_37_1_98M.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_38_1_eY5.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_3_1_DWt.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_4_1_2gn.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_5_1_QaO.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_6_1_PnT.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_7_1_YvZ.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_8_1_MJe.root',
'root://eoscms.cern.ch//eos/cms/store/user/mcitron/140702_neutrino_PU40/L1SkimRun_9_1_LJ1.root',
    ),
    skipEvents=cms.untracked.uint32(4200)
)
import datetime
now = datetime.datetime.now()
date = now.strftime("%Y-%m-%d")

process.demo = cms.EDAnalyzer('CaloTowerAnalyser',
skim_name=cms.string("jadtest"),
gctinfo=cms.bool(True),
makeTree=cms.bool(True)
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('output/neutrino-output-'+date+'.root'),
                                   #fileName = cms.string('histograms-ttbar_13TeV_PU40_50ns_test_v3.root')
                                   )

process.p = cms.Path(process.demo)
