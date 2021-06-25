<शैली गुरु>
/*
 * linux/drivers/video/stअगरb.c - 
 * Low level Frame buffer driver क्रम HP workstations with 
 * STI (standard text पूर्णांकerface) video firmware.
 *
 * Copyright (C) 2001-2006 Helge Deller <deller@gmx.de>
 * Portions Copyright (C) 2001 Thomas Bogenकरोerfer <tsbogend@alpha.franken.de>
 * 
 * Based on:
 * - linux/drivers/video/artistfb.c -- Artist frame buffer driver
 *	Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 *   - based on skeletonfb, which was
 *	Created 28 Dec 1997 by Geert Uytterhoeven
 * - HP Xhp cfb-based X11 winकरोw driver क्रम XFree86
 *	(c)Copyright 1992 Hewlett-Packard Co.
 *
 * 
 *  The following graphics display devices (NGLE family) are supported by this driver:
 *
 *  HPA4070A	known as "HCRX", a 1280x1024 color device with 8 planes
 *  HPA4071A	known as "HCRX24", a 1280x1024 color device with 24 planes,
 *		optionally available with a hardware accelerator as HPA4071A_Z
 *  HPA1659A	known as "CRX", a 1280x1024 color device with 8 planes
 *  HPA1439A	known as "CRX24", a 1280x1024 color device with 24 planes,
 *		optionally available with a hardware accelerator.
 *  HPA1924A	known as "GRX", a 1280x1024 grayscale device with 8 planes
 *  HPA2269A	known as "Dual CRX", a 1280x1024 color device with 8 planes,
 *		implements support क्रम two displays on a single graphics card.
 *  HP710C	पूर्णांकernal graphics support optionally available on the HP9000s710 SPU,
 *		supports 1280x1024 color displays with 8 planes.
 *  HP710G	same as HP710C, 1280x1024 grayscale only
 *  HP710L	same as HP710C, 1024x768 color only
 *  HP712	पूर्णांकernal graphics support on HP9000s712 SPU, supports 640x480, 
 *		1024x768 or 1280x1024 color displays on 8 planes (Artist)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/* TODO:
 *	- 1bpp mode is completely untested
 *	- add support क्रम h/w acceleration
 *	- add hardware cursor
 *	- स्वतःmatically disable द्विगुन buffering (e.g. on RDI precisionbook laptop)
 */


/* on supported graphic devices you may:
 * #घोषणा FALLBACK_TO_1BPP to fall back to 1 bpp, or
 * #अघोषित  FALLBACK_TO_1BPP to reject support क्रम unsupported cards */
#अघोषित FALLBACK_TO_1BPP

#अघोषित DEBUG_STIFB_REGS		/* debug sti रेजिस्टर accesses */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/grfioctl.h>	/* क्रम HP-UX compatibility */
#समावेश <linux/uaccess.h>

#समावेश "sticore.h"

/* REGION_BASE(fb_info, index) वापसs the भव address क्रम region <index> */
#घोषणा REGION_BASE(fb_info, index) \
	F_EXTEND(fb_info->sti->glob_cfg->region_ptrs[index])

#घोषणा NGLEDEVDEPROM_CRT_REGION 1

#घोषणा NR_PALETTE 256

प्रकार काष्ठा अणु
	__s32	video_config_reg;
	__s32	misc_video_start;
	__s32	horiz_timing_fmt;
	__s32	serr_timing_fmt;
	__s32	vert_timing_fmt;
	__s32	horiz_state;
	__s32	vert_state;
	__s32	vtg_state_elements;
	__s32	pipeline_delay;
	__s32	misc_video_end;
पूर्ण video_setup_t;

प्रकार काष्ठा अणु                  
	__s16	माप_ngle_data;
	__s16	x_size_visible;	    /* visible screen dim in pixels  */
	__s16	y_size_visible;
	__s16	pad2[15];
	__s16	cursor_pipeline_delay;
	__s16	video_पूर्णांकerleaves;
	__s32	pad3[11];
पूर्ण ngle_rom_t;

काष्ठा stअगरb_info अणु
	काष्ठा fb_info info;
	अचिन्हित पूर्णांक id;
	ngle_rom_t ngle_rom;
	काष्ठा sti_काष्ठा *sti;
	पूर्णांक deviceSpecअगरicConfig;
	u32 pseuकरो_palette[16];
पूर्ण;

अटल पूर्णांक __initdata stअगरb_bpp_pref[MAX_STI_ROMS];

/* ------------------- chipset specअगरic functions -------------------------- */

/* offsets to graphic-chip पूर्णांकernal रेजिस्टरs */

#घोषणा REG_1		0x000118
#घोषणा REG_2		0x000480
#घोषणा REG_3		0x0004a0
#घोषणा REG_4		0x000600
#घोषणा REG_6		0x000800
#घोषणा REG_7		0x000804
#घोषणा REG_8		0x000820
#घोषणा REG_9		0x000a04
#घोषणा REG_10		0x018000
#घोषणा REG_11		0x018004
#घोषणा REG_12		0x01800c
#घोषणा REG_13		0x018018
#घोषणा REG_14  	0x01801c
#घोषणा REG_15		0x200000
#घोषणा REG_15b0	0x200000
#घोषणा REG_16b1	0x200005
#घोषणा REG_16b3	0x200007
#घोषणा REG_21		0x200218
#घोषणा REG_22		0x0005a0
#घोषणा REG_23		0x0005c0
#घोषणा REG_24		0x000808
#घोषणा REG_25		0x000b00
#घोषणा REG_26		0x200118
#घोषणा REG_27		0x200308
#घोषणा REG_32		0x21003c
#घोषणा REG_33		0x210040
#घोषणा REG_34		0x200008
#घोषणा REG_35		0x018010
#घोषणा REG_38		0x210020
#घोषणा REG_39		0x210120
#घोषणा REG_40		0x210130
#घोषणा REG_42		0x210028
#घोषणा REG_43		0x21002c
#घोषणा REG_44		0x210030
#घोषणा REG_45		0x210034

#घोषणा READ_BYTE(fb,reg)		gsc_पढ़ोb((fb)->info.fix.mmio_start + (reg))
#घोषणा READ_WORD(fb,reg)		gsc_पढ़ोl((fb)->info.fix.mmio_start + (reg))


#अगर_अघोषित DEBUG_STIFB_REGS
# define  DEBUG_OFF()
# define  DEBUG_ON()
# define WRITE_BYTE(value,fb,reg)	gsc_ग_लिखोb((value),(fb)->info.fix.mmio_start + (reg))
# define WRITE_WORD(value,fb,reg)	gsc_ग_लिखोl((value),(fb)->info.fix.mmio_start + (reg))
#अन्यथा
  अटल पूर्णांक debug_on = 1;
# define  DEBUG_OFF() debug_on=0
# define  DEBUG_ON()  debug_on=1
# define WRITE_BYTE(value,fb,reg)	करो अणु अगर (debug_on) \
						prपूर्णांकk(KERN_DEBUG "%30s: WRITE_BYTE(0x%06x) = 0x%02x (old=0x%02x)\n", \
							__func__, reg, value, READ_BYTE(fb,reg)); 		  \
					gsc_ग_लिखोb((value),(fb)->info.fix.mmio_start + (reg)); पूर्ण जबतक (0)
# define WRITE_WORD(value,fb,reg)	करो अणु अगर (debug_on) \
						prपूर्णांकk(KERN_DEBUG "%30s: WRITE_WORD(0x%06x) = 0x%08x (old=0x%08x)\n", \
							__func__, reg, value, READ_WORD(fb,reg)); 		  \
					gsc_ग_लिखोl((value),(fb)->info.fix.mmio_start + (reg)); पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG_STIFB_REGS */


#घोषणा ENABLE	1	/* क्रम enabling/disabling screen */	
#घोषणा DISABLE 0

#घोषणा NGLE_LOCK(fb_info)	करो अणु पूर्ण जबतक (0) 
#घोषणा NGLE_UNLOCK(fb_info)	करो अणु पूर्ण जबतक (0)

अटल व्योम
SETUP_HW(काष्ठा stअगरb_info *fb)
अणु
	अक्षर stat;

	करो अणु
		stat = READ_BYTE(fb, REG_15b0);
		अगर (!stat)
	    		stat = READ_BYTE(fb, REG_15b0);
	पूर्ण जबतक (stat);
पूर्ण


अटल व्योम
SETUP_FB(काष्ठा stअगरb_info *fb)
अणु	
	अचिन्हित पूर्णांक reg10_value = 0;
	
	SETUP_HW(fb);
	चयन (fb->id)
	अणु
		हाल CRT_ID_VISUALIZE_EG:
		हाल S9000_ID_ARTIST:
		हाल S9000_ID_A1659A:
			reg10_value = 0x13601000;
			अवरोध;
		हाल S9000_ID_A1439A:
			अगर (fb->info.var.bits_per_pixel == 32)						
				reg10_value = 0xBBA0A000;
			अन्यथा 
				reg10_value = 0x13601000;
			अवरोध;
		हाल S9000_ID_HCRX:
			अगर (fb->info.var.bits_per_pixel == 32)
				reg10_value = 0xBBA0A000;
			अन्यथा					
				reg10_value = 0x13602000;
			अवरोध;
		हाल S9000_ID_TIMBER:
		हाल CRX24_OVERLAY_PLANES:
			reg10_value = 0x13602000;
			अवरोध;
	पूर्ण
	अगर (reg10_value)
		WRITE_WORD(reg10_value, fb, REG_10);
	WRITE_WORD(0x83000300, fb, REG_14);
	SETUP_HW(fb);
	WRITE_BYTE(1, fb, REG_16b1);
पूर्ण

अटल व्योम
START_IMAGE_COLORMAP_ACCESS(काष्ठा stअगरb_info *fb)
अणु
	SETUP_HW(fb);
	WRITE_WORD(0xBBE0F000, fb, REG_10);
	WRITE_WORD(0x03000300, fb, REG_14);
	WRITE_WORD(~0, fb, REG_13);
पूर्ण

अटल व्योम
WRITE_IMAGE_COLOR(काष्ठा stअगरb_info *fb, पूर्णांक index, पूर्णांक color) 
अणु
	SETUP_HW(fb);
	WRITE_WORD(((0x100+index)<<2), fb, REG_3);
	WRITE_WORD(color, fb, REG_4);
पूर्ण

अटल व्योम
FINISH_IMAGE_COLORMAP_ACCESS(काष्ठा stअगरb_info *fb) 
अणु		
	WRITE_WORD(0x400, fb, REG_2);
	अगर (fb->info.var.bits_per_pixel == 32) अणु
		WRITE_WORD(0x83000100, fb, REG_1);
	पूर्ण अन्यथा अणु
		अगर (fb->id == S9000_ID_ARTIST || fb->id == CRT_ID_VISUALIZE_EG)
			WRITE_WORD(0x80000100, fb, REG_26);
		अन्यथा							
			WRITE_WORD(0x80000100, fb, REG_1);
	पूर्ण
	SETUP_FB(fb);
पूर्ण

अटल व्योम
SETUP_RAMDAC(काष्ठा stअगरb_info *fb) 
अणु
	SETUP_HW(fb);
	WRITE_WORD(0x04000000, fb, 0x1020);
	WRITE_WORD(0xff000000, fb, 0x1028);
पूर्ण

अटल व्योम 
CRX24_SETUP_RAMDAC(काष्ठा stअगरb_info *fb) 
अणु
	SETUP_HW(fb);
	WRITE_WORD(0x04000000, fb, 0x1000);
	WRITE_WORD(0x02000000, fb, 0x1004);
	WRITE_WORD(0xff000000, fb, 0x1008);
	WRITE_WORD(0x05000000, fb, 0x1000);
	WRITE_WORD(0x02000000, fb, 0x1004);
	WRITE_WORD(0x03000000, fb, 0x1008);
पूर्ण

#अगर 0
अटल व्योम 
HCRX_SETUP_RAMDAC(काष्ठा stअगरb_info *fb)
अणु
	WRITE_WORD(0xffffffff, fb, REG_32);
पूर्ण
#पूर्ण_अगर

अटल व्योम 
CRX24_SET_OVLY_MASK(काष्ठा stअगरb_info *fb)
अणु
	SETUP_HW(fb);
	WRITE_WORD(0x13a02000, fb, REG_11);
	WRITE_WORD(0x03000300, fb, REG_14);
	WRITE_WORD(0x000017f0, fb, REG_3);
	WRITE_WORD(0xffffffff, fb, REG_13);
	WRITE_WORD(0xffffffff, fb, REG_22);
	WRITE_WORD(0x00000000, fb, REG_23);
पूर्ण

अटल व्योम
ENABLE_DISABLE_DISPLAY(काष्ठा stअगरb_info *fb, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक value = enable ? 0x43000000 : 0x03000000;
        SETUP_HW(fb);
        WRITE_WORD(0x06000000,	fb, 0x1030);
        WRITE_WORD(value, 	fb, 0x1038);
पूर्ण

अटल व्योम 
CRX24_ENABLE_DISABLE_DISPLAY(काष्ठा stअगरb_info *fb, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक value = enable ? 0x10000000 : 0x30000000;
	SETUP_HW(fb);
	WRITE_WORD(0x01000000,	fb, 0x1000);
	WRITE_WORD(0x02000000,	fb, 0x1004);
	WRITE_WORD(value,	fb, 0x1008);
पूर्ण

अटल व्योम
ARTIST_ENABLE_DISABLE_DISPLAY(काष्ठा stअगरb_info *fb, पूर्णांक enable) 
अणु
	u32 DregsMiscVideo = REG_21;
	u32 DregsMiscCtl = REG_27;
	
	SETUP_HW(fb);
	अगर (enable) अणु
	  WRITE_WORD(READ_WORD(fb, DregsMiscVideo) | 0x0A000000, fb, DregsMiscVideo);
	  WRITE_WORD(READ_WORD(fb, DregsMiscCtl)   | 0x00800000, fb, DregsMiscCtl);
	पूर्ण अन्यथा अणु
	  WRITE_WORD(READ_WORD(fb, DregsMiscVideo) & ~0x0A000000, fb, DregsMiscVideo);
	  WRITE_WORD(READ_WORD(fb, DregsMiscCtl)   & ~0x00800000, fb, DregsMiscCtl);
	पूर्ण
पूर्ण

#घोषणा GET_ROMTABLE_INDEX(fb) \
	(READ_BYTE(fb, REG_16b3) - 1)

#घोषणा HYPER_CONFIG_PLANES_24 0x00000100
	
#घोषणा IS_24_DEVICE(fb) \
	(fb->deviceSpecअगरicConfig & HYPER_CONFIG_PLANES_24)

#घोषणा IS_888_DEVICE(fb) \
	(!(IS_24_DEVICE(fb)))

#घोषणा GET_FIFO_SLOTS(fb, cnt, numslots)	\
अणु	जबतक (cnt < numslots) 			\
		cnt = READ_WORD(fb, REG_34);	\
	cnt -= numslots;			\
पूर्ण

#घोषणा	    IndexedDcd	0	/* Pixel data is indexed (pseuकरो) color */
#घोषणा	    Otc04	2	/* Pixels in each दीर्घword transfer (4) */
#घोषणा	    Otc32	5	/* Pixels in each दीर्घword transfer (32) */
#घोषणा	    Ots08	3	/* Each pixel is size (8)d transfer (1) */
#घोषणा	    OtsIndirect	6	/* Each bit goes through FG/BG color(8) */
#घोषणा	    AddrLong	5	/* FB address is Long aligned (pixel) */
#घोषणा	    BINovly	0x2	/* 8 bit overlay */
#घोषणा	    BINapp0I	0x0	/* Application Buffer 0, Indexed */
#घोषणा	    BINapp1I	0x1	/* Application Buffer 1, Indexed */
#घोषणा	    BINapp0F8	0xa	/* Application Buffer 0, Fractional 8-8-8 */
#घोषणा	    BINattr	0xd	/* Attribute Biपंचांगap */
#घोषणा	    RopSrc 	0x3
#घोषणा	    BiपंचांगapExtent08  3	/* Each ग_लिखो hits ( 8) bits in depth */
#घोषणा	    BiपंचांगapExtent32  5	/* Each ग_लिखो hits (32) bits in depth */
#घोषणा	    DataDynamic	    0	/* Data रेजिस्टर reloaded by direct access */
#घोषणा	    MaskDynamic	    1	/* Mask रेजिस्टर reloaded by direct access */
#घोषणा	    MaskOtc	    0	/* Mask contains Object Count valid bits */

#घोषणा MaskAddrOffset(offset) (offset)
#घोषणा StaticReg(en) (en)
#घोषणा BGx(en) (en)
#घोषणा FGx(en) (en)

#घोषणा BAJustPoपूर्णांक(offset) (offset)
#घोषणा BAIndexBase(base) (base)
#घोषणा BA(F,C,S,A,J,B,I) \
	(((F)<<31)|((C)<<27)|((S)<<24)|((A)<<21)|((J)<<16)|((B)<<12)|(I))

#घोषणा IBOvals(R,M,X,S,D,L,B,F) \
	(((R)<<8)|((M)<<16)|((X)<<24)|((S)<<29)|((D)<<28)|((L)<<31)|((B)<<1)|(F))

#घोषणा NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb, val) \
	WRITE_WORD(val, fb, REG_14)

#घोषणा NGLE_QUICK_SET_DST_BM_ACCESS(fb, val) \
	WRITE_WORD(val, fb, REG_11)

#घोषणा NGLE_QUICK_SET_CTL_PLN_REG(fb, val) \
	WRITE_WORD(val, fb, REG_12)

#घोषणा NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, plnmsk32) \
	WRITE_WORD(plnmsk32, fb, REG_13)

#घोषणा NGLE_REALLY_SET_IMAGE_FG_COLOR(fb, fg32) \
	WRITE_WORD(fg32, fb, REG_35)

#घोषणा NGLE_SET_TRANSFERDATA(fb, val) \
	WRITE_WORD(val, fb, REG_8)

#घोषणा NGLE_SET_DSTXY(fb, val) \
	WRITE_WORD(val, fb, REG_6)

#घोषणा NGLE_LONG_FB_ADDRESS(fbaddrbase, x, y) (		\
	(u32) (fbaddrbase) +					\
	    (	(अचिन्हित पूर्णांक)  ( (y) << 13      ) |		\
		(अचिन्हित पूर्णांक)  ( (x) << 2       )	)	\
	)

#घोषणा NGLE_BINC_SET_DSTADDR(fb, addr) \
	WRITE_WORD(addr, fb, REG_3)

#घोषणा NGLE_BINC_SET_SRCADDR(fb, addr) \
	WRITE_WORD(addr, fb, REG_2)

#घोषणा NGLE_BINC_SET_DSTMASK(fb, mask) \
	WRITE_WORD(mask, fb, REG_22)

#घोषणा NGLE_BINC_WRITE32(fb, data32) \
	WRITE_WORD(data32, fb, REG_23)

#घोषणा START_COLORMAPLOAD(fb, cmapBltCtlData32) \
	WRITE_WORD((cmapBltCtlData32), fb, REG_38)

#घोषणा SET_LENXY_START_RECFILL(fb, lenxy) \
	WRITE_WORD(lenxy, fb, REG_9)

#घोषणा SETUP_COPYAREA(fb) \
	WRITE_BYTE(0, fb, REG_16b1)

अटल व्योम
HYPER_ENABLE_DISABLE_DISPLAY(काष्ठा stअगरb_info *fb, पूर्णांक enable)
अणु
	u32 DregsHypMiscVideo = REG_33;
	अचिन्हित पूर्णांक value;
	SETUP_HW(fb);
	value = READ_WORD(fb, DregsHypMiscVideo);
	अगर (enable)
		value |= 0x0A000000;
	अन्यथा
		value &= ~0x0A000000;
	WRITE_WORD(value, fb, DregsHypMiscVideo);
पूर्ण


/* BufferNumbers used by SETUP_ATTR_ACCESS() */
#घोषणा BUFF0_CMAP0	0x00001e02
#घोषणा BUFF1_CMAP0	0x02001e02
#घोषणा BUFF1_CMAP3	0x0c001e02
#घोषणा ARTIST_CMAP0	0x00000102
#घोषणा HYPER_CMAP8	0x00000100
#घोषणा HYPER_CMAP24	0x00000800

अटल व्योम
SETUP_ATTR_ACCESS(काष्ठा stअगरb_info *fb, अचिन्हित BufferNumber)
अणु
	SETUP_HW(fb);
	WRITE_WORD(0x2EA0D000, fb, REG_11);
	WRITE_WORD(0x23000302, fb, REG_14);
	WRITE_WORD(BufferNumber, fb, REG_12);
	WRITE_WORD(0xffffffff, fb, REG_8);
पूर्ण

अटल व्योम
SET_ATTR_SIZE(काष्ठा stअगरb_info *fb, पूर्णांक width, पूर्णांक height) 
अणु
	/* REG_6 seems to have special values when run on a 
	   RDI precisionbook parisc laptop (INTERNAL_EG_DX1024 or
	   INTERNAL_EG_X1024).  The values are:
		0x2f0: पूर्णांकernal (LCD) & बाह्यal display enabled
		0x2a0: बाह्यal display only
		0x000: zero on standard artist graphic cards
	*/ 
	WRITE_WORD(0x00000000, fb, REG_6);
	WRITE_WORD((width<<16) | height, fb, REG_9);
	WRITE_WORD(0x05000000, fb, REG_6);
	WRITE_WORD(0x00040001, fb, REG_9);
पूर्ण

अटल व्योम
FINISH_ATTR_ACCESS(काष्ठा stअगरb_info *fb) 
अणु
	SETUP_HW(fb);
	WRITE_WORD(0x00000000, fb, REG_12);
पूर्ण

अटल व्योम
elkSetupPlanes(काष्ठा stअगरb_info *fb)
अणु
	SETUP_RAMDAC(fb);
	SETUP_FB(fb);
पूर्ण

अटल व्योम 
ngleSetupAttrPlanes(काष्ठा stअगरb_info *fb, पूर्णांक BufferNumber)
अणु
	SETUP_ATTR_ACCESS(fb, BufferNumber);
	SET_ATTR_SIZE(fb, fb->info.var.xres, fb->info.var.yres);
	FINISH_ATTR_ACCESS(fb);
	SETUP_FB(fb);
पूर्ण


अटल व्योम
rattlerSetupPlanes(काष्ठा stअगरb_info *fb)
अणु
	पूर्णांक saved_id, y;

 	/* Write RAMDAC pixel पढ़ो mask रेजिस्टर so all overlay
	 * planes are display-enabled.  (CRX24 uses Bt462 pixel
	 * पढ़ो mask रेजिस्टर क्रम overlay planes, not image planes).
	 */
	CRX24_SETUP_RAMDAC(fb);
    
	/* change fb->id temporarily to fool SETUP_FB() */
	saved_id = fb->id;
	fb->id = CRX24_OVERLAY_PLANES;
	SETUP_FB(fb);
	fb->id = saved_id;

	क्रम (y = 0; y < fb->info.var.yres; ++y)
		fb_स_रखो(fb->info.screen_base + y * fb->info.fix.line_length,
			0xff, fb->info.var.xres * fb->info.var.bits_per_pixel/8);

	CRX24_SET_OVLY_MASK(fb);
	SETUP_FB(fb);
पूर्ण


#घोषणा HYPER_CMAP_TYPE				0
#घोषणा NGLE_CMAP_INDEXED0_TYPE			0
#घोषणा NGLE_CMAP_OVERLAY_TYPE			3

/* प्रकार of LUT (Colormap) BLT Control Register */
प्रकार जोड़	/* Note assumption that fields are packed left-to-right */
अणु	u32 all;
	काष्ठा
	अणु
		अचिन्हित enable              :  1;
		अचिन्हित रुकोBlank           :  1;
		अचिन्हित reserved1           :  4;
		अचिन्हित lutOffset           : 10;   /* Within destination LUT */
		अचिन्हित lutType             :  2;   /* Cursor, image, overlay */
		अचिन्हित reserved2           :  4;
		अचिन्हित length              : 10;
	पूर्ण fields;
पूर्ण NgleLutBltCtl;


#अगर 0
अटल NgleLutBltCtl
setNgleLutBltCtl(काष्ठा stअगरb_info *fb, पूर्णांक offsetWithinLut, पूर्णांक length)
अणु
	NgleLutBltCtl lutBltCtl;

	/* set enable, zero reserved fields */
	lutBltCtl.all           = 0x80000000;
	lutBltCtl.fields.length = length;

	चयन (fb->id) 
	अणु
	हाल S9000_ID_A1439A:		/* CRX24 */
		अगर (fb->var.bits_per_pixel == 8) अणु
			lutBltCtl.fields.lutType = NGLE_CMAP_OVERLAY_TYPE;
			lutBltCtl.fields.lutOffset = 0;
		पूर्ण अन्यथा अणु
			lutBltCtl.fields.lutType = NGLE_CMAP_INDEXED0_TYPE;
			lutBltCtl.fields.lutOffset = 0 * 256;
		पूर्ण
		अवरोध;
		
	हाल S9000_ID_ARTIST:
		lutBltCtl.fields.lutType = NGLE_CMAP_INDEXED0_TYPE;
		lutBltCtl.fields.lutOffset = 0 * 256;
		अवरोध;
		
	शेष:
		lutBltCtl.fields.lutType = NGLE_CMAP_INDEXED0_TYPE;
		lutBltCtl.fields.lutOffset = 0;
		अवरोध;
	पूर्ण

	/* Offset poपूर्णांकs to start of LUT.  Adjust क्रम within LUT */
	lutBltCtl.fields.lutOffset += offsetWithinLut;

	वापस lutBltCtl;
पूर्ण
#पूर्ण_अगर

अटल NgleLutBltCtl
setHyperLutBltCtl(काष्ठा stअगरb_info *fb, पूर्णांक offsetWithinLut, पूर्णांक length) 
अणु
	NgleLutBltCtl lutBltCtl;

	/* set enable, zero reserved fields */
	lutBltCtl.all = 0x80000000;

	lutBltCtl.fields.length = length;
	lutBltCtl.fields.lutType = HYPER_CMAP_TYPE;

	/* Expect lutIndex to be 0 or 1 क्रम image cmaps, 2 or 3 क्रम overlay cmaps */
	अगर (fb->info.var.bits_per_pixel == 8)
		lutBltCtl.fields.lutOffset = 2 * 256;
	अन्यथा
		lutBltCtl.fields.lutOffset = 0 * 256;

	/* Offset poपूर्णांकs to start of LUT.  Adjust क्रम within LUT */
	lutBltCtl.fields.lutOffset += offsetWithinLut;

	वापस lutBltCtl;
पूर्ण


अटल व्योम hyperUnकरोITE(काष्ठा stअगरb_info *fb)
अणु
	पूर्णांक nFreeFअगरoSlots = 0;
	u32 fbAddr;

	NGLE_LOCK(fb);

	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 1);
	WRITE_WORD(0xffffffff, fb, REG_32);

	/* Write overlay transparency mask so only entry 255 is transparent */

	/* Hardware setup क्रम full-depth ग_लिखो to "magic" location */
	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 7);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
		BA(IndexedDcd, Otc04, Ots08, AddrLong,
		BAJustPoपूर्णांक(0), BINovly, BAIndexBase(0)));
	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
		IBOvals(RopSrc, MaskAddrOffset(0),
		BiपंचांगapExtent08, StaticReg(0),
		DataDynamic, MaskOtc, BGx(0), FGx(0)));

	/* Now prepare to ग_लिखो to the "magic" location */
	fbAddr = NGLE_LONG_FB_ADDRESS(0, 1532, 0);
	NGLE_BINC_SET_DSTADDR(fb, fbAddr);
	NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, 0xffffff);
	NGLE_BINC_SET_DSTMASK(fb, 0xffffffff);

	/* Finally, ग_लिखो a zero to clear the mask */
	NGLE_BINC_WRITE32(fb, 0);

	NGLE_UNLOCK(fb);
पूर्ण

अटल व्योम 
ngleDepth8_ClearImagePlanes(काष्ठा stअगरb_info *fb)
अणु
	/* FIXME! */
पूर्ण

अटल व्योम 
ngleDepth24_ClearImagePlanes(काष्ठा stअगरb_info *fb)
अणु
	/* FIXME! */
पूर्ण

अटल व्योम
ngleResetAttrPlanes(काष्ठा stअगरb_info *fb, अचिन्हित पूर्णांक ctlPlaneReg)
अणु
	पूर्णांक nFreeFअगरoSlots = 0;
	u32 packed_dst;
	u32 packed_len;

	NGLE_LOCK(fb);

	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 4);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
				     BA(IndexedDcd, Otc32, OtsIndirect,
					AddrLong, BAJustPoपूर्णांक(0),
					BINattr, BAIndexBase(0)));
	NGLE_QUICK_SET_CTL_PLN_REG(fb, ctlPlaneReg);
	NGLE_SET_TRANSFERDATA(fb, 0xffffffff);

	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvals(RopSrc, MaskAddrOffset(0),
					       BiपंचांगapExtent08, StaticReg(1),
					       DataDynamic, MaskOtc,
					       BGx(0), FGx(0)));
	packed_dst = 0;
	packed_len = (fb->info.var.xres << 16) | fb->info.var.yres;
	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 2);
	NGLE_SET_DSTXY(fb, packed_dst);
	SET_LENXY_START_RECFILL(fb, packed_len);

	/*
	 * In order to work around an ELK hardware problem (Buffy करोesn't
	 * always flush it's buffers when writing to the attribute
	 * planes), at least 4 pixels must be written to the attribute
	 * planes starting at (X == 1280) and (Y != to the last Y written
	 * by BIF):
	 */

	अगर (fb->id == S9000_ID_A1659A) अणु   /* ELK_DEVICE_ID */
		/* It's safe to use scanline zero: */
		packed_dst = (1280 << 16);
		GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 2);
		NGLE_SET_DSTXY(fb, packed_dst);
		packed_len = (4 << 16) | 1;
		SET_LENXY_START_RECFILL(fb, packed_len);
	पूर्ण   /* ELK Hardware Kludge */

	/**** Finally, set the Control Plane Register back to zero: ****/
	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 1);
	NGLE_QUICK_SET_CTL_PLN_REG(fb, 0);
	
	NGLE_UNLOCK(fb);
पूर्ण
    
अटल व्योम
ngleClearOverlayPlanes(काष्ठा stअगरb_info *fb, पूर्णांक mask, पूर्णांक data)
अणु
	पूर्णांक nFreeFअगरoSlots = 0;
	u32 packed_dst;
	u32 packed_len;
    
	NGLE_LOCK(fb);

	/* Hardware setup */
	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 8);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
				     BA(IndexedDcd, Otc04, Ots08, AddrLong,
					BAJustPoपूर्णांक(0), BINovly, BAIndexBase(0)));

        NGLE_SET_TRANSFERDATA(fb, 0xffffffff);  /* Write क्रमeground color */

        NGLE_REALLY_SET_IMAGE_FG_COLOR(fb, data);
        NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, mask);
    
        packed_dst = 0;
        packed_len = (fb->info.var.xres << 16) | fb->info.var.yres;
        NGLE_SET_DSTXY(fb, packed_dst);
    
        /* Write zeroes to overlay planes */		       
	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvals(RopSrc, MaskAddrOffset(0),
					       BiपंचांगapExtent08, StaticReg(0),
					       DataDynamic, MaskOtc, BGx(0), FGx(0)));
		       
        SET_LENXY_START_RECFILL(fb, packed_len);

	NGLE_UNLOCK(fb);
पूर्ण

अटल व्योम 
hyperResetPlanes(काष्ठा stअगरb_info *fb, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक controlPlaneReg;

	NGLE_LOCK(fb);

	अगर (IS_24_DEVICE(fb))
		अगर (fb->info.var.bits_per_pixel == 32)
			controlPlaneReg = 0x04000F00;
		अन्यथा
			controlPlaneReg = 0x00000F00;   /* 0x00000800 should be enough, but lets clear all 4 bits */
	अन्यथा
		controlPlaneReg = 0x00000F00; /* 0x00000100 should be enough, but lets clear all 4 bits */

	चयन (enable) अणु
	हाल ENABLE:
		/* clear screen */
		अगर (IS_24_DEVICE(fb))
			ngleDepth24_ClearImagePlanes(fb);
		अन्यथा
			ngleDepth8_ClearImagePlanes(fb);

		/* Paपूर्णांक attribute planes क्रम शेष हाल.
		 * On Hyperdrive, this means all winकरोws using overlay cmap 0. */
		ngleResetAttrPlanes(fb, controlPlaneReg);

		/* clear overlay planes */
	        ngleClearOverlayPlanes(fb, 0xff, 255);

		/**************************************************
		 ** Also need to counteract ITE settings 
		 **************************************************/
		hyperUnकरोITE(fb);
		अवरोध;

	हाल DISABLE:
		/* clear screen */
		अगर (IS_24_DEVICE(fb))
			ngleDepth24_ClearImagePlanes(fb);
		अन्यथा
			ngleDepth8_ClearImagePlanes(fb);
		ngleResetAttrPlanes(fb, controlPlaneReg);
		ngleClearOverlayPlanes(fb, 0xff, 0);
		अवरोध;

	हाल -1:	/* RESET */
		hyperUnकरोITE(fb);
		ngleResetAttrPlanes(fb, controlPlaneReg);
		अवरोध;
    	पूर्ण
	
	NGLE_UNLOCK(fb);
पूर्ण

/* Return poपूर्णांकer to in-memory काष्ठाure holding ELK device-dependent ROM values. */

अटल व्योम 
ngleGetDeviceRomData(काष्ठा stअगरb_info *fb)
अणु
#अगर 0
XXX: FIXME: !!!
	पूर्णांक	*pBytePerLongDevDepData;/* data byte == LSB */
	पूर्णांक 	*pRomTable;
	NgleDevRomData	*pPackedDevRomData;
	पूर्णांक	sizePackedDevRomData = माप(*pPackedDevRomData);
	अक्षर	*pCard8;
	पूर्णांक	i;
	अक्षर	*mapOrigin = शून्य;
    
	पूर्णांक romTableIdx;

	pPackedDevRomData = fb->ngle_rom;

	SETUP_HW(fb);
	अगर (fb->id == S9000_ID_ARTIST) अणु
		pPackedDevRomData->cursor_pipeline_delay = 4;
		pPackedDevRomData->video_पूर्णांकerleaves     = 4;
	पूर्ण अन्यथा अणु
		/* Get poपूर्णांकer to unpacked byte/दीर्घ data in ROM */
		pBytePerLongDevDepData = fb->sti->regions[NGLEDEVDEPROM_CRT_REGION];

		/* Tomcat supports several resolutions: 1280x1024, 1024x768, 640x480 */
		अगर (fb->id == S9000_ID_TOMCAT)
	अणु
	    /*  jump to the correct ROM table  */
	    GET_ROMTABLE_INDEX(romTableIdx);
	    जबतक  (romTableIdx > 0)
	    अणु
		pCard8 = (Card8 *) pPackedDevRomData;
		pRomTable = pBytePerLongDevDepData;
		/* Pack every fourth byte from ROM पूर्णांकo काष्ठाure */
		क्रम (i = 0; i < sizePackedDevRomData; i++)
		अणु
		    *pCard8++ = (Card8) (*pRomTable++);
		पूर्ण

		pBytePerLongDevDepData = (Card32 *)
			((Card8 *) pBytePerLongDevDepData +
			       pPackedDevRomData->माप_ngle_data);

		romTableIdx--;
	    पूर्ण
	पूर्ण

	pCard8 = (Card8 *) pPackedDevRomData;

	/* Pack every fourth byte from ROM पूर्णांकo काष्ठाure */
	क्रम (i = 0; i < sizePackedDevRomData; i++)
	अणु
	    *pCard8++ = (Card8) (*pBytePerLongDevDepData++);
	पूर्ण
    पूर्ण

    SETUP_FB(fb);
#पूर्ण_अगर
पूर्ण


#घोषणा HYPERBOWL_MODE_FOR_8_OVER_88_LUT0_NO_TRANSPARENCIES	4
#घोषणा HYPERBOWL_MODE01_8_24_LUT0_TRANSPARENT_LUT1_OPAQUE	8
#घोषणा HYPERBOWL_MODE01_8_24_LUT0_OPAQUE_LUT1_OPAQUE		10
#घोषणा HYPERBOWL_MODE2_8_24					15

/* HCRX specअगरic boot-समय initialization */
अटल व्योम __init
SETUP_HCRX(काष्ठा stअगरb_info *fb)
अणु
	पूर्णांक	hyperbowl;
        पूर्णांक	nFreeFअगरoSlots = 0;

	अगर (fb->id != S9000_ID_HCRX)
		वापस;

	/* Initialize Hyperbowl रेजिस्टरs */
	GET_FIFO_SLOTS(fb, nFreeFअगरoSlots, 7);
	
	अगर (IS_24_DEVICE(fb)) अणु
		hyperbowl = (fb->info.var.bits_per_pixel == 32) ?
			HYPERBOWL_MODE01_8_24_LUT0_TRANSPARENT_LUT1_OPAQUE :
			HYPERBOWL_MODE01_8_24_LUT0_OPAQUE_LUT1_OPAQUE;

		/* First ग_लिखो to Hyperbowl must happen twice (bug) */
		WRITE_WORD(hyperbowl, fb, REG_40);
		WRITE_WORD(hyperbowl, fb, REG_40);
		
		WRITE_WORD(HYPERBOWL_MODE2_8_24, fb, REG_39);
		
		WRITE_WORD(0x014c0148, fb, REG_42); /* Set lut 0 to be the direct color */
		WRITE_WORD(0x404c4048, fb, REG_43);
		WRITE_WORD(0x034c0348, fb, REG_44);
		WRITE_WORD(0x444c4448, fb, REG_45);
	पूर्ण अन्यथा अणु
		hyperbowl = HYPERBOWL_MODE_FOR_8_OVER_88_LUT0_NO_TRANSPARENCIES;

		/* First ग_लिखो to Hyperbowl must happen twice (bug) */
		WRITE_WORD(hyperbowl, fb, REG_40);
		WRITE_WORD(hyperbowl, fb, REG_40);

		WRITE_WORD(0x00000000, fb, REG_42);
		WRITE_WORD(0x00000000, fb, REG_43);
		WRITE_WORD(0x00000000, fb, REG_44);
		WRITE_WORD(0x444c4048, fb, REG_45);
	पूर्ण
पूर्ण


/* ------------------- driver specअगरic functions --------------------------- */

अटल पूर्णांक
stअगरb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
	      u_पूर्णांक blue, u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा stअगरb_info *fb = container_of(info, काष्ठा stअगरb_info, info);
	u32 color;

	अगर (regno >= NR_PALETTE)
		वापस 1;

	red   >>= 8;
	green >>= 8;
	blue  >>= 8;

	DEBUG_OFF();

	START_IMAGE_COLORMAP_ACCESS(fb);

	अगर (unlikely(fb->info.var.grayscale)) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		color = ((red * 77) +
			 (green * 151) +
			 (blue * 28)) >> 8;
	पूर्ण अन्यथा अणु
		color = ((red << 16) |
			 (green << 8) |
			 (blue));
	पूर्ण

	अगर (fb->info.fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		काष्ठा fb_var_screeninfo *var = &fb->info.var;
		अगर (regno < 16)
			((u32 *)fb->info.pseuकरो_palette)[regno] =
				regno << var->red.offset |
				regno << var->green.offset |
				regno << var->blue.offset;
	पूर्ण

	WRITE_IMAGE_COLOR(fb, regno, color);

	अगर (fb->id == S9000_ID_HCRX) अणु
		NgleLutBltCtl lutBltCtl;

		lutBltCtl = setHyperLutBltCtl(fb,
				0,	/* Offset w/i LUT */
				256);	/* Load entire LUT */
		NGLE_BINC_SET_SRCADDR(fb,
				NGLE_LONG_FB_ADDRESS(0, 0x100, 0)); 
				/* 0x100 is same as used in WRITE_IMAGE_COLOR() */
		START_COLORMAPLOAD(fb, lutBltCtl.all);
		SETUP_FB(fb);
	पूर्ण अन्यथा अणु
		/* cleanup colormap hardware */
		FINISH_IMAGE_COLORMAP_ACCESS(fb);
	पूर्ण

	DEBUG_ON();

	वापस 0;
पूर्ण

अटल पूर्णांक
stअगरb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा stअगरb_info *fb = container_of(info, काष्ठा stअगरb_info, info);
	पूर्णांक enable = (blank_mode == 0) ? ENABLE : DISABLE;

	चयन (fb->id) अणु
	हाल S9000_ID_A1439A:
		CRX24_ENABLE_DISABLE_DISPLAY(fb, enable);
		अवरोध;
	हाल CRT_ID_VISUALIZE_EG:
	हाल S9000_ID_ARTIST:
		ARTIST_ENABLE_DISABLE_DISPLAY(fb, enable);
		अवरोध;
	हाल S9000_ID_HCRX:
		HYPER_ENABLE_DISABLE_DISPLAY(fb, enable);
		अवरोध;
	हाल S9000_ID_A1659A:
	हाल S9000_ID_TIMBER:
	हाल CRX24_OVERLAY_PLANES:
	शेष:
		ENABLE_DISABLE_DISPLAY(fb, enable);
		अवरोध;
	पूर्ण
	
	SETUP_FB(fb);
	वापस 0;
पूर्ण

अटल व्योम
stअगरb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा stअगरb_info *fb = container_of(info, काष्ठा stअगरb_info, info);

	SETUP_COPYAREA(fb);

	SETUP_HW(fb);
	अगर (fb->info.var.bits_per_pixel == 32) अणु
		WRITE_WORD(0xBBA0A000, fb, REG_10);

		NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, 0xffffffff);
	पूर्ण अन्यथा अणु
		WRITE_WORD(fb->id == S9000_ID_HCRX ? 0x13a02000 : 0x13a01000, fb, REG_10);

		NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, 0xff);
	पूर्ण

	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
		IBOvals(RopSrc, MaskAddrOffset(0),
		BiपंचांगapExtent08, StaticReg(1),
		DataDynamic, MaskOtc, BGx(0), FGx(0)));

	WRITE_WORD(((area->sx << 16) | area->sy), fb, REG_24);
	WRITE_WORD(((area->width << 16) | area->height), fb, REG_7);
	WRITE_WORD(((area->dx << 16) | area->dy), fb, REG_25);

	SETUP_FB(fb);
पूर्ण

अटल व्योम __init
stअगरb_init_display(काष्ठा stअगरb_info *fb)
अणु
	पूर्णांक id = fb->id;

	SETUP_FB(fb);

	/* HCRX specअगरic initialization */
	SETUP_HCRX(fb);
	
	/*
	अगर (id == S9000_ID_HCRX)
		hyperInitSprite(fb);
	अन्यथा
		ngleInitSprite(fb);
	*/
	
	/* Initialize the image planes. */ 
        चयन (id) अणु
	 हाल S9000_ID_HCRX:
	    hyperResetPlanes(fb, ENABLE);
	    अवरोध;
	 हाल S9000_ID_A1439A:
	    rattlerSetupPlanes(fb);
	    अवरोध;
	 हाल S9000_ID_A1659A:
	 हाल S9000_ID_ARTIST:
	 हाल CRT_ID_VISUALIZE_EG:
	    elkSetupPlanes(fb);
	    अवरोध;
	पूर्ण

	/* Clear attribute planes on non HCRX devices. */
        चयन (id) अणु
	 हाल S9000_ID_A1659A:
	 हाल S9000_ID_A1439A:
	    अगर (fb->info.var.bits_per_pixel == 32)
		ngleSetupAttrPlanes(fb, BUFF1_CMAP3);
	    अन्यथा अणु
		ngleSetupAttrPlanes(fb, BUFF1_CMAP0);
	    पूर्ण
	    अगर (id == S9000_ID_A1439A)
		ngleClearOverlayPlanes(fb, 0xff, 0);
	    अवरोध;
	 हाल S9000_ID_ARTIST:
	 हाल CRT_ID_VISUALIZE_EG:
	    अगर (fb->info.var.bits_per_pixel == 32)
		ngleSetupAttrPlanes(fb, BUFF1_CMAP3);
	    अन्यथा अणु
		ngleSetupAttrPlanes(fb, ARTIST_CMAP0);
	    पूर्ण
	    अवरोध;
	पूर्ण
	stअगरb_blank(0, (काष्ठा fb_info *)fb);	/* 0=enable screen */

	SETUP_FB(fb);
पूर्ण

/* ------------ Interfaces to hardware functions ------------ */

अटल स्थिर काष्ठा fb_ops stअगरb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= stअगरb_setcolreg,
	.fb_blank	= stअगरb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= stअगरb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;


/*
 *  Initialization
 */

अटल पूर्णांक __init stअगरb_init_fb(काष्ठा sti_काष्ठा *sti, पूर्णांक bpp_pref)
अणु
	काष्ठा fb_fix_screeninfo *fix;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा stअगरb_info *fb;
	काष्ठा fb_info *info;
	अचिन्हित दीर्घ sti_rom_address;
	अक्षर *dev_name;
	पूर्णांक bpp, xres, yres;

	fb = kzalloc(माप(*fb), GFP_ATOMIC);
	अगर (!fb)
		वापस -ENOMEM;
	
	info = &fb->info;

	/* set काष्ठा to a known state */
	fix = &info->fix;
	var = &info->var;

	fb->sti = sti;
	dev_name = sti->sti_data->inq_outptr.dev_name;
	/* store upper 32bits of the graphics id */
	fb->id = fb->sti->graphics_id[0];

	/* only supported cards are allowed */
	चयन (fb->id) अणु
	हाल CRT_ID_VISUALIZE_EG:
		/* Visualize cards can run either in "double buffer" or
 		  "standard" mode. Depending on the mode, the card reports
		  a dअगरferent device name, e.g. "INTERNAL_EG_DX1024" in द्विगुन
		  buffer mode and "INTERNAL_EG_X1024" in standard mode.
		  Since this driver only supports standard mode, we check
		  अगर the device name contains the string "DX" and tell the
		  user how to reconfigure the card. */
		अगर (म_माला(dev_name, "DX")) अणु
		   prपूर्णांकk(KERN_WARNING
"WARNING: stifb framebuffer driver does not support '%s' in double-buffer mode.\n"
"WARNING: Please disable the double-buffer mode in IPL menu (the PARISC-BIOS).\n",
			dev_name);
		   जाओ out_err0;
		पूर्ण
		fallthrough;
	हाल S9000_ID_ARTIST:
	हाल S9000_ID_HCRX:
	हाल S9000_ID_TIMBER:
	हाल S9000_ID_A1659A:
	हाल S9000_ID_A1439A:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "stifb: '%s' (id: 0x%08x) not supported.\n",
			dev_name, fb->id);
		जाओ out_err0;
	पूर्ण
	
	/* शेष to 8 bpp on most graphic chips */
	bpp = 8;
	xres = sti_onscreen_x(fb->sti);
	yres = sti_onscreen_y(fb->sti);

	ngleGetDeviceRomData(fb);

	/* get (भव) io region base addr */
	fix->mmio_start = REGION_BASE(fb,2);
	fix->mmio_len   = 0x400000;

       	/* Reject any device not in the NGLE family */
	चयन (fb->id) अणु
	हाल S9000_ID_A1659A:	/* CRX/A1659A */
		अवरोध;
	हाल S9000_ID_ELM:	/* GRX, grayscale but अन्यथा same as A1659A */
		var->grayscale = 1;
		fb->id = S9000_ID_A1659A;
		अवरोध;
	हाल S9000_ID_TIMBER:	/* HP9000/710 Any (may be a grayscale device) */
		अगर (म_माला(dev_name, "GRAYSCALE") || 
		    म_माला(dev_name, "Grayscale") ||
		    म_माला(dev_name, "grayscale"))
			var->grayscale = 1;
		अवरोध;
	हाल S9000_ID_TOMCAT:	/* Dual CRX, behaves अन्यथा like a CRX */
		/* FIXME: TomCat supports two heads:
		 * fb.iobase = REGION_BASE(fb_info,3);
		 * fb.screen_base = ioremap(REGION_BASE(fb_info,2),xxx);
		 * क्रम now we only support the left one ! */
		xres = fb->ngle_rom.x_size_visible;
		yres = fb->ngle_rom.y_size_visible;
		fb->id = S9000_ID_A1659A;
		अवरोध;
	हाल S9000_ID_A1439A:	/* CRX24/A1439A */
		bpp = 32;
		अवरोध;
	हाल S9000_ID_HCRX:	/* Hyperdrive/HCRX */
		स_रखो(&fb->ngle_rom, 0, माप(fb->ngle_rom));
		अगर ((fb->sti->regions_phys[0] & 0xfc000000) ==
		    (fb->sti->regions_phys[2] & 0xfc000000))
			sti_rom_address = F_EXTEND(fb->sti->regions_phys[0]);
		अन्यथा
			sti_rom_address = F_EXTEND(fb->sti->regions_phys[1]);

		fb->deviceSpecअगरicConfig = gsc_पढ़ोl(sti_rom_address);
		अगर (IS_24_DEVICE(fb)) अणु
			अगर (bpp_pref == 8 || bpp_pref == 32)
				bpp = bpp_pref;
			अन्यथा
				bpp = 32;
		पूर्ण अन्यथा
			bpp = 8;
		READ_WORD(fb, REG_15);
		SETUP_HW(fb);
		अवरोध;
	हाल CRT_ID_VISUALIZE_EG:
	हाल S9000_ID_ARTIST:	/* Artist */
		अवरोध;
	शेष: 
#अगर_घोषित FALLBACK_TO_1BPP
	       	prपूर्णांकk(KERN_WARNING 
			"stifb: Unsupported graphics card (id=0x%08x) "
				"- now trying 1bpp mode instead\n",
			fb->id);
		bpp = 1;	/* शेष to 1 bpp */
		अवरोध;
#अन्यथा
	       	prपूर्णांकk(KERN_WARNING 
			"stifb: Unsupported graphics card (id=0x%08x) "
				"- skipping.\n",
			fb->id);
		जाओ out_err0;
#पूर्ण_अगर
	पूर्ण


	/* get framebuffer physical and भव base addr & len (64bit पढ़ोy) */
	fix->smem_start = F_EXTEND(fb->sti->regions_phys[1]);
	fix->smem_len = fb->sti->regions[1].region_desc.length * 4096;

	fix->line_length = (fb->sti->glob_cfg->total_x * bpp) / 8;
	अगर (!fix->line_length)
		fix->line_length = 2048; /* शेष */
	
	/* limit fbsize to max visible screen size */
	अगर (fix->smem_len > yres*fix->line_length)
		fix->smem_len = yres*fix->line_length;
	
	fix->accel = FB_ACCEL_NONE;

	चयन (bpp) अणु
	    हाल 1:
		fix->type = FB_TYPE_PLANES;	/* well, sort of */
		fix->visual = FB_VISUAL_MONO10;
		var->red.length = var->green.length = var->blue.length = 1;
		अवरोध;
	    हाल 8:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		var->red.length = var->green.length = var->blue.length = 8;
		अवरोध;
	    हाल 32:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->visual = FB_VISUAL_सूचीECTCOLOR;
		var->red.length = var->green.length = var->blue.length = var->transp.length = 8;
		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;
		अवरोध;
	    शेष:
		अवरोध;
	पूर्ण
	
	var->xres = var->xres_भव = xres;
	var->yres = var->yres_भव = yres;
	var->bits_per_pixel = bpp;

	म_नकल(fix->id, "stifb");
	info->fbops = &stअगरb_ops;
	info->screen_base = ioremap(REGION_BASE(fb,1), fix->smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "stifb: failed to map memory\n");
		जाओ out_err0;
	पूर्ण
	info->screen_size = fix->smem_len;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_COPYAREA;
	info->pseuकरो_palette = &fb->pseuकरो_palette;

	/* This has to be करोne !!! */
	अगर (fb_alloc_cmap(&info->cmap, NR_PALETTE, 0))
		जाओ out_err1;
	stअगरb_init_display(fb);

	अगर (!request_mem_region(fix->smem_start, fix->smem_len, "stifb fb")) अणु
		prपूर्णांकk(KERN_ERR "stifb: cannot reserve fb region 0x%04lx-0x%04lx\n",
				fix->smem_start, fix->smem_start+fix->smem_len);
		जाओ out_err2;
	पूर्ण
		
	अगर (!request_mem_region(fix->mmio_start, fix->mmio_len, "stifb mmio")) अणु
		prपूर्णांकk(KERN_ERR "stifb: cannot reserve sti mmio region 0x%04lx-0x%04lx\n",
				fix->mmio_start, fix->mmio_start+fix->mmio_len);
		जाओ out_err3;
	पूर्ण

	अगर (रेजिस्टर_framebuffer(&fb->info) < 0)
		जाओ out_err4;

	sti->info = info; /* save क्रम unरेजिस्टर_framebuffer() */

	fb_info(&fb->info, "%s %dx%d-%d frame buffer device, %s, id: %04x, mmio: 0x%04lx\n",
		fix->id,
		var->xres, 
		var->yres,
		var->bits_per_pixel,
		dev_name,
		fb->id, 
		fix->mmio_start);

	वापस 0;


out_err4:
	release_mem_region(fix->mmio_start, fix->mmio_len);
out_err3:
	release_mem_region(fix->smem_start, fix->smem_len);
out_err2:
	fb_dealloc_cmap(&info->cmap);
out_err1:
	iounmap(info->screen_base);
out_err0:
	kमुक्त(fb);
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक stअगरb_disabled __initdata;

पूर्णांक __init
stअगरb_setup(अक्षर *options);

अटल पूर्णांक __init stअगरb_init(व्योम)
अणु
	काष्ठा sti_काष्ठा *sti;
	काष्ठा sti_काष्ठा *def_sti;
	पूर्णांक i;
	
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("stifb", &option))
		वापस -ENODEV;
	stअगरb_setup(option);
#पूर्ण_अगर
	अगर (stअगरb_disabled) अणु
		prपूर्णांकk(KERN_INFO "stifb: disabled by \"stifb=off\" kernel parameter\n");
		वापस -ENXIO;
	पूर्ण
	
	def_sti = sti_get_rom(0);
	अगर (def_sti) अणु
		क्रम (i = 1; i <= MAX_STI_ROMS; i++) अणु
			sti = sti_get_rom(i);
			अगर (!sti)
				अवरोध;
			अगर (sti == def_sti) अणु
				stअगरb_init_fb(sti, stअगरb_bpp_pref[i - 1]);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 1; i <= MAX_STI_ROMS; i++) अणु
		sti = sti_get_rom(i);
		अगर (!sti)
			अवरोध;
		अगर (sti == def_sti)
			जारी;
		stअगरb_init_fb(sti, stअगरb_bpp_pref[i - 1]);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  Cleanup
 */

अटल व्योम __निकास
stअगरb_cleanup(व्योम)
अणु
	काष्ठा sti_काष्ठा *sti;
	पूर्णांक i;
	
	क्रम (i = 1; i <= MAX_STI_ROMS; i++) अणु
		sti = sti_get_rom(i);
		अगर (!sti)
			अवरोध;
		अगर (sti->info) अणु
			काष्ठा fb_info *info = sti->info;
			unरेजिस्टर_framebuffer(sti->info);
			release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
		        release_mem_region(info->fix.smem_start, info->fix.smem_len);
				अगर (info->screen_base)
					iounmap(info->screen_base);
		        fb_dealloc_cmap(&info->cmap);
		        framebuffer_release(info);
		पूर्ण
		sti->info = शून्य;
	पूर्ण
पूर्ण

पूर्णांक __init
stअगरb_setup(अक्षर *options)
अणु
	पूर्णांक i;
	
	अगर (!options || !*options)
		वापस 1;
	
	अगर (म_भेदन(options, "off", 3) == 0) अणु
		stअगरb_disabled = 1;
		options += 3;
	पूर्ण

	अगर (म_भेदन(options, "bpp", 3) == 0) अणु
		options += 3;
		क्रम (i = 0; i < MAX_STI_ROMS; i++) अणु
			अगर (*options++ != ':')
				अवरोध;
			stअगरb_bpp_pref[i] = simple_म_से_अदीर्घ(options, &options, 10);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("stifb=", stअगरb_setup);

module_init(stअगरb_init);
module_निकास(stअगरb_cleanup);

MODULE_AUTHOR("Helge Deller <deller@gmx.de>, Thomas Bogendoerfer <tsbogend@alpha.franken.de>");
MODULE_DESCRIPTION("Framebuffer driver for HP's NGLE series graphics cards in HP PARISC machines");
MODULE_LICENSE("GPL v2");
