#pragma once

#include <string>

enum class BookStatus { AVAILABLE, BORROWED, RESERVED };

std::string bookStatusToString(BookStatus status);

class Book {
  private:
    std::string title;
    std::string author;
    std::string publisher;
    int         year;
    std::string ISBN;
    BookStatus  status;

  public:
    Book(const std::string &title, const std::string &author, const std::string &publisher, int year, const std::string &ISBN);

    void setStatus(BookStatus status);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int         getYear() const;
    std::string getISBN() const;
    BookStatus  getStatus() const;
};
