#include "command_interface.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "face_gallery.h"
#include "idle_animation.h"

namespace {

constexpr size_t kMaxCommandLength = 64;

char commandBuffer[kMaxCommandLength];
size_t commandLength = 0;

void trimTrailingWhitespace(char* text) {
  size_t length = strlen(text);
  while (length > 0 && isspace(static_cast<unsigned char>(text[length - 1])) != 0) {
    text[length - 1] = '\0';
    --length;
  }
}

char* trimLeadingWhitespace(char* text) {
  while (*text != '\0' && isspace(static_cast<unsigned char>(*text)) != 0) {
    ++text;
  }
  return text;
}

void toUpperInPlace(char* text) {
  for (; *text != '\0'; ++text) {
    *text = static_cast<char>(toupper(static_cast<unsigned char>(*text)));
  }
}

void toLowerInPlace(char* text) {
  for (; *text != '\0'; ++text) {
    *text = static_cast<char>(tolower(static_cast<unsigned char>(*text)));
  }
}

void replyOk(const char* message) {
  Serial.print("OK");
  if (message != nullptr && message[0] != '\0') {
    Serial.print(' ');
    Serial.print(message);
  }
  Serial.print('\n');
}

void replyError(const char* message) {
  Serial.print("ERR ");
  Serial.print(message);
  Serial.print('\n');
}

bool parseDirection(const char* text, int8_t& direction) {
  if (strcmp(text, "LEFT") == 0) {
    direction = -1;
    return true;
  }
  if (strcmp(text, "RIGHT") == 0) {
    direction = 1;
    return true;
  }
  if (strcmp(text, "CENTER") == 0 || strcmp(text, "CENTRE") == 0) {
    direction = 0;
    return true;
  }
  return false;
}

void processFaceArgument(char* argument, unsigned long now) {
  argument = trimLeadingWhitespace(argument);
  trimTrailingWhitespace(argument);
  toLowerInPlace(argument);

  if (!FaceGallery::setByName(argument)) {
    replyError("unknown face");
    return;
  }

  IdleAnimation::triggerAttention(now, 0);
  replyOk(argument);
}

void processCommand(char* line, unsigned long now) {
  line = trimLeadingWhitespace(line);
  trimTrailingWhitespace(line);
  if (*line == '\0') {
    return;
  }

  char original[kMaxCommandLength];
  strncpy(original, line, sizeof(original) - 1);
  original[sizeof(original) - 1] = '\0';

  char uppercase[kMaxCommandLength];
  strncpy(uppercase, line, sizeof(uppercase) - 1);
  uppercase[sizeof(uppercase) - 1] = '\0';
  toUpperInPlace(uppercase);

  char* space = strchr(uppercase, ' ');
  char* argUpper = nullptr;
  if (space != nullptr) {
    *space = '\0';
    argUpper = trimLeadingWhitespace(space + 1);
  }

  if (strcmp(uppercase, "PING") == 0) {
    replyOk("PONG");
    return;
  }

  if (strcmp(uppercase, "NEXT") == 0) {
    FaceGallery::next();
    IdleAnimation::triggerAttention(now, 1);
    replyOk(FaceGallery::currentName());
    return;
  }

  if (strcmp(uppercase, "PREV") == 0 || strcmp(uppercase, "PREVIOUS") == 0) {
    FaceGallery::previous();
    IdleAnimation::triggerAttention(now, -1);
    replyOk(FaceGallery::currentName());
    return;
  }

  if (strcmp(uppercase, "BLINK") == 0) {
    IdleAnimation::triggerBlink(now);
    replyOk("BLINK");
    return;
  }

  if (strcmp(uppercase, "ATTEND") == 0) {
    int8_t direction = 0;
    if (argUpper != nullptr && *argUpper != '\0' && !parseDirection(argUpper, direction)) {
      replyError("invalid attention direction");
      return;
    }
    IdleAnimation::triggerAttention(now, direction);
    replyOk("ATTEND");
    return;
  }

  if (strcmp(uppercase, "FACE") == 0) {
    if (argUpper == nullptr || *argUpper == '\0') {
      replyError("missing face name");
      return;
    }
    char* argOriginal = strchr(original, ' ');
    if (argOriginal == nullptr) {
      replyError("missing face name");
      return;
    }
    processFaceArgument(argOriginal + 1, now);
    return;
  }

  if (strcmp(uppercase, "INDEX") == 0) {
    if (argUpper == nullptr || *argUpper == '\0') {
      replyError("missing face index");
      return;
    }
    const long index = strtol(argUpper, nullptr, 10);
    if (index < 0 || index > 255 || !FaceGallery::setByIndex(static_cast<uint8_t>(index))) {
      replyError("invalid face index");
      return;
    }
    IdleAnimation::triggerAttention(now, 0);
    replyOk(FaceGallery::currentName());
    return;
  }

  if (strncmp(uppercase, "SHOW_FACE_", 10) == 0) {
    char faceName[kMaxCommandLength];
    strncpy(faceName, uppercase + 10, sizeof(faceName) - 1);
    faceName[sizeof(faceName) - 1] = '\0';
    toLowerInPlace(faceName);
    if (!FaceGallery::setByName(faceName)) {
      replyError("unknown face");
      return;
    }
    IdleAnimation::triggerAttention(now, 0);
    replyOk(faceName);
    return;
  }

  char lowerLine[kMaxCommandLength];
  strncpy(lowerLine, original, sizeof(lowerLine) - 1);
  lowerLine[sizeof(lowerLine) - 1] = '\0';
  toLowerInPlace(lowerLine);
  if (FaceGallery::setByName(lowerLine)) {
    IdleAnimation::triggerAttention(now, 0);
    replyOk(lowerLine);
    return;
  }

  replyError("unknown command");
}

}  // namespace

namespace CommandInterface {

void begin() {
  commandBuffer[0] = '\0';
  commandLength = 0;
}

void update(unsigned long now) {
  while (Serial.available() > 0) {
    const int raw = Serial.read();
    if (raw < 0) {
      break;
    }

    const char ch = static_cast<char>(raw);
    if (ch == '\r') {
      continue;
    }

    if (ch == '\n') {
      commandBuffer[commandLength] = '\0';
      processCommand(commandBuffer, now);
      commandLength = 0;
      commandBuffer[0] = '\0';
      continue;
    }

    if (commandLength < (kMaxCommandLength - 1)) {
      commandBuffer[commandLength++] = ch;
      commandBuffer[commandLength] = '\0';
    }
  }
}

}  // namespace CommandInterface
