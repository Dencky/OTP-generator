#ifndef HOTP
#define HOTP

#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

uint32_t dynamicTruncation(uint8_t string[20]);

void hmac_sha1( const unsigned char* text, size_t textLen, unsigned char* key, size_t keyLen, uint8_t out[20]);

#endif //HOTP