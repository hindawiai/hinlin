<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sysctrl घड़ी implementation क्रम ux500 platक्रमm.
 *
 * Copyright (C) 2013 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/abx500/ab8500-sysctrl.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

#घोषणा SYSCTRL_MAX_NUM_PARENTS 4

#घोषणा to_clk_sysctrl(_hw) container_of(_hw, काष्ठा clk_sysctrl, hw)

काष्ठा clk_sysctrl अणु
	काष्ठा clk_hw hw;
	काष्ठा device *dev;
	u8 parent_index;
	u16 reg_sel[SYSCTRL_MAX_NUM_PARENTS];
	u8 reg_mask[SYSCTRL_MAX_NUM_PARENTS];
	u8 reg_bits[SYSCTRL_MAX_NUM_PARENTS];
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ enable_delay_us;
पूर्ण;

/* Sysctrl घड़ी operations. */

अटल पूर्णांक clk_sysctrl_prepare(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_sysctrl *clk = to_clk_sysctrl(hw);

	ret = ab8500_sysctrl_ग_लिखो(clk->reg_sel[0], clk->reg_mask[0],
				clk->reg_bits[0]);

	अगर (!ret && clk->enable_delay_us)
		usleep_range(clk->enable_delay_us, clk->enable_delay_us +
			     (clk->enable_delay_us >> 2));

	वापस ret;
पूर्ण

अटल व्योम clk_sysctrl_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sysctrl *clk = to_clk_sysctrl(hw);
	अगर (ab8500_sysctrl_clear(clk->reg_sel[0], clk->reg_mask[0]))
		dev_err(clk->dev, "clk_sysctrl: %s fail to clear %s.\n",
			__func__, clk_hw_get_name(hw));
पूर्ण

अटल अचिन्हित दीर्घ clk_sysctrl_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sysctrl *clk = to_clk_sysctrl(hw);
	वापस clk->rate;
पूर्ण

अटल पूर्णांक clk_sysctrl_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_sysctrl *clk = to_clk_sysctrl(hw);
	u8 old_index = clk->parent_index;
	पूर्णांक ret = 0;

	अगर (clk->reg_sel[old_index]) अणु
		ret = ab8500_sysctrl_clear(clk->reg_sel[old_index],
					clk->reg_mask[old_index]);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (clk->reg_sel[index]) अणु
		ret = ab8500_sysctrl_ग_लिखो(clk->reg_sel[index],
					clk->reg_mask[index],
					clk->reg_bits[index]);
		अगर (ret) अणु
			अगर (clk->reg_sel[old_index])
				ab8500_sysctrl_ग_लिखो(clk->reg_sel[old_index],
						clk->reg_mask[old_index],
						clk->reg_bits[old_index]);
			वापस ret;
		पूर्ण
	पूर्ण
	clk->parent_index = index;

	वापस ret;
पूर्ण

अटल u8 clk_sysctrl_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sysctrl *clk = to_clk_sysctrl(hw);
	वापस clk->parent_index;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_sysctrl_gate_ops = अणु
	.prepare = clk_sysctrl_prepare,
	.unprepare = clk_sysctrl_unprepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_sysctrl_gate_fixed_rate_ops = अणु
	.prepare = clk_sysctrl_prepare,
	.unprepare = clk_sysctrl_unprepare,
	.recalc_rate = clk_sysctrl_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_sysctrl_set_parent_ops = अणु
	.set_parent = clk_sysctrl_set_parent,
	.get_parent = clk_sysctrl_get_parent,
पूर्ण;

अटल काष्ठा clk *clk_reg_sysctrl(काष्ठा device *dev,
				स्थिर अक्षर *name,
				स्थिर अक्षर **parent_names,
				u8 num_parents,
				u16 *reg_sel,
				u8 *reg_mask,
				u8 *reg_bits,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ enable_delay_us,
				अचिन्हित दीर्घ flags,
				स्थिर काष्ठा clk_ops *clk_sysctrl_ops)
अणु
	काष्ठा clk_sysctrl *clk;
	काष्ठा clk_init_data clk_sysctrl_init;
	काष्ठा clk *clk_reg;
	पूर्णांक i;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	अगर (!name || (num_parents > SYSCTRL_MAX_NUM_PARENTS)) अणु
		dev_err(dev, "clk_sysctrl: invalid arguments passed\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	clk = devm_kzalloc(dev, माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	/* set मुख्य घड़ी रेजिस्टरs */
	clk->reg_sel[0] = reg_sel[0];
	clk->reg_bits[0] = reg_bits[0];
	clk->reg_mask[0] = reg_mask[0];

	/* handle घड़ीs with more than one parent */
	क्रम (i = 1; i < num_parents; i++) अणु
		clk->reg_sel[i] = reg_sel[i];
		clk->reg_bits[i] = reg_bits[i];
		clk->reg_mask[i] = reg_mask[i];
	पूर्ण

	clk->parent_index = 0;
	clk->rate = rate;
	clk->enable_delay_us = enable_delay_us;
	clk->dev = dev;

	clk_sysctrl_init.name = name;
	clk_sysctrl_init.ops = clk_sysctrl_ops;
	clk_sysctrl_init.flags = flags;
	clk_sysctrl_init.parent_names = parent_names;
	clk_sysctrl_init.num_parents = num_parents;
	clk->hw.init = &clk_sysctrl_init;

	clk_reg = devm_clk_रेजिस्टर(clk->dev, &clk->hw);
	अगर (IS_ERR(clk_reg))
		dev_err(dev, "clk_sysctrl: clk_register failed\n");

	वापस clk_reg;
पूर्ण

काष्ठा clk *clk_reg_sysctrl_gate(काष्ठा device *dev,
				स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				u16 reg_sel,
				u8 reg_mask,
				u8 reg_bits,
				अचिन्हित दीर्घ enable_delay_us,
				अचिन्हित दीर्घ flags)
अणु
	स्थिर अक्षर **parent_names = (parent_name ? &parent_name : शून्य);
	u8 num_parents = (parent_name ? 1 : 0);

	वापस clk_reg_sysctrl(dev, name, parent_names, num_parents,
			&reg_sel, &reg_mask, &reg_bits, 0, enable_delay_us,
			flags, &clk_sysctrl_gate_ops);
पूर्ण

काष्ठा clk *clk_reg_sysctrl_gate_fixed_rate(काष्ठा device *dev,
					स्थिर अक्षर *name,
					स्थिर अक्षर *parent_name,
					u16 reg_sel,
					u8 reg_mask,
					u8 reg_bits,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ enable_delay_us,
					अचिन्हित दीर्घ flags)
अणु
	स्थिर अक्षर **parent_names = (parent_name ? &parent_name : शून्य);
	u8 num_parents = (parent_name ? 1 : 0);

	वापस clk_reg_sysctrl(dev, name, parent_names, num_parents,
			&reg_sel, &reg_mask, &reg_bits,
			rate, enable_delay_us, flags,
			&clk_sysctrl_gate_fixed_rate_ops);
पूर्ण

काष्ठा clk *clk_reg_sysctrl_set_parent(काष्ठा device *dev,
				स्थिर अक्षर *name,
				स्थिर अक्षर **parent_names,
				u8 num_parents,
				u16 *reg_sel,
				u8 *reg_mask,
				u8 *reg_bits,
				अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_sysctrl(dev, name, parent_names, num_parents,
			reg_sel, reg_mask, reg_bits, 0, 0, flags,
			&clk_sysctrl_set_parent_ops);
पूर्ण
