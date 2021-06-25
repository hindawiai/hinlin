<शैली गुरु>
/*
 *  Fast C2P (Chunky-to-Planar) Conversion
 *
 *  Copyright (C) 2003-2008 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/unaligned.h>

#समावेश "c2p.h"
#समावेश "c2p_core.h"


    /*
     *  Perक्रमm a full C2P step on 32 8-bit pixels, stored in 8 32-bit words
     *  containing
     *    - 32 8-bit chunky pixels on input
     *    - permutated planar data (1 plane per 32-bit word) on output
     */

अटल व्योम c2p_32x8(u32 d[8])
अणु
	transp8(d, 16, 4);
	transp8(d, 8, 2);
	transp8(d, 4, 1);
	transp8(d, 2, 4);
	transp8(d, 1, 2);
पूर्ण


    /*
     *  Array containing the permutation indices of the planar data after c2p
     */

अटल स्थिर पूर्णांक perm_c2p_32x8[8] = अणु 7, 5, 3, 1, 6, 4, 2, 0 पूर्ण;


    /*
     *  Store a full block of planar data after c2p conversion
     */

अटल अंतरभूत व्योम store_planar(व्योम *dst, u32 dst_inc, u32 bpp, u32 d[8])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bpp; i++, dst += dst_inc)
		put_unaligned_be32(d[perm_c2p_32x8[i]], dst);
पूर्ण


    /*
     *  Store a partial block of planar data after c2p conversion
     */

अटल अंतरभूत व्योम store_planar_masked(व्योम *dst, u32 dst_inc, u32 bpp,
				       u32 d[8], u32 mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bpp; i++, dst += dst_inc)
		put_unaligned_be32(comp(d[perm_c2p_32x8[i]],
					get_unaligned_be32(dst), mask),
				   dst);
पूर्ण


    /*
     *  c2p_planar - Copy 8-bit chunky image data to a planar frame buffer
     *  @dst: Starting address of the planar frame buffer
     *  @dx: Horizontal destination offset (in pixels)
     *  @dy: Vertical destination offset (in pixels)
     *  @width: Image width (in pixels)
     *  @height: Image height (in pixels)
     *  @dst_nextline: Frame buffer offset to the next line (in bytes)
     *  @dst_nextplane: Frame buffer offset to the next plane (in bytes)
     *  @src_nextline: Image offset to the next line (in bytes)
     *  @bpp: Bits per pixel of the planar frame buffer (1-8)
     */

व्योम c2p_planar(व्योम *dst, स्थिर व्योम *src, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextline, u32 dst_nextplane,
		u32 src_nextline, u32 bpp)
अणु
	जोड़ अणु
		u8 pixels[32];
		u32 words[8];
	पूर्ण d;
	u32 dst_idx, first, last, w;
	स्थिर u8 *c;
	व्योम *p;

	dst += dy*dst_nextline+(dx & ~31);
	dst_idx = dx % 32;
	first = 0xffffffffU >> dst_idx;
	last = ~(0xffffffffU >> ((dst_idx+width) % 32));
	जबतक (height--) अणु
		c = src;
		p = dst;
		w = width;
		अगर (dst_idx+width <= 32) अणु
			/* Single destination word */
			first &= last;
			स_रखो(d.pixels, 0, माप(d));
			स_नकल(d.pixels+dst_idx, c, width);
			c += width;
			c2p_32x8(d.words);
			store_planar_masked(p, dst_nextplane, bpp, d.words,
					    first);
			p += 4;
		पूर्ण अन्यथा अणु
			/* Multiple destination words */
			w = width;
			/* Leading bits */
			अगर (dst_idx) अणु
				w = 32 - dst_idx;
				स_रखो(d.pixels, 0, dst_idx);
				स_नकल(d.pixels+dst_idx, c, w);
				c += w;
				c2p_32x8(d.words);
				store_planar_masked(p, dst_nextplane, bpp,
						    d.words, first);
				p += 4;
				w = width-w;
			पूर्ण
			/* Main chunk */
			जबतक (w >= 32) अणु
				स_नकल(d.pixels, c, 32);
				c += 32;
				c2p_32x8(d.words);
				store_planar(p, dst_nextplane, bpp, d.words);
				p += 4;
				w -= 32;
			पूर्ण
			/* Trailing bits */
			w %= 32;
			अगर (w > 0) अणु
				स_नकल(d.pixels, c, w);
				स_रखो(d.pixels+w, 0, 32-w);
				c2p_32x8(d.words);
				store_planar_masked(p, dst_nextplane, bpp,
						    d.words, last);
			पूर्ण
		पूर्ण
		src += src_nextline;
		dst += dst_nextline;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(c2p_planar);

MODULE_LICENSE("GPL");
