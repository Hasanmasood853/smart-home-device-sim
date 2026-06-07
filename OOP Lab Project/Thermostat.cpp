#include "Thermostat.h"

bool Thermostat::isValidTime(string time)
{
    if (time.empty())
        return false;
    if (time.length() != 5)
        return false;
    if (time[2] != ':')
        return false;
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
            continue;
        if (!isdigit(time[i]))
            return false;
    }
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    if (hours < 0 || hours > 23)
        return false;
    if (minutes < 0 || minutes > 59)
        return false;
    return true;
}

bool Thermostat::isValidTemperature(float t)
{
    return (t >= 10.0 && t <= 35.0);
}

bool Thermostat::isValidMode(string m)
{
    return (m == "heat" || m == "cool" || m == "auto");
}

Thermostat::Thermostat(int id, string n, string l, bool on, string f,
                       int temp, int target, string m)
    : SmartDevice(id, n, l, on, f), currentTemperature((float)temp),
      targetTemperature((float)target), mode(m), scheduledTime(""),
      scheduledAction(""), isScheduled(false)
{
    if (!isValidTemperature(currentTemperature))
    {
        cout << "Invalid temperature range (10-35°C) setting default 22°C\n";
        currentTemperature = 22.0;
    }

    if (!isValidTemperature(targetTemperature))
    {
        cout << "Invalid target temperature range (10-35°C) setting default 22°C\n";
        targetTemperature = 22.0;
    }

    if (!isValidMode(mode))
    {
        cout << "Invalid mode setting default auto\n";
        mode = "auto";
    }
}

Thermostat::Thermostat(const Thermostat &other) : SmartDevice(other)
{
    currentTemperature = other.getCurrentTemperature();
    targetTemperature = other.getTargetTemperature();
    mode = other.getMode();
    scheduledTime = other.getScheduledTime();
    scheduledAction = other.getScheduledAction();
    isScheduled = other.getIsScheduled();
}

void Thermostat::setCurrentTemperature(float t)
{
    if (!isValidTemperature(t))
    {
        cout << "Invalid temperature range (10-35°C)\n";
        return;
    }
    currentTemperature = t;
    cout << getName() << " current temperature set to " << currentTemperature << "°C\n";
}

void Thermostat::setTargetTemperature(float t)
{
    if (!isValidTemperature(t))
    {
        cout << "Invalid target temperature range (10-35°C)\n";
        return;
    }
    targetTemperature = t;
    cout << getName() << " target temperature set to " << targetTemperature << "°C\n";
}

void Thermostat::changeMode(string m)
{
    if (!isValidMode(m))
    {
        cout << "Invalid mode. Use heat, cool, or auto\n";
        return;
    }
    mode = m;
    cout << getName() << " mode changed to " << mode << endl;
}

void Thermostat::toggle()
{
    if (getIsOn())
    {
        cout << getName() << " turned off\n";
        setisON(false);
    }
    else
    {
        cout << getName() << " turned on\n";
        setisON(true);
    }
}

void Thermostat::getStatus()
{
    SmartDevice::getStatus();

    cout << "Current temperature: " << currentTemperature << " C" << endl;
    cout << "Target temperature: " << targetTemperature << " C" << endl;
    cout << "Mode: " << mode << endl;

    if (isScheduled)
    {
        cout << "Scheduled at " << scheduledTime << " to " << scheduledAction << endl;
    }
    else
    {
        cout << "No active schedule" << endl;
    }
}

void Thermostat::generateReport()
{
    SmartDevice::generateReport();

    cout << "Current temperature: " << currentTemperature << "°C" << endl;
    cout << "Target temperature: " << targetTemperature << "°C" << endl;
    cout << "Difference: " << (targetTemperature - currentTemperature) << "°C" << endl;
    cout << "Mode: " << mode << endl;

    if (isScheduled)
    {
        cout << "Scheduled time: " << scheduledTime << endl;
        cout << "Scheduled action: " << scheduledAction << endl;
    }
}

void Thermostat::schedule(string time, string action)
{
    if (!getIsOn())
    {
        cout << "Device is off - can't schedule it\n";
        return;
    }

    if (!isValidTime(time))
    {
        cout << "Invalid time! Only supported format: HH:MM (e.g., 14:30)\n";
        return;
    }

    if (action.empty())
    {
        cout << "Action cannot be empty\n";
        return;
    }

    scheduledTime = time;
    scheduledAction = action;
    isScheduled = true;
    cout << getName() << " scheduled at " << scheduledTime << " to " << scheduledAction << endl;
}

void Thermostat::cancelSchedule()
{
    if (isScheduled)
    {
        scheduledTime = "";
        scheduledAction = "";
        isScheduled = false;
        cout << getName() << " schedule cancelled successfully\n";
    }
    else
    {
        cout << "No active schedule found for " << getName() << endl;
    }
}

void Thermostat::restart()
{
    SmartDevice::restart();
    targetTemperature = 22.0;
    mode = "auto";
    cout << "Thermostat reset to default settings" << endl;
}
void Thermostat::showAvailableActions()
{
    cout << "Thermostat Actions: 'heat', 'cool', 'auto', 'turn_on', 'turn_off'\n";
}