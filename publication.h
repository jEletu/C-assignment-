#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string> 
#include <iostream> 
#include <vector> 

class Publication{ 
    protected:
    std::string id;
    std::string title;
    std::string author;
    std::string genre;
    bool isAvailable; 
    int pageCount;

    public:
    //constructors
    Publication();
    Publication(const std::string& id, const std::string& title,  const std::string& author, const std::string& genre, int pageCount, bool isAvailable = true);
    virtual~Publication()=default;
   
    //Getters 
    std::string getId() const;
    std:: string getTitle() const;
    std:: string getAuthor() const;
    std:: string getGenre() const;
    bool getAvailability() const;
    int getPageCount() const;

    //setters 
    void setId(const std::string& id); 
    void setTitle(const std::string& title);
    void setAuthor(const std:: string& Author);
    void setAvailability(bool available);
    void setPageCount(int count);

    virtual void display()const;
    virtual std::string getType()const;
    virtual std::string toFileString()const;
};
#endif


