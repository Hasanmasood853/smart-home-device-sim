#ifndef THERMOSTAT_H
#define THERMOSTAT_H
#include <iostream>
#include <string>
using namespace std;
#include "SmartDevice.h"
#include "Schedulable.h"

class Thermostat : public SmartDevice, public Schedulable
{
    float currentTemperature;
    float targetTemperature;
    string mode;
    string scheduledTime;
    string scheduledAction;
    bool isScheduled;

    bool isValidTime(string time);
    bool isValidTemperature(float t);
    bool isValidMode(string m);

public:
    Thermostat(int id, string n, string l, bool on, string f, int temp, int target, std::string m);
    Thermostat(const Thermostat &other);

    void setCurrentTemperature(float t);
    void setTargetTemperature(float t);
    void changeMode(string m);

    void toggle() override;
    void getStatus() override;
    void generateReport() override;
    void schedule(string time, string action) override;
    void cancelSchedule() override;
    void restart() override;

    float getCurrentTemperature() const
    {
        return currentTemperature;
    }
    float getTargetTemperature() const
    {
        return targetTemperature;
    }
    string getMode() const
    {
        return mode;
    }
    bool getIsScheduled() const
    {
        return isScheduled;
    }
    string getScheduledTime() const
    {
        return scheduledTime;
    }
    string getScheduledAction() const
    {
        return scheduledAction;
    }
    void showAvailableActions();
    ~Thermostat() {};
};

#endif