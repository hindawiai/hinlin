<शैली गुरु>
/*
 *  linux/drivers/video/vfb.c -- Virtual frame buffer device
 *
 *      Copyright (C) 2002 James Simmons
 *
 *	Copyright (C) 1997 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/fb.h>
#समावेश <linux/init.h>

    /*
     *  RAM we reserve क्रम the frame buffer. This defines the maximum screen
     *  size
     *
     *  The शेष can be overridden अगर the driver is compiled as a module
     */

#घोषणा VIDEOMEMSIZE	(1*1024*1024)	/* 1 MB */

अटल व्योम *videomemory;
अटल u_दीर्घ videomemorysize = VIDEOMEMSIZE;
module_param(videomemorysize, uदीर्घ, 0);
MODULE_PARM_DESC(videomemorysize, "RAM available to frame buffer (in bytes)");

अटल अक्षर *mode_option = शून्य;
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Preferred video mode (e.g. 640x480-8@60)");

अटल स्थिर काष्ठा fb_videomode vfb_शेष = अणु
	.xres =		640,
	.yres =		480,
	.pixघड़ी =	20000,
	.left_margin =	64,
	.right_margin =	64,
	.upper_margin =	32,
	.lower_margin =	32,
	.hsync_len =	64,
	.vsync_len =	2,
	.vmode =	FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo vfb_fix = अणु
	.id =		"Virtual FB",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	1,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल bool vfb_enable __initdata = 0;	/* disabled by शेष */
module_param(vfb_enable, bool, 0);
MODULE_PARM_DESC(vfb_enable, "Enable Virtual FB driver");

अटल पूर्णांक vfb_check_var(काष्ठा fb_var_screeninfo *var,
			 काष्ठा fb_info *info);
अटल पूर्णांक vfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक vfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			 u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक vfb_pan_display(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info);
अटल पूर्णांक vfb_mmap(काष्ठा fb_info *info,
		    काष्ठा vm_area_काष्ठा *vma);

अटल स्थिर काष्ठा fb_ops vfb_ops = अणु
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो       = fb_sys_ग_लिखो,
	.fb_check_var	= vfb_check_var,
	.fb_set_par	= vfb_set_par,
	.fb_setcolreg	= vfb_setcolreg,
	.fb_pan_display	= vfb_pan_display,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_mmap	= vfb_mmap,
पूर्ण;

    /*
     *  Internal routines
     */

अटल u_दीर्घ get_line_length(पूर्णांक xres_भव, पूर्णांक bpp)
अणु
	u_दीर्घ length;

	length = xres_भव * bpp;
	length = (length + 31) & ~31;
	length >>= 3;
	वापस (length);
पूर्ण

    /*
     *  Setting the video mode has been split पूर्णांकo two parts.
     *  First part, xxxfb_check_var, must not ग_लिखो anything
     *  to hardware, it should only verअगरy and adjust var.
     *  This means it करोesn't alter par but it करोes use hardware
     *  data from it to check this var. 
     */

अटल पूर्णांक vfb_check_var(काष्ठा fb_var_screeninfo *var,
			 काष्ठा fb_info *info)
अणु
	u_दीर्घ line_length;

	/*
	 *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal!
	 *  as FB_VMODE_SMOOTH_XPAN is only used पूर्णांकernally
	 */

	अगर (var->vmode & FB_VMODE_CONUPDATE) अणु
		var->vmode |= FB_VMODE_YWRAP;
		var->xoffset = info->var.xoffset;
		var->yoffset = info->var.yoffset;
	पूर्ण

	/*
	 *  Some very basic checks
	 */
	अगर (!var->xres)
		var->xres = 1;
	अगर (!var->yres)
		var->yres = 1;
	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;
	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;
	अगर (var->bits_per_pixel <= 1)
		var->bits_per_pixel = 1;
	अन्यथा अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel <= 24)
		var->bits_per_pixel = 24;
	अन्यथा अगर (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;
	अन्यथा
		वापस -EINVAL;

	अगर (var->xres_भव < var->xoffset + var->xres)
		var->xres_भव = var->xoffset + var->xres;
	अगर (var->yres_भव < var->yoffset + var->yres)
		var->yres_भव = var->yoffset + var->yres;

	/*
	 *  Memory limit
	 */
	line_length =
	    get_line_length(var->xres_भव, var->bits_per_pixel);
	अगर (line_length * var->yres_भव > videomemorysize)
		वापस -ENOMEM;

	/*
	 * Now that we checked it we alter var. The reason being is that the video
	 * mode passed in might not work but slight changes to it might make it 
	 * work. This way we let the user know what is acceptable.
	 */
	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 16:		/* RGBA 5551 */
		अगर (var->transp.length) अणु
			var->red.offset = 0;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 5;
			var->blue.offset = 10;
			var->blue.length = 5;
			var->transp.offset = 15;
			var->transp.length = 1;
		पूर्ण अन्यथा अणु	/* RGB 565 */
			var->red.offset = 0;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 11;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		पूर्ण
		अवरोध;
	हाल 24:		/* RGB 888 */
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 16;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 32:		/* RGBA 8888 */
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 16;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	पूर्ण
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	वापस 0;
पूर्ण

/* This routine actually sets the video mode. It's in here where we
 * the hardware state info->par and fix which can be affected by the 
 * change in par. For this driver it करोesn't करो much. 
 */
अटल पूर्णांक vfb_set_par(काष्ठा fb_info *info)
अणु
	चयन (info->var.bits_per_pixel) अणु
	हाल 1:
		info->fix.visual = FB_VISUAL_MONO01;
		अवरोध;
	हाल 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 16:
	हाल 24:
	हाल 32:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	पूर्ण

	info->fix.line_length = get_line_length(info->var.xres_भव,
						info->var.bits_per_pixel);

	वापस 0;
पूर्ण

    /*
     *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
     *  rounded करोwn to the hardware's capabilities (according to the
     *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
     */

अटल पूर्णांक vfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			 u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno >= 256)	/* no. of hw रेजिस्टरs */
		वापस 1;
	/*
	 * Program hardware... करो anything you want with transp
	 */

	/* grayscale works only partially under directcolor */
	अगर (info->var.grayscale) अणु
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue =
		    (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	/* Directcolor:
	 *   var->अणुcolorपूर्ण.offset contains start of bitfield
	 *   var->अणुcolorपूर्ण.length contains length of bitfield
	 *   अणुhardwarespecअगरicपूर्ण contains width of RAMDAC
	 *   cmap[X] is programmed to (X << red.offset) | (X << green.offset) | (X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Pseuकरोcolor:
	 *    var->अणुcolorपूर्ण.offset is 0 unless the palette index takes less than
	 *                        bits_per_pixel bits and is stored in the upper
	 *                        bits of the pixel value
	 *    var->अणुcolorपूर्ण.length is set so that 1 << length is the number of available
	 *                        palette entries
	 *    cmap is not used
	 *    RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Truecolor:
	 *    करोes not use DAC. Usually 3 are present.
	 *    var->अणुcolorपूर्ण.offset contains start of bitfield
	 *    var->अणुcolorपूर्ण.length contains length of bitfield
	 *    cmap is programmed to (red << red.offset) | (green << green.offset) |
	 *                      (blue << blue.offset) | (transp << transp.offset)
	 *    RAMDAC करोes not exist
	 */
#घोषणा CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		transp = CNVT_TOHW(transp, info->var.transp.length);
		अवरोध;
	हाल FB_VISUAL_सूचीECTCOLOR:
		red = CNVT_TOHW(red, 8);	/* expect 8 bit DAC */
		green = CNVT_TOHW(green, 8);
		blue = CNVT_TOHW(blue, 8);
		/* hey, there is bug in transp handling... */
		transp = CNVT_TOHW(transp, 8);
		अवरोध;
	पूर्ण
#अघोषित CNVT_TOHW
	/* Truecolor has hardware independent palette */
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 v;

		अगर (regno >= 16)
			वापस 1;

		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset) |
		    (transp << info->var.transp.offset);
		चयन (info->var.bits_per_pixel) अणु
		हाल 8:
			अवरोध;
		हाल 16:
			((u32 *) (info->pseuकरो_palette))[regno] = v;
			अवरोध;
		हाल 24:
		हाल 32:
			((u32 *) (info->pseuकरो_palette))[regno] = v;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

    /*
     *  Pan or Wrap the Display
     *
     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
     */

अटल पूर्णांक vfb_pan_display(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->yoffset >= info->var.yres_भव ||
		    var->xoffset)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (var->xoffset + info->var.xres > info->var.xres_भव ||
		    var->yoffset + info->var.yres > info->var.yres_भव)
			वापस -EINVAL;
	पूर्ण
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	अगर (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		info->var.vmode &= ~FB_VMODE_YWRAP;
	वापस 0;
पूर्ण

    /*
     *  Most drivers करोn't need their own mmap function 
     */

अटल पूर्णांक vfb_mmap(काष्ठा fb_info *info,
		    काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस remap_vदो_स्मृति_range(vma, (व्योम *)info->fix.smem_start, vma->vm_pgoff);
पूर्ण

#अगर_अघोषित MODULE
/*
 * The भव framebuffer driver is only enabled अगर explicitly
 * requested by passing 'video=vfb:' (or any actual options).
 */
अटल पूर्णांक __init vfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	vfb_enable = 0;

	अगर (!options)
		वापस 1;

	vfb_enable = 1;

	अगर (!*options)
		वापस 1;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		/* Test disable क्रम backwards compatibility */
		अगर (!म_भेद(this_opt, "disable"))
			vfb_enable = 0;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

    /*
     *  Initialisation
     */

अटल पूर्णांक vfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	अचिन्हित पूर्णांक size = PAGE_ALIGN(videomemorysize);
	पूर्णांक retval = -ENOMEM;

	/*
	 * For real video cards we use ioremap.
	 */
	अगर (!(videomemory = vदो_स्मृति_32_user(size)))
		वापस retval;

	info = framebuffer_alloc(माप(u32) * 256, &dev->dev);
	अगर (!info)
		जाओ err;

	info->screen_base = (अक्षर __iomem *)videomemory;
	info->fbops = &vfb_ops;

	अगर (!fb_find_mode(&info->var, info, mode_option,
			  शून्य, 0, &vfb_शेष, 8))अणु
		fb_err(info, "Unable to find usable video mode.\n");
		retval = -EINVAL;
		जाओ err1;
	पूर्ण

	vfb_fix.smem_start = (अचिन्हित दीर्घ) videomemory;
	vfb_fix.smem_len = videomemorysize;
	info->fix = vfb_fix;
	info->pseuकरो_palette = info->par;
	info->par = शून्य;
	info->flags = FBINFO_FLAG_DEFAULT;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0)
		जाओ err1;

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err2;
	platक्रमm_set_drvdata(dev, info);

	vfb_set_par(info);

	fb_info(info, "Virtual frame buffer device, using %ldK of video memory\n",
		videomemorysize >> 10);
	वापस 0;
err2:
	fb_dealloc_cmap(&info->cmap);
err1:
	framebuffer_release(info);
err:
	vमुक्त(videomemory);
	वापस retval;
पूर्ण

अटल पूर्णांक vfb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		vमुक्त(videomemory);
		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vfb_driver = अणु
	.probe	= vfb_probe,
	.हटाओ = vfb_हटाओ,
	.driver = अणु
		.name	= "vfb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *vfb_device;

अटल पूर्णांक __init vfb_init(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("vfb", &option))
		वापस -ENODEV;
	vfb_setup(option);
#पूर्ण_अगर

	अगर (!vfb_enable)
		वापस -ENXIO;

	ret = platक्रमm_driver_रेजिस्टर(&vfb_driver);

	अगर (!ret) अणु
		vfb_device = platक्रमm_device_alloc("vfb", 0);

		अगर (vfb_device)
			ret = platक्रमm_device_add(vfb_device);
		अन्यथा
			ret = -ENOMEM;

		अगर (ret) अणु
			platक्रमm_device_put(vfb_device);
			platक्रमm_driver_unरेजिस्टर(&vfb_driver);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

module_init(vfb_init);

#अगर_घोषित MODULE
अटल व्योम __निकास vfb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(vfb_device);
	platक्रमm_driver_unरेजिस्टर(&vfb_driver);
पूर्ण

module_निकास(vfb_निकास);

MODULE_LICENSE("GPL");
#पूर्ण_अगर				/* MODULE */
