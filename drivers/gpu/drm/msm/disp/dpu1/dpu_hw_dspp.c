<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_dspp.h"
#समावेश "dpu_kms.h"


/* DSPP_PCC */
#घोषणा PCC_EN BIT(0)
#घोषणा PCC_DIS 0
#घोषणा PCC_RED_R_OFF 0x10
#घोषणा PCC_RED_G_OFF 0x1C
#घोषणा PCC_RED_B_OFF 0x28
#घोषणा PCC_GREEN_R_OFF 0x14
#घोषणा PCC_GREEN_G_OFF 0x20
#घोषणा PCC_GREEN_B_OFF 0x2C
#घोषणा PCC_BLUE_R_OFF 0x18
#घोषणा PCC_BLUE_G_OFF 0x24
#घोषणा PCC_BLUE_B_OFF 0x30

अटल व्योम dpu_setup_dspp_pcc(काष्ठा dpu_hw_dspp *ctx,
		काष्ठा dpu_hw_pcc_cfg *cfg)
अणु

	u32 base = ctx->cap->sblk->pcc.base;

	अगर (!ctx || !base) अणु
		DRM_ERROR("invalid ctx %pK pcc base 0x%x\n", ctx, base);
		वापस;
	पूर्ण

	अगर (!cfg) अणु
		DRM_DEBUG_DRIVER("disable pcc feature\n");
		DPU_REG_WRITE(&ctx->hw, base, PCC_DIS);
		वापस;
	पूर्ण

	DPU_REG_WRITE(&ctx->hw, base + PCC_RED_R_OFF, cfg->r.r);
	DPU_REG_WRITE(&ctx->hw, base + PCC_RED_G_OFF, cfg->r.g);
	DPU_REG_WRITE(&ctx->hw, base + PCC_RED_B_OFF, cfg->r.b);

	DPU_REG_WRITE(&ctx->hw, base + PCC_GREEN_R_OFF, cfg->g.r);
	DPU_REG_WRITE(&ctx->hw, base + PCC_GREEN_G_OFF, cfg->g.g);
	DPU_REG_WRITE(&ctx->hw, base + PCC_GREEN_B_OFF, cfg->g.b);

	DPU_REG_WRITE(&ctx->hw, base + PCC_BLUE_R_OFF, cfg->b.r);
	DPU_REG_WRITE(&ctx->hw, base + PCC_BLUE_G_OFF, cfg->b.g);
	DPU_REG_WRITE(&ctx->hw, base + PCC_BLUE_B_OFF, cfg->b.b);

	DPU_REG_WRITE(&ctx->hw, base, PCC_EN);
पूर्ण

अटल व्योम _setup_dspp_ops(काष्ठा dpu_hw_dspp *c,
		अचिन्हित दीर्घ features)
अणु
	अगर (test_bit(DPU_DSPP_PCC, &features))
		c->ops.setup_pcc = dpu_setup_dspp_pcc;
पूर्ण

अटल स्थिर काष्ठा dpu_dspp_cfg *_dspp_offset(क्रमागत dpu_dspp dspp,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	अगर (!m || !addr || !b)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < m->dspp_count; i++) अणु
		अगर (dspp == m->dspp[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->dspp[i].base;
			b->length = m->dspp[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_DSPP;
			वापस &m->dspp[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_dspp *dpu_hw_dspp_init(क्रमागत dpu_dspp idx,
			व्योम __iomem *addr,
			स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_dspp *c;
	स्थिर काष्ठा dpu_dspp_cfg *cfg;

	अगर (!addr || !m)
		वापस ERR_PTR(-EINVAL);

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _dspp_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Assign ops */
	c->idx = idx;
	c->cap = cfg;
	_setup_dspp_ops(c, c->cap->features);

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_DSPP, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_dspp_destroy(काष्ठा dpu_hw_dspp *dspp)
अणु
	अगर (dspp)
		dpu_hw_blk_destroy(&dspp->base);

	kमुक्त(dspp);
पूर्ण


