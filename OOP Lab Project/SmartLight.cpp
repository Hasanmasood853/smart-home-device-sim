#include "SmartLight.h"
using namespace std;

bool SmartLight::isValidTime(std::string time)
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
bool SmartLight::isValidHexColor(const std::string &hex)
{
    if (hex.length() != 7)
    {
        return false;
    }
    if (hex[0] != '#')
    {
        return false;
    }
    for (int i = 1; i < 7; i++)
    {
        if (!isxdigit(hex[i]))
        {
            return false;
        }
    }
    return true;
}

SmartLight::SmartLight(int id, std::string n, std::string l, bool on, std::string f, int b, int c, std::string h) : SmartDevice(id, n, l, on, f), brightness(b), colorTemperature(c),
                                                                                                                    hexColor(h), scheduledTime(""), scheduledAction(""), isScheduled(false)
{
    if (colorTemperature < 2000 || colorTemperature > 6500)
    {
        cout << "Invalid color temperature range(2000-6500) setting default 4000\n";
        colorTemperature = 4000;
    }
    if (brightness < 0 || brightness > 100)
    {
        cout << "Invalid brightness range(0-100) setting default 50\n";
        brightness = 50;
    }
    if (!isValidHexColor(hexColor))
    {
        cout << "Invalid hex color setting to default #FFFFFF\n";
        hexColor = "#FFFFFF";
    }
};
SmartLight::SmartLight(const SmartLight &other) : SmartDevice(other)
{
    brightness = other.getBrightness();
    colorTemperature = other.getColorTemperature();
    hexColor = other.getHexColor();
    scheduledTime = other.getScheduledTime();
    scheduledAction = other.getScheduledAction();
    isScheduled = other.getIsScheduled();
};
void SmartLight::setBrightness(int b)
{
    if (b < 0 || b > 100)
    {
        cout << "Invalid brightess Range(0-100)\n";
        return;
    };
    brightness = b;
}
void SmartLight::setColorTemperature(int c)
{
    if (c < 2000 || c > 6500)
    {
        cout << "Invalid color temperature range(2000-6500)\n";
        return;
    }
    colorTemperature = c;
}
void SmartLight::setHexColor(string h)
{
    if (!isValidHexColor(h))
    {
        cout << "Invalid hex color\n";
        return;
    }
    hexColor = h;
}
void SmartLight::dimToSunset()
{
    brightness = 30;
    colorTemperature = 2000;
    hexColor = "#FF4500";
    cout << getName() << " dimmed to sunset mode\n";
}
void SmartLight::toggle()
{
    if (SmartDevice::getIsOn())
    {
        cout << getName() << " turned off\n";
        setisON(false);
    }
    else if (!SmartDevice::getIsOn())
    {
        cout << getName() << " turned On\n";
        setisON(true);
    }
};
void SmartLight::getStatus()
{
    SmartDevice::getStatus();
    cout << "current brightness: " << brightness << endl;
    cout << "color temperature: " << colorTemperature << endl;
    cout << "Hex color: " << hexColor << endl;
}
void SmartLight::generateReport()
{
    SmartDevice::generateReport();
    cout << "current brightness: " << brightness << endl;
    cout << "color temperature: " << colorTemperature << endl;
    cout << "Hex color: " << hexColor << endl;
}
void SmartLight::schedule(string time, string action)
{
    if (!getIsOn())
    {
        cout << "device is off can't schedule it\n";
        return;
    }
    if (!isValidTime(time))
    {
        cout << "Invalid time only supported format HH:MM\n";
        return;
    }
    if (action.empty())
    {
        cout << "action cannot be empty\n";
        return;
    }
    scheduledTime = time;
    scheduledAction = action;
    isScheduled = true;
    cout << getName() << " scheduled at " << scheduledTime << " to " << scheduledAction << endl;
};
void SmartLight::cancelSchedule()
{
    if (isScheduled)
    {
        scheduledTime = "";
        scheduledAction = "";
        isScheduled = false;
        cout << getName() << " Schedule is cancelled successfully\n";
    }
    else
    {
        cout << "No active schedule found for " << getName() << endl;
    }
}