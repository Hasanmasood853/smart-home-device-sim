#include "SecurityCamera.h"
using namespace std;
bool SecurityCamera::isValidTime(string time)
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

bool SecurityCamera::isValidResolution(string res)
{
    return (res == "720p" || res == "1080p" || res == "4K");
}

SecurityCamera::SecurityCamera(int id, string n, string l, bool on, string f, string res)
    : SmartDevice(id, n, l, on, f), resolution(res), isRecording(false),
      scheduledTime(""), scheduledAction(""), isScheduled(false)
{
    if (!isValidResolution(resolution))
    {
        cout << "Invalid resolution setting default 1080p\n";
        resolution = "1080p";
    }
}

SecurityCamera::SecurityCamera(const SecurityCamera &other) : SmartDevice(other)
{
    resolution = other.getResolution();
    isRecording = other.getIsRecording();
    scheduledTime = other.getScheduledTime();
    scheduledAction = other.getScheduledAction();
    isScheduled = other.getIsScheduled();
}

void SecurityCamera::setResolution(string res)
{
    if (!isValidResolution(res))
    {
        cout << "Invalid resolution. Use 720p, 1080p, or 4K\n";
        return;
    }
    resolution = res;
    cout << getName() << " resolution set to " << resolution << endl;
}

void SecurityCamera::startRecording()
{
    if (!getIsOn())
    {
        cout << "Camera is off - cannot start recording\n";
        return;
    }
    if (!isRecording)
    {
        isRecording = true;
        cout << getName() << " started recording at " << resolution << endl;
    }
    else
    {
        cout << getName() << " is already recording\n";
    }
}

void SecurityCamera::stopRecording()
{
    if (isRecording)
    {
        isRecording = false;
        cout << getName() << " stopped recording\n";
    }
    else
    {
        cout << getName() << " is not recording\n";
    }
}

void SecurityCamera::toggle()
{
    if (getIsOn())
    {
        cout << getName() << " turned off\n";
        if (isRecording)
        {
            stopRecording();
        }
        setisON(false);
    }
    else
    {
        cout << getName() << " turned on\n";
        setisON(true);
    }
}

void SecurityCamera::getStatus()
{
    SmartDevice::getStatus();

    cout << "Resolution: " << resolution << endl;
    if (isRecording)
    {
        cout << "Status: Recording" << endl;
    }
    else
    {
        cout << "Status: Not recording" << endl;
    }

    if (isScheduled)
    {
        cout << "Scheduled at " << scheduledTime << " to " << scheduledAction << endl;
    }
    else
    {
        cout << "No active schedule" << endl;
    }
}

void SecurityCamera::generateReport()
{
    SmartDevice::generateReport();

    cout << "Resolution: " << resolution << endl;
    cout << "Recording status: " << (isRecording ? "Recording" : "Not recording") << endl;

    if (isScheduled)
    {
        cout << "Scheduled time: " << scheduledTime << endl;
        cout << "Scheduled action: " << scheduledAction << endl;
    }
}

void SecurityCamera::restart()
{
    SmartDevice::restart();
    isRecording = false;
    resolution = "1080p";
    cout << "Camera reset to default settings" << endl;
}