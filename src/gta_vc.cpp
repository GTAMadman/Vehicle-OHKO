#include "plugin.h"

void GameProcess()
{
	static float health = -1;
	CVehicle* vehicle = FindPlayerVehicle();
	CVehicle* remote = FindPlayerPed()->GetPlayerInfoForThisPlayerPed()->m_pRemoteVehicle;

	if (!vehicle)
		health = -1;

	if (vehicle && vehicle->IsDriver(FindPlayerPed()) || remote)
	{
		if (remote)
			vehicle = remote;

		if (vehicle->m_fHealth < health)
			vehicle->m_fHealth -= vehicle->m_fHealth;

		health = vehicle->m_fHealth;
	}
}

class VehicleOHKO {
public:
    VehicleOHKO() {
		plugin::Events::gameProcessEvent += GameProcess;
    }
} vehicleOHKO;