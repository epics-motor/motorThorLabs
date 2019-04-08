#!../../bin/linux-x86_64/thorlabs

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/thorlabs.dbd"
thorlabs_registerRecordDeviceDriver pdbbase

cd "${TOP}/iocBoot/${IOC}"

## motorUtil (allstop & alldone)
dbLoadRecords("$(MOTOR)/db/motorUtil.db", "P=thorlabs:")

## 
< MDT695.cmd

iocInit

## motorUtil (allstop & alldone)
motorUtilInit("thorlabs:")

# Boot complete
