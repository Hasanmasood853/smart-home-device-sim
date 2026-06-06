#include "EnergyLog.h"
using namespace std;
UsageRecord EnergyLog::getUsageRecord(int index) const
{
    if (index < 0 || index >= recordCount)
    {
        UsageRecord empty;
        empty.kilowattHours = 0.0;
        empty.timestamp = "";
        empty.date = "";
        return empty;
    }
    return usageRecords[index];
}
bool EnergyLog::isValidTimestamp(string timestamp)
{
    //"2024-01-15 14:30" valid format
    if (timestamp.empty())
        return false;
    if (timestamp.length() != 16)
        return false;
    if (timestamp[4] != '-' || timestamp[7] != '-' || timestamp[10] != ' ' || timestamp[13] != ':')
        return false;
    for (int i = 0; i < 16; i++)
    {
        if (i == 4 || i == 7 || i == 10 || i == 13)
            continue;
        if (!isdigit(timestamp[i]))
            return false;
    }
    return true;
}
void EnergyLog::resizeRecords()
{
    if (recordCount >= recordCapacity)
    {
        recordCapacity = (recordCapacity == 0) ? 1 : recordCapacity * 2;
        UsageRecord *temp = new UsageRecord[recordCapacity];
        for (int i = 0; i < recordCount; i++)
        {
            temp[i] = usageRecords[i];
        }
        delete[] usageRecords;
        usageRecords = temp;
    }
}
void EnergyLog::updateAverage()
{
    if (recordCount == 0)
    {
        averageUsage = 0.0;
        return;
    }
    float total = 0.0;
    for (int i = 0; i < recordCount; i++)
    {
        total += usageRecords[i].kilowattHours;
    }
    averageUsage = total / recordCount;
}
EnergyLog::EnergyLog(int id, SmartDevice *device)
    : logID(id), deviceReference(device),
      recordCount(0), recordCapacity(10),
      averageUsage(0.0)
{
    if (device == nullptr)
    {
        cout << "Warning: device reference is null\n";
    }
    usageRecords = new UsageRecord[recordCapacity];
}
EnergyLog::EnergyLog(const EnergyLog &obj)
    : logID(obj.getLogID()),
      deviceReference(obj.getDeviceReference()),
      recordCount(obj.getRecordCount()),
      recordCapacity(obj.getRecordCapacity()),
      averageUsage(obj.getAverageUsage())
{
    usageRecords = new UsageRecord[recordCapacity];
    for (int i = 0; i < recordCount; i++)
    {
        usageRecords[i] = obj.getUsageRecord(i);
    }
}

void EnergyLog::recordUsage(float kwh, string timestamp)
{
    if (deviceReference == nullptr)
    {
        cout << "No device reference cannot record usage\n";
        return;
    }
    if (kwh <= 0)
    {
        cout << "Invalid kwh value must be greater than 0\n";
        return;
    }
    if (!isValidTimestamp(timestamp))
    {
        cout << "Invalid timestamp format use YYYY-MM-DD HH:MM\n";
        return;
    }
    resizeRecords();
    usageRecords[recordCount].kilowattHours = kwh;
    usageRecords[recordCount].timestamp = timestamp;
    string date = "";
    for (int i = 0; i < 7; i++)
        date += timestamp[i];
    usageRecords[recordCount].date = date;
    recordCount++;
    updateAverage();
    cout << "Usage recorded: " << kwh << " kWh at " << timestamp
         << " for " << deviceReference->getName() << endl;
}

void EnergyLog::getMonthlyReport(string month)
{
    if (month.empty())
    {
        cout << "month cannot be empty\n";
        return;
    }
    if (recordCount == 0)
    {
        cout << "no records found\n";
        return;
    }
    cout << "Monthly report for " << month << endl;
    float monthlyTotal = 0.0;
    int monthlyCount = 0;
    for (int i = 0; i < recordCount; i++)
    {
        bool match = true;
        if (usageRecords[i].date.length() < month.length())
        {
            match = false;
        }
        else
        {
            for (int j = 0; j < month.length(); j++)
            {
                if (usageRecords[i].date[j] != month[j])
                {
                    match = false;
                    break;
                }
            }
        }
        if (match)
        {
            cout << "Timestamp: " << usageRecords[i].timestamp << endl;
            cout << "Usage: " << usageRecords[i].kilowattHours << " kWh\n";
            monthlyTotal += usageRecords[i].kilowattHours;
            monthlyCount++;
        }
    }
    if (monthlyCount == 0)
    {
        cout << "No records found for " << month << endl;
        return;
    }
    cout << "Total for " << month << ": " << monthlyTotal << " kWh\n";
    cout << "Records found: " << monthlyCount << endl;
}

void EnergyLog::compareToAverage(float kwh)
{
    if (recordCount == 0)
    {
        cout << "No records to compare\n";
        return;
    }
    if (kwh <= 0)
    {
        cout << "Invalid kwh value\n";
        return;
    }
    float difference = kwh - averageUsage;
    if (difference > 0)
    {
        cout << "above average by " << difference << " kWh\n";
    }
    else if (difference < 0)
    {
        difference = difference * -1;
        cout << "below average by " << difference << " kWh\n";
    }
    else
    {
        cout << "exactly at average\n";
    }
}

float EnergyLog::getTotalUsage() const
{
    float total = 0.0;
    for (int i = 0; i < recordCount; i++)
    {
        total += usageRecords[i].kilowattHours;
    }
    return total;
}

void EnergyLog::displayAllRecords()
{
    if (recordCount == 0)
    {
        cout << "No records found\n";
        return;
    }
    if (deviceReference != nullptr)
        cout << "device: " << deviceReference->getName() << endl;
    for (int i = 0; i < recordCount; i++)
    {
        cout << "record " << i + 1 << endl;
        cout << "Timestamp: " << usageRecords[i].timestamp << endl;
        cout << "usage: " << usageRecords[i].kilowattHours << " kWh\n";
    }
    cout << "Total usage: " << getTotalUsage() << " kWh\n";
    cout << "Average usage: " << averageUsage << " kWh\n";
}
EnergyLog::~EnergyLog()
{
    delete[] usageRecords;
    usageRecords = nullptr;
    deviceReference = nullptr;
}