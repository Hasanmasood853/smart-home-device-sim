#include "Automation.h"
using namespace std;
void Automation::resizeActions()
{
    if (actionCount >= actionCapacity)
    {
        actionCapacity = (actionCapacity == 0) ? 1 : actionCapacity * 2;
        ActionCommand *temp = new ActionCommand[actionCapacity];
        for (int i = 0; i < actionCount; i++)
        {
            temp[i] = actionList[i];
        }
        delete[] actionList;
        actionList = temp;
    }
}
bool Automation::isValidTime(string time)
{
    if (time.empty())
        return false;
    if (time.length() != 5)
        return false;
    if (time[2] != ':')
        return false;
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
            continue;
        if (!isdigit(time[i]))
            return false;
    }
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    if (hours < 0 || hours > 23)
        return false;
    if (minutes < 0 || minutes > 59)
        return false;
    return true;
}
bool Automation::isValidCondition(string condition)
{
    if (condition == "time")
        return true;
    if (condition == "motion_detected")
        return true;
    if (condition == "device_state")
        return true;
    if (condition == "temperature")
        return true;
    return false;
}

Automation::Automation(int id, std::string condition, std::string time) : ruleID(id), triggerCondition(condition), triggerTime(time), actionCount(0), actionCapacity(10), isActive(false)
{
    if (!isValidTime(triggerTime))
    {
        cout << "Invalid time setting default 00:00" << endl;
        triggerTime = "00:00";
    }
    if (!isValidCondition(triggerCondition))
    {
        cout << "Invalid trigger condition setting to default : time" << endl;
        triggerCondition = "time";
    }
    actionList = new ActionCommand[actionCapacity];
}
Automation::Automation(const Automation &obj)
{
    ruleID = obj.getRuleID();
    triggerCondition = obj.getTriggerCondition();
    triggerTime = obj.getTriggerTime();
    actionCount = obj.getActionCount();
    actionCapacity = obj.getActionCapacity();
    isActive = obj.getIsActive();
    actionList = new ActionCommand[actionCapacity];
    for (int i = 0; i < actionCount; i++)
    {
        actionList[i].actionType = obj.actionList[i].actionType;
        actionList[i].deviceName = obj.actionList[i].deviceName;
        actionList[i].actionValue = obj.actionList[i].actionValue;
    }
}
void Automation::activate()
{
    if (getIsActive())
    {
        cout << "Rule " << getRuleID() << " already activated\n";
        return;
    }
    isActive = true;
    cout << "Rule " << getRuleID() << " activated\n";
}
void Automation::deactivate()
{
    if (!getIsActive())
    {
        cout << "Rule " << getRuleID() << " already deactivated\n";
        return;
    }
    isActive = false;
    cout << "Rule " << getRuleID() << " deactivated\n";
}
void Automation::addAction(string name, string type, string value)
{
    if (name.empty())
    {
        cout << "error: device name is empty\n";
        return;
    }
    if (type.empty())
    {
        cout << "error: device type is empty\n";
        return;
    }
    resizeActions();
    actionList[actionCount].deviceName = name;
    actionList[actionCount].actionType = type;
    actionList[actionCount].actionValue = value;
    actionCount++;
}
void Automation::removeAction(int index)
{
    if (actionCount == 0)
    {
        cout << "no actions available\n";
        return;
    }
    if (index < 0 || index >= actionCount)
    {
        cout << "Invalid remove action index\n";
        return;
    }
    string savedName = actionList[index].deviceName;
    string savedType = actionList[index].actionType;
    for (int i = index; i < actionCount - 1; i++)
    {
        actionList[i] = actionList[i + 1];
    }
    cout << savedName << " action removed: " << savedType << endl;
    actionCount--;
}
void Automation::editRule(std::string newCondition, std::string newTime)
{
    if (!isValidCondition(newCondition))
    {
        cout << "invalid trigger conditon\n";
        return;
    }
    if (!isValidTime(newTime))
    {
        cout << "invalid trigger time\n";
        return;
    }
    triggerCondition = newCondition;
    triggerTime = newTime;
    cout << "Condition & time updated successfully\n";
}
bool Automation::evaluateTrigger(string currentTime, string currentCondition)
{
    if (!getIsActive())
    {
        cout << "Rule is not active\n";
        return false;
    }
    bool isTriggerEvaluated = false;
    if (triggerCondition == "time")
    {
        if (currentTime == triggerTime)
        {
            isTriggerEvaluated = true;
        }
    }
    else if (triggerCondition == "motion_detected")
    {
        if (currentCondition == "motion_detected")
        {
            isTriggerEvaluated = true;
        }
    }
    else if (triggerCondition == "device_state")
    {
        if (currentCondition == "device_state")
        {
            isTriggerEvaluated = true;
        }
    }
    else if (triggerCondition == "temperature")
    {
        if (currentCondition == "temperature")
        {
            isTriggerEvaluated = true;
        }
    }

    if (isTriggerEvaluated)
    {
        cout << "Rule " << getRuleID() << " triggered! Executing actions...\n";
        displayActions();
    }
    return isTriggerEvaluated;
}
void Automation::displayActions()
{
    if (getActionCount() == 0)
    {
        cout << "no actions defined\n";
        return;
    }
    for (int i = 0; i < actionCount; i++)
    {
        cout << "device name: " << actionList[i].deviceName << endl;
        cout << "Action Type: " << actionList[i].actionType << endl;
        if (!actionList[i].actionValue.empty())
        {
            cout << "Action Value: " << actionList[i].actionValue << endl;
        }
    }
};
Automation::~Automation()
{
    delete[] actionList;
    actionList = nullptr;
}