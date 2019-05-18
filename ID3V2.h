#ifndef __ID3V2_H__
#define __ID3V2_H__

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>

#include "Frame.h"

class ID3V2 {
private:
  const int FRAME_BYTES_TO_READ = 512;
  const int HEADER_LENGTH = 10;

  bool validTag;
  
  Frame album;
  Frame artist;
  Frame title;
  
  struct Header {
    char identifier[4] = { 0 };
    int majorVersion;
    int minorVersion;
    char flags;
    size_t size;

  } header;

  bool isValidIdentifier() const;
  bool isValidVersion() const;
  
  void readTag(const char* path);
  bool readHeader(const char* path);


public:
  ID3V2();
  ID3V2(const char* path);
  
  int getMajorVersion() const;
  int getMinorVersion() const;
  char getFlags() const;
  size_t getSize() const;
  bool isValidTag() const;

  void getFrameData(FRAME_TYPE frameType, char *data, size_t bytesToRead);

};

#endif