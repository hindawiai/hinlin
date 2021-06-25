<शैली गुरु>
/*
 *	drivers/video/aty/radeon_base.c
 *
 *	framebuffer driver क्रम ATI Radeon chipset video boards
 *
 *	Copyright 2003	Ben. Herrenschmidt <benh@kernel.crashing.org>
 *	Copyright 2000	Ani Joshi <ajoshi@kernel.crashing.org>
 *
 *	i2c bits from Luca Tettamanti <kronos@kronoz.cjb.net>
 *	
 *	Special thanks to ATI DevRel team क्रम their hardware करोnations.
 *
 *	...Insert GPL boilerplate here...
 *
 *	Signअगरicant portions of this driver apdated from XFree86 Radeon
 *	driver which has the following copyright notice:
 *
 *	Copyright 2000 ATI Technologies Inc., Markham, Ontario, and
 *                     VA Linux Systems Inc., Fremont, Calअगरornia.
 *
 *	All Rights Reserved.
 *
 *	Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 *	a copy of this software and associated करोcumentation files (the
 *	"Software"), to deal in the Software without restriction, including
 *	without limitation on the rights to use, copy, modअगरy, merge,
 *	publish, distribute, sublicense, and/or sell copies of the Software,
 *	and to permit persons to whom the Software is furnished to करो so,
 *	subject to the following conditions:
 *
 *	The above copyright notice and this permission notice (including the
 *	next paragraph) shall be included in all copies or substantial
 *	portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * 	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NON-INFRINGEMENT.  IN NO EVENT SHALL ATI, VA LINUX SYSTEMS AND/OR
 *	THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *	DEALINGS IN THE SOFTWARE.
 *
 *	XFree86 driver authors:
 *
 *	   Kevin E. Martin <martin@xमुक्त86.org>
 *	   Rickard E. Faith <faith@valinux.com>
 *	   Alan Hourihane <alanh@fairlite.demon.co.uk>
 *
 */


#घोषणा RADEON_VERSION	"0.2.0"

#समावेश "radeonfb.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_PPC

#समावेश "../macmodes.h"

#अगर_घोषित CONFIG_BOOTX_TEXT
#समावेश <यंत्र/btext.h>
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PPC */

#समावेश <video/radeon.h>
#समावेश <linux/radeonfb.h>

#समावेश "../edid.h" // MOVE THAT TO include/video
#समावेश "ati_ids.h"

#घोषणा MAX_MAPPED_VRAM	(2048*2048*4)
#घोषणा MIN_MAPPED_VRAM	(1024*768*1)

#घोषणा CHIP_DEF(id, family, flags)					\
	अणु PCI_VENDOR_ID_ATI, id, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (flags) | (CHIP_FAMILY_##family) पूर्ण

अटल स्थिर काष्ठा pci_device_id radeonfb_pci_table[] = अणु
        /* Radeon Xpress 200m */
	CHIP_DEF(PCI_CHIP_RS480_5955,   RS480,  CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RS482_5975,	RS480,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* Mobility M6 */
	CHIP_DEF(PCI_CHIP_RADEON_LY, 	RV100,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RADEON_LZ,	RV100,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	/* Radeon VE/7000 */
	CHIP_DEF(PCI_CHIP_RV100_QY, 	RV100,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV100_QZ, 	RV100,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RN50,		RV100,	CHIP_HAS_CRTC2),
	/* Radeon IGP320M (U1) */
	CHIP_DEF(PCI_CHIP_RS100_4336,	RS100,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* Radeon IGP320 (A3) */
	CHIP_DEF(PCI_CHIP_RS100_4136,	RS100,	CHIP_HAS_CRTC2 | CHIP_IS_IGP), 
	/* IGP330M/340M/350M (U2) */
	CHIP_DEF(PCI_CHIP_RS200_4337,	RS200,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* IGP330/340/350 (A4) */
	CHIP_DEF(PCI_CHIP_RS200_4137,	RS200,	CHIP_HAS_CRTC2 | CHIP_IS_IGP),
	/* Mobility 7000 IGP */
	CHIP_DEF(PCI_CHIP_RS250_4437,	RS200,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* 7000 IGP (A4+) */
	CHIP_DEF(PCI_CHIP_RS250_4237,	RS200,	CHIP_HAS_CRTC2 | CHIP_IS_IGP),
	/* 8500 AIW */
	CHIP_DEF(PCI_CHIP_R200_BB,	R200,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R200_BC,	R200,	CHIP_HAS_CRTC2),
	/* 8700/8800 */
	CHIP_DEF(PCI_CHIP_R200_QH,	R200,	CHIP_HAS_CRTC2),
	/* 8500 */
	CHIP_DEF(PCI_CHIP_R200_QL,	R200,	CHIP_HAS_CRTC2),
	/* 9100 */
	CHIP_DEF(PCI_CHIP_R200_QM,	R200,	CHIP_HAS_CRTC2),
	/* Mobility M7 */
	CHIP_DEF(PCI_CHIP_RADEON_LW,	RV200,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RADEON_LX,	RV200,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	/* 7500 */
	CHIP_DEF(PCI_CHIP_RV200_QW,	RV200,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV200_QX,	RV200,	CHIP_HAS_CRTC2),
	/* Mobility M9 */
	CHIP_DEF(PCI_CHIP_RV250_Ld,	RV250,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV250_Le,	RV250,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV250_Lf,	RV250,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV250_Lg,	RV250,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	/* 9000/Pro */
	CHIP_DEF(PCI_CHIP_RV250_If,	RV250,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV250_Ig,	RV250,	CHIP_HAS_CRTC2),

	CHIP_DEF(PCI_CHIP_RC410_5A62,   RC410,  CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* Mobility 9100 IGP (U3) */
	CHIP_DEF(PCI_CHIP_RS300_5835,	RS300,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RS350_7835,	RS300,	CHIP_HAS_CRTC2 | CHIP_IS_IGP | CHIP_IS_MOBILITY),
	/* 9100 IGP (A5) */
	CHIP_DEF(PCI_CHIP_RS300_5834,	RS300,	CHIP_HAS_CRTC2 | CHIP_IS_IGP),
	CHIP_DEF(PCI_CHIP_RS350_7834,	RS300,	CHIP_HAS_CRTC2 | CHIP_IS_IGP),
	/* Mobility 9200 (M9+) */
	CHIP_DEF(PCI_CHIP_RV280_5C61,	RV280,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV280_5C63,	RV280,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	/* 9200 */
	CHIP_DEF(PCI_CHIP_RV280_5960,	RV280,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV280_5961,	RV280,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV280_5962,	RV280,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV280_5964,	RV280,	CHIP_HAS_CRTC2),
	/* 9500 */
	CHIP_DEF(PCI_CHIP_R300_AD,	R300,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R300_AE,	R300,	CHIP_HAS_CRTC2),
	/* 9600TX / FireGL Z1 */
	CHIP_DEF(PCI_CHIP_R300_AF,	R300,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R300_AG,	R300,	CHIP_HAS_CRTC2),
	/* 9700/9500/Pro/FireGL X1 */
	CHIP_DEF(PCI_CHIP_R300_ND,	R300,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R300_NE,	R300,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R300_NF,	R300,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R300_NG,	R300,	CHIP_HAS_CRTC2),
	/* Mobility M10/M11 */
	CHIP_DEF(PCI_CHIP_RV350_NP,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV350_NQ,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV350_NR,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV350_NS,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV350_NT,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV350_NV,	RV350,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	/* 9600/FireGL T2 */
	CHIP_DEF(PCI_CHIP_RV350_AP,	RV350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV350_AQ,	RV350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV360_AR,	RV350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV350_AS,	RV350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV350_AT,	RV350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV350_AV,	RV350,	CHIP_HAS_CRTC2),
	/* 9800/Pro/FileGL X2 */
	CHIP_DEF(PCI_CHIP_R350_AH,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_AI,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_AJ,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_AK,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_NH,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_NI,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R360_NJ,	R350,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R350_NK,	R350,	CHIP_HAS_CRTC2),
	/* Newer stuff */
	CHIP_DEF(PCI_CHIP_RV380_3E50,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV380_3E54,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV380_3150,	RV380,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV380_3154,	RV380,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV370_5B60,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV370_5B62,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV370_5B63,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV370_5B64,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV370_5B65,	RV380,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_RV370_5460,	RV380,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_RV370_5464,	RV380,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_R420_JH,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JI,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JJ,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JK,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JL,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JM,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R420_JN,	R420,	CHIP_HAS_CRTC2 | CHIP_IS_MOBILITY),
	CHIP_DEF(PCI_CHIP_R420_JP,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UH,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UI,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UJ,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UK,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UQ,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UR,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_UT,	R420,	CHIP_HAS_CRTC2),
	CHIP_DEF(PCI_CHIP_R423_5D57,	R420,	CHIP_HAS_CRTC2),
	/* Original Radeon/7200 */
	CHIP_DEF(PCI_CHIP_RADEON_QD,	RADEON,	0),
	CHIP_DEF(PCI_CHIP_RADEON_QE,	RADEON,	0),
	CHIP_DEF(PCI_CHIP_RADEON_QF,	RADEON,	0),
	CHIP_DEF(PCI_CHIP_RADEON_QG,	RADEON,	0),
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, radeonfb_pci_table);


प्रकार काष्ठा अणु
	u16 reg;
	u32 val;
पूर्ण reg_val;


/* these common regs are cleared beक्रमe mode setting so they करो not
 * पूर्णांकerfere with anything
 */
अटल reg_val common_regs[] = अणु
	अणु OVR_CLR, 0 पूर्ण,	
	अणु OVR_WID_LEFT_RIGHT, 0 पूर्ण,
	अणु OVR_WID_TOP_BOTTOM, 0 पूर्ण,
	अणु OV0_SCALE_CNTL, 0 पूर्ण,
	अणु SUBPIC_CNTL, 0 पूर्ण,
	अणु VIPH_CONTROL, 0 पूर्ण,
	अणु I2C_CNTL_1, 0 पूर्ण,
	अणु GEN_INT_CNTL, 0 पूर्ण,
	अणु CAP0_TRIG_CNTL, 0 पूर्ण,
	अणु CAP1_TRIG_CNTL, 0 पूर्ण,
पूर्ण;

/*
 * globals
 */
        
अटल अक्षर *mode_option;
अटल अक्षर *monitor_layout;
अटल bool noaccel = 0;
अटल पूर्णांक शेष_dynclk = -2;
अटल bool nomodeset = 0;
अटल bool ignore_edid = 0;
अटल bool mirror = 0;
अटल पूर्णांक panel_yres = 0;
अटल bool क्रमce_dfp = 0;
अटल bool क्रमce_measure_pll = 0;
अटल bool nomtrr = 0;
अटल bool क्रमce_sleep;
अटल bool ignore_devlist;
अटल पूर्णांक backlight = IS_BUILTIN(CONFIG_PMAC_BACKLIGHT);

/* Note about this function: we have some rare हालs where we must not schedule,
 * this typically happen with our special "wake up early" hook which allows us to
 * wake up the graphic chip (and thus get the console back) beक्रमe everything अन्यथा
 * on some machines that support that mechanism. At this poपूर्णांक, पूर्णांकerrupts are off
 * and scheduling is not permitted
 */
व्योम _radeon_msleep(काष्ठा radeonfb_info *rinfo, अचिन्हित दीर्घ ms)
अणु
	अगर (rinfo->no_schedule || oops_in_progress)
		mdelay(ms);
	अन्यथा
		msleep(ms);
पूर्ण

व्योम radeon_pll_errata_after_index_slow(काष्ठा radeonfb_info *rinfo)
अणु
	/* Called अगर (rinfo->errata & CHIP_ERRATA_PLL_DUMMYREADS) is set */
	(व्योम)INREG(CLOCK_CNTL_DATA);
	(व्योम)INREG(CRTC_GEN_CNTL);
पूर्ण

व्योम radeon_pll_errata_after_data_slow(काष्ठा radeonfb_info *rinfo)
अणु
	अगर (rinfo->errata & CHIP_ERRATA_PLL_DELAY) अणु
		/* we can't deal with posted ग_लिखोs here ... */
		_radeon_msleep(rinfo, 5);
	पूर्ण
	अगर (rinfo->errata & CHIP_ERRATA_R300_CG) अणु
		u32 save, पंचांगp;
		save = INREG(CLOCK_CNTL_INDEX);
		पंचांगp = save & ~(0x3f | PLL_WR_EN);
		OUTREG(CLOCK_CNTL_INDEX, पंचांगp);
		पंचांगp = INREG(CLOCK_CNTL_DATA);
		OUTREG(CLOCK_CNTL_INDEX, save);
	पूर्ण
पूर्ण

व्योम _OUTREGP(काष्ठा radeonfb_info *rinfo, u32 addr, u32 val, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp;

	spin_lock_irqsave(&rinfo->reg_lock, flags);
	पंचांगp = INREG(addr);
	पंचांगp &= (mask);
	पंचांगp |= (val);
	OUTREG(addr, पंचांगp);
	spin_unlock_irqrestore(&rinfo->reg_lock, flags);
पूर्ण

u32 __INPLL(काष्ठा radeonfb_info *rinfo, u32 addr)
अणु
	u32 data;

	OUTREG8(CLOCK_CNTL_INDEX, addr & 0x0000003f);
	radeon_pll_errata_after_index(rinfo);
	data = INREG(CLOCK_CNTL_DATA);
	radeon_pll_errata_after_data(rinfo);
	वापस data;
पूर्ण

व्योम __OUTPLL(काष्ठा radeonfb_info *rinfo, अचिन्हित पूर्णांक index, u32 val)
अणु
	OUTREG8(CLOCK_CNTL_INDEX, (index & 0x0000003f) | 0x00000080);
	radeon_pll_errata_after_index(rinfo);
	OUTREG(CLOCK_CNTL_DATA, val);
	radeon_pll_errata_after_data(rinfo);
पूर्ण

व्योम __OUTPLLP(काष्ठा radeonfb_info *rinfo, अचिन्हित पूर्णांक index,
			     u32 val, u32 mask)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp  = __INPLL(rinfo, index);
	पंचांगp &= (mask);
	पंचांगp |= (val);
	__OUTPLL(rinfo, index, पंचांगp);
पूर्ण

व्योम _radeon_fअगरo_रुको(काष्ठा radeonfb_info *rinfo, पूर्णांक entries)
अणु
	पूर्णांक i;

	क्रम (i=0; i<2000000; i++) अणु
		अगर ((INREG(RBBM_STATUS) & 0x7f) >= entries)
			वापस;
		udelay(1);
	पूर्ण
	prपूर्णांकk(KERN_ERR "radeonfb: FIFO Timeout !\n");
पूर्ण

व्योम radeon_engine_flush(काष्ठा radeonfb_info *rinfo)
अणु
	पूर्णांक i;

	/* Initiate flush */
	OUTREGP(DSTCACHE_CTLSTAT, RB2D_DC_FLUSH_ALL,
	        ~RB2D_DC_FLUSH_ALL);

	/* Ensure FIFO is empty, ie, make sure the flush commands
	 * has reached the cache
	 */
	_radeon_fअगरo_रुको(rinfo, 64);

	/* Wait क्रम the flush to complete */
	क्रम (i=0; i < 2000000; i++) अणु
		अगर (!(INREG(DSTCACHE_CTLSTAT) & RB2D_DC_BUSY))
			वापस;
		udelay(1);
	पूर्ण
	prपूर्णांकk(KERN_ERR "radeonfb: Flush Timeout !\n");
पूर्ण

व्योम _radeon_engine_idle(काष्ठा radeonfb_info *rinfo)
अणु
	पूर्णांक i;

	/* ensure FIFO is empty beक्रमe रुकोing क्रम idle */
	_radeon_fअगरo_रुको(rinfo, 64);

	क्रम (i=0; i<2000000; i++) अणु
		अगर (((INREG(RBBM_STATUS) & GUI_ACTIVE)) == 0) अणु
			radeon_engine_flush(rinfo);
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
	prपूर्णांकk(KERN_ERR "radeonfb: Idle Timeout !\n");
पूर्ण



अटल व्योम radeon_unmap_ROM(काष्ठा radeonfb_info *rinfo, काष्ठा pci_dev *dev)
अणु
	अगर (!rinfo->bios_seg)
		वापस;
	pci_unmap_rom(dev, rinfo->bios_seg);
पूर्ण

अटल पूर्णांक radeon_map_ROM(काष्ठा radeonfb_info *rinfo, काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *rom;
	u16 dptr;
	u8 rom_type;
	माप_प्रकार rom_size;

	/* If this is a primary card, there is a shaकरोw copy of the
	 * ROM somewhere in the first meg. We will just ignore the copy
	 * and use the ROM directly.
	 */
    
    	/* Fix from ATI क्रम problem with Radeon hardware not leaving ROM enabled */
    	अचिन्हित पूर्णांक temp;
	temp = INREG(MPP_TB_CONFIG);
	temp &= 0x00ffffffu;
	temp |= 0x04 << 24;
	OUTREG(MPP_TB_CONFIG, temp);
	temp = INREG(MPP_TB_CONFIG);
                                                                                                          
	rom = pci_map_rom(dev, &rom_size);
	अगर (!rom) अणु
		prपूर्णांकk(KERN_ERR "radeonfb (%s): ROM failed to map\n",
		       pci_name(rinfo->pdev));
		वापस -ENOMEM;
	पूर्ण
	
	rinfo->bios_seg = rom;

	/* Very simple test to make sure it appeared */
	अगर (BIOS_IN16(0) != 0xaa55) अणु
		prपूर्णांकk(KERN_DEBUG "radeonfb (%s): Invalid ROM signature %x "
			"should be 0xaa55\n",
			pci_name(rinfo->pdev), BIOS_IN16(0));
		जाओ failed;
	पूर्ण
	/* Look क्रम the PCI data to check the ROM type */
	dptr = BIOS_IN16(0x18);

	/* Check the PCI data signature. If it's wrong, we still assume a normal x86 ROM
	 * क्रम now, until I've verअगरied this works everywhere. The goal here is more
	 * to phase out Open Firmware images.
	 *
	 * Currently, we only look at the first PCI data, we could iteratre and deal with
	 * them all, and we should use fb_bios_start relative to start of image and not
	 * relative start of ROM, but so far, I never found a dual-image ATI card
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
		prपूर्णांकk(KERN_WARNING "radeonfb (%s): PCI DATA signature in ROM"
		       "incorrect: %08x\n", pci_name(rinfo->pdev), BIOS_IN32(dptr));
		जाओ anyway;
	पूर्ण
	rom_type = BIOS_IN8(dptr + 0x14);
	चयन(rom_type) अणु
	हाल 0:
		prपूर्णांकk(KERN_INFO "radeonfb: Found Intel x86 BIOS ROM Image\n");
		अवरोध;
	हाल 1:
		prपूर्णांकk(KERN_INFO "radeonfb: Found Open Firmware ROM Image\n");
		जाओ failed;
	हाल 2:
		prपूर्णांकk(KERN_INFO "radeonfb: Found HP PA-RISC ROM Image\n");
		जाओ failed;
	शेष:
		prपूर्णांकk(KERN_INFO "radeonfb: Found unknown type %d ROM Image\n", rom_type);
		जाओ failed;
	पूर्ण
 anyway:
	/* Locate the flat panel infos, करो some sanity checking !!! */
	rinfo->fp_bios_start = BIOS_IN16(0x48);
	वापस 0;

 failed:
	rinfo->bios_seg = शून्य;
	radeon_unmap_ROM(rinfo, dev);
	वापस -ENXIO;
पूर्ण

#अगर_घोषित CONFIG_X86
अटल पूर्णांक  radeon_find_mem_vbios(काष्ठा radeonfb_info *rinfo)
अणु
	/* I simplअगरied this code as we used to miss the signatures in
	 * a lot of हाल. It's now closer to XFree, we just don't check
	 * क्रम signatures at all... Something better will have to be करोne
	 * अगर we end up having conflicts
	 */
        u32  segstart;
	व्योम __iomem *rom_base = शून्य;
                                                
        क्रम(segstart=0x000c0000; segstart<0x000f0000; segstart+=0x00001000) अणु
                rom_base = ioremap(segstart, 0x10000);
		अगर (rom_base == शून्य)
			वापस -ENOMEM;
                अगर (पढ़ोb(rom_base) == 0x55 && पढ़ोb(rom_base + 1) == 0xaa)
	                अवरोध;
                iounmap(rom_base);
		rom_base = शून्य;
        पूर्ण
	अगर (rom_base == शून्य)
		वापस -ENXIO;

	/* Locate the flat panel infos, करो some sanity checking !!! */
	rinfo->bios_seg = rom_base;
	rinfo->fp_bios_start = BIOS_IN16(0x48);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
/*
 * Read XTAL (ref घड़ी), SCLK and MCLK from Open Firmware device
 * tree. Hopefully, ATI OF driver is kind enough to fill these
 */
अटल पूर्णांक radeon_पढ़ो_xtal_OF(काष्ठा radeonfb_info *rinfo)
अणु
	काष्ठा device_node *dp = rinfo->of_node;
	स्थिर u32 *val;

	अगर (dp == शून्य)
		वापस -ENODEV;
	val = of_get_property(dp, "ATY,RefCLK", शून्य);
	अगर (!val || !*val) अणु
		prपूर्णांकk(KERN_WARNING "radeonfb: No ATY,RefCLK property !\n");
		वापस -EINVAL;
	पूर्ण

	rinfo->pll.ref_clk = (*val) / 10;

	val = of_get_property(dp, "ATY,SCLK", शून्य);
	अगर (val && *val)
		rinfo->pll.sclk = (*val) / 10;

	val = of_get_property(dp, "ATY,MCLK", शून्य);
	अगर (val && *val)
		rinfo->pll.mclk = (*val) / 10;

       	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */

/*
 * Read PLL infos from chip रेजिस्टरs
 */
अटल पूर्णांक radeon_probe_pll_params(काष्ठा radeonfb_info *rinfo)
अणु
	अचिन्हित अक्षर ppll_भाग_sel;
	अचिन्हित Ns, Nm, M;
	अचिन्हित sclk, mclk, पंचांगp, ref_भाग;
	पूर्णांक hTotal, vTotal, num, denom, m, n;
	अचिन्हित दीर्घ दीर्घ hz, vclk;
	दीर्घ xtal;
	kसमय_प्रकार start_समय, stop_समय;
	u64 total_usecs;
	पूर्णांक i;

	/* Ugh, we cut पूर्णांकerrupts, bad bad bad, but we want some precision
	 * here, so... --BenH
	 */

	/* Flush PCI buffers ? */
	पंचांगp = INREG16(DEVICE_ID);

	local_irq_disable();

	क्रम(i=0; i<1000000; i++)
		अगर (((INREG(CRTC_VLINE_CRNT_VLINE) >> 16) & 0x3ff) == 0)
			अवरोध;

	start_समय = kसमय_get();

	क्रम(i=0; i<1000000; i++)
		अगर (((INREG(CRTC_VLINE_CRNT_VLINE) >> 16) & 0x3ff) != 0)
			अवरोध;

	क्रम(i=0; i<1000000; i++)
		अगर (((INREG(CRTC_VLINE_CRNT_VLINE) >> 16) & 0x3ff) == 0)
			अवरोध;
	
	stop_समय = kसमय_get();
	
	local_irq_enable();

	total_usecs = kसमय_us_delta(stop_समय, start_समय);
	अगर (total_usecs >= 10 * USEC_PER_SEC || total_usecs == 0)
		वापस -1;
	hz = USEC_PER_SEC/(u32)total_usecs;
 
	hTotal = ((INREG(CRTC_H_TOTAL_DISP) & 0x1ff) + 1) * 8;
	vTotal = ((INREG(CRTC_V_TOTAL_DISP) & 0x3ff) + 1);
	vclk = (दीर्घ दीर्घ)hTotal * (दीर्घ दीर्घ)vTotal * hz;

	चयन((INPLL(PPLL_REF_DIV) & 0x30000) >> 16) अणु
	हाल 0:
	शेष:
		num = 1;
		denom = 1;
		अवरोध;
	हाल 1:
		n = ((INPLL(M_SPLL_REF_FB_DIV) >> 16) & 0xff);
		m = (INPLL(M_SPLL_REF_FB_DIV) & 0xff);
		num = 2*n;
		denom = 2*m;
		अवरोध;
	हाल 2:
		n = ((INPLL(M_SPLL_REF_FB_DIV) >> 8) & 0xff);
		m = (INPLL(M_SPLL_REF_FB_DIV) & 0xff);
		num = 2*n;
		denom = 2*m;
        अवरोध;
	पूर्ण

	ppll_भाग_sel = INREG8(CLOCK_CNTL_INDEX + 1) & 0x3;
	radeon_pll_errata_after_index(rinfo);

	n = (INPLL(PPLL_DIV_0 + ppll_भाग_sel) & 0x7ff);
	m = (INPLL(PPLL_REF_DIV) & 0x3ff);

	num *= n;
	denom *= m;

	चयन ((INPLL(PPLL_DIV_0 + ppll_भाग_sel) >> 16) & 0x7) अणु
	हाल 1:
		denom *= 2;
		अवरोध;
	हाल 2:
		denom *= 4;
		अवरोध;
	हाल 3:
		denom *= 8;
		अवरोध;
	हाल 4:
		denom *= 3;
		अवरोध;
	हाल 6:
		denom *= 6;   
		अवरोध;
	हाल 7:
		denom *= 12;
		अवरोध;
	पूर्ण

	vclk *= denom;
	करो_भाग(vclk, 1000 * num);
	xtal = vclk;

	अगर ((xtal > 26900) && (xtal < 27100))
		xtal = 2700;
	अन्यथा अगर ((xtal > 14200) && (xtal < 14400))
		xtal = 1432;
	अन्यथा अगर ((xtal > 29400) && (xtal < 29600))
		xtal = 2950;
	अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "xtal calculation failed: %ld\n", xtal);
		वापस -1;
	पूर्ण

	पंचांगp = INPLL(M_SPLL_REF_FB_DIV);
	ref_भाग = INPLL(PPLL_REF_DIV) & 0x3ff;

	Ns = (पंचांगp & 0xff0000) >> 16;
	Nm = (पंचांगp & 0xff00) >> 8;
	M = (पंचांगp & 0xff);
	sclk = round_भाग((2 * Ns * xtal), (2 * M));
	mclk = round_भाग((2 * Nm * xtal), (2 * M));

	/* we're करोne, hopefully these are sane values */
	rinfo->pll.ref_clk = xtal;
	rinfo->pll.ref_भाग = ref_भाग;
	rinfo->pll.sclk = sclk;
	rinfo->pll.mclk = mclk;

	वापस 0;
पूर्ण

/*
 * Retrieve PLL infos by dअगरferent means (BIOS, Open Firmware, रेजिस्टर probing...)
 */
अटल व्योम radeon_get_pllinfo(काष्ठा radeonfb_info *rinfo)
अणु
	/*
	 * In the हाल nothing works, these are शेषs; they are mostly
	 * incomplete, however.  It करोes provide ppll_max and _min values
	 * even क्रम most other methods, however.
	 */
	चयन (rinfo->chipset) अणु
	हाल PCI_DEVICE_ID_ATI_RADEON_QW:
	हाल PCI_DEVICE_ID_ATI_RADEON_QX:
		rinfo->pll.ppll_max = 35000;
		rinfo->pll.ppll_min = 12000;
		rinfo->pll.mclk = 23000;
		rinfo->pll.sclk = 23000;
		rinfo->pll.ref_clk = 2700;
		अवरोध;
	हाल PCI_DEVICE_ID_ATI_RADEON_QL:
	हाल PCI_DEVICE_ID_ATI_RADEON_QN:
	हाल PCI_DEVICE_ID_ATI_RADEON_QO:
	हाल PCI_DEVICE_ID_ATI_RADEON_Ql:
	हाल PCI_DEVICE_ID_ATI_RADEON_BB:
		rinfo->pll.ppll_max = 35000;
		rinfo->pll.ppll_min = 12000;
		rinfo->pll.mclk = 27500;
		rinfo->pll.sclk = 27500;
		rinfo->pll.ref_clk = 2700;
		अवरोध;
	हाल PCI_DEVICE_ID_ATI_RADEON_Id:
	हाल PCI_DEVICE_ID_ATI_RADEON_Ie:
	हाल PCI_DEVICE_ID_ATI_RADEON_If:
	हाल PCI_DEVICE_ID_ATI_RADEON_Ig:
		rinfo->pll.ppll_max = 35000;
		rinfo->pll.ppll_min = 12000;
		rinfo->pll.mclk = 25000;
		rinfo->pll.sclk = 25000;
		rinfo->pll.ref_clk = 2700;
		अवरोध;
	हाल PCI_DEVICE_ID_ATI_RADEON_ND:
	हाल PCI_DEVICE_ID_ATI_RADEON_NE:
	हाल PCI_DEVICE_ID_ATI_RADEON_NF:
	हाल PCI_DEVICE_ID_ATI_RADEON_NG:
		rinfo->pll.ppll_max = 40000;
		rinfo->pll.ppll_min = 20000;
		rinfo->pll.mclk = 27000;
		rinfo->pll.sclk = 27000;
		rinfo->pll.ref_clk = 2700;
		अवरोध;
	हाल PCI_DEVICE_ID_ATI_RADEON_QD:
	हाल PCI_DEVICE_ID_ATI_RADEON_QE:
	हाल PCI_DEVICE_ID_ATI_RADEON_QF:
	हाल PCI_DEVICE_ID_ATI_RADEON_QG:
	शेष:
		rinfo->pll.ppll_max = 35000;
		rinfo->pll.ppll_min = 12000;
		rinfo->pll.mclk = 16600;
		rinfo->pll.sclk = 16600;
		rinfo->pll.ref_clk = 2700;
		अवरोध;
	पूर्ण
	rinfo->pll.ref_भाग = INPLL(PPLL_REF_DIV) & PPLL_REF_DIV_MASK;


#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
	/*
	 * Retrieve PLL infos from Open Firmware first
	 */
       	अगर (!क्रमce_measure_pll && radeon_पढ़ो_xtal_OF(rinfo) == 0) अणु
       		prपूर्णांकk(KERN_INFO "radeonfb: Retrieved PLL infos from Open Firmware\n");
		जाओ found;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */

	/*
	 * Check out अगर we have an X86 which gave us some PLL inक्रमmations
	 * and अगर yes, retrieve them
	 */
	अगर (!क्रमce_measure_pll && rinfo->bios_seg) अणु
		u16 pll_info_block = BIOS_IN16(rinfo->fp_bios_start + 0x30);

		rinfo->pll.sclk		= BIOS_IN16(pll_info_block + 0x08);
		rinfo->pll.mclk		= BIOS_IN16(pll_info_block + 0x0a);
		rinfo->pll.ref_clk	= BIOS_IN16(pll_info_block + 0x0e);
		rinfo->pll.ref_भाग	= BIOS_IN16(pll_info_block + 0x10);
		rinfo->pll.ppll_min	= BIOS_IN32(pll_info_block + 0x12);
		rinfo->pll.ppll_max	= BIOS_IN32(pll_info_block + 0x16);

		prपूर्णांकk(KERN_INFO "radeonfb: Retrieved PLL infos from BIOS\n");
		जाओ found;
	पूर्ण

	/*
	 * We didn't get PLL parameters from either OF or BIOS, we try to
	 * probe them
	 */
	अगर (radeon_probe_pll_params(rinfo) == 0) अणु
		prपूर्णांकk(KERN_INFO "radeonfb: Retrieved PLL infos from registers\n");
		जाओ found;
	पूर्ण

	/*
	 * Fall back to alपढ़ोy-set शेषs...
	 */
       	prपूर्णांकk(KERN_INFO "radeonfb: Used default PLL infos\n");

found:
	/*
	 * Some methods fail to retrieve SCLK and MCLK values, we apply शेष
	 * settings in this हाल (200Mhz). If that really happens often, we
	 * could fetch from रेजिस्टरs instead...
	 */
	अगर (rinfo->pll.mclk == 0)
		rinfo->pll.mclk = 20000;
	अगर (rinfo->pll.sclk == 0)
		rinfo->pll.sclk = 20000;

	prपूर्णांकk("radeonfb: Reference=%d.%02d MHz (RefDiv=%d) Memory=%d.%02d Mhz, System=%d.%02d MHz\n",
	       rinfo->pll.ref_clk / 100, rinfo->pll.ref_clk % 100,
	       rinfo->pll.ref_भाग,
	       rinfo->pll.mclk / 100, rinfo->pll.mclk % 100,
	       rinfo->pll.sclk / 100, rinfo->pll.sclk % 100);
	prपूर्णांकk("radeonfb: PLL min %d max %d\n", rinfo->pll.ppll_min, rinfo->pll.ppll_max);
पूर्ण

अटल पूर्णांक radeonfb_check_var (काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;
        काष्ठा fb_var_screeninfo v;
        पूर्णांक nom, den;
	अचिन्हित पूर्णांक pitch;

	अगर (radeon_match_mode(rinfo, &v, var))
		वापस -EINVAL;

        चयन (v.bits_per_pixel) अणु
		हाल 0 ... 8:
			v.bits_per_pixel = 8;
			अवरोध;
		हाल 9 ... 16:
			v.bits_per_pixel = 16;
			अवरोध;
		हाल 25 ... 32:
			v.bits_per_pixel = 32;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (var_to_depth(&v)) अणु
                हाल 8:
                        nom = den = 1;
                        v.red.offset = v.green.offset = v.blue.offset = 0;
                        v.red.length = v.green.length = v.blue.length = 8;
                        v.transp.offset = v.transp.length = 0;
                        अवरोध;
		हाल 15:
			nom = 2;
			den = 1;
			v.red.offset = 10;
			v.green.offset = 5;
			v.blue.offset = 0;
			v.red.length = v.green.length = v.blue.length = 5;
			v.transp.offset = v.transp.length = 0;
			अवरोध;
                हाल 16:
                        nom = 2;
                        den = 1;
                        v.red.offset = 11;
                        v.green.offset = 5;
                        v.blue.offset = 0;
                        v.red.length = 5;
                        v.green.length = 6;
                        v.blue.length = 5;
                        v.transp.offset = v.transp.length = 0;
                        अवरोध;                          
                हाल 24:
                        nom = 4;
                        den = 1;
                        v.red.offset = 16;
                        v.green.offset = 8;
                        v.blue.offset = 0;
                        v.red.length = v.blue.length = v.green.length = 8;
                        v.transp.offset = v.transp.length = 0;
                        अवरोध;
                हाल 32:
                        nom = 4;
                        den = 1;
                        v.red.offset = 16;
                        v.green.offset = 8;
                        v.blue.offset = 0;
                        v.red.length = v.blue.length = v.green.length = 8;
                        v.transp.offset = 24;
                        v.transp.length = 8;
                        अवरोध;
                शेष:
                        prपूर्णांकk ("radeonfb: mode %dx%dx%d rejected, color depth invalid\n",
                                var->xres, var->yres, var->bits_per_pixel);
                        वापस -EINVAL;
        पूर्ण

	अगर (v.yres_भव < v.yres)
		v.yres_भव = v.yres;
	अगर (v.xres_भव < v.xres)
		v.xres_भव = v.xres;
                

	/* XXX I'm adjusting xres_भव to the pitch, that may help XFree
	 * with some panels, though I करोn't quite like this solution
	 */
  	अगर (rinfo->info->flags & FBINFO_HWACCEL_DISABLED) अणु
		v.xres_भव = v.xres_भव & ~7ul;
	पूर्ण अन्यथा अणु
		pitch = ((v.xres_भव * ((v.bits_per_pixel + 1) / 8) + 0x3f)
 				& ~(0x3f)) >> 6;
		v.xres_भव = (pitch << 6) / ((v.bits_per_pixel + 1) / 8);
	पूर्ण

	अगर (((v.xres_भव * v.yres_भव * nom) / den) > rinfo->mapped_vram)
		वापस -EINVAL;

	अगर (v.xres_भव < v.xres)
		v.xres = v.xres_भव;

        अगर (v.xoffset > v.xres_भव - v.xres)
                v.xoffset = v.xres_भव - v.xres - 1;
                        
        अगर (v.yoffset > v.yres_भव - v.yres)
                v.yoffset = v.yres_भव - v.yres - 1;
         
        v.red.msb_right = v.green.msb_right = v.blue.msb_right =
                          v.transp.offset = v.transp.length =
                          v.transp.msb_right = 0;
	
        स_नकल(var, &v, माप(v));

        वापस 0;
पूर्ण


अटल पूर्णांक radeonfb_pan_display (काष्ठा fb_var_screeninfo *var,
                                 काष्ठा fb_info *info)
अणु
        काष्ठा radeonfb_info *rinfo = info->par;

	अगर ((var->xoffset + info->var.xres > info->var.xres_भव)
	    || (var->yoffset + info->var.yres > info->var.yres_भव))
		वापस -EINVAL;
                
        अगर (rinfo->asleep)
        	वापस 0;

	radeon_fअगरo_रुको(2);
	OUTREG(CRTC_OFFSET, (var->yoffset * info->fix.line_length +
			     var->xoffset * info->var.bits_per_pixel / 8) & ~7);
        वापस 0;
पूर्ण


अटल पूर्णांक radeonfb_ioctl (काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
                           अचिन्हित दीर्घ arg)
अणु
        काष्ठा radeonfb_info *rinfo = info->par;
	अचिन्हित पूर्णांक पंचांगp;
	u32 value = 0;
	पूर्णांक rc;

	चयन (cmd) अणु
		/*
		 * TODO:  set mirror accordingly क्रम non-Mobility chipsets with 2 CRTC's
		 *        and करो something better using 2nd CRTC instead of just hackish
		 *        routing to second output
		 */
		हाल FBIO_RADEON_SET_MIRROR:
			अगर (!rinfo->is_mobility)
				वापस -EINVAL;

			rc = get_user(value, (__u32 __user *)arg);

			अगर (rc)
				वापस rc;

			radeon_fअगरo_रुको(2);
			अगर (value & 0x01) अणु
				पंचांगp = INREG(LVDS_GEN_CNTL);

				पंचांगp |= (LVDS_ON | LVDS_BLON);
			पूर्ण अन्यथा अणु
				पंचांगp = INREG(LVDS_GEN_CNTL);

				पंचांगp &= ~(LVDS_ON | LVDS_BLON);
			पूर्ण

			OUTREG(LVDS_GEN_CNTL, पंचांगp);

			अगर (value & 0x02) अणु
				पंचांगp = INREG(CRTC_EXT_CNTL);
				पंचांगp |= CRTC_CRT_ON;

				mirror = 1;
			पूर्ण अन्यथा अणु
				पंचांगp = INREG(CRTC_EXT_CNTL);
				पंचांगp &= ~CRTC_CRT_ON;

				mirror = 0;
			पूर्ण

			OUTREG(CRTC_EXT_CNTL, पंचांगp);

			वापस 0;
		हाल FBIO_RADEON_GET_MIRROR:
			अगर (!rinfo->is_mobility)
				वापस -EINVAL;

			पंचांगp = INREG(LVDS_GEN_CNTL);
			अगर ((LVDS_ON | LVDS_BLON) & पंचांगp)
				value |= 0x01;

			पंचांगp = INREG(CRTC_EXT_CNTL);
			अगर (CRTC_CRT_ON & पंचांगp)
				value |= 0x02;

			वापस put_user(value, (__u32 __user *)arg);
		शेष:
			वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण


पूर्णांक radeon_screen_blank(काष्ठा radeonfb_info *rinfo, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
        u32 val;
	u32 पंचांगp_pix_clks;
	पूर्णांक unblank = 0;

	अगर (rinfo->lock_blank)
		वापस 0;

	radeon_engine_idle();

	val = INREG(CRTC_EXT_CNTL);
        val &= ~(CRTC_DISPLAY_DIS | CRTC_HSYNC_DIS |
                 CRTC_VSYNC_DIS);
        चयन (blank) अणु
	हाल FB_BLANK_VSYNC_SUSPEND:
		val |= (CRTC_DISPLAY_DIS | CRTC_VSYNC_DIS);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		val |= (CRTC_DISPLAY_DIS | CRTC_HSYNC_DIS);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		val |= (CRTC_DISPLAY_DIS | CRTC_VSYNC_DIS |
			CRTC_HSYNC_DIS);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		val |= CRTC_DISPLAY_DIS;
		अवरोध;
	हाल FB_BLANK_UNBLANK:
	शेष:
		unblank = 1;
        पूर्ण
	OUTREG(CRTC_EXT_CNTL, val);


	चयन (rinfo->mon1_type) अणु
	हाल MT_DFP:
		अगर (unblank)
			OUTREGP(FP_GEN_CNTL, (FP_FPON | FP_TMDS_EN),
				~(FP_FPON | FP_TMDS_EN));
		अन्यथा अणु
			अगर (mode_चयन || blank == FB_BLANK_NORMAL)
				अवरोध;
			OUTREGP(FP_GEN_CNTL, 0, ~(FP_FPON | FP_TMDS_EN));
		पूर्ण
		अवरोध;
	हाल MT_LCD:
		del_समयr_sync(&rinfo->lvds_समयr);
		val = INREG(LVDS_GEN_CNTL);
		अगर (unblank) अणु
			u32 target_val = (val & ~LVDS_DISPLAY_DIS) | LVDS_BLON | LVDS_ON
				| LVDS_EN | (rinfo->init_state.lvds_gen_cntl
					     & (LVDS_DIGON | LVDS_BL_MOD_EN));
			अगर ((val ^ target_val) == LVDS_DISPLAY_DIS)
				OUTREG(LVDS_GEN_CNTL, target_val);
			अन्यथा अगर ((val ^ target_val) != 0) अणु
				OUTREG(LVDS_GEN_CNTL, target_val
				       & ~(LVDS_ON | LVDS_BL_MOD_EN));
				rinfo->init_state.lvds_gen_cntl &= ~LVDS_STATE_MASK;
				rinfo->init_state.lvds_gen_cntl |=
					target_val & LVDS_STATE_MASK;
				अगर (mode_चयन) अणु
					radeon_msleep(rinfo->panel_info.pwr_delay);
					OUTREG(LVDS_GEN_CNTL, target_val);
				पूर्ण
				अन्यथा अणु
					rinfo->pending_lvds_gen_cntl = target_val;
					mod_समयr(&rinfo->lvds_समयr,
					   jअगरfies +
					   msecs_to_jअगरfies(rinfo->panel_info.pwr_delay));
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			val |= LVDS_DISPLAY_DIS;
			OUTREG(LVDS_GEN_CNTL, val);

			/* We करोn't करो a full चयन-off on a simple mode चयन */
			अगर (mode_चयन || blank == FB_BLANK_NORMAL)
				अवरोध;

			/* Asic bug, when turning off LVDS_ON, we have to make sure
			 * RADEON_PIXCLK_LVDS_ALWAYS_ON bit is off
			 */
			पंचांगp_pix_clks = INPLL(PIXCLKS_CNTL);
			अगर (rinfo->is_mobility || rinfo->is_IGP)
				OUTPLLP(PIXCLKS_CNTL, 0, ~PIXCLK_LVDS_ALWAYS_ONb);
			val &= ~(LVDS_BL_MOD_EN);
			OUTREG(LVDS_GEN_CNTL, val);
			udelay(100);
			val &= ~(LVDS_ON | LVDS_EN);
			OUTREG(LVDS_GEN_CNTL, val);
			val &= ~LVDS_DIGON;
			rinfo->pending_lvds_gen_cntl = val;
			mod_समयr(&rinfo->lvds_समयr,
				  jअगरfies +
				  msecs_to_jअगरfies(rinfo->panel_info.pwr_delay));
			rinfo->init_state.lvds_gen_cntl &= ~LVDS_STATE_MASK;
			rinfo->init_state.lvds_gen_cntl |= val & LVDS_STATE_MASK;
			अगर (rinfo->is_mobility || rinfo->is_IGP)
				OUTPLL(PIXCLKS_CNTL, पंचांगp_pix_clks);
		पूर्ण
		अवरोध;
	हाल MT_CRT:
		// toकरो: घातerकरोwn DAC
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक radeonfb_blank (पूर्णांक blank, काष्ठा fb_info *info)
अणु
        काष्ठा radeonfb_info *rinfo = info->par;

	अगर (rinfo->asleep)
		वापस 0;
		
	वापस radeon_screen_blank(rinfo, blank, 0);
पूर्ण

अटल पूर्णांक radeon_setcolreg (अचिन्हित regno, अचिन्हित red, अचिन्हित green,
                             अचिन्हित blue, अचिन्हित transp,
			     काष्ठा radeonfb_info *rinfo)
अणु
	u32 pindex;
	अचिन्हित पूर्णांक i;


	अगर (regno > 255)
		वापस -EINVAL;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	rinfo->palette[regno].red = red;
	rinfo->palette[regno].green = green;
	rinfo->palette[regno].blue = blue;

        /* शेष */
        pindex = regno;

        अगर (!rinfo->asleep) अणु
		radeon_fअगरo_रुको(9);

		अगर (rinfo->bpp == 16) अणु
			pindex = regno * 8;

			अगर (rinfo->depth == 16 && regno > 63)
				वापस -EINVAL;
			अगर (rinfo->depth == 15 && regno > 31)
				वापस -EINVAL;

			/* For 565, the green component is mixed one order
			 * below
			 */
			अगर (rinfo->depth == 16) अणु
		                OUTREG(PALETTE_INDEX, pindex>>1);
	       	         	OUTREG(PALETTE_DATA,
				       (rinfo->palette[regno>>1].red << 16) |
	                        	(green << 8) |
				       (rinfo->palette[regno>>1].blue));
	                	green = rinfo->palette[regno<<1].green;
	        	पूर्ण
		पूर्ण

		अगर (rinfo->depth != 16 || regno < 32) अणु
			OUTREG(PALETTE_INDEX, pindex);
			OUTREG(PALETTE_DATA, (red << 16) |
			       (green << 8) | blue);
		पूर्ण
	पूर्ण
 	अगर (regno < 16) अणु
		u32 *pal = rinfo->info->pseuकरो_palette;
        	चयन (rinfo->depth) अणु
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
	वापस 0;
पूर्ण

अटल पूर्णांक radeonfb_setcolreg (अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			       अचिन्हित blue, अचिन्हित transp,
			       काष्ठा fb_info *info)
अणु
        काष्ठा radeonfb_info *rinfo = info->par;
	u32 dac_cntl2, vclk_cntl = 0;
	पूर्णांक rc;

        अगर (!rinfo->asleep) अणु
		अगर (rinfo->is_mobility) अणु
			vclk_cntl = INPLL(VCLK_ECP_CNTL);
			OUTPLL(VCLK_ECP_CNTL,
			       vclk_cntl & ~PIXCLK_DAC_ALWAYS_ONb);
		पूर्ण

		/* Make sure we are on first palette */
		अगर (rinfo->has_CRTC2) अणु
			dac_cntl2 = INREG(DAC_CNTL2);
			dac_cntl2 &= ~DAC2_PALETTE_ACCESS_CNTL;
			OUTREG(DAC_CNTL2, dac_cntl2);
		पूर्ण
	पूर्ण

	rc = radeon_setcolreg (regno, red, green, blue, transp, rinfo);

	अगर (!rinfo->asleep && rinfo->is_mobility)
		OUTPLL(VCLK_ECP_CNTL, vclk_cntl);

	वापस rc;
पूर्ण

अटल पूर्णांक radeonfb_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
        काष्ठा radeonfb_info *rinfo = info->par;
	u16 *red, *green, *blue, *transp;
	u32 dac_cntl2, vclk_cntl = 0;
	पूर्णांक i, start, rc = 0;

        अगर (!rinfo->asleep) अणु
		अगर (rinfo->is_mobility) अणु
			vclk_cntl = INPLL(VCLK_ECP_CNTL);
			OUTPLL(VCLK_ECP_CNTL,
			       vclk_cntl & ~PIXCLK_DAC_ALWAYS_ONb);
		पूर्ण

		/* Make sure we are on first palette */
		अगर (rinfo->has_CRTC2) अणु
			dac_cntl2 = INREG(DAC_CNTL2);
			dac_cntl2 &= ~DAC2_PALETTE_ACCESS_CNTL;
			OUTREG(DAC_CNTL2, dac_cntl2);
		पूर्ण
	पूर्ण

	red = cmap->red;
	green = cmap->green;
	blue = cmap->blue;
	transp = cmap->transp;
	start = cmap->start;

	क्रम (i = 0; i < cmap->len; i++) अणु
		u_पूर्णांक hred, hgreen, hblue, htransp = 0xffff;

		hred = *red++;
		hgreen = *green++;
		hblue = *blue++;
		अगर (transp)
			htransp = *transp++;
		rc = radeon_setcolreg (start++, hred, hgreen, hblue, htransp,
				       rinfo);
		अगर (rc)
			अवरोध;
	पूर्ण

	अगर (!rinfo->asleep && rinfo->is_mobility)
		OUTPLL(VCLK_ECP_CNTL, vclk_cntl);

	वापस rc;
पूर्ण

अटल व्योम radeon_save_state (काष्ठा radeonfb_info *rinfo,
			       काष्ठा radeon_regs *save)
अणु
	/* CRTC regs */
	save->crtc_gen_cntl = INREG(CRTC_GEN_CNTL);
	save->crtc_ext_cntl = INREG(CRTC_EXT_CNTL);
	save->crtc_more_cntl = INREG(CRTC_MORE_CNTL);
	save->dac_cntl = INREG(DAC_CNTL);
        save->crtc_h_total_disp = INREG(CRTC_H_TOTAL_DISP);
        save->crtc_h_sync_strt_wid = INREG(CRTC_H_SYNC_STRT_WID);
        save->crtc_v_total_disp = INREG(CRTC_V_TOTAL_DISP);
        save->crtc_v_sync_strt_wid = INREG(CRTC_V_SYNC_STRT_WID);
	save->crtc_pitch = INREG(CRTC_PITCH);
	save->surface_cntl = INREG(SURFACE_CNTL);

	/* FP regs */
	save->fp_crtc_h_total_disp = INREG(FP_CRTC_H_TOTAL_DISP);
	save->fp_crtc_v_total_disp = INREG(FP_CRTC_V_TOTAL_DISP);
	save->fp_gen_cntl = INREG(FP_GEN_CNTL);
	save->fp_h_sync_strt_wid = INREG(FP_H_SYNC_STRT_WID);
	save->fp_horz_stretch = INREG(FP_HORZ_STRETCH);
	save->fp_v_sync_strt_wid = INREG(FP_V_SYNC_STRT_WID);
	save->fp_vert_stretch = INREG(FP_VERT_STRETCH);
	save->lvds_gen_cntl = INREG(LVDS_GEN_CNTL);
	save->lvds_pll_cntl = INREG(LVDS_PLL_CNTL);
	save->पंचांगds_crc = INREG(TMDS_CRC);
	save->पंचांगds_transmitter_cntl = INREG(TMDS_TRANSMITTER_CNTL);
	save->vclk_ecp_cntl = INPLL(VCLK_ECP_CNTL);

	/* PLL regs */
	save->clk_cntl_index = INREG(CLOCK_CNTL_INDEX) & ~0x3f;
	radeon_pll_errata_after_index(rinfo);
	save->ppll_भाग_3 = INPLL(PPLL_DIV_3);
	save->ppll_ref_भाग = INPLL(PPLL_REF_DIV);
पूर्ण


अटल व्योम radeon_ग_लिखो_pll_regs(काष्ठा radeonfb_info *rinfo, काष्ठा radeon_regs *mode)
अणु
	पूर्णांक i;

	radeon_fअगरo_रुको(20);

	/* Workaround from XFree */
	अगर (rinfo->is_mobility) अणु
	        /* A temporal workaround क्रम the occasional blanking on certain laptop
		 * panels. This appears to related to the PLL भागider रेजिस्टरs
		 * (fail to lock?). It occurs even when all भागiders are the same
		 * with their old settings. In this हाल we really करोn't need to
		 * fiddle with PLL रेजिस्टरs. By करोing this we can aव्योम the blanking
		 * problem with some panels.
	         */
		अगर ((mode->ppll_ref_भाग == (INPLL(PPLL_REF_DIV) & PPLL_REF_DIV_MASK)) &&
		    (mode->ppll_भाग_3 == (INPLL(PPLL_DIV_3) &
					  (PPLL_POST3_DIV_MASK | PPLL_FB3_DIV_MASK)))) अणु
			/* We still have to क्रमce a चयन to selected PPLL भाग thanks to
			 * an XFree86 driver bug which will चयन it away in some हालs
			 * even when using UseFDev */
			OUTREGP(CLOCK_CNTL_INDEX,
				mode->clk_cntl_index & PPLL_DIV_SEL_MASK,
				~PPLL_DIV_SEL_MASK);
			radeon_pll_errata_after_index(rinfo);
			radeon_pll_errata_after_data(rinfo);
            		वापस;
		पूर्ण
	पूर्ण

	/* Swich VCKL घड़ी input to CPUCLK so it stays fed जबतक PPLL updates*/
	OUTPLLP(VCLK_ECP_CNTL, VCLK_SRC_SEL_CPUCLK, ~VCLK_SRC_SEL_MASK);

	/* Reset PPLL & enable atomic update */
	OUTPLLP(PPLL_CNTL,
		PPLL_RESET | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN,
		~(PPLL_RESET | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN));

	/* Switch to selected PPLL भागider */
	OUTREGP(CLOCK_CNTL_INDEX,
		mode->clk_cntl_index & PPLL_DIV_SEL_MASK,
		~PPLL_DIV_SEL_MASK);
	radeon_pll_errata_after_index(rinfo);
	radeon_pll_errata_after_data(rinfo);

	/* Set PPLL ref. भाग */
	अगर (IS_R300_VARIANT(rinfo) ||
	    rinfo->family == CHIP_FAMILY_RS300 ||
	    rinfo->family == CHIP_FAMILY_RS400 ||
	    rinfo->family == CHIP_FAMILY_RS480) अणु
		अगर (mode->ppll_ref_भाग & R300_PPLL_REF_DIV_ACC_MASK) अणु
			/* When restoring console mode, use saved PPLL_REF_DIV
			 * setting.
			 */
			OUTPLLP(PPLL_REF_DIV, mode->ppll_ref_भाग, 0);
		पूर्ण अन्यथा अणु
			/* R300 uses ref_भाग_acc field as real ref भागider */
			OUTPLLP(PPLL_REF_DIV,
				(mode->ppll_ref_भाग << R300_PPLL_REF_DIV_ACC_SHIFT), 
				~R300_PPLL_REF_DIV_ACC_MASK);
		पूर्ण
	पूर्ण अन्यथा
		OUTPLLP(PPLL_REF_DIV, mode->ppll_ref_भाग, ~PPLL_REF_DIV_MASK);

	/* Set PPLL भागider 3 & post भागider*/
	OUTPLLP(PPLL_DIV_3, mode->ppll_भाग_3, ~PPLL_FB3_DIV_MASK);
	OUTPLLP(PPLL_DIV_3, mode->ppll_भाग_3, ~PPLL_POST3_DIV_MASK);

	/* Write update */
	जबतक (INPLL(PPLL_REF_DIV) & PPLL_ATOMIC_UPDATE_R)
		;
	OUTPLLP(PPLL_REF_DIV, PPLL_ATOMIC_UPDATE_W, ~PPLL_ATOMIC_UPDATE_W);

	/* Wait पढ़ो update complete */
	/* FIXME: Certain revisions of R300 can't recover here.  Not sure of
	   the cause yet, but this workaround will mask the problem क्रम now.
	   Other chips usually will pass at the very first test, so the
	   workaround shouldn't have any effect on them. */
	क्रम (i = 0; (i < 10000 && INPLL(PPLL_REF_DIV) & PPLL_ATOMIC_UPDATE_R); i++)
		;
	
	OUTPLL(HTOTAL_CNTL, 0);

	/* Clear reset & atomic update */
	OUTPLLP(PPLL_CNTL, 0,
		~(PPLL_RESET | PPLL_SLEEP | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN));

	/* We may want some locking ... oh well */
       	radeon_msleep(5);

	/* Switch back VCLK source to PPLL */
	OUTPLLP(VCLK_ECP_CNTL, VCLK_SRC_SEL_PPLLCLK, ~VCLK_SRC_SEL_MASK);
पूर्ण

/*
 * Timer function क्रम delayed LVDS panel घातer up/करोwn
 */
अटल व्योम radeon_lvds_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा radeonfb_info *rinfo = from_समयr(rinfo, t, lvds_समयr);

	radeon_engine_idle();

	OUTREG(LVDS_GEN_CNTL, rinfo->pending_lvds_gen_cntl);
पूर्ण

/*
 * Apply a video mode. This will apply the whole रेजिस्टर set, including
 * the PLL रेजिस्टरs, to the card
 */
व्योम radeon_ग_लिखो_mode (काष्ठा radeonfb_info *rinfo, काष्ठा radeon_regs *mode,
			पूर्णांक regs_only)
अणु
	पूर्णांक i;
	पूर्णांक primary_mon = PRIMARY_MONITOR(rinfo);

	अगर (nomodeset)
		वापस;

	अगर (!regs_only)
		radeon_screen_blank(rinfo, FB_BLANK_NORMAL, 0);

	radeon_fअगरo_रुको(31);
	क्रम (i=0; i<10; i++)
		OUTREG(common_regs[i].reg, common_regs[i].val);

	/* Apply surface रेजिस्टरs */
	क्रम (i=0; i<8; i++) अणु
		OUTREG(SURFACE0_LOWER_BOUND + 0x10*i, mode->surf_lower_bound[i]);
		OUTREG(SURFACE0_UPPER_BOUND + 0x10*i, mode->surf_upper_bound[i]);
		OUTREG(SURFACE0_INFO + 0x10*i, mode->surf_info[i]);
	पूर्ण

	OUTREG(CRTC_GEN_CNTL, mode->crtc_gen_cntl);
	OUTREGP(CRTC_EXT_CNTL, mode->crtc_ext_cntl,
		~(CRTC_HSYNC_DIS | CRTC_VSYNC_DIS | CRTC_DISPLAY_DIS));
	OUTREG(CRTC_MORE_CNTL, mode->crtc_more_cntl);
	OUTREGP(DAC_CNTL, mode->dac_cntl, DAC_RANGE_CNTL | DAC_BLANKING);
	OUTREG(CRTC_H_TOTAL_DISP, mode->crtc_h_total_disp);
	OUTREG(CRTC_H_SYNC_STRT_WID, mode->crtc_h_sync_strt_wid);
	OUTREG(CRTC_V_TOTAL_DISP, mode->crtc_v_total_disp);
	OUTREG(CRTC_V_SYNC_STRT_WID, mode->crtc_v_sync_strt_wid);
	OUTREG(CRTC_OFFSET, 0);
	OUTREG(CRTC_OFFSET_CNTL, 0);
	OUTREG(CRTC_PITCH, mode->crtc_pitch);
	OUTREG(SURFACE_CNTL, mode->surface_cntl);

	radeon_ग_लिखो_pll_regs(rinfo, mode);

	अगर ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) अणु
		radeon_fअगरo_रुको(10);
		OUTREG(FP_CRTC_H_TOTAL_DISP, mode->fp_crtc_h_total_disp);
		OUTREG(FP_CRTC_V_TOTAL_DISP, mode->fp_crtc_v_total_disp);
		OUTREG(FP_H_SYNC_STRT_WID, mode->fp_h_sync_strt_wid);
		OUTREG(FP_V_SYNC_STRT_WID, mode->fp_v_sync_strt_wid);
		OUTREG(FP_HORZ_STRETCH, mode->fp_horz_stretch);
		OUTREG(FP_VERT_STRETCH, mode->fp_vert_stretch);
		OUTREG(FP_GEN_CNTL, mode->fp_gen_cntl);
		OUTREG(TMDS_CRC, mode->पंचांगds_crc);
		OUTREG(TMDS_TRANSMITTER_CNTL, mode->पंचांगds_transmitter_cntl);
	पूर्ण

	अगर (!regs_only)
		radeon_screen_blank(rinfo, FB_BLANK_UNBLANK, 0);

	radeon_fअगरo_रुको(2);
	OUTPLL(VCLK_ECP_CNTL, mode->vclk_ecp_cntl);
	
	वापस;
पूर्ण

/*
 * Calculate the PLL values क्रम a given mode
 */
अटल व्योम radeon_calc_pll_regs(काष्ठा radeonfb_info *rinfo, काष्ठा radeon_regs *regs,
				 अचिन्हित दीर्घ freq)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक भागider;
		पूर्णांक bitvalue;
	पूर्ण *post_भाग,
	  post_भागs[] = अणु
		अणु 1,  0 पूर्ण,
		अणु 2,  1 पूर्ण,
		अणु 4,  2 पूर्ण,
		अणु 8,  3 पूर्ण,
		अणु 3,  4 पूर्ण,
		अणु 16, 5 पूर्ण,
		अणु 6,  6 पूर्ण,
		अणु 12, 7 पूर्ण,
		अणु 0,  0 पूर्ण,
	पूर्ण;
	पूर्णांक fb_भाग, pll_output_freq = 0;
	पूर्णांक uses_dvo = 0;

	/* Check अगर the DVO port is enabled and sourced from the primary CRTC. I'm
	 * not sure which model starts having FP2_GEN_CNTL, I assume anything more
	 * recent than an r(v)100...
	 */
#अगर 1
	/* XXX I had reports of flicker happening with the cinema display
	 * on TMDS1 that seem to be fixed अगर I also क्रमbit odd भागiders in
	 * this हाल. This could just be a bandwidth calculation issue, I
	 * haven't implemented the bandwidth code yet, but in the meanसमय,
	 * क्रमcing uses_dvo to 1 fixes it and shouln't have bad side effects,
	 * I haven't seen a हाल were were असलolutely needed an odd PLL
	 * भागider. I'll find a better fix once I have more infos on the
	 * real cause of the problem.
	 */
	जबतक (rinfo->has_CRTC2) अणु
		u32 fp2_gen_cntl = INREG(FP2_GEN_CNTL);
		u32 disp_output_cntl;
		पूर्णांक source;

		/* FP2 path not enabled */
		अगर ((fp2_gen_cntl & FP2_ON) == 0)
			अवरोध;
		/* Not all chip revs have the same क्रमmat क्रम this रेजिस्टर,
		 * extract the source selection
		 */
		अगर (rinfo->family == CHIP_FAMILY_R200 || IS_R300_VARIANT(rinfo)) अणु
			source = (fp2_gen_cntl >> 10) & 0x3;
			/* sourced from transक्रमm unit, check क्रम transक्रमm unit
			 * own source
			 */
			अगर (source == 3) अणु
				disp_output_cntl = INREG(DISP_OUTPUT_CNTL);
				source = (disp_output_cntl >> 12) & 0x3;
			पूर्ण
		पूर्ण अन्यथा
			source = (fp2_gen_cntl >> 13) & 0x1;
		/* sourced from CRTC2 -> निकास */
		अगर (source == 1)
			अवरोध;

		/* so we end up on CRTC1, let's set uses_dvo to 1 now */
		uses_dvo = 1;
		अवरोध;
	पूर्ण
#अन्यथा
	uses_dvo = 1;
#पूर्ण_अगर
	अगर (freq > rinfo->pll.ppll_max)
		freq = rinfo->pll.ppll_max;
	अगर (freq*12 < rinfo->pll.ppll_min)
		freq = rinfo->pll.ppll_min / 12;
	pr_debug("freq = %lu, PLL min = %u, PLL max = %u\n",
	       freq, rinfo->pll.ppll_min, rinfo->pll.ppll_max);

	क्रम (post_भाग = &post_भागs[0]; post_भाग->भागider; ++post_भाग) अणु
		pll_output_freq = post_भाग->भागider * freq;
		/* If we output to the DVO port (बाह्यal TMDS), we करोn't allow an
		 * odd PLL भागider as those aren't supported on this path
		 */
		अगर (uses_dvo && (post_भाग->भागider & 1))
			जारी;
		अगर (pll_output_freq >= rinfo->pll.ppll_min  &&
		    pll_output_freq <= rinfo->pll.ppll_max)
			अवरोध;
	पूर्ण

	/* If we fall through the bottom, try the "default value"
	   given by the terminal post_भाग->bitvalue */
	अगर ( !post_भाग->भागider ) अणु
		post_भाग = &post_भागs[post_भाग->bitvalue];
		pll_output_freq = post_भाग->भागider * freq;
	पूर्ण
	pr_debug("ref_div = %d, ref_clk = %d, output_freq = %d\n",
	       rinfo->pll.ref_भाग, rinfo->pll.ref_clk,
	       pll_output_freq);

	/* If we fall through the bottom, try the "default value"
	   given by the terminal post_भाग->bitvalue */
	अगर ( !post_भाग->भागider ) अणु
		post_भाग = &post_भागs[post_भाग->bitvalue];
		pll_output_freq = post_भाग->भागider * freq;
	पूर्ण
	pr_debug("ref_div = %d, ref_clk = %d, output_freq = %d\n",
	       rinfo->pll.ref_भाग, rinfo->pll.ref_clk,
	       pll_output_freq);

	fb_भाग = round_भाग(rinfo->pll.ref_भाग*pll_output_freq,
				  rinfo->pll.ref_clk);
	regs->ppll_ref_भाग = rinfo->pll.ref_भाग;
	regs->ppll_भाग_3 = fb_भाग | (post_भाग->bitvalue << 16);

	pr_debug("post div = 0x%x\n", post_भाग->bitvalue);
	pr_debug("fb_div = 0x%x\n", fb_भाग);
	pr_debug("ppll_div_3 = 0x%x\n", regs->ppll_भाग_3);
पूर्ण

अटल पूर्णांक radeonfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;
	काष्ठा fb_var_screeninfo *mode = &info->var;
	काष्ठा radeon_regs *newmode;
	पूर्णांक hTotal, vTotal, hSyncStart, hSyncEnd,
	    vSyncStart, vSyncEnd;
	u8 hsync_adj_tab[] = अणु0, 0x12, 9, 9, 6, 5पूर्ण;
	u8 hsync_fudge_fp[] = अणु2, 2, 0, 0, 5, 5पूर्ण;
	u32 sync, h_sync_pol, v_sync_pol, करोtClock, pixClock;
	पूर्णांक i, freq;
	पूर्णांक क्रमmat = 0;
	पूर्णांक nopllcalc = 0;
	पूर्णांक hsync_start, hsync_fudge, hsync_wid, vsync_wid;
	पूर्णांक primary_mon = PRIMARY_MONITOR(rinfo);
	पूर्णांक depth = var_to_depth(mode);
	पूर्णांक use_rmx = 0;

	newmode = kदो_स्मृति(माप(काष्ठा radeon_regs), GFP_KERNEL);
	अगर (!newmode)
		वापस -ENOMEM;

	/* We always want engine to be idle on a mode चयन, even
	 * अगर we won't actually change the mode
	 */
	radeon_engine_idle();

	hSyncStart = mode->xres + mode->right_margin;
	hSyncEnd = hSyncStart + mode->hsync_len;
	hTotal = hSyncEnd + mode->left_margin;

	vSyncStart = mode->yres + mode->lower_margin;
	vSyncEnd = vSyncStart + mode->vsync_len;
	vTotal = vSyncEnd + mode->upper_margin;
	pixClock = mode->pixघड़ी;

	sync = mode->sync;
	h_sync_pol = sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	v_sync_pol = sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;

	अगर (primary_mon == MT_DFP || primary_mon == MT_LCD) अणु
		अगर (rinfo->panel_info.xres < mode->xres)
			mode->xres = rinfo->panel_info.xres;
		अगर (rinfo->panel_info.yres < mode->yres)
			mode->yres = rinfo->panel_info.yres;

		hTotal = mode->xres + rinfo->panel_info.hblank;
		hSyncStart = mode->xres + rinfo->panel_info.hOver_plus;
		hSyncEnd = hSyncStart + rinfo->panel_info.hSync_width;

		vTotal = mode->yres + rinfo->panel_info.vblank;
		vSyncStart = mode->yres + rinfo->panel_info.vOver_plus;
		vSyncEnd = vSyncStart + rinfo->panel_info.vSync_width;

		h_sync_pol = !rinfo->panel_info.hAct_high;
		v_sync_pol = !rinfo->panel_info.vAct_high;

		pixClock = 100000000 / rinfo->panel_info.घड़ी;

		अगर (rinfo->panel_info.use_bios_भागiders) अणु
			nopllcalc = 1;
			newmode->ppll_भाग_3 = rinfo->panel_info.fbk_भागider |
				(rinfo->panel_info.post_भागider << 16);
			newmode->ppll_ref_भाग = rinfo->panel_info.ref_भागider;
		पूर्ण
	पूर्ण
	करोtClock = 1000000000 / pixClock;
	freq = करोtClock / 10; /* x100 */

	pr_debug("hStart = %d, hEnd = %d, hTotal = %d\n",
		hSyncStart, hSyncEnd, hTotal);
	pr_debug("vStart = %d, vEnd = %d, vTotal = %d\n",
		vSyncStart, vSyncEnd, vTotal);

	hsync_wid = (hSyncEnd - hSyncStart) / 8;
	vsync_wid = vSyncEnd - vSyncStart;
	अगर (hsync_wid == 0)
		hsync_wid = 1;
	अन्यथा अगर (hsync_wid > 0x3f)	/* max */
		hsync_wid = 0x3f;

	अगर (vsync_wid == 0)
		vsync_wid = 1;
	अन्यथा अगर (vsync_wid > 0x1f)	/* max */
		vsync_wid = 0x1f;

	क्रमmat = radeon_get_dstbpp(depth);

	अगर ((primary_mon == MT_DFP) || (primary_mon == MT_LCD))
		hsync_fudge = hsync_fudge_fp[क्रमmat-1];
	अन्यथा
		hsync_fudge = hsync_adj_tab[क्रमmat-1];

	hsync_start = hSyncStart - 8 + hsync_fudge;

	newmode->crtc_gen_cntl = CRTC_EXT_DISP_EN | CRTC_EN |
				(क्रमmat << 8);

	/* Clear स्वतः-center etc... */
	newmode->crtc_more_cntl = rinfo->init_state.crtc_more_cntl;
	newmode->crtc_more_cntl &= 0xfffffff0;
	
	अगर ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) अणु
		newmode->crtc_ext_cntl = VGA_ATI_LINEAR | XCRT_CNT_EN;
		अगर (mirror)
			newmode->crtc_ext_cntl |= CRTC_CRT_ON;

		newmode->crtc_gen_cntl &= ~(CRTC_DBL_SCAN_EN |
					   CRTC_INTERLACE_EN);
	पूर्ण अन्यथा अणु
		newmode->crtc_ext_cntl = VGA_ATI_LINEAR | XCRT_CNT_EN |
					CRTC_CRT_ON;
	पूर्ण

	newmode->dac_cntl = /* INREG(DAC_CNTL) | */ DAC_MASK_ALL | DAC_VGA_ADR_EN |
			   DAC_8BIT_EN;

	newmode->crtc_h_total_disp = ((((hTotal / 8) - 1) & 0x3ff) |
				     (((mode->xres / 8) - 1) << 16));

	newmode->crtc_h_sync_strt_wid = ((hsync_start & 0x1fff) |
					(hsync_wid << 16) | (h_sync_pol << 23));

	newmode->crtc_v_total_disp = ((vTotal - 1) & 0xffff) |
				    ((mode->yres - 1) << 16);

	newmode->crtc_v_sync_strt_wid = (((vSyncStart - 1) & 0xfff) |
					 (vsync_wid << 16) | (v_sync_pol  << 23));

	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED)) अणु
		/* We first calculate the engine pitch */
		rinfo->pitch = ((mode->xres_भव * ((mode->bits_per_pixel + 1) / 8) + 0x3f)
 				& ~(0x3f)) >> 6;

		/* Then, re-multiply it to get the CRTC pitch */
		newmode->crtc_pitch = (rinfo->pitch << 3) / ((mode->bits_per_pixel + 1) / 8);
	पूर्ण अन्यथा
		newmode->crtc_pitch = (mode->xres_भव >> 3);

	newmode->crtc_pitch |= (newmode->crtc_pitch << 16);

	/*
	 * It looks like recent chips have a problem with SURFACE_CNTL,
	 * setting SURF_TRANSLATION_DIS completely disables the
	 * swapper as well, so we leave it unset now.
	 */
	newmode->surface_cntl = 0;

#अगर defined(__BIG_ENDIAN)

	/* Setup swapping on both apertures, though we currently
	 * only use aperture 0, enabling swapper on aperture 1
	 * won't harm
	 */
	चयन (mode->bits_per_pixel) अणु
		हाल 16:
			newmode->surface_cntl |= NONSURF_AP0_SWP_16BPP;
			newmode->surface_cntl |= NONSURF_AP1_SWP_16BPP;
			अवरोध;
		हाल 24:	
		हाल 32:
			newmode->surface_cntl |= NONSURF_AP0_SWP_32BPP;
			newmode->surface_cntl |= NONSURF_AP1_SWP_32BPP;
			अवरोध;
	पूर्ण
#पूर्ण_अगर

	/* Clear surface रेजिस्टरs */
	क्रम (i=0; i<8; i++) अणु
		newmode->surf_lower_bound[i] = 0;
		newmode->surf_upper_bound[i] = 0x1f;
		newmode->surf_info[i] = 0;
	पूर्ण

	pr_debug("h_total_disp = 0x%x\t   hsync_strt_wid = 0x%x\n",
		newmode->crtc_h_total_disp, newmode->crtc_h_sync_strt_wid);
	pr_debug("v_total_disp = 0x%x\t   vsync_strt_wid = 0x%x\n",
		newmode->crtc_v_total_disp, newmode->crtc_v_sync_strt_wid);

	rinfo->bpp = mode->bits_per_pixel;
	rinfo->depth = depth;

	pr_debug("pixclock = %lu\n", (अचिन्हित दीर्घ)pixClock);
	pr_debug("freq = %lu\n", (अचिन्हित दीर्घ)freq);

	/* We use PPLL_DIV_3 */
	newmode->clk_cntl_index = 0x300;

	/* Calculate PPLL value अगर necessary */
	अगर (!nopllcalc)
		radeon_calc_pll_regs(rinfo, newmode, freq);

	newmode->vclk_ecp_cntl = rinfo->init_state.vclk_ecp_cntl;

	अगर ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) अणु
		अचिन्हित पूर्णांक hRatio, vRatio;

		अगर (mode->xres > rinfo->panel_info.xres)
			mode->xres = rinfo->panel_info.xres;
		अगर (mode->yres > rinfo->panel_info.yres)
			mode->yres = rinfo->panel_info.yres;

		newmode->fp_horz_stretch = (((rinfo->panel_info.xres / 8) - 1)
					   << HORZ_PANEL_SHIFT);
		newmode->fp_vert_stretch = ((rinfo->panel_info.yres - 1)
					   << VERT_PANEL_SHIFT);

		अगर (mode->xres != rinfo->panel_info.xres) अणु
			hRatio = round_भाग(mode->xres * HORZ_STRETCH_RATIO_MAX,
					   rinfo->panel_info.xres);
			newmode->fp_horz_stretch = (((((अचिन्हित दीर्घ)hRatio) & HORZ_STRETCH_RATIO_MASK)) |
						   (newmode->fp_horz_stretch &
						    (HORZ_PANEL_SIZE | HORZ_FP_LOOP_STRETCH |
						     HORZ_AUTO_RATIO_INC)));
			newmode->fp_horz_stretch |= (HORZ_STRETCH_BLEND |
						    HORZ_STRETCH_ENABLE);
			use_rmx = 1;
		पूर्ण
		newmode->fp_horz_stretch &= ~HORZ_AUTO_RATIO;

		अगर (mode->yres != rinfo->panel_info.yres) अणु
			vRatio = round_भाग(mode->yres * VERT_STRETCH_RATIO_MAX,
					   rinfo->panel_info.yres);
			newmode->fp_vert_stretch = (((((अचिन्हित दीर्घ)vRatio) & VERT_STRETCH_RATIO_MASK)) |
						   (newmode->fp_vert_stretch &
						   (VERT_PANEL_SIZE | VERT_STRETCH_RESERVED)));
			newmode->fp_vert_stretch |= (VERT_STRETCH_BLEND |
						    VERT_STRETCH_ENABLE);
			use_rmx = 1;
		पूर्ण
		newmode->fp_vert_stretch &= ~VERT_AUTO_RATIO_EN;

		newmode->fp_gen_cntl = (rinfo->init_state.fp_gen_cntl & (u32)
				       ~(FP_SEL_CRTC2 |
					 FP_RMX_HVSYNC_CONTROL_EN |
					 FP_DFP_SYNC_SEL |
					 FP_CRT_SYNC_SEL |
					 FP_CRTC_LOCK_8DOT |
					 FP_USE_SHADOW_EN |
					 FP_CRTC_USE_SHADOW_VEND |
					 FP_CRT_SYNC_ALT));

		newmode->fp_gen_cntl |= (FP_CRTC_DONT_SHADOW_VPAR |
					FP_CRTC_DONT_SHADOW_HEND |
					FP_PANEL_FORMAT);

		अगर (IS_R300_VARIANT(rinfo) ||
		    (rinfo->family == CHIP_FAMILY_R200)) अणु
			newmode->fp_gen_cntl &= ~R200_FP_SOURCE_SEL_MASK;
			अगर (use_rmx)
				newmode->fp_gen_cntl |= R200_FP_SOURCE_SEL_RMX;
			अन्यथा
				newmode->fp_gen_cntl |= R200_FP_SOURCE_SEL_CRTC1;
		पूर्ण अन्यथा
			newmode->fp_gen_cntl |= FP_SEL_CRTC1;

		newmode->lvds_gen_cntl = rinfo->init_state.lvds_gen_cntl;
		newmode->lvds_pll_cntl = rinfo->init_state.lvds_pll_cntl;
		newmode->पंचांगds_crc = rinfo->init_state.पंचांगds_crc;
		newmode->पंचांगds_transmitter_cntl = rinfo->init_state.पंचांगds_transmitter_cntl;

		अगर (primary_mon == MT_LCD) अणु
			newmode->lvds_gen_cntl |= (LVDS_ON | LVDS_BLON);
			newmode->fp_gen_cntl &= ~(FP_FPON | FP_TMDS_EN);
		पूर्ण अन्यथा अणु
			/* DFP */
			newmode->fp_gen_cntl |= (FP_FPON | FP_TMDS_EN);
			newmode->पंचांगds_transmitter_cntl &= ~(TMDS_PLLRST);
			/* TMDS_PLL_EN bit is reversed on RV (and mobility) chips */
			अगर (IS_R300_VARIANT(rinfo) ||
			    (rinfo->family == CHIP_FAMILY_R200) || !rinfo->has_CRTC2)
				newmode->पंचांगds_transmitter_cntl &= ~TMDS_PLL_EN;
			अन्यथा
				newmode->पंचांगds_transmitter_cntl |= TMDS_PLL_EN;
			newmode->crtc_ext_cntl &= ~CRTC_CRT_ON;
		पूर्ण

		newmode->fp_crtc_h_total_disp = (((rinfo->panel_info.hblank / 8) & 0x3ff) |
				(((mode->xres / 8) - 1) << 16));
		newmode->fp_crtc_v_total_disp = (rinfo->panel_info.vblank & 0xffff) |
				((mode->yres - 1) << 16);
		newmode->fp_h_sync_strt_wid = ((rinfo->panel_info.hOver_plus & 0x1fff) |
				(hsync_wid << 16) | (h_sync_pol << 23));
		newmode->fp_v_sync_strt_wid = ((rinfo->panel_info.vOver_plus & 0xfff) |
				(vsync_wid << 16) | (v_sync_pol  << 23));
	पूर्ण

	/* करो it! */
	अगर (!rinfo->asleep) अणु
		स_नकल(&rinfo->state, newmode, माप(*newmode));
		radeon_ग_लिखो_mode (rinfo, newmode, 0);
		/* (re)initialize the engine */
		अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
			radeonfb_engine_init (rinfo);
	पूर्ण
	/* Update fix */
	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
        	info->fix.line_length = rinfo->pitch*64;
        अन्यथा
		info->fix.line_length = mode->xres_भव
			* ((mode->bits_per_pixel + 1) / 8);
        info->fix.visual = rinfo->depth == 8 ? FB_VISUAL_PSEUDOCOLOR
		: FB_VISUAL_सूचीECTCOLOR;

#अगर_घोषित CONFIG_BOOTX_TEXT
	/* Update debug text engine */
	btext_update_display(rinfo->fb_base_phys, mode->xres, mode->yres,
			     rinfo->depth, info->fix.line_length);
#पूर्ण_अगर

	kमुक्त(newmode);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा fb_ops radeonfb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_check_var		= radeonfb_check_var,
	.fb_set_par		= radeonfb_set_par,
	.fb_setcolreg		= radeonfb_setcolreg,
	.fb_setcmap		= radeonfb_setcmap,
	.fb_pan_display 	= radeonfb_pan_display,
	.fb_blank		= radeonfb_blank,
	.fb_ioctl		= radeonfb_ioctl,
	.fb_sync		= radeonfb_sync,
	.fb_fillrect		= radeonfb_fillrect,
	.fb_copyarea		= radeonfb_copyarea,
	.fb_imageblit		= radeonfb_imageblit,
पूर्ण;


अटल पूर्णांक radeon_set_fbinfo(काष्ठा radeonfb_info *rinfo)
अणु
	काष्ठा fb_info *info = rinfo->info;

	info->par = rinfo;
	info->pseuकरो_palette = rinfo->pseuकरो_palette;
	info->flags = FBINFO_DEFAULT
		    | FBINFO_HWACCEL_COPYAREA
		    | FBINFO_HWACCEL_FILLRECT
		    | FBINFO_HWACCEL_XPAN
		    | FBINFO_HWACCEL_YPAN;
	info->fbops = &radeonfb_ops;
	info->screen_base = rinfo->fb_base;
	info->screen_size = rinfo->mapped_vram;
	/* Fill fix common fields */
	strlcpy(info->fix.id, rinfo->name, माप(info->fix.id));
        info->fix.smem_start = rinfo->fb_base_phys;
        info->fix.smem_len = rinfo->video_ram;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
        info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
        info->fix.xpanstep = 8;
        info->fix.ypanstep = 1;
        info->fix.ywrapstep = 0;
        info->fix.type_aux = 0;
        info->fix.mmio_start = rinfo->mmio_base_phys;
        info->fix.mmio_len = RADEON_REGSIZE;
	info->fix.accel = FB_ACCEL_ATI_RADEON;

	fb_alloc_cmap(&info->cmap, 256, 0);

	अगर (noaccel)
		info->flags |= FBINFO_HWACCEL_DISABLED;

        वापस 0;
पूर्ण

/*
 * This reconfigure the card's internal memory map. In theory, we'd like
 * to setup the card's memory at the same address as it's PCI bus address,
 * and the AGP aperture right after that so that प्रणाली RAM on 32 bits
 * machines at least, is directly accessible. However, करोing so would
 * conflict with the current XFree drivers...
 * Ultimately, I hope XFree, GATOS and ATI binary drivers will all agree
 * on the proper way to set this up and duplicate this here. In the meanसमय,
 * I put the card's memory at 0 in card space and AGP at some अक्रमom high
 * local (0xe0000000 क्रम now) that will be changed by XFree/DRI anyway
 */
#अगर_घोषित CONFIG_PPC
#अघोषित SET_MC_FB_FROM_APERTURE
अटल व्योम fixup_memory_mappings(काष्ठा radeonfb_info *rinfo)
अणु
	u32 save_crtc_gen_cntl, save_crtc2_gen_cntl = 0;
	u32 save_crtc_ext_cntl;
	u32 aper_base, aper_size;
	u32 agp_base;

	/* First, we disable display to aव्योम पूर्णांकerfering */
	अगर (rinfo->has_CRTC2) अणु
		save_crtc2_gen_cntl = INREG(CRTC2_GEN_CNTL);
		OUTREG(CRTC2_GEN_CNTL, save_crtc2_gen_cntl | CRTC2_DISP_REQ_EN_B);
	पूर्ण
	save_crtc_gen_cntl = INREG(CRTC_GEN_CNTL);
	save_crtc_ext_cntl = INREG(CRTC_EXT_CNTL);
	
	OUTREG(CRTC_EXT_CNTL, save_crtc_ext_cntl | CRTC_DISPLAY_DIS);
	OUTREG(CRTC_GEN_CNTL, save_crtc_gen_cntl | CRTC_DISP_REQ_EN_B);
	mdelay(100);

	aper_base = INREG(CNFG_APER_0_BASE);
	aper_size = INREG(CNFG_APER_SIZE);

#अगर_घोषित SET_MC_FB_FROM_APERTURE
	/* Set framebuffer to be at the same address as set in PCI BAR */
	OUTREG(MC_FB_LOCATION, 
		((aper_base + aper_size - 1) & 0xffff0000) | (aper_base >> 16));
	rinfo->fb_local_base = aper_base;
#अन्यथा
	OUTREG(MC_FB_LOCATION, 0x7fff0000);
	rinfo->fb_local_base = 0;
#पूर्ण_अगर
	agp_base = aper_base + aper_size;
	अगर (agp_base & 0xf0000000)
		agp_base = (aper_base | 0x0fffffff) + 1;

	/* Set AGP to be just after the framebuffer on a 256Mb boundary. This
	 * assumes the FB isn't mapped to 0xf0000000 or above, but this is
	 * always the हाल on PPCs afaik.
	 */
#अगर_घोषित SET_MC_FB_FROM_APERTURE
	OUTREG(MC_AGP_LOCATION, 0xffff0000 | (agp_base >> 16));
#अन्यथा
	OUTREG(MC_AGP_LOCATION, 0xffffe000);
#पूर्ण_अगर

	/* Fixup the display base addresses & engine offsets जबतक we
	 * are at it as well
	 */
#अगर_घोषित SET_MC_FB_FROM_APERTURE
	OUTREG(DISPLAY_BASE_ADDR, aper_base);
	अगर (rinfo->has_CRTC2)
		OUTREG(CRTC2_DISPLAY_BASE_ADDR, aper_base);
	OUTREG(OV0_BASE_ADDR, aper_base);
#अन्यथा
	OUTREG(DISPLAY_BASE_ADDR, 0);
	अगर (rinfo->has_CRTC2)
		OUTREG(CRTC2_DISPLAY_BASE_ADDR, 0);
	OUTREG(OV0_BASE_ADDR, 0);
#पूर्ण_अगर
	mdelay(100);

	/* Restore display settings */
	OUTREG(CRTC_GEN_CNTL, save_crtc_gen_cntl);
	OUTREG(CRTC_EXT_CNTL, save_crtc_ext_cntl);
	अगर (rinfo->has_CRTC2)
		OUTREG(CRTC2_GEN_CNTL, save_crtc2_gen_cntl);	

	pr_debug("aper_base: %08x MC_FB_LOC to: %08x, MC_AGP_LOC to: %08x\n",
		aper_base,
		((aper_base + aper_size - 1) & 0xffff0000) | (aper_base >> 16),
		0xffff0000 | (agp_base >> 16));
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC */


अटल व्योम radeon_identअगरy_vram(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	/* framebuffer size */
        अगर ((rinfo->family == CHIP_FAMILY_RS100) ||
            (rinfo->family == CHIP_FAMILY_RS200) ||
            (rinfo->family == CHIP_FAMILY_RS300) ||
            (rinfo->family == CHIP_FAMILY_RC410) ||
            (rinfo->family == CHIP_FAMILY_RS400) ||
	    (rinfo->family == CHIP_FAMILY_RS480) ) अणु
          u32 tom = INREG(NB_TOM);
          पंचांगp = ((((tom >> 16) - (tom & 0xffff) + 1) << 6) * 1024);

 		radeon_fअगरo_रुको(6);
          OUTREG(MC_FB_LOCATION, tom);
          OUTREG(DISPLAY_BASE_ADDR, (tom & 0xffff) << 16);
          OUTREG(CRTC2_DISPLAY_BASE_ADDR, (tom & 0xffff) << 16);
          OUTREG(OV0_BASE_ADDR, (tom & 0xffff) << 16);

          /* This is supposed to fix the crtc2 noise problem. */
          OUTREG(GRPH2_BUFFER_CNTL, INREG(GRPH2_BUFFER_CNTL) & ~0x7f0000);

          अगर ((rinfo->family == CHIP_FAMILY_RS100) ||
              (rinfo->family == CHIP_FAMILY_RS200)) अणु
             /* This is to workaround the asic bug क्रम RMX, some versions
                of BIOS करोesn't have this रेजिस्टर initialized correctly.
             */
             OUTREGP(CRTC_MORE_CNTL, CRTC_H_CUTOFF_ACTIVE_EN,
                     ~CRTC_H_CUTOFF_ACTIVE_EN);
          पूर्ण
        पूर्ण अन्यथा अणु
          पंचांगp = INREG(CNFG_MEMSIZE);
        पूर्ण

	/* mem size is bits [28:0], mask off the rest */
	rinfo->video_ram = पंचांगp & CNFG_MEMSIZE_MASK;

	/*
	 * Hack to get around some busted production M6's
	 * reporting no ram
	 */
	अगर (rinfo->video_ram == 0) अणु
		चयन (rinfo->pdev->device) अणु
	       	हाल PCI_CHIP_RADEON_LY:
		हाल PCI_CHIP_RADEON_LZ:
	       		rinfo->video_ram = 8192 * 1024;
	       		अवरोध;
	       	शेष:
	       		अवरोध;
		पूर्ण
	पूर्ण


	/*
	 * Now try to identअगरy VRAM type
	 */
	अगर (rinfo->is_IGP || (rinfo->family >= CHIP_FAMILY_R300) ||
	    (INREG(MEM_SDRAM_MODE_REG) & (1<<30)))
		rinfo->vram_ddr = 1;
	अन्यथा
		rinfo->vram_ddr = 0;

	पंचांगp = INREG(MEM_CNTL);
	अगर (IS_R300_VARIANT(rinfo)) अणु
		पंचांगp &=  R300_MEM_NUM_CHANNELS_MASK;
		चयन (पंचांगp) अणु
		हाल 0:  rinfo->vram_width = 64; अवरोध;
		हाल 1:  rinfo->vram_width = 128; अवरोध;
		हाल 2:  rinfo->vram_width = 256; अवरोध;
		शेष: rinfo->vram_width = 128; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((rinfo->family == CHIP_FAMILY_RV100) ||
		   (rinfo->family == CHIP_FAMILY_RS100) ||
		   (rinfo->family == CHIP_FAMILY_RS200))अणु
		अगर (पंचांगp & RV100_MEM_HALF_MODE)
			rinfo->vram_width = 32;
		अन्यथा
			rinfo->vram_width = 64;
	पूर्ण अन्यथा अणु
		अगर (पंचांगp & MEM_NUM_CHANNELS_MASK)
			rinfo->vram_width = 128;
		अन्यथा
			rinfo->vram_width = 64;
	पूर्ण

	/* This may not be correct, as some cards can have half of channel disabled
	 * ToDo: identअगरy these हालs
	 */

	pr_debug("radeonfb (%s): Found %ldk of %s %d bits wide videoram\n",
	       pci_name(rinfo->pdev),
	       rinfo->video_ram / 1024,
	       rinfo->vram_ddr ? "DDR" : "SDRAM",
	       rinfo->vram_width);
पूर्ण

/*
 * Sysfs
 */

अटल sमाप_प्रकार radeon_show_one_edid(अक्षर *buf, loff_t off, माप_प्रकार count, स्थिर u8 *edid)
अणु
	वापस memory_पढ़ो_from_buffer(buf, count, &off, edid, EDID_LENGTH);
पूर्ण


अटल sमाप_प्रकार radeon_show_edid1(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fb_info *info = dev_get_drvdata(dev);
        काष्ठा radeonfb_info *rinfo = info->par;

	वापस radeon_show_one_edid(buf, off, count, rinfo->mon1_EDID);
पूर्ण


अटल sमाप_प्रकार radeon_show_edid2(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fb_info *info = dev_get_drvdata(dev);
        काष्ठा radeonfb_info *rinfo = info->par;

	वापस radeon_show_one_edid(buf, off, count, rinfo->mon2_EDID);
पूर्ण

अटल स्थिर काष्ठा bin_attribute edid1_attr = अणु
	.attr   = अणु
		.name	= "edid1",
		.mode	= 0444,
	पूर्ण,
	.size	= EDID_LENGTH,
	.पढ़ो	= radeon_show_edid1,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute edid2_attr = अणु
	.attr   = अणु
		.name	= "edid2",
		.mode	= 0444,
	पूर्ण,
	.size	= EDID_LENGTH,
	.पढ़ो	= radeon_show_edid2,
पूर्ण;

अटल पूर्णांक radeon_kick_out_firmware_fb(काष्ठा pci_dev *pdev)
अणु
	काष्ठा apertures_काष्ठा *ap;

	ap = alloc_apertures(1);
	अगर (!ap)
		वापस -ENOMEM;

	ap->ranges[0].base = pci_resource_start(pdev, 0);
	ap->ranges[0].size = pci_resource_len(pdev, 0);

	हटाओ_conflicting_framebuffers(ap, KBUILD_MODNAME, false);

	kमुक्त(ap);

	वापस 0;
पूर्ण

अटल पूर्णांक radeonfb_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा radeonfb_info *rinfo;
	पूर्णांक ret;
	अचिन्हित अक्षर c1, c2;
	पूर्णांक err = 0;

	pr_debug("radeonfb_pci_register BEGIN\n");
	
	/* Enable device in PCI config */
	ret = pci_enable_device(pdev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "radeonfb (%s): Cannot enable PCI device\n",
		       pci_name(pdev));
		जाओ err_out;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा radeonfb_info), &pdev->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ err_disable;
	पूर्ण
	rinfo = info->par;
	rinfo->info = info;	
	rinfo->pdev = pdev;
	
	spin_lock_init(&rinfo->reg_lock);
	समयr_setup(&rinfo->lvds_समयr, radeon_lvds_समयr_func, 0);

	c1 = ent->device >> 8;
	c2 = ent->device & 0xff;
	अगर (है_छाप(c1) && है_छाप(c2))
		snम_लिखो(rinfo->name, माप(rinfo->name),
			 "ATI Radeon %x \"%c%c\"", ent->device & 0xffff, c1, c2);
	अन्यथा
		snम_लिखो(rinfo->name, माप(rinfo->name),
			 "ATI Radeon %x", ent->device & 0xffff);

	rinfo->family = ent->driver_data & CHIP_FAMILY_MASK;
	rinfo->chipset = pdev->device;
	rinfo->has_CRTC2 = (ent->driver_data & CHIP_HAS_CRTC2) != 0;
	rinfo->is_mobility = (ent->driver_data & CHIP_IS_MOBILITY) != 0;
	rinfo->is_IGP = (ent->driver_data & CHIP_IS_IGP) != 0;

	/* Set base addrs */
	rinfo->fb_base_phys = pci_resource_start (pdev, 0);
	rinfo->mmio_base_phys = pci_resource_start (pdev, 2);

	ret = radeon_kick_out_firmware_fb(pdev);
	अगर (ret)
		जाओ err_release_fb;

	/* request the mem regions */
	ret = pci_request_region(pdev, 0, "radeonfb framebuffer");
	अगर (ret < 0) अणु
		prपूर्णांकk( KERN_ERR "radeonfb (%s): cannot request region 0.\n",
			pci_name(rinfo->pdev));
		जाओ err_release_fb;
	पूर्ण

	ret = pci_request_region(pdev, 2, "radeonfb mmio");
	अगर (ret < 0) अणु
		prपूर्णांकk( KERN_ERR "radeonfb (%s): cannot request region 2.\n",
			pci_name(rinfo->pdev));
		जाओ err_release_pci0;
	पूर्ण

	/* map the regions */
	rinfo->mmio_base = ioremap(rinfo->mmio_base_phys, RADEON_REGSIZE);
	अगर (!rinfo->mmio_base) अणु
		prपूर्णांकk(KERN_ERR "radeonfb (%s): cannot map MMIO\n",
		       pci_name(rinfo->pdev));
		ret = -EIO;
		जाओ err_release_pci2;
	पूर्ण

	rinfo->fb_local_base = INREG(MC_FB_LOCATION) << 16;

	/*
	 * Check क्रम errata
	 */
	rinfo->errata = 0;
	अगर (rinfo->family == CHIP_FAMILY_R300 &&
	    (INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK)
	    == CFG_ATI_REV_A11)
		rinfo->errata |= CHIP_ERRATA_R300_CG;

	अगर (rinfo->family == CHIP_FAMILY_RV200 ||
	    rinfo->family == CHIP_FAMILY_RS200)
		rinfo->errata |= CHIP_ERRATA_PLL_DUMMYREADS;

	अगर (rinfo->family == CHIP_FAMILY_RV100 ||
	    rinfo->family == CHIP_FAMILY_RS100 ||
	    rinfo->family == CHIP_FAMILY_RS200)
		rinfo->errata |= CHIP_ERRATA_PLL_DELAY;

#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
	/* On PPC, we obtain the OF device-node poपूर्णांकer to the firmware
	 * data क्रम this chip
	 */
	rinfo->of_node = pci_device_to_OF_node(pdev);
	अगर (rinfo->of_node == शून्य)
		prपूर्णांकk(KERN_WARNING "radeonfb (%s): Cannot match card to OF node !\n",
		       pci_name(rinfo->pdev));

#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */
#अगर_घोषित CONFIG_PPC
	/* On PPC, the firmware sets up a memory mapping that tends
	 * to cause lockups when enabling the engine. We reconfigure
	 * the card पूर्णांकernal memory mappings properly
	 */
	fixup_memory_mappings(rinfo);
#पूर्ण_अगर /* CONFIG_PPC */

	/* Get VRAM size and type */
	radeon_identअगरy_vram(rinfo);

	rinfo->mapped_vram = min_t(अचिन्हित दीर्घ, MAX_MAPPED_VRAM, rinfo->video_ram);

	करो अणु
		rinfo->fb_base = ioremap_wc(rinfo->fb_base_phys,
					    rinfo->mapped_vram);
	पूर्ण जबतक (rinfo->fb_base == शून्य &&
		 ((rinfo->mapped_vram /= 2) >= MIN_MAPPED_VRAM));

	अगर (rinfo->fb_base == शून्य) अणु
		prपूर्णांकk (KERN_ERR "radeonfb (%s): cannot map FB\n",
			pci_name(rinfo->pdev));
		ret = -EIO;
		जाओ err_unmap_rom;
	पूर्ण

	pr_debug("radeonfb (%s): mapped %ldk videoram\n", pci_name(rinfo->pdev),
	       rinfo->mapped_vram/1024);

	/*
	 * Map the BIOS ROM अगर any and retrieve PLL parameters from
	 * the BIOS. We skip that on mobility chips as the real panel
	 * values we need aren't in the ROM but in the BIOS image in
	 * memory. This is definitely not the best meacnism though,
	 * we really need the arch code to tell us which is the "primary"
	 * video adapter to use the memory image (or better, the arch
	 * should provide us a copy of the BIOS image to shield us from
	 * archs who would store that अन्यथाwhere and/or could initialize
	 * more than one adapter during boot).
	 */
	अगर (!rinfo->is_mobility)
		radeon_map_ROM(rinfo, pdev);

	/*
	 * On x86, the primary display on laptop may have it's BIOS
	 * ROM अन्यथाwhere, try to locate it at the legacy memory hole.
	 * We probably need to make sure this is the primary display,
	 * but that is dअगरficult without some arch support.
	 */
#अगर_घोषित CONFIG_X86
	अगर (rinfo->bios_seg == शून्य)
		radeon_find_mem_vbios(rinfo);
#पूर्ण_अगर

	/* If both above failed, try the BIOS ROM again क्रम mobility
	 * chips
	 */
	अगर (rinfo->bios_seg == शून्य && rinfo->is_mobility)
		radeon_map_ROM(rinfo, pdev);

	/* Get inक्रमmations about the board's PLL */
	radeon_get_pllinfo(rinfo);

#अगर_घोषित CONFIG_FB_RADEON_I2C
	/* Register I2C bus */
	radeon_create_i2c_busses(rinfo);
#पूर्ण_अगर

	/* set all the vital stuff */
	radeon_set_fbinfo (rinfo);

	/* Probe screen types */
	radeon_probe_screens(rinfo, monitor_layout, ignore_edid);

	/* Build mode list, check out panel native model */
	radeon_check_modes(rinfo, mode_option);

	/* Register some sysfs stuff (should be करोne better) */
	अगर (rinfo->mon1_EDID)
		err |= sysfs_create_bin_file(&rinfo->pdev->dev.kobj,
						&edid1_attr);
	अगर (rinfo->mon2_EDID)
		err |= sysfs_create_bin_file(&rinfo->pdev->dev.kobj,
						&edid2_attr);
	अगर (err)
		pr_warn("%s() Creating sysfs files failed, continuing\n",
			__func__);

	/* save current mode regs beक्रमe we चयन पूर्णांकo the new one
	 * so we can restore this upon __निकास
	 */
	radeon_save_state (rinfo, &rinfo->init_state);
	स_नकल(&rinfo->state, &rinfo->init_state, माप(काष्ठा radeon_regs));

	/* Setup Power Management capabilities */
	अगर (शेष_dynclk < -1) अणु
		/* -2 is special: means  ON on mobility chips and करो not
		 * change on others
		 */
		radeonfb_pm_init(rinfo, rinfo->is_mobility ? 1 : -1, ignore_devlist, क्रमce_sleep);
	पूर्ण अन्यथा
		radeonfb_pm_init(rinfo, शेष_dynclk, ignore_devlist, क्रमce_sleep);

	pci_set_drvdata(pdev, info);

	/* Register with fbdev layer */
	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		prपूर्णांकk (KERN_ERR "radeonfb (%s): could not register framebuffer\n",
			pci_name(rinfo->pdev));
		जाओ err_unmap_fb;
	पूर्ण

	अगर (!nomtrr)
		rinfo->wc_cookie = arch_phys_wc_add(rinfo->fb_base_phys,
						    rinfo->video_ram);

	अगर (backlight)
		radeonfb_bl_init(rinfo);

	prपूर्णांकk ("radeonfb (%s): %s\n", pci_name(rinfo->pdev), rinfo->name);

	अगर (rinfo->bios_seg)
		radeon_unmap_ROM(rinfo, pdev);
	pr_debug("radeonfb_pci_register END\n");

	वापस 0;
err_unmap_fb:
	iounmap(rinfo->fb_base);
err_unmap_rom:
	kमुक्त(rinfo->mon1_EDID);
	kमुक्त(rinfo->mon2_EDID);
	अगर (rinfo->mon1_modedb)
		fb_destroy_modedb(rinfo->mon1_modedb);
	fb_dealloc_cmap(&info->cmap);
#अगर_घोषित CONFIG_FB_RADEON_I2C
	radeon_delete_i2c_busses(rinfo);
#पूर्ण_अगर
	अगर (rinfo->bios_seg)
		radeon_unmap_ROM(rinfo, pdev);
	iounmap(rinfo->mmio_base);
err_release_pci2:
	pci_release_region(pdev, 2);
err_release_pci0:
	pci_release_region(pdev, 0);
err_release_fb:
        framebuffer_release(info);
err_disable:
err_out:
	वापस ret;
पूर्ण



अटल व्योम radeonfb_pci_unरेजिस्टर(काष्ठा pci_dev *pdev)
अणु
        काष्ठा fb_info *info = pci_get_drvdata(pdev);
        काष्ठा radeonfb_info *rinfo = info->par;
 
        अगर (!rinfo)
                वापस;

	radeonfb_pm_निकास(rinfo);

	अगर (rinfo->mon1_EDID)
		sysfs_हटाओ_bin_file(&rinfo->pdev->dev.kobj, &edid1_attr);
	अगर (rinfo->mon2_EDID)
		sysfs_हटाओ_bin_file(&rinfo->pdev->dev.kobj, &edid2_attr);

	del_समयr_sync(&rinfo->lvds_समयr);
	arch_phys_wc_del(rinfo->wc_cookie);
        unरेजिस्टर_framebuffer(info);

        radeonfb_bl_निकास(rinfo);

        iounmap(rinfo->mmio_base);
        iounmap(rinfo->fb_base);
 
	pci_release_region(pdev, 2);
	pci_release_region(pdev, 0);

	kमुक्त(rinfo->mon1_EDID);
	kमुक्त(rinfo->mon2_EDID);
	अगर (rinfo->mon1_modedb)
		fb_destroy_modedb(rinfo->mon1_modedb);
#अगर_घोषित CONFIG_FB_RADEON_I2C
	radeon_delete_i2c_busses(rinfo);
#पूर्ण_अगर        
	fb_dealloc_cmap(&info->cmap);
        framebuffer_release(info);
पूर्ण

#अगर_घोषित CONFIG_PM
#घोषणा RADEONFB_PCI_PM_OPS (&radeonfb_pci_pm_ops)
#अन्यथा
#घोषणा RADEONFB_PCI_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा pci_driver radeonfb_driver = अणु
	.name		= "radeonfb",
	.id_table	= radeonfb_pci_table,
	.probe		= radeonfb_pci_रेजिस्टर,
	.हटाओ		= radeonfb_pci_unरेजिस्टर,
	.driver.pm	= RADEONFB_PCI_PM_OPS,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक __init radeonfb_setup (अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep (&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेदन(this_opt, "noaccel", 7)) अणु
			noaccel = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "mirror", 6)) अणु
			mirror = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "force_dfp", 9)) अणु
			क्रमce_dfp = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "panel_yres:", 11)) अणु
			panel_yres = simple_म_से_अदीर्घ((this_opt+11), शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "backlight:", 10)) अणु
			backlight = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6)) अणु
			nomtrr = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomodeset", 9)) अणु
			nomodeset = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "force_measure_pll", 17)) अणु
			क्रमce_measure_pll = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "ignore_edid", 11)) अणु
			ignore_edid = 1;
#अगर defined(CONFIG_PM) && defined(CONFIG_X86)
	 	पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "force_sleep", 11)) अणु
			क्रमce_sleep = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "ignore_devlist", 14)) अणु
			ignore_devlist = 1;
#पूर्ण_अगर
		पूर्ण अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

अटल पूर्णांक __init radeonfb_init (व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("radeonfb", &option))
		वापस -ENODEV;
	radeonfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver (&radeonfb_driver);
पूर्ण


अटल व्योम __निकास radeonfb_निकास (व्योम)
अणु
	pci_unरेजिस्टर_driver (&radeonfb_driver);
पूर्ण

module_init(radeonfb_init);
module_निकास(radeonfb_निकास);

MODULE_AUTHOR("Ani Joshi");
MODULE_DESCRIPTION("framebuffer driver for ATI Radeon chipset");
MODULE_LICENSE("GPL");
module_param(noaccel, bool, 0);
module_param(शेष_dynclk, पूर्णांक, 0);
MODULE_PARM_DESC(शेष_dynclk, "int: -2=enable on mobility only,-1=do not change,0=off,1=on");
MODULE_PARM_DESC(noaccel, "bool: disable acceleration");
module_param(nomodeset, bool, 0);
MODULE_PARM_DESC(nomodeset, "bool: disable actual setting of video mode");
module_param(mirror, bool, 0);
MODULE_PARM_DESC(mirror, "bool: mirror the display to both monitors");
module_param(क्रमce_dfp, bool, 0);
MODULE_PARM_DESC(क्रमce_dfp, "bool: force display to dfp");
module_param(ignore_edid, bool, 0);
MODULE_PARM_DESC(ignore_edid, "bool: Ignore EDID data when doing DDC probe");
module_param(monitor_layout, अक्षरp, 0);
MODULE_PARM_DESC(monitor_layout, "Specify monitor mapping (like XFree86)");
module_param(क्रमce_measure_pll, bool, 0);
MODULE_PARM_DESC(क्रमce_measure_pll, "Force measurement of PLL (debug)");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "bool: disable use of MTRR registers");
module_param(panel_yres, पूर्णांक, 0);
MODULE_PARM_DESC(panel_yres, "int: set panel yres");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\" ");
#अगर defined(CONFIG_PM) && defined(CONFIG_X86)
module_param(क्रमce_sleep, bool, 0);
MODULE_PARM_DESC(क्रमce_sleep, "bool: force D2 sleep mode on all hardware");
module_param(ignore_devlist, bool, 0);
MODULE_PARM_DESC(ignore_devlist, "bool: ignore workarounds for bugs in specific laptops");
#पूर्ण_अगर
