<शैली गुरु>
/* linux/drivers/video/s3c2410fb.c
 *	Copyright (c) 2004,2005 Arnaud Patard
 *	Copyright (c) 2004-2008 Ben Dooks
 *
 * S3C2410 LCD Framebuffer Driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Driver based on skeletonfb.c, sa1100fb.c and others.
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <यंत्र/mach/map.h>

#अगर_घोषित CONFIG_PM
#समावेश <linux/pm.h>
#पूर्ण_अगर

#समावेश "s3c2410fb.h"
#समावेश "s3c2410fb-regs-lcd.h"

/* Debugging stuff */
अटल पूर्णांक debug = IS_BUILTIN(CONFIG_FB_S3C2410_DEBUG);

#घोषणा dprपूर्णांकk(msg...) \
करो अणु \
	अगर (debug) \
		pr_debug(msg); \
पूर्ण जबतक (0)

/* useful functions */

अटल पूर्णांक is_s3c2412(काष्ठा s3c2410fb_info *fbi)
अणु
	वापस (fbi->drv_type == DRV_S3C2412);
पूर्ण

/* s3c2410fb_set_lcdaddr
 *
 * initialise lcd controller address poपूर्णांकers
 */
अटल व्योम s3c2410fb_set_lcdaddr(काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ saddr1, saddr2, saddr3;
	काष्ठा s3c2410fb_info *fbi = info->par;
	व्योम __iomem *regs = fbi->io;

	saddr1  = info->fix.smem_start >> 1;
	saddr2  = info->fix.smem_start;
	saddr2 += info->fix.line_length * info->var.yres;
	saddr2 >>= 1;

	saddr3 = S3C2410_OFFSIZE(0) |
		 S3C2410_PAGEWIDTH((info->fix.line_length / 2) & 0x3ff);

	dprपूर्णांकk("LCDSADDR1 = 0x%08lx\n", saddr1);
	dprपूर्णांकk("LCDSADDR2 = 0x%08lx\n", saddr2);
	dprपूर्णांकk("LCDSADDR3 = 0x%08lx\n", saddr3);

	ग_लिखोl(saddr1, regs + S3C2410_LCDSADDR1);
	ग_लिखोl(saddr2, regs + S3C2410_LCDSADDR2);
	ग_लिखोl(saddr3, regs + S3C2410_LCDSADDR3);
पूर्ण

/* s3c2410fb_calc_pixclk()
 *
 * calculate भागisor क्रम clk->pixclk
 */
अटल अचिन्हित पूर्णांक s3c2410fb_calc_pixclk(काष्ठा s3c2410fb_info *fbi,
					  अचिन्हित दीर्घ pixclk)
अणु
	अचिन्हित दीर्घ clk = fbi->clk_rate;
	अचिन्हित दीर्घ दीर्घ भाग;

	/* pixclk is in picoseconds, our घड़ी is in Hz
	 *
	 * Hz -> picoseconds is / 10^-12
	 */

	भाग = (अचिन्हित दीर्घ दीर्घ)clk * pixclk;
	भाग >>= 12;			/* भाग / 2^12 */
	करो_भाग(भाग, 625 * 625UL * 625); /* भाग / 5^12 */

	dprपूर्णांकk("pixclk %ld, divisor is %ld\n", pixclk, (दीर्घ)भाग);
	वापस भाग;
पूर्ण

/*
 *	s3c2410fb_check_var():
 *	Get the video params out of 'var'. If a value doesn't fit, round it up,
 *	अगर it's too big, वापस -EINVAL.
 *
 */
अटल पूर्णांक s3c2410fb_check_var(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	काष्ठा s3c2410fb_mach_info *mach_info = dev_get_platdata(fbi->dev);
	काष्ठा s3c2410fb_display *display = शून्य;
	काष्ठा s3c2410fb_display *शेष_display = mach_info->displays +
						    mach_info->शेष_display;
	पूर्णांक type = शेष_display->type;
	अचिन्हित i;

	dprपूर्णांकk("check_var(var=%p, info=%p)\n", var, info);

	/* validate x/y resolution */
	/* choose शेष mode अगर possible */
	अगर (var->yres == शेष_display->yres &&
	    var->xres == शेष_display->xres &&
	    var->bits_per_pixel == शेष_display->bpp)
		display = शेष_display;
	अन्यथा
		क्रम (i = 0; i < mach_info->num_displays; i++)
			अगर (type == mach_info->displays[i].type &&
			    var->yres == mach_info->displays[i].yres &&
			    var->xres == mach_info->displays[i].xres &&
			    var->bits_per_pixel == mach_info->displays[i].bpp) अणु
				display = mach_info->displays + i;
				अवरोध;
			पूर्ण

	अगर (!display) अणु
		dprपूर्णांकk("wrong resolution or depth %dx%d at %d bpp\n",
			var->xres, var->yres, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	/* it is always the size as the display */
	var->xres_भव = display->xres;
	var->yres_भव = display->yres;
	var->height = display->height;
	var->width = display->width;

	/* copy lcd settings */
	var->pixघड़ी = display->pixघड़ी;
	var->left_margin = display->left_margin;
	var->right_margin = display->right_margin;
	var->upper_margin = display->upper_margin;
	var->lower_margin = display->lower_margin;
	var->vsync_len = display->vsync_len;
	var->hsync_len = display->hsync_len;

	fbi->regs.lcdcon5 = display->lcdcon5;
	/* set display type */
	fbi->regs.lcdcon1 = display->type;

	var->transp.offset = 0;
	var->transp.length = 0;
	/* set r/g/b positions */
	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		var->red.offset	= 0;
		var->red.length	= var->bits_per_pixel;
		var->green	= var->red;
		var->blue	= var->red;
		अवरोध;
	हाल 8:
		अगर (display->type != S3C2410_LCDCON1_TFT) अणु
			/* 8 bpp 332 */
			var->red.length		= 3;
			var->red.offset		= 5;
			var->green.length	= 3;
			var->green.offset	= 2;
			var->blue.length	= 2;
			var->blue.offset	= 0;
		पूर्ण अन्यथा अणु
			var->red.offset		= 0;
			var->red.length		= 8;
			var->green		= var->red;
			var->blue		= var->red;
		पूर्ण
		अवरोध;
	हाल 12:
		/* 12 bpp 444 */
		var->red.length		= 4;
		var->red.offset		= 8;
		var->green.length	= 4;
		var->green.offset	= 4;
		var->blue.length	= 4;
		var->blue.offset	= 0;
		अवरोध;

	शेष:
	हाल 16:
		अगर (display->lcdcon5 & S3C2410_LCDCON5_FRM565) अणु
			/* 16 bpp, 565 क्रमmat */
			var->red.offset		= 11;
			var->green.offset	= 5;
			var->blue.offset	= 0;
			var->red.length		= 5;
			var->green.length	= 6;
			var->blue.length	= 5;
		पूर्ण अन्यथा अणु
			/* 16 bpp, 5551 क्रमmat */
			var->red.offset		= 11;
			var->green.offset	= 6;
			var->blue.offset	= 1;
			var->red.length		= 5;
			var->green.length	= 5;
			var->blue.length	= 5;
		पूर्ण
		अवरोध;
	हाल 32:
		/* 24 bpp 888 and 8 dummy */
		var->red.length		= 8;
		var->red.offset		= 16;
		var->green.length	= 8;
		var->green.offset	= 8;
		var->blue.length	= 8;
		var->blue.offset	= 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* s3c2410fb_calculate_stn_lcd_regs
 *
 * calculate रेजिस्टर values from var settings
 */
अटल व्योम s3c2410fb_calculate_stn_lcd_regs(स्थिर काष्ठा fb_info *info,
					     काष्ठा s3c2410fb_hw *regs)
अणु
	स्थिर काष्ठा s3c2410fb_info *fbi = info->par;
	स्थिर काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक type = regs->lcdcon1 & ~S3C2410_LCDCON1_TFT;
	पूर्णांक hs = var->xres >> 2;
	अचिन्हित wdly = (var->left_margin >> 4) - 1;
	अचिन्हित wlh = (var->hsync_len >> 4) - 1;

	अगर (type != S3C2410_LCDCON1_STN4)
		hs >>= 1;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN1BPP;
		अवरोध;
	हाल 2:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN2GREY;
		अवरोध;
	हाल 4:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN4GREY;
		अवरोध;
	हाल 8:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN8BPP;
		hs *= 3;
		अवरोध;
	हाल 12:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN12BPP;
		hs *= 3;
		अवरोध;

	शेष:
		/* invalid pixel depth */
		dev_err(fbi->dev, "invalid bpp %d\n",
			var->bits_per_pixel);
	पूर्ण
	/* update X/Y info */
	dprपूर्णांकk("setting horz: lft=%d, rt=%d, sync=%d\n",
		var->left_margin, var->right_margin, var->hsync_len);

	regs->lcdcon2 = S3C2410_LCDCON2_LINEVAL(var->yres - 1);

	अगर (wdly > 3)
		wdly = 3;

	अगर (wlh > 3)
		wlh = 3;

	regs->lcdcon3 =	S3C2410_LCDCON3_WDLY(wdly) |
			S3C2410_LCDCON3_LINEBLANK(var->right_margin / 8) |
			S3C2410_LCDCON3_HOZVAL(hs - 1);

	regs->lcdcon4 = S3C2410_LCDCON4_WLH(wlh);
पूर्ण

/* s3c2410fb_calculate_tft_lcd_regs
 *
 * calculate रेजिस्टर values from var settings
 */
अटल व्योम s3c2410fb_calculate_tft_lcd_regs(स्थिर काष्ठा fb_info *info,
					     काष्ठा s3c2410fb_hw *regs)
अणु
	स्थिर काष्ठा s3c2410fb_info *fbi = info->par;
	स्थिर काष्ठा fb_var_screeninfo *var = &info->var;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT1BPP;
		अवरोध;
	हाल 2:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT2BPP;
		अवरोध;
	हाल 4:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT4BPP;
		अवरोध;
	हाल 8:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT8BPP;
		regs->lcdcon5 |= S3C2410_LCDCON5_BSWP |
				 S3C2410_LCDCON5_FRM565;
		regs->lcdcon5 &= ~S3C2410_LCDCON5_HWSWP;
		अवरोध;
	हाल 16:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT16BPP;
		regs->lcdcon5 &= ~S3C2410_LCDCON5_BSWP;
		regs->lcdcon5 |= S3C2410_LCDCON5_HWSWP;
		अवरोध;
	हाल 32:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT24BPP;
		regs->lcdcon5 &= ~(S3C2410_LCDCON5_BSWP |
				   S3C2410_LCDCON5_HWSWP |
				   S3C2410_LCDCON5_BPP24BL);
		अवरोध;
	शेष:
		/* invalid pixel depth */
		dev_err(fbi->dev, "invalid bpp %d\n",
			var->bits_per_pixel);
	पूर्ण
	/* update X/Y info */
	dprपूर्णांकk("setting vert: up=%d, low=%d, sync=%d\n",
		var->upper_margin, var->lower_margin, var->vsync_len);

	dprपूर्णांकk("setting horz: lft=%d, rt=%d, sync=%d\n",
		var->left_margin, var->right_margin, var->hsync_len);

	regs->lcdcon2 = S3C2410_LCDCON2_LINEVAL(var->yres - 1) |
			S3C2410_LCDCON2_VBPD(var->upper_margin - 1) |
			S3C2410_LCDCON2_VFPD(var->lower_margin - 1) |
			S3C2410_LCDCON2_VSPW(var->vsync_len - 1);

	regs->lcdcon3 = S3C2410_LCDCON3_HBPD(var->right_margin - 1) |
			S3C2410_LCDCON3_HFPD(var->left_margin - 1) |
			S3C2410_LCDCON3_HOZVAL(var->xres - 1);

	regs->lcdcon4 = S3C2410_LCDCON4_HSPW(var->hsync_len - 1);
पूर्ण

/* s3c2410fb_activate_var
 *
 * activate (set) the controller from the given framebuffer
 * inक्रमmation
 */
अटल व्योम s3c2410fb_activate_var(काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	व्योम __iomem *regs = fbi->io;
	पूर्णांक type = fbi->regs.lcdcon1 & S3C2410_LCDCON1_TFT;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक clkभाग;

	clkभाग = DIV_ROUND_UP(s3c2410fb_calc_pixclk(fbi, var->pixघड़ी), 2);

	dprपूर्णांकk("%s: var->xres  = %d\n", __func__, var->xres);
	dprपूर्णांकk("%s: var->yres  = %d\n", __func__, var->yres);
	dprपूर्णांकk("%s: var->bpp   = %d\n", __func__, var->bits_per_pixel);

	अगर (type == S3C2410_LCDCON1_TFT) अणु
		s3c2410fb_calculate_tft_lcd_regs(info, &fbi->regs);
		--clkभाग;
		अगर (clkभाग < 0)
			clkभाग = 0;
	पूर्ण अन्यथा अणु
		s3c2410fb_calculate_stn_lcd_regs(info, &fbi->regs);
		अगर (clkभाग < 2)
			clkभाग = 2;
	पूर्ण

	fbi->regs.lcdcon1 |=  S3C2410_LCDCON1_CLKVAL(clkभाग);

	/* ग_लिखो new रेजिस्टरs */

	dprपूर्णांकk("new register set:\n");
	dprपूर्णांकk("lcdcon[1] = 0x%08lx\n", fbi->regs.lcdcon1);
	dprपूर्णांकk("lcdcon[2] = 0x%08lx\n", fbi->regs.lcdcon2);
	dprपूर्णांकk("lcdcon[3] = 0x%08lx\n", fbi->regs.lcdcon3);
	dprपूर्णांकk("lcdcon[4] = 0x%08lx\n", fbi->regs.lcdcon4);
	dprपूर्णांकk("lcdcon[5] = 0x%08lx\n", fbi->regs.lcdcon5);

	ग_लिखोl(fbi->regs.lcdcon1 & ~S3C2410_LCDCON1_ENVID,
		regs + S3C2410_LCDCON1);
	ग_लिखोl(fbi->regs.lcdcon2, regs + S3C2410_LCDCON2);
	ग_लिखोl(fbi->regs.lcdcon3, regs + S3C2410_LCDCON3);
	ग_लिखोl(fbi->regs.lcdcon4, regs + S3C2410_LCDCON4);
	ग_लिखोl(fbi->regs.lcdcon5, regs + S3C2410_LCDCON5);

	/* set lcd address poपूर्णांकers */
	s3c2410fb_set_lcdaddr(info);

	fbi->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID,
	ग_लिखोl(fbi->regs.lcdcon1, regs + S3C2410_LCDCON1);
पूर्ण

/*
 *      s3c2410fb_set_par - Alters the hardware state.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 */
अटल पूर्णांक s3c2410fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;

	चयन (var->bits_per_pixel) अणु
	हाल 32:
	हाल 16:
	हाल 12:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	हाल 1:
		info->fix.visual = FB_VISUAL_MONO01;
		अवरोध;
	शेष:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	पूर्ण

	info->fix.line_length = (var->xres_भव * var->bits_per_pixel) / 8;

	/* activate this new configuration */

	s3c2410fb_activate_var(info);
	वापस 0;
पूर्ण

अटल व्योम schedule_palette_update(काष्ठा s3c2410fb_info *fbi,
				    अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ irqen;
	व्योम __iomem *irq_base = fbi->irq_base;

	local_irq_save(flags);

	fbi->palette_buffer[regno] = val;

	अगर (!fbi->palette_पढ़ोy) अणु
		fbi->palette_पढ़ोy = 1;

		/* enable IRQ */
		irqen = पढ़ोl(irq_base + S3C24XX_LCDINTMSK);
		irqen &= ~S3C2410_LCDINT_FRSYNC;
		ग_लिखोl(irqen, irq_base + S3C24XX_LCDINTMSK);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/* from pxafb.c */
अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan,
					 काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक s3c2410fb_setcolreg(अचिन्हित regno,
			       अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			       अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	व्योम __iomem *regs = fbi->io;
	अचिन्हित पूर्णांक val;

	/* dprपूर्णांकk("setcol: regno=%d, rgb=%d,%d,%d\n",
		   regno, red, green, blue); */

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/* true-colour, use pseuकरो-palette */

		अगर (regno < 16) अणु
			u32 *pal = info->pseuकरो_palette;

			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);

			pal[regno] = val;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno < 256) अणु
			/* currently assume RGB 5-6-5 mode */

			val  = (red   >>  0) & 0xf800;
			val |= (green >>  5) & 0x07e0;
			val |= (blue  >> 11) & 0x001f;

			ग_लिखोl(val, regs + S3C2410_TFTPAL(regno));
			schedule_palette_update(fbi, regno, val);
		पूर्ण

		अवरोध;

	शेष:
		वापस 1;	/* unknown type */
	पूर्ण

	वापस 0;
पूर्ण

/* s3c2410fb_lcd_enable
 *
 * shutकरोwn the lcd controller
 */
अटल व्योम s3c2410fb_lcd_enable(काष्ठा s3c2410fb_info *fbi, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर (enable)
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID;
	अन्यथा
		fbi->regs.lcdcon1 &= ~S3C2410_LCDCON1_ENVID;

	ग_लिखोl(fbi->regs.lcdcon1, fbi->io + S3C2410_LCDCON1);

	local_irq_restore(flags);
पूर्ण


/*
 *      s3c2410fb_blank
 *	@blank_mode: the blank mode we want.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Blank the screen अगर blank_mode != 0, अन्यथा unblank. Return 0 अगर
 *	blanking succeeded, != 0 अगर un-/blanking failed due to e.g. a
 *	video mode which करोesn't support it. Implements VESA suspend
 *	and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 *
 */
अटल पूर्णांक s3c2410fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	व्योम __iomem *tpal_reg = fbi->io;

	dprपूर्णांकk("blank(mode=%d, info=%p)\n", blank_mode, info);

	tpal_reg += is_s3c2412(fbi) ? S3C2412_TPAL : S3C2410_TPAL;

	अगर (blank_mode == FB_BLANK_POWERDOWN)
		s3c2410fb_lcd_enable(fbi, 0);
	अन्यथा
		s3c2410fb_lcd_enable(fbi, 1);

	अगर (blank_mode == FB_BLANK_UNBLANK)
		ग_लिखोl(0x0, tpal_reg);
	अन्यथा अणु
		dprपूर्णांकk("setting TPAL to output 0x000000\n");
		ग_लिखोl(S3C2410_TPAL_EN, tpal_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410fb_debug_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", debug ? "on" : "off");
पूर्ण

अटल पूर्णांक s3c2410fb_debug_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (len < 1)
		वापस -EINVAL;

	अगर (strnहालcmp(buf, "on", 2) == 0 ||
	    strnहालcmp(buf, "1", 1) == 0) अणु
		debug = 1;
		dev_dbg(dev, "s3c2410fb: Debug On");
	पूर्ण अन्यथा अगर (strnहालcmp(buf, "off", 3) == 0 ||
		   strnहालcmp(buf, "0", 1) == 0) अणु
		debug = 0;
		dev_dbg(dev, "s3c2410fb: Debug Off");
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(debug, 0664, s3c2410fb_debug_show, s3c2410fb_debug_store);

अटल स्थिर काष्ठा fb_ops s3c2410fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= s3c2410fb_check_var,
	.fb_set_par	= s3c2410fb_set_par,
	.fb_blank	= s3c2410fb_blank,
	.fb_setcolreg	= s3c2410fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 * s3c2410fb_map_video_memory():
 *	Allocates the DRAM memory क्रम the frame buffer.  This buffer is
 *	remapped पूर्णांकo a non-cached, non-buffered, memory region to
 *	allow palette and pixel ग_लिखोs to occur without flushing the
 *	cache.  Once this area is remapped, all भव memory
 *	access to the video memory should occur at the new region.
 */
अटल पूर्णांक s3c2410fb_map_video_memory(काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	dma_addr_t map_dma;
	अचिन्हित map_size = PAGE_ALIGN(info->fix.smem_len);

	dprपूर्णांकk("map_video_memory(fbi=%p) map_size %u\n", fbi, map_size);

	info->screen_base = dma_alloc_wc(fbi->dev, map_size, &map_dma,
					 GFP_KERNEL);

	अगर (info->screen_base) अणु
		/* prevent initial garbage on screen */
		dprपूर्णांकk("map_video_memory: clear %p:%08x\n",
			info->screen_base, map_size);
		स_रखो(info->screen_base, 0x00, map_size);

		info->fix.smem_start = map_dma;

		dprपूर्णांकk("map_video_memory: dma=%08lx cpu=%p size=%08x\n",
			info->fix.smem_start, info->screen_base, map_size);
	पूर्ण

	वापस info->screen_base ? 0 : -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम s3c2410fb_unmap_video_memory(काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;

	dma_मुक्त_wc(fbi->dev, PAGE_ALIGN(info->fix.smem_len),
		    info->screen_base, info->fix.smem_start);
पूर्ण

अटल अंतरभूत व्योम modअगरy_gpio(व्योम __iomem *reg,
			       अचिन्हित दीर्घ set, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (!reg)
		वापस;

	पंचांगp = पढ़ोl(reg) & ~mask;
	ग_लिखोl(पंचांगp | set, reg);
पूर्ण

/*
 * s3c2410fb_init_रेजिस्टरs - Initialise all LCD-related रेजिस्टरs
 */
अटल पूर्णांक s3c2410fb_init_रेजिस्टरs(काष्ठा fb_info *info)
अणु
	काष्ठा s3c2410fb_info *fbi = info->par;
	काष्ठा s3c2410fb_mach_info *mach_info = dev_get_platdata(fbi->dev);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *regs = fbi->io;
	व्योम __iomem *tpal;
	व्योम __iomem *lpcsel;

	अगर (is_s3c2412(fbi)) अणु
		tpal = regs + S3C2412_TPAL;
		lpcsel = regs + S3C2412_TCONSEL;
	पूर्ण अन्यथा अणु
		tpal = regs + S3C2410_TPAL;
		lpcsel = regs + S3C2410_LPCSEL;
	पूर्ण

	/* Initialise LCD with values from haret */

	local_irq_save(flags);

	/* modअगरy the gpio(s) with पूर्णांकerrupts set (bjd) */

	modअगरy_gpio(mach_info->gpcup_reg,  mach_info->gpcup,  mach_info->gpcup_mask);
	modअगरy_gpio(mach_info->gpccon_reg, mach_info->gpccon, mach_info->gpccon_mask);
	modअगरy_gpio(mach_info->gpdup_reg,  mach_info->gpdup,  mach_info->gpdup_mask);
	modअगरy_gpio(mach_info->gpdcon_reg, mach_info->gpdcon, mach_info->gpdcon_mask);

	local_irq_restore(flags);

	dprपूर्णांकk("LPCSEL    = 0x%08lx\n", mach_info->lpcsel);
	ग_लिखोl(mach_info->lpcsel, lpcsel);

	dprपूर्णांकk("replacing TPAL %08x\n", पढ़ोl(tpal));

	/* ensure temporary palette disabled */
	ग_लिखोl(0x00, tpal);

	वापस 0;
पूर्ण

अटल व्योम s3c2410fb_ग_लिखो_palette(काष्ठा s3c2410fb_info *fbi)
अणु
	अचिन्हित पूर्णांक i;
	व्योम __iomem *regs = fbi->io;

	fbi->palette_पढ़ोy = 0;

	क्रम (i = 0; i < 256; i++) अणु
		अचिन्हित दीर्घ ent = fbi->palette_buffer[i];
		अगर (ent == PALETTE_BUFF_CLEAR)
			जारी;

		ग_लिखोl(ent, regs + S3C2410_TFTPAL(i));

		/* it seems the only way to know exactly
		 * अगर the palette wrote ok, is to check
		 * to see अगर the value verअगरies ok
		 */

		अगर (पढ़ोw(regs + S3C2410_TFTPAL(i)) == ent)
			fbi->palette_buffer[i] = PALETTE_BUFF_CLEAR;
		अन्यथा
			fbi->palette_पढ़ोy = 1;   /* retry */
	पूर्ण
पूर्ण

अटल irqवापस_t s3c2410fb_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s3c2410fb_info *fbi = dev_id;
	व्योम __iomem *irq_base = fbi->irq_base;
	अचिन्हित दीर्घ lcdirq = पढ़ोl(irq_base + S3C24XX_LCDINTPND);

	अगर (lcdirq & S3C2410_LCDINT_FRSYNC) अणु
		अगर (fbi->palette_पढ़ोy)
			s3c2410fb_ग_लिखो_palette(fbi);

		ग_लिखोl(S3C2410_LCDINT_FRSYNC, irq_base + S3C24XX_LCDINTPND);
		ग_लिखोl(S3C2410_LCDINT_FRSYNC, irq_base + S3C24XX_LCDSRCPND);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ

अटल पूर्णांक s3c2410fb_cpufreq_transition(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा s3c2410fb_info *info;
	काष्ठा fb_info *fbinfo;
	दीर्घ delta_f;

	info = container_of(nb, काष्ठा s3c2410fb_info, freq_transition);
	fbinfo = dev_get_drvdata(info->dev);

	/* work out change, <0 क्रम speed-up */
	delta_f = info->clk_rate - clk_get_rate(info->clk);

	अगर ((val == CPUFREQ_POSTCHANGE && delta_f > 0) ||
	    (val == CPUFREQ_PRECHANGE && delta_f < 0)) अणु
		info->clk_rate = clk_get_rate(info->clk);
		s3c2410fb_activate_var(fbinfo);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410fb_cpufreq_रेजिस्टर(काष्ठा s3c2410fb_info *info)
अणु
	info->freq_transition.notअगरier_call = s3c2410fb_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&info->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम s3c2410fb_cpufreq_deरेजिस्टर(काष्ठा s3c2410fb_info *info)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&info->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक s3c2410fb_cpufreq_रेजिस्टर(काष्ठा s3c2410fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s3c2410fb_cpufreq_deरेजिस्टर(काष्ठा s3c2410fb_info *info)
अणु
पूर्ण
#पूर्ण_अगर


अटल स्थिर अक्षर driver_name[] = "s3c2410fb";

अटल पूर्णांक s3c24xxfb_probe(काष्ठा platक्रमm_device *pdev,
			   क्रमागत s3c_drv_type drv_type)
अणु
	काष्ठा s3c2410fb_info *info;
	काष्ठा s3c2410fb_display *display;
	काष्ठा fb_info *fbinfo;
	काष्ठा s3c2410fb_mach_info *mach_info;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i;
	पूर्णांक size;
	u32 lcdcon1;

	mach_info = dev_get_platdata(&pdev->dev);
	अगर (mach_info == शून्य) अणु
		dev_err(&pdev->dev,
			"no platform data for lcd, cannot attach\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mach_info->शेष_display >= mach_info->num_displays) अणु
		dev_err(&pdev->dev, "default is %d but only %d displays\n",
			mach_info->शेष_display, mach_info->num_displays);
		वापस -EINVAL;
	पूर्ण

	display = mach_info->displays + mach_info->शेष_display;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "no irq for device\n");
		वापस -ENOENT;
	पूर्ण

	fbinfo = framebuffer_alloc(माप(काष्ठा s3c2410fb_info), &pdev->dev);
	अगर (!fbinfo)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, fbinfo);

	info = fbinfo->par;
	info->dev = &pdev->dev;
	info->drv_type = drv_type;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to get memory registers\n");
		ret = -ENXIO;
		जाओ dealloc_fb;
	पूर्ण

	size = resource_size(res);
	info->mem = request_mem_region(res->start, size, pdev->name);
	अगर (info->mem == शून्य) अणु
		dev_err(&pdev->dev, "failed to get memory region\n");
		ret = -ENOENT;
		जाओ dealloc_fb;
	पूर्ण

	info->io = ioremap(res->start, size);
	अगर (info->io == शून्य) अणु
		dev_err(&pdev->dev, "ioremap() of registers failed\n");
		ret = -ENXIO;
		जाओ release_mem;
	पूर्ण

	अगर (drv_type == DRV_S3C2412)
		info->irq_base = info->io + S3C2412_LCDINTBASE;
	अन्यथा
		info->irq_base = info->io + S3C2410_LCDINTBASE;

	dprपूर्णांकk("devinit\n");

	म_नकल(fbinfo->fix.id, driver_name);

	/* Stop the video */
	lcdcon1 = पढ़ोl(info->io + S3C2410_LCDCON1);
	ग_लिखोl(lcdcon1 & ~S3C2410_LCDCON1_ENVID, info->io + S3C2410_LCDCON1);

	fbinfo->fix.type	    = FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.type_aux	    = 0;
	fbinfo->fix.xpanstep	    = 0;
	fbinfo->fix.ypanstep	    = 0;
	fbinfo->fix.ywrapstep	    = 0;
	fbinfo->fix.accel	    = FB_ACCEL_NONE;

	fbinfo->var.nonstd	    = 0;
	fbinfo->var.activate	    = FB_ACTIVATE_NOW;
	fbinfo->var.accel_flags     = 0;
	fbinfo->var.vmode	    = FB_VMODE_NONINTERLACED;

	fbinfo->fbops		    = &s3c2410fb_ops;
	fbinfo->flags		    = FBINFO_FLAG_DEFAULT;
	fbinfo->pseuकरो_palette      = &info->pseuकरो_pal;

	क्रम (i = 0; i < 256; i++)
		info->palette_buffer[i] = PALETTE_BUFF_CLEAR;

	ret = request_irq(irq, s3c2410fb_irq, 0, pdev->name, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot get irq %d - err %d\n", irq, ret);
		ret = -EBUSY;
		जाओ release_regs;
	पूर्ण

	info->clk = clk_get(शून्य, "lcd");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed to get lcd clock source\n");
		ret = PTR_ERR(info->clk);
		जाओ release_irq;
	पूर्ण

	clk_prepare_enable(info->clk);
	dprपूर्णांकk("got and enabled clock\n");

	usleep_range(1000, 1100);

	info->clk_rate = clk_get_rate(info->clk);

	/* find maximum required memory size क्रम display */
	क्रम (i = 0; i < mach_info->num_displays; i++) अणु
		अचिन्हित दीर्घ smem_len = mach_info->displays[i].xres;

		smem_len *= mach_info->displays[i].yres;
		smem_len *= mach_info->displays[i].bpp;
		smem_len >>= 3;
		अगर (fbinfo->fix.smem_len < smem_len)
			fbinfo->fix.smem_len = smem_len;
	पूर्ण

	/* Initialize video memory */
	ret = s3c2410fb_map_video_memory(fbinfo);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to allocate video RAM: %d\n", ret);
		ret = -ENOMEM;
		जाओ release_घड़ी;
	पूर्ण

	dprपूर्णांकk("got video memory\n");

	fbinfo->var.xres = display->xres;
	fbinfo->var.yres = display->yres;
	fbinfo->var.bits_per_pixel = display->bpp;

	s3c2410fb_init_रेजिस्टरs(fbinfo);

	s3c2410fb_check_var(&fbinfo->var, fbinfo);

	ret = s3c2410fb_cpufreq_रेजिस्टर(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register cpufreq\n");
		जाओ मुक्त_video_memory;
	पूर्ण

	ret = रेजिस्टर_framebuffer(fbinfo);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register framebuffer device: %d\n",
			ret);
		जाओ मुक्त_cpufreq;
	पूर्ण

	/* create device files */
	ret = device_create_file(&pdev->dev, &dev_attr_debug);
	अगर (ret)
		dev_err(&pdev->dev, "failed to add debug attribute\n");

	dev_info(&pdev->dev, "fb%d: %s frame buffer device\n",
		fbinfo->node, fbinfo->fix.id);

	वापस 0;

 मुक्त_cpufreq:
	s3c2410fb_cpufreq_deरेजिस्टर(info);
मुक्त_video_memory:
	s3c2410fb_unmap_video_memory(fbinfo);
release_घड़ी:
	clk_disable_unprepare(info->clk);
	clk_put(info->clk);
release_irq:
	मुक्त_irq(irq, info);
release_regs:
	iounmap(info->io);
release_mem:
	release_mem_region(res->start, size);
dealloc_fb:
	framebuffer_release(fbinfo);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c2410fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस s3c24xxfb_probe(pdev, DRV_S3C2410);
पूर्ण

अटल पूर्णांक s3c2412fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस s3c24xxfb_probe(pdev, DRV_S3C2412);
पूर्ण


/*
 *  Cleanup
 */
अटल पूर्णांक s3c2410fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *fbinfo = platक्रमm_get_drvdata(pdev);
	काष्ठा s3c2410fb_info *info = fbinfo->par;
	पूर्णांक irq;

	unरेजिस्टर_framebuffer(fbinfo);
	s3c2410fb_cpufreq_deरेजिस्टर(info);

	s3c2410fb_lcd_enable(info, 0);
	usleep_range(1000, 1100);

	s3c2410fb_unmap_video_memory(fbinfo);

	अगर (info->clk) अणु
		clk_disable_unprepare(info->clk);
		clk_put(info->clk);
		info->clk = शून्य;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	मुक्त_irq(irq, info);

	iounmap(info->io);

	release_mem_region(info->mem->start, resource_size(info->mem));

	framebuffer_release(fbinfo);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

/* suspend and resume support क्रम the lcd controller */
अटल पूर्णांक s3c2410fb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा fb_info	   *fbinfo = platक्रमm_get_drvdata(dev);
	काष्ठा s3c2410fb_info *info = fbinfo->par;

	s3c2410fb_lcd_enable(info, 0);

	/* sleep beक्रमe disabling the घड़ी, we need to ensure
	 * the LCD DMA engine is not going to get back on the bus
	 * beक्रमe the घड़ी goes off again (bjd) */

	usleep_range(1000, 1100);
	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410fb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info	   *fbinfo = platक्रमm_get_drvdata(dev);
	काष्ठा s3c2410fb_info *info = fbinfo->par;

	clk_prepare_enable(info->clk);
	usleep_range(1000, 1100);

	s3c2410fb_init_रेजिस्टरs(fbinfo);

	/* re-activate our display after resume */
	s3c2410fb_activate_var(fbinfo);
	s3c2410fb_blank(FB_BLANK_UNBLANK, fbinfo);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा s3c2410fb_suspend शून्य
#घोषणा s3c2410fb_resume  शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver s3c2410fb_driver = अणु
	.probe		= s3c2410fb_probe,
	.हटाओ		= s3c2410fb_हटाओ,
	.suspend	= s3c2410fb_suspend,
	.resume		= s3c2410fb_resume,
	.driver		= अणु
		.name	= "s3c2410-lcd",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver s3c2412fb_driver = अणु
	.probe		= s3c2412fb_probe,
	.हटाओ		= s3c2410fb_हटाओ,
	.suspend	= s3c2410fb_suspend,
	.resume		= s3c2410fb_resume,
	.driver		= अणु
		.name	= "s3c2412-lcd",
	पूर्ण,
पूर्ण;

पूर्णांक __init s3c2410fb_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&s3c2410fb_driver);

	अगर (ret == 0)
		ret = platक्रमm_driver_रेजिस्टर(&s3c2412fb_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास s3c2410fb_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&s3c2410fb_driver);
	platक्रमm_driver_unरेजिस्टर(&s3c2412fb_driver);
पूर्ण

module_init(s3c2410fb_init);
module_निकास(s3c2410fb_cleanup);

MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>");
MODULE_AUTHOR("Ben Dooks <ben-linux@fluff.org>");
MODULE_DESCRIPTION("Framebuffer driver for the s3c2410");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c2410-lcd");
MODULE_ALIAS("platform:s3c2412-lcd");
