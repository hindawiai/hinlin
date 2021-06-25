<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/iopoll.h>

#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_merge3d.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_trace.h"

#घोषणा MERGE_3D_MUX  0x000
#घोषणा MERGE_3D_MODE 0x004

अटल स्थिर काष्ठा dpu_merge_3d_cfg *_merge_3d_offset(क्रमागत dpu_merge_3d idx,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->merge_3d_count; i++) अणु
		अगर (idx == m->merge_3d[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->merge_3d[i].base;
			b->length = m->merge_3d[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_PINGPONG;
			वापस &m->merge_3d[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम dpu_hw_merge_3d_setup_3d_mode(काष्ठा dpu_hw_merge_3d *merge_3d,
			क्रमागत dpu_3d_blend_mode mode_3d)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 data;


	c = &merge_3d->hw;
	अगर (mode_3d == BLEND_3D_NONE) अणु
		DPU_REG_WRITE(c, MERGE_3D_MODE, 0);
		DPU_REG_WRITE(c, MERGE_3D_MUX, 0);
	पूर्ण अन्यथा अणु
		data = BIT(0) | ((mode_3d - 1) << 1);
		DPU_REG_WRITE(c, MERGE_3D_MODE, data);
	पूर्ण
पूर्ण

अटल व्योम _setup_merge_3d_ops(काष्ठा dpu_hw_merge_3d *c,
				अचिन्हित दीर्घ features)
अणु
	c->ops.setup_3d_mode = dpu_hw_merge_3d_setup_3d_mode;
पूर्ण;

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_merge_3d *dpu_hw_merge_3d_init(क्रमागत dpu_merge_3d idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_merge_3d *c;
	स्थिर काष्ठा dpu_merge_3d_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _merge_3d_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	c->idx = idx;
	c->caps = cfg;
	_setup_merge_3d_ops(c, c->caps->features);

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_MERGE_3D, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_merge_3d_destroy(काष्ठा dpu_hw_merge_3d *hw)
अणु
	अगर (hw)
		dpu_hw_blk_destroy(&hw->base);
	kमुक्त(hw);
पूर्ण
