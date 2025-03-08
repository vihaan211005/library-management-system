#include "User.h"
#include "Account.h"
#include "Library.h"

std::string userTypeToString(UserType type) {
        switch (type) {
            case UserType::STUDENT:
                return "Student";
            case UserType::FACULTY:
                return "Faculty";
            case UserType::LIBRARIAN:
                return "Librarian";
            default:
                return "Unknown";
        }
}

User::User(const std::string &name, const std::string &userID, const std::string &password, Library *library, UserType userType) {
    this->name     = name;
    this->userID   = userID;
    this->password = password;
    this->account  = new Account(this);
    this->library  = library;
    this->type     = userType;
}

User::~User() {
    delete account;
}

void User::setName(const std::string &name) {
    this->name = name;
}

void User::setType(UserType userType) {
    this->type = userType;
}

UserType User::getType() const {
    return type;
}

bool User::checkPassword(const std::string &password) const {
    return this->password == sha256(password);
}

std::string User::getPassword() const {
    return password;
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

Student::Student(const std::string &name, const std::string &id, const std::string &password, Library *library):
    User(name, id, password, library, UserType::STUDENT) {
}

void Student::borrowBook(Book &book) {
    int fine = getAccount().calculateFine(maxDays, finePerDay);

        if (fine) {
            std::cout << "You have to pay a fine of ₹" << fine << " for borrowing first." << std::endl;
            return;
        } else if (getAccount().getBorrowedBooks().size() == maxBooks) {
            std::cout << "You have reached the maximum number of books you can borrow." << std::endl;
            return;
        } else {
            book.setStatus(BookStatus::BORROWED);
            getAccount().addBook(book);
        }
}

void Student::returnBook(Book &book) {
    int days = getAccount().removeBook(book);
    
    if (days > maxDays)
        std::cout << "You have to pay a fine of ₹" << (days - maxDays) * finePerDay << std::endl;
    book.setStatus(BookStatus::AVAILABLE);
}

void Student::payFine() {
    int fine = getAccount().calculateFine(maxDays, finePerDay);
    if (fine)
        std::cout << "You have to pay a fine of ₹" << fine << std::endl;
    getAccount().payFine();
}

Faculty::Faculty(const std::string &name, const std::string &id, const std::string &password, Library *library):
    User(name, id, password, library, UserType::FACULTY) {
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

Librarian::Librarian(const std::string &name, const std::string &id, const std::string &password, Library *library):
    User(name, id, password, library, UserType::LIBRARIAN) {
}

void Librarian::borrowBook(Book &book) {
    (void) book;
    std::cout << "Librarians do not borrow books." << std::endl;
}

void Librarian::returnBook(Book &book) {
    (void) book;
    std::cout << "Librarians do not return books." << std::endl;
}
