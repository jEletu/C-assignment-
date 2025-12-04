#ifndef LIBRARY_H
#define LIBRARY_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "publication.h"
#include "member.h"

template<typename T>
class Library {
private:
    std::unordered_map<std::string, std::shared_ptr<T>> publications;
    std::unordered_map<std::string, Member> members;
    
public:
    // Publication management
    bool addPublication(const std::shared_ptr<T>& publication);
    bool removePublication(const std::string& publicationId);
    std::shared_ptr<T> findPublication(const std::string& publicationId) const;
    std::vector<std::shared_ptr<T>> searchByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<T>> searchByAuthor(const std::string& author) const;
    void displayAllPublications() const;
    void displayAvailablePublications() const;
    
    // Member management
    bool addMember(const Member& member);
    bool removeMember(const std::string& memberId);
    Member* findMember(const std::string& memberId);
    void displayAllMembers() const;
    
    // Borrowing and returning
    bool borrowPublication(const std::string& memberId, const std::string& publicationId);
    bool returnPublication(const std::string& memberId, const std::string& publicationId);
    
    // File I/O
    bool loadPublicationsFromFile(const std::string& filename);
    bool loadMembersFromFile(const std::string& filename);
    bool savePublicationsToFile(const std::string& filename) const;
    bool saveMembersToFile(const std::string& filename) const;
    
    // Helper functions
    size_t getPublicationCount() const;
    size_t getMemberCount() const;
};

#endif
