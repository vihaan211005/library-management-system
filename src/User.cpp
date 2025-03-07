#include "User.h"
#include "Account.h"
#include "Library.h"

User::User(const std::string &name, const std::string &userID, const std::string &password) {
    this->name     = name;
    this->userID   = userID;
    this->password = password;
    this->account  = new Account(this);
}

User::~User() {
    delete account;
}

std::string User::getName() const {
    return name;
}

std::string User::getUserID() const {
    return userID;
}

Account &User::getAccount() const {
    return *account;
}

Student::Student(const std::string &name, const std::string &id, const std::string &password): User(name, id, password) {
}

void Student::borrowBook(Book &book) {
    int fine = getAccount().calculateFine(maxDays, finePerDay);

        if (fine) {
            std::cout << "You have to pay a fine of ₹" << fine << " for borrowing." << std::endl;
            return;
        } else if (getAccount().getBorrowedBooks().size() == maxBooks) {
            std::cout << "You have reached the maximum number of books you can borrow." << std::endl;
            return;
        } else {
            getAccount().addBook(book);
        }
}

void Student::returnBook(Book &book) {
    int days = getAccount().removeBook(book);
    if (days > maxDays)
        std::cout << "You have to pay a fine of ₹" << (days - maxDays) * finePerDay << std::endl;
}

void Student::payFine() {
    int fine = getAccount().calculateFine(maxDays, finePerDay);
    if (fine)
        std::cout << "You have to pay a fine of ₹" << fine << std::endl;
    getAccount().payFine();
}

Faculty::Faculty(const std::string &name, const std::string &id, const std::string &password): User(name, id, password) {
}

void Faculty::borrowBook(Book &book) {
        if (getAccount().getBorrowedBooks().size() == maxBooks) {
            std::cout << "You have reached the maximum number of books you can borrow." << std::endl;
            return;
        } else if (getAccount().getMaxOverdue(maxDays + maxDue).size()) {
            std::cout << "You have overdue books. Please return them before borrowing more." << std::endl;
            return;
        } else {
            getAccount().addBook(book);
        }
}

void Faculty::returnBook(Book &book) {
    int days = getAccount().removeBook(book);
    if (days > maxDays)
        std::cout << "Please return books before " << maxDays << " days from next time" << std::endl;
}

Librarian::Librarian(const std::string &name, const std::string &id, const std::string &password): User(name, id, password) {
    this->library = new Library();
}

void Librarian::borrowBook(Book &book) {
    std::cout << "Librarians do not borrow books." << std::endl;
}

void Librarian::returnBook(Book &book) {
    std::cout << "Librarians do not return books." << std::endl;
}
