#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H
#include <iostream>
#include <string>
#include <cctype>
#include "SmartDevice.h"
#include "Schedulable.h"

class SmartLight : public SmartDevice, public Schedulable
{
    int brightness, colorTemperature;
    std::string hexColor, scheduledTime, scheduledAction;
    bool isScheduled;
    bool isValidHexColor(const std::string &hex);
    bool isValidTime(std::string time);

public:
    SmartLight(int id, std::string n, std::string l, bool on, std::string f, int b, int c, std::string h);
    SmartLight(const SmartLight &other);
    void setBrightness(int b);
    void setColorTemperature(int c);
    void setHexColor(std::string h);
    void dimToSunset();
    void toggle() override;
    void getStatus() override;
    void generateReport() override;
    void schedule(std::string time, std::string action) override;
    void cancelSchedule();
    void showAvailableActions() override;
    int getBrightness() const
    {
        return brightness;
    }
    int getColorTemperature() const
    {
        return colorTemperature;
    }
    std::string getHexColor() const
    {
        return hexColor;
    }
    bool getIsScheduled() const
    {
        return isScheduled;
    }
    std::string  getScheduledTime() const
    {
        return scheduledTime;
    }
    std::string  getScheduledAction() const
    {
        return scheduledAction;
    }
    ~SmartLight() {};
};

#endif