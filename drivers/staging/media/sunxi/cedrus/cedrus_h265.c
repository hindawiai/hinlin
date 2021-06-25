<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2013 Jens Kuske <jenskuske@gmail.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>

#समावेश <media/videobuf2-dma-contig.h>

#समावेश "cedrus.h"
#समावेश "cedrus_hw.h"
#समावेश "cedrus_regs.h"

/*
 * These are the sizes क्रम side buffers required by the hardware क्रम storing
 * पूर्णांकernal decoding metadata. They match the values used by the early BSP
 * implementations, that were initially exposed in libvdpau-sunxi.
 * Subsequent BSP implementations seem to द्विगुन the neighbor info buffer size
 * क्रम the H6 SoC, which may be related to 10 bit H265 support.
 */
#घोषणा CEDRUS_H265_NEIGHBOR_INFO_BUF_SIZE	(397 * SZ_1K)
#घोषणा CEDRUS_H265_ENTRY_POINTS_BUF_SIZE	(4 * SZ_1K)
#घोषणा CEDRUS_H265_MV_COL_BUF_UNIT_CTB_SIZE	160

काष्ठा cedrus_h265_sram_frame_info अणु
	__le32	top_pic_order_cnt;
	__le32	bottom_pic_order_cnt;
	__le32	top_mv_col_buf_addr;
	__le32	bottom_mv_col_buf_addr;
	__le32	luma_addr;
	__le32	chroma_addr;
पूर्ण __packed;

काष्ठा cedrus_h265_sram_pred_weight अणु
	__s8	delta_weight;
	__s8	offset;
पूर्ण __packed;

अटल क्रमागत cedrus_irq_status cedrus_h265_irq_status(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg;

	reg = cedrus_पढ़ो(dev, VE_DEC_H265_STATUS);
	reg &= VE_DEC_H265_STATUS_CHECK_MASK;

	अगर (reg & VE_DEC_H265_STATUS_CHECK_ERROR ||
	    !(reg & VE_DEC_H265_STATUS_SUCCESS))
		वापस CEDRUS_IRQ_ERROR;

	वापस CEDRUS_IRQ_OK;
पूर्ण

अटल व्योम cedrus_h265_irq_clear(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_ग_लिखो(dev, VE_DEC_H265_STATUS, VE_DEC_H265_STATUS_CHECK_MASK);
पूर्ण

अटल व्योम cedrus_h265_irq_disable(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_पढ़ो(dev, VE_DEC_H265_CTRL);

	reg &= ~VE_DEC_H265_CTRL_IRQ_MASK;

	cedrus_ग_लिखो(dev, VE_DEC_H265_CTRL, reg);
पूर्ण

अटल व्योम cedrus_h265_sram_ग_लिखो_offset(काष्ठा cedrus_dev *dev, u32 offset)
अणु
	cedrus_ग_लिखो(dev, VE_DEC_H265_SRAM_OFFSET, offset);
पूर्ण

अटल व्योम cedrus_h265_sram_ग_लिखो_data(काष्ठा cedrus_dev *dev, व्योम *data,
					अचिन्हित पूर्णांक size)
अणु
	u32 *word = data;

	जबतक (size >= माप(u32)) अणु
		cedrus_ग_लिखो(dev, VE_DEC_H265_SRAM_DATA, *word++);
		size -= माप(u32);
	पूर्ण
पूर्ण

अटल अंतरभूत dma_addr_t
cedrus_h265_frame_info_mv_col_buf_addr(काष्ठा cedrus_ctx *ctx,
				       अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक field)
अणु
	वापस ctx->codec.h265.mv_col_buf_addr + index *
	       ctx->codec.h265.mv_col_buf_unit_size +
	       field * ctx->codec.h265.mv_col_buf_unit_size / 2;
पूर्ण

अटल व्योम cedrus_h265_frame_info_ग_लिखो_single(काष्ठा cedrus_ctx *ctx,
						अचिन्हित पूर्णांक index,
						bool field_pic,
						u32 pic_order_cnt[],
						पूर्णांक buffer_index)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	dma_addr_t dst_luma_addr = cedrus_dst_buf_addr(ctx, buffer_index, 0);
	dma_addr_t dst_chroma_addr = cedrus_dst_buf_addr(ctx, buffer_index, 1);
	dma_addr_t mv_col_buf_addr[2] = अणु
		cedrus_h265_frame_info_mv_col_buf_addr(ctx, buffer_index, 0),
		cedrus_h265_frame_info_mv_col_buf_addr(ctx, buffer_index,
						       field_pic ? 1 : 0)
	पूर्ण;
	u32 offset = VE_DEC_H265_SRAM_OFFSET_FRAME_INFO +
		     VE_DEC_H265_SRAM_OFFSET_FRAME_INFO_UNIT * index;
	काष्ठा cedrus_h265_sram_frame_info frame_info = अणु
		.top_pic_order_cnt = cpu_to_le32(pic_order_cnt[0]),
		.bottom_pic_order_cnt = cpu_to_le32(field_pic ?
						    pic_order_cnt[1] :
						    pic_order_cnt[0]),
		.top_mv_col_buf_addr =
			cpu_to_le32(VE_DEC_H265_SRAM_DATA_ADDR_BASE(mv_col_buf_addr[0])),
		.bottom_mv_col_buf_addr = cpu_to_le32(field_pic ?
			VE_DEC_H265_SRAM_DATA_ADDR_BASE(mv_col_buf_addr[1]) :
			VE_DEC_H265_SRAM_DATA_ADDR_BASE(mv_col_buf_addr[0])),
		.luma_addr = cpu_to_le32(VE_DEC_H265_SRAM_DATA_ADDR_BASE(dst_luma_addr)),
		.chroma_addr = cpu_to_le32(VE_DEC_H265_SRAM_DATA_ADDR_BASE(dst_chroma_addr)),
	पूर्ण;

	cedrus_h265_sram_ग_लिखो_offset(dev, offset);
	cedrus_h265_sram_ग_लिखो_data(dev, &frame_info, माप(frame_info));
पूर्ण

अटल व्योम cedrus_h265_frame_info_ग_लिखो_dpb(काष्ठा cedrus_ctx *ctx,
					     स्थिर काष्ठा v4l2_hevc_dpb_entry *dpb,
					     u8 num_active_dpb_entries)
अणु
	काष्ठा vb2_queue *vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					       V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_active_dpb_entries; i++) अणु
		पूर्णांक buffer_index = vb2_find_बारtamp(vq, dpb[i].बारtamp, 0);
		u32 pic_order_cnt[2] = अणु
			dpb[i].pic_order_cnt[0],
			dpb[i].pic_order_cnt[1]
		पूर्ण;

		cedrus_h265_frame_info_ग_लिखो_single(ctx, i, dpb[i].field_pic,
						    pic_order_cnt,
						    buffer_index);
	पूर्ण
पूर्ण

अटल व्योम cedrus_h265_ref_pic_list_ग_लिखो(काष्ठा cedrus_dev *dev,
					   स्थिर काष्ठा v4l2_hevc_dpb_entry *dpb,
					   स्थिर u8 list[],
					   u8 num_ref_idx_active,
					   u32 sram_offset)
अणु
	अचिन्हित पूर्णांक i;
	u32 word = 0;

	cedrus_h265_sram_ग_लिखो_offset(dev, sram_offset);

	क्रम (i = 0; i < num_ref_idx_active; i++) अणु
		अचिन्हित पूर्णांक shअगरt = (i % 4) * 8;
		अचिन्हित पूर्णांक index = list[i];
		u8 value = list[i];

		अगर (dpb[index].rps == V4L2_HEVC_DPB_ENTRY_RPS_LT_CURR)
			value |= VE_DEC_H265_SRAM_REF_PIC_LIST_LT_REF;

		/* Each SRAM word gathers up to 4 references. */
		word |= value << shअगरt;

		/* Write the word to SRAM and clear it क्रम the next batch. */
		अगर ((i % 4) == 3 || i == (num_ref_idx_active - 1)) अणु
			cedrus_h265_sram_ग_लिखो_data(dev, &word, माप(word));
			word = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cedrus_h265_pred_weight_ग_लिखो(काष्ठा cedrus_dev *dev,
					  स्थिर s8 delta_luma_weight[],
					  स्थिर s8 luma_offset[],
					  स्थिर s8 delta_chroma_weight[][2],
					  स्थिर s8 chroma_offset[][2],
					  u8 num_ref_idx_active,
					  u32 sram_luma_offset,
					  u32 sram_chroma_offset)
अणु
	काष्ठा cedrus_h265_sram_pred_weight pred_weight[2] = अणु अणु 0 पूर्ण पूर्ण;
	अचिन्हित पूर्णांक i, j;

	cedrus_h265_sram_ग_लिखो_offset(dev, sram_luma_offset);

	क्रम (i = 0; i < num_ref_idx_active; i++) अणु
		अचिन्हित पूर्णांक index = i % 2;

		pred_weight[index].delta_weight = delta_luma_weight[i];
		pred_weight[index].offset = luma_offset[i];

		अगर (index == 1 || i == (num_ref_idx_active - 1))
			cedrus_h265_sram_ग_लिखो_data(dev, (u32 *)&pred_weight,
						    माप(pred_weight));
	पूर्ण

	cedrus_h265_sram_ग_लिखो_offset(dev, sram_chroma_offset);

	क्रम (i = 0; i < num_ref_idx_active; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			pred_weight[j].delta_weight = delta_chroma_weight[i][j];
			pred_weight[j].offset = chroma_offset[i][j];
		पूर्ण

		cedrus_h265_sram_ग_लिखो_data(dev, &pred_weight,
					    माप(pred_weight));
	पूर्ण
पूर्ण

अटल व्योम cedrus_h265_skip_bits(काष्ठा cedrus_dev *dev, पूर्णांक num)
अणु
	पूर्णांक count = 0;

	जबतक (count < num) अणु
		पूर्णांक पंचांगp = min(num - count, 32);

		cedrus_ग_लिखो(dev, VE_DEC_H265_TRIGGER,
			     VE_DEC_H265_TRIGGER_FLUSH_BITS |
			     VE_DEC_H265_TRIGGER_TYPE_N_BITS(पंचांगp));
		जबतक (cedrus_पढ़ो(dev, VE_DEC_H265_STATUS) & VE_DEC_H265_STATUS_VLD_BUSY)
			udelay(1);

		count += पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम cedrus_h265_setup(काष्ठा cedrus_ctx *ctx,
			      काष्ठा cedrus_run *run)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;
	स्थिर काष्ठा v4l2_ctrl_hevc_sps *sps;
	स्थिर काष्ठा v4l2_ctrl_hevc_pps *pps;
	स्थिर काष्ठा v4l2_ctrl_hevc_slice_params *slice_params;
	स्थिर काष्ठा v4l2_hevc_pred_weight_table *pred_weight_table;
	dma_addr_t src_buf_addr;
	dma_addr_t src_buf_end_addr;
	u32 chroma_log2_weight_denom;
	u32 output_pic_list_index;
	u32 pic_order_cnt[2];
	u32 reg;

	sps = run->h265.sps;
	pps = run->h265.pps;
	slice_params = run->h265.slice_params;
	pred_weight_table = &slice_params->pred_weight_table;

	/* MV column buffer size and allocation. */
	अगर (!ctx->codec.h265.mv_col_buf_size) अणु
		अचिन्हित पूर्णांक num_buffers =
			run->dst->vb2_buf.vb2_queue->num_buffers;
		अचिन्हित पूर्णांक log2_max_luma_coding_block_size =
			sps->log2_min_luma_coding_block_size_minus3 + 3 +
			sps->log2_dअगरf_max_min_luma_coding_block_size;
		अचिन्हित पूर्णांक ctb_size_luma =
			1UL << log2_max_luma_coding_block_size;

		/*
		 * Each CTB requires a MV col buffer with a specअगरic unit size.
		 * Since the address is given with missing lsb bits, 1 KiB is
		 * added to each buffer to ensure proper alignment.
		 */
		ctx->codec.h265.mv_col_buf_unit_size =
			DIV_ROUND_UP(ctx->src_fmt.width, ctb_size_luma) *
			DIV_ROUND_UP(ctx->src_fmt.height, ctb_size_luma) *
			CEDRUS_H265_MV_COL_BUF_UNIT_CTB_SIZE + SZ_1K;

		ctx->codec.h265.mv_col_buf_size = num_buffers *
			ctx->codec.h265.mv_col_buf_unit_size;

		ctx->codec.h265.mv_col_buf =
			dma_alloc_coherent(dev->dev,
					   ctx->codec.h265.mv_col_buf_size,
					   &ctx->codec.h265.mv_col_buf_addr,
					   GFP_KERNEL);
		अगर (!ctx->codec.h265.mv_col_buf) अणु
			ctx->codec.h265.mv_col_buf_size = 0;
			// TODO: Abort the process here.
			वापस;
		पूर्ण
	पूर्ण

	/* Activate H265 engine. */
	cedrus_engine_enable(ctx, CEDRUS_CODEC_H265);

	/* Source offset and length in bits. */

	cedrus_ग_लिखो(dev, VE_DEC_H265_BITS_OFFSET, 0);

	reg = slice_params->bit_size;
	cedrus_ग_लिखो(dev, VE_DEC_H265_BITS_LEN, reg);

	/* Source beginning and end addresses. */

	src_buf_addr = vb2_dma_contig_plane_dma_addr(&run->src->vb2_buf, 0);

	reg = VE_DEC_H265_BITS_ADDR_BASE(src_buf_addr);
	reg |= VE_DEC_H265_BITS_ADDR_VALID_SLICE_DATA;
	reg |= VE_DEC_H265_BITS_ADDR_LAST_SLICE_DATA;
	reg |= VE_DEC_H265_BITS_ADDR_FIRST_SLICE_DATA;

	cedrus_ग_लिखो(dev, VE_DEC_H265_BITS_ADDR, reg);

	src_buf_end_addr = src_buf_addr +
			   DIV_ROUND_UP(slice_params->bit_size, 8);

	reg = VE_DEC_H265_BITS_END_ADDR_BASE(src_buf_end_addr);
	cedrus_ग_लिखो(dev, VE_DEC_H265_BITS_END_ADDR, reg);

	/* Coding tree block address: start at the beginning. */
	reg = VE_DEC_H265_DEC_CTB_ADDR_X(0) | VE_DEC_H265_DEC_CTB_ADDR_Y(0);
	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_CTB_ADDR, reg);

	cedrus_ग_लिखो(dev, VE_DEC_H265_TILE_START_CTB, 0);
	cedrus_ग_लिखो(dev, VE_DEC_H265_TILE_END_CTB, 0);

	/* Clear the number of correctly-decoded coding tree blocks. */
	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_CTB_NUM, 0);

	/* Initialize bitstream access. */
	cedrus_ग_लिखो(dev, VE_DEC_H265_TRIGGER, VE_DEC_H265_TRIGGER_INIT_SWDEC);

	cedrus_h265_skip_bits(dev, slice_params->data_bit_offset);

	/* Bitstream parameters. */

	reg = VE_DEC_H265_DEC_NAL_HDR_NAL_UNIT_TYPE(slice_params->nal_unit_type) |
	      VE_DEC_H265_DEC_NAL_HDR_NUH_TEMPORAL_ID_PLUS1(slice_params->nuh_temporal_id_plus1);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_NAL_HDR, reg);

	/* SPS. */

	reg = VE_DEC_H265_DEC_SPS_HDR_MAX_TRANSFORM_HIERARCHY_DEPTH_INTRA(sps->max_transक्रमm_hierarchy_depth_पूर्णांकra) |
	      VE_DEC_H265_DEC_SPS_HDR_MAX_TRANSFORM_HIERARCHY_DEPTH_INTER(sps->max_transक्रमm_hierarchy_depth_पूर्णांकer) |
	      VE_DEC_H265_DEC_SPS_HDR_LOG2_DIFF_MAX_MIN_TRANSFORM_BLOCK_SIZE(sps->log2_dअगरf_max_min_luma_transक्रमm_block_size) |
	      VE_DEC_H265_DEC_SPS_HDR_LOG2_MIN_TRANSFORM_BLOCK_SIZE_MINUS2(sps->log2_min_luma_transक्रमm_block_size_minus2) |
	      VE_DEC_H265_DEC_SPS_HDR_LOG2_DIFF_MAX_MIN_LUMA_CODING_BLOCK_SIZE(sps->log2_dअगरf_max_min_luma_coding_block_size) |
	      VE_DEC_H265_DEC_SPS_HDR_LOG2_MIN_LUMA_CODING_BLOCK_SIZE_MINUS3(sps->log2_min_luma_coding_block_size_minus3) |
	      VE_DEC_H265_DEC_SPS_HDR_BIT_DEPTH_CHROMA_MINUS8(sps->bit_depth_chroma_minus8) |
	      VE_DEC_H265_DEC_SPS_HDR_BIT_DEPTH_LUMA_MINUS8(sps->bit_depth_luma_minus8) |
	      VE_DEC_H265_DEC_SPS_HDR_CHROMA_FORMAT_IDC(sps->chroma_क्रमmat_idc);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SPS_HDR_FLAG_STRONG_INTRA_SMOOTHING_ENABLE,
				V4L2_HEVC_SPS_FLAG_STRONG_INTRA_SMOOTHING_ENABLED,
				sps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SPS_HDR_FLAG_SPS_TEMPORAL_MVP_ENABLED,
				V4L2_HEVC_SPS_FLAG_SPS_TEMPORAL_MVP_ENABLED,
				sps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SPS_HDR_FLAG_SAMPLE_ADAPTIVE_OFFSET_ENABLED,
				V4L2_HEVC_SPS_FLAG_SAMPLE_ADAPTIVE_OFFSET,
				sps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SPS_HDR_FLAG_AMP_ENABLED,
				V4L2_HEVC_SPS_FLAG_AMP_ENABLED, sps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SPS_HDR_FLAG_SEPARATE_COLOUR_PLANE,
				V4L2_HEVC_SPS_FLAG_SEPARATE_COLOUR_PLANE,
				sps->flags);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_SPS_HDR, reg);

	reg = VE_DEC_H265_DEC_PCM_CTRL_LOG2_DIFF_MAX_MIN_PCM_LUMA_CODING_BLOCK_SIZE(sps->log2_dअगरf_max_min_pcm_luma_coding_block_size) |
	      VE_DEC_H265_DEC_PCM_CTRL_LOG2_MIN_PCM_LUMA_CODING_BLOCK_SIZE_MINUS3(sps->log2_min_pcm_luma_coding_block_size_minus3) |
	      VE_DEC_H265_DEC_PCM_CTRL_PCM_SAMPLE_BIT_DEPTH_CHROMA_MINUS1(sps->pcm_sample_bit_depth_chroma_minus1) |
	      VE_DEC_H265_DEC_PCM_CTRL_PCM_SAMPLE_BIT_DEPTH_LUMA_MINUS1(sps->pcm_sample_bit_depth_luma_minus1);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PCM_CTRL_FLAG_PCM_ENABLED,
				V4L2_HEVC_SPS_FLAG_PCM_ENABLED, sps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PCM_CTRL_FLAG_PCM_LOOP_FILTER_DISABLED,
				V4L2_HEVC_SPS_FLAG_PCM_LOOP_FILTER_DISABLED,
				sps->flags);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_PCM_CTRL, reg);

	/* PPS. */

	reg = VE_DEC_H265_DEC_PPS_CTRL0_PPS_CR_QP_OFFSET(pps->pps_cr_qp_offset) |
	      VE_DEC_H265_DEC_PPS_CTRL0_PPS_CB_QP_OFFSET(pps->pps_cb_qp_offset) |
	      VE_DEC_H265_DEC_PPS_CTRL0_INIT_QP_MINUS26(pps->init_qp_minus26) |
	      VE_DEC_H265_DEC_PPS_CTRL0_DIFF_CU_QP_DELTA_DEPTH(pps->dअगरf_cu_qp_delta_depth);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL0_FLAG_CU_QP_DELTA_ENABLED,
				V4L2_HEVC_PPS_FLAG_CU_QP_DELTA_ENABLED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL0_FLAG_TRANSFORM_SKIP_ENABLED,
				V4L2_HEVC_PPS_FLAG_TRANSFORM_SKIP_ENABLED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL0_FLAG_CONSTRAINED_INTRA_PRED,
				V4L2_HEVC_PPS_FLAG_CONSTRAINED_INTRA_PRED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL0_FLAG_SIGN_DATA_HIDING_ENABLED,
				V4L2_HEVC_PPS_FLAG_SIGN_DATA_HIDING_ENABLED,
				pps->flags);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_PPS_CTRL0, reg);

	reg = VE_DEC_H265_DEC_PPS_CTRL1_LOG2_PARALLEL_MERGE_LEVEL_MINUS2(pps->log2_parallel_merge_level_minus2);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_PPS_LOOP_FILTER_ACROSS_SLICES_ENABLED,
				V4L2_HEVC_PPS_FLAG_PPS_LOOP_FILTER_ACROSS_SLICES_ENABLED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_LOOP_FILTER_ACROSS_TILES_ENABLED,
				V4L2_HEVC_PPS_FLAG_LOOP_FILTER_ACROSS_TILES_ENABLED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_ENTROPY_CODING_SYNC_ENABLED,
				V4L2_HEVC_PPS_FLAG_ENTROPY_CODING_SYNC_ENABLED,
				pps->flags);

	/* TODO: VE_DEC_H265_DEC_PPS_CTRL1_FLAG_TILES_ENABLED */

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_TRANSQUANT_BYPASS_ENABLED,
				V4L2_HEVC_PPS_FLAG_TRANSQUANT_BYPASS_ENABLED,
				pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_WEIGHTED_BIPRED,
				V4L2_HEVC_PPS_FLAG_WEIGHTED_BIPRED, pps->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_PPS_CTRL1_FLAG_WEIGHTED_PRED,
				V4L2_HEVC_PPS_FLAG_WEIGHTED_PRED, pps->flags);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_PPS_CTRL1, reg);

	/* Slice Parameters. */

	reg = VE_DEC_H265_DEC_SLICE_HDR_INFO0_PICTURE_TYPE(slice_params->pic_काष्ठा) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_FIVE_MINUS_MAX_NUM_MERGE_CAND(slice_params->five_minus_max_num_merge_cand) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_NUM_REF_IDX_L1_ACTIVE_MINUS1(slice_params->num_ref_idx_l1_active_minus1) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_NUM_REF_IDX_L0_ACTIVE_MINUS1(slice_params->num_ref_idx_l0_active_minus1) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_COLLOCATED_REF_IDX(slice_params->collocated_ref_idx) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_COLOUR_PLANE_ID(slice_params->colour_plane_id) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO0_SLICE_TYPE(slice_params->slice_type);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_COLLOCATED_FROM_L0,
				V4L2_HEVC_SLICE_PARAMS_FLAG_COLLOCATED_FROM_L0,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_CABAC_INIT,
				V4L2_HEVC_SLICE_PARAMS_FLAG_CABAC_INIT,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_MVD_L1_ZERO,
				V4L2_HEVC_SLICE_PARAMS_FLAG_MVD_L1_ZERO,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_SLICE_SAO_CHROMA,
				V4L2_HEVC_SLICE_PARAMS_FLAG_SLICE_SAO_CHROMA,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_SLICE_SAO_LUMA,
				V4L2_HEVC_SLICE_PARAMS_FLAG_SLICE_SAO_LUMA,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_SLICE_TEMPORAL_MVP_ENABLE,
				V4L2_HEVC_SLICE_PARAMS_FLAG_SLICE_TEMPORAL_MVP_ENABLED,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_DEPENDENT_SLICE_SEGMENT,
				V4L2_HEVC_PPS_FLAG_DEPENDENT_SLICE_SEGMENT,
				pps->flags);

	/* FIXME: For multi-slice support. */
	reg |= VE_DEC_H265_DEC_SLICE_HDR_INFO0_FLAG_FIRST_SLICE_SEGMENT_IN_PIC;

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_SLICE_HDR_INFO0, reg);

	reg = VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_TC_OFFSET_DIV2(slice_params->slice_tc_offset_भाग2) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_BETA_OFFSET_DIV2(slice_params->slice_beta_offset_भाग2) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_POC_BIGEST_IN_RPS_ST(slice_params->num_rps_poc_st_curr_after == 0) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_CR_QP_OFFSET(slice_params->slice_cr_qp_offset) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_CB_QP_OFFSET(slice_params->slice_cb_qp_offset) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO1_SLICE_QP_DELTA(slice_params->slice_qp_delta);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO1_FLAG_SLICE_DEBLOCKING_FILTER_DISABLED,
				V4L2_HEVC_SLICE_PARAMS_FLAG_SLICE_DEBLOCKING_FILTER_DISABLED,
				slice_params->flags);

	reg |= VE_DEC_H265_FLAG(VE_DEC_H265_DEC_SLICE_HDR_INFO1_FLAG_SLICE_LOOP_FILTER_ACROSS_SLICES_ENABLED,
				V4L2_HEVC_SLICE_PARAMS_FLAG_SLICE_LOOP_FILTER_ACROSS_SLICES_ENABLED,
				slice_params->flags);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_SLICE_HDR_INFO1, reg);

	chroma_log2_weight_denom = pred_weight_table->luma_log2_weight_denom +
				   pred_weight_table->delta_chroma_log2_weight_denom;
	reg = VE_DEC_H265_DEC_SLICE_HDR_INFO2_NUM_ENTRY_POINT_OFFSETS(0) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO2_CHROMA_LOG2_WEIGHT_DENOM(chroma_log2_weight_denom) |
	      VE_DEC_H265_DEC_SLICE_HDR_INFO2_LUMA_LOG2_WEIGHT_DENOM(pred_weight_table->luma_log2_weight_denom);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_SLICE_HDR_INFO2, reg);

	/* Decoded picture size. */

	reg = VE_DEC_H265_DEC_PIC_SIZE_WIDTH(ctx->src_fmt.width) |
	      VE_DEC_H265_DEC_PIC_SIZE_HEIGHT(ctx->src_fmt.height);

	cedrus_ग_लिखो(dev, VE_DEC_H265_DEC_PIC_SIZE, reg);

	/* Scaling list. */

	reg = VE_DEC_H265_SCALING_LIST_CTRL0_DEFAULT;
	cedrus_ग_लिखो(dev, VE_DEC_H265_SCALING_LIST_CTRL0, reg);

	/* Neightbor inक्रमmation address. */
	reg = VE_DEC_H265_NEIGHBOR_INFO_ADDR_BASE(ctx->codec.h265.neighbor_info_buf_addr);
	cedrus_ग_लिखो(dev, VE_DEC_H265_NEIGHBOR_INFO_ADDR, reg);

	/* Write decoded picture buffer in pic list. */
	cedrus_h265_frame_info_ग_लिखो_dpb(ctx, slice_params->dpb,
					 slice_params->num_active_dpb_entries);

	/* Output frame. */

	output_pic_list_index = V4L2_HEVC_DPB_ENTRIES_NUM_MAX;
	pic_order_cnt[0] = slice_params->slice_pic_order_cnt;
	pic_order_cnt[1] = slice_params->slice_pic_order_cnt;

	cedrus_h265_frame_info_ग_लिखो_single(ctx, output_pic_list_index,
					    slice_params->pic_काष्ठा != 0,
					    pic_order_cnt,
					    run->dst->vb2_buf.index);

	cedrus_ग_लिखो(dev, VE_DEC_H265_OUTPUT_FRAME_IDX, output_pic_list_index);

	/* Reference picture list 0 (क्रम P/B frames). */
	अगर (slice_params->slice_type != V4L2_HEVC_SLICE_TYPE_I) अणु
		cedrus_h265_ref_pic_list_ग_लिखो(dev, slice_params->dpb,
					       slice_params->ref_idx_l0,
					       slice_params->num_ref_idx_l0_active_minus1 + 1,
					       VE_DEC_H265_SRAM_OFFSET_REF_PIC_LIST0);

		अगर ((pps->flags & V4L2_HEVC_PPS_FLAG_WEIGHTED_PRED) ||
		    (pps->flags & V4L2_HEVC_PPS_FLAG_WEIGHTED_BIPRED))
			cedrus_h265_pred_weight_ग_लिखो(dev,
						      pred_weight_table->delta_luma_weight_l0,
						      pred_weight_table->luma_offset_l0,
						      pred_weight_table->delta_chroma_weight_l0,
						      pred_weight_table->chroma_offset_l0,
						      slice_params->num_ref_idx_l0_active_minus1 + 1,
						      VE_DEC_H265_SRAM_OFFSET_PRED_WEIGHT_LUMA_L0,
						      VE_DEC_H265_SRAM_OFFSET_PRED_WEIGHT_CHROMA_L0);
	पूर्ण

	/* Reference picture list 1 (क्रम B frames). */
	अगर (slice_params->slice_type == V4L2_HEVC_SLICE_TYPE_B) अणु
		cedrus_h265_ref_pic_list_ग_लिखो(dev, slice_params->dpb,
					       slice_params->ref_idx_l1,
					       slice_params->num_ref_idx_l1_active_minus1 + 1,
					       VE_DEC_H265_SRAM_OFFSET_REF_PIC_LIST1);

		अगर (pps->flags & V4L2_HEVC_PPS_FLAG_WEIGHTED_BIPRED)
			cedrus_h265_pred_weight_ग_लिखो(dev,
						      pred_weight_table->delta_luma_weight_l1,
						      pred_weight_table->luma_offset_l1,
						      pred_weight_table->delta_chroma_weight_l1,
						      pred_weight_table->chroma_offset_l1,
						      slice_params->num_ref_idx_l1_active_minus1 + 1,
						      VE_DEC_H265_SRAM_OFFSET_PRED_WEIGHT_LUMA_L1,
						      VE_DEC_H265_SRAM_OFFSET_PRED_WEIGHT_CHROMA_L1);
	पूर्ण

	/* Enable appropriate पूर्णांकerruptions. */
	cedrus_ग_लिखो(dev, VE_DEC_H265_CTRL, VE_DEC_H265_CTRL_IRQ_MASK);
पूर्ण

अटल पूर्णांक cedrus_h265_start(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	/* The buffer size is calculated at setup समय. */
	ctx->codec.h265.mv_col_buf_size = 0;

	ctx->codec.h265.neighbor_info_buf =
		dma_alloc_coherent(dev->dev, CEDRUS_H265_NEIGHBOR_INFO_BUF_SIZE,
				   &ctx->codec.h265.neighbor_info_buf_addr,
				   GFP_KERNEL);
	अगर (!ctx->codec.h265.neighbor_info_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम cedrus_h265_stop(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	अगर (ctx->codec.h265.mv_col_buf_size > 0) अणु
		dma_मुक्त_coherent(dev->dev, ctx->codec.h265.mv_col_buf_size,
				  ctx->codec.h265.mv_col_buf,
				  ctx->codec.h265.mv_col_buf_addr);

		ctx->codec.h265.mv_col_buf_size = 0;
	पूर्ण

	dma_मुक्त_coherent(dev->dev, CEDRUS_H265_NEIGHBOR_INFO_BUF_SIZE,
			  ctx->codec.h265.neighbor_info_buf,
			  ctx->codec.h265.neighbor_info_buf_addr);
पूर्ण

अटल व्योम cedrus_h265_trigger(काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा cedrus_dev *dev = ctx->dev;

	cedrus_ग_लिखो(dev, VE_DEC_H265_TRIGGER, VE_DEC_H265_TRIGGER_DEC_SLICE);
पूर्ण

काष्ठा cedrus_dec_ops cedrus_dec_ops_h265 = अणु
	.irq_clear	= cedrus_h265_irq_clear,
	.irq_disable	= cedrus_h265_irq_disable,
	.irq_status	= cedrus_h265_irq_status,
	.setup		= cedrus_h265_setup,
	.start		= cedrus_h265_start,
	.stop		= cedrus_h265_stop,
	.trigger	= cedrus_h265_trigger,
पूर्ण;
