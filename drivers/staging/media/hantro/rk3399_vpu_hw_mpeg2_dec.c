<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitfield.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश "hantro.h"
#समावेश "hantro_hw.h"

#घोषणा VDPU_SWREG(nr)			((nr) * 4)

#घोषणा VDPU_REG_DEC_OUT_BASE		VDPU_SWREG(63)
#घोषणा VDPU_REG_RLC_VLC_BASE		VDPU_SWREG(64)
#घोषणा VDPU_REG_QTABLE_BASE		VDPU_SWREG(61)
#घोषणा VDPU_REG_REFER0_BASE		VDPU_SWREG(131)
#घोषणा VDPU_REG_REFER2_BASE		VDPU_SWREG(134)
#घोषणा VDPU_REG_REFER3_BASE		VDPU_SWREG(135)
#घोषणा VDPU_REG_REFER1_BASE		VDPU_SWREG(148)
#घोषणा VDPU_REG_DEC_E(v)		((v) ? BIT(0) : 0)

#घोषणा VDPU_REG_DEC_ADV_PRE_DIS(v)	((v) ? BIT(11) : 0)
#घोषणा VDPU_REG_DEC_SCMD_DIS(v)	((v) ? BIT(10) : 0)
#घोषणा VDPU_REG_FILTERING_DIS(v)	((v) ? BIT(8) : 0)
#घोषणा VDPU_REG_DEC_LATENCY(v)		(((v) << 1) & GENMASK(6, 1))

#घोषणा VDPU_REG_INIT_QP(v)		(((v) << 25) & GENMASK(30, 25))
#घोषणा VDPU_REG_STREAM_LEN(v)		(((v) << 0) & GENMASK(23, 0))

#घोषणा VDPU_REG_APF_THRESHOLD(v)	(((v) << 17) & GENMASK(30, 17))
#घोषणा VDPU_REG_STARTMB_X(v)		(((v) << 8) & GENMASK(16, 8))
#घोषणा VDPU_REG_STARTMB_Y(v)		(((v) << 0) & GENMASK(7, 0))

#घोषणा VDPU_REG_DEC_MODE(v)		(((v) << 0) & GENMASK(3, 0))

#घोषणा VDPU_REG_DEC_STRENDIAN_E(v)	((v) ? BIT(5) : 0)
#घोषणा VDPU_REG_DEC_STRSWAP32_E(v)	((v) ? BIT(4) : 0)
#घोषणा VDPU_REG_DEC_OUTSWAP32_E(v)	((v) ? BIT(3) : 0)
#घोषणा VDPU_REG_DEC_INSWAP32_E(v)	((v) ? BIT(2) : 0)
#घोषणा VDPU_REG_DEC_OUT_ENDIAN(v)	((v) ? BIT(1) : 0)
#घोषणा VDPU_REG_DEC_IN_ENDIAN(v)	((v) ? BIT(0) : 0)

#घोषणा VDPU_REG_DEC_DATA_DISC_E(v)	((v) ? BIT(22) : 0)
#घोषणा VDPU_REG_DEC_MAX_BURST(v)	(((v) << 16) & GENMASK(20, 16))
#घोषणा VDPU_REG_DEC_AXI_WR_ID(v)	(((v) << 8) & GENMASK(15, 8))
#घोषणा VDPU_REG_DEC_AXI_RD_ID(v)	(((v) << 0) & GENMASK(7, 0))

#घोषणा VDPU_REG_RLC_MODE_E(v)		((v) ? BIT(20) : 0)
#घोषणा VDPU_REG_PIC_INTERLACE_E(v)	((v) ? BIT(17) : 0)
#घोषणा VDPU_REG_PIC_FIELDMODE_E(v)	((v) ? BIT(16) : 0)
#घोषणा VDPU_REG_PIC_B_E(v)		((v) ? BIT(15) : 0)
#घोषणा VDPU_REG_PIC_INTER_E(v)		((v) ? BIT(14) : 0)
#घोषणा VDPU_REG_PIC_TOPFIELD_E(v)	((v) ? BIT(13) : 0)
#घोषणा VDPU_REG_FWD_INTERLACE_E(v)	((v) ? BIT(12) : 0)
#घोषणा VDPU_REG_WRITE_MVS_E(v)		((v) ? BIT(10) : 0)
#घोषणा VDPU_REG_DEC_TIMEOUT_E(v)	((v) ? BIT(5) : 0)
#घोषणा VDPU_REG_DEC_CLK_GATE_E(v)	((v) ? BIT(4) : 0)

#घोषणा VDPU_REG_PIC_MB_WIDTH(v)	(((v) << 23) & GENMASK(31, 23))
#घोषणा VDPU_REG_PIC_MB_HEIGHT_P(v)	(((v) << 11) & GENMASK(18, 11))
#घोषणा VDPU_REG_ALT_SCAN_E(v)		((v) ? BIT(6) : 0)
#घोषणा VDPU_REG_TOPFIELDFIRST_E(v)	((v) ? BIT(5) : 0)

#घोषणा VDPU_REG_STRM_START_BIT(v)	(((v) << 26) & GENMASK(31, 26))
#घोषणा VDPU_REG_QSCALE_TYPE(v)		((v) ? BIT(24) : 0)
#घोषणा VDPU_REG_CON_MV_E(v)		((v) ? BIT(4) : 0)
#घोषणा VDPU_REG_INTRA_DC_PREC(v)	(((v) << 2) & GENMASK(3, 2))
#घोषणा VDPU_REG_INTRA_VLC_TAB(v)	((v) ? BIT(1) : 0)
#घोषणा VDPU_REG_FRAME_PRED_DCT(v)	((v) ? BIT(0) : 0)

#घोषणा VDPU_REG_ALT_SCAN_FLAG_E(v)	((v) ? BIT(19) : 0)
#घोषणा VDPU_REG_FCODE_FWD_HOR(v)	(((v) << 15) & GENMASK(18, 15))
#घोषणा VDPU_REG_FCODE_FWD_VER(v)	(((v) << 11) & GENMASK(14, 11))
#घोषणा VDPU_REG_FCODE_BWD_HOR(v)	(((v) << 7) & GENMASK(10, 7))
#घोषणा VDPU_REG_FCODE_BWD_VER(v)	(((v) << 3) & GENMASK(6, 3))
#घोषणा VDPU_REG_MV_ACCURACY_FWD(v)	((v) ? BIT(2) : 0)
#घोषणा VDPU_REG_MV_ACCURACY_BWD(v)	((v) ? BIT(1) : 0)

#घोषणा PICT_TOP_FIELD     1
#घोषणा PICT_BOTTOM_FIELD  2
#घोषणा PICT_FRAME         3

अटल व्योम
rk3399_vpu_mpeg2_dec_set_quantization(काष्ठा hantro_dev *vpu,
				      काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl_mpeg2_quantization *quantization;

	quantization = hantro_get_ctrl(ctx,
				       V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION);
	hantro_mpeg2_dec_copy_qtable(ctx->mpeg2_dec.qtable.cpu, quantization);
	vdpu_ग_लिखो_relaxed(vpu, ctx->mpeg2_dec.qtable.dma,
			   VDPU_REG_QTABLE_BASE);
पूर्ण

अटल व्योम
rk3399_vpu_mpeg2_dec_set_buffers(काष्ठा hantro_dev *vpu,
				 काष्ठा hantro_ctx *ctx,
				 काष्ठा vb2_buffer *src_buf,
				 काष्ठा vb2_buffer *dst_buf,
				 स्थिर काष्ठा v4l2_mpeg2_sequence *sequence,
				 स्थिर काष्ठा v4l2_mpeg2_picture *picture,
				 स्थिर काष्ठा v4l2_ctrl_mpeg2_slice_params *slice_params)
अणु
	dma_addr_t क्रमward_addr = 0, backward_addr = 0;
	dma_addr_t current_addr, addr;

	चयन (picture->picture_coding_type) अणु
	हाल V4L2_MPEG2_PICTURE_CODING_TYPE_B:
		backward_addr = hantro_get_ref(ctx,
					       slice_params->backward_ref_ts);
		fallthrough;
	हाल V4L2_MPEG2_PICTURE_CODING_TYPE_P:
		क्रमward_addr = hantro_get_ref(ctx,
					      slice_params->क्रमward_ref_ts);
	पूर्ण

	/* Source bitstream buffer */
	addr = vb2_dma_contig_plane_dma_addr(src_buf, 0);
	vdpu_ग_लिखो_relaxed(vpu, addr, VDPU_REG_RLC_VLC_BASE);

	/* Destination frame buffer */
	addr = vb2_dma_contig_plane_dma_addr(dst_buf, 0);
	current_addr = addr;

	अगर (picture->picture_काष्ठाure == PICT_BOTTOM_FIELD)
		addr += ALIGN(ctx->dst_fmt.width, 16);
	vdpu_ग_लिखो_relaxed(vpu, addr, VDPU_REG_DEC_OUT_BASE);

	अगर (!क्रमward_addr)
		क्रमward_addr = current_addr;
	अगर (!backward_addr)
		backward_addr = current_addr;

	/* Set क्रमward ref frame (top/bottom field) */
	अगर (picture->picture_काष्ठाure == PICT_FRAME ||
	    picture->picture_coding_type == V4L2_MPEG2_PICTURE_CODING_TYPE_B ||
	    (picture->picture_काष्ठाure == PICT_TOP_FIELD &&
	     picture->top_field_first) ||
	    (picture->picture_काष्ठाure == PICT_BOTTOM_FIELD &&
	     !picture->top_field_first)) अणु
		vdpu_ग_लिखो_relaxed(vpu, क्रमward_addr, VDPU_REG_REFER0_BASE);
		vdpu_ग_लिखो_relaxed(vpu, क्रमward_addr, VDPU_REG_REFER1_BASE);
	पूर्ण अन्यथा अगर (picture->picture_काष्ठाure == PICT_TOP_FIELD) अणु
		vdpu_ग_लिखो_relaxed(vpu, क्रमward_addr, VDPU_REG_REFER0_BASE);
		vdpu_ग_लिखो_relaxed(vpu, current_addr, VDPU_REG_REFER1_BASE);
	पूर्ण अन्यथा अगर (picture->picture_काष्ठाure == PICT_BOTTOM_FIELD) अणु
		vdpu_ग_लिखो_relaxed(vpu, current_addr, VDPU_REG_REFER0_BASE);
		vdpu_ग_लिखो_relaxed(vpu, क्रमward_addr, VDPU_REG_REFER1_BASE);
	पूर्ण

	/* Set backward ref frame (top/bottom field) */
	vdpu_ग_लिखो_relaxed(vpu, backward_addr, VDPU_REG_REFER2_BASE);
	vdpu_ग_लिखो_relaxed(vpu, backward_addr, VDPU_REG_REFER3_BASE);
पूर्ण

व्योम rk3399_vpu_mpeg2_dec_run(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	स्थिर काष्ठा v4l2_ctrl_mpeg2_slice_params *slice_params;
	स्थिर काष्ठा v4l2_mpeg2_sequence *sequence;
	स्थिर काष्ठा v4l2_mpeg2_picture *picture;
	u32 reg;

	src_buf = hantro_get_src_buf(ctx);
	dst_buf = hantro_get_dst_buf(ctx);

	hantro_start_prepare_run(ctx);

	slice_params = hantro_get_ctrl(ctx,
				       V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS);
	sequence = &slice_params->sequence;
	picture = &slice_params->picture;

	reg = VDPU_REG_DEC_ADV_PRE_DIS(0) |
	      VDPU_REG_DEC_SCMD_DIS(0) |
	      VDPU_REG_FILTERING_DIS(1) |
	      VDPU_REG_DEC_LATENCY(0);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(50));

	reg = VDPU_REG_INIT_QP(1) |
	      VDPU_REG_STREAM_LEN(slice_params->bit_size >> 3);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(51));

	reg = VDPU_REG_APF_THRESHOLD(8) |
	      VDPU_REG_STARTMB_X(0) |
	      VDPU_REG_STARTMB_Y(0);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(52));

	reg = VDPU_REG_DEC_MODE(5);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(53));

	reg = VDPU_REG_DEC_STRENDIAN_E(1) |
	      VDPU_REG_DEC_STRSWAP32_E(1) |
	      VDPU_REG_DEC_OUTSWAP32_E(1) |
	      VDPU_REG_DEC_INSWAP32_E(1) |
	      VDPU_REG_DEC_OUT_ENDIAN(1) |
	      VDPU_REG_DEC_IN_ENDIAN(1);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(54));

	reg = VDPU_REG_DEC_DATA_DISC_E(0) |
	      VDPU_REG_DEC_MAX_BURST(16) |
	      VDPU_REG_DEC_AXI_WR_ID(0) |
	      VDPU_REG_DEC_AXI_RD_ID(0);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(56));

	reg = VDPU_REG_RLC_MODE_E(0) |
	      VDPU_REG_PIC_INTERLACE_E(!sequence->progressive_sequence) |
	      VDPU_REG_PIC_FIELDMODE_E(picture->picture_काष्ठाure != PICT_FRAME) |
	      VDPU_REG_PIC_B_E(picture->picture_coding_type == V4L2_MPEG2_PICTURE_CODING_TYPE_B) |
	      VDPU_REG_PIC_INTER_E(picture->picture_coding_type != V4L2_MPEG2_PICTURE_CODING_TYPE_I) |
	      VDPU_REG_PIC_TOPFIELD_E(picture->picture_काष्ठाure == PICT_TOP_FIELD) |
	      VDPU_REG_FWD_INTERLACE_E(0) |
	      VDPU_REG_WRITE_MVS_E(0) |
	      VDPU_REG_DEC_TIMEOUT_E(1) |
	      VDPU_REG_DEC_CLK_GATE_E(1);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(57));

	reg = VDPU_REG_PIC_MB_WIDTH(MB_WIDTH(ctx->dst_fmt.width)) |
	      VDPU_REG_PIC_MB_HEIGHT_P(MB_HEIGHT(ctx->dst_fmt.height)) |
	      VDPU_REG_ALT_SCAN_E(picture->alternate_scan) |
	      VDPU_REG_TOPFIELDFIRST_E(picture->top_field_first);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(120));

	reg = VDPU_REG_STRM_START_BIT(slice_params->data_bit_offset) |
	      VDPU_REG_QSCALE_TYPE(picture->q_scale_type) |
	      VDPU_REG_CON_MV_E(picture->concealment_motion_vectors) |
	      VDPU_REG_INTRA_DC_PREC(picture->पूर्णांकra_dc_precision) |
	      VDPU_REG_INTRA_VLC_TAB(picture->पूर्णांकra_vlc_क्रमmat) |
	      VDPU_REG_FRAME_PRED_DCT(picture->frame_pred_frame_dct);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(122));

	reg = VDPU_REG_ALT_SCAN_FLAG_E(picture->alternate_scan) |
	      VDPU_REG_FCODE_FWD_HOR(picture->f_code[0][0]) |
	      VDPU_REG_FCODE_FWD_VER(picture->f_code[0][1]) |
	      VDPU_REG_FCODE_BWD_HOR(picture->f_code[1][0]) |
	      VDPU_REG_FCODE_BWD_VER(picture->f_code[1][1]) |
	      VDPU_REG_MV_ACCURACY_FWD(1) |
	      VDPU_REG_MV_ACCURACY_BWD(1);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_SWREG(136));

	rk3399_vpu_mpeg2_dec_set_quantization(vpu, ctx);

	rk3399_vpu_mpeg2_dec_set_buffers(vpu, ctx, &src_buf->vb2_buf,
					 &dst_buf->vb2_buf,
					 sequence, picture, slice_params);

	/* Kick the watchकरोg and start decoding */
	hantro_end_prepare_run(ctx);

	reg = vdpu_पढ़ो(vpu, VDPU_SWREG(57)) | VDPU_REG_DEC_E(1);
	vdpu_ग_लिखो(vpu, reg, VDPU_SWREG(57));
पूर्ण
