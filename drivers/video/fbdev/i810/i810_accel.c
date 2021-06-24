<शैली गुरु>
/*-*- linux-c -*-
 *  linux/drivers/video/i810_accel.c -- Hardware Acceleration
 *
 *      Copyright (C) 2001 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved      
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>

#समावेश "i810_regs.h"
#समावेश "i810.h"
#समावेश "i810_main.h"

अटल u32 i810fb_rop[] = अणु
	COLOR_COPY_ROP, /* ROP_COPY */
	XOR_ROP         /* ROP_XOR  */
पूर्ण;

/* Macros */
#घोषणा PUT_RING(n) अणु                                        \
	i810_ग_लिखोl(par->cur_tail, par->iring.भव, n);   \
        par->cur_tail += 4;                                  \
        par->cur_tail &= RING_SIZE_MASK;                     \
पूर्ण                                                                      

बाह्य व्योम flush_cache(व्योम);

/************************************************************/

/* BLT Engine Routines */
अटल अंतरभूत व्योम i810_report_error(u8 __iomem *mmio)
अणु
	prपूर्णांकk("IIR     : 0x%04x\n"
	       "EIR     : 0x%04x\n"
	       "PGTBL_ER: 0x%04x\n"
	       "IPEIR   : 0x%04x\n"
	       "IPEHR   : 0x%04x\n",
	       i810_पढ़ोw(IIR, mmio),
	       i810_पढ़ोb(EIR, mmio),
	       i810_पढ़ोl(PGTBL_ER, mmio),
	       i810_पढ़ोl(IPEIR, mmio), 
	       i810_पढ़ोl(IPEHR, mmio));
पूर्ण

/**
 * रुको_क्रम_space - check ring buffer मुक्त space
 * @space: amount of ringbuffer space needed in bytes
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * The function रुकोs until a मुक्त space from the ringbuffer
 * is available 
 */	
अटल अंतरभूत पूर्णांक रुको_क्रम_space(काष्ठा fb_info *info, u32 space)
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 head, count = WAIT_COUNT, tail;
	u8 __iomem *mmio = par->mmio_start_भव;

	tail = par->cur_tail;
	जबतक (count--) अणु
		head = i810_पढ़ोl(IRING + 4, mmio) & RBUFFER_HEAD_MASK;	
		अगर ((tail == head) || 
		    (tail > head && 
		     (par->iring.size - tail + head) >= space) || 
		    (tail < head && (head - tail) >= space)) अणु
			वापस 0;	
		पूर्ण
	पूर्ण
	prपूर्णांकk("ringbuffer lockup!!!\n");
	i810_report_error(mmio); 
	par->dev_flags |= LOCKUP;
	info->pixmap.scan_align = 1;
	वापस 1;
पूर्ण

/** 
 * रुको_क्रम_engine_idle - रुकोs क्रम all hardware engines to finish
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * This रुकोs क्रम lring(0), iring(1), and batch(3), etc to finish and
 * रुकोs until ringbuffer is empty.
 */
अटल अंतरभूत पूर्णांक रुको_क्रम_engine_idle(काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;
	पूर्णांक count = WAIT_COUNT;

	अगर (रुको_क्रम_space(info, par->iring.size)) /* flush */
		वापस 1;

	जबतक((i810_पढ़ोw(INSTDONE, mmio) & 0x7B) != 0x7B && --count); 
	अगर (count) वापस 0;

	prपूर्णांकk("accel engine lockup!!!\n");
	prपूर्णांकk("INSTDONE: 0x%04x\n", i810_पढ़ोl(INSTDONE, mmio));
	i810_report_error(mmio); 
	par->dev_flags |= LOCKUP;
	info->pixmap.scan_align = 1;
	वापस 1;
पूर्ण

/* begin_iring - prepares the ringbuffer 
 * @space: length of sequence in dwords
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Checks/रुकोs क्रम sufficient space in ringbuffer of size
 * space.  Returns the tail of the buffer
 */ 
अटल अंतरभूत u32 begin_iring(काष्ठा fb_info *info, u32 space)
अणु
	काष्ठा i810fb_par *par = info->par;

	अगर (par->dev_flags & ALWAYS_SYNC) 
		रुको_क्रम_engine_idle(info);
	वापस रुको_क्रम_space(info, space);
पूर्ण

/**
 * end_iring - advances the buffer
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * This advances the tail of the ringbuffer, effectively
 * beginning the execution of the graphics inकाष्ठाion sequence.
 */
अटल अंतरभूत व्योम end_iring(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_ग_लिखोl(IRING, mmio, par->cur_tail);
पूर्ण

/**
 * source_copy_blit - BLIT transfer operation
 * @dwidth: width of rectangular graphics data
 * @dheight: height of rectangular graphics data
 * @dpitch: bytes per line of destination buffer
 * @xdir: direction of copy (left to right or right to left)
 * @src: address of first pixel to पढ़ो from
 * @dest: address of first pixel to ग_लिखो to
 * @from: source address
 * @where: destination address
 * @rop: raster operation
 * @blit_bpp: pixel क्रमmat which can be dअगरferent from the 
 *            framebuffer's pixelक्रमmat
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * This is a BLIT operation typically used when करोing
 * a 'Copy and Paste'
 */
अटल अंतरभूत व्योम source_copy_blit(पूर्णांक dwidth, पूर्णांक dheight, पूर्णांक dpitch, 
				    पूर्णांक xdir, पूर्णांक src, पूर्णांक dest, पूर्णांक rop, 
				    पूर्णांक blit_bpp, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

	अगर (begin_iring(info, 24 + IRING_PAD)) वापस;

	PUT_RING(BLIT | SOURCE_COPY_BLIT | 4);
	PUT_RING(xdir | rop << 16 | dpitch | DYN_COLOR_EN | blit_bpp);
	PUT_RING(dheight << 16 | dwidth);
	PUT_RING(dest);
	PUT_RING(dpitch);
	PUT_RING(src);

	end_iring(par);
पूर्ण	

/**
 * color_blit - solid color BLIT operation
 * @width: width of destination
 * @height: height of destination
 * @pitch: pixels per line of the buffer
 * @dest: address of first pixel to ग_लिखो to
 * @where: destination
 * @rop: raster operation
 * @what: color to transfer
 * @blit_bpp: pixel क्रमmat which can be dअगरferent from the 
 *            framebuffer's pixelक्रमmat
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * A BLIT operation which can be used क्रम  color fill/rectangular fill
 */
अटल अंतरभूत व्योम color_blit(पूर्णांक width, पूर्णांक height, पूर्णांक pitch,  पूर्णांक dest, 
			      पूर्णांक rop, पूर्णांक what, पूर्णांक blit_bpp, 
			      काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

	अगर (begin_iring(info, 24 + IRING_PAD)) वापस;

	PUT_RING(BLIT | COLOR_BLT | 3);
	PUT_RING(rop << 16 | pitch | SOLIDPATTERN | DYN_COLOR_EN | blit_bpp);
	PUT_RING(height << 16 | width);
	PUT_RING(dest);
	PUT_RING(what);
	PUT_RING(NOP);

	end_iring(par);
पूर्ण
 
/**
 * mono_src_copy_imm_blit - color expand from प्रणाली memory to framebuffer
 * @dwidth: width of destination
 * @dheight: height of destination
 * @dpitch: pixels per line of the buffer
 * @dsize: size of biपंचांगap in द्विगुन words
 * @dest: address of first byte of pixel;
 * @rop: raster operation
 * @blit_bpp: pixelक्रमmat to use which can be dअगरferent from the 
 *            framebuffer's pixelक्रमmat
 * @src: address of image data
 * @bg: backgound color
 * @fg: क्रमground color
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * A color expand operation where the  source data is placed in the 
 * ringbuffer itself. Useful क्रम drawing text. 
 *
 * REQUIREMENT:
 * The end of a scanline must be padded to the next word.
 */
अटल अंतरभूत व्योम mono_src_copy_imm_blit(पूर्णांक dwidth, पूर्णांक dheight, पूर्णांक dpitch,
					  पूर्णांक dsize, पूर्णांक blit_bpp, पूर्णांक rop,
					  पूर्णांक dest, स्थिर u32 *src, पूर्णांक bg,
					  पूर्णांक fg, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

	अगर (begin_iring(info, 24 + (dsize << 2) + IRING_PAD)) वापस;

	PUT_RING(BLIT | MONO_SOURCE_COPY_IMMEDIATE | (4 + dsize));
	PUT_RING(DYN_COLOR_EN | blit_bpp | rop << 16 | dpitch);
	PUT_RING(dheight << 16 | dwidth);
	PUT_RING(dest);
	PUT_RING(bg);
	PUT_RING(fg);
	जबतक (dsize--) 
		PUT_RING(*src++);

	end_iring(par);
पूर्ण

अटल अंतरभूत व्योम load_front(पूर्णांक offset, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

	अगर (begin_iring(info, 8 + IRING_PAD)) वापस;

	PUT_RING(PARSER | FLUSH);
	PUT_RING(NOP);

	end_iring(par);

	अगर (begin_iring(info, 8 + IRING_PAD)) वापस;

	PUT_RING(PARSER | FRONT_BUFFER | ((par->pitch >> 3) << 8));
	PUT_RING((par->fb.offset << 12) + offset);

	end_iring(par);
पूर्ण

/**
 * i810fb_iring_enable - enables/disables the ringbuffer
 * @mode: enable or disable
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Enables or disables the ringbuffer, effectively enabling or
 * disabling the inकाष्ठाion/acceleration engine.
 */
अटल अंतरभूत व्योम i810fb_iring_enable(काष्ठा i810fb_par *par, u32 mode)
अणु
	u32 पंचांगp;
	u8 __iomem *mmio = par->mmio_start_भव;

	पंचांगp = i810_पढ़ोl(IRING + 12, mmio);
	अगर (mode == OFF) 
		पंचांगp &= ~1;
	अन्यथा 
		पंचांगp |= 1;
	flush_cache();
	i810_ग_लिखोl(IRING + 12, mmio, पंचांगp);
पूर्ण       

व्योम i810fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 dx, dy, width, height, dest, rop = 0, color = 0;

	अगर (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (par->depth == 1) 
		color = rect->color;
	अन्यथा 
		color = ((u32 *) (info->pseuकरो_palette))[rect->color];

	rop = i810fb_rop[rect->rop];

	dx = rect->dx * par->depth;
	width = rect->width * par->depth;
	dy = rect->dy;
	height = rect->height;

	dest = info->fix.smem_start + (dy * info->fix.line_length) + dx;
	color_blit(width, height, info->fix.line_length, dest, rop, color, 
		   par->blit_bpp, info);
पूर्ण
	
व्योम i810fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region) 
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 sx, sy, dx, dy, pitch, width, height, src, dest, xdir;

	अगर (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4) अणु
		cfb_copyarea(info, region);
		वापस;
	पूर्ण

	dx = region->dx * par->depth;
	sx = region->sx * par->depth;
	width = region->width * par->depth;
	sy = region->sy;
	dy = region->dy;
	height = region->height;

	अगर (dx <= sx) अणु
		xdir = INCREMENT;
	पूर्ण
	अन्यथा अणु
		xdir = DECREMENT;
		sx += width - 1;
		dx += width - 1;
	पूर्ण
	अगर (dy <= sy) अणु
		pitch = info->fix.line_length;
	पूर्ण
	अन्यथा अणु
		pitch = (-(info->fix.line_length)) & 0xFFFF;
		sy += height - 1;
		dy += height - 1;
	पूर्ण
	src = info->fix.smem_start + (sy * info->fix.line_length) + sx;
	dest = info->fix.smem_start + (dy * info->fix.line_length) + dx;

	source_copy_blit(width, height, pitch, xdir, src, dest,
			 PAT_COPY_ROP, par->blit_bpp, info);
पूर्ण

व्योम i810fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 fg = 0, bg = 0, size, dst;
	
	अगर (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4 || image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		fg = image->fg_color;
		bg = image->bg_color;
		अवरोध;
	हाल 16:
	हाल 24:
		fg = ((u32 *)(info->pseuकरो_palette))[image->fg_color];
		bg = ((u32 *)(info->pseuकरो_palette))[image->bg_color];
		अवरोध;
	पूर्ण	
	
	dst = info->fix.smem_start + (image->dy * info->fix.line_length) + 
		(image->dx * par->depth);

	size = (image->width+7)/8 + 1;
	size &= ~1;
	size *= image->height;
	size += 7;
	size &= ~7;
	mono_src_copy_imm_blit(image->width * par->depth, 
			       image->height, info->fix.line_length, 
			       size/4, par->blit_bpp,
			       PAT_COPY_ROP, dst, (u32 *) image->data, 
			       bg, fg, info);
पूर्ण 

पूर्णांक i810fb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	
	अगर (!info->var.accel_flags || par->dev_flags & LOCKUP)
		वापस 0;

	वापस रुको_क्रम_engine_idle(info);
पूर्ण

व्योम i810fb_load_front(u32 offset, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;

	अगर (!info->var.accel_flags || par->dev_flags & LOCKUP)
		i810_ग_लिखोl(DPLYBASE, mmio, par->fb.physical + offset);
	अन्यथा 
		load_front(offset, info);
पूर्ण

/**
 * i810fb_init_ringbuffer - initialize the ringbuffer
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Initializes the ringbuffer by telling the device the
 * size and location of the ringbuffer.  It also sets 
 * the head and tail poपूर्णांकers = 0
 */
व्योम i810fb_init_ringbuffer(काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 पंचांगp1, पंचांगp2;
	u8 __iomem *mmio = par->mmio_start_भव;
	
	रुको_क्रम_engine_idle(info);
	i810fb_iring_enable(par, OFF);
	i810_ग_लिखोl(IRING, mmio, 0);
	i810_ग_लिखोl(IRING + 4, mmio, 0);
	par->cur_tail = 0;

	पंचांगp2 = i810_पढ़ोl(IRING + 8, mmio) & ~RBUFFER_START_MASK; 
	पंचांगp1 = par->iring.physical;
	i810_ग_लिखोl(IRING + 8, mmio, पंचांगp2 | पंचांगp1);

	पंचांगp1 = i810_पढ़ोl(IRING + 12, mmio);
	पंचांगp1 &= ~RBUFFER_SIZE_MASK;
	पंचांगp2 = (par->iring.size - I810_PAGESIZE) & RBUFFER_SIZE_MASK;
	i810_ग_लिखोl(IRING + 12, mmio, पंचांगp1 | पंचांगp2);
	i810fb_iring_enable(par, ON);
पूर्ण
