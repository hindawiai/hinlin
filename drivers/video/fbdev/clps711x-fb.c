<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cirrus Logic CLPS711X FB driver
 *
 * Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 * Based on driver by Russell King <rmk@arm.linux.org.uk>
 */

#समावेश <linux/clk.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/clps711x.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <video/of_display_timing.h>

#घोषणा CLPS711X_FB_NAME	"clps711x-fb"
#घोषणा CLPS711X_FB_BPP_MAX	(4)

/* Registers relative to LCDCON */
#घोषणा CLPS711X_LCDCON		(0x0000)
# define LCDCON_GSEN		BIT(30)
# define LCDCON_GSMD		BIT(31)
#घोषणा CLPS711X_PALLSW		(0x0280)
#घोषणा CLPS711X_PALMSW		(0x02c0)
#घोषणा CLPS711X_FBADDR		(0x0d40)

काष्ठा clps711x_fb_info अणु
	काष्ठा clk		*clk;
	व्योम __iomem		*base;
	काष्ठा regmap		*syscon;
	resource_माप_प्रकार		buffsize;
	काष्ठा fb_videomode	mode;
	काष्ठा regulator	*lcd_pwr;
	u32			ac_prescale;
	bool			cmap_invert;
पूर्ण;

अटल पूर्णांक clps711x_fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
				 u_पूर्णांक blue, u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा clps711x_fb_info *cfb = info->par;
	u32 level, mask, shअगरt;

	अगर (regno >= BIT(info->var.bits_per_pixel))
		वापस -EINVAL;

	shअगरt = 4 * (regno & 7);
	mask  = 0xf << shअगरt;
	/* gray = 0.30*R + 0.58*G + 0.11*B */
	level = (((red * 77 + green * 151 + blue * 28) >> 20) << shअगरt) & mask;
	अगर (cfb->cmap_invert)
		level = 0xf - level;

	regno = (regno < 8) ? CLPS711X_PALLSW : CLPS711X_PALMSW;

	ग_लिखोl((पढ़ोl(cfb->base + regno) & ~mask) | level, cfb->base + regno);

	वापस 0;
पूर्ण

अटल पूर्णांक clps711x_fb_check_var(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	u32 val;

	अगर (var->bits_per_pixel < 1 ||
	    var->bits_per_pixel > CLPS711X_FB_BPP_MAX)
		वापस -EINVAL;

	अगर (!var->pixघड़ी)
		वापस -EINVAL;

	val = DIV_ROUND_UP(var->xres, 16) - 1;
	अगर (val < 0x01 || val > 0x3f)
		वापस -EINVAL;

	val = DIV_ROUND_UP(var->yres * var->xres * var->bits_per_pixel, 128);
	val--;
	अगर (val < 0x001 || val > 0x1fff)
		वापस -EINVAL;

	var->transp.msb_right	= 0;
	var->transp.offset	= 0;
	var->transp.length	= 0;
	var->red.msb_right	= 0;
	var->red.offset		= 0;
	var->red.length		= var->bits_per_pixel;
	var->green		= var->red;
	var->blue		= var->red;
	var->grayscale		= var->bits_per_pixel > 1;

	वापस 0;
पूर्ण

अटल पूर्णांक clps711x_fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा clps711x_fb_info *cfb = info->par;
	resource_माप_प्रकार size;
	u32 lcdcon, pps;

	size = (info->var.xres * info->var.yres * info->var.bits_per_pixel) / 8;
	अगर (size > cfb->buffsize)
		वापस -EINVAL;

	चयन (info->var.bits_per_pixel) अणु
	हाल 1:
		info->fix.visual = FB_VISUAL_MONO01;
		अवरोध;
	हाल 2:
	हाल 4:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	info->fix.line_length = info->var.xres * info->var.bits_per_pixel / 8;
	info->fix.smem_len = size;

	lcdcon = (info->var.xres * info->var.yres *
		  info->var.bits_per_pixel) / 128 - 1;
	lcdcon |= ((info->var.xres / 16) - 1) << 13;
	lcdcon |= (cfb->ac_prescale & 0x1f) << 25;

	pps = clk_get_rate(cfb->clk) / (PICOS2KHZ(info->var.pixघड़ी) * 1000);
	अगर (pps)
		pps--;
	lcdcon |= (pps & 0x3f) << 19;

	अगर (info->var.bits_per_pixel == 4)
		lcdcon |= LCDCON_GSMD;
	अगर (info->var.bits_per_pixel >= 2)
		lcdcon |= LCDCON_GSEN;

	/* LCDCON must only be changed जबतक the LCD is disabled */
	regmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_LCDEN, 0);
	ग_लिखोl(lcdcon, cfb->base + CLPS711X_LCDCON);
	regmap_update_bits(cfb->syscon, SYSCON_OFFSET,
			   SYSCON1_LCDEN, SYSCON1_LCDEN);

	वापस 0;
पूर्ण

अटल पूर्णांक clps711x_fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	/* Return happy */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops clps711x_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= clps711x_fb_setcolreg,
	.fb_check_var	= clps711x_fb_check_var,
	.fb_set_par	= clps711x_fb_set_par,
	.fb_blank	= clps711x_fb_blank,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
पूर्ण;

अटल पूर्णांक clps711x_lcd_check_fb(काष्ठा lcd_device *lcddev, काष्ठा fb_info *fi)
अणु
	काष्ठा clps711x_fb_info *cfb = dev_get_drvdata(&lcddev->dev);

	वापस (!fi || fi->par == cfb) ? 1 : 0;
पूर्ण

अटल पूर्णांक clps711x_lcd_get_घातer(काष्ठा lcd_device *lcddev)
अणु
	काष्ठा clps711x_fb_info *cfb = dev_get_drvdata(&lcddev->dev);

	अगर (!IS_ERR_OR_शून्य(cfb->lcd_pwr))
		अगर (!regulator_is_enabled(cfb->lcd_pwr))
			वापस FB_BLANK_NORMAL;

	वापस FB_BLANK_UNBLANK;
पूर्ण

अटल पूर्णांक clps711x_lcd_set_घातer(काष्ठा lcd_device *lcddev, पूर्णांक blank)
अणु
	काष्ठा clps711x_fb_info *cfb = dev_get_drvdata(&lcddev->dev);

	अगर (!IS_ERR_OR_शून्य(cfb->lcd_pwr)) अणु
		अगर (blank == FB_BLANK_UNBLANK) अणु
			अगर (!regulator_is_enabled(cfb->lcd_pwr))
				वापस regulator_enable(cfb->lcd_pwr);
		पूर्ण अन्यथा अणु
			अगर (regulator_is_enabled(cfb->lcd_pwr))
				वापस regulator_disable(cfb->lcd_pwr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops clps711x_lcd_ops = अणु
	.check_fb	= clps711x_lcd_check_fb,
	.get_घातer	= clps711x_lcd_get_घातer,
	.set_घातer	= clps711x_lcd_set_घातer,
पूर्ण;

अटल पूर्णांक clps711x_fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *disp, *np = dev->of_node;
	काष्ठा clps711x_fb_info *cfb;
	काष्ठा lcd_device *lcd;
	काष्ठा fb_info *info;
	काष्ठा resource *res;
	पूर्णांक ret = -ENOENT;
	u32 val;

	अगर (fb_get_options(CLPS711X_FB_NAME, शून्य))
		वापस -ENODEV;

	info = framebuffer_alloc(माप(*cfb), dev);
	अगर (!info)
		वापस -ENOMEM;

	cfb = info->par;
	platक्रमm_set_drvdata(pdev, info);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		जाओ out_fb_release;
	cfb->base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!cfb->base) अणु
		ret = -ENOMEM;
		जाओ out_fb_release;
	पूर्ण

	info->fix.mmio_start = res->start;
	info->fix.mmio_len = resource_size(res);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	info->screen_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(info->screen_base)) अणु
		ret = PTR_ERR(info->screen_base);
		जाओ out_fb_release;
	पूर्ण

	/* Physical address should be aligned to 256 MiB */
	अगर (res->start & 0x0fffffff) अणु
		ret = -EINVAL;
		जाओ out_fb_release;
	पूर्ण

	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ out_fb_release;
	पूर्ण

	cfb->buffsize = resource_size(res);
	info->fix.smem_start = res->start;
	info->apertures->ranges[0].base = info->fix.smem_start;
	info->apertures->ranges[0].size = cfb->buffsize;

	cfb->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(cfb->clk)) अणु
		ret = PTR_ERR(cfb->clk);
		जाओ out_fb_release;
	पूर्ण

	cfb->syscon =
		syscon_regmap_lookup_by_compatible("cirrus,ep7209-syscon1");
	अगर (IS_ERR(cfb->syscon)) अणु
		ret = PTR_ERR(cfb->syscon);
		जाओ out_fb_release;
	पूर्ण

	disp = of_parse_phandle(np, "display", 0);
	अगर (!disp) अणु
		dev_err(&pdev->dev, "No display defined\n");
		ret = -ENODATA;
		जाओ out_fb_release;
	पूर्ण

	ret = of_get_fb_videomode(disp, &cfb->mode, OF_USE_NATIVE_MODE);
	अगर (ret) अणु
		of_node_put(disp);
		जाओ out_fb_release;
	पूर्ण

	of_property_पढ़ो_u32(disp, "ac-prescale", &cfb->ac_prescale);
	cfb->cmap_invert = of_property_पढ़ो_bool(disp, "cmap-invert");

	ret = of_property_पढ़ो_u32(disp, "bits-per-pixel",
				   &info->var.bits_per_pixel);
	of_node_put(disp);
	अगर (ret)
		जाओ out_fb_release;

	/* Force disable LCD on any mismatch */
	अगर (info->fix.smem_start != (पढ़ोb(cfb->base + CLPS711X_FBADDR) << 28))
		regmap_update_bits(cfb->syscon, SYSCON_OFFSET,
				   SYSCON1_LCDEN, 0);

	ret = regmap_पढ़ो(cfb->syscon, SYSCON_OFFSET, &val);
	अगर (ret)
		जाओ out_fb_release;

	अगर (!(val & SYSCON1_LCDEN)) अणु
		/* Setup start FB address */
		ग_लिखोb(info->fix.smem_start >> 28, cfb->base + CLPS711X_FBADDR);
		/* Clean FB memory */
		स_रखो_io(info->screen_base, 0, cfb->buffsize);
	पूर्ण

	cfb->lcd_pwr = devm_regulator_get(dev, "lcd");
	अगर (PTR_ERR(cfb->lcd_pwr) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ out_fb_release;
	पूर्ण

	info->fbops = &clps711x_fb_ops;
	info->flags = FBINFO_DEFAULT;
	info->var.activate = FB_ACTIVATE_FORCE | FB_ACTIVATE_NOW;
	info->var.height = -1;
	info->var.width = -1;
	info->var.vmode = FB_VMODE_NONINTERLACED;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.accel = FB_ACCEL_NONE;
	strlcpy(info->fix.id, CLPS711X_FB_NAME, माप(info->fix.id));
	fb_videomode_to_var(&info->var, &cfb->mode);

	ret = fb_alloc_cmap(&info->cmap, BIT(CLPS711X_FB_BPP_MAX), 0);
	अगर (ret)
		जाओ out_fb_release;

	ret = fb_set_var(info, &info->var);
	अगर (ret)
		जाओ out_fb_dealloc_cmap;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret)
		जाओ out_fb_dealloc_cmap;

	lcd = devm_lcd_device_रेजिस्टर(dev, "clps711x-lcd", dev, cfb,
				       &clps711x_lcd_ops);
	अगर (!IS_ERR(lcd))
		वापस 0;
	
	ret = PTR_ERR(lcd);
	unरेजिस्टर_framebuffer(info);

out_fb_dealloc_cmap:
	regmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_LCDEN, 0);
	fb_dealloc_cmap(&info->cmap);

out_fb_release:
	framebuffer_release(info);

	वापस ret;
पूर्ण

अटल पूर्णांक clps711x_fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा clps711x_fb_info *cfb = info->par;

	regmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_LCDEN, 0);

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clps711x_fb_dt_ids[] = अणु
	अणु .compatible = "cirrus,ep7209-fb", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_fb_dt_ids);

अटल काष्ठा platक्रमm_driver clps711x_fb_driver = अणु
	.driver	= अणु
		.name		= CLPS711X_FB_NAME,
		.of_match_table	= clps711x_fb_dt_ids,
	पूर्ण,
	.probe	= clps711x_fb_probe,
	.हटाओ	= clps711x_fb_हटाओ,
पूर्ण;
module_platक्रमm_driver(clps711x_fb_driver);

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("Cirrus Logic CLPS711X FB driver");
MODULE_LICENSE("GPL");
