# Library Management System

## Overview

The Library Management System is a C++ application designed to manage and track the inventory of a library. It provides a user-friendly interface for librarians to add, remove, and update books, as well as track borrowing and returning of books by students and faculty.

## Features

*   User Roles and Permissions:
    *   Students: Can borrow up to 3 books at a time, maximum borrowing period of 15 days, and fines of 10 rupees per day for overdue books.
    *   Faculty: Can borrow up to 5 books at a time, maximum borrowing period of 30 days, and no fines for overdue books.
    *   Librarian: Can manage the library, including adding, removing, or updating books, and adding or removing users.
*   Book Management:
    *   Add new books to the library's inventory.
    *   Remove books from the library's inventory.
    *   Update book details (title, author, publication date, etc.).
*   Borrowing and Returning:
    *   Track borrowing and returning of books by students and faculty.
    *   Set due dates for borrowed books.
*   Reporting:
    *   Generate reports on book inventory, patron borrowing history, and overdue books.
*   Account Management:
    *   Maintain a record of currently borrowed books.
    *   Track overdue books and calculate fines.

## Classes and Objects

*   `User`: Represents a user in the library system.
*   `Student`: Represents a student user, derived from the `User` class.
*   `Faculty`: Represents a faculty user, derived from the `User` class.
*   `Librarian`: Represents a librarian user, derived from the `User` class.
*   `Book`: Represents a book in the library's inventory.
*   `Account`: Represents a user's account, tracking borrowed books and fines.
*   `Library`: Represents the Users and Books in the library, maintains inventory.

<!-- ## Methods

*   `addBook()`: Adds a new book to the library's inventory.
*   `removeBook()`: Removes a book from the library's inventory.
*   `updateBook()`: Updates a book's details.
*   `borrowBook()`: Allows a user to borrow a book.
*   `returnBook()`: Allows a user to return a book.
*   `generateReport()`: Generates reports on book inventory, patron borrowing history, and overdue books.
*   `payFine()`: Allows a user to pay their outstanding fines. -->

## Prerequisites

Ensure you have the following installed on your system:

- **CMake** (version 3.x or higher)
- **C++ Compiler** (GCC/Clang/MSVC)
- **Make** (for Linux/macOS) or **Ninja/MinGW** (for Windows)
- **Git** (optional, to clone the repository)

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