<शैली गुरु>
/*
 *  Generic fillrect क्रम frame buffers in प्रणाली RAM with packed pixels of
 *  any depth.
 *
 *  Based almost entirely from cfbfillrect.c (which is based almost entirely
 *  on Geert Uytterhoeven's fillrect routine)
 *
 *      Copyright (C)  2007 Antonino Daplas <adaplas@pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <यंत्र/types.h>
#समावेश "fb_draw.h"

    /*
     *  Aligned pattern fill using 32/64-bit memory accesses
     */

अटल व्योम
bitfill_aligned(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		अचिन्हित दीर्घ pat, अचिन्हित n, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		/* Single word */
		अगर (last)
			first &= last;
		*dst = comp(pat, *dst, first);
	पूर्ण अन्यथा अणु
		/* Multiple destination words */

		/* Leading bits */
 		अगर (first!= ~0UL) अणु
			*dst = comp(pat, *dst, first);
			dst++;
			n -= bits - dst_idx;
		पूर्ण

		/* Main chunk */
		n /= bits;
		जबतक (n >= 8) अणु
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			*dst++ = pat;
			n -= 8;
		पूर्ण
		जबतक (n--)
			*dst++ = pat;
		/* Trailing bits */
		अगर (last)
			*dst = comp(pat, *dst, last);
	पूर्ण
पूर्ण


    /*
     *  Unaligned generic pattern fill using 32/64-bit memory accesses
     *  The pattern must have been expanded to a full 32/64-bit value
     *  Left/right are the appropriate shअगरts to convert to the pattern to be
     *  used क्रम the next 32/64-bit word
     */

अटल व्योम
bitfill_unaligned(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		  अचिन्हित दीर्घ pat, पूर्णांक left, पूर्णांक right, अचिन्हित n, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		/* Single word */
		अगर (last)
			first &= last;
		*dst = comp(pat, *dst, first);
	पूर्ण अन्यथा अणु
		/* Multiple destination words */
		/* Leading bits */
		अगर (first) अणु
			*dst = comp(pat, *dst, first);
			dst++;
			pat = pat << left | pat >> right;
			n -= bits - dst_idx;
		पूर्ण

		/* Main chunk */
		n /= bits;
		जबतक (n >= 4) अणु
			*dst++ = pat;
			pat = pat << left | pat >> right;
			*dst++ = pat;
			pat = pat << left | pat >> right;
			*dst++ = pat;
			pat = pat << left | pat >> right;
			*dst++ = pat;
			pat = pat << left | pat >> right;
			n -= 4;
		पूर्ण
		जबतक (n--) अणु
			*dst++ = pat;
			pat = pat << left | pat >> right;
		पूर्ण

		/* Trailing bits */
		अगर (last)
			*dst = comp(pat, *dst, last);
	पूर्ण
पूर्ण

    /*
     *  Aligned pattern invert using 32/64-bit memory accesses
     */
अटल व्योम
bitfill_aligned_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		    अचिन्हित दीर्घ pat, अचिन्हित n, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ val = pat;
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		/* Single word */
		अगर (last)
			first &= last;
		*dst = comp(*dst ^ val, *dst, first);
	पूर्ण अन्यथा अणु
		/* Multiple destination words */
		/* Leading bits */
		अगर (first!=0UL) अणु
			*dst = comp(*dst ^ val, *dst, first);
			dst++;
			n -= bits - dst_idx;
		पूर्ण

		/* Main chunk */
		n /= bits;
		जबतक (n >= 8) अणु
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			n -= 8;
		पूर्ण
		जबतक (n--)
			*dst++ ^= val;
		/* Trailing bits */
		अगर (last)
			*dst = comp(*dst ^ val, *dst, last);
	पूर्ण
पूर्ण


    /*
     *  Unaligned generic pattern invert using 32/64-bit memory accesses
     *  The pattern must have been expanded to a full 32/64-bit value
     *  Left/right are the appropriate shअगरts to convert to the pattern to be
     *  used क्रम the next 32/64-bit word
     */

अटल व्योम
bitfill_unaligned_rev(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		      अचिन्हित दीर्घ pat, पूर्णांक left, पूर्णांक right, अचिन्हित n,
		      पूर्णांक bits)
अणु
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	अगर (dst_idx+n <= bits) अणु
		/* Single word */
		अगर (last)
			first &= last;
		*dst = comp(*dst ^ pat, *dst, first);
	पूर्ण अन्यथा अणु
		/* Multiple destination words */

		/* Leading bits */
		अगर (first != 0UL) अणु
			*dst = comp(*dst ^ pat, *dst, first);
			dst++;
			pat = pat << left | pat >> right;
			n -= bits - dst_idx;
		पूर्ण

		/* Main chunk */
		n /= bits;
		जबतक (n >= 4) अणु
			*dst++ ^= pat;
			pat = pat << left | pat >> right;
			*dst++ ^= pat;
			pat = pat << left | pat >> right;
			*dst++ ^= pat;
			pat = pat << left | pat >> right;
			*dst++ ^= pat;
			pat = pat << left | pat >> right;
			n -= 4;
		पूर्ण
		जबतक (n--) अणु
			*dst ^= pat;
			pat = pat << left | pat >> right;
		पूर्ण

		/* Trailing bits */
		अगर (last)
			*dst = comp(*dst ^ pat, *dst, last);
	पूर्ण
पूर्ण

व्योम sys_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अचिन्हित दीर्घ pat, pat2, fg;
	अचिन्हित दीर्घ width = rect->width, height = rect->height;
	पूर्णांक bits = BITS_PER_LONG, bytes = bits >> 3;
	u32 bpp = p->var.bits_per_pixel;
	अचिन्हित दीर्घ *dst;
	पूर्णांक dst_idx, left;

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (p->fix.visual == FB_VISUAL_TRUECOLOR ||
	    p->fix.visual == FB_VISUAL_सूचीECTCOLOR )
		fg = ((u32 *) (p->pseuकरो_palette))[rect->color];
	अन्यथा
		fg = rect->color;

	pat = pixel_to_pat( bpp, fg);

	dst = (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)p->screen_base & ~(bytes-1));
	dst_idx = ((अचिन्हित दीर्घ)p->screen_base & (bytes - 1))*8;
	dst_idx += rect->dy*p->fix.line_length*8+rect->dx*bpp;
	/* FIXME For now we support 1-32 bpp only */
	left = bits % bpp;
	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);
	अगर (!left) अणु
		व्योम (*fill_op32)(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst,
				  पूर्णांक dst_idx, अचिन्हित दीर्घ pat, अचिन्हित n,
				  पूर्णांक bits) = शून्य;

		चयन (rect->rop) अणु
		हाल ROP_XOR:
			fill_op32 = bitfill_aligned_rev;
			अवरोध;
		हाल ROP_COPY:
			fill_op32 = bitfill_aligned;
			अवरोध;
		शेष:
			prपूर्णांकk( KERN_ERR "cfb_fillrect(): unknown rop, "
				"defaulting to ROP_COPY\n");
			fill_op32 = bitfill_aligned;
			अवरोध;
		पूर्ण
		जबतक (height--) अणु
			dst += dst_idx >> (ffs(bits) - 1);
			dst_idx &= (bits - 1);
			fill_op32(p, dst, dst_idx, pat, width*bpp, bits);
			dst_idx += p->fix.line_length*8;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक right, r;
		व्योम (*fill_op)(काष्ठा fb_info *p, अचिन्हित दीर्घ *dst,
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
			prपूर्णांकk(KERN_ERR "sys_fillrect(): unknown rop, "
				"defaulting to ROP_COPY\n");
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

EXPORT_SYMBOL(sys_fillrect);

MODULE_AUTHOR("Antonino Daplas <adaplas@pol.net>");
MODULE_DESCRIPTION("Generic fill rectangle (sys-to-sys)");
MODULE_LICENSE("GPL");
