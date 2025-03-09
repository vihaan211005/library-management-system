#include "SHACalc.h"

std::string sha256(const std::string &input) {
#ifdef OPENSSL_FOUND
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];

    return ss.str();
#else
    return input;
#endif
}
