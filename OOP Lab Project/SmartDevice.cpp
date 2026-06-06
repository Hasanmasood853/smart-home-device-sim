#include "SmartDevice.h"
using namespace std;

int SmartDevice::totalDevices = 0;

SmartDevice::SmartDevice(int id, string n, string l, bool on, string f) : deviceID(id), location(l), name(n), isON(on), firmwareVersion(f)
{
    totalDevices++;
}

SmartDevice::SmartDevice(const SmartDevice &other)
{
    deviceID = other.getDeviceID();
    name = other.getName();
    location = other.getLocation();
    isON = other.getIsOn();
    firmwareVersion = other.getFirmwareVersion();
    totalDevices++;
}

void SmartDevice::setName(string n)
{
    name = n;
}

void SmartDevice::setLocation(string l)
{
    location = l;
}

void SmartDevice::setVersion(string f)
{
    firmwareVersion = f;
}

void SmartDevice::setisON(bool status)
{
    isON = status;
}

void SmartDevice::restart()
{
    if (!isON)
    {
        cout << "device is off\n";
        return;
    }
    cout << "restarting " << name << endl;
    isON = false;
    cout << "Turning off\n";
    cout << "Turning on\n";
    isON = true;
    cout << name << " restarted successfully\n";
}

void SmartDevice::getStatus()
{
    cout << "device name: " << getName() << endl;
    cout << "location: " << getLocation() << endl;
    if (isON)
    {
        cout << "device is ON\n";
    }
    else
    {
        cout << "device is OFF\n";
    }
}

void SmartDevice::generateReport()
{
    cout << "----- Device Report -----\n";
    cout << "Device ID: " << deviceID << "\n";
    cout << "Name: " << name << "\n";
    cout << "Location: " << location << "\n";
    if (isON)
    {
        cout << "device is ON\n";
    }
    else
    {
        cout << "device is OFF\n";
    }
    cout << "Firmware Version: " << firmwareVersion << "\n";
    cout << "-------------------------\n";
}

bool SmartDevice::operator==(const SmartDevice &other) const
{
    return (deviceID == other.getDeviceID());
}

ostream& operator<<(ostream& os, const SmartDevice& device)
{
    os << "Device ID: " << device.getDeviceID() << ", Name: " << device.getName() 
       << ", Location: " << device.getLocation() << ", Status: " 
       << (device.getIsOn() ? "ON" : "OFF");
    return os;
}