<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018 NXP
 *	Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "clk-scu.h"

अटल DEFINE_SPINLOCK(imx_lpcg_scu_lock);

#घोषणा CLK_GATE_SCU_LPCG_MASK		0x3
#घोषणा CLK_GATE_SCU_LPCG_HW_SEL	BIT(0)
#घोषणा CLK_GATE_SCU_LPCG_SW_SEL	BIT(1)

/*
 * काष्ठा clk_lpcg_scu - Description of LPCG घड़ी
 *
 * @hw: clk_hw of this LPCG
 * @reg: रेजिस्टर of this LPCG घड़ी
 * @bit_idx: bit index of this LPCG घड़ी
 * @hw_gate: HW स्वतः gate enable
 *
 * This काष्ठाure describes one LPCG घड़ी
 */
काष्ठा clk_lpcg_scu अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	u8 bit_idx;
	bool hw_gate;

	/* क्रम state save&restore */
	u32 state;
पूर्ण;

#घोषणा to_clk_lpcg_scu(_hw) container_of(_hw, काष्ठा clk_lpcg_scu, hw)

अटल पूर्णांक clk_lpcg_scu_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_lpcg_scu *clk = to_clk_lpcg_scu(hw);
	अचिन्हित दीर्घ flags;
	u32 reg, val;

	spin_lock_irqsave(&imx_lpcg_scu_lock, flags);

	reg = पढ़ोl_relaxed(clk->reg);
	reg &= ~(CLK_GATE_SCU_LPCG_MASK << clk->bit_idx);

	val = CLK_GATE_SCU_LPCG_SW_SEL;
	अगर (clk->hw_gate)
		val |= CLK_GATE_SCU_LPCG_HW_SEL;

	reg |= val << clk->bit_idx;
	ग_लिखोl(reg, clk->reg);

	spin_unlock_irqrestore(&imx_lpcg_scu_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_lpcg_scu_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_lpcg_scu *clk = to_clk_lpcg_scu(hw);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&imx_lpcg_scu_lock, flags);

	reg = पढ़ोl_relaxed(clk->reg);
	reg &= ~(CLK_GATE_SCU_LPCG_MASK << clk->bit_idx);
	ग_लिखोl(reg, clk->reg);

	spin_unlock_irqrestore(&imx_lpcg_scu_lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_lpcg_scu_ops = अणु
	.enable = clk_lpcg_scu_enable,
	.disable = clk_lpcg_scu_disable,
पूर्ण;

काष्ठा clk_hw *__imx_clk_lpcg_scu(काष्ठा device *dev, स्थिर अक्षर *name,
				  स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
				  व्योम __iomem *reg, u8 bit_idx, bool hw_gate)
अणु
	काष्ठा clk_lpcg_scu *clk;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->reg = reg;
	clk->bit_idx = bit_idx;
	clk->hw_gate = hw_gate;

	init.name = name;
	init.ops = &clk_lpcg_scu_ops;
	init.flags = CLK_SET_RATE_PARENT | flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	clk->hw.init = &init;

	hw = &clk->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(clk);
		hw = ERR_PTR(ret);
		वापस hw;
	पूर्ण

	अगर (dev)
		dev_set_drvdata(dev, clk);

	वापस hw;
पूर्ण

व्योम imx_clk_lpcg_scu_unरेजिस्टर(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_lpcg_scu *clk = to_clk_lpcg_scu(hw);

	clk_hw_unरेजिस्टर(&clk->hw);
	kमुक्त(clk);
पूर्ण

अटल पूर्णांक __maybe_unused imx_clk_lpcg_scu_suspend(काष्ठा device *dev)
अणु
	काष्ठा clk_lpcg_scu *clk = dev_get_drvdata(dev);

	clk->state = पढ़ोl_relaxed(clk->reg);
	dev_dbg(dev, "save lpcg state 0x%x\n", clk->state);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_clk_lpcg_scu_resume(काष्ठा device *dev)
अणु
	काष्ठा clk_lpcg_scu *clk = dev_get_drvdata(dev);

	/*
	 * FIXME: Someबार ग_लिखोs करोn't work unless the CPU issues
	 * them twice
	 */

	ग_लिखोl(clk->state, clk->reg);
	ग_लिखोl(clk->state, clk->reg);
	dev_dbg(dev, "restore lpcg state 0x%x\n", clk->state);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops imx_clk_lpcg_scu_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx_clk_lpcg_scu_suspend,
				      imx_clk_lpcg_scu_resume)
पूर्ण;
