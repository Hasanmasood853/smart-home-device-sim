#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H
#include <iostream>
#include <string>
class SmartDevice
{
private:
    int deviceID;
    std::string name;
    std::string location;
    bool isON;
    std::string firmwareVersion;

public:
    SmartDevice(int id, std::string n, std::string l, bool on, std::string f);
    SmartDevice(const SmartDevice &obj);
    virtual void toggle() = 0;
    virtual void getStatus() = 0;
    virtual void generateReport() = 0;
    virtual void restart() = 0;
    void setName(std::string n);
    void setLocation(std::string l);
    void setVersion(std::string f);
    void setisON(bool status);
    
    int getDeviceID() const
    {
        return deviceID;
    }
    std::string getName() const
    {
        return name;
    }
    std::string getLocation() const
    {
        return location;
    }
    std::string getFirmwareVersion() const
    {
        return firmwareVersion;
    }
    bool getIsOn() const
    {
        return isON;
    }
    
    bool operator==(const SmartDevice &other) const;
    
    virtual ~SmartDevice() {};
};

#endif