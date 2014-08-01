import subprocess
import make_config
import sys
import os

num = str(int(os.environ['LSB_JOBINDEX'])-1)

filelist = sys.argv[1]
outputdir = sys.argv[2]

arg_array=[]

i=0
with open(filelist) as f:
 for line in f.read().splitlines():
  arg_array.append([-1,line,0,os.path.join(outputdir,"output"+"_run"+str(i)+".root")])
  i+=1

#define file names
configinput=make_config.make_config_input(arg_array[int(num)][0],arg_array[int(num)][1],arg_array[int(num)][2],arg_array[int(num)][3],"jadtest")
if not os.path.exists(outputdir):
    os.makedirs(outputdir)
print configinput
os.chdir(outputdir)

f = open('config_'+num+'.py','w')
f.write(configinput)

with open("cmssw_"+num+".log",'w') as f:
 subprocess.call(["cmsRun", "config_"+num+".py"],stdout=f)

