<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_frac.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_nm.h"

काष्ठा _ccu_nm अणु
	अचिन्हित दीर्घ	n, min_n, max_n;
	अचिन्हित दीर्घ	m, min_m, max_m;
पूर्ण;

अटल अचिन्हित दीर्घ ccu_nm_calc_rate(अचिन्हित दीर्घ parent,
				      अचिन्हित दीर्घ n, अचिन्हित दीर्घ m)
अणु
	u64 rate = parent;

	rate *= n;
	करो_भाग(rate, m);

	वापस rate;
पूर्ण

अटल व्योम ccu_nm_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			     काष्ठा _ccu_nm *nm)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित दीर्घ best_n = 0, best_m = 0;
	अचिन्हित दीर्घ _n, _m;

	क्रम (_n = nm->min_n; _n <= nm->max_n; _n++) अणु
		क्रम (_m = nm->min_m; _m <= nm->max_m; _m++) अणु
			अचिन्हित दीर्घ पंचांगp_rate = ccu_nm_calc_rate(parent,
								  _n, _m);

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर ((rate - पंचांगp_rate) < (rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_n = _n;
				best_m = _m;
			पूर्ण
		पूर्ण
	पूर्ण

	nm->n = best_n;
	nm->m = best_m;
पूर्ण

अटल व्योम ccu_nm_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);

	वापस ccu_gate_helper_disable(&nm->common, nm->enable);
पूर्ण

अटल पूर्णांक ccu_nm_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);

	वापस ccu_gate_helper_enable(&nm->common, nm->enable);
पूर्ण

अटल पूर्णांक ccu_nm_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);

	वापस ccu_gate_helper_is_enabled(&nm->common, nm->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_nm_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ n, m;
	u32 reg;

	अगर (ccu_frac_helper_is_enabled(&nm->common, &nm->frac)) अणु
		rate = ccu_frac_helper_पढ़ो_rate(&nm->common, &nm->frac);

		अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_भाग;

		वापस rate;
	पूर्ण

	reg = पढ़ोl(nm->common.base + nm->common.reg);

	n = reg >> nm->n.shअगरt;
	n &= (1 << nm->n.width) - 1;
	n += nm->n.offset;
	अगर (!n)
		n++;

	m = reg >> nm->m.shअगरt;
	m &= (1 << nm->m.width) - 1;
	m += nm->m.offset;
	अगर (!m)
		m++;

	अगर (ccu_sdm_helper_is_enabled(&nm->common, &nm->sdm))
		rate = ccu_sdm_helper_पढ़ो_rate(&nm->common, &nm->sdm, m, n);
	अन्यथा
		rate = ccu_nm_calc_rate(parent_rate, n, m);

	अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nm->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल दीर्घ ccu_nm_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);
	काष्ठा _ccu_nm _nm;

	अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nm->fixed_post_भाग;

	अगर (rate < nm->min_rate) अणु
		rate = nm->min_rate;
		अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_भाग;
		वापस rate;
	पूर्ण

	अगर (nm->max_rate && rate > nm->max_rate) अणु
		rate = nm->max_rate;
		अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_भाग;
		वापस rate;
	पूर्ण

	अगर (ccu_frac_helper_has_rate(&nm->common, &nm->frac, rate)) अणु
		अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_भाग;
		वापस rate;
	पूर्ण

	अगर (ccu_sdm_helper_has_rate(&nm->common, &nm->sdm, rate)) अणु
		अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_भाग;
		वापस rate;
	पूर्ण

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

	ccu_nm_find_best(*parent_rate, rate, &_nm);
	rate = ccu_nm_calc_rate(*parent_rate, _nm.n, _nm.m);

	अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nm->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल पूर्णांक ccu_nm_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nm *nm = hw_to_ccu_nm(hw);
	काष्ठा _ccu_nm _nm;
	अचिन्हित दीर्घ flags;
	u32 reg;

	/* Adjust target rate according to post-भागiders */
	अगर (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate * nm->fixed_post_भाग;

	अगर (ccu_frac_helper_has_rate(&nm->common, &nm->frac, rate)) अणु
		spin_lock_irqsave(nm->common.lock, flags);

		/* most SoCs require M to be 0 अगर fractional mode is used */
		reg = पढ़ोl(nm->common.base + nm->common.reg);
		reg &= ~GENMASK(nm->m.width + nm->m.shअगरt - 1, nm->m.shअगरt);
		ग_लिखोl(reg, nm->common.base + nm->common.reg);

		spin_unlock_irqrestore(nm->common.lock, flags);

		ccu_frac_helper_enable(&nm->common, &nm->frac);

		वापस ccu_frac_helper_set_rate(&nm->common, &nm->frac,
						rate, nm->lock);
	पूर्ण अन्यथा अणु
		ccu_frac_helper_disable(&nm->common, &nm->frac);
	पूर्ण

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

	अगर (ccu_sdm_helper_has_rate(&nm->common, &nm->sdm, rate)) अणु
		ccu_sdm_helper_enable(&nm->common, &nm->sdm, rate);

		/* Sigma delta modulation requires specअगरic N and M factors */
		ccu_sdm_helper_get_factors(&nm->common, &nm->sdm, rate,
					   &_nm.m, &_nm.n);
	पूर्ण अन्यथा अणु
		ccu_sdm_helper_disable(&nm->common, &nm->sdm);
		ccu_nm_find_best(parent_rate, rate, &_nm);
	पूर्ण

	spin_lock_irqsave(nm->common.lock, flags);

	reg = पढ़ोl(nm->common.base + nm->common.reg);
	reg &= ~GENMASK(nm->n.width + nm->n.shअगरt - 1, nm->n.shअगरt);
	reg &= ~GENMASK(nm->m.width + nm->m.shअगरt - 1, nm->m.shअगरt);

	reg |= (_nm.n - nm->n.offset) << nm->n.shअगरt;
	reg |= (_nm.m - nm->m.offset) << nm->m.shअगरt;
	ग_लिखोl(reg, nm->common.base + nm->common.reg);

	spin_unlock_irqrestore(nm->common.lock, flags);

	ccu_helper_रुको_क्रम_lock(&nm->common, nm->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops ccu_nm_ops = अणु
	.disable	= ccu_nm_disable,
	.enable		= ccu_nm_enable,
	.is_enabled	= ccu_nm_is_enabled,

	.recalc_rate	= ccu_nm_recalc_rate,
	.round_rate	= ccu_nm_round_rate,
	.set_rate	= ccu_nm_set_rate,
पूर्ण;
