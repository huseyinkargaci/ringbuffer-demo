#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef enum {
    ST_OK    = 0,
    ST_ERR   = -1,
    ST_FULL  = -2,
    ST_EMPTY = -3
} status_t;

#endif /* COMMON_H */
