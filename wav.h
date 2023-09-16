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

#endif