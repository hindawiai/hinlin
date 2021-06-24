<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/vt8500lcdfb.c
 *
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 *
 * Based on skeletonfb.c and pxafb.c
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <video/of_display_timing.h>

#समावेश "vt8500lcdfb.h"
#समावेश "wmt_ge_rops.h"

#अगर_घोषित CONFIG_OF
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/memblock.h>
#पूर्ण_अगर


#घोषणा to_vt8500lcd_info(__info) container_of(__info, \
						काष्ठा vt8500lcd_info, fb)

अटल पूर्णांक vt8500lcd_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा vt8500lcd_info *fbi = to_vt8500lcd_info(info);
	पूर्णांक reg_bpp = 5; /* 16bpp */
	पूर्णांक i;
	अचिन्हित दीर्घ control0;

	अगर (!fbi)
		वापस -EINVAL;

	अगर (info->var.bits_per_pixel <= 8) अणु
		/* palettized */
		info->var.red.offset    = 0;
		info->var.red.length    = info->var.bits_per_pixel;
		info->var.red.msb_right = 0;

		info->var.green.offset  = 0;
		info->var.green.length  = info->var.bits_per_pixel;
		info->var.green.msb_right = 0;

		info->var.blue.offset   = 0;
		info->var.blue.length   = info->var.bits_per_pixel;
		info->var.blue.msb_right = 0;

		info->var.transp.offset = 0;
		info->var.transp.length = 0;
		info->var.transp.msb_right = 0;

		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		info->fix.line_length = info->var.xres_भव /
						(8/info->var.bits_per_pixel);
	पूर्ण अन्यथा अणु
		/* non-palettized */
		info->var.transp.offset = 0;
		info->var.transp.length = 0;
		info->var.transp.msb_right = 0;

		अगर (info->var.bits_per_pixel == 16) अणु
			/* RGB565 */
			info->var.red.offset = 11;
			info->var.red.length = 5;
			info->var.red.msb_right = 0;
			info->var.green.offset = 5;
			info->var.green.length = 6;
			info->var.green.msb_right = 0;
			info->var.blue.offset = 0;
			info->var.blue.length = 5;
			info->var.blue.msb_right = 0;
		पूर्ण अन्यथा अणु
			/* Equal depths per channel */
			info->var.red.offset = info->var.bits_per_pixel
							* 2 / 3;
			info->var.red.length = info->var.bits_per_pixel / 3;
			info->var.red.msb_right = 0;
			info->var.green.offset = info->var.bits_per_pixel / 3;
			info->var.green.length = info->var.bits_per_pixel / 3;
			info->var.green.msb_right = 0;
			info->var.blue.offset = 0;
			info->var.blue.length = info->var.bits_per_pixel / 3;
			info->var.blue.msb_right = 0;
		पूर्ण

		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.line_length = info->var.bits_per_pixel > 16 ?
					info->var.xres_भव << 2 :
					info->var.xres_भव << 1;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		अगर (bpp_values[i] == info->var.bits_per_pixel)
			reg_bpp = i;
	पूर्ण

	control0 = पढ़ोl(fbi->regbase) & ~0xf;
	ग_लिखोl(0, fbi->regbase);
	जबतक (पढ़ोl(fbi->regbase + 0x38) & 0x10)
		/* रुको */;
	ग_लिखोl((((info->var.hsync_len - 1) & 0x3f) << 26)
		| ((info->var.left_margin & 0xff) << 18)
		| (((info->var.xres - 1) & 0x3ff) << 8)
		| (info->var.right_margin & 0xff), fbi->regbase + 0x4);
	ग_लिखोl((((info->var.vsync_len - 1) & 0x3f) << 26)
		| ((info->var.upper_margin & 0xff) << 18)
		| (((info->var.yres - 1) & 0x3ff) << 8)
		| (info->var.lower_margin & 0xff), fbi->regbase + 0x8);
	ग_लिखोl((((info->var.yres - 1) & 0x400) << 2)
		| ((info->var.xres - 1) & 0x400), fbi->regbase + 0x10);
	ग_लिखोl(0x80000000, fbi->regbase + 0x20);
	ग_लिखोl(control0 | (reg_bpp << 1) | 0x100, fbi->regbase);

	वापस 0;
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक vt8500lcd_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info) अणु
	काष्ठा vt8500lcd_info *fbi = to_vt8500lcd_info(info);
	पूर्णांक ret = 1;
	अचिन्हित पूर्णांक val;
	अगर (regno >= 256)
		वापस -EINVAL;

	अगर (info->var.grayscale)
		red = green = blue =
			(19595 * red + 38470 * green + 7471 * blue) >> 16;

	चयन (fbi->fb.fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
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
		ग_लिखोw((red & 0xf800)
		      | ((green >> 5) & 0x7e0)
		      | ((blue >> 11) & 0x1f),
		       fbi->palette_cpu + माप(u16) * regno);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vt8500lcd_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	काष्ठा vt8500lcd_info *fbi = to_vt8500lcd_info(info);

	अगर (cmd == FBIO_WAITFORVSYNC) अणु
		/* Unmask End of Frame पूर्णांकerrupt */
		ग_लिखोl(0xffffffff ^ (1 << 3), fbi->regbase + 0x3c);
		ret = रुको_event_पूर्णांकerruptible_समयout(fbi->रुको,
			पढ़ोl(fbi->regbase + 0x38) & (1 << 3), HZ / 10);
		/* Mask back to reduce unwanted पूर्णांकerrupt traffic */
		ग_लिखोl(0xffffffff, fbi->regbase + 0x3c);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vt8500lcd_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	अचिन्हित pixlen = info->fix.line_length / info->var.xres_भव;
	अचिन्हित off = pixlen * var->xoffset
		      + info->fix.line_length * var->yoffset;
	काष्ठा vt8500lcd_info *fbi = to_vt8500lcd_info(info);

	ग_लिखोl((1 << 31)
	     | (((info->var.xres_भव - info->var.xres) * pixlen / 4) << 20)
	     | (off >> 2), fbi->regbase + 0x20);
	वापस 0;
पूर्ण

/*
 * vt8500lcd_blank():
 *	Blank the display by setting all palette values to zero.  Note,
 * 	True Color modes करो not really use the palette, so this will not
 *      blank the display in all modes.
 */
अटल पूर्णांक vt8500lcd_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	पूर्णांक i;

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    info->fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			क्रम (i = 0; i < 256; i++)
				vt8500lcd_setcolreg(i, 0, 0, 0, 0, info);
		fallthrough;
	हाल FB_BLANK_UNBLANK:
		अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    info->fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&info->cmap, info);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops vt8500lcd_ops = अणु
	.owner		= THIS_MODULE,
	.fb_set_par	= vt8500lcd_set_par,
	.fb_setcolreg	= vt8500lcd_setcolreg,
	.fb_fillrect	= wmt_ge_fillrect,
	.fb_copyarea	= wmt_ge_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_sync	= wmt_ge_sync,
	.fb_ioctl	= vt8500lcd_ioctl,
	.fb_pan_display	= vt8500lcd_pan_display,
	.fb_blank	= vt8500lcd_blank,
पूर्ण;

अटल irqवापस_t vt8500lcd_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vt8500lcd_info *fbi = dev_id;

	अगर (पढ़ोl(fbi->regbase + 0x38) & (1 << 3))
		wake_up_पूर्णांकerruptible(&fbi->रुको);

	ग_लिखोl(0xffffffff, fbi->regbase + 0x38);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vt8500lcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500lcd_info *fbi;
	काष्ठा resource *res;
	काष्ठा display_timings *disp_timing;
	व्योम *addr;
	पूर्णांक irq, ret;

	काष्ठा fb_videomode	of_mode;
	u32			bpp;
	dma_addr_t fb_mem_phys;
	अचिन्हित दीर्घ fb_mem_len;
	व्योम *fb_mem_virt;

	ret = -ENOMEM;
	fbi = शून्य;

	fbi = devm_kzalloc(&pdev->dev, माप(काष्ठा vt8500lcd_info)
			+ माप(u32) * 16, GFP_KERNEL);
	अगर (!fbi)
		वापस -ENOMEM;

	म_नकल(fbi->fb.fix.id, "VT8500 LCD");

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.var.nonstd	= 0;
	fbi->fb.var.activate	= FB_ACTIVATE_NOW;
	fbi->fb.var.height	= -1;
	fbi->fb.var.width	= -1;
	fbi->fb.var.vmode	= FB_VMODE_NONINTERLACED;

	fbi->fb.fbops		= &vt8500lcd_ops;
	fbi->fb.flags		= FBINFO_DEFAULT
				| FBINFO_HWACCEL_COPYAREA
				| FBINFO_HWACCEL_FILLRECT
				| FBINFO_HWACCEL_YPAN
				| FBINFO_VIRTFB
				| FBINFO_PARTIAL_PAN_OK;
	fbi->fb.node		= -1;

	addr = fbi;
	addr = addr + माप(काष्ठा vt8500lcd_info);
	fbi->fb.pseuकरो_palette	= addr;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no I/O memory resource defined\n");
		वापस -ENODEV;
	पूर्ण

	res = request_mem_region(res->start, resource_size(res), "vt8500lcd");
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to request I/O memory\n");
		वापस -EBUSY;
	पूर्ण

	fbi->regbase = ioremap(res->start, resource_size(res));
	अगर (fbi->regbase == शून्य) अणु
		dev_err(&pdev->dev, "failed to map I/O memory\n");
		ret = -EBUSY;
		जाओ failed_मुक्त_res;
	पूर्ण

	disp_timing = of_get_display_timings(pdev->dev.of_node);
	अगर (!disp_timing) अणु
		ret = -EINVAL;
		जाओ failed_मुक्त_io;
	पूर्ण

	ret = of_get_fb_videomode(pdev->dev.of_node, &of_mode,
							OF_USE_NATIVE_MODE);
	अगर (ret)
		जाओ failed_मुक्त_io;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "bits-per-pixel", &bpp);
	अगर (ret)
		जाओ failed_मुक्त_io;

	/* try allocating the framebuffer */
	fb_mem_len = of_mode.xres * of_mode.yres * 2 * (bpp / 8);
	fb_mem_virt = dma_alloc_coherent(&pdev->dev, fb_mem_len, &fb_mem_phys,
				GFP_KERNEL);
	अगर (!fb_mem_virt) अणु
		pr_err("%s: Failed to allocate framebuffer\n", __func__);
		ret = -ENOMEM;
		जाओ failed_मुक्त_io;
	पूर्ण

	fbi->fb.fix.smem_start	= fb_mem_phys;
	fbi->fb.fix.smem_len	= fb_mem_len;
	fbi->fb.screen_base	= fb_mem_virt;

	fbi->palette_size	= PAGE_ALIGN(512);
	fbi->palette_cpu	= dma_alloc_coherent(&pdev->dev,
						     fbi->palette_size,
						     &fbi->palette_phys,
						     GFP_KERNEL);
	अगर (fbi->palette_cpu == शून्य) अणु
		dev_err(&pdev->dev, "Failed to allocate palette buffer\n");
		ret = -ENOMEM;
		जाओ failed_मुक्त_io;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "no IRQ defined\n");
		ret = -ENODEV;
		जाओ failed_मुक्त_palette;
	पूर्ण

	ret = request_irq(irq, vt8500lcd_handle_irq, 0, "LCD", fbi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed: %d\n", ret);
		ret = -EBUSY;
		जाओ failed_मुक्त_palette;
	पूर्ण

	init_रुकोqueue_head(&fbi->रुको);

	अगर (fb_alloc_cmap(&fbi->fb.cmap, 256, 0) < 0) अणु
		dev_err(&pdev->dev, "Failed to allocate color map\n");
		ret = -ENOMEM;
		जाओ failed_मुक्त_irq;
	पूर्ण

	fb_videomode_to_var(&fbi->fb.var, &of_mode);

	fbi->fb.var.xres_भव	= of_mode.xres;
	fbi->fb.var.yres_भव	= of_mode.yres * 2;
	fbi->fb.var.bits_per_pixel	= bpp;

	ret = vt8500lcd_set_par(&fbi->fb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set parameters\n");
		जाओ failed_मुक्त_cmap;
	पूर्ण

	ग_लिखोl(fbi->fb.fix.smem_start >> 22, fbi->regbase + 0x1c);
	ग_लिखोl((fbi->palette_phys & 0xfffffe00) | 1, fbi->regbase + 0x18);

	platक्रमm_set_drvdata(pdev, fbi);

	ret = रेजिस्टर_framebuffer(&fbi->fb);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Failed to register framebuffer device: %d\n", ret);
		जाओ failed_मुक्त_cmap;
	पूर्ण

	/*
	 * Ok, now enable the LCD controller
	 */
	ग_लिखोl(पढ़ोl(fbi->regbase) | 1, fbi->regbase);

	वापस 0;

failed_मुक्त_cmap:
	अगर (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);
failed_मुक्त_irq:
	मुक्त_irq(irq, fbi);
failed_मुक्त_palette:
	dma_मुक्त_coherent(&pdev->dev, fbi->palette_size,
			  fbi->palette_cpu, fbi->palette_phys);
failed_मुक्त_io:
	iounmap(fbi->regbase);
failed_मुक्त_res:
	release_mem_region(res->start, resource_size(res));
	वापस ret;
पूर्ण

अटल पूर्णांक vt8500lcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500lcd_info *fbi = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res;
	पूर्णांक irq;

	unरेजिस्टर_framebuffer(&fbi->fb);

	ग_लिखोl(0, fbi->regbase);

	अगर (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	irq = platक्रमm_get_irq(pdev, 0);
	मुक्त_irq(irq, fbi);

	dma_मुक्त_coherent(&pdev->dev, fbi->palette_size,
			  fbi->palette_cpu, fbi->palette_phys);

	iounmap(fbi->regbase);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id via_dt_ids[] = अणु
	अणु .compatible = "via,vt8500-fb", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver vt8500lcd_driver = अणु
	.probe		= vt8500lcd_probe,
	.हटाओ		= vt8500lcd_हटाओ,
	.driver		= अणु
		.name	= "vt8500-lcd",
		.of_match_table = of_match_ptr(via_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vt8500lcd_driver);

MODULE_AUTHOR("Alexey Charkov <alchark@gmail.com>");
MODULE_DESCRIPTION("LCD controller driver for VIA VT8500");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, via_dt_ids);
