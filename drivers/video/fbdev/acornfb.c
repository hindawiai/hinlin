<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/acornfb.c
 *
 *  Copyright (C) 1998-2001 Russell King
 *
 * Frame buffer code क्रम Acorn platक्रमms
 *
 * NOTE: Most of the modes with X!=640 will disappear लघुly.
 * NOTE: Startup setting of HS & VS polarity not supported.
 *       (करो we need to support it अगर we're coming up in 640x480?)
 *
 * FIXME: (things broken by the "new improved" FBCON API)
 *  - Blanking 8bpp displays with VIDC
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/gfp.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "acornfb.h"

/*
 * Default resolution.
 * NOTE that it has to be supported in the table towards
 * the end of this file.
 */
#घोषणा DEFAULT_XRES	640
#घोषणा DEFAULT_YRES	480
#घोषणा DEFAULT_BPP	4

/*
 * define this to debug the video mode selection
 */
#अघोषित DEBUG_MODE_SELECTION

/*
 * Translation from RISC OS monitor types to actual
 * HSYNC and VSYNC frequency ranges.  These are
 * probably not right, but they're the best info I
 * have.  Allow 1% either way on the nominal क्रम TVs.
 */
#घोषणा NR_MONTYPES	6
अटल काष्ठा fb_monspecs monspecs[NR_MONTYPES] = अणु
	अणु	/* TV		*/
		.hfmin	= 15469,
		.hfmax	= 15781,
		.vfmin	= 49,
		.vfmax	= 51,
	पूर्ण, अणु	/* Multi Freq	*/
		.hfmin	= 0,
		.hfmax	= 99999,
		.vfmin	= 0,
		.vfmax	= 199,
	पूर्ण, अणु	/* Hi-res mono	*/
		.hfmin	= 58608,
		.hfmax	= 58608,
		.vfmin	= 64,
		.vfmax	= 64,
	पूर्ण, अणु	/* VGA		*/
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 60,
		.vfmax	= 60,
	पूर्ण, अणु	/* SVGA		*/
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 56,
		.vfmax	= 75,
	पूर्ण, अणु
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 60,
		.vfmax	= 60,
	पूर्ण
पूर्ण;

अटल काष्ठा fb_info fb_info;
अटल काष्ठा acornfb_par current_par;
अटल काष्ठा vidc_timing current_vidc;

बाह्य अचिन्हित पूर्णांक vram_size;	/* set by setup.c */

#अगर_घोषित HAS_VIDC20
#समावेश <mach/acornfb.h>

#घोषणा MAX_SIZE	(2*1024*1024)

/* VIDC20 has a dअगरferent set of rules from the VIDC:
 *  hcr  : must be multiple of 4
 *  hswr : must be even
 *  hdsr : must be even
 *  hder : must be even
 *  vcr  : >= 2, (पूर्णांकerlace, must be odd)
 *  vswr : >= 1
 *  vdsr : >= 1
 *  vder : >= vdsr
 */
अटल व्योम acornfb_set_timing(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा vidc_timing vidc;
	u_पूर्णांक vcr, fsize;
	u_पूर्णांक ext_ctl, dat_ctl;
	u_पूर्णांक words_per_line;

	स_रखो(&vidc, 0, माप(vidc));

	vidc.h_sync_width	= var->hsync_len - 8;
	vidc.h_border_start	= vidc.h_sync_width + var->left_margin + 8 - 12;
	vidc.h_display_start	= vidc.h_border_start + 12 - 18;
	vidc.h_display_end	= vidc.h_display_start + var->xres;
	vidc.h_border_end	= vidc.h_display_end + 18 - 12;
	vidc.h_cycle		= vidc.h_border_end + var->right_margin + 12 - 8;
	vidc.h_पूर्णांकerlace	= vidc.h_cycle / 2;
	vidc.v_sync_width	= var->vsync_len - 1;
	vidc.v_border_start	= vidc.v_sync_width + var->upper_margin;
	vidc.v_display_start	= vidc.v_border_start;
	vidc.v_display_end	= vidc.v_display_start + var->yres;
	vidc.v_border_end	= vidc.v_display_end;
	vidc.control		= acornfb_शेष_control();

	vcr = var->vsync_len + var->upper_margin + var->yres +
	      var->lower_margin;

	अगर ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		vidc.v_cycle = (vcr - 3) / 2;
		vidc.control |= VIDC20_CTRL_INT;
	पूर्ण अन्यथा
		vidc.v_cycle = vcr - 2;

	चयन (var->bits_per_pixel) अणु
	हाल  1: vidc.control |= VIDC20_CTRL_1BPP;	अवरोध;
	हाल  2: vidc.control |= VIDC20_CTRL_2BPP;	अवरोध;
	हाल  4: vidc.control |= VIDC20_CTRL_4BPP;	अवरोध;
	शेष:
	हाल  8: vidc.control |= VIDC20_CTRL_8BPP;	अवरोध;
	हाल 16: vidc.control |= VIDC20_CTRL_16BPP;	अवरोध;
	हाल 32: vidc.control |= VIDC20_CTRL_32BPP;	अवरोध;
	पूर्ण

	acornfb_vidc20_find_rates(&vidc, var);
	fsize = var->vsync_len + var->upper_margin + var->lower_margin - 1;

	अगर (स_भेद(&current_vidc, &vidc, माप(vidc))) अणु
		current_vidc = vidc;

		vidc_ग_लिखोl(VIDC20_CTRL | vidc.control);
		vidc_ग_लिखोl(0xd0000000 | vidc.pll_ctl);
		vidc_ग_लिखोl(0x80000000 | vidc.h_cycle);
		vidc_ग_लिखोl(0x81000000 | vidc.h_sync_width);
		vidc_ग_लिखोl(0x82000000 | vidc.h_border_start);
		vidc_ग_लिखोl(0x83000000 | vidc.h_display_start);
		vidc_ग_लिखोl(0x84000000 | vidc.h_display_end);
		vidc_ग_लिखोl(0x85000000 | vidc.h_border_end);
		vidc_ग_लिखोl(0x86000000);
		vidc_ग_लिखोl(0x87000000 | vidc.h_पूर्णांकerlace);
		vidc_ग_लिखोl(0x90000000 | vidc.v_cycle);
		vidc_ग_लिखोl(0x91000000 | vidc.v_sync_width);
		vidc_ग_लिखोl(0x92000000 | vidc.v_border_start);
		vidc_ग_लिखोl(0x93000000 | vidc.v_display_start);
		vidc_ग_लिखोl(0x94000000 | vidc.v_display_end);
		vidc_ग_लिखोl(0x95000000 | vidc.v_border_end);
		vidc_ग_लिखोl(0x96000000);
		vidc_ग_लिखोl(0x97000000);
	पूर्ण

	iomd_ग_लिखोl(fsize, IOMD_FSIZE);

	ext_ctl = acornfb_शेष_econtrol();

	अगर (var->sync & FB_SYNC_COMP_HIGH_ACT) /* should be FB_SYNC_COMP */
		ext_ctl |= VIDC20_ECTL_HS_NCSYNC | VIDC20_ECTL_VS_NCSYNC;
	अन्यथा अणु
		अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
			ext_ctl |= VIDC20_ECTL_HS_HSYNC;
		अन्यथा
			ext_ctl |= VIDC20_ECTL_HS_NHSYNC;

		अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
			ext_ctl |= VIDC20_ECTL_VS_VSYNC;
		अन्यथा
			ext_ctl |= VIDC20_ECTL_VS_NVSYNC;
	पूर्ण

	vidc_ग_लिखोl(VIDC20_ECTL | ext_ctl);

	words_per_line = var->xres * var->bits_per_pixel / 32;

	अगर (current_par.using_vram && info->fix.smem_len == 2048*1024)
		words_per_line /= 2;

	/* RiscPC करोesn't use the VIDC's VRAM control. */
	dat_ctl = VIDC20_DCTL_VRAM_DIS | VIDC20_DCTL_SNA | words_per_line;

	/* The data bus width is dependent on both the type
	 * and amount of video memory.
	 *     DRAM	32bit low
	 * 1MB VRAM	32bit
	 * 2MB VRAM	64bit
	 */
	अगर (current_par.using_vram && current_par.vram_half_sam == 2048)
		dat_ctl |= VIDC20_DCTL_BUS_D63_0;
	अन्यथा
		dat_ctl |= VIDC20_DCTL_BUS_D31_0;

	vidc_ग_लिखोl(VIDC20_DCTL | dat_ctl);

#अगर_घोषित DEBUG_MODE_SELECTION
	prपूर्णांकk(KERN_DEBUG "VIDC registers for %dx%dx%d:\n", var->xres,
	       var->yres, var->bits_per_pixel);
	prपूर्णांकk(KERN_DEBUG " H-cycle          : %d\n", vidc.h_cycle);
	prपूर्णांकk(KERN_DEBUG " H-sync-width     : %d\n", vidc.h_sync_width);
	prपूर्णांकk(KERN_DEBUG " H-border-start   : %d\n", vidc.h_border_start);
	prपूर्णांकk(KERN_DEBUG " H-display-start  : %d\n", vidc.h_display_start);
	prपूर्णांकk(KERN_DEBUG " H-display-end    : %d\n", vidc.h_display_end);
	prपूर्णांकk(KERN_DEBUG " H-border-end     : %d\n", vidc.h_border_end);
	prपूर्णांकk(KERN_DEBUG " H-interlace      : %d\n", vidc.h_पूर्णांकerlace);
	prपूर्णांकk(KERN_DEBUG " V-cycle          : %d\n", vidc.v_cycle);
	prपूर्णांकk(KERN_DEBUG " V-sync-width     : %d\n", vidc.v_sync_width);
	prपूर्णांकk(KERN_DEBUG " V-border-start   : %d\n", vidc.v_border_start);
	prपूर्णांकk(KERN_DEBUG " V-display-start  : %d\n", vidc.v_display_start);
	prपूर्णांकk(KERN_DEBUG " V-display-end    : %d\n", vidc.v_display_end);
	prपूर्णांकk(KERN_DEBUG " V-border-end     : %d\n", vidc.v_border_end);
	prपूर्णांकk(KERN_DEBUG " Ext Ctrl  (C)    : 0x%08X\n", ext_ctl);
	prपूर्णांकk(KERN_DEBUG " PLL Ctrl  (D)    : 0x%08X\n", vidc.pll_ctl);
	prपूर्णांकk(KERN_DEBUG " Ctrl      (E)    : 0x%08X\n", vidc.control);
	prपूर्णांकk(KERN_DEBUG " Data Ctrl (F)    : 0x%08X\n", dat_ctl);
	prपूर्णांकk(KERN_DEBUG " Fsize            : 0x%08X\n", fsize);
#पूर्ण_अगर
पूर्ण

/*
 * We have to take note of the VIDC20's 16-bit palette here.
 * The VIDC20 looks up a 16 bit pixel as follows:
 *
 *   bits   111111
 *          5432109876543210
 *   red            ++++++++  (8 bits,  7 to 0)
 *  green       ++++++++      (8 bits, 11 to 4)
 *   blue   ++++++++          (8 bits, 15 to 8)
 *
 * We use a pixel which looks like:
 *
 *   bits   111111
 *          5432109876543210
 *   red               +++++  (5 bits,  4 to  0)
 *  green         +++++       (5 bits,  9 to  5)
 *   blue    +++++            (5 bits, 14 to 10)
 */
अटल पूर्णांक
acornfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		  u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	जोड़ palette pal;

	अगर (regno >= current_par.palette_size)
		वापस 1;

	अगर (regno < 16 && info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		u32 pseuकरो_val;

		pseuकरो_val  = regno << info->var.red.offset;
		pseuकरो_val |= regno << info->var.green.offset;
		pseuकरो_val |= regno << info->var.blue.offset;

		((u32 *)info->pseuकरो_palette)[regno] = pseuकरो_val;
	पूर्ण

	pal.p = 0;
	pal.vidc20.red   = red >> 8;
	pal.vidc20.green = green >> 8;
	pal.vidc20.blue  = blue >> 8;

	current_par.palette[regno] = pal;

	अगर (info->var.bits_per_pixel == 16) अणु
		पूर्णांक i;

		pal.p = 0;
		vidc_ग_लिखोl(0x10000000);
		क्रम (i = 0; i < 256; i += 1) अणु
			pal.vidc20.red   = current_par.palette[i       & 31].vidc20.red;
			pal.vidc20.green = current_par.palette[(i >> 1) & 31].vidc20.green;
			pal.vidc20.blue  = current_par.palette[(i >> 2) & 31].vidc20.blue;
			vidc_ग_लिखोl(pal.p);
			/* Palette रेजिस्टर poपूर्णांकer स्वतः-increments */
		पूर्ण
	पूर्ण अन्यथा अणु
		vidc_ग_लिखोl(0x10000000 | regno);
		vidc_ग_लिखोl(pal.p);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Beक्रमe selecting the timing parameters, adjust
 * the resolution to fit the rules.
 */
अटल पूर्णांक
acornfb_adjust_timing(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var, u_पूर्णांक fontht)
अणु
	u_पूर्णांक font_line_len, sam_size, min_size, size, nr_y;

	/* xres must be even */
	var->xres = (var->xres + 1) & ~1;

	/*
	 * We करोn't allow xres_भव to dअगरfer from xres
	 */
	var->xres_भव = var->xres;
	var->xoffset = 0;

	अगर (current_par.using_vram)
		sam_size = current_par.vram_half_sam * 2;
	अन्यथा
		sam_size = 16;

	/*
	 * Now, find a value क्रम yres_भव which allows
	 * us to करो ywrap scrolling.  The value of
	 * yres_भव must be such that the end of the
	 * displayable frame buffer must be aligned with
	 * the start of a font line.
	 */
	font_line_len = var->xres * var->bits_per_pixel * fontht / 8;
	min_size = var->xres * var->yres * var->bits_per_pixel / 8;

	/*
	 * If minimum screen size is greater than that we have
	 * available, reject it.
	 */
	अगर (min_size > info->fix.smem_len)
		वापस -EINVAL;

	/* Find पूर्णांक 'y', such that y * fll == s * sam < maxsize
	 * y = s * sam / fll; s = maxsize / sam
	 */
	क्रम (size = info->fix.smem_len;
	     nr_y = size / font_line_len, min_size <= size;
	     size -= sam_size) अणु
		अगर (nr_y * font_line_len == size)
			अवरोध;
	पूर्ण
	nr_y *= fontht;

	अगर (var->accel_flags & FB_ACCELF_TEXT) अणु
		अगर (min_size > size) अणु
			/*
			 * failed, use ypan
			 */
			size = info->fix.smem_len;
			var->yres_भव = size / (font_line_len / fontht);
		पूर्ण अन्यथा
			var->yres_भव = nr_y;
	पूर्ण अन्यथा अगर (var->yres_भव > nr_y)
		var->yres_भव = nr_y;

	current_par.screen_end = info->fix.smem_start + size;

	/*
	 * Fix yres & yoffset अगर needed.
	 */
	अगर (var->yres > var->yres_भव)
		var->yres = var->yres_भव;

	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->yoffset > var->yres_भव)
			var->yoffset = var->yres_भव;
	पूर्ण अन्यथा अणु
		अगर (var->yoffset + var->yres > var->yres_भव)
			var->yoffset = var->yres_भव - var->yres;
	पूर्ण

	/* hsync_len must be even */
	var->hsync_len = (var->hsync_len + 1) & ~1;

#अगर defined(HAS_VIDC20)
	/* left_margin must be even */
	अगर (var->left_margin & 1) अणु
		var->left_margin += 1;
		var->right_margin -= 1;
	पूर्ण

	/* right_margin must be even */
	अगर (var->right_margin & 1)
		var->right_margin += 1;
#पूर्ण_अगर

	अगर (var->vsync_len < 1)
		var->vsync_len = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
acornfb_validate_timing(काष्ठा fb_var_screeninfo *var,
			काष्ठा fb_monspecs *monspecs)
अणु
	अचिन्हित दीर्घ hs, vs;

	/*
	 * hs(Hz) = 10^12 / (pixघड़ी * xtotal)
	 * vs(Hz) = hs(Hz) / ytotal
	 *
	 * No need to करो दीर्घ दीर्घ भागisions or anything
	 * like that अगर you factor it correctly
	 */
	hs = 1953125000 / var->pixघड़ी;
	hs = hs * 512 /
	     (var->xres + var->left_margin + var->right_margin + var->hsync_len);
	vs = hs /
	     (var->yres + var->upper_margin + var->lower_margin + var->vsync_len);

	वापस (vs >= monspecs->vfmin && vs <= monspecs->vfmax &&
		hs >= monspecs->hfmin && hs <= monspecs->hfmax) ? 0 : -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
acornfb_update_dma(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var)
अणु
	u_पूर्णांक off = var->yoffset * info->fix.line_length;

#अगर defined(HAS_MEMC)
	memc_ग_लिखो(VDMA_INIT, off >> 2);
#या_अगर defined(HAS_IOMD)
	iomd_ग_लिखोl(info->fix.smem_start + off, IOMD_VIDINIT);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
acornfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u_पूर्णांक fontht;
	पूर्णांक err;

	/*
	 * FIXME: Find the font height
	 */
	fontht = 8;

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	चयन (var->bits_per_pixel) अणु
	हाल 1:	हाल 2:	हाल 4:	हाल 8:
		var->red.offset    = 0;
		var->red.length    = var->bits_per_pixel;
		var->green         = var->red;
		var->blue          = var->red;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;

#अगर_घोषित HAS_VIDC20
	हाल 16:
		var->red.offset    = 0;
		var->red.length    = 5;
		var->green.offset  = 5;
		var->green.length  = 5;
		var->blue.offset   = 10;
		var->blue.length   = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		अवरोध;

	हाल 32:
		var->red.offset    = 0;
		var->red.length    = 8;
		var->green.offset  = 8;
		var->green.length  = 8;
		var->blue.offset   = 16;
		var->blue.length   = 8;
		var->transp.offset = 24;
		var->transp.length = 4;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check to see अगर the pixel rate is valid.
	 */
	अगर (!acornfb_valid_pixrate(var))
		वापस -EINVAL;

	/*
	 * Validate and adjust the resolution to
	 * match the video generator hardware.
	 */
	err = acornfb_adjust_timing(info, var, fontht);
	अगर (err)
		वापस err;

	/*
	 * Validate the timing against the
	 * monitor hardware.
	 */
	वापस acornfb_validate_timing(var, &info->monspecs);
पूर्ण

अटल पूर्णांक acornfb_set_par(काष्ठा fb_info *info)
अणु
	चयन (info->var.bits_per_pixel) अणु
	हाल 1:
		current_par.palette_size = 2;
		info->fix.visual = FB_VISUAL_MONO10;
		अवरोध;
	हाल 2:
		current_par.palette_size = 4;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 4:
		current_par.palette_size = 16;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 8:
		current_par.palette_size = VIDC_PALETTE_SIZE;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
#अगर_घोषित HAS_VIDC20
	हाल 16:
		current_par.palette_size = 32;
		info->fix.visual = FB_VISUAL_सूचीECTCOLOR;
		अवरोध;
	हाल 32:
		current_par.palette_size = VIDC_PALETTE_SIZE;
		info->fix.visual = FB_VISUAL_सूचीECTCOLOR;
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण

	info->fix.line_length	= (info->var.xres * info->var.bits_per_pixel) / 8;

#अगर defined(HAS_MEMC)
	अणु
		अचिन्हित दीर्घ size = info->fix.smem_len - VDMA_XFERSIZE;

		memc_ग_लिखो(VDMA_START, 0);
		memc_ग_लिखो(VDMA_END, size >> 2);
	पूर्ण
#या_अगर defined(HAS_IOMD)
	अणु
		अचिन्हित दीर्घ start, size;
		u_पूर्णांक control;

		start = info->fix.smem_start;
		size  = current_par.screen_end;

		अगर (current_par.using_vram) अणु
			size -= current_par.vram_half_sam;
			control = DMA_CR_E | (current_par.vram_half_sam / 256);
		पूर्ण अन्यथा अणु
			size -= 16;
			control = DMA_CR_E | DMA_CR_D | 16;
		पूर्ण

		iomd_ग_लिखोl(start,   IOMD_VIDSTART);
		iomd_ग_लिखोl(size,    IOMD_VIDEND);
		iomd_ग_लिखोl(control, IOMD_VIDCR);
	पूर्ण
#पूर्ण_अगर

	acornfb_update_dma(info, &info->var);
	acornfb_set_timing(info);

	वापस 0;
पूर्ण

अटल पूर्णांक
acornfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u_पूर्णांक y_bottom = var->yoffset;

	अगर (!(var->vmode & FB_VMODE_YWRAP))
		y_bottom += info->var.yres;

	अगर (y_bottom > info->var.yres_भव)
		वापस -EINVAL;

	acornfb_update_dma(info, var);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops acornfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= acornfb_check_var,
	.fb_set_par	= acornfb_set_par,
	.fb_setcolreg	= acornfb_setcolreg,
	.fb_pan_display	= acornfb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 * Everything after here is initialisation!!!
 */
अटल काष्ठा fb_videomode modedb[] = अणु
	अणु	/* 320x256 @ 50Hz */
		शून्य, 50,  320,  256, 125000,  92,  62,  35, 19,  38, 2,
		FB_SYNC_COMP_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x250 @ 50Hz, 15.6 kHz hsync */
		शून्य, 50,  640,  250,  62500, 185, 123,  38, 21,  76, 3,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x256 @ 50Hz, 15.6 kHz hsync */
		शून्य, 50,  640,  256,  62500, 185, 123,  35, 18,  76, 3,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x512 @ 50Hz, 26.8 kHz hsync */
		शून्य, 50,  640,  512,  41667, 113,  87,  18,  1,  56, 3,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x250 @ 70Hz, 31.5 kHz hsync */
		शून्य, 70,  640,  250,  39722,  48,  16, 109, 88,  96, 2,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x256 @ 70Hz, 31.5 kHz hsync */
		शून्य, 70,  640,  256,  39722,  48,  16, 106, 85,  96, 2,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x352 @ 70Hz, 31.5 kHz hsync */
		शून्य, 70,  640,  352,  39722,  48,  16,  58, 37,  96, 2,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 640x480 @ 60Hz, 31.5 kHz hsync */
		शून्य, 60,  640,  480,  39722,  48,  16,  32, 11,  96, 2,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 800x600 @ 56Hz, 35.2 kHz hsync */
		शून्य, 56,  800,  600,  27778, 101,  23,  22,  1, 100, 2,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 896x352 @ 60Hz, 21.8 kHz hsync */
		शून्य, 60,  896,  352,  41667,  59,  27,   9,  0, 118, 3,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 1024x 768 @ 60Hz, 48.4 kHz hsync */
		शून्य, 60, 1024,  768,  15385, 160,  24,  29,  3, 136, 6,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण, अणु	/* 1280x1024 @ 60Hz, 63.8 kHz hsync */
		शून्य, 60, 1280, 1024,   9090, 186,  96,  38,  1, 160, 3,
		0,
		FB_VMODE_NONINTERLACED
	पूर्ण
पूर्ण;

अटल काष्ठा fb_videomode acornfb_शेष_mode = अणु
	.name =		शून्य,
	.refresh =	60,
	.xres =		640,
	.yres =		480,
	.pixघड़ी =	39722,
	.left_margin =	56,
	.right_margin =	16,
	.upper_margin =	34,
	.lower_margin =	9,
	.hsync_len =	88,
	.vsync_len =	2,
	.sync =		0,
	.vmode =	FB_VMODE_NONINTERLACED
पूर्ण;

अटल व्योम acornfb_init_fbinfo(व्योम)
अणु
	अटल पूर्णांक first = 1;

	अगर (!first)
		वापस;
	first = 0;

	fb_info.fbops		= &acornfb_ops;
	fb_info.flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	fb_info.pseuकरो_palette	= current_par.pseuकरो_palette;

	म_नकल(fb_info.fix.id, "Acorn");
	fb_info.fix.type	= FB_TYPE_PACKED_PIXELS;
	fb_info.fix.type_aux	= 0;
	fb_info.fix.xpanstep	= 0;
	fb_info.fix.ypanstep	= 1;
	fb_info.fix.ywrapstep	= 1;
	fb_info.fix.line_length	= 0;
	fb_info.fix.accel	= FB_ACCEL_NONE;

	/*
	 * setup initial parameters
	 */
	स_रखो(&fb_info.var, 0, माप(fb_info.var));

#अगर defined(HAS_VIDC20)
	fb_info.var.red.length	   = 8;
	fb_info.var.transp.length  = 4;
#पूर्ण_अगर
	fb_info.var.green	   = fb_info.var.red;
	fb_info.var.blue	   = fb_info.var.red;
	fb_info.var.nonstd	   = 0;
	fb_info.var.activate	   = FB_ACTIVATE_NOW;
	fb_info.var.height	   = -1;
	fb_info.var.width	   = -1;
	fb_info.var.vmode	   = FB_VMODE_NONINTERLACED;
	fb_info.var.accel_flags	   = FB_ACCELF_TEXT;

	current_par.dram_size	   = 0;
	current_par.montype	   = -1;
	current_par.dpms	   = 0;
पूर्ण

/*
 * setup acornfb options:
 *
 *  mon:hmin-hmax:vmin-vmax:dpms:width:height
 *	Set monitor parameters:
 *		hmin   = horizontal minimum frequency (Hz)
 *		hmax   = horizontal maximum frequency (Hz)	(optional)
 *		vmin   = vertical minimum frequency (Hz)
 *		vmax   = vertical maximum frequency (Hz)	(optional)
 *		dpms   = DPMS supported?			(optional)
 *		width  = width of picture in mm.		(optional)
 *		height = height of picture in mm.		(optional)
 *
 * montype:type
 *	Set RISC-OS style monitor type:
 *		0 (or tv)	- TV frequency
 *		1 (or multi)	- Multi frequency
 *		2 (or hires)	- Hi-res monochrome
 *		3 (or vga)	- VGA
 *		4 (or svga)	- SVGA
 *		स्वतः, or option missing
 *				- try hardware detect
 *
 * dram:size
 *	Set the amount of DRAM to use क्रम the frame buffer
 *	(even अगर you have VRAM).
 *	size can optionally be followed by 'M' or 'K' क्रम
 *	MB or KB respectively.
 */
अटल व्योम acornfb_parse_mon(अक्षर *opt)
अणु
	अक्षर *p = opt;

	current_par.montype = -2;

	fb_info.monspecs.hfmin = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (*p == '-')
		fb_info.monspecs.hfmax = simple_म_से_अदीर्घ(p + 1, &p, 0);
	अन्यथा
		fb_info.monspecs.hfmax = fb_info.monspecs.hfmin;

	अगर (*p != ':')
		जाओ bad;

	fb_info.monspecs.vfmin = simple_म_से_अदीर्घ(p + 1, &p, 0);
	अगर (*p == '-')
		fb_info.monspecs.vfmax = simple_म_से_अदीर्घ(p + 1, &p, 0);
	अन्यथा
		fb_info.monspecs.vfmax = fb_info.monspecs.vfmin;

	अगर (*p != ':')
		जाओ check_values;

	fb_info.monspecs.dpms = simple_म_से_अदीर्घ(p + 1, &p, 0);

	अगर (*p != ':')
		जाओ check_values;

	fb_info.var.width = simple_म_से_अदीर्घ(p + 1, &p, 0);

	अगर (*p != ':')
		जाओ check_values;

	fb_info.var.height = simple_म_से_अदीर्घ(p + 1, शून्य, 0);

check_values:
	अगर (fb_info.monspecs.hfmax < fb_info.monspecs.hfmin ||
	    fb_info.monspecs.vfmax < fb_info.monspecs.vfmin)
		जाओ bad;
	वापस;

bad:
	prपूर्णांकk(KERN_ERR "Acornfb: bad monitor settings: %s\n", opt);
	current_par.montype = -1;
पूर्ण

अटल व्योम acornfb_parse_montype(अक्षर *opt)
अणु
	current_par.montype = -2;

	अगर (म_भेदन(opt, "tv", 2) == 0) अणु
		opt += 2;
		current_par.montype = 0;
	पूर्ण अन्यथा अगर (म_भेदन(opt, "multi", 5) == 0) अणु
		opt += 5;
		current_par.montype = 1;
	पूर्ण अन्यथा अगर (म_भेदन(opt, "hires", 5) == 0) अणु
		opt += 5;
		current_par.montype = 2;
	पूर्ण अन्यथा अगर (म_भेदन(opt, "vga", 3) == 0) अणु
		opt += 3;
		current_par.montype = 3;
	पूर्ण अन्यथा अगर (म_भेदन(opt, "svga", 4) == 0) अणु
		opt += 4;
		current_par.montype = 4;
	पूर्ण अन्यथा अगर (म_भेदन(opt, "auto", 4) == 0) अणु
		opt += 4;
		current_par.montype = -1;
	पूर्ण अन्यथा अगर (है_अंक(*opt))
		current_par.montype = simple_म_से_अदीर्घ(opt, &opt, 0);

	अगर (current_par.montype == -2 ||
	    current_par.montype > NR_MONTYPES) अणु
		prपूर्णांकk(KERN_ERR "acornfb: unknown monitor type: %s\n",
			opt);
		current_par.montype = -1;
	पूर्ण अन्यथा
	अगर (opt && *opt) अणु
		अगर (म_भेद(opt, ",dpms") == 0)
			current_par.dpms = 1;
		अन्यथा
			prपूर्णांकk(KERN_ERR
			       "acornfb: unknown monitor option: %s\n",
			       opt);
	पूर्ण
पूर्ण

अटल व्योम acornfb_parse_dram(अक्षर *opt)
अणु
	अचिन्हित पूर्णांक size;

	size = simple_म_से_अदीर्घ(opt, &opt, 0);

	अगर (opt) अणु
		चयन (*opt) अणु
		हाल 'M':
		हाल 'm':
			size *= 1024;
			fallthrough;
		हाल 'K':
		हाल 'k':
			size *= 1024;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	current_par.dram_size = size;
पूर्ण

अटल काष्ठा options अणु
	अक्षर *name;
	व्योम (*parse)(अक्षर *opt);
पूर्ण opt_table[] = अणु
	अणु "mon",     acornfb_parse_mon     पूर्ण,
	अणु "montype", acornfb_parse_montype पूर्ण,
	अणु "dram",    acornfb_parse_dram    पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक acornfb_setup(अक्षर *options)
अणु
	काष्ठा options *optp;
	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	acornfb_init_fbinfo();

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;

		क्रम (optp = opt_table; optp->name; optp++) अणु
			पूर्णांक optlen;

			optlen = म_माप(optp->name);

			अगर (म_भेदन(opt, optp->name, optlen) == 0 &&
			    opt[optlen] == ':') अणु
				optp->parse(opt + optlen + 1);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!optp->name)
			prपूर्णांकk(KERN_ERR "acornfb: unknown parameter: %s\n",
			       opt);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Detect type of monitor connected
 *  For now, we just assume SVGA
 */
अटल पूर्णांक acornfb_detect_monitortype(व्योम)
अणु
	वापस 4;
पूर्ण

अटल पूर्णांक acornfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित दीर्घ size;
	u_पूर्णांक h_sync, v_sync;
	पूर्णांक rc, i;
	अक्षर *option = शून्य;

	अगर (fb_get_options("acornfb", &option))
		वापस -ENODEV;
	acornfb_setup(option);

	acornfb_init_fbinfo();

	current_par.dev = &dev->dev;

	अगर (current_par.montype == -1)
		current_par.montype = acornfb_detect_monitortype();

	अगर (current_par.montype == -1 || current_par.montype > NR_MONTYPES)
		current_par.montype = 4;

	अगर (current_par.montype >= 0) अणु
		fb_info.monspecs = monspecs[current_par.montype];
		fb_info.monspecs.dpms = current_par.dpms;
	पूर्ण

	/*
	 * Try to select a suitable शेष mode
	 */
	क्रम (i = 0; i < ARRAY_SIZE(modedb); i++) अणु
		अचिन्हित दीर्घ hs;

		hs = modedb[i].refresh *
		     (modedb[i].yres + modedb[i].upper_margin +
		      modedb[i].lower_margin + modedb[i].vsync_len);
		अगर (modedb[i].xres == DEFAULT_XRES &&
		    modedb[i].yres == DEFAULT_YRES &&
		    modedb[i].refresh >= fb_info.monspecs.vfmin &&
		    modedb[i].refresh <= fb_info.monspecs.vfmax &&
		    hs                >= fb_info.monspecs.hfmin &&
		    hs                <= fb_info.monspecs.hfmax) अणु
			acornfb_शेष_mode = modedb[i];
			अवरोध;
		पूर्ण
	पूर्ण

	fb_info.screen_base    = (अक्षर *)SCREEN_BASE;
	fb_info.fix.smem_start = SCREEN_START;
	current_par.using_vram = 0;

	/*
	 * If vram_size is set, we are using VRAM in
	 * a Risc PC.  However, अगर the user has specअगरied
	 * an amount of DRAM then use that instead.
	 */
	अगर (vram_size && !current_par.dram_size) अणु
		size = vram_size;
		current_par.vram_half_sam = vram_size / 1024;
		current_par.using_vram = 1;
	पूर्ण अन्यथा अगर (current_par.dram_size)
		size = current_par.dram_size;
	अन्यथा
		size = MAX_SIZE;

	/*
	 * Limit maximum screen size.
	 */
	अगर (size > MAX_SIZE)
		size = MAX_SIZE;

	size = PAGE_ALIGN(size);

#अगर defined(HAS_VIDC20)
	अगर (!current_par.using_vram) अणु
		dma_addr_t handle;
		व्योम *base;

		/*
		 * RiscPC needs to allocate the DRAM memory
		 * क्रम the framebuffer अगर we are not using
		 * VRAM.
		 */
		base = dma_alloc_wc(current_par.dev, size, &handle,
				    GFP_KERNEL);
		अगर (base == शून्य) अणु
			prपूर्णांकk(KERN_ERR "acornfb: unable to allocate screen memory\n");
			वापस -ENOMEM;
		पूर्ण

		fb_info.screen_base = base;
		fb_info.fix.smem_start = handle;
	पूर्ण
#पूर्ण_अगर
	fb_info.fix.smem_len = size;
	current_par.palette_size   = VIDC_PALETTE_SIZE;

	/*
	 * Lookup the timing क्रम this resolution.  If we can't
	 * find it, then we can't restore it अगर we change
	 * the resolution, so we disable this feature.
	 */
	करो अणु
		rc = fb_find_mode(&fb_info.var, &fb_info, शून्य, modedb,
				 ARRAY_SIZE(modedb),
				 &acornfb_शेष_mode, DEFAULT_BPP);
		/*
		 * If we found an exact match, all ok.
		 */
		अगर (rc == 1)
			अवरोध;

		rc = fb_find_mode(&fb_info.var, &fb_info, शून्य, शून्य, 0,
				  &acornfb_शेष_mode, DEFAULT_BPP);
		/*
		 * If we found an exact match, all ok.
		 */
		अगर (rc == 1)
			अवरोध;

		rc = fb_find_mode(&fb_info.var, &fb_info, शून्य, modedb,
				 ARRAY_SIZE(modedb),
				 &acornfb_शेष_mode, DEFAULT_BPP);
		अगर (rc)
			अवरोध;

		rc = fb_find_mode(&fb_info.var, &fb_info, शून्य, शून्य, 0,
				  &acornfb_शेष_mode, DEFAULT_BPP);
	पूर्ण जबतक (0);

	/*
	 * If we didn't find an exact match, try the
	 * generic database.
	 */
	अगर (rc == 0) अणु
		prपूर्णांकk("Acornfb: no valid mode found\n");
		वापस -EINVAL;
	पूर्ण

	h_sync = 1953125000 / fb_info.var.pixघड़ी;
	h_sync = h_sync * 512 / (fb_info.var.xres + fb_info.var.left_margin +
		 fb_info.var.right_margin + fb_info.var.hsync_len);
	v_sync = h_sync / (fb_info.var.yres + fb_info.var.upper_margin +
		 fb_info.var.lower_margin + fb_info.var.vsync_len);

	prपूर्णांकk(KERN_INFO "Acornfb: %dkB %cRAM, %s, using %dx%d, %d.%03dkHz, %dHz\n",
		fb_info.fix.smem_len / 1024,
		current_par.using_vram ? 'V' : 'D',
		VIDC_NAME, fb_info.var.xres, fb_info.var.yres,
		h_sync / 1000, h_sync % 1000, v_sync);

	prपूर्णांकk(KERN_INFO "Acornfb: Monitor: %d.%03d-%d.%03dkHz, %d-%dHz%s\n",
		fb_info.monspecs.hfmin / 1000, fb_info.monspecs.hfmin % 1000,
		fb_info.monspecs.hfmax / 1000, fb_info.monspecs.hfmax % 1000,
		fb_info.monspecs.vfmin, fb_info.monspecs.vfmax,
		fb_info.monspecs.dpms ? ", DPMS" : "");

	अगर (fb_set_var(&fb_info, &fb_info.var))
		prपूर्णांकk(KERN_ERR "Acornfb: unable to set display parameters\n");

	अगर (रेजिस्टर_framebuffer(&fb_info) < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver acornfb_driver = अणु
	.probe	= acornfb_probe,
	.driver	= अणु
		.name	= "acornfb",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init acornfb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&acornfb_driver);
पूर्ण

module_init(acornfb_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("VIDC 1/1a/20 framebuffer driver");
MODULE_LICENSE("GPL");
