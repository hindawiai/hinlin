<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 */

#अगर_अघोषित __KIRIN_ADE_REG_H__
#घोषणा __KIRIN_ADE_REG_H__

/*
 * ADE Registers
 */
#घोषणा MASK(x)				(BIT(x) - 1)

#घोषणा ADE_CTRL			0x0004
#घोषणा FRM_END_START_OFST		0
#घोषणा FRM_END_START_MASK		MASK(2)
#घोषणा AUTO_CLK_GATE_EN_OFST		0
#घोषणा AUTO_CLK_GATE_EN		BIT(0)
#घोषणा ADE_DISP_SRC_CFG		0x0018
#घोषणा ADE_CTRL1			0x008C
#घोषणा ADE_EN				0x0100
#घोषणा ADE_DISABLE			0
#घोषणा ADE_ENABLE			1
/* reset and reload regs */
#घोषणा ADE_SOFT_RST_SEL(x)		(0x0078 + (x) * 0x4)
#घोषणा ADE_RELOAD_DIS(x)		(0x00AC + (x) * 0x4)
#घोषणा RDMA_OFST			0
#घोषणा CLIP_OFST			15
#घोषणा SCL_OFST			21
#घोषणा CTRAN_OFST			24
#घोषणा OVLY_OFST			37 /* 32+5 */
/* channel regs */
#घोषणा RD_CH_CTRL(x)			(0x1004 + (x) * 0x80)
#घोषणा RD_CH_ADDR(x)			(0x1008 + (x) * 0x80)
#घोषणा RD_CH_SIZE(x)			(0x100C + (x) * 0x80)
#घोषणा RD_CH_STRIDE(x)			(0x1010 + (x) * 0x80)
#घोषणा RD_CH_SPACE(x)			(0x1014 + (x) * 0x80)
#घोषणा RD_CH_EN(x)			(0x1020 + (x) * 0x80)
/* overlay regs */
#घोषणा ADE_OVLY1_TRANS_CFG		0x002C
#घोषणा ADE_OVLY_CTL			0x0098
#घोषणा ADE_OVLY_CH_XY0(x)		(0x2004 + (x) * 4)
#घोषणा ADE_OVLY_CH_XY1(x)		(0x2024 + (x) * 4)
#घोषणा ADE_OVLY_CH_CTL(x)		(0x204C + (x) * 4)
#घोषणा ADE_OVLY_OUTPUT_SIZE(x)		(0x2070 + (x) * 8)
#घोषणा OUTPUT_XSIZE_OFST		16
#घोषणा ADE_OVLYX_CTL(x)		(0x209C + (x) * 4)
#घोषणा CH_OVLY_SEL_OFST(x)		((x) * 4)
#घोषणा CH_OVLY_SEL_MASK		MASK(2)
#घोषणा CH_OVLY_SEL_VAL(x)		((x) + 1)
#घोषणा CH_ALP_MODE_OFST		0
#घोषणा CH_ALP_SEL_OFST			2
#घोषणा CH_UNDER_ALP_SEL_OFST		4
#घोषणा CH_EN_OFST			6
#घोषणा CH_ALP_GBL_OFST			15
#घोषणा CH_SEL_OFST			28
/* ctran regs */
#घोषणा ADE_CTRAN_DIS(x)		(0x5004 + (x) * 0x100)
#घोषणा CTRAN_BYPASS_ON			1
#घोषणा CTRAN_BYPASS_OFF		0
#घोषणा ADE_CTRAN_IMAGE_SIZE(x)		(0x503C + (x) * 0x100)
/* clip regs */
#घोषणा ADE_CLIP_DISABLE(x)		(0x6800 + (x) * 0x100)
#घोषणा ADE_CLIP_SIZE0(x)		(0x6804 + (x) * 0x100)
#घोषणा ADE_CLIP_SIZE1(x)		(0x6808 + (x) * 0x100)

/*
 * LDI Registers
 */
#घोषणा LDI_HRZ_CTRL0			0x7400
#घोषणा HBP_OFST			20
#घोषणा LDI_HRZ_CTRL1			0x7404
#घोषणा LDI_VRT_CTRL0			0x7408
#घोषणा VBP_OFST			20
#घोषणा LDI_VRT_CTRL1			0x740C
#घोषणा LDI_PLR_CTRL			0x7410
#घोषणा FLAG_NVSYNC			BIT(0)
#घोषणा FLAG_NHSYNC			BIT(1)
#घोषणा FLAG_NPIXCLK			BIT(2)
#घोषणा FLAG_NDE			BIT(3)
#घोषणा LDI_DSP_SIZE			0x7414
#घोषणा VSIZE_OFST			20
#घोषणा LDI_INT_EN			0x741C
#घोषणा FRAME_END_INT_EN_OFST		1
#घोषणा LDI_CTRL			0x7420
#घोषणा BPP_OFST			3
#घोषणा DATA_GATE_EN			BIT(2)
#घोषणा LDI_EN				BIT(0)
#घोषणा LDI_MSK_INT			0x7428
#घोषणा LDI_INT_CLR			0x742C
#घोषणा LDI_WORK_MODE			0x7430
#घोषणा LDI_HDMI_DSI_GT			0x7434

/*
 * ADE media bus service regs
 */
#घोषणा ADE0_QOSGENERATOR_MODE		0x010C
#घोषणा QOSGENERATOR_MODE_MASK		MASK(2)
#घोषणा ADE0_QOSGENERATOR_EXTCONTROL	0x0118
#घोषणा SOCKET_QOS_EN			BIT(0)
#घोषणा ADE1_QOSGENERATOR_MODE		0x020C
#घोषणा ADE1_QOSGENERATOR_EXTCONTROL	0x0218

/*
 * ADE regs relevant क्रमागतs
 */
क्रमागत frame_end_start अणु
	/* regs take effect in every vsync */
	REG_EFFECTIVE_IN_VSYNC = 0,
	/* regs take effect in fist ade en and every frame end */
	REG_EFFECTIVE_IN_ADEEN_FRMEND,
	/* regs take effect in ade en immediately */
	REG_EFFECTIVE_IN_ADEEN,
	/* regs take effect in first vsync and every frame end */
	REG_EFFECTIVE_IN_VSYNC_FRMEND
पूर्ण;

क्रमागत ade_fb_क्रमmat अणु
	ADE_RGB_565 = 0,
	ADE_BGR_565,
	ADE_XRGB_8888,
	ADE_XBGR_8888,
	ADE_ARGB_8888,
	ADE_ABGR_8888,
	ADE_RGBA_8888,
	ADE_BGRA_8888,
	ADE_RGB_888,
	ADE_BGR_888 = 9,
	ADE_FORMAT_UNSUPPORT = 800
पूर्ण;

क्रमागत ade_channel अणु
	ADE_CH1 = 0,	/* channel 1 क्रम primary plane */
	ADE_CH_NUM
पूर्ण;

क्रमागत ade_scale अणु
	ADE_SCL1 = 0,
	ADE_SCL2,
	ADE_SCL3,
	ADE_SCL_NUM
पूर्ण;

क्रमागत ade_ctran अणु
	ADE_CTRAN1 = 0,
	ADE_CTRAN2,
	ADE_CTRAN3,
	ADE_CTRAN4,
	ADE_CTRAN5,
	ADE_CTRAN6,
	ADE_CTRAN_NUM
पूर्ण;

क्रमागत ade_overlay अणु
	ADE_OVLY1 = 0,
	ADE_OVLY2,
	ADE_OVLY3,
	ADE_OVLY_NUM
पूर्ण;

क्रमागत ade_alpha_mode अणु
	ADE_ALP_GLOBAL = 0,
	ADE_ALP_PIXEL,
	ADE_ALP_PIXEL_AND_GLB
पूर्ण;

क्रमागत ade_alpha_blending_mode अणु
	ADE_ALP_MUL_COEFF_0 = 0,	/* alpha */
	ADE_ALP_MUL_COEFF_1,		/* 1-alpha */
	ADE_ALP_MUL_COEFF_2,		/* 0 */
	ADE_ALP_MUL_COEFF_3		/* 1 */
पूर्ण;

/*
 * LDI regs relevant क्रमागतs
 */
क्रमागत dsi_pclk_en अणु
	DSI_PCLK_ON = 0,
	DSI_PCLK_OFF
पूर्ण;

क्रमागत ldi_output_क्रमmat अणु
	LDI_OUT_RGB_565 = 0,
	LDI_OUT_RGB_666,
	LDI_OUT_RGB_888
पूर्ण;

क्रमागत ldi_work_mode अणु
	TEST_MODE = 0,
	NORMAL_MODE
पूर्ण;

क्रमागत ldi_input_source अणु
	DISP_SRC_NONE = 0,
	DISP_SRC_OVLY2,
	DISP_SRC_DISP,
	DISP_SRC_ROT,
	DISP_SRC_SCL2
पूर्ण;

/*
 * ADE media bus service relevant क्रमागतs
 */
क्रमागत qos_generator_mode अणु
	FIXED_MODE = 0,
	LIMITER_MODE,
	BYPASS_MODE,
	REGULATOR_MODE
पूर्ण;

/*
 * Register Write/Read Helper functions
 */
अटल अंतरभूत व्योम ade_update_bits(व्योम __iomem *addr, u32 bit_start,
				   u32 mask, u32 val)
अणु
	u32 पंचांगp, orig;

	orig = पढ़ोl(addr);
	पंचांगp = orig & ~(mask << bit_start);
	पंचांगp |= (val & mask) << bit_start;
	ग_लिखोl(पंचांगp, addr);
पूर्ण

#पूर्ण_अगर
