#pragma once

#include "Book.h"
#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>
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
    bool                addBook(Book *book);
    bool                removeBook(const std::string &ISBN);
    bool                addUser(User *user);
    bool                removeUser(const std::string &userID);
    std::string         getName() const;
    Book               *getBook(const std::string &ISBN) const;
    User               *getUser(const std::string &userId) const;
    std::vector<Book *> getBooks() const;
    std::vector<User *> getUsers() const;
    friend void         saveBooks(const Library &library);
    friend void         saveUsers(const Library &library);
    friend void         retrieveBooks(Library &library);
    friend void         retrieveUsers(Library &library);
};
