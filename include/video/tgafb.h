<शैली गुरु>
/*
 *  linux/drivers/video/tgafb.h -- DEC 21030 TGA frame buffer device
 *
 *  	Copyright (C) 1999,2000 Martin Lucina, Tom Zerucha
 *  
 *  $Id: tgafb.h,v 1.4.2.3 2000/04/04 06:44:56 mato Exp $
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#अगर_अघोषित TGAFB_H
#घोषणा TGAFB_H

/*
 * TGA hardware description (minimal)
 */

#घोषणा TGA_TYPE_8PLANE			0
#घोषणा TGA_TYPE_24PLANE		1
#घोषणा TGA_TYPE_24PLUSZ		3

/*
 * Offsets within Memory Space
 */

#घोषणा	TGA_ROM_OFFSET			0x0000000
#घोषणा	TGA_REGS_OFFSET			0x0100000
#घोषणा	TGA_8PLANE_FB_OFFSET		0x0200000
#घोषणा	TGA_24PLANE_FB_OFFSET		0x0804000
#घोषणा	TGA_24PLUSZ_FB_OFFSET		0x1004000

#घोषणा TGA_FOREGROUND_REG		0x0020
#घोषणा TGA_BACKGROUND_REG		0x0024
#घोषणा	TGA_PLANEMASK_REG		0x0028
#घोषणा TGA_PIXELMASK_ONESHOT_REG	0x002c
#घोषणा	TGA_MODE_REG			0x0030
#घोषणा	TGA_RASTEROP_REG		0x0034
#घोषणा	TGA_PIXELSHIFT_REG		0x0038
#घोषणा	TGA_DEEP_REG			0x0050
#घोषणा	TGA_START_REG			0x0054
#घोषणा	TGA_PIXELMASK_REG		0x005c
#घोषणा	TGA_CURSOR_BASE_REG		0x0060
#घोषणा	TGA_HORIZ_REG			0x0064
#घोषणा	TGA_VERT_REG			0x0068
#घोषणा	TGA_BASE_ADDR_REG		0x006c
#घोषणा	TGA_VALID_REG			0x0070
#घोषणा	TGA_CURSOR_XY_REG		0x0074
#घोषणा	TGA_INTR_STAT_REG		0x007c
#घोषणा TGA_DATA_REG			0x0080
#घोषणा	TGA_RAMDAC_SETUP_REG		0x00c0
#घोषणा	TGA_BLOCK_COLOR0_REG		0x0140
#घोषणा	TGA_BLOCK_COLOR1_REG		0x0144
#घोषणा	TGA_BLOCK_COLOR2_REG		0x0148
#घोषणा	TGA_BLOCK_COLOR3_REG		0x014c
#घोषणा	TGA_BLOCK_COLOR4_REG		0x0150
#घोषणा	TGA_BLOCK_COLOR5_REG		0x0154
#घोषणा	TGA_BLOCK_COLOR6_REG		0x0158
#घोषणा	TGA_BLOCK_COLOR7_REG		0x015c
#घोषणा TGA_COPY64_SRC			0x0160
#घोषणा TGA_COPY64_DST			0x0164
#घोषणा	TGA_CLOCK_REG			0x01e8
#घोषणा	TGA_RAMDAC_REG			0x01f0
#घोषणा	TGA_CMD_STAT_REG		0x01f8


/* 
 * Useful defines क्रम managing the रेजिस्टरs
 */

#घोषणा TGA_HORIZ_ODD			0x80000000
#घोषणा TGA_HORIZ_POLARITY		0x40000000
#घोषणा TGA_HORIZ_ACT_MSB		0x30000000
#घोषणा TGA_HORIZ_BP			0x0fe00000
#घोषणा TGA_HORIZ_SYNC			0x001fc000
#घोषणा TGA_HORIZ_FP			0x00007c00
#घोषणा TGA_HORIZ_ACT_LSB		0x000001ff

#घोषणा TGA_VERT_SE			0x80000000
#घोषणा TGA_VERT_POLARITY		0x40000000
#घोषणा TGA_VERT_RESERVED		0x30000000
#घोषणा TGA_VERT_BP			0x0fc00000
#घोषणा TGA_VERT_SYNC			0x003f0000
#घोषणा TGA_VERT_FP			0x0000f800
#घोषणा TGA_VERT_ACTIVE			0x000007ff

#घोषणा TGA_VALID_VIDEO			0x01
#घोषणा TGA_VALID_BLANK			0x02
#घोषणा TGA_VALID_CURSOR		0x04

#घोषणा TGA_MODE_SBM_8BPP		0x000
#घोषणा TGA_MODE_SBM_24BPP		0x300

#घोषणा TGA_MODE_SIMPLE			0x00
#घोषणा TGA_MODE_SIMPLEZ		0x10
#घोषणा TGA_MODE_OPAQUE_STIPPLE		0x01
#घोषणा TGA_MODE_OPAQUE_FILL		0x21
#घोषणा TGA_MODE_TRANSPARENT_STIPPLE	0x03
#घोषणा TGA_MODE_TRANSPARENT_FILL	0x23
#घोषणा TGA_MODE_BLOCK_STIPPLE		0x0d
#घोषणा TGA_MODE_BLOCK_FILL		0x2d
#घोषणा TGA_MODE_COPY			0x07
#घोषणा TGA_MODE_DMA_READ_COPY_ND	0x17
#घोषणा TGA_MODE_DMA_READ_COPY_D	0x37
#घोषणा TGA_MODE_DMA_WRITE_COPY		0x1f


/*
 * Useful defines क्रम managing the ICS1562 PLL घड़ी
 */

#घोषणा TGA_PLL_BASE_FREQ 		14318		/* .18 */
#घोषणा TGA_PLL_MAX_FREQ 		230000


/*
 * Useful defines क्रम managing the BT485 on the 8-plane TGA
 */

#घोषणा	BT485_READ_BIT			0x01
#घोषणा	BT485_WRITE_BIT			0x00

#घोषणा	BT485_ADDR_PAL_WRITE		0x00
#घोषणा	BT485_DATA_PAL			0x02
#घोषणा	BT485_PIXEL_MASK		0x04
#घोषणा	BT485_ADDR_PAL_READ		0x06
#घोषणा	BT485_ADDR_CUR_WRITE		0x08
#घोषणा	BT485_DATA_CUR			0x0a
#घोषणा	BT485_CMD_0			0x0c
#घोषणा	BT485_ADDR_CUR_READ		0x0e
#घोषणा	BT485_CMD_1			0x10
#घोषणा	BT485_CMD_2			0x12
#घोषणा	BT485_STATUS			0x14
#घोषणा	BT485_CMD_3			0x14
#घोषणा	BT485_CUR_RAM			0x16
#घोषणा	BT485_CUR_LOW_X			0x18
#घोषणा	BT485_CUR_HIGH_X		0x1a
#घोषणा	BT485_CUR_LOW_Y			0x1c
#घोषणा	BT485_CUR_HIGH_Y		0x1e


/*
 * Useful defines क्रम managing the BT463 on the 24-plane TGAs/SFB+s
 */

#घोषणा	BT463_ADDR_LO		0x0
#घोषणा	BT463_ADDR_HI		0x1
#घोषणा	BT463_REG_ACC		0x2
#घोषणा	BT463_PALETTE		0x3

#घोषणा	BT463_CUR_CLR_0		0x0100
#घोषणा	BT463_CUR_CLR_1		0x0101

#घोषणा	BT463_CMD_REG_0		0x0201
#घोषणा	BT463_CMD_REG_1		0x0202
#घोषणा	BT463_CMD_REG_2		0x0203

#घोषणा	BT463_READ_MASK_0	0x0205
#घोषणा	BT463_READ_MASK_1	0x0206
#घोषणा	BT463_READ_MASK_2	0x0207
#घोषणा	BT463_READ_MASK_3	0x0208

#घोषणा	BT463_BLINK_MASK_0	0x0209
#घोषणा	BT463_BLINK_MASK_1	0x020a
#घोषणा	BT463_BLINK_MASK_2	0x020b
#घोषणा	BT463_BLINK_MASK_3	0x020c

#घोषणा	BT463_WINDOW_TYPE_BASE	0x0300

/*
 * Useful defines क्रम managing the BT459 on the 8-plane SFB+s
 */

#घोषणा	BT459_ADDR_LO		0x0
#घोषणा	BT459_ADDR_HI		0x1
#घोषणा	BT459_REG_ACC		0x2
#घोषणा	BT459_PALETTE		0x3

#घोषणा	BT459_CUR_CLR_1		0x0181
#घोषणा	BT459_CUR_CLR_2		0x0182
#घोषणा	BT459_CUR_CLR_3		0x0183

#घोषणा	BT459_CMD_REG_0		0x0201
#घोषणा	BT459_CMD_REG_1		0x0202
#घोषणा	BT459_CMD_REG_2		0x0203

#घोषणा	BT459_READ_MASK		0x0204

#घोषणा	BT459_BLINK_MASK	0x0206

#घोषणा	BT459_CUR_CMD_REG	0x0300

/*
 * The framebuffer driver निजी data.
 */

काष्ठा tga_par अणु
	/* PCI/TC device.  */
	काष्ठा device *dev;

	/* Device dependent inक्रमmation.  */
	व्योम __iomem *tga_mem_base;
	व्योम __iomem *tga_fb_base;
	व्योम __iomem *tga_regs_base;
	u8 tga_type;				/* TGA_TYPE_XXX */
	u8 tga_chip_rev;			/* dc21030 revision */

	/* Remember blank mode.  */
	u8 vesa_blanked;

	/* Define the video mode.  */
	u32 xres, yres;			/* resolution in pixels */
	u32 htimings;			/* horizontal timing रेजिस्टर */
	u32 vtimings;			/* vertical timing रेजिस्टर */
	u32 pll_freq;			/* pixघड़ी in mhz */
	u32 bits_per_pixel;		/* bits per pixel */
	u32 sync_on_green;		/* set अगर sync is on green */
	u32 palette[16];
पूर्ण;


/*
 * Macros क्रम पढ़ोing/writing TGA and RAMDAC रेजिस्टरs
 */

अटल अंतरभूत व्योम
TGA_WRITE_REG(काष्ठा tga_par *par, u32 v, u32 r)
अणु
	ग_लिखोl(v, par->tga_regs_base +r);
पूर्ण

अटल अंतरभूत u32
TGA_READ_REG(काष्ठा tga_par *par, u32 r)
अणु
	वापस पढ़ोl(par->tga_regs_base +r);
पूर्ण

अटल अंतरभूत व्योम
BT485_WRITE(काष्ठा tga_par *par, u8 v, u8 r)
अणु
	TGA_WRITE_REG(par, r, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, v | (r << 8), TGA_RAMDAC_REG);
पूर्ण

अटल अंतरभूत व्योम
BT463_LOAD_ADDR(काष्ठा tga_par *par, u16 a)
अणु
	TGA_WRITE_REG(par, BT463_ADDR_LO<<2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, (BT463_ADDR_LO<<10) | (a & 0xff), TGA_RAMDAC_REG);
	TGA_WRITE_REG(par, BT463_ADDR_HI<<2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, (BT463_ADDR_HI<<10) | (a >> 8), TGA_RAMDAC_REG);
पूर्ण

अटल अंतरभूत व्योम
BT463_WRITE(काष्ठा tga_par *par, u32 m, u16 a, u8 v)
अणु
	BT463_LOAD_ADDR(par, a);
	TGA_WRITE_REG(par, m << 2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, m << 10 | v, TGA_RAMDAC_REG);
पूर्ण

अटल अंतरभूत व्योम
BT459_LOAD_ADDR(काष्ठा tga_par *par, u16 a)
अणु
	TGA_WRITE_REG(par, BT459_ADDR_LO << 2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, a & 0xff, TGA_RAMDAC_REG);
	TGA_WRITE_REG(par, BT459_ADDR_HI << 2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, a >> 8, TGA_RAMDAC_REG);
पूर्ण

अटल अंतरभूत व्योम
BT459_WRITE(काष्ठा tga_par *par, u32 m, u16 a, u8 v)
अणु
	BT459_LOAD_ADDR(par, a);
	TGA_WRITE_REG(par, m << 2, TGA_RAMDAC_SETUP_REG);
	TGA_WRITE_REG(par, v, TGA_RAMDAC_REG);
पूर्ण

#पूर्ण_अगर /* TGAFB_H */
