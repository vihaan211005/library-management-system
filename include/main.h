#pragma once

#include "Account.h"
#include "Book.h"
#include "Library.h"
#include "TerminalPrint.h"
#include "User.h"
#include "DateUtils.h"

Library *library = nullptr;
User    *user    = nullptr;

void logout();
void login();
void createLibrary();
void createFirstUser();
void handleLibrarian();
void mainLogic();
User *makeUser(UserType type);
