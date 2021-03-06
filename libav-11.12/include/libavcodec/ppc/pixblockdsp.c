/*
 * Copyright (c) 2002 Brian Foley
 * Copyright (c) 2002 Dieter Shirley
 * Copyright (c) 2003-2004 Romain Dolbeau <romain@dolbeau.org>
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "config.h"
#if HAVE_ALTIVEC_H
#include <altivec.h>
#endif

#include "libavutil/attributes.h"
#include "libavutil/cpu.h"
#include "libavutil/ppc/cpu.h"
#include "libavutil/ppc/types_altivec.h"
#include "libavutil/ppc/util_altivec.h"
#include "libavcodec/avcodec.h"
#include "libavcodec/pixblockdsp.h"

#if HAVE_ALTIVEC && HAVE_BIGENDIAN

static void get_pixels_altivec(int16_t *restrict block, const uint8_t *pixels,
                               int line_size)
{
    int i;
    vector unsigned char perm = vec_lvsl(0, pixels);
    const vector unsigned char zero =
        (const vector unsigned char) vec_splat_u8(0);

    for (i = 0; i < 8; i++) {
        /* Read potentially unaligned pixels.
         * We're reading 16 pixels, and actually only want 8,
         * but we simply ignore the extras. */
        vector unsigned char pixl = vec_ld(0, pixels);
        vector unsigned char pixr = vec_ld(7, pixels);
        vector unsigned char bytes = vec_perm(pixl, pixr, perm);

        // Convert the bytes into shorts.
        vector signed short shorts = (vector signed short) vec_mergeh(zero,
                                                                      bytes);

        // Save the data to the block, we assume the block is 16-byte aligned.
        vec_st(shorts, i * 16, (vector signed short *) block);

        pixels += line_size;
    }
}

static void diff_pixels_altivec(int16_t *restrict block, const uint8_t *s1,
                                const uint8_t *s2, int stride)
{
    int i;
    vector unsigned char perm1 = vec_lvsl(0, s1);
    vector unsigned char perm2 = vec_lvsl(0, s2);
    const vector unsigned char zero =
        (const vector unsigned char) vec_splat_u8(0);
    vector signed short shorts1, shorts2;

    for (i = 0; i < 4; i++) {
        /* Read potentially unaligned pixels.
         * We're reading 16 pixels, and actually only want 8,
         * but we simply ignore the extras. */
        vector unsigned char pixl  = vec_ld(0,  s1);
        vector unsigned char pixr  = vec_ld(15, s1);
        vector unsigned char bytes = vec_perm(pixl, pixr, perm1);

        // Convert the bytes into shorts.
        shorts1 = (vector signed short) vec_mergeh(zero, bytes);

        // Do the same for the second block of pixels.
        pixl  = vec_ld(0,  s2);
        pixr  = vec_ld(15, s2);
        bytes = vec_perm(pixl, pixr, perm2);

        // Convert the bytes into shorts.
        shorts2 = (vector signed short) vec_mergeh(zero, bytes);

        // Do the subtraction.
        shorts1 = vec_sub(shorts1, shorts2);

        // Save the data to the block, we assume the block is 16-byte aligned.
        vec_st(shorts1, 0, (vector signed short *) block);

        s1    += stride;
        s2    += stride;
        block += 8;

        /* The code below is a copy of the code above...
         * This is a manual unroll. */

        /* Read potentially unaligned pixels.
         * We're reading 16 pixels, and actually only want 8,
         * but we simply ignore the extras. */
        pixl  = vec_ld(0,  s1);
        pixr  = vec_ld(15, s1);
        bytes = vec_perm(pixl, pixr, perm1);

        // Convert the bytes into shorts.
        shorts1 = (vector signed short) vec_mergeh(zero, bytes);

        // Do the same for the second block of pixels.
        pixl  = vec_ld(0,  s2);
        pixr  = vec_ld(15, s2);
        bytes = vec_perm(pixl, pixr, perm2);

        // Convert the bytes into shorts.
        shorts2 = (vector signed short) vec_mergeh(zero, bytes);

        // Do the subtraction.
        shorts1 = vec_sub(shorts1, shorts2);

        // Save the data to the block, we assume the block is 16-byte aligned.
        vec_st(shorts1, 0, (vector signed short *) block);

        s1    += stride;
        s2    += stride;
        block += 8;
    }
}

#endif /* HAVE_ALTIVEC */

av_cold void ff_pixblockdsp_init_ppc(PixblockDSPContext *c,
                                     AVCodecContext *avctx,
                                     unsigned high_bit_depth)
{
#if HAVE_ALTIVEC && HAVE_BIGENDIAN
    if (!PPC_ALTIVEC(av_get_cpu_flags()))
        return;

    c->diff_pixels = diff_pixels_altivec;

    if (!high_bit_depth) {
        c->get_pixels = get_pixels_altivec;
    }
#endif /* HAVE_ALTIVEC */
}
