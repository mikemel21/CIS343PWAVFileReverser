#include <stdio.h>
#include <string.h>
#include "file_lib.h"

//* returns 1 if the first 4 bytes of WAV file are "RIFF" and 0 if they are not
int isRIFF (char* fileContents);

//! to compile using clang, use following command: clang -o reversed *.c

int main(int argc, char** argv) { 
    size_t sizeOfFile; // size of WAV file
    char* fileContents = read_file(argv[1], &sizeOfFile); // stores the WAV file contents
    printf("actual file size: %d\n", sizeOfFile);

    if (isRIFF(fileContents) == 1) {
        printf("Unable to process file.\n");
        exit(1);
    }

    // read bytes 4-7 and see if they equal the sizeOfFile - 8;
    // ! you need to read the bytes backwards (7, 6, 5, then 4)
    

    free (fileContents);
    return 0;
}

int isRIFF (char* fileContents) {
    char RIFF[4] = "RIFF";
    for (int i = 0; i < 4; i++) {
        if (fileContents[i] != RIFF[i]) {
            return 1;
        }
    }
    return 0;
}
