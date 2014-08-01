import subprocess
import make_config_skim
#import sys
import os

num = str(int(os.environ['LSB_JOBINDEX'])-1)
#if len(sys.argv) != 3:
# print "Correct Usage: python run_skim.py <input> <output>"
# sys.exit(1)
#outputdir=sys.argv[1]#'file:/afs/cern.ch/work/m/mcitron/public/'    
#filelist=sys.argv[2]#'/afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/testin.txt'
outputdir='//afs/cern.ch/work/m/mcitron/public/QCDPU140/'    
filelist='//afs/cern.ch/work/m/mcitron/jadjets/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/batch/qcd_pu140.txt'
arg_array=[]
i=0
with open(filelist) as f:
 for line in f.read().splitlines():
  arg_array.append([line,os.path.join(outputdir,"output"+"_run"+str(i)+".root")])
  i+=1

#define file names
configinput=make_config_skim.make_config_input(arg_array[int(num)][0],arg_array[int(num)][1])
if not os.path.exists(outputdir):
    os.makedirs(outputdir)

#os.chdir(outputdir)

f = open(outputdir+'config_'+num+'.py','w')
f.write(configinput)
print configinput
with open(outputdir+"cmssw_"+num+".log",'w') as f:
 subprocess.call(["cmsRun", outputdir+"config_"+num+".py"],stdout=f)

#os.remove('config_'+num+'.py')
