#include <stdio.h>
#include "common.h"
#include "ring_buffer.h"

int main(void){
    ring_buffer_t rx;
    ring_buffer_init(&rx);

    // Örnek: bir şeyler push et
    const char *msg = "SET LED ON\n";
    for (const char *p = msg; *p; ++p) {
        status_t st = ring_buffer_put(&rx, (u8)*p);
        if (st == ST_FULL) { puts("[FULL]"); break; }
    }

    // '\n' gelmiş gibi satırı pop et ve yazdır
    u8 ch;
    while (ring_buffer_get(&rx, &ch) == ST_OK) {
        if (ch == '\n') break;
        putchar(ch);
    }
    putchar('\n');
    return 0;
}
