<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 */

#समावेश "hantro.h"

/*
 * probs table with packed
 */
काष्ठा vp8_prob_tbl_packed अणु
	u8 prob_mb_skip_false;
	u8 prob_पूर्णांकra;
	u8 prob_ref_last;
	u8 prob_ref_golden;
	u8 prob_segment[3];
	u8 padding0;

	u8 prob_luma_16x16_pred_mode[4];
	u8 prob_chroma_pred_mode[3];
	u8 padding1;

	/* mv prob */
	u8 prob_mv_context[2][V4L2_VP8_MV_PROB_CNT];
	u8 padding2[2];

	/* coeff probs */
	u8 prob_coeffs[4][8][3][V4L2_VP8_COEFF_PROB_CNT];
	u8 padding3[96];
पूर्ण;

/*
 * filter taps taken to 7-bit precision,
 * reference RFC6386#Page-16, filters[8][6]
 */
स्थिर u32 hantro_vp8_dec_mc_filter[8][6] = अणु
	अणु 0, 0, 128, 0, 0, 0 पूर्ण,
	अणु 0, -6, 123, 12, -1, 0 पूर्ण,
	अणु 2, -11, 108, 36, -8, 1 पूर्ण,
	अणु 0, -9, 93, 50, -6, 0 पूर्ण,
	अणु 3, -16, 77, 77, -16, 3 पूर्ण,
	अणु 0, -6, 50, 93, -9, 0 पूर्ण,
	अणु 1, -8, 36, 108, -11, 2 पूर्ण,
	अणु 0, -1, 12, 123, -6, 0 पूर्ण
पूर्ण;

व्योम hantro_vp8_prob_update(काष्ठा hantro_ctx *ctx,
			    स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	स्थिर काष्ठा v4l2_vp8_entropy *entropy = &hdr->entropy;
	u32 i, j, k;
	u8 *dst;

	/* first probs */
	dst = ctx->vp8_dec.prob_tbl.cpu;

	dst[0] = hdr->prob_skip_false;
	dst[1] = hdr->prob_पूर्णांकra;
	dst[2] = hdr->prob_last;
	dst[3] = hdr->prob_gf;
	dst[4] = hdr->segment.segment_probs[0];
	dst[5] = hdr->segment.segment_probs[1];
	dst[6] = hdr->segment.segment_probs[2];
	dst[7] = 0;

	dst += 8;
	dst[0] = entropy->y_mode_probs[0];
	dst[1] = entropy->y_mode_probs[1];
	dst[2] = entropy->y_mode_probs[2];
	dst[3] = entropy->y_mode_probs[3];
	dst[4] = entropy->uv_mode_probs[0];
	dst[5] = entropy->uv_mode_probs[1];
	dst[6] = entropy->uv_mode_probs[2];
	dst[7] = 0; /*unused */

	/* mv probs */
	dst += 8;
	dst[0] = entropy->mv_probs[0][0]; /* is लघु */
	dst[1] = entropy->mv_probs[1][0];
	dst[2] = entropy->mv_probs[0][1]; /* sign */
	dst[3] = entropy->mv_probs[1][1];
	dst[4] = entropy->mv_probs[0][8 + 9];
	dst[5] = entropy->mv_probs[0][9 + 9];
	dst[6] = entropy->mv_probs[1][8 + 9];
	dst[7] = entropy->mv_probs[1][9 + 9];
	dst += 8;
	क्रम (i = 0; i < 2; ++i) अणु
		क्रम (j = 0; j < 8; j += 4) अणु
			dst[0] = entropy->mv_probs[i][j + 9 + 0];
			dst[1] = entropy->mv_probs[i][j + 9 + 1];
			dst[2] = entropy->mv_probs[i][j + 9 + 2];
			dst[3] = entropy->mv_probs[i][j + 9 + 3];
			dst += 4;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 2; ++i) अणु
		dst[0] = entropy->mv_probs[i][0 + 2];
		dst[1] = entropy->mv_probs[i][1 + 2];
		dst[2] = entropy->mv_probs[i][2 + 2];
		dst[3] = entropy->mv_probs[i][3 + 2];
		dst[4] = entropy->mv_probs[i][4 + 2];
		dst[5] = entropy->mv_probs[i][5 + 2];
		dst[6] = entropy->mv_probs[i][6 + 2];
		dst[7] = 0;	/*unused */
		dst += 8;
	पूर्ण

	/* coeff probs (header part) */
	dst = ctx->vp8_dec.prob_tbl.cpu;
	dst += (8 * 7);
	क्रम (i = 0; i < 4; ++i) अणु
		क्रम (j = 0; j < 8; ++j) अणु
			क्रम (k = 0; k < 3; ++k) अणु
				dst[0] = entropy->coeff_probs[i][j][k][0];
				dst[1] = entropy->coeff_probs[i][j][k][1];
				dst[2] = entropy->coeff_probs[i][j][k][2];
				dst[3] = entropy->coeff_probs[i][j][k][3];
				dst += 4;
			पूर्ण
		पूर्ण
	पूर्ण

	/* coeff probs (footer part) */
	dst = ctx->vp8_dec.prob_tbl.cpu;
	dst += (8 * 55);
	क्रम (i = 0; i < 4; ++i) अणु
		क्रम (j = 0; j < 8; ++j) अणु
			क्रम (k = 0; k < 3; ++k) अणु
				dst[0] = entropy->coeff_probs[i][j][k][4];
				dst[1] = entropy->coeff_probs[i][j][k][5];
				dst[2] = entropy->coeff_probs[i][j][k][6];
				dst[3] = entropy->coeff_probs[i][j][k][7];
				dst[4] = entropy->coeff_probs[i][j][k][8];
				dst[5] = entropy->coeff_probs[i][j][k][9];
				dst[6] = entropy->coeff_probs[i][j][k][10];
				dst[7] = 0;	/*unused */
				dst += 8;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hantro_vp8_dec_init(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा hantro_aux_buf *aux_buf;
	अचिन्हित पूर्णांक mb_width, mb_height;
	माप_प्रकार segment_map_size;
	पूर्णांक ret;

	/* segment map table size calculation */
	mb_width = DIV_ROUND_UP(ctx->dst_fmt.width, 16);
	mb_height = DIV_ROUND_UP(ctx->dst_fmt.height, 16);
	segment_map_size = round_up(DIV_ROUND_UP(mb_width * mb_height, 4), 64);

	/*
	 * In context init the dma buffer क्रम segment map must be allocated.
	 * And the data in segment map buffer must be set to all zero.
	 */
	aux_buf = &ctx->vp8_dec.segment_map;
	aux_buf->size = segment_map_size;
	aux_buf->cpu = dma_alloc_coherent(vpu->dev, aux_buf->size,
					  &aux_buf->dma, GFP_KERNEL);
	अगर (!aux_buf->cpu)
		वापस -ENOMEM;

	/*
	 * Allocate probability table buffer,
	 * total 1208 bytes, 4K page is far enough.
	 */
	aux_buf = &ctx->vp8_dec.prob_tbl;
	aux_buf->size = माप(काष्ठा vp8_prob_tbl_packed);
	aux_buf->cpu = dma_alloc_coherent(vpu->dev, aux_buf->size,
					  &aux_buf->dma, GFP_KERNEL);
	अगर (!aux_buf->cpu) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_seg_map;
	पूर्ण

	वापस 0;

err_मुक्त_seg_map:
	dma_मुक्त_coherent(vpu->dev, ctx->vp8_dec.segment_map.size,
			  ctx->vp8_dec.segment_map.cpu,
			  ctx->vp8_dec.segment_map.dma);

	वापस ret;
पूर्ण

व्योम hantro_vp8_dec_निकास(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_vp8_dec_hw_ctx *vp8_dec = &ctx->vp8_dec;
	काष्ठा hantro_dev *vpu = ctx->dev;

	dma_मुक्त_coherent(vpu->dev, vp8_dec->segment_map.size,
			  vp8_dec->segment_map.cpu, vp8_dec->segment_map.dma);
	dma_मुक्त_coherent(vpu->dev, vp8_dec->prob_tbl.size,
			  vp8_dec->prob_tbl.cpu, vp8_dec->prob_tbl.dma);
पूर्ण
