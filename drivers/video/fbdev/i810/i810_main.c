<शैली गुरु>
 /*-*- linux-c -*-
 *  linux/drivers/video/i810_मुख्य.c -- Intel 810 frame buffer device
 *
 *      Copyright (C) 2001 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved      
 *
 *      Contributors:
 *         Michael Vogt <mvogt@acm.org> - added support क्रम Intel 815 chipsets
 *                                        and enabling the घातer-on state of 
 *                                        बाह्यal VGA connectors क्रम 
 *                                        secondary displays
 *
 *         Fredrik Andersson <krueger@shell.linux.se> - alpha testing of
 *                                        the VESA GTF
 *
 *         Brad Corrion <bcorrion@web-co.com> - alpha testing of customized
 *                                        timings support
 *
 *	The code framework is a modअगरication of vfb.c by Geert Uytterhoeven.
 *      DotClock and PLL calculations are partly based on i810_driver.c 
 *              in xमुक्त86 v4.0.3 by Precision Insight.
 *      Watermark calculation and tables are based on i810_wmark.c 
 *              in xfre86 v4.0.3 by Precision Insight.  Slight modअगरications 
 *              only to allow क्रम पूर्णांकeger operations instead of भग्नing poपूर्णांक.
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
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/resource.h>
#समावेश <linux/unistd.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/page.h>

#समावेश "i810_regs.h"
#समावेश "i810.h"
#समावेश "i810_main.h"

/*
 * voffset - framebuffer offset in MiB from aperture start address.  In order क्रम
 * the driver to work with X, we must try to use memory holes left untouched by X. The
 * following table lists where X's dअगरferent surfaces start at.
 *
 * ---------------------------------------------
 * :                :  64 MiB     : 32 MiB      :
 * ----------------------------------------------
 * : FrontBuffer    :   0         :  0          :
 * : DepthBuffer    :   48        :  16         :
 * : BackBuffer     :   56        :  24         :
 * ----------------------------------------------
 *
 * So क्रम chipsets with 64 MiB Aperture sizes, 32 MiB क्रम v_offset is okay, allowing up to
 * 15 + 1 MiB of Framebuffer memory.  For 32 MiB Aperture sizes, a v_offset of 8 MiB should
 * work, allowing 7 + 1 MiB of Framebuffer memory.
 * Note, the size of the hole may change depending on how much memory you allocate to X,
 * and how the memory is split up between these surfaces.
 *
 * Note: Anyसमय the DepthBuffer or FrontBuffer is overlapped, X would still run but with
 * DRI disabled.  But अगर the Frontbuffer is overlapped, X will fail to load.
 *
 * Experiment with v_offset to find out which works best क्रम you.
 */
अटल u32 v_offset_शेष; /* For 32 MiB Aper size, 8 should be the शेष */
अटल u32 voffset;

अटल पूर्णांक i810fb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor);
अटल पूर्णांक i810fb_init_pci(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा pci_device_id *entry);
अटल व्योम i810fb_हटाओ_pci(काष्ठा pci_dev *dev);
अटल पूर्णांक i810fb_resume(काष्ठा pci_dev *dev);
अटल पूर्णांक i810fb_suspend(काष्ठा pci_dev *dev, pm_message_t state);

/* Chipset Specअगरic Functions */
अटल पूर्णांक i810fb_set_par    (काष्ठा fb_info *info);
अटल पूर्णांक i810fb_अ_लोolreg  (u8 regno, u8 *red, u8 *green, u8 *blue,
			      u8 *transp, काष्ठा fb_info *info);
अटल पूर्णांक i810fb_setcolreg  (अचिन्हित regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			      अचिन्हित transp, काष्ठा fb_info *info);
अटल पूर्णांक i810fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);
अटल पूर्णांक i810fb_blank      (पूर्णांक blank_mode, काष्ठा fb_info *info);

/* Initialization */
अटल व्योम i810fb_release_resource       (काष्ठा fb_info *info, काष्ठा i810fb_par *par);

/* PCI */
अटल स्थिर अक्षर * स्थिर i810_pci_list[] = अणु
	"Intel(R) 810 Framebuffer Device"                                 ,
	"Intel(R) 810-DC100 Framebuffer Device"                           ,
	"Intel(R) 810E Framebuffer Device"                                ,
	"Intel(R) 815 (Internal Graphics 100Mhz FSB) Framebuffer Device"  ,
	"Intel(R) 815 (Internal Graphics only) Framebuffer Device"        ,
	"Intel(R) 815 (Internal Graphics with AGP) Framebuffer Device"
पूर्ण;

अटल स्थिर काष्ठा pci_device_id i810fb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82810_IG1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82810_IG3,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1  पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82810E_IG,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2 पूर्ण,
	/* mvo: added i815 PCI-ID */
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82815_100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3 पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82815_NOAGP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4 पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82815_CGC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver i810fb_driver = अणु
	.name     =	"i810fb",
	.id_table =	i810fb_pci_tbl,
	.probe    =	i810fb_init_pci,
	.हटाओ   =	i810fb_हटाओ_pci,
	.suspend  =     i810fb_suspend,
	.resume   =     i810fb_resume,
पूर्ण;

अटल अक्षर *mode_option = शून्य;
अटल पूर्णांक vram = 4;
अटल पूर्णांक bpp = 8;
अटल bool mtrr;
अटल bool accel;
अटल पूर्णांक hsync1;
अटल पूर्णांक hsync2;
अटल पूर्णांक vsync1;
अटल पूर्णांक vsync2;
अटल पूर्णांक xres;
अटल पूर्णांक yres;
अटल पूर्णांक vyres;
अटल bool sync;
अटल bool extvga;
अटल bool dcolor;
अटल bool ddc3;

/*------------------------------------------------------------*/

/**************************************************************
 *                Hardware Low Level Routines                 *
 **************************************************************/

/**
 * i810_screen_off - turns off/on display
 * @mmio: address of रेजिस्टर space
 * @mode: on or off
 *
 * DESCRIPTION:
 * Blanks/unblanks the display
 */
अटल व्योम i810_screen_off(u8 __iomem *mmio, u8 mode)
अणु
	u32 count = WAIT_COUNT;
	u8 val;

	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	val = i810_पढ़ोb(SR_DATA, mmio);
	val = (mode == OFF) ? val | SCR_OFF :
		val & ~SCR_OFF;

	जबतक((i810_पढ़ोw(DISP_SL, mmio) & 0xFFF) && count--);
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	i810_ग_लिखोb(SR_DATA, mmio, val);
पूर्ण

/**
 * i810_dram_off - turns off/on dram refresh
 * @mmio: address of रेजिस्टर space
 * @mode: on or off
 *
 * DESCRIPTION:
 * Turns off DRAM refresh.  Must be off क्रम only 2 vsyncs
 * beक्रमe data becomes corrupt
 */
अटल व्योम i810_dram_off(u8 __iomem *mmio, u8 mode)
अणु
	u8 val;

	val = i810_पढ़ोb(DRAMCH, mmio);
	val &= DRAM_OFF;
	val = (mode == OFF) ? val : val | DRAM_ON;
	i810_ग_लिखोb(DRAMCH, mmio, val);
पूर्ण

/**
 * i810_protect_regs - allows rw/ro mode of certain VGA रेजिस्टरs
 * @mmio: address of रेजिस्टर space
 * @mode: protect/unprotect
 *
 * DESCRIPTION:
 * The IBM VGA standard allows protection of certain VGA रेजिस्टरs.  
 * This will  protect or unprotect them. 
 */
अटल व्योम i810_protect_regs(u8 __iomem *mmio, पूर्णांक mode)
अणु
	u8 reg;

	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR11);
	reg = i810_पढ़ोb(CR_DATA_CGA, mmio);
	reg = (mode == OFF) ? reg & ~0x80 :
		reg | 0x80;
 		
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR11);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, reg);
पूर्ण

/**
 * i810_load_pll - loads values क्रम the hardware PLL घड़ी
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Loads the P, M, and N रेजिस्टरs.  
 */
अटल व्योम i810_load_pll(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp1, पंचांगp2;
	u8 __iomem *mmio = par->mmio_start_भव;
	
	पंचांगp1 = par->regs.M | par->regs.N << 16;
	पंचांगp2 = i810_पढ़ोl(DCLK_2D, mmio);
	पंचांगp2 &= ~MN_MASK;
	i810_ग_लिखोl(DCLK_2D, mmio, पंचांगp1 | पंचांगp2);
	
	पंचांगp1 = par->regs.P;
	पंचांगp2 = i810_पढ़ोl(DCLK_0DS, mmio);
	पंचांगp2 &= ~(P_OR << 16);
	i810_ग_लिखोl(DCLK_0DS, mmio, (पंचांगp1 << 16) | पंचांगp2);

	i810_ग_लिखोb(MSR_WRITE, mmio, par->regs.msr | 0xC8 | 1);

पूर्ण

/**
 * i810_load_vga - load standard VGA रेजिस्टरs
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Load values to VGA रेजिस्टरs
 */
अटल व्योम i810_load_vga(काष्ठा i810fb_par *par)
अणु	
	u8 __iomem *mmio = par->mmio_start_भव;

	/* पूर्णांकerlace */
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR70);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->पूर्णांकerlace);

	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR00);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr00);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR01);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr01);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR02);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr02);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR03);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr03);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR04);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr04);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR05);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr05);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR06);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr06);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR09);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr09);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR10);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr10);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR11);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr11);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR12);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr12);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR15);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr15);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR16);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr16);
पूर्ण

/**
 * i810_load_vgax - load extended VGA रेजिस्टरs
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Load values to extended VGA रेजिस्टरs
 */
अटल व्योम i810_load_vgax(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR30);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr30);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR31);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr31);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR32);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr32);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR33);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr33);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR35);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr35);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR39);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->regs.cr39);
पूर्ण

/**
 * i810_load_2d - load grahics रेजिस्टरs
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Load values to graphics रेजिस्टरs
 */
अटल व्योम i810_load_2d(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp;
	u8 पंचांगp8;
	u8 __iomem *mmio = par->mmio_start_भव;

  	i810_ग_लिखोl(FW_BLC, mmio, par->watermark); 
	पंचांगp = i810_पढ़ोl(PIXCONF, mmio);
	पंचांगp |= 1 | 1 << 20;
	i810_ग_लिखोl(PIXCONF, mmio, पंचांगp);

	i810_ग_लिखोl(OVRACT, mmio, par->ovract);

	i810_ग_लिखोb(GR_INDEX, mmio, GR10);
	पंचांगp8 = i810_पढ़ोb(GR_DATA, mmio);
	पंचांगp8 |= 2;
	i810_ग_लिखोb(GR_INDEX, mmio, GR10);
	i810_ग_लिखोb(GR_DATA, mmio, पंचांगp8);
पूर्ण	

/**
 * i810_hires - enables high resolution mode
 * @mmio: address of रेजिस्टर space
 */
अटल व्योम i810_hires(u8 __iomem *mmio)
अणु
	u8 val;
	
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR80);
	val = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR80);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, val | 1);
	/* Stop LCD displays from flickering */
	i810_ग_लिखोl(MEM_MODE, mmio, i810_पढ़ोl(MEM_MODE, mmio) | 4);
पूर्ण

/**
 * i810_load_pitch - loads the अक्षरacters per line of the display
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Loads the अक्षरacters per line
 */	
अटल व्योम i810_load_pitch(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp, pitch;
	u8 val;
	u8 __iomem *mmio = par->mmio_start_भव;
			
	pitch = par->pitch >> 3;
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	val = i810_पढ़ोb(SR_DATA, mmio);
	val &= 0xE0;
	val |= 1 | 1 << 2;
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	i810_ग_लिखोb(SR_DATA, mmio, val);

	पंचांगp = pitch & 0xFF;
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR13);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, (u8) पंचांगp);
	
	पंचांगp = pitch >> 8;
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR41);
	val = i810_पढ़ोb(CR_DATA_CGA, mmio) & ~0x0F;
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR41);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, (u8) पंचांगp | val);
पूर्ण

/**
 * i810_load_color - loads the color depth of the display
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Loads the color depth of the display and the graphics engine
 */
अटल व्योम i810_load_color(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;
	u32 reg1;
	u16 reg2;

	reg1 = i810_पढ़ोl(PIXCONF, mmio) & ~(0xF0000 | 1 << 27);
	reg2 = i810_पढ़ोw(BLTCNTL, mmio) & ~0x30;

	reg1 |= 0x8000 | par->pixconf;
	reg2 |= par->bltcntl;
	i810_ग_लिखोl(PIXCONF, mmio, reg1);
	i810_ग_लिखोw(BLTCNTL, mmio, reg2);
पूर्ण

/**
 * i810_load_regs - loads all रेजिस्टरs क्रम the mode
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 * 
 * DESCRIPTION:
 * Loads रेजिस्टरs
 */
अटल व्योम i810_load_regs(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_screen_off(mmio, OFF);
	i810_protect_regs(mmio, OFF);
	i810_dram_off(mmio, OFF);
	i810_load_pll(par);
	i810_load_vga(par);
	i810_load_vgax(par);
	i810_dram_off(mmio, ON);	
	i810_load_2d(par);
	i810_hires(mmio);
	i810_screen_off(mmio, ON);
	i810_protect_regs(mmio, ON);
	i810_load_color(par);
	i810_load_pitch(par);
पूर्ण

अटल व्योम i810_ग_लिखो_dac(u8 regno, u8 red, u8 green, u8 blue,
			  u8 __iomem *mmio)
अणु
	i810_ग_लिखोb(CLUT_INDEX_WRITE, mmio, regno);
	i810_ग_लिखोb(CLUT_DATA, mmio, red);
	i810_ग_लिखोb(CLUT_DATA, mmio, green);
	i810_ग_लिखोb(CLUT_DATA, mmio, blue); 	
पूर्ण

अटल व्योम i810_पढ़ो_dac(u8 regno, u8 *red, u8 *green, u8 *blue,
			  u8 __iomem *mmio)
अणु
	i810_ग_लिखोb(CLUT_INDEX_READ, mmio, regno);
	*red = i810_पढ़ोb(CLUT_DATA, mmio);
	*green = i810_पढ़ोb(CLUT_DATA, mmio);
	*blue = i810_पढ़ोb(CLUT_DATA, mmio);
पूर्ण

/************************************************************
 *                   VGA State Restore                      * 
 ************************************************************/
अटल व्योम i810_restore_pll(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp1, पंचांगp2;
	u8 __iomem *mmio = par->mmio_start_भव;
	
	पंचांगp1 = par->hw_state.dclk_2d;
	पंचांगp2 = i810_पढ़ोl(DCLK_2D, mmio);
	पंचांगp1 &= ~MN_MASK;
	पंचांगp2 &= MN_MASK;
	i810_ग_लिखोl(DCLK_2D, mmio, पंचांगp1 | पंचांगp2);

	पंचांगp1 = par->hw_state.dclk_1d;
	पंचांगp2 = i810_पढ़ोl(DCLK_1D, mmio);
	पंचांगp1 &= ~MN_MASK;
	पंचांगp2 &= MN_MASK;
	i810_ग_लिखोl(DCLK_1D, mmio, पंचांगp1 | पंचांगp2);

	i810_ग_लिखोl(DCLK_0DS, mmio, par->hw_state.dclk_0ds);
पूर्ण

अटल व्योम i810_restore_dac(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp1, पंचांगp2;
	u8 __iomem *mmio = par->mmio_start_भव;

	पंचांगp1 = par->hw_state.pixconf;
	पंचांगp2 = i810_पढ़ोl(PIXCONF, mmio);
	पंचांगp1 &= DAC_BIT;
	पंचांगp2 &= ~DAC_BIT;
	i810_ग_लिखोl(PIXCONF, mmio, पंचांगp1 | पंचांगp2);
पूर्ण

अटल व्योम i810_restore_vgax(काष्ठा i810fb_par *par)
अणु
	u8 i, j;
	u8 __iomem *mmio = par->mmio_start_भव;
	
	क्रम (i = 0; i < 4; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR30+i);
		i810_ग_लिखोb(CR_DATA_CGA, mmio, *(&(par->hw_state.cr30) + i));
	पूर्ण
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR35);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->hw_state.cr35);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR39);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->hw_state.cr39);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR41);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->hw_state.cr39);

	/*restore पूर्णांकerlace*/
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR70);
	i = par->hw_state.cr70;
	i &= INTERLACE_BIT;
	j = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR70);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, j | i);

	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR80);
	i810_ग_लिखोb(CR_DATA_CGA, mmio, par->hw_state.cr80);
	i810_ग_लिखोb(MSR_WRITE, mmio, par->hw_state.msr);
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	i = (par->hw_state.sr01) & ~0xE0 ;
	j = i810_पढ़ोb(SR_DATA, mmio) & 0xE0;
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	i810_ग_लिखोb(SR_DATA, mmio, i | j);
पूर्ण

अटल व्योम i810_restore_vga(काष्ठा i810fb_par *par)
अणु
	u8 i;
	u8 __iomem *mmio = par->mmio_start_भव;
	
	क्रम (i = 0; i < 10; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR00 + i);
		i810_ग_लिखोb(CR_DATA_CGA, mmio, *((&par->hw_state.cr00) + i));
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR10 + i);
		i810_ग_लिखोb(CR_DATA_CGA, mmio, *((&par->hw_state.cr10) + i));
	पूर्ण
पूर्ण

अटल व्योम i810_restore_addr_map(काष्ठा i810fb_par *par)
अणु
	u8 पंचांगp;
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_ग_लिखोb(GR_INDEX, mmio, GR10);
	पंचांगp = i810_पढ़ोb(GR_DATA, mmio);
	पंचांगp &= ADDR_MAP_MASK;
	पंचांगp |= par->hw_state.gr10;
	i810_ग_लिखोb(GR_INDEX, mmio, GR10);
	i810_ग_लिखोb(GR_DATA, mmio, पंचांगp);
पूर्ण

अटल व्योम i810_restore_2d(काष्ठा i810fb_par *par)
अणु
	u32 पंचांगp_दीर्घ;
	u16 पंचांगp_word;
	u8 __iomem *mmio = par->mmio_start_भव;

	पंचांगp_word = i810_पढ़ोw(BLTCNTL, mmio);
	पंचांगp_word &= ~(3 << 4); 
	पंचांगp_word |= par->hw_state.bltcntl;
	i810_ग_लिखोw(BLTCNTL, mmio, पंचांगp_word);
       
	i810_dram_off(mmio, OFF);
	i810_ग_लिखोl(PIXCONF, mmio, par->hw_state.pixconf);
	i810_dram_off(mmio, ON);

	पंचांगp_word = i810_पढ़ोw(HWSTAM, mmio);
	पंचांगp_word &= 3 << 13;
	पंचांगp_word |= par->hw_state.hwstam;
	i810_ग_लिखोw(HWSTAM, mmio, पंचांगp_word);

	पंचांगp_दीर्घ = i810_पढ़ोl(FW_BLC, mmio);
	पंचांगp_दीर्घ &= FW_BLC_MASK;
	पंचांगp_दीर्घ |= par->hw_state.fw_blc;
	i810_ग_लिखोl(FW_BLC, mmio, पंचांगp_दीर्घ);

	i810_ग_लिखोl(HWS_PGA, mmio, par->hw_state.hws_pga); 
	i810_ग_लिखोw(IER, mmio, par->hw_state.ier);
	i810_ग_लिखोw(IMR, mmio, par->hw_state.imr);
	i810_ग_लिखोl(DPLYSTAS, mmio, par->hw_state.dplystas);
पूर्ण

अटल व्योम i810_restore_vga_state(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_screen_off(mmio, OFF);
	i810_protect_regs(mmio, OFF);
	i810_dram_off(mmio, OFF);
	i810_restore_pll(par);
	i810_restore_dac(par);
	i810_restore_vga(par);
	i810_restore_vgax(par);
	i810_restore_addr_map(par);
	i810_dram_off(mmio, ON);
	i810_restore_2d(par);
	i810_screen_off(mmio, ON);
	i810_protect_regs(mmio, ON);
पूर्ण

/***********************************************************************
 *                         VGA State Save                              *
 ***********************************************************************/

अटल व्योम i810_save_vgax(काष्ठा i810fb_par *par)
अणु
	u8 i;
	u8 __iomem *mmio = par->mmio_start_भव;

	क्रम (i = 0; i < 4; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR30 + i);
		*(&(par->hw_state.cr30) + i) = i810_पढ़ोb(CR_DATA_CGA, mmio);
	पूर्ण
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR35);
	par->hw_state.cr35 = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR39);
	par->hw_state.cr39 = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR41);
	par->hw_state.cr41 = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR70);
	par->hw_state.cr70 = i810_पढ़ोb(CR_DATA_CGA, mmio);	
	par->hw_state.msr = i810_पढ़ोb(MSR_READ, mmio);
	i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR80);
	par->hw_state.cr80 = i810_पढ़ोb(CR_DATA_CGA, mmio);
	i810_ग_लिखोb(SR_INDEX, mmio, SR01);
	par->hw_state.sr01 = i810_पढ़ोb(SR_DATA, mmio);
पूर्ण

अटल व्योम i810_save_vga(काष्ठा i810fb_par *par)
अणु
	u8 i;
	u8 __iomem *mmio = par->mmio_start_भव;

	क्रम (i = 0; i < 10; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR00 + i);
		*((&par->hw_state.cr00) + i) = i810_पढ़ोb(CR_DATA_CGA, mmio);
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		i810_ग_लिखोb(CR_INDEX_CGA, mmio, CR10 + i);
		*((&par->hw_state.cr10) + i) = i810_पढ़ोb(CR_DATA_CGA, mmio);
	पूर्ण
पूर्ण

अटल व्योम i810_save_2d(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	par->hw_state.dclk_2d = i810_पढ़ोl(DCLK_2D, mmio);
	par->hw_state.dclk_1d = i810_पढ़ोl(DCLK_1D, mmio);
	par->hw_state.dclk_0ds = i810_पढ़ोl(DCLK_0DS, mmio);
	par->hw_state.pixconf = i810_पढ़ोl(PIXCONF, mmio);
	par->hw_state.fw_blc = i810_पढ़ोl(FW_BLC, mmio);
	par->hw_state.bltcntl = i810_पढ़ोw(BLTCNTL, mmio);
	par->hw_state.hwstam = i810_पढ़ोw(HWSTAM, mmio); 
	par->hw_state.hws_pga = i810_पढ़ोl(HWS_PGA, mmio); 
	par->hw_state.ier = i810_पढ़ोw(IER, mmio);
	par->hw_state.imr = i810_पढ़ोw(IMR, mmio);
	par->hw_state.dplystas = i810_पढ़ोl(DPLYSTAS, mmio);
पूर्ण

अटल व्योम i810_save_vga_state(काष्ठा i810fb_par *par)
अणु
	i810_save_vga(par);
	i810_save_vgax(par);
	i810_save_2d(par);
पूर्ण

/************************************************************
 *                    Helpers                               * 
 ************************************************************/
/**
 * get_line_length - calculates buffer pitch in bytes
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 * @xres_भव: भव resolution of the frame
 * @bpp: bits per pixel
 *
 * DESCRIPTION:
 * Calculates buffer pitch in bytes.  
 */
अटल u32 get_line_length(काष्ठा i810fb_par *par, पूर्णांक xres_भव, पूर्णांक bpp)
अणु
   	u32 length;
	
	length = xres_भव*bpp;
	length = (length+31)&-32;
	length >>= 3;
	वापस length;
पूर्ण

/**
 * i810_calc_dclk - calculates the P, M, and N values of a pixelघड़ी value
 * @freq: target pixelघड़ी in picoseconds
 * @m: where to ग_लिखो M रेजिस्टर
 * @n: where to ग_लिखो N रेजिस्टर
 * @p: where to ग_लिखो P रेजिस्टर
 *
 * DESCRIPTION:
 * Based on the क्रमmula Freq_actual = (4*M*Freq_ref)/(N^P)
 * Repeatedly computes the Freq until the actual Freq is equal to
 * the target Freq or until the loop count is zero.  In the latter
 * हाल, the actual frequency nearest the target will be used.
 */
अटल व्योम i810_calc_dclk(u32 freq, u32 *m, u32 *n, u32 *p)
अणु
	u32 m_reg, n_reg, p_भागisor, n_target_max;
	u32 m_target, n_target, p_target, n_best, m_best, mod;
	u32 f_out, target_freq, dअगरf = 0, mod_min, dअगरf_min;

	dअगरf_min = mod_min = 0xFFFFFFFF;
	n_best = m_best = m_target = f_out = 0;

	target_freq =  freq;
	n_target_max = 30;

	/*
	 * find P such that target freq is 16x reference freq (Hz). 
	 */
	p_भागisor = 1;
	p_target = 0;
	जबतक(!((1000000 * p_भागisor)/(16 * 24 * target_freq)) && 
	      p_भागisor <= 32) अणु
		p_भागisor <<= 1;
		p_target++;
	पूर्ण

	n_reg = m_reg = n_target = 3;	
	जबतक (dअगरf_min && mod_min && (n_target < n_target_max)) अणु
		f_out = (p_भागisor * n_reg * 1000000)/(4 * 24 * m_reg);
		mod = (p_भागisor * n_reg * 1000000) % (4 * 24 * m_reg);
		m_target = m_reg;
		n_target = n_reg;
		अगर (f_out <= target_freq) अणु
			n_reg++;
			dअगरf = target_freq - f_out;
		पूर्ण अन्यथा अणु
			m_reg++;
			dअगरf = f_out - target_freq;
		पूर्ण

		अगर (dअगरf_min > dअगरf) अणु
			dअगरf_min = dअगरf;
			n_best = n_target;
			m_best = m_target;
		पूर्ण		 

		अगर (!dअगरf && mod_min > mod) अणु
			mod_min = mod;
			n_best = n_target;
			m_best = m_target;
		पूर्ण
	पूर्ण 
	अगर (m) *m = (m_best - 2) & 0x3FF;
	अगर (n) *n = (n_best - 2) & 0x3FF;
	अगर (p) *p = (p_target << 4);
पूर्ण

/*************************************************************
 *                Hardware Cursor Routines                   *
 *************************************************************/

/**
 * i810_enable_cursor - show or hide the hardware cursor
 * @mmio: address of रेजिस्टर space
 * @mode: show (1) or hide (0)
 *
 * Description:
 * Shows or hides the hardware cursor
 */
अटल व्योम i810_enable_cursor(u8 __iomem *mmio, पूर्णांक mode)
अणु
	u32 temp;
	
	temp = i810_पढ़ोl(PIXCONF, mmio);
	temp = (mode == ON) ? temp | CURSOR_ENABLE_MASK :
		temp & ~CURSOR_ENABLE_MASK;

	i810_ग_लिखोl(PIXCONF, mmio, temp);
पूर्ण

अटल व्योम i810_reset_cursor_image(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *addr = par->cursor_heap.भव;
	पूर्णांक i, j;

	क्रम (i = 64; i--; ) अणु
		क्रम (j = 0; j < 8; j++) अणु             
			i810_ग_लिखोb(j, addr, 0xff);   
			i810_ग_लिखोb(j+8, addr, 0x00); 
		पूर्ण	
		addr +=16;
	पूर्ण
पूर्ण

अटल व्योम i810_load_cursor_image(पूर्णांक width, पूर्णांक height, u8 *data,
				   काष्ठा i810fb_par *par)
अणु
	u8 __iomem *addr = par->cursor_heap.भव;
	पूर्णांक i, j, w = width/8;
	पूर्णांक mod = width % 8, t_mask, d_mask;
	
	t_mask = 0xff >> mod;
	d_mask = ~(0xff >> mod); 
	क्रम (i = height; i--; ) अणु
		क्रम (j = 0; j < w; j++) अणु
			i810_ग_लिखोb(j+0, addr, 0x00);
			i810_ग_लिखोb(j+8, addr, *data++);
		पूर्ण
		अगर (mod) अणु
			i810_ग_लिखोb(j+0, addr, t_mask);
			i810_ग_लिखोb(j+8, addr, *data++ & d_mask);
		पूर्ण
		addr += 16;
	पूर्ण
पूर्ण

अटल व्योम i810_load_cursor_colors(पूर्णांक fg, पूर्णांक bg, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;
	u8 red, green, blue, trans, temp;

	i810fb_अ_लोolreg(bg, &red, &green, &blue, &trans, info);

	temp = i810_पढ़ोb(PIXCONF1, mmio);
	i810_ग_लिखोb(PIXCONF1, mmio, temp | EXTENDED_PALETTE);

	i810_ग_लिखो_dac(4, red, green, blue, mmio);

	i810_ग_लिखोb(PIXCONF1, mmio, temp);

	i810fb_अ_लोolreg(fg, &red, &green, &blue, &trans, info);
	temp = i810_पढ़ोb(PIXCONF1, mmio);
	i810_ग_लिखोb(PIXCONF1, mmio, temp | EXTENDED_PALETTE);

	i810_ग_लिखो_dac(5, red, green, blue, mmio);

	i810_ग_लिखोb(PIXCONF1, mmio, temp);
पूर्ण

/**
 * i810_init_cursor - initializes the cursor
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 *
 * DESCRIPTION:
 * Initializes the cursor रेजिस्टरs
 */
अटल व्योम i810_init_cursor(काष्ठा i810fb_par *par)
अणु
	u8 __iomem *mmio = par->mmio_start_भव;

	i810_enable_cursor(mmio, OFF);
	i810_ग_लिखोl(CURBASE, mmio, par->cursor_heap.physical);
	i810_ग_लिखोw(CURCNTR, mmio, COORD_ACTIVE | CURSOR_MODE_64_XOR);
पूर्ण	

/*********************************************************************
 *                    Framebuffer hook helpers                       *
 *********************************************************************/
/**
 * i810_round_off -  Round off values to capability of hardware
 * @var: poपूर्णांकer to fb_var_screeninfo काष्ठाure
 *
 * DESCRIPTION:
 * @var contains user-defined inक्रमmation क्रम the mode to be set.
 * This will try modअगरy those values to ones nearest the
 * capability of the hardware
 */
अटल व्योम i810_round_off(काष्ठा fb_var_screeninfo *var)
अणु
	u32 xres, yres, vxres, vyres;

	/*
	 *  Presently supports only these configurations 
	 */

	xres = var->xres;
	yres = var->yres;
	vxres = var->xres_भव;
	vyres = var->yres_भव;

	var->bits_per_pixel += 7;
	var->bits_per_pixel &= ~7;
	
	अगर (var->bits_per_pixel < 8)
		var->bits_per_pixel = 8;
	अगर (var->bits_per_pixel > 32) 
		var->bits_per_pixel = 32;

	round_off_xres(&xres);
	अगर (xres < 40)
		xres = 40;
	अगर (xres > 2048) 
		xres = 2048;
	xres = (xres + 7) & ~7;

	अगर (vxres < xres) 
		vxres = xres;

	round_off_yres(&xres, &yres);
	अगर (yres < 1)
		yres = 1;
	अगर (yres >= 2048)
		yres = 2048;

	अगर (vyres < yres) 
		vyres = yres;

	अगर (var->bits_per_pixel == 32)
		var->accel_flags = 0;

	/* round of horizontal timings to nearest 8 pixels */
	var->left_margin = (var->left_margin + 4) & ~7;
	var->right_margin = (var->right_margin + 4) & ~7;
	var->hsync_len = (var->hsync_len + 4) & ~7;

	अगर (var->vmode & FB_VMODE_INTERLACED) अणु
		अगर (!((yres + var->upper_margin + var->vsync_len + 
		       var->lower_margin) & 1))
			var->upper_margin++;
	पूर्ण
	
	var->xres = xres;
	var->yres = yres;
	var->xres_भव = vxres;
	var->yres_भव = vyres;
पूर्ण	

/**
 * set_color_bitfields - sets rgba fields
 * @var: poपूर्णांकer to fb_var_screeninfo
 *
 * DESCRIPTION:
 * The length, offset and ordering  क्रम each color field 
 * (red, green, blue)  will be set as specअगरied 
 * by the hardware
 */  
अटल व्योम set_color_bitfields(काष्ठा fb_var_screeninfo *var)
अणु
	चयन (var->bits_per_pixel) अणु
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
	हाल 16:
		var->green.length = (var->green.length == 5) ? 5 : 6;
		var->red.length = 5;
		var->blue.length = 5;
		var->transp.length = 6 - var->green.length;
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 5 + var->green.length;
		var->transp.offset =  (5 + var->red.offset) & 15;
		अवरोध;
	हाल 24:	/* RGB 888   */
	हाल 32:	/* RGBA 8888 */
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.length = var->bits_per_pixel - 24;
		var->transp.offset = (var->transp.length) ? 24 : 0;
		अवरोध;
	पूर्ण
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;
पूर्ण

/**
 * i810_check_params - check अगर contents in var are valid
 * @var: poपूर्णांकer to fb_var_screeninfo
 * @info: poपूर्णांकer to fb_info
 *
 * DESCRIPTION:
 * This will check अगर the framebuffer size is sufficient 
 * क्रम the current mode and अगर the user's monitor has the 
 * required specअगरications to display the current mode.
 */
अटल पूर्णांक i810_check_params(काष्ठा fb_var_screeninfo *var, 
			     काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	पूर्णांक line_length, vidmem, mode_valid = 0, retval = 0;
	u32 vyres = var->yres_भव, vxres = var->xres_भव;

	/*
	 *  Memory limit
	 */
	line_length = get_line_length(par, vxres, var->bits_per_pixel);
	vidmem = line_length*vyres;

	अगर (vidmem > par->fb.size) अणु
		vyres = par->fb.size/line_length;
		अगर (vyres < var->yres) अणु
			vyres = info->var.yres;
			vxres = par->fb.size/vyres;
			vxres /= var->bits_per_pixel >> 3;
			line_length = get_line_length(par, vxres, 
						      var->bits_per_pixel);
			vidmem = line_length * info->var.yres;
			अगर (vxres < var->xres) अणु
				prपूर्णांकk("i810fb: required video memory, "
				       "%d bytes, for %dx%d-%d (virtual) "
				       "is out of range\n", 
				       vidmem, vxres, vyres, 
				       var->bits_per_pixel);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	var->xres_भव = vxres;
	var->yres_भव = vyres;

	/*
	 * Monitor limit
	 */
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		info->monspecs.dclkmax = 234000000;
		अवरोध;
	हाल 16:
		info->monspecs.dclkmax = 229000000;
		अवरोध;
	हाल 24:
	हाल 32:
		info->monspecs.dclkmax = 204000000;
		अवरोध;
	पूर्ण

	info->monspecs.dclkmin = 15000000;

	अगर (!fb_validate_mode(var, info))
		mode_valid = 1;

#अगर_घोषित CONFIG_FB_I810_I2C
	अगर (!mode_valid && info->monspecs.gtf &&
	    !fb_get_mode(FB_MAXTIMINGS, 0, var, info))
		mode_valid = 1;

	अगर (!mode_valid && info->monspecs.modedb_len) अणु
		स्थिर काष्ठा fb_videomode *mode;

		mode = fb_find_best_mode(var, &info->modelist);
		अगर (mode) अणु
			fb_videomode_to_var(var, mode);
			mode_valid = 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!mode_valid && info->monspecs.modedb_len == 0) अणु
		अगर (fb_get_mode(FB_MAXTIMINGS, 0, var, info)) अणु
			पूर्णांक शेष_sync = (info->monspecs.hfmin-HFMIN)
				|(info->monspecs.hfmax-HFMAX)
				|(info->monspecs.vfmin-VFMIN)
				|(info->monspecs.vfmax-VFMAX);
			prपूर्णांकk("i810fb: invalid video mode%s\n",
			       शेष_sync ? "" : ". Specifying "
			       "vsyncN/hsyncN parameters may help");
			retval = -EINVAL;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण	

/**
 * encode_fix - fill up fb_fix_screeninfo काष्ठाure
 * @fix: poपूर्णांकer to fb_fix_screeninfo
 * @info: poपूर्णांकer to fb_info
 *
 * DESCRIPTION:
 * This will set up parameters that are unmodअगरiable by the user.
 */
अटल पूर्णांक encode_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

    	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));

    	म_नकल(fix->id, "I810");
	mutex_lock(&info->mm_lock);
    	fix->smem_start = par->fb.physical;
    	fix->smem_len = par->fb.size;
	mutex_unlock(&info->mm_lock);
    	fix->type = FB_TYPE_PACKED_PIXELS;
    	fix->type_aux = 0;
	fix->xpanstep = 8;
	fix->ypanstep = 1;

    	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
	    	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	    	अवरोध;
	हाल 16:
	हाल 24:
	हाल 32:
		अगर (info->var.nonstd)
			fix->visual = FB_VISUAL_सूचीECTCOLOR;
		अन्यथा
			fix->visual = FB_VISUAL_TRUECOLOR;
	    	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
    	fix->ywrapstep = 0;
	fix->line_length = par->pitch;
	fix->mmio_start = par->mmio_start_phys;
	fix->mmio_len = MMIO_SIZE;
	fix->accel = FB_ACCEL_I810;

	वापस 0;
पूर्ण

/**
 * decode_var - modअगरy par according to contents of var
 * @var: poपूर्णांकer to fb_var_screeninfo
 * @par: poपूर्णांकer to i810fb_par
 *
 * DESCRIPTION:
 * Based on the contents of @var, @par will be dynamically filled up.
 * @par contains all inक्रमmation necessary to modअगरy the hardware. 
*/
अटल व्योम decode_var(स्थिर काष्ठा fb_var_screeninfo *var, 
		       काष्ठा i810fb_par *par)
अणु
	u32 xres, yres, vxres, vyres;

	xres = var->xres;
	yres = var->yres;
	vxres = var->xres_भव;
	vyres = var->yres_भव;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		par->pixconf = PIXCONF8;
		par->bltcntl = 0;
		par->depth = 1;
		par->blit_bpp = BPP8;
		अवरोध;
	हाल 16:
		अगर (var->green.length == 5)
			par->pixconf = PIXCONF15;
		अन्यथा
			par->pixconf = PIXCONF16;
		par->bltcntl = 16;
		par->depth = 2;
		par->blit_bpp = BPP16;
		अवरोध;
	हाल 24:
		par->pixconf = PIXCONF24;
		par->bltcntl = 32;
		par->depth = 3;
		par->blit_bpp = BPP24;
		अवरोध;
	हाल 32:
		par->pixconf = PIXCONF32;
		par->bltcntl = 0;
		par->depth = 4;
		par->blit_bpp = 3 << 24;
		अवरोध;
	पूर्ण
	अगर (var->nonstd && var->bits_per_pixel != 8)
		par->pixconf |= 1 << 27;

	i810_calc_dclk(var->pixघड़ी, &par->regs.M, 
		       &par->regs.N, &par->regs.P);
	i810fb_encode_रेजिस्टरs(var, par, xres, yres);

	par->watermark = i810_get_watermark(var, par);
	par->pitch = get_line_length(par, vxres, var->bits_per_pixel);
पूर्ण	

/**
 * i810fb_अ_लोolreg - माला_लो red, green and blue values of the hardware DAC
 * @regno: DAC index
 * @red: red
 * @green: green
 * @blue: blue
 * @transp: transparency (alpha)
 * @info: poपूर्णांकer to fb_info
 *
 * DESCRIPTION:
 * Gets the red, green and blue values of the hardware DAC as poपूर्णांकed by @regno
 * and ग_लिखोs them to @red, @green and @blue respectively
 */
अटल पूर्णांक i810fb_अ_लोolreg(u8 regno, u8 *red, u8 *green, u8 *blue, 
			    u8 *transp, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;
	u8 temp;

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		अगर ((info->var.green.length == 5 && regno > 31) ||
		    (info->var.green.length == 6 && regno > 63))
			वापस 1;
	पूर्ण

	temp = i810_पढ़ोb(PIXCONF1, mmio);
	i810_ग_लिखोb(PIXCONF1, mmio, temp & ~EXTENDED_PALETTE);

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR && 
	    info->var.green.length == 5) 
		i810_पढ़ो_dac(regno * 8, red, green, blue, mmio);

	अन्यथा अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR && 
		 info->var.green.length == 6) अणु
		u8 पंचांगp;

		i810_पढ़ो_dac(regno * 8, red, &पंचांगp, blue, mmio);
		i810_पढ़ो_dac(regno * 4, &पंचांगp, green, &पंचांगp, mmio);
	पूर्ण
	अन्यथा 
		i810_पढ़ो_dac(regno, red, green, blue, mmio);

    	*transp = 0;
	i810_ग_लिखोb(PIXCONF1, mmio, temp);

    	वापस 0;
पूर्ण

/****************************************************************** 
 *           Framebuffer device-specअगरic hooks                    *
 ******************************************************************/

अटल पूर्णांक i810fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा i810fb_par *par = info->par;

	mutex_lock(&par->खोलो_lock);
	अगर (par->use_count == 0) अणु
		स_रखो(&par->state, 0, माप(काष्ठा vgastate));
		par->state.flags = VGA_SAVE_CMAP;
		par->state.vgabase = par->mmio_start_भव;
		save_vga(&par->state);

		i810_save_vga_state(par);
	पूर्ण

	par->use_count++;
	mutex_unlock(&par->खोलो_lock);
	
	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा i810fb_par *par = info->par;

	mutex_lock(&par->खोलो_lock);
	अगर (par->use_count == 0) अणु
		mutex_unlock(&par->खोलो_lock);
		वापस -EINVAL;
	पूर्ण

	अगर (par->use_count == 1) अणु
		i810_restore_vga_state(par);
		restore_vga(&par->state);
	पूर्ण

	par->use_count--;
	mutex_unlock(&par->खोलो_lock);
	
	वापस 0;
पूर्ण


अटल पूर्णांक i810fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green, 
			    अचिन्हित blue, अचिन्हित transp, 
			    काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;
	u8 temp;
	पूर्णांक i;

 	अगर (regno > 255) वापस 1;

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		अगर ((info->var.green.length == 5 && regno > 31) ||
		    (info->var.green.length == 6 && regno > 63))
			वापस 1;
	पूर्ण

	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
				      7471 * blue) >> 16;

	temp = i810_पढ़ोb(PIXCONF1, mmio);
	i810_ग_लिखोb(PIXCONF1, mmio, temp & ~EXTENDED_PALETTE);

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR && 
	    info->var.green.length == 5) अणु
		क्रम (i = 0; i < 8; i++) 
			i810_ग_लिखो_dac((u8) (regno * 8) + i, (u8) red, 
				       (u8) green, (u8) blue, mmio);
	पूर्ण अन्यथा अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR && 
		 info->var.green.length == 6) अणु
		u8 r, g, b;

		अगर (regno < 32) अणु
			क्रम (i = 0; i < 8; i++) 
				i810_ग_लिखो_dac((u8) (regno * 8) + i,
					       (u8) red, (u8) green, 
					       (u8) blue, mmio);
		पूर्ण
		i810_पढ़ो_dac((u8) (regno*4), &r, &g, &b, mmio);
		क्रम (i = 0; i < 4; i++) 
			i810_ग_लिखो_dac((u8) (regno*4) + i, r, (u8) green, 
				       b, mmio);
	पूर्ण अन्यथा अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) अणु
		i810_ग_लिखो_dac((u8) regno, (u8) red, (u8) green,
			       (u8) blue, mmio);
	पूर्ण

	i810_ग_लिखोb(PIXCONF1, mmio, temp);

	अगर (regno < 16) अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 16:	
			अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
				अगर (info->var.green.length == 5) 
					((u32 *)info->pseuकरो_palette)[regno] = 
						(regno << 10) | (regno << 5) |
						regno;
				अन्यथा
					((u32 *)info->pseuकरो_palette)[regno] = 
						(regno << 11) | (regno << 5) |
						regno;
			पूर्ण अन्यथा अणु
				अगर (info->var.green.length == 5) अणु
					/* RGB 555 */
					((u32 *)info->pseuकरो_palette)[regno] = 
						((red & 0xf800) >> 1) |
						((green & 0xf800) >> 6) |
						((blue & 0xf800) >> 11);
				पूर्ण अन्यथा अणु
					/* RGB 565 */
					((u32 *)info->pseuकरो_palette)[regno] =
						(red & 0xf800) |
						((green & 0xf800) >> 5) |
						((blue & 0xf800) >> 11);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 24:	/* RGB 888 */
		हाल 32:	/* RGBA 8888 */
			अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR) 
				((u32 *)info->pseuकरो_palette)[regno] = 
					(regno << 16) | (regno << 8) |
					regno;
			अन्यथा 
				((u32 *)info->pseuकरो_palette)[regno] = 
					((red & 0xff00) << 8) |
					(green & 0xff00) |
					((blue & 0xff00) >> 8);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_pan_display(काष्ठा fb_var_screeninfo *var, 
			      काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u32 total;
	
	total = var->xoffset * par->depth + 
		var->yoffset * info->fix.line_length;
	i810fb_load_front(total, info);

	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_blank (पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;
	पूर्णांक mode = 0, pwr, scr_off = 0;
	
	pwr = i810_पढ़ोl(PWR_CLKC, mmio);

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		mode = POWERON;
		pwr |= 1;
		scr_off = ON;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		mode = POWERON;
		pwr |= 1;
		scr_off = OFF;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		mode = STANDBY;
		pwr |= 1;
		scr_off = OFF;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		mode = SUSPEND;
		pwr |= 1;
		scr_off = OFF;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		mode = POWERDOWN;
		pwr &= ~1;
		scr_off = OFF;
		अवरोध;
	शेष:
		वापस -EINVAL; 
	पूर्ण

	i810_screen_off(mmio, scr_off);
	i810_ग_लिखोl(HVSYNC, mmio, mode);
	i810_ग_लिखोl(PWR_CLKC, mmio, pwr);

	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;

	decode_var(&info->var, par);
	i810_load_regs(par);
	i810_init_cursor(par);
	encode_fix(&info->fix, info);

	अगर (info->var.accel_flags && !(par->dev_flags & LOCKUP)) अणु
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN |
		FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
		FBINFO_HWACCEL_IMAGEBLIT;
		info->pixmap.scan_align = 2;
	पूर्ण अन्यथा अणु
		info->pixmap.scan_align = 1;
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_check_var(काष्ठा fb_var_screeninfo *var, 
			    काष्ठा fb_info *info)
अणु
	पूर्णांक err;

	अगर (IS_DVT) अणु
		var->vmode &= ~FB_VMODE_MASK;
		var->vmode |= FB_VMODE_NONINTERLACED;
	पूर्ण
	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		var->vmode &= ~FB_VMODE_MASK;
		var->vmode |= FB_VMODE_NONINTERLACED;
	पूर्ण

	i810_round_off(var);
	अगर ((err = i810_check_params(var, info)))
		वापस err;

	i810fb_fill_var_timings(var);
	set_color_bitfields(var);
	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा i810fb_par *par = info->par;
	u8 __iomem *mmio = par->mmio_start_भव;

	अगर (par->dev_flags & LOCKUP)
		वापस -ENXIO;

	अगर (cursor->image.width > 64 || cursor->image.height > 64)
		वापस -ENXIO;

	अगर ((i810_पढ़ोl(CURBASE, mmio) & 0xf) != par->cursor_heap.physical) अणु
		i810_init_cursor(par);
		cursor->set |= FB_CUR_SETALL;
	पूर्ण

	i810_enable_cursor(mmio, OFF);

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		u32 पंचांगp;

		पंचांगp = (cursor->image.dx - info->var.xoffset) & 0xffff;
		पंचांगp |= (cursor->image.dy - info->var.yoffset) << 16;
		i810_ग_लिखोl(CURPOS, mmio, पंचांगp);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSIZE)
		i810_reset_cursor_image(par);

	अगर (cursor->set & FB_CUR_SETCMAP)
		i810_load_cursor_colors(cursor->image.fg_color,
					cursor->image.bg_color,
					info);

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		पूर्णांक size = ((cursor->image.width + 7) >> 3) *
			cursor->image.height;
		पूर्णांक i;
		u8 *data = kदो_स्मृति(64 * 8, GFP_ATOMIC);

		अगर (data == शून्य)
			वापस -ENOMEM;

		चयन (cursor->rop) अणु
		हाल ROP_XOR:
			क्रम (i = 0; i < size; i++)
				data[i] = cursor->image.data[i] ^ cursor->mask[i];
			अवरोध;
		हाल ROP_COPY:
		शेष:
			क्रम (i = 0; i < size; i++)
				data[i] = cursor->image.data[i] & cursor->mask[i];
			अवरोध;
		पूर्ण

		i810_load_cursor_image(cursor->image.width,
				       cursor->image.height, data,
				       par);
		kमुक्त(data);
	पूर्ण

	अगर (cursor->enable)
		i810_enable_cursor(mmio, ON);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops i810fb_ops = अणु
	.owner =             THIS_MODULE,
	.fb_खोलो =           i810fb_खोलो,
	.fb_release =        i810fb_release,
	.fb_check_var =      i810fb_check_var,
	.fb_set_par =        i810fb_set_par,
	.fb_setcolreg =      i810fb_setcolreg,
	.fb_blank =          i810fb_blank,
	.fb_pan_display =    i810fb_pan_display, 
	.fb_fillrect =       i810fb_fillrect,
	.fb_copyarea =       i810fb_copyarea,
	.fb_imageblit =      i810fb_imageblit,
	.fb_cursor =         i810fb_cursor,
	.fb_sync =           i810fb_sync,
पूर्ण;

/***********************************************************************
 *                         Power Management                            *
 ***********************************************************************/
अटल पूर्णांक i810fb_suspend(काष्ठा pci_dev *dev, pm_message_t mesg)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा i810fb_par *par = info->par;

	par->cur_state = mesg.event;

	चयन (mesg.event) अणु
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_PRETHAW:
		dev->dev.घातer.घातer_state = mesg;
		वापस 0;
	पूर्ण

	console_lock();
	fb_set_suspend(info, 1);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	i810fb_blank(FB_BLANK_POWERDOWN, info);
	agp_unbind_memory(par->i810_gtt.i810_fb_memory);
	agp_unbind_memory(par->i810_gtt.i810_cursor_memory);

	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_घातer_state(dev, pci_choose_state(dev, mesg));
	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक i810fb_resume(काष्ठा pci_dev *dev) 
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा i810fb_par *par = info->par;
	पूर्णांक cur_state = par->cur_state;

	par->cur_state = PM_EVENT_ON;

	अगर (cur_state == PM_EVENT_FREEZE) अणु
		pci_set_घातer_state(dev, PCI_D0);
		वापस 0;
	पूर्ण

	console_lock();
	pci_set_घातer_state(dev, PCI_D0);
	pci_restore_state(dev);

	अगर (pci_enable_device(dev))
		जाओ fail;

	pci_set_master(dev);
	agp_bind_memory(par->i810_gtt.i810_fb_memory,
			par->fb.offset);
	agp_bind_memory(par->i810_gtt.i810_cursor_memory,
			par->cursor_heap.offset);
	i810fb_set_par(info);
	fb_set_suspend (info, 0);
	info->fbops->fb_blank(VESA_NO_BLANKING, info);
fail:
	console_unlock();
	वापस 0;
पूर्ण
/***********************************************************************
 *                  AGP resource allocation                            *
 ***********************************************************************/
  
अटल व्योम i810_fix_poपूर्णांकers(काष्ठा i810fb_par *par)
अणु
      	par->fb.physical = par->aperture.physical+(par->fb.offset << 12);
	par->fb.भव = par->aperture.भव+(par->fb.offset << 12);
	par->iring.physical = par->aperture.physical + 
		(par->iring.offset << 12);
	par->iring.भव = par->aperture.भव + 
		(par->iring.offset << 12);
	par->cursor_heap.भव = par->aperture.भव+
		(par->cursor_heap.offset << 12);
पूर्ण

अटल व्योम i810_fix_offsets(काष्ठा i810fb_par *par)
अणु
	अगर (vram + 1 > par->aperture.size >> 20)
		vram = (par->aperture.size >> 20) - 1;
	अगर (v_offset_शेष > (par->aperture.size >> 20))
		v_offset_शेष = (par->aperture.size >> 20);
	अगर (vram + v_offset_शेष + 1 > par->aperture.size >> 20)
		v_offset_शेष = (par->aperture.size >> 20) - (vram + 1);

	par->fb.size = vram << 20;
	par->fb.offset = v_offset_शेष << 20;
	par->fb.offset >>= 12;

	par->iring.offset = par->fb.offset + (par->fb.size >> 12);
	par->iring.size = RINGBUFFER_SIZE;

	par->cursor_heap.offset = par->iring.offset + (RINGBUFFER_SIZE >> 12);
	par->cursor_heap.size = 4096;
पूर्ण

अटल पूर्णांक i810_alloc_agp_mem(काष्ठा fb_info *info)
अणु
	काष्ठा i810fb_par *par = info->par;
	पूर्णांक size;
	काष्ठा agp_bridge_data *bridge;
	
	i810_fix_offsets(par);
	size = par->fb.size + par->iring.size;

	अगर (!(bridge = agp_backend_acquire(par->dev))) अणु
		prपूर्णांकk("i810fb_alloc_fbmem: cannot acquire agpgart\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!(par->i810_gtt.i810_fb_memory = 
	      agp_allocate_memory(bridge, size >> 12, AGP_NORMAL_MEMORY))) अणु
		prपूर्णांकk("i810fb_alloc_fbmem: can't allocate framebuffer "
		       "memory\n");
		agp_backend_release(bridge);
		वापस -ENOMEM;
	पूर्ण
	अगर (agp_bind_memory(par->i810_gtt.i810_fb_memory,
			    par->fb.offset)) अणु
		prपूर्णांकk("i810fb_alloc_fbmem: can't bind framebuffer memory\n");
		agp_backend_release(bridge);
		वापस -EBUSY;
	पूर्ण	
	
	अगर (!(par->i810_gtt.i810_cursor_memory = 
	      agp_allocate_memory(bridge, par->cursor_heap.size >> 12,
				  AGP_PHYSICAL_MEMORY))) अणु
		prपूर्णांकk("i810fb_alloc_cursormem:  can't allocate "
		       "cursor memory\n");
		agp_backend_release(bridge);
		वापस -ENOMEM;
	पूर्ण
	अगर (agp_bind_memory(par->i810_gtt.i810_cursor_memory,
			    par->cursor_heap.offset)) अणु
		prपूर्णांकk("i810fb_alloc_cursormem: cannot bind cursor memory\n");
		agp_backend_release(bridge);
		वापस -EBUSY;
	पूर्ण	

	par->cursor_heap.physical = par->i810_gtt.i810_cursor_memory->physical;

	i810_fix_poपूर्णांकers(par);

	agp_backend_release(bridge);

	वापस 0;
पूर्ण

/*************************************************************** 
 *                    Initialization                           * 
 ***************************************************************/

/**
 * i810_init_monspecs
 * @info: poपूर्णांकer to device specअगरic info काष्ठाure
 *
 * DESCRIPTION:
 * Sets the user monitor's horizontal and vertical
 * frequency limits
 */
अटल व्योम i810_init_monspecs(काष्ठा fb_info *info)
अणु
	अगर (!hsync1)
		hsync1 = HFMIN;
	अगर (!hsync2) 
		hsync2 = HFMAX;
	अगर (!info->monspecs.hfmax)
		info->monspecs.hfmax = hsync2;
	अगर (!info->monspecs.hfmin)
		info->monspecs.hfmin = hsync1;
	अगर (hsync2 < hsync1)
		info->monspecs.hfmin = hsync2;

	अगर (!vsync1)
		vsync1 = VFMIN;
	अगर (!vsync2) 
		vsync2 = VFMAX;
	अगर (IS_DVT && vsync1 < 60)
		vsync1 = 60;
	अगर (!info->monspecs.vfmax)
		info->monspecs.vfmax = vsync2;
	अगर (!info->monspecs.vfmin)
		info->monspecs.vfmin = vsync1;
	अगर (vsync2 < vsync1) 
		info->monspecs.vfmin = vsync2;
पूर्ण

/**
 * i810_init_शेषs - initializes शेष values to use
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 * @info: poपूर्णांकer to current fb_info काष्ठाure
 */
अटल व्योम i810_init_शेषs(काष्ठा i810fb_par *par, काष्ठा fb_info *info)
अणु
	mutex_init(&par->खोलो_lock);

	अगर (voffset) 
		v_offset_शेष = voffset;
	अन्यथा अगर (par->aperture.size > 32 * 1024 * 1024)
		v_offset_शेष = 16;
	अन्यथा
		v_offset_शेष = 8;

	अगर (!vram) 
		vram = 1;

	अगर (accel) 
		par->dev_flags |= HAS_ACCELERATION;

	अगर (sync) 
		par->dev_flags |= ALWAYS_SYNC;

	par->ddc_num = (ddc3 ? 3 : 2);

	अगर (bpp < 8)
		bpp = 8;
	
	par->i810fb_ops = i810fb_ops;

	अगर (xres)
		info->var.xres = xres;
	अन्यथा
		info->var.xres = 640;

	अगर (yres)
		info->var.yres = yres;
	अन्यथा
		info->var.yres = 480;

	अगर (!vyres) 
		vyres = (vram << 20)/(info->var.xres*bpp >> 3);

	info->var.yres_भव = vyres;
	info->var.bits_per_pixel = bpp;

	अगर (dcolor)
		info->var.nonstd = 1;

	अगर (par->dev_flags & HAS_ACCELERATION) 
		info->var.accel_flags = 1;

	i810_init_monspecs(info);
पूर्ण
	
/**
 * i810_init_device - initialize device
 * @par: poपूर्णांकer to i810fb_par काष्ठाure
 */
अटल व्योम i810_init_device(काष्ठा i810fb_par *par)
अणु
	u8 reg;
	u8 __iomem *mmio = par->mmio_start_भव;

	अगर (mtrr)
		par->wc_cookie= arch_phys_wc_add((u32) par->aperture.physical,
						 par->aperture.size);

	i810_init_cursor(par);

	/* mvo: enable बाह्यal vga-connector (क्रम laptops) */
	अगर (extvga) अणु
		i810_ग_लिखोl(HVSYNC, mmio, 0);
		i810_ग_लिखोl(PWR_CLKC, mmio, 3);
	पूर्ण

	pci_पढ़ो_config_byte(par->dev, 0x50, &reg);
	reg &= FREQ_MASK;
	par->mem_freq = (reg) ? 133 : 100;

पूर्ण

अटल पूर्णांक i810_allocate_pci_resource(काष्ठा i810fb_par *par,
				      स्थिर काष्ठा pci_device_id *entry)
अणु
	पूर्णांक err;

	अगर ((err = pci_enable_device(par->dev))) अणु 
		prपूर्णांकk("i810fb_init: cannot enable device\n");
		वापस err;		
	पूर्ण
	par->res_flags |= PCI_DEVICE_ENABLED;

	अगर (pci_resource_len(par->dev, 0) > 512 * 1024) अणु
		par->aperture.physical = pci_resource_start(par->dev, 0);
		par->aperture.size = pci_resource_len(par->dev, 0);
		par->mmio_start_phys = pci_resource_start(par->dev, 1);
	पूर्ण अन्यथा अणु
		par->aperture.physical = pci_resource_start(par->dev, 1);
		par->aperture.size = pci_resource_len(par->dev, 1);
		par->mmio_start_phys = pci_resource_start(par->dev, 0);
	पूर्ण
	अगर (!par->aperture.size) अणु
		prपूर्णांकk("i810fb_init: device is disabled\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!request_mem_region(par->aperture.physical, 
				par->aperture.size, 
				i810_pci_list[entry->driver_data])) अणु
		prपूर्णांकk("i810fb_init: cannot request framebuffer region\n");
		वापस -ENODEV;
	पूर्ण
	par->res_flags |= FRAMEBUFFER_REQ;

	par->aperture.भव = ioremap_wc(par->aperture.physical,
					   par->aperture.size);
	अगर (!par->aperture.भव) अणु
		prपूर्णांकk("i810fb_init: cannot remap framebuffer region\n");
		वापस -ENODEV;
	पूर्ण
  
	अगर (!request_mem_region(par->mmio_start_phys, 
				MMIO_SIZE, 
				i810_pci_list[entry->driver_data])) अणु
		prपूर्णांकk("i810fb_init: cannot request mmio region\n");
		वापस -ENODEV;
	पूर्ण
	par->res_flags |= MMIO_REQ;

	par->mmio_start_भव = ioremap(par->mmio_start_phys, 
						  MMIO_SIZE);
	अगर (!par->mmio_start_भव) अणु
		prपूर्णांकk("i810fb_init: cannot remap mmio region\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i810fb_find_init_mode(काष्ठा fb_info *info)
अणु
	काष्ठा fb_videomode mode;
	काष्ठा fb_var_screeninfo var;
	काष्ठा fb_monspecs *specs = &info->monspecs;
	पूर्णांक found = 0;
#अगर_घोषित CONFIG_FB_I810_I2C
	पूर्णांक i;
	पूर्णांक err = 1;
	काष्ठा i810fb_par *par = info->par;
#पूर्ण_अगर

	INIT_LIST_HEAD(&info->modelist);
	स_रखो(&mode, 0, माप(काष्ठा fb_videomode));
	var = info->var;
#अगर_घोषित CONFIG_FB_I810_I2C
	i810_create_i2c_busses(par);

	क्रम (i = 0; i < par->ddc_num + 1; i++) अणु
		err = i810_probe_i2c_connector(info, &par->edid, i);
		अगर (!err)
			अवरोध;
	पूर्ण

	अगर (!err)
		prपूर्णांकk("i810fb_init_pci: DDC probe successful\n");

	fb_edid_to_monspecs(par->edid, specs);

	अगर (specs->modedb == शून्य)
		prपूर्णांकk("i810fb_init_pci: Unable to get Mode Database\n");

	fb_videomode_to_modelist(specs->modedb, specs->modedb_len,
				 &info->modelist);
	अगर (specs->modedb != शून्य) अणु
		स्थिर काष्ठा fb_videomode *m;

		अगर (xres && yres) अणु
			अगर ((m = fb_find_best_mode(&var, &info->modelist))) अणु
				mode = *m;
				found  = 1;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			m = fb_find_best_display(&info->monspecs, &info->modelist);
			mode = *m;
			found = 1;
		पूर्ण

		fb_videomode_to_var(&var, &mode);
	पूर्ण
#पूर्ण_अगर
	अगर (mode_option)
		fb_find_mode(&var, info, mode_option, specs->modedb,
			     specs->modedb_len, (found) ? &mode : शून्य,
			     info->var.bits_per_pixel);

	info->var = var;
	fb_destroy_modedb(specs->modedb);
	specs->modedb = शून्य;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक i810fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt, *suffix = शून्य;

	अगर (!options || !*options)
		वापस 0;
	
	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "mtrr", 4))
			mtrr = true;
		अन्यथा अगर (!म_भेदन(this_opt, "accel", 5))
			accel = true;
		अन्यथा अगर (!म_भेदन(this_opt, "extvga", 6))
			extvga = true;
		अन्यथा अगर (!म_भेदन(this_opt, "sync", 4))
			sync = true;
		अन्यथा अगर (!म_भेदन(this_opt, "vram:", 5))
			vram = (simple_म_से_अदीर्घ(this_opt+5, शून्य, 0));
		अन्यथा अगर (!म_भेदन(this_opt, "voffset:", 8))
			voffset = (simple_म_से_अदीर्घ(this_opt+8, शून्य, 0));
		अन्यथा अगर (!म_भेदन(this_opt, "xres:", 5))
			xres = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "yres:", 5))
			yres = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vyres:", 6))
			vyres = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "bpp:", 4))
			bpp = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "hsync1:", 7)) अणु
			hsync1 = simple_म_से_अदीर्घ(this_opt+7, &suffix, 0);
			अगर (म_भेदन(suffix, "H", 1)) 
				hsync1 *= 1000;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "hsync2:", 7)) अणु
			hsync2 = simple_म_से_अदीर्घ(this_opt+7, &suffix, 0);
			अगर (म_भेदन(suffix, "H", 1)) 
				hsync2 *= 1000;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "vsync1:", 7)) 
			vsync1 = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vsync2:", 7))
			vsync2 = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "dcolor", 6))
			dcolor = true;
		अन्यथा अगर (!म_भेदन(this_opt, "ddc3", 4))
			ddc3 = true;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक i810fb_init_pci(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा fb_info    *info;
	काष्ठा i810fb_par *par = शून्य;
	काष्ठा fb_videomode mode;
	पूर्णांक err = -1, vfreq, hfreq, pixघड़ी;

	info = framebuffer_alloc(माप(काष्ठा i810fb_par), &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->dev = dev;

	अगर (!(info->pixmap.addr = kzalloc(8*1024, GFP_KERNEL))) अणु
		i810fb_release_resource(info, par);
		वापस -ENOMEM;
	पूर्ण
	info->pixmap.size = 8*1024;
	info->pixmap.buf_align = 8;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	अगर ((err = i810_allocate_pci_resource(par, entry))) अणु
		i810fb_release_resource(info, par);
		वापस err;
	पूर्ण

	i810_init_शेषs(par, info);

	अगर ((err = i810_alloc_agp_mem(info))) अणु
		i810fb_release_resource(info, par);
		वापस err;
	पूर्ण

	i810_init_device(par);        

	info->screen_base = par->fb.भव;
	info->fbops = &par->i810fb_ops;
	info->pseuकरो_palette = par->pseuकरो_palette;
	fb_alloc_cmap(&info->cmap, 256, 0);
	i810fb_find_init_mode(info);

	अगर ((err = info->fbops->fb_check_var(&info->var, info))) अणु
		i810fb_release_resource(info, par);
		वापस err;
	पूर्ण

	fb_var_to_videomode(&mode, &info->var);
	fb_add_videomode(&mode, &info->modelist);

	i810fb_init_ringbuffer(info);
	err = रेजिस्टर_framebuffer(info);

	अगर (err < 0) अणु
    		i810fb_release_resource(info, par); 
		prपूर्णांकk("i810fb_init: cannot register framebuffer device\n");
    		वापस err;  
    	पूर्ण   

	pci_set_drvdata(dev, info);
	pixघड़ी = 1000000000/(info->var.pixघड़ी);
	pixघड़ी *= 1000;
	hfreq = pixघड़ी/(info->var.xres + info->var.left_margin + 
			  info->var.hsync_len + info->var.right_margin);
	vfreq = hfreq/(info->var.yres + info->var.upper_margin +
		       info->var.vsync_len + info->var.lower_margin);

      	prपूर्णांकk("I810FB: fb%d         : %s v%d.%d.%d%s\n"
      	       "I810FB: Video RAM   : %dK\n" 
	       "I810FB: Monitor     : H: %d-%d KHz V: %d-%d Hz\n"
	       "I810FB: Mode        : %dx%d-%dbpp@%dHz\n",
	       info->node,
	       i810_pci_list[entry->driver_data],
	       VERSION_MAJOR, VERSION_MINOR, VERSION_TEENIE, BRANCH_VERSION,
	       (पूर्णांक) par->fb.size>>10, info->monspecs.hfmin/1000,
	       info->monspecs.hfmax/1000, info->monspecs.vfmin,
	       info->monspecs.vfmax, info->var.xres, 
	       info->var.yres, info->var.bits_per_pixel, vfreq);
	वापस 0;
पूर्ण

/***************************************************************
 *                     De-initialization                        *
 ***************************************************************/

अटल व्योम i810fb_release_resource(काष्ठा fb_info *info, 
				    काष्ठा i810fb_par *par)
अणु
	काष्ठा gtt_data *gtt = &par->i810_gtt;
	arch_phys_wc_del(par->wc_cookie);

	i810_delete_i2c_busses(par);

	अगर (par->i810_gtt.i810_cursor_memory)
		agp_मुक्त_memory(gtt->i810_cursor_memory);
	अगर (par->i810_gtt.i810_fb_memory)
		agp_मुक्त_memory(gtt->i810_fb_memory);

	अगर (par->mmio_start_भव)
		iounmap(par->mmio_start_भव);
	अगर (par->aperture.भव)
		iounmap(par->aperture.भव);
	kमुक्त(par->edid);
	अगर (par->res_flags & FRAMEBUFFER_REQ)
		release_mem_region(par->aperture.physical,
				   par->aperture.size);
	अगर (par->res_flags & MMIO_REQ)
		release_mem_region(par->mmio_start_phys, MMIO_SIZE);

	framebuffer_release(info);

पूर्ण

अटल व्योम i810fb_हटाओ_pci(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा i810fb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);  
	i810fb_release_resource(info, par);
	prपूर्णांकk("cleanup_module:  unloaded i810 framebuffer device\n");
पूर्ण                                                	

#अगर_अघोषित MODULE
अटल पूर्णांक i810fb_init(व्योम)
अणु
	अक्षर *option = शून्य;

	अगर (fb_get_options("i810fb", &option))
		वापस -ENODEV;
	i810fb_setup(option);

	वापस pci_रेजिस्टर_driver(&i810fb_driver);
पूर्ण
#पूर्ण_अगर 

/*********************************************************************
 *                          Modularization                           *
 *********************************************************************/

#अगर_घोषित MODULE

अटल पूर्णांक i810fb_init(व्योम)
अणु
	hsync1 *= 1000;
	hsync2 *= 1000;

	वापस pci_रेजिस्टर_driver(&i810fb_driver);
पूर्ण

module_param(vram, पूर्णांक, 0);
MODULE_PARM_DESC(vram, "System RAM to allocate to framebuffer in MiB" 
		 " (default=4)");
module_param(voffset, पूर्णांक, 0);
MODULE_PARM_DESC(voffset, "at what offset to place start of framebuffer "
                 "memory (0 to maximum aperture size), in MiB (default = 48)");
module_param(bpp, पूर्णांक, 0);
MODULE_PARM_DESC(bpp, "Color depth for display in bits per pixel"
		 " (default = 8)");
module_param(xres, पूर्णांक, 0);
MODULE_PARM_DESC(xres, "Horizontal resolution in pixels (default = 640)");
module_param(yres, पूर्णांक, 0);
MODULE_PARM_DESC(yres, "Vertical resolution in scanlines (default = 480)");
module_param(vyres,पूर्णांक, 0);
MODULE_PARM_DESC(vyres, "Virtual vertical resolution in scanlines"
		 " (default = 480)");
module_param(hsync1, पूर्णांक, 0);
MODULE_PARM_DESC(hsync1, "Minimum horizontal frequency of monitor in KHz"
		 " (default = 29)");
module_param(hsync2, पूर्णांक, 0);
MODULE_PARM_DESC(hsync2, "Maximum horizontal frequency of monitor in KHz"
		 " (default = 30)");
module_param(vsync1, पूर्णांक, 0);
MODULE_PARM_DESC(vsync1, "Minimum vertical frequency of monitor in Hz"
		 " (default = 50)");
module_param(vsync2, पूर्णांक, 0);
MODULE_PARM_DESC(vsync2, "Maximum vertical frequency of monitor in Hz" 
		 " (default = 60)");
module_param(accel, bool, 0);
MODULE_PARM_DESC(accel, "Use Acceleration (BLIT) engine (default = 0)");
module_param(mtrr, bool, 0);
MODULE_PARM_DESC(mtrr, "Use MTRR (default = 0)");
module_param(extvga, bool, 0);
MODULE_PARM_DESC(extvga, "Enable external VGA connector (default = 0)");
module_param(sync, bool, 0);
MODULE_PARM_DESC(sync, "wait for accel engine to finish drawing"
		 " (default = 0)");
module_param(dcolor, bool, 0);
MODULE_PARM_DESC(dcolor, "use DirectColor visuals"
		 " (default = 0 = TrueColor)");
module_param(ddc3, bool, 0);
MODULE_PARM_DESC(ddc3, "Probe DDC bus 3 (default = 0 = no)");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify initial video mode");

MODULE_AUTHOR("Tony A. Daplas");
MODULE_DESCRIPTION("Framebuffer device for the Intel 810/815 and"
		   " compatible cards");
MODULE_LICENSE("GPL"); 

अटल व्योम __निकास i810fb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i810fb_driver);
पूर्ण
module_निकास(i810fb_निकास);

#पूर्ण_अगर /* MODULE */

module_init(i810fb_init);
