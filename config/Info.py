import json

class Info():
    def __init__(self, Label, jobs, year, **kwargs):
        files_json = "/eos/user/q/qiguo/gKK/transfertree/UL/2016/MC/BKG/V1/config/Files.json"
        files_json = kwargs.get("files_json",files_json)
        with open(files_json, "r") as f:
            self.files = json.load(f)

        self.Nevents_all = {
            "QCD_HT1500to2000_APV":"7846928.0",
            "ST_tW_top":"6676015",
        }
        self.sampleXS_all = {
            "QCD_HT1500to2000_APV":"1000",
            "ST_tW_top":"35600.",
        }

        self.channel = "mu"
        if Label in self.Nevents_all.keys():
            self.IsData = 1
        else:
            self.IsData = 0

        self.year = year

        if self.year == "2016":
            self.LUMI = 36.8
        if self.year == "2017":
            self.LUMI = 41.5

        self.Nevents    = self.Nevents_all[Label]
        self.sampleXS   = self.sampleXS_all[Label]
        self.inputfile  = self.files[Label][jobs]["infile"]  if Label in self.files else None
        self.outputfile = self.files[Label][jobs]["outfile"] if Label in self.files else None
        



