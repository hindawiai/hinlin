<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-vfe-4-1.c
 *
 * Qualcomm MSM Camera Subप्रणाली - VFE (Video Front End) Module v4.1
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>

#समावेश "camss.h"
#समावेश "camss-vfe.h"
#समावेश "camss-vfe-gen1.h"

#घोषणा VFE_0_HW_VERSION		0x000

#घोषणा VFE_0_GLOBAL_RESET_CMD		0x00c
#घोषणा VFE_0_GLOBAL_RESET_CMD_CORE	BIT(0)
#घोषणा VFE_0_GLOBAL_RESET_CMD_CAMIF	BIT(1)
#घोषणा VFE_0_GLOBAL_RESET_CMD_BUS	BIT(2)
#घोषणा VFE_0_GLOBAL_RESET_CMD_BUS_BDG	BIT(3)
#घोषणा VFE_0_GLOBAL_RESET_CMD_REGISTER	BIT(4)
#घोषणा VFE_0_GLOBAL_RESET_CMD_TIMER	BIT(5)
#घोषणा VFE_0_GLOBAL_RESET_CMD_PM	BIT(6)
#घोषणा VFE_0_GLOBAL_RESET_CMD_BUS_MISR	BIT(7)
#घोषणा VFE_0_GLOBAL_RESET_CMD_TESTGEN	BIT(8)

#घोषणा VFE_0_MODULE_CFG		0x018
#घोषणा VFE_0_MODULE_CFG_DEMUX			BIT(2)
#घोषणा VFE_0_MODULE_CFG_CHROMA_UPSAMPLE	BIT(3)
#घोषणा VFE_0_MODULE_CFG_SCALE_ENC		BIT(23)
#घोषणा VFE_0_MODULE_CFG_CROP_ENC		BIT(27)

#घोषणा VFE_0_CORE_CFG			0x01c
#घोषणा VFE_0_CORE_CFG_PIXEL_PATTERN_YCBYCR	0x4
#घोषणा VFE_0_CORE_CFG_PIXEL_PATTERN_YCRYCB	0x5
#घोषणा VFE_0_CORE_CFG_PIXEL_PATTERN_CBYCRY	0x6
#घोषणा VFE_0_CORE_CFG_PIXEL_PATTERN_CRYCBY	0x7

#घोषणा VFE_0_IRQ_CMD			0x024
#घोषणा VFE_0_IRQ_CMD_GLOBAL_CLEAR	BIT(0)

#घोषणा VFE_0_IRQ_MASK_0		0x028
#घोषणा VFE_0_IRQ_MASK_0_CAMIF_SOF			BIT(0)
#घोषणा VFE_0_IRQ_MASK_0_CAMIF_खातापूर्ण			BIT(1)
#घोषणा VFE_0_IRQ_MASK_0_RDIn_REG_UPDATE(n)		BIT((n) + 5)
#घोषणा VFE_0_IRQ_MASK_0_line_n_REG_UPDATE(n)		\
	((n) == VFE_LINE_PIX ? BIT(4) : VFE_0_IRQ_MASK_0_RDIn_REG_UPDATE(n))
#घोषणा VFE_0_IRQ_MASK_0_IMAGE_MASTER_n_PING_PONG(n)	BIT((n) + 8)
#घोषणा VFE_0_IRQ_MASK_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#घोषणा VFE_0_IRQ_MASK_0_RESET_ACK			BIT(31)
#घोषणा VFE_0_IRQ_MASK_1		0x02c
#घोषणा VFE_0_IRQ_MASK_1_CAMIF_ERROR			BIT(0)
#घोषणा VFE_0_IRQ_MASK_1_VIOLATION			BIT(7)
#घोषणा VFE_0_IRQ_MASK_1_BUS_BDG_HALT_ACK		BIT(8)
#घोषणा VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(n)	BIT((n) + 9)
#घोषणा VFE_0_IRQ_MASK_1_RDIn_SOF(n)			BIT((n) + 29)

#घोषणा VFE_0_IRQ_CLEAR_0		0x030
#घोषणा VFE_0_IRQ_CLEAR_1		0x034

#घोषणा VFE_0_IRQ_STATUS_0		0x038
#घोषणा VFE_0_IRQ_STATUS_0_CAMIF_SOF			BIT(0)
#घोषणा VFE_0_IRQ_STATUS_0_RDIn_REG_UPDATE(n)		BIT((n) + 5)
#घोषणा VFE_0_IRQ_STATUS_0_line_n_REG_UPDATE(n)		\
	((n) == VFE_LINE_PIX ? BIT(4) : VFE_0_IRQ_STATUS_0_RDIn_REG_UPDATE(n))
#घोषणा VFE_0_IRQ_STATUS_0_IMAGE_MASTER_n_PING_PONG(n)	BIT((n) + 8)
#घोषणा VFE_0_IRQ_STATUS_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#घोषणा VFE_0_IRQ_STATUS_0_RESET_ACK			BIT(31)
#घोषणा VFE_0_IRQ_STATUS_1		0x03c
#घोषणा VFE_0_IRQ_STATUS_1_VIOLATION			BIT(7)
#घोषणा VFE_0_IRQ_STATUS_1_BUS_BDG_HALT_ACK		BIT(8)
#घोषणा VFE_0_IRQ_STATUS_1_RDIn_SOF(n)			BIT((n) + 29)

#घोषणा VFE_0_IRQ_COMPOSITE_MASK_0	0x40
#घोषणा VFE_0_VIOLATION_STATUS		0x48

#घोषणा VFE_0_BUS_CMD			0x4c
#घोषणा VFE_0_BUS_CMD_Mx_RLD_CMD(x)	BIT(x)

#घोषणा VFE_0_BUS_CFG			0x050

#घोषणा VFE_0_BUS_XBAR_CFG_x(x)		(0x58 + 0x4 * ((x) / 2))
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_PAIR_STREAM_EN			BIT(1)
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_PAIR_STREAM_SWAP_INTER_INTRA	(0x3 << 4)
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT		8
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_LUMA		0
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI0	5
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI1	6
#घोषणा VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI2	7

#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_CFG(n)		(0x06c + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_WR_PATH_SHIFT	0
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_FRM_BASED_SHIFT	1
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_PING_ADDR(n)	(0x070 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_PONG_ADDR(n)	(0x074 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(n)		(0x078 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_SHIFT	2
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK	(0x1f << 2)

#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_UB_CFG(n)		(0x07c + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_UB_CFG_OFFSET_SHIFT	16
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_IMAGE_SIZE(n)	(0x080 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_BUFFER_CFG(n)	(0x084 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_FRAMEDROP_PATTERN(n)	\
							(0x088 + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_IRQ_SUBSAMPLE_PATTERN(n)	\
							(0x08c + 0x24 * (n))
#घोषणा VFE_0_BUS_IMAGE_MASTER_n_WR_IRQ_SUBSAMPLE_PATTERN_DEF	0xffffffff

#घोषणा VFE_0_BUS_PING_PONG_STATUS	0x268

#घोषणा VFE_0_BUS_BDG_CMD		0x2c0
#घोषणा VFE_0_BUS_BDG_CMD_HALT_REQ	1

#घोषणा VFE_0_BUS_BDG_QOS_CFG_0		0x2c4
#घोषणा VFE_0_BUS_BDG_QOS_CFG_0_CFG	0xaaa5aaa5
#घोषणा VFE_0_BUS_BDG_QOS_CFG_1		0x2c8
#घोषणा VFE_0_BUS_BDG_QOS_CFG_2		0x2cc
#घोषणा VFE_0_BUS_BDG_QOS_CFG_3		0x2d0
#घोषणा VFE_0_BUS_BDG_QOS_CFG_4		0x2d4
#घोषणा VFE_0_BUS_BDG_QOS_CFG_5		0x2d8
#घोषणा VFE_0_BUS_BDG_QOS_CFG_6		0x2dc
#घोषणा VFE_0_BUS_BDG_QOS_CFG_7		0x2e0
#घोषणा VFE_0_BUS_BDG_QOS_CFG_7_CFG	0x0001aaa5

#घोषणा VFE_0_RDI_CFG_x(x)		(0x2e8 + (0x4 * (x)))
#घोषणा VFE_0_RDI_CFG_x_RDI_STREAM_SEL_SHIFT	28
#घोषणा VFE_0_RDI_CFG_x_RDI_STREAM_SEL_MASK	(0xf << 28)
#घोषणा VFE_0_RDI_CFG_x_RDI_M0_SEL_SHIFT	4
#घोषणा VFE_0_RDI_CFG_x_RDI_M0_SEL_MASK		(0xf << 4)
#घोषणा VFE_0_RDI_CFG_x_RDI_EN_BIT		BIT(2)
#घोषणा VFE_0_RDI_CFG_x_MIPI_EN_BITS		0x3
#घोषणा VFE_0_RDI_CFG_x_RDI_Mr_FRAME_BASED_EN(r)	BIT(16 + (r))

#घोषणा VFE_0_CAMIF_CMD				0x2f4
#घोषणा VFE_0_CAMIF_CMD_DISABLE_FRAME_BOUNDARY	0
#घोषणा VFE_0_CAMIF_CMD_ENABLE_FRAME_BOUNDARY	1
#घोषणा VFE_0_CAMIF_CMD_NO_CHANGE		3
#घोषणा VFE_0_CAMIF_CMD_CLEAR_CAMIF_STATUS	BIT(2)
#घोषणा VFE_0_CAMIF_CFG				0x2f8
#घोषणा VFE_0_CAMIF_CFG_VFE_OUTPUT_EN		BIT(6)
#घोषणा VFE_0_CAMIF_FRAME_CFG			0x300
#घोषणा VFE_0_CAMIF_WINDOW_WIDTH_CFG		0x304
#घोषणा VFE_0_CAMIF_WINDOW_HEIGHT_CFG		0x308
#घोषणा VFE_0_CAMIF_SUBSAMPLE_CFG_0		0x30c
#घोषणा VFE_0_CAMIF_IRQ_SUBSAMPLE_PATTERN	0x314
#घोषणा VFE_0_CAMIF_STATUS			0x31c
#घोषणा VFE_0_CAMIF_STATUS_HALT			BIT(31)

#घोषणा VFE_0_REG_UPDATE			0x378
#घोषणा VFE_0_REG_UPDATE_RDIn(n)		BIT(1 + (n))
#घोषणा VFE_0_REG_UPDATE_line_n(n)		\
			((n) == VFE_LINE_PIX ? 1 : VFE_0_REG_UPDATE_RDIn(n))

#घोषणा VFE_0_DEMUX_CFG				0x424
#घोषणा VFE_0_DEMUX_CFG_PERIOD			0x3
#घोषणा VFE_0_DEMUX_GAIN_0			0x428
#घोषणा VFE_0_DEMUX_GAIN_0_CH0_EVEN		(0x80 << 0)
#घोषणा VFE_0_DEMUX_GAIN_0_CH0_ODD		(0x80 << 16)
#घोषणा VFE_0_DEMUX_GAIN_1			0x42c
#घोषणा VFE_0_DEMUX_GAIN_1_CH1			(0x80 << 0)
#घोषणा VFE_0_DEMUX_GAIN_1_CH2			(0x80 << 16)
#घोषणा VFE_0_DEMUX_EVEN_CFG			0x438
#घोषणा VFE_0_DEMUX_EVEN_CFG_PATTERN_YUYV	0x9cac
#घोषणा VFE_0_DEMUX_EVEN_CFG_PATTERN_YVYU	0xac9c
#घोषणा VFE_0_DEMUX_EVEN_CFG_PATTERN_UYVY	0xc9ca
#घोषणा VFE_0_DEMUX_EVEN_CFG_PATTERN_VYUY	0xcac9
#घोषणा VFE_0_DEMUX_ODD_CFG			0x43c
#घोषणा VFE_0_DEMUX_ODD_CFG_PATTERN_YUYV	0x9cac
#घोषणा VFE_0_DEMUX_ODD_CFG_PATTERN_YVYU	0xac9c
#घोषणा VFE_0_DEMUX_ODD_CFG_PATTERN_UYVY	0xc9ca
#घोषणा VFE_0_DEMUX_ODD_CFG_PATTERN_VYUY	0xcac9

#घोषणा VFE_0_SCALE_ENC_Y_CFG			0x75c
#घोषणा VFE_0_SCALE_ENC_Y_H_IMAGE_SIZE		0x760
#घोषणा VFE_0_SCALE_ENC_Y_H_PHASE		0x764
#घोषणा VFE_0_SCALE_ENC_Y_V_IMAGE_SIZE		0x76c
#घोषणा VFE_0_SCALE_ENC_Y_V_PHASE		0x770
#घोषणा VFE_0_SCALE_ENC_CBCR_CFG		0x778
#घोषणा VFE_0_SCALE_ENC_CBCR_H_IMAGE_SIZE	0x77c
#घोषणा VFE_0_SCALE_ENC_CBCR_H_PHASE		0x780
#घोषणा VFE_0_SCALE_ENC_CBCR_V_IMAGE_SIZE	0x790
#घोषणा VFE_0_SCALE_ENC_CBCR_V_PHASE		0x794

#घोषणा VFE_0_CROP_ENC_Y_WIDTH			0x854
#घोषणा VFE_0_CROP_ENC_Y_HEIGHT			0x858
#घोषणा VFE_0_CROP_ENC_CBCR_WIDTH		0x85c
#घोषणा VFE_0_CROP_ENC_CBCR_HEIGHT		0x860

#घोषणा VFE_0_CLAMP_ENC_MAX_CFG			0x874
#घोषणा VFE_0_CLAMP_ENC_MAX_CFG_CH0		(0xff << 0)
#घोषणा VFE_0_CLAMP_ENC_MAX_CFG_CH1		(0xff << 8)
#घोषणा VFE_0_CLAMP_ENC_MAX_CFG_CH2		(0xff << 16)
#घोषणा VFE_0_CLAMP_ENC_MIN_CFG			0x878
#घोषणा VFE_0_CLAMP_ENC_MIN_CFG_CH0		(0x0 << 0)
#घोषणा VFE_0_CLAMP_ENC_MIN_CFG_CH1		(0x0 << 8)
#घोषणा VFE_0_CLAMP_ENC_MIN_CFG_CH2		(0x0 << 16)

#घोषणा VFE_0_CGC_OVERRIDE_1			0x974
#घोषणा VFE_0_CGC_OVERRIDE_1_IMAGE_Mx_CGC_OVERRIDE(x)	BIT(x)

#घोषणा CAMIF_TIMEOUT_SLEEP_US 1000
#घोषणा CAMIF_TIMEOUT_ALL_US 1000000

#घोषणा MSM_VFE_VFE0_UB_SIZE 1023
#घोषणा MSM_VFE_VFE0_UB_SIZE_RDI (MSM_VFE_VFE0_UB_SIZE / 3)

अटल व्योम vfe_hw_version_पढ़ो(काष्ठा vfe_device *vfe, काष्ठा device *dev)
अणु
	u32 hw_version = पढ़ोl_relaxed(vfe->base + VFE_0_HW_VERSION);

	dev_dbg(dev, "VFE HW Version = 0x%08x\n", hw_version);
पूर्ण

अटल u16 vfe_get_ub_size(u8 vfe_id)
अणु
	अगर (vfe_id == 0)
		वापस MSM_VFE_VFE0_UB_SIZE_RDI;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम vfe_reg_clr(काष्ठा vfe_device *vfe, u32 reg, u32 clr_bits)
अणु
	u32 bits = पढ़ोl_relaxed(vfe->base + reg);

	ग_लिखोl_relaxed(bits & ~clr_bits, vfe->base + reg);
पूर्ण

अटल अंतरभूत व्योम vfe_reg_set(काष्ठा vfe_device *vfe, u32 reg, u32 set_bits)
अणु
	u32 bits = पढ़ोl_relaxed(vfe->base + reg);

	ग_लिखोl_relaxed(bits | set_bits, vfe->base + reg);
पूर्ण

अटल व्योम vfe_global_reset(काष्ठा vfe_device *vfe)
अणु
	u32 reset_bits = VFE_0_GLOBAL_RESET_CMD_TESTGEN		|
			 VFE_0_GLOBAL_RESET_CMD_BUS_MISR	|
			 VFE_0_GLOBAL_RESET_CMD_PM		|
			 VFE_0_GLOBAL_RESET_CMD_TIMER		|
			 VFE_0_GLOBAL_RESET_CMD_REGISTER	|
			 VFE_0_GLOBAL_RESET_CMD_BUS_BDG		|
			 VFE_0_GLOBAL_RESET_CMD_BUS		|
			 VFE_0_GLOBAL_RESET_CMD_CAMIF		|
			 VFE_0_GLOBAL_RESET_CMD_CORE;

	ग_लिखोl_relaxed(reset_bits, vfe->base + VFE_0_GLOBAL_RESET_CMD);
पूर्ण

अटल व्योम vfe_halt_request(काष्ठा vfe_device *vfe)
अणु
	ग_लिखोl_relaxed(VFE_0_BUS_BDG_CMD_HALT_REQ,
		       vfe->base + VFE_0_BUS_BDG_CMD);
पूर्ण

अटल व्योम vfe_halt_clear(काष्ठा vfe_device *vfe)
अणु
	ग_लिखोl_relaxed(0x0, vfe->base + VFE_0_BUS_BDG_CMD);
पूर्ण

अटल व्योम vfe_wm_enable(काष्ठा vfe_device *vfe, u8 wm, u8 enable)
अणु
	अगर (enable)
		vfe_reg_set(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_CFG(wm),
			    1 << VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_WR_PATH_SHIFT);
	अन्यथा
		vfe_reg_clr(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_CFG(wm),
			    1 << VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_WR_PATH_SHIFT);
पूर्ण

अटल व्योम vfe_wm_frame_based(काष्ठा vfe_device *vfe, u8 wm, u8 enable)
अणु
	अगर (enable)
		vfe_reg_set(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_FRM_BASED_SHIFT);
	अन्यथा
		vfe_reg_clr(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTER_n_WR_CFG_FRM_BASED_SHIFT);
पूर्ण

अटल व्योम vfe_get_wm_sizes(काष्ठा v4l2_pix_क्रमmat_mplane *pix, u8 plane,
			     u16 *width, u16 *height, u16 *bytesperline)
अणु
	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		*width = pix->width;
		*height = pix->height;
		*bytesperline = pix->plane_fmt[0].bytesperline;
		अगर (plane == 1)
			*height /= 2;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		*width = pix->width;
		*height = pix->height;
		*bytesperline = pix->plane_fmt[0].bytesperline;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vfe_wm_line_based(काष्ठा vfe_device *vfe, u32 wm,
			      काष्ठा v4l2_pix_क्रमmat_mplane *pix,
			      u8 plane, u32 enable)
अणु
	u32 reg;

	अगर (enable) अणु
		u16 width = 0, height = 0, bytesperline = 0, wpl;

		vfe_get_wm_sizes(pix, plane, &width, &height, &bytesperline);

		wpl = vfe_word_per_line(pix->pixelक्रमmat, width);

		reg = height - 1;
		reg |= ((wpl + 1) / 2 - 1) << 16;

		ग_लिखोl_relaxed(reg, vfe->base +
			       VFE_0_BUS_IMAGE_MASTER_n_WR_IMAGE_SIZE(wm));

		wpl = vfe_word_per_line(pix->pixelक्रमmat, bytesperline);

		reg = 0x3;
		reg |= (height - 1) << 4;
		reg |= wpl << 16;

		ग_लिखोl_relaxed(reg, vfe->base +
			       VFE_0_BUS_IMAGE_MASTER_n_WR_BUFFER_CFG(wm));
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(0, vfe->base +
			       VFE_0_BUS_IMAGE_MASTER_n_WR_IMAGE_SIZE(wm));
		ग_लिखोl_relaxed(0, vfe->base +
			       VFE_0_BUS_IMAGE_MASTER_n_WR_BUFFER_CFG(wm));
	पूर्ण
पूर्ण

अटल व्योम vfe_wm_set_framedrop_period(काष्ठा vfe_device *vfe, u8 wm, u8 per)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(vfe->base +
			    VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm));

	reg &= ~(VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK);

	reg |= (per << VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_SHIFT)
		& VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK;

	ग_लिखोl_relaxed(reg,
		       vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm));
पूर्ण

अटल व्योम vfe_wm_set_framedrop_pattern(काष्ठा vfe_device *vfe, u8 wm,
					 u32 pattern)
अणु
	ग_लिखोl_relaxed(pattern,
	       vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_FRAMEDROP_PATTERN(wm));
पूर्ण

अटल व्योम vfe_wm_set_ub_cfg(काष्ठा vfe_device *vfe, u8 wm,
			      u16 offset, u16 depth)
अणु
	u32 reg;

	reg = (offset << VFE_0_BUS_IMAGE_MASTER_n_WR_UB_CFG_OFFSET_SHIFT) |
		depth;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_UB_CFG(wm));
पूर्ण

अटल व्योम vfe_bus_reload_wm(काष्ठा vfe_device *vfe, u8 wm)
अणु
	wmb();
	ग_लिखोl_relaxed(VFE_0_BUS_CMD_Mx_RLD_CMD(wm), vfe->base + VFE_0_BUS_CMD);
	wmb();
पूर्ण

अटल व्योम vfe_wm_set_ping_addr(काष्ठा vfe_device *vfe, u8 wm, u32 addr)
अणु
	ग_लिखोl_relaxed(addr,
		       vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_PING_ADDR(wm));
पूर्ण

अटल व्योम vfe_wm_set_pong_addr(काष्ठा vfe_device *vfe, u8 wm, u32 addr)
अणु
	ग_लिखोl_relaxed(addr,
		       vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_PONG_ADDR(wm));
पूर्ण

अटल पूर्णांक vfe_wm_get_ping_pong_status(काष्ठा vfe_device *vfe, u8 wm)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(vfe->base + VFE_0_BUS_PING_PONG_STATUS);

	वापस (reg >> wm) & 0x1;
पूर्ण

अटल व्योम vfe_bus_enable_wr_अगर(काष्ठा vfe_device *vfe, u8 enable)
अणु
	अगर (enable)
		ग_लिखोl_relaxed(0x10000009, vfe->base + VFE_0_BUS_CFG);
	अन्यथा
		ग_लिखोl_relaxed(0, vfe->base + VFE_0_BUS_CFG);
पूर्ण

अटल व्योम vfe_bus_connect_wm_to_rdi(काष्ठा vfe_device *vfe, u8 wm,
				      क्रमागत vfe_line_id id)
अणु
	u32 reg;

	reg = VFE_0_RDI_CFG_x_MIPI_EN_BITS;
	reg |= VFE_0_RDI_CFG_x_RDI_Mr_FRAME_BASED_EN(id);
	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(0), reg);

	reg = VFE_0_RDI_CFG_x_RDI_EN_BIT;
	reg |= ((3 * id) << VFE_0_RDI_CFG_x_RDI_STREAM_SEL_SHIFT) &
		VFE_0_RDI_CFG_x_RDI_STREAM_SEL_MASK;
	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(id), reg);

	चयन (id) अणु
	हाल VFE_LINE_RDI0:
	शेष:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI0 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	हाल VFE_LINE_RDI1:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI1 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	हाल VFE_LINE_RDI2:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI2 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	पूर्ण

	अगर (wm % 2 == 1)
		reg <<= 16;

	vfe_reg_set(vfe, VFE_0_BUS_XBAR_CFG_x(wm), reg);
पूर्ण

अटल व्योम vfe_wm_set_subsample(काष्ठा vfe_device *vfe, u8 wm)
अणु
	ग_लिखोl_relaxed(VFE_0_BUS_IMAGE_MASTER_n_WR_IRQ_SUBSAMPLE_PATTERN_DEF,
		       vfe->base +
		       VFE_0_BUS_IMAGE_MASTER_n_WR_IRQ_SUBSAMPLE_PATTERN(wm));
पूर्ण

अटल व्योम vfe_bus_disconnect_wm_from_rdi(काष्ठा vfe_device *vfe, u8 wm,
					   क्रमागत vfe_line_id id)
अणु
	u32 reg;

	reg = VFE_0_RDI_CFG_x_RDI_Mr_FRAME_BASED_EN(id);
	vfe_reg_clr(vfe, VFE_0_RDI_CFG_x(0), reg);

	reg = VFE_0_RDI_CFG_x_RDI_EN_BIT;
	vfe_reg_clr(vfe, VFE_0_RDI_CFG_x(id), reg);

	चयन (id) अणु
	हाल VFE_LINE_RDI0:
	शेष:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI0 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	हाल VFE_LINE_RDI1:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI1 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	हाल VFE_LINE_RDI2:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI2 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		अवरोध;
	पूर्ण

	अगर (wm % 2 == 1)
		reg <<= 16;

	vfe_reg_clr(vfe, VFE_0_BUS_XBAR_CFG_x(wm), reg);
पूर्ण

अटल व्योम vfe_set_xbar_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_output *output,
			     u8 enable)
अणु
	काष्ठा vfe_line *line = container_of(output, काष्ठा vfe_line, output);
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelक्रमmat;
	u32 reg;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < output->wm_num; i++) अणु
		अगर (i == 0) अणु
			reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_LUMA <<
				VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		पूर्ण अन्यथा अगर (i == 1) अणु
			reg = VFE_0_BUS_XBAR_CFG_x_M_PAIR_STREAM_EN;
			अगर (p == V4L2_PIX_FMT_NV12 || p == V4L2_PIX_FMT_NV16)
				reg |= VFE_0_BUS_XBAR_CFG_x_M_PAIR_STREAM_SWAP_INTER_INTRA;
		पूर्ण अन्यथा अणु
			/* On current devices output->wm_num is always <= 2 */
			अवरोध;
		पूर्ण

		अगर (output->wm_idx[i] % 2 == 1)
			reg <<= 16;

		अगर (enable)
			vfe_reg_set(vfe,
				    VFE_0_BUS_XBAR_CFG_x(output->wm_idx[i]),
				    reg);
		अन्यथा
			vfe_reg_clr(vfe,
				    VFE_0_BUS_XBAR_CFG_x(output->wm_idx[i]),
				    reg);
	पूर्ण
पूर्ण

अटल व्योम vfe_set_realign_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line,
				u8 enable)
अणु
	/* empty */
पूर्ण
अटल व्योम vfe_set_rdi_cid(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id id, u8 cid)
अणु
	vfe_reg_clr(vfe, VFE_0_RDI_CFG_x(id),
		    VFE_0_RDI_CFG_x_RDI_M0_SEL_MASK);

	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(id),
		    cid << VFE_0_RDI_CFG_x_RDI_M0_SEL_SHIFT);
पूर्ण

अटल व्योम vfe_reg_update(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	vfe->reg_update |= VFE_0_REG_UPDATE_line_n(line_id);
	wmb();
	ग_लिखोl_relaxed(vfe->reg_update, vfe->base + VFE_0_REG_UPDATE);
	wmb();
पूर्ण

अटल अंतरभूत व्योम vfe_reg_update_clear(काष्ठा vfe_device *vfe,
					क्रमागत vfe_line_id line_id)
अणु
	vfe->reg_update &= ~VFE_0_REG_UPDATE_line_n(line_id);
पूर्ण

अटल व्योम vfe_enable_irq_wm_line(काष्ठा vfe_device *vfe, u8 wm,
				   क्रमागत vfe_line_id line_id, u8 enable)
अणु
	u32 irq_en0 = VFE_0_IRQ_MASK_0_IMAGE_MASTER_n_PING_PONG(wm) |
		      VFE_0_IRQ_MASK_0_line_n_REG_UPDATE(line_id);
	u32 irq_en1 = VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(wm) |
		      VFE_0_IRQ_MASK_1_RDIn_SOF(line_id);

	अगर (enable) अणु
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_1, irq_en1);
	पूर्ण अन्यथा अणु
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_1, irq_en1);
	पूर्ण
पूर्ण

अटल व्योम vfe_enable_irq_pix_line(काष्ठा vfe_device *vfe, u8 comp,
				    क्रमागत vfe_line_id line_id, u8 enable)
अणु
	काष्ठा vfe_output *output = &vfe->line[line_id].output;
	अचिन्हित पूर्णांक i;
	u32 irq_en0;
	u32 irq_en1;
	u32 comp_mask = 0;

	irq_en0 = VFE_0_IRQ_MASK_0_CAMIF_SOF;
	irq_en0 |= VFE_0_IRQ_MASK_0_CAMIF_खातापूर्ण;
	irq_en0 |= VFE_0_IRQ_MASK_0_IMAGE_COMPOSITE_DONE_n(comp);
	irq_en0 |= VFE_0_IRQ_MASK_0_line_n_REG_UPDATE(line_id);
	irq_en1 = VFE_0_IRQ_MASK_1_CAMIF_ERROR;
	क्रम (i = 0; i < output->wm_num; i++) अणु
		irq_en1 |= VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(
							output->wm_idx[i]);
		comp_mask |= (1 << output->wm_idx[i]) << comp * 8;
	पूर्ण

	अगर (enable) अणु
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_1, irq_en1);
		vfe_reg_set(vfe, VFE_0_IRQ_COMPOSITE_MASK_0, comp_mask);
	पूर्ण अन्यथा अणु
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_1, irq_en1);
		vfe_reg_clr(vfe, VFE_0_IRQ_COMPOSITE_MASK_0, comp_mask);
	पूर्ण
पूर्ण

अटल व्योम vfe_enable_irq_common(काष्ठा vfe_device *vfe)
अणु
	u32 irq_en0 = VFE_0_IRQ_MASK_0_RESET_ACK;
	u32 irq_en1 = VFE_0_IRQ_MASK_1_VIOLATION |
		      VFE_0_IRQ_MASK_1_BUS_BDG_HALT_ACK;

	vfe_reg_set(vfe, VFE_0_IRQ_MASK_0, irq_en0);
	vfe_reg_set(vfe, VFE_0_IRQ_MASK_1, irq_en1);
पूर्ण

अटल व्योम vfe_set_demux_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line)
अणु
	u32 val, even_cfg, odd_cfg;

	ग_लिखोl_relaxed(VFE_0_DEMUX_CFG_PERIOD, vfe->base + VFE_0_DEMUX_CFG);

	val = VFE_0_DEMUX_GAIN_0_CH0_EVEN | VFE_0_DEMUX_GAIN_0_CH0_ODD;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_DEMUX_GAIN_0);

	val = VFE_0_DEMUX_GAIN_1_CH1 | VFE_0_DEMUX_GAIN_1_CH2;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_DEMUX_GAIN_1);

	चयन (line->fmt[MSM_VFE_PAD_SINK].code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTERN_YUYV;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTERN_YUYV;
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTERN_YVYU;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTERN_YVYU;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	शेष:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTERN_UYVY;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTERN_UYVY;
		अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTERN_VYUY;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTERN_VYUY;
		अवरोध;
	पूर्ण

	ग_लिखोl_relaxed(even_cfg, vfe->base + VFE_0_DEMUX_EVEN_CFG);
	ग_लिखोl_relaxed(odd_cfg, vfe->base + VFE_0_DEMUX_ODD_CFG);
पूर्ण

अटल व्योम vfe_set_scale_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line)
अणु
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelक्रमmat;
	u32 reg;
	u16 input, output;
	u8 पूर्णांकerp_reso;
	u32 phase_mult;

	ग_लिखोl_relaxed(0x3, vfe->base + VFE_0_SCALE_ENC_Y_CFG);

	input = line->fmt[MSM_VFE_PAD_SINK].width;
	output = line->compose.width;
	reg = (output << 16) | input;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_H_IMAGE_SIZE);

	पूर्णांकerp_reso = vfe_calc_पूर्णांकerp_reso(input, output);
	phase_mult = input * (1 << (13 + पूर्णांकerp_reso)) / output;
	reg = (पूर्णांकerp_reso << 20) | phase_mult;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_H_PHASE);

	input = line->fmt[MSM_VFE_PAD_SINK].height;
	output = line->compose.height;
	reg = (output << 16) | input;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_V_IMAGE_SIZE);

	पूर्णांकerp_reso = vfe_calc_पूर्णांकerp_reso(input, output);
	phase_mult = input * (1 << (13 + पूर्णांकerp_reso)) / output;
	reg = (पूर्णांकerp_reso << 20) | phase_mult;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_V_PHASE);

	ग_लिखोl_relaxed(0x3, vfe->base + VFE_0_SCALE_ENC_CBCR_CFG);

	input = line->fmt[MSM_VFE_PAD_SINK].width;
	output = line->compose.width / 2;
	reg = (output << 16) | input;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_H_IMAGE_SIZE);

	पूर्णांकerp_reso = vfe_calc_पूर्णांकerp_reso(input, output);
	phase_mult = input * (1 << (13 + पूर्णांकerp_reso)) / output;
	reg = (पूर्णांकerp_reso << 20) | phase_mult;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_H_PHASE);

	input = line->fmt[MSM_VFE_PAD_SINK].height;
	output = line->compose.height;
	अगर (p == V4L2_PIX_FMT_NV12 || p == V4L2_PIX_FMT_NV21)
		output = line->compose.height / 2;
	reg = (output << 16) | input;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_V_IMAGE_SIZE);

	पूर्णांकerp_reso = vfe_calc_पूर्णांकerp_reso(input, output);
	phase_mult = input * (1 << (13 + पूर्णांकerp_reso)) / output;
	reg = (पूर्णांकerp_reso << 20) | phase_mult;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_V_PHASE);
पूर्ण

अटल व्योम vfe_set_crop_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line)
अणु
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelक्रमmat;
	u32 reg;
	u16 first, last;

	first = line->crop.left;
	last = line->crop.left + line->crop.width - 1;
	reg = (first << 16) | last;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_CROP_ENC_Y_WIDTH);

	first = line->crop.top;
	last = line->crop.top + line->crop.height - 1;
	reg = (first << 16) | last;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_CROP_ENC_Y_HEIGHT);

	first = line->crop.left / 2;
	last = line->crop.left / 2 + line->crop.width / 2 - 1;
	reg = (first << 16) | last;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_CROP_ENC_CBCR_WIDTH);

	first = line->crop.top;
	last = line->crop.top + line->crop.height - 1;
	अगर (p == V4L2_PIX_FMT_NV12 || p == V4L2_PIX_FMT_NV21) अणु
		first = line->crop.top / 2;
		last = line->crop.top / 2 + line->crop.height / 2 - 1;
	पूर्ण
	reg = (first << 16) | last;
	ग_लिखोl_relaxed(reg, vfe->base + VFE_0_CROP_ENC_CBCR_HEIGHT);
पूर्ण

अटल व्योम vfe_set_clamp_cfg(काष्ठा vfe_device *vfe)
अणु
	u32 val = VFE_0_CLAMP_ENC_MAX_CFG_CH0 |
		VFE_0_CLAMP_ENC_MAX_CFG_CH1 |
		VFE_0_CLAMP_ENC_MAX_CFG_CH2;

	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CLAMP_ENC_MAX_CFG);

	val = VFE_0_CLAMP_ENC_MIN_CFG_CH0 |
		VFE_0_CLAMP_ENC_MIN_CFG_CH1 |
		VFE_0_CLAMP_ENC_MIN_CFG_CH2;

	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CLAMP_ENC_MIN_CFG);
पूर्ण

अटल व्योम vfe_set_qos(काष्ठा vfe_device *vfe)
अणु
	u32 val = VFE_0_BUS_BDG_QOS_CFG_0_CFG;
	u32 val7 = VFE_0_BUS_BDG_QOS_CFG_7_CFG;

	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_0);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_1);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_2);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_3);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_4);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_5);
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_BUS_BDG_QOS_CFG_6);
	ग_लिखोl_relaxed(val7, vfe->base + VFE_0_BUS_BDG_QOS_CFG_7);
पूर्ण

अटल व्योम vfe_set_ds(काष्ठा vfe_device *vfe)
अणु
	/* empty */
पूर्ण

अटल व्योम vfe_set_cgc_override(काष्ठा vfe_device *vfe, u8 wm, u8 enable)
अणु
	u32 val = VFE_0_CGC_OVERRIDE_1_IMAGE_Mx_CGC_OVERRIDE(wm);

	अगर (enable)
		vfe_reg_set(vfe, VFE_0_CGC_OVERRIDE_1, val);
	अन्यथा
		vfe_reg_clr(vfe, VFE_0_CGC_OVERRIDE_1, val);

	wmb();
पूर्ण

अटल व्योम vfe_set_camअगर_cfg(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line)
अणु
	u32 val;

	चयन (line->fmt[MSM_VFE_PAD_SINK].code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_YCBYCR;
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_YCRYCB;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	शेष:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_CBYCRY;
		अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_CRYCBY;
		अवरोध;
	पूर्ण

	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CORE_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].width * 2;
	val |= line->fmt[MSM_VFE_PAD_SINK].height << 16;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_FRAME_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].width * 2 - 1;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_WINDOW_WIDTH_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].height - 1;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_WINDOW_HEIGHT_CFG);

	val = 0xffffffff;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_SUBSAMPLE_CFG_0);

	val = 0xffffffff;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_IRQ_SUBSAMPLE_PATTERN);

	val = VFE_0_RDI_CFG_x_MIPI_EN_BITS;
	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(0), val);

	val = VFE_0_CAMIF_CFG_VFE_OUTPUT_EN;
	ग_लिखोl_relaxed(val, vfe->base + VFE_0_CAMIF_CFG);
पूर्ण

अटल व्योम vfe_set_camअगर_cmd(काष्ठा vfe_device *vfe, u8 enable)
अणु
	u32 cmd;

	cmd = VFE_0_CAMIF_CMD_CLEAR_CAMIF_STATUS | VFE_0_CAMIF_CMD_NO_CHANGE;
	ग_लिखोl_relaxed(cmd, vfe->base + VFE_0_CAMIF_CMD);
	wmb();

	अगर (enable)
		cmd = VFE_0_CAMIF_CMD_ENABLE_FRAME_BOUNDARY;
	अन्यथा
		cmd = VFE_0_CAMIF_CMD_DISABLE_FRAME_BOUNDARY;

	ग_लिखोl_relaxed(cmd, vfe->base + VFE_0_CAMIF_CMD);
पूर्ण

अटल व्योम vfe_set_module_cfg(काष्ठा vfe_device *vfe, u8 enable)
अणु
	u32 val = VFE_0_MODULE_CFG_DEMUX |
		  VFE_0_MODULE_CFG_CHROMA_UPSAMPLE |
		  VFE_0_MODULE_CFG_SCALE_ENC |
		  VFE_0_MODULE_CFG_CROP_ENC;

	अगर (enable)
		ग_लिखोl_relaxed(val, vfe->base + VFE_0_MODULE_CFG);
	अन्यथा
		ग_लिखोl_relaxed(0x0, vfe->base + VFE_0_MODULE_CFG);
पूर्ण

अटल पूर्णांक vfe_camअगर_रुको_क्रम_stop(काष्ठा vfe_device *vfe, काष्ठा device *dev)
अणु
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(vfe->base + VFE_0_CAMIF_STATUS,
				 val,
				 (val & VFE_0_CAMIF_STATUS_HALT),
				 CAMIF_TIMEOUT_SLEEP_US,
				 CAMIF_TIMEOUT_ALL_US);
	अगर (ret < 0)
		dev_err(dev, "%s: camif stop timeout\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम vfe_isr_पढ़ो(काष्ठा vfe_device *vfe, u32 *value0, u32 *value1)
अणु
	*value0 = पढ़ोl_relaxed(vfe->base + VFE_0_IRQ_STATUS_0);
	*value1 = पढ़ोl_relaxed(vfe->base + VFE_0_IRQ_STATUS_1);

	ग_लिखोl_relaxed(*value0, vfe->base + VFE_0_IRQ_CLEAR_0);
	ग_लिखोl_relaxed(*value1, vfe->base + VFE_0_IRQ_CLEAR_1);

	wmb();
	ग_लिखोl_relaxed(VFE_0_IRQ_CMD_GLOBAL_CLEAR, vfe->base + VFE_0_IRQ_CMD);
पूर्ण

अटल व्योम vfe_violation_पढ़ो(काष्ठा vfe_device *vfe)
अणु
	u32 violation = पढ़ोl_relaxed(vfe->base + VFE_0_VIOLATION_STATUS);

	pr_err_ratelimited("VFE: violation = 0x%08x\n", violation);
पूर्ण

/*
 * vfe_isr - VFE module पूर्णांकerrupt handler
 * @irq: Interrupt line
 * @dev: VFE device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t vfe_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा vfe_device *vfe = dev;
	u32 value0, value1;
	पूर्णांक i, j;

	vfe->ops->isr_पढ़ो(vfe, &value0, &value1);

	dev_dbg(vfe->camss->dev, "VFE: status0 = 0x%08x, status1 = 0x%08x\n",
		value0, value1);

	अगर (value0 & VFE_0_IRQ_STATUS_0_RESET_ACK)
		vfe->isr_ops.reset_ack(vfe);

	अगर (value1 & VFE_0_IRQ_STATUS_1_VIOLATION)
		vfe->ops->violation_पढ़ो(vfe);

	अगर (value1 & VFE_0_IRQ_STATUS_1_BUS_BDG_HALT_ACK)
		vfe->isr_ops.halt_ack(vfe);

	क्रम (i = VFE_LINE_RDI0; i <= VFE_LINE_PIX; i++)
		अगर (value0 & VFE_0_IRQ_STATUS_0_line_n_REG_UPDATE(i))
			vfe->isr_ops.reg_update(vfe, i);

	अगर (value0 & VFE_0_IRQ_STATUS_0_CAMIF_SOF)
		vfe->isr_ops.sof(vfe, VFE_LINE_PIX);

	क्रम (i = VFE_LINE_RDI0; i <= VFE_LINE_RDI2; i++)
		अगर (value1 & VFE_0_IRQ_STATUS_1_RDIn_SOF(i))
			vfe->isr_ops.sof(vfe, i);

	क्रम (i = 0; i < MSM_VFE_COMPOSITE_IRQ_NUM; i++)
		अगर (value0 & VFE_0_IRQ_STATUS_0_IMAGE_COMPOSITE_DONE_n(i)) अणु
			vfe->isr_ops.comp_करोne(vfe, i);
			क्रम (j = 0; j < ARRAY_SIZE(vfe->wm_output_map); j++)
				अगर (vfe->wm_output_map[j] == VFE_LINE_PIX)
					value0 &= ~VFE_0_IRQ_MASK_0_IMAGE_MASTER_n_PING_PONG(j);
		पूर्ण

	क्रम (i = 0; i < MSM_VFE_IMAGE_MASTERS_NUM; i++)
		अगर (value0 & VFE_0_IRQ_STATUS_0_IMAGE_MASTER_n_PING_PONG(i))
			vfe->isr_ops.wm_करोne(vfe, i);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * vfe_pm_करोमुख्य_off - Disable घातer करोमुख्यs specअगरic to this VFE.
 * @vfe: VFE Device
 */
अटल व्योम vfe_pm_करोमुख्य_off(काष्ठा vfe_device *vfe)
अणु
	/* nop */
पूर्ण

/*
 * vfe_pm_करोमुख्य_on - Enable घातer करोमुख्यs specअगरic to this VFE.
 * @vfe: VFE Device
 */
अटल पूर्णांक vfe_pm_करोमुख्य_on(काष्ठा vfe_device *vfe)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vfe_hw_ops_gen1 vfe_ops_gen1_4_1 = अणु
	.bus_connect_wm_to_rdi = vfe_bus_connect_wm_to_rdi,
	.bus_disconnect_wm_from_rdi = vfe_bus_disconnect_wm_from_rdi,
	.bus_enable_wr_अगर = vfe_bus_enable_wr_अगर,
	.bus_reload_wm = vfe_bus_reload_wm,
	.camअगर_रुको_क्रम_stop = vfe_camअगर_रुको_क्रम_stop,
	.enable_irq_common = vfe_enable_irq_common,
	.enable_irq_pix_line = vfe_enable_irq_pix_line,
	.enable_irq_wm_line = vfe_enable_irq_wm_line,
	.get_ub_size = vfe_get_ub_size,
	.halt_clear = vfe_halt_clear,
	.halt_request = vfe_halt_request,
	.set_camअगर_cfg = vfe_set_camअगर_cfg,
	.set_camअगर_cmd = vfe_set_camअगर_cmd,
	.set_cgc_override = vfe_set_cgc_override,
	.set_clamp_cfg = vfe_set_clamp_cfg,
	.set_crop_cfg = vfe_set_crop_cfg,
	.set_demux_cfg = vfe_set_demux_cfg,
	.set_ds = vfe_set_ds,
	.set_module_cfg = vfe_set_module_cfg,
	.set_qos = vfe_set_qos,
	.set_rdi_cid = vfe_set_rdi_cid,
	.set_realign_cfg = vfe_set_realign_cfg,
	.set_scale_cfg = vfe_set_scale_cfg,
	.set_xbar_cfg = vfe_set_xbar_cfg,
	.wm_enable = vfe_wm_enable,
	.wm_frame_based = vfe_wm_frame_based,
	.wm_get_ping_pong_status = vfe_wm_get_ping_pong_status,
	.wm_line_based = vfe_wm_line_based,
	.wm_set_framedrop_pattern = vfe_wm_set_framedrop_pattern,
	.wm_set_framedrop_period = vfe_wm_set_framedrop_period,
	.wm_set_ping_addr = vfe_wm_set_ping_addr,
	.wm_set_pong_addr = vfe_wm_set_pong_addr,
	.wm_set_subsample = vfe_wm_set_subsample,
	.wm_set_ub_cfg = vfe_wm_set_ub_cfg,
पूर्ण;

अटल व्योम vfe_subdev_init(काष्ठा device *dev, काष्ठा vfe_device *vfe)
अणु
	vfe->isr_ops = vfe_isr_ops_gen1;
	vfe->ops_gen1 = &vfe_ops_gen1_4_1;
	vfe->video_ops = vfe_video_ops_gen1;

	vfe->line_num = VFE_LINE_NUM_GEN1;
पूर्ण

स्थिर काष्ठा vfe_hw_ops vfe_ops_4_1 = अणु
	.global_reset = vfe_global_reset,
	.hw_version_पढ़ो = vfe_hw_version_पढ़ो,
	.isr_पढ़ो = vfe_isr_पढ़ो,
	.isr = vfe_isr,
	.pm_करोमुख्य_off = vfe_pm_करोमुख्य_off,
	.pm_करोमुख्य_on = vfe_pm_करोमुख्य_on,
	.reg_update_clear = vfe_reg_update_clear,
	.reg_update = vfe_reg_update,
	.subdev_init = vfe_subdev_init,
	.vfe_disable = vfe_gen1_disable,
	.vfe_enable = vfe_gen1_enable,
	.vfe_halt = vfe_gen1_halt,
	.violation_पढ़ो = vfe_violation_पढ़ो,
पूर्ण;
