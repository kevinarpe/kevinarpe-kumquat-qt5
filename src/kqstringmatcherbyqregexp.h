//
// Created by kca on 5/17/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_QSTRINGMATCHERBYQREGEXP_H
#define KEVINARPE_KUMQUAT_QT5_QSTRINGMATCHERBYQREGEXP_H

#include "KStringMatch"
#include <QRegExp>
#include <vector>
#include <algorithm>
#include <cassert>

namespace kumquat {

class KQStringMatcherByQRegExp {

public:
    KQStringMatcherByQRegExp(std::initializer_list<QRegExp> list);

    bool
    match(const QString& s, KStringMatchVec* const v)
    const;

private:
    typedef std::vector<QRegExp> _QRegExpVec;

    const _QRegExpVec _regExpVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_QSTRINGMATCHERBYQREGEXP_H
