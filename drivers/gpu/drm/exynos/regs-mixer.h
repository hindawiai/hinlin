<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Cloned from drivers/media/video/s5p-tv/regs-mixer.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 * http://www.samsung.com/
 *
 * Mixer रेजिस्टर header file क्रम Samsung Mixer driver
*/
#अगर_अघोषित SAMSUNG_REGS_MIXER_H
#घोषणा SAMSUNG_REGS_MIXER_H

/*
 * Register part
 */
#घोषणा MXR_STATUS			0x0000
#घोषणा MXR_CFG				0x0004
#घोषणा MXR_INT_EN			0x0008
#घोषणा MXR_INT_STATUS			0x000C
#घोषणा MXR_LAYER_CFG			0x0010
#घोषणा MXR_VIDEO_CFG			0x0014
#घोषणा MXR_GRAPHIC0_CFG		0x0020
#घोषणा MXR_GRAPHIC0_BASE		0x0024
#घोषणा MXR_GRAPHIC0_SPAN		0x0028
#घोषणा MXR_GRAPHIC0_SXY		0x002C
#घोषणा MXR_GRAPHIC0_WH			0x0030
#घोषणा MXR_GRAPHIC0_DXY		0x0034
#घोषणा MXR_GRAPHIC0_BLANK		0x0038
#घोषणा MXR_GRAPHIC1_CFG		0x0040
#घोषणा MXR_GRAPHIC1_BASE		0x0044
#घोषणा MXR_GRAPHIC1_SPAN		0x0048
#घोषणा MXR_GRAPHIC1_SXY		0x004C
#घोषणा MXR_GRAPHIC1_WH			0x0050
#घोषणा MXR_GRAPHIC1_DXY		0x0054
#घोषणा MXR_GRAPHIC1_BLANK		0x0058
#घोषणा MXR_BG_CFG			0x0060
#घोषणा MXR_BG_COLOR0			0x0064
#घोषणा MXR_BG_COLOR1			0x0068
#घोषणा MXR_BG_COLOR2			0x006C
#घोषणा MXR_CM_COEFF_Y			0x0080
#घोषणा MXR_CM_COEFF_CB			0x0084
#घोषणा MXR_CM_COEFF_CR			0x0088
#घोषणा MXR_MO				0x0304
#घोषणा MXR_RESOLUTION			0x0310

#घोषणा MXR_CFG_S			0x2004
#घोषणा MXR_GRAPHIC0_BASE_S		0x2024
#घोषणा MXR_GRAPHIC1_BASE_S		0x2044

/* क्रम parametrized access to layer रेजिस्टरs */
#घोषणा MXR_GRAPHIC_CFG(i)		(0x0020 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_BASE(i)		(0x0024 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_SPAN(i)		(0x0028 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_SXY(i)		(0x002C + (i) * 0x20)
#घोषणा MXR_GRAPHIC_WH(i)		(0x0030 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_DXY(i)		(0x0034 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_BLANK(i)		(0x0038 + (i) * 0x20)
#घोषणा MXR_GRAPHIC_BASE_S(i)		(0x2024 + (i) * 0x20)

/*
 * Bit definition part
 */

/* generates mask क्रम range of bits */
#घोषणा MXR_MASK(high_bit, low_bit) \
	(((2 << ((high_bit) - (low_bit))) - 1) << (low_bit))

#घोषणा MXR_MASK_VAL(val, high_bit, low_bit) \
	(((val) << (low_bit)) & MXR_MASK(high_bit, low_bit))

/* bits क्रम MXR_STATUS */
#घोषणा MXR_STATUS_SOFT_RESET		(1 << 8)
#घोषणा MXR_STATUS_16_BURST		(1 << 7)
#घोषणा MXR_STATUS_BURST_MASK		(1 << 7)
#घोषणा MXR_STATUS_BIG_ENDIAN		(1 << 3)
#घोषणा MXR_STATUS_ENDIAN_MASK		(1 << 3)
#घोषणा MXR_STATUS_SYNC_ENABLE		(1 << 2)
#घोषणा MXR_STATUS_REG_IDLE		(1 << 1)
#घोषणा MXR_STATUS_REG_RUN		(1 << 0)

/* bits क्रम MXR_CFG */
#घोषणा MXR_CFG_LAYER_UPDATE		(1 << 31)
#घोषणा MXR_CFG_LAYER_UPDATE_COUNT_MASK (3 << 29)
#घोषणा MXR_CFG_QUANT_RANGE_FULL	(0 << 9)
#घोषणा MXR_CFG_QUANT_RANGE_LIMITED	(1 << 9)
#घोषणा MXR_CFG_RGB601			(0 << 10)
#घोषणा MXR_CFG_RGB709			(1 << 10)

#घोषणा MXR_CFG_RGB_FMT_MASK		0x600
#घोषणा MXR_CFG_OUT_YUV444		(0 << 8)
#घोषणा MXR_CFG_OUT_RGB888		(1 << 8)
#घोषणा MXR_CFG_OUT_MASK		(1 << 8)
#घोषणा MXR_CFG_DST_SDO			(0 << 7)
#घोषणा MXR_CFG_DST_HDMI		(1 << 7)
#घोषणा MXR_CFG_DST_MASK		(1 << 7)
#घोषणा MXR_CFG_SCAN_HD_720		(0 << 6)
#घोषणा MXR_CFG_SCAN_HD_1080		(1 << 6)
#घोषणा MXR_CFG_GRP1_ENABLE		(1 << 5)
#घोषणा MXR_CFG_GRP0_ENABLE		(1 << 4)
#घोषणा MXR_CFG_VP_ENABLE		(1 << 3)
#घोषणा MXR_CFG_SCAN_INTERLACE		(0 << 2)
#घोषणा MXR_CFG_SCAN_PROGRESSIVE	(1 << 2)
#घोषणा MXR_CFG_SCAN_NTSC		(0 << 1)
#घोषणा MXR_CFG_SCAN_PAL		(1 << 1)
#घोषणा MXR_CFG_SCAN_SD			(0 << 0)
#घोषणा MXR_CFG_SCAN_HD			(1 << 0)
#घोषणा MXR_CFG_SCAN_MASK		0x47

/* bits क्रम MXR_VIDEO_CFG */
#घोषणा MXR_VID_CFG_BLEND_EN		(1 << 16)

/* bits क्रम MXR_GRAPHICn_CFG */
#घोषणा MXR_GRP_CFG_COLOR_KEY_DISABLE	(1 << 21)
#घोषणा MXR_GRP_CFG_BLEND_PRE_MUL	(1 << 20)
#घोषणा MXR_GRP_CFG_WIN_BLEND_EN	(1 << 17)
#घोषणा MXR_GRP_CFG_PIXEL_BLEND_EN	(1 << 16)
#घोषणा MXR_GRP_CFG_MISC_MASK		((3 << 16) | (3 << 20) | 0xff)
#घोषणा MXR_GRP_CFG_FORMAT_VAL(x)	MXR_MASK_VAL(x, 11, 8)
#घोषणा MXR_GRP_CFG_FORMAT_MASK		MXR_GRP_CFG_FORMAT_VAL(~0)
#घोषणा MXR_GRP_CFG_ALPHA_VAL(x)	MXR_MASK_VAL(x, 7, 0)

/* bits क्रम MXR_GRAPHICn_WH */
#घोषणा MXR_GRP_WH_H_SCALE(x)		MXR_MASK_VAL(x, 28, 28)
#घोषणा MXR_GRP_WH_V_SCALE(x)		MXR_MASK_VAL(x, 12, 12)
#घोषणा MXR_GRP_WH_WIDTH(x)		MXR_MASK_VAL(x, 26, 16)
#घोषणा MXR_GRP_WH_HEIGHT(x)		MXR_MASK_VAL(x, 10, 0)

/* bits क्रम MXR_RESOLUTION */
#घोषणा MXR_MXR_RES_HEIGHT(x)		MXR_MASK_VAL(x, 26, 16)
#घोषणा MXR_MXR_RES_WIDTH(x)		MXR_MASK_VAL(x, 10, 0)

/* bits क्रम MXR_GRAPHICn_SXY */
#घोषणा MXR_GRP_SXY_SX(x)		MXR_MASK_VAL(x, 26, 16)
#घोषणा MXR_GRP_SXY_SY(x)		MXR_MASK_VAL(x, 10, 0)

/* bits क्रम MXR_GRAPHICn_DXY */
#घोषणा MXR_GRP_DXY_DX(x)		MXR_MASK_VAL(x, 26, 16)
#घोषणा MXR_GRP_DXY_DY(x)		MXR_MASK_VAL(x, 10, 0)

/* bits क्रम MXR_INT_EN */
#घोषणा MXR_INT_EN_VSYNC		(1 << 11)
#घोषणा MXR_INT_EN_ALL			(0x0f << 8)

/* bits क्रम MXR_INT_STATUS */
#घोषणा MXR_INT_CLEAR_VSYNC		(1 << 11)
#घोषणा MXR_INT_STATUS_VSYNC		(1 << 0)

/* bits क्रम MXR_LAYER_CFG */
#घोषणा MXR_LAYER_CFG_GRP1_VAL(x)	MXR_MASK_VAL(x, 11, 8)
#घोषणा MXR_LAYER_CFG_GRP1_MASK		MXR_LAYER_CFG_GRP1_VAL(~0)
#घोषणा MXR_LAYER_CFG_GRP0_VAL(x)	MXR_MASK_VAL(x, 7, 4)
#घोषणा MXR_LAYER_CFG_GRP0_MASK		MXR_LAYER_CFG_GRP0_VAL(~0)
#घोषणा MXR_LAYER_CFG_VP_VAL(x)		MXR_MASK_VAL(x, 3, 0)
#घोषणा MXR_LAYER_CFG_VP_MASK		MXR_LAYER_CFG_VP_VAL(~0)

/* bits क्रम MXR_CM_COEFF_Y */
#घोषणा MXR_CM_COEFF_RGB_FULL		(1 << 30)

#पूर्ण_अगर /* SAMSUNG_REGS_MIXER_H */

