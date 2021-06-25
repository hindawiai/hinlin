<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PXA168FB_H__
#घोषणा __PXA168FB_H__

/* ------------< LCD रेजिस्टर >------------ */
/* Video Frame 0&1 start address रेजिस्टरs */
#घोषणा	LCD_SPU_DMA_START_ADDR_Y0		0x00C0
#घोषणा	LCD_SPU_DMA_START_ADDR_U0		0x00C4
#घोषणा	LCD_SPU_DMA_START_ADDR_V0		0x00C8
#घोषणा LCD_CFG_DMA_START_ADDR_0		0x00CC /* Cmd address */
#घोषणा	LCD_SPU_DMA_START_ADDR_Y1		0x00D0
#घोषणा	LCD_SPU_DMA_START_ADDR_U1		0x00D4
#घोषणा	LCD_SPU_DMA_START_ADDR_V1		0x00D8
#घोषणा LCD_CFG_DMA_START_ADDR_1		0x00DC /* Cmd address */

/* YC & UV Pitch */
#घोषणा LCD_SPU_DMA_PITCH_YC			0x00E0
#घोषणा     SPU_DMA_PITCH_C(c)			((c) << 16)
#घोषणा     SPU_DMA_PITCH_Y(y)			(y)
#घोषणा LCD_SPU_DMA_PITCH_UV			0x00E4
#घोषणा     SPU_DMA_PITCH_V(v)			((v) << 16)
#घोषणा     SPU_DMA_PITCH_U(u)			(u)

/* Video Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPUT_DMA_OVSA_HPXL_VLN		0x00E8
#घोषणा     CFG_DMA_OVSA_VLN(y)			((y) << 16) /* 0~0xfff */
#घोषणा     CFG_DMA_OVSA_HPXL(x)		(x)     /* 0~0xfff */

/* Video Size Register */
#घोषणा LCD_SPU_DMA_HPXL_VLN			0x00EC
#घोषणा     CFG_DMA_VLN(y)			((y) << 16)
#घोषणा     CFG_DMA_HPXL(x)			(x)

/* Video Size After zooming Register */
#घोषणा LCD_SPU_DZM_HPXL_VLN			0x00F0
#घोषणा     CFG_DZM_VLN(y)			((y) << 16)
#घोषणा     CFG_DZM_HPXL(x)			(x)

/* Graphic Frame 0&1 Starting Address Register */
#घोषणा LCD_CFG_GRA_START_ADDR0			0x00F4
#घोषणा LCD_CFG_GRA_START_ADDR1			0x00F8

/* Graphic Frame Pitch */
#घोषणा LCD_CFG_GRA_PITCH			0x00FC

/* Graphic Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPU_GRA_OVSA_HPXL_VLN		0x0100
#घोषणा     CFG_GRA_OVSA_VLN(y)			((y) << 16)
#घोषणा     CFG_GRA_OVSA_HPXL(x)		(x)

/* Graphic Size Register */
#घोषणा LCD_SPU_GRA_HPXL_VLN			0x0104
#घोषणा     CFG_GRA_VLN(y)			((y) << 16)
#घोषणा     CFG_GRA_HPXL(x)			(x)

/* Graphic Size after Zooming Register */
#घोषणा LCD_SPU_GZM_HPXL_VLN			0x0108
#घोषणा     CFG_GZM_VLN(y)			((y) << 16)
#घोषणा     CFG_GZM_HPXL(x)			(x)

/* HW Cursor Starting Poपूर्णांक on Screen Register */
#घोषणा LCD_SPU_HWC_OVSA_HPXL_VLN		0x010C
#घोषणा     CFG_HWC_OVSA_VLN(y)			((y) << 16)
#घोषणा     CFG_HWC_OVSA_HPXL(x)		(x)

/* HW Cursor Size */
#घोषणा LCD_SPU_HWC_HPXL_VLN			0x0110
#घोषणा     CFG_HWC_VLN(y)			((y) << 16)
#घोषणा     CFG_HWC_HPXL(x)			(x)

/* Total Screen Size Register */
#घोषणा LCD_SPUT_V_H_TOTAL			0x0114
#घोषणा     CFG_V_TOTAL(y)			((y) << 16)
#घोषणा     CFG_H_TOTAL(x)			(x)

/* Total Screen Active Size Register */
#घोषणा LCD_SPU_V_H_ACTIVE			0x0118
#घोषणा     CFG_V_ACTIVE(y)			((y) << 16)
#घोषणा     CFG_H_ACTIVE(x)			(x)

/* Screen H&V Porch Register */
#घोषणा LCD_SPU_H_PORCH				0x011C
#घोषणा     CFG_H_BACK_PORCH(b)			((b) << 16)
#घोषणा     CFG_H_FRONT_PORCH(f)		(f)
#घोषणा LCD_SPU_V_PORCH				0x0120
#घोषणा     CFG_V_BACK_PORCH(b)			((b) << 16)
#घोषणा     CFG_V_FRONT_PORCH(f)		(f)

/* Screen Blank Color Register */
#घोषणा LCD_SPU_BLANKCOLOR			0x0124
#घोषणा     CFG_BLANKCOLOR_MASK			0x00FFFFFF
#घोषणा     CFG_BLANKCOLOR_R_MASK		0x000000FF
#घोषणा     CFG_BLANKCOLOR_G_MASK		0x0000FF00
#घोषणा     CFG_BLANKCOLOR_B_MASK		0x00FF0000

/* HW Cursor Color 1&2 Register */
#घोषणा LCD_SPU_ALPHA_COLOR1			0x0128
#घोषणा     CFG_HWC_COLOR1			0x00FFFFFF
#घोषणा     CFG_HWC_COLOR1_R(red)		((red) << 16)
#घोषणा     CFG_HWC_COLOR1_G(green)		((green) << 8)
#घोषणा     CFG_HWC_COLOR1_B(blue)		(blue)
#घोषणा     CFG_HWC_COLOR1_R_MASK		0x000000FF
#घोषणा     CFG_HWC_COLOR1_G_MASK		0x0000FF00
#घोषणा     CFG_HWC_COLOR1_B_MASK		0x00FF0000
#घोषणा LCD_SPU_ALPHA_COLOR2			0x012C
#घोषणा     CFG_HWC_COLOR2			0x00FFFFFF
#घोषणा     CFG_HWC_COLOR2_R_MASK		0x000000FF
#घोषणा     CFG_HWC_COLOR2_G_MASK		0x0000FF00
#घोषणा     CFG_HWC_COLOR2_B_MASK		0x00FF0000

/* Video YUV Color Key Control */
#घोषणा LCD_SPU_COLORKEY_Y			0x0130
#घोषणा     CFG_CKEY_Y2(y2)			((y2) << 24)
#घोषणा     CFG_CKEY_Y2_MASK			0xFF000000
#घोषणा     CFG_CKEY_Y1(y1)			((y1) << 16)
#घोषणा     CFG_CKEY_Y1_MASK			0x00FF0000
#घोषणा     CFG_CKEY_Y(y)			((y) << 8)
#घोषणा     CFG_CKEY_Y_MASK			0x0000FF00
#घोषणा     CFG_ALPHA_Y(y)			(y)
#घोषणा     CFG_ALPHA_Y_MASK			0x000000FF
#घोषणा LCD_SPU_COLORKEY_U			0x0134
#घोषणा     CFG_CKEY_U2(u2)			((u2) << 24)
#घोषणा     CFG_CKEY_U2_MASK			0xFF000000
#घोषणा     CFG_CKEY_U1(u1)			((u1) << 16)
#घोषणा     CFG_CKEY_U1_MASK			0x00FF0000
#घोषणा     CFG_CKEY_U(u)			((u) << 8)
#घोषणा     CFG_CKEY_U_MASK			0x0000FF00
#घोषणा     CFG_ALPHA_U(u)			(u)
#घोषणा     CFG_ALPHA_U_MASK			0x000000FF
#घोषणा LCD_SPU_COLORKEY_V			0x0138
#घोषणा     CFG_CKEY_V2(v2)			((v2) << 24)
#घोषणा     CFG_CKEY_V2_MASK			0xFF000000
#घोषणा     CFG_CKEY_V1(v1)			((v1) << 16)
#घोषणा     CFG_CKEY_V1_MASK			0x00FF0000
#घोषणा     CFG_CKEY_V(v)			((v) << 8)
#घोषणा     CFG_CKEY_V_MASK			0x0000FF00
#घोषणा     CFG_ALPHA_V(v)			(v)
#घोषणा     CFG_ALPHA_V_MASK			0x000000FF

/* SPI Read Data Register */
#घोषणा LCD_SPU_SPI_RXDATA			0x0140

/* Smart Panel Read Data Register */
#घोषणा LCD_SPU_ISA_RSDATA			0x0144
#घोषणा     ISA_RXDATA_16BIT_1_DATA_MASK	0x000000FF
#घोषणा     ISA_RXDATA_16BIT_2_DATA_MASK	0x0000FF00
#घोषणा     ISA_RXDATA_16BIT_3_DATA_MASK	0x00FF0000
#घोषणा     ISA_RXDATA_16BIT_4_DATA_MASK	0xFF000000
#घोषणा     ISA_RXDATA_32BIT_1_DATA_MASK	0x00FFFFFF

/* HWC SRAM Read Data Register */
#घोषणा LCD_SPU_HWC_RDDAT			0x0158

/* Gamma Table SRAM Read Data Register */
#घोषणा LCD_SPU_GAMMA_RDDAT			0x015c
#घोषणा     CFG_GAMMA_RDDAT_MASK		0x000000FF

/* Palette Table SRAM Read Data Register */
#घोषणा LCD_SPU_PALETTE_RDDAT			0x0160
#घोषणा     CFG_PALETTE_RDDAT_MASK		0x00FFFFFF

/* I/O Pads Input Read Only Register */
#घोषणा LCD_SPU_IOPAD_IN			0x0178
#घोषणा     CFG_IOPAD_IN_MASK			0x0FFFFFFF

/* Reserved Read Only Registers */
#घोषणा LCD_CFG_RDREG5F				0x017C
#घोषणा     IRE_FRAME_CNT_MASK			0x000000C0
#घोषणा     IPE_FRAME_CNT_MASK			0x00000030
#घोषणा     GRA_FRAME_CNT_MASK			0x0000000C  /* Graphic */
#घोषणा     DMA_FRAME_CNT_MASK			0x00000003  /* Video */

/* SPI Control Register. */
#घोषणा LCD_SPU_SPI_CTRL			0x0180
#घोषणा     CFG_SCLKCNT(भाग)			((भाग) << 24)  /* 0xFF~0x2 */
#घोषणा     CFG_SCLKCNT_MASK			0xFF000000
#घोषणा     CFG_RXBITS(rx)			((rx) << 16)   /* 0x1F~0x1 */
#घोषणा     CFG_RXBITS_MASK			0x00FF0000
#घोषणा     CFG_TXBITS(tx)			((tx) << 8)    /* 0x1F~0x1 */
#घोषणा     CFG_TXBITS_MASK			0x0000FF00
#घोषणा     CFG_CLKINV(clk)			((clk) << 7)
#घोषणा     CFG_CLKINV_MASK			0x00000080
#घोषणा     CFG_KEEPXFER(transfer)		((transfer) << 6)
#घोषणा     CFG_KEEPXFER_MASK			0x00000040
#घोषणा     CFG_RXBITSTO0(rx)			((rx) << 5)
#घोषणा     CFG_RXBITSTO0_MASK			0x00000020
#घोषणा     CFG_TXBITSTO0(tx)			((tx) << 4)
#घोषणा     CFG_TXBITSTO0_MASK			0x00000010
#घोषणा     CFG_SPI_ENA(spi)			((spi) << 3)
#घोषणा     CFG_SPI_ENA_MASK			0x00000008
#घोषणा     CFG_SPI_SEL(spi)			((spi) << 2)
#घोषणा     CFG_SPI_SEL_MASK			0x00000004
#घोषणा     CFG_SPI_3W4WB(wire)			((wire) << 1)
#घोषणा     CFG_SPI_3W4WB_MASK			0x00000002
#घोषणा     CFG_SPI_START(start)		(start)
#घोषणा     CFG_SPI_START_MASK			0x00000001

/* SPI Tx Data Register */
#घोषणा LCD_SPU_SPI_TXDATA			0x0184

/*
   1. Smart Pannel 8-bit Bus Control Register.
   2. AHB Slave Path Data Port Register
*/
#घोषणा LCD_SPU_SMPN_CTRL			0x0188

/* DMA Control 0 Register */
#घोषणा LCD_SPU_DMA_CTRL0			0x0190
#घोषणा     CFG_NOBLENDING(nb)			((nb) << 31)
#घोषणा     CFG_NOBLENDING_MASK			0x80000000
#घोषणा     CFG_GAMMA_ENA(gn)			((gn) << 30)
#घोषणा     CFG_GAMMA_ENA_MASK			0x40000000
#घोषणा     CFG_CBSH_ENA(cn)			((cn) << 29)
#घोषणा     CFG_CBSH_ENA_MASK			0x20000000
#घोषणा     CFG_PALETTE_ENA(pn)			((pn) << 28)
#घोषणा     CFG_PALETTE_ENA_MASK		0x10000000
#घोषणा     CFG_ARBFAST_ENA(an)			((an) << 27)
#घोषणा     CFG_ARBFAST_ENA_MASK		0x08000000
#घोषणा     CFG_HWC_1BITMOD(mode)		((mode) << 26)
#घोषणा     CFG_HWC_1BITMOD_MASK		0x04000000
#घोषणा     CFG_HWC_1BITENA(mn)			((mn) << 25)
#घोषणा     CFG_HWC_1BITENA_MASK		0x02000000
#घोषणा     CFG_HWC_ENA(cn)		        ((cn) << 24)
#घोषणा     CFG_HWC_ENA_MASK			0x01000000
#घोषणा     CFG_DMAFORMAT(dmaक्रमmat)		((dmaक्रमmat) << 20)
#घोषणा     CFG_DMAFORMAT_MASK			0x00F00000
#घोषणा     CFG_GRAFORMAT(graक्रमmat)		((graक्रमmat) << 16)
#घोषणा     CFG_GRAFORMAT_MASK			0x000F0000
/* क्रम graphic part */
#घोषणा     CFG_GRA_FTOGGLE(toggle)		((toggle) << 15)
#घोषणा     CFG_GRA_FTOGGLE_MASK		0x00008000
#घोषणा     CFG_GRA_HSMOOTH(smooth)		((smooth) << 14)
#घोषणा     CFG_GRA_HSMOOTH_MASK		0x00004000
#घोषणा     CFG_GRA_TSTMODE(test)		((test) << 13)
#घोषणा     CFG_GRA_TSTMODE_MASK		0x00002000
#घोषणा     CFG_GRA_SWAPRB(swap)		((swap) << 12)
#घोषणा     CFG_GRA_SWAPRB_MASK			0x00001000
#घोषणा     CFG_GRA_SWAPUV(swap)		((swap) << 11)
#घोषणा     CFG_GRA_SWAPUV_MASK			0x00000800
#घोषणा     CFG_GRA_SWAPYU(swap)		((swap) << 10)
#घोषणा     CFG_GRA_SWAPYU_MASK			0x00000400
#घोषणा     CFG_YUV2RGB_GRA(cvrt)		((cvrt) << 9)
#घोषणा     CFG_YUV2RGB_GRA_MASK		0x00000200
#घोषणा     CFG_GRA_ENA(gra)			((gra) << 8)
#घोषणा     CFG_GRA_ENA_MASK			0x00000100
/* क्रम video part */
#घोषणा     CFG_DMA_FTOGGLE(toggle)		((toggle) << 7)
#घोषणा     CFG_DMA_FTOGGLE_MASK		0x00000080
#घोषणा     CFG_DMA_HSMOOTH(smooth)		((smooth) << 6)
#घोषणा     CFG_DMA_HSMOOTH_MASK		0x00000040
#घोषणा     CFG_DMA_TSTMODE(test)		((test) << 5)
#घोषणा     CFG_DMA_TSTMODE_MASK		0x00000020
#घोषणा     CFG_DMA_SWAPRB(swap)		((swap) << 4)
#घोषणा     CFG_DMA_SWAPRB_MASK			0x00000010
#घोषणा     CFG_DMA_SWAPUV(swap)		((swap) << 3)
#घोषणा     CFG_DMA_SWAPUV_MASK			0x00000008
#घोषणा     CFG_DMA_SWAPYU(swap)		((swap) << 2)
#घोषणा     CFG_DMA_SWAPYU_MASK			0x00000004
#घोषणा     CFG_DMA_SWAP_MASK			0x0000001C
#घोषणा     CFG_YUV2RGB_DMA(cvrt)		((cvrt) << 1)
#घोषणा     CFG_YUV2RGB_DMA_MASK		0x00000002
#घोषणा     CFG_DMA_ENA(video)			(video)
#घोषणा     CFG_DMA_ENA_MASK			0x00000001

/* DMA Control 1 Register */
#घोषणा LCD_SPU_DMA_CTRL1			0x0194
#घोषणा     CFG_FRAME_TRIG(trig)		((trig) << 31)
#घोषणा     CFG_FRAME_TRIG_MASK			0x80000000
#घोषणा     CFG_VSYNC_TRIG(trig)		((trig) << 28)
#घोषणा     CFG_VSYNC_TRIG_MASK			0x70000000
#घोषणा     CFG_VSYNC_INV(inv)			((inv) << 27)
#घोषणा     CFG_VSYNC_INV_MASK			0x08000000
#घोषणा     CFG_COLOR_KEY_MODE(cmode)		((cmode) << 24)
#घोषणा     CFG_COLOR_KEY_MASK			0x07000000
#घोषणा     CFG_CARRY(carry)			((carry) << 23)
#घोषणा     CFG_CARRY_MASK			0x00800000
#घोषणा     CFG_LNBUF_ENA(lnbuf)		((lnbuf) << 22)
#घोषणा     CFG_LNBUF_ENA_MASK			0x00400000
#घोषणा     CFG_GATED_ENA(gated)		((gated) << 21)
#घोषणा     CFG_GATED_ENA_MASK			0x00200000
#घोषणा     CFG_PWRDN_ENA(घातer)		((घातer) << 20)
#घोषणा     CFG_PWRDN_ENA_MASK			0x00100000
#घोषणा     CFG_DSCALE(dscale)			((dscale) << 18)
#घोषणा     CFG_DSCALE_MASK			0x000C0000
#घोषणा     CFG_ALPHA_MODE(amode)		((amode) << 16)
#घोषणा     CFG_ALPHA_MODE_MASK			0x00030000
#घोषणा     CFG_ALPHA(alpha)			((alpha) << 8)
#घोषणा     CFG_ALPHA_MASK			0x0000FF00
#घोषणा     CFG_PXLCMD(pxlcmd)			(pxlcmd)
#घोषणा     CFG_PXLCMD_MASK			0x000000FF

/* SRAM Control Register */
#घोषणा LCD_SPU_SRAM_CTRL			0x0198
#घोषणा     CFG_SRAM_INIT_WR_RD(mode)		((mode) << 14)
#घोषणा     CFG_SRAM_INIT_WR_RD_MASK		0x0000C000
#घोषणा     CFG_SRAM_ADDR_LCDID(id)		((id) << 8)
#घोषणा     CFG_SRAM_ADDR_LCDID_MASK		0x00000F00
#घोषणा     CFG_SRAM_ADDR(addr)			(addr)
#घोषणा     CFG_SRAM_ADDR_MASK			0x000000FF

/* SRAM Write Data Register */
#घोषणा LCD_SPU_SRAM_WRDAT			0x019C

/* SRAM RTC/WTC Control Register */
#घोषणा LCD_SPU_SRAM_PARA0			0x01A0

/* SRAM Power Down Control Register */
#घोषणा LCD_SPU_SRAM_PARA1			0x01A4
#घोषणा     CFG_CSB_256x32(hwc)			((hwc) << 15)	/* HWC */
#घोषणा     CFG_CSB_256x32_MASK			0x00008000
#घोषणा     CFG_CSB_256x24(palette)		((palette) << 14)	/* Palette */
#घोषणा     CFG_CSB_256x24_MASK			0x00004000
#घोषणा     CFG_CSB_256x8(gamma)		((gamma) << 13)	/* Gamma */
#घोषणा     CFG_CSB_256x8_MASK			0x00002000
#घोषणा     CFG_PDWN256x32(pdwn)		((pdwn) << 7)	/* HWC */
#घोषणा     CFG_PDWN256x32_MASK			0x00000080
#घोषणा     CFG_PDWN256x24(pdwn)		((pdwn) << 6)	/* Palette */
#घोषणा     CFG_PDWN256x24_MASK			0x00000040
#घोषणा     CFG_PDWN256x8(pdwn)			((pdwn) << 5)	/* Gamma */
#घोषणा     CFG_PDWN256x8_MASK			0x00000020
#घोषणा     CFG_PDWN32x32(pdwn)			((pdwn) << 3)
#घोषणा     CFG_PDWN32x32_MASK			0x00000008
#घोषणा     CFG_PDWN16x66(pdwn)			((pdwn) << 2)
#घोषणा     CFG_PDWN16x66_MASK			0x00000004
#घोषणा     CFG_PDWN32x66(pdwn)			((pdwn) << 1)
#घोषणा     CFG_PDWN32x66_MASK			0x00000002
#घोषणा     CFG_PDWN64x66(pdwn)			(pdwn)
#घोषणा     CFG_PDWN64x66_MASK			0x00000001

/* Smart or Dumb Panel Clock Divider */
#घोषणा LCD_CFG_SCLK_DIV			0x01A8
#घोषणा     SCLK_SOURCE_SELECT(src)		((src) << 31)
#घोषणा     SCLK_SOURCE_SELECT_MASK		0x80000000
#घोषणा     CLK_FRACDIV(frac)			((frac) << 16)
#घोषणा     CLK_FRACDIV_MASK			0x0FFF0000
#घोषणा     CLK_INT_DIV(भाग)			(भाग)
#घोषणा     CLK_INT_DIV_MASK			0x0000FFFF

/* Video Contrast Register */
#घोषणा LCD_SPU_CONTRAST			0x01AC
#घोषणा     CFG_BRIGHTNESS(bright)		((bright) << 16)
#घोषणा     CFG_BRIGHTNESS_MASK			0xFFFF0000
#घोषणा     CFG_CONTRAST(contrast)		(contrast)
#घोषणा     CFG_CONTRAST_MASK			0x0000FFFF

/* Video Saturation Register */
#घोषणा LCD_SPU_SATURATION			0x01B0
#घोषणा     CFG_C_MULTS(mult)			((mult) << 16)
#घोषणा     CFG_C_MULTS_MASK			0xFFFF0000
#घोषणा     CFG_SATURATION(sat)			(sat)
#घोषणा     CFG_SATURATION_MASK			0x0000FFFF

/* Video Hue Adjust Register */
#घोषणा LCD_SPU_CBSH_HUE			0x01B4
#घोषणा     CFG_SIN0(sin0)			((sin0) << 16)
#घोषणा     CFG_SIN0_MASK			0xFFFF0000
#घोषणा     CFG_COS0(con0)			(con0)
#घोषणा     CFG_COS0_MASK			0x0000FFFF

/* Dump LCD Panel Control Register */
#घोषणा LCD_SPU_DUMB_CTRL			0x01B8
#घोषणा     CFG_DUMBMODE(mode)			((mode) << 28)
#घोषणा     CFG_DUMBMODE_MASK			0xF0000000
#घोषणा     CFG_LCDGPIO_O(data)			((data) << 20)
#घोषणा     CFG_LCDGPIO_O_MASK			0x0FF00000
#घोषणा     CFG_LCDGPIO_ENA(gpio)		((gpio) << 12)
#घोषणा     CFG_LCDGPIO_ENA_MASK		0x000FF000
#घोषणा     CFG_BIAS_OUT(bias)			((bias) << 8)
#घोषणा     CFG_BIAS_OUT_MASK			0x00000100
#घोषणा     CFG_REVERSE_RGB(rRGB)		((rRGB) << 7)
#घोषणा     CFG_REVERSE_RGB_MASK		0x00000080
#घोषणा     CFG_INV_COMPBLANK(blank)		((blank) << 6)
#घोषणा     CFG_INV_COMPBLANK_MASK		0x00000040
#घोषणा     CFG_INV_COMPSYNC(sync)		((sync) << 5)
#घोषणा     CFG_INV_COMPSYNC_MASK		0x00000020
#घोषणा     CFG_INV_HENA(hena)			((hena) << 4)
#घोषणा     CFG_INV_HENA_MASK			0x00000010
#घोषणा     CFG_INV_VSYNC(vsync)		((vsync) << 3)
#घोषणा     CFG_INV_VSYNC_MASK			0x00000008
#घोषणा     CFG_INV_HSYNC(hsync)		((hsync) << 2)
#घोषणा     CFG_INV_HSYNC_MASK			0x00000004
#घोषणा     CFG_INV_PCLK(pclk)			((pclk) << 1)
#घोषणा     CFG_INV_PCLK_MASK			0x00000002
#घोषणा     CFG_DUMB_ENA(dumb)			(dumb)
#घोषणा     CFG_DUMB_ENA_MASK			0x00000001

/* LCD I/O Pads Control Register */
#घोषणा SPU_IOPAD_CONTROL			0x01BC
#घोषणा     CFG_GRA_VM_ENA(vm)			((vm) << 15)        /* gfx */
#घोषणा     CFG_GRA_VM_ENA_MASK			0x00008000
#घोषणा     CFG_DMA_VM_ENA(vm)			((vm) << 13)	/* video */
#घोषणा     CFG_DMA_VM_ENA_MASK			0x00002000
#घोषणा     CFG_CMD_VM_ENA(vm)			((vm) << 13)
#घोषणा     CFG_CMD_VM_ENA_MASK			0x00000800
#घोषणा     CFG_CSC(csc)			((csc) << 8)	/* csc */
#घोषणा     CFG_CSC_MASK			0x00000300
#घोषणा     CFG_AXICTRL(axi)			((axi) << 4)
#घोषणा     CFG_AXICTRL_MASK			0x000000F0
#घोषणा     CFG_IOPADMODE(iopad)		(iopad)
#घोषणा     CFG_IOPADMODE_MASK			0x0000000F

/* LCD Interrupt Control Register */
#घोषणा SPU_IRQ_ENA				0x01C0
#घोषणा     DMA_FRAME_IRQ0_ENA(irq)		((irq) << 31)
#घोषणा     DMA_FRAME_IRQ0_ENA_MASK		0x80000000
#घोषणा     DMA_FRAME_IRQ1_ENA(irq)		((irq) << 30)
#घोषणा     DMA_FRAME_IRQ1_ENA_MASK		0x40000000
#घोषणा     DMA_FF_UNDERFLOW_ENA(ff)		((ff) << 29)
#घोषणा     DMA_FF_UNDERFLOW_ENA_MASK		0x20000000
#घोषणा     GRA_FRAME_IRQ0_ENA(irq)		((irq) << 27)
#घोषणा     GRA_FRAME_IRQ0_ENA_MASK		0x08000000
#घोषणा     GRA_FRAME_IRQ1_ENA(irq)		((irq) << 26)
#घोषणा     GRA_FRAME_IRQ1_ENA_MASK		0x04000000
#घोषणा     GRA_FF_UNDERFLOW_ENA(ff)		((ff) << 25)
#घोषणा     GRA_FF_UNDERFLOW_ENA_MASK		0x02000000
#घोषणा     VSYNC_IRQ_ENA(vsync_irq)		((vsync_irq) << 23)
#घोषणा     VSYNC_IRQ_ENA_MASK			0x00800000
#घोषणा     DUMB_FRAMEDONE_ENA(fकरोne)		((fकरोne) << 22)
#घोषणा     DUMB_FRAMEDONE_ENA_MASK		0x00400000
#घोषणा     TWC_FRAMEDONE_ENA(fकरोne)		((fकरोne) << 21)
#घोषणा     TWC_FRAMEDONE_ENA_MASK		0x00200000
#घोषणा     HWC_FRAMEDONE_ENA(fकरोne)		((fकरोne) << 20)
#घोषणा     HWC_FRAMEDONE_ENA_MASK		0x00100000
#घोषणा     SLV_IRQ_ENA(irq)			((irq) << 19)
#घोषणा     SLV_IRQ_ENA_MASK			0x00080000
#घोषणा     SPI_IRQ_ENA(irq)			((irq) << 18)
#घोषणा     SPI_IRQ_ENA_MASK			0x00040000
#घोषणा     PWRDN_IRQ_ENA(irq)			((irq) << 17)
#घोषणा     PWRDN_IRQ_ENA_MASK			0x00020000
#घोषणा     ERR_IRQ_ENA(irq)			((irq) << 16)
#घोषणा     ERR_IRQ_ENA_MASK			0x00010000
#घोषणा     CLEAN_SPU_IRQ_ISR(irq)		(irq)
#घोषणा     CLEAN_SPU_IRQ_ISR_MASK		0x0000FFFF

/* LCD Interrupt Status Register */
#घोषणा SPU_IRQ_ISR				0x01C4
#घोषणा     DMA_FRAME_IRQ0(irq)			((irq) << 31)
#घोषणा     DMA_FRAME_IRQ0_MASK			0x80000000
#घोषणा     DMA_FRAME_IRQ1(irq)			((irq) << 30)
#घोषणा     DMA_FRAME_IRQ1_MASK			0x40000000
#घोषणा     DMA_FF_UNDERFLOW(ff)		((ff) << 29)
#घोषणा     DMA_FF_UNDERFLOW_MASK		0x20000000
#घोषणा     GRA_FRAME_IRQ0(irq)			((irq) << 27)
#घोषणा     GRA_FRAME_IRQ0_MASK			0x08000000
#घोषणा     GRA_FRAME_IRQ1(irq)			((irq) << 26)
#घोषणा     GRA_FRAME_IRQ1_MASK			0x04000000
#घोषणा     GRA_FF_UNDERFLOW(ff)		((ff) << 25)
#घोषणा     GRA_FF_UNDERFLOW_MASK		0x02000000
#घोषणा     VSYNC_IRQ(vsync_irq)		((vsync_irq) << 23)
#घोषणा     VSYNC_IRQ_MASK			0x00800000
#घोषणा     DUMB_FRAMEDONE(fकरोne)		((fकरोne) << 22)
#घोषणा     DUMB_FRAMEDONE_MASK			0x00400000
#घोषणा     TWC_FRAMEDONE(fकरोne)		((fकरोne) << 21)
#घोषणा     TWC_FRAMEDONE_MASK			0x00200000
#घोषणा     HWC_FRAMEDONE(fकरोne)		((fकरोne) << 20)
#घोषणा     HWC_FRAMEDONE_MASK			0x00100000
#घोषणा     SLV_IRQ(irq)			((irq) << 19)
#घोषणा     SLV_IRQ_MASK			0x00080000
#घोषणा     SPI_IRQ(irq)			((irq) << 18)
#घोषणा     SPI_IRQ_MASK			0x00040000
#घोषणा     PWRDN_IRQ(irq)			((irq) << 17)
#घोषणा     PWRDN_IRQ_MASK			0x00020000
#घोषणा     ERR_IRQ(irq)			((irq) << 16)
#घोषणा     ERR_IRQ_MASK			0x00010000
/* पढ़ो-only */
#घोषणा     DMA_FRAME_IRQ0_LEVEL_MASK		0x00008000
#घोषणा     DMA_FRAME_IRQ1_LEVEL_MASK		0x00004000
#घोषणा     DMA_FRAME_CNT_ISR_MASK		0x00003000
#घोषणा     GRA_FRAME_IRQ0_LEVEL_MASK		0x00000800
#घोषणा     GRA_FRAME_IRQ1_LEVEL_MASK		0x00000400
#घोषणा     GRA_FRAME_CNT_ISR_MASK		0x00000300
#घोषणा     VSYNC_IRQ_LEVEL_MASK		0x00000080
#घोषणा     DUMB_FRAMEDONE_LEVEL_MASK		0x00000040
#घोषणा     TWC_FRAMEDONE_LEVEL_MASK		0x00000020
#घोषणा     HWC_FRAMEDONE_LEVEL_MASK		0x00000010
#घोषणा     SLV_FF_EMPTY_MASK			0x00000008
#घोषणा     DMA_FF_ALLEMPTY_MASK		0x00000004
#घोषणा     GRA_FF_ALLEMPTY_MASK		0x00000002
#घोषणा     PWRDN_IRQ_LEVEL_MASK		0x00000001


/*
 * defined Video Memory Color क्रमmat क्रम DMA control 0 रेजिस्टर
 * DMA0 bit[23:20]
 */
#घोषणा VMODE_RGB565		0x0
#घोषणा VMODE_RGB1555		0x1
#घोषणा VMODE_RGB888PACKED	0x2
#घोषणा VMODE_RGB888UNPACKED	0x3
#घोषणा VMODE_RGBA888		0x4
#घोषणा VMODE_YUV422PACKED	0x5
#घोषणा VMODE_YUV422PLANAR	0x6
#घोषणा VMODE_YUV420PLANAR	0x7
#घोषणा VMODE_SMPNCMD		0x8
#घोषणा VMODE_PALETTE4BIT	0x9
#घोषणा VMODE_PALETTE8BIT	0xa
#घोषणा VMODE_RESERVED		0xb

/*
 * defined Graphic Memory Color क्रमmat क्रम DMA control 0 रेजिस्टर
 * DMA0 bit[19:16]
 */
#घोषणा GMODE_RGB565		0x0
#घोषणा GMODE_RGB1555		0x1
#घोषणा GMODE_RGB888PACKED	0x2
#घोषणा GMODE_RGB888UNPACKED	0x3
#घोषणा GMODE_RGBA888		0x4
#घोषणा GMODE_YUV422PACKED	0x5
#घोषणा GMODE_YUV422PLANAR	0x6
#घोषणा GMODE_YUV420PLANAR	0x7
#घोषणा GMODE_SMPNCMD		0x8
#घोषणा GMODE_PALETTE4BIT	0x9
#घोषणा GMODE_PALETTE8BIT	0xa
#घोषणा GMODE_RESERVED		0xb

/*
 * define क्रम DMA control 1 रेजिस्टर
 */
#घोषणा DMA1_FRAME_TRIG		31 /* bit location */
#घोषणा DMA1_VSYNC_MODE		28
#घोषणा DMA1_VSYNC_INV		27
#घोषणा DMA1_CKEY		24
#घोषणा DMA1_CARRY		23
#घोषणा DMA1_LNBUF_ENA		22
#घोषणा DMA1_GATED_ENA		21
#घोषणा DMA1_PWRDN_ENA		20
#घोषणा DMA1_DSCALE		18
#घोषणा DMA1_ALPHA_MODE		16
#घोषणा DMA1_ALPHA		08
#घोषणा DMA1_PXLCMD		00

/*
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

#पूर्ण_अगर /* __PXA168FB_H__ */
