<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ingenic SoC CGU driver
 *
 * Copyright (c) 2013-2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>

#समावेश "cgu.h"

#घोषणा MHZ (1000 * 1000)

अटल अंतरभूत स्थिर काष्ठा ingenic_cgu_clk_info *
to_clk_info(काष्ठा ingenic_clk *clk)
अणु
	वापस &clk->cgu->घड़ी_info[clk->idx];
पूर्ण

/**
 * ingenic_cgu_gate_get() - get the value of घड़ी gate रेजिस्टर bit
 * @cgu: reference to the CGU whose रेजिस्टरs should be पढ़ो
 * @info: info काष्ठा describing the gate bit
 *
 * Retrieves the state of the घड़ी gate bit described by info. The
 * caller must hold cgu->lock.
 *
 * Return: true अगर the gate bit is set, अन्यथा false.
 */
अटल अंतरभूत bool
ingenic_cgu_gate_get(काष्ठा ingenic_cgu *cgu,
		     स्थिर काष्ठा ingenic_cgu_gate_info *info)
अणु
	वापस !!(पढ़ोl(cgu->base + info->reg) & BIT(info->bit))
		^ info->clear_to_gate;
पूर्ण

/**
 * ingenic_cgu_gate_set() - set the value of घड़ी gate रेजिस्टर bit
 * @cgu: reference to the CGU whose रेजिस्टरs should be modअगरied
 * @info: info काष्ठा describing the gate bit
 * @val: non-zero to gate a घड़ी, otherwise zero
 *
 * Sets the given gate bit in order to gate or ungate a घड़ी.
 *
 * The caller must hold cgu->lock.
 */
अटल अंतरभूत व्योम
ingenic_cgu_gate_set(काष्ठा ingenic_cgu *cgu,
		     स्थिर काष्ठा ingenic_cgu_gate_info *info, bool val)
अणु
	u32 clkgr = पढ़ोl(cgu->base + info->reg);

	अगर (val ^ info->clear_to_gate)
		clkgr |= BIT(info->bit);
	अन्यथा
		clkgr &= ~BIT(info->bit);

	ग_लिखोl(clkgr, cgu->base + info->reg);
पूर्ण

/*
 * PLL operations
 */

अटल अचिन्हित दीर्घ
ingenic_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info;
	अचिन्हित m, n, od_enc, od;
	bool bypass;
	u32 ctl;

	BUG_ON(clk_info->type != CGU_CLK_PLL);
	pll_info = &clk_info->pll;

	ctl = पढ़ोl(cgu->base + pll_info->reg);

	m = (ctl >> pll_info->m_shअगरt) & GENMASK(pll_info->m_bits - 1, 0);
	m += pll_info->m_offset;
	n = (ctl >> pll_info->n_shअगरt) & GENMASK(pll_info->n_bits - 1, 0);
	n += pll_info->n_offset;
	od_enc = ctl >> pll_info->od_shअगरt;
	od_enc &= GENMASK(pll_info->od_bits - 1, 0);

	ctl = पढ़ोl(cgu->base + pll_info->bypass_reg);

	bypass = !pll_info->no_bypass_bit &&
		 !!(ctl & BIT(pll_info->bypass_bit));

	अगर (bypass)
		वापस parent_rate;

	क्रम (od = 0; od < pll_info->od_max; od++) अणु
		अगर (pll_info->od_encoding[od] == od_enc)
			अवरोध;
	पूर्ण
	BUG_ON(od == pll_info->od_max);
	od++;

	वापस भाग_u64((u64)parent_rate * m * pll_info->rate_multiplier,
		n * od);
पूर्ण

अटल अचिन्हित दीर्घ
ingenic_pll_calc(स्थिर काष्ठा ingenic_cgu_clk_info *clk_info,
		 अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
		 अचिन्हित *pm, अचिन्हित *pn, अचिन्हित *pod)
अणु
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info;
	अचिन्हित m, n, od;

	pll_info = &clk_info->pll;
	od = 1;

	/*
	 * The frequency after the input भागider must be between 10 and 50 MHz.
	 * The highest भागider yields the best resolution.
	 */
	n = parent_rate / (10 * MHZ);
	n = min_t(अचिन्हित, n, 1 << clk_info->pll.n_bits);
	n = max_t(अचिन्हित, n, pll_info->n_offset);

	m = (rate / MHZ) * od * n / (parent_rate / MHZ);
	m = min_t(अचिन्हित, m, 1 << clk_info->pll.m_bits);
	m = max_t(अचिन्हित, m, pll_info->m_offset);

	अगर (pm)
		*pm = m;
	अगर (pn)
		*pn = n;
	अगर (pod)
		*pod = od;

	वापस भाग_u64((u64)parent_rate * m * pll_info->rate_multiplier,
		n * od);
पूर्ण

अटल दीर्घ
ingenic_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		       अचिन्हित दीर्घ *prate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);

	वापस ingenic_pll_calc(clk_info, req_rate, *prate, शून्य, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक ingenic_pll_check_stable(काष्ठा ingenic_cgu *cgu,
					   स्थिर काष्ठा ingenic_cgu_pll_info *pll_info)
अणु
	u32 ctl;

	वापस पढ़ोl_poll_समयout(cgu->base + pll_info->reg, ctl,
				  ctl & BIT(pll_info->stable_bit),
				  0, 100 * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक
ingenic_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	अचिन्हित दीर्घ rate, flags;
	अचिन्हित पूर्णांक m, n, od;
	पूर्णांक ret = 0;
	u32 ctl;

	rate = ingenic_pll_calc(clk_info, req_rate, parent_rate,
			       &m, &n, &od);
	अगर (rate != req_rate)
		pr_info("ingenic-cgu: request '%s' rate %luHz, actual %luHz\n",
			clk_info->name, req_rate, rate);

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = पढ़ोl(cgu->base + pll_info->reg);

	ctl &= ~(GENMASK(pll_info->m_bits - 1, 0) << pll_info->m_shअगरt);
	ctl |= (m - pll_info->m_offset) << pll_info->m_shअगरt;

	ctl &= ~(GENMASK(pll_info->n_bits - 1, 0) << pll_info->n_shअगरt);
	ctl |= (n - pll_info->n_offset) << pll_info->n_shअगरt;

	ctl &= ~(GENMASK(pll_info->od_bits - 1, 0) << pll_info->od_shअगरt);
	ctl |= pll_info->od_encoding[od - 1] << pll_info->od_shअगरt;

	ग_लिखोl(ctl, cgu->base + pll_info->reg);

	/* If the PLL is enabled, verअगरy that it's stable */
	अगर (ctl & BIT(pll_info->enable_bit))
		ret = ingenic_pll_check_stable(cgu, pll_info);

	spin_unlock_irqrestore(&cgu->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 ctl;

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = पढ़ोl(cgu->base + pll_info->bypass_reg);

	ctl &= ~BIT(pll_info->bypass_bit);

	ग_लिखोl(ctl, cgu->base + pll_info->bypass_reg);

	ctl = पढ़ोl(cgu->base + pll_info->reg);

	ctl |= BIT(pll_info->enable_bit);

	ग_लिखोl(ctl, cgu->base + pll_info->reg);

	ret = ingenic_pll_check_stable(cgu, pll_info);
	spin_unlock_irqrestore(&cgu->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ingenic_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	अचिन्हित दीर्घ flags;
	u32 ctl;

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = पढ़ोl(cgu->base + pll_info->reg);

	ctl &= ~BIT(pll_info->enable_bit);

	ग_लिखोl(ctl, cgu->base + pll_info->reg);
	spin_unlock_irqrestore(&cgu->lock, flags);
पूर्ण

अटल पूर्णांक ingenic_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	स्थिर काष्ठा ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	u32 ctl;

	ctl = पढ़ोl(cgu->base + pll_info->reg);

	वापस !!(ctl & BIT(pll_info->enable_bit));
पूर्ण

अटल स्थिर काष्ठा clk_ops ingenic_pll_ops = अणु
	.recalc_rate = ingenic_pll_recalc_rate,
	.round_rate = ingenic_pll_round_rate,
	.set_rate = ingenic_pll_set_rate,

	.enable = ingenic_pll_enable,
	.disable = ingenic_pll_disable,
	.is_enabled = ingenic_pll_is_enabled,
पूर्ण;

/*
 * Operations क्रम all non-PLL घड़ीs
 */

अटल u8 ingenic_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	u32 reg;
	u8 i, hw_idx, idx = 0;

	अगर (clk_info->type & CGU_CLK_MUX) अणु
		reg = पढ़ोl(cgu->base + clk_info->mux.reg);
		hw_idx = (reg >> clk_info->mux.shअगरt) &
			 GENMASK(clk_info->mux.bits - 1, 0);

		/*
		 * Convert the hardware index to the parent index by skipping
		 * over any -1's in the parents array.
		 */
		क्रम (i = 0; i < hw_idx; i++) अणु
			अगर (clk_info->parents[i] != -1)
				idx++;
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक ingenic_clk_set_parent(काष्ठा clk_hw *hw, u8 idx)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	अचिन्हित दीर्घ flags;
	u8 curr_idx, hw_idx, num_poss;
	u32 reg, mask;

	अगर (clk_info->type & CGU_CLK_MUX) अणु
		/*
		 * Convert the parent index to the hardware index by adding
		 * 1 क्रम any -1 in the parents array preceding the given
		 * index. That is, we want the index of idx'th entry in
		 * clk_info->parents which करोes not equal -1.
		 */
		hw_idx = curr_idx = 0;
		num_poss = 1 << clk_info->mux.bits;
		क्रम (; hw_idx < num_poss; hw_idx++) अणु
			अगर (clk_info->parents[hw_idx] == -1)
				जारी;
			अगर (curr_idx == idx)
				अवरोध;
			curr_idx++;
		पूर्ण

		/* idx should always be a valid parent */
		BUG_ON(curr_idx != idx);

		mask = GENMASK(clk_info->mux.bits - 1, 0);
		mask <<= clk_info->mux.shअगरt;

		spin_lock_irqsave(&cgu->lock, flags);

		/* ग_लिखो the रेजिस्टर */
		reg = पढ़ोl(cgu->base + clk_info->mux.reg);
		reg &= ~mask;
		reg |= hw_idx << clk_info->mux.shअगरt;
		ग_लिखोl(reg, cgu->base + clk_info->mux.reg);

		spin_unlock_irqrestore(&cgu->lock, flags);
		वापस 0;
	पूर्ण

	वापस idx ? -EINVAL : 0;
पूर्ण

अटल अचिन्हित दीर्घ
ingenic_clk_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	अचिन्हित दीर्घ rate = parent_rate;
	u32 भाग_reg, भाग;

	अगर (clk_info->type & CGU_CLK_DIV) अणु
		भाग_reg = पढ़ोl(cgu->base + clk_info->भाग.reg);
		भाग = (भाग_reg >> clk_info->भाग.shअगरt) &
		      GENMASK(clk_info->भाग.bits - 1, 0);

		अगर (clk_info->भाग.भाग_प्रकारable)
			भाग = clk_info->भाग.भाग_प्रकारable[भाग];
		अन्यथा
			भाग = (भाग + 1) * clk_info->भाग.भाग;

		rate /= भाग;
	पूर्ण अन्यथा अगर (clk_info->type & CGU_CLK_FIXDIV) अणु
		rate /= clk_info->fixभाग.भाग;
	पूर्ण

	वापस rate;
पूर्ण

अटल अचिन्हित पूर्णांक
ingenic_clk_calc_hw_भाग(स्थिर काष्ठा ingenic_cgu_clk_info *clk_info,
			अचिन्हित पूर्णांक भाग)
अणु
	अचिन्हित पूर्णांक i, best_i = 0, best = (अचिन्हित पूर्णांक)-1;

	क्रम (i = 0; i < (1 << clk_info->भाग.bits)
				&& clk_info->भाग.भाग_प्रकारable[i]; i++) अणु
		अगर (clk_info->भाग.भाग_प्रकारable[i] >= भाग &&
		    clk_info->भाग.भाग_प्रकारable[i] < best) अणु
			best = clk_info->भाग.भाग_प्रकारable[i];
			best_i = i;

			अगर (भाग == best)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस best_i;
पूर्ण

अटल अचिन्हित
ingenic_clk_calc_भाग(स्थिर काष्ठा ingenic_cgu_clk_info *clk_info,
		     अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ req_rate)
अणु
	अचिन्हित पूर्णांक भाग, hw_भाग;

	/* calculate the भागide */
	भाग = DIV_ROUND_UP(parent_rate, req_rate);

	अगर (clk_info->भाग.भाग_प्रकारable) अणु
		hw_भाग = ingenic_clk_calc_hw_भाग(clk_info, भाग);

		वापस clk_info->भाग.भाग_प्रकारable[hw_भाग];
	पूर्ण

	/* Impose hardware स्थिरraपूर्णांकs */
	भाग = min_t(अचिन्हित, भाग, 1 << clk_info->भाग.bits);
	भाग = max_t(अचिन्हित, भाग, 1);

	/*
	 * If the भागider value itself must be भागided beक्रमe being written to
	 * the भागider रेजिस्टर, we must ensure we करोn't have any bits set that
	 * would be lost as a result of करोing so.
	 */
	भाग /= clk_info->भाग.भाग;
	भाग *= clk_info->भाग.भाग;

	वापस भाग;
पूर्ण

अटल दीर्घ
ingenic_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		       अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	अचिन्हित पूर्णांक भाग = 1;

	अगर (clk_info->type & CGU_CLK_DIV)
		भाग = ingenic_clk_calc_भाग(clk_info, *parent_rate, req_rate);
	अन्यथा अगर (clk_info->type & CGU_CLK_FIXDIV)
		भाग = clk_info->fixभाग.भाग;
	अन्यथा अगर (clk_hw_can_set_rate_parent(hw))
		*parent_rate = req_rate;

	वापस DIV_ROUND_UP(*parent_rate, भाग);
पूर्ण

अटल अंतरभूत पूर्णांक ingenic_clk_check_stable(काष्ठा ingenic_cgu *cgu,
					   स्थिर काष्ठा ingenic_cgu_clk_info *clk_info)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(cgu->base + clk_info->भाग.reg, reg,
				  !(reg & BIT(clk_info->भाग.busy_bit)),
				  0, 100 * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक
ingenic_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	अचिन्हित दीर्घ rate, flags;
	अचिन्हित पूर्णांक hw_भाग, भाग;
	u32 reg, mask;
	पूर्णांक ret = 0;

	अगर (clk_info->type & CGU_CLK_DIV) अणु
		भाग = ingenic_clk_calc_भाग(clk_info, parent_rate, req_rate);
		rate = DIV_ROUND_UP(parent_rate, भाग);

		अगर (rate != req_rate)
			वापस -EINVAL;

		अगर (clk_info->भाग.भाग_प्रकारable)
			hw_भाग = ingenic_clk_calc_hw_भाग(clk_info, भाग);
		अन्यथा
			hw_भाग = ((भाग / clk_info->भाग.भाग) - 1);

		spin_lock_irqsave(&cgu->lock, flags);
		reg = पढ़ोl(cgu->base + clk_info->भाग.reg);

		/* update the भागide */
		mask = GENMASK(clk_info->भाग.bits - 1, 0);
		reg &= ~(mask << clk_info->भाग.shअगरt);
		reg |= hw_भाग << clk_info->भाग.shअगरt;

		/* clear the stop bit */
		अगर (clk_info->भाग.stop_bit != -1)
			reg &= ~BIT(clk_info->भाग.stop_bit);

		/* set the change enable bit */
		अगर (clk_info->भाग.ce_bit != -1)
			reg |= BIT(clk_info->भाग.ce_bit);

		/* update the hardware */
		ग_लिखोl(reg, cgu->base + clk_info->भाग.reg);

		/* रुको क्रम the change to take effect */
		अगर (clk_info->भाग.busy_bit != -1)
			ret = ingenic_clk_check_stable(cgu, clk_info);

		spin_unlock_irqrestore(&cgu->lock, flags);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ingenic_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	अचिन्हित दीर्घ flags;

	अगर (clk_info->type & CGU_CLK_GATE) अणु
		/* ungate the घड़ी */
		spin_lock_irqsave(&cgu->lock, flags);
		ingenic_cgu_gate_set(cgu, &clk_info->gate, false);
		spin_unlock_irqrestore(&cgu->lock, flags);

		अगर (clk_info->gate.delay_us)
			udelay(clk_info->gate.delay_us);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ingenic_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	अचिन्हित दीर्घ flags;

	अगर (clk_info->type & CGU_CLK_GATE) अणु
		/* gate the घड़ी */
		spin_lock_irqsave(&cgu->lock, flags);
		ingenic_cgu_gate_set(cgu, &clk_info->gate, true);
		spin_unlock_irqrestore(&cgu->lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक ingenic_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	काष्ठा ingenic_cgu *cgu = ingenic_clk->cgu;
	पूर्णांक enabled = 1;

	अगर (clk_info->type & CGU_CLK_GATE)
		enabled = !ingenic_cgu_gate_get(cgu, &clk_info->gate);

	वापस enabled;
पूर्ण

अटल स्थिर काष्ठा clk_ops ingenic_clk_ops = अणु
	.get_parent = ingenic_clk_get_parent,
	.set_parent = ingenic_clk_set_parent,

	.recalc_rate = ingenic_clk_recalc_rate,
	.round_rate = ingenic_clk_round_rate,
	.set_rate = ingenic_clk_set_rate,

	.enable = ingenic_clk_enable,
	.disable = ingenic_clk_disable,
	.is_enabled = ingenic_clk_is_enabled,
पूर्ण;

/*
 * Setup functions.
 */

अटल पूर्णांक ingenic_रेजिस्टर_घड़ी(काष्ठा ingenic_cgu *cgu, अचिन्हित idx)
अणु
	स्थिर काष्ठा ingenic_cgu_clk_info *clk_info = &cgu->घड़ी_info[idx];
	काष्ठा clk_init_data clk_init;
	काष्ठा ingenic_clk *ingenic_clk = शून्य;
	काष्ठा clk *clk, *parent;
	स्थिर अक्षर *parent_names[4];
	अचिन्हित caps, i, num_possible;
	पूर्णांक err = -EINVAL;

	BUILD_BUG_ON(ARRAY_SIZE(clk_info->parents) > ARRAY_SIZE(parent_names));

	अगर (clk_info->type == CGU_CLK_EXT) अणु
		clk = of_clk_get_by_name(cgu->np, clk_info->name);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: no external clock '%s' provided\n",
			       __func__, clk_info->name);
			err = -ENODEV;
			जाओ out;
		पूर्ण
		err = clk_रेजिस्टर_clkdev(clk, clk_info->name, शून्य);
		अगर (err) अणु
			clk_put(clk);
			जाओ out;
		पूर्ण
		cgu->घड़ीs.clks[idx] = clk;
		वापस 0;
	पूर्ण

	अगर (!clk_info->type) अणु
		pr_err("%s: no clock type specified for '%s'\n", __func__,
		       clk_info->name);
		जाओ out;
	पूर्ण

	ingenic_clk = kzalloc(माप(*ingenic_clk), GFP_KERNEL);
	अगर (!ingenic_clk) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ingenic_clk->hw.init = &clk_init;
	ingenic_clk->cgu = cgu;
	ingenic_clk->idx = idx;

	clk_init.name = clk_info->name;
	clk_init.flags = 0;
	clk_init.parent_names = parent_names;

	caps = clk_info->type;

	अगर (caps & CGU_CLK_DIV) अणु
		caps &= ~CGU_CLK_DIV;
	पूर्ण अन्यथा अगर (!(caps & CGU_CLK_CUSTOM)) अणु
		/* pass rate changes to the parent घड़ी */
		clk_init.flags |= CLK_SET_RATE_PARENT;
	पूर्ण

	अगर (caps & (CGU_CLK_MUX | CGU_CLK_CUSTOM)) अणु
		clk_init.num_parents = 0;

		अगर (caps & CGU_CLK_MUX)
			num_possible = 1 << clk_info->mux.bits;
		अन्यथा
			num_possible = ARRAY_SIZE(clk_info->parents);

		क्रम (i = 0; i < num_possible; i++) अणु
			अगर (clk_info->parents[i] == -1)
				जारी;

			parent = cgu->घड़ीs.clks[clk_info->parents[i]];
			parent_names[clk_init.num_parents] =
				__clk_get_name(parent);
			clk_init.num_parents++;
		पूर्ण

		BUG_ON(!clk_init.num_parents);
		BUG_ON(clk_init.num_parents > ARRAY_SIZE(parent_names));
	पूर्ण अन्यथा अणु
		BUG_ON(clk_info->parents[0] == -1);
		clk_init.num_parents = 1;
		parent = cgu->घड़ीs.clks[clk_info->parents[0]];
		parent_names[0] = __clk_get_name(parent);
	पूर्ण

	अगर (caps & CGU_CLK_CUSTOM) अणु
		clk_init.ops = clk_info->custom.clk_ops;

		caps &= ~CGU_CLK_CUSTOM;

		अगर (caps) अणु
			pr_err("%s: custom clock may not be combined with type 0x%x\n",
			       __func__, caps);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (caps & CGU_CLK_PLL) अणु
		clk_init.ops = &ingenic_pll_ops;

		caps &= ~CGU_CLK_PLL;

		अगर (caps) अणु
			pr_err("%s: PLL may not be combined with type 0x%x\n",
			       __func__, caps);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_init.ops = &ingenic_clk_ops;
	पूर्ण

	/* nothing to करो क्रम gates or fixed भागiders */
	caps &= ~(CGU_CLK_GATE | CGU_CLK_FIXDIV);

	अगर (caps & CGU_CLK_MUX) अणु
		अगर (!(caps & CGU_CLK_MUX_GLITCHFREE))
			clk_init.flags |= CLK_SET_PARENT_GATE;

		caps &= ~(CGU_CLK_MUX | CGU_CLK_MUX_GLITCHFREE);
	पूर्ण

	अगर (caps) अणु
		pr_err("%s: unknown clock type 0x%x\n", __func__, caps);
		जाओ out;
	पूर्ण

	clk = clk_रेजिस्टर(शून्य, &ingenic_clk->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to register clock '%s'\n", __func__,
		       clk_info->name);
		err = PTR_ERR(clk);
		जाओ out;
	पूर्ण

	err = clk_रेजिस्टर_clkdev(clk, clk_info->name, शून्य);
	अगर (err)
		जाओ out;

	cgu->घड़ीs.clks[idx] = clk;
out:
	अगर (err)
		kमुक्त(ingenic_clk);
	वापस err;
पूर्ण

काष्ठा ingenic_cgu *
ingenic_cgu_new(स्थिर काष्ठा ingenic_cgu_clk_info *घड़ी_info,
		अचिन्हित num_घड़ीs, काष्ठा device_node *np)
अणु
	काष्ठा ingenic_cgu *cgu;

	cgu = kzalloc(माप(*cgu), GFP_KERNEL);
	अगर (!cgu)
		जाओ err_out;

	cgu->base = of_iomap(np, 0);
	अगर (!cgu->base) अणु
		pr_err("%s: failed to map CGU registers\n", __func__);
		जाओ err_out_मुक्त;
	पूर्ण

	cgu->np = np;
	cgu->घड़ी_info = घड़ी_info;
	cgu->घड़ीs.clk_num = num_घड़ीs;

	spin_lock_init(&cgu->lock);

	वापस cgu;

err_out_मुक्त:
	kमुक्त(cgu);
err_out:
	वापस शून्य;
पूर्ण

पूर्णांक ingenic_cgu_रेजिस्टर_घड़ीs(काष्ठा ingenic_cgu *cgu)
अणु
	अचिन्हित i;
	पूर्णांक err;

	cgu->घड़ीs.clks = kसुस्मृति(cgu->घड़ीs.clk_num, माप(काष्ठा clk *),
				   GFP_KERNEL);
	अगर (!cgu->घड़ीs.clks) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	क्रम (i = 0; i < cgu->घड़ीs.clk_num; i++) अणु
		err = ingenic_रेजिस्टर_घड़ी(cgu, i);
		अगर (err)
			जाओ err_out_unरेजिस्टर;
	पूर्ण

	err = of_clk_add_provider(cgu->np, of_clk_src_onecell_get,
				  &cgu->घड़ीs);
	अगर (err)
		जाओ err_out_unरेजिस्टर;

	वापस 0;

err_out_unरेजिस्टर:
	क्रम (i = 0; i < cgu->घड़ीs.clk_num; i++) अणु
		अगर (!cgu->घड़ीs.clks[i])
			जारी;
		अगर (cgu->घड़ी_info[i].type & CGU_CLK_EXT)
			clk_put(cgu->घड़ीs.clks[i]);
		अन्यथा
			clk_unरेजिस्टर(cgu->घड़ीs.clks[i]);
	पूर्ण
	kमुक्त(cgu->घड़ीs.clks);
err_out:
	वापस err;
पूर्ण
