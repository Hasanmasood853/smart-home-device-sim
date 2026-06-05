#ifndef SMARTHOME_H
#define SMARTHOME_H
#include <iostream>
#include <string>
using namespace std;
#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"

class SmartHome
{
private:
    SmartDevice** devices;
    int deviceCount;
    int capacity;
    
    void resize();
    
public:
    SmartHome();
    ~SmartHome();
    
    void addDevice(SmartDevice* device);
    void removeDevice(int deviceId);
    SmartDevice* findDevice(int deviceId);
    
    void turnOnAll();
    void turnOffAll();
    
    void showAllStatus();
    void generateFullReport();
    
    void restartAll();
    void restartDevice(int deviceId);
    
    void scheduleForDevice(int deviceId, string time, string action);
    void cancelScheduleForDevice(int deviceId);
    
    int getDeviceCount() const;
    int getCapacity() const;
};

#endif