<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>

#समावेश "dsi_phy.h"
#समावेश "dsi.xml.h"

/*
 * DSI PLL 28nm (8960/A family) - घड़ी diagram (eg: DSI1):
 *
 *
 *                        +------+
 *  dsi1vco_clk ----o-----| DIV1 |---dsi1pllbit (not exposed as घड़ी)
 *  F * byte_clk    |     +------+
 *                  | bit घड़ी भागider (F / 8)
 *                  |
 *                  |     +------+
 *                  o-----| DIV2 |---dsi0pllbyte---o---> To byte RCG
 *                  |     +------+                 | (sets parent rate)
 *                  | byte घड़ी भागider (F)       |
 *                  |                              |
 *                  |                              o---> To esc RCG
 *                  |                                (करोesn't set parent rate)
 *                  |
 *                  |     +------+
 *                  o-----| DIV3 |----dsi0pll------o---> To dsi RCG
 *                        +------+                 | (sets parent rate)
 *                  dsi घड़ी भागider (F * magic)  |
 *                                                 |
 *                                                 o---> To pixel rcg
 *                                                  (करोesn't set parent rate)
 */

#घोषणा POLL_MAX_READS		8000
#घोषणा POLL_TIMEOUT_US		1

#घोषणा VCO_REF_CLK_RATE	27000000
#घोषणा VCO_MIN_RATE		600000000
#घोषणा VCO_MAX_RATE		1200000000

#घोषणा VCO_PREF_DIV_RATIO	27

काष्ठा pll_28nm_cached_state अणु
	अचिन्हित दीर्घ vco_rate;
	u8 postभाग3;
	u8 postभाग2;
	u8 postभाग1;
पूर्ण;

काष्ठा clk_byteभाग अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
पूर्ण;

काष्ठा dsi_pll_28nm अणु
	काष्ठा clk_hw clk_hw;

	काष्ठा msm_dsi_phy *phy;

	काष्ठा pll_28nm_cached_state cached_state;
पूर्ण;

#घोषणा to_pll_28nm(x)	container_of(x, काष्ठा dsi_pll_28nm, clk_hw)

अटल bool pll_28nm_poll_क्रम_पढ़ोy(काष्ठा dsi_pll_28nm *pll_28nm,
				    पूर्णांक nb_tries, पूर्णांक समयout_us)
अणु
	bool pll_locked = false;
	u32 val;

	जबतक (nb_tries--) अणु
		val = dsi_phy_पढ़ो(pll_28nm->phy->pll_base + REG_DSI_28nm_8960_PHY_PLL_RDY);
		pll_locked = !!(val & DSI_28nm_8960_PHY_PLL_RDY_PLL_RDY);

		अगर (pll_locked)
			अवरोध;

		udelay(समयout_us);
	पूर्ण
	DBG("DSI PLL is %slocked", pll_locked ? "" : "*not* ");

	वापस pll_locked;
पूर्ण

/*
 * Clock Callbacks
 */
अटल पूर्णांक dsi_pll_28nm_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	u32 val, temp, fb_भागider;

	DBG("rate=%lu, parent's=%lu", rate, parent_rate);

	temp = rate / 10;
	val = VCO_REF_CLK_RATE / 10;
	fb_भागider = (temp * VCO_PREF_DIV_RATIO) / val;
	fb_भागider = fb_भागider / 2 - 1;
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_1,
			fb_भागider & 0xff);

	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_2);

	val |= (fb_भागider >> 8) & 0x07;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_2,
			val);

	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_3);

	val |= (VCO_PREF_DIV_RATIO - 1) & 0x3f;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_3,
			val);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_6,
			0xf);

	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8);
	val |= 0x7 << 4;
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8,
			val);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	वापस pll_28nm_poll_क्रम_पढ़ोy(pll_28nm, POLL_MAX_READS,
					POLL_TIMEOUT_US);
पूर्ण

अटल अचिन्हित दीर्घ dsi_pll_28nm_clk_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	अचिन्हित दीर्घ vco_rate;
	u32 status, fb_भागider, temp, ref_भागider;

	VERB("parent_rate=%lu", parent_rate);

	status = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_0);

	अगर (status & DSI_28nm_8960_PHY_PLL_CTRL_0_ENABLE) अणु
		fb_भागider = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_1);
		fb_भागider &= 0xff;
		temp = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_2) & 0x07;
		fb_भागider = (temp << 8) | fb_भागider;
		fb_भागider += 1;

		ref_भागider = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_3);
		ref_भागider &= 0x3f;
		ref_भागider += 1;

		/* multiply by 2 */
		vco_rate = (parent_rate / ref_भागider) * fb_भागider * 2;
	पूर्ण अन्यथा अणु
		vco_rate = 0;
	पूर्ण

	DBG("returning vco rate = %lu", vco_rate);

	वापस vco_rate;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_vco_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	bool locked;
	अचिन्हित पूर्णांक bit_भाग, byte_भाग;
	पूर्णांक max_पढ़ोs = 1000, समयout_us = 100;
	u32 val;

	DBG("id=%d", pll_28nm->phy->id);

	अगर (unlikely(pll_28nm->phy->pll_on))
		वापस 0;

	/*
	 * beक्रमe enabling the PLL, configure the bit घड़ी भागider since we
	 * करोn't expose it as a घड़ी to the outside world
	 * 1: पढ़ो back the byte घड़ी भागider that should alपढ़ोy be set
	 * 2: भागide by 8 to get bit घड़ी भागider
	 * 3: ग_लिखो it to POSTDIV1
	 */
	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_9);
	byte_भाग = val + 1;
	bit_भाग = byte_भाग / 8;

	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8);
	val &= ~0xf;
	val |= (bit_भाग - 1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8, val);

	/* enable the PLL */
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_0,
			DSI_28nm_8960_PHY_PLL_CTRL_0_ENABLE);

	locked = pll_28nm_poll_क्रम_पढ़ोy(pll_28nm, max_पढ़ोs, समयout_us);

	अगर (unlikely(!locked)) अणु
		DRM_DEV_ERROR(dev, "DSI PLL lock failed\n");
		वापस -EINVAL;
	पूर्ण

	DBG("DSI PLL lock success");
	pll_28nm->phy->pll_on = true;

	वापस 0;
पूर्ण

अटल व्योम dsi_pll_28nm_vco_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	DBG("id=%d", pll_28nm->phy->id);

	अगर (unlikely(!pll_28nm->phy->pll_on))
		वापस;

	dsi_phy_ग_लिखो(pll_28nm->phy->pll_base + REG_DSI_28nm_8960_PHY_PLL_CTRL_0, 0x00);

	pll_28nm->phy->pll_on = false;
पूर्ण

अटल दीर्घ dsi_pll_28nm_clk_round_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	अगर      (rate < pll_28nm->phy->cfg->min_pll_rate)
		वापस  pll_28nm->phy->cfg->min_pll_rate;
	अन्यथा अगर (rate > pll_28nm->phy->cfg->max_pll_rate)
		वापस  pll_28nm->phy->cfg->max_pll_rate;
	अन्यथा
		वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_28nm_vco = अणु
	.round_rate = dsi_pll_28nm_clk_round_rate,
	.set_rate = dsi_pll_28nm_clk_set_rate,
	.recalc_rate = dsi_pll_28nm_clk_recalc_rate,
	.prepare = dsi_pll_28nm_vco_prepare,
	.unprepare = dsi_pll_28nm_vco_unprepare,
	.is_enabled = dsi_pll_28nm_clk_is_enabled,
पूर्ण;

/*
 * Custom byte घड़ी भागier clk_ops
 *
 * This घड़ी is the entry poपूर्णांक to configuring the PLL. The user (dsi host)
 * will set this घड़ी's rate to the desired byte घड़ी rate. The VCO lock
 * frequency is a multiple of the byte घड़ी rate. The multiplication factor
 * (shown as F in the diagram above) is a function of the byte घड़ी rate.
 *
 * This custom भागider घड़ी ensures that its parent (VCO) is set to the
 * desired rate, and that the byte घड़ी postभागider (POSTDIV2) is configured
 * accordingly
 */
#घोषणा to_clk_byteभाग(_hw) container_of(_hw, काष्ठा clk_byteभाग, hw)

अटल अचिन्हित दीर्घ clk_byteभाग_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_byteभाग *byteभाग = to_clk_byteभाग(hw);
	अचिन्हित पूर्णांक भाग;

	भाग = dsi_phy_पढ़ो(byteभाग->reg) & 0xff;

	वापस parent_rate / (भाग + 1);
पूर्ण

/* find multiplication factor(wrt byte घड़ी) at which the VCO should be set */
अटल अचिन्हित पूर्णांक get_vco_mul_factor(अचिन्हित दीर्घ byte_clk_rate)
अणु
	अचिन्हित दीर्घ bit_mhz;

	/* convert to bit घड़ी in Mhz */
	bit_mhz = (byte_clk_rate * 8) / 1000000;

	अगर (bit_mhz < 125)
		वापस 64;
	अन्यथा अगर (bit_mhz < 250)
		वापस 32;
	अन्यथा अगर (bit_mhz < 600)
		वापस 16;
	अन्यथा
		वापस 8;
पूर्ण

अटल दीर्घ clk_byteभाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ best_parent;
	अचिन्हित पूर्णांक factor;

	factor = get_vco_mul_factor(rate);

	best_parent = rate * factor;
	*prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);

	वापस *prate / factor;
पूर्ण

अटल पूर्णांक clk_byteभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_byteभाग *byteभाग = to_clk_byteभाग(hw);
	u32 val;
	अचिन्हित पूर्णांक factor;

	factor = get_vco_mul_factor(rate);

	val = dsi_phy_पढ़ो(byteभाग->reg);
	val |= (factor - 1) & 0xff;
	dsi_phy_ग_लिखो(byteभाग->reg, val);

	वापस 0;
पूर्ण

/* Our special byte घड़ी भागider ops */
अटल स्थिर काष्ठा clk_ops clk_byteभाग_ops = अणु
	.round_rate = clk_byteभाग_round_rate,
	.set_rate = clk_byteभाग_set_rate,
	.recalc_rate = clk_byteभाग_recalc_rate,
पूर्ण;

/*
 * PLL Callbacks
 */
अटल व्योम dsi_28nm_pll_save_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(phy->vco_hw);
	काष्ठा pll_28nm_cached_state *cached_state = &pll_28nm->cached_state;
	व्योम __iomem *base = pll_28nm->phy->pll_base;

	cached_state->postभाग3 =
			dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_10);
	cached_state->postभाग2 =
			dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_9);
	cached_state->postभाग1 =
			dsi_phy_पढ़ो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8);

	cached_state->vco_rate = clk_hw_get_rate(phy->vco_hw);
पूर्ण

अटल पूर्णांक dsi_28nm_pll_restore_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(phy->vco_hw);
	काष्ठा pll_28nm_cached_state *cached_state = &pll_28nm->cached_state;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	पूर्णांक ret;

	ret = dsi_pll_28nm_clk_set_rate(phy->vco_hw,
					cached_state->vco_rate, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pll_28nm->phy->pdev->dev,
			"restore vco rate failed. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_10,
			cached_state->postभाग3);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_9,
			cached_state->postभाग2);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_PLL_CTRL_8,
			cached_state->postभाग1);

	वापस 0;
पूर्ण

अटल पूर्णांक pll_28nm_रेजिस्टर(काष्ठा dsi_pll_28nm *pll_28nm, काष्ठा clk_hw **provided_घड़ीs)
अणु
	अक्षर *clk_name, *parent_name, *vco_name;
	काष्ठा clk_init_data vco_init = अणु
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.flags = CLK_IGNORE_UNUSED,
		.ops = &clk_ops_dsi_pll_28nm_vco,
	पूर्ण;
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	काष्ठा clk_hw *hw;
	काष्ठा clk_byteभाग *byteभाग;
	काष्ठा clk_init_data byteभाग_init = अणु पूर्ण;
	पूर्णांक ret;

	DBG("%d", pll_28nm->phy->id);

	byteभाग = devm_kzalloc(dev, माप(*byteभाग), GFP_KERNEL);
	अगर (!byteभाग)
		वापस -ENOMEM;

	vco_name = devm_kzalloc(dev, 32, GFP_KERNEL);
	अगर (!vco_name)
		वापस -ENOMEM;

	parent_name = devm_kzalloc(dev, 32, GFP_KERNEL);
	अगर (!parent_name)
		वापस -ENOMEM;

	clk_name = devm_kzalloc(dev, 32, GFP_KERNEL);
	अगर (!clk_name)
		वापस -ENOMEM;

	snम_लिखो(vco_name, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	vco_init.name = vco_name;

	pll_28nm->clk_hw.init = &vco_init;

	ret = devm_clk_hw_रेजिस्टर(dev, &pll_28nm->clk_hw);
	अगर (ret)
		वापस ret;

	/* prepare and रेजिस्टर byteभाग */
	byteभाग->hw.init = &byteभाग_init;
	byteभाग->reg = pll_28nm->phy->pll_base + REG_DSI_28nm_8960_PHY_PLL_CTRL_9;

	snम_लिखो(parent_name, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	snम_लिखो(clk_name, 32, "dsi%dpllbyte", pll_28nm->phy->id);

	byteभाग_init.name = clk_name;
	byteभाग_init.ops = &clk_byteभाग_ops;
	byteभाग_init.flags = CLK_SET_RATE_PARENT;
	byteभाग_init.parent_names = (स्थिर अक्षर * स्थिर *) &parent_name;
	byteभाग_init.num_parents = 1;

	/* DIV2 */
	ret = devm_clk_hw_रेजिस्टर(dev, &byteभाग->hw);
	अगर (ret)
		वापस ret;
	provided_घड़ीs[DSI_BYTE_PLL_CLK] = &byteभाग->hw;

	snम_लिखो(clk_name, 32, "dsi%dpll", pll_28nm->phy->id);
	/* DIV3 */
	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name,
				parent_name, 0, pll_28nm->phy->pll_base +
				REG_DSI_28nm_8960_PHY_PLL_CTRL_10,
				0, 8, 0, शून्य);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	provided_घड़ीs[DSI_PIXEL_PLL_CLK] = hw;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_8960_init(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा platक्रमm_device *pdev = phy->pdev;
	काष्ठा dsi_pll_28nm *pll_28nm;
	पूर्णांक ret;

	अगर (!pdev)
		वापस -ENODEV;

	pll_28nm = devm_kzalloc(&pdev->dev, माप(*pll_28nm), GFP_KERNEL);
	अगर (!pll_28nm)
		वापस -ENOMEM;

	pll_28nm->phy = phy;

	ret = pll_28nm_रेजिस्टर(pll_28nm, phy->provided_घड़ीs->hws);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	phy->vco_hw = &pll_28nm->clk_hw;

	वापस 0;
पूर्ण

अटल व्योम dsi_28nm_dphy_set_timing(काष्ठा msm_dsi_phy *phy,
		काष्ठा msm_dsi_dphy_timing *timing)
अणु
	व्योम __iomem *base = phy->base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_0,
		DSI_28nm_8960_PHY_TIMING_CTRL_0_CLK_ZERO(timing->clk_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_1,
		DSI_28nm_8960_PHY_TIMING_CTRL_1_CLK_TRAIL(timing->clk_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_2,
		DSI_28nm_8960_PHY_TIMING_CTRL_2_CLK_PREPARE(timing->clk_prepare));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_3, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_4,
		DSI_28nm_8960_PHY_TIMING_CTRL_4_HS_EXIT(timing->hs_निकास));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_5,
		DSI_28nm_8960_PHY_TIMING_CTRL_5_HS_ZERO(timing->hs_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_6,
		DSI_28nm_8960_PHY_TIMING_CTRL_6_HS_PREPARE(timing->hs_prepare));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_7,
		DSI_28nm_8960_PHY_TIMING_CTRL_7_HS_TRAIL(timing->hs_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_8,
		DSI_28nm_8960_PHY_TIMING_CTRL_8_HS_RQST(timing->hs_rqst));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_9,
		DSI_28nm_8960_PHY_TIMING_CTRL_9_TA_GO(timing->ta_go) |
		DSI_28nm_8960_PHY_TIMING_CTRL_9_TA_SURE(timing->ta_sure));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_10,
		DSI_28nm_8960_PHY_TIMING_CTRL_10_TA_GET(timing->ta_get));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_TIMING_CTRL_11,
		DSI_28nm_8960_PHY_TIMING_CTRL_11_TRIG3_CMD(0));
पूर्ण

अटल व्योम dsi_28nm_phy_regulator_init(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->reg_base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_0, 0x3);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_1, 1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_2, 1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_3, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_4,
		0x100);
पूर्ण

अटल व्योम dsi_28nm_phy_regulator_ctrl(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->reg_base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_0, 0x3);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_1, 0xa);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_2, 0x4);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_3, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CTRL_4, 0x20);
पूर्ण

अटल व्योम dsi_28nm_phy_calibration(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->reg_base;
	u32 status;
	पूर्णांक i = 5000;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_REGULATOR_CAL_PWR_CFG,
			0x3);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_SW_CFG_2, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_CFG_1, 0x5a);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_CFG_3, 0x10);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_CFG_4, 0x1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_CFG_0, 0x1);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_TRIGGER, 0x1);
	usleep_range(5000, 6000);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_MISC_CAL_HW_TRIGGER, 0x0);

	करो अणु
		status = dsi_phy_पढ़ो(base +
				REG_DSI_28nm_8960_PHY_MISC_CAL_STATUS);

		अगर (!(status & DSI_28nm_8960_PHY_MISC_CAL_STATUS_CAL_BUSY))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--i > 0);
पूर्ण

अटल व्योम dsi_28nm_phy_lane_config(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->base;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_CFG_0(i), 0x80);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_CFG_1(i), 0x45);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_CFG_2(i), 0x00);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_TEST_DATAPATH(i),
			0x00);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_TEST_STR_0(i),
			0x01);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LN_TEST_STR_1(i),
			0x66);
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_CFG_0, 0x40);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_CFG_1, 0x67);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_CFG_2, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_TEST_DATAPATH, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_TEST_STR0, 0x1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LNCK_TEST_STR1, 0x88);
पूर्ण

अटल पूर्णांक dsi_28nm_phy_enable(काष्ठा msm_dsi_phy *phy,
				काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	काष्ठा msm_dsi_dphy_timing *timing = &phy->timing;
	व्योम __iomem *base = phy->base;

	DBG("");

	अगर (msm_dsi_dphy_timing_calc(timing, clk_req)) अणु
		DRM_DEV_ERROR(&phy->pdev->dev,
			"%s: D-PHY timing calculation failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dsi_28nm_phy_regulator_init(phy);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_LDO_CTRL, 0x04);

	/* strength control */
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_STRENGTH_0, 0xff);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_STRENGTH_1, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_STRENGTH_2, 0x06);

	/* phy ctrl */
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_CTRL_0, 0x5f);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_CTRL_1, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_CTRL_2, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_CTRL_3, 0x10);

	dsi_28nm_phy_regulator_ctrl(phy);

	dsi_28nm_phy_calibration(phy);

	dsi_28nm_phy_lane_config(phy);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_BIST_CTRL_4, 0x0f);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_BIST_CTRL_1, 0x03);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_BIST_CTRL_0, 0x03);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_8960_PHY_BIST_CTRL_4, 0x0);

	dsi_28nm_dphy_set_timing(phy, timing);

	वापस 0;
पूर्ण

अटल व्योम dsi_28nm_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	dsi_phy_ग_लिखो(phy->base + REG_DSI_28nm_8960_PHY_CTRL_0, 0x0);

	/*
	 * Wait क्रम the रेजिस्टरs ग_लिखोs to complete in order to
	 * ensure that the phy is completely disabled
	 */
	wmb();
पूर्ण

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_8960_cfgs = अणु
	.has_phy_regulator = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_28nm_phy_enable,
		.disable = dsi_28nm_phy_disable,
		.pll_init = dsi_pll_28nm_8960_init,
		.save_pll_state = dsi_28nm_pll_save_state,
		.restore_pll_state = dsi_28nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0x4700300, 0x5800300 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;
