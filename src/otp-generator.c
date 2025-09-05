#include "otp-generator.h"

void printUsage(char* name){
    printf("Usage %s -k key -c counter -d digits\n", name);
}

int main(int argc, char* argv[])
{
    int opt;
    char* key = NULL;
    int counter = 0, digits = 6;
    while ((opt = getopt(argc, argv, "k:c:d:")) != -1)
    {
        switch (opt)
        {
        case 'k':
            key = optarg;
            break;
        
        case 'c':
            counter = atoi(optarg);
            break;

        case 'd':
            digits = atoi(optarg);
            break;
        
        default:
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
    }
    
    if (!key)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    if (counter < 0)
    {
        printf("Counter value has to be positive.\n");
        return EXIT_FAILURE;
    }
    
    if (digits < 6 || digits > 10)
    {
        printf("The number of digits should be between 6 and 10.\n");
        return EXIT_FAILURE;
    }

    uint8_t out[20];
    unsigned char counterBytes[8];
    for (int i = 7; i >= 0; i--) {
        counterBytes[i] = counter & 0xFF;
        counter >>= 8;
    }

    hmac_sha1(counterBytes, 8, (unsigned char*) key, strlen(key), out);
    uint32_t truncated = dynamicTruncation(out);

    printf("%0*d", digits, truncated % (int)pow((double)10, (double)digits));
    printf("\n");
    
    return EXIT_SUCCESS;
}
