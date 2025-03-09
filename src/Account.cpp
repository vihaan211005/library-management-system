#include "Account.h"
#include "DateUtils.h"

Account::Account(User *user) {
    this->user = user;
}

void Account::addBook(Book &book) {
        switch (book.getStatus()) {
            case BookStatus::BORROWED:
                std::cout << "Book is already borrowed." << std::endl;
                return;
            case BookStatus::RESERVED:
                std::cout << "Book is reserved." << std::endl;
                return;
            default:
                break;
        }
    book.setStatus(BookStatus::BORROWED);
    time_t now = getCurrentTime();
    borrowedBooks.push_back({&book, now, 0});
    std::cout << "Book borrowed successfully." << std::endl;
}

int Account::removeBook(Book &book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
                if (it->book->getISBN() == book.getISBN()) {
                    book.setStatus(BookStatus::AVAILABLE);
                    it->returnTime = getCurrentTime();
                    int days       = calculateDateDifference(it->borrowTime, it->returnTime);

                    borrowHistory.push_back(*it);
                    borrowedBooks.erase(it);
                    std::cout << "Book returned successfully." << std::endl;
                    return days;
            }
        }
    std::cout << "Book not found in borrowed list." << std::endl;
    return 0;
}

int Account::calculateFine(int maxDays, int finePerDay) {
    outstandingFine = 0;
    time_t now      = getCurrentTime();

        for (const auto &borrowed: borrowedBooks) {
            int daysBorrowed = calculateDateDifference(borrowed.borrowTime, now);
            if (daysBorrowed < 0)
                throw std::invalid_argument("Days borrowed cannot be negative.");
            if (daysBorrowed > maxDays)
                outstandingFine += (daysBorrowed - maxDays) * finePerDay;
        }
    return outstandingFine;
}

std::vector<Book *> Account::getMaxOverdue(int days) const {
    std::vector<Book *> maxOverdueBooks;
    time_t              now = getCurrentTime();
        for (const auto &borrowed: borrowedBooks) {
            int daysBorrowed = calculateDateDifference(borrowed.borrowTime, now);
            if (daysBorrowed > days)
                maxOverdueBooks.push_back(borrowed.book);
        }
    return maxOverdueBooks;
}

void Account::payFine() {
    outstandingFine = 0;
}

std::vector<BorrowedBook> Account::getBorrowedBooks() const {
    return borrowedBooks;
}

std::vector<BorrowedBook> Account::getBorrowHistory() const {
    return borrowHistory;
}

int Account::getFine() const {
    return outstandingFine;
}

void Account::addToBorrowed(BorrowedBook book) {
    borrowedBooks.push_back(book);
}

void Account::addToHistory(BorrowedBook book) {
    borrowHistory.push_back(book);
}