<शैली गुरु>
/*
 * drivers/video/cirrusfb.c - driver क्रम Cirrus Logic chipsets
 *
 * Copyright 1999-2001 Jeff Garzik <jgarzik@pobox.com>
 *
 * Contributors (thanks, all!)
 *
 *	David Eger:
 *	Overhaul क्रम Linux 2.6
 *
 *      Jeff Rugen:
 *      Major contributions;  Motorola PowerStack (PPC and PCI) support,
 *      GD54xx, 1280x1024 mode support, change MCLK based on VCLK.
 *
 *	Geert Uytterhoeven:
 *	Excellent code review.
 *
 *	Lars Hecking:
 *	Amiga updates and testing.
 *
 * Original cirrusfb author:  Frank Neumann
 *
 * Based on retz3fb.c and cirrusfb.c:
 *      Copyright (C) 1997 Jes Sorensen
 *      Copyright (C) 1996 Frank Neumann
 *
 ***************************************************************
 *
 * Format this code with GNU indent '-kr -i8 -pcs' options.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>

#अगर_घोषित CONFIG_ZORRO
#समावेश <linux/zorro.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA
#समावेश <यंत्र/amigahw.h>
#पूर्ण_अगर

#समावेश <video/vga.h>
#समावेश <video/cirrus.h>

/*****************************************************************
 *
 * debugging and utility macros
 *
 */

/* disable runसमय निश्चितions? */
/* #घोषणा CIRRUSFB_न_संशोधन */

/* debugging निश्चितions */
#अगर_अघोषित CIRRUSFB_न_संशोधन
#घोषणा निश्चित(expr) \
	अगर (!(expr)) अणु \
		prपूर्णांकk("Assertion failed! %s,%s,%s,line=%d\n", \
		#expr, __खाता__, __func__, __LINE__); \
	पूर्ण
#अन्यथा
#घोषणा निश्चित(expr)
#पूर्ण_अगर

#घोषणा MB_ (1024 * 1024)

/*****************************************************************
 *
 * chipset inक्रमmation
 *
 */

/* board types */
क्रमागत cirrus_board अणु
	BT_NONE = 0,
	BT_SD64,	/* GD5434 */
	BT_PICCOLO,	/* GD5426 */
	BT_PICASSO,	/* GD5426 or GD5428 */
	BT_SPECTRUM,	/* GD5426 or GD5428 */
	BT_PICASSO4,	/* GD5446 */
	BT_ALPINE,	/* GD543x/4x */
	BT_GD5480,
	BT_LAGUNA,	/* GD5462/64 */
	BT_LAGUNAB,	/* GD5465 */
पूर्ण;

/*
 * per-board-type inक्रमmation, used क्रम क्रमागतerating and असलtracting
 * chip-specअगरic inक्रमmation
 * NOTE: MUST be in the same order as क्रमागत cirrus_board in order to
 * use direct indexing on this array
 * NOTE: '__initdata' cannot be used as some of this info
 * is required at runसमय.  Maybe separate पूर्णांकo an init-only and
 * a run-समय table?
 */
अटल स्थिर काष्ठा cirrusfb_board_info_rec अणु
	अक्षर *name;		/* ASCII name of chipset */
	दीर्घ maxघड़ी[5];		/* maximum video घड़ी */
	/* क्रम  1/4bpp, 8bpp 15/16bpp, 24bpp, 32bpp - numbers from xorg code */
	bool init_sr07 : 1; /* init SR07 during init_vgachip() */
	bool init_sr1f : 1; /* ग_लिखो SR1F during init_vgachip() */
	/* स्थिरruct bit 19 of screen start address */
	bool scrn_start_bit19 : 1;

	/* initial SR07 value, then क्रम each mode */
	अचिन्हित अक्षर sr07;
	अचिन्हित अक्षर sr07_1bpp;
	अचिन्हित अक्षर sr07_1bpp_mux;
	अचिन्हित अक्षर sr07_8bpp;
	अचिन्हित अक्षर sr07_8bpp_mux;

	अचिन्हित अक्षर sr1f;	/* SR1F VGA initial रेजिस्टर value */
पूर्ण cirrusfb_board_info[] = अणु
	[BT_SD64] = अणु
		.name			= "CL SD64",
		.maxघड़ी		= अणु
			/* guess */
			/* the SD64/P4 have a higher max. videoघड़ी */
			135100, 135100, 85500, 85500, 0
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= true,
		.sr07			= 0xF0,
		.sr07_1bpp		= 0xF0,
		.sr07_1bpp_mux		= 0xF6,
		.sr07_8bpp		= 0xF1,
		.sr07_8bpp_mux		= 0xF7,
		.sr1f			= 0x1E
	पूर्ण,
	[BT_PICCOLO] = अणु
		.name			= "CL Piccolo",
		.maxघड़ी		= अणु
			/* guess */
			90000, 90000, 90000, 90000, 90000
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= false,
		.sr07			= 0x80,
		.sr07_1bpp		= 0x80,
		.sr07_8bpp		= 0x81,
		.sr1f			= 0x22
	पूर्ण,
	[BT_PICASSO] = अणु
		.name			= "CL Picasso",
		.maxघड़ी		= अणु
			/* guess */
			90000, 90000, 90000, 90000, 90000
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= false,
		.sr07			= 0x20,
		.sr07_1bpp		= 0x20,
		.sr07_8bpp		= 0x21,
		.sr1f			= 0x22
	पूर्ण,
	[BT_SPECTRUM] = अणु
		.name			= "CL Spectrum",
		.maxघड़ी		= अणु
			/* guess */
			90000, 90000, 90000, 90000, 90000
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= false,
		.sr07			= 0x80,
		.sr07_1bpp		= 0x80,
		.sr07_8bpp		= 0x81,
		.sr1f			= 0x22
	पूर्ण,
	[BT_PICASSO4] = अणु
		.name			= "CL Picasso4",
		.maxघड़ी		= अणु
			135100, 135100, 85500, 85500, 0
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= false,
		.scrn_start_bit19	= true,
		.sr07			= 0xA0,
		.sr07_1bpp		= 0xA0,
		.sr07_1bpp_mux		= 0xA6,
		.sr07_8bpp		= 0xA1,
		.sr07_8bpp_mux		= 0xA7,
		.sr1f			= 0
	पूर्ण,
	[BT_ALPINE] = अणु
		.name			= "CL Alpine",
		.maxघड़ी		= अणु
			/* क्रम the GD5430.  GD5446 can करो more... */
			85500, 85500, 50000, 28500, 0
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= true,
		.sr07			= 0xA0,
		.sr07_1bpp		= 0xA0,
		.sr07_1bpp_mux		= 0xA6,
		.sr07_8bpp		= 0xA1,
		.sr07_8bpp_mux		= 0xA7,
		.sr1f			= 0x1C
	पूर्ण,
	[BT_GD5480] = अणु
		.name			= "CL GD5480",
		.maxघड़ी		= अणु
			135100, 200000, 200000, 135100, 135100
		पूर्ण,
		.init_sr07		= true,
		.init_sr1f		= true,
		.scrn_start_bit19	= true,
		.sr07			= 0x10,
		.sr07_1bpp		= 0x11,
		.sr07_8bpp		= 0x11,
		.sr1f			= 0x1C
	पूर्ण,
	[BT_LAGUNA] = अणु
		.name			= "CL Laguna",
		.maxघड़ी		= अणु
			/* taken from X11 code */
			170000, 170000, 170000, 170000, 135100,
		पूर्ण,
		.init_sr07		= false,
		.init_sr1f		= false,
		.scrn_start_bit19	= true,
	पूर्ण,
	[BT_LAGUNAB] = अणु
		.name			= "CL Laguna AGP",
		.maxघड़ी		= अणु
			/* taken from X11 code */
			170000, 250000, 170000, 170000, 135100,
		पूर्ण,
		.init_sr07		= false,
		.init_sr1f		= false,
		.scrn_start_bit19	= true,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PCI
#घोषणा CHIP(id, btype) \
	अणु PCI_VENDOR_ID_CIRRUS, id, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (btype) पूर्ण

अटल काष्ठा pci_device_id cirrusfb_pci_table[] = अणु
	CHIP(PCI_DEVICE_ID_CIRRUS_5436, BT_ALPINE),
	CHIP(PCI_DEVICE_ID_CIRRUS_5434_8, BT_SD64),
	CHIP(PCI_DEVICE_ID_CIRRUS_5434_4, BT_SD64),
	CHIP(PCI_DEVICE_ID_CIRRUS_5430, BT_ALPINE), /* GD-5440 is same id */
	CHIP(PCI_DEVICE_ID_CIRRUS_7543, BT_ALPINE),
	CHIP(PCI_DEVICE_ID_CIRRUS_7548, BT_ALPINE),
	CHIP(PCI_DEVICE_ID_CIRRUS_5480, BT_GD5480), /* MacPicasso likely */
	CHIP(PCI_DEVICE_ID_CIRRUS_5446, BT_PICASSO4), /* Picasso 4 is 5446 */
	CHIP(PCI_DEVICE_ID_CIRRUS_5462, BT_LAGUNA), /* CL Laguna */
	CHIP(PCI_DEVICE_ID_CIRRUS_5464, BT_LAGUNA), /* CL Laguna 3D */
	CHIP(PCI_DEVICE_ID_CIRRUS_5465, BT_LAGUNAB), /* CL Laguna 3DA*/
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cirrusfb_pci_table);
#अघोषित CHIP
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_ZORRO
काष्ठा zorrocl अणु
	क्रमागत cirrus_board type;	/* Board type */
	u32 regoffset;		/* Offset of रेजिस्टरs in first Zorro device */
	u32 ramsize;		/* Size of video RAM in first Zorro device */
				/* If zero, use स्वतःprobe on RAM device */
	u32 ramoffset;		/* Offset of video RAM in first Zorro device */
	zorro_id ramid;		/* Zorro ID of RAM device */
	zorro_id ramid2;	/* Zorro ID of optional second RAM device */
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_sd64 = अणु
	.type		= BT_SD64,
	.ramid		= ZORRO_PROD_HELFRICH_SD64_RAM,
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_piccolo = अणु
	.type		= BT_PICCOLO,
	.ramid		= ZORRO_PROD_HELFRICH_PICCOLO_RAM,
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_picasso = अणु
	.type		= BT_PICASSO,
	.ramid		= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_II_II_PLUS_RAM,
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_spectrum = अणु
	.type		= BT_SPECTRUM,
	.ramid		= ZORRO_PROD_GVP_EGS_28_24_SPECTRUM_RAM,
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_picasso4_z3 = अणु
	.type		= BT_PICASSO4,
	.regoffset	= 0x00600000,
	.ramsize	= 4 * MB_,
	.ramoffset	= 0x01000000,	/* 0x02000000 क्रम 64 MiB boards */
पूर्ण;

अटल स्थिर काष्ठा zorrocl zcl_picasso4_z2 = अणु
	.type		= BT_PICASSO4,
	.regoffset	= 0x10000,
	.ramid		= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_IV_Z2_RAM1,
	.ramid2		= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_IV_Z2_RAM2,
पूर्ण;


अटल स्थिर काष्ठा zorro_device_id cirrusfb_zorro_table[] = अणु
	अणु
		.id		= ZORRO_PROD_HELFRICH_SD64_REG,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_sd64,
	पूर्ण, अणु
		.id		= ZORRO_PROD_HELFRICH_PICCOLO_REG,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_piccolo,
	पूर्ण, अणु
		.id	= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_II_II_PLUS_REG,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_picasso,
	पूर्ण, अणु
		.id		= ZORRO_PROD_GVP_EGS_28_24_SPECTRUM_REG,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_spectrum,
	पूर्ण, अणु
		.id		= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_IV_Z3,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_picasso4_z3,
	पूर्ण, अणु
		.id		= ZORRO_PROD_VILLAGE_TRONIC_PICASSO_IV_Z2_REG,
		.driver_data	= (अचिन्हित दीर्घ)&zcl_picasso4_z2,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, cirrusfb_zorro_table);
#पूर्ण_अगर /* CONFIG_ZORRO */

#अगर_घोषित CIRRUSFB_DEBUG
क्रमागत cirrusfb_dbg_reg_class अणु
	CRT,
	SEQ
पूर्ण;
#पूर्ण_अगर		/* CIRRUSFB_DEBUG */

/* info about board */
काष्ठा cirrusfb_info अणु
	u8 __iomem *regbase;
	u8 __iomem *laguna_mmio;
	क्रमागत cirrus_board btype;
	अचिन्हित अक्षर SFR;	/* Shaकरोw of special function रेजिस्टर */

	पूर्णांक multiplexing;
	पूर्णांक द्विगुनVCLK;
	पूर्णांक blank_mode;
	u32 pseuकरो_palette[16];

	व्योम (*unmap)(काष्ठा fb_info *info);
पूर्ण;

अटल bool noaccel;
अटल अक्षर *mode_option = "640x480@60";

/****************************************************************************/
/**** BEGIN PROTOTYPES ******************************************************/

/*--- Interface used by the world ------------------------------------------*/
अटल पूर्णांक cirrusfb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info);

/*--- Internal routines ----------------------------------------------------*/
अटल व्योम init_vgachip(काष्ठा fb_info *info);
अटल व्योम चयन_monitor(काष्ठा cirrusfb_info *cinfo, पूर्णांक on);
अटल व्योम WGen(स्थिर काष्ठा cirrusfb_info *cinfo,
		 पूर्णांक regnum, अचिन्हित अक्षर val);
अटल अचिन्हित अक्षर RGen(स्थिर काष्ठा cirrusfb_info *cinfo, पूर्णांक regnum);
अटल व्योम AttrOn(स्थिर काष्ठा cirrusfb_info *cinfo);
अटल व्योम WHDR(स्थिर काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val);
अटल व्योम WSFR(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val);
अटल व्योम WSFR2(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val);
अटल व्योम WClut(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर regnum,
		  अचिन्हित अक्षर red, अचिन्हित अक्षर green, अचिन्हित अक्षर blue);
#अगर 0
अटल व्योम RClut(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर regnum,
		  अचिन्हित अक्षर *red, अचिन्हित अक्षर *green,
		  अचिन्हित अक्षर *blue);
#पूर्ण_अगर
अटल व्योम cirrusfb_WaitBLT(u8 __iomem *regbase);
अटल व्योम cirrusfb_BitBLT(u8 __iomem *regbase, पूर्णांक bits_per_pixel,
			    u_लघु curx, u_लघु cury,
			    u_लघु destx, u_लघु desty,
			    u_लघु width, u_लघु height,
			    u_लघु line_length);
अटल व्योम cirrusfb_RectFill(u8 __iomem *regbase, पूर्णांक bits_per_pixel,
			      u_लघु x, u_लघु y,
			      u_लघु width, u_लघु height,
			      u32 fg_color, u32 bg_color,
			      u_लघु line_length, u_अक्षर bliपंचांगode);

अटल व्योम bestघड़ी(दीर्घ freq, पूर्णांक *nom, पूर्णांक *den, पूर्णांक *भाग);

#अगर_घोषित CIRRUSFB_DEBUG
अटल व्योम cirrusfb_dbg_reg_dump(काष्ठा fb_info *info, caddr_t regbase);
अटल व्योम cirrusfb_dbg_prपूर्णांक_regs(काष्ठा fb_info *info,
				    caddr_t regbase,
				    क्रमागत cirrusfb_dbg_reg_class reg_class, ...);
#पूर्ण_अगर /* CIRRUSFB_DEBUG */

/*** END   PROTOTYPES ********************************************************/
/*****************************************************************************/
/*** BEGIN Interface Used by the World ***************************************/

अटल अंतरभूत पूर्णांक is_laguna(स्थिर काष्ठा cirrusfb_info *cinfo)
अणु
	वापस cinfo->btype == BT_LAGUNA || cinfo->btype == BT_LAGUNAB;
पूर्ण

अटल पूर्णांक खोलोcount;

/*--- Open /dev/fbx ---------------------------------------------------------*/
अटल पूर्णांक cirrusfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	अगर (खोलोcount++ == 0)
		चयन_monitor(info->par, 1);
	वापस 0;
पूर्ण

/*--- Close /dev/fbx --------------------------------------------------------*/
अटल पूर्णांक cirrusfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	अगर (--खोलोcount == 0)
		चयन_monitor(info->par, 0);
	वापस 0;
पूर्ण

/**** END   Interface used by the World *************************************/
/****************************************************************************/
/**** BEGIN Hardware specअगरic Routines **************************************/

/* Check अगर the MCLK is not a better घड़ी source */
अटल पूर्णांक cirrusfb_check_mclk(काष्ठा fb_info *info, दीर्घ freq)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	दीर्घ mclk = vga_rseq(cinfo->regbase, CL_SEQR1F) & 0x3f;

	/* Read MCLK value */
	mclk = (14318 * mclk) >> 3;
	dev_dbg(info->device, "Read MCLK of %ld kHz\n", mclk);

	/* Determine अगर we should use MCLK instead of VCLK, and अगर so, what we
	 * should भागide it by to get VCLK
	 */

	अगर (असल(freq - mclk) < 250) अणु
		dev_dbg(info->device, "Using VCLK = MCLK\n");
		वापस 1;
	पूर्ण अन्यथा अगर (असल(freq - (mclk / 2)) < 250) अणु
		dev_dbg(info->device, "Using VCLK = MCLK/2\n");
		वापस 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cirrusfb_check_pixघड़ी(स्थिर काष्ठा fb_var_screeninfo *var,
				   काष्ठा fb_info *info)
अणु
	दीर्घ freq;
	दीर्घ maxघड़ी;
	काष्ठा cirrusfb_info *cinfo = info->par;
	अचिन्हित maxघड़ीidx = var->bits_per_pixel >> 3;

	/* convert from ps to kHz */
	freq = PICOS2KHZ(var->pixघड़ी);

	dev_dbg(info->device, "desired pixclock: %ld kHz\n", freq);

	maxघड़ी = cirrusfb_board_info[cinfo->btype].maxघड़ी[maxघड़ीidx];
	cinfo->multiplexing = 0;

	/* If the frequency is greater than we can support, we might be able
	 * to use multiplexing क्रम the video mode */
	अगर (freq > maxघड़ी) अणु
		dev_err(info->device,
			"Frequency greater than maxclock (%ld kHz)\n",
			maxघड़ी);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Additional स्थिरraपूर्णांक: 8bpp uses DAC घड़ी करोubling to allow maximum
	 * pixel घड़ी
	 */
	अगर (var->bits_per_pixel == 8) अणु
		चयन (cinfo->btype) अणु
		हाल BT_ALPINE:
		हाल BT_SD64:
		हाल BT_PICASSO4:
			अगर (freq > 85500)
				cinfo->multiplexing = 1;
			अवरोध;
		हाल BT_GD5480:
			अगर (freq > 135100)
				cinfo->multiplexing = 1;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we have a 1MB 5434, we need to put ourselves in a mode where
	 * the VCLK is द्विगुन the pixel घड़ी. */
	cinfo->द्विगुनVCLK = 0;
	अगर (cinfo->btype == BT_SD64 && info->fix.smem_len <= MB_ &&
	    var->bits_per_pixel == 16) अणु
		cinfo->द्विगुनVCLK = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cirrusfb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	पूर्णांक yres;
	/* memory size in pixels */
	अचिन्हित पूर्णांक pixels;
	काष्ठा cirrusfb_info *cinfo = info->par;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		var->red.offset = 0;
		var->red.length = 1;
		var->green = var->red;
		var->blue = var->red;
		अवरोध;

	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green = var->red;
		var->blue = var->red;
		अवरोध;

	हाल 16:
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;

	हाल 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;

	शेष:
		dev_dbg(info->device,
			"Unsupported bpp size: %d\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	pixels = info->screen_size * 8 / var->bits_per_pixel;
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	/* use highest possible भव resolution */
	अगर (var->yres_भव == -1) अणु
		var->yres_भव = pixels / var->xres_भव;

		dev_info(info->device,
			 "virtual resolution set to maximum of %dx%d\n",
			 var->xres_भव, var->yres_भव);
	पूर्ण
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर (var->xres_भव * var->yres_भव > pixels) अणु
		dev_err(info->device, "mode %dx%dx%d rejected... "
		      "virtual resolution too high to fit into video memory!\n",
			var->xres_भव, var->yres_भव,
			var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	/* truncate xoffset and yoffset to maximum अगर too high */
	अगर (var->xoffset > var->xres_भव - var->xres)
		var->xoffset = var->xres_भव - var->xres - 1;
	अगर (var->yoffset > var->yres_भव - var->yres)
		var->yoffset = var->yres_भव - var->yres - 1;

	var->red.msb_right =
	    var->green.msb_right =
	    var->blue.msb_right =
	    var->transp.offset =
	    var->transp.length =
	    var->transp.msb_right = 0;

	yres = var->yres;
	अगर (var->vmode & FB_VMODE_DOUBLE)
		yres *= 2;
	अन्यथा अगर (var->vmode & FB_VMODE_INTERLACED)
		yres = (yres + 1) / 2;

	अगर (yres >= 1280) अणु
		dev_err(info->device, "ERROR: VerticalTotal >= 1280; "
			"special treatment required! (TODO)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cirrusfb_check_pixघड़ी(var, info))
		वापस -EINVAL;

	अगर (!is_laguna(cinfo))
		var->accel_flags = FB_ACCELF_TEXT;

	वापस 0;
पूर्ण

अटल व्योम cirrusfb_set_mclk_as_source(स्थिर काष्ठा fb_info *info, पूर्णांक भाग)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	अचिन्हित अक्षर old1f, old1e;

	निश्चित(cinfo != शून्य);
	old1f = vga_rseq(cinfo->regbase, CL_SEQR1F) & ~0x40;

	अगर (भाग) अणु
		dev_dbg(info->device, "Set %s as pixclock source.\n",
			(भाग == 2) ? "MCLK/2" : "MCLK");
		old1f |= 0x40;
		old1e = vga_rseq(cinfo->regbase, CL_SEQR1E) & ~0x1;
		अगर (भाग == 2)
			old1e |= 1;

		vga_wseq(cinfo->regbase, CL_SEQR1E, old1e);
	पूर्ण
	vga_wseq(cinfo->regbase, CL_SEQR1F, old1f);
पूर्ण

/*************************************************************************
	cirrusfb_set_par_foo()

	actually ग_लिखोs the values क्रम a new video mode पूर्णांकo the hardware,
**************************************************************************/
अटल पूर्णांक cirrusfb_set_par_foo(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	u8 __iomem *regbase = cinfo->regbase;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक pitch;
	स्थिर काष्ठा cirrusfb_board_info_rec *bi;
	पूर्णांक hdispend, hsyncstart, hsyncend, htotal;
	पूर्णांक yres, vdispend, vsyncstart, vsyncend, vtotal;
	दीर्घ freq;
	पूर्णांक nom, den, भाग;
	अचिन्हित पूर्णांक control = 0, क्रमmat = 0, threshold = 0;

	dev_dbg(info->device, "Requested mode: %dx%dx%d\n",
	       var->xres, var->yres, var->bits_per_pixel);

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		info->fix.line_length = var->xres_भव / 8;
		info->fix.visual = FB_VISUAL_MONO10;
		अवरोध;

	हाल 8:
		info->fix.line_length = var->xres_भव;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;

	हाल 16:
	हाल 24:
		info->fix.line_length = var->xres_भव *
					var->bits_per_pixel >> 3;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	पूर्ण
	info->fix.type = FB_TYPE_PACKED_PIXELS;

	init_vgachip(info);

	bi = &cirrusfb_board_info[cinfo->btype];

	hsyncstart = var->xres + var->right_margin;
	hsyncend = hsyncstart + var->hsync_len;
	htotal = (hsyncend + var->left_margin) / 8;
	hdispend = var->xres / 8;
	hsyncstart = hsyncstart / 8;
	hsyncend = hsyncend / 8;

	vdispend = var->yres;
	vsyncstart = vdispend + var->lower_margin;
	vsyncend = vsyncstart + var->vsync_len;
	vtotal = vsyncend + var->upper_margin;

	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		vdispend *= 2;
		vsyncstart *= 2;
		vsyncend *= 2;
		vtotal *= 2;
	पूर्ण अन्यथा अगर (var->vmode & FB_VMODE_INTERLACED) अणु
		vdispend = (vdispend + 1) / 2;
		vsyncstart = (vsyncstart + 1) / 2;
		vsyncend = (vsyncend + 1) / 2;
		vtotal = (vtotal + 1) / 2;
	पूर्ण
	yres = vdispend;
	अगर (yres >= 1024) अणु
		vtotal /= 2;
		vsyncstart /= 2;
		vsyncend /= 2;
		vdispend /= 2;
	पूर्ण

	vdispend -= 1;
	vsyncstart -= 1;
	vsyncend -= 1;
	vtotal -= 2;

	अगर (cinfo->multiplexing) अणु
		htotal /= 2;
		hsyncstart /= 2;
		hsyncend /= 2;
		hdispend /= 2;
	पूर्ण

	htotal -= 5;
	hdispend -= 1;
	hsyncstart += 1;
	hsyncend += 1;

	/* unlock रेजिस्टर VGA_CRTC_H_TOTAL..CRT7 */
	vga_wcrt(regbase, VGA_CRTC_V_SYNC_END, 0x20);	/* previously: 0x00) */

	/* अगर debugging is enabled, all parameters get output beक्रमe writing */
	dev_dbg(info->device, "CRT0: %d\n", htotal);
	vga_wcrt(regbase, VGA_CRTC_H_TOTAL, htotal);

	dev_dbg(info->device, "CRT1: %d\n", hdispend);
	vga_wcrt(regbase, VGA_CRTC_H_DISP, hdispend);

	dev_dbg(info->device, "CRT2: %d\n", var->xres / 8);
	vga_wcrt(regbase, VGA_CRTC_H_BLANK_START, var->xres / 8);

	/*  + 128: Compatible पढ़ो */
	dev_dbg(info->device, "CRT3: 128+%d\n", (htotal + 5) % 32);
	vga_wcrt(regbase, VGA_CRTC_H_BLANK_END,
		 128 + ((htotal + 5) % 32));

	dev_dbg(info->device, "CRT4: %d\n", hsyncstart);
	vga_wcrt(regbase, VGA_CRTC_H_SYNC_START, hsyncstart);

	पंचांगp = hsyncend % 32;
	अगर ((htotal + 5) & 32)
		पंचांगp += 128;
	dev_dbg(info->device, "CRT5: %d\n", पंचांगp);
	vga_wcrt(regbase, VGA_CRTC_H_SYNC_END, पंचांगp);

	dev_dbg(info->device, "CRT6: %d\n", vtotal & 0xff);
	vga_wcrt(regbase, VGA_CRTC_V_TOTAL, vtotal & 0xff);

	पंचांगp = 16;		/* LineCompare bit #9 */
	अगर (vtotal & 256)
		पंचांगp |= 1;
	अगर (vdispend & 256)
		पंचांगp |= 2;
	अगर (vsyncstart & 256)
		पंचांगp |= 4;
	अगर ((vdispend + 1) & 256)
		पंचांगp |= 8;
	अगर (vtotal & 512)
		पंचांगp |= 32;
	अगर (vdispend & 512)
		पंचांगp |= 64;
	अगर (vsyncstart & 512)
		पंचांगp |= 128;
	dev_dbg(info->device, "CRT7: %d\n", पंचांगp);
	vga_wcrt(regbase, VGA_CRTC_OVERFLOW, पंचांगp);

	पंचांगp = 0x40;		/* LineCompare bit #8 */
	अगर ((vdispend + 1) & 512)
		पंचांगp |= 0x20;
	अगर (var->vmode & FB_VMODE_DOUBLE)
		पंचांगp |= 0x80;
	dev_dbg(info->device, "CRT9: %d\n", पंचांगp);
	vga_wcrt(regbase, VGA_CRTC_MAX_SCAN, पंचांगp);

	dev_dbg(info->device, "CRT10: %d\n", vsyncstart & 0xff);
	vga_wcrt(regbase, VGA_CRTC_V_SYNC_START, vsyncstart & 0xff);

	dev_dbg(info->device, "CRT11: 64+32+%d\n", vsyncend % 16);
	vga_wcrt(regbase, VGA_CRTC_V_SYNC_END, vsyncend % 16 + 64 + 32);

	dev_dbg(info->device, "CRT12: %d\n", vdispend & 0xff);
	vga_wcrt(regbase, VGA_CRTC_V_DISP_END, vdispend & 0xff);

	dev_dbg(info->device, "CRT15: %d\n", (vdispend + 1) & 0xff);
	vga_wcrt(regbase, VGA_CRTC_V_BLANK_START, (vdispend + 1) & 0xff);

	dev_dbg(info->device, "CRT16: %d\n", vtotal & 0xff);
	vga_wcrt(regbase, VGA_CRTC_V_BLANK_END, vtotal & 0xff);

	dev_dbg(info->device, "CRT18: 0xff\n");
	vga_wcrt(regbase, VGA_CRTC_LINE_COMPARE, 0xff);

	पंचांगp = 0;
	अगर (var->vmode & FB_VMODE_INTERLACED)
		पंचांगp |= 1;
	अगर ((htotal + 5) & 64)
		पंचांगp |= 16;
	अगर ((htotal + 5) & 128)
		पंचांगp |= 32;
	अगर (vtotal & 256)
		पंचांगp |= 64;
	अगर (vtotal & 512)
		पंचांगp |= 128;

	dev_dbg(info->device, "CRT1a: %d\n", पंचांगp);
	vga_wcrt(regbase, CL_CRT1A, पंचांगp);

	freq = PICOS2KHZ(var->pixघड़ी);
	अगर (var->bits_per_pixel == 24)
		अगर (cinfo->btype == BT_ALPINE || cinfo->btype == BT_SD64)
			freq *= 3;
	अगर (cinfo->multiplexing)
		freq /= 2;
	अगर (cinfo->द्विगुनVCLK)
		freq *= 2;

	bestघड़ी(freq, &nom, &den, &भाग);

	dev_dbg(info->device, "VCLK freq: %ld kHz  nom: %d  den: %d  div: %d\n",
		freq, nom, den, भाग);

	/* set VCLK0 */
	/* hardware RefClock: 14.31818 MHz */
	/* क्रमmula: VClk = (OSC * N) / (D * (1+P)) */
	/* Example: VClk = (14.31818 * 91) / (23 * (1+1)) = 28.325 MHz */

	अगर (cinfo->btype == BT_ALPINE || cinfo->btype == BT_PICASSO4 ||
	    cinfo->btype == BT_SD64) अणु
		/* अगर freq is बंद to mclk or mclk/2 select mclk
		 * as घड़ी source
		 */
		पूर्णांक भागMCLK = cirrusfb_check_mclk(info, freq);
		अगर (भागMCLK)
			nom = 0;
		cirrusfb_set_mclk_as_source(info, भागMCLK);
	पूर्ण
	अगर (is_laguna(cinfo)) अणु
		दीर्घ pcअगरc = fb_पढ़ोl(cinfo->laguna_mmio + 0x3fc);
		अचिन्हित अक्षर tile = fb_पढ़ोb(cinfo->laguna_mmio + 0x407);
		अचिन्हित लघु tile_control;

		अगर (cinfo->btype == BT_LAGUNAB) अणु
			tile_control = fb_पढ़ोw(cinfo->laguna_mmio + 0x2c4);
			tile_control &= ~0x80;
			fb_ग_लिखोw(tile_control, cinfo->laguna_mmio + 0x2c4);
		पूर्ण

		fb_ग_लिखोl(pcअगरc | 0x10000000l, cinfo->laguna_mmio + 0x3fc);
		fb_ग_लिखोb(tile & 0x3f, cinfo->laguna_mmio + 0x407);
		control = fb_पढ़ोw(cinfo->laguna_mmio + 0x402);
		threshold = fb_पढ़ोw(cinfo->laguna_mmio + 0xea);
		control &= ~0x6800;
		क्रमmat = 0;
		threshold &= 0xffc0 & 0x3fbf;
	पूर्ण
	अगर (nom) अणु
		पंचांगp = den << 1;
		अगर (भाग != 0)
			पंचांगp |= 1;
		/* 6 bit denom; ONLY 5434!!! (bugged me 10 days) */
		अगर ((cinfo->btype == BT_SD64) ||
		    (cinfo->btype == BT_ALPINE) ||
		    (cinfo->btype == BT_GD5480))
			पंचांगp |= 0x80;

		/* Laguna chipset has reversed घड़ी रेजिस्टरs */
		अगर (is_laguna(cinfo)) अणु
			vga_wseq(regbase, CL_SEQRE, पंचांगp);
			vga_wseq(regbase, CL_SEQR1E, nom);
		पूर्ण अन्यथा अणु
			vga_wseq(regbase, CL_SEQRE, nom);
			vga_wseq(regbase, CL_SEQR1E, पंचांगp);
		पूर्ण
	पूर्ण

	अगर (yres >= 1024)
		/* 1280x1024 */
		vga_wcrt(regbase, VGA_CRTC_MODE, 0xc7);
	अन्यथा
		/* mode control: VGA_CRTC_START_HI enable, ROTATE(?), 16bit
		 * address wrap, no compat. */
		vga_wcrt(regbase, VGA_CRTC_MODE, 0xc3);

	/* करोn't know अगर it would hurt to also program this अगर no पूर्णांकerlaced */
	/* mode is used, but I feel better this way.. :-) */
	अगर (var->vmode & FB_VMODE_INTERLACED)
		vga_wcrt(regbase, VGA_CRTC_REGS, htotal / 2);
	अन्यथा
		vga_wcrt(regbase, VGA_CRTC_REGS, 0x00);	/* पूर्णांकerlace control */

	/* adjust horizontal/vertical sync type (low/high), use VCLK3 */
	/* enable display memory & CRTC I/O address क्रम color mode */
	पंचांगp = 0x03 | 0xc;
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		पंचांगp |= 0x40;
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		पंचांगp |= 0x80;
	WGen(cinfo, VGA_MIS_W, पंचांगp);

	/* text cursor on and start line */
	vga_wcrt(regbase, VGA_CRTC_CURSOR_START, 0);
	/* text cursor end line */
	vga_wcrt(regbase, VGA_CRTC_CURSOR_END, 31);

	/******************************************************
	 *
	 * 1 bpp
	 *
	 */

	/* programming क्रम dअगरferent color depths */
	अगर (var->bits_per_pixel == 1) अणु
		dev_dbg(info->device, "preparing for 1 bit deep display\n");
		vga_wgfx(regbase, VGA_GFX_MODE, 0);	/* mode रेजिस्टर */

		/* SR07 */
		चयन (cinfo->btype) अणु
		हाल BT_SD64:
		हाल BT_PICCOLO:
		हाल BT_PICASSO:
		हाल BT_SPECTRUM:
		हाल BT_PICASSO4:
		हाल BT_ALPINE:
		हाल BT_GD5480:
			vga_wseq(regbase, CL_SEQR7,
				 cinfo->multiplexing ?
					bi->sr07_1bpp_mux : bi->sr07_1bpp);
			अवरोध;

		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			vga_wseq(regbase, CL_SEQR7,
				vga_rseq(regbase, CL_SEQR7) & ~0x01);
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown Board\n");
			अवरोध;
		पूर्ण

		/* Extended Sequencer Mode */
		चयन (cinfo->btype) अणु

		हाल BT_PICCOLO:
		हाल BT_SPECTRUM:
			/* evtl d0 bei 1 bit? aव्योम FIFO underruns..? */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_PICASSO:
			/* ## vorher d0 aव्योम FIFO underruns..? */
			vga_wseq(regbase, CL_SEQRF, 0xd0);
			अवरोध;

		हाल BT_SD64:
		हाल BT_PICASSO4:
		हाल BT_ALPINE:
		हाल BT_GD5480:
		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			/* करो nothing */
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown Board\n");
			अवरोध;
		पूर्ण

		/* pixel mask: pass-through क्रम first plane */
		WGen(cinfo, VGA_PEL_MSK, 0x01);
		अगर (cinfo->multiplexing)
			/* hidden dac reg: 1280x1024 */
			WHDR(cinfo, 0x4a);
		अन्यथा
			/* hidden dac: nothing */
			WHDR(cinfo, 0);
		/* memory mode: odd/even, ext. memory */
		vga_wseq(regbase, VGA_SEQ_MEMORY_MODE, 0x06);
		/* plane mask: only ग_लिखो to first plane */
		vga_wseq(regbase, VGA_SEQ_PLANE_WRITE, 0x01);
	पूर्ण

	/******************************************************
	 *
	 * 8 bpp
	 *
	 */

	अन्यथा अगर (var->bits_per_pixel == 8) अणु
		dev_dbg(info->device, "preparing for 8 bit deep display\n");
		चयन (cinfo->btype) अणु
		हाल BT_SD64:
		हाल BT_PICCOLO:
		हाल BT_PICASSO:
		हाल BT_SPECTRUM:
		हाल BT_PICASSO4:
		हाल BT_ALPINE:
		हाल BT_GD5480:
			vga_wseq(regbase, CL_SEQR7,
				  cinfo->multiplexing ?
					bi->sr07_8bpp_mux : bi->sr07_8bpp);
			अवरोध;

		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			vga_wseq(regbase, CL_SEQR7,
				vga_rseq(regbase, CL_SEQR7) | 0x01);
			threshold |= 0x10;
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown Board\n");
			अवरोध;
		पूर्ण

		चयन (cinfo->btype) अणु
		हाल BT_PICCOLO:
		हाल BT_PICASSO:
		हाल BT_SPECTRUM:
			/* Fast Page-Mode ग_लिखोs */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_PICASSO4:
#अगर_घोषित CONFIG_ZORRO
			/* ### INCOMPLETE!! */
			vga_wseq(regbase, CL_SEQRF, 0xb8);
#पूर्ण_अगर
		हाल BT_ALPINE:
		हाल BT_SD64:
		हाल BT_GD5480:
		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			/* करो nothing */
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown board\n");
			अवरोध;
		पूर्ण

		/* mode रेजिस्टर: 256 color mode */
		vga_wgfx(regbase, VGA_GFX_MODE, 64);
		अगर (cinfo->multiplexing)
			/* hidden dac reg: 1280x1024 */
			WHDR(cinfo, 0x4a);
		अन्यथा
			/* hidden dac: nothing */
			WHDR(cinfo, 0);
	पूर्ण

	/******************************************************
	 *
	 * 16 bpp
	 *
	 */

	अन्यथा अगर (var->bits_per_pixel == 16) अणु
		dev_dbg(info->device, "preparing for 16 bit deep display\n");
		चयन (cinfo->btype) अणु
		हाल BT_PICCOLO:
		हाल BT_SPECTRUM:
			vga_wseq(regbase, CL_SEQR7, 0x87);
			/* Fast Page-Mode ग_लिखोs */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_PICASSO:
			vga_wseq(regbase, CL_SEQR7, 0x27);
			/* Fast Page-Mode ग_लिखोs */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_SD64:
		हाल BT_PICASSO4:
		हाल BT_ALPINE:
			/* Extended Sequencer Mode: 256c col. mode */
			vga_wseq(regbase, CL_SEQR7,
					cinfo->द्विगुनVCLK ? 0xa3 : 0xa7);
			अवरोध;

		हाल BT_GD5480:
			vga_wseq(regbase, CL_SEQR7, 0x17);
			/* We alपढ़ोy set SRF and SR1F */
			अवरोध;

		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			vga_wseq(regbase, CL_SEQR7,
				vga_rseq(regbase, CL_SEQR7) & ~0x01);
			control |= 0x2000;
			क्रमmat |= 0x1400;
			threshold |= 0x10;
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown Board\n");
			अवरोध;
		पूर्ण

		/* mode रेजिस्टर: 256 color mode */
		vga_wgfx(regbase, VGA_GFX_MODE, 64);
#अगर_घोषित CONFIG_PCI
		WHDR(cinfo, cinfo->द्विगुनVCLK ? 0xe1 : 0xc1);
#या_अगर defined(CONFIG_ZORRO)
		/* FIXME: CONFIG_PCI and CONFIG_ZORRO may be defined both */
		WHDR(cinfo, 0xa0);	/* hidden dac reg: nothing special */
#पूर्ण_अगर
	पूर्ण

	/******************************************************
	 *
	 * 24 bpp
	 *
	 */

	अन्यथा अगर (var->bits_per_pixel == 24) अणु
		dev_dbg(info->device, "preparing for 24 bit deep display\n");
		चयन (cinfo->btype) अणु
		हाल BT_PICCOLO:
		हाल BT_SPECTRUM:
			vga_wseq(regbase, CL_SEQR7, 0x85);
			/* Fast Page-Mode ग_लिखोs */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_PICASSO:
			vga_wseq(regbase, CL_SEQR7, 0x25);
			/* Fast Page-Mode ग_लिखोs */
			vga_wseq(regbase, CL_SEQRF, 0xb0);
			अवरोध;

		हाल BT_SD64:
		हाल BT_PICASSO4:
		हाल BT_ALPINE:
			/* Extended Sequencer Mode: 256c col. mode */
			vga_wseq(regbase, CL_SEQR7, 0xa5);
			अवरोध;

		हाल BT_GD5480:
			vga_wseq(regbase, CL_SEQR7, 0x15);
			/* We alपढ़ोy set SRF and SR1F */
			अवरोध;

		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			vga_wseq(regbase, CL_SEQR7,
				vga_rseq(regbase, CL_SEQR7) & ~0x01);
			control |= 0x4000;
			क्रमmat |= 0x2400;
			threshold |= 0x20;
			अवरोध;

		शेष:
			dev_warn(info->device, "unknown Board\n");
			अवरोध;
		पूर्ण

		/* mode रेजिस्टर: 256 color mode */
		vga_wgfx(regbase, VGA_GFX_MODE, 64);
		/* hidden dac reg: 8-8-8 mode (24 or 32) */
		WHDR(cinfo, 0xc5);
	पूर्ण

	/******************************************************
	 *
	 * unknown/unsupported bpp
	 *
	 */

	अन्यथा
		dev_err(info->device,
			"What's this? requested color depth == %d.\n",
			var->bits_per_pixel);

	pitch = info->fix.line_length >> 3;
	vga_wcrt(regbase, VGA_CRTC_OFFSET, pitch & 0xff);
	पंचांगp = 0x22;
	अगर (pitch & 0x100)
		पंचांगp |= 0x10;	/* offset overflow bit */

	/* screen start addr #16-18, fastpagemode cycles */
	vga_wcrt(regbase, CL_CRT1B, पंचांगp);

	/* screen start address bit 19 */
	अगर (cirrusfb_board_info[cinfo->btype].scrn_start_bit19)
		vga_wcrt(regbase, CL_CRT1D, (pitch >> 9) & 1);

	अगर (is_laguna(cinfo)) अणु
		पंचांगp = 0;
		अगर ((htotal + 5) & 256)
			पंचांगp |= 128;
		अगर (hdispend & 256)
			पंचांगp |= 64;
		अगर (hsyncstart & 256)
			पंचांगp |= 48;
		अगर (vtotal & 1024)
			पंचांगp |= 8;
		अगर (vdispend & 1024)
			पंचांगp |= 4;
		अगर (vsyncstart & 1024)
			पंचांगp |= 3;

		vga_wcrt(regbase, CL_CRT1E, पंचांगp);
		dev_dbg(info->device, "CRT1e: %d\n", पंचांगp);
	पूर्ण

	/* pixel panning */
	vga_wattr(regbase, CL_AR33, 0);

	/* [ EGS: SetOffset(); ] */
	/* From SetOffset(): Turn on VideoEnable bit in Attribute controller */
	AttrOn(cinfo);

	अगर (is_laguna(cinfo)) अणु
		/* no tiles */
		fb_ग_लिखोw(control | 0x1000, cinfo->laguna_mmio + 0x402);
		fb_ग_लिखोw(क्रमmat, cinfo->laguna_mmio + 0xc0);
		fb_ग_लिखोw(threshold, cinfo->laguna_mmio + 0xea);
	पूर्ण
	/* finally, turn on everything - turn off "FullBandwidth" bit */
	/* also, set "DotClock%2" bit where requested */
	पंचांगp = 0x01;

/*** FB_VMODE_CLOCK_HALVE in linux/fb.h not defined anymore ?
    अगर (var->vmode & FB_VMODE_CLOCK_HALVE)
	पंचांगp |= 0x08;
*/

	vga_wseq(regbase, VGA_SEQ_CLOCK_MODE, पंचांगp);
	dev_dbg(info->device, "CL_SEQR1: %d\n", पंचांगp);

#अगर_घोषित CIRRUSFB_DEBUG
	cirrusfb_dbg_reg_dump(info, शून्य);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* क्रम some reason incomprehensible to me, cirrusfb requires that you ग_लिखो
 * the रेजिस्टरs twice क्रम the settings to take..grr. -dte */
अटल पूर्णांक cirrusfb_set_par(काष्ठा fb_info *info)
अणु
	cirrusfb_set_par_foo(info);
	वापस cirrusfb_set_par_foo(info);
पूर्ण

अटल पूर्णांक cirrusfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			      अचिन्हित blue, अचिन्हित transp,
			      काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;

	अगर (regno > 255)
		वापस -EINVAL;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 v;
		red >>= (16 - info->var.red.length);
		green >>= (16 - info->var.green.length);
		blue >>= (16 - info->var.blue.length);

		अगर (regno >= 16)
			वापस 1;
		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset);

		cinfo->pseuकरो_palette[regno] = v;
		वापस 0;
	पूर्ण

	अगर (info->var.bits_per_pixel == 8)
		WClut(cinfo, regno, red >> 10, green >> 10, blue >> 10);

	वापस 0;

पूर्ण

/*************************************************************************
	cirrusfb_pan_display()

	perक्रमms display panning - provided hardware permits this
**************************************************************************/
अटल पूर्णांक cirrusfb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	पूर्णांक xoffset;
	अचिन्हित दीर्घ base;
	अचिन्हित अक्षर पंचांगp, xpix;
	काष्ठा cirrusfb_info *cinfo = info->par;

	/* no range checks क्रम xoffset and yoffset,   */
	/* as fb_pan_display has alपढ़ोy करोne this */
	अगर (var->vmode & FB_VMODE_YWRAP)
		वापस -EINVAL;

	xoffset = var->xoffset * info->var.bits_per_pixel / 8;

	base = var->yoffset * info->fix.line_length + xoffset;

	अगर (info->var.bits_per_pixel == 1) अणु
		/* base is alपढ़ोy correct */
		xpix = (अचिन्हित अक्षर) (var->xoffset % 8);
	पूर्ण अन्यथा अणु
		base /= 4;
		xpix = (अचिन्हित अक्षर) ((xoffset % 4) * 2);
	पूर्ण

	अगर (!is_laguna(cinfo))
		cirrusfb_WaitBLT(cinfo->regbase);

	/* lower 8 + 8 bits of screen start address */
	vga_wcrt(cinfo->regbase, VGA_CRTC_START_LO, base & 0xff);
	vga_wcrt(cinfo->regbase, VGA_CRTC_START_HI, (base >> 8) & 0xff);

	/* 0xf2 is %11110010, exclude पंचांगp bits */
	पंचांगp = vga_rcrt(cinfo->regbase, CL_CRT1B) & 0xf2;
	/* स्थिरruct bits 16, 17 and 18 of screen start address */
	अगर (base & 0x10000)
		पंचांगp |= 0x01;
	अगर (base & 0x20000)
		पंचांगp |= 0x04;
	अगर (base & 0x40000)
		पंचांगp |= 0x08;

	vga_wcrt(cinfo->regbase, CL_CRT1B, पंचांगp);

	/* स्थिरruct bit 19 of screen start address */
	अगर (cirrusfb_board_info[cinfo->btype].scrn_start_bit19) अणु
		पंचांगp = vga_rcrt(cinfo->regbase, CL_CRT1D);
		अगर (is_laguna(cinfo))
			पंचांगp = (पंचांगp & ~0x18) | ((base >> 16) & 0x18);
		अन्यथा
			पंचांगp = (पंचांगp & ~0x80) | ((base >> 12) & 0x80);
		vga_wcrt(cinfo->regbase, CL_CRT1D, पंचांगp);
	पूर्ण

	/* ग_लिखो pixel panning value to AR33; this करोes not quite work in 8bpp
	 *
	 * ### Piccolo..? Will this work?
	 */
	अगर (info->var.bits_per_pixel == 1)
		vga_wattr(cinfo->regbase, CL_AR33, xpix);

	वापस 0;
पूर्ण

अटल पूर्णांक cirrusfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	/*
	 * Blank the screen अगर blank_mode != 0, अन्यथा unblank. If blank == शून्य
	 * then the caller blanks by setting the CLUT (Color Look Up Table)
	 * to all black. Return 0 अगर blanking succeeded, != 0 अगर un-/blanking
	 * failed due to e.g. a video mode which करोesn't support it.
	 * Implements VESA suspend and घातerकरोwn modes on hardware that
	 * supports disabling hsync/vsync:
	 *   blank_mode == 2: suspend vsync
	 *   blank_mode == 3: suspend hsync
	 *   blank_mode == 4: घातerकरोwn
	 */
	अचिन्हित अक्षर val;
	काष्ठा cirrusfb_info *cinfo = info->par;
	पूर्णांक current_mode = cinfo->blank_mode;

	dev_dbg(info->device, "ENTER, blank mode = %d\n", blank_mode);

	अगर (info->state != FBINFO_STATE_RUNNING ||
	    current_mode == blank_mode) अणु
		dev_dbg(info->device, "EXIT, returning 0\n");
		वापस 0;
	पूर्ण

	/* Unकरो current */
	अगर (current_mode == FB_BLANK_NORMAL ||
	    current_mode == FB_BLANK_UNBLANK)
		/* clear "FullBandwidth" bit */
		val = 0;
	अन्यथा
		/* set "FullBandwidth" bit */
		val = 0x20;

	val |= vga_rseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE) & 0xdf;
	vga_wseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE, val);

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		val = 0x00;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		val = 0x04;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		val = 0x02;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		val = 0x06;
		अवरोध;
	शेष:
		dev_dbg(info->device, "EXIT, returning 1\n");
		वापस 1;
	पूर्ण

	vga_wgfx(cinfo->regbase, CL_GRE, val);

	cinfo->blank_mode = blank_mode;
	dev_dbg(info->device, "EXIT, returning 0\n");

	/* Let fbcon करो a soft blank क्रम us */
	वापस (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
पूर्ण

/**** END   Hardware specअगरic Routines **************************************/
/****************************************************************************/
/**** BEGIN Internal Routines ***********************************************/

अटल व्योम init_vgachip(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	स्थिर काष्ठा cirrusfb_board_info_rec *bi;

	निश्चित(cinfo != शून्य);

	bi = &cirrusfb_board_info[cinfo->btype];

	/* reset board globally */
	चयन (cinfo->btype) अणु
	हाल BT_PICCOLO:
		WSFR(cinfo, 0x01);
		udelay(500);
		WSFR(cinfo, 0x51);
		udelay(500);
		अवरोध;
	हाल BT_PICASSO:
		WSFR2(cinfo, 0xff);
		udelay(500);
		अवरोध;
	हाल BT_SD64:
	हाल BT_SPECTRUM:
		WSFR(cinfo, 0x1f);
		udelay(500);
		WSFR(cinfo, 0x4f);
		udelay(500);
		अवरोध;
	हाल BT_PICASSO4:
		/* disable flickerfixer */
		vga_wcrt(cinfo->regbase, CL_CRT51, 0x00);
		mdelay(100);
		/* mode */
		vga_wgfx(cinfo->regbase, CL_GR31, 0x00);
		fallthrough;
	हाल BT_GD5480:
		/* from Klaus' NetBSD driver: */
		vga_wgfx(cinfo->regbase, CL_GR2F, 0x00);
		fallthrough;
	हाल BT_ALPINE:
		/* put blitter पूर्णांकo 542x compat */
		vga_wgfx(cinfo->regbase, CL_GR33, 0x00);
		अवरोध;

	हाल BT_LAGUNA:
	हाल BT_LAGUNAB:
		/* Nothing to करो to reset the board. */
		अवरोध;

	शेष:
		dev_err(info->device, "Warning: Unknown board type\n");
		अवरोध;
	पूर्ण

	/* make sure RAM size set by this poपूर्णांक */
	निश्चित(info->screen_size > 0);

	/* the P4 is not fully initialized here; I rely on it having been */
	/* inited under AmigaOS alपढ़ोy, which seems to work just fine    */
	/* (Klaus advised to करो it this way)			      */

	अगर (cinfo->btype != BT_PICASSO4) अणु
		WGen(cinfo, CL_VSSM, 0x10);	/* EGS: 0x16 */
		WGen(cinfo, CL_POS102, 0x01);
		WGen(cinfo, CL_VSSM, 0x08);	/* EGS: 0x0e */

		अगर (cinfo->btype != BT_SD64)
			WGen(cinfo, CL_VSSM2, 0x01);

		/* reset sequencer logic */
		vga_wseq(cinfo->regbase, VGA_SEQ_RESET, 0x03);

		/* FullBandwidth (video off) and 8/9 करोt घड़ी */
		vga_wseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE, 0x21);

		/* "magic cookie" - करोesn't make any sense to me.. */
/*      vga_wgfx(cinfo->regbase, CL_GRA, 0xce);   */
		/* unlock all extension रेजिस्टरs */
		vga_wseq(cinfo->regbase, CL_SEQR6, 0x12);

		चयन (cinfo->btype) अणु
		हाल BT_GD5480:
			vga_wseq(cinfo->regbase, CL_SEQRF, 0x98);
			अवरोध;
		हाल BT_ALPINE:
		हाल BT_LAGUNA:
		हाल BT_LAGUNAB:
			अवरोध;
		हाल BT_SD64:
#अगर_घोषित CONFIG_ZORRO
			vga_wseq(cinfo->regbase, CL_SEQRF, 0xb8);
#पूर्ण_अगर
			अवरोध;
		शेष:
			vga_wseq(cinfo->regbase, CL_SEQR16, 0x0f);
			vga_wseq(cinfo->regbase, CL_SEQRF, 0xb0);
			अवरोध;
		पूर्ण
	पूर्ण
	/* plane mask: nothing */
	vga_wseq(cinfo->regbase, VGA_SEQ_PLANE_WRITE, 0xff);
	/* अक्षरacter map select: करोesn't even matter in gx mode */
	vga_wseq(cinfo->regbase, VGA_SEQ_CHARACTER_MAP, 0x00);
	/* memory mode: chain4, ext. memory */
	vga_wseq(cinfo->regbase, VGA_SEQ_MEMORY_MODE, 0x0a);

	/* controller-पूर्णांकernal base address of video memory */
	अगर (bi->init_sr07)
		vga_wseq(cinfo->regbase, CL_SEQR7, bi->sr07);

	/*  vga_wseq(cinfo->regbase, CL_SEQR8, 0x00); */
	/* EEPROM control: shouldn't be necessary to ग_लिखो to this at all.. */

	/* graphics cursor X position (incomplete; position gives rem. 3 bits */
	vga_wseq(cinfo->regbase, CL_SEQR10, 0x00);
	/* graphics cursor Y position (..."... ) */
	vga_wseq(cinfo->regbase, CL_SEQR11, 0x00);
	/* graphics cursor attributes */
	vga_wseq(cinfo->regbase, CL_SEQR12, 0x00);
	/* graphics cursor pattern address */
	vga_wseq(cinfo->regbase, CL_SEQR13, 0x00);

	/* writing these on a P4 might give problems..  */
	अगर (cinfo->btype != BT_PICASSO4) अणु
		/* configuration पढ़ोback and ext. color */
		vga_wseq(cinfo->regbase, CL_SEQR17, 0x00);
		/* signature generator */
		vga_wseq(cinfo->regbase, CL_SEQR18, 0x02);
	पूर्ण

	/* Screen A preset row scan: none */
	vga_wcrt(cinfo->regbase, VGA_CRTC_PRESET_ROW, 0x00);
	/* Text cursor start: disable text cursor */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_START, 0x20);
	/* Text cursor end: - */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_END, 0x00);
	/* text cursor location high: 0 */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_HI, 0x00);
	/* text cursor location low: 0 */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_LO, 0x00);

	/* Underline Row scanline: - */
	vga_wcrt(cinfo->regbase, VGA_CRTC_UNDERLINE, 0x00);
	/* ### add 0x40 क्रम text modes with > 30 MHz pixघड़ी */
	/* ext. display controls: ext.adr. wrap */
	vga_wcrt(cinfo->regbase, CL_CRT1B, 0x02);

	/* Set/Reset रेजिस्टरs: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_SR_VALUE, 0x00);
	/* Set/Reset enable: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_SR_ENABLE, 0x00);
	/* Color Compare: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_COMPARE_VALUE, 0x00);
	/* Data Rotate: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_DATA_ROTATE, 0x00);
	/* Read Map Select: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_PLANE_READ, 0x00);
	/* Mode: conf. क्रम 16/4/2 color mode, no odd/even, पढ़ो/ग_लिखो mode 0 */
	vga_wgfx(cinfo->regbase, VGA_GFX_MODE, 0x00);
	/* Miscellaneous: memory map base address, graphics mode */
	vga_wgfx(cinfo->regbase, VGA_GFX_MISC, 0x01);
	/* Color Don't care: involve all planes */
	vga_wgfx(cinfo->regbase, VGA_GFX_COMPARE_MASK, 0x0f);
	/* Bit Mask: no mask at all */
	vga_wgfx(cinfo->regbase, VGA_GFX_BIT_MASK, 0xff);

	अगर (cinfo->btype == BT_ALPINE || cinfo->btype == BT_SD64 ||
	    is_laguna(cinfo))
		/* (5434 can't have bit 3 set क्रम bitblt) */
		vga_wgfx(cinfo->regbase, CL_GRB, 0x20);
	अन्यथा
	/* Graphics controller mode extensions: finer granularity,
	 * 8byte data latches
	 */
		vga_wgfx(cinfo->regbase, CL_GRB, 0x28);

	vga_wgfx(cinfo->regbase, CL_GRC, 0xff);	/* Color Key compare: - */
	vga_wgfx(cinfo->regbase, CL_GRD, 0x00);	/* Color Key compare mask: - */
	vga_wgfx(cinfo->regbase, CL_GRE, 0x00);	/* Miscellaneous control: - */
	/* Background color byte 1: - */
	/*  vga_wgfx (cinfo->regbase, CL_GR10, 0x00); */
	/*  vga_wgfx (cinfo->regbase, CL_GR11, 0x00); */

	/* Attribute Controller palette रेजिस्टरs: "identity mapping" */
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE0, 0x00);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE1, 0x01);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE2, 0x02);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE3, 0x03);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE4, 0x04);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE5, 0x05);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE6, 0x06);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE7, 0x07);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE8, 0x08);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE9, 0x09);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEA, 0x0a);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEB, 0x0b);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEC, 0x0c);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTED, 0x0d);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEE, 0x0e);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEF, 0x0f);

	/* Attribute Controller mode: graphics mode */
	vga_wattr(cinfo->regbase, VGA_ATC_MODE, 0x01);
	/* Overscan color reg.: reg. 0 */
	vga_wattr(cinfo->regbase, VGA_ATC_OVERSCAN, 0x00);
	/* Color Plane enable: Enable all 4 planes */
	vga_wattr(cinfo->regbase, VGA_ATC_PLANE_ENABLE, 0x0f);
	/* Color Select: - */
	vga_wattr(cinfo->regbase, VGA_ATC_COLOR_PAGE, 0x00);

	WGen(cinfo, VGA_PEL_MSK, 0xff);	/* Pixel mask: no mask */

	/* BLT Start/status: Blitter reset */
	vga_wgfx(cinfo->regbase, CL_GR31, 0x04);
	/* - " -	   : "end-of-reset" */
	vga_wgfx(cinfo->regbase, CL_GR31, 0x00);

	/* misc... */
	WHDR(cinfo, 0);	/* Hidden DAC रेजिस्टर: - */
	वापस;
पूर्ण

अटल व्योम चयन_monitor(काष्ठा cirrusfb_info *cinfo, पूर्णांक on)
अणु
#अगर_घोषित CONFIG_ZORRO /* only works on Zorro boards */
	अटल पूर्णांक IsOn = 0;	/* XXX not ok क्रम multiple boards */

	अगर (cinfo->btype == BT_PICASSO4)
		वापस;		/* nothing to चयन */
	अगर (cinfo->btype == BT_ALPINE)
		वापस;		/* nothing to चयन */
	अगर (cinfo->btype == BT_GD5480)
		वापस;		/* nothing to चयन */
	अगर (cinfo->btype == BT_PICASSO) अणु
		अगर ((on && !IsOn) || (!on && IsOn))
			WSFR(cinfo, 0xff);
		वापस;
	पूर्ण
	अगर (on) अणु
		चयन (cinfo->btype) अणु
		हाल BT_SD64:
			WSFR(cinfo, cinfo->SFR | 0x21);
			अवरोध;
		हाल BT_PICCOLO:
			WSFR(cinfo, cinfo->SFR | 0x28);
			अवरोध;
		हाल BT_SPECTRUM:
			WSFR(cinfo, 0x6f);
			अवरोध;
		शेष: /* करो nothing */ अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cinfo->btype) अणु
		हाल BT_SD64:
			WSFR(cinfo, cinfo->SFR & 0xde);
			अवरोध;
		हाल BT_PICCOLO:
			WSFR(cinfo, cinfo->SFR & 0xd7);
			अवरोध;
		हाल BT_SPECTRUM:
			WSFR(cinfo, 0x4f);
			अवरोध;
		शेष: /* करो nothing */
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_ZORRO */
पूर्ण

/******************************************/
/* Linux 2.6-style  accelerated functions */
/******************************************/

अटल पूर्णांक cirrusfb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;

	अगर (!is_laguna(cinfo)) अणु
		जबतक (vga_rgfx(cinfo->regbase, CL_GR31) & 0x03)
			cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cirrusfb_fillrect(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_fillrect *region)
अणु
	काष्ठा fb_fillrect modded;
	पूर्णांक vxres, vyres;
	काष्ठा cirrusfb_info *cinfo = info->par;
	पूर्णांक m = info->var.bits_per_pixel;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		cinfo->pseuकरो_palette[region->color] : region->color;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(info, region);
		वापस;
	पूर्ण

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	स_नकल(&modded, region, माप(काष्ठा fb_fillrect));

	अगर (!modded.width || !modded.height ||
	   modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	cirrusfb_RectFill(cinfo->regbase,
			  info->var.bits_per_pixel,
			  (region->dx * m) / 8, region->dy,
			  (region->width * m) / 8, region->height,
			  color, color,
			  info->fix.line_length, 0x40);
पूर्ण

अटल व्योम cirrusfb_copyarea(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा fb_copyarea modded;
	u32 vxres, vyres;
	काष्ठा cirrusfb_info *cinfo = info->par;
	पूर्णांक m = info->var.bits_per_pixel;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	स_नकल(&modded, area, माप(काष्ठा fb_copyarea));

	अगर (!modded.width || !modded.height ||
	   modded.sx >= vxres || modded.sy >= vyres ||
	   modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.sx + modded.width > vxres)
		modded.width = vxres - modded.sx;
	अगर (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	अगर (modded.sy + modded.height > vyres)
		modded.height = vyres - modded.sy;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	cirrusfb_BitBLT(cinfo->regbase, info->var.bits_per_pixel,
			(area->sx * m) / 8, area->sy,
			(area->dx * m) / 8, area->dy,
			(area->width * m) / 8, area->height,
			info->fix.line_length);

पूर्ण

अटल व्योम cirrusfb_imageblit(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	अचिन्हित अक्षर op = (info->var.bits_per_pixel == 24) ? 0xc : 0x4;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	/* Alpine/SD64 करोes not work at 24bpp ??? */
	अगर (info->flags & FBINFO_HWACCEL_DISABLED || image->depth != 1)
		cfb_imageblit(info, image);
	अन्यथा अगर ((cinfo->btype == BT_ALPINE || cinfo->btype == BT_SD64) &&
		  op == 0xc)
		cfb_imageblit(info, image);
	अन्यथा अणु
		अचिन्हित size = ((image->width + 7) >> 3) * image->height;
		पूर्णांक m = info->var.bits_per_pixel;
		u32 fg, bg;

		अगर (info->var.bits_per_pixel == 8) अणु
			fg = image->fg_color;
			bg = image->bg_color;
		पूर्ण अन्यथा अणु
			fg = ((u32 *)(info->pseuकरो_palette))[image->fg_color];
			bg = ((u32 *)(info->pseuकरो_palette))[image->bg_color];
		पूर्ण
		अगर (info->var.bits_per_pixel == 24) अणु
			/* clear background first */
			cirrusfb_RectFill(cinfo->regbase,
					  info->var.bits_per_pixel,
					  (image->dx * m) / 8, image->dy,
					  (image->width * m) / 8,
					  image->height,
					  bg, bg,
					  info->fix.line_length, 0x40);
		पूर्ण
		cirrusfb_RectFill(cinfo->regbase,
				  info->var.bits_per_pixel,
				  (image->dx * m) / 8, image->dy,
				  (image->width * m) / 8, image->height,
				  fg, bg,
				  info->fix.line_length, op);
		स_नकल(info->screen_base, image->data, size);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक release_io_ports;

/* Pulled the logic from XFree86 Cirrus driver to get the memory size,
 * based on the DRAM bandwidth bit and DRAM bank चयनing bit.  This
 * works with 1MB, 2MB and 4MB configurations (which the Motorola boards
 * seem to have. */
अटल अचिन्हित पूर्णांक cirrusfb_get_memsize(काष्ठा fb_info *info,
					 u8 __iomem *regbase)
अणु
	अचिन्हित दीर्घ mem;
	काष्ठा cirrusfb_info *cinfo = info->par;

	अगर (is_laguna(cinfo)) अणु
		अचिन्हित अक्षर SR14 = vga_rseq(regbase, CL_SEQR14);

		mem = ((SR14 & 7) + 1) << 20;
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर SRF = vga_rseq(regbase, CL_SEQRF);
		चयन ((SRF & 0x18)) अणु
		हाल 0x08:
			mem = 512 * 1024;
			अवरोध;
		हाल 0x10:
			mem = 1024 * 1024;
			अवरोध;
		/* 64-bit DRAM data bus width; assume 2MB.
		 * Also indicates 2MB memory on the 5430.
		 */
		हाल 0x18:
			mem = 2048 * 1024;
			अवरोध;
		शेष:
			dev_warn(info->device, "Unknown memory size!\n");
			mem = 1024 * 1024;
		पूर्ण
		/* If DRAM bank चयनing is enabled, there must be
		 * twice as much memory installed. (4MB on the 5434)
		 */
		अगर (cinfo->btype != BT_ALPINE && (SRF & 0x80) != 0)
			mem *= 2;
	पूर्ण

	/* TODO: Handling of GD5446/5480 (see XF86 sources ...) */
	वापस mem;
पूर्ण

अटल व्योम get_pci_addrs(स्थिर काष्ठा pci_dev *pdev,
			  अचिन्हित दीर्घ *display, अचिन्हित दीर्घ *रेजिस्टरs)
अणु
	निश्चित(pdev != शून्य);
	निश्चित(display != शून्य);
	निश्चित(रेजिस्टरs != शून्य);

	*display = 0;
	*रेजिस्टरs = 0;

	/* This is a best-guess क्रम now */

	अगर (pci_resource_flags(pdev, 0) & IORESOURCE_IO) अणु
		*display = pci_resource_start(pdev, 1);
		*रेजिस्टरs = pci_resource_start(pdev, 0);
	पूर्ण अन्यथा अणु
		*display = pci_resource_start(pdev, 0);
		*रेजिस्टरs = pci_resource_start(pdev, 1);
	पूर्ण

	निश्चित(*display != 0);
पूर्ण

अटल व्योम cirrusfb_pci_unmap(काष्ठा fb_info *info)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(info->device);
	काष्ठा cirrusfb_info *cinfo = info->par;

	अगर (cinfo->laguna_mmio == शून्य)
		iounmap(cinfo->laguna_mmio);
	iounmap(info->screen_base);
#अगर 0 /* अगर प्रणाली didn't claim this region, we would... */
	release_mem_region(0xA0000, 65535);
#पूर्ण_अगर
	अगर (release_io_ports)
		release_region(0x3C0, 32);
	pci_release_regions(pdev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_ZORRO
अटल व्योम cirrusfb_zorro_unmap(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	काष्ठा zorro_dev *zdev = to_zorro_dev(info->device);

	अगर (info->fix.smem_start > 16 * MB_)
		iounmap(info->screen_base);
	अगर (info->fix.mmio_start > 16 * MB_)
		iounmap(cinfo->regbase);

	zorro_release_device(zdev);
पूर्ण
#पूर्ण_अगर /* CONFIG_ZORRO */

/* function table of the above functions */
अटल स्थिर काष्ठा fb_ops cirrusfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= cirrusfb_खोलो,
	.fb_release	= cirrusfb_release,
	.fb_setcolreg	= cirrusfb_setcolreg,
	.fb_check_var	= cirrusfb_check_var,
	.fb_set_par	= cirrusfb_set_par,
	.fb_pan_display = cirrusfb_pan_display,
	.fb_blank	= cirrusfb_blank,
	.fb_fillrect	= cirrusfb_fillrect,
	.fb_copyarea	= cirrusfb_copyarea,
	.fb_sync	= cirrusfb_sync,
	.fb_imageblit	= cirrusfb_imageblit,
पूर्ण;

अटल पूर्णांक cirrusfb_set_fbinfo(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;

	info->pseuकरो_palette = cinfo->pseuकरो_palette;
	info->flags = FBINFO_DEFAULT
		    | FBINFO_HWACCEL_XPAN
		    | FBINFO_HWACCEL_YPAN
		    | FBINFO_HWACCEL_FILLRECT
		    | FBINFO_HWACCEL_IMAGEBLIT
		    | FBINFO_HWACCEL_COPYAREA;
	अगर (noaccel || is_laguna(cinfo)) अणु
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->fix.accel = FB_ACCEL_NONE;
	पूर्ण अन्यथा
		info->fix.accel = FB_ACCEL_CIRRUS_ALPINE;

	info->fbops = &cirrusfb_ops;

	अगर (cinfo->btype == BT_GD5480) अणु
		अगर (var->bits_per_pixel == 16)
			info->screen_base += 1 * MB_;
		अगर (var->bits_per_pixel == 32)
			info->screen_base += 2 * MB_;
	पूर्ण

	/* Fill fix common fields */
	strlcpy(info->fix.id, cirrusfb_board_info[cinfo->btype].name,
		माप(info->fix.id));

	/* monochrome: only 1 memory plane */
	/* 8 bit and above: Use whole memory area */
	info->fix.smem_len   = info->screen_size;
	अगर (var->bits_per_pixel == 1)
		info->fix.smem_len /= 4;
	info->fix.type_aux   = 0;
	info->fix.xpanstep   = 1;
	info->fix.ypanstep   = 1;
	info->fix.ywrapstep  = 0;

	/* FIXME: map region at 0xB8000 अगर available, fill in here */
	info->fix.mmio_len   = 0;

	fb_alloc_cmap(&info->cmap, 256, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cirrusfb_रेजिस्टर(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;
	पूर्णांक err;

	/* sanity checks */
	निश्चित(cinfo->btype != BT_NONE);

	/* set all the vital stuff */
	cirrusfb_set_fbinfo(info);

	dev_dbg(info->device, "(RAM start set to: 0x%p)\n", info->screen_base);

	err = fb_find_mode(&info->var, info, mode_option, शून्य, 0, शून्य, 8);
	अगर (!err) अणु
		dev_dbg(info->device, "wrong initial video mode\n");
		err = -EINVAL;
		जाओ err_dealloc_cmap;
	पूर्ण

	info->var.activate = FB_ACTIVATE_NOW;

	err = cirrusfb_check_var(&info->var, info);
	अगर (err < 0) अणु
		/* should never happen */
		dev_dbg(info->device,
			"choking on default var... umm, no good.\n");
		जाओ err_dealloc_cmap;
	पूर्ण

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		dev_err(info->device,
			"could not register fb device; err = %d!\n", err);
		जाओ err_dealloc_cmap;
	पूर्ण

	वापस 0;

err_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);
	वापस err;
पूर्ण

अटल व्योम cirrusfb_cleanup(काष्ठा fb_info *info)
अणु
	काष्ठा cirrusfb_info *cinfo = info->par;

	चयन_monitor(cinfo, 0);
	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	dev_dbg(info->device, "Framebuffer unregistered\n");
	cinfo->unmap(info);
	framebuffer_release(info);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक cirrusfb_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा cirrusfb_info *cinfo;
	काष्ठा fb_info *info;
	अचिन्हित दीर्घ board_addr, board_size;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "cirrusfb: Cannot enable PCI device\n");
		जाओ err_out;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा cirrusfb_info), &pdev->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण

	cinfo = info->par;
	cinfo->btype = (क्रमागत cirrus_board) ent->driver_data;

	dev_dbg(info->device,
		" Found PCI device, base address 0 is 0x%Lx, btype set to %d\n",
		(अचिन्हित दीर्घ दीर्घ)pdev->resource[0].start,  cinfo->btype);
	dev_dbg(info->device, " base address 1 is 0x%Lx\n",
		(अचिन्हित दीर्घ दीर्घ)pdev->resource[1].start);

	dev_dbg(info->device,
		"Attempt to get PCI info for Cirrus Graphics Card\n");
	get_pci_addrs(pdev, &board_addr, &info->fix.mmio_start);
	/* FIXME: this क्रमces VGA.  alternatives? */
	cinfo->regbase = शून्य;
	cinfo->laguna_mmio = ioremap(info->fix.mmio_start, 0x1000);

	dev_dbg(info->device, "Board address: 0x%lx, register address: 0x%lx\n",
		board_addr, info->fix.mmio_start);

	board_size = (cinfo->btype == BT_GD5480) ?
		32 * MB_ : cirrusfb_get_memsize(info, cinfo->regbase);

	ret = pci_request_regions(pdev, "cirrusfb");
	अगर (ret < 0) अणु
		dev_err(info->device, "cannot reserve region 0x%lx, abort\n",
			board_addr);
		जाओ err_release_fb;
	पूर्ण
#अगर 0 /* अगर the प्रणाली didn't claim this region, we would... */
	अगर (!request_mem_region(0xA0000, 65535, "cirrusfb")) अणु
		dev_err(info->device, "cannot reserve region 0x%lx, abort\n",
			0xA0000L);
		ret = -EBUSY;
		जाओ err_release_regions;
	पूर्ण
#पूर्ण_अगर
	अगर (request_region(0x3C0, 32, "cirrusfb"))
		release_io_ports = 1;

	info->screen_base = ioremap(board_addr, board_size);
	अगर (!info->screen_base) अणु
		ret = -EIO;
		जाओ err_release_legacy;
	पूर्ण

	info->fix.smem_start = board_addr;
	info->screen_size = board_size;
	cinfo->unmap = cirrusfb_pci_unmap;

	dev_info(info->device,
		 "Cirrus Logic chipset on PCI bus, RAM (%lu kB) at 0x%lx\n",
		 info->screen_size >> 10, board_addr);
	pci_set_drvdata(pdev, info);

	ret = cirrusfb_रेजिस्टर(info);
	अगर (!ret)
		वापस 0;

	iounmap(info->screen_base);
err_release_legacy:
	अगर (release_io_ports)
		release_region(0x3C0, 32);
#अगर 0
	release_mem_region(0xA0000, 65535);
err_release_regions:
#पूर्ण_अगर
	pci_release_regions(pdev);
err_release_fb:
	अगर (cinfo->laguna_mmio != शून्य)
		iounmap(cinfo->laguna_mmio);
	framebuffer_release(info);
err_out:
	वापस ret;
पूर्ण

अटल व्योम cirrusfb_pci_unरेजिस्टर(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);

	cirrusfb_cleanup(info);
पूर्ण

अटल काष्ठा pci_driver cirrusfb_pci_driver = अणु
	.name		= "cirrusfb",
	.id_table	= cirrusfb_pci_table,
	.probe		= cirrusfb_pci_रेजिस्टर,
	.हटाओ		= cirrusfb_pci_unरेजिस्टर,
#अगर_घोषित CONFIG_PM
#अगर 0
	.suspend	= cirrusfb_pci_suspend,
	.resume		= cirrusfb_pci_resume,
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_ZORRO
अटल पूर्णांक cirrusfb_zorro_रेजिस्टर(काष्ठा zorro_dev *z,
				   स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा fb_info *info;
	पूर्णांक error;
	स्थिर काष्ठा zorrocl *zcl;
	क्रमागत cirrus_board btype;
	अचिन्हित दीर्घ regbase, ramsize, rambase;
	काष्ठा cirrusfb_info *cinfo;

	info = framebuffer_alloc(माप(काष्ठा cirrusfb_info), &z->dev);
	अगर (!info)
		वापस -ENOMEM;

	zcl = (स्थिर काष्ठा zorrocl *)ent->driver_data;
	btype = zcl->type;
	regbase = zorro_resource_start(z) + zcl->regoffset;
	ramsize = zcl->ramsize;
	अगर (ramsize) अणु
		rambase = zorro_resource_start(z) + zcl->ramoffset;
		अगर (zorro_resource_len(z) == 64 * MB_) अणु
			/* Quirk क्रम 64 MiB Picasso IV */
			rambase += zcl->ramoffset;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा zorro_dev *ram = zorro_find_device(zcl->ramid, शून्य);
		अगर (!ram || !zorro_resource_len(ram)) अणु
			dev_err(info->device, "No video RAM found\n");
			error = -ENODEV;
			जाओ err_release_fb;
		पूर्ण
		rambase = zorro_resource_start(ram);
		ramsize = zorro_resource_len(ram);
		अगर (zcl->ramid2 &&
		    (ram = zorro_find_device(zcl->ramid2, शून्य))) अणु
			अगर (zorro_resource_start(ram) != rambase + ramsize) अणु
				dev_warn(info->device,
					 "Skipping non-contiguous RAM at %pR\n",
					 &ram->resource);
			पूर्ण अन्यथा अणु
				ramsize += zorro_resource_len(ram);
			पूर्ण
		पूर्ण
	पूर्ण

	dev_info(info->device,
		 "%s board detected, REG at 0x%lx, %lu MiB RAM at 0x%lx\n",
		 cirrusfb_board_info[btype].name, regbase, ramsize / MB_,
		 rambase);

	अगर (!zorro_request_device(z, "cirrusfb")) अणु
		dev_err(info->device, "Cannot reserve %pR\n", &z->resource);
		error = -EBUSY;
		जाओ err_release_fb;
	पूर्ण

	cinfo = info->par;
	cinfo->btype = btype;

	info->fix.mmio_start = regbase;
	cinfo->regbase = regbase > 16 * MB_ ? ioremap(regbase, 64 * 1024)
					    : ZTWO_VADDR(regbase);
	अगर (!cinfo->regbase) अणु
		dev_err(info->device, "Cannot map registers\n");
		error = -EIO;
		जाओ err_release_dev;
	पूर्ण

	info->fix.smem_start = rambase;
	info->screen_size = ramsize;
	info->screen_base = rambase > 16 * MB_ ? ioremap(rambase, ramsize)
					       : ZTWO_VADDR(rambase);
	अगर (!info->screen_base) अणु
		dev_err(info->device, "Cannot map video RAM\n");
		error = -EIO;
		जाओ err_unmap_reg;
	पूर्ण

	cinfo->unmap = cirrusfb_zorro_unmap;

	dev_info(info->device,
		 "Cirrus Logic chipset on Zorro bus, RAM (%lu MiB) at 0x%lx\n",
		 ramsize / MB_, rambase);

	/* MCLK select etc. */
	अगर (cirrusfb_board_info[btype].init_sr1f)
		vga_wseq(cinfo->regbase, CL_SEQR1F,
			 cirrusfb_board_info[btype].sr1f);

	error = cirrusfb_रेजिस्टर(info);
	अगर (error) अणु
		dev_err(info->device, "Failed to register device, error %d\n",
			error);
		जाओ err_unmap_ram;
	पूर्ण

	zorro_set_drvdata(z, info);
	वापस 0;

err_unmap_ram:
	अगर (rambase > 16 * MB_)
		iounmap(info->screen_base);

err_unmap_reg:
	अगर (regbase > 16 * MB_)
		iounmap(cinfo->regbase);
err_release_dev:
	zorro_release_device(z);
err_release_fb:
	framebuffer_release(info);
	वापस error;
पूर्ण

व्योम cirrusfb_zorro_unरेजिस्टर(काष्ठा zorro_dev *z)
अणु
	काष्ठा fb_info *info = zorro_get_drvdata(z);

	cirrusfb_cleanup(info);
	zorro_set_drvdata(z, शून्य);
पूर्ण

अटल काष्ठा zorro_driver cirrusfb_zorro_driver = अणु
	.name		= "cirrusfb",
	.id_table	= cirrusfb_zorro_table,
	.probe		= cirrusfb_zorro_रेजिस्टर,
	.हटाओ		= cirrusfb_zorro_unरेजिस्टर,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ZORRO */

#अगर_अघोषित MODULE
अटल पूर्णांक __init cirrusfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेद(this_opt, "noaccel"))
			noaccel = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "mode:", 5))
			mode_option = this_opt + 5;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

    /*
     *  Modularization
     */

MODULE_AUTHOR("Copyright 1999,2000 Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION("Accelerated FBDev driver for Cirrus Logic chips");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init cirrusfb_init(व्योम)
अणु
	पूर्णांक error = 0;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("cirrusfb", &option))
		वापस -ENODEV;
	cirrusfb_setup(option);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZORRO
	error |= zorro_रेजिस्टर_driver(&cirrusfb_zorro_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	error |= pci_रेजिस्टर_driver(&cirrusfb_pci_driver);
#पूर्ण_अगर
	वापस error;
पूर्ण

अटल व्योम __निकास cirrusfb_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&cirrusfb_pci_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZORRO
	zorro_unरेजिस्टर_driver(&cirrusfb_zorro_driver);
#पूर्ण_अगर
पूर्ण

module_init(cirrusfb_init);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode e.g. '648x480-8@60'");
module_param(noaccel, bool, 0);
MODULE_PARM_DESC(noaccel, "Disable acceleration");

#अगर_घोषित MODULE
module_निकास(cirrusfb_निकास);
#पूर्ण_अगर

/**********************************************************************/
/* about the following functions - I have used the same names क्रम the */
/* functions as Markus Wild did in his Retina driver क्रम NetBSD as    */
/* they just made sense क्रम this purpose. Apart from that, I wrote    */
/* these functions myself.					    */
/**********************************************************************/

/*** WGen() - ग_लिखो पूर्णांकo one of the बाह्यal/general रेजिस्टरs ***/
अटल व्योम WGen(स्थिर काष्ठा cirrusfb_info *cinfo,
		  पूर्णांक regnum, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ regofs = 0;

	अगर (cinfo->btype == BT_PICASSO) अणु
		/* Picasso II specअगरic hack */
/*	      अगर (regnum == VGA_PEL_IR || regnum == VGA_PEL_D ||
		  regnum == CL_VSSM2) */
		अगर (regnum == VGA_PEL_IR || regnum == VGA_PEL_D)
			regofs = 0xfff;
	पूर्ण

	vga_w(cinfo->regbase, regofs + regnum, val);
पूर्ण

/*** RGen() - पढ़ो out one of the बाह्यal/general रेजिस्टरs ***/
अटल अचिन्हित अक्षर RGen(स्थिर काष्ठा cirrusfb_info *cinfo, पूर्णांक regnum)
अणु
	अचिन्हित दीर्घ regofs = 0;

	अगर (cinfo->btype == BT_PICASSO) अणु
		/* Picasso II specअगरic hack */
/*	      अगर (regnum == VGA_PEL_IR || regnum == VGA_PEL_D ||
		  regnum == CL_VSSM2) */
		अगर (regnum == VGA_PEL_IR || regnum == VGA_PEL_D)
			regofs = 0xfff;
	पूर्ण

	वापस vga_r(cinfo->regbase, regofs + regnum);
पूर्ण

/*** AttrOn() - turn on VideoEnable क्रम Attribute controller ***/
अटल व्योम AttrOn(स्थिर काष्ठा cirrusfb_info *cinfo)
अणु
	निश्चित(cinfo != शून्य);

	अगर (vga_rcrt(cinfo->regbase, CL_CRT24) & 0x80) अणु
		/* अगर we're just in "write value" mode, ग_लिखो back the */
		/* same value as beक्रमe to not modअगरy anything */
		vga_w(cinfo->regbase, VGA_ATT_IW,
		      vga_r(cinfo->regbase, VGA_ATT_R));
	पूर्ण
	/* turn on video bit */
/*      vga_w(cinfo->regbase, VGA_ATT_IW, 0x20); */
	vga_w(cinfo->regbase, VGA_ATT_IW, 0x33);

	/* dummy ग_लिखो on Reg0 to be on "write index" mode next समय */
	vga_w(cinfo->regbase, VGA_ATT_IW, 0x00);
पूर्ण

/*** WHDR() - ग_लिखो पूर्णांकo the Hidden DAC रेजिस्टर ***/
/* as the HDR is the only extension रेजिस्टर that requires special treaपंचांगent
 * (the other extension रेजिस्टरs are accessible just like the "ordinary"
 * रेजिस्टरs of their functional group) here is a specialized routine क्रम
 * accessing the HDR
 */
अटल व्योम WHDR(स्थिर काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val)
अणु
	अगर (is_laguna(cinfo))
		वापस;
	अगर (cinfo->btype == BT_PICASSO) अणु
		/* Klaus' hपूर्णांक क्रम correct access to HDR on some boards */
		/* first ग_लिखो 0 to pixel mask (3c6) */
		WGen(cinfo, VGA_PEL_MSK, 0x00);
		udelay(200);
		/* next पढ़ो dummy from pixel address (3c8) */
		RGen(cinfo, VGA_PEL_IW);
		udelay(200);
	पूर्ण
	/* now करो the usual stuff to access the HDR */

	RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	RGen(cinfo, VGA_PEL_MSK);
	udelay(200);

	WGen(cinfo, VGA_PEL_MSK, val);
	udelay(200);

	अगर (cinfo->btype == BT_PICASSO) अणु
		/* now first reset HDR access counter */
		RGen(cinfo, VGA_PEL_IW);
		udelay(200);

		/* and at the end, restore the mask value */
		/* ## is this mask always 0xff? */
		WGen(cinfo, VGA_PEL_MSK, 0xff);
		udelay(200);
	पूर्ण
पूर्ण

/*** WSFR() - ग_लिखो to the "special function register" (SFR) ***/
अटल व्योम WSFR(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val)
अणु
#अगर_घोषित CONFIG_ZORRO
	निश्चित(cinfo->regbase != शून्य);
	cinfo->SFR = val;
	z_ग_लिखोb(val, cinfo->regbase + 0x8000);
#पूर्ण_अगर
पूर्ण

/* The Picasso has a second रेजिस्टर क्रम चयनing the monitor bit */
अटल व्योम WSFR2(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर val)
अणु
#अगर_घोषित CONFIG_ZORRO
	/* writing an arbitrary value to this one causes the monitor चयनer */
	/* to flip to Amiga display */
	निश्चित(cinfo->regbase != शून्य);
	cinfo->SFR = val;
	z_ग_लिखोb(val, cinfo->regbase + 0x9000);
#पूर्ण_अगर
पूर्ण

/*** WClut - set CLUT entry (range: 0..63) ***/
अटल व्योम WClut(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर regnum, अचिन्हित अक्षर red,
	    अचिन्हित अक्षर green, अचिन्हित अक्षर blue)
अणु
	अचिन्हित पूर्णांक data = VGA_PEL_D;

	/* address ग_लिखो mode रेजिस्टर is not translated.. */
	vga_w(cinfo->regbase, VGA_PEL_IW, regnum);

	अगर (cinfo->btype == BT_PICASSO || cinfo->btype == BT_PICASSO4 ||
	    cinfo->btype == BT_ALPINE || cinfo->btype == BT_GD5480 ||
	    cinfo->btype == BT_SD64 || is_laguna(cinfo)) अणु
		/* but DAC data रेजिस्टर IS, at least क्रम Picasso II */
		अगर (cinfo->btype == BT_PICASSO)
			data += 0xfff;
		vga_w(cinfo->regbase, data, red);
		vga_w(cinfo->regbase, data, green);
		vga_w(cinfo->regbase, data, blue);
	पूर्ण अन्यथा अणु
		vga_w(cinfo->regbase, data, blue);
		vga_w(cinfo->regbase, data, green);
		vga_w(cinfo->regbase, data, red);
	पूर्ण
पूर्ण

#अगर 0
/*** RClut - पढ़ो CLUT entry (range 0..63) ***/
अटल व्योम RClut(काष्ठा cirrusfb_info *cinfo, अचिन्हित अक्षर regnum, अचिन्हित अक्षर *red,
	    अचिन्हित अक्षर *green, अचिन्हित अक्षर *blue)
अणु
	अचिन्हित पूर्णांक data = VGA_PEL_D;

	vga_w(cinfo->regbase, VGA_PEL_IR, regnum);

	अगर (cinfo->btype == BT_PICASSO || cinfo->btype == BT_PICASSO4 ||
	    cinfo->btype == BT_ALPINE || cinfo->btype == BT_GD5480) अणु
		अगर (cinfo->btype == BT_PICASSO)
			data += 0xfff;
		*red = vga_r(cinfo->regbase, data);
		*green = vga_r(cinfo->regbase, data);
		*blue = vga_r(cinfo->regbase, data);
	पूर्ण अन्यथा अणु
		*blue = vga_r(cinfo->regbase, data);
		*green = vga_r(cinfo->regbase, data);
		*red = vga_r(cinfo->regbase, data);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*******************************************************************
	cirrusfb_WaitBLT()

	Wait क्रम the BitBLT engine to complete a possible earlier job
*********************************************************************/

/* FIXME: use पूर्णांकerrupts instead */
अटल व्योम cirrusfb_WaitBLT(u8 __iomem *regbase)
अणु
	जबतक (vga_rgfx(regbase, CL_GR31) & 0x08)
		cpu_relax();
पूर्ण

/*******************************************************************
	cirrusfb_BitBLT()

	perक्रमm accelerated "scrolling"
********************************************************************/

अटल व्योम cirrusfb_set_blitter(u8 __iomem *regbase,
			    u_लघु nwidth, u_लघु nheight,
			    u_दीर्घ nsrc, u_दीर्घ ndest,
			    u_लघु blपंचांगode, u_लघु line_length)

अणु
	/* pitch: set to line_length */
	/* dest pitch low */
	vga_wgfx(regbase, CL_GR24, line_length & 0xff);
	/* dest pitch hi */
	vga_wgfx(regbase, CL_GR25, line_length >> 8);
	/* source pitch low */
	vga_wgfx(regbase, CL_GR26, line_length & 0xff);
	/* source pitch hi */
	vga_wgfx(regbase, CL_GR27, line_length >> 8);

	/* BLT width: actual number of pixels - 1 */
	/* BLT width low */
	vga_wgfx(regbase, CL_GR20, nwidth & 0xff);
	/* BLT width hi */
	vga_wgfx(regbase, CL_GR21, nwidth >> 8);

	/* BLT height: actual number of lines -1 */
	/* BLT height low */
	vga_wgfx(regbase, CL_GR22, nheight & 0xff);
	/* BLT width hi */
	vga_wgfx(regbase, CL_GR23, nheight >> 8);

	/* BLT destination */
	/* BLT dest low */
	vga_wgfx(regbase, CL_GR28, (u_अक्षर) (ndest & 0xff));
	/* BLT dest mid */
	vga_wgfx(regbase, CL_GR29, (u_अक्षर) (ndest >> 8));
	/* BLT dest hi */
	vga_wgfx(regbase, CL_GR2A, (u_अक्षर) (ndest >> 16));

	/* BLT source */
	/* BLT src low */
	vga_wgfx(regbase, CL_GR2C, (u_अक्षर) (nsrc & 0xff));
	/* BLT src mid */
	vga_wgfx(regbase, CL_GR2D, (u_अक्षर) (nsrc >> 8));
	/* BLT src hi */
	vga_wgfx(regbase, CL_GR2E, (u_अक्षर) (nsrc >> 16));

	/* BLT mode */
	vga_wgfx(regbase, CL_GR30, blपंचांगode);	/* BLT mode */

	/* BLT ROP: SrcCopy */
	vga_wgfx(regbase, CL_GR32, 0x0d);	/* BLT ROP */

	/* and finally: GO! */
	vga_wgfx(regbase, CL_GR31, 0x02);	/* BLT Start/status */
पूर्ण

/*******************************************************************
	cirrusfb_BitBLT()

	perक्रमm accelerated "scrolling"
********************************************************************/

अटल व्योम cirrusfb_BitBLT(u8 __iomem *regbase, पूर्णांक bits_per_pixel,
			    u_लघु curx, u_लघु cury,
			    u_लघु destx, u_लघु desty,
			    u_लघु width, u_लघु height,
			    u_लघु line_length)
अणु
	u_लघु nwidth = width - 1;
	u_लघु nheight = height - 1;
	u_दीर्घ nsrc, ndest;
	u_अक्षर blपंचांगode;

	blपंचांगode = 0x00;
	/* अगर source adr < dest addr, करो the Blt backwards */
	अगर (cury <= desty) अणु
		अगर (cury == desty) अणु
			/* अगर src and dest are on the same line, check x */
			अगर (curx < destx)
				blपंचांगode |= 0x01;
		पूर्ण अन्यथा
			blपंचांगode |= 0x01;
	पूर्ण
	/* standard हाल: क्रमward blitting */
	nsrc = (cury * line_length) + curx;
	ndest = (desty * line_length) + destx;
	अगर (blपंचांगode) अणु
		/* this means start addresses are at the end,
		 * counting backwards
		 */
		nsrc += nheight * line_length + nwidth;
		ndest += nheight * line_length + nwidth;
	पूर्ण

	cirrusfb_WaitBLT(regbase);

	cirrusfb_set_blitter(regbase, nwidth, nheight,
			    nsrc, ndest, blपंचांगode, line_length);
पूर्ण

/*******************************************************************
	cirrusfb_RectFill()

	perक्रमm accelerated rectangle fill
********************************************************************/

अटल व्योम cirrusfb_RectFill(u8 __iomem *regbase, पूर्णांक bits_per_pixel,
		     u_लघु x, u_लघु y, u_लघु width, u_लघु height,
		     u32 fg_color, u32 bg_color, u_लघु line_length,
		     u_अक्षर bliपंचांगode)
अणु
	u_दीर्घ ndest = (y * line_length) + x;
	u_अक्षर op;

	cirrusfb_WaitBLT(regbase);

	/* This is a ColorExpand Blt, using the */
	/* same color क्रम क्रमeground and background */
	vga_wgfx(regbase, VGA_GFX_SR_VALUE, bg_color);
	vga_wgfx(regbase, VGA_GFX_SR_ENABLE, fg_color);

	op = 0x80;
	अगर (bits_per_pixel >= 16) अणु
		vga_wgfx(regbase, CL_GR10, bg_color >> 8);
		vga_wgfx(regbase, CL_GR11, fg_color >> 8);
		op = 0x90;
	पूर्ण
	अगर (bits_per_pixel >= 24) अणु
		vga_wgfx(regbase, CL_GR12, bg_color >> 16);
		vga_wgfx(regbase, CL_GR13, fg_color >> 16);
		op = 0xa0;
	पूर्ण
	अगर (bits_per_pixel == 32) अणु
		vga_wgfx(regbase, CL_GR14, bg_color >> 24);
		vga_wgfx(regbase, CL_GR15, fg_color >> 24);
		op = 0xb0;
	पूर्ण
	cirrusfb_set_blitter(regbase, width - 1, height - 1,
			    0, ndest, op | bliपंचांगode, line_length);
पूर्ण

/**************************************************************************
 * bestघड़ी() - determine बंदst possible घड़ी lower(?) than the
 * desired pixel घड़ी
 **************************************************************************/
अटल व्योम bestघड़ी(दीर्घ freq, पूर्णांक *nom, पूर्णांक *den, पूर्णांक *भाग)
अणु
	पूर्णांक n, d;
	दीर्घ h, dअगरf;

	निश्चित(nom != शून्य);
	निश्चित(den != शून्य);
	निश्चित(भाग != शून्य);

	*nom = 0;
	*den = 0;
	*भाग = 0;

	अगर (freq < 8000)
		freq = 8000;

	dअगरf = freq;

	क्रम (n = 32; n < 128; n++) अणु
		पूर्णांक s = 0;

		d = (14318 * n) / freq;
		अगर ((d >= 7) && (d <= 63)) अणु
			पूर्णांक temp = d;

			अगर (temp > 31) अणु
				s = 1;
				temp >>= 1;
			पूर्ण
			h = ((14318 * n) / temp) >> s;
			h = h > freq ? h - freq : freq - h;
			अगर (h < dअगरf) अणु
				dअगरf = h;
				*nom = n;
				*den = temp;
				*भाग = s;
			पूर्ण
		पूर्ण
		d++;
		अगर ((d >= 7) && (d <= 63)) अणु
			अगर (d > 31) अणु
				s = 1;
				d >>= 1;
			पूर्ण
			h = ((14318 * n) / d) >> s;
			h = h > freq ? h - freq : freq - h;
			अगर (h < dअगरf) अणु
				dअगरf = h;
				*nom = n;
				*den = d;
				*भाग = s;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------
 *
 * debugging functions
 *
 * -------------------------------------------------------------------------
 */

#अगर_घोषित CIRRUSFB_DEBUG

/*
 * cirrusfb_dbg_prपूर्णांक_regs
 * @regbase: If using newmmio, the newmmio base address, otherwise %शून्य
 * @reg_class: type of रेजिस्टरs to पढ़ो: %CRT, or %SEQ
 *
 * DESCRIPTION:
 * Dumps the given list of VGA CRTC रेजिस्टरs.  If @base is %शून्य,
 * old-style I/O ports are queried क्रम inक्रमmation, otherwise MMIO is
 * used at the given @base address to query the inक्रमmation.
 */

अटल व्योम cirrusfb_dbg_prपूर्णांक_regs(काष्ठा fb_info *info,
				    caddr_t regbase,
				    क्रमागत cirrusfb_dbg_reg_class reg_class, ...)
अणु
	बहु_सूची list;
	अचिन्हित अक्षर val = 0;
	अचिन्हित reg;
	अक्षर *name;

	बहु_शुरू(list, reg_class);

	name = बहु_तर्क(list, अक्षर *);
	जबतक (name != शून्य) अणु
		reg = बहु_तर्क(list, पूर्णांक);

		चयन (reg_class) अणु
		हाल CRT:
			val = vga_rcrt(regbase, (अचिन्हित अक्षर) reg);
			अवरोध;
		हाल SEQ:
			val = vga_rseq(regbase, (अचिन्हित अक्षर) reg);
			अवरोध;
		शेष:
			/* should never occur */
			निश्चित(false);
			अवरोध;
		पूर्ण

		dev_dbg(info->device, "%8s = 0x%02X\n", name, val);

		name = बहु_तर्क(list, अक्षर *);
	पूर्ण

	बहु_पूर्ण(list);
पूर्ण

/*
 * cirrusfb_dbg_reg_dump
 * @base: If using newmmio, the newmmio base address, otherwise %शून्य
 *
 * DESCRIPTION:
 * Dumps a list of पूर्णांकeresting VGA and CIRRUSFB रेजिस्टरs.  If @base is %शून्य,
 * old-style I/O ports are queried क्रम inक्रमmation, otherwise MMIO is
 * used at the given @base address to query the inक्रमmation.
 */

अटल व्योम cirrusfb_dbg_reg_dump(काष्ठा fb_info *info, caddr_t regbase)
अणु
	dev_dbg(info->device, "VGA CRTC register dump:\n");

	cirrusfb_dbg_prपूर्णांक_regs(info, regbase, CRT,
			   "CR00", 0x00,
			   "CR01", 0x01,
			   "CR02", 0x02,
			   "CR03", 0x03,
			   "CR04", 0x04,
			   "CR05", 0x05,
			   "CR06", 0x06,
			   "CR07", 0x07,
			   "CR08", 0x08,
			   "CR09", 0x09,
			   "CR0A", 0x0A,
			   "CR0B", 0x0B,
			   "CR0C", 0x0C,
			   "CR0D", 0x0D,
			   "CR0E", 0x0E,
			   "CR0F", 0x0F,
			   "CR10", 0x10,
			   "CR11", 0x11,
			   "CR12", 0x12,
			   "CR13", 0x13,
			   "CR14", 0x14,
			   "CR15", 0x15,
			   "CR16", 0x16,
			   "CR17", 0x17,
			   "CR18", 0x18,
			   "CR22", 0x22,
			   "CR24", 0x24,
			   "CR26", 0x26,
			   "CR2D", 0x2D,
			   "CR2E", 0x2E,
			   "CR2F", 0x2F,
			   "CR30", 0x30,
			   "CR31", 0x31,
			   "CR32", 0x32,
			   "CR33", 0x33,
			   "CR34", 0x34,
			   "CR35", 0x35,
			   "CR36", 0x36,
			   "CR37", 0x37,
			   "CR38", 0x38,
			   "CR39", 0x39,
			   "CR3A", 0x3A,
			   "CR3B", 0x3B,
			   "CR3C", 0x3C,
			   "CR3D", 0x3D,
			   "CR3E", 0x3E,
			   "CR3F", 0x3F,
			   शून्य);

	dev_dbg(info->device, "\n");

	dev_dbg(info->device, "VGA SEQ register dump:\n");

	cirrusfb_dbg_prपूर्णांक_regs(info, regbase, SEQ,
			   "SR00", 0x00,
			   "SR01", 0x01,
			   "SR02", 0x02,
			   "SR03", 0x03,
			   "SR04", 0x04,
			   "SR08", 0x08,
			   "SR09", 0x09,
			   "SR0A", 0x0A,
			   "SR0B", 0x0B,
			   "SR0D", 0x0D,
			   "SR10", 0x10,
			   "SR11", 0x11,
			   "SR12", 0x12,
			   "SR13", 0x13,
			   "SR14", 0x14,
			   "SR15", 0x15,
			   "SR16", 0x16,
			   "SR17", 0x17,
			   "SR18", 0x18,
			   "SR19", 0x19,
			   "SR1A", 0x1A,
			   "SR1B", 0x1B,
			   "SR1C", 0x1C,
			   "SR1D", 0x1D,
			   "SR1E", 0x1E,
			   "SR1F", 0x1F,
			   शून्य);

	dev_dbg(info->device, "\n");
पूर्ण

#पूर्ण_अगर				/* CIRRUSFB_DEBUG */

