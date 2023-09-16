#include <stdio.h>
#include <stdint.h>
#include "file_lib.h"
#include "wav.h"

int main(int argc, char** argv) { 
    size_t sizeOfFile; // size of WAV file
    char* fileContents = read_file(argv[1], &sizeOfFile); // stores the WAV file contents

    // requirement checking
    if (isRIFF(fileContents) == 1 || bits4to7(fileContents, sizeOfFile) == 1 || isWAVE(fileContents) == 1 || has2Channels(fileContents) == 1 || formatType(fileContents) == 1) {
        printf("Unable to process file.\n");
        // TODO: Make specific error messages for each requirement
        exit(1);
    }

    // file that will hold the reversed WAV
    char* reversedFile = malloc(sizeOfFile);


    printf("Success.");

    free (fileContents);
    return 0;
}