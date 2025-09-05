#ifndef HOTP
#define HOTP

#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void hmac_sha1( const unsigned char* text, size_t textLen, unsigned char* key, size_t keyLen, uint8_t out[20]);

#endif //HOTP