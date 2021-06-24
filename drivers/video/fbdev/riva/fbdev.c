<शैली गुरु>
/*
 * linux/drivers/video/riva/fbdev.c - nVidia RIVA 128/TNT/TNT2 fb driver
 *
 * Maपूर्णांकained by Ani Joshi <ajoshi@shell.unixbox.com>
 *
 * Copyright 1999-2000 Jeff Garzik
 *
 * Contributors:
 *
 *	Ani Joshi:  Lots of debugging and cleanup work, really helped
 *	get the driver going
 *
 *	Ferenc Bakonyi:  Bug fixes, cleanup, modularization
 *
 *	Jindrich Makovicka:  Accel code help, hw cursor, mtrr
 *
 *	Paul Riअक्षरds:  Bug fixes, updates
 *
 * Initial ढाँचा from skeletonfb.c, created 28 Dec 1997 by Geert Uytterhoeven
 * Includes riva_hw.c from nVidia, see copyright below.
 * KGI code provided the basis क्रम state storage, init, and mode चयनing.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Known bugs and issues:
 *	restoring text mode fails
 *	द्विगुनscan modes are broken
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/backlight.h>
#समावेश <linux/bitrev.h>
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

#समावेश "rivafb.h"
#समावेश "nvreg.h"

/* version number of this driver */
#घोषणा RIVAFB_VERSION "0.9.5b"

/* ------------------------------------------------------------------------- *
 *
 * various helpful macros and स्थिरants
 *
 * ------------------------------------------------------------------------- */
#अगर_घोषित CONFIG_FB_RIVA_DEBUG
#घोषणा NVTRACE          prपूर्णांकk
#अन्यथा
#घोषणा NVTRACE          अगर(0) prपूर्णांकk
#पूर्ण_अगर

#घोषणा NVTRACE_ENTER(...)  NVTRACE("%s START\n", __func__)
#घोषणा NVTRACE_LEAVE(...)  NVTRACE("%s END\n", __func__)

#अगर_घोषित CONFIG_FB_RIVA_DEBUG
#घोषणा निश्चित(expr) \
	अगर(!(expr)) अणु \
	prपूर्णांकk( "Assertion failed! %s,%s,%s,line=%d\n",\
	#expr,__खाता__,__func__,__LINE__); \
	BUG(); \
	पूर्ण
#अन्यथा
#घोषणा निश्चित(expr)
#पूर्ण_अगर

#घोषणा PFX "rivafb: "

/* macro that allows you to set overflow bits */
#घोषणा SetBitField(value,from,to) SetBF(to,GetBF(value,from))
#घोषणा SetBit(n)		(1<<(n))
#घोषणा Set8Bits(value)		((value)&0xff)

/* HW cursor parameters */
#घोषणा MAX_CURS		32

/* ------------------------------------------------------------------------- *
 *
 * prototypes
 *
 * ------------------------------------------------------------------------- */

अटल पूर्णांक rivafb_blank(पूर्णांक blank, काष्ठा fb_info *info);

/* ------------------------------------------------------------------------- *
 *
 * card identअगरication
 *
 * ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा pci_device_id rivafb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_NVIDIA_SGS, PCI_DEVICE_ID_NVIDIA_SGS_RIVA128,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_TNT,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_TNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_UTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_VTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_UVTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_ITNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE_SDR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE_DDR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_MX,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_MX2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO2_MXR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_GTS,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_GTS2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE2_ULTRA,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO2_PRO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_MX_460,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_MX_440,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	// NF2/IGP version, GeForce 4 MX, NV18
	अणु PCI_VENDOR_ID_NVIDIA, 0x01f0,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_MX_420,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_440_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_420_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_420_GO_M32,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_500XGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_440_GO_M64,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_550XGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_500_GOGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_IGEFORCE2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE3,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE3_1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE3_2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO_DDC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_TI_4600,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_TI_4400,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE4_TI_4200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
 	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_900XGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_750XGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADRO4_700XGL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFORCE_FX_GO_5200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, rivafb_pci_tbl);

/* ------------------------------------------------------------------------- *
 *
 * global variables
 *
 * ------------------------------------------------------------------------- */

/* command line data, set in rivafb_setup() */
अटल पूर्णांक flatpanel = -1; /* Autodetect later */
अटल पूर्णांक क्रमceCRTC = -1;
अटल bool noaccel  = 0;
अटल bool nomtrr = 0;
अटल पूर्णांक backlight = IS_BUILTIN(CONFIG_PMAC_BACKLIGHT);

अटल अक्षर *mode_option = शून्य;
अटल bool stricपंचांगode       = 0;

अटल काष्ठा fb_fix_screeninfo rivafb_fix = अणु
	.type		= FB_TYPE_PACKED_PIXELS,
	.xpanstep	= 1,
	.ypanstep	= 1,
पूर्ण;

अटल काष्ठा fb_var_screeninfo rivafb_शेष_var = अणु
	.xres		= 640,
	.yres		= 480,
	.xres_भव	= 640,
	.yres_भव	= 480,
	.bits_per_pixel	= 8,
	.red		= अणु0, 8, 0पूर्ण,
	.green		= अणु0, 8, 0पूर्ण,
	.blue		= अणु0, 8, 0पूर्ण,
	.transp		= अणु0, 0, 0पूर्ण,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixघड़ी	= 39721,
	.left_margin	= 40,
	.right_margin	= 24,
	.upper_margin	= 32,
	.lower_margin	= 11,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.vmode		= FB_VMODE_NONINTERLACED
पूर्ण;

/* from GGI */
अटल स्थिर काष्ठा riva_regs reg_ढाँचा = अणु
	अणु0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,	/* ATTR */
	 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	 0x41, 0x01, 0x0F, 0x00, 0x00पूर्ण,
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* CRT  */
	 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3,	/* 0x10 */
	 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 0x20 */
	 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 0x30 */
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00,							/* 0x40 */
	 पूर्ण,
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,	/* GRA  */
	 0xFFपूर्ण,
	अणु0x03, 0x01, 0x0F, 0x00, 0x0Eपूर्ण,				/* SEQ  */
	0xEB							/* MISC */
पूर्ण;

/*
 * Backlight control
 */
#अगर_घोषित CONFIG_FB_RIVA_BACKLIGHT
/* We करो not have any inक्रमmation about which values are allowed, thus
 * we used safe values.
 */
#घोषणा MIN_LEVEL 0x158
#घोषणा MAX_LEVEL 0x534
#घोषणा LEVEL_STEP ((MAX_LEVEL - MIN_LEVEL) / FB_BACKLIGHT_MAX)

अटल पूर्णांक riva_bl_get_level_brightness(काष्ठा riva_par *par,
		पूर्णांक level)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	पूर्णांक nlevel;

	/* Get and convert the value */
	/* No locking on bl_curve since accessing a single value */
	nlevel = MIN_LEVEL + info->bl_curve[level] * LEVEL_STEP;

	अगर (nlevel < 0)
		nlevel = 0;
	अन्यथा अगर (nlevel < MIN_LEVEL)
		nlevel = MIN_LEVEL;
	अन्यथा अगर (nlevel > MAX_LEVEL)
		nlevel = MAX_LEVEL;

	वापस nlevel;
पूर्ण

अटल पूर्णांक riva_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा riva_par *par = bl_get_data(bd);
	U032 पंचांगp_pcrt, पंचांगp_pmc;
	पूर्णांक level;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;
	अन्यथा
		level = bd->props.brightness;

	पंचांगp_pmc = NV_RD32(par->riva.PMC, 0x10F0) & 0x0000FFFF;
	पंचांगp_pcrt = NV_RD32(par->riva.PCRTC0, 0x081C) & 0xFFFFFFFC;
	अगर(level > 0) अणु
		पंचांगp_pcrt |= 0x1;
		पंचांगp_pmc |= (1 << 31); /* backlight bit */
		पंचांगp_pmc |= riva_bl_get_level_brightness(par, level) << 16; /* level */
	पूर्ण
	NV_WR32(par->riva.PCRTC0, 0x081C, पंचांगp_pcrt);
	NV_WR32(par->riva.PMC, 0x10F0, पंचांगp_pmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops riva_bl_ops = अणु
	.update_status	= riva_bl_update_status,
पूर्ण;

अटल व्योम riva_bl_init(काष्ठा riva_par *par)
अणु
	काष्ठा backlight_properties props;
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	काष्ठा backlight_device *bd;
	अक्षर name[12];

	अगर (!par->FlatPanel)
		वापस;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!machine_is(घातermac) ||
	    !pmac_has_backlight_type("mnca"))
		वापस;
#पूर्ण_अगर

	snम_लिखो(name, माप(name), "rivabl%d", info->node);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, info->dev, par, &riva_bl_ops,
				       &props);
	अगर (IS_ERR(bd)) अणु
		info->bl_dev = शून्य;
		prपूर्णांकk(KERN_WARNING "riva: Backlight registration failed\n");
		जाओ error;
	पूर्ण

	info->bl_dev = bd;
	fb_bl_शेष_curve(info, 0,
		MIN_LEVEL * FB_BACKLIGHT_MAX / MAX_LEVEL,
		FB_BACKLIGHT_MAX);

	bd->props.brightness = bd->props.max_brightness;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk("riva: Backlight initialized (%s)\n", name);

	वापस;

error:
	वापस;
पूर्ण

अटल व्योम riva_bl_निकास(काष्ठा fb_info *info)
अणु
	काष्ठा backlight_device *bd = info->bl_dev;

	backlight_device_unरेजिस्टर(bd);
	prपूर्णांकk("riva: Backlight unloaded\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम riva_bl_init(काष्ठा riva_par *par) अणुपूर्ण
अटल अंतरभूत व्योम riva_bl_निकास(काष्ठा fb_info *info) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_FB_RIVA_BACKLIGHT */

/* ------------------------------------------------------------------------- *
 *
 * MMIO access macros
 *
 * ------------------------------------------------------------------------- */

अटल अंतरभूत व्योम CRTCout(काष्ठा riva_par *par, अचिन्हित अक्षर index,
			   अचिन्हित अक्षर val)
अणु
	VGA_WR08(par->riva.PCIO, 0x3d4, index);
	VGA_WR08(par->riva.PCIO, 0x3d5, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर CRTCin(काष्ठा riva_par *par,
				   अचिन्हित अक्षर index)
अणु
	VGA_WR08(par->riva.PCIO, 0x3d4, index);
	वापस (VGA_RD08(par->riva.PCIO, 0x3d5));
पूर्ण

अटल अंतरभूत व्योम GRAout(काष्ठा riva_par *par, अचिन्हित अक्षर index,
			  अचिन्हित अक्षर val)
अणु
	VGA_WR08(par->riva.PVIO, 0x3ce, index);
	VGA_WR08(par->riva.PVIO, 0x3cf, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर GRAin(काष्ठा riva_par *par,
				  अचिन्हित अक्षर index)
अणु
	VGA_WR08(par->riva.PVIO, 0x3ce, index);
	वापस (VGA_RD08(par->riva.PVIO, 0x3cf));
पूर्ण

अटल अंतरभूत व्योम SEQout(काष्ठा riva_par *par, अचिन्हित अक्षर index,
			  अचिन्हित अक्षर val)
अणु
	VGA_WR08(par->riva.PVIO, 0x3c4, index);
	VGA_WR08(par->riva.PVIO, 0x3c5, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर SEQin(काष्ठा riva_par *par,
				  अचिन्हित अक्षर index)
अणु
	VGA_WR08(par->riva.PVIO, 0x3c4, index);
	वापस (VGA_RD08(par->riva.PVIO, 0x3c5));
पूर्ण

अटल अंतरभूत व्योम ATTRout(काष्ठा riva_par *par, अचिन्हित अक्षर index,
			   अचिन्हित अक्षर val)
अणु
	VGA_WR08(par->riva.PCIO, 0x3c0, index);
	VGA_WR08(par->riva.PCIO, 0x3c0, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर ATTRin(काष्ठा riva_par *par,
				   अचिन्हित अक्षर index)
अणु
	VGA_WR08(par->riva.PCIO, 0x3c0, index);
	वापस (VGA_RD08(par->riva.PCIO, 0x3c1));
पूर्ण

अटल अंतरभूत व्योम MISCout(काष्ठा riva_par *par, अचिन्हित अक्षर val)
अणु
	VGA_WR08(par->riva.PVIO, 0x3c2, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर MISCin(काष्ठा riva_par *par)
अणु
	वापस (VGA_RD08(par->riva.PVIO, 0x3cc));
पूर्ण

अटल अंतरभूत व्योम reverse_order(u32 *l)
अणु
	u8 *a = (u8 *)l;
	a[0] = bitrev8(a[0]);
	a[1] = bitrev8(a[1]);
	a[2] = bitrev8(a[2]);
	a[3] = bitrev8(a[3]);
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * cursor stuff
 *
 * ------------------------------------------------------------------------- */

/**
 * rivafb_load_cursor_image - load cursor image to hardware
 * @data8: address to monochrome biपंचांगap (1 = क्रमeground color, 0 = background)
 * @par:  poपूर्णांकer to निजी data
 * @w:    width of cursor image in pixels
 * @h:    height of cursor image in scanlines
 * @bg:   background color (ARGB1555) - alpha bit determines opacity
 * @fg:   क्रमeground color (ARGB1555)
 *
 * DESCRIPTiON:
 * Loads cursor image based on a monochrome source and mask biपंचांगap.  The
 * image bits determines the color of the pixel, 0 क्रम background, 1 क्रम
 * क्रमeground.  Only the affected region (as determined by @w and @h 
 * parameters) will be updated.
 *
 * CALLED FROM:
 * rivafb_cursor()
 */
अटल व्योम rivafb_load_cursor_image(काष्ठा riva_par *par, u8 *data8,
				     u16 bg, u16 fg, u32 w, u32 h)
अणु
	पूर्णांक i, j, k = 0;
	u32 b, पंचांगp;
	u32 *data = (u32 *)data8;
	bg = le16_to_cpu(bg);
	fg = le16_to_cpu(fg);

	w = (w + 1) & ~1;

	क्रम (i = 0; i < h; i++) अणु
		b = *data++;
		reverse_order(&b);
		
		क्रम (j = 0; j < w/2; j++) अणु
			पंचांगp = 0;
#अगर defined (__BIG_ENDIAN)
			पंचांगp = (b & (1 << 31)) ? fg << 16 : bg << 16;
			b <<= 1;
			पंचांगp |= (b & (1 << 31)) ? fg : bg;
			b <<= 1;
#अन्यथा
			पंचांगp = (b & 1) ? fg : bg;
			b >>= 1;
			पंचांगp |= (b & 1) ? fg << 16 : bg << 16;
			b >>= 1;
#पूर्ण_अगर
			ग_लिखोl(पंचांगp, &par->riva.CURSOR[k++]);
		पूर्ण
		k += (MAX_CURS - w)/2;
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * general utility functions
 *
 * ------------------------------------------------------------------------- */

/**
 * riva_wclut - set CLUT entry
 * @chip: poपूर्णांकer to RIVA_HW_INST object
 * @regnum: रेजिस्टर number
 * @red: red component
 * @green: green component
 * @blue: blue component
 *
 * DESCRIPTION:
 * Sets color रेजिस्टर @regnum.
 *
 * CALLED FROM:
 * rivafb_setcolreg()
 */
अटल व्योम riva_wclut(RIVA_HW_INST *chip,
		       अचिन्हित अक्षर regnum, अचिन्हित अक्षर red,
		       अचिन्हित अक्षर green, अचिन्हित अक्षर blue)
अणु
	VGA_WR08(chip->PDIO, 0x3c8, regnum);
	VGA_WR08(chip->PDIO, 0x3c9, red);
	VGA_WR08(chip->PDIO, 0x3c9, green);
	VGA_WR08(chip->PDIO, 0x3c9, blue);
पूर्ण

/**
 * riva_rclut - पढ़ो fromCLUT रेजिस्टर
 * @chip: poपूर्णांकer to RIVA_HW_INST object
 * @regnum: रेजिस्टर number
 * @red: red component
 * @green: green component
 * @blue: blue component
 *
 * DESCRIPTION:
 * Reads red, green, and blue from color रेजिस्टर @regnum.
 *
 * CALLED FROM:
 * rivafb_setcolreg()
 */
अटल व्योम riva_rclut(RIVA_HW_INST *chip,
		       अचिन्हित अक्षर regnum, अचिन्हित अक्षर *red,
		       अचिन्हित अक्षर *green, अचिन्हित अक्षर *blue)
अणु
	
	VGA_WR08(chip->PDIO, 0x3c7, regnum);
	*red = VGA_RD08(chip->PDIO, 0x3c9);
	*green = VGA_RD08(chip->PDIO, 0x3c9);
	*blue = VGA_RD08(chip->PDIO, 0x3c9);
पूर्ण

/**
 * riva_save_state - saves current chip state
 * @par: poपूर्णांकer to riva_par object containing info क्रम current riva board
 * @regs: poपूर्णांकer to riva_regs object
 *
 * DESCRIPTION:
 * Saves current chip state to @regs.
 *
 * CALLED FROM:
 * rivafb_probe()
 */
/* from GGI */
अटल व्योम riva_save_state(काष्ठा riva_par *par, काष्ठा riva_regs *regs)
अणु
	पूर्णांक i;

	NVTRACE_ENTER();
	par->riva.LockUnlock(&par->riva, 0);

	par->riva.UnloadStateExt(&par->riva, &regs->ext);

	regs->misc_output = MISCin(par);

	क्रम (i = 0; i < NUM_CRT_REGS; i++)
		regs->crtc[i] = CRTCin(par, i);

	क्रम (i = 0; i < NUM_ATC_REGS; i++)
		regs->attr[i] = ATTRin(par, i);

	क्रम (i = 0; i < NUM_GRC_REGS; i++)
		regs->gra[i] = GRAin(par, i);

	क्रम (i = 0; i < NUM_SEQ_REGS; i++)
		regs->seq[i] = SEQin(par, i);
	NVTRACE_LEAVE();
पूर्ण

/**
 * riva_load_state - loads current chip state
 * @par: poपूर्णांकer to riva_par object containing info क्रम current riva board
 * @regs: poपूर्णांकer to riva_regs object
 *
 * DESCRIPTION:
 * Loads chip state from @regs.
 *
 * CALLED FROM:
 * riva_load_video_mode()
 * rivafb_probe()
 * rivafb_हटाओ()
 */
/* from GGI */
अटल व्योम riva_load_state(काष्ठा riva_par *par, काष्ठा riva_regs *regs)
अणु
	RIVA_HW_STATE *state = &regs->ext;
	पूर्णांक i;

	NVTRACE_ENTER();
	CRTCout(par, 0x11, 0x00);

	par->riva.LockUnlock(&par->riva, 0);

	par->riva.LoadStateExt(&par->riva, state);

	MISCout(par, regs->misc_output);

	क्रम (i = 0; i < NUM_CRT_REGS; i++) अणु
		चयन (i) अणु
		हाल 0x19:
		हाल 0x20 ... 0x40:
			अवरोध;
		शेष:
			CRTCout(par, i, regs->crtc[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NUM_ATC_REGS; i++)
		ATTRout(par, i, regs->attr[i]);

	क्रम (i = 0; i < NUM_GRC_REGS; i++)
		GRAout(par, i, regs->gra[i]);

	क्रम (i = 0; i < NUM_SEQ_REGS; i++)
		SEQout(par, i, regs->seq[i]);
	NVTRACE_LEAVE();
पूर्ण

/**
 * riva_load_video_mode - calculate timings
 * @info: poपूर्णांकer to fb_info object containing info क्रम current riva board
 *
 * DESCRIPTION:
 * Calculate some timings and then send em off to riva_load_state().
 *
 * CALLED FROM:
 * rivafb_set_par()
 */
अटल पूर्णांक riva_load_video_mode(काष्ठा fb_info *info)
अणु
	पूर्णांक bpp, width, hDisplaySize, hDisplay, hStart,
	    hEnd, hTotal, height, vDisplay, vStart, vEnd, vTotal, करोtClock;
	पूर्णांक hBlankStart, hBlankEnd, vBlankStart, vBlankEnd;
	पूर्णांक rc;
	काष्ठा riva_par *par = info->par;
	काष्ठा riva_regs newmode;
	
	NVTRACE_ENTER();
	/* समय to calculate */
	rivafb_blank(FB_BLANK_NORMAL, info);

	bpp = info->var.bits_per_pixel;
	अगर (bpp == 16 && info->var.green.length == 5)
		bpp = 15;
	width = info->var.xres_भव;
	hDisplaySize = info->var.xres;
	hDisplay = (hDisplaySize / 8) - 1;
	hStart = (hDisplaySize + info->var.right_margin) / 8 - 1;
	hEnd = (hDisplaySize + info->var.right_margin +
		info->var.hsync_len) / 8 - 1;
	hTotal = (hDisplaySize + info->var.right_margin +
		  info->var.hsync_len + info->var.left_margin) / 8 - 5;
	hBlankStart = hDisplay;
	hBlankEnd = hTotal + 4;

	height = info->var.yres_भव;
	vDisplay = info->var.yres - 1;
	vStart = info->var.yres + info->var.lower_margin - 1;
	vEnd = info->var.yres + info->var.lower_margin +
	       info->var.vsync_len - 1;
	vTotal = info->var.yres + info->var.lower_margin +
		 info->var.vsync_len + info->var.upper_margin + 2;
	vBlankStart = vDisplay;
	vBlankEnd = vTotal + 1;
	करोtClock = 1000000000 / info->var.pixघड़ी;

	स_नकल(&newmode, &reg_ढाँचा, माप(काष्ठा riva_regs));

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
		vTotal |= 1;

	अगर (par->FlatPanel) अणु
		vStart = vTotal - 3;
		vEnd = vTotal - 2;
		vBlankStart = vStart;
		hStart = hTotal - 3;
		hEnd = hTotal - 2;
		hBlankEnd = hTotal + 4;
	पूर्ण

	newmode.crtc[0x0] = Set8Bits (hTotal); 
	newmode.crtc[0x1] = Set8Bits (hDisplay);
	newmode.crtc[0x2] = Set8Bits (hBlankStart);
	newmode.crtc[0x3] = SetBitField (hBlankEnd, 4: 0, 4:0) | SetBit (7);
	newmode.crtc[0x4] = Set8Bits (hStart);
	newmode.crtc[0x5] = SetBitField (hBlankEnd, 5: 5, 7:7)
		| SetBitField (hEnd, 4: 0, 4:0);
	newmode.crtc[0x6] = SetBitField (vTotal, 7: 0, 7:0);
	newmode.crtc[0x7] = SetBitField (vTotal, 8: 8, 0:0)
		| SetBitField (vDisplay, 8: 8, 1:1)
		| SetBitField (vStart, 8: 8, 2:2)
		| SetBitField (vBlankStart, 8: 8, 3:3)
		| SetBit (4)
		| SetBitField (vTotal, 9: 9, 5:5)
		| SetBitField (vDisplay, 9: 9, 6:6)
		| SetBitField (vStart, 9: 9, 7:7);
	newmode.crtc[0x9] = SetBitField (vBlankStart, 9: 9, 5:5)
		| SetBit (6);
	newmode.crtc[0x10] = Set8Bits (vStart);
	newmode.crtc[0x11] = SetBitField (vEnd, 3: 0, 3:0)
		| SetBit (5);
	newmode.crtc[0x12] = Set8Bits (vDisplay);
	newmode.crtc[0x13] = (width / 8) * ((bpp + 1) / 8);
	newmode.crtc[0x15] = Set8Bits (vBlankStart);
	newmode.crtc[0x16] = Set8Bits (vBlankEnd);

	newmode.ext.screen = SetBitField(hBlankEnd,6:6,4:4)
		| SetBitField(vBlankStart,10:10,3:3)
		| SetBitField(vStart,10:10,2:2)
		| SetBitField(vDisplay,10:10,1:1)
		| SetBitField(vTotal,10:10,0:0);
	newmode.ext.horiz  = SetBitField(hTotal,8:8,0:0) 
		| SetBitField(hDisplay,8:8,1:1)
		| SetBitField(hBlankStart,8:8,2:2)
		| SetBitField(hStart,8:8,3:3);
	newmode.ext.extra  = SetBitField(vTotal,11:11,0:0)
		| SetBitField(vDisplay,11:11,2:2)
		| SetBitField(vStart,11:11,4:4)
		| SetBitField(vBlankStart,11:11,6:6); 

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		पूर्णांक पंचांगp = (hTotal >> 1) & ~1;
		newmode.ext.पूर्णांकerlace = Set8Bits(पंचांगp);
		newmode.ext.horiz |= SetBitField(पंचांगp, 8:8,4:4);
	पूर्ण अन्यथा 
		newmode.ext.पूर्णांकerlace = 0xff; /* पूर्णांकerlace off */

	अगर (par->riva.Architecture >= NV_ARCH_10)
		par->riva.CURSOR = (U032 __iomem *)(info->screen_base + par->riva.CursorStart);

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		newmode.misc_output &= ~0x40;
	अन्यथा
		newmode.misc_output |= 0x40;
	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		newmode.misc_output &= ~0x80;
	अन्यथा
		newmode.misc_output |= 0x80;	

	rc = CalcStateExt(&par->riva, &newmode.ext, par->pdev, bpp, width,
			  hDisplaySize, height, करोtClock);
	अगर (rc)
		जाओ out;

	newmode.ext.scale = NV_RD32(par->riva.PRAMDAC, 0x00000848) &
		0xfff000ff;
	अगर (par->FlatPanel == 1) अणु
		newmode.ext.pixel |= (1 << 7);
		newmode.ext.scale |= (1 << 8);
	पूर्ण
	अगर (par->SecondCRTC) अणु
		newmode.ext.head  = NV_RD32(par->riva.PCRTC0, 0x00000860) &
			~0x00001000;
		newmode.ext.head2 = NV_RD32(par->riva.PCRTC0, 0x00002860) |
			0x00001000;
		newmode.ext.crtcOwner = 3;
		newmode.ext.pllsel |= 0x20000800;
		newmode.ext.vpll2 = newmode.ext.vpll;
	पूर्ण अन्यथा अगर (par->riva.twoHeads) अणु
		newmode.ext.head  =  NV_RD32(par->riva.PCRTC0, 0x00000860) |
			0x00001000;
		newmode.ext.head2 =  NV_RD32(par->riva.PCRTC0, 0x00002860) &
			~0x00001000;
		newmode.ext.crtcOwner = 0;
		newmode.ext.vpll2 = NV_RD32(par->riva.PRAMDAC0, 0x00000520);
	पूर्ण
	अगर (par->FlatPanel == 1) अणु
		newmode.ext.pixel |= (1 << 7);
		newmode.ext.scale |= (1 << 8);
	पूर्ण
	newmode.ext.cursorConfig = 0x02000100;
	par->current_state = newmode;
	riva_load_state(par, &par->current_state);
	par->riva.LockUnlock(&par->riva, 0); /* important क्रम HW cursor */

out:
	rivafb_blank(FB_BLANK_UNBLANK, info);
	NVTRACE_LEAVE();

	वापस rc;
पूर्ण

अटल व्योम riva_update_var(काष्ठा fb_var_screeninfo *var,
			    स्थिर काष्ठा fb_videomode *modedb)
अणु
	NVTRACE_ENTER();
	var->xres = var->xres_भव = modedb->xres;
	var->yres = modedb->yres;
        अगर (var->yres_भव < var->yres)
	    var->yres_भव = var->yres;
        var->xoffset = var->yoffset = 0;
        var->pixघड़ी = modedb->pixघड़ी;
        var->left_margin = modedb->left_margin;
        var->right_margin = modedb->right_margin;
        var->upper_margin = modedb->upper_margin;
        var->lower_margin = modedb->lower_margin;
        var->hsync_len = modedb->hsync_len;
        var->vsync_len = modedb->vsync_len;
        var->sync = modedb->sync;
        var->vmode = modedb->vmode;
	NVTRACE_LEAVE();
पूर्ण

/**
 * rivafb_करो_maximize - 
 * @info: poपूर्णांकer to fb_info object containing info क्रम current riva board
 * @var: standard kernel fb changeable data
 * @nom: nom
 * @den: den
 *
 * DESCRIPTION:
 * .
 *
 * RETURNS:
 * -EINVAL on failure, 0 on success
 * 
 *
 * CALLED FROM:
 * rivafb_check_var()
 */
अटल पूर्णांक rivafb_करो_maximize(काष्ठा fb_info *info,
			      काष्ठा fb_var_screeninfo *var,
			      पूर्णांक nom, पूर्णांक den)
अणु
	अटल काष्ठा अणु
		पूर्णांक xres, yres;
	पूर्ण modes[] = अणु
		अणु1600, 1280पूर्ण,
		अणु1280, 1024पूर्ण,
		अणु1024, 768पूर्ण,
		अणु800, 600पूर्ण,
		अणु640, 480पूर्ण,
		अणु-1, -1पूर्ण
	पूर्ण;
	पूर्णांक i;

	NVTRACE_ENTER();
	/* use highest possible भव resolution */
	अगर (var->xres_भव == -1 && var->yres_भव == -1) अणु
		prपूर्णांकk(KERN_WARNING PFX
		       "using maximum available virtual resolution\n");
		क्रम (i = 0; modes[i].xres != -1; i++) अणु
			अगर (modes[i].xres * nom / den * modes[i].yres <
			    info->fix.smem_len)
				अवरोध;
		पूर्ण
		अगर (modes[i].xres == -1) अणु
			prपूर्णांकk(KERN_ERR PFX
			       "could not find a virtual resolution that fits into video memory!!\n");
			NVTRACE("EXIT - EINVAL error\n");
			वापस -EINVAL;
		पूर्ण
		var->xres_भव = modes[i].xres;
		var->yres_भव = modes[i].yres;

		prपूर्णांकk(KERN_INFO PFX
		       "virtual resolution set to maximum of %dx%d\n",
		       var->xres_भव, var->yres_भव);
	पूर्ण अन्यथा अगर (var->xres_भव == -1) अणु
		var->xres_भव = (info->fix.smem_len * den /
			(nom * var->yres_भव)) & ~15;
		prपूर्णांकk(KERN_WARNING PFX
		       "setting virtual X resolution to %d\n", var->xres_भव);
	पूर्ण अन्यथा अगर (var->yres_भव == -1) अणु
		var->xres_भव = (var->xres_भव + 15) & ~15;
		var->yres_भव = info->fix.smem_len * den /
			(nom * var->xres_भव);
		prपूर्णांकk(KERN_WARNING PFX
		       "setting virtual Y resolution to %d\n", var->yres_भव);
	पूर्ण अन्यथा अणु
		var->xres_भव = (var->xres_भव + 15) & ~15;
		अगर (var->xres_भव * nom / den * var->yres_भव > info->fix.smem_len) अणु
			prपूर्णांकk(KERN_ERR PFX
			       "mode %dx%dx%d rejected...resolution too high to fit into video memory!\n",
			       var->xres, var->yres, var->bits_per_pixel);
			NVTRACE("EXIT - EINVAL error\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	
	अगर (var->xres_भव * nom / den >= 8192) अणु
		prपूर्णांकk(KERN_WARNING PFX
		       "virtual X resolution (%d) is too high, lowering to %d\n",
		       var->xres_भव, 8192 * den / nom - 16);
		var->xres_भव = 8192 * den / nom - 16;
	पूर्ण
	
	अगर (var->xres_भव < var->xres) अणु
		prपूर्णांकk(KERN_ERR PFX
		       "virtual X resolution (%d) is smaller than real\n", var->xres_भव);
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres_भव < var->yres) अणु
		prपूर्णांकk(KERN_ERR PFX
		       "virtual Y resolution (%d) is smaller than real\n", var->yres_भव);
		वापस -EINVAL;
	पूर्ण
	अगर (var->yres_भव > 0x7fff/nom)
		var->yres_भव = 0x7fff/nom;
	अगर (var->xres_भव > 0x7fff/nom)
		var->xres_भव = 0x7fff/nom;
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल व्योम
riva_set_pattern(काष्ठा riva_par *par, पूर्णांक clr0, पूर्णांक clr1, पूर्णांक pat0, पूर्णांक pat1)
अणु
	RIVA_FIFO_FREE(par->riva, Patt, 4);
	NV_WR32(&par->riva.Patt->Color0, 0, clr0);
	NV_WR32(&par->riva.Patt->Color1, 0, clr1);
	NV_WR32(par->riva.Patt->Monochrome, 0, pat0);
	NV_WR32(par->riva.Patt->Monochrome, 4, pat1);
पूर्ण

/* acceleration routines */
अटल अंतरभूत व्योम रुको_क्रम_idle(काष्ठा riva_par *par)
अणु
	जबतक (par->riva.Busy(&par->riva));
पूर्ण

/*
 * Set ROP.  Translate X rop पूर्णांकo ROP3.  Internal routine.
 */
अटल व्योम
riva_set_rop_solid(काष्ठा riva_par *par, पूर्णांक rop)
अणु
	riva_set_pattern(par, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
        RIVA_FIFO_FREE(par->riva, Rop, 1);
        NV_WR32(&par->riva.Rop->Rop3, 0, rop);

पूर्ण

अटल व्योम riva_setup_accel(काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;

	RIVA_FIFO_FREE(par->riva, Clip, 2);
	NV_WR32(&par->riva.Clip->TopLeft, 0, 0x0);
	NV_WR32(&par->riva.Clip->WidthHeight, 0,
		(info->var.xres_भव & 0xffff) |
		(info->var.yres_भव << 16));
	riva_set_rop_solid(par, 0xcc);
	रुको_क्रम_idle(par);
पूर्ण

/**
 * riva_get_cmap_len - query current color map length
 * @var: standard kernel fb changeable data
 *
 * DESCRIPTION:
 * Get current color map length.
 *
 * RETURNS:
 * Length of color map
 *
 * CALLED FROM:
 * rivafb_setcolreg()
 */
अटल पूर्णांक riva_get_cmap_len(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक rc = 256;		/* reasonable शेष */

	चयन (var->green.length) अणु
	हाल 8:
		rc = 256;	/* 256 entries (2^8), 8 bpp and RGB8888 */
		अवरोध;
	हाल 5:
		rc = 32;	/* 32 entries (2^5), 16 bpp, RGB555 */
		अवरोध;
	हाल 6:
		rc = 64;	/* 64 entries (2^6), 16 bpp, RGB565 */
		अवरोध;		
	शेष:
		/* should not occur */
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * framebuffer operations
 *
 * ------------------------------------------------------------------------- */

अटल पूर्णांक rivafb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा riva_par *par = info->par;

	NVTRACE_ENTER();
	mutex_lock(&par->खोलो_lock);
	अगर (!par->ref_count) अणु
#अगर_घोषित CONFIG_X86
		स_रखो(&par->state, 0, माप(काष्ठा vgastate));
		par->state.flags = VGA_SAVE_MODE  | VGA_SAVE_FONTS;
		/* save the DAC क्रम Riva128 */
		अगर (par->riva.Architecture == NV_ARCH_03)
			par->state.flags |= VGA_SAVE_CMAP;
		save_vga(&par->state);
#पूर्ण_अगर
		/* vgaHWunlock() + riva unlock (0x7F) */
		CRTCout(par, 0x11, 0xFF);
		par->riva.LockUnlock(&par->riva, 0);
	
		riva_save_state(par, &par->initial_state);
	पूर्ण
	par->ref_count++;
	mutex_unlock(&par->खोलो_lock);
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक rivafb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा riva_par *par = info->par;

	NVTRACE_ENTER();
	mutex_lock(&par->खोलो_lock);
	अगर (!par->ref_count) अणु
		mutex_unlock(&par->खोलो_lock);
		वापस -EINVAL;
	पूर्ण
	अगर (par->ref_count == 1) अणु
		par->riva.LockUnlock(&par->riva, 0);
		par->riva.LoadStateExt(&par->riva, &par->initial_state.ext);
		riva_load_state(par, &par->initial_state);
#अगर_घोषित CONFIG_X86
		restore_vga(&par->state);
#पूर्ण_अगर
		par->riva.LockUnlock(&par->riva, 1);
	पूर्ण
	par->ref_count--;
	mutex_unlock(&par->खोलो_lock);
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक rivafb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	स्थिर काष्ठा fb_videomode *mode;
	काष्ठा riva_par *par = info->par;
	पूर्णांक nom, den;		/* translating from pixels->bytes */
	पूर्णांक mode_valid = 0;
	
	NVTRACE_ENTER();
	चयन (var->bits_per_pixel) अणु
	हाल 1 ... 8:
		var->red.offset = var->green.offset = var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
		var->bits_per_pixel = 8;
		nom = den = 1;
		अवरोध;
	हाल 9 ... 15:
		var->green.length = 5;
		fallthrough;
	हाल 16:
		var->bits_per_pixel = 16;
		/* The Riva128 supports RGB555 only */
		अगर (par->riva.Architecture == NV_ARCH_03)
			var->green.length = 5;
		अगर (var->green.length == 5) अणु
			/* 0rrrrrgg gggbbbbb */
			var->red.offset = 10;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length = 5;
			var->green.length = 5;
			var->blue.length = 5;
		पूर्ण अन्यथा अणु
			/* rrrrrggg gggbbbbb */
			var->red.offset = 11;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length = 5;
			var->green.length = 6;
			var->blue.length = 5;
		पूर्ण
		nom = 2;
		den = 1;
		अवरोध;
	हाल 17 ... 32:
		var->red.length = var->green.length = var->blue.length = 8;
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		nom = 4;
		den = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX
		       "mode %dx%dx%d rejected...color depth not supported.\n",
		       var->xres, var->yres, var->bits_per_pixel);
		NVTRACE("EXIT, returning -EINVAL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!stricपंचांगode) अणु
		अगर (!info->monspecs.vfmax || !info->monspecs.hfmax ||
		    !info->monspecs.dclkmax || !fb_validate_mode(var, info))
			mode_valid = 1;
	पूर्ण

	/* calculate modeline अगर supported by monitor */
	अगर (!mode_valid && info->monspecs.gtf) अणु
		अगर (!fb_get_mode(FB_MAXTIMINGS, 0, var, info))
			mode_valid = 1;
	पूर्ण

	अगर (!mode_valid) अणु
		mode = fb_find_best_mode(var, &info->modelist);
		अगर (mode) अणु
			riva_update_var(var, mode);
			mode_valid = 1;
		पूर्ण
	पूर्ण

	अगर (!mode_valid && info->monspecs.modedb_len)
		वापस -EINVAL;

	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव <= var->yres)
		var->yres_भव = -1;
	अगर (rivafb_करो_maximize(info, var, nom, den) < 0)
		वापस -EINVAL;

	/* truncate xoffset and yoffset to maximum अगर too high */
	अगर (var->xoffset > var->xres_भव - var->xres)
		var->xoffset = var->xres_भव - var->xres - 1;

	अगर (var->yoffset > var->yres_भव - var->yres)
		var->yoffset = var->yres_भव - var->yres - 1;

	var->red.msb_right = 
	    var->green.msb_right =
	    var->blue.msb_right =
	    var->transp.offset = var->transp.length = var->transp.msb_right = 0;
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक rivafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;
	पूर्णांक rc = 0;

	NVTRACE_ENTER();
	/* vgaHWunlock() + riva unlock (0x7F) */
	CRTCout(par, 0x11, 0xFF);
	par->riva.LockUnlock(&par->riva, 0);
	rc = riva_load_video_mode(info);
	अगर (rc)
		जाओ out;
	अगर(!(info->flags & FBINFO_HWACCEL_DISABLED))
		riva_setup_accel(info);
	
	par->cursor_reset = 1;
	info->fix.line_length = (info->var.xres_भव * (info->var.bits_per_pixel >> 3));
	info->fix.visual = (info->var.bits_per_pixel == 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED)
		info->pixmap.scan_align = 1;
	अन्यथा
		info->pixmap.scan_align = 4;

out:
	NVTRACE_LEAVE();
	वापस rc;
पूर्ण

/**
 * rivafb_pan_display
 * @var: standard kernel fb changeable data
 * @info: poपूर्णांकer to fb_info object containing info क्रम current riva board
 *
 * DESCRIPTION:
 * Pan (or wrap, depending on the `vmode' field) the display using the
 * `xoffset' and `yoffset' fields of the `var' काष्ठाure.
 * If the values करोn't fit, वापस -EINVAL.
 *
 * This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
 */
अटल पूर्णांक rivafb_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;
	अचिन्हित पूर्णांक base;

	NVTRACE_ENTER();
	base = var->yoffset * info->fix.line_length + var->xoffset;
	par->riva.SetStartAddress(&par->riva, base);
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक rivafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par= info->par;
	अचिन्हित अक्षर पंचांगp, vesa;

	पंचांगp = SEQin(par, 0x01) & ~0x20;	/* screen on/off */
	vesa = CRTCin(par, 0x1a) & ~0xc0;	/* sync on/off */

	NVTRACE_ENTER();

	अगर (blank)
		पंचांगp |= 0x20;

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		vesa |= 0x80;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		vesa |= 0x40;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		vesa |= 0xc0;
		अवरोध;
	पूर्ण

	SEQout(par, 0x01, पंचांगp);
	CRTCout(par, 0x1a, vesa);

	NVTRACE_LEAVE();

	वापस 0;
पूर्ण

/**
 * rivafb_setcolreg
 * @regno: रेजिस्टर index
 * @red: red component
 * @green: green component
 * @blue: blue component
 * @transp: transparency
 * @info: poपूर्णांकer to fb_info object containing info क्रम current riva board
 *
 * DESCRIPTION:
 * Set a single color रेजिस्टर. The values supplied have a 16 bit
 * magnitude.
 *
 * RETURNS:
 * Return != 0 क्रम invalid regno.
 *
 * CALLED FROM:
 * fbcmap.c:fb_set_cmap()
 */
अटल पूर्णांक rivafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			  अचिन्हित blue, अचिन्हित transp,
			  काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;
	RIVA_HW_INST *chip = &par->riva;
	पूर्णांक i;

	अगर (regno >= riva_get_cmap_len(&info->var))
			वापस -EINVAL;

	अगर (info->var.grayscale) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue =
		    (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	अगर (regno < 16 && info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		((u32 *) info->pseuकरो_palette)[regno] =
			(regno << info->var.red.offset) |
			(regno << info->var.green.offset) |
			(regno << info->var.blue.offset);
		/*
		 * The Riva128 2D engine requires color inक्रमmation in
		 * TrueColor क्रमmat even अगर framebuffer is in DirectColor
		 */
		अगर (par->riva.Architecture == NV_ARCH_03) अणु
			चयन (info->var.bits_per_pixel) अणु
			हाल 16:
				par->palette[regno] = ((red & 0xf800) >> 1) |
					((green & 0xf800) >> 6) |
					((blue & 0xf800) >> 11);
				अवरोध;
			हाल 32:
				par->palette[regno] = ((red & 0xff00) << 8) |
					((green & 0xff00)) |
					((blue & 0xff00) >> 8);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		/* "transparent" stuff is completely ignored. */
		riva_wclut(chip, regno, red >> 8, green >> 8, blue >> 8);
		अवरोध;
	हाल 16:
		अगर (info->var.green.length == 5) अणु
			क्रम (i = 0; i < 8; i++) अणु
				riva_wclut(chip, regno*8+i, red >> 8,
					   green >> 8, blue >> 8);
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 r, g, b;

			अगर (regno < 32) अणु
				क्रम (i = 0; i < 8; i++) अणु
					riva_wclut(chip, regno*8+i,
						   red >> 8, green >> 8,
						   blue >> 8);
				पूर्ण
			पूर्ण
			riva_rclut(chip, regno*4, &r, &g, &b);
			क्रम (i = 0; i < 4; i++)
				riva_wclut(chip, regno*4+i, r,
					   green >> 8, b);
		पूर्ण
		अवरोध;
	हाल 32:
		riva_wclut(chip, regno, red >> 8, green >> 8, blue >> 8);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * rivafb_fillrect - hardware accelerated color fill function
 * @info: poपूर्णांकer to fb_info काष्ठाure
 * @rect: poपूर्णांकer to fb_fillrect काष्ठाure
 *
 * DESCRIPTION:
 * This function fills up a region of framebuffer memory with a solid
 * color with a choice of two dअगरferent ROP's, copy or invert.
 *
 * CALLED FROM:
 * framebuffer hook
 */
अटल व्योम rivafb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा riva_par *par = info->par;
	u_पूर्णांक color, rop = 0;

	अगर ((info->flags & FBINFO_HWACCEL_DISABLED)) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (info->var.bits_per_pixel == 8)
		color = rect->color;
	अन्यथा अणु
		अगर (par->riva.Architecture != NV_ARCH_03)
			color = ((u32 *)info->pseuकरो_palette)[rect->color];
		अन्यथा
			color = par->palette[rect->color];
	पूर्ण

	चयन (rect->rop) अणु
	हाल ROP_XOR:
		rop = 0x66;
		अवरोध;
	हाल ROP_COPY:
	शेष:
		rop = 0xCC;
		अवरोध;
	पूर्ण

	riva_set_rop_solid(par, rop);

	RIVA_FIFO_FREE(par->riva, Biपंचांगap, 1);
	NV_WR32(&par->riva.Biपंचांगap->Color1A, 0, color);

	RIVA_FIFO_FREE(par->riva, Biपंचांगap, 2);
	NV_WR32(&par->riva.Biपंचांगap->UnclippedRectangle[0].TopLeft, 0,
		(rect->dx << 16) | rect->dy);
	mb();
	NV_WR32(&par->riva.Biपंचांगap->UnclippedRectangle[0].WidthHeight, 0,
		(rect->width << 16) | rect->height);
	mb();
	riva_set_rop_solid(par, 0xcc);

पूर्ण

/**
 * rivafb_copyarea - hardware accelerated blit function
 * @info: poपूर्णांकer to fb_info काष्ठाure
 * @region: poपूर्णांकer to fb_copyarea काष्ठाure
 *
 * DESCRIPTION:
 * This copies an area of pixels from one location to another
 *
 * CALLED FROM:
 * framebuffer hook
 */
अटल व्योम rivafb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा riva_par *par = info->par;

	अगर ((info->flags & FBINFO_HWACCEL_DISABLED)) अणु
		cfb_copyarea(info, region);
		वापस;
	पूर्ण

	RIVA_FIFO_FREE(par->riva, Blt, 3);
	NV_WR32(&par->riva.Blt->TopLeftSrc, 0,
		(region->sy << 16) | region->sx);
	NV_WR32(&par->riva.Blt->TopLeftDst, 0,
		(region->dy << 16) | region->dx);
	mb();
	NV_WR32(&par->riva.Blt->WidthHeight, 0,
		(region->height << 16) | region->width);
	mb();
पूर्ण

अटल अंतरभूत व्योम convert_bgcolor_16(u32 *col)
अणु
	*col = ((*col & 0x0000F800) << 8)
		| ((*col & 0x00007E0) << 5)
		| ((*col & 0x0000001F) << 3)
		|	   0xFF000000;
	mb();
पूर्ण

/**
 * rivafb_imageblit: hardware accelerated color expand function
 * @info: poपूर्णांकer to fb_info काष्ठाure
 * @image: poपूर्णांकer to fb_image काष्ठाure
 *
 * DESCRIPTION:
 * If the source is a monochrome biपंचांगap, the function fills up a a region
 * of framebuffer memory with pixels whose color is determined by the bit
 * setting of the biपंचांगap, 1 - क्रमeground, 0 - background.
 *
 * If the source is not a monochrome biपंचांगap, color expansion is not करोne.
 * In this हाल, it is channeled to a software function.
 *
 * CALLED FROM:
 * framebuffer hook
 */
अटल व्योम rivafb_imageblit(काष्ठा fb_info *info, 
			     स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा riva_par *par = info->par;
	u32 fgx = 0, bgx = 0, width, पंचांगp;
	u8 *cdat = (u8 *) image->data;
	अस्थिर u32 __iomem *d;
	पूर्णांक i, size;

	अगर ((info->flags & FBINFO_HWACCEL_DISABLED) || image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		fgx = image->fg_color;
		bgx = image->bg_color;
		अवरोध;
	हाल 16:
	हाल 32:
		अगर (par->riva.Architecture != NV_ARCH_03) अणु
			fgx = ((u32 *)info->pseuकरो_palette)[image->fg_color];
			bgx = ((u32 *)info->pseuकरो_palette)[image->bg_color];
		पूर्ण अन्यथा अणु
			fgx = par->palette[image->fg_color];
			bgx = par->palette[image->bg_color];
		पूर्ण
		अगर (info->var.green.length == 6)
			convert_bgcolor_16(&bgx);	
		अवरोध;
	पूर्ण

	RIVA_FIFO_FREE(par->riva, Biपंचांगap, 7);
	NV_WR32(&par->riva.Biपंचांगap->ClipE.TopLeft, 0,
		(image->dy << 16) | (image->dx & 0xFFFF));
	NV_WR32(&par->riva.Biपंचांगap->ClipE.BottomRight, 0,
		(((image->dy + image->height) << 16) |
		 ((image->dx + image->width) & 0xffff)));
	NV_WR32(&par->riva.Biपंचांगap->Color0E, 0, bgx);
	NV_WR32(&par->riva.Biपंचांगap->Color1E, 0, fgx);
	NV_WR32(&par->riva.Biपंचांगap->WidthHeightInE, 0,
		(image->height << 16) | ((image->width + 31) & ~31));
	NV_WR32(&par->riva.Biपंचांगap->WidthHeightOutE, 0,
		(image->height << 16) | ((image->width + 31) & ~31));
	NV_WR32(&par->riva.Biपंचांगap->Poपूर्णांकE, 0,
		(image->dy << 16) | (image->dx & 0xFFFF));

	d = &par->riva.Biपंचांगap->MonochromeData01E;

	width = (image->width + 31)/32;
	size = width * image->height;
	जबतक (size >= 16) अणु
		RIVA_FIFO_FREE(par->riva, Biपंचांगap, 16);
		क्रम (i = 0; i < 16; i++) अणु
			पंचांगp = *((u32 *)cdat);
			cdat = (u8 *)((u32 *)cdat + 1);
			reverse_order(&पंचांगp);
			NV_WR32(d, i*4, पंचांगp);
		पूर्ण
		size -= 16;
	पूर्ण
	अगर (size) अणु
		RIVA_FIFO_FREE(par->riva, Biपंचांगap, size);
		क्रम (i = 0; i < size; i++) अणु
			पंचांगp = *((u32 *) cdat);
			cdat = (u8 *)((u32 *)cdat + 1);
			reverse_order(&पंचांगp);
			NV_WR32(d, i*4, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * rivafb_cursor - hardware cursor function
 * @info: poपूर्णांकer to info काष्ठाure
 * @cursor: poपूर्णांकer to fbcursor काष्ठाure
 *
 * DESCRIPTION:
 * A cursor function that supports displaying a cursor image via hardware.
 * Within the kernel, copy and invert rops are supported.  If exported
 * to user space, only the copy rop will be supported.
 *
 * CALLED FROM
 * framebuffer hook
 */
अटल पूर्णांक rivafb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा riva_par *par = info->par;
	u8 data[MAX_CURS * MAX_CURS/8];
	पूर्णांक i, set = cursor->set;
	u16 fg, bg;

	अगर (cursor->image.width > MAX_CURS || cursor->image.height > MAX_CURS)
		वापस -ENXIO;

	par->riva.ShowHideCursor(&par->riva, 0);

	अगर (par->cursor_reset) अणु
		set = FB_CUR_SETALL;
		par->cursor_reset = 0;
	पूर्ण

	अगर (set & FB_CUR_SETSIZE)
		स_रखो_io(par->riva.CURSOR, 0, MAX_CURS * MAX_CURS * 2);

	अगर (set & FB_CUR_SETPOS) अणु
		u32 xx, yy, temp;

		yy = cursor->image.dy - info->var.yoffset;
		xx = cursor->image.dx - info->var.xoffset;
		temp = xx & 0xFFFF;
		temp |= yy << 16;

		NV_WR32(par->riva.PRAMDAC, 0x0000300, temp);
	पूर्ण


	अगर (set & (FB_CUR_SETSHAPE | FB_CUR_SETCMAP | FB_CUR_SETIMAGE)) अणु
		u32 bg_idx = cursor->image.bg_color;
		u32 fg_idx = cursor->image.fg_color;
		u32 s_pitch = (cursor->image.width+7) >> 3;
		u32 d_pitch = MAX_CURS/8;
		u8 *dat = (u8 *) cursor->image.data;
		u8 *msk = (u8 *) cursor->mask;
		u8 *src;
		
		src = kदो_स्मृति_array(s_pitch, cursor->image.height, GFP_ATOMIC);

		अगर (src) अणु
			चयन (cursor->rop) अणु
			हाल ROP_XOR:
				क्रम (i = 0; i < s_pitch * cursor->image.height; i++)
					src[i] = dat[i] ^ msk[i];
				अवरोध;
			हाल ROP_COPY:
			शेष:
				क्रम (i = 0; i < s_pitch * cursor->image.height; i++)
					src[i] = dat[i] & msk[i];
				अवरोध;
			पूर्ण

			fb_pad_aligned_buffer(data, d_pitch, src, s_pitch,
						cursor->image.height);

			bg = ((info->cmap.red[bg_idx] & 0xf8) << 7) |
				((info->cmap.green[bg_idx] & 0xf8) << 2) |
				((info->cmap.blue[bg_idx] & 0xf8) >> 3) |
				1 << 15;

			fg = ((info->cmap.red[fg_idx] & 0xf8) << 7) |
				((info->cmap.green[fg_idx] & 0xf8) << 2) |
				((info->cmap.blue[fg_idx] & 0xf8) >> 3) |
				1 << 15;

			par->riva.LockUnlock(&par->riva, 0);

			rivafb_load_cursor_image(par, data, bg, fg,
						 cursor->image.width,
						 cursor->image.height);
			kमुक्त(src);
		पूर्ण
	पूर्ण

	अगर (cursor->enable)
		par->riva.ShowHideCursor(&par->riva, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक rivafb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;

	रुको_क्रम_idle(par);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * initialization helper functions
 *
 * ------------------------------------------------------------------------- */

/* kernel पूर्णांकerface */
अटल स्थिर काष्ठा fb_ops riva_fb_ops = अणु
	.owner 		= THIS_MODULE,
	.fb_खोलो	= rivafb_खोलो,
	.fb_release	= rivafb_release,
	.fb_check_var 	= rivafb_check_var,
	.fb_set_par 	= rivafb_set_par,
	.fb_setcolreg 	= rivafb_setcolreg,
	.fb_pan_display	= rivafb_pan_display,
	.fb_blank 	= rivafb_blank,
	.fb_fillrect 	= rivafb_fillrect,
	.fb_copyarea 	= rivafb_copyarea,
	.fb_imageblit 	= rivafb_imageblit,
	.fb_cursor	= rivafb_cursor,	
	.fb_sync 	= rivafb_sync,
पूर्ण;

अटल पूर्णांक riva_set_fbinfo(काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक cmap_len;
	काष्ठा riva_par *par = info->par;

	NVTRACE_ENTER();
	info->flags = FBINFO_DEFAULT
		    | FBINFO_HWACCEL_XPAN
		    | FBINFO_HWACCEL_YPAN
		    | FBINFO_HWACCEL_COPYAREA
		    | FBINFO_HWACCEL_FILLRECT
	            | FBINFO_HWACCEL_IMAGEBLIT;

	/* Accel seems to not work properly on NV30 yet...*/
	अगर ((par->riva.Architecture == NV_ARCH_30) || noaccel) अणु
	    	prपूर्णांकk(KERN_DEBUG PFX "disabling acceleration\n");
  		info->flags |= FBINFO_HWACCEL_DISABLED;
	पूर्ण

	info->var = rivafb_शेष_var;
	info->fix.visual = (info->var.bits_per_pixel == 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;

	info->pseuकरो_palette = par->pseuकरो_palette;

	cmap_len = riva_get_cmap_len(&info->var);
	fb_alloc_cmap(&info->cmap, cmap_len, 0);	

	info->pixmap.size = 8 * 1024;
	info->pixmap.buf_align = 4;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;
	info->var.yres_भव = -1;
	NVTRACE_LEAVE();
	वापस (rivafb_check_var(&info->var, info));
पूर्ण

अटल पूर्णांक riva_get_EDID_OF(काष्ठा fb_info *info, काष्ठा pci_dev *pd)
अणु
	काष्ठा riva_par *par = info->par;
	काष्ठा device_node *dp;
	स्थिर अचिन्हित अक्षर *pedid = शून्य;
	स्थिर अचिन्हित अक्षर *disptype = शून्य;
	अटल अक्षर *propnames[] = अणु
		"DFP,EDID", "LCD,EDID", "EDID", "EDID1", "EDID,B", "EDID,A", शून्य पूर्ण;
	पूर्णांक i;

	NVTRACE_ENTER();
	dp = pci_device_to_OF_node(pd);
	क्रम (; dp != शून्य; dp = dp->child) अणु
		disptype = of_get_property(dp, "display-type", शून्य);
		अगर (disptype == शून्य)
			जारी;
		अगर (म_भेदन(disptype, "LCD", 3) != 0)
			जारी;
		क्रम (i = 0; propnames[i] != शून्य; ++i) अणु
			pedid = of_get_property(dp, propnames[i], शून्य);
			अगर (pedid != शून्य) अणु
				par->EDID = (अचिन्हित अक्षर *)pedid;
				NVTRACE("LCD found.\n");
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

#अगर defined(CONFIG_FB_RIVA_I2C)
अटल पूर्णांक riva_get_EDID_i2c(काष्ठा fb_info *info)
अणु
	काष्ठा riva_par *par = info->par;
	काष्ठा fb_var_screeninfo var;
	पूर्णांक i;

	NVTRACE_ENTER();
	par->riva.LockUnlock(&par->riva, 0);
	riva_create_i2c_busses(par);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!par->chan[i].par)
			जारी;
		riva_probe_i2c_connector(par, i, &par->EDID);
		अगर (par->EDID && !fb_parse_edid(par->EDID, &var)) अणु
			prपूर्णांकk(PFX "Found EDID Block from BUS %i\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	NVTRACE_LEAVE();
	वापस (par->EDID) ? 1 : 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_RIVA_I2C */

अटल व्योम riva_update_शेष_var(काष्ठा fb_var_screeninfo *var,
				    काष्ठा fb_info *info)
अणु
	काष्ठा fb_monspecs *specs = &info->monspecs;
	काष्ठा fb_videomode modedb;

	NVTRACE_ENTER();
	/* respect mode options */
	अगर (mode_option) अणु
		fb_find_mode(var, info, mode_option,
			     specs->modedb, specs->modedb_len,
			     शून्य, 8);
	पूर्ण अन्यथा अगर (specs->modedb != शून्य) अणु
		/* get first mode in database as fallback */
		modedb = specs->modedb[0];
		/* get preferred timing */
		अगर (info->monspecs.misc & FB_MISC_1ST_DETAIL) अणु
			पूर्णांक i;

			क्रम (i = 0; i < specs->modedb_len; i++) अणु
				अगर (specs->modedb[i].flag & FB_MODE_IS_FIRST) अणु
					modedb = specs->modedb[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		var->bits_per_pixel = 8;
		riva_update_var(var, &modedb);
	पूर्ण
	NVTRACE_LEAVE();
पूर्ण


अटल व्योम riva_get_EDID(काष्ठा fb_info *info, काष्ठा pci_dev *pdev)
अणु
	NVTRACE_ENTER();
	अगर (riva_get_EDID_OF(info, pdev)) अणु
		NVTRACE_LEAVE();
		वापस;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_OF))
		prपूर्णांकk(PFX "could not retrieve EDID from OF\n");
#अगर defined(CONFIG_FB_RIVA_I2C)
	अगर (!riva_get_EDID_i2c(info))
		prपूर्णांकk(PFX "could not retrieve EDID from DDC/I2C\n");
#पूर्ण_अगर
	NVTRACE_LEAVE();
पूर्ण


अटल व्योम riva_get_edidinfo(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &rivafb_शेष_var;
	काष्ठा riva_par *par = info->par;

	fb_edid_to_monspecs(par->EDID, &info->monspecs);
	fb_videomode_to_modelist(info->monspecs.modedb, info->monspecs.modedb_len,
				 &info->modelist);
	riva_update_शेष_var(var, info);

	/* अगर user specअगरied flatpanel, we respect that */
	अगर (info->monspecs.input & FB_DISP_DDI)
		par->FlatPanel = 1;
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * PCI bus
 *
 * ------------------------------------------------------------------------- */

अटल u32 riva_get_arch(काष्ठा pci_dev *pd)
अणु
    	u32 arch = 0;

	चयन (pd->device & 0x0ff0) अणु
		हाल 0x0100:   /* GeForce 256 */
		हाल 0x0110:   /* GeForce2 MX */
		हाल 0x0150:   /* GeForce2 */
		हाल 0x0170:   /* GeForce4 MX */
		हाल 0x0180:   /* GeForce4 MX (8x AGP) */
		हाल 0x01A0:   /* nForce */
		हाल 0x01F0:   /* nForce2 */
		     arch =  NV_ARCH_10;
		     अवरोध;
		हाल 0x0200:   /* GeForce3 */
		हाल 0x0250:   /* GeForce4 Ti */
		हाल 0x0280:   /* GeForce4 Ti (8x AGP) */
		     arch =  NV_ARCH_20;
		     अवरोध;
		हाल 0x0300:   /* GeForceFX 5800 */
		हाल 0x0310:   /* GeForceFX 5600 */
		हाल 0x0320:   /* GeForceFX 5200 */
		हाल 0x0330:   /* GeForceFX 5900 */
		हाल 0x0340:   /* GeForceFX 5700 */
		     arch =  NV_ARCH_30;
		     अवरोध;
		हाल 0x0020:   /* TNT, TNT2 */
		     arch =  NV_ARCH_04;
		     अवरोध;
		हाल 0x0010:   /* Riva128 */
		     arch =  NV_ARCH_03;
		     अवरोध;
		शेष:   /* unknown architecture */
		     अवरोध;
	पूर्ण
	वापस arch;
पूर्ण

अटल पूर्णांक rivafb_probe(काष्ठा pci_dev *pd, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा riva_par *शेष_par;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	NVTRACE_ENTER();
	निश्चित(pd != शून्य);

	info = framebuffer_alloc(माप(काष्ठा riva_par), &pd->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ err_ret;
	पूर्ण
	शेष_par = info->par;
	शेष_par->pdev = pd;

	info->pixmap.addr = kzalloc(8 * 1024, GFP_KERNEL);
	अगर (info->pixmap.addr == शून्य) अणु
	    	ret = -ENOMEM;
		जाओ err_framebuffer_release;
	पूर्ण

	ret = pci_enable_device(pd);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot enable PCI device\n");
		जाओ err_मुक्त_pixmap;
	पूर्ण

	ret = pci_request_regions(pd, "rivafb");
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot request PCI regions\n");
		जाओ err_disable_device;
	पूर्ण

	mutex_init(&शेष_par->खोलो_lock);
	शेष_par->riva.Architecture = riva_get_arch(pd);

	शेष_par->Chipset = (pd->venकरोr << 16) | pd->device;
	prपूर्णांकk(KERN_INFO PFX "nVidia device/chipset %X\n",शेष_par->Chipset);
	
	अगर(शेष_par->riva.Architecture == 0) अणु
		prपूर्णांकk(KERN_ERR PFX "unknown NV_ARCH\n");
		ret=-ENODEV;
		जाओ err_release_region;
	पूर्ण
	अगर(शेष_par->riva.Architecture == NV_ARCH_10 ||
	   शेष_par->riva.Architecture == NV_ARCH_20 ||
	   शेष_par->riva.Architecture == NV_ARCH_30) अणु
		प्र_लिखो(rivafb_fix.id, "NV%x", (pd->device & 0x0ff0) >> 4);
	पूर्ण अन्यथा अणु
		प्र_लिखो(rivafb_fix.id, "NV%x", शेष_par->riva.Architecture);
	पूर्ण

	शेष_par->FlatPanel = flatpanel;
	अगर (flatpanel == 1)
		prपूर्णांकk(KERN_INFO PFX "flatpanel support enabled\n");
	शेष_par->क्रमceCRTC = क्रमceCRTC;
	
	rivafb_fix.mmio_len = pci_resource_len(pd, 0);
	rivafb_fix.smem_len = pci_resource_len(pd, 1);

	अणु
		/* enable IO and mem अगर not alपढ़ोy करोne */
		अचिन्हित लघु cmd;

		pci_पढ़ो_config_word(pd, PCI_COMMAND, &cmd);
		cmd |= (PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
		pci_ग_लिखो_config_word(pd, PCI_COMMAND, cmd);
	पूर्ण
	
	rivafb_fix.mmio_start = pci_resource_start(pd, 0);
	rivafb_fix.smem_start = pci_resource_start(pd, 1);

	शेष_par->ctrl_base = ioremap(rivafb_fix.mmio_start,
					 rivafb_fix.mmio_len);
	अगर (!शेष_par->ctrl_base) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot ioremap MMIO base\n");
		ret = -EIO;
		जाओ err_release_region;
	पूर्ण

	चयन (शेष_par->riva.Architecture) अणु
	हाल NV_ARCH_03:
		/* Riva128's PRAMIN is in the "framebuffer" space
		 * Since these cards were never made with more than 8 megabytes
		 * we can safely allocate this separately.
		 */
		शेष_par->riva.PRAMIN = ioremap(rivafb_fix.smem_start + 0x00C00000, 0x00008000);
		अगर (!शेष_par->riva.PRAMIN) अणु
			prपूर्णांकk(KERN_ERR PFX "cannot ioremap PRAMIN region\n");
			ret = -EIO;
			जाओ err_iounmap_ctrl_base;
		पूर्ण
		अवरोध;
	हाल NV_ARCH_04:
	हाल NV_ARCH_10:
	हाल NV_ARCH_20:
	हाल NV_ARCH_30:
		शेष_par->riva.PCRTC0 =
			(u32 __iomem *)(शेष_par->ctrl_base + 0x00600000);
		शेष_par->riva.PRAMIN =
			(u32 __iomem *)(शेष_par->ctrl_base + 0x00710000);
		अवरोध;
	पूर्ण
	riva_common_setup(शेष_par);

	अगर (शेष_par->riva.Architecture == NV_ARCH_03) अणु
		शेष_par->riva.PCRTC = शेष_par->riva.PCRTC0
		                        = शेष_par->riva.PGRAPH;
	पूर्ण

	rivafb_fix.smem_len = riva_get_memlen(शेष_par) * 1024;
	शेष_par->dclk_max = riva_get_maxdclk(शेष_par) * 1000;
	info->screen_base = ioremap_wc(rivafb_fix.smem_start,
				       rivafb_fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot ioremap FB base\n");
		ret = -EIO;
		जाओ err_iounmap_pramin;
	पूर्ण

	अगर (!nomtrr)
		शेष_par->wc_cookie =
			arch_phys_wc_add(rivafb_fix.smem_start,
					 rivafb_fix.smem_len);

	info->fbops = &riva_fb_ops;
	info->fix = rivafb_fix;
	riva_get_EDID(info, pd);
	riva_get_edidinfo(info);

	ret=riva_set_fbinfo(info);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "error setting initial video mode\n");
		जाओ err_iounmap_screen_base;
	पूर्ण

	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	pci_set_drvdata(pd, info);

	अगर (backlight)
		riva_bl_init(info->par);

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR PFX
			"error registering riva framebuffer\n");
		जाओ err_iounmap_screen_base;
	पूर्ण

	prपूर्णांकk(KERN_INFO PFX
		"PCI nVidia %s framebuffer ver %s (%dMB @ 0x%lX)\n",
		info->fix.id,
		RIVAFB_VERSION,
		info->fix.smem_len / (1024 * 1024),
		info->fix.smem_start);

	NVTRACE_LEAVE();
	वापस 0;

err_iounmap_screen_base:
#अगर_घोषित CONFIG_FB_RIVA_I2C
	riva_delete_i2c_busses(info->par);
#पूर्ण_अगर
	iounmap(info->screen_base);
err_iounmap_pramin:
	अगर (शेष_par->riva.Architecture == NV_ARCH_03) 
		iounmap(शेष_par->riva.PRAMIN);
err_iounmap_ctrl_base:
	iounmap(शेष_par->ctrl_base);
err_release_region:
	pci_release_regions(pd);
err_disable_device:
err_मुक्त_pixmap:
	kमुक्त(info->pixmap.addr);
err_framebuffer_release:
	framebuffer_release(info);
err_ret:
	वापस ret;
पूर्ण

अटल व्योम rivafb_हटाओ(काष्ठा pci_dev *pd)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pd);
	काष्ठा riva_par *par = info->par;
	
	NVTRACE_ENTER();

#अगर_घोषित CONFIG_FB_RIVA_I2C
	riva_delete_i2c_busses(par);
	kमुक्त(par->EDID);
#पूर्ण_अगर

	unरेजिस्टर_framebuffer(info);

	riva_bl_निकास(info);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(par->ctrl_base);
	iounmap(info->screen_base);
	अगर (par->riva.Architecture == NV_ARCH_03)
		iounmap(par->riva.PRAMIN);
	pci_release_regions(pd);
	kमुक्त(info->pixmap.addr);
	framebuffer_release(info);
	NVTRACE_LEAVE();
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * initialization
 *
 * ------------------------------------------------------------------------- */

#अगर_अघोषित MODULE
अटल पूर्णांक rivafb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	NVTRACE_ENTER();
	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "forceCRTC", 9)) अणु
			अक्षर *p;
			
			p = this_opt + 9;
			अगर (!*p || !*(++p)) जारी; 
			क्रमceCRTC = *p - '0';
			अगर (क्रमceCRTC < 0 || क्रमceCRTC > 1) 
				क्रमceCRTC = -1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "flatpanel", 9)) अणु
			flatpanel = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "backlight:", 10)) अणु
			backlight = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6)) अणु
			nomtrr = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "strictmode", 10)) अणु
			stricपंचांगode = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "noaccel", 7)) अणु
			noaccel = 1;
		पूर्ण अन्यथा
			mode_option = this_opt;
	पूर्ण
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !MODULE */

अटल काष्ठा pci_driver rivafb_driver = अणु
	.name		= "rivafb",
	.id_table	= rivafb_pci_tbl,
	.probe		= rivafb_probe,
	.हटाओ		= rivafb_हटाओ,
पूर्ण;



/* ------------------------------------------------------------------------- *
 *
 * modularization
 *
 * ------------------------------------------------------------------------- */

अटल पूर्णांक rivafb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("rivafb", &option))
		वापस -ENODEV;
	rivafb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&rivafb_driver);
पूर्ण


module_init(rivafb_init);

अटल व्योम __निकास rivafb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rivafb_driver);
पूर्ण

module_निकास(rivafb_निकास);

module_param(noaccel, bool, 0);
MODULE_PARM_DESC(noaccel, "bool: disable acceleration");
module_param(flatpanel, पूर्णांक, 0);
MODULE_PARM_DESC(flatpanel, "Enables experimental flat panel support for some chipsets. (0 or 1=enabled) (default=0)");
module_param(क्रमceCRTC, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमceCRTC, "Forces usage of a particular CRTC in case autodetection fails. (0 or 1) (default=autodetect)");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "Disables MTRR support (0 or 1=disabled) (default=0)");
module_param(stricपंचांगode, bool, 0);
MODULE_PARM_DESC(stricपंचांगode, "Only use video modes from EDID");

MODULE_AUTHOR("Ani Joshi, maintainer");
MODULE_DESCRIPTION("Framebuffer driver for nVidia Riva 128, TNT, TNT2, and the GeForce series");
MODULE_LICENSE("GPL");
