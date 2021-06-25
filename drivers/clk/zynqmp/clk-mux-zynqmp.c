<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zynq UltraScale+ MPSoC mux
 *
 *  Copyright (C) 2016-2018 Xilinx
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश "clk-zynqmp.h"

/*
 * DOC: basic adjustable multiplexer घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is only affected by parent चयनing.  No clk_set_rate support
 * parent - parent is adjustable through clk_set_parent
 */

/**
 * काष्ठा zynqmp_clk_mux - multiplexer घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @flags:	hardware-specअगरic flags
 * @clk_id:	Id of घड़ी
 */
काष्ठा zynqmp_clk_mux अणु
	काष्ठा clk_hw hw;
	u8 flags;
	u32 clk_id;
पूर्ण;

#घोषणा to_zynqmp_clk_mux(_hw) container_of(_hw, काष्ठा zynqmp_clk_mux, hw)

/**
 * zynqmp_clk_mux_get_parent() - Get parent of घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Return: Parent index
 */
अटल u8 zynqmp_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा zynqmp_clk_mux *mux = to_zynqmp_clk_mux(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = mux->clk_id;
	u32 val;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_getparent(clk_id, &val);

	अगर (ret)
		pr_warn_once("%s() getparent failed for clock: %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस val;
पूर्ण

/**
 * zynqmp_clk_mux_set_parent() - Set parent of घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @index:	Parent index
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा zynqmp_clk_mux *mux = to_zynqmp_clk_mux(hw);
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 clk_id = mux->clk_id;
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_setparent(clk_id, index);

	अगर (ret)
		pr_warn_once("%s() set parent failed for clock: %s, ret = %d\n",
			     __func__, clk_name, ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_clk_mux_ops = अणु
	.get_parent = zynqmp_clk_mux_get_parent,
	.set_parent = zynqmp_clk_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops zynqmp_clk_mux_ro_ops = अणु
	.get_parent = zynqmp_clk_mux_get_parent,
पूर्ण;

/**
 * zynqmp_clk_रेजिस्टर_mux() - Register a mux table with the घड़ी
 *			       framework
 * @name:		Name of this घड़ी
 * @clk_id:		Id of this घड़ी
 * @parents:		Name of this घड़ी's parents
 * @num_parents:	Number of parents
 * @nodes:		Clock topology node
 *
 * Return: घड़ी hardware of the रेजिस्टरed घड़ी mux
 */
काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_mux(स्थिर अक्षर *name, u32 clk_id,
				       स्थिर अक्षर * स्थिर *parents,
				       u8 num_parents,
				       स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
अणु
	काष्ठा zynqmp_clk_mux *mux;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	अगर (nodes->type_flag & CLK_MUX_READ_ONLY)
		init.ops = &zynqmp_clk_mux_ro_ops;
	अन्यथा
		init.ops = &zynqmp_clk_mux_ops;
	init.flags = nodes->flag;
	init.parent_names = parents;
	init.num_parents = num_parents;
	mux->flags = nodes->type_flag;
	mux->hw.init = &init;
	mux->clk_id = clk_id;

	hw = &mux->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(hw);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
