<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  WonderMedia WM8505 Frame Buffer device driver
 *
 *  Copyright (C) 2010 Ed Spiriकरोnov <eकरो.rus@gmail.com>
 *    Based on vt8500lcdfb.c
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fb.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <video/of_display_timing.h>

#समावेश "wm8505fb_regs.h"
#समावेश "wmt_ge_rops.h"

#घोषणा DRIVER_NAME "wm8505-fb"

#घोषणा to_wm8505fb_info(__info) container_of(__info, \
						काष्ठा wm8505fb_info, fb)
काष्ठा wm8505fb_info अणु
	काष्ठा fb_info		fb;
	व्योम __iomem		*regbase;
	अचिन्हित पूर्णांक		contrast;
पूर्ण;


अटल पूर्णांक wm8505fb_init_hw(काष्ठा fb_info *info)
अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	पूर्णांक i;

	/* I know the purpose only of few रेजिस्टरs, so clear unknown */
	क्रम (i = 0; i < 0x200; i += 4)
		ग_लिखोl(0, fbi->regbase + i);

	/* Set frame buffer address */
	ग_लिखोl(fbi->fb.fix.smem_start, fbi->regbase + WMT_GOVR_FBADDR);
	ग_लिखोl(fbi->fb.fix.smem_start, fbi->regbase + WMT_GOVR_FBADDR1);

	/*
	 * Set in-memory picture क्रमmat to RGB
	 * 0x31C sets the correct color mode (RGB565) क्रम WM8650
	 * Bit 8+9 (0x300) are ignored on WM8505 as reserved
	 */
	ग_लिखोl(0x31c,		       fbi->regbase + WMT_GOVR_COLORSPACE);
	ग_लिखोl(1,		       fbi->regbase + WMT_GOVR_COLORSPACE1);

	/* Virtual buffer size */
	ग_लिखोl(info->var.xres,	       fbi->regbase + WMT_GOVR_XRES);
	ग_लिखोl(info->var.xres_भव, fbi->regbase + WMT_GOVR_XRES_VIRTUAL);

	/* black magic ;) */
	ग_लिखोl(0xf,		       fbi->regbase + WMT_GOVR_FHI);
	ग_लिखोl(4,		       fbi->regbase + WMT_GOVR_DVO_SET);
	ग_लिखोl(1,		       fbi->regbase + WMT_GOVR_MIF_ENABLE);
	ग_लिखोl(1,		       fbi->regbase + WMT_GOVR_REG_UPDATE);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8505fb_set_timing(काष्ठा fb_info *info)
अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	पूर्णांक h_start = info->var.left_margin;
	पूर्णांक h_end = h_start + info->var.xres;
	पूर्णांक h_all = h_end + info->var.right_margin;
	पूर्णांक h_sync = info->var.hsync_len;

	पूर्णांक v_start = info->var.upper_margin;
	पूर्णांक v_end = v_start + info->var.yres;
	पूर्णांक v_all = v_end + info->var.lower_margin;
	पूर्णांक v_sync = info->var.vsync_len;

	ग_लिखोl(0, fbi->regbase + WMT_GOVR_TG);

	ग_लिखोl(h_start, fbi->regbase + WMT_GOVR_TIMING_H_START);
	ग_लिखोl(h_end,   fbi->regbase + WMT_GOVR_TIMING_H_END);
	ग_लिखोl(h_all,   fbi->regbase + WMT_GOVR_TIMING_H_ALL);
	ग_लिखोl(h_sync,  fbi->regbase + WMT_GOVR_TIMING_H_SYNC);

	ग_लिखोl(v_start, fbi->regbase + WMT_GOVR_TIMING_V_START);
	ग_लिखोl(v_end,   fbi->regbase + WMT_GOVR_TIMING_V_END);
	ग_लिखोl(v_all,   fbi->regbase + WMT_GOVR_TIMING_V_ALL);
	ग_लिखोl(v_sync,  fbi->regbase + WMT_GOVR_TIMING_V_SYNC);

	ग_लिखोl(1, fbi->regbase + WMT_GOVR_TG);

	वापस 0;
पूर्ण


अटल पूर्णांक wm8505fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	अगर (!fbi)
		वापस -EINVAL;

	अगर (info->var.bits_per_pixel == 32) अणु
		info->var.red.offset = 16;
		info->var.red.length = 8;
		info->var.red.msb_right = 0;
		info->var.green.offset = 8;
		info->var.green.length = 8;
		info->var.green.msb_right = 0;
		info->var.blue.offset = 0;
		info->var.blue.length = 8;
		info->var.blue.msb_right = 0;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.line_length = info->var.xres_भव << 2;
	पूर्ण अन्यथा अगर (info->var.bits_per_pixel == 16) अणु
		info->var.red.offset = 11;
		info->var.red.length = 5;
		info->var.red.msb_right = 0;
		info->var.green.offset = 5;
		info->var.green.length = 6;
		info->var.green.msb_right = 0;
		info->var.blue.offset = 0;
		info->var.blue.length = 5;
		info->var.blue.msb_right = 0;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.line_length = info->var.xres_भव << 1;
	पूर्ण

	wm8505fb_set_timing(info);

	ग_लिखोl(fbi->contrast<<16 | fbi->contrast<<8 | fbi->contrast,
		fbi->regbase + WMT_GOVR_CONTRAST);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार contrast_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	वापस प्र_लिखो(buf, "%u\n", fbi->contrast);
पूर्ण

अटल sमाप_प्रकार contrast_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);
	अचिन्हित दीर्घ पंचांगp;

	अगर (kम_से_अदीर्घ(buf, 10, &पंचांगp) || (पंचांगp > 0xff))
		वापस -EINVAL;
	fbi->contrast = पंचांगp;

	wm8505fb_set_par(info);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(contrast);

अटल काष्ठा attribute *wm8505fb_attrs[] = अणु
	&dev_attr_contrast.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wm8505fb);

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक wm8505fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info) अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);
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
			u32 *pal = info->pseuकरो_palette;

			val  = chan_to_field(red, &fbi->fb.var.red);
			val |= chan_to_field(green, &fbi->fb.var.green);
			val |= chan_to_field(blue, &fbi->fb.var.blue);

			pal[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wm8505fb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	ग_लिखोl(var->xoffset, fbi->regbase + WMT_GOVR_XPAN);
	ग_लिखोl(var->yoffset, fbi->regbase + WMT_GOVR_YPAN);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8505fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा wm8505fb_info *fbi = to_wm8505fb_info(info);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		wm8505fb_set_timing(info);
		अवरोध;
	शेष:
		ग_लिखोl(0,  fbi->regbase + WMT_GOVR_TIMING_V_SYNC);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops wm8505fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_set_par	= wm8505fb_set_par,
	.fb_setcolreg	= wm8505fb_setcolreg,
	.fb_fillrect	= wmt_ge_fillrect,
	.fb_copyarea	= wmt_ge_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_sync	= wmt_ge_sync,
	.fb_pan_display	= wm8505fb_pan_display,
	.fb_blank	= wm8505fb_blank,
पूर्ण;

अटल पूर्णांक wm8505fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8505fb_info	*fbi;
	काष्ठा resource	*res;
	काष्ठा display_timings *disp_timing;
	व्योम			*addr;
	पूर्णांक ret;

	काष्ठा fb_videomode	mode;
	u32			bpp;
	dma_addr_t fb_mem_phys;
	अचिन्हित दीर्घ fb_mem_len;
	व्योम *fb_mem_virt;

	fbi = devm_kzalloc(&pdev->dev, माप(काष्ठा wm8505fb_info) +
			माप(u32) * 16, GFP_KERNEL);
	अगर (!fbi)
		वापस -ENOMEM;

	म_नकल(fbi->fb.fix.id, DRIVER_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.xpanstep	= 1;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.fbops		= &wm8505fb_ops;
	fbi->fb.flags		= FBINFO_DEFAULT
				| FBINFO_HWACCEL_COPYAREA
				| FBINFO_HWACCEL_FILLRECT
				| FBINFO_HWACCEL_XPAN
				| FBINFO_HWACCEL_YPAN
				| FBINFO_VIRTFB
				| FBINFO_PARTIAL_PAN_OK;
	fbi->fb.node		= -1;

	addr = fbi;
	addr = addr + माप(काष्ठा wm8505fb_info);
	fbi->fb.pseuकरो_palette	= addr;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fbi->regbase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fbi->regbase))
		वापस PTR_ERR(fbi->regbase);

	disp_timing = of_get_display_timings(pdev->dev.of_node);
	अगर (!disp_timing)
		वापस -EINVAL;

	ret = of_get_fb_videomode(pdev->dev.of_node, &mode, OF_USE_NATIVE_MODE);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "bits-per-pixel", &bpp);
	अगर (ret)
		वापस ret;

	fb_videomode_to_var(&fbi->fb.var, &mode);

	fbi->fb.var.nonstd		= 0;
	fbi->fb.var.activate		= FB_ACTIVATE_NOW;

	fbi->fb.var.height		= -1;
	fbi->fb.var.width		= -1;

	/* try allocating the framebuffer */
	fb_mem_len = mode.xres * mode.yres * 2 * (bpp / 8);
	fb_mem_virt = dmam_alloc_coherent(&pdev->dev, fb_mem_len, &fb_mem_phys,
				GFP_KERNEL);
	अगर (!fb_mem_virt) अणु
		pr_err("%s: Failed to allocate framebuffer\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	fbi->fb.var.xres_भव	= mode.xres;
	fbi->fb.var.yres_भव	= mode.yres * 2;
	fbi->fb.var.bits_per_pixel	= bpp;

	fbi->fb.fix.smem_start		= fb_mem_phys;
	fbi->fb.fix.smem_len		= fb_mem_len;
	fbi->fb.screen_buffer		= fb_mem_virt;
	fbi->fb.screen_size		= fb_mem_len;

	fbi->contrast = 0x10;
	ret = wm8505fb_set_par(&fbi->fb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set parameters\n");
		वापस ret;
	पूर्ण

	अगर (fb_alloc_cmap(&fbi->fb.cmap, 256, 0) < 0) अणु
		dev_err(&pdev->dev, "Failed to allocate color map\n");
		वापस -ENOMEM;
	पूर्ण

	wm8505fb_init_hw(&fbi->fb);

	platक्रमm_set_drvdata(pdev, fbi);

	ret = रेजिस्टर_framebuffer(&fbi->fb);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Failed to register framebuffer device: %d\n", ret);
		अगर (fbi->fb.cmap.len)
			fb_dealloc_cmap(&fbi->fb.cmap);
		वापस ret;
	पूर्ण

	fb_info(&fbi->fb, "%s frame buffer at 0x%lx-0x%lx\n",
		fbi->fb.fix.id, fbi->fb.fix.smem_start,
		fbi->fb.fix.smem_start + fbi->fb.fix.smem_len - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8505fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8505fb_info *fbi = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(&fbi->fb);

	ग_लिखोl(0, fbi->regbase);

	अगर (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wmt_dt_ids[] = अणु
	अणु .compatible = "wm,wm8505-fb", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver wm8505fb_driver = अणु
	.probe		= wm8505fb_probe,
	.हटाओ		= wm8505fb_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = wmt_dt_ids,
		.dev_groups	= wm8505fb_groups,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8505fb_driver);

MODULE_AUTHOR("Ed Spiridonov <edo.rus@gmail.com>");
MODULE_DESCRIPTION("Framebuffer driver for WMT WM8505");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, wmt_dt_ids);
