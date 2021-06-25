<शैली गुरु>
/*
 *  Generic fillrect क्रम frame buffers with packed pixels of any depth.
 *
 *      Copyright (C)  2000 James Simmons (jsimmons@linux-fbdev.org)
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 * NOTES:
 *
 *  Also need to add code to deal with cards endians that are dअगरferent than
 *  the native cpu endians. I also need to deal with MSB position in the word.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <यंत्र/types.h>
#समावेश "fb_draw.h"

#अगर BITS_PER_LONG == 32
#  define FB_WRITEL fb_ग_लिखोl
#  define FB_READL  fb_पढ़ोl
#अन्यथा
#  define FB_WRITEL fb_ग_लिखोq
#  define FB_READL  fb_पढ़ोq
#पूर्ण_अगर

    /*
     *  Aligned pattern fill using 32/64-bit memory accesses
     */

अटल व्योम
bitfill_aligned(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst, पूर्णांक dst_idx,
		अचिन्हित दीर्घ pat, अचिन्हित n, पूर्णांक bits, u32 bswapmask)
अणु
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = fb_shअगरted_pixels_mask_दीर्घ(p, dst_idx, bswapmask);
	last = ~fb_shअगरted_pixels_mask_दीर्घ(p, (dst_idx+n) % bits, bswapmask);

	अगर (dst_idx+n <= bits) अणु
		// Single word
		अगर (last)
			first &= last;
		FB_WRITEL(comp(pat, FB_READL(dst), first), dst);
	पूर्ण अन्यथा अणु
		// Multiple destination words

		// Leading bits
		अगर (first!= ~0UL) अणु
			FB_WRITEL(comp(pat, FB_READL(dst), first), dst);
			dst++;
			n -= bits - dst_idx;
		पूर्ण

		// Main chunk
		n /= bits;
		जबतक (n >= 8) अणु
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			FB_WRITEL(pat, dst++);
			n -= 8;
		पूर्ण
		जबतक (n--)
			FB_WRITEL(pat, dst++);

		// Trailing bits
		अगर (last)
			FB_WRITEL(comp(pat, FB_READL(dst), last), dst);
	पूर्ण
पूर्ण


    /*
     *  Unaligned generic pattern fill using 32/64-bit memory accesses
     *  The pattern must have been expanded to a full 32/64-bit value
     *  Left/right are the appropriate shअगरts to convert to the pattern to be
     *  used क्रम the next 32/64-bit word
     */

अटल व्योम
bitfill_unaligned(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst, पूर्णांक dst_idx,
		  अचिन्हित दीर्घ pat, पूर्णांक left, पूर्णांक right, अचिन्हित n, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		// Single word
		अगर (last)
			first &= last;
		FB_WRITEL(comp(pat, FB_READL(dst), first), dst);
	पूर्ण अन्यथा अणु
		// Multiple destination words
		// Leading bits
		अगर (first) अणु
			FB_WRITEL(comp(pat, FB_READL(dst), first), dst);
			dst++;
			pat = pat << left | pat >> right;
			n -= bits - dst_idx;
		पूर्ण

		// Main chunk
		n /= bits;
		जबतक (n >= 4) अणु
			FB_WRITEL(pat, dst++);
			pat = pat << left | pat >> right;
			FB_WRITEL(pat, dst++);
			pat = pat << left | pat >> right;
			FB_WRITEL(pat, dst++);
			pat = pat << left | pat >> right;
			FB_WRITEL(pat, dst++);
			pat = pat << left | pat >> right;
			n -= 4;
		पूर्ण
		जबतक (n--) अणु
			FB_WRITEL(pat, dst++);
			pat = pat << left | pat >> right;
		पूर्ण

		// Trailing bits
		अगर (last)
			FB_WRITEL(comp(pat, FB_READL(dst), last), dst);
	पूर्ण
पूर्ण

    /*
     *  Aligned pattern invert using 32/64-bit memory accesses
     */
अटल व्योम
bitfill_aligned_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst,
		    पूर्णांक dst_idx, अचिन्हित दीर्घ pat, अचिन्हित n, पूर्णांक bits,
		    u32 bswapmask)
अणु
	अचिन्हित दीर्घ val = pat, dat;
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = fb_shअगरted_pixels_mask_दीर्घ(p, dst_idx, bswapmask);
	last = ~fb_shअगरted_pixels_mask_दीर्घ(p, (dst_idx+n) % bits, bswapmask);

	अगर (dst_idx+n <= bits) अणु
		// Single word
		अगर (last)
			first &= last;
		dat = FB_READL(dst);
		FB_WRITEL(comp(dat ^ val, dat, first), dst);
	पूर्ण अन्यथा अणु
		// Multiple destination words
		// Leading bits
		अगर (first!=0UL) अणु
			dat = FB_READL(dst);
			FB_WRITEL(comp(dat ^ val, dat, first), dst);
			dst++;
			n -= bits - dst_idx;
		पूर्ण

		// Main chunk
		n /= bits;
		जबतक (n >= 8) अणु
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
			n -= 8;
		पूर्ण
		जबतक (n--) अणु
			FB_WRITEL(FB_READL(dst) ^ val, dst);
			dst++;
		पूर्ण
		// Trailing bits
		अगर (last) अणु
			dat = FB_READL(dst);
			FB_WRITEL(comp(dat ^ val, dat, last), dst);
		पूर्ण
	पूर्ण
पूर्ण


    /*
     *  Unaligned generic pattern invert using 32/64-bit memory accesses
     *  The pattern must have been expanded to a full 32/64-bit value
     *  Left/right are the appropriate shअगरts to convert to the pattern to be
     *  used क्रम the next 32/64-bit word
     */

अटल व्योम
bitfill_unaligned_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst,
		      पूर्णांक dst_idx, अचिन्हित दीर्घ pat, पूर्णांक left, पूर्णांक right,
		      अचिन्हित n, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ first, last, dat;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		// Single word
		अगर (last)
			first &= last;
		dat = FB_READL(dst);
		FB_WRITEL(comp(dat ^ pat, dat, first), dst);
	पूर्ण अन्यथा अणु
		// Multiple destination words

		// Leading bits
		अगर (first != 0UL) अणु
			dat = FB_READL(dst);
			FB_WRITEL(comp(dat ^ pat, dat, first), dst);
			dst++;
			pat = pat << left | pat >> right;
			n -= bits - dst_idx;
		पूर्ण

		// Main chunk
		n /= bits;
		जबतक (n >= 4) अणु
			FB_WRITEL(FB_READL(dst) ^ pat, dst);
			dst++;
			pat = pat << left | pat >> right;
			FB_WRITEL(FB_READL(dst) ^ pat, dst);
			dst++;
			pat = pat << left | pat >> right;
			FB_WRITEL(FB_READL(dst) ^ pat, dst);
			dst++;
			pat = pat << left | pat >> right;
			FB_WRITEL(FB_READL(dst) ^ pat, dst);
			dst++;
			pat = pat << left | pat >> right;
			n -= 4;
		पूर्ण
		जबतक (n--) अणु
			FB_WRITEL(FB_READL(dst) ^ pat, dst);
			dst++;
			pat = pat << left | pat >> right;
		पूर्ण

		// Trailing bits
		अगर (last) अणु
			dat = FB_READL(dst);
			FB_WRITEL(comp(dat ^ pat, dat, last), dst);
		पूर्ण
	पूर्ण
पूर्ण

व्योम cfb_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अचिन्हित दीर्घ pat, pat2, fg;
	अचिन्हित दीर्घ width = rect->width, height = rect->height;
	पूर्णांक bits = BITS_PER_LONG, bytes = bits >> 3;
	u32 bpp = p->var.bits_per_pixel;
	अचिन्हित दीर्घ __iomem *dst;
	पूर्णांक dst_idx, left;

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (p->fix.visual == FB_VISUAL_TRUECOLOR ||
	    p->fix.visual == FB_VISUAL_सूचीECTCOLOR )
		fg = ((u32 *) (p->pseuकरो_palette))[rect->color];
	अन्यथा
		fg = rect->color;

	pat = pixel_to_pat(bpp, fg);

	dst = (अचिन्हित दीर्घ __iomem *)((अचिन्हित दीर्घ)p->screen_base & ~(bytes-1));
	dst_idx = ((अचिन्हित दीर्घ)p->screen_base & (bytes - 1))*8;
	dst_idx += rect->dy*p->fix.line_length*8+rect->dx*bpp;
	/* FIXME For now we support 1-32 bpp only */
	left = bits % bpp;
	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);
	अगर (!left) अणु
		u32 bswapmask = fb_compute_bswapmask(p);
		व्योम (*fill_op32)(काष्ठा fb_info *p,
				  अचिन्हित दीर्घ __iomem *dst, पूर्णांक dst_idx,
		                  अचिन्हित दीर्घ pat, अचिन्हित n, पूर्णांक bits,
				  u32 bswapmask) = शून्य;

		चयन (rect->rop) अणु
		हाल ROP_XOR:
			fill_op32 = bitfill_aligned_rev;
			अवरोध;
		हाल ROP_COPY:
			fill_op32 = bitfill_aligned;
			अवरोध;
		शेष:
			prपूर्णांकk( KERN_ERR "cfb_fillrect(): unknown rop, defaulting to ROP_COPY\n");
			fill_op32 = bitfill_aligned;
			अवरोध;
		पूर्ण
		जबतक (height--) अणु
			dst += dst_idx >> (ffs(bits) - 1);
			dst_idx &= (bits - 1);
			fill_op32(p, dst, dst_idx, pat, width*bpp, bits,
				  bswapmask);
			dst_idx += p->fix.line_length*8;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक right, r;
		व्योम (*fill_op)(काष्ठा fb_info *p, अचिन्हित दीर्घ __iomem *dst,
				पूर्णांक dst_idx, अचिन्हित दीर्घ pat, पूर्णांक left,
				पूर्णांक right, अचिन्हित n, पूर्णांक bits) = शून्य;
#अगर_घोषित __LITTLE_ENDIAN
		right = left;
		left = bpp - right;
#अन्यथा
		right = bpp - left;
#पूर्ण_अगर
		चयन (rect->rop) अणु
		हाल ROP_XOR:
			fill_op = bitfill_unaligned_rev;
			अवरोध;
		हाल ROP_COPY:
			fill_op = bitfill_unaligned;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "cfb_fillrect(): unknown rop, defaulting to ROP_COPY\n");
			fill_op = bitfill_unaligned;
			अवरोध;
		पूर्ण
		जबतक (height--) अणु
			dst += dst_idx / bits;
			dst_idx &= (bits - 1);
			r = dst_idx % bpp;
			/* rotate pattern to the correct start position */
			pat2 = le_दीर्घ_to_cpu(rolx(cpu_to_le_दीर्घ(pat), r, bpp));
			fill_op(p, dst, dst_idx, pat2, left, right,
				width*bpp, bits);
			dst_idx += p->fix.line_length*8;
		पूर्ण
	पूर्ण
पूर्ण

EXPORT_SYMBOL(cfb_fillrect);

MODULE_AUTHOR("James Simmons <jsimmons@users.sf.net>");
MODULE_DESCRIPTION("Generic software accelerated fill rectangle");
MODULE_LICENSE("GPL");
