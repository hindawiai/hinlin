<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * H8S2678 घड़ी driver
 *
 * Copyright 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

अटल DEFINE_SPINLOCK(clklock);

#घोषणा MAX_FREQ 33333333
#घोषणा MIN_FREQ  8000000

काष्ठा pll_घड़ी अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *sckcr;
	व्योम __iomem *pllcr;
पूर्ण;

#घोषणा to_pll_घड़ी(_hw) container_of(_hw, काष्ठा pll_घड़ी, hw)

अटल अचिन्हित दीर्घ pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pll_घड़ी *pll_घड़ी = to_pll_घड़ी(hw);
	पूर्णांक mul = 1 << (पढ़ोb(pll_घड़ी->pllcr) & 3);

	वापस parent_rate * mul;
पूर्ण

अटल दीर्घ pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i, m = -1;
	दीर्घ offset[3];

	अगर (rate > MAX_FREQ)
		rate = MAX_FREQ;
	अगर (rate < MIN_FREQ)
		rate = MIN_FREQ;

	क्रम (i = 0; i < 3; i++)
		offset[i] = असल(rate - (*prate * (1 << i)));
	क्रम (i = 0; i < 3; i++)
		अगर (m < 0)
			m = i;
		अन्यथा
			m = (offset[i] < offset[m])?i:m;

	वापस *prate * (1 << m);
पूर्ण

अटल पूर्णांक pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक pll;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;
	काष्ठा pll_घड़ी *pll_घड़ी = to_pll_घड़ी(hw);

	pll = ((rate / parent_rate) / 2) & 0x03;
	spin_lock_irqsave(&clklock, flags);
	val = पढ़ोb(pll_घड़ी->sckcr);
	val |= 0x08;
	ग_लिखोb(val, pll_घड़ी->sckcr);
	val = पढ़ोb(pll_घड़ी->pllcr);
	val &= ~0x03;
	val |= pll;
	ग_लिखोb(val, pll_घड़ी->pllcr);
	spin_unlock_irqrestore(&clklock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_ops = अणु
	.recalc_rate = pll_recalc_rate,
	.round_rate = pll_round_rate,
	.set_rate = pll_set_rate,
पूर्ण;

अटल व्योम __init h8s2678_pll_clk_setup(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा pll_घड़ी *pll_घड़ी;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	num_parents = of_clk_get_parent_count(node);
	अगर (!num_parents) अणु
		pr_err("%s: no parent found\n", clk_name);
		वापस;
	पूर्ण


	pll_घड़ी = kzalloc(माप(*pll_घड़ी), GFP_KERNEL);
	अगर (!pll_घड़ी)
		वापस;

	pll_घड़ी->sckcr = of_iomap(node, 0);
	अगर (pll_घड़ी->sckcr == शून्य) अणु
		pr_err("%s: failed to map divide register\n", clk_name);
		जाओ मुक्त_घड़ी;
	पूर्ण

	pll_घड़ी->pllcr = of_iomap(node, 1);
	अगर (pll_घड़ी->pllcr == शून्य) अणु
		pr_err("%s: failed to map multiply register\n", clk_name);
		जाओ unmap_sckcr;
	पूर्ण

	parent_name = of_clk_get_parent_name(node, 0);
	init.name = clk_name;
	init.ops = &pll_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pll_घड़ी->hw.init = &init;

	ret = clk_hw_रेजिस्टर(शून्य, &pll_घड़ी->hw);
	अगर (ret) अणु
		pr_err("%s: failed to register %s div clock (%d)\n",
		       __func__, clk_name, ret);
		जाओ unmap_pllcr;
	पूर्ण

	of_clk_add_hw_provider(node, of_clk_hw_simple_get, &pll_घड़ी->hw);
	वापस;

unmap_pllcr:
	iounmap(pll_घड़ी->pllcr);
unmap_sckcr:
	iounmap(pll_घड़ी->sckcr);
मुक्त_घड़ी:
	kमुक्त(pll_घड़ी);
पूर्ण

CLK_OF_DECLARE(h8s2678_भाग_clk, "renesas,h8s2678-pll-clock",
	       h8s2678_pll_clk_setup);
