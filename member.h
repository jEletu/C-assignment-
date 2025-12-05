#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class Publication;

class Member {
private:
    std::string memberId;
    std::string name;
    std::vector<std::string> borrowedPublications; // Store IDs of borrowed items

public:
    Member();
    Member(const std::string& memberId, const std::string& name);
    
    // Getters
    std::string getMemberId() const;
    std::string getName() const;
    const std::vector<std::string>& getBorrowedPublications() const;
    
    // Setters
    void setMemberId(const std::string& id);
    void setName(const std::string& name);
    
    // Member operations
    bool borrowPublication(const std::string& publicationId);
    bool returnPublication(const std::string& publicationId);
    bool hasBorrowed(const std::string& publicationId) const;
    int getBorrowCount() const;
    
    // Display
    void display() const;
    
    // File I/O helper
    std::string toFileString() const;
    
    // Static factory method for creating from file string
    static Member fromFileString(const std::string& fileString);
};

#endif
