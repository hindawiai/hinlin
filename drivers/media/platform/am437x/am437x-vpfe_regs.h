<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI AM437x Image Sensor Interface Registers
 *
 * Copyright (C) 2013 - 2014 Texas Instruments, Inc.
 *
 * Benoit Parrot <bparrot@ti.com>
 * Lad, Prabhakar <prabhakar.csengg@gmail.com>
 */

#अगर_अघोषित AM437X_VPFE_REGS_H
#घोषणा AM437X_VPFE_REGS_H

/* VPFE module रेजिस्टर offset */
#घोषणा VPFE_REVISION				0x0
#घोषणा VPFE_PCR				0x4
#घोषणा VPFE_SYNMODE				0x8
#घोषणा VPFE_HD_VD_WID				0xc
#घोषणा VPFE_PIX_LINES				0x10
#घोषणा VPFE_HORZ_INFO				0x14
#घोषणा VPFE_VERT_START				0x18
#घोषणा VPFE_VERT_LINES				0x1c
#घोषणा VPFE_CULLING				0x20
#घोषणा VPFE_HSIZE_OFF				0x24
#घोषणा VPFE_SDOFST				0x28
#घोषणा VPFE_SDR_ADDR				0x2c
#घोषणा VPFE_CLAMP				0x30
#घोषणा VPFE_DCSUB				0x34
#घोषणा VPFE_COLPTN				0x38
#घोषणा VPFE_BLKCMP				0x3c
#घोषणा VPFE_VDINT				0x48
#घोषणा VPFE_ALAW				0x4c
#घोषणा VPFE_REC656IF				0x50
#घोषणा VPFE_CCDCFG				0x54
#घोषणा VPFE_DMA_CNTL				0x98
#घोषणा VPFE_SYSCONFIG				0x104
#घोषणा VPFE_CONFIG				0x108
#घोषणा VPFE_IRQ_EOI				0x110
#घोषणा VPFE_IRQ_STS_RAW			0x114
#घोषणा VPFE_IRQ_STS				0x118
#घोषणा VPFE_IRQ_EN_SET				0x11c
#घोषणा VPFE_IRQ_EN_CLR				0x120
#घोषणा VPFE_REG_END				0x124

/* Define bit fields within selected रेजिस्टरs */
#घोषणा VPFE_FID_POL_MASK			1
#घोषणा VPFE_FID_POL_SHIFT			4
#घोषणा VPFE_HD_POL_MASK			1
#घोषणा VPFE_HD_POL_SHIFT			3
#घोषणा VPFE_VD_POL_MASK			1
#घोषणा VPFE_VD_POL_SHIFT			2
#घोषणा VPFE_HSIZE_OFF_MASK			0xffffffe0
#घोषणा VPFE_32BYTE_ALIGN_VAL			31
#घोषणा VPFE_FRM_FMT_MASK			0x1
#घोषणा VPFE_FRM_FMT_SHIFT			7
#घोषणा VPFE_DATA_SZ_MASK			7
#घोषणा VPFE_DATA_SZ_SHIFT			8
#घोषणा VPFE_PIX_FMT_MASK			3
#घोषणा VPFE_PIX_FMT_SHIFT			12
#घोषणा VPFE_VP2SDR_DISABLE			0xfffbffff
#घोषणा VPFE_WEN_ENABLE				BIT(17)
#घोषणा VPFE_SDR2RSZ_DISABLE			0xfff7ffff
#घोषणा VPFE_VDHDEN_ENABLE			BIT(16)
#घोषणा VPFE_LPF_ENABLE				BIT(14)
#घोषणा VPFE_ALAW_ENABLE			BIT(3)
#घोषणा VPFE_ALAW_GAMMA_WD_MASK			7
#घोषणा VPFE_BLK_CLAMP_ENABLE			BIT(31)
#घोषणा VPFE_BLK_SGAIN_MASK			0x1f
#घोषणा VPFE_BLK_ST_PXL_MASK			0x7fff
#घोषणा VPFE_BLK_ST_PXL_SHIFT			10
#घोषणा VPFE_BLK_SAMPLE_LN_MASK			7
#घोषणा VPFE_BLK_SAMPLE_LN_SHIFT		28
#घोषणा VPFE_BLK_SAMPLE_LINE_MASK		7
#घोषणा VPFE_BLK_SAMPLE_LINE_SHIFT		25
#घोषणा VPFE_BLK_DC_SUB_MASK			0x03fff
#घोषणा VPFE_BLK_COMP_MASK			0xff
#घोषणा VPFE_BLK_COMP_GB_COMP_SHIFT		8
#घोषणा VPFE_BLK_COMP_GR_COMP_SHIFT		16
#घोषणा VPFE_BLK_COMP_R_COMP_SHIFT		24
#घोषणा VPFE_LATCH_ON_VSYNC_DISABLE		BIT(15)
#घोषणा VPFE_DATA_PACK_ENABLE			BIT(11)
#घोषणा VPFE_HORZ_INFO_SPH_SHIFT		16
#घोषणा VPFE_VERT_START_SLV0_SHIFT		16
#घोषणा VPFE_VDINT_VDINT0_SHIFT			16
#घोषणा VPFE_VDINT_VDINT1_MASK			0xffff
#घोषणा VPFE_PPC_RAW				1
#घोषणा VPFE_DCSUB_DEFAULT_VAL			0
#घोषणा VPFE_CLAMP_DEFAULT_VAL			0
#घोषणा VPFE_COLPTN_VAL				0xbb11bb11
#घोषणा VPFE_TWO_BYTES_PER_PIXEL		2
#घोषणा VPFE_INTERLACED_IMAGE_INVERT		0x4b6d
#घोषणा VPFE_INTERLACED_NO_IMAGE_INVERT		0x0249
#घोषणा VPFE_PROGRESSIVE_IMAGE_INVERT		0x4000
#घोषणा VPFE_PROGRESSIVE_NO_IMAGE_INVERT	0
#घोषणा VPFE_INTERLACED_HEIGHT_SHIFT		1
#घोषणा VPFE_SYN_MODE_INPMOD_SHIFT		12
#घोषणा VPFE_SYN_MODE_INPMOD_MASK		3
#घोषणा VPFE_SYN_MODE_8BITS			(7 << 8)
#घोषणा VPFE_SYN_MODE_10BITS			(6 << 8)
#घोषणा VPFE_SYN_MODE_11BITS			(5 << 8)
#घोषणा VPFE_SYN_MODE_12BITS			(4 << 8)
#घोषणा VPFE_SYN_MODE_13BITS			(3 << 8)
#घोषणा VPFE_SYN_MODE_14BITS			(2 << 8)
#घोषणा VPFE_SYN_MODE_15BITS			(1 << 8)
#घोषणा VPFE_SYN_MODE_16BITS			(0 << 8)
#घोषणा VPFE_SYN_FLDMODE_MASK			1
#घोषणा VPFE_SYN_FLDMODE_SHIFT			7
#घोषणा VPFE_REC656IF_BT656_EN			3
#घोषणा VPFE_SYN_MODE_VD_POL_NEGATIVE		BIT(2)
#घोषणा VPFE_CCDCFG_Y8POS_SHIFT			11
#घोषणा VPFE_CCDCFG_BW656_10BIT			BIT(5)
#घोषणा VPFE_SDOFST_FIELD_INTERLEAVED		0x249
#घोषणा VPFE_NO_CULLING				0xffff00ff
#घोषणा VPFE_VDINT0				BIT(0)
#घोषणा VPFE_VDINT1				BIT(1)
#घोषणा VPFE_VDINT2				BIT(2)
#घोषणा VPFE_DMA_CNTL_OVERFLOW			BIT(31)

#घोषणा VPFE_CONFIG_PCLK_INV_SHIFT		0
#घोषणा VPFE_CONFIG_PCLK_INV_MASK		1
#घोषणा VPFE_CONFIG_PCLK_INV_NOT_INV		0
#घोषणा VPFE_CONFIG_PCLK_INV_INV		1
#घोषणा VPFE_CONFIG_EN_SHIFT			1
#घोषणा VPFE_CONFIG_EN_MASK			2
#घोषणा VPFE_CONFIG_EN_DISABLE			0
#घोषणा VPFE_CONFIG_EN_ENABLE			1
#घोषणा VPFE_CONFIG_ST_SHIFT			2
#घोषणा VPFE_CONFIG_ST_MASK			4
#घोषणा VPFE_CONFIG_ST_OCP_ACTIVE		0
#घोषणा VPFE_CONFIG_ST_OCP_STANDBY		1

#पूर्ण_अगर		/* AM437X_VPFE_REGS_H */
