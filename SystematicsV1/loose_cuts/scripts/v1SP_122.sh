#!/bin/sh
cd ..
DIRECTORY="results/v1SP_122"
if [ ! -d "$DIRECTORY" ]; then
    mkdir $DIRECTORY
    cp -r src $DIRECTORY/.
    cp GenerateV1.C $DIRECTORY/.
    cp -r EfficiencyTables $DIRECTORY/.
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_262548_262799/* > inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_262800_263230/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_263231_263359/* >> inlist.dat
mv inlist.dat $DIRECTORY/.
fi
cd $DIRECTORY
if [ ! -d "results" ]; then
    mkdir results
    mkdir logs
fi
root -l -b -q '/home/w955m639/v1flow/2015_PbPb/SystematicsV1/loose_cuts/GenerateV1.C+("v1SP_122", "inlist.dat", 10)'
# root -l -b -q '/home/w955m639/v1flow/2015_PbPb/SystematicsV1/loose_cuts/GenerateV1.C+("v1SP_122", "inlist.dat", 5000)' > logs/v1SP_122.logs
cd ..
