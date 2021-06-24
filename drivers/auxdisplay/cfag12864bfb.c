<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Filename: cfag12864bfb.c
 *     Version: 0.1.0
 * Description: cfag12864b LCD framebuffer driver
 *     Depends: cfag12864b
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-31
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/cfag12864b.h>

#घोषणा CFAG12864BFB_NAME "cfag12864bfb"

अटल स्थिर काष्ठा fb_fix_screeninfo cfag12864bfb_fix = अणु
	.id = "cfag12864b",
	.type = FB_TYPE_PACKED_PIXELS,
	.visual = FB_VISUAL_MONO10,
	.xpanstep = 0,
	.ypanstep = 0,
	.ywrapstep = 0,
	.line_length = CFAG12864B_WIDTH / 8,
	.accel = FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo cfag12864bfb_var = अणु
	.xres = CFAG12864B_WIDTH,
	.yres = CFAG12864B_HEIGHT,
	.xres_भव = CFAG12864B_WIDTH,
	.yres_भव = CFAG12864B_HEIGHT,
	.bits_per_pixel = 1,
	.red = अणु 0, 1, 0 पूर्ण,
      	.green = अणु 0, 1, 0 पूर्ण,
      	.blue = अणु 0, 1, 0 पूर्ण,
	.left_margin = 0,
	.right_margin = 0,
	.upper_margin = 0,
	.lower_margin = 0,
	.vmode = FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक cfag12864bfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा page *pages = virt_to_page(cfag12864b_buffer);

	वापस vm_map_pages_zero(vma, &pages, 1);
पूर्ण

अटल स्थिर काष्ठा fb_ops cfag12864bfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_पढ़ो = fb_sys_पढ़ो,
	.fb_ग_लिखो = fb_sys_ग_लिखो,
	.fb_fillrect = sys_fillrect,
	.fb_copyarea = sys_copyarea,
	.fb_imageblit = sys_imageblit,
	.fb_mmap = cfag12864bfb_mmap,
पूर्ण;

अटल पूर्णांक cfag12864bfb_probe(काष्ठा platक्रमm_device *device)
अणु
	पूर्णांक ret = -EINVAL;
 	काष्ठा fb_info *info = framebuffer_alloc(0, &device->dev);

	अगर (!info)
		जाओ none;

	info->screen_base = (अक्षर __iomem *) cfag12864b_buffer;
	info->screen_size = CFAG12864B_SIZE;
	info->fbops = &cfag12864bfb_ops;
	info->fix = cfag12864bfb_fix;
	info->var = cfag12864bfb_var;
	info->pseuकरो_palette = शून्य;
	info->par = शून्य;
	info->flags = FBINFO_FLAG_DEFAULT;

	अगर (रेजिस्टर_framebuffer(info) < 0)
		जाओ fballoced;

	platक्रमm_set_drvdata(device, info);

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	वापस 0;

fballoced:
	framebuffer_release(info);

none:
	वापस ret;
पूर्ण

अटल पूर्णांक cfag12864bfb_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(device);

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		framebuffer_release(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cfag12864bfb_driver = अणु
	.probe	= cfag12864bfb_probe,
	.हटाओ = cfag12864bfb_हटाओ,
	.driver = अणु
		.name	= CFAG12864BFB_NAME,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *cfag12864bfb_device;

अटल पूर्णांक __init cfag12864bfb_init(व्योम)
अणु
	पूर्णांक ret = -EINVAL;

	/* cfag12864b_init() must be called first */
	अगर (!cfag12864b_isinited()) अणु
		prपूर्णांकk(KERN_ERR CFAG12864BFB_NAME ": ERROR: "
			"cfag12864b is not initialized\n");
		जाओ none;
	पूर्ण

	अगर (cfag12864b_enable()) अणु
		prपूर्णांकk(KERN_ERR CFAG12864BFB_NAME ": ERROR: "
			"can't enable cfag12864b refreshing (being used)\n");
		वापस -ENODEV;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&cfag12864bfb_driver);

	अगर (!ret) अणु
		cfag12864bfb_device =
			platक्रमm_device_alloc(CFAG12864BFB_NAME, 0);

		अगर (cfag12864bfb_device)
			ret = platक्रमm_device_add(cfag12864bfb_device);
		अन्यथा
			ret = -ENOMEM;

		अगर (ret) अणु
			platक्रमm_device_put(cfag12864bfb_device);
			platक्रमm_driver_unरेजिस्टर(&cfag12864bfb_driver);
		पूर्ण
	पूर्ण

none:
	वापस ret;
पूर्ण

अटल व्योम __निकास cfag12864bfb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(cfag12864bfb_device);
	platक्रमm_driver_unरेजिस्टर(&cfag12864bfb_driver);
	cfag12864b_disable();
पूर्ण

module_init(cfag12864bfb_init);
module_निकास(cfag12864bfb_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Miguel Ojeda <ojeda@kernel.org>");
MODULE_DESCRIPTION("cfag12864b LCD framebuffer driver");
