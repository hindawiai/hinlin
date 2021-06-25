<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2016 Florent Revest <florent.revest@मुक्त-electrons.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 */

#समावेश <media/videobuf2-dma-contig.h>

#समावेश "cedrus.h"
#समावेश "cedrus_hw.h"
#समावेश "cedrus_regs.h"

/* Default MPEG-2 quantization coefficients, from the specअगरication. */

अटल स्थिर u8 पूर्णांकra_quantization_matrix_शेष[64] = अणु
	8,  16, 16, 19, 16, 19, 22, 22,
	22, 22, 22, 22, 26, 24, 26, 27,
	27, 27, 26, 26, 26, 26, 27, 27,
	27, 29, 29, 29, 34, 34, 34, 29,
	29, 29, 27, 27, 29, 29, 32, 32,
	34, 34, 37, 38, 37, 35, 35, 34,
	35, 38, 38, 40, 40, 40, 48, 48,
	46, 46, 56, 56, 58, 69, 69, 83
पूर्ण;

अटल स्थिर u8 non_पूर्णांकra_quantization_matrix_शेष[64] = अणु
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16
पूर्ण;

अटल क्रमागत cedrus_irq_status cedrus_mpeg2_irq_status(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg;

	reg = cedrus_पढ़ो(dev, VE_DEC_MPEG_STATUS);
	reg &= VE_DEC_MPEG_STATUS_CHECK_MASK;

	अगर (!reg)
		वापस CEDRUS_IRQ_NONE;

	अगर (reg & VE_DEC_MPEG_STATUS_CHECK_ERROR ||
	    !(reg & VE_DEC_MPEG_STATUS_SUCCESS))
		वापस CEDRUS_IRQ_ERROR;

	वापस CEDRUS_IRQ_OK;
पूर्ण

अटल व्योम cedrus_mpeg2_irq_clear(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_STATUS, VE_DEC_MPEG_STATUS_CHECK_MASK);
पूर्ण

अटल व्योम cedrus_mpeg2_irq_disable(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_पढ़ो(dev, VE_DEC_MPEG_CTRL);

	reg &= ~VE_DEC_MPEG_CTRL_IRQ_MASK;

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_CTRL, reg);
पूर्ण

अटल व्योम cedrus_mpeg2_setup(काष्ठा cedrus_ctx *ctx, काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_mpeg2_slice_params *slice_params;
	स्थिर काष्ठा v4l2_mpeg2_sequence *sequence;
	स्थिर काष्ठा v4l2_mpeg2_picture *picture;
	स्थिर काष्ठा v4l2_ctrl_mpeg2_quantization *quantization;
	dma_addr_t src_buf_addr, dst_luma_addr, dst_chroma_addr;
	dma_addr_t fwd_luma_addr, fwd_chroma_addr;
	dma_addr_t bwd_luma_addr, bwd_chroma_addr;
	काष्ठा cedrus_dev *dev = ctx->dev;
	काष्ठा vb2_queue *vq;
	स्थिर u8 *matrix;
	पूर्णांक क्रमward_idx;
	पूर्णांक backward_idx;
	अचिन्हित पूर्णांक i;
	u32 reg;

	slice_params = run->mpeg2.slice_params;
	sequence = &slice_params->sequence;
	picture = &slice_params->picture;

	quantization = run->mpeg2.quantization;

	/* Activate MPEG engine. */
	cedrus_engine_enable(ctx, CEDRUS_CODEC_MPEG2);

	/* Set पूर्णांकra quantization matrix. */

	अगर (quantization && quantization->load_पूर्णांकra_quantiser_matrix)
		matrix = quantization->पूर्णांकra_quantiser_matrix;
	अन्यथा
		matrix = पूर्णांकra_quantization_matrix_शेष;

	क्रम (i = 0; i < 64; i++) अणु
		reg = VE_DEC_MPEG_IQMINPUT_WEIGHT(i, matrix[i]);
		reg |= VE_DEC_MPEG_IQMINPUT_FLAG_INTRA;

		cedrus_ग_लिखो(dev, VE_DEC_MPEG_IQMINPUT, reg);
	पूर्ण

	/* Set non-पूर्णांकra quantization matrix. */

	अगर (quantization && quantization->load_non_पूर्णांकra_quantiser_matrix)
		matrix = quantization->non_पूर्णांकra_quantiser_matrix;
	अन्यथा
		matrix = non_पूर्णांकra_quantization_matrix_शेष;

	क्रम (i = 0; i < 64; i++) अणु
		reg = VE_DEC_MPEG_IQMINPUT_WEIGHT(i, matrix[i]);
		reg |= VE_DEC_MPEG_IQMINPUT_FLAG_NON_INTRA;

		cedrus_ग_लिखो(dev, VE_DEC_MPEG_IQMINPUT, reg);
	पूर्ण

	/* Set MPEG picture header. */

	reg = VE_DEC_MPEG_MP12HDR_SLICE_TYPE(picture->picture_coding_type);
	reg |= VE_DEC_MPEG_MP12HDR_F_CODE(0, 0, picture->f_code[0][0]);
	reg |= VE_DEC_MPEG_MP12HDR_F_CODE(0, 1, picture->f_code[0][1]);
	reg |= VE_DEC_MPEG_MP12HDR_F_CODE(1, 0, picture->f_code[1][0]);
	reg |= VE_DEC_MPEG_MP12HDR_F_CODE(1, 1, picture->f_code[1][1]);
	reg |= VE_DEC_MPEG_MP12HDR_INTRA_DC_PRECISION(picture->पूर्णांकra_dc_precision);
	reg |= VE_DEC_MPEG_MP12HDR_INTRA_PICTURE_STRUCTURE(picture->picture_काष्ठाure);
	reg |= VE_DEC_MPEG_MP12HDR_TOP_FIELD_FIRST(picture->top_field_first);
	reg |= VE_DEC_MPEG_MP12HDR_FRAME_PRED_FRAME_DCT(picture->frame_pred_frame_dct);
	reg |= VE_DEC_MPEG_MP12HDR_CONCEALMENT_MOTION_VECTORS(picture->concealment_motion_vectors);
	reg |= VE_DEC_MPEG_MP12HDR_Q_SCALE_TYPE(picture->q_scale_type);
	reg |= VE_DEC_MPEG_MP12HDR_INTRA_VLC_FORMAT(picture->पूर्णांकra_vlc_क्रमmat);
	reg |= VE_DEC_MPEG_MP12HDR_ALTERNATE_SCAN(picture->alternate_scan);
	reg |= VE_DEC_MPEG_MP12HDR_FULL_PEL_FORWARD_VECTOR(0);
	reg |= VE_DEC_MPEG_MP12HDR_FULL_PEL_BACKWARD_VECTOR(0);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_MP12HDR, reg);

	/* Set frame dimensions. */

	reg = VE_DEC_MPEG_PICCODEDSIZE_WIDTH(sequence->horizontal_size);
	reg |= VE_DEC_MPEG_PICCODEDSIZE_HEIGHT(sequence->vertical_size);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_PICCODEDSIZE, reg);

	reg = VE_DEC_MPEG_PICBOUNDSIZE_WIDTH(ctx->src_fmt.width);
	reg |= VE_DEC_MPEG_PICBOUNDSIZE_HEIGHT(ctx->src_fmt.height);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_PICBOUNDSIZE, reg);

	/* Forward and backward prediction reference buffers. */

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	क्रमward_idx = vb2_find_बारtamp(vq, slice_params->क्रमward_ref_ts, 0);
	fwd_luma_addr = cedrus_dst_buf_addr(ctx, क्रमward_idx, 0);
	fwd_chroma_addr = cedrus_dst_buf_addr(ctx, क्रमward_idx, 1);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_FWD_REF_LUMA_ADDR, fwd_luma_addr);
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_FWD_REF_CHROMA_ADDR, fwd_chroma_addr);

	backward_idx = vb2_find_बारtamp(vq, slice_params->backward_ref_ts, 0);
	bwd_luma_addr = cedrus_dst_buf_addr(ctx, backward_idx, 0);
	bwd_chroma_addr = cedrus_dst_buf_addr(ctx, backward_idx, 1);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_BWD_REF_LUMA_ADDR, bwd_luma_addr);
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_BWD_REF_CHROMA_ADDR, bwd_chroma_addr);

	/* Destination luma and chroma buffers. */

	dst_luma_addr = cedrus_dst_buf_addr(ctx, run->dst->vb2_buf.index, 0);
	dst_chroma_addr = cedrus_dst_buf_addr(ctx, run->dst->vb2_buf.index, 1);

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_REC_LUMA, dst_luma_addr);
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_REC_CHROMA, dst_chroma_addr);

	/* Source offset and length in bits. */

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_VLD_OFFSET,
		     slice_params->data_bit_offset);

	reg = slice_params->bit_size - slice_params->data_bit_offset;
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_VLD_LEN, reg);

	/* Source beginning and end addresses. */

	src_buf_addr = vb2_dma_contig_plane_dma_addr(&run->src->vb2_buf, 0);

	reg = VE_DEC_MPEG_VLD_ADDR_BASE(src_buf_addr);
	reg |= VE_DEC_MPEG_VLD_ADDR_VALID_PIC_DATA;
	reg |= VE_DEC_MPEG_VLD_ADDR_LAST_PIC_DATA;
	reg |= VE_DEC_MPEG_VLD_ADDR_FIRST_PIC_DATA;

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_VLD_ADDR, reg);

	reg = src_buf_addr + DIV_ROUND_UP(slice_params->bit_size, 8);
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_VLD_END_ADDR, reg);

	/* Macroblock address: start at the beginning. */
	reg = VE_DEC_MPEG_MBADDR_Y(0) | VE_DEC_MPEG_MBADDR_X(0);
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_MBADDR, reg);

	/* Clear previous errors. */
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_ERROR, 0);

	/* Clear correct macroblocks रेजिस्टर. */
	cedrus_ग_लिखो(dev, VE_DEC_MPEG_CRTMBADDR, 0);

	/* Enable appropriate पूर्णांकerruptions and components. */

	reg = VE_DEC_MPEG_CTRL_IRQ_MASK | VE_DEC_MPEG_CTRL_MC_NO_WRITEBACK |
	      VE_DEC_MPEG_CTRL_MC_CACHE_EN;

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_CTRL, reg);
पूर्ण

अटल व्योम cedrus_mpeg2_trigger(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg;

	/* Trigger MPEG engine. */
	reg = VE_DEC_MPEG_TRIGGER_HW_MPEG_VLD | VE_DEC_MPEG_TRIGGER_MPEG2 |
	      VE_DEC_MPEG_TRIGGER_MB_BOUNDARY;

	cedrus_ग_लिखो(dev, VE_DEC_MPEG_TRIGGER, reg);
पूर्ण

काष्ठा cedrus_dec_ops cedrus_dec_ops_mpeg2 = अणु
	.irq_clear	= cedrus_mpeg2_irq_clear,
	.irq_disable	= cedrus_mpeg2_irq_disable,
	.irq_status	= cedrus_mpeg2_irq_status,
	.setup		= cedrus_mpeg2_setup,
	.trigger	= cedrus_mpeg2_trigger,
पूर्ण;
