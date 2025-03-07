#include "Library.h"
#include <algorithm>

Library::Library() {
}

void Library::addBook(const Book &book) {
    books.push_back(new Book(book));
}

void Library::removeBook(const std::string &ISBN) {
        for (auto it = books.begin(); it != books.end();) {
                if ((*it)->getISBN() == ISBN) {
                    delete *it;
                    it = books.erase(it);
                } else {
                    ++it;
                }
        }
}

void Library::addUser(User *user) {
    users.push_back(user);
}

void Library::removeUser(const std::string &userID) {
    auto it = std::remove_if(users.begin(), users.end(), [&](User *user) {
        return user->getUserID() == userID;
    });
        if (it != users.end()) {
            delete *it;
            users.erase(it, users.end());
    }
}

std::vector<Book *> Library::getBooks() const {
    return books;
}

std::vector<User *> Library::getUsers() const {
    return users;
}

Book *Library::getBook(const std::string &ISBN) const {
        for (Book *book: books) {
                if (book->getISBN() == ISBN) {
                    return book;
            }
        }
    return nullptr;
}

Library::~Library() {
        for (Book *book: books) {
            delete book;
        }
        for (User *user: users) {
            delete user;
        }
}