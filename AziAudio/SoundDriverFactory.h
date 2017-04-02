#pragma once
#include "SoundDriverInterface.h"

enum SoundDriverType
{
	SND_DRIVER_NOSOUND = 0x0000,
	SND_DRIVER_DS8L    = 0x1000,
	SND_DRIVER_DS8     = 0x1001,
	SND_DRIVER_XA2L    = 0x1002,
	SND_DRIVER_XA2     = 0x1003,
};


class SoundDriverFactory
{
private:
	typedef SoundDriverInterface* (*SoundDriverCreationFunction)();
	struct FactoryDriversStruct
	{
		SoundDriverType DriverType;
		SoundDriverCreationFunction CreateFunction;
	};

private:
	SoundDriverFactory() {};
	static int FactoryNextSlot;
	static const int MAX_FACTORY_DRIVERS = 20;
	static FactoryDriversStruct FactoryDrivers[MAX_FACTORY_DRIVERS];
public:
	~SoundDriverFactory() {};

	static SoundDriverInterface* CreateSoundDriver(SoundDriverType DriverID);
	static bool RegisterSoundDriver(SoundDriverType DriverType, SoundDriverCreationFunction CreateFunction);
};

