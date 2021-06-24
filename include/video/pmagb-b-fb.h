<शैली गुरु>
/*
 *	linux/include/video/pmagb-b-fb.h
 *
 *	TURBOchannel PMAGB-B Smart Frame Buffer (SFB) card support,
 *	Copyright (C) 1999, 2000, 2001 by
 *	Michael Engel <engel@unix-ag.org> and
 *	Karsten Merker <merker@linuxtag.org>
 *	Copyright (c) 2005  Maciej W. Rozycki
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License.  See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */

/* IOmem resource offsets.  */
#घोषणा PMAGB_B_ROM		0x000000	/* REX option ROM */
#घोषणा PMAGB_B_SFB		0x100000	/* SFB ASIC */
#घोषणा PMAGB_B_GP0		0x140000	/* general purpose output 0 */
#घोषणा PMAGB_B_GP1		0x180000	/* general purpose output 1 */
#घोषणा PMAGB_B_BT459		0x1c0000	/* Bt459 RAMDAC */
#घोषणा PMAGB_B_FBMEM		0x200000	/* frame buffer */
#घोषणा PMAGB_B_SIZE		0x400000	/* address space size */

/* IOmem रेजिस्टर offsets.  */
#घोषणा SFB_REG_VID_HOR		0x64		/* video horizontal setup */
#घोषणा SFB_REG_VID_VER		0x68		/* video vertical setup */
#घोषणा SFB_REG_VID_BASE	0x6c		/* video base address */
#घोषणा SFB_REG_TCCLK_COUNT	0x78		/* TURBOchannel घड़ी count */
#घोषणा SFB_REG_VIDCLK_COUNT	0x7c		/* video घड़ी count */

/* Video horizontal setup रेजिस्टर स्थिरants.  All bits are r/w.  */
#घोषणा SFB_VID_HOR_BP_SHIFT	0x15		/* back porch */
#घोषणा SFB_VID_HOR_BP_MASK	0x7f
#घोषणा SFB_VID_HOR_SYN_SHIFT	0x0e		/* sync pulse */
#घोषणा SFB_VID_HOR_SYN_MASK	0x7f
#घोषणा SFB_VID_HOR_FP_SHIFT	0x09		/* front porch */
#घोषणा SFB_VID_HOR_FP_MASK	0x1f
#घोषणा SFB_VID_HOR_PIX_SHIFT	0x00		/* active video */
#घोषणा SFB_VID_HOR_PIX_MASK	0x1ff

/* Video vertical setup रेजिस्टर स्थिरants.  All bits are r/w.  */
#घोषणा SFB_VID_VER_BP_SHIFT	0x16		/* back porch */
#घोषणा SFB_VID_VER_BP_MASK	0x3f
#घोषणा SFB_VID_VER_SYN_SHIFT	0x10		/* sync pulse */
#घोषणा SFB_VID_VER_SYN_MASK	0x3f
#घोषणा SFB_VID_VER_FP_SHIFT	0x0b		/* front porch */
#घोषणा SFB_VID_VER_FP_MASK	0x1f
#घोषणा SFB_VID_VER_SL_SHIFT	0x00		/* active scan lines */
#घोषणा SFB_VID_VER_SL_MASK	0x7ff

/* Video base address रेजिस्टर स्थिरants.  All bits are r/w.  */
#घोषणा SFB_VID_BASE_MASK	0x1ff		/* video base row address */

/* Bt459 रेजिस्टर offsets, byte-wide रेजिस्टरs.  */
#घोषणा BT459_ADDR_LO		0x0		/* address low */
#घोषणा BT459_ADDR_HI		0x4		/* address high */
#घोषणा BT459_DATA		0x8		/* data winकरोw रेजिस्टर */
#घोषणा BT459_CMAP		0xc		/* color map winकरोw रेजिस्टर */
