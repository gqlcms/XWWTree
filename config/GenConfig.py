import os
import sys
import json

def Gen_Inoutput_map(InputDir, OutputDir):
    InputDir  = os.path.normpath(InputDir)
    OutputDir = os.path.normpath(OutputDir)
    if OutputDir == InputDir:
        sys.exit("OutputDir can not be the same InputDir")

    Inoutput_map = {}
    for ds in os.listdir(InputDir):
        Inoutput_map[ds] = {}
        for ijobs,ifile in enumerate(os.listdir("%s/%s"%(InputDir,ds))):
            ijobs = ifile.split("_")[-1].replace(".root","")
            infile  = "%s/%s/%s"%(InputDir,ds,ifile)
            outfile = "%s/%s/%s"%(OutputDir,ds,ifile)
            if not os.path.isdir("%s/%s"%(OutputDir,ds)):
                os.makedirs("%s/%s"%(OutputDir,ds)) 
            Inoutput_map[ds][ijobs] = {
                "infile" : infile,
                "outfile" : outfile,
            }
    
    return Inoutput_map

# save Dic in better format
def SaveDic(FileName, DIC):
    if not FileName.endswith(".json"):
        sys.exit("the File is not json file")
    with open(FileName,"w") as f:
        json.dump(DIC, f, sort_keys=True, indent=4)
    print FileName

InputDir = "/eos/user/q/qiguo/yunxuan/ROOTFILE/NTuple_Output/Merge/2016UL/V1/"
OutputDir = "/eos/user/q/qiguo/yunxuan/ROOTFILE/Tree/UL2016/V1/"
Inoutput_map = Gen_Inoutput_map(InputDir, OutputDir)
SaveDic("/eos/user/q/qiguo/gKK/transfertree/UL/2016/MC/BKG/V1/config/Files.json", Inoutput_map)

