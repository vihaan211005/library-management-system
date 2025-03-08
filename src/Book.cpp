#include "Book.h"

std::string bookStatusToString(BookStatus status) {
        switch (status) {
            case BookStatus::AVAILABLE:
                return "Available";
            case BookStatus::BORROWED:
                return "Borrowed";
            case BookStatus::RESERVED:
                return "Reserved";
            default:
                return "Unknown";
        }
}

Book::Book(const std::string &title, const std::string &author, const std::string &publisher, int year, const std::string &ISBN, BookStatus status):
    title(title), author(author), publisher(publisher), year(year), ISBN(ISBN), status(status) {
}

void Book::setTitle(const std::string &title) {
    this->title = title;
}

void Book::setAuthor(const std::string &author) {
    this->author = author;
}

void Book::setPublisher(const std::string &publisher) {
    this->publisher = publisher;
}

void Book::setYear(int year) {
    this->year = year;
}

void Book::setStatus(BookStatus status) {
    this->status = status;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getPublisher() const {
    return publisher;
}

int Book::getYear() const {
    return year;
}

std::string Book::getISBN() const {
    return ISBN;
}

BookStatus Book::getStatus() const {
    return status;
}
