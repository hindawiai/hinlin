<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 *
 * JPEG encoder
 * ------------
 * The VPU JPEG encoder produces JPEG baseline sequential क्रमmat.
 * The quantization coefficients are 8-bit values, complying with
 * the baseline specअगरication. Thereक्रमe, it requires
 * luma and chroma quantization tables. The hardware करोes entropy
 * encoding using पूर्णांकernal Huffman tables, as specअगरied in the JPEG
 * specअगरication.
 *
 * In other words, only the luma and chroma quantization tables are
 * required क्रम the encoding operation.
 *
 * Quantization luma table values are written to रेजिस्टरs
 * VEPU_swreg_0-VEPU_swreg_15, and chroma table values to
 * VEPU_swreg_16-VEPU_swreg_31. A special order is needed, neither
 * zigzag, nor linear.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश "hantro_jpeg.h"
#समावेश "hantro.h"
#समावेश "hantro_v4l2.h"
#समावेश "hantro_hw.h"
#समावेश "rk3399_vpu_regs.h"

#घोषणा VEPU_JPEG_QUANT_TABLE_COUNT 16

अटल व्योम rk3399_vpu_set_src_img_ctrl(काष्ठा hantro_dev *vpu,
					काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt = &ctx->src_fmt;
	u32 reg;

	/*
	 * The pix fmt width/height are alपढ़ोy macroblock aligned
	 * by .vidioc_s_fmt_vid_cap_mplane() callback
	 */
	reg = VEPU_REG_IN_IMG_CTRL_ROW_LEN(pix_fmt->width);
	vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_INPUT_LUMA_INFO);

	reg = VEPU_REG_IN_IMG_CTRL_OVRFLR_D4(0) |
	      VEPU_REG_IN_IMG_CTRL_OVRFLB(0);
	/*
	 * This रेजिस्टर controls the input crop, as the offset
	 * from the right/bottom within the last macroblock. The offset from the
	 * right must be भागided by 4 and so the crop must be aligned to 4 pixels
	 * horizontally.
	 */
	vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_ENC_OVER_FILL_STRM_OFFSET);

	reg = VEPU_REG_IN_IMG_CTRL_FMT(ctx->vpu_src_fmt->enc_fmt);
	vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_ENC_CTRL1);
पूर्ण

अटल व्योम rk3399_vpu_jpeg_enc_set_buffers(काष्ठा hantro_dev *vpu,
					    काष्ठा hantro_ctx *ctx,
					    काष्ठा vb2_buffer *src_buf)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt = &ctx->src_fmt;
	dma_addr_t src[3];

	WARN_ON(pix_fmt->num_planes > 3);

	vepu_ग_लिखो_relaxed(vpu, ctx->jpeg_enc.bounce_buffer.dma,
			   VEPU_REG_ADDR_OUTPUT_STREAM);
	vepu_ग_लिखो_relaxed(vpu, ctx->jpeg_enc.bounce_buffer.size,
			   VEPU_REG_STR_BUF_LIMIT);

	अगर (pix_fmt->num_planes == 1) अणु
		src[0] = vb2_dma_contig_plane_dma_addr(src_buf, 0);
		vepu_ग_लिखो_relaxed(vpu, src[0], VEPU_REG_ADDR_IN_PLANE_0);
	पूर्ण अन्यथा अगर (pix_fmt->num_planes == 2) अणु
		src[0] = vb2_dma_contig_plane_dma_addr(src_buf, 0);
		src[1] = vb2_dma_contig_plane_dma_addr(src_buf, 1);
		vepu_ग_लिखो_relaxed(vpu, src[0], VEPU_REG_ADDR_IN_PLANE_0);
		vepu_ग_लिखो_relaxed(vpu, src[1], VEPU_REG_ADDR_IN_PLANE_1);
	पूर्ण अन्यथा अणु
		src[0] = vb2_dma_contig_plane_dma_addr(src_buf, 0);
		src[1] = vb2_dma_contig_plane_dma_addr(src_buf, 1);
		src[2] = vb2_dma_contig_plane_dma_addr(src_buf, 2);
		vepu_ग_लिखो_relaxed(vpu, src[0], VEPU_REG_ADDR_IN_PLANE_0);
		vepu_ग_लिखो_relaxed(vpu, src[1], VEPU_REG_ADDR_IN_PLANE_1);
		vepu_ग_लिखो_relaxed(vpu, src[2], VEPU_REG_ADDR_IN_PLANE_2);
	पूर्ण
पूर्ण

अटल व्योम
rk3399_vpu_jpeg_enc_set_qtable(काष्ठा hantro_dev *vpu,
			       अचिन्हित अक्षर *luma_qtable,
			       अचिन्हित अक्षर *chroma_qtable)
अणु
	u32 reg, i;
	__be32 *luma_qtable_p;
	__be32 *chroma_qtable_p;

	luma_qtable_p = (__be32 *)luma_qtable;
	chroma_qtable_p = (__be32 *)chroma_qtable;

	/*
	 * Quantization table रेजिस्टरs must be written in contiguous blocks.
	 * DO NOT collapse the below two "for" loops पूर्णांकo one.
	 */
	क्रम (i = 0; i < VEPU_JPEG_QUANT_TABLE_COUNT; i++) अणु
		reg = get_unaligned_be32(&luma_qtable_p[i]);
		vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_JPEG_LUMA_QUAT(i));
	पूर्ण

	क्रम (i = 0; i < VEPU_JPEG_QUANT_TABLE_COUNT; i++) अणु
		reg = get_unaligned_be32(&chroma_qtable_p[i]);
		vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_JPEG_CHROMA_QUAT(i));
	पूर्ण
पूर्ण

व्योम rk3399_vpu_jpeg_enc_run(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा hantro_jpeg_ctx jpeg_ctx;
	u32 reg;

	src_buf = hantro_get_src_buf(ctx);
	dst_buf = hantro_get_dst_buf(ctx);

	hantro_start_prepare_run(ctx);

	स_रखो(&jpeg_ctx, 0, माप(jpeg_ctx));
	jpeg_ctx.buffer = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	jpeg_ctx.width = ctx->dst_fmt.width;
	jpeg_ctx.height = ctx->dst_fmt.height;
	jpeg_ctx.quality = ctx->jpeg_quality;
	hantro_jpeg_header_assemble(&jpeg_ctx);

	/* Switch to JPEG encoder mode beक्रमe writing रेजिस्टरs */
	vepu_ग_लिखो_relaxed(vpu, VEPU_REG_ENCODE_FORMAT_JPEG,
			   VEPU_REG_ENCODE_START);

	rk3399_vpu_set_src_img_ctrl(vpu, ctx);
	rk3399_vpu_jpeg_enc_set_buffers(vpu, ctx, &src_buf->vb2_buf);
	rk3399_vpu_jpeg_enc_set_qtable(vpu,
				       hantro_jpeg_get_qtable(0),
				       hantro_jpeg_get_qtable(1));

	reg = VEPU_REG_OUTPUT_SWAP32
		| VEPU_REG_OUTPUT_SWAP16
		| VEPU_REG_OUTPUT_SWAP8
		| VEPU_REG_INPUT_SWAP8
		| VEPU_REG_INPUT_SWAP16
		| VEPU_REG_INPUT_SWAP32;
	/* Make sure that all रेजिस्टरs are written at this poपूर्णांक. */
	vepu_ग_लिखो(vpu, reg, VEPU_REG_DATA_ENDIAN);

	reg = VEPU_REG_AXI_CTRL_BURST_LEN(16);
	vepu_ग_लिखो_relaxed(vpu, reg, VEPU_REG_AXI_CTRL);

	reg = VEPU_REG_MB_WIDTH(MB_WIDTH(ctx->src_fmt.width))
		| VEPU_REG_MB_HEIGHT(MB_HEIGHT(ctx->src_fmt.height))
		| VEPU_REG_FRAME_TYPE_INTRA
		| VEPU_REG_ENCODE_FORMAT_JPEG
		| VEPU_REG_ENCODE_ENABLE;

	/* Kick the watchकरोg and start encoding */
	hantro_end_prepare_run(ctx);
	vepu_ग_लिखो(vpu, reg, VEPU_REG_ENCODE_START);
पूर्ण
