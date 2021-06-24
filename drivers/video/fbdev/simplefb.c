<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simplest possible simple frame-buffer driver, as a platक्रमm device
 *
 * Copyright (c) 2013, Stephen Warren
 *
 * Based on q40fb.c, which was:
 * Copyright (C) 2001 Riअक्षरd Zidlicky <rz@linux-m68k.org>
 *
 * Also based on offb.c, which was:
 * Copyright (C) 1997 Geert Uytterhoeven
 * Copyright (C) 1996 Paul Mackerras
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/parser.h>
#समावेश <linux/regulator/consumer.h>

अटल स्थिर काष्ठा fb_fix_screeninfo simplefb_fix = अणु
	.id		= "simple",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_TRUECOLOR,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo simplefb_var = अणु
	.height		= -1,
	.width		= -1,
	.activate	= FB_ACTIVATE_NOW,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

#घोषणा PSEUDO_PALETTE_SIZE 16

अटल पूर्णांक simplefb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			      u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 *pal = info->pseuकरो_palette;
	u32 cr = red >> (16 - info->var.red.length);
	u32 cg = green >> (16 - info->var.green.length);
	u32 cb = blue >> (16 - info->var.blue.length);
	u32 value;

	अगर (regno >= PSEUDO_PALETTE_SIZE)
		वापस -EINVAL;

	value = (cr << info->var.red.offset) |
		(cg << info->var.green.offset) |
		(cb << info->var.blue.offset);
	अगर (info->var.transp.length > 0) अणु
		u32 mask = (1 << info->var.transp.length) - 1;
		mask <<= info->var.transp.offset;
		value |= mask;
	पूर्ण
	pal[regno] = value;

	वापस 0;
पूर्ण

काष्ठा simplefb_par;
अटल व्योम simplefb_घड़ीs_destroy(काष्ठा simplefb_par *par);
अटल व्योम simplefb_regulators_destroy(काष्ठा simplefb_par *par);

अटल व्योम simplefb_destroy(काष्ठा fb_info *info)
अणु
	simplefb_regulators_destroy(info->par);
	simplefb_घड़ीs_destroy(info->par);
	अगर (info->screen_base)
		iounmap(info->screen_base);
पूर्ण

अटल स्थिर काष्ठा fb_ops simplefb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_destroy	= simplefb_destroy,
	.fb_setcolreg	= simplefb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल काष्ठा simplefb_क्रमmat simplefb_क्रमmats[] = SIMPLEFB_FORMATS;

काष्ठा simplefb_params अणु
	u32 width;
	u32 height;
	u32 stride;
	काष्ठा simplefb_क्रमmat *क्रमmat;
पूर्ण;

अटल पूर्णांक simplefb_parse_dt(काष्ठा platक्रमm_device *pdev,
			   काष्ठा simplefb_params *params)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;
	स्थिर अक्षर *क्रमmat;
	पूर्णांक i;

	ret = of_property_पढ़ो_u32(np, "width", &params->width);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't parse width property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "height", &params->height);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't parse height property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "stride", &params->stride);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't parse stride property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_string(np, "format", &क्रमmat);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't parse format property\n");
		वापस ret;
	पूर्ण
	params->क्रमmat = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(simplefb_क्रमmats); i++) अणु
		अगर (म_भेद(क्रमmat, simplefb_क्रमmats[i].name))
			जारी;
		params->क्रमmat = &simplefb_क्रमmats[i];
		अवरोध;
	पूर्ण
	अगर (!params->क्रमmat) अणु
		dev_err(&pdev->dev, "Invalid format value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simplefb_parse_pd(काष्ठा platक्रमm_device *pdev,
			     काष्ठा simplefb_params *params)
अणु
	काष्ठा simplefb_platक्रमm_data *pd = dev_get_platdata(&pdev->dev);
	पूर्णांक i;

	params->width = pd->width;
	params->height = pd->height;
	params->stride = pd->stride;

	params->क्रमmat = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(simplefb_क्रमmats); i++) अणु
		अगर (म_भेद(pd->क्रमmat, simplefb_क्रमmats[i].name))
			जारी;

		params->क्रमmat = &simplefb_क्रमmats[i];
		अवरोध;
	पूर्ण

	अगर (!params->क्रमmat) अणु
		dev_err(&pdev->dev, "Invalid format value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा simplefb_par अणु
	u32 palette[PSEUDO_PALETTE_SIZE];
#अगर defined CONFIG_OF && defined CONFIG_COMMON_CLK
	bool clks_enabled;
	अचिन्हित पूर्णांक clk_count;
	काष्ठा clk **clks;
#पूर्ण_अगर
#अगर defined CONFIG_OF && defined CONFIG_REGULATOR
	bool regulators_enabled;
	u32 regulator_count;
	काष्ठा regulator **regulators;
#पूर्ण_अगर
पूर्ण;

#अगर defined CONFIG_OF && defined CONFIG_COMMON_CLK
/*
 * Clock handling code.
 *
 * Here we handle the घड़ीs property of our "simple-framebuffer" dt node.
 * This is necessary so that we can make sure that any घड़ीs needed by
 * the display engine that the bootloader set up क्रम us (and क्रम which it
 * provided a simplefb dt node), stay up, क्रम the lअगरe of the simplefb
 * driver.
 *
 * When the driver unloads, we cleanly disable, and then release the घड़ीs.
 *
 * We only complain about errors here, no action is taken as the most likely
 * error can only happen due to a mismatch between the bootloader which set
 * up simplefb, and the घड़ी definitions in the device tree. Chances are
 * that there are no adverse effects, and अगर there are, a clean tearकरोwn of
 * the fb probe will not help us much either. So just complain and carry on,
 * and hope that the user actually माला_लो a working fb at the end of things.
 */
अटल पूर्णांक simplefb_घड़ीs_get(काष्ठा simplefb_par *par,
			       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk *घड़ी;
	पूर्णांक i;

	अगर (dev_get_platdata(&pdev->dev) || !np)
		वापस 0;

	par->clk_count = of_clk_get_parent_count(np);
	अगर (!par->clk_count)
		वापस 0;

	par->clks = kसुस्मृति(par->clk_count, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!par->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < par->clk_count; i++) अणु
		घड़ी = of_clk_get(np, i);
		अगर (IS_ERR(घड़ी)) अणु
			अगर (PTR_ERR(घड़ी) == -EPROBE_DEFER) अणु
				जबतक (--i >= 0) अणु
					अगर (par->clks[i])
						clk_put(par->clks[i]);
				पूर्ण
				kमुक्त(par->clks);
				वापस -EPROBE_DEFER;
			पूर्ण
			dev_err(&pdev->dev, "%s: clock %d not found: %ld\n",
				__func__, i, PTR_ERR(घड़ी));
			जारी;
		पूर्ण
		par->clks[i] = घड़ी;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम simplefb_घड़ीs_enable(काष्ठा simplefb_par *par,
				   काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < par->clk_count; i++) अणु
		अगर (par->clks[i]) अणु
			ret = clk_prepare_enable(par->clks[i]);
			अगर (ret) अणु
				dev_err(&pdev->dev,
					"%s: failed to enable clock %d: %d\n",
					__func__, i, ret);
				clk_put(par->clks[i]);
				par->clks[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	par->clks_enabled = true;
पूर्ण

अटल व्योम simplefb_घड़ीs_destroy(काष्ठा simplefb_par *par)
अणु
	पूर्णांक i;

	अगर (!par->clks)
		वापस;

	क्रम (i = 0; i < par->clk_count; i++) अणु
		अगर (par->clks[i]) अणु
			अगर (par->clks_enabled)
				clk_disable_unprepare(par->clks[i]);
			clk_put(par->clks[i]);
		पूर्ण
	पूर्ण

	kमुक्त(par->clks);
पूर्ण
#अन्यथा
अटल पूर्णांक simplefb_घड़ीs_get(काष्ठा simplefb_par *par,
	काष्ठा platक्रमm_device *pdev) अणु वापस 0; पूर्ण
अटल व्योम simplefb_घड़ीs_enable(काष्ठा simplefb_par *par,
	काष्ठा platक्रमm_device *pdev) अणु पूर्ण
अटल व्योम simplefb_घड़ीs_destroy(काष्ठा simplefb_par *par) अणु पूर्ण
#पूर्ण_अगर

#अगर defined CONFIG_OF && defined CONFIG_REGULATOR

#घोषणा SUPPLY_SUFFIX "-supply"

/*
 * Regulator handling code.
 *
 * Here we handle the num-supplies and vin*-supply properties of our
 * "simple-framebuffer" dt node. This is necessary so that we can make sure
 * that any regulators needed by the display hardware that the bootloader
 * set up क्रम us (and क्रम which it provided a simplefb dt node), stay up,
 * क्रम the lअगरe of the simplefb driver.
 *
 * When the driver unloads, we cleanly disable, and then release the
 * regulators.
 *
 * We only complain about errors here, no action is taken as the most likely
 * error can only happen due to a mismatch between the bootloader which set
 * up simplefb, and the regulator definitions in the device tree. Chances are
 * that there are no adverse effects, and अगर there are, a clean tearकरोwn of
 * the fb probe will not help us much either. So just complain and carry on,
 * and hope that the user actually माला_लो a working fb at the end of things.
 */
अटल पूर्णांक simplefb_regulators_get(काष्ठा simplefb_par *par,
				   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा property *prop;
	काष्ठा regulator *regulator;
	स्थिर अक्षर *p;
	पूर्णांक count = 0, i = 0;

	अगर (dev_get_platdata(&pdev->dev) || !np)
		वापस 0;

	/* Count the number of regulator supplies */
	क्रम_each_property_of_node(np, prop) अणु
		p = म_माला(prop->name, SUPPLY_SUFFIX);
		अगर (p && p != prop->name)
			count++;
	पूर्ण

	अगर (!count)
		वापस 0;

	par->regulators = devm_kसुस्मृति(&pdev->dev, count,
				       माप(काष्ठा regulator *), GFP_KERNEL);
	अगर (!par->regulators)
		वापस -ENOMEM;

	/* Get all the regulators */
	क्रम_each_property_of_node(np, prop) अणु
		अक्षर name[32]; /* 32 is max size of property name */

		p = म_माला(prop->name, SUPPLY_SUFFIX);
		अगर (!p || p == prop->name)
			जारी;

		strlcpy(name, prop->name,
			म_माप(prop->name) - म_माप(SUPPLY_SUFFIX) + 1);
		regulator = devm_regulator_get_optional(&pdev->dev, name);
		अगर (IS_ERR(regulator)) अणु
			अगर (PTR_ERR(regulator) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			dev_err(&pdev->dev, "regulator %s not found: %ld\n",
				name, PTR_ERR(regulator));
			जारी;
		पूर्ण
		par->regulators[i++] = regulator;
	पूर्ण
	par->regulator_count = i;

	वापस 0;
पूर्ण

अटल व्योम simplefb_regulators_enable(काष्ठा simplefb_par *par,
				       काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;

	/* Enable all the regulators */
	क्रम (i = 0; i < par->regulator_count; i++) अणु
		ret = regulator_enable(par->regulators[i]);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to enable regulator %d: %d\n",
				i, ret);
			devm_regulator_put(par->regulators[i]);
			par->regulators[i] = शून्य;
		पूर्ण
	पूर्ण
	par->regulators_enabled = true;
पूर्ण

अटल व्योम simplefb_regulators_destroy(काष्ठा simplefb_par *par)
अणु
	पूर्णांक i;

	अगर (!par->regulators || !par->regulators_enabled)
		वापस;

	क्रम (i = 0; i < par->regulator_count; i++)
		अगर (par->regulators[i])
			regulator_disable(par->regulators[i]);
पूर्ण
#अन्यथा
अटल पूर्णांक simplefb_regulators_get(काष्ठा simplefb_par *par,
	काष्ठा platक्रमm_device *pdev) अणु वापस 0; पूर्ण
अटल व्योम simplefb_regulators_enable(काष्ठा simplefb_par *par,
	काष्ठा platक्रमm_device *pdev) अणु पूर्ण
अटल व्योम simplefb_regulators_destroy(काष्ठा simplefb_par *par) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक simplefb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा simplefb_params params;
	काष्ठा fb_info *info;
	काष्ठा simplefb_par *par;
	काष्ठा resource *mem;

	अगर (fb_get_options("simplefb", शून्य))
		वापस -ENODEV;

	ret = -ENODEV;
	अगर (dev_get_platdata(&pdev->dev))
		ret = simplefb_parse_pd(pdev, &params);
	अन्यथा अगर (pdev->dev.of_node)
		ret = simplefb_parse_dt(pdev, &params);

	अगर (ret)
		वापस ret;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(&pdev->dev, "No memory resource\n");
		वापस -EINVAL;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा simplefb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, info);

	par = info->par;

	info->fix = simplefb_fix;
	info->fix.smem_start = mem->start;
	info->fix.smem_len = resource_size(mem);
	info->fix.line_length = params.stride;

	info->var = simplefb_var;
	info->var.xres = params.width;
	info->var.yres = params.height;
	info->var.xres_भव = params.width;
	info->var.yres_भव = params.height;
	info->var.bits_per_pixel = params.क्रमmat->bits_per_pixel;
	info->var.red = params.क्रमmat->red;
	info->var.green = params.क्रमmat->green;
	info->var.blue = params.क्रमmat->blue;
	info->var.transp = params.क्रमmat->transp;

	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ error_fb_release;
	पूर्ण
	info->apertures->ranges[0].base = info->fix.smem_start;
	info->apertures->ranges[0].size = info->fix.smem_len;

	info->fbops = &simplefb_ops;
	info->flags = FBINFO_DEFAULT | FBINFO_MISC_FIRMWARE;
	info->screen_base = ioremap_wc(info->fix.smem_start,
				       info->fix.smem_len);
	अगर (!info->screen_base) अणु
		ret = -ENOMEM;
		जाओ error_fb_release;
	पूर्ण
	info->pseuकरो_palette = par->palette;

	ret = simplefb_घड़ीs_get(par, pdev);
	अगर (ret < 0)
		जाओ error_unmap;

	ret = simplefb_regulators_get(par, pdev);
	अगर (ret < 0)
		जाओ error_घड़ीs;

	simplefb_घड़ीs_enable(par, pdev);
	simplefb_regulators_enable(par, pdev);

	dev_info(&pdev->dev, "framebuffer at 0x%lx, 0x%x bytes\n",
			     info->fix.smem_start, info->fix.smem_len);
	dev_info(&pdev->dev, "format=%s, mode=%dx%dx%d, linelength=%d\n",
			     params.क्रमmat->name,
			     info->var.xres, info->var.yres,
			     info->var.bits_per_pixel, info->fix.line_length);

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Unable to register simplefb: %d\n", ret);
		जाओ error_regulators;
	पूर्ण

	dev_info(&pdev->dev, "fb%d: simplefb registered!\n", info->node);

	वापस 0;

error_regulators:
	simplefb_regulators_destroy(par);
error_घड़ीs:
	simplefb_घड़ीs_destroy(par);
error_unmap:
	iounmap(info->screen_base);
error_fb_release:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक simplefb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id simplefb_of_match[] = अणु
	अणु .compatible = "simple-framebuffer", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, simplefb_of_match);

अटल काष्ठा platक्रमm_driver simplefb_driver = अणु
	.driver = अणु
		.name = "simple-framebuffer",
		.of_match_table = simplefb_of_match,
	पूर्ण,
	.probe = simplefb_probe,
	.हटाओ = simplefb_हटाओ,
पूर्ण;

अटल पूर्णांक __init simplefb_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np;

	ret = platक्रमm_driver_रेजिस्टर(&simplefb_driver);
	अगर (ret)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_OF_ADDRESS) && of_chosen) अणु
		क्रम_each_child_of_node(of_chosen, np) अणु
			अगर (of_device_is_compatible(np, "simple-framebuffer"))
				of_platक्रमm_device_create(np, शून्य, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

fs_initcall(simplefb_init);

MODULE_AUTHOR("Stephen Warren <swarren@wwwdotorg.org>");
MODULE_DESCRIPTION("Simple framebuffer driver");
MODULE_LICENSE("GPL v2");
