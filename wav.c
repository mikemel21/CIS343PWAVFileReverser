#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

wave_header createHeader (char* fileContents) {
    wave_header head;

    for (int i = 0; i < 44; i++) {
        head.header[i] = fileContents[i];
    }

    return head;
}

wave_file* loadWAV (const char* path) {
    size_t sizeOfFile;
    char* file = read_file(path, &sizeOfFile);
    wave_header headerBytes = createHeader(file);
    wave_file* wave = malloc(sizeof(*wave));

    wave->fileSize = sizeOfFile;
    wave->dataPointer = &file[44]; 
    
    wave->header = headerBytes;

    return wave;
}

//TODO: write the function that prepares a byte array for the reversed file and writes the new audio file to disk
int prepByteArray (wave_file wf, char* path) {
    char* byteArray = malloc(wf.fileSize);
    byteArray = wf.header.header;
    strcat(byteArray+44, wf.dataPointer);
    //byteArray = wf.dataPointer;
    return write_file(path, byteArray, wf.fileSize);
}

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

void checkHeader (wave_file* wf) {
    if (isRIFF(wf) == 1){
        printf("\nBytes 0-3 RIFF not found\n");
        exit(1);
    }
    if (bits4to7 (wf, wf->fileSize) == 1){
        printf("\nBytes 4-7 do not contain the right file size\n");
        exit(1);
    }
    if (isWAVE (wf) == 1){
        printf("\nBytes 8-11 WAVE not found\n");
        exit(1);
    }
    if (has2Channels (wf) == 1){
        printf("\nBytes 22 Does not show 2 channles\n");
        exit(1);
    }
    if (formatType (wf) == 1){
        printf("\nBytes 20-21 is not a 16-bit interger value of 1\n");
        exit(1);
    }
}

int getSampleRate (wave_file* wf) {
    uint16_t sampleRate = (wf->header.header[27] << 24) | (wf->header.header[26] << 16) | (wf->header.header[25] << 8) | wf->header.header[24];
    return sampleRate;
}
