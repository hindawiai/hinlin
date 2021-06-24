<शैली गुरु>
/*
 *  ATI Frame Buffer Device Driver Core
 *
 *	Copyright (C) 2004  Alex Kern <alex.kern@gmx.de>
 *	Copyright (C) 1997-2001  Geert Uytterhoeven
 *	Copyright (C) 1998  Bernd Harries
 *	Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 *
 *  This driver supports the following ATI graphics chips:
 *    - ATI Mach64
 *
 *  To करो: add support क्रम
 *    - ATI Rage128 (from aty128fb.c)
 *    - ATI Radeon (from radeonfb.c)
 *
 *  This driver is partly based on the PowerMac console driver:
 *
 *	Copyright (C) 1996 Paul Mackerras
 *
 *  and on the PowerMac ATI/mach64 display driver:
 *
 *	Copyright (C) 1997 Michael AK Tesch
 *
 *	      with work by Jon Howell
 *			   Harry AC Eaton
 *			   Anthony Tong <atong@uiuc.edu>
 *
 *  Generic LCD support written by Daniel Mantione, ported from 2.4.20 by Alex Kern
 *  Many Thanks to Ville Syrjथअlथअ क्रम patches and fixing nasting 16 bit color bug.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 *  Many thanks to Nitya from ATI devrel क्रम support and patience !
 */

/******************************************************************************

  TODO:

    - cursor support on all cards and all ramdacs.
    - cursor parameters controlable via ioctl()s.
    - guess PLL and MCLK based on the original PLL रेजिस्टर values initialized
      by Open Firmware (अगर they are initialized). BIOS is करोne

    (Anyone with Mac to help with this?)

******************************************************************************/

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/compiler.h>
#समावेश <linux/console.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/backlight.h>
#समावेश <linux/reboot.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <video/mach64.h>
#समावेश "atyfb.h"
#समावेश "ati_ids.h"

#अगर_घोषित __घातerpc__
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश "../macmodes.h"
#पूर्ण_अगर
#अगर_घोषित __sparc__
#समावेश <यंत्र/fbपन.स>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ADB_PMU
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_BOOTX_TEXT
#समावेश <यंत्र/btext.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

/*
 * Debug flags.
 */
#अघोषित DEBUG
/*#घोषणा DEBUG*/

/* Make sure n * PAGE_SIZE is रक्षित at end of Aperture क्रम GUI-regs */
/*  - must be large enough to catch all GUI-Regs   */
/*  - must be aligned to a PAGE boundary           */
#घोषणा GUI_RESERVE	(1 * PAGE_SIZE)

/* FIXME: हटाओ the FAIL definition */
#घोषणा FAIL(msg) करो अणु \
	अगर (!(var->activate & FB_ACTIVATE_TEST)) \
		prपूर्णांकk(KERN_CRIT "atyfb: " msg "\n"); \
	वापस -EINVAL; \
पूर्ण जबतक (0)
#घोषणा FAIL_MAX(msg, x, _max_) करो अणु \
	अगर (x > _max_) अणु \
		अगर (!(var->activate & FB_ACTIVATE_TEST)) \
			prपूर्णांकk(KERN_CRIT "atyfb: " msg " %x(%x)\n", x, _max_); \
		वापस -EINVAL; \
	पूर्ण \
पूर्ण जबतक (0)
#अगर_घोषित DEBUG
#घोषणा DPRINTK(fmt, args...)	prपूर्णांकk(KERN_DEBUG "atyfb: " fmt, ## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)	no_prपूर्णांकk(fmt, ##args)
#पूर्ण_अगर

#घोषणा PRINTKI(fmt, args...)	prपूर्णांकk(KERN_INFO "atyfb: " fmt, ## args)
#घोषणा PRINTKE(fmt, args...)	prपूर्णांकk(KERN_ERR "atyfb: " fmt, ## args)

#अगर defined(CONFIG_PMAC_BACKLIGHT) || defined(CONFIG_FB_ATY_GENERIC_LCD) || \
defined(CONFIG_FB_ATY_BACKLIGHT) || defined (CONFIG_PPC_PMAC)
अटल स्थिर u32 lt_lcd_regs[] = अणु
	CNFG_PANEL_LG,
	LCD_GEN_CNTL_LG,
	DSTN_CONTROL_LG,
	HFB_PITCH_ADDR_LG,
	HORZ_STRETCHING_LG,
	VERT_STRETCHING_LG,
	0, /* EXT_VERT_STRETCH */
	LT_GIO_LG,
	POWER_MANAGEMENT_LG
पूर्ण;

व्योम aty_st_lcd(पूर्णांक index, u32 val, स्थिर काष्ठा atyfb_par *par)
अणु
	अगर (M64_HAS(LT_LCD_REGS)) अणु
		aty_st_le32(lt_lcd_regs[index], val, par);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ temp;

		/* ग_लिखो addr byte */
		temp = aty_ld_le32(LCD_INDEX, par);
		aty_st_le32(LCD_INDEX, (temp & ~LCD_INDEX_MASK) | index, par);
		/* ग_लिखो the रेजिस्टर value */
		aty_st_le32(LCD_DATA, val, par);
	पूर्ण
पूर्ण

u32 aty_ld_lcd(पूर्णांक index, स्थिर काष्ठा atyfb_par *par)
अणु
	अगर (M64_HAS(LT_LCD_REGS)) अणु
		वापस aty_ld_le32(lt_lcd_regs[index], par);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ temp;

		/* ग_लिखो addr byte */
		temp = aty_ld_le32(LCD_INDEX, par);
		aty_st_le32(LCD_INDEX, (temp & ~LCD_INDEX_MASK) | index, par);
		/* पढ़ो the रेजिस्टर value */
		वापस aty_ld_le32(LCD_DATA, par);
	पूर्ण
पूर्ण
#अन्यथा /* defined(CONFIG_PMAC_BACKLIGHT) || defined(CONFIG_FB_ATY_BACKLIGHT) ||
	 defined(CONFIG_FB_ATY_GENERIC_LCD) || defined(CONFIG_PPC_PMAC) */
व्योम aty_st_lcd(पूर्णांक index, u32 val, स्थिर काष्ठा atyfb_par *par)
अणु पूर्ण

u32 aty_ld_lcd(पूर्णांक index, स्थिर काष्ठा atyfb_par *par)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_PMAC_BACKLIGHT) || defined(CONFIG_FB_ATY_BACKLIGHT) ||
	  defined (CONFIG_FB_ATY_GENERIC_LCD) || defined(CONFIG_PPC_PMAC) */

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
/*
 * ATIReduceRatio --
 *
 * Reduce a fraction by factoring out the largest common भागider of the
 * fraction's numerator and denominator.
 */
अटल व्योम ATIReduceRatio(पूर्णांक *Numerator, पूर्णांक *Denominator)
अणु
	पूर्णांक Multiplier, Divider, Reमुख्यder;

	Multiplier = *Numerator;
	Divider = *Denominator;

	जबतक ((Reमुख्यder = Multiplier % Divider)) अणु
		Multiplier = Divider;
		Divider = Reमुख्यder;
	पूर्ण

	*Numerator /= Divider;
	*Denominator /= Divider;
पूर्ण
#पूर्ण_अगर
/*
 * The Hardware parameters क्रम each card
 */

काष्ठा pci_mmap_map अणु
	अचिन्हित दीर्घ voff;
	अचिन्हित दीर्घ poff;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ prot_flag;
	अचिन्हित दीर्घ prot_mask;
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo atyfb_fix = अणु
	.id		= "ATY Mach64",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.xpanstep	= 8,
	.ypanstep	= 1,
पूर्ण;

/*
 * Frame buffer device API
 */

अटल पूर्णांक atyfb_खोलो(काष्ठा fb_info *info, पूर्णांक user);
अटल पूर्णांक atyfb_release(काष्ठा fb_info *info, पूर्णांक user);
अटल पूर्णांक atyfb_check_var(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info);
अटल पूर्णांक atyfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक atyfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक atyfb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info);
अटल पूर्णांक atyfb_blank(पूर्णांक blank, काष्ठा fb_info *info);
अटल पूर्णांक atyfb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg);
#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक atyfb_compat_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	वापस atyfb_ioctl(info, cmd, (u_दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __sparc__
अटल पूर्णांक atyfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर
अटल पूर्णांक atyfb_sync(काष्ठा fb_info *info);

/*
 * Internal routines
 */

अटल पूर्णांक aty_init(काष्ठा fb_info *info);

अटल व्योम aty_get_crtc(स्थिर काष्ठा atyfb_par *par, काष्ठा crtc *crtc);

अटल व्योम aty_set_crtc(स्थिर काष्ठा atyfb_par *par, स्थिर काष्ठा crtc *crtc);
अटल पूर्णांक aty_var_to_crtc(स्थिर काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_var_screeninfo *var,
			   काष्ठा crtc *crtc);
अटल पूर्णांक aty_crtc_to_var(स्थिर काष्ठा crtc *crtc,
			   काष्ठा fb_var_screeninfo *var);
अटल व्योम set_off_pitch(काष्ठा atyfb_par *par, स्थिर काष्ठा fb_info *info);
#अगर_घोषित CONFIG_PPC
अटल पूर्णांक पढ़ो_aty_sense(स्थिर काष्ठा atyfb_par *par);
#पूर्ण_अगर

अटल DEFINE_MUTEX(reboot_lock);
अटल काष्ठा fb_info *reboot_info;

/*
 * Interface used by the world
 */

अटल काष्ठा fb_var_screeninfo शेष_var = अणु
	/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz करोtघड़ी) */
	640, 480, 640, 480, 0, 0, 8, 0,
	अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण,
	0, 0, -1, -1, 0, 39722, 48, 16, 33, 10, 96, 2,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

अटल स्थिर काष्ठा fb_videomode deभ_शेषe = अणु
	/* 640x480 @ 60 Hz, 31.5 kHz hsync */
	शून्य, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

अटल काष्ठा fb_ops atyfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= atyfb_खोलो,
	.fb_release	= atyfb_release,
	.fb_check_var	= atyfb_check_var,
	.fb_set_par	= atyfb_set_par,
	.fb_setcolreg	= atyfb_setcolreg,
	.fb_pan_display	= atyfb_pan_display,
	.fb_blank	= atyfb_blank,
	.fb_ioctl	= atyfb_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl = atyfb_compat_ioctl,
#पूर्ण_अगर
	.fb_fillrect	= atyfb_fillrect,
	.fb_copyarea	= atyfb_copyarea,
	.fb_imageblit	= atyfb_imageblit,
#अगर_घोषित __sparc__
	.fb_mmap	= atyfb_mmap,
#पूर्ण_अगर
	.fb_sync	= atyfb_sync,
पूर्ण;

अटल bool noaccel;
अटल bool nomtrr;
अटल पूर्णांक vram;
अटल पूर्णांक pll;
अटल पूर्णांक mclk;
अटल पूर्णांक xclk;
अटल पूर्णांक comp_sync = -1;
अटल अक्षर *mode;
अटल पूर्णांक backlight = IS_BUILTIN(CONFIG_PMAC_BACKLIGHT);

#अगर_घोषित CONFIG_PPC
अटल पूर्णांक शेष_vmode = VMODE_CHOOSE;
अटल पूर्णांक शेष_cmode = CMODE_CHOOSE;

module_param_named(vmode, शेष_vmode, पूर्णांक, 0);
MODULE_PARM_DESC(vmode, "int: video mode for mac");
module_param_named(cmode, शेष_cmode, पूर्णांक, 0);
MODULE_PARM_DESC(cmode, "int: color mode for mac");
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATARI
अटल अचिन्हित पूर्णांक mach64_count = 0;
अटल अचिन्हित दीर्घ phys_vmembase[FB_MAX] = अणु 0, पूर्ण;
अटल अचिन्हित दीर्घ phys_size[FB_MAX] = अणु 0, पूर्ण;
अटल अचिन्हित दीर्घ phys_guiregbase[FB_MAX] = अणु 0, पूर्ण;
#पूर्ण_अगर

/* top -> करोwn is an evolution of mach64 chipset, any corrections? */
#घोषणा ATI_CHIP_88800GX   (M64F_GX)
#घोषणा ATI_CHIP_88800CX   (M64F_GX)

#घोषणा ATI_CHIP_264CT     (M64F_CT | M64F_INTEGRATED | M64F_CT_BUS | M64F_MAGIC_FIFO)
#घोषणा ATI_CHIP_264ET     (M64F_CT | M64F_INTEGRATED | M64F_CT_BUS | M64F_MAGIC_FIFO)

#घोषणा ATI_CHIP_264VT     (M64F_VT | M64F_INTEGRATED | M64F_VT_BUS | M64F_MAGIC_FIFO)
#घोषणा ATI_CHIP_264GT     (M64F_GT | M64F_INTEGRATED               | M64F_MAGIC_FIFO | M64F_EXTRA_BRIGHT)

#घोषणा ATI_CHIP_264VTB    (M64F_VT | M64F_INTEGRATED | M64F_VT_BUS | M64F_GTB_DSP)
#घोषणा ATI_CHIP_264VT3    (M64F_VT | M64F_INTEGRATED | M64F_VT_BUS | M64F_GTB_DSP | M64F_SDRAM_MAGIC_PLL)
#घोषणा ATI_CHIP_264VT4    (M64F_VT | M64F_INTEGRATED               | M64F_GTB_DSP)

/* FIXME what is this chip? */
#घोषणा ATI_CHIP_264LT     (M64F_GT | M64F_INTEGRATED               | M64F_GTB_DSP)

/* make sets लघुer */
#घोषणा ATI_MODERN_SET     (M64F_GT | M64F_INTEGRATED               | M64F_GTB_DSP | M64F_EXTRA_BRIGHT)

#घोषणा ATI_CHIP_264GTB    (ATI_MODERN_SET | M64F_SDRAM_MAGIC_PLL)
/*#घोषणा ATI_CHIP_264GTDVD  ?*/
#घोषणा ATI_CHIP_264LTG    (ATI_MODERN_SET | M64F_SDRAM_MAGIC_PLL)

#घोषणा ATI_CHIP_264GT2C   (ATI_MODERN_SET | M64F_SDRAM_MAGIC_PLL | M64F_HW_TRIPLE)
#घोषणा ATI_CHIP_264GTPRO  (ATI_MODERN_SET | M64F_SDRAM_MAGIC_PLL | M64F_HW_TRIPLE | M64F_FIFO_32 | M64F_RESET_3D)
#घोषणा ATI_CHIP_264LTPRO  (ATI_MODERN_SET | M64F_HW_TRIPLE | M64F_FIFO_32 | M64F_RESET_3D)

#घोषणा ATI_CHIP_264XL     (ATI_MODERN_SET | M64F_HW_TRIPLE | M64F_FIFO_32 | M64F_RESET_3D | M64F_XL_DLL | M64F_MFB_FORCE_4 | M64F_XL_MEM)
#घोषणा ATI_CHIP_MOBILITY  (ATI_MODERN_SET | M64F_HW_TRIPLE | M64F_FIFO_32 | M64F_RESET_3D | M64F_XL_DLL | M64F_MFB_FORCE_4 | M64F_XL_MEM | M64F_MOBIL_BUS)

अटल काष्ठा अणु
	u16 pci_id;
	स्थिर अक्षर *name;
	पूर्णांक pll, mclk, xclk, ecp_max;
	u32 features;
पूर्ण aty_chips[] = अणु
#अगर_घोषित CONFIG_FB_ATY_GX
	/* Mach64 GX */
	अणु PCI_CHIP_MACH64GX, "ATI888GX00 (Mach64 GX)", 135, 50, 50, 0, ATI_CHIP_88800GX पूर्ण,
	अणु PCI_CHIP_MACH64CX, "ATI888CX00 (Mach64 CX)", 135, 50, 50, 0, ATI_CHIP_88800CX पूर्ण,
#पूर्ण_अगर /* CONFIG_FB_ATY_GX */

#अगर_घोषित CONFIG_FB_ATY_CT
	अणु PCI_CHIP_MACH64CT, "ATI264CT (Mach64 CT)", 135, 60, 60, 0, ATI_CHIP_264CT पूर्ण,
	अणु PCI_CHIP_MACH64ET, "ATI264ET (Mach64 ET)", 135, 60, 60, 0, ATI_CHIP_264ET पूर्ण,

	/* FIXME what is this chip? */
	अणु PCI_CHIP_MACH64LT, "ATI264LT (Mach64 LT)", 135, 63, 63, 0, ATI_CHIP_264LT पूर्ण,

	अणु PCI_CHIP_MACH64VT, "ATI264VT (Mach64 VT)", 170, 67, 67, 80, ATI_CHIP_264VT पूर्ण,
	अणु PCI_CHIP_MACH64GT, "3D RAGE (Mach64 GT)", 135, 63, 63, 80, ATI_CHIP_264GT पूर्ण,

	अणु PCI_CHIP_MACH64VU, "ATI264VT3 (Mach64 VU)", 200, 67, 67, 80, ATI_CHIP_264VT3 पूर्ण,
	अणु PCI_CHIP_MACH64GU, "3D RAGE II+ (Mach64 GU)", 200, 67, 67, 100, ATI_CHIP_264GTB पूर्ण,

	अणु PCI_CHIP_MACH64LG, "3D RAGE LT (Mach64 LG)", 230, 63, 63, 100, ATI_CHIP_264LTG | M64F_LT_LCD_REGS | M64F_G3_PB_1024x768 पूर्ण,

	अणु PCI_CHIP_MACH64VV, "ATI264VT4 (Mach64 VV)", 230, 83, 83, 100, ATI_CHIP_264VT4 पूर्ण,

	अणु PCI_CHIP_MACH64GV, "3D RAGE IIC (Mach64 GV, PCI)", 230, 83, 83, 100, ATI_CHIP_264GT2C पूर्ण,
	अणु PCI_CHIP_MACH64GW, "3D RAGE IIC (Mach64 GW, AGP)", 230, 83, 83, 100, ATI_CHIP_264GT2C पूर्ण,
	अणु PCI_CHIP_MACH64GY, "3D RAGE IIC (Mach64 GY, PCI)", 230, 83, 83, 100, ATI_CHIP_264GT2C पूर्ण,
	अणु PCI_CHIP_MACH64GZ, "3D RAGE IIC (Mach64 GZ, AGP)", 230, 83, 83, 100, ATI_CHIP_264GT2C पूर्ण,

	अणु PCI_CHIP_MACH64GB, "3D RAGE PRO (Mach64 GB, BGA, AGP)", 230, 100, 100, 125, ATI_CHIP_264GTPRO पूर्ण,
	अणु PCI_CHIP_MACH64GD, "3D RAGE PRO (Mach64 GD, BGA, AGP 1x)", 230, 100, 100, 125, ATI_CHIP_264GTPRO पूर्ण,
	अणु PCI_CHIP_MACH64GI, "3D RAGE PRO (Mach64 GI, BGA, PCI)", 230, 100, 100, 125, ATI_CHIP_264GTPRO | M64F_MAGIC_VRAM_SIZE पूर्ण,
	अणु PCI_CHIP_MACH64GP, "3D RAGE PRO (Mach64 GP, PQFP, PCI)", 230, 100, 100, 125, ATI_CHIP_264GTPRO पूर्ण,
	अणु PCI_CHIP_MACH64GQ, "3D RAGE PRO (Mach64 GQ, PQFP, PCI, limited 3D)", 230, 100, 100, 125, ATI_CHIP_264GTPRO पूर्ण,

	अणु PCI_CHIP_MACH64LB, "3D RAGE LT PRO (Mach64 LB, AGP)", 236, 75, 100, 135, ATI_CHIP_264LTPRO पूर्ण,
	अणु PCI_CHIP_MACH64LD, "3D RAGE LT PRO (Mach64 LD, AGP)", 230, 100, 100, 135, ATI_CHIP_264LTPRO पूर्ण,
	अणु PCI_CHIP_MACH64LI, "3D RAGE LT PRO (Mach64 LI, PCI)", 230, 100, 100, 135, ATI_CHIP_264LTPRO | M64F_G3_PB_1_1 | M64F_G3_PB_1024x768 पूर्ण,
	अणु PCI_CHIP_MACH64LP, "3D RAGE LT PRO (Mach64 LP, PCI)", 230, 100, 100, 135, ATI_CHIP_264LTPRO | M64F_G3_PB_1024x768 पूर्ण,
	अणु PCI_CHIP_MACH64LQ, "3D RAGE LT PRO (Mach64 LQ, PCI)", 230, 100, 100, 135, ATI_CHIP_264LTPRO पूर्ण,

	अणु PCI_CHIP_MACH64GM, "3D RAGE XL (Mach64 GM, AGP 2x)", 230, 83, 63, 135, ATI_CHIP_264XL पूर्ण,
	अणु PCI_CHIP_MACH64GN, "3D RAGE XC (Mach64 GN, AGP 2x)", 230, 83, 63, 135, ATI_CHIP_264XL पूर्ण,
	अणु PCI_CHIP_MACH64GO, "3D RAGE XL (Mach64 GO, PCI-66)", 230, 83, 63, 135, ATI_CHIP_264XL पूर्ण,
	अणु PCI_CHIP_MACH64GL, "3D RAGE XC (Mach64 GL, PCI-66)", 230, 83, 63, 135, ATI_CHIP_264XL पूर्ण,
	अणु PCI_CHIP_MACH64GR, "3D RAGE XL (Mach64 GR, PCI-33)", 230, 83, 63, 135, ATI_CHIP_264XL | M64F_SDRAM_MAGIC_PLL पूर्ण,
	अणु PCI_CHIP_MACH64GS, "3D RAGE XC (Mach64 GS, PCI-33)", 230, 83, 63, 135, ATI_CHIP_264XL पूर्ण,

	अणु PCI_CHIP_MACH64LM, "3D RAGE Mobility P/M (Mach64 LM, AGP 2x)", 230, 83, 125, 135, ATI_CHIP_MOBILITY पूर्ण,
	अणु PCI_CHIP_MACH64LN, "3D RAGE Mobility L (Mach64 LN, AGP 2x)", 230, 83, 125, 135, ATI_CHIP_MOBILITY पूर्ण,
	अणु PCI_CHIP_MACH64LR, "3D RAGE Mobility P/M (Mach64 LR, PCI)", 230, 83, 125, 135, ATI_CHIP_MOBILITY पूर्ण,
	अणु PCI_CHIP_MACH64LS, "3D RAGE Mobility L (Mach64 LS, PCI)", 230, 83, 125, 135, ATI_CHIP_MOBILITY पूर्ण,
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */
पूर्ण;

/*
 * Last page of 8 MB (4 MB on ISA) aperture is MMIO,
 * unless the auxiliary रेजिस्टर aperture is used.
 */
अटल व्योम aty_fudge_framebuffer_len(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	अगर (!par->aux_start &&
	    (info->fix.smem_len == 0x800000 ||
	     (par->bus_type == ISA && info->fix.smem_len == 0x400000)))
		info->fix.smem_len -= GUI_RESERVE;
पूर्ण

अटल पूर्णांक correct_chipset(काष्ठा atyfb_par *par)
अणु
	u8 rev;
	u16 type;
	u32 chip_id;
	स्थिर अक्षर *name;
	पूर्णांक i;

	क्रम (i = (पूर्णांक)ARRAY_SIZE(aty_chips) - 1; i >= 0; i--)
		अगर (par->pci_id == aty_chips[i].pci_id)
			अवरोध;

	अगर (i < 0)
		वापस -ENODEV;

	name = aty_chips[i].name;
	par->pll_limits.pll_max = aty_chips[i].pll;
	par->pll_limits.mclk = aty_chips[i].mclk;
	par->pll_limits.xclk = aty_chips[i].xclk;
	par->pll_limits.ecp_max = aty_chips[i].ecp_max;
	par->features = aty_chips[i].features;

	chip_id = aty_ld_le32(CNFG_CHIP_ID, par);
	type = chip_id & CFG_CHIP_TYPE;
	rev = (chip_id & CFG_CHIP_REV) >> 24;

	चयन (par->pci_id) अणु
#अगर_घोषित CONFIG_FB_ATY_GX
	हाल PCI_CHIP_MACH64GX:
		अगर (type != 0x00d7)
			वापस -ENODEV;
		अवरोध;
	हाल PCI_CHIP_MACH64CX:
		अगर (type != 0x0057)
			वापस -ENODEV;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_ATY_CT
	हाल PCI_CHIP_MACH64VT:
		चयन (rev & 0x07) अणु
		हाल 0x00:
			चयन (rev & 0xc0) अणु
			हाल 0x00:
				name = "ATI264VT (A3) (Mach64 VT)";
				par->pll_limits.pll_max = 170;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT;
				अवरोध;
			हाल 0x40:
				name = "ATI264VT2 (A4) (Mach64 VT)";
				par->pll_limits.pll_max = 200;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT | M64F_MAGIC_POSTDIV;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x01:
			name = "ATI264VT3 (B1) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VTB;
			अवरोध;
		हाल 0x02:
			name = "ATI264VT3 (B2) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VT3;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_CHIP_MACH64GT:
		चयन (rev & 0x07) अणु
		हाल 0x01:
			name = "3D RAGE II (Mach64 GT)";
			par->pll_limits.pll_max = 170;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264GTB;
			अवरोध;
		हाल 0x02:
			name = "3D RAGE II+ (Mach64 GT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 100;
			par->features = ATI_CHIP_264GTB;
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	PRINTKI("%s [0x%04x rev 0x%02x]\n", name, type, rev);
	वापस 0;
पूर्ण

अटल अक्षर ram_dram[] __maybe_unused = "DRAM";
अटल अक्षर ram_resv[] __maybe_unused = "RESV";
#अगर_घोषित CONFIG_FB_ATY_GX
अटल अक्षर ram_vram[] = "VRAM";
#पूर्ण_अगर /* CONFIG_FB_ATY_GX */
#अगर_घोषित CONFIG_FB_ATY_CT
अटल अक्षर ram_eकरो[] = "EDO";
अटल अक्षर ram_sdram[] = "SDRAM (1:1)";
अटल अक्षर ram_sgram[] = "SGRAM (1:1)";
अटल अक्षर ram_sdram32[] = "SDRAM (2:1) (32-bit)";
अटल अक्षर ram_wram[] = "WRAM";
अटल अक्षर ram_off[] = "OFF";
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */


#अगर_घोषित CONFIG_FB_ATY_GX
अटल अक्षर *aty_gx_ram[8] = अणु
	ram_dram, ram_vram, ram_vram, ram_dram,
	ram_dram, ram_vram, ram_vram, ram_resv
पूर्ण;
#पूर्ण_अगर /* CONFIG_FB_ATY_GX */

#अगर_घोषित CONFIG_FB_ATY_CT
अटल अक्षर *aty_ct_ram[8] = अणु
	ram_off, ram_dram, ram_eकरो, ram_eकरो,
	ram_sdram, ram_sgram, ram_wram, ram_resv
पूर्ण;
अटल अक्षर *aty_xl_ram[8] = अणु
	ram_off, ram_dram, ram_eकरो, ram_eकरो,
	ram_sdram, ram_sgram, ram_sdram32, ram_resv
पूर्ण;
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */

अटल u32 atyfb_get_pixघड़ी(काष्ठा fb_var_screeninfo *var,
			      काष्ठा atyfb_par *par)
अणु
	u32 pixघड़ी = var->pixघड़ी;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	u32 lcd_on_off;
	par->pll.ct.xres = 0;
	अगर (par->lcd_table != 0) अणु
		lcd_on_off = aty_ld_lcd(LCD_GEN_CNTL, par);
		अगर (lcd_on_off & LCD_ON) अणु
			par->pll.ct.xres = var->xres;
			pixघड़ी = par->lcd_pixघड़ी;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस pixघड़ी;
पूर्ण

#अगर defined(CONFIG_PPC)

/*
 * Apple monitor sense
 */

अटल पूर्णांक पढ़ो_aty_sense(स्थिर काष्ठा atyfb_par *par)
अणु
	पूर्णांक sense, i;

	aty_st_le32(GP_IO, 0x31003100, par); /* drive outमाला_दो high */
	__delay(200);
	aty_st_le32(GP_IO, 0, par); /* turn off outमाला_दो */
	__delay(2000);
	i = aty_ld_le32(GP_IO, par); /* get primary sense value */
	sense = ((i & 0x3000) >> 3) | (i & 0x100);

	/* drive each sense line low in turn and collect the other 2 */
	aty_st_le32(GP_IO, 0x20000000, par); /* drive A low */
	__delay(2000);
	i = aty_ld_le32(GP_IO, par);
	sense |= ((i & 0x1000) >> 7) | ((i & 0x100) >> 4);
	aty_st_le32(GP_IO, 0x20002000, par); /* drive A high again */
	__delay(200);

	aty_st_le32(GP_IO, 0x10000000, par); /* drive B low */
	__delay(2000);
	i = aty_ld_le32(GP_IO, par);
	sense |= ((i & 0x2000) >> 10) | ((i & 0x100) >> 6);
	aty_st_le32(GP_IO, 0x10001000, par); /* drive B high again */
	__delay(200);

	aty_st_le32(GP_IO, 0x01000000, par); /* drive C low */
	__delay(2000);
	sense |= (aty_ld_le32(GP_IO, par) & 0x3000) >> 12;
	aty_st_le32(GP_IO, 0, par); /* turn off outमाला_दो */
	वापस sense;
पूर्ण

#पूर्ण_अगर /* defined(CONFIG_PPC) */

/* ------------------------------------------------------------------------- */

/*
 * CRTC programming
 */

अटल व्योम aty_get_crtc(स्थिर काष्ठा atyfb_par *par, काष्ठा crtc *crtc)
अणु
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		अगर (!M64_HAS(LT_LCD_REGS)) अणु
			crtc->lcd_index = aty_ld_le32(LCD_INDEX, par);
			aty_st_le32(LCD_INDEX, crtc->lcd_index, par);
		पूर्ण
		crtc->lcd_config_panel = aty_ld_lcd(CNFG_PANEL, par);
		crtc->lcd_gen_cntl = aty_ld_lcd(LCD_GEN_CNTL, par);


		/* चयन to non shaकरोw रेजिस्टरs */
		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl &
			   ~(CRTC_RW_SELECT | SHADOW_EN | SHADOW_RW_EN), par);

		/* save stretching */
		crtc->horz_stretching = aty_ld_lcd(HORZ_STRETCHING, par);
		crtc->vert_stretching = aty_ld_lcd(VERT_STRETCHING, par);
		अगर (!M64_HAS(LT_LCD_REGS))
			crtc->ext_vert_stretch = aty_ld_lcd(EXT_VERT_STRETCH, par);
	पूर्ण
#पूर्ण_अगर
	crtc->h_tot_disp = aty_ld_le32(CRTC_H_TOTAL_DISP, par);
	crtc->h_sync_strt_wid = aty_ld_le32(CRTC_H_SYNC_STRT_WID, par);
	crtc->v_tot_disp = aty_ld_le32(CRTC_V_TOTAL_DISP, par);
	crtc->v_sync_strt_wid = aty_ld_le32(CRTC_V_SYNC_STRT_WID, par);
	crtc->vline_crnt_vline = aty_ld_le32(CRTC_VLINE_CRNT_VLINE, par);
	crtc->off_pitch = aty_ld_le32(CRTC_OFF_PITCH, par);
	crtc->gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		/* चयन to shaकरोw रेजिस्टरs */
		aty_st_lcd(LCD_GEN_CNTL, (crtc->lcd_gen_cntl & ~CRTC_RW_SELECT) |
			   SHADOW_EN | SHADOW_RW_EN, par);

		crtc->shaकरोw_h_tot_disp = aty_ld_le32(CRTC_H_TOTAL_DISP, par);
		crtc->shaकरोw_h_sync_strt_wid = aty_ld_le32(CRTC_H_SYNC_STRT_WID, par);
		crtc->shaकरोw_v_tot_disp = aty_ld_le32(CRTC_V_TOTAL_DISP, par);
		crtc->shaकरोw_v_sync_strt_wid = aty_ld_le32(CRTC_V_SYNC_STRT_WID, par);

		aty_st_le32(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */
पूर्ण

अटल व्योम aty_set_crtc(स्थिर काष्ठा atyfb_par *par, स्थिर काष्ठा crtc *crtc)
अणु
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		/* stop CRTC */
		aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl &
			    ~(CRTC_EXT_DISP_EN | CRTC_EN), par);

		/* update non-shaकरोw रेजिस्टरs first */
		aty_st_lcd(CNFG_PANEL, crtc->lcd_config_panel, par);
		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl &
			   ~(CRTC_RW_SELECT | SHADOW_EN | SHADOW_RW_EN), par);

		/* temporarily disable stretching */
		aty_st_lcd(HORZ_STRETCHING, crtc->horz_stretching &
			   ~(HORZ_STRETCH_MODE | HORZ_STRETCH_EN), par);
		aty_st_lcd(VERT_STRETCHING, crtc->vert_stretching &
			   ~(VERT_STRETCH_RATIO1 | VERT_STRETCH_RATIO2 |
			     VERT_STRETCH_USE0 | VERT_STRETCH_EN), par);
	पूर्ण
#पूर्ण_अगर
	/* turn off CRT */
	aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl & ~CRTC_EN, par);

	DPRINTK("setting up CRTC\n");
	DPRINTK("set primary CRT to %ix%i %c%c composite %c\n",
		((((crtc->h_tot_disp >> 16) & 0xff) + 1) << 3),
		(((crtc->v_tot_disp >> 16) & 0x7ff) + 1),
		(crtc->h_sync_strt_wid & 0x200000) ? 'N' : 'P',
		(crtc->v_sync_strt_wid & 0x200000) ? 'N' : 'P',
		(crtc->gen_cntl & CRTC_CSYNC_EN) ? 'P' : 'N');

	DPRINTK("CRTC_H_TOTAL_DISP: %x\n", crtc->h_tot_disp);
	DPRINTK("CRTC_H_SYNC_STRT_WID: %x\n", crtc->h_sync_strt_wid);
	DPRINTK("CRTC_V_TOTAL_DISP: %x\n", crtc->v_tot_disp);
	DPRINTK("CRTC_V_SYNC_STRT_WID: %x\n", crtc->v_sync_strt_wid);
	DPRINTK("CRTC_OFF_PITCH: %x\n", crtc->off_pitch);
	DPRINTK("CRTC_VLINE_CRNT_VLINE: %x\n", crtc->vline_crnt_vline);
	DPRINTK("CRTC_GEN_CNTL: %x\n", crtc->gen_cntl);

	aty_st_le32(CRTC_H_TOTAL_DISP, crtc->h_tot_disp, par);
	aty_st_le32(CRTC_H_SYNC_STRT_WID, crtc->h_sync_strt_wid, par);
	aty_st_le32(CRTC_V_TOTAL_DISP, crtc->v_tot_disp, par);
	aty_st_le32(CRTC_V_SYNC_STRT_WID, crtc->v_sync_strt_wid, par);
	aty_st_le32(CRTC_OFF_PITCH, crtc->off_pitch, par);
	aty_st_le32(CRTC_VLINE_CRNT_VLINE, crtc->vline_crnt_vline, par);

	aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl, par);
#अगर 0
	FIXME
	अगर (par->accel_flags & FB_ACCELF_TEXT)
		aty_init_engine(par, info);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	/* after setting the CRTC रेजिस्टरs we should set the LCD रेजिस्टरs. */
	अगर (par->lcd_table != 0) अणु
		/* चयन to shaकरोw रेजिस्टरs */
		aty_st_lcd(LCD_GEN_CNTL, (crtc->lcd_gen_cntl & ~CRTC_RW_SELECT) |
			   SHADOW_EN | SHADOW_RW_EN, par);

		DPRINTK("set shadow CRT to %ix%i %c%c\n",
			((((crtc->shaकरोw_h_tot_disp >> 16) & 0xff) + 1) << 3),
			(((crtc->shaकरोw_v_tot_disp >> 16) & 0x7ff) + 1),
			(crtc->shaकरोw_h_sync_strt_wid & 0x200000) ? 'N' : 'P',
			(crtc->shaकरोw_v_sync_strt_wid & 0x200000) ? 'N' : 'P');

		DPRINTK("SHADOW CRTC_H_TOTAL_DISP: %x\n",
			crtc->shaकरोw_h_tot_disp);
		DPRINTK("SHADOW CRTC_H_SYNC_STRT_WID: %x\n",
			crtc->shaकरोw_h_sync_strt_wid);
		DPRINTK("SHADOW CRTC_V_TOTAL_DISP: %x\n",
			crtc->shaकरोw_v_tot_disp);
		DPRINTK("SHADOW CRTC_V_SYNC_STRT_WID: %x\n",
			crtc->shaकरोw_v_sync_strt_wid);

		aty_st_le32(CRTC_H_TOTAL_DISP, crtc->shaकरोw_h_tot_disp, par);
		aty_st_le32(CRTC_H_SYNC_STRT_WID, crtc->shaकरोw_h_sync_strt_wid, par);
		aty_st_le32(CRTC_V_TOTAL_DISP, crtc->shaकरोw_v_tot_disp, par);
		aty_st_le32(CRTC_V_SYNC_STRT_WID, crtc->shaकरोw_v_sync_strt_wid, par);

		/* restore CRTC selection & shaकरोw state and enable stretching */
		DPRINTK("LCD_GEN_CNTL: %x\n", crtc->lcd_gen_cntl);
		DPRINTK("HORZ_STRETCHING: %x\n", crtc->horz_stretching);
		DPRINTK("VERT_STRETCHING: %x\n", crtc->vert_stretching);
		अगर (!M64_HAS(LT_LCD_REGS))
			DPRINTK("EXT_VERT_STRETCH: %x\n", crtc->ext_vert_stretch);

		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);
		aty_st_lcd(HORZ_STRETCHING, crtc->horz_stretching, par);
		aty_st_lcd(VERT_STRETCHING, crtc->vert_stretching, par);
		अगर (!M64_HAS(LT_LCD_REGS)) अणु
			aty_st_lcd(EXT_VERT_STRETCH, crtc->ext_vert_stretch, par);
			aty_ld_le32(LCD_INDEX, par);
			aty_st_le32(LCD_INDEX, crtc->lcd_index, par);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */
पूर्ण

अटल u32 calc_line_length(काष्ठा atyfb_par *par, u32 vxres, u32 bpp)
अणु
	u32 line_length = vxres * bpp / 8;

	अगर (par->ram_type == SGRAM ||
	    (!M64_HAS(XL_MEM) && par->ram_type == WRAM))
		line_length = (line_length + 63) & ~63;

	वापस line_length;
पूर्ण

अटल पूर्णांक aty_var_to_crtc(स्थिर काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_var_screeninfo *var,
			   काष्ठा crtc *crtc)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 xres, yres, vxres, vyres, xoffset, yoffset, bpp;
	u32 sync, vmode;
	u32 h_total, h_disp, h_sync_strt, h_sync_end, h_sync_dly, h_sync_wid, h_sync_pol;
	u32 v_total, v_disp, v_sync_strt, v_sync_end, v_sync_wid, v_sync_pol, c_sync;
	u32 pix_width, dp_pix_width, dp_chain_mask;
	u32 line_length;

	/* input */
	xres = (var->xres + 7) & ~7;
	yres = var->yres;
	vxres = (var->xres_भव + 7) & ~7;
	vyres = var->yres_भव;
	xoffset = (var->xoffset + 7) & ~7;
	yoffset = var->yoffset;
	bpp = var->bits_per_pixel;
	अगर (bpp == 16)
		bpp = (var->green.length == 5) ? 15 : 16;
	sync = var->sync;
	vmode = var->vmode;

	/* convert (and round up) and validate */
	अगर (vxres < xres + xoffset)
		vxres = xres + xoffset;
	h_disp = xres;

	अगर (vyres < yres + yoffset)
		vyres = yres + yoffset;
	v_disp = yres;

	अगर (bpp <= 8) अणु
		bpp = 8;
		pix_width = CRTC_PIX_WIDTH_8BPP;
		dp_pix_width = HOST_8BPP | SRC_8BPP | DST_8BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_8BPP;
	पूर्ण अन्यथा अगर (bpp <= 15) अणु
		bpp = 16;
		pix_width = CRTC_PIX_WIDTH_15BPP;
		dp_pix_width = HOST_15BPP | SRC_15BPP | DST_15BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_15BPP;
	पूर्ण अन्यथा अगर (bpp <= 16) अणु
		bpp = 16;
		pix_width = CRTC_PIX_WIDTH_16BPP;
		dp_pix_width = HOST_16BPP | SRC_16BPP | DST_16BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_16BPP;
	पूर्ण अन्यथा अगर (bpp <= 24 && M64_HAS(INTEGRATED)) अणु
		bpp = 24;
		pix_width = CRTC_PIX_WIDTH_24BPP;
		dp_pix_width = HOST_8BPP | SRC_8BPP | DST_8BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_24BPP;
	पूर्ण अन्यथा अगर (bpp <= 32) अणु
		bpp = 32;
		pix_width = CRTC_PIX_WIDTH_32BPP;
		dp_pix_width = HOST_32BPP | SRC_32BPP | DST_32BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_32BPP;
	पूर्ण अन्यथा
		FAIL("invalid bpp");

	line_length = calc_line_length(par, vxres, bpp);

	अगर (vyres * line_length > info->fix.smem_len)
		FAIL("not enough video RAM");

	h_sync_pol = sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	v_sync_pol = sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;

	अगर ((xres > 1920) || (yres > 1200)) अणु
		FAIL("MACH64 chips are designed for max 1920x1200\n"
		     "select another resolution.");
	पूर्ण
	h_sync_strt = h_disp + var->right_margin;
	h_sync_end = h_sync_strt + var->hsync_len;
	h_sync_dly  = var->right_margin & 7;
	h_total = h_sync_end + h_sync_dly + var->left_margin;

	v_sync_strt = v_disp + var->lower_margin;
	v_sync_end = v_sync_strt + var->vsync_len;
	v_total = v_sync_end + var->upper_margin;

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		अगर (!M64_HAS(LT_LCD_REGS)) अणु
			u32 lcd_index = aty_ld_le32(LCD_INDEX, par);
			crtc->lcd_index = lcd_index &
				~(LCD_INDEX_MASK | LCD_DISPLAY_DIS |
				  LCD_SRC_SEL | CRTC2_DISPLAY_DIS);
			aty_st_le32(LCD_INDEX, lcd_index, par);
		पूर्ण

		अगर (!M64_HAS(MOBIL_BUS))
			crtc->lcd_index |= CRTC2_DISPLAY_DIS;

		crtc->lcd_config_panel = aty_ld_lcd(CNFG_PANEL, par) | 0x4000;
		crtc->lcd_gen_cntl = aty_ld_lcd(LCD_GEN_CNTL, par) & ~CRTC_RW_SELECT;

		crtc->lcd_gen_cntl &=
			~(HORZ_DIVBY2_EN | DIS_HOR_CRT_DIVBY2 | TVCLK_PM_EN |
			/*VCLK_DAC_PM_EN | USE_SHADOWED_VEND |*/
			USE_SHADOWED_ROWCUR | SHADOW_EN | SHADOW_RW_EN);
		crtc->lcd_gen_cntl |= DONT_SHADOW_VPAR | LOCK_8DOT;

		अगर ((crtc->lcd_gen_cntl & LCD_ON) &&
		    ((xres > par->lcd_width) || (yres > par->lcd_height))) अणु
			/*
			 * We cannot display the mode on the LCD. If the CRT is
			 * enabled we can turn off the LCD.
			 * If the CRT is off, it isn't a good idea to चयन it
			 * on; we करोn't know if one is connected. So it's better
			 * to fail then.
			 */
			अगर (crtc->lcd_gen_cntl & CRT_ON) अणु
				अगर (!(var->activate & FB_ACTIVATE_TEST))
					PRINTKI("Disable LCD panel, because video mode does not fit.\n");
				crtc->lcd_gen_cntl &= ~LCD_ON;
				/*aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);*/
			पूर्ण अन्यथा अणु
				अगर (!(var->activate & FB_ACTIVATE_TEST))
					PRINTKE("Video mode exceeds size of LCD panel.\nConnect this computer to a conventional monitor if you really need this mode.\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((par->lcd_table != 0) && (crtc->lcd_gen_cntl & LCD_ON)) अणु
		पूर्णांक VScan = 1;
		/* bpp -> bytespp, 1,4 -> 0; 8 -> 2; 15,16 -> 1; 24 -> 6; 32 -> 5
		स्थिर u8 DFP_h_sync_dly_LT[] = अणु 0, 2, 1, 6, 5 पूर्ण;
		स्थिर u8 ADD_to_strt_wid_and_dly_LT_DAC[] = अणु 0, 5, 6, 9, 9, 12, 12 पूर्ण;  */

		vmode &= ~(FB_VMODE_DOUBLE | FB_VMODE_INTERLACED);

		/*
		 * This is horror! When we simulate, say 640x480 on an 800x600
		 * LCD monitor, the CRTC should be programmed 800x600 values क्रम
		 * the non visible part, but 640x480 क्रम the visible part.
		 * This code has been tested on a laptop with it's 1400x1050 LCD
		 * monitor and a conventional monitor both चयनed on.
		 * Tested modes: 1280x1024, 1152x864, 1024x768, 800x600,
		 * works with little glitches also with DOUBLESCAN modes
		 */
		अगर (yres < par->lcd_height) अणु
			VScan = par->lcd_height / yres;
			अगर (VScan > 1) अणु
				VScan = 2;
				vmode |= FB_VMODE_DOUBLE;
			पूर्ण
		पूर्ण

		h_sync_strt = h_disp + par->lcd_right_margin;
		h_sync_end = h_sync_strt + par->lcd_hsync_len;
		h_sync_dly = /*DFP_h_sync_dly[ ( bpp + 1 ) / 3 ]; */par->lcd_hsync_dly;
		h_total = h_disp + par->lcd_hblank_len;

		v_sync_strt = v_disp + par->lcd_lower_margin / VScan;
		v_sync_end = v_sync_strt + par->lcd_vsync_len / VScan;
		v_total = v_disp + par->lcd_vblank_len / VScan;
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */

	h_disp = (h_disp >> 3) - 1;
	h_sync_strt = (h_sync_strt >> 3) - 1;
	h_sync_end = (h_sync_end >> 3) - 1;
	h_total = (h_total >> 3) - 1;
	h_sync_wid = h_sync_end - h_sync_strt;

	FAIL_MAX("h_disp too large", h_disp, 0xff);
	FAIL_MAX("h_sync_strt too large", h_sync_strt, 0x1ff);
	/*FAIL_MAX("h_sync_wid too large", h_sync_wid, 0x1f);*/
	अगर (h_sync_wid > 0x1f)
		h_sync_wid = 0x1f;
	FAIL_MAX("h_total too large", h_total, 0x1ff);

	अगर (vmode & FB_VMODE_DOUBLE) अणु
		v_disp <<= 1;
		v_sync_strt <<= 1;
		v_sync_end <<= 1;
		v_total <<= 1;
	पूर्ण

	v_disp--;
	v_sync_strt--;
	v_sync_end--;
	v_total--;
	v_sync_wid = v_sync_end - v_sync_strt;

	FAIL_MAX("v_disp too large", v_disp, 0x7ff);
	FAIL_MAX("v_sync_stsrt too large", v_sync_strt, 0x7ff);
	/*FAIL_MAX("v_sync_wid too large", v_sync_wid, 0x1f);*/
	अगर (v_sync_wid > 0x1f)
		v_sync_wid = 0x1f;
	FAIL_MAX("v_total too large", v_total, 0x7ff);

	c_sync = sync & FB_SYNC_COMP_HIGH_ACT ? CRTC_CSYNC_EN : 0;

	/* output */
	crtc->vxres = vxres;
	crtc->vyres = vyres;
	crtc->xoffset = xoffset;
	crtc->yoffset = yoffset;
	crtc->bpp = bpp;
	crtc->off_pitch =
		((yoffset * line_length + xoffset * bpp / 8) / 8) |
		((line_length / bpp) << 22);
	crtc->vline_crnt_vline = 0;

	crtc->h_tot_disp = h_total | (h_disp << 16);
	crtc->h_sync_strt_wid = (h_sync_strt & 0xff) | (h_sync_dly << 8) |
		((h_sync_strt & 0x100) << 4) | (h_sync_wid << 16) |
		(h_sync_pol << 21);
	crtc->v_tot_disp = v_total | (v_disp << 16);
	crtc->v_sync_strt_wid = v_sync_strt | (v_sync_wid << 16) |
		(v_sync_pol << 21);

	/* crtc->gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par) & CRTC_PRESERVED_MASK; */
	crtc->gen_cntl = CRTC_EXT_DISP_EN | CRTC_EN | pix_width | c_sync;
	crtc->gen_cntl |= CRTC_VGA_LINEAR;

	/* Enable द्विगुनscan mode अगर requested */
	अगर (vmode & FB_VMODE_DOUBLE)
		crtc->gen_cntl |= CRTC_DBL_SCAN_EN;
	/* Enable पूर्णांकerlaced mode अगर requested */
	अगर (vmode & FB_VMODE_INTERLACED)
		crtc->gen_cntl |= CRTC_INTERLACE_EN;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		u32 vdisplay = yres;
		अगर (vmode & FB_VMODE_DOUBLE)
			vdisplay <<= 1;
		crtc->gen_cntl &= ~(CRTC2_EN | CRTC2_PIX_WIDTH);
		crtc->lcd_gen_cntl &= ~(HORZ_DIVBY2_EN | DIS_HOR_CRT_DIVBY2 |
					/*TVCLK_PM_EN | VCLK_DAC_PM_EN |*/
					USE_SHADOWED_VEND |
					USE_SHADOWED_ROWCUR |
					SHADOW_EN | SHADOW_RW_EN);
		crtc->lcd_gen_cntl |= DONT_SHADOW_VPAR/* | LOCK_8DOT*/;

		/* MOBILITY M1 tested, FIXME: LT */
		crtc->horz_stretching = aty_ld_lcd(HORZ_STRETCHING, par);
		अगर (!M64_HAS(LT_LCD_REGS))
			crtc->ext_vert_stretch = aty_ld_lcd(EXT_VERT_STRETCH, par) &
				~(AUTO_VERT_RATIO | VERT_STRETCH_MODE | VERT_STRETCH_RATIO3);

		crtc->horz_stretching &= ~(HORZ_STRETCH_RATIO |
					   HORZ_STRETCH_LOOP | AUTO_HORZ_RATIO |
					   HORZ_STRETCH_MODE | HORZ_STRETCH_EN);
		अगर (xres < par->lcd_width && crtc->lcd_gen_cntl & LCD_ON) अणु
			करो अणु
				/*
				 * The horizontal blender misbehaves when
				 * HDisplay is less than a certain threshold
				 * (440 क्रम a 1024-wide panel).  It करोesn't
				 * stretch such modes enough.  Use pixel
				 * replication instead of blending to stretch
				 * modes that can be made to exactly fit the
				 * panel width.  The unकरोcumented "NoLCDBlend"
				 * option allows the pixel-replicated mode to
				 * be slightly wider or narrower than the
				 * panel width.  It also causes a mode that is
				 * exactly half as wide as the panel to be
				 * pixel-replicated, rather than blended.
				 */
				पूर्णांक HDisplay  = xres & ~7;
				पूर्णांक nStretch  = par->lcd_width / HDisplay;
				पूर्णांक Reमुख्यder = par->lcd_width % HDisplay;

				अगर ((!Reमुख्यder && ((nStretch > 2))) ||
				    (((HDisplay * 16) / par->lcd_width) < 7)) अणु
					अटल स्थिर अक्षर StretchLoops[] = अणु 10, 12, 13, 15, 16 पूर्ण;
					पूर्णांक horz_stretch_loop = -1, BestReमुख्यder;
					पूर्णांक Numerator = HDisplay, Denominator = par->lcd_width;
					पूर्णांक Index = 5;
					ATIReduceRatio(&Numerator, &Denominator);

					BestReमुख्यder = (Numerator * 16) / Denominator;
					जबतक (--Index >= 0) अणु
						Reमुख्यder = ((Denominator - Numerator) * StretchLoops[Index]) %
							Denominator;
						अगर (Reमुख्यder < BestReमुख्यder) अणु
							horz_stretch_loop = Index;
							अगर (!(BestReमुख्यder = Reमुख्यder))
								अवरोध;
						पूर्ण
					पूर्ण

					अगर ((horz_stretch_loop >= 0) && !BestReमुख्यder) अणु
						पूर्णांक horz_stretch_ratio = 0, Accumulator = 0;
						पूर्णांक reuse_previous = 1;

						Index = StretchLoops[horz_stretch_loop];

						जबतक (--Index >= 0) अणु
							अगर (Accumulator > 0)
								horz_stretch_ratio |= reuse_previous;
							अन्यथा
								Accumulator += Denominator;
							Accumulator -= Numerator;
							reuse_previous <<= 1;
						पूर्ण

						crtc->horz_stretching |= (HORZ_STRETCH_EN |
							((horz_stretch_loop & HORZ_STRETCH_LOOP) << 16) |
							(horz_stretch_ratio & HORZ_STRETCH_RATIO));
						अवरोध;      /* Out of the करो अणु ... पूर्ण जबतक (0) */
					पूर्ण
				पूर्ण

				crtc->horz_stretching |= (HORZ_STRETCH_MODE | HORZ_STRETCH_EN |
					(((HDisplay * (HORZ_STRETCH_BLEND + 1)) / par->lcd_width) & HORZ_STRETCH_BLEND));
			पूर्ण जबतक (0);
		पूर्ण

		अगर (vdisplay < par->lcd_height && crtc->lcd_gen_cntl & LCD_ON) अणु
			crtc->vert_stretching = (VERT_STRETCH_USE0 | VERT_STRETCH_EN |
				(((vdisplay * (VERT_STRETCH_RATIO0 + 1)) / par->lcd_height) & VERT_STRETCH_RATIO0));

			अगर (!M64_HAS(LT_LCD_REGS) &&
			    xres <= (M64_HAS(MOBIL_BUS) ? 1024 : 800))
				crtc->ext_vert_stretch |= VERT_STRETCH_MODE;
		पूर्ण अन्यथा अणु
			/*
			 * Don't use vertical blending अगर the mode is too wide
			 * or not vertically stretched.
			 */
			crtc->vert_stretching = 0;
		पूर्ण
		/* copy to shaकरोw crtc */
		crtc->shaकरोw_h_tot_disp = crtc->h_tot_disp;
		crtc->shaकरोw_h_sync_strt_wid = crtc->h_sync_strt_wid;
		crtc->shaकरोw_v_tot_disp = crtc->v_tot_disp;
		crtc->shaकरोw_v_sync_strt_wid = crtc->v_sync_strt_wid;
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */

	अगर (M64_HAS(MAGIC_FIFO)) अणु
		/* FIXME: display FIFO low watermark values */
		crtc->gen_cntl |= (aty_ld_le32(CRTC_GEN_CNTL, par) & CRTC_FIFO_LWM);
	पूर्ण
	crtc->dp_pix_width = dp_pix_width;
	crtc->dp_chain_mask = dp_chain_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक aty_crtc_to_var(स्थिर काष्ठा crtc *crtc,
			   काष्ठा fb_var_screeninfo *var)
अणु
	u32 xres, yres, bpp, left, right, upper, lower, hslen, vslen, sync;
	u32 h_total, h_disp, h_sync_strt, h_sync_dly, h_sync_wid, h_sync_pol;
	u32 v_total, v_disp, v_sync_strt, v_sync_wid, v_sync_pol, c_sync;
	u32 pix_width;
	u32 द्विगुन_scan, पूर्णांकerlace;

	/* input */
	h_total = crtc->h_tot_disp & 0x1ff;
	h_disp = (crtc->h_tot_disp >> 16) & 0xff;
	h_sync_strt = (crtc->h_sync_strt_wid & 0xff) | ((crtc->h_sync_strt_wid >> 4) & 0x100);
	h_sync_dly = (crtc->h_sync_strt_wid >> 8) & 0x7;
	h_sync_wid = (crtc->h_sync_strt_wid >> 16) & 0x1f;
	h_sync_pol = (crtc->h_sync_strt_wid >> 21) & 0x1;
	v_total = crtc->v_tot_disp & 0x7ff;
	v_disp = (crtc->v_tot_disp >> 16) & 0x7ff;
	v_sync_strt = crtc->v_sync_strt_wid & 0x7ff;
	v_sync_wid = (crtc->v_sync_strt_wid >> 16) & 0x1f;
	v_sync_pol = (crtc->v_sync_strt_wid >> 21) & 0x1;
	c_sync = crtc->gen_cntl & CRTC_CSYNC_EN ? 1 : 0;
	pix_width = crtc->gen_cntl & CRTC_PIX_WIDTH_MASK;
	द्विगुन_scan = crtc->gen_cntl & CRTC_DBL_SCAN_EN;
	पूर्णांकerlace = crtc->gen_cntl & CRTC_INTERLACE_EN;

	/* convert */
	xres = (h_disp + 1) * 8;
	yres = v_disp + 1;
	left = (h_total - h_sync_strt - h_sync_wid) * 8 - h_sync_dly;
	right = (h_sync_strt - h_disp) * 8 + h_sync_dly;
	hslen = h_sync_wid * 8;
	upper = v_total - v_sync_strt - v_sync_wid;
	lower = v_sync_strt - v_disp;
	vslen = v_sync_wid;
	sync = (h_sync_pol ? 0 : FB_SYNC_HOR_HIGH_ACT) |
		(v_sync_pol ? 0 : FB_SYNC_VERT_HIGH_ACT) |
		(c_sync ? FB_SYNC_COMP_HIGH_ACT : 0);

	चयन (pix_width) अणु
	हाल CRTC_PIX_WIDTH_8BPP:
		bpp = 8;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल CRTC_PIX_WIDTH_15BPP:	/* RGB 555 */
		bpp = 16;
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल CRTC_PIX_WIDTH_16BPP:	/* RGB 565 */
		bpp = 16;
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल CRTC_PIX_WIDTH_24BPP:	/* RGB 888 */
		bpp = 24;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल CRTC_PIX_WIDTH_32BPP:	/* ARGB 8888 */
		bpp = 32;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	शेष:
		PRINTKE("Invalid pixel width\n");
		वापस -EINVAL;
	पूर्ण

	/* output */
	var->xres = xres;
	var->yres = yres;
	var->xres_भव = crtc->vxres;
	var->yres_भव = crtc->vyres;
	var->bits_per_pixel = bpp;
	var->left_margin = left;
	var->right_margin = right;
	var->upper_margin = upper;
	var->lower_margin = lower;
	var->hsync_len = hslen;
	var->vsync_len = vslen;
	var->sync = sync;
	var->vmode = FB_VMODE_NONINTERLACED;
	/*
	 * In द्विगुन scan mode, the vertical parameters are द्विगुनd,
	 * so we need to halve them to get the right values.
	 * In पूर्णांकerlaced mode the values are alपढ़ोy correct,
	 * so no correction is necessary.
	 */
	अगर (पूर्णांकerlace)
		var->vmode = FB_VMODE_INTERLACED;

	अगर (द्विगुन_scan) अणु
		var->vmode = FB_VMODE_DOUBLE;
		var->yres >>= 1;
		var->upper_margin >>= 1;
		var->lower_margin >>= 1;
		var->vsync_len >>= 1;
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक atyfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	u32 पंचांगp, pixघड़ी;
	पूर्णांक err;
#अगर_घोषित DEBUG
	काष्ठा fb_var_screeninfo debug;
	u32 pixघड़ी_in_ps;
#पूर्ण_अगर
	अगर (par->asleep)
		वापस 0;

	err = aty_var_to_crtc(info, var, &par->crtc);
	अगर (err)
		वापस err;

	pixघड़ी = atyfb_get_pixघड़ी(var, par);

	अगर (pixघड़ी == 0) अणु
		PRINTKE("Invalid pixclock\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		err = par->pll_ops->var_to_pll(info, pixघड़ी,
					       var->bits_per_pixel, &par->pll);
		अगर (err)
			वापस err;
	पूर्ण

	par->accel_flags = var->accel_flags; /* hack */

	अगर (var->accel_flags) अणु
		atyfb_ops.fb_sync = atyfb_sync;
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
	पूर्ण अन्यथा अणु
		atyfb_ops.fb_sync = शून्य;
		info->flags |= FBINFO_HWACCEL_DISABLED;
	पूर्ण

	अगर (par->blitter_may_be_busy)
		रुको_क्रम_idle(par);

	aty_set_crtc(par, &par->crtc);
	par->dac_ops->set_dac(info, &par->pll,
			      var->bits_per_pixel, par->accel_flags);
	par->pll_ops->set_pll(info, &par->pll);

#अगर_घोषित DEBUG
	अगर (par->pll_ops && par->pll_ops->pll_to_var)
		pixघड़ी_in_ps = par->pll_ops->pll_to_var(info, &par->pll);
	अन्यथा
		pixघड़ी_in_ps = 0;

	अगर (0 == pixघड़ी_in_ps) अणु
		PRINTKE("ALERT ops->pll_to_var get 0\n");
		pixघड़ी_in_ps = pixघड़ी;
	पूर्ण

	स_रखो(&debug, 0, माप(debug));
	अगर (!aty_crtc_to_var(&par->crtc, &debug)) अणु
		u32 hSync, vRefresh;
		u32 h_disp, h_sync_strt, h_sync_end, h_total;
		u32 v_disp, v_sync_strt, v_sync_end, v_total;

		h_disp = debug.xres;
		h_sync_strt = h_disp + debug.right_margin;
		h_sync_end = h_sync_strt + debug.hsync_len;
		h_total = h_sync_end + debug.left_margin;
		v_disp = debug.yres;
		v_sync_strt = v_disp + debug.lower_margin;
		v_sync_end = v_sync_strt + debug.vsync_len;
		v_total = v_sync_end + debug.upper_margin;

		hSync = 1000000000 / (pixघड़ी_in_ps * h_total);
		vRefresh = (hSync * 1000) / v_total;
		अगर (par->crtc.gen_cntl & CRTC_INTERLACE_EN)
			vRefresh *= 2;
		अगर (par->crtc.gen_cntl & CRTC_DBL_SCAN_EN)
			vRefresh /= 2;

		DPRINTK("atyfb_set_par\n");
		DPRINTK(" Set Visible Mode to %ix%i-%i\n",
			var->xres, var->yres, var->bits_per_pixel);
		DPRINTK(" Virtual resolution %ix%i, "
			"pixclock_in_ps %i (calculated %i)\n",
			var->xres_भव, var->yres_भव,
			pixघड़ी, pixघड़ी_in_ps);
		DPRINTK(" Dot clock:           %i MHz\n",
			1000000 / pixघड़ी_in_ps);
		DPRINTK(" Horizontal sync:     %i kHz\n", hSync);
		DPRINTK(" Vertical refresh:    %i Hz\n", vRefresh);
		DPRINTK(" x  style: %i.%03i %i %i %i %i   %i %i %i %i\n",
			1000000 / pixघड़ी_in_ps, 1000000 % pixघड़ी_in_ps,
			h_disp, h_sync_strt, h_sync_end, h_total,
			v_disp, v_sync_strt, v_sync_end, v_total);
		DPRINTK(" fb style: %i  %i %i %i %i %i %i %i %i\n",
			pixघड़ी_in_ps,
			debug.left_margin, h_disp, debug.right_margin, debug.hsync_len,
			debug.upper_margin, v_disp, debug.lower_margin, debug.vsync_len);
	पूर्ण
#पूर्ण_अगर /* DEBUG */

	अगर (!M64_HAS(INTEGRATED)) अणु
		/* Don't क्रमget MEM_CNTL */
		पंचांगp = aty_ld_le32(MEM_CNTL, par) & 0xf0ffffff;
		चयन (var->bits_per_pixel) अणु
		हाल 8:
			पंचांगp |= 0x02000000;
			अवरोध;
		हाल 16:
			पंचांगp |= 0x03000000;
			अवरोध;
		हाल 32:
			पंचांगp |= 0x06000000;
			अवरोध;
		पूर्ण
		aty_st_le32(MEM_CNTL, पंचांगp, par);
	पूर्ण अन्यथा अणु
		पंचांगp = aty_ld_le32(MEM_CNTL, par) & 0xf00fffff;
		अगर (!M64_HAS(MAGIC_POSTDIV))
			पंचांगp |= par->mem_refresh_rate << 20;
		चयन (var->bits_per_pixel) अणु
		हाल 8:
		हाल 24:
			पंचांगp |= 0x00000000;
			अवरोध;
		हाल 16:
			पंचांगp |= 0x04000000;
			अवरोध;
		हाल 32:
			पंचांगp |= 0x08000000;
			अवरोध;
		पूर्ण
		अगर (M64_HAS(CT_BUS)) अणु
			aty_st_le32(DAC_CNTL, 0x87010184, par);
			aty_st_le32(BUS_CNTL, 0x680000f9, par);
		पूर्ण अन्यथा अगर (M64_HAS(VT_BUS)) अणु
			aty_st_le32(DAC_CNTL, 0x87010184, par);
			aty_st_le32(BUS_CNTL, 0x680000f9, par);
		पूर्ण अन्यथा अगर (M64_HAS(MOBIL_BUS)) अणु
			aty_st_le32(DAC_CNTL, 0x80010102, par);
			aty_st_le32(BUS_CNTL, 0x7b33a040 | (par->aux_start ? BUS_APER_REG_DIS : 0), par);
		पूर्ण अन्यथा अणु
			/* GT */
			aty_st_le32(DAC_CNTL, 0x86010102, par);
			aty_st_le32(BUS_CNTL, 0x7b23a040 | (par->aux_start ? BUS_APER_REG_DIS : 0), par);
			aty_st_le32(EXT_MEM_CNTL, aty_ld_le32(EXT_MEM_CNTL, par) | 0x5000001, par);
		पूर्ण
		aty_st_le32(MEM_CNTL, पंचांगp, par);
	पूर्ण
	aty_st_8(DAC_MASK, 0xff, par);

	info->fix.line_length = calc_line_length(par, var->xres_भव,
						 var->bits_per_pixel);

	info->fix.visual = var->bits_per_pixel <= 8 ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;

	/* Initialize the graphics engine */
	अगर (par->accel_flags & FB_ACCELF_TEXT)
		aty_init_engine(par, info);

#अगर_घोषित CONFIG_BOOTX_TEXT
	btext_update_display(info->fix.smem_start,
		(((par->crtc.h_tot_disp >> 16) & 0xff) + 1) * 8,
		((par->crtc.v_tot_disp >> 16) & 0x7ff) + 1,
		var->bits_per_pixel,
		par->crtc.vxres * var->bits_per_pixel / 8);
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */
#अगर_घोषित DEBUG
अणु
	/* dump non shaकरोw CRTC, pll, LCD रेजिस्टरs */
	पूर्णांक i; u32 base;

	/* CRTC रेजिस्टरs */
	base = 0x2000;
	prपूर्णांकk("debug atyfb: Mach64 non-shadow register values:");
	क्रम (i = 0; i < 256; i = i+4) अणु
		अगर (i % 16 == 0) अणु
			pr_cont("\n");
			prपूर्णांकk("debug atyfb: 0x%04X: ", base + i);
		पूर्ण
		pr_cont(" %08X", aty_ld_le32(i, par));
	पूर्ण
	pr_cont("\n\n");

#अगर_घोषित CONFIG_FB_ATY_CT
	/* PLL रेजिस्टरs */
	base = 0x00;
	prपूर्णांकk("debug atyfb: Mach64 PLL register values:");
	क्रम (i = 0; i < 64; i++) अणु
		अगर (i % 16 == 0) अणु
			pr_cont("\n");
			prपूर्णांकk("debug atyfb: 0x%02X: ", base + i);
		पूर्ण
		अगर (i % 4 == 0)
			pr_cont(" ");
		pr_cont("%02X", aty_ld_pll_ct(i, par));
	पूर्ण
	pr_cont("\n\n");
#पूर्ण_अगर	/* CONFIG_FB_ATY_CT */

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		/* LCD रेजिस्टरs */
		base = 0x00;
		prपूर्णांकk("debug atyfb: LCD register values:");
		अगर (M64_HAS(LT_LCD_REGS)) अणु
			क्रम (i = 0; i <= POWER_MANAGEMENT; i++) अणु
				अगर (i == EXT_VERT_STRETCH)
					जारी;
				pr_cont("\ndebug atyfb: 0x%04X: ",
				       lt_lcd_regs[i]);
				pr_cont(" %08X", aty_ld_lcd(i, par));
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 64; i++) अणु
				अगर (i % 4 == 0)
					pr_cont("\ndebug atyfb: 0x%02X: ",
					       base + i);
				pr_cont(" %08X", aty_ld_lcd(i, par));
			पूर्ण
		पूर्ण
		pr_cont("\n\n");
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */
पूर्ण
#पूर्ण_अगर /* DEBUG */
	वापस 0;
पूर्ण

अटल पूर्णांक atyfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	पूर्णांक err;
	काष्ठा crtc crtc;
	जोड़ aty_pll pll;
	u32 pixघड़ी;

	स_नकल(&pll, &par->pll, माप(pll));

	err = aty_var_to_crtc(info, var, &crtc);
	अगर (err)
		वापस err;

	pixघड़ी = atyfb_get_pixघड़ी(var, par);

	अगर (pixघड़ी == 0) अणु
		अगर (!(var->activate & FB_ACTIVATE_TEST))
			PRINTKE("Invalid pixclock\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		err = par->pll_ops->var_to_pll(info, pixघड़ी,
					       var->bits_per_pixel, &pll);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (var->accel_flags & FB_ACCELF_TEXT)
		info->var.accel_flags = FB_ACCELF_TEXT;
	अन्यथा
		info->var.accel_flags = 0;

	aty_crtc_to_var(&crtc, var);
	var->pixघड़ी = par->pll_ops->pll_to_var(info, &pll);
	वापस 0;
पूर्ण

अटल व्योम set_off_pitch(काष्ठा atyfb_par *par, स्थिर काष्ठा fb_info *info)
अणु
	u32 xoffset = info->var.xoffset;
	u32 yoffset = info->var.yoffset;
	u32 line_length = info->fix.line_length;
	u32 bpp = info->var.bits_per_pixel;

	par->crtc.off_pitch =
		((yoffset * line_length + xoffset * bpp / 8) / 8) |
		((line_length / bpp) << 22);
पूर्ण


/*
 * Open/Release the frame buffer device
 */

अटल पूर्णांक atyfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	अगर (user) अणु
		par->खोलो++;
#अगर_घोषित __sparc__
		par->mmaped = 0;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t aty_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा atyfb_par *par = dev_id;
	पूर्णांक handled = 0;
	u32 पूर्णांक_cntl;

	spin_lock(&par->पूर्णांक_lock);

	पूर्णांक_cntl = aty_ld_le32(CRTC_INT_CNTL, par);

	अगर (पूर्णांक_cntl & CRTC_VBLANK_INT) अणु
		/* clear पूर्णांकerrupt */
		aty_st_le32(CRTC_INT_CNTL, (पूर्णांक_cntl & CRTC_INT_EN_MASK) |
			    CRTC_VBLANK_INT_AK, par);
		par->vblank.count++;
		अगर (par->vblank.pan_display) अणु
			par->vblank.pan_display = 0;
			aty_st_le32(CRTC_OFF_PITCH, par->crtc.off_pitch, par);
		पूर्ण
		wake_up_पूर्णांकerruptible(&par->vblank.रुको);
		handled = 1;
	पूर्ण

	spin_unlock(&par->पूर्णांक_lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक aty_enable_irq(काष्ठा atyfb_par *par, पूर्णांक reenable)
अणु
	u32 पूर्णांक_cntl;

	अगर (!test_and_set_bit(0, &par->irq_flags)) अणु
		अगर (request_irq(par->irq, aty_irq, IRQF_SHARED, "atyfb", par)) अणु
			clear_bit(0, &par->irq_flags);
			वापस -EINVAL;
		पूर्ण
		spin_lock_irq(&par->पूर्णांक_lock);
		पूर्णांक_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		/* clear पूर्णांकerrupt */
		aty_st_le32(CRTC_INT_CNTL, पूर्णांक_cntl | CRTC_VBLANK_INT_AK, par);
		/* enable पूर्णांकerrupt */
		aty_st_le32(CRTC_INT_CNTL, पूर्णांक_cntl | CRTC_VBLANK_INT_EN, par);
		spin_unlock_irq(&par->पूर्णांक_lock);
	पूर्ण अन्यथा अगर (reenable) अणु
		spin_lock_irq(&par->पूर्णांक_lock);
		पूर्णांक_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		अगर (!(पूर्णांक_cntl & CRTC_VBLANK_INT_EN)) अणु
			prपूर्णांकk("atyfb: someone disabled IRQ [%08x]\n",
			       पूर्णांक_cntl);
			/* re-enable पूर्णांकerrupt */
			aty_st_le32(CRTC_INT_CNTL, पूर्णांक_cntl |
				    CRTC_VBLANK_INT_EN, par);
		पूर्ण
		spin_unlock_irq(&par->पूर्णांक_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aty_disable_irq(काष्ठा atyfb_par *par)
अणु
	u32 पूर्णांक_cntl;

	अगर (test_and_clear_bit(0, &par->irq_flags)) अणु
		अगर (par->vblank.pan_display) अणु
			par->vblank.pan_display = 0;
			aty_st_le32(CRTC_OFF_PITCH, par->crtc.off_pitch, par);
		पूर्ण
		spin_lock_irq(&par->पूर्णांक_lock);
		पूर्णांक_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		/* disable पूर्णांकerrupt */
		aty_st_le32(CRTC_INT_CNTL, पूर्णांक_cntl & ~CRTC_VBLANK_INT_EN, par);
		spin_unlock_irq(&par->पूर्णांक_lock);
		मुक्त_irq(par->irq, par);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atyfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
#अगर_घोषित __sparc__
	पूर्णांक was_mmaped;
#पूर्ण_अगर

	अगर (!user)
		वापस 0;

	par->खोलो--;
	mdelay(1);
	रुको_क्रम_idle(par);

	अगर (par->खोलो)
		वापस 0;

#अगर_घोषित __sparc__
	was_mmaped = par->mmaped;

	par->mmaped = 0;

	अगर (was_mmaped) अणु
		काष्ठा fb_var_screeninfo var;

		/*
		 * Now reset the शेष display config, we have
		 * no idea what the program(s) which mmap'd the
		 * chip did to the configuration, nor whether it
		 * restored it correctly.
		 */
		var = शेष_var;
		अगर (noaccel)
			var.accel_flags &= ~FB_ACCELF_TEXT;
		अन्यथा
			var.accel_flags |= FB_ACCELF_TEXT;
		अगर (var.yres == var.yres_भव) अणु
			u32 videoram = (info->fix.smem_len - (PAGE_SIZE << 2));
			var.yres_भव =
				((videoram * 8) / var.bits_per_pixel) /
				var.xres_भव;
			अगर (var.yres_भव < var.yres)
				var.yres_भव = var.yres;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	aty_disable_irq(par);

	वापस 0;
पूर्ण

/*
 * Pan or Wrap the Display
 *
 * This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
 */

अटल पूर्णांक atyfb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 xres, yres, xoffset, yoffset;

	xres = (((par->crtc.h_tot_disp >> 16) & 0xff) + 1) * 8;
	yres = ((par->crtc.v_tot_disp >> 16) & 0x7ff) + 1;
	अगर (par->crtc.gen_cntl & CRTC_DBL_SCAN_EN)
		yres >>= 1;
	xoffset = (var->xoffset + 7) & ~7;
	yoffset = var->yoffset;
	अगर (xoffset + xres > par->crtc.vxres ||
	    yoffset + yres > par->crtc.vyres)
		वापस -EINVAL;
	info->var.xoffset = xoffset;
	info->var.yoffset = yoffset;
	अगर (par->asleep)
		वापस 0;

	set_off_pitch(par, info);
	अगर ((var->activate & FB_ACTIVATE_VBL) && !aty_enable_irq(par, 0)) अणु
		par->vblank.pan_display = 1;
	पूर्ण अन्यथा अणु
		par->vblank.pan_display = 0;
		aty_st_le32(CRTC_OFF_PITCH, par->crtc.off_pitch, par);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aty_रुकोक्रमvblank(काष्ठा atyfb_par *par, u32 crtc)
अणु
	काष्ठा aty_पूर्णांकerrupt *vbl;
	अचिन्हित पूर्णांक count;
	पूर्णांक ret;

	चयन (crtc) अणु
	हाल 0:
		vbl = &par->vblank;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = aty_enable_irq(par, 0);
	अगर (ret)
		वापस ret;

	count = vbl->count;
	ret = रुको_event_पूर्णांकerruptible_समयout(vbl->रुको,
					       count != vbl->count, HZ/10);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0) अणु
		aty_enable_irq(par, 1);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण


#अगर_घोषित DEBUG
#घोषणा ATYIO_CLKR		0x41545900	/* ATY\00 */
#घोषणा ATYIO_CLKW		0x41545901	/* ATY\01 */

काष्ठा atyclk अणु
	u32 ref_clk_per;
	u8 pll_ref_भाग;
	u8 mclk_fb_भाग;
	u8 mclk_post_भाग;	/* 1,2,3,4,8 */
	u8 mclk_fb_mult;	/* 2 or 4 */
	u8 xclk_post_भाग;	/* 1,2,3,4,8 */
	u8 vclk_fb_भाग;
	u8 vclk_post_भाग;	/* 1,2,3,4,6,8,12 */
	u32 dsp_xclks_per_row;	/* 0-16383 */
	u32 dsp_loop_latency;	/* 0-15 */
	u32 dsp_precision;	/* 0-7 */
	u32 dsp_on;		/* 0-2047 */
	u32 dsp_off;		/* 0-2047 */
पूर्ण;

#घोषणा ATYIO_FEATR		0x41545902	/* ATY\02 */
#घोषणा ATYIO_FEATW		0x41545903	/* ATY\03 */
#पूर्ण_अगर

अटल पूर्णांक atyfb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
#अगर_घोषित __sparc__
	काष्ठा fbtype fbtyp;
#पूर्ण_अगर

	चयन (cmd) अणु
#अगर_घोषित __sparc__
	हाल FBIOGTYPE:
		fbtyp.fb_type = FBTYPE_PCI_GENERIC;
		fbtyp.fb_width = par->crtc.vxres;
		fbtyp.fb_height = par->crtc.vyres;
		fbtyp.fb_depth = info->var.bits_per_pixel;
		fbtyp.fb_cmsize = info->cmap.len;
		fbtyp.fb_size = info->fix.smem_len;
		अगर (copy_to_user((काष्ठा fbtype __user *) arg, &fbtyp,
				 माप(fbtyp)))
			वापस -EFAULT;
		अवरोध;
#पूर्ण_अगर /* __sparc__ */

	हाल FBIO_WAITFORVSYNC:
		अणु
			u32 crtc;

			अगर (get_user(crtc, (__u32 __user *) arg))
				वापस -EFAULT;

			वापस aty_रुकोक्रमvblank(par, crtc);
		पूर्ण

#अगर defined(DEBUG) && defined(CONFIG_FB_ATY_CT)
	हाल ATYIO_CLKR:
		अगर (M64_HAS(INTEGRATED)) अणु
			काष्ठा atyclk clk = अणु 0 पूर्ण;
			जोड़ aty_pll *pll = &par->pll;
			u32 dsp_config = pll->ct.dsp_config;
			u32 dsp_on_off = pll->ct.dsp_on_off;
			clk.ref_clk_per = par->ref_clk_per;
			clk.pll_ref_भाग = pll->ct.pll_ref_भाग;
			clk.mclk_fb_भाग = pll->ct.mclk_fb_भाग;
			clk.mclk_post_भाग = pll->ct.mclk_post_भाग_real;
			clk.mclk_fb_mult = pll->ct.mclk_fb_mult;
			clk.xclk_post_भाग = pll->ct.xclk_post_भाग_real;
			clk.vclk_fb_भाग = pll->ct.vclk_fb_भाग;
			clk.vclk_post_भाग = pll->ct.vclk_post_भाग_real;
			clk.dsp_xclks_per_row = dsp_config & 0x3fff;
			clk.dsp_loop_latency = (dsp_config >> 16) & 0xf;
			clk.dsp_precision = (dsp_config >> 20) & 7;
			clk.dsp_off = dsp_on_off & 0x7ff;
			clk.dsp_on = (dsp_on_off >> 16) & 0x7ff;
			अगर (copy_to_user((काष्ठा atyclk __user *) arg, &clk,
					 माप(clk)))
				वापस -EFAULT;
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल ATYIO_CLKW:
		अगर (M64_HAS(INTEGRATED)) अणु
			काष्ठा atyclk clk;
			जोड़ aty_pll *pll = &par->pll;
			अगर (copy_from_user(&clk, (काष्ठा atyclk __user *) arg,
					   माप(clk)))
				वापस -EFAULT;
			par->ref_clk_per = clk.ref_clk_per;
			pll->ct.pll_ref_भाग = clk.pll_ref_भाग;
			pll->ct.mclk_fb_भाग = clk.mclk_fb_भाग;
			pll->ct.mclk_post_भाग_real = clk.mclk_post_भाग;
			pll->ct.mclk_fb_mult = clk.mclk_fb_mult;
			pll->ct.xclk_post_भाग_real = clk.xclk_post_भाग;
			pll->ct.vclk_fb_भाग = clk.vclk_fb_भाग;
			pll->ct.vclk_post_भाग_real = clk.vclk_post_भाग;
			pll->ct.dsp_config = (clk.dsp_xclks_per_row & 0x3fff) |
				((clk.dsp_loop_latency & 0xf) << 16) |
				((clk.dsp_precision & 7) << 20);
			pll->ct.dsp_on_off = (clk.dsp_off & 0x7ff) |
				((clk.dsp_on & 0x7ff) << 16);
			/*aty_calc_pll_ct(info, &pll->ct);*/
			aty_set_pll_ct(info, pll);
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल ATYIO_FEATR:
		अगर (get_user(par->features, (u32 __user *) arg))
			वापस -EFAULT;
		अवरोध;
	हाल ATYIO_FEATW:
		अगर (put_user(par->features, (u32 __user *) arg))
			वापस -EFAULT;
		अवरोध;
#पूर्ण_अगर /* DEBUG && CONFIG_FB_ATY_CT */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक atyfb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	अगर (par->blitter_may_be_busy)
		रुको_क्रम_idle(par);
	वापस 0;
पूर्ण

#अगर_घोषित __sparc__
अटल पूर्णांक atyfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	अचिन्हित पूर्णांक size, page, map_size = 0;
	अचिन्हित दीर्घ map_offset = 0;
	अचिन्हित दीर्घ off;
	पूर्णांक i;

	अगर (!par->mmap_map)
		वापस -ENXIO;

	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;

	off = vma->vm_pgoff << PAGE_SHIFT;
	size = vma->vm_end - vma->vm_start;

	/* VM_IO | VM_DONTEXPAND | VM_DONTDUMP are set by remap_pfn_range() */

	अगर (((vma->vm_pgoff == 0) && (size == info->fix.smem_len)) ||
	    ((off == info->fix.smem_len) && (size == PAGE_SIZE)))
		off += 0x8000000000000000UL;

	vma->vm_pgoff = off >> PAGE_SHIFT;	/* propagate off changes */

	/* Each page, see which map applies */
	क्रम (page = 0; page < size;) अणु
		map_size = 0;
		क्रम (i = 0; par->mmap_map[i].size; i++) अणु
			अचिन्हित दीर्घ start = par->mmap_map[i].voff;
			अचिन्हित दीर्घ end = start + par->mmap_map[i].size;
			अचिन्हित दीर्घ offset = off + page;

			अगर (start > offset)
				जारी;
			अगर (offset >= end)
				जारी;

			map_size = par->mmap_map[i].size - (offset - start);
			map_offset = par->mmap_map[i].poff + (offset - start);
			अवरोध;
		पूर्ण
		अगर (!map_size) अणु
			page += PAGE_SIZE;
			जारी;
		पूर्ण
		अगर (page + map_size > size)
			map_size = size - page;

		pgprot_val(vma->vm_page_prot) &= ~(par->mmap_map[i].prot_mask);
		pgprot_val(vma->vm_page_prot) |= par->mmap_map[i].prot_flag;

		अगर (remap_pfn_range(vma, vma->vm_start + page,
			map_offset >> PAGE_SHIFT, map_size, vma->vm_page_prot))
			वापस -EAGAIN;

		page += map_size;
	पूर्ण

	अगर (!map_size)
		वापस -EINVAL;

	अगर (!par->mmaped)
		par->mmaped = 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* __sparc__ */



#अगर defined(CONFIG_PCI)

#अगर_घोषित CONFIG_PPC_PMAC
/* Power management routines. Those are used क्रम PowerBook sleep.
 */
अटल पूर्णांक aty_घातer_mgmt(पूर्णांक sleep, काष्ठा atyfb_par *par)
अणु
	u32 pm;
	पूर्णांक समयout;

	pm = aty_ld_lcd(POWER_MANAGEMENT, par);
	pm = (pm & ~PWR_MGT_MODE_MASK) | PWR_MGT_MODE_REG;
	aty_st_lcd(POWER_MANAGEMENT, pm, par);
	pm = aty_ld_lcd(POWER_MANAGEMENT, par);

	समयout = 2000;
	अगर (sleep) अणु
		/* Sleep */
		pm &= ~PWR_MGT_ON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		udelay(10);
		pm &= ~(PWR_BLON | AUTO_PWR_UP);
		pm |= SUSPEND_NOW;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		udelay(10);
		pm |= PWR_MGT_ON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		करो अणु
			pm = aty_ld_lcd(POWER_MANAGEMENT, par);
			mdelay(1);
			अगर ((--समयout) == 0)
				अवरोध;
		पूर्ण जबतक ((pm & PWR_MGT_STATUS_MASK) != PWR_MGT_STATUS_SUSPEND);
	पूर्ण अन्यथा अणु
		/* Wakeup */
		pm &= ~PWR_MGT_ON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		udelay(10);
		pm &= ~SUSPEND_NOW;
		pm |= (PWR_BLON | AUTO_PWR_UP);
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		udelay(10);
		pm |= PWR_MGT_ON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
		करो अणु
			pm = aty_ld_lcd(POWER_MANAGEMENT, par);
			mdelay(1);
			अगर ((--समयout) == 0)
				अवरोध;
		पूर्ण जबतक ((pm & PWR_MGT_STATUS_MASK) != 0);
	पूर्ण
	mdelay(500);

	वापस समयout ? 0 : -EIO;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

अटल पूर्णांक atyfb_pci_suspend_late(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	अगर (state.event == pdev->dev.घातer.घातer_state.event)
		वापस 0;

	console_lock();

	fb_set_suspend(info, 1);

	/* Idle & reset engine */
	रुको_क्रम_idle(par);
	aty_reset_engine(par);

	/* Blank display and LCD */
	atyfb_blank(FB_BLANK_POWERDOWN, info);

	par->asleep = 1;
	par->lock_blank = 1;

	/*
	 * Because we may change PCI D state ourselves, we need to
	 * first save the config space content so the core can
	 * restore it properly on resume.
	 */

#अगर_घोषित CONFIG_PPC_PMAC
	/* Set chip to "suspend" mode */
	अगर (machine_is(घातermac) && aty_घातer_mgmt(1, par)) अणु
		par->asleep = 0;
		par->lock_blank = 0;
		atyfb_blank(FB_BLANK_UNBLANK, info);
		fb_set_suspend(info, 0);
		console_unlock();
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर

	console_unlock();

	pdev->dev.घातer.घातer_state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused atyfb_pci_suspend(काष्ठा device *dev)
अणु
	वापस atyfb_pci_suspend_late(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक __maybe_unused atyfb_pci_hibernate(काष्ठा device *dev)
अणु
	वापस atyfb_pci_suspend_late(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक __maybe_unused atyfb_pci_मुक्तze(काष्ठा device *dev)
अणु
	वापस atyfb_pci_suspend_late(dev, PMSG_FREEZE);
पूर्ण

अटल व्योम aty_resume_chip(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = info->par;

	aty_st_le32(MEM_CNTL, par->mem_cntl, par);

	अगर (par->pll_ops->resume_pll)
		par->pll_ops->resume_pll(info, &par->pll);

	अगर (par->aux_start)
		aty_st_le32(BUS_CNTL,
			aty_ld_le32(BUS_CNTL, par) | BUS_APER_REG_DIS, par);
पूर्ण

अटल पूर्णांक __maybe_unused atyfb_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_ON)
		वापस 0;

	console_lock();

	/*
	 * PCI state will have been restored by the core, so
	 * we should be in D0 now with our config space fully
	 * restored
	 */

#अगर_घोषित CONFIG_PPC_PMAC
	अगर (machine_is(घातermac) &&
	    pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND)
		aty_घातer_mgmt(0, par);
#पूर्ण_अगर

	aty_resume_chip(info);

	par->asleep = 0;

	/* Restore display */
	atyfb_set_par(info);

	/* Refresh */
	fb_set_suspend(info, 0);

	/* Unblank */
	par->lock_blank = 0;
	atyfb_blank(FB_BLANK_UNBLANK, info);

	console_unlock();

	pdev->dev.घातer.घातer_state = PMSG_ON;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops atyfb_pci_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= atyfb_pci_suspend,
	.resume		= atyfb_pci_resume,
	.मुक्तze		= atyfb_pci_मुक्तze,
	.thaw		= atyfb_pci_resume,
	.घातeroff	= atyfb_pci_hibernate,
	.restore	= atyfb_pci_resume,
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
पूर्ण;

#पूर्ण_अगर /*  defined(CONFIG_PCI) */

/* Backlight */
#अगर_घोषित CONFIG_FB_ATY_BACKLIGHT
#घोषणा MAX_LEVEL 0xFF

अटल पूर्णांक aty_bl_get_level_brightness(काष्ठा atyfb_par *par, पूर्णांक level)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	पूर्णांक atylevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we पढ़ो a single value */
	atylevel = info->bl_curve[level] * FB_BACKLIGHT_MAX / MAX_LEVEL;

	अगर (atylevel < 0)
		atylevel = 0;
	अन्यथा अगर (atylevel > MAX_LEVEL)
		atylevel = MAX_LEVEL;

	वापस atylevel;
पूर्ण

अटल पूर्णांक aty_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा atyfb_par *par = bl_get_data(bd);
	अचिन्हित पूर्णांक reg = aty_ld_lcd(LCD_MISC_CNTL, par);
	पूर्णांक level;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;
	अन्यथा
		level = bd->props.brightness;

	reg |= (BLMOD_EN | BIASMOD_EN);
	अगर (level > 0) अणु
		reg &= ~BIAS_MOD_LEVEL_MASK;
		reg |= (aty_bl_get_level_brightness(par, level) << BIAS_MOD_LEVEL_SHIFT);
	पूर्ण अन्यथा अणु
		reg &= ~BIAS_MOD_LEVEL_MASK;
		reg |= (aty_bl_get_level_brightness(par, 0) << BIAS_MOD_LEVEL_SHIFT);
	पूर्ण
	aty_st_lcd(LCD_MISC_CNTL, reg, par);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops aty_bl_data = अणु
	.update_status	= aty_bl_update_status,
पूर्ण;

अटल व्योम aty_bl_init(काष्ठा atyfb_par *par)
अणु
	काष्ठा backlight_properties props;
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	काष्ठा backlight_device *bd;
	अक्षर name[12];

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!pmac_has_backlight_type("ati"))
		वापस;
#पूर्ण_अगर

	snम_लिखो(name, माप(name), "atybl%d", info->node);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, info->dev, par, &aty_bl_data,
				       &props);
	अगर (IS_ERR(bd)) अणु
		info->bl_dev = शून्य;
		prपूर्णांकk(KERN_WARNING "aty: Backlight registration failed\n");
		जाओ error;
	पूर्ण

	info->bl_dev = bd;
	fb_bl_शेष_curve(info, 0,
			    0x3F * FB_BACKLIGHT_MAX / MAX_LEVEL,
			    0xFF * FB_BACKLIGHT_MAX / MAX_LEVEL);

	bd->props.brightness = bd->props.max_brightness;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk("aty: Backlight initialized (%s)\n", name);

	वापस;

error:
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल व्योम aty_bl_निकास(काष्ठा backlight_device *bd)
अणु
	backlight_device_unरेजिस्टर(bd);
	prपूर्णांकk("aty: Backlight unloaded\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#पूर्ण_अगर /* CONFIG_FB_ATY_BACKLIGHT */

अटल व्योम aty_calc_mem_refresh(काष्ठा atyfb_par *par, पूर्णांक xclk)
अणु
	अटल स्थिर पूर्णांक ragepro_tbl[] = अणु
		44, 50, 55, 66, 75, 80, 100
	पूर्ण;
	अटल स्थिर पूर्णांक ragexl_tbl[] = अणु
		50, 66, 75, 83, 90, 95, 100, 105,
		110, 115, 120, 125, 133, 143, 166
	पूर्ण;
	स्थिर पूर्णांक *refresh_tbl;
	पूर्णांक i, size;

	अगर (M64_HAS(XL_MEM)) अणु
		refresh_tbl = ragexl_tbl;
		size = ARRAY_SIZE(ragexl_tbl);
	पूर्ण अन्यथा अणु
		refresh_tbl = ragepro_tbl;
		size = ARRAY_SIZE(ragepro_tbl);
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (xclk < refresh_tbl[i])
			अवरोध;
	पूर्ण
	par->mem_refresh_rate = i;
पूर्ण

/*
 * Initialisation
 */

अटल काष्ठा fb_info *fb_list = शून्य;

#अगर defined(__i386__) && defined(CONFIG_FB_ATY_GENERIC_LCD)
अटल पूर्णांक atyfb_get_timings_from_lcd(काष्ठा atyfb_par *par,
				      काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (par->lcd_table != 0 && (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) अणु
		*var = शेष_var;
		var->xres = var->xres_भव = par->lcd_hdisp;
		var->right_margin = par->lcd_right_margin;
		var->left_margin = par->lcd_hblank_len -
			(par->lcd_right_margin + par->lcd_hsync_dly +
			 par->lcd_hsync_len);
		var->hsync_len = par->lcd_hsync_len + par->lcd_hsync_dly;
		var->yres = var->yres_भव = par->lcd_vdisp;
		var->lower_margin = par->lcd_lower_margin;
		var->upper_margin = par->lcd_vblank_len -
			(par->lcd_lower_margin + par->lcd_vsync_len);
		var->vsync_len = par->lcd_vsync_len;
		var->pixघड़ी = par->lcd_pixघड़ी;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* defined(__i386__) && defined(CONFIG_FB_ATY_GENERIC_LCD) */

अटल पूर्णांक aty_init(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	स्थिर अक्षर *ramname = शून्य, *xtal;
	पूर्णांक gtb_memsize, has_var = 0;
	काष्ठा fb_var_screeninfo var;
	पूर्णांक ret;
#अगर_घोषित CONFIG_ATARI
	u8 dac_type;
#पूर्ण_अगर

	init_रुकोqueue_head(&par->vblank.रुको);
	spin_lock_init(&par->पूर्णांक_lock);

#अगर_घोषित CONFIG_FB_ATY_GX
	अगर (!M64_HAS(INTEGRATED)) अणु
		u32 stat0;
		u8 dac_subtype, clk_type;
		stat0 = aty_ld_le32(CNFG_STAT0, par);
		par->bus_type = (stat0 >> 0) & 0x07;
		par->ram_type = (stat0 >> 3) & 0x07;
		ramname = aty_gx_ram[par->ram_type];
		/* FIXME: घड़ीchip/RAMDAC probing? */
#अगर_घोषित CONFIG_ATARI
		clk_type = CLK_ATI18818_1;
		dac_type = (stat0 >> 9) & 0x07;
		अगर (dac_type == 0x07)
			dac_subtype = DAC_ATT20C408;
		अन्यथा
			dac_subtype = (aty_ld_8(SCRATCH_REG1 + 1, par) & 0xF0) | dac_type;
#अन्यथा
		dac_subtype = DAC_IBMRGB514;
		clk_type = CLK_IBMRGB514;
#पूर्ण_अगर
		चयन (dac_subtype) अणु
		हाल DAC_IBMRGB514:
			par->dac_ops = &aty_dac_ibm514;
			अवरोध;
#अगर_घोषित CONFIG_ATARI
		हाल DAC_ATI68860_B:
		हाल DAC_ATI68860_C:
			par->dac_ops = &aty_dac_ati68860b;
			अवरोध;
		हाल DAC_ATT20C408:
		हाल DAC_ATT21C498:
			par->dac_ops = &aty_dac_att21c498;
			अवरोध;
#पूर्ण_अगर
		शेष:
			PRINTKI("aty_init: DAC type not implemented yet!\n");
			par->dac_ops = &aty_dac_unsupported;
			अवरोध;
		पूर्ण
		चयन (clk_type) अणु
#अगर_घोषित CONFIG_ATARI
		हाल CLK_ATI18818_1:
			par->pll_ops = &aty_pll_ati18818_1;
			अवरोध;
#अन्यथा
		हाल CLK_IBMRGB514:
			par->pll_ops = &aty_pll_ibm514;
			अवरोध;
#पूर्ण_अगर
		शेष:
			PRINTKI("aty_init: CLK type not implemented yet!");
			par->pll_ops = &aty_pll_unsupported;
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GX */
#अगर_घोषित CONFIG_FB_ATY_CT
	अगर (M64_HAS(INTEGRATED)) अणु
		par->dac_ops = &aty_dac_ct;
		par->pll_ops = &aty_pll_ct;
		par->bus_type = PCI;
		par->ram_type = (aty_ld_le32(CNFG_STAT0, par) & 0x07);
		अगर (M64_HAS(XL_MEM))
			ramname = aty_xl_ram[par->ram_type];
		अन्यथा
			ramname = aty_ct_ram[par->ram_type];
		/* क्रम many chips, the mclk is 67 MHz क्रम SDRAM, 63 MHz otherwise */
		अगर (par->pll_limits.mclk == 67 && par->ram_type < SDRAM)
			par->pll_limits.mclk = 63;
		/* Mobility + 32bit memory पूर्णांकerface need halved XCLK. */
		अगर (M64_HAS(MOBIL_BUS) && par->ram_type == SDRAM32)
			par->pll_limits.xclk = (par->pll_limits.xclk + 1) >> 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_PMAC
	/*
	 * The Apple iBook1 uses non-standard memory frequencies.
	 * We detect it and set the frequency manually.
	 */
	अगर (of_machine_is_compatible("PowerBook2,1")) अणु
		par->pll_limits.mclk = 70;
		par->pll_limits.xclk = 53;
	पूर्ण
#पूर्ण_अगर

	/* Allow command line to override घड़ीs. */
	अगर (pll)
		par->pll_limits.pll_max = pll;
	अगर (mclk)
		par->pll_limits.mclk = mclk;
	अगर (xclk)
		par->pll_limits.xclk = xclk;

	aty_calc_mem_refresh(par, par->pll_limits.xclk);
	par->pll_per = 1000000/par->pll_limits.pll_max;
	par->mclk_per = 1000000/par->pll_limits.mclk;
	par->xclk_per = 1000000/par->pll_limits.xclk;

	par->ref_clk_per = 1000000000000ULL / 14318180;
	xtal = "14.31818";

#अगर_घोषित CONFIG_FB_ATY_CT
	अगर (M64_HAS(GTB_DSP)) अणु
		u8 pll_ref_भाग = aty_ld_pll_ct(PLL_REF_DIV, par);

		अगर (pll_ref_भाग) अणु
			पूर्णांक dअगरf1, dअगरf2;
			dअगरf1 = 510 * 14 / pll_ref_भाग - par->pll_limits.pll_max;
			dअगरf2 = 510 * 29 / pll_ref_भाग - par->pll_limits.pll_max;
			अगर (dअगरf1 < 0)
				dअगरf1 = -dअगरf1;
			अगर (dअगरf2 < 0)
				dअगरf2 = -dअगरf2;
			अगर (dअगरf2 < dअगरf1) अणु
				par->ref_clk_per = 1000000000000ULL / 29498928;
				xtal = "29.498928";
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */

	/* save previous video mode */
	aty_get_crtc(par, &par->saved_crtc);
	अगर (par->pll_ops->get_pll)
		par->pll_ops->get_pll(info, &par->saved_pll);

	par->mem_cntl = aty_ld_le32(MEM_CNTL, par);
	gtb_memsize = M64_HAS(GTB_DSP);
	अगर (gtb_memsize)
		/* 0xF used instead of MEM_SIZE_ALIAS */
		चयन (par->mem_cntl & 0xF) अणु
		हाल MEM_SIZE_512K:
			info->fix.smem_len = 0x80000;
			अवरोध;
		हाल MEM_SIZE_1M:
			info->fix.smem_len = 0x100000;
			अवरोध;
		हाल MEM_SIZE_2M_GTB:
			info->fix.smem_len = 0x200000;
			अवरोध;
		हाल MEM_SIZE_4M_GTB:
			info->fix.smem_len = 0x400000;
			अवरोध;
		हाल MEM_SIZE_6M_GTB:
			info->fix.smem_len = 0x600000;
			अवरोध;
		हाल MEM_SIZE_8M_GTB:
			info->fix.smem_len = 0x800000;
			अवरोध;
		शेष:
			info->fix.smem_len = 0x80000;
	पूर्ण अन्यथा
		चयन (par->mem_cntl & MEM_SIZE_ALIAS) अणु
		हाल MEM_SIZE_512K:
			info->fix.smem_len = 0x80000;
			अवरोध;
		हाल MEM_SIZE_1M:
			info->fix.smem_len = 0x100000;
			अवरोध;
		हाल MEM_SIZE_2M:
			info->fix.smem_len = 0x200000;
			अवरोध;
		हाल MEM_SIZE_4M:
			info->fix.smem_len = 0x400000;
			अवरोध;
		हाल MEM_SIZE_6M:
			info->fix.smem_len = 0x600000;
			अवरोध;
		हाल MEM_SIZE_8M:
			info->fix.smem_len = 0x800000;
			अवरोध;
		शेष:
			info->fix.smem_len = 0x80000;
		पूर्ण

	अगर (M64_HAS(MAGIC_VRAM_SIZE)) अणु
		अगर (aty_ld_le32(CNFG_STAT1, par) & 0x40000000)
			info->fix.smem_len += 0x400000;
	पूर्ण

	अगर (vram) अणु
		info->fix.smem_len = vram * 1024;
		par->mem_cntl &= ~(gtb_memsize ? 0xF : MEM_SIZE_ALIAS);
		अगर (info->fix.smem_len <= 0x80000)
			par->mem_cntl |= MEM_SIZE_512K;
		अन्यथा अगर (info->fix.smem_len <= 0x100000)
			par->mem_cntl |= MEM_SIZE_1M;
		अन्यथा अगर (info->fix.smem_len <= 0x200000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_2M_GTB : MEM_SIZE_2M;
		अन्यथा अगर (info->fix.smem_len <= 0x400000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_4M_GTB : MEM_SIZE_4M;
		अन्यथा अगर (info->fix.smem_len <= 0x600000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_6M_GTB : MEM_SIZE_6M;
		अन्यथा
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_8M_GTB : MEM_SIZE_8M;
		aty_st_le32(MEM_CNTL, par->mem_cntl, par);
	पूर्ण

	/*
	 * Reg Block 0 (CT-compatible block) is at mmio_start
	 * Reg Block 1 (mulसमयdia extensions) is at mmio_start - 0x400
	 */
	अगर (M64_HAS(GX)) अणु
		info->fix.mmio_len = 0x400;
		info->fix.accel = FB_ACCEL_ATI_MACH64GX;
	पूर्ण अन्यथा अगर (M64_HAS(CT)) अणु
		info->fix.mmio_len = 0x400;
		info->fix.accel = FB_ACCEL_ATI_MACH64CT;
	पूर्ण अन्यथा अगर (M64_HAS(VT)) अणु
		info->fix.mmio_start -= 0x400;
		info->fix.mmio_len = 0x800;
		info->fix.accel = FB_ACCEL_ATI_MACH64VT;
	पूर्ण अन्यथा अणु/* GT */
		info->fix.mmio_start -= 0x400;
		info->fix.mmio_len = 0x800;
		info->fix.accel = FB_ACCEL_ATI_MACH64GT;
	पूर्ण

	PRINTKI("%d%c %s, %s MHz XTAL, %d MHz PLL, %d Mhz MCLK, %d MHz XCLK\n",
		info->fix.smem_len == 0x80000 ? 512 : (info->fix.smem_len>>20),
		info->fix.smem_len == 0x80000 ? 'K' : 'M', ramname, xtal,
		par->pll_limits.pll_max, par->pll_limits.mclk,
		par->pll_limits.xclk);

#अगर defined(DEBUG) && defined(CONFIG_FB_ATY_CT)
	अगर (M64_HAS(INTEGRATED)) अणु
		पूर्णांक i;
		prपूर्णांकk("debug atyfb: BUS_CNTL DAC_CNTL MEM_CNTL "
		       "EXT_MEM_CNTL CRTC_GEN_CNTL DSP_CONFIG "
		       "DSP_ON_OFF CLOCK_CNTL\n"
		       "debug atyfb: %08x %08x %08x "
		       "%08x     %08x      %08x   "
		       "%08x   %08x\n"
		       "debug atyfb: PLL",
		       aty_ld_le32(BUS_CNTL, par),
		       aty_ld_le32(DAC_CNTL, par),
		       aty_ld_le32(MEM_CNTL, par),
		       aty_ld_le32(EXT_MEM_CNTL, par),
		       aty_ld_le32(CRTC_GEN_CNTL, par),
		       aty_ld_le32(DSP_CONFIG, par),
		       aty_ld_le32(DSP_ON_OFF, par),
		       aty_ld_le32(CLOCK_CNTL, par));
		क्रम (i = 0; i < 40; i++)
			pr_cont(" %02x", aty_ld_pll_ct(i, par));
		pr_cont("\n");
	पूर्ण
#पूर्ण_अगर
	अगर (par->pll_ops->init_pll)
		par->pll_ops->init_pll(info, &par->pll);
	अगर (par->pll_ops->resume_pll)
		par->pll_ops->resume_pll(info, &par->pll);

	aty_fudge_framebuffer_len(info);

	/*
	 * Disable रेजिस्टर access through the linear aperture
	 * अगर the auxiliary aperture is used so we can access
	 * the full 8 MB of video RAM on 8 MB boards.
	 */
	अगर (par->aux_start)
		aty_st_le32(BUS_CNTL, aty_ld_le32(BUS_CNTL, par) |
			    BUS_APER_REG_DIS, par);

	अगर (!nomtrr)
		/*
		 * Only the ioremap_wc()'d area will get WC here
		 * since ioremap_uc() was used on the entire PCI BAR.
		 */
		par->wc_cookie = arch_phys_wc_add(par->res_start,
						  par->res_size);

	info->fbops = &atyfb_ops;
	info->pseuकरो_palette = par->pseuकरो_palette;
	info->flags = FBINFO_DEFAULT           |
		      FBINFO_HWACCEL_IMAGEBLIT |
		      FBINFO_HWACCEL_FILLRECT  |
		      FBINFO_HWACCEL_COPYAREA  |
		      FBINFO_HWACCEL_YPAN      |
		      FBINFO_READS_FAST;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (M64_HAS(G3_PB_1_1) && of_machine_is_compatible("PowerBook1,1")) अणु
		/*
		 * these bits let the 101 घातerbook
		 * wake up from sleep -- paulus
		 */
		aty_st_lcd(POWER_MANAGEMENT, aty_ld_lcd(POWER_MANAGEMENT, par) |
			   USE_F32KHZ | TRISTATE_MEM_EN, par);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (M64_HAS(MOBIL_BUS) && backlight) अणु
#अगर_घोषित CONFIG_FB_ATY_BACKLIGHT
		aty_bl_init(par);
#पूर्ण_अगर
	पूर्ण

	स_रखो(&var, 0, माप(var));
#अगर_घोषित CONFIG_PPC
	अगर (machine_is(घातermac)) अणु
		/*
		 * FIXME: The NVRAM stuff should be put in a Mac-specअगरic file,
		 *        as it applies to all Mac video cards
		 */
		अगर (mode) अणु
			अगर (mac_find_mode(&var, info, mode, 8))
				has_var = 1;
		पूर्ण अन्यथा अणु
			अगर (शेष_vmode == VMODE_CHOOSE) अणु
				पूर्णांक sense;
				अगर (M64_HAS(G3_PB_1024x768))
					/* G3 PowerBook with 1024x768 LCD */
					शेष_vmode = VMODE_1024_768_60;
				अन्यथा अगर (of_machine_is_compatible("iMac"))
					शेष_vmode = VMODE_1024_768_75;
				अन्यथा अगर (of_machine_is_compatible("PowerBook2,1"))
					/* iBook with 800x600 LCD */
					शेष_vmode = VMODE_800_600_60;
				अन्यथा
					शेष_vmode = VMODE_640_480_67;
				sense = पढ़ो_aty_sense(par);
				PRINTKI("monitor sense=%x, mode %d\n",
					sense,  mac_map_monitor_sense(sense));
			पूर्ण
			अगर (शेष_vmode <= 0 || शेष_vmode > VMODE_MAX)
				शेष_vmode = VMODE_640_480_60;
			अगर (शेष_cmode < CMODE_8 || शेष_cmode > CMODE_32)
				शेष_cmode = CMODE_8;
			अगर (!mac_vmode_to_var(शेष_vmode, शेष_cmode,
					      &var))
				has_var = 1;
		पूर्ण
	पूर्ण

#पूर्ण_अगर /* !CONFIG_PPC */

#अगर defined(__i386__) && defined(CONFIG_FB_ATY_GENERIC_LCD)
	अगर (!atyfb_get_timings_from_lcd(par, &var))
		has_var = 1;
#पूर्ण_अगर

	अगर (mode && fb_find_mode(&var, info, mode, शून्य, 0, &deभ_शेषe, 8))
		has_var = 1;

	अगर (!has_var)
		var = शेष_var;

	अगर (noaccel)
		var.accel_flags &= ~FB_ACCELF_TEXT;
	अन्यथा
		var.accel_flags |= FB_ACCELF_TEXT;

	अगर (comp_sync != -1) अणु
		अगर (!comp_sync)
			var.sync &= ~FB_SYNC_COMP_HIGH_ACT;
		अन्यथा
			var.sync |= FB_SYNC_COMP_HIGH_ACT;
	पूर्ण

	अगर (var.yres == var.yres_भव) अणु
		u32 videoram = (info->fix.smem_len - (PAGE_SIZE << 2));
		var.yres_भव = ((videoram * 8) / var.bits_per_pixel) / var.xres_भव;
		अगर (var.yres_भव < var.yres)
			var.yres_भव = var.yres;
	पूर्ण

	ret = atyfb_check_var(&var, info);
	अगर (ret) अणु
		PRINTKE("can't set default video mode\n");
		जाओ aty_init_निकास;
	पूर्ण

#अगर_घोषित CONFIG_FB_ATY_CT
	अगर (!noaccel && M64_HAS(INTEGRATED))
		aty_init_cursor(info, &atyfb_ops);
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */
	info->var = var;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret < 0)
		जाओ aty_init_निकास;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		fb_dealloc_cmap(&info->cmap);
		जाओ aty_init_निकास;
	पूर्ण

	fb_list = info;

	PRINTKI("fb%d: %s frame buffer device on %s\n",
		info->node, info->fix.id, par->bus_type == ISA ? "ISA" : "PCI");
	वापस 0;

aty_init_निकास:
	/* restore video mode */
	aty_set_crtc(par, &par->saved_crtc);
	par->pll_ops->set_pll(info, &par->saved_pll);
	arch_phys_wc_del(par->wc_cookie);

	वापस ret;
पूर्ण

#अगर defined(CONFIG_ATARI) && !defined(MODULE)
अटल पूर्णांक store_video_par(अक्षर *video_str, अचिन्हित अक्षर m64_num)
अणु
	अक्षर *p;
	अचिन्हित दीर्घ vmembase, size, guiregbase;

	PRINTKI("store_video_par() '%s' \n", video_str);

	अगर (!(p = strsep(&video_str, ";")) || !*p)
		जाओ mach64_invalid;
	vmembase = simple_म_से_अदीर्घ(p, शून्य, 0);
	अगर (!(p = strsep(&video_str, ";")) || !*p)
		जाओ mach64_invalid;
	size = simple_म_से_अदीर्घ(p, शून्य, 0);
	अगर (!(p = strsep(&video_str, ";")) || !*p)
		जाओ mach64_invalid;
	guiregbase = simple_म_से_अदीर्घ(p, शून्य, 0);

	phys_vmembase[m64_num] = vmembase;
	phys_size[m64_num] = size;
	phys_guiregbase[m64_num] = guiregbase;
	PRINTKI("stored them all: $%08lX $%08lX $%08lX \n", vmembase, size,
		guiregbase);
	वापस 0;

 mach64_invalid:
	phys_vmembase[m64_num] = 0;
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATARI && !MODULE */

/*
 * Blank the display.
 */

अटल पूर्णांक atyfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 gen_cntl;

	अगर (par->lock_blank || par->asleep)
		वापस 0;

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table && blank > FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) अणु
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm &= ~PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	पूर्ण
#पूर्ण_अगर

	gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
	gen_cntl &= ~0x400004c;
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		अवरोध;
	हाल FB_BLANK_NORMAL:
		gen_cntl |= 0x4000040;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		gen_cntl |= 0x4000048;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		gen_cntl |= 0x4000044;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		gen_cntl |= 0x400004c;
		अवरोध;
	पूर्ण
	aty_st_le32(CRTC_GEN_CNTL, gen_cntl, par);

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table && blank <= FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) अणु
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm |= PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम aty_st_pal(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		       स्थिर काष्ठा atyfb_par *par)
अणु
	aty_st_8(DAC_W_INDEX, regno, par);
	aty_st_8(DAC_DATA, red, par);
	aty_st_8(DAC_DATA, green, par);
	aty_st_8(DAC_DATA, blue, par);
पूर्ण

/*
 * Set a single color रेजिस्टर. The values supplied are alपढ़ोy
 * rounded करोwn to the hardware's capabilities (according to the
 * entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
 * !! 4 & 8 =  PSEUDO, > 8 = सूचीECTCOLOR
 */

अटल पूर्णांक atyfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	पूर्णांक i, depth;
	u32 *pal = info->pseuकरो_palette;

	depth = info->var.bits_per_pixel;
	अगर (depth == 16)
		depth = (info->var.green.length == 5) ? 15 : 16;

	अगर (par->asleep)
		वापस 0;

	अगर (regno > 255 ||
	    (depth == 16 && regno > 63) ||
	    (depth == 15 && regno > 31))
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	par->palette[regno].red = red;
	par->palette[regno].green = green;
	par->palette[regno].blue = blue;

	अगर (regno < 16) अणु
		चयन (depth) अणु
		हाल 15:
			pal[regno] = (regno << 10) | (regno << 5) | regno;
			अवरोध;
		हाल 16:
			pal[regno] = (regno << 11) | (regno << 5) | regno;
			अवरोध;
		हाल 24:
			pal[regno] = (regno << 16) | (regno << 8) | regno;
			अवरोध;
		हाल 32:
			i = (regno << 8) | regno;
			pal[regno] = (i << 16) | i;
			अवरोध;
		पूर्ण
	पूर्ण

	i = aty_ld_8(DAC_CNTL, par) & 0xfc;
	अगर (M64_HAS(EXTRA_BRIGHT))
		i |= 0x2; /* DAC_CNTL | 0x2 turns off the extra brightness क्रम gt */
	aty_st_8(DAC_CNTL, i, par);
	aty_st_8(DAC_MASK, 0xff, par);

	अगर (M64_HAS(INTEGRATED)) अणु
		अगर (depth == 16) अणु
			अगर (regno < 32)
				aty_st_pal(regno << 3, red,
					   par->palette[regno << 1].green,
					   blue, par);
			red = par->palette[regno >> 1].red;
			blue = par->palette[regno >> 1].blue;
			regno <<= 2;
		पूर्ण अन्यथा अगर (depth == 15) अणु
			regno <<= 3;
			क्रम (i = 0; i < 8; i++)
				aty_st_pal(regno + i, red, green, blue, par);
		पूर्ण
	पूर्ण
	aty_st_pal(regno, red, green, blue, par);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI

#अगर_घोषित __sparc__

अटल पूर्णांक atyfb_setup_sparc(काष्ठा pci_dev *pdev, काष्ठा fb_info *info,
			     अचिन्हित दीर्घ addr)
अणु
	काष्ठा atyfb_par *par = info->par;
	काष्ठा device_node *dp;
	u32 mem, chip_id;
	पूर्णांक i, j, ret;

	/*
	 * Map memory-mapped रेजिस्टरs.
	 */
	par->ati_regbase = (व्योम *)addr + 0x7ffc00UL;
	info->fix.mmio_start = addr + 0x7ffc00UL;

	/*
	 * Map in big-endian aperture.
	 */
	info->screen_base = (अक्षर *) (addr + 0x800000UL);
	info->fix.smem_start = addr + 0x800000UL;

	/*
	 * Figure mmap addresses from PCI config space.
	 * Split Framebuffer in big- and little-endian halfs.
	 */
	क्रम (i = 0; i < 6 && pdev->resource[i].start; i++)
		/* nothing */ ;
	j = i + 4;

	par->mmap_map = kसुस्मृति(j, माप(*par->mmap_map), GFP_ATOMIC);
	अगर (!par->mmap_map) अणु
		PRINTKE("atyfb_setup_sparc() can't alloc mmap_map\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0, j = 2; i < 6 && pdev->resource[i].start; i++) अणु
		काष्ठा resource *rp = &pdev->resource[i];
		पूर्णांक io, breg = PCI_BASE_ADDRESS_0 + (i << 2);
		अचिन्हित दीर्घ base;
		u32 size, pbase;

		base = rp->start;

		io = (rp->flags & IORESOURCE_IO);

		size = rp->end - base + 1;

		pci_पढ़ो_config_dword(pdev, breg, &pbase);

		अगर (io)
			size &= ~1;

		/*
		 * Map the framebuffer a second समय, this समय without
		 * the braindead _PAGE_IE setting. This is used by the
		 * fixed Xserver, but we need to मुख्यtain the old mapping
		 * to stay compatible with older ones...
		 */
		अगर (base == addr) अणु
			par->mmap_map[j].voff = (pbase + 0x10000000) & PAGE_MASK;
			par->mmap_map[j].poff = base & PAGE_MASK;
			par->mmap_map[j].size = (size + ~PAGE_MASK) & PAGE_MASK;
			par->mmap_map[j].prot_mask = _PAGE_CACHE;
			par->mmap_map[j].prot_flag = _PAGE_E;
			j++;
		पूर्ण

		/*
		 * Here comes the old framebuffer mapping with _PAGE_IE
		 * set क्रम the big endian half of the framebuffer...
		 */
		अगर (base == addr) अणु
			par->mmap_map[j].voff = (pbase + 0x800000) & PAGE_MASK;
			par->mmap_map[j].poff = (base + 0x800000) & PAGE_MASK;
			par->mmap_map[j].size = 0x800000;
			par->mmap_map[j].prot_mask = _PAGE_CACHE;
			par->mmap_map[j].prot_flag = _PAGE_E | _PAGE_IE;
			size -= 0x800000;
			j++;
		पूर्ण

		par->mmap_map[j].voff = pbase & PAGE_MASK;
		par->mmap_map[j].poff = base & PAGE_MASK;
		par->mmap_map[j].size = (size + ~PAGE_MASK) & PAGE_MASK;
		par->mmap_map[j].prot_mask = _PAGE_CACHE;
		par->mmap_map[j].prot_flag = _PAGE_E;
		j++;
	पूर्ण

	ret = correct_chipset(par);
	अगर (ret)
		वापस ret;

	अगर (IS_XL(pdev->device)) अणु
		/*
		 * Fix PROMs idea of MEM_CNTL settings...
		 */
		mem = aty_ld_le32(MEM_CNTL, par);
		chip_id = aty_ld_le32(CNFG_CHIP_ID, par);
		अगर (((chip_id & CFG_CHIP_TYPE) == VT_CHIP_ID) && !((chip_id >> 24) & 1)) अणु
			चयन (mem & 0x0f) अणु
			हाल 3:
				mem = (mem & ~(0x0f)) | 2;
				अवरोध;
			हाल 7:
				mem = (mem & ~(0x0f)) | 3;
				अवरोध;
			हाल 9:
				mem = (mem & ~(0x0f)) | 4;
				अवरोध;
			हाल 11:
				mem = (mem & ~(0x0f)) | 5;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर ((aty_ld_le32(CNFG_STAT0, par) & 7) >= SDRAM)
				mem &= ~(0x00700000);
		पूर्ण
		mem &= ~(0xcf80e000);	/* Turn off all unकरोcumented bits. */
		aty_st_le32(MEM_CNTL, mem, par);
	पूर्ण

	dp = pci_device_to_OF_node(pdev);
	अगर (dp == of_console_device) अणु
		काष्ठा fb_var_screeninfo *var = &शेष_var;
		अचिन्हित पूर्णांक N, P, Q, M, T, R;
		काष्ठा crtc crtc;
		u8 pll_regs[16];
		u8 घड़ी_cntl;

		crtc.vxres = of_getपूर्णांकprop_शेष(dp, "width", 1024);
		crtc.vyres = of_getपूर्णांकprop_शेष(dp, "height", 768);
		var->bits_per_pixel = of_getपूर्णांकprop_शेष(dp, "depth", 8);
		var->xoffset = var->yoffset = 0;
		crtc.h_tot_disp = aty_ld_le32(CRTC_H_TOTAL_DISP, par);
		crtc.h_sync_strt_wid = aty_ld_le32(CRTC_H_SYNC_STRT_WID, par);
		crtc.v_tot_disp = aty_ld_le32(CRTC_V_TOTAL_DISP, par);
		crtc.v_sync_strt_wid = aty_ld_le32(CRTC_V_SYNC_STRT_WID, par);
		crtc.gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
		aty_crtc_to_var(&crtc, var);

		/*
		 * Read the PLL to figure actual Refresh Rate.
		 */
		घड़ी_cntl = aty_ld_8(CLOCK_CNTL, par);
		/* DPRINTK("CLOCK_CNTL %02x\n", घड़ी_cntl); */
		क्रम (i = 0; i < 16; i++)
			pll_regs[i] = aty_ld_pll_ct(i, par);

		/*
		 * PLL Reference Divider M:
		 */
		M = pll_regs[PLL_REF_DIV];

		/*
		 * PLL Feedback Divider N (Dependent on CLOCK_CNTL):
		 */
		N = pll_regs[VCLK0_FB_DIV + (घड़ी_cntl & 3)];

		/*
		 * PLL Post Divider P (Dependent on CLOCK_CNTL):
		 */
		P = aty_postभागiders[((pll_regs[VCLK_POST_DIV] >> ((घड़ी_cntl & 3) << 1)) & 3) |
		                     ((pll_regs[PLL_EXT_CNTL] >> (2 + (घड़ी_cntl & 3))) & 4)];

		/*
		 * PLL Divider Q:
		 */
		Q = N / P;

		/*
		 * Target Frequency:
		 *
		 *      T * M
		 * Q = -------
		 *      2 * R
		 *
		 * where R is XTALIN (= 14318 or 29498 kHz).
		 */
		अगर (IS_XL(pdev->device))
			R = 29498;
		अन्यथा
			R = 14318;

		T = 2 * Q * R / M;

		शेष_var.pixघड़ी = 1000000000 / T;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* __sparc__ */

#अगर_घोषित __i386__
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
अटल व्योम aty_init_lcd(काष्ठा atyfb_par *par, u32 bios_base)
अणु
	u32 driv_inf_tab, sig;
	u16 lcd_ofs;

	/*
	 * To support an LCD panel, we should know it's dimensions and
	 *  it's desired pixel घड़ी.
	 * There are two ways to करो it:
	 *  - Check the startup video mode and calculate the panel
	 *    size from it. This is unreliable.
	 *  - Read it from the driver inक्रमmation table in the video BIOS.
	 */
	/* Address of driver inक्रमmation table is at offset 0x78. */
	driv_inf_tab = bios_base + *((u16 *)(bios_base+0x78));

	/* Check क्रम the driver inक्रमmation table signature. */
	sig = *(u32 *)driv_inf_tab;
	अगर ((sig == 0x54504c24) || /* Rage LT pro */
	    (sig == 0x544d5224) || /* Rage mobility */
	    (sig == 0x54435824) || /* Rage XC */
	    (sig == 0x544c5824)) अणु /* Rage XL */
		PRINTKI("BIOS contains driver information table.\n");
		lcd_ofs = *(u16 *)(driv_inf_tab + 10);
		par->lcd_table = 0;
		अगर (lcd_ofs != 0)
			par->lcd_table = bios_base + lcd_ofs;
	पूर्ण

	अगर (par->lcd_table != 0) अणु
		अक्षर model[24];
		अक्षर strbuf[16];
		अक्षर refresh_rates_buf[100];
		पूर्णांक id, tech, f, i, m, शेष_refresh_rate;
		अक्षर *txtcolour;
		अक्षर *txपंचांगonitor;
		अक्षर *txtdual;
		अक्षर *txtक्रमmat;
		u16 width, height, panel_type, refresh_rates;
		u16 *lcdmodeptr;
		u32 क्रमmat;
		u8 lcd_refresh_rates[16] = अणु 50, 56, 60, 67, 70, 72, 75, 76, 85,
					     90, 100, 120, 140, 150, 160, 200 पूर्ण;
		/*
		 * The most important inक्रमmation is the panel size at
		 * offset 25 and 27, but there's some other nice inक्रमmation
		 * which we prपूर्णांक to the screen.
		 */
		id = *(u8 *)par->lcd_table;
		म_नकलन(model, (अक्षर *)par->lcd_table+1, 24);
		model[23] = 0;

		width = par->lcd_width = *(u16 *)(par->lcd_table+25);
		height = par->lcd_height = *(u16 *)(par->lcd_table+27);
		panel_type = *(u16 *)(par->lcd_table+29);
		अगर (panel_type & 1)
			txtcolour = "colour";
		अन्यथा
			txtcolour = "monochrome";
		अगर (panel_type & 2)
			txtdual = "dual (split) ";
		अन्यथा
			txtdual = "";
		tech = (panel_type >> 2) & 63;
		चयन (tech) अणु
		हाल 0:
			txपंचांगonitor = "passive matrix";
			अवरोध;
		हाल 1:
			txपंचांगonitor = "active matrix";
			अवरोध;
		हाल 2:
			txपंचांगonitor = "active addressed STN";
			अवरोध;
		हाल 3:
			txपंचांगonitor = "EL";
			अवरोध;
		हाल 4:
			txपंचांगonitor = "plasma";
			अवरोध;
		शेष:
			txपंचांगonitor = "unknown";
		पूर्ण
		क्रमmat = *(u32 *)(par->lcd_table+57);
		अगर (tech == 0 || tech == 2) अणु
			चयन (क्रमmat & 7) अणु
			हाल 0:
				txtक्रमmat = "12 bit interface";
				अवरोध;
			हाल 1:
				txtक्रमmat = "16 bit interface";
				अवरोध;
			हाल 2:
				txtक्रमmat = "24 bit interface";
				अवरोध;
			शेष:
				txtक्रमmat = "unknown format";
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (क्रमmat & 7) अणु
			हाल 0:
				txtक्रमmat = "8 colours";
				अवरोध;
			हाल 1:
				txtक्रमmat = "512 colours";
				अवरोध;
			हाल 2:
				txtक्रमmat = "4096 colours";
				अवरोध;
			हाल 4:
				txtक्रमmat = "262144 colours (LT mode)";
				अवरोध;
			हाल 5:
				txtक्रमmat = "16777216 colours";
				अवरोध;
			हाल 6:
				txtक्रमmat = "262144 colours (FDPI-2 mode)";
				अवरोध;
			शेष:
				txtक्रमmat = "unknown format";
			पूर्ण
		पूर्ण
		PRINTKI("%s%s %s monitor detected: %s\n",
			txtdual, txtcolour, txपंचांगonitor, model);
		PRINTKI("       id=%d, %dx%d pixels, %s\n",
			id, width, height, txtक्रमmat);
		refresh_rates_buf[0] = 0;
		refresh_rates = *(u16 *)(par->lcd_table+62);
		m = 1;
		f = 0;
		क्रम (i = 0; i < 16; i++) अणु
			अगर (refresh_rates & m) अणु
				अगर (f == 0) अणु
					प्र_लिखो(strbuf, "%d",
						lcd_refresh_rates[i]);
					f++;
				पूर्ण अन्यथा अणु
					प्र_लिखो(strbuf, ",%d",
						lcd_refresh_rates[i]);
				पूर्ण
				म_जोड़ो(refresh_rates_buf, strbuf);
			पूर्ण
			m = m << 1;
		पूर्ण
		शेष_refresh_rate = (*(u8 *)(par->lcd_table+61) & 0xf0) >> 4;
		PRINTKI("       supports refresh rates [%s], default %d Hz\n",
			refresh_rates_buf, lcd_refresh_rates[शेष_refresh_rate]);
		par->lcd_refreshrate = lcd_refresh_rates[शेष_refresh_rate];
		/*
		 * We now need to determine the crtc parameters क्रम the
		 * LCD monitor. This is tricky, because they are not stored
		 * inभागidually in the BIOS. Instead, the BIOS contains a
		 * table of display modes that work क्रम this monitor.
		 *
		 * The idea is that we search क्रम a mode of the same dimensions
		 * as the dimensions of the LCD monitor. Say our LCD monitor
		 * is 800x600 pixels, we search क्रम a 800x600 monitor.
		 * The CRTC parameters we find here are the ones that we need
		 * to use to simulate other resolutions on the LCD screen.
		 */
		lcdmodeptr = (u16 *)(par->lcd_table + 64);
		जबतक (*lcdmodeptr != 0) अणु
			u32 modeptr;
			u16 mwidth, mheight, lcd_hsync_start, lcd_vsync_start;
			modeptr = bios_base + *lcdmodeptr;

			mwidth = *((u16 *)(modeptr+0));
			mheight = *((u16 *)(modeptr+2));

			अगर (mwidth == width && mheight == height) अणु
				par->lcd_pixघड़ी = 100000000 / *((u16 *)(modeptr+9));
				par->lcd_htotal = *((u16 *)(modeptr+17)) & 511;
				par->lcd_hdisp = *((u16 *)(modeptr+19)) & 511;
				lcd_hsync_start = *((u16 *)(modeptr+21)) & 511;
				par->lcd_hsync_dly = (*((u16 *)(modeptr+21)) >> 9) & 7;
				par->lcd_hsync_len = *((u8 *)(modeptr+23)) & 63;

				par->lcd_vtotal = *((u16 *)(modeptr+24)) & 2047;
				par->lcd_vdisp = *((u16 *)(modeptr+26)) & 2047;
				lcd_vsync_start = *((u16 *)(modeptr+28)) & 2047;
				par->lcd_vsync_len = (*((u16 *)(modeptr+28)) >> 11) & 31;

				par->lcd_htotal = (par->lcd_htotal + 1) * 8;
				par->lcd_hdisp = (par->lcd_hdisp + 1) * 8;
				lcd_hsync_start = (lcd_hsync_start + 1) * 8;
				par->lcd_hsync_len = par->lcd_hsync_len * 8;

				par->lcd_vtotal++;
				par->lcd_vdisp++;
				lcd_vsync_start++;

				par->lcd_right_margin = lcd_hsync_start - par->lcd_hdisp;
				par->lcd_lower_margin = lcd_vsync_start - par->lcd_vdisp;
				par->lcd_hblank_len = par->lcd_htotal - par->lcd_hdisp;
				par->lcd_vblank_len = par->lcd_vtotal - par->lcd_vdisp;
				अवरोध;
			पूर्ण

			lcdmodeptr++;
		पूर्ण
		अगर (*lcdmodeptr == 0) अणु
			PRINTKE("LCD monitor CRTC parameters not found!!!\n");
			/* To करो: Switch to CRT अगर possible. */
		पूर्ण अन्यथा अणु
			PRINTKI("       LCD CRTC parameters: %d.%d  %d %d %d %d  %d %d %d %d\n",
				1000000 / par->lcd_pixघड़ी, 1000000 % par->lcd_pixघड़ी,
				par->lcd_hdisp,
				par->lcd_hdisp + par->lcd_right_margin,
				par->lcd_hdisp + par->lcd_right_margin
					+ par->lcd_hsync_dly + par->lcd_hsync_len,
				par->lcd_htotal,
				par->lcd_vdisp,
				par->lcd_vdisp + par->lcd_lower_margin,
				par->lcd_vdisp + par->lcd_lower_margin + par->lcd_vsync_len,
				par->lcd_vtotal);
			PRINTKI("                          : %d %d %d %d %d %d %d %d %d\n",
				par->lcd_pixघड़ी,
				par->lcd_hblank_len - (par->lcd_right_margin +
					par->lcd_hsync_dly + par->lcd_hsync_len),
				par->lcd_hdisp,
				par->lcd_right_margin,
				par->lcd_hsync_len,
				par->lcd_vblank_len - (par->lcd_lower_margin + par->lcd_vsync_len),
				par->lcd_vdisp,
				par->lcd_lower_margin,
				par->lcd_vsync_len);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY_GENERIC_LCD */

अटल पूर्णांक init_from_bios(काष्ठा atyfb_par *par)
अणु
	u32 bios_base, rom_addr;
	पूर्णांक ret;

	rom_addr = 0xc0000 + ((aty_ld_le32(SCRATCH_REG1, par) & 0x7f) << 11);
	bios_base = (अचिन्हित दीर्घ)ioremap(rom_addr, 0x10000);

	/* The BIOS starts with 0xaa55. */
	अगर (*((u16 *)bios_base) == 0xaa55) अणु

		u8 *bios_ptr;
		u16 rom_table_offset, freq_table_offset;
		PLL_BLOCK_MACH64 pll_block;

		PRINTKI("Mach64 BIOS is located at %x, mapped at %x.\n", rom_addr, bios_base);

		/* check क्रम frequncy table */
		bios_ptr = (u8*)bios_base;
		rom_table_offset = (u16)(bios_ptr[0x48] | (bios_ptr[0x49] << 8));
		freq_table_offset = bios_ptr[rom_table_offset + 16] | (bios_ptr[rom_table_offset + 17] << 8);
		स_नकल(&pll_block, bios_ptr + freq_table_offset, माप(PLL_BLOCK_MACH64));

		PRINTKI("BIOS frequency table:\n");
		PRINTKI("PCLK_min_freq %d, PCLK_max_freq %d, ref_freq %d, ref_divider %d\n",
			pll_block.PCLK_min_freq, pll_block.PCLK_max_freq,
			pll_block.ref_freq, pll_block.ref_भागider);
		PRINTKI("MCLK_pwd %d, MCLK_max_freq %d, XCLK_max_freq %d, SCLK_freq %d\n",
			pll_block.MCLK_pwd, pll_block.MCLK_max_freq,
			pll_block.XCLK_max_freq, pll_block.SCLK_freq);

		par->pll_limits.pll_min = pll_block.PCLK_min_freq/100;
		par->pll_limits.pll_max = pll_block.PCLK_max_freq/100;
		par->pll_limits.ref_clk = pll_block.ref_freq/100;
		par->pll_limits.ref_भाग = pll_block.ref_भागider;
		par->pll_limits.sclk = pll_block.SCLK_freq/100;
		par->pll_limits.mclk = pll_block.MCLK_max_freq/100;
		par->pll_limits.mclk_pm = pll_block.MCLK_pwd/100;
		par->pll_limits.xclk = pll_block.XCLK_max_freq/100;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
		aty_init_lcd(par, bios_base);
#पूर्ण_अगर
		ret = 0;
	पूर्ण अन्यथा अणु
		PRINTKE("no BIOS frequency table found, use parameters\n");
		ret = -ENXIO;
	पूर्ण
	iounmap((व्योम __iomem *)bios_base);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* __i386__ */

अटल पूर्णांक atyfb_setup_generic(काष्ठा pci_dev *pdev, काष्ठा fb_info *info,
			       अचिन्हित दीर्घ addr)
अणु
	काष्ठा atyfb_par *par = info->par;
	u16 पंचांगp;
	अचिन्हित दीर्घ raddr;
	काष्ठा resource *rrp;
	पूर्णांक ret = 0;

	raddr = addr + 0x7ff000UL;
	rrp = &pdev->resource[2];
	अगर ((rrp->flags & IORESOURCE_MEM) &&
	    request_mem_region(rrp->start, resource_size(rrp), "atyfb")) अणु
		par->aux_start = rrp->start;
		par->aux_size = resource_size(rrp);
		raddr = rrp->start;
		PRINTKI("using auxiliary register aperture\n");
	पूर्ण

	info->fix.mmio_start = raddr;
	/*
	 * By using strong UC we क्रमce the MTRR to never have an
	 * effect on the MMIO region on both non-PAT and PAT प्रणालीs.
	 */
	par->ati_regbase = ioremap_uc(info->fix.mmio_start, 0x1000);
	अगर (par->ati_regbase == शून्य)
		वापस -ENOMEM;

	info->fix.mmio_start += par->aux_start ? 0x400 : 0xc00;
	par->ati_regbase += par->aux_start ? 0x400 : 0xc00;

	/*
	 * Enable memory-space accesses using config-space
	 * command रेजिस्टर.
	 */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &पंचांगp);
	अगर (!(पंचांगp & PCI_COMMAND_MEMORY)) अणु
		पंचांगp |= PCI_COMMAND_MEMORY;
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, पंचांगp);
	पूर्ण
#अगर_घोषित __BIG_ENDIAN
	/* Use the big-endian aperture */
	addr += 0x800000;
#पूर्ण_अगर

	/* Map in frame buffer */
	info->fix.smem_start = addr;

	/*
	 * The framebuffer is not always 8 MiB, that's just the size of the
	 * PCI BAR. We temporarily abuse smem_len here to store the size
	 * of the BAR. aty_init() will later correct it to match the actual
	 * framebuffer size.
	 *
	 * On devices that करोn't have the auxiliary रेजिस्टर aperture, the
	 * रेजिस्टरs are housed at the top end of the framebuffer PCI BAR.
	 * aty_fudge_framebuffer_len() is used to reduce smem_len to not
	 * overlap with the रेजिस्टरs.
	 */
	info->fix.smem_len = 0x800000;

	aty_fudge_framebuffer_len(info);

	info->screen_base = ioremap_wc(info->fix.smem_start,
				       info->fix.smem_len);
	अगर (info->screen_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ atyfb_setup_generic_fail;
	पूर्ण

	ret = correct_chipset(par);
	अगर (ret)
		जाओ atyfb_setup_generic_fail;
#अगर_घोषित __i386__
	ret = init_from_bios(par);
	अगर (ret)
		जाओ atyfb_setup_generic_fail;
#पूर्ण_अगर
	अगर (!(aty_ld_le32(CRTC_GEN_CNTL, par) & CRTC_EXT_DISP_EN))
		par->clk_wr_offset = (inb(R_GENMO) & 0x0CU) >> 2;
	अन्यथा
		par->clk_wr_offset = aty_ld_8(CLOCK_CNTL, par) & 0x03U;

	/* according to ATI, we should use घड़ी 3 क्रम acelerated mode */
	par->clk_wr_offset = 3;

	वापस 0;

atyfb_setup_generic_fail:
	iounmap(par->ati_regbase);
	par->ati_regbase = शून्य;
	अगर (info->screen_base) अणु
		iounmap(info->screen_base);
		info->screen_base = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

#पूर्ण_अगर /* !__sparc__ */

अटल पूर्णांक atyfb_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ addr, res_start, res_size;
	काष्ठा fb_info *info;
	काष्ठा resource *rp;
	काष्ठा atyfb_par *par;
	पूर्णांक rc = -ENOMEM;

	/* Enable device in PCI config */
	अगर (pci_enable_device(pdev)) अणु
		PRINTKE("Cannot enable PCI device\n");
		वापस -ENXIO;
	पूर्ण

	/* Find which resource to use */
	rp = &pdev->resource[0];
	अगर (rp->flags & IORESOURCE_IO)
		rp = &pdev->resource[1];
	addr = rp->start;
	अगर (!addr)
		वापस -ENXIO;

	/* Reserve space */
	res_start = rp->start;
	res_size = resource_size(rp);
	अगर (!request_mem_region(res_start, res_size, "atyfb"))
		वापस -EBUSY;

	/* Allocate framebuffer */
	info = framebuffer_alloc(माप(काष्ठा atyfb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->bus_type = PCI;
	info->fix = atyfb_fix;
	info->device = &pdev->dev;
	par->pci_id = pdev->device;
	par->res_start = res_start;
	par->res_size = res_size;
	par->irq = pdev->irq;
	par->pdev = pdev;

	/* Setup "info" काष्ठाure */
#अगर_घोषित __sparc__
	rc = atyfb_setup_sparc(pdev, info, addr);
#अन्यथा
	rc = atyfb_setup_generic(pdev, info, addr);
#पूर्ण_अगर
	अगर (rc)
		जाओ err_release_mem;

	pci_set_drvdata(pdev, info);

	/* Init chip & रेजिस्टर framebuffer */
	rc = aty_init(info);
	अगर (rc)
		जाओ err_release_io;

#अगर_घोषित __sparc__
	/*
	 * Add /dev/fb mmap values.
	 */
	par->mmap_map[0].voff = 0x8000000000000000UL;
	par->mmap_map[0].poff = (अचिन्हित दीर्घ) info->screen_base & PAGE_MASK;
	par->mmap_map[0].size = info->fix.smem_len;
	par->mmap_map[0].prot_mask = _PAGE_CACHE;
	par->mmap_map[0].prot_flag = _PAGE_E;
	par->mmap_map[1].voff = par->mmap_map[0].voff + info->fix.smem_len;
	par->mmap_map[1].poff = (दीर्घ)par->ati_regbase & PAGE_MASK;
	par->mmap_map[1].size = PAGE_SIZE;
	par->mmap_map[1].prot_mask = _PAGE_CACHE;
	par->mmap_map[1].prot_flag = _PAGE_E;
#पूर्ण_अगर /* __sparc__ */

	mutex_lock(&reboot_lock);
	अगर (!reboot_info)
		reboot_info = info;
	mutex_unlock(&reboot_lock);

	वापस 0;

err_release_io:
#अगर_घोषित __sparc__
	kमुक्त(par->mmap_map);
#अन्यथा
	अगर (par->ati_regbase)
		iounmap(par->ati_regbase);
	अगर (info->screen_base)
		iounmap(info->screen_base);
#पूर्ण_अगर
err_release_mem:
	अगर (par->aux_start)
		release_mem_region(par->aux_start, par->aux_size);

	release_mem_region(par->res_start, par->res_size);
	framebuffer_release(info);

	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_ATARI

अटल पूर्णांक __init atyfb_atari_probe(व्योम)
अणु
	काष्ठा atyfb_par *par;
	काष्ठा fb_info *info;
	पूर्णांक m64_num;
	u32 घड़ी_r;
	पूर्णांक num_found = 0;

	क्रम (m64_num = 0; m64_num < mach64_count; m64_num++) अणु
		अगर (!phys_vmembase[m64_num] || !phys_size[m64_num] ||
		    !phys_guiregbase[m64_num]) अणु
			PRINTKI("phys_*[%d] parameters not set => "
				"returning early. \n", m64_num);
			जारी;
		पूर्ण

		info = framebuffer_alloc(माप(काष्ठा atyfb_par), शून्य);
		अगर (!info)
			वापस -ENOMEM;

		par = info->par;

		info->fix = atyfb_fix;

		par->irq = (अचिन्हित पूर्णांक) -1; /* something invalid */

		/*
		 * Map the video memory (physical address given)
		 * to somewhere in the kernel address space.
		 */
		info->screen_base = ioremap_wc(phys_vmembase[m64_num],
					       phys_size[m64_num]);
		info->fix.smem_start = (अचिन्हित दीर्घ)info->screen_base; /* Fake! */
		par->ati_regbase = ioremap(phys_guiregbase[m64_num], 0x10000) +
						0xFC00ul;
		info->fix.mmio_start = (अचिन्हित दीर्घ)par->ati_regbase; /* Fake! */

		aty_st_le32(CLOCK_CNTL, 0x12345678, par);
		घड़ी_r = aty_ld_le32(CLOCK_CNTL, par);

		चयन (घड़ी_r & 0x003F) अणु
		हाल 0x12:
			par->clk_wr_offset = 3; /*  */
			अवरोध;
		हाल 0x34:
			par->clk_wr_offset = 2; /* Medusa ST-IO ISA Adapter etc. */
			अवरोध;
		हाल 0x16:
			par->clk_wr_offset = 1; /*  */
			अवरोध;
		हाल 0x38:
			par->clk_wr_offset = 0; /* Panther 1 ISA Adapter (Gerald) */
			अवरोध;
		पूर्ण

		/* Fake pci_id क्रम correct_chipset() */
		चयन (aty_ld_le32(CNFG_CHIP_ID, par) & CFG_CHIP_TYPE) अणु
		हाल 0x00d7:
			par->pci_id = PCI_CHIP_MACH64GX;
			अवरोध;
		हाल 0x0057:
			par->pci_id = PCI_CHIP_MACH64CX;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (correct_chipset(par) || aty_init(info)) अणु
			iounmap(info->screen_base);
			iounmap(par->ati_regbase);
			framebuffer_release(info);
		पूर्ण अन्यथा अणु
			num_found++;
		पूर्ण
	पूर्ण

	वापस num_found ? 0 : -ENXIO;
पूर्ण

#पूर्ण_अगर /* CONFIG_ATARI */

#अगर_घोषित CONFIG_PCI

अटल व्योम atyfb_हटाओ(काष्ठा fb_info *info)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	/* restore video mode */
	aty_set_crtc(par, &par->saved_crtc);
	par->pll_ops->set_pll(info, &par->saved_pll);

	unरेजिस्टर_framebuffer(info);

#अगर_घोषित CONFIG_FB_ATY_BACKLIGHT
	अगर (M64_HAS(MOBIL_BUS))
		aty_bl_निकास(info->bl_dev);
#पूर्ण_अगर
	arch_phys_wc_del(par->wc_cookie);

#अगर_अघोषित __sparc__
	अगर (par->ati_regbase)
		iounmap(par->ati_regbase);
	अगर (info->screen_base)
		iounmap(info->screen_base);
#अगर_घोषित __BIG_ENDIAN
	अगर (info->sprite.addr)
		iounmap(info->sprite.addr);
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित __sparc__
	kमुक्त(par->mmap_map);
#पूर्ण_अगर
	अगर (par->aux_start)
		release_mem_region(par->aux_start, par->aux_size);

	अगर (par->res_start)
		release_mem_region(par->res_start, par->res_size);

	framebuffer_release(info);
पूर्ण


अटल व्योम atyfb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);

	mutex_lock(&reboot_lock);
	अगर (reboot_info == info)
		reboot_info = शून्य;
	mutex_unlock(&reboot_lock);

	atyfb_हटाओ(info);
पूर्ण

अटल स्थिर काष्ठा pci_device_id atyfb_pci_tbl[] = अणु
#अगर_घोषित CONFIG_FB_ATY_GX
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GX) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64CX) पूर्ण,
#पूर्ण_अगर /* CONFIG_FB_ATY_GX */

#अगर_घोषित CONFIG_FB_ATY_CT
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64CT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64ET) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LT) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64VT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GT) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64VU) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GU) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LG) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64VV) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GV) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GW) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GY) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GZ) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GB) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GD) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GI) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GP) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GQ) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LB) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LD) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LI) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LP) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LQ) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GM) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GN) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GO) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GL) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GR) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64GS) पूर्ण,

	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LM) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LN) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LR) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_CHIP_MACH64LS) पूर्ण,
#पूर्ण_अगर /* CONFIG_FB_ATY_CT */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, atyfb_pci_tbl);

अटल काष्ठा pci_driver atyfb_driver = अणु
	.name		= "atyfb",
	.id_table	= atyfb_pci_tbl,
	.probe		= atyfb_pci_probe,
	.हटाओ		= atyfb_pci_हटाओ,
	.driver.pm	= &atyfb_pci_pm_ops,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PCI */

#अगर_अघोषित MODULE
अटल पूर्णांक __init atyfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "noaccel", 7)) अणु
			noaccel = true;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6)) अणु
			nomtrr = true;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "vram:", 5))
			vram = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "pll:", 4))
			pll = simple_म_से_अदीर्घ(this_opt + 4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "mclk:", 5))
			mclk = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "xclk:", 5))
			xclk = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "comp_sync:", 10))
			comp_sync = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "backlight:", 10))
			backlight = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
#अगर_घोषित CONFIG_PPC
		अन्यथा अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
			अचिन्हित पूर्णांक vmode =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				शेष_vmode = vmode;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			अचिन्हित पूर्णांक cmode =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
			चयन (cmode) अणु
			हाल 0:
			हाल 8:
				शेष_cmode = CMODE_8;
				अवरोध;
			हाल 15:
			हाल 16:
				शेष_cmode = CMODE_16;
				अवरोध;
			हाल 24:
			हाल 32:
				शेष_cmode = CMODE_32;
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI
		/*
		 * Why करो we need this silly Mach64 argument?
		 * We are alपढ़ोy here because of mach64= so its redundant.
		 */
		अन्यथा अगर (MACH_IS_ATARI
			 && (!म_भेदन(this_opt, "Mach64:", 7))) अणु
			अटल अचिन्हित अक्षर m64_num;
			अटल अक्षर mach64_str[80];
			strlcpy(mach64_str, this_opt + 7, माप(mach64_str));
			अगर (!store_video_par(mach64_str, m64_num)) अणु
				m64_num++;
				mach64_count = m64_num;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अन्यथा
			mode = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

अटल पूर्णांक atyfb_reboot_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा atyfb_par *par;

	अगर (code != SYS_RESTART)
		वापस NOTIFY_DONE;

	mutex_lock(&reboot_lock);

	अगर (!reboot_info)
		जाओ out;

	lock_fb_info(reboot_info);

	par = reboot_info->par;

	/*
	 * HP OmniBook 500's BIOS doesn't like the state of the
	 * hardware after atyfb has been used. Restore the hardware
	 * to the original state to allow successful reboots.
	 */
	aty_set_crtc(par, &par->saved_crtc);
	par->pll_ops->set_pll(reboot_info, &par->saved_pll);

	unlock_fb_info(reboot_info);
 out:
	mutex_unlock(&reboot_lock);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block atyfb_reboot_notअगरier = अणु
	.notअगरier_call = atyfb_reboot_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id atyfb_reboot_ids[] __initस्थिर = अणु
	अणु
		.ident = "HP OmniBook 500",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP OmniBook PC"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "HP OmniBook 500 FA"),
		पूर्ण,
	पूर्ण,

	अणु पूर्ण
पूर्ण;
अटल bool रेजिस्टरed_notअगरier = false;

अटल पूर्णांक __init atyfb_init(व्योम)
अणु
	पूर्णांक err1 = 1, err2 = 1;
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("atyfb", &option))
		वापस -ENODEV;
	atyfb_setup(option);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
	err1 = pci_रेजिस्टर_driver(&atyfb_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI
	err2 = atyfb_atari_probe();
#पूर्ण_अगर

	अगर (err1 && err2)
		वापस -ENODEV;

	अगर (dmi_check_प्रणाली(atyfb_reboot_ids)) अणु
		रेजिस्टर_reboot_notअगरier(&atyfb_reboot_notअगरier);
		रेजिस्टरed_notअगरier = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास atyfb_निकास(व्योम)
अणु
	अगर (रेजिस्टरed_notअगरier)
		unरेजिस्टर_reboot_notअगरier(&atyfb_reboot_notअगरier);

#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&atyfb_driver);
#पूर्ण_अगर
पूर्ण

module_init(atyfb_init);
module_निकास(atyfb_निकास);

MODULE_DESCRIPTION("FBDev driver for ATI Mach64 cards");
MODULE_LICENSE("GPL");
module_param(noaccel, bool, 0);
MODULE_PARM_DESC(noaccel, "bool: disable acceleration");
module_param(vram, पूर्णांक, 0);
MODULE_PARM_DESC(vram, "int: override size of video ram");
module_param(pll, पूर्णांक, 0);
MODULE_PARM_DESC(pll, "int: override video clock");
module_param(mclk, पूर्णांक, 0);
MODULE_PARM_DESC(mclk, "int: override memory clock");
module_param(xclk, पूर्णांक, 0);
MODULE_PARM_DESC(xclk, "int: override accelerated engine clock");
module_param(comp_sync, पूर्णांक, 0);
MODULE_PARM_DESC(comp_sync, "Set composite sync signal to low (0) or high (1)");
module_param(mode, अक्षरp, 0);
MODULE_PARM_DESC(mode, "Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\" ");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "bool: disable use of MTRR registers");
