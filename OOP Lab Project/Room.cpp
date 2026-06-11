#include "Room.h"
using namespace std;
void Room::resizeDevices()
{
    if (deviceCount >= deviceCapacity)
    {
        deviceCapacity = (deviceCapacity == 0) ? 1 : deviceCapacity * 2;
        SmartDevice **temp = new SmartDevice *[deviceCapacity];
        for (int i = 0; i < deviceCount; i++)
        {
            temp[i] = devices[i];
        }
        delete[] devices;
        devices = temp;
    }
}
Room::Room(int id, string name, int f) : roomID(id), roomName(name), floor(f), deviceCount(0), deviceCapacity(10)
{
    devices = new SmartDevice *[deviceCapacity];
}
Room::Room(const Room &obj) : roomID(obj.getRoomID()),
                              roomName(obj.getRoomName()),
                              floor(obj.getFloor()),
                              deviceCount(obj.getDeviceCount()),
                              deviceCapacity(obj.getDeviceCapacity())
{
    devices = new SmartDevice *[deviceCapacity];
    for (int i = 0; i < deviceCount; i++)
    {
        devices[i] = obj.devices[i];
    }
}
void Room::addDevice(SmartDevice *device)
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
            cout << "Device already exists with this id\n";
            return;
        }
    }
    resizeDevices();
    devices[deviceCount] = device;
    cout << devices[deviceCount]->getName() << " successfully added\n";
    deviceCount++;
}
void Room::removeDevice(int id)
{
    int deviceIdx = -1;
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == id)
        {
            deviceIdx = i;
            break;
        }
    }
    if (deviceIdx != -1)
    {
        string name = devices[deviceIdx]->getName();
        for (int i = deviceIdx; i < deviceCount - 1; i++)
            devices[i] = devices[i + 1];
        devices[deviceCount - 1] = nullptr;
        deviceCount--;
        cout << name << " successfully removed\n";
    }
    else
    {
        cout << "Device with this id: " << id << " not found\n";
    }
}
void Room::turnAllOff()
{
    if (deviceCount == 0)
    {
        cout << "No device in room\n";
        return;
    }
    int countDevices = 0;
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getIsOn())
        {
            devices[i]->toggle();
            countDevices++;
        }
    }
    cout << countDevices << " devices turned off in " << roomName << endl;
}
void Room::getRoomStatus()
{
    cout << "Room Info:\n";
    cout << "ID: " << roomID << endl;
    cout << "Name: " << roomName << endl;
    cout << "Floor: " << floor << endl;
    if (deviceCount == 0)
    {
        cout << "No device in room\n";
        return;
    }
    cout << "Devices info:\n";
    for (int i = 0; i < deviceCount; i++)
    {
        devices[i]->getStatus();
    }
}
SmartDevice *Room::findDeviceByID(int id)
{
    if (deviceCount == 0)
    {
        cout << "No device in room\n";
        return nullptr;
    }
    for (int i = 0; i < deviceCount; i++)
    {
        if (devices[i]->getDeviceID() == id)
        {
            return devices[i];
        }
    }
    return nullptr;
}
Room::~Room()
{
    delete[] devices;
    devices = nullptr;
}