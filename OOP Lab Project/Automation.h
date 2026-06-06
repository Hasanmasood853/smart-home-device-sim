#ifndef AUTOMATION_H
#define AUTOMATION_H
#include <iostream>
#include <string>
struct ActionCommand
{
    std::string deviceName;
    std::string actionType;
    std::string actionValue;
};

class Automation
{
    int ruleID, actionCount, actionCapacity;
    std::string triggerCondition, triggerTime;
    ActionCommand *actionList;
    bool isActive;
    void resizeActions();
    bool isValidTime(std::string time);
    bool isValidCondition(std::string condition);

public:
    Automation(int id, std::string condition, std::string time);
    Automation(const Automation &obj);
    void activate();
    void deactivate();
    void addAction(std::string name, std::string type, std::string value);
    void removeAction(int index);
    void editRule(std::string newCondition, std::string newTime);
    bool evaluateTrigger(std::string currentTime, std::string currentCondition);
    void displayActions();
    int getRuleID() const
    {
        return ruleID;
    }
    int getActionCount() const
    {
        return actionCount;
    }
    int getActionCapacity() const
    {
        return actionCapacity;
    }
    std::string getTriggerCondition() const
    {
        return triggerCondition;
    }
    std::string getTriggerTime() const
    {
        return triggerTime;
    }
    bool getIsActive() const
    {
        return isActive;
    }
    ~Automation();
};
#endif