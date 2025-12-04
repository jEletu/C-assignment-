#include "member.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Member::Member() : memberId(""), name("") {}

Member::Member(const std::string& memberId, const std::string& name)
    : memberId(memberId), name(name) {}

// Getters
std::string Member::getMemberId() const { return memberId; }
std::string Member::getName() const { return name; }
const std::vector<std::string>& Member::getBorrowedPublications() const { 
    return borrowedPublications; 
}

// Setters
void Member::setMemberId(const std::string& id) { memberId = id; }
void Member::setName(const std::string& name) { this->name = name; }

bool Member::borrowPublication(const std::string& publicationId) {
    // Check if already borrowed
    if (hasBorrowed(publicationId)) {
        return false;
    }
    borrowedPublications.push_back(publicationId);
    return true;
}

bool Member::returnPublication(const std::string& publicationId) {
    auto it = std::find(borrowedPublications.begin(), 
                       borrowedPublications.end(), 
                       publicationId);
    
    if (it != borrowedPublications.end()) {
        borrowedPublications.erase(it);
        return true;
    }
    return false;
}

bool Member::hasBorrowed(const std::string& publicationId) const {
    return std::find(borrowedPublications.begin(), 
                    borrowedPublications.end(), 
                    publicationId) != borrowedPublications.end();
}

int Member::getBorrowCount() const {
    return borrowedPublications.size();
}

void Member::display() const {
    std::cout << "=== Member Information ===\n";
    std::cout << "Member ID: " << memberId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Borrowed Items: " << getBorrowCount() << "\n";
    
    if (!borrowedPublications.empty()) {
        std::cout << "Currently Borrowed IDs:\n";
        for (const auto& id : borrowedPublications) {
            std::cout << "  - " << id << "\n";
        }
    }
    std::cout << "==========================\n";
}

std::string Member::toFileString() const {
    std::string result = memberId + " " + name;
    
    for (const auto& pubId : borrowedPublications) {
        result += " " + pubId;
    }
    
    return result;
}

Member Member::fromFileString(const std::string& fileString) {
    std::istringstream iss(fileString);
    std::string memberId, name;
    
    // Read member ID and name
    if (!(iss >> memberId >> name)) {
        throw std::runtime_error("Invalid member data format");
    }
    
    Member member(memberId, name);
    
    // Read borrowed publication IDs
    std::string borrowedId;
    while (iss >> borrowedId) {
        member.borrowPublication(borrowedId);
    }
    
    return member;
}
