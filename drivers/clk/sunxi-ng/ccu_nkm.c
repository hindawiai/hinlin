<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_nkm.h"

काष्ठा _ccu_nkm अणु
	अचिन्हित दीर्घ	n, min_n, max_n;
	अचिन्हित दीर्घ	k, min_k, max_k;
	अचिन्हित दीर्घ	m, min_m, max_m;
पूर्ण;

अटल व्योम ccu_nkm_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			      काष्ठा _ccu_nkm *nkm)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित दीर्घ best_n = 0, best_k = 0, best_m = 0;
	अचिन्हित दीर्घ _n, _k, _m;

	क्रम (_k = nkm->min_k; _k <= nkm->max_k; _k++) अणु
		क्रम (_n = nkm->min_n; _n <= nkm->max_n; _n++) अणु
			क्रम (_m = nkm->min_m; _m <= nkm->max_m; _m++) अणु
				अचिन्हित दीर्घ पंचांगp_rate;

				पंचांगp_rate = parent * _n * _k / _m;

				अगर (पंचांगp_rate > rate)
					जारी;
				अगर ((rate - पंचांगp_rate) < (rate - best_rate)) अणु
					best_rate = पंचांगp_rate;
					best_n = _n;
					best_k = _k;
					best_m = _m;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	nkm->n = best_n;
	nkm->k = best_k;
	nkm->m = best_m;
पूर्ण

अटल व्योम ccu_nkm_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_gate_helper_disable(&nkm->common, nkm->enable);
पूर्ण

अटल पूर्णांक ccu_nkm_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_gate_helper_enable(&nkm->common, nkm->enable);
पूर्ण

अटल पूर्णांक ccu_nkm_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_gate_helper_is_enabled(&nkm->common, nkm->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_nkm_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);
	अचिन्हित दीर्घ n, m, k, rate;
	u32 reg;

	reg = पढ़ोl(nkm->common.base + nkm->common.reg);

	n = reg >> nkm->n.shअगरt;
	n &= (1 << nkm->n.width) - 1;
	n += nkm->n.offset;
	अगर (!n)
		n++;

	k = reg >> nkm->k.shअगरt;
	k &= (1 << nkm->k.width) - 1;
	k += nkm->k.offset;
	अगर (!k)
		k++;

	m = reg >> nkm->m.shअगरt;
	m &= (1 << nkm->m.width) - 1;
	m += nkm->m.offset;
	अगर (!m)
		m++;

	rate = parent_rate * n  * k / m;

	अगर (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkm->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ ccu_nkm_round_rate(काष्ठा ccu_mux_पूर्णांकernal *mux,
					काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ *parent_rate,
					अचिन्हित दीर्घ rate,
					व्योम *data)
अणु
	काष्ठा ccu_nkm *nkm = data;
	काष्ठा _ccu_nkm _nkm;

	_nkm.min_n = nkm->n.min ?: 1;
	_nkm.max_n = nkm->n.max ?: 1 << nkm->n.width;
	_nkm.min_k = nkm->k.min ?: 1;
	_nkm.max_k = nkm->k.max ?: 1 << nkm->k.width;
	_nkm.min_m = 1;
	_nkm.max_m = nkm->m.max ?: 1 << nkm->m.width;

	अगर (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nkm->fixed_post_भाग;

	ccu_nkm_find_best(*parent_rate, rate, &_nkm);

	rate = *parent_rate * _nkm.n * _nkm.k / _nkm.m;

	अगर (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkm->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल पूर्णांक ccu_nkm_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_mux_helper_determine_rate(&nkm->common, &nkm->mux,
					     req, ccu_nkm_round_rate, nkm);
पूर्ण

अटल पूर्णांक ccu_nkm_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);
	काष्ठा _ccu_nkm _nkm;
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nkm->fixed_post_भाग;

	_nkm.min_n = nkm->n.min ?: 1;
	_nkm.max_n = nkm->n.max ?: 1 << nkm->n.width;
	_nkm.min_k = nkm->k.min ?: 1;
	_nkm.max_k = nkm->k.max ?: 1 << nkm->k.width;
	_nkm.min_m = 1;
	_nkm.max_m = nkm->m.max ?: 1 << nkm->m.width;

	ccu_nkm_find_best(parent_rate, rate, &_nkm);

	spin_lock_irqsave(nkm->common.lock, flags);

	reg = पढ़ोl(nkm->common.base + nkm->common.reg);
	reg &= ~GENMASK(nkm->n.width + nkm->n.shअगरt - 1, nkm->n.shअगरt);
	reg &= ~GENMASK(nkm->k.width + nkm->k.shअगरt - 1, nkm->k.shअगरt);
	reg &= ~GENMASK(nkm->m.width + nkm->m.shअगरt - 1, nkm->m.shअगरt);

	reg |= (_nkm.n - nkm->n.offset) << nkm->n.shअगरt;
	reg |= (_nkm.k - nkm->k.offset) << nkm->k.shअगरt;
	reg |= (_nkm.m - nkm->m.offset) << nkm->m.shअगरt;
	ग_लिखोl(reg, nkm->common.base + nkm->common.reg);

	spin_unlock_irqrestore(nkm->common.lock, flags);

	ccu_helper_रुको_क्रम_lock(&nkm->common, nkm->lock);

	वापस 0;
पूर्ण

अटल u8 ccu_nkm_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_mux_helper_get_parent(&nkm->common, &nkm->mux);
पूर्ण

अटल पूर्णांक ccu_nkm_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	वापस ccu_mux_helper_set_parent(&nkm->common, &nkm->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops ccu_nkm_ops = अणु
	.disable	= ccu_nkm_disable,
	.enable		= ccu_nkm_enable,
	.is_enabled	= ccu_nkm_is_enabled,

	.get_parent	= ccu_nkm_get_parent,
	.set_parent	= ccu_nkm_set_parent,

	.determine_rate	= ccu_nkm_determine_rate,
	.recalc_rate	= ccu_nkm_recalc_rate,
	.set_rate	= ccu_nkm_set_rate,
पूर्ण;
