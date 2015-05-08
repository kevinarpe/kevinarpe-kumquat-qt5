//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H
#define KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H

#include <Qt>

namespace kumquat {

enum Dimension {
    Row = 0x1,
    Column = 0x2,
};

Q_DECLARE_FLAGS(Dimensions, Dimension)

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H
