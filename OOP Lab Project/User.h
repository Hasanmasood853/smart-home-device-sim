#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class User
{
private:
    int userID;
    string username;
    string passwordHash;
    string role;
    bool isLoggedIn;
    int failedAttempts;
    static int totalUsers;
    
    string hashPassword(string password);
    bool validatePassword(string password);
    
public:
    User(int id, string name, string password, string userRole);
    User(const User &other);
    
    bool login(string password);
    void logout();
    bool changePassword(string oldPassword, string newPassword);
    void resetFailedAttempts();
    
    int getUserID() const { return userID; }
    string getUsername() const { return username; }
    string getRole() const { return role; }
    bool getIsLoggedIn() const { return isLoggedIn; }
    int getFailedAttempts() const { return failedAttempts; }
    static int getTotalUsers() { return totalUsers; }
    
    bool operator==(const User &other) const;
    friend ostream& operator<<(ostream& os, const User& user);
    
    ~User() {}
};

#endif