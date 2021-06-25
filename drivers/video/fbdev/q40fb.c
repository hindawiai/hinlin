<शैली गुरु>
/*
 * linux/drivers/video/q40fb.c -- Q40 frame buffer device
 *
 * Copyright (C) 2001
 *
 *      Riअक्षरd Zidlicky <rz@linux-m68k.org>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/q40_master.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>

#घोषणा Q40_PHYS_SCREEN_ADDR 0xFE800000

अटल काष्ठा fb_fix_screeninfo q40fb_fix = अणु
	.id		= "Q40",
	.smem_len	= 1024*1024,
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_TRUECOLOR,
	.line_length	= 1024*2,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo q40fb_var = अणु
	.xres		= 1024,
	.yres		= 512,
	.xres_भव	= 1024,
	.yres_भव	= 512,
	.bits_per_pixel	= 16,
    	.red		= अणु6, 5, 0पूर्ण,
	.green		= अणु11, 5, 0पूर्ण,
	.blue		= अणु0, 6, 0पूर्ण,
	.activate	= FB_ACTIVATE_NOW,
	.height		= 230,
	.width		= 300,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक q40fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
    /*
     *  Set a single color रेजिस्टर. The values supplied have a 16 bit
     *  magnitude.
     *  Return != 0 क्रम invalid regno.
     */

    अगर (regno > 255)
	    वापस 1;
    red>>=11;
    green>>=11;
    blue>>=10;

    अगर (regno < 16) अणु
	((u32 *)info->pseuकरो_palette)[regno] = ((red & 31) <<6) |
					       ((green & 31) << 11) |
					       (blue & 63);
    पूर्ण
    वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops q40fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= q40fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक q40fb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;

	अगर (!MACH_IS_Q40)
		वापस -ENXIO;

	/* mapped in q40/config.c */
	q40fb_fix.smem_start = Q40_PHYS_SCREEN_ADDR;

	info = framebuffer_alloc(माप(u32) * 16, &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	info->var = q40fb_var;
	info->fix = q40fb_fix;
	info->fbops = &q40fb_ops;
	info->flags = FBINFO_DEFAULT;  /* not as module क्रम now */
	info->pseuकरो_palette = info->par;
	info->par = शून्य;
	info->screen_base = (अक्षर *) q40fb_fix.smem_start;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		framebuffer_release(info);
		वापस -ENOMEM;
	पूर्ण

	master_outb(3, DISPLAY_CONTROL_REG);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "Unable to register Q40 frame buffer\n");
		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
		वापस -EINVAL;
	पूर्ण

	fb_info(info, "Q40 frame buffer alive and kicking !\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver q40fb_driver = अणु
	.probe	= q40fb_probe,
	.driver	= अणु
		.name	= "q40fb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device q40fb_device = अणु
	.name	= "q40fb",
पूर्ण;

पूर्णांक __init q40fb_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (fb_get_options("q40fb", शून्य))
		वापस -ENODEV;

	ret = platक्रमm_driver_रेजिस्टर(&q40fb_driver);

	अगर (!ret) अणु
		ret = platक्रमm_device_रेजिस्टर(&q40fb_device);
		अगर (ret)
			platक्रमm_driver_unरेजिस्टर(&q40fb_driver);
	पूर्ण
	वापस ret;
पूर्ण

module_init(q40fb_init);
MODULE_LICENSE("GPL");
