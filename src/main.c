#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "FiSH.h"
#include "FiSH_version.h"
#include "blowfish.h"

void usage( const char* msg)
{
    if( msg != "" ) printf( "%s\n\n", msg );
    printf( "Decrypt a blowfish message\n\n"
            "Usage: $0 -d|-e key message\n");
}

int main(int argc, char* argv[])
{
    int encrypt=0;
    char opt;
    while (( opt = getopt( argc, argv, "deh" )) != -1 )
    {
        switch ( opt )
        {
        case 'e': encrypt=1; break;
        case 'd': encrypt=0; break;
        case 'h': usage("Hi!"); exit(0);
        default:
            break;
        }
    }

    if(argc < 3)
    {
        usage("Not enough arguments!");
        exit(-1);
    }
    const char* key = argv[argc-2];
    const char* message = argv[argc-1];

    char* dest = malloc(sizeof(char*) * 255);
    if(encrypt==1)
    {
        if( encrypt_string(key, message, dest, strlen(message)) == 0)
            printf("Failed to encrypt..\n");
    } else {
        if(decrypt_string(key, message, dest, strlen(message)) == 0)
            printf("Failed to decrypt..\n");
    }

    if(dest != NULL) printf("%s\0", dest);
    else printf("Failed...");

    return 0;
}
