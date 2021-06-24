<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_nk.h"

काष्ठा _ccu_nk अणु
	अचिन्हित दीर्घ	n, min_n, max_n;
	अचिन्हित दीर्घ	k, min_k, max_k;
पूर्ण;

अटल व्योम ccu_nk_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			     काष्ठा _ccu_nk *nk)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित पूर्णांक best_k = 0, best_n = 0;
	अचिन्हित पूर्णांक _k, _n;

	क्रम (_k = nk->min_k; _k <= nk->max_k; _k++) अणु
		क्रम (_n = nk->min_n; _n <= nk->max_n; _n++) अणु
			अचिन्हित दीर्घ पंचांगp_rate = parent * _n * _k;

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर ((rate - पंचांगp_rate) < (rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_k = _k;
				best_n = _n;
			पूर्ण
		पूर्ण
	पूर्ण

	nk->k = best_k;
	nk->n = best_n;
पूर्ण

अटल व्योम ccu_nk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);

	वापस ccu_gate_helper_disable(&nk->common, nk->enable);
पूर्ण

अटल पूर्णांक ccu_nk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);

	वापस ccu_gate_helper_enable(&nk->common, nk->enable);
पूर्ण

अटल पूर्णांक ccu_nk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);

	वापस ccu_gate_helper_is_enabled(&nk->common, nk->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_nk_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);
	अचिन्हित दीर्घ rate, n, k;
	u32 reg;

	reg = पढ़ोl(nk->common.base + nk->common.reg);

	n = reg >> nk->n.shअगरt;
	n &= (1 << nk->n.width) - 1;
	n += nk->n.offset;
	अगर (!n)
		n++;

	k = reg >> nk->k.shअगरt;
	k &= (1 << nk->k.width) - 1;
	k += nk->k.offset;
	अगर (!k)
		k++;

	rate = parent_rate * n * k;
	अगर (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nk->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल दीर्घ ccu_nk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);
	काष्ठा _ccu_nk _nk;

	अगर (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nk->fixed_post_भाग;

	_nk.min_n = nk->n.min ?: 1;
	_nk.max_n = nk->n.max ?: 1 << nk->n.width;
	_nk.min_k = nk->k.min ?: 1;
	_nk.max_k = nk->k.max ?: 1 << nk->k.width;

	ccu_nk_find_best(*parent_rate, rate, &_nk);
	rate = *parent_rate * _nk.n * _nk.k;

	अगर (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate / nk->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल पूर्णांक ccu_nk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nk *nk = hw_to_ccu_nk(hw);
	अचिन्हित दीर्घ flags;
	काष्ठा _ccu_nk _nk;
	u32 reg;

	अगर (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate * nk->fixed_post_भाग;

	_nk.min_n = nk->n.min ?: 1;
	_nk.max_n = nk->n.max ?: 1 << nk->n.width;
	_nk.min_k = nk->k.min ?: 1;
	_nk.max_k = nk->k.max ?: 1 << nk->k.width;

	ccu_nk_find_best(parent_rate, rate, &_nk);

	spin_lock_irqsave(nk->common.lock, flags);

	reg = पढ़ोl(nk->common.base + nk->common.reg);
	reg &= ~GENMASK(nk->n.width + nk->n.shअगरt - 1, nk->n.shअगरt);
	reg &= ~GENMASK(nk->k.width + nk->k.shअगरt - 1, nk->k.shअगरt);

	reg |= (_nk.k - nk->k.offset) << nk->k.shअगरt;
	reg |= (_nk.n - nk->n.offset) << nk->n.shअगरt;
	ग_लिखोl(reg, nk->common.base + nk->common.reg);

	spin_unlock_irqrestore(nk->common.lock, flags);

	ccu_helper_रुको_क्रम_lock(&nk->common, nk->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops ccu_nk_ops = अणु
	.disable	= ccu_nk_disable,
	.enable		= ccu_nk_enable,
	.is_enabled	= ccu_nk_is_enabled,

	.recalc_rate	= ccu_nk_recalc_rate,
	.round_rate	= ccu_nk_round_rate,
	.set_rate	= ccu_nk_set_rate,
पूर्ण;
