#include <iostream>
#include <memory>
#include "library.h"
#include "book.h"
#include "member.h"

void runTests() {
    std::cout << "=== Running Library Management System Tests ===\n\n";
    
    // Create library instance
    Library<Publication> library;
    
    // Test 1: Load sample data files
    std::cout << "Test 1: Loading sample data files...\n";
    bool loadSuccess = true;
    
    if (!library.loadPublicationsFromFile("data/books.txt")) {
        std::cout << "FAILED to load publications\n";
        loadSuccess = false;
    }
    
    if (!library.loadMembersFromFile("data/members.txt")) {
        std::cout << "FAILED to load members\n";
        loadSuccess = false;
    }
    
    if (loadSuccess) {
        std::cout << "SUCCESS: Files loaded successfully\n";
        std::cout << "Loaded " << library.getPublicationCount() << " publications\n";
        std::cout << "Loaded " << library.getMemberCount() << " members\n";
    }
    std::cout << "\n";
    
    // Test 2: Add a new book
    std::cout << "Test 2: Adding a new book...\n";
    auto newBook = std::make_shared<Book>(
        "B108", 
        "The Power of Positive Thinking", 
        "Norman Vincent Peale", 
        "Motivational, spiritual", 
        240, 
        true,
        "978-0743234801", 
        1
    );
    
    if (library.addPublication(newBook)) {
        std::cout << "SUCCESS: New book added\n";
        newBook->display();
    } else {
        std::cout << "FAILED: Could not add new book (possibly duplicate ID)\n";
    }
    std::cout << "\n";
    
    // Test 3: Add a new member
    std::cout << "Test 3: Adding a new member...\n";
    Member newMember("M110", "Jane");
    if (library.addMember(newMember)) {
        std::cout << "SUCCESS: New member 'Jane' added with ID M110\n";
        newMember.display();
    } else {
        std::cout << "FAILED: Could not add new member\n";
    }
    std::cout << "\n";
    
    // Test 4: Have Ben borrow book B106
    std::cout << "Test 4: Ben borrowing book B106...\n";
    if (library.borrowPublication("M106", "B106")) {
        std::cout << "SUCCESS: Ben borrowed book B106\n";
    } else {
        std::cout << "FAILED: Could not borrow book B106\n";
    }
    std::cout << "\n";
    
    // Test 5: Have Ben return book B106
    std::cout << "Test 5: Ben returning book B106...\n";
    if (library.returnPublication("M106", "B106")) {
        std::cout << "SUCCESS: Ben returned book B106\n";
    } else {
        std::cout << "FAILED: Could not return book B106\n";
    }
    std::cout << "\n";
    
    // Test 6: Search for book by title and author
    std::cout << "Test 6: Searching for 'Awaken the Giant Within' by 'Tony Robbins'...\n";
    auto titleResults = library.searchByTitle("Awaken the Giant Within");
    auto authorResults = library.searchByAuthor("Tony Robbins");
    
    std::cout << "Found " << titleResults.size() << " publications by title\n";
    std::cout << "Found " << authorResults.size() << " publications by author\n";
    
    if (!titleResults.empty()) {
        std::cout << "First result:\n";
        titleResults[0]->display();
    }
    std::cout << "\n";
    
    // Test 7: Chen borrowing book B109 (which might not exist)
    std::cout << "Test 7: Chen attempting to borrow book B109...\n";
    if (library.borrowPublication("M109", "B109")) {
        std::cout << "SUCCESS: Chen borrowed book B109\n";
    } else {
        std::cout << "EXPECTED: Could not borrow non-existent book B109\n";
    }
    std::cout << "\n";
    
    // Test 8: Export current data to new files
    std::cout << "Test 8: Exporting data to new files...\n";
    if (library.savePublicationsToFile("data/books_updated.txt") &&
        library.saveMembersToFile("data/members_updated.txt")) {
        std::cout << "SUCCESS: Data exported to books_updated.txt and members_updated.txt\n";
    } else {
        std::cout << "FAILED: Could not export data\n";
    }
    std::cout << "\n";
    
    // Display final statistics
    std::cout << "=== Final Statistics ===\n";
    std::cout << "Total publications: " << library.getPublicationCount() << "\n";
    std::cout << "Total members: " << library.getMemberCount() << "\n";
    
    // Show available publications
    library.displayAvailablePublications();
    
    std::cout << "\n=== All Tests Completed ===\n";
}

void interactiveMenu() {
    Library<Publication> library;
    int choice;
    
    // Load initial data
    library.loadPublicationsFromFile("data/books.txt");
    library.loadMembersFromFile("data/members.txt");
    
    do {
        std::cout << "\n=== Library Management System ===\n";
        std::cout << "1. Display all publications\n";
        std::cout << "2. Display available publications\n";
        std::cout << "3. Display all members\n";
        std::cout << "4. Search for publication by title\n";
        std::cout << "5. Search for publication by author\n";
        std::cout << "6. Borrow a publication\n";
        std::cout << "7. Return a publication\n";
        std::cout << "8. Add new publication\n";
        std::cout << "9. Add new member\n";
        std::cout << "10. Save data to files\n";
        std::cout << "11. Run automated tests\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline
        
switch (choice) {
case 1:
library.displayAllPublications();
break;
                
case 2:
library.displayAvailablePublications();
break;
                
case 3:
library.displayAllMembers();
break;
                
case 4: {
std::string title;
std::cout << "Enter title to search: ";
std::getline(std::cin, title);
auto results = library.searchByTitle(title);
std::cout << "Found " << results.size() << " publication(s):\n";
    for (const auto& pub : results) {
        pub->display();
        std::cout << "\n";
                }
        break;
            }
                
case 5: {
std::string author;
std::cout << "Enter author to search: ";
std::getline(std::cin, author);
    auto results = library.searchByAuthor(author);
                std::cout << "Found " << results.size() << " publication(s):\n";
                for (const auto& pub : results) {
                    pub->display();
                    std::cout << "\n";
                }
                break;
            }
                
            case 6: {
                std::string memberId, pubId;
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter publication ID to borrow: ";
                std::getline(std::cin, pubId);
                
                if (library.borrowPublication(memberId, pubId)) {
                    std::cout << "Successfully borrowed publication\n";
                } else {
                    std::cout << "Failed to borrow publication\n";
                }
                break;
            }
                
            case 7: {
                std::string memberId, pubId;
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter publication ID to return: ";
                std::getline(std::cin, pubId);
                
                if (library.returnPublication(memberId, pubId)) {
                    std::cout << "Successfully returned publication\n";
                } else {
                    std::cout << "Failed to return publication\n";
                }
                break;
            }
                
            case 8: {
                std::string id, title, author, genre, isbn;
                int pageCount, edition;
                bool available;
                
                std::cout << "Enter publication ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter genre: ";
                std::getline(std::cin, genre);
                std::cout << "Enter page count: ";
                std::cin >> pageCount;
                std::cout << "Is available (1 for yes, 0 for no): ";
                std::cin >> available;
                std::cin.ignore();
                
                auto newPub = std::make_shared<Book>(id, title, author, genre, 
                                                    pageCount, available, isbn, edition);
                
                if (library.addPublication(newPub)) {
                    std::cout << "Publication added successfully\n";
                } else {
                    std::cout << "Failed to add publication\n";
                }
                break;
            }
                
            case 9: {
                std::string memberId, name;
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter member name: ";
                std::getline(std::cin, name);
                
                Member newMember(memberId, name);
                if (library.addMember(newMember)) {
                    std::cout << "Member added successfully\n";
                } else {
                    std::cout << "Failed to add member\n";
                }
                break;
            }
                
            case 10:
                library.savePublicationsToFile("data/books_updated.txt");
                library.saveMembersToFile("data/members_updated.txt");
                std::cout << "Data saved to files\n";
                break;
                
            case 11:
                runTests();
                break;
                
            case 0:
                std::cout << "Exiting...\n";
                break;
                
default:
std::cout << "Invalid choice. Please try again.\n";
        }
        
    } while (choice != 0);
}

int main() {
    std::cout << "Library Management System\n";
    std::cout << "=========================\n\n";
    
    int mode;
    std::cout << "Select mode:\n";
    std::cout << "1. Run automated tests (for assignment testing)\n";
    std::cout << "2. Interactive menu (for manual use)\n";
    std::cout << "Enter choice: ";
    std::cin >> mode;
    
    if (mode == 1) {
        runTests();
    } else {
        interactiveMenu();
    }
    
    return 0;
}
            