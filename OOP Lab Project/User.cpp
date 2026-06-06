#include "User.h"
#include <algorithm>
using namespace std;

int User::totalUsers = 0;

string User::hashPassword(string password)
{
    string hashed = "";
    for (int i = 0; i < password.length(); i++)
    {
        hashed += (password[i] + 1);
    }
    reverse(hashed.begin(), hashed.end());
    return hashed;
}

bool User::validatePassword(string password)
{
    if (password.length() < 6)
        return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
    }
    return (hasUpper && hasLower && hasDigit);
}

User::User(int id, string name, string password, string userRole)
    : userID(id), username(name), role(userRole), isLoggedIn(false), failedAttempts(0)
{
    if (!validatePassword(password))
    {
        cout << "Password too weak! Using default: Admin@123\n";
        password = "Admin@123";
    }
    passwordHash = hashPassword(password);
    totalUsers++;
    cout << "User " << username << " created with role: " << role << endl;
}

User::User(const User &other)
{
    userID = other.getUserID();
    username = other.getUsername();
    passwordHash = other.passwordHash;
    role = other.getRole();
    isLoggedIn = false;
    failedAttempts = 0;
    totalUsers++;
}

bool User::login(string password)
{
    if (isLoggedIn)
    {
        cout << username << " is already logged in!\n";
        return false;
    }
    
    if (failedAttempts >= 3)
    {
        cout << "Account locked! Too many failed attempts.\n";
        return false;
    }
    
    if (hashPassword(password) == passwordHash)
    {
        isLoggedIn = true;
        failedAttempts = 0;
        cout << "Welcome back, " << username << "!\n";
        return true;
    }
    else
    {
        failedAttempts++;
        cout << "Invalid password! Attempt " << failedAttempts << "/3\n";
        return false;
    }
}

void User::logout()
{
    if (isLoggedIn)
    {
        isLoggedIn = false;
        cout << username << " logged out successfully.\n";
    }
    else
    {
        cout << username << " is not logged in!\n";
    }
}

bool User::changePassword(string oldPassword, string newPassword)
{
    if (!isLoggedIn)
    {
        cout << "Must be logged in to change password!\n";
        return false;
    }
    
    if (hashPassword(oldPassword) != passwordHash)
    {
        cout << "Old password is incorrect!\n";
        return false;
    }
    
    if (!validatePassword(newPassword))
    {
        cout << "New password too weak! Use 6+ chars with uppercase, lowercase, digit\n";
        return false;
    }
    
    passwordHash = hashPassword(newPassword);
    cout << "Password changed successfully!\n";
    return true;
}

void User::resetFailedAttempts()
{
    failedAttempts = 0;
}

bool User::operator==(const User &other) const
{
    return (userID == other.getUserID());
}

ostream& operator<<(ostream& os, const User& user)
{
    os << "User ID: " << user.userID 
       << ", Username: " << user.username 
       << ", Role: " << user.role
       << ", Status: " << (user.isLoggedIn ? "Logged In" : "Logged Out");
    return os;
}