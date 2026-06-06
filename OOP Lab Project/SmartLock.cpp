#include "SmartLock.h"
using namespace std;
bool SmartLock::isValidCode(string code)
{
    if (code.empty())
        return false;
    if (code.length() != 4)
        return false;
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(code[i]))
        {
            return false;
        }
    }
    return true;
}
void SmartLock::resizeLogCapacity()
{
    if (logCount >= logCapacity)
    {
        logCapacity = (logCapacity == 0) ? 1 : logCapacity * 2;
        string *temp = new string[logCapacity];

        for (int i = 0; i < logCount; i++)
            temp[i] = accessLog[i];
        delete[] accessLog;
        accessLog = temp;
    }
}
bool SmartLock::verifyCode(string code)
{
    return code == accessCode;
}

SmartLock::SmartLock(int id, string n, string l, bool on, string f, float power, string mode, string code) : SmartAppliance(id, n, l, on, f, power, mode), accessCode(code), logCount(0), logCapacity(50), isLocked(true)
{
    accessLog = new string[logCapacity];
    if (!isValidCode(accessCode))
    {
        cout << "Invalid access code setting to default 0000\n";
        accessCode = "0000";
    }
};
SmartLock::SmartLock(const SmartLock &obj) : SmartAppliance(obj)
{
    isLocked = obj.getIsLocked();
    accessCode = obj.getAccessCode();
    logCount = obj.getLogCount();
    logCapacity = obj.getLogCapacity();
    accessLog = new string[obj.getLogCapacity()];
    for (int i = 0; i < logCount; i++)
    {
        accessLog[i] = obj.getAccessLog(i);
    }
}
void SmartLock::lock()
{
    if (isLocked)
    {
        cout << "Smart Lock is already locked\n";
        return;
    }
    isLocked = true;
    resizeLogCapacity();
    accessLog[logCount] = getName() + " Locked\n";
    logCount++;
    cout << getName() << " locked successfully with smartLock\n";
}
void SmartLock::unlock(string code)
{
    if (!isLocked)
    {
        cout << "Smart lock is already unlocked\n";
        return;
    }
    if (!verifyCode(code))
    {

        cout << "Failed attempt Invalid code\n";
        resizeLogCapacity();
        accessLog[logCount] = getName() + " Failed unlock attempt";
        logCount++;
        return;
    }
    isLocked = false;
    cout << getName() << " Unlocked successfully\n";
    resizeLogCapacity();
    accessLog[logCount] = getName() + " Unlocked successfully";
    logCount++;
}
float SmartLock::getPowerUsage()
{
    return getPowerRating();
}
void SmartLock::startCycle()
{
    cout << "SmartLock does not support cycle operation\n";
}
string SmartLock::getAccessLog(int index) const
{
    if (index < 0 || index >= logCount)
    {
        return "Invalid index";
    }
    return accessLog[index];
}
void SmartLock::getAccessHistory()
{
    if (logCount == 0)
    {
        cout << "No access history found\n";
        return;
    }
    for (int i = 0; i < logCount; i++)
    {
        cout << "Entry no " << i + 1 << endl;
        cout << accessLog[i] << endl;
    }
}
void SmartLock::setAccessCode(string code)
{
    if (!isValidCode(code))
    {
        cout << "Invalid access code\n";
        return;
    }
    accessCode = code;
}
void SmartLock::toggle()
{
    if (getIsOn())
        setisON(false);
    else
        setisON(true);
    if (isLocked)
    {
        isLocked = false;
        cout << getName() << " unlocked via toggle\n";
    }
    else
    {
        lock();
    }
}
void SmartLock::getStatus()
{
    SmartAppliance::getStatus();
    if (isLocked)
        cout << "State:locked" << endl;
    else if (!isLocked)
        cout << "State:Unlocked" << endl;
    cout << "Access code: **** " << endl;
    cout << "Total log entries: " << logCount << endl;
}
void SmartLock::generateReport()
{
    SmartAppliance::generateReport();
    if (isLocked)
        cout << "State:locked" << endl;
    else if (!isLocked)
        cout << "State:Unlocked" << endl;
    cout << "Total Access attempts: " << logCount << endl;
    getAccessHistory();
}
void SmartLock::restart()
{
    SmartAppliance::restart();
    isLocked = true;
    cout << "SmartLock reset — locked for security\n";
}
SmartLock::~SmartLock()
{
    delete[] accessLog;
    accessLog = nullptr;
}