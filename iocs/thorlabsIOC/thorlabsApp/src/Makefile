TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

# The following are used for debugging messages.
#!USR_CXXFLAGS += -DDEBUG

#=============================
# Build the IOC application

PROD_IOC = thorlabs
# thorlabs.dbd will be created and installed
DBD += thorlabs.dbd

# thorlabs.dbd will be made up from these files:
thorlabs_DBD += base.dbd

# Include dbd files from all support applications:
#ifdef ASYN
thorlabs_DBD += asyn.dbd
thorlabs_DBD += drvAsynSerialPort.dbd
#endif
thorlabs_DBD += motorSupport.dbd
thorlabs_DBD += devThorLabs.dbd

# Add all the support libraries needed by this IOC
thorlabs_LIBS += ThorLabs
thorlabs_LIBS += motor
#ifdef ASYN
thorlabs_LIBS += asyn
#endif
#ifdef SNCSEQ
thorlabs_LIBS += seq pv
#endif

# thorlabs_registerRecordDeviceDriver.cpp derives from thorlabs.dbd
thorlabs_SRCS += thorlabs_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
thorlabs_SRCS_DEFAULT += thorlabsMain.cpp
thorlabs_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#thorlabs_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
thorlabs_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

