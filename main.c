#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file_lib.h"
#include "wav.h"

int main(int argc, char** argv) { 
    wave_file* waveFile = loadWAV(argv[1]);
    printf("Input File Name: %s\n", argv[1]);
    // validates file can be reversed
    checkHeader(waveFile);


    free (waveFile);
    return 0;
}