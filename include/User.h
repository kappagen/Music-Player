#ifndef USER_H
#define USER_H

#include <string>

/**
 * User class represents a collaborator in the playlist system.
 * Each user has a unique name/ID used for tracking operations.
 */
class User {
private:
    std::string username;
    int userId;

public:
    User(const std::string& name, int id);
    
    std::string getUsername() const;
    int getUserId() const;
    
    std::string toString() const;
};

#endif // USER_H