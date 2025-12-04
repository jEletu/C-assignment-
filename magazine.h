#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "publication.h"
#include <string>

class Magazine : public Publication {
private:
    int issueNumber;
    std::string publicationMonth;

public:
    Magazine();
    Magazine(const std::string& id, const std::string& title,
             const std::string& author, const std::string& genre,
             int pageCount, bool isAvailable = true,
             int issueNumber = 1, const std::string& publicationMonth = "");
    
    int getIssueNumber() const;
    std::string getPublicationMonth() const;
    
    void setIssueNumber(int issue);
    void setPublicationMonth(const std::string& month);
    
    void display() const override;
    std::string getType() const override;
    std::string toFileString() const override;
};

#endif
