<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_mdss.h"

#घोषणा LM_OP_MODE                        0x00
#घोषणा LM_OUT_SIZE                       0x04
#घोषणा LM_BORDER_COLOR_0                 0x08
#घोषणा LM_BORDER_COLOR_1                 0x010

/* These रेजिस्टर are offset to mixer base + stage base */
#घोषणा LM_BLEND0_OP                     0x00
#घोषणा LM_BLEND0_CONST_ALPHA            0x04
#घोषणा LM_FG_COLOR_FILL_COLOR_0         0x08
#घोषणा LM_FG_COLOR_FILL_COLOR_1         0x0C
#घोषणा LM_FG_COLOR_FILL_SIZE            0x10
#घोषणा LM_FG_COLOR_FILL_XY              0x14

#घोषणा LM_BLEND0_FG_ALPHA               0x04
#घोषणा LM_BLEND0_BG_ALPHA               0x08

अटल स्थिर काष्ठा dpu_lm_cfg *_lm_offset(क्रमागत dpu_lm mixer,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->mixer_count; i++) अणु
		अगर (mixer == m->mixer[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->mixer[i].base;
			b->length = m->mixer[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_LM;
			वापस &m->mixer[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * _stage_offset(): वापसs the relative offset of the blend रेजिस्टरs
 * क्रम the stage to be setup
 * @ctx:     mixer ctx contains the mixer to be programmed
 * @stage: stage index to setup
 */
अटल अंतरभूत पूर्णांक _stage_offset(काष्ठा dpu_hw_mixer *ctx, क्रमागत dpu_stage stage)
अणु
	स्थिर काष्ठा dpu_lm_sub_blks *sblk = ctx->cap->sblk;
	अगर (stage != DPU_STAGE_BASE && stage <= sblk->maxblendstages)
		वापस sblk->blendstage_base[stage - DPU_STAGE_0];

	वापस -EINVAL;
पूर्ण

अटल व्योम dpu_hw_lm_setup_out(काष्ठा dpu_hw_mixer *ctx,
		काष्ठा dpu_hw_mixer_cfg *mixer)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 outsize;
	u32 op_mode;

	op_mode = DPU_REG_READ(c, LM_OP_MODE);

	outsize = mixer->out_height << 16 | mixer->out_width;
	DPU_REG_WRITE(c, LM_OUT_SIZE, outsize);

	/* SPLIT_LEFT_RIGHT */
	अगर (mixer->right_mixer)
		op_mode |= BIT(31);
	अन्यथा
		op_mode &= ~BIT(31);
	DPU_REG_WRITE(c, LM_OP_MODE, op_mode);
पूर्ण

अटल व्योम dpu_hw_lm_setup_border_color(काष्ठा dpu_hw_mixer *ctx,
		काष्ठा dpu_mdss_color *color,
		u8 border_en)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;

	अगर (border_en) अणु
		DPU_REG_WRITE(c, LM_BORDER_COLOR_0,
			(color->color_0 & 0xFFF) |
			((color->color_1 & 0xFFF) << 0x10));
		DPU_REG_WRITE(c, LM_BORDER_COLOR_1,
			(color->color_2 & 0xFFF) |
			((color->color_3 & 0xFFF) << 0x10));
	पूर्ण
पूर्ण

अटल व्योम dpu_hw_lm_setup_blend_config_sdm845(काष्ठा dpu_hw_mixer *ctx,
	u32 stage, u32 fg_alpha, u32 bg_alpha, u32 blend_op)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	पूर्णांक stage_off;
	u32 स्थिर_alpha;

	अगर (stage == DPU_STAGE_BASE)
		वापस;

	stage_off = _stage_offset(ctx, stage);
	अगर (WARN_ON(stage_off < 0))
		वापस;

	स्थिर_alpha = (bg_alpha & 0xFF) | ((fg_alpha & 0xFF) << 16);
	DPU_REG_WRITE(c, LM_BLEND0_CONST_ALPHA + stage_off, स्थिर_alpha);
	DPU_REG_WRITE(c, LM_BLEND0_OP + stage_off, blend_op);
पूर्ण

अटल व्योम dpu_hw_lm_setup_blend_config(काष्ठा dpu_hw_mixer *ctx,
	u32 stage, u32 fg_alpha, u32 bg_alpha, u32 blend_op)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	पूर्णांक stage_off;

	अगर (stage == DPU_STAGE_BASE)
		वापस;

	stage_off = _stage_offset(ctx, stage);
	अगर (WARN_ON(stage_off < 0))
		वापस;

	DPU_REG_WRITE(c, LM_BLEND0_FG_ALPHA + stage_off, fg_alpha);
	DPU_REG_WRITE(c, LM_BLEND0_BG_ALPHA + stage_off, bg_alpha);
	DPU_REG_WRITE(c, LM_BLEND0_OP + stage_off, blend_op);
पूर्ण

अटल व्योम dpu_hw_lm_setup_color3(काष्ठा dpu_hw_mixer *ctx,
	uपूर्णांक32_t mixer_op_mode)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	पूर्णांक op_mode;

	/* पढ़ो the existing op_mode configuration */
	op_mode = DPU_REG_READ(c, LM_OP_MODE);

	op_mode = (op_mode & (BIT(31) | BIT(30))) | mixer_op_mode;

	DPU_REG_WRITE(c, LM_OP_MODE, op_mode);
पूर्ण

अटल व्योम _setup_mixer_ops(स्थिर काष्ठा dpu_mdss_cfg *m,
		काष्ठा dpu_hw_lm_ops *ops,
		अचिन्हित दीर्घ features)
अणु
	ops->setup_mixer_out = dpu_hw_lm_setup_out;
	अगर (m->hwversion >= DPU_HW_VER_400)
		ops->setup_blend_config = dpu_hw_lm_setup_blend_config_sdm845;
	अन्यथा
		ops->setup_blend_config = dpu_hw_lm_setup_blend_config;
	ops->setup_alpha_out = dpu_hw_lm_setup_color3;
	ops->setup_border_color = dpu_hw_lm_setup_border_color;
पूर्ण

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_mixer *dpu_hw_lm_init(क्रमागत dpu_lm idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_mixer *c;
	स्थिर काष्ठा dpu_lm_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _lm_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Assign ops */
	c->idx = idx;
	c->cap = cfg;
	_setup_mixer_ops(m, &c->ops, c->cap->features);

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_LM, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_lm_destroy(काष्ठा dpu_hw_mixer *lm)
अणु
	अगर (lm)
		dpu_hw_blk_destroy(&lm->base);
	kमुक्त(lm);
पूर्ण
