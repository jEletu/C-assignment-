#ifndef JOURNAL_H
#define JOURNAL_H

#include "publication.h"
#include <string>

class Journal : public Publication {
private:
    int volume;
    int issueNumber;
    std::string publisher;
    std::string issn;  // International Standard Serial Number

public:
    // Constructors
    Journal();
    Journal(const std::string& id, const std::string& title, 
            const std::string& author, const std::string& genre,
            int pageCount, bool isAvailable = true,
            int volume = 1, int issueNumber = 1,
            const std::string& publisher = "", const std::string& issn = "");
    
    // Getters
    int getVolume() const;
    int getIssueNumber() const;
    std::string getPublisher() const;
    std::string getIssn() const;
    
    // Setters
    void setVolume(int volume);
    void setIssueNumber(int issueNumber);
    void setPublisher(const std::string& publisher);
    void setIssn(const std::string& issn);
    
    // Override virtual methods
    void display() const override;
    std::string getType() const override;
    std::string toFileString() const override;
    
    // Journal-specific methods
    std::string getFullCitation() const;
};

#endif
