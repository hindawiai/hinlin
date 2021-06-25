<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Zynq PLL driver
 *
 *  Copyright (C) 2013 Xilinx
 *
 *  Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */
#समावेश <linux/clk/zynq.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

/**
 * काष्ठा zynq_pll
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @pll_ctrl:	PLL control रेजिस्टर
 * @pll_status:	PLL status रेजिस्टर
 * @lock:	Register lock
 * @lockbit:	Indicates the associated PLL_LOCKED bit in the PLL status
 *		रेजिस्टर.
 */
काष्ठा zynq_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*pll_ctrl;
	व्योम __iomem	*pll_status;
	spinlock_t	*lock;
	u8		lockbit;
पूर्ण;
#घोषणा to_zynq_pll(_hw)	container_of(_hw, काष्ठा zynq_pll, hw)

/* Register bitfield defines */
#घोषणा PLLCTRL_FBDIV_MASK	0x7f000
#घोषणा PLLCTRL_FBDIV_SHIFT	12
#घोषणा PLLCTRL_BPQUAL_MASK	(1 << 3)
#घोषणा PLLCTRL_PWRDWN_MASK	2
#घोषणा PLLCTRL_PWRDWN_SHIFT	1
#घोषणा PLLCTRL_RESET_MASK	1
#घोषणा PLLCTRL_RESET_SHIFT	0

#घोषणा PLL_FBDIV_MIN	13
#घोषणा PLL_FBDIV_MAX	66

/**
 * zynq_pll_round_rate() - Round a घड़ी frequency
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate:	Desired घड़ी frequency
 * @prate:	Clock frequency of parent घड़ी
 * Returns frequency बंदst to @rate the hardware can generate.
 */
अटल दीर्घ zynq_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *prate)
अणु
	u32 fbभाग;

	fbभाग = DIV_ROUND_CLOSEST(rate, *prate);
	अगर (fbभाग < PLL_FBDIV_MIN)
		fbभाग = PLL_FBDIV_MIN;
	अन्यथा अगर (fbभाग > PLL_FBDIV_MAX)
		fbभाग = PLL_FBDIV_MAX;

	वापस *prate * fbभाग;
पूर्ण

/**
 * zynq_pll_recalc_rate() - Recalculate घड़ी frequency
 * @hw:			Handle between common and hardware-specअगरic पूर्णांकerfaces
 * @parent_rate:	Clock frequency of parent घड़ी
 * Returns current घड़ी frequency.
 */
अटल अचिन्हित दीर्घ zynq_pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा zynq_pll *clk = to_zynq_pll(hw);
	u32 fbभाग;

	/*
	 * makes probably sense to redundantly save fbभाग in the काष्ठा
	 * zynq_pll to save the IO access.
	 */
	fbभाग = (पढ़ोl(clk->pll_ctrl) & PLLCTRL_FBDIV_MASK) >>
			PLLCTRL_FBDIV_SHIFT;

	वापस parent_rate * fbभाग;
पूर्ण

/**
 * zynq_pll_is_enabled - Check अगर a घड़ी is enabled
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * Returns 1 अगर the घड़ी is enabled, 0 otherwise.
 *
 * Not sure this is a good idea, but since disabled means bypassed क्रम
 * this घड़ी implementation we say we are always enabled.
 */
अटल पूर्णांक zynq_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags = 0;
	u32 reg;
	काष्ठा zynq_pll *clk = to_zynq_pll(hw);

	spin_lock_irqsave(clk->lock, flags);

	reg = पढ़ोl(clk->pll_ctrl);

	spin_unlock_irqrestore(clk->lock, flags);

	वापस !(reg & (PLLCTRL_RESET_MASK | PLLCTRL_PWRDWN_MASK));
पूर्ण

/**
 * zynq_pll_enable - Enable घड़ी
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * Returns 0 on success
 */
अटल पूर्णांक zynq_pll_enable(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags = 0;
	u32 reg;
	काष्ठा zynq_pll *clk = to_zynq_pll(hw);

	अगर (zynq_pll_is_enabled(hw))
		वापस 0;

	pr_info("PLL: enable\n");

	/* Power up PLL and रुको क्रम lock */
	spin_lock_irqsave(clk->lock, flags);

	reg = पढ़ोl(clk->pll_ctrl);
	reg &= ~(PLLCTRL_RESET_MASK | PLLCTRL_PWRDWN_MASK);
	ग_लिखोl(reg, clk->pll_ctrl);
	जबतक (!(पढ़ोl(clk->pll_status) & (1 << clk->lockbit)))
		;

	spin_unlock_irqrestore(clk->lock, flags);

	वापस 0;
पूर्ण

/**
 * zynq_pll_disable - Disable घड़ी
 * @hw:		Handle between common and hardware-specअगरic पूर्णांकerfaces
 * Returns 0 on success
 */
अटल व्योम zynq_pll_disable(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags = 0;
	u32 reg;
	काष्ठा zynq_pll *clk = to_zynq_pll(hw);

	अगर (!zynq_pll_is_enabled(hw))
		वापस;

	pr_info("PLL: shutdown\n");

	/* shut करोwn PLL */
	spin_lock_irqsave(clk->lock, flags);

	reg = पढ़ोl(clk->pll_ctrl);
	reg |= PLLCTRL_RESET_MASK | PLLCTRL_PWRDWN_MASK;
	ग_लिखोl(reg, clk->pll_ctrl);

	spin_unlock_irqrestore(clk->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops zynq_pll_ops = अणु
	.enable = zynq_pll_enable,
	.disable = zynq_pll_disable,
	.is_enabled = zynq_pll_is_enabled,
	.round_rate = zynq_pll_round_rate,
	.recalc_rate = zynq_pll_recalc_rate
पूर्ण;

/**
 * clk_रेजिस्टर_zynq_pll() - Register PLL with the घड़ी framework
 * @name:	PLL name
 * @parent:	Parent घड़ी name
 * @pll_ctrl:	Poपूर्णांकer to PLL control रेजिस्टर
 * @pll_status:	Poपूर्णांकer to PLL status रेजिस्टर
 * @lock_index:	Bit index to this PLL's lock status bit in @pll_status
 * @lock:	Register lock
 * Returns handle to the रेजिस्टरed घड़ी.
 */
काष्ठा clk *clk_रेजिस्टर_zynq_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *pll_ctrl, व्योम __iomem *pll_status, u8 lock_index,
		spinlock_t *lock)
अणु
	काष्ठा zynq_pll *pll;
	काष्ठा clk *clk;
	u32 reg;
	स्थिर अक्षर *parent_arr[1] = अणुparentपूर्ण;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा clk_init_data initd = अणु
		.name = name,
		.parent_names = parent_arr,
		.ops = &zynq_pll_ops,
		.num_parents = 1,
		.flags = 0
	पूर्ण;

	pll = kदो_स्मृति(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	/* Populate the काष्ठा */
	pll->hw.init = &initd;
	pll->pll_ctrl = pll_ctrl;
	pll->pll_status = pll_status;
	pll->lockbit = lock_index;
	pll->lock = lock;

	spin_lock_irqsave(pll->lock, flags);

	reg = पढ़ोl(pll->pll_ctrl);
	reg &= ~PLLCTRL_BPQUAL_MASK;
	ग_लिखोl(reg, pll->pll_ctrl);

	spin_unlock_irqrestore(pll->lock, flags);

	clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		जाओ मुक्त_pll;

	वापस clk;

मुक्त_pll:
	kमुक्त(pll);

	वापस clk;
पूर्ण
