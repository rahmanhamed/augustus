#include "image.h"

#include "Data/State.h"

static const int CORPSE_IMAGE_OFFSETS[128] = {
    0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static const int CART_OFFSETS_X[] = {13, 18, 12, 0, -13, -18, -13, 0};
static const int CART_OFFSETS_Y[] = {-7, -1, 7, 11, 6, -1, -7, -12};

void figure_image_update(figure *f, int image_base)
{
    if (f->actionState == FigureActionState_149_Corpse) {
        f->graphicId = image_base + CORPSE_IMAGE_OFFSETS[f->waitTicks / 2] + 96;
    } else {
        f->graphicId = image_base + figure_image_direction(f) + 8 * f->graphicOffset;
    }
}

void figure_image_increase_offset(figure *f, int max)
{
    f->graphicOffset++;
    if (f->graphicOffset >= (max)) {
        f->graphicOffset = 0;
    }
}

void figure_image_set_cart_offset(figure *f, int direction)
{
    f->xOffsetCart = CART_OFFSETS_X[direction];
    f->yOffsetCart = CART_OFFSETS_Y[direction];
}

int figure_image_corpse_offset(figure *f)
{
    return CORPSE_IMAGE_OFFSETS[f->waitTicks / 2];
}

int figure_image_direction(figure *f)
{
    int dir = f->direction - Data_State.map.orientation;
    if (dir < 0) {
        dir += 8;
    }
    return dir;
}

int figure_image_normalize_direction(int direction)
{
    return (8 + direction - Data_State.map.orientation) % 8;
}