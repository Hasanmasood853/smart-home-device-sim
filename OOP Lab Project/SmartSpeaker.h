#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H
#include <iostream>
#include <string>
#include "SmartAppliance.h"

class SmartSpeaker : public SmartAppliance
{
    int volume;
    std::string activeSkill;
    std::string *connectedServices;
    int serviceCount;
    int serviceCapacity;

    bool isValidVolume(int v);
    void resizeServices();

public:
    SmartSpeaker(int id, std::string n, std::string l, bool on, std::string f, float power, std::string mode, int v, std::string skill);
    SmartSpeaker(const SmartSpeaker &other);

    void setVolume(int v);
    void setActiveSkill(std::string skill);

    int getVolume() const { return volume; }
    std::string getActiveSkill() const { return activeSkill; }
    int getServiceCount() const { return serviceCount; }
    int getServiceCapacity() const { return serviceCapacity; }
    std::string getConnectedService(int index) const;
    void playMusic(std::string song);
    void triggerSkill(std::string skill);
    void addConnectedService(std::string service);
    void removeConnectedService(std::string service);
    void listConnectedServices() const;
    void toggle() override;
    void startCycle() override;
    float getPowerUsage() override;
    void getStatus() override;
    void generateReport() override;
    void restart() override;

    ~SmartSpeaker();
};
#endif