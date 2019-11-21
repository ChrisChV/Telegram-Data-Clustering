#!/usr/bin/python

import sys
import json
import subprocess

if len(sys.argv) < 4:
    print("Missing arguments: copyLang.py <json_file> <inDir> <outDir>")
else:
    jsonFile = open(sys.argv[1])
    jsonData = jsonFile.readline()
    inDir = sys.argv[2]
    outDir = sys.argv[3]
    data = json.loads(jsonData)
    for article in data[0]['articles']:
        subprocess.call(['cp', inDir + '/' + article, outDir])
    for article in data[1]['articles']:
        subprocess.call(['cp', inDir + '/' + article, outDir])




