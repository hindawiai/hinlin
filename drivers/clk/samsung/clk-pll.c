<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 *
 * This file contains the utility functions to रेजिस्टर the pll घड़ीs.
*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश "clk.h"
#समावेश "clk-pll.h"

#घोषणा PLL_TIMEOUT_US		20000U
#घोषणा PLL_TIMEOUT_LOOPS	1000000U

काष्ठा samsung_clk_pll अणु
	काष्ठा clk_hw		hw;
	व्योम __iomem		*lock_reg;
	व्योम __iomem		*con_reg;
	/* PLL enable control bit offset in @con_reg रेजिस्टर */
	अचिन्हित लघु		enable_offs;
	/* PLL lock status bit offset in @con_reg रेजिस्टर */
	अचिन्हित लघु		lock_offs;
	क्रमागत samsung_pll_type	type;
	अचिन्हित पूर्णांक		rate_count;
	स्थिर काष्ठा samsung_pll_rate_table *rate_table;
पूर्ण;

#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा samsung_clk_pll, hw)

अटल स्थिर काष्ठा samsung_pll_rate_table *samsung_get_pll_settings(
				काष्ठा samsung_clk_pll *pll, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा samsung_pll_rate_table  *rate_table = pll->rate_table;
	पूर्णांक i;

	क्रम (i = 0; i < pll->rate_count; i++) अणु
		अगर (rate == rate_table[i].rate)
			वापस &rate_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल दीर्घ samsung_pll_round_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ drate, अचिन्हित दीर्घ *prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate_table = pll->rate_table;
	पूर्णांक i;

	/* Assumming rate_table is in descending order */
	क्रम (i = 0; i < pll->rate_count; i++) अणु
		अगर (drate >= rate_table[i].rate)
			वापस rate_table[i].rate;
	पूर्ण

	/* वापस minimum supported value */
	वापस rate_table[i - 1].rate;
पूर्ण

अटल bool pll_early_समयout = true;

अटल पूर्णांक __init samsung_pll_disable_early_समयout(व्योम)
अणु
	pll_early_समयout = false;
	वापस 0;
पूर्ण
arch_initcall(samsung_pll_disable_early_समयout);

/* Wait until the PLL is locked */
अटल पूर्णांक samsung_pll_lock_रुको(काष्ठा samsung_clk_pll *pll,
				 अचिन्हित पूर्णांक reg_mask)
अणु
	पूर्णांक i, ret;
	u32 val;

	/*
	 * This function might be called when the समयkeeping API can't be used
	 * to detect समयouts. One situation is when the घड़ीsource is not yet
	 * initialized, another when the समयkeeping is suspended. udelay() also
	 * cannot be used when the घड़ीsource is not running on arm64, since
	 * the current समयr is used as cycle counter. So a simple busy loop
	 * is used here in that special हालs. The limit of iterations has been
	 * derived from experimental measurements of various PLLs on multiple
	 * Exynos SoC variants. Single रेजिस्टर पढ़ो समय was usually in range
	 * 0.4...1.5 us, never less than 0.4 us.
	 */
	अगर (pll_early_समयout || समयkeeping_suspended) अणु
		i = PLL_TIMEOUT_LOOPS;
		जबतक (i-- > 0) अणु
			अगर (पढ़ोl_relaxed(pll->con_reg) & reg_mask)
				वापस 0;

			cpu_relax();
		पूर्ण
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = पढ़ोl_relaxed_poll_समयout_atomic(pll->con_reg, val,
					val & reg_mask, 0, PLL_TIMEOUT_US);
	पूर्ण

	अगर (ret < 0)
		pr_err("Could not lock PLL %s\n", clk_hw_get_name(&pll->hw));

	वापस ret;
पूर्ण

अटल पूर्णांक samsung_pll3xxx_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(pll->con_reg);
	पंचांगp |= BIT(pll->enable_offs);
	ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

	वापस samsung_pll_lock_रुको(pll, BIT(pll->lock_offs));
पूर्ण

अटल व्योम samsung_pll3xxx_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(pll->con_reg);
	पंचांगp &= ~BIT(pll->enable_offs);
	ग_लिखोl_relaxed(पंचांगp, pll->con_reg);
पूर्ण

/*
 * PLL2126 Clock Type
 */

#घोषणा PLL2126_MDIV_MASK	(0xff)
#घोषणा PLL2126_PDIV_MASK	(0x3f)
#घोषणा PLL2126_SDIV_MASK	(0x3)
#घोषणा PLL2126_MDIV_SHIFT	(16)
#घोषणा PLL2126_PDIV_SHIFT	(8)
#घोषणा PLL2126_SDIV_SHIFT	(0)

अटल अचिन्हित दीर्घ samsung_pll2126_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con, mभाग, pभाग, sभाग;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLL2126_MDIV_SHIFT) & PLL2126_MDIV_MASK;
	pभाग = (pll_con >> PLL2126_PDIV_SHIFT) & PLL2126_PDIV_MASK;
	sभाग = (pll_con >> PLL2126_SDIV_SHIFT) & PLL2126_SDIV_MASK;

	fvco *= (mभाग + 8);
	करो_भाग(fvco, (pभाग + 2) << sभाग);

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll2126_clk_ops = अणु
	.recalc_rate = samsung_pll2126_recalc_rate,
पूर्ण;

/*
 * PLL3000 Clock Type
 */

#घोषणा PLL3000_MDIV_MASK	(0xff)
#घोषणा PLL3000_PDIV_MASK	(0x3)
#घोषणा PLL3000_SDIV_MASK	(0x3)
#घोषणा PLL3000_MDIV_SHIFT	(16)
#घोषणा PLL3000_PDIV_SHIFT	(8)
#घोषणा PLL3000_SDIV_SHIFT	(0)

अटल अचिन्हित दीर्घ samsung_pll3000_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con, mभाग, pभाग, sभाग;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLL3000_MDIV_SHIFT) & PLL3000_MDIV_MASK;
	pभाग = (pll_con >> PLL3000_PDIV_SHIFT) & PLL3000_PDIV_MASK;
	sभाग = (pll_con >> PLL3000_SDIV_SHIFT) & PLL3000_SDIV_MASK;

	fvco *= (2 * (mभाग + 8));
	करो_भाग(fvco, pभाग << sभाग);

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll3000_clk_ops = अणु
	.recalc_rate = samsung_pll3000_recalc_rate,
पूर्ण;

/*
 * PLL35xx Clock Type
 */
/* Maximum lock समय can be 270 * PDIV cycles */
#घोषणा PLL35XX_LOCK_FACTOR	(270)

#घोषणा PLL35XX_MDIV_MASK       (0x3FF)
#घोषणा PLL35XX_PDIV_MASK       (0x3F)
#घोषणा PLL35XX_SDIV_MASK       (0x7)
#घोषणा PLL35XX_MDIV_SHIFT      (16)
#घोषणा PLL35XX_PDIV_SHIFT      (8)
#घोषणा PLL35XX_SDIV_SHIFT      (0)
#घोषणा PLL35XX_LOCK_STAT_SHIFT	(29)
#घोषणा PLL35XX_ENABLE_SHIFT	(31)

अटल अचिन्हित दीर्घ samsung_pll35xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLL35XX_MDIV_SHIFT) & PLL35XX_MDIV_MASK;
	pभाग = (pll_con >> PLL35XX_PDIV_SHIFT) & PLL35XX_PDIV_MASK;
	sभाग = (pll_con >> PLL35XX_SDIV_SHIFT) & PLL35XX_SDIV_MASK;

	fvco *= mभाग;
	करो_भाग(fvco, (pभाग << sभाग));

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल अंतरभूत bool samsung_pll35xx_mp_change(
		स्थिर काष्ठा samsung_pll_rate_table *rate, u32 pll_con)
अणु
	u32 old_mभाग, old_pभाग;

	old_mभाग = (pll_con >> PLL35XX_MDIV_SHIFT) & PLL35XX_MDIV_MASK;
	old_pभाग = (pll_con >> PLL35XX_PDIV_SHIFT) & PLL35XX_PDIV_MASK;

	वापस (rate->mभाग != old_mभाग || rate->pभाग != old_pभाग);
पूर्ण

अटल पूर्णांक samsung_pll35xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 पंचांगp;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(pll->con_reg);

	अगर (!(samsung_pll35xx_mp_change(rate, पंचांगp))) अणु
		/* If only s change, change just s value only*/
		पंचांगp &= ~(PLL35XX_SDIV_MASK << PLL35XX_SDIV_SHIFT);
		पंचांगp |= rate->sभाग << PLL35XX_SDIV_SHIFT;
		ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

		वापस 0;
	पूर्ण

	/* Set PLL lock समय. */
	ग_लिखोl_relaxed(rate->pभाग * PLL35XX_LOCK_FACTOR,
			pll->lock_reg);

	/* Change PLL PMS values */
	पंचांगp &= ~((PLL35XX_MDIV_MASK << PLL35XX_MDIV_SHIFT) |
			(PLL35XX_PDIV_MASK << PLL35XX_PDIV_SHIFT) |
			(PLL35XX_SDIV_MASK << PLL35XX_SDIV_SHIFT));
	पंचांगp |= (rate->mभाग << PLL35XX_MDIV_SHIFT) |
			(rate->pभाग << PLL35XX_PDIV_SHIFT) |
			(rate->sभाग << PLL35XX_SDIV_SHIFT);
	ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

	/* Wait क्रम PLL lock अगर the PLL is enabled */
	अगर (पंचांगp & BIT(pll->enable_offs))
		वापस samsung_pll_lock_रुको(pll, BIT(pll->lock_offs));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll35xx_clk_ops = अणु
	.recalc_rate = samsung_pll35xx_recalc_rate,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_pll35xx_set_rate,
	.enable = samsung_pll3xxx_enable,
	.disable = samsung_pll3xxx_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll35xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll35xx_recalc_rate,
पूर्ण;

/*
 * PLL36xx Clock Type
 */
/* Maximum lock समय can be 3000 * PDIV cycles */
#घोषणा PLL36XX_LOCK_FACTOR    (3000)

#घोषणा PLL36XX_KDIV_MASK	(0xFFFF)
#घोषणा PLL36XX_MDIV_MASK	(0x1FF)
#घोषणा PLL36XX_PDIV_MASK	(0x3F)
#घोषणा PLL36XX_SDIV_MASK	(0x7)
#घोषणा PLL36XX_MDIV_SHIFT	(16)
#घोषणा PLL36XX_PDIV_SHIFT	(8)
#घोषणा PLL36XX_SDIV_SHIFT	(0)
#घोषणा PLL36XX_KDIV_SHIFT	(0)
#घोषणा PLL36XX_LOCK_STAT_SHIFT	(29)
#घोषणा PLL36XX_ENABLE_SHIFT	(31)

अटल अचिन्हित दीर्घ samsung_pll36xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con0, pll_con1;
	s16 kभाग;
	u64 fvco = parent_rate;

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con1 = पढ़ोl_relaxed(pll->con_reg + 4);
	mभाग = (pll_con0 >> PLL36XX_MDIV_SHIFT) & PLL36XX_MDIV_MASK;
	pभाग = (pll_con0 >> PLL36XX_PDIV_SHIFT) & PLL36XX_PDIV_MASK;
	sभाग = (pll_con0 >> PLL36XX_SDIV_SHIFT) & PLL36XX_SDIV_MASK;
	kभाग = (s16)(pll_con1 & PLL36XX_KDIV_MASK);

	fvco *= (mभाग << 16) + kभाग;
	करो_भाग(fvco, (pभाग << sभाग));
	fvco >>= 16;

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल अंतरभूत bool samsung_pll36xx_mpk_change(
	स्थिर काष्ठा samsung_pll_rate_table *rate, u32 pll_con0, u32 pll_con1)
अणु
	u32 old_mभाग, old_pभाग, old_kभाग;

	old_mभाग = (pll_con0 >> PLL36XX_MDIV_SHIFT) & PLL36XX_MDIV_MASK;
	old_pभाग = (pll_con0 >> PLL36XX_PDIV_SHIFT) & PLL36XX_PDIV_MASK;
	old_kभाग = (pll_con1 >> PLL36XX_KDIV_SHIFT) & PLL36XX_KDIV_MASK;

	वापस (rate->mभाग != old_mभाग || rate->pभाग != old_pभाग ||
		rate->kभाग != old_kभाग);
पूर्ण

अटल पूर्णांक samsung_pll36xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con0, pll_con1;
	स्थिर काष्ठा samsung_pll_rate_table *rate;

	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con1 = पढ़ोl_relaxed(pll->con_reg + 4);

	अगर (!(samsung_pll36xx_mpk_change(rate, pll_con0, pll_con1))) अणु
		/* If only s change, change just s value only*/
		pll_con0 &= ~(PLL36XX_SDIV_MASK << PLL36XX_SDIV_SHIFT);
		pll_con0 |= (rate->sभाग << PLL36XX_SDIV_SHIFT);
		ग_लिखोl_relaxed(pll_con0, pll->con_reg);

		वापस 0;
	पूर्ण

	/* Set PLL lock समय. */
	ग_लिखोl_relaxed(rate->pभाग * PLL36XX_LOCK_FACTOR, pll->lock_reg);

	 /* Change PLL PMS values */
	pll_con0 &= ~((PLL36XX_MDIV_MASK << PLL36XX_MDIV_SHIFT) |
			(PLL36XX_PDIV_MASK << PLL36XX_PDIV_SHIFT) |
			(PLL36XX_SDIV_MASK << PLL36XX_SDIV_SHIFT));
	pll_con0 |= (rate->mभाग << PLL36XX_MDIV_SHIFT) |
			(rate->pभाग << PLL36XX_PDIV_SHIFT) |
			(rate->sभाग << PLL36XX_SDIV_SHIFT);
	ग_लिखोl_relaxed(pll_con0, pll->con_reg);

	pll_con1 &= ~(PLL36XX_KDIV_MASK << PLL36XX_KDIV_SHIFT);
	pll_con1 |= rate->kभाग << PLL36XX_KDIV_SHIFT;
	ग_लिखोl_relaxed(pll_con1, pll->con_reg + 4);

	अगर (pll_con0 & BIT(pll->enable_offs))
		वापस samsung_pll_lock_रुको(pll, BIT(pll->lock_offs));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll36xx_clk_ops = अणु
	.recalc_rate = samsung_pll36xx_recalc_rate,
	.set_rate = samsung_pll36xx_set_rate,
	.round_rate = samsung_pll_round_rate,
	.enable = samsung_pll3xxx_enable,
	.disable = samsung_pll3xxx_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll36xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll36xx_recalc_rate,
पूर्ण;

/*
 * PLL45xx Clock Type
 */
#घोषणा PLL4502_LOCK_FACTOR	400
#घोषणा PLL4508_LOCK_FACTOR	240

#घोषणा PLL45XX_MDIV_MASK	(0x3FF)
#घोषणा PLL45XX_PDIV_MASK	(0x3F)
#घोषणा PLL45XX_SDIV_MASK	(0x7)
#घोषणा PLL45XX_AFC_MASK	(0x1F)
#घोषणा PLL45XX_MDIV_SHIFT	(16)
#घोषणा PLL45XX_PDIV_SHIFT	(8)
#घोषणा PLL45XX_SDIV_SHIFT	(0)
#घोषणा PLL45XX_AFC_SHIFT	(0)

#घोषणा PLL45XX_ENABLE		BIT(31)
#घोषणा PLL45XX_LOCKED		BIT(29)

अटल अचिन्हित दीर्घ samsung_pll45xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLL45XX_MDIV_SHIFT) & PLL45XX_MDIV_MASK;
	pभाग = (pll_con >> PLL45XX_PDIV_SHIFT) & PLL45XX_PDIV_MASK;
	sभाग = (pll_con >> PLL45XX_SDIV_SHIFT) & PLL45XX_SDIV_MASK;

	अगर (pll->type == pll_4508)
		sभाग = sभाग - 1;

	fvco *= mभाग;
	करो_भाग(fvco, (pभाग << sभाग));

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल bool samsung_pll45xx_mp_change(u32 pll_con0, u32 pll_con1,
				स्थिर काष्ठा samsung_pll_rate_table *rate)
अणु
	u32 old_mभाग, old_pभाग, old_afc;

	old_mभाग = (pll_con0 >> PLL45XX_MDIV_SHIFT) & PLL45XX_MDIV_MASK;
	old_pभाग = (pll_con0 >> PLL45XX_PDIV_SHIFT) & PLL45XX_PDIV_MASK;
	old_afc = (pll_con1 >> PLL45XX_AFC_SHIFT) & PLL45XX_AFC_MASK;

	वापस (old_mभाग != rate->mभाग || old_pभाग != rate->pभाग
		|| old_afc != rate->afc);
पूर्ण

अटल पूर्णांक samsung_pll45xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 con0, con1;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	con0 = पढ़ोl_relaxed(pll->con_reg);
	con1 = पढ़ोl_relaxed(pll->con_reg + 0x4);

	अगर (!(samsung_pll45xx_mp_change(con0, con1, rate))) अणु
		/* If only s change, change just s value only*/
		con0 &= ~(PLL45XX_SDIV_MASK << PLL45XX_SDIV_SHIFT);
		con0 |= rate->sभाग << PLL45XX_SDIV_SHIFT;
		ग_लिखोl_relaxed(con0, pll->con_reg);

		वापस 0;
	पूर्ण

	/* Set PLL PMS values. */
	con0 &= ~((PLL45XX_MDIV_MASK << PLL45XX_MDIV_SHIFT) |
			(PLL45XX_PDIV_MASK << PLL45XX_PDIV_SHIFT) |
			(PLL45XX_SDIV_MASK << PLL45XX_SDIV_SHIFT));
	con0 |= (rate->mभाग << PLL45XX_MDIV_SHIFT) |
			(rate->pभाग << PLL45XX_PDIV_SHIFT) |
			(rate->sभाग << PLL45XX_SDIV_SHIFT);

	/* Set PLL AFC value. */
	con1 = पढ़ोl_relaxed(pll->con_reg + 0x4);
	con1 &= ~(PLL45XX_AFC_MASK << PLL45XX_AFC_SHIFT);
	con1 |= (rate->afc << PLL45XX_AFC_SHIFT);

	/* Set PLL lock समय. */
	चयन (pll->type) अणु
	हाल pll_4502:
		ग_लिखोl_relaxed(rate->pभाग * PLL4502_LOCK_FACTOR, pll->lock_reg);
		अवरोध;
	हाल pll_4508:
		ग_लिखोl_relaxed(rate->pभाग * PLL4508_LOCK_FACTOR, pll->lock_reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Set new configuration. */
	ग_लिखोl_relaxed(con1, pll->con_reg + 0x4);
	ग_लिखोl_relaxed(con0, pll->con_reg);

	/* Wait क्रम PLL lock */
	वापस samsung_pll_lock_रुको(pll, PLL45XX_LOCKED);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll45xx_clk_ops = अणु
	.recalc_rate = samsung_pll45xx_recalc_rate,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_pll45xx_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll45xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll45xx_recalc_rate,
पूर्ण;

/*
 * PLL46xx Clock Type
 */
#घोषणा PLL46XX_LOCK_FACTOR	3000

#घोषणा PLL46XX_VSEL_MASK	(1)
#घोषणा PLL46XX_MDIV_MASK	(0x1FF)
#घोषणा PLL1460X_MDIV_MASK	(0x3FF)

#घोषणा PLL46XX_PDIV_MASK	(0x3F)
#घोषणा PLL46XX_SDIV_MASK	(0x7)
#घोषणा PLL46XX_VSEL_SHIFT	(27)
#घोषणा PLL46XX_MDIV_SHIFT	(16)
#घोषणा PLL46XX_PDIV_SHIFT	(8)
#घोषणा PLL46XX_SDIV_SHIFT	(0)

#घोषणा PLL46XX_KDIV_MASK	(0xFFFF)
#घोषणा PLL4650C_KDIV_MASK	(0xFFF)
#घोषणा PLL46XX_KDIV_SHIFT	(0)
#घोषणा PLL46XX_MFR_MASK	(0x3F)
#घोषणा PLL46XX_MRR_MASK	(0x1F)
#घोषणा PLL46XX_KDIV_SHIFT	(0)
#घोषणा PLL46XX_MFR_SHIFT	(16)
#घोषणा PLL46XX_MRR_SHIFT	(24)

#घोषणा PLL46XX_ENABLE		BIT(31)
#घोषणा PLL46XX_LOCKED		BIT(29)
#घोषणा PLL46XX_VSEL		BIT(27)

अटल अचिन्हित दीर्घ samsung_pll46xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, kभाग, pll_con0, pll_con1, shअगरt;
	u64 fvco = parent_rate;

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con1 = पढ़ोl_relaxed(pll->con_reg + 4);
	mभाग = (pll_con0 >> PLL46XX_MDIV_SHIFT) & ((pll->type == pll_1460x) ?
				PLL1460X_MDIV_MASK : PLL46XX_MDIV_MASK);
	pभाग = (pll_con0 >> PLL46XX_PDIV_SHIFT) & PLL46XX_PDIV_MASK;
	sभाग = (pll_con0 >> PLL46XX_SDIV_SHIFT) & PLL46XX_SDIV_MASK;
	kभाग = pll->type == pll_4650c ? pll_con1 & PLL4650C_KDIV_MASK :
					pll_con1 & PLL46XX_KDIV_MASK;

	shअगरt = ((pll->type == pll_4600) || (pll->type == pll_1460x)) ? 16 : 10;

	fvco *= (mभाग << shअगरt) + kभाग;
	करो_भाग(fvco, (pभाग << sभाग));
	fvco >>= shअगरt;

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल bool samsung_pll46xx_mpk_change(u32 pll_con0, u32 pll_con1,
				स्थिर काष्ठा samsung_pll_rate_table *rate)
अणु
	u32 old_mभाग, old_pभाग, old_kभाग;

	old_mभाग = (pll_con0 >> PLL46XX_MDIV_SHIFT) & PLL46XX_MDIV_MASK;
	old_pभाग = (pll_con0 >> PLL46XX_PDIV_SHIFT) & PLL46XX_PDIV_MASK;
	old_kभाग = (pll_con1 >> PLL46XX_KDIV_SHIFT) & PLL46XX_KDIV_MASK;

	वापस (old_mभाग != rate->mभाग || old_pभाग != rate->pभाग
		|| old_kभाग != rate->kभाग);
पूर्ण

अटल पूर्णांक samsung_pll46xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 con0, con1, lock;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	con0 = पढ़ोl_relaxed(pll->con_reg);
	con1 = पढ़ोl_relaxed(pll->con_reg + 0x4);

	अगर (!(samsung_pll46xx_mpk_change(con0, con1, rate))) अणु
		/* If only s change, change just s value only*/
		con0 &= ~(PLL46XX_SDIV_MASK << PLL46XX_SDIV_SHIFT);
		con0 |= rate->sभाग << PLL46XX_SDIV_SHIFT;
		ग_लिखोl_relaxed(con0, pll->con_reg);

		वापस 0;
	पूर्ण

	/* Set PLL lock समय. */
	lock = rate->pभाग * PLL46XX_LOCK_FACTOR;
	अगर (lock > 0xffff)
		/* Maximum lock समय bitfield is 16-bit. */
		lock = 0xffff;

	/* Set PLL PMS and VSEL values. */
	अगर (pll->type == pll_1460x) अणु
		con0 &= ~((PLL1460X_MDIV_MASK << PLL46XX_MDIV_SHIFT) |
			(PLL46XX_PDIV_MASK << PLL46XX_PDIV_SHIFT) |
			(PLL46XX_SDIV_MASK << PLL46XX_SDIV_SHIFT));
	पूर्ण अन्यथा अणु
		con0 &= ~((PLL46XX_MDIV_MASK << PLL46XX_MDIV_SHIFT) |
			(PLL46XX_PDIV_MASK << PLL46XX_PDIV_SHIFT) |
			(PLL46XX_SDIV_MASK << PLL46XX_SDIV_SHIFT) |
			(PLL46XX_VSEL_MASK << PLL46XX_VSEL_SHIFT));
		con0 |=	rate->vsel << PLL46XX_VSEL_SHIFT;
	पूर्ण

	con0 |= (rate->mभाग << PLL46XX_MDIV_SHIFT) |
			(rate->pभाग << PLL46XX_PDIV_SHIFT) |
			(rate->sभाग << PLL46XX_SDIV_SHIFT);

	/* Set PLL K, MFR and MRR values. */
	con1 = पढ़ोl_relaxed(pll->con_reg + 0x4);
	con1 &= ~((PLL46XX_KDIV_MASK << PLL46XX_KDIV_SHIFT) |
			(PLL46XX_MFR_MASK << PLL46XX_MFR_SHIFT) |
			(PLL46XX_MRR_MASK << PLL46XX_MRR_SHIFT));
	con1 |= (rate->kभाग << PLL46XX_KDIV_SHIFT) |
			(rate->mfr << PLL46XX_MFR_SHIFT) |
			(rate->mrr << PLL46XX_MRR_SHIFT);

	/* Write configuration to PLL */
	ग_लिखोl_relaxed(lock, pll->lock_reg);
	ग_लिखोl_relaxed(con0, pll->con_reg);
	ग_लिखोl_relaxed(con1, pll->con_reg + 0x4);

	/* Wait क्रम PLL lock */
	वापस samsung_pll_lock_रुको(pll, PLL46XX_LOCKED);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll46xx_clk_ops = अणु
	.recalc_rate = samsung_pll46xx_recalc_rate,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_pll46xx_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll46xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll46xx_recalc_rate,
पूर्ण;

/*
 * PLL6552 Clock Type
 */

#घोषणा PLL6552_MDIV_MASK	0x3ff
#घोषणा PLL6552_PDIV_MASK	0x3f
#घोषणा PLL6552_SDIV_MASK	0x7
#घोषणा PLL6552_MDIV_SHIFT	16
#घोषणा PLL6552_MDIV_SHIFT_2416	14
#घोषणा PLL6552_PDIV_SHIFT	8
#घोषणा PLL6552_PDIV_SHIFT_2416	5
#घोषणा PLL6552_SDIV_SHIFT	0

अटल अचिन्हित दीर्घ samsung_pll6552_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	अगर (pll->type == pll_6552_s3c2416) अणु
		mभाग = (pll_con >> PLL6552_MDIV_SHIFT_2416) & PLL6552_MDIV_MASK;
		pभाग = (pll_con >> PLL6552_PDIV_SHIFT_2416) & PLL6552_PDIV_MASK;
	पूर्ण अन्यथा अणु
		mभाग = (pll_con >> PLL6552_MDIV_SHIFT) & PLL6552_MDIV_MASK;
		pभाग = (pll_con >> PLL6552_PDIV_SHIFT) & PLL6552_PDIV_MASK;
	पूर्ण
	sभाग = (pll_con >> PLL6552_SDIV_SHIFT) & PLL6552_SDIV_MASK;

	fvco *= mभाग;
	करो_भाग(fvco, (pभाग << sभाग));

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll6552_clk_ops = अणु
	.recalc_rate = samsung_pll6552_recalc_rate,
पूर्ण;

/*
 * PLL6553 Clock Type
 */

#घोषणा PLL6553_MDIV_MASK	0xff
#घोषणा PLL6553_PDIV_MASK	0x3f
#घोषणा PLL6553_SDIV_MASK	0x7
#घोषणा PLL6553_KDIV_MASK	0xffff
#घोषणा PLL6553_MDIV_SHIFT	16
#घोषणा PLL6553_PDIV_SHIFT	8
#घोषणा PLL6553_SDIV_SHIFT	0
#घोषणा PLL6553_KDIV_SHIFT	0

अटल अचिन्हित दीर्घ samsung_pll6553_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, kभाग, pll_con0, pll_con1;
	u64 fvco = parent_rate;

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con1 = पढ़ोl_relaxed(pll->con_reg + 0x4);
	mभाग = (pll_con0 >> PLL6553_MDIV_SHIFT) & PLL6553_MDIV_MASK;
	pभाग = (pll_con0 >> PLL6553_PDIV_SHIFT) & PLL6553_PDIV_MASK;
	sभाग = (pll_con0 >> PLL6553_SDIV_SHIFT) & PLL6553_SDIV_MASK;
	kभाग = (pll_con1 >> PLL6553_KDIV_SHIFT) & PLL6553_KDIV_MASK;

	fvco *= (mभाग << 16) + kभाग;
	करो_भाग(fvco, (pभाग << sभाग));
	fvco >>= 16;

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll6553_clk_ops = अणु
	.recalc_rate = samsung_pll6553_recalc_rate,
पूर्ण;

/*
 * PLL Clock Type of S3C24XX beक्रमe S3C2443
 */

#घोषणा PLLS3C2410_MDIV_MASK		(0xff)
#घोषणा PLLS3C2410_PDIV_MASK		(0x1f)
#घोषणा PLLS3C2410_SDIV_MASK		(0x3)
#घोषणा PLLS3C2410_MDIV_SHIFT		(12)
#घोषणा PLLS3C2410_PDIV_SHIFT		(4)
#घोषणा PLLS3C2410_SDIV_SHIFT		(0)

#घोषणा PLLS3C2410_ENABLE_REG_OFFSET	0x10

अटल अचिन्हित दीर्घ samsung_s3c2410_pll_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con, mभाग, pभाग, sभाग;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLLS3C2410_MDIV_SHIFT) & PLLS3C2410_MDIV_MASK;
	pभाग = (pll_con >> PLLS3C2410_PDIV_SHIFT) & PLLS3C2410_PDIV_MASK;
	sभाग = (pll_con >> PLLS3C2410_SDIV_SHIFT) & PLLS3C2410_SDIV_MASK;

	fvco *= (mभाग + 8);
	करो_भाग(fvco, (pभाग + 2) << sभाग);

	वापस (अचिन्हित पूर्णांक)fvco;
पूर्ण

अटल अचिन्हित दीर्घ samsung_s3c2440_mpll_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con, mभाग, pभाग, sभाग;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLLS3C2410_MDIV_SHIFT) & PLLS3C2410_MDIV_MASK;
	pभाग = (pll_con >> PLLS3C2410_PDIV_SHIFT) & PLLS3C2410_PDIV_MASK;
	sभाग = (pll_con >> PLLS3C2410_SDIV_SHIFT) & PLLS3C2410_SDIV_MASK;

	fvco *= (2 * (mभाग + 8));
	करो_भाग(fvco, (pभाग + 2) << sभाग);

	वापस (अचिन्हित पूर्णांक)fvco;
पूर्ण

अटल पूर्णांक samsung_s3c2410_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 पंचांगp;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(pll->con_reg);

	/* Change PLL PMS values */
	पंचांगp &= ~((PLLS3C2410_MDIV_MASK << PLLS3C2410_MDIV_SHIFT) |
			(PLLS3C2410_PDIV_MASK << PLLS3C2410_PDIV_SHIFT) |
			(PLLS3C2410_SDIV_MASK << PLLS3C2410_SDIV_SHIFT));
	पंचांगp |= (rate->mभाग << PLLS3C2410_MDIV_SHIFT) |
			(rate->pभाग << PLLS3C2410_PDIV_SHIFT) |
			(rate->sभाग << PLLS3C2410_SDIV_SHIFT);
	ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

	/* Time to settle according to the manual */
	udelay(300);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_s3c2410_pll_enable(काष्ठा clk_hw *hw, पूर्णांक bit, bool enable)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_en = पढ़ोl_relaxed(pll->lock_reg + PLLS3C2410_ENABLE_REG_OFFSET);
	u32 pll_en_orig = pll_en;

	अगर (enable)
		pll_en &= ~BIT(bit);
	अन्यथा
		pll_en |= BIT(bit);

	ग_लिखोl_relaxed(pll_en, pll->lock_reg + PLLS3C2410_ENABLE_REG_OFFSET);

	/* अगर we started the UPLL, then allow to settle */
	अगर (enable && (pll_en_orig & BIT(bit)))
		udelay(300);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_s3c2410_mpll_enable(काष्ठा clk_hw *hw)
अणु
	वापस samsung_s3c2410_pll_enable(hw, 5, true);
पूर्ण

अटल व्योम samsung_s3c2410_mpll_disable(काष्ठा clk_hw *hw)
अणु
	samsung_s3c2410_pll_enable(hw, 5, false);
पूर्ण

अटल पूर्णांक samsung_s3c2410_upll_enable(काष्ठा clk_hw *hw)
अणु
	वापस samsung_s3c2410_pll_enable(hw, 7, true);
पूर्ण

अटल व्योम samsung_s3c2410_upll_disable(काष्ठा clk_hw *hw)
अणु
	samsung_s3c2410_pll_enable(hw, 7, false);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_s3c2410_mpll_clk_min_ops = अणु
	.recalc_rate = samsung_s3c2410_pll_recalc_rate,
	.enable = samsung_s3c2410_mpll_enable,
	.disable = samsung_s3c2410_mpll_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_s3c2410_upll_clk_min_ops = अणु
	.recalc_rate = samsung_s3c2410_pll_recalc_rate,
	.enable = samsung_s3c2410_upll_enable,
	.disable = samsung_s3c2410_upll_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_s3c2440_mpll_clk_min_ops = अणु
	.recalc_rate = samsung_s3c2440_mpll_recalc_rate,
	.enable = samsung_s3c2410_mpll_enable,
	.disable = samsung_s3c2410_mpll_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_s3c2410_mpll_clk_ops = अणु
	.recalc_rate = samsung_s3c2410_pll_recalc_rate,
	.enable = samsung_s3c2410_mpll_enable,
	.disable = samsung_s3c2410_mpll_disable,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_s3c2410_pll_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_s3c2410_upll_clk_ops = अणु
	.recalc_rate = samsung_s3c2410_pll_recalc_rate,
	.enable = samsung_s3c2410_upll_enable,
	.disable = samsung_s3c2410_upll_disable,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_s3c2410_pll_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_s3c2440_mpll_clk_ops = अणु
	.recalc_rate = samsung_s3c2440_mpll_recalc_rate,
	.enable = samsung_s3c2410_mpll_enable,
	.disable = samsung_s3c2410_mpll_disable,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_s3c2410_pll_set_rate,
पूर्ण;

/*
 * PLL2550x Clock Type
 */

#घोषणा PLL2550X_R_MASK       (0x1)
#घोषणा PLL2550X_P_MASK       (0x3F)
#घोषणा PLL2550X_M_MASK       (0x3FF)
#घोषणा PLL2550X_S_MASK       (0x7)
#घोषणा PLL2550X_R_SHIFT      (20)
#घोषणा PLL2550X_P_SHIFT      (14)
#घोषणा PLL2550X_M_SHIFT      (4)
#घोषणा PLL2550X_S_SHIFT      (0)

अटल अचिन्हित दीर्घ samsung_pll2550x_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 r, p, m, s, pll_stat;
	u64 fvco = parent_rate;

	pll_stat = पढ़ोl_relaxed(pll->con_reg);
	r = (pll_stat >> PLL2550X_R_SHIFT) & PLL2550X_R_MASK;
	अगर (!r)
		वापस 0;
	p = (pll_stat >> PLL2550X_P_SHIFT) & PLL2550X_P_MASK;
	m = (pll_stat >> PLL2550X_M_SHIFT) & PLL2550X_M_MASK;
	s = (pll_stat >> PLL2550X_S_SHIFT) & PLL2550X_S_MASK;

	fvco *= m;
	करो_भाग(fvco, (p << s));

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll2550x_clk_ops = अणु
	.recalc_rate = samsung_pll2550x_recalc_rate,
पूर्ण;

/*
 * PLL2550xx Clock Type
 */

/* Maximum lock समय can be 270 * PDIV cycles */
#घोषणा PLL2550XX_LOCK_FACTOR 270

#घोषणा PLL2550XX_M_MASK		0x3FF
#घोषणा PLL2550XX_P_MASK		0x3F
#घोषणा PLL2550XX_S_MASK		0x7
#घोषणा PLL2550XX_LOCK_STAT_MASK	0x1
#घोषणा PLL2550XX_M_SHIFT		9
#घोषणा PLL2550XX_P_SHIFT		3
#घोषणा PLL2550XX_S_SHIFT		0
#घोषणा PLL2550XX_LOCK_STAT_SHIFT	21

अटल अचिन्हित दीर्घ samsung_pll2550xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con;
	u64 fvco = parent_rate;

	pll_con = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con >> PLL2550XX_M_SHIFT) & PLL2550XX_M_MASK;
	pभाग = (pll_con >> PLL2550XX_P_SHIFT) & PLL2550XX_P_MASK;
	sभाग = (pll_con >> PLL2550XX_S_SHIFT) & PLL2550XX_S_MASK;

	fvco *= mभाग;
	करो_भाग(fvco, (pभाग << sभाग));

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल अंतरभूत bool samsung_pll2550xx_mp_change(u32 mभाग, u32 pभाग, u32 pll_con)
अणु
	u32 old_mभाग, old_pभाग;

	old_mभाग = (pll_con >> PLL2550XX_M_SHIFT) & PLL2550XX_M_MASK;
	old_pभाग = (pll_con >> PLL2550XX_P_SHIFT) & PLL2550XX_P_MASK;

	वापस mभाग != old_mभाग || pभाग != old_pभाग;
पूर्ण

अटल पूर्णांक samsung_pll2550xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 पंचांगp;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(pll->con_reg);

	अगर (!(samsung_pll2550xx_mp_change(rate->mभाग, rate->pभाग, पंचांगp))) अणु
		/* If only s change, change just s value only*/
		पंचांगp &= ~(PLL2550XX_S_MASK << PLL2550XX_S_SHIFT);
		पंचांगp |= rate->sभाग << PLL2550XX_S_SHIFT;
		ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

		वापस 0;
	पूर्ण

	/* Set PLL lock समय. */
	ग_लिखोl_relaxed(rate->pभाग * PLL2550XX_LOCK_FACTOR, pll->lock_reg);

	/* Change PLL PMS values */
	पंचांगp &= ~((PLL2550XX_M_MASK << PLL2550XX_M_SHIFT) |
			(PLL2550XX_P_MASK << PLL2550XX_P_SHIFT) |
			(PLL2550XX_S_MASK << PLL2550XX_S_SHIFT));
	पंचांगp |= (rate->mभाग << PLL2550XX_M_SHIFT) |
			(rate->pभाग << PLL2550XX_P_SHIFT) |
			(rate->sभाग << PLL2550XX_S_SHIFT);
	ग_लिखोl_relaxed(पंचांगp, pll->con_reg);

	/* Wait क्रम PLL lock */
	वापस samsung_pll_lock_रुको(pll,
			PLL2550XX_LOCK_STAT_MASK << PLL2550XX_LOCK_STAT_SHIFT);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll2550xx_clk_ops = अणु
	.recalc_rate = samsung_pll2550xx_recalc_rate,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_pll2550xx_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll2550xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll2550xx_recalc_rate,
पूर्ण;

/*
 * PLL2650x Clock Type
 */

/* Maximum lock समय can be 3000 * PDIV cycles */
#घोषणा PLL2650X_LOCK_FACTOR		3000

#घोषणा PLL2650X_M_MASK			0x1ff
#घोषणा PLL2650X_P_MASK			0x3f
#घोषणा PLL2650X_S_MASK			0x7
#घोषणा PLL2650X_K_MASK			0xffff
#घोषणा PLL2650X_LOCK_STAT_MASK		0x1
#घोषणा PLL2650X_M_SHIFT		16
#घोषणा PLL2650X_P_SHIFT		8
#घोषणा PLL2650X_S_SHIFT		0
#घोषणा PLL2650X_K_SHIFT		0
#घोषणा PLL2650X_LOCK_STAT_SHIFT	29
#घोषणा PLL2650X_PLL_ENABLE_SHIFT	31

अटल अचिन्हित दीर्घ samsung_pll2650x_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u64 fout = parent_rate;
	u32 mभाग, pभाग, sभाग, pll_con0, pll_con1;
	s16 kभाग;

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	mभाग = (pll_con0 >> PLL2650X_M_SHIFT) & PLL2650X_M_MASK;
	pभाग = (pll_con0 >> PLL2650X_P_SHIFT) & PLL2650X_P_MASK;
	sभाग = (pll_con0 >> PLL2650X_S_SHIFT) & PLL2650X_S_MASK;

	pll_con1 = पढ़ोl_relaxed(pll->con_reg + 4);
	kभाग = (s16)((pll_con1 >> PLL2650X_K_SHIFT) & PLL2650X_K_MASK);

	fout *= (mभाग << 16) + kभाग;
	करो_भाग(fout, (pभाग << sभाग));
	fout >>= 16;

	वापस (अचिन्हित दीर्घ)fout;
पूर्ण

अटल पूर्णांक samsung_pll2650x_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा samsung_pll_rate_table *rate;
	u32 con0, con1;

	/* Get required rate settings from table */
	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	con0 = पढ़ोl_relaxed(pll->con_reg);
	con1 = पढ़ोl_relaxed(pll->con_reg + 4);

	/* Set PLL lock समय. */
	ग_लिखोl_relaxed(rate->pभाग * PLL2650X_LOCK_FACTOR, pll->lock_reg);

	/* Change PLL PMS values */
	con0 &= ~((PLL2650X_M_MASK << PLL2650X_M_SHIFT) |
			(PLL2650X_P_MASK << PLL2650X_P_SHIFT) |
			(PLL2650X_S_MASK << PLL2650X_S_SHIFT));
	con0 |= (rate->mभाग << PLL2650X_M_SHIFT) |
			(rate->pभाग << PLL2650X_P_SHIFT) |
			(rate->sभाग << PLL2650X_S_SHIFT);
	con0 |= (1 << PLL2650X_PLL_ENABLE_SHIFT);
	ग_लिखोl_relaxed(con0, pll->con_reg);

	con1 &= ~(PLL2650X_K_MASK << PLL2650X_K_SHIFT);
	con1 |= ((rate->kभाग & PLL2650X_K_MASK) << PLL2650X_K_SHIFT);
	ग_लिखोl_relaxed(con1, pll->con_reg + 4);

	/* Wait क्रम PLL lock */
	वापस samsung_pll_lock_रुको(pll,
			PLL2650X_LOCK_STAT_MASK << PLL2650X_LOCK_STAT_SHIFT);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll2650x_clk_ops = अणु
	.recalc_rate = samsung_pll2650x_recalc_rate,
	.round_rate = samsung_pll_round_rate,
	.set_rate = samsung_pll2650x_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll2650x_clk_min_ops = अणु
	.recalc_rate = samsung_pll2650x_recalc_rate,
पूर्ण;

/*
 * PLL2650XX Clock Type
 */

/* Maximum lock समय can be 3000 * PDIV cycles */
#घोषणा PLL2650XX_LOCK_FACTOR 3000

#घोषणा PLL2650XX_MDIV_SHIFT		9
#घोषणा PLL2650XX_PDIV_SHIFT		3
#घोषणा PLL2650XX_SDIV_SHIFT		0
#घोषणा PLL2650XX_KDIV_SHIFT		0
#घोषणा PLL2650XX_MDIV_MASK		0x1ff
#घोषणा PLL2650XX_PDIV_MASK		0x3f
#घोषणा PLL2650XX_SDIV_MASK		0x7
#घोषणा PLL2650XX_KDIV_MASK		0xffff
#घोषणा PLL2650XX_PLL_ENABLE_SHIFT	23
#घोषणा PLL2650XX_PLL_LOCKTIME_SHIFT	21
#घोषणा PLL2650XX_PLL_FOUTMASK_SHIFT	31

अटल अचिन्हित दीर्घ samsung_pll2650xx_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mभाग, pभाग, sभाग, pll_con0, pll_con2;
	s16 kभाग;
	u64 fvco = parent_rate;

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con2 = पढ़ोl_relaxed(pll->con_reg + 8);
	mभाग = (pll_con0 >> PLL2650XX_MDIV_SHIFT) & PLL2650XX_MDIV_MASK;
	pभाग = (pll_con0 >> PLL2650XX_PDIV_SHIFT) & PLL2650XX_PDIV_MASK;
	sभाग = (pll_con0 >> PLL2650XX_SDIV_SHIFT) & PLL2650XX_SDIV_MASK;
	kभाग = (s16)(pll_con2 & PLL2650XX_KDIV_MASK);

	fvco *= (mभाग << 16) + kभाग;
	करो_भाग(fvco, (pभाग << sभाग));
	fvco >>= 16;

	वापस (अचिन्हित दीर्घ)fvco;
पूर्ण

अटल पूर्णांक samsung_pll2650xx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा samsung_clk_pll *pll = to_clk_pll(hw);
	u32 pll_con0, pll_con2;
	स्थिर काष्ठा samsung_pll_rate_table *rate;

	rate = samsung_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	pll_con0 = पढ़ोl_relaxed(pll->con_reg);
	pll_con2 = पढ़ोl_relaxed(pll->con_reg + 8);

	 /* Change PLL PMS values */
	pll_con0 &= ~(PLL2650XX_MDIV_MASK << PLL2650XX_MDIV_SHIFT |
			PLL2650XX_PDIV_MASK << PLL2650XX_PDIV_SHIFT |
			PLL2650XX_SDIV_MASK << PLL2650XX_SDIV_SHIFT);
	pll_con0 |= rate->mभाग << PLL2650XX_MDIV_SHIFT;
	pll_con0 |= rate->pभाग << PLL2650XX_PDIV_SHIFT;
	pll_con0 |= rate->sभाग << PLL2650XX_SDIV_SHIFT;
	pll_con0 |= 1 << PLL2650XX_PLL_ENABLE_SHIFT;
	pll_con0 |= 1 << PLL2650XX_PLL_FOUTMASK_SHIFT;

	pll_con2 &= ~(PLL2650XX_KDIV_MASK << PLL2650XX_KDIV_SHIFT);
	pll_con2 |= ((~(rate->kभाग) + 1) & PLL2650XX_KDIV_MASK)
			<< PLL2650XX_KDIV_SHIFT;

	/* Set PLL lock समय. */
	ग_लिखोl_relaxed(PLL2650XX_LOCK_FACTOR * rate->pभाग, pll->lock_reg);

	ग_लिखोl_relaxed(pll_con0, pll->con_reg);
	ग_लिखोl_relaxed(pll_con2, pll->con_reg + 8);

	वापस samsung_pll_lock_रुको(pll, 0x1 << PLL2650XX_PLL_LOCKTIME_SHIFT);
पूर्ण

अटल स्थिर काष्ठा clk_ops samsung_pll2650xx_clk_ops = अणु
	.recalc_rate = samsung_pll2650xx_recalc_rate,
	.set_rate = samsung_pll2650xx_set_rate,
	.round_rate = samsung_pll_round_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops samsung_pll2650xx_clk_min_ops = अणु
	.recalc_rate = samsung_pll2650xx_recalc_rate,
पूर्ण;

अटल व्योम __init _samsung_clk_रेजिस्टर_pll(काष्ठा samsung_clk_provider *ctx,
				स्थिर काष्ठा samsung_pll_घड़ी *pll_clk,
				व्योम __iomem *base)
अणु
	काष्ठा samsung_clk_pll *pll;
	काष्ठा clk_init_data init;
	पूर्णांक ret, len;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll) अणु
		pr_err("%s: could not allocate pll clk %s\n",
			__func__, pll_clk->name);
		वापस;
	पूर्ण

	init.name = pll_clk->name;
	init.flags = pll_clk->flags;
	init.parent_names = &pll_clk->parent_name;
	init.num_parents = 1;

	अगर (pll_clk->rate_table) अणु
		/* find count of rates in rate_table */
		क्रम (len = 0; pll_clk->rate_table[len].rate != 0; )
			len++;

		pll->rate_count = len;
		pll->rate_table = kmemdup(pll_clk->rate_table,
					pll->rate_count *
					माप(काष्ठा samsung_pll_rate_table),
					GFP_KERNEL);
		WARN(!pll->rate_table,
			"%s: could not allocate rate table for %s\n",
			__func__, pll_clk->name);
	पूर्ण

	चयन (pll_clk->type) अणु
	हाल pll_2126:
		init.ops = &samsung_pll2126_clk_ops;
		अवरोध;
	हाल pll_3000:
		init.ops = &samsung_pll3000_clk_ops;
		अवरोध;
	/* clk_ops क्रम 35xx and 2550 are similar */
	हाल pll_35xx:
	हाल pll_2550:
	हाल pll_1450x:
	हाल pll_1451x:
	हाल pll_1452x:
		pll->enable_offs = PLL35XX_ENABLE_SHIFT;
		pll->lock_offs = PLL35XX_LOCK_STAT_SHIFT;
		अगर (!pll->rate_table)
			init.ops = &samsung_pll35xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll35xx_clk_ops;
		अवरोध;
	हाल pll_4500:
		init.ops = &samsung_pll45xx_clk_min_ops;
		अवरोध;
	हाल pll_4502:
	हाल pll_4508:
		अगर (!pll->rate_table)
			init.ops = &samsung_pll45xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll45xx_clk_ops;
		अवरोध;
	/* clk_ops क्रम 36xx and 2650 are similar */
	हाल pll_36xx:
	हाल pll_2650:
		pll->enable_offs = PLL36XX_ENABLE_SHIFT;
		pll->lock_offs = PLL36XX_LOCK_STAT_SHIFT;
		अगर (!pll->rate_table)
			init.ops = &samsung_pll36xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll36xx_clk_ops;
		अवरोध;
	हाल pll_6552:
	हाल pll_6552_s3c2416:
		init.ops = &samsung_pll6552_clk_ops;
		अवरोध;
	हाल pll_6553:
		init.ops = &samsung_pll6553_clk_ops;
		अवरोध;
	हाल pll_4600:
	हाल pll_4650:
	हाल pll_4650c:
	हाल pll_1460x:
		अगर (!pll->rate_table)
			init.ops = &samsung_pll46xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll46xx_clk_ops;
		अवरोध;
	हाल pll_s3c2410_mpll:
		अगर (!pll->rate_table)
			init.ops = &samsung_s3c2410_mpll_clk_min_ops;
		अन्यथा
			init.ops = &samsung_s3c2410_mpll_clk_ops;
		अवरोध;
	हाल pll_s3c2410_upll:
		अगर (!pll->rate_table)
			init.ops = &samsung_s3c2410_upll_clk_min_ops;
		अन्यथा
			init.ops = &samsung_s3c2410_upll_clk_ops;
		अवरोध;
	हाल pll_s3c2440_mpll:
		अगर (!pll->rate_table)
			init.ops = &samsung_s3c2440_mpll_clk_min_ops;
		अन्यथा
			init.ops = &samsung_s3c2440_mpll_clk_ops;
		अवरोध;
	हाल pll_2550x:
		init.ops = &samsung_pll2550x_clk_ops;
		अवरोध;
	हाल pll_2550xx:
		अगर (!pll->rate_table)
			init.ops = &samsung_pll2550xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll2550xx_clk_ops;
		अवरोध;
	हाल pll_2650x:
		अगर (!pll->rate_table)
			init.ops = &samsung_pll2650x_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll2650x_clk_ops;
		अवरोध;
	हाल pll_2650xx:
		अगर (!pll->rate_table)
			init.ops = &samsung_pll2650xx_clk_min_ops;
		अन्यथा
			init.ops = &samsung_pll2650xx_clk_ops;
		अवरोध;
	शेष:
		pr_warn("%s: Unknown pll type for pll clk %s\n",
			__func__, pll_clk->name);
	पूर्ण

	pll->hw.init = &init;
	pll->type = pll_clk->type;
	pll->lock_reg = base + pll_clk->lock_offset;
	pll->con_reg = base + pll_clk->con_offset;

	ret = clk_hw_रेजिस्टर(ctx->dev, &pll->hw);
	अगर (ret) अणु
		pr_err("%s: failed to register pll clock %s : %d\n",
			__func__, pll_clk->name, ret);
		kमुक्त(pll);
		वापस;
	पूर्ण

	samsung_clk_add_lookup(ctx, &pll->hw, pll_clk->id);
पूर्ण

व्योम __init samsung_clk_रेजिस्टर_pll(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_pll_घड़ी *pll_list,
			अचिन्हित पूर्णांक nr_pll, व्योम __iomem *base)
अणु
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < nr_pll; cnt++)
		_samsung_clk_रेजिस्टर_pll(ctx, &pll_list[cnt], base);
पूर्ण
