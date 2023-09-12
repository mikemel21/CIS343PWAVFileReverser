#ifndef 	__H_LIB_FILE__
#define		__H_LIB_FILE__

/**
 *
 * MrW's simple file reading/writing library.
 * 2023
 *
 * Is it full proof and ready for production?  Probably not.
 * Use at your own risk.  Intended purpose is to reinforce using
 * pointers.
 *
 * Usage:
 *
 * Of course, you first need to import the library header with
 *
 * #include "file_lib.h"
 *
 * READING A FILE
 * ==============
 *
 * To read a file you would make a call such as:
 *
 * size_t size;
 * char* file_contents = read_file("/path/to/my/file", &size);
 * 
 * (Make sure NULL wasn't returned, or else there was an error!)
 *
 * file_contents can then be used like an array of chars.
 * Be sure to free the memory before exiting:
 *
 * free(file_contents);
 *
 * WRITING A FILE
 * ==============
 *
 * Writing a chunk of bytes to a file can be performed as such:
 *
 * int error = write_file("/path/to/my/file", size);
 *
 * (Make sure 0 was returned for success, otherwise there was an error!)
 *
 * This is assuming you already have a chunk of bytes already, called
 * "byteArray", and you know its size which is stored in "byteArraySize".
 *
 */

#include <stdlib.h>

/*
 * The read_file function will attempt to read a file into a new buffer.
 *
 * Args:
 * 	path: A path string to the file's location.
 *	fileSize: A pointer to a size_t so that we can let the calling
 *		  function know how many bytes we were able to read in.
 * Returns:
 *	A pointer to the memory where the file locations are stored, or
 *	NULL on failure.
 */

char* read_file(const char* path, size_t* fileSize);

/*
 * The write_file function will attempt to write a chunk of bytes to the
 * given path.
 *
 * Args:
 *	path: A path string to the file's location.
 *	byteArray: The data to save (a chunk of bytes).
 *	byteArraySize: The size of the array.
 * Returns:
 *	0 on success or the perror errno code otherwsie.
 */

int write_file(const char* path, const char* byteArray, size_t byteArraySize);

#endif
