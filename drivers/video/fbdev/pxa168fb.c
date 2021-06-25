<शैली गुरु>
/*
 * linux/drivers/video/pxa168fb.c -- Marvell PXA168 LCD Controller
 *
 *  Copyright (C) 2008 Marvell International Ltd.
 *  All rights reserved.
 *
 *  2009-02-16  adapted from original version क्रम PXA168/910
 *              Jun Nie <njun@marvell.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/uaccess.h>
#समावेश <video/pxa168fb.h>

#समावेश "pxa168fb.h"

#घोषणा DEFAULT_REFRESH		60	/* Hz */

अटल पूर्णांक determine_best_pix_fmt(काष्ठा fb_var_screeninfo *var)
अणु
	/*
	 * Pseuकरोcolor mode?
	 */
	अगर (var->bits_per_pixel == 8)
		वापस PIX_FMT_PSEUDOCOLOR;

	/*
	 * Check क्रम 565/1555.
	 */
	अगर (var->bits_per_pixel == 16 && var->red.length <= 5 &&
	    var->green.length <= 6 && var->blue.length <= 5) अणु
		अगर (var->transp.length == 0) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIX_FMT_RGB565;
			अन्यथा
				वापस PIX_FMT_BGR565;
		पूर्ण

		अगर (var->transp.length == 1 && var->green.length <= 5) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIX_FMT_RGB1555;
			अन्यथा
				वापस PIX_FMT_BGR1555;
		पूर्ण
	पूर्ण

	/*
	 * Check क्रम 888/A888.
	 */
	अगर (var->bits_per_pixel <= 32 && var->red.length <= 8 &&
	    var->green.length <= 8 && var->blue.length <= 8) अणु
		अगर (var->bits_per_pixel == 24 && var->transp.length == 0) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIX_FMT_RGB888PACK;
			अन्यथा
				वापस PIX_FMT_BGR888PACK;
		पूर्ण

		अगर (var->bits_per_pixel == 32 && var->transp.length == 8) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIX_FMT_RGBA888;
			अन्यथा
				वापस PIX_FMT_BGRA888;
		पूर्ण अन्यथा अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIX_FMT_RGB888UNPACK;
			अन्यथा
				वापस PIX_FMT_BGR888UNPACK;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम set_pix_fmt(काष्ठा fb_var_screeninfo *var, पूर्णांक pix_fmt)
अणु
	चयन (pix_fmt) अणु
	हाल PIX_FMT_RGB565:
		var->bits_per_pixel = 16;
		var->red.offset = 11;    var->red.length = 5;
		var->green.offset = 5;   var->green.length = 6;
		var->blue.offset = 0;    var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIX_FMT_BGR565:
		var->bits_per_pixel = 16;
		var->red.offset = 0;     var->red.length = 5;
		var->green.offset = 5;   var->green.length = 6;
		var->blue.offset = 11;   var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIX_FMT_RGB1555:
		var->bits_per_pixel = 16;
		var->red.offset = 10;    var->red.length = 5;
		var->green.offset = 5;   var->green.length = 5;
		var->blue.offset = 0;    var->blue.length = 5;
		var->transp.offset = 15; var->transp.length = 1;
		अवरोध;
	हाल PIX_FMT_BGR1555:
		var->bits_per_pixel = 16;
		var->red.offset = 0;     var->red.length = 5;
		var->green.offset = 5;   var->green.length = 5;
		var->blue.offset = 10;   var->blue.length = 5;
		var->transp.offset = 15; var->transp.length = 1;
		अवरोध;
	हाल PIX_FMT_RGB888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 16;    var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;    var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIX_FMT_BGR888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 0;     var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 16;   var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIX_FMT_RGBA888:
		var->bits_per_pixel = 32;
		var->red.offset = 16;    var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;    var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		अवरोध;
	हाल PIX_FMT_BGRA888:
		var->bits_per_pixel = 32;
		var->red.offset = 0;     var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 16;   var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		अवरोध;
	हाल PIX_FMT_PSEUDOCOLOR:
		var->bits_per_pixel = 8;
		var->red.offset = 0;     var->red.length = 8;
		var->green.offset = 0;   var->green.length = 8;
		var->blue.offset = 0;    var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_mode(काष्ठा pxa168fb_info *fbi, काष्ठा fb_var_screeninfo *var,
		     काष्ठा fb_videomode *mode, पूर्णांक pix_fmt, पूर्णांक ystretch)
अणु
	काष्ठा fb_info *info = fbi->info;

	set_pix_fmt(var, pix_fmt);

	var->xres = mode->xres;
	var->yres = mode->yres;
	var->xres_भव = max(var->xres, var->xres_भव);
	अगर (ystretch)
		var->yres_भव = info->fix.smem_len /
			(var->xres_भव * (var->bits_per_pixel >> 3));
	अन्यथा
		var->yres_भव = max(var->yres, var->yres_भव);
	var->grayscale = 0;
	var->accel_flags = FB_ACCEL_NONE;
	var->pixघड़ी = mode->pixघड़ी;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->hsync_len = mode->hsync_len;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
	var->vmode = FB_VMODE_NONINTERLACED;
	var->rotate = FB_ROTATE_UR;
पूर्ण

अटल पूर्णांक pxa168fb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	पूर्णांक pix_fmt;

	/*
	 * Determine which pixel क्रमmat we're going to use.
	 */
	pix_fmt = determine_best_pix_fmt(var);
	अगर (pix_fmt < 0)
		वापस pix_fmt;
	set_pix_fmt(var, pix_fmt);
	fbi->pix_fmt = pix_fmt;

	/*
	 * Basic geometry sanity checks.
	 */
	अगर (var->xoffset + var->xres > var->xres_भव)
		वापस -EINVAL;
	अगर (var->yoffset + var->yres > var->yres_भव)
		वापस -EINVAL;
	अगर (var->xres + var->right_margin +
	    var->hsync_len + var->left_margin > 2048)
		वापस -EINVAL;
	अगर (var->yres + var->lower_margin +
	    var->vsync_len + var->upper_margin > 2048)
		वापस -EINVAL;

	/*
	 * Check size of framebuffer.
	 */
	अगर (var->xres_भव * var->yres_भव *
	    (var->bits_per_pixel >> 3) > info->fix.smem_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * The hardware घड़ी भागider has an पूर्णांकeger and a fractional
 * stage:
 *
 *	clk2 = clk_in / पूर्णांकeger_भागider
 *	clk_out = clk2 * (1 - (fractional_भागider >> 12))
 *
 * Calculate पूर्णांकeger and fractional भागider क्रम given clk_in
 * and clk_out.
 */
अटल व्योम set_घड़ी_भागider(काष्ठा pxa168fb_info *fbi,
			      स्थिर काष्ठा fb_videomode *m)
अणु
	पूर्णांक भागider_पूर्णांक;
	पूर्णांक needed_pixclk;
	u64 भाग_result;
	u32 x = 0;

	/*
	 * Notice: The field pixघड़ी is used by linux fb
	 * is in pixel second. E.g. काष्ठा fb_videomode &
	 * काष्ठा fb_var_screeninfo
	 */

	/*
	 * Check input values.
	 */
	अगर (!m || !m->pixघड़ी || !m->refresh) अणु
		dev_err(fbi->dev, "Input refresh or pixclock is wrong.\n");
		वापस;
	पूर्ण

	/*
	 * Using PLL/AXI घड़ी.
	 */
	x = 0x80000000;

	/*
	 * Calc भागider according to refresh rate.
	 */
	भाग_result = 1000000000000ll;
	करो_भाग(भाग_result, m->pixघड़ी);
	needed_pixclk = (u32)भाग_result;

	भागider_पूर्णांक = clk_get_rate(fbi->clk) / needed_pixclk;

	/* check whether भागisor is too small. */
	अगर (भागider_पूर्णांक < 2) अणु
		dev_warn(fbi->dev, "Warning: clock source is too slow. "
				"Try smaller resolution\n");
		भागider_पूर्णांक = 2;
	पूर्ण

	/*
	 * Set setting to reg.
	 */
	x |= भागider_पूर्णांक;
	ग_लिखोl(x, fbi->reg_base + LCD_CFG_SCLK_DIV);
पूर्ण

अटल व्योम set_dma_control0(काष्ठा pxa168fb_info *fbi)
अणु
	u32 x;

	/*
	 * Set bit to enable graphics DMA.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_SPU_DMA_CTRL0);
	x &= ~CFG_GRA_ENA_MASK;
	x |= fbi->active ? CFG_GRA_ENA(1) : CFG_GRA_ENA(0);

	/*
	 * If we are in a pseuकरो-color mode, we need to enable
	 * palette lookup.
	 */
	अगर (fbi->pix_fmt == PIX_FMT_PSEUDOCOLOR)
		x |= 0x10000000;

	/*
	 * Configure hardware pixel क्रमmat.
	 */
	x &= ~(0xF << 16);
	x |= (fbi->pix_fmt >> 1) << 16;

	/*
	 * Check red and blue pixel swap.
	 * 1. source data swap
	 * 2. panel output data swap
	 */
	x &= ~(1 << 12);
	x |= ((fbi->pix_fmt & 1) ^ (fbi->panel_rbswap)) << 12;

	ग_लिखोl(x, fbi->reg_base + LCD_SPU_DMA_CTRL0);
पूर्ण

अटल व्योम set_dma_control1(काष्ठा pxa168fb_info *fbi, पूर्णांक sync)
अणु
	u32 x;

	/*
	 * Configure शेष bits: vsync triggers DMA, gated घड़ी
	 * enable, घातer save enable, configure alpha रेजिस्टरs to
	 * display 100% graphics, and set pixel command.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_SPU_DMA_CTRL1);
	x |= 0x2032ff81;

	/*
	 * We trigger DMA on the falling edge of vsync अगर vsync is
	 * active low, or on the rising edge अगर vsync is active high.
	 */
	अगर (!(sync & FB_SYNC_VERT_HIGH_ACT))
		x |= 0x08000000;

	ग_लिखोl(x, fbi->reg_base + LCD_SPU_DMA_CTRL1);
पूर्ण

अटल व्योम set_graphics_start(काष्ठा fb_info *info, पूर्णांक xoffset, पूर्णांक yoffset)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक pixel_offset;
	अचिन्हित दीर्घ addr;

	pixel_offset = (yoffset * var->xres_भव) + xoffset;

	addr = fbi->fb_start_dma + (pixel_offset * (var->bits_per_pixel >> 3));
	ग_लिखोl(addr, fbi->reg_base + LCD_CFG_GRA_START_ADDR0);
पूर्ण

अटल व्योम set_dumb_panel_control(काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	काष्ठा pxa168fb_mach_info *mi = dev_get_platdata(fbi->dev);
	u32 x;

	/*
	 * Preserve enable flag.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_SPU_DUMB_CTRL) & 0x00000001;

	x |= (fbi->is_blanked ? 0x7 : mi->dumb_mode) << 28;
	x |= mi->gpio_output_data << 20;
	x |= mi->gpio_output_mask << 12;
	x |= mi->panel_rgb_reverse_lanes ? 0x00000080 : 0;
	x |= mi->invert_composite_blank ? 0x00000040 : 0;
	x |= (info->var.sync & FB_SYNC_COMP_HIGH_ACT) ? 0x00000020 : 0;
	x |= mi->invert_pix_val_ena ? 0x00000010 : 0;
	x |= (info->var.sync & FB_SYNC_VERT_HIGH_ACT) ? 0 : 0x00000008;
	x |= (info->var.sync & FB_SYNC_HOR_HIGH_ACT) ? 0 : 0x00000004;
	x |= mi->invert_pixघड़ी ? 0x00000002 : 0;

	ग_लिखोl(x, fbi->reg_base + LCD_SPU_DUMB_CTRL);
पूर्ण

अटल व्योम set_dumb_screen_dimensions(काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *v = &info->var;
	पूर्णांक x;
	पूर्णांक y;

	x = v->xres + v->right_margin + v->hsync_len + v->left_margin;
	y = v->yres + v->lower_margin + v->vsync_len + v->upper_margin;

	ग_लिखोl((y << 16) | x, fbi->reg_base + LCD_SPUT_V_H_TOTAL);
पूर्ण

अटल पूर्णांक pxa168fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा fb_videomode mode;
	u32 x;

	/*
	 * Set additional mode info.
	 */
	अगर (fbi->pix_fmt == PIX_FMT_PSEUDOCOLOR)
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.line_length = var->xres_भव * var->bits_per_pixel / 8;
	info->fix.ypanstep = var->yres;

	/*
	 * Disable panel output जबतक we setup the display.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_SPU_DUMB_CTRL);
	ग_लिखोl(x & ~1, fbi->reg_base + LCD_SPU_DUMB_CTRL);

	/*
	 * Configure global panel parameters.
	 */
	ग_लिखोl((var->yres << 16) | var->xres,
		fbi->reg_base + LCD_SPU_V_H_ACTIVE);

	/*
	 * convet var to video mode
	 */
	fb_var_to_videomode(&mode, &info->var);

	/* Calculate घड़ी भागisor. */
	set_घड़ी_भागider(fbi, &mode);

	/* Configure dma ctrl regs. */
	set_dma_control0(fbi);
	set_dma_control1(fbi, info->var.sync);

	/*
	 * Configure graphics DMA parameters.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_CFG_GRA_PITCH);
	x = (x & ~0xFFFF) | ((var->xres_भव * var->bits_per_pixel) >> 3);
	ग_लिखोl(x, fbi->reg_base + LCD_CFG_GRA_PITCH);
	ग_लिखोl((var->yres << 16) | var->xres,
		fbi->reg_base + LCD_SPU_GRA_HPXL_VLN);
	ग_लिखोl((var->yres << 16) | var->xres,
		fbi->reg_base + LCD_SPU_GZM_HPXL_VLN);

	/*
	 * Configure dumb panel ctrl regs & timings.
	 */
	set_dumb_panel_control(info);
	set_dumb_screen_dimensions(info);

	ग_लिखोl((var->left_margin << 16) | var->right_margin,
			fbi->reg_base + LCD_SPU_H_PORCH);
	ग_लिखोl((var->upper_margin << 16) | var->lower_margin,
			fbi->reg_base + LCD_SPU_V_PORCH);

	/*
	 * Re-enable panel output.
	 */
	x = पढ़ोl(fbi->reg_base + LCD_SPU_DUMB_CTRL);
	ग_लिखोl(x | 1, fbi->reg_base + LCD_SPU_DUMB_CTRL);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	वापस ((chan & 0xffff) >> (16 - bf->length)) << bf->offset;
पूर्ण

अटल u32 to_rgb(u16 red, u16 green, u16 blue)
अणु
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	वापस (red << 16) | (green << 8) | blue;
पूर्ण

अटल पूर्णांक
pxa168fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red, अचिन्हित पूर्णांक green,
		 अचिन्हित पूर्णांक blue, अचिन्हित पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	u32 val;

	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
					7471 * blue) >> 16;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 16) अणु
		val =  chan_to_field(red,   &info->var.red);
		val |= chan_to_field(green, &info->var.green);
		val |= chan_to_field(blue , &info->var.blue);
		fbi->pseuकरो_palette[regno] = val;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR && regno < 256) अणु
		val = to_rgb(red, green, blue);
		ग_लिखोl(val, fbi->reg_base + LCD_SPU_SRAM_WRDAT);
		ग_लिखोl(0x8300 | regno, fbi->reg_base + LCD_SPU_SRAM_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pxa168fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;

	fbi->is_blanked = (blank == FB_BLANK_UNBLANK) ? 0 : 1;
	set_dumb_panel_control(info);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa168fb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	set_graphics_start(info, var->xoffset, var->yoffset);

	वापस 0;
पूर्ण

अटल irqवापस_t pxa168fb_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxa168fb_info *fbi = dev_id;
	u32 isr = पढ़ोl(fbi->reg_base + SPU_IRQ_ISR);

	अगर ((isr & GRA_FRAME_IRQ0_ENA_MASK)) अणु

		ग_लिखोl(isr & (~GRA_FRAME_IRQ0_ENA_MASK),
			fbi->reg_base + SPU_IRQ_ISR);

		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा fb_ops pxa168fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= pxa168fb_check_var,
	.fb_set_par	= pxa168fb_set_par,
	.fb_setcolreg	= pxa168fb_setcolreg,
	.fb_blank	= pxa168fb_blank,
	.fb_pan_display	= pxa168fb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल व्योम pxa168fb_init_mode(काष्ठा fb_info *info,
			      काष्ठा pxa168fb_mach_info *mi)
अणु
	काष्ठा pxa168fb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	u32 total_w, total_h, refresh;
	u64 भाग_result;
	स्थिर काष्ठा fb_videomode *m;

	/*
	 * Set शेष value
	 */
	refresh = DEFAULT_REFRESH;

	/* try to find best video mode. */
	m = fb_find_best_mode(&info->var, &info->modelist);
	अगर (m)
		fb_videomode_to_var(&info->var, m);

	/* Init settings. */
	var->xres_भव = var->xres;
	var->yres_भव = info->fix.smem_len /
		(var->xres_भव * (var->bits_per_pixel >> 3));
	dev_dbg(fbi->dev, "pxa168fb: find best mode: res = %dx%d\n",
				var->xres, var->yres);

	/* correct pixघड़ी. */
	total_w = var->xres + var->left_margin + var->right_margin +
		  var->hsync_len;
	total_h = var->yres + var->upper_margin + var->lower_margin +
		  var->vsync_len;

	भाग_result = 1000000000000ll;
	करो_भाग(भाग_result, total_w * total_h * refresh);
	var->pixघड़ी = (u32)भाग_result;
पूर्ण

अटल पूर्णांक pxa168fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa168fb_mach_info *mi;
	काष्ठा fb_info *info = 0;
	काष्ठा pxa168fb_info *fbi = 0;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	पूर्णांक irq, ret;

	mi = dev_get_platdata(&pdev->dev);
	अगर (mi == शून्य) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		वापस -EINVAL;
	पूर्ण

	clk = devm_clk_get(&pdev->dev, "LCDCLK");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get LCDCLK");
		वापस PTR_ERR(clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no IO memory defined\n");
		वापस -ENOENT;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "no IRQ defined\n");
		वापस -ENOENT;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा pxa168fb_info), &pdev->dev);
	अगर (info == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	/* Initialize निजी data */
	fbi = info->par;
	fbi->info = info;
	fbi->clk = clk;
	fbi->dev = info->dev = &pdev->dev;
	fbi->panel_rbswap = mi->panel_rbswap;
	fbi->is_blanked = 0;
	fbi->active = mi->active;

	/*
	 * Initialise अटल fb parameters.
	 */
	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK |
		      FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;
	info->node = -1;
	strlcpy(info->fix.id, mi->id, 16);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
	info->fix.ywrapstep = 0;
	info->fix.mmio_start = res->start;
	info->fix.mmio_len = resource_size(res);
	info->fix.accel = FB_ACCEL_NONE;
	info->fbops = &pxa168fb_ops;
	info->pseuकरो_palette = fbi->pseuकरो_palette;

	/*
	 * Map LCD controller रेजिस्टरs.
	 */
	fbi->reg_base = devm_ioremap(&pdev->dev, res->start,
					     resource_size(res));
	अगर (fbi->reg_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ failed_मुक्त_info;
	पूर्ण

	/*
	 * Allocate framebuffer memory.
	 */
	info->fix.smem_len = PAGE_ALIGN(DEFAULT_FB_SIZE);

	info->screen_base = dma_alloc_wc(fbi->dev, info->fix.smem_len,
					 &fbi->fb_start_dma, GFP_KERNEL);
	अगर (info->screen_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ failed_मुक्त_info;
	पूर्ण

	info->fix.smem_start = (अचिन्हित दीर्घ)fbi->fb_start_dma;
	set_graphics_start(info, 0, 0);

	/*
	 * Set video mode according to platक्रमm data.
	 */
	set_mode(fbi, &info->var, mi->modes, mi->pix_fmt, 1);

	fb_videomode_to_modelist(mi->modes, mi->num_modes, &info->modelist);

	/*
	 * init video mode data.
	 */
	pxa168fb_init_mode(info, mi);

	/*
	 * Fill in sane शेषs.
	 */
	ret = pxa168fb_check_var(&info->var, info);
	अगर (ret)
		जाओ failed_मुक्त_fbmem;

	/*
	 * enable controller घड़ी
	 */
	clk_prepare_enable(fbi->clk);

	pxa168fb_set_par(info);

	/*
	 * Configure शेष रेजिस्टर values.
	 */
	ग_लिखोl(0, fbi->reg_base + LCD_SPU_BLANKCOLOR);
	ग_लिखोl(mi->io_pin_allocation_mode, fbi->reg_base + SPU_IOPAD_CONTROL);
	ग_लिखोl(0, fbi->reg_base + LCD_CFG_GRA_START_ADDR1);
	ग_लिखोl(0, fbi->reg_base + LCD_SPU_GRA_OVSA_HPXL_VLN);
	ग_लिखोl(0, fbi->reg_base + LCD_SPU_SRAM_PARA0);
	ग_लिखोl(CFG_CSB_256x32(0x1)|CFG_CSB_256x24(0x1)|CFG_CSB_256x8(0x1),
		fbi->reg_base + LCD_SPU_SRAM_PARA1);

	/*
	 * Allocate color map.
	 */
	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		ret = -ENOMEM;
		जाओ failed_मुक्त_clk;
	पूर्ण

	/*
	 * Register irq handler.
	 */
	ret = devm_request_irq(&pdev->dev, irq, pxa168fb_handle_irq,
			       IRQF_SHARED, info->fix.id, fbi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to request IRQ\n");
		ret = -ENXIO;
		जाओ failed_मुक्त_cmap;
	पूर्ण

	/*
	 * Enable GFX पूर्णांकerrupt
	 */
	ग_लिखोl(GRA_FRAME_IRQ0_ENA(0x1), fbi->reg_base + SPU_IRQ_ENA);

	/*
	 * Register framebuffer.
	 */
	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register pxa168-fb: %d\n", ret);
		ret = -ENXIO;
		जाओ failed_मुक्त_cmap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, fbi);
	वापस 0;

failed_मुक्त_cmap:
	fb_dealloc_cmap(&info->cmap);
failed_मुक्त_clk:
	clk_disable_unprepare(fbi->clk);
failed_मुक्त_fbmem:
	dma_मुक्त_wc(fbi->dev, info->fix.smem_len,
		    info->screen_base, fbi->fb_start_dma);
failed_मुक्त_info:
	framebuffer_release(info);

	dev_err(&pdev->dev, "frame buffer device init failed with %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक pxa168fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa168fb_info *fbi = platक्रमm_get_drvdata(pdev);
	काष्ठा fb_info *info;
	अचिन्हित पूर्णांक data;

	अगर (!fbi)
		वापस 0;

	/* disable DMA transfer */
	data = पढ़ोl(fbi->reg_base + LCD_SPU_DMA_CTRL0);
	data &= ~CFG_GRA_ENA_MASK;
	ग_लिखोl(data, fbi->reg_base + LCD_SPU_DMA_CTRL0);

	info = fbi->info;

	unरेजिस्टर_framebuffer(info);

	ग_लिखोl(GRA_FRAME_IRQ0_ENA(0x0), fbi->reg_base + SPU_IRQ_ENA);

	अगर (info->cmap.len)
		fb_dealloc_cmap(&info->cmap);

	dma_मुक्त_wc(fbi->dev, info->fix.smem_len,
		    info->screen_base, info->fix.smem_start);

	clk_disable_unprepare(fbi->clk);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa168fb_driver = अणु
	.driver		= अणु
		.name	= "pxa168-fb",
	पूर्ण,
	.probe		= pxa168fb_probe,
	.हटाओ		= pxa168fb_हटाओ,
पूर्ण;

module_platक्रमm_driver(pxa168fb_driver);

MODULE_AUTHOR("Lennert Buytenhek <buytenh@marvell.com> "
	      "Green Wan <gwan@marvell.com>");
MODULE_DESCRIPTION("Framebuffer driver for PXA168/910");
MODULE_LICENSE("GPL");
