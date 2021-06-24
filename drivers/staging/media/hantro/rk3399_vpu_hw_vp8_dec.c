<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Rockchip VPU codec vp8 decode driver
 *
 * Copyright (C) 2014 Rockchip Electronics Co., Ltd.
 *	ZhiChao Yu <zhichao.yu@rock-chips.com>
 *
 * Copyright (C) 2014 Google LLC.
 *      Tomasz Figa <tfiga@chromium.org>
 *
 * Copyright (C) 2015 Rockchip Electronics Co., Ltd.
 *      Alpha Lin <alpha.lin@rock-chips.com>
 */

#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "hantro_hw.h"
#समावेश "hantro.h"
#समावेश "hantro_g1_regs.h"

#घोषणा VDPU_REG_DEC_CTRL0			0x0c8
#घोषणा VDPU_REG_STREAM_LEN			0x0cc
#घोषणा VDPU_REG_DEC_FORMAT			0x0d4
#घोषणा     VDPU_REG_DEC_CTRL0_DEC_MODE(x)		(((x) & 0xf) << 0)
#घोषणा VDPU_REG_DATA_ENDIAN			0x0d8
#घोषणा     VDPU_REG_CONFIG_DEC_STRENDIAN_E		BIT(5)
#घोषणा     VDPU_REG_CONFIG_DEC_STRSWAP32_E		BIT(4)
#घोषणा     VDPU_REG_CONFIG_DEC_OUTSWAP32_E		BIT(3)
#घोषणा     VDPU_REG_CONFIG_DEC_INSWAP32_E		BIT(2)
#घोषणा     VDPU_REG_CONFIG_DEC_OUT_ENDIAN		BIT(1)
#घोषणा     VDPU_REG_CONFIG_DEC_IN_ENDIAN		BIT(0)
#घोषणा VDPU_REG_AXI_CTRL			0x0e0
#घोषणा     VDPU_REG_CONFIG_DEC_MAX_BURST(x)		(((x) & 0x1f) << 16)
#घोषणा VDPU_REG_EN_FLAGS			0x0e4
#घोषणा     VDPU_REG_DEC_CTRL0_PIC_INTER_E		BIT(14)
#घोषणा     VDPU_REG_CONFIG_DEC_TIMEOUT_E		BIT(5)
#घोषणा     VDPU_REG_CONFIG_DEC_CLK_GATE_E		BIT(4)
#घोषणा VDPU_REG_PRED_FLT			0x0ec
#घोषणा VDPU_REG_ADDR_QTABLE			0x0f4
#घोषणा VDPU_REG_ADDR_DST			0x0fc
#घोषणा VDPU_REG_ADDR_STR			0x100
#घोषणा VDPU_REG_VP8_PIC_MB_SIZE		0x1e0
#घोषणा VDPU_REG_VP8_DCT_START_BIT		0x1e4
#घोषणा     VDPU_REG_DEC_CTRL4_VC1_HEIGHT_EXT		BIT(13)
#घोषणा     VDPU_REG_DEC_CTRL4_BILIN_MC_E		BIT(12)
#घोषणा VDPU_REG_VP8_CTRL0			0x1e8
#घोषणा VDPU_REG_VP8_DATA_VAL			0x1f0
#घोषणा VDPU_REG_PRED_FLT7			0x1f4
#घोषणा VDPU_REG_PRED_FLT8			0x1f8
#घोषणा VDPU_REG_PRED_FLT9			0x1fc
#घोषणा VDPU_REG_PRED_FLT10			0x200
#घोषणा VDPU_REG_FILTER_LEVEL			0x204
#घोषणा VDPU_REG_VP8_QUANTER0			0x208
#घोषणा VDPU_REG_VP8_ADDR_REF0			0x20c
#घोषणा VDPU_REG_FILTER_MB_ADJ			0x210
#घोषणा     VDPU_REG_REF_PIC_FILT_TYPE_E		BIT(31)
#घोषणा     VDPU_REG_REF_PIC_FILT_SHARPNESS(x)		(((x) & 0x7) << 28)
#घोषणा VDPU_REG_FILTER_REF_ADJ			0x214
#घोषणा VDPU_REG_VP8_ADDR_REF2_5(i)		(0x218 + ((i) * 0x4))
#घोषणा     VDPU_REG_VP8_GREF_SIGN_BIAS			BIT(0)
#घोषणा     VDPU_REG_VP8_AREF_SIGN_BIAS			BIT(0)
#घोषणा VDPU_REG_VP8_DCT_BASE(i)		\
		(0x230 + ((((i) < 5) ? (i) : ((i) + 1)) * 0x4))
#घोषणा VDPU_REG_VP8_ADDR_CTRL_PART		0x244
#घोषणा VDPU_REG_VP8_SEGMENT_VAL		0x254
#घोषणा     VDPU_REG_FWD_PIC1_SEGMENT_BASE(x)		((x) << 0)
#घोषणा     VDPU_REG_FWD_PIC1_SEGMENT_UPD_E		BIT(1)
#घोषणा     VDPU_REG_FWD_PIC1_SEGMENT_E			BIT(0)
#घोषणा VDPU_REG_VP8_DCT_START_BIT2		0x258
#घोषणा VDPU_REG_VP8_QUANTER1			0x25c
#घोषणा VDPU_REG_VP8_QUANTER2			0x260
#घोषणा VDPU_REG_PRED_FLT1			0x264
#घोषणा VDPU_REG_PRED_FLT2			0x268
#घोषणा VDPU_REG_PRED_FLT3			0x26c
#घोषणा VDPU_REG_PRED_FLT4			0x270
#घोषणा VDPU_REG_PRED_FLT5			0x274
#घोषणा VDPU_REG_PRED_FLT6			0x278

अटल स्थिर काष्ठा hantro_reg vp8_dec_dct_base[8] = अणु
	अणु VDPU_REG_ADDR_STR, 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(0), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(1), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(2), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(3), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(4), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(5), 0, 0xffffffff पूर्ण,
	अणु VDPU_REG_VP8_DCT_BASE(6), 0, 0xffffffff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_lf_level[4] = अणु
	अणु VDPU_REG_FILTER_LEVEL, 18, 0x3f पूर्ण,
	अणु VDPU_REG_FILTER_LEVEL, 12, 0x3f पूर्ण,
	अणु VDPU_REG_FILTER_LEVEL, 6, 0x3f पूर्ण,
	अणु VDPU_REG_FILTER_LEVEL, 0, 0x3f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_adj[4] = अणु
	अणु VDPU_REG_FILTER_MB_ADJ, 21, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_MB_ADJ, 14, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_MB_ADJ, 7, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_MB_ADJ, 0, 0x7f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_ref_adj[4] = अणु
	अणु VDPU_REG_FILTER_REF_ADJ, 21, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_REF_ADJ, 14, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_REF_ADJ, 7, 0x7f पूर्ण,
	अणु VDPU_REG_FILTER_REF_ADJ, 0, 0x7f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_quant[4] = अणु
	अणु VDPU_REG_VP8_QUANTER0, 11, 0x7ff पूर्ण,
	अणु VDPU_REG_VP8_QUANTER0, 0, 0x7ff पूर्ण,
	अणु VDPU_REG_VP8_QUANTER1, 11, 0x7ff पूर्ण,
	अणु VDPU_REG_VP8_QUANTER1, 0, 0x7ff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_quant_delta[5] = अणु
	अणु VDPU_REG_VP8_QUANTER0, 27, 0x1f पूर्ण,
	अणु VDPU_REG_VP8_QUANTER0, 22, 0x1f पूर्ण,
	अणु VDPU_REG_VP8_QUANTER1, 27, 0x1f पूर्ण,
	अणु VDPU_REG_VP8_QUANTER1, 22, 0x1f पूर्ण,
	अणु VDPU_REG_VP8_QUANTER2, 27, 0x1f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_dct_start_bits[8] = अणु
	अणु VDPU_REG_VP8_CTRL0, 26, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT, 26, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT, 20, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT2, 24, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT2, 18, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT2, 12, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT2, 6, 0x3f पूर्ण,
	अणु VDPU_REG_VP8_DCT_START_BIT2, 0, 0x3f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_pred_bc_tap[8][6] = अणु
	अणु
		अणु 0, 0, 0पूर्ण,
		अणु VDPU_REG_PRED_FLT, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT1, 22, 0x3ff पूर्ण,
		अणु 0, 0, 0पूर्ण,
	पूर्ण, अणु
		अणु 0, 0, 0पूर्ण,
		अणु VDPU_REG_PRED_FLT1, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT1, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT2, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT2, 12, 0x3ff पूर्ण,
		अणु 0, 0, 0पूर्ण,
	पूर्ण, अणु
		अणु VDPU_REG_PRED_FLT10, 10, 0x3 पूर्ण,
		अणु VDPU_REG_PRED_FLT2, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT3, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT3, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT3, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT10, 8, 0x3पूर्ण,
	पूर्ण, अणु
		अणु 0, 0, 0पूर्ण,
		अणु VDPU_REG_PRED_FLT4, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT4, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT4, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT5, 22, 0x3ff पूर्ण,
		अणु 0, 0, 0पूर्ण,
	पूर्ण, अणु
		अणु VDPU_REG_PRED_FLT10, 6, 0x3 पूर्ण,
		अणु VDPU_REG_PRED_FLT5, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT5, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT6, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT6, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT10, 4, 0x3 पूर्ण,
	पूर्ण, अणु
		अणु 0, 0, 0पूर्ण,
		अणु VDPU_REG_PRED_FLT6, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT7, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT7, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT7, 2, 0x3ff पूर्ण,
		अणु 0, 0, 0पूर्ण,
	पूर्ण, अणु
		अणु VDPU_REG_PRED_FLT10, 2, 0x3 पूर्ण,
		अणु VDPU_REG_PRED_FLT8, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT8, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT8, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT9, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT10, 0, 0x3 पूर्ण,
	पूर्ण, अणु
		अणु 0, 0, 0पूर्ण,
		अणु VDPU_REG_PRED_FLT9, 12, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT9, 2, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT10, 22, 0x3ff पूर्ण,
		अणु VDPU_REG_PRED_FLT10, 12, 0x3ff पूर्ण,
		अणु 0, 0, 0पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_start_bit = अणु
	.base = VDPU_REG_VP8_CTRL0,
	.shअगरt = 18,
	.mask = 0x3f
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_aligned_data_len = अणु
	.base = VDPU_REG_VP8_DATA_VAL,
	.shअगरt = 0,
	.mask = 0x3fffff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_num_dct_partitions = अणु
	.base = VDPU_REG_VP8_DATA_VAL,
	.shअगरt = 24,
	.mask = 0xf
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_stream_len = अणु
	.base = VDPU_REG_STREAM_LEN,
	.shअगरt = 0,
	.mask = 0xffffff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_width = अणु
	.base = VDPU_REG_VP8_PIC_MB_SIZE,
	.shअगरt = 23,
	.mask = 0x1ff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_height = अणु
	.base = VDPU_REG_VP8_PIC_MB_SIZE,
	.shअगरt = 11,
	.mask = 0xff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_width_ext = अणु
	.base = VDPU_REG_VP8_PIC_MB_SIZE,
	.shअगरt = 3,
	.mask = 0x7
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_mb_height_ext = अणु
	.base = VDPU_REG_VP8_PIC_MB_SIZE,
	.shअगरt = 0,
	.mask = 0x7
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_bool_range = अणु
	.base = VDPU_REG_VP8_CTRL0,
	.shअगरt = 0,
	.mask = 0xff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_bool_value = अणु
	.base = VDPU_REG_VP8_CTRL0,
	.shअगरt = 8,
	.mask = 0xff
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_filter_disable = अणु
	.base = VDPU_REG_DEC_CTRL0,
	.shअगरt = 8,
	.mask = 1
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_skip_mode = अणु
	.base = VDPU_REG_DEC_CTRL0,
	.shअगरt = 9,
	.mask = 1
पूर्ण;

अटल स्थिर काष्ठा hantro_reg vp8_dec_start_dec = अणु
	.base = VDPU_REG_EN_FLAGS,
	.shअगरt = 0,
	.mask = 1
पूर्ण;

अटल व्योम cfg_lf(काष्ठा hantro_ctx *ctx,
		   स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	स्थिर काष्ठा v4l2_vp8_segment *seg = &hdr->segment;
	स्थिर काष्ठा v4l2_vp8_loop_filter *lf = &hdr->lf;
	काष्ठा hantro_dev *vpu = ctx->dev;
	अचिन्हित पूर्णांक i;
	u32 reg;

	अगर (!(seg->flags & V4L2_VP8_SEGMENT_FLAG_ENABLED)) अणु
		hantro_reg_ग_लिखो(vpu, &vp8_dec_lf_level[0], lf->level);
	पूर्ण अन्यथा अगर (seg->flags & V4L2_VP8_SEGMENT_FLAG_DELTA_VALUE_MODE) अणु
		क्रम (i = 0; i < 4; i++) अणु
			u32 lf_level = clamp(lf->level + seg->lf_update[i],
					     0, 63);

			hantro_reg_ग_लिखो(vpu, &vp8_dec_lf_level[i], lf_level);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++)
			hantro_reg_ग_लिखो(vpu, &vp8_dec_lf_level[i],
					 seg->lf_update[i]);
	पूर्ण

	reg = VDPU_REG_REF_PIC_FILT_SHARPNESS(lf->sharpness_level);
	अगर (lf->flags & V4L2_VP8_LF_FILTER_TYPE_SIMPLE)
		reg |= VDPU_REG_REF_PIC_FILT_TYPE_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_FILTER_MB_ADJ);

	अगर (lf->flags & V4L2_VP8_LF_ADJ_ENABLE) अणु
		क्रम (i = 0; i < 4; i++) अणु
			hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_adj[i],
					 lf->mb_mode_delta[i]);
			hantro_reg_ग_लिखो(vpu, &vp8_dec_ref_adj[i],
					 lf->ref_frm_delta[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cfg_qp(काष्ठा hantro_ctx *ctx,
		   स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	स्थिर काष्ठा v4l2_vp8_quantization *q = &hdr->quant;
	स्थिर काष्ठा v4l2_vp8_segment *seg = &hdr->segment;
	काष्ठा hantro_dev *vpu = ctx->dev;
	अचिन्हित पूर्णांक i;

	अगर (!(seg->flags & V4L2_VP8_SEGMENT_FLAG_ENABLED)) अणु
		hantro_reg_ग_लिखो(vpu, &vp8_dec_quant[0], q->y_ac_qi);
	पूर्ण अन्यथा अगर (seg->flags & V4L2_VP8_SEGMENT_FLAG_DELTA_VALUE_MODE) अणु
		क्रम (i = 0; i < 4; i++) अणु
			u32 quant = clamp(q->y_ac_qi + seg->quant_update[i],
					  0, 127);

			hantro_reg_ग_लिखो(vpu, &vp8_dec_quant[i], quant);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++)
			hantro_reg_ग_लिखो(vpu, &vp8_dec_quant[i],
					 seg->quant_update[i]);
	पूर्ण

	hantro_reg_ग_लिखो(vpu, &vp8_dec_quant_delta[0], q->y_dc_delta);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_quant_delta[1], q->y2_dc_delta);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_quant_delta[2], q->y2_ac_delta);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_quant_delta[3], q->uv_dc_delta);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_quant_delta[4], q->uv_ac_delta);
पूर्ण

अटल व्योम cfg_parts(काष्ठा hantro_ctx *ctx,
		      स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vb2_src;
	u32 first_part_offset = V4L2_VP8_FRAME_IS_KEY_FRAME(hdr) ? 10 : 3;
	u32 mb_size, mb_offset_bytes, mb_offset_bits, mb_start_bits;
	u32 dct_size_part_size, dct_part_offset;
	dma_addr_t src_dma;
	u32 dct_part_total_len = 0;
	u32 count = 0;
	अचिन्हित पूर्णांक i;

	vb2_src = hantro_get_src_buf(ctx);
	src_dma = vb2_dma_contig_plane_dma_addr(&vb2_src->vb2_buf, 0);

	/*
	 * Calculate control partition mb data info
	 * @first_part_header_bits:	bits offset of mb data from first
	 *				part start pos
	 * @mb_offset_bits:		bits offset of mb data from src_dma
	 *				base addr
	 * @mb_offset_byte:		bytes offset of mb data from src_dma
	 *				base addr
	 * @mb_start_bits:		bits offset of mb data from mb data
	 *				64bits alignment addr
	 */
	mb_offset_bits = first_part_offset * 8 +
			 hdr->first_part_header_bits + 8;
	mb_offset_bytes = mb_offset_bits / 8;
	mb_start_bits = mb_offset_bits -
			(mb_offset_bytes & (~DEC_8190_ALIGN_MASK)) * 8;
	mb_size = hdr->first_part_size -
		  (mb_offset_bytes - first_part_offset) +
		  (mb_offset_bytes & DEC_8190_ALIGN_MASK);

	/* Macroblock data aligned base addr */
	vdpu_ग_लिखो_relaxed(vpu, (mb_offset_bytes & (~DEC_8190_ALIGN_MASK)) +
			   src_dma, VDPU_REG_VP8_ADDR_CTRL_PART);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_start_bit, mb_start_bits);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_aligned_data_len, mb_size);

	/*
	 * Calculate DCT partition info
	 * @dct_size_part_size: Containing sizes of DCT part, every DCT part
	 *			has 3 bytes to store its size, except the last
	 *			DCT part
	 * @dct_part_offset:	bytes offset of DCT parts from src_dma base addr
	 * @dct_part_total_len: total size of all DCT parts
	 */
	dct_size_part_size = (hdr->num_dct_parts - 1) * 3;
	dct_part_offset = first_part_offset + hdr->first_part_size;
	क्रम (i = 0; i < hdr->num_dct_parts; i++)
		dct_part_total_len += hdr->dct_part_sizes[i];
	dct_part_total_len += dct_size_part_size;
	dct_part_total_len += (dct_part_offset & DEC_8190_ALIGN_MASK);

	/* Number of DCT partitions */
	hantro_reg_ग_लिखो(vpu, &vp8_dec_num_dct_partitions,
			 hdr->num_dct_parts - 1);

	/* DCT partition length */
	hantro_reg_ग_लिखो(vpu, &vp8_dec_stream_len, dct_part_total_len);

	/* DCT partitions base address */
	क्रम (i = 0; i < hdr->num_dct_parts; i++) अणु
		u32 byte_offset = dct_part_offset + dct_size_part_size + count;
		u32 base_addr = byte_offset + src_dma;

		hantro_reg_ग_लिखो(vpu, &vp8_dec_dct_base[i],
				 base_addr & (~DEC_8190_ALIGN_MASK));

		hantro_reg_ग_लिखो(vpu, &vp8_dec_dct_start_bits[i],
				 (byte_offset & DEC_8190_ALIGN_MASK) * 8);

		count += hdr->dct_part_sizes[i];
	पूर्ण
पूर्ण

/*
 * prediction filter taps
 * normal 6-tap filters
 */
अटल व्योम cfg_tap(काष्ठा hantro_ctx *ctx,
		    स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	पूर्णांक i, j;

	अगर ((hdr->version & 0x03) != 0)
		वापस; /* Tap filter not used. */

	क्रम (i = 0; i < 8; i++) अणु
		क्रम (j = 0; j < 6; j++) अणु
			अगर (vp8_dec_pred_bc_tap[i][j].base != 0)
				hantro_reg_ग_लिखो(vpu,
						 &vp8_dec_pred_bc_tap[i][j],
						 hantro_vp8_dec_mc_filter[i][j]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cfg_ref(काष्ठा hantro_ctx *ctx,
		    स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vb2_dst;
	dma_addr_t ref;

	vb2_dst = hantro_get_dst_buf(ctx);

	ref = hantro_get_ref(ctx, hdr->last_frame_ts);
	अगर (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	vdpu_ग_लिखो_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF0);

	ref = hantro_get_ref(ctx, hdr->golden_frame_ts);
	WARN_ON(!ref && hdr->golden_frame_ts);
	अगर (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	अगर (hdr->flags & V4L2_VP8_FRAME_FLAG_SIGN_BIAS_GOLDEN)
		ref |= VDPU_REG_VP8_GREF_SIGN_BIAS;
	vdpu_ग_लिखो_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF2_5(2));

	ref = hantro_get_ref(ctx, hdr->alt_frame_ts);
	WARN_ON(!ref && hdr->alt_frame_ts);
	अगर (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	अगर (hdr->flags & V4L2_VP8_FRAME_FLAG_SIGN_BIAS_ALT)
		ref |= VDPU_REG_VP8_AREF_SIGN_BIAS;
	vdpu_ग_लिखो_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF2_5(3));
पूर्ण

अटल व्योम cfg_buffers(काष्ठा hantro_ctx *ctx,
			स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr)
अणु
	स्थिर काष्ठा v4l2_vp8_segment *seg = &hdr->segment;
	काष्ठा hantro_dev *vpu = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vb2_dst;
	dma_addr_t dst_dma;
	u32 reg;

	vb2_dst = hantro_get_dst_buf(ctx);

	/* Set probability table buffer address */
	vdpu_ग_लिखो_relaxed(vpu, ctx->vp8_dec.prob_tbl.dma,
			   VDPU_REG_ADDR_QTABLE);

	/* Set segment map address */
	reg = VDPU_REG_FWD_PIC1_SEGMENT_BASE(ctx->vp8_dec.segment_map.dma);
	अगर (seg->flags & V4L2_VP8_SEGMENT_FLAG_ENABLED) अणु
		reg |= VDPU_REG_FWD_PIC1_SEGMENT_E;
		अगर (seg->flags & V4L2_VP8_SEGMENT_FLAG_UPDATE_MAP)
			reg |= VDPU_REG_FWD_PIC1_SEGMENT_UPD_E;
	पूर्ण
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_VP8_SEGMENT_VAL);

	/* set output frame buffer address */
	dst_dma = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	vdpu_ग_लिखो_relaxed(vpu, dst_dma, VDPU_REG_ADDR_DST);
पूर्ण

व्योम rk3399_vpu_vp8_dec_run(काष्ठा hantro_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_ctrl_vp8_frame *hdr;
	काष्ठा hantro_dev *vpu = ctx->dev;
	माप_प्रकार height = ctx->dst_fmt.height;
	माप_प्रकार width = ctx->dst_fmt.width;
	u32 mb_width, mb_height;
	u32 reg;

	hantro_start_prepare_run(ctx);

	hdr = hantro_get_ctrl(ctx, V4L2_CID_STATELESS_VP8_FRAME);
	अगर (WARN_ON(!hdr))
		वापस;

	/* Reset segment_map buffer in keyframe */
	अगर (V4L2_VP8_FRAME_IS_KEY_FRAME(hdr) && ctx->vp8_dec.segment_map.cpu)
		स_रखो(ctx->vp8_dec.segment_map.cpu, 0,
		       ctx->vp8_dec.segment_map.size);

	hantro_vp8_prob_update(ctx, hdr);

	/*
	 * Extensive testing shows that the hardware करोes not properly
	 * clear the पूर्णांकernal state from previous a decoding run. This
	 * causes corruption in decoded frames क्रम multi-instance use हालs.
	 * A soft reset beक्रमe programming the रेजिस्टरs has been found
	 * to resolve those problems.
	 */
	ctx->codec_ops->reset(ctx);

	reg = VDPU_REG_CONFIG_DEC_TIMEOUT_E
		| VDPU_REG_CONFIG_DEC_CLK_GATE_E;
	अगर (!V4L2_VP8_FRAME_IS_KEY_FRAME(hdr))
		reg |= VDPU_REG_DEC_CTRL0_PIC_INTER_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_EN_FLAGS);

	reg = VDPU_REG_CONFIG_DEC_STRENDIAN_E
		| VDPU_REG_CONFIG_DEC_INSWAP32_E
		| VDPU_REG_CONFIG_DEC_STRSWAP32_E
		| VDPU_REG_CONFIG_DEC_OUTSWAP32_E
		| VDPU_REG_CONFIG_DEC_IN_ENDIAN
		| VDPU_REG_CONFIG_DEC_OUT_ENDIAN;
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_DATA_ENDIAN);

	reg = VDPU_REG_CONFIG_DEC_MAX_BURST(16);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_AXI_CTRL);

	reg = VDPU_REG_DEC_CTRL0_DEC_MODE(10);
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_DEC_FORMAT);

	अगर (!(hdr->flags & V4L2_VP8_FRAME_FLAG_MB_NO_SKIP_COEFF))
		hantro_reg_ग_लिखो(vpu, &vp8_dec_skip_mode, 1);
	अगर (hdr->lf.level == 0)
		hantro_reg_ग_लिखो(vpu, &vp8_dec_filter_disable, 1);

	/* Frame dimensions */
	mb_width = MB_WIDTH(width);
	mb_height = MB_HEIGHT(height);

	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_width, mb_width);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_height, mb_height);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_width_ext, mb_width >> 9);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_mb_height_ext, mb_height >> 8);

	/* Boolean decoder */
	hantro_reg_ग_लिखो(vpu, &vp8_dec_bool_range, hdr->coder_state.range);
	hantro_reg_ग_लिखो(vpu, &vp8_dec_bool_value, hdr->coder_state.value);

	reg = vdpu_पढ़ो(vpu, VDPU_REG_VP8_DCT_START_BIT);
	अगर (hdr->version != 3)
		reg |= VDPU_REG_DEC_CTRL4_VC1_HEIGHT_EXT;
	अगर (hdr->version & 0x3)
		reg |= VDPU_REG_DEC_CTRL4_BILIN_MC_E;
	vdpu_ग_लिखो_relaxed(vpu, reg, VDPU_REG_VP8_DCT_START_BIT);

	cfg_lf(ctx, hdr);
	cfg_qp(ctx, hdr);
	cfg_parts(ctx, hdr);
	cfg_tap(ctx, hdr);
	cfg_ref(ctx, hdr);
	cfg_buffers(ctx, hdr);

	hantro_end_prepare_run(ctx);

	hantro_reg_ग_लिखो(vpu, &vp8_dec_start_dec, 1);
पूर्ण
