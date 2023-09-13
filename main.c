#include <stdio.h>
#include <string.h>
#include "file_lib.h"

//* returns 1 if the first 4 bytes of WAV file are "RIFF" and 0 if they are not
int isRIFF (char* fileContents);
//* returns 1 if bytes 8-11 are "WAVE" and 0 if they are not
int isWAVE (char* fileContacts);

//! to compile using clang, use following command: clang -o reversed *.c

int main(int argc, char** argv) { 
    size_t sizeOfFile; // size of WAV file
    char* fileContents = read_file(argv[1], &sizeOfFile); // stores the WAV file contents

    int RIFF = isRIFF(fileContents); // 1 if first 4 bytes are "RIFF", 0 if not
    if (isRIFF(fileContents) == 0) {
        printf("Unable to process file.\n");
        exit(1);
    }
    free (fileContents);
    return 0;
}

int isRIFF (char* fileContents) {
    char RIFF[4] = "RIFF";
    for (int i = 0; i < 4; i++) {
        if (fileContents[i] != RIFF[i]) {
            return 0;
        }
    }
    return 1;
}