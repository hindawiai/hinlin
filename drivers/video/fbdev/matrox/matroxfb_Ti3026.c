<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200 and G400
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Portions Copyright (c) 2001 Matrox Graphics Inc.
 *
 * Version: 1.65 2002/08/14
 *
 * MTRR stuff: 1998 Tom Rini <trini@kernel.crashing.org>
 *
 * Contributors: "menion?" <menion@mindless.com>
 *                     Betatesting, fixes, ideas
 *
 *               "Kurt Garloff" <garloff@suse.de>
 *                     Betatesting, fixes, ideas, videomodes, videomodes timmings
 *
 *               "Tom Rini" <trini@kernel.crashing.org>
 *                     MTRR stuff, PPC cleanups, betatesting, fixes, ideas
 *
 *               "Bibek Sahu" <scorpio@करोdds.net>
 *                     Access device through पढ़ोb|w|l and ग_लिखो b|w|l
 *                     Extensive debugging stuff
 *
 *               "Daniel Haun" <haund@usa.net>
 *                     Testing, hardware cursor fixes
 *
 *               "Scott Wood" <sawst46+@pitt.edu>
 *                     Fixes
 *
 *               "Gerd Knorr" <kraxel@goldbach.isdn.cs.tu-berlin.de>
 *                     Betatesting
 *
 *               "Kelly French" <targon@hazmat.com>
 *               "Fernando Herrera" <fherrera@eurielec.etsit.upm.es>
 *                     Betatesting, bug reporting
 *
 *               "Pablo Bianucci" <pbian@pccp.com.ar>
 *                     Fixes, ideas, betatesting
 *
 *               "Inaky Perez Gonzalez" <inaky@peloncho.fis.ucm.es>
 *                     Fixes, enhandcements, ideas, betatesting
 *
 *               "Ryuichi Oikawa" <roikawa@rr.iiij4u.or.jp>
 *                     PPC betatesting, PPC support, backward compatibility
 *
 *               "Paul Womar" <Paul@pwomar.demon.co.uk>
 *               "Owen Waller" <O.Waller@ee.qub.ac.uk>
 *                     PPC betatesting
 *
 *               "Thomas Pornin" <pornin@bolet.ens.fr>
 *                     Alpha betatesting
 *
 *               "Pieter van Leuven" <pvl@iae.nl>
 *               "Ulf Jaenicke-Roessler" <ujr@physik.phy.tu-dresden.de>
 *                     G100 testing
 *
 *               "H. Peter Arvin" <hpa@transmeta.com>
 *                     Ideas
 *
 *               "Cort Dougan" <cort@cs.nmt.edu>
 *                     CHRP fixes and PReP cleanup
 *
 *               "Mark Vojkovich" <mvojkovi@ucsd.edu>
 *                     G400 support
 *
 * (following author is not in any relation with this code, but his code
 *  is included in this driver)
 *
 * Based on framebuffer driver क्रम VBE 2.0 compliant graphic boards
 *     (c) 1998 Gerd Knorr <kraxel@cs.tu-berlin.de>
 *
 * (following author is not in any relation with this code, but his ideas
 *  were used when writing this driver)
 *
 *		 FreeVBE/AF (Matrox), "Shawn Hargreaves" <shawn@talula.demon.co.uk>
 *
 */


#समावेश "matroxfb_Ti3026.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_accel.h"
#समावेश <linux/matroxfb.h>

#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
#घोषणा outTi3026 matroxfb_DAC_out
#घोषणा inTi3026 matroxfb_DAC_in

#घोषणा TVP3026_INDEX		0x00
#घोषणा TVP3026_PALWRADD	0x00
#घोषणा TVP3026_PALDATA		0x01
#घोषणा TVP3026_PIXRDMSK	0x02
#घोषणा TVP3026_PALRDADD	0x03
#घोषणा TVP3026_CURCOLWRADD	0x04
#घोषणा     TVP3026_CLOVERSCAN		0x00
#घोषणा     TVP3026_CLCOLOR0		0x01
#घोषणा     TVP3026_CLCOLOR1		0x02
#घोषणा     TVP3026_CLCOLOR2		0x03
#घोषणा TVP3026_CURCOLDATA	0x05
#घोषणा TVP3026_CURCOLRDADD	0x07
#घोषणा TVP3026_CURCTRL		0x09
#घोषणा TVP3026_X_DATAREG	0x0A
#घोषणा TVP3026_CURRAMDATA	0x0B
#घोषणा TVP3026_CURPOSXL	0x0C
#घोषणा TVP3026_CURPOSXH	0x0D
#घोषणा TVP3026_CURPOSYL	0x0E
#घोषणा TVP3026_CURPOSYH	0x0F

#घोषणा TVP3026_XSILICONREV	0x01
#घोषणा TVP3026_XCURCTRL	0x06
#घोषणा     TVP3026_XCURCTRL_DIS	0x00	/* transparent, transparent, transparent, transparent */
#घोषणा     TVP3026_XCURCTRL_3COLOR	0x01	/* transparent, 0, 1, 2 */
#घोषणा     TVP3026_XCURCTRL_XGA	0x02	/* 0, 1, transparent, complement */
#घोषणा     TVP3026_XCURCTRL_XWIN	0x03	/* transparent, transparent, 0, 1 */
#घोषणा     TVP3026_XCURCTRL_BLANK2048	0x00
#घोषणा     TVP3026_XCURCTRL_BLANK4096	0x10
#घोषणा     TVP3026_XCURCTRL_INTERLACED	0x20
#घोषणा     TVP3026_XCURCTRL_ODD	0x00 /* ext.संकेत ODD/\EVEN */
#घोषणा     TVP3026_XCURCTRL_EVEN	0x40 /* ext.संकेत EVEN/\ODD */
#घोषणा     TVP3026_XCURCTRL_INसूचीECT	0x00
#घोषणा     TVP3026_XCURCTRL_सूचीECT	0x80
#घोषणा TVP3026_XLATCHCTRL	0x0F
#घोषणा     TVP3026_XLATCHCTRL_1_1	0x06
#घोषणा     TVP3026_XLATCHCTRL_2_1	0x07
#घोषणा     TVP3026_XLATCHCTRL_4_1	0x06
#घोषणा     TVP3026_XLATCHCTRL_8_1	0x06
#घोषणा     TVP3026_XLATCHCTRL_16_1	0x06
#घोषणा     TVP3026A_XLATCHCTRL_4_3	0x06	/* ??? करो not understand... but it works... !!! */
#घोषणा     TVP3026A_XLATCHCTRL_8_3	0x07
#घोषणा     TVP3026B_XLATCHCTRL_4_3	0x08
#घोषणा     TVP3026B_XLATCHCTRL_8_3	0x06	/* ??? करो not understand... but it works... !!! */
#घोषणा TVP3026_XTRUECOLORCTRL	0x18
#घोषणा     TVP3026_XTRUECOLORCTRL_VRAM_SHIFT_ACCEL	0x00
#घोषणा     TVP3026_XTRUECOLORCTRL_VRAM_SHIFT_TVP	0x20
#घोषणा     TVP3026_XTRUECOLORCTRL_PSEUDOCOLOR		0x80
#घोषणा     TVP3026_XTRUECOLORCTRL_TRUECOLOR		0x40 /* paletized */
#घोषणा     TVP3026_XTRUECOLORCTRL_सूचीECTCOLOR		0x00
#घोषणा     TVP3026_XTRUECOLORCTRL_24_ALTERNATE		0x08 /* 5:4/5:2 instead of 4:3/8:3 */
#घोषणा     TVP3026_XTRUECOLORCTRL_RGB_888		0x16 /* 4:3/8:3 (or 5:4/5:2) */
#घोषणा	    TVP3026_XTRUECOLORCTRL_BGR_888		0x17
#घोषणा     TVP3026_XTRUECOLORCTRL_ORGB_8888		0x06
#घोषणा     TVP3026_XTRUECOLORCTRL_BGRO_8888		0x07
#घोषणा     TVP3026_XTRUECOLORCTRL_RGB_565		0x05
#घोषणा     TVP3026_XTRUECOLORCTRL_ORGB_1555		0x04
#घोषणा     TVP3026_XTRUECOLORCTRL_RGB_664		0x03
#घोषणा     TVP3026_XTRUECOLORCTRL_RGBO_4444		0x01
#घोषणा TVP3026_XMUXCTRL	0x19
#घोषणा     TVP3026_XMUXCTRL_MEMORY_8BIT			0x01 /* - */
#घोषणा     TVP3026_XMUXCTRL_MEMORY_16BIT			0x02 /* - */
#घोषणा     TVP3026_XMUXCTRL_MEMORY_32BIT			0x03 /* 2MB RAM, 512K * 4 */
#घोषणा     TVP3026_XMUXCTRL_MEMORY_64BIT			0x04 /* >2MB RAM, 512K * 8 & more */
#घोषणा     TVP3026_XMUXCTRL_PIXEL_4BIT				0x40 /* L0,H0,L1,H1... */
#घोषणा     TVP3026_XMUXCTRL_PIXEL_4BIT_SWAPPED			0x60 /* H0,L0,H1,L1... */
#घोषणा     TVP3026_XMUXCTRL_PIXEL_8BIT				0x48
#घोषणा     TVP3026_XMUXCTRL_PIXEL_16BIT			0x50
#घोषणा     TVP3026_XMUXCTRL_PIXEL_32BIT			0x58
#घोषणा     TVP3026_XMUXCTRL_VGA				0x98 /* VGA MEMORY, 8BIT PIXEL */
#घोषणा TVP3026_XCLKCTRL	0x1A
#घोषणा     TVP3026_XCLKCTRL_DIV1	0x00
#घोषणा     TVP3026_XCLKCTRL_DIV2	0x10
#घोषणा     TVP3026_XCLKCTRL_DIV4	0x20
#घोषणा     TVP3026_XCLKCTRL_DIV8	0x30
#घोषणा     TVP3026_XCLKCTRL_DIV16	0x40
#घोषणा     TVP3026_XCLKCTRL_DIV32	0x50
#घोषणा     TVP3026_XCLKCTRL_DIV64	0x60
#घोषणा     TVP3026_XCLKCTRL_CLKSTOPPED	0x70
#घोषणा     TVP3026_XCLKCTRL_SRC_CLK0	0x00
#घोषणा     TVP3026_XCLKCTRL_SRC_CLK1   0x01
#घोषणा     TVP3026_XCLKCTRL_SRC_CLK2	0x02	/* CLK2 is TTL source*/
#घोषणा     TVP3026_XCLKCTRL_SRC_NCLK2	0x03	/* not CLK2 is TTL source */
#घोषणा     TVP3026_XCLKCTRL_SRC_ECLK2	0x04	/* CLK2 and not CLK2 is ECL source */
#घोषणा     TVP3026_XCLKCTRL_SRC_PLL	0x05
#घोषणा     TVP3026_XCLKCTRL_SRC_DIS	0x06	/* disable & घातeroff पूर्णांकernal घड़ी */
#घोषणा     TVP3026_XCLKCTRL_SRC_CLK0VGA 0x07
#घोषणा TVP3026_XPALETTEPAGE	0x1C
#घोषणा TVP3026_XGENCTRL	0x1D
#घोषणा     TVP3026_XGENCTRL_HSYNC_POS	0x00
#घोषणा     TVP3026_XGENCTRL_HSYNC_NEG	0x01
#घोषणा     TVP3026_XGENCTRL_VSYNC_POS	0x00
#घोषणा     TVP3026_XGENCTRL_VSYNC_NEG	0x02
#घोषणा     TVP3026_XGENCTRL_LITTLE_ENDIAN 0x00
#घोषणा     TVP3026_XGENCTRL_BIG_ENDIAN    0x08
#घोषणा     TVP3026_XGENCTRL_BLACK_0IRE		0x00
#घोषणा     TVP3026_XGENCTRL_BLACK_75IRE	0x10
#घोषणा     TVP3026_XGENCTRL_NO_SYNC_ON_GREEN	0x00
#घोषणा     TVP3026_XGENCTRL_SYNC_ON_GREEN	0x20
#घोषणा     TVP3026_XGENCTRL_OVERSCAN_DIS	0x00
#घोषणा     TVP3026_XGENCTRL_OVERSCAN_EN	0x40
#घोषणा TVP3026_XMISCCTRL	0x1E
#घोषणा     TVP3026_XMISCCTRL_DAC_PUP	0x00
#घोषणा     TVP3026_XMISCCTRL_DAC_PDOWN	0x01
#घोषणा     TVP3026_XMISCCTRL_DAC_EXT	0x00 /* or 8, bit 3 is ignored */
#घोषणा     TVP3026_XMISCCTRL_DAC_6BIT	0x04
#घोषणा     TVP3026_XMISCCTRL_DAC_8BIT	0x0C
#घोषणा     TVP3026_XMISCCTRL_PSEL_DIS	0x00
#घोषणा     TVP3026_XMISCCTRL_PSEL_EN	0x10
#घोषणा     TVP3026_XMISCCTRL_PSEL_LOW	0x00 /* PSEL high selects directcolor */
#घोषणा     TVP3026_XMISCCTRL_PSEL_HIGH 0x20 /* PSEL high selects truecolor or pseuकरोcolor */
#घोषणा TVP3026_XGENIOCTRL	0x2A
#घोषणा TVP3026_XGENIODATA	0x2B
#घोषणा TVP3026_XPLLADDR	0x2C
#घोषणा     TVP3026_XPLLADDR_X(LOOP,MCLK,PIX) (((LOOP)<<4) | ((MCLK)<<2) | (PIX))
#घोषणा     TVP3026_XPLLDATA_N		0x00
#घोषणा     TVP3026_XPLLDATA_M		0x01
#घोषणा     TVP3026_XPLLDATA_P		0x02
#घोषणा     TVP3026_XPLLDATA_STAT	0x03
#घोषणा TVP3026_XPIXPLLDATA	0x2D
#घोषणा TVP3026_XMEMPLLDATA	0x2E
#घोषणा TVP3026_XLOOPPLLDATA	0x2F
#घोषणा TVP3026_XCOLKEYOVRMIN	0x30
#घोषणा TVP3026_XCOLKEYOVRMAX	0x31
#घोषणा TVP3026_XCOLKEYREDMIN	0x32
#घोषणा TVP3026_XCOLKEYREDMAX	0x33
#घोषणा TVP3026_XCOLKEYGREENMIN	0x34
#घोषणा TVP3026_XCOLKEYGREENMAX	0x35
#घोषणा TVP3026_XCOLKEYBLUEMIN	0x36
#घोषणा TVP3026_XCOLKEYBLUEMAX	0x37
#घोषणा TVP3026_XCOLKEYCTRL	0x38
#घोषणा     TVP3026_XCOLKEYCTRL_OVR_EN	0x01
#घोषणा     TVP3026_XCOLKEYCTRL_RED_EN	0x02
#घोषणा     TVP3026_XCOLKEYCTRL_GREEN_EN 0x04
#घोषणा     TVP3026_XCOLKEYCTRL_BLUE_EN	0x08
#घोषणा     TVP3026_XCOLKEYCTRL_NEGATE	0x10
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM1	0x00
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM2	0x20
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM4	0x40
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM8	0x60
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM16	0x80
#घोषणा     TVP3026_XCOLKEYCTRL_ZOOM32	0xA0
#घोषणा TVP3026_XMEMPLLCTRL	0x39
#घोषणा     TVP3026_XMEMPLLCTRL_DIV(X)	(((X)-1)>>1)	/* 2,4,6,8,10,12,14,16, भागision applied to LOOP PLL after भागide by 2^P */
#घोषणा     TVP3026_XMEMPLLCTRL_STROBEMKC4	0x08
#घोषणा     TVP3026_XMEMPLLCTRL_MCLK_DOTCLOCK	0x00	/* MKC4 */
#घोषणा     TVP3026_XMEMPLLCTRL_MCLK_MCLKPLL	0x10	/* MKC4 */
#घोषणा     TVP3026_XMEMPLLCTRL_RCLK_PIXPLL	0x00
#घोषणा     TVP3026_XMEMPLLCTRL_RCLK_LOOPPLL	0x20
#घोषणा     TVP3026_XMEMPLLCTRL_RCLK_DOTDIVN	0x40	/* करोt घड़ी भागided by loop pclk N prescaler */
#घोषणा TVP3026_XSENSETEST	0x3A
#घोषणा TVP3026_XTESTMODEDATA	0x3B
#घोषणा TVP3026_XCRCREML	0x3C
#घोषणा TVP3026_XCRCREMH	0x3D
#घोषणा TVP3026_XCRCBITSEL	0x3E
#घोषणा TVP3026_XID		0x3F

अटल स्थिर अचिन्हित अक्षर DACseq[] =
अणु TVP3026_XLATCHCTRL, TVP3026_XTRUECOLORCTRL,
  TVP3026_XMUXCTRL, TVP3026_XCLKCTRL,
  TVP3026_XPALETTEPAGE,
  TVP3026_XGENCTRL,
  TVP3026_XMISCCTRL,
  TVP3026_XGENIOCTRL,
  TVP3026_XGENIODATA,
  TVP3026_XCOLKEYOVRMIN, TVP3026_XCOLKEYOVRMAX, TVP3026_XCOLKEYREDMIN, TVP3026_XCOLKEYREDMAX,
  TVP3026_XCOLKEYGREENMIN, TVP3026_XCOLKEYGREENMAX, TVP3026_XCOLKEYBLUEMIN, TVP3026_XCOLKEYBLUEMAX,
  TVP3026_XCOLKEYCTRL,
  TVP3026_XMEMPLLCTRL, TVP3026_XSENSETEST, TVP3026_XCURCTRL पूर्ण;

#घोषणा POS3026_XLATCHCTRL	0
#घोषणा POS3026_XTRUECOLORCTRL	1
#घोषणा POS3026_XMUXCTRL	2
#घोषणा POS3026_XCLKCTRL	3
#घोषणा POS3026_XGENCTRL	5
#घोषणा POS3026_XMISCCTRL	6
#घोषणा POS3026_XMEMPLLCTRL	18
#घोषणा POS3026_XCURCTRL	20

अटल स्थिर अचिन्हित अक्षर MGADACbpp32[] =
अणु TVP3026_XLATCHCTRL_2_1, TVP3026_XTRUECOLORCTRL_सूचीECTCOLOR | TVP3026_XTRUECOLORCTRL_ORGB_8888,
  0x00, TVP3026_XCLKCTRL_DIV1 | TVP3026_XCLKCTRL_SRC_PLL,
  0x00,
  TVP3026_XGENCTRL_HSYNC_POS | TVP3026_XGENCTRL_VSYNC_POS | TVP3026_XGENCTRL_LITTLE_ENDIAN | TVP3026_XGENCTRL_BLACK_0IRE | TVP3026_XGENCTRL_NO_SYNC_ON_GREEN | TVP3026_XGENCTRL_OVERSCAN_DIS,
  TVP3026_XMISCCTRL_DAC_PUP | TVP3026_XMISCCTRL_DAC_8BIT | TVP3026_XMISCCTRL_PSEL_DIS | TVP3026_XMISCCTRL_PSEL_HIGH,
  0x00,
  0x1E,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  TVP3026_XCOLKEYCTRL_ZOOM1,
  0x00, 0x00, TVP3026_XCURCTRL_DIS पूर्ण;

अटल पूर्णांक Ti3026_calcघड़ी(स्थिर काष्ठा matrox_fb_info *minfo,
			    अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax, पूर्णांक *in,
			    पूर्णांक *feed, पूर्णांक *post)
अणु
	अचिन्हित पूर्णांक fvco;
	अचिन्हित पूर्णांक lin, lfeed, lpost;

	DBG(__func__)

	fvco = PLL_calcघड़ी(minfo, freq, fmax, &lin, &lfeed, &lpost);
	fvco >>= (*post = lpost);
	*in = 64 - lin;
	*feed = 64 - lfeed;
	वापस fvco;
पूर्ण

अटल पूर्णांक Ti3026_setpclk(काष्ठा matrox_fb_info *minfo, पूर्णांक clk)
अणु
	अचिन्हित पूर्णांक f_pll;
	अचिन्हित पूर्णांक pixfeed, pixin, pixpost;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	f_pll = Ti3026_calcघड़ी(minfo, clk, minfo->max_pixel_घड़ी, &pixin, &pixfeed, &pixpost);

	hw->DACclk[0] = pixin | 0xC0;
	hw->DACclk[1] = pixfeed;
	hw->DACclk[2] = pixpost | 0xB0;

	अणु
		अचिन्हित पूर्णांक loopfeed, loopin, looppost, loopभाग, z;
		अचिन्हित पूर्णांक Bpp;

		Bpp = minfo->curr.final_bppShअगरt;

		अगर (minfo->fbcon.var.bits_per_pixel == 24) अणु
			loopfeed = 3;		/* set lm to any possible value */
			loopin = 3 * 32 / Bpp;
		पूर्ण अन्यथा अणु
			loopfeed = 4;
			loopin = 4 * 32 / Bpp;
		पूर्ण
		z = (110000 * loopin) / (f_pll * loopfeed);
		loopभाग = 0; /* भाग 2 */
		अगर (z < 2)
			looppost = 0;
		अन्यथा अगर (z < 4)
			looppost = 1;
		अन्यथा अगर (z < 8)
			looppost = 2;
		अन्यथा अणु
			looppost = 3;
			loopभाग = z/16;
		पूर्ण
		अगर (minfo->fbcon.var.bits_per_pixel == 24) अणु
			hw->DACclk[3] = ((65 - loopin) & 0x3F) | 0xC0;
			hw->DACclk[4] = (65 - loopfeed) | 0x80;
			अगर (minfo->accel.ramdac_rev > 0x20) अणु
				अगर (isInterleave(minfo))
					hw->DACreg[POS3026_XLATCHCTRL] = TVP3026B_XLATCHCTRL_8_3;
				अन्यथा अणु
					hw->DACclk[4] &= ~0xC0;
					hw->DACreg[POS3026_XLATCHCTRL] = TVP3026B_XLATCHCTRL_4_3;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (isInterleave(minfo))
					;	/* शेष... */
				अन्यथा अणु
					hw->DACclk[4] ^= 0xC0;	/* change from 0x80 to 0x40 */
					hw->DACreg[POS3026_XLATCHCTRL] = TVP3026A_XLATCHCTRL_4_3;
				पूर्ण
			पूर्ण
			hw->DACclk[5] = looppost | 0xF8;
			अगर (minfo->devflags.mga_24bpp_fix)
				hw->DACclk[5] ^= 0x40;
		पूर्ण अन्यथा अणु
			hw->DACclk[3] = ((65 - loopin) & 0x3F) | 0xC0;
			hw->DACclk[4] = 65 - loopfeed;
			hw->DACclk[5] = looppost | 0xF0;
		पूर्ण
		hw->DACreg[POS3026_XMEMPLLCTRL] = loopभाग | TVP3026_XMEMPLLCTRL_MCLK_MCLKPLL | TVP3026_XMEMPLLCTRL_RCLK_LOOPPLL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक Ti3026_init(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	u_पूर्णांक8_t muxctrl = isInterleave(minfo) ? TVP3026_XMUXCTRL_MEMORY_64BIT : TVP3026_XMUXCTRL_MEMORY_32BIT;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	स_नकल(hw->DACreg, MGADACbpp32, माप(MGADACbpp32));
	चयन (minfo->fbcon.var.bits_per_pixel) अणु
		हाल 4:	hw->DACreg[POS3026_XLATCHCTRL] = TVP3026_XLATCHCTRL_16_1;	/* or _8_1, they are same */
			hw->DACreg[POS3026_XTRUECOLORCTRL] = TVP3026_XTRUECOLORCTRL_PSEUDOCOLOR;
			hw->DACreg[POS3026_XMUXCTRL] = muxctrl | TVP3026_XMUXCTRL_PIXEL_4BIT;
			hw->DACreg[POS3026_XCLKCTRL] = TVP3026_XCLKCTRL_SRC_PLL | TVP3026_XCLKCTRL_DIV8;
			hw->DACreg[POS3026_XMISCCTRL] = TVP3026_XMISCCTRL_DAC_PUP | TVP3026_XMISCCTRL_DAC_8BIT | TVP3026_XMISCCTRL_PSEL_DIS | TVP3026_XMISCCTRL_PSEL_LOW;
			अवरोध;
		हाल 8: hw->DACreg[POS3026_XLATCHCTRL] = TVP3026_XLATCHCTRL_8_1;	/* or _4_1, they are same */
			hw->DACreg[POS3026_XTRUECOLORCTRL] = TVP3026_XTRUECOLORCTRL_PSEUDOCOLOR;
			hw->DACreg[POS3026_XMUXCTRL] = muxctrl | TVP3026_XMUXCTRL_PIXEL_8BIT;
			hw->DACreg[POS3026_XCLKCTRL] = TVP3026_XCLKCTRL_SRC_PLL | TVP3026_XCLKCTRL_DIV4;
			hw->DACreg[POS3026_XMISCCTRL] = TVP3026_XMISCCTRL_DAC_PUP | TVP3026_XMISCCTRL_DAC_8BIT | TVP3026_XMISCCTRL_PSEL_DIS | TVP3026_XMISCCTRL_PSEL_LOW;
			अवरोध;
		हाल 16:
			/* XLATCHCTRL should be _4_1 / _2_1... Why is not? (_2_1 is used every समय) */
			hw->DACreg[POS3026_XTRUECOLORCTRL] = (minfo->fbcon.var.green.length == 5) ? (TVP3026_XTRUECOLORCTRL_सूचीECTCOLOR | TVP3026_XTRUECOLORCTRL_ORGB_1555) : (TVP3026_XTRUECOLORCTRL_सूचीECTCOLOR | TVP3026_XTRUECOLORCTRL_RGB_565);
			hw->DACreg[POS3026_XMUXCTRL] = muxctrl | TVP3026_XMUXCTRL_PIXEL_16BIT;
			hw->DACreg[POS3026_XCLKCTRL] = TVP3026_XCLKCTRL_SRC_PLL | TVP3026_XCLKCTRL_DIV2;
			अवरोध;
		हाल 24:
			/* XLATCHCTRL is: क्रम (A) use _4_3 (?_8_3 is same? TBD), क्रम (B) it is set in setpclk */
			hw->DACreg[POS3026_XTRUECOLORCTRL] = TVP3026_XTRUECOLORCTRL_सूचीECTCOLOR | TVP3026_XTRUECOLORCTRL_RGB_888;
			hw->DACreg[POS3026_XMUXCTRL] = muxctrl | TVP3026_XMUXCTRL_PIXEL_32BIT;
			hw->DACreg[POS3026_XCLKCTRL] = TVP3026_XCLKCTRL_SRC_PLL | TVP3026_XCLKCTRL_DIV4;
			अवरोध;
		हाल 32:
			/* XLATCHCTRL should be _2_1 / _1_1... Why is not? (_2_1 is used every समय) */
			hw->DACreg[POS3026_XMUXCTRL] = muxctrl | TVP3026_XMUXCTRL_PIXEL_32BIT;
			अवरोध;
		शेष:
			वापस 1;	/* TODO: failed */
	पूर्ण
	अगर (matroxfb_vgaHWinit(minfo, m)) वापस 1;

	/* set SYNC */
	hw->MiscOutReg = 0xCB;
	अगर (m->sync & FB_SYNC_HOR_HIGH_ACT)
		hw->DACreg[POS3026_XGENCTRL] |= TVP3026_XGENCTRL_HSYNC_NEG;
	अगर (m->sync & FB_SYNC_VERT_HIGH_ACT)
		hw->DACreg[POS3026_XGENCTRL] |= TVP3026_XGENCTRL_VSYNC_NEG;
	अगर (m->sync & FB_SYNC_ON_GREEN)
		hw->DACreg[POS3026_XGENCTRL] |= TVP3026_XGENCTRL_SYNC_ON_GREEN;

	/* set DELAY */
	अगर (minfo->video.len < 0x400000)
		hw->CRTCEXT[3] |= 0x08;
	अन्यथा अगर (minfo->video.len > 0x400000)
		hw->CRTCEXT[3] |= 0x10;

	/* set HWCURSOR */
	अगर (m->पूर्णांकerlaced) अणु
		hw->DACreg[POS3026_XCURCTRL] |= TVP3026_XCURCTRL_INTERLACED;
	पूर्ण
	अगर (m->HTotal >= 1536)
		hw->DACreg[POS3026_XCURCTRL] |= TVP3026_XCURCTRL_BLANK4096;

	/* set पूर्णांकerleaving */
	hw->MXoptionReg &= ~0x00001000;
	अगर (isInterleave(minfo)) hw->MXoptionReg |= 0x00001000;

	/* set DAC */
	Ti3026_setpclk(minfo, m->pixघड़ी);
	वापस 0;
पूर्ण

अटल व्योम ti3026_setMCLK(काष्ठा matrox_fb_info *minfo, पूर्णांक fout)
अणु
	अचिन्हित पूर्णांक f_pll;
	अचिन्हित पूर्णांक pclk_m, pclk_n, pclk_p;
	अचिन्हित पूर्णांक mclk_m, mclk_n, mclk_p;
	अचिन्हित पूर्णांक rfhcnt, mclk_ctl;
	पूर्णांक पंचांगout;

	DBG(__func__)

	f_pll = Ti3026_calcघड़ी(minfo, fout, minfo->max_pixel_घड़ी, &mclk_n, &mclk_m, &mclk_p);

	/* save pclk */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFC);
	pclk_n = inTi3026(minfo, TVP3026_XPIXPLLDATA);
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFD);
	pclk_m = inTi3026(minfo, TVP3026_XPIXPLLDATA);
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFE);
	pclk_p = inTi3026(minfo, TVP3026_XPIXPLLDATA);

	/* stop pclk */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFE);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, 0x00);

	/* set pclk to new mclk */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFC);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, mclk_n | 0xC0);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, mclk_m);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, mclk_p | 0xB0);

	/* रुको क्रम PLL to lock */
	क्रम (पंचांगout = 500000; पंचांगout; पंचांगout--) अणु
		अगर (inTi3026(minfo, TVP3026_XPIXPLLDATA) & 0x40)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (!पंचांगout)
		prपूर्णांकk(KERN_ERR "matroxfb: Temporary pixel PLL not locked after 5 secs\n");

	/* output pclk on mclk pin */
	mclk_ctl = inTi3026(minfo, TVP3026_XMEMPLLCTRL);
	outTi3026(minfo, TVP3026_XMEMPLLCTRL, mclk_ctl & 0xE7);
	outTi3026(minfo, TVP3026_XMEMPLLCTRL, (mclk_ctl & 0xE7) | TVP3026_XMEMPLLCTRL_STROBEMKC4);

	/* stop MCLK */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFB);
	outTi3026(minfo, TVP3026_XMEMPLLDATA, 0x00);

	/* set mclk to new freq */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xF3);
	outTi3026(minfo, TVP3026_XMEMPLLDATA, mclk_n | 0xC0);
	outTi3026(minfo, TVP3026_XMEMPLLDATA, mclk_m);
	outTi3026(minfo, TVP3026_XMEMPLLDATA, mclk_p | 0xB0);

	/* रुको क्रम PLL to lock */
	क्रम (पंचांगout = 500000; पंचांगout; पंचांगout--) अणु
		अगर (inTi3026(minfo, TVP3026_XMEMPLLDATA) & 0x40)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (!पंचांगout)
		prपूर्णांकk(KERN_ERR "matroxfb: Memory PLL not locked after 5 secs\n");

	f_pll = f_pll * 333 / (10000 << mclk_p);
	अगर (isMilleniumII(minfo)) अणु
		rfhcnt = (f_pll - 128) / 256;
		अगर (rfhcnt > 15)
			rfhcnt = 15;
	पूर्ण अन्यथा अणु
		rfhcnt = (f_pll - 64) / 128;
		अगर (rfhcnt > 15)
			rfhcnt = 0;
	पूर्ण
	minfo->hw.MXoptionReg = (minfo->hw.MXoptionReg & ~0x000F0000) | (rfhcnt << 16);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);

	/* output MCLK to MCLK pin */
	outTi3026(minfo, TVP3026_XMEMPLLCTRL, (mclk_ctl & 0xE7) | TVP3026_XMEMPLLCTRL_MCLK_MCLKPLL);
	outTi3026(minfo, TVP3026_XMEMPLLCTRL, (mclk_ctl       ) | TVP3026_XMEMPLLCTRL_MCLK_MCLKPLL | TVP3026_XMEMPLLCTRL_STROBEMKC4);

	/* stop PCLK */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFE);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, 0x00);

	/* restore pclk */
	outTi3026(minfo, TVP3026_XPLLADDR, 0xFC);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, pclk_n);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, pclk_m);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, pclk_p);

	/* रुको क्रम PLL to lock */
	क्रम (पंचांगout = 500000; पंचांगout; पंचांगout--) अणु
		अगर (inTi3026(minfo, TVP3026_XPIXPLLDATA) & 0x40)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (!पंचांगout)
		prपूर्णांकk(KERN_ERR "matroxfb: Pixel PLL not locked after 5 secs\n");
पूर्ण

अटल व्योम ti3026_ramdac_init(काष्ठा matrox_fb_info *minfo)
अणु
	DBG(__func__)

	minfo->features.pll.vco_freq_min = 110000;
	minfo->features.pll.ref_freq	 = 114545;
	minfo->features.pll.feed_भाग_min = 2;
	minfo->features.pll.feed_भाग_max = 24;
	minfo->features.pll.in_भाग_min	 = 2;
	minfo->features.pll.in_भाग_max	 = 63;
	minfo->features.pll.post_shअगरt_max = 3;
	अगर (minfo->devflags.noinit)
		वापस;
	ti3026_setMCLK(minfo, 60000);
पूर्ण

अटल व्योम Ti3026_restore(काष्ठा matrox_fb_info *minfo)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर progdac[6];
	काष्ठा matrox_hw_state *hw = &minfo->hw;
	CRITFLAGS

	DBG(__func__)

#अगर_घोषित DEBUG
	dprपूर्णांकk(KERN_INFO "EXTVGA regs: ");
	क्रम (i = 0; i < 6; i++)
		dprपूर्णांकk("%02X:", hw->CRTCEXT[i]);
	dprपूर्णांकk("\n");
#पूर्ण_अगर

	CRITBEGIN

	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);

	CRITEND

	matroxfb_vgaHWrestore(minfo);

	CRITBEGIN

	minfo->crtc1.panpos = -1;
	क्रम (i = 0; i < 6; i++)
		mga_setr(M_EXTVGA_INDEX, i, hw->CRTCEXT[i]);

	क्रम (i = 0; i < 21; i++) अणु
		outTi3026(minfo, DACseq[i], hw->DACreg[i]);
	पूर्ण

	outTi3026(minfo, TVP3026_XPLLADDR, 0x00);
	progdac[0] = inTi3026(minfo, TVP3026_XPIXPLLDATA);
	progdac[3] = inTi3026(minfo, TVP3026_XLOOPPLLDATA);
	outTi3026(minfo, TVP3026_XPLLADDR, 0x15);
	progdac[1] = inTi3026(minfo, TVP3026_XPIXPLLDATA);
	progdac[4] = inTi3026(minfo, TVP3026_XLOOPPLLDATA);
	outTi3026(minfo, TVP3026_XPLLADDR, 0x2A);
	progdac[2] = inTi3026(minfo, TVP3026_XPIXPLLDATA);
	progdac[5] = inTi3026(minfo, TVP3026_XLOOPPLLDATA);

	CRITEND
	अगर (स_भेद(hw->DACclk, progdac, 6)) अणु
		/* agrhh... setting up PLL is very slow on Millennium... */
		/* Mystique PLL is locked in few ms, but Millennium PLL lock takes about 0.15 s... */
		/* Maybe even we should call schedule() ? */

		CRITBEGIN
		outTi3026(minfo, TVP3026_XCLKCTRL, hw->DACreg[POS3026_XCLKCTRL]);
		outTi3026(minfo, TVP3026_XPLLADDR, 0x2A);
		outTi3026(minfo, TVP3026_XLOOPPLLDATA, 0);
		outTi3026(minfo, TVP3026_XPIXPLLDATA, 0);

		outTi3026(minfo, TVP3026_XPLLADDR, 0x00);
		क्रम (i = 0; i < 3; i++)
			outTi3026(minfo, TVP3026_XPIXPLLDATA, hw->DACclk[i]);
		/* रुको क्रम PLL only अगर PLL घड़ी requested (always क्रम PowerMode, never क्रम VGA) */
		अगर (hw->MiscOutReg & 0x08) अणु
			पूर्णांक पंचांगout;
			outTi3026(minfo, TVP3026_XPLLADDR, 0x3F);
			क्रम (पंचांगout = 500000; पंचांगout; --पंचांगout) अणु
				अगर (inTi3026(minfo, TVP3026_XPIXPLLDATA) & 0x40)
					अवरोध;
				udelay(10);
			पूर्ण

			CRITEND

			अगर (!पंचांगout)
				prपूर्णांकk(KERN_ERR "matroxfb: Pixel PLL not locked after 5 secs\n");
			अन्यथा
				dprपूर्णांकk(KERN_INFO "PixelPLL: %d\n", 500000-पंचांगout);
			CRITBEGIN
		पूर्ण
		outTi3026(minfo, TVP3026_XMEMPLLCTRL, hw->DACreg[POS3026_XMEMPLLCTRL]);
		outTi3026(minfo, TVP3026_XPLLADDR, 0x00);
		क्रम (i = 3; i < 6; i++)
			outTi3026(minfo, TVP3026_XLOOPPLLDATA, hw->DACclk[i]);
		CRITEND
		अगर ((hw->MiscOutReg & 0x08) && ((hw->DACclk[5] & 0x80) == 0x80)) अणु
			पूर्णांक पंचांगout;

			CRITBEGIN
			outTi3026(minfo, TVP3026_XPLLADDR, 0x3F);
			क्रम (पंचांगout = 500000; पंचांगout; --पंचांगout) अणु
				अगर (inTi3026(minfo, TVP3026_XLOOPPLLDATA) & 0x40)
					अवरोध;
				udelay(10);
			पूर्ण
			CRITEND
			अगर (!पंचांगout)
				prपूर्णांकk(KERN_ERR "matroxfb: Loop PLL not locked after 5 secs\n");
			अन्यथा
				dprपूर्णांकk(KERN_INFO "LoopPLL: %d\n", 500000-पंचांगout);
		पूर्ण
	पूर्ण

#अगर_घोषित DEBUG
	dprपूर्णांकk(KERN_DEBUG "3026DACregs ");
	क्रम (i = 0; i < 21; i++) अणु
		dprपूर्णांकk("R%02X=%02X ", DACseq[i], hw->DACreg[i]);
		अगर ((i & 0x7) == 0x7) dprपूर्णांकk(KERN_DEBUG "continuing... ");
	पूर्ण
	dprपूर्णांकk(KERN_DEBUG "DACclk ");
	क्रम (i = 0; i < 6; i++)
		dprपूर्णांकk("C%02X=%02X ", i, hw->DACclk[i]);
	dprपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण

अटल व्योम Ti3026_reset(काष्ठा matrox_fb_info *minfo)
अणु
	DBG(__func__)

	ti3026_ramdac_init(minfo);
पूर्ण

अटल काष्ठा matrox_altout ti3026_output = अणु
	.name	 = "Primary output",
पूर्ण;

अटल पूर्णांक Ti3026_preinit(काष्ठा matrox_fb_info *minfo)
अणु
	अटल स्थिर पूर्णांक vxres_mill2[] = अणु 512,        640, 768,  800,  832,  960,
					  1024, 1152, 1280,      1600, 1664, 1920,
					  2048, 0पूर्ण;
	अटल स्थिर पूर्णांक vxres_mill1[] = अणु             640, 768,  800,        960,
					  1024, 1152, 1280,      1600,       1920,
					  2048, 0पूर्ण;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	minfo->millenium = 1;
	minfo->milleniumII = (minfo->pcidev->device != PCI_DEVICE_ID_MATROX_MIL);
	minfo->capable.cfb4 = 1;
	minfo->capable.text = 1; /* isMilleniumII(minfo); */
	minfo->capable.vxres = isMilleniumII(minfo) ? vxres_mill2 : vxres_mill1;

	minfo->outमाला_दो[0].data = minfo;
	minfo->outमाला_दो[0].output = &ti3026_output;
	minfo->outमाला_दो[0].src = minfo->outमाला_दो[0].शेष_src;
	minfo->outमाला_दो[0].mode = MATROXFB_OUTPUT_MODE_MONITOR;

	अगर (minfo->devflags.noinit)
		वापस 0;
	/* preserve VGA I/O, BIOS and PPC */
	hw->MXoptionReg &= 0xC0000100;
	hw->MXoptionReg |= 0x002C0000;
	अगर (minfo->devflags.novga)
		hw->MXoptionReg &= ~0x00000100;
	अगर (minfo->devflags.nobios)
		hw->MXoptionReg &= ~0x40000000;
	अगर (minfo->devflags.nopciretry)
		hw->MXoptionReg |=  0x20000000;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);

	minfo->accel.ramdac_rev = inTi3026(minfo, TVP3026_XSILICONREV);

	outTi3026(minfo, TVP3026_XCLKCTRL, TVP3026_XCLKCTRL_SRC_CLK0VGA | TVP3026_XCLKCTRL_CLKSTOPPED);
	outTi3026(minfo, TVP3026_XTRUECOLORCTRL, TVP3026_XTRUECOLORCTRL_PSEUDOCOLOR);
	outTi3026(minfo, TVP3026_XMUXCTRL, TVP3026_XMUXCTRL_VGA);

	outTi3026(minfo, TVP3026_XPLLADDR, 0x2A);
	outTi3026(minfo, TVP3026_XLOOPPLLDATA, 0x00);
	outTi3026(minfo, TVP3026_XPIXPLLDATA, 0x00);

	mga_outb(M_MISC_REG, 0x67);

	outTi3026(minfo, TVP3026_XMEMPLLCTRL, TVP3026_XMEMPLLCTRL_STROBEMKC4 | TVP3026_XMEMPLLCTRL_MCLK_MCLKPLL);

	mga_outl(M_RESET, 1);
	udelay(250);
	mga_outl(M_RESET, 0);
	udelay(250);
	mga_outl(M_MACCESS, 0x00008000);
	udelay(10);
	वापस 0;
पूर्ण

काष्ठा matrox_चयन matrox_millennium = अणु
	.preinit	= Ti3026_preinit,
	.reset		= Ti3026_reset,
	.init		= Ti3026_init,
	.restore	= Ti3026_restore
पूर्ण;
EXPORT_SYMBOL(matrox_millennium);
#पूर्ण_अगर
MODULE_LICENSE("GPL");
