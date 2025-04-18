#pragma once

#include <string>

enum class BookStatus { AVAILABLE, BORROWED, RESERVED, COUNT };

std::string bookStatusToString(BookStatus status);

class Book {
  private:
    std::string title;
    std::string author;
    std::string publisher;
    int         year;
    std::string ISBN;
    BookStatus  status;
    std::string reservedByID;
    bool atLib;

  public:
    Book(const std::string &title, const std::string &author, const std::string &publisher, int year, const std::string &ISBN, BookStatus status, const std::string &reservedByID, bool atLib);

    void setStatus(BookStatus status);

    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setPublisher(const std::string &publisher);
    void setYear(int year);
    void setReserver(const std::string &reservedByID);
    void setAtLib(bool cur);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int         getYear() const;
    std::string getISBN() const;
    BookStatus  getStatus() const;
    std::string getReserver() const;
    bool        getAtLib() const;
};
