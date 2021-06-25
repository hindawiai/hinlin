<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Geode GX framebuffer driver.
 *
 *   Copyright (C) 2006 Arcom Control Systems Ltd.
 *
 * This driver assumes that the BIOS has created a भव PCI device header
 * क्रम the video device. The PCI header is assumed to contain the following
 * BARs:
 *
 *    BAR0 - framebuffer memory
 *    BAR1 - graphics processor रेजिस्टरs
 *    BAR2 - display controller रेजिस्टरs
 *    BAR3 - video processor and flat panel control रेजिस्टरs.
 *
 * 16 MiB of framebuffer memory is assumed to be available.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/console.h>
#समावेश <linux/suspend.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/cs5535.h>

#समावेश <यंत्र/olpc.h>

#समावेश "gxfb.h"

अटल अक्षर *mode_option;
अटल पूर्णांक vram;
अटल पूर्णांक vt_चयन;

/* Modes relevant to the GX (taken from modedb.c) */
अटल काष्ठा fb_videomode gx_modedb[] = अणु
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
	/* 1600x1200-60 VESA */
	अणु शून्य, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1600x1200-75 VESA */
	अणु शून्य, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 1600x1200-85 VESA */
	अणु शून्य, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode gx_dcon_modedb[] = अणु
	/* The only mode the DCON has is 1200x900 */
	अणु शून्य, 50, 1200, 900, 17460, 24, 8, 4, 5, 8, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण
पूर्ण;

अटल व्योम get_modedb(काष्ठा fb_videomode **modedb, अचिन्हित पूर्णांक *size)
अणु
	अगर (olpc_has_dcon()) अणु
		*modedb = (काष्ठा fb_videomode *) gx_dcon_modedb;
		*size = ARRAY_SIZE(gx_dcon_modedb);
	पूर्ण अन्यथा अणु
		*modedb = (काष्ठा fb_videomode *) gx_modedb;
		*size = ARRAY_SIZE(gx_modedb);
	पूर्ण
पूर्ण

अटल पूर्णांक gxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अगर (var->xres > 1600 || var->yres > 1200)
		वापस -EINVAL;
	अगर ((var->xres > 1280 || var->yres > 1024) && var->bits_per_pixel > 16)
		वापस -EINVAL;

	अगर (var->bits_per_pixel == 32) अणु
		var->red.offset   = 16; var->red.length   = 8;
		var->green.offset =  8; var->green.length = 8;
		var->blue.offset  =  0; var->blue.length  = 8;
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 16) अणु
		var->red.offset   = 11; var->red.length   = 5;
		var->green.offset =  5; var->green.length = 6;
		var->blue.offset  =  0; var->blue.length  = 5;
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 8) अणु
		var->red.offset   = 0; var->red.length   = 8;
		var->green.offset = 0; var->green.length = 8;
		var->blue.offset  = 0; var->blue.length  = 8;
	पूर्ण अन्यथा
		वापस -EINVAL;
	var->transp.offset = 0; var->transp.length = 0;

	/* Enough video memory? */
	अगर (gx_line_delta(var->xres, var->bits_per_pixel) * var->yres > info->fix.smem_len)
		वापस -EINVAL;

	/* FIXME: Check timing parameters here? */

	वापस 0;
पूर्ण

अटल पूर्णांक gxfb_set_par(काष्ठा fb_info *info)
अणु
	अगर (info->var.bits_per_pixel > 8)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = gx_line_delta(info->var.xres, info->var.bits_per_pixel);

	gx_set_mode(info);

	वापस 0;
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक gxfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
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

		gx_set_hw_palette_reg(info, regno, red, green, blue);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gxfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	वापस gx_blank_display(info, blank_mode);
पूर्ण

अटल पूर्णांक gxfb_map_video_memory(काष्ठा fb_info *info, काष्ठा pci_dev *dev)
अणु
	काष्ठा gxfb_par *par = info->par;
	पूर्णांक ret;

	ret = pci_enable_device(dev);
	अगर (ret < 0)
		वापस ret;

	ret = pci_request_region(dev, 3, "gxfb (video processor)");
	अगर (ret < 0)
		वापस ret;
	par->vid_regs = pci_ioremap_bar(dev, 3);
	अगर (!par->vid_regs)
		वापस -ENOMEM;

	ret = pci_request_region(dev, 2, "gxfb (display controller)");
	अगर (ret < 0)
		वापस ret;
	par->dc_regs = pci_ioremap_bar(dev, 2);
	अगर (!par->dc_regs)
		वापस -ENOMEM;

	ret = pci_request_region(dev, 1, "gxfb (graphics processor)");
	अगर (ret < 0)
		वापस ret;
	par->gp_regs = pci_ioremap_bar(dev, 1);

	अगर (!par->gp_regs)
		वापस -ENOMEM;

	ret = pci_request_region(dev, 0, "gxfb (framebuffer)");
	अगर (ret < 0)
		वापस ret;

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = vram ? vram : gx_frame_buffer_size();
	info->screen_base = ioremap_wc(info->fix.smem_start,
				       info->fix.smem_len);
	अगर (!info->screen_base)
		वापस -ENOMEM;

	/* Set the 16MiB aligned base address of the graphics memory region
	 * in the display controller */

	ग_लिखो_dc(par, DC_GLIU0_MEM_OFFSET, info->fix.smem_start & 0xFF000000);

	dev_info(&dev->dev, "%d KiB of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops gxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= gxfb_check_var,
	.fb_set_par	= gxfb_set_par,
	.fb_setcolreg	= gxfb_setcolreg,
	.fb_blank       = gxfb_blank,
	/* No HW acceleration क्रम now. */
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल काष्ठा fb_info *gxfb_init_fbinfo(काष्ठा device *dev)
अणु
	काष्ठा gxfb_par *par;
	काष्ठा fb_info *info;

	/* Alloc enough space क्रम the pseuकरो palette. */
	info = framebuffer_alloc(माप(काष्ठा gxfb_par) + माप(u32) * 16,
			dev);
	अगर (!info)
		वापस शून्य;

	par = info->par;

	म_नकल(info->fix.id, "Geode GX");

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

	info->fbops		= &gxfb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseuकरो_palette	= (व्योम *)par + माप(काष्ठा gxfb_par);

	info->var.grayscale	= 0;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		framebuffer_release(info);
		वापस शून्य;
	पूर्ण

	वापस info;
पूर्ण

अटल पूर्णांक __maybe_unused gxfb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);

	console_lock();
	gx_घातerकरोwn(info);
	fb_set_suspend(info, 1);
	console_unlock();

	/* there's no poपूर्णांक in setting PCI states; we emulate PCI, so
	 * we करोn't end up getting घातer savings anyways */

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gxfb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	console_lock();
	ret = gx_घातerup(info);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "gxfb:  power up failed!\n");
		वापस ret;
	पूर्ण

	fb_set_suspend(info, 0);
	console_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक gxfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा gxfb_par *par;
	काष्ठा fb_info *info;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;

	काष्ठा fb_videomode *modedb_ptr;
	अचिन्हित पूर्णांक modedb_size;

	info = gxfb_init_fbinfo(&pdev->dev);
	अगर (!info)
		वापस -ENOMEM;
	par = info->par;

	अगर ((ret = gxfb_map_video_memory(info, pdev)) < 0) अणु
		dev_err(&pdev->dev, "failed to map frame buffer or controller registers\n");
		जाओ err;
	पूर्ण

	/* Figure out अगर this is a TFT or CRT part */

	rdmsrl(MSR_GX_GLD_MSR_CONFIG, val);

	अगर ((val & MSR_GX_GLD_MSR_CONFIG_FP) == MSR_GX_GLD_MSR_CONFIG_FP)
		par->enable_crt = 0;
	अन्यथा
		par->enable_crt = 1;

	get_modedb(&modedb_ptr, &modedb_size);
	ret = fb_find_mode(&info->var, info, mode_option,
			   modedb_ptr, modedb_size, शून्य, 16);
	अगर (ret == 0 || ret == 4) अणु
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण


	/* Clear the frame buffer of garbage. */
        स_रखो_io(info->screen_base, 0, info->fix.smem_len);

	gxfb_check_var(&info->var, info);
	gxfb_set_par(info);

	pm_set_vt_चयन(vt_चयन);

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
		pci_release_region(pdev, 3);
	पूर्ण
	अगर (par->dc_regs) अणु
		iounmap(par->dc_regs);
		pci_release_region(pdev, 2);
	पूर्ण
	अगर (par->gp_regs) अणु
		iounmap(par->gp_regs);
		pci_release_region(pdev, 1);
	पूर्ण

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल व्योम gxfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा gxfb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);

	iounmap((व्योम __iomem *)info->screen_base);
	pci_release_region(pdev, 0);

	iounmap(par->vid_regs);
	pci_release_region(pdev, 3);

	iounmap(par->dc_regs);
	pci_release_region(pdev, 2);

	iounmap(par->gp_regs);
	pci_release_region(pdev, 1);

	fb_dealloc_cmap(&info->cmap);

	framebuffer_release(info);
पूर्ण

अटल स्थिर काष्ठा pci_device_id gxfb_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_GX_VIDEO) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, gxfb_id_table);

अटल स्थिर काष्ठा dev_pm_ops gxfb_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= gxfb_suspend,
	.resume		= gxfb_resume,
	.मुक्तze		= शून्य,
	.thaw		= gxfb_resume,
	.घातeroff	= शून्य,
	.restore	= gxfb_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pci_driver gxfb_driver = अणु
	.name		= "gxfb",
	.id_table	= gxfb_id_table,
	.probe		= gxfb_probe,
	.हटाओ		= gxfb_हटाओ,
	.driver.pm	= &gxfb_pm_ops,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक __init gxfb_setup(अक्षर *options)
अणु

	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;

		mode_option = opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init gxfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("gxfb", &option))
		वापस -ENODEV;

	gxfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&gxfb_driver);
पूर्ण

अटल व्योम __निकास gxfb_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&gxfb_driver);
पूर्ण

module_init(gxfb_init);
module_निकास(gxfb_cleanup);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "video mode (<x>x<y>[-<bpp>][@<refr>])");

module_param(vram, पूर्णांक, 0);
MODULE_PARM_DESC(vram, "video memory size");

module_param(vt_चयन, पूर्णांक, 0);
MODULE_PARM_DESC(vt_चयन, "enable VT switch during suspend/resume");

MODULE_DESCRIPTION("Framebuffer driver for the AMD Geode GX");
MODULE_LICENSE("GPL");
