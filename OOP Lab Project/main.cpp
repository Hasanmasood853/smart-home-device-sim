#include "SmartHome.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

void printHeader(const string& title)
{
    cout << "\n========================================\n";
    cout << title << "\n";
    cout << "========================================\n";
}

bool isValidHexColor(const string& hex)
{
    if (hex.length() != 7) return false;
    if (hex[0] != '#') return false;
    for (int i = 1; i < 7; i++)
    {
        if (!isxdigit(hex[i])) return false;
    }
    return true;
}

int getValidIntInput()
{
    int value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void displayMainMenu()
{
    cout << "\n========================================\n";
    cout << "        SMART HOME CONTROL PANEL        \n";
    cout << "========================================\n";
    cout << "1. View All Devices\n";
    cout << "2. Control a Device\n";
    cout << "3. View Rooms\n";
    cout << "4. View Energy Dashboard\n";
    cout << "5. View Automations\n";
    cout << "6. Turn ON/OFF All Devices\n";
    cout << "7. Restart a Device\n";
    cout << "8. Schedule an Action\n";
    cout << "9. User Management (Admin Only)\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter choice: ";
}

void controlDeviceMenu(SmartHome& home, User* currentUser)
{
    if (currentUser == nullptr || !currentUser->getIsLoggedIn())
    {
        cout << "Please login first!\n";
        return;
    }
    
    int id = getValidDeviceID();
    
    SmartDevice* device = home.findDevice(id);
    if (device == nullptr) 
    {
        cout << "Device not found!\n";
        return;
    }
    
    cout << "\n--- Controlling: " << device->getName() << " ---\n";
    cout << "1. Toggle ON/OFF\n";
    cout << "2. View Status\n";
    cout << "3. Restart Device\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
    {
        case 1:
            if (home.hasPermission(currentUser, "user"))
                device->toggle();
            break;
        case 2:
            device->getStatus();
            break;
        case 3:
            if (home.hasPermission(currentUser, "user"))
                device->restart();
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void controlSmartLightMenu(SmartLight* light)
{
    if (light == nullptr) return;
    
    cout << "\n--- SmartLight Controls ---\n";
    cout << "1. Set Brightness (0-100)\n";
    cout << "2. Set Color Temperature (2000-6500K)\n";
    cout << "3. Set Hex Color (#RRGGBB)\n";
    cout << "4. Dim to Sunset Mode\n";
    cout << "5. Toggle ON/OFF\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
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
            if (isValidHexColor(hex))
                light->setHexColor(hex);
            else
                cout << "Invalid hex color format! Use # followed by 6 hex digits.\n";
            break;
        }
        case 4:
            light->dimToSunset();
            break;
        case 5:
            light->toggle();
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void controlThermostatMenu(Thermostat* thermo)
{
    if (thermo == nullptr) return;
    
    cout << "\n--- Thermostat Controls ---\n";
    cout << "1. Set Current Temperature (10-35°C)\n";
    cout << "2. Set Target Temperature (10-35°C)\n";
    cout << "3. Change Mode (heat/cool/auto)\n";
    cout << "4. Toggle ON/OFF\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
    {
        case 1:
        {
            cout << "Enter current temperature (10-35): ";
            float temp = getValidIntInput();
            thermo->setCurrentTemperature(temp);
            break;
        }
        case 2:
        {
            cout << "Enter target temperature (10-35): ";
            float target = getValidIntInput();
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
        default:
            cout << "Invalid choice!\n";
    }
}

void controlCameraMenu(SecurityCamera* cam)
{
    if (cam == nullptr) return;
    
    cout << "\n--- Security Camera Controls ---\n";
    cout << "1. Start Recording\n";
    cout << "2. Stop Recording\n";
    cout << "3. Set Resolution (720p/1080p/4K)\n";
    cout << "4. Toggle ON/OFF\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
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
        default:
            cout << "Invalid choice!\n";
    }
}

void controlLockMenu(SmartLock* lock)
{
    if (lock == nullptr) return;
    
    cout << "\n--- SmartLock Controls ---\n";
    cout << "1. Unlock (with code)\n";
    cout << "2. Lock\n";
    cout << "3. View Access History\n";
    cout << "4. Change Access Code\n";
    cout << "5. Toggle ON/OFF\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
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
        default:
            cout << "Invalid choice!\n";
    }
}

void controlSpeakerMenu(SmartSpeaker* speaker)
{
    if (speaker == nullptr) return;
    
    cout << "\n--- SmartSpeaker Controls ---\n";
    cout << "1. Set Volume (0-100)\n";
    cout << "2. Play Music\n";
    cout << "3. Add Connected Service\n";
    cout << "4. Remove Connected Service\n";
    cout << "5. List Connected Services\n";
    cout << "6. Toggle ON/OFF\n";
    cout << "Enter choice: ";
    
    int choice = getValidIntInput();
    
    switch(choice)
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
            string song = getValidStringInput();
            speaker->playMusic(song);
            break;
        }
        case 3:
        {
            cout << "Enter service name: ";
            string service = getValidStringInput();
            speaker->addConnectedService(service);
            break;
        }
        case 4:
        {
            cout << "Enter service name to remove: ";
            string service = getValidStringInput();
            speaker->removeConnectedService(service);
            break;
        }
        case 5:
            speaker->listConnectedServices();
            break;
        case 6:
            speaker->toggle();
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void userManagementMenu(SmartHome& home, User* currentUser)
{
    if (currentUser == nullptr || !currentUser->getIsLoggedIn())
    {
        cout << "Please login first!\n";
        return;
    }
    
    if (!home.hasPermission(currentUser, "admin"))
    {
        cout << "Admin access required for user management!\n";
        return;
    }
    
    int choice;
    cout << "\n--- User Management ---\n";
    cout << "1. Add New User\n";
    cout << "2. Remove User\n";
    cout << "3. List All Users\n";
    cout << "4. Change Your Password\n";
    cout << "Enter choice: ";
    choice = getValidIntInput();
    
    switch(choice)
    {
        case 1:
        {
            int id;
            string name, password, role;
            cout << "Enter user ID: ";
            id = getValidIntInput();
            cout << "Enter username: ";
            name = getValidStringInput();
            cout << "Enter password (min 6 chars): ";
            password = getValidStringInput();
            cout << "Enter role (admin/user/guest): ";
            role = getValidStringInput();
            
            User* newUser = new User(id, name, password, role);
            home.addUser(newUser);
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter user ID to remove: ";
            id = getValidIntInput();
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
            cout << "Enter new password (min 6 chars): ";
            newPass = getValidStringInput();
            currentUser->changePassword(oldPass, newPass);
            break;
        }
        default:
            cout << "Invalid choice!\n";
    }
}

int main()
{
    printHeader("SMART HOME SYSTEM INITIALIZATION");
    
    SmartHome myHome(1001, "John Doe", "WiFi_Home_5G");
    
    // Create default users
    User* admin = new User(1, "admin", "Admin@123", "admin");
    myHome.addUser(admin);
    
    User* demoUser = new User(2, "user", "User@123", "user");
    myHome.addUser(demoUser);
    
    // ============================================
    // USER LOGIN
    // ============================================
    printHeader("USER LOGIN");
    
    string username, password;
    User* currentUser = nullptr;
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
        cout << "\nToo many failed attempts! Exiting...\n";
        return 0;
    }
    
    cout << "\n✅ Welcome " << currentUser->getUsername() << "! (Role: " << currentUser->getRole() << ")\n";
    
    // ============================================
    // CREATE DEVICES
    // ============================================
    printHeader("INITIALIZING DEVICES");
    
    SmartLight* livingLight = new SmartLight(1, "Living Room Light", "Living Room", true, "v1.0", 75, 4000, "#FFFFFF");
    SmartLight* kitchenLight = new SmartLight(2, "Kitchen Light", "Kitchen", false, "v1.0", 60, 3500, "#FFE4B5");
    SmartLight* bedroomLight = new SmartLight(3, "Bedroom Light", "Bedroom", true, "v1.0", 40, 3000, "#FFA500");
    Thermostat* mainThermostat = new Thermostat(4, "Main Thermostat", "Living Room", true, "v2.0", 22, 24, "heat");
    Thermostat* bedroomThermostat = new Thermostat(5, "Bedroom Thermostat", "Bedroom", false, "v2.0", 20, 22, "auto");
    SecurityCamera* frontCamera = new SecurityCamera(6, "Front Door Camera", "Entrance", true, "v1.5", "1080p");
    SecurityCamera* backCamera = new SecurityCamera(7, "Backyard Camera", "Backyard", true, "v1.5", "720p");
    SmartLock* frontLock = new SmartLock(8, "Front Door Lock", "Entrance", true, "v2.0", 50.0, "normal", "1234");
    SmartLock* backLock = new SmartLock(9, "Back Door Lock", "Backyard", false, "v2.0", 50.0, "normal", "5678");
    SmartSpeaker* livingSpeaker = new SmartSpeaker(10, "Living Room Speaker", "Living Room", true, "v3.0", 100.0, "normal", 30, "music");
    SmartSpeaker* kitchenSpeaker = new SmartSpeaker(11, "Kitchen Speaker", "Kitchen", false, "v3.0", 80.0, "eco", 20, "news");
    
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
    
    // Create Rooms
    Room* livingRoom = new Room(201, "Living Room", 1);
    Room* bedroom = new Room(202, "Bedroom", 2);
    Room* kitchen = new Room(203, "Kitchen", 1);
    
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
    
    // Create Energy Logs
    EnergyLog* lightLog = new EnergyLog(301, livingLight);
    EnergyLog* thermostatLog = new EnergyLog(302, mainThermostat);
    EnergyLog* speakerLog = new EnergyLog(303, livingSpeaker);
    
    lightLog->recordUsage(2.5, "2024-01-15 08:00");
    lightLog->recordUsage(1.8, "2024-01-15 12:00");
    lightLog->recordUsage(3.2, "2024-01-15 18:00");
    thermostatLog->recordUsage(5.5, "2024-01-15 06:00");
    thermostatLog->recordUsage(4.2, "2024-01-15 14:00");
    speakerLog->recordUsage(0.5, "2024-01-15 10:00");
    
    myHome.addEnergyLog(lightLog);
    myHome.addEnergyLog(thermostatLog);
    myHome.addEnergyLog(speakerLog);
    
    // Create Automation
    Automation* nightRoutine = new Automation(401, "time", "22:00");
    nightRoutine->addAction("Living Room Light", "setBrightness", "20");
    nightRoutine->addAction("Main Thermostat", "setMode", "auto");
    nightRoutine->activate();
    myHome.addAutomation(nightRoutine);
    
    cout << "\n✅ System ready! " << myHome.getDeviceCount() << " devices available.\n";
    
    // ============================================
    // MAIN INTERACTIVE LOOP
    // ============================================
    int choice;
    do {
        displayMainMenu();
        choice = getValidIntInput();
        
        switch(choice)
        {
            case 1:
                myHome.showAllStatus();
                break;
            case 2:
            {
                int deviceId = getValidDeviceID();
                SmartDevice* device = myHome.findDevice(deviceId);
                if (device == nullptr) break;
                
                // Check device type and show appropriate menu
                SmartLight* light = dynamic_cast<SmartLight*>(device);
                Thermostat* thermo = dynamic_cast<Thermostat*>(device);
                SecurityCamera* cam = dynamic_cast<SecurityCamera*>(device);
                SmartLock* lock = dynamic_cast<SmartLock*>(device);
                SmartSpeaker* speaker = dynamic_cast<SmartSpeaker*>(device);
                
                if (light) controlSmartLightMenu(light);
                else if (thermo) controlThermostatMenu(thermo);
                else if (cam) controlCameraMenu(cam);
                else if (lock) controlLockMenu(lock);
                else if (speaker) controlSpeakerMenu(speaker);
                else device->getStatus();
                break;
            }
            case 3:
                if (myHome.hasPermission(currentUser, "user"))
                {
                    livingRoom->getRoomStatus();
                    cout << "\n";
                    bedroom->getRoomStatus();
                    cout << "\n";
                    kitchen->getRoomStatus();
                }
                break;
            case 4:
                if (myHome.hasPermission(currentUser, "user"))
                    myHome.getEnergyDashboard();
                break;
            case 5:
                if (myHome.hasPermission(currentUser, "user"))
                    myHome.evaluateAllAutomations("22:00", "time");
                break;
            case 6:
                if (myHome.hasPermission(currentUser, "user"))
                {
                    cout << "1. Turn ON all devices\n2. Turn OFF all devices\nEnter: ";
                    int subChoice = getValidIntInput();
                    if (subChoice == 1) myHome.turnOnAll();
                    else if (subChoice == 2) myHome.turnOffAll();
                    else cout << "Invalid choice!\n";
                }
                break;
            case 7:
                if (myHome.hasPermission(currentUser, "user"))
                {
                    int id = getValidDeviceID();
                    myHome.restartDevice(id);
                }
                break;
            case 8:
                if (myHome.hasPermission(currentUser, "user"))
                {
                    int id = getValidDeviceID();
                    string time = getValidTime();
                    cout << "Enter action: ";
                    string action = getValidStringInput();
                    myHome.scheduleForDevice(id, time, action);
                }
                break;
            case 9:
                userManagementMenu(myHome, currentUser);
                break;
            case 0:
                cout << "\nGoodbye " << currentUser->getUsername() << "!\n";
                currentUser->logout();
                break;
            default:
                cout << "Invalid choice! Please enter 0-9.\n";
        }
    } while(choice != 0);
    
    printHeader("SYSTEM SHUTDOWN");
    cout << "Thank you for using Smart Home System!\n";
    
    return 0;
}