<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/gpu/drm/exynos/regs-gsc.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Register definition file क्रम Samsung G-Scaler driver
 */

#अगर_अघोषित EXYNOS_REGS_GSC_H_
#घोषणा EXYNOS_REGS_GSC_H_

/* G-Scaler enable */
#घोषणा GSC_ENABLE			0x00
#घोषणा GSC_ENABLE_PP_UPDATE_TIME_MASK	(1 << 9)
#घोषणा GSC_ENABLE_PP_UPDATE_TIME_CURR	(0 << 9)
#घोषणा GSC_ENABLE_PP_UPDATE_TIME_EOPAS	(1 << 9)
#घोषणा GSC_ENABLE_CLK_GATE_MODE_MASK	(1 << 8)
#घोषणा GSC_ENABLE_CLK_GATE_MODE_FREE	(1 << 8)
#घोषणा GSC_ENABLE_IPC_MODE_MASK	(1 << 7)
#घोषणा GSC_ENABLE_NORM_MODE		(0 << 7)
#घोषणा GSC_ENABLE_IPC_MODE		(1 << 7)
#घोषणा GSC_ENABLE_PP_UPDATE_MODE_MASK	(1 << 6)
#घोषणा GSC_ENABLE_PP_UPDATE_FIRE_MODE	(1 << 6)
#घोषणा GSC_ENABLE_IN_PP_UPDATE		(1 << 5)
#घोषणा GSC_ENABLE_ON_CLEAR_MASK	(1 << 4)
#घोषणा GSC_ENABLE_ON_CLEAR_ONESHOT	(1 << 4)
#घोषणा GSC_ENABLE_QOS_ENABLE		(1 << 3)
#घोषणा GSC_ENABLE_OP_STATUS		(1 << 2)
#घोषणा GSC_ENABLE_SFR_UPDATE		(1 << 1)
#घोषणा GSC_ENABLE_ON			(1 << 0)

/* G-Scaler S/W reset */
#घोषणा GSC_SW_RESET			0x04
#घोषणा GSC_SW_RESET_SRESET		(1 << 0)

/* G-Scaler IRQ */
#घोषणा GSC_IRQ				0x08
#घोषणा GSC_IRQ_STATUS_OR_IRQ		(1 << 17)
#घोषणा GSC_IRQ_STATUS_OR_FRM_DONE	(1 << 16)
#घोषणा GSC_IRQ_OR_MASK			(1 << 2)
#घोषणा GSC_IRQ_FRMDONE_MASK		(1 << 1)
#घोषणा GSC_IRQ_ENABLE			(1 << 0)

/* G-Scaler input control */
#घोषणा GSC_IN_CON			0x10
#घोषणा GSC_IN_CHROM_STRIDE_SEL_MASK	(1 << 20)
#घोषणा GSC_IN_CHROM_STRIDE_SEPAR	(1 << 20)
#घोषणा GSC_IN_RB_SWAP_MASK		(1 << 19)
#घोषणा GSC_IN_RB_SWAP			(1 << 19)
#घोषणा GSC_IN_ROT_MASK			(7 << 16)
#घोषणा GSC_IN_ROT_270			(7 << 16)
#घोषणा GSC_IN_ROT_90_YFLIP		(6 << 16)
#घोषणा GSC_IN_ROT_90_XFLIP		(5 << 16)
#घोषणा GSC_IN_ROT_90			(4 << 16)
#घोषणा GSC_IN_ROT_180			(3 << 16)
#घोषणा GSC_IN_ROT_YFLIP		(2 << 16)
#घोषणा GSC_IN_ROT_XFLIP		(1 << 16)
#घोषणा GSC_IN_RGB_TYPE_MASK		(3 << 14)
#घोषणा GSC_IN_RGB_HD_WIDE		(3 << 14)
#घोषणा GSC_IN_RGB_HD_NARROW		(2 << 14)
#घोषणा GSC_IN_RGB_SD_WIDE		(1 << 14)
#घोषणा GSC_IN_RGB_SD_NARROW		(0 << 14)
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
#घोषणा GSC_IN_TILE_C_16x16		(1 << 4)
#घोषणा GSC_IN_TILE_MODE		(1 << 3)
#घोषणा GSC_IN_LOCAL_SEL_MASK		(3 << 1)
#घोषणा GSC_IN_LOCAL_CAM3		(3 << 1)
#घोषणा GSC_IN_LOCAL_FIMD_WB		(2 << 1)
#घोषणा GSC_IN_LOCAL_CAM1		(1 << 1)
#घोषणा GSC_IN_LOCAL_CAM0		(0 << 1)
#घोषणा GSC_IN_PATH_MASK		(1 << 0)
#घोषणा GSC_IN_PATH_LOCAL		(1 << 0)
#घोषणा GSC_IN_PATH_MEMORY		(0 << 0)

/* G-Scaler source image size */
#घोषणा GSC_SRCIMG_SIZE			0x14
#घोषणा GSC_SRCIMG_HEIGHT_MASK		(0x1fff << 16)
#घोषणा GSC_SRCIMG_HEIGHT(x)		((x) << 16)
#घोषणा GSC_SRCIMG_WIDTH_MASK		(0x3fff << 0)
#घोषणा GSC_SRCIMG_WIDTH(x)		((x) << 0)

/* G-Scaler source image offset */
#घोषणा GSC_SRCIMG_OFFSET		0x18
#घोषणा GSC_SRCIMG_OFFSET_Y_MASK	(0x1fff << 16)
#घोषणा GSC_SRCIMG_OFFSET_Y(x)		((x) << 16)
#घोषणा GSC_SRCIMG_OFFSET_X_MASK	(0x1fff << 0)
#घोषणा GSC_SRCIMG_OFFSET_X(x)		((x) << 0)

/* G-Scaler cropped source image size */
#घोषणा GSC_CROPPED_SIZE		0x1C
#घोषणा GSC_CROPPED_HEIGHT_MASK		(0x1fff << 16)
#घोषणा GSC_CROPPED_HEIGHT(x)		((x) << 16)
#घोषणा GSC_CROPPED_WIDTH_MASK		(0x1fff << 0)
#घोषणा GSC_CROPPED_WIDTH(x)		((x) << 0)

/* G-Scaler output control */
#घोषणा GSC_OUT_CON			0x20
#घोषणा GSC_OUT_GLOBAL_ALPHA_MASK	(0xff << 24)
#घोषणा GSC_OUT_GLOBAL_ALPHA(x)		((x) << 24)
#घोषणा GSC_OUT_CHROM_STRIDE_SEL_MASK	(1 << 13)
#घोषणा GSC_OUT_CHROM_STRIDE_SEPAR	(1 << 13)
#घोषणा GSC_OUT_RB_SWAP_MASK		(1 << 12)
#घोषणा GSC_OUT_RB_SWAP			(1 << 12)
#घोषणा GSC_OUT_RGB_TYPE_MASK		(3 << 10)
#घोषणा GSC_OUT_RGB_HD_NARROW		(3 << 10)
#घोषणा GSC_OUT_RGB_HD_WIDE		(2 << 10)
#घोषणा GSC_OUT_RGB_SD_NARROW		(1 << 10)
#घोषणा GSC_OUT_RGB_SD_WIDE		(0 << 10)
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
#घोषणा GSC_OUT_YUV422_3P		(6 << 4)
#घोषणा GSC_OUT_YUV444			(7 << 4)
#घोषणा GSC_OUT_TILE_TYPE_MASK		(1 << 2)
#घोषणा GSC_OUT_TILE_C_16x8		(0 << 2)
#घोषणा GSC_OUT_TILE_C_16x16		(1 << 2)
#घोषणा GSC_OUT_TILE_MODE		(1 << 1)
#घोषणा GSC_OUT_PATH_MASK		(1 << 0)
#घोषणा GSC_OUT_PATH_LOCAL		(1 << 0)
#घोषणा GSC_OUT_PATH_MEMORY		(0 << 0)

/* G-Scaler scaled destination image size */
#घोषणा GSC_SCALED_SIZE			0x24
#घोषणा GSC_SCALED_HEIGHT_MASK		(0x1fff << 16)
#घोषणा GSC_SCALED_HEIGHT(x)		((x) << 16)
#घोषणा GSC_SCALED_WIDTH_MASK		(0x1fff << 0)
#घोषणा GSC_SCALED_WIDTH(x)		((x) << 0)

/* G-Scaler pre scale ratio */
#घोषणा GSC_PRE_SCALE_RATIO		0x28
#घोषणा GSC_PRESC_SHFACTOR_MASK		(7 << 28)
#घोषणा GSC_PRESC_SHFACTOR(x)		((x) << 28)
#घोषणा GSC_PRESC_V_RATIO_MASK		(7 << 16)
#घोषणा GSC_PRESC_V_RATIO(x)		((x) << 16)
#घोषणा GSC_PRESC_H_RATIO_MASK		(7 << 0)
#घोषणा GSC_PRESC_H_RATIO(x)		((x) << 0)

/* G-Scaler मुख्य scale horizontal ratio */
#घोषणा GSC_MAIN_H_RATIO		0x2C
#घोषणा GSC_MAIN_H_RATIO_MASK		(0xfffff << 0)
#घोषणा GSC_MAIN_H_RATIO_VALUE(x)	((x) << 0)

/* G-Scaler मुख्य scale vertical ratio */
#घोषणा GSC_MAIN_V_RATIO		0x30
#घोषणा GSC_MAIN_V_RATIO_MASK		(0xfffff << 0)
#घोषणा GSC_MAIN_V_RATIO_VALUE(x)	((x) << 0)

/* G-Scaler input chrominance stride */
#घोषणा GSC_IN_CHROM_STRIDE		0x3C
#घोषणा GSC_IN_CHROM_STRIDE_MASK	(0x3fff << 0)
#घोषणा GSC_IN_CHROM_STRIDE_VALUE(x)	((x) << 0)

/* G-Scaler destination image size */
#घोषणा GSC_DSTIMG_SIZE			0x40
#घोषणा GSC_DSTIMG_HEIGHT_MASK		(0x1fff << 16)
#घोषणा GSC_DSTIMG_HEIGHT(x)		((x) << 16)
#घोषणा GSC_DSTIMG_WIDTH_MASK		(0x1fff << 0)
#घोषणा GSC_DSTIMG_WIDTH(x)		((x) << 0)

/* G-Scaler destination image offset */
#घोषणा GSC_DSTIMG_OFFSET		0x44
#घोषणा GSC_DSTIMG_OFFSET_Y_MASK	(0x1fff << 16)
#घोषणा GSC_DSTIMG_OFFSET_Y(x)		((x) << 16)
#घोषणा GSC_DSTIMG_OFFSET_X_MASK	(0x1fff << 0)
#घोषणा GSC_DSTIMG_OFFSET_X(x)		((x) << 0)

/* G-Scaler output chrominance stride */
#घोषणा GSC_OUT_CHROM_STRIDE		0x48
#घोषणा GSC_OUT_CHROM_STRIDE_MASK	(0x3fff << 0)
#घोषणा GSC_OUT_CHROM_STRIDE_VALUE(x)	((x) << 0)

/* G-Scaler input y address mask */
#घोषणा GSC_IN_BASE_ADDR_Y_MASK		0x4C
/* G-Scaler input y base address */
#घोषणा GSC_IN_BASE_ADDR_Y(n)		(0x50 + (n) * 0x4)
/* G-Scaler input y base current address */
#घोषणा GSC_IN_BASE_ADDR_Y_CUR(n)	(0x60 + (n) * 0x4)

/* G-Scaler input cb address mask */
#घोषणा GSC_IN_BASE_ADDR_CB_MASK	0x7C
/* G-Scaler input cb base address */
#घोषणा GSC_IN_BASE_ADDR_CB(n)		(0x80 + (n) * 0x4)
/* G-Scaler input cb base current address */
#घोषणा GSC_IN_BASE_ADDR_CB_CUR(n)	(0x90 + (n) * 0x4)

/* G-Scaler input cr address mask */
#घोषणा GSC_IN_BASE_ADDR_CR_MASK	0xAC
/* G-Scaler input cr base address */
#घोषणा GSC_IN_BASE_ADDR_CR(n)		(0xB0 + (n) * 0x4)
/* G-Scaler input cr base current address */
#घोषणा GSC_IN_BASE_ADDR_CR_CUR(n)	(0xC0 + (n) * 0x4)

/* G-Scaler input address mask */
#घोषणा GSC_IN_CURR_ADDR_INDEX	(0xf << 24)
#घोषणा GSC_IN_CURR_GET_INDEX(x)	((x) >> 24)
#घोषणा GSC_IN_BASE_ADDR_PINGPONG(x)	((x) << 16)
#घोषणा GSC_IN_BASE_ADDR_MASK		(0xff << 0)

/* G-Scaler output y address mask */
#घोषणा GSC_OUT_BASE_ADDR_Y_MASK	0x10C
/* G-Scaler output y base address */
#घोषणा GSC_OUT_BASE_ADDR_Y(n)		(0x110 + (n) * 0x4)

/* G-Scaler output cb address mask */
#घोषणा GSC_OUT_BASE_ADDR_CB_MASK	0x15C
/* G-Scaler output cb base address */
#घोषणा GSC_OUT_BASE_ADDR_CB(n)		(0x160 + (n) * 0x4)

/* G-Scaler output cr address mask */
#घोषणा GSC_OUT_BASE_ADDR_CR_MASK	0x1AC
/* G-Scaler output cr base address */
#घोषणा GSC_OUT_BASE_ADDR_CR(n)		(0x1B0 + (n) * 0x4)

/* G-Scaler output address mask */
#घोषणा GSC_OUT_CURR_ADDR_INDEX		(0xf << 24)
#घोषणा GSC_OUT_CURR_GET_INDEX(x)	((x) >> 24)
#घोषणा GSC_OUT_BASE_ADDR_PINGPONG(x)	((x) << 16)
#घोषणा GSC_OUT_BASE_ADDR_MASK		(0xffff << 0)

/* G-Scaler horizontal scaling filter */
#घोषणा GSC_HCOEF(n, s, x)	(0x300 + (n) * 0x4 + (s) * 0x30 + (x) * 0x300)

/* G-Scaler vertical scaling filter */
#घोषणा GSC_VCOEF(n, s, x)	(0x200 + (n) * 0x4 + (s) * 0x30 + (x) * 0x300)

/* G-Scaler BUS control */
#घोषणा GSC_BUSCON			0xA78
#घोषणा GSC_BUSCON_INT_TIME_MASK	(1 << 8)
#घोषणा GSC_BUSCON_INT_DATA_TRANS	(0 << 8)
#घोषणा GSC_BUSCON_INT_AXI_RESPONSE	(1 << 8)
#घोषणा GSC_BUSCON_AWCACHE(x)		((x) << 4)
#घोषणा GSC_BUSCON_ARCACHE(x)		((x) << 0)

/* G-Scaler V position */
#घोषणा GSC_VPOSITION			0xA7C
#घोषणा GSC_VPOS_F(x)			((x) << 0)


/* G-Scaler घड़ी initial count */
#घोषणा GSC_CLK_INIT_COUNT		0xC00
#घोषणा GSC_CLK_GATE_MODE_INIT_CNT(x)	((x) << 0)

/* G-Scaler घड़ी snoop count */
#घोषणा GSC_CLK_SNOOP_COUNT		0xC04
#घोषणा GSC_CLK_GATE_MODE_SNOOP_CNT(x)	((x) << 0)

/* SYSCON. GSCBLK_CFG */
#घोषणा SYSREG_GSCBLK_CFG1		0x0224
#घोषणा GSC_BLK_DISP1WB_DEST(x)		(x << 10)
#घोषणा GSC_BLK_SW_RESET_WB_DEST(x)	(1 << (18 + x))
#घोषणा GSC_BLK_PXLASYNC_LO_MASK_WB(x)	(0 << (14 + x))
#घोषणा GSC_BLK_GSCL_WB_IN_SRC_SEL(x)	(1 << (2 * x))
#घोषणा SYSREG_GSCBLK_CFG2		0x2000
#घोषणा PXLASYNC_LO_MASK_CAMIF_GSCL(x)	(1 << (x))

#पूर्ण_अगर /* EXYNOS_REGS_GSC_H_ */
