#ifndef SMARTHOME_H
#define SMARTHOME_H
#include <iostream>
#include <string>
#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartLock.h"
#include "SmartSpeaker.h"
#include "SmartAppliance.h"
#include "Room.h"
#include "Automation.h"
#include "EnergyLog.h"
#include "Schedulable.h"
#include "User.h"

class SmartHome
{
private:
    int homeID;
    std::string ownerName;
    std::string wifiNetwork;

    SmartDevice **devices;
    int deviceCount;
    int deviceCapacity;

    Room **rooms;
    int roomCount;
    int roomCapacity;

    Automation **automations;
    int automationCount;
    int automationCapacity;

    EnergyLog **energyLogs;
    int logCount;
    int logCapacity;

    User **users;
    int userCount;
    int userCapacity;

    static int totalDevicesRegistered;

    void resizeDevices();
    void resizeRooms();
    void resizeAutomations();
    void resizeLogs();
    void resizeUsers();

public:
    SmartHome(int id, std::string owner, std::string wifi);
    ~SmartHome();

    void addDevice(SmartDevice *device);
    void removeDevice(int deviceID);
    SmartDevice *findDevice(int deviceID);

    template <typename T>
    T *findDeviceOfType(int deviceID)
    {
        for (int i = 0; i < deviceCount; i++)
        {
            if (devices[i]->getDeviceID() == deviceID)
            {
                T *typed = dynamic_cast<T *>(devices[i]);
                if (typed != nullptr)
                    return typed;
                else
                {
                    std::cout << "Device found but type mismatch\n";
                    return nullptr;
                }
            }
        }
        std::cout << "Device not found\n";
        return nullptr;
    }

    void addRoom(Room *room);
    void removeRoom(int roomID);
    Room *findRoom(int roomID);

    void addAutomation(Automation *automation);
    void removeAutomation(int ruleID);
    void evaluateAllAutomations(std::string currentTime, std::string currentCondition);

    void addEnergyLog(EnergyLog *log);
    void getEnergyDashboard();

    void scheduleForDevice(int deviceID, std::string time, std::string action);
    void cancelScheduleForDevice(int deviceID);

    void turnOnAll();
    void turnOffAll();
    void restartAll();
    void restartDevice(int deviceID);

    void showAllStatus();
    void generateFullReport();

    // User Authentication Methods
    void addUser(User *user);
    void removeUser(int userID);
    User *findUser(int userID);
    User *authenticateUser(std::string username, std::string password);
    bool hasPermission(User *user, std::string requiredRole);
    void listAllUsers();

    int getHomeID() const
    {
        return homeID;
    }
    string getOwnerName() const
    {
        return ownerName;
    }
    string getWifiNetwork() const
    {
        return wifiNetwork;
    }
    int getDeviceCount() const
    {
        return deviceCount;
    }
    int getRoomCount() const
    {
        return roomCount;
    }
    int getAutomationCount() const
    {
        return automationCount;
    }

    static int getTotalDevicesRegistered();

    friend std::ostream &operator<<(std::ostream &os, const SmartHome &home);
};

#endif