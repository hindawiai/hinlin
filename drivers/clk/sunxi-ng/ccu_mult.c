<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_mult.h"

काष्ठा _ccu_mult अणु
	अचिन्हित दीर्घ	mult, min, max;
पूर्ण;

अटल व्योम ccu_mult_find_best(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ rate,
			       काष्ठा _ccu_mult *mult)
अणु
	पूर्णांक _mult;

	_mult = rate / parent;
	अगर (_mult < mult->min)
		_mult = mult->min;

	अगर (_mult > mult->max)
		_mult = mult->max;

	mult->mult = _mult;
पूर्ण

अटल अचिन्हित दीर्घ ccu_mult_round_rate(काष्ठा ccu_mux_पूर्णांकernal *mux,
					 काष्ठा clk_hw *parent,
					 अचिन्हित दीर्घ *parent_rate,
					 अचिन्हित दीर्घ rate,
					 व्योम *data)
अणु
	काष्ठा ccu_mult *cm = data;
	काष्ठा _ccu_mult _cm;

	_cm.min = cm->mult.min;

	अगर (cm->mult.max)
		_cm.max = cm->mult.max;
	अन्यथा
		_cm.max = (1 << cm->mult.width) + cm->mult.offset - 1;

	ccu_mult_find_best(*parent_rate, rate, &_cm);

	वापस *parent_rate * _cm.mult;
पूर्ण

अटल व्योम ccu_mult_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_gate_helper_disable(&cm->common, cm->enable);
पूर्ण

अटल पूर्णांक ccu_mult_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_gate_helper_enable(&cm->common, cm->enable);
पूर्ण

अटल पूर्णांक ccu_mult_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_gate_helper_is_enabled(&cm->common, cm->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_mult_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);
	अचिन्हित दीर्घ val;
	u32 reg;

	अगर (ccu_frac_helper_is_enabled(&cm->common, &cm->frac))
		वापस ccu_frac_helper_पढ़ो_rate(&cm->common, &cm->frac);

	reg = पढ़ोl(cm->common.base + cm->common.reg);
	val = reg >> cm->mult.shअगरt;
	val &= (1 << cm->mult.width) - 1;

	parent_rate = ccu_mux_helper_apply_preभाग(&cm->common, &cm->mux, -1,
						  parent_rate);

	वापस parent_rate * (val + cm->mult.offset);
पूर्ण

अटल पूर्णांक ccu_mult_determine_rate(काष्ठा clk_hw *hw,
				काष्ठा clk_rate_request *req)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_mux_helper_determine_rate(&cm->common, &cm->mux,
					     req, ccu_mult_round_rate, cm);
पूर्ण

अटल पूर्णांक ccu_mult_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);
	काष्ठा _ccu_mult _cm;
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (ccu_frac_helper_has_rate(&cm->common, &cm->frac, rate)) अणु
		ccu_frac_helper_enable(&cm->common, &cm->frac);

		वापस ccu_frac_helper_set_rate(&cm->common, &cm->frac,
						rate, cm->lock);
	पूर्ण अन्यथा अणु
		ccu_frac_helper_disable(&cm->common, &cm->frac);
	पूर्ण

	parent_rate = ccu_mux_helper_apply_preभाग(&cm->common, &cm->mux, -1,
						  parent_rate);

	_cm.min = cm->mult.min;

	अगर (cm->mult.max)
		_cm.max = cm->mult.max;
	अन्यथा
		_cm.max = (1 << cm->mult.width) + cm->mult.offset - 1;

	ccu_mult_find_best(parent_rate, rate, &_cm);

	spin_lock_irqsave(cm->common.lock, flags);

	reg = पढ़ोl(cm->common.base + cm->common.reg);
	reg &= ~GENMASK(cm->mult.width + cm->mult.shअगरt - 1, cm->mult.shअगरt);
	reg |= ((_cm.mult - cm->mult.offset) << cm->mult.shअगरt);

	ग_लिखोl(reg, cm->common.base + cm->common.reg);

	spin_unlock_irqrestore(cm->common.lock, flags);

	ccu_helper_रुको_क्रम_lock(&cm->common, cm->lock);

	वापस 0;
पूर्ण

अटल u8 ccu_mult_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_mux_helper_get_parent(&cm->common, &cm->mux);
पूर्ण

अटल पूर्णांक ccu_mult_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ccu_mult *cm = hw_to_ccu_mult(hw);

	वापस ccu_mux_helper_set_parent(&cm->common, &cm->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops ccu_mult_ops = अणु
	.disable	= ccu_mult_disable,
	.enable		= ccu_mult_enable,
	.is_enabled	= ccu_mult_is_enabled,

	.get_parent	= ccu_mult_get_parent,
	.set_parent	= ccu_mult_set_parent,

	.determine_rate	= ccu_mult_determine_rate,
	.recalc_rate	= ccu_mult_recalc_rate,
	.set_rate	= ccu_mult_set_rate,
पूर्ण;
