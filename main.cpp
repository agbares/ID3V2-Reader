#include <iostream>
#include "ID3V2.h"
#include "Frame.h"

int main()
{
  const char* path = { "saymyname.mp3" };
  ID3V2 tag(path);

  std::cout << "Valid? " << tag.isValidTag() << std::endl;

  char data[Frame::NUM_BYTES_TO_READ] = { 0 };
  tag.getFrameData(FRAME_TYPE::ALBUM, data, sizeof(data));

  std::cout << "Album: " << data << std::endl;

  tag.getFrameData(FRAME_TYPE::ARTIST, data, sizeof(data));
  std::cout << "Artist: " << data << std::endl;
  
  tag.getFrameData(FRAME_TYPE::TITLE, data, sizeof(data));
  std::cout << "Title: " << data << std::endl;
  
  return 0;
}