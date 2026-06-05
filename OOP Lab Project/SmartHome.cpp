#include "SmartHome.h"

SmartHome::SmartHome()
{
    deviceCount = 0;
    capacity = 5;
    devices = new SmartDevice*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        devices[i] = nullptr;
    }
    cout << "SmartHome system initialized (capacity: " << capacity << ")\n";
}

SmartHome::~SmartHome()
{
    cout << "Shutting down SmartHome system...\n";
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i] != nullptr)
        {
            delete devices[i];
            devices[i] = nullptr;
        }
    }
    delete[] devices;
    deviceCount = 0;
    capacity = 0;
    cout << "All devices cleaned up\n";
}

void SmartHome::resize()
{
    int newCapacity = capacity * 2;
    SmartDevice** newDevices = new SmartDevice*[newCapacity];
    
    for (int i = 0; i < newCapacity; i++)
    {
        newDevices[i] = nullptr;
    }
    
    for (int i = 0; i < deviceCount; i++)
    {
        newDevices[i] = devices[i];
    }
    
    delete[] devices;
    devices = newDevices;
    capacity = newCapacity;
    
    cout << "SmartHome capacity increased to " << capacity << endl;
}

void SmartHome::addDevice(SmartDevice* device)
{
    if (device == nullptr)
    {
        cout << "Cannot add null device\n";
        return;
    }
    
  
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == device->getDeviceID())
        {
            cout << "Device with ID " << device->getDeviceID() << " already exists!\n";
            return;
        }
    }
    
    if (deviceCount >= capacity)
    {
        resize();
    }
    
    devices[deviceCount] = device;
    deviceCount++;
    cout << "Device added: " << device->getName() << " (ID: " << device->getDeviceID() << ")\n";
}

void SmartHome::removeDevice(int deviceId)
{
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == deviceId)
        {
            cout << "Removing device: " << devices[i]->getName() << " (ID: " << deviceId << ")\n";
            delete devices[i];
            devices[i] = nullptr;
            
           
            for (int j = i; j < deviceCount - 1; j++)
            {
                devices[j] = devices[j + 1];
            }
            deviceCount--;
            cout << "Device removed successfully\n";
            return;
        }
    }
    cout << "Device with ID " << deviceId << " not found\n";
}

SmartDevice* SmartHome::findDevice(int deviceId)
{
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == deviceId)
        {
            return devices[i];
        }
    }
    cout << "Device with ID " << deviceId << " not found\n";
    return nullptr;
}

void SmartHome::turnOnAll()
{
    cout << "\n--- Turning ON all devices ---\n";
    for (int i = 0; i < deviceCount; i++)
    {
        if (!devices[i]->getIsOn())
        {
            devices[i]->toggle();
        }
        else
        {
            cout << devices[i]->getName() << " is already ON\n";
        }
    }
}

void SmartHome::turnOffAll()
{
    cout << "\n--- Turning OFF all devices ---\n";
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getIsOn())
        {
            devices[i]->toggle();
        }
        else
        {
            cout << devices[i]->getName() << " is already OFF\n";
        }
    }
}

void SmartHome::showAllStatus()
{
    cout << "\n========================================\n";
    cout << "        SMART HOME STATUS REPORT        \n";
    cout << "========================================\n";
    cout << "Total devices: " << deviceCount << " (Capacity: " << capacity << ")\n\n";
    
    if (deviceCount == 0)
    {
        cout << "No devices in the system\n";
        return;
    }
    
    for (int i = 0; i < deviceCount; i++)
    {
        cout << "--- Device " << (i + 1) << " ---\n";
        devices[i]->getStatus();
        cout << endl;
    }
    cout << "========================================\n";
}

void SmartHome::generateFullReport()
{
    cout << "\n========================================\n";
    cout << "      COMPLETE SYSTEM REPORT           \n";
    cout << "========================================\n";
    cout << "Report generated at system level\n";
    cout << "Total devices in network: " << deviceCount << "\n\n";
    
    if (deviceCount == 0)
    {
        cout << "No devices registered\n";
        return;
    }
    
    for (int i = 0; i < deviceCount; i++)
    {
        devices[i]->generateReport();
        cout << "----------------------------------------\n";
    }
    cout << "========================================\n";
}

void SmartHome::restartAll()
{
    cout << "\n--- Restarting ALL devices ---\n";
    for (int i = 0; i < deviceCount; i++)
    {
        devices[i]->restart();
        cout << endl;
    }
}

void SmartHome::restartDevice(int deviceId)
{
    SmartDevice* device = findDevice(deviceId);
    if (device != nullptr)
    {
        cout << "\n--- Restarting specific device ---\n";
        device->restart();
    }
}

void SmartHome::scheduleForDevice(int deviceId, string time, string action)
{
    SmartDevice* device = findDevice(deviceId);
    if (device == nullptr)
    {
        return;
    }
    
    Schedulable* schedulableDevice = dynamic_cast<Schedulable*>(device);
    if (schedulableDevice != nullptr)
    {
        schedulableDevice->schedule(time, action);
    }
    else
    {
        cout << "Device " << device->getName() << " does not support scheduling\n";
    }
}

void SmartHome::cancelScheduleForDevice(int deviceId)
{
    SmartDevice* device = findDevice(deviceId);
    if (device == nullptr)
    {
        return;
    }
    
    Schedulable* schedulableDevice = dynamic_cast<Schedulable*>(device);
    if (schedulableDevice != nullptr)
    {
        schedulableDevice->cancelSchedule();
    }
    else
    {
        cout << "Device " << device->getName() << " does not support scheduling\n";
    }
}

int SmartHome::getDeviceCount() const
{
    return deviceCount;
}

int SmartHome::getCapacity() const
{
    return capacity;
}