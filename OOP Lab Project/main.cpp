#include "SmartHome.h"
#include <iostream>
#include <string>
using namespace std;

void printHeader(const string &title)
{
    cout << "\n========================================\n";
    cout << title << "\n";
    cout << "========================================\n";
}

int getValidIntInput()
{
    int value;
    cin >> value;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number: ";
        cin >> value;
    }
    cin.ignore(1000, '\n');
    return value;
}

float getValidFloatInput()
{
    float value;
    cin >> value;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a valid decimal number: ";
        cin >> value;
    }
    cin.ignore(1000, '\n');
    return value;
}

string getValidStringInput()
{
    string value;
    getline(cin, value);
    while (value.empty())
    {
        cout << "Input cannot be empty! Please enter again: ";
        getline(cin, value);
    }
    return value;
}

int getValidDeviceID()
{
    cout << "Enter device ID: ";
    return getValidIntInput();
}

string getValidTime()
{
    string time;
    while (true)
    {
        cout << "Enter time (HH:MM format, e.g., 14:30): ";
        time = getValidStringInput();
        if (time.length() == 5 && time[2] == ':' &&
            isdigit(time[0]) && isdigit(time[1]) &&
            isdigit(time[3]) && isdigit(time[4]))
        {
            int hours = (time[0] - '0') * 10 + (time[1] - '0');
            int minutes = (time[3] - '0') * 10 + (time[4] - '0');
            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59)
                return time;
        }
        cout << "Invalid time format! Use HH:MM (00:00 to 23:59)\n";
    }
}

void controlSmartLightMenu(SmartLight *light)
{
    if (light == nullptr)
        return;

    int choice;
    do
    {
        cout << "\n--- SmartLight Controls ---\n";
        cout << "1. Set Brightness (0-100)\n";
        cout << "2. Set Color Temperature (2000-6500K)\n";
        cout << "3. Set Hex Color (#RRGGBB)\n";
        cout << "4. Dim to Sunset Mode\n";
        cout << "5. Toggle ON/OFF\n";
        cout << "6. View Status\n";
        cout << "7. Schedule Action\n";     // naya
        cout << "8. Cancel Schedule\n";     // naya
        cout << "9. Return to Main Menu\n"; // 7 se 9
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter brightness (0-100): ";
            int brightness = getValidIntInput();
            light->setBrightness(brightness);
            break;
        }
        case 2:
        {
            cout << "Enter color temperature (2000-6500K): ";
            int temp = getValidIntInput();
            light->setColorTemperature(temp);
            break;
        }
        case 3:
        {
            cout << "Enter hex color (#RRGGBB): ";
            string hex = getValidStringInput();
            light->setHexColor(hex);
            break;
        }
        case 4:
            light->dimToSunset();
            break;
        case 5:
            light->toggle();
            break;
        case 6:
            light->getStatus();
            break;
        case 7:
        {
            string time = getValidTime();
            string action;
            cout << "Valid actions: setBrightness, setColor, dimToSunset, turn_on, turn_off\n";
            cout << "Enter action: ";
            action = getValidStringInput();
            while (action != "setBrightness" &&
                   action != "setColor" &&
                   action != "dimToSunset" &&
                   action != "turn_on" &&
                   action != "turn_off")
            {
                cout << "Invalid action!\n";
                cout << "Valid actions: setBrightness, setColor, dimToSunset, turn_on, turn_off\n";
                cout << "Enter action: ";
                getline(cin, action);
            }
            light->schedule(time, action);
            break;
        }
        case 8:
            light->cancelSchedule();
            break;
        case 9:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 9);
}
void controlThermostatMenu(Thermostat *thermo)
{
    if (thermo == nullptr)
        return;

    int choice;
    do
    {
        cout << "\n--- Thermostat Controls ---\n";
        cout << "1. Set Current Temperature (10-35C)\n";
        cout << "2. Set Target Temperature (10-35C)\n";
        cout << "3. Change Mode (heat/cool/auto)\n";
        cout << "4. Toggle ON/OFF\n";
        cout << "5. Schedule Action\n";
        cout << "6. Cancel Schedule\n";
        cout << "7. View Status\n";
        cout << "8. Return to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter current temperature (10-35): ";
            float temp = getValidFloatInput();
            thermo->setCurrentTemperature(temp);
            break;
        }
        case 2:
        {
            cout << "Enter target temperature (10-35): ";
            float target = getValidFloatInput();
            thermo->setTargetTemperature(target);
            break;
        }
        case 3:
        {
            cout << "Enter mode (heat/cool/auto): ";
            string mode = getValidStringInput();
            thermo->changeMode(mode);
            break;
        }
        case 4:
            thermo->toggle();
            break;
        case 5:
        {
            string time = getValidTime();
            cout << "\nValid actions: heat, cool, auto, turn_on, turn_off\n";
            cout << "Enter action: ";
            string action = getValidStringInput();
            while (action != "heat" &&
                   action != "cool" &&
                   action != "auto" &&
                   action != "turn_on" &&
                   action != "turn_off")
            {
                cout << "Invalid action!\n";
                cout << "Enter action again: ";
                getline(cin, action);
            }
            thermo->schedule(time, action);
            break;
        }
        case 6:
            thermo->cancelSchedule();
            break;
        case 7:
            thermo->getStatus();
            break;
        case 8:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 8);
}

void controlCameraMenu(SecurityCamera *cam)
{
    if (cam == nullptr)
        return;

    int choice;
    do
    {
        cout << "\n--- Security Camera Controls ---\n";
        cout << "1. Start Recording\n";
        cout << "2. Stop Recording\n";
        cout << "3. Set Resolution (720p/1080p/4K)\n";
        cout << "4. Toggle ON/OFF\n";
        cout << "5. View Status\n";
        cout << "6. Return to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
            cam->startRecording();
            break;
        case 2:
            cam->stopRecording();
            break;
        case 3:
        {
            cout << "Enter resolution (720p/1080p/4K): ";
            string res = getValidStringInput();
            cam->setResolution(res);
            break;
        }
        case 4:
            cam->toggle();
            break;
        case 5:
            cam->getStatus();
            break;
        case 6:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

void controlLockMenu(SmartLock *lock)
{
    if (lock == nullptr)
        return;

    int choice;
    do
    {
        cout << "\n--- SmartLock Controls ---\n";
        cout << "1. Unlock (with code)\n";
        cout << "2. Lock\n";
        cout << "3. View Access History\n";
        cout << "4. Change Access Code\n";
        cout << "5. Toggle ON/OFF\n";
        cout << "6. View Status\n";
        cout << "7. Return to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter access code (4 digits): ";
            string code = getValidStringInput();
            lock->unlock(code);
            break;
        }
        case 2:
            lock->lock();
            break;
        case 3:
            lock->getAccessHistory();
            break;
        case 4:
        {
            cout << "Enter new access code (4 digits): ";
            string code = getValidStringInput();
            lock->setAccessCode(code);
            break;
        }
        case 5:
            lock->toggle();
            break;
        case 6:
            lock->getStatus();
            break;
        case 7:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 7);
}

void controlSpeakerMenu(SmartSpeaker *speaker)
{
    if (speaker == nullptr)
        return;

    int choice;
    do
    {
        cout << "\n--- SmartSpeaker Controls ---\n";
        cout << "1. Set Volume (0-100)\n";
        cout << "2. Play Music\n";
        cout << "3. Trigger Skill\n";
        cout << "4. Add Connected Service\n";
        cout << "5. Remove Connected Service\n";
        cout << "6. List Connected Services\n";
        cout << "7. Toggle ON/OFF\n";
        cout << "8. View Status\n";
        cout << "9. Return to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter volume (0-100): ";
            int vol = getValidIntInput();
            speaker->setVolume(vol);
            break;
        }
        case 2:
        {
            cout << "Enter song name: ";
            cout << "(e.g. Bohemian rap, Faasle Slowed): ";
            string song = getValidStringInput();
            speaker->playMusic(song);
            break;
        }
        case 3:
        {
            cout << "Enter skill name\n";
            cout << "(e.g. weather/timer/news/alarm): ";
            string skill = getValidStringInput();
            speaker->triggerSkill(skill);
            break;
        }
        case 4:
        {
            cout << "Enter service name\n";
            cout << "(e.g. Spotify/Netflix/YouTube/Google): ";
            string service = getValidStringInput();
            speaker->addConnectedService(service);
            break;
        }
        case 5:
        {
            cout << "Enter service name to remove: ";
            string service = getValidStringInput();
            speaker->removeConnectedService(service);
            break;
        }
        case 6:
            speaker->listConnectedServices();
            break;
        case 7:
            speaker->toggle();
            break;
        case 8:
            speaker->getStatus();
            break;
        case 9:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 9);
}

void userManagementMenu(SmartHome &home, User *currentUser)
{
    if (currentUser == nullptr || !currentUser->getIsLoggedIn())
    {
        cout << "Please login first!\n";
        return;
    }
    if (!home.hasPermission(currentUser, "admin"))
    {
        cout << "Admin access required!\n";
        return;
    }

    int choice;
    do
    {
        cout << "\n--- User Management ---\n";
        cout << "1. Add New User\n";
        cout << "2. Remove User\n";
        cout << "3. List All Users\n";
        cout << "4. Change Your Password\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidIntInput();

        switch (choice)
        {
        case 1:
        {
            int id;
            string name, pass, role;
            cout << "Enter user ID: ";
            id = getValidIntInput();
            cout << "Enter username: ";
            name = getValidStringInput();
            cout << "Enter password (min 6 chars): ";
            pass = getValidStringInput();
            cout << "Enter role (admin/user/guest): ";
            role = getValidStringInput();
            User *newUser = new User(id, name, pass, role);
            home.addUser(newUser);
            break;
        }
        case 2:
        {
            cout << "Enter user ID to remove: ";
            int id = getValidIntInput();
            if (id == currentUser->getUserID())
            {
                cout << "You cannot remove your own account while logged in!\n";
                break;
            }
            home.removeUser(id);
            break;
        }
        case 3:
            home.listAllUsers();
            break;
        case 4:
        {
            string oldPass, newPass;
            cout << "Enter old password: ";
            oldPass = getValidStringInput();
            cout << "Enter new password: ";
            newPass = getValidStringInput();
            currentUser->changePassword(oldPass, newPass);
            break;
        }
        case 5:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void displayMainMenu()
{
    cout << "\n========================================\n";
    cout << "        SMART HOME CONTROL PANEL        \n";
    cout << "========================================\n";
    cout << "1. View All Devices Status\n";
    cout << "2. Control a Device\n";
    cout << "3. View All Rooms\n";
    cout << "4. View Energy Dashboard\n";
    cout << "5. Automations Panel\n";
    cout << "6. Turn ON/OFF All Devices\n";
    cout << "7. Restart a Device\n";
    cout << "8. Schedule an Action\n";
    cout << "9. User Management (Admin Only)\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter choice: ";
}

int main()
{
    printHeader("SMART HOME SYSTEM INITIALIZATION");

    SmartHome myHome(1001, "Zaid Farid", "WiFi_Home_5G");

    User *admin = new User(1, "admin", "Admin@123", "admin");
    myHome.addUser(admin);
    User *demoUser = new User(2, "user", "User@123", "user");
    myHome.addUser(demoUser);
    bool systemRunning = true;
    while (systemRunning)
    {
        printHeader("USER LOGIN");

        string username, password;
        User *currentUser = nullptr;
        int loginAttempts = 0;

        while (currentUser == nullptr && loginAttempts < 3)
        {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            currentUser = myHome.authenticateUser(username, password);
            loginAttempts++;
            if (currentUser == nullptr && loginAttempts < 3)
                cout << "Invalid credentials! " << (3 - loginAttempts) << " attempts left\n";
        }

        if (currentUser == nullptr)
        {
            cout << "\nToo many failed attempts!\n";
            cout << "1. Try Again\n2. Exit System\nEnter: ";
            int opt = getValidIntInput();
            if (opt == 2)
            {
                systemRunning = false;
            }
            continue;
        }

        cout << "\nWelcome " << currentUser->getUsername()
             << "! (Role: " << currentUser->getRole() << ")\n";

        printHeader("Initializing Devices");

        SmartLight *livingLight = new SmartLight(1, "Living Room Light", "Living Room", true, "v1.0", 75, 4000, "#FFFFFF");
        SmartLight *kitchenLight = new SmartLight(2, "Kitchen Light", "Kitchen", false, "v1.0", 60, 3500, "#FFE4B5");
        SmartLight *bedroomLight = new SmartLight(3, "Bedroom Light", "Bedroom", true, "v1.0", 40, 3000, "#FFA500");
        Thermostat *mainThermostat = new Thermostat(4, "Main Thermostat", "Living Room", true, "v2.0", 22, 24, "heat");
        Thermostat *bedroomThermostat = new Thermostat(5, "Bedroom Thermostat", "Bedroom", false, "v2.0", 20, 22, "auto");
        SecurityCamera *frontCamera = new SecurityCamera(6, "Front Door Camera", "Entrance", true, "v1.5", "1080p");
        SecurityCamera *backCamera = new SecurityCamera(7, "Backyard Camera", "Backyard", true, "v1.5", "720p");
        SmartLock *frontLock = new SmartLock(8, "Front Door Lock", "Entrance", true, "v2.0", 50.0, "normal", "1234");
        SmartLock *backLock = new SmartLock(9, "Back Door Lock", "Backyard", false, "v2.0", 50.0, "normal", "5678");
        SmartSpeaker *livingSpeaker = new SmartSpeaker(10, "Living Room Speaker", "Living Room", true, "v3.0", 100.0, "normal", 30, "music");
        livingSpeaker->addConnectedService("Spotify");
        livingSpeaker->addConnectedService("Google");
        SmartSpeaker *kitchenSpeaker = new SmartSpeaker(11, "Kitchen Speaker", "Kitchen", false, "v3.0", 80.0, "eco", 20, "news");
        kitchenSpeaker->addConnectedService("YouTube");
        kitchenSpeaker->addConnectedService("Netflix");

        myHome.addDevice(livingLight);
        myHome.addDevice(kitchenLight);
        myHome.addDevice(bedroomLight);
        myHome.addDevice(mainThermostat);
        myHome.addDevice(bedroomThermostat);
        myHome.addDevice(frontCamera);
        myHome.addDevice(backCamera);
        myHome.addDevice(frontLock);
        myHome.addDevice(backLock);
        myHome.addDevice(livingSpeaker);
        myHome.addDevice(kitchenSpeaker);

        Room *livingRoom = new Room(201, "Living Room", 1);
        Room *bedroom = new Room(202, "Bedroom", 2);
        Room *kitchen = new Room(203, "Kitchen", 1);

        livingRoom->addDevice(livingLight);
        livingRoom->addDevice(mainThermostat);
        livingRoom->addDevice(livingSpeaker);
        livingRoom->addDevice(frontCamera);
        bedroom->addDevice(bedroomLight);
        bedroom->addDevice(bedroomThermostat);
        kitchen->addDevice(kitchenLight);
        kitchen->addDevice(kitchenSpeaker);

        myHome.addRoom(livingRoom);
        myHome.addRoom(bedroom);
        myHome.addRoom(kitchen);

        EnergyLog *lightLog = new EnergyLog(301, livingLight);
        EnergyLog *thermostatLog = new EnergyLog(302, mainThermostat);
        EnergyLog *speakerLog = new EnergyLog(303, livingSpeaker);

        lightLog->recordUsage(2.5, "2024-01-15 08:00");
        lightLog->recordUsage(1.8, "2024-01-15 12:00");
        lightLog->recordUsage(3.2, "2024-01-15 18:00");
        thermostatLog->recordUsage(5.5, "2024-01-15 06:00");
        thermostatLog->recordUsage(4.2, "2024-01-15 14:00");
        speakerLog->recordUsage(0.5, "2024-01-15 10:00");

        myHome.addEnergyLog(lightLog);
        myHome.addEnergyLog(thermostatLog);
        myHome.addEnergyLog(speakerLog);

        Automation *nightRoutine = new Automation(401, "time", "22:00");
        nightRoutine->addAction("Living Room Light", "setBrightness", "20");
        nightRoutine->addAction("Main Thermostat", "setMode", "auto");
        nightRoutine->activate();
        myHome.addAutomation(nightRoutine);

        cout << myHome;
        cout << "\nSystem ready! " << myHome.getDeviceCount() << " devices loaded. "
             << "Total ever registered: "
             << SmartHome::getTotalDevicesRegistered() << "\n";

        int choice;
        do
        {
            displayMainMenu();
            choice = getValidIntInput();

            switch (choice)
            {
            case 1:
                myHome.showAllStatus();
                break;

            case 2:
            {
                int deviceId = getValidDeviceID();
                SmartLight *light = myHome.findDeviceOfType<SmartLight>(deviceId);
                Thermostat *thermo = myHome.findDeviceOfType<Thermostat>(deviceId);
                SecurityCamera *cam = myHome.findDeviceOfType<SecurityCamera>(deviceId);
                SmartLock *lock = myHome.findDeviceOfType<SmartLock>(deviceId);
                SmartSpeaker *speaker = myHome.findDeviceOfType<SmartSpeaker>(deviceId);

                if (light)
                    controlSmartLightMenu(light);
                else if (thermo)
                    controlThermostatMenu(thermo);
                else if (cam)
                    controlCameraMenu(cam);
                else if (lock)
                    controlLockMenu(lock);
                else if (speaker)
                    controlSpeakerMenu(speaker);
                else
                {
                    SmartDevice *device = myHome.findDevice(deviceId);
                    if (device != nullptr)
                        device->getStatus();
                }
                break;
            }

            case 3:
            {
                livingRoom->getRoomStatus();
                cout << "\n";
                bedroom->getRoomStatus();
                cout << "\n";
                kitchen->getRoomStatus();
                break;
            }
            case 4:
                myHome.getEnergyDashboard();
                break;

            case 5:
            {
                int autoChoice;
                do
                {
                    cout << "\n--- Automation Menu ---\n";
                    cout << "1. View All Automations\n";
                    cout << "2. Evaluate Automations\n";
                    cout << "3. Activate Automation\n";
                    cout << "4. Deactivate Automation\n";
                    cout << "5. Return to Main Menu\n";
                    cout << "Enter choice: ";
                    autoChoice = getValidIntInput();

                    switch (autoChoice)
                    {
                    case 1:
                    {
                        if (myHome.getAutomationCount() == 0)
                        {
                            cout << "No automations found\n";
                            break;
                        }
                        myHome.displayAllAutomations();
                        break;
                    }
                    case 2:
                    {
                        string currentTime = getValidTime();

                        string condition;
                        cout << "Valid: time, motion_detected, device_state, temperature\n";
                        cout << "Enter condition: ";
                        condition = getValidStringInput();
                        while (condition != "time" &&
                               condition != "motion_detected" &&
                               condition != "device_state" &&
                               condition != "temperature")
                        {
                            cout << "Invalid condition!\n";
                            cout << "Valid: time, motion_detected, device_state, temperature\n";
                            cout << "Enter condition: ";
                            getline(cin, condition);
                        }
                        myHome.evaluateAllAutomations(currentTime, condition);
                        break;
                    }
                    case 3:
                    {
                        cout << "Enter automation rule ID: ";
                        int id = getValidIntInput();
                        myHome.activateAutomation(id);
                        break;
                    }
                    case 4:
                    {
                        cout << "Enter automation rule ID: ";
                        int id = getValidIntInput();
                        myHome.deactivateAutomation(id);
                        break;
                    }
                    case 5:
                        cout << "Returning to main menu\n";
                        break;
                    default:
                        cout << "Invalid choice!\n";
                    }
                } while (autoChoice != 5);
                break;
            }

            case 6:
            {
                if (myHome.hasPermission(currentUser, "user") ||
                    myHome.hasPermission(currentUser, "admin"))
                {
                    cout << "1. Turn ON all devices\n";
                    cout << "2. Turn OFF all devices\n";
                    cout << "Enter: ";
                    int subChoice = getValidIntInput();
                    if (subChoice == 1)
                        myHome.turnOnAll();
                    else if (subChoice == 2)
                        myHome.turnOffAll();
                    else
                        cout << "Invalid choice!\n";
                }
                else
                {
                    cout << "Access Denied! User or Admin role required\n";
                }
                break;
            }

            case 7:
            {
                if (myHome.hasPermission(currentUser, "user") ||
                    myHome.hasPermission(currentUser, "admin"))
                {
                    int id = getValidDeviceID();
                    myHome.restartDevice(id);
                }
                else
                {
                    cout << "Access Denied! User or Admin role required\n";
                }
                break;
            }

            case 8:
            {
                int id = getValidDeviceID();
                SmartDevice *device = myHome.findDevice(id);
                if (device == nullptr)
                    break;

                Schedulable *schedulable = dynamic_cast<Schedulable *>(device);
                if (schedulable == nullptr)
                {
                    cout << device->getName() << " does not support scheduling\n";
                    break;
                }

                string time = getValidTime();
                string action;

                SmartLight *light = dynamic_cast<SmartLight *>(device);
                Thermostat *thermo = dynamic_cast<Thermostat *>(device);

                if (light != nullptr)
                {
                    cout << "Valid actions: setBrightness, setColor, dimToSunset, turn_on, turn_off\n";
                    cout << "Enter action: ";
                    action = getValidStringInput();
                    while (action != "setBrightness" &&
                           action != "setColor" &&
                           action != "dimToSunset" &&
                           action != "turn_on" &&
                           action != "turn_off")
                    {
                        cout << "Invalid action!\n";
                        cout << "Valid actions: setBrightness, setColor, dimToSunset, turn_on, turn_off\n";
                        cout << "Enter action: ";
                        getline(cin, action);
                    }
                }
                else if (thermo != nullptr)
                {
                    cout << "Valid actions: heat, cool, auto, turn_on, turn_off\n";
                    cout << "Enter action: ";
                    action = getValidStringInput();
                    while (action != "heat" &&
                           action != "cool" &&
                           action != "auto" &&
                           action != "turn_on" &&
                           action != "turn_off")
                    {
                        cout << "Invalid action!\n";
                        cout << "Valid actions: heat, cool, auto, turn_on, turn_off\n";
                        cout << "Enter action: ";
                        getline(cin, action);
                    }
                }

                schedulable->schedule(time, action);
                break;
            }
            case 9:
                userManagementMenu(myHome, currentUser);
                break;

            case 0:
                cout << "\nGoodbye " << currentUser->getUsername() << "!\n";
                currentUser->logout();
                cout << "Returning to login screen...\n";
                break;

            default:
                cout << "Invalid choice! Please enter 0-9.\n";
            }
        } while (choice != 0);
    }
    printHeader("System Shutdown");
    cout << "Thank you for using Smart Home System!\n";

    return 0;
}