<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "clk.h"

अटल DEFINE_SPINLOCK(periph_ref_lock);

/* Macros to assist peripheral gate घड़ी */
#घोषणा पढ़ो_enb(gate) \
	पढ़ोl_relaxed(gate->clk_base + (gate->regs->enb_reg))
#घोषणा ग_लिखो_enb_set(val, gate) \
	ग_लिखोl_relaxed(val, gate->clk_base + (gate->regs->enb_set_reg))
#घोषणा ग_लिखो_enb_clr(val, gate) \
	ग_लिखोl_relaxed(val, gate->clk_base + (gate->regs->enb_clr_reg))

#घोषणा पढ़ो_rst(gate) \
	पढ़ोl_relaxed(gate->clk_base + (gate->regs->rst_reg))
#घोषणा ग_लिखो_rst_clr(val, gate) \
	ग_लिखोl_relaxed(val, gate->clk_base + (gate->regs->rst_clr_reg))

#घोषणा periph_clk_to_bit(gate) (1 << (gate->clk_num % 32))

#घोषणा LVL2_CLK_GATE_OVRE 0x554

/* Peripheral gate घड़ी ops */
अटल पूर्णांक clk_periph_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_gate *gate = to_clk_periph_gate(hw);
	पूर्णांक state = 1;

	अगर (!(पढ़ो_enb(gate) & periph_clk_to_bit(gate)))
		state = 0;

	अगर (!(gate->flags & TEGRA_PERIPH_NO_RESET))
		अगर (पढ़ो_rst(gate) & periph_clk_to_bit(gate))
			state = 0;

	वापस state;
पूर्ण

अटल पूर्णांक clk_periph_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_gate *gate = to_clk_periph_gate(hw);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&periph_ref_lock, flags);

	gate->enable_refcnt[gate->clk_num]++;
	अगर (gate->enable_refcnt[gate->clk_num] > 1) अणु
		spin_unlock_irqrestore(&periph_ref_lock, flags);
		वापस 0;
	पूर्ण

	ग_लिखो_enb_set(periph_clk_to_bit(gate), gate);
	udelay(2);

	अगर (!(gate->flags & TEGRA_PERIPH_NO_RESET) &&
	    !(gate->flags & TEGRA_PERIPH_MANUAL_RESET)) अणु
		अगर (पढ़ो_rst(gate) & periph_clk_to_bit(gate)) अणु
			udelay(5); /* reset propogation delay */
			ग_लिखो_rst_clr(periph_clk_to_bit(gate), gate);
		पूर्ण
	पूर्ण

	अगर (gate->flags & TEGRA_PERIPH_WAR_1005168) अणु
		ग_लिखोl_relaxed(0, gate->clk_base + LVL2_CLK_GATE_OVRE);
		ग_लिखोl_relaxed(BIT(22), gate->clk_base + LVL2_CLK_GATE_OVRE);
		udelay(1);
		ग_लिखोl_relaxed(0, gate->clk_base + LVL2_CLK_GATE_OVRE);
	पूर्ण

	spin_unlock_irqrestore(&periph_ref_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_periph_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_gate *gate = to_clk_periph_gate(hw);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&periph_ref_lock, flags);

	gate->enable_refcnt[gate->clk_num]--;
	अगर (gate->enable_refcnt[gate->clk_num] > 0) अणु
		spin_unlock_irqrestore(&periph_ref_lock, flags);
		वापस;
	पूर्ण

	/*
	 * If peripheral is in the APB bus then पढ़ो the APB bus to
	 * flush the ग_लिखो operation in apb bus. This will aव्योम the
	 * peripheral access after disabling घड़ी
	 */
	अगर (gate->flags & TEGRA_PERIPH_ON_APB)
		tegra_पढ़ो_chipid();

	ग_लिखो_enb_clr(periph_clk_to_bit(gate), gate);

	spin_unlock_irqrestore(&periph_ref_lock, flags);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_periph_gate_ops = अणु
	.is_enabled = clk_periph_is_enabled,
	.enable = clk_periph_enable,
	.disable = clk_periph_disable,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_periph_gate(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, u8 gate_flags, व्योम __iomem *clk_base,
		अचिन्हित दीर्घ flags, पूर्णांक clk_num, पूर्णांक *enable_refcnt)
अणु
	काष्ठा tegra_clk_periph_gate *gate;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	स्थिर काष्ठा tegra_clk_periph_regs *pregs;

	pregs = get_reg_bank(clk_num);
	अगर (!pregs)
		वापस ERR_PTR(-EINVAL);

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate) अणु
		pr_err("%s: could not allocate periph gate clk\n", __func__);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	init.name = name;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	init.ops = &tegra_clk_periph_gate_ops;

	gate->magic = TEGRA_CLK_PERIPH_GATE_MAGIC;
	gate->clk_base = clk_base;
	gate->clk_num = clk_num;
	gate->flags = gate_flags;
	gate->enable_refcnt = enable_refcnt;
	gate->regs = pregs;

	अगर (पढ़ो_enb(gate) & periph_clk_to_bit(gate))
		enable_refcnt[clk_num]++;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	gate->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &gate->hw);
	अगर (IS_ERR(clk))
		kमुक्त(gate);

	वापस clk;
पूर्ण
