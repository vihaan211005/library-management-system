#include "main.h"

void logout() {
    std::cout << "Goodbye, " << user->getName() << "!" << std::endl;
    user = nullptr;
    mainLogic();
}

void login() {
    std::cout << "Would you like to login? (y/n): ";
        if (getYN()) {
            std::cout << "Please login." << std::endl;
        } else {
            std::cout << "Exiting..." << std::endl;
            saveLibName(*library);
            saveBooks(*library);
            saveUsers(*library);
            exit(1);
        }
    std::string id, password;
    std::cout << "Enter id: ";
    std::getline(std::cin, id);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    User *userTemp = library->getUser(id);
        if (userTemp != nullptr && userTemp->checkPassword(password)) {
            user = userTemp;
            std::cout << "Welcome, " << user->getName() << std::endl;
        } else {
            std::cout << "Invalid id or password." << std::endl;
            login();
        }
}

void createLibrary() {
    library = retrieveLibName();
        if (library == nullptr) {
            std::string libraryName;
            std::cout << "Enter library name: ";
            std::getline(std::cin, libraryName);
            library = new Library(libraryName);
        } else {
            std::cout << "Welcome to Library Management System for: " << library->getName() << std::endl;
        }
}

User *makeUser(UserType type) {
    std::string name, id, password;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter id: ";
    std::getline(std::cin, id);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    password = sha256(password);
        switch (type) {
            case UserType::LIBRARIAN:
                return new Librarian(name, id, password, library);
            case UserType::STUDENT:
                return new Student(name, id, password, library);
            case UserType::FACULTY:
                return new Faculty(name, id, password, library);
            default:
                return nullptr;
        }
}

Book *makeBook() {
    std::string ISBN, title, author, publisher;
    int         year;
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, ISBN);
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    std::cout << "Enter publisher: ";
    std::getline(std::cin, publisher);
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cin.ignore();
    return new Book(title, author, publisher, year, ISBN, BookStatus::AVAILABLE);
}

void createFirstUser() {
    std::cout << "No users. Do you want to create a new user as librarian? (y/n): ";
        if (getYN()) {
            user = makeUser(UserType::LIBRARIAN);
            library->addUser(user);
        } else {
            std::cout << "Exiting..." << std::endl;
            exit(1);
        }
}

void displayBooks(std::vector<Book *> books) {
    std::vector<std::vector<std::string>> bookDetails;
    bookDetails.push_back({"ISBN", "Title", "Author", "Publisher", "Year", "Status"});
        for (const auto &book: books) {
            bookDetails.push_back({book->getISBN(), book->getTitle(), book->getAuthor(), book->getPublisher(), std::to_string(book->getYear()), bookStatusToString(book->getStatus())});
        }
    printTable(bookDetails);
}
void displayBooks(std::vector<BorrowedBook> books) {
    std::vector<std::vector<std::string>> bookDetails;
    bookDetails.push_back({"ISBN", "Title", "Author", "Publisher", "Year", "Status", "Borrow Date", "Return Date"});
        for (const auto &book: books) {
            bookDetails.push_back({book.book->getISBN(), book.book->getTitle(), book.book->getAuthor(), book.book->getPublisher(), std::to_string(book.book->getYear()),
                                   bookStatusToString(book.book->getStatus()), timeToString(book.borrowTime), book.returnTime ? timeToString(book.returnTime) : "-"});
        }
    printTable(bookDetails);
}

void displayUsers(std::vector<User *> users) {
    std::vector<std::vector<std::string>> userDetails;
    userDetails.push_back({"Name", "ID", "Type"});
        for (const auto &user: users) {
            userDetails.push_back({user->getName(), user->getUserID(), userTypeToString(user->getType())});
        }
    printTable(userDetails);
}
void borrowBoookUser() {
    displayBooks(library->getBooks());
    std::cout << "Enter ISBN of book to borrow: ";
    std::string isbn;
    std::cin >> isbn;
    std::cin.ignore();
    Book *bookToBorrow = library->getBook(isbn);
        if (bookToBorrow == nullptr) {
            std::cout << "Book not found." << std::endl;
            return;
    }
        if (bookToBorrow->getStatus() != BookStatus::AVAILABLE) {
            std::cout << "Book is not available." << std::endl;
            return;
    }

    user->borrowBook(*bookToBorrow);
}
void returnBoookUser() {
    displayBooks(user->getAccount().getBorrowedBooks());
    std::cout << "Enter ISBN of book to return: ";
    std::string isbn;
    std::cin >> isbn;
    std::cin.ignore();
    Book *bookToReturn = library->getBook(isbn);
        if (bookToReturn == nullptr) {
            std::cout << "Book not found." << std::endl;
            return;
    }
        for (const auto &book: user->getAccount().getBorrowedBooks()) {
                if (book.book->getISBN() == bookToReturn->getISBN()) {
                    user->returnBook(*bookToReturn);
                    return;
            }
        }
    std::cout << "Book is not borrowed by you." << std::endl;
}

void handleFaculty() {
    std::cout << "Faculty Menu: " << std::endl;
    std::vector<std::string> options = {"Borrow book", "Return book", "View History", "Logout"};
    int                      choice  = printOptions(options);
        switch (choice) {
            case 1:
                borrowBoookUser();
                handleFaculty();
                break;
            case 2:
                returnBoookUser();
                handleFaculty();
                break;
            case 3:
                displayBooks(user->getAccount().getBorrowHistory());
                handleFaculty();
                break;
            case 4:
                logout();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                handleFaculty();
                break;
        }
}

void handleStudent() {
    std::cout << "Student Menu: " << std::endl;
    std::vector<std::string> options = {"Borrow book", "Return book", "Pay Fine", "View History", "Logout"};
    int                      choice  = printOptions(options);
        switch (choice) {
            case 1:
                borrowBoookUser();
                handleStudent();
                break;
            case 2:
                returnBoookUser();
                handleStudent();
                break;
            case 3:
                dynamic_cast<Student *>(user)->payFine();
                handleStudent();
                break;
            case 4:
                displayBooks(user->getAccount().getBorrowHistory());
                handleStudent();
                break;
            case 5:
                logout();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                handleStudent();
                break;
        }
}

UserType getUserTypeTerminal() {
    std::cout << "Choose user type:" << std::endl;
    std::vector<std::string> userTypeOptions;
        for (int i = 0; i < static_cast<int>(UserType::COUNT); ++i) {
            userTypeOptions.push_back(userTypeToString(static_cast<UserType>(i)));
        }
    int userTypeChoice = printOptions(userTypeOptions);
    return static_cast<UserType>(userTypeChoice - 1);
}

void handleLibrarian() {
    std::cout << "Librarian Menu:" << std::endl;
    std::vector<std::string> options = {"Add User", "Remove User", "Add Book", "Remove Book", "View Users", "View Books", "Edit User", "Edit Book", "Logout"};
    int                      choice  = printOptions(options);
        switch (choice) {
                case 1: {
                    UserType typeTemp = getUserTypeTerminal();
                    User    *userTemp = makeUser(typeTemp);
                    if (library->addUser(userTemp))
                        std::cout << "User added successfully." << std::endl;
                    else
                        std::cout << "Failed to add user. User with this ID already exists." << std::endl;
                    handleLibrarian();
                    break;
                }
                case 2: {
                    std::cout << "Enter user ID to remove: ";
                    std::string idToRemove;
                    std::getline(std::cin, idToRemove);
                        if (idToRemove == user->getUserID()) {
                            std::cout << "You cannot remove yourself." << std::endl;
                            handleLibrarian();
                            break;
                    }
                    if (library->removeUser(idToRemove))
                        std::cout << "User removed successfully." << std::endl;
                    else
                        std::cout << "Failed to remove user. User not found." << std::endl;
                    handleLibrarian();
                    break;
                }
                case 3: {
                    Book *bookTemp = makeBook();
                    if (library->addBook(bookTemp))
                        std::cout << "Book added successfully." << std::endl;
                    else
                        std::cout << "Failed to add book. Book with this ISBN already exists." << std::endl;
                    handleLibrarian();
                    break;
                }
                case 4: {
                    std::cout << "Enter book ISBN to remove: ";
                    std::string isbnToRemove;
                    std::getline(std::cin, isbnToRemove);
                    if (library->removeBook(isbnToRemove))
                        std::cout << "Book removed successfully." << std::endl;
                    else
                        std::cout << "Failed to remove book. Book not found." << std::endl;
                    handleLibrarian();
                    break;
                }
                case 5: {
                    displayUsers(library->getUsers());
                    handleLibrarian();
                    break;
                }
                case 6: {
                    displayBooks(library->getBooks());

                    handleLibrarian();
                    break;
                }
                case 7: {
                    std::cout << "Enter user ID to update: ";
                    std::string idToUpdate;
                    std::getline(std::cin, idToUpdate);
                        if (idToUpdate == user->getUserID()) {
                            std::cout << "You cannot update yourself." << std::endl;
                            handleLibrarian();
                            break;
                    }
                    User *userToUpdate = library->getUser(idToUpdate);
                        if (userToUpdate == nullptr) {
                            std::cout << "User not found." << std::endl;
                            handleLibrarian();
                            break;
                    }
                    std::cout << "Change name? (y/n): ";
                        if (getYN()) {
                            std::cout << "Enter new name: ";
                            std::string newName;
                            std::getline(std::cin, newName);
                            userToUpdate->setName(newName);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    std::cout << "Change type? (y/n): ";
                        if (getYN()) {
                            UserType typeTemp = getUserTypeTerminal();
                            userToUpdate->setType(typeTemp);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    handleLibrarian();
                    break;
                }
                case 8: {
                    std::cout << "Enter book ISBN to update: ";
                    std::string isbnToUpdate;
                    std::getline(std::cin, isbnToUpdate);
                    Book *bookToUpdate = library->getBook(isbnToUpdate);
                        if (bookToUpdate == nullptr) {
                            std::cout << "Book not found." << std::endl;
                            handleLibrarian();
                            break;
                    }
                    std::cout << "Change title? (y/n): ";
                        if (getYN()) {
                            std::cout << "Enter new title: ";
                            std::string newTitle;
                            std::getline(std::cin, newTitle);
                            bookToUpdate->setTitle(newTitle);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    std::cout << "Change author? (y/n): ";
                        if (getYN()) {
                            std::cout << "Enter new author: ";
                            std::string newAuthor;
                            std::getline(std::cin, newAuthor);
                            bookToUpdate->setAuthor(newAuthor);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    std::cout << "Change publication year? (y/n): ";
                        if (getYN()) {
                            std::cout << "Enter new publication year: ";
                            int newYear;
                            std::cin >> newYear;
                            std::cin.ignore();
                            bookToUpdate->setYear(newYear);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    std::cout << "Change publisher? (y/n): ";
                        if (getYN()) {
                            std::cout << "Enter new publisher: ";
                            std::string newPublisher;
                            std::getline(std::cin, newPublisher);
                            bookToUpdate->setPublisher(newPublisher);
                            std::cout << "Updated successfully" << std::endl;
                    }
                    handleLibrarian();
                    break;
                }
                case 9: {
                    logout();
                    break;
                }
            default:
                std::cout << "Invalid choice. Please choose a valid option." << std::endl;
                handleLibrarian();
                break;
        }
}

void mainLogic() {
        if (library->getUsers().size() == 0) {
            createFirstUser();
    }
        if (user == nullptr) {
            login();
    }

        switch (user->getType()) {
            case UserType::LIBRARIAN:
                handleLibrarian();
                break;
            case UserType::STUDENT:
                handleStudent();
                break;
            case UserType::FACULTY:
                handleFaculty();
                break;
            default:
                break;
        }
}

int main() {
    createLibrary();
    retrieveBooks(*library);
    retrieveUsers(*library);
    mainLogic();

    return 0;
}
