#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Debug verbosity
 * -1: no debug logs
 *  0: errors only
 *  1: + INFO logs
 *  2: + warnings
 *  3: + TRACE logs
 *
 */

extern int debug_level;

#define LOG_START()                                                            \
    char* str_level = getenv("DEBUG");                                         \
    debug_level = str_level ? atoi(str_level) : 0;

#define ERROR(...)                                                             \
    do {                                                                       \
        if (debug_level >= 0) {                                                \
            printf("[ERROR] %s:%d ", __FILE__, __LINE__);                      \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
        }                                                                      \
    } while (0)

#define WARN(...)                                                              \
    do {                                                                       \
        if (debug_level >= 1) {                                                \
            printf("[WARNING] %s:%d ", __FILE__, __LINE__);                    \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
        }                                                                      \
    } while (0)

#define INFO(...)                                                              \
    do {                                                                       \
        if (debug_level >= 2) {                                                \
            printf("[INFO] %s:%d ", __FILE__, __LINE__);                       \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
        }                                                                      \
    } while (0)

#define TRACE(...)                                                             \
    do {                                                                       \
        if (debug_level >= 3) {                                                \
            printf("[TRACE] %s:%d ", __FILE__, __LINE__);                      \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
        }                                                                      \
    } while (0)

#define assert(cond, ...)                                                      \
    ({                                                                         \
        if (!(cond)) {                                                         \
            printf("[ERROR] Assertion failed %s:%d %s. ",                      \
                   __FILE__,                                                   \
                   __LINE__,                                                   \
                   #cond);                                                     \
            printf(""__VA_ARGS__);                                             \
            printf("\n");                                                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    })

#endif
