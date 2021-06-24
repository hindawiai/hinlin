<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_trace.h"

#घोषणा   CTL_LAYER(lm)                 \
	(((lm) == LM_5) ? (0x024) : (((lm) - LM_0) * 0x004))
#घोषणा   CTL_LAYER_EXT(lm)             \
	(0x40 + (((lm) - LM_0) * 0x004))
#घोषणा   CTL_LAYER_EXT2(lm)             \
	(0x70 + (((lm) - LM_0) * 0x004))
#घोषणा   CTL_LAYER_EXT3(lm)             \
	(0xA0 + (((lm) - LM_0) * 0x004))
#घोषणा   CTL_TOP                       0x014
#घोषणा   CTL_FLUSH                     0x018
#घोषणा   CTL_START                     0x01C
#घोषणा   CTL_PREPARE                   0x0d0
#घोषणा   CTL_SW_RESET                  0x030
#घोषणा   CTL_LAYER_EXTN_OFFSET         0x40
#घोषणा   CTL_MERGE_3D_ACTIVE           0x0E4
#घोषणा   CTL_INTF_ACTIVE               0x0F4
#घोषणा   CTL_MERGE_3D_FLUSH            0x100
#घोषणा   CTL_INTF_FLUSH                0x110
#घोषणा   CTL_INTF_MASTER               0x134
#घोषणा   CTL_FETCH_PIPE_ACTIVE         0x0FC

#घोषणा CTL_MIXER_BORDER_OUT            BIT(24)
#घोषणा CTL_FLUSH_MASK_CTL              BIT(17)

#घोषणा DPU_REG_RESET_TIMEOUT_US        2000
#घोषणा  MERGE_3D_IDX   23
#घोषणा  INTF_IDX       31
#घोषणा CTL_INVALID_BIT                 0xffff

अटल स्थिर u32 fetch_tbl[SSPP_MAX] = अणुCTL_INVALID_BIT, 16, 17, 18, 19,
	CTL_INVALID_BIT, CTL_INVALID_BIT, CTL_INVALID_BIT, CTL_INVALID_BIT, 0,
	1, 2, 3, CTL_INVALID_BIT, CTL_INVALID_BITपूर्ण;

अटल स्थिर काष्ठा dpu_ctl_cfg *_ctl_offset(क्रमागत dpu_ctl ctl,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->ctl_count; i++) अणु
		अगर (ctl == m->ctl[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->ctl[i].base;
			b->length = m->ctl[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_CTL;
			वापस &m->ctl[i];
		पूर्ण
	पूर्ण
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक _mixer_stages(स्थिर काष्ठा dpu_lm_cfg *mixer, पूर्णांक count,
		क्रमागत dpu_lm lm)
अणु
	पूर्णांक i;
	पूर्णांक stages = -EINVAL;

	क्रम (i = 0; i < count; i++) अणु
		अगर (lm == mixer[i].id) अणु
			stages = mixer[i].sblk->maxblendstages;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस stages;
पूर्ण

अटल अंतरभूत u32 dpu_hw_ctl_get_flush_रेजिस्टर(काष्ठा dpu_hw_ctl *ctx)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;

	वापस DPU_REG_READ(c, CTL_FLUSH);
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_trigger_start(काष्ठा dpu_hw_ctl *ctx)
अणु
	trace_dpu_hw_ctl_trigger_start(ctx->pending_flush_mask,
				       dpu_hw_ctl_get_flush_रेजिस्टर(ctx));
	DPU_REG_WRITE(&ctx->hw, CTL_START, 0x1);
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_trigger_pending(काष्ठा dpu_hw_ctl *ctx)
अणु
	trace_dpu_hw_ctl_trigger_prepare(ctx->pending_flush_mask,
					 dpu_hw_ctl_get_flush_रेजिस्टर(ctx));
	DPU_REG_WRITE(&ctx->hw, CTL_PREPARE, 0x1);
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_clear_pending_flush(काष्ठा dpu_hw_ctl *ctx)
अणु
	trace_dpu_hw_ctl_clear_pending_flush(ctx->pending_flush_mask,
				     dpu_hw_ctl_get_flush_रेजिस्टर(ctx));
	ctx->pending_flush_mask = 0x0;
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_update_pending_flush(काष्ठा dpu_hw_ctl *ctx,
		u32 flushbits)
अणु
	trace_dpu_hw_ctl_update_pending_flush(flushbits,
					      ctx->pending_flush_mask);
	ctx->pending_flush_mask |= flushbits;
पूर्ण

अटल u32 dpu_hw_ctl_get_pending_flush(काष्ठा dpu_hw_ctl *ctx)
अणु
	वापस ctx->pending_flush_mask;
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_trigger_flush_v1(काष्ठा dpu_hw_ctl *ctx)
अणु

	अगर (ctx->pending_flush_mask & BIT(MERGE_3D_IDX))
		DPU_REG_WRITE(&ctx->hw, CTL_MERGE_3D_FLUSH,
				ctx->pending_merge_3d_flush_mask);
	अगर (ctx->pending_flush_mask & BIT(INTF_IDX))
		DPU_REG_WRITE(&ctx->hw, CTL_INTF_FLUSH,
				ctx->pending_पूर्णांकf_flush_mask);

	DPU_REG_WRITE(&ctx->hw, CTL_FLUSH, ctx->pending_flush_mask);
पूर्ण

अटल अंतरभूत व्योम dpu_hw_ctl_trigger_flush(काष्ठा dpu_hw_ctl *ctx)
अणु
	trace_dpu_hw_ctl_trigger_pending_flush(ctx->pending_flush_mask,
				     dpu_hw_ctl_get_flush_रेजिस्टर(ctx));
	DPU_REG_WRITE(&ctx->hw, CTL_FLUSH, ctx->pending_flush_mask);
पूर्ण

अटल uपूर्णांक32_t dpu_hw_ctl_get_biपंचांगask_sspp(काष्ठा dpu_hw_ctl *ctx,
	क्रमागत dpu_sspp sspp)
अणु
	uपूर्णांक32_t flushbits = 0;

	चयन (sspp) अणु
	हाल SSPP_VIG0:
		flushbits =  BIT(0);
		अवरोध;
	हाल SSPP_VIG1:
		flushbits = BIT(1);
		अवरोध;
	हाल SSPP_VIG2:
		flushbits = BIT(2);
		अवरोध;
	हाल SSPP_VIG3:
		flushbits = BIT(18);
		अवरोध;
	हाल SSPP_RGB0:
		flushbits = BIT(3);
		अवरोध;
	हाल SSPP_RGB1:
		flushbits = BIT(4);
		अवरोध;
	हाल SSPP_RGB2:
		flushbits = BIT(5);
		अवरोध;
	हाल SSPP_RGB3:
		flushbits = BIT(19);
		अवरोध;
	हाल SSPP_DMA0:
		flushbits = BIT(11);
		अवरोध;
	हाल SSPP_DMA1:
		flushbits = BIT(12);
		अवरोध;
	हाल SSPP_DMA2:
		flushbits = BIT(24);
		अवरोध;
	हाल SSPP_DMA3:
		flushbits = BIT(25);
		अवरोध;
	हाल SSPP_CURSOR0:
		flushbits = BIT(22);
		अवरोध;
	हाल SSPP_CURSOR1:
		flushbits = BIT(23);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस flushbits;
पूर्ण

अटल uपूर्णांक32_t dpu_hw_ctl_get_biपंचांगask_mixer(काष्ठा dpu_hw_ctl *ctx,
	क्रमागत dpu_lm lm)
अणु
	uपूर्णांक32_t flushbits = 0;

	चयन (lm) अणु
	हाल LM_0:
		flushbits = BIT(6);
		अवरोध;
	हाल LM_1:
		flushbits = BIT(7);
		अवरोध;
	हाल LM_2:
		flushbits = BIT(8);
		अवरोध;
	हाल LM_3:
		flushbits = BIT(9);
		अवरोध;
	हाल LM_4:
		flushbits = BIT(10);
		अवरोध;
	हाल LM_5:
		flushbits = BIT(20);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	flushbits |= CTL_FLUSH_MASK_CTL;

	वापस flushbits;
पूर्ण

अटल व्योम dpu_hw_ctl_update_pending_flush_पूर्णांकf(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_पूर्णांकf पूर्णांकf)
अणु
	चयन (पूर्णांकf) अणु
	हाल INTF_0:
		ctx->pending_flush_mask |= BIT(31);
		अवरोध;
	हाल INTF_1:
		ctx->pending_flush_mask |= BIT(30);
		अवरोध;
	हाल INTF_2:
		ctx->pending_flush_mask |= BIT(29);
		अवरोध;
	हाल INTF_3:
		ctx->pending_flush_mask |= BIT(28);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dpu_hw_ctl_update_pending_flush_पूर्णांकf_v1(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_पूर्णांकf पूर्णांकf)
अणु
	ctx->pending_पूर्णांकf_flush_mask |= BIT(पूर्णांकf - INTF_0);
	ctx->pending_flush_mask |= BIT(INTF_IDX);
पूर्ण

अटल व्योम dpu_hw_ctl_update_pending_flush_merge_3d_v1(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_merge_3d merge_3d)
अणु
	ctx->pending_merge_3d_flush_mask |= BIT(merge_3d - MERGE_3D_0);
	ctx->pending_flush_mask |= BIT(MERGE_3D_IDX);
पूर्ण

अटल uपूर्णांक32_t dpu_hw_ctl_get_biपंचांगask_dspp(काष्ठा dpu_hw_ctl *ctx,
	क्रमागत dpu_dspp dspp)
अणु
	uपूर्णांक32_t flushbits = 0;

	चयन (dspp) अणु
	हाल DSPP_0:
		flushbits = BIT(13);
		अवरोध;
	हाल DSPP_1:
		flushbits = BIT(14);
		अवरोध;
	हाल DSPP_2:
		flushbits = BIT(15);
		अवरोध;
	हाल DSPP_3:
		flushbits = BIT(21);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस flushbits;
पूर्ण

अटल u32 dpu_hw_ctl_poll_reset_status(काष्ठा dpu_hw_ctl *ctx, u32 समयout_us)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	kसमय_प्रकार समयout;
	u32 status;

	समयout = kसमय_add_us(kसमय_get(), समयout_us);

	/*
	 * it takes around 30us to have mdp finish resetting its ctl path
	 * poll every 50us so that reset should be completed at 1st poll
	 */
	करो अणु
		status = DPU_REG_READ(c, CTL_SW_RESET);
		status &= 0x1;
		अगर (status)
			usleep_range(20, 50);
	पूर्ण जबतक (status && kसमय_compare_safe(kसमय_get(), समयout) < 0);

	वापस status;
पूर्ण

अटल पूर्णांक dpu_hw_ctl_reset_control(काष्ठा dpu_hw_ctl *ctx)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;

	pr_debug("issuing hw ctl reset for ctl:%d\n", ctx->idx);
	DPU_REG_WRITE(c, CTL_SW_RESET, 0x1);
	अगर (dpu_hw_ctl_poll_reset_status(ctx, DPU_REG_RESET_TIMEOUT_US))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_ctl_रुको_reset_status(काष्ठा dpu_hw_ctl *ctx)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 status;

	status = DPU_REG_READ(c, CTL_SW_RESET);
	status &= 0x01;
	अगर (!status)
		वापस 0;

	pr_debug("hw ctl reset is set for ctl:%d\n", ctx->idx);
	अगर (dpu_hw_ctl_poll_reset_status(ctx, DPU_REG_RESET_TIMEOUT_US)) अणु
		pr_err("hw recovery is not complete for ctl:%d\n", ctx->idx);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpu_hw_ctl_clear_all_blendstages(काष्ठा dpu_hw_ctl *ctx)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	पूर्णांक i;

	क्रम (i = 0; i < ctx->mixer_count; i++) अणु
		DPU_REG_WRITE(c, CTL_LAYER(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT2(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT3(LM_0 + i), 0);
	पूर्ण

	DPU_REG_WRITE(c, CTL_FETCH_PIPE_ACTIVE, 0);
पूर्ण

अटल व्योम dpu_hw_ctl_setup_blendstage(काष्ठा dpu_hw_ctl *ctx,
	क्रमागत dpu_lm lm, काष्ठा dpu_hw_stage_cfg *stage_cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 mixercfg = 0, mixercfg_ext = 0, mix, ext;
	u32 mixercfg_ext2 = 0, mixercfg_ext3 = 0;
	पूर्णांक i, j;
	पूर्णांक stages;
	पूर्णांक pipes_per_stage;

	stages = _mixer_stages(ctx->mixer_hw_caps, ctx->mixer_count, lm);
	अगर (stages < 0)
		वापस;

	अगर (test_bit(DPU_MIXER_SOURCESPLIT,
		&ctx->mixer_hw_caps->features))
		pipes_per_stage = PIPES_PER_STAGE;
	अन्यथा
		pipes_per_stage = 1;

	mixercfg = CTL_MIXER_BORDER_OUT; /* always set BORDER_OUT */

	अगर (!stage_cfg)
		जाओ निकास;

	क्रम (i = 0; i <= stages; i++) अणु
		/* overflow to ext रेजिस्टर अगर 'i + 1 > 7' */
		mix = (i + 1) & 0x7;
		ext = i >= 7;

		क्रम (j = 0 ; j < pipes_per_stage; j++) अणु
			क्रमागत dpu_sspp_multirect_index rect_index =
				stage_cfg->multirect_index[i][j];

			चयन (stage_cfg->stage[i][j]) अणु
			हाल SSPP_VIG0:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext3 |= ((i + 1) & 0xF) << 0;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 0;
					mixercfg_ext |= ext << 0;
				पूर्ण
				अवरोध;
			हाल SSPP_VIG1:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext3 |= ((i + 1) & 0xF) << 4;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 3;
					mixercfg_ext |= ext << 2;
				पूर्ण
				अवरोध;
			हाल SSPP_VIG2:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext3 |= ((i + 1) & 0xF) << 8;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 6;
					mixercfg_ext |= ext << 4;
				पूर्ण
				अवरोध;
			हाल SSPP_VIG3:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext3 |= ((i + 1) & 0xF) << 12;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 26;
					mixercfg_ext |= ext << 6;
				पूर्ण
				अवरोध;
			हाल SSPP_RGB0:
				mixercfg |= mix << 9;
				mixercfg_ext |= ext << 8;
				अवरोध;
			हाल SSPP_RGB1:
				mixercfg |= mix << 12;
				mixercfg_ext |= ext << 10;
				अवरोध;
			हाल SSPP_RGB2:
				mixercfg |= mix << 15;
				mixercfg_ext |= ext << 12;
				अवरोध;
			हाल SSPP_RGB3:
				mixercfg |= mix << 29;
				mixercfg_ext |= ext << 14;
				अवरोध;
			हाल SSPP_DMA0:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext2 |= ((i + 1) & 0xF) << 8;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 18;
					mixercfg_ext |= ext << 16;
				पूर्ण
				अवरोध;
			हाल SSPP_DMA1:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext2 |= ((i + 1) & 0xF) << 12;
				पूर्ण अन्यथा अणु
					mixercfg |= mix << 21;
					mixercfg_ext |= ext << 18;
				पूर्ण
				अवरोध;
			हाल SSPP_DMA2:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext2 |= ((i + 1) & 0xF) << 16;
				पूर्ण अन्यथा अणु
					mix |= (i + 1) & 0xF;
					mixercfg_ext2 |= mix << 0;
				पूर्ण
				अवरोध;
			हाल SSPP_DMA3:
				अगर (rect_index == DPU_SSPP_RECT_1) अणु
					mixercfg_ext2 |= ((i + 1) & 0xF) << 20;
				पूर्ण अन्यथा अणु
					mix |= (i + 1) & 0xF;
					mixercfg_ext2 |= mix << 4;
				पूर्ण
				अवरोध;
			हाल SSPP_CURSOR0:
				mixercfg_ext |= ((i + 1) & 0xF) << 20;
				अवरोध;
			हाल SSPP_CURSOR1:
				mixercfg_ext |= ((i + 1) & 0xF) << 26;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	DPU_REG_WRITE(c, CTL_LAYER(lm), mixercfg);
	DPU_REG_WRITE(c, CTL_LAYER_EXT(lm), mixercfg_ext);
	DPU_REG_WRITE(c, CTL_LAYER_EXT2(lm), mixercfg_ext2);
	DPU_REG_WRITE(c, CTL_LAYER_EXT3(lm), mixercfg_ext3);
पूर्ण


अटल व्योम dpu_hw_ctl_पूर्णांकf_cfg_v1(काष्ठा dpu_hw_ctl *ctx,
		काष्ठा dpu_hw_पूर्णांकf_cfg *cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 पूर्णांकf_active = 0;
	u32 mode_sel = 0;

	अगर (cfg->पूर्णांकf_mode_sel == DPU_CTL_MODE_SEL_CMD)
		mode_sel |= BIT(17);

	पूर्णांकf_active = DPU_REG_READ(c, CTL_INTF_ACTIVE);
	पूर्णांकf_active |= BIT(cfg->पूर्णांकf - INTF_0);

	DPU_REG_WRITE(c, CTL_TOP, mode_sel);
	DPU_REG_WRITE(c, CTL_INTF_ACTIVE, पूर्णांकf_active);
	अगर (cfg->merge_3d)
		DPU_REG_WRITE(c, CTL_MERGE_3D_ACTIVE,
			      BIT(cfg->merge_3d - MERGE_3D_0));
पूर्ण

अटल व्योम dpu_hw_ctl_पूर्णांकf_cfg(काष्ठा dpu_hw_ctl *ctx,
		काष्ठा dpu_hw_पूर्णांकf_cfg *cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 पूर्णांकf_cfg = 0;

	पूर्णांकf_cfg |= (cfg->पूर्णांकf & 0xF) << 4;

	अगर (cfg->mode_3d) अणु
		पूर्णांकf_cfg |= BIT(19);
		पूर्णांकf_cfg |= (cfg->mode_3d - 0x1) << 20;
	पूर्ण

	चयन (cfg->पूर्णांकf_mode_sel) अणु
	हाल DPU_CTL_MODE_SEL_VID:
		पूर्णांकf_cfg &= ~BIT(17);
		पूर्णांकf_cfg &= ~(0x3 << 15);
		अवरोध;
	हाल DPU_CTL_MODE_SEL_CMD:
		पूर्णांकf_cfg |= BIT(17);
		पूर्णांकf_cfg |= ((cfg->stream_sel & 0x3) << 15);
		अवरोध;
	शेष:
		pr_err("unknown interface type %d\n", cfg->पूर्णांकf_mode_sel);
		वापस;
	पूर्ण

	DPU_REG_WRITE(c, CTL_TOP, पूर्णांकf_cfg);
पूर्ण

अटल व्योम dpu_hw_ctl_set_fetch_pipe_active(काष्ठा dpu_hw_ctl *ctx,
	अचिन्हित दीर्घ *fetch_active)
अणु
	पूर्णांक i;
	u32 val = 0;

	अगर (fetch_active) अणु
		क्रम (i = 0; i < SSPP_MAX; i++) अणु
			अगर (test_bit(i, fetch_active) &&
				fetch_tbl[i] != CTL_INVALID_BIT)
				val |= BIT(fetch_tbl[i]);
		पूर्ण
	पूर्ण

	DPU_REG_WRITE(&ctx->hw, CTL_FETCH_PIPE_ACTIVE, val);
पूर्ण

अटल व्योम _setup_ctl_ops(काष्ठा dpu_hw_ctl_ops *ops,
		अचिन्हित दीर्घ cap)
अणु
	अगर (cap & BIT(DPU_CTL_ACTIVE_CFG)) अणु
		ops->trigger_flush = dpu_hw_ctl_trigger_flush_v1;
		ops->setup_पूर्णांकf_cfg = dpu_hw_ctl_पूर्णांकf_cfg_v1;
		ops->update_pending_flush_पूर्णांकf =
			dpu_hw_ctl_update_pending_flush_पूर्णांकf_v1;
		ops->update_pending_flush_merge_3d =
			dpu_hw_ctl_update_pending_flush_merge_3d_v1;
	पूर्ण अन्यथा अणु
		ops->trigger_flush = dpu_hw_ctl_trigger_flush;
		ops->setup_पूर्णांकf_cfg = dpu_hw_ctl_पूर्णांकf_cfg;
		ops->update_pending_flush_पूर्णांकf =
			dpu_hw_ctl_update_pending_flush_पूर्णांकf;
	पूर्ण
	ops->clear_pending_flush = dpu_hw_ctl_clear_pending_flush;
	ops->update_pending_flush = dpu_hw_ctl_update_pending_flush;
	ops->get_pending_flush = dpu_hw_ctl_get_pending_flush;
	ops->get_flush_रेजिस्टर = dpu_hw_ctl_get_flush_रेजिस्टर;
	ops->trigger_start = dpu_hw_ctl_trigger_start;
	ops->trigger_pending = dpu_hw_ctl_trigger_pending;
	ops->reset = dpu_hw_ctl_reset_control;
	ops->रुको_reset_status = dpu_hw_ctl_रुको_reset_status;
	ops->clear_all_blendstages = dpu_hw_ctl_clear_all_blendstages;
	ops->setup_blendstage = dpu_hw_ctl_setup_blendstage;
	ops->get_biपंचांगask_sspp = dpu_hw_ctl_get_biपंचांगask_sspp;
	ops->get_biपंचांगask_mixer = dpu_hw_ctl_get_biपंचांगask_mixer;
	ops->get_biपंचांगask_dspp = dpu_hw_ctl_get_biपंचांगask_dspp;
	अगर (cap & BIT(DPU_CTL_FETCH_ACTIVE))
		ops->set_active_pipes = dpu_hw_ctl_set_fetch_pipe_active;
पूर्ण;

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_ctl *dpu_hw_ctl_init(क्रमागत dpu_ctl idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_ctl *c;
	स्थिर काष्ठा dpu_ctl_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _ctl_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		pr_err("failed to create dpu_hw_ctl %d\n", idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	c->caps = cfg;
	_setup_ctl_ops(&c->ops, c->caps->features);
	c->idx = idx;
	c->mixer_count = m->mixer_count;
	c->mixer_hw_caps = m->mixer;

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_CTL, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_ctl_destroy(काष्ठा dpu_hw_ctl *ctx)
अणु
	अगर (ctx)
		dpu_hw_blk_destroy(&ctx->base);
	kमुक्त(ctx);
पूर्ण
