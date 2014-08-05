cd /afs/cern.ch/work/a/aelwood/trigger/jets/jadjet/ucttest/CMSSW_7_1_0_pre8/src/jCaloTower/CaloTowerAnalyser/batch
eval `scramv1 runtime -sh` 
#filelist='/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/qcd_PU140.txt'
filelist='ngun_files.txt'
outputdir="/afs/cern.ch/work/a/aelwood/public/NGUN/TwentyFiveNs/140805/"
python python/run_qcd.py $filelist $outputdir
