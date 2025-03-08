#include "main.h"

void logout() {
    std::cout << "Goodbye, " << user->getName() << "!" << std::endl;
    user = nullptr;
    mainLogic();
}

void login() {
    std::cout << "Please login." << std::endl;
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

void createFirstUser() {
    std::cout << "No users. Do you want to create a new user as librarian? (yes/no): ";
    std::string response;
    std::getline(std::cin, response);
        if (response == "yes") {
            std::string name, id, password;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter id: ";
            std::getline(std::cin, id);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            user = new Librarian(name, id, password, library);
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
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
                case 6: {
                    std::vector<Book *>                   books = library->getBooks();
                    std::vector<std::vector<std::string>> bookDetails;
                    bookDetails.push_back({"ISBN", "Title", "Author", "Publisher", "Year", "Status"});
                        for (const auto &book: books) {
                            bookDetails.push_back({book->getISBN(), book->getTitle(), book->getAuthor(), book->getPublisher(), std::to_string(book->getYear()), bookStatusToString(book->getStatus())});
                        }
                    break;
                }
            case 7:
                user = nullptr;
                mainLogic();
                break;
            default:
                break;
        }
}

void mainLogic() {
    if (library->getUsers().size() == 0)
        createFirstUser();
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
    mainLogic();

    return 0;
}
