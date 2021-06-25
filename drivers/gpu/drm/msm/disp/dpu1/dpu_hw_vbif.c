<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_vbif.h"

#घोषणा VBIF_VERSION			0x0000
#घोषणा VBIF_CLK_FORCE_CTRL0		0x0008
#घोषणा VBIF_CLK_FORCE_CTRL1		0x000C
#घोषणा VBIF_QOS_REMAP_00		0x0020
#घोषणा VBIF_QOS_REMAP_01		0x0024
#घोषणा VBIF_QOS_REMAP_10		0x0028
#घोषणा VBIF_QOS_REMAP_11		0x002C
#घोषणा VBIF_WRITE_GATHER_EN		0x00AC
#घोषणा VBIF_IN_RD_LIM_CONF0		0x00B0
#घोषणा VBIF_IN_RD_LIM_CONF1		0x00B4
#घोषणा VBIF_IN_RD_LIM_CONF2		0x00B8
#घोषणा VBIF_IN_WR_LIM_CONF0		0x00C0
#घोषणा VBIF_IN_WR_LIM_CONF1		0x00C4
#घोषणा VBIF_IN_WR_LIM_CONF2		0x00C8
#घोषणा VBIF_OUT_RD_LIM_CONF0		0x00D0
#घोषणा VBIF_OUT_WR_LIM_CONF0		0x00D4
#घोषणा VBIF_OUT_AXI_AMEMTYPE_CONF0	0x0160
#घोषणा VBIF_OUT_AXI_AMEMTYPE_CONF1	0x0164
#घोषणा VBIF_XIN_PND_ERR		0x0190
#घोषणा VBIF_XIN_SRC_ERR		0x0194
#घोषणा VBIF_XIN_CLR_ERR		0x019C
#घोषणा VBIF_XIN_HALT_CTRL0		0x0200
#घोषणा VBIF_XIN_HALT_CTRL1		0x0204
#घोषणा VBIF_XINL_QOS_RP_REMAP_000	0x0550
#घोषणा VBIF_XINL_QOS_LVL_REMAP_000(v)	(v < DPU_HW_VER_400 ? 0x570 : 0x0590)

अटल व्योम dpu_hw_clear_errors(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 *pnd_errors, u32 *src_errors)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 pnd, src;

	अगर (!vbअगर)
		वापस;
	c = &vbअगर->hw;
	pnd = DPU_REG_READ(c, VBIF_XIN_PND_ERR);
	src = DPU_REG_READ(c, VBIF_XIN_SRC_ERR);

	अगर (pnd_errors)
		*pnd_errors = pnd;
	अगर (src_errors)
		*src_errors = src;

	DPU_REG_WRITE(c, VBIF_XIN_CLR_ERR, pnd | src);
पूर्ण

अटल व्योम dpu_hw_set_mem_type(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id, u32 value)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 reg_off;
	u32 bit_off;
	u32 reg_val;

	/*
	 * Assume 4 bits per bit field, 8 fields per 32-bit रेजिस्टर so
	 * 16 bit fields maximum across two रेजिस्टरs
	 */
	अगर (!vbअगर || xin_id >= MAX_XIN_COUNT || xin_id >= 16)
		वापस;

	c = &vbअगर->hw;

	अगर (xin_id >= 8) अणु
		xin_id -= 8;
		reg_off = VBIF_OUT_AXI_AMEMTYPE_CONF1;
	पूर्ण अन्यथा अणु
		reg_off = VBIF_OUT_AXI_AMEMTYPE_CONF0;
	पूर्ण
	bit_off = (xin_id & 0x7) * 4;
	reg_val = DPU_REG_READ(c, reg_off);
	reg_val &= ~(0x7 << bit_off);
	reg_val |= (value & 0x7) << bit_off;
	DPU_REG_WRITE(c, reg_off, reg_val);
पूर्ण

अटल व्योम dpu_hw_set_limit_conf(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id, bool rd, u32 limit)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &vbअगर->hw;
	u32 reg_val;
	u32 reg_off;
	u32 bit_off;

	अगर (rd)
		reg_off = VBIF_IN_RD_LIM_CONF0;
	अन्यथा
		reg_off = VBIF_IN_WR_LIM_CONF0;

	reg_off += (xin_id / 4) * 4;
	bit_off = (xin_id % 4) * 8;
	reg_val = DPU_REG_READ(c, reg_off);
	reg_val &= ~(0xFF << bit_off);
	reg_val |= (limit) << bit_off;
	DPU_REG_WRITE(c, reg_off, reg_val);
पूर्ण

अटल u32 dpu_hw_get_limit_conf(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id, bool rd)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &vbअगर->hw;
	u32 reg_val;
	u32 reg_off;
	u32 bit_off;
	u32 limit;

	अगर (rd)
		reg_off = VBIF_IN_RD_LIM_CONF0;
	अन्यथा
		reg_off = VBIF_IN_WR_LIM_CONF0;

	reg_off += (xin_id / 4) * 4;
	bit_off = (xin_id % 4) * 8;
	reg_val = DPU_REG_READ(c, reg_off);
	limit = (reg_val >> bit_off) & 0xFF;

	वापस limit;
पूर्ण

अटल व्योम dpu_hw_set_halt_ctrl(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id, bool enable)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &vbअगर->hw;
	u32 reg_val;

	reg_val = DPU_REG_READ(c, VBIF_XIN_HALT_CTRL0);

	अगर (enable)
		reg_val |= BIT(xin_id);
	अन्यथा
		reg_val &= ~BIT(xin_id);

	DPU_REG_WRITE(c, VBIF_XIN_HALT_CTRL0, reg_val);
पूर्ण

अटल bool dpu_hw_get_halt_ctrl(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &vbअगर->hw;
	u32 reg_val;

	reg_val = DPU_REG_READ(c, VBIF_XIN_HALT_CTRL1);

	वापस (reg_val & BIT(xin_id)) ? true : false;
पूर्ण

अटल व्योम dpu_hw_set_qos_remap(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 xin_id, u32 level, u32 remap_level)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 reg_lvl, reg_val, reg_val_lvl, mask, reg_high, reg_shअगरt;

	अगर (!vbअगर)
		वापस;

	c = &vbअगर->hw;

	reg_lvl = VBIF_XINL_QOS_LVL_REMAP_000(c->hwversion);
	reg_high = ((xin_id & 0x8) >> 3) * 4 + (level * 8);
	reg_shअगरt = (xin_id & 0x7) * 4;

	reg_val = DPU_REG_READ(c, VBIF_XINL_QOS_RP_REMAP_000 + reg_high);
	reg_val_lvl = DPU_REG_READ(c, reg_lvl + reg_high);

	mask = 0x7 << reg_shअगरt;

	reg_val &= ~mask;
	reg_val |= (remap_level << reg_shअगरt) & mask;

	reg_val_lvl &= ~mask;
	reg_val_lvl |= (remap_level << reg_shअगरt) & mask;

	DPU_REG_WRITE(c, VBIF_XINL_QOS_RP_REMAP_000 + reg_high, reg_val);
	DPU_REG_WRITE(c, reg_lvl + reg_high, reg_val_lvl);
पूर्ण

अटल व्योम dpu_hw_set_ग_लिखो_gather_en(काष्ठा dpu_hw_vbअगर *vbअगर, u32 xin_id)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 reg_val;

	अगर (!vbअगर || xin_id >= MAX_XIN_COUNT)
		वापस;

	c = &vbअगर->hw;

	reg_val = DPU_REG_READ(c, VBIF_WRITE_GATHER_EN);
	reg_val |= BIT(xin_id);
	DPU_REG_WRITE(c, VBIF_WRITE_GATHER_EN, reg_val);
पूर्ण

अटल व्योम _setup_vbअगर_ops(काष्ठा dpu_hw_vbअगर_ops *ops,
		अचिन्हित दीर्घ cap)
अणु
	ops->set_limit_conf = dpu_hw_set_limit_conf;
	ops->get_limit_conf = dpu_hw_get_limit_conf;
	ops->set_halt_ctrl = dpu_hw_set_halt_ctrl;
	ops->get_halt_ctrl = dpu_hw_get_halt_ctrl;
	अगर (test_bit(DPU_VBIF_QOS_REMAP, &cap))
		ops->set_qos_remap = dpu_hw_set_qos_remap;
	ops->set_mem_type = dpu_hw_set_mem_type;
	ops->clear_errors = dpu_hw_clear_errors;
	ops->set_ग_लिखो_gather_en = dpu_hw_set_ग_लिखो_gather_en;
पूर्ण

अटल स्थिर काष्ठा dpu_vbअगर_cfg *_top_offset(क्रमागत dpu_vbअगर vbअगर,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->vbअगर_count; i++) अणु
		अगर (vbअगर == m->vbअगर[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->vbअगर[i].base;
			b->length = m->vbअगर[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_VBIF;
			वापस &m->vbअगर[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा dpu_hw_vbअगर *dpu_hw_vbअगर_init(क्रमागत dpu_vbअगर idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_vbअगर *c;
	स्थिर काष्ठा dpu_vbअगर_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _top_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Assign ops
	 */
	c->idx = idx;
	c->cap = cfg;
	_setup_vbअगर_ops(&c->ops, c->cap->features);

	/* no need to रेजिस्टर sub-range in dpu dbg, dump entire vbअगर io base */

	वापस c;
पूर्ण

व्योम dpu_hw_vbअगर_destroy(काष्ठा dpu_hw_vbअगर *vbअगर)
अणु
	kमुक्त(vbअगर);
पूर्ण
