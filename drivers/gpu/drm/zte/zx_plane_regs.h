<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#अगर_अघोषित __ZX_PLANE_REGS_H__
#घोषणा __ZX_PLANE_REGS_H__

/* GL रेजिस्टरs */
#घोषणा GL_CTRL0			0x00
#घोषणा GL_UPDATE			BIT(5)
#घोषणा GL_CTRL1			0x04
#घोषणा GL_DATA_FMT_SHIFT		0
#घोषणा GL_DATA_FMT_MASK		(0xf << GL_DATA_FMT_SHIFT)
#घोषणा GL_FMT_ARGB8888			0
#घोषणा GL_FMT_RGB888			1
#घोषणा GL_FMT_RGB565			2
#घोषणा GL_FMT_ARGB1555			3
#घोषणा GL_FMT_ARGB4444			4
#घोषणा GL_CTRL2			0x08
#घोषणा GL_GLOBAL_ALPHA_SHIFT		8
#घोषणा GL_GLOBAL_ALPHA_MASK		(0xff << GL_GLOBAL_ALPHA_SHIFT)
#घोषणा GL_CTRL3			0x0c
#घोषणा GL_SCALER_BYPASS_MODE		BIT(0)
#घोषणा GL_STRIDE			0x18
#घोषणा GL_ADDR				0x1c
#घोषणा GL_SRC_SIZE			0x38
#घोषणा GL_SRC_W_SHIFT			16
#घोषणा GL_SRC_W_MASK			(0x3fff << GL_SRC_W_SHIFT)
#घोषणा GL_SRC_H_SHIFT			0
#घोषणा GL_SRC_H_MASK			(0x3fff << GL_SRC_H_SHIFT)
#घोषणा GL_POS_START			0x9c
#घोषणा GL_POS_END			0xa0
#घोषणा GL_POS_X_SHIFT			16
#घोषणा GL_POS_X_MASK			(0x1fff << GL_POS_X_SHIFT)
#घोषणा GL_POS_Y_SHIFT			0
#घोषणा GL_POS_Y_MASK			(0x1fff << GL_POS_Y_SHIFT)

#घोषणा GL_SRC_W(x)	(((x) << GL_SRC_W_SHIFT) & GL_SRC_W_MASK)
#घोषणा GL_SRC_H(x)	(((x) << GL_SRC_H_SHIFT) & GL_SRC_H_MASK)
#घोषणा GL_POS_X(x)	(((x) << GL_POS_X_SHIFT) & GL_POS_X_MASK)
#घोषणा GL_POS_Y(x)	(((x) << GL_POS_Y_SHIFT) & GL_POS_Y_MASK)

/* VL रेजिस्टरs */
#घोषणा VL_CTRL0			0x00
#घोषणा VL_UPDATE			BIT(3)
#घोषणा VL_CTRL1			0x04
#घोषणा VL_YUV420_PLANAR		BIT(5)
#घोषणा VL_YUV422_SHIFT			3
#घोषणा VL_YUV422_YUYV			(0 << VL_YUV422_SHIFT)
#घोषणा VL_YUV422_YVYU			(1 << VL_YUV422_SHIFT)
#घोषणा VL_YUV422_UYVY			(2 << VL_YUV422_SHIFT)
#घोषणा VL_YUV422_VYUY			(3 << VL_YUV422_SHIFT)
#घोषणा VL_FMT_YUV420			0
#घोषणा VL_FMT_YUV422			1
#घोषणा VL_FMT_YUV420_P010		2
#घोषणा VL_FMT_YUV420_HANTRO		3
#घोषणा VL_FMT_YUV444_8BIT		4
#घोषणा VL_FMT_YUV444_10BIT		5
#घोषणा VL_CTRL2			0x08
#घोषणा VL_SCALER_BYPASS_MODE		BIT(0)
#घोषणा VL_STRIDE			0x0c
#घोषणा LUMA_STRIDE_SHIFT		16
#घोषणा LUMA_STRIDE_MASK		(0xffff << LUMA_STRIDE_SHIFT)
#घोषणा CHROMA_STRIDE_SHIFT		0
#घोषणा CHROMA_STRIDE_MASK		(0xffff << CHROMA_STRIDE_SHIFT)
#घोषणा VL_SRC_SIZE			0x10
#घोषणा VL_Y				0x14
#घोषणा VL_POS_START			0x30
#घोषणा VL_POS_END			0x34

#घोषणा LUMA_STRIDE(x)	 (((x) << LUMA_STRIDE_SHIFT) & LUMA_STRIDE_MASK)
#घोषणा CHROMA_STRIDE(x) (((x) << CHROMA_STRIDE_SHIFT) & CHROMA_STRIDE_MASK)

/* RSZ रेजिस्टरs */
#घोषणा RSZ_SRC_CFG			0x00
#घोषणा RSZ_DEST_CFG			0x04
#घोषणा RSZ_ENABLE_CFG			0x14

#घोषणा RSZ_VL_LUMA_HOR			0x08
#घोषणा RSZ_VL_LUMA_VER			0x0c
#घोषणा RSZ_VL_CHROMA_HOR		0x10
#घोषणा RSZ_VL_CHROMA_VER		0x14
#घोषणा RSZ_VL_CTRL_CFG			0x18
#घोषणा RSZ_VL_FMT_SHIFT		3
#घोषणा RSZ_VL_FMT_MASK			(0x3 << RSZ_VL_FMT_SHIFT)
#घोषणा RSZ_VL_FMT_YCBCR420		(0x0 << RSZ_VL_FMT_SHIFT)
#घोषणा RSZ_VL_FMT_YCBCR422		(0x1 << RSZ_VL_FMT_SHIFT)
#घोषणा RSZ_VL_FMT_YCBCR444		(0x2 << RSZ_VL_FMT_SHIFT)
#घोषणा RSZ_VL_ENABLE_CFG		0x1c

#घोषणा RSZ_VER_SHIFT			16
#घोषणा RSZ_VER_MASK			(0xffff << RSZ_VER_SHIFT)
#घोषणा RSZ_HOR_SHIFT			0
#घोषणा RSZ_HOR_MASK			(0xffff << RSZ_HOR_SHIFT)

#घोषणा RSZ_VER(x)	(((x) << RSZ_VER_SHIFT) & RSZ_VER_MASK)
#घोषणा RSZ_HOR(x)	(((x) << RSZ_HOR_SHIFT) & RSZ_HOR_MASK)

#घोषणा RSZ_DATA_STEP_SHIFT		16
#घोषणा RSZ_DATA_STEP_MASK		(0xffff << RSZ_DATA_STEP_SHIFT)
#घोषणा RSZ_PARA_STEP_SHIFT		0
#घोषणा RSZ_PARA_STEP_MASK		(0xffff << RSZ_PARA_STEP_SHIFT)

#घोषणा RSZ_DATA_STEP(x) (((x) << RSZ_DATA_STEP_SHIFT) & RSZ_DATA_STEP_MASK)
#घोषणा RSZ_PARA_STEP(x) (((x) << RSZ_PARA_STEP_SHIFT) & RSZ_PARA_STEP_MASK)

/* HBSC रेजिस्टरs */
#घोषणा HBSC_SATURATION			0x00
#घोषणा HBSC_HUE			0x04
#घोषणा HBSC_BRIGHT			0x08
#घोषणा HBSC_CONTRAST			0x0c
#घोषणा HBSC_THRESHOLD_COL1		0x10
#घोषणा HBSC_THRESHOLD_COL2		0x14
#घोषणा HBSC_THRESHOLD_COL3		0x18
#घोषणा HBSC_CTRL0			0x28
#घोषणा HBSC_CTRL_EN			BIT(2)

#पूर्ण_अगर /* __ZX_PLANE_REGS_H__ */
