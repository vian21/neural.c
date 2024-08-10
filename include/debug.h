#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#define ERROR(...) do{ \
    printf("[ERROR] %s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); \
}while(0)

#define WARN(...) do{ \
    printf("[WARNING] %s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); \
}while(0)

#define INFO(...) do{ \
    printf("[INFO] %s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); \
}while(0)

#define TRACE(...) do{ \
    printf("[TRACE] %s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); \
}while(0)

#ifdef PRODUCTION
    #undef TRACE
    #define TRACE(...) do{}while(0)
#endif

#endif