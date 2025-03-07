#include "Book.h"

Book::Book(const std::string& title,
           const std::string& author,
           const std::string& publisher,
           int                year,
           const std::string& ISBN)
    : title(title), author(author), publisher(publisher), year(year), ISBN(ISBN),
      status(BookStatus::AVAILABLE) {
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
