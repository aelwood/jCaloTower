import subprocess
import make_config
import sys
import os

num = str(int(os.environ['LSB_JOBINDEX'])-1)

if len(sys.argv) != 6:
#print len(sys.argv)
 print "USAGE run_config.py <tot num> <split> <output> <input> <skimname>"
 sys.exit(1)
#totevents = 70000
totevents = int(sys.argv[1])
#Nruns = 10
Nruns = int(sys.argv[2])
outputdir = sys.argv[3]
input = sys.argv[4]
skimname= sys.argv[5]
#input = "file:/afs/cern.ch/work/a/aelwood/public/TriggerTowers_TTbar_13TeV_PU40_50ns_1-10_skimmed_v3.root"
#input = "file:/afs/cern.ch/work/m/mcitron/public/TriggerTowers_NeutrinoGun_13TeV_PU40_50ns_1-10_skimmed_v3.root" 
print totevents,Nruns,outputdir,input 
arg_array=[]
for i in range(0,Nruns):
 arg_array.append([str(int(totevents*1./Nruns)),input,str(i*int(totevents*1./Nruns)+1),os.path.join(outputdir,"output"+"_run"+str(i)+".root")])

#define file names
configinput=make_config.make_config_input(arg_array[int(num)][0],arg_array[int(num)][1],arg_array[int(num)][2],arg_array[int(num)][3],skimname)
if not os.path.exists(outputdir):
    os.makedirs(outputdir)

os.chdir(outputdir)
print configinput
f = open('config_'+num+'.py','w')
f.write(configinput)

with open("cmssw_"+num+".log",'w') as f:
 subprocess.call(["cmsRun", "config_"+num+".py"],stdout=f)

#os.remove('config_'+num+'.py')
