<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा TCON_CH1_SCLK2_PARENTS		4

#घोषणा TCON_CH1_SCLK2_GATE_BIT		BIT(31)
#घोषणा TCON_CH1_SCLK2_MUX_MASK		3
#घोषणा TCON_CH1_SCLK2_MUX_SHIFT	24
#घोषणा TCON_CH1_SCLK2_DIV_MASK		0xf
#घोषणा TCON_CH1_SCLK2_DIV_SHIFT	0

#घोषणा TCON_CH1_SCLK1_GATE_BIT		BIT(15)
#घोषणा TCON_CH1_SCLK1_HALF_BIT		BIT(11)

काष्ठा tcon_ch1_clk अणु
	काष्ठा clk_hw	hw;
	spinlock_t	lock;
	व्योम __iomem	*reg;
पूर्ण;

#घोषणा hw_to_tclk(hw)	container_of(hw, काष्ठा tcon_ch1_clk, hw)

अटल व्योम tcon_ch1_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&tclk->lock, flags);
	reg = पढ़ोl(tclk->reg);
	reg &= ~(TCON_CH1_SCLK2_GATE_BIT | TCON_CH1_SCLK1_GATE_BIT);
	ग_लिखोl(reg, tclk->reg);
	spin_unlock_irqrestore(&tclk->lock, flags);
पूर्ण

अटल पूर्णांक tcon_ch1_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&tclk->lock, flags);
	reg = पढ़ोl(tclk->reg);
	reg |= TCON_CH1_SCLK2_GATE_BIT | TCON_CH1_SCLK1_GATE_BIT;
	ग_लिखोl(reg, tclk->reg);
	spin_unlock_irqrestore(&tclk->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tcon_ch1_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	u32 reg;

	reg = पढ़ोl(tclk->reg);
	वापस reg & (TCON_CH1_SCLK2_GATE_BIT | TCON_CH1_SCLK1_GATE_BIT);
पूर्ण

अटल u8 tcon_ch1_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	u32 reg;

	reg = पढ़ोl(tclk->reg) >> TCON_CH1_SCLK2_MUX_SHIFT;
	reg &= reg >> TCON_CH1_SCLK2_MUX_MASK;

	वापस reg;
पूर्ण

अटल पूर्णांक tcon_ch1_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&tclk->lock, flags);
	reg = पढ़ोl(tclk->reg);
	reg &= ~(TCON_CH1_SCLK2_MUX_MASK << TCON_CH1_SCLK2_MUX_SHIFT);
	reg |= index << TCON_CH1_SCLK2_MUX_SHIFT;
	ग_लिखोl(reg, tclk->reg);
	spin_unlock_irqrestore(&tclk->lock, flags);

	वापस 0;
पूर्ण;

अटल अचिन्हित दीर्घ tcon_ch1_calc_भागider(अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ parent_rate,
					   u8 *भाग,
					   bool *half)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	u8 best_m = 0, m;
	bool is_द्विगुन;

	क्रम (m = 1; m < 16; m++) अणु
		u8 d;

		क्रम (d = 1; d < 3; d++) अणु
			अचिन्हित दीर्घ पंचांगp_rate;

			पंचांगp_rate = parent_rate / m / d;

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर (!best_rate ||
			    (rate - पंचांगp_rate) < (rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_m = m;
				is_द्विगुन = d;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (भाग && half) अणु
		*भाग = best_m;
		*half = is_द्विगुन;
	पूर्ण

	वापस best_rate;
पूर्ण

अटल पूर्णांक tcon_ch1_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *req)
अणु
	दीर्घ best_rate = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		अचिन्हित दीर्घ parent_rate;
		अचिन्हित दीर्घ पंचांगp_rate;
		काष्ठा clk_hw *parent;

		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = clk_hw_get_rate(parent);

		पंचांगp_rate = tcon_ch1_calc_भागider(req->rate, parent_rate,
						 शून्य, शून्य);

		अगर (best_rate < 0 ||
		    (req->rate - पंचांगp_rate) < (req->rate - best_rate)) अणु
			best_rate = पंचांगp_rate;
			req->best_parent_rate = parent_rate;
			req->best_parent_hw = parent;
		पूर्ण
	पूर्ण

	अगर (best_rate < 0)
		वापस best_rate;

	req->rate = best_rate;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ tcon_ch1_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	u32 reg;

	reg = पढ़ोl(tclk->reg);

	parent_rate /= (reg & TCON_CH1_SCLK2_DIV_MASK) + 1;

	अगर (reg & TCON_CH1_SCLK1_HALF_BIT)
		parent_rate /= 2;

	वापस parent_rate;
पूर्ण

अटल पूर्णांक tcon_ch1_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tcon_ch1_clk *tclk = hw_to_tclk(hw);
	अचिन्हित दीर्घ flags;
	bool half;
	u8 भाग_m;
	u32 reg;

	tcon_ch1_calc_भागider(rate, parent_rate, &भाग_m, &half);

	spin_lock_irqsave(&tclk->lock, flags);
	reg = पढ़ोl(tclk->reg);
	reg &= ~(TCON_CH1_SCLK2_DIV_MASK | TCON_CH1_SCLK1_HALF_BIT);
	reg |= (भाग_m - 1) & TCON_CH1_SCLK2_DIV_MASK;

	अगर (half)
		reg |= TCON_CH1_SCLK1_HALF_BIT;

	ग_लिखोl(reg, tclk->reg);
	spin_unlock_irqrestore(&tclk->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops tcon_ch1_ops = अणु
	.disable	= tcon_ch1_disable,
	.enable		= tcon_ch1_enable,
	.is_enabled	= tcon_ch1_is_enabled,

	.get_parent	= tcon_ch1_get_parent,
	.set_parent	= tcon_ch1_set_parent,

	.determine_rate	= tcon_ch1_determine_rate,
	.recalc_rate	= tcon_ch1_recalc_rate,
	.set_rate	= tcon_ch1_set_rate,
पूर्ण;

अटल व्योम __init tcon_ch1_setup(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *parents[TCON_CH1_SCLK2_PARENTS];
	स्थिर अक्षर *clk_name = node->name;
	काष्ठा clk_init_data init;
	काष्ठा tcon_ch1_clk *tclk;
	काष्ठा resource res;
	काष्ठा clk *clk;
	व्योम __iomem *reg;
	पूर्णांक ret;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%s: Could not map the clock registers\n", clk_name);
		वापस;
	पूर्ण

	ret = of_clk_parent_fill(node, parents, TCON_CH1_SCLK2_PARENTS);
	अगर (ret != TCON_CH1_SCLK2_PARENTS) अणु
		pr_err("%s Could not retrieve the parents\n", clk_name);
		जाओ err_unmap;
	पूर्ण

	tclk = kzalloc(माप(*tclk), GFP_KERNEL);
	अगर (!tclk)
		जाओ err_unmap;

	init.name = clk_name;
	init.ops = &tcon_ch1_ops;
	init.parent_names = parents;
	init.num_parents = TCON_CH1_SCLK2_PARENTS;
	init.flags = CLK_SET_RATE_PARENT;

	tclk->reg = reg;
	tclk->hw.init = &init;
	spin_lock_init(&tclk->lock);

	clk = clk_रेजिस्टर(शून्य, &tclk->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: Couldn't register the clock\n", clk_name);
		जाओ err_मुक्त_data;
	पूर्ण

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret) अणु
		pr_err("%s: Couldn't register our clock provider\n", clk_name);
		जाओ err_unरेजिस्टर_clk;
	पूर्ण

	वापस;

err_unरेजिस्टर_clk:
	clk_unरेजिस्टर(clk);
err_मुक्त_data:
	kमुक्त(tclk);
err_unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
पूर्ण

CLK_OF_DECLARE(tcon_ch1, "allwinner,sun4i-a10-tcon-ch1-clk",
	       tcon_ch1_setup);
