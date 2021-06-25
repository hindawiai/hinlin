<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * clk-flexgen.c
 *
 * Copyright (C) ST-Microelectronics SA 2013
 * Author:  Maxime Coquelin <maxime.coquelin@st.com> क्रम ST-Microelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

काष्ठा clkgen_data अणु
	अचिन्हित दीर्घ flags;
	bool mode;
पूर्ण;

काष्ठा flexgen अणु
	काष्ठा clk_hw hw;

	/* Crossbar */
	काष्ठा clk_mux mux;
	/* Pre-भागisor's gate */
	काष्ठा clk_gate pgate;
	/* Pre-भागisor */
	काष्ठा clk_भागider pभाग;
	/* Final भागisor's gate */
	काष्ठा clk_gate fgate;
	/* Final भागisor */
	काष्ठा clk_भागider fभाग;
	/* Asynchronous mode control */
	काष्ठा clk_gate sync;
	/* hw control flags */
	bool control_mode;
पूर्ण;

#घोषणा to_flexgen(_hw) container_of(_hw, काष्ठा flexgen, hw)
#घोषणा to_clk_gate(_hw) container_of(_hw, काष्ठा clk_gate, hw)

अटल पूर्णांक flexgen_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *pgate_hw = &flexgen->pgate.hw;
	काष्ठा clk_hw *fgate_hw = &flexgen->fgate.hw;

	__clk_hw_set_clk(pgate_hw, hw);
	__clk_hw_set_clk(fgate_hw, hw);

	clk_gate_ops.enable(pgate_hw);

	clk_gate_ops.enable(fgate_hw);

	pr_debug("%s: flexgen output enabled\n", clk_hw_get_name(hw));
	वापस 0;
पूर्ण

अटल व्योम flexgen_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *fgate_hw = &flexgen->fgate.hw;

	/* disable only the final gate */
	__clk_hw_set_clk(fgate_hw, hw);

	clk_gate_ops.disable(fgate_hw);

	pr_debug("%s: flexgen output disabled\n", clk_hw_get_name(hw));
पूर्ण

अटल पूर्णांक flexgen_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *fgate_hw = &flexgen->fgate.hw;

	__clk_hw_set_clk(fgate_hw, hw);

	अगर (!clk_gate_ops.is_enabled(fgate_hw))
		वापस 0;

	वापस 1;
पूर्ण

अटल u8 flexgen_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *mux_hw = &flexgen->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस clk_mux_ops.get_parent(mux_hw);
पूर्ण

अटल पूर्णांक flexgen_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *mux_hw = &flexgen->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस clk_mux_ops.set_parent(mux_hw, index);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
clk_best_भाग(अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate)
अणु
	वापस parent_rate / rate + ((rate > (2*(parent_rate % rate))) ? 0 : 1);
पूर्ण

अटल दीर्घ flexgen_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ भाग;

	/* Round भाग according to exact prate and wished rate */
	भाग = clk_best_भाग(*prate, rate);

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		*prate = rate * भाग;
		वापस rate;
	पूर्ण

	वापस *prate / भाग;
पूर्ण

अटल अचिन्हित दीर्घ flexgen_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *pभाग_hw = &flexgen->pभाग.hw;
	काष्ठा clk_hw *fभाग_hw = &flexgen->fभाग.hw;
	अचिन्हित दीर्घ mid_rate;

	__clk_hw_set_clk(pभाग_hw, hw);
	__clk_hw_set_clk(fभाग_hw, hw);

	mid_rate = clk_भागider_ops.recalc_rate(pभाग_hw, parent_rate);

	वापस clk_भागider_ops.recalc_rate(fभाग_hw, mid_rate);
पूर्ण

अटल पूर्णांक flexgen_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा flexgen *flexgen = to_flexgen(hw);
	काष्ठा clk_hw *pभाग_hw = &flexgen->pभाग.hw;
	काष्ठा clk_hw *fभाग_hw = &flexgen->fभाग.hw;
	काष्ठा clk_hw *sync_hw = &flexgen->sync.hw;
	काष्ठा clk_gate *config = to_clk_gate(sync_hw);
	अचिन्हित दीर्घ भाग = 0;
	पूर्णांक ret = 0;
	u32 reg;

	__clk_hw_set_clk(pभाग_hw, hw);
	__clk_hw_set_clk(fभाग_hw, hw);

	अगर (flexgen->control_mode) अणु
		reg = पढ़ोl(config->reg);
		reg &= ~BIT(config->bit_idx);
		ग_लिखोl(reg, config->reg);
	पूर्ण

	भाग = clk_best_भाग(parent_rate, rate);

	/*
	* pभाग is मुख्यly targeted क्रम low freq results, जबतक fभाग
	* should be used क्रम भाग <= 64. The other way round can
	* lead to 'duty cycle' issues.
	*/

	अगर (भाग <= 64) अणु
		clk_भागider_ops.set_rate(pभाग_hw, parent_rate, parent_rate);
		ret = clk_भागider_ops.set_rate(fभाग_hw, rate, rate * भाग);
	पूर्ण अन्यथा अणु
		clk_भागider_ops.set_rate(fभाग_hw, parent_rate, parent_rate);
		ret = clk_भागider_ops.set_rate(pभाग_hw, rate, rate * भाग);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops flexgen_ops = अणु
	.enable = flexgen_enable,
	.disable = flexgen_disable,
	.is_enabled = flexgen_is_enabled,
	.get_parent = flexgen_get_parent,
	.set_parent = flexgen_set_parent,
	.round_rate = flexgen_round_rate,
	.recalc_rate = flexgen_recalc_rate,
	.set_rate = flexgen_set_rate,
पूर्ण;

अटल काष्ठा clk *clk_रेजिस्टर_flexgen(स्थिर अक्षर *name,
				स्थिर अक्षर **parent_names, u8 num_parents,
				व्योम __iomem *reg, spinlock_t *lock, u32 idx,
				अचिन्हित दीर्घ flexgen_flags, bool mode) अणु
	काष्ठा flexgen *fgxbar;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	u32  xbar_shअगरt;
	व्योम __iomem *xbar_reg, *fभाग_reg;

	fgxbar = kzalloc(माप(काष्ठा flexgen), GFP_KERNEL);
	अगर (!fgxbar)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &flexgen_ops;
	init.flags = CLK_GET_RATE_NOCACHE | flexgen_flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	xbar_reg = reg + 0x18 + (idx & ~0x3);
	xbar_shअगरt = (idx % 4) * 0x8;
	fभाग_reg = reg + 0x164 + idx * 4;

	/* Crossbar element config */
	fgxbar->mux.lock = lock;
	fgxbar->mux.mask = BIT(6) - 1;
	fgxbar->mux.reg = xbar_reg;
	fgxbar->mux.shअगरt = xbar_shअगरt;
	fgxbar->mux.table = शून्य;


	/* Pre-भागider's gate config (in xbar रेजिस्टर)*/
	fgxbar->pgate.lock = lock;
	fgxbar->pgate.reg = xbar_reg;
	fgxbar->pgate.bit_idx = xbar_shअगरt + 6;

	/* Pre-भागider config */
	fgxbar->pभाग.lock = lock;
	fgxbar->pभाग.reg = reg + 0x58 + idx * 4;
	fgxbar->pभाग.width = 10;

	/* Final भागider's gate config */
	fgxbar->fgate.lock = lock;
	fgxbar->fgate.reg = fभाग_reg;
	fgxbar->fgate.bit_idx = 6;

	/* Final भागider config */
	fgxbar->fभाग.lock = lock;
	fgxbar->fभाग.reg = fभाग_reg;
	fgxbar->fभाग.width = 6;

	/* Final भागider sync config */
	fgxbar->sync.lock = lock;
	fgxbar->sync.reg = fभाग_reg;
	fgxbar->sync.bit_idx = 7;

	fgxbar->control_mode = mode;

	fgxbar->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &fgxbar->hw);
	अगर (IS_ERR(clk))
		kमुक्त(fgxbar);
	अन्यथा
		pr_debug("%s: parent %s rate %u\n",
			__clk_get_name(clk),
			__clk_get_name(clk_get_parent(clk)),
			(अचिन्हित पूर्णांक)clk_get_rate(clk));
	वापस clk;
पूर्ण

अटल स्थिर अक्षर ** __init flexgen_get_parents(काष्ठा device_node *np,
						       पूर्णांक *num_parents)
अणु
	स्थिर अक्षर **parents;
	अचिन्हित पूर्णांक nparents;

	nparents = of_clk_get_parent_count(np);
	अगर (WARN_ON(!nparents))
		वापस शून्य;

	parents = kसुस्मृति(nparents, माप(स्थिर अक्षर *), GFP_KERNEL);
	अगर (!parents)
		वापस शून्य;

	*num_parents = of_clk_parent_fill(np, parents, nparents);

	वापस parents;
पूर्ण

अटल स्थिर काष्ठा clkgen_data clkgen_audio = अणु
	.flags = CLK_SET_RATE_PARENT,
पूर्ण;

अटल स्थिर काष्ठा clkgen_data clkgen_video = अणु
	.flags = CLK_SET_RATE_PARENT,
	.mode = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id flexgen_of_match[] = अणु
	अणु
		.compatible = "st,flexgen-audio",
		.data = &clkgen_audio,
	पूर्ण,
	अणु
		.compatible = "st,flexgen-video",
		.data = &clkgen_video,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम __init st_of_flexgen_setup(काष्ठा device_node *np)
अणु
	काष्ठा device_node *pnode;
	व्योम __iomem *reg;
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर **parents;
	पूर्णांक num_parents, i;
	spinlock_t *rlock = शून्य;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा clkgen_data *data = शून्य;
	अचिन्हित दीर्घ flex_flags = 0;
	पूर्णांक ret;
	bool clk_mode = 0;

	pnode = of_get_parent(np);
	अगर (!pnode)
		वापस;

	reg = of_iomap(pnode, 0);
	of_node_put(pnode);
	अगर (!reg)
		वापस;

	parents = flexgen_get_parents(np, &num_parents);
	अगर (!parents) अणु
		iounmap(reg);
		वापस;
	पूर्ण

	match = of_match_node(flexgen_of_match, np);
	अगर (match) अणु
		data = (काष्ठा clkgen_data *)match->data;
		flex_flags = data->flags;
		clk_mode = data->mode;
	पूर्ण

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ err;

	ret = of_property_count_strings(np, "clock-output-names");
	अगर (ret <= 0) अणु
		pr_err("%s: Failed to get number of output clocks (%d)",
				__func__, clk_data->clk_num);
		जाओ err;
	पूर्ण
	clk_data->clk_num = ret;

	clk_data->clks = kसुस्मृति(clk_data->clk_num, माप(काष्ठा clk *),
			GFP_KERNEL);
	अगर (!clk_data->clks)
		जाओ err;

	rlock = kzalloc(माप(spinlock_t), GFP_KERNEL);
	अगर (!rlock)
		जाओ err;

	spin_lock_init(rlock);

	क्रम (i = 0; i < clk_data->clk_num; i++) अणु
		काष्ठा clk *clk;
		स्थिर अक्षर *clk_name;

		अगर (of_property_पढ़ो_string_index(np, "clock-output-names",
						  i, &clk_name)) अणु
			अवरोध;
		पूर्ण

		flex_flags &= ~CLK_IS_CRITICAL;
		of_clk_detect_critical(np, i, &flex_flags);

		/*
		 * If we पढ़ो an empty घड़ी name then the output is unused
		 */
		अगर (*clk_name == '\0')
			जारी;

		clk = clk_रेजिस्टर_flexgen(clk_name, parents, num_parents,
					   reg, rlock, i, flex_flags, clk_mode);

		अगर (IS_ERR(clk))
			जाओ err;

		clk_data->clks[i] = clk;
	पूर्ण

	kमुक्त(parents);
	of_clk_add_provider(np, of_clk_src_onecell_get, clk_data);

	वापस;

err:
	iounmap(reg);
	अगर (clk_data)
		kमुक्त(clk_data->clks);
	kमुक्त(clk_data);
	kमुक्त(parents);
	kमुक्त(rlock);
पूर्ण
CLK_OF_DECLARE(flexgen, "st,flexgen", st_of_flexgen_setup);
