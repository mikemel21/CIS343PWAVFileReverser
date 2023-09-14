#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "file_lib.h"

//* returns 0 if the first 4 bytes of WAV file are "RIFF" and 1 if they are not
int isRIFF (char* fileContents);
//* returns 0 if bytes 4-7 equal the sizeOfFile-8 and 2 if not
int bits4to7 (char* fileContents, size_t size);
//* returns 0 if bytes 8-11 = WAVE and 1 if not
int isWAVE (char* fileContents);
//*returns 0 if file has two channels and 1 if it does not
int has2Channels (char* fileContents);

//! to compile using clang, use following command: clang -o reversed *.c

int main(int argc, char** argv) { 
    size_t sizeOfFile; // size of WAV file
    char* fileContents = read_file(argv[1], &sizeOfFile); // stores the WAV file contents

    // requirement checking
    if (isRIFF(fileContents) == 1 || bits4to7(fileContents, sizeOfFile) == 1 || isWAVE(fileContents) == 1 || has2Channels(fileContents) == 1) {
        
        printf("Unable to process file.\n");
        exit(1);
    }

    printf("Success.");

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

int bits4to7 (char* fileContents, size_t size) {
    // ! you need to read the bytes backwards (7, 6, 5, then 4)
    uint8_t hashSize[4];
    int a = 0;
    for (int i = 7; i > 3; i--) {
        hashSize[a++] = fileContents[i];
    }
    // bit shifts bit 7 to left most, then bit 6, then bit 5, and bit 4 is the rightmost
    int sizeComp = (hashSize[0] << 24) | (hashSize[1] << 16) | (hashSize[2] << 8) | hashSize[3];
    // final check to see if bits 4-7 = sizeOfFile-8
    if (sizeComp != size-8) {
        return 1;
    }
    return 0; 
}

int isWAVE (char* fileContents) {
    char WAVE[4] = {fileContents[8], fileContents[9], fileContents[10], fileContents[11]};
    if (WAVE[0] != 'W' || WAVE[1] != 'A' || WAVE[2] != 'V' || WAVE[3] != 'E') {
        return 1;
    }
    return 0;
}

int has2Channels (char* fileContents) {
    if (fileContents[22] != 2) {
        return 1;
    }
    return 0;
}