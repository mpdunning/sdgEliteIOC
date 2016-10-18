TOP=../..

include $(TOP)/configure/CONFIG

PROD_IOC = sdgElite

DBD += sdgElite.dbd

sdgElite_DBD += sdgSup.dbd
sdgElite_DBD += base.dbd
sdgElite_DBD += stream.dbd
sdgElite_DBD += asyn.dbd
sdgElite_DBD += asSupport.dbd
#sdgElite_DBD += calcSupport.dbd
sdgElite_DBD += drvAsynIPPort.dbd

sdgElite_SRCS += sdgElite_registerRecordDeviceDriver.cpp sdgASub.c
sdgElite_SRCS_DEFAULT += sdgEliteMain.cpp

sdgElite_LIBS += asyn
sdgElite_LIBS += autosave
sdgElite_LIBS += stream
#sdgElite_LIBS += calc

sdgElite_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES

