#include <stdio.h>
#include <string.h>
#include "file_lib.h"

//* returns 1 if the first 4 bytes of WAV file are "RIFF" and 0 if they are not
int isRIFF (char* fileContents);

//! to compile using clang, use following command: clang -o main main.c file_lib.c

int main() { 
    const char* testFile = "t1_be_back.wav"; // file path
    size_t sizeOfFile = sizeof(testFile); // size of WAV file
    char* fileContents = read_file(testFile, &sizeOfFile); // stores the WAV file contents

    int RIFF = isRIFF(fileContents); // 1 if first 4 bytes are "RIFF", 0 if not

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