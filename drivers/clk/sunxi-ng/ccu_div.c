<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_div.h"

अटल अचिन्हित दीर्घ ccu_भाग_round_rate(काष्ठा ccu_mux_पूर्णांकernal *mux,
					काष्ठा clk_hw *parent,
					अचिन्हित दीर्घ *parent_rate,
					अचिन्हित दीर्घ rate,
					व्योम *data)
अणु
	काष्ठा ccu_भाग *cd = data;

	अगर (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= cd->fixed_post_भाग;

	rate = भागider_round_rate_parent(&cd->common.hw, parent,
					 rate, parent_rate,
					 cd->भाग.table, cd->भाग.width,
					 cd->भाग.flags);

	अगर (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= cd->fixed_post_भाग;

	वापस rate;
पूर्ण

अटल व्योम ccu_भाग_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_gate_helper_disable(&cd->common, cd->enable);
पूर्ण

अटल पूर्णांक ccu_भाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_gate_helper_enable(&cd->common, cd->enable);
पूर्ण

अटल पूर्णांक ccu_भाग_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_gate_helper_is_enabled(&cd->common, cd->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_भाग_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);
	अचिन्हित दीर्घ val;
	u32 reg;

	reg = पढ़ोl(cd->common.base + cd->common.reg);
	val = reg >> cd->भाग.shअगरt;
	val &= (1 << cd->भाग.width) - 1;

	parent_rate = ccu_mux_helper_apply_preभाग(&cd->common, &cd->mux, -1,
						  parent_rate);

	val = भागider_recalc_rate(hw, parent_rate, val, cd->भाग.table,
				  cd->भाग.flags, cd->भाग.width);

	अगर (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		val /= cd->fixed_post_भाग;

	वापस val;
पूर्ण

अटल पूर्णांक ccu_भाग_determine_rate(काष्ठा clk_hw *hw,
				काष्ठा clk_rate_request *req)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_mux_helper_determine_rate(&cd->common, &cd->mux,
					     req, ccu_भाग_round_rate, cd);
पूर्ण

अटल पूर्णांक ccu_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;
	u32 reg;

	parent_rate = ccu_mux_helper_apply_preभाग(&cd->common, &cd->mux, -1,
						  parent_rate);

	अगर (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= cd->fixed_post_भाग;

	val = भागider_get_val(rate, parent_rate, cd->भाग.table, cd->भाग.width,
			      cd->भाग.flags);

	spin_lock_irqsave(cd->common.lock, flags);

	reg = पढ़ोl(cd->common.base + cd->common.reg);
	reg &= ~GENMASK(cd->भाग.width + cd->भाग.shअगरt - 1, cd->भाग.shअगरt);

	ग_लिखोl(reg | (val << cd->भाग.shअगरt),
	       cd->common.base + cd->common.reg);

	spin_unlock_irqrestore(cd->common.lock, flags);

	वापस 0;
पूर्ण

अटल u8 ccu_भाग_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_mux_helper_get_parent(&cd->common, &cd->mux);
पूर्ण

अटल पूर्णांक ccu_भाग_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ccu_भाग *cd = hw_to_ccu_भाग(hw);

	वापस ccu_mux_helper_set_parent(&cd->common, &cd->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops ccu_भाग_ops = अणु
	.disable	= ccu_भाग_disable,
	.enable		= ccu_भाग_enable,
	.is_enabled	= ccu_भाग_is_enabled,

	.get_parent	= ccu_भाग_get_parent,
	.set_parent	= ccu_भाग_set_parent,

	.determine_rate	= ccu_भाग_determine_rate,
	.recalc_rate	= ccu_भाग_recalc_rate,
	.set_rate	= ccu_भाग_set_rate,
पूर्ण;
