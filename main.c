#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

int main(int argc, char** argv) { 
    wave_file* waveFile = loadWAV(argv[1]);
    wave_file* reversedFile = malloc(sizeof(*reversedFile));
    // validates file can be reversed
    checkHeader(waveFile);
    
    reversedFile->fileSize = waveFile->fileSize;
    reversedFile->header = waveFile->header;
    reversedFile->dataPointer = waveFile->dataPointer;

    printf("%zu\n", reversedFile->fileSize);
    printf("%lu\n", sizeof(reversedFile->header.header));

    printf("Input File Name: %s\n", argv[1]);
    printf("File Size: %zu\n", waveFile->fileSize);
    printf("Sample Rate: %u\n", getSampleRate(waveFile));
    printf("# Channels: %d\n", waveFile->header.header[22]); // get # channels from byte 22
    printf("Output File Name: %s\n", "");
    int error = prepByteArray(*reversedFile, "reversed.wav");

    free (waveFile);
    return 0;
}