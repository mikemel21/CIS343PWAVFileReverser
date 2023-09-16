#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

//* returns 0 if the first 4 bytes of WAV file are "RIFF" and 1 if they are not
int isRIFF (wave_file* wf);

//* returns 0 if bytes 4-7 equal the sizeOfFile-8 and 2 if not
int bits4to7 (wave_file* wf, size_t size);

//* returns 0 if bytes 8-11 = WAVE and 1 if not
int isWAVE (wave_file* wf);

//* returns 0 if file has two channels and 1 if it does not
int has2Channels (wave_file* wf);

//* returns 0 if file has format type 1 and 1 if it does not
int formatType (wave_file* wf);

int main(int argc, char** argv) { 
    wave_file* waveFile = loadWAV(argv[1]);
    printf("Input File Name: %s\n", argv[1]);



    // requirement checking
    // if (isRIFF(fileContents) == 1 || bits4to7(fileContents, sizeOfFile) == 1 || isWAVE(fileContents) == 1 || has2Channels(fileContents) == 1 || formatType(fileContents) == 1) {
    //     printf("Unable to process file.\n");
    //     // TODO: Make specific error messages for each requirement
    //     exit(1);
    // }

    // // file that will hold the reversed WAV
    // char* reversedFile = malloc(sizeOfFile);


    // printf("Success.");

    // free (fileContents);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int isRIFF (wave_file* wf) {
    if (wf->header.header[0] != 'R' && wf->header.header[1] != 'I' && wf->header.header[2] != 'F' && wf->header.header[3] != 'F') {
        return 1;
    }
    return 0;
}

int bits4to7 (wave_file* wf, size_t size) {
    // ! you need to read the bytes backwards (7, 6, 5, then 4)
    uint8_t hashSize[4];
    int a = 0;
    // read bits 4-7 in reverse and add their values to the hashSize variable
    for (int i = 7; i > 3; i--) {
        hashSize[a++] = wf->header.header[i];
    }
    // bit shifts bit 7 to left most, then bit 6, then bit 5, and bit 4 is the rightmost
    int sizeComp = (hashSize[0] << 24) | (hashSize[1] << 16) | (hashSize[2] << 8) | hashSize[3];
    // final check to see if bits 4-7 = sizeOfFile-8
    if (sizeComp != size-8) {
        return 1;
    }
    return 0; 
}

int isWAVE (wave_file* wf) {
    char WAVE[4] = {wf->header.header[8], wf->header.header[9], wf->header.header[10], wf->header.header[11]};
    if (WAVE[0] != 'W' || WAVE[1] != 'A' || WAVE[2] != 'V' || WAVE[3] != 'E') {
        return 1;
    }
    return 0;
}

int has2Channels (wave_file* wf) {
    if (wf->header.header[22] != 2) {
        return 1;
    }
    return 0;
}

int formatType (wave_file* wf) {
    if ((int) (wf->header.header[20]) != 1) {
        return 1;
    }
    return 0;
}