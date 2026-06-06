#ifndef ENERGYLOG_H
#define ENERGYLOG_H
#include <iostream>
#include <string>
#include "SmartDevice.h"

struct UsageRecord
{
    float kilowattHours;
    std::string timestamp;
    std::string date;
};

class EnergyLog
{
    int logID;
    SmartDevice *deviceReference;
    UsageRecord *usageRecords;
    int recordCount;
    int recordCapacity;
    float averageUsage;

    void resizeRecords();
    bool isValidTimestamp(std::string timestamp);
    void updateAverage();

public:
    EnergyLog(int id, SmartDevice *device);
    EnergyLog(const EnergyLog &obj);

    void recordUsage(float kwh, std::string timestamp);
    void getMonthlyReport(std::string month);
    void compareToAverage(float kwh);
    void displayAllRecords();

    int getLogID() const
    {
        return logID;
    }
    int getRecordCount() const
    {
        return recordCount;
    }
    int getRecordCapacity() const
    {
        return recordCapacity;
    }
    float getAverageUsage() const
    {
        return averageUsage;
    }
    float getTotalUsage() const;
    UsageRecord getUsageRecord(int index) const;
    SmartDevice *getDeviceReference() const
    {
        return deviceReference;
    }
    ~EnergyLog();
};

#endif