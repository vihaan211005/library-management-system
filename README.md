# Library Management System

## Overview

The Library Management System is a C++ application designed to manage and track the inventory of a library. It provides a user-friendly interface for librarians to add, remove, and update books, as well as track borrowing and returning of books by students and faculty.

## Features

*   User Roles and Permissions:
    *   Students: Can borrow up to 3 books at a time, maximum borrowing period of 15 days, and fines of 10 rupees per day for overdue books.
    *   Faculty: Can borrow up to 5 books at a time, maximum borrowing period of 30 days, and no fines for overdue books.
    *   Librarian: Can manage the library, including adding, removing, or updating books, and adding, removing or updating users.
    * To prevent unauthorized access, the system will have a login system with a username and password.
*   Book Management:
    *   Add new books to the library's inventory.
    *   Remove books from the library's inventory.
    *   Update book details (title, author, publication date, etc.).
    *   Reserving books for students and faculty when it is borrowed by another user so that another user cant borrow it when returned by the first.
*   Borrowing and Returning:
    *   Track borrowing and returning of books by students and faculty.
    *   Set due dates for borrowed books.
    *   Calculate fines for overdue books. Fines are assumed to be payed at the counter when returning the book. Overdue books are assumed to be returned over the counter at the time of fine payment.
*   Reporting:
    *   Generate reports on book inventory, student, faculty borrowing history, and overdue books.
*   Account Management:
    *   Maintain a record of currently borrowed books.
    *   Track overdue books and calculate fines.
*   Password Hashing:
    *   Passwords are stored in file and in class after applying SHA-256 hashing.
    * Password is verified by check hash of entered password with stored hash.
    *   Secure user password in case of data breach.
## Classes and Objects

*   `User`: Represents a user in the library system.
*   `Student`: Represents a student user, derived from the `User` class.
*   `Faculty`: Represents a faculty user, derived from the `User` class.
*   `Librarian`: Represents a librarian user, derived from the `User` class.
*   `Book`: Represents a book in the library's inventory.
*   `Account`: Represents a user's account, tracking borrowed books and fines.
*   `Library`: Represents the Users and Books in the library, maintains inventory.

## Prerequisites

Ensure you have the following installed on your system:

- **CMake**
- **C++ Compiler**
- **Make**
- **Git**

```sh
sudo apt-get update
sudo apt-get install -y cmake build-essential make git
```

## Optional(Recommended)

- **OpenSSL**
```sh
sudo apt-get update
sudo apt-get install libssl-dev
```

## Compilation and Execution 

### Clone the repository
```sh
git clone https://github.com/vihaan211005/library-management-system.git
cd library-management-system
```

### Compile the project
```sh
mkdir build
cd build
cmake ..
make
```
### Run the application
```sh
./LibraryManagementSystem
```

## Usage

To use the Library Management System, follow these steps:

1.  Run the application.
2.  Select an option from the main menu (e.g., Add Book, Remove Book, etc.).
3.  Follow the prompts to perform the desired action.

## Acknowledgments

The Library Management System was developed by Vihaan Sapra (Roll No. 231149), Department of Computer Science and Engineering, Indian Institute of Technology Kanpur. Special thanks to Prof. Indranil Saha and the teaching assistants of the CS253 course for their guidance and support throughout the course.

## Note for TA

I have made 5 students and 3 faculty and 10+ books. Password for all users is currently 123 and to see id you can see users.csv. ID of librarian is 23. I have 2 files users and users_nohash depending on if the system has openSSL installed or not. If it is installed password is hashed and stored in users.csv while if it is not it is saved in users_nohash. For testing purposes days has been replaced by seconds for fine calculation. To change it back see DateUtils.cpp. While returning books and paying fine, overdue books and fine is assumed to be exchanged over the counter.