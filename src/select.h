#include "pixmap.h"
#include "viewport.h"

#include <stdbool.h>
#include <sys/types.h>

struct selection {
    bool ongoing;
    ssize_t sx;
    ssize_t sy;
    ssize_t ex;
    ssize_t ey;
};

char* get_formatted_selection(void);

void selection_init(void);

void selection_draw(const struct viewport* vp, struct pixmap* wnd);

void selection_resize(const struct viewport* vp, ssize_t w, ssize_t h);

void selection_start(const struct viewport* vp, ssize_t x, ssize_t y);
