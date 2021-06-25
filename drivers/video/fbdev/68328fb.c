<शैली गुरु>
/*
 *  linux/drivers/video/68328fb.c -- Low level implementation of the
 *                                   mc68x328 LCD frame buffer device
 *
 *	Copyright (C) 2003 Georges Menie
 *
 *  This driver assumes an alपढ़ोy configured controller (e.g. from config.c)
 *  Keep the code clean of board specअगरic initialization.
 *
 *  This code has not been tested with colors, colormap management functions
 *  are minimal (no colormap data written to the 68328 रेजिस्टरs...)
 *
 *  initial version of this driver:
 *    Copyright (C) 1998,1999 Kenneth Albanowski <kjahds@kjahds.com>,
 *                            The Silver Hammer Group, Ltd.
 *
 *  this version is based on :
 *
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
#समावेश <linux/uaccess.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>

#अगर defined(CONFIG_M68VZ328)
#समावेश <यंत्र/MC68VZ328.h>
#या_अगर defined(CONFIG_M68EZ328)
#समावेश <यंत्र/MC68EZ328.h>
#या_अगर defined(CONFIG_M68328)
#समावेश <यंत्र/MC68328.h>
#अन्यथा
#त्रुटि wrong architecture क्रम the MC68x328 frame buffer device
#पूर्ण_अगर

अटल u_दीर्घ videomemory;
अटल u_दीर्घ videomemorysize;

अटल काष्ठा fb_info fb_info;
अटल u32 mc68x328fb_pseuकरो_palette[16];

अटल काष्ठा fb_var_screeninfo mc68x328fb_शेष __initdata = अणु
	.red =		अणु 0, 8, 0 पूर्ण,
      	.green =	अणु 0, 8, 0 पूर्ण,
      	.blue =		अणु 0, 8, 0 पूर्ण,
      	.activate =	FB_ACTIVATE_TEST,
      	.height =	-1,
      	.width =	-1,
      	.pixघड़ी =	20000,
      	.left_margin =	64,
      	.right_margin =	64,
      	.upper_margin =	32,
      	.lower_margin =	32,
      	.hsync_len =	64,
      	.vsync_len =	2,
      	.vmode =	FB_VMODE_NONINTERLACED,
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo mc68x328fb_fix __initस्थिर = अणु
	.id =		"68328fb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	1,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

    /*
     *  Interface used by the world
     */
पूर्णांक mc68x328fb_init(व्योम);
पूर्णांक mc68x328fb_setup(अक्षर *);

अटल पूर्णांक mc68x328fb_check_var(काष्ठा fb_var_screeninfo *var,
			 काष्ठा fb_info *info);
अटल पूर्णांक mc68x328fb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक mc68x328fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			 u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक mc68x328fb_pan_display(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info);
अटल पूर्णांक mc68x328fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);

अटल स्थिर काष्ठा fb_ops mc68x328fb_ops = अणु
	.fb_check_var	= mc68x328fb_check_var,
	.fb_set_par	= mc68x328fb_set_par,
	.fb_setcolreg	= mc68x328fb_setcolreg,
	.fb_pan_display	= mc68x328fb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_mmap	= mc68x328fb_mmap,
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

अटल पूर्णांक mc68x328fb_check_var(काष्ठा fb_var_screeninfo *var,
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
		var->red.offset = 0;
		var->red.length = 1;
		var->green.offset = 0;
		var->green.length = 1;
		var->blue.offset = 0;
		var->blue.length = 1;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
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
अटल पूर्णांक mc68x328fb_set_par(काष्ठा fb_info *info)
अणु
	info->fix.line_length = get_line_length(info->var.xres_भव,
						info->var.bits_per_pixel);
	वापस 0;
पूर्ण

    /*
     *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
     *  rounded करोwn to the hardware's capabilities (according to the
     *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
     */

अटल पूर्णांक mc68x328fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
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
	 *    uses offset = 0 && length = RAMDAC रेजिस्टर width.
	 *    var->अणुcolorपूर्ण.offset is 0
	 *    var->अणुcolorपूर्ण.length contains width of DAC
	 *    cmap is not used
	 *    RAMDAC[X] is programmed to (red, green, blue)
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

अटल पूर्णांक mc68x328fb_pan_display(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->yoffset < 0
		    || var->yoffset >= info->var.yres_भव
		    || var->xoffset)
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

अटल पूर्णांक mc68x328fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
#अगर_अघोषित MMU
	/* this is uClinux (no MMU) specअगरic code */

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_start = videomemory;

	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

पूर्णांक __init mc68x328fb_setup(अक्षर *options)
अणु
	अगर (!options || !*options)
		वापस 1;
	वापस 1;
पूर्ण

    /*
     *  Initialisation
     */

पूर्णांक __init mc68x328fb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("68328fb", &option))
		वापस -ENODEV;
	mc68x328fb_setup(option);
#पूर्ण_अगर
	/*
	 *  initialize the शेष mode from the LCD controller रेजिस्टरs
	 */
	mc68x328fb_शेष.xres = LXMAX;
	mc68x328fb_शेष.yres = LYMAX+1;
	mc68x328fb_शेष.xres_भव = mc68x328fb_शेष.xres;
	mc68x328fb_शेष.yres_भव = mc68x328fb_शेष.yres;
	mc68x328fb_शेष.bits_per_pixel = 1 + (LPICF & 0x01);
	videomemory = LSSA;
	videomemorysize = (mc68x328fb_शेष.xres_भव+7) / 8 *
		mc68x328fb_शेष.yres_भव * mc68x328fb_शेष.bits_per_pixel;

	fb_info.screen_base = (व्योम *)videomemory;
	fb_info.fbops = &mc68x328fb_ops;
	fb_info.var = mc68x328fb_शेष;
	fb_info.fix = mc68x328fb_fix;
	fb_info.fix.smem_start = videomemory;
	fb_info.fix.smem_len = videomemorysize;
	fb_info.fix.line_length =
		get_line_length(mc68x328fb_शेष.xres_भव, mc68x328fb_शेष.bits_per_pixel);
	fb_info.fix.visual = (mc68x328fb_शेष.bits_per_pixel) == 1 ?
		FB_VISUAL_MONO10 : FB_VISUAL_PSEUDOCOLOR;
	अगर (fb_info.var.bits_per_pixel == 1) अणु
		fb_info.var.red.length = fb_info.var.green.length = fb_info.var.blue.length = 1;
		fb_info.var.red.offset = fb_info.var.green.offset = fb_info.var.blue.offset = 0;
	पूर्ण
	fb_info.pseuकरो_palette = &mc68x328fb_pseuकरो_palette;
	fb_info.flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	अगर (fb_alloc_cmap(&fb_info.cmap, 256, 0))
		वापस -ENOMEM;

	अगर (रेजिस्टर_framebuffer(&fb_info) < 0) अणु
		fb_dealloc_cmap(&fb_info.cmap);
		वापस -EINVAL;
	पूर्ण

	fb_info(&fb_info, "%s frame buffer device\n", fb_info.fix.id);
	fb_info(&fb_info, "%dx%dx%d at 0x%08lx\n",
		mc68x328fb_शेष.xres_भव,
		mc68x328fb_शेष.yres_भव,
		1 << mc68x328fb_शेष.bits_per_pixel, videomemory);

	वापस 0;
पूर्ण

module_init(mc68x328fb_init);

#अगर_घोषित MODULE

अटल व्योम __निकास mc68x328fb_cleanup(व्योम)
अणु
	unरेजिस्टर_framebuffer(&fb_info);
	fb_dealloc_cmap(&fb_info.cmap);
पूर्ण

module_निकास(mc68x328fb_cleanup);

MODULE_LICENSE("GPL");
#पूर्ण_अगर				/* MODULE */
