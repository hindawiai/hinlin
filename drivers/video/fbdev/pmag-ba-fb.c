<शैली गुरु>
/*
 *	linux/drivers/video/pmag-ba-fb.c
 *
 *	PMAG-BA TURBOchannel Color Frame Buffer (CFB) card support,
 *	derived from:
 *	"HP300 Topcat framebuffer support (derived from macfb of all things)
 *	Phil Blundell <philb@gnu.org> 1998", the original code can be
 *	found in the file hpfb.c in the same directory.
 *
 *	Based on digital करोcument:
 * 	"PMAG-BA TURBOchannel Color Frame Buffer
 *	 Functional Specअगरication", Revision 1.2, August 27, 1990
 *
 *	DECstation related code Copyright (C) 1999, 2000, 2001 by
 *	Michael Engel <engel@unix-ag.org>,
 *	Karsten Merker <merker@linuxtag.org> and
 *	Harald Koerfgen.
 *	Copyright (c) 2005, 2006  Maciej W. Rozycki
 *	Copyright (c) 2005  James Simmons
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License.  See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/tc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>

#समावेश <video/pmag-ba-fb.h>


काष्ठा pmagbafb_par अणु
	अस्थिर व्योम __iomem *mmio;
	अस्थिर u32 __iomem *dac;
पूर्ण;


अटल स्थिर काष्ठा fb_var_screeninfo pmagbafb_defined = अणु
	.xres		= 1024,
	.yres		= 864,
	.xres_भव	= 1024,
	.yres_भव	= 864,
	.bits_per_pixel	= 8,
	.red.length	= 8,
	.green.length	= 8,
	.blue.length	= 8,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.accel_flags	= FB_ACCEL_NONE,
	.pixघड़ी	= 14452,
	.left_margin	= 116,
	.right_margin	= 12,
	.upper_margin	= 34,
	.lower_margin	= 0,
	.hsync_len	= 128,
	.vsync_len	= 3,
	.sync		= FB_SYNC_ON_GREEN,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo pmagbafb_fix = अणु
	.id		= "PMAG-BA",
	.smem_len	= (1024 * 1024),
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.line_length	= 1024,
	.mmio_len	= PMAG_BA_SIZE - PMAG_BA_BT459,
पूर्ण;


अटल अंतरभूत व्योम dac_ग_लिखो(काष्ठा pmagbafb_par *par, अचिन्हित पूर्णांक reg, u8 v)
अणु
	ग_लिखोb(v, par->dac + reg / 4);
पूर्ण

अटल अंतरभूत u8 dac_पढ़ो(काष्ठा pmagbafb_par *par, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(par->dac + reg / 4);
पूर्ण


/*
 * Set the palette.
 */
अटल पूर्णांक pmagbafb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			      अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			      अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा pmagbafb_par *par = info->par;

	अगर (regno >= info->cmap.len)
		वापस 1;

	red   >>= 8;	/* The cmap fields are 16 bits    */
	green >>= 8;	/* wide, but the hardware colormap */
	blue  >>= 8;	/* रेजिस्टरs are only 8 bits wide */

	mb();
	dac_ग_लिखो(par, BT459_ADDR_LO, regno);
	dac_ग_लिखो(par, BT459_ADDR_HI, 0x00);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, red);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, green);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, blue);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops pmagbafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= pmagbafb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;


/*
 * Turn the hardware cursor off.
 */
अटल व्योम pmagbafb_erase_cursor(काष्ठा fb_info *info)
अणु
	काष्ठा pmagbafb_par *par = info->par;

	mb();
	dac_ग_लिखो(par, BT459_ADDR_LO, 0x00);
	dac_ग_लिखो(par, BT459_ADDR_HI, 0x03);
	wmb();
	dac_ग_लिखो(par, BT459_DATA, 0x00);
पूर्ण


अटल पूर्णांक pmagbafb_probe(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	resource_माप_प्रकार start, len;
	काष्ठा fb_info *info;
	काष्ठा pmagbafb_par *par;
	पूर्णांक err;

	info = framebuffer_alloc(माप(काष्ठा pmagbafb_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	dev_set_drvdata(dev, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot allocate color map\n",
		       dev_name(dev));
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	info->fbops = &pmagbafb_ops;
	info->fix = pmagbafb_fix;
	info->var = pmagbafb_defined;
	info->flags = FBINFO_DEFAULT;

	/* Request the I/O MEM resource.  */
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	अगर (!request_mem_region(start, len, dev_name(dev))) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot reserve FB region\n",
		       dev_name(dev));
		err = -EBUSY;
		जाओ err_cmap;
	पूर्ण

	/* MMIO mapping setup.  */
	info->fix.mmio_start = start;
	par->mmio = ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!par->mmio) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map MMIO\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_resource;
	पूर्ण
	par->dac = par->mmio + PMAG_BA_BT459;

	/* Frame buffer mapping setup.  */
	info->fix.smem_start = start + PMAG_BA_FBMEM;
	info->screen_base = ioremap(info->fix.smem_start,
					    info->fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map FB\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_mmio_map;
	पूर्ण
	info->screen_size = info->fix.smem_len;

	pmagbafb_erase_cursor(info);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot register framebuffer\n",
		       dev_name(dev));
		जाओ err_smem_map;
	पूर्ण

	get_device(dev);

	fb_info(info, "%s frame buffer device at %s\n",
		info->fix.id, dev_name(dev));

	वापस 0;


err_smem_map:
	iounmap(info->screen_base);

err_mmio_map:
	iounmap(par->mmio);

err_resource:
	release_mem_region(start, len);

err_cmap:
	fb_dealloc_cmap(&info->cmap);

err_alloc:
	framebuffer_release(info);
	वापस err;
पूर्ण

अटल पूर्णांक pmagbafb_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा pmagbafb_par *par = info->par;
	resource_माप_प्रकार start, len;

	put_device(dev);
	unरेजिस्टर_framebuffer(info);
	iounmap(info->screen_base);
	iounmap(par->mmio);
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
	वापस 0;
पूर्ण


/*
 * Initialize the framebuffer.
 */
अटल स्थिर काष्ठा tc_device_id pmagbafb_tc_table[] = अणु
	अणु "DEC     ", "PMAG-BA " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, pmagbafb_tc_table);

अटल काष्ठा tc_driver pmagbafb_driver = अणु
	.id_table	= pmagbafb_tc_table,
	.driver		= अणु
		.name	= "pmagbafb",
		.bus	= &tc_bus_type,
		.probe	= pmagbafb_probe,
		.हटाओ	= pmagbafb_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmagbafb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (fb_get_options("pmagbafb", शून्य))
		वापस -ENXIO;
#पूर्ण_अगर
	वापस tc_रेजिस्टर_driver(&pmagbafb_driver);
पूर्ण

अटल व्योम __निकास pmagbafb_निकास(व्योम)
अणु
	tc_unरेजिस्टर_driver(&pmagbafb_driver);
पूर्ण


module_init(pmagbafb_init);
module_निकास(pmagbafb_निकास);

MODULE_LICENSE("GPL");
