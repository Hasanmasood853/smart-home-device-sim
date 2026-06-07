#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H
#include <iostream>
#include <string>
#include "SmartDevice.h"

class SecurityCamera : public SmartDevice
{
    std::string resolution;
    bool isRecording;
    std::string scheduledTime;
    std::string scheduledAction;
    bool isScheduled;

    bool isValidTime(std::string time);
    bool isValidResolution(std::string  res);

public:
    SecurityCamera(int id, std::string n, std::string l, bool on, std::string f, std::string res);
    SecurityCamera(const SecurityCamera &other);

    void setResolution(std::string res);
    void startRecording();
    void stopRecording();

    void toggle() override;
    void getStatus() override;
    void generateReport() override;
    void restart() override;

    std::string getResolution() const
    {
        return resolution;
    }
    bool getIsRecording() const
    {
        return isRecording;
    }
    bool getIsScheduled() const
    {
        return isScheduled;
    }
    std::string getScheduledTime() const
    {
        return scheduledTime;
    }
    std::string getScheduledAction() const
    {
        return scheduledAction;
    }

    ~SecurityCamera() {};
};

#endif