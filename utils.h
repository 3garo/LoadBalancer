#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

/**
 * @brief A utility function to generate a random number within a specified range.
 * 
 * This function generates a random number between the specified minimum
 * and maximum values (inclusive).
 * 
 * @param min The minimum value of the random number range.
 * @param max The maximum value of the random number range.
 * @return A random integer between min and max (inclusive).
 */
inline int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

#endif // UTILS_H
