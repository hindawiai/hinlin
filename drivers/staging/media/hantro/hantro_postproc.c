<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro G1 post-processor support
 *
 * Copyright (C) 2019 Collabora, Ltd.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/types.h>

#समावेश "hantro.h"
#समावेश "hantro_hw.h"
#समावेश "hantro_g1_regs.h"

#घोषणा HANTRO_PP_REG_WRITE(vpu, reg_name, val) \
अणु \
	hantro_reg_ग_लिखो(vpu, \
			 &(vpu)->variant->postproc_regs->reg_name, \
			 val); \
पूर्ण

#घोषणा HANTRO_PP_REG_WRITE_S(vpu, reg_name, val) \
अणु \
	hantro_reg_ग_लिखो_s(vpu, \
			   &(vpu)->variant->postproc_regs->reg_name, \
			   val); \
पूर्ण

#घोषणा VPU_PP_IN_YUYV			0x0
#घोषणा VPU_PP_IN_NV12			0x1
#घोषणा VPU_PP_IN_YUV420		0x2
#घोषणा VPU_PP_IN_YUV240_TILED		0x5
#घोषणा VPU_PP_OUT_RGB			0x0
#घोषणा VPU_PP_OUT_YUYV			0x3

स्थिर काष्ठा hantro_postproc_regs hantro_g1_postproc_regs = अणु
	.pipeline_en = अणुG1_REG_PP_INTERRUPT, 1, 0x1पूर्ण,
	.max_burst = अणुG1_REG_PP_DEV_CONFIG, 0, 0x1fपूर्ण,
	.clk_gate = अणुG1_REG_PP_DEV_CONFIG, 1, 0x1पूर्ण,
	.out_swap32 = अणुG1_REG_PP_DEV_CONFIG, 5, 0x1पूर्ण,
	.out_endian = अणुG1_REG_PP_DEV_CONFIG, 6, 0x1पूर्ण,
	.out_luma_base = अणुG1_REG_PP_OUT_LUMA_BASE, 0, 0xffffffffपूर्ण,
	.input_width = अणुG1_REG_PP_INPUT_SIZE, 0, 0x1ffपूर्ण,
	.input_height = अणुG1_REG_PP_INPUT_SIZE, 9, 0x1ffपूर्ण,
	.output_width = अणुG1_REG_PP_CONTROL, 4, 0x7ffपूर्ण,
	.output_height = अणुG1_REG_PP_CONTROL, 15, 0x7ffपूर्ण,
	.input_fmt = अणुG1_REG_PP_CONTROL, 29, 0x7पूर्ण,
	.output_fmt = अणुG1_REG_PP_CONTROL, 26, 0x7पूर्ण,
	.orig_width = अणुG1_REG_PP_MASK1_ORIG_WIDTH, 23, 0x1ffपूर्ण,
	.display_width = अणुG1_REG_PP_DISPLAY_WIDTH, 0, 0xfffपूर्ण,
पूर्ण;

व्योम hantro_postproc_enable(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *dst_buf;
	u32 src_pp_fmt, dst_pp_fmt;
	dma_addr_t dst_dma;

	अगर (!vpu->variant->postproc_regs)
		वापस;

	/* Turn on pipeline mode. Must be करोne first. */
	HANTRO_PP_REG_WRITE_S(vpu, pipeline_en, 0x1);

	src_pp_fmt = VPU_PP_IN_NV12;

	चयन (ctx->vpu_dst_fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUYV:
		dst_pp_fmt = VPU_PP_OUT_YUYV;
		अवरोध;
	शेष:
		WARN(1, "output format %d not supported by the post-processor, this wasn't expected.",
		     ctx->vpu_dst_fmt->fourcc);
		dst_pp_fmt = 0;
		अवरोध;
	पूर्ण

	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	dst_dma = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);

	HANTRO_PP_REG_WRITE(vpu, clk_gate, 0x1);
	HANTRO_PP_REG_WRITE(vpu, out_endian, 0x1);
	HANTRO_PP_REG_WRITE(vpu, out_swap32, 0x1);
	HANTRO_PP_REG_WRITE(vpu, max_burst, 16);
	HANTRO_PP_REG_WRITE(vpu, out_luma_base, dst_dma);
	HANTRO_PP_REG_WRITE(vpu, input_width, MB_WIDTH(ctx->dst_fmt.width));
	HANTRO_PP_REG_WRITE(vpu, input_height, MB_HEIGHT(ctx->dst_fmt.height));
	HANTRO_PP_REG_WRITE(vpu, input_fmt, src_pp_fmt);
	HANTRO_PP_REG_WRITE(vpu, output_fmt, dst_pp_fmt);
	HANTRO_PP_REG_WRITE(vpu, output_width, ctx->dst_fmt.width);
	HANTRO_PP_REG_WRITE(vpu, output_height, ctx->dst_fmt.height);
	HANTRO_PP_REG_WRITE(vpu, orig_width, MB_WIDTH(ctx->dst_fmt.width));
	HANTRO_PP_REG_WRITE(vpu, display_width, ctx->dst_fmt.width);
पूर्ण

व्योम hantro_postproc_मुक्त(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < VB2_MAX_FRAME; ++i) अणु
		काष्ठा hantro_aux_buf *priv = &ctx->postproc.dec_q[i];

		अगर (priv->cpu) अणु
			dma_मुक्त_attrs(vpu->dev, priv->size, priv->cpu,
				       priv->dma, priv->attrs);
			priv->cpu = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hantro_postproc_alloc(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा v4l2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	काष्ठा vb2_queue *cap_queue = &m2m_ctx->cap_q_ctx.q;
	अचिन्हित पूर्णांक num_buffers = cap_queue->num_buffers;
	अचिन्हित पूर्णांक i, buf_size;

	buf_size = ctx->dst_fmt.plane_fmt[0].sizeimage +
		   hantro_h264_mv_size(ctx->dst_fmt.width,
				       ctx->dst_fmt.height);

	क्रम (i = 0; i < num_buffers; ++i) अणु
		काष्ठा hantro_aux_buf *priv = &ctx->postproc.dec_q[i];

		/*
		 * The buffers on this queue are meant as पूर्णांकermediate
		 * buffers क्रम the decoder, so no mapping is needed.
		 */
		priv->attrs = DMA_ATTR_NO_KERNEL_MAPPING;
		priv->cpu = dma_alloc_attrs(vpu->dev, buf_size, &priv->dma,
					    GFP_KERNEL, priv->attrs);
		अगर (!priv->cpu)
			वापस -ENOMEM;
		priv->size = buf_size;
	पूर्ण
	वापस 0;
पूर्ण

व्योम hantro_postproc_disable(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	अगर (!vpu->variant->postproc_regs)
		वापस;

	HANTRO_PP_REG_WRITE_S(vpu, pipeline_en, 0x0);
पूर्ण
