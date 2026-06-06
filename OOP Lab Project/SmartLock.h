#ifndef SMARTLOCK_H
#define SMARTLOCK_H
#include <iostream>
#include <string>
#include <cctype>
#include "SmartAppliance.h"
class SmartLock : public SmartAppliance
{
    bool isLocked;
    std::string accessCode;
    std::string *accessLog;
    int logCount;
    int logCapacity;
    bool isValidCode(std::string code);
    bool verifyCode(std::string code);
    void resizeLogCapacity();

public:
    SmartLock(int id, std::string n, std::string l, bool on, std::string f, float power, std::string mode, std::string code);
    SmartLock(const SmartLock &obj);
    void lock();
    void unlock(std::string code);
    void getAccessHistory();
    void setAccessCode(std::string code);
    void toggle() override;
    void startCycle() override;
    void getStatus() override;
    void generateReport() override;
    void restart() override;
    float getPowerUsage() override;
    bool getIsLocked() const
    {
        return isLocked;
    }
    std::string getAccessCode() const
    {
        return accessCode;
    }
    int getLogCount() const
    {
        return logCount;
    }
    int getLogCapacity() const
    {
        return logCapacity;
    }
    std::string getAccessLog(int index) const;
    ~SmartLock();
};
#endif