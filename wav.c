#include <stdio.h>
#include <stdint.h>
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
    wave_file* wave = malloc(sizeof(wave));
    size_t sizeOfFile;
    wave->dataPointer = read_file(path, &sizeOfFile); // stores the WAV file contents
    wave->header = createHeader(wave->dataPointer);
    wave->fileSize = sizeOfFile;

    return wave;
}