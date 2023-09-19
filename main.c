#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

/*  CIS 343
    Justin and Michael Melei
    WAV File Reverser
*/

int main(int argc, char** argv) { 
    wave_file* waveFile = loadWAV(argv[1]);
    wave_file reversedFile;
    // validates file can be reversed
    checkHeader(waveFile);
    
    // just a direct copy
    reversedFile.fileSize = waveFile->fileSize;
    reversedFile.header = waveFile->header;
    //reversedFile.dataPointer = waveFile->dataPointer;

    //memcpy(reversedFile.dataPointer, waveFile->dataPointer, waveFile->fileSize);

    int count = 0;
    for (int i = 0; i < waveFile->fileSize ; i++) {
        reversedFile.dataPointer[count++] = *waveFile->dataPointer+(waveFile->fileSize-i);
    }

    printf("Input File Name: %s\n", argv[1]);
    printf("File Size: %zu\n", waveFile->fileSize);
    printf("Sample Rate: %u\n", getSampleRate(waveFile));
    printf("# Channels: %d\n", waveFile->header.header[22]); // get # channels from byte 22
    printf("Output File Name: %s\n", "");

    //SWITCH TO THIS: int error = prepByteArray(*reversedFile, argv[2]);
    int error = prepByteArray(reversedFile, "reversed.wav");
    free (waveFile);
    return 0;
}