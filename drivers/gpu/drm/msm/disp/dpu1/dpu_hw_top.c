<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_top.h"
#समावेश "dpu_kms.h"

#घोषणा SSPP_SPARE                        0x28

#घोषणा FLD_SPLIT_DISPLAY_CMD             BIT(1)
#घोषणा FLD_SMART_PANEL_FREE_RUN          BIT(2)
#घोषणा FLD_INTF_1_SW_TRG_MUX             BIT(4)
#घोषणा FLD_INTF_2_SW_TRG_MUX             BIT(8)
#घोषणा FLD_TE_LINE_INTER_WATERLEVEL_MASK 0xFFFF

#घोषणा DANGER_STATUS                     0x360
#घोषणा SAFE_STATUS                       0x364

#घोषणा TE_LINE_INTERVAL                  0x3F4

#घोषणा TRAFFIC_SHAPER_EN                 BIT(31)
#घोषणा TRAFFIC_SHAPER_RD_CLIENT(num)     (0x030 + (num * 4))
#घोषणा TRAFFIC_SHAPER_WR_CLIENT(num)     (0x060 + (num * 4))
#घोषणा TRAFFIC_SHAPER_FIXPOINT_FACTOR    4

#घोषणा MDP_WD_TIMER_0_CTL                0x380
#घोषणा MDP_WD_TIMER_0_CTL2               0x384
#घोषणा MDP_WD_TIMER_0_LOAD_VALUE         0x388
#घोषणा MDP_WD_TIMER_1_CTL                0x390
#घोषणा MDP_WD_TIMER_1_CTL2               0x394
#घोषणा MDP_WD_TIMER_1_LOAD_VALUE         0x398
#घोषणा MDP_WD_TIMER_2_CTL                0x420
#घोषणा MDP_WD_TIMER_2_CTL2               0x424
#घोषणा MDP_WD_TIMER_2_LOAD_VALUE         0x428
#घोषणा MDP_WD_TIMER_3_CTL                0x430
#घोषणा MDP_WD_TIMER_3_CTL2               0x434
#घोषणा MDP_WD_TIMER_3_LOAD_VALUE         0x438
#घोषणा MDP_WD_TIMER_4_CTL                0x440
#घोषणा MDP_WD_TIMER_4_CTL2               0x444
#घोषणा MDP_WD_TIMER_4_LOAD_VALUE         0x448

#घोषणा MDP_TICK_COUNT                    16
#घोषणा XO_CLK_RATE                       19200
#घोषणा MS_TICKS_IN_SEC                   1000

#घोषणा CALCULATE_WD_LOAD_VALUE(fps) \
	((uपूर्णांक32_t)((MS_TICKS_IN_SEC * XO_CLK_RATE)/(MDP_TICK_COUNT * fps)))

#घोषणा DCE_SEL                           0x450

अटल व्योम dpu_hw_setup_split_pipe(काष्ठा dpu_hw_mdp *mdp,
		काष्ठा split_pipe_cfg *cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 upper_pipe = 0;
	u32 lower_pipe = 0;

	अगर (!mdp || !cfg)
		वापस;

	c = &mdp->hw;

	अगर (cfg->en) अणु
		अगर (cfg->mode == INTF_MODE_CMD) अणु
			lower_pipe = FLD_SPLIT_DISPLAY_CMD;
			/* पूर्णांकerface controlling sw trigger */
			अगर (cfg->पूर्णांकf == INTF_2)
				lower_pipe |= FLD_INTF_1_SW_TRG_MUX;
			अन्यथा
				lower_pipe |= FLD_INTF_2_SW_TRG_MUX;
			upper_pipe = lower_pipe;
		पूर्ण अन्यथा अणु
			अगर (cfg->पूर्णांकf == INTF_2) अणु
				lower_pipe = FLD_INTF_1_SW_TRG_MUX;
				upper_pipe = FLD_INTF_2_SW_TRG_MUX;
			पूर्ण अन्यथा अणु
				lower_pipe = FLD_INTF_2_SW_TRG_MUX;
				upper_pipe = FLD_INTF_1_SW_TRG_MUX;
			पूर्ण
		पूर्ण
	पूर्ण

	DPU_REG_WRITE(c, SSPP_SPARE, cfg->split_flush_en ? 0x1 : 0x0);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_LOWER_PIPE_CTRL, lower_pipe);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_UPPER_PIPE_CTRL, upper_pipe);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_EN, cfg->en & 0x1);
पूर्ण

अटल bool dpu_hw_setup_clk_क्रमce_ctrl(काष्ठा dpu_hw_mdp *mdp,
		क्रमागत dpu_clk_ctrl_type clk_ctrl, bool enable)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 reg_off, bit_off;
	u32 reg_val, new_val;
	bool clk_क्रमced_on;

	अगर (!mdp)
		वापस false;

	c = &mdp->hw;

	अगर (clk_ctrl <= DPU_CLK_CTRL_NONE || clk_ctrl >= DPU_CLK_CTRL_MAX)
		वापस false;

	reg_off = mdp->caps->clk_ctrls[clk_ctrl].reg_off;
	bit_off = mdp->caps->clk_ctrls[clk_ctrl].bit_off;

	reg_val = DPU_REG_READ(c, reg_off);

	अगर (enable)
		new_val = reg_val | BIT(bit_off);
	अन्यथा
		new_val = reg_val & ~BIT(bit_off);

	DPU_REG_WRITE(c, reg_off, new_val);

	clk_क्रमced_on = !(reg_val & BIT(bit_off));

	वापस clk_क्रमced_on;
पूर्ण


अटल व्योम dpu_hw_get_danger_status(काष्ठा dpu_hw_mdp *mdp,
		काष्ठा dpu_danger_safe_status *status)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 value;

	अगर (!mdp || !status)
		वापस;

	c = &mdp->hw;

	value = DPU_REG_READ(c, DANGER_STATUS);
	status->mdp = (value >> 0) & 0x3;
	status->sspp[SSPP_VIG0] = (value >> 4) & 0x3;
	status->sspp[SSPP_VIG1] = (value >> 6) & 0x3;
	status->sspp[SSPP_VIG2] = (value >> 8) & 0x3;
	status->sspp[SSPP_VIG3] = (value >> 10) & 0x3;
	status->sspp[SSPP_RGB0] = (value >> 12) & 0x3;
	status->sspp[SSPP_RGB1] = (value >> 14) & 0x3;
	status->sspp[SSPP_RGB2] = (value >> 16) & 0x3;
	status->sspp[SSPP_RGB3] = (value >> 18) & 0x3;
	status->sspp[SSPP_DMA0] = (value >> 20) & 0x3;
	status->sspp[SSPP_DMA1] = (value >> 22) & 0x3;
	status->sspp[SSPP_DMA2] = (value >> 28) & 0x3;
	status->sspp[SSPP_DMA3] = (value >> 30) & 0x3;
	status->sspp[SSPP_CURSOR0] = (value >> 24) & 0x3;
	status->sspp[SSPP_CURSOR1] = (value >> 26) & 0x3;
पूर्ण

अटल व्योम dpu_hw_setup_vsync_source(काष्ठा dpu_hw_mdp *mdp,
		काष्ठा dpu_vsync_source_cfg *cfg)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 reg, wd_load_value, wd_ctl, wd_ctl2, i;
	अटल स्थिर u32 pp_offset[PINGPONG_MAX] = अणु0xC, 0x8, 0x4, 0x13, 0x18पूर्ण;

	अगर (!mdp || !cfg || (cfg->pp_count > ARRAY_SIZE(cfg->ppnumber)))
		वापस;

	c = &mdp->hw;
	reg = DPU_REG_READ(c, MDP_VSYNC_SEL);
	क्रम (i = 0; i < cfg->pp_count; i++) अणु
		पूर्णांक pp_idx = cfg->ppnumber[i] - PINGPONG_0;

		अगर (pp_idx >= ARRAY_SIZE(pp_offset))
			जारी;

		reg &= ~(0xf << pp_offset[pp_idx]);
		reg |= (cfg->vsync_source & 0xf) << pp_offset[pp_idx];
	पूर्ण
	DPU_REG_WRITE(c, MDP_VSYNC_SEL, reg);

	अगर (cfg->vsync_source >= DPU_VSYNC_SOURCE_WD_TIMER_4 &&
			cfg->vsync_source <= DPU_VSYNC_SOURCE_WD_TIMER_0) अणु
		चयन (cfg->vsync_source) अणु
		हाल DPU_VSYNC_SOURCE_WD_TIMER_4:
			wd_load_value = MDP_WD_TIMER_4_LOAD_VALUE;
			wd_ctl = MDP_WD_TIMER_4_CTL;
			wd_ctl2 = MDP_WD_TIMER_4_CTL2;
			अवरोध;
		हाल DPU_VSYNC_SOURCE_WD_TIMER_3:
			wd_load_value = MDP_WD_TIMER_3_LOAD_VALUE;
			wd_ctl = MDP_WD_TIMER_3_CTL;
			wd_ctl2 = MDP_WD_TIMER_3_CTL2;
			अवरोध;
		हाल DPU_VSYNC_SOURCE_WD_TIMER_2:
			wd_load_value = MDP_WD_TIMER_2_LOAD_VALUE;
			wd_ctl = MDP_WD_TIMER_2_CTL;
			wd_ctl2 = MDP_WD_TIMER_2_CTL2;
			अवरोध;
		हाल DPU_VSYNC_SOURCE_WD_TIMER_1:
			wd_load_value = MDP_WD_TIMER_1_LOAD_VALUE;
			wd_ctl = MDP_WD_TIMER_1_CTL;
			wd_ctl2 = MDP_WD_TIMER_1_CTL2;
			अवरोध;
		हाल DPU_VSYNC_SOURCE_WD_TIMER_0:
		शेष:
			wd_load_value = MDP_WD_TIMER_0_LOAD_VALUE;
			wd_ctl = MDP_WD_TIMER_0_CTL;
			wd_ctl2 = MDP_WD_TIMER_0_CTL2;
			अवरोध;
		पूर्ण

		DPU_REG_WRITE(c, wd_load_value,
			CALCULATE_WD_LOAD_VALUE(cfg->frame_rate));

		DPU_REG_WRITE(c, wd_ctl, BIT(0)); /* clear समयr */
		reg = DPU_REG_READ(c, wd_ctl2);
		reg |= BIT(8);		/* enable heartbeat समयr */
		reg |= BIT(0);		/* enable WD समयr */
		DPU_REG_WRITE(c, wd_ctl2, reg);

		/* make sure that समयrs are enabled/disabled क्रम vsync state */
		wmb();
	पूर्ण
पूर्ण

अटल व्योम dpu_hw_get_safe_status(काष्ठा dpu_hw_mdp *mdp,
		काष्ठा dpu_danger_safe_status *status)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;
	u32 value;

	अगर (!mdp || !status)
		वापस;

	c = &mdp->hw;

	value = DPU_REG_READ(c, SAFE_STATUS);
	status->mdp = (value >> 0) & 0x1;
	status->sspp[SSPP_VIG0] = (value >> 4) & 0x1;
	status->sspp[SSPP_VIG1] = (value >> 6) & 0x1;
	status->sspp[SSPP_VIG2] = (value >> 8) & 0x1;
	status->sspp[SSPP_VIG3] = (value >> 10) & 0x1;
	status->sspp[SSPP_RGB0] = (value >> 12) & 0x1;
	status->sspp[SSPP_RGB1] = (value >> 14) & 0x1;
	status->sspp[SSPP_RGB2] = (value >> 16) & 0x1;
	status->sspp[SSPP_RGB3] = (value >> 18) & 0x1;
	status->sspp[SSPP_DMA0] = (value >> 20) & 0x1;
	status->sspp[SSPP_DMA1] = (value >> 22) & 0x1;
	status->sspp[SSPP_DMA2] = (value >> 28) & 0x1;
	status->sspp[SSPP_DMA3] = (value >> 30) & 0x1;
	status->sspp[SSPP_CURSOR0] = (value >> 24) & 0x1;
	status->sspp[SSPP_CURSOR1] = (value >> 26) & 0x1;
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_audio_select(काष्ठा dpu_hw_mdp *mdp)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;

	अगर (!mdp)
		वापस;

	c = &mdp->hw;

	DPU_REG_WRITE(c, HDMI_DP_CORE_SELECT, 0x1);
पूर्ण

अटल व्योम _setup_mdp_ops(काष्ठा dpu_hw_mdp_ops *ops,
		अचिन्हित दीर्घ cap)
अणु
	ops->setup_split_pipe = dpu_hw_setup_split_pipe;
	ops->setup_clk_क्रमce_ctrl = dpu_hw_setup_clk_क्रमce_ctrl;
	ops->get_danger_status = dpu_hw_get_danger_status;
	ops->setup_vsync_source = dpu_hw_setup_vsync_source;
	ops->get_safe_status = dpu_hw_get_safe_status;
	ops->पूर्णांकf_audio_select = dpu_hw_पूर्णांकf_audio_select;
पूर्ण

अटल स्थिर काष्ठा dpu_mdp_cfg *_top_offset(क्रमागत dpu_mdp mdp,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	अगर (!m || !addr || !b)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < m->mdp_count; i++) अणु
		अगर (mdp == m->mdp[i].id) अणु
			b->base_off = addr;
			b->blk_off = m->mdp[i].base;
			b->length = m->mdp[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_TOP;
			वापस &m->mdp[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_mdp *dpu_hw_mdptop_init(क्रमागत dpu_mdp idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_mdp *mdp;
	स्थिर काष्ठा dpu_mdp_cfg *cfg;

	अगर (!addr || !m)
		वापस ERR_PTR(-EINVAL);

	mdp = kzalloc(माप(*mdp), GFP_KERNEL);
	अगर (!mdp)
		वापस ERR_PTR(-ENOMEM);

	cfg = _top_offset(idx, m, addr, &mdp->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(mdp);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Assign ops
	 */
	mdp->idx = idx;
	mdp->caps = cfg;
	_setup_mdp_ops(&mdp->ops, mdp->caps->features);

	dpu_hw_blk_init(&mdp->base, DPU_HW_BLK_TOP, idx, &dpu_hw_ops);

	वापस mdp;
पूर्ण

व्योम dpu_hw_mdp_destroy(काष्ठा dpu_hw_mdp *mdp)
अणु
	अगर (mdp)
		dpu_hw_blk_destroy(&mdp->base);
	kमुक्त(mdp);
पूर्ण

