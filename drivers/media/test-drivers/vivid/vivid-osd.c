<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-osd.c - osd support क्रम testing overlays.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/font.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/fb.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-common.h>

#समावेश "vivid-core.h"
#समावेश "vivid-osd.h"

#घोषणा MAX_OSD_WIDTH  720
#घोषणा MAX_OSD_HEIGHT 576

/*
 * Order: white, yellow, cyan, green, magenta, red, blue, black,
 * and same again with the alpha bit set (अगर any)
 */
अटल स्थिर u16 rgb555[16] = अणु
	0x7fff, 0x7fe0, 0x03ff, 0x03e0, 0x7c1f, 0x7c00, 0x001f, 0x0000,
	0xffff, 0xffe0, 0x83ff, 0x83e0, 0xfc1f, 0xfc00, 0x801f, 0x8000
पूर्ण;

अटल स्थिर u16 rgb565[16] = अणु
	0xffff, 0xffe0, 0x07ff, 0x07e0, 0xf81f, 0xf800, 0x001f, 0x0000,
	0xffff, 0xffe0, 0x07ff, 0x07e0, 0xf81f, 0xf800, 0x001f, 0x0000
पूर्ण;

व्योम vivid_clear_fb(काष्ठा vivid_dev *dev)
अणु
	व्योम *p = dev->video_vbase;
	स्थिर u16 *rgb = rgb555;
	अचिन्हित x, y;

	अगर (dev->fb_defined.green.length == 6)
		rgb = rgb565;

	क्रम (y = 0; y < dev->display_height; y++) अणु
		u16 *d = p;

		क्रम (x = 0; x < dev->display_width; x++)
			d[x] = rgb[(y / 16 + x / 16) % 16];
		p += dev->display_byte_stride;
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक vivid_fb_ioctl(काष्ठा fb_info *info, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vivid_dev *dev = (काष्ठा vivid_dev *)info->par;

	चयन (cmd) अणु
	हाल FBIOGET_VBLANK: अणु
		काष्ठा fb_vblank vblank;

		स_रखो(&vblank, 0, माप(vblank));
		vblank.flags = FB_VBLANK_HAVE_COUNT | FB_VBLANK_HAVE_VCOUNT |
			FB_VBLANK_HAVE_VSYNC;
		vblank.count = 0;
		vblank.vcount = 0;
		vblank.hcount = 0;
		अगर (copy_to_user((व्योम __user *)arg, &vblank, माप(vblank)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	शेष:
		dprपूर्णांकk(dev, 1, "Unknown ioctl %08x\n", cmd);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Framebuffer device handling */

अटल पूर्णांक vivid_fb_set_var(काष्ठा vivid_dev *dev, काष्ठा fb_var_screeninfo *var)
अणु
	dprपूर्णांकk(dev, 1, "vivid_fb_set_var\n");

	अगर (var->bits_per_pixel != 16) अणु
		dprपूर्णांकk(dev, 1, "vivid_fb_set_var - Invalid bpp\n");
		वापस -EINVAL;
	पूर्ण
	dev->display_byte_stride = var->xres * dev->bytes_per_pixel;

	वापस 0;
पूर्ण

अटल पूर्णांक vivid_fb_get_fix(काष्ठा vivid_dev *dev, काष्ठा fb_fix_screeninfo *fix)
अणु
	dprपूर्णांकk(dev, 1, "vivid_fb_get_fix\n");
	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));
	strscpy(fix->id, "vioverlay fb", माप(fix->id));
	fix->smem_start = dev->video_pbase;
	fix->smem_len = dev->video_buffer_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->line_length = dev->display_byte_stride;
	fix->accel = FB_ACCEL_NONE;
	वापस 0;
पूर्ण

/* Check the requested display mode, वापसing -EINVAL अगर we can't
   handle it. */

अटल पूर्णांक _vivid_fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा vivid_dev *dev)
अणु
	dprपूर्णांकk(dev, 1, "vivid_fb_check_var\n");

	var->bits_per_pixel = 16;
	अगर (var->green.length == 5) अणु
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
	पूर्ण अन्यथा अणु
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
	पूर्ण
	var->xoffset = var->yoffset = 0;
	var->left_margin = var->upper_margin = 0;
	var->nonstd = 0;

	var->vmode &= ~FB_VMODE_MASK;
	var->vmode |= FB_VMODE_NONINTERLACED;

	/* Dummy values */
	var->hsync_len = 24;
	var->vsync_len = 2;
	var->pixघड़ी = 84316;
	var->right_margin = 776;
	var->lower_margin = 591;
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा vivid_dev *dev = (काष्ठा vivid_dev *) info->par;

	dprपूर्णांकk(dev, 1, "vivid_fb_check_var\n");
	वापस _vivid_fb_check_var(var, dev);
पूर्ण

अटल पूर्णांक vivid_fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_fb_set_par(काष्ठा fb_info *info)
अणु
	पूर्णांक rc = 0;
	काष्ठा vivid_dev *dev = (काष्ठा vivid_dev *) info->par;

	dprपूर्णांकk(dev, 1, "vivid_fb_set_par\n");

	rc = vivid_fb_set_var(dev, &info->var);
	vivid_fb_get_fix(dev, &info->fix);
	वापस rc;
पूर्ण

अटल पूर्णांक vivid_fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
				अचिन्हित blue, अचिन्हित transp,
				काष्ठा fb_info *info)
अणु
	u32 color, *palette;

	अगर (regno >= info->cmap.len)
		वापस -EINVAL;

	color = ((transp & 0xFF00) << 16) | ((red & 0xFF00) << 8) |
		 (green & 0xFF00) | ((blue & 0xFF00) >> 8);
	अगर (regno >= 16)
		वापस -EINVAL;

	palette = info->pseuकरो_palette;
	अगर (info->var.bits_per_pixel == 16) अणु
		चयन (info->var.green.length) अणु
		हाल 6:
			color = (red & 0xf800) |
				((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
			अवरोध;
		हाल 5:
			color = ((red & 0xf800) >> 1) |
				((green & 0xf800) >> 6) |
				((blue & 0xf800) >> 11) |
				(transp ? 0x8000 : 0);
			अवरोध;
		पूर्ण
	पूर्ण
	palette[regno] = color;
	वापस 0;
पूर्ण

/* We करोn't really support blanking. All this करोes is enable or
   disable the OSD. */
अटल पूर्णांक vivid_fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा vivid_dev *dev = (काष्ठा vivid_dev *)info->par;

	dprपूर्णांकk(dev, 1, "Set blanking mode : %d\n", blank_mode);
	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		अवरोध;
	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops vivid_fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var   = vivid_fb_check_var,
	.fb_set_par     = vivid_fb_set_par,
	.fb_setcolreg   = vivid_fb_setcolreg,
	.fb_fillrect    = cfb_fillrect,
	.fb_copyarea    = cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
	.fb_cursor      = शून्य,
	.fb_ioctl       = vivid_fb_ioctl,
	.fb_pan_display = vivid_fb_pan_display,
	.fb_blank       = vivid_fb_blank,
पूर्ण;

/* Initialization */


/* Setup our initial video mode */
अटल पूर्णांक vivid_fb_init_vidmode(काष्ठा vivid_dev *dev)
अणु
	काष्ठा v4l2_rect start_winकरोw;

	/* Color mode */

	dev->bits_per_pixel = 16;
	dev->bytes_per_pixel = dev->bits_per_pixel / 8;

	start_winकरोw.width = MAX_OSD_WIDTH;
	start_winकरोw.left = 0;

	dev->display_byte_stride = start_winकरोw.width * dev->bytes_per_pixel;

	/* Vertical size & position */

	start_winकरोw.height = MAX_OSD_HEIGHT;
	start_winकरोw.top = 0;

	dev->display_width = start_winकरोw.width;
	dev->display_height = start_winकरोw.height;

	/* Generate a valid fb_var_screeninfo */

	dev->fb_defined.xres = dev->display_width;
	dev->fb_defined.yres = dev->display_height;
	dev->fb_defined.xres_भव = dev->display_width;
	dev->fb_defined.yres_भव = dev->display_height;
	dev->fb_defined.bits_per_pixel = dev->bits_per_pixel;
	dev->fb_defined.vmode = FB_VMODE_NONINTERLACED;
	dev->fb_defined.left_margin = start_winकरोw.left + 1;
	dev->fb_defined.upper_margin = start_winकरोw.top + 1;
	dev->fb_defined.accel_flags = FB_ACCEL_NONE;
	dev->fb_defined.nonstd = 0;
	/* set शेष to 1:5:5:5 */
	dev->fb_defined.green.length = 5;

	/* We've filled in the most data, let the usual mode check
	   routine fill in the rest. */
	_vivid_fb_check_var(&dev->fb_defined, dev);

	/* Generate valid fb_fix_screeninfo */

	vivid_fb_get_fix(dev, &dev->fb_fix);

	/* Generate valid fb_info */

	dev->fb_info.node = -1;
	dev->fb_info.flags = FBINFO_FLAG_DEFAULT;
	dev->fb_info.par = dev;
	dev->fb_info.var = dev->fb_defined;
	dev->fb_info.fix = dev->fb_fix;
	dev->fb_info.screen_base = (u8 __iomem *)dev->video_vbase;
	dev->fb_info.fbops = &vivid_fb_ops;

	/* Supply some monitor specs. Bogus values will करो क्रम now */
	dev->fb_info.monspecs.hfmin = 8000;
	dev->fb_info.monspecs.hfmax = 70000;
	dev->fb_info.monspecs.vfmin = 10;
	dev->fb_info.monspecs.vfmax = 100;

	/* Allocate color map */
	अगर (fb_alloc_cmap(&dev->fb_info.cmap, 256, 1)) अणु
		pr_err("abort, unable to alloc cmap\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate the pseuकरो palette */
	dev->fb_info.pseuकरो_palette = kदो_स्मृति_array(16, माप(u32), GFP_KERNEL);

	वापस dev->fb_info.pseuकरो_palette ? 0 : -ENOMEM;
पूर्ण

/* Release any memory we've grabbed */
व्योम vivid_fb_release_buffers(काष्ठा vivid_dev *dev)
अणु
	अगर (dev->video_vbase == शून्य)
		वापस;

	/* Release cmap */
	अगर (dev->fb_info.cmap.len)
		fb_dealloc_cmap(&dev->fb_info.cmap);

	/* Release pseuकरो palette */
	kमुक्त(dev->fb_info.pseuकरो_palette);
	kमुक्त(dev->video_vbase);
पूर्ण

/* Initialize the specअगरied card */

पूर्णांक vivid_fb_init(काष्ठा vivid_dev *dev)
अणु
	पूर्णांक ret;

	dev->video_buffer_size = MAX_OSD_HEIGHT * MAX_OSD_WIDTH * 2;
	dev->video_vbase = kzalloc(dev->video_buffer_size, GFP_KERNEL | GFP_DMA32);
	अगर (dev->video_vbase == शून्य)
		वापस -ENOMEM;
	dev->video_pbase = virt_to_phys(dev->video_vbase);

	pr_info("Framebuffer at 0x%lx, mapped to 0x%p, size %dk\n",
			dev->video_pbase, dev->video_vbase,
			dev->video_buffer_size / 1024);

	/* Set the startup video mode inक्रमmation */
	ret = vivid_fb_init_vidmode(dev);
	अगर (ret) अणु
		vivid_fb_release_buffers(dev);
		वापस ret;
	पूर्ण

	vivid_clear_fb(dev);

	/* Register the framebuffer */
	अगर (रेजिस्टर_framebuffer(&dev->fb_info) < 0) अणु
		vivid_fb_release_buffers(dev);
		वापस -EINVAL;
	पूर्ण

	/* Set the card to the requested mode */
	vivid_fb_set_par(&dev->fb_info);
	वापस 0;

पूर्ण
