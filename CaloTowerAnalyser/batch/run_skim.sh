cd /afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/
eval `scramv1 runtime -sh`
python python/run_skim.py
#eval `scramv1 runtime -sh` 
#for i in {1..5}
#do
# export LSB_JOBINDEX=$i
# echo $LSB_JOBINDEX
# python python/run_skim.py
#done
