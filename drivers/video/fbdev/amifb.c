<शैली गुरु>
/*
 * linux/drivers/video/amअगरb.c -- Amiga builtin chipset frame buffer device
 *
 *    Copyright (C) 1995-2003 Geert Uytterhoeven
 *
 *          with work by Roman Zippel
 *
 *
 * This file is based on the Atari frame buffer device (atafb.c):
 *
 *    Copyright (C) 1994 Martin Schaller
 *                       Roman Hodek
 *
 *          with work by Andreas Schwab
 *                       Guenther Kelleter
 *
 * and on the original Amiga console driver (amicon.c):
 *
 *    Copyright (C) 1993 Hamish Macकरोnald
 *                       Greg Harp
 *    Copyright (C) 1994 David Carter [carter@compsci.bristol.ac.uk]
 *
 *          with work by William Rucklidge (wjr@cs.cornell.edu)
 *                       Geert Uytterhoeven
 *                       Jes Sorensen (jds@kom.auc.dk)
 *
 *
 * History:
 *
 *   - 24 Jul 96: Copper generates now vblank पूर्णांकerrupt and
 *                VESA Power Saving Protocol is fully implemented
 *   - 14 Jul 96: Rework and hopefully last ECS bugs fixed
 *   -  7 Mar 96: Hardware sprite support by Roman Zippel
 *   - 18 Feb 96: OCS and ECS support by Roman Zippel
 *                Hardware functions completely rewritten
 *   -  2 Dec 95: AGA version by Geert Uytterhoeven
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/setup.h>

#समावेश "c2p.h"


#घोषणा DEBUG

#अगर !defined(CONFIG_FB_AMIGA_OCS) && !defined(CONFIG_FB_AMIGA_ECS) && !defined(CONFIG_FB_AMIGA_AGA)
#घोषणा CONFIG_FB_AMIGA_OCS   /* define at least one fb driver, this will change later */
#पूर्ण_अगर

#अगर !defined(CONFIG_FB_AMIGA_OCS)
#  define IS_OCS (0)
#या_अगर defined(CONFIG_FB_AMIGA_ECS) || defined(CONFIG_FB_AMIGA_AGA)
#  define IS_OCS (chipset == TAG_OCS)
#अन्यथा
#  define CONFIG_FB_AMIGA_OCS_ONLY
#  define IS_OCS (1)
#पूर्ण_अगर

#अगर !defined(CONFIG_FB_AMIGA_ECS)
#  define IS_ECS (0)
#या_अगर defined(CONFIG_FB_AMIGA_OCS) || defined(CONFIG_FB_AMIGA_AGA)
#  define IS_ECS (chipset == TAG_ECS)
#अन्यथा
#  define CONFIG_FB_AMIGA_ECS_ONLY
#  define IS_ECS (1)
#पूर्ण_अगर

#अगर !defined(CONFIG_FB_AMIGA_AGA)
#  define IS_AGA (0)
#या_अगर defined(CONFIG_FB_AMIGA_OCS) || defined(CONFIG_FB_AMIGA_ECS)
#  define IS_AGA (chipset == TAG_AGA)
#अन्यथा
#  define CONFIG_FB_AMIGA_AGA_ONLY
#  define IS_AGA (1)
#पूर्ण_अगर

#अगर_घोषित DEBUG
#  define DPRINTK(fmt, args...)	prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__ , ## args)
#अन्यथा
#  define DPRINTK(fmt, args...)
#पूर्ण_अगर

/*******************************************************************************


   Generic video timings
   ---------------------

   Timings used by the frame buffer पूर्णांकerface:

   +----------+---------------------------------------------+----------+-------+
   |          |                ^                            |          |       |
   |          |                |upper_margin                |          |       |
   |          |                v                            |          |       |
   +----------###############################################----------+-------+
   |          #                ^                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |   left   #                |                            #  right   | hsync |
   |  margin  #                |       xres                 #  margin  |  len  |
   |<-------->#<---------------+--------------------------->#<-------->|<----->|
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |yres                        #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                |                            #          |       |
   |          #                v                            #          |       |
   +----------###############################################----------+-------+
   |          |                ^                            |          |       |
   |          |                |lower_margin                |          |       |
   |          |                v                            |          |       |
   +----------+---------------------------------------------+----------+-------+
   |          |                ^                            |          |       |
   |          |                |vsync_len                   |          |       |
   |          |                v                            |          |       |
   +----------+---------------------------------------------+----------+-------+


   Amiga video timings
   -------------------

   The Amiga native chipsets uses another timing scheme:

      - hsstrt:   Start of horizontal synchronization pulse
      - hsstop:   End of horizontal synchronization pulse
      - htotal:   Last value on the line (i.e. line length = htotal + 1)
      - vsstrt:   Start of vertical synchronization pulse
      - vsstop:   End of vertical synchronization pulse
      - vtotal:   Last line value (i.e. number of lines = vtotal + 1)
      - hcenter:  Start of vertical retrace क्रम पूर्णांकerlace

   You can specअगरy the blanking timings independently. Currently I just set
   them equal to the respective synchronization values:

      - hbstrt:   Start of horizontal blank
      - hbstop:   End of horizontal blank
      - vbstrt:   Start of vertical blank
      - vbstop:   End of vertical blank

   Horizontal values are in color घड़ी cycles (280 ns), vertical values are in
   scanlines.

   (0, 0) is somewhere in the upper-left corner :-)


   Amiga visible winकरोw definitions
   --------------------------------

   Currently I only have values क्रम AGA, SHRES (28 MHz करोtघड़ी). Feel मुक्त to
   make corrections and/or additions.

   Within the above synchronization specअगरications, the visible winकरोw is
   defined by the following parameters (actual रेजिस्टर resolutions may be
   dअगरferent; all horizontal values are normalized with respect to the pixel
   घड़ी):

      - diwstrt_h:   Horizontal start of the visible winकरोw
      - diwstop_h:   Horizontal stop + 1(*) of the visible winकरोw
      - diwstrt_v:   Vertical start of the visible winकरोw
      - diwstop_v:   Vertical stop of the visible winकरोw
      - ddfstrt:     Horizontal start of display DMA
      - ddfstop:     Horizontal stop of display DMA
      - hscroll:     Horizontal display output delay

   Sprite positioning:

      - sprstrt_h:   Horizontal start - 4 of sprite
      - sprstrt_v:   Vertical start of sprite

   (*) Even Commoकरोre did it wrong in the AGA monitor drivers by not adding 1.

   Horizontal values are in करोtघड़ी cycles (35 ns), vertical values are in
   scanlines.

   (0, 0) is somewhere in the upper-left corner :-)


   Dependencies (AGA, SHRES (35 ns करोtघड़ी))
   -------------------------------------------

   Since there are much more parameters क्रम the Amiga display than क्रम the
   frame buffer पूर्णांकerface, there must be some dependencies among the Amiga
   display parameters. Here's what I found out:

      - ddfstrt and ddfstop are best aligned to 64 pixels.
      - the chipset needs 64 + 4 horizontal pixels after the DMA start beक्रमe
	the first pixel is output, so diwstrt_h = ddfstrt + 64 + 4 अगर you want
	to display the first pixel on the line too. Increase diwstrt_h क्रम
	भव screen panning.
      - the display DMA always fetches 64 pixels at a समय (भ_शेषe = 3).
      - ddfstop is ddfstrt+#pixels - 64.
      - diwstop_h = diwstrt_h + xres + 1. Because of the additional 1 this can
	be 1 more than htotal.
      - hscroll simply adds a delay to the display output. Smooth horizontal
	panning needs an extra 64 pixels on the left to prefetch the pixels that
	`fall off' on the left.
      - अगर ddfstrt < 192, the sprite DMA cycles are all stolen by the bitplane
	DMA, so it's best to make the DMA start as late as possible.
      - you really करोn't want to make ddfstrt < 128, since this will steal DMA
	cycles from the other DMA channels (audio, floppy and Chip RAM refresh).
      - I make diwstop_h and diwstop_v as large as possible.

   General dependencies
   --------------------

      - all values are SHRES pixel (35ns)

		  table 1:fetchstart  table 2:prefetch    table 3:fetchsize
		  ------------------  ----------------    -----------------
   Pixघड़ी     # SHRES|HIRES|LORES # SHRES|HIRES|LORES # SHRES|HIRES|LORES
   -------------#------+-----+------#------+-----+------#------+-----+------
   Bus width 1x #   16 |  32 |  64  #   16 |  32 |  64  #   64 |  64 |  64
   Bus width 2x #   32 |  64 | 128  #   32 |  64 |  64  #   64 |  64 | 128
   Bus width 4x #   64 | 128 | 256  #   64 |  64 |  64  #   64 | 128 | 256

      - chipset needs 4 pixels beक्रमe the first pixel is output
      - ddfstrt must be aligned to fetchstart (table 1)
      - chipset needs also prefetch (table 2) to get first pixel data, so
	ddfstrt = ((diwstrt_h - 4) & -fetchstart) - prefetch
      - क्रम horizontal panning decrease diwstrt_h
      - the length of a fetchline must be aligned to fetchsize (table 3)
      - अगर fetchstart is smaller than fetchsize, then ddfstrt can a little bit
	moved to optimize use of dma (useful क्रम OCS/ECS overscan displays)
      - ddfstop is ddfstrt + ddfsize - fetchsize
      - If C= didn't change anything क्रम AGA, then at following positions the
	dma bus is alपढ़ोy used:
	ddfstrt <  48 -> memory refresh
		<  96 -> disk dma
		< 160 -> audio dma
		< 192 -> sprite 0 dma
		< 416 -> sprite dma (32 per sprite)
      - in accordance with the hardware reference manual a hardware stop is at
	192, but AGA (ECS?) can go below this.

   DMA priorities
   --------------

   Since there are limits on the earliest start value क्रम display DMA and the
   display of sprites, I use the following policy on horizontal panning and
   the hardware cursor:

      - अगर you want to start display DMA too early, you lose the ability to
	करो smooth horizontal panning (xpanstep 1 -> 64).
      - अगर you want to go even further, you lose the hardware cursor too.

   IMHO a hardware cursor is more important क्रम X than horizontal scrolling,
   so that's my motivation.


   Implementation
   --------------

   ami_decode_var() converts the frame buffer values to the Amiga values. It's
   just a `straightक्रमward' implementation of the above rules.


   Standard VGA timings
   --------------------

	       xres  yres    left  right  upper  lower    hsync    vsync
	       ----  ----    ----  -----  -----  -----    -----    -----
      80x25     720   400      27     45     35     12      108        2
      80x30     720   480      27     45     30      9      108        2

   These were taken from a XFree86 configuration file, recalculated क्रम a 28 MHz
   करोtघड़ी (Amigas करोn't have a 25 MHz करोtघड़ी) and converted to frame buffer
   generic timings.

   As a comparison, graphics/monitor.h suggests the following:

	       xres  yres    left  right  upper  lower    hsync    vsync
	       ----  ----    ----  -----  -----  -----    -----    -----

      VGA       640   480      52    112     24     19    112 -      2 +
      VGA70     640   400      52    112     27     21    112 -      2 -


   Sync polarities
   ---------------

      VSYNC    HSYNC    Vertical size    Vertical total
      -----    -----    -------------    --------------
	+        +           Reserved          Reserved
	+        -                400               414
	-        +                350               362
	-        -                480               496

   Source: CL-GD542X Technical Reference Manual, Cirrus Logic, Oct 1992


   Broadcast video timings
   -----------------------

   According to the CCIR and RETMA specअगरications, we have the following values:

   CCIR -> PAL
   -----------

      - a scanline is 64 तगs दीर्घ, of which 52.48 तगs are visible. This is about
	736 visible 70 ns pixels per line.
      - we have 625 scanlines, of which 575 are visible (पूर्णांकerlaced); after
	rounding this becomes 576.

   RETMA -> NTSC
   -------------

      - a scanline is 63.5 तगs दीर्घ, of which 53.5 तगs are visible.  This is about
	736 visible 70 ns pixels per line.
      - we have 525 scanlines, of which 485 are visible (पूर्णांकerlaced); after
	rounding this becomes 484.

   Thus अगर you want a PAL compatible display, you have to करो the following:

      - set the FB_SYNC_BROADCAST flag to indicate that standard broadcast
	timings are to be used.
      - make sure upper_margin + yres + lower_margin + vsync_len = 625 क्रम an
	पूर्णांकerlaced, 312 क्रम a non-पूर्णांकerlaced and 156 क्रम a द्विगुनscanned
	display.
      - make sure left_margin + xres + right_margin + hsync_len = 1816 क्रम a
	SHRES, 908 क्रम a HIRES and 454 क्रम a LORES display.
      - the left visible part begins at 360 (SHRES; HIRES:180, LORES:90),
	left_margin + 2 * hsync_len must be greater or equal.
      - the upper visible part begins at 48 (पूर्णांकerlaced; non-पूर्णांकerlaced:24,
	द्विगुनscanned:12), upper_margin + 2 * vsync_len must be greater or
	equal.
      - ami_encode_var() calculates margins with a hsync of 5320 ns and a vsync
	of 4 scanlines

   The settings क्रम a NTSC compatible display are straightक्रमward.

   Note that in a strict sense the PAL and NTSC standards only define the
   encoding of the color part (chrominance) of the video संकेत and करोn't say
   anything about horizontal/vertical synchronization nor refresh rates.


							    -- Geert --

*******************************************************************************/


	/*
	 * Custom Chipset Definitions
	 */

#घोषणा CUSTOM_OFS(fld) ((दीर्घ)&((काष्ठा CUSTOM*)0)->fld)

	/*
	 * BPLCON0 -- Bitplane Control Register 0
	 */

#घोषणा BPC0_HIRES	(0x8000)
#घोषणा BPC0_BPU2	(0x4000) /* Bit plane used count */
#घोषणा BPC0_BPU1	(0x2000)
#घोषणा BPC0_BPU0	(0x1000)
#घोषणा BPC0_HAM	(0x0800) /* HAM mode */
#घोषणा BPC0_DPF	(0x0400) /* Double playfield */
#घोषणा BPC0_COLOR	(0x0200) /* Enable colorburst */
#घोषणा BPC0_GAUD	(0x0100) /* Genlock audio enable */
#घोषणा BPC0_UHRES	(0x0080) /* Ultrahi res enable */
#घोषणा BPC0_SHRES	(0x0040) /* Super hi res mode */
#घोषणा BPC0_BYPASS	(0x0020) /* Bypass LUT - AGA */
#घोषणा BPC0_BPU3	(0x0010) /* AGA */
#घोषणा BPC0_LPEN	(0x0008) /* Light pen enable */
#घोषणा BPC0_LACE	(0x0004) /* Interlace */
#घोषणा BPC0_ERSY	(0x0002) /* External resync */
#घोषणा BPC0_ECSENA	(0x0001) /* ECS enable */

	/*
	 * BPLCON2 -- Bitplane Control Register 2
	 */

#घोषणा BPC2_ZDBPSEL2	(0x4000) /* Bitplane to be used क्रम ZD - AGA */
#घोषणा BPC2_ZDBPSEL1	(0x2000)
#घोषणा BPC2_ZDBPSEL0	(0x1000)
#घोषणा BPC2_ZDBPEN	(0x0800) /* Enable ZD with ZDBPSELx - AGA */
#घोषणा BPC2_ZDCTEN	(0x0400) /* Enable ZD with palette bit #31 - AGA */
#घोषणा BPC2_KILLEHB	(0x0200) /* Kill EHB mode - AGA */
#घोषणा BPC2_RDRAM	(0x0100) /* Color table accesses पढ़ो, not ग_लिखो - AGA */
#घोषणा BPC2_SOGEN	(0x0080) /* SOG output pin high - AGA */
#घोषणा BPC2_PF2PRI	(0x0040) /* PF2 priority over PF1 */
#घोषणा BPC2_PF2P2	(0x0020) /* PF2 priority wrt sprites */
#घोषणा BPC2_PF2P1	(0x0010)
#घोषणा BPC2_PF2P0	(0x0008)
#घोषणा BPC2_PF1P2	(0x0004) /* ditto PF1 */
#घोषणा BPC2_PF1P1	(0x0002)
#घोषणा BPC2_PF1P0	(0x0001)

	/*
	 * BPLCON3 -- Bitplane Control Register 3 (AGA)
	 */

#घोषणा BPC3_BANK2	(0x8000) /* Bits to select color रेजिस्टर bank */
#घोषणा BPC3_BANK1	(0x4000)
#घोषणा BPC3_BANK0	(0x2000)
#घोषणा BPC3_PF2OF2	(0x1000) /* Bits क्रम color table offset when PF2 */
#घोषणा BPC3_PF2OF1	(0x0800)
#घोषणा BPC3_PF2OF0	(0x0400)
#घोषणा BPC3_LOCT	(0x0200) /* Color रेजिस्टर ग_लिखोs go to low bits */
#घोषणा BPC3_SPRES1	(0x0080) /* Sprite resolution bits */
#घोषणा BPC3_SPRES0	(0x0040)
#घोषणा BPC3_BRDRBLNK	(0x0020) /* Border blanked? */
#घोषणा BPC3_BRDRTRAN	(0x0010) /* Border transparent? */
#घोषणा BPC3_ZDCLKEN	(0x0004) /* ZD pin is 14 MHz (HIRES) घड़ी output */
#घोषणा BPC3_BRDRSPRT	(0x0002) /* Sprites in border? */
#घोषणा BPC3_EXTBLKEN	(0x0001) /* BLANK programmable */

	/*
	 * BPLCON4 -- Bitplane Control Register 4 (AGA)
	 */

#घोषणा BPC4_BPLAM7	(0x8000) /* bitplane color XOR field */
#घोषणा BPC4_BPLAM6	(0x4000)
#घोषणा BPC4_BPLAM5	(0x2000)
#घोषणा BPC4_BPLAM4	(0x1000)
#घोषणा BPC4_BPLAM3	(0x0800)
#घोषणा BPC4_BPLAM2	(0x0400)
#घोषणा BPC4_BPLAM1	(0x0200)
#घोषणा BPC4_BPLAM0	(0x0100)
#घोषणा BPC4_ESPRM7	(0x0080) /* 4 high bits क्रम even sprite colors */
#घोषणा BPC4_ESPRM6	(0x0040)
#घोषणा BPC4_ESPRM5	(0x0020)
#घोषणा BPC4_ESPRM4	(0x0010)
#घोषणा BPC4_OSPRM7	(0x0008) /* 4 high bits क्रम odd sprite colors */
#घोषणा BPC4_OSPRM6	(0x0004)
#घोषणा BPC4_OSPRM5	(0x0002)
#घोषणा BPC4_OSPRM4	(0x0001)

	/*
	 * BEAMCON0 -- Beam Control Register
	 */

#घोषणा BMC0_HARDDIS	(0x4000) /* Disable hardware limits */
#घोषणा BMC0_LPENDIS	(0x2000) /* Disable light pen latch */
#घोषणा BMC0_VARVBEN	(0x1000) /* Enable variable vertical blank */
#घोषणा BMC0_LOLDIS	(0x0800) /* Disable दीर्घ/लघु line toggle */
#घोषणा BMC0_CSCBEN	(0x0400) /* Composite sync/blank */
#घोषणा BMC0_VARVSYEN	(0x0200) /* Enable variable vertical sync */
#घोषणा BMC0_VARHSYEN	(0x0100) /* Enable variable horizontal sync */
#घोषणा BMC0_VARBEAMEN	(0x0080) /* Enable variable beam counters */
#घोषणा BMC0_DUAL	(0x0040) /* Enable alternate horizontal beam counter */
#घोषणा BMC0_PAL	(0x0020) /* Set decodes क्रम PAL */
#घोषणा BMC0_VARCSYEN	(0x0010) /* Enable variable composite sync */
#घोषणा BMC0_BLANKEN	(0x0008) /* Blank enable (no दीर्घer used on AGA) */
#घोषणा BMC0_CSYTRUE	(0x0004) /* CSY polarity */
#घोषणा BMC0_VSYTRUE	(0x0002) /* VSY polarity */
#घोषणा BMC0_HSYTRUE	(0x0001) /* HSY polarity */


	/*
	 * FMODE -- Fetch Mode Control Register (AGA)
	 */

#घोषणा FMODE_SSCAN2	(0x8000) /* Sprite scan-करोubling */
#घोषणा FMODE_BSCAN2	(0x4000) /* Use PF2 modulus every other line */
#घोषणा FMODE_SPAGEM	(0x0008) /* Sprite page mode */
#घोषणा FMODE_SPR32	(0x0004) /* Sprite 32 bit fetch */
#घोषणा FMODE_BPAGEM	(0x0002) /* Bitplane page mode */
#घोषणा FMODE_BPL32	(0x0001) /* Bitplane 32 bit fetch */

	/*
	 * Tags used to indicate a specअगरic Pixel Clock
	 *
	 * clk_shअगरt is the shअगरt value to get the timings in 35 ns units
	 */

क्रमागत अणु TAG_SHRES, TAG_HIRES, TAG_LORES पूर्ण;

	/*
	 * Tags used to indicate the specअगरic chipset
	 */

क्रमागत अणु TAG_OCS, TAG_ECS, TAG_AGA पूर्ण;

	/*
	 * Tags used to indicate the memory bandwidth
	 */

क्रमागत अणु TAG_FMODE_1, TAG_FMODE_2, TAG_FMODE_4 पूर्ण;


	/*
	 * Clock Definitions, Maximum Display Depth
	 *
	 * These depend on the E-Clock or the Chipset, so they are filled in
	 * dynamically
	 */

अटल u_दीर्घ pixघड़ी[3];	/* SHRES/HIRES/LORES: index = clk_shअगरt */
अटल u_लघु maxdepth[3];	/* SHRES/HIRES/LORES: index = clk_shअगरt */
अटल u_लघु maxभ_शेषe, chipset;


	/*
	 * Broadcast Video Timings
	 *
	 * Horizontal values are in 35 ns (SHRES) units
	 * Vertical values are in पूर्णांकerlaced scanlines
	 */

#घोषणा PAL_DIWSTRT_H	(360)	/* PAL Winकरोw Limits */
#घोषणा PAL_DIWSTRT_V	(48)
#घोषणा PAL_HTOTAL	(1816)
#घोषणा PAL_VTOTAL	(625)

#घोषणा NTSC_DIWSTRT_H	(360)	/* NTSC Winकरोw Limits */
#घोषणा NTSC_DIWSTRT_V	(40)
#घोषणा NTSC_HTOTAL	(1816)
#घोषणा NTSC_VTOTAL	(525)


	/*
	 * Various macros
	 */

#घोषणा up2(v)		(((v) + 1) & -2)
#घोषणा करोwn2(v)	((v) & -2)
#घोषणा भाग2(v)		((v)>>1)
#घोषणा mod2(v)		((v) & 1)

#घोषणा up4(v)		(((v) + 3) & -4)
#घोषणा करोwn4(v)	((v) & -4)
#घोषणा mul4(v)		((v) << 2)
#घोषणा भाग4(v)		((v)>>2)
#घोषणा mod4(v)		((v) & 3)

#घोषणा up8(v)		(((v) + 7) & -8)
#घोषणा करोwn8(v)	((v) & -8)
#घोषणा भाग8(v)		((v)>>3)
#घोषणा mod8(v)		((v) & 7)

#घोषणा up16(v)		(((v) + 15) & -16)
#घोषणा करोwn16(v)	((v) & -16)
#घोषणा भाग16(v)	((v)>>4)
#घोषणा mod16(v)	((v) & 15)

#घोषणा up32(v)		(((v) + 31) & -32)
#घोषणा करोwn32(v)	((v) & -32)
#घोषणा भाग32(v)	((v)>>5)
#घोषणा mod32(v)	((v) & 31)

#घोषणा up64(v)		(((v) + 63) & -64)
#घोषणा करोwn64(v)	((v) & -64)
#घोषणा भाग64(v)	((v)>>6)
#घोषणा mod64(v)	((v) & 63)

#घोषणा upx(x, v)	(((v) + (x) - 1) & -(x))
#घोषणा करोwnx(x, v)	((v) & -(x))
#घोषणा modx(x, v)	((v) & ((x) - 1))

/*
 * FIXME: Use C variants of the code marked with #अगर_घोषित __mc68000__
 * in the driver. It shouldn't negatively affect the perक्रमmance and
 * is required क्रम APUS support (once it is re-added to the kernel).
 * Needs to be tested on the hardware though..
 */
/* अगर x1 is not a स्थिरant, this macro won't make real sense :-) */
#अगर_घोषित __mc68000__
#घोषणा DIVUL(x1, x2) (अणुपूर्णांक res; यंत्र("divul %1,%2,%3": "=d" (res): \
	"d" (x2), "d" ((दीर्घ)((x1) / 0x100000000ULL)), "0" ((दीर्घ)(x1))); res;पूर्ण)
#अन्यथा
/* We know a bit about the numbers, so we can करो it this way */
#घोषणा DIVUL(x1, x2) ((((दीर्घ)((अचिन्हित दीर्घ दीर्घ)x1 >> 8) / x2) << 8) + \
	((((दीर्घ)((अचिन्हित दीर्घ दीर्घ)x1 >> 8) % x2) << 8) / x2))
#पूर्ण_अगर

#घोषणा highw(x)	((u_दीर्घ)(x)>>16 & 0xffff)
#घोषणा loww(x)		((u_दीर्घ)(x) & 0xffff)

#घोषणा custom		amiga_custom

#घोषणा VBlankOn()	custom.पूर्णांकena = IF_SETCLR|IF_COPER
#घोषणा VBlankOff()	custom.पूर्णांकena = IF_COPER


	/*
	 * Chip RAM we reserve क्रम the Frame Buffer
	 *
	 * This defines the Maximum Virtual Screen Size
	 * (Setable per kernel options?)
	 */

#घोषणा VIDEOMEMSIZE_AGA_2M	(1310720) /* AGA (2MB) : max 1280*1024*256  */
#घोषणा VIDEOMEMSIZE_AGA_1M	(786432)  /* AGA (1MB) : max 1024*768*256   */
#घोषणा VIDEOMEMSIZE_ECS_2M	(655360)  /* ECS (2MB) : max 1280*1024*16   */
#घोषणा VIDEOMEMSIZE_ECS_1M	(393216)  /* ECS (1MB) : max 1024*768*16    */
#घोषणा VIDEOMEMSIZE_OCS	(262144)  /* OCS       : max ca. 800*600*16 */

#घोषणा SPRITEMEMSIZE		(64 * 64 / 4) /* max 64*64*4 */
#घोषणा DUMMYSPRITEMEMSIZE	(8)
अटल u_दीर्घ spritememory;

#घोषणा CHIPRAM_SAFETY_LIMIT	(16384)

अटल u_दीर्घ videomemory;

	/*
	 * This is the earliest allowed start of fetching display data.
	 * Only अगर you really want no hardware cursor and audio,
	 * set this to 128, but let it better at 192
	 */

अटल u_दीर्घ min_fstrt = 192;

#घोषणा assignchunk(name, type, ptr, size) \
अणु \
	(name) = (type)(ptr); \
	ptr += size; \
पूर्ण


	/*
	 * Copper Inकाष्ठाions
	 */

#घोषणा CMOVE(val, reg)		(CUSTOM_OFS(reg) << 16 | (val))
#घोषणा CMOVE2(val, reg)	((CUSTOM_OFS(reg) + 2) << 16 | (val))
#घोषणा CWAIT(x, y)		(((y) & 0x1fe) << 23 | ((x) & 0x7f0) << 13 | 0x0001fffe)
#घोषणा CEND			(0xfffffffe)


प्रकार जोड़ अणु
	u_दीर्घ l;
	u_लघु w[2];
पूर्ण copins;

अटल काष्ठा copdisplay अणु
	copins *init;
	copins *रुको;
	copins *list[2][2];
	copins *rebuild[2];
पूर्ण copdisplay;

अटल u_लघु currentcop = 0;

	/*
	 * Hardware Cursor API Definitions
	 * These used to be in linux/fb.h, but were preliminary and used by
	 * amअगरb only anyway
	 */

#घोषणा FBIOGET_FCURSORINFO     0x4607
#घोषणा FBIOGET_VCURSORINFO     0x4608
#घोषणा FBIOPUT_VCURSORINFO     0x4609
#घोषणा FBIOGET_CURSORSTATE     0x460A
#घोषणा FBIOPUT_CURSORSTATE     0x460B


काष्ठा fb_fix_cursorinfo अणु
	__u16 crsr_width;		/* width and height of the cursor in */
	__u16 crsr_height;		/* pixels (zero अगर no cursor)	*/
	__u16 crsr_xsize;		/* cursor size in display pixels */
	__u16 crsr_ysize;
	__u16 crsr_color1;		/* colormap entry क्रम cursor color1 */
	__u16 crsr_color2;		/* colormap entry क्रम cursor color2 */
पूर्ण;

काष्ठा fb_var_cursorinfo अणु
	__u16 width;
	__u16 height;
	__u16 xspot;
	__u16 yspot;
	__u8 data[1];			/* field with [height][width]        */
पूर्ण;

काष्ठा fb_cursorstate अणु
	__s16 xoffset;
	__s16 yoffset;
	__u16 mode;
पूर्ण;

#घोषणा FB_CURSOR_OFF		0
#घोषणा FB_CURSOR_ON		1
#घोषणा FB_CURSOR_FLASH		2


	/*
	 * Hardware Cursor
	 */

अटल पूर्णांक cursorrate = 20;	/* Number of frames/flash toggle */
अटल u_लघु cursorstate = -1;
अटल u_लघु cursormode = FB_CURSOR_OFF;

अटल u_लघु *lofsprite, *shfsprite, *dummysprite;

	/*
	 * Current Video Mode
	 */

काष्ठा amअगरb_par अणु

	/* General Values */

	पूर्णांक xres;		/* vmode */
	पूर्णांक yres;		/* vmode */
	पूर्णांक vxres;		/* vmode */
	पूर्णांक vyres;		/* vmode */
	पूर्णांक xoffset;		/* vmode */
	पूर्णांक yoffset;		/* vmode */
	u_लघु bpp;		/* vmode */
	u_लघु clk_shअगरt;	/* vmode */
	u_लघु line_shअगरt;	/* vmode */
	पूर्णांक vmode;		/* vmode */
	u_लघु diwstrt_h;	/* vmode */
	u_लघु diwstop_h;	/* vmode */
	u_लघु diwstrt_v;	/* vmode */
	u_लघु diwstop_v;	/* vmode */
	u_दीर्घ next_line;	/* modulo क्रम next line */
	u_दीर्घ next_plane;	/* modulo क्रम next plane */

	/* Cursor Values */

	काष्ठा अणु
		लघु crsr_x;	/* movecursor */
		लघु crsr_y;	/* movecursor */
		लघु spot_x;
		लघु spot_y;
		u_लघु height;
		u_लघु width;
		u_लघु भ_शेषe;
	पूर्ण crsr;

	/* OCS Hardware Registers */

	u_दीर्घ bplpt0;		/* vmode, pan (Note: physical address) */
	u_दीर्घ bplpt0wrap;	/* vmode, pan (Note: physical address) */
	u_लघु ddfstrt;
	u_लघु ddfstop;
	u_लघु bpl1mod;
	u_लघु bpl2mod;
	u_लघु bplcon0;	/* vmode */
	u_लघु bplcon1;	/* vmode */
	u_लघु htotal;		/* vmode */
	u_लघु vtotal;		/* vmode */

	/* Additional ECS Hardware Registers */

	u_लघु bplcon3;	/* vmode */
	u_लघु beamcon0;	/* vmode */
	u_लघु hsstrt;		/* vmode */
	u_लघु hsstop;		/* vmode */
	u_लघु hbstrt;		/* vmode */
	u_लघु hbstop;		/* vmode */
	u_लघु vsstrt;		/* vmode */
	u_लघु vsstop;		/* vmode */
	u_लघु vbstrt;		/* vmode */
	u_लघु vbstop;		/* vmode */
	u_लघु hcenter;	/* vmode */

	/* Additional AGA Hardware Registers */

	u_लघु भ_शेषe;		/* vmode */
पूर्ण;


	/*
	 *  Saved color entry 0 so we can restore it when unblanking
	 */

अटल u_अक्षर red0, green0, blue0;


#अगर defined(CONFIG_FB_AMIGA_ECS)
अटल u_लघु ecs_palette[32];
#पूर्ण_अगर


	/*
	 * Latches क्रम Display Changes during VBlank
	 */

अटल u_लघु करो_vmode_full = 0;	/* Change the Video Mode */
अटल u_लघु करो_vmode_pan = 0;	/* Update the Video Mode */
अटल लघु करो_blank = 0;		/* (Un)Blank the Screen (तऔ1) */
अटल u_लघु करो_cursor = 0;		/* Move the Cursor */


	/*
	 * Various Flags
	 */

अटल u_लघु is_blanked = 0;		/* Screen is Blanked */
अटल u_लघु is_lace = 0;		/* Screen is laced */

	/*
	 * Predefined Video Modes
	 *
	 */

अटल काष्ठा fb_videomode ami_modedb[] __initdata = अणु

	/*
	 *  AmigaOS Video Modes
	 *
	 *  If you change these, make sure to update DEFMODE_* as well!
	 */

	अणु
		/* 640x200, 15 kHz, 60 Hz (NTSC) */
		"ntsc", 60, 640, 200, TAG_HIRES, 106, 86, 44, 16, 76, 2,
		FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 15 kHz, 60 Hz पूर्णांकerlaced (NTSC) */
		"ntsc-lace", 60, 640, 400, TAG_HIRES, 106, 86, 88, 33, 76, 4,
		FB_SYNC_BROADCAST, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x256, 15 kHz, 50 Hz (PAL) */
		"pal", 50, 640, 256, TAG_HIRES, 106, 86, 40, 14, 76, 2,
		FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x512, 15 kHz, 50 Hz पूर्णांकerlaced (PAL) */
		"pal-lace", 50, 640, 512, TAG_HIRES, 106, 86, 80, 29, 76, 4,
		FB_SYNC_BROADCAST, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x480, 29 kHz, 57 Hz */
		"multiscan", 57, 640, 480, TAG_SHRES, 96, 112, 29, 8, 72, 8,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x960, 29 kHz, 57 Hz पूर्णांकerlaced */
		"multiscan-lace", 57, 640, 960, TAG_SHRES, 96, 112, 58, 16, 72,
		16,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x200, 15 kHz, 72 Hz */
		"euro36", 72, 640, 200, TAG_HIRES, 92, 124, 6, 6, 52, 5,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 15 kHz, 72 Hz पूर्णांकerlaced */
		"euro36-lace", 72, 640, 400, TAG_HIRES, 92, 124, 12, 12, 52,
		10,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 29 kHz, 68 Hz */
		"euro72", 68, 640, 400, TAG_SHRES, 164, 92, 9, 9, 80, 8,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x800, 29 kHz, 68 Hz पूर्णांकerlaced */
		"euro72-lace", 68, 640, 800, TAG_SHRES, 164, 92, 18, 18, 80,
		16,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 800x300, 23 kHz, 70 Hz */
		"super72", 70, 800, 300, TAG_SHRES, 212, 140, 10, 11, 80, 7,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 800x600, 23 kHz, 70 Hz पूर्णांकerlaced */
		"super72-lace", 70, 800, 600, TAG_SHRES, 212, 140, 20, 22, 80,
		14,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x200, 27 kHz, 57 Hz द्विगुनscan */
		"dblntsc", 57, 640, 200, TAG_SHRES, 196, 124, 18, 17, 80, 4,
		0, FB_VMODE_DOUBLE | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 27 kHz, 57 Hz */
		"dblntsc-ff", 57, 640, 400, TAG_SHRES, 196, 124, 36, 35, 80, 7,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x800, 27 kHz, 57 Hz पूर्णांकerlaced */
		"dblntsc-lace", 57, 640, 800, TAG_SHRES, 196, 124, 72, 70, 80,
		14,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x256, 27 kHz, 47 Hz द्विगुनscan */
		"dblpal", 47, 640, 256, TAG_SHRES, 196, 124, 14, 13, 80, 4,
		0, FB_VMODE_DOUBLE | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x512, 27 kHz, 47 Hz */
		"dblpal-ff", 47, 640, 512, TAG_SHRES, 196, 124, 28, 27, 80, 7,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x1024, 27 kHz, 47 Hz पूर्णांकerlaced */
		"dblpal-lace", 47, 640, 1024, TAG_SHRES, 196, 124, 56, 54, 80,
		14,
		0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
	पूर्ण,

	/*
	 *  VGA Video Modes
	 */

	अणु
		/* 640x480, 31 kHz, 60 Hz (VGA) */
		"vga", 60, 640, 480, TAG_SHRES, 64, 96, 30, 9, 112, 2,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 31 kHz, 70 Hz (VGA) */
		"vga70", 70, 640, 400, TAG_SHRES, 64, 96, 35, 12, 112, 2,
		FB_SYNC_VERT_HIGH_ACT | FB_SYNC_COMP_HIGH_ACT,
		FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण,

#अगर 0

	/*
	 *  A2024 video modes
	 *  These modes करोn't work yet because there's no A2024 driver.
	 */

	अणु
		/* 1024x800, 10 Hz */
		"a2024-10", 10, 1024, 800, TAG_HIRES, 0, 0, 0, 0, 0, 0,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 1024x800, 15 Hz */
		"a2024-15", 15, 1024, 800, TAG_HIRES, 0, 0, 0, 0, 0, 0,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण
#पूर्ण_अगर
पूर्ण;

#घोषणा NUM_TOTAL_MODES  ARRAY_SIZE(ami_modedb)

अटल अक्षर *mode_option __initdata = शून्य;
अटल पूर्णांक round_करोwn_bpp = 1;	/* क्रम mode probing */

	/*
	 * Some शेष modes
	 */


#घोषणा DEFMODE_PAL	    2	/* "pal" क्रम PAL OCS/ECS */
#घोषणा DEFMODE_NTSC	    0	/* "ntsc" क्रम NTSC OCS/ECS */
#घोषणा DEFMODE_AMBER_PAL   3	/* "pal-lace" क्रम flicker fixed PAL (A3000) */
#घोषणा DEFMODE_AMBER_NTSC  1	/* "ntsc-lace" क्रम flicker fixed NTSC (A3000) */
#घोषणा DEFMODE_AGA	    19	/* "vga70" क्रम AGA */


अटल पूर्णांक amअगरb_ilbm = 0;	/* पूर्णांकerleaved or normal bitplanes */

अटल u32 amअगरb_hfmin __initdata;	/* monitor hfreq lower limit (Hz) */
अटल u32 amअगरb_hfmax __initdata;	/* monitor hfreq upper limit (Hz) */
अटल u16 amअगरb_vfmin __initdata;	/* monitor vfreq lower limit (Hz) */
अटल u16 amअगरb_vfmax __initdata;	/* monitor vfreq upper limit (Hz) */


	/*
	 * Macros क्रम the conversion from real world values to hardware रेजिस्टर
	 * values
	 *
	 * This helps us to keep our attention on the real stuff...
	 *
	 * Hardware limits क्रम AGA:
	 *
	 *	parameter  min    max  step
	 *	---------  ---   ----  ----
	 *	diwstrt_h    0   2047     1
	 *	diwstrt_v    0   2047     1
	 *	diwstop_h    0   4095     1
	 *	diwstop_v    0   4095     1
	 *
	 *	ddfstrt      0   2032    16
	 *	ddfstop      0   2032    16
	 *
	 *	htotal       8   2048     8
	 *	hsstrt       0   2040     8
	 *	hsstop       0   2040     8
	 *	vtotal       1   4096     1
	 *	vsstrt       0   4095     1
	 *	vsstop       0   4095     1
	 *	hcenter      0   2040     8
	 *
	 *	hbstrt       0   2047     1
	 *	hbstop       0   2047     1
	 *	vbstrt       0   4095     1
	 *	vbstop       0   4095     1
	 *
	 * Horizontal values are in 35 ns (SHRES) pixels
	 * Vertical values are in half scanlines
	 */

/* bplcon1 (smooth scrolling) */

#घोषणा hscroll2hw(hscroll) \
	(((hscroll) << 12 & 0x3000) | ((hscroll) << 8 & 0xc300) | \
	 ((hscroll) << 4 & 0x0c00) | ((hscroll) << 2 & 0x00f0) | \
	 ((hscroll)>>2 & 0x000f))

/* diwstrt/diwstop/diwhigh (visible display winकरोw) */

#घोषणा diwstrt2hw(diwstrt_h, diwstrt_v) \
	(((diwstrt_v) << 7 & 0xff00) | ((diwstrt_h)>>2 & 0x00ff))
#घोषणा diwstop2hw(diwstop_h, diwstop_v) \
	(((diwstop_v) << 7 & 0xff00) | ((diwstop_h)>>2 & 0x00ff))
#घोषणा diwhigh2hw(diwstrt_h, diwstrt_v, diwstop_h, diwstop_v) \
	(((diwstop_h) << 3 & 0x2000) | ((diwstop_h) << 11 & 0x1800) | \
	 ((diwstop_v)>>1 & 0x0700) | ((diwstrt_h)>>5 & 0x0020) | \
	 ((diwstrt_h) << 3 & 0x0018) | ((diwstrt_v)>>9 & 0x0007))

/* ddfstrt/ddfstop (display DMA) */

#घोषणा ddfstrt2hw(ddfstrt)	भाग8(ddfstrt)
#घोषणा ddfstop2hw(ddfstop)	भाग8(ddfstop)

/* hsstrt/hsstop/htotal/vsstrt/vsstop/vtotal/hcenter (sync timings) */

#घोषणा hsstrt2hw(hsstrt)	(भाग8(hsstrt))
#घोषणा hsstop2hw(hsstop)	(भाग8(hsstop))
#घोषणा htotal2hw(htotal)	(भाग8(htotal) - 1)
#घोषणा vsstrt2hw(vsstrt)	(भाग2(vsstrt))
#घोषणा vsstop2hw(vsstop)	(भाग2(vsstop))
#घोषणा vtotal2hw(vtotal)	(भाग2(vtotal) - 1)
#घोषणा hcenter2hw(htotal)	(भाग8(htotal))

/* hbstrt/hbstop/vbstrt/vbstop (blanking timings) */

#घोषणा hbstrt2hw(hbstrt)	(((hbstrt) << 8 & 0x0700) | ((hbstrt)>>3 & 0x00ff))
#घोषणा hbstop2hw(hbstop)	(((hbstop) << 8 & 0x0700) | ((hbstop)>>3 & 0x00ff))
#घोषणा vbstrt2hw(vbstrt)	(भाग2(vbstrt))
#घोषणा vbstop2hw(vbstop)	(भाग2(vbstop))

/* colour */

#घोषणा rgb2hw8_high(red, green, blue) \
	(((red & 0xf0) << 4) | (green & 0xf0) | ((blue & 0xf0)>>4))
#घोषणा rgb2hw8_low(red, green, blue) \
	(((red & 0x0f) << 8) | ((green & 0x0f) << 4) | (blue & 0x0f))
#घोषणा rgb2hw4(red, green, blue) \
	(((red & 0xf0) << 4) | (green & 0xf0) | ((blue & 0xf0)>>4))
#घोषणा rgb2hw2(red, green, blue) \
	(((red & 0xc0) << 4) | (green & 0xc0) | ((blue & 0xc0)>>4))

/* sprpos/sprctl (sprite positioning) */

#घोषणा spr2hw_pos(start_v, start_h) \
	(((start_v) << 7 & 0xff00) | ((start_h)>>3 & 0x00ff))
#घोषणा spr2hw_ctl(start_v, start_h, stop_v) \
	(((stop_v) << 7 & 0xff00) | ((start_v)>>4 & 0x0040) | \
	 ((stop_v)>>5 & 0x0020) | ((start_h) << 3 & 0x0018) | \
	 ((start_v)>>7 & 0x0004) | ((stop_v)>>8 & 0x0002) | \
	 ((start_h)>>2 & 0x0001))

/* get current vertical position of beam */
#घोषणा get_vbpos()	((u_लघु)((*(u_दीर्घ अस्थिर *)&custom.vposr >> 7) & 0xffe))

	/*
	 * Copper Initialisation List
	 */

#घोषणा COPINITSIZE (माप(copins) * 40)

क्रमागत अणु
	cip_bplcon0
पूर्ण;

	/*
	 * Long Frame/Short Frame Copper List
	 * Don't change the order, build_copper()/rebuild_copper() rely on this
	 */

#घोषणा COPLISTSIZE (माप(copins) * 64)

क्रमागत अणु
	cop_रुको, cop_bplcon0,
	cop_spr0ptrh, cop_spr0ptrl,
	cop_diwstrt, cop_diwstop,
	cop_diwhigh,
पूर्ण;

	/*
	 * Pixel modes क्रम Bitplanes and Sprites
	 */

अटल u_लघु bplpixmode[3] = अणु
	BPC0_SHRES,			/*  35 ns */
	BPC0_HIRES,			/*  70 ns */
	0				/* 140 ns */
पूर्ण;

अटल u_लघु sprpixmode[3] = अणु
	BPC3_SPRES1 | BPC3_SPRES0,	/*  35 ns */
	BPC3_SPRES1,			/*  70 ns */
	BPC3_SPRES0			/* 140 ns */
पूर्ण;

	/*
	 * Fetch modes क्रम Bitplanes and Sprites
	 */

अटल u_लघु bplfetchmode[3] = अणु
	0,				/* 1x */
	FMODE_BPL32,			/* 2x */
	FMODE_BPAGEM | FMODE_BPL32	/* 4x */
पूर्ण;

अटल u_लघु sprfetchmode[3] = अणु
	0,				/* 1x */
	FMODE_SPR32,			/* 2x */
	FMODE_SPAGEM | FMODE_SPR32	/* 4x */
पूर्ण;


/* --------------------------- Hardware routines --------------------------- */

	/*
	 * Get the video params out of `var'. If a value doesn't fit, round
	 * it up, अगर it's too big, वापस -EINVAL.
	 */

अटल पूर्णांक ami_decode_var(काष्ठा fb_var_screeninfo *var, काष्ठा amअगरb_par *par,
			  स्थिर काष्ठा fb_info *info)
अणु
	u_लघु clk_shअगरt, line_shअगरt;
	u_दीर्घ maxfetchstop, fstrt, fsize, fस्थिर, xres_n, yres_n;
	u_पूर्णांक htotal, vtotal;

	/*
	 * Find a matching Pixel Clock
	 */

	क्रम (clk_shअगरt = TAG_SHRES; clk_shअगरt <= TAG_LORES; clk_shअगरt++)
		अगर (var->pixघड़ी <= pixघड़ी[clk_shअगरt])
			अवरोध;
	अगर (clk_shअगरt > TAG_LORES) अणु
		DPRINTK("pixclock too high\n");
		वापस -EINVAL;
	पूर्ण
	par->clk_shअगरt = clk_shअगरt;

	/*
	 * Check the Geometry Values
	 */

	अगर ((par->xres = var->xres) < 64)
		par->xres = 64;
	अगर ((par->yres = var->yres) < 64)
		par->yres = 64;
	अगर ((par->vxres = var->xres_भव) < par->xres)
		par->vxres = par->xres;
	अगर ((par->vyres = var->yres_भव) < par->yres)
		par->vyres = par->yres;

	par->bpp = var->bits_per_pixel;
	अगर (!var->nonstd) अणु
		अगर (par->bpp < 1)
			par->bpp = 1;
		अगर (par->bpp > maxdepth[clk_shअगरt]) अणु
			अगर (round_करोwn_bpp && maxdepth[clk_shअगरt])
				par->bpp = maxdepth[clk_shअगरt];
			अन्यथा अणु
				DPRINTK("invalid bpp\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (var->nonstd == FB_NONSTD_HAM) अणु
		अगर (par->bpp < 6)
			par->bpp = 6;
		अगर (par->bpp != 6) अणु
			अगर (par->bpp < 8)
				par->bpp = 8;
			अगर (par->bpp != 8 || !IS_AGA) अणु
				DPRINTK("invalid bpp for ham mode\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DPRINTK("unknown nonstd mode\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * FB_VMODE_SMOOTH_XPAN will be cleared, अगर one of the following
	 * checks failed and smooth scrolling is not possible
	 */

	par->vmode = var->vmode | FB_VMODE_SMOOTH_XPAN;
	चयन (par->vmode & FB_VMODE_MASK) अणु
	हाल FB_VMODE_INTERLACED:
		line_shअगरt = 0;
		अवरोध;
	हाल FB_VMODE_NONINTERLACED:
		line_shअगरt = 1;
		अवरोध;
	हाल FB_VMODE_DOUBLE:
		अगर (!IS_AGA) अणु
			DPRINTK("double mode only possible with aga\n");
			वापस -EINVAL;
		पूर्ण
		line_shअगरt = 2;
		अवरोध;
	शेष:
		DPRINTK("unknown video mode\n");
		वापस -EINVAL;
		अवरोध;
	पूर्ण
	par->line_shअगरt = line_shअगरt;

	/*
	 * Vertical and Horizontal Timings
	 */

	xres_n = par->xres << clk_shअगरt;
	yres_n = par->yres << line_shअगरt;
	par->htotal = करोwn8((var->left_margin + par->xres + var->right_margin +
			     var->hsync_len) << clk_shअगरt);
	par->vtotal =
		करोwn2(((var->upper_margin + par->yres + var->lower_margin +
			var->vsync_len) << line_shअगरt) + 1);

	अगर (IS_AGA)
		par->bplcon3 = sprpixmode[clk_shअगरt];
	अन्यथा
		par->bplcon3 = 0;
	अगर (var->sync & FB_SYNC_BROADCAST) अणु
		par->diwstop_h = par->htotal -
			((var->right_margin - var->hsync_len) << clk_shअगरt);
		अगर (IS_AGA)
			par->diwstop_h += mod4(var->hsync_len);
		अन्यथा
			par->diwstop_h = करोwn4(par->diwstop_h);

		par->diwstrt_h = par->diwstop_h - xres_n;
		par->diwstop_v = par->vtotal -
			((var->lower_margin - var->vsync_len) << line_shअगरt);
		par->diwstrt_v = par->diwstop_v - yres_n;
		अगर (par->diwstop_h >= par->htotal + 8) अणु
			DPRINTK("invalid diwstop_h\n");
			वापस -EINVAL;
		पूर्ण
		अगर (par->diwstop_v > par->vtotal) अणु
			DPRINTK("invalid diwstop_v\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!IS_OCS) अणु
			/* Initialize sync with some reasonable values क्रम pwrsave */
			par->hsstrt = 160;
			par->hsstop = 320;
			par->vsstrt = 30;
			par->vsstop = 34;
		पूर्ण अन्यथा अणु
			par->hsstrt = 0;
			par->hsstop = 0;
			par->vsstrt = 0;
			par->vsstop = 0;
		पूर्ण
		अगर (par->vtotal > (PAL_VTOTAL + NTSC_VTOTAL) / 2) अणु
			/* PAL video mode */
			अगर (par->htotal != PAL_HTOTAL) अणु
				DPRINTK("htotal invalid for pal\n");
				वापस -EINVAL;
			पूर्ण
			अगर (par->diwstrt_h < PAL_DIWSTRT_H) अणु
				DPRINTK("diwstrt_h too low for pal\n");
				वापस -EINVAL;
			पूर्ण
			अगर (par->diwstrt_v < PAL_DIWSTRT_V) अणु
				DPRINTK("diwstrt_v too low for pal\n");
				वापस -EINVAL;
			पूर्ण
			htotal = PAL_HTOTAL>>clk_shअगरt;
			vtotal = PAL_VTOTAL>>1;
			अगर (!IS_OCS) अणु
				par->beamcon0 = BMC0_PAL;
				par->bplcon3 |= BPC3_BRDRBLNK;
			पूर्ण अन्यथा अगर (AMIGAHW_PRESENT(AGNUS_HR_PAL) ||
				   AMIGAHW_PRESENT(AGNUS_HR_NTSC)) अणु
				par->beamcon0 = BMC0_PAL;
				par->hsstop = 1;
			पूर्ण अन्यथा अगर (amiga_vblank != 50) अणु
				DPRINTK("pal not supported by this chipset\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* NTSC video mode
			 * In the AGA chipset seems to be hardware bug with BPC3_BRDRBLNK
			 * and NTSC activated, so than better let diwstop_h <= 1812
			 */
			अगर (par->htotal != NTSC_HTOTAL) अणु
				DPRINTK("htotal invalid for ntsc\n");
				वापस -EINVAL;
			पूर्ण
			अगर (par->diwstrt_h < NTSC_DIWSTRT_H) अणु
				DPRINTK("diwstrt_h too low for ntsc\n");
				वापस -EINVAL;
			पूर्ण
			अगर (par->diwstrt_v < NTSC_DIWSTRT_V) अणु
				DPRINTK("diwstrt_v too low for ntsc\n");
				वापस -EINVAL;
			पूर्ण
			htotal = NTSC_HTOTAL>>clk_shअगरt;
			vtotal = NTSC_VTOTAL>>1;
			अगर (!IS_OCS) अणु
				par->beamcon0 = 0;
				par->bplcon3 |= BPC3_BRDRBLNK;
			पूर्ण अन्यथा अगर (AMIGAHW_PRESENT(AGNUS_HR_PAL) ||
				   AMIGAHW_PRESENT(AGNUS_HR_NTSC)) अणु
				par->beamcon0 = 0;
				par->hsstop = 1;
			पूर्ण अन्यथा अगर (amiga_vblank != 60) अणु
				DPRINTK("ntsc not supported by this chipset\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (IS_OCS) अणु
			अगर (par->diwstrt_h >= 1024 || par->diwstop_h < 1024 ||
			    par->diwstrt_v >=  512 || par->diwstop_v <  256) अणु
				DPRINTK("invalid position for display on ocs\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!IS_OCS) अणु
		/* Programmable video mode */
		par->hsstrt = var->right_margin << clk_shअगरt;
		par->hsstop = (var->right_margin + var->hsync_len) << clk_shअगरt;
		par->diwstop_h = par->htotal - mod8(par->hsstrt) + 8 - (1 << clk_shअगरt);
		अगर (!IS_AGA)
			par->diwstop_h = करोwn4(par->diwstop_h) - 16;
		par->diwstrt_h = par->diwstop_h - xres_n;
		par->hbstop = par->diwstrt_h + 4;
		par->hbstrt = par->diwstop_h + 4;
		अगर (par->hbstrt >= par->htotal + 8)
			par->hbstrt -= par->htotal;
		par->hcenter = par->hsstrt + (par->htotal >> 1);
		par->vsstrt = var->lower_margin << line_shअगरt;
		par->vsstop = (var->lower_margin + var->vsync_len) << line_shअगरt;
		par->diwstop_v = par->vtotal;
		अगर ((par->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
			par->diwstop_v -= 2;
		par->diwstrt_v = par->diwstop_v - yres_n;
		par->vbstop = par->diwstrt_v - 2;
		par->vbstrt = par->diwstop_v - 2;
		अगर (par->vtotal > 2048) अणु
			DPRINTK("vtotal too high\n");
			वापस -EINVAL;
		पूर्ण
		अगर (par->htotal > 2048) अणु
			DPRINTK("htotal too high\n");
			वापस -EINVAL;
		पूर्ण
		par->bplcon3 |= BPC3_EXTBLKEN;
		par->beamcon0 = BMC0_HARDDIS | BMC0_VARVBEN | BMC0_LOLDIS |
				BMC0_VARVSYEN | BMC0_VARHSYEN | BMC0_VARBEAMEN |
				BMC0_PAL | BMC0_VARCSYEN;
		अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
			par->beamcon0 |= BMC0_HSYTRUE;
		अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
			par->beamcon0 |= BMC0_VSYTRUE;
		अगर (var->sync & FB_SYNC_COMP_HIGH_ACT)
			par->beamcon0 |= BMC0_CSYTRUE;
		htotal = par->htotal>>clk_shअगरt;
		vtotal = par->vtotal>>1;
	पूर्ण अन्यथा अणु
		DPRINTK("only broadcast modes possible for ocs\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Checking the DMA timing
	 */

	fस्थिर = 16 << maxभ_शेषe << clk_shअगरt;

	/*
	 * smallest winकरोw start value without turn off other dma cycles
	 * than sprite1-7, unless you change min_fstrt
	 */


	fsize = ((maxभ_शेषe + clk_shअगरt <= 1) ? fस्थिर : 64);
	fstrt = करोwnx(fस्थिर, par->diwstrt_h - 4) - fsize;
	अगर (fstrt < min_fstrt) अणु
		DPRINTK("fetch start too low\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * smallest winकरोw start value where smooth scrolling is possible
	 */

	fstrt = करोwnx(fस्थिर, par->diwstrt_h - fस्थिर + (1 << clk_shअगरt) - 4) -
		fsize;
	अगर (fstrt < min_fstrt)
		par->vmode &= ~FB_VMODE_SMOOTH_XPAN;

	maxfetchstop = करोwn16(par->htotal - 80);

	fstrt = करोwnx(fस्थिर, par->diwstrt_h - 4) - 64 - fस्थिर;
	fsize = upx(fस्थिर, xres_n +
		    modx(fस्थिर, करोwnx(1 << clk_shअगरt, par->diwstrt_h - 4)));
	अगर (fstrt + fsize > maxfetchstop)
		par->vmode &= ~FB_VMODE_SMOOTH_XPAN;

	fsize = upx(fस्थिर, xres_n);
	अगर (fstrt + fsize > maxfetchstop) अणु
		DPRINTK("fetch stop too high\n");
		वापस -EINVAL;
	पूर्ण

	अगर (maxभ_शेषe + clk_shअगरt <= 1) अणु
		fsize = up64(xres_n + fस्थिर - 1);
		अगर (min_fstrt + fsize - 64 > maxfetchstop)
			par->vmode &= ~FB_VMODE_SMOOTH_XPAN;

		fsize = up64(xres_n);
		अगर (min_fstrt + fsize - 64 > maxfetchstop) अणु
			DPRINTK("fetch size too high\n");
			वापस -EINVAL;
		पूर्ण

		fsize -= 64;
	पूर्ण अन्यथा
		fsize -= fस्थिर;

	/*
	 * Check अगर there is enough समय to update the bitplane poपूर्णांकers क्रम ywrap
	 */

	अगर (par->htotal - fsize - 64 < par->bpp * 64)
		par->vmode &= ~FB_VMODE_YWRAP;

	/*
	 * Bitplane calculations and check the Memory Requirements
	 */

	अगर (amअगरb_ilbm) अणु
		par->next_plane = भाग8(upx(16 << maxभ_शेषe, par->vxres));
		par->next_line = par->bpp * par->next_plane;
		अगर (par->next_line * par->vyres > info->fix.smem_len) अणु
			DPRINTK("too few video mem\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		par->next_line = भाग8(upx(16 << maxभ_शेषe, par->vxres));
		par->next_plane = par->vyres * par->next_line;
		अगर (par->next_plane * par->bpp > info->fix.smem_len) अणु
			DPRINTK("too few video mem\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Hardware Register Values
	 */

	par->bplcon0 = BPC0_COLOR | bplpixmode[clk_shअगरt];
	अगर (!IS_OCS)
		par->bplcon0 |= BPC0_ECSENA;
	अगर (par->bpp == 8)
		par->bplcon0 |= BPC0_BPU3;
	अन्यथा
		par->bplcon0 |= par->bpp << 12;
	अगर (var->nonstd == FB_NONSTD_HAM)
		par->bplcon0 |= BPC0_HAM;
	अगर (var->sync & FB_SYNC_EXT)
		par->bplcon0 |= BPC0_ERSY;

	अगर (IS_AGA)
		par->भ_शेषe = bplfetchmode[maxभ_शेषe];

	चयन (par->vmode & FB_VMODE_MASK) अणु
	हाल FB_VMODE_INTERLACED:
		par->bplcon0 |= BPC0_LACE;
		अवरोध;
	हाल FB_VMODE_DOUBLE:
		अगर (IS_AGA)
			par->भ_शेषe |= FMODE_SSCAN2 | FMODE_BSCAN2;
		अवरोध;
	पूर्ण

	अगर (!((par->vmode ^ var->vmode) & FB_VMODE_YWRAP)) अणु
		par->xoffset = var->xoffset;
		par->yoffset = var->yoffset;
		अगर (par->vmode & FB_VMODE_YWRAP) अणु
			अगर (par->yoffset >= par->vyres)
				par->xoffset = par->yoffset = 0;
		पूर्ण अन्यथा अणु
			अगर (par->xoffset > upx(16 << maxभ_शेषe, par->vxres - par->xres) ||
			    par->yoffset > par->vyres - par->yres)
				par->xoffset = par->yoffset = 0;
		पूर्ण
	पूर्ण अन्यथा
		par->xoffset = par->yoffset = 0;

	par->crsr.crsr_x = par->crsr.crsr_y = 0;
	par->crsr.spot_x = par->crsr.spot_y = 0;
	par->crsr.height = par->crsr.width = 0;

	वापस 0;
पूर्ण

	/*
	 * Fill the `var' structure based on the values in `par' and maybe
	 * other values पढ़ो out of the hardware.
	 */

अटल व्योम ami_encode_var(काष्ठा fb_var_screeninfo *var,
			   काष्ठा amअगरb_par *par)
अणु
	u_लघु clk_shअगरt, line_shअगरt;

	स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));

	clk_shअगरt = par->clk_shअगरt;
	line_shअगरt = par->line_shअगरt;

	var->xres = par->xres;
	var->yres = par->yres;
	var->xres_भव = par->vxres;
	var->yres_भव = par->vyres;
	var->xoffset = par->xoffset;
	var->yoffset = par->yoffset;

	var->bits_per_pixel = par->bpp;
	var->grayscale = 0;

	var->red.offset = 0;
	var->red.msb_right = 0;
	var->red.length = par->bpp;
	अगर (par->bplcon0 & BPC0_HAM)
		var->red.length -= 2;
	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;

	अगर (par->bplcon0 & BPC0_HAM)
		var->nonstd = FB_NONSTD_HAM;
	अन्यथा
		var->nonstd = 0;
	var->activate = 0;

	var->height = -1;
	var->width = -1;

	var->pixघड़ी = pixघड़ी[clk_shअगरt];

	अगर (IS_AGA && par->भ_शेषe & FMODE_BSCAN2)
		var->vmode = FB_VMODE_DOUBLE;
	अन्यथा अगर (par->bplcon0 & BPC0_LACE)
		var->vmode = FB_VMODE_INTERLACED;
	अन्यथा
		var->vmode = FB_VMODE_NONINTERLACED;

	अगर (!IS_OCS && par->beamcon0 & BMC0_VARBEAMEN) अणु
		var->hsync_len = (par->hsstop - par->hsstrt)>>clk_shअगरt;
		var->right_margin = par->hsstrt>>clk_shअगरt;
		var->left_margin = (par->htotal>>clk_shअगरt) - var->xres - var->right_margin - var->hsync_len;
		var->vsync_len = (par->vsstop - par->vsstrt)>>line_shअगरt;
		var->lower_margin = par->vsstrt>>line_shअगरt;
		var->upper_margin = (par->vtotal>>line_shअगरt) - var->yres - var->lower_margin - var->vsync_len;
		var->sync = 0;
		अगर (par->beamcon0 & BMC0_HSYTRUE)
			var->sync |= FB_SYNC_HOR_HIGH_ACT;
		अगर (par->beamcon0 & BMC0_VSYTRUE)
			var->sync |= FB_SYNC_VERT_HIGH_ACT;
		अगर (par->beamcon0 & BMC0_CSYTRUE)
			var->sync |= FB_SYNC_COMP_HIGH_ACT;
	पूर्ण अन्यथा अणु
		var->sync = FB_SYNC_BROADCAST;
		var->hsync_len = (152>>clk_shअगरt) + mod4(par->diwstop_h);
		var->right_margin = ((par->htotal - करोwn4(par->diwstop_h))>>clk_shअगरt) + var->hsync_len;
		var->left_margin = (par->htotal>>clk_shअगरt) - var->xres - var->right_margin - var->hsync_len;
		var->vsync_len = 4>>line_shअगरt;
		var->lower_margin = ((par->vtotal - par->diwstop_v)>>line_shअगरt) + var->vsync_len;
		var->upper_margin = (((par->vtotal - 2)>>line_shअगरt) + 1) - var->yres -
				    var->lower_margin - var->vsync_len;
	पूर्ण

	अगर (par->bplcon0 & BPC0_ERSY)
		var->sync |= FB_SYNC_EXT;
	अगर (par->vmode & FB_VMODE_YWRAP)
		var->vmode |= FB_VMODE_YWRAP;
पूर्ण


	/*
	 * Update hardware
	 */

अटल व्योम ami_update_par(काष्ठा fb_info *info)
अणु
	काष्ठा amअगरb_par *par = info->par;
	लघु clk_shअगरt, vshअगरt, fstrt, fsize, fstop, fस्थिर,  shअगरt, move, mod;

	clk_shअगरt = par->clk_shअगरt;

	अगर (!(par->vmode & FB_VMODE_SMOOTH_XPAN))
		par->xoffset = upx(16 << maxभ_शेषe, par->xoffset);

	fस्थिर = 16 << maxभ_शेषe << clk_shअगरt;
	vshअगरt = modx(16 << maxभ_शेषe, par->xoffset);
	fstrt = par->diwstrt_h - (vshअगरt << clk_shअगरt) - 4;
	fsize = (par->xres + vshअगरt) << clk_shअगरt;
	shअगरt = modx(fस्थिर, fstrt);
	move = करोwnx(2 << maxभ_शेषe, भाग8(par->xoffset));
	अगर (maxभ_शेषe + clk_shअगरt > 1) अणु
		fstrt = करोwnx(fस्थिर, fstrt) - 64;
		fsize = upx(fस्थिर, fsize);
		fstop = fstrt + fsize - fस्थिर;
	पूर्ण अन्यथा अणु
		mod = fstrt = करोwnx(fस्थिर, fstrt) - fस्थिर;
		fstop = fstrt + upx(fस्थिर, fsize) - 64;
		fsize = up64(fsize);
		fstrt = fstop - fsize + 64;
		अगर (fstrt < min_fstrt) अणु
			fstop += min_fstrt - fstrt;
			fstrt = min_fstrt;
		पूर्ण
		move = move - भाग8((mod - fstrt)>>clk_shअगरt);
	पूर्ण
	mod = par->next_line - भाग8(fsize>>clk_shअगरt);
	par->ddfstrt = fstrt;
	par->ddfstop = fstop;
	par->bplcon1 = hscroll2hw(shअगरt);
	par->bpl2mod = mod;
	अगर (par->bplcon0 & BPC0_LACE)
		par->bpl2mod += par->next_line;
	अगर (IS_AGA && (par->भ_शेषe & FMODE_BSCAN2))
		par->bpl1mod = -भाग8(fsize>>clk_shअगरt);
	अन्यथा
		par->bpl1mod = par->bpl2mod;

	अगर (par->yoffset) अणु
		par->bplpt0 = info->fix.smem_start +
			      par->next_line * par->yoffset + move;
		अगर (par->vmode & FB_VMODE_YWRAP) अणु
			अगर (par->yoffset > par->vyres - par->yres) अणु
				par->bplpt0wrap = info->fix.smem_start + move;
				अगर (par->bplcon0 & BPC0_LACE &&
				    mod2(par->diwstrt_v + par->vyres -
					 par->yoffset))
					par->bplpt0wrap += par->next_line;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		par->bplpt0 = info->fix.smem_start + move;

	अगर (par->bplcon0 & BPC0_LACE && mod2(par->diwstrt_v))
		par->bplpt0 += par->next_line;
पूर्ण


	/*
	 * Pan or Wrap the Display
	 *
	 * This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
	 * in `var'.
	 */

अटल व्योम ami_pan_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा amअगरb_par *par = info->par;

	par->xoffset = var->xoffset;
	par->yoffset = var->yoffset;
	अगर (var->vmode & FB_VMODE_YWRAP)
		par->vmode |= FB_VMODE_YWRAP;
	अन्यथा
		par->vmode &= ~FB_VMODE_YWRAP;

	करो_vmode_pan = 0;
	ami_update_par(info);
	करो_vmode_pan = 1;
पूर्ण


अटल व्योम ami_update_display(स्थिर काष्ठा amअगरb_par *par)
अणु
	custom.bplcon1 = par->bplcon1;
	custom.bpl1mod = par->bpl1mod;
	custom.bpl2mod = par->bpl2mod;
	custom.ddfstrt = ddfstrt2hw(par->ddfstrt);
	custom.ddfstop = ddfstop2hw(par->ddfstop);
पूर्ण

	/*
	 * Change the video mode (called by VBlank पूर्णांकerrupt)
	 */

अटल व्योम ami_init_display(स्थिर काष्ठा amअगरb_par *par)
अणु
	पूर्णांक i;

	custom.bplcon0 = par->bplcon0 & ~BPC0_LACE;
	custom.bplcon2 = (IS_OCS ? 0 : BPC2_KILLEHB) | BPC2_PF2P2 | BPC2_PF1P2;
	अगर (!IS_OCS) अणु
		custom.bplcon3 = par->bplcon3;
		अगर (IS_AGA)
			custom.bplcon4 = BPC4_ESPRM4 | BPC4_OSPRM4;
		अगर (par->beamcon0 & BMC0_VARBEAMEN) अणु
			custom.htotal = htotal2hw(par->htotal);
			custom.hbstrt = hbstrt2hw(par->hbstrt);
			custom.hbstop = hbstop2hw(par->hbstop);
			custom.hsstrt = hsstrt2hw(par->hsstrt);
			custom.hsstop = hsstop2hw(par->hsstop);
			custom.hcenter = hcenter2hw(par->hcenter);
			custom.vtotal = vtotal2hw(par->vtotal);
			custom.vbstrt = vbstrt2hw(par->vbstrt);
			custom.vbstop = vbstop2hw(par->vbstop);
			custom.vsstrt = vsstrt2hw(par->vsstrt);
			custom.vsstop = vsstop2hw(par->vsstop);
		पूर्ण
	पूर्ण
	अगर (!IS_OCS || par->hsstop)
		custom.beamcon0 = par->beamcon0;
	अगर (IS_AGA)
		custom.भ_शेषe = par->भ_शेषe;

	/*
	 * The minimum period क्रम audio depends on htotal
	 */

	amiga_audio_min_period = भाग16(par->htotal);

	is_lace = par->bplcon0 & BPC0_LACE ? 1 : 0;
#अगर 1
	अगर (is_lace) अणु
		i = custom.vposr >> 15;
	पूर्ण अन्यथा अणु
		custom.vposw = custom.vposr | 0x8000;
		i = 1;
	पूर्ण
#अन्यथा
	i = 1;
	custom.vposw = custom.vposr | 0x8000;
#पूर्ण_अगर
	custom.cop2lc = (u_लघु *)ZTWO_PADDR(copdisplay.list[currentcop][i]);
पूर्ण

	/*
	 * (Un)Blank the screen (called by VBlank पूर्णांकerrupt)
	 */

अटल व्योम ami_करो_blank(स्थिर काष्ठा amअगरb_par *par)
अणु
#अगर defined(CONFIG_FB_AMIGA_AGA)
	u_लघु bplcon3 = par->bplcon3;
#पूर्ण_अगर
	u_अक्षर red, green, blue;

	अगर (करो_blank > 0) अणु
		custom.dmacon = DMAF_RASTER | DMAF_SPRITE;
		red = green = blue = 0;
		अगर (!IS_OCS && करो_blank > 1) अणु
			चयन (करो_blank) अणु
			हाल FB_BLANK_VSYNC_SUSPEND:
				custom.hsstrt = hsstrt2hw(par->hsstrt);
				custom.hsstop = hsstop2hw(par->hsstop);
				custom.vsstrt = vsstrt2hw(par->vtotal + 4);
				custom.vsstop = vsstop2hw(par->vtotal + 4);
				अवरोध;
			हाल FB_BLANK_HSYNC_SUSPEND:
				custom.hsstrt = hsstrt2hw(par->htotal + 16);
				custom.hsstop = hsstop2hw(par->htotal + 16);
				custom.vsstrt = vsstrt2hw(par->vsstrt);
				custom.vsstop = vsstrt2hw(par->vsstop);
				अवरोध;
			हाल FB_BLANK_POWERDOWN:
				custom.hsstrt = hsstrt2hw(par->htotal + 16);
				custom.hsstop = hsstop2hw(par->htotal + 16);
				custom.vsstrt = vsstrt2hw(par->vtotal + 4);
				custom.vsstop = vsstop2hw(par->vtotal + 4);
				अवरोध;
			पूर्ण
			अगर (!(par->beamcon0 & BMC0_VARBEAMEN)) अणु
				custom.htotal = htotal2hw(par->htotal);
				custom.vtotal = vtotal2hw(par->vtotal);
				custom.beamcon0 = BMC0_HARDDIS | BMC0_VARBEAMEN |
						  BMC0_VARVSYEN | BMC0_VARHSYEN | BMC0_VARCSYEN;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		custom.dmacon = DMAF_SETCLR | DMAF_RASTER | DMAF_SPRITE;
		red = red0;
		green = green0;
		blue = blue0;
		अगर (!IS_OCS) अणु
			custom.hsstrt = hsstrt2hw(par->hsstrt);
			custom.hsstop = hsstop2hw(par->hsstop);
			custom.vsstrt = vsstrt2hw(par->vsstrt);
			custom.vsstop = vsstop2hw(par->vsstop);
			custom.beamcon0 = par->beamcon0;
		पूर्ण
	पूर्ण
#अगर defined(CONFIG_FB_AMIGA_AGA)
	अगर (IS_AGA) अणु
		custom.bplcon3 = bplcon3;
		custom.color[0] = rgb2hw8_high(red, green, blue);
		custom.bplcon3 = bplcon3 | BPC3_LOCT;
		custom.color[0] = rgb2hw8_low(red, green, blue);
		custom.bplcon3 = bplcon3;
	पूर्ण अन्यथा
#पूर्ण_अगर
#अगर defined(CONFIG_FB_AMIGA_ECS)
	अगर (par->bplcon0 & BPC0_SHRES) अणु
		u_लघु color, mask;
		पूर्णांक i;

		mask = 0x3333;
		color = rgb2hw2(red, green, blue);
		क्रम (i = 12; i >= 0; i -= 4)
			custom.color[i] = ecs_palette[i] = (ecs_palette[i] & mask) | color;
		mask <<= 2; color >>= 2;
		क्रम (i = 3; i >= 0; i--)
			custom.color[i] = ecs_palette[i] = (ecs_palette[i] & mask) | color;
	पूर्ण अन्यथा
#पूर्ण_अगर
		custom.color[0] = rgb2hw4(red, green, blue);
	is_blanked = करो_blank > 0 ? करो_blank : 0;
पूर्ण

अटल पूर्णांक ami_get_fix_cursorinfo(काष्ठा fb_fix_cursorinfo *fix,
				  स्थिर काष्ठा amअगरb_par *par)
अणु
	fix->crsr_width = fix->crsr_xsize = par->crsr.width;
	fix->crsr_height = fix->crsr_ysize = par->crsr.height;
	fix->crsr_color1 = 17;
	fix->crsr_color2 = 18;
	वापस 0;
पूर्ण

अटल पूर्णांक ami_get_var_cursorinfo(काष्ठा fb_var_cursorinfo *var,
				  u_अक्षर __user *data,
				  स्थिर काष्ठा amअगरb_par *par)
अणु
	रेजिस्टर u_लघु *lspr, *sspr;
#अगर_घोषित __mc68000__
	रेजिस्टर u_दीर्घ datawords यंत्र ("d2");
#अन्यथा
	रेजिस्टर u_दीर्घ datawords;
#पूर्ण_अगर
	रेजिस्टर लघु delta;
	रेजिस्टर u_अक्षर color;
	लघु height, width, bits, words;
	पूर्णांक size, alloc;

	size = par->crsr.height * par->crsr.width;
	alloc = var->height * var->width;
	var->height = par->crsr.height;
	var->width = par->crsr.width;
	var->xspot = par->crsr.spot_x;
	var->yspot = par->crsr.spot_y;
	अगर (size > var->height * var->width)
		वापस -ENAMETOOLONG;
	delta = 1 << par->crsr.भ_शेषe;
	lspr = lofsprite + (delta << 1);
	अगर (par->bplcon0 & BPC0_LACE)
		sspr = shfsprite + (delta << 1);
	अन्यथा
		sspr = शून्य;
	क्रम (height = (लघु)var->height - 1; height >= 0; height--) अणु
		bits = 0; words = delta; datawords = 0;
		क्रम (width = (लघु)var->width - 1; width >= 0; width--) अणु
			अगर (bits == 0) अणु
				bits = 16; --words;
#अगर_घोषित __mc68000__
				यंत्र अस्थिर ("movew %1@(%3:w:2),%0 ; swap %0 ; movew %1@+,%0"
					: "=d" (datawords), "=a" (lspr) : "1" (lspr), "d" (delta));
#अन्यथा
				datawords = (*(lspr + delta) << 16) | (*lspr++);
#पूर्ण_अगर
			पूर्ण
			--bits;
#अगर_घोषित __mc68000__
			यंत्र अस्थिर (
				"clrb %0 ; swap %1 ; lslw #1,%1 ; roxlb #1,%0 ; "
				"swap %1 ; lslw #1,%1 ; roxlb #1,%0"
				: "=d" (color), "=d" (datawords) : "1" (datawords));
#अन्यथा
			color = (((datawords >> 30) & 2)
				 | ((datawords >> 15) & 1));
			datawords <<= 1;
#पूर्ण_अगर
			/* FIXME: check the वापस value + test the change */
			put_user(color, data++);
		पूर्ण
		अगर (bits > 0) अणु
			--words; ++lspr;
		पूर्ण
		जबतक (--words >= 0)
			++lspr;
#अगर_घोषित __mc68000__
		यंत्र अस्थिर ("lea %0@(%4:w:2),%0 ; tstl %1 ; jeq 1f ; exg %0,%1\n1:"
			: "=a" (lspr), "=a" (sspr) : "0" (lspr), "1" (sspr), "d" (delta));
#अन्यथा
		lspr += delta;
		अगर (sspr) अणु
			u_लघु *पंचांगp = lspr;
			lspr = sspr;
			sspr = पंचांगp;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ami_set_var_cursorinfo(काष्ठा fb_var_cursorinfo *var,
				  u_अक्षर __user *data, काष्ठा amअगरb_par *par)
अणु
	रेजिस्टर u_लघु *lspr, *sspr;
#अगर_घोषित __mc68000__
	रेजिस्टर u_दीर्घ datawords यंत्र ("d2");
#अन्यथा
	रेजिस्टर u_दीर्घ datawords;
#पूर्ण_अगर
	रेजिस्टर लघु delta;
	u_लघु भ_शेषe;
	लघु height, width, bits, words;

	अगर (!var->width)
		वापस -EINVAL;
	अन्यथा अगर (var->width <= 16)
		भ_शेषe = TAG_FMODE_1;
	अन्यथा अगर (var->width <= 32)
		भ_शेषe = TAG_FMODE_2;
	अन्यथा अगर (var->width <= 64)
		भ_शेषe = TAG_FMODE_4;
	अन्यथा
		वापस -EINVAL;
	अगर (भ_शेषe > maxभ_शेषe)
		वापस -EINVAL;
	अगर (!var->height)
		वापस -EINVAL;
	delta = 1 << भ_शेषe;
	lofsprite = shfsprite = (u_लघु *)spritememory;
	lspr = lofsprite + (delta << 1);
	अगर (par->bplcon0 & BPC0_LACE) अणु
		अगर (((var->height + 4) << भ_शेषe << 2) > SPRITEMEMSIZE)
			वापस -EINVAL;
		स_रखो(lspr, 0, (var->height + 4) << भ_शेषe << 2);
		shfsprite += ((var->height + 5)&-2) << भ_शेषe;
		sspr = shfsprite + (delta << 1);
	पूर्ण अन्यथा अणु
		अगर (((var->height + 2) << भ_शेषe << 2) > SPRITEMEMSIZE)
			वापस -EINVAL;
		स_रखो(lspr, 0, (var->height + 2) << भ_शेषe << 2);
		sspr = शून्य;
	पूर्ण
	क्रम (height = (लघु)var->height - 1; height >= 0; height--) अणु
		bits = 16; words = delta; datawords = 0;
		क्रम (width = (लघु)var->width - 1; width >= 0; width--) अणु
			अचिन्हित दीर्घ tdata = 0;
			/* FIXME: check the वापस value + test the change */
			get_user(tdata, data);
			data++;
#अगर_घोषित __mc68000__
			यंत्र अस्थिर (
				"lsrb #1,%2 ; roxlw #1,%0 ; swap %0 ; "
				"lsrb #1,%2 ; roxlw #1,%0 ; swap %0"
				: "=d" (datawords)
				: "0" (datawords), "d" (tdata));
#अन्यथा
			datawords = ((datawords << 1) & 0xfffefffe);
			datawords |= tdata & 1;
			datawords |= (tdata & 2) << (16 - 1);
#पूर्ण_अगर
			अगर (--bits == 0) अणु
				bits = 16; --words;
#अगर_घोषित __mc68000__
				यंत्र अस्थिर ("swap %2 ; movew %2,%0@(%3:w:2) ; swap %2 ; movew %2,%0@+"
					: "=a" (lspr) : "0" (lspr), "d" (datawords), "d" (delta));
#अन्यथा
				*(lspr + delta) = (u_लघु) (datawords >> 16);
				*lspr++ = (u_लघु) (datawords & 0xffff);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		अगर (bits < 16) अणु
			--words;
#अगर_घोषित __mc68000__
			यंत्र अस्थिर (
				"swap %2 ; lslw %4,%2 ; movew %2,%0@(%3:w:2) ; "
				"swap %2 ; lslw %4,%2 ; movew %2,%0@+"
				: "=a" (lspr) : "0" (lspr), "d" (datawords), "d" (delta), "d" (bits));
#अन्यथा
			*(lspr + delta) = (u_लघु) (datawords >> (16 + bits));
			*lspr++ = (u_लघु) ((datawords & 0x0000ffff) >> bits);
#पूर्ण_अगर
		पूर्ण
		जबतक (--words >= 0) अणु
#अगर_घोषित __mc68000__
			यंत्र अस्थिर ("moveql #0,%%d0 ; movew %%d0,%0@(%2:w:2) ; movew %%d0,%0@+"
				: "=a" (lspr) : "0" (lspr), "d" (delta) : "d0");
#अन्यथा
			*(lspr + delta) = 0;
			*lspr++ = 0;
#पूर्ण_अगर
		पूर्ण
#अगर_घोषित __mc68000__
		यंत्र अस्थिर ("lea %0@(%4:w:2),%0 ; tstl %1 ; jeq 1f ; exg %0,%1\n1:"
			: "=a" (lspr), "=a" (sspr) : "0" (lspr), "1" (sspr), "d" (delta));
#अन्यथा
		lspr += delta;
		अगर (sspr) अणु
			u_लघु *पंचांगp = lspr;
			lspr = sspr;
			sspr = पंचांगp;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	par->crsr.height = var->height;
	par->crsr.width = var->width;
	par->crsr.spot_x = var->xspot;
	par->crsr.spot_y = var->yspot;
	par->crsr.भ_शेषe = भ_शेषe;
	अगर (IS_AGA) अणु
		par->भ_शेषe &= ~(FMODE_SPAGEM | FMODE_SPR32);
		par->भ_शेषe |= sprfetchmode[भ_शेषe];
		custom.भ_शेषe = par->भ_शेषe;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ami_get_cursorstate(काष्ठा fb_cursorstate *state,
			       स्थिर काष्ठा amअगरb_par *par)
अणु
	state->xoffset = par->crsr.crsr_x;
	state->yoffset = par->crsr.crsr_y;
	state->mode = cursormode;
	वापस 0;
पूर्ण

अटल पूर्णांक ami_set_cursorstate(काष्ठा fb_cursorstate *state,
			       काष्ठा amअगरb_par *par)
अणु
	par->crsr.crsr_x = state->xoffset;
	par->crsr.crsr_y = state->yoffset;
	अगर ((cursormode = state->mode) == FB_CURSOR_OFF)
		cursorstate = -1;
	करो_cursor = 1;
	वापस 0;
पूर्ण

अटल व्योम ami_set_sprite(स्थिर काष्ठा amअगरb_par *par)
अणु
	copins *copl, *cops;
	u_लघु hs, vs, ve;
	u_दीर्घ pl, ps;
	लघु mx, my;

	cops = copdisplay.list[currentcop][0];
	copl = copdisplay.list[currentcop][1];
	ps = pl = ZTWO_PADDR(dummysprite);
	mx = par->crsr.crsr_x - par->crsr.spot_x;
	my = par->crsr.crsr_y - par->crsr.spot_y;
	अगर (!(par->vmode & FB_VMODE_YWRAP)) अणु
		mx -= par->xoffset;
		my -= par->yoffset;
	पूर्ण
	अगर (!is_blanked && cursorstate > 0 && par->crsr.height > 0 &&
	    mx > -(लघु)par->crsr.width && mx < par->xres &&
	    my > -(लघु)par->crsr.height && my < par->yres) अणु
		pl = ZTWO_PADDR(lofsprite);
		hs = par->diwstrt_h + (mx << par->clk_shअगरt) - 4;
		vs = par->diwstrt_v + (my << par->line_shअगरt);
		ve = vs + (par->crsr.height << par->line_shअगरt);
		अगर (par->bplcon0 & BPC0_LACE) अणु
			ps = ZTWO_PADDR(shfsprite);
			lofsprite[0] = spr2hw_pos(vs, hs);
			shfsprite[0] = spr2hw_pos(vs + 1, hs);
			अगर (mod2(vs)) अणु
				lofsprite[1 << par->crsr.भ_शेषe] = spr2hw_ctl(vs, hs, ve);
				shfsprite[1 << par->crsr.भ_शेषe] = spr2hw_ctl(vs + 1, hs, ve + 1);
				swap(pl, ps);
			पूर्ण अन्यथा अणु
				lofsprite[1 << par->crsr.भ_शेषe] = spr2hw_ctl(vs, hs, ve + 1);
				shfsprite[1 << par->crsr.भ_शेषe] = spr2hw_ctl(vs + 1, hs, ve);
			पूर्ण
		पूर्ण अन्यथा अणु
			lofsprite[0] = spr2hw_pos(vs, hs) | (IS_AGA && (par->भ_शेषe & FMODE_BSCAN2) ? 0x80 : 0);
			lofsprite[1 << par->crsr.भ_शेषe] = spr2hw_ctl(vs, hs, ve);
		पूर्ण
	पूर्ण
	copl[cop_spr0ptrh].w[1] = highw(pl);
	copl[cop_spr0ptrl].w[1] = loww(pl);
	अगर (par->bplcon0 & BPC0_LACE) अणु
		cops[cop_spr0ptrh].w[1] = highw(ps);
		cops[cop_spr0ptrl].w[1] = loww(ps);
	पूर्ण
पूर्ण


	/*
	 * Initialise the Copper Initialisation List
	 */

अटल व्योम __init ami_init_copper(व्योम)
अणु
	copins *cop = copdisplay.init;
	u_दीर्घ p;
	पूर्णांक i;

	अगर (!IS_OCS) अणु
		(cop++)->l = CMOVE(BPC0_COLOR | BPC0_SHRES | BPC0_ECSENA, bplcon0);
		(cop++)->l = CMOVE(0x0181, diwstrt);
		(cop++)->l = CMOVE(0x0281, diwstop);
		(cop++)->l = CMOVE(0x0000, diwhigh);
	पूर्ण अन्यथा
		(cop++)->l = CMOVE(BPC0_COLOR, bplcon0);
	p = ZTWO_PADDR(dummysprite);
	क्रम (i = 0; i < 8; i++) अणु
		(cop++)->l = CMOVE(0, spr[i].pos);
		(cop++)->l = CMOVE(highw(p), sprpt[i]);
		(cop++)->l = CMOVE2(loww(p), sprpt[i]);
	पूर्ण

	(cop++)->l = CMOVE(IF_SETCLR | IF_COPER, पूर्णांकreq);
	copdisplay.रुको = cop;
	(cop++)->l = CEND;
	(cop++)->l = CMOVE(0, copjmp2);
	cop->l = CEND;

	custom.cop1lc = (u_लघु *)ZTWO_PADDR(copdisplay.init);
	custom.copjmp1 = 0;
पूर्ण

अटल व्योम ami_reinit_copper(स्थिर काष्ठा amअगरb_par *par)
अणु
	copdisplay.init[cip_bplcon0].w[1] = ~(BPC0_BPU3 | BPC0_BPU2 | BPC0_BPU1 | BPC0_BPU0) & par->bplcon0;
	copdisplay.रुको->l = CWAIT(32, par->diwstrt_v - 4);
पूर्ण


	/*
	 * Rebuild the Copper List
	 *
	 * We only change the things that are not अटल
	 */

अटल व्योम ami_rebuild_copper(स्थिर काष्ठा amअगरb_par *par)
अणु
	copins *copl, *cops;
	u_लघु line, h_end1, h_end2;
	लघु i;
	u_दीर्घ p;

	अगर (IS_AGA && maxभ_शेषe + par->clk_shअगरt == 0)
		h_end1 = par->diwstrt_h - 64;
	अन्यथा
		h_end1 = par->htotal - 32;
	h_end2 = par->ddfstop + 64;

	ami_set_sprite(par);

	copl = copdisplay.rebuild[1];
	p = par->bplpt0;
	अगर (par->vmode & FB_VMODE_YWRAP) अणु
		अगर ((par->vyres - par->yoffset) != 1 || !mod2(par->diwstrt_v)) अणु
			अगर (par->yoffset > par->vyres - par->yres) अणु
				क्रम (i = 0; i < (लघु)par->bpp; i++, p += par->next_plane) अणु
					(copl++)->l = CMOVE(highw(p), bplpt[i]);
					(copl++)->l = CMOVE2(loww(p), bplpt[i]);
				पूर्ण
				line = par->diwstrt_v + ((par->vyres - par->yoffset) << par->line_shअगरt) - 1;
				जबतक (line >= 512) अणु
					(copl++)->l = CWAIT(h_end1, 510);
					line -= 512;
				पूर्ण
				अगर (line >= 510 && IS_AGA && maxभ_शेषe + par->clk_shअगरt == 0)
					(copl++)->l = CWAIT(h_end1, line);
				अन्यथा
					(copl++)->l = CWAIT(h_end2, line);
				p = par->bplpt0wrap;
			पूर्ण
		पूर्ण अन्यथा
			p = par->bplpt0wrap;
	पूर्ण
	क्रम (i = 0; i < (लघु)par->bpp; i++, p += par->next_plane) अणु
		(copl++)->l = CMOVE(highw(p), bplpt[i]);
		(copl++)->l = CMOVE2(loww(p), bplpt[i]);
	पूर्ण
	copl->l = CEND;

	अगर (par->bplcon0 & BPC0_LACE) अणु
		cops = copdisplay.rebuild[0];
		p = par->bplpt0;
		अगर (mod2(par->diwstrt_v))
			p -= par->next_line;
		अन्यथा
			p += par->next_line;
		अगर (par->vmode & FB_VMODE_YWRAP) अणु
			अगर ((par->vyres - par->yoffset) != 1 || mod2(par->diwstrt_v)) अणु
				अगर (par->yoffset > par->vyres - par->yres + 1) अणु
					क्रम (i = 0; i < (लघु)par->bpp; i++, p += par->next_plane) अणु
						(cops++)->l = CMOVE(highw(p), bplpt[i]);
						(cops++)->l = CMOVE2(loww(p), bplpt[i]);
					पूर्ण
					line = par->diwstrt_v + ((par->vyres - par->yoffset) << par->line_shअगरt) - 2;
					जबतक (line >= 512) अणु
						(cops++)->l = CWAIT(h_end1, 510);
						line -= 512;
					पूर्ण
					अगर (line > 510 && IS_AGA && maxभ_शेषe + par->clk_shअगरt == 0)
						(cops++)->l = CWAIT(h_end1, line);
					अन्यथा
						(cops++)->l = CWAIT(h_end2, line);
					p = par->bplpt0wrap;
					अगर (mod2(par->diwstrt_v + par->vyres -
					    par->yoffset))
						p -= par->next_line;
					अन्यथा
						p += par->next_line;
				पूर्ण
			पूर्ण अन्यथा
				p = par->bplpt0wrap - par->next_line;
		पूर्ण
		क्रम (i = 0; i < (लघु)par->bpp; i++, p += par->next_plane) अणु
			(cops++)->l = CMOVE(highw(p), bplpt[i]);
			(cops++)->l = CMOVE2(loww(p), bplpt[i]);
		पूर्ण
		cops->l = CEND;
	पूर्ण
पूर्ण


	/*
	 * Build the Copper List
	 */

अटल व्योम ami_build_copper(काष्ठा fb_info *info)
अणु
	काष्ठा amअगरb_par *par = info->par;
	copins *copl, *cops;
	u_दीर्घ p;

	currentcop = 1 - currentcop;

	copl = copdisplay.list[currentcop][1];

	(copl++)->l = CWAIT(0, 10);
	(copl++)->l = CMOVE(par->bplcon0, bplcon0);
	(copl++)->l = CMOVE(0, sprpt[0]);
	(copl++)->l = CMOVE2(0, sprpt[0]);

	अगर (par->bplcon0 & BPC0_LACE) अणु
		cops = copdisplay.list[currentcop][0];

		(cops++)->l = CWAIT(0, 10);
		(cops++)->l = CMOVE(par->bplcon0, bplcon0);
		(cops++)->l = CMOVE(0, sprpt[0]);
		(cops++)->l = CMOVE2(0, sprpt[0]);

		(copl++)->l = CMOVE(diwstrt2hw(par->diwstrt_h, par->diwstrt_v + 1), diwstrt);
		(copl++)->l = CMOVE(diwstop2hw(par->diwstop_h, par->diwstop_v + 1), diwstop);
		(cops++)->l = CMOVE(diwstrt2hw(par->diwstrt_h, par->diwstrt_v), diwstrt);
		(cops++)->l = CMOVE(diwstop2hw(par->diwstop_h, par->diwstop_v), diwstop);
		अगर (!IS_OCS) अणु
			(copl++)->l = CMOVE(diwhigh2hw(par->diwstrt_h, par->diwstrt_v + 1,
					    par->diwstop_h, par->diwstop_v + 1), diwhigh);
			(cops++)->l = CMOVE(diwhigh2hw(par->diwstrt_h, par->diwstrt_v,
					    par->diwstop_h, par->diwstop_v), diwhigh);
#अगर 0
			अगर (par->beamcon0 & BMC0_VARBEAMEN) अणु
				(copl++)->l = CMOVE(vtotal2hw(par->vtotal), vtotal);
				(copl++)->l = CMOVE(vbstrt2hw(par->vbstrt + 1), vbstrt);
				(copl++)->l = CMOVE(vbstop2hw(par->vbstop + 1), vbstop);
				(cops++)->l = CMOVE(vtotal2hw(par->vtotal), vtotal);
				(cops++)->l = CMOVE(vbstrt2hw(par->vbstrt), vbstrt);
				(cops++)->l = CMOVE(vbstop2hw(par->vbstop), vbstop);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
		p = ZTWO_PADDR(copdisplay.list[currentcop][0]);
		(copl++)->l = CMOVE(highw(p), cop2lc);
		(copl++)->l = CMOVE2(loww(p), cop2lc);
		p = ZTWO_PADDR(copdisplay.list[currentcop][1]);
		(cops++)->l = CMOVE(highw(p), cop2lc);
		(cops++)->l = CMOVE2(loww(p), cop2lc);
		copdisplay.rebuild[0] = cops;
	पूर्ण अन्यथा अणु
		(copl++)->l = CMOVE(diwstrt2hw(par->diwstrt_h, par->diwstrt_v), diwstrt);
		(copl++)->l = CMOVE(diwstop2hw(par->diwstop_h, par->diwstop_v), diwstop);
		अगर (!IS_OCS) अणु
			(copl++)->l = CMOVE(diwhigh2hw(par->diwstrt_h, par->diwstrt_v,
					    par->diwstop_h, par->diwstop_v), diwhigh);
#अगर 0
			अगर (par->beamcon0 & BMC0_VARBEAMEN) अणु
				(copl++)->l = CMOVE(vtotal2hw(par->vtotal), vtotal);
				(copl++)->l = CMOVE(vbstrt2hw(par->vbstrt), vbstrt);
				(copl++)->l = CMOVE(vbstop2hw(par->vbstop), vbstop);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	copdisplay.rebuild[1] = copl;

	ami_update_par(info);
	ami_rebuild_copper(info->par);
पूर्ण

#अगर_अघोषित MODULE
अटल व्योम __init amअगरb_setup_mcap(अक्षर *spec)
अणु
	अक्षर *p;
	पूर्णांक vmin, vmax, hmin, hmax;

	/* Format क्रम monitor capabilities is: <Vmin>;<Vmax>;<Hmin>;<Hmax>
	 * <V*> vertical freq. in Hz
	 * <H*> horizontal freq. in kHz
	 */

	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	vmin = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (vmin <= 0)
		वापस;
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	vmax = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (vmax <= 0 || vmax <= vmin)
		वापस;
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	hmin = 1000 * simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (hmin <= 0)
		वापस;
	अगर (!(p = strsep(&spec, "")) || !*p)
		वापस;
	hmax = 1000 * simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (hmax <= 0 || hmax <= hmin)
		वापस;

	amअगरb_hfmin = hmin;
	amअगरb_hfmax = hmax;
	amअगरb_vfmin = vmin;
	amअगरb_vfmax = vmax;
पूर्ण

अटल पूर्णांक __init amअगरb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		अगर (!म_भेद(this_opt, "inverse")) अणु
			fb_invert_cmaps();
		पूर्ण अन्यथा अगर (!म_भेद(this_opt, "ilbm"))
			amअगरb_ilbm = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "monitorcap:", 11))
			amअगरb_setup_mcap(this_opt + 11);
		अन्यथा अगर (!म_भेदन(this_opt, "fstart:", 7))
			min_fstrt = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		अन्यथा
			mode_option = this_opt;
	पूर्ण

	अगर (min_fstrt < 48)
		min_fstrt = 48;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक amअगरb_check_var(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	पूर्णांक err;
	काष्ठा amअगरb_par par;

	/* Validate wanted screen parameters */
	err = ami_decode_var(var, &par, info);
	अगर (err)
		वापस err;

	/* Encode (possibly rounded) screen parameters */
	ami_encode_var(var, &par);
	वापस 0;
पूर्ण


अटल पूर्णांक amअगरb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा amअगरb_par *par = info->par;
	पूर्णांक error;

	करो_vmode_pan = 0;
	करो_vmode_full = 0;

	/* Decode wanted screen parameters */
	error = ami_decode_var(&info->var, par, info);
	अगर (error)
		वापस error;

	/* Set new videomode */
	ami_build_copper(info);

	/* Set VBlank trigger */
	करो_vmode_full = 1;

	/* Update fix क्रम new screen parameters */
	अगर (par->bpp == 1) अणु
		info->fix.type = FB_TYPE_PACKED_PIXELS;
		info->fix.type_aux = 0;
	पूर्ण अन्यथा अगर (amअगरb_ilbm) अणु
		info->fix.type = FB_TYPE_INTERLEAVED_PLANES;
		info->fix.type_aux = par->next_line;
	पूर्ण अन्यथा अणु
		info->fix.type = FB_TYPE_PLANES;
		info->fix.type_aux = 0;
	पूर्ण
	info->fix.line_length = भाग8(upx(16 << maxभ_शेषe, par->vxres));

	अगर (par->vmode & FB_VMODE_YWRAP) अणु
		info->fix.ywrapstep = 1;
		info->fix.xpanstep = 0;
		info->fix.ypanstep = 0;
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YWRAP |
			FBINFO_READS_FAST; /* override SCROLL_REDRAW */
	पूर्ण अन्यथा अणु
		info->fix.ywrapstep = 0;
		अगर (par->vmode & FB_VMODE_SMOOTH_XPAN)
			info->fix.xpanstep = 1;
		अन्यथा
			info->fix.xpanstep = 16 << maxभ_शेषe;
		info->fix.ypanstep = 1;
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	पूर्ण
	वापस 0;
पूर्ण


	/*
	 * Set a single color रेजिस्टर. The values supplied are alपढ़ोy
	 * rounded करोwn to the hardware's capabilities (according to the
	 * entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
	 */

अटल पूर्णांक amअगरb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	स्थिर काष्ठा amअगरb_par *par = info->par;

	अगर (IS_AGA) अणु
		अगर (regno > 255)
			वापस 1;
	पूर्ण अन्यथा अगर (par->bplcon0 & BPC0_SHRES) अणु
		अगर (regno > 3)
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (regno > 31)
			वापस 1;
	पूर्ण
	red >>= 8;
	green >>= 8;
	blue >>= 8;
	अगर (!regno) अणु
		red0 = red;
		green0 = green;
		blue0 = blue;
	पूर्ण

	/*
	 * Update the corresponding Hardware Color Register, unless it's Color
	 * Register 0 and the screen is blanked.
	 *
	 * VBlank is चयनed off to protect bplcon3 or ecs_palette[] from
	 * being changed by ami_करो_blank() during the VBlank.
	 */

	अगर (regno || !is_blanked) अणु
#अगर defined(CONFIG_FB_AMIGA_AGA)
		अगर (IS_AGA) अणु
			u_लघु bplcon3 = par->bplcon3;
			VBlankOff();
			custom.bplcon3 = bplcon3 | (regno << 8 & 0xe000);
			custom.color[regno & 31] = rgb2hw8_high(red, green,
								blue);
			custom.bplcon3 = bplcon3 | (regno << 8 & 0xe000) |
					 BPC3_LOCT;
			custom.color[regno & 31] = rgb2hw8_low(red, green,
							       blue);
			custom.bplcon3 = bplcon3;
			VBlankOn();
		पूर्ण अन्यथा
#पूर्ण_अगर
#अगर defined(CONFIG_FB_AMIGA_ECS)
		अगर (par->bplcon0 & BPC0_SHRES) अणु
			u_लघु color, mask;
			पूर्णांक i;

			mask = 0x3333;
			color = rgb2hw2(red, green, blue);
			VBlankOff();
			क्रम (i = regno + 12; i >= (पूर्णांक)regno; i -= 4)
				custom.color[i] = ecs_palette[i] = (ecs_palette[i] & mask) | color;
			mask <<= 2; color >>= 2;
			regno = करोwn16(regno) + mul4(mod4(regno));
			क्रम (i = regno + 3; i >= (पूर्णांक)regno; i--)
				custom.color[i] = ecs_palette[i] = (ecs_palette[i] & mask) | color;
			VBlankOn();
		पूर्ण अन्यथा
#पूर्ण_अगर
			custom.color[regno] = rgb2hw4(red, green, blue);
	पूर्ण
	वापस 0;
पूर्ण


	/*
	 * Blank the display.
	 */

अटल पूर्णांक amअगरb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	करो_blank = blank ? blank : -1;

	वापस 0;
पूर्ण


	/*
	 * Pan or Wrap the Display
	 *
	 * This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
	 */

अटल पूर्णांक amअगरb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->yoffset < 0 ||
			var->yoffset >= info->var.yres_भव || var->xoffset)
				वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/*
		 * TODO: There will be problems when xpan!=1, so some columns
		 * on the right side will never be seen
		 */
		अगर (var->xoffset + info->var.xres >
		    upx(16 << maxभ_शेषe, info->var.xres_भव) ||
		    var->yoffset + info->var.yres > info->var.yres_भव)
			वापस -EINVAL;
	पूर्ण
	ami_pan_var(var, info);
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	अगर (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		info->var.vmode &= ~FB_VMODE_YWRAP;
	वापस 0;
पूर्ण


#अगर BITS_PER_LONG == 32
#घोषणा BYTES_PER_LONG	4
#घोषणा SHIFT_PER_LONG	5
#या_अगर BITS_PER_LONG == 64
#घोषणा BYTES_PER_LONG	8
#घोषणा SHIFT_PER_LONG	6
#अन्यथा
#घोषणा Please update me
#पूर्ण_अगर


	/*
	 *  Compose two values, using a biपंचांगask as decision value
	 *  This is equivalent to (a & mask) | (b & ~mask)
	 */

अटल अंतरभूत अचिन्हित दीर्घ comp(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b,
				 अचिन्हित दीर्घ mask)
अणु
	वापस ((a ^ b) & mask) ^ b;
पूर्ण


अटल अंतरभूत अचिन्हित दीर्घ xor(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b,
				अचिन्हित दीर्घ mask)
अणु
	वापस (a & mask) ^ b;
पूर्ण


	/*
	 *  Unaligned क्रमward bit copy using 32-bit or 64-bit memory accesses
	 */

अटल व्योम bitcpy(अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, स्थिर अचिन्हित दीर्घ *src,
		   पूर्णांक src_idx, u32 n)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक shअगरt = dst_idx - src_idx, left, right;
	अचिन्हित दीर्घ d0, d1;
	पूर्णांक m;

	अगर (!n)
		वापस;

	shअगरt = dst_idx - src_idx;
	first = ~0UL >> dst_idx;
	last = ~(~0UL >> ((dst_idx + n) % BITS_PER_LONG));

	अगर (!shअगरt) अणु
		// Same alignment क्रम source and dest

		अगर (dst_idx + n <= BITS_PER_LONG) अणु
			// Single word
			अगर (last)
				first &= last;
			*dst = comp(*src, *dst, first);
		पूर्ण अन्यथा अणु
			// Multiple destination words
			// Leading bits
			अगर (first) अणु
				*dst = comp(*src, *dst, first);
				dst++;
				src++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण

			// Main chunk
			n /= BITS_PER_LONG;
			जबतक (n >= 8) अणु
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				n -= 8;
			पूर्ण
			जबतक (n--)
				*dst++ = *src++;

			// Trailing bits
			अगर (last)
				*dst = comp(*src, *dst, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		// Dअगरferent alignment क्रम source and dest

		right = shअगरt & (BITS_PER_LONG - 1);
		left = -shअगरt & (BITS_PER_LONG - 1);

		अगर (dst_idx + n <= BITS_PER_LONG) अणु
			// Single destination word
			अगर (last)
				first &= last;
			अगर (shअगरt > 0) अणु
				// Single source word
				*dst = comp(*src >> right, *dst, first);
			पूर्ण अन्यथा अगर (src_idx + n <= BITS_PER_LONG) अणु
				// Single source word
				*dst = comp(*src << left, *dst, first);
			पूर्ण अन्यथा अणु
				// 2 source words
				d0 = *src++;
				d1 = *src;
				*dst = comp(d0 << left | d1 >> right, *dst,
					    first);
			पूर्ण
		पूर्ण अन्यथा अणु
			// Multiple destination words
			d0 = *src++;
			// Leading bits
			अगर (shअगरt > 0) अणु
				// Single source word
				*dst = comp(d0 >> right, *dst, first);
				dst++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = *src++;
				*dst = comp(d0 << left | d1 >> right, *dst,
					    first);
				d0 = d1;
				dst++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण

			// Main chunk
			m = n % BITS_PER_LONG;
			n /= BITS_PER_LONG;
			जबतक (n >= 4) अणु
				d1 = *src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = *src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = *src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
			पूर्ण

			// Trailing bits
			अगर (last) अणु
				अगर (m <= right) अणु
					// Single source word
					*dst = comp(d0 << left, *dst, last);
				पूर्ण अन्यथा अणु
					// 2 source words
					d1 = *src;
					*dst = comp(d0 << left | d1 >> right,
						    *dst, last);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


	/*
	 *  Unaligned reverse bit copy using 32-bit or 64-bit memory accesses
	 */

अटल व्योम bitcpy_rev(अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		       स्थिर अचिन्हित दीर्घ *src, पूर्णांक src_idx, u32 n)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक shअगरt = dst_idx - src_idx, left, right;
	अचिन्हित दीर्घ d0, d1;
	पूर्णांक m;

	अगर (!n)
		वापस;

	dst += (n - 1) / BITS_PER_LONG;
	src += (n - 1) / BITS_PER_LONG;
	अगर ((n - 1) % BITS_PER_LONG) अणु
		dst_idx += (n - 1) % BITS_PER_LONG;
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= BITS_PER_LONG - 1;
		src_idx += (n - 1) % BITS_PER_LONG;
		src += src_idx >> SHIFT_PER_LONG;
		src_idx &= BITS_PER_LONG - 1;
	पूर्ण

	shअगरt = dst_idx - src_idx;
	first = ~0UL << (BITS_PER_LONG - 1 - dst_idx);
	last = ~(~0UL << (BITS_PER_LONG - 1 - ((dst_idx - n) % BITS_PER_LONG)));

	अगर (!shअगरt) अणु
		// Same alignment क्रम source and dest

		अगर ((अचिन्हित दीर्घ)dst_idx + 1 >= n) अणु
			// Single word
			अगर (last)
				first &= last;
			*dst = comp(*src, *dst, first);
		पूर्ण अन्यथा अणु
			// Multiple destination words
			// Leading bits
			अगर (first) अणु
				*dst = comp(*src, *dst, first);
				dst--;
				src--;
				n -= dst_idx + 1;
			पूर्ण

			// Main chunk
			n /= BITS_PER_LONG;
			जबतक (n >= 8) अणु
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				n -= 8;
			पूर्ण
			जबतक (n--)
				*dst-- = *src--;

			// Trailing bits
			अगर (last)
				*dst = comp(*src, *dst, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		// Dअगरferent alignment क्रम source and dest

		right = shअगरt & (BITS_PER_LONG - 1);
		left = -shअगरt & (BITS_PER_LONG - 1);

		अगर ((अचिन्हित दीर्घ)dst_idx + 1 >= n) अणु
			// Single destination word
			अगर (last)
				first &= last;
			अगर (shअगरt < 0) अणु
				// Single source word
				*dst = comp(*src << left, *dst, first);
			पूर्ण अन्यथा अगर (1 + (अचिन्हित दीर्घ)src_idx >= n) अणु
				// Single source word
				*dst = comp(*src >> right, *dst, first);
			पूर्ण अन्यथा अणु
				// 2 source words
				d0 = *src--;
				d1 = *src;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
			पूर्ण
		पूर्ण अन्यथा अणु
			// Multiple destination words
			d0 = *src--;
			// Leading bits
			अगर (shअगरt < 0) अणु
				// Single source word
				*dst = comp(d0 << left, *dst, first);
				dst--;
				n -= dst_idx + 1;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = *src--;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
				d0 = d1;
				dst--;
				n -= dst_idx + 1;
			पूर्ण

			// Main chunk
			m = n % BITS_PER_LONG;
			n /= BITS_PER_LONG;
			जबतक (n >= 4) अणु
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
			पूर्ण

			// Trailing bits
			अगर (last) अणु
				अगर (m <= left) अणु
					// Single source word
					*dst = comp(d0 >> right, *dst, last);
				पूर्ण अन्यथा अणु
					// 2 source words
					d1 = *src;
					*dst = comp(d0 >> right | d1 << left,
						    *dst, last);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


	/*
	 *  Unaligned क्रमward inverting bit copy using 32-bit or 64-bit memory
	 *  accesses
	 */

अटल व्योम bitcpy_not(अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
		       स्थिर अचिन्हित दीर्घ *src, पूर्णांक src_idx, u32 n)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक shअगरt = dst_idx - src_idx, left, right;
	अचिन्हित दीर्घ d0, d1;
	पूर्णांक m;

	अगर (!n)
		वापस;

	shअगरt = dst_idx - src_idx;
	first = ~0UL >> dst_idx;
	last = ~(~0UL >> ((dst_idx + n) % BITS_PER_LONG));

	अगर (!shअगरt) अणु
		// Same alignment क्रम source and dest

		अगर (dst_idx + n <= BITS_PER_LONG) अणु
			// Single word
			अगर (last)
				first &= last;
			*dst = comp(~*src, *dst, first);
		पूर्ण अन्यथा अणु
			// Multiple destination words
			// Leading bits
			अगर (first) अणु
				*dst = comp(~*src, *dst, first);
				dst++;
				src++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण

			// Main chunk
			n /= BITS_PER_LONG;
			जबतक (n >= 8) अणु
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				*dst++ = ~*src++;
				n -= 8;
			पूर्ण
			जबतक (n--)
				*dst++ = ~*src++;

			// Trailing bits
			अगर (last)
				*dst = comp(~*src, *dst, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		// Dअगरferent alignment क्रम source and dest

		right = shअगरt & (BITS_PER_LONG - 1);
		left = -shअगरt & (BITS_PER_LONG - 1);

		अगर (dst_idx + n <= BITS_PER_LONG) अणु
			// Single destination word
			अगर (last)
				first &= last;
			अगर (shअगरt > 0) अणु
				// Single source word
				*dst = comp(~*src >> right, *dst, first);
			पूर्ण अन्यथा अगर (src_idx + n <= BITS_PER_LONG) अणु
				// Single source word
				*dst = comp(~*src << left, *dst, first);
			पूर्ण अन्यथा अणु
				// 2 source words
				d0 = ~*src++;
				d1 = ~*src;
				*dst = comp(d0 << left | d1 >> right, *dst,
					    first);
			पूर्ण
		पूर्ण अन्यथा अणु
			// Multiple destination words
			d0 = ~*src++;
			// Leading bits
			अगर (shअगरt > 0) अणु
				// Single source word
				*dst = comp(d0 >> right, *dst, first);
				dst++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण अन्यथा अणु
				// 2 source words
				d1 = ~*src++;
				*dst = comp(d0 << left | d1 >> right, *dst,
					    first);
				d0 = d1;
				dst++;
				n -= BITS_PER_LONG - dst_idx;
			पूर्ण

			// Main chunk
			m = n % BITS_PER_LONG;
			n /= BITS_PER_LONG;
			जबतक (n >= 4) अणु
				d1 = ~*src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = ~*src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = ~*src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				d1 = ~*src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
				n -= 4;
			पूर्ण
			जबतक (n--) अणु
				d1 = ~*src++;
				*dst++ = d0 << left | d1 >> right;
				d0 = d1;
			पूर्ण

			// Trailing bits
			अगर (last) अणु
				अगर (m <= right) अणु
					// Single source word
					*dst = comp(d0 << left, *dst, last);
				पूर्ण अन्यथा अणु
					// 2 source words
					d1 = ~*src;
					*dst = comp(d0 << left | d1 >> right,
						    *dst, last);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


	/*
	 *  Unaligned 32-bit pattern fill using 32/64-bit memory accesses
	 */

अटल व्योम bitfill32(अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, u32 pat, u32 n)
अणु
	अचिन्हित दीर्घ val = pat;
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

#अगर BITS_PER_LONG == 64
	val |= val << 32;
#पूर्ण_अगर

	first = ~0UL >> dst_idx;
	last = ~(~0UL >> ((dst_idx + n) % BITS_PER_LONG));

	अगर (dst_idx + n <= BITS_PER_LONG) अणु
		// Single word
		अगर (last)
			first &= last;
		*dst = comp(val, *dst, first);
	पूर्ण अन्यथा अणु
		// Multiple destination words
		// Leading bits
		अगर (first) अणु
			*dst = comp(val, *dst, first);
			dst++;
			n -= BITS_PER_LONG - dst_idx;
		पूर्ण

		// Main chunk
		n /= BITS_PER_LONG;
		जबतक (n >= 8) अणु
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			*dst++ = val;
			n -= 8;
		पूर्ण
		जबतक (n--)
			*dst++ = val;

		// Trailing bits
		अगर (last)
			*dst = comp(val, *dst, last);
	पूर्ण
पूर्ण


	/*
	 *  Unaligned 32-bit pattern xor using 32/64-bit memory accesses
	 */

अटल व्योम bitxor32(अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, u32 pat, u32 n)
अणु
	अचिन्हित दीर्घ val = pat;
	अचिन्हित दीर्घ first, last;

	अगर (!n)
		वापस;

#अगर BITS_PER_LONG == 64
	val |= val << 32;
#पूर्ण_अगर

	first = ~0UL >> dst_idx;
	last = ~(~0UL >> ((dst_idx + n) % BITS_PER_LONG));

	अगर (dst_idx + n <= BITS_PER_LONG) अणु
		// Single word
		अगर (last)
			first &= last;
		*dst = xor(val, *dst, first);
	पूर्ण अन्यथा अणु
		// Multiple destination words
		// Leading bits
		अगर (first) अणु
			*dst = xor(val, *dst, first);
			dst++;
			n -= BITS_PER_LONG - dst_idx;
		पूर्ण

		// Main chunk
		n /= BITS_PER_LONG;
		जबतक (n >= 4) अणु
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			n -= 4;
		पूर्ण
		जबतक (n--)
			*dst++ ^= val;

		// Trailing bits
		अगर (last)
			*dst = xor(val, *dst, last);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fill_one_line(पूर्णांक bpp, अचिन्हित दीर्घ next_plane,
				 अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, u32 n,
				 u32 color)
अणु
	जबतक (1) अणु
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= (BITS_PER_LONG - 1);
		bitfill32(dst, dst_idx, color & 1 ? ~0 : 0, n);
		अगर (!--bpp)
			अवरोध;
		color >>= 1;
		dst_idx += next_plane * 8;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम xor_one_line(पूर्णांक bpp, अचिन्हित दीर्घ next_plane,
				अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, u32 n,
				u32 color)
अणु
	जबतक (color) अणु
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= (BITS_PER_LONG - 1);
		bitxor32(dst, dst_idx, color & 1 ? ~0 : 0, n);
		अगर (!--bpp)
			अवरोध;
		color >>= 1;
		dst_idx += next_plane * 8;
	पूर्ण
पूर्ण


अटल व्योम amअगरb_fillrect(काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा amअगरb_par *par = info->par;
	पूर्णांक dst_idx, x2, y2;
	अचिन्हित दीर्घ *dst;
	u32 width, height;

	अगर (!rect->width || !rect->height)
		वापस;

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly.
	 * */
	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width = x2 - rect->dx;
	height = y2 - rect->dy;

	dst = (अचिन्हित दीर्घ *)
		((अचिन्हित दीर्घ)info->screen_base & ~(BYTES_PER_LONG - 1));
	dst_idx = ((अचिन्हित दीर्घ)info->screen_base & (BYTES_PER_LONG - 1)) * 8;
	dst_idx += rect->dy * par->next_line * 8 + rect->dx;
	जबतक (height--) अणु
		चयन (rect->rop) अणु
		हाल ROP_COPY:
			fill_one_line(info->var.bits_per_pixel,
				      par->next_plane, dst, dst_idx, width,
				      rect->color);
			अवरोध;

		हाल ROP_XOR:
			xor_one_line(info->var.bits_per_pixel, par->next_plane,
				     dst, dst_idx, width, rect->color);
			अवरोध;
		पूर्ण
		dst_idx += par->next_line * 8;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम copy_one_line(पूर्णांक bpp, अचिन्हित दीर्घ next_plane,
				 अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
				 अचिन्हित दीर्घ *src, पूर्णांक src_idx, u32 n)
अणु
	जबतक (1) अणु
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= (BITS_PER_LONG - 1);
		src += src_idx >> SHIFT_PER_LONG;
		src_idx &= (BITS_PER_LONG - 1);
		bitcpy(dst, dst_idx, src, src_idx, n);
		अगर (!--bpp)
			अवरोध;
		dst_idx += next_plane * 8;
		src_idx += next_plane * 8;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम copy_one_line_rev(पूर्णांक bpp, अचिन्हित दीर्घ next_plane,
				     अचिन्हित दीर्घ *dst, पूर्णांक dst_idx,
				     अचिन्हित दीर्घ *src, पूर्णांक src_idx, u32 n)
अणु
	जबतक (1) अणु
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= (BITS_PER_LONG - 1);
		src += src_idx >> SHIFT_PER_LONG;
		src_idx &= (BITS_PER_LONG - 1);
		bitcpy_rev(dst, dst_idx, src, src_idx, n);
		अगर (!--bpp)
			अवरोध;
		dst_idx += next_plane * 8;
		src_idx += next_plane * 8;
	पूर्ण
पूर्ण


अटल व्योम amअगरb_copyarea(काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा amअगरb_par *par = info->par;
	पूर्णांक x2, y2;
	u32 dx, dy, sx, sy, width, height;
	अचिन्हित दीर्घ *dst, *src;
	पूर्णांक dst_idx, src_idx;
	पूर्णांक rev_copy = 0;

	/* clip the destination */
	x2 = area->dx + area->width;
	y2 = area->dy + area->height;
	dx = area->dx > 0 ? area->dx : 0;
	dy = area->dy > 0 ? area->dy : 0;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width = x2 - dx;
	height = y2 - dy;

	अगर (area->sx + dx < area->dx || area->sy + dy < area->dy)
		वापस;

	/* update sx,sy */
	sx = area->sx + (dx - area->dx);
	sy = area->sy + (dy - area->dy);

	/* the source must be completely inside the भव screen */
	अगर (sx + width > info->var.xres_भव ||
			sy + height > info->var.yres_भव)
		वापस;

	अगर (dy > sy || (dy == sy && dx > sx)) अणु
		dy += height;
		sy += height;
		rev_copy = 1;
	पूर्ण
	dst = (अचिन्हित दीर्घ *)
		((अचिन्हित दीर्घ)info->screen_base & ~(BYTES_PER_LONG - 1));
	src = dst;
	dst_idx = ((अचिन्हित दीर्घ)info->screen_base & (BYTES_PER_LONG - 1)) * 8;
	src_idx = dst_idx;
	dst_idx += dy * par->next_line * 8 + dx;
	src_idx += sy * par->next_line * 8 + sx;
	अगर (rev_copy) अणु
		जबतक (height--) अणु
			dst_idx -= par->next_line * 8;
			src_idx -= par->next_line * 8;
			copy_one_line_rev(info->var.bits_per_pixel,
					  par->next_plane, dst, dst_idx, src,
					  src_idx, width);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (height--) अणु
			copy_one_line(info->var.bits_per_pixel,
				      par->next_plane, dst, dst_idx, src,
				      src_idx, width);
			dst_idx += par->next_line * 8;
			src_idx += par->next_line * 8;
		पूर्ण
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम expand_one_line(पूर्णांक bpp, अचिन्हित दीर्घ next_plane,
				   अचिन्हित दीर्घ *dst, पूर्णांक dst_idx, u32 n,
				   स्थिर u8 *data, u32 bgcolor, u32 fgcolor)
अणु
	स्थिर अचिन्हित दीर्घ *src;
	पूर्णांक src_idx;

	जबतक (1) अणु
		dst += dst_idx >> SHIFT_PER_LONG;
		dst_idx &= (BITS_PER_LONG - 1);
		अगर ((bgcolor ^ fgcolor) & 1) अणु
			src = (अचिन्हित दीर्घ *)
				((अचिन्हित दीर्घ)data & ~(BYTES_PER_LONG - 1));
			src_idx = ((अचिन्हित दीर्घ)data & (BYTES_PER_LONG - 1)) * 8;
			अगर (fgcolor & 1)
				bitcpy(dst, dst_idx, src, src_idx, n);
			अन्यथा
				bitcpy_not(dst, dst_idx, src, src_idx, n);
			/* set or clear */
		पूर्ण अन्यथा
			bitfill32(dst, dst_idx, fgcolor & 1 ? ~0 : 0, n);
		अगर (!--bpp)
			अवरोध;
		bgcolor >>= 1;
		fgcolor >>= 1;
		dst_idx += next_plane * 8;
	पूर्ण
पूर्ण


अटल व्योम amअगरb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा amअगरb_par *par = info->par;
	पूर्णांक x2, y2;
	अचिन्हित दीर्घ *dst;
	पूर्णांक dst_idx;
	स्थिर अक्षर *src;
	u32 dx, dy, width, height, pitch;

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly like we are
	 * करोing here.
	 */
	x2 = image->dx + image->width;
	y2 = image->dy + image->height;
	dx = image->dx;
	dy = image->dy;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width  = x2 - dx;
	height = y2 - dy;

	अगर (image->depth == 1) अणु
		dst = (अचिन्हित दीर्घ *)
			((अचिन्हित दीर्घ)info->screen_base & ~(BYTES_PER_LONG - 1));
		dst_idx = ((अचिन्हित दीर्घ)info->screen_base & (BYTES_PER_LONG - 1)) * 8;
		dst_idx += dy * par->next_line * 8 + dx;
		src = image->data;
		pitch = (image->width + 7) / 8;
		जबतक (height--) अणु
			expand_one_line(info->var.bits_per_pixel,
					par->next_plane, dst, dst_idx, width,
					src, image->bg_color,
					image->fg_color);
			dst_idx += par->next_line * 8;
			src += pitch;
		पूर्ण
	पूर्ण अन्यथा अणु
		c2p_planar(info->screen_base, image->data, dx, dy, width,
			   height, par->next_line, par->next_plane,
			   image->width, info->var.bits_per_pixel);
	पूर्ण
पूर्ण


	/*
	 * Amiga Frame Buffer Specअगरic ioctls
	 */

अटल पूर्णांक amअगरb_ioctl(काष्ठा fb_info *info,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	जोड़ अणु
		काष्ठा fb_fix_cursorinfo fix;
		काष्ठा fb_var_cursorinfo var;
		काष्ठा fb_cursorstate state;
	पूर्ण crsr;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक i;

	चयन (cmd) अणु
	हाल FBIOGET_FCURSORINFO:
		i = ami_get_fix_cursorinfo(&crsr.fix, info->par);
		अगर (i)
			वापस i;
		वापस copy_to_user(argp, &crsr.fix,
				    माप(crsr.fix)) ? -EFAULT : 0;

	हाल FBIOGET_VCURSORINFO:
		i = ami_get_var_cursorinfo(&crsr.var,
			((काष्ठा fb_var_cursorinfo __user *)arg)->data,
			info->par);
		अगर (i)
			वापस i;
		वापस copy_to_user(argp, &crsr.var,
				    माप(crsr.var)) ? -EFAULT : 0;

	हाल FBIOPUT_VCURSORINFO:
		अगर (copy_from_user(&crsr.var, argp, माप(crsr.var)))
			वापस -EFAULT;
		वापस ami_set_var_cursorinfo(&crsr.var,
			((काष्ठा fb_var_cursorinfo __user *)arg)->data,
			info->par);

	हाल FBIOGET_CURSORSTATE:
		i = ami_get_cursorstate(&crsr.state, info->par);
		अगर (i)
			वापस i;
		वापस copy_to_user(argp, &crsr.state,
				    माप(crsr.state)) ? -EFAULT : 0;

	हाल FBIOPUT_CURSORSTATE:
		अगर (copy_from_user(&crsr.state, argp, माप(crsr.state)))
			वापस -EFAULT;
		वापस ami_set_cursorstate(&crsr.state, info->par);
	पूर्ण
	वापस -EINVAL;
पूर्ण


	/*
	 * Flash the cursor (called by VBlank पूर्णांकerrupt)
	 */

अटल पूर्णांक flash_cursor(व्योम)
अणु
	अटल पूर्णांक cursorcount = 1;

	अगर (cursormode == FB_CURSOR_FLASH) अणु
		अगर (!--cursorcount) अणु
			cursorstate = -cursorstate;
			cursorcount = cursorrate;
			अगर (!is_blanked)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

	/*
	 * VBlank Display Interrupt
	 */

अटल irqवापस_t amअगरb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा amअगरb_par *par = dev_id;

	अगर (करो_vmode_pan || करो_vmode_full)
		ami_update_display(par);

	अगर (करो_vmode_full)
		ami_init_display(par);

	अगर (करो_vmode_pan) अणु
		flash_cursor();
		ami_rebuild_copper(par);
		करो_cursor = करो_vmode_pan = 0;
	पूर्ण अन्यथा अगर (करो_cursor) अणु
		flash_cursor();
		ami_set_sprite(par);
		करो_cursor = 0;
	पूर्ण अन्यथा अणु
		अगर (flash_cursor())
			ami_set_sprite(par);
	पूर्ण

	अगर (करो_blank) अणु
		ami_करो_blank(par);
		करो_blank = 0;
	पूर्ण

	अगर (करो_vmode_full) अणु
		ami_reinit_copper(par);
		करो_vmode_full = 0;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


अटल स्थिर काष्ठा fb_ops amअगरb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= amअगरb_check_var,
	.fb_set_par	= amअगरb_set_par,
	.fb_setcolreg	= amअगरb_setcolreg,
	.fb_blank	= amअगरb_blank,
	.fb_pan_display	= amअगरb_pan_display,
	.fb_fillrect	= amअगरb_fillrect,
	.fb_copyarea	= amअगरb_copyarea,
	.fb_imageblit	= amअगरb_imageblit,
	.fb_ioctl	= amअगरb_ioctl,
पूर्ण;


	/*
	 * Allocate, Clear and Align a Block of Chip Memory
	 */

अटल व्योम *aligned_chipptr;

अटल अंतरभूत u_दीर्घ __init chipalloc(u_दीर्घ size)
अणु
	aligned_chipptr = amiga_chip_alloc(size, "amifb [RAM]");
	अगर (!aligned_chipptr) अणु
		pr_err("amifb: No Chip RAM for frame buffer");
		वापस 0;
	पूर्ण
	स_रखो(aligned_chipptr, 0, size);
	वापस (u_दीर्घ)aligned_chipptr;
पूर्ण

अटल अंतरभूत व्योम chipमुक्त(व्योम)
अणु
	अगर (aligned_chipptr)
		amiga_chip_मुक्त(aligned_chipptr);
पूर्ण


	/*
	 * Initialisation
	 */

अटल पूर्णांक __init amअगरb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक tag, i, err = 0;
	u_दीर्घ chipptr;
	u_पूर्णांक deभ_शेषe;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("amifb", &option)) अणु
		amअगरb_video_off();
		वापस -ENODEV;
	पूर्ण
	amअगरb_setup(option);
#पूर्ण_अगर
	custom.dmacon = DMAF_ALL | DMAF_MASTER;

	info = framebuffer_alloc(माप(काष्ठा amअगरb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	म_नकल(info->fix.id, "Amiga ");
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	info->fix.accel = FB_ACCEL_AMIGABLITT;

	चयन (amiga_chipset) अणु
#अगर_घोषित CONFIG_FB_AMIGA_OCS
	हाल CS_OCS:
		म_जोड़ो(info->fix.id, "OCS");
शेष_chipset:
		chipset = TAG_OCS;
		maxdepth[TAG_SHRES] = 0;	/* OCS means no SHRES */
		maxdepth[TAG_HIRES] = 4;
		maxdepth[TAG_LORES] = 6;
		maxभ_शेषe = TAG_FMODE_1;
		deभ_शेषe = amiga_vblank == 50 ? DEFMODE_PAL : DEFMODE_NTSC;
		info->fix.smem_len = VIDEOMEMSIZE_OCS;
		अवरोध;
#पूर्ण_अगर /* CONFIG_FB_AMIGA_OCS */

#अगर_घोषित CONFIG_FB_AMIGA_ECS
	हाल CS_ECS:
		म_जोड़ो(info->fix.id, "ECS");
		chipset = TAG_ECS;
		maxdepth[TAG_SHRES] = 2;
		maxdepth[TAG_HIRES] = 4;
		maxdepth[TAG_LORES] = 6;
		maxभ_शेषe = TAG_FMODE_1;
		अगर (AMIGAHW_PRESENT(AMBER_FF))
			deभ_शेषe = amiga_vblank == 50 ? DEFMODE_AMBER_PAL
						     : DEFMODE_AMBER_NTSC;
		अन्यथा
			deभ_शेषe = amiga_vblank == 50 ? DEFMODE_PAL
						     : DEFMODE_NTSC;
		अगर (amiga_chip_avail() - CHIPRAM_SAFETY_LIMIT >
		    VIDEOMEMSIZE_ECS_2M)
			info->fix.smem_len = VIDEOMEMSIZE_ECS_2M;
		अन्यथा
			info->fix.smem_len = VIDEOMEMSIZE_ECS_1M;
		अवरोध;
#पूर्ण_अगर /* CONFIG_FB_AMIGA_ECS */

#अगर_घोषित CONFIG_FB_AMIGA_AGA
	हाल CS_AGA:
		म_जोड़ो(info->fix.id, "AGA");
		chipset = TAG_AGA;
		maxdepth[TAG_SHRES] = 8;
		maxdepth[TAG_HIRES] = 8;
		maxdepth[TAG_LORES] = 8;
		maxभ_शेषe = TAG_FMODE_4;
		deभ_शेषe = DEFMODE_AGA;
		अगर (amiga_chip_avail() - CHIPRAM_SAFETY_LIMIT >
		    VIDEOMEMSIZE_AGA_2M)
			info->fix.smem_len = VIDEOMEMSIZE_AGA_2M;
		अन्यथा
			info->fix.smem_len = VIDEOMEMSIZE_AGA_1M;
		अवरोध;
#पूर्ण_अगर /* CONFIG_FB_AMIGA_AGA */

	शेष:
#अगर_घोषित CONFIG_FB_AMIGA_OCS
		prपूर्णांकk("Unknown graphics chipset, defaulting to OCS\n");
		म_जोड़ो(info->fix.id, "Unknown");
		जाओ शेष_chipset;
#अन्यथा /* CONFIG_FB_AMIGA_OCS */
		err = -ENODEV;
		जाओ release;
#पूर्ण_अगर /* CONFIG_FB_AMIGA_OCS */
		अवरोध;
	पूर्ण

	/*
	 * Calculate the Pixel Clock Values क्रम this Machine
	 */

	अणु
	u_दीर्घ पंचांगp = DIVUL(200000000000ULL, amiga_eघड़ी);

	pixघड़ी[TAG_SHRES] = (पंचांगp + 4) / 8;	/* SHRES:  35 ns / 28 MHz */
	pixघड़ी[TAG_HIRES] = (पंचांगp + 2) / 4;	/* HIRES:  70 ns / 14 MHz */
	pixघड़ी[TAG_LORES] = (पंचांगp + 1) / 2;	/* LORES: 140 ns /  7 MHz */
	पूर्ण

	/*
	 * Replace the Tag Values with the Real Pixel Clock Values
	 */

	क्रम (i = 0; i < NUM_TOTAL_MODES; i++) अणु
		काष्ठा fb_videomode *mode = &ami_modedb[i];
		tag = mode->pixघड़ी;
		अगर (tag == TAG_SHRES || tag == TAG_HIRES || tag == TAG_LORES) अणु
			mode->pixघड़ी = pixघड़ी[tag];
		पूर्ण
	पूर्ण

	अगर (amअगरb_hfmin) अणु
		info->monspecs.hfmin = amअगरb_hfmin;
		info->monspecs.hfmax = amअगरb_hfmax;
		info->monspecs.vfmin = amअगरb_vfmin;
		info->monspecs.vfmax = amअगरb_vfmax;
	पूर्ण अन्यथा अणु
		/*
		 *  These are क्रम a typical Amiga monitor (e.g. A1960)
		 */
		info->monspecs.hfmin = 15000;
		info->monspecs.hfmax = 38000;
		info->monspecs.vfmin = 49;
		info->monspecs.vfmax = 90;
	पूर्ण

	info->fbops = &amअगरb_ops;
	info->flags = FBINFO_DEFAULT;
	info->device = &pdev->dev;

	अगर (!fb_find_mode(&info->var, info, mode_option, ami_modedb,
			  NUM_TOTAL_MODES, &ami_modedb[deभ_शेषe], 4)) अणु
		err = -EINVAL;
		जाओ release;
	पूर्ण

	fb_videomode_to_modelist(ami_modedb, NUM_TOTAL_MODES,
				 &info->modelist);

	round_करोwn_bpp = 0;
	chipptr = chipalloc(info->fix.smem_len + SPRITEMEMSIZE +
			    DUMMYSPRITEMEMSIZE + COPINITSIZE +
			    4 * COPLISTSIZE);
	अगर (!chipptr) अणु
		err = -ENOMEM;
		जाओ release;
	पूर्ण

	assignchunk(videomemory, u_दीर्घ, chipptr, info->fix.smem_len);
	assignchunk(spritememory, u_दीर्घ, chipptr, SPRITEMEMSIZE);
	assignchunk(dummysprite, u_लघु *, chipptr, DUMMYSPRITEMEMSIZE);
	assignchunk(copdisplay.init, copins *, chipptr, COPINITSIZE);
	assignchunk(copdisplay.list[0][0], copins *, chipptr, COPLISTSIZE);
	assignchunk(copdisplay.list[0][1], copins *, chipptr, COPLISTSIZE);
	assignchunk(copdisplay.list[1][0], copins *, chipptr, COPLISTSIZE);
	assignchunk(copdisplay.list[1][1], copins *, chipptr, COPLISTSIZE);

	/*
	 * access the videomem with ग_लिखोthrough cache
	 */
	info->fix.smem_start = (u_दीर्घ)ZTWO_PADDR(videomemory);
	videomemory = (u_दीर्घ)ioremap_wt(info->fix.smem_start,
					 info->fix.smem_len);
	अगर (!videomemory) अणु
		dev_warn(&pdev->dev,
			 "Unable to map videomem cached writethrough\n");
		info->screen_base = ZTWO_VADDR(info->fix.smem_start);
	पूर्ण अन्यथा
		info->screen_base = (अक्षर *)videomemory;

	स_रखो(dummysprite, 0, DUMMYSPRITEMEMSIZE);

	/*
	 * Make sure the Copper has something to करो
	 */
	ami_init_copper();

	/*
	 * Enable Display DMA
	 */
	custom.dmacon = DMAF_SETCLR | DMAF_MASTER | DMAF_RASTER | DMAF_COPPER |
			DMAF_BLITTER | DMAF_SPRITE;

	err = request_irq(IRQ_AMIGA_COPPER, amअगरb_पूर्णांकerrupt, 0,
			  "fb vertb handler", info->par);
	अगर (err)
		जाओ disable_dma;

	err = fb_alloc_cmap(&info->cmap, 1 << info->var.bits_per_pixel, 0);
	अगर (err)
		जाओ मुक्त_irq;

	platक्रमm_set_drvdata(pdev, info);

	err = रेजिस्टर_framebuffer(info);
	अगर (err)
		जाओ unset_drvdata;

	fb_info(info, "%s frame buffer device, using %dK of video memory\n",
		info->fix.id, info->fix.smem_len>>10);

	वापस 0;

unset_drvdata:
	fb_dealloc_cmap(&info->cmap);
मुक्त_irq:
	मुक्त_irq(IRQ_AMIGA_COPPER, info->par);
disable_dma:
	custom.dmacon = DMAF_ALL | DMAF_MASTER;
	अगर (videomemory)
		iounmap((व्योम *)videomemory);
	chipमुक्त();
release:
	framebuffer_release(info);
	वापस err;
पूर्ण


अटल पूर्णांक __निकास amअगरb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	मुक्त_irq(IRQ_AMIGA_COPPER, info->par);
	custom.dmacon = DMAF_ALL | DMAF_MASTER;
	अगर (videomemory)
		iounmap((व्योम *)videomemory);
	chipमुक्त();
	framebuffer_release(info);
	amअगरb_video_off();
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amअगरb_driver = अणु
	.हटाओ = __निकास_p(amअगरb_हटाओ),
	.driver   = अणु
		.name	= "amiga-video",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amअगरb_driver, amअगरb_probe);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-video");
