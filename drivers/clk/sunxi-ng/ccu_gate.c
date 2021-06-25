<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"

व्योम ccu_gate_helper_disable(काष्ठा ccu_common *common, u32 gate)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!gate)
		वापस;

	spin_lock_irqsave(common->lock, flags);

	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg & ~gate, common->base + common->reg);

	spin_unlock_irqrestore(common->lock, flags);
पूर्ण

अटल व्योम ccu_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_gate *cg = hw_to_ccu_gate(hw);

	वापस ccu_gate_helper_disable(&cg->common, cg->enable);
पूर्ण

पूर्णांक ccu_gate_helper_enable(काष्ठा ccu_common *common, u32 gate)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!gate)
		वापस 0;

	spin_lock_irqsave(common->lock, flags);

	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg | gate, common->base + common->reg);

	spin_unlock_irqrestore(common->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_gate *cg = hw_to_ccu_gate(hw);

	वापस ccu_gate_helper_enable(&cg->common, cg->enable);
पूर्ण

पूर्णांक ccu_gate_helper_is_enabled(काष्ठा ccu_common *common, u32 gate)
अणु
	अगर (!gate)
		वापस 1;

	वापस पढ़ोl(common->base + common->reg) & gate;
पूर्ण

अटल पूर्णांक ccu_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_gate *cg = hw_to_ccu_gate(hw);

	वापस ccu_gate_helper_is_enabled(&cg->common, cg->enable);
पूर्ण

अटल अचिन्हित दीर्घ ccu_gate_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_gate *cg = hw_to_ccu_gate(hw);
	अचिन्हित दीर्घ rate = parent_rate;

	अगर (cg->common.features & CCU_FEATURE_ALL_PREDIV)
		rate /= cg->common.preभाग;

	वापस rate;
पूर्ण

अटल दीर्घ ccu_gate_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा ccu_gate *cg = hw_to_ccu_gate(hw);
	पूर्णांक भाग = 1;

	अगर (cg->common.features & CCU_FEATURE_ALL_PREDIV)
		भाग = cg->common.preभाग;

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		अचिन्हित दीर्घ best_parent = rate;

		अगर (cg->common.features & CCU_FEATURE_ALL_PREDIV)
			best_parent *= भाग;
		*prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);
	पूर्ण

	वापस *prate / भाग;
पूर्ण

अटल पूर्णांक ccu_gate_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * We must report success but we can करो so unconditionally because
	 * clk_factor_round_rate वापसs values that ensure this call is a
	 * nop.
	 */

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops ccu_gate_ops = अणु
	.disable	= ccu_gate_disable,
	.enable		= ccu_gate_enable,
	.is_enabled	= ccu_gate_is_enabled,
	.round_rate	= ccu_gate_round_rate,
	.set_rate	= ccu_gate_set_rate,
	.recalc_rate	= ccu_gate_recalc_rate,
पूर्ण;
