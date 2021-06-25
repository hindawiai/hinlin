<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/video/geode/gx1fb_core.c
 *   -- Geode GX1 framebuffer driver
 *
 * Copyright (C) 2005 Arcom Control Systems Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश "geodefb.h"
#समावेश "display_gx1.h"
#समावेश "video_cs5530.h"

अटल अक्षर mode_option[32] = "640x480-16@60";
अटल पूर्णांक  crt_option = 1;
अटल अक्षर panel_option[32] = "";

/* Modes relevant to the GX1 (taken from modedb.c) */
अटल स्थिर काष्ठा fb_videomode gx1_modedb[] = अणु
	/* 640x480-60 VESA */
	अणु शून्य, 60, 640, 480, 39682,  48, 16, 33, 10, 96, 2,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 640x480-75 VESA */
	अणु शून्य, 75, 640, 480, 31746, 120, 16, 16, 01, 64, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 640x480-85 VESA */
	अणु शून्य, 85, 640, 480, 27777, 80, 56, 25, 01, 56, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 800x600-60 VESA */
	अणु शून्य, 60, 800, 600, 25000, 88, 40, 23, 01, 128, 4,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 800x600-75 VESA */
	अणु शून्य, 75, 800, 600, 20202, 160, 16, 21, 01, 80, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 800x600-85 VESA */
	अणु शून्य, 85, 800, 600, 17761, 152, 32, 27, 01, 64, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1024x768-60 VESA */
	अणु शून्य, 60, 1024, 768, 15384, 160, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1024x768-75 VESA */
	अणु शून्य, 75, 1024, 768, 12690, 176, 16, 28, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1024x768-85 VESA */
	अणु शून्य, 85, 1024, 768, 10582, 208, 48, 36, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1280x960-60 VESA */
	अणु शून्य, 60, 1280, 960, 9259, 312, 96, 36, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1280x960-85 VESA */
	अणु शून्य, 85, 1280, 960, 6734, 224, 64, 47, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1280x1024-60 VESA */
	अणु शून्य, 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1280x1024-75 VESA */
	अणु शून्य, 75, 1280, 1024, 7407, 248, 16, 38, 1, 144, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1280x1024-85 VESA */
	अणु शून्य, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
पूर्ण;

अटल पूर्णांक gx1_line_delta(पूर्णांक xres, पूर्णांक bpp)
अणु
	पूर्णांक line_delta = xres * (bpp >> 3);

	अगर (line_delta > 2048)
		line_delta = 4096;
	अन्यथा अगर (line_delta > 1024)
		line_delta = 2048;
	अन्यथा
		line_delta = 1024;
	वापस line_delta;
पूर्ण

अटल पूर्णांक gx1fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;

	/* Maximum resolution is 1280x1024. */
	अगर (var->xres > 1280 || var->yres > 1024)
		वापस -EINVAL;

	अगर (par->panel_x && (var->xres > par->panel_x || var->yres > par->panel_y))
		वापस -EINVAL;

	/* Only 16 bpp and 8 bpp is supported by the hardware. */
	अगर (var->bits_per_pixel == 16) अणु
		var->red.offset   = 11; var->red.length   = 5;
		var->green.offset =  5; var->green.length = 6;
		var->blue.offset  =  0; var->blue.length  = 5;
		var->transp.offset = 0; var->transp.length = 0;
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 8) अणु
		var->red.offset   = 0; var->red.length   = 8;
		var->green.offset = 0; var->green.length = 8;
		var->blue.offset  = 0; var->blue.length  = 8;
		var->transp.offset = 0; var->transp.length = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/* Enough video memory? */
	अगर (gx1_line_delta(var->xres, var->bits_per_pixel) * var->yres > info->fix.smem_len)
		वापस -EINVAL;

	/* FIXME: Check timing parameters here? */

	वापस 0;
पूर्ण

अटल पूर्णांक gx1fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;

	अगर (info->var.bits_per_pixel == 16)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = gx1_line_delta(info->var.xres, info->var.bits_per_pixel);

	par->dc_ops->set_mode(info);

	वापस 0;
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक gx1fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;

	अगर (info->var.grayscale) अणु
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	/* Truecolor has hardware independent palette */
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 *pal = info->pseuकरो_palette;
		u32 v;

		अगर (regno >= 16)
			वापस -EINVAL;

		v  = chan_to_field(red, &info->var.red);
		v |= chan_to_field(green, &info->var.green);
		v |= chan_to_field(blue, &info->var.blue);

		pal[regno] = v;
	पूर्ण अन्यथा अणु
		अगर (regno >= 256)
			वापस -EINVAL;

		par->dc_ops->set_palette_reg(info, regno, red, green, blue);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gx1fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;

	वापस par->vid_ops->blank_display(info, blank_mode);
पूर्ण

अटल पूर्णांक gx1fb_map_video_memory(काष्ठा fb_info *info, काष्ठा pci_dev *dev)
अणु
	काष्ठा geodefb_par *par = info->par;
	अचिन्हित gx_base;
	पूर्णांक fb_len;
	पूर्णांक ret;

	gx_base = gx1_gx_base();
	अगर (!gx_base)
		वापस -ENODEV;

	ret = pci_enable_device(dev);
	अगर (ret < 0)
		वापस ret;

	ret = pci_request_region(dev, 0, "gx1fb (video)");
	अगर (ret < 0)
		वापस ret;
	par->vid_regs = pci_ioremap_bar(dev, 0);
	अगर (!par->vid_regs)
		वापस -ENOMEM;

	अगर (!request_mem_region(gx_base + 0x8300, 0x100, "gx1fb (display controller)"))
		वापस -EBUSY;
	par->dc_regs = ioremap(gx_base + 0x8300, 0x100);
	अगर (!par->dc_regs)
		वापस -ENOMEM;

	अगर ((fb_len = gx1_frame_buffer_size()) < 0)
		वापस -ENOMEM;
	info->fix.smem_start = gx_base + 0x800000;
	info->fix.smem_len = fb_len;
	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);
	अगर (!info->screen_base)
		वापस -ENOMEM;

	dev_info(&dev->dev, "%d Kibyte of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_panel_option(काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;

	अगर (म_भेद(panel_option, "") != 0) अणु
		पूर्णांक x, y;
		अक्षर *s;
		x = simple_म_से_दीर्घ(panel_option, &s, 10);
		अगर (!x)
			वापस -EINVAL;
		y = simple_म_से_दीर्घ(s + 1, शून्य, 10);
		अगर (!y)
			वापस -EINVAL;
		par->panel_x = x;
		par->panel_y = y;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops gx1fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= gx1fb_check_var,
	.fb_set_par	= gx1fb_set_par,
	.fb_setcolreg	= gx1fb_setcolreg,
	.fb_blank       = gx1fb_blank,
	/* No HW acceleration क्रम now. */
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल काष्ठा fb_info *gx1fb_init_fbinfo(काष्ठा device *dev)
अणु
	काष्ठा geodefb_par *par;
	काष्ठा fb_info *info;

	/* Alloc enough space क्रम the pseuकरो palette. */
	info = framebuffer_alloc(माप(काष्ठा geodefb_par) + माप(u32) * 16, dev);
	अगर (!info)
		वापस शून्य;

	par = info->par;

	म_नकल(info->fix.id, "GX1");

	info->fix.type		= FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	= 0;
	info->fix.xpanstep	= 0;
	info->fix.ypanstep	= 0;
	info->fix.ywrapstep	= 0;
	info->fix.accel		= FB_ACCEL_NONE;

	info->var.nonstd	= 0;
	info->var.activate	= FB_ACTIVATE_NOW;
	info->var.height	= -1;
	info->var.width	= -1;
	info->var.accel_flags = 0;
	info->var.vmode	= FB_VMODE_NONINTERLACED;

	info->fbops		= &gx1fb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseuकरो_palette	= (व्योम *)par + माप(काष्ठा geodefb_par);

	info->var.grayscale	= 0;

	/* CRT and panel options */
	par->enable_crt = crt_option;
	अगर (parse_panel_option(info) < 0)
		prपूर्णांकk(KERN_WARNING "gx1fb: invalid 'panel' option -- disabling flat panel\n");
	अगर (!par->panel_x)
		par->enable_crt = 1; /* fall back to CRT अगर no panel is specअगरied */

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		framebuffer_release(info);
		वापस शून्य;
	पूर्ण
	वापस info;
पूर्ण

अटल पूर्णांक gx1fb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा geodefb_par *par;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	info = gx1fb_init_fbinfo(&pdev->dev);
	अगर (!info)
		वापस -ENOMEM;
	par = info->par;

	/* GX1 display controller and CS5530 video device */
	par->dc_ops  = &gx1_dc_ops;
	par->vid_ops = &cs5530_vid_ops;

	अगर ((ret = gx1fb_map_video_memory(info, pdev)) < 0) अणु
		dev_err(&pdev->dev, "failed to map frame buffer or controller registers\n");
		जाओ err;
	पूर्ण

	ret = fb_find_mode(&info->var, info, mode_option,
			   gx1_modedb, ARRAY_SIZE(gx1_modedb), शून्य, 16);
	अगर (ret == 0 || ret == 4) अणु
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

        /* Clear the frame buffer of garbage. */
        स_रखो_io(info->screen_base, 0, info->fix.smem_len);

	gx1fb_check_var(&info->var, info);
	gx1fb_set_par(info);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	pci_set_drvdata(pdev, info);
	fb_info(info, "%s frame buffer device\n", info->fix.id);
	वापस 0;

  err:
	अगर (info->screen_base) अणु
		iounmap(info->screen_base);
		pci_release_region(pdev, 0);
	पूर्ण
	अगर (par->vid_regs) अणु
		iounmap(par->vid_regs);
		pci_release_region(pdev, 1);
	पूर्ण
	अगर (par->dc_regs) अणु
		iounmap(par->dc_regs);
		release_mem_region(gx1_gx_base() + 0x8300, 0x100);
	पूर्ण

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	वापस ret;
पूर्ण

अटल व्योम gx1fb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा geodefb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);

	iounmap((व्योम __iomem *)info->screen_base);
	pci_release_region(pdev, 0);

	iounmap(par->vid_regs);
	pci_release_region(pdev, 1);

	iounmap(par->dc_regs);
	release_mem_region(gx1_gx_base() + 0x8300, 0x100);

	fb_dealloc_cmap(&info->cmap);

	framebuffer_release(info);
पूर्ण

#अगर_अघोषित MODULE
अटल व्योम __init gx1fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस;

	जबतक ((this_opt = strsep(&options, ","))) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेदन(this_opt, "mode:", 5))
			strlcpy(mode_option, this_opt + 5, माप(mode_option));
		अन्यथा अगर (!म_भेदन(this_opt, "crt:", 4))
			crt_option = !!simple_म_से_अदीर्घ(this_opt + 4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "panel:", 6))
			strlcpy(panel_option, this_opt + 6, माप(panel_option));
		अन्यथा
			strlcpy(mode_option, this_opt, माप(mode_option));
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pci_device_id gx1fb_id_table[] = अणु
	अणु PCI_VENDOR_ID_CYRIX, PCI_DEVICE_ID_CYRIX_5530_VIDEO,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  0xff0000, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, gx1fb_id_table);

अटल काष्ठा pci_driver gx1fb_driver = अणु
	.name		= "gx1fb",
	.id_table	= gx1fb_id_table,
	.probe		= gx1fb_probe,
	.हटाओ		= gx1fb_हटाओ,
पूर्ण;

अटल पूर्णांक __init gx1fb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("gx1fb", &option))
		वापस -ENODEV;
	gx1fb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&gx1fb_driver);
पूर्ण

अटल व्योम gx1fb_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&gx1fb_driver);
पूर्ण

module_init(gx1fb_init);
module_निकास(gx1fb_cleanup);

module_param_string(mode, mode_option, माप(mode_option), 0444);
MODULE_PARM_DESC(mode, "video mode (<x>x<y>[-<bpp>][@<refr>])");

module_param_named(crt, crt_option, पूर्णांक, 0444);
MODULE_PARM_DESC(crt, "enable CRT output. 0 = off, 1 = on (default)");

module_param_string(panel, panel_option, माप(panel_option), 0444);
MODULE_PARM_DESC(panel, "size of attached flat panel (<x>x<y>)");

MODULE_DESCRIPTION("framebuffer driver for the AMD Geode GX1");
MODULE_LICENSE("GPL");
