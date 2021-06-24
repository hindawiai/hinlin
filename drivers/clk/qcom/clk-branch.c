<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "clk-branch.h"

अटल bool clk_branch_in_hwcg_mode(स्थिर काष्ठा clk_branch *br)
अणु
	u32 val;

	अगर (!br->hwcg_reg)
		वापस false;

	regmap_पढ़ो(br->clkr.regmap, br->hwcg_reg, &val);

	वापस !!(val & BIT(br->hwcg_bit));
पूर्ण

अटल bool clk_branch_check_halt(स्थिर काष्ठा clk_branch *br, bool enabling)
अणु
	bool invert = (br->halt_check == BRANCH_HALT_ENABLE);
	u32 val;

	regmap_पढ़ो(br->clkr.regmap, br->halt_reg, &val);

	val &= BIT(br->halt_bit);
	अगर (invert)
		val = !val;

	वापस !!val == !enabling;
पूर्ण

#घोषणा BRANCH_CLK_OFF			BIT(31)
#घोषणा BRANCH_NOC_FSM_STATUS_SHIFT	28
#घोषणा BRANCH_NOC_FSM_STATUS_MASK	0x7
#घोषणा BRANCH_NOC_FSM_STATUS_ON	(0x2 << BRANCH_NOC_FSM_STATUS_SHIFT)

अटल bool clk_branch2_check_halt(स्थिर काष्ठा clk_branch *br, bool enabling)
अणु
	u32 val;
	u32 mask;

	mask = BRANCH_NOC_FSM_STATUS_MASK << BRANCH_NOC_FSM_STATUS_SHIFT;
	mask |= BRANCH_CLK_OFF;

	regmap_पढ़ो(br->clkr.regmap, br->halt_reg, &val);

	अगर (enabling) अणु
		val &= mask;
		वापस (val & BRANCH_CLK_OFF) == 0 ||
			val == BRANCH_NOC_FSM_STATUS_ON;
	पूर्ण अन्यथा अणु
		वापस val & BRANCH_CLK_OFF;
	पूर्ण
पूर्ण

अटल पूर्णांक clk_branch_रुको(स्थिर काष्ठा clk_branch *br, bool enabling,
		bool (check_halt)(स्थिर काष्ठा clk_branch *, bool))
अणु
	bool voted = br->halt_check & BRANCH_VOTED;
	स्थिर अक्षर *name = clk_hw_get_name(&br->clkr.hw);

	/*
	 * Skip checking halt bit अगर we're explicitly ignoring the bit or the
	 * घड़ी is in hardware gated mode
	 */
	अगर (br->halt_check == BRANCH_HALT_SKIP || clk_branch_in_hwcg_mode(br))
		वापस 0;

	अगर (br->halt_check == BRANCH_HALT_DELAY || (!enabling && voted)) अणु
		udelay(10);
	पूर्ण अन्यथा अगर (br->halt_check == BRANCH_HALT_ENABLE ||
		   br->halt_check == BRANCH_HALT ||
		   (enabling && voted)) अणु
		पूर्णांक count = 200;

		जबतक (count-- > 0) अणु
			अगर (check_halt(br, enabling))
				वापस 0;
			udelay(1);
		पूर्ण
		WARN(1, "%s status stuck at 'o%s'", name,
				enabling ? "ff" : "n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक clk_branch_toggle(काष्ठा clk_hw *hw, bool en,
		bool (check_halt)(स्थिर काष्ठा clk_branch *, bool))
अणु
	काष्ठा clk_branch *br = to_clk_branch(hw);
	पूर्णांक ret;

	अगर (en) अणु
		ret = clk_enable_regmap(hw);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		clk_disable_regmap(hw);
	पूर्ण

	वापस clk_branch_रुको(br, en, check_halt);
पूर्ण

अटल पूर्णांक clk_branch_enable(काष्ठा clk_hw *hw)
अणु
	वापस clk_branch_toggle(hw, true, clk_branch_check_halt);
पूर्ण

अटल व्योम clk_branch_disable(काष्ठा clk_hw *hw)
अणु
	clk_branch_toggle(hw, false, clk_branch_check_halt);
पूर्ण

स्थिर काष्ठा clk_ops clk_branch_ops = अणु
	.enable = clk_branch_enable,
	.disable = clk_branch_disable,
	.is_enabled = clk_is_enabled_regmap,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_branch_ops);

अटल पूर्णांक clk_branch2_enable(काष्ठा clk_hw *hw)
अणु
	वापस clk_branch_toggle(hw, true, clk_branch2_check_halt);
पूर्ण

अटल व्योम clk_branch2_disable(काष्ठा clk_hw *hw)
अणु
	clk_branch_toggle(hw, false, clk_branch2_check_halt);
पूर्ण

स्थिर काष्ठा clk_ops clk_branch2_ops = अणु
	.enable = clk_branch2_enable,
	.disable = clk_branch2_disable,
	.is_enabled = clk_is_enabled_regmap,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_branch2_ops);

स्थिर काष्ठा clk_ops clk_branch2_aon_ops = अणु
	.enable = clk_branch2_enable,
	.is_enabled = clk_is_enabled_regmap,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_branch2_aon_ops);

स्थिर काष्ठा clk_ops clk_branch_simple_ops = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.is_enabled = clk_is_enabled_regmap,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_branch_simple_ops);
