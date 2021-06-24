<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/iopoll.h>

#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_pingpong.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_trace.h"

#घोषणा PP_TEAR_CHECK_EN                0x000
#घोषणा PP_SYNC_CONFIG_VSYNC            0x004
#घोषणा PP_SYNC_CONFIG_HEIGHT           0x008
#घोषणा PP_SYNC_WRCOUNT                 0x00C
#घोषणा PP_VSYNC_INIT_VAL               0x010
#घोषणा PP_INT_COUNT_VAL                0x014
#घोषणा PP_SYNC_THRESH                  0x018
#घोषणा PP_START_POS                    0x01C
#घोषणा PP_RD_PTR_IRQ                   0x020
#घोषणा PP_WR_PTR_IRQ                   0x024
#घोषणा PP_OUT_LINE_COUNT               0x028
#घोषणा PP_LINE_COUNT                   0x02C
#घोषणा PP_AUTOREFRESH_CONFIG           0x030

#घोषणा PP_FBC_MODE                     0x034
#घोषणा PP_FBC_BUDGET_CTL               0x038
#घोषणा PP_FBC_LOSSY_MODE               0x03C

#घोषणा PP_DITHER_EN			0x000
#घोषणा PP_DITHER_BITDEPTH		0x004
#घोषणा PP_DITHER_MATRIX		0x008

#घोषणा DITHER_DEPTH_MAP_INDEX 9

अटल u32 dither_depth_map[DITHER_DEPTH_MAP_INDEX] = अणु
	0, 0, 0, 0, 0, 0, 0, 1, 2
पूर्ण;

अटल स्थिर काष्ठा dpu_pingpong_cfg *_pingpong_offset(क्रमागत dpu_pingpong pp,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->pingpong_count; i++) अणु
		अगर (pp == m->pingpong[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->pingpong[i].base;
			b->length = m->pingpong[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_PINGPONG;
			वापस &m->pingpong[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम dpu_hw_pp_setup_dither(काष्ठा dpu_hw_pingpong *pp,
				    काष्ठा dpu_hw_dither_cfg *cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 i, base, data = 0;

	c = &pp->hw;
	base = pp->caps->sblk->dither.base;
	अगर (!cfg) अणु
		DPU_REG_WRITE(c, base + PP_DITHER_EN, 0);
		वापस;
	पूर्ण

	data = dither_depth_map[cfg->c0_bitdepth] & REG_MASK(2);
	data |= (dither_depth_map[cfg->c1_bitdepth] & REG_MASK(2)) << 2;
	data |= (dither_depth_map[cfg->c2_bitdepth] & REG_MASK(2)) << 4;
	data |= (dither_depth_map[cfg->c3_bitdepth] & REG_MASK(2)) << 6;
	data |= (cfg->temporal_en) ? (1 << 8) : 0;

	DPU_REG_WRITE(c, base + PP_DITHER_BITDEPTH, data);

	क्रम (i = 0; i < DITHER_MATRIX_SZ - 3; i += 4) अणु
		data = (cfg->matrix[i] & REG_MASK(4)) |
			((cfg->matrix[i + 1] & REG_MASK(4)) << 4) |
			((cfg->matrix[i + 2] & REG_MASK(4)) << 8) |
			((cfg->matrix[i + 3] & REG_MASK(4)) << 12);
		DPU_REG_WRITE(c, base + PP_DITHER_MATRIX + i, data);
	पूर्ण
	DPU_REG_WRITE(c, base + PP_DITHER_EN, 1);
पूर्ण

अटल पूर्णांक dpu_hw_pp_setup_te_config(काष्ठा dpu_hw_pingpong *pp,
		काष्ठा dpu_hw_tear_check *te)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	पूर्णांक cfg;

	अगर (!pp || !te)
		वापस -EINVAL;
	c = &pp->hw;

	cfg = BIT(19); /*VSYNC_COUNTER_EN */
	अगर (te->hw_vsync_mode)
		cfg |= BIT(20);

	cfg |= te->vsync_count;

	DPU_REG_WRITE(c, PP_SYNC_CONFIG_VSYNC, cfg);
	DPU_REG_WRITE(c, PP_SYNC_CONFIG_HEIGHT, te->sync_cfg_height);
	DPU_REG_WRITE(c, PP_VSYNC_INIT_VAL, te->vsync_init_val);
	DPU_REG_WRITE(c, PP_RD_PTR_IRQ, te->rd_ptr_irq);
	DPU_REG_WRITE(c, PP_START_POS, te->start_pos);
	DPU_REG_WRITE(c, PP_SYNC_THRESH,
			((te->sync_threshold_जारी << 16) |
			 te->sync_threshold_start));
	DPU_REG_WRITE(c, PP_SYNC_WRCOUNT,
			(te->start_pos + te->sync_threshold_start + 1));

	वापस 0;
पूर्ण

अटल व्योम dpu_hw_pp_setup_स्वतःrefresh_config(काष्ठा dpu_hw_pingpong *pp,
					       u32 frame_count, bool enable)
अणु
	DPU_REG_WRITE(&pp->hw, PP_AUTOREFRESH_CONFIG,
		      enable ? (BIT(31) | frame_count) : 0);
पूर्ण

/*
 * dpu_hw_pp_get_स्वतःrefresh_config - Get स्वतःrefresh config from HW
 * @pp:          DPU pingpong काष्ठाure
 * @frame_count: Used to वापस the current frame count from hw
 *
 * Returns: True अगर स्वतःrefresh enabled, false अगर disabled.
 */
अटल bool dpu_hw_pp_get_स्वतःrefresh_config(काष्ठा dpu_hw_pingpong *pp,
					     u32 *frame_count)
अणु
	u32 val = DPU_REG_READ(&pp->hw, PP_AUTOREFRESH_CONFIG);
	अगर (frame_count != शून्य)
		*frame_count = val & 0xffff;
	वापस !!((val & BIT(31)) >> 31);
पूर्ण

अटल पूर्णांक dpu_hw_pp_poll_समयout_wr_ptr(काष्ठा dpu_hw_pingpong *pp,
		u32 समयout_us)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 val;
	पूर्णांक rc;

	अगर (!pp)
		वापस -EINVAL;

	c = &pp->hw;
	rc = पढ़ोl_poll_समयout(c->base_off + c->blk_off + PP_LINE_COUNT,
			val, (val & 0xffff) >= 1, 10, समयout_us);

	वापस rc;
पूर्ण

अटल पूर्णांक dpu_hw_pp_enable_te(काष्ठा dpu_hw_pingpong *pp, bool enable)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;

	अगर (!pp)
		वापस -EINVAL;
	c = &pp->hw;

	DPU_REG_WRITE(c, PP_TEAR_CHECK_EN, enable);
	वापस 0;
पूर्ण

अटल पूर्णांक dpu_hw_pp_connect_बाह्यal_te(काष्ठा dpu_hw_pingpong *pp,
		bool enable_बाह्यal_te)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &pp->hw;
	u32 cfg;
	पूर्णांक orig;

	अगर (!pp)
		वापस -EINVAL;

	c = &pp->hw;
	cfg = DPU_REG_READ(c, PP_SYNC_CONFIG_VSYNC);
	orig = (bool)(cfg & BIT(20));
	अगर (enable_बाह्यal_te)
		cfg |= BIT(20);
	अन्यथा
		cfg &= ~BIT(20);
	DPU_REG_WRITE(c, PP_SYNC_CONFIG_VSYNC, cfg);
	trace_dpu_pp_connect_ext_te(pp->idx - PINGPONG_0, cfg);

	वापस orig;
पूर्ण

अटल पूर्णांक dpu_hw_pp_get_vsync_info(काष्ठा dpu_hw_pingpong *pp,
		काष्ठा dpu_hw_pp_vsync_info *info)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 val;

	अगर (!pp || !info)
		वापस -EINVAL;
	c = &pp->hw;

	val = DPU_REG_READ(c, PP_VSYNC_INIT_VAL);
	info->rd_ptr_init_val = val & 0xffff;

	val = DPU_REG_READ(c, PP_INT_COUNT_VAL);
	info->rd_ptr_frame_count = (val & 0xffff0000) >> 16;
	info->rd_ptr_line_count = val & 0xffff;

	val = DPU_REG_READ(c, PP_LINE_COUNT);
	info->wr_ptr_line_count = val & 0xffff;

	वापस 0;
पूर्ण

अटल u32 dpu_hw_pp_get_line_count(काष्ठा dpu_hw_pingpong *pp)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &pp->hw;
	u32 height, init;
	u32 line = 0xFFFF;

	अगर (!pp)
		वापस 0;
	c = &pp->hw;

	init = DPU_REG_READ(c, PP_VSYNC_INIT_VAL) & 0xFFFF;
	height = DPU_REG_READ(c, PP_SYNC_CONFIG_HEIGHT) & 0xFFFF;

	अगर (height < init)
		वापस line;

	line = DPU_REG_READ(c, PP_INT_COUNT_VAL) & 0xFFFF;

	अगर (line < init)
		line += (0xFFFF - init);
	अन्यथा
		line -= init;

	वापस line;
पूर्ण

अटल व्योम _setup_pingpong_ops(काष्ठा dpu_hw_pingpong *c,
				अचिन्हित दीर्घ features)
अणु
	c->ops.setup_tearcheck = dpu_hw_pp_setup_te_config;
	c->ops.enable_tearcheck = dpu_hw_pp_enable_te;
	c->ops.connect_बाह्यal_te = dpu_hw_pp_connect_बाह्यal_te;
	c->ops.get_vsync_info = dpu_hw_pp_get_vsync_info;
	c->ops.setup_स्वतःrefresh = dpu_hw_pp_setup_स्वतःrefresh_config;
	c->ops.get_स्वतःrefresh = dpu_hw_pp_get_स्वतःrefresh_config;
	c->ops.poll_समयout_wr_ptr = dpu_hw_pp_poll_समयout_wr_ptr;
	c->ops.get_line_count = dpu_hw_pp_get_line_count;

	अगर (test_bit(DPU_PINGPONG_DITHER, &features))
		c->ops.setup_dither = dpu_hw_pp_setup_dither;
पूर्ण;

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_pingpong *dpu_hw_pingpong_init(क्रमागत dpu_pingpong idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_pingpong *c;
	स्थिर काष्ठा dpu_pingpong_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _pingpong_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	c->idx = idx;
	c->caps = cfg;
	_setup_pingpong_ops(c, c->caps->features);

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_PINGPONG, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_pingpong_destroy(काष्ठा dpu_hw_pingpong *pp)
अणु
	अगर (pp)
		dpu_hw_blk_destroy(&pp->base);
	kमुक्त(pp);
पूर्ण
