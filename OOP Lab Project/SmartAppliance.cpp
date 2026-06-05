#include "SmartAppliance.h"

SmartAppliance::SmartAppliance(int id, string n, string l, bool on, string f, float power, string mode)
    : SmartDevice(id, n, l, on, f), powerRating(power), runMode(mode)
{
    if (powerRating < 0)
    {
        cout << "Invalid power rating setting default 100W\n";
        powerRating = 100.0;
    }
    
    if (runMode != "eco" && runMode != "normal" && runMode != "powerful")
    {
        cout << "Invalid run mode setting default normal\n";
        runMode = "normal";
    }
}

SmartAppliance::SmartAppliance(const SmartAppliance &other) : SmartDevice(other)
{
    powerRating = other.getPowerRating();
    runMode = other.getRunMode();
}

void SmartAppliance::setPowerRating(float power)
{
    if (power < 0)
    {
        cout << "Power rating cannot be negative\n";
        return;
    }
    powerRating = power;
    cout << getName() << " power rating set to " << powerRating << "W\n";
}

void SmartAppliance::setRunMode(string mode)
{
    if (mode != "eco" && mode != "normal" && mode != "powerful")
    {
        cout << "Invalid mode. Use eco, normal, or powerful\n";
        return;
    }
    runMode = mode;
    cout << getName() << " run mode set to " << runMode << endl;
}

void SmartAppliance::getStatus()
{
    SmartDevice::getStatus();
    cout << "Power rating: " << powerRating << "W" << endl;
    cout << "Run mode: " << runMode << endl;
}

void SmartAppliance::generateReport()
{
    SmartDevice::generateReport();
    cout << "Power rating: " << powerRating << "W" << endl;
    cout << "Run mode: " << runMode << endl;
}