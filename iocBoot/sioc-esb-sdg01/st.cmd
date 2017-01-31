#!../../bin/linux-x86_64/sdgElite

epicsEnvSet( "STREAM_PROTOCOL_PATH","../../sdgEliteApp/Db:.")

< envPaths

cd ${TOP}

dbLoadDatabase "dbd/sdgElite.dbd"
sdgElite_registerRecordDeviceDriver pdbbase

epicsEnvSet("P","ESB:SDG01")
drvAsynIPPortConfigure ("L0","ts-esb-06:200x",0,0,0)

#asynSetTraceMask("L0",-1,0x9)
#asynSetTraceIOMask("L0",-1,0x2)

dbLoadRecords("db/sdgElite.db","IOCNAME=${IOC},P=ESB:SDG01,PORT=P0,L=L0,A=0")

cd ${TOP}/iocBoot/${IOC}
iocInit()

