//
// Created by kca on 5/16/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KSTDLIB_H
#define KEVINARPE_KUMQUAT_QT5_KSTDLIB_H

#include <string>
#include <iostream>

namespace kumquat {

void
kabort(std::string message);

void
__kabort(std::string message, const char* const filePath, unsigned int lineNumber, const char* const prettyFunc);

#define KABORT(std_string_message) __kabort(std_string_message, __FILE__, __LINE__, __PRETTY_FUNCTION__)

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KSTDLIB_H
