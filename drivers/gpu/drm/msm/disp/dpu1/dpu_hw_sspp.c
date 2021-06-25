<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_sspp.h"
#समावेश "dpu_kms.h"

#घोषणा DPU_FETCH_CONFIG_RESET_VALUE   0x00000087

/* DPU_SSPP_SRC */
#घोषणा SSPP_SRC_SIZE                      0x00
#घोषणा SSPP_SRC_XY                        0x08
#घोषणा SSPP_OUT_SIZE                      0x0c
#घोषणा SSPP_OUT_XY                        0x10
#घोषणा SSPP_SRC0_ADDR                     0x14
#घोषणा SSPP_SRC1_ADDR                     0x18
#घोषणा SSPP_SRC2_ADDR                     0x1C
#घोषणा SSPP_SRC3_ADDR                     0x20
#घोषणा SSPP_SRC_YSTRIDE0                  0x24
#घोषणा SSPP_SRC_YSTRIDE1                  0x28
#घोषणा SSPP_SRC_FORMAT                    0x30
#घोषणा SSPP_SRC_UNPACK_PATTERN            0x34
#घोषणा SSPP_SRC_OP_MODE                   0x38

/* SSPP_MULTIRECT*/
#घोषणा SSPP_SRC_SIZE_REC1                 0x16C
#घोषणा SSPP_SRC_XY_REC1                   0x168
#घोषणा SSPP_OUT_SIZE_REC1                 0x160
#घोषणा SSPP_OUT_XY_REC1                   0x164
#घोषणा SSPP_SRC_FORMAT_REC1               0x174
#घोषणा SSPP_SRC_UNPACK_PATTERN_REC1       0x178
#घोषणा SSPP_SRC_OP_MODE_REC1              0x17C
#घोषणा SSPP_MULTIRECT_OPMODE              0x170
#घोषणा SSPP_SRC_CONSTANT_COLOR_REC1       0x180
#घोषणा SSPP_EXCL_REC_SIZE_REC1            0x184
#घोषणा SSPP_EXCL_REC_XY_REC1              0x188

#घोषणा MDSS_MDP_OP_DEINTERLACE            BIT(22)
#घोषणा MDSS_MDP_OP_DEINTERLACE_ODD        BIT(23)
#घोषणा MDSS_MDP_OP_IGC_ROM_1              BIT(18)
#घोषणा MDSS_MDP_OP_IGC_ROM_0              BIT(17)
#घोषणा MDSS_MDP_OP_IGC_EN                 BIT(16)
#घोषणा MDSS_MDP_OP_FLIP_UD                BIT(14)
#घोषणा MDSS_MDP_OP_FLIP_LR                BIT(13)
#घोषणा MDSS_MDP_OP_BWC_EN                 BIT(0)
#घोषणा MDSS_MDP_OP_PE_OVERRIDE            BIT(31)
#घोषणा MDSS_MDP_OP_BWC_LOSSLESS           (0 << 1)
#घोषणा MDSS_MDP_OP_BWC_Q_HIGH             (1 << 1)
#घोषणा MDSS_MDP_OP_BWC_Q_MED              (2 << 1)

#घोषणा SSPP_SRC_CONSTANT_COLOR            0x3c
#घोषणा SSPP_EXCL_REC_CTL                  0x40
#घोषणा SSPP_UBWC_STATIC_CTRL              0x44
#घोषणा SSPP_FETCH_CONFIG                  0x048
#घोषणा SSPP_DANGER_LUT                    0x60
#घोषणा SSPP_SAFE_LUT                      0x64
#घोषणा SSPP_CREQ_LUT                      0x68
#घोषणा SSPP_QOS_CTRL                      0x6C
#घोषणा SSPP_DECIMATION_CONFIG             0xB4
#घोषणा SSPP_SRC_ADDR_SW_STATUS            0x70
#घोषणा SSPP_CREQ_LUT_0                    0x74
#घोषणा SSPP_CREQ_LUT_1                    0x78
#घोषणा SSPP_SW_PIX_EXT_C0_LR              0x100
#घोषणा SSPP_SW_PIX_EXT_C0_TB              0x104
#घोषणा SSPP_SW_PIX_EXT_C0_REQ_PIXELS      0x108
#घोषणा SSPP_SW_PIX_EXT_C1C2_LR            0x110
#घोषणा SSPP_SW_PIX_EXT_C1C2_TB            0x114
#घोषणा SSPP_SW_PIX_EXT_C1C2_REQ_PIXELS    0x118
#घोषणा SSPP_SW_PIX_EXT_C3_LR              0x120
#घोषणा SSPP_SW_PIX_EXT_C3_TB              0x124
#घोषणा SSPP_SW_PIX_EXT_C3_REQ_PIXELS      0x128
#घोषणा SSPP_TRAFFIC_SHAPER                0x130
#घोषणा SSPP_CDP_CNTL                      0x134
#घोषणा SSPP_UBWC_ERROR_STATUS             0x138
#घोषणा SSPP_TRAFFIC_SHAPER_PREFILL        0x150
#घोषणा SSPP_TRAFFIC_SHAPER_REC1_PREFILL   0x154
#घोषणा SSPP_TRAFFIC_SHAPER_REC1           0x158
#घोषणा SSPP_EXCL_REC_SIZE                 0x1B4
#घोषणा SSPP_EXCL_REC_XY                   0x1B8
#घोषणा SSPP_VIG_OP_MODE                   0x0
#घोषणा SSPP_VIG_CSC_10_OP_MODE            0x0
#घोषणा SSPP_TRAFFIC_SHAPER_BPC_MAX        0xFF

/* SSPP_QOS_CTRL */
#घोषणा SSPP_QOS_CTRL_VBLANK_EN            BIT(16)
#घोषणा SSPP_QOS_CTRL_DANGER_SAFE_EN       BIT(0)
#घोषणा SSPP_QOS_CTRL_DANGER_VBLANK_MASK   0x3
#घोषणा SSPP_QOS_CTRL_DANGER_VBLANK_OFF    4
#घोषणा SSPP_QOS_CTRL_CREQ_VBLANK_MASK     0x3
#घोषणा SSPP_QOS_CTRL_CREQ_VBLANK_OFF      20

/* DPU_SSPP_SCALER_QSEED2 */
#घोषणा SCALE_CONFIG                       0x04
#घोषणा COMP0_3_PHASE_STEP_X               0x10
#घोषणा COMP0_3_PHASE_STEP_Y               0x14
#घोषणा COMP1_2_PHASE_STEP_X               0x18
#घोषणा COMP1_2_PHASE_STEP_Y               0x1c
#घोषणा COMP0_3_INIT_PHASE_X               0x20
#घोषणा COMP0_3_INIT_PHASE_Y               0x24
#घोषणा COMP1_2_INIT_PHASE_X               0x28
#घोषणा COMP1_2_INIT_PHASE_Y               0x2C
#घोषणा VIG_0_QSEED2_SHARP                 0x30

/*
 * Definitions क्रम ViG op modes
 */
#घोषणा VIG_OP_CSC_DST_DATAFMT BIT(19)
#घोषणा VIG_OP_CSC_SRC_DATAFMT BIT(18)
#घोषणा VIG_OP_CSC_EN          BIT(17)
#घोषणा VIG_OP_MEM_PROT_CONT   BIT(15)
#घोषणा VIG_OP_MEM_PROT_VAL    BIT(14)
#घोषणा VIG_OP_MEM_PROT_SAT    BIT(13)
#घोषणा VIG_OP_MEM_PROT_HUE    BIT(12)
#घोषणा VIG_OP_HIST            BIT(8)
#घोषणा VIG_OP_SKY_COL         BIT(7)
#घोषणा VIG_OP_FOIL            BIT(6)
#घोषणा VIG_OP_SKIN_COL        BIT(5)
#घोषणा VIG_OP_PA_EN           BIT(4)
#घोषणा VIG_OP_PA_SAT_ZERO_EXP BIT(2)
#घोषणा VIG_OP_MEM_PROT_BLEND  BIT(1)

/*
 * Definitions क्रम CSC 10 op modes
 */
#घोषणा VIG_CSC_10_SRC_DATAFMT BIT(1)
#घोषणा VIG_CSC_10_EN          BIT(0)
#घोषणा CSC_10BIT_OFFSET       4

/* traffic shaper घड़ी in Hz */
#घोषणा TS_CLK			19200000


अटल पूर्णांक _sspp_subblk_offset(काष्ठा dpu_hw_pipe *ctx,
		पूर्णांक s_id,
		u32 *idx)
अणु
	पूर्णांक rc = 0;
	स्थिर काष्ठा dpu_sspp_sub_blks *sblk = ctx->cap->sblk;

	अगर (!ctx)
		वापस -EINVAL;

	चयन (s_id) अणु
	हाल DPU_SSPP_SRC:
		*idx = sblk->src_blk.base;
		अवरोध;
	हाल DPU_SSPP_SCALER_QSEED2:
	हाल DPU_SSPP_SCALER_QSEED3:
	हाल DPU_SSPP_SCALER_RGB:
		*idx = sblk->scaler_blk.base;
		अवरोध;
	हाल DPU_SSPP_CSC:
	हाल DPU_SSPP_CSC_10BIT:
		*idx = sblk->csc_blk.base;
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम dpu_hw_sspp_setup_multirect(काष्ठा dpu_hw_pipe *ctx,
		क्रमागत dpu_sspp_multirect_index index,
		क्रमागत dpu_sspp_multirect_mode mode)
अणु
	u32 mode_mask;
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (index == DPU_SSPP_RECT_SOLO) अणु
		/**
		 * अगर rect index is RECT_SOLO, we cannot expect a
		 * भव plane sharing the same SSPP id. So we go
		 * and disable multirect
		 */
		mode_mask = 0;
	पूर्ण अन्यथा अणु
		mode_mask = DPU_REG_READ(&ctx->hw, SSPP_MULTIRECT_OPMODE + idx);
		mode_mask |= index;
		अगर (mode == DPU_SSPP_MULTIRECT_TIME_MX)
			mode_mask |= BIT(2);
		अन्यथा
			mode_mask &= ~BIT(2);
	पूर्ण

	DPU_REG_WRITE(&ctx->hw, SSPP_MULTIRECT_OPMODE + idx, mode_mask);
पूर्ण

अटल व्योम _sspp_setup_opmode(काष्ठा dpu_hw_pipe *ctx,
		u32 mask, u8 en)
अणु
	u32 idx;
	u32 opmode;

	अगर (!test_bit(DPU_SSPP_SCALER_QSEED2, &ctx->cap->features) ||
		_sspp_subblk_offset(ctx, DPU_SSPP_SCALER_QSEED2, &idx) ||
		!test_bit(DPU_SSPP_CSC, &ctx->cap->features))
		वापस;

	opmode = DPU_REG_READ(&ctx->hw, SSPP_VIG_OP_MODE + idx);

	अगर (en)
		opmode |= mask;
	अन्यथा
		opmode &= ~mask;

	DPU_REG_WRITE(&ctx->hw, SSPP_VIG_OP_MODE + idx, opmode);
पूर्ण

अटल व्योम _sspp_setup_csc10_opmode(काष्ठा dpu_hw_pipe *ctx,
		u32 mask, u8 en)
अणु
	u32 idx;
	u32 opmode;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_CSC_10BIT, &idx))
		वापस;

	opmode = DPU_REG_READ(&ctx->hw, SSPP_VIG_CSC_10_OP_MODE + idx);
	अगर (en)
		opmode |= mask;
	अन्यथा
		opmode &= ~mask;

	DPU_REG_WRITE(&ctx->hw, SSPP_VIG_CSC_10_OP_MODE + idx, opmode);
पूर्ण

/*
 * Setup source pixel क्रमmat, flip,
 */
अटल व्योम dpu_hw_sspp_setup_क्रमmat(काष्ठा dpu_hw_pipe *ctx,
		स्थिर काष्ठा dpu_क्रमmat *fmt, u32 flags,
		क्रमागत dpu_sspp_multirect_index rect_mode)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 chroma_samp, unpack, src_क्रमmat;
	u32 opmode = 0;
	u32 fast_clear = 0;
	u32 op_mode_off, unpack_pat_off, क्रमmat_off;
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx) || !fmt)
		वापस;

	अगर (rect_mode == DPU_SSPP_RECT_SOLO || rect_mode == DPU_SSPP_RECT_0) अणु
		op_mode_off = SSPP_SRC_OP_MODE;
		unpack_pat_off = SSPP_SRC_UNPACK_PATTERN;
		क्रमmat_off = SSPP_SRC_FORMAT;
	पूर्ण अन्यथा अणु
		op_mode_off = SSPP_SRC_OP_MODE_REC1;
		unpack_pat_off = SSPP_SRC_UNPACK_PATTERN_REC1;
		क्रमmat_off = SSPP_SRC_FORMAT_REC1;
	पूर्ण

	c = &ctx->hw;
	opmode = DPU_REG_READ(c, op_mode_off + idx);
	opmode &= ~(MDSS_MDP_OP_FLIP_LR | MDSS_MDP_OP_FLIP_UD |
			MDSS_MDP_OP_BWC_EN | MDSS_MDP_OP_PE_OVERRIDE);

	अगर (flags & DPU_SSPP_FLIP_LR)
		opmode |= MDSS_MDP_OP_FLIP_LR;
	अगर (flags & DPU_SSPP_FLIP_UD)
		opmode |= MDSS_MDP_OP_FLIP_UD;

	chroma_samp = fmt->chroma_sample;
	अगर (flags & DPU_SSPP_SOURCE_ROTATED_90) अणु
		अगर (chroma_samp == DPU_CHROMA_H2V1)
			chroma_samp = DPU_CHROMA_H1V2;
		अन्यथा अगर (chroma_samp == DPU_CHROMA_H1V2)
			chroma_samp = DPU_CHROMA_H2V1;
	पूर्ण

	src_क्रमmat = (chroma_samp << 23) | (fmt->fetch_planes << 19) |
		(fmt->bits[C3_ALPHA] << 6) | (fmt->bits[C2_R_Cr] << 4) |
		(fmt->bits[C1_B_Cb] << 2) | (fmt->bits[C0_G_Y] << 0);

	अगर (flags & DPU_SSPP_ROT_90)
		src_क्रमmat |= BIT(11); /* ROT90 */

	अगर (fmt->alpha_enable && fmt->fetch_planes == DPU_PLANE_INTERLEAVED)
		src_क्रमmat |= BIT(8); /* SRCC3_EN */

	अगर (flags & DPU_SSPP_SOLID_FILL)
		src_क्रमmat |= BIT(22);

	unpack = (fmt->element[3] << 24) | (fmt->element[2] << 16) |
		(fmt->element[1] << 8) | (fmt->element[0] << 0);
	src_क्रमmat |= ((fmt->unpack_count - 1) << 12) |
		(fmt->unpack_tight << 17) |
		(fmt->unpack_align_msb << 18) |
		((fmt->bpp - 1) << 9);

	अगर (fmt->fetch_mode != DPU_FETCH_LINEAR) अणु
		अगर (DPU_FORMAT_IS_UBWC(fmt))
			opmode |= MDSS_MDP_OP_BWC_EN;
		src_क्रमmat |= (fmt->fetch_mode & 3) << 30; /*FRAME_FORMAT */
		DPU_REG_WRITE(c, SSPP_FETCH_CONFIG,
			DPU_FETCH_CONFIG_RESET_VALUE |
			ctx->mdp->highest_bank_bit << 18);
		चयन (ctx->catalog->caps->ubwc_version) अणु
		हाल DPU_HW_UBWC_VER_10:
			/* TODO: UBWC v1 हाल */
			अवरोध;
		हाल DPU_HW_UBWC_VER_20:
			fast_clear = fmt->alpha_enable ? BIT(31) : 0;
			DPU_REG_WRITE(c, SSPP_UBWC_STATIC_CTRL,
					fast_clear | (ctx->mdp->ubwc_swizzle) |
					(ctx->mdp->highest_bank_bit << 4));
			अवरोध;
		हाल DPU_HW_UBWC_VER_30:
			DPU_REG_WRITE(c, SSPP_UBWC_STATIC_CTRL,
					BIT(30) | (ctx->mdp->ubwc_swizzle) |
					(ctx->mdp->highest_bank_bit << 4));
			अवरोध;
		हाल DPU_HW_UBWC_VER_40:
			DPU_REG_WRITE(c, SSPP_UBWC_STATIC_CTRL,
					DPU_FORMAT_IS_YUV(fmt) ? 0 : BIT(30));
			अवरोध;
		पूर्ण
	पूर्ण

	opmode |= MDSS_MDP_OP_PE_OVERRIDE;

	/* अगर this is YUV pixel क्रमmat, enable CSC */
	अगर (DPU_FORMAT_IS_YUV(fmt))
		src_क्रमmat |= BIT(15);

	अगर (DPU_FORMAT_IS_DX(fmt))
		src_क्रमmat |= BIT(14);

	/* update scaler opmode, अगर appropriate */
	अगर (test_bit(DPU_SSPP_CSC, &ctx->cap->features))
		_sspp_setup_opmode(ctx, VIG_OP_CSC_EN | VIG_OP_CSC_SRC_DATAFMT,
			DPU_FORMAT_IS_YUV(fmt));
	अन्यथा अगर (test_bit(DPU_SSPP_CSC_10BIT, &ctx->cap->features))
		_sspp_setup_csc10_opmode(ctx,
			VIG_CSC_10_EN | VIG_CSC_10_SRC_DATAFMT,
			DPU_FORMAT_IS_YUV(fmt));

	DPU_REG_WRITE(c, क्रमmat_off + idx, src_क्रमmat);
	DPU_REG_WRITE(c, unpack_pat_off + idx, unpack);
	DPU_REG_WRITE(c, op_mode_off + idx, opmode);

	/* clear previous UBWC error */
	DPU_REG_WRITE(c, SSPP_UBWC_ERROR_STATUS + idx, BIT(31));
पूर्ण

अटल व्योम dpu_hw_sspp_setup_pe_config(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pixel_ext *pe_ext)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u8 color;
	u32 lr_pe[4], tb_pe[4], tot_req_pixels[4];
	स्थिर u32 bytemask = 0xff;
	स्थिर u32 लघुmask = 0xffff;
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx) || !pe_ext)
		वापस;

	c = &ctx->hw;

	/* program SW pixel extension override क्रम all pipes*/
	क्रम (color = 0; color < DPU_MAX_PLANES; color++) अणु
		/* color 2 has the same set of रेजिस्टरs as color 1 */
		अगर (color == 2)
			जारी;

		lr_pe[color] = ((pe_ext->right_ftch[color] & bytemask) << 24)|
			((pe_ext->right_rpt[color] & bytemask) << 16)|
			((pe_ext->left_ftch[color] & bytemask) << 8)|
			(pe_ext->left_rpt[color] & bytemask);

		tb_pe[color] = ((pe_ext->bपंचांग_ftch[color] & bytemask) << 24)|
			((pe_ext->bपंचांग_rpt[color] & bytemask) << 16)|
			((pe_ext->top_ftch[color] & bytemask) << 8)|
			(pe_ext->top_rpt[color] & bytemask);

		tot_req_pixels[color] = (((pe_ext->roi_h[color] +
			pe_ext->num_ext_pxls_top[color] +
			pe_ext->num_ext_pxls_bपंचांग[color]) & लघुmask) << 16) |
			((pe_ext->roi_w[color] +
			pe_ext->num_ext_pxls_left[color] +
			pe_ext->num_ext_pxls_right[color]) & लघुmask);
	पूर्ण

	/* color 0 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_LR + idx, lr_pe[0]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_TB + idx, tb_pe[0]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_REQ_PIXELS + idx,
			tot_req_pixels[0]);

	/* color 1 and color 2 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_LR + idx, lr_pe[1]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_TB + idx, tb_pe[1]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_REQ_PIXELS + idx,
			tot_req_pixels[1]);

	/* color 3 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_LR + idx, lr_pe[3]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_TB + idx, lr_pe[3]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_REQ_PIXELS + idx,
			tot_req_pixels[3]);
पूर्ण

अटल व्योम _dpu_hw_sspp_setup_scaler3(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_cfg *sspp,
		काष्ठा dpu_hw_pixel_ext *pe,
		व्योम *scaler_cfg)
अणु
	u32 idx;
	काष्ठा dpu_hw_scaler3_cfg *scaler3_cfg = scaler_cfg;

	(व्योम)pe;
	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SCALER_QSEED3, &idx) || !sspp
		|| !scaler3_cfg || !ctx || !ctx->cap || !ctx->cap->sblk)
		वापस;

	dpu_hw_setup_scaler3(&ctx->hw, scaler3_cfg, idx,
			ctx->cap->sblk->scaler_blk.version,
			sspp->layout.क्रमmat);
पूर्ण

अटल u32 _dpu_hw_sspp_get_scaler3_ver(काष्ठा dpu_hw_pipe *ctx)
अणु
	u32 idx;

	अगर (!ctx || _sspp_subblk_offset(ctx, DPU_SSPP_SCALER_QSEED3, &idx))
		वापस 0;

	वापस dpu_hw_get_scaler3_ver(&ctx->hw, idx);
पूर्ण

/*
 * dpu_hw_sspp_setup_rects()
 */
अटल व्योम dpu_hw_sspp_setup_rects(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_cfg *cfg,
		क्रमागत dpu_sspp_multirect_index rect_index)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 src_size, src_xy, dst_size, dst_xy, ystride0, ystride1;
	u32 src_size_off, src_xy_off, out_size_off, out_xy_off;
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx) || !cfg)
		वापस;

	c = &ctx->hw;

	अगर (rect_index == DPU_SSPP_RECT_SOLO || rect_index == DPU_SSPP_RECT_0) अणु
		src_size_off = SSPP_SRC_SIZE;
		src_xy_off = SSPP_SRC_XY;
		out_size_off = SSPP_OUT_SIZE;
		out_xy_off = SSPP_OUT_XY;
	पूर्ण अन्यथा अणु
		src_size_off = SSPP_SRC_SIZE_REC1;
		src_xy_off = SSPP_SRC_XY_REC1;
		out_size_off = SSPP_OUT_SIZE_REC1;
		out_xy_off = SSPP_OUT_XY_REC1;
	पूर्ण


	/* src and dest rect programming */
	src_xy = (cfg->src_rect.y1 << 16) | cfg->src_rect.x1;
	src_size = (drm_rect_height(&cfg->src_rect) << 16) |
		   drm_rect_width(&cfg->src_rect);
	dst_xy = (cfg->dst_rect.y1 << 16) | cfg->dst_rect.x1;
	dst_size = (drm_rect_height(&cfg->dst_rect) << 16) |
		drm_rect_width(&cfg->dst_rect);

	अगर (rect_index == DPU_SSPP_RECT_SOLO) अणु
		ystride0 = (cfg->layout.plane_pitch[0]) |
			(cfg->layout.plane_pitch[1] << 16);
		ystride1 = (cfg->layout.plane_pitch[2]) |
			(cfg->layout.plane_pitch[3] << 16);
	पूर्ण अन्यथा अणु
		ystride0 = DPU_REG_READ(c, SSPP_SRC_YSTRIDE0 + idx);
		ystride1 = DPU_REG_READ(c, SSPP_SRC_YSTRIDE1 + idx);

		अगर (rect_index == DPU_SSPP_RECT_0) अणु
			ystride0 = (ystride0 & 0xFFFF0000) |
				(cfg->layout.plane_pitch[0] & 0x0000FFFF);
			ystride1 = (ystride1 & 0xFFFF0000)|
				(cfg->layout.plane_pitch[2] & 0x0000FFFF);
		पूर्ण अन्यथा अणु
			ystride0 = (ystride0 & 0x0000FFFF) |
				((cfg->layout.plane_pitch[0] << 16) &
				 0xFFFF0000);
			ystride1 = (ystride1 & 0x0000FFFF) |
				((cfg->layout.plane_pitch[2] << 16) &
				 0xFFFF0000);
		पूर्ण
	पूर्ण

	/* rectangle रेजिस्टर programming */
	DPU_REG_WRITE(c, src_size_off + idx, src_size);
	DPU_REG_WRITE(c, src_xy_off + idx, src_xy);
	DPU_REG_WRITE(c, out_size_off + idx, dst_size);
	DPU_REG_WRITE(c, out_xy_off + idx, dst_xy);

	DPU_REG_WRITE(c, SSPP_SRC_YSTRIDE0 + idx, ystride0);
	DPU_REG_WRITE(c, SSPP_SRC_YSTRIDE1 + idx, ystride1);
पूर्ण

अटल व्योम dpu_hw_sspp_setup_sourceaddress(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_cfg *cfg,
		क्रमागत dpu_sspp_multirect_index rect_mode)
अणु
	पूर्णांक i;
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (rect_mode == DPU_SSPP_RECT_SOLO) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cfg->layout.plane_addr); i++)
			DPU_REG_WRITE(&ctx->hw, SSPP_SRC0_ADDR + idx + i * 0x4,
					cfg->layout.plane_addr[i]);
	पूर्ण अन्यथा अगर (rect_mode == DPU_SSPP_RECT_0) अणु
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC0_ADDR + idx,
				cfg->layout.plane_addr[0]);
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC2_ADDR + idx,
				cfg->layout.plane_addr[2]);
	पूर्ण अन्यथा अणु
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC1_ADDR + idx,
				cfg->layout.plane_addr[0]);
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC3_ADDR + idx,
				cfg->layout.plane_addr[2]);
	पूर्ण
पूर्ण

अटल व्योम dpu_hw_sspp_setup_csc(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_csc_cfg *data)
अणु
	u32 idx;
	bool csc10 = false;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_CSC, &idx) || !data)
		वापस;

	अगर (test_bit(DPU_SSPP_CSC_10BIT, &ctx->cap->features)) अणु
		idx += CSC_10BIT_OFFSET;
		csc10 = true;
	पूर्ण

	dpu_hw_csc_setup(&ctx->hw, idx, data, csc10);
पूर्ण

अटल व्योम dpu_hw_sspp_setup_solidfill(काष्ठा dpu_hw_pipe *ctx, u32 color, क्रमागत
		dpu_sspp_multirect_index rect_index)
अणु
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (rect_index == DPU_SSPP_RECT_SOLO || rect_index == DPU_SSPP_RECT_0)
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC_CONSTANT_COLOR + idx, color);
	अन्यथा
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC_CONSTANT_COLOR_REC1 + idx,
				color);
पूर्ण

अटल व्योम dpu_hw_sspp_setup_danger_safe_lut(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_qos_cfg *cfg)
अणु
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	DPU_REG_WRITE(&ctx->hw, SSPP_DANGER_LUT + idx, cfg->danger_lut);
	DPU_REG_WRITE(&ctx->hw, SSPP_SAFE_LUT + idx, cfg->safe_lut);
पूर्ण

अटल व्योम dpu_hw_sspp_setup_creq_lut(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_qos_cfg *cfg)
अणु
	u32 idx;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (ctx->cap && test_bit(DPU_SSPP_QOS_8LVL, &ctx->cap->features)) अणु
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT_0 + idx, cfg->creq_lut);
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT_1 + idx,
				cfg->creq_lut >> 32);
	पूर्ण अन्यथा अणु
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT + idx, cfg->creq_lut);
	पूर्ण
पूर्ण

अटल व्योम dpu_hw_sspp_setup_qos_ctrl(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_qos_cfg *cfg)
अणु
	u32 idx;
	u32 qos_ctrl = 0;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (cfg->vblank_en) अणु
		qos_ctrl |= ((cfg->creq_vblank &
				SSPP_QOS_CTRL_CREQ_VBLANK_MASK) <<
				SSPP_QOS_CTRL_CREQ_VBLANK_OFF);
		qos_ctrl |= ((cfg->danger_vblank &
				SSPP_QOS_CTRL_DANGER_VBLANK_MASK) <<
				SSPP_QOS_CTRL_DANGER_VBLANK_OFF);
		qos_ctrl |= SSPP_QOS_CTRL_VBLANK_EN;
	पूर्ण

	अगर (cfg->danger_safe_en)
		qos_ctrl |= SSPP_QOS_CTRL_DANGER_SAFE_EN;

	DPU_REG_WRITE(&ctx->hw, SSPP_QOS_CTRL + idx, qos_ctrl);
पूर्ण

अटल व्योम dpu_hw_sspp_setup_cdp(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_cdp_cfg *cfg)
अणु
	u32 idx;
	u32 cdp_cntl = 0;

	अगर (!ctx || !cfg)
		वापस;

	अगर (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		वापस;

	अगर (cfg->enable)
		cdp_cntl |= BIT(0);
	अगर (cfg->ubwc_meta_enable)
		cdp_cntl |= BIT(1);
	अगर (cfg->tile_amortize_enable)
		cdp_cntl |= BIT(2);
	अगर (cfg->preload_ahead == DPU_SSPP_CDP_PRELOAD_AHEAD_64)
		cdp_cntl |= BIT(3);

	DPU_REG_WRITE(&ctx->hw, SSPP_CDP_CNTL, cdp_cntl);
पूर्ण

अटल व्योम _setup_layer_ops(काष्ठा dpu_hw_pipe *c,
		अचिन्हित दीर्घ features)
अणु
	अगर (test_bit(DPU_SSPP_SRC, &features)) अणु
		c->ops.setup_क्रमmat = dpu_hw_sspp_setup_क्रमmat;
		c->ops.setup_rects = dpu_hw_sspp_setup_rects;
		c->ops.setup_sourceaddress = dpu_hw_sspp_setup_sourceaddress;
		c->ops.setup_solidfill = dpu_hw_sspp_setup_solidfill;
		c->ops.setup_pe = dpu_hw_sspp_setup_pe_config;
	पूर्ण

	अगर (test_bit(DPU_SSPP_QOS, &features)) अणु
		c->ops.setup_danger_safe_lut =
			dpu_hw_sspp_setup_danger_safe_lut;
		c->ops.setup_creq_lut = dpu_hw_sspp_setup_creq_lut;
		c->ops.setup_qos_ctrl = dpu_hw_sspp_setup_qos_ctrl;
	पूर्ण

	अगर (test_bit(DPU_SSPP_CSC, &features) ||
		test_bit(DPU_SSPP_CSC_10BIT, &features))
		c->ops.setup_csc = dpu_hw_sspp_setup_csc;

	अगर (test_bit(DPU_SSPP_SMART_DMA_V1, &c->cap->features) ||
		test_bit(DPU_SSPP_SMART_DMA_V2, &c->cap->features))
		c->ops.setup_multirect = dpu_hw_sspp_setup_multirect;

	अगर (test_bit(DPU_SSPP_SCALER_QSEED3, &features) ||
			test_bit(DPU_SSPP_SCALER_QSEED3LITE, &features) ||
			test_bit(DPU_SSPP_SCALER_QSEED4, &features)) अणु
		c->ops.setup_scaler = _dpu_hw_sspp_setup_scaler3;
		c->ops.get_scaler_ver = _dpu_hw_sspp_get_scaler3_ver;
	पूर्ण

	अगर (test_bit(DPU_SSPP_CDP, &features))
		c->ops.setup_cdp = dpu_hw_sspp_setup_cdp;
पूर्ण

अटल स्थिर काष्ठा dpu_sspp_cfg *_sspp_offset(क्रमागत dpu_sspp sspp,
		व्योम __iomem *addr,
		काष्ठा dpu_mdss_cfg *catalog,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	अगर ((sspp < SSPP_MAX) && catalog && addr && b) अणु
		क्रम (i = 0; i < catalog->sspp_count; i++) अणु
			अगर (sspp == catalog->sspp[i].id) अणु
				b->base_off = addr;
				b->blk_off = catalog->sspp[i].base;
				b->length = catalog->sspp[i].len;
				b->hwversion = catalog->hwversion;
				b->log_mask = DPU_DBG_MASK_SSPP;
				वापस &catalog->sspp[i];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_pipe *dpu_hw_sspp_init(क्रमागत dpu_sspp idx,
		व्योम __iomem *addr, काष्ठा dpu_mdss_cfg *catalog,
		bool is_भव_pipe)
अणु
	काष्ठा dpu_hw_pipe *hw_pipe;
	स्थिर काष्ठा dpu_sspp_cfg *cfg;

	अगर (!addr || !catalog)
		वापस ERR_PTR(-EINVAL);

	hw_pipe = kzalloc(माप(*hw_pipe), GFP_KERNEL);
	अगर (!hw_pipe)
		वापस ERR_PTR(-ENOMEM);

	cfg = _sspp_offset(idx, addr, catalog, &hw_pipe->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(hw_pipe);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Assign ops */
	hw_pipe->catalog = catalog;
	hw_pipe->mdp = &catalog->mdp[0];
	hw_pipe->idx = idx;
	hw_pipe->cap = cfg;
	_setup_layer_ops(hw_pipe, hw_pipe->cap->features);

	dpu_hw_blk_init(&hw_pipe->base, DPU_HW_BLK_SSPP, idx, &dpu_hw_ops);

	वापस hw_pipe;
पूर्ण

व्योम dpu_hw_sspp_destroy(काष्ठा dpu_hw_pipe *ctx)
अणु
	अगर (ctx)
		dpu_hw_blk_destroy(&ctx->base);
	kमुक्त(ctx);
पूर्ण

