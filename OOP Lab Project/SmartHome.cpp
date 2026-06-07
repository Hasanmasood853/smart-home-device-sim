#include "SmartHome.h"
using namespace std;

int SmartHome::totalDevicesRegistered = 0;

SmartHome::SmartHome(int id, string owner, string wifi)
    : homeID(id), ownerName(owner), wifiNetwork(wifi),
      deviceCount(0), deviceCapacity(5),
      roomCount(0), roomCapacity(5),
      automationCount(0), automationCapacity(5),
      logCount(0), logCapacity(5),
      userCount(0), userCapacity(5)
{
    devices = new SmartDevice *[deviceCapacity];
    for (int i = 0; i < deviceCapacity; i++)
        devices[i] = nullptr;

    rooms = new Room *[roomCapacity];
    for (int i = 0; i < roomCapacity; i++)
        rooms[i] = nullptr;

    automations = new Automation *[automationCapacity];
    for (int i = 0; i < automationCapacity; i++)
        automations[i] = nullptr;

    energyLogs = new EnergyLog *[logCapacity];
    for (int i = 0; i < logCapacity; i++)
        energyLogs[i] = nullptr;

    users = new User *[userCapacity];
    for (int i = 0; i < userCapacity; i++)
        users[i] = nullptr;

    cout << "SmartHome initialized for " << ownerName << endl;
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

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i] != nullptr)
        {
            delete rooms[i];
            rooms[i] = nullptr;
        }
    }
    delete[] rooms;

    for (int i = 0; i < automationCount; i++)
    {
        if (automations[i] != nullptr)
        {
            delete automations[i];
            automations[i] = nullptr;
        }
    }
    delete[] automations;

    for (int i = 0; i < logCount; i++)
    {
        if (energyLogs[i] != nullptr)
        {
            delete energyLogs[i];
            energyLogs[i] = nullptr;
        }
    }
    delete[] energyLogs;

    for (int i = 0; i < userCount; i++)
    {
        if (users[i] != nullptr)
        {
            delete users[i];
            users[i] = nullptr;
        }
    }
    delete[] users;

    cout << "SmartHome shut down successfully\n";
}

void SmartHome::resizeDevices()
{
    deviceCapacity *= 2;
    SmartDevice **temp = new SmartDevice *[deviceCapacity];
    for (int i = 0; i < deviceCapacity; i++)
        temp[i] = nullptr;
    for (int i = 0; i < deviceCount; i++)
        temp[i] = devices[i];
    delete[] devices;
    devices = temp;
}

void SmartHome::resizeRooms()
{
    roomCapacity *= 2;
    Room **temp = new Room *[roomCapacity];
    for (int i = 0; i < roomCapacity; i++)
        temp[i] = nullptr;
    for (int i = 0; i < roomCount; i++)
        temp[i] = rooms[i];
    delete[] rooms;
    rooms = temp;
}

void SmartHome::resizeAutomations()
{
    automationCapacity *= 2;
    Automation **temp = new Automation *[automationCapacity];
    for (int i = 0; i < automationCapacity; i++)
        temp[i] = nullptr;
    for (int i = 0; i < automationCount; i++)
        temp[i] = automations[i];
    delete[] automations;
    automations = temp;
}

void SmartHome::resizeLogs()
{
    logCapacity *= 2;
    EnergyLog **temp = new EnergyLog *[logCapacity];
    for (int i = 0; i < logCapacity; i++)
        temp[i] = nullptr;
    for (int i = 0; i < logCount; i++)
        temp[i] = energyLogs[i];
    delete[] energyLogs;
    energyLogs = temp;
}

void SmartHome::resizeUsers()
{
    userCapacity *= 2;
    User **temp = new User *[userCapacity];
    for (int i = 0; i < userCapacity; i++)
        temp[i] = nullptr;
    for (int i = 0; i < userCount; i++)
        temp[i] = users[i];
    delete[] users;
    users = temp;
}

void SmartHome::addDevice(SmartDevice *device)
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
            cout << "Device with ID " << device->getDeviceID() << " already exists\n";
            return;
        }
    }
    if (deviceCount >= deviceCapacity)
        resizeDevices();

    devices[deviceCount] = device;
    deviceCount++;
    totalDevicesRegistered++;
    cout << device->getName() << " added successfully\n";
}

void SmartHome::removeDevice(int deviceID)
{
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == deviceID)
        {
            string name = devices[i]->getName();
            delete devices[i];
            devices[i] = nullptr;
            for (int j = i; j < deviceCount - 1; j++)
                devices[j] = devices[j + 1];
            devices[deviceCount - 1] = nullptr;
            deviceCount--;
            cout << name << " removed successfully\n";
            return;
        }
    }
    cout << "Device with ID " << deviceID << " not found\n";
}

SmartDevice *SmartHome::findDevice(int deviceID)
{
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == deviceID)
            return devices[i];
    }
    cout << "Device with ID " << deviceID << " not found\n";
    return nullptr;
}

void SmartHome::addRoom(Room *room)
{
    if (room == nullptr)
    {
        cout << "Cannot add null room\n";
        return;
    }
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getRoomID() == room->getRoomID())
        {
            cout << "Room with ID " << room->getRoomID() << " already exists\n";
            return;
        }
    }
    if (roomCount >= roomCapacity)
        resizeRooms();

    rooms[roomCount] = room;
    roomCount++;
    cout << room->getRoomName() << " added successfully\n";
}

void SmartHome::removeRoom(int roomID)
{
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getRoomID() == roomID)
        {
            string name = rooms[i]->getRoomName();
            delete rooms[i];
            rooms[i] = nullptr;
            for (int j = i; j < roomCount - 1; j++)
                rooms[j] = rooms[j + 1];
            rooms[roomCount - 1] = nullptr;
            roomCount--;
            cout << name << " removed successfully\n";
            return;
        }
    }
    cout << "Room with ID " << roomID << " not found\n";
}

Room *SmartHome::findRoom(int roomID)
{
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getRoomID() == roomID)
            return rooms[i];
    }
    cout << "Room with ID " << roomID << " not found\n";
    return nullptr;
}

void SmartHome::addAutomation(Automation *automation)
{
    if (automation == nullptr)
    {
        cout << "Cannot add null automation\n";
        return;
    }
    for (int i = 0; i < automationCount; i++)
    {
        if (automations[i]->getRuleID() == automation->getRuleID())
        {
            cout << "Automation with ID " << automation->getRuleID() << " already exists\n";
            return;
        }
    }
    if (automationCount >= automationCapacity)
        resizeAutomations();

    automations[automationCount] = automation;
    automationCount++;
    cout << "Automation rule " << automation->getRuleID() << " added successfully\n";
}

void SmartHome::removeAutomation(int ruleID)
{
    for (int i = 0; i < automationCount; i++)
    {
        if (automations[i]->getRuleID() == ruleID)
        {
            delete automations[i];
            automations[i] = nullptr;
            for (int j = i; j < automationCount - 1; j++)
                automations[j] = automations[j + 1];
            automations[automationCount - 1] = nullptr;
            automationCount--;
            cout << "Automation rule " << ruleID << " removed successfully\n";
            return;
        }
    }
    cout << "Automation with ID " << ruleID << " not found\n";
}

void SmartHome::evaluateAllAutomations(string currentTime, string currentCondition)
{
    if (automationCount == 0)
    {
        cout << "No automations defined\n";
        return;
    }
    cout << "Evaluating all automation rules...\n";
    for (int i = 0; i < automationCount; i++)
        automations[i]->evaluateTrigger(currentTime, currentCondition);
}

void SmartHome::addEnergyLog(EnergyLog *log)
{
    if (log == nullptr)
    {
        cout << "Cannot add null energy log\n";
        return;
    }
    if (logCount >= logCapacity)
        resizeLogs();

    energyLogs[logCount] = log;
    logCount++;
    cout << "Energy log added successfully\n";
}

void SmartHome::getEnergyDashboard()
{
    cout << "\n========================================\n";
    cout << "         ENERGY DASHBOARD               \n";
    cout << "========================================\n";

    if (logCount == 0)
    {
        cout << "No energy logs found\n";
        return;
    }

    float grandTotal = 0.0;
    for (int i = 0; i < logCount; i++)
    {
        cout << "Log id: " << energyLogs[i]->getLogID() << endl;
        if (energyLogs[i]->getDeviceReference() != nullptr)
            cout << "Device: " << energyLogs[i]->getDeviceReference()->getName() << endl;
        cout << "Total usage: " << energyLogs[i]->getTotalUsage() << " kWh\n";
        cout << "Average usage: " << energyLogs[i]->getAverageUsage() << " kWh\n";
        cout << "----------------------------------------\n";
        grandTotal += energyLogs[i]->getTotalUsage();
    }
    cout << "Grand total energy: " << grandTotal << " kWh\n";
    cout << "========================================\n";
}

void SmartHome::scheduleForDevice(int deviceID, string time, string action)
{
    SmartDevice *device = findDevice(deviceID);
    if (device == nullptr)
        return;

    Schedulable *schedulable = dynamic_cast<Schedulable *>(device);
    if (schedulable != nullptr)
        schedulable->schedule(time, action);
    else
        cout << device->getName() << " does not support scheduling\n";
}

void SmartHome::cancelScheduleForDevice(int deviceID)
{
    SmartDevice *device = findDevice(deviceID);
    if (device == nullptr)
        return;

    Schedulable *schedulable = dynamic_cast<Schedulable *>(device);
    if (schedulable != nullptr)
        schedulable->cancelSchedule();
    else
        cout << device->getName() << " does not support scheduling\n";
}

void SmartHome::turnOnAll()
{
    cout << "\nTurning ON all devices\n";
    for (int i = 0; i < deviceCount; i++)
    {
        if (!devices[i]->getIsOn())
            devices[i]->toggle();
        else
            cout << devices[i]->getName() << " is already ON\n";
    }
}

void SmartHome::turnOffAll()
{
    cout << "\nTurning OFF all devices\n";
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getIsOn())
            devices[i]->toggle();
        else
            cout << devices[i]->getName() << " is already OFF\n";
    }
}

void SmartHome::restartAll()
{
    cout << "\nRestarting all devices\n";
    for (int i = 0; i < deviceCount; i++)
        devices[i]->restart();
}

void SmartHome::restartDevice(int deviceID)
{
    SmartDevice *device = findDevice(deviceID);
    if (device != nullptr)
        device->restart();
}

void SmartHome::showAllStatus()
{
    cout << "\n========================================\n";
    cout << "        SMART HOME STATUS               \n";
    cout << "========================================\n";
    cout << "Home id: " << homeID << endl;
    cout << "Owner: " << ownerName << endl;
    cout << "Wifi: " << wifiNetwork << endl;
    cout << "Total devices: " << deviceCount << endl;
    cout << "Total rooms: " << roomCount << endl;
    cout << "Total automations: " << automationCount << endl;
    cout << "Total devices ever registered: " << totalDevicesRegistered << endl;
    cout << "----------------------------------------\n";

    if (deviceCount == 0)
    {
        cout << "No devices in system\n";
        return;
    }
    for (int i = 0; i < deviceCount; i++)
    {
        cout << "Device " << i + 1 << ":\n";
        devices[i]->getStatus();
        cout << "----------------------------------------\n";
    }
    cout << "========================================\n";
}

void SmartHome::generateFullReport()
{
    cout << "\n========================================\n";
    cout << "       COMPLETE SYSTEM REPORT           \n";
    cout << "========================================\n";
    cout << "Home id: " << homeID << endl;
    cout << "Owner: " << ownerName << endl;
    cout << "Wifi network: " << wifiNetwork << endl;
    cout << "Total devices: " << deviceCount << endl;
    cout << "----------------------------------------\n";

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

int SmartHome::getTotalDevicesRegistered()
{
    return totalDevicesRegistered;
}

ostream &operator<<(ostream &os, const SmartHome &home)
{
    os << "========================================\n";
    os << "SmartHome ID: " << home.homeID << "\n";
    os << "Owner: " << home.ownerName << "\n";
    os << "WiFi: " << home.wifiNetwork << "\n";
    os << "Devices: " << home.deviceCount << "\n";
    os << "Rooms: " << home.roomCount << "\n";
    os << "Automations: " << home.automationCount << "\n";
    os << "========================================\n";
    return os;
}

void SmartHome::addUser(User *user)
{
    if (user == nullptr)
    {
        cout << "Cannot add null user\n";
        return;
    }
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getUserID() == user->getUserID())
        {
            cout << "User with ID " << user->getUserID() << " already exists\n";
            return;
        }
    }
    if (userCount >= userCapacity)
        resizeUsers();

    users[userCount] = user;
    userCount++;
    cout << "User " << user->getUsername() << " added successfully\n";
}

void SmartHome::removeUser(int userID)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getUserID() == userID)
        {
            string name = users[i]->getUsername();
            delete users[i];
            users[i] = nullptr;
            for (int j = i; j < userCount - 1; j++)
                users[j] = users[j + 1];
            users[userCount - 1] = nullptr;
            userCount--;
            cout << "User " << name << " removed successfully\n";
            return;
        }
    }
    cout << "User with ID " << userID << " not found\n";
}

User *SmartHome::findUser(int userID)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getUserID() == userID)
            return users[i];
    }
    cout << "User with ID " << userID << " not found\n";
    return nullptr;
}

User *SmartHome::authenticateUser(string username, string password)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getUsername() == username)
        {
            if (users[i]->login(password))
                return users[i];
            else
                return nullptr;
        }
    }
    cout << "User " << username << " not found!\n";
    return nullptr;
}

bool SmartHome::hasPermission(User *user, string requiredRole)
{
    if (user == nullptr || !user->getIsLoggedIn())
    {
        cout << "Access denied! User not logged in.\n";
        return false;
    }
    
    string userRole = user->getRole();
    if (userRole == "admin")
        return true;
    if (userRole == requiredRole)
        return true;
    
    cout << "Permission denied! " << user->getUsername() 
         << " needs " << requiredRole << " role.\n";
    return false;
}

void SmartHome::listAllUsers()
{
    if (userCount == 0)
    {
        cout << "No users registered\n";
        return;
    }
    cout << "\n--- Registered Users ---\n";
    for (int i = 0; i < userCount; i++)
    {
        cout << *users[i] << endl;
    }
}