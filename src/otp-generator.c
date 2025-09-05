#include "../include/otp-generator.h"

void printUsage(char* name){
    printf("Usage %s -t|-h -k key -c counter -d digits -s step\n", name);
}

int main(int argc, char* argv[])
{
    int opt;
    bool t = false, h = false;
    char* key = NULL;
    int counter = 0, digits = 6, step = 30;
    while ((opt = getopt(argc, argv, "thk:c:d:s:")) != -1)
    {
        switch (opt)
        {
        case 't':
            t = true;
            break;
        
        case 'h':
            h = true;
            break;

        case 'k':
            key = optarg;
            break;
        
        case 'c':
            counter = atoi(optarg);
            break;

        case 'd':
            digits = atoi(optarg);
            break;

        case 's':
            step = atoi(optarg);
            break;
        
        default:
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (t && h)
    {
        printf("Only one type can be used either t(otp) or h(otp).\n");
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

    if (step < 0)
    {
        printf("The step interval should not be negative.\n");
        return EXIT_FAILURE;
    }
    

    uint8_t out[20];
    unsigned char counterBytes[8];

    if (h)
    {
        for (int i = 7; i >= 0; i--) {
            counterBytes[i] = counter & 0xFF;
            counter >>= 8;
        }
    }else{
        uint64_t timeCount = time(NULL) / step;
        for (int i = 7; i >= 0; i--) {
            counterBytes[i] = timeCount & 0xFF;
            timeCount >>= 8;
        }
    }

    hmac_sha1(counterBytes, 8, (unsigned char*) key, strlen(key), out);
    uint32_t truncated = dynamicTruncation(out);

    printf("%0*d", digits, truncated % (int)pow((double)10, (double)digits));
    printf("\n");
    
    return EXIT_SUCCESS;
}
