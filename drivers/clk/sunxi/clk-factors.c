<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Emilio Lथकpez <emilio@elopez.com.ar>
 *
 * Adjustable factor-based घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "clk-factors.h"

/*
 * DOC: basic adjustable factor-based घड़ी
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.
 *        clk->rate = (parent->rate * N * (K + 1) >> P) / (M + 1)
 * parent - fixed parent.  No clk_set_parent support
 */

#घोषणा to_clk_factors(_hw) container_of(_hw, काष्ठा clk_factors, hw)

#घोषणा FACTORS_MAX_PARENTS		5

#घोषणा SETMASK(len, pos)		(((1U << (len)) - 1) << (pos))
#घोषणा CLRMASK(len, pos)		(~(SETMASK(len, pos)))
#घोषणा FACTOR_GET(bit, len, reg)	(((reg) & SETMASK(len, bit)) >> (bit))

#घोषणा FACTOR_SET(bit, len, reg, val) \
	(((reg) & CLRMASK(len, bit)) | (val << (bit)))

अटल अचिन्हित दीर्घ clk_factors_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	u8 n = 1, k = 0, p = 0, m = 0;
	u32 reg;
	अचिन्हित दीर्घ rate;
	काष्ठा clk_factors *factors = to_clk_factors(hw);
	स्थिर काष्ठा clk_factors_config *config = factors->config;

	/* Fetch the रेजिस्टर value */
	reg = पढ़ोl(factors->reg);

	/* Get each inभागidual factor अगर applicable */
	अगर (config->nwidth != SUNXI_FACTORS_NOT_APPLICABLE)
		n = FACTOR_GET(config->nshअगरt, config->nwidth, reg);
	अगर (config->kwidth != SUNXI_FACTORS_NOT_APPLICABLE)
		k = FACTOR_GET(config->kshअगरt, config->kwidth, reg);
	अगर (config->mwidth != SUNXI_FACTORS_NOT_APPLICABLE)
		m = FACTOR_GET(config->mshअगरt, config->mwidth, reg);
	अगर (config->pwidth != SUNXI_FACTORS_NOT_APPLICABLE)
		p = FACTOR_GET(config->pshअगरt, config->pwidth, reg);

	अगर (factors->recalc) अणु
		काष्ठा factors_request factors_req = अणु
			.parent_rate = parent_rate,
			.n = n,
			.k = k,
			.m = m,
			.p = p,
		पूर्ण;

		/* get mux details from mux clk काष्ठाure */
		अगर (factors->mux)
			factors_req.parent_index =
				(reg >> factors->mux->shअगरt) &
				factors->mux->mask;

		factors->recalc(&factors_req);

		वापस factors_req.rate;
	पूर्ण

	/* Calculate the rate */
	rate = (parent_rate * (n + config->n_start) * (k + 1) >> p) / (m + 1);

	वापस rate;
पूर्ण

अटल पूर्णांक clk_factors_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_factors *factors = to_clk_factors(hw);
	काष्ठा clk_hw *parent, *best_parent = शून्य;
	पूर्णांक i, num_parents;
	अचिन्हित दीर्घ parent_rate, best = 0, child_rate, best_child_rate = 0;

	/* find the parent that can help provide the fastest rate <= rate */
	num_parents = clk_hw_get_num_parents(hw);
	क्रम (i = 0; i < num_parents; i++) अणु
		काष्ठा factors_request factors_req = अणु
			.rate = req->rate,
			.parent_index = i,
		पूर्ण;
		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;
		अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
			parent_rate = clk_hw_round_rate(parent, req->rate);
		अन्यथा
			parent_rate = clk_hw_get_rate(parent);

		factors_req.parent_rate = parent_rate;
		factors->get_factors(&factors_req);
		child_rate = factors_req.rate;

		अगर (child_rate <= req->rate && child_rate > best_child_rate) अणु
			best_parent = parent;
			best = parent_rate;
			best_child_rate = child_rate;
		पूर्ण
	पूर्ण

	अगर (!best_parent)
		वापस -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best_child_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_factors_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा factors_request req = अणु
		.rate = rate,
		.parent_rate = parent_rate,
	पूर्ण;
	u32 reg;
	काष्ठा clk_factors *factors = to_clk_factors(hw);
	स्थिर काष्ठा clk_factors_config *config = factors->config;
	अचिन्हित दीर्घ flags = 0;

	factors->get_factors(&req);

	अगर (factors->lock)
		spin_lock_irqsave(factors->lock, flags);

	/* Fetch the रेजिस्टर value */
	reg = पढ़ोl(factors->reg);

	/* Set up the new factors - macros करो not करो anything अगर width is 0 */
	reg = FACTOR_SET(config->nshअगरt, config->nwidth, reg, req.n);
	reg = FACTOR_SET(config->kshअगरt, config->kwidth, reg, req.k);
	reg = FACTOR_SET(config->mshअगरt, config->mwidth, reg, req.m);
	reg = FACTOR_SET(config->pshअगरt, config->pwidth, reg, req.p);

	/* Apply them now */
	ग_लिखोl(reg, factors->reg);

	/* delay 500us so pll stabilizes */
	__delay((rate >> 20) * 500 / 2);

	अगर (factors->lock)
		spin_unlock_irqrestore(factors->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_factors_ops = अणु
	.determine_rate = clk_factors_determine_rate,
	.recalc_rate = clk_factors_recalc_rate,
	.set_rate = clk_factors_set_rate,
पूर्ण;

अटल काष्ठा clk *__sunxi_factors_रेजिस्टर(काष्ठा device_node *node,
					    स्थिर काष्ठा factors_data *data,
					    spinlock_t *lock, व्योम __iomem *reg,
					    अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_factors *factors;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_hw *gate_hw = शून्य;
	काष्ठा clk_hw *mux_hw = शून्य;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parents[FACTORS_MAX_PARENTS];
	पूर्णांक ret, i = 0;

	/* अगर we have a mux, we will have >1 parents */
	i = of_clk_parent_fill(node, parents, FACTORS_MAX_PARENTS);

	/*
	 * some factor घड़ीs, such as pll5 and pll6, may have multiple
	 * outमाला_दो, and have their name designated in factors_data
	 */
	अगर (data->name)
		clk_name = data->name;
	अन्यथा
		of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	factors = kzalloc(माप(काष्ठा clk_factors), GFP_KERNEL);
	अगर (!factors)
		जाओ err_factors;

	/* set up factors properties */
	factors->reg = reg;
	factors->config = data->table;
	factors->get_factors = data->getter;
	factors->recalc = data->recalc;
	factors->lock = lock;

	/* Add a gate अगर this factor घड़ी can be gated */
	अगर (data->enable) अणु
		gate = kzalloc(माप(काष्ठा clk_gate), GFP_KERNEL);
		अगर (!gate)
			जाओ err_gate;

		factors->gate = gate;

		/* set up gate properties */
		gate->reg = reg;
		gate->bit_idx = data->enable;
		gate->lock = factors->lock;
		gate_hw = &gate->hw;
	पूर्ण

	/* Add a mux अगर this factor घड़ी can be muxed */
	अगर (data->mux) अणु
		mux = kzalloc(माप(काष्ठा clk_mux), GFP_KERNEL);
		अगर (!mux)
			जाओ err_mux;

		factors->mux = mux;

		/* set up gate properties */
		mux->reg = reg;
		mux->shअगरt = data->mux;
		mux->mask = data->muxmask;
		mux->lock = factors->lock;
		mux_hw = &mux->hw;
	पूर्ण

	clk = clk_रेजिस्टर_composite(शून्य, clk_name,
			parents, i,
			mux_hw, &clk_mux_ops,
			&factors->hw, &clk_factors_ops,
			gate_hw, &clk_gate_ops, CLK_IS_CRITICAL);
	अगर (IS_ERR(clk))
		जाओ err_रेजिस्टर;

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret)
		जाओ err_provider;

	वापस clk;

err_provider:
	/* TODO: The composite घड़ी stuff will leak a bit here. */
	clk_unरेजिस्टर(clk);
err_रेजिस्टर:
	kमुक्त(mux);
err_mux:
	kमुक्त(gate);
err_gate:
	kमुक्त(factors);
err_factors:
	वापस शून्य;
पूर्ण

काष्ठा clk *sunxi_factors_रेजिस्टर(काष्ठा device_node *node,
				   स्थिर काष्ठा factors_data *data,
				   spinlock_t *lock,
				   व्योम __iomem *reg)
अणु
	वापस __sunxi_factors_रेजिस्टर(node, data, lock, reg, 0);
पूर्ण

काष्ठा clk *sunxi_factors_रेजिस्टर_critical(काष्ठा device_node *node,
					    स्थिर काष्ठा factors_data *data,
					    spinlock_t *lock,
					    व्योम __iomem *reg)
अणु
	वापस __sunxi_factors_रेजिस्टर(node, data, lock, reg, CLK_IS_CRITICAL);
पूर्ण

व्योम sunxi_factors_unरेजिस्टर(काष्ठा device_node *node, काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा clk_factors *factors;

	अगर (!hw)
		वापस;

	factors = to_clk_factors(hw);

	of_clk_del_provider(node);
	/* TODO: The composite घड़ी stuff will leak a bit here. */
	clk_unरेजिस्टर(clk);
	kमुक्त(factors->mux);
	kमुक्त(factors->gate);
	kमुक्त(factors);
पूर्ण
