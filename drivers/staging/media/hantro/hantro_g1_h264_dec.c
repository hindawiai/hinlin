<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Rockchip RK3288 VPU codec driver
 *
 * Copyright (c) 2014 Rockchip Electronics Co., Ltd.
 *	Hertz Wong <hertz.wong@rock-chips.com>
 *	Herman Chen <herman.chen@rock-chips.com>
 *
 * Copyright (C) 2014 Google, Inc.
 *	Tomasz Figa <tfiga@chromium.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/sort.h>

#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "hantro_g1_regs.h"
#समावेश "hantro_hw.h"
#समावेश "hantro_v4l2.h"

अटल व्योम set_params(काष्ठा hantro_ctx *ctx)
अणु
	स्थिर काष्ठा hantro_h264_dec_ctrls *ctrls = &ctx->h264_dec.ctrls;
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params *dec_param = ctrls->decode;
	स्थिर काष्ठा v4l2_ctrl_h264_sps *sps = ctrls->sps;
	स्थिर काष्ठा v4l2_ctrl_h264_pps *pps = ctrls->pps;
	काष्ठा vb2_v4l2_buffer *src_buf = hantro_get_src_buf(ctx);
	काष्ठा hantro_dev *vpu = ctx->dev;
	u32 reg;

	/* Decoder control रेजिस्टर 0. */
	reg = G1_REG_DEC_CTRL0_DEC_AXI_WR_ID(0x0);
	अगर (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		reg |= G1_REG_DEC_CTRL0_SEQ_MBAFF_E;
	अगर (sps->profile_idc > 66) अणु
		reg |= G1_REG_DEC_CTRL0_PICORD_COUNT_E;
		अगर (dec_param->nal_ref_idc)
			reg |= G1_REG_DEC_CTRL0_WRITE_MVS_E;
	पूर्ण

	अगर (!(sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY) &&
	    (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD ||
	     dec_param->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC))
		reg |= G1_REG_DEC_CTRL0_PIC_INTERLACE_E;
	अगर (dec_param->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC)
		reg |= G1_REG_DEC_CTRL0_PIC_FIELDMODE_E;
	अगर (!(dec_param->flags & V4L2_H264_DECODE_PARAM_FLAG_BOTTOM_FIELD))
		reg |= G1_REG_DEC_CTRL0_PIC_TOPFIELD_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL0);

	/* Decoder control रेजिस्टर 1. */
	reg = G1_REG_DEC_CTRL1_PIC_MB_WIDTH(MB_WIDTH(ctx->src_fmt.width)) |
	      G1_REG_DEC_CTRL1_PIC_MB_HEIGHT_P(MB_HEIGHT(ctx->src_fmt.height)) |
	      G1_REG_DEC_CTRL1_REF_FRAMES(sps->max_num_ref_frames);
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL1);

	/* Decoder control रेजिस्टर 2. */
	reg = G1_REG_DEC_CTRL2_CH_QP_OFFSET(pps->chroma_qp_index_offset) |
	      G1_REG_DEC_CTRL2_CH_QP_OFFSET2(pps->second_chroma_qp_index_offset);

	अगर (pps->flags & V4L2_H264_PPS_FLAG_SCALING_MATRIX_PRESENT)
		reg |= G1_REG_DEC_CTRL2_TYPE1_QUANT_E;
	अगर (!(sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY))
		reg |= G1_REG_DEC_CTRL2_FIELDPIC_FLAG_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL2);

	/* Decoder control रेजिस्टर 3. */
	reg = G1_REG_DEC_CTRL3_START_CODE_E |
	      G1_REG_DEC_CTRL3_INIT_QP(pps->pic_init_qp_minus26 + 26) |
	      G1_REG_DEC_CTRL3_STREAM_LEN(vb2_get_plane_payload(&src_buf->vb2_buf, 0));
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL3);

	/* Decoder control रेजिस्टर 4. */
	reg = G1_REG_DEC_CTRL4_FRAMENUM_LEN(sps->log2_max_frame_num_minus4 + 4) |
	      G1_REG_DEC_CTRL4_FRAMENUM(dec_param->frame_num) |
	      G1_REG_DEC_CTRL4_WEIGHT_BIPR_IDC(pps->weighted_bipred_idc);
	अगर (pps->flags & V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE)
		reg |= G1_REG_DEC_CTRL4_CABAC_E;
	अगर (sps->flags & V4L2_H264_SPS_FLAG_सूचीECT_8X8_INFERENCE)
		reg |= G1_REG_DEC_CTRL4_सूची_8X8_INFER_E;
	अगर (sps->profile_idc >= 100 && sps->chroma_क्रमmat_idc == 0)
		reg |= G1_REG_DEC_CTRL4_BLACKWHITE_E;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_WEIGHTED_PRED)
		reg |= G1_REG_DEC_CTRL4_WEIGHT_PRED_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL4);

	/* Decoder control रेजिस्टर 5. */
	reg = G1_REG_DEC_CTRL5_REFPIC_MK_LEN(dec_param->dec_ref_pic_marking_bit_size) |
	      G1_REG_DEC_CTRL5_IDR_PIC_ID(dec_param->idr_pic_id);
	अगर (pps->flags & V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED)
		reg |= G1_REG_DEC_CTRL5_CONST_INTRA_E;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_DEBLOCKING_FILTER_CONTROL_PRESENT)
		reg |= G1_REG_DEC_CTRL5_FILT_CTRL_PRES;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_REDUNDANT_PIC_CNT_PRESENT)
		reg |= G1_REG_DEC_CTRL5_RDPIC_CNT_PRES;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE)
		reg |= G1_REG_DEC_CTRL5_8X8TRANS_FLAG_E;
	अगर (dec_param->flags & V4L2_H264_DECODE_PARAM_FLAG_IDR_PIC)
		reg |= G1_REG_DEC_CTRL5_IDR_PIC_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL5);

	/* Decoder control रेजिस्टर 6. */
	reg = G1_REG_DEC_CTRL6_PPS_ID(pps->pic_parameter_set_id) |
	      G1_REG_DEC_CTRL6_REFIDX0_ACTIVE(pps->num_ref_idx_l0_शेष_active_minus1 + 1) |
	      G1_REG_DEC_CTRL6_REFIDX1_ACTIVE(pps->num_ref_idx_l1_शेष_active_minus1 + 1) |
	      G1_REG_DEC_CTRL6_POC_LENGTH(dec_param->pic_order_cnt_bit_size);
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_DEC_CTRL6);

	/* Error concealment रेजिस्टर. */
	vdpu_ग_लिखो_relaxed(vpu, 0, G1_REG_ERR_CONC);

	/* Prediction filter tap रेजिस्टर. */
	vdpu_ग_लिखो_relaxed(vpu,
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_0(1) |
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_1(-5 & 0x3ff) |
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_2(20),
			   G1_REG_PRED_FLT);

	/* Reference picture buffer control रेजिस्टर. */
	vdpu_ग_लिखो_relaxed(vpu, 0, G1_REG_REF_BUF_CTRL);

	/* Reference picture buffer control रेजिस्टर 2. */
	vdpu_ग_लिखो_relaxed(vpu, G1_REG_REF_BUF_CTRL2_APF_THRESHOLD(8),
			   G1_REG_REF_BUF_CTRL2);
पूर्ण

अटल व्योम set_ref(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा v4l2_h264_dpb_entry *dpb = ctx->h264_dec.dpb;
	स्थिर u8 *b0_reflist, *b1_reflist, *p_reflist;
	काष्ठा hantro_dev *vpu = ctx->dev;
	u32 dpb_दीर्घterm = 0;
	u32 dpb_valid = 0;
	पूर्णांक reg_num;
	u32 reg;
	पूर्णांक i;

	/*
	 * Set up bit maps of valid and दीर्घ term DPBs.
	 * NOTE: The bits are reversed, i.e. MSb is DPB 0.
	 */
	क्रम (i = 0; i < HANTRO_H264_DPB_SIZE; ++i) अणु
		अगर (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE)
			dpb_valid |= BIT(HANTRO_H264_DPB_SIZE - 1 - i);

		अगर (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			dpb_दीर्घterm |= BIT(HANTRO_H264_DPB_SIZE - 1 - i);
	पूर्ण
	vdpu_ग_लिखो_relaxed(vpu, dpb_valid << 16, G1_REG_VALID_REF);
	vdpu_ग_लिखो_relaxed(vpu, dpb_दीर्घterm << 16, G1_REG_LT_REF);

	/*
	 * Set up reference frame picture numbers.
	 *
	 * Each G1_REG_REF_PIC(x) रेजिस्टर contains numbers of two
	 * subsequential reference pictures.
	 */
	क्रम (i = 0; i < HANTRO_H264_DPB_SIZE; i += 2) अणु
		reg = 0;
		अगर (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			reg |= G1_REG_REF_PIC_REFER0_NBR(dpb[i].pic_num);
		अन्यथा
			reg |= G1_REG_REF_PIC_REFER0_NBR(dpb[i].frame_num);

		अगर (dpb[i + 1].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			reg |= G1_REG_REF_PIC_REFER1_NBR(dpb[i + 1].pic_num);
		अन्यथा
			reg |= G1_REG_REF_PIC_REFER1_NBR(dpb[i + 1].frame_num);

		vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_REF_PIC(i / 2));
	पूर्ण

	b0_reflist = ctx->h264_dec.reflists.b0;
	b1_reflist = ctx->h264_dec.reflists.b1;
	p_reflist = ctx->h264_dec.reflists.p;

	/*
	 * Each G1_REG_BD_REF_PIC(x) रेजिस्टर contains three entries
	 * of each क्रमward and backward picture list.
	 */
	reg_num = 0;
	क्रम (i = 0; i < 15; i += 3) अणु
		reg = G1_REG_BD_REF_PIC_BINIT_RLIST_F0(b0_reflist[i]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_F1(b0_reflist[i + 1]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_F2(b0_reflist[i + 2]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B0(b1_reflist[i]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B1(b1_reflist[i + 1]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B2(b1_reflist[i + 2]);
		vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_BD_REF_PIC(reg_num++));
	पूर्ण

	/*
	 * G1_REG_BD_P_REF_PIC रेजिस्टर contains last entries (index 15)
	 * of क्रमward and backward reference picture lists and first 4 entries
	 * of P क्रमward picture list.
	 */
	reg = G1_REG_BD_P_REF_PIC_BINIT_RLIST_F15(b0_reflist[15]) |
	      G1_REG_BD_P_REF_PIC_BINIT_RLIST_B15(b1_reflist[15]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F0(p_reflist[0]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F1(p_reflist[1]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F2(p_reflist[2]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F3(p_reflist[3]);
	vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_BD_P_REF_PIC);

	/*
	 * Each G1_REG_FWD_PIC(x) रेजिस्टर contains six consecutive
	 * entries of P क्रमward picture list, starting from index 4.
	 */
	reg_num = 0;
	क्रम (i = 4; i < HANTRO_H264_DPB_SIZE; i += 6) अणु
		reg = G1_REG_FWD_PIC_PINIT_RLIST_F0(p_reflist[i]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F1(p_reflist[i + 1]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F2(p_reflist[i + 2]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F3(p_reflist[i + 3]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F4(p_reflist[i + 4]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F5(p_reflist[i + 5]);
		vdpu_ग_लिखो_relaxed(vpu, reg, G1_REG_FWD_PIC(reg_num++));
	पूर्ण

	/* Set up addresses of DPB buffers. */
	क्रम (i = 0; i < HANTRO_H264_DPB_SIZE; i++) अणु
		dma_addr_t dma_addr = hantro_h264_get_ref_buf(ctx, i);

		vdpu_ग_लिखो_relaxed(vpu, dma_addr, G1_REG_ADDR_REF(i));
	पूर्ण
पूर्ण

अटल व्योम set_buffers(काष्ठा hantro_ctx *ctx)
अणु
	स्थिर काष्ठा hantro_h264_dec_ctrls *ctrls = &ctx->h264_dec.ctrls;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा hantro_dev *vpu = ctx->dev;
	dma_addr_t src_dma, dst_dma;
	माप_प्रकार offset = 0;

	src_buf = hantro_get_src_buf(ctx);
	dst_buf = hantro_get_dst_buf(ctx);

	/* Source (stream) buffer. */
	src_dma = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	vdpu_ग_लिखो_relaxed(vpu, src_dma, G1_REG_ADDR_STR);

	/* Destination (decoded frame) buffer. */
	dst_dma = hantro_get_dec_buf_addr(ctx, &dst_buf->vb2_buf);
	/* Adjust dma addr to start at second line क्रम bottom field */
	अगर (ctrls->decode->flags & V4L2_H264_DECODE_PARAM_FLAG_BOTTOM_FIELD)
		offset = ALIGN(ctx->src_fmt.width, MB_DIM);
	vdpu_ग_लिखो_relaxed(vpu, dst_dma + offset, G1_REG_ADDR_DST);

	/* Higher profiles require DMV buffer appended to reference frames. */
	अगर (ctrls->sps->profile_idc > 66 && ctrls->decode->nal_ref_idc) अणु
		अचिन्हित पूर्णांक bytes_per_mb = 384;

		/* DMV buffer क्रम monochrome start directly after Y-plane */
		अगर (ctrls->sps->profile_idc >= 100 &&
		    ctrls->sps->chroma_क्रमmat_idc == 0)
			bytes_per_mb = 256;
		offset = bytes_per_mb * MB_WIDTH(ctx->src_fmt.width) *
			 MB_HEIGHT(ctx->src_fmt.height);

		/*
		 * DMV buffer is split in two क्रम field encoded frames,
		 * adjust offset क्रम bottom field
		 */
		अगर (ctrls->decode->flags & V4L2_H264_DECODE_PARAM_FLAG_BOTTOM_FIELD)
			offset += 32 * MB_WIDTH(ctx->src_fmt.width) *
				  MB_HEIGHT(ctx->src_fmt.height);
		vdpu_ग_लिखो_relaxed(vpu, dst_dma + offset, G1_REG_ADDR_सूची_MV);
	पूर्ण

	/* Auxiliary buffer prepared in hantro_g1_h264_dec_prepare_table(). */
	vdpu_ग_लिखो_relaxed(vpu, ctx->h264_dec.priv.dma, G1_REG_ADDR_QTABLE);
पूर्ण

व्योम hantro_g1_h264_dec_run(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	/* Prepare the H264 decoder context. */
	अगर (hantro_h264_dec_prepare_run(ctx))
		वापस;

	/* Configure hardware रेजिस्टरs. */
	set_params(ctx);
	set_ref(ctx);
	set_buffers(ctx);

	hantro_end_prepare_run(ctx);

	/* Start decoding! */
	vdpu_ग_लिखो_relaxed(vpu,
			   G1_REG_CONFIG_DEC_AXI_RD_ID(0xffu) |
			   G1_REG_CONFIG_DEC_TIMEOUT_E |
			   G1_REG_CONFIG_DEC_OUT_ENDIAN |
			   G1_REG_CONFIG_DEC_STRENDIAN_E |
			   G1_REG_CONFIG_DEC_MAX_BURST(16) |
			   G1_REG_CONFIG_DEC_OUTSWAP32_E |
			   G1_REG_CONFIG_DEC_INSWAP32_E |
			   G1_REG_CONFIG_DEC_STRSWAP32_E |
			   G1_REG_CONFIG_DEC_CLK_GATE_E,
			   G1_REG_CONFIG);
	vdpu_ग_लिखो(vpu, G1_REG_INTERRUPT_DEC_E, G1_REG_INTERRUPT);
पूर्ण
