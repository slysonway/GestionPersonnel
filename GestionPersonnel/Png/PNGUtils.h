//
//  testpng.h
//  QRGenerator
//
//  Created by Pierre Kettmus on 19/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#ifndef testpng_h
#define testpng_h

#include <stdio.h>
#include "qrcodegen.h"

/* A coloured pixel. */

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

/* A picture. */

typedef struct  {
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;

static pixel_t * pixel_at (bitmap_t * bitmap, int x, int y);
static int save_png_to_file (bitmap_t *bitmap, const char *path);
static int pix (int value, int max);
int generatePNG(int **buffer, char * FileName);
void resizeBitMap(QRCode qrcode, int nSize, int *buffer[]);

#endif /* testpng_h */
