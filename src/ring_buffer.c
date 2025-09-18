#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *rb) {
    rb->head = rb->tail = rb->count = 0;
}

bool ring_buffer_is_empty(const ring_buffer_t *rb) {
    return rb->count == 0;
}

bool ring_buffer_is_full(const ring_buffer_t *rb) {
    return rb->count == RING_BUFFER_CAP;
}

size_t ring_buffer_size(const ring_buffer_t *rb) {
    return rb->count;
}

status_t ring_buffer_put(ring_buffer_t *rb, u8 byte) {
    if (ring_buffer_is_full(rb)) {
        // Politika 1: yeni geleni düşür (şimdilik bunu yapıyoruz)
        return ST_FULL;

        // Politika 2 (istersen): en eskisini at, yeniyi al
        // rb->tail = (rb->tail + 1) % RING_BUFFER_CAP;
        // rb->count--;
    }
    rb->data[rb->head] = byte;
    rb->head = (rb->head + 1) % RING_BUFFER_CAP;
    rb->count++;
    return ST_OK;
}

status_t ring_buffer_get(ring_buffer_t *rb, u8 *byte) {
    if (ring_buffer_is_empty(rb)) return ST_EMPTY;
    *byte = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_CAP;
    rb->count--;
    return ST_OK;
}

void ring_buffer_clear(ring_buffer_t *rb) {
    rb->head = rb->tail = rb->count = 0;
}
