<शैली गुरु>
/*
 *  SGI GBE frame buffer driver
 *
 *  Copyright (C) 1999 Silicon Graphics, Inc. - Jeffrey Newquist
 *  Copyright (C) 2002 Vivien Chappelier <vivien.chappelier@linux-mips.org>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#अगर_घोषित CONFIG_MIPS
#समावेश <यंत्र/addrspace.h>
#पूर्ण_अगर
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <video/gbe.h>

अटल काष्ठा sgi_gbe *gbe;

काष्ठा gbefb_par अणु
	काष्ठा fb_var_screeninfo var;
	काष्ठा gbe_timing_info timing;
	पूर्णांक wc_cookie;
	पूर्णांक valid;
पूर्ण;

#घोषणा GBE_BASE	0x16000000 /* SGI O2 */

/* macro क्रम fastest ग_लिखो-though access to the framebuffer */
#अगर_घोषित CONFIG_MIPS
#अगर_घोषित CONFIG_CPU_R10000
#घोषणा pgprot_fb(_prot) (((_prot) & (~_CACHE_MASK)) | _CACHE_UNCACHED_ACCELERATED)
#अन्यथा
#घोषणा pgprot_fb(_prot) (((_prot) & (~_CACHE_MASK)) | _CACHE_CACHABLE_NO_WA)
#पूर्ण_अगर
#पूर्ण_अगर

/*
 *  RAM we reserve क्रम the frame buffer. This defines the maximum screen
 *  size
 */
#अगर CONFIG_FB_GBE_MEM > 8
#त्रुटि GBE Framebuffer cannot use more than 8MB of memory
#पूर्ण_अगर

#घोषणा TILE_SHIFT 16
#घोषणा TILE_SIZE (1 << TILE_SHIFT)
#घोषणा TILE_MASK (TILE_SIZE - 1)

अटल अचिन्हित पूर्णांक gbe_mem_size = CONFIG_FB_GBE_MEM * 1024*1024;
अटल व्योम *gbe_mem;
अटल dma_addr_t gbe_dma_addr;
अटल अचिन्हित दीर्घ gbe_mem_phys;

अटल काष्ठा अणु
	uपूर्णांक16_t *cpu;
	dma_addr_t dma;
पूर्ण gbe_tiles;

अटल पूर्णांक gbe_revision;

अटल पूर्णांक ypan, ywrap;

अटल uपूर्णांक32_t pseuकरो_palette[16];
अटल uपूर्णांक32_t gbe_cmap[256];
अटल पूर्णांक gbe_turned_on; /* 0 turned off, 1 turned on */

अटल अक्षर *mode_option = शून्य;

/* शेष CRT mode */
अटल काष्ठा fb_var_screeninfo शेष_var_CRT = अणु
	/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz करोtघड़ी) */
	.xres		= 640,
	.yres		= 480,
	.xres_भव	= 640,
	.yres_भव	= 480,
	.xoffset	= 0,
	.yoffset	= 0,
	.bits_per_pixel	= 8,
	.grayscale	= 0,
	.red		= अणु 0, 8, 0 पूर्ण,
	.green		= अणु 0, 8, 0 पूर्ण,
	.blue		= अणु 0, 8, 0 पूर्ण,
	.transp		= अणु 0, 0, 0 पूर्ण,
	.nonstd		= 0,
	.activate	= 0,
	.height		= -1,
	.width		= -1,
	.accel_flags	= 0,
	.pixघड़ी	= 39722,	/* picoseconds */
	.left_margin	= 48,
	.right_margin	= 16,
	.upper_margin	= 33,
	.lower_margin	= 10,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.sync		= 0,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

/* शेष LCD mode */
अटल काष्ठा fb_var_screeninfo शेष_var_LCD = अणु
	/* 1600x1024, 8 bpp */
	.xres		= 1600,
	.yres		= 1024,
	.xres_भव	= 1600,
	.yres_भव	= 1024,
	.xoffset	= 0,
	.yoffset	= 0,
	.bits_per_pixel	= 8,
	.grayscale	= 0,
	.red		= अणु 0, 8, 0 पूर्ण,
	.green		= अणु 0, 8, 0 पूर्ण,
	.blue		= अणु 0, 8, 0 पूर्ण,
	.transp		= अणु 0, 0, 0 पूर्ण,
	.nonstd		= 0,
	.activate	= 0,
	.height		= -1,
	.width		= -1,
	.accel_flags	= 0,
	.pixघड़ी	= 9353,
	.left_margin	= 20,
	.right_margin	= 30,
	.upper_margin	= 37,
	.lower_margin	= 3,
	.hsync_len	= 20,
	.vsync_len	= 3,
	.sync		= 0,
	.vmode		= FB_VMODE_NONINTERLACED
पूर्ण;

/* शेष modedb mode */
/* 640x480, 60 Hz, Non-Interlaced (25.172 MHz करोtघड़ी) */
अटल काष्ठा fb_videomode शेष_mode_CRT = अणु
	.refresh	= 60,
	.xres		= 640,
	.yres		= 480,
	.pixघड़ी	= 39722,
	.left_margin	= 48,
	.right_margin	= 16,
	.upper_margin	= 33,
	.lower_margin	= 10,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.sync		= 0,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;
/* 1600x1024 SGI flatpanel 1600sw */
अटल काष्ठा fb_videomode शेष_mode_LCD = अणु
	/* 1600x1024, 8 bpp */
	.xres		= 1600,
	.yres		= 1024,
	.pixघड़ी	= 9353,
	.left_margin	= 20,
	.right_margin	= 30,
	.upper_margin	= 37,
	.lower_margin	= 3,
	.hsync_len	= 20,
	.vsync_len	= 3,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_videomode *शेष_mode = &शेष_mode_CRT;
अटल काष्ठा fb_var_screeninfo *शेष_var = &शेष_var_CRT;

अटल पूर्णांक flat_panel_enabled = 0;

अटल व्योम gbe_reset(व्योम)
अणु
	/* Turn on करोtघड़ी PLL */
	gbe->ctrlstat = 0x300aa000;
पूर्ण


/*
 * Function:	gbe_turn_off
 * Parameters:	(None)
 * Description:	This should turn off the monitor and gbe.  This is used
 *              when चयनing between the serial console and the graphics
 *              console.
 */

अटल व्योम gbe_turn_off(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val, y, vpixen_off;

	gbe_turned_on = 0;

	/* check अगर pixel counter is on */
	val = gbe->vt_xy;
	अगर (GET_GBE_FIELD(VT_XY, FREEZE, val) == 1)
		वापस;

	/* turn off DMA */
	val = gbe->ovr_control;
	SET_GBE_FIELD(OVR_CONTROL, OVR_DMA_ENABLE, val, 0);
	gbe->ovr_control = val;
	udelay(1000);
	val = gbe->frm_control;
	SET_GBE_FIELD(FRM_CONTROL, FRM_DMA_ENABLE, val, 0);
	gbe->frm_control = val;
	udelay(1000);
	val = gbe->did_control;
	SET_GBE_FIELD(DID_CONTROL, DID_DMA_ENABLE, val, 0);
	gbe->did_control = val;
	udelay(1000);

	/* We have to रुको through two vertical retrace periods beक्रमe
	 * the pixel DMA is turned off क्रम sure. */
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->frm_inhwctrl;
		अगर (GET_GBE_FIELD(FRM_INHWCTRL, FRM_DMA_ENABLE, val)) अणु
			udelay(10);
		पूर्ण अन्यथा अणु
			val = gbe->ovr_inhwctrl;
			अगर (GET_GBE_FIELD(OVR_INHWCTRL, OVR_DMA_ENABLE, val)) अणु
				udelay(10);
			पूर्ण अन्यथा अणु
				val = gbe->did_inhwctrl;
				अगर (GET_GBE_FIELD(DID_INHWCTRL, DID_DMA_ENABLE, val)) अणु
					udelay(10);
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn off DMA timed out\n");

	/* रुको क्रम vpixen_off */
	val = gbe->vt_vpixen;
	vpixen_off = GET_GBE_FIELD(VT_VPIXEN, VPIXEN_OFF, val);

	क्रम (i = 0; i < 100000; i++) अणु
		val = gbe->vt_xy;
		y = GET_GBE_FIELD(VT_XY, Y, val);
		अगर (y < vpixen_off)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == 100000)
		prपूर्णांकk(KERN_ERR
		       "gbefb: wait for vpixen_off timed out\n");
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->vt_xy;
		y = GET_GBE_FIELD(VT_XY, Y, val);
		अगर (y > vpixen_off)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: wait for vpixen_off timed out\n");

	/* turn off pixel counter */
	val = 0;
	SET_GBE_FIELD(VT_XY, FREEZE, val, 1);
	gbe->vt_xy = val;
	mdelay(10);
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->vt_xy;
		अगर (GET_GBE_FIELD(VT_XY, FREEZE, val) != 1)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn off pixel clock timed out\n");

	/* turn off करोt घड़ी */
	val = gbe->करोtघड़ी;
	SET_GBE_FIELD(DOTCLK, RUN, val, 0);
	gbe->करोtघड़ी = val;
	mdelay(10);
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->करोtघड़ी;
		अगर (GET_GBE_FIELD(DOTCLK, RUN, val))
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn off dotclock timed out\n");

	/* reset the frame DMA FIFO */
	val = gbe->frm_माप_प्रकारile;
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_FIFO_RESET, val, 1);
	gbe->frm_माप_प्रकारile = val;
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_FIFO_RESET, val, 0);
	gbe->frm_माप_प्रकारile = val;
पूर्ण

अटल व्योम gbe_turn_on(व्योम)
अणु
	अचिन्हित पूर्णांक val, i;

	/*
	 * Check अगर pixel counter is off, क्रम unknown reason this
	 * code hangs Visual Workstations
	 */
	अगर (gbe_revision < 2) अणु
		val = gbe->vt_xy;
		अगर (GET_GBE_FIELD(VT_XY, FREEZE, val) == 0)
			वापस;
	पूर्ण

	/* turn on करोt घड़ी */
	val = gbe->करोtघड़ी;
	SET_GBE_FIELD(DOTCLK, RUN, val, 1);
	gbe->करोtघड़ी = val;
	mdelay(10);
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->करोtघड़ी;
		अगर (GET_GBE_FIELD(DOTCLK, RUN, val) != 1)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn on dotclock timed out\n");

	/* turn on pixel counter */
	val = 0;
	SET_GBE_FIELD(VT_XY, FREEZE, val, 0);
	gbe->vt_xy = val;
	mdelay(10);
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->vt_xy;
		अगर (GET_GBE_FIELD(VT_XY, FREEZE, val))
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn on pixel clock timed out\n");

	/* turn on DMA */
	val = gbe->frm_control;
	SET_GBE_FIELD(FRM_CONTROL, FRM_DMA_ENABLE, val, 1);
	gbe->frm_control = val;
	udelay(1000);
	क्रम (i = 0; i < 10000; i++) अणु
		val = gbe->frm_inhwctrl;
		अगर (GET_GBE_FIELD(FRM_INHWCTRL, FRM_DMA_ENABLE, val) != 1)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == 10000)
		prपूर्णांकk(KERN_ERR "gbefb: turn on DMA timed out\n");

	gbe_turned_on = 1;
पूर्ण

अटल व्योम gbe_loadcmap(व्योम)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 256; i++) अणु
		क्रम (j = 0; j < 1000 && gbe->cm_fअगरo >= 63; j++)
			udelay(10);
		अगर (j == 1000)
			prपूर्णांकk(KERN_ERR "gbefb: cmap FIFO timeout\n");

		gbe->cmap[i] = gbe_cmap[i];
	पूर्ण
पूर्ण

/*
 *  Blank the display.
 */
अटल पूर्णांक gbefb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:		/* unblank */
		gbe_turn_on();
		gbe_loadcmap();
		अवरोध;

	हाल FB_BLANK_NORMAL:		/* blank */
		gbe_turn_off();
		अवरोध;

	शेष:
		/* Nothing */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  Setup flatpanel related रेजिस्टरs.
 */
अटल व्योम gbefb_setup_flatpanel(काष्ठा gbe_timing_info *timing)
अणु
	पूर्णांक fp_wid, fp_hgt, fp_vbs, fp_vbe;
	u32 outputVal = 0;

	SET_GBE_FIELD(VT_FLAGS, HDRV_INVERT, outputVal,
		(timing->flags & FB_SYNC_HOR_HIGH_ACT) ? 0 : 1);
	SET_GBE_FIELD(VT_FLAGS, VDRV_INVERT, outputVal,
		(timing->flags & FB_SYNC_VERT_HIGH_ACT) ? 0 : 1);
	gbe->vt_flags = outputVal;

	/* Turn on the flat panel */
	fp_wid = 1600;
	fp_hgt = 1024;
	fp_vbs = 0;
	fp_vbe = 1600;
	timing->pll_m = 4;
	timing->pll_n = 1;
	timing->pll_p = 0;

	outputVal = 0;
	SET_GBE_FIELD(FP_DE, ON, outputVal, fp_vbs);
	SET_GBE_FIELD(FP_DE, OFF, outputVal, fp_vbe);
	gbe->fp_de = outputVal;
	outputVal = 0;
	SET_GBE_FIELD(FP_HDRV, OFF, outputVal, fp_wid);
	gbe->fp_hdrv = outputVal;
	outputVal = 0;
	SET_GBE_FIELD(FP_VDRV, ON, outputVal, 1);
	SET_GBE_FIELD(FP_VDRV, OFF, outputVal, fp_hgt + 1);
	gbe->fp_vdrv = outputVal;
पूर्ण

काष्ठा gbe_pll_info अणु
	पूर्णांक घड़ी_rate;
	पूर्णांक fvco_min;
	पूर्णांक fvco_max;
पूर्ण;

अटल काष्ठा gbe_pll_info gbe_pll_table[2] = अणु
	अणु 20, 80, 220 पूर्ण,
	अणु 27, 80, 220 पूर्ण,
पूर्ण;

अटल पूर्णांक compute_gbe_timing(काष्ठा fb_var_screeninfo *var,
			      काष्ठा gbe_timing_info *timing)
अणु
	पूर्णांक pll_m, pll_n, pll_p, error, best_m, best_n, best_p, best_error;
	पूर्णांक pixघड़ी;
	काष्ठा gbe_pll_info *gbe_pll;

	अगर (gbe_revision < 2)
		gbe_pll = &gbe_pll_table[0];
	अन्यथा
		gbe_pll = &gbe_pll_table[1];

	/* Determine valid resolution and timing
	 * GBE crystal runs at 20Mhz or 27Mhz
	 * pll_m, pll_n, pll_p define the following frequencies
	 * fvco = pll_m * 20Mhz / pll_n
	 * fout = fvco / (2**pll_p) */
	best_error = 1000000000;
	best_n = best_m = best_p = 0;
	क्रम (pll_p = 0; pll_p < 4; pll_p++)
		क्रम (pll_m = 1; pll_m < 256; pll_m++)
			क्रम (pll_n = 1; pll_n < 64; pll_n++) अणु
				pixघड़ी = (1000000 / gbe_pll->घड़ी_rate) *
						(pll_n << pll_p) / pll_m;

				error = var->pixघड़ी - pixघड़ी;

				अगर (error < 0)
					error = -error;

				अगर (error < best_error &&
				    pll_m / pll_n >
				    gbe_pll->fvco_min / gbe_pll->घड़ी_rate &&
 				    pll_m / pll_n <
				    gbe_pll->fvco_max / gbe_pll->घड़ी_rate) अणु
					best_error = error;
					best_m = pll_m;
					best_n = pll_n;
					best_p = pll_p;
				पूर्ण
			पूर्ण

	अगर (!best_n || !best_m)
		वापस -EINVAL;	/* Resolution to high */

	pixघड़ी = (1000000 / gbe_pll->घड़ी_rate) *
		(best_n << best_p) / best_m;

	/* set video timing inक्रमmation */
	अगर (timing) अणु
		timing->width = var->xres;
		timing->height = var->yres;
		timing->pll_m = best_m;
		timing->pll_n = best_n;
		timing->pll_p = best_p;
		timing->cfreq = gbe_pll->घड़ी_rate * 1000 * timing->pll_m /
			(timing->pll_n << timing->pll_p);
		timing->htotal = var->left_margin + var->xres +
				var->right_margin + var->hsync_len;
		timing->vtotal = var->upper_margin + var->yres +
				var->lower_margin + var->vsync_len;
		timing->fields_sec = 1000 * timing->cfreq / timing->htotal *
				1000 / timing->vtotal;
		timing->hblank_start = var->xres;
		timing->vblank_start = var->yres;
		timing->hblank_end = timing->htotal;
		timing->hsync_start = var->xres + var->right_margin + 1;
		timing->hsync_end = timing->hsync_start + var->hsync_len;
		timing->vblank_end = timing->vtotal;
		timing->vsync_start = var->yres + var->lower_margin + 1;
		timing->vsync_end = timing->vsync_start + var->vsync_len;
	पूर्ण

	वापस pixघड़ी;
पूर्ण

अटल व्योम gbe_set_timing_info(काष्ठा gbe_timing_info *timing)
अणु
	पूर्णांक temp;
	अचिन्हित पूर्णांक val;

	/* setup करोt घड़ी PLL */
	val = 0;
	SET_GBE_FIELD(DOTCLK, M, val, timing->pll_m - 1);
	SET_GBE_FIELD(DOTCLK, N, val, timing->pll_n - 1);
	SET_GBE_FIELD(DOTCLK, P, val, timing->pll_p);
	SET_GBE_FIELD(DOTCLK, RUN, val, 0);	/* करो not start yet */
	gbe->करोtघड़ी = val;
	mdelay(10);

	/* setup pixel counter */
	val = 0;
	SET_GBE_FIELD(VT_XYMAX, MAXX, val, timing->htotal);
	SET_GBE_FIELD(VT_XYMAX, MAXY, val, timing->vtotal);
	gbe->vt_xymax = val;

	/* setup video timing संकेतs */
	val = 0;
	SET_GBE_FIELD(VT_VSYNC, VSYNC_ON, val, timing->vsync_start);
	SET_GBE_FIELD(VT_VSYNC, VSYNC_OFF, val, timing->vsync_end);
	gbe->vt_vsync = val;
	val = 0;
	SET_GBE_FIELD(VT_HSYNC, HSYNC_ON, val, timing->hsync_start);
	SET_GBE_FIELD(VT_HSYNC, HSYNC_OFF, val, timing->hsync_end);
	gbe->vt_hsync = val;
	val = 0;
	SET_GBE_FIELD(VT_VBLANK, VBLANK_ON, val, timing->vblank_start);
	SET_GBE_FIELD(VT_VBLANK, VBLANK_OFF, val, timing->vblank_end);
	gbe->vt_vblank = val;
	val = 0;
	SET_GBE_FIELD(VT_HBLANK, HBLANK_ON, val,
		      timing->hblank_start - 5);
	SET_GBE_FIELD(VT_HBLANK, HBLANK_OFF, val,
		      timing->hblank_end - 3);
	gbe->vt_hblank = val;

	/* setup पूर्णांकernal timing संकेतs */
	val = 0;
	SET_GBE_FIELD(VT_VCMAP, VCMAP_ON, val, timing->vblank_start);
	SET_GBE_FIELD(VT_VCMAP, VCMAP_OFF, val, timing->vblank_end);
	gbe->vt_vcmap = val;
	val = 0;
	SET_GBE_FIELD(VT_HCMAP, HCMAP_ON, val, timing->hblank_start);
	SET_GBE_FIELD(VT_HCMAP, HCMAP_OFF, val, timing->hblank_end);
	gbe->vt_hcmap = val;

	val = 0;
	temp = timing->vblank_start - timing->vblank_end - 1;
	अगर (temp > 0)
		temp = -temp;

	अगर (flat_panel_enabled)
		gbefb_setup_flatpanel(timing);

	SET_GBE_FIELD(DID_START_XY, DID_STARTY, val, (u32) temp);
	अगर (timing->hblank_end >= 20)
		SET_GBE_FIELD(DID_START_XY, DID_STARTX, val,
			      timing->hblank_end - 20);
	अन्यथा
		SET_GBE_FIELD(DID_START_XY, DID_STARTX, val,
			      timing->htotal - (20 - timing->hblank_end));
	gbe->did_start_xy = val;

	val = 0;
	SET_GBE_FIELD(CRS_START_XY, CRS_STARTY, val, (u32) (temp + 1));
	अगर (timing->hblank_end >= GBE_CRS_MAGIC)
		SET_GBE_FIELD(CRS_START_XY, CRS_STARTX, val,
			      timing->hblank_end - GBE_CRS_MAGIC);
	अन्यथा
		SET_GBE_FIELD(CRS_START_XY, CRS_STARTX, val,
			      timing->htotal - (GBE_CRS_MAGIC -
						timing->hblank_end));
	gbe->crs_start_xy = val;

	val = 0;
	SET_GBE_FIELD(VC_START_XY, VC_STARTY, val, (u32) temp);
	SET_GBE_FIELD(VC_START_XY, VC_STARTX, val, timing->hblank_end - 4);
	gbe->vc_start_xy = val;

	val = 0;
	temp = timing->hblank_end - GBE_PIXEN_MAGIC_ON;
	अगर (temp < 0)
		temp += timing->htotal;	/* allow blank to wrap around */

	SET_GBE_FIELD(VT_HPIXEN, HPIXEN_ON, val, temp);
	SET_GBE_FIELD(VT_HPIXEN, HPIXEN_OFF, val,
		      ((temp + timing->width -
			GBE_PIXEN_MAGIC_OFF) % timing->htotal));
	gbe->vt_hpixen = val;

	val = 0;
	SET_GBE_FIELD(VT_VPIXEN, VPIXEN_ON, val, timing->vblank_end);
	SET_GBE_FIELD(VT_VPIXEN, VPIXEN_OFF, val, timing->vblank_start);
	gbe->vt_vpixen = val;

	/* turn off sync on green */
	val = 0;
	SET_GBE_FIELD(VT_FLAGS, SYNC_LOW, val, 1);
	gbe->vt_flags = val;
पूर्ण

/*
 *  Set the hardware according to 'par'.
 */

अटल पूर्णांक gbefb_set_par(काष्ठा fb_info *info)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val;
	पूर्णांक wholeTilesX, partTilesX, maxPixelsPerTileX;
	पूर्णांक height_pix;
	पूर्णांक xpmax, ypmax;	/* Monitor resolution */
	पूर्णांक bytesPerPixel;	/* Bytes per pixel */
	काष्ठा gbefb_par *par = (काष्ठा gbefb_par *) info->par;

	compute_gbe_timing(&info->var, &par->timing);

	bytesPerPixel = info->var.bits_per_pixel / 8;
	info->fix.line_length = info->var.xres_भव * bytesPerPixel;
	xpmax = par->timing.width;
	ypmax = par->timing.height;

	/* turn off GBE */
	gbe_turn_off();

	/* set timing info */
	gbe_set_timing_info(&par->timing);

	/* initialize DIDs */
	val = 0;
	चयन (bytesPerPixel) अणु
	हाल 1:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_I8);
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 2:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_ARGB5);
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	हाल 4:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_RGB8);
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	पूर्ण
	SET_GBE_FIELD(WID, BUF, val, GBE_BMODE_BOTH);

	क्रम (i = 0; i < 32; i++)
		gbe->mode_regs[i] = val;

	/* Initialize पूर्णांकerrupts */
	gbe->vt_पूर्णांकr01 = 0xffffffff;
	gbe->vt_पूर्णांकr23 = 0xffffffff;

	/* HACK:
	   The GBE hardware uses a tiled memory to screen mapping. Tiles are
	   blocks of 512x128, 256x128 or 128x128 pixels, respectively क्रम 8bit,
	   16bit and 32 bit modes (64 kB). They cover the screen with partial
	   tiles on the right and/or bottom of the screen अगर needed.
	   For example in 640x480 8 bit mode the mapping is:

	   <-------- 640 ----->
	   <---- 512 ----><128|384 offscreen>
	   ^  ^
	   | 128    [tile 0]        [tile 1]
	   |  v
	   ^
	   4 128    [tile 2]        [tile 3]
	   8  v
	   0  ^
	   128    [tile 4]        [tile 5]
	   |  v
	   |  ^
	   v  96    [tile 6]        [tile 7]
	   32 offscreen

	   Tiles have the advantage that they can be allocated inभागidually in
	   memory. However, this mapping is not linear at all, which is not
	   really convenient. In order to support linear addressing, the GBE
	   DMA hardware is fooled पूर्णांकo thinking the screen is only one tile
	   large and but has a greater height, so that the DMA transfer covers
	   the same region.
	   Tiles are still allocated as independent chunks of 64KB of
	   continuous physical memory and remapped so that the kernel sees the
	   framebuffer as a continuous भव memory. The GBE tile table is
	   set up so that each tile references one of these 64k blocks:

	   GBE -> tile list    framebuffer           TLB   <------------ CPU
	          [ tile 0 ] -> [ 64KB ]  <- [ 16x 4KB page entries ]     ^
	             ...           ...              ...       linear भव FB
	          [ tile n ] -> [ 64KB ]  <- [ 16x 4KB page entries ]     v


	   The GBE hardware is then told that the buffer is 512*tweaked_height,
	   with tweaked_height = real_width*real_height/pixels_per_tile.
	   Thus the GBE hardware will scan the first tile, filing the first 64k
	   covered region of the screen, and then will proceed to the next
	   tile, until the whole screen is covered.

	   Here is what would happen at 640x480 8bit:

	   normal tiling               linear
	   ^   11111111111111112222    11111111111111111111  ^
	   128 11111111111111112222    11111111111111111111 102 lines
	       11111111111111112222    11111111111111111111  v
	   V   11111111111111112222    11111111222222222222
	       33333333333333334444    22222222222222222222
	       33333333333333334444    22222222222222222222
	       <      512     >        <  256 >               102*640+256 = 64k

	   NOTE: The only mode क्रम which this is not working is 800x600 8bit,
	   as 800*600/512 = 937.5 which is not पूर्णांकeger and thus causes
	   flickering.
	   I guess this is not so important as one can use 640x480 8bit or
	   800x600 16bit anyway.
	 */

	/* Tell gbe about the tiles table location */
	/* tile_ptr -> [ tile 1 ] -> FB mem */
	/*             [ tile 2 ] -> FB mem */
	/*               ...                */
	val = 0;
	SET_GBE_FIELD(FRM_CONTROL, FRM_TILE_PTR, val, gbe_tiles.dma >> 9);
	SET_GBE_FIELD(FRM_CONTROL, FRM_DMA_ENABLE, val, 0); /* करो not start */
	SET_GBE_FIELD(FRM_CONTROL, FRM_LINEAR, val, 0);
	gbe->frm_control = val;

	maxPixelsPerTileX = 512 / bytesPerPixel;
	wholeTilesX = 1;
	partTilesX = 0;

	/* Initialize the framebuffer */
	val = 0;
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_WIDTH_TILE, val, wholeTilesX);
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_RHS, val, partTilesX);

	चयन (bytesPerPixel) अणु
	हाल 1:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_8);
		अवरोध;
	हाल 2:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_16);
		अवरोध;
	हाल 4:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_32);
		अवरोध;
	पूर्ण
	gbe->frm_माप_प्रकारile = val;

	/* compute tweaked height */
	height_pix = xpmax * ypmax / maxPixelsPerTileX;

	val = 0;
	SET_GBE_FIELD(FRM_SIZE_PIXEL, FB_HEIGHT_PIX, val, height_pix);
	gbe->frm_size_pixel = val;

	/* turn off DID and overlay DMA */
	gbe->did_control = 0;
	gbe->ovr_width_tile = 0;

	/* Turn off mouse cursor */
	gbe->crs_ctl = 0;

	/* Turn on GBE */
	gbe_turn_on();

	/* Initialize the gamma map */
	udelay(10);
	क्रम (i = 0; i < 256; i++)
		gbe->gmap[i] = (i << 24) | (i << 16) | (i << 8);

	/* Initialize the color map */
	क्रम (i = 0; i < 256; i++)
		gbe_cmap[i] = (i << 8) | (i << 16) | (i << 24);

	gbe_loadcmap();

	वापस 0;
पूर्ण

अटल व्योम gbefb_encode_fix(काष्ठा fb_fix_screeninfo *fix,
			     काष्ठा fb_var_screeninfo *var)
अणु
	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));
	म_नकल(fix->id, "SGI GBE");
	fix->smem_start = (अचिन्हित दीर्घ) gbe_mem;
	fix->smem_len = gbe_mem_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	fix->accel = FB_ACCEL_NONE;
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	शेष:
		fix->visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	पूर्ण
	fix->ywrapstep = 0;
	fix->xpanstep = 0;
	fix->ypanstep = 0;
	fix->line_length = var->xres_भव * var->bits_per_pixel / 8;
	fix->mmio_start = GBE_BASE;
	fix->mmio_len = माप(काष्ठा sgi_gbe);
पूर्ण

/*
 *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
 *  rounded करोwn to the hardware's capabilities (according to the
 *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
 */

अटल पूर्णांक gbefb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			     अचिन्हित blue, अचिन्हित transp,
			     काष्ठा fb_info *info)
अणु
	पूर्णांक i;

	अगर (regno > 255)
		वापस 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	अगर (info->var.bits_per_pixel <= 8) अणु
		gbe_cmap[regno] = (red << 24) | (green << 16) | (blue << 8);
		अगर (gbe_turned_on) अणु
			/* रुको क्रम the color map FIFO to have a मुक्त entry */
			क्रम (i = 0; i < 1000 && gbe->cm_fअगरo >= 63; i++)
				udelay(10);
			अगर (i == 1000) अणु
				prपूर्णांकk(KERN_ERR "gbefb: cmap FIFO timeout\n");
				वापस 1;
			पूर्ण
			gbe->cmap[regno] = gbe_cmap[regno];
		पूर्ण
	पूर्ण अन्यथा अगर (regno < 16) अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 15:
		हाल 16:
			red >>= 3;
			green >>= 3;
			blue >>= 3;
			pseuकरो_palette[regno] =
				(red << info->var.red.offset) |
				(green << info->var.green.offset) |
				(blue << info->var.blue.offset);
			अवरोध;
		हाल 32:
			pseuकरो_palette[regno] =
				(red << info->var.red.offset) |
				(green << info->var.green.offset) |
				(blue << info->var.blue.offset);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Check video mode validity, eventually modअगरy var to best match.
 */
अटल पूर्णांक gbefb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक line_length;
	काष्ठा gbe_timing_info timing;
	पूर्णांक ret;

	/* Limit bpp to 8, 16, and 32 */
	अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;
	अन्यथा
		वापस -EINVAL;

	/* Check the mode can be mapped linearly with the tile table trick. */
	/* This requires width x height x bytes/pixel be a multiple of 512 */
	अगर ((var->xres * var->yres * var->bits_per_pixel) & 4095)
		वापस -EINVAL;

	var->grayscale = 0;	/* No grayscale क्रम now */

	ret = compute_gbe_timing(var, &timing);
	var->pixघड़ी = ret;
	अगर (ret < 0)
		वापस -EINVAL;

	/* Adjust भव resolution, अगर necessary */
	अगर (var->xres > var->xres_भव || (!ywrap && !ypan))
		var->xres_भव = var->xres;
	अगर (var->yres > var->yres_भव || (!ywrap && !ypan))
		var->yres_भव = var->yres;

	अगर (var->vmode & FB_VMODE_CONUPDATE) अणु
		var->vmode |= FB_VMODE_YWRAP;
		var->xoffset = info->var.xoffset;
		var->yoffset = info->var.yoffset;
	पूर्ण

	/* No grayscale क्रम now */
	var->grayscale = 0;

	/* Memory limit */
	line_length = var->xres_भव * var->bits_per_pixel / 8;
	अगर (line_length * var->yres_भव > gbe_mem_size)
		वापस -ENOMEM;	/* Virtual resolution too high */

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 16:		/* RGB 1555 */
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 32:		/* RGB 8888 */
		var->red.offset = 24;
		var->red.length = 8;
		var->green.offset = 16;
		var->green.length = 8;
		var->blue.offset = 8;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 8;
		अवरोध;
	पूर्ण
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	var->left_margin = timing.htotal - timing.hsync_end;
	var->right_margin = timing.hsync_start - timing.width;
	var->upper_margin = timing.vtotal - timing.vsync_end;
	var->lower_margin = timing.vsync_start - timing.height;
	var->hsync_len = timing.hsync_end - timing.hsync_start;
	var->vsync_len = timing.vsync_end - timing.vsync_start;

	वापस 0;
पूर्ण

अटल पूर्णांक gbefb_mmap(काष्ठा fb_info *info,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ phys_addr, phys_size;
	u16 *tile;

	/* check range */
	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;
	अगर (size > gbe_mem_size)
		वापस -EINVAL;
	अगर (offset > gbe_mem_size - size)
		वापस -EINVAL;

	/* remap using the fastest ग_लिखो-through mode on architecture */
	/* try not polluting the cache when possible */
#अगर_घोषित CONFIG_MIPS
	pgprot_val(vma->vm_page_prot) =
		pgprot_fb(pgprot_val(vma->vm_page_prot));
#पूर्ण_अगर
	/* VM_IO | VM_DONTEXPAND | VM_DONTDUMP are set by remap_pfn_range() */

	/* look क्रम the starting tile */
	tile = &gbe_tiles.cpu[offset >> TILE_SHIFT];
	addr = vma->vm_start;
	offset &= TILE_MASK;

	/* remap each tile separately */
	करो अणु
		phys_addr = (((अचिन्हित दीर्घ) (*tile)) << TILE_SHIFT) + offset;
		अगर ((offset + size) < TILE_SIZE)
			phys_size = size;
		अन्यथा
			phys_size = TILE_SIZE - offset;

		अगर (remap_pfn_range(vma, addr, phys_addr >> PAGE_SHIFT,
						phys_size, vma->vm_page_prot))
			वापस -EAGAIN;

		offset = 0;
		size -= phys_size;
		addr += phys_size;
		tile++;
	पूर्ण जबतक (size);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops gbefb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= gbefb_check_var,
	.fb_set_par	= gbefb_set_par,
	.fb_setcolreg	= gbefb_setcolreg,
	.fb_mmap	= gbefb_mmap,
	.fb_blank	= gbefb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 * sysfs
 */

अटल sमाप_प्रकार gbefb_show_memsize(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", gbe_mem_size);
पूर्ण

अटल DEVICE_ATTR(size, S_IRUGO, gbefb_show_memsize, शून्य);

अटल sमाप_प्रकार gbefb_show_rev(काष्ठा device *device, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", gbe_revision);
पूर्ण

अटल DEVICE_ATTR(revision, S_IRUGO, gbefb_show_rev, शून्य);

अटल व्योम gbefb_हटाओ_sysfs(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_size);
	device_हटाओ_file(dev, &dev_attr_revision);
पूर्ण

अटल व्योम gbefb_create_sysfs(काष्ठा device *dev)
अणु
	device_create_file(dev, &dev_attr_size);
	device_create_file(dev, &dev_attr_revision);
पूर्ण

/*
 * Initialization
 */

अटल पूर्णांक gbefb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "monitor:", 8)) अणु
			अगर (!म_भेदन(this_opt + 8, "crt", 3)) अणु
				flat_panel_enabled = 0;
				शेष_var = &शेष_var_CRT;
				शेष_mode = &शेष_mode_CRT;
			पूर्ण अन्यथा अगर (!म_भेदन(this_opt + 8, "1600sw", 6) ||
				   !म_भेदन(this_opt + 8, "lcd", 3)) अणु
				flat_panel_enabled = 1;
				शेष_var = &शेष_var_LCD;
				शेष_mode = &शेष_mode_LCD;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "mem:", 4)) अणु
			gbe_mem_size = memparse(this_opt + 4, &this_opt);
			अगर (gbe_mem_size > CONFIG_FB_GBE_MEM * 1024 * 1024)
				gbe_mem_size = CONFIG_FB_GBE_MEM * 1024 * 1024;
			अगर (gbe_mem_size < TILE_SIZE)
				gbe_mem_size = TILE_SIZE;
		पूर्ण अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gbefb_probe(काष्ठा platक्रमm_device *p_dev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा fb_info *info;
	काष्ठा gbefb_par *par;
#अगर_अघोषित MODULE
	अक्षर *options = शून्य;
#पूर्ण_अगर

	info = framebuffer_alloc(माप(काष्ठा gbefb_par), &p_dev->dev);
	अगर (!info)
		वापस -ENOMEM;

#अगर_अघोषित MODULE
	अगर (fb_get_options("gbefb", &options)) अणु
		ret = -ENODEV;
		जाओ out_release_framebuffer;
	पूर्ण
	gbefb_setup(options);
#पूर्ण_अगर

	अगर (!request_mem_region(GBE_BASE, माप(काष्ठा sgi_gbe), "GBE")) अणु
		prपूर्णांकk(KERN_ERR "gbefb: couldn't reserve mmio region\n");
		ret = -EBUSY;
		जाओ out_release_framebuffer;
	पूर्ण

	gbe = (काष्ठा sgi_gbe *) devm_ioremap(&p_dev->dev, GBE_BASE,
					      माप(काष्ठा sgi_gbe));
	अगर (!gbe) अणु
		prपूर्णांकk(KERN_ERR "gbefb: couldn't map mmio region\n");
		ret = -ENXIO;
		जाओ out_release_mem_region;
	पूर्ण
	gbe_revision = gbe->ctrlstat & 15;

	gbe_tiles.cpu = dmam_alloc_coherent(&p_dev->dev,
				GBE_TLB_SIZE * माप(uपूर्णांक16_t),
				&gbe_tiles.dma, GFP_KERNEL);
	अगर (!gbe_tiles.cpu) अणु
		prपूर्णांकk(KERN_ERR "gbefb: couldn't allocate tiles table\n");
		ret = -ENOMEM;
		जाओ out_release_mem_region;
	पूर्ण

	अगर (gbe_mem_phys) अणु
		/* memory was allocated at boot समय */
		gbe_mem = devm_ioremap_wc(&p_dev->dev, gbe_mem_phys,
					  gbe_mem_size);
		अगर (!gbe_mem) अणु
			prपूर्णांकk(KERN_ERR "gbefb: couldn't map framebuffer\n");
			ret = -ENOMEM;
			जाओ out_release_mem_region;
		पूर्ण

		gbe_dma_addr = 0;
	पूर्ण अन्यथा अणु
		/* try to allocate memory with the classical allocator
		 * this has high chance to fail on low memory machines */
		gbe_mem = dmam_alloc_attrs(&p_dev->dev, gbe_mem_size,
				&gbe_dma_addr, GFP_KERNEL,
				DMA_ATTR_WRITE_COMBINE);
		अगर (!gbe_mem) अणु
			prपूर्णांकk(KERN_ERR "gbefb: couldn't allocate framebuffer memory\n");
			ret = -ENOMEM;
			जाओ out_release_mem_region;
		पूर्ण

		gbe_mem_phys = (अचिन्हित दीर्घ) gbe_dma_addr;
	पूर्ण

	par = info->par;
	par->wc_cookie = arch_phys_wc_add(gbe_mem_phys, gbe_mem_size);

	/* map framebuffer memory पूर्णांकo tiles table */
	क्रम (i = 0; i < (gbe_mem_size >> TILE_SHIFT); i++)
		gbe_tiles.cpu[i] = (gbe_mem_phys >> TILE_SHIFT) + i;

	info->fbops = &gbefb_ops;
	info->pseuकरो_palette = pseuकरो_palette;
	info->flags = FBINFO_DEFAULT;
	info->screen_base = gbe_mem;
	fb_alloc_cmap(&info->cmap, 256, 0);

	/* reset GBE */
	gbe_reset();

	/* turn on शेष video mode */
	अगर (fb_find_mode(&par->var, info, mode_option, शून्य, 0,
			 शेष_mode, 8) == 0)
		par->var = *शेष_var;
	info->var = par->var;
	gbefb_check_var(&par->var, info);
	gbefb_encode_fix(&info->fix, &info->var);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "gbefb: couldn't register framebuffer\n");
		ret = -ENXIO;
		जाओ out_gbe_unmap;
	पूर्ण

	platक्रमm_set_drvdata(p_dev, info);
	gbefb_create_sysfs(&p_dev->dev);

	fb_info(info, "%s rev %d @ 0x%08x using %dkB memory\n",
		info->fix.id, gbe_revision, (अचिन्हित)GBE_BASE,
		gbe_mem_size >> 10);

	वापस 0;

out_gbe_unmap:
	arch_phys_wc_del(par->wc_cookie);
out_release_mem_region:
	release_mem_region(GBE_BASE, माप(काष्ठा sgi_gbe));
out_release_framebuffer:
	framebuffer_release(info);

	वापस ret;
पूर्ण

अटल पूर्णांक gbefb_हटाओ(काष्ठा platक्रमm_device* p_dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(p_dev);
	काष्ठा gbefb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	gbe_turn_off();
	arch_phys_wc_del(par->wc_cookie);
	release_mem_region(GBE_BASE, माप(काष्ठा sgi_gbe));
	gbefb_हटाओ_sysfs(&p_dev->dev);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gbefb_driver = अणु
	.probe = gbefb_probe,
	.हटाओ = gbefb_हटाओ,
	.driver	= अणु
		.name = "gbefb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *gbefb_device;

अटल पूर्णांक __init gbefb_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&gbefb_driver);
	अगर (!ret) अणु
		gbefb_device = platक्रमm_device_alloc("gbefb", 0);
		अगर (gbefb_device) अणु
			ret = platक्रमm_device_add(gbefb_device);
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
		पूर्ण
		अगर (ret) अणु
			platक्रमm_device_put(gbefb_device);
			platक्रमm_driver_unरेजिस्टर(&gbefb_driver);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास gbefb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(gbefb_device);
	platक्रमm_driver_unरेजिस्टर(&gbefb_driver);
पूर्ण

module_init(gbefb_init);
module_निकास(gbefb_निकास);

MODULE_LICENSE("GPL");
