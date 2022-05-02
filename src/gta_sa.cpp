#include "plugin.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include "CWorld.h"

void __fastcall FixTrucking(CRunningScript* script, void* edx, short count)
{
	script->CollectParameters(count);

	if (script->m_szName == (std::string)"truck")
		CTheScripts::ScriptParams[1].iParam = 1000;
}

void GameProcess()
{
	static float health = -1;
	static float trailerHealth = -1;

	CVehicle* vehicle = FindPlayerVehicle(-1, true);

	if (!vehicle)
	{
		health = -1;
		trailerHealth = -1;
	}

	if (vehicle && vehicle->IsDriver(FindPlayerPed()) 
		|| vehicle && FindPlayerPed()->GetPlayerInfoForThisPlayerPed()->m_pRemoteVehicle)
	{
		CVehicle* trailer = vehicle->m_pTrailer;

		if (vehicle->m_fHealth < health)
			vehicle->m_fHealth -= vehicle->m_fHealth;

		// Used for vehicle's attached using winches.
		if (vehicle->m_nWinchType && vehicle->QueryPickedUpEntityWithWinch())
			trailer = reinterpret_cast<CVehicle*>(vehicle->QueryPickedUpEntityWithWinch());

		health = vehicle->m_fHealth;

		if (trailer)
		{
			if (trailer->m_fHealth < trailerHealth)
				trailer->m_fHealth -= trailer->m_fHealth;

			trailerHealth = trailer->m_fHealth;
		}
		else
			trailerHealth = -1;
	}
}

class VehicleOHKO {
public:
    VehicleOHKO() {
		plugin::Events::gameProcessEvent += GameProcess;
		plugin::patch::RedirectCall(0x47E9E4, FixTrucking);
    }
} vehicleOHKO;