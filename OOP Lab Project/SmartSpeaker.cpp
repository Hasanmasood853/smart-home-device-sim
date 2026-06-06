#include "SmartSpeaker.h"
using namespace std;

bool SmartSpeaker::isValidVolume(int v)
{
    return v >= 0 && v <= 100;
}

void SmartSpeaker::resizeServices()
{
    if (serviceCount >= serviceCapacity)
    {
        serviceCapacity = (serviceCapacity == 0) ? 1 : serviceCapacity * 2;
        string *temp = new string[serviceCapacity];
        for (int i = 0; i < serviceCount; i++)
            temp[i] = connectedServices[i];
        delete[] connectedServices;
        connectedServices = temp;
    }
}

SmartSpeaker::SmartSpeaker(int id, string n, string l, bool on, string f,
                           float power, string mode, int v, string skill)
    : SmartAppliance(id, n, l, on, f, power, mode),
      volume(50),
      activeSkill(skill),
      serviceCount(0),
      serviceCapacity(10)
{
    connectedServices = new string[serviceCapacity];

    if (isValidVolume(v))
        volume = v;
    else
    {
        cout << "Invalid volume range(0-100) setting default 50\n";
        volume = 50;
    }

    if (skill.empty())
    {
        cout << "Skill cannot be empty setting default none\n";
        activeSkill = "none";
    }
}

SmartSpeaker::SmartSpeaker(const SmartSpeaker &other)
    : SmartAppliance(other),
      volume(other.getVolume()),
      activeSkill(other.getActiveSkill()),
      serviceCount(other.getServiceCount()),
      serviceCapacity(other.getServiceCapacity())
{
    connectedServices = new string[serviceCapacity];
    for (int i = 0; i < serviceCount; i++)
        connectedServices[i] = other.getConnectedService(i);
}

string SmartSpeaker::getConnectedService(int index) const
{
    if (index < 0 || index >= serviceCount)
        return "Invalid index";
    return connectedServices[index];
}

void SmartSpeaker::setVolume(int v)
{
    if (!isValidVolume(v))
    {
        cout << "Invalid volume range(0-100)\n";
        return;
    }
    volume = v;
    cout << getName() << " volume set to " << volume << endl;
}

void SmartSpeaker::setActiveSkill(string skill)
{
    if (skill.empty())
    {
        cout << "Skill cannot be empty\n";
        return;
    }
    activeSkill = skill;
    cout << getName() << " skill set to " << activeSkill << endl;
}

void SmartSpeaker::playMusic(string song)
{
    if (!getIsOn())
    {
        cout << getName() << " is OFF cannot play music\n";
        return;
    }
    if (song.empty())
    {
        cout << "Song name cannot be empty\n";
        return;
    }
    activeSkill = "music";
    cout << getName() << " is now playing: " << song << endl;
}

void SmartSpeaker::triggerSkill(string skill)
{
    if (!getIsOn())
    {
        cout << getName() << " is OFF cannot trigger skill\n";
        return;
    }
    if (skill.empty())
    {
        cout << "Skill name cannot be empty\n";
        return;
    }
    activeSkill = skill;
    cout << getName() << " triggered skill: " << activeSkill << endl;
}

void SmartSpeaker::addConnectedService(string service)
{
    if (service.empty())
    {
        cout << "Service name cannot be empty\n";
        return;
    }
    for (int i = 0; i < serviceCount; i++)
    {
        if (connectedServices[i] == service)
        {
            cout << service << " is already connected\n";
            return;
        }
    }
    resizeServices();
    connectedServices[serviceCount] = service;
    serviceCount++;
    cout << service << " connected to " << getName() << endl;
}

void SmartSpeaker::removeConnectedService(string service)
{
    if (serviceCount == 0)
    {
        cout << "No services connected\n";
        return;
    }

    int foundIndex = -1;
    for (int i = 0; i < serviceCount; i++)
    {
        if (connectedServices[i] == service)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1)
    {
        cout << service << " not found\n";
        return;
    }
    for (int i = foundIndex; i < serviceCount - 1; i++)
        connectedServices[i] = connectedServices[i + 1];

    serviceCount--;
    cout << service << " disconnected from " << getName() << endl;
}

void SmartSpeaker::listConnectedServices() const
{
    if (serviceCount == 0)
    {
        cout << "No services connected\n";
        return;
    }
    cout << "Connected services:\n";
    for (int i = 0; i < serviceCount; i++)
        cout << i + 1 << ". " << connectedServices[i] << endl;
}

void SmartSpeaker::toggle()
{
    if (getIsOn())
    {
        setisON(false);
        activeSkill = "none";
        cout << getName() << " turned OFF\n";
    }
    else
    {
        setisON(true);
        cout << getName() << " turned ON\n";
    }
}

void SmartSpeaker::startCycle()
{
    cout << "SmartSpeaker does not support cycle operation\n";
}

float SmartSpeaker::getPowerUsage()
{
    return getPowerRating();
}

void SmartSpeaker::getStatus()
{
    SmartAppliance::getStatus();
    cout << "Volume: " << volume << endl;
    cout << "Active skill: " << activeSkill << endl;
    cout << "Connected services: " << serviceCount << endl;
}

void SmartSpeaker::generateReport()
{
    SmartAppliance::generateReport();
    cout << "Volume: " << volume << endl;
    cout << "Active skill: " << activeSkill << endl;
    listConnectedServices();
}

void SmartSpeaker::restart()
{
    SmartAppliance::restart();
    volume = 50;
    activeSkill = "none";
    cout << getName() << " reset to defaults\n";
}

SmartSpeaker::~SmartSpeaker()
{
    delete[] connectedServices;
    connectedServices = nullptr;
}