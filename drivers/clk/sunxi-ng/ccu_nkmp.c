<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_nkmp.h"

काष्ठा _ccu_nkmp अणु
	अचिन्हित दीर्घ	n, min_n, max_n;
	अचिन्हित दीर्घ	k, min_k, max_k;
	अचिन्हित दीर्घ	m, min_m, max_m;
	अचिन्हित दीर्घ	p, min_p, max_p;
पूर्ण;

अटल अचिन्हित दीर्घ ccu_nkmp_calc_rate(अचिन्हित दीर्घ parent,
					अचिन्हित दीर्घ n, अचिन्हित दीर्घ k,
					अचिन्हित दीर्घ m, अचिन्हित दीर्घ p)
अणु
	u64 rate = parent;

	rate *= n * k;
	करो_भाग(rate, m * p);

	वापस rate;
पूर्ण

अटल व्योम ccu_nkmp_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			       काष्ठा _ccu_nkmp *nkmp)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित दीर्घ best_n = 0, best_k = 0, best_m = 0, best_p = 0;
	अचिन्हित दीर्घ _n, _k, _m, _p;

	क्रम (_k = nkmp->min_k; _k <= nkmp->max_k; _k++) अणु
		क्रम (_n = nkmp->min_n; _n <= nkmp->max_n; _n++) अणु
			क्रम (_m = nkmp->min_m; _m <= nkmp->max_m; _m++) अणु
				क्रम (_p = nkmp->min_p; _p <= nkmp->max_p; _p <<= 1) अणु
					अचिन्हित दीर्घ पंचांगp_rate;

					पंचांगp_rate = ccu_nkmp_calc_rate(parent,
								      _n, _k,
								      _m, _p);

					अगर (पंचांगp_rate > rate)
						जारी;

					अगर ((rate - पंचांगp_rate) < (rate - best_rate)) अणु
						best_rate = पंचांगp_rate;
						best_n = _n;
						best_k = _k;
						best_m = _m;
						best_p = _p;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	nkmp->n = best_n;
	nkmp->k = best_k;
	nkmp->m = best_m;
	nkmp->p = best_p;
पूर्ण

अटल व्योम ccu_nkmp_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	वापस ccu_gate_helper_disable(&nkmp->common, nkmp->enable);
पूर्ण

अटल पूर्णांक ccu_nkmp_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	वापस ccu_gate_helper_enable(&nkmp->common, nkmp->enable);
पूर्ण

अटल पूर्णांक ccu_nkmp_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	वापस ccu_gate_helper_is_enabled(&nkmp->common, nkmp->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_nkmp_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	अचिन्हित दीर्घ n, m, k, p, rate;
	u32 reg;

	reg = पढ़ोl(nkmp->common.base + nkmp->common.reg);

	n = reg >> nkmp->n.shअगरt;
	n &= (1 << nkmp->n.width) - 1;
	n += nkmp->n.offset;
	अगर (!n)
		n++;

	k = reg >> nkmp->k.shअगरt;
	k &= (1 << nkmp->k.width) - 1;
	k += nkmp->k.offset;
	अगर (!k)
		k++;

	m = reg >> nkmp->m.shअगरt;
	m &= (1 << nkmp->m.width) - 1;
	m += nkmp->m.offset;
	अगर (!m)
		m++;

	p = reg >> nkmp->p.shअगरt;
	p &= (1 << nkmp->p.width) - 1;

	rate = ccu_nkmp_calc_rate(parent_rate, n, k, m, 1 << p);
	अगर (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkmp->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल दीर्घ ccu_nkmp_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	काष्ठा _ccu_nkmp _nkmp;

	अगर (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nkmp->fixed_post_भाग;

	अगर (nkmp->max_rate && rate > nkmp->max_rate) अणु
		rate = nkmp->max_rate;
		अगर (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nkmp->fixed_post_भाग;
		वापस rate;
	पूर्ण

	_nkmp.min_n = nkmp->n.min ?: 1;
	_nkmp.max_n = nkmp->n.max ?: 1 << nkmp->n.width;
	_nkmp.min_k = nkmp->k.min ?: 1;
	_nkmp.max_k = nkmp->k.max ?: 1 << nkmp->k.width;
	_nkmp.min_m = 1;
	_nkmp.max_m = nkmp->m.max ?: 1 << nkmp->m.width;
	_nkmp.min_p = 1;
	_nkmp.max_p = nkmp->p.max ?: 1 << ((1 << nkmp->p.width) - 1);

	ccu_nkmp_find_best(*parent_rate, rate, &_nkmp);

	rate = ccu_nkmp_calc_rate(*parent_rate, _nkmp.n, _nkmp.k,
				  _nkmp.m, _nkmp.p);
	अगर (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate / nkmp->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल पूर्णांक ccu_nkmp_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	u32 n_mask = 0, k_mask = 0, m_mask = 0, p_mask = 0;
	काष्ठा _ccu_nkmp _nkmp;
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate * nkmp->fixed_post_भाग;

	_nkmp.min_n = nkmp->n.min ?: 1;
	_nkmp.max_n = nkmp->n.max ?: 1 << nkmp->n.width;
	_nkmp.min_k = nkmp->k.min ?: 1;
	_nkmp.max_k = nkmp->k.max ?: 1 << nkmp->k.width;
	_nkmp.min_m = 1;
	_nkmp.max_m = nkmp->m.max ?: 1 << nkmp->m.width;
	_nkmp.min_p = 1;
	_nkmp.max_p = nkmp->p.max ?: 1 << ((1 << nkmp->p.width) - 1);

	ccu_nkmp_find_best(parent_rate, rate, &_nkmp);

	/*
	 * If width is 0, GENMASK() macro may not generate expected mask (0)
	 * as it falls under undefined behaviour by C standard due to shअगरts
	 * which are equal or greater than width of left opeअक्रम. This can
	 * be easily aव्योमed by explicitly checking अगर width is 0.
	 */
	अगर (nkmp->n.width)
		n_mask = GENMASK(nkmp->n.width + nkmp->n.shअगरt - 1,
				 nkmp->n.shअगरt);
	अगर (nkmp->k.width)
		k_mask = GENMASK(nkmp->k.width + nkmp->k.shअगरt - 1,
				 nkmp->k.shअगरt);
	अगर (nkmp->m.width)
		m_mask = GENMASK(nkmp->m.width + nkmp->m.shअगरt - 1,
				 nkmp->m.shअगरt);
	अगर (nkmp->p.width)
		p_mask = GENMASK(nkmp->p.width + nkmp->p.shअगरt - 1,
				 nkmp->p.shअगरt);

	spin_lock_irqsave(nkmp->common.lock, flags);

	reg = पढ़ोl(nkmp->common.base + nkmp->common.reg);
	reg &= ~(n_mask | k_mask | m_mask | p_mask);

	reg |= ((_nkmp.n - nkmp->n.offset) << nkmp->n.shअगरt) & n_mask;
	reg |= ((_nkmp.k - nkmp->k.offset) << nkmp->k.shअगरt) & k_mask;
	reg |= ((_nkmp.m - nkmp->m.offset) << nkmp->m.shअगरt) & m_mask;
	reg |= (ilog2(_nkmp.p) << nkmp->p.shअगरt) & p_mask;

	ग_लिखोl(reg, nkmp->common.base + nkmp->common.reg);

	spin_unlock_irqrestore(nkmp->common.lock, flags);

	ccu_helper_रुको_क्रम_lock(&nkmp->common, nkmp->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops ccu_nkmp_ops = अणु
	.disable	= ccu_nkmp_disable,
	.enable		= ccu_nkmp_enable,
	.is_enabled	= ccu_nkmp_is_enabled,

	.recalc_rate	= ccu_nkmp_recalc_rate,
	.round_rate	= ccu_nkmp_round_rate,
	.set_rate	= ccu_nkmp_set_rate,
पूर्ण;
