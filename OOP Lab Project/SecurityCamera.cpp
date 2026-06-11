#include "SecurityCamera.h"
using namespace std;

bool SecurityCamera::isValidResolution(string res)
{
    return (res == "720p" || res == "1080p" || res == "4K");
}

SecurityCamera::SecurityCamera(int id, string n, string l, bool on, string f, string res)
    : SmartDevice(id, n, l, on, f), resolution(res), isRecording(false)
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
}

void SecurityCamera::generateReport()
{
    SmartDevice::generateReport();

    cout << "Resolution: " << resolution << endl;
    cout << "Recording status: " << (isRecording ? "Recording" : "Not recording") << endl;
}

void SecurityCamera::restart()
{
    SmartDevice::restart();
    isRecording = false;
    resolution = "1080p";
    cout << "Camera restarted/reset to default settings" << endl;
}