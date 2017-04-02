#include "SoundDriverFactory.h"
#include "NoSoundDriver.h"

int SoundDriverFactory::FactoryNextSlot = 0;
SoundDriverFactory::FactoryDriversStruct SoundDriverFactory::FactoryDrivers[MAX_FACTORY_DRIVERS];

SoundDriverInterface* SoundDriverFactory::CreateSoundDriver(SoundDriverType DriverID)
{
	SoundDriverInterface *result = NULL;
	for (int x = 0; x < FactoryNextSlot; x++)
	{
		if (FactoryDrivers[x].DriverType == DriverID)
		{
			result = FactoryDrivers[x].CreateFunction();
			break;
		}
	}
	if (result == NULL)
		result = new NoSoundDriver();

	return result;
}

bool SoundDriverFactory::RegisterSoundDriver(SoundDriverType DriverType, SoundDriverCreationFunction CreateFunction)
{
	if (FactoryNextSlot < MAX_FACTORY_DRIVERS)
	{
		FactoryDrivers[FactoryNextSlot].DriverType = DriverType;
		FactoryDrivers[FactoryNextSlot].CreateFunction = CreateFunction;
		FactoryNextSlot++;
		return true;
	}
	return false;
}