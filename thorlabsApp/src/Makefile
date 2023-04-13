# Makefile
TOP = ../..
include $(TOP)/configure/CONFIG

# The following are used for debugging messages.
USR_CXXFLAGS += -DDEBUG

#OPT_CXXFLAGS = -g -O0

DBD += devThorLabs.dbd

LIBRARY_IOC = ThorLabs

# Intelligent Motion Systems driver support.
SRCS += ThorLabsRegister.cc
SRCS += devMDT695.cc drvMDT695.cc

ifeq ($(WITH_KINESIS),YES)
    SRC_DIRS += $(TOP)/thorlabsApp/src/kinesis
    
    USR_INCLUDES = -I$(THORLABS_DIR)
    
    DBD += devThorLabsKinesis.dbd
    
    SRCS += drvKinesis.cpp
    SRCS += drvKinesisStepper.cpp
    SRCS += drvKinesisDC.cpp
    
    Thorlabs.MotionControl.KCube.DCServo_DIR += $(THORLABS_DIR)
    ThorLabs_DLL_LIBS += Thorlabs.MotionControl.KCube.DCServo

    Thorlabs.MotionControl.KCube.StepperMotor_DIR += $(THORLABS_DIR)
    ThorLabs_DLL_LIBS += Thorlabs.MotionControl.KCube.StepperMotor
endif


ThorLabs_LIBS += motor asyn
ThorLabs_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES

