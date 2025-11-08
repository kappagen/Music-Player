#include "User.h"

using namespace std;

User::User(const string& name, int id) : username(name), userId(id) {}

string User::getUsername() const {
    return username;
}

int User::getUserId() const {
    return userId;
}

std::string User::toString() const {
    return username + " (ID: " + std::to_string(userId) + ")";
}