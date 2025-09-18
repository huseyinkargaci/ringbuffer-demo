#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RING_BUFFER_CAP 128

typedef struct {
    u8     data[RING_BUFFER_CAP];
    size_t head;   // yazma ucu
    size_t tail;   // okuma ucu
    size_t count;  // mevcut byte sayısı
} ring_buffer_t;

/* API */
void    ring_buffer_init     (ring_buffer_t *rb);
bool    ring_buffer_is_empty (const ring_buffer_t *rb);
bool    ring_buffer_is_full  (const ring_buffer_t *rb);
size_t  ring_buffer_size     (const ring_buffer_t *rb);
status_t ring_buffer_put     (ring_buffer_t *rb, u8 byte);
status_t ring_buffer_get     (ring_buffer_t *rb, u8 *byte);
void    ring_buffer_clear    (ring_buffer_t *rb);

/* Eski isimlere uyumluluk (istersen main.c'yi hiç değiştirme) */
#define RB_CAP          RING_BUFFER_CAP
#define rb_init         ring_buffer_init
#define rb_is_empty     ring_buffer_is_empty
#define rb_is_full      ring_buffer_is_full
#define rb_size         ring_buffer_size
#define rb_push         ring_buffer_put
#define rb_pop          ring_buffer_get
#define rb_reset        ring_buffer_clear

#ifdef __cplusplus
}
#endif
#endif /* RING_BUFFER_H */
