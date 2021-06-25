<शैली गुरु>
/*
 * TI Multiplexer Clock
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल u8 ti_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_mux *mux = to_clk_omap_mux(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	u32 val;

	/*
	 * FIXME need a mux-specअगरic flag to determine अगर val is bitwise or
	 * numeric. e.g. sys_clkin_ck's clksel field is 3 bits wide, but ranges
	 * from 0x1 to 0x7 (index starts at one)
	 * OTOH, pmd_trace_clk_mux_ck uses a separate bit क्रम each घड़ी, so
	 * val = 0x4 really means "bit 2, index starts at bit 0"
	 */
	val = ti_clk_ll_ops->clk_पढ़ोl(&mux->reg) >> mux->shअगरt;
	val &= mux->mask;

	अगर (mux->table) अणु
		पूर्णांक i;

		क्रम (i = 0; i < num_parents; i++)
			अगर (mux->table[i] == val)
				वापस i;
		वापस -EINVAL;
	पूर्ण

	अगर (val && (mux->flags & CLK_MUX_INDEX_BIT))
		val = ffs(val) - 1;

	अगर (val && (mux->flags & CLK_MUX_INDEX_ONE))
		val--;

	अगर (val >= num_parents)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक ti_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_omap_mux *mux = to_clk_omap_mux(hw);
	u32 val;

	अगर (mux->table) अणु
		index = mux->table[index];
	पूर्ण अन्यथा अणु
		अगर (mux->flags & CLK_MUX_INDEX_BIT)
			index = (1 << ffs(index));

		अगर (mux->flags & CLK_MUX_INDEX_ONE)
			index++;
	पूर्ण

	अगर (mux->flags & CLK_MUX_HIWORD_MASK) अणु
		val = mux->mask << (mux->shअगरt + 16);
	पूर्ण अन्यथा अणु
		val = ti_clk_ll_ops->clk_पढ़ोl(&mux->reg);
		val &= ~(mux->mask << mux->shअगरt);
	पूर्ण
	val |= index << mux->shअगरt;
	ti_clk_ll_ops->clk_ग_लिखोl(val, &mux->reg);
	ti_clk_latch(&mux->reg, mux->latch);

	वापस 0;
पूर्ण

/**
 * clk_mux_save_context - Save the parent selcted in the mux
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Save the parent mux value.
 */
अटल पूर्णांक clk_mux_save_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_mux *mux = to_clk_omap_mux(hw);

	mux->saved_parent = ti_clk_mux_get_parent(hw);
	वापस 0;
पूर्ण

/**
 * clk_mux_restore_context - Restore the parent in the mux
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Restore the saved parent mux value.
 */
अटल व्योम clk_mux_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_mux *mux = to_clk_omap_mux(hw);

	ti_clk_mux_set_parent(hw, mux->saved_parent);
पूर्ण

स्थिर काष्ठा clk_ops ti_clk_mux_ops = अणु
	.get_parent = ti_clk_mux_get_parent,
	.set_parent = ti_clk_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
	.save_context = clk_mux_save_context,
	.restore_context = clk_mux_restore_context,
पूर्ण;

अटल काष्ठा clk *_रेजिस्टर_mux(काष्ठा device *dev, स्थिर अक्षर *name,
				 स्थिर अक्षर * स्थिर *parent_names,
				 u8 num_parents, अचिन्हित दीर्घ flags,
				 काष्ठा clk_omap_reg *reg, u8 shअगरt, u32 mask,
				 s8 latch, u8 clk_mux_flags, u32 *table)
अणु
	काष्ठा clk_omap_mux *mux;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	/* allocate the mux */
	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &ti_clk_mux_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	/* काष्ठा clk_mux assignments */
	स_नकल(&mux->reg, reg, माप(*reg));
	mux->shअगरt = shअगरt;
	mux->mask = mask;
	mux->latch = latch;
	mux->flags = clk_mux_flags;
	mux->table = table;
	mux->hw.init = &init;

	clk = ti_clk_रेजिस्टर(dev, &mux->hw, name);

	अगर (IS_ERR(clk))
		kमुक्त(mux);

	वापस clk;
पूर्ण

/**
 * of_mux_clk_setup - Setup function क्रम simple mux rate घड़ी
 * @node: DT node क्रम the घड़ी
 *
 * Sets up a basic घड़ी multiplexer.
 */
अटल व्योम of_mux_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_omap_reg reg;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	u8 clk_mux_flags = 0;
	u32 mask = 0;
	u32 shअगरt = 0;
	s32 latch = -EINVAL;
	u32 flags = CLK_SET_RATE_NO_REPARENT;

	num_parents = of_clk_get_parent_count(node);
	अगर (num_parents < 2) अणु
		pr_err("mux-clock %pOFn must have parents\n", node);
		वापस;
	पूर्ण
	parent_names = kzalloc((माप(अक्षर *) * num_parents), GFP_KERNEL);
	अगर (!parent_names)
		जाओ cleanup;

	of_clk_parent_fill(node, parent_names, num_parents);

	अगर (ti_clk_get_reg_addr(node, 0, &reg))
		जाओ cleanup;

	of_property_पढ़ो_u32(node, "ti,bit-shift", &shअगरt);

	of_property_पढ़ो_u32(node, "ti,latch-bit", &latch);

	अगर (of_property_पढ़ो_bool(node, "ti,index-starts-at-one"))
		clk_mux_flags |= CLK_MUX_INDEX_ONE;

	अगर (of_property_पढ़ो_bool(node, "ti,set-rate-parent"))
		flags |= CLK_SET_RATE_PARENT;

	/* Generate bit-mask based on parent info */
	mask = num_parents;
	अगर (!(clk_mux_flags & CLK_MUX_INDEX_ONE))
		mask--;

	mask = (1 << fls(mask)) - 1;

	clk = _रेजिस्टर_mux(शून्य, node->name, parent_names, num_parents,
			    flags, &reg, shअगरt, mask, latch, clk_mux_flags,
			    शून्य);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

cleanup:
	kमुक्त(parent_names);
पूर्ण
CLK_OF_DECLARE(mux_clk, "ti,mux-clock", of_mux_clk_setup);

काष्ठा clk_hw *ti_clk_build_component_mux(काष्ठा ti_clk_mux *setup)
अणु
	काष्ठा clk_omap_mux *mux;
	पूर्णांक num_parents;

	अगर (!setup)
		वापस शून्य;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	mux->shअगरt = setup->bit_shअगरt;
	mux->latch = -EINVAL;

	mux->reg.index = setup->module;
	mux->reg.offset = setup->reg;

	अगर (setup->flags & CLKF_INDEX_STARTS_AT_ONE)
		mux->flags |= CLK_MUX_INDEX_ONE;

	num_parents = setup->num_parents;

	mux->mask = num_parents - 1;
	mux->mask = (1 << fls(mux->mask)) - 1;

	वापस &mux->hw;
पूर्ण

अटल व्योम __init of_ti_composite_mux_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_omap_mux *mux;
	अचिन्हित पूर्णांक num_parents;
	u32 val;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस;

	अगर (ti_clk_get_reg_addr(node, 0, &mux->reg))
		जाओ cleanup;

	अगर (!of_property_पढ़ो_u32(node, "ti,bit-shift", &val))
		mux->shअगरt = val;

	अगर (of_property_पढ़ो_bool(node, "ti,index-starts-at-one"))
		mux->flags |= CLK_MUX_INDEX_ONE;

	num_parents = of_clk_get_parent_count(node);

	अगर (num_parents < 2) अणु
		pr_err("%pOFn must have parents\n", node);
		जाओ cleanup;
	पूर्ण

	mux->mask = num_parents - 1;
	mux->mask = (1 << fls(mux->mask)) - 1;

	अगर (!ti_clk_add_component(node, &mux->hw, CLK_COMPONENT_TYPE_MUX))
		वापस;

cleanup:
	kमुक्त(mux);
पूर्ण
CLK_OF_DECLARE(ti_composite_mux_clk_setup, "ti,composite-mux-clock",
	       of_ti_composite_mux_clk_setup);
