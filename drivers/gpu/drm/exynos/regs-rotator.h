<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* drivers/gpu/drm/exynos/regs-rotator.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Register definition file क्रम Samsung Rotator Interface (Rotator) driver
*/

#अगर_अघोषित EXYNOS_REGS_ROTATOR_H
#घोषणा EXYNOS_REGS_ROTATOR_H

/* Configuration */
#घोषणा ROT_CONFIG			0x00
#घोषणा ROT_CONFIG_IRQ			(3 << 8)

/* Image Control */
#घोषणा ROT_CONTROL			0x10
#घोषणा ROT_CONTROL_PATTERN_WRITE	(1 << 16)
#घोषणा ROT_CONTROL_FMT_YCBCR420_2P	(1 << 8)
#घोषणा ROT_CONTROL_FMT_RGB888		(6 << 8)
#घोषणा ROT_CONTROL_FMT_MASK		(7 << 8)
#घोषणा ROT_CONTROL_FLIP_VERTICAL	(2 << 6)
#घोषणा ROT_CONTROL_FLIP_HORIZONTAL	(3 << 6)
#घोषणा ROT_CONTROL_FLIP_MASK		(3 << 6)
#घोषणा ROT_CONTROL_ROT_90		(1 << 4)
#घोषणा ROT_CONTROL_ROT_180		(2 << 4)
#घोषणा ROT_CONTROL_ROT_270		(3 << 4)
#घोषणा ROT_CONTROL_ROT_MASK		(3 << 4)
#घोषणा ROT_CONTROL_START		(1 << 0)

/* Status */
#घोषणा ROT_STATUS			0x20
#घोषणा ROT_STATUS_IRQ_PENDING(x)	(1 << (x))
#घोषणा ROT_STATUS_IRQ(x)		(((x) >> 8) & 0x3)
#घोषणा ROT_STATUS_IRQ_VAL_COMPLETE	1
#घोषणा ROT_STATUS_IRQ_VAL_ILLEGAL	2

/* Buffer Address */
#घोषणा ROT_SRC_BUF_ADDR(n)		(0x30 + ((n) << 2))
#घोषणा ROT_DST_BUF_ADDR(n)		(0x50 + ((n) << 2))

/* Buffer Size */
#घोषणा ROT_SRC_BUF_SIZE		0x3c
#घोषणा ROT_DST_BUF_SIZE		0x5c
#घोषणा ROT_SET_BUF_SIZE_H(x)		((x) << 16)
#घोषणा ROT_SET_BUF_SIZE_W(x)		((x) << 0)
#घोषणा ROT_GET_BUF_SIZE_H(x)		((x) >> 16)
#घोषणा ROT_GET_BUF_SIZE_W(x)		((x) & 0xffff)

/* Crop Position */
#घोषणा ROT_SRC_CROP_POS		0x40
#घोषणा ROT_DST_CROP_POS		0x60
#घोषणा ROT_CROP_POS_Y(x)		((x) << 16)
#घोषणा ROT_CROP_POS_X(x)		((x) << 0)

/* Source Crop Size */
#घोषणा ROT_SRC_CROP_SIZE		0x44
#घोषणा ROT_SRC_CROP_SIZE_H(x)		((x) << 16)
#घोषणा ROT_SRC_CROP_SIZE_W(x)		((x) << 0)

/* Round to nearest aligned value */
#घोषणा ROT_ALIGN(x, align, mask)	(((x) + (1 << ((align) - 1))) & (mask))
/* Minimum limit value */
#घोषणा ROT_MIN(min, mask)		(((min) + ~(mask)) & (mask))
/* Maximum limit value */
#घोषणा ROT_MAX(max, mask)		((max) & (mask))

#पूर्ण_अगर /* EXYNOS_REGS_ROTATOR_H */

