<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006-2009 Texas Instruments Inc
 */
#अगर_अघोषित _DM644X_CCDC_REGS_H
#घोषणा _DM644X_CCDC_REGS_H

/**************************************************************************\
* Register OFFSET Definitions
\**************************************************************************/
#घोषणा CCDC_PID				0x0
#घोषणा CCDC_PCR				0x4
#घोषणा CCDC_SYN_MODE				0x8
#घोषणा CCDC_HD_VD_WID				0xc
#घोषणा CCDC_PIX_LINES				0x10
#घोषणा CCDC_HORZ_INFO				0x14
#घोषणा CCDC_VERT_START				0x18
#घोषणा CCDC_VERT_LINES				0x1c
#घोषणा CCDC_CULLING				0x20
#घोषणा CCDC_HSIZE_OFF				0x24
#घोषणा CCDC_SDOFST				0x28
#घोषणा CCDC_SDR_ADDR				0x2c
#घोषणा CCDC_CLAMP				0x30
#घोषणा CCDC_DCSUB				0x34
#घोषणा CCDC_COLPTN				0x38
#घोषणा CCDC_BLKCMP				0x3c
#घोषणा CCDC_FPC				0x40
#घोषणा CCDC_FPC_ADDR				0x44
#घोषणा CCDC_VDINT				0x48
#घोषणा CCDC_ALAW				0x4c
#घोषणा CCDC_REC656IF				0x50
#घोषणा CCDC_CCDCFG				0x54
#घोषणा CCDC_FMTCFG				0x58
#घोषणा CCDC_FMT_HORZ				0x5c
#घोषणा CCDC_FMT_VERT				0x60
#घोषणा CCDC_FMT_ADDR0				0x64
#घोषणा CCDC_FMT_ADDR1				0x68
#घोषणा CCDC_FMT_ADDR2				0x6c
#घोषणा CCDC_FMT_ADDR3				0x70
#घोषणा CCDC_FMT_ADDR4				0x74
#घोषणा CCDC_FMT_ADDR5				0x78
#घोषणा CCDC_FMT_ADDR6				0x7c
#घोषणा CCDC_FMT_ADDR7				0x80
#घोषणा CCDC_PRGEVEN_0				0x84
#घोषणा CCDC_PRGEVEN_1				0x88
#घोषणा CCDC_PRGODD_0				0x8c
#घोषणा CCDC_PRGODD_1				0x90
#घोषणा CCDC_VP_OUT				0x94
#घोषणा CCDC_REG_END				0x98

/***************************************************************
*	Define क्रम various रेजिस्टर bit mask and shअगरts क्रम CCDC
****************************************************************/
#घोषणा CCDC_FID_POL_MASK			1
#घोषणा CCDC_FID_POL_SHIFT			4
#घोषणा CCDC_HD_POL_MASK			1
#घोषणा CCDC_HD_POL_SHIFT			3
#घोषणा CCDC_VD_POL_MASK			1
#घोषणा CCDC_VD_POL_SHIFT			2
#घोषणा CCDC_HSIZE_OFF_MASK			0xffffffe0
#घोषणा CCDC_32BYTE_ALIGN_VAL			31
#घोषणा CCDC_FRM_FMT_MASK			0x1
#घोषणा CCDC_FRM_FMT_SHIFT			7
#घोषणा CCDC_DATA_SZ_MASK			7
#घोषणा CCDC_DATA_SZ_SHIFT			8
#घोषणा CCDC_PIX_FMT_MASK			3
#घोषणा CCDC_PIX_FMT_SHIFT			12
#घोषणा CCDC_VP2SDR_DISABLE			0xFFFBFFFF
#घोषणा CCDC_WEN_ENABLE				BIT(17)
#घोषणा CCDC_SDR2RSZ_DISABLE			0xFFF7FFFF
#घोषणा CCDC_VDHDEN_ENABLE			BIT(16)
#घोषणा CCDC_LPF_ENABLE				BIT(14)
#घोषणा CCDC_ALAW_ENABLE			BIT(3)
#घोषणा CCDC_ALAW_GAMMA_WD_MASK			7
#घोषणा CCDC_BLK_CLAMP_ENABLE			BIT(31)
#घोषणा CCDC_BLK_SGAIN_MASK			0x1F
#घोषणा CCDC_BLK_ST_PXL_MASK			0x7FFF
#घोषणा CCDC_BLK_ST_PXL_SHIFT			10
#घोषणा CCDC_BLK_SAMPLE_LN_MASK			7
#घोषणा CCDC_BLK_SAMPLE_LN_SHIFT		28
#घोषणा CCDC_BLK_SAMPLE_LINE_MASK		7
#घोषणा CCDC_BLK_SAMPLE_LINE_SHIFT		25
#घोषणा CCDC_BLK_DC_SUB_MASK			0x03FFF
#घोषणा CCDC_BLK_COMP_MASK			0xFF
#घोषणा CCDC_BLK_COMP_GB_COMP_SHIFT		8
#घोषणा CCDC_BLK_COMP_GR_COMP_SHIFT		16
#घोषणा CCDC_BLK_COMP_R_COMP_SHIFT		24
#घोषणा CCDC_LATCH_ON_VSYNC_DISABLE		BIT(15)
#घोषणा CCDC_FPC_ENABLE				BIT(15)
#घोषणा CCDC_FPC_DISABLE			0
#घोषणा CCDC_FPC_FPC_NUM_MASK			0x7FFF
#घोषणा CCDC_DATA_PACK_ENABLE			BIT(11)
#घोषणा CCDC_FMTCFG_VPIN_MASK			7
#घोषणा CCDC_FMTCFG_VPIN_SHIFT			12
#घोषणा CCDC_FMT_HORZ_FMTLNH_MASK		0x1FFF
#घोषणा CCDC_FMT_HORZ_FMTSPH_MASK		0x1FFF
#घोषणा CCDC_FMT_HORZ_FMTSPH_SHIFT		16
#घोषणा CCDC_FMT_VERT_FMTLNV_MASK		0x1FFF
#घोषणा CCDC_FMT_VERT_FMTSLV_MASK		0x1FFF
#घोषणा CCDC_FMT_VERT_FMTSLV_SHIFT		16
#घोषणा CCDC_VP_OUT_VERT_NUM_MASK		0x3FFF
#घोषणा CCDC_VP_OUT_VERT_NUM_SHIFT		17
#घोषणा CCDC_VP_OUT_HORZ_NUM_MASK		0x1FFF
#घोषणा CCDC_VP_OUT_HORZ_NUM_SHIFT		4
#घोषणा CCDC_VP_OUT_HORZ_ST_MASK		0xF
#घोषणा CCDC_HORZ_INFO_SPH_SHIFT		16
#घोषणा CCDC_VERT_START_SLV0_SHIFT		16
#घोषणा CCDC_VDINT_VDINT0_SHIFT			16
#घोषणा CCDC_VDINT_VDINT1_MASK			0xFFFF
#घोषणा CCDC_PPC_RAW				1
#घोषणा CCDC_DCSUB_DEFAULT_VAL			0
#घोषणा CCDC_CLAMP_DEFAULT_VAL			0
#घोषणा CCDC_ENABLE_VIDEO_PORT			0x8000
#घोषणा CCDC_DISABLE_VIDEO_PORT			0
#घोषणा CCDC_COLPTN_VAL				0xBB11BB11
#घोषणा CCDC_TWO_BYTES_PER_PIXEL		2
#घोषणा CCDC_INTERLACED_IMAGE_INVERT		0x4B6D
#घोषणा CCDC_INTERLACED_NO_IMAGE_INVERT		0x0249
#घोषणा CCDC_PROGRESSIVE_IMAGE_INVERT		0x4000
#घोषणा CCDC_PROGRESSIVE_NO_IMAGE_INVERT	0
#घोषणा CCDC_INTERLACED_HEIGHT_SHIFT		1
#घोषणा CCDC_SYN_MODE_INPMOD_SHIFT		12
#घोषणा CCDC_SYN_MODE_INPMOD_MASK		3
#घोषणा CCDC_SYN_MODE_8BITS			(7 << 8)
#घोषणा CCDC_SYN_MODE_10BITS			(6 << 8)
#घोषणा CCDC_SYN_MODE_11BITS			(5 << 8)
#घोषणा CCDC_SYN_MODE_12BITS			(4 << 8)
#घोषणा CCDC_SYN_MODE_13BITS			(3 << 8)
#घोषणा CCDC_SYN_MODE_14BITS			(2 << 8)
#घोषणा CCDC_SYN_MODE_15BITS			(1 << 8)
#घोषणा CCDC_SYN_MODE_16BITS			(0 << 8)
#घोषणा CCDC_SYN_FLDMODE_MASK			1
#घोषणा CCDC_SYN_FLDMODE_SHIFT			7
#घोषणा CCDC_REC656IF_BT656_EN			3
#घोषणा CCDC_SYN_MODE_VD_POL_NEGATIVE		BIT(2)
#घोषणा CCDC_CCDCFG_Y8POS_SHIFT			11
#घोषणा CCDC_CCDCFG_BW656_10BIT			BIT(5)
#घोषणा CCDC_SDOFST_FIELD_INTERLEAVED		0x249
#घोषणा CCDC_NO_CULLING				0xffff00ff
#पूर्ण_अगर
