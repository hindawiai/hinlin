<शैली गुरु>
/*
 *  Generic BitBLT function क्रम frame buffer with packed pixels of any depth.
 *
 *      Copyright (C)  June 1999 James Simmons
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 * NOTES:
 *
 *    This function copys a image from प्रणाली memory to video memory. The
 *  image can be a biपंचांगap where each 0 represents the background color and
 *  each 1 represents the क्रमeground color. Great क्रम font handling. It can
 *  also be a color image. This is determined by image_depth. The color image
 *  must be laid out exactly in the same क्रमmat as the framebuffer. Yes I know
 *  their are cards with hardware that coverts images of various depths to the
 *  framebuffer depth. But not every card has this. All images must be rounded
 *  up to the nearest byte. For example a biपंचांगap 12 bits wide must be two 
 *  bytes width. 
 *
 *  Tony: 
 *  Incorporate mask tables similar to fbcon-cfb*.c in 2.4 API.  This speeds 
 *  up the code signअगरicantly.
 *  
 *  Code क्रम depths not multiples of BITS_PER_LONG is still kludgy, which is
 *  still processed a bit at a समय.   
 *
 *  Also need to add code to deal with cards endians that are dअगरferent than
 *  the native cpu endians. I also need to deal with MSB position in the word.
 */
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <यंत्र/types.h>
#समावेश "fb_draw.h"

#घोषणा DEBUG

#अगर_घोषित DEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(KERN_DEBUG "%s: " fmt,__func__,## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#पूर्ण_अगर

अटल स्थिर u32 cfb_tab8_be[] = अणु
    0x00000000,0x000000ff,0x0000ff00,0x0000ffff,
    0x00ff0000,0x00ff00ff,0x00ffff00,0x00ffffff,
    0xff000000,0xff0000ff,0xff00ff00,0xff00ffff,
    0xffff0000,0xffff00ff,0xffffff00,0xffffffff
पूर्ण;

अटल स्थिर u32 cfb_tab8_le[] = अणु
    0x00000000,0xff000000,0x00ff0000,0xffff0000,
    0x0000ff00,0xff00ff00,0x00ffff00,0xffffff00,
    0x000000ff,0xff0000ff,0x00ff00ff,0xffff00ff,
    0x0000ffff,0xff00ffff,0x00ffffff,0xffffffff
पूर्ण;

अटल स्थिर u32 cfb_tab16_be[] = अणु
    0x00000000, 0x0000ffff, 0xffff0000, 0xffffffff
पूर्ण;

अटल स्थिर u32 cfb_tab16_le[] = अणु
    0x00000000, 0xffff0000, 0x0000ffff, 0xffffffff
पूर्ण;

अटल स्थिर u32 cfb_tab32[] = अणु
	0x00000000, 0xffffffff
पूर्ण;

#घोषणा FB_WRITEL fb_ग_लिखोl
#घोषणा FB_READL  fb_पढ़ोl

अटल अंतरभूत व्योम color_imageblit(स्थिर काष्ठा fb_image *image, 
				   काष्ठा fb_info *p, u8 __iomem *dst1, 
				   u32 start_index,
				   u32 pitch_index)
अणु
	/* Draw the penguin */
	u32 __iomem *dst, *dst2;
	u32 color = 0, val, shअगरt;
	पूर्णांक i, n, bpp = p->var.bits_per_pixel;
	u32 null_bits = 32 - bpp;
	u32 *palette = (u32 *) p->pseuकरो_palette;
	स्थिर u8 *src = image->data;
	u32 bswapmask = fb_compute_bswapmask(p);

	dst2 = (u32 __iomem *) dst1;
	क्रम (i = image->height; i--; ) अणु
		n = image->width;
		dst = (u32 __iomem *) dst1;
		shअगरt = 0;
		val = 0;
		
		अगर (start_index) अणु
			u32 start_mask = ~fb_shअगरted_pixels_mask_u32(p,
						start_index, bswapmask);
			val = FB_READL(dst) & start_mask;
			shअगरt = start_index;
		पूर्ण
		जबतक (n--) अणु
			अगर (p->fix.visual == FB_VISUAL_TRUECOLOR ||
			    p->fix.visual == FB_VISUAL_सूचीECTCOLOR )
				color = palette[*src];
			अन्यथा
				color = *src;
			color <<= FB_LEFT_POS(p, bpp);
			val |= FB_SHIFT_HIGH(p, color, shअगरt ^ bswapmask);
			अगर (shअगरt >= null_bits) अणु
				FB_WRITEL(val, dst++);
	
				val = (shअगरt == null_bits) ? 0 : 
					FB_SHIFT_LOW(p, color, 32 - shअगरt);
			पूर्ण
			shअगरt += bpp;
			shअगरt &= (32 - 1);
			src++;
		पूर्ण
		अगर (shअगरt) अणु
			u32 end_mask = fb_shअगरted_pixels_mask_u32(p, shअगरt,
						bswapmask);

			FB_WRITEL((FB_READL(dst) & end_mask) | val, dst);
		पूर्ण
		dst1 += p->fix.line_length;
		अगर (pitch_index) अणु
			dst2 += p->fix.line_length;
			dst1 = (u8 __iomem *)((दीर्घ __क्रमce)dst2 & ~(माप(u32) - 1));

			start_index += pitch_index;
			start_index &= 32 - 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम slow_imageblit(स्थिर काष्ठा fb_image *image, काष्ठा fb_info *p, 
				  u8 __iomem *dst1, u32 fgcolor,
				  u32 bgcolor, 
				  u32 start_index,
				  u32 pitch_index)
अणु
	u32 shअगरt, color = 0, bpp = p->var.bits_per_pixel;
	u32 __iomem *dst, *dst2;
	u32 val, pitch = p->fix.line_length;
	u32 null_bits = 32 - bpp;
	u32 spitch = (image->width+7)/8;
	स्थिर u8 *src = image->data, *s;
	u32 i, j, l;
	u32 bswapmask = fb_compute_bswapmask(p);

	dst2 = (u32 __iomem *) dst1;
	fgcolor <<= FB_LEFT_POS(p, bpp);
	bgcolor <<= FB_LEFT_POS(p, bpp);

	क्रम (i = image->height; i--; ) अणु
		shअगरt = val = 0;
		l = 8;
		j = image->width;
		dst = (u32 __iomem *) dst1;
		s = src;

		/* ग_लिखो leading bits */
		अगर (start_index) अणु
			u32 start_mask = ~fb_shअगरted_pixels_mask_u32(p,
						start_index, bswapmask);
			val = FB_READL(dst) & start_mask;
			shअगरt = start_index;
		पूर्ण

		जबतक (j--) अणु
			l--;
			color = (*s & (1 << l)) ? fgcolor : bgcolor;
			val |= FB_SHIFT_HIGH(p, color, shअगरt ^ bswapmask);
			
			/* Did the bitshअगरt spill bits to the next दीर्घ? */
			अगर (shअगरt >= null_bits) अणु
				FB_WRITEL(val, dst++);
				val = (shअगरt == null_bits) ? 0 :
					FB_SHIFT_LOW(p, color, 32 - shअगरt);
			पूर्ण
			shअगरt += bpp;
			shअगरt &= (32 - 1);
			अगर (!l) अणु l = 8; s++; पूर्ण
		पूर्ण

		/* ग_लिखो trailing bits */
 		अगर (shअगरt) अणु
			u32 end_mask = fb_shअगरted_pixels_mask_u32(p, shअगरt,
						bswapmask);

			FB_WRITEL((FB_READL(dst) & end_mask) | val, dst);
		पूर्ण
		
		dst1 += pitch;
		src += spitch;	
		अगर (pitch_index) अणु
			dst2 += pitch;
			dst1 = (u8 __iomem *)((दीर्घ __क्रमce)dst2 & ~(माप(u32) - 1));
			start_index += pitch_index;
			start_index &= 32 - 1;
		पूर्ण
		
	पूर्ण
पूर्ण

/*
 * fast_imageblit - optimized monochrome color expansion
 *
 * Only अगर:  bits_per_pixel == 8, 16, or 32
 *           image->width is भागisible by pixel/dword (ppw);
 *           fix->line_legth is भागisible by 4;
 *           beginning and end of a scanline is dword aligned
 */
अटल अंतरभूत व्योम fast_imageblit(स्थिर काष्ठा fb_image *image, काष्ठा fb_info *p, 
				  u8 __iomem *dst1, u32 fgcolor, 
				  u32 bgcolor) 
अणु
	u32 fgx = fgcolor, bgx = bgcolor, bpp = p->var.bits_per_pixel;
	u32 ppw = 32/bpp, spitch = (image->width + 7)/8;
	u32 bit_mask, end_mask, eorx, shअगरt;
	स्थिर अक्षर *s = image->data, *src;
	u32 __iomem *dst;
	स्थिर u32 *tab = शून्य;
	पूर्णांक i, j, k;

	चयन (bpp) अणु
	हाल 8:
		tab = fb_be_math(p) ? cfb_tab8_be : cfb_tab8_le;
		अवरोध;
	हाल 16:
		tab = fb_be_math(p) ? cfb_tab16_be : cfb_tab16_le;
		अवरोध;
	हाल 32:
	शेष:
		tab = cfb_tab32;
		अवरोध;
	पूर्ण

	क्रम (i = ppw-1; i--; ) अणु
		fgx <<= bpp;
		bgx <<= bpp;
		fgx |= fgcolor;
		bgx |= bgcolor;
	पूर्ण
	
	bit_mask = (1 << ppw) - 1;
	eorx = fgx ^ bgx;
	k = image->width/ppw;

	क्रम (i = image->height; i--; ) अणु
		dst = (u32 __iomem *) dst1, shअगरt = 8; src = s;
		
		क्रम (j = k; j--; ) अणु
			shअगरt -= ppw;
			end_mask = tab[(*src >> shअगरt) & bit_mask];
			FB_WRITEL((end_mask & eorx)^bgx, dst++);
			अगर (!shअगरt) अणु shअगरt = 8; src++; पूर्ण		
		पूर्ण
		dst1 += p->fix.line_length;
		s += spitch;
	पूर्ण
पूर्ण	
	
व्योम cfb_imageblit(काष्ठा fb_info *p, स्थिर काष्ठा fb_image *image)
अणु
	u32 fgcolor, bgcolor, start_index, bitstart, pitch_index = 0;
	u32 bpl = माप(u32), bpp = p->var.bits_per_pixel;
	u32 width = image->width;
	u32 dx = image->dx, dy = image->dy;
	u8 __iomem *dst1;

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	bitstart = (dy * p->fix.line_length * 8) + (dx * bpp);
	start_index = bitstart & (32 - 1);
	pitch_index = (p->fix.line_length & (bpl - 1)) * 8;

	bitstart /= 8;
	bitstart &= ~(bpl - 1);
	dst1 = p->screen_base + bitstart;

	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	अगर (image->depth == 1) अणु
		अगर (p->fix.visual == FB_VISUAL_TRUECOLOR ||
		    p->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
			fgcolor = ((u32*)(p->pseuकरो_palette))[image->fg_color];
			bgcolor = ((u32*)(p->pseuकरो_palette))[image->bg_color];
		पूर्ण अन्यथा अणु
			fgcolor = image->fg_color;
			bgcolor = image->bg_color;
		पूर्ण	
		
		अगर (32 % bpp == 0 && !start_index && !pitch_index && 
		    ((width & (32/bpp-1)) == 0) &&
		    bpp >= 8 && bpp <= 32) 			
			fast_imageblit(image, p, dst1, fgcolor, bgcolor);
		अन्यथा 
			slow_imageblit(image, p, dst1, fgcolor, bgcolor,
					start_index, pitch_index);
	पूर्ण अन्यथा
		color_imageblit(image, p, dst1, start_index, pitch_index);
पूर्ण

EXPORT_SYMBOL(cfb_imageblit);

MODULE_AUTHOR("James Simmons <jsimmons@users.sf.net>");
MODULE_DESCRIPTION("Generic software accelerated imaging drawing");
MODULE_LICENSE("GPL");

