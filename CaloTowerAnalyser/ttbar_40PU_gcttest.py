import FWCore.ParameterSet.Config as cms
import datetime
import os.path

doVer=False
process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'WARNING'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
                                                                    
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#'root://eoscms.cern.ch//eos/cms/store/user/aelwood/140725_jJets_ttbar_PU40bx50/L1SkimRun_48_1_Wg8.root'
#'/store/user/aelwood/140801_jJets_ttbar_PU40bx25/L1SkimRun_11_1_UBf.root'
'/store/user/aelwood/140801_jJets_ngun_PU40bx25/L1SkimRun_18_2_lRf.root'

#'file://L1SkimRun.root'
    ),
    skipEvents=cms.untracked.uint32(0)
)
now = datetime.datetime.now()
date = now.strftime("%Y-%m-%d")

process.demo = cms.EDAnalyzer('CaloTowerAnalyser',
skim_name=cms.string("jadtest"),
gctinfo=cms.bool(True)
)
fileName=('output/ttbar-output-PU40-'+date+'.root')
if(doVer):
 verNum = 1
 while (os.path.isfile(fileName)):
  fileName=('output/ttbar-output-PU40-'+date+'-rev'+str(verNum)+'.root')
  verNum+=1
print fileName
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(fileName),
                                   #fileName = cms.string('histograms-ttbar_13TeV_PU40_50ns_test_v3.root')
                                   )

process.p = cms.Path(process.demo)
