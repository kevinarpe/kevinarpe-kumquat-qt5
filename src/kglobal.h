//
// Created by kca on 5/10/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KGLOBAL_H
#define KEVINARPE_KUMQUAT_QT5_KGLOBAL_H

#include <cassert>

/**
 * Aborts if {@code predicateResult} is false, or returns {@code value}.
 *
 * To be used in assignment statements, such as constructor initialiser lists.
 *
 * @param value
 *        value to test and return, e.g., vec (std::vector<>)
 * @param predicateResult
 *        value to be boolean tested as not false, e.g., {@code vec.empty()}
 * @param message
 *        string literal for assert message, e.g., {@code "Argument 'vec' is empty"}
 *
 * @return checked value
 *
 * @see http://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
 */
#define KASSERT(value, predicateResult, message) \
    ((!(predicateResult)) ? assert((predicateResult) && (message)) : (value))

#endif //KEVINARPE_KUMQUAT_QT5_KGLOBAL_H
