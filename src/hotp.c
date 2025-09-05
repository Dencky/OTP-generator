#include "hotp.h"

uint32_t dynamicTruncation(uint8_t string[20]){
    size_t offset = string[19] & 0x0f;
    uint32_t p =    (((uint32_t) string[offset] & 0x7f) << 24)  |
                    (((uint32_t) string[offset + 1])    << 16)  |
                    (((uint32_t) string[offset + 2])    << 8)   |
                    (((uint32_t) string[offset + 3]));
    return p;
}

void hmac_sha1(const unsigned char* text, size_t textLen, unsigned char* key, size_t keyLen, uint8_t out[20]){
    
    unsigned char paddedKey[64];
    unsigned char ipad[64];
    unsigned char opad[64];

    if(keyLen > 64){

        SHA1(key, keyLen, paddedKey);
        keyLen = 20;
    }else{
        memcpy(paddedKey, key, keyLen);
    }
    
    memset(paddedKey + keyLen, 0, 64 - keyLen);

    for (size_t i = 0; i < 64; i++)
    {
        ipad[i] = paddedKey[i] ^ 0x36;
        opad[i] = paddedKey[i] ^ 0x5c;
    }

    //Inside hash
    unsigned char* in = (unsigned char*) calloc(textLen + 64, sizeof(unsigned char));
    memcpy(in, ipad, 64);
    memcpy(in + 64, text, textLen);
    SHA1(in, textLen + 64, out);
    free(in);

    //Outside hash
    unsigned char outBuf[64 + 20];
    memcpy(outBuf, opad, 64);
    memcpy(outBuf + 64, out, 20);
    SHA1(outBuf, 64 + 20, out);
}