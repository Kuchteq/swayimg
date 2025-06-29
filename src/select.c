#include "select.h"

#include "pixmap.h"
#include "viewport.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/** Global selection context. */
static struct selection ctx;

static char formatted_selection[128];

void selection_init(void)
{
    ctx.ongoing = false;
    ctx.sx = 0;
    ctx.sy = 0;
    ctx.ex = 0;
    ctx.ey = 0;
    formatted_selection[0] = 0;
}

char* get_formatted_selection(void)
{
    snprintf(formatted_selection, sizeof(formatted_selection),
             "%zdx%zd+%zd+%zd", ctx.ex - ctx.sx, ctx.ey - ctx.sy, ctx.sx,
             ctx.sy);
    return formatted_selection;
}

void selection_draw(const struct viewport* vp, struct pixmap* wnd)
{
    if (!ctx.ongoing) {
        return;
    }
    const struct pixmap* pm = viewport_pixmap(vp);
    const size_t width = vp->scale * pm->width;
    const size_t height = vp->scale * pm->height;
    const size_t sx = ctx.sx * vp->scale;
    const size_t sy = ctx.sy * vp->scale;

    const size_t ex = ctx.ex * vp->scale;
    const size_t ey = ctx.ey * vp->scale;

    argb_t backdrop = 0xbb000000;

    // Dim regions outside the selection rectangle
    pixmap_blend(wnd, vp->x, vp->y, sx, height, backdrop);
    pixmap_blend(wnd, vp->x + ex, vp->y, width - ex, height, backdrop);
    pixmap_blend(wnd, vp->x + sx, vp->y, ex - sx, sy, backdrop);
    pixmap_blend(wnd, vp->x + sx, vp->y + ey, ex - sx, height - ey, backdrop);
}

void selection_resize(const struct viewport* vp, ssize_t x, ssize_t y)
{
    ctx.ex = (x - vp->x) / vp->scale;
    ctx.ey = (y - vp->y) / vp->scale;
}

void selection_start(const struct viewport* vp, ssize_t x, ssize_t y)
{
    ctx.ongoing = true;
    ctx.sx = max(x - vp->x, 0) / vp->scale;
    ctx.sy = max(y - vp->y, 0) / vp->scale;
}
