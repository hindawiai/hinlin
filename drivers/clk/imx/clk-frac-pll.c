<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018 NXP.
 *
 * This driver supports the fractional plls found in the imx8m SOCs
 *
 * Documentation क्रम this fractional pll can be found at:
 *   https://www.nxp.com/करोcs/en/reference-manual/IMX8MDQLQRM.pdf#page=834
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>

#समावेश "clk.h"

#घोषणा PLL_CFG0		0x0
#घोषणा PLL_CFG1		0x4

#घोषणा PLL_LOCK_STATUS		BIT(31)
#घोषणा PLL_PD_MASK		BIT(19)
#घोषणा PLL_BYPASS_MASK		BIT(14)
#घोषणा PLL_NEWDIV_VAL		BIT(12)
#घोषणा PLL_NEWDIV_ACK		BIT(11)
#घोषणा PLL_FRAC_DIV_MASK	GENMASK(30, 7)
#घोषणा PLL_INT_DIV_MASK	GENMASK(6, 0)
#घोषणा PLL_OUTPUT_DIV_MASK	GENMASK(4, 0)
#घोषणा PLL_FRAC_DENOM		0x1000000

#घोषणा PLL_FRAC_LOCK_TIMEOUT	10000
#घोषणा PLL_FRAC_ACK_TIMEOUT	500000

काष्ठा clk_frac_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base;
पूर्ण;

#घोषणा to_clk_frac_pll(_hw) container_of(_hw, काष्ठा clk_frac_pll, hw)

अटल पूर्णांक clk_रुको_lock(काष्ठा clk_frac_pll *pll)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(pll->base, val, val & PLL_LOCK_STATUS, 0,
					PLL_FRAC_LOCK_TIMEOUT);
पूर्ण

अटल पूर्णांक clk_रुको_ack(काष्ठा clk_frac_pll *pll)
अणु
	u32 val;

	/* वापस directly अगर the pll is in घातerकरोwn or in bypass */
	अगर (पढ़ोl_relaxed(pll->base) & (PLL_PD_MASK | PLL_BYPASS_MASK))
		वापस 0;

	/* Wait क्रम the pll's भागfi and भागff to be reloaded */
	वापस पढ़ोl_poll_समयout(pll->base, val, val & PLL_NEWDIV_ACK, 0,
					PLL_FRAC_ACK_TIMEOUT);
पूर्ण

अटल पूर्णांक clk_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val &= ~PLL_PD_MASK;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);

	वापस clk_रुको_lock(pll);
पूर्ण

अटल व्योम clk_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val |= PLL_PD_MASK;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);
पूर्ण

अटल पूर्णांक clk_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	वापस (val & PLL_PD_MASK) ? 0 : 1;
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val, भागff, भागfi, भागq;
	u64 temp64 = parent_rate;
	u64 rate;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	भागq = (FIELD_GET(PLL_OUTPUT_DIV_MASK, val) + 1) * 2;
	val = पढ़ोl_relaxed(pll->base + PLL_CFG1);
	भागff = FIELD_GET(PLL_FRAC_DIV_MASK, val);
	भागfi = FIELD_GET(PLL_INT_DIV_MASK, val);

	temp64 *= 8;
	temp64 *= भागff;
	करो_भाग(temp64, PLL_FRAC_DENOM);
	करो_भाग(temp64, भागq);

	rate = parent_rate * 8 * (भागfi + 1);
	करो_भाग(rate, भागq);
	rate += temp64;

	वापस rate;
पूर्ण

अटल दीर्घ clk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	u64 parent_rate = *prate;
	u32 भागff, भागfi;
	u64 temp64;

	parent_rate *= 8;
	rate *= 2;
	temp64 = rate;
	करो_भाग(temp64, parent_rate);
	भागfi = temp64;
	temp64 = rate - भागfi * parent_rate;
	temp64 *= PLL_FRAC_DENOM;
	करो_भाग(temp64, parent_rate);
	भागff = temp64;

	temp64 = parent_rate;
	temp64 *= भागff;
	करो_भाग(temp64, PLL_FRAC_DENOM);

	rate = parent_rate * भागfi + temp64;

	वापस rate / 2;
पूर्ण

/*
 * To simplअगरy the घड़ी calculation, we can keep the 'PLL_OUTPUT_VAL' at zero
 * (means the PLL output will be भागided by 2). So the PLL output can use
 * the below क्रमmula:
 * pllout = parent_rate * 8 / 2 * DIVF_VAL;
 * where DIVF_VAL = 1 + DIVFI + DIVFF / 2^24.
 */
अटल पूर्णांक clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val, भागfi, भागff;
	u64 temp64;
	पूर्णांक ret;

	parent_rate *= 8;
	rate *= 2;
	भागfi = rate / parent_rate;
	temp64 = parent_rate * भागfi;
	temp64 = rate - temp64;
	temp64 *= PLL_FRAC_DENOM;
	करो_भाग(temp64, parent_rate);
	भागff = temp64;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG1);
	val &= ~(PLL_FRAC_DIV_MASK | PLL_INT_DIV_MASK);
	val |= (भागff << 7) | (भागfi - 1);
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG1);

	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val &= ~0x1f;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);

	/* Set the NEV_DIV_VAL to reload the DIVFI and DIVFF */
	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val |= PLL_NEWDIV_VAL;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);

	ret = clk_रुको_ack(pll);

	/* clear the NEV_DIV_VAL */
	val = पढ़ोl_relaxed(pll->base + PLL_CFG0);
	val &= ~PLL_NEWDIV_VAL;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG0);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_frac_pll_ops = अणु
	.prepare	= clk_pll_prepare,
	.unprepare	= clk_pll_unprepare,
	.is_prepared	= clk_pll_is_prepared,
	.recalc_rate	= clk_pll_recalc_rate,
	.round_rate	= clk_pll_round_rate,
	.set_rate	= clk_pll_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_frac_pll(स्थिर अक्षर *name,
				   स्थिर अक्षर *parent_name,
				   व्योम __iomem *base)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_frac_pll *pll;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_frac_pll_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	pll->base = base;
	pll->hw.init = &init;

	hw = &pll->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(imx_clk_hw_frac_pll);
