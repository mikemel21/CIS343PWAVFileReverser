#ifndef 	__H_WAV__
#define		__H_WAV__
#include <stdio.h>

// WAV header struct
typedef struct wh {
    char header[44];
} wave_header;

//WAV file struct
typedef struct wf {
    wave_header header;
    size_t fileSize;
    char* dataPointer;
} wave_file;

// takes in a file and creates a header struct
wave_header createHeader (char* fileContents);

// loads wave file
wave_file* loadWAV(const char* path);

// creates a byte array of the file
int prepByteArray (struct wf);

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

void checkHeader(wave_file* wf);

#endif