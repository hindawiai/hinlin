<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	HP300 Topcat framebuffer support (derived from macfb of all things)
 *	Phil Blundell <philb@gnu.org> 1998
 *	DIO-II, colour map and Catseye support by
 *	Kars de Jong <jongk@linux-m68k.org>, May 2004.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/dपन.स>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

अटल काष्ठा fb_info fb_info = अणु
	.fix = अणु
		.id		= "HP300 ",
		.type		= FB_TYPE_PACKED_PIXELS,
		.visual		= FB_VISUAL_PSEUDOCOLOR,
		.accel		= FB_ACCEL_NONE,
	पूर्ण
पूर्ण;

अटल अचिन्हित दीर्घ fb_regs;
अटल अचिन्हित अक्षर fb_biपंचांगask;

#घोषणा TC_NBLANK	0x4080
#घोषणा TC_WEN		0x4088
#घोषणा TC_REN		0x408c
#घोषणा TC_FBEN		0x4090
#घोषणा TC_PRR		0x40ea

/* These defines match the X winकरोw प्रणाली */
#घोषणा RR_CLEAR	0x0
#घोषणा RR_COPY		0x3
#घोषणा RR_NOOP		0x5
#घोषणा RR_XOR		0x6
#घोषणा RR_INVERT	0xa
#घोषणा RR_COPYINVERTED 0xc
#घोषणा RR_SET		0xf

/* blitter regs */
#घोषणा BUSY		0x4044
#घोषणा WMRR		0x40ef
#घोषणा SOURCE_X	0x40f2
#घोषणा SOURCE_Y	0x40f6
#घोषणा DEST_X		0x40fa
#घोषणा DEST_Y		0x40fe
#घोषणा WHEIGHT		0x4106
#घोषणा WWIDTH		0x4102
#घोषणा WMOVE		0x409c

अटल काष्ठा fb_var_screeninfo hpfb_defined = अणु
	.red		= अणु
		.length = 8,
	पूर्ण,
	.green		= अणु
		.length = 8,
	पूर्ण,
	.blue		= अणु
		.length = 8,
	पूर्ण,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक hpfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			  अचिन्हित blue, अचिन्हित transp,
			  काष्ठा fb_info *info)
अणु
	/* use MSBs */
	अचिन्हित अक्षर _red  =red>>8;
	अचिन्हित अक्षर _green=green>>8;
	अचिन्हित अक्षर _blue =blue>>8;
	अचिन्हित अक्षर _regno=regno;

	/*
	 *  Set a single color रेजिस्टर. The values supplied are
	 *  alपढ़ोy rounded करोwn to the hardware's capabilities
	 *  (according to the entries in the `var' काष्ठाure). Return
	 *  != 0 क्रम invalid regno.
	 */

	अगर (regno >= info->cmap.len)
		वापस 1;
	
	जबतक (in_be16(fb_regs + 0x6002) & 0x4) udelay(1);

	out_be16(fb_regs + 0x60ba, 0xff);

	out_be16(fb_regs + 0x60b2, _red);
	out_be16(fb_regs + 0x60b4, _green);
	out_be16(fb_regs + 0x60b6, _blue);
	out_be16(fb_regs + 0x60b8, ~_regno);
	out_be16(fb_regs + 0x60f0, 0xff);

	udelay(100);

	जबतक (in_be16(fb_regs + 0x6002) & 0x4) udelay(1);
	out_be16(fb_regs + 0x60b2, 0);
	out_be16(fb_regs + 0x60b4, 0);
	out_be16(fb_regs + 0x60b6, 0);
	out_be16(fb_regs + 0x60b8, 0);

	वापस 0;
पूर्ण

/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */

अटल पूर्णांक hpfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	out_8(fb_regs + TC_NBLANK, (blank ? 0x00 : fb_biपंचांगask));

	वापस 0;
पूर्ण

अटल व्योम topcat_blit(पूर्णांक x0, पूर्णांक y0, पूर्णांक x1, पूर्णांक y1, पूर्णांक w, पूर्णांक h, पूर्णांक rr)
अणु
	अगर (rr >= 0) अणु
		जबतक (in_8(fb_regs + BUSY) & fb_biपंचांगask)
			;
	पूर्ण
	out_8(fb_regs + TC_FBEN, fb_biपंचांगask);
	अगर (rr >= 0) अणु
		out_8(fb_regs + TC_WEN, fb_biपंचांगask);
		out_8(fb_regs + WMRR, rr);
	पूर्ण
	out_be16(fb_regs + SOURCE_X, x0);
	out_be16(fb_regs + SOURCE_Y, y0);
	out_be16(fb_regs + DEST_X, x1);
	out_be16(fb_regs + DEST_Y, y1);
	out_be16(fb_regs + WWIDTH, w);
	out_be16(fb_regs + WHEIGHT, h);
	out_8(fb_regs + WMOVE, fb_biपंचांगask);
पूर्ण

अटल व्योम hpfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area) 
अणु
	topcat_blit(area->sx, area->sy, area->dx, area->dy, area->width, area->height, RR_COPY);
पूर्ण

अटल व्योम hpfb_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *region)
अणु
	u8 clr;

	clr = region->color & 0xff;

	जबतक (in_8(fb_regs + BUSY) & fb_biपंचांगask)
		;

	/* Foreground */
	out_8(fb_regs + TC_WEN, fb_biपंचांगask & clr);
	out_8(fb_regs + WMRR, (region->rop == ROP_COPY ? RR_SET : RR_INVERT));

	/* Background */
	out_8(fb_regs + TC_WEN, fb_biपंचांगask & ~clr);
	out_8(fb_regs + WMRR, (region->rop == ROP_COPY ? RR_CLEAR : RR_NOOP));

	topcat_blit(region->dx, region->dy, region->dx, region->dy, region->width, region->height, -1);
पूर्ण

अटल पूर्णांक hpfb_sync(काष्ठा fb_info *info)
अणु
	/*
	 * Since we also access the framebuffer directly, we have to रुको
	 * until the block mover is finished
	 */
	जबतक (in_8(fb_regs + BUSY) & fb_biपंचांगask)
		;

	out_8(fb_regs + TC_WEN, fb_biपंचांगask);
	out_8(fb_regs + TC_PRR, RR_COPY);
	out_8(fb_regs + TC_FBEN, fb_biपंचांगask);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops hpfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= hpfb_setcolreg,
	.fb_blank	= hpfb_blank,
	.fb_fillrect	= hpfb_fillrect,
	.fb_copyarea	= hpfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_sync	= hpfb_sync,
पूर्ण;

/* Common to all HP framebuffers */
#घोषणा HPFB_FBWMSB	0x05	/* Frame buffer width 		*/
#घोषणा HPFB_FBWLSB	0x07
#घोषणा HPFB_FBHMSB	0x09	/* Frame buffer height		*/
#घोषणा HPFB_FBHLSB	0x0b
#घोषणा HPFB_DWMSB	0x0d	/* Display width		*/
#घोषणा HPFB_DWLSB	0x0f
#घोषणा HPFB_DHMSB	0x11	/* Display height		*/
#घोषणा HPFB_DHLSB	0x13
#घोषणा HPFB_NUMPLANES	0x5b	/* Number of colour planes	*/
#घोषणा HPFB_FBOMSB	0x5d	/* Frame buffer offset		*/
#घोषणा HPFB_FBOLSB	0x5f

अटल पूर्णांक hpfb_init_one(अचिन्हित दीर्घ phys_base, अचिन्हित दीर्घ virt_base)
अणु
	अचिन्हित दीर्घ fboff, fb_width, fb_height, fb_start;
	पूर्णांक ret;

	fb_regs = virt_base;
	fboff = (in_8(fb_regs + HPFB_FBOMSB) << 8) | in_8(fb_regs + HPFB_FBOLSB);

	fb_info.fix.smem_start = (in_8(fb_regs + fboff) << 16);

	अगर (phys_base >= DIOII_BASE) अणु
		fb_info.fix.smem_start += phys_base;
	पूर्ण

	अगर (DIO_SECID(fb_regs) != DIO_ID2_TOPCAT) अणु
		/* This is the magic incantation the HP X server uses to make Catseye boards work. */
		जबतक (in_be16(fb_regs+0x4800) & 1)
			;
		out_be16(fb_regs+0x4800, 0);	/* Catseye status */
		out_be16(fb_regs+0x4510, 0);	/* VB */
		out_be16(fb_regs+0x4512, 0);	/* TCNTRL */
		out_be16(fb_regs+0x4514, 0);	/* ACNTRL */
		out_be16(fb_regs+0x4516, 0);	/* PNCNTRL */
		out_be16(fb_regs+0x4206, 0x90);	/* RUG Command/Status */
		out_be16(fb_regs+0x60a2, 0);	/* Overlay Mask */
		out_be16(fb_regs+0x60bc, 0);	/* Ram Select */
	पूर्ण

	/*
	 *	Fill in the available video resolution
	 */
	fb_width = (in_8(fb_regs + HPFB_FBWMSB) << 8) | in_8(fb_regs + HPFB_FBWLSB);
	fb_info.fix.line_length = fb_width;
	fb_height = (in_8(fb_regs + HPFB_FBHMSB) << 8) | in_8(fb_regs + HPFB_FBHLSB);
	fb_info.fix.smem_len = fb_width * fb_height;
	fb_start = (अचिन्हित दीर्घ)ioremap_wt(fb_info.fix.smem_start,
					     fb_info.fix.smem_len);
	hpfb_defined.xres = (in_8(fb_regs + HPFB_DWMSB) << 8) | in_8(fb_regs + HPFB_DWLSB);
	hpfb_defined.yres = (in_8(fb_regs + HPFB_DHMSB) << 8) | in_8(fb_regs + HPFB_DHLSB);
	hpfb_defined.xres_भव = hpfb_defined.xres;
	hpfb_defined.yres_भव = hpfb_defined.yres;
	hpfb_defined.bits_per_pixel = in_8(fb_regs + HPFB_NUMPLANES);

	prपूर्णांकk(KERN_INFO "hpfb: framebuffer at 0x%lx, mapped to 0x%lx, size %dk\n",
	       fb_info.fix.smem_start, fb_start, fb_info.fix.smem_len/1024);
	prपूर्णांकk(KERN_INFO "hpfb: mode is %dx%dx%d, linelength=%d\n",
	       hpfb_defined.xres, hpfb_defined.yres, hpfb_defined.bits_per_pixel, fb_info.fix.line_length);

	/*
	 *	Give the hardware a bit of a prod and work out how many bits per
	 *	pixel are supported.
	 */
	out_8(fb_regs + TC_WEN, 0xff);
	out_8(fb_regs + TC_PRR, RR_COPY);
	out_8(fb_regs + TC_FBEN, 0xff);
	out_8(fb_start, 0xff);
	fb_biपंचांगask = in_8(fb_start);
	out_8(fb_start, 0);

	/*
	 *	Enable पढ़ोing/writing of all the planes.
	 */
	out_8(fb_regs + TC_WEN, fb_biपंचांगask);
	out_8(fb_regs + TC_PRR, RR_COPY);
	out_8(fb_regs + TC_REN, fb_biपंचांगask);
	out_8(fb_regs + TC_FBEN, fb_biपंचांगask);

	/*
	 *	Clear the screen.
	 */
	topcat_blit(0, 0, 0, 0, fb_width, fb_height, RR_CLEAR);

	/*
	 *	Let there be consoles..
	 */
	अगर (DIO_SECID(fb_regs) == DIO_ID2_TOPCAT)
		म_जोड़ो(fb_info.fix.id, "Topcat");
	अन्यथा
		म_जोड़ो(fb_info.fix.id, "Catseye");
	fb_info.fbops = &hpfb_ops;
	fb_info.flags = FBINFO_DEFAULT;
	fb_info.var   = hpfb_defined;
	fb_info.screen_base = (अक्षर *)fb_start;

	ret = fb_alloc_cmap(&fb_info.cmap, 1 << hpfb_defined.bits_per_pixel, 0);
	अगर (ret < 0)
		जाओ unmap_screen_base;

	ret = रेजिस्टर_framebuffer(&fb_info);
	अगर (ret < 0)
		जाओ dealloc_cmap;

	fb_info(&fb_info, "%s frame buffer device\n", fb_info.fix.id);

	वापस 0;

dealloc_cmap:
	fb_dealloc_cmap(&fb_info.cmap);

unmap_screen_base:
	अगर (fb_info.screen_base) अणु
		iounmap(fb_info.screen_base);
		fb_info.screen_base = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/* 
 * Check that the secondary ID indicates that we have some hope of working with this
 * framebuffer.  The catseye boards are pretty much like topcats and we can muddle through.
 */

#घोषणा topcat_sid_ok(x)  (((x) == DIO_ID2_LRCATSEYE) || ((x) == DIO_ID2_HRCCATSEYE)    \
			   || ((x) == DIO_ID2_HRMCATSEYE) || ((x) == DIO_ID2_TOPCAT))

/* 
 * Initialise the framebuffer
 */
अटल पूर्णांक hpfb_dio_probe(काष्ठा dio_dev *d, स्थिर काष्ठा dio_device_id *ent)
अणु
	अचिन्हित दीर्घ paddr, vaddr;

	paddr = d->resource.start;
	अगर (!request_mem_region(d->resource.start, resource_size(&d->resource), d->name))
                वापस -EBUSY;

	अगर (d->scode >= DIOII_SCBASE) अणु
		vaddr = (अचिन्हित दीर्घ)ioremap(paddr, resource_size(&d->resource));
	पूर्ण अन्यथा अणु
		vaddr = paddr + DIO_VIRADDRBASE;
	पूर्ण
	prपूर्णांकk(KERN_INFO "Topcat found at DIO select code %d "
	       "(secondary id %02x)\n", d->scode, (d->id >> 8) & 0xff);
	अगर (hpfb_init_one(paddr, vaddr)) अणु
		अगर (d->scode >= DIOII_SCBASE)
			iounmap((व्योम *)vaddr);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hpfb_हटाओ_one(काष्ठा dio_dev *d)
अणु
	unरेजिस्टर_framebuffer(&fb_info);
	अगर (d->scode >= DIOII_SCBASE)
		iounmap((व्योम *)fb_regs);
	release_mem_region(d->resource.start, resource_size(&d->resource));
	fb_dealloc_cmap(&fb_info.cmap);
	अगर (fb_info.screen_base)
		iounmap(fb_info.screen_base);
पूर्ण

अटल काष्ठा dio_device_id hpfb_dio_tbl[] = अणु
    अणु DIO_ENCODE_ID(DIO_ID_FBUFFER, DIO_ID2_LRCATSEYE) पूर्ण,
    अणु DIO_ENCODE_ID(DIO_ID_FBUFFER, DIO_ID2_HRCCATSEYE) पूर्ण,
    अणु DIO_ENCODE_ID(DIO_ID_FBUFFER, DIO_ID2_HRMCATSEYE) पूर्ण,
    अणु DIO_ENCODE_ID(DIO_ID_FBUFFER, DIO_ID2_TOPCAT) पूर्ण,
    अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा dio_driver hpfb_driver = अणु
    .name      = "hpfb",
    .id_table  = hpfb_dio_tbl,
    .probe     = hpfb_dio_probe,
    .हटाओ    = hpfb_हटाओ_one,
पूर्ण;

पूर्णांक __init hpfb_init(व्योम)
अणु
	अचिन्हित पूर्णांक sid;
	अचिन्हित अक्षर i;
	पूर्णांक err;

	/* Topcats can be on the पूर्णांकernal IO bus or real DIO devices.
	 * The पूर्णांकernal variant sits at 0x560000; it has primary
	 * and secondary ID रेजिस्टरs just like the DIO version.
	 * So we merge the two detection routines.
	 *
	 * Perhaps this #घोषणा should be in a global header file:
	 * I believe it's common to all पूर्णांकernal fbs, not just topcat.
	 */
#घोषणा INTFBVADDR 0xf0560000
#घोषणा INTFBPADDR 0x560000

	अगर (!MACH_IS_HP300)
		वापस -ENODEV;

	अगर (fb_get_options("hpfb", शून्य))
		वापस -ENODEV;

	err = dio_रेजिस्टर_driver(&hpfb_driver);
	अगर (err)
		वापस err;

	err = copy_from_kernel_nofault(&i, (अचिन्हित अक्षर *)INTFBVADDR + DIO_IDOFF, 1);

	अगर (!err && (i == DIO_ID_FBUFFER) && topcat_sid_ok(sid = DIO_SECID(INTFBVADDR))) अणु
		अगर (!request_mem_region(INTFBPADDR, DIO_DEVSIZE, "Internal Topcat"))
			वापस -EBUSY;
		prपूर्णांकk(KERN_INFO "Internal Topcat found (secondary id %02x)\n", sid);
		अगर (hpfb_init_one(INTFBPADDR, INTFBVADDR)) अणु
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास hpfb_cleanup_module(व्योम)
अणु
	dio_unरेजिस्टर_driver(&hpfb_driver);
पूर्ण

module_init(hpfb_init);
module_निकास(hpfb_cleanup_module);

MODULE_LICENSE("GPL");
