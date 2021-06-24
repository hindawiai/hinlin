<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* $Id: aty128fb.c,v 1.1.1.1.36.1 1999/12/11 09:03:05 Exp $
 *  linux/drivers/video/aty128fb.c -- Frame buffer device क्रम ATI Rage128
 *
 *  Copyright (C) 1999-2003, Brad Douglas <brad@neruo.com>
 *  Copyright (C) 1999, Anthony Tong <atong@uiuc.edu>
 *
 *                Ani Joshi / Jeff Garzik
 *                      - Code cleanup
 *
 *                Michel Danzer <michdaen@iiic.ethz.ch>
 *                      - 15/16 bit cleanup
 *                      - fix panning
 *
 *                Benjamin Herrenschmidt
 *                      - pmac-specअगरic PM stuff
 *			- various fixes & cleanups
 *
 *                Andreas Hundt <andi@convergence.de>
 *                      - FB_ACTIVATE fixes
 *
 *		  Paul Mackerras <paulus@samba.org>
 *			- Convert to new framebuffer API,
 *			  fix colormap setting at 16 bits/pixel (565)
 *
 *		  Paul Mundt 
 *		  	- PCI hotplug
 *
 *		  Jon Smirl <jonsmirl@yahoo.com>
 * 			- PCI ID update
 * 			- replace ROM BIOS search
 *
 *  Based off of Geert's atyfb.c and vfb.c.
 *
 *  TODO:
 *		- monitor sensing (DDC)
 *              - भव display
 *		- other platक्रमm support (only ppc/x86 supported)
 *		- hardware cursor support
 *
 *    Please cc: your patches to brad@neruo.com.
 */

/*
 * A special note of gratitude to ATI's devrel क्रम providing करोcumentation,
 * example code and hardware. Thanks Nitya.	-atong and brad
 */


#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
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
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/console.h>
#समावेश <linux/backlight.h>
#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/prom.h>
#समावेश "../macmodes.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOTX_TEXT
#समावेश <यंत्र/btext.h>
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

#समावेश <video/aty128.h>

/* Debug flag */
#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, args...) \
	prपूर्णांकk(KERN_DEBUG "aty128fb: %s " fmt, __func__, ##args);
#अन्यथा
#घोषणा DBG(fmt, args...)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PPC_PMAC
/* शेष mode */
अटल स्थिर काष्ठा fb_var_screeninfo शेष_var = अणु
	/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz करोtघड़ी) */
	640, 480, 640, 480, 0, 0, 8, 0,
	अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण,
	0, 0, -1, -1, 0, 39722, 48, 16, 33, 10, 96, 2,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

#अन्यथा /* CONFIG_PPC_PMAC */
/* शेष to 1024x768 at 75Hz on PPC - this will work
 * on the iMac, the usual 640x480 @ 60Hz करोesn't. */
अटल स्थिर काष्ठा fb_var_screeninfo शेष_var = अणु
	/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz करोtघड़ी) */
	1024, 768, 1024, 768, 0, 0, 8, 0,
	अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण,
	0, 0, -1, -1, 0, 12699, 160, 32, 28, 1, 96, 3,
	FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	FB_VMODE_NONINTERLACED
पूर्ण;
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

/* शेष modedb mode */
/* 640x480, 60 Hz, Non-Interlaced (25.172 MHz करोtघड़ी) */
अटल स्थिर काष्ठा fb_videomode शेषmode = अणु
	.refresh =	60,
	.xres =		640,
	.yres =		480,
	.pixघड़ी =	39722,
	.left_margin =	48,
	.right_margin =	16,
	.upper_margin =	33,
	.lower_margin =	10,
	.hsync_len =	96,
	.vsync_len =	2,
	.sync =		0,
	.vmode =	FB_VMODE_NONINTERLACED
पूर्ण;

/* Chip generations */
क्रमागत अणु
	rage_128,
	rage_128_pci,
	rage_128_pro,
	rage_128_pro_pci,
	rage_M3,
	rage_M3_pci,
	rage_M4,
	rage_128_ultra,
पूर्ण;

/* Must match above क्रमागत */
अटल अक्षर * स्थिर r128_family[] = अणु
	"AGP",
	"PCI",
	"PRO AGP",
	"PRO PCI",
	"M3 AGP",
	"M3 PCI",
	"M4 AGP",
	"Ultra AGP",
पूर्ण;

/*
 * PCI driver prototypes
 */
अटल पूर्णांक aty128_probe(काष्ठा pci_dev *pdev,
                               स्थिर काष्ठा pci_device_id *ent);
अटल व्योम aty128_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक aty128_pci_suspend_late(काष्ठा device *dev, pm_message_t state);
अटल पूर्णांक __maybe_unused aty128_pci_suspend(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused aty128_pci_hibernate(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused aty128_pci_मुक्तze(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused aty128_pci_resume(काष्ठा device *dev);
अटल पूर्णांक aty128_करो_resume(काष्ठा pci_dev *pdev);

अटल स्थिर काष्ठा dev_pm_ops aty128_pci_pm_ops = अणु
	.suspend	= aty128_pci_suspend,
	.resume		= aty128_pci_resume,
	.मुक्तze		= aty128_pci_मुक्तze,
	.thaw		= aty128_pci_resume,
	.घातeroff	= aty128_pci_hibernate,
	.restore	= aty128_pci_resume,
पूर्ण;

/* supported Rage128 chipsets */
अटल स्थिर काष्ठा pci_device_id aty128_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_LE,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_M3_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_LF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_M3 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_MF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_M4 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_ML,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_M4 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PA,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PB,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PD,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PE,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PG,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PH,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PI,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PJ,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PK,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PN,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PQ,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PS,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PT,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PU,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PV,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_PX,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pro पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_RE,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_RF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_RG,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_RK,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_RL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SE,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_pci पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SG,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SH,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SK,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_SN,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128 पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TF,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TS,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TT,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RAGE128_TU,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, rage_128_ultra पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, aty128_pci_tbl);

अटल काष्ठा pci_driver aty128fb_driver = अणु
	.name		= "aty128fb",
	.id_table	= aty128_pci_tbl,
	.probe		= aty128_probe,
	.हटाओ		= aty128_हटाओ,
	.driver.pm	= &aty128_pci_pm_ops,
पूर्ण;

/* packed BIOS settings */
#अगर_अघोषित CONFIG_PPC
प्रकार काष्ठा अणु
	u8 घड़ी_chip_type;
	u8 काष्ठा_size;
	u8 accelerator_entry;
	u8 VGA_entry;
	u16 VGA_table_offset;
	u16 POST_table_offset;
	u16 XCLK;
	u16 MCLK;
	u8 num_PLL_blocks;
	u8 size_PLL_blocks;
	u16 PCLK_ref_freq;
	u16 PCLK_ref_भागider;
	u32 PCLK_min_freq;
	u32 PCLK_max_freq;
	u16 MCLK_ref_freq;
	u16 MCLK_ref_भागider;
	u32 MCLK_min_freq;
	u32 MCLK_max_freq;
	u16 XCLK_ref_freq;
	u16 XCLK_ref_भागider;
	u32 XCLK_min_freq;
	u32 XCLK_max_freq;
पूर्ण __attribute__ ((packed)) PLL_BLOCK;
#पूर्ण_अगर /* !CONFIG_PPC */

/* onboard memory inक्रमmation */
काष्ठा aty128_meminfo अणु
	u8 ML;
	u8 MB;
	u8 Trcd;
	u8 Trp;
	u8 Twr;
	u8 CL;
	u8 Tr2w;
	u8 LoopLatency;
	u8 DspOn;
	u8 Rloop;
	स्थिर अक्षर *name;
पूर्ण;

/* various memory configurations */
अटल स्थिर काष्ठा aty128_meminfo sdr_128 = अणु
	.ML = 4,
	.MB = 4,
	.Trcd = 3,
	.Trp = 3,
	.Twr = 1,
	.CL = 3,
	.Tr2w = 1,
	.LoopLatency = 16,
	.DspOn = 30,
	.Rloop = 16,
	.name = "128-bit SDR SGRAM (1:1)",
पूर्ण;

अटल स्थिर काष्ठा aty128_meminfo sdr_sgram = अणु
	.ML = 4,
	.MB = 4,
	.Trcd = 1,
	.Trp = 2,
	.Twr = 1,
	.CL = 2,
	.Tr2w = 1,
	.LoopLatency = 16,
	.DspOn = 24,
	.Rloop = 16,
	.name = "64-bit SDR SGRAM (2:1)",
पूर्ण;

अटल स्थिर काष्ठा aty128_meminfo ddr_sgram = अणु
	.ML = 4,
	.MB = 4,
	.Trcd = 3,
	.Trp = 3,
	.Twr = 2,
	.CL = 3,
	.Tr2w = 1,
	.LoopLatency = 16,
	.DspOn = 31,
	.Rloop = 16,
	.name = "64-bit DDR SGRAM",
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo aty128fb_fix = अणु
	.id		= "ATY Rage128",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.xpanstep	= 8,
	.ypanstep	= 1,
	.mmio_len	= 0x2000,
	.accel		= FB_ACCEL_ATI_RAGE128,
पूर्ण;

अटल अक्षर *mode_option = शून्य;

#अगर_घोषित CONFIG_PPC_PMAC
अटल पूर्णांक शेष_vmode = VMODE_1024_768_60;
अटल पूर्णांक शेष_cmode = CMODE_8;
#पूर्ण_अगर

अटल पूर्णांक शेष_crt_on = 0;
अटल पूर्णांक शेष_lcd_on = 1;
अटल bool mtrr = true;

#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
अटल पूर्णांक backlight = IS_BUILTIN(CONFIG_PMAC_BACKLIGHT);
#पूर्ण_अगर

/* PLL स्थिरants */
काष्ठा aty128_स्थिरants अणु
	u32 ref_clk;
	u32 ppll_min;
	u32 ppll_max;
	u32 ref_भागider;
	u32 xclk;
	u32 fअगरo_width;
	u32 fअगरo_depth;
पूर्ण;

काष्ठा aty128_crtc अणु
	u32 gen_cntl;
	u32 h_total, h_sync_strt_wid;
	u32 v_total, v_sync_strt_wid;
	u32 pitch;
	u32 offset, offset_cntl;
	u32 xoffset, yoffset;
	u32 vxres, vyres;
	u32 depth, bpp;
पूर्ण;

काष्ठा aty128_pll अणु
	u32 post_भागider;
	u32 feedback_भागider;
	u32 vclk;
पूर्ण;

काष्ठा aty128_ddafअगरo अणु
	u32 dda_config;
	u32 dda_on_off;
पूर्ण;

/* रेजिस्टर values क्रम a specअगरic mode */
काष्ठा aty128fb_par अणु
	काष्ठा aty128_crtc crtc;
	काष्ठा aty128_pll pll;
	काष्ठा aty128_ddafअगरo fअगरo_reg;
	u32 accel_flags;
	काष्ठा aty128_स्थिरants स्थिरants;  /* PLL and others      */
	व्योम __iomem *regbase;              /* remapped mmio       */
	u32 vram_size;                      /* onboard video ram   */
	पूर्णांक chip_gen;
	स्थिर काष्ठा aty128_meminfo *mem;   /* onboard mem info    */
	पूर्णांक wc_cookie;
	पूर्णांक blitter_may_be_busy;
	पूर्णांक fअगरo_slots;                 /* मुक्त slots in FIFO (64 max) */

	पूर्णांक crt_on, lcd_on;
	काष्ठा pci_dev *pdev;
	काष्ठा fb_info *next;
	पूर्णांक	asleep;
	पूर्णांक	lock_blank;

	u8	red[32];		/* see aty128fb_setcolreg */
	u8	green[64];
	u8	blue[32];
	u32	pseuकरो_palette[16];	/* used क्रम TRUECOLOR */
पूर्ण;


#घोषणा round_भाग(n, d) ((n+(d/2))/d)

अटल पूर्णांक aty128fb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info);
अटल पूर्णांक aty128fb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक aty128fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			      u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक aty128fb_pan_display(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *fb);
अटल पूर्णांक aty128fb_blank(पूर्णांक blank, काष्ठा fb_info *fb);
अटल पूर्णांक aty128fb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक aty128fb_sync(काष्ठा fb_info *info);

    /*
     *  Internal routines
     */

अटल पूर्णांक aty128_encode_var(काष्ठा fb_var_screeninfo *var,
                             स्थिर काष्ठा aty128fb_par *par);
अटल पूर्णांक aty128_decode_var(काष्ठा fb_var_screeninfo *var,
                             काष्ठा aty128fb_par *par);
अटल व्योम aty128_timings(काष्ठा aty128fb_par *par);
अटल व्योम aty128_init_engine(काष्ठा aty128fb_par *par);
अटल व्योम aty128_reset_engine(स्थिर काष्ठा aty128fb_par *par);
अटल व्योम aty128_flush_pixel_cache(स्थिर काष्ठा aty128fb_par *par);
अटल व्योम करो_रुको_क्रम_fअगरo(u16 entries, काष्ठा aty128fb_par *par);
अटल व्योम रुको_क्रम_fअगरo(u16 entries, काष्ठा aty128fb_par *par);
अटल व्योम रुको_क्रम_idle(काष्ठा aty128fb_par *par);
अटल u32 depth_to_dst(u32 depth);

#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
अटल व्योम aty128_bl_set_घातer(काष्ठा fb_info *info, पूर्णांक घातer);
#पूर्ण_अगर

#घोषणा BIOS_IN8(v)  	(पढ़ोb(bios + (v)))
#घोषणा BIOS_IN16(v) 	(पढ़ोb(bios + (v)) | \
			  (पढ़ोb(bios + (v) + 1) << 8))
#घोषणा BIOS_IN32(v) 	(पढ़ोb(bios + (v)) | \
			  (पढ़ोb(bios + (v) + 1) << 8) | \
			  (पढ़ोb(bios + (v) + 2) << 16) | \
			  (पढ़ोb(bios + (v) + 3) << 24))


अटल स्थिर काष्ठा fb_ops aty128fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= aty128fb_check_var,
	.fb_set_par	= aty128fb_set_par,
	.fb_setcolreg	= aty128fb_setcolreg,
	.fb_pan_display = aty128fb_pan_display,
	.fb_blank	= aty128fb_blank,
	.fb_ioctl	= aty128fb_ioctl,
	.fb_sync	= aty128fb_sync,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

    /*
     * Functions to पढ़ो from/ग_लिखो to the mmio रेजिस्टरs
     *	- endian conversions may possibly be aव्योमed by
     *    using the other रेजिस्टर aperture. TODO.
     */
अटल अंतरभूत u32 _aty_ld_le32(अस्थिर अचिन्हित पूर्णांक regindex, 
			       स्थिर काष्ठा aty128fb_par *par)
अणु
	वापस पढ़ोl (par->regbase + regindex);
पूर्ण

अटल अंतरभूत व्योम _aty_st_le32(अस्थिर अचिन्हित पूर्णांक regindex, u32 val, 
				स्थिर काष्ठा aty128fb_par *par)
अणु
	ग_लिखोl (val, par->regbase + regindex);
पूर्ण

अटल अंतरभूत u8 _aty_ld_8(अचिन्हित पूर्णांक regindex,
			   स्थिर काष्ठा aty128fb_par *par)
अणु
	वापस पढ़ोb (par->regbase + regindex);
पूर्ण

अटल अंतरभूत व्योम _aty_st_8(अचिन्हित पूर्णांक regindex, u8 val,
			     स्थिर काष्ठा aty128fb_par *par)
अणु
	ग_लिखोb (val, par->regbase + regindex);
पूर्ण

#घोषणा aty_ld_le32(regindex)		_aty_ld_le32(regindex, par)
#घोषणा aty_st_le32(regindex, val)	_aty_st_le32(regindex, val, par)
#घोषणा aty_ld_8(regindex)		_aty_ld_8(regindex, par)
#घोषणा aty_st_8(regindex, val)		_aty_st_8(regindex, val, par)

    /*
     * Functions to पढ़ो from/ग_लिखो to the pll रेजिस्टरs
     */

#घोषणा aty_ld_pll(pll_index)		_aty_ld_pll(pll_index, par)
#घोषणा aty_st_pll(pll_index, val)	_aty_st_pll(pll_index, val, par)


अटल u32 _aty_ld_pll(अचिन्हित पूर्णांक pll_index,
		       स्थिर काष्ठा aty128fb_par *par)
अणु       
	aty_st_8(CLOCK_CNTL_INDEX, pll_index & 0x3F);
	वापस aty_ld_le32(CLOCK_CNTL_DATA);
पूर्ण

    
अटल व्योम _aty_st_pll(अचिन्हित पूर्णांक pll_index, u32 val,
			स्थिर काष्ठा aty128fb_par *par)
अणु
	aty_st_8(CLOCK_CNTL_INDEX, (pll_index & 0x3F) | PLL_WR_EN);
	aty_st_le32(CLOCK_CNTL_DATA, val);
पूर्ण


/* वापस true when the PLL has completed an atomic update */
अटल पूर्णांक aty_pll_पढ़ोupdate(स्थिर काष्ठा aty128fb_par *par)
अणु
	वापस !(aty_ld_pll(PPLL_REF_DIV) & PPLL_ATOMIC_UPDATE_R);
पूर्ण


अटल व्योम aty_pll_रुको_पढ़ोupdate(स्थिर काष्ठा aty128fb_par *par)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ/100; // should be more than enough
	पूर्णांक reset = 1;

	जबतक (समय_beक्रमe(jअगरfies, समयout))
		अगर (aty_pll_पढ़ोupdate(par)) अणु
			reset = 0;
			अवरोध;
		पूर्ण

	अगर (reset)	/* reset engine?? */
		prपूर्णांकk(KERN_DEBUG "aty128fb: PLL write timeout!\n");
पूर्ण


/* tell PLL to update */
अटल व्योम aty_pll_ग_लिखोupdate(स्थिर काष्ठा aty128fb_par *par)
अणु
	aty_pll_रुको_पढ़ोupdate(par);

	aty_st_pll(PPLL_REF_DIV,
		   aty_ld_pll(PPLL_REF_DIV) | PPLL_ATOMIC_UPDATE_W);
पूर्ण


/* ग_लिखो to the scratch रेजिस्टर to test r/w functionality */
अटल पूर्णांक रेजिस्टर_test(स्थिर काष्ठा aty128fb_par *par)
अणु
	u32 val;
	पूर्णांक flag = 0;

	val = aty_ld_le32(BIOS_0_SCRATCH);

	aty_st_le32(BIOS_0_SCRATCH, 0x55555555);
	अगर (aty_ld_le32(BIOS_0_SCRATCH) == 0x55555555) अणु
		aty_st_le32(BIOS_0_SCRATCH, 0xAAAAAAAA);

		अगर (aty_ld_le32(BIOS_0_SCRATCH) == 0xAAAAAAAA)
			flag = 1; 
	पूर्ण

	aty_st_le32(BIOS_0_SCRATCH, val);	// restore value
	वापस flag;
पूर्ण


/*
 * Accelerator engine functions
 */
अटल व्योम करो_रुको_क्रम_fअगरo(u16 entries, काष्ठा aty128fb_par *par)
अणु
	पूर्णांक i;

	क्रम (;;) अणु
		क्रम (i = 0; i < 2000000; i++) अणु
			par->fअगरo_slots = aty_ld_le32(GUI_STAT) & 0x0fff;
			अगर (par->fअगरo_slots >= entries)
				वापस;
		पूर्ण
		aty128_reset_engine(par);
	पूर्ण
पूर्ण


अटल व्योम रुको_क्रम_idle(काष्ठा aty128fb_par *par)
अणु
	पूर्णांक i;

	करो_रुको_क्रम_fअगरo(64, par);

	क्रम (;;) अणु
		क्रम (i = 0; i < 2000000; i++) अणु
			अगर (!(aty_ld_le32(GUI_STAT) & (1 << 31))) अणु
				aty128_flush_pixel_cache(par);
				par->blitter_may_be_busy = 0;
				वापस;
			पूर्ण
		पूर्ण
		aty128_reset_engine(par);
	पूर्ण
पूर्ण


अटल व्योम रुको_क्रम_fअगरo(u16 entries, काष्ठा aty128fb_par *par)
अणु
	अगर (par->fअगरo_slots < entries)
		करो_रुको_क्रम_fअगरo(64, par);
	par->fअगरo_slots -= entries;
पूर्ण


अटल व्योम aty128_flush_pixel_cache(स्थिर काष्ठा aty128fb_par *par)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	पंचांगp = aty_ld_le32(PC_NGUI_CTLSTAT);
	पंचांगp &= ~(0x00ff);
	पंचांगp |= 0x00ff;
	aty_st_le32(PC_NGUI_CTLSTAT, पंचांगp);

	क्रम (i = 0; i < 2000000; i++)
		अगर (!(aty_ld_le32(PC_NGUI_CTLSTAT) & PC_BUSY))
			अवरोध;
पूर्ण


अटल व्योम aty128_reset_engine(स्थिर काष्ठा aty128fb_par *par)
अणु
	u32 gen_reset_cntl, घड़ी_cntl_index, mclk_cntl;

	aty128_flush_pixel_cache(par);

	घड़ी_cntl_index = aty_ld_le32(CLOCK_CNTL_INDEX);
	mclk_cntl = aty_ld_pll(MCLK_CNTL);

	aty_st_pll(MCLK_CNTL, mclk_cntl | 0x00030000);

	gen_reset_cntl = aty_ld_le32(GEN_RESET_CNTL);
	aty_st_le32(GEN_RESET_CNTL, gen_reset_cntl | SOFT_RESET_GUI);
	aty_ld_le32(GEN_RESET_CNTL);
	aty_st_le32(GEN_RESET_CNTL, gen_reset_cntl & ~(SOFT_RESET_GUI));
	aty_ld_le32(GEN_RESET_CNTL);

	aty_st_pll(MCLK_CNTL, mclk_cntl);
	aty_st_le32(CLOCK_CNTL_INDEX, घड़ी_cntl_index);
	aty_st_le32(GEN_RESET_CNTL, gen_reset_cntl);

	/* use old pio mode */
	aty_st_le32(PM4_BUFFER_CNTL, PM4_BUFFER_CNTL_NONPM4);

	DBG("engine reset");
पूर्ण


अटल व्योम aty128_init_engine(काष्ठा aty128fb_par *par)
अणु
	u32 pitch_value;

	रुको_क्रम_idle(par);

	/* 3D scaler not spoken here */
	रुको_क्रम_fअगरo(1, par);
	aty_st_le32(SCALE_3D_CNTL, 0x00000000);

	aty128_reset_engine(par);

	pitch_value = par->crtc.pitch;
	अगर (par->crtc.bpp == 24) अणु
		pitch_value = pitch_value * 3;
	पूर्ण

	रुको_क्रम_fअगरo(4, par);
	/* setup engine offset रेजिस्टरs */
	aty_st_le32(DEFAULT_OFFSET, 0x00000000);

	/* setup engine pitch रेजिस्टरs */
	aty_st_le32(DEFAULT_PITCH, pitch_value);

	/* set the शेष scissor रेजिस्टर to max dimensions */
	aty_st_le32(DEFAULT_SC_BOTTOM_RIGHT, (0x1FFF << 16) | 0x1FFF);

	/* set the drawing controls रेजिस्टरs */
	aty_st_le32(DP_GUI_MASTER_CNTL,
		    GMC_SRC_PITCH_OFFSET_DEFAULT		|
		    GMC_DST_PITCH_OFFSET_DEFAULT		|
		    GMC_SRC_CLIP_DEFAULT			|
		    GMC_DST_CLIP_DEFAULT			|
		    GMC_BRUSH_SOLIDCOLOR			|
		    (depth_to_dst(par->crtc.depth) << 8)	|
		    GMC_SRC_DSTCOLOR			|
		    GMC_BYTE_ORDER_MSB_TO_LSB		|
		    GMC_DP_CONVERSION_TEMP_6500		|
		    ROP3_PATCOPY				|
		    GMC_DP_SRC_RECT				|
		    GMC_3D_FCN_EN_CLR			|
		    GMC_DST_CLR_CMP_FCN_CLEAR		|
		    GMC_AUX_CLIP_CLEAR			|
		    GMC_WRITE_MASK_SET);

	रुको_क्रम_fअगरo(8, par);
	/* clear the line drawing रेजिस्टरs */
	aty_st_le32(DST_BRES_ERR, 0);
	aty_st_le32(DST_BRES_INC, 0);
	aty_st_le32(DST_BRES_DEC, 0);

	/* set brush color रेजिस्टरs */
	aty_st_le32(DP_BRUSH_FRGD_CLR, 0xFFFFFFFF); /* white */
	aty_st_le32(DP_BRUSH_BKGD_CLR, 0x00000000); /* black */

	/* set source color रेजिस्टरs */
	aty_st_le32(DP_SRC_FRGD_CLR, 0xFFFFFFFF);   /* white */
	aty_st_le32(DP_SRC_BKGD_CLR, 0x00000000);   /* black */

	/* शेष ग_लिखो mask */
	aty_st_le32(DP_WRITE_MASK, 0xFFFFFFFF);

	/* Wait क्रम all the ग_लिखोs to be completed beक्रमe वापसing */
	रुको_क्रम_idle(par);
पूर्ण


/* convert depth values to their रेजिस्टर representation */
अटल u32 depth_to_dst(u32 depth)
अणु
	अगर (depth <= 8)
		वापस DST_8BPP;
	अन्यथा अगर (depth <= 15)
		वापस DST_15BPP;
	अन्यथा अगर (depth == 16)
		वापस DST_16BPP;
	अन्यथा अगर (depth <= 24)
		वापस DST_24BPP;
	अन्यथा अगर (depth <= 32)
		वापस DST_32BPP;

	वापस -EINVAL;
पूर्ण

/*
 * PLL inक्रमmations retreival
 */


#अगर_अघोषित __sparc__
अटल व्योम __iomem *aty128_map_ROM(स्थिर काष्ठा aty128fb_par *par,
				    काष्ठा pci_dev *dev)
अणु
	u16 dptr;
	u8 rom_type;
	व्योम __iomem *bios;
	माप_प्रकार rom_size;

    	/* Fix from ATI क्रम problem with Rage128 hardware not leaving ROM enabled */
    	अचिन्हित पूर्णांक temp;
	temp = aty_ld_le32(RAGE128_MPP_TB_CONFIG);
	temp &= 0x00ffffffu;
	temp |= 0x04 << 24;
	aty_st_le32(RAGE128_MPP_TB_CONFIG, temp);
	temp = aty_ld_le32(RAGE128_MPP_TB_CONFIG);

	bios = pci_map_rom(dev, &rom_size);

	अगर (!bios) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: ROM failed to map\n");
		वापस शून्य;
	पूर्ण

	/* Very simple test to make sure it appeared */
	अगर (BIOS_IN16(0) != 0xaa55) अणु
		prपूर्णांकk(KERN_DEBUG "aty128fb: Invalid ROM signature %x should "
			" be 0xaa55\n", BIOS_IN16(0));
		जाओ failed;
	पूर्ण

	/* Look क्रम the PCI data to check the ROM type */
	dptr = BIOS_IN16(0x18);

	/* Check the PCI data signature. If it's wrong, we still assume a normal
	 * x86 ROM क्रम now, until I've verअगरied this works everywhere.
	 * The goal here is more to phase out Open Firmware images.
	 *
	 * Currently, we only look at the first PCI data, we could iteratre and
	 * deal with them all, and we should use fb_bios_start relative to start
	 * of image and not relative start of ROM, but so far, I never found a
	 * dual-image ATI card.
	 *
	 * प्रकार काष्ठा अणु
	 * 	u32	signature;	+ 0x00
	 * 	u16	venकरोr;		+ 0x04
	 * 	u16	device;		+ 0x06
	 * 	u16	reserved_1;	+ 0x08
	 * 	u16	dlen;		+ 0x0a
	 * 	u8	drevision;	+ 0x0c
	 * 	u8	class_hi;	+ 0x0d
	 * 	u16	class_lo;	+ 0x0e
	 * 	u16	ilen;		+ 0x10
	 * 	u16	irevision;	+ 0x12
	 * 	u8	type;		+ 0x14
	 * 	u8	indicator;	+ 0x15
	 * 	u16	reserved_2;	+ 0x16
	 * पूर्ण pci_data_t;
	 */
	अगर (BIOS_IN32(dptr) !=  (('R' << 24) | ('I' << 16) | ('C' << 8) | 'P')) अणु
		prपूर्णांकk(KERN_WARNING "aty128fb: PCI DATA signature in ROM incorrect: %08x\n",
		       BIOS_IN32(dptr));
		जाओ anyway;
	पूर्ण
	rom_type = BIOS_IN8(dptr + 0x14);
	चयन(rom_type) अणु
	हाल 0:
		prपूर्णांकk(KERN_INFO "aty128fb: Found Intel x86 BIOS ROM Image\n");
		अवरोध;
	हाल 1:
		prपूर्णांकk(KERN_INFO "aty128fb: Found Open Firmware ROM Image\n");
		जाओ failed;
	हाल 2:
		prपूर्णांकk(KERN_INFO "aty128fb: Found HP PA-RISC ROM Image\n");
		जाओ failed;
	शेष:
		prपूर्णांकk(KERN_INFO "aty128fb: Found unknown type %d ROM Image\n",
		       rom_type);
		जाओ failed;
	पूर्ण
 anyway:
	वापस bios;

 failed:
	pci_unmap_rom(dev, bios);
	वापस शून्य;
पूर्ण

अटल व्योम aty128_get_pllinfo(काष्ठा aty128fb_par *par,
			       अचिन्हित अक्षर __iomem *bios)
अणु
	अचिन्हित पूर्णांक bios_hdr;
	अचिन्हित पूर्णांक bios_pll;

	bios_hdr = BIOS_IN16(0x48);
	bios_pll = BIOS_IN16(bios_hdr + 0x30);
	
	par->स्थिरants.ppll_max = BIOS_IN32(bios_pll + 0x16);
	par->स्थिरants.ppll_min = BIOS_IN32(bios_pll + 0x12);
	par->स्थिरants.xclk = BIOS_IN16(bios_pll + 0x08);
	par->स्थिरants.ref_भागider = BIOS_IN16(bios_pll + 0x10);
	par->स्थिरants.ref_clk = BIOS_IN16(bios_pll + 0x0e);

	DBG("ppll_max %d ppll_min %d xclk %d ref_divider %d ref clock %d\n",
			par->स्थिरants.ppll_max, par->स्थिरants.ppll_min,
			par->स्थिरants.xclk, par->स्थिरants.ref_भागider,
			par->स्थिरants.ref_clk);

पूर्ण           

#अगर_घोषित CONFIG_X86
अटल व्योम __iomem *aty128_find_mem_vbios(काष्ठा aty128fb_par *par)
अणु
	/* I simplअगरied this code as we used to miss the signatures in
	 * a lot of हाल. It's now closer to XFree, we just don't check
	 * क्रम signatures at all... Something better will have to be करोne
	 * अगर we end up having conflicts
	 */
        u32  segstart;
        अचिन्हित अक्षर __iomem *rom_base = शून्य;
                                                
        क्रम (segstart=0x000c0000; segstart<0x000f0000; segstart+=0x00001000) अणु
                rom_base = ioremap(segstart, 0x10000);
		अगर (rom_base == शून्य)
			वापस शून्य;
		अगर (पढ़ोb(rom_base) == 0x55 && पढ़ोb(rom_base + 1) == 0xaa)
	                अवरोध;
                iounmap(rom_base);
		rom_base = शून्य;
        पूर्ण
	वापस rom_base;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* ndef(__sparc__) */

/* fill in known card स्थिरants अगर pll_block is not available */
अटल व्योम aty128_timings(काष्ठा aty128fb_par *par)
अणु
#अगर_घोषित CONFIG_PPC
	/* instead of a table lookup, assume OF has properly
	 * setup the PLL रेजिस्टरs and use their values
	 * to set the XCLK values and reference भागider values */

	u32 x_mpll_ref_fb_भाग;
	u32 xclk_cntl;
	u32 Nx, M;
	अचिन्हित PostDivSet[] = अणु 0, 1, 2, 4, 8, 3, 6, 12 पूर्ण;
#पूर्ण_अगर

	अगर (!par->स्थिरants.ref_clk)
		par->स्थिरants.ref_clk = 2950;

#अगर_घोषित CONFIG_PPC
	x_mpll_ref_fb_भाग = aty_ld_pll(X_MPLL_REF_FB_DIV);
	xclk_cntl = aty_ld_pll(XCLK_CNTL) & 0x7;
	Nx = (x_mpll_ref_fb_भाग & 0x00ff00) >> 8;
	M  = x_mpll_ref_fb_भाग & 0x0000ff;

	par->स्थिरants.xclk = round_भाग((2 * Nx * par->स्थिरants.ref_clk),
					(M * PostDivSet[xclk_cntl]));

	par->स्थिरants.ref_भागider =
		aty_ld_pll(PPLL_REF_DIV) & PPLL_REF_DIV_MASK;
#पूर्ण_अगर

	अगर (!par->स्थिरants.ref_भागider) अणु
		par->स्थिरants.ref_भागider = 0x3b;

		aty_st_pll(X_MPLL_REF_FB_DIV, 0x004c4c1e);
		aty_pll_ग_लिखोupdate(par);
	पूर्ण
	aty_st_pll(PPLL_REF_DIV, par->स्थिरants.ref_भागider);
	aty_pll_ग_लिखोupdate(par);

	/* from करोcumentation */
	अगर (!par->स्थिरants.ppll_min)
		par->स्थिरants.ppll_min = 12500;
	अगर (!par->स्थिरants.ppll_max)
		par->स्थिरants.ppll_max = 25000;    /* 23000 on some cards? */
	अगर (!par->स्थिरants.xclk)
		par->स्थिरants.xclk = 0x1d4d;	     /* same as mclk */

	par->स्थिरants.fअगरo_width = 128;
	par->स्थिरants.fअगरo_depth = 32;

	चयन (aty_ld_le32(MEM_CNTL) & 0x3) अणु
	हाल 0:
		par->mem = &sdr_128;
		अवरोध;
	हाल 1:
		par->mem = &sdr_sgram;
		अवरोध;
	हाल 2:
		par->mem = &ddr_sgram;
		अवरोध;
	शेष:
		par->mem = &sdr_sgram;
	पूर्ण
पूर्ण



/*
 * CRTC programming
 */

/* Program the CRTC रेजिस्टरs */
अटल व्योम aty128_set_crtc(स्थिर काष्ठा aty128_crtc *crtc,
			    स्थिर काष्ठा aty128fb_par *par)
अणु
	aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl);
	aty_st_le32(CRTC_H_TOTAL_DISP, crtc->h_total);
	aty_st_le32(CRTC_H_SYNC_STRT_WID, crtc->h_sync_strt_wid);
	aty_st_le32(CRTC_V_TOTAL_DISP, crtc->v_total);
	aty_st_le32(CRTC_V_SYNC_STRT_WID, crtc->v_sync_strt_wid);
	aty_st_le32(CRTC_PITCH, crtc->pitch);
	aty_st_le32(CRTC_OFFSET, crtc->offset);
	aty_st_le32(CRTC_OFFSET_CNTL, crtc->offset_cntl);
	/* Disable ATOMIC updating.  Is this the right place? */
	aty_st_pll(PPLL_CNTL, aty_ld_pll(PPLL_CNTL) & ~(0x00030000));
पूर्ण


अटल पूर्णांक aty128_var_to_crtc(स्थिर काष्ठा fb_var_screeninfo *var,
			      काष्ठा aty128_crtc *crtc,
			      स्थिर काष्ठा aty128fb_par *par)
अणु
	u32 xres, yres, vxres, vyres, xoffset, yoffset, bpp, dst;
	u32 left, right, upper, lower, hslen, vslen, sync, vmode;
	u32 h_total, h_disp, h_sync_strt, h_sync_wid, h_sync_pol;
	u32 v_total, v_disp, v_sync_strt, v_sync_wid, v_sync_pol, c_sync;
	u32 depth, bytpp;
	u8 mode_bytpp[7] = अणु 0, 0, 1, 2, 2, 3, 4 पूर्ण;

	/* input */
	xres = var->xres;
	yres = var->yres;
	vxres   = var->xres_भव;
	vyres   = var->yres_भव;
	xoffset = var->xoffset;
	yoffset = var->yoffset;
	bpp   = var->bits_per_pixel;
	left  = var->left_margin;
	right = var->right_margin;
	upper = var->upper_margin;
	lower = var->lower_margin;
	hslen = var->hsync_len;
	vslen = var->vsync_len;
	sync  = var->sync;
	vmode = var->vmode;

	अगर (bpp != 16)
		depth = bpp;
	अन्यथा
		depth = (var->green.length == 6) ? 16 : 15;

	/* check क्रम mode eligibility
	 * accept only non पूर्णांकerlaced modes */
	अगर ((vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

	/* convert (and round up) and validate */
	xres = (xres + 7) & ~7;
	xoffset = (xoffset + 7) & ~7;

	अगर (vxres < xres + xoffset)
		vxres = xres + xoffset;

	अगर (vyres < yres + yoffset)
		vyres = yres + yoffset;

	/* convert depth पूर्णांकo ATI रेजिस्टर depth */
	dst = depth_to_dst(depth);

	अगर (dst == -EINVAL) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Invalid depth or RGBA\n");
		वापस -EINVAL;
	पूर्ण

	/* convert रेजिस्टर depth to bytes per pixel */
	bytpp = mode_bytpp[dst];

	/* make sure there is enough video ram क्रम the mode */
	अगर ((u32)(vxres * vyres * bytpp) > par->vram_size) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Not enough memory for mode\n");
		वापस -EINVAL;
	पूर्ण

	h_disp = (xres >> 3) - 1;
	h_total = (((xres + right + hslen + left) >> 3) - 1) & 0xFFFFL;

	v_disp = yres - 1;
	v_total = (yres + upper + vslen + lower - 1) & 0xFFFFL;

	/* check to make sure h_total and v_total are in range */
	अगर (((h_total >> 3) - 1) > 0x1ff || (v_total - 1) > 0x7FF) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: invalid width ranges\n");
		वापस -EINVAL;
	पूर्ण

	h_sync_wid = (hslen + 7) >> 3;
	अगर (h_sync_wid == 0)
		h_sync_wid = 1;
	अन्यथा अगर (h_sync_wid > 0x3f)        /* 0x3f = max hwidth */
		h_sync_wid = 0x3f;

	h_sync_strt = (h_disp << 3) + right;

	v_sync_wid = vslen;
	अगर (v_sync_wid == 0)
		v_sync_wid = 1;
	अन्यथा अगर (v_sync_wid > 0x1f)        /* 0x1f = max vwidth */
		v_sync_wid = 0x1f;
    
	v_sync_strt = v_disp + lower;

	h_sync_pol = sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	v_sync_pol = sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;
    
	c_sync = sync & FB_SYNC_COMP_HIGH_ACT ? (1 << 4) : 0;

	crtc->gen_cntl = 0x3000000L | c_sync | (dst << 8);

	crtc->h_total = h_total | (h_disp << 16);
	crtc->v_total = v_total | (v_disp << 16);

	crtc->h_sync_strt_wid = h_sync_strt | (h_sync_wid << 16) |
	        (h_sync_pol << 23);
	crtc->v_sync_strt_wid = v_sync_strt | (v_sync_wid << 16) |
                (v_sync_pol << 23);

	crtc->pitch = vxres >> 3;

	crtc->offset = 0;

	अगर ((var->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		crtc->offset_cntl = 0x00010000;
	अन्यथा
		crtc->offset_cntl = 0;

	crtc->vxres = vxres;
	crtc->vyres = vyres;
	crtc->xoffset = xoffset;
	crtc->yoffset = yoffset;
	crtc->depth = depth;
	crtc->bpp = bpp;

	वापस 0;
पूर्ण


अटल पूर्णांक aty128_pix_width_to_var(पूर्णांक pix_width, काष्ठा fb_var_screeninfo *var)
अणु

	/* fill in pixel info */
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.offset = 0;
	var->blue.msb_right = 0;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	चयन (pix_width) अणु
	हाल CRTC_PIX_WIDTH_8BPP:
		var->bits_per_pixel = 8;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल CRTC_PIX_WIDTH_15BPP:
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.length = 5;
		अवरोध;
	हाल CRTC_PIX_WIDTH_16BPP:
		var->bits_per_pixel = 16;
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;
	हाल CRTC_PIX_WIDTH_24BPP:
		var->bits_per_pixel = 24;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल CRTC_PIX_WIDTH_32BPP:
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "aty128fb: Invalid pixel width\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक aty128_crtc_to_var(स्थिर काष्ठा aty128_crtc *crtc,
			      काष्ठा fb_var_screeninfo *var)
अणु
	u32 xres, yres, left, right, upper, lower, hslen, vslen, sync;
	u32 h_total, h_disp, h_sync_strt, h_sync_dly, h_sync_wid, h_sync_pol;
	u32 v_total, v_disp, v_sync_strt, v_sync_wid, v_sync_pol, c_sync;
	u32 pix_width;

	/* fun with masking */
	h_total     = crtc->h_total & 0x1ff;
	h_disp      = (crtc->h_total >> 16) & 0xff;
	h_sync_strt = (crtc->h_sync_strt_wid >> 3) & 0x1ff;
	h_sync_dly  = crtc->h_sync_strt_wid & 0x7;
	h_sync_wid  = (crtc->h_sync_strt_wid >> 16) & 0x3f;
	h_sync_pol  = (crtc->h_sync_strt_wid >> 23) & 0x1;
	v_total     = crtc->v_total & 0x7ff;
	v_disp      = (crtc->v_total >> 16) & 0x7ff;
	v_sync_strt = crtc->v_sync_strt_wid & 0x7ff;
	v_sync_wid  = (crtc->v_sync_strt_wid >> 16) & 0x1f;
	v_sync_pol  = (crtc->v_sync_strt_wid >> 23) & 0x1;
	c_sync      = crtc->gen_cntl & CRTC_CSYNC_EN ? 1 : 0;
	pix_width   = crtc->gen_cntl & CRTC_PIX_WIDTH_MASK;

	/* करो conversions */
	xres  = (h_disp + 1) << 3;
	yres  = v_disp + 1;
	left  = ((h_total - h_sync_strt - h_sync_wid) << 3) - h_sync_dly;
	right = ((h_sync_strt - h_disp) << 3) + h_sync_dly;
	hslen = h_sync_wid << 3;
	upper = v_total - v_sync_strt - v_sync_wid;
	lower = v_sync_strt - v_disp;
	vslen = v_sync_wid;
	sync  = (h_sync_pol ? 0 : FB_SYNC_HOR_HIGH_ACT) |
		(v_sync_pol ? 0 : FB_SYNC_VERT_HIGH_ACT) |
		(c_sync ? FB_SYNC_COMP_HIGH_ACT : 0);

	aty128_pix_width_to_var(pix_width, var);

	var->xres = xres;
	var->yres = yres;
	var->xres_भव = crtc->vxres;
	var->yres_भव = crtc->vyres;
	var->xoffset = crtc->xoffset;
	var->yoffset = crtc->yoffset;
	var->left_margin  = left;
	var->right_margin = right;
	var->upper_margin = upper;
	var->lower_margin = lower;
	var->hsync_len = hslen;
	var->vsync_len = vslen;
	var->sync  = sync;
	var->vmode = FB_VMODE_NONINTERLACED;

	वापस 0;
पूर्ण

अटल व्योम aty128_set_crt_enable(काष्ठा aty128fb_par *par, पूर्णांक on)
अणु
	अगर (on) अणु
		aty_st_le32(CRTC_EXT_CNTL, aty_ld_le32(CRTC_EXT_CNTL) |
			    CRT_CRTC_ON);
		aty_st_le32(DAC_CNTL, (aty_ld_le32(DAC_CNTL) |
			    DAC_PALETTE2_SNOOP_EN));
	पूर्ण अन्यथा
		aty_st_le32(CRTC_EXT_CNTL, aty_ld_le32(CRTC_EXT_CNTL) &
			    ~CRT_CRTC_ON);
पूर्ण

अटल व्योम aty128_set_lcd_enable(काष्ठा aty128fb_par *par, पूर्णांक on)
अणु
	u32 reg;
#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
#पूर्ण_अगर

	अगर (on) अणु
		reg = aty_ld_le32(LVDS_GEN_CNTL);
		reg |= LVDS_ON | LVDS_EN | LVDS_BLON | LVDS_DIGION;
		reg &= ~LVDS_DISPLAY_DIS;
		aty_st_le32(LVDS_GEN_CNTL, reg);
#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
		aty128_bl_set_घातer(info, FB_BLANK_UNBLANK);
#पूर्ण_अगर	
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
		aty128_bl_set_घातer(info, FB_BLANK_POWERDOWN);
#पूर्ण_अगर	
		reg = aty_ld_le32(LVDS_GEN_CNTL);
		reg |= LVDS_DISPLAY_DIS;
		aty_st_le32(LVDS_GEN_CNTL, reg);
		mdelay(100);
		reg &= ~(LVDS_ON /*| LVDS_EN*/);
		aty_st_le32(LVDS_GEN_CNTL, reg);
	पूर्ण
पूर्ण

अटल व्योम aty128_set_pll(काष्ठा aty128_pll *pll,
			   स्थिर काष्ठा aty128fb_par *par)
अणु
	u32 भाग3;

	अचिन्हित अक्षर post_conv[] =	/* रेजिस्टर values क्रम post भागiders */
        अणु 2, 0, 1, 4, 2, 2, 6, 2, 3, 2, 2, 2, 7 पूर्ण;

	/* select PPLL_DIV_3 */
	aty_st_le32(CLOCK_CNTL_INDEX, aty_ld_le32(CLOCK_CNTL_INDEX) | (3 << 8));

	/* reset PLL */
	aty_st_pll(PPLL_CNTL,
		   aty_ld_pll(PPLL_CNTL) | PPLL_RESET | PPLL_ATOMIC_UPDATE_EN);

	/* ग_लिखो the reference भागider */
	aty_pll_रुको_पढ़ोupdate(par);
	aty_st_pll(PPLL_REF_DIV, par->स्थिरants.ref_भागider & 0x3ff);
	aty_pll_ग_लिखोupdate(par);

	भाग3 = aty_ld_pll(PPLL_DIV_3);
	भाग3 &= ~PPLL_FB3_DIV_MASK;
	भाग3 |= pll->feedback_भागider;
	भाग3 &= ~PPLL_POST3_DIV_MASK;
	भाग3 |= post_conv[pll->post_भागider] << 16;

	/* ग_लिखो feedback and post भागiders */
	aty_pll_रुको_पढ़ोupdate(par);
	aty_st_pll(PPLL_DIV_3, भाग3);
	aty_pll_ग_लिखोupdate(par);

	aty_pll_रुको_पढ़ोupdate(par);
	aty_st_pll(HTOTAL_CNTL, 0);	/* no horiz crtc adjusपंचांगent */
	aty_pll_ग_लिखोupdate(par);

	/* clear the reset, just in हाल */
	aty_st_pll(PPLL_CNTL, aty_ld_pll(PPLL_CNTL) & ~PPLL_RESET);
पूर्ण


अटल पूर्णांक aty128_var_to_pll(u32 period_in_ps, काष्ठा aty128_pll *pll,
			     स्थिर काष्ठा aty128fb_par *par)
अणु
	स्थिर काष्ठा aty128_स्थिरants c = par->स्थिरants;
	अचिन्हित अक्षर post_भागiders[] = अणु1,2,4,8,3,6,12पूर्ण;
	u32 output_freq;
	u32 vclk;        /* in .01 MHz */
	पूर्णांक i = 0;
	u32 n, d;

	vclk = 100000000 / period_in_ps;	/* convert units to 10 kHz */

	/* adjust pixel घड़ी अगर necessary */
	अगर (vclk > c.ppll_max)
		vclk = c.ppll_max;
	अगर (vclk * 12 < c.ppll_min)
		vclk = c.ppll_min/12;

	/* now, find an acceptable भागider */
	क्रम (i = 0; i < ARRAY_SIZE(post_भागiders); i++) अणु
		output_freq = post_भागiders[i] * vclk;
		अगर (output_freq >= c.ppll_min && output_freq <= c.ppll_max) अणु
			pll->post_भागider = post_भागiders[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(post_भागiders))
		वापस -EINVAL;

	/* calculate feedback भागider */
	n = c.ref_भागider * output_freq;
	d = c.ref_clk;

	pll->feedback_भागider = round_भाग(n, d);
	pll->vclk = vclk;

	DBG("post %d feedback %d vlck %d output %d ref_divider %d "
	    "vclk_per: %d\n", pll->post_भागider,
	    pll->feedback_भागider, vclk, output_freq,
	    c.ref_भागider, period_in_ps);

	वापस 0;
पूर्ण


अटल पूर्णांक aty128_pll_to_var(स्थिर काष्ठा aty128_pll *pll,
			     काष्ठा fb_var_screeninfo *var)
अणु
	var->pixघड़ी = 100000000 / pll->vclk;

	वापस 0;
पूर्ण


अटल व्योम aty128_set_fअगरo(स्थिर काष्ठा aty128_ddafअगरo *dsp,
			    स्थिर काष्ठा aty128fb_par *par)
अणु
	aty_st_le32(DDA_CONFIG, dsp->dda_config);
	aty_st_le32(DDA_ON_OFF, dsp->dda_on_off);
पूर्ण


अटल पूर्णांक aty128_ddafअगरo(काष्ठा aty128_ddafअगरo *dsp,
			  स्थिर काष्ठा aty128_pll *pll,
			  u32 depth,
			  स्थिर काष्ठा aty128fb_par *par)
अणु
	स्थिर काष्ठा aty128_meminfo *m = par->mem;
	u32 xclk = par->स्थिरants.xclk;
	u32 fअगरo_width = par->स्थिरants.fअगरo_width;
	u32 fअगरo_depth = par->स्थिरants.fअगरo_depth;
	s32 x, b, p, ron, roff;
	u32 n, d, bpp;

	/* round up to multiple of 8 */
	bpp = (depth+7) & ~7;

	n = xclk * fअगरo_width;
	d = pll->vclk * bpp;
	x = round_भाग(n, d);

	ron = 4 * m->MB +
		3 * ((m->Trcd - 2 > 0) ? m->Trcd - 2 : 0) +
		2 * m->Trp +
		m->Twr +
		m->CL +
		m->Tr2w +
		x;

	DBG("x %x\n", x);

	b = 0;
	जबतक (x) अणु
		x >>= 1;
		b++;
	पूर्ण
	p = b + 1;

	ron <<= (11 - p);

	n <<= (11 - p);
	x = round_भाग(n, d);
	roff = x * (fअगरo_depth - 4);

	अगर ((ron + m->Rloop) >= roff) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Mode out of range!\n");
		वापस -EINVAL;
	पूर्ण

	DBG("p: %x rloop: %x x: %x ron: %x roff: %x\n",
	    p, m->Rloop, x, ron, roff);

	dsp->dda_config = p << 16 | m->Rloop << 20 | x;
	dsp->dda_on_off = ron << 16 | roff;

	वापस 0;
पूर्ण


/*
 * This actually sets the video mode.
 */
अटल पूर्णांक aty128fb_set_par(काष्ठा fb_info *info)
अणु 
	काष्ठा aty128fb_par *par = info->par;
	u32 config;
	पूर्णांक err;

	अगर ((err = aty128_decode_var(&info->var, par)) != 0)
		वापस err;

	अगर (par->blitter_may_be_busy)
		रुको_क्रम_idle(par);

	/* clear all रेजिस्टरs that may पूर्णांकerfere with mode setting */
	aty_st_le32(OVR_CLR, 0);
	aty_st_le32(OVR_WID_LEFT_RIGHT, 0);
	aty_st_le32(OVR_WID_TOP_BOTTOM, 0);
	aty_st_le32(OV0_SCALE_CNTL, 0);
	aty_st_le32(MPP_TB_CONFIG, 0);
	aty_st_le32(MPP_GP_CONFIG, 0);
	aty_st_le32(SUBPIC_CNTL, 0);
	aty_st_le32(VIPH_CONTROL, 0);
	aty_st_le32(I2C_CNTL_1, 0);         /* turn off i2c */
	aty_st_le32(GEN_INT_CNTL, 0);	/* turn off पूर्णांकerrupts */
	aty_st_le32(CAP0_TRIG_CNTL, 0);
	aty_st_le32(CAP1_TRIG_CNTL, 0);

	aty_st_8(CRTC_EXT_CNTL + 1, 4);	/* turn video off */

	aty128_set_crtc(&par->crtc, par);
	aty128_set_pll(&par->pll, par);
	aty128_set_fअगरo(&par->fअगरo_reg, par);

	config = aty_ld_le32(CNFG_CNTL) & ~3;

#अगर defined(__BIG_ENDIAN)
	अगर (par->crtc.bpp == 32)
		config |= 2;	/* make aperture करो 32 bit swapping */
	अन्यथा अगर (par->crtc.bpp == 16)
		config |= 1;	/* make aperture करो 16 bit swapping */
#पूर्ण_अगर

	aty_st_le32(CNFG_CNTL, config);
	aty_st_8(CRTC_EXT_CNTL + 1, 0);	/* turn the video back on */

	info->fix.line_length = (par->crtc.vxres * par->crtc.bpp) >> 3;
	info->fix.visual = par->crtc.bpp == 8 ? FB_VISUAL_PSEUDOCOLOR
		: FB_VISUAL_सूचीECTCOLOR;

	अगर (par->chip_gen == rage_M3) अणु
		aty128_set_crt_enable(par, par->crt_on);
		aty128_set_lcd_enable(par, par->lcd_on);
	पूर्ण
	अगर (par->accel_flags & FB_ACCELF_TEXT)
		aty128_init_engine(par);

#अगर_घोषित CONFIG_BOOTX_TEXT
	btext_update_display(info->fix.smem_start,
			     (((par->crtc.h_total>>16) & 0xff)+1)*8,
			     ((par->crtc.v_total>>16) & 0x7ff)+1,
			     par->crtc.bpp,
			     par->crtc.vxres*par->crtc.bpp/8);
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

	वापस 0;
पूर्ण

/*
 *  encode/decode the User Defined Part of the Display
 */

अटल पूर्णांक aty128_decode_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा aty128fb_par *par)
अणु
	पूर्णांक err;
	काष्ठा aty128_crtc crtc;
	काष्ठा aty128_pll pll;
	काष्ठा aty128_ddafअगरo fअगरo_reg;

	अगर ((err = aty128_var_to_crtc(var, &crtc, par)))
		वापस err;

	अगर ((err = aty128_var_to_pll(var->pixघड़ी, &pll, par)))
		वापस err;

	अगर ((err = aty128_ddafअगरo(&fअगरo_reg, &pll, crtc.depth, par)))
		वापस err;

	par->crtc = crtc;
	par->pll = pll;
	par->fअगरo_reg = fअगरo_reg;
	par->accel_flags = var->accel_flags;

	वापस 0;
पूर्ण


अटल पूर्णांक aty128_encode_var(काष्ठा fb_var_screeninfo *var,
			     स्थिर काष्ठा aty128fb_par *par)
अणु
	पूर्णांक err;

	अगर ((err = aty128_crtc_to_var(&par->crtc, var)))
		वापस err;

	अगर ((err = aty128_pll_to_var(&par->pll, var)))
		वापस err;

	var->nonstd = 0;
	var->activate = 0;

	var->height = -1;
	var->width = -1;
	var->accel_flags = par->accel_flags;

	वापस 0;
पूर्ण           


अटल पूर्णांक aty128fb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा aty128fb_par par;
	पूर्णांक err;

	par = *(काष्ठा aty128fb_par *)info->par;
	अगर ((err = aty128_decode_var(var, &par)) != 0)
		वापस err;
	aty128_encode_var(var, &par);
	वापस 0;
पूर्ण


/*
 *  Pan or Wrap the Display
 */
अटल पूर्णांक aty128fb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *fb)
अणु
	काष्ठा aty128fb_par *par = fb->par;
	u32 xoffset, yoffset;
	u32 offset;
	u32 xres, yres;

	xres = (((par->crtc.h_total >> 16) & 0xff) + 1) << 3;
	yres = ((par->crtc.v_total >> 16) & 0x7ff) + 1;

	xoffset = (var->xoffset +7) & ~7;
	yoffset = var->yoffset;

	अगर (xoffset+xres > par->crtc.vxres || yoffset+yres > par->crtc.vyres)
		वापस -EINVAL;

	par->crtc.xoffset = xoffset;
	par->crtc.yoffset = yoffset;

	offset = ((yoffset * par->crtc.vxres + xoffset) * (par->crtc.bpp >> 3))
									  & ~7;

	अगर (par->crtc.bpp == 24)
		offset += 8 * (offset % 3); /* Must be multiple of 8 and 3 */

	aty_st_le32(CRTC_OFFSET, offset);

	वापस 0;
पूर्ण


/*
 *  Helper function to store a single palette रेजिस्टर
 */
अटल व्योम aty128_st_pal(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			  काष्ठा aty128fb_par *par)
अणु
	अगर (par->chip_gen == rage_M3) अणु
		aty_st_le32(DAC_CNTL, aty_ld_le32(DAC_CNTL) &
			    ~DAC_PALETTE_ACCESS_CNTL);
	पूर्ण

	aty_st_8(PALETTE_INDEX, regno);
	aty_st_le32(PALETTE_DATA, (red<<16)|(green<<8)|blue);
पूर्ण

अटल पूर्णांक aty128fb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा aty128fb_par *par = info->par;

	अगर (par->blitter_may_be_busy)
		रुको_क्रम_idle(par);
	वापस 0;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक aty128fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "lcd:", 4)) अणु
			शेष_lcd_on = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
			जारी;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "crt:", 4)) अणु
			शेष_crt_on = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
			जारी;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "backlight:", 10)) अणु
#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
			backlight = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
#पूर्ण_अगर
			जारी;
		पूर्ण
		अगर(!म_भेदन(this_opt, "nomtrr", 6)) अणु
			mtrr = false;
			जारी;
		पूर्ण
#अगर_घोषित CONFIG_PPC_PMAC
		/* vmode and cmode deprecated */
		अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
			अचिन्हित पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				शेष_vmode = vmode;
			जारी;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			अचिन्हित पूर्णांक cmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
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
			जारी;
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
		mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

/* Backlight */
#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
#घोषणा MAX_LEVEL 0xFF

अटल पूर्णांक aty128_bl_get_level_brightness(काष्ठा aty128fb_par *par,
		पूर्णांक level)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	पूर्णांक atylevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we पढ़ो a single value */
	atylevel = MAX_LEVEL -
		(info->bl_curve[level] * FB_BACKLIGHT_MAX / MAX_LEVEL);

	अगर (atylevel < 0)
		atylevel = 0;
	अन्यथा अगर (atylevel > MAX_LEVEL)
		atylevel = MAX_LEVEL;

	वापस atylevel;
पूर्ण

/* We turn off the LCD completely instead of just dimming the backlight.
 * This provides greater घातer saving and the display is useless without
 * backlight anyway
 */
#घोषणा BACKLIGHT_LVDS_OFF
/* That one prevents proper CRT output with LCD off */
#अघोषित BACKLIGHT_DAC_OFF

अटल पूर्णांक aty128_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा aty128fb_par *par = bl_get_data(bd);
	अचिन्हित पूर्णांक reg = aty_ld_le32(LVDS_GEN_CNTL);
	पूर्णांक level;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK ||
	    !par->lcd_on)
		level = 0;
	अन्यथा
		level = bd->props.brightness;

	reg |= LVDS_BL_MOD_EN | LVDS_BLON;
	अगर (level > 0) अणु
		reg |= LVDS_DIGION;
		अगर (!(reg & LVDS_ON)) अणु
			reg &= ~LVDS_BLON;
			aty_st_le32(LVDS_GEN_CNTL, reg);
			aty_ld_le32(LVDS_GEN_CNTL);
			mdelay(10);
			reg |= LVDS_BLON;
			aty_st_le32(LVDS_GEN_CNTL, reg);
		पूर्ण
		reg &= ~LVDS_BL_MOD_LEVEL_MASK;
		reg |= (aty128_bl_get_level_brightness(par, level) <<
			LVDS_BL_MOD_LEVEL_SHIFT);
#अगर_घोषित BACKLIGHT_LVDS_OFF
		reg |= LVDS_ON | LVDS_EN;
		reg &= ~LVDS_DISPLAY_DIS;
#पूर्ण_अगर
		aty_st_le32(LVDS_GEN_CNTL, reg);
#अगर_घोषित BACKLIGHT_DAC_OFF
		aty_st_le32(DAC_CNTL, aty_ld_le32(DAC_CNTL) & (~DAC_PDWN));
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		reg &= ~LVDS_BL_MOD_LEVEL_MASK;
		reg |= (aty128_bl_get_level_brightness(par, 0) <<
			LVDS_BL_MOD_LEVEL_SHIFT);
#अगर_घोषित BACKLIGHT_LVDS_OFF
		reg |= LVDS_DISPLAY_DIS;
		aty_st_le32(LVDS_GEN_CNTL, reg);
		aty_ld_le32(LVDS_GEN_CNTL);
		udelay(10);
		reg &= ~(LVDS_ON | LVDS_EN | LVDS_BLON | LVDS_DIGION);
#पूर्ण_अगर
		aty_st_le32(LVDS_GEN_CNTL, reg);
#अगर_घोषित BACKLIGHT_DAC_OFF
		aty_st_le32(DAC_CNTL, aty_ld_le32(DAC_CNTL) | DAC_PDWN);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops aty128_bl_data = अणु
	.update_status	= aty128_bl_update_status,
पूर्ण;

अटल व्योम aty128_bl_set_घातer(काष्ठा fb_info *info, पूर्णांक घातer)
अणु
	अगर (info->bl_dev) अणु
		info->bl_dev->props.घातer = घातer;
		backlight_update_status(info->bl_dev);
	पूर्ण
पूर्ण

अटल व्योम aty128_bl_init(काष्ठा aty128fb_par *par)
अणु
	काष्ठा backlight_properties props;
	काष्ठा fb_info *info = pci_get_drvdata(par->pdev);
	काष्ठा backlight_device *bd;
	अक्षर name[12];

	/* Could be extended to Rage128Pro LVDS output too */
	अगर (par->chip_gen != rage_M3)
		वापस;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!pmac_has_backlight_type("ati"))
		वापस;
#पूर्ण_अगर

	snम_लिखो(name, माप(name), "aty128bl%d", info->node);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, info->dev, par, &aty128_bl_data,
				       &props);
	अगर (IS_ERR(bd)) अणु
		info->bl_dev = शून्य;
		prपूर्णांकk(KERN_WARNING "aty128: Backlight registration failed\n");
		जाओ error;
	पूर्ण

	info->bl_dev = bd;
	fb_bl_शेष_curve(info, 0,
		 63 * FB_BACKLIGHT_MAX / MAX_LEVEL,
		219 * FB_BACKLIGHT_MAX / MAX_LEVEL);

	bd->props.brightness = bd->props.max_brightness;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk("aty128: Backlight initialized (%s)\n", name);

	वापस;

error:
	वापस;
पूर्ण

अटल व्योम aty128_bl_निकास(काष्ठा backlight_device *bd)
अणु
	backlight_device_unरेजिस्टर(bd);
	prपूर्णांकk("aty128: Backlight unloaded\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_ATY128_BACKLIGHT */

/*
 *  Initialisation
 */

#अगर_घोषित CONFIG_PPC_PMAC__disabled
अटल व्योम aty128_early_resume(व्योम *data)
अणु
        काष्ठा aty128fb_par *par = data;

	अगर (!console_trylock())
		वापस;
	pci_restore_state(par->pdev);
	aty128_करो_resume(par->pdev);
	console_unlock();
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

अटल पूर्णांक aty128_init(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा aty128fb_par *par = info->par;
	काष्ठा fb_var_screeninfo var;
	अक्षर video_card[50];
	u8 chip_rev;
	u32 dac;

	/* Get the chip revision */
	chip_rev = (aty_ld_le32(CNFG_CNTL) >> 16) & 0x1F;

	म_नकल(video_card, "Rage128 XX ");
	video_card[8] = ent->device >> 8;
	video_card[9] = ent->device & 0xFF;

	/* range check to make sure */
	अगर (ent->driver_data < ARRAY_SIZE(r128_family))
		strlcat(video_card, r128_family[ent->driver_data],
			माप(video_card));

	prपूर्णांकk(KERN_INFO "aty128fb: %s [chip rev 0x%x] ", video_card, chip_rev);

	अगर (par->vram_size % (1024 * 1024) == 0)
		prपूर्णांकk("%dM %s\n", par->vram_size / (1024*1024), par->mem->name);
	अन्यथा
		prपूर्णांकk("%dk %s\n", par->vram_size / 1024, par->mem->name);

	par->chip_gen = ent->driver_data;

	/* fill in info */
	info->fbops = &aty128fb_ops;
	info->flags = FBINFO_FLAG_DEFAULT;

	par->lcd_on = शेष_lcd_on;
	par->crt_on = शेष_crt_on;

	var = शेष_var;
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (machine_is(घातermac)) अणु
		/* Indicate sleep capability */
		अगर (par->chip_gen == rage_M3) अणु
			pmac_call_feature(PMAC_FTR_DEVICE_CAN_WAKE, शून्य, 0, 1);
#अगर 0 /* Disable the early video resume hack क्रम now as it's causing problems,
       * among others we now rely on the PCI core restoring the config space
       * क्रम us, which isn't the हाल with that hack, and that code path causes
       * various things to be called with पूर्णांकerrupts off जबतक they shouldn't.
       * I'm leaving the code in as it can be useful क्रम debugging purposes
       */
			pmac_set_early_video_resume(aty128_early_resume, par);
#पूर्ण_अगर
		पूर्ण

		/* Find शेष mode */
		अगर (mode_option) अणु
			अगर (!mac_find_mode(&var, info, mode_option, 8))
				var = शेष_var;
		पूर्ण अन्यथा अणु
			अगर (शेष_vmode <= 0 || शेष_vmode > VMODE_MAX)
				शेष_vmode = VMODE_1024_768_60;

			/* iMacs need that resolution
			 * PowerMac2,1 first r128 iMacs
			 * PowerMac2,2 summer 2000 iMacs
			 * PowerMac4,1 january 2001 iMacs "flower power"
			 */
			अगर (of_machine_is_compatible("PowerMac2,1") ||
			    of_machine_is_compatible("PowerMac2,2") ||
			    of_machine_is_compatible("PowerMac4,1"))
				शेष_vmode = VMODE_1024_768_75;

			/* iBook SE */
			अगर (of_machine_is_compatible("PowerBook2,2"))
				शेष_vmode = VMODE_800_600_60;

			/* PowerBook Firewire (Pismo), iBook Dual USB */
			अगर (of_machine_is_compatible("PowerBook3,1") ||
			    of_machine_is_compatible("PowerBook4,1"))
				शेष_vmode = VMODE_1024_768_60;

			/* PowerBook Titanium */
			अगर (of_machine_is_compatible("PowerBook3,2"))
				शेष_vmode = VMODE_1152_768_60;
	
			अगर (शेष_cmode > 16) 
				शेष_cmode = CMODE_32;
			अन्यथा अगर (शेष_cmode > 8) 
				शेष_cmode = CMODE_16;
			अन्यथा 
				शेष_cmode = CMODE_8;

			अगर (mac_vmode_to_var(शेष_vmode, शेष_cmode, &var))
				var = शेष_var;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
	अणु
		अगर (mode_option)
			अगर (fb_find_mode(&var, info, mode_option, शून्य, 
					 0, &शेषmode, 8) == 0)
				var = शेष_var;
	पूर्ण

	var.accel_flags &= ~FB_ACCELF_TEXT;
//	var.accel_flags |= FB_ACCELF_TEXT;/* FIXME Will add accel later */

	अगर (aty128fb_check_var(&var, info)) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Cannot set default mode.\n");
		वापस 0;
	पूर्ण

	/* setup the DAC the way we like it */
	dac = aty_ld_le32(DAC_CNTL);
	dac |= (DAC_8BIT_EN | DAC_RANGE_CNTL);
	dac |= DAC_MASK;
	अगर (par->chip_gen == rage_M3)
		dac |= DAC_PALETTE2_SNOOP_EN;
	aty_st_le32(DAC_CNTL, dac);

	/* turn off bus mastering, just in हाल */
	aty_st_le32(BUS_CNTL, aty_ld_le32(BUS_CNTL) | BUS_MASTER_DIS);

	info->var = var;
	fb_alloc_cmap(&info->cmap, 256, 0);

	var.activate = FB_ACTIVATE_NOW;

	aty128_init_engine(par);

	par->pdev = pdev;
	par->asleep = 0;
	par->lock_blank = 0;

#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
	अगर (backlight)
		aty128_bl_init(par);
#पूर्ण_अगर

	अगर (रेजिस्टर_framebuffer(info) < 0)
		वापस 0;

	fb_info(info, "%s frame buffer device on %s\n",
		info->fix.id, video_card);

	वापस 1;	/* success! */
पूर्ण

#अगर_घोषित CONFIG_PCI
/* रेजिस्टर a card    ++ajoshi */
अटल पूर्णांक aty128_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ fb_addr, reg_addr;
	काष्ठा aty128fb_par *par;
	काष्ठा fb_info *info;
	पूर्णांक err;
#अगर_अघोषित __sparc__
	व्योम __iomem *bios = शून्य;
#पूर्ण_अगर

	/* Enable device in PCI config */
	अगर ((err = pci_enable_device(pdev))) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Cannot enable PCI device: %d\n",
				err);
		वापस -ENODEV;
	पूर्ण

	fb_addr = pci_resource_start(pdev, 0);
	अगर (!request_mem_region(fb_addr, pci_resource_len(pdev, 0),
				"aty128fb FB")) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: cannot reserve frame "
				"buffer memory\n");
		वापस -ENODEV;
	पूर्ण

	reg_addr = pci_resource_start(pdev, 2);
	अगर (!request_mem_region(reg_addr, pci_resource_len(pdev, 2),
				"aty128fb MMIO")) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: cannot reserve MMIO region\n");
		जाओ err_मुक्त_fb;
	पूर्ण

	/* We have the resources. Now भवize them */
	info = framebuffer_alloc(माप(काष्ठा aty128fb_par), &pdev->dev);
	अगर (!info)
		जाओ err_मुक्त_mmio;

	par = info->par;

	info->pseuकरो_palette = par->pseuकरो_palette;

	/* Virtualize mmio region */
	info->fix.mmio_start = reg_addr;
	par->regbase = pci_ioremap_bar(pdev, 2);
	अगर (!par->regbase)
		जाओ err_मुक्त_info;

	/* Grab memory size from the card */
	// How करोes this relate to the resource length from the PCI hardware?
	par->vram_size = aty_ld_le32(CNFG_MEMSIZE) & 0x03FFFFFF;

	/* Virtualize the framebuffer */
	info->screen_base = ioremap_wc(fb_addr, par->vram_size);
	अगर (!info->screen_base)
		जाओ err_unmap_out;

	/* Set up info->fix */
	info->fix = aty128fb_fix;
	info->fix.smem_start = fb_addr;
	info->fix.smem_len = par->vram_size;
	info->fix.mmio_start = reg_addr;

	/* If we can't test scratch रेजिस्टरs, something is seriously wrong */
	अगर (!रेजिस्टर_test(par)) अणु
		prपूर्णांकk(KERN_ERR "aty128fb: Can't write to video register!\n");
		जाओ err_out;
	पूर्ण

#अगर_अघोषित __sparc__
	bios = aty128_map_ROM(par, pdev);
#अगर_घोषित CONFIG_X86
	अगर (bios == शून्य)
		bios = aty128_find_mem_vbios(par);
#पूर्ण_अगर
	अगर (bios == शून्य)
		prपूर्णांकk(KERN_INFO "aty128fb: BIOS not located, guessing timings.\n");
	अन्यथा अणु
		prपूर्णांकk(KERN_INFO "aty128fb: Rage128 BIOS located\n");
		aty128_get_pllinfo(par, bios);
		pci_unmap_rom(pdev, bios);
	पूर्ण
#पूर्ण_अगर /* __sparc__ */

	aty128_timings(par);
	pci_set_drvdata(pdev, info);

	अगर (!aty128_init(pdev, ent))
		जाओ err_out;

	अगर (mtrr)
		par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
						  par->vram_size);
	वापस 0;

err_out:
	iounmap(info->screen_base);
err_unmap_out:
	iounmap(par->regbase);
err_मुक्त_info:
	framebuffer_release(info);
err_मुक्त_mmio:
	release_mem_region(pci_resource_start(pdev, 2),
			pci_resource_len(pdev, 2));
err_मुक्त_fb:
	release_mem_region(pci_resource_start(pdev, 0),
			pci_resource_len(pdev, 0));
	वापस -ENODEV;
पूर्ण

अटल व्योम aty128_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा aty128fb_par *par;

	अगर (!info)
		वापस;

	par = info->par;

	unरेजिस्टर_framebuffer(info);

#अगर_घोषित CONFIG_FB_ATY128_BACKLIGHT
	aty128_bl_निकास(info->bl_dev);
#पूर्ण_अगर

	arch_phys_wc_del(par->wc_cookie);
	iounmap(par->regbase);
	iounmap(info->screen_base);

	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	release_mem_region(pci_resource_start(pdev, 2),
			   pci_resource_len(pdev, 2));
	framebuffer_release(info);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */



    /*
     *  Blank the display.
     */
अटल पूर्णांक aty128fb_blank(पूर्णांक blank, काष्ठा fb_info *fb)
अणु
	काष्ठा aty128fb_par *par = fb->par;
	u8 state;

	अगर (par->lock_blank || par->asleep)
		वापस 0;

	चयन (blank) अणु
	हाल FB_BLANK_NORMAL:
		state = 4;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		state = 6;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		state = 5;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		state = 7;
		अवरोध;
	हाल FB_BLANK_UNBLANK:
	शेष:
		state = 0;
		अवरोध;
	पूर्ण
	aty_st_8(CRTC_EXT_CNTL+1, state);

	अगर (par->chip_gen == rage_M3) अणु
		aty128_set_crt_enable(par, par->crt_on && !blank);
		aty128_set_lcd_enable(par, par->lcd_on && !blank);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
 *  rounded करोwn to the hardware's capabilities (according to the
 *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
 */
अटल पूर्णांक aty128fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			      u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा aty128fb_par *par = info->par;

	अगर (regno > 255
	    || (par->crtc.depth == 16 && regno > 63)
	    || (par->crtc.depth == 15 && regno > 31))
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	अगर (regno < 16) अणु
		पूर्णांक i;
		u32 *pal = info->pseuकरो_palette;

		चयन (par->crtc.depth) अणु
		हाल 15:
			pal[regno] = (regno << 10) | (regno << 5) | regno;
			अवरोध;
		हाल 16:
			pal[regno] = (regno << 11) | (regno << 6) | regno;
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

	अगर (par->crtc.depth == 16 && regno > 0) अणु
		/*
		 * With the 5-6-5 split of bits क्रम RGB at 16 bits/pixel, we
		 * have 32 slots क्रम R and B values but 64 slots क्रम G values.
		 * Thus the R and B values go in one slot but the G value
		 * goes in a dअगरferent slot, and we have to aव्योम disturbing
		 * the other fields in the slots we touch.
		 */
		par->green[regno] = green;
		अगर (regno < 32) अणु
			par->red[regno] = red;
			par->blue[regno] = blue;
			aty128_st_pal(regno * 8, red, par->green[regno*2],
				      blue, par);
		पूर्ण
		red = par->red[regno/2];
		blue = par->blue[regno/2];
		regno <<= 2;
	पूर्ण अन्यथा अगर (par->crtc.bpp == 16)
		regno <<= 3;
	aty128_st_pal(regno, red, green, blue, par);

	वापस 0;
पूर्ण

#घोषणा ATY_MIRROR_LCD_ON	0x00000001
#घोषणा ATY_MIRROR_CRT_ON	0x00000002

/* out param: u32*	backlight value: 0 to 15 */
#घोषणा FBIO_ATY128_GET_MIRROR	_IOR('@', 1, __u32)
/* in param: u32*	backlight value: 0 to 15 */
#घोषणा FBIO_ATY128_SET_MIRROR	_IOW('@', 2, __u32)

अटल पूर्णांक aty128fb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा aty128fb_par *par = info->par;
	u32 value;
	पूर्णांक rc;
    
	चयन (cmd) अणु
	हाल FBIO_ATY128_SET_MIRROR:
		अगर (par->chip_gen != rage_M3)
			वापस -EINVAL;
		rc = get_user(value, (__u32 __user *)arg);
		अगर (rc)
			वापस rc;
		par->lcd_on = (value & 0x01) != 0;
		par->crt_on = (value & 0x02) != 0;
		अगर (!par->crt_on && !par->lcd_on)
			par->lcd_on = 1;
		aty128_set_crt_enable(par, par->crt_on);	
		aty128_set_lcd_enable(par, par->lcd_on);	
		वापस 0;
	हाल FBIO_ATY128_GET_MIRROR:
		अगर (par->chip_gen != rage_M3)
			वापस -EINVAL;
		value = (par->crt_on << 1) | par->lcd_on;
		वापस put_user(value, (__u32 __user *)arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम aty128_set_suspend(काष्ठा aty128fb_par *par, पूर्णांक suspend)
अणु
	u32	pmgt;

	अगर (!par->pdev->pm_cap)
		वापस;
		
	/* Set the chip पूर्णांकo the appropriate suspend mode (we use D2,
	 * D3 would require a complete re-initialisation of the chip,
	 * including PCI config रेजिस्टरs, घड़ीs, AGP configuration, ...)
	 *
	 * For resume, the core will have alपढ़ोy brought us back to D0
	 */
	अगर (suspend) अणु
		/* Make sure CRTC2 is reset. Remove that the day we decide to
		 * actually use CRTC2 and replace it with real code क्रम disabling
		 * the CRTC2 output during sleep
		 */
		aty_st_le32(CRTC2_GEN_CNTL, aty_ld_le32(CRTC2_GEN_CNTL) &
			~(CRTC2_EN));

		/* Set the घातer management mode to be PCI based */
		/* Use this magic value क्रम now */
		pmgt = 0x0c005407;
		aty_st_pll(POWER_MANAGEMENT, pmgt);
		(व्योम)aty_ld_pll(POWER_MANAGEMENT);
		aty_st_le32(BUS_CNTL1, 0x00000010);
		aty_st_le32(MEM_POWER_MISC, 0x0c830000);
		msleep(100);
	पूर्ण
पूर्ण

अटल पूर्णांक aty128_pci_suspend_late(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा aty128fb_par *par = info->par;

	/* We करोn't करो anything but D2, क्रम now we वापस 0, but
	 * we may want to change that. How करो we know अगर the BIOS
	 * can properly take care of D3 ? Also, with swsusp, we
	 * know we'll be rebooted, ...
	 */
#अगर_अघोषित CONFIG_PPC_PMAC
	/* HACK ALERT ! Once I find a proper way to say to each driver
	 * inभागidually what will happen with it's PCI slot, I'll change
	 * that. On laptops, the AGP slot is just unघड़ीed, so D2 is
	 * expected, जबतक on desktops, the card is घातered off
	 */
	वापस 0;
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
	 
	अगर (state.event == pdev->dev.घातer.घातer_state.event)
		वापस 0;

	prपूर्णांकk(KERN_DEBUG "aty128fb: suspending...\n");
	
	console_lock();

	fb_set_suspend(info, 1);

	/* Make sure engine is reset */
	रुको_क्रम_idle(par);
	aty128_reset_engine(par);
	रुको_क्रम_idle(par);

	/* Blank display and LCD */
	aty128fb_blank(FB_BLANK_POWERDOWN, info);

	/* Sleep */
	par->asleep = 1;
	par->lock_blank = 1;

#अगर_घोषित CONFIG_PPC_PMAC
	/* On घातermac, we have hooks to properly suspend/resume AGP now,
	 * use them here. We'll ultimately need some generic support here,
	 * but the generic code isn't quite पढ़ोy क्रम that yet
	 */
	pmac_suspend_agp_क्रम_card(pdev);
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

	/* We need a way to make sure the fbdev layer will _not_ touch the
	 * framebuffer beक्रमe we put the chip to suspend state. On 2.4, I
	 * used dummy fb ops, 2.5 need proper support क्रम this at the
	 * fbdev level
	 */
	अगर (state.event != PM_EVENT_ON)
		aty128_set_suspend(par, 1);

	console_unlock();

	pdev->dev.घातer.घातer_state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aty128_pci_suspend(काष्ठा device *dev)
अणु
	वापस aty128_pci_suspend_late(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक __maybe_unused aty128_pci_hibernate(काष्ठा device *dev)
अणु
	वापस aty128_pci_suspend_late(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक __maybe_unused aty128_pci_मुक्तze(काष्ठा device *dev)
अणु
	वापस aty128_pci_suspend_late(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक aty128_करो_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा aty128fb_par *par = info->par;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_ON)
		वापस 0;

	/* PCI state will have been restored by the core, so
	 * we should be in D0 now with our config space fully
	 * restored
	 */

	/* Wakeup chip */
	aty128_set_suspend(par, 0);
	par->asleep = 0;

	/* Restore display & engine */
	aty128_reset_engine(par);
	रुको_क्रम_idle(par);
	aty128fb_set_par(info);
	fb_pan_display(info, &info->var);
	fb_set_cmap(&info->cmap, info);

	/* Refresh */
	fb_set_suspend(info, 0);

	/* Unblank */
	par->lock_blank = 0;
	aty128fb_blank(0, info);

#अगर_घोषित CONFIG_PPC_PMAC
	/* On घातermac, we have hooks to properly suspend/resume AGP now,
	 * use them here. We'll ultimately need some generic support here,
	 * but the generic code isn't quite पढ़ोy क्रम that yet
	 */
	pmac_resume_agp_क्रम_card(pdev);
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

	pdev->dev.घातer.घातer_state = PMSG_ON;

	prपूर्णांकk(KERN_DEBUG "aty128fb: resumed !\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aty128_pci_resume(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	console_lock();
	rc = aty128_करो_resume(to_pci_dev(dev));
	console_unlock();

	वापस rc;
पूर्ण


अटल पूर्णांक aty128fb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("aty128fb", &option))
		वापस -ENODEV;
	aty128fb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&aty128fb_driver);
पूर्ण

अटल व्योम __निकास aty128fb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&aty128fb_driver);
पूर्ण

module_init(aty128fb_init);

module_निकास(aty128fb_निकास);

MODULE_AUTHOR("(c)1999-2003 Brad Douglas <brad@neruo.com>");
MODULE_DESCRIPTION("FBDev driver for ATI Rage128 / Pro cards");
MODULE_LICENSE("GPL");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\" ");
module_param_named(nomtrr, mtrr, invbool, 0);
MODULE_PARM_DESC(nomtrr, "bool: Disable MTRR support (0 or 1=disabled) (default=0)");
