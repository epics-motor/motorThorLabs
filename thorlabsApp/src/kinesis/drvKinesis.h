#ifndef INC_DRVKINESIS_H
#define INC_DRVKINESIS_H

#include "asynMotorController.h"
#include "asynMotorAxis.h"

enum
{
	KINESIS_DC_MOTOR,
	KINESIS_STEP_MOTOR,
};

class epicsShareClass KinesisController;

class epicsShareClass KinesisAxis : public asynMotorAxis
{
	public:
		KinesisAxis(KinesisController* controller, int axisNo, int serialNo);
		
		asynStatus move(double position, int relative, double min_velocity, double max_velocity, double acceleration);
		asynStatus home(double min_velocity, double max_velocity, double acceleration, int forwards);
		asynStatus stop(double acceleration);
		asynStatus poll(bool* moving);
		
		virtual void connect() = 0;
		virtual void disconnect() = 0;
		
		virtual void startPoll(int interval) = 0;
		virtual void stopPoll() = 0;
		
		virtual void enableChannel() = 0;
		virtual void disableChannel() = 0;
		
		virtual int getPosition() = 0;
		virtual int getStatus() = 0;
		
		virtual void moveRelative(double position) = 0;
		virtual void moveToPosition(double position) = 0;
		
		virtual bool canHome() = 0;
		virtual void home() = 0;
		
		virtual int stopImmediate() = 0;
		
	protected:
		KinesisController* pC_;
		
		int axisIndex_;
		
		char serial[16];
};

class epicsShareClass KinesisDCMotorAxis : public KinesisAxis
{
	public:
		KinesisDCMotorAxis(KinesisController* controller, int axisNo, int serialNo);
		~KinesisDCMotorAxis();
		
		void connect();
		void disconnect();
		
		void startPoll(int interval);
		void stopPoll();
		
		void enableChannel();
		void disableChannel();
		
		int getPosition();
		int getStatus();
		
		void moveRelative(double position);
		void moveToPosition(double position);
		
		bool canHome();
		void home();
		
		int stopImmediate();
};

class epicsShareClass KinesisStepMotorAxis : public KinesisAxis
{
	public:
		KinesisStepMotorAxis(KinesisController* controller, int axisNo, int serialNo);
		~KinesisStepMotorAxis();
		
		void connect();
		void disconnect();
		
		void startPoll(int interval);
		void stopPoll();
		
		void enableChannel();
		void disableChannel();
		
		int getPosition();
		int getStatus();
		
		void moveRelative(double position);
		void moveToPosition(double position);
		
		bool canHome();
		void home();
		
		int stopImmediate();
};

class epicsShareClass KinesisController : public asynMotorController
{
	public:
		KinesisController(const char* portName, int serialNo, int type, double movingPollPeriod, double idlePollPeriod);
		KinesisAxis* getAxis(asynUser* pasynuser);
		KinesisAxis* getAxis(int axis);
		
	friend class KinesisAxis;
};


#endif
