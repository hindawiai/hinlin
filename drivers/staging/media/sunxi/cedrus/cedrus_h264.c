<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cedrus VPU driver
 *
 * Copyright (c) 2013 Jens Kuske <jenskuske@gmail.com>
 * Copyright (c) 2018 Bootlin
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>

#समावेश <media/videobuf2-dma-contig.h>

#समावेश "cedrus.h"
#समावेश "cedrus_hw.h"
#समावेश "cedrus_regs.h"

क्रमागत cedrus_h264_sram_off अणु
	CEDRUS_SRAM_H264_PRED_WEIGHT_TABLE	= 0x000,
	CEDRUS_SRAM_H264_FRAMEBUFFER_LIST	= 0x100,
	CEDRUS_SRAM_H264_REF_LIST_0		= 0x190,
	CEDRUS_SRAM_H264_REF_LIST_1		= 0x199,
	CEDRUS_SRAM_H264_SCALING_LIST_8x8_0	= 0x200,
	CEDRUS_SRAM_H264_SCALING_LIST_8x8_1	= 0x210,
	CEDRUS_SRAM_H264_SCALING_LIST_4x4	= 0x220,
पूर्ण;

काष्ठा cedrus_h264_sram_ref_pic अणु
	__le32	top_field_order_cnt;
	__le32	bottom_field_order_cnt;
	__le32	frame_info;
	__le32	luma_ptr;
	__le32	chroma_ptr;
	__le32	mv_col_top_ptr;
	__le32	mv_col_bot_ptr;
	__le32	reserved;
पूर्ण __packed;

#घोषणा CEDRUS_H264_FRAME_NUM		18

#घोषणा CEDRUS_NEIGHBOR_INFO_BUF_SIZE	(16 * SZ_1K)
#घोषणा CEDRUS_MIN_PIC_INFO_BUF_SIZE       (130 * SZ_1K)

अटल व्योम cedrus_h264_ग_लिखो_sram(काष्ठा cedrus_dev *dev,
				   क्रमागत cedrus_h264_sram_off off,
				   स्थिर व्योम *data, माप_प्रकार len)
अणु
	स्थिर u32 *buffer = data;
	माप_प्रकार count = DIV_ROUND_UP(len, 4);

	cedrus_ग_लिखो(dev, VE_AVC_SRAM_PORT_OFFSET, off << 2);

	जबतक (count--)
		cedrus_ग_लिखो(dev, VE_AVC_SRAM_PORT_DATA, *buffer++);
पूर्ण

अटल dma_addr_t cedrus_h264_mv_col_buf_addr(काष्ठा cedrus_ctx *ctx,
					      अचिन्हित पूर्णांक position,
					      अचिन्हित पूर्णांक field)
अणु
	dma_addr_t addr = ctx->codec.h264.mv_col_buf_dma;

	/* Adjust क्रम the position */
	addr += position * ctx->codec.h264.mv_col_buf_field_size * 2;

	/* Adjust क्रम the field */
	addr += field * ctx->codec.h264.mv_col_buf_field_size;

	वापस addr;
पूर्ण

अटल व्योम cedrus_fill_ref_pic(काष्ठा cedrus_ctx *ctx,
				काष्ठा cedrus_buffer *buf,
				अचिन्हित पूर्णांक top_field_order_cnt,
				अचिन्हित पूर्णांक bottom_field_order_cnt,
				काष्ठा cedrus_h264_sram_ref_pic *pic)
अणु
	काष्ठा vb2_buffer *vbuf = &buf->m2m_buf.vb.vb2_buf;
	अचिन्हित पूर्णांक position = buf->codec.h264.position;

	pic->top_field_order_cnt = cpu_to_le32(top_field_order_cnt);
	pic->bottom_field_order_cnt = cpu_to_le32(bottom_field_order_cnt);
	pic->frame_info = cpu_to_le32(buf->codec.h264.pic_type << 8);

	pic->luma_ptr = cpu_to_le32(cedrus_buf_addr(vbuf, &ctx->dst_fmt, 0));
	pic->chroma_ptr = cpu_to_le32(cedrus_buf_addr(vbuf, &ctx->dst_fmt, 1));
	pic->mv_col_top_ptr =
		cpu_to_le32(cedrus_h264_mv_col_buf_addr(ctx, position, 0));
	pic->mv_col_bot_ptr =
		cpu_to_le32(cedrus_h264_mv_col_buf_addr(ctx, position, 1));
पूर्ण

अटल व्योम cedrus_ग_लिखो_frame_list(काष्ठा cedrus_ctx *ctx,
				    काष्ठा cedrus_run *run)
अणु
	काष्ठा cedrus_h264_sram_ref_pic pic_list[CEDRUS_H264_FRAME_NUM];
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params *decode = run->h264.decode_params;
	स्थिर काष्ठा v4l2_ctrl_h264_sps *sps = run->h264.sps;
	काष्ठा vb2_queue *cap_q;
	काष्ठा cedrus_buffer *output_buf;
	काष्ठा cedrus_dev *dev = ctx->dev;
	अचिन्हित दीर्घ used_dpbs = 0;
	अचिन्हित पूर्णांक position;
	पूर्णांक output = -1;
	अचिन्हित पूर्णांक i;

	cap_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	स_रखो(pic_list, 0, माप(pic_list));

	क्रम (i = 0; i < ARRAY_SIZE(decode->dpb); i++) अणु
		स्थिर काष्ठा v4l2_h264_dpb_entry *dpb = &decode->dpb[i];
		काष्ठा cedrus_buffer *cedrus_buf;
		पूर्णांक buf_idx;

		अगर (!(dpb->flags & V4L2_H264_DPB_ENTRY_FLAG_VALID))
			जारी;

		buf_idx = vb2_find_बारtamp(cap_q, dpb->reference_ts, 0);
		अगर (buf_idx < 0)
			जारी;

		cedrus_buf = vb2_to_cedrus_buffer(cap_q->bufs[buf_idx]);
		position = cedrus_buf->codec.h264.position;
		used_dpbs |= BIT(position);

		अगर (run->dst->vb2_buf.बारtamp == dpb->reference_ts) अणु
			output = position;
			जारी;
		पूर्ण

		अगर (!(dpb->flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE))
			जारी;

		cedrus_fill_ref_pic(ctx, cedrus_buf,
				    dpb->top_field_order_cnt,
				    dpb->bottom_field_order_cnt,
				    &pic_list[position]);
	पूर्ण

	अगर (output >= 0)
		position = output;
	अन्यथा
		position = find_first_zero_bit(&used_dpbs, CEDRUS_H264_FRAME_NUM);

	output_buf = vb2_to_cedrus_buffer(&run->dst->vb2_buf);
	output_buf->codec.h264.position = position;

	अगर (decode->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC)
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_FIELD;
	अन्यथा अगर (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_MBAFF;
	अन्यथा
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_FRAME;

	cedrus_fill_ref_pic(ctx, output_buf,
			    decode->top_field_order_cnt,
			    decode->bottom_field_order_cnt,
			    &pic_list[position]);

	cedrus_h264_ग_लिखो_sram(dev, CEDRUS_SRAM_H264_FRAMEBUFFER_LIST,
			       pic_list, माप(pic_list));

	cedrus_ग_लिखो(dev, VE_H264_OUTPUT_FRAME_IDX, position);
पूर्ण

#घोषणा CEDRUS_MAX_REF_IDX	32

अटल व्योम _cedrus_ग_लिखो_ref_list(काष्ठा cedrus_ctx *ctx,
				   काष्ठा cedrus_run *run,
				   स्थिर काष्ठा v4l2_h264_reference *ref_list,
				   u8 num_ref, क्रमागत cedrus_h264_sram_off sram)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params *decode = run->h264.decode_params;
	काष्ठा vb2_queue *cap_q;
	काष्ठा cedrus_dev *dev = ctx->dev;
	u8 sram_array[CEDRUS_MAX_REF_IDX];
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;

	cap_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	स_रखो(sram_array, 0, माप(sram_array));

	क्रम (i = 0; i < num_ref; i++) अणु
		स्थिर काष्ठा v4l2_h264_dpb_entry *dpb;
		स्थिर काष्ठा cedrus_buffer *cedrus_buf;
		अचिन्हित पूर्णांक position;
		पूर्णांक buf_idx;
		u8 dpb_idx;

		dpb_idx = ref_list[i].index;
		dpb = &decode->dpb[dpb_idx];

		अगर (!(dpb->flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE))
			जारी;

		buf_idx = vb2_find_बारtamp(cap_q, dpb->reference_ts, 0);
		अगर (buf_idx < 0)
			जारी;

		cedrus_buf = vb2_to_cedrus_buffer(cap_q->bufs[buf_idx]);
		position = cedrus_buf->codec.h264.position;

		sram_array[i] |= position << 1;
		अगर (ref_list[i].fields == V4L2_H264_BOTTOM_FIELD_REF)
			sram_array[i] |= BIT(0);
	पूर्ण

	size = min_t(माप_प्रकार, ALIGN(num_ref, 4), माप(sram_array));
	cedrus_h264_ग_लिखो_sram(dev, sram, &sram_array, size);
पूर्ण

अटल व्योम cedrus_ग_लिखो_ref_list0(काष्ठा cedrus_ctx *ctx,
				   काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;

	_cedrus_ग_लिखो_ref_list(ctx, run,
			       slice->ref_pic_list0,
			       slice->num_ref_idx_l0_active_minus1 + 1,
			       CEDRUS_SRAM_H264_REF_LIST_0);
पूर्ण

अटल व्योम cedrus_ग_लिखो_ref_list1(काष्ठा cedrus_ctx *ctx,
				   काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;

	_cedrus_ग_लिखो_ref_list(ctx, run,
			       slice->ref_pic_list1,
			       slice->num_ref_idx_l1_active_minus1 + 1,
			       CEDRUS_SRAM_H264_REF_LIST_1);
पूर्ण

अटल व्योम cedrus_ग_लिखो_scaling_lists(काष्ठा cedrus_ctx *ctx,
				       काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_scaling_matrix *scaling =
		run->h264.scaling_matrix;
	स्थिर काष्ठा v4l2_ctrl_h264_pps *pps = run->h264.pps;
	काष्ठा cedrus_dev *dev = ctx->dev;

	अगर (!(pps->flags & V4L2_H264_PPS_FLAG_SCALING_MATRIX_PRESENT))
		वापस;

	cedrus_h264_ग_लिखो_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_8x8_0,
			       scaling->scaling_list_8x8[0],
			       माप(scaling->scaling_list_8x8[0]));

	cedrus_h264_ग_लिखो_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_8x8_1,
			       scaling->scaling_list_8x8[1],
			       माप(scaling->scaling_list_8x8[1]));

	cedrus_h264_ग_लिखो_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_4x4,
			       scaling->scaling_list_4x4,
			       माप(scaling->scaling_list_4x4));
पूर्ण

अटल व्योम cedrus_ग_लिखो_pred_weight_table(काष्ठा cedrus_ctx *ctx,
					   काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_pred_weights *pred_weight =
		run->h264.pred_weights;
	काष्ठा cedrus_dev *dev = ctx->dev;
	पूर्णांक i, j, k;

	cedrus_ग_लिखो(dev, VE_H264_SHS_WP,
		     ((pred_weight->chroma_log2_weight_denom & 0x7) << 4) |
		     ((pred_weight->luma_log2_weight_denom & 0x7) << 0));

	cedrus_ग_लिखो(dev, VE_AVC_SRAM_PORT_OFFSET,
		     CEDRUS_SRAM_H264_PRED_WEIGHT_TABLE << 2);

	क्रम (i = 0; i < ARRAY_SIZE(pred_weight->weight_factors); i++) अणु
		स्थिर काष्ठा v4l2_h264_weight_factors *factors =
			&pred_weight->weight_factors[i];

		क्रम (j = 0; j < ARRAY_SIZE(factors->luma_weight); j++) अणु
			u32 val;

			val = (((u32)factors->luma_offset[j] & 0x1ff) << 16) |
				(factors->luma_weight[j] & 0x1ff);
			cedrus_ग_लिखो(dev, VE_AVC_SRAM_PORT_DATA, val);
		पूर्ण

		क्रम (j = 0; j < ARRAY_SIZE(factors->chroma_weight); j++) अणु
			क्रम (k = 0; k < ARRAY_SIZE(factors->chroma_weight[0]); k++) अणु
				u32 val;

				val = (((u32)factors->chroma_offset[j][k] & 0x1ff) << 16) |
					(factors->chroma_weight[j][k] & 0x1ff);
				cedrus_ग_लिखो(dev, VE_AVC_SRAM_PORT_DATA, val);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * It turns out that using VE_H264_VLD_OFFSET to skip bits is not reliable. In
 * rare हालs frame is not decoded correctly. However, setting offset to 0 and
 * skipping appropriate amount of bits with flush bits trigger always works.
 */
अटल व्योम cedrus_skip_bits(काष्ठा cedrus_dev *dev, पूर्णांक num)
अणु
	पूर्णांक count = 0;

	जबतक (count < num) अणु
		पूर्णांक पंचांगp = min(num - count, 32);

		cedrus_ग_लिखो(dev, VE_H264_TRIGGER_TYPE,
			     VE_H264_TRIGGER_TYPE_FLUSH_BITS |
			     VE_H264_TRIGGER_TYPE_N_BITS(पंचांगp));
		जबतक (cedrus_पढ़ो(dev, VE_H264_STATUS) & VE_H264_STATUS_VLD_BUSY)
			udelay(1);

		count += पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम cedrus_set_params(काष्ठा cedrus_ctx *ctx,
			      काष्ठा cedrus_run *run)
अणु
	स्थिर काष्ठा v4l2_ctrl_h264_decode_params *decode = run->h264.decode_params;
	स्थिर काष्ठा v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;
	स्थिर काष्ठा v4l2_ctrl_h264_pps *pps = run->h264.pps;
	स्थिर काष्ठा v4l2_ctrl_h264_sps *sps = run->h264.sps;
	काष्ठा vb2_buffer *src_buf = &run->src->vb2_buf;
	काष्ठा cedrus_dev *dev = ctx->dev;
	dma_addr_t src_buf_addr;
	माप_प्रकार slice_bytes = vb2_get_plane_payload(src_buf, 0);
	अचिन्हित पूर्णांक pic_width_in_mbs;
	bool mbaff_pic;
	u32 reg;

	cedrus_ग_लिखो(dev, VE_H264_VLD_LEN, slice_bytes * 8);
	cedrus_ग_लिखो(dev, VE_H264_VLD_OFFSET, 0);

	src_buf_addr = vb2_dma_contig_plane_dma_addr(src_buf, 0);
	cedrus_ग_लिखो(dev, VE_H264_VLD_END, src_buf_addr + slice_bytes);
	cedrus_ग_लिखो(dev, VE_H264_VLD_ADDR,
		     VE_H264_VLD_ADDR_VAL(src_buf_addr) |
		     VE_H264_VLD_ADDR_FIRST | VE_H264_VLD_ADDR_VALID |
		     VE_H264_VLD_ADDR_LAST);

	अगर (ctx->src_fmt.width > 2048) अणु
		cedrus_ग_लिखो(dev, VE_BUF_CTRL,
			     VE_BUF_CTRL_INTRAPRED_MIXED_RAM |
			     VE_BUF_CTRL_DBLK_MIXED_RAM);
		cedrus_ग_लिखो(dev, VE_DBLK_DRAM_BUF_ADDR,
			     ctx->codec.h264.deblk_buf_dma);
		cedrus_ग_लिखो(dev, VE_INTRAPRED_DRAM_BUF_ADDR,
			     ctx->codec.h264.पूर्णांकra_pred_buf_dma);
	पूर्ण अन्यथा अणु
		cedrus_ग_लिखो(dev, VE_BUF_CTRL,
			     VE_BUF_CTRL_INTRAPRED_INT_SRAM |
			     VE_BUF_CTRL_DBLK_INT_SRAM);
	पूर्ण

	/*
	 * FIXME: Since the bitstream parsing is करोne in software, and
	 * in userspace, this shouldn't be needed anymore. But it
	 * turns out that removing it अवरोधs the decoding process,
	 * without any clear indication why.
	 */
	cedrus_ग_लिखो(dev, VE_H264_TRIGGER_TYPE,
		     VE_H264_TRIGGER_TYPE_INIT_SWDEC);

	cedrus_skip_bits(dev, slice->header_bit_size);

	अगर (V4L2_H264_CTRL_PRED_WEIGHTS_REQUIRED(pps, slice))
		cedrus_ग_लिखो_pred_weight_table(ctx, run);

	अगर ((slice->slice_type == V4L2_H264_SLICE_TYPE_P) ||
	    (slice->slice_type == V4L2_H264_SLICE_TYPE_SP) ||
	    (slice->slice_type == V4L2_H264_SLICE_TYPE_B))
		cedrus_ग_लिखो_ref_list0(ctx, run);

	अगर (slice->slice_type == V4L2_H264_SLICE_TYPE_B)
		cedrus_ग_लिखो_ref_list1(ctx, run);

	// picture parameters
	reg = 0;
	/*
	 * FIXME: the kernel headers are allowing the शेष value to
	 * be passed, but the libva करोesn't give us that.
	 */
	reg |= (slice->num_ref_idx_l0_active_minus1 & 0x1f) << 10;
	reg |= (slice->num_ref_idx_l1_active_minus1 & 0x1f) << 5;
	reg |= (pps->weighted_bipred_idc & 0x3) << 2;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE)
		reg |= VE_H264_PPS_ENTROPY_CODING_MODE;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_WEIGHTED_PRED)
		reg |= VE_H264_PPS_WEIGHTED_PRED;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED)
		reg |= VE_H264_PPS_CONSTRAINED_INTRA_PRED;
	अगर (pps->flags & V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE)
		reg |= VE_H264_PPS_TRANSFORM_8X8_MODE;
	cedrus_ग_लिखो(dev, VE_H264_PPS, reg);

	// sequence parameters
	reg = 0;
	reg |= (sps->chroma_क्रमmat_idc & 0x7) << 19;
	reg |= (sps->pic_width_in_mbs_minus1 & 0xff) << 8;
	reg |= sps->pic_height_in_map_units_minus1 & 0xff;
	अगर (sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY)
		reg |= VE_H264_SPS_MBS_ONLY;
	अगर (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		reg |= VE_H264_SPS_MB_ADAPTIVE_FRAME_FIELD;
	अगर (sps->flags & V4L2_H264_SPS_FLAG_सूचीECT_8X8_INFERENCE)
		reg |= VE_H264_SPS_सूचीECT_8X8_INFERENCE;
	cedrus_ग_लिखो(dev, VE_H264_SPS, reg);

	mbaff_pic = !(decode->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC) &&
		    (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD);
	pic_width_in_mbs = sps->pic_width_in_mbs_minus1 + 1;

	// slice parameters
	reg = 0;
	reg |= ((slice->first_mb_in_slice % pic_width_in_mbs) & 0xff) << 24;
	reg |= (((slice->first_mb_in_slice / pic_width_in_mbs) *
		 (mbaff_pic + 1)) & 0xff) << 16;
	reg |= decode->nal_ref_idc ? BIT(12) : 0;
	reg |= (slice->slice_type & 0xf) << 8;
	reg |= slice->cabac_init_idc & 0x3;
	अगर (ctx->fh.m2m_ctx->new_frame)
		reg |= VE_H264_SHS_FIRST_SLICE_IN_PIC;
	अगर (decode->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC)
		reg |= VE_H264_SHS_FIELD_PIC;
	अगर (decode->flags & V4L2_H264_DECODE_PARAM_FLAG_BOTTOM_FIELD)
		reg |= VE_H264_SHS_BOTTOM_FIELD;
	अगर (slice->flags & V4L2_H264_SLICE_FLAG_सूचीECT_SPATIAL_MV_PRED)
		reg |= VE_H264_SHS_सूचीECT_SPATIAL_MV_PRED;
	cedrus_ग_लिखो(dev, VE_H264_SHS, reg);

	reg = 0;
	reg |= VE_H264_SHS2_NUM_REF_IDX_ACTIVE_OVRD;
	reg |= (slice->num_ref_idx_l0_active_minus1 & 0x1f) << 24;
	reg |= (slice->num_ref_idx_l1_active_minus1 & 0x1f) << 16;
	reg |= (slice->disable_deblocking_filter_idc & 0x3) << 8;
	reg |= (slice->slice_alpha_c0_offset_भाग2 & 0xf) << 4;
	reg |= slice->slice_beta_offset_भाग2 & 0xf;
	cedrus_ग_लिखो(dev, VE_H264_SHS2, reg);

	reg = 0;
	reg |= (pps->second_chroma_qp_index_offset & 0x3f) << 16;
	reg |= (pps->chroma_qp_index_offset & 0x3f) << 8;
	reg |= (pps->pic_init_qp_minus26 + 26 + slice->slice_qp_delta) & 0x3f;
	अगर (!(pps->flags & V4L2_H264_PPS_FLAG_SCALING_MATRIX_PRESENT))
		reg |= VE_H264_SHS_QP_SCALING_MATRIX_DEFAULT;
	cedrus_ग_लिखो(dev, VE_H264_SHS_QP, reg);

	// clear status flags
	cedrus_ग_लिखो(dev, VE_H264_STATUS, cedrus_पढ़ो(dev, VE_H264_STATUS));

	// enable पूर्णांक
	cedrus_ग_लिखो(dev, VE_H264_CTRL,
		     VE_H264_CTRL_SLICE_DECODE_INT |
		     VE_H264_CTRL_DECODE_ERR_INT |
		     VE_H264_CTRL_VLD_DATA_REQ_INT);
पूर्ण

अटल क्रमागत cedrus_irq_status
cedrus_h264_irq_status(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_पढ़ो(dev, VE_H264_STATUS);

	अगर (reg & (VE_H264_STATUS_DECODE_ERR_INT |
		   VE_H264_STATUS_VLD_DATA_REQ_INT))
		वापस CEDRUS_IRQ_ERROR;

	अगर (reg & VE_H264_CTRL_SLICE_DECODE_INT)
		वापस CEDRUS_IRQ_OK;

	वापस CEDRUS_IRQ_NONE;
पूर्ण

अटल व्योम cedrus_h264_irq_clear(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_ग_लिखो(dev, VE_H264_STATUS,
		     VE_H264_STATUS_INT_MASK);
पूर्ण

अटल व्योम cedrus_h264_irq_disable(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_पढ़ो(dev, VE_H264_CTRL);

	cedrus_ग_लिखो(dev, VE_H264_CTRL,
		     reg & ~VE_H264_CTRL_INT_MASK);
पूर्ण

अटल व्योम cedrus_h264_setup(काष्ठा cedrus_ctx *ctx,
			      काष्ठा cedrus_run *run)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_engine_enable(ctx, CEDRUS_CODEC_H264);

	cedrus_ग_लिखो(dev, VE_H264_SDROT_CTRL, 0);
	cedrus_ग_लिखो(dev, VE_H264_EXTRA_BUFFER1,
		     ctx->codec.h264.pic_info_buf_dma);
	cedrus_ग_लिखो(dev, VE_H264_EXTRA_BUFFER2,
		     ctx->codec.h264.neighbor_info_buf_dma);

	cedrus_ग_लिखो_scaling_lists(ctx, run);
	cedrus_ग_लिखो_frame_list(ctx, run);

	cedrus_set_params(ctx, run);
पूर्ण

अटल पूर्णांक cedrus_h264_start(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक pic_info_size;
	अचिन्हित पूर्णांक field_size;
	अचिन्हित पूर्णांक mv_col_size;
	पूर्णांक ret;

	/* Formula क्रम picture buffer size is taken from CedarX source. */

	अगर (ctx->src_fmt.width > 2048)
		pic_info_size = CEDRUS_H264_FRAME_NUM * 0x4000;
	अन्यथा
		pic_info_size = CEDRUS_H264_FRAME_NUM * 0x1000;

	/*
	 * FIXME: If V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY is set,
	 * there is no need to multiply by 2.
	 */
	pic_info_size += ctx->src_fmt.height * 2 * 64;

	अगर (pic_info_size < CEDRUS_MIN_PIC_INFO_BUF_SIZE)
		pic_info_size = CEDRUS_MIN_PIC_INFO_BUF_SIZE;

	ctx->codec.h264.pic_info_buf_size = pic_info_size;
	ctx->codec.h264.pic_info_buf =
		dma_alloc_coherent(dev->dev, ctx->codec.h264.pic_info_buf_size,
				   &ctx->codec.h264.pic_info_buf_dma,
				   GFP_KERNEL);
	अगर (!ctx->codec.h264.pic_info_buf)
		वापस -ENOMEM;

	/*
	 * That buffer is supposed to be 16kiB in size, and be aligned
	 * on 16kiB as well. However, dma_alloc_coherent provides the
	 * guarantee that we'll have a CPU and DMA address aligned on
	 * the smallest page order that is greater to the requested
	 * size, so we करोn't have to overallocate.
	 */
	ctx->codec.h264.neighbor_info_buf =
		dma_alloc_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
				   &ctx->codec.h264.neighbor_info_buf_dma,
				   GFP_KERNEL);
	अगर (!ctx->codec.h264.neighbor_info_buf) अणु
		ret = -ENOMEM;
		जाओ err_pic_buf;
	पूर्ण

	field_size = DIV_ROUND_UP(ctx->src_fmt.width, 16) *
		DIV_ROUND_UP(ctx->src_fmt.height, 16) * 16;

	/*
	 * FIXME: This is actually conditional to
	 * V4L2_H264_SPS_FLAG_सूचीECT_8X8_INFERENCE not being set, we
	 * might have to rework this अगर memory efficiency ever is
	 * something we need to work on.
	 */
	field_size = field_size * 2;

	/*
	 * FIXME: This is actually conditional to
	 * V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY not being set, we might
	 * have to rework this अगर memory efficiency ever is something
	 * we need to work on.
	 */
	field_size = field_size * 2;
	ctx->codec.h264.mv_col_buf_field_size = field_size;

	mv_col_size = field_size * 2 * CEDRUS_H264_FRAME_NUM;
	ctx->codec.h264.mv_col_buf_size = mv_col_size;
	ctx->codec.h264.mv_col_buf = dma_alloc_coherent(dev->dev,
							ctx->codec.h264.mv_col_buf_size,
							&ctx->codec.h264.mv_col_buf_dma,
							GFP_KERNEL);
	अगर (!ctx->codec.h264.mv_col_buf) अणु
		ret = -ENOMEM;
		जाओ err_neighbor_buf;
	पूर्ण

	अगर (ctx->src_fmt.width > 2048) अणु
		/*
		 * Formulas क्रम deblock and पूर्णांकra prediction buffer sizes
		 * are taken from CedarX source.
		 */

		ctx->codec.h264.deblk_buf_size =
			ALIGN(ctx->src_fmt.width, 32) * 12;
		ctx->codec.h264.deblk_buf =
			dma_alloc_coherent(dev->dev,
					   ctx->codec.h264.deblk_buf_size,
					   &ctx->codec.h264.deblk_buf_dma,
					   GFP_KERNEL);
		अगर (!ctx->codec.h264.deblk_buf) अणु
			ret = -ENOMEM;
			जाओ err_mv_col_buf;
		पूर्ण

		/*
		 * NOTE: Multiplying by two deviates from CedarX logic, but it
		 * is क्रम some unknown reason needed क्रम H264 4K decoding on H6.
		 */
		ctx->codec.h264.पूर्णांकra_pred_buf_size =
			ALIGN(ctx->src_fmt.width, 64) * 5 * 2;
		ctx->codec.h264.पूर्णांकra_pred_buf =
			dma_alloc_coherent(dev->dev,
					   ctx->codec.h264.पूर्णांकra_pred_buf_size,
					   &ctx->codec.h264.पूर्णांकra_pred_buf_dma,
					   GFP_KERNEL);
		अगर (!ctx->codec.h264.पूर्णांकra_pred_buf) अणु
			ret = -ENOMEM;
			जाओ err_deblk_buf;
		पूर्ण
	पूर्ण

	वापस 0;

err_deblk_buf:
	dma_मुक्त_coherent(dev->dev, ctx->codec.h264.deblk_buf_size,
			  ctx->codec.h264.deblk_buf,
			  ctx->codec.h264.deblk_buf_dma);

err_mv_col_buf:
	dma_मुक्त_coherent(dev->dev, ctx->codec.h264.mv_col_buf_size,
			  ctx->codec.h264.mv_col_buf,
			  ctx->codec.h264.mv_col_buf_dma);

err_neighbor_buf:
	dma_मुक्त_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
			  ctx->codec.h264.neighbor_info_buf,
			  ctx->codec.h264.neighbor_info_buf_dma);

err_pic_buf:
	dma_मुक्त_coherent(dev->dev, ctx->codec.h264.pic_info_buf_size,
			  ctx->codec.h264.pic_info_buf,
			  ctx->codec.h264.pic_info_buf_dma);
	वापस ret;
पूर्ण

अटल व्योम cedrus_h264_stop(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	dma_मुक्त_coherent(dev->dev, ctx->codec.h264.mv_col_buf_size,
			  ctx->codec.h264.mv_col_buf,
			  ctx->codec.h264.mv_col_buf_dma);
	dma_मुक्त_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
			  ctx->codec.h264.neighbor_info_buf,
			  ctx->codec.h264.neighbor_info_buf_dma);
	dma_मुक्त_coherent(dev->dev, ctx->codec.h264.pic_info_buf_size,
			  ctx->codec.h264.pic_info_buf,
			  ctx->codec.h264.pic_info_buf_dma);
	अगर (ctx->codec.h264.deblk_buf_size)
		dma_मुक्त_coherent(dev->dev, ctx->codec.h264.deblk_buf_size,
				  ctx->codec.h264.deblk_buf,
				  ctx->codec.h264.deblk_buf_dma);
	अगर (ctx->codec.h264.पूर्णांकra_pred_buf_size)
		dma_मुक्त_coherent(dev->dev, ctx->codec.h264.पूर्णांकra_pred_buf_size,
				  ctx->codec.h264.पूर्णांकra_pred_buf,
				  ctx->codec.h264.पूर्णांकra_pred_buf_dma);
पूर्ण

अटल व्योम cedrus_h264_trigger(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_ग_लिखो(dev, VE_H264_TRIGGER_TYPE,
		     VE_H264_TRIGGER_TYPE_AVC_SLICE_DECODE);
पूर्ण

काष्ठा cedrus_dec_ops cedrus_dec_ops_h264 = अणु
	.irq_clear	= cedrus_h264_irq_clear,
	.irq_disable	= cedrus_h264_irq_disable,
	.irq_status	= cedrus_h264_irq_status,
	.setup		= cedrus_h264_setup,
	.start		= cedrus_h264_start,
	.stop		= cedrus_h264_stop,
	.trigger	= cedrus_h264_trigger,
पूर्ण;
