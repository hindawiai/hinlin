<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/video/samsung_fimd.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platक्रमm - new-style fimd and framebuffer रेजिस्टर definitions
 *
 * This is the रेजिस्टर set क्रम the fimd and new style framebuffer पूर्णांकerface
 * found from the S3C2443 onwards पूर्णांकo the S3C2416, S3C2450, the
 * S3C64XX series such as the S3C6400 and S3C6410, and Exynos series.
*/

/* VIDCON0 */

#घोषणा VIDCON0					0x00
#घोषणा VIDCON0_DSI_EN				(1 << 30)
#घोषणा VIDCON0_INTERLACE			(1 << 29)
#घोषणा VIDCON0_VIDOUT_MASK			(0x7 << 26)
#घोषणा VIDCON0_VIDOUT_SHIFT			26
#घोषणा VIDCON0_VIDOUT_RGB			(0x0 << 26)
#घोषणा VIDCON0_VIDOUT_TV			(0x1 << 26)
#घोषणा VIDCON0_VIDOUT_I80_LDI0			(0x2 << 26)
#घोषणा VIDCON0_VIDOUT_I80_LDI1			(0x3 << 26)
#घोषणा VIDCON0_VIDOUT_WB_RGB			(0x4 << 26)
#घोषणा VIDCON0_VIDOUT_WB_I80_LDI0		(0x6 << 26)
#घोषणा VIDCON0_VIDOUT_WB_I80_LDI1		(0x7 << 26)

#घोषणा VIDCON0_L1_DATA_MASK			(0x7 << 23)
#घोषणा VIDCON0_L1_DATA_SHIFT			23
#घोषणा VIDCON0_L1_DATA_16BPP			(0x0 << 23)
#घोषणा VIDCON0_L1_DATA_18BPP16			(0x1 << 23)
#घोषणा VIDCON0_L1_DATA_18BPP9			(0x2 << 23)
#घोषणा VIDCON0_L1_DATA_24BPP			(0x3 << 23)
#घोषणा VIDCON0_L1_DATA_18BPP			(0x4 << 23)
#घोषणा VIDCON0_L1_DATA_16BPP8			(0x5 << 23)

#घोषणा VIDCON0_L0_DATA_MASK			(0x7 << 20)
#घोषणा VIDCON0_L0_DATA_SHIFT			20
#घोषणा VIDCON0_L0_DATA_16BPP			(0x0 << 20)
#घोषणा VIDCON0_L0_DATA_18BPP16			(0x1 << 20)
#घोषणा VIDCON0_L0_DATA_18BPP9			(0x2 << 20)
#घोषणा VIDCON0_L0_DATA_24BPP			(0x3 << 20)
#घोषणा VIDCON0_L0_DATA_18BPP			(0x4 << 20)
#घोषणा VIDCON0_L0_DATA_16BPP8			(0x5 << 20)

#घोषणा VIDCON0_PNRMODE_MASK			(0x3 << 17)
#घोषणा VIDCON0_PNRMODE_SHIFT			17
#घोषणा VIDCON0_PNRMODE_RGB			(0x0 << 17)
#घोषणा VIDCON0_PNRMODE_BGR			(0x1 << 17)
#घोषणा VIDCON0_PNRMODE_SERIAL_RGB		(0x2 << 17)
#घोषणा VIDCON0_PNRMODE_SERIAL_BGR		(0x3 << 17)

#घोषणा VIDCON0_CLKVALUP			(1 << 16)
#घोषणा VIDCON0_CLKVAL_F_MASK			(0xff << 6)
#घोषणा VIDCON0_CLKVAL_F_SHIFT			6
#घोषणा VIDCON0_CLKVAL_F_LIMIT			0xff
#घोषणा VIDCON0_CLKVAL_F(_x)			((_x) << 6)
#घोषणा VIDCON0_VLCKFREE			(1 << 5)
#घोषणा VIDCON0_CLKसूची				(1 << 4)

#घोषणा VIDCON0_CLKSEL_MASK			(0x3 << 2)
#घोषणा VIDCON0_CLKSEL_SHIFT			2
#घोषणा VIDCON0_CLKSEL_HCLK			(0x0 << 2)
#घोषणा VIDCON0_CLKSEL_LCD			(0x1 << 2)
#घोषणा VIDCON0_CLKSEL_27M			(0x3 << 2)

#घोषणा VIDCON0_ENVID				(1 << 1)
#घोषणा VIDCON0_ENVID_F				(1 << 0)

#घोषणा VIDCON1					0x04
#घोषणा VIDCON1_LINECNT_MASK			(0x7ff << 16)
#घोषणा VIDCON1_LINECNT_SHIFT			16
#घोषणा VIDCON1_LINECNT_GET(_v)			(((_v) >> 16) & 0x7ff)
#घोषणा VIDCON1_FSTATUS_EVEN			(1 << 15)
#घोषणा VIDCON1_VSTATUS_MASK			(0x3 << 13)
#घोषणा VIDCON1_VSTATUS_SHIFT			13
#घोषणा VIDCON1_VSTATUS_VSYNC			(0x0 << 13)
#घोषणा VIDCON1_VSTATUS_BACKPORCH		(0x1 << 13)
#घोषणा VIDCON1_VSTATUS_ACTIVE			(0x2 << 13)
#घोषणा VIDCON1_VSTATUS_FRONTPORCH		(0x3 << 13)
#घोषणा VIDCON1_VCLK_MASK			(0x3 << 9)
#घोषणा VIDCON1_VCLK_HOLD			(0x0 << 9)
#घोषणा VIDCON1_VCLK_RUN			(0x1 << 9)

#घोषणा VIDCON1_INV_VCLK			(1 << 7)
#घोषणा VIDCON1_INV_HSYNC			(1 << 6)
#घोषणा VIDCON1_INV_VSYNC			(1 << 5)
#घोषणा VIDCON1_INV_VDEN			(1 << 4)

/* VIDCON2 */

#घोषणा VIDCON2					0x08
#घोषणा VIDCON2_EN601				(1 << 23)
#घोषणा VIDCON2_TVFMTSEL_SW			(1 << 14)

#घोषणा VIDCON2_TVFMTSEL1_MASK			(0x3 << 12)
#घोषणा VIDCON2_TVFMTSEL1_SHIFT			12
#घोषणा VIDCON2_TVFMTSEL1_RGB			(0x0 << 12)
#घोषणा VIDCON2_TVFMTSEL1_YUV422		(0x1 << 12)
#घोषणा VIDCON2_TVFMTSEL1_YUV444		(0x2 << 12)

#घोषणा VIDCON2_ORGYCbCr			(1 << 8)
#घोषणा VIDCON2_YUVORDCrCb			(1 << 7)

/* PRTCON (S3C6410)
 * Might not be present in the S3C6410 करोcumentation,
 * but tests prove it's there almost for sure; shouldn't hurt in any हाल.
 */
#घोषणा PRTCON					0x0c
#घोषणा PRTCON_PROTECT				(1 << 11)

/* VIDTCON0 */

#घोषणा VIDTCON0				0x10
#घोषणा VIDTCON0_VBPDE_MASK			(0xff << 24)
#घोषणा VIDTCON0_VBPDE_SHIFT			24
#घोषणा VIDTCON0_VBPDE_LIMIT			0xff
#घोषणा VIDTCON0_VBPDE(_x)			((_x) << 24)

#घोषणा VIDTCON0_VBPD_MASK			(0xff << 16)
#घोषणा VIDTCON0_VBPD_SHIFT			16
#घोषणा VIDTCON0_VBPD_LIMIT			0xff
#घोषणा VIDTCON0_VBPD(_x)			((_x) << 16)

#घोषणा VIDTCON0_VFPD_MASK			(0xff << 8)
#घोषणा VIDTCON0_VFPD_SHIFT			8
#घोषणा VIDTCON0_VFPD_LIMIT			0xff
#घोषणा VIDTCON0_VFPD(_x)			((_x) << 8)

#घोषणा VIDTCON0_VSPW_MASK			(0xff << 0)
#घोषणा VIDTCON0_VSPW_SHIFT			0
#घोषणा VIDTCON0_VSPW_LIMIT			0xff
#घोषणा VIDTCON0_VSPW(_x)			((_x) << 0)

/* VIDTCON1 */

#घोषणा VIDTCON1				0x14
#घोषणा VIDTCON1_VFPDE_MASK			(0xff << 24)
#घोषणा VIDTCON1_VFPDE_SHIFT			24
#घोषणा VIDTCON1_VFPDE_LIMIT			0xff
#घोषणा VIDTCON1_VFPDE(_x)			((_x) << 24)

#घोषणा VIDTCON1_HBPD_MASK			(0xff << 16)
#घोषणा VIDTCON1_HBPD_SHIFT			16
#घोषणा VIDTCON1_HBPD_LIMIT			0xff
#घोषणा VIDTCON1_HBPD(_x)			((_x) << 16)

#घोषणा VIDTCON1_HFPD_MASK			(0xff << 8)
#घोषणा VIDTCON1_HFPD_SHIFT			8
#घोषणा VIDTCON1_HFPD_LIMIT			0xff
#घोषणा VIDTCON1_HFPD(_x)			((_x) << 8)

#घोषणा VIDTCON1_HSPW_MASK			(0xff << 0)
#घोषणा VIDTCON1_HSPW_SHIFT			0
#घोषणा VIDTCON1_HSPW_LIMIT			0xff
#घोषणा VIDTCON1_HSPW(_x)			((_x) << 0)

#घोषणा VIDTCON2				0x18
#घोषणा VIDTCON2_LINEVAL_E(_x)			((((_x) & 0x800) >> 11) << 23)
#घोषणा VIDTCON2_LINEVAL_MASK			(0x7ff << 11)
#घोषणा VIDTCON2_LINEVAL_SHIFT			11
#घोषणा VIDTCON2_LINEVAL_LIMIT			0x7ff
#घोषणा VIDTCON2_LINEVAL(_x)			(((_x) & 0x7ff) << 11)

#घोषणा VIDTCON2_HOZVAL_E(_x)			((((_x) & 0x800) >> 11) << 22)
#घोषणा VIDTCON2_HOZVAL_MASK			(0x7ff << 0)
#घोषणा VIDTCON2_HOZVAL_SHIFT			0
#घोषणा VIDTCON2_HOZVAL_LIMIT			0x7ff
#घोषणा VIDTCON2_HOZVAL(_x)			(((_x) & 0x7ff) << 0)

/* WINCONx */

#घोषणा WINCON(_win)				(0x20 + ((_win) * 4))
#घोषणा WINCONx_CSCCON_EQ601			(0x0 << 28)
#घोषणा WINCONx_CSCCON_EQ709			(0x1 << 28)
#घोषणा WINCONx_CSCWIDTH_MASK			(0x3 << 26)
#घोषणा WINCONx_CSCWIDTH_SHIFT			26
#घोषणा WINCONx_CSCWIDTH_WIDE			(0x0 << 26)
#घोषणा WINCONx_CSCWIDTH_NARROW			(0x3 << 26)
#घोषणा WINCONx_ENLOCAL				(1 << 22)
#घोषणा WINCONx_BUFSTATUS			(1 << 21)
#घोषणा WINCONx_BUFSEL				(1 << 20)
#घोषणा WINCONx_BUFAUTOEN			(1 << 19)
#घोषणा WINCONx_BITSWP				(1 << 18)
#घोषणा WINCONx_BYTSWP				(1 << 17)
#घोषणा WINCONx_HAWSWP				(1 << 16)
#घोषणा WINCONx_WSWP				(1 << 15)
#घोषणा WINCONx_YCbCr				(1 << 13)
#घोषणा WINCONx_BURSTLEN_MASK			(0x3 << 9)
#घोषणा WINCONx_BURSTLEN_SHIFT			9
#घोषणा WINCONx_BURSTLEN_16WORD			(0x0 << 9)
#घोषणा WINCONx_BURSTLEN_8WORD			(0x1 << 9)
#घोषणा WINCONx_BURSTLEN_4WORD			(0x2 << 9)
#घोषणा WINCONx_ENWIN				(1 << 0)
#घोषणा WINCONx_BLEND_MODE_MASK			(0xc2)

#घोषणा WINCON0_BPPMODE_MASK			(0xf << 2)
#घोषणा WINCON0_BPPMODE_SHIFT			2
#घोषणा WINCON0_BPPMODE_1BPP			(0x0 << 2)
#घोषणा WINCON0_BPPMODE_2BPP			(0x1 << 2)
#घोषणा WINCON0_BPPMODE_4BPP			(0x2 << 2)
#घोषणा WINCON0_BPPMODE_8BPP_PALETTE		(0x3 << 2)
#घोषणा WINCON0_BPPMODE_16BPP_565		(0x5 << 2)
#घोषणा WINCON0_BPPMODE_16BPP_1555		(0x7 << 2)
#घोषणा WINCON0_BPPMODE_18BPP_666		(0x8 << 2)
#घोषणा WINCON0_BPPMODE_24BPP_888		(0xb << 2)

#घोषणा WINCON1_LOCALSEL_CAMIF			(1 << 23)
#घोषणा WINCON1_ALPHA_MUL			(1 << 7)
#घोषणा WINCON1_BLD_PIX				(1 << 6)
#घोषणा WINCON1_BPPMODE_MASK			(0xf << 2)
#घोषणा WINCON1_BPPMODE_SHIFT			2
#घोषणा WINCON1_BPPMODE_1BPP			(0x0 << 2)
#घोषणा WINCON1_BPPMODE_2BPP			(0x1 << 2)
#घोषणा WINCON1_BPPMODE_4BPP			(0x2 << 2)
#घोषणा WINCON1_BPPMODE_8BPP_PALETTE		(0x3 << 2)
#घोषणा WINCON1_BPPMODE_8BPP_1232		(0x4 << 2)
#घोषणा WINCON1_BPPMODE_16BPP_565		(0x5 << 2)
#घोषणा WINCON1_BPPMODE_16BPP_A1555		(0x6 << 2)
#घोषणा WINCON1_BPPMODE_16BPP_I1555		(0x7 << 2)
#घोषणा WINCON1_BPPMODE_18BPP_666		(0x8 << 2)
#घोषणा WINCON1_BPPMODE_18BPP_A1665		(0x9 << 2)
#घोषणा WINCON1_BPPMODE_19BPP_A1666		(0xa << 2)
#घोषणा WINCON1_BPPMODE_24BPP_888		(0xb << 2)
#घोषणा WINCON1_BPPMODE_24BPP_A1887		(0xc << 2)
#घोषणा WINCON1_BPPMODE_25BPP_A1888		(0xd << 2)
#घोषणा WINCON1_BPPMODE_28BPP_A4888		(0xd << 2)
#घोषणा WINCON1_ALPHA_SEL			(1 << 1)

/* S5PV210 */
#घोषणा SHADOWCON				0x34
#घोषणा SHADOWCON_WINx_PROTECT(_win)		(1 << (10 + (_win)))
/* DMA channels (all winकरोws) */
#घोषणा SHADOWCON_CHx_ENABLE(_win)		(1 << (_win))
/* Local input channels (winकरोws 0-2) */
#घोषणा SHADOWCON_CHx_LOCAL_ENABLE(_win)	(1 << (5 + (_win)))

/* VIDOSDx */

#घोषणा VIDOSD_BASE				0x40
#घोषणा VIDOSDxA_TOPLEFT_X_E(_x)		((((_x) & 0x800) >> 11) << 23)
#घोषणा VIDOSDxA_TOPLEFT_X_MASK			(0x7ff << 11)
#घोषणा VIDOSDxA_TOPLEFT_X_SHIFT		11
#घोषणा VIDOSDxA_TOPLEFT_X_LIMIT		0x7ff
#घोषणा VIDOSDxA_TOPLEFT_X(_x)			(((_x) & 0x7ff) << 11)

#घोषणा VIDOSDxA_TOPLEFT_Y_E(_x)		((((_x) & 0x800) >> 11) << 22)
#घोषणा VIDOSDxA_TOPLEFT_Y_MASK			(0x7ff << 0)
#घोषणा VIDOSDxA_TOPLEFT_Y_SHIFT		0
#घोषणा VIDOSDxA_TOPLEFT_Y_LIMIT		0x7ff
#घोषणा VIDOSDxA_TOPLEFT_Y(_x)			(((_x) & 0x7ff) << 0)

#घोषणा VIDOSDxB_BOTRIGHT_X_E(_x)		((((_x) & 0x800) >> 11) << 23)
#घोषणा VIDOSDxB_BOTRIGHT_X_MASK		(0x7ff << 11)
#घोषणा VIDOSDxB_BOTRIGHT_X_SHIFT		11
#घोषणा VIDOSDxB_BOTRIGHT_X_LIMIT		0x7ff
#घोषणा VIDOSDxB_BOTRIGHT_X(_x)			(((_x) & 0x7ff) << 11)

#घोषणा VIDOSDxB_BOTRIGHT_Y_E(_x)		((((_x) & 0x800) >> 11) << 22)
#घोषणा VIDOSDxB_BOTRIGHT_Y_MASK		(0x7ff << 0)
#घोषणा VIDOSDxB_BOTRIGHT_Y_SHIFT		0
#घोषणा VIDOSDxB_BOTRIGHT_Y_LIMIT		0x7ff
#घोषणा VIDOSDxB_BOTRIGHT_Y(_x)			(((_x) & 0x7ff) << 0)

/* For VIDOSD[1..4]C */
#घोषणा VIDISD14C_ALPHA0_R(_x)			((_x) << 20)
#घोषणा VIDISD14C_ALPHA0_G_MASK			(0xf << 16)
#घोषणा VIDISD14C_ALPHA0_G_SHIFT		16
#घोषणा VIDISD14C_ALPHA0_G_LIMIT		0xf
#घोषणा VIDISD14C_ALPHA0_G(_x)			((_x) << 16)
#घोषणा VIDISD14C_ALPHA0_B_MASK			(0xf << 12)
#घोषणा VIDISD14C_ALPHA0_B_SHIFT		12
#घोषणा VIDISD14C_ALPHA0_B_LIMIT		0xf
#घोषणा VIDISD14C_ALPHA0_B(_x)			((_x) << 12)
#घोषणा VIDISD14C_ALPHA1_R_MASK			(0xf << 8)
#घोषणा VIDISD14C_ALPHA1_R_SHIFT		8
#घोषणा VIDISD14C_ALPHA1_R_LIMIT		0xf
#घोषणा VIDISD14C_ALPHA1_R(_x)			((_x) << 8)
#घोषणा VIDISD14C_ALPHA1_G_MASK			(0xf << 4)
#घोषणा VIDISD14C_ALPHA1_G_SHIFT		4
#घोषणा VIDISD14C_ALPHA1_G_LIMIT		0xf
#घोषणा VIDISD14C_ALPHA1_G(_x)			((_x) << 4)
#घोषणा VIDISD14C_ALPHA1_B_MASK			(0xf << 0)
#घोषणा VIDISD14C_ALPHA1_B_SHIFT		0
#घोषणा VIDISD14C_ALPHA1_B_LIMIT		0xf
#घोषणा VIDISD14C_ALPHA1_B(_x)			((_x) << 0)

#घोषणा VIDW_ALPHA				0x021c
#घोषणा VIDW_ALPHA_R(_x)			((_x) << 16)
#घोषणा VIDW_ALPHA_G(_x)			((_x) << 8)
#घोषणा VIDW_ALPHA_B(_x)			((_x) << 0)

/* Video buffer addresses */
#घोषणा VIDW_BUF_START(_buff)			(0xA0 + ((_buff) * 8))
#घोषणा VIDW_BUF_START_S(_buff)			(0x40A0 + ((_buff) * 8))
#घोषणा VIDW_BUF_START1(_buff)			(0xA4 + ((_buff) * 8))
#घोषणा VIDW_BUF_END(_buff)			(0xD0 + ((_buff) * 8))
#घोषणा VIDW_BUF_END1(_buff)			(0xD4 + ((_buff) * 8))
#घोषणा VIDW_BUF_SIZE(_buff)			(0x100 + ((_buff) * 4))

#घोषणा VIDW_BUF_SIZE_OFFSET_E(_x)		((((_x) & 0x2000) >> 13) << 27)
#घोषणा VIDW_BUF_SIZE_OFFSET_MASK		(0x1fff << 13)
#घोषणा VIDW_BUF_SIZE_OFFSET_SHIFT		13
#घोषणा VIDW_BUF_SIZE_OFFSET_LIMIT		0x1fff
#घोषणा VIDW_BUF_SIZE_OFFSET(_x)		(((_x) & 0x1fff) << 13)

#घोषणा VIDW_BUF_SIZE_PAGEWIDTH_E(_x)		((((_x) & 0x2000) >> 13) << 26)
#घोषणा VIDW_BUF_SIZE_PAGEWIDTH_MASK		(0x1fff << 0)
#घोषणा VIDW_BUF_SIZE_PAGEWIDTH_SHIFT		0
#घोषणा VIDW_BUF_SIZE_PAGEWIDTH_LIMIT		0x1fff
#घोषणा VIDW_BUF_SIZE_PAGEWIDTH(_x)		(((_x) & 0x1fff) << 0)

/* Interrupt controls and status */

#घोषणा VIDINTCON0				0x130
#घोषणा VIDINTCON0_FIFOINTERVAL_MASK		(0x3f << 20)
#घोषणा VIDINTCON0_FIFOINTERVAL_SHIFT		20
#घोषणा VIDINTCON0_FIFOINTERVAL_LIMIT		0x3f
#घोषणा VIDINTCON0_FIFOINTERVAL(_x)		((_x) << 20)

#घोषणा VIDINTCON0_INT_SYSMAINCON		(1 << 19)
#घोषणा VIDINTCON0_INT_SYSSUBCON		(1 << 18)
#घोषणा VIDINTCON0_INT_I80IFDONE		(1 << 17)

#घोषणा VIDINTCON0_FRAMESEL0_MASK		(0x3 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_SHIFT		15
#घोषणा VIDINTCON0_FRAMESEL0_BACKPORCH		(0x0 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_VSYNC		(0x1 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_ACTIVE		(0x2 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_FRONTPORCH		(0x3 << 15)

#घोषणा VIDINTCON0_FRAMESEL1			(1 << 13)
#घोषणा VIDINTCON0_FRAMESEL1_MASK		(0x3 << 13)
#घोषणा VIDINTCON0_FRAMESEL1_NONE		(0x0 << 13)
#घोषणा VIDINTCON0_FRAMESEL1_BACKPORCH		(0x1 << 13)
#घोषणा VIDINTCON0_FRAMESEL1_VSYNC		(0x2 << 13)
#घोषणा VIDINTCON0_FRAMESEL1_FRONTPORCH		(0x3 << 13)

#घोषणा VIDINTCON0_INT_FRAME			(1 << 12)
#घोषणा VIDINTCON0_FIFIOSEL_MASK		(0x7f << 5)
#घोषणा VIDINTCON0_FIFIOSEL_SHIFT		5
#घोषणा VIDINTCON0_FIFIOSEL_WINDOW0		(0x1 << 5)
#घोषणा VIDINTCON0_FIFIOSEL_WINDOW1		(0x2 << 5)
#घोषणा VIDINTCON0_FIFIOSEL_WINDOW2		(0x10 << 5)
#घोषणा VIDINTCON0_FIFIOSEL_WINDOW3		(0x20 << 5)
#घोषणा VIDINTCON0_FIFIOSEL_WINDOW4		(0x40 << 5)

#घोषणा VIDINTCON0_FIFOLEVEL_MASK		(0x7 << 2)
#घोषणा VIDINTCON0_FIFOLEVEL_SHIFT		2
#घोषणा VIDINTCON0_FIFOLEVEL_TO25PC		(0x0 << 2)
#घोषणा VIDINTCON0_FIFOLEVEL_TO50PC		(0x1 << 2)
#घोषणा VIDINTCON0_FIFOLEVEL_TO75PC		(0x2 << 2)
#घोषणा VIDINTCON0_FIFOLEVEL_EMPTY		(0x3 << 2)
#घोषणा VIDINTCON0_FIFOLEVEL_FULL		(0x4 << 2)

#घोषणा VIDINTCON0_INT_FIFO_MASK		(0x3 << 0)
#घोषणा VIDINTCON0_INT_FIFO_SHIFT		0
#घोषणा VIDINTCON0_INT_ENABLE			(1 << 0)

#घोषणा VIDINTCON1				0x134
#घोषणा VIDINTCON1_INT_I80			(1 << 2)
#घोषणा VIDINTCON1_INT_FRAME			(1 << 1)
#घोषणा VIDINTCON1_INT_FIFO			(1 << 0)

/* Winकरोw colour-key control रेजिस्टरs */
#घोषणा WKEYCON					0x140

#घोषणा WKEYCON0				0x00
#घोषणा WKEYCON1				0x04

#घोषणा WxKEYCON0_KEYBL_EN			(1 << 26)
#घोषणा WxKEYCON0_KEYEN_F			(1 << 25)
#घोषणा WxKEYCON0_सूचीCON			(1 << 24)
#घोषणा WxKEYCON0_COMPKEY_MASK			(0xffffff << 0)
#घोषणा WxKEYCON0_COMPKEY_SHIFT			0
#घोषणा WxKEYCON0_COMPKEY_LIMIT			0xffffff
#घोषणा WxKEYCON0_COMPKEY(_x)			((_x) << 0)
#घोषणा WxKEYCON1_COLVAL_MASK			(0xffffff << 0)
#घोषणा WxKEYCON1_COLVAL_SHIFT			0
#घोषणा WxKEYCON1_COLVAL_LIMIT			0xffffff
#घोषणा WxKEYCON1_COLVAL(_x)			((_x) << 0)

/* Dithering control */
#घोषणा DITHMODE				0x170
#घोषणा DITHMODE_R_POS_MASK			(0x3 << 5)
#घोषणा DITHMODE_R_POS_SHIFT			5
#घोषणा DITHMODE_R_POS_8BIT			(0x0 << 5)
#घोषणा DITHMODE_R_POS_6BIT			(0x1 << 5)
#घोषणा DITHMODE_R_POS_5BIT			(0x2 << 5)
#घोषणा DITHMODE_G_POS_MASK			(0x3 << 3)
#घोषणा DITHMODE_G_POS_SHIFT			3
#घोषणा DITHMODE_G_POS_8BIT			(0x0 << 3)
#घोषणा DITHMODE_G_POS_6BIT			(0x1 << 3)
#घोषणा DITHMODE_G_POS_5BIT			(0x2 << 3)
#घोषणा DITHMODE_B_POS_MASK			(0x3 << 1)
#घोषणा DITHMODE_B_POS_SHIFT			1
#घोषणा DITHMODE_B_POS_8BIT			(0x0 << 1)
#घोषणा DITHMODE_B_POS_6BIT			(0x1 << 1)
#घोषणा DITHMODE_B_POS_5BIT			(0x2 << 1)
#घोषणा DITHMODE_DITH_EN			(1 << 0)

/* Winकरोw blanking (MAP) */
#घोषणा WINxMAP(_win)				(0x180 + ((_win) * 4))
#घोषणा WINxMAP_MAP				(1 << 24)
#घोषणा WINxMAP_MAP_COLOUR_MASK			(0xffffff << 0)
#घोषणा WINxMAP_MAP_COLOUR_SHIFT		0
#घोषणा WINxMAP_MAP_COLOUR_LIMIT		0xffffff
#घोषणा WINxMAP_MAP_COLOUR(_x)			((_x) << 0)

/* Winodw palette control */
#घोषणा WPALCON					0x1A0
#घोषणा WPALCON_PAL_UPDATE			(1 << 9)
#घोषणा WPALCON_W4PAL_16BPP_A555		(1 << 8)
#घोषणा WPALCON_W3PAL_16BPP_A555		(1 << 7)
#घोषणा WPALCON_W2PAL_16BPP_A555		(1 << 6)
#घोषणा WPALCON_W1PAL_MASK			(0x7 << 3)
#घोषणा WPALCON_W1PAL_SHIFT			3
#घोषणा WPALCON_W1PAL_25BPP_A888		(0x0 << 3)
#घोषणा WPALCON_W1PAL_24BPP			(0x1 << 3)
#घोषणा WPALCON_W1PAL_19BPP_A666		(0x2 << 3)
#घोषणा WPALCON_W1PAL_18BPP_A665		(0x3 << 3)
#घोषणा WPALCON_W1PAL_18BPP			(0x4 << 3)
#घोषणा WPALCON_W1PAL_16BPP_A555		(0x5 << 3)
#घोषणा WPALCON_W1PAL_16BPP_565			(0x6 << 3)
#घोषणा WPALCON_W0PAL_MASK			(0x7 << 0)
#घोषणा WPALCON_W0PAL_SHIFT			0
#घोषणा WPALCON_W0PAL_25BPP_A888		(0x0 << 0)
#घोषणा WPALCON_W0PAL_24BPP			(0x1 << 0)
#घोषणा WPALCON_W0PAL_19BPP_A666		(0x2 << 0)
#घोषणा WPALCON_W0PAL_18BPP_A665		(0x3 << 0)
#घोषणा WPALCON_W0PAL_18BPP			(0x4 << 0)
#घोषणा WPALCON_W0PAL_16BPP_A555		(0x5 << 0)
#घोषणा WPALCON_W0PAL_16BPP_565			(0x6 << 0)

/* Blending equation control */
#घोषणा BLENDEQx(_win)				(0x244 + ((_win - 1) * 4))
#घोषणा BLENDEQ_ZERO				0x0
#घोषणा BLENDEQ_ONE				0x1
#घोषणा BLENDEQ_ALPHA_A				0x2
#घोषणा BLENDEQ_ONE_MINUS_ALPHA_A		0x3
#घोषणा BLENDEQ_ALPHA0				0x6
#घोषणा BLENDEQ_B_FUNC_F(_x)			(_x << 6)
#घोषणा BLENDEQ_A_FUNC_F(_x)			(_x << 0)
#घोषणा BLENDCON				0x260
#घोषणा BLENDCON_NEW_MASK			(1 << 0)
#घोषणा BLENDCON_NEW_8BIT_ALPHA_VALUE		(1 << 0)
#घोषणा BLENDCON_NEW_4BIT_ALPHA_VALUE		(0 << 0)

/* Display port घड़ी control */
#घोषणा DP_MIE_CLKCON				0x27c
#घोषणा DP_MIE_CLK_DISABLE			0x0
#घोषणा DP_MIE_CLK_DP_ENABLE			0x2
#घोषणा DP_MIE_CLK_MIE_ENABLE			0x3

/* Notes on per-winकरोw bpp settings
 *
 * Value	Win0	 Win1	  Win2	   Win3	    Win 4
 * 0000		1(P)	 1(P)	  1(P)	   1(P)	    1(P)
 * 0001		2(P)	 2(P)     2(P)	   2(P)	    2(P)
 * 0010		4(P)	 4(P)     4(P)	   4(P)     -none-
 * 0011		8(P)	 8(P)     -none-   -none-   -none-
 * 0100		-none-	 8(A232)  8(A232)  -none-   -none-
 * 0101		16(565)	 16(565)  16(565)  16(565)   16(565)
 * 0110		-none-	 16(A555) 16(A555) 16(A555)  16(A555)
 * 0111		16(I555) 16(I565) 16(I555) 16(I555)  16(I555)
 * 1000		18(666)	 18(666)  18(666)  18(666)   18(666)
 * 1001		-none-	 18(A665) 18(A665) 18(A665)  16(A665)
 * 1010		-none-	 19(A666) 19(A666) 19(A666)  19(A666)
 * 1011		24(888)	 24(888)  24(888)  24(888)   24(888)
 * 1100		-none-	 24(A887) 24(A887) 24(A887)  24(A887)
 * 1101		-none-	 25(A888) 25(A888) 25(A888)  25(A888)
 * 1110		-none-	 -none-	  -none-   -none-    -none-
 * 1111		-none-	 -none-   -none-   -none-    -none-
*/

/* FIMD Version 8 रेजिस्टर offset definitions */
#घोषणा FIMD_V8_VIDTCON0	0x20010
#घोषणा FIMD_V8_VIDTCON1	0x20014
#घोषणा FIMD_V8_VIDTCON2	0x20018
#घोषणा FIMD_V8_VIDTCON3	0x2001C
#घोषणा FIMD_V8_VIDCON1		0x20004
