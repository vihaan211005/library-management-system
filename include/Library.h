#pragma once

#include "Book.h"
#include "User.h"
#include <vector>

class User;
class Book;

class Library {
  private:
    std::vector<Book *> books;
    std::vector<User *> users;

  public:
    Library();
    ~Library();
    void                addBook(const Book &book);
    void                removeBook(const std::string &ISBN);
    void                addUser(User *user);
    void                removeUser(const std::string &userID);
    Book               *getBook(const std::string &ISBN) const;
    std::vector<Book *> getBooks() const;
    std::vector<User *> getUsers() const;
};
