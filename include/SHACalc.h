#include <iostream>
#ifdef OPENSSL_FOUND
#include <openssl/sha.h>
#endif
#include <iomanip>
#include <sstream>

std::string sha256(const std::string &input);