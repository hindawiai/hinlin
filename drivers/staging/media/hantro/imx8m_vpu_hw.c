<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2019 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>

#समावेश "hantro.h"
#समावेश "hantro_jpeg.h"
#समावेश "hantro_g1_regs.h"

#घोषणा CTRL_SOFT_RESET		0x00
#घोषणा RESET_G1		BIT(1)
#घोषणा RESET_G2		BIT(0)

#घोषणा CTRL_CLOCK_ENABLE	0x04
#घोषणा CLOCK_G1		BIT(1)
#घोषणा CLOCK_G2		BIT(0)

#घोषणा CTRL_G1_DEC_FUSE	0x08
#घोषणा CTRL_G1_PP_FUSE		0x0c
#घोषणा CTRL_G2_DEC_FUSE	0x10

अटल व्योम imx8m_soft_reset(काष्ठा hantro_dev *vpu, u32 reset_bits)
अणु
	u32 val;

	/* Assert */
	val = पढ़ोl(vpu->ctrl_base + CTRL_SOFT_RESET);
	val &= ~reset_bits;
	ग_लिखोl(val, vpu->ctrl_base + CTRL_SOFT_RESET);

	udelay(2);

	/* Release */
	val = पढ़ोl(vpu->ctrl_base + CTRL_SOFT_RESET);
	val |= reset_bits;
	ग_लिखोl(val, vpu->ctrl_base + CTRL_SOFT_RESET);
पूर्ण

अटल व्योम imx8m_clk_enable(काष्ठा hantro_dev *vpu, u32 घड़ी_bits)
अणु
	u32 val;

	val = पढ़ोl(vpu->ctrl_base + CTRL_CLOCK_ENABLE);
	val |= घड़ी_bits;
	ग_लिखोl(val, vpu->ctrl_base + CTRL_CLOCK_ENABLE);
पूर्ण

अटल पूर्णांक imx8mq_runसमय_resume(काष्ठा hantro_dev *vpu)
अणु
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(vpu->variant->num_घड़ीs, vpu->घड़ीs);
	अगर (ret) अणु
		dev_err(vpu->dev, "Failed to enable clocks\n");
		वापस ret;
	पूर्ण

	imx8m_soft_reset(vpu, RESET_G1 | RESET_G2);
	imx8m_clk_enable(vpu, CLOCK_G1 | CLOCK_G2);

	/* Set values of the fuse रेजिस्टरs */
	ग_लिखोl(0xffffffff, vpu->ctrl_base + CTRL_G1_DEC_FUSE);
	ग_लिखोl(0xffffffff, vpu->ctrl_base + CTRL_G1_PP_FUSE);
	ग_लिखोl(0xffffffff, vpu->ctrl_base + CTRL_G2_DEC_FUSE);

	clk_bulk_disable_unprepare(vpu->variant->num_घड़ीs, vpu->घड़ीs);

	वापस 0;
पूर्ण

/*
 * Supported क्रमmats.
 */

अटल स्थिर काष्ठा hantro_fmt imx8m_vpu_postproc_fmts[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.codec_mode = HANTRO_MODE_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_fmt imx8m_vpu_dec_fmts[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.codec_mode = HANTRO_MODE_NONE,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_MPEG2_SLICE,
		.codec_mode = HANTRO_MODE_MPEG2_DEC,
		.max_depth = 2,
		.frmsize = अणु
			.min_width = 48,
			.max_width = 1920,
			.step_width = MB_DIM,
			.min_height = 48,
			.max_height = 1088,
			.step_height = MB_DIM,
		पूर्ण,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_VP8_FRAME,
		.codec_mode = HANTRO_MODE_VP8_DEC,
		.max_depth = 2,
		.frmsize = अणु
			.min_width = 48,
			.max_width = 3840,
			.step_width = 16,
			.min_height = 48,
			.max_height = 2160,
			.step_height = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_H264_SLICE,
		.codec_mode = HANTRO_MODE_H264_DEC,
		.max_depth = 2,
		.frmsize = अणु
			.min_width = 48,
			.max_width = 3840,
			.step_width = MB_DIM,
			.min_height = 48,
			.max_height = 2160,
			.step_height = MB_DIM,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t imx8m_vpu_g1_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hantro_dev *vpu = dev_id;
	क्रमागत vb2_buffer_state state;
	u32 status;

	status = vdpu_पढ़ो(vpu, G1_REG_INTERRUPT);
	state = (status & G1_REG_INTERRUPT_DEC_RDY_INT) ?
		 VB2_BUF_STATE_DONE : VB2_BUF_STATE_ERROR;

	vdpu_ग_लिखो(vpu, 0, G1_REG_INTERRUPT);
	vdpu_ग_लिखो(vpu, G1_REG_CONFIG_DEC_CLK_GATE_E, G1_REG_CONFIG);

	hantro_irq_करोne(vpu, state);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx8mq_vpu_hw_init(काष्ठा hantro_dev *vpu)
अणु
	vpu->dec_base = vpu->reg_bases[0];
	vpu->ctrl_base = vpu->reg_bases[vpu->variant->num_regs - 1];

	वापस 0;
पूर्ण

अटल व्योम imx8m_vpu_g1_reset(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	imx8m_soft_reset(vpu, RESET_G1);
पूर्ण

/*
 * Supported codec ops.
 */

अटल स्थिर काष्ठा hantro_codec_ops imx8mq_vpu_codec_ops[] = अणु
	[HANTRO_MODE_MPEG2_DEC] = अणु
		.run = hantro_g1_mpeg2_dec_run,
		.reset = imx8m_vpu_g1_reset,
		.init = hantro_mpeg2_dec_init,
		.निकास = hantro_mpeg2_dec_निकास,
	पूर्ण,
	[HANTRO_MODE_VP8_DEC] = अणु
		.run = hantro_g1_vp8_dec_run,
		.reset = imx8m_vpu_g1_reset,
		.init = hantro_vp8_dec_init,
		.निकास = hantro_vp8_dec_निकास,
	पूर्ण,
	[HANTRO_MODE_H264_DEC] = अणु
		.run = hantro_g1_h264_dec_run,
		.reset = imx8m_vpu_g1_reset,
		.init = hantro_h264_dec_init,
		.निकास = hantro_h264_dec_निकास,
	पूर्ण,
पूर्ण;

/*
 * VPU variants.
 */

अटल स्थिर काष्ठा hantro_irq imx8mq_irqs[] = अणु
	अणु "g1", imx8m_vpu_g1_irq पूर्ण,
	अणु "g2", शून्य /* TODO: imx8m_vpu_g2_irq */ पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx8mq_clk_names[] = अणु "g1", "g2", "bus" पूर्ण;
अटल स्थिर अक्षर * स्थिर imx8mq_reg_names[] = अणु "g1", "g2", "ctrl" पूर्ण;

स्थिर काष्ठा hantro_variant imx8mq_vpu_variant = अणु
	.dec_fmts = imx8m_vpu_dec_fmts,
	.num_dec_fmts = ARRAY_SIZE(imx8m_vpu_dec_fmts),
	.postproc_fmts = imx8m_vpu_postproc_fmts,
	.num_postproc_fmts = ARRAY_SIZE(imx8m_vpu_postproc_fmts),
	.postproc_regs = &hantro_g1_postproc_regs,
	.codec = HANTRO_MPEG2_DECODER | HANTRO_VP8_DECODER |
		 HANTRO_H264_DECODER,
	.codec_ops = imx8mq_vpu_codec_ops,
	.init = imx8mq_vpu_hw_init,
	.runसमय_resume = imx8mq_runसमय_resume,
	.irqs = imx8mq_irqs,
	.num_irqs = ARRAY_SIZE(imx8mq_irqs),
	.clk_names = imx8mq_clk_names,
	.num_घड़ीs = ARRAY_SIZE(imx8mq_clk_names),
	.reg_names = imx8mq_reg_names,
	.num_regs = ARRAY_SIZE(imx8mq_reg_names)
पूर्ण;
