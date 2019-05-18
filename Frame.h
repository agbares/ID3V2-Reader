#ifndef __FRAME_H__
#define __FRAME_H__

#include <cstring>
#include <cmath>

struct FrameHeader {
  char id[5];
  size_t size = 0;
  char flags[2] = { 0 };

  FrameHeader(const char* header);
  FrameHeader();

};

struct Frame {
  FrameHeader header;
  
  static const int NUM_BYTES_TO_READ = 50;
  char data[NUM_BYTES_TO_READ + 1] = { 0 }; // + 1 to hold null terminating character

  Frame(FrameHeader header);
  Frame();
};

enum class FRAME_TYPE {
  ALBUM,
  ARTIST,
  TITLE,
  INVALID
};

extern bool isDesiredFrame(const char* frameID);
extern FRAME_TYPE strToFrameType(const char* frameID);

#endif