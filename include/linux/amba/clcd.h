<शैली गुरु>
/*
 * linux/include/यंत्र-arm/hardware/amba_clcd.h -- Integrator LCD panel.
 *
 * David A Rusling
 *
 * Copyright (C) 2001 ARM Limited
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/fb.h>
#समावेश <linux/amba/clcd-regs.h>

क्रमागत अणु
	/* inभागidual क्रमmats */
	CLCD_CAP_RGB444		= (1 << 0),
	CLCD_CAP_RGB5551	= (1 << 1),
	CLCD_CAP_RGB565		= (1 << 2),
	CLCD_CAP_RGB888		= (1 << 3),
	CLCD_CAP_BGR444		= (1 << 4),
	CLCD_CAP_BGR5551	= (1 << 5),
	CLCD_CAP_BGR565		= (1 << 6),
	CLCD_CAP_BGR888		= (1 << 7),

	/* connection layouts */
	CLCD_CAP_444		= CLCD_CAP_RGB444 | CLCD_CAP_BGR444,
	CLCD_CAP_5551		= CLCD_CAP_RGB5551 | CLCD_CAP_BGR5551,
	CLCD_CAP_565		= CLCD_CAP_RGB565 | CLCD_CAP_BGR565,
	CLCD_CAP_888		= CLCD_CAP_RGB888 | CLCD_CAP_BGR888,

	/* red/blue ordering */
	CLCD_CAP_RGB		= CLCD_CAP_RGB444 | CLCD_CAP_RGB5551 |
				  CLCD_CAP_RGB565 | CLCD_CAP_RGB888,
	CLCD_CAP_BGR		= CLCD_CAP_BGR444 | CLCD_CAP_BGR5551 |
				  CLCD_CAP_BGR565 | CLCD_CAP_BGR888,

	CLCD_CAP_ALL		= CLCD_CAP_BGR | CLCD_CAP_RGB,
पूर्ण;

काष्ठा backlight_device;

काष्ठा clcd_panel अणु
	काष्ठा fb_videomode	mode;
	चिन्हित लघु		width;	/* width in mm */
	चिन्हित लघु		height;	/* height in mm */
	u32			tim2;
	u32			tim3;
	u32			cntl;
	u32			caps;
	अचिन्हित पूर्णांक		bpp:8,
				fixedtimings:1,
				grayscale:1;
	अचिन्हित पूर्णांक		connector;
	काष्ठा backlight_device	*backlight;
	/*
	 * If the B/R lines are चयनed between the CLCD
	 * and the panel we need to know this and not try to
	 * compensate with the BGR bit in the control रेजिस्टर.
	 */
	bool			bgr_connection;
पूर्ण;

काष्ठा clcd_regs अणु
	u32			tim0;
	u32			tim1;
	u32			tim2;
	u32			tim3;
	u32			cntl;
	अचिन्हित दीर्घ		pixघड़ी;
पूर्ण;

काष्ठा clcd_fb;

/*
 * the board-type specअगरic routines
 */
काष्ठा clcd_board अणु
	स्थिर अक्षर *name;

	/*
	 * Optional.  Hardware capability flags.
	 */
	u32	caps;

	/*
	 * Optional.  Check whether the var काष्ठाure is acceptable
	 * क्रम this display.
	 */
	पूर्णांक	(*check)(काष्ठा clcd_fb *fb, काष्ठा fb_var_screeninfo *var);

	/*
	 * Compulsory.  Decode fb->fb.var पूर्णांकo regs->*.  In the हाल of
	 * fixed timing, set regs->* to the रेजिस्टर values required.
	 */
	व्योम	(*decode)(काष्ठा clcd_fb *fb, काष्ठा clcd_regs *regs);

	/*
	 * Optional.  Disable any extra display hardware.
	 */
	व्योम	(*disable)(काष्ठा clcd_fb *);

	/*
	 * Optional.  Enable any extra display hardware.
	 */
	व्योम	(*enable)(काष्ठा clcd_fb *);

	/*
	 * Setup platक्रमm specअगरic parts of CLCD driver
	 */
	पूर्णांक	(*setup)(काष्ठा clcd_fb *);

	/*
	 * mmap the framebuffer memory
	 */
	पूर्णांक	(*mmap)(काष्ठा clcd_fb *, काष्ठा vm_area_काष्ठा *);

	/*
	 * Remove platक्रमm specअगरic parts of CLCD driver
	 */
	व्योम	(*हटाओ)(काष्ठा clcd_fb *);
पूर्ण;

काष्ठा amba_device;
काष्ठा clk;

/* this data काष्ठाure describes each frame buffer device we find */
काष्ठा clcd_fb अणु
	काष्ठा fb_info		fb;
	काष्ठा amba_device	*dev;
	काष्ठा clk		*clk;
	काष्ठा clcd_panel	*panel;
	काष्ठा clcd_board	*board;
	व्योम			*board_data;
	व्योम __iomem		*regs;
	u16			off_ienb;
	u16			off_cntl;
	u32			clcd_cntl;
	u32			cmap[16];
	bool			clk_enabled;
पूर्ण;

अटल अंतरभूत व्योम clcdfb_decode(काष्ठा clcd_fb *fb, काष्ठा clcd_regs *regs)
अणु
	काष्ठा fb_var_screeninfo *var = &fb->fb.var;
	u32 val, cpl;

	/*
	 * Program the CLCD controller रेजिस्टरs and start the CLCD
	 */
	val = ((var->xres / 16) - 1) << 2;
	val |= (var->hsync_len - 1) << 8;
	val |= (var->right_margin - 1) << 16;
	val |= (var->left_margin - 1) << 24;
	regs->tim0 = val;

	val = var->yres;
	अगर (fb->panel->cntl & CNTL_LCDDUAL)
		val /= 2;
	val -= 1;
	val |= (var->vsync_len - 1) << 10;
	val |= var->lower_margin << 16;
	val |= var->upper_margin << 24;
	regs->tim1 = val;

	val = fb->panel->tim2;
	val |= var->sync & FB_SYNC_HOR_HIGH_ACT  ? 0 : TIM2_IHS;
	val |= var->sync & FB_SYNC_VERT_HIGH_ACT ? 0 : TIM2_IVS;

	cpl = var->xres_भव;
	अगर (fb->panel->cntl & CNTL_LCDTFT)	  /* TFT */
		/* / 1 */;
	अन्यथा अगर (!var->grayscale)		  /* STN color */
		cpl = cpl * 8 / 3;
	अन्यथा अगर (fb->panel->cntl & CNTL_LCDMONO8) /* STN monochrome, 8bit */
		cpl /= 8;
	अन्यथा					  /* STN monochrome, 4bit */
		cpl /= 4;

	regs->tim2 = val | ((cpl - 1) << 16);

	regs->tim3 = fb->panel->tim3;

	val = fb->panel->cntl;
	अगर (var->grayscale)
		val |= CNTL_LCDBW;

	अगर (fb->panel->caps && fb->board->caps && var->bits_per_pixel >= 16) अणु
		/*
		 * अगर board and panel supply capabilities, we can support
		 * changing BGR/RGB depending on supplied parameters. Here
		 * we चयन to what the framebuffer is providing अगर need
		 * be, so अगर the framebuffer is BGR but the display connection
		 * is RGB (first हाल) we चयन it around. Vice versa mutatis
		 * mutandis अगर the framebuffer is RGB but the display connection
		 * is BGR, we flip it around.
		 */
		अगर (var->red.offset == 0)
			val &= ~CNTL_BGR;
		अन्यथा
			val |= CNTL_BGR;
		अगर (fb->panel->bgr_connection)
			val ^= CNTL_BGR;
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		val |= CNTL_LCDBPP1;
		अवरोध;
	हाल 2:
		val |= CNTL_LCDBPP2;
		अवरोध;
	हाल 4:
		val |= CNTL_LCDBPP4;
		अवरोध;
	हाल 8:
		val |= CNTL_LCDBPP8;
		अवरोध;
	हाल 16:
		/*
		 * PL110 cannot choose between 5551 and 565 modes in its
		 * control रेजिस्टर.  It is possible to use 565 with
		 * custom बाह्यal wiring.
		 */
		अगर (amba_part(fb->dev) == 0x110 ||
		    var->green.length == 5)
			val |= CNTL_LCDBPP16;
		अन्यथा अगर (var->green.length == 6)
			val |= CNTL_LCDBPP16_565;
		अन्यथा
			val |= CNTL_LCDBPP16_444;
		अवरोध;
	हाल 32:
		val |= CNTL_LCDBPP24;
		अवरोध;
	पूर्ण

	regs->cntl = val;
	regs->pixघड़ी = var->pixघड़ी;
पूर्ण

अटल अंतरभूत पूर्णांक clcdfb_check(काष्ठा clcd_fb *fb, काष्ठा fb_var_screeninfo *var)
अणु
	var->xres_भव = var->xres = (var->xres + 15) & ~15;
	var->yres_भव = var->yres = (var->yres + 1) & ~1;

#घोषणा CHECK(e,l,h) (var->e < l || var->e > h)
	अगर (CHECK(right_margin, (5+1), 256) ||	/* back porch */
	    CHECK(left_margin, (5+1), 256) ||	/* front porch */
	    CHECK(hsync_len, (5+1), 256) ||
	    var->xres > 4096 ||
	    var->lower_margin > 255 ||		/* back porch */
	    var->upper_margin > 255 ||		/* front porch */
	    var->vsync_len > 32 ||
	    var->yres > 1024)
		वापस -EINVAL;
#अघोषित CHECK

	/* single panel mode: PCD = max(PCD, 1) */
	/* dual panel mode: PCD = max(PCD, 5) */

	/*
	 * You can't change the grayscale setting, and
	 * we can only करो non-पूर्णांकerlaced video.
	 */
	अगर (var->grayscale != fb->fb.var.grayscale ||
	    (var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

#घोषणा CHECK(e) (var->e != fb->fb.var.e)
	अगर (fb->panel->fixedtimings &&
	    (CHECK(xres)		||
	     CHECK(yres)		||
	     CHECK(bits_per_pixel)	||
	     CHECK(pixघड़ी)		||
	     CHECK(left_margin)		||
	     CHECK(right_margin)	||
	     CHECK(upper_margin)	||
	     CHECK(lower_margin)	||
	     CHECK(hsync_len)		||
	     CHECK(vsync_len)		||
	     CHECK(sync)))
		वापस -EINVAL;
#अघोषित CHECK

	var->nonstd = 0;
	var->accel_flags = 0;

	वापस 0;
पूर्ण
