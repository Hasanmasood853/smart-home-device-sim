#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H
#include <string>
class Schedulable
{
public:
    virtual void schedule(std::string time, std::string action) = 0;
    virtual void cancelSchedule() = 0;
    virtual void showAvailableActions() = 0;
    virtual ~Schedulable() {};
};
#endif