<शैली गुरु>
/*
 *  Generic Bit Block Transfer क्रम frame buffers located in प्रणाली RAM with
 *  packed pixels of any depth.
 *
 *  Based almost entirely from cfbcopyarea.c (which is based almost entirely
 *  on Geert Uytterhoeven's copyarea routine)
 *
 *      Copyright (C)  2007 Antonino Daplas <adaplas@pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/पन.स>
#समावेश "fb_draw.h"

    /*
     *  Generic bitwise copy algorithm
     */

अटल व्योम
bitcpy(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, अचिन्हित dst_idx,
	स्थिर अचिन्हित दीर्घ *src, अचिन्हित src_idx, पूर्णांक bits, अचिन्हित n)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक स्थिर shअगरt = dst_idx-src_idx;
	पूर्णांक left, right;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (!shअगरt) अणु
		/* Same alignment क्रम source and dest */
		अगर (dst_idx+n <= bits) अणु
			/* Single word */
			अगर (last)
				first &= last;
			*dst = comp(*src, *dst, first);
		पूर्ण अन्यथा अणु
			/* Multiple destination words */
			/* Leading bits */
 			अगर (first != ~0UL) अणु
				*dst = comp(*src, *dst, first);
				dst++;
				src++;
				n -= bits - dst_idx;
			पूर्ण

			/* Main chunk */
			n /= bits;
			जबतक (n >= 8) अणु
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				n -= 8;
			पूर्ण
			जबतक (n--)
				*dst++ = *src++;

			/* Trailing bits */
			अगर (last)
				*dst = comp(*src, *dst, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ d0, d1;
		पूर्णांक m;

		/* Dअगरferent alignment क्रम source and dest */
		right = shअगरt & (bits - 1);
		left = -shअगरt & (bits - 1);

		अगर (dst_idx+n <= bits) अणु
			/* Single destination word */
			अगर (last)
				first &= last;
			अगर (shअगरt > 0) अणु
				/* Single source word */
				*dst = comp(*src << left, *dst, first);
			पूर्ण अन्यथा अगर (src_idx+n <= bits) अणु
				/* Single source word */
				*dst = comp(*src >> right, *dst, first);
			पूर्ण अन्यथा अणु
				/* 2 source words */
				d0 = *src++;
				d1 = *src;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Multiple destination words */
			/** We must always remember the last value पढ़ो,
			    because in हाल SRC and DST overlap bitwise (e.g.
			    when moving just one pixel in 1bpp), we always
			    collect one full दीर्घ क्रम DST and that might
			    overlap with the current दीर्घ from SRC. We store
			    this value in 'd0'. */
			d0 = *src++;
			/* Leading bits */
			अगर (shअगरt > 0) अणु
				/* Single source word */
				*dst = comp(d0 << left, *dst, first);
				dst++;
				n -= bits - dst_idx;
			पूर्ण अन्यथा अणु
				/* 2 source words */
				d1 = *src++;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
				d0 = d1;
				dst++;
				n -= bits - dst_idx;
			पूर्ण

			/* Main chunk */
			m = n % bits;
			n /= bits;
			जबतक (n >= 4) अणु
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = *src++;
				*dst++ = d0 >> right | d1 << left;
				d0 = d1;
			पूर्ण

			/* Trailing bits */
			अगर (m) अणु
				अगर (m <= bits - right) अणु
					/* Single source word */
					d0 >>= right;
				पूर्ण अन्यथा अणु
					/* 2 source words */
 					d1 = *src;
					d0 = d0 >> right | d1 << left;
				पूर्ण
				*dst = comp(d0, *dst, last);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

    /*
     *  Generic bitwise copy algorithm, operating backward
     */

अटल व्योम
bitcpy_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, अचिन्हित dst_idx,
	   स्थिर अचिन्हित दीर्घ *src, अचिन्हित src_idx, अचिन्हित bits,
	   अचिन्हित n)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक shअगरt;

	dst += (dst_idx + n - 1) / bits;
	src += (src_idx + n - 1) / bits;
	dst_idx = (dst_idx + n - 1) % bits;
	src_idx = (src_idx + n - 1) % bits;

	shअगरt = dst_idx-src_idx;

	first = ~FB_SHIFT_HIGH(p, ~0UL, (dst_idx + 1) % bits);
	last = FB_SHIFT_HIGH(p, ~0UL, (bits + dst_idx + 1 - n) % bits);

	अगर (!shअगरt) अणु
		/* Same alignment क्रम source and dest */
		अगर ((अचिन्हित दीर्घ)dst_idx+1 >= n) अणु
			/* Single word */
			अगर (first)
				last &= first;
			*dst = comp(*src, *dst, last);
		पूर्ण अन्यथा अणु
			/* Multiple destination words */

			/* Leading bits */
			अगर (first) अणु
				*dst = comp(*src, *dst, first);
				dst--;
				src--;
				n -= dst_idx+1;
			पूर्ण

			/* Main chunk */
			n /= bits;
			जबतक (n >= 8) अणु
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				n -= 8;
			पूर्ण
			जबतक (n--)
				*dst-- = *src--;
			/* Trailing bits */
			अगर (last != -1UL)
				*dst = comp(*src, *dst, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Dअगरferent alignment क्रम source and dest */

		पूर्णांक स्थिर left = shअगरt & (bits-1);
		पूर्णांक स्थिर right = -shअगरt & (bits-1);

		अगर ((अचिन्हित दीर्घ)dst_idx+1 >= n) अणु
			/* Single destination word */
			अगर (first)
				last &= first;
			अगर (shअगरt < 0) अणु
				/* Single source word */
				*dst = comp(*src >> right, *dst, last);
			पूर्ण अन्यथा अगर (1+(अचिन्हित दीर्घ)src_idx >= n) अणु
				/* Single source word */
				*dst = comp(*src << left, *dst, last);
			पूर्ण अन्यथा अणु
				/* 2 source words */
				*dst = comp(*src << left | *(src-1) >> right,
					    *dst, last);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Multiple destination words */
			/** We must always remember the last value पढ़ो,
			    because in हाल SRC and DST overlap bitwise (e.g.
			    when moving just one pixel in 1bpp), we always
			    collect one full दीर्घ क्रम DST and that might
			    overlap with the current दीर्घ from SRC. We store
			    this value in 'd0'. */
			अचिन्हित दीर्घ d0, d1;
			पूर्णांक m;

			d0 = *src--;
			/* Leading bits */
			अगर (shअगरt < 0) अणु
				/* Single source word */
				d1 = d0;
				d0 >>= right;
			पूर्ण अन्यथा अणु
				/* 2 source words */
				d1 = *src--;
				d0 = d0 << left | d1 >> right;
			पूर्ण
			अगर (!first)
				*dst = d0;
			अन्यथा
				*dst = comp(d0, *dst, first);
			d0 = d1;
			dst--;
			n -= dst_idx+1;

			/* Main chunk */
			m = n % bits;
			n /= bits;
			जबतक (n >= 4) अणु
				d1 = *src--;
				*dst-- = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 << left | d1 >> right;
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = *src--;
				*dst-- = d0 << left | d1 >> right;
				d0 = d1;
			पूर्ण

			/* Trailing bits */
			अगर (m) अणु
				अगर (m <= bits - left) अणु
					/* Single source word */
					d0 <<= left;
				पूर्ण अन्यथा अणु
					/* 2 source words */
					d1 = *src;
					d0 = d0 << left | d1 >> right;
				पूर्ण
				*dst = comp(d0, *dst, last);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम sys_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 dx = area->dx, dy = area->dy, sx = area->sx, sy = area->sy;
	u32 height = area->height, width = area->width;
	अचिन्हित दीर्घ स्थिर bits_per_line = p->fix.line_length*8u;
	अचिन्हित दीर्घ *base = शून्य;
	पूर्णांक bits = BITS_PER_LONG, bytes = bits >> 3;
	अचिन्हित dst_idx = 0, src_idx = 0, rev_copy = 0;

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	/* अगर the beginning of the target area might overlap with the end of
	the source area, be have to copy the area reverse. */
	अगर ((dy == sy && dx > sx) || (dy > sy)) अणु
		dy += height;
		sy += height;
		rev_copy = 1;
	पूर्ण

	/* split the base of the framebuffer पूर्णांकo a दीर्घ-aligned address and
	   the index of the first bit */
	base = (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)p->screen_base & ~(bytes-1));
	dst_idx = src_idx = 8*((अचिन्हित दीर्घ)p->screen_base & (bytes-1));
	/* add offset of source and target area */
	dst_idx += dy*bits_per_line + dx*p->var.bits_per_pixel;
	src_idx += sy*bits_per_line + sx*p->var.bits_per_pixel;

	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	अगर (rev_copy) अणु
		जबतक (height--) अणु
			dst_idx -= bits_per_line;
			src_idx -= bits_per_line;
			bitcpy_rev(p, base + (dst_idx / bits), dst_idx % bits,
				base + (src_idx / bits), src_idx % bits, bits,
				width*p->var.bits_per_pixel);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (height--) अणु
			bitcpy(p, base + (dst_idx / bits), dst_idx % bits,
				base + (src_idx / bits), src_idx % bits, bits,
				width*p->var.bits_per_pixel);
			dst_idx += bits_per_line;
			src_idx += bits_per_line;
		पूर्ण
	पूर्ण
पूर्ण

EXPORT_SYMBOL(sys_copyarea);

MODULE_AUTHOR("Antonino Daplas <adaplas@pol.net>");
MODULE_DESCRIPTION("Generic copyarea (sys-to-sys)");
MODULE_LICENSE("GPL");

