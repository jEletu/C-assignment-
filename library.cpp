#include "library.h"
#include "book.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <memory>

// Template implementation needs to be in header file, 
// but we'll keep some helper functions here

// Helper function to parse a line from books.txt
std::shared_ptr<Publication> parsePublicationLine(const std::string& line) {
    std::istringstream iss(line);
    std::string id, title, author, genre;
    int pageCount;
    std::string availabilityStr;
    
    // Read until we find quoted strings
    iss >> std::ws;
    
    // Read ID (not quoted)
    iss >> id;
    
    // Read quoted title
    if (iss.peek() == ' ') iss.get();
    if (iss.peek() == '"') {
        iss.get(); // remove opening quote
        std::getline(iss, title, '"');
    } else {
        iss >> title;
    }
    
    // Read quoted author
    iss >> std::ws;
    if (iss.peek() == '"') {
        iss.get();
        std::getline(iss, author, '"');
    } else {
        iss >> author;
    }
    
    // Read quoted genre
    iss >> std::ws;
    if (iss.peek() == '"') {
        iss.get();
        std::getline(iss, genre, '"');
    } else {
        iss >> genre;
    }
    
    // Read page count and availability
    if (!(iss >> pageCount)) {
        pageCount = 0;
    }
    
    bool isAvailable = true;
    if (iss >> availabilityStr) {
        isAvailable = (availabilityStr == "1");
    }
    
    return std::make_shared<Book>(id, title, author, genre, pageCount, isAvailable);
}

// Template class method implementations (kept together for clarity)
template<typename T>
bool Library<T>::addPublication(const std::shared_ptr<T>& publication) {
    if (!publication || publications.find(publication->getId()) != publications.end()) {
        return false;
    }
    publications[publication->getId()] = publication;
    return true;
}

template<typename T>
bool Library<T>::removePublication(const std::string& publicationId) {
    auto it = publications.find(publicationId);
    if (it != publications.end()) {
        // Check if the publication is borrowed
        if (!it->second->getAvailability()) {
            return false; // Cannot remove borrowed item
        }
        publications.erase(it);
        return true;
    }
    return false;
}

template<typename T>
std::shared_ptr<T> Library<T>::findPublication(const std::string& publicationId) const {
    auto it = publications.find(publicationId);
    if (it != publications.end()) {
        return it->second;
    }
    return nullptr;
}

template<typename T>
std::vector<std::shared_ptr<T>> Library<T>::searchByTitle(const std::string& title) const {
    std::vector<std::shared_ptr<T>> results;
    std::string lowerTitle = title;
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    
    for (const auto& pair : publications) {
        std::string pubTitle = pair.second->getTitle();
        std::transform(pubTitle.begin(), pubTitle.end(), pubTitle.begin(), ::tolower);
        
        if (pubTitle.find(lowerTitle) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

template<typename T>
std::vector<std::shared_ptr<T>> Library<T>::searchByAuthor(const std::string& author) const {
    std::vector<std::shared_ptr<T>> results;
    std::string lowerAuthor = author;
    std::transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
    
    for (const auto& pair : publications) {
        std::string pubAuthor = pair.second->getAuthor();
        std::transform(pubAuthor.begin(), pubAuthor.end(), pubAuthor.begin(), ::tolower);
        
        if (pubAuthor.find(lowerAuthor) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

template<typename T>
void Library<T>::displayAllPublications() const {
    std::cout << "\n=== All Publications (" << publications.size() << ") ===\n";
    for (const auto& pair : publications) {
        pair.second->display();
        std::cout << "\n";
    }
}

template<typename T>
void Library<T>::displayAvailablePublications() const {
    std::cout << "\n=== Available Publications ===\n";
    int count = 0;
    for (const auto& pair : publications) {
        if (pair.second->getAvailability()) {
            pair.second->display();
            std::cout << "\n";
            count++;
        }
    }
    std::cout << "Total available: " << count << "\n";
}

template<typename T>
bool Library<T>::addMember(const Member& member) {
    if (members.find(member.getMemberId()) != members.end()) {
        return false;
    }
    members[member.getMemberId()] = member;
    return true;
}

template<typename T>
bool Library<T>::removeMember(const std::string& memberId) {
    auto it = members.find(memberId);
    if (it != members.end()) {
        // Check if member has borrowed items
        if (it->second.getBorrowCount() > 0) {
            return false; // Cannot remove member with borrowed items
        }
        members.erase(it);
        return true;
    }
    return false;
}

template<typename T>
Member* Library<T>::findMember(const std::string& memberId) {
    auto it = members.find(memberId);
    if (it != members.end()) {
        return &(it->second);
    }
    return nullptr;
}

template<typename T>
void Library<T>::displayAllMembers() const {
    std::cout << "\n=== All Members (" << members.size() << ") ===\n";
    for (const auto& pair : members) {
        pair.second.display();
        std::cout << "\n";
    }
}

template<typename T>
bool Library<T>::borrowPublication(const std::string& memberId, const std::string& publicationId) {
    // Find member
    Member* member = findMember(memberId);
    if (!member) {
        std::cerr << "Error: Member not found.\n";
        return false;
    }
    
    // Find publication
    auto publication = findPublication(publicationId);
    if (!publication) {
        std::cerr << "Error: Publication not found.\n";
        return false;
    }
    
    // Check availability
    if (!publication->getAvailability()) {
        std::cerr << "Error: Publication is not available.\n";
        return false;
    }
    
    // Borrow the publication
    if (member->borrowPublication(publicationId)) {
        publication->setAvailability(false);
        return true;
    }
    
    return false;
}

template<typename T>
bool Library<T>::returnPublication(const std::string& memberId, const std::string& publicationId) {
    // Find member
    Member* member = findMember(memberId);
    if (!member) {
        std::cerr << "Error: Member not found.\n";
        return false;
    }
    
    // Find publication
    auto publication = findPublication(publicationId);
    if (!publication) {
        std::cerr << "Error: Publication not found.\n";
        return false;
    }
    
    // Check if member borrowed this publication
    if (!member->hasBorrowed(publicationId)) {
        std::cerr << "Error: Member did not borrow this publication.\n";
        return false;
    }
    
    // Return the publication
    if (member->returnPublication(publicationId)) {
        publication->setAvailability(true);
        return true;
    }
    
    return false;
}

template<typename T>
bool Library<T>::loadPublicationsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }
    
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            auto publication = parsePublicationLine(line);
            if (publication) {
                addPublication(publication);
                count++;
            }
        } catch (const std::exception& e) {
            std::cerr << "Warning: Could not parse line: " << line << "\n";
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " publications from " << filename << "\n";
    return true;
}

template<typename T>
bool Library<T>::loadMembersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }
    
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            Member member = Member::fromFileString(line);
            addMember(member);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Warning: Could not parse line: " << line << "\n";
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " members from " << filename << "\n";
    return true;
}

template<typename T>
bool Library<T>::savePublicationsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing\n";
        return false;
    }
    
    int count = 0;
    for (const auto& pair : publications) {
        file << pair.second->toFileString() << "\n";
        count++;
    }
    
    file.close();
    std::cout << "Saved " << count << " publications to " << filename << "\n";
    return true;
}

template<typename T>
bool Library<T>::saveMembersToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing\n";
        return false;
    }
    
    int count = 0;
    for (const auto& pair : members) {
        file << pair.second.toFileString() << "\n";
        count++;
    }
    
    file.close();
    std::cout << "Saved " << count << " members to " << filename << "\n";
    return true;
}

template<typename T>
size_t Library<T>::getPublicationCount() const {
    return publications.size();
}

template<typename T>
size_t Library<T>::getMemberCount() const {
    return members.size();
}

// Explicit template instantiation
template class Library<Publication>;