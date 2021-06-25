<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zynq UltraScale+ MPSoC घड़ी controller
 *
 *  Copyright (C) 2016-2018 Xilinx
 *
 * Gated घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश "clk-zynqmp.h"

/**
 * काष्ठा clk_gate - gating घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @flags:	hardware-specअगरic flags
 * @clk_id:	Id of घड़ी
 */
काष्ठा zynqmp_clk_gate अणु
	काष्ठा clk_hw hw;
	u8 flags;
	u32 clk_id;
पूर्ण;

#घोषणा to_zynqmp_clk_gate(_hw) container_of(_hw, काष्ठा zynqmp_clk_gate, hw)

/**
 * zynqmp_clk_gate_enable() - Enable घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_clk_gate *gate = to_zynqmp_clk_gate(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = gate->clk_id;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_enable(clk_id);

	अगर (ret)
		pr_warn_once("%s() clock enabled failed for %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस ret;
पूर्ण

/*
 * zynqmp_clk_gate_disable() - Disable घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 */
अटल व्योम zynqmp_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_clk_gate *gate = to_zynqmp_clk_gate(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = gate->clk_id;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_disable(clk_id);

	अगर (ret)
		pr_warn_once("%s() clock disable failed for %s, ret = %d\n",
			     __func__, clk_name, ret);
पूर्ण

/**
 * zynqmp_clk_gate_is_enable() - Check घड़ी state
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: 1 अगर enabled, 0 अगर disabled अन्यथा error code
 */
अटल पूर्णांक zynqmp_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_clk_gate *gate = to_zynqmp_clk_gate(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = gate->clk_id;
	पूर्णांक state, ret;

	ret = zynqmp_pm_घड़ी_माला_लोtate(clk_id, &state);
	अगर (ret) अणु
		pr_warn_once("%s() clock get state failed for %s, ret = %d\n",
			     __func__, clk_name, ret);
		वापस -EIO;
	पूर्ण

	वापस state ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_clk_gate_ops = अणु
	.enable = zynqmp_clk_gate_enable,
	.disable = zynqmp_clk_gate_disable,
	.is_enabled = zynqmp_clk_gate_is_enabled,
पूर्ण;

/**
 * zynqmp_clk_रेजिस्टर_gate() - Register a gate घड़ी with the घड़ी framework
 * @name:		Name of this घड़ी
 * @clk_id:		Id of this घड़ी
 * @parents:		Name of this घड़ी's parents
 * @num_parents:	Number of parents
 * @nodes:		Clock topology node
 *
 * Return: घड़ी hardware of the रेजिस्टरed घड़ी gate
 */
काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_gate(स्थिर अक्षर *name, u32 clk_id,
					स्थिर अक्षर * स्थिर *parents,
					u8 num_parents,
					स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
अणु
	काष्ठा zynqmp_clk_gate *gate;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;
	काष्ठा clk_init_data init;

	/* allocate the gate */
	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &zynqmp_clk_gate_ops;
	init.flags = nodes->flag;
	init.parent_names = parents;
	init.num_parents = 1;

	/* काष्ठा clk_gate assignments */
	gate->flags = nodes->type_flag;
	gate->hw.init = &init;
	gate->clk_id = clk_id;

	hw = &gate->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
