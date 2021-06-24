<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_gate_exclusive - i.MX specअगरic gate घड़ी which is mutually
 * exclusive with other gate घड़ीs
 *
 * @gate: the parent class
 * @exclusive_mask: mask of gate bits which are mutually exclusive to this
 *	gate घड़ी
 *
 * The imx exclusive gate घड़ी is a subclass of basic clk_gate
 * with an addtional mask to indicate which other gate bits in the same
 * रेजिस्टर is mutually exclusive to this gate घड़ी.
 */
काष्ठा clk_gate_exclusive अणु
	काष्ठा clk_gate gate;
	u32 exclusive_mask;
पूर्ण;

अटल पूर्णांक clk_gate_exclusive_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा clk_gate_exclusive *exgate = container_of(gate,
					काष्ठा clk_gate_exclusive, gate);
	u32 val = पढ़ोl(gate->reg);

	अगर (val & exgate->exclusive_mask)
		वापस -EBUSY;

	वापस clk_gate_ops.enable(hw);
पूर्ण

अटल व्योम clk_gate_exclusive_disable(काष्ठा clk_hw *hw)
अणु
	clk_gate_ops.disable(hw);
पूर्ण

अटल पूर्णांक clk_gate_exclusive_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gate_exclusive_ops = अणु
	.enable = clk_gate_exclusive_enable,
	.disable = clk_gate_exclusive_disable,
	.is_enabled = clk_gate_exclusive_is_enabled,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_gate_exclusive(स्थिर अक्षर *name, स्थिर अक्षर *parent,
	 व्योम __iomem *reg, u8 shअगरt, u32 exclusive_mask)
अणु
	काष्ठा clk_gate_exclusive *exgate;
	काष्ठा clk_gate *gate;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (exclusive_mask == 0)
		वापस ERR_PTR(-EINVAL);

	exgate = kzalloc(माप(*exgate), GFP_KERNEL);
	अगर (!exgate)
		वापस ERR_PTR(-ENOMEM);
	gate = &exgate->gate;

	init.name = name;
	init.ops = &clk_gate_exclusive_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent ? &parent : शून्य;
	init.num_parents = parent ? 1 : 0;

	gate->reg = reg;
	gate->bit_idx = shअगरt;
	gate->lock = &imx_ccm_lock;
	gate->hw.init = &init;
	exgate->exclusive_mask = exclusive_mask;

	hw = &gate->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
