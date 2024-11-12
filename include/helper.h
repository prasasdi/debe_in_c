#ifndef HELPER_H_
#define HELPER_H_

#include <stdio.h>
#include <stdlib.h>

size_t win_getline(char** lineptr, size_t* n, FILE* stream);

size_t win_getline(char** lineptr, size_t* n, FILE* stream) {
  if (lineptr == NULL || n == NULL || stream == NULL) {
    return -1;
  }
  size_t pos = 0;
  int c; // character
  
  if (*lineptr == NULL) {
    *n = 128; //initial buffer size
    *lineptr = (char*) malloc(*n);
    if (*lineptr == NULL ){
      perror("*lineptr malloc()");
      return -1;
    }
  }

  while((c = fgetc(stream)) != EOF) {
    if (pos + 1 >= *n) {
      size_t new_size = *n * 2;
      char* new_ptr = (char*)realloc(*lineptr, new_size);
      if (new_ptr == NULL) {
        perror("new_ptr realloc()");
        return -1;
      }
      *lineptr = new_ptr;
      *n = new_size;
    }
    (*lineptr)[pos++] = (char)c;
    if (c == '\n') {
      break;
    }
  }
  if (pos == 0 && c == EOF) {
    return -1; // no characters read, end of file
  }

  (*lineptr)[pos] = '\0';
  return pos;
}

#endif

