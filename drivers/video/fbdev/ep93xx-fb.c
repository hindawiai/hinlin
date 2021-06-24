<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/ep93xx-fb.c
 *
 * Framebuffer support क्रम the EP93xx series.
 *
 * Copyright (C) 2007 Bluewater Systems Ltd
 * Author: Ryan Mallon
 *
 * Copyright (c) 2009 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the Cirrus Logic ep93xxfb driver, and various other ep93xxfb
 * drivers.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>

#समावेश <linux/platक्रमm_data/video-ep93xx.h>

/* Vertical Frame Timing Registers */
#घोषणा EP93XXFB_VLINES_TOTAL			0x0000	/* SW locked */
#घोषणा EP93XXFB_VSYNC				0x0004	/* SW locked */
#घोषणा EP93XXFB_VACTIVE			0x0008	/* SW locked */
#घोषणा EP93XXFB_VBLANK				0x0228	/* SW locked */
#घोषणा EP93XXFB_VCLK				0x000c	/* SW locked */

/* Horizontal Frame Timing Registers */
#घोषणा EP93XXFB_HCLKS_TOTAL			0x0010	/* SW locked */
#घोषणा EP93XXFB_HSYNC				0x0014	/* SW locked */
#घोषणा EP93XXFB_HACTIVE			0x0018	/* SW locked */
#घोषणा EP93XXFB_HBLANK				0x022c	/* SW locked */
#घोषणा EP93XXFB_HCLK				0x001c	/* SW locked */

/* Frame Buffer Memory Configuration Registers */
#घोषणा EP93XXFB_SCREEN_PAGE			0x0028
#घोषणा EP93XXFB_SCREEN_HPAGE			0x002c
#घोषणा EP93XXFB_SCREEN_LINES			0x0030
#घोषणा EP93XXFB_LINE_LENGTH			0x0034
#घोषणा EP93XXFB_VLINE_STEP			0x0038
#घोषणा EP93XXFB_LINE_CARRY			0x003c	/* SW locked */
#घोषणा EP93XXFB_EOL_OFFSET			0x0230

/* Other Video Registers */
#घोषणा EP93XXFB_BRIGHTNESS			0x0020
#घोषणा EP93XXFB_ATTRIBS			0x0024	/* SW locked */
#घोषणा EP93XXFB_SWLOCK				0x007c	/* SW locked */
#घोषणा EP93XXFB_AC_RATE			0x0214
#घोषणा EP93XXFB_FIFO_LEVEL			0x0234
#घोषणा EP93XXFB_PIXELMODE			0x0054
#घोषणा EP93XXFB_PIXELMODE_32BPP		(0x7 << 0)
#घोषणा EP93XXFB_PIXELMODE_24BPP		(0x6 << 0)
#घोषणा EP93XXFB_PIXELMODE_16BPP		(0x4 << 0)
#घोषणा EP93XXFB_PIXELMODE_8BPP			(0x2 << 0)
#घोषणा EP93XXFB_PIXELMODE_SHIFT_1P_24B		(0x0 << 3)
#घोषणा EP93XXFB_PIXELMODE_SHIFT_1P_18B		(0x1 << 3)
#घोषणा EP93XXFB_PIXELMODE_COLOR_LUT		(0x0 << 10)
#घोषणा EP93XXFB_PIXELMODE_COLOR_888		(0x4 << 10)
#घोषणा EP93XXFB_PIXELMODE_COLOR_555		(0x5 << 10)
#घोषणा EP93XXFB_PARL_IF_OUT			0x0058
#घोषणा EP93XXFB_PARL_IF_IN			0x005c

/* Blink Control Registers */
#घोषणा EP93XXFB_BLINK_RATE			0x0040
#घोषणा EP93XXFB_BLINK_MASK			0x0044
#घोषणा EP93XXFB_BLINK_PATTRN			0x0048
#घोषणा EP93XXFB_PATTRN_MASK			0x004c
#घोषणा EP93XXFB_BKGRND_OFFSET			0x0050

/* Hardware Cursor Registers */
#घोषणा EP93XXFB_CURSOR_ADR_START		0x0060
#घोषणा EP93XXFB_CURSOR_ADR_RESET		0x0064
#घोषणा EP93XXFB_CURSOR_SIZE			0x0068
#घोषणा EP93XXFB_CURSOR_COLOR1			0x006c
#घोषणा EP93XXFB_CURSOR_COLOR2			0x0070
#घोषणा EP93XXFB_CURSOR_BLINK_COLOR1		0x021c
#घोषणा EP93XXFB_CURSOR_BLINK_COLOR2		0x0220
#घोषणा EP93XXFB_CURSOR_XY_LOC			0x0074
#घोषणा EP93XXFB_CURSOR_DSCAN_HY_LOC		0x0078
#घोषणा EP93XXFB_CURSOR_BLINK_RATE_CTRL		0x0224

/* LUT Registers */
#घोषणा EP93XXFB_GRY_SCL_LUTR			0x0080
#घोषणा EP93XXFB_GRY_SCL_LUTG			0x0280
#घोषणा EP93XXFB_GRY_SCL_LUTB			0x0300
#घोषणा EP93XXFB_LUT_SW_CONTROL			0x0218
#घोषणा EP93XXFB_LUT_SW_CONTROL_SWTCH		(1 << 0)
#घोषणा EP93XXFB_LUT_SW_CONTROL_SSTAT		(1 << 1)
#घोषणा EP93XXFB_COLOR_LUT			0x0400

/* Video Signature Registers */
#घोषणा EP93XXFB_VID_SIG_RSLT_VAL		0x0200
#घोषणा EP93XXFB_VID_SIG_CTRL			0x0204
#घोषणा EP93XXFB_VSIG				0x0208
#घोषणा EP93XXFB_HSIG				0x020c
#घोषणा EP93XXFB_SIG_CLR_STR			0x0210

/* Minimum / Maximum resolutions supported */
#घोषणा EP93XXFB_MIN_XRES			64
#घोषणा EP93XXFB_MIN_YRES			64
#घोषणा EP93XXFB_MAX_XRES			1024
#घोषणा EP93XXFB_MAX_YRES			768

काष्ठा ep93xx_fbi अणु
	काष्ठा ep93xxfb_mach_info	*mach_info;
	काष्ठा clk			*clk;
	काष्ठा resource			*res;
	व्योम __iomem			*mmio_base;
	अचिन्हित पूर्णांक			pseuकरो_palette[256];
पूर्ण;

अटल पूर्णांक check_screenpage_bug = 1;
module_param(check_screenpage_bug, पूर्णांक, 0644);
MODULE_PARM_DESC(check_screenpage_bug,
		 "Check for bit 27 screen page bug. Default = 1");

अटल अंतरभूत अचिन्हित पूर्णांक ep93xxfb_पढ़ोl(काष्ठा ep93xx_fbi *fbi,
					  अचिन्हित पूर्णांक off)
अणु
	वापस __raw_पढ़ोl(fbi->mmio_base + off);
पूर्ण

अटल अंतरभूत व्योम ep93xxfb_ग_लिखोl(काष्ठा ep93xx_fbi *fbi,
				   अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक off)
अणु
	__raw_ग_लिखोl(val, fbi->mmio_base + off);
पूर्ण

/*
 * Write to one of the locked raster रेजिस्टरs.
 */
अटल अंतरभूत व्योम ep93xxfb_out_locked(काष्ठा ep93xx_fbi *fbi,
				       अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक reg)
अणु
	/*
	 * We करोn't need a lock or delay here since the raster रेजिस्टर
	 * block will reमुख्य unlocked until the next access.
	 */
	ep93xxfb_ग_लिखोl(fbi, 0xaa, EP93XXFB_SWLOCK);
	ep93xxfb_ग_लिखोl(fbi, val, reg);
पूर्ण

अटल व्योम ep93xxfb_set_video_attribs(काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;
	अचिन्हित पूर्णांक attribs;

	attribs = EP93XXFB_ENABLE;
	attribs |= fbi->mach_info->flags;
	ep93xxfb_out_locked(fbi, attribs, EP93XXFB_ATTRIBS);
पूर्ण

अटल पूर्णांक ep93xxfb_set_pixelmode(काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;
	अचिन्हित पूर्णांक val;

	info->var.transp.offset = 0;
	info->var.transp.length = 0;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		val = EP93XXFB_PIXELMODE_8BPP | EP93XXFB_PIXELMODE_COLOR_LUT |
			EP93XXFB_PIXELMODE_SHIFT_1P_18B;

		info->var.red.offset	= 0;
		info->var.red.length	= 8;
		info->var.green.offset	= 0;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_PSEUDOCOLOR;
		अवरोध;

	हाल 16:
		val = EP93XXFB_PIXELMODE_16BPP | EP93XXFB_PIXELMODE_COLOR_555 |
			EP93XXFB_PIXELMODE_SHIFT_1P_18B;

		info->var.red.offset	= 11;
		info->var.red.length	= 5;
		info->var.green.offset	= 5;
		info->var.green.length	= 6;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 5;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		अवरोध;

	हाल 24:
		val = EP93XXFB_PIXELMODE_24BPP | EP93XXFB_PIXELMODE_COLOR_888 |
			EP93XXFB_PIXELMODE_SHIFT_1P_24B;

		info->var.red.offset	= 16;
		info->var.red.length	= 8;
		info->var.green.offset	= 8;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		अवरोध;

	हाल 32:
		val = EP93XXFB_PIXELMODE_32BPP | EP93XXFB_PIXELMODE_COLOR_888 |
			EP93XXFB_PIXELMODE_SHIFT_1P_24B;

		info->var.red.offset	= 16;
		info->var.red.length	= 8;
		info->var.green.offset	= 8;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ep93xxfb_ग_लिखोl(fbi, val, EP93XXFB_PIXELMODE);
	वापस 0;
पूर्ण

अटल व्योम ep93xxfb_set_timing(काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;
	अचिन्हित पूर्णांक vlines_total, hclks_total, start, stop;

	vlines_total = info->var.yres + info->var.upper_margin +
		info->var.lower_margin + info->var.vsync_len - 1;

	hclks_total = info->var.xres + info->var.left_margin +
		info->var.right_margin + info->var.hsync_len - 1;

	ep93xxfb_out_locked(fbi, vlines_total, EP93XXFB_VLINES_TOTAL);
	ep93xxfb_out_locked(fbi, hclks_total, EP93XXFB_HCLKS_TOTAL);

	start = vlines_total;
	stop = vlines_total - info->var.vsync_len;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_VSYNC);

	start = vlines_total - info->var.vsync_len - info->var.upper_margin;
	stop = info->var.lower_margin - 1;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_VBLANK);
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_VACTIVE);

	start = vlines_total;
	stop = vlines_total + 1;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_VCLK);

	start = hclks_total;
	stop = hclks_total - info->var.hsync_len;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_HSYNC);

	start = hclks_total - info->var.hsync_len - info->var.left_margin;
	stop = info->var.right_margin - 1;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_HBLANK);
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_HACTIVE);

	start = hclks_total;
	stop = hclks_total;
	ep93xxfb_out_locked(fbi, start | (stop << 16), EP93XXFB_HCLK);

	ep93xxfb_out_locked(fbi, 0x0, EP93XXFB_LINE_CARRY);
पूर्ण

अटल पूर्णांक ep93xxfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;

	clk_set_rate(fbi->clk, 1000 * PICOS2KHZ(info->var.pixघड़ी));

	ep93xxfb_set_timing(info);

	info->fix.line_length = info->var.xres_भव *
		info->var.bits_per_pixel / 8;

	ep93xxfb_ग_लिखोl(fbi, info->fix.smem_start, EP93XXFB_SCREEN_PAGE);
	ep93xxfb_ग_लिखोl(fbi, info->var.yres - 1, EP93XXFB_SCREEN_LINES);
	ep93xxfb_ग_लिखोl(fbi, ((info->var.xres * info->var.bits_per_pixel)
			      / 32) - 1, EP93XXFB_LINE_LENGTH);
	ep93xxfb_ग_लिखोl(fbi, info->fix.line_length / 4, EP93XXFB_VLINE_STEP);
	ep93xxfb_set_video_attribs(info);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xxfb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	पूर्णांक err;

	err = ep93xxfb_set_pixelmode(info);
	अगर (err)
		वापस err;

	var->xres = max_t(अचिन्हित पूर्णांक, var->xres, EP93XXFB_MIN_XRES);
	var->xres = min_t(अचिन्हित पूर्णांक, var->xres, EP93XXFB_MAX_XRES);
	var->xres_भव = max(var->xres_भव, var->xres);

	var->yres = max_t(अचिन्हित पूर्णांक, var->yres, EP93XXFB_MIN_YRES);
	var->yres = min_t(अचिन्हित पूर्णांक, var->yres, EP93XXFB_MAX_YRES);
	var->yres_भव = max(var->yres_भव, var->yres);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xxfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक offset = vma->vm_pgoff << PAGE_SHIFT;

	अगर (offset < info->fix.smem_len) अणु
		वापस dma_mmap_wc(info->dev, vma, info->screen_base,
				   info->fix.smem_start, info->fix.smem_len);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ep93xxfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;
	अचिन्हित पूर्णांक attribs = ep93xxfb_पढ़ोl(fbi, EP93XXFB_ATTRIBS);

	अगर (blank_mode) अणु
		अगर (fbi->mach_info->blank)
			fbi->mach_info->blank(blank_mode, info);
		ep93xxfb_out_locked(fbi, attribs & ~EP93XXFB_ENABLE,
				    EP93XXFB_ATTRIBS);
		clk_disable(fbi->clk);
	पूर्ण अन्यथा अणु
		clk_enable(fbi->clk);
		ep93xxfb_out_locked(fbi, attribs | EP93XXFB_ENABLE,
				    EP93XXFB_ATTRIBS);
		अगर (fbi->mach_info->blank)
			fbi->mach_info->blank(blank_mode, info);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ep93xxfb_convert_color(पूर्णांक val, पूर्णांक width)
अणु
	वापस ((val << width) + 0x7fff - val) >> 16;
पूर्ण

अटल पूर्णांक ep93xxfb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			      अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			      अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा ep93xx_fbi *fbi = info->par;
	अचिन्हित पूर्णांक *pal = info->pseuकरो_palette;
	अचिन्हित पूर्णांक ctrl, i, rgb, lut_current, lut_stat;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno > 255)
			वापस 1;
		rgb = ((red & 0xff00) << 8) | (green & 0xff00) |
			((blue & 0xff00) >> 8);

		pal[regno] = rgb;
		ep93xxfb_ग_लिखोl(fbi, rgb, (EP93XXFB_COLOR_LUT + (regno << 2)));
		ctrl = ep93xxfb_पढ़ोl(fbi, EP93XXFB_LUT_SW_CONTROL);
		lut_stat = !!(ctrl & EP93XXFB_LUT_SW_CONTROL_SSTAT);
		lut_current = !!(ctrl & EP93XXFB_LUT_SW_CONTROL_SWTCH);

		अगर (lut_stat == lut_current) अणु
			क्रम (i = 0; i < 256; i++) अणु
				ep93xxfb_ग_लिखोl(fbi, pal[i],
					EP93XXFB_COLOR_LUT + (i << 2));
			पूर्ण

			ep93xxfb_ग_लिखोl(fbi,
					ctrl ^ EP93XXFB_LUT_SW_CONTROL_SWTCH,
					EP93XXFB_LUT_SW_CONTROL);
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno > 16)
			वापस 1;

		red = ep93xxfb_convert_color(red, info->var.red.length);
		green = ep93xxfb_convert_color(green, info->var.green.length);
		blue = ep93xxfb_convert_color(blue, info->var.blue.length);
		transp = ep93xxfb_convert_color(transp,
						info->var.transp.length);

		pal[regno] = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);
		अवरोध;

	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops ep93xxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= ep93xxfb_check_var,
	.fb_set_par	= ep93xxfb_set_par,
	.fb_blank	= ep93xxfb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_setcolreg	= ep93xxfb_setcolreg,
	.fb_mmap	= ep93xxfb_mmap,
पूर्ण;

अटल पूर्णांक ep93xxfb_alloc_videomem(काष्ठा fb_info *info)
अणु
	अक्षर __iomem *virt_addr;
	dma_addr_t phys_addr;
	अचिन्हित पूर्णांक fb_size;

	/* Maximum 16bpp -> used memory is maximum x*y*2 bytes */
	fb_size = EP93XXFB_MAX_XRES * EP93XXFB_MAX_YRES * 2;

	virt_addr = dma_alloc_wc(info->dev, fb_size, &phys_addr, GFP_KERNEL);
	अगर (!virt_addr)
		वापस -ENOMEM;

	/*
	 * There is a bug in the ep93xx framebuffer which causes problems
	 * अगर bit 27 of the physical address is set.
	 * See: https://marc.info/?l=linux-arm-kernel&m=110061245502000&w=2
	 * There करोes not seem to be any official errata क्रम this, but I
	 * have confirmed the problem exists on my hardware (ep9315) at
	 * least.
	 */
	अगर (check_screenpage_bug && phys_addr & (1 << 27)) अणु
		dev_err(info->dev, "ep93xx framebuffer bug. phys addr (0x%x) "
			"has bit 27 set: cannot init framebuffer\n",
			phys_addr);

		dma_मुक्त_coherent(info->dev, fb_size, virt_addr, phys_addr);
		वापस -ENOMEM;
	पूर्ण

	info->fix.smem_start = phys_addr;
	info->fix.smem_len = fb_size;
	info->screen_base = virt_addr;

	वापस 0;
पूर्ण

अटल व्योम ep93xxfb_dealloc_videomem(काष्ठा fb_info *info)
अणु
	अगर (info->screen_base)
		dma_मुक्त_coherent(info->dev, info->fix.smem_len,
				  info->screen_base, info->fix.smem_start);
पूर्ण

अटल पूर्णांक ep93xxfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xxfb_mach_info *mach_info = dev_get_platdata(&pdev->dev);
	काष्ठा fb_info *info;
	काष्ठा ep93xx_fbi *fbi;
	काष्ठा resource *res;
	अक्षर *video_mode;
	पूर्णांक err;

	अगर (!mach_info)
		वापस -EINVAL;

	info = framebuffer_alloc(माप(काष्ठा ep93xx_fbi), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, info);
	fbi = info->par;
	fbi->mach_info = mach_info;

	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err)
		जाओ failed_cmap;

	err = ep93xxfb_alloc_videomem(info);
	अगर (err)
		जाओ failed_videomem;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		err = -ENXIO;
		जाओ failed_resource;
	पूर्ण

	/*
	 * FIXME - We करोn't करो a request_mem_region here because we are
	 * sharing the रेजिस्टर space with the backlight driver (see
	 * drivers/video/backlight/ep93xx_bl.c) and करोing so will cause
	 * the second loaded driver to वापस -EBUSY.
	 *
	 * NOTE: No locking is required; the backlight करोes not touch
	 * any of the framebuffer रेजिस्टरs.
	 */
	fbi->res = res;
	fbi->mmio_base = devm_ioremap(&pdev->dev, res->start,
				      resource_size(res));
	अगर (!fbi->mmio_base) अणु
		err = -ENXIO;
		जाओ failed_resource;
	पूर्ण

	म_नकल(info->fix.id, pdev->name);
	info->fbops		= &ep93xxfb_ops;
	info->fix.type		= FB_TYPE_PACKED_PIXELS;
	info->fix.accel		= FB_ACCEL_NONE;
	info->var.activate	= FB_ACTIVATE_NOW;
	info->var.vmode		= FB_VMODE_NONINTERLACED;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;
	info->state		= FBINFO_STATE_RUNNING;
	info->pseuकरो_palette	= &fbi->pseuकरो_palette;

	fb_get_options("ep93xx-fb", &video_mode);
	err = fb_find_mode(&info->var, info, video_mode,
			   शून्य, 0, शून्य, 16);
	अगर (err == 0) अणु
		dev_err(info->dev, "No suitable video mode found\n");
		err = -EINVAL;
		जाओ failed_resource;
	पूर्ण

	अगर (mach_info->setup) अणु
		err = mach_info->setup(pdev);
		अगर (err)
			जाओ failed_resource;
	पूर्ण

	err = ep93xxfb_check_var(&info->var, info);
	अगर (err)
		जाओ failed_check;

	fbi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(fbi->clk)) अणु
		err = PTR_ERR(fbi->clk);
		fbi->clk = शून्य;
		जाओ failed_check;
	पूर्ण

	ep93xxfb_set_par(info);
	clk_enable(fbi->clk);

	err = रेजिस्टर_framebuffer(info);
	अगर (err)
		जाओ failed_check;

	dev_info(info->dev, "registered. Mode = %dx%d-%d\n",
		 info->var.xres, info->var.yres, info->var.bits_per_pixel);
	वापस 0;

failed_check:
	अगर (fbi->mach_info->tearकरोwn)
		fbi->mach_info->tearकरोwn(pdev);
failed_resource:
	ep93xxfb_dealloc_videomem(info);
failed_videomem:
	fb_dealloc_cmap(&info->cmap);
failed_cmap:
	kमुक्त(info);

	वापस err;
पूर्ण

अटल पूर्णांक ep93xxfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा ep93xx_fbi *fbi = info->par;

	unरेजिस्टर_framebuffer(info);
	clk_disable(fbi->clk);
	ep93xxfb_dealloc_videomem(info);
	fb_dealloc_cmap(&info->cmap);

	अगर (fbi->mach_info->tearकरोwn)
		fbi->mach_info->tearकरोwn(pdev);

	kमुक्त(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xxfb_driver = अणु
	.probe		= ep93xxfb_probe,
	.हटाओ		= ep93xxfb_हटाओ,
	.driver = अणु
		.name	= "ep93xx-fb",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ep93xxfb_driver);

MODULE_DESCRIPTION("EP93XX Framebuffer Driver");
MODULE_ALIAS("platform:ep93xx-fb");
MODULE_AUTHOR("Ryan Mallon, "
	      "H Hartley Sweeten <hsweeten@visionengravers.com");
MODULE_LICENSE("GPL");
