<शैली गुरु>
/* sunxvr1000.c: Sun XVR-1000 fb driver क्रम sparc64 प्रणालीs
 *
 * License: GPL
 *
 * Copyright (C) 2010 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>

काष्ठा gfb_info अणु
	काष्ठा fb_info		*info;

	अक्षर __iomem		*fb_base;
	अचिन्हित दीर्घ		fb_base_phys;

	काष्ठा device_node	*of_node;

	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		depth;
	अचिन्हित पूर्णांक		fb_size;

	u32			pseuकरो_palette[16];
पूर्ण;

अटल पूर्णांक gfb_get_props(काष्ठा gfb_info *gp)
अणु
	gp->width = of_getपूर्णांकprop_शेष(gp->of_node, "width", 0);
	gp->height = of_getपूर्णांकprop_शेष(gp->of_node, "height", 0);
	gp->depth = of_getपूर्णांकprop_शेष(gp->of_node, "depth", 32);

	अगर (!gp->width || !gp->height) अणु
		prपूर्णांकk(KERN_ERR "gfb: Critical properties missing for %pOF\n",
		       gp->of_node);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfb_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	u32 value;

	अगर (regno < 16) अणु
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		value = (blue << 16) | (green << 8) | red;
		((u32 *)info->pseuकरो_palette)[regno] = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops gfb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= gfb_setcolreg,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
पूर्ण;

अटल पूर्णांक gfb_set_fbinfo(काष्ठा gfb_info *gp)
अणु
	काष्ठा fb_info *info = gp->info;
	काष्ठा fb_var_screeninfo *var = &info->var;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &gfb_ops;
	info->screen_base = gp->fb_base;
	info->screen_size = gp->fb_size;

	info->pseuकरो_palette = gp->pseuकरो_palette;

	/* Fill fix common fields */
	strlcpy(info->fix.id, "gfb", माप(info->fix.id));
        info->fix.smem_start = gp->fb_base_phys;
        info->fix.smem_len = gp->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
	अगर (gp->depth == 32 || gp->depth == 24)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	var->xres = gp->width;
	var->yres = gp->height;
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;
	var->bits_per_pixel = gp->depth;

	var->red.offset = 0;
	var->red.length = 8;
	var->green.offset = 8;
	var->green.length = 8;
	var->blue.offset = 16;
	var->blue.length = 8;
	var->transp.offset = 0;
	var->transp.length = 0;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0)) अणु
		prपूर्णांकk(KERN_ERR "gfb: Cannot allocate color map.\n");
		वापस -ENOMEM;
	पूर्ण

        वापस 0;
पूर्ण

अटल पूर्णांक gfb_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा gfb_info *gp;
	पूर्णांक err;

	info = framebuffer_alloc(माप(काष्ठा gfb_info), &op->dev);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	gp = info->par;
	gp->info = info;
	gp->of_node = dp;

	gp->fb_base_phys = op->resource[6].start;

	err = gfb_get_props(gp);
	अगर (err)
		जाओ err_release_fb;

	/* Framebuffer length is the same regardless of resolution. */
	info->fix.line_length = 16384;
	gp->fb_size = info->fix.line_length * gp->height;

	gp->fb_base = of_ioremap(&op->resource[6], 0,
				 gp->fb_size, "gfb fb");
	अगर (!gp->fb_base) अणु
		err = -ENOMEM;
		जाओ err_release_fb;
	पूर्ण

	err = gfb_set_fbinfo(gp);
	अगर (err)
		जाओ err_unmap_fb;

	prपूर्णांकk("gfb: Found device at %pOF\n", dp);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "gfb: Could not register framebuffer %pOF\n",
		       dp);
		जाओ err_unmap_fb;
	पूर्ण

	dev_set_drvdata(&op->dev, info);

	वापस 0;

err_unmap_fb:
	of_iounmap(&op->resource[6], gp->fb_base, gp->fb_size);

err_release_fb:
        framebuffer_release(info);

err_out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id gfb_match[] = अणु
	अणु
		.name = "SUNW,gfb",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gfb_driver = अणु
	.probe		= gfb_probe,
	.driver = अणु
		.name			= "gfb",
		.of_match_table		= gfb_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gfb_init(व्योम)
अणु
	अगर (fb_get_options("gfb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&gfb_driver);
पूर्ण
device_initcall(gfb_init);
