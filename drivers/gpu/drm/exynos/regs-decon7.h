<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Ajay Kumar <ajaykumar.rs@samsung.com>
 */

#अगर_अघोषित EXYNOS_REGS_DECON7_H
#घोषणा EXYNOS_REGS_DECON7_H

/* VIDCON0 */
#घोषणा VIDCON0					0x00

#घोषणा VIDCON0_SWRESET				(1 << 28)
#घोषणा VIDCON0_DECON_STOP_STATUS		(1 << 2)
#घोषणा VIDCON0_ENVID				(1 << 1)
#घोषणा VIDCON0_ENVID_F				(1 << 0)

/* VIDOUTCON0 */
#घोषणा VIDOUTCON0				0x4

#घोषणा VIDOUTCON0_DUAL_MASK			(0x3 << 24)
#घोषणा VIDOUTCON0_DUAL_ON			(0x3 << 24)
#घोषणा VIDOUTCON0_DISP_IF_1_ON			(0x2 << 24)
#घोषणा VIDOUTCON0_DISP_IF_0_ON			(0x1 << 24)
#घोषणा VIDOUTCON0_DUAL_OFF			(0x0 << 24)
#घोषणा VIDOUTCON0_IF_SHIFT			23
#घोषणा VIDOUTCON0_IF_MASK			(0x1 << 23)
#घोषणा VIDOUTCON0_RGBIF			(0x0 << 23)
#घोषणा VIDOUTCON0_I80IF			(0x1 << 23)

/* VIDCON3 */
#घोषणा VIDCON3					0x8

/* VIDCON4 */
#घोषणा VIDCON4					0xC
#घोषणा VIDCON4_FIFOCNT_START_EN		(1 << 0)

/* VCLKCON0 */
#घोषणा VCLKCON0				0x10
#घोषणा VCLKCON0_CLKVALUP			(1 << 8)
#घोषणा VCLKCON0_VCLKFREE			(1 << 0)

/* VCLKCON */
#घोषणा VCLKCON1				0x14
#घोषणा VCLKCON1_CLKVAL_NUM_VCLK(val)		(((val) & 0xff) << 0)
#घोषणा VCLKCON2				0x18

/* SHADOWCON */
#घोषणा SHADOWCON				0x30

#घोषणा SHADOWCON_WINx_PROTECT(_win)		(1 << (10 + (_win)))

/* WINCONx */
#घोषणा WINCON(_win)				(0x50 + ((_win) * 4))

#घोषणा WINCONx_BUFSTATUS			(0x3 << 30)
#घोषणा WINCONx_BUFSEL_MASK			(0x3 << 28)
#घोषणा WINCONx_BUFSEL_SHIFT			28
#घोषणा WINCONx_TRIPLE_BUF_MODE			(0x1 << 18)
#घोषणा WINCONx_DOUBLE_BUF_MODE			(0x0 << 18)
#घोषणा WINCONx_BURSTLEN_16WORD			(0x0 << 11)
#घोषणा WINCONx_BURSTLEN_8WORD			(0x1 << 11)
#घोषणा WINCONx_BURSTLEN_MASK			(0x1 << 11)
#घोषणा WINCONx_BURSTLEN_SHIFT			11
#घोषणा WINCONx_BLD_PLANE			(0 << 8)
#घोषणा WINCONx_BLD_PIX				(1 << 8)
#घोषणा WINCONx_ALPHA_MUL			(1 << 7)

#घोषणा WINCONx_BPPMODE_MASK			(0xf << 2)
#घोषणा WINCONx_BPPMODE_SHIFT			2
#घोषणा WINCONx_BPPMODE_16BPP_565		(0x8 << 2)
#घोषणा WINCONx_BPPMODE_24BPP_BGRx		(0x7 << 2)
#घोषणा WINCONx_BPPMODE_24BPP_RGBx		(0x6 << 2)
#घोषणा WINCONx_BPPMODE_24BPP_xBGR		(0x5 << 2)
#घोषणा WINCONx_BPPMODE_24BPP_xRGB		(0x4 << 2)
#घोषणा WINCONx_BPPMODE_32BPP_BGRA		(0x3 << 2)
#घोषणा WINCONx_BPPMODE_32BPP_RGBA		(0x2 << 2)
#घोषणा WINCONx_BPPMODE_32BPP_ABGR		(0x1 << 2)
#घोषणा WINCONx_BPPMODE_32BPP_ARGB		(0x0 << 2)
#घोषणा WINCONx_ALPHA_SEL			(1 << 1)
#घोषणा WINCONx_ENWIN				(1 << 0)

#घोषणा WINCON1_ALPHA_MUL_F			(1 << 7)
#घोषणा WINCON2_ALPHA_MUL_F			(1 << 7)
#घोषणा WINCON3_ALPHA_MUL_F			(1 << 7)
#घोषणा WINCON4_ALPHA_MUL_F			(1 << 7)

/*  VIDOSDxH: The height क्रम the OSD image(READ ONLY)*/
#घोषणा VIDOSD_H(_x)				(0x80 + ((_x) * 4))

/* Frame buffer start addresses: VIDWxxADD0n */
#घोषणा VIDW_BUF_START(_win)			(0x80 + ((_win) * 0x10))
#घोषणा VIDW_BUF_START1(_win)			(0x84 + ((_win) * 0x10))
#घोषणा VIDW_BUF_START2(_win)			(0x88 + ((_win) * 0x10))

#घोषणा VIDW_WHOLE_X(_win)			(0x0130 + ((_win) * 8))
#घोषणा VIDW_WHOLE_Y(_win)			(0x0134 + ((_win) * 8))
#घोषणा VIDW_OFFSET_X(_win)			(0x0170 + ((_win) * 8))
#घोषणा VIDW_OFFSET_Y(_win)			(0x0174 + ((_win) * 8))
#घोषणा VIDW_BLKOFFSET(_win)			(0x01B0 + ((_win) * 4))
#घोषणा VIDW_BLKSIZE(win)			(0x0200 + ((_win) * 4))

/* Interrupt controls रेजिस्टर */
#घोषणा VIDINTCON2				0x228

#घोषणा VIDINTCON1_INTEXTRA1_EN			(1 << 1)
#घोषणा VIDINTCON1_INTEXTRA0_EN			(1 << 0)

/* Interrupt controls and status रेजिस्टर */
#घोषणा VIDINTCON3				0x22C

#घोषणा VIDINTCON1_INTEXTRA1_PEND		(1 << 1)
#घोषणा VIDINTCON1_INTEXTRA0_PEND		(1 << 0)

/* VIDOSDxA ~ VIDOSDxE */
#घोषणा VIDOSD_BASE				0x230

#घोषणा OSD_STRIDE				0x20

#घोषणा VIDOSD_A(_win)				(VIDOSD_BASE + \
						((_win) * OSD_STRIDE) + 0x00)
#घोषणा VIDOSD_B(_win)				(VIDOSD_BASE + \
						((_win) * OSD_STRIDE) + 0x04)
#घोषणा VIDOSD_C(_win)				(VIDOSD_BASE + \
						((_win) * OSD_STRIDE) + 0x08)
#घोषणा VIDOSD_D(_win)				(VIDOSD_BASE + \
						((_win) * OSD_STRIDE) + 0x0C)
#घोषणा VIDOSD_E(_win)				(VIDOSD_BASE + \
						((_win) * OSD_STRIDE) + 0x10)

#घोषणा VIDOSDxA_TOPLEFT_X_MASK			(0x1fff << 13)
#घोषणा VIDOSDxA_TOPLEFT_X_SHIFT		13
#घोषणा VIDOSDxA_TOPLEFT_X_LIMIT		0x1fff
#घोषणा VIDOSDxA_TOPLEFT_X(_x)			(((_x) & 0x1fff) << 13)

#घोषणा VIDOSDxA_TOPLEFT_Y_MASK			(0x1fff << 0)
#घोषणा VIDOSDxA_TOPLEFT_Y_SHIFT		0
#घोषणा VIDOSDxA_TOPLEFT_Y_LIMIT		0x1fff
#घोषणा VIDOSDxA_TOPLEFT_Y(_x)			(((_x) & 0x1fff) << 0)

#घोषणा VIDOSDxB_BOTRIGHT_X_MASK		(0x1fff << 13)
#घोषणा VIDOSDxB_BOTRIGHT_X_SHIFT		13
#घोषणा VIDOSDxB_BOTRIGHT_X_LIMIT		0x1fff
#घोषणा VIDOSDxB_BOTRIGHT_X(_x)			(((_x) & 0x1fff) << 13)

#घोषणा VIDOSDxB_BOTRIGHT_Y_MASK		(0x1fff << 0)
#घोषणा VIDOSDxB_BOTRIGHT_Y_SHIFT		0
#घोषणा VIDOSDxB_BOTRIGHT_Y_LIMIT		0x1fff
#घोषणा VIDOSDxB_BOTRIGHT_Y(_x)			(((_x) & 0x1fff) << 0)

#घोषणा VIDOSDxC_ALPHA0_R_F(_x)			(((_x) & 0xFF) << 16)
#घोषणा VIDOSDxC_ALPHA0_G_F(_x)			(((_x) & 0xFF) << 8)
#घोषणा VIDOSDxC_ALPHA0_B_F(_x)			(((_x) & 0xFF) << 0)

#घोषणा VIDOSDxD_ALPHA1_R_F(_x)			(((_x) & 0xFF) << 16)
#घोषणा VIDOSDxD_ALPHA1_G_F(_x)			(((_x) & 0xFF) << 8)
#घोषणा VIDOSDxD_ALPHA1_B_F(_x)			(((_x) & 0xFF) >> 0)

/* Winकरोw MAP (Color map) */
#घोषणा WINxMAP(_win)				(0x340 + ((_win) * 4))

#घोषणा WINxMAP_MAP				(1 << 24)
#घोषणा WINxMAP_MAP_COLOUR_MASK			(0xffffff << 0)
#घोषणा WINxMAP_MAP_COLOUR_SHIFT		0
#घोषणा WINxMAP_MAP_COLOUR_LIMIT		0xffffff
#घोषणा WINxMAP_MAP_COLOUR(_x)			((_x) << 0)

/* Winकरोw colour-key control रेजिस्टरs */
#घोषणा WKEYCON					0x370

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

/* color key control रेजिस्टर क्रम hardware winकरोw 1 ~ 4. */
#घोषणा WKEYCON0_BASE(x)		((WKEYCON + WKEYCON0) + ((x - 1) * 8))
/* color key value रेजिस्टर क्रम hardware winकरोw 1 ~ 4. */
#घोषणा WKEYCON1_BASE(x)		((WKEYCON + WKEYCON1) + ((x - 1) * 8))

/* Winकरोw KEY Alpha value */
#घोषणा WxKEYALPHA(_win)			(0x3A0 + (((_win) - 1) * 0x4))

#घोषणा Wx_KEYALPHA_R_F_SHIFT			16
#घोषणा Wx_KEYALPHA_G_F_SHIFT			8
#घोषणा Wx_KEYALPHA_B_F_SHIFT			0

/* Blending equation */
#घोषणा BLENDE(_win)				(0x03C0 + ((_win) * 4))
#घोषणा BLENDE_COEF_ZERO			0x0
#घोषणा BLENDE_COEF_ONE				0x1
#घोषणा BLENDE_COEF_ALPHA_A			0x2
#घोषणा BLENDE_COEF_ONE_MINUS_ALPHA_A		0x3
#घोषणा BLENDE_COEF_ALPHA_B			0x4
#घोषणा BLENDE_COEF_ONE_MINUS_ALPHA_B		0x5
#घोषणा BLENDE_COEF_ALPHA0			0x6
#घोषणा BLENDE_COEF_A				0xA
#घोषणा BLENDE_COEF_ONE_MINUS_A			0xB
#घोषणा BLENDE_COEF_B				0xC
#घोषणा BLENDE_COEF_ONE_MINUS_B			0xD
#घोषणा BLENDE_Q_FUNC(_v)			((_v) << 18)
#घोषणा BLENDE_P_FUNC(_v)			((_v) << 12)
#घोषणा BLENDE_B_FUNC(_v)			((_v) << 6)
#घोषणा BLENDE_A_FUNC(_v)			((_v) << 0)

/* Blending equation control */
#घोषणा BLENDCON				0x3D8
#घोषणा BLENDCON_NEW_MASK			(1 << 0)
#घोषणा BLENDCON_NEW_8BIT_ALPHA_VALUE		(1 << 0)
#घोषणा BLENDCON_NEW_4BIT_ALPHA_VALUE		(0 << 0)

/* Interrupt control रेजिस्टर */
#घोषणा VIDINTCON0				0x500

#घोषणा VIDINTCON0_WAKEUP_MASK			(0x3f << 26)
#घोषणा VIDINTCON0_INTEXTRAEN			(1 << 21)

#घोषणा VIDINTCON0_FRAMESEL0_SHIFT		15
#घोषणा VIDINTCON0_FRAMESEL0_MASK		(0x3 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_BACKPORCH		(0x0 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_VSYNC		(0x1 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_ACTIVE		(0x2 << 15)
#घोषणा VIDINTCON0_FRAMESEL0_FRONTPORCH		(0x3 << 15)

#घोषणा VIDINTCON0_INT_FRAME			(1 << 11)

#घोषणा VIDINTCON0_FIFOLEVEL_MASK		(0x7 << 3)
#घोषणा VIDINTCON0_FIFOLEVEL_SHIFT		3
#घोषणा VIDINTCON0_FIFOLEVEL_EMPTY		(0x0 << 3)
#घोषणा VIDINTCON0_FIFOLEVEL_TO25PC		(0x1 << 3)
#घोषणा VIDINTCON0_FIFOLEVEL_TO50PC		(0x2 << 3)
#घोषणा VIDINTCON0_FIFOLEVEL_FULL		(0x4 << 3)

#घोषणा VIDINTCON0_FIFOSEL_MAIN_EN		(1 << 1)
#घोषणा VIDINTCON0_INT_FIFO			(1 << 1)

#घोषणा VIDINTCON0_INT_ENABLE			(1 << 0)

/* Interrupt controls and status रेजिस्टर */
#घोषणा VIDINTCON1				0x504

#घोषणा VIDINTCON1_INT_EXTRA			(1 << 3)
#घोषणा VIDINTCON1_INT_I80			(1 << 2)
#घोषणा VIDINTCON1_INT_FRAME			(1 << 1)
#घोषणा VIDINTCON1_INT_FIFO			(1 << 0)

/* VIDCON1 */
#घोषणा VIDCON1(_x)				(0x0600 + ((_x) * 0x50))
#घोषणा VIDCON1_LINECNT_GET(_v)			(((_v) >> 17) & 0x1fff)
#घोषणा VIDCON1_VCLK_MASK			(0x3 << 9)
#घोषणा VIDCON1_VCLK_HOLD			(0x0 << 9)
#घोषणा VIDCON1_VCLK_RUN			(0x1 << 9)
#घोषणा VIDCON1_VCLK_RUN_VDEN_DISABLE		(0x3 << 9)
#घोषणा VIDCON1_RGB_ORDER_O_MASK		(0x7 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_RGB			(0x0 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_GBR			(0x1 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_BRG			(0x2 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_BGR			(0x4 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_RBG			(0x5 << 4)
#घोषणा VIDCON1_RGB_ORDER_O_GRB			(0x6 << 4)

/* VIDTCON0 */
#घोषणा VIDTCON0				0x610

#घोषणा VIDTCON0_VBPD_MASK			(0xffff << 16)
#घोषणा VIDTCON0_VBPD_SHIFT			16
#घोषणा VIDTCON0_VBPD_LIMIT			0xffff
#घोषणा VIDTCON0_VBPD(_x)			((_x) << 16)

#घोषणा VIDTCON0_VFPD_MASK			(0xffff << 0)
#घोषणा VIDTCON0_VFPD_SHIFT			0
#घोषणा VIDTCON0_VFPD_LIMIT			0xffff
#घोषणा VIDTCON0_VFPD(_x)			((_x) << 0)

/* VIDTCON1 */
#घोषणा VIDTCON1				0x614

#घोषणा VIDTCON1_VSPW_MASK			(0xffff << 16)
#घोषणा VIDTCON1_VSPW_SHIFT			16
#घोषणा VIDTCON1_VSPW_LIMIT			0xffff
#घोषणा VIDTCON1_VSPW(_x)			((_x) << 16)

/* VIDTCON2 */
#घोषणा VIDTCON2				0x618

#घोषणा VIDTCON2_HBPD_MASK			(0xffff << 16)
#घोषणा VIDTCON2_HBPD_SHIFT			16
#घोषणा VIDTCON2_HBPD_LIMIT			0xffff
#घोषणा VIDTCON2_HBPD(_x)			((_x) << 16)

#घोषणा VIDTCON2_HFPD_MASK			(0xffff << 0)
#घोषणा VIDTCON2_HFPD_SHIFT			0
#घोषणा VIDTCON2_HFPD_LIMIT			0xffff
#घोषणा VIDTCON2_HFPD(_x)			((_x) << 0)

/* VIDTCON3 */
#घोषणा VIDTCON3				0x61C

#घोषणा VIDTCON3_HSPW_MASK			(0xffff << 16)
#घोषणा VIDTCON3_HSPW_SHIFT			16
#घोषणा VIDTCON3_HSPW_LIMIT			0xffff
#घोषणा VIDTCON3_HSPW(_x)			((_x) << 16)

/* VIDTCON4 */
#घोषणा VIDTCON4				0x620

#घोषणा VIDTCON4_LINEVAL_MASK			(0xfff << 16)
#घोषणा VIDTCON4_LINEVAL_SHIFT			16
#घोषणा VIDTCON4_LINEVAL_LIMIT			0xfff
#घोषणा VIDTCON4_LINEVAL(_x)			(((_x) & 0xfff) << 16)

#घोषणा VIDTCON4_HOZVAL_MASK			(0xfff << 0)
#घोषणा VIDTCON4_HOZVAL_SHIFT			0
#घोषणा VIDTCON4_HOZVAL_LIMIT			0xfff
#घोषणा VIDTCON4_HOZVAL(_x)			(((_x) & 0xfff) << 0)

/* LINECNT OP THRSHOLD*/
#घोषणा LINECNT_OP_THRESHOLD			0x630

/* CRCCTRL */
#घोषणा CRCCTRL					0x6C8
#घोषणा CRCCTRL_CRCCLKEN			(0x1 << 2)
#घोषणा CRCCTRL_CRCSTART_F			(0x1 << 1)
#घोषणा CRCCTRL_CRCEN				(0x1 << 0)

/* DECON_CMU */
#घोषणा DECON_CMU				0x704

#घोषणा DECON_CMU_ALL_CLKGATE_ENABLE		0x3
#घोषणा DECON_CMU_SE_CLKGATE_ENABLE		(0x1 << 2)
#घोषणा DECON_CMU_SFR_CLKGATE_ENABLE		(0x1 << 1)
#घोषणा DECON_CMU_MEM_CLKGATE_ENABLE		(0x1 << 0)

/* DECON_UPDATE */
#घोषणा DECON_UPDATE				0x710

#घोषणा DECON_UPDATE_SLAVE_SYNC			(1 << 4)
#घोषणा DECON_UPDATE_STANDALONE_F		(1 << 0)

#पूर्ण_अगर /* EXYNOS_REGS_DECON7_H */
