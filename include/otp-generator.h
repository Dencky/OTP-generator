#ifndef OTP_GENERATOR
#define OTP_GENERATOR

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "hotp.h"

void printUsage(char* name);

int main(int argc, char* argv[]);

#endif //OTP_GENERATOR