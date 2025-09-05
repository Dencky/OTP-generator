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
    
    return EXIT_SUCCESS;
}
