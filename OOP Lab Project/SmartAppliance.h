#ifndef SMARTAPPLIANCE_H
#define SMARTAPPLIANCE_H
#include <iostream>
#include <string>
#include "SmartDevice.h"
using namespace std;

class SmartAppliance : public SmartDevice
{
private:
    float powerRating;
    string runMode;

public:
    SmartAppliance(int id, string n, string l, bool on, string f, float power, string mode);
    SmartAppliance(const SmartAppliance &other);

    void setPowerRating(float power);
    void setRunMode(string mode);
    virtual void startCycle() = 0;
    virtual float getPowerUsage() = 0;

    void getStatus() override;
    void generateReport() override;
    void toggle() override = 0;
    void restart() override;

    float getPowerRating() const { return powerRating; }
    string getRunMode() const { return runMode; }

    virtual ~SmartAppliance() {}
};

#endif