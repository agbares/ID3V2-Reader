#ifndef __ID3V2_H__
#define __ID3V2_H__

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>

#include "Frame.h"

class ID3V2 {
private:
  const int ID3V2_HEADER_SIZE = 10;
  static const int FRAME_BYTES_TO_READ = 512;

  bool validTag;
  
  struct Header {
    char identifier[4] = { 0 };
    int majorVersion;
    int minorVersion;
    char flags;
    size_t size;

  } header;

  bool isValidIdentifier() const;
  bool isValidVersion() const;

  Frame album;
  Frame artist;
  Frame title;

public:
  ID3V2();
  ID3V2(const char* path);
  
  int getMajorVersion() const;
  int getMinorVersion() const;
  char getFlags() const;
  size_t getSize() const;
  bool isValidTag() const;

  void getFrameData(FRAME_TYPE frameType, char *data, size_t bytesToRead);
  void readTag(const char* path);
  bool readHeader(const char* path);

  static const int HEADER_LENGTH = 10;
};

#endif