<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>

#समावेश "clk-mtk.h"

#घोषणा REG_CON0		0
#घोषणा REG_CON1		4

#घोषणा CON0_BASE_EN		BIT(0)
#घोषणा CON0_PWR_ON		BIT(0)
#घोषणा CON0_ISO_EN		BIT(1)
#घोषणा PCW_CHG_MASK		BIT(31)

#घोषणा AUDPLL_TUNER_EN		BIT(31)

#घोषणा POSTDIV_MASK		0x7

/* शेष 7 bits पूर्णांकeger, can be overridden with pcwibits. */
#घोषणा INTEGER_BITS		7

/*
 * MediaTek PLLs are configured through their pcw value. The pcw value describes
 * a भागider in the PLL feedback loop which consists of 7 bits क्रम the पूर्णांकeger
 * part and the reमुख्यing bits (अगर present) क्रम the fractional part. Also they
 * have a 3 bit घातer-of-two post भागider.
 */

काष्ठा mtk_clk_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base_addr;
	व्योम __iomem	*pd_addr;
	व्योम __iomem	*pwr_addr;
	व्योम __iomem	*tuner_addr;
	व्योम __iomem	*tuner_en_addr;
	व्योम __iomem	*pcw_addr;
	व्योम __iomem	*pcw_chg_addr;
	स्थिर काष्ठा mtk_pll_data *data;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_clk_pll *to_mtk_clk_pll(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_clk_pll, hw);
पूर्ण

अटल पूर्णांक mtk_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);

	वापस (पढ़ोl(pll->base_addr + REG_CON0) & CON0_BASE_EN) != 0;
पूर्ण

अटल अचिन्हित दीर्घ __mtk_pll_recalc_rate(काष्ठा mtk_clk_pll *pll, u32 fin,
		u32 pcw, पूर्णांक postभाग)
अणु
	पूर्णांक pcwbits = pll->data->pcwbits;
	पूर्णांक pcwfbits = 0;
	पूर्णांक ibits;
	u64 vco;
	u8 c = 0;

	/* The fractional part of the PLL भागider. */
	ibits = pll->data->pcwibits ? pll->data->pcwibits : INTEGER_BITS;
	अगर (pcwbits > ibits)
		pcwfbits = pcwbits - ibits;

	vco = (u64)fin * pcw;

	अगर (pcwfbits && (vco & GENMASK(pcwfbits - 1, 0)))
		c = 1;

	vco >>= pcwfbits;

	अगर (c)
		vco++;

	वापस ((अचिन्हित दीर्घ)vco + postभाग - 1) / postभाग;
पूर्ण

अटल व्योम __mtk_pll_tuner_enable(काष्ठा mtk_clk_pll *pll)
अणु
	u32 r;

	अगर (pll->tuner_en_addr) अणु
		r = पढ़ोl(pll->tuner_en_addr) | BIT(pll->data->tuner_en_bit);
		ग_लिखोl(r, pll->tuner_en_addr);
	पूर्ण अन्यथा अगर (pll->tuner_addr) अणु
		r = पढ़ोl(pll->tuner_addr) | AUDPLL_TUNER_EN;
		ग_लिखोl(r, pll->tuner_addr);
	पूर्ण
पूर्ण

अटल व्योम __mtk_pll_tuner_disable(काष्ठा mtk_clk_pll *pll)
अणु
	u32 r;

	अगर (pll->tuner_en_addr) अणु
		r = पढ़ोl(pll->tuner_en_addr) & ~BIT(pll->data->tuner_en_bit);
		ग_लिखोl(r, pll->tuner_en_addr);
	पूर्ण अन्यथा अगर (pll->tuner_addr) अणु
		r = पढ़ोl(pll->tuner_addr) & ~AUDPLL_TUNER_EN;
		ग_लिखोl(r, pll->tuner_addr);
	पूर्ण
पूर्ण

अटल व्योम mtk_pll_set_rate_regs(काष्ठा mtk_clk_pll *pll, u32 pcw,
		पूर्णांक postभाग)
अणु
	u32 chg, val;

	/* disable tuner */
	__mtk_pll_tuner_disable(pll);

	/* set postभाग */
	val = पढ़ोl(pll->pd_addr);
	val &= ~(POSTDIV_MASK << pll->data->pd_shअगरt);
	val |= (ffs(postभाग) - 1) << pll->data->pd_shअगरt;

	/* postभाग and pcw need to set at the same समय अगर on same रेजिस्टर */
	अगर (pll->pd_addr != pll->pcw_addr) अणु
		ग_लिखोl(val, pll->pd_addr);
		val = पढ़ोl(pll->pcw_addr);
	पूर्ण

	/* set pcw */
	val &= ~GENMASK(pll->data->pcw_shअगरt + pll->data->pcwbits - 1,
			pll->data->pcw_shअगरt);
	val |= pcw << pll->data->pcw_shअगरt;
	ग_लिखोl(val, pll->pcw_addr);
	chg = पढ़ोl(pll->pcw_chg_addr) | PCW_CHG_MASK;
	ग_लिखोl(chg, pll->pcw_chg_addr);
	अगर (pll->tuner_addr)
		ग_लिखोl(val + 1, pll->tuner_addr);

	/* restore tuner_en */
	__mtk_pll_tuner_enable(pll);

	udelay(20);
पूर्ण

/*
 * mtk_pll_calc_values - calculate good values क्रम a given input frequency.
 * @pll:	The pll
 * @pcw:	The pcw value (output)
 * @postभाग:	The post भागider (output)
 * @freq:	The desired target frequency
 * @fin:	The input frequency
 *
 */
अटल व्योम mtk_pll_calc_values(काष्ठा mtk_clk_pll *pll, u32 *pcw, u32 *postभाग,
		u32 freq, u32 fin)
अणु
	अचिन्हित दीर्घ fmin = pll->data->fmin ? pll->data->fmin : (1000 * MHZ);
	स्थिर काष्ठा mtk_pll_भाग_प्रकारable *भाग_प्रकारable = pll->data->भाग_प्रकारable;
	u64 _pcw;
	पूर्णांक ibits;
	u32 val;

	अगर (freq > pll->data->fmax)
		freq = pll->data->fmax;

	अगर (भाग_प्रकारable) अणु
		अगर (freq > भाग_प्रकारable[0].freq)
			freq = भाग_प्रकारable[0].freq;

		क्रम (val = 0; भाग_प्रकारable[val + 1].freq != 0; val++) अणु
			अगर (freq > भाग_प्रकारable[val + 1].freq)
				अवरोध;
		पूर्ण
		*postभाग = 1 << val;
	पूर्ण अन्यथा अणु
		क्रम (val = 0; val < 5; val++) अणु
			*postभाग = 1 << val;
			अगर ((u64)freq * *postभाग >= fmin)
				अवरोध;
		पूर्ण
	पूर्ण

	/* _pcw = freq * postभाग / fin * 2^pcwfbits */
	ibits = pll->data->pcwibits ? pll->data->pcwibits : INTEGER_BITS;
	_pcw = ((u64)freq << val) << (pll->data->pcwbits - ibits);
	करो_भाग(_pcw, fin);

	*pcw = (u32)_pcw;
पूर्ण

अटल पूर्णांक mtk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 pcw = 0;
	u32 postभाग;

	mtk_pll_calc_values(pll, &pcw, &postभाग, rate, parent_rate);
	mtk_pll_set_rate_regs(pll, pcw, postभाग);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ mtk_pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 postभाग;
	u32 pcw;

	postभाग = (पढ़ोl(pll->pd_addr) >> pll->data->pd_shअगरt) & POSTDIV_MASK;
	postभाग = 1 << postभाग;

	pcw = पढ़ोl(pll->pcw_addr) >> pll->data->pcw_shअगरt;
	pcw &= GENMASK(pll->data->pcwbits - 1, 0);

	वापस __mtk_pll_recalc_rate(pll, parent_rate, pcw, postभाग);
पूर्ण

अटल दीर्घ mtk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 pcw = 0;
	पूर्णांक postभाग;

	mtk_pll_calc_values(pll, &pcw, &postभाग, rate, *prate);

	वापस __mtk_pll_recalc_rate(pll, *prate, pcw, postभाग);
पूर्ण

अटल पूर्णांक mtk_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 r;

	r = पढ़ोl(pll->pwr_addr) | CON0_PWR_ON;
	ग_लिखोl(r, pll->pwr_addr);
	udelay(1);

	r = पढ़ोl(pll->pwr_addr) & ~CON0_ISO_EN;
	ग_लिखोl(r, pll->pwr_addr);
	udelay(1);

	r = पढ़ोl(pll->base_addr + REG_CON0);
	r |= pll->data->en_mask;
	ग_लिखोl(r, pll->base_addr + REG_CON0);

	__mtk_pll_tuner_enable(pll);

	udelay(20);

	अगर (pll->data->flags & HAVE_RST_BAR) अणु
		r = पढ़ोl(pll->base_addr + REG_CON0);
		r |= pll->data->rst_bar_mask;
		ग_लिखोl(r, pll->base_addr + REG_CON0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 r;

	अगर (pll->data->flags & HAVE_RST_BAR) अणु
		r = पढ़ोl(pll->base_addr + REG_CON0);
		r &= ~pll->data->rst_bar_mask;
		ग_लिखोl(r, pll->base_addr + REG_CON0);
	पूर्ण

	__mtk_pll_tuner_disable(pll);

	r = पढ़ोl(pll->base_addr + REG_CON0);
	r &= ~CON0_BASE_EN;
	ग_लिखोl(r, pll->base_addr + REG_CON0);

	r = पढ़ोl(pll->pwr_addr) | CON0_ISO_EN;
	ग_लिखोl(r, pll->pwr_addr);

	r = पढ़ोl(pll->pwr_addr) & ~CON0_PWR_ON;
	ग_लिखोl(r, pll->pwr_addr);
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_pll_ops = अणु
	.is_prepared	= mtk_pll_is_prepared,
	.prepare	= mtk_pll_prepare,
	.unprepare	= mtk_pll_unprepare,
	.recalc_rate	= mtk_pll_recalc_rate,
	.round_rate	= mtk_pll_round_rate,
	.set_rate	= mtk_pll_set_rate,
पूर्ण;

अटल काष्ठा clk *mtk_clk_रेजिस्टर_pll(स्थिर काष्ठा mtk_pll_data *data,
		व्योम __iomem *base)
अणु
	काष्ठा mtk_clk_pll *pll;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name = "clk26m";

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->base_addr = base + data->reg;
	pll->pwr_addr = base + data->pwr_reg;
	pll->pd_addr = base + data->pd_reg;
	pll->pcw_addr = base + data->pcw_reg;
	अगर (data->pcw_chg_reg)
		pll->pcw_chg_addr = base + data->pcw_chg_reg;
	अन्यथा
		pll->pcw_chg_addr = pll->base_addr + REG_CON1;
	अगर (data->tuner_reg)
		pll->tuner_addr = base + data->tuner_reg;
	अगर (data->tuner_en_reg)
		pll->tuner_en_addr = base + data->tuner_en_reg;
	pll->hw.init = &init;
	pll->data = data;

	init.name = data->name;
	init.flags = (data->flags & PLL_AO) ? CLK_IS_CRITICAL : 0;
	init.ops = &mtk_pll_ops;
	अगर (data->parent_name)
		init.parent_names = &data->parent_name;
	अन्यथा
		init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);

	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

व्योम mtk_clk_रेजिस्टर_plls(काष्ठा device_node *node,
		स्थिर काष्ठा mtk_pll_data *plls, पूर्णांक num_plls, काष्ठा clk_onecell_data *clk_data)
अणु
	व्योम __iomem *base;
	पूर्णांक i;
	काष्ठा clk *clk;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%s(): ioremap failed\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_plls; i++) अणु
		स्थिर काष्ठा mtk_pll_data *pll = &plls[i];

		clk = mtk_clk_रेजिस्टर_pll(pll, base);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
					pll->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		clk_data->clks[pll->id] = clk;
	पूर्ण
पूर्ण
