#include "select.h"

#include "pixmap.h"
#include "viewport.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void selection_init(struct selection* s)
{
    s->ongoing = false;
    s->sx = 0;
    s->sy = 0;
    s->ex = 0;
    s->ey = 0;
}

void selection_draw(const struct viewport* vp, struct pixmap* wnd,
                    struct selection* s)
{
    if (!s->ongoing) {
        return;
    }
    const struct pixmap* pm = viewport_pixmap(vp);
    const size_t width = vp->scale * pm->width;
    const size_t height = vp->scale * pm->height;
    const size_t sx = s->sx * vp->scale;
    const size_t sy = s->sy * vp->scale;

    const size_t ex = s->ex * vp->scale;
    const size_t ey = s->ey * vp->scale;

    argb_t backdrop = 0xbb000000;

    // Dim regions outside the selection rectangle
    pixmap_blend(wnd, vp->x, vp->y, sx, height, backdrop);
    pixmap_blend(wnd, vp->x + ex, vp->y, width - ex, height, backdrop);
    pixmap_blend(wnd, vp->x + sx, vp->y, ex - sx, sy, backdrop);
    pixmap_blend(wnd, vp->x + sx, ey, ex - sx, height - sy, backdrop);
}

void selection_resize(const struct viewport* vp, struct selection* s, ssize_t x,
                      ssize_t y)
{
    s->ex = (x - vp->x) / vp->scale;
    s->ey = (y - vp->y) / vp->scale;
    printf("%d x %d\n", s->ex, s->ey);
}

void selection_start(const struct viewport* vp, struct selection* s, ssize_t x,
                     ssize_t y)
{
    s->ongoing = true;
    // s->sx = max(x-vp->x, 0)/vp->scale;
    // s->sy = max(y-vp->y, 0)/vp->scale;
    s->sx = max(x - vp->x, 0) / vp->scale;
    s->sy = max(y - vp->y, 0) / vp->scale;
    printf("%d x %d\n", s->sx, s->sy);
}
