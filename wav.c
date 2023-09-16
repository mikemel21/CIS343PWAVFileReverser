#include <stdio.h>
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
    wave_file* wave = malloc(sizeof(wave));

    wave->fileSize = sizeOfFile;
    wave->dataPointer = file; 
    
    wave->header = headerBytes;

    return wave;
}

//TODO: write the function that prepares a byte array for the reversed file and writes the new audion file to disk