#include <stdlib.h>
#include <conio.h>
#include <iocsh.h>
#include <epicsExport.h>

#include "drvKinesis.h"

KinesisController::KinesisController(const char* asyn_port, int serial, int type, double movingPollPeriod, double idlePollPeriod)
	: asynMotorController(asyn_port,
	                      1,
	                      0,
	                      0,
	                      0,
	                      ASYN_CANBLOCK | ASYN_MULTIDEVICE,
	                      1,
	                      0,
	                      0)
{
	if      (type == KINESIS_DC_MOTOR)    { new KinesisDCMotorAxis(this, 0, serial); }
	else if (type == KINESIS_STEP_MOTOR)  { new KinesisStepMotorAxis(this, 0, serial); }
	
	startPoller(movingPollPeriod, idlePollPeriod, 2);
}

KinesisAxis* KinesisController::getAxis(asynUser* pasynUser)
{ 
	return static_cast<KinesisAxis*>(asynMotorController::getAxis(pasynUser));
}

KinesisAxis* KinesisController::getAxis(int axis)
{ 
	return static_cast<KinesisAxis*>(asynMotorController::getAxis(axis)); 
}


KinesisAxis::KinesisAxis(KinesisController* pc, int axisNo, int serial_no)
	: asynMotorAxis(pc, axisNo),
	  pC_(pc)
{
	sprintf_s(this->serial, "%d", serial_no);
	
	setDoubleParam(pC_->motorEncoderPosition_, 0.0);
	callParamCallbacks();
}

asynStatus KinesisAxis::move(double position, int relative, double minVelocity, double maxVelocity, double acceleration)
{	
	if (relative)    { this->moveRelative(position); }
	else             { this->moveToPosition(position); }
	
	return asynSuccess;
}

asynStatus KinesisAxis::home(double minVelocity, double maxVelocity, double acceleration, int forwards)
{
	if (this->canHome())    { this->home();	}
	
	return asynSuccess;
}

asynStatus KinesisAxis::poll(bool* moving)
{
	int pos = this->getPosition();
	int status = this->getStatus();
		
	setDoubleParam(this->pC_->motorPosition_, (double)pos);
	
	if ((status & 0x00000010) | (status & 0x00000020))
	{
		setIntegerParam(this->pC_->motorStatusMoving_, 1);
		setIntegerParam(this->pC_->motorStatusDirection_, (status & 0x00000010) ? 0 : 1);
		setIntegerParam(this->pC_->motorStatusDone_, 0);
		*moving = true;
	}
	else
	{
		setIntegerParam(this->pC_->motorStatusMoving_, 0);
		setIntegerParam(this->pC_->motorStatusDone_, 1);
		*moving = false;
	}
	
	setIntegerParam(this->pC_->motorStatusLowLimit_, (status & 0x00000001) ? 1 : 0);
	setIntegerParam(this->pC_->motorStatusHighLimit_,  (status & 0x00000002) ? 1 : 0);
	setIntegerParam(this->pC_->motorStatusHome_,  (status & 0x00000200) ? 1 : 0);
	setIntegerParam(this->pC_->motorStatusHomed_, (status & 0x00000400) ? 1 : 0);
	
	callParamCallbacks();
	
	return asynSuccess;
}

asynStatus KinesisAxis::stop(double acceleration)
{
	this->stopImmediate();
	
	return asynSuccess;
}


extern "C" void KinesisControllerConfig(const char* asyn_port, int serial, const char* type, double movingPollPeriod, double idlePollPeriod)
{
	std::string motor_type(type);
	
	if (motor_type == "dc" || motor_type == "DC")
	{ 
		new KinesisController(asyn_port, serial, KINESIS_DC_MOTOR, movingPollPeriod, idlePollPeriod);
	}
	else if (motor_type == "stepper" || motor_type == "Stepper" ||
	         motor_type == "step" || motor_type == "Step")
	{
		new KinesisController(asyn_port, serial, KINESIS_STEP_MOTOR, movingPollPeriod, idlePollPeriod);
	}
	else
	{
		printf("Unknown motor type: %s\n", type);
	}
}

static const iocshArg KinesisControllerArg0 = {"Motor Port Name", iocshArgString};
static const iocshArg KinesisControllerArg1 = {"Serial Number", iocshArgInt};
static const iocshArg KinesisControllerArg2 = {"Motor Type", iocshArgString};
static const iocshArg KinesisControllerArg3 = {"movingPollPeriod", iocshArgDouble};
static const iocshArg KinesisControllerArg4 = {"idlePollPeriod", iocshArgDouble};

static const iocshArg* const KinesisControllerArgs[] = {&KinesisControllerArg0, &KinesisControllerArg1, &KinesisControllerArg2, &KinesisControllerArg3, &KinesisControllerArg4};

static const iocshFuncDef KinesisControllerDef = {"KinesisControllerConfig", 5, KinesisControllerArgs};

static void KinesisControllerCallFunc(const iocshArgBuf* args)
{
	KinesisControllerConfig(args[0].sval, args[1].ival, args[2].sval, args[3].dval, args[4].dval);
}

static void KinesisRegister(void)
{
	iocshRegister(&KinesisControllerDef, KinesisControllerCallFunc);
}

extern "C"
{
	epicsExportRegistrar(KinesisRegister);
}
