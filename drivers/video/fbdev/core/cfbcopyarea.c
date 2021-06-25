<शैली गुरु>
/*
 *  Generic function क्रम frame buffer with packed pixels of any depth.
 *
 *      Copyright (C)  1999-2005 James Simmons <jsimmons@www.infradead.org>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 * NOTES:
 *
 *  This is क्रम cfb packed pixels. Iplan and such are incorporated in the
 *  drivers that need them.
 *
 *  FIXME
 *
 *  Also need to add code to deal with cards endians that are dअगरferent than
 *  the native cpu endians. I also need to deal with MSB position in the word.
 *
 *  The two functions or copying क्रमward and backward could be split up like
 *  the ones क्रम filling, i.e. in aligned and unaligned versions. This would
 *  help moving some redundant computations and branches out of the loop, too.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/पन.स>
#समावेश "fb_draw.h"

#अगर BITS_PER_LONG == 32
#  define FB_WRITEL fb_ग_लिखोl
#  define FB_READL  fb_पढ़ोl
#अन्यथा
#  define FB_WRITEL fb_ग_लिखोq
#  define FB_READL  fb_पढ़ोq
#पूर्ण_अगर

    /*
     *  Generic bitwise copy algorithm
     */

अटल व्योम
bitcpy(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst, अचिन्हित dst_idx,
		स्थिर अचिन्हित दीर्घ __iomem *src, अचिन्हित src_idx, पूर्णांक bits,
		अचिन्हित n, u32 bswapmask)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक स्थिर shअगरt = dst_idx-src_idx;

#अगर 0
	/*
	 * If you suspect bug in this function, compare it with this simple
	 * स_हटाओ implementation.
	 */
	स_हटाओ((अक्षर *)dst + ((dst_idx & (bits - 1))) / 8,
		(अक्षर *)src + ((src_idx & (bits - 1))) / 8, n / 8);
	वापस;
#पूर्ण_अगर

	first = fb_shअगरted_pixels_mask_दीर्घ(p, dst_idx, bswapmask);
	last = ~fb_shअगरted_pixels_mask_दीर्घ(p, (dst_idx+n) % bits, bswapmask);

	अगर (!shअगरt) अणु
		// Same alignment क्रम source and dest

		अगर (dst_idx+n <= bits) अणु
			// Single word
			अगर (last)
				first &= last;
			FB_WRITEL( comp( FB_READL(src), FB_READL(dst), first), dst);
		पूर्ण अन्यथा अणु
			// Multiple destination words

			// Leading bits
			अगर (first != ~0UL) अणु
				FB_WRITEL( comp( FB_READL(src), FB_READL(dst), first), dst);
				dst++;
				src++;
				n -= bits - dst_idx;
			पूर्ण

			// Main chunk
			n /= bits;
			जबतक (n >= 8) अणु
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				FB_WRITEL(FB_READL(src++), dst++);
				n -= 8;
			पूर्ण
			जबतक (n--)
				FB_WRITEL(FB_READL(src++), dst++);

			// Trailing bits
			अगर (last)
				FB_WRITEL( comp( FB_READL(src), FB_READL(dst), last), dst);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Dअगरferent alignment क्रम source and dest */
		अचिन्हित दीर्घ d0, d1;
		पूर्णांक m;

		पूर्णांक स्थिर left = shअगरt & (bits - 1);
		पूर्णांक स्थिर right = -shअगरt & (bits - 1);

		अगर (dst_idx+n <= bits) अणु
			// Single destination word
			अगर (last)
				first &= last;
			d0 = FB_READL(src);
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			अगर (shअगरt > 0) अणु
				// Single source word
				d0 <<= left;
			पूर्ण अन्यथा अगर (src_idx+n <= bits) अणु
				// Single source word
				d0 >>= right;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = FB_READL(src + 1);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);
				d0 = d0 >> right | d1 << left;
			पूर्ण
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			FB_WRITEL(comp(d0, FB_READL(dst), first), dst);
		पूर्ण अन्यथा अणु
			// Multiple destination words
			/** We must always remember the last value पढ़ो, because in हाल
			SRC and DST overlap bitwise (e.g. when moving just one pixel in
			1bpp), we always collect one full दीर्घ क्रम DST and that might
			overlap with the current दीर्घ from SRC. We store this value in
			'd0'. */
			d0 = FB_READL(src++);
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			// Leading bits
			अगर (shअगरt > 0) अणु
				// Single source word
				d1 = d0;
				d0 <<= left;
				n -= bits - dst_idx;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = FB_READL(src++);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);

				d0 = d0 >> right | d1 << left;
				n -= bits - dst_idx;
			पूर्ण
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			FB_WRITEL(comp(d0, FB_READL(dst), first), dst);
			d0 = d1;
			dst++;

			// Main chunk
			m = n % bits;
			n /= bits;
			जबतक ((n >= 4) && !bswapmask) अणु
				d1 = FB_READL(src++);
				FB_WRITEL(d0 >> right | d1 << left, dst++);
				d0 = d1;
				d1 = FB_READL(src++);
				FB_WRITEL(d0 >> right | d1 << left, dst++);
				d0 = d1;
				d1 = FB_READL(src++);
				FB_WRITEL(d0 >> right | d1 << left, dst++);
				d0 = d1;
				d1 = FB_READL(src++);
				FB_WRITEL(d0 >> right | d1 << left, dst++);
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = FB_READL(src++);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);
				d0 = d0 >> right | d1 << left;
				d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
				FB_WRITEL(d0, dst++);
				d0 = d1;
			पूर्ण

			// Trailing bits
			अगर (m) अणु
				अगर (m <= bits - right) अणु
					// Single source word
					d0 >>= right;
				पूर्ण अन्यथा अणु
					// 2 source words
					d1 = FB_READL(src);
					d1 = fb_rev_pixels_in_दीर्घ(d1,
								bswapmask);
					d0 = d0 >> right | d1 << left;
				पूर्ण
				d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
				FB_WRITEL(comp(d0, FB_READL(dst), last), dst);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

    /*
     *  Generic bitwise copy algorithm, operating backward
     */

अटल व्योम
bitcpy_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst, अचिन्हित dst_idx,
		स्थिर अचिन्हित दीर्घ __iomem *src, अचिन्हित src_idx, पूर्णांक bits,
		अचिन्हित n, u32 bswapmask)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक shअगरt;

#अगर 0
	/*
	 * If you suspect bug in this function, compare it with this simple
	 * स_हटाओ implementation.
	 */
	स_हटाओ((अक्षर *)dst + ((dst_idx & (bits - 1))) / 8,
		(अक्षर *)src + ((src_idx & (bits - 1))) / 8, n / 8);
	वापस;
#पूर्ण_अगर

	dst += (dst_idx + n - 1) / bits;
	src += (src_idx + n - 1) / bits;
	dst_idx = (dst_idx + n - 1) % bits;
	src_idx = (src_idx + n - 1) % bits;

	shअगरt = dst_idx-src_idx;

	first = ~fb_shअगरted_pixels_mask_दीर्घ(p, (dst_idx + 1) % bits, bswapmask);
	last = fb_shअगरted_pixels_mask_दीर्घ(p, (bits + dst_idx + 1 - n) % bits, bswapmask);

	अगर (!shअगरt) अणु
		// Same alignment क्रम source and dest

		अगर ((अचिन्हित दीर्घ)dst_idx+1 >= n) अणु
			// Single word
			अगर (first)
				last &= first;
			FB_WRITEL( comp( FB_READL(src), FB_READL(dst), last), dst);
		पूर्ण अन्यथा अणु
			// Multiple destination words

			// Leading bits
			अगर (first) अणु
				FB_WRITEL( comp( FB_READL(src), FB_READL(dst), first), dst);
				dst--;
				src--;
				n -= dst_idx+1;
			पूर्ण

			// Main chunk
			n /= bits;
			जबतक (n >= 8) अणु
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				FB_WRITEL(FB_READL(src--), dst--);
				n -= 8;
			पूर्ण
			जबतक (n--)
				FB_WRITEL(FB_READL(src--), dst--);

			// Trailing bits
			अगर (last != -1UL)
				FB_WRITEL( comp( FB_READL(src), FB_READL(dst), last), dst);
		पूर्ण
	पूर्ण अन्यथा अणु
		// Dअगरferent alignment क्रम source and dest
		अचिन्हित दीर्घ d0, d1;
		पूर्णांक m;

		पूर्णांक स्थिर left = shअगरt & (bits-1);
		पूर्णांक स्थिर right = -shअगरt & (bits-1);

		अगर ((अचिन्हित दीर्घ)dst_idx+1 >= n) अणु
			// Single destination word
			अगर (first)
				last &= first;
			d0 = FB_READL(src);
			अगर (shअगरt < 0) अणु
				// Single source word
				d0 >>= right;
			पूर्ण अन्यथा अगर (1+(अचिन्हित दीर्घ)src_idx >= n) अणु
				// Single source word
				d0 <<= left;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = FB_READL(src - 1);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);
				d0 = d0 << left | d1 >> right;
			पूर्ण
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			FB_WRITEL(comp(d0, FB_READL(dst), last), dst);
		पूर्ण अन्यथा अणु
			// Multiple destination words
			/** We must always remember the last value पढ़ो, because in हाल
			SRC and DST overlap bitwise (e.g. when moving just one pixel in
			1bpp), we always collect one full दीर्घ क्रम DST and that might
			overlap with the current दीर्घ from SRC. We store this value in
			'd0'. */

			d0 = FB_READL(src--);
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			// Leading bits
			अगर (shअगरt < 0) अणु
				// Single source word
				d1 = d0;
				d0 >>= right;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = FB_READL(src--);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);
				d0 = d0 << left | d1 >> right;
			पूर्ण
			d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
			अगर (!first)
				FB_WRITEL(d0, dst);
			अन्यथा
				FB_WRITEL(comp(d0, FB_READL(dst), first), dst);
			d0 = d1;
			dst--;
			n -= dst_idx+1;

			// Main chunk
			m = n % bits;
			n /= bits;
			जबतक ((n >= 4) && !bswapmask) अणु
				d1 = FB_READL(src--);
				FB_WRITEL(d0 << left | d1 >> right, dst--);
				d0 = d1;
				d1 = FB_READL(src--);
				FB_WRITEL(d0 << left | d1 >> right, dst--);
				d0 = d1;
				d1 = FB_READL(src--);
				FB_WRITEL(d0 << left | d1 >> right, dst--);
				d0 = d1;
				d1 = FB_READL(src--);
				FB_WRITEL(d0 << left | d1 >> right, dst--);
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = FB_READL(src--);
				d1 = fb_rev_pixels_in_दीर्घ(d1, bswapmask);
				d0 = d0 << left | d1 >> right;
				d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
				FB_WRITEL(d0, dst--);
				d0 = d1;
			पूर्ण

			// Trailing bits
			अगर (m) अणु
				अगर (m <= bits - left) अणु
					// Single source word
					d0 <<= left;
				पूर्ण अन्यथा अणु
					// 2 source words
					d1 = FB_READL(src);
					d1 = fb_rev_pixels_in_दीर्घ(d1,
								bswapmask);
					d0 = d0 << left | d1 >> right;
				पूर्ण
				d0 = fb_rev_pixels_in_दीर्घ(d0, bswapmask);
				FB_WRITEL(comp(d0, FB_READL(dst), last), dst);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम cfb_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 dx = area->dx, dy = area->dy, sx = area->sx, sy = area->sy;
	u32 height = area->height, width = area->width;
	अचिन्हित दीर्घ स्थिर bits_per_line = p->fix.line_length*8u;
	अचिन्हित दीर्घ __iomem *base = शून्य;
	पूर्णांक bits = BITS_PER_LONG, bytes = bits >> 3;
	अचिन्हित dst_idx = 0, src_idx = 0, rev_copy = 0;
	u32 bswapmask = fb_compute_bswapmask(p);

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	/* अगर the beginning of the target area might overlap with the end of
	the source area, be have to copy the area reverse. */
	अगर ((dy == sy && dx > sx) || (dy > sy)) अणु
		dy += height;
		sy += height;
		rev_copy = 1;
	पूर्ण

	// split the base of the framebuffer पूर्णांकo a दीर्घ-aligned address and the
	// index of the first bit
	base = (अचिन्हित दीर्घ __iomem *)((अचिन्हित दीर्घ)p->screen_base & ~(bytes-1));
	dst_idx = src_idx = 8*((अचिन्हित दीर्घ)p->screen_base & (bytes-1));
	// add offset of source and target area
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
				width*p->var.bits_per_pixel, bswapmask);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (height--) अणु
			bitcpy(p, base + (dst_idx / bits), dst_idx % bits,
				base + (src_idx / bits), src_idx % bits, bits,
				width*p->var.bits_per_pixel, bswapmask);
			dst_idx += bits_per_line;
			src_idx += bits_per_line;
		पूर्ण
	पूर्ण
पूर्ण

EXPORT_SYMBOL(cfb_copyarea);

MODULE_AUTHOR("James Simmons <jsimmons@users.sf.net>");
MODULE_DESCRIPTION("Generic software accelerated copyarea");
MODULE_LICENSE("GPL");

