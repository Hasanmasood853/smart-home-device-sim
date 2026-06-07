#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H
#include <iostream>
#include <string>
using namespace std;
#include "SmartDevice.h"
#include "Schedulable.h"

class SecurityCamera : public SmartDevice, public Schedulable
{
    string resolution;
    bool isRecording;
    string scheduledTime;
    string scheduledAction;
    bool isScheduled;

    bool isValidTime(string time);
    bool isValidResolution(string res);

public:
    SecurityCamera(int id, string n, string l, bool on, string f, string res);
    SecurityCamera(const SecurityCamera &other);

    void setResolution(string res);
    void startRecording();
    void stopRecording();

    void toggle() override;
    void getStatus() override;
    void generateReport() override;
    void schedule(string time, string action) override;
    void cancelSchedule() override;
    void restart() override;
    void showAvailableActions() override;

    string getResolution() const
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
    string getScheduledTime() const
    {
        return scheduledTime;
    }
    string getScheduledAction() const
    {
        return scheduledAction;
    }

    ~SecurityCamera() {};
};

#endif