#include <stdio.h>
#include <stdint.h>
#include "file_lib.h"
#include "wav.h"

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

int formatType (char* fileContents) {
    if ((int) (fileContents[20]) != 1) {
        return 1;
    }
    return 0;
}