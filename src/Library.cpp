#include "Library.h"

Library::Library(const std::string &libraryName) {
    this->libraryName = libraryName;
}

std::string Library::getName() const {
    return libraryName;
}

bool Library::addBook(Book *book) {
        if (getBook(book->getISBN()) == nullptr) {
            books.push_back(book);
            return true;
    }
    return false;
}

bool Library::removeBook(const std::string &ISBN) {
        for (auto it = books.begin(); it != books.end(); ++it) {
                if ((*it)->getISBN() == ISBN) {
                    delete *it;
                    it = books.erase(it);
                    return true;
            }
        }
    return false;
}

bool Library::addUser(User *user) {
        if (getUser(user->getUserID()) == nullptr) {
            users.push_back(user);
            return true;
    }
    return false;
}

bool Library::removeUser(const std::string &userID) {
        for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)->getUserID() == userID) {
                    delete *it;
                    it = users.erase(it);
                    return true;
            }
        }
    return false;
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

User *Library::getUser(const std::string &userID) const {
        for (User *user: users) {
                if (user->getUserID() == userID) {
                    return user;
            }
        }
    return nullptr;
}

void saveBooks(const Library &library) {
    std::ofstream file(books_filepath);
        if (file.is_open()) {
            file << "ISBN,Title,Author,Publisher,Year,Status\n";
                for (const Book *book: library.getBooks()) {
                    file << book->getISBN() << "," << book->getTitle() << "," << book->getAuthor() << "," << book->getPublisher() << "," << std::to_string(book->getYear()) << "," << std::to_string(static_cast<int>(book->getStatus())) << "\n";
                }
            file.close();
    }
}

void saveUsers(const Library &library) {
    std::ofstream file(users_filepath);
        if (file.is_open()) {
            file << "ID,Name,Type,Password\n";
                for (const User *user: library.getUsers()) {
                    file << user->getUserID() << "," << user->getName() << "," << std::to_string(static_cast<int>(user->getType())) << "," << user->getPassword() << "\n";
                }
            file.close();
    }
        for (const User *user: library.getUsers()) {
            std::ofstream file(dir_path + "_" + user->getUserID() + ".csv");
                if (file.is_open()) {
                    file << "ISBN,BorrowTime,ReturnTime\n";
                        for (BorrowedBook book: user->getAccount().getBorrowedBooks()) {
                            file << book.book->getISBN() << "," << book.borrowTime << "," << book.returnTime << "\n";
                        }
                        for (BorrowedBook book: user->getAccount().getBorrowHistory()) {
                            file << book.book->getISBN() << "," << book.borrowTime << "," << book.returnTime << "\n";
                        }
            }
        }
}

void retrieveUsers(Library &library) {
    std::ifstream file(users_filepath);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file for reading.\n";
            return;
    }

    std::string line;
    std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string       id, name, typeStr, password;

            User *userTemp;

                if (!std::getline(ss, id, ',') || !std::getline(ss, name, ',') || !std::getline(ss, typeStr, ',') || !std::getline(ss, password, ',')) {
                    std::cerr << "Warning: Invalid line format -> " << line << "\n";
                    continue;
            }

                try {
                    UserType type = static_cast<UserType>(std::stoi(typeStr));

                        switch (type) {
                            case UserType::STUDENT:
                                userTemp = new Student(name, id, password, &library);
                                break;
                            case UserType::FACULTY:
                                userTemp = new Faculty(name, id, password, &library);
                                break;
                            case UserType::LIBRARIAN:
                                userTemp = new Librarian(name, id, password, &library);
                                break;
                            default:
                                std::cerr << "Warning: Unknown user type -> " << typeStr << "\n";
                                break;
                        }
                    library.addUser(userTemp);

                } catch (const std::exception &e) {
                    std::cerr << "Error parsing line: " << line << " -> " << e.what() << "\n";
            }
            std::ifstream file_user(dir_path + "_" + id + ".csv");
                if (file_user.is_open()) {
                    std::string line;
                    std::getline(file_user, line);

                        while (std::getline(file_user, line)) {
                            std::stringstream ss(line);
                            std::string       ISBN, BorrowTimeStr, ReturnTimeStr;
                                if (!std::getline(ss, ISBN, ',') || !std::getline(ss, BorrowTimeStr, ',') || !std::getline(ss, ReturnTimeStr, ',')) {
                                    std::cerr << "Warning: Invalid line format -> " << line << "\n";
                                    continue;
                            }
                                try {
                                    time_t borrowTime = std::stol(BorrowTimeStr);
                                    time_t returnTime = std::stol(ReturnTimeStr);
                                    if (returnTime)
                                        userTemp->getAccount().addToHistory({library.getBook(ISBN), borrowTime, returnTime});
                                    else
                                        userTemp->getAccount().addToBorrowed({library.getBook(ISBN), borrowTime, returnTime});
                                } catch (const std::exception &e) {
                                    std::cerr << "Error parsing line: " << line << " -> " << e.what() << "\n";
                            }
                        }
            }

            file.close();
        }
}

void retrieveBooks(Library &library) {
    std::ifstream file(books_filepath);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file for reading.\n";
            return;
    }

    std::string line;
    std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string       isbn, title, author, publisher, yearStr, statusStr;

                if (!std::getline(ss, isbn, ',') || !std::getline(ss, title, ',') || !std::getline(ss, author, ',') || !std::getline(ss, publisher, ',') || !std::getline(ss, yearStr, ',') || !std::getline(ss, statusStr, ',')) {
                    std::cerr << "Warning: Invalid line format -> " << line << "\n";
                    continue;
            }

                try {
                    int        year   = std::stoi(yearStr);
                    BookStatus status = static_cast<BookStatus>(std::stoi(statusStr));

                    library.addBook(new Book(title, author, publisher, year, isbn, status));
                } catch (const std::exception &e) {
                    std::cerr << "Error parsing line: " << line << " -> " << e.what() << "\n";
            }
        }

    file.close();
}

Library::~Library() {
        for (Book *book: books) {
            delete book;
        }
        for (User *user: users) {
            delete user;
        }
}
