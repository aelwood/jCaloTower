cd /afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
eval `scramv1 runtime -sh` 
#filelist='/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/qcd_PU140.txt'
filelist='/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/skimfiles/140708_ttbar_PU40.txt'
outputdir="/afs/cern.ch/work/m/mcitron/public/TTBAR/140710/"
python python/run_qcd.py $filelist $outputdir
