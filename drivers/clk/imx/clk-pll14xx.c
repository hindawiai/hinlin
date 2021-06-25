<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017-2018 NXP.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>

#समावेश "clk.h"

#घोषणा GNRL_CTL	0x0
#घोषणा DIV_CTL		0x4
#घोषणा LOCK_STATUS	BIT(31)
#घोषणा LOCK_SEL_MASK	BIT(29)
#घोषणा CLKE_MASK	BIT(11)
#घोषणा RST_MASK	BIT(9)
#घोषणा BYPASS_MASK	BIT(4)
#घोषणा MDIV_SHIFT	12
#घोषणा MDIV_MASK	GENMASK(21, 12)
#घोषणा PDIV_SHIFT	4
#घोषणा PDIV_MASK	GENMASK(9, 4)
#घोषणा SDIV_SHIFT	0
#घोषणा SDIV_MASK	GENMASK(2, 0)
#घोषणा KDIV_SHIFT	0
#घोषणा KDIV_MASK	GENMASK(15, 0)

#घोषणा LOCK_TIMEOUT_US		10000

काष्ठा clk_pll14xx अणु
	काष्ठा clk_hw			hw;
	व्योम __iomem			*base;
	क्रमागत imx_pll14xx_type		type;
	स्थिर काष्ठा imx_pll14xx_rate_table *rate_table;
	पूर्णांक rate_count;
पूर्ण;

#घोषणा to_clk_pll14xx(_hw) container_of(_hw, काष्ठा clk_pll14xx, hw)

अटल स्थिर काष्ठा imx_pll14xx_rate_table imx_pll1416x_tbl[] = अणु
	PLL_1416X_RATE(1800000000U, 225, 3, 0),
	PLL_1416X_RATE(1600000000U, 200, 3, 0),
	PLL_1416X_RATE(1500000000U, 375, 3, 1),
	PLL_1416X_RATE(1400000000U, 350, 3, 1),
	PLL_1416X_RATE(1200000000U, 300, 3, 1),
	PLL_1416X_RATE(1000000000U, 250, 3, 1),
	PLL_1416X_RATE(800000000U,  200, 3, 1),
	PLL_1416X_RATE(750000000U,  250, 2, 2),
	PLL_1416X_RATE(700000000U,  350, 3, 2),
	PLL_1416X_RATE(600000000U,  300, 3, 2),
पूर्ण;

अटल स्थिर काष्ठा imx_pll14xx_rate_table imx_pll1443x_tbl[] = अणु
	PLL_1443X_RATE(1039500000U, 173, 2, 1, 16384),
	PLL_1443X_RATE(650000000U, 325, 3, 2, 0),
	PLL_1443X_RATE(594000000U, 198, 2, 2, 0),
	PLL_1443X_RATE(519750000U, 173, 2, 2, 16384),
	PLL_1443X_RATE(393216000U, 262, 2, 3, 9437),
	PLL_1443X_RATE(361267200U, 361, 3, 3, 17511),
पूर्ण;

काष्ठा imx_pll14xx_clk imx_1443x_pll = अणु
	.type = PLL_1443X,
	.rate_table = imx_pll1443x_tbl,
	.rate_count = ARRAY_SIZE(imx_pll1443x_tbl),
पूर्ण;
EXPORT_SYMBOL_GPL(imx_1443x_pll);

काष्ठा imx_pll14xx_clk imx_1443x_dram_pll = अणु
	.type = PLL_1443X,
	.rate_table = imx_pll1443x_tbl,
	.rate_count = ARRAY_SIZE(imx_pll1443x_tbl),
	.flags = CLK_GET_RATE_NOCACHE,
पूर्ण;
EXPORT_SYMBOL_GPL(imx_1443x_dram_pll);

काष्ठा imx_pll14xx_clk imx_1416x_pll = अणु
	.type = PLL_1416X,
	.rate_table = imx_pll1416x_tbl,
	.rate_count = ARRAY_SIZE(imx_pll1416x_tbl),
पूर्ण;
EXPORT_SYMBOL_GPL(imx_1416x_pll);

अटल स्थिर काष्ठा imx_pll14xx_rate_table *imx_get_pll_settings(
		काष्ठा clk_pll14xx *pll, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा imx_pll14xx_rate_table *rate_table = pll->rate_table;
	पूर्णांक i;

	क्रम (i = 0; i < pll->rate_count; i++)
		अगर (rate == rate_table[i].rate)
			वापस &rate_table[i];

	वापस शून्य;
पूर्ण

अटल दीर्घ clk_pll14xx_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	स्थिर काष्ठा imx_pll14xx_rate_table *rate_table = pll->rate_table;
	पूर्णांक i;

	/* Assumming rate_table is in descending order */
	क्रम (i = 0; i < pll->rate_count; i++)
		अगर (rate >= rate_table[i].rate)
			वापस rate_table[i].rate;

	/* वापस minimum supported value */
	वापस rate_table[i - 1].rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_pll1416x_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 mभाग, pभाग, sभाग, pll_भाग;
	u64 fvco = parent_rate;

	pll_भाग = पढ़ोl_relaxed(pll->base + 4);
	mभाग = (pll_भाग & MDIV_MASK) >> MDIV_SHIFT;
	pभाग = (pll_भाग & PDIV_MASK) >> PDIV_SHIFT;
	sभाग = (pll_भाग & SDIV_MASK) >> SDIV_SHIFT;

	fvco *= mभाग;
	करो_भाग(fvco, pभाग << sभाग);

	वापस fvco;
पूर्ण

अटल अचिन्हित दीर्घ clk_pll1443x_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 mभाग, pभाग, sभाग, pll_भाग_ctl0, pll_भाग_ctl1;
	लघु पूर्णांक kभाग;
	u64 fvco = parent_rate;

	pll_भाग_ctl0 = पढ़ोl_relaxed(pll->base + 4);
	pll_भाग_ctl1 = पढ़ोl_relaxed(pll->base + 8);
	mभाग = (pll_भाग_ctl0 & MDIV_MASK) >> MDIV_SHIFT;
	pभाग = (pll_भाग_ctl0 & PDIV_MASK) >> PDIV_SHIFT;
	sभाग = (pll_भाग_ctl0 & SDIV_MASK) >> SDIV_SHIFT;
	kभाग = pll_भाग_ctl1 & KDIV_MASK;

	/* fvco = (m * 65536 + k) * Fin / (p * 65536) */
	fvco *= (mभाग * 65536 + kभाग);
	pभाग *= 65536;

	करो_भाग(fvco, pभाग << sभाग);

	वापस fvco;
पूर्ण

अटल अंतरभूत bool clk_pll14xx_mp_change(स्थिर काष्ठा imx_pll14xx_rate_table *rate,
					  u32 pll_भाग)
अणु
	u32 old_mभाग, old_pभाग;

	old_mभाग = (pll_भाग & MDIV_MASK) >> MDIV_SHIFT;
	old_pभाग = (pll_भाग & PDIV_MASK) >> PDIV_SHIFT;

	वापस rate->mभाग != old_mभाग || rate->pभाग != old_pभाग;
पूर्ण

अटल पूर्णांक clk_pll14xx_रुको_lock(काष्ठा clk_pll14xx *pll)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(pll->base, val, val & LOCK_STATUS, 0,
			LOCK_TIMEOUT_US);
पूर्ण

अटल पूर्णांक clk_pll1416x_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				 अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	स्थिर काष्ठा imx_pll14xx_rate_table *rate;
	u32 पंचांगp, भाग_val;
	पूर्णांक ret;

	rate = imx_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
		       drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(pll->base + 4);

	अगर (!clk_pll14xx_mp_change(rate, पंचांगp)) अणु
		पंचांगp &= ~(SDIV_MASK) << SDIV_SHIFT;
		पंचांगp |= rate->sभाग << SDIV_SHIFT;
		ग_लिखोl_relaxed(पंचांगp, pll->base + 4);

		वापस 0;
	पूर्ण

	/* Bypass घड़ी and set lock to pll output lock */
	पंचांगp = पढ़ोl_relaxed(pll->base);
	पंचांगp |= LOCK_SEL_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	/* Enable RST */
	पंचांगp &= ~RST_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	/* Enable BYPASS */
	पंचांगp |= BYPASS_MASK;
	ग_लिखोl(पंचांगp, pll->base);

	भाग_val = (rate->mभाग << MDIV_SHIFT) | (rate->pभाग << PDIV_SHIFT) |
		(rate->sभाग << SDIV_SHIFT);
	ग_लिखोl_relaxed(भाग_val, pll->base + 0x4);

	/*
	 * According to SPEC, t3 - t2 need to be greater than
	 * 1us and 1/FREF, respectively.
	 * FREF is FIN / Preभाग, the preभाग is [1, 63], so choose
	 * 3us.
	 */
	udelay(3);

	/* Disable RST */
	पंचांगp |= RST_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	/* Wait Lock */
	ret = clk_pll14xx_रुको_lock(pll);
	अगर (ret)
		वापस ret;

	/* Bypass */
	पंचांगp &= ~BYPASS_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pll1443x_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				 अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	स्थिर काष्ठा imx_pll14xx_rate_table *rate;
	u32 पंचांगp, भाग_val;
	पूर्णांक ret;

	rate = imx_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(pll->base + 4);

	अगर (!clk_pll14xx_mp_change(rate, पंचांगp)) अणु
		पंचांगp &= ~(SDIV_MASK) << SDIV_SHIFT;
		पंचांगp |= rate->sभाग << SDIV_SHIFT;
		ग_लिखोl_relaxed(पंचांगp, pll->base + 4);

		पंचांगp = rate->kभाग << KDIV_SHIFT;
		ग_लिखोl_relaxed(पंचांगp, pll->base + 8);

		वापस 0;
	पूर्ण

	/* Enable RST */
	पंचांगp = पढ़ोl_relaxed(pll->base);
	पंचांगp &= ~RST_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	/* Enable BYPASS */
	पंचांगp |= BYPASS_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	भाग_val = (rate->mभाग << MDIV_SHIFT) | (rate->pभाग << PDIV_SHIFT) |
		(rate->sभाग << SDIV_SHIFT);
	ग_लिखोl_relaxed(भाग_val, pll->base + 0x4);
	ग_लिखोl_relaxed(rate->kभाग << KDIV_SHIFT, pll->base + 0x8);

	/*
	 * According to SPEC, t3 - t2 need to be greater than
	 * 1us and 1/FREF, respectively.
	 * FREF is FIN / Preभाग, the preभाग is [1, 63], so choose
	 * 3us.
	 */
	udelay(3);

	/* Disable RST */
	पंचांगp |= RST_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	/* Wait Lock*/
	ret = clk_pll14xx_रुको_lock(pll);
	अगर (ret)
		वापस ret;

	/* Bypass */
	पंचांगp &= ~BYPASS_MASK;
	ग_लिखोl_relaxed(पंचांगp, pll->base);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pll14xx_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 val;
	पूर्णांक ret;

	/*
	 * RESETB = 1 from 0, PLL starts its normal
	 * operation after lock समय
	 */
	val = पढ़ोl_relaxed(pll->base + GNRL_CTL);
	अगर (val & RST_MASK)
		वापस 0;
	val |= BYPASS_MASK;
	ग_लिखोl_relaxed(val, pll->base + GNRL_CTL);
	val |= RST_MASK;
	ग_लिखोl_relaxed(val, pll->base + GNRL_CTL);

	ret = clk_pll14xx_रुको_lock(pll);
	अगर (ret)
		वापस ret;

	val &= ~BYPASS_MASK;
	ग_लिखोl_relaxed(val, pll->base + GNRL_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pll14xx_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + GNRL_CTL);

	वापस (val & RST_MASK) ? 1 : 0;
पूर्ण

अटल व्योम clk_pll14xx_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 val;

	/*
	 * Set RST to 0, घातer करोwn mode is enabled and
	 * every digital block is reset
	 */
	val = पढ़ोl_relaxed(pll->base + GNRL_CTL);
	val &= ~RST_MASK;
	ग_लिखोl_relaxed(val, pll->base + GNRL_CTL);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll1416x_ops = अणु
	.prepare	= clk_pll14xx_prepare,
	.unprepare	= clk_pll14xx_unprepare,
	.is_prepared	= clk_pll14xx_is_prepared,
	.recalc_rate	= clk_pll1416x_recalc_rate,
	.round_rate	= clk_pll14xx_round_rate,
	.set_rate	= clk_pll1416x_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_pll1416x_min_ops = अणु
	.recalc_rate	= clk_pll1416x_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_pll1443x_ops = अणु
	.prepare	= clk_pll14xx_prepare,
	.unprepare	= clk_pll14xx_unprepare,
	.is_prepared	= clk_pll14xx_is_prepared,
	.recalc_rate	= clk_pll1443x_recalc_rate,
	.round_rate	= clk_pll14xx_round_rate,
	.set_rate	= clk_pll1443x_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_dev_clk_hw_pll14xx(काष्ठा device *dev, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name, व्योम __iomem *base,
				स्थिर काष्ठा imx_pll14xx_clk *pll_clk)
अणु
	काष्ठा clk_pll14xx *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;
	u32 val;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = pll_clk->flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	चयन (pll_clk->type) अणु
	हाल PLL_1416X:
		अगर (!pll_clk->rate_table)
			init.ops = &clk_pll1416x_min_ops;
		अन्यथा
			init.ops = &clk_pll1416x_ops;
		अवरोध;
	हाल PLL_1443X:
		init.ops = &clk_pll1443x_ops;
		अवरोध;
	शेष:
		pr_err("%s: Unknown pll type for pll clk %s\n",
		       __func__, name);
		kमुक्त(pll);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pll->base = base;
	pll->hw.init = &init;
	pll->type = pll_clk->type;
	pll->rate_table = pll_clk->rate_table;
	pll->rate_count = pll_clk->rate_count;

	val = पढ़ोl_relaxed(pll->base + GNRL_CTL);
	val &= ~BYPASS_MASK;
	ग_लिखोl_relaxed(val, pll->base + GNRL_CTL);

	hw = &pll->hw;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		pr_err("%s: failed to register pll %s %d\n",
			__func__, name, ret);
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(imx_dev_clk_hw_pll14xx);
