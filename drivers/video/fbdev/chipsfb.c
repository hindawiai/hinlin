<शैली गुरु>
/*
 *  drivers/video/chipsfb.c -- frame buffer device क्रम
 *  Chips & Technologies 65550 chip.
 *
 *  Copyright (C) 1998-2002 Paul Mackerras
 *
 *  This file is derived from the Powermac "chips" driver:
 *  Copyright (C) 1997 Fabio Riccardi.
 *  And from the frame buffer device क्रम Open Firmware-initialized devices:
 *  Copyright (C) 1997 Geert Uytterhoeven.
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
#समावेश <linux/fb.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/console.h>

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

/*
 * Since we access the display with inb/outb to fixed port numbers,
 * we can only handle one 6555x chip.  -- paulus
 */
#घोषणा ग_लिखो_ind(num, val, ap, dp)	करो अणु \
	outb((num), (ap)); outb((val), (dp)); \
पूर्ण जबतक (0)
#घोषणा पढ़ो_ind(num, var, ap, dp)	करो अणु \
	outb((num), (ap)); var = inb((dp)); \
पूर्ण जबतक (0)

/* extension रेजिस्टरs */
#घोषणा ग_लिखो_xr(num, val)	ग_लिखो_ind(num, val, 0x3d6, 0x3d7)
#घोषणा पढ़ो_xr(num, var)	पढ़ो_ind(num, var, 0x3d6, 0x3d7)
/* flat panel रेजिस्टरs */
#घोषणा ग_लिखो_fr(num, val)	ग_लिखो_ind(num, val, 0x3d0, 0x3d1)
#घोषणा पढ़ो_fr(num, var)	पढ़ो_ind(num, var, 0x3d0, 0x3d1)
/* CRTC रेजिस्टरs */
#घोषणा ग_लिखो_cr(num, val)	ग_लिखो_ind(num, val, 0x3d4, 0x3d5)
#घोषणा पढ़ो_cr(num, var)	पढ़ो_ind(num, var, 0x3d4, 0x3d5)
/* graphics रेजिस्टरs */
#घोषणा ग_लिखो_gr(num, val)	ग_लिखो_ind(num, val, 0x3ce, 0x3cf)
#घोषणा पढ़ो_gr(num, var)	पढ़ो_ind(num, var, 0x3ce, 0x3cf)
/* sequencer रेजिस्टरs */
#घोषणा ग_लिखो_sr(num, val)	ग_लिखो_ind(num, val, 0x3c4, 0x3c5)
#घोषणा पढ़ो_sr(num, var)	पढ़ो_ind(num, var, 0x3c4, 0x3c5)
/* attribute रेजिस्टरs - slightly strange */
#घोषणा ग_लिखो_ar(num, val)	करो अणु \
	inb(0x3da); ग_लिखो_ind(num, val, 0x3c0, 0x3c0); \
पूर्ण जबतक (0)
#घोषणा पढ़ो_ar(num, var)	करो अणु \
	inb(0x3da); पढ़ो_ind(num, var, 0x3c0, 0x3c1); \
पूर्ण जबतक (0)

/*
 * Exported functions
 */
पूर्णांक chips_init(व्योम);

अटल पूर्णांक chipsfb_pci_init(काष्ठा pci_dev *dp, स्थिर काष्ठा pci_device_id *);
अटल पूर्णांक chipsfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info);
अटल पूर्णांक chipsfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक chipsfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक chipsfb_blank(पूर्णांक blank, काष्ठा fb_info *info);

अटल स्थिर काष्ठा fb_ops chipsfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= chipsfb_check_var,
	.fb_set_par	= chipsfb_set_par,
	.fb_setcolreg	= chipsfb_setcolreg,
	.fb_blank	= chipsfb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक chipsfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	अगर (var->xres > 800 || var->yres > 600
	    || var->xres_भव > 800 || var->yres_भव > 600
	    || (var->bits_per_pixel != 8 && var->bits_per_pixel != 16)
	    || var->nonstd
	    || (var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

	var->xres = var->xres_भव = 800;
	var->yres = var->yres_भव = 600;

	वापस 0;
पूर्ण

अटल पूर्णांक chipsfb_set_par(काष्ठा fb_info *info)
अणु
	अगर (info->var.bits_per_pixel == 16) अणु
		ग_लिखो_cr(0x13, 200);		// Set line length (द्विगुनwords)
		ग_लिखो_xr(0x81, 0x14);		// 15 bit (555) color mode
		ग_लिखो_xr(0x82, 0x00);		// Disable palettes
		ग_लिखो_xr(0x20, 0x10);		// 16 bit blitter mode

		info->fix.line_length = 800*2;
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		info->var.red.offset = 10;
		info->var.green.offset = 5;
		info->var.blue.offset = 0;
		info->var.red.length = info->var.green.length =
			info->var.blue.length = 5;
		
	पूर्ण अन्यथा अणु
		/* p->var.bits_per_pixel == 8 */
		ग_लिखो_cr(0x13, 100);		// Set line length (द्विगुनwords)
		ग_लिखो_xr(0x81, 0x12);		// 8 bit color mode
		ग_लिखो_xr(0x82, 0x08);		// Graphics gamma enable
		ग_लिखो_xr(0x20, 0x00);		// 8 bit blitter mode

		info->fix.line_length = 800;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;		

 		info->var.red.offset = info->var.green.offset =
			info->var.blue.offset = 0;
		info->var.red.length = info->var.green.length =
			info->var.blue.length = 8;
		
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक chipsfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	वापस 1;	/* get fb_blank to set the colormap to all black */
पूर्ण

अटल पूर्णांक chipsfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno > 255)
		वापस 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;
	outb(regno, 0x3c8);
	udelay(1);
	outb(red, 0x3c9);
	outb(green, 0x3c9);
	outb(blue, 0x3c9);

	वापस 0;
पूर्ण

काष्ठा chips_init_reg अणु
	अचिन्हित अक्षर addr;
	अचिन्हित अक्षर data;
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_sr[] = अणु
	अणु 0x00, 0x03 पूर्ण,
	अणु 0x01, 0x01 पूर्ण,
	अणु 0x02, 0x0f पूर्ण,
	अणु 0x04, 0x0e पूर्ण
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_gr[] = अणु
	अणु 0x05, 0x00 पूर्ण,
	अणु 0x06, 0x0d पूर्ण,
	अणु 0x08, 0xff पूर्ण
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_ar[] = अणु
	अणु 0x10, 0x01 पूर्ण,
	अणु 0x12, 0x0f पूर्ण,
	अणु 0x13, 0x00 पूर्ण
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_cr[] = अणु
	अणु 0x00, 0x7f पूर्ण,
	अणु 0x01, 0x63 पूर्ण,
	अणु 0x02, 0x63 पूर्ण,
	अणु 0x03, 0x83 पूर्ण,
	अणु 0x04, 0x66 पूर्ण,
	अणु 0x05, 0x10 पूर्ण,
	अणु 0x06, 0x72 पूर्ण,
	अणु 0x07, 0x3e पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x40 पूर्ण,
	अणु 0x0c, 0x00 पूर्ण,
	अणु 0x0d, 0x00 पूर्ण,
	अणु 0x10, 0x59 पूर्ण,
	अणु 0x11, 0x0d पूर्ण,
	अणु 0x12, 0x57 पूर्ण,
	अणु 0x13, 0x64 पूर्ण,
	अणु 0x14, 0x00 पूर्ण,
	अणु 0x15, 0x57 पूर्ण,
	अणु 0x16, 0x73 पूर्ण,
	अणु 0x17, 0xe3 पूर्ण,
	अणु 0x18, 0xff पूर्ण,
	अणु 0x30, 0x02 पूर्ण,
	अणु 0x31, 0x02 पूर्ण,
	अणु 0x32, 0x02 पूर्ण,
	अणु 0x33, 0x02 पूर्ण,
	अणु 0x40, 0x00 पूर्ण,
	अणु 0x41, 0x00 पूर्ण,
	अणु 0x40, 0x80 पूर्ण
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_fr[] = अणु
	अणु 0x01, 0x02 पूर्ण,
	अणु 0x03, 0x08 पूर्ण,
	अणु 0x04, 0x81 पूर्ण,
	अणु 0x05, 0x21 पूर्ण,
	अणु 0x08, 0x0c पूर्ण,
	अणु 0x0a, 0x74 पूर्ण,
	अणु 0x0b, 0x11 पूर्ण,
	अणु 0x10, 0x0c पूर्ण,
	अणु 0x11, 0xe0 पूर्ण,
	/* अणु 0x12, 0x40 पूर्ण, -- 3400 needs 40, 2400 needs 48, no way to tell */
	अणु 0x20, 0x63 पूर्ण,
	अणु 0x21, 0x68 पूर्ण,
	अणु 0x22, 0x19 पूर्ण,
	अणु 0x23, 0x7f पूर्ण,
	अणु 0x24, 0x68 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x0f पूर्ण,
	अणु 0x30, 0x57 पूर्ण,
	अणु 0x31, 0x58 पूर्ण,
	अणु 0x32, 0x0d पूर्ण,
	अणु 0x33, 0x72 पूर्ण,
	अणु 0x34, 0x02 पूर्ण,
	अणु 0x35, 0x22 पूर्ण,
	अणु 0x36, 0x02 पूर्ण,
	अणु 0x37, 0x00 पूर्ण
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_xr[] = अणु
	अणु 0xce, 0x00 पूर्ण,		/* set शेष memory घड़ी */
	अणु 0xcc, 0x43 पूर्ण,		/* memory घड़ी ratio */
	अणु 0xcd, 0x18 पूर्ण,
	अणु 0xce, 0xa1 पूर्ण,
	अणु 0xc8, 0x84 पूर्ण,
	अणु 0xc9, 0x0a पूर्ण,
	अणु 0xca, 0x00 पूर्ण,
	अणु 0xcb, 0x20 पूर्ण,
	अणु 0xcf, 0x06 पूर्ण,
	अणु 0xd0, 0x0e पूर्ण,
	अणु 0x09, 0x01 पूर्ण,
	अणु 0x0a, 0x02 पूर्ण,
	अणु 0x0b, 0x01 पूर्ण,
	अणु 0x20, 0x00 पूर्ण,
	अणु 0x40, 0x03 पूर्ण,
	अणु 0x41, 0x01 पूर्ण,
	अणु 0x42, 0x00 पूर्ण,
	अणु 0x80, 0x82 पूर्ण,
	अणु 0x81, 0x12 पूर्ण,
	अणु 0x82, 0x08 पूर्ण,
	अणु 0xa0, 0x00 पूर्ण,
	अणु 0xa8, 0x00 पूर्ण
पूर्ण;

अटल व्योम chips_hw_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chips_init_xr); ++i)
		ग_लिखो_xr(chips_init_xr[i].addr, chips_init_xr[i].data);
	outb(0x29, 0x3c2); /* set misc output reg */
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_sr); ++i)
		ग_लिखो_sr(chips_init_sr[i].addr, chips_init_sr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_gr); ++i)
		ग_लिखो_gr(chips_init_gr[i].addr, chips_init_gr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_ar); ++i)
		ग_लिखो_ar(chips_init_ar[i].addr, chips_init_ar[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_cr); ++i)
		ग_लिखो_cr(chips_init_cr[i].addr, chips_init_cr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_fr); ++i)
		ग_लिखो_fr(chips_init_fr[i].addr, chips_init_fr[i].data);
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo chipsfb_fix = अणु
	.id =		"C&T 65550",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.accel =	FB_ACCEL_NONE,
	.line_length =	800,

// FIXME: Assumes 1MB frame buffer, but 65550 supports 1MB or 2MB.
// * "3500" PowerBook G3 (the original PB G3) has 2MB.
// * 2400 has 1MB composed of 2 Mitsubishi M5M4V4265CTP DRAM chips.
//   Motherboard actually supports 2MB -- there are two blank locations
//   क्रम a second pair of DRAMs.  (Thanks, Apple!)
// * 3400 has 1MB (I think).  Don't know if it's expandable.
// -- Tim Seufert
	.smem_len =	0x100000,	/* 1MB */
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo chipsfb_var = अणु
	.xres = 800,
	.yres = 600,
	.xres_भव = 800,
	.yres_भव = 600,
	.bits_per_pixel = 8,
	.red = अणु .length = 8 पूर्ण,
	.green = अणु .length = 8 पूर्ण,
	.blue = अणु .length = 8 पूर्ण,
	.height = -1,
	.width = -1,
	.vmode = FB_VMODE_NONINTERLACED,
	.pixघड़ी = 10000,
	.left_margin = 16,
	.right_margin = 16,
	.upper_margin = 16,
	.lower_margin = 16,
	.hsync_len = 8,
	.vsync_len = 8,
पूर्ण;

अटल व्योम init_chips(काष्ठा fb_info *p, अचिन्हित दीर्घ addr)
अणु
	स_रखो(p->screen_base, 0, 0x100000);

	p->fix = chipsfb_fix;
	p->fix.smem_start = addr;

	p->var = chipsfb_var;

	p->fbops = &chipsfb_ops;
	p->flags = FBINFO_DEFAULT;

	fb_alloc_cmap(&p->cmap, 256, 0);

	chips_hw_init();
पूर्ण

अटल पूर्णांक chipsfb_pci_init(काष्ठा pci_dev *dp, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *p;
	अचिन्हित दीर्घ addr;
	अचिन्हित लघु cmd;
	पूर्णांक rc = -ENODEV;

	अगर (pci_enable_device(dp) < 0) अणु
		dev_err(&dp->dev, "Cannot enable PCI device\n");
		जाओ err_out;
	पूर्ण

	अगर ((dp->resource[0].flags & IORESOURCE_MEM) == 0)
		जाओ err_disable;
	addr = pci_resource_start(dp, 0);
	अगर (addr == 0)
		जाओ err_disable;

	p = framebuffer_alloc(0, &dp->dev);
	अगर (p == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_disable;
	पूर्ण

	अगर (pci_request_region(dp, 0, "chipsfb") != 0) अणु
		dev_err(&dp->dev, "Cannot request framebuffer\n");
		rc = -EBUSY;
		जाओ err_release_fb;
	पूर्ण

#अगर_घोषित __BIG_ENDIAN
	addr += 0x800000;	// Use big-endian aperture
#पूर्ण_अगर

	/* we should use pci_enable_device here, but,
	   the device करोesn't declare its I/O ports in its BARs
	   so pci_enable_device won't turn on I/O responses */
	pci_पढ़ो_config_word(dp, PCI_COMMAND, &cmd);
	cmd |= 3;	/* enable memory and IO space */
	pci_ग_लिखो_config_word(dp, PCI_COMMAND, cmd);

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	/* turn on the backlight */
	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight) अणु
		pmac_backlight->props.घातer = FB_BLANK_UNBLANK;
		backlight_update_status(pmac_backlight);
	पूर्ण
	mutex_unlock(&pmac_backlight_mutex);
#पूर्ण_अगर /* CONFIG_PMAC_BACKLIGHT */

#अगर_घोषित CONFIG_PPC
	p->screen_base = ioremap_wc(addr, 0x200000);
#अन्यथा
	p->screen_base = ioremap(addr, 0x200000);
#पूर्ण_अगर
	अगर (p->screen_base == शून्य) अणु
		dev_err(&dp->dev, "Cannot map framebuffer\n");
		rc = -ENOMEM;
		जाओ err_release_pci;
	पूर्ण

	pci_set_drvdata(dp, p);

	init_chips(p, addr);

	अगर (रेजिस्टर_framebuffer(p) < 0) अणु
		dev_err(&dp->dev,"C&T 65550 framebuffer failed to register\n");
		जाओ err_unmap;
	पूर्ण

	dev_info(&dp->dev,"fb%d: Chips 65550 frame buffer"
		 " (%dK RAM detected)\n",
		 p->node, p->fix.smem_len / 1024);

	वापस 0;

 err_unmap:
	iounmap(p->screen_base);
 err_release_pci:
	pci_release_region(dp, 0);
 err_release_fb:
	framebuffer_release(p);
 err_disable:
 err_out:
	वापस rc;
पूर्ण

अटल व्योम chipsfb_हटाओ(काष्ठा pci_dev *dp)
अणु
	काष्ठा fb_info *p = pci_get_drvdata(dp);

	अगर (p->screen_base == शून्य)
		वापस;
	unरेजिस्टर_framebuffer(p);
	iounmap(p->screen_base);
	p->screen_base = शून्य;
	pci_release_region(dp, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक chipsfb_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
        काष्ठा fb_info *p = pci_get_drvdata(pdev);

	अगर (state.event == pdev->dev.घातer.घातer_state.event)
		वापस 0;
	अगर (!(state.event & PM_EVENT_SLEEP))
		जाओ करोne;

	console_lock();
	chipsfb_blank(1, p);
	fb_set_suspend(p, 1);
	console_unlock();
 करोne:
	pdev->dev.घातer.घातer_state = state;
	वापस 0;
पूर्ण

अटल पूर्णांक chipsfb_pci_resume(काष्ठा pci_dev *pdev)
अणु
        काष्ठा fb_info *p = pci_get_drvdata(pdev);

	console_lock();
	fb_set_suspend(p, 0);
	chipsfb_blank(0, p);
	console_unlock();

	pdev->dev.घातer.घातer_state = PMSG_ON;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */


अटल काष्ठा pci_device_id chipsfb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_CT, PCI_DEVICE_ID_CT_65550, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, chipsfb_pci_tbl);

अटल काष्ठा pci_driver chipsfb_driver = अणु
	.name =		"chipsfb",
	.id_table =	chipsfb_pci_tbl,
	.probe =	chipsfb_pci_init,
	.हटाओ =	chipsfb_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend =	chipsfb_pci_suspend,
	.resume =	chipsfb_pci_resume,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init chips_init(व्योम)
अणु
	अगर (fb_get_options("chipsfb", शून्य))
		वापस -ENODEV;

	वापस pci_रेजिस्टर_driver(&chipsfb_driver);
पूर्ण

module_init(chips_init);

अटल व्योम __निकास chipsfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&chipsfb_driver);
पूर्ण

MODULE_LICENSE("GPL");
