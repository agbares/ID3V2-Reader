#include <cstdio>
#include "ID3V2.h"

ID3V2::ID3V2() {

}

ID3V2::ID3V2(const char* path) {
  if (!readHeader(path)) {
    validTag = false;
    return;

  } else {
    validTag = true;
    readTag(path);
  }
}

int ID3V2::getMajorVersion() const {
  return header.majorVersion;
}

int ID3V2::getMinorVersion() const {
  return header.minorVersion;
}

char ID3V2::getFlags() const {
  return header.flags;
}

size_t ID3V2::getSize() const {
  return header.size;
}

bool ID3V2::isValidIdentifier() const {
  const char* EXPECTED_IDENTIFIER = "ID3";

  if (strcmp(header.identifier, EXPECTED_IDENTIFIER) == 0) {
    return true;
  }

  return false;
}

bool ID3V2::isValidVersion() const {
  const int validVersion = 4;

  if (header.majorVersion == 4) {
    return true;
  }

  return false;
}

bool ID3V2::isValidTag() const {
  return validTag;
}

void ID3V2::getFrameData(FRAME_TYPE frameType, char *data, size_t bytesToRead) {
  switch (frameType) {
    case FRAME_TYPE::ALBUM:
      strncpy(data, album.data, bytesToRead - 1);
      break;

    case FRAME_TYPE::ARTIST:
      strncpy(data, artist.data, bytesToRead - 1);
      break;

    case FRAME_TYPE::TITLE:
      strncpy(data, title.data, bytesToRead - 1);
      break;

    default:
      break;
  }
}

void ID3V2::readTag(const char* path) {
  std::fstream file;
  file.open(path);

  if (!file.is_open())
    std::cout << "File open failure!" << std::endl;
  else {
    
    char data[FRAME_BYTES_TO_READ];
    file.seekg(HEADER_LENGTH);
    file.read(data, FRAME_BYTES_TO_READ);

    int offset = 0;

    while (offset < FRAME_BYTES_TO_READ) {
      FrameHeader frameHeader((data + offset));
      if (isDesiredFrame(frameHeader.id)) {
        Frame frame(frameHeader);

        // for (int i = 0; i < 4; i++) {
        //   printf("%c", frame.header.id[i]);
        // }

        // For some reason the ID3V2 frame's contain an empty byte between the header and the data.
        int dataOffset = 1;
        int bytesToRead = (frame.header.size < Frame::NUM_BYTES_TO_READ) ? frame.header.size - dataOffset : Frame::NUM_BYTES_TO_READ;

        strncat(frame.data, (data + offset + HEADER_LENGTH + dataOffset), bytesToRead);

        // std::cout << "\nsize: " << frame.header.size << std::endl;
        // std::cout << "Data: " << frame.data << std::endl;
        // std::cout << "\n";

        FRAME_TYPE frameType = strToFrameType(frameHeader.id);
        switch (frameType) {
          case FRAME_TYPE::ALBUM:
            album = frame;
            break;
          
          case FRAME_TYPE::ARTIST:
            artist = frame;
            break;
          
          case FRAME_TYPE::TITLE:
            title = frame;
            break;

          default:
            break;
        }

      }

      offset += frameHeader.size + HEADER_LENGTH;
    }

    file.close();
  }
}

bool ID3V2::readHeader(const char* path) {
  std::fstream file;
  file.open(path);

  if (!file.is_open()) {
    std::cout << "File open failure!" << std::endl;
    return false;

  } else {
    char headerArr[HEADER_LENGTH];

    file.read(headerArr, sizeof(headerArr));
    
    strncpy(header.identifier, headerArr, sizeof(header.identifier) - 1);

    header.majorVersion = headerArr[3];
    header.minorVersion = headerArr[4];
    header.flags = headerArr[5];

    // Check validity of the tag before continuing on
    if (!isValidIdentifier() || !isValidVersion()) {
      return false;
    }

    const int MSB = 7;
    header.size = 0;
    header.size = headerArr[6] * pow(2, MSB * 3);
    header.size += headerArr[7] * pow(2, MSB * 2);
    header.size += headerArr[8] * pow(2, MSB * 1);
    header.size += headerArr[9] * pow(2, MSB * 0);

    file.close();

    return true;
  }
}