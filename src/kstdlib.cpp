//
// Created by kca on 5/16/15.
//

#include "kstdlib"
#include <string>
#include <iostream>

namespace kumquat {

void
kabort(std::string message) {
      std::cerr << message << std::endl;
      std::abort();
}

}  // namespace kumquat
