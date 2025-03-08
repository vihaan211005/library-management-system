#pragma once

#include "Book.h"
#include "User.h"
#include <vector>

class User;
class Book;

class Library {
  private:
    std::string         libraryName;
    std::vector<Book *> books;
    std::vector<User *> users;

  public:
    Library(const std::string &libraryName);
    ~Library();
    void                addBook(const Book &book);
    void                removeBook(const std::string &ISBN);
    void                addUser(User *user);
    void                removeUser(const std::string &userID);
    std::string         getName() const;
    Book               *getBook(const std::string &ISBN) const;
    User               *getUser(const std::string &userId) const;
    std::vector<Book *> getBooks() const;
    std::vector<User *> getUsers() const;
};
