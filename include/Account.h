#pragma once

#include "Book.h"
#include "User.h"
#include <vector>

class User;

struct BorrowedBook {
    Book  *book;
    time_t borrowTime;
    time_t returnTime;
};

class Account {
  private:
    User                     *user;
    std::vector<BorrowedBook> borrowedBooks;
    std::vector<BorrowedBook> borrowHistory;
    int                       outstandingFine = 0;

  public:
    Account(User *user);
    void addBook(Book &book);
    int  removeBook(Book &book);
    int  calculateFine(int maxDays, int finePerDay);
    void payFine();

    std::vector<BorrowedBook> getBorrowedBooks() const;
    std::vector<BorrowedBook> getBorrowHistory() const;
    int                       getFine() const;
    std::vector<Book *>       getMaxOverdue(int days) const;
};
