<शैली गुरु>
/*
 *	linux/drivers/video/pmag-aa-fb.c
 *	Copyright 2002 Karsten Merker <merker@debian.org>
 *
 *	PMAG-AA TurboChannel framebuffer card support ... derived from
 *	pmag-ba-fb.c, which is Copyright (C) 1999, 2000, 2001 by
 *	Michael Engel <engel@unix-ag.org>, Karsten Merker <merker@debian.org>
 *	and Harald Koerfgen <hkoerfg@web.de>, which itself is derived from
 *	"HP300 Topcat framebuffer support (derived from macfb of all things)
 *	Phil Blundell <philb@gnu.org> 1998"
 *	Copyright (c) 2016  Maciej W. Rozycki
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License.  See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 *
 *	2002-09-28  Karsten Merker <merker@linuxtag.org>
 *		Version 0.01: First try to get a PMAG-AA running.
 *
 *	2003-02-24  Thiemo Seufer  <seufer@csv.ica.uni-stuttgart.de>
 *		Version 0.02: Major code cleanup.
 *
 *	2003-09-21  Thiemo Seufer  <seufer@csv.ica.uni-stuttgart.de>
 *		Hardware cursor support.
 *
 *	2016-02-21  Maciej W. Rozycki  <macro@linux-mips.org>
 *		Version 0.03: Rewritten क्रम the new FB and TC APIs.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/tc.h>
#समावेश <linux/समयr.h>

#समावेश "bt455.h"
#समावेश "bt431.h"

/* Version inक्रमmation */
#घोषणा DRIVER_VERSION "0.03"
#घोषणा DRIVER_AUTHOR "Karsten Merker <merker@linuxtag.org>"
#घोषणा DRIVER_DESCRIPTION "PMAG-AA Framebuffer Driver"

/*
 * Bt455 RAM DAC रेजिस्टर base offset (rel. to TC slot base address).
 */
#घोषणा PMAG_AA_BT455_OFFSET		0x100000

/*
 * Bt431 cursor generator offset (rel. to TC slot base address).
 */
#घोषणा PMAG_AA_BT431_OFFSET		0x180000

/*
 * Begin of PMAG-AA framebuffer memory relative to TC slot address,
 * resolution is 1280x1024x1 (8 bits deep, but only LSB is used).
 */
#घोषणा PMAG_AA_ONBOARD_FBMEM_OFFSET	0x200000

काष्ठा aafb_par अणु
	व्योम __iomem *mmio;
	काष्ठा bt455_regs __iomem *bt455;
	काष्ठा bt431_regs __iomem *bt431;
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo aafb_defined = अणु
	.xres		= 1280,
	.yres		= 1024,
	.xres_भव	= 2048,
	.yres_भव	= 1024,
	.bits_per_pixel	= 8,
	.grayscale	= 1,
	.red.length	= 0,
	.green.length	= 1,
	.blue.length	= 0,
	.activate	= FB_ACTIVATE_NOW,
	.accel_flags	= FB_ACCEL_NONE,
	.pixघड़ी	= 7645,
	.left_margin	= 224,
	.right_margin	= 32,
	.upper_margin	= 33,
	.lower_margin	= 3,
	.hsync_len	= 160,
	.vsync_len	= 3,
	.sync		= FB_SYNC_ON_GREEN,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo aafb_fix = अणु
	.id		= "PMAG-AA",
	.smem_len	= (2048 * 1024),
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_MONO10,
	.ypanstep	= 1,
	.ywrapstep	= 1,
	.line_length	= 2048,
	.mmio_len	= PMAG_AA_ONBOARD_FBMEM_OFFSET - PMAG_AA_BT455_OFFSET,
पूर्ण;

अटल पूर्णांक aafb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा aafb_par *par = info->par;

	अगर (cursor->image.height > BT431_CURSOR_SIZE ||
	    cursor->image.width > BT431_CURSOR_SIZE) अणु
		bt431_erase_cursor(par->bt431);
		वापस -EINVAL;
	पूर्ण

	अगर (!cursor->enable)
		bt431_erase_cursor(par->bt431);

	अगर (cursor->set & FB_CUR_SETPOS)
		bt431_position_cursor(par->bt431,
				      cursor->image.dx, cursor->image.dy);
	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u8 fg = cursor->image.fg_color ? 0xf : 0x0;
		u8 bg = cursor->image.bg_color ? 0xf : 0x0;

		bt455_ग_लिखो_cmap_entry(par->bt455, 8, bg);
		bt455_ग_लिखो_cmap_next(par->bt455, bg);
		bt455_ग_लिखो_ovly_next(par->bt455, fg);
	पूर्ण
	अगर (cursor->set & (FB_CUR_SETSIZE | FB_CUR_SETSHAPE | FB_CUR_SETIMAGE))
		bt431_set_cursor(par->bt431,
				 cursor->image.data, cursor->mask, cursor->rop,
				 cursor->image.width, cursor->image.height);

	अगर (cursor->enable)
		bt431_enable_cursor(par->bt431);

	वापस 0;
पूर्ण

/* 0 unblanks, any other blanks. */

अटल पूर्णांक aafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा aafb_par *par = info->par;
	u8 val = blank ? 0x00 : 0x0f;

	bt455_ग_लिखो_cmap_entry(par->bt455, 1, val);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops aafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_blank	= aafb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_cursor	= aafb_cursor,
पूर्ण;

अटल पूर्णांक pmagaafb_probe(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	resource_माप_प्रकार start, len;
	काष्ठा fb_info *info;
	काष्ठा aafb_par *par;
	पूर्णांक err;

	info = framebuffer_alloc(माप(काष्ठा aafb_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	dev_set_drvdata(dev, info);

	info->fbops = &aafb_ops;
	info->fix = aafb_fix;
	info->var = aafb_defined;
	info->flags = FBINFO_DEFAULT;

	/* Request the I/O MEM resource. */
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	अगर (!request_mem_region(start, len, dev_name(dev))) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot reserve FB region\n",
		       dev_name(dev));
		err = -EBUSY;
		जाओ err_alloc;
	पूर्ण

	/* MMIO mapping setup. */
	info->fix.mmio_start = start + PMAG_AA_BT455_OFFSET;
	par->mmio = ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!par->mmio) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map MMIO\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_resource;
	पूर्ण
	par->bt455 = par->mmio - PMAG_AA_BT455_OFFSET + PMAG_AA_BT455_OFFSET;
	par->bt431 = par->mmio - PMAG_AA_BT455_OFFSET + PMAG_AA_BT431_OFFSET;

	/* Frame buffer mapping setup. */
	info->fix.smem_start = start + PMAG_AA_ONBOARD_FBMEM_OFFSET;
	info->screen_base = ioremap(info->fix.smem_start,
					    info->fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map FB\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_mmio_map;
	पूर्ण
	info->screen_size = info->fix.smem_len;

	/* Init colormap. */
	bt455_ग_लिखो_cmap_entry(par->bt455, 0, 0x0);
	bt455_ग_लिखो_cmap_next(par->bt455, 0xf);

	/* Init hardware cursor. */
	bt431_erase_cursor(par->bt431);
	bt431_init_cursor(par->bt431);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot register framebuffer\n",
		       dev_name(dev));
		जाओ err_smem_map;
	पूर्ण

	get_device(dev);

	pr_info("fb%d: %s frame buffer device at %s\n",
		info->node, info->fix.id, dev_name(dev));

	वापस 0;


err_smem_map:
	iounmap(info->screen_base);

err_mmio_map:
	iounmap(par->mmio);

err_resource:
	release_mem_region(start, len);

err_alloc:
	framebuffer_release(info);
	वापस err;
पूर्ण

अटल पूर्णांक pmagaafb_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा aafb_par *par = info->par;
	resource_माप_प्रकार start, len;

	put_device(dev);
	unरेजिस्टर_framebuffer(info);
	iounmap(info->screen_base);
	iounmap(par->mmio);
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);
	framebuffer_release(info);
	वापस 0;
पूर्ण

/*
 * Initialise the framebuffer.
 */
अटल स्थिर काष्ठा tc_device_id pmagaafb_tc_table[] = अणु
	अणु "DEC     ", "PMAG-AA " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, pmagaafb_tc_table);

अटल काष्ठा tc_driver pmagaafb_driver = अणु
	.id_table	= pmagaafb_tc_table,
	.driver		= अणु
		.name	= "pmagaafb",
		.bus	= &tc_bus_type,
		.probe	= pmagaafb_probe,
		.हटाओ	= pmagaafb_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmagaafb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (fb_get_options("pmagaafb", शून्य))
		वापस -ENXIO;
#पूर्ण_अगर
	वापस tc_रेजिस्टर_driver(&pmagaafb_driver);
पूर्ण

अटल व्योम __निकास pmagaafb_निकास(व्योम)
अणु
	tc_unरेजिस्टर_driver(&pmagaafb_driver);
पूर्ण

module_init(pmagaafb_init);
module_निकास(pmagaafb_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_LICENSE("GPL");
