#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

int main(int argc, char** argv) { 
    wave_file* waveFile = loadWAV(argv[1]);
    // validates file can be reversed
    checkHeader(waveFile);
    

    printf("Input File Name: %s\n", argv[1]);
    printf("File Size: %d\n", waveFile->fileSize);
    printf("Sample Rate: %u\n", getSampleRate(waveFile));
    printf("# Channels: %d\n", waveFile->header.header[22]); // get # channels from byte 22
    printf("Output File Name: %s\n", "");

    free (waveFile);
    return 0;
}