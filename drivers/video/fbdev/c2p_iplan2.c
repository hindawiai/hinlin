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
     *  Perक्रमm a full C2P step on 16 8-bit pixels, stored in 4 32-bit words
     *  containing
     *    - 16 8-bit chunky pixels on input
     *    - permutated planar data (2 planes per 32-bit word) on output
     */

अटल व्योम c2p_16x8(u32 d[4])
अणु
	transp4(d, 8, 2);
	transp4(d, 1, 2);
	transp4x(d, 16, 2);
	transp4x(d, 2, 2);
	transp4(d, 4, 1);
पूर्ण


    /*
     *  Array containing the permutation indices of the planar data after c2p
     */

अटल स्थिर पूर्णांक perm_c2p_16x8[4] = अणु 1, 3, 0, 2 पूर्ण;


    /*
     *  Store a full block of iplan2 data after c2p conversion
     */

अटल अंतरभूत व्योम store_iplan2(व्योम *dst, u32 bpp, u32 d[4])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bpp/2; i++, dst += 4)
		put_unaligned_be32(d[perm_c2p_16x8[i]], dst);
पूर्ण


    /*
     *  Store a partial block of iplan2 data after c2p conversion
     */

अटल अंतरभूत व्योम store_iplan2_masked(व्योम *dst, u32 bpp, u32 d[4], u32 mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bpp/2; i++, dst += 4)
		put_unaligned_be32(comp(d[perm_c2p_16x8[i]],
					get_unaligned_be32(dst), mask),
				   dst);
पूर्ण


    /*
     *  c2p_iplan2 - Copy 8-bit chunky image data to an पूर्णांकerleaved planar
     *  frame buffer with 2 bytes of पूर्णांकerleave
     *  @dst: Starting address of the planar frame buffer
     *  @dx: Horizontal destination offset (in pixels)
     *  @dy: Vertical destination offset (in pixels)
     *  @width: Image width (in pixels)
     *  @height: Image height (in pixels)
     *  @dst_nextline: Frame buffer offset to the next line (in bytes)
     *  @src_nextline: Image offset to the next line (in bytes)
     *  @bpp: Bits per pixel of the planar frame buffer (2, 4, or 8)
     */

व्योम c2p_iplan2(व्योम *dst, स्थिर व्योम *src, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextline, u32 src_nextline, u32 bpp)
अणु
	जोड़ अणु
		u8 pixels[16];
		u32 words[4];
	पूर्ण d;
	u32 dst_idx, first, last, w;
	स्थिर u8 *c;
	व्योम *p;

	dst += dy*dst_nextline+(dx & ~15)*bpp;
	dst_idx = dx % 16;
	first = 0xffffU >> dst_idx;
	first |= first << 16;
	last = 0xffffU ^ (0xffffU >> ((dst_idx+width) % 16));
	last |= last << 16;
	जबतक (height--) अणु
		c = src;
		p = dst;
		w = width;
		अगर (dst_idx+width <= 16) अणु
			/* Single destination word */
			first &= last;
			स_रखो(d.pixels, 0, माप(d));
			स_नकल(d.pixels+dst_idx, c, width);
			c += width;
			c2p_16x8(d.words);
			store_iplan2_masked(p, bpp, d.words, first);
			p += bpp*2;
		पूर्ण अन्यथा अणु
			/* Multiple destination words */
			w = width;
			/* Leading bits */
			अगर (dst_idx) अणु
				w = 16 - dst_idx;
				स_रखो(d.pixels, 0, dst_idx);
				स_नकल(d.pixels+dst_idx, c, w);
				c += w;
				c2p_16x8(d.words);
				store_iplan2_masked(p, bpp, d.words, first);
				p += bpp*2;
				w = width-w;
			पूर्ण
			/* Main chunk */
			जबतक (w >= 16) अणु
				स_नकल(d.pixels, c, 16);
				c += 16;
				c2p_16x8(d.words);
				store_iplan2(p, bpp, d.words);
				p += bpp*2;
				w -= 16;
			पूर्ण
			/* Trailing bits */
			w %= 16;
			अगर (w > 0) अणु
				स_नकल(d.pixels, c, w);
				स_रखो(d.pixels+w, 0, 16-w);
				c2p_16x8(d.words);
				store_iplan2_masked(p, bpp, d.words, last);
			पूर्ण
		पूर्ण
		src += src_nextline;
		dst += dst_nextline;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(c2p_iplan2);

MODULE_LICENSE("GPL");
