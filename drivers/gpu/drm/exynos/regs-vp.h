<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Cloned from drivers/media/video/s5p-tv/regs-vp.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Video processor रेजिस्टर header file क्रम Samsung Mixer driver
 */

#अगर_अघोषित SAMSUNG_REGS_VP_H
#घोषणा SAMSUNG_REGS_VP_H

/*
 * Register part
 */

#घोषणा VP_ENABLE			0x0000
#घोषणा VP_SRESET			0x0004
#घोषणा VP_SHADOW_UPDATE		0x0008
#घोषणा VP_FIELD_ID			0x000C
#घोषणा VP_MODE				0x0010
#घोषणा VP_IMG_SIZE_Y			0x0014
#घोषणा VP_IMG_SIZE_C			0x0018
#घोषणा VP_PER_RATE_CTRL		0x001C
#घोषणा VP_TOP_Y_PTR			0x0028
#घोषणा VP_BOT_Y_PTR			0x002C
#घोषणा VP_TOP_C_PTR			0x0030
#घोषणा VP_BOT_C_PTR			0x0034
#घोषणा VP_ENDIAN_MODE			0x03CC
#घोषणा VP_SRC_H_POSITION		0x0044
#घोषणा VP_SRC_V_POSITION		0x0048
#घोषणा VP_SRC_WIDTH			0x004C
#घोषणा VP_SRC_HEIGHT			0x0050
#घोषणा VP_DST_H_POSITION		0x0054
#घोषणा VP_DST_V_POSITION		0x0058
#घोषणा VP_DST_WIDTH			0x005C
#घोषणा VP_DST_HEIGHT			0x0060
#घोषणा VP_H_RATIO			0x0064
#घोषणा VP_V_RATIO			0x0068
#घोषणा VP_POLY8_Y0_LL			0x006C
#घोषणा VP_POLY4_Y0_LL			0x00EC
#घोषणा VP_POLY4_C0_LL			0x012C

/*
 * Bit definition part
 */

/* generates mask क्रम range of bits */

#घोषणा VP_MASK(high_bit, low_bit) \
	(((2 << ((high_bit) - (low_bit))) - 1) << (low_bit))

#घोषणा VP_MASK_VAL(val, high_bit, low_bit) \
	(((val) << (low_bit)) & VP_MASK(high_bit, low_bit))

 /* VP_ENABLE */
#घोषणा VP_ENABLE_ON			(1 << 0)

/* VP_SRESET */
#घोषणा VP_SRESET_PROCESSING		(1 << 0)

/* VP_SHADOW_UPDATE */
#घोषणा VP_SHADOW_UPDATE_ENABLE		(1 << 0)

/* VP_MODE */
#घोषणा VP_MODE_NV12			(0 << 6)
#घोषणा VP_MODE_NV21			(1 << 6)
#घोषणा VP_MODE_LINE_SKIP		(1 << 5)
#घोषणा VP_MODE_MEM_LINEAR		(0 << 4)
#घोषणा VP_MODE_MEM_TILED		(1 << 4)
#घोषणा VP_MODE_FMT_MASK		(5 << 4)
#घोषणा VP_MODE_FIELD_ID_AUTO_TOGGLING	(1 << 2)
#घोषणा VP_MODE_2D_IPC			(1 << 1)

/* VP_IMG_SIZE_Y */
/* VP_IMG_SIZE_C */
#घोषणा VP_IMG_HSIZE(x)			VP_MASK_VAL(x, 29, 16)
#घोषणा VP_IMG_VSIZE(x)			VP_MASK_VAL(x, 13, 0)

/* VP_SRC_H_POSITION */
#घोषणा VP_SRC_H_POSITION_VAL(x)	VP_MASK_VAL(x, 14, 4)

/* VP_ENDIAN_MODE */
#घोषणा VP_ENDIAN_MODE_LITTLE		(1 << 0)

#पूर्ण_अगर /* SAMSUNG_REGS_VP_H */
