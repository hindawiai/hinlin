<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>

#समावेश "mdp4_kms.h"

काष्ठा mdp4_lvds_pll अणु
	काष्ठा clk_hw pll_hw;
	काष्ठा drm_device *dev;
	अचिन्हित दीर्घ pixclk;
पूर्ण;
#घोषणा to_mdp4_lvds_pll(x) container_of(x, काष्ठा mdp4_lvds_pll, pll_hw)

अटल काष्ठा mdp4_kms *get_kms(काष्ठा mdp4_lvds_pll *lvds_pll)
अणु
	काष्ठा msm_drm_निजी *priv = lvds_pll->dev->dev_निजी;
	वापस to_mdp4_kms(to_mdp_kms(priv->kms));
पूर्ण

काष्ठा pll_rate अणु
	अचिन्हित दीर्घ rate;
	काष्ठा अणु
		uपूर्णांक32_t val;
		uपूर्णांक32_t reg;
	पूर्ण conf[32];
पूर्ण;

/* NOTE: keep sorted highest freq to lowest: */
अटल स्थिर काष्ठा pll_rate freqtbl[] = अणु
	अणु 72000000, अणु
		अणु 0x8f, REG_MDP4_LVDS_PHY_PLL_CTRL_1 पूर्ण,
		अणु 0x30, REG_MDP4_LVDS_PHY_PLL_CTRL_2 पूर्ण,
		अणु 0xc6, REG_MDP4_LVDS_PHY_PLL_CTRL_3 पूर्ण,
		अणु 0x10, REG_MDP4_LVDS_PHY_PLL_CTRL_5 पूर्ण,
		अणु 0x07, REG_MDP4_LVDS_PHY_PLL_CTRL_6 पूर्ण,
		अणु 0x62, REG_MDP4_LVDS_PHY_PLL_CTRL_7 पूर्ण,
		अणु 0x41, REG_MDP4_LVDS_PHY_PLL_CTRL_8 पूर्ण,
		अणु 0x0d, REG_MDP4_LVDS_PHY_PLL_CTRL_9 पूर्ण,
		अणु 0, 0 पूर्ण पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_rate *find_rate(अचिन्हित दीर्घ rate)
अणु
	पूर्णांक i;
	क्रम (i = 1; i < ARRAY_SIZE(freqtbl); i++)
		अगर (rate > freqtbl[i].rate)
			वापस &freqtbl[i-1];
	वापस &freqtbl[i-1];
पूर्ण

अटल पूर्णांक mpd4_lvds_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mdp4_lvds_pll *lvds_pll = to_mdp4_lvds_pll(hw);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(lvds_pll);
	स्थिर काष्ठा pll_rate *pll_rate = find_rate(lvds_pll->pixclk);
	पूर्णांक i;

	DBG("pixclk=%lu (%lu)", lvds_pll->pixclk, pll_rate->rate);

	अगर (WARN_ON(!pll_rate))
		वापस -EINVAL;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_PHY_RESET, 0x33);

	क्रम (i = 0; pll_rate->conf[i].reg; i++)
		mdp4_ग_लिखो(mdp4_kms, pll_rate->conf[i].reg, pll_rate->conf[i].val);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_PLL_CTRL_0, 0x01);

	/* Wait until LVDS PLL is locked and पढ़ोy */
	जबतक (!mdp4_पढ़ो(mdp4_kms, REG_MDP4_LVDS_PHY_PLL_LOCKED))
		cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम mpd4_lvds_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mdp4_lvds_pll *lvds_pll = to_mdp4_lvds_pll(hw);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(lvds_pll);

	DBG("");

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_CFG0, 0x0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_PLL_CTRL_0, 0x0);
पूर्ण

अटल अचिन्हित दीर्घ mpd4_lvds_pll_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mdp4_lvds_pll *lvds_pll = to_mdp4_lvds_pll(hw);
	वापस lvds_pll->pixclk;
पूर्ण

अटल दीर्घ mpd4_lvds_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा pll_rate *pll_rate = find_rate(rate);
	वापस pll_rate->rate;
पूर्ण

अटल पूर्णांक mpd4_lvds_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mdp4_lvds_pll *lvds_pll = to_mdp4_lvds_pll(hw);
	lvds_pll->pixclk = rate;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा clk_ops mpd4_lvds_pll_ops = अणु
	.enable = mpd4_lvds_pll_enable,
	.disable = mpd4_lvds_pll_disable,
	.recalc_rate = mpd4_lvds_pll_recalc_rate,
	.round_rate = mpd4_lvds_pll_round_rate,
	.set_rate = mpd4_lvds_pll_set_rate,
पूर्ण;

अटल स्थिर अक्षर *mpd4_lvds_pll_parents[] = अणु
	"pxo",
पूर्ण;

अटल काष्ठा clk_init_data pll_init = अणु
	.name = "mpd4_lvds_pll",
	.ops = &mpd4_lvds_pll_ops,
	.parent_names = mpd4_lvds_pll_parents,
	.num_parents = ARRAY_SIZE(mpd4_lvds_pll_parents),
पूर्ण;

काष्ठा clk *mpd4_lvds_pll_init(काष्ठा drm_device *dev)
अणु
	काष्ठा mdp4_lvds_pll *lvds_pll;
	काष्ठा clk *clk;
	पूर्णांक ret;

	lvds_pll = devm_kzalloc(dev->dev, माप(*lvds_pll), GFP_KERNEL);
	अगर (!lvds_pll) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	lvds_pll->dev = dev;

	lvds_pll->pll_hw.init = &pll_init;
	clk = devm_clk_रेजिस्टर(dev->dev, &lvds_pll->pll_hw);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ fail;
	पूर्ण

	वापस clk;

fail:
	वापस ERR_PTR(ret);
पूर्ण
