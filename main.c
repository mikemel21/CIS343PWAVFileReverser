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
    // allocate memory to data pointer of reverse file. ensures it has enough memory to store the full data section of wav
    reversedFile.dataPointer = malloc(waveFile->fileSize);

    // validates file can be reversed
    checkHeader(waveFile);
    
    reversedFile.fileSize = waveFile->fileSize;
    memcpy(reversedFile.header.header, waveFile->header.header, 44);

    int count = 0;
    for (int i = waveFile->fileSize-4; i >= 0; i -= 4) {
        memcpy(&reversedFile.dataPointer[count], &waveFile->dataPointer[i], 4);
        count += 4;
    }

    // output results
    printf("Input File Name: %s\n", argv[1]);
    printf("File Size: %zu\n", waveFile->fileSize);
    printf("Sample Rate: %u\n", getSampleRate(waveFile));
    printf("# Channels: %d\n", waveFile->header.header[22]); // get # channels from byte 22
    printf("Output File Name: %s\n", "");

    int error = prepByteArray(reversedFile, argv[2]);

    free (waveFile);
    free (reversedFile.dataPointer);
    return 0;
}