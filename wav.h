#ifndef 	__H_WAV__
#define		__H_WAV__
#include <stdio.h>

// WAV header struct; holds a char that stores the header
typedef struct wh {
    char header[44];
} wave_header;

//WAV file struct
typedef struct wf {
    wave_header header;
    // size of WAV file
    size_t fileSize;
    // pointer to the data section of the WAV file
    char* dataPointer;
} wave_file;

// takes in a file (char *) and creates a header struct from the first 44 bytes of the file
wave_header createHeader (char* fileContents);

// takes a file path and creates a wave_file struct
wave_file* loadWAV(const char* path);

// creates a byte array of the file
int prepByteArray (wave_file wf, char* path);

//* Helper functions; These functions go through the checks to ensure the WAV file is one we can work with
// returns 0 if the first 4 bytes of WAV file are "RIFF" and 1 if they are not
int isRIFF (wave_file* wf);

// returns 0 if bytes 4-7 equal the sizeOfFile-8 and 2 if not
int bits4to7 (wave_file* wf, size_t size);

// returns 0 if bytes 8-11 = WAVE and 1 if not
int isWAVE (wave_file* wf);

// returns 0 if file has two channels and 1 if it does not
int has2Channels (wave_file* wf);

// returns 0 if file has format type 1 and 1 if it does not
int formatType (wave_file* wf);

// evaluates above functions and prints detailed error depending on which function fails
void checkHeader(wave_file* wf);

// gets the Sample Rate of file
int getSampleRate (wave_file* wf);


#endif