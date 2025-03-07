#pragma once

#include "Account.h"
#include "Book.h"
#include <iostream>
#include <string>
#include <vector>

class Library;

class Account;

class User {
  private:
    std::string name;
    std::string userID;
    std::string password;
    Account    *account;

  public:
    User(const std::string &name, const std::string &userID, const std::string &password);
    ~User();

    virtual void borrowBook(Book &book) = 0;
    virtual void returnBook(Book &book) = 0;

    std::string getName() const;
    std::string getUserID() const;
    Account    &getAccount() const;
};

class Student: public User {
  private:
    static constexpr int maxBooks   = 3;
    static constexpr int finePerDay = 10;
    static constexpr int maxDays    = 15;

  public:
    Student(const std::string &name, const std::string &id, const std::string &password);
    void borrowBook(Book &book) override;
    void returnBook(Book &book) override;

    void payFine();
};

class Faculty: public User {
  private:
    static constexpr int maxBooks = 5;
    static constexpr int maxDays  = 30;
    static constexpr int maxDue   = 60;

  public:
    Faculty(const std::string &name, const std::string &id, const std::string &password);
    void borrowBook(Book &book) override;
    void returnBook(Book &book) override;
};

class Librarian: public User {
  public:
    Library *library;

    Librarian(const std::string &name, const std::string &id, const std::string &password);
    void borrowBook(Book &book) override;
    void returnBook(Book &book) override;
};
