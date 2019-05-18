#include "Frame.h"

FrameHeader::FrameHeader() {

}

FrameHeader::FrameHeader(const char* header) {
  memcpy(id, header, sizeof(id));
  memcpy(flags, (header + 8), 2);

  const int MSB = 7;
  size = 0;
  size = header[4] * pow(2, MSB * 3);
  size += header[5] * pow(2, MSB * 2);
  size += header[6] * pow(2, MSB * 1);
  size += header[7] * pow(2, MSB * 0);
}

Frame::Frame(FrameHeader header): header(header) {

}

Frame::Frame() {
  
}

bool isDesiredFrame(const char* frameID) { 
  FRAME_TYPE frameType = strToFrameType(frameID);

  switch (frameType) {
    case FRAME_TYPE::ALBUM:
    case FRAME_TYPE::ARTIST:
    case FRAME_TYPE::TITLE:
      return true;
      break;

    case FRAME_TYPE::INVALID:
    default:
      return false;
      break;
  }
}

FRAME_TYPE strToFrameType(const char* frameID) {
  const char * const ALBUM = "TALB";
  const char * const ARTIST = "TPE1";
  const char * const TITLE = "TIT2";

  if (strcmp(frameID, TITLE) == 0) {
    return FRAME_TYPE::TITLE;
  } else if (strcmp(frameID, ARTIST) == 0) {
    return FRAME_TYPE::ARTIST;
  } else if (strcmp(frameID, ALBUM) == 0) {
    return FRAME_TYPE::ALBUM;
  } else {
    return FRAME_TYPE::INVALID;
  }
} 