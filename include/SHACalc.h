#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string sha256(const std::string &input);