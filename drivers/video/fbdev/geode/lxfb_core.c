<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Geode LX framebuffer driver.
 *
 * Copyright (C) 2007 Advanced Micro Devices, Inc.
 * Built from gxfb (which is Copyright (C) 2006 Arcom Control Systems Ltd.)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/console.h>
#समावेश <linux/mm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/olpc.h>

#समावेश "lxfb.h"

अटल अक्षर *mode_option;
अटल पूर्णांक noclear, nopanel, nocrt;
अटल पूर्णांक vram;
अटल पूर्णांक vt_चयन;

/* Most of these modes are sorted in ascending order, but
 * since the first entry in this table is the "default" mode,
 * we try to make it something sane - 640x480-60 is sane
 */

अटल काष्ठा fb_videomode geode_modedb[] = अणु
	/* 640x480-60 */
	अणु शून्य, 60, 640, 480, 39682, 48, 8, 25, 2, 88, 2,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x400-70 */
	अणु शून्य, 70, 640, 400, 39770, 40, 8, 28, 5, 96, 2,
	  FB_SYNC_HOR_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-70 */
	अणु शून्य, 70, 640, 480, 35014, 88, 24, 15, 2, 64, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-72 */
	अणु शून्य, 72, 640, 480, 32102, 120, 16, 20, 1, 40, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-75 */
	अणु शून्य, 75, 640, 480, 31746, 120, 16, 16, 1, 64, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-85 */
	अणु शून्य, 85, 640, 480, 27780, 80, 56, 25, 1, 56, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-90 */
	अणु शून्य, 90, 640, 480, 26392, 96, 32, 22, 1, 64, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-100 */
	अणु शून्य, 100, 640, 480, 23167, 104, 40, 25, 1, 64, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 640x480-60 */
	अणु शून्य, 60, 640, 480, 39682, 48, 16, 25, 10, 88, 2,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-56 */
	अणु शून्य, 56, 800, 600, 27901, 128, 24, 22, 1, 72, 2,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-60 */
	अणु शून्य, 60, 800, 600, 25131, 72, 32, 23, 1, 136, 4,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-70 */
	अणु शून्य, 70, 800, 600, 21873, 120, 40, 21, 4, 80, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-72 */
	अणु शून्य, 72, 800, 600, 20052, 64, 56, 23, 37, 120, 6,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-75 */
	अणु शून्य, 75, 800, 600, 20202, 160, 16, 21, 1, 80, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-85 */
	अणु शून्य, 85, 800, 600, 17790, 152, 32, 27, 1, 64, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-90 */
	अणु शून्य, 90, 800, 600, 16648, 128, 40, 28, 1, 88, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-100 */
	अणु शून्य, 100, 800, 600, 14667, 136, 48, 27, 1, 88, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 800x600-60 */
	अणु शून्य, 60, 800, 600, 25131, 88, 40, 23, 1, 128, 4,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-60 */
	अणु शून्य, 60, 1024, 768, 15385, 160, 24, 29, 3, 136, 6,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-70 */
	अणु शून्य, 70, 1024, 768, 13346, 144, 24, 29, 3, 136, 6,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-72 */
	अणु शून्य, 72, 1024, 768, 12702, 168, 56, 29, 4, 112, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-75 */
	अणु शून्य, 75, 1024, 768, 12703, 176, 16, 28, 1, 96, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-85 */
	अणु शून्य, 85, 1024, 768, 10581, 208, 48, 36, 1, 96, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-90 */
	अणु शून्य, 90, 1024, 768, 9981, 176, 64, 37, 1, 112, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-100 */
	अणु शून्य, 100, 1024, 768, 8825, 184, 72, 42, 1, 112, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1024x768-60 */
	अणु शून्य, 60, 1024, 768, 15385, 160, 24, 29, 3, 136, 6,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-60 */
	अणु शून्य, 60, 1152, 864, 12251, 184, 64, 27, 1, 120, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-70 */
	अणु शून्य, 70, 1152, 864, 10254, 192, 72, 32, 8, 120, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-72 */
	अणु शून्य, 72, 1152, 864, 9866, 200, 72, 33, 7, 128, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-75 */
	अणु शून्य, 75, 1152, 864, 9259, 256, 64, 32, 1, 128, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-85 */
	अणु शून्य, 85, 1152, 864, 8357, 200, 72, 37, 3, 128, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-90 */
	अणु शून्य, 90, 1152, 864, 7719, 208, 80, 42, 9, 128, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-100 */
	अणु शून्य, 100, 1152, 864, 6947, 208, 80, 48, 3, 128, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1152x864-60 */
	अणु शून्य, 60, 1152, 864, 12251, 184, 64, 27, 1, 120, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-60 */
	अणु शून्य, 60, 1280, 1024, 9262, 248, 48, 38, 1, 112, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-70 */
	अणु शून्य, 70, 1280, 1024, 7719, 224, 88, 38, 6, 136, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-72 */
	अणु शून्य, 72, 1280, 1024, 7490, 224, 88, 39, 7, 136, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-75 */
	अणु शून्य, 75, 1280, 1024, 7409, 248, 16, 38, 1, 144, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-85 */
	अणु शून्य, 85, 1280, 1024, 6351, 224, 64, 44, 1, 160, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-90 */
	अणु शून्य, 90, 1280, 1024, 5791, 240, 96, 51, 12, 144, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-100 */
	अणु शून्य, 100, 1280, 1024, 5212, 240, 96, 57, 6, 144, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1280x1024-60 */
	अणु शून्य, 60, 1280, 1024, 9262, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-60 */
	अणु शून्य, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-70 */
	अणु शून्य, 70, 1600, 1200, 5291, 304, 64, 46, 1, 192, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-72 */
	अणु शून्य, 72, 1600, 1200, 5053, 288, 112, 47, 13, 176, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-75 */
	अणु शून्य, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-85 */
	अणु शून्य, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-90 */
	अणु शून्य, 90, 1600, 1200, 3981, 304, 128, 60, 1, 176, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-100 */
	अणु शून्य, 100, 1600, 1200, 3563, 304, 128, 67, 1, 176, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1600x1200-60 */
	अणु शून्य, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1920x1440-60 */
	अणु शून्य, 60, 1920, 1440, 4273, 344, 128, 56, 1, 208, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1920x1440-70 */
	अणु शून्य, 70, 1920, 1440, 3593, 360, 152, 55, 8, 208, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1920x1440-72 */
	अणु शून्य, 72, 1920, 1440, 3472, 360, 152, 68, 4, 208, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1920x1440-75 */
	अणु शून्य, 75, 1920, 1440, 3367, 352, 144, 56, 1, 224, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
	/* 1920x1440-85 */
	अणु शून्य, 85, 1920, 1440, 2929, 368, 152, 68, 1, 216, 3,
	  0, FB_VMODE_NONINTERLACED, 0 पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode olpc_dcon_modedb[] = अणु
	/* The only mode the DCON has is 1200x900 */
	अणु शून्य, 50, 1200, 900, 17460, 24, 8, 4, 5, 8, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, 0 पूर्ण
पूर्ण;

अटल व्योम get_modedb(काष्ठा fb_videomode **modedb, अचिन्हित पूर्णांक *size)
अणु
	अगर (olpc_has_dcon()) अणु
		*modedb = (काष्ठा fb_videomode *) olpc_dcon_modedb;
		*size = ARRAY_SIZE(olpc_dcon_modedb);
	पूर्ण अन्यथा अणु
		*modedb = (काष्ठा fb_videomode *) geode_modedb;
		*size = ARRAY_SIZE(geode_modedb);
	पूर्ण
पूर्ण

अटल पूर्णांक lxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अगर (var->xres > 1920 || var->yres > 1440)
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
	अगर ((lx_get_pitch(var->xres, var->bits_per_pixel) * var->yres)
	    > info->fix.smem_len)
	  वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक lxfb_set_par(काष्ठा fb_info *info)
अणु
	अगर (info->var.bits_per_pixel > 8)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = lx_get_pitch(info->var.xres,
		info->var.bits_per_pixel);

	lx_set_mode(info);
	वापस 0;
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक lxfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
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

		lx_set_palette_reg(info, regno, red, green, blue);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lxfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	वापस lx_blank_display(info, blank_mode);
पूर्ण


अटल पूर्णांक lxfb_map_video_memory(काष्ठा fb_info *info, काष्ठा pci_dev *dev)
अणु
	काष्ठा lxfb_par *par = info->par;
	पूर्णांक ret;

	ret = pci_enable_device(dev);

	अगर (ret)
		वापस ret;

	ret = pci_request_region(dev, 0, "lxfb-framebuffer");

	अगर (ret)
		वापस ret;

	ret = pci_request_region(dev, 1, "lxfb-gp");

	अगर (ret)
		वापस ret;

	ret = pci_request_region(dev, 2, "lxfb-vg");

	अगर (ret)
		वापस ret;

	ret = pci_request_region(dev, 3, "lxfb-vp");

	अगर (ret)
		वापस ret;

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = vram ? vram : lx_framebuffer_size();

	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);

	ret = -ENOMEM;

	अगर (info->screen_base == शून्य)
		वापस ret;

	par->gp_regs = pci_ioremap_bar(dev, 1);

	अगर (par->gp_regs == शून्य)
		वापस ret;

	par->dc_regs = pci_ioremap_bar(dev, 2);

	अगर (par->dc_regs == शून्य)
		वापस ret;

	par->vp_regs = pci_ioremap_bar(dev, 3);

	अगर (par->vp_regs == शून्य)
		वापस ret;

	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
	ग_लिखो_dc(par, DC_GLIU0_MEM_OFFSET, info->fix.smem_start & 0xFF000000);
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);

	dev_info(&dev->dev, "%d KB of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops lxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= lxfb_check_var,
	.fb_set_par	= lxfb_set_par,
	.fb_setcolreg	= lxfb_setcolreg,
	.fb_blank       = lxfb_blank,
	/* No HW acceleration क्रम now. */
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल काष्ठा fb_info *lxfb_init_fbinfo(काष्ठा device *dev)
अणु
	काष्ठा lxfb_par *par;
	काष्ठा fb_info *info;

	/* Alloc enough space क्रम the pseuकरो palette. */
	info = framebuffer_alloc(माप(काष्ठा lxfb_par) + माप(u32) * 16,
				 dev);
	अगर (!info)
		वापस शून्य;

	par = info->par;

	म_नकल(info->fix.id, "Geode LX");

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

	info->fbops		= &lxfb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseuकरो_palette	= (व्योम *)par + माप(काष्ठा lxfb_par);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		framebuffer_release(info);
		वापस शून्य;
	पूर्ण

	info->var.grayscale	= 0;

	वापस info;
पूर्ण

अटल पूर्णांक __maybe_unused lxfb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);

	console_lock();
	lx_घातerकरोwn(info);
	fb_set_suspend(info, 1);
	console_unlock();

	/* there's no poपूर्णांक in setting PCI states; we emulate PCI, so
	 * we करोn't end up getting घातer savings anyways */

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lxfb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	console_lock();
	ret = lx_घातerup(info);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "lxfb:  power up failed!\n");
		वापस ret;
	पूर्ण

	fb_set_suspend(info, 0);
	console_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक lxfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा lxfb_par *par;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	काष्ठा fb_videomode *modedb_ptr;
	अचिन्हित पूर्णांक modedb_size;

	info = lxfb_init_fbinfo(&pdev->dev);

	अगर (info == शून्य)
		वापस -ENOMEM;

	par = info->par;

	ret = lxfb_map_video_memory(info, pdev);

	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to map frame buffer or controller registers\n");
		जाओ err;
	पूर्ण

	/* Set up the desired outमाला_दो */

	par->output = 0;
	par->output |= (nopanel) ? 0 : OUTPUT_PANEL;
	par->output |= (nocrt) ? 0 : OUTPUT_CRT;

	/* Set up the mode database */

	get_modedb(&modedb_ptr, &modedb_size);
	ret = fb_find_mode(&info->var, info, mode_option,
			   modedb_ptr, modedb_size, शून्य, 16);

	अगर (ret == 0 || ret == 4) अणु
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Clear the screen of garbage, unless noclear was specअगरied,
	 * in which हाल we assume the user knows what he is करोing */

	अगर (!noclear)
		स_रखो_io(info->screen_base, 0, info->fix.smem_len);

	/* Set the mode */

	lxfb_check_var(&info->var, info);
	lxfb_set_par(info);

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
	अगर (par->gp_regs) अणु
		iounmap(par->gp_regs);
		pci_release_region(pdev, 1);
	पूर्ण
	अगर (par->dc_regs) अणु
		iounmap(par->dc_regs);
		pci_release_region(pdev, 2);
	पूर्ण
	अगर (par->vp_regs) अणु
		iounmap(par->vp_regs);
		pci_release_region(pdev, 3);
	पूर्ण

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	वापस ret;
पूर्ण

अटल व्योम lxfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा lxfb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);

	iounmap(info->screen_base);
	pci_release_region(pdev, 0);

	iounmap(par->gp_regs);
	pci_release_region(pdev, 1);

	iounmap(par->dc_regs);
	pci_release_region(pdev, 2);

	iounmap(par->vp_regs);
	pci_release_region(pdev, 3);

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
पूर्ण

अटल काष्ठा pci_device_id lxfb_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LX_VIDEO) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, lxfb_id_table);

अटल स्थिर काष्ठा dev_pm_ops lxfb_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= lxfb_suspend,
	.resume		= lxfb_resume,
	.मुक्तze		= शून्य,
	.thaw		= lxfb_resume,
	.घातeroff	= शून्य,
	.restore	= lxfb_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pci_driver lxfb_driver = अणु
	.name		= "lxfb",
	.id_table	= lxfb_id_table,
	.probe		= lxfb_probe,
	.हटाओ		= lxfb_हटाओ,
	.driver.pm	= &lxfb_pm_ops,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक __init lxfb_setup(अक्षर *options)
अणु
	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;

		अगर (!म_भेद(opt, "noclear"))
			noclear = 1;
		अन्यथा अगर (!म_भेद(opt, "nopanel"))
			nopanel = 1;
		अन्यथा अगर (!म_भेद(opt, "nocrt"))
			nocrt = 1;
		अन्यथा
			mode_option = opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init lxfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("lxfb", &option))
		वापस -ENODEV;

	lxfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&lxfb_driver);
पूर्ण
अटल व्योम __निकास lxfb_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&lxfb_driver);
पूर्ण

module_init(lxfb_init);
module_निकास(lxfb_cleanup);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "video mode (<x>x<y>[-<bpp>][@<refr>])");

module_param(vram, पूर्णांक, 0);
MODULE_PARM_DESC(vram, "video memory size");

module_param(vt_चयन, पूर्णांक, 0);
MODULE_PARM_DESC(vt_चयन, "enable VT switch during suspend/resume");

MODULE_DESCRIPTION("Framebuffer driver for the AMD Geode LX");
MODULE_LICENSE("GPL");
