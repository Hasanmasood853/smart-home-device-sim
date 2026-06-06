#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
#include "SmartDevice.h"
class Room
{
    int roomID;
    std::string roomName;
    int floor;
    SmartDevice **devices;
    int deviceCount;
    int deviceCapacity;
    void resizeDevices();

public:
    Room(int id, std::string name, int f);
    Room(const Room &obj);
    void addDevice(SmartDevice *device);
    void removeDevice(int id);
    void turnAllOff();
    void getRoomStatus();
    SmartDevice *findDeviceByID(int id);
    int getRoomID() const
    {
        return roomID;
    }
    int getDeviceCount() const
    {
        return deviceCount;
    }
    int getDeviceCapacity() const
    {
        return deviceCapacity;
    }
    std::string getRoomName() const
    {
        return roomName;
    }
    int getFloor() const
    {
        return floor;
    }
    ~Room();
};

#endif