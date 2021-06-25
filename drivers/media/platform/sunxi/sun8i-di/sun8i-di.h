<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Allwinner Deपूर्णांकerlace driver
 *
 * Copyright (C) 2019 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#अगर_अघोषित _SUN8I_DEINTERLACE_H_
#घोषणा _SUN8I_DEINTERLACE_H_

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <linux/platक्रमm_device.h>

#घोषणा DEINTERLACE_NAME		"sun8i-di"

#घोषणा DEINTERLACE_MOD_ENABLE			0x00
#घोषणा DEINTERLACE_MOD_ENABLE_EN			BIT(0)

#घोषणा DEINTERLACE_FRM_CTRL			0x04
#घोषणा DEINTERLACE_FRM_CTRL_REG_READY			BIT(0)
#घोषणा DEINTERLACE_FRM_CTRL_WB_EN			BIT(2)
#घोषणा DEINTERLACE_FRM_CTRL_OUT_CTRL			BIT(11)
#घोषणा DEINTERLACE_FRM_CTRL_START			BIT(16)
#घोषणा DEINTERLACE_FRM_CTRL_COEF_ACCESS		BIT(23)

#घोषणा DEINTERLACE_BYPASS			0x08
#घोषणा DEINTERLACE_BYPASS_CSC				BIT(1)

#घोषणा DEINTERLACE_AGTH_SEL			0x0c
#घोषणा DEINTERLACE_AGTH_SEL_LINEBUF			BIT(8)

#घोषणा DEINTERLACE_LINT_CTRL			0x10
#घोषणा DEINTERLACE_TRD_PRELUMA			0x1c
#घोषणा DEINTERLACE_BUF_ADDR0			0x20
#घोषणा DEINTERLACE_BUF_ADDR1			0x24
#घोषणा DEINTERLACE_BUF_ADDR2			0x28

#घोषणा DEINTERLACE_FIELD_CTRL			0x2c
#घोषणा DEINTERLACE_FIELD_CTRL_FIELD_CNT(v)		((v) & 0xff)
#घोषणा DEINTERLACE_FIELD_CTRL_FIELD_CNT_MSK		(0xff)

#घोषणा DEINTERLACE_TB_OFFSET0			0x30
#घोषणा DEINTERLACE_TB_OFFSET1			0x34
#घोषणा DEINTERLACE_TB_OFFSET2			0x38
#घोषणा DEINTERLACE_TRD_PRECHROMA		0x3c
#घोषणा DEINTERLACE_LINE_STRIDE0		0x40
#घोषणा DEINTERLACE_LINE_STRIDE1		0x44
#घोषणा DEINTERLACE_LINE_STRIDE2		0x48

#घोषणा DEINTERLACE_IN_FMT			0x4c
#घोषणा DEINTERLACE_IN_FMT_PS(v)			((v) & 3)
#घोषणा DEINTERLACE_IN_FMT_FMT(v)			(((v) & 7) << 4)
#घोषणा DEINTERLACE_IN_FMT_MOD(v)			(((v) & 7) << 8)

#घोषणा DEINTERLACE_WB_ADDR0			0x50
#घोषणा DEINTERLACE_WB_ADDR1			0x54
#घोषणा DEINTERLACE_WB_ADDR2			0x58

#घोषणा DEINTERLACE_OUT_FMT			0x5c
#घोषणा DEINTERLACE_OUT_FMT_FMT(v)			((v) & 0xf)
#घोषणा DEINTERLACE_OUT_FMT_PS(v)			(((v) & 3) << 5)

#घोषणा DEINTERLACE_INT_ENABLE			0x60
#घोषणा DEINTERLACE_INT_ENABLE_WB_EN			BIT(7)

#घोषणा DEINTERLACE_INT_STATUS			0x64
#घोषणा DEINTERLACE_INT_STATUS_WRITEBACK		BIT(7)

#घोषणा DEINTERLACE_STATUS			0x68
#घोषणा DEINTERLACE_STATUS_COEF_STATUS			BIT(11)
#घोषणा DEINTERLACE_STATUS_WB_ERROR			BIT(12)

#घोषणा DEINTERLACE_CSC_COEF			0x70 /* 12 रेजिस्टरs */

#घोषणा DEINTERLACE_CTRL			0xa0
#घोषणा DEINTERLACE_CTRL_EN				BIT(0)
#घोषणा DEINTERLACE_CTRL_FLAG_OUT_EN			BIT(8)
#घोषणा DEINTERLACE_CTRL_MODE_PASSTROUGH		(0 << 16)
#घोषणा DEINTERLACE_CTRL_MODE_WEAVE			(1 << 16)
#घोषणा DEINTERLACE_CTRL_MODE_BOB			(2 << 16)
#घोषणा DEINTERLACE_CTRL_MODE_MIXED			(3 << 16)
#घोषणा DEINTERLACE_CTRL_DIAG_INTP_EN			BIT(24)
#घोषणा DEINTERLACE_CTRL_TEMP_DIFF_EN			BIT(25)

#घोषणा DEINTERLACE_DIAG_INTP			0xa4
#घोषणा DEINTERLACE_DIAG_INTP_TH0(v)			((v) & 0x7f)
#घोषणा DEINTERLACE_DIAG_INTP_TH0_MSK			(0x7f)
#घोषणा DEINTERLACE_DIAG_INTP_TH1(v)			(((v) & 0x7f) << 8)
#घोषणा DEINTERLACE_DIAG_INTP_TH1_MSK			(0x7f << 8)
#घोषणा DEINTERLACE_DIAG_INTP_TH3(v)			(((v) & 0xff) << 24)
#घोषणा DEINTERLACE_DIAG_INTP_TH3_MSK			(0xff << 24)

#घोषणा DEINTERLACE_TEMP_DIFF			0xa8
#घोषणा DEINTERLACE_TEMP_DIFF_SAD_CENTRAL_TH(v)		((v) & 0x7f)
#घोषणा DEINTERLACE_TEMP_DIFF_SAD_CENTRAL_TH_MSK	(0x7f)
#घोषणा DEINTERLACE_TEMP_DIFF_AMBIGUITY_TH(v)		(((v) & 0x7f) << 8)
#घोषणा DEINTERLACE_TEMP_DIFF_AMBIGUITY_TH_MSK		(0x7f << 8)
#घोषणा DEINTERLACE_TEMP_DIFF_सूचीECT_DITHER_TH(v)	(((v) & 0x7ff) << 16)
#घोषणा DEINTERLACE_TEMP_DIFF_सूचीECT_DITHER_TH_MSK	(0x7ff << 16)

#घोषणा DEINTERLACE_LUMA_TH			0xac
#घोषणा DEINTERLACE_LUMA_TH_MIN_LUMA(v)			((v) & 0xff)
#घोषणा DEINTERLACE_LUMA_TH_MIN_LUMA_MSK		(0xff)
#घोषणा DEINTERLACE_LUMA_TH_MAX_LUMA(v)			(((v) & 0xff) << 8)
#घोषणा DEINTERLACE_LUMA_TH_MAX_LUMA_MSK		(0xff << 8)
#घोषणा DEINTERLACE_LUMA_TH_AVG_LUMA_SHIFT(v)		(((v) & 0xff) << 16)
#घोषणा DEINTERLACE_LUMA_TH_AVG_LUMA_SHIFT_MSK		(0xff << 16)
#घोषणा DEINTERLACE_LUMA_TH_PIXEL_STATIC(v)		(((v) & 3) << 24)
#घोषणा DEINTERLACE_LUMA_TH_PIXEL_STATIC_MSK		(3 << 24)

#घोषणा DEINTERLACE_SPAT_COMP			0xb0
#घोषणा DEINTERLACE_SPAT_COMP_TH2(v)			((v) & 0xff)
#घोषणा DEINTERLACE_SPAT_COMP_TH2_MSK			(0xff)
#घोषणा DEINTERLACE_SPAT_COMP_TH3(v)			(((v) & 0xff) << 16)
#घोषणा DEINTERLACE_SPAT_COMP_TH3_MSK			(0xff << 16)

#घोषणा DEINTERLACE_CHROMA_DIFF			0xb4
#घोषणा DEINTERLACE_CHROMA_DIFF_TH(v)			((v) & 0xff)
#घोषणा DEINTERLACE_CHROMA_DIFF_TH_MSK			(0xff)
#घोषणा DEINTERLACE_CHROMA_DIFF_LUMA(v)			(((v) & 0x3f) << 16)
#घोषणा DEINTERLACE_CHROMA_DIFF_LUMA_MSK		(0x3f << 16)
#घोषणा DEINTERLACE_CHROMA_DIFF_CHROMA(v)		(((v) & 0x3f) << 24)
#घोषणा DEINTERLACE_CHROMA_DIFF_CHROMA_MSK		(0x3f << 24)

#घोषणा DEINTERLACE_PRELUMA			0xb8
#घोषणा DEINTERLACE_PRECHROMA			0xbc
#घोषणा DEINTERLACE_TILE_FLAG0			0xc0
#घोषणा DEINTERLACE_TILE_FLAG1			0xc4
#घोषणा DEINTERLACE_FLAG_LINE_STRIDE		0xc8
#घोषणा DEINTERLACE_FLAG_SEQ			0xcc

#घोषणा DEINTERLACE_WB_LINE_STRIDE_CTRL		0xd0
#घोषणा DEINTERLACE_WB_LINE_STRIDE_CTRL_EN		BIT(0)

#घोषणा DEINTERLACE_WB_LINE_STRIDE0		0xd4
#घोषणा DEINTERLACE_WB_LINE_STRIDE1		0xd8
#घोषणा DEINTERLACE_WB_LINE_STRIDE2		0xdc
#घोषणा DEINTERLACE_TRD_CTRL			0xe0
#घोषणा DEINTERLACE_TRD_BUF_ADDR0		0xe4
#घोषणा DEINTERLACE_TRD_BUF_ADDR1		0xe8
#घोषणा DEINTERLACE_TRD_BUF_ADDR2		0xec
#घोषणा DEINTERLACE_TRD_TB_OFF0			0xf0
#घोषणा DEINTERLACE_TRD_TB_OFF1			0xf4
#घोषणा DEINTERLACE_TRD_TB_OFF2			0xf8
#घोषणा DEINTERLACE_TRD_WB_STRIDE		0xfc
#घोषणा DEINTERLACE_CH0_IN_SIZE			0x100
#घोषणा DEINTERLACE_CH0_OUT_SIZE		0x104
#घोषणा DEINTERLACE_CH0_HORZ_FACT		0x108
#घोषणा DEINTERLACE_CH0_VERT_FACT		0x10c
#घोषणा DEINTERLACE_CH0_HORZ_PHASE		0x110
#घोषणा DEINTERLACE_CH0_VERT_PHASE0		0x114
#घोषणा DEINTERLACE_CH0_VERT_PHASE1		0x118
#घोषणा DEINTERLACE_CH0_HORZ_TAP0		0x120
#घोषणा DEINTERLACE_CH0_HORZ_TAP1		0x124
#घोषणा DEINTERLACE_CH0_VERT_TAP		0x128
#घोषणा DEINTERLACE_CH1_IN_SIZE			0x200
#घोषणा DEINTERLACE_CH1_OUT_SIZE		0x204
#घोषणा DEINTERLACE_CH1_HORZ_FACT		0x208
#घोषणा DEINTERLACE_CH1_VERT_FACT		0x20c
#घोषणा DEINTERLACE_CH1_HORZ_PHASE		0x210
#घोषणा DEINTERLACE_CH1_VERT_PHASE0		0x214
#घोषणा DEINTERLACE_CH1_VERT_PHASE1		0x218
#घोषणा DEINTERLACE_CH1_HORZ_TAP0		0x220
#घोषणा DEINTERLACE_CH1_HORZ_TAP1		0x224
#घोषणा DEINTERLACE_CH1_VERT_TAP		0x228
#घोषणा DEINTERLACE_CH0_HORZ_COEF0		0x400 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH0_HORZ_COEF1		0x480 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH0_VERT_COEF		0x500 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH1_HORZ_COEF0		0x600 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH1_HORZ_COEF1		0x680 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH1_VERT_COEF		0x700 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH3_HORZ_COEF0		0x800 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH3_HORZ_COEF1		0x880 /* 32 रेजिस्टरs */
#घोषणा DEINTERLACE_CH3_VERT_COEF		0x900 /* 32 रेजिस्टरs */

#घोषणा DEINTERLACE_MIN_WIDTH	2U
#घोषणा DEINTERLACE_MIN_HEIGHT	2U
#घोषणा DEINTERLACE_MAX_WIDTH	2048U
#घोषणा DEINTERLACE_MAX_HEIGHT	1100U

#घोषणा DEINTERLACE_MODE_UV_COMBINED	2

#घोषणा DEINTERLACE_IN_FMT_YUV420	2

#घोषणा DEINTERLACE_OUT_FMT_YUV420SP	13

#घोषणा DEINTERLACE_PS_UVUV		0
#घोषणा DEINTERLACE_PS_VUVU		1

#घोषणा DEINTERLACE_IDENTITY_COEF	0x4000

#घोषणा DEINTERLACE_SIZE(w, h)	(((h) - 1) << 16 | ((w) - 1))

काष्ठा deपूर्णांकerlace_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा deपूर्णांकerlace_dev	*dev;

	काष्ठा v4l2_pix_क्रमmat	src_fmt;
	काष्ठा v4l2_pix_क्रमmat	dst_fmt;

	व्योम			*flag1_buf;
	dma_addr_t		flag1_buf_dma;

	व्योम			*flag2_buf;
	dma_addr_t		flag2_buf_dma;

	काष्ठा vb2_v4l2_buffer	*prev;

	अचिन्हित पूर्णांक		first_field;
	अचिन्हित पूर्णांक		field;

	पूर्णांक			पातing;
पूर्ण;

काष्ठा deपूर्णांकerlace_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;
	काष्ठा device		*dev;
	काष्ठा v4l2_m2m_dev	*m2m_dev;

	/* Device file mutex */
	काष्ठा mutex		dev_mutex;

	व्योम __iomem		*base;

	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;
	काष्ठा clk		*ram_clk;

	काष्ठा reset_control	*rstc;
पूर्ण;

#पूर्ण_अगर
