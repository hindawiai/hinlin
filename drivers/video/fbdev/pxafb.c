<शैली गुरु>
/*
 *  linux/drivers/video/pxafb.c
 *
 *  Copyright (C) 1999 Eric A. Thomas.
 *  Copyright (C) 2004 Jean-Frederic Clere.
 *  Copyright (C) 2004 Ian Campbell.
 *  Copyright (C) 2004 Jeff Lackey.
 *   Based on sa1100fb.c Copyright (C) 1999 Eric A. Thomas
 *  which in turn is
 *   Based on acornfb.c Copyright (C) Russell King.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 *	        Intel PXA250/210 LCD Controller Frame Buffer Driver
 *
 * Please direct your questions and comments on this driver to the following
 * email address:
 *
 *	linux-arm-kernel@lists.arm.linux.org.uk
 *
 * Add support क्रम overlay1 and overlay2 based on pxafb_overlay.c:
 *
 *   Copyright (C) 2004, Intel Corporation
 *
 *     2003/08/27: <yu.tang@पूर्णांकel.com>
 *     2004/03/10: <stanley.cai@पूर्णांकel.com>
 *     2004/10/28: <yan.yin@पूर्णांकel.com>
 *
 *   Copyright (C) 2006-2008 Marvell International Ltd.
 *   All Rights Reserved
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/console.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/videomode.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <mach/bitfield.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>

/*
 * Complain अगर VAR is out of range.
 */
#घोषणा DEBUG_VAR 1

#समावेश "pxafb.h"

/* Bits which should not be set in machine configuration काष्ठाures */
#घोषणा LCCR0_INVALID_CONFIG_MASK	(LCCR0_OUM | LCCR0_BM | LCCR0_QDM |\
					 LCCR0_DIS | LCCR0_EFM | LCCR0_IUM |\
					 LCCR0_SFM | LCCR0_LDM | LCCR0_ENB)

#घोषणा LCCR3_INVALID_CONFIG_MASK	(LCCR3_HSP | LCCR3_VSP |\
					 LCCR3_PCD | LCCR3_BPP(0xf))

अटल पूर्णांक pxafb_activate_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा pxafb_info *);
अटल व्योम set_ctrlr_state(काष्ठा pxafb_info *fbi, u_पूर्णांक state);
अटल व्योम setup_base_frame(काष्ठा pxafb_info *fbi,
                             काष्ठा fb_var_screeninfo *var, पूर्णांक branch);
अटल पूर्णांक setup_frame_dma(काष्ठा pxafb_info *fbi, पूर्णांक dma, पूर्णांक pal,
			   अचिन्हित दीर्घ offset, माप_प्रकार size);

अटल अचिन्हित दीर्घ video_mem_size = 0;

अटल अंतरभूत अचिन्हित दीर्घ
lcd_पढ़ोl(काष्ठा pxafb_info *fbi, अचिन्हित पूर्णांक off)
अणु
	वापस __raw_पढ़ोl(fbi->mmio_base + off);
पूर्ण

अटल अंतरभूत व्योम
lcd_ग_लिखोl(काष्ठा pxafb_info *fbi, अचिन्हित पूर्णांक off, अचिन्हित दीर्घ val)
अणु
	__raw_ग_लिखोl(val, fbi->mmio_base + off);
पूर्ण

अटल अंतरभूत व्योम pxafb_schedule_work(काष्ठा pxafb_info *fbi, u_पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/*
	 * We need to handle two requests being made at the same समय.
	 * There are two important हालs:
	 *  1. When we are changing VT (C_REENABLE) जबतक unblanking
	 *     (C_ENABLE) We must perक्रमm the unblanking, which will
	 *     करो our REENABLE क्रम us.
	 *  2. When we are blanking, but immediately unblank beक्रमe
	 *     we have blanked.  We करो the "REENABLE" thing here as
	 *     well, just to be sure.
	 */
	अगर (fbi->task_state == C_ENABLE && state == C_REENABLE)
		state = (u_पूर्णांक) -1;
	अगर (fbi->task_state == C_DISABLE && state == C_ENABLE)
		state = C_REENABLE;

	अगर (state != (u_पूर्णांक)-1) अणु
		fbi->task_state = state;
		schedule_work(&fbi->task);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक
pxafb_setpalettereg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		       u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	u_पूर्णांक val;

	अगर (regno >= fbi->palette_size)
		वापस 1;

	अगर (fbi->fb.var.grayscale) अणु
		fbi->palette_cpu[regno] = ((blue >> 8) & 0x00ff);
		वापस 0;
	पूर्ण

	चयन (fbi->lccr4 & LCCR4_PAL_FOR_MASK) अणु
	हाल LCCR4_PAL_FOR_0:
		val  = ((red   >>  0) & 0xf800);
		val |= ((green >>  5) & 0x07e0);
		val |= ((blue  >> 11) & 0x001f);
		fbi->palette_cpu[regno] = val;
		अवरोध;
	हाल LCCR4_PAL_FOR_1:
		val  = ((red   << 8) & 0x00f80000);
		val |= ((green >> 0) & 0x0000fc00);
		val |= ((blue  >> 8) & 0x000000f8);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		अवरोध;
	हाल LCCR4_PAL_FOR_2:
		val  = ((red   << 8) & 0x00fc0000);
		val |= ((green >> 0) & 0x0000fc00);
		val |= ((blue  >> 8) & 0x000000fc);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		अवरोध;
	हाल LCCR4_PAL_FOR_3:
		val  = ((red   << 8) & 0x00ff0000);
		val |= ((green >> 0) & 0x0000ff00);
		val |= ((blue  >> 8) & 0x000000ff);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
pxafb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		   u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 1;

	/*
	 * If inverse mode was selected, invert all the colours
	 * rather than the रेजिस्टर number.  The रेजिस्टर number
	 * is what you poke पूर्णांकo the framebuffer to produce the
	 * colour you requested.
	 */
	अगर (fbi->cmap_inverse) अणु
		red   = 0xffff - red;
		green = 0xffff - green;
		blue  = 0xffff - blue;
	पूर्ण

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	अगर (fbi->fb.var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
					7471 * blue) >> 16;

	चयन (fbi->fb.fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/*
		 * 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield inक्रमmation.
		 */
		अगर (regno < 16) अणु
			u32 *pal = fbi->fb.pseuकरो_palette;

			val  = chan_to_field(red, &fbi->fb.var.red);
			val |= chan_to_field(green, &fbi->fb.var.green);
			val |= chan_to_field(blue, &fbi->fb.var.blue);

			pal[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_STATIC_PSEUDOCOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		ret = pxafb_setpalettereg(regno, red, green, blue, trans, info);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* calculate pixel depth, transparency bit included, >=16bpp क्रमmats _only_ */
अटल अंतरभूत पूर्णांक var_to_depth(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->red.length + var->green.length +
		var->blue.length + var->transp.length;
पूर्ण

/* calculate 4-bit BPP value क्रम LCCR3 and OVLxC1 */
अटल पूर्णांक pxafb_var_to_bpp(काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक bpp = -EINVAL;

	चयन (var->bits_per_pixel) अणु
	हाल 1:  bpp = 0; अवरोध;
	हाल 2:  bpp = 1; अवरोध;
	हाल 4:  bpp = 2; अवरोध;
	हाल 8:  bpp = 3; अवरोध;
	हाल 16: bpp = 4; अवरोध;
	हाल 24:
		चयन (var_to_depth(var)) अणु
		हाल 18: bpp = 6; अवरोध; /* 18-bits/pixel packed */
		हाल 19: bpp = 8; अवरोध; /* 19-bits/pixel packed */
		हाल 24: bpp = 9; अवरोध;
		पूर्ण
		अवरोध;
	हाल 32:
		चयन (var_to_depth(var)) अणु
		हाल 18: bpp = 5; अवरोध; /* 18-bits/pixel unpacked */
		हाल 19: bpp = 7; अवरोध; /* 19-bits/pixel unpacked */
		हाल 25: bpp = 10; अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस bpp;
पूर्ण

/*
 *  pxafb_var_to_lccr3():
 *    Convert a bits per pixel value to the correct bit pattern क्रम LCCR3
 *
 *  NOTE: क्रम PXA27x with overlays support, the LCCR3_PDFOR_x bits have an
 *  implication of the acutal use of transparency bit,  which we handle it
 *  here separatedly. See PXA27x Developer's Manual, Section <<7.4.6 Pixel
 *  Formats>> क्रम the valid combination of PDFOR, PAL_FOR क्रम various BPP.
 *
 *  Transparency क्रम palette pixel क्रमmats is not supported at the moment.
 */
अटल uपूर्णांक32_t pxafb_var_to_lccr3(काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक bpp = pxafb_var_to_bpp(var);
	uपूर्णांक32_t lccr3;

	अगर (bpp < 0)
		वापस 0;

	lccr3 = LCCR3_BPP(bpp);

	चयन (var_to_depth(var)) अणु
	हाल 16: lccr3 |= var->transp.length ? LCCR3_PDFOR_3 : 0; अवरोध;
	हाल 18: lccr3 |= LCCR3_PDFOR_3; अवरोध;
	हाल 24: lccr3 |= var->transp.length ? LCCR3_PDFOR_2 : LCCR3_PDFOR_3;
		 अवरोध;
	हाल 19:
	हाल 25: lccr3 |= LCCR3_PDFOR_0; अवरोध;
	पूर्ण
	वापस lccr3;
पूर्ण

#घोषणा SET_PIXFMT(v, r, g, b, t)				\
(अणु								\
	(v)->transp.offset = (t) ? (r) + (g) + (b) : 0;		\
	(v)->transp.length = (t) ? (t) : 0;			\
	(v)->blue.length   = (b); (v)->blue.offset = 0;		\
	(v)->green.length  = (g); (v)->green.offset = (b);	\
	(v)->red.length    = (r); (v)->red.offset = (b) + (g);	\
पूर्ण)

/* set the RGBT bitfields of fb_var_screeninf according to
 * var->bits_per_pixel and given depth
 */
अटल व्योम pxafb_set_pixfmt(काष्ठा fb_var_screeninfo *var, पूर्णांक depth)
अणु
	अगर (depth == 0)
		depth = var->bits_per_pixel;

	अगर (var->bits_per_pixel < 16) अणु
		/* indexed pixel क्रमmats */
		var->red.offset    = 0; var->red.length    = 8;
		var->green.offset  = 0; var->green.length  = 8;
		var->blue.offset   = 0; var->blue.length   = 8;
		var->transp.offset = 0; var->transp.length = 8;
	पूर्ण

	चयन (depth) अणु
	हाल 16: var->transp.length ?
		 SET_PIXFMT(var, 5, 5, 5, 1) :		/* RGBT555 */
		 SET_PIXFMT(var, 5, 6, 5, 0); अवरोध;	/* RGB565 */
	हाल 18: SET_PIXFMT(var, 6, 6, 6, 0); अवरोध;	/* RGB666 */
	हाल 19: SET_PIXFMT(var, 6, 6, 6, 1); अवरोध;	/* RGBT666 */
	हाल 24: var->transp.length ?
		 SET_PIXFMT(var, 8, 8, 7, 1) :		/* RGBT887 */
		 SET_PIXFMT(var, 8, 8, 8, 0); अवरोध;	/* RGB888 */
	हाल 25: SET_PIXFMT(var, 8, 8, 8, 1); अवरोध;	/* RGBT888 */
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
/*
 *  pxafb_display_dma_period()
 *    Calculate the minimum period (in picoseconds) between two DMA
 *    requests क्रम the LCD controller.  If we hit this, it means we're
 *    करोing nothing but LCD DMA.
 */
अटल अचिन्हित पूर्णांक pxafb_display_dma_period(काष्ठा fb_var_screeninfo *var)
अणु
	/*
	 * Period = pixघड़ी * bits_per_byte * bytes_per_transfer
	 *              / memory_bits_per_pixel;
	 */
	वापस var->pixघड़ी * 8 * 16 / var->bits_per_pixel;
पूर्ण
#पूर्ण_अगर

/*
 * Select the smallest mode that allows the desired resolution to be
 * displayed. If desired parameters can be rounded up.
 */
अटल काष्ठा pxafb_mode_info *pxafb_geपंचांगode(काष्ठा pxafb_mach_info *mach,
					     काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा pxafb_mode_info *mode = शून्य;
	काष्ठा pxafb_mode_info *modelist = mach->modes;
	अचिन्हित पूर्णांक best_x = 0xffffffff, best_y = 0xffffffff;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mach->num_modes; i++) अणु
		अगर (modelist[i].xres >= var->xres &&
		    modelist[i].yres >= var->yres &&
		    modelist[i].xres < best_x &&
		    modelist[i].yres < best_y &&
		    modelist[i].bpp >= var->bits_per_pixel) अणु
			best_x = modelist[i].xres;
			best_y = modelist[i].yres;
			mode = &modelist[i];
		पूर्ण
	पूर्ण

	वापस mode;
पूर्ण

अटल व्योम pxafb_seपंचांगode(काष्ठा fb_var_screeninfo *var,
			  काष्ठा pxafb_mode_info *mode)
अणु
	var->xres		= mode->xres;
	var->yres		= mode->yres;
	var->bits_per_pixel	= mode->bpp;
	var->pixघड़ी		= mode->pixघड़ी;
	var->hsync_len		= mode->hsync_len;
	var->left_margin	= mode->left_margin;
	var->right_margin	= mode->right_margin;
	var->vsync_len		= mode->vsync_len;
	var->upper_margin	= mode->upper_margin;
	var->lower_margin	= mode->lower_margin;
	var->sync		= mode->sync;
	var->grayscale		= mode->cmap_greyscale;
	var->transp.length	= mode->transparency;

	/* set the initial RGBA bitfields */
	pxafb_set_pixfmt(var, mode->depth);
पूर्ण

अटल पूर्णांक pxafb_adjust_timing(काष्ठा pxafb_info *fbi,
			       काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक line_length;

	var->xres = max_t(पूर्णांक, var->xres, MIN_XRES);
	var->yres = max_t(पूर्णांक, var->yres, MIN_YRES);

	अगर (!(fbi->lccr0 & LCCR0_LCDT)) अणु
		clamp_val(var->hsync_len, 1, 64);
		clamp_val(var->vsync_len, 1, 64);
		clamp_val(var->left_margin,  1, 255);
		clamp_val(var->right_margin, 1, 255);
		clamp_val(var->upper_margin, 1, 255);
		clamp_val(var->lower_margin, 1, 255);
	पूर्ण

	/* make sure each line is aligned on word boundary */
	line_length = var->xres * var->bits_per_pixel / 8;
	line_length = ALIGN(line_length, 4);
	var->xres = line_length * 8 / var->bits_per_pixel;

	/* we करोn't support xpan, क्रमce xres_भव to be equal to xres */
	var->xres_भव = var->xres;

	अगर (var->accel_flags & FB_ACCELF_TEXT)
		var->yres_भव = fbi->fb.fix.smem_len / line_length;
	अन्यथा
		var->yres_भव = max(var->yres_भव, var->yres);

	/* check क्रम limits */
	अगर (var->xres > MAX_XRES || var->yres > MAX_YRES)
		वापस -EINVAL;

	अगर (var->yres > var->yres_भव)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 *  pxafb_check_var():
 *    Get the video params out of 'var'. If a value doesn't fit, round it up,
 *    अगर it's too big, वापस -EINVAL.
 *
 *    Round up in the following order: bits_per_pixel, xres,
 *    yres, xres_भव, yres_भव, xoffset, yoffset, grayscale,
 *    bitfields, horizontal timing, vertical timing.
 */
अटल पूर्णांक pxafb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	काष्ठा pxafb_mach_info *inf = fbi->inf;
	पूर्णांक err;

	अगर (inf->fixed_modes) अणु
		काष्ठा pxafb_mode_info *mode;

		mode = pxafb_geपंचांगode(inf, var);
		अगर (!mode)
			वापस -EINVAL;
		pxafb_seपंचांगode(var, mode);
	पूर्ण

	/* करो a test conversion to BPP fields to check the color क्रमmats */
	err = pxafb_var_to_bpp(var);
	अगर (err < 0)
		वापस err;

	pxafb_set_pixfmt(var, var_to_depth(var));

	err = pxafb_adjust_timing(fbi, var);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_CPU_FREQ
	pr_debug("pxafb: dma period = %d ps\n",
		 pxafb_display_dma_period(var));
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * pxafb_set_par():
 *	Set the user defined part of the display क्रम the specअगरied console
 */
अटल पूर्णांक pxafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	काष्ठा fb_var_screeninfo *var = &info->var;

	अगर (var->bits_per_pixel >= 16)
		fbi->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा अगर (!fbi->cmap_अटल)
		fbi->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा अणु
		/*
		 * Some people have weird ideas about wanting अटल
		 * pseuकरोcolor maps.  I suspect their user space
		 * applications are broken.
		 */
		fbi->fb.fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	पूर्ण

	fbi->fb.fix.line_length = var->xres_भव *
				  var->bits_per_pixel / 8;
	अगर (var->bits_per_pixel >= 16)
		fbi->palette_size = 0;
	अन्यथा
		fbi->palette_size = var->bits_per_pixel == 1 ?
					4 : 1 << var->bits_per_pixel;

	fbi->palette_cpu = (u16 *)&fbi->dma_buff->palette[0];

	अगर (fbi->fb.var.bits_per_pixel >= 16)
		fb_dealloc_cmap(&fbi->fb.cmap);
	अन्यथा
		fb_alloc_cmap(&fbi->fb.cmap, 1<<fbi->fb.var.bits_per_pixel, 0);

	pxafb_activate_var(var, fbi);

	वापस 0;
पूर्ण

अटल पूर्णांक pxafb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	काष्ठा fb_var_screeninfo newvar;
	पूर्णांक dma = DMA_MAX + DMA_BASE;

	अगर (fbi->state != C_ENABLE)
		वापस 0;

	/* Only take .xoffset, .yoffset and .vmode & FB_VMODE_YWRAP from what
	 * was passed in and copy the rest from the old screeninfo.
	 */
	स_नकल(&newvar, &fbi->fb.var, माप(newvar));
	newvar.xoffset = var->xoffset;
	newvar.yoffset = var->yoffset;
	newvar.vmode &= ~FB_VMODE_YWRAP;
	newvar.vmode |= var->vmode & FB_VMODE_YWRAP;

	setup_base_frame(fbi, &newvar, 1);

	अगर (fbi->lccr0 & LCCR0_SDS)
		lcd_ग_लिखोl(fbi, FBR1, fbi->fdadr[dma + 1] | 0x1);

	lcd_ग_लिखोl(fbi, FBR0, fbi->fdadr[dma] | 0x1);
	वापस 0;
पूर्ण

/*
 * pxafb_blank():
 *	Blank the display by setting all palette values to zero.  Note, the
 * 	16 bpp mode करोes not really use the palette, so this will not
 *      blank the display in all modes.
 */
अटल पूर्णांक pxafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	पूर्णांक i;

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		अगर (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			क्रम (i = 0; i < fbi->palette_size; i++)
				pxafb_setpalettereg(i, 0, 0, 0, 0, info);

		pxafb_schedule_work(fbi, C_DISABLE);
		/* TODO अगर (pxafb_blank_helper) pxafb_blank_helper(blank); */
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		/* TODO अगर (pxafb_blank_helper) pxafb_blank_helper(blank); */
		अगर (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&fbi->fb.cmap, info);
		pxafb_schedule_work(fbi, C_ENABLE);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops pxafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= pxafb_check_var,
	.fb_set_par	= pxafb_set_par,
	.fb_pan_display	= pxafb_pan_display,
	.fb_setcolreg	= pxafb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_blank	= pxafb_blank,
पूर्ण;

#अगर_घोषित CONFIG_FB_PXA_OVERLAY
अटल व्योम overlay1fb_setup(काष्ठा pxafb_layer *ofb)
अणु
	पूर्णांक size = ofb->fb.fix.line_length * ofb->fb.var.yres_भव;
	अचिन्हित दीर्घ start = ofb->video_mem_phys;
	setup_frame_dma(ofb->fbi, DMA_OV1, PAL_NONE, start, size);
पूर्ण

/* Depending on the enable status of overlay1/2, the DMA should be
 * updated from FDADRx (when disabled) or FBRx (when enabled).
 */
अटल व्योम overlay1fb_enable(काष्ठा pxafb_layer *ofb)
अणु
	पूर्णांक enabled = lcd_पढ़ोl(ofb->fbi, OVL1C1) & OVLxC1_OEN;
	uपूर्णांक32_t fdadr1 = ofb->fbi->fdadr[DMA_OV1] | (enabled ? 0x1 : 0);

	lcd_ग_लिखोl(ofb->fbi, enabled ? FBR1 : FDADR1, fdadr1);
	lcd_ग_लिखोl(ofb->fbi, OVL1C2, ofb->control[1]);
	lcd_ग_लिखोl(ofb->fbi, OVL1C1, ofb->control[0] | OVLxC1_OEN);
पूर्ण

अटल व्योम overlay1fb_disable(काष्ठा pxafb_layer *ofb)
अणु
	uपूर्णांक32_t lccr5;

	अगर (!(lcd_पढ़ोl(ofb->fbi, OVL1C1) & OVLxC1_OEN))
		वापस;

	lccr5 = lcd_पढ़ोl(ofb->fbi, LCCR5);

	lcd_ग_लिखोl(ofb->fbi, OVL1C1, ofb->control[0] & ~OVLxC1_OEN);

	lcd_ग_लिखोl(ofb->fbi, LCSR1, LCSR1_BS(1));
	lcd_ग_लिखोl(ofb->fbi, LCCR5, lccr5 & ~LCSR1_BS(1));
	lcd_ग_लिखोl(ofb->fbi, FBR1, ofb->fbi->fdadr[DMA_OV1] | 0x3);

	अगर (रुको_क्रम_completion_समयout(&ofb->branch_करोne, 1 * HZ) == 0)
		pr_warn("%s: timeout disabling overlay1\n", __func__);

	lcd_ग_लिखोl(ofb->fbi, LCCR5, lccr5);
पूर्ण

अटल व्योम overlay2fb_setup(काष्ठा pxafb_layer *ofb)
अणु
	पूर्णांक size, भाग = 1, pक्रम = NONSTD_TO_PFOR(ofb->fb.var.nonstd);
	अचिन्हित दीर्घ start[3] = अणु ofb->video_mem_phys, 0, 0 पूर्ण;

	अगर (pक्रम == OVERLAY_FORMAT_RGB || pक्रम == OVERLAY_FORMAT_YUV444_PACKED) अणु
		size = ofb->fb.fix.line_length * ofb->fb.var.yres_भव;
		setup_frame_dma(ofb->fbi, DMA_OV2_Y, -1, start[0], size);
	पूर्ण अन्यथा अणु
		size = ofb->fb.var.xres_भव * ofb->fb.var.yres_भव;
		चयन (pक्रम) अणु
		हाल OVERLAY_FORMAT_YUV444_PLANAR: भाग = 1; अवरोध;
		हाल OVERLAY_FORMAT_YUV422_PLANAR: भाग = 2; अवरोध;
		हाल OVERLAY_FORMAT_YUV420_PLANAR: भाग = 4; अवरोध;
		पूर्ण
		start[1] = start[0] + size;
		start[2] = start[1] + size / भाग;
		setup_frame_dma(ofb->fbi, DMA_OV2_Y,  -1, start[0], size);
		setup_frame_dma(ofb->fbi, DMA_OV2_Cb, -1, start[1], size / भाग);
		setup_frame_dma(ofb->fbi, DMA_OV2_Cr, -1, start[2], size / भाग);
	पूर्ण
पूर्ण

अटल व्योम overlay2fb_enable(काष्ठा pxafb_layer *ofb)
अणु
	पूर्णांक pक्रम = NONSTD_TO_PFOR(ofb->fb.var.nonstd);
	पूर्णांक enabled = lcd_पढ़ोl(ofb->fbi, OVL2C1) & OVLxC1_OEN;
	uपूर्णांक32_t fdadr2 = ofb->fbi->fdadr[DMA_OV2_Y]  | (enabled ? 0x1 : 0);
	uपूर्णांक32_t fdadr3 = ofb->fbi->fdadr[DMA_OV2_Cb] | (enabled ? 0x1 : 0);
	uपूर्णांक32_t fdadr4 = ofb->fbi->fdadr[DMA_OV2_Cr] | (enabled ? 0x1 : 0);

	अगर (pक्रम == OVERLAY_FORMAT_RGB || pक्रम == OVERLAY_FORMAT_YUV444_PACKED)
		lcd_ग_लिखोl(ofb->fbi, enabled ? FBR2 : FDADR2, fdadr2);
	अन्यथा अणु
		lcd_ग_लिखोl(ofb->fbi, enabled ? FBR2 : FDADR2, fdadr2);
		lcd_ग_लिखोl(ofb->fbi, enabled ? FBR3 : FDADR3, fdadr3);
		lcd_ग_लिखोl(ofb->fbi, enabled ? FBR4 : FDADR4, fdadr4);
	पूर्ण
	lcd_ग_लिखोl(ofb->fbi, OVL2C2, ofb->control[1]);
	lcd_ग_लिखोl(ofb->fbi, OVL2C1, ofb->control[0] | OVLxC1_OEN);
पूर्ण

अटल व्योम overlay2fb_disable(काष्ठा pxafb_layer *ofb)
अणु
	uपूर्णांक32_t lccr5;

	अगर (!(lcd_पढ़ोl(ofb->fbi, OVL2C1) & OVLxC1_OEN))
		वापस;

	lccr5 = lcd_पढ़ोl(ofb->fbi, LCCR5);

	lcd_ग_लिखोl(ofb->fbi, OVL2C1, ofb->control[0] & ~OVLxC1_OEN);

	lcd_ग_लिखोl(ofb->fbi, LCSR1, LCSR1_BS(2));
	lcd_ग_लिखोl(ofb->fbi, LCCR5, lccr5 & ~LCSR1_BS(2));
	lcd_ग_लिखोl(ofb->fbi, FBR2, ofb->fbi->fdadr[DMA_OV2_Y]  | 0x3);
	lcd_ग_लिखोl(ofb->fbi, FBR3, ofb->fbi->fdadr[DMA_OV2_Cb] | 0x3);
	lcd_ग_लिखोl(ofb->fbi, FBR4, ofb->fbi->fdadr[DMA_OV2_Cr] | 0x3);

	अगर (रुको_क्रम_completion_समयout(&ofb->branch_करोne, 1 * HZ) == 0)
		pr_warn("%s: timeout disabling overlay2\n", __func__);
पूर्ण

अटल काष्ठा pxafb_layer_ops ofb_ops[] = अणु
	[0] = अणु
		.enable		= overlay1fb_enable,
		.disable	= overlay1fb_disable,
		.setup		= overlay1fb_setup,
	पूर्ण,
	[1] = अणु
		.enable		= overlay2fb_enable,
		.disable	= overlay2fb_disable,
		.setup		= overlay2fb_setup,
	पूर्ण,
पूर्ण;

अटल पूर्णांक overlayfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा pxafb_layer *ofb = container_of(info, काष्ठा pxafb_layer, fb);

	/* no support क्रम framebuffer console on overlay */
	अगर (user == 0)
		वापस -ENODEV;

	अगर (ofb->usage++ == 0) अणु
		/* unblank the base framebuffer */
		console_lock();
		fb_blank(&ofb->fbi->fb, FB_BLANK_UNBLANK);
		console_unlock();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक overlayfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा pxafb_layer *ofb = container_of(info, काष्ठा pxafb_layer, fb);

	अगर (ofb->usage == 1) अणु
		ofb->ops->disable(ofb);
		ofb->fb.var.height	= -1;
		ofb->fb.var.width	= -1;
		ofb->fb.var.xres = ofb->fb.var.xres_भव = 0;
		ofb->fb.var.yres = ofb->fb.var.yres_भव = 0;

		ofb->usage--;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक overlayfb_check_var(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_layer *ofb = container_of(info, काष्ठा pxafb_layer, fb);
	काष्ठा fb_var_screeninfo *base_var = &ofb->fbi->fb.var;
	पूर्णांक xpos, ypos, pक्रम, bpp;

	xpos = NONSTD_TO_XPOS(var->nonstd);
	ypos = NONSTD_TO_YPOS(var->nonstd);
	pक्रम = NONSTD_TO_PFOR(var->nonstd);

	bpp = pxafb_var_to_bpp(var);
	अगर (bpp < 0)
		वापस -EINVAL;

	/* no support क्रम YUV क्रमmat on overlay1 */
	अगर (ofb->id == OVERLAY1 && pक्रम != 0)
		वापस -EINVAL;

	/* क्रम YUV packed क्रमmats, bpp = 'minimum bpp of YUV components' */
	चयन (pक्रम) अणु
	हाल OVERLAY_FORMAT_RGB:
		bpp = pxafb_var_to_bpp(var);
		अगर (bpp < 0)
			वापस -EINVAL;

		pxafb_set_pixfmt(var, var_to_depth(var));
		अवरोध;
	हाल OVERLAY_FORMAT_YUV444_PACKED: bpp = 24; अवरोध;
	हाल OVERLAY_FORMAT_YUV444_PLANAR: bpp = 8; अवरोध;
	हाल OVERLAY_FORMAT_YUV422_PLANAR: bpp = 4; अवरोध;
	हाल OVERLAY_FORMAT_YUV420_PLANAR: bpp = 2; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* each line must start at a 32-bit word boundary */
	अगर ((xpos * bpp) % 32)
		वापस -EINVAL;

	/* xres must align on 32-bit word boundary */
	var->xres = roundup(var->xres * bpp, 32) / bpp;

	अगर ((xpos + var->xres > base_var->xres) ||
	    (ypos + var->yres > base_var->yres))
		वापस -EINVAL;

	var->xres_भव = var->xres;
	var->yres_भव = max(var->yres, var->yres_भव);
	वापस 0;
पूर्ण

अटल पूर्णांक overlayfb_check_video_memory(काष्ठा pxafb_layer *ofb)
अणु
	काष्ठा fb_var_screeninfo *var = &ofb->fb.var;
	पूर्णांक pक्रम = NONSTD_TO_PFOR(var->nonstd);
	पूर्णांक size, bpp = 0;

	चयन (pक्रम) अणु
	हाल OVERLAY_FORMAT_RGB: bpp = var->bits_per_pixel; अवरोध;
	हाल OVERLAY_FORMAT_YUV444_PACKED: bpp = 24; अवरोध;
	हाल OVERLAY_FORMAT_YUV444_PLANAR: bpp = 24; अवरोध;
	हाल OVERLAY_FORMAT_YUV422_PLANAR: bpp = 16; अवरोध;
	हाल OVERLAY_FORMAT_YUV420_PLANAR: bpp = 12; अवरोध;
	पूर्ण

	ofb->fb.fix.line_length = var->xres_भव * bpp / 8;

	size = PAGE_ALIGN(ofb->fb.fix.line_length * var->yres_भव);

	अगर (ofb->video_mem) अणु
		अगर (ofb->video_mem_size >= size)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक overlayfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_layer *ofb = container_of(info, काष्ठा pxafb_layer, fb);
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक xpos, ypos, pक्रम, bpp, ret;

	ret = overlayfb_check_video_memory(ofb);
	अगर (ret)
		वापस ret;

	bpp  = pxafb_var_to_bpp(var);
	xpos = NONSTD_TO_XPOS(var->nonstd);
	ypos = NONSTD_TO_YPOS(var->nonstd);
	pक्रम = NONSTD_TO_PFOR(var->nonstd);

	ofb->control[0] = OVLxC1_PPL(var->xres) | OVLxC1_LPO(var->yres) |
			  OVLxC1_BPP(bpp);
	ofb->control[1] = OVLxC2_XPOS(xpos) | OVLxC2_YPOS(ypos);

	अगर (ofb->id == OVERLAY2)
		ofb->control[1] |= OVL2C2_PFOR(pक्रम);

	ofb->ops->setup(ofb);
	ofb->ops->enable(ofb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops overlay_fb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_खोलो		= overlayfb_खोलो,
	.fb_release		= overlayfb_release,
	.fb_check_var 		= overlayfb_check_var,
	.fb_set_par		= overlayfb_set_par,
पूर्ण;

अटल व्योम init_pxafb_overlay(काष्ठा pxafb_info *fbi, काष्ठा pxafb_layer *ofb,
			       पूर्णांक id)
अणु
	प्र_लिखो(ofb->fb.fix.id, "overlay%d", id + 1);

	ofb->fb.fix.type		= FB_TYPE_PACKED_PIXELS;
	ofb->fb.fix.xpanstep		= 0;
	ofb->fb.fix.ypanstep		= 1;

	ofb->fb.var.activate		= FB_ACTIVATE_NOW;
	ofb->fb.var.height		= -1;
	ofb->fb.var.width		= -1;
	ofb->fb.var.vmode		= FB_VMODE_NONINTERLACED;

	ofb->fb.fbops			= &overlay_fb_ops;
	ofb->fb.flags			= FBINFO_FLAG_DEFAULT;
	ofb->fb.node			= -1;
	ofb->fb.pseuकरो_palette		= शून्य;

	ofb->id = id;
	ofb->ops = &ofb_ops[id];
	ofb->usage = 0;
	ofb->fbi = fbi;
	init_completion(&ofb->branch_करोne);
पूर्ण

अटल अंतरभूत पूर्णांक pxafb_overlay_supported(व्योम)
अणु
	अगर (cpu_is_pxa27x() || cpu_is_pxa3xx())
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pxafb_overlay_map_video_memory(काष्ठा pxafb_info *pxafb,
					  काष्ठा pxafb_layer *ofb)
अणु
	/* We assume that user will use at most video_mem_size क्रम overlay fb,
	 * anyway, it's useless to use 16bpp मुख्य plane and 24bpp overlay
	 */
	ofb->video_mem = alloc_pages_exact(PAGE_ALIGN(pxafb->video_mem_size),
		GFP_KERNEL | __GFP_ZERO);
	अगर (ofb->video_mem == शून्य)
		वापस -ENOMEM;

	ofb->video_mem_phys = virt_to_phys(ofb->video_mem);
	ofb->video_mem_size = PAGE_ALIGN(pxafb->video_mem_size);

	mutex_lock(&ofb->fb.mm_lock);
	ofb->fb.fix.smem_start	= ofb->video_mem_phys;
	ofb->fb.fix.smem_len	= pxafb->video_mem_size;
	mutex_unlock(&ofb->fb.mm_lock);

	ofb->fb.screen_base	= ofb->video_mem;

	वापस 0;
पूर्ण

अटल व्योम pxafb_overlay_init(काष्ठा pxafb_info *fbi)
अणु
	पूर्णांक i, ret;

	अगर (!pxafb_overlay_supported())
		वापस;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा pxafb_layer *ofb = &fbi->overlay[i];
		init_pxafb_overlay(fbi, ofb, i);
		ret = रेजिस्टर_framebuffer(&ofb->fb);
		अगर (ret) अणु
			dev_err(fbi->dev, "failed to register overlay %d\n", i);
			जारी;
		पूर्ण
		ret = pxafb_overlay_map_video_memory(fbi, ofb);
		अगर (ret) अणु
			dev_err(fbi->dev,
				"failed to map video memory for overlay %d\n",
				i);
			unरेजिस्टर_framebuffer(&ofb->fb);
			जारी;
		पूर्ण
		ofb->रेजिस्टरed = 1;
	पूर्ण

	/* mask all IU/BS/खातापूर्ण/SOF पूर्णांकerrupts */
	lcd_ग_लिखोl(fbi, LCCR5, ~0);

	pr_info("PXA Overlay driver loaded successfully!\n");
पूर्ण

अटल व्योम pxafb_overlay_निकास(काष्ठा pxafb_info *fbi)
अणु
	पूर्णांक i;

	अगर (!pxafb_overlay_supported())
		वापस;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा pxafb_layer *ofb = &fbi->overlay[i];
		अगर (ofb->रेजिस्टरed) अणु
			अगर (ofb->video_mem)
				मुक्त_pages_exact(ofb->video_mem,
					ofb->video_mem_size);
			unरेजिस्टर_framebuffer(&ofb->fb);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxafb_overlay_init(काष्ठा pxafb_info *fbi) अणुपूर्ण
अटल अंतरभूत व्योम pxafb_overlay_निकास(काष्ठा pxafb_info *fbi) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_FB_PXA_OVERLAY */

/*
 * Calculate the PCD value from the घड़ी rate (in picoseconds).
 * We take account of the PPCR घड़ी setting.
 * From PXA Developer's Manual:
 *
 *   PixelClock =      LCLK
 *                -------------
 *                2 ( PCD + 1 )
 *
 *   PCD =      LCLK
 *         ------------- - 1
 *         2(PixelClock)
 *
 * Where:
 *   LCLK = LCD/Memory Clock
 *   PCD = LCCR3[7:0]
 *
 * PixelClock here is in Hz जबतक the pixघड़ी argument given is the
 * period in picoseconds. Hence PixelClock = 1 / ( pixघड़ी * 10^-12 )
 *
 * The function get_lclk_frequency_10khz वापसs LCLK in units of
 * 10khz. Calling the result of this function lclk gives us the
 * following
 *
 *    PCD = (lclk * 10^4 ) * ( pixघड़ी * 10^-12 )
 *          -------------------------------------- - 1
 *                          2
 *
 * Factoring the 10^4 and 10^-12 out gives 10^-8 == 1 / 100000000 as used below.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_pcd(काष्ठा pxafb_info *fbi,
				   अचिन्हित पूर्णांक pixघड़ी)
अणु
	अचिन्हित दीर्घ दीर्घ pcd;

	/* FIXME: Need to take पूर्णांकo account Double Pixel Clock mode
	 * (DPC) bit? or perhaps set it based on the various घड़ी
	 * speeds */
	pcd = (अचिन्हित दीर्घ दीर्घ)(clk_get_rate(fbi->clk) / 10000);
	pcd *= pixघड़ी;
	करो_भाग(pcd, 100000000 * 2);
	/* no need क्रम this, since we should subtract 1 anyway. they cancel */
	/* pcd += 1; */ /* make up क्रम पूर्णांकeger math truncations */
	वापस (अचिन्हित पूर्णांक)pcd;
पूर्ण

/*
 * Some touchscreens need hsync inक्रमmation from the video driver to
 * function correctly. We export it here.  Note that 'hsync_time' and
 * the value वापसed from pxafb_get_hsync_समय() is the *reciprocal*
 * of the hsync period in seconds.
 */
अटल अंतरभूत व्योम set_hsync_समय(काष्ठा pxafb_info *fbi, अचिन्हित पूर्णांक pcd)
अणु
	अचिन्हित दीर्घ hसमय;

	अगर ((pcd == 0) || (fbi->fb.var.hsync_len == 0)) अणु
		fbi->hsync_समय = 0;
		वापस;
	पूर्ण

	hसमय = clk_get_rate(fbi->clk) / (pcd * fbi->fb.var.hsync_len);

	fbi->hsync_समय = hसमय;
पूर्ण

अचिन्हित दीर्घ pxafb_get_hsync_समय(काष्ठा device *dev)
अणु
	काष्ठा pxafb_info *fbi = dev_get_drvdata(dev);

	/* If display is blanked/suspended, hsync isn't active */
	अगर (!fbi || (fbi->state != C_ENABLE))
		वापस 0;

	वापस fbi->hsync_समय;
पूर्ण
EXPORT_SYMBOL(pxafb_get_hsync_समय);

अटल पूर्णांक setup_frame_dma(काष्ठा pxafb_info *fbi, पूर्णांक dma, पूर्णांक pal,
			   अचिन्हित दीर्घ start, माप_प्रकार size)
अणु
	काष्ठा pxafb_dma_descriptor *dma_desc, *pal_desc;
	अचिन्हित पूर्णांक dma_desc_off, pal_desc_off;

	अगर (dma < 0 || dma >= DMA_MAX * 2)
		वापस -EINVAL;

	dma_desc = &fbi->dma_buff->dma_desc[dma];
	dma_desc_off = दुरत्व(काष्ठा pxafb_dma_buff, dma_desc[dma]);

	dma_desc->fsadr = start;
	dma_desc->fidr  = 0;
	dma_desc->ldcmd = size;

	अगर (pal < 0 || pal >= PAL_MAX * 2) अणु
		dma_desc->fdadr = fbi->dma_buff_phys + dma_desc_off;
		fbi->fdadr[dma] = fbi->dma_buff_phys + dma_desc_off;
	पूर्ण अन्यथा अणु
		pal_desc = &fbi->dma_buff->pal_desc[pal];
		pal_desc_off = दुरत्व(काष्ठा pxafb_dma_buff, pal_desc[pal]);

		pal_desc->fsadr = fbi->dma_buff_phys + pal * PALETTE_SIZE;
		pal_desc->fidr  = 0;

		अगर ((fbi->lccr4 & LCCR4_PAL_FOR_MASK) == LCCR4_PAL_FOR_0)
			pal_desc->ldcmd = fbi->palette_size * माप(u16);
		अन्यथा
			pal_desc->ldcmd = fbi->palette_size * माप(u32);

		pal_desc->ldcmd |= LDCMD_PAL;

		/* flip back and क्रमth between palette and frame buffer */
		pal_desc->fdadr = fbi->dma_buff_phys + dma_desc_off;
		dma_desc->fdadr = fbi->dma_buff_phys + pal_desc_off;
		fbi->fdadr[dma] = fbi->dma_buff_phys + dma_desc_off;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम setup_base_frame(काष्ठा pxafb_info *fbi,
                             काष्ठा fb_var_screeninfo *var,
                             पूर्णांक branch)
अणु
	काष्ठा fb_fix_screeninfo *fix = &fbi->fb.fix;
	पूर्णांक nbytes, dma, pal, bpp = var->bits_per_pixel;
	अचिन्हित दीर्घ offset;

	dma = DMA_BASE + (branch ? DMA_MAX : 0);
	pal = (bpp >= 16) ? PAL_NONE : PAL_BASE + (branch ? PAL_MAX : 0);

	nbytes = fix->line_length * var->yres;
	offset = fix->line_length * var->yoffset + fbi->video_mem_phys;

	अगर (fbi->lccr0 & LCCR0_SDS) अणु
		nbytes = nbytes / 2;
		setup_frame_dma(fbi, dma + 1, PAL_NONE, offset + nbytes, nbytes);
	पूर्ण

	setup_frame_dma(fbi, dma, pal, offset, nbytes);
पूर्ण

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
अटल पूर्णांक setup_smart_dma(काष्ठा pxafb_info *fbi)
अणु
	काष्ठा pxafb_dma_descriptor *dma_desc;
	अचिन्हित दीर्घ dma_desc_off, cmd_buff_off;

	dma_desc = &fbi->dma_buff->dma_desc[DMA_CMD];
	dma_desc_off = दुरत्व(काष्ठा pxafb_dma_buff, dma_desc[DMA_CMD]);
	cmd_buff_off = दुरत्व(काष्ठा pxafb_dma_buff, cmd_buff);

	dma_desc->fdadr = fbi->dma_buff_phys + dma_desc_off;
	dma_desc->fsadr = fbi->dma_buff_phys + cmd_buff_off;
	dma_desc->fidr  = 0;
	dma_desc->ldcmd = fbi->n_smart_cmds * माप(uपूर्णांक16_t);

	fbi->fdadr[DMA_CMD] = dma_desc->fdadr;
	वापस 0;
पूर्ण

पूर्णांक pxafb_smart_flush(काष्ठा fb_info *info)
अणु
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);
	uपूर्णांक32_t prsr;
	पूर्णांक ret = 0;

	/* disable controller until all रेजिस्टरs are set up */
	lcd_ग_लिखोl(fbi, LCCR0, fbi->reg_lccr0 & ~LCCR0_ENB);

	/* 1. make it an even number of commands to align on 32-bit boundary
	 * 2. add the पूर्णांकerrupt command to the end of the chain so we can
	 *    keep track of the end of the transfer
	 */

	जबतक (fbi->n_smart_cmds & 1)
		fbi->smart_cmds[fbi->n_smart_cmds++] = SMART_CMD_NOOP;

	fbi->smart_cmds[fbi->n_smart_cmds++] = SMART_CMD_INTERRUPT;
	fbi->smart_cmds[fbi->n_smart_cmds++] = SMART_CMD_WAIT_FOR_VSYNC;
	setup_smart_dma(fbi);

	/* जारी to execute next command */
	prsr = lcd_पढ़ोl(fbi, PRSR) | PRSR_ST_OK | PRSR_CON_NT;
	lcd_ग_लिखोl(fbi, PRSR, prsr);

	/* stop the processor in हाल it executed "wait for sync" cmd */
	lcd_ग_लिखोl(fbi, CMDCR, 0x0001);

	/* करोn't send पूर्णांकerrupts क्रम fअगरo underruns on channel 6 */
	lcd_ग_लिखोl(fbi, LCCR5, LCCR5_IUM(6));

	lcd_ग_लिखोl(fbi, LCCR1, fbi->reg_lccr1);
	lcd_ग_लिखोl(fbi, LCCR2, fbi->reg_lccr2);
	lcd_ग_लिखोl(fbi, LCCR3, fbi->reg_lccr3);
	lcd_ग_लिखोl(fbi, LCCR4, fbi->reg_lccr4);
	lcd_ग_लिखोl(fbi, FDADR0, fbi->fdadr[0]);
	lcd_ग_लिखोl(fbi, FDADR6, fbi->fdadr[6]);

	/* begin sending */
	lcd_ग_लिखोl(fbi, LCCR0, fbi->reg_lccr0 | LCCR0_ENB);

	अगर (रुको_क्रम_completion_समयout(&fbi->command_करोne, HZ/2) == 0) अणु
		pr_warn("%s: timeout waiting for command done\n", __func__);
		ret = -ETIMEDOUT;
	पूर्ण

	/* quick disable */
	prsr = lcd_पढ़ोl(fbi, PRSR) & ~(PRSR_ST_OK | PRSR_CON_NT);
	lcd_ग_लिखोl(fbi, PRSR, prsr);
	lcd_ग_लिखोl(fbi, LCCR0, fbi->reg_lccr0 & ~LCCR0_ENB);
	lcd_ग_लिखोl(fbi, FDADR6, 0);
	fbi->n_smart_cmds = 0;
	वापस ret;
पूर्ण

पूर्णांक pxafb_smart_queue(काष्ठा fb_info *info, uपूर्णांक16_t *cmds, पूर्णांक n_cmds)
अणु
	पूर्णांक i;
	काष्ठा pxafb_info *fbi = container_of(info, काष्ठा pxafb_info, fb);

	क्रम (i = 0; i < n_cmds; i++, cmds++) अणु
		/* अगर it is a software delay, flush and delay */
		अगर ((*cmds & 0xff00) == SMART_CMD_DELAY) अणु
			pxafb_smart_flush(info);
			mdelay(*cmds & 0xff);
			जारी;
		पूर्ण

		/* leave 2 commands क्रम INTERRUPT and WAIT_FOR_SYNC */
		अगर (fbi->n_smart_cmds == CMD_BUFF_SIZE - 8)
			pxafb_smart_flush(info);

		fbi->smart_cmds[fbi->n_smart_cmds++] = *cmds;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __smart_timing(अचिन्हित समय_ns, अचिन्हित दीर्घ lcd_clk)
अणु
	अचिन्हित पूर्णांक t = (समय_ns * (lcd_clk / 1000000) / 1000);
	वापस (t == 0) ? 1 : t;
पूर्ण

अटल व्योम setup_smart_timing(काष्ठा pxafb_info *fbi,
				काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा pxafb_mach_info *inf = fbi->inf;
	काष्ठा pxafb_mode_info *mode = &inf->modes[0];
	अचिन्हित दीर्घ lclk = clk_get_rate(fbi->clk);
	अचिन्हित t1, t2, t3, t4;

	t1 = max(mode->a0csrd_set_hld, mode->a0cswr_set_hld);
	t2 = max(mode->rd_pulse_width, mode->wr_pulse_width);
	t3 = mode->op_hold_समय;
	t4 = mode->cmd_inh_समय;

	fbi->reg_lccr1 =
		LCCR1_DisWdth(var->xres) |
		LCCR1_BegLnDel(__smart_timing(t1, lclk)) |
		LCCR1_EndLnDel(__smart_timing(t2, lclk)) |
		LCCR1_HorSnchWdth(__smart_timing(t3, lclk));

	fbi->reg_lccr2 = LCCR2_DisHght(var->yres);
	fbi->reg_lccr3 = fbi->lccr3 | LCCR3_PixClkDiv(__smart_timing(t4, lclk));
	fbi->reg_lccr3 |= (var->sync & FB_SYNC_HOR_HIGH_ACT) ? LCCR3_HSP : 0;
	fbi->reg_lccr3 |= (var->sync & FB_SYNC_VERT_HIGH_ACT) ? LCCR3_VSP : 0;

	/* FIXME: make this configurable */
	fbi->reg_cmdcr = 1;
पूर्ण

अटल पूर्णांक pxafb_smart_thपढ़ो(व्योम *arg)
अणु
	काष्ठा pxafb_info *fbi = arg;
	काष्ठा pxafb_mach_info *inf = fbi->inf;

	अगर (!inf->smart_update) अणु
		pr_err("%s: not properly initialized, thread terminated\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	pr_debug("%s(): task starting\n", __func__);

	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु

		अगर (try_to_मुक्तze())
			जारी;

		mutex_lock(&fbi->ctrlr_lock);

		अगर (fbi->state == C_ENABLE) अणु
			inf->smart_update(&fbi->fb);
			complete(&fbi->refresh_करोne);
		पूर्ण

		mutex_unlock(&fbi->ctrlr_lock);

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(30));
	पूर्ण

	pr_debug("%s(): task ending\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक pxafb_smart_init(काष्ठा pxafb_info *fbi)
अणु
	अगर (!(fbi->lccr0 & LCCR0_LCDT))
		वापस 0;

	fbi->smart_cmds = (uपूर्णांक16_t *) fbi->dma_buff->cmd_buff;
	fbi->n_smart_cmds = 0;

	init_completion(&fbi->command_करोne);
	init_completion(&fbi->refresh_करोne);

	fbi->smart_thपढ़ो = kthपढ़ो_run(pxafb_smart_thपढ़ो, fbi,
					"lcd_refresh");
	अगर (IS_ERR(fbi->smart_thपढ़ो)) अणु
		pr_err("%s: unable to create kernel thread\n", __func__);
		वापस PTR_ERR(fbi->smart_thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pxafb_smart_init(काष्ठा pxafb_info *fbi) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_FB_PXA_SMARTPANEL */

अटल व्योम setup_parallel_timing(काष्ठा pxafb_info *fbi,
				  काष्ठा fb_var_screeninfo *var)
अणु
	अचिन्हित पूर्णांक lines_per_panel, pcd = get_pcd(fbi, var->pixघड़ी);

	fbi->reg_lccr1 =
		LCCR1_DisWdth(var->xres) +
		LCCR1_HorSnchWdth(var->hsync_len) +
		LCCR1_BegLnDel(var->left_margin) +
		LCCR1_EndLnDel(var->right_margin);

	/*
	 * If we have a dual scan LCD, we need to halve
	 * the YRES parameter.
	 */
	lines_per_panel = var->yres;
	अगर ((fbi->lccr0 & LCCR0_SDS) == LCCR0_Dual)
		lines_per_panel /= 2;

	fbi->reg_lccr2 =
		LCCR2_DisHght(lines_per_panel) +
		LCCR2_VrtSnchWdth(var->vsync_len) +
		LCCR2_BegFrmDel(var->upper_margin) +
		LCCR2_EndFrmDel(var->lower_margin);

	fbi->reg_lccr3 = fbi->lccr3 |
		(var->sync & FB_SYNC_HOR_HIGH_ACT ?
		 LCCR3_HorSnchH : LCCR3_HorSnchL) |
		(var->sync & FB_SYNC_VERT_HIGH_ACT ?
		 LCCR3_VrtSnchH : LCCR3_VrtSnchL);

	अगर (pcd) अणु
		fbi->reg_lccr3 |= LCCR3_PixClkDiv(pcd);
		set_hsync_समय(fbi, pcd);
	पूर्ण
पूर्ण

/*
 * pxafb_activate_var():
 *	Configures LCD Controller based on entries in var parameter.
 *	Settings are only written to the controller अगर changes were made.
 */
अटल पूर्णांक pxafb_activate_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा pxafb_info *fbi)
अणु
	u_दीर्घ flags;

	/* Update shaकरोw copy atomically */
	local_irq_save(flags);

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
	अगर (fbi->lccr0 & LCCR0_LCDT)
		setup_smart_timing(fbi, var);
	अन्यथा
#पूर्ण_अगर
		setup_parallel_timing(fbi, var);

	setup_base_frame(fbi, var, 0);

	fbi->reg_lccr0 = fbi->lccr0 |
		(LCCR0_LDM | LCCR0_SFM | LCCR0_IUM | LCCR0_EFM |
		 LCCR0_QDM | LCCR0_BM  | LCCR0_OUM);

	fbi->reg_lccr3 |= pxafb_var_to_lccr3(var);

	fbi->reg_lccr4 = lcd_पढ़ोl(fbi, LCCR4) & ~LCCR4_PAL_FOR_MASK;
	fbi->reg_lccr4 |= (fbi->lccr4 & LCCR4_PAL_FOR_MASK);
	local_irq_restore(flags);

	/*
	 * Only update the रेजिस्टरs अगर the controller is enabled
	 * and something has changed.
	 */
	अगर ((lcd_पढ़ोl(fbi, LCCR0) != fbi->reg_lccr0) ||
	    (lcd_पढ़ोl(fbi, LCCR1) != fbi->reg_lccr1) ||
	    (lcd_पढ़ोl(fbi, LCCR2) != fbi->reg_lccr2) ||
	    (lcd_पढ़ोl(fbi, LCCR3) != fbi->reg_lccr3) ||
	    (lcd_पढ़ोl(fbi, LCCR4) != fbi->reg_lccr4) ||
	    (lcd_पढ़ोl(fbi, FDADR0) != fbi->fdadr[0]) ||
	    ((fbi->lccr0 & LCCR0_SDS) &&
	    (lcd_पढ़ोl(fbi, FDADR1) != fbi->fdadr[1])))
		pxafb_schedule_work(fbi, C_REENABLE);

	वापस 0;
पूर्ण

/*
 * NOTE!  The following functions are purely helpers क्रम set_ctrlr_state.
 * Do not call them directly; set_ctrlr_state करोes the correct serialisation
 * to ensure that things happen in the right way 100% of समय समय.
 *	-- rmk
 */
अटल अंतरभूत व्योम __pxafb_backlight_घातer(काष्ठा pxafb_info *fbi, पूर्णांक on)
अणु
	pr_debug("pxafb: backlight o%s\n", on ? "n" : "ff");

	अगर (fbi->backlight_घातer)
		fbi->backlight_घातer(on);
पूर्ण

अटल अंतरभूत व्योम __pxafb_lcd_घातer(काष्ठा pxafb_info *fbi, पूर्णांक on)
अणु
	pr_debug("pxafb: LCD power o%s\n", on ? "n" : "ff");

	अगर (fbi->lcd_घातer)
		fbi->lcd_घातer(on, &fbi->fb.var);

	अगर (fbi->lcd_supply && fbi->lcd_supply_enabled != on) अणु
		पूर्णांक ret;

		अगर (on)
			ret = regulator_enable(fbi->lcd_supply);
		अन्यथा
			ret = regulator_disable(fbi->lcd_supply);

		अगर (ret < 0)
			pr_warn("Unable to %s LCD supply regulator: %d\n",
				on ? "enable" : "disable", ret);
		अन्यथा
			fbi->lcd_supply_enabled = on;
	पूर्ण
पूर्ण

अटल व्योम pxafb_enable_controller(काष्ठा pxafb_info *fbi)
अणु
	pr_debug("pxafb: Enabling LCD controller\n");
	pr_debug("fdadr0 0x%08x\n", (अचिन्हित पूर्णांक) fbi->fdadr[0]);
	pr_debug("fdadr1 0x%08x\n", (अचिन्हित पूर्णांक) fbi->fdadr[1]);
	pr_debug("reg_lccr0 0x%08x\n", (अचिन्हित पूर्णांक) fbi->reg_lccr0);
	pr_debug("reg_lccr1 0x%08x\n", (अचिन्हित पूर्णांक) fbi->reg_lccr1);
	pr_debug("reg_lccr2 0x%08x\n", (अचिन्हित पूर्णांक) fbi->reg_lccr2);
	pr_debug("reg_lccr3 0x%08x\n", (अचिन्हित पूर्णांक) fbi->reg_lccr3);

	/* enable LCD controller घड़ी */
	अगर (clk_prepare_enable(fbi->clk)) अणु
		pr_err("%s: Failed to prepare clock\n", __func__);
		वापस;
	पूर्ण

	अगर (fbi->lccr0 & LCCR0_LCDT)
		वापस;

	/* Sequence from 11.7.10 */
	lcd_ग_लिखोl(fbi, LCCR4, fbi->reg_lccr4);
	lcd_ग_लिखोl(fbi, LCCR3, fbi->reg_lccr3);
	lcd_ग_लिखोl(fbi, LCCR2, fbi->reg_lccr2);
	lcd_ग_लिखोl(fbi, LCCR1, fbi->reg_lccr1);
	lcd_ग_लिखोl(fbi, LCCR0, fbi->reg_lccr0 & ~LCCR0_ENB);

	lcd_ग_लिखोl(fbi, FDADR0, fbi->fdadr[0]);
	अगर (fbi->lccr0 & LCCR0_SDS)
		lcd_ग_लिखोl(fbi, FDADR1, fbi->fdadr[1]);
	lcd_ग_लिखोl(fbi, LCCR0, fbi->reg_lccr0 | LCCR0_ENB);
पूर्ण

अटल व्योम pxafb_disable_controller(काष्ठा pxafb_info *fbi)
अणु
	uपूर्णांक32_t lccr0;

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
	अगर (fbi->lccr0 & LCCR0_LCDT) अणु
		रुको_क्रम_completion_समयout(&fbi->refresh_करोne,
				msecs_to_jअगरfies(200));
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Clear LCD Status Register */
	lcd_ग_लिखोl(fbi, LCSR, 0xffffffff);

	lccr0 = lcd_पढ़ोl(fbi, LCCR0) & ~LCCR0_LDM;
	lcd_ग_लिखोl(fbi, LCCR0, lccr0);
	lcd_ग_लिखोl(fbi, LCCR0, lccr0 | LCCR0_DIS);

	रुको_क्रम_completion_समयout(&fbi->disable_करोne, msecs_to_jअगरfies(200));

	/* disable LCD controller घड़ी */
	clk_disable_unprepare(fbi->clk);
पूर्ण

/*
 *  pxafb_handle_irq: Handle 'LCD DONE' पूर्णांकerrupts.
 */
अटल irqवापस_t pxafb_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxafb_info *fbi = dev_id;
	अचिन्हित पूर्णांक lccr0, lcsr;

	lcsr = lcd_पढ़ोl(fbi, LCSR);
	अगर (lcsr & LCSR_LDD) अणु
		lccr0 = lcd_पढ़ोl(fbi, LCCR0);
		lcd_ग_लिखोl(fbi, LCCR0, lccr0 | LCCR0_LDM);
		complete(&fbi->disable_करोne);
	पूर्ण

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
	अगर (lcsr & LCSR_CMD_INT)
		complete(&fbi->command_करोne);
#पूर्ण_अगर
	lcd_ग_लिखोl(fbi, LCSR, lcsr);

#अगर_घोषित CONFIG_FB_PXA_OVERLAY
	अणु
		अचिन्हित पूर्णांक lcsr1 = lcd_पढ़ोl(fbi, LCSR1);
		अगर (lcsr1 & LCSR1_BS(1))
			complete(&fbi->overlay[0].branch_करोne);

		अगर (lcsr1 & LCSR1_BS(2))
			complete(&fbi->overlay[1].branch_करोne);

		lcd_ग_लिखोl(fbi, LCSR1, lcsr1);
	पूर्ण
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function must be called from task context only, since it will
 * sleep when disabling the LCD controller, or अगर we get two contending
 * processes trying to alter state.
 */
अटल व्योम set_ctrlr_state(काष्ठा pxafb_info *fbi, u_पूर्णांक state)
अणु
	u_पूर्णांक old_state;

	mutex_lock(&fbi->ctrlr_lock);

	old_state = fbi->state;

	/*
	 * Hack around fbcon initialisation.
	 */
	अगर (old_state == C_STARTUP && state == C_REENABLE)
		state = C_ENABLE;

	चयन (state) अणु
	हाल C_DISABLE_CLKCHANGE:
		/*
		 * Disable controller क्रम घड़ी change.  If the
		 * controller is alपढ़ोy disabled, then करो nothing.
		 */
		अगर (old_state != C_DISABLE && old_state != C_DISABLE_PM) अणु
			fbi->state = state;
			/* TODO __pxafb_lcd_घातer(fbi, 0); */
			pxafb_disable_controller(fbi);
		पूर्ण
		अवरोध;

	हाल C_DISABLE_PM:
	हाल C_DISABLE:
		/*
		 * Disable controller
		 */
		अगर (old_state != C_DISABLE) अणु
			fbi->state = state;
			__pxafb_backlight_घातer(fbi, 0);
			__pxafb_lcd_घातer(fbi, 0);
			अगर (old_state != C_DISABLE_CLKCHANGE)
				pxafb_disable_controller(fbi);
		पूर्ण
		अवरोध;

	हाल C_ENABLE_CLKCHANGE:
		/*
		 * Enable the controller after घड़ी change.  Only
		 * करो this अगर we were disabled क्रम the घड़ी change.
		 */
		अगर (old_state == C_DISABLE_CLKCHANGE) अणु
			fbi->state = C_ENABLE;
			pxafb_enable_controller(fbi);
			/* TODO __pxafb_lcd_घातer(fbi, 1); */
		पूर्ण
		अवरोध;

	हाल C_REENABLE:
		/*
		 * Re-enable the controller only अगर it was alपढ़ोy
		 * enabled.  This is so we reprogram the control
		 * रेजिस्टरs.
		 */
		अगर (old_state == C_ENABLE) अणु
			__pxafb_lcd_घातer(fbi, 0);
			pxafb_disable_controller(fbi);
			pxafb_enable_controller(fbi);
			__pxafb_lcd_घातer(fbi, 1);
		पूर्ण
		अवरोध;

	हाल C_ENABLE_PM:
		/*
		 * Re-enable the controller after PM.  This is not
		 * perfect - think about the हाल where we were करोing
		 * a घड़ी change, and we suspended half-way through.
		 */
		अगर (old_state != C_DISABLE_PM)
			अवरोध;
		fallthrough;

	हाल C_ENABLE:
		/*
		 * Power up the LCD screen, enable controller, and
		 * turn on the backlight.
		 */
		अगर (old_state != C_ENABLE) अणु
			fbi->state = C_ENABLE;
			pxafb_enable_controller(fbi);
			__pxafb_lcd_घातer(fbi, 1);
			__pxafb_backlight_घातer(fbi, 1);
		पूर्ण
		अवरोध;
	पूर्ण
	mutex_unlock(&fbi->ctrlr_lock);
पूर्ण

/*
 * Our LCD controller task (which is called when we blank or unblank)
 * via keventd.
 */
अटल व्योम pxafb_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pxafb_info *fbi =
		container_of(work, काष्ठा pxafb_info, task);
	u_पूर्णांक state = xchg(&fbi->task_state, -1);

	set_ctrlr_state(fbi, state);
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
/*
 * CPU घड़ी speed change handler.  We need to adjust the LCD timing
 * parameters when the CPU घड़ी is adjusted by the घातer management
 * subप्रणाली.
 *
 * TODO: Determine why f->new != 10*get_lclk_frequency_10khz()
 */
अटल पूर्णांक
pxafb_freq_transition(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा pxafb_info *fbi = TO_INF(nb, freq_transition);
	/* TODO काष्ठा cpufreq_freqs *f = data; */
	u_पूर्णांक pcd;

	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
#अगर_घोषित CONFIG_FB_PXA_OVERLAY
		अगर (!(fbi->overlay[0].usage || fbi->overlay[1].usage))
#पूर्ण_अगर
			set_ctrlr_state(fbi, C_DISABLE_CLKCHANGE);
		अवरोध;

	हाल CPUFREQ_POSTCHANGE:
		pcd = get_pcd(fbi, fbi->fb.var.pixघड़ी);
		set_hsync_समय(fbi, pcd);
		fbi->reg_lccr3 = (fbi->reg_lccr3 & ~0xff) |
				  LCCR3_PixClkDiv(pcd);
		set_ctrlr_state(fbi, C_ENABLE_CLKCHANGE);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
/*
 * Power management hooks.  Note that we won't be called from IRQ context,
 * unlike the blank functions above, so we may sleep.
 */
अटल पूर्णांक pxafb_suspend(काष्ठा device *dev)
अणु
	काष्ठा pxafb_info *fbi = dev_get_drvdata(dev);

	set_ctrlr_state(fbi, C_DISABLE_PM);
	वापस 0;
पूर्ण

अटल पूर्णांक pxafb_resume(काष्ठा device *dev)
अणु
	काष्ठा pxafb_info *fbi = dev_get_drvdata(dev);

	set_ctrlr_state(fbi, C_ENABLE_PM);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pxafb_pm_ops = अणु
	.suspend	= pxafb_suspend,
	.resume		= pxafb_resume,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक pxafb_init_video_memory(काष्ठा pxafb_info *fbi)
अणु
	पूर्णांक size = PAGE_ALIGN(fbi->video_mem_size);

	fbi->video_mem = alloc_pages_exact(size, GFP_KERNEL | __GFP_ZERO);
	अगर (fbi->video_mem == शून्य)
		वापस -ENOMEM;

	fbi->video_mem_phys = virt_to_phys(fbi->video_mem);
	fbi->video_mem_size = size;

	fbi->fb.fix.smem_start	= fbi->video_mem_phys;
	fbi->fb.fix.smem_len	= fbi->video_mem_size;
	fbi->fb.screen_base	= fbi->video_mem;

	वापस fbi->video_mem ? 0 : -ENOMEM;
पूर्ण

अटल व्योम pxafb_decode_mach_info(काष्ठा pxafb_info *fbi,
				   काष्ठा pxafb_mach_info *inf)
अणु
	अचिन्हित पूर्णांक lcd_conn = inf->lcd_conn;
	काष्ठा pxafb_mode_info *m;
	पूर्णांक i;

	fbi->cmap_inverse	= inf->cmap_inverse;
	fbi->cmap_अटल	= inf->cmap_अटल;
	fbi->lccr4 		= inf->lccr4;

	चयन (lcd_conn & LCD_TYPE_MASK) अणु
	हाल LCD_TYPE_MONO_STN:
		fbi->lccr0 = LCCR0_CMS;
		अवरोध;
	हाल LCD_TYPE_MONO_DSTN:
		fbi->lccr0 = LCCR0_CMS | LCCR0_SDS;
		अवरोध;
	हाल LCD_TYPE_COLOR_STN:
		fbi->lccr0 = 0;
		अवरोध;
	हाल LCD_TYPE_COLOR_DSTN:
		fbi->lccr0 = LCCR0_SDS;
		अवरोध;
	हाल LCD_TYPE_COLOR_TFT:
		fbi->lccr0 = LCCR0_PAS;
		अवरोध;
	हाल LCD_TYPE_SMART_PANEL:
		fbi->lccr0 = LCCR0_LCDT | LCCR0_PAS;
		अवरोध;
	शेष:
		/* fall back to backward compatibility way */
		fbi->lccr0 = inf->lccr0;
		fbi->lccr3 = inf->lccr3;
		जाओ decode_mode;
	पूर्ण

	अगर (lcd_conn == LCD_MONO_STN_8BPP)
		fbi->lccr0 |= LCCR0_DPD;

	fbi->lccr0 |= (lcd_conn & LCD_ALTERNATE_MAPPING) ? LCCR0_LDDALT : 0;

	fbi->lccr3 = LCCR3_Acb((inf->lcd_conn >> 10) & 0xff);
	fbi->lccr3 |= (lcd_conn & LCD_BIAS_ACTIVE_LOW) ? LCCR3_OEP : 0;
	fbi->lccr3 |= (lcd_conn & LCD_PCLK_EDGE_FALL)  ? LCCR3_PCP : 0;

decode_mode:
	pxafb_seपंचांगode(&fbi->fb.var, &inf->modes[0]);

	/* decide video memory size as follows:
	 * 1. शेष to mode of maximum resolution
	 * 2. allow platक्रमm to override
	 * 3. allow module parameter to override
	 */
	क्रम (i = 0, m = &inf->modes[0]; i < inf->num_modes; i++, m++)
		fbi->video_mem_size = max_t(माप_प्रकार, fbi->video_mem_size,
				m->xres * m->yres * m->bpp / 8);

	अगर (inf->video_mem_size > fbi->video_mem_size)
		fbi->video_mem_size = inf->video_mem_size;

	अगर (video_mem_size > fbi->video_mem_size)
		fbi->video_mem_size = video_mem_size;
पूर्ण

अटल काष्ठा pxafb_info *pxafb_init_fbinfo(काष्ठा device *dev,
					    काष्ठा pxafb_mach_info *inf)
अणु
	काष्ठा pxafb_info *fbi;
	व्योम *addr;

	/* Alloc the pxafb_info and pseuकरो_palette in one step */
	fbi = devm_kzalloc(dev, माप(काष्ठा pxafb_info) + माप(u32) * 16,
			   GFP_KERNEL);
	अगर (!fbi)
		वापस ERR_PTR(-ENOMEM);

	fbi->dev = dev;
	fbi->inf = inf;

	fbi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(fbi->clk))
		वापस ERR_CAST(fbi->clk);

	म_नकल(fbi->fb.fix.id, PXA_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.var.nonstd	= 0;
	fbi->fb.var.activate	= FB_ACTIVATE_NOW;
	fbi->fb.var.height	= -1;
	fbi->fb.var.width	= -1;
	fbi->fb.var.accel_flags	= FB_ACCELF_TEXT;
	fbi->fb.var.vmode	= FB_VMODE_NONINTERLACED;

	fbi->fb.fbops		= &pxafb_ops;
	fbi->fb.flags		= FBINFO_DEFAULT;
	fbi->fb.node		= -1;

	addr = fbi;
	addr = addr + माप(काष्ठा pxafb_info);
	fbi->fb.pseuकरो_palette	= addr;

	fbi->state		= C_STARTUP;
	fbi->task_state		= (u_अक्षर)-1;

	pxafb_decode_mach_info(fbi, inf);

#अगर_घोषित CONFIG_FB_PXA_OVERLAY
	/* place overlay(s) on top of base */
	अगर (pxafb_overlay_supported())
		fbi->lccr0 |= LCCR0_OUC;
#पूर्ण_अगर

	init_रुकोqueue_head(&fbi->ctrlr_रुको);
	INIT_WORK(&fbi->task, pxafb_task);
	mutex_init(&fbi->ctrlr_lock);
	init_completion(&fbi->disable_करोne);

	वापस fbi;
पूर्ण

#अगर_घोषित CONFIG_FB_PXA_PARAMETERS
अटल पूर्णांक parse_opt_mode(काष्ठा device *dev, स्थिर अक्षर *this_opt,
			  काष्ठा pxafb_mach_info *inf)
अणु
	स्थिर अक्षर *name = this_opt+5;
	अचिन्हित पूर्णांक namelen = म_माप(name);
	पूर्णांक res_specअगरied = 0, bpp_specअगरied = 0;
	अचिन्हित पूर्णांक xres = 0, yres = 0, bpp = 0;
	पूर्णांक yres_specअगरied = 0;
	पूर्णांक i;
	क्रम (i = namelen-1; i >= 0; i--) अणु
		चयन (name[i]) अणु
		हाल '-':
			namelen = i;
			अगर (!bpp_specअगरied && !yres_specअगरied) अणु
				bpp = simple_म_से_अदीर्घ(&name[i+1], शून्य, 0);
				bpp_specअगरied = 1;
			पूर्ण अन्यथा
				जाओ करोne;
			अवरोध;
		हाल 'x':
			अगर (!yres_specअगरied) अणु
				yres = simple_म_से_अदीर्घ(&name[i+1], शून्य, 0);
				yres_specअगरied = 1;
			पूर्ण अन्यथा
				जाओ करोne;
			अवरोध;
		हाल '0' ... '9':
			अवरोध;
		शेष:
			जाओ करोne;
		पूर्ण
	पूर्ण
	अगर (i < 0 && yres_specअगरied) अणु
		xres = simple_म_से_अदीर्घ(name, शून्य, 0);
		res_specअगरied = 1;
	पूर्ण
करोne:
	अगर (res_specअगरied) अणु
		dev_info(dev, "overriding resolution: %dx%d\n", xres, yres);
		inf->modes[0].xres = xres; inf->modes[0].yres = yres;
	पूर्ण
	अगर (bpp_specअगरied)
		चयन (bpp) अणु
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
		हाल 16:
			inf->modes[0].bpp = bpp;
			dev_info(dev, "overriding bit depth: %d\n", bpp);
			अवरोध;
		शेष:
			dev_err(dev, "Depth %d is not valid\n", bpp);
			वापस -EINVAL;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_opt(काष्ठा device *dev, अक्षर *this_opt,
		     काष्ठा pxafb_mach_info *inf)
अणु
	काष्ठा pxafb_mode_info *mode = &inf->modes[0];
	अक्षर s[64];

	s[0] = '\0';

	अगर (!म_भेदन(this_opt, "vmem:", 5)) अणु
		video_mem_size = memparse(this_opt + 5, शून्य);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "mode:", 5)) अणु
		वापस parse_opt_mode(dev, this_opt, inf);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "pixclock:", 9)) अणु
		mode->pixघड़ी = simple_म_से_अदीर्घ(this_opt+9, शून्य, 0);
		प्र_लिखो(s, "pixclock: %ld\n", mode->pixघड़ी);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "left:", 5)) अणु
		mode->left_margin = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		प्र_लिखो(s, "left: %u\n", mode->left_margin);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "right:", 6)) अणु
		mode->right_margin = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		प्र_लिखो(s, "right: %u\n", mode->right_margin);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "upper:", 6)) अणु
		mode->upper_margin = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		प्र_लिखो(s, "upper: %u\n", mode->upper_margin);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "lower:", 6)) अणु
		mode->lower_margin = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		प्र_लिखो(s, "lower: %u\n", mode->lower_margin);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "hsynclen:", 9)) अणु
		mode->hsync_len = simple_म_से_अदीर्घ(this_opt+9, शून्य, 0);
		प्र_लिखो(s, "hsynclen: %u\n", mode->hsync_len);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "vsynclen:", 9)) अणु
		mode->vsync_len = simple_म_से_अदीर्घ(this_opt+9, शून्य, 0);
		प्र_लिखो(s, "vsynclen: %u\n", mode->vsync_len);
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "hsync:", 6)) अणु
		अगर (simple_म_से_अदीर्घ(this_opt+6, शून्य, 0) == 0) अणु
			प्र_लिखो(s, "hsync: Active Low\n");
			mode->sync &= ~FB_SYNC_HOR_HIGH_ACT;
		पूर्ण अन्यथा अणु
			प्र_लिखो(s, "hsync: Active High\n");
			mode->sync |= FB_SYNC_HOR_HIGH_ACT;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "vsync:", 6)) अणु
		अगर (simple_म_से_अदीर्घ(this_opt+6, शून्य, 0) == 0) अणु
			प्र_लिखो(s, "vsync: Active Low\n");
			mode->sync &= ~FB_SYNC_VERT_HIGH_ACT;
		पूर्ण अन्यथा अणु
			प्र_लिखो(s, "vsync: Active High\n");
			mode->sync |= FB_SYNC_VERT_HIGH_ACT;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "dpc:", 4)) अणु
		अगर (simple_म_से_अदीर्घ(this_opt+4, शून्य, 0) == 0) अणु
			प्र_लिखो(s, "double pixel clock: false\n");
			inf->lccr3 &= ~LCCR3_DPC;
		पूर्ण अन्यथा अणु
			प्र_लिखो(s, "double pixel clock: true\n");
			inf->lccr3 |= LCCR3_DPC;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "outputen:", 9)) अणु
		अगर (simple_म_से_अदीर्घ(this_opt+9, शून्य, 0) == 0) अणु
			प्र_लिखो(s, "output enable: active low\n");
			inf->lccr3 = (inf->lccr3 & ~LCCR3_OEP) | LCCR3_OutEnL;
		पूर्ण अन्यथा अणु
			प्र_लिखो(s, "output enable: active high\n");
			inf->lccr3 = (inf->lccr3 & ~LCCR3_OEP) | LCCR3_OutEnH;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "pixclockpol:", 12)) अणु
		अगर (simple_म_से_अदीर्घ(this_opt+12, शून्य, 0) == 0) अणु
			प्र_लिखो(s, "pixel clock polarity: falling edge\n");
			inf->lccr3 = (inf->lccr3 & ~LCCR3_PCP) | LCCR3_PixFlEdg;
		पूर्ण अन्यथा अणु
			प्र_लिखो(s, "pixel clock polarity: rising edge\n");
			inf->lccr3 = (inf->lccr3 & ~LCCR3_PCP) | LCCR3_PixRsEdg;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "color", 5)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_CMS) | LCCR0_Color;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "mono", 4)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_CMS) | LCCR0_Mono;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "active", 6)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_PAS) | LCCR0_Act;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "passive", 7)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_PAS) | LCCR0_Pas;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "single", 6)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_SDS) | LCCR0_Sngl;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "dual", 4)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_SDS) | LCCR0_Dual;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "4pix", 4)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_DPD) | LCCR0_4PixMono;
	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "8pix", 4)) अणु
		inf->lccr0 = (inf->lccr0 & ~LCCR0_DPD) | LCCR0_8PixMono;
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown option: %s\n", this_opt);
		वापस -EINVAL;
	पूर्ण

	अगर (s[0] != '\0')
		dev_info(dev, "override %s", s);

	वापस 0;
पूर्ण

अटल पूर्णांक pxafb_parse_options(काष्ठा device *dev, अक्षर *options,
			       काष्ठा pxafb_mach_info *inf)
अणु
	अक्षर *this_opt;
	पूर्णांक ret;

	अगर (!options || !*options)
		वापस 0;

	dev_dbg(dev, "options are \"%s\"\n", options ? options : "null");

	/* could be made table driven or similar?... */
	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		ret = parse_opt(dev, this_opt, inf);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर g_options[256] = "";

#अगर_अघोषित MODULE
अटल पूर्णांक __init pxafb_setup_options(व्योम)
अणु
	अक्षर *options = शून्य;

	अगर (fb_get_options("pxafb", &options))
		वापस -ENODEV;

	अगर (options)
		strlcpy(g_options, options, माप(g_options));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pxafb_setup_options()		(0)

module_param_string(options, g_options, माप(g_options), 0);
MODULE_PARM_DESC(options, "LCD parameters (see Documentation/fb/pxafb.rst)");
#पूर्ण_अगर

#अन्यथा
#घोषणा pxafb_parse_options(...)	(0)
#घोषणा pxafb_setup_options()		(0)
#पूर्ण_अगर

#अगर_घोषित DEBUG_VAR
/* Check क्रम various illegal bit-combinations. Currently only
 * a warning is given. */
अटल व्योम pxafb_check_options(काष्ठा device *dev, काष्ठा pxafb_mach_info *inf)
अणु
	अगर (inf->lcd_conn)
		वापस;

	अगर (inf->lccr0 & LCCR0_INVALID_CONFIG_MASK)
		dev_warn(dev, "machine LCCR0 setting contains "
				"illegal bits: %08x\n",
			inf->lccr0 & LCCR0_INVALID_CONFIG_MASK);
	अगर (inf->lccr3 & LCCR3_INVALID_CONFIG_MASK)
		dev_warn(dev, "machine LCCR3 setting contains "
				"illegal bits: %08x\n",
			inf->lccr3 & LCCR3_INVALID_CONFIG_MASK);
	अगर (inf->lccr0 & LCCR0_DPD &&
	    ((inf->lccr0 & LCCR0_PAS) != LCCR0_Pas ||
	     (inf->lccr0 & LCCR0_SDS) != LCCR0_Sngl ||
	     (inf->lccr0 & LCCR0_CMS) != LCCR0_Mono))
		dev_warn(dev, "Double Pixel Data (DPD) mode is "
				"only valid in passive mono"
				" single panel mode\n");
	अगर ((inf->lccr0 & LCCR0_PAS) == LCCR0_Act &&
	    (inf->lccr0 & LCCR0_SDS) == LCCR0_Dual)
		dev_warn(dev, "Dual panel only valid in passive mode\n");
	अगर ((inf->lccr0 & LCCR0_PAS) == LCCR0_Pas &&
	     (inf->modes->upper_margin || inf->modes->lower_margin))
		dev_warn(dev, "Upper and lower margins must be 0 in "
				"passive mode\n");
पूर्ण
#अन्यथा
#घोषणा pxafb_check_options(...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(CONFIG_OF)
अटल स्थिर अक्षर * स्थिर lcd_types[] = अणु
	"unknown", "mono-stn", "mono-dstn", "color-stn", "color-dstn",
	"color-tft", "smart-panel", शून्य
पूर्ण;

अटल पूर्णांक of_get_pxafb_display(काष्ठा device *dev, काष्ठा device_node *disp,
				काष्ठा pxafb_mach_info *info, u32 bus_width)
अणु
	काष्ठा display_timings *timings;
	काष्ठा videomode vm;
	पूर्णांक i, ret = -EINVAL;
	स्थिर अक्षर *s;

	ret = of_property_पढ़ो_string(disp, "lcd-type", &s);
	अगर (ret)
		s = "color-tft";

	i = match_string(lcd_types, -1, s);
	अगर (i < 0) अणु
		dev_err(dev, "lcd-type %s is unknown\n", s);
		वापस i;
	पूर्ण
	info->lcd_conn |= LCD_CONN_TYPE(i);
	info->lcd_conn |= LCD_CONN_WIDTH(bus_width);

	timings = of_get_display_timings(disp);
	अगर (!timings)
		वापस -EINVAL;

	ret = -ENOMEM;
	info->modes = devm_kसुस्मृति(dev, timings->num_timings,
				   माप(info->modes[0]),
				   GFP_KERNEL);
	अगर (!info->modes)
		जाओ out;
	info->num_modes = timings->num_timings;

	क्रम (i = 0; i < timings->num_timings; i++) अणु
		ret = videomode_from_timings(timings, &vm, i);
		अगर (ret) अणु
			dev_err(dev, "videomode_from_timings %d failed: %d\n",
				i, ret);
			जाओ out;
		पूर्ण
		अगर (vm.flags & DISPLAY_FLAGS_PIXDATA_POSEDGE)
			info->lcd_conn |= LCD_PCLK_EDGE_RISE;
		अगर (vm.flags & DISPLAY_FLAGS_PIXDATA_NEGEDGE)
			info->lcd_conn |= LCD_PCLK_EDGE_FALL;
		अगर (vm.flags & DISPLAY_FLAGS_DE_HIGH)
			info->lcd_conn |= LCD_BIAS_ACTIVE_HIGH;
		अगर (vm.flags & DISPLAY_FLAGS_DE_LOW)
			info->lcd_conn |= LCD_BIAS_ACTIVE_LOW;
		अगर (vm.flags & DISPLAY_FLAGS_HSYNC_HIGH)
			info->modes[i].sync |= FB_SYNC_HOR_HIGH_ACT;
		अगर (vm.flags & DISPLAY_FLAGS_VSYNC_HIGH)
			info->modes[i].sync |= FB_SYNC_VERT_HIGH_ACT;

		info->modes[i].pixघड़ी = 1000000000UL / (vm.pixelघड़ी / 1000);
		info->modes[i].xres = vm.hactive;
		info->modes[i].yres = vm.vactive;
		info->modes[i].hsync_len = vm.hsync_len;
		info->modes[i].left_margin = vm.hback_porch;
		info->modes[i].right_margin = vm.hfront_porch;
		info->modes[i].vsync_len = vm.vsync_len;
		info->modes[i].upper_margin = vm.vback_porch;
		info->modes[i].lower_margin = vm.vfront_porch;
	पूर्ण
	ret = 0;

out:
	display_timings_release(timings);
	वापस ret;
पूर्ण

अटल पूर्णांक of_get_pxafb_mode_info(काष्ठा device *dev,
				  काष्ठा pxafb_mach_info *info)
अणु
	काष्ठा device_node *display, *np;
	u32 bus_width;
	पूर्णांक ret, i;

	np = of_graph_get_next_endpoपूर्णांक(dev->of_node, शून्य);
	अगर (!np) अणु
		dev_err(dev, "could not find endpoint\n");
		वापस -EINVAL;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "bus-width", &bus_width);
	अगर (ret) अणु
		dev_err(dev, "no bus-width specified: %d\n", ret);
		of_node_put(np);
		वापस ret;
	पूर्ण

	display = of_graph_get_remote_port_parent(np);
	of_node_put(np);
	अगर (!display) अणु
		dev_err(dev, "no display defined\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_get_pxafb_display(dev, display, info, bus_width);
	of_node_put(display);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < info->num_modes; i++)
		info->modes[i].bpp = bus_width;

	वापस 0;
पूर्ण

अटल काष्ठा pxafb_mach_info *of_pxafb_of_mach_info(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा pxafb_mach_info *info;

	अगर (!dev->of_node)
		वापस शून्य;
	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);
	ret = of_get_pxafb_mode_info(dev, info);
	अगर (ret)
		वापस ERR_PTR(ret);

	/*
	 * On purpose, neither lccrX रेजिस्टरs nor video memory size can be
	 * specअगरied through device-tree, they are considered more a debug hack
	 * available through command line.
	 */
	वापस info;
पूर्ण
#अन्यथा
अटल काष्ठा pxafb_mach_info *of_pxafb_of_mach_info(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pxafb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxafb_info *fbi;
	काष्ठा pxafb_mach_info *inf, *pdata;
	पूर्णांक i, irq, ret;

	dev_dbg(&dev->dev, "pxafb_probe\n");

	ret = -ENOMEM;
	pdata = dev_get_platdata(&dev->dev);
	inf = devm_kदो_स्मृति(&dev->dev, माप(*inf), GFP_KERNEL);
	अगर (!inf)
		जाओ failed;

	अगर (pdata) अणु
		*inf = *pdata;
		inf->modes =
			devm_kदो_स्मृति_array(&dev->dev, pdata->num_modes,
					   माप(inf->modes[0]), GFP_KERNEL);
		अगर (!inf->modes)
			जाओ failed;
		क्रम (i = 0; i < inf->num_modes; i++)
			inf->modes[i] = pdata->modes[i];
	पूर्ण

	अगर (!pdata)
		inf = of_pxafb_of_mach_info(&dev->dev);
	अगर (IS_ERR_OR_शून्य(inf))
		जाओ failed;

	ret = pxafb_parse_options(&dev->dev, g_options, inf);
	अगर (ret < 0)
		जाओ failed;

	pxafb_check_options(&dev->dev, inf);

	dev_dbg(&dev->dev, "got a %dx%dx%d LCD\n",
			inf->modes->xres,
			inf->modes->yres,
			inf->modes->bpp);
	अगर (inf->modes->xres == 0 ||
	    inf->modes->yres == 0 ||
	    inf->modes->bpp == 0) अणु
		dev_err(&dev->dev, "Invalid resolution or bit depth\n");
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	fbi = pxafb_init_fbinfo(&dev->dev, inf);
	अगर (IS_ERR(fbi)) अणु
		dev_err(&dev->dev, "Failed to initialize framebuffer device\n");
		ret = PTR_ERR(fbi);
		जाओ failed;
	पूर्ण

	अगर (cpu_is_pxa3xx() && inf->acceleration_enabled)
		fbi->fb.fix.accel = FB_ACCEL_PXA3XX;

	fbi->backlight_घातer = inf->pxafb_backlight_घातer;
	fbi->lcd_घातer = inf->pxafb_lcd_घातer;

	fbi->lcd_supply = devm_regulator_get_optional(&dev->dev, "lcd");
	अगर (IS_ERR(fbi->lcd_supply)) अणु
		अगर (PTR_ERR(fbi->lcd_supply) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		fbi->lcd_supply = शून्य;
	पूर्ण

	fbi->mmio_base = devm_platक्रमm_ioremap_resource(dev, 0);
	अगर (IS_ERR(fbi->mmio_base)) अणु
		dev_err(&dev->dev, "failed to get I/O memory\n");
		ret = PTR_ERR(fbi->mmio_base);
		जाओ failed;
	पूर्ण

	fbi->dma_buff_size = PAGE_ALIGN(माप(काष्ठा pxafb_dma_buff));
	fbi->dma_buff = dma_alloc_coherent(fbi->dev, fbi->dma_buff_size,
				&fbi->dma_buff_phys, GFP_KERNEL);
	अगर (fbi->dma_buff == शून्य) अणु
		dev_err(&dev->dev, "failed to allocate memory for DMA\n");
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	ret = pxafb_init_video_memory(fbi);
	अगर (ret) अणु
		dev_err(&dev->dev, "Failed to allocate video RAM: %d\n", ret);
		ret = -ENOMEM;
		जाओ failed_मुक्त_dma;
	पूर्ण

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0) अणु
		dev_err(&dev->dev, "no IRQ defined\n");
		ret = -ENODEV;
		जाओ failed_मुक्त_mem;
	पूर्ण

	ret = devm_request_irq(&dev->dev, irq, pxafb_handle_irq, 0, "LCD", fbi);
	अगर (ret) अणु
		dev_err(&dev->dev, "request_irq failed: %d\n", ret);
		ret = -EBUSY;
		जाओ failed_मुक्त_mem;
	पूर्ण

	ret = pxafb_smart_init(fbi);
	अगर (ret) अणु
		dev_err(&dev->dev, "failed to initialize smartpanel\n");
		जाओ failed_मुक्त_mem;
	पूर्ण

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	ret = pxafb_check_var(&fbi->fb.var, &fbi->fb);
	अगर (ret) अणु
		dev_err(&dev->dev, "failed to get suitable mode\n");
		जाओ failed_मुक्त_mem;
	पूर्ण

	ret = pxafb_set_par(&fbi->fb);
	अगर (ret) अणु
		dev_err(&dev->dev, "Failed to set parameters\n");
		जाओ failed_मुक्त_mem;
	पूर्ण

	platक्रमm_set_drvdata(dev, fbi);

	ret = रेजिस्टर_framebuffer(&fbi->fb);
	अगर (ret < 0) अणु
		dev_err(&dev->dev,
			"Failed to register framebuffer device: %d\n", ret);
		जाओ failed_मुक्त_cmap;
	पूर्ण

	pxafb_overlay_init(fbi);

#अगर_घोषित CONFIG_CPU_FREQ
	fbi->freq_transition.notअगरier_call = pxafb_freq_transition;
	cpufreq_रेजिस्टर_notअगरier(&fbi->freq_transition,
				CPUFREQ_TRANSITION_NOTIFIER);
#पूर्ण_अगर

	/*
	 * Ok, now enable the LCD controller
	 */
	set_ctrlr_state(fbi, C_ENABLE);

	वापस 0;

failed_मुक्त_cmap:
	अगर (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);
failed_मुक्त_mem:
	मुक्त_pages_exact(fbi->video_mem, fbi->video_mem_size);
failed_मुक्त_dma:
	dma_मुक्त_coherent(&dev->dev, fbi->dma_buff_size,
			fbi->dma_buff, fbi->dma_buff_phys);
failed:
	वापस ret;
पूर्ण

अटल पूर्णांक pxafb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxafb_info *fbi = platक्रमm_get_drvdata(dev);
	काष्ठा fb_info *info;

	अगर (!fbi)
		वापस 0;

	info = &fbi->fb;

	pxafb_overlay_निकास(fbi);
	unरेजिस्टर_framebuffer(info);

	pxafb_disable_controller(fbi);

	अगर (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	मुक्त_pages_exact(fbi->video_mem, fbi->video_mem_size);

	dma_मुक्त_coherent(&dev->dev, fbi->dma_buff_size, fbi->dma_buff,
			  fbi->dma_buff_phys);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pxafb_of_dev_id[] = अणु
	अणु .compatible = "marvell,pxa270-lcdc", पूर्ण,
	अणु .compatible = "marvell,pxa300-lcdc", पूर्ण,
	अणु .compatible = "marvell,pxa2xx-lcdc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxafb_of_dev_id);

अटल काष्ठा platक्रमm_driver pxafb_driver = अणु
	.probe		= pxafb_probe,
	.हटाओ 	= pxafb_हटाओ,
	.driver		= अणु
		.name	= "pxa2xx-fb",
		.of_match_table = pxafb_of_dev_id,
#अगर_घोषित CONFIG_PM
		.pm	= &pxafb_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pxafb_init(व्योम)
अणु
	अगर (pxafb_setup_options())
		वापस -EINVAL;

	वापस platक्रमm_driver_रेजिस्टर(&pxafb_driver);
पूर्ण

अटल व्योम __निकास pxafb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pxafb_driver);
पूर्ण

module_init(pxafb_init);
module_निकास(pxafb_निकास);

MODULE_DESCRIPTION("loadable framebuffer driver for PXA");
MODULE_LICENSE("GPL");
