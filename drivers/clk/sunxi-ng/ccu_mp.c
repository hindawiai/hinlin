<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_mp.h"

अटल व्योम ccu_mp_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			     अचिन्हित पूर्णांक max_m, अचिन्हित पूर्णांक max_p,
			     अचिन्हित पूर्णांक *m, अचिन्हित पूर्णांक *p)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित पूर्णांक best_m = 0, best_p = 0;
	अचिन्हित पूर्णांक _m, _p;

	क्रम (_p = 1; _p <= max_p; _p <<= 1) अणु
		क्रम (_m = 1; _m <= max_m; _m++) अणु
			अचिन्हित दीर्घ पंचांगp_rate = parent / _p / _m;

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर ((rate - पंचांगp_rate) < (rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_m = _m;
				best_p = _p;
			पूर्ण
		पूर्ण
	पूर्ण

	*m = best_m;
	*p = best_p;
पूर्ण

अटल अचिन्हित दीर्घ ccu_mp_find_best_with_parent_adj(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ *parent,
						      अचिन्हित दीर्घ rate,
						      अचिन्हित पूर्णांक max_m,
						      अचिन्हित पूर्णांक max_p)
अणु
	अचिन्हित दीर्घ parent_rate_saved;
	अचिन्हित दीर्घ parent_rate, now;
	अचिन्हित दीर्घ best_rate = 0;
	अचिन्हित पूर्णांक _m, _p, भाग;
	अचिन्हित दीर्घ maxभाग;

	parent_rate_saved = *parent;

	/*
	 * The maximum भागider we can use without overflowing
	 * अचिन्हित दीर्घ in rate * m * p below
	 */
	maxभाग = max_m * max_p;
	maxभाग = min(अच_दीर्घ_उच्च / rate, maxभाग);

	क्रम (_p = 1; _p <= max_p; _p <<= 1) अणु
		क्रम (_m = 1; _m <= max_m; _m++) अणु
			भाग = _m * _p;

			अगर (भाग > maxभाग)
				अवरोध;

			अगर (rate * भाग == parent_rate_saved) अणु
				/*
				 * It's the most ideal हाल अगर the requested
				 * rate can be भागided from parent घड़ी without
				 * needing to change parent rate, so वापस the
				 * भागider immediately.
				 */
				*parent = parent_rate_saved;
				वापस rate;
			पूर्ण

			parent_rate = clk_hw_round_rate(hw, rate * भाग);
			now = parent_rate / भाग;

			अगर (now <= rate && now > best_rate) अणु
				best_rate = now;
				*parent = parent_rate;

				अगर (now == rate)
					वापस rate;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस best_rate;
पूर्ण

अटल अचिन्हित दीर्घ ccu_mp_round_rate(काष्ठा ccu_mux_पूर्णांकernal *mux,
				       काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ *parent_rate,
				       अचिन्हित दीर्घ rate,
				       व्योम *data)
अणु
	काष्ठा ccu_mp *cmp = data;
	अचिन्हित पूर्णांक max_m, max_p;
	अचिन्हित पूर्णांक m, p;

	अगर (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= cmp->fixed_post_भाग;

	max_m = cmp->m.max ?: 1 << cmp->m.width;
	max_p = cmp->p.max ?: 1 << ((1 << cmp->p.width) - 1);

	अगर (!clk_hw_can_set_rate_parent(&cmp->common.hw)) अणु
		ccu_mp_find_best(*parent_rate, rate, max_m, max_p, &m, &p);
		rate = *parent_rate / p / m;
	पूर्ण अन्यथा अणु
		rate = ccu_mp_find_best_with_parent_adj(hw, parent_rate, rate,
							max_m, max_p);
	पूर्ण

	अगर (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= cmp->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल व्योम ccu_mp_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_gate_helper_disable(&cmp->common, cmp->enable);
पूर्ण

अटल पूर्णांक ccu_mp_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_gate_helper_enable(&cmp->common, cmp->enable);
पूर्ण

अटल पूर्णांक ccu_mp_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_gate_helper_is_enabled(&cmp->common, cmp->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_mp_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक m, p;
	u32 reg;

	/* Adjust parent_rate according to pre-भागiders */
	parent_rate = ccu_mux_helper_apply_preभाग(&cmp->common, &cmp->mux, -1,
						  parent_rate);

	reg = पढ़ोl(cmp->common.base + cmp->common.reg);

	m = reg >> cmp->m.shअगरt;
	m &= (1 << cmp->m.width) - 1;
	m += cmp->m.offset;
	अगर (!m)
		m++;

	p = reg >> cmp->p.shअगरt;
	p &= (1 << cmp->p.width) - 1;

	rate = (parent_rate >> p) / m;
	अगर (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= cmp->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल पूर्णांक ccu_mp_determine_rate(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_mux_helper_determine_rate(&cmp->common, &cmp->mux,
					     req, ccu_mp_round_rate, cmp);
पूर्ण

अटल पूर्णांक ccu_mp_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक max_m, max_p;
	अचिन्हित पूर्णांक m, p;
	u32 reg;

	/* Adjust parent_rate according to pre-भागiders */
	parent_rate = ccu_mux_helper_apply_preभाग(&cmp->common, &cmp->mux, -1,
						  parent_rate);

	max_m = cmp->m.max ?: 1 << cmp->m.width;
	max_p = cmp->p.max ?: 1 << ((1 << cmp->p.width) - 1);

	/* Adjust target rate according to post-भागiders */
	अगर (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate * cmp->fixed_post_भाग;

	ccu_mp_find_best(parent_rate, rate, max_m, max_p, &m, &p);

	spin_lock_irqsave(cmp->common.lock, flags);

	reg = पढ़ोl(cmp->common.base + cmp->common.reg);
	reg &= ~GENMASK(cmp->m.width + cmp->m.shअगरt - 1, cmp->m.shअगरt);
	reg &= ~GENMASK(cmp->p.width + cmp->p.shअगरt - 1, cmp->p.shअगरt);
	reg |= (m - cmp->m.offset) << cmp->m.shअगरt;
	reg |= ilog2(p) << cmp->p.shअगरt;

	ग_लिखोl(reg, cmp->common.base + cmp->common.reg);

	spin_unlock_irqrestore(cmp->common.lock, flags);

	वापस 0;
पूर्ण

अटल u8 ccu_mp_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_mux_helper_get_parent(&cmp->common, &cmp->mux);
पूर्ण

अटल पूर्णांक ccu_mp_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ccu_mp *cmp = hw_to_ccu_mp(hw);

	वापस ccu_mux_helper_set_parent(&cmp->common, &cmp->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops ccu_mp_ops = अणु
	.disable	= ccu_mp_disable,
	.enable		= ccu_mp_enable,
	.is_enabled	= ccu_mp_is_enabled,

	.get_parent	= ccu_mp_get_parent,
	.set_parent	= ccu_mp_set_parent,

	.determine_rate	= ccu_mp_determine_rate,
	.recalc_rate	= ccu_mp_recalc_rate,
	.set_rate	= ccu_mp_set_rate,
पूर्ण;

/*
 * Support क्रम MMC timing mode चयनing
 *
 * The MMC घड़ीs on some SoCs support चयनing between old and
 * new timing modes. A platक्रमm specअगरic API is provided to query
 * and set the timing mode on supported SoCs.
 *
 * In addition, a special class of ccu_mp_ops is provided, which
 * takes in to account the timing mode चयन. When the new timing
 * mode is active, the घड़ी output rate is halved. This new class
 * is a wrapper around the generic ccu_mp_ops. When घड़ी rates
 * are passed through to ccu_mp_ops callbacks, they are द्विगुनd
 * अगर the new timing mode bit is set, to account क्रम the post
 * भागider. Conversely, when घड़ी rates are passed back, they
 * are halved अगर the mode bit is set.
 */

अटल अचिन्हित दीर्घ ccu_mp_mmc_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ rate = ccu_mp_recalc_rate(hw, parent_rate);
	काष्ठा ccu_common *cm = hw_to_ccu_common(hw);
	u32 val = पढ़ोl(cm->base + cm->reg);

	अगर (val & CCU_MMC_NEW_TIMING_MODE)
		वापस rate / 2;
	वापस rate;
पूर्ण

अटल पूर्णांक ccu_mp_mmc_determine_rate(काष्ठा clk_hw *hw,
				     काष्ठा clk_rate_request *req)
अणु
	काष्ठा ccu_common *cm = hw_to_ccu_common(hw);
	u32 val = पढ़ोl(cm->base + cm->reg);
	पूर्णांक ret;

	/* adjust the requested घड़ी rate */
	अगर (val & CCU_MMC_NEW_TIMING_MODE) अणु
		req->rate *= 2;
		req->min_rate *= 2;
		req->max_rate *= 2;
	पूर्ण

	ret = ccu_mp_determine_rate(hw, req);

	/* re-adjust the requested घड़ी rate back */
	अगर (val & CCU_MMC_NEW_TIMING_MODE) अणु
		req->rate /= 2;
		req->min_rate /= 2;
		req->max_rate /= 2;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ccu_mp_mmc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_common *cm = hw_to_ccu_common(hw);
	u32 val = पढ़ोl(cm->base + cm->reg);

	अगर (val & CCU_MMC_NEW_TIMING_MODE)
		rate *= 2;

	वापस ccu_mp_set_rate(hw, rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops ccu_mp_mmc_ops = अणु
	.disable	= ccu_mp_disable,
	.enable		= ccu_mp_enable,
	.is_enabled	= ccu_mp_is_enabled,

	.get_parent	= ccu_mp_get_parent,
	.set_parent	= ccu_mp_set_parent,

	.determine_rate	= ccu_mp_mmc_determine_rate,
	.recalc_rate	= ccu_mp_mmc_recalc_rate,
	.set_rate	= ccu_mp_mmc_set_rate,
पूर्ण;
