#include "main.h"

void logout() {
    std::cout << "Goodbye, " << user->getName() << "!" << std::endl;
    user = nullptr;
    mainLogic();
}

void login() {
    std::cout << "Would you like to login? (yes/no): ";
    std::string response;
    std::getline(std::cin, response);
        if (response == "yes") {
            std::cout << "Please login." << std::endl;
        } else {
            std::cout << "Exiting..." << std::endl;
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
    } else
        std::cout << "Invalid id or password." << std::endl;
}

void createLibrary() {
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
    std::cout << "No users. Do you want to create a new user as librarian? (yes/no): ";
    std::string response;
    std::getline(std::cin, response);
        if (response == "yes") {
            user = makeUser(UserType::LIBRARIAN);
            library->addUser(user);
        } else {
            std::cout << "Exiting..." << std::endl;
            exit(1);
        }
}

void handleLibrarian() {
    std::cout << "Librarian Menu:" << std::endl;
    std::vector<std::string> options = {"Add User", "Remove User", "Add Book", "Remove Book", "View Users", "View Books", "Logout"};
    int                      choice  = printOptions(options);
        switch (choice) {
                case 1: {
                    std::cout << "Choose user type:" << std::endl;
                    std::vector<std::string> userTypeOptions;
                        for (int i = 0; i < static_cast<int>(UserType::COUNT); ++i) {
                            userTypeOptions.push_back(userTypeToString(static_cast<UserType>(i)));
                        }
                    int   userTypeChoice = printOptions(userTypeOptions);
                    User *userTemp       = makeUser(static_cast<UserType>(userTypeChoice - 1));
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
                    std::vector<User *>                   users = library->getUsers();
                    std::vector<std::vector<std::string>> userDetails;
                    userDetails.push_back({"Name", "ID", "Type"});
                        for (const auto &user: users) {
                            userDetails.push_back({user->getName(), user->getUserID(), userTypeToString(user->getType())});
                        }
                    printTable(userDetails);
                    handleLibrarian();
                    break;
                }
                case 6: {
                    std::vector<Book *>                   books = library->getBooks();
                    std::vector<std::vector<std::string>> bookDetails;
                    bookDetails.push_back({"ISBN", "Title", "Author", "Publisher", "Year", "Status"});
                        for (const auto &book: books) {
                            bookDetails.push_back({book->getISBN(), book->getTitle(), book->getAuthor(), book->getPublisher(), std::to_string(book->getYear()), bookStatusToString(book->getStatus())});
                        }
                    printTable(bookDetails);
                    handleLibrarian();
                    break;
                }
                case 7: {
                    logout();
                    break;
                }
            default:
                break;
        }
}

void mainLogic() {
        if (library->getUsers().size() == 0) {
            createFirstUser();
    }
        while (user == nullptr) {
            login();
        }

        switch (user->getType()) {
            case UserType::LIBRARIAN:
                handleLibrarian();
                break;
            case UserType::STUDENT:
                break;
            case UserType::FACULTY:
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
