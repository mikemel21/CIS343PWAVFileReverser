#ifndef 	__H_WAV__
#define		__H_WAV__
#include <stdio.h>

//* returns 0 if the first 4 bytes of WAV file are "RIFF" and 1 if they are not
int isRIFF (char* fileContents);

//* returns 0 if bytes 4-7 equal the sizeOfFile-8 and 2 if not
int bits4to7 (char* fileContents, size_t size);

//* returns 0 if bytes 8-11 = WAVE and 1 if not
int isWAVE (char* fileContents);

//* returns 0 if file has two channels and 1 if it does not
int has2Channels (char* fileContents);

//* returns 0 if file has format type 1 and 1 if it does not
int formatType (char* fileContents);
#endif