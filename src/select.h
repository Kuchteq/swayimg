#include <stdbool.h>
#include <sys/types.h>
#include "pixmap.h"
#include "viewport.h"

struct selection {
        bool ongoing;
        ssize_t sx;
        ssize_t sy;
        ssize_t ex;
        ssize_t ey;
};
void selection_init(struct selection* s);

void selection_draw(const struct viewport* vp, struct pixmap* wnd, struct selection *s);


void selection_resize(const struct viewport* vp, struct selection* s, ssize_t w, ssize_t h);


void selection_start(const struct viewport* vp,struct selection* s, ssize_t x, ssize_t y);
