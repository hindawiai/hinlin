<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 *	Jeffy Chen <jeffy.chen@rock-chips.com>
 */

#समावेश <linux/clk.h>

#समावेश "hantro.h"
#समावेश "hantro_jpeg.h"
#समावेश "rk3399_vpu_regs.h"

#घोषणा RK3399_ACLK_MAX_FREQ (400 * 1000 * 1000)

/*
 * Supported क्रमmats.
 */

अटल स्थिर काष्ठा hantro_fmt rk3399_vpu_enc_fmts[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_YUV420M,
		.codec_mode = HANTRO_MODE_NONE,
		.enc_fmt = RK3288_VPU_ENC_FMT_YUV420P,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV12M,
		.codec_mode = HANTRO_MODE_NONE,
		.enc_fmt = RK3288_VPU_ENC_FMT_YUV420SP,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.codec_mode = HANTRO_MODE_NONE,
		.enc_fmt = RK3288_VPU_ENC_FMT_YUYV422,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.codec_mode = HANTRO_MODE_NONE,
		.enc_fmt = RK3288_VPU_ENC_FMT_UYVY422,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_JPEG,
		.codec_mode = HANTRO_MODE_JPEG_ENC,
		.max_depth = 2,
		.header_size = JPEG_HEADER_SIZE,
		.frmsize = अणु
			.min_width = 96,
			.max_width = 8192,
			.step_width = MB_DIM,
			.min_height = 32,
			.max_height = 8192,
			.step_height = MB_DIM,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_fmt rk3399_vpu_dec_fmts[] = अणु
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
			.step_width = MB_DIM,
			.min_height = 48,
			.max_height = 2160,
			.step_height = MB_DIM,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t rk3399_vepu_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hantro_dev *vpu = dev_id;
	क्रमागत vb2_buffer_state state;
	u32 status;

	status = vepu_पढ़ो(vpu, VEPU_REG_INTERRUPT);
	state = (status & VEPU_REG_INTERRUPT_FRAME_READY) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_ERROR;

	vepu_ग_लिखो(vpu, 0, VEPU_REG_INTERRUPT);
	vepu_ग_लिखो(vpu, 0, VEPU_REG_AXI_CTRL);

	hantro_irq_करोne(vpu, state);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rk3399_vdpu_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hantro_dev *vpu = dev_id;
	क्रमागत vb2_buffer_state state;
	u32 status;

	status = vdpu_पढ़ो(vpu, VDPU_REG_INTERRUPT);
	state = (status & VDPU_REG_INTERRUPT_DEC_IRQ) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_ERROR;

	vdpu_ग_लिखो(vpu, 0, VDPU_REG_INTERRUPT);
	vdpu_ग_लिखो(vpu, 0, VDPU_REG_AXI_CTRL);

	hantro_irq_करोne(vpu, state);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rk3399_vpu_hw_init(काष्ठा hantro_dev *vpu)
अणु
	/* Bump ACLK to max. possible freq. to improve perक्रमmance. */
	clk_set_rate(vpu->घड़ीs[0].clk, RK3399_ACLK_MAX_FREQ);
	वापस 0;
पूर्ण

अटल व्योम rk3399_vpu_enc_reset(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	vepu_ग_लिखो(vpu, VEPU_REG_INTERRUPT_DIS_BIT, VEPU_REG_INTERRUPT);
	vepu_ग_लिखो(vpu, 0, VEPU_REG_ENCODE_START);
	vepu_ग_लिखो(vpu, 0, VEPU_REG_AXI_CTRL);
पूर्ण

अटल व्योम rk3399_vpu_dec_reset(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	vdpu_ग_लिखो(vpu, VDPU_REG_INTERRUPT_DEC_IRQ_DIS, VDPU_REG_INTERRUPT);
	vdpu_ग_लिखो(vpu, 0, VDPU_REG_EN_FLAGS);
	vdpu_ग_लिखो(vpu, 1, VDPU_REG_SOFT_RESET);
पूर्ण

/*
 * Supported codec ops.
 */

अटल स्थिर काष्ठा hantro_codec_ops rk3399_vpu_codec_ops[] = अणु
	[HANTRO_MODE_JPEG_ENC] = अणु
		.run = rk3399_vpu_jpeg_enc_run,
		.reset = rk3399_vpu_enc_reset,
		.init = hantro_jpeg_enc_init,
		.निकास = hantro_jpeg_enc_निकास,
	पूर्ण,
	[HANTRO_MODE_MPEG2_DEC] = अणु
		.run = rk3399_vpu_mpeg2_dec_run,
		.reset = rk3399_vpu_dec_reset,
		.init = hantro_mpeg2_dec_init,
		.निकास = hantro_mpeg2_dec_निकास,
	पूर्ण,
	[HANTRO_MODE_VP8_DEC] = अणु
		.run = rk3399_vpu_vp8_dec_run,
		.reset = rk3399_vpu_dec_reset,
		.init = hantro_vp8_dec_init,
		.निकास = hantro_vp8_dec_निकास,
	पूर्ण,
पूर्ण;

/*
 * VPU variant.
 */

अटल स्थिर काष्ठा hantro_irq rk3399_irqs[] = अणु
	अणु "vepu", rk3399_vepu_irq पूर्ण,
	अणु "vdpu", rk3399_vdpu_irq पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rk3399_clk_names[] = अणु
	"aclk", "hclk"
पूर्ण;

स्थिर काष्ठा hantro_variant rk3399_vpu_variant = अणु
	.enc_offset = 0x0,
	.enc_fmts = rk3399_vpu_enc_fmts,
	.num_enc_fmts = ARRAY_SIZE(rk3399_vpu_enc_fmts),
	.dec_offset = 0x400,
	.dec_fmts = rk3399_vpu_dec_fmts,
	.num_dec_fmts = ARRAY_SIZE(rk3399_vpu_dec_fmts),
	.codec = HANTRO_JPEG_ENCODER | HANTRO_MPEG2_DECODER |
		 HANTRO_VP8_DECODER,
	.codec_ops = rk3399_vpu_codec_ops,
	.irqs = rk3399_irqs,
	.num_irqs = ARRAY_SIZE(rk3399_irqs),
	.init = rk3399_vpu_hw_init,
	.clk_names = rk3399_clk_names,
	.num_घड़ीs = ARRAY_SIZE(rk3399_clk_names)
पूर्ण;

अटल स्थिर काष्ठा hantro_irq rk3328_irqs[] = अणु
	अणु "vdpu", rk3399_vdpu_irq पूर्ण,
पूर्ण;

स्थिर काष्ठा hantro_variant rk3328_vpu_variant = अणु
	.dec_offset = 0x400,
	.dec_fmts = rk3399_vpu_dec_fmts,
	.num_dec_fmts = ARRAY_SIZE(rk3399_vpu_dec_fmts),
	.codec = HANTRO_MPEG2_DECODER | HANTRO_VP8_DECODER,
	.codec_ops = rk3399_vpu_codec_ops,
	.irqs = rk3328_irqs,
	.num_irqs = ARRAY_SIZE(rk3328_irqs),
	.init = rk3399_vpu_hw_init,
	.clk_names = rk3399_clk_names,
	.num_घड़ीs = ARRAY_SIZE(rk3399_clk_names),
पूर्ण;
