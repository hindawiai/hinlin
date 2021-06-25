<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Register definition file क्रम Samsung G-Scaler driver
 */

#अगर_अघोषित REGS_GSC_H_
#घोषणा REGS_GSC_H_

/* G-Scaler enable */
#घोषणा GSC_ENABLE			0x00
#घोषणा GSC_ENABLE_OP_STATUS		(1 << 2)
#घोषणा GSC_ENABLE_SFR_UPDATE		(1 << 1)
#घोषणा GSC_ENABLE_ON			(1 << 0)

/* G-Scaler S/W reset */
#घोषणा GSC_SW_RESET			0x04
#घोषणा GSC_SW_RESET_SRESET		(1 << 0)

/* G-Scaler IRQ */
#घोषणा GSC_IRQ				0x08
#घोषणा GSC_IRQ_STATUS_OR_IRQ		(1 << 17)
#घोषणा GSC_IRQ_STATUS_FRM_DONE_IRQ	(1 << 16)
#घोषणा GSC_IRQ_FRMDONE_MASK		(1 << 1)
#घोषणा GSC_IRQ_ENABLE			(1 << 0)

/* G-Scaler input control */
#घोषणा GSC_IN_CON			0x10
#घोषणा GSC_IN_ROT_MASK			(7 << 16)
#घोषणा GSC_IN_ROT_270			(7 << 16)
#घोषणा GSC_IN_ROT_90_YFLIP		(6 << 16)
#घोषणा GSC_IN_ROT_90_XFLIP		(5 << 16)
#घोषणा GSC_IN_ROT_90			(4 << 16)
#घोषणा GSC_IN_ROT_180			(3 << 16)
#घोषणा GSC_IN_ROT_YFLIP		(2 << 16)
#घोषणा GSC_IN_ROT_XFLIP		(1 << 16)
#घोषणा GSC_IN_RGB_TYPE_MASK		(3 << 14)
#घोषणा GSC_IN_RGB_HD_NARROW		(3 << 14)
#घोषणा GSC_IN_RGB_HD_WIDE		(2 << 14)
#घोषणा GSC_IN_RGB_SD_NARROW		(1 << 14)
#घोषणा GSC_IN_RGB_SD_WIDE		(0 << 14)
#घोषणा GSC_IN_YUV422_1P_ORDER_MASK	(1 << 13)
#घोषणा GSC_IN_YUV422_1P_ORDER_LSB_Y	(0 << 13)
#घोषणा GSC_IN_YUV422_1P_OEDER_LSB_C	(1 << 13)
#घोषणा GSC_IN_CHROMA_ORDER_MASK	(1 << 12)
#घोषणा GSC_IN_CHROMA_ORDER_CBCR	(0 << 12)
#घोषणा GSC_IN_CHROMA_ORDER_CRCB	(1 << 12)
#घोषणा GSC_IN_FORMAT_MASK		(7 << 8)
#घोषणा GSC_IN_XRGB8888			(0 << 8)
#घोषणा GSC_IN_RGB565			(1 << 8)
#घोषणा GSC_IN_YUV420_2P		(2 << 8)
#घोषणा GSC_IN_YUV420_3P		(3 << 8)
#घोषणा GSC_IN_YUV422_1P		(4 << 8)
#घोषणा GSC_IN_YUV422_2P		(5 << 8)
#घोषणा GSC_IN_YUV422_3P		(6 << 8)
#घोषणा GSC_IN_TILE_TYPE_MASK		(1 << 4)
#घोषणा GSC_IN_TILE_C_16x8		(0 << 4)
#घोषणा GSC_IN_TILE_MODE		(1 << 3)
#घोषणा GSC_IN_LOCAL_SEL_MASK		(3 << 1)
#घोषणा GSC_IN_PATH_MASK		(1 << 0)
#घोषणा GSC_IN_PATH_MEMORY		(0 << 0)

/* G-Scaler source image size */
#घोषणा GSC_SRCIMG_SIZE			0x14
#घोषणा GSC_SRCIMG_HEIGHT(x)		((x) << 16)
#घोषणा GSC_SRCIMG_WIDTH(x)		((x) << 0)

/* G-Scaler source image offset */
#घोषणा GSC_SRCIMG_OFFSET		0x18
#घोषणा GSC_SRCIMG_OFFSET_Y(x)		((x) << 16)
#घोषणा GSC_SRCIMG_OFFSET_X(x)		((x) << 0)

/* G-Scaler cropped source image size */
#घोषणा GSC_CROPPED_SIZE		0x1c
#घोषणा GSC_CROPPED_HEIGHT(x)		((x) << 16)
#घोषणा GSC_CROPPED_WIDTH(x)		((x) << 0)

/* G-Scaler output control */
#घोषणा GSC_OUT_CON			0x20
#घोषणा GSC_OUT_GLOBAL_ALPHA_MASK	(0xff << 24)
#घोषणा GSC_OUT_GLOBAL_ALPHA(x)		((x) << 24)
#घोषणा GSC_OUT_RGB_TYPE_MASK		(3 << 10)
#घोषणा GSC_OUT_RGB_HD_WIDE		(3 << 10)
#घोषणा GSC_OUT_RGB_HD_NARROW		(2 << 10)
#घोषणा GSC_OUT_RGB_SD_WIDE		(1 << 10)
#घोषणा GSC_OUT_RGB_SD_NARROW		(0 << 10)
#घोषणा GSC_OUT_YUV422_1P_ORDER_MASK	(1 << 9)
#घोषणा GSC_OUT_YUV422_1P_ORDER_LSB_Y	(0 << 9)
#घोषणा GSC_OUT_YUV422_1P_OEDER_LSB_C	(1 << 9)
#घोषणा GSC_OUT_CHROMA_ORDER_MASK	(1 << 8)
#घोषणा GSC_OUT_CHROMA_ORDER_CBCR	(0 << 8)
#घोषणा GSC_OUT_CHROMA_ORDER_CRCB	(1 << 8)
#घोषणा GSC_OUT_FORMAT_MASK		(7 << 4)
#घोषणा GSC_OUT_XRGB8888		(0 << 4)
#घोषणा GSC_OUT_RGB565			(1 << 4)
#घोषणा GSC_OUT_YUV420_2P		(2 << 4)
#घोषणा GSC_OUT_YUV420_3P		(3 << 4)
#घोषणा GSC_OUT_YUV422_1P		(4 << 4)
#घोषणा GSC_OUT_YUV422_2P		(5 << 4)
#घोषणा GSC_OUT_YUV444			(7 << 4)
#घोषणा GSC_OUT_TILE_TYPE_MASK		(1 << 2)
#घोषणा GSC_OUT_TILE_C_16x8		(0 << 2)
#घोषणा GSC_OUT_TILE_MODE		(1 << 1)
#घोषणा GSC_OUT_PATH_MASK		(1 << 0)
#घोषणा GSC_OUT_PATH_LOCAL		(1 << 0)
#घोषणा GSC_OUT_PATH_MEMORY		(0 << 0)

/* G-Scaler scaled destination image size */
#घोषणा GSC_SCALED_SIZE			0x24
#घोषणा GSC_SCALED_HEIGHT(x)		((x) << 16)
#घोषणा GSC_SCALED_WIDTH(x)		((x) << 0)

/* G-Scaler pre scale ratio */
#घोषणा GSC_PRE_SCALE_RATIO		0x28
#घोषणा GSC_PRESC_SHFACTOR(x)		((x) << 28)
#घोषणा GSC_PRESC_V_RATIO(x)		((x) << 16)
#घोषणा GSC_PRESC_H_RATIO(x)		((x) << 0)

/* G-Scaler मुख्य scale horizontal ratio */
#घोषणा GSC_MAIN_H_RATIO		0x2c
#घोषणा GSC_MAIN_H_RATIO_VALUE(x)	((x) << 0)

/* G-Scaler मुख्य scale vertical ratio */
#घोषणा GSC_MAIN_V_RATIO		0x30
#घोषणा GSC_MAIN_V_RATIO_VALUE(x)	((x) << 0)

/* G-Scaler destination image size */
#घोषणा GSC_DSTIMG_SIZE			0x40
#घोषणा GSC_DSTIMG_HEIGHT(x)		((x) << 16)
#घोषणा GSC_DSTIMG_WIDTH(x)		((x) << 0)

/* G-Scaler destination image offset */
#घोषणा GSC_DSTIMG_OFFSET		0x44
#घोषणा GSC_DSTIMG_OFFSET_Y(x)		((x) << 16)
#घोषणा GSC_DSTIMG_OFFSET_X(x)		((x) << 0)

/* G-Scaler input y address mask */
#घोषणा GSC_IN_BASE_ADDR_Y_MASK		0x4c
/* G-Scaler input y base address */
#घोषणा GSC_IN_BASE_ADDR_Y(n)		(0x50 + (n) * 0x4)

/* G-Scaler input cb address mask */
#घोषणा GSC_IN_BASE_ADDR_CB_MASK	0x7c
/* G-Scaler input cb base address */
#घोषणा GSC_IN_BASE_ADDR_CB(n)		(0x80 + (n) * 0x4)

/* G-Scaler input cr address mask */
#घोषणा GSC_IN_BASE_ADDR_CR_MASK	0xac
/* G-Scaler input cr base address */
#घोषणा GSC_IN_BASE_ADDR_CR(n)		(0xb0 + (n) * 0x4)

/* G-Scaler output y address mask */
#घोषणा GSC_OUT_BASE_ADDR_Y_MASK	0x10c
/* G-Scaler output y base address */
#घोषणा GSC_OUT_BASE_ADDR_Y(n)		(0x110 + (n) * 0x4)

/* G-Scaler output cb address mask */
#घोषणा GSC_OUT_BASE_ADDR_CB_MASK	0x15c
/* G-Scaler output cb base address */
#घोषणा GSC_OUT_BASE_ADDR_CB(n)		(0x160 + (n) * 0x4)

/* G-Scaler output cr address mask */
#घोषणा GSC_OUT_BASE_ADDR_CR_MASK	0x1ac
/* G-Scaler output cr base address */
#घोषणा GSC_OUT_BASE_ADDR_CR(n)		(0x1b0 + (n) * 0x4)

#पूर्ण_अगर /* REGS_GSC_H_ */
