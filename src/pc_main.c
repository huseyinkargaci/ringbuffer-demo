// src/pc_main.c
#include <stdio.h>
#include <ctype.h>
#include "common.h"
#include "ring_buffer.h"

static void rb_dump(const char* tag, const ring_buffer_t* rb) {
    printf("[%s] head=%zu tail=%zu count=%zu | [", tag, rb->head, rb->tail, rb->count);
    for (size_t i = 0; i < rb->count; i++) {
        u8 b = rb->data[(rb->tail + i) % RING_BUFFER_CAP];
        if (b == '\n') printf("\\n");
        else if (b == '\r') printf("\\r");
        else if (isprint(b)) printf("%c", b);
        else printf("0x%02X", b);
        if (i + 1 < rb->count) printf(" ");
    }
    printf("]\n");
}

int main(void){
    ring_buffer_t rx;
    ring_buffer_init(&rx);

    puts("Write characters and press ENTER button to see them echoed back."
         " CTRL+Z to exit.");

    int ch;
    while ((ch = getchar()) != EOF) {
        u8 b = (u8)ch;
        if (b == '\r') continue;

        status_t st = ring_buffer_put(&rx, b);
        if (st == ST_FULL) {
            puts("[WARN] RX buffer FULL (char dropped)");
        }

        
        if (b == '\n') {
            
            printf(">> ");
            u8 out;
            while (ring_buffer_get(&rx, &out) == ST_OK) {
                if (out == '\n') break;             // satır sonu
                putchar(out);
            }
            putchar('\n');
            rb_dump("after line", &rx);
        }
    }

    puts("Exiting...");
    return 0;
}
