<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/video/mmp/hw/mmp_ctrl.h
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors:  Guoqing Li <ligq@marvell.com>
 *          Lisa Du <cldu@marvell.com>
 *          Zhou Zhu <zzhu3@marvell.com>
 */

#अगर_अघोषित _MMP_CTRL_H_
#घोषणा _MMP_CTRL_H_

#समावेश <video/mmp_disp.h>

/* ------------< LCD रेजिस्टर >------------ */
काष्ठा lcd_regs अणु
/* TV patch रेजिस्टर क्रम MMP2 */
/* 32 bit		TV Video Frame0 Y Starting Address */
#घोषणा LCD_TVD_START_ADDR_Y0			(0x0000)
/* 32 bit		TV Video Frame0 U Starting Address */
#घोषणा LCD_TVD_START_ADDR_U0			(0x0004)
/* 32 bit		TV Video Frame0 V Starting Address */
#घोषणा LCD_TVD_START_ADDR_V0			(0x0008)
/* 32 bit		TV Video Frame0 Command Starting Address */
#घोषणा LCD_TVD_START_ADDR_C0			(0x000C)
/* 32 bit		TV Video Frame1 Y Starting Address Register*/
#घोषणा LCD_TVD_START_ADDR_Y1			(0x0010)
/* 32 bit		TV Video Frame1 U Starting Address Register*/
#घोषणा LCD_TVD_START_ADDR_U1			(0x0014)
/* 32 bit		TV Video Frame1 V Starting Address Register*/
#घोषणा LCD_TVD_START_ADDR_V1			(0x0018)
/* 32 bit		TV Video Frame1 Command Starting Address Register*/
#घोषणा LCD_TVD_START_ADDR_C1			(0x001C)
/* 32 bit		TV Video Y andC Line Length(Pitch)Register*/
#घोषणा LCD_TVD_PITCH_YC			(0x0020)
/* 32 bit		TV Video U andV Line Length(Pitch)Register*/
#घोषणा LCD_TVD_PITCH_UV			(0x0024)
/* 32 bit	  TV Video Starting Poपूर्णांक on Screen Register*/
#घोषणा LCD_TVD_OVSA_HPXL_VLN			(0x0028)
/* 32 bit		TV Video Source Size Register*/
#घोषणा LCD_TVD_HPXL_VLN			(0x002C)
/* 32 bit	  TV Video Destination Size (After Zooming)Register*/
#घोषणा LCD_TVDZM_HPXL_VLN			(0x0030)
	u32 v_y0;
	u32 v_u0;
	u32 v_v0;
	u32 v_c0;
	u32 v_y1;
	u32 v_u1;
	u32 v_v1;
	u32 v_c1;
	u32 v_pitch_yc;		/* Video Y and C Line Length (Pitch) */
	u32 v_pitch_uv;		/* Video U and V Line Length (Pitch) */
	u32 v_start;		/* Video Starting Poपूर्णांक on Screen */
	u32 v_size;			/* Video Source Size */
	u32 v_size_z;		/* Video Destination Size (After Zooming) */

/* 32 bit	   TV Graphic Frame 0 Starting Address Register*/
#घोषणा LCD_TVG_START_ADDR0				(0x0034)
/* 32 bit	  TV Graphic Frame 1 Starting Address Register*/
#घोषणा LCD_TVG_START_ADDR1				(0x0038)
/* 32 bit		TV Graphic Line Length(Pitch)Register*/
#घोषणा LCD_TVG_PITCH					(0x003C)
/* 32 bit		TV Graphic Starting Poपूर्णांक on Screen Register*/
#घोषणा LCD_TVG_OVSA_HPXL_VLN				(0x0040)
/* 32 bit		TV Graphic Source Size Register*/
#घोषणा LCD_TVG_HPXL_VLN				(0x0044)
/* 32 bit		TV Graphic Destination size (after Zooming)Register*/
#घोषणा LCD_TVGZM_HPXL_VLN				(0x0048)
	u32 g_0;			/* Graphic Frame 0/1 Starting Address */
	u32 g_1;
	u32 g_pitch;		/* Graphic Line Length (Pitch) */
	u32 g_start;		/* Graphic Starting Poपूर्णांक on Screen */
	u32 g_size;			/* Graphic Source Size */
	u32 g_size_z;		/* Graphic Destination Size (After Zooming) */

/* 32 bit	  TV Hardware Cursor Starting Poपूर्णांक on screen Register*/
#घोषणा LCD_TVC_OVSA_HPXL_VLN				(0x004C)
/* 32 bit		TV Hardware Cursor Size Register */
#घोषणा LCD_TVC_HPXL_VLN				(0x0050)
	u32 hc_start;			/* Hardware Cursor */
	u32 hc_size;			/* Hardware Cursor */

/* 32 bit		TV Total Screen Size Register*/
#घोषणा LCD_TV_V_H_TOTAL				(0x0054)
/* 32 bit		TV Screen Active Size Register*/
#घोषणा LCD_TV_V_H_ACTIVE				(0x0058)
/* 32 bit		TV Screen Horizontal Porch Register*/
#घोषणा LCD_TV_H_PORCH					(0x005C)
/* 32 bit		TV Screen Vertical Porch Register*/
#घोषणा LCD_TV_V_PORCH					(0x0060)
	u32 screen_size;		/* Screen Total Size */
	u32 screen_active;		/* Screen Active Size */
	u32 screen_h_porch;		/* Screen Horizontal Porch */
	u32 screen_v_porch;		/* Screen Vertical Porch */

/* 32 bit		TV Screen Blank Color Register*/
#घोषणा LCD_TV_BLANKCOLOR				(0x0064)
/* 32 bit		TV Hardware Cursor Color1 Register*/
#घोषणा LCD_TV_ALPHA_COLOR1				(0x0068)
/* 32 bit		TV Hardware Cursor Color2 Register*/
#घोषणा LCD_TV_ALPHA_COLOR2				(0x006C)
	u32 blank_color;		/* Screen Blank Color */
	u32 hc_Alpha_color1;	/* Hardware Cursor Color1 */
	u32 hc_Alpha_color2;	/* Hardware Cursor Color2 */

/* 32 bit		TV Video Y Color Key Control*/
#घोषणा LCD_TV_COLORKEY_Y				(0x0070)
/* 32 bit		TV Video U Color Key Control*/
#घोषणा LCD_TV_COLORKEY_U				(0x0074)
/* 32 bit		TV Video V Color Key Control*/
#घोषणा LCD_TV_COLORKEY_V				(0x0078)
	u32 v_colorkey_y;		/* Video Y Color Key Control */
	u32 v_colorkey_u;		/* Video U Color Key Control */
	u32 v_colorkey_v;		/* Video V Color Key Control */

/* 32 bit		TV VSYNC PulsePixel Edge Control Register*/
#घोषणा LCD_TV_SEPXLCNT					(0x007C)
	u32 vsync_ctrl;			/* VSYNC PulsePixel Edge Control */
पूर्ण;

#घोषणा पूर्णांकf_ctrl(id)		((id) ? (((id) & 1) ? LCD_TVIF_CTRL : \
				LCD_DUMB2_CTRL) : LCD_SPU_DUMB_CTRL)
#घोषणा dma_ctrl0(id)	   ((id) ? (((id) & 1) ? LCD_TV_CTRL0 : \
				LCD_PN2_CTRL0) : LCD_SPU_DMA_CTRL0)
#घोषणा dma_ctrl1(id)	   ((id) ? (((id) & 1) ? LCD_TV_CTRL1 : \
				LCD_PN2_CTRL1) : LCD_SPU_DMA_CTRL1)
#घोषणा dma_ctrl(ctrl1, id)	 (ctrl1 ? dma_ctrl1(id) : dma_ctrl0(id))

/* 32 bit		TV Path DMA Control 0*/
#घोषणा LCD_TV_CTRL0					(0x0080)
/* 32 bit		TV Path DMA Control 1*/
#घोषणा LCD_TV_CTRL1					(0x0084)
/* 32 bit		TV Path Video Contrast*/
#घोषणा LCD_TV_CONTRAST					(0x0088)
/* 32 bit		TV Path Video Saturation*/
#घोषणा LCD_TV_SATURATION				(0x008C)
/* 32 bit		TV Path Video Hue Adjust*/
#घोषणा LCD_TV_CBSH_HUE					(0x0090)
/* 32 bit TV Path TVIF Control	Register */
#घोषणा LCD_TVIF_CTRL					(0x0094)
#घोषणा TV_VBLNK_VALID_EN				(1 << 12)

/* 32 bit TV Path I/O Pad Control*/
#घोषणा LCD_TVIOPAD_CTRL				(0x0098)
/* 32 bit TV Path Cloc	Divider  */
#घोषणा LCD_TCLK_DIV					(0x009C)

#घोषणा LCD_SCLK(path) ((PATH_PN == path->id) ? LCD_CFG_SCLK_DIV :\
	((PATH_TV == path->id) ? LCD_TCLK_DIV : LCD_PN2_SCLK_DIV))
#घोषणा पूर्णांकf_rbswap_ctrl(id)	((id) ? (((id) & 1) ? LCD_TVIF_CTRL : \
				PN2_IOPAD_CONTROL) : LCD_TOP_CTRL)

/* dither configure */
#घोषणा LCD_DITHER_CTRL				(0x00A0)

#घोषणा DITHER_TBL_INDEX_SEL(s)		((s) << 16)
#घोषणा DITHER_MODE2(m)				((m) << 12)
#घोषणा DITHER_MODE2_SHIFT			(12)
#घोषणा DITHER_4X8_EN2				(1 << 9)
#घोषणा DITHER_4X8_EN2_SHIFT		(9)
#घोषणा DITHER_EN2					(1 << 8)
#घोषणा DITHER_MODE1(m)				((m) << 4)
#घोषणा DITHER_MODE1_SHIFT			(4)
#घोषणा DITHER_4X8_EN1				(1 << 1)
#घोषणा DITHER_4X8_EN1_SHIFT		(1)
#घोषणा DITHER_EN1					(1)

/* dither table data was fixed by video bpp of input and output*/
#घोषणा DITHER_TB_4X4_INDEX0		(0x3b19f7d5)
#घोषणा DITHER_TB_4X4_INDEX1		(0x082ac4e6)
#घोषणा DITHER_TB_4X8_INDEX0		(0xf7d508e6)
#घोषणा DITHER_TB_4X8_INDEX1		(0x3b194c2a)
#घोषणा DITHER_TB_4X8_INDEX2		(0xc4e6d5f7)
#घोषणा DITHER_TB_4X8_INDEX3		(0x082a193b)
#घोषणा LCD_DITHER_TBL_DATA		(0x00A4)

/* Video Frame 0&1 start address रेजिस्टरs */
#घोषणा	LCD_SPU_DMA_START_ADDR_Y0	0x00C0
#घोषणा	LCD_SPU_DMA_START_ADDR_U0	0x00C4
#घोषणा	LCD_SPU_DMA_START_ADDR_V0	0x00C8
#घोषणा LCD_CFG_DMA_START_ADDR_0	0x00CC /* Cmd address */
#घोषणा	LCD_SPU_DMA_START_ADDR_Y1	0x00D0
#घोषणा	LCD_SPU_DMA_START_ADDR_U1	0x00D4
#घोषणा	LCD_SPU_DMA_START_ADDR_V1	0x00D8
#घोषणा LCD_CFG_DMA_START_ADDR_1	0x00DC /* Cmd address */

/* YC & UV Pitch */
#घोषणा LCD_SPU_DMA_PITCH_YC		0x00E0
#घोषणा	 SPU_DMA_PITCH_C(c)		((c)<<16)
#घोषणा	 SPU_DMA_PITCH_Y(y)		(y)
#घोषणा LCD_SPU_DMA_PITCH_UV		0x00E4
#घोषणा	 SPU_DMA_PITCH_V(v)		((v)<<16)
#घोषणा	 SPU_DMA_PITCH_U(u)		(u)

/* Video Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPUT_DMA_OVSA_HPXL_VLN		0x00E8
#घोषणा	 CFG_DMA_OVSA_VLN(y)			((y)<<16) /* 0~0xfff */
#घोषणा	 CFG_DMA_OVSA_HPXL(x)			(x)	 /* 0~0xfff */

/* Video Size Register */
#घोषणा LCD_SPU_DMA_HPXL_VLN			0x00EC
#घोषणा	 CFG_DMA_VLN(y)				((y)<<16)
#घोषणा	 CFG_DMA_HPXL(x)			(x)

/* Video Size After zooming Register */
#घोषणा LCD_SPU_DZM_HPXL_VLN			0x00F0
#घोषणा	 CFG_DZM_VLN(y)				((y)<<16)
#घोषणा	 CFG_DZM_HPXL(x)			(x)

/* Graphic Frame 0&1 Starting Address Register */
#घोषणा LCD_CFG_GRA_START_ADDR0			0x00F4
#घोषणा LCD_CFG_GRA_START_ADDR1			0x00F8

/* Graphic Frame Pitch */
#घोषणा LCD_CFG_GRA_PITCH			0x00FC

/* Graphic Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPU_GRA_OVSA_HPXL_VLN		0x0100
#घोषणा	 CFG_GRA_OVSA_VLN(y)			((y)<<16)
#घोषणा	 CFG_GRA_OVSA_HPXL(x)			(x)

/* Graphic Size Register */
#घोषणा LCD_SPU_GRA_HPXL_VLN			0x0104
#घोषणा	 CFG_GRA_VLN(y)				((y)<<16)
#घोषणा	 CFG_GRA_HPXL(x)			(x)

/* Graphic Size after Zooming Register */
#घोषणा LCD_SPU_GZM_HPXL_VLN			0x0108
#घोषणा	 CFG_GZM_VLN(y)				((y)<<16)
#घोषणा	 CFG_GZM_HPXL(x)			(x)

/* HW Cursor Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPU_HWC_OVSA_HPXL_VLN		0x010C
#घोषणा	 CFG_HWC_OVSA_VLN(y)			((y)<<16)
#घोषणा	 CFG_HWC_OVSA_HPXL(x)			(x)

/* HW Cursor Size */
#घोषणा LCD_SPU_HWC_HPXL_VLN			0x0110
#घोषणा	 CFG_HWC_VLN(y)				((y)<<16)
#घोषणा	 CFG_HWC_HPXL(x)			(x)

/* Total Screen Size Register */
#घोषणा LCD_SPUT_V_H_TOTAL			0x0114
#घोषणा	 CFG_V_TOTAL(y)				((y)<<16)
#घोषणा	 CFG_H_TOTAL(x)				(x)

/* Total Screen Active Size Register */
#घोषणा LCD_SPU_V_H_ACTIVE			0x0118
#घोषणा	 CFG_V_ACTIVE(y)			((y)<<16)
#घोषणा	 CFG_H_ACTIVE(x)			(x)

/* Screen H&V Porch Register */
#घोषणा LCD_SPU_H_PORCH				0x011C
#घोषणा	 CFG_H_BACK_PORCH(b)			((b)<<16)
#घोषणा	 CFG_H_FRONT_PORCH(f)			(f)
#घोषणा LCD_SPU_V_PORCH				0x0120
#घोषणा	 CFG_V_BACK_PORCH(b)			((b)<<16)
#घोषणा	 CFG_V_FRONT_PORCH(f)			(f)

/* Screen Blank Color Register */
#घोषणा LCD_SPU_BLANKCOLOR			0x0124
#घोषणा  CFG_BLANKCOLOR_MASK			0x00FFFFFF
#घोषणा  CFG_BLANKCOLOR_R_MASK			0x000000FF
#घोषणा  CFG_BLANKCOLOR_G_MASK			0x0000FF00
#घोषणा  CFG_BLANKCOLOR_B_MASK			0x00FF0000

/* HW Cursor Color 1&2 Register */
#घोषणा LCD_SPU_ALPHA_COLOR1			0x0128
#घोषणा	 CFG_HWC_COLOR1				0x00FFFFFF
#घोषणा	 CFG_HWC_COLOR1_R(red)			((red)<<16)
#घोषणा	 CFG_HWC_COLOR1_G(green)		((green)<<8)
#घोषणा	 CFG_HWC_COLOR1_B(blue)			(blue)
#घोषणा	 CFG_HWC_COLOR1_R_MASK			0x000000FF
#घोषणा	 CFG_HWC_COLOR1_G_MASK			0x0000FF00
#घोषणा	 CFG_HWC_COLOR1_B_MASK			0x00FF0000
#घोषणा LCD_SPU_ALPHA_COLOR2			0x012C
#घोषणा	 CFG_HWC_COLOR2				0x00FFFFFF
#घोषणा	 CFG_HWC_COLOR2_R_MASK			0x000000FF
#घोषणा	 CFG_HWC_COLOR2_G_MASK			0x0000FF00
#घोषणा	 CFG_HWC_COLOR2_B_MASK			0x00FF0000

/* Video YUV Color Key Control */
#घोषणा LCD_SPU_COLORKEY_Y			0x0130
#घोषणा	 CFG_CKEY_Y2(y2)			((y2)<<24)
#घोषणा	 CFG_CKEY_Y2_MASK			0xFF000000
#घोषणा	 CFG_CKEY_Y1(y1)			((y1)<<16)
#घोषणा	 CFG_CKEY_Y1_MASK			0x00FF0000
#घोषणा	 CFG_CKEY_Y(y)				((y)<<8)
#घोषणा	 CFG_CKEY_Y_MASK			0x0000FF00
#घोषणा	 CFG_ALPHA_Y(y)				(y)
#घोषणा	 CFG_ALPHA_Y_MASK			0x000000FF
#घोषणा LCD_SPU_COLORKEY_U			0x0134
#घोषणा	 CFG_CKEY_U2(u2)			((u2)<<24)
#घोषणा	 CFG_CKEY_U2_MASK			0xFF000000
#घोषणा	 CFG_CKEY_U1(u1)			((u1)<<16)
#घोषणा	 CFG_CKEY_U1_MASK			0x00FF0000
#घोषणा	 CFG_CKEY_U(u)				((u)<<8)
#घोषणा	 CFG_CKEY_U_MASK			0x0000FF00
#घोषणा	 CFG_ALPHA_U(u)				(u)
#घोषणा	 CFG_ALPHA_U_MASK			0x000000FF
#घोषणा LCD_SPU_COLORKEY_V			0x0138
#घोषणा	 CFG_CKEY_V2(v2)			((v2)<<24)
#घोषणा	 CFG_CKEY_V2_MASK			0xFF000000
#घोषणा	 CFG_CKEY_V1(v1)			((v1)<<16)
#घोषणा	 CFG_CKEY_V1_MASK			0x00FF0000
#घोषणा	 CFG_CKEY_V(v)				((v)<<8)
#घोषणा	 CFG_CKEY_V_MASK			0x0000FF00
#घोषणा	 CFG_ALPHA_V(v)				(v)
#घोषणा	 CFG_ALPHA_V_MASK			0x000000FF

/* Graphics/Video DMA color key enable bits in LCD_TV_CTRL1 */
#घोषणा	 CFG_CKEY_GRA				0x2
#घोषणा	 CFG_CKEY_DMA				0x1

/* Interlace mode enable bits in LCD_TV_CTRL1 */
#घोषणा     CFG_TV_INTERLACE_EN                 (1 << 22)
#घोषणा     CFG_TV_NIB                          (1 << 0)

#घोषणा LCD_PN_SEPXLCNT				0x013c /* MMP2 */

/* SPI Read Data Register */
#घोषणा LCD_SPU_SPI_RXDATA			0x0140

/* Smart Panel Read Data Register */
#घोषणा LCD_SPU_ISA_RSDATA			0x0144
#घोषणा	 ISA_RXDATA_16BIT_1_DATA_MASK		0x000000FF
#घोषणा	 ISA_RXDATA_16BIT_2_DATA_MASK		0x0000FF00
#घोषणा	 ISA_RXDATA_16BIT_3_DATA_MASK		0x00FF0000
#घोषणा	 ISA_RXDATA_16BIT_4_DATA_MASK		0xFF000000
#घोषणा	 ISA_RXDATA_32BIT_1_DATA_MASK		0x00FFFFFF

#घोषणा LCD_SPU_DBG_ISA				(0x0148) /* TTC */
#घोषणा LCD_SPU_DMAVLD_YC			(0x014C)
#घोषणा LCD_SPU_DMAVLD_UV			(0x0150)
#घोषणा LCD_SPU_DMAVLD_UVSPU_GRAVLD		(0x0154)

#घोषणा LCD_READ_IOPAD				(0x0148) /* MMP2*/
#घोषणा LCD_DMAVLD_YC				(0x014C)
#घोषणा LCD_DMAVLD_UV				(0x0150)
#घोषणा LCD_TVGGRAVLD_HLEN			(0x0154)

/* HWC SRAM Read Data Register */
#घोषणा LCD_SPU_HWC_RDDAT			0x0158

/* Gamma Table SRAM Read Data Register */
#घोषणा LCD_SPU_GAMMA_RDDAT			0x015c
#घोषणा	 CFG_GAMMA_RDDAT_MASK			0x000000FF

/* Palette Table SRAM Read Data Register */
#घोषणा LCD_SPU_PALETTE_RDDAT			0x0160
#घोषणा	 CFG_PALETTE_RDDAT_MASK			0x00FFFFFF

#घोषणा LCD_SPU_DBG_DMATOP			(0x0164) /* TTC */
#घोषणा LCD_SPU_DBG_GRATOP			(0x0168)
#घोषणा LCD_SPU_DBG_TXCTRL			(0x016C)
#घोषणा LCD_SPU_DBG_SLVTOP			(0x0170)
#घोषणा LCD_SPU_DBG_MUXTOP			(0x0174)

#घोषणा LCD_SLV_DBG				(0x0164) /* MMP2 */
#घोषणा LCD_TVDVLD_YC				(0x0168)
#घोषणा LCD_TVDVLD_UV				(0x016C)
#घोषणा LCD_TVC_RDDAT				(0x0170)
#घोषणा LCD_TV_GAMMA_RDDAT			(0x0174)

/* I/O Pads Input Read Only Register */
#घोषणा LCD_SPU_IOPAD_IN			0x0178
#घोषणा	 CFG_IOPAD_IN_MASK			0x0FFFFFFF

#घोषणा LCD_TV_PALETTE_RDDAT			(0x0178) /* MMP2 */

/* Reserved Read Only Registers */
#घोषणा LCD_CFG_RDREG5F				0x017C
#घोषणा	 IRE_FRAME_CNT_MASK			0x000000C0
#घोषणा	 IPE_FRAME_CNT_MASK			0x00000030
#घोषणा	 GRA_FRAME_CNT_MASK			0x0000000C /* Graphic */
#घोषणा	 DMA_FRAME_CNT_MASK			0x00000003 /* Video */

#घोषणा LCD_FRAME_CNT				(0x017C) /* MMP2 */

/* SPI Control Register. */
#घोषणा LCD_SPU_SPI_CTRL			0x0180
#घोषणा	 CFG_SCLKCNT(भाग)			((भाग)<<24) /* 0xFF~0x2 */
#घोषणा	 CFG_SCLKCNT_MASK			0xFF000000
#घोषणा	 CFG_RXBITS(rx)				(((rx) - 1)<<16) /* 0x1F~0x1 */
#घोषणा	 CFG_RXBITS_MASK			0x00FF0000
#घोषणा	 CFG_TXBITS(tx)				(((tx) - 1)<<8) /* 0x1F~0x1 */
#घोषणा	 CFG_TXBITS_MASK			0x0000FF00
#घोषणा	 CFG_CLKINV(clk)			((clk)<<7)
#घोषणा	 CFG_CLKINV_MASK			0x00000080
#घोषणा	 CFG_KEEPXFER(transfer)			((transfer)<<6)
#घोषणा	 CFG_KEEPXFER_MASK			0x00000040
#घोषणा	 CFG_RXBITSTO0(rx)			((rx)<<5)
#घोषणा	 CFG_RXBITSTO0_MASK			0x00000020
#घोषणा	 CFG_TXBITSTO0(tx)			((tx)<<4)
#घोषणा	 CFG_TXBITSTO0_MASK			0x00000010
#घोषणा	 CFG_SPI_ENA(spi)			((spi)<<3)
#घोषणा	 CFG_SPI_ENA_MASK			0x00000008
#घोषणा	 CFG_SPI_SEL(spi)			((spi)<<2)
#घोषणा	 CFG_SPI_SEL_MASK			0x00000004
#घोषणा	 CFG_SPI_3W4WB(wire)			((wire)<<1)
#घोषणा	 CFG_SPI_3W4WB_MASK			0x00000002
#घोषणा	 CFG_SPI_START(start)			(start)
#घोषणा	 CFG_SPI_START_MASK			0x00000001

/* SPI Tx Data Register */
#घोषणा LCD_SPU_SPI_TXDATA			0x0184

/*
   1. Smart Pannel 8-bit Bus Control Register.
   2. AHB Slave Path Data Port Register
*/
#घोषणा LCD_SPU_SMPN_CTRL			0x0188

/* DMA Control 0 Register */
#घोषणा LCD_SPU_DMA_CTRL0			0x0190
#घोषणा	 CFG_NOBLENDING(nb)			((nb)<<31)
#घोषणा	 CFG_NOBLENDING_MASK			0x80000000
#घोषणा	 CFG_GAMMA_ENA(gn)			((gn)<<30)
#घोषणा	 CFG_GAMMA_ENA_MASK			0x40000000
#घोषणा	 CFG_CBSH_ENA(cn)			((cn)<<29)
#घोषणा	 CFG_CBSH_ENA_MASK			0x20000000
#घोषणा	 CFG_PALETTE_ENA(pn)			((pn)<<28)
#घोषणा	 CFG_PALETTE_ENA_MASK			0x10000000
#घोषणा	 CFG_ARBFAST_ENA(an)			((an)<<27)
#घोषणा	 CFG_ARBFAST_ENA_MASK			0x08000000
#घोषणा	 CFG_HWC_1BITMOD(mode)			((mode)<<26)
#घोषणा	 CFG_HWC_1BITMOD_MASK			0x04000000
#घोषणा	 CFG_HWC_1BITENA(mn)			((mn)<<25)
#घोषणा	 CFG_HWC_1BITENA_MASK			0x02000000
#घोषणा	 CFG_HWC_ENA(cn)			((cn)<<24)
#घोषणा	 CFG_HWC_ENA_MASK			0x01000000
#घोषणा	 CFG_DMAFORMAT(dmaक्रमmat)		((dmaक्रमmat)<<20)
#घोषणा	 CFG_DMAFORMAT_MASK			0x00F00000
#घोषणा	 CFG_GRAFORMAT(graक्रमmat)		((graक्रमmat)<<16)
#घोषणा	 CFG_GRAFORMAT_MASK			0x000F0000
/* क्रम graphic part */
#घोषणा	 CFG_GRA_FTOGGLE(toggle)		((toggle)<<15)
#घोषणा	 CFG_GRA_FTOGGLE_MASK			0x00008000
#घोषणा	 CFG_GRA_HSMOOTH(smooth)		((smooth)<<14)
#घोषणा	 CFG_GRA_HSMOOTH_MASK			0x00004000
#घोषणा	 CFG_GRA_TSTMODE(test)			((test)<<13)
#घोषणा	 CFG_GRA_TSTMODE_MASK			0x00002000
#घोषणा	 CFG_GRA_SWAPRB(swap)			((swap)<<12)
#घोषणा	 CFG_GRA_SWAPRB_MASK			0x00001000
#घोषणा	 CFG_GRA_SWAPUV(swap)			((swap)<<11)
#घोषणा	 CFG_GRA_SWAPUV_MASK			0x00000800
#घोषणा	 CFG_GRA_SWAPYU(swap)			((swap)<<10)
#घोषणा	 CFG_GRA_SWAPYU_MASK			0x00000400
#घोषणा	 CFG_GRA_SWAP_MASK			0x00001C00
#घोषणा	 CFG_YUV2RGB_GRA(cvrt)			((cvrt)<<9)
#घोषणा	 CFG_YUV2RGB_GRA_MASK			0x00000200
#घोषणा	 CFG_GRA_ENA(gra)			((gra)<<8)
#घोषणा	 CFG_GRA_ENA_MASK			0x00000100
#घोषणा dma0_gfx_masks	(CFG_GRAFORMAT_MASK | CFG_GRA_FTOGGLE_MASK | \
	CFG_GRA_HSMOOTH_MASK | CFG_GRA_TSTMODE_MASK | CFG_GRA_SWAP_MASK | \
	CFG_YUV2RGB_GRA_MASK | CFG_GRA_ENA_MASK)
/* क्रम video part */
#घोषणा	 CFG_DMA_FTOGGLE(toggle)		((toggle)<<7)
#घोषणा	 CFG_DMA_FTOGGLE_MASK			0x00000080
#घोषणा	 CFG_DMA_HSMOOTH(smooth)		((smooth)<<6)
#घोषणा	 CFG_DMA_HSMOOTH_MASK			0x00000040
#घोषणा	 CFG_DMA_TSTMODE(test)			((test)<<5)
#घोषणा	 CFG_DMA_TSTMODE_MASK			0x00000020
#घोषणा	 CFG_DMA_SWAPRB(swap)			((swap)<<4)
#घोषणा	 CFG_DMA_SWAPRB_MASK			0x00000010
#घोषणा	 CFG_DMA_SWAPUV(swap)			((swap)<<3)
#घोषणा	 CFG_DMA_SWAPUV_MASK			0x00000008
#घोषणा	 CFG_DMA_SWAPYU(swap)			((swap)<<2)
#घोषणा	 CFG_DMA_SWAPYU_MASK			0x00000004
#घोषणा	 CFG_DMA_SWAP_MASK			0x0000001C
#घोषणा	 CFG_YUV2RGB_DMA(cvrt)			((cvrt)<<1)
#घोषणा	 CFG_YUV2RGB_DMA_MASK			0x00000002
#घोषणा	 CFG_DMA_ENA(video)			(video)
#घोषणा	 CFG_DMA_ENA_MASK			0x00000001
#घोषणा dma0_vid_masks	(CFG_DMAFORMAT_MASK | CFG_DMA_FTOGGLE_MASK | \
	CFG_DMA_HSMOOTH_MASK | CFG_DMA_TSTMODE_MASK | CFG_DMA_SWAP_MASK | \
	CFG_YUV2RGB_DMA_MASK | CFG_DMA_ENA_MASK)
#घोषणा dma_palette(val)		((val ? 1 : 0) << 28)
#घोषणा dma_fmt(vid, val)		((val & 0xf) << ((vid) ? 20 : 16))
#घोषणा dma_swaprb(vid, val)		((val ? 1 : 0) << ((vid) ? 4 : 12))
#घोषणा dma_swapuv(vid, val)		((val ? 1 : 0) << ((vid) ? 3 : 11))
#घोषणा dma_swapyuv(vid, val)		((val ? 1 : 0) << ((vid) ? 2 : 10))
#घोषणा dma_csc(vid, val)		((val ? 1 : 0) << ((vid) ? 1 : 9))
#घोषणा dma_hsmooth(vid, val)		((val ? 1 : 0) << ((vid) ? 6 : 14))
#घोषणा dma_mask(vid)	(dma_palette(1) | dma_fmt(vid, 0xf) | dma_csc(vid, 1) \
	| dma_swaprb(vid, 1) | dma_swapuv(vid, 1) | dma_swapyuv(vid, 1))

/* DMA Control 1 Register */
#घोषणा LCD_SPU_DMA_CTRL1			0x0194
#घोषणा	 CFG_FRAME_TRIG(trig)			((trig)<<31)
#घोषणा	 CFG_FRAME_TRIG_MASK			0x80000000
#घोषणा	 CFG_VSYNC_TRIG(trig)			((trig)<<28)
#घोषणा	 CFG_VSYNC_TRIG_MASK			0x70000000
#घोषणा	 CFG_VSYNC_INV(inv)			((inv)<<27)
#घोषणा	 CFG_VSYNC_INV_MASK			0x08000000
#घोषणा	 CFG_COLOR_KEY_MODE(cmode)		((cmode)<<24)
#घोषणा	 CFG_COLOR_KEY_MASK			0x07000000
#घोषणा	 CFG_CARRY(carry)			((carry)<<23)
#घोषणा	 CFG_CARRY_MASK				0x00800000
#घोषणा	 CFG_LNBUF_ENA(lnbuf)			((lnbuf)<<22)
#घोषणा	 CFG_LNBUF_ENA_MASK			0x00400000
#घोषणा	 CFG_GATED_ENA(gated)			((gated)<<21)
#घोषणा	 CFG_GATED_ENA_MASK			0x00200000
#घोषणा	 CFG_PWRDN_ENA(घातer)			((घातer)<<20)
#घोषणा	 CFG_PWRDN_ENA_MASK			0x00100000
#घोषणा	 CFG_DSCALE(dscale)			((dscale)<<18)
#घोषणा	 CFG_DSCALE_MASK			0x000C0000
#घोषणा	 CFG_ALPHA_MODE(amode)			((amode)<<16)
#घोषणा	 CFG_ALPHA_MODE_MASK			0x00030000
#घोषणा	 CFG_ALPHA(alpha)			((alpha)<<8)
#घोषणा	 CFG_ALPHA_MASK				0x0000FF00
#घोषणा	 CFG_PXLCMD(pxlcmd)			(pxlcmd)
#घोषणा	 CFG_PXLCMD_MASK			0x000000FF

/* SRAM Control Register */
#घोषणा LCD_SPU_SRAM_CTRL			0x0198
#घोषणा	 CFG_SRAM_INIT_WR_RD(mode)		((mode)<<14)
#घोषणा	 CFG_SRAM_INIT_WR_RD_MASK		0x0000C000
#घोषणा	 CFG_SRAM_ADDR_LCDID(id)		((id)<<8)
#घोषणा	 CFG_SRAM_ADDR_LCDID_MASK		0x00000F00
#घोषणा	 CFG_SRAM_ADDR(addr)			(addr)
#घोषणा	 CFG_SRAM_ADDR_MASK			0x000000FF

/* SRAM Write Data Register */
#घोषणा LCD_SPU_SRAM_WRDAT			0x019C

/* SRAM RTC/WTC Control Register */
#घोषणा LCD_SPU_SRAM_PARA0			0x01A0

/* SRAM Power Down Control Register */
#घोषणा LCD_SPU_SRAM_PARA1			0x01A4
#घोषणा	 CFG_CSB_256x32(hwc)			((hwc)<<15)	/* HWC */
#घोषणा	 CFG_CSB_256x32_MASK			0x00008000
#घोषणा	 CFG_CSB_256x24(palette)		((palette)<<14)	/* Palette */
#घोषणा	 CFG_CSB_256x24_MASK			0x00004000
#घोषणा	 CFG_CSB_256x8(gamma)			((gamma)<<13)	/* Gamma */
#घोषणा	 CFG_CSB_256x8_MASK			0x00002000
#घोषणा	 CFG_PDWN256x32(pdwn)			((pdwn)<<7)	/* HWC */
#घोषणा	 CFG_PDWN256x32_MASK			0x00000080
#घोषणा	 CFG_PDWN256x24(pdwn)			((pdwn)<<6)	/* Palette */
#घोषणा	 CFG_PDWN256x24_MASK			0x00000040
#घोषणा	 CFG_PDWN256x8(pdwn)			((pdwn)<<5)	/* Gamma */
#घोषणा	 CFG_PDWN256x8_MASK			0x00000020
#घोषणा	 CFG_PDWN32x32(pdwn)			((pdwn)<<3)
#घोषणा	 CFG_PDWN32x32_MASK			0x00000008
#घोषणा	 CFG_PDWN16x66(pdwn)			((pdwn)<<2)
#घोषणा	 CFG_PDWN16x66_MASK			0x00000004
#घोषणा	 CFG_PDWN32x66(pdwn)			((pdwn)<<1)
#घोषणा	 CFG_PDWN32x66_MASK			0x00000002
#घोषणा	 CFG_PDWN64x66(pdwn)			(pdwn)
#घोषणा	 CFG_PDWN64x66_MASK			0x00000001

/* Smart or Dumb Panel Clock Divider */
#घोषणा LCD_CFG_SCLK_DIV			0x01A8
#घोषणा	 SCLK_SRC_SEL(src)		((src)<<31)
#घोषणा	 SCLK_SRC_SEL_MASK		0x80000000
#घोषणा  SCLK_DISABLE				(1<<28)
#घोषणा	 CLK_FRACDIV(frac)			((frac)<<16)
#घोषणा	 CLK_FRACDIV_MASK			0x0FFF0000
#घोषणा	 DSI1_BITCLK_DIV(भाग)			(भाग<<8)
#घोषणा	 DSI1_BITCLK_DIV_MASK			0x00000F00
#घोषणा	 CLK_INT_DIV(भाग)			(भाग)
#घोषणा	 CLK_INT_DIV_MASK			0x000000FF

/* Video Contrast Register */
#घोषणा LCD_SPU_CONTRAST			0x01AC
#घोषणा	 CFG_BRIGHTNESS(bright)			((bright)<<16)
#घोषणा	 CFG_BRIGHTNESS_MASK			0xFFFF0000
#घोषणा	 CFG_CONTRAST(contrast)			(contrast)
#घोषणा	 CFG_CONTRAST_MASK			0x0000FFFF

/* Video Saturation Register */
#घोषणा LCD_SPU_SATURATION			0x01B0
#घोषणा	 CFG_C_MULTS(mult)			((mult)<<16)
#घोषणा	 CFG_C_MULTS_MASK			0xFFFF0000
#घोषणा	 CFG_SATURATION(sat)			(sat)
#घोषणा	 CFG_SATURATION_MASK			0x0000FFFF

/* Video Hue Adjust Register */
#घोषणा LCD_SPU_CBSH_HUE			0x01B4
#घोषणा	 CFG_SIN0(sin0)				((sin0)<<16)
#घोषणा	 CFG_SIN0_MASK				0xFFFF0000
#घोषणा	 CFG_COS0(con0)				(con0)
#घोषणा	 CFG_COS0_MASK				0x0000FFFF

/* Dump LCD Panel Control Register */
#घोषणा LCD_SPU_DUMB_CTRL			0x01B8
#घोषणा	 CFG_DUMBMODE(mode)			((mode)<<28)
#घोषणा	 CFG_DUMBMODE_MASK			0xF0000000
#घोषणा	 CFG_INTFRBSWAP(mode)			((mode)<<24)
#घोषणा	 CFG_INTFRBSWAP_MASK			0x0F000000
#घोषणा	 CFG_LCDGPIO_O(data)			((data)<<20)
#घोषणा	 CFG_LCDGPIO_O_MASK			0x0FF00000
#घोषणा	 CFG_LCDGPIO_ENA(gpio)			((gpio)<<12)
#घोषणा	 CFG_LCDGPIO_ENA_MASK			0x000FF000
#घोषणा	 CFG_BIAS_OUT(bias)			((bias)<<8)
#घोषणा	 CFG_BIAS_OUT_MASK			0x00000100
#घोषणा	 CFG_REVERSE_RGB(RGB)			((RGB)<<7)
#घोषणा	 CFG_REVERSE_RGB_MASK			0x00000080
#घोषणा	 CFG_INV_COMPBLANK(blank)		((blank)<<6)
#घोषणा	 CFG_INV_COMPBLANK_MASK			0x00000040
#घोषणा	 CFG_INV_COMPSYNC(sync)			((sync)<<5)
#घोषणा	 CFG_INV_COMPSYNC_MASK			0x00000020
#घोषणा	 CFG_INV_HENA(hena)			((hena)<<4)
#घोषणा	 CFG_INV_HENA_MASK			0x00000010
#घोषणा	 CFG_INV_VSYNC(vsync)			((vsync)<<3)
#घोषणा	 CFG_INV_VSYNC_MASK			0x00000008
#घोषणा	 CFG_INV_HSYNC(hsync)			((hsync)<<2)
#घोषणा	 CFG_INV_HSYNC_MASK			0x00000004
#घोषणा	 CFG_INV_PCLK(pclk)			((pclk)<<1)
#घोषणा	 CFG_INV_PCLK_MASK			0x00000002
#घोषणा	 CFG_DUMB_ENA(dumb)			(dumb)
#घोषणा	 CFG_DUMB_ENA_MASK			0x00000001

/* LCD I/O Pads Control Register */
#घोषणा SPU_IOPAD_CONTROL			0x01BC
#घोषणा	 CFG_GRA_VM_ENA(vm)			((vm)<<15)
#घोषणा	 CFG_GRA_VM_ENA_MASK			0x00008000
#घोषणा	 CFG_DMA_VM_ENA(vm)			((vm)<<13)
#घोषणा	 CFG_DMA_VM_ENA_MASK			0x00002000
#घोषणा	 CFG_CMD_VM_ENA(vm)			((vm)<<12)
#घोषणा	 CFG_CMD_VM_ENA_MASK			0x00001000
#घोषणा	 CFG_CSC(csc)				((csc)<<8)
#घोषणा	 CFG_CSC_MASK				0x00000300
#घोषणा	 CFG_BOUNDARY(size)			((size)<<5)
#घोषणा	 CFG_BOUNDARY_MASK			0x00000020
#घोषणा	 CFG_BURST(len)				((len)<<4)
#घोषणा	 CFG_BURST_MASK				0x00000010
#घोषणा	 CFG_IOPADMODE(iopad)			(iopad)
#घोषणा	 CFG_IOPADMODE_MASK			0x0000000F

/* LCD Interrupt Control Register */
#घोषणा SPU_IRQ_ENA				0x01C0
#घोषणा	 DMA_FRAME_IRQ0_ENA(irq)		((irq)<<31)
#घोषणा	 DMA_FRAME_IRQ0_ENA_MASK		0x80000000
#घोषणा	 DMA_FRAME_IRQ1_ENA(irq)		((irq)<<30)
#घोषणा	 DMA_FRAME_IRQ1_ENA_MASK		0x40000000
#घोषणा	 DMA_FF_UNDERFLOW_ENA(ff)		((ff)<<29)
#घोषणा	 DMA_FF_UNDERFLOW_ENA_MASK		0x20000000
#घोषणा	 AXI_BUS_ERROR_IRQ_ENA(irq)		((irq)<<28)
#घोषणा	 AXI_BUS_ERROR_IRQ_ENA_MASK		0x10000000
#घोषणा	 GRA_FRAME_IRQ0_ENA(irq)		((irq)<<27)
#घोषणा	 GRA_FRAME_IRQ0_ENA_MASK		0x08000000
#घोषणा	 GRA_FRAME_IRQ1_ENA(irq)		((irq)<<26)
#घोषणा	 GRA_FRAME_IRQ1_ENA_MASK		0x04000000
#घोषणा	 GRA_FF_UNDERFLOW_ENA(ff)		((ff)<<25)
#घोषणा	 GRA_FF_UNDERFLOW_ENA_MASK		0x02000000
#घोषणा	 VSYNC_IRQ_ENA(vsync_irq)		((vsync_irq)<<23)
#घोषणा	 VSYNC_IRQ_ENA_MASK			0x00800000
#घोषणा	 DUMB_FRAMEDONE_ENA(fकरोne)		((fकरोne)<<22)
#घोषणा	 DUMB_FRAMEDONE_ENA_MASK		0x00400000
#घोषणा	 TWC_FRAMEDONE_ENA(fकरोne)		((fकरोne)<<21)
#घोषणा	 TWC_FRAMEDONE_ENA_MASK			0x00200000
#घोषणा	 HWC_FRAMEDONE_ENA(fकरोne)		((fकरोne)<<20)
#घोषणा	 HWC_FRAMEDONE_ENA_MASK			0x00100000
#घोषणा	 SLV_IRQ_ENA(irq)			((irq)<<19)
#घोषणा	 SLV_IRQ_ENA_MASK			0x00080000
#घोषणा	 SPI_IRQ_ENA(irq)			((irq)<<18)
#घोषणा	 SPI_IRQ_ENA_MASK			0x00040000
#घोषणा	 PWRDN_IRQ_ENA(irq)			((irq)<<17)
#घोषणा	 PWRDN_IRQ_ENA_MASK			0x00020000
#घोषणा	 AXI_LATENCY_TOO_LONG_IRQ_ENA(irq)	((irq)<<16)
#घोषणा  AXI_LATENCY_TOO_LONG_IRQ_ENA_MASK	0x00010000
#घोषणा	 CLEAN_SPU_IRQ_ISR(irq)			(irq)
#घोषणा	 CLEAN_SPU_IRQ_ISR_MASK			0x0000FFFF
#घोषणा	 TV_DMA_FRAME_IRQ0_ENA(irq)		((irq)<<15)
#घोषणा	 TV_DMA_FRAME_IRQ0_ENA_MASK		0x00008000
#घोषणा	 TV_DMA_FRAME_IRQ1_ENA(irq)		((irq)<<14)
#घोषणा	 TV_DMA_FRAME_IRQ1_ENA_MASK		0x00004000
#घोषणा	 TV_DMA_FF_UNDERFLOW_ENA(unerrun)	((unerrun)<<13)
#घोषणा	 TV_DMA_FF_UNDERFLOW_ENA_MASK		0x00002000
#घोषणा	 TVSYNC_IRQ_ENA(irq)			((irq)<<12)
#घोषणा	 TVSYNC_IRQ_ENA_MASK			0x00001000
#घोषणा	 TV_FRAME_IRQ0_ENA(irq)			((irq)<<11)
#घोषणा	 TV_FRAME_IRQ0_ENA_MASK			0x00000800
#घोषणा	 TV_FRAME_IRQ1_ENA(irq)			((irq)<<10)
#घोषणा	 TV_FRAME_IRQ1_ENA_MASK			0x00000400
#घोषणा	 TV_GRA_FF_UNDERFLOW_ENA(unerrun)	((unerrun)<<9)
#घोषणा	 TV_GRA_FF_UNDERFLOW_ENA_MASK		0x00000200
#घोषणा	 TV_FRAMEDONE_ENA(irq)			((irq)<<8)
#घोषणा	 TV_FRAMEDONE_ENA_MASK			0x00000100

/* FIXME - JUST GUESS */
#घोषणा	 PN2_DMA_FRAME_IRQ0_ENA(irq)		((irq)<<7)
#घोषणा	 PN2_DMA_FRAME_IRQ0_ENA_MASK		0x00000080
#घोषणा	 PN2_DMA_FRAME_IRQ1_ENA(irq)		((irq)<<6)
#घोषणा	 PN2_DMA_FRAME_IRQ1_ENA_MASK		0x00000040
#घोषणा	 PN2_DMA_FF_UNDERFLOW_ENA(ff)		((ff)<<5)
#घोषणा	 PN2_DMA_FF_UNDERFLOW_ENA_MASK		0x00000020
#घोषणा	 PN2_GRA_FRAME_IRQ0_ENA(irq)		((irq)<<3)
#घोषणा	 PN2_GRA_FRAME_IRQ0_ENA_MASK		0x00000008
#घोषणा	 PN2_GRA_FRAME_IRQ1_ENA(irq)		((irq)<<2)
#घोषणा	 PN2_GRA_FRAME_IRQ1_ENA_MASK		0x04000004
#घोषणा	 PN2_GRA_FF_UNDERFLOW_ENA(ff)		((ff)<<1)
#घोषणा	 PN2_GRA_FF_UNDERFLOW_ENA_MASK		0x00000002
#घोषणा	 PN2_VSYNC_IRQ_ENA(irq)			((irq)<<0)
#घोषणा	 PN2_SYNC_IRQ_ENA_MASK			0x00000001

#घोषणा gf0_imask(id)	((id) ? (((id) & 1) ? TV_FRAME_IRQ0_ENA_MASK \
		: PN2_GRA_FRAME_IRQ0_ENA_MASK) : GRA_FRAME_IRQ0_ENA_MASK)
#घोषणा gf1_imask(id)	((id) ? (((id) & 1) ? TV_FRAME_IRQ1_ENA_MASK \
		: PN2_GRA_FRAME_IRQ1_ENA_MASK) : GRA_FRAME_IRQ1_ENA_MASK)
#घोषणा vsync_imask(id)	((id) ? (((id) & 1) ? TVSYNC_IRQ_ENA_MASK \
		: PN2_SYNC_IRQ_ENA_MASK) : VSYNC_IRQ_ENA_MASK)
#घोषणा vsync_imasks	(vsync_imask(0) | vsync_imask(1))

#घोषणा display_करोne_imask(id)	((id) ? (((id) & 1) ? TV_FRAMEDONE_ENA_MASK\
	: (PN2_DMA_FRAME_IRQ0_ENA_MASK | PN2_DMA_FRAME_IRQ1_ENA_MASK))\
	: DUMB_FRAMEDONE_ENA_MASK)

#घोषणा display_करोne_imasks	(display_करोne_imask(0) | display_करोne_imask(1))

#घोषणा vf0_imask(id)	((id) ? (((id) & 1) ? TV_DMA_FRAME_IRQ0_ENA_MASK \
		: PN2_DMA_FRAME_IRQ0_ENA_MASK) : DMA_FRAME_IRQ0_ENA_MASK)
#घोषणा vf1_imask(id)	((id) ? (((id) & 1) ? TV_DMA_FRAME_IRQ1_ENA_MASK \
		: PN2_DMA_FRAME_IRQ1_ENA_MASK) : DMA_FRAME_IRQ1_ENA_MASK)

#घोषणा gfx_imasks	(gf0_imask(0) | gf1_imask(0) | gf0_imask(1) | \
		gf1_imask(1))
#घोषणा vid_imasks	(vf0_imask(0) | vf1_imask(0) | vf0_imask(1) | \
		vf1_imask(1))
#घोषणा vid_imask(id)	(display_करोne_imask(id))

#घोषणा pn1_imasks	(gf0_imask(0) | gf1_imask(0) | vsync_imask(0) | \
		display_करोne_imask(0) | vf0_imask(0) | vf1_imask(0))
#घोषणा tv_imasks	(gf0_imask(1) | gf1_imask(1) | vsync_imask(1) | \
		display_करोne_imask(1) | vf0_imask(1) | vf1_imask(1))
#घोषणा path_imasks(id)	((id) ? (tv_imasks) : (pn1_imasks))

/* error indications */
#घोषणा vid_udflow_imask(id)	((id) ? (((id) & 1) ? \
	(TV_DMA_FF_UNDERFLOW_ENA_MASK) : (PN2_DMA_FF_UNDERFLOW_ENA_MASK)) : \
	(DMA_FF_UNDERFLOW_ENA_MASK))
#घोषणा gfx_udflow_imask(id)	((id) ? (((id) & 1) ? \
	(TV_GRA_FF_UNDERFLOW_ENA_MASK) : (PN2_GRA_FF_UNDERFLOW_ENA_MASK)) : \
	(GRA_FF_UNDERFLOW_ENA_MASK))

#घोषणा err_imask(id) (vid_udflow_imask(id) | gfx_udflow_imask(id) | \
	AXI_BUS_ERROR_IRQ_ENA_MASK | AXI_LATENCY_TOO_LONG_IRQ_ENA_MASK)
#घोषणा err_imasks (err_imask(0) | err_imask(1) | err_imask(2))
/* LCD Interrupt Status Register */
#घोषणा SPU_IRQ_ISR			0x01C4
#घोषणा	 DMA_FRAME_IRQ0(irq)		((irq)<<31)
#घोषणा	 DMA_FRAME_IRQ0_MASK		0x80000000
#घोषणा	 DMA_FRAME_IRQ1(irq)		((irq)<<30)
#घोषणा	 DMA_FRAME_IRQ1_MASK		0x40000000
#घोषणा	 DMA_FF_UNDERFLOW(ff)		((ff)<<29)
#घोषणा	 DMA_FF_UNDERFLOW_MASK		0x20000000
#घोषणा	 AXI_BUS_ERROR_IRQ(irq)		((irq)<<28)
#घोषणा	 AXI_BUS_ERROR_IRQ_MASK		0x10000000
#घोषणा	 GRA_FRAME_IRQ0(irq)		((irq)<<27)
#घोषणा	 GRA_FRAME_IRQ0_MASK		0x08000000
#घोषणा	 GRA_FRAME_IRQ1(irq)		((irq)<<26)
#घोषणा	 GRA_FRAME_IRQ1_MASK		0x04000000
#घोषणा	 GRA_FF_UNDERFLOW(ff)		((ff)<<25)
#घोषणा	 GRA_FF_UNDERFLOW_MASK		0x02000000
#घोषणा	 VSYNC_IRQ(vsync_irq)		((vsync_irq)<<23)
#घोषणा	 VSYNC_IRQ_MASK			0x00800000
#घोषणा	 DUMB_FRAMEDONE(fकरोne)		((fकरोne)<<22)
#घोषणा	 DUMB_FRAMEDONE_MASK		0x00400000
#घोषणा	 TWC_FRAMEDONE(fकरोne)		((fकरोne)<<21)
#घोषणा	 TWC_FRAMEDONE_MASK		0x00200000
#घोषणा	 HWC_FRAMEDONE(fकरोne)		((fकरोne)<<20)
#घोषणा	 HWC_FRAMEDONE_MASK		0x00100000
#घोषणा	 SLV_IRQ(irq)			((irq)<<19)
#घोषणा	 SLV_IRQ_MASK			0x00080000
#घोषणा	 SPI_IRQ(irq)			((irq)<<18)
#घोषणा	 SPI_IRQ_MASK			0x00040000
#घोषणा	 PWRDN_IRQ(irq)			((irq)<<17)
#घोषणा	 PWRDN_IRQ_MASK			0x00020000
#घोषणा	 AXI_LATENCY_TOO_LONGR_IRQ(irq)	((irq)<<16)
#घोषणा	 AXI_LATENCY_TOO_LONGR_IRQ_MASK	0x00010000
#घोषणा	 TV_DMA_FRAME_IRQ0(irq)		((irq)<<15)
#घोषणा	 TV_DMA_FRAME_IRQ0_MASK		0x00008000
#घोषणा	 TV_DMA_FRAME_IRQ1(irq)		((irq)<<14)
#घोषणा	 TV_DMA_FRAME_IRQ1_MASK		0x00004000
#घोषणा	 TV_DMA_FF_UNDERFLOW(unerrun)	((unerrun)<<13)
#घोषणा	 TV_DMA_FF_UNDERFLOW_MASK	0x00002000
#घोषणा	 TVSYNC_IRQ(irq)		((irq)<<12)
#घोषणा	 TVSYNC_IRQ_MASK		0x00001000
#घोषणा	 TV_FRAME_IRQ0(irq)		((irq)<<11)
#घोषणा	 TV_FRAME_IRQ0_MASK		0x00000800
#घोषणा	 TV_FRAME_IRQ1(irq)		((irq)<<10)
#घोषणा	 TV_FRAME_IRQ1_MASK		0x00000400
#घोषणा	 TV_GRA_FF_UNDERFLOW(unerrun)	((unerrun)<<9)
#घोषणा	 TV_GRA_FF_UNDERFLOW_MASK	0x00000200
#घोषणा	 PN2_DMA_FRAME_IRQ0(irq)	((irq)<<7)
#घोषणा	 PN2_DMA_FRAME_IRQ0_MASK	0x00000080
#घोषणा	 PN2_DMA_FRAME_IRQ1(irq)	((irq)<<6)
#घोषणा	 PN2_DMA_FRAME_IRQ1_MASK	0x00000040
#घोषणा	 PN2_DMA_FF_UNDERFLOW(ff)	((ff)<<5)
#घोषणा	 PN2_DMA_FF_UNDERFLOW_MASK	0x00000020
#घोषणा	 PN2_GRA_FRAME_IRQ0(irq)	((irq)<<3)
#घोषणा	 PN2_GRA_FRAME_IRQ0_MASK	0x00000008
#घोषणा	 PN2_GRA_FRAME_IRQ1(irq)	((irq)<<2)
#घोषणा	 PN2_GRA_FRAME_IRQ1_MASK	0x04000004
#घोषणा	 PN2_GRA_FF_UNDERFLOW(ff)	((ff)<<1)
#घोषणा	 PN2_GRA_FF_UNDERFLOW_MASK	0x00000002
#घोषणा	 PN2_VSYNC_IRQ(irq)		((irq)<<0)
#घोषणा	 PN2_SYNC_IRQ_MASK		0x00000001

/* LCD FIFO Depth रेजिस्टर */
#घोषणा LCD_FIFO_DEPTH			0x01c8
#घोषणा	 VIDEO_FIFO(fi)			((fi) << 0)
#घोषणा	 VIDEO_FIFO_MASK		0x00000003
#घोषणा	 GRAPHIC_FIFO(fi)		((fi) << 2)
#घोषणा	 GRAPHIC_FIFO_MASK		0x0000000c

/* पढ़ो-only */
#घोषणा	 DMA_FRAME_IRQ0_LEVEL_MASK		0x00008000
#घोषणा	 DMA_FRAME_IRQ1_LEVEL_MASK		0x00004000
#घोषणा	 DMA_FRAME_CNT_ISR_MASK			0x00003000
#घोषणा	 GRA_FRAME_IRQ0_LEVEL_MASK		0x00000800
#घोषणा	 GRA_FRAME_IRQ1_LEVEL_MASK		0x00000400
#घोषणा	 GRA_FRAME_CNT_ISR_MASK			0x00000300
#घोषणा	 VSYNC_IRQ_LEVEL_MASK			0x00000080
#घोषणा	 DUMB_FRAMEDONE_LEVEL_MASK		0x00000040
#घोषणा	 TWC_FRAMEDONE_LEVEL_MASK		0x00000020
#घोषणा	 HWC_FRAMEDONE_LEVEL_MASK		0x00000010
#घोषणा	 SLV_FF_EMPTY_MASK			0x00000008
#घोषणा	 DMA_FF_ALLEMPTY_MASK			0x00000004
#घोषणा	 GRA_FF_ALLEMPTY_MASK			0x00000002
#घोषणा	 PWRDN_IRQ_LEVEL_MASK			0x00000001

/* 32 bit LCD Interrupt Reset Status*/
#घोषणा SPU_IRQ_RSR				(0x01C8)
/* 32 bit Panel Path Graphic Partial Display Horizontal Control Register*/
#घोषणा LCD_GRA_CUTHPXL				(0x01CC)
/* 32 bit Panel Path Graphic Partial Display Vertical Control Register*/
#घोषणा LCD_GRA_CUTVLN				(0x01D0)
/* 32 bit TV Path Graphic Partial Display	  Horizontal Control Register*/
#घोषणा LCD_TVG_CUTHPXL				(0x01D4)
/* 32 bit TV Path Graphic Partial Display Vertical Control Register*/
#घोषणा LCD_TVG_CUTVLN				(0x01D8)
/* 32 bit LCD Global Control Register*/
#घोषणा LCD_TOP_CTRL				(0x01DC)
/* 32 bit LCD SQU Line Buffer Control Register 1*/
#घोषणा LCD_SQULN1_CTRL				(0x01E0)
/* 32 bit LCD SQU Line Buffer Control Register 2*/
#घोषणा LCD_SQULN2_CTRL				(0x01E4)
#घोषणा squln_ctrl(id)	((id) ? (((id) & 1) ? LCD_SQULN2_CTRL : \
			LCD_PN2_SQULN1_CTRL) : LCD_SQULN1_CTRL)

/* 32 bit LCD Mixed Overlay Control Register */
#घोषणा LCD_AFA_ALL2ONE				(0x01E8)

#घोषणा LCD_PN2_SCLK_DIV			(0x01EC)
#घोषणा LCD_PN2_TCLK_DIV			(0x01F0)
#घोषणा LCD_LVDS_SCLK_DIV_WR			(0x01F4)
#घोषणा LCD_LVDS_SCLK_DIV_RD			(0x01FC)
#घोषणा PN2_LCD_DMA_START_ADDR_Y0		(0x0200)
#घोषणा PN2_LCD_DMA_START_ADDR_U0		(0x0204)
#घोषणा PN2_LCD_DMA_START_ADDR_V0		(0x0208)
#घोषणा PN2_LCD_DMA_START_ADDR_C0		(0x020C)
#घोषणा PN2_LCD_DMA_START_ADDR_Y1		(0x0210)
#घोषणा PN2_LCD_DMA_START_ADDR_U1		(0x0214)
#घोषणा PN2_LCD_DMA_START_ADDR_V1		(0x0218)
#घोषणा PN2_LCD_DMA_START_ADDR_C1		(0x021C)
#घोषणा PN2_LCD_DMA_PITCH_YC			(0x0220)
#घोषणा PN2_LCD_DMA_PITCH_UV			(0x0224)
#घोषणा PN2_LCD_DMA_OVSA_HPXL_VLN		(0x0228)
#घोषणा PN2_LCD_DMA_HPXL_VLN			(0x022C)
#घोषणा PN2_LCD_DMAZM_HPXL_VLN			(0x0230)
#घोषणा PN2_LCD_GRA_START_ADDR0			(0x0234)
#घोषणा PN2_LCD_GRA_START_ADDR1			(0x0238)
#घोषणा PN2_LCD_GRA_PITCH			(0x023C)
#घोषणा PN2_LCD_GRA_OVSA_HPXL_VLN		(0x0240)
#घोषणा PN2_LCD_GRA_HPXL_VLN			(0x0244)
#घोषणा PN2_LCD_GRAZM_HPXL_VLN			(0x0248)
#घोषणा PN2_LCD_HWC_OVSA_HPXL_VLN		(0x024C)
#घोषणा PN2_LCD_HWC_HPXL_VLN			(0x0250)
#घोषणा LCD_PN2_V_H_TOTAL			(0x0254)
#घोषणा LCD_PN2_V_H_ACTIVE			(0x0258)
#घोषणा LCD_PN2_H_PORCH				(0x025C)
#घोषणा LCD_PN2_V_PORCH				(0x0260)
#घोषणा LCD_PN2_BLANKCOLOR			(0x0264)
#घोषणा LCD_PN2_ALPHA_COLOR1			(0x0268)
#घोषणा LCD_PN2_ALPHA_COLOR2			(0x026C)
#घोषणा LCD_PN2_COLORKEY_Y			(0x0270)
#घोषणा LCD_PN2_COLORKEY_U			(0x0274)
#घोषणा LCD_PN2_COLORKEY_V			(0x0278)
#घोषणा LCD_PN2_SEPXLCNT			(0x027C)
#घोषणा LCD_TV_V_H_TOTAL_FLD			(0x0280)
#घोषणा LCD_TV_V_PORCH_FLD			(0x0284)
#घोषणा LCD_TV_SEPXLCNT_FLD			(0x0288)

#घोषणा LCD_2ND_ALPHA				(0x0294)
#घोषणा LCD_PN2_CONTRAST			(0x0298)
#घोषणा LCD_PN2_SATURATION			(0x029c)
#घोषणा LCD_PN2_CBSH_HUE			(0x02a0)
#घोषणा LCD_TIMING_EXT				(0x02C0)
#घोषणा LCD_PN2_LAYER_ALPHA_SEL1		(0x02c4)
#घोषणा LCD_PN2_CTRL0				(0x02C8)
#घोषणा TV_LAYER_ALPHA_SEL1			(0x02cc)
#घोषणा LCD_SMPN2_CTRL				(0x02D0)
#घोषणा LCD_IO_OVERL_MAP_CTRL			(0x02D4)
#घोषणा LCD_DUMB2_CTRL				(0x02d8)
#घोषणा LCD_PN2_CTRL1				(0x02DC)
#घोषणा PN2_IOPAD_CONTROL			(0x02E0)
#घोषणा LCD_PN2_SQULN1_CTRL			(0x02E4)
#घोषणा PN2_LCD_GRA_CUTHPXL			(0x02e8)
#घोषणा PN2_LCD_GRA_CUTVLN			(0x02ec)
#घोषणा LCD_PN2_SQULN2_CTRL			(0x02F0)
#घोषणा ALL_LAYER_ALPHA_SEL			(0x02F4)

#घोषणा TIMING_MASTER_CONTROL			(0x02F8)
#घोषणा MASTER_ENH(id)				(1 << (id))
#घोषणा MASTER_ENV(id)				(1 << ((id) + 4))

#घोषणा DSI_START_SEL_SHIFT(id)		(((id) << 1) + 8)
#घोषणा timing_master_config(path, dsi_id, lcd_id) \
	(MASTER_ENH(path) | MASTER_ENV(path) | \
	(((lcd_id) + ((dsi_id) << 1)) << DSI_START_SEL_SHIFT(path)))

#घोषणा LCD_2ND_BLD_CTL				(0x02Fc)
#घोषणा LVDS_SRC_MASK				(3 << 30)
#घोषणा LVDS_SRC_SHIFT				(30)
#घोषणा LVDS_FMT_MASK				(1 << 28)
#घोषणा LVDS_FMT_SHIFT				(28)

#घोषणा CLK_SCLK	(1 << 0)
#घोषणा CLK_LVDS_RD	(1 << 1)
#घोषणा CLK_LVDS_WR	(1 << 2)

#घोषणा gra_partdisp_ctrl_hor(id)	((id) ? (((id) & 1) ? \
	LCD_TVG_CUTHPXL : PN2_LCD_GRA_CUTHPXL) : LCD_GRA_CUTHPXL)
#घोषणा gra_partdisp_ctrl_ver(id)	((id) ? (((id) & 1) ? \
	LCD_TVG_CUTVLN : PN2_LCD_GRA_CUTVLN) : LCD_GRA_CUTVLN)

/*
 * defined क्रम Configure Dumb Mode
 * defined क्रम Configure Dumb Mode
 * DUMB LCD Panel bit[31:28]
 */
#घोषणा DUMB16_RGB565_0		0x0
#घोषणा DUMB16_RGB565_1		0x1
#घोषणा DUMB18_RGB666_0		0x2
#घोषणा DUMB18_RGB666_1		0x3
#घोषणा DUMB12_RGB444_0		0x4
#घोषणा DUMB12_RGB444_1		0x5
#घोषणा DUMB24_RGB888_0		0x6
#घोषणा DUMB_BLANK		0x7

/*
 * defined क्रम Configure I/O Pin Allocation Mode
 * LCD LCD I/O Pads control रेजिस्टर bit[3:0]
 */
#घोषणा IOPAD_DUMB24		0x0
#घोषणा IOPAD_DUMB18SPI		0x1
#घोषणा IOPAD_DUMB18GPIO	0x2
#घोषणा IOPAD_DUMB16SPI		0x3
#घोषणा IOPAD_DUMB16GPIO	0x4
#घोषणा IOPAD_DUMB12		0x5
#घोषणा IOPAD_SMART18SPI	0x6
#घोषणा IOPAD_SMART16SPI	0x7
#घोषणा IOPAD_SMART8BOTH	0x8
#घोषणा IOPAD_DUMB18_SMART8	0x9
#घोषणा IOPAD_DUMB16_SMART8SPI	0xa
#घोषणा IOPAD_DUMB16_SMART8GPIO	0xb
#घोषणा IOPAD_DUMB16_DUMB16	0xc
#घोषणा IOPAD_SMART8_SMART8	0xc

/*
 *defined क्रम indicating boundary and cycle burst length
 */
#घोषणा  CFG_BOUNDARY_1KB			(1<<5)
#घोषणा  CFG_BOUNDARY_4KB			(0<<5)
#घोषणा	 CFG_CYC_BURST_LEN16			(1<<4)
#घोषणा	 CFG_CYC_BURST_LEN8			(0<<4)

/* SRAM ID */
#घोषणा SRAMID_GAMMA_YR			0x0
#घोषणा SRAMID_GAMMA_UG			0x1
#घोषणा SRAMID_GAMMA_VB			0x2
#घोषणा SRAMID_PALATTE			0x3
#घोषणा SRAMID_HWC			0xf

/* SRAM INIT Read/Write */
#घोषणा SRAMID_INIT_READ		0x0
#घोषणा SRAMID_INIT_WRITE		0x2
#घोषणा SRAMID_INIT_DEFAULT		0x3

/*
 * defined VSYNC selection mode क्रम DMA control 1 रेजिस्टर
 * DMA1 bit[30:28]
 */
#घोषणा VMODE_SMPN			0x0
#घोषणा VMODE_SMPNIRQ			0x1
#घोषणा VMODE_DUMB			0x2
#घोषणा VMODE_IPE			0x3
#घोषणा VMODE_IRE			0x4

/*
 * defined Configure Alpha and Alpha mode क्रम DMA control 1 रेजिस्टर
 * DMA1 bit[15:08](alpha) / bit[17:16](alpha mode)
 */
/* ALPHA mode */
#घोषणा MODE_ALPHA_DMA			0x0
#घोषणा MODE_ALPHA_GRA			0x1
#घोषणा MODE_ALPHA_CFG			0x2

/* alpha value */
#घोषणा ALPHA_NOGRAPHIC			0xFF	  /* all video, no graphic */
#घोषणा ALPHA_NOVIDEO			0x00	  /* all graphic, no video */
#घोषणा ALPHA_GRAPHNVIDEO		0x0F	  /* Selects graphic & video */

/*
 * defined Pixel Command क्रम DMA control 1 रेजिस्टर
 * DMA1 bit[07:00]
 */
#घोषणा PIXEL_CMD			0x81

/* DSI */
/* DSI1 - 4 Lane Controller base */
#घोषणा DSI1_REGS_PHYSICAL_BASE		0xD420B800
/* DSI2 - 3 Lane Controller base */
#घोषणा DSI2_REGS_PHYSICAL_BASE		0xD420BA00

/*	   DSI Controller Registers	   */
काष्ठा dsi_lcd_regs अणु
#घोषणा DSI_LCD1_CTRL_0  0x100   /* DSI Active Panel 1 Control रेजिस्टर 0 */
#घोषणा DSI_LCD1_CTRL_1  0x104   /* DSI Active Panel 1 Control रेजिस्टर 1 */
	u32 ctrl0;
	u32 ctrl1;
	u32 reserved1[2];

#घोषणा DSI_LCD1_TIMING_0		0x110   /* Timing रेजिस्टर 0 */
#घोषणा DSI_LCD1_TIMING_1		0x114   /* Timing रेजिस्टर 1 */
#घोषणा DSI_LCD1_TIMING_2		0x118   /* Timing रेजिस्टर 2 */
#घोषणा DSI_LCD1_TIMING_3		0x11C   /* Timing रेजिस्टर 3 */
#घोषणा DSI_LCD1_WC_0			0x120   /* Word Count रेजिस्टर 0 */
#घोषणा DSI_LCD1_WC_1			0x124   /* Word Count रेजिस्टर 1 */
#घोषणा DSI_LCD1_WC_2			0x128	 /* Word Count रेजिस्टर 2 */
	u32 timing0;
	u32 timing1;
	u32 timing2;
	u32 timing3;
	u32 wc0;
	u32 wc1;
	u32 wc2;
	u32 reserved2[1];
	u32 slot_cnt0;
	u32 slot_cnt1;
	u32 reserved3[2];
	u32 status_0;
	u32 status_1;
	u32 status_2;
	u32 status_3;
	u32 status_4;
पूर्ण;

काष्ठा dsi_regs अणु
#घोषणा DSI_CTRL_0	  0x000   /* DSI control रेजिस्टर 0 */
#घोषणा DSI_CTRL_1	  0x004   /* DSI control रेजिस्टर 1 */
	u32 ctrl0;
	u32 ctrl1;
	u32 reserved1[2];
	u32 irq_status;
	u32 irq_mask;
	u32 reserved2[2];

#घोषणा DSI_CPU_CMD_0   0x020   /* DSI CPU packet command रेजिस्टर 0 */
#घोषणा DSI_CPU_CMD_1   0x024   /* DSU CPU Packet Command Register 1 */
#घोषणा DSI_CPU_CMD_3	0x02C   /* DSU CPU Packet Command Register 3 */
#घोषणा DSI_CPU_WDAT_0	0x030   /* DSI CUP */
	u32 cmd0;
	u32 cmd1;
	u32 cmd2;
	u32 cmd3;
	u32 dat0;
	u32 status0;
	u32 status1;
	u32 status2;
	u32 status3;
	u32 status4;
	u32 reserved3[2];

	u32 smt_cmd;
	u32 smt_ctrl0;
	u32 smt_ctrl1;
	u32 reserved4[1];

	u32 rx0_status;

/* Rx Packet Header - data from slave device */
#घोषणा DSI_RX_PKT_HDR_0 0x064
	u32 rx0_header;
	u32 rx1_status;
	u32 rx1_header;
	u32 rx_ctrl;
	u32 rx_ctrl1;
	u32 rx2_status;
	u32 rx2_header;
	u32 reserved5[1];

	u32 phy_ctrl1;
#घोषणा DSI_PHY_CTRL_2		0x088   /* DSI DPHI Control Register 2 */
#घोषणा DSI_PHY_CTRL_3		0x08C   /* DPHY Control Register 3 */
	u32 phy_ctrl2;
	u32 phy_ctrl3;
	u32 phy_status0;
	u32 phy_status1;
	u32 reserved6[5];
	u32 phy_status2;

#घोषणा DSI_PHY_RCOMP_0		0x0B0   /* DPHY Rcomp Control Register */
	u32 phy_rcomp0;
	u32 reserved7[3];
#घोषणा DSI_PHY_TIME_0		0x0C0   /* DPHY Timing Control Register 0 */
#घोषणा DSI_PHY_TIME_1		0x0C4   /* DPHY Timing Control Register 1 */
#घोषणा DSI_PHY_TIME_2		0x0C8   /* DPHY Timing Control Register 2 */
#घोषणा DSI_PHY_TIME_3		0x0CC   /* DPHY Timing Control Register 3 */
#घोषणा DSI_PHY_TIME_4		0x0D0   /* DPHY Timing Control Register 4 */
#घोषणा DSI_PHY_TIME_5		0x0D4   /* DPHY Timing Control Register 5 */
	u32 phy_timing0;
	u32 phy_timing1;
	u32 phy_timing2;
	u32 phy_timing3;
	u32 phy_code_0;
	u32 phy_code_1;
	u32 reserved8[2];
	u32 mem_ctrl;
	u32 tx_समयr;
	u32 rx_समयr;
	u32 turn_समयr;
	u32 reserved9[4];

#घोषणा DSI_LCD1_CTRL_0  0x100   /* DSI Active Panel 1 Control रेजिस्टर 0 */
#घोषणा DSI_LCD1_CTRL_1  0x104   /* DSI Active Panel 1 Control रेजिस्टर 1 */
#घोषणा DSI_LCD1_TIMING_0		0x110   /* Timing रेजिस्टर 0 */
#घोषणा DSI_LCD1_TIMING_1		0x114   /* Timing रेजिस्टर 1 */
#घोषणा DSI_LCD1_TIMING_2		0x118   /* Timing रेजिस्टर 2 */
#घोषणा DSI_LCD1_TIMING_3		0x11C   /* Timing रेजिस्टर 3 */
#घोषणा DSI_LCD1_WC_0			0x120   /* Word Count रेजिस्टर 0 */
#घोषणा DSI_LCD1_WC_1			0x124   /* Word Count रेजिस्टर 1 */
#घोषणा DSI_LCD1_WC_2			0x128   /* Word Count रेजिस्टर 2 */
	काष्ठा dsi_lcd_regs lcd1;
	u32 reserved10[11];
	काष्ठा dsi_lcd_regs lcd2;
पूर्ण;

#घोषणा DSI_LCD2_CTRL_0  0x180   /* DSI Active Panel 2 Control रेजिस्टर 0 */
#घोषणा DSI_LCD2_CTRL_1  0x184   /* DSI Active Panel 2 Control रेजिस्टर 1 */
#घोषणा DSI_LCD2_TIMING_0		0x190   /* Timing रेजिस्टर 0 */
#घोषणा DSI_LCD2_TIMING_1		0x194   /* Timing रेजिस्टर 1 */
#घोषणा DSI_LCD2_TIMING_2		0x198   /* Timing रेजिस्टर 2 */
#घोषणा DSI_LCD2_TIMING_3		0x19C   /* Timing रेजिस्टर 3 */
#घोषणा DSI_LCD2_WC_0			0x1A0   /* Word Count रेजिस्टर 0 */
#घोषणा DSI_LCD2_WC_1			0x1A4   /* Word Count रेजिस्टर 1 */
#घोषणा DSI_LCD2_WC_2			0x1A8	 /* Word Count रेजिस्टर 2 */

/*	DSI_CTRL_0		0x0000	DSI Control Register 0 */
#घोषणा DSI_CTRL_0_CFG_SOFT_RST			(1<<31)
#घोषणा DSI_CTRL_0_CFG_SOFT_RST_REG		(1<<30)
#घोषणा DSI_CTRL_0_CFG_LCD1_TX_EN		(1<<8)
#घोषणा DSI_CTRL_0_CFG_LCD1_SLV			(1<<4)
#घोषणा DSI_CTRL_0_CFG_LCD1_EN			(1<<0)

/*	DSI_CTRL_1		0x0004	DSI Control Register 1 */
#घोषणा DSI_CTRL_1_CFG_EOTP			(1<<8)
#घोषणा DSI_CTRL_1_CFG_RSVD			(2<<4)
#घोषणा DSI_CTRL_1_CFG_LCD2_VCH_NO_MASK		(3<<2)
#घोषणा DSI_CTRL_1_CFG_LCD2_VCH_NO_SHIFT	2
#घोषणा DSI_CTRL_1_CFG_LCD1_VCH_NO_MASK		(3<<0)
#घोषणा DSI_CTRL_1_CFG_LCD1_VCH_NO_SHIFT	0

/*	DSI_LCD1_CTRL_1	0x0104	DSI Active Panel 1 Control Register 1 */
/* LCD 1 Vsync Reset Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_VSYNC_RST_EN	(1<<31)
/* LCD 1 2K Pixel Buffer Mode Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_M2K_EN		(1<<30)
/*		Bit(s) DSI_LCD1_CTRL_1_RSRV_29_23 reserved */
/* Long Blanking Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HLP_PKT_EN	(1<<22)
/* Extra Long Blanking Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HEX_PKT_EN	(1<<21)
/* Front Porch Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HFP_PKT_EN	(1<<20)
/* hact Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HACT_PKT_EN	(1<<19)
/* Back Porch Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HBP_PKT_EN	(1<<18)
/* hse Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HSE_PKT_EN	(1<<17)
/* hsa Packet Enable */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HSA_PKT_EN	(1<<16)
/* All Item Enable after Pixel Data */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_ALL_SLOT_EN	(1<<15)
/* Extra Long Packet Enable after Pixel Data */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_HEX_SLOT_EN	(1<<14)
/*		Bit(s) DSI_LCD1_CTRL_1_RSRV_13_11 reserved */
/* Turn Around Bus at Last h Line */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_LAST_LINE_TURN	(1<<10)
/* Go to Low Power Every Frame */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_LPM_FRAME_EN	(1<<9)
/* Go to Low Power Every Line */
#घोषणा	DSI_LCD1_CTRL_1_CFG_L1_LPM_LINE_EN	(1<<8)
/*		Bit(s) DSI_LCD1_CTRL_1_RSRV_7_4 reserved */
/* DSI Transmission Mode क्रम LCD 1 */
#घोषणा DSI_LCD1_CTRL_1_CFG_L1_BURST_MODE_SHIFT	2
#घोषणा DSI_LCD1_CTRL_1_CFG_L1_BURST_MODE_MASK	(3<<2)
/* LCD 1 Input Data RGB Mode क्रम LCD 1 */
#घोषणा DSI_LCD2_CTRL_1_CFG_L1_RGB_TYPE_SHIFT	0
#घोषणा DSI_LCD2_CTRL_1_CFG_L1_RGB_TYPE_MASK	(3<<2)

/*	DSI_PHY_CTRL_2		0x0088	DPHY Control Register 2 */
/*		Bit(s) DSI_PHY_CTRL_2_RSRV_31_12 reserved */
/* DPHY LP Receiver Enable */
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_RESC_EN_MASK	(0xf<<8)
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_RESC_EN_SHIFT	8
/* DPHY Data Lane Enable */
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_EN_MASK		(0xf<<4)
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_EN_SHIFT		4
/* DPHY Bus Turn Around */
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_TURN_MASK		(0xf)
#घोषणा	DSI_PHY_CTRL_2_CFG_CSR_LANE_TURN_SHIFT		0

/*	DSI_CPU_CMD_1		0x0024	DSI CPU Packet Command Register 1 */
/*		Bit(s) DSI_CPU_CMD_1_RSRV_31_24 reserved */
/* LPDT TX Enable */
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_LPDT_MASK		(0xf<<20)
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_LPDT_SHIFT		20
/* ULPS TX Enable */
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_ULPS_MASK		(0xf<<16)
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_ULPS_SHIFT		16
/* Low Power TX Trigger Code */
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_TRIGGER_CODE_MASK	(0xffff)
#घोषणा	DSI_CPU_CMD_1_CFG_TXLP_TRIGGER_CODE_SHIFT	0

/*	DSI_PHY_TIME_0	0x00c0	DPHY Timing Control Register 0 */
/* Length of HS Exit Period in tx_clk_esc Cycles */
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_EXIT_MASK	(0xff<<24)
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_EXIT_SHIFT	24
/* DPHY HS Trail Period Length */
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_TRAIL_MASK	(0xff<<16)
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_TRAIL_SHIFT	16
/* DPHY HS Zero State Length */
#घोषणा	DSI_PHY_TIME_0_CDG_CSR_TIME_HS_ZERO_MASK	(0xff<<8)
#घोषणा	DSI_PHY_TIME_0_CDG_CSR_TIME_HS_ZERO_SHIFT	8
/* DPHY HS Prepare State Length */
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_PREP_MASK	(0xff)
#घोषणा	DSI_PHY_TIME_0_CFG_CSR_TIME_HS_PREP_SHIFT	0

/*	DSI_PHY_TIME_1		0x00c4	DPHY Timing Control Register 1 */
/* Time to Drive LP-00 by New Transmitter */
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_TA_GET_MASK		(0xff<<24)
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_TA_GET_SHIFT	24
/* Time to Drive LP-00 after Turn Request */
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_TA_GO_MASK		(0xff<<16)
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_TA_GO_SHIFT		16
/* DPHY HS Wakeup Period Length */
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_WAKEUP_MASK		(0xffff)
#घोषणा	DSI_PHY_TIME_1_CFG_CSR_TIME_WAKEUP_SHIFT	0

/*	DSI_PHY_TIME_2		0x00c8	DPHY Timing Control Register 2 */
/* DPHY CLK Exit Period Length */
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_EXIT_MASK	(0xff<<24)
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_EXIT_SHIFT	24
/* DPHY CLK Trail Period Length */
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_TRAIL_MASK	(0xff<<16)
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_TRAIL_SHIFT	16
/* DPHY CLK Zero State Length */
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_ZERO_MASK	(0xff<<8)
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_ZERO_SHIFT	8
/* DPHY CLK LP Length */
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_LPX_MASK		(0xff)
#घोषणा	DSI_PHY_TIME_2_CFG_CSR_TIME_CK_LPX_SHIFT	0

/*	DSI_PHY_TIME_3		0x00cc	DPHY Timing Control Register 3 */
/*		Bit(s) DSI_PHY_TIME_3_RSRV_31_16 reserved */
/* DPHY LP Length */
#घोषणा	DSI_PHY_TIME_3_CFG_CSR_TIME_LPX_MASK		(0xff<<8)
#घोषणा	DSI_PHY_TIME_3_CFG_CSR_TIME_LPX_SHIFT		8
/* DPHY HS req to rdy Length */
#घोषणा	DSI_PHY_TIME_3_CFG_CSR_TIME_REQRDY_MASK		(0xff)
#घोषणा	DSI_PHY_TIME_3_CFG_CSR_TIME_REQRDY_SHIFT	0

#घोषणा DSI_ESC_CLK				66  /* Unit: Mhz */
#घोषणा DSI_ESC_CLK_T				15  /* Unit: ns */

/* LVDS */
/* LVDS_PHY_CTRL */
#घोषणा LVDS_PHY_CTL				0x2A4
#घोषणा LVDS_PLL_LOCK				(1 << 31)
#घोषणा LVDS_PHY_EXT_MASK			(7 << 28)
#घोषणा LVDS_PHY_EXT_SHIFT			(28)
#घोषणा LVDS_CLK_PHASE_MASK			(0x7f << 16)
#घोषणा LVDS_CLK_PHASE_SHIFT			(16)
#घोषणा LVDS_SSC_RESET_EXT			(1 << 13)
#घोषणा LVDS_SSC_MODE_DOWN_SPREAD		(1 << 12)
#घोषणा LVDS_SSC_EN				(1 << 11)
#घोषणा LVDS_PU_PLL				(1 << 10)
#घोषणा LVDS_PU_TX				(1 << 9)
#घोषणा LVDS_PU_IVREF				(1 << 8)
#घोषणा LVDS_CLK_SEL				(1 << 7)
#घोषणा LVDS_CLK_SEL_LVDS_PCLK			(1 << 7)
#घोषणा LVDS_PD_CH_MASK				(0x3f << 1)
#घोषणा LVDS_PD_CH(ch)				((ch) << 1)
#घोषणा LVDS_RST				(1 << 0)

#घोषणा LVDS_PHY_CTL_EXT	0x2A8

/* LVDS_PHY_CTRL_EXT1 */
#घोषणा LVDS_SSC_RNGE_MASK			(0x7ff << 16)
#घोषणा LVDS_SSC_RNGE_SHIFT			(16)
#घोषणा LVDS_RESERVE_IN_MASK			(0xf << 12)
#घोषणा LVDS_RESERVE_IN_SHIFT			(12)
#घोषणा LVDS_TEST_MON_MASK			(0x7 << 8)
#घोषणा LVDS_TEST_MON_SHIFT			(8)
#घोषणा LVDS_POL_SWAP_MASK			(0x3f << 0)
#घोषणा LVDS_POL_SWAP_SHIFT			(0)

/* LVDS_PHY_CTRL_EXT2 */
#घोषणा LVDS_TX_DIF_AMP_MASK			(0xf << 24)
#घोषणा LVDS_TX_DIF_AMP_SHIFT			(24)
#घोषणा LVDS_TX_DIF_CM_MASK			(0x3 << 22)
#घोषणा LVDS_TX_DIF_CM_SHIFT			(22)
#घोषणा LVDS_SELLV_TXCLK_MASK			(0x1f << 16)
#घोषणा LVDS_SELLV_TXCLK_SHIFT			(16)
#घोषणा LVDS_TX_CMFB_EN				(0x1 << 15)
#घोषणा LVDS_TX_TERM_EN				(0x1 << 14)
#घोषणा LVDS_SELLV_TXDATA_MASK			(0x1f << 8)
#घोषणा LVDS_SELLV_TXDATA_SHIFT			(8)
#घोषणा LVDS_SELLV_OP7_MASK			(0x3 << 6)
#घोषणा LVDS_SELLV_OP7_SHIFT			(6)
#घोषणा LVDS_SELLV_OP6_MASK			(0x3 << 4)
#घोषणा LVDS_SELLV_OP6_SHIFT			(4)
#घोषणा LVDS_SELLV_OP9_MASK			(0x3 << 2)
#घोषणा LVDS_SELLV_OP9_SHIFT			(2)
#घोषणा LVDS_STRESSTST_EN			(0x1 << 0)

/* LVDS_PHY_CTRL_EXT3 */
#घोषणा LVDS_KVCO_MASK				(0xf << 28)
#घोषणा LVDS_KVCO_SHIFT				(28)
#घोषणा LVDS_CTUNE_MASK				(0x3 << 26)
#घोषणा LVDS_CTUNE_SHIFT			(26)
#घोषणा LVDS_VREG_IVREF_MASK			(0x3 << 24)
#घोषणा LVDS_VREG_IVREF_SHIFT			(24)
#घोषणा LVDS_VDDL_MASK				(0xf << 20)
#घोषणा LVDS_VDDL_SHIFT				(20)
#घोषणा LVDS_VDDM_MASK				(0x3 << 18)
#घोषणा LVDS_VDDM_SHIFT				(18)
#घोषणा LVDS_FBDIV_MASK				(0xf << 8)
#घोषणा LVDS_FBDIV_SHIFT			(8)
#घोषणा LVDS_REFDIV_MASK			(0x7f << 0)
#घोषणा LVDS_REFDIV_SHIFT			(0)

/* LVDS_PHY_CTRL_EXT4 */
#घोषणा LVDS_SSC_FREQ_DIV_MASK			(0xffff << 16)
#घोषणा LVDS_SSC_FREQ_DIV_SHIFT			(16)
#घोषणा LVDS_INTPI_MASK				(0xf << 12)
#घोषणा LVDS_INTPI_SHIFT			(12)
#घोषणा LVDS_VCODIV_SEL_SE_MASK			(0xf << 8)
#घोषणा LVDS_VCODIV_SEL_SE_SHIFT		(8)
#घोषणा LVDS_RESET_INTP_EXT			(0x1 << 7)
#घोषणा LVDS_VCO_VRNG_MASK			(0x7 << 4)
#घोषणा LVDS_VCO_VRNG_SHIFT			(4)
#घोषणा LVDS_PI_EN				(0x1 << 3)
#घोषणा LVDS_ICP_MASK				(0x7 << 0)
#घोषणा LVDS_ICP_SHIFT				(0)

/* LVDS_PHY_CTRL_EXT5 */
#घोषणा LVDS_FREQ_OFFSET_MASK			(0x1ffff << 15)
#घोषणा LVDS_FREQ_OFFSET_SHIFT			(15)
#घोषणा LVDS_FREQ_OFFSET_VALID			(0x1 << 2)
#घोषणा LVDS_FREQ_OFFSET_MODE_CK_DIV4_OUT	(0x1 << 1)
#घोषणा LVDS_FREQ_OFFSET_MODE_EN		(0x1 << 0)

क्रमागत अणु
	PATH_PN = 0,
	PATH_TV,
	PATH_P2,
पूर्ण;

/*
 * mmp path describes part of mmp path related info:
 * which is hiden in display driver and not exported to buffer driver
 */
काष्ठा mmphw_ctrl;
काष्ठा mmphw_path_plat अणु
	पूर्णांक id;
	काष्ठा mmphw_ctrl *ctrl;
	काष्ठा mmp_path *path;
	u32 path_config;
	u32 link_config;
	u32 dsi_rbswap;
पूर्ण;

/* mmp ctrl describes mmp controller related info */
काष्ठा mmphw_ctrl अणु
	/* platक्रमm related, get from config */
	स्थिर अक्षर *name;
	पूर्णांक irq;
	व्योम __iomem *reg_base;
	काष्ठा clk *clk;

	/* sys info */
	काष्ठा device *dev;

	/* state */
	पूर्णांक खोलो_count;
	पूर्णांक status;
	काष्ठा mutex access_ok;

	/*pathes*/
	पूर्णांक path_num;
	काष्ठा mmphw_path_plat path_plats[];
पूर्ण;

अटल अंतरभूत पूर्णांक overlay_is_vid(काष्ठा mmp_overlay *overlay)
अणु
	वापस overlay->dmafetch_id & 1;
पूर्ण

अटल अंतरभूत काष्ठा mmphw_path_plat *path_to_path_plat(काष्ठा mmp_path *path)
अणु
	वापस (काष्ठा mmphw_path_plat *)path->plat_data;
पूर्ण

अटल अंतरभूत काष्ठा mmphw_ctrl *path_to_ctrl(काष्ठा mmp_path *path)
अणु
	वापस path_to_path_plat(path)->ctrl;
पूर्ण

अटल अंतरभूत काष्ठा mmphw_ctrl *overlay_to_ctrl(काष्ठा mmp_overlay *overlay)
अणु
	वापस path_to_ctrl(overlay->path);
पूर्ण

अटल अंतरभूत व्योम __iomem *ctrl_regs(काष्ठा mmp_path *path)
अणु
	वापस path_to_ctrl(path)->reg_base;
पूर्ण

/* path regs, क्रम regs symmetrical क्रम both pathes */
अटल अंतरभूत काष्ठा lcd_regs *path_regs(काष्ठा mmp_path *path)
अणु
	अगर (path->id == PATH_PN)
		वापस (काष्ठा lcd_regs __क्रमce *)(ctrl_regs(path) + 0xc0);
	अन्यथा अगर (path->id == PATH_TV)
		वापस (काष्ठा lcd_regs __क्रमce  *)ctrl_regs(path);
	अन्यथा अगर (path->id == PATH_P2)
		वापस (काष्ठा lcd_regs __क्रमce *)(ctrl_regs(path) + 0x200);
	अन्यथा अणु
		dev_err(path->dev, "path id %d invalid\n", path->id);
		BUG_ON(1);
		वापस शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MMP_DISP_SPI
बाह्य पूर्णांक lcd_spi_रेजिस्टर(काष्ठा mmphw_ctrl *ctrl);
#पूर्ण_अगर
#पूर्ण_अगर	/* _MMP_CTRL_H_ */
