<शैली गुरु>
/*
 *  linux/drivers/video/amba-clcd.c
 *
 * Copyright (C) 2001 ARM Limited, by David A Rusling
 * Updated to 2.5, Deep Blue Solutions Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 *  ARM PrimeCell PL110 Color LCD Controller
 */
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/clcd.h>
#समावेश <linux/backlight.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/videomode.h>

#घोषणा to_clcd(info)	container_of(info, काष्ठा clcd_fb, fb)

/* This is limited to 16 अक्षरacters when displayed by X startup */
अटल स्थिर अक्षर *clcd_name = "CLCD FB";

अटल अंतरभूत व्योम clcdfb_set_start(काष्ठा clcd_fb *fb)
अणु
	अचिन्हित दीर्घ ustart = fb->fb.fix.smem_start;
	अचिन्हित दीर्घ lstart;

	ustart += fb->fb.var.yoffset * fb->fb.fix.line_length;
	lstart = ustart + fb->fb.var.yres * fb->fb.fix.line_length / 2;

	ग_लिखोl(ustart, fb->regs + CLCD_UBAS);
	ग_लिखोl(lstart, fb->regs + CLCD_LBAS);
पूर्ण

अटल व्योम clcdfb_disable(काष्ठा clcd_fb *fb)
अणु
	u32 val;

	अगर (fb->board->disable)
		fb->board->disable(fb);

	अगर (fb->panel->backlight) अणु
		fb->panel->backlight->props.घातer = FB_BLANK_POWERDOWN;
		backlight_update_status(fb->panel->backlight);
	पूर्ण

	val = पढ़ोl(fb->regs + fb->off_cntl);
	अगर (val & CNTL_LCDPWR) अणु
		val &= ~CNTL_LCDPWR;
		ग_लिखोl(val, fb->regs + fb->off_cntl);

		msleep(20);
	पूर्ण
	अगर (val & CNTL_LCDEN) अणु
		val &= ~CNTL_LCDEN;
		ग_लिखोl(val, fb->regs + fb->off_cntl);
	पूर्ण

	/*
	 * Disable CLCD घड़ी source.
	 */
	अगर (fb->clk_enabled) अणु
		fb->clk_enabled = false;
		clk_disable(fb->clk);
	पूर्ण
पूर्ण

अटल व्योम clcdfb_enable(काष्ठा clcd_fb *fb, u32 cntl)
अणु
	/*
	 * Enable the CLCD घड़ी source.
	 */
	अगर (!fb->clk_enabled) अणु
		fb->clk_enabled = true;
		clk_enable(fb->clk);
	पूर्ण

	/*
	 * Bring up by first enabling..
	 */
	cntl |= CNTL_LCDEN;
	ग_लिखोl(cntl, fb->regs + fb->off_cntl);

	msleep(20);

	/*
	 * and now apply घातer.
	 */
	cntl |= CNTL_LCDPWR;
	ग_लिखोl(cntl, fb->regs + fb->off_cntl);

	/*
	 * Turn on backlight
	 */
	अगर (fb->panel->backlight) अणु
		fb->panel->backlight->props.घातer = FB_BLANK_UNBLANK;
		backlight_update_status(fb->panel->backlight);
	पूर्ण

	/*
	 * finally, enable the पूर्णांकerface.
	 */
	अगर (fb->board->enable)
		fb->board->enable(fb);
पूर्ण

अटल पूर्णांक
clcdfb_set_bitfields(काष्ठा clcd_fb *fb, काष्ठा fb_var_screeninfo *var)
अणु
	u32 caps;
	पूर्णांक ret = 0;

	अगर (fb->panel->caps && fb->board->caps)
		caps = fb->panel->caps & fb->board->caps;
	अन्यथा अणु
		/* Old way of specअगरying what can be used */
		caps = fb->panel->cntl & CNTL_BGR ?
			CLCD_CAP_BGR : CLCD_CAP_RGB;
		/* But mask out 444 modes as they weren't supported */
		caps &= ~CLCD_CAP_444;
	पूर्ण

	/* Only TFT panels can करो RGB888/BGR888 */
	अगर (!(fb->panel->cntl & CNTL_LCDTFT))
		caps &= ~CLCD_CAP_888;

	स_रखो(&var->transp, 0, माप(var->transp));

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		/* If we can't करो 5551, reject */
		caps &= CLCD_CAP_5551;
		अगर (!caps) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		var->red.length		= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.length	= var->bits_per_pixel;
		var->green.offset	= 0;
		var->blue.length	= var->bits_per_pixel;
		var->blue.offset	= 0;
		अवरोध;

	हाल 16:
		/* If we can't करो 444, 5551 or 565, reject */
		अगर (!(caps & (CLCD_CAP_444 | CLCD_CAP_5551 | CLCD_CAP_565))) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Green length can be 4, 5 or 6 depending whether
		 * we're operating in 444, 5551 or 565 mode.
		 */
		अगर (var->green.length == 4 && caps & CLCD_CAP_444)
			caps &= CLCD_CAP_444;
		अगर (var->green.length == 5 && caps & CLCD_CAP_5551)
			caps &= CLCD_CAP_5551;
		अन्यथा अगर (var->green.length == 6 && caps & CLCD_CAP_565)
			caps &= CLCD_CAP_565;
		अन्यथा अणु
			/*
			 * PL110 officially only supports RGB555,
			 * but may be wired up to allow RGB565.
			 */
			अगर (caps & CLCD_CAP_565) अणु
				var->green.length = 6;
				caps &= CLCD_CAP_565;
			पूर्ण अन्यथा अगर (caps & CLCD_CAP_5551) अणु
				var->green.length = 5;
				caps &= CLCD_CAP_5551;
			पूर्ण अन्यथा अणु
				var->green.length = 4;
				caps &= CLCD_CAP_444;
			पूर्ण
		पूर्ण

		अगर (var->green.length >= 5) अणु
			var->red.length = 5;
			var->blue.length = 5;
		पूर्ण अन्यथा अणु
			var->red.length = 4;
			var->blue.length = 4;
		पूर्ण
		अवरोध;
	हाल 32:
		/* If we can't करो 888, reject */
		caps &= CLCD_CAP_888;
		अगर (!caps) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	/*
	 * >= 16bpp displays have separate colour component bitfields
	 * encoded in the pixel data.  Calculate their position from
	 * the bitfield length defined above.
	 */
	अगर (ret == 0 && var->bits_per_pixel >= 16) अणु
		bool bgr, rgb;

		bgr = caps & CLCD_CAP_BGR && var->blue.offset == 0;
		rgb = caps & CLCD_CAP_RGB && var->red.offset == 0;

		अगर (!bgr && !rgb)
			/*
			 * The requested क्रमmat was not possible, try just
			 * our capabilities.  One of BGR or RGB must be
			 * supported.
			 */
			bgr = caps & CLCD_CAP_BGR;

		अगर (bgr) अणु
			var->blue.offset = 0;
			var->green.offset = var->blue.offset + var->blue.length;
			var->red.offset = var->green.offset + var->green.length;
		पूर्ण अन्यथा अणु
			var->red.offset = 0;
			var->green.offset = var->red.offset + var->red.length;
			var->blue.offset = var->green.offset + var->green.length;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clcdfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा clcd_fb *fb = to_clcd(info);
	पूर्णांक ret = -EINVAL;

	अगर (fb->board->check)
		ret = fb->board->check(fb, var);

	अगर (ret == 0 &&
	    var->xres_भव * var->bits_per_pixel / 8 *
	    var->yres_भव > fb->fb.fix.smem_len)
		ret = -EINVAL;

	अगर (ret == 0)
		ret = clcdfb_set_bitfields(fb, var);

	वापस ret;
पूर्ण

अटल पूर्णांक clcdfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा clcd_fb *fb = to_clcd(info);
	काष्ठा clcd_regs regs;

	fb->fb.fix.line_length = fb->fb.var.xres_भव *
				 fb->fb.var.bits_per_pixel / 8;

	अगर (fb->fb.var.bits_per_pixel <= 8)
		fb->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा
		fb->fb.fix.visual = FB_VISUAL_TRUECOLOR;

	fb->board->decode(fb, &regs);

	clcdfb_disable(fb);

	ग_लिखोl(regs.tim0, fb->regs + CLCD_TIM0);
	ग_लिखोl(regs.tim1, fb->regs + CLCD_TIM1);
	ग_लिखोl(regs.tim2, fb->regs + CLCD_TIM2);
	ग_लिखोl(regs.tim3, fb->regs + CLCD_TIM3);

	clcdfb_set_start(fb);

	clk_set_rate(fb->clk, (1000000000 / regs.pixघड़ी) * 1000);

	fb->clcd_cntl = regs.cntl;

	clcdfb_enable(fb, regs.cntl);

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_INFO
	       "CLCD: Registers set to\n"
	       "  %08x %08x %08x %08x\n"
	       "  %08x %08x %08x %08x\n",
		पढ़ोl(fb->regs + CLCD_TIM0), पढ़ोl(fb->regs + CLCD_TIM1),
		पढ़ोl(fb->regs + CLCD_TIM2), पढ़ोl(fb->regs + CLCD_TIM3),
		पढ़ोl(fb->regs + CLCD_UBAS), पढ़ोl(fb->regs + CLCD_LBAS),
		पढ़ोl(fb->regs + fb->off_ienb), पढ़ोl(fb->regs + fb->off_cntl));
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल अंतरभूत u32 convert_bitfield(पूर्णांक val, काष्ठा fb_bitfield *bf)
अणु
	अचिन्हित पूर्णांक mask = (1 << bf->length) - 1;

	वापस (val >> (16 - bf->length) & mask) << bf->offset;
पूर्ण

/*
 *  Set a single color रेजिस्टर. The values supplied have a 16 bit
 *  magnitude.  Return != 0 क्रम invalid regno.
 */
अटल पूर्णांक
clcdfb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red, अचिन्हित पूर्णांक green,
		 अचिन्हित पूर्णांक blue, अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा clcd_fb *fb = to_clcd(info);

	अगर (regno < 16)
		fb->cmap[regno] = convert_bitfield(transp, &fb->fb.var.transp) |
				  convert_bitfield(blue, &fb->fb.var.blue) |
				  convert_bitfield(green, &fb->fb.var.green) |
				  convert_bitfield(red, &fb->fb.var.red);

	अगर (fb->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR && regno < 256) अणु
		पूर्णांक hw_reg = CLCD_PALETTE + ((regno * 2) & ~3);
		u32 val, mask, newval;

		newval  = (red >> 11)  & 0x001f;
		newval |= (green >> 6) & 0x03e0;
		newval |= (blue >> 1)  & 0x7c00;

		/*
		 * 3.2.11: अगर we're configured क्रम big endian
		 * byte order, the palette entries are swapped.
		 */
		अगर (fb->clcd_cntl & CNTL_BEBO)
			regno ^= 1;

		अगर (regno & 1) अणु
			newval <<= 16;
			mask = 0x0000ffff;
		पूर्ण अन्यथा अणु
			mask = 0xffff0000;
		पूर्ण

		val = पढ़ोl(fb->regs + hw_reg) & mask;
		ग_लिखोl(val | newval, fb->regs + hw_reg);
	पूर्ण

	वापस regno > 255;
पूर्ण

/*
 *  Blank the screen अगर blank_mode != 0, अन्यथा unblank. If blank == शून्य
 *  then the caller blanks by setting the CLUT (Color Look Up Table) to all
 *  black. Return 0 अगर blanking succeeded, != 0 अगर un-/blanking failed due
 *  to e.g. a video mode which करोesn't support it. Implements VESA suspend
 *  and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *    blank_mode == 2: suspend vsync
 *    blank_mode == 3: suspend hsync
 *    blank_mode == 4: घातerकरोwn
 */
अटल पूर्णांक clcdfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा clcd_fb *fb = to_clcd(info);

	अगर (blank_mode != 0) अणु
		clcdfb_disable(fb);
	पूर्ण अन्यथा अणु
		clcdfb_enable(fb, fb->clcd_cntl);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_mmap(काष्ठा fb_info *info,
		       काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा clcd_fb *fb = to_clcd(info);
	अचिन्हित दीर्घ len, off = vma->vm_pgoff << PAGE_SHIFT;
	पूर्णांक ret = -EINVAL;

	len = info->fix.smem_len;

	अगर (off <= len && vma->vm_end - vma->vm_start <= len - off &&
	    fb->board->mmap)
		ret = fb->board->mmap(fb, vma);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fb_ops clcdfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= clcdfb_check_var,
	.fb_set_par	= clcdfb_set_par,
	.fb_setcolreg	= clcdfb_setcolreg,
	.fb_blank	= clcdfb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_mmap	= clcdfb_mmap,
पूर्ण;

अटल पूर्णांक clcdfb_रेजिस्टर(काष्ठा clcd_fb *fb)
अणु
	पूर्णांक ret;

	/*
	 * ARM PL111 always has IENB at 0x1c; it's only PL110
	 * which is reversed on some platक्रमms.
	 */
	अगर (amba_manf(fb->dev) == 0x41 && amba_part(fb->dev) == 0x111) अणु
		fb->off_ienb = CLCD_PL111_IENB;
		fb->off_cntl = CLCD_PL111_CNTL;
	पूर्ण अन्यथा अणु
		fb->off_ienb = CLCD_PL110_IENB;
		fb->off_cntl = CLCD_PL110_CNTL;
	पूर्ण

	fb->clk = clk_get(&fb->dev->dev, शून्य);
	अगर (IS_ERR(fb->clk)) अणु
		ret = PTR_ERR(fb->clk);
		जाओ out;
	पूर्ण

	ret = clk_prepare(fb->clk);
	अगर (ret)
		जाओ मुक्त_clk;

	fb->fb.device		= &fb->dev->dev;

	fb->fb.fix.mmio_start	= fb->dev->res.start;
	fb->fb.fix.mmio_len	= resource_size(&fb->dev->res);

	fb->regs = ioremap(fb->fb.fix.mmio_start, fb->fb.fix.mmio_len);
	अगर (!fb->regs) अणु
		prपूर्णांकk(KERN_ERR "CLCD: unable to remap registers\n");
		ret = -ENOMEM;
		जाओ clk_unprep;
	पूर्ण

	fb->fb.fbops		= &clcdfb_ops;
	fb->fb.flags		= FBINFO_FLAG_DEFAULT;
	fb->fb.pseuकरो_palette	= fb->cmap;

	म_नकलन(fb->fb.fix.id, clcd_name, माप(fb->fb.fix.id));
	fb->fb.fix.type		= FB_TYPE_PACKED_PIXELS;
	fb->fb.fix.type_aux	= 0;
	fb->fb.fix.xpanstep	= 0;
	fb->fb.fix.ypanstep	= 0;
	fb->fb.fix.ywrapstep	= 0;
	fb->fb.fix.accel	= FB_ACCEL_NONE;

	fb->fb.var.xres		= fb->panel->mode.xres;
	fb->fb.var.yres		= fb->panel->mode.yres;
	fb->fb.var.xres_भव	= fb->panel->mode.xres;
	fb->fb.var.yres_भव	= fb->panel->mode.yres;
	fb->fb.var.bits_per_pixel = fb->panel->bpp;
	fb->fb.var.grayscale	= fb->panel->grayscale;
	fb->fb.var.pixघड़ी	= fb->panel->mode.pixघड़ी;
	fb->fb.var.left_margin	= fb->panel->mode.left_margin;
	fb->fb.var.right_margin	= fb->panel->mode.right_margin;
	fb->fb.var.upper_margin	= fb->panel->mode.upper_margin;
	fb->fb.var.lower_margin	= fb->panel->mode.lower_margin;
	fb->fb.var.hsync_len	= fb->panel->mode.hsync_len;
	fb->fb.var.vsync_len	= fb->panel->mode.vsync_len;
	fb->fb.var.sync		= fb->panel->mode.sync;
	fb->fb.var.vmode	= fb->panel->mode.vmode;
	fb->fb.var.activate	= FB_ACTIVATE_NOW;
	fb->fb.var.nonstd	= 0;
	fb->fb.var.height	= fb->panel->height;
	fb->fb.var.width	= fb->panel->width;
	fb->fb.var.accel_flags	= 0;

	fb->fb.monspecs.hfmin	= 0;
	fb->fb.monspecs.hfmax   = 100000;
	fb->fb.monspecs.vfmin	= 0;
	fb->fb.monspecs.vfmax	= 400;
	fb->fb.monspecs.dclkmin = 1000000;
	fb->fb.monspecs.dclkmax	= 100000000;

	/*
	 * Make sure that the bitfields are set appropriately.
	 */
	clcdfb_set_bitfields(fb, &fb->fb.var);

	/*
	 * Allocate colourmap.
	 */
	ret = fb_alloc_cmap(&fb->fb.cmap, 256, 0);
	अगर (ret)
		जाओ unmap;

	/*
	 * Ensure पूर्णांकerrupts are disabled.
	 */
	ग_लिखोl(0, fb->regs + fb->off_ienb);

	fb_set_var(&fb->fb, &fb->fb.var);

	dev_info(&fb->dev->dev, "%s hardware, %s display\n",
	         fb->board->name, fb->panel->mode.name);

	ret = रेजिस्टर_framebuffer(&fb->fb);
	अगर (ret == 0)
		जाओ out;

	prपूर्णांकk(KERN_ERR "CLCD: cannot register framebuffer (%d)\n", ret);

	fb_dealloc_cmap(&fb->fb.cmap);
 unmap:
	iounmap(fb->regs);
 clk_unprep:
	clk_unprepare(fb->clk);
 मुक्त_clk:
	clk_put(fb->clk);
 out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक clcdfb_of_get_dpi_panel_mode(काष्ठा device_node *node,
		काष्ठा clcd_panel *clcd_panel)
अणु
	पूर्णांक err;
	काष्ठा display_timing timing;
	काष्ठा videomode video;

	err = of_get_display_timing(node, "panel-timing", &timing);
	अगर (err) अणु
		pr_err("%pOF: problems parsing panel-timing (%d)\n", node, err);
		वापस err;
	पूर्ण

	videomode_from_timing(&timing, &video);

	err = fb_videomode_from_videomode(&video, &clcd_panel->mode);
	अगर (err)
		वापस err;

	/* Set up some inversion flags */
	अगर (timing.flags & DISPLAY_FLAGS_PIXDATA_NEGEDGE)
		clcd_panel->tim2 |= TIM2_IPC;
	अन्यथा अगर (!(timing.flags & DISPLAY_FLAGS_PIXDATA_POSEDGE))
		/*
		 * To preserve backwards compatibility, the IPC (inverted
		 * pixel घड़ी) flag needs to be set on any display that
		 * करोesn't explicitly specअगरy that the pixel घड़ी is
		 * active on the negative or positive edge.
		 */
		clcd_panel->tim2 |= TIM2_IPC;

	अगर (timing.flags & DISPLAY_FLAGS_HSYNC_LOW)
		clcd_panel->tim2 |= TIM2_IHS;

	अगर (timing.flags & DISPLAY_FLAGS_VSYNC_LOW)
		clcd_panel->tim2 |= TIM2_IVS;

	अगर (timing.flags & DISPLAY_FLAGS_DE_LOW)
		clcd_panel->tim2 |= TIM2_IOE;

	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_snम_लिखो_mode(अक्षर *buf, पूर्णांक size, काष्ठा fb_videomode *mode)
अणु
	वापस snम_लिखो(buf, size, "%ux%u@%u", mode->xres, mode->yres,
			mode->refresh);
पूर्ण

अटल पूर्णांक clcdfb_of_get_backlight(काष्ठा device *dev,
				   काष्ठा clcd_panel *clcd_panel)
अणु
	काष्ठा backlight_device *backlight;

	/* Look up the optional backlight device */
	backlight = devm_of_find_backlight(dev);
	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);

	clcd_panel->backlight = backlight;
	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_of_get_mode(काष्ठा device *dev, काष्ठा device_node *panel,
			      काष्ठा clcd_panel *clcd_panel)
अणु
	पूर्णांक err;
	काष्ठा fb_videomode *mode;
	अक्षर *name;
	पूर्णांक len;

	/* Only directly connected DPI panels supported क्रम now */
	अगर (of_device_is_compatible(panel, "panel-dpi"))
		err = clcdfb_of_get_dpi_panel_mode(panel, clcd_panel);
	अन्यथा
		err = -ENOENT;
	अगर (err)
		वापस err;
	mode = &clcd_panel->mode;

	len = clcdfb_snम_लिखो_mode(शून्य, 0, mode);
	name = devm_kzalloc(dev, len + 1, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	clcdfb_snम_लिखो_mode(name, len + 1, mode);
	mode->name = name;

	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_of_init_tft_panel(काष्ठा clcd_fb *fb, u32 r0, u32 g0, u32 b0)
अणु
	अटल काष्ठा अणु
		अचिन्हित पूर्णांक part;
		u32 r0, g0, b0;
		u32 caps;
	पूर्ण panels[] = अणु
		अणु 0x110, 1,  7, 13, CLCD_CAP_5551 पूर्ण,
		अणु 0x110, 0,  8, 16, CLCD_CAP_888 पूर्ण,
		अणु 0x110, 16, 8, 0,  CLCD_CAP_888 पूर्ण,
		अणु 0x111, 4, 14, 20, CLCD_CAP_444 पूर्ण,
		अणु 0x111, 3, 11, 19, CLCD_CAP_444 | CLCD_CAP_5551 पूर्ण,
		अणु 0x111, 3, 10, 19, CLCD_CAP_444 | CLCD_CAP_5551 |
				    CLCD_CAP_565 पूर्ण,
		अणु 0x111, 0,  8, 16, CLCD_CAP_444 | CLCD_CAP_5551 |
				    CLCD_CAP_565 | CLCD_CAP_888 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	/* Bypass pixel घड़ी भागider */
	fb->panel->tim2 |= TIM2_BCD;

	/* TFT display, vert. comp. पूर्णांकerrupt at the start of the back porch */
	fb->panel->cntl |= CNTL_LCDTFT | CNTL_LCDVCOMP(1);

	fb->panel->caps = 0;

	/* Match the setup with known variants */
	क्रम (i = 0; i < ARRAY_SIZE(panels) && !fb->panel->caps; i++) अणु
		अगर (amba_part(fb->dev) != panels[i].part)
			जारी;
		अगर (g0 != panels[i].g0)
			जारी;
		अगर (r0 == panels[i].r0 && b0 == panels[i].b0)
			fb->panel->caps = panels[i].caps;
	पूर्ण

	/*
	 * If we actually physically connected the R lines to B and
	 * vice versa
	 */
	अगर (r0 != 0 && b0 == 0)
		fb->panel->bgr_connection = true;

	वापस fb->panel->caps ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक clcdfb_of_init_display(काष्ठा clcd_fb *fb)
अणु
	काष्ठा device_node *endpoपूर्णांक, *panel;
	पूर्णांक err;
	अचिन्हित पूर्णांक bpp;
	u32 max_bandwidth;
	u32 tft_r0b0g0[3];

	fb->panel = devm_kzalloc(&fb->dev->dev, माप(*fb->panel), GFP_KERNEL);
	अगर (!fb->panel)
		वापस -ENOMEM;

	/*
	 * Fetch the panel endpoपूर्णांक.
	 */
	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(fb->dev->dev.of_node, शून्य);
	अगर (!endpoपूर्णांक)
		वापस -ENODEV;

	panel = of_graph_get_remote_port_parent(endpoपूर्णांक);
	अगर (!panel)
		वापस -ENODEV;

	err = clcdfb_of_get_backlight(&fb->dev->dev, fb->panel);
	अगर (err)
		वापस err;

	err = clcdfb_of_get_mode(&fb->dev->dev, panel, fb->panel);
	अगर (err)
		वापस err;

	err = of_property_पढ़ो_u32(fb->dev->dev.of_node, "max-memory-bandwidth",
			&max_bandwidth);
	अगर (!err) अणु
		/*
		 * max_bandwidth is in bytes per second and pixघड़ी in
		 * pico-seconds, so the maximum allowed bits per pixel is
		 *   8 * max_bandwidth / (PICOS2KHZ(pixघड़ी) * 1000)
		 * Rearrange this calculation to aव्योम overflow and then ensure
		 * result is a valid क्रमmat.
		 */
		bpp = max_bandwidth / (1000 / 8)
			/ PICOS2KHZ(fb->panel->mode.pixघड़ी);
		bpp = roundकरोwn_घात_of_two(bpp);
		अगर (bpp > 32)
			bpp = 32;
	पूर्ण अन्यथा
		bpp = 32;
	fb->panel->bpp = bpp;

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	fb->panel->cntl |= CNTL_BEBO;
#पूर्ण_अगर
	fb->panel->width = -1;
	fb->panel->height = -1;

	अगर (of_property_पढ़ो_u32_array(endpoपूर्णांक,
			"arm,pl11x,tft-r0g0b0-pads",
			tft_r0b0g0, ARRAY_SIZE(tft_r0b0g0)) != 0)
		वापस -ENOENT;

	वापस clcdfb_of_init_tft_panel(fb, tft_r0b0g0[0],
					tft_r0b0g0[1],  tft_r0b0g0[2]);
पूर्ण

अटल पूर्णांक clcdfb_of_vram_setup(काष्ठा clcd_fb *fb)
अणु
	पूर्णांक err;
	काष्ठा device_node *memory;
	u64 size;

	err = clcdfb_of_init_display(fb);
	अगर (err)
		वापस err;

	memory = of_parse_phandle(fb->dev->dev.of_node, "memory-region", 0);
	अगर (!memory)
		वापस -ENODEV;

	fb->fb.screen_base = of_iomap(memory, 0);
	अगर (!fb->fb.screen_base)
		वापस -ENOMEM;

	fb->fb.fix.smem_start = of_translate_address(memory,
			of_get_address(memory, 0, &size, शून्य));
	fb->fb.fix.smem_len = size;

	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_of_vram_mmap(काष्ठा clcd_fb *fb, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ off, user_size, kernel_size;


	off = vma->vm_pgoff << PAGE_SHIFT;
	user_size = vma->vm_end - vma->vm_start;
	kernel_size = fb->fb.fix.smem_len;

	अगर (off >= kernel_size || user_size > (kernel_size - off))
		वापस -ENXIO;

	वापस remap_pfn_range(vma, vma->vm_start,
			__phys_to_pfn(fb->fb.fix.smem_start) + vma->vm_pgoff,
			user_size,
			pgprot_ग_लिखोcombine(vma->vm_page_prot));
पूर्ण

अटल व्योम clcdfb_of_vram_हटाओ(काष्ठा clcd_fb *fb)
अणु
	iounmap(fb->fb.screen_base);
पूर्ण

अटल पूर्णांक clcdfb_of_dma_setup(काष्ठा clcd_fb *fb)
अणु
	अचिन्हित दीर्घ framesize;
	dma_addr_t dma;
	पूर्णांक err;

	err = clcdfb_of_init_display(fb);
	अगर (err)
		वापस err;

	framesize = PAGE_ALIGN(fb->panel->mode.xres * fb->panel->mode.yres *
			fb->panel->bpp / 8);
	fb->fb.screen_base = dma_alloc_coherent(&fb->dev->dev, framesize,
			&dma, GFP_KERNEL);
	अगर (!fb->fb.screen_base)
		वापस -ENOMEM;

	fb->fb.fix.smem_start = dma;
	fb->fb.fix.smem_len = framesize;

	वापस 0;
पूर्ण

अटल पूर्णांक clcdfb_of_dma_mmap(काष्ठा clcd_fb *fb, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस dma_mmap_wc(&fb->dev->dev, vma, fb->fb.screen_base,
			   fb->fb.fix.smem_start, fb->fb.fix.smem_len);
पूर्ण

अटल व्योम clcdfb_of_dma_हटाओ(काष्ठा clcd_fb *fb)
अणु
	dma_मुक्त_coherent(&fb->dev->dev, fb->fb.fix.smem_len,
			fb->fb.screen_base, fb->fb.fix.smem_start);
पूर्ण

अटल काष्ठा clcd_board *clcdfb_of_get_board(काष्ठा amba_device *dev)
अणु
	काष्ठा clcd_board *board = devm_kzalloc(&dev->dev, माप(*board),
			GFP_KERNEL);
	काष्ठा device_node *node = dev->dev.of_node;

	अगर (!board)
		वापस शून्य;

	board->name = of_node_full_name(node);
	board->caps = CLCD_CAP_ALL;
	board->check = clcdfb_check;
	board->decode = clcdfb_decode;
	अगर (of_find_property(node, "memory-region", शून्य)) अणु
		board->setup = clcdfb_of_vram_setup;
		board->mmap = clcdfb_of_vram_mmap;
		board->हटाओ = clcdfb_of_vram_हटाओ;
	पूर्ण अन्यथा अणु
		board->setup = clcdfb_of_dma_setup;
		board->mmap = clcdfb_of_dma_mmap;
		board->हटाओ = clcdfb_of_dma_हटाओ;
	पूर्ण

	वापस board;
पूर्ण
#अन्यथा
अटल काष्ठा clcd_board *clcdfb_of_get_board(काष्ठा amba_device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक clcdfb_probe(काष्ठा amba_device *dev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा clcd_board *board = dev_get_platdata(&dev->dev);
	काष्ठा clcd_fb *fb;
	पूर्णांक ret;

	अगर (!board)
		board = clcdfb_of_get_board(dev);

	अगर (!board)
		वापस -EINVAL;

	ret = dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ out;

	ret = amba_request_regions(dev, शून्य);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "CLCD: unable to reserve regs region\n");
		जाओ out;
	पूर्ण

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb) अणु
		ret = -ENOMEM;
		जाओ मुक्त_region;
	पूर्ण

	fb->dev = dev;
	fb->board = board;

	dev_info(&fb->dev->dev, "PL%03x designer %02x rev%u at 0x%08llx\n",
		amba_part(dev), amba_manf(dev), amba_rev(dev),
		(अचिन्हित दीर्घ दीर्घ)dev->res.start);

	ret = fb->board->setup(fb);
	अगर (ret)
		जाओ मुक्त_fb;

	ret = clcdfb_रेजिस्टर(fb);
	अगर (ret == 0) अणु
		amba_set_drvdata(dev, fb);
		जाओ out;
	पूर्ण

	fb->board->हटाओ(fb);
 मुक्त_fb:
	kमुक्त(fb);
 मुक्त_region:
	amba_release_regions(dev);
 out:
	वापस ret;
पूर्ण

अटल व्योम clcdfb_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा clcd_fb *fb = amba_get_drvdata(dev);

	clcdfb_disable(fb);
	unरेजिस्टर_framebuffer(&fb->fb);
	अगर (fb->fb.cmap.len)
		fb_dealloc_cmap(&fb->fb.cmap);
	iounmap(fb->regs);
	clk_unprepare(fb->clk);
	clk_put(fb->clk);

	fb->board->हटाओ(fb);

	kमुक्त(fb);

	amba_release_regions(dev);
पूर्ण

अटल स्थिर काष्ठा amba_id clcdfb_id_table[] = अणु
	अणु
		.id	= 0x00041110,
		.mask	= 0x000ffffe,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, clcdfb_id_table);

अटल काष्ठा amba_driver clcd_driver = अणु
	.drv 		= अणु
		.name	= "clcd-pl11x",
	पूर्ण,
	.probe		= clcdfb_probe,
	.हटाओ		= clcdfb_हटाओ,
	.id_table	= clcdfb_id_table,
पूर्ण;

अटल पूर्णांक __init amba_clcdfb_init(व्योम)
अणु
	अगर (fb_get_options("ambafb", शून्य))
		वापस -ENODEV;

	वापस amba_driver_रेजिस्टर(&clcd_driver);
पूर्ण

module_init(amba_clcdfb_init);

अटल व्योम __निकास amba_clcdfb_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&clcd_driver);
पूर्ण

module_निकास(amba_clcdfb_निकास);

MODULE_DESCRIPTION("ARM PrimeCell PL110 CLCD core driver");
MODULE_LICENSE("GPL");
