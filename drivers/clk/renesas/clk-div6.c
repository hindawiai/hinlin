<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7790 Common Clock Framework support
 *
 * Copyright (C) 2013  Renesas Solutions Corp.
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश "clk-div6.h"

#घोषणा CPG_DIV6_CKSTP		BIT(8)
#घोषणा CPG_DIV6_DIV(d)		((d) & 0x3f)
#घोषणा CPG_DIV6_DIV_MASK	0x3f

/**
 * काष्ठा भाग6_घड़ी - CPG 6 bit भागider घड़ी
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg: IO-remapped रेजिस्टर
 * @भाग: भागisor value (1-64)
 * @src_shअगरt: Shअगरt to access the रेजिस्टर bits to select the parent घड़ी
 * @src_width: Number of रेजिस्टर bits to select the parent घड़ी (may be 0)
 * @nb: Notअगरier block to save/restore घड़ी state क्रम प्रणाली resume
 * @parents: Array to map from valid parent घड़ीs indices to hardware indices
 */
काष्ठा भाग6_घड़ी अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक भाग;
	u32 src_shअगरt;
	u32 src_width;
	काष्ठा notअगरier_block nb;
	u8 parents[];
पूर्ण;

#घोषणा to_भाग6_घड़ी(_hw) container_of(_hw, काष्ठा भाग6_घड़ी, hw)

अटल पूर्णांक cpg_भाग6_घड़ी_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);
	u32 val;

	val = (पढ़ोl(घड़ी->reg) & ~(CPG_DIV6_DIV_MASK | CPG_DIV6_CKSTP))
	    | CPG_DIV6_DIV(घड़ी->भाग - 1);
	ग_लिखोl(val, घड़ी->reg);

	वापस 0;
पूर्ण

अटल व्योम cpg_भाग6_घड़ी_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);
	u32 val;

	val = पढ़ोl(घड़ी->reg);
	val |= CPG_DIV6_CKSTP;
	/*
	 * DIV6 घड़ीs require the भागisor field to be non-zero when stopping
	 * the घड़ी. However, some घड़ीs (e.g. ZB on sh73a0) fail to be
	 * re-enabled later अगर the भागisor field is changed when stopping the
	 * घड़ी
	 */
	अगर (!(val & CPG_DIV6_DIV_MASK))
		val |= CPG_DIV6_DIV_MASK;
	ग_लिखोl(val, घड़ी->reg);
पूर्ण

अटल पूर्णांक cpg_भाग6_घड़ी_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);

	वापस !(पढ़ोl(घड़ी->reg) & CPG_DIV6_CKSTP);
पूर्ण

अटल अचिन्हित दीर्घ cpg_भाग6_घड़ी_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);

	वापस parent_rate / घड़ी->भाग;
पूर्ण

अटल अचिन्हित पूर्णांक cpg_भाग6_घड़ी_calc_भाग(अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक भाग;

	अगर (!rate)
		rate = 1;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	वापस clamp_t(अचिन्हित पूर्णांक, भाग, 1, 64);
पूर्ण

अटल दीर्घ cpg_भाग6_घड़ी_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित पूर्णांक भाग = cpg_भाग6_घड़ी_calc_भाग(rate, *parent_rate);

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक cpg_भाग6_घड़ी_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);
	अचिन्हित पूर्णांक भाग = cpg_भाग6_घड़ी_calc_भाग(rate, parent_rate);
	u32 val;

	घड़ी->भाग = भाग;

	val = पढ़ोl(घड़ी->reg) & ~CPG_DIV6_DIV_MASK;
	/* Only program the new भागisor अगर the घड़ी isn't stopped. */
	अगर (!(val & CPG_DIV6_CKSTP))
		ग_लिखोl(val | CPG_DIV6_DIV(घड़ी->भाग - 1), घड़ी->reg);

	वापस 0;
पूर्ण

अटल u8 cpg_भाग6_घड़ी_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);
	अचिन्हित पूर्णांक i;
	u8 hw_index;

	अगर (घड़ी->src_width == 0)
		वापस 0;

	hw_index = (पढ़ोl(घड़ी->reg) >> घड़ी->src_shअगरt) &
		   (BIT(घड़ी->src_width) - 1);
	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		अगर (घड़ी->parents[i] == hw_index)
			वापस i;
	पूर्ण

	pr_err("%s: %s DIV6 clock set to invalid parent %u\n",
	       __func__, clk_hw_get_name(hw), hw_index);
	वापस 0;
पूर्ण

अटल पूर्णांक cpg_भाग6_घड़ी_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = to_भाग6_घड़ी(hw);
	u8 hw_index;
	u32 mask;

	अगर (index >= clk_hw_get_num_parents(hw))
		वापस -EINVAL;

	mask = ~((BIT(घड़ी->src_width) - 1) << घड़ी->src_shअगरt);
	hw_index = घड़ी->parents[index];

	ग_लिखोl((पढ़ोl(घड़ी->reg) & mask) | (hw_index << घड़ी->src_shअगरt),
	       घड़ी->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops cpg_भाग6_घड़ी_ops = अणु
	.enable = cpg_भाग6_घड़ी_enable,
	.disable = cpg_भाग6_घड़ी_disable,
	.is_enabled = cpg_भाग6_घड़ी_is_enabled,
	.get_parent = cpg_भाग6_घड़ी_get_parent,
	.set_parent = cpg_भाग6_घड़ी_set_parent,
	.recalc_rate = cpg_भाग6_घड़ी_recalc_rate,
	.round_rate = cpg_भाग6_घड़ी_round_rate,
	.set_rate = cpg_भाग6_घड़ी_set_rate,
पूर्ण;

अटल पूर्णांक cpg_भाग6_घड़ी_notअगरier_call(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा भाग6_घड़ी *घड़ी = container_of(nb, काष्ठा भाग6_घड़ी, nb);

	चयन (action) अणु
	हाल PM_EVENT_RESUME:
		/*
		 * TODO: This करोes not yet support DIV6 घड़ीs with multiple
		 * parents, as the parent selection bits are not restored.
		 * Fortunately so far such DIV6 घड़ीs are found only on
		 * R/SH-Mobile SoCs, जबतक the resume functionality is only
		 * needed on R-Car Gen3.
		 */
		अगर (__clk_get_enable_count(घड़ी->hw.clk))
			cpg_भाग6_घड़ी_enable(&घड़ी->hw);
		अन्यथा
			cpg_भाग6_घड़ी_disable(&घड़ी->hw);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * cpg_भाग6_रेजिस्टर - Register a DIV6 घड़ी
 * @name: Name of the DIV6 घड़ी
 * @num_parents: Number of parent घड़ीs of the DIV6 घड़ी (1, 4, or 8)
 * @parent_names: Array containing the names of the parent घड़ीs
 * @reg: Mapped रेजिस्टर used to control the DIV6 घड़ी
 * @notअगरiers: Optional notअगरier chain to save/restore state क्रम प्रणाली resume
 */
काष्ठा clk * __init cpg_भाग6_रेजिस्टर(स्थिर अक्षर *name,
				      अचिन्हित पूर्णांक num_parents,
				      स्थिर अक्षर **parent_names,
				      व्योम __iomem *reg,
				      काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	अचिन्हित पूर्णांक valid_parents;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा भाग6_घड़ी *घड़ी;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	घड़ी = kzalloc(काष्ठा_size(घड़ी, parents, num_parents), GFP_KERNEL);
	अगर (!घड़ी)
		वापस ERR_PTR(-ENOMEM);

	घड़ी->reg = reg;

	/*
	 * Read the भागisor. Disabling the घड़ी overग_लिखोs the भागisor, so we
	 * need to cache its value क्रम the enable operation.
	 */
	घड़ी->भाग = (पढ़ोl(घड़ी->reg) & CPG_DIV6_DIV_MASK) + 1;

	चयन (num_parents) अणु
	हाल 1:
		/* fixed parent घड़ी */
		घड़ी->src_shअगरt = घड़ी->src_width = 0;
		अवरोध;
	हाल 4:
		/* घड़ी with EXSRC bits 6-7 */
		घड़ी->src_shअगरt = 6;
		घड़ी->src_width = 2;
		अवरोध;
	हाल 8:
		/* VCLK with EXSRC bits 12-14 */
		घड़ी->src_shअगरt = 12;
		घड़ी->src_width = 3;
		अवरोध;
	शेष:
		pr_err("%s: invalid number of parents for DIV6 clock %s\n",
		       __func__, name);
		clk = ERR_PTR(-EINVAL);
		जाओ मुक्त_घड़ी;
	पूर्ण

	/* Filter out invalid parents */
	क्रम (i = 0, valid_parents = 0; i < num_parents; i++) अणु
		अगर (parent_names[i]) अणु
			parent_names[valid_parents] = parent_names[i];
			घड़ी->parents[valid_parents] = i;
			valid_parents++;
		पूर्ण
	पूर्ण

	/* Register the घड़ी. */
	init.name = name;
	init.ops = &cpg_भाग6_घड़ी_ops;
	init.parent_names = parent_names;
	init.num_parents = valid_parents;

	घड़ी->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &घड़ी->hw);
	अगर (IS_ERR(clk))
		जाओ मुक्त_घड़ी;

	अगर (notअगरiers) अणु
		घड़ी->nb.notअगरier_call = cpg_भाग6_घड़ी_notअगरier_call;
		raw_notअगरier_chain_रेजिस्टर(notअगरiers, &घड़ी->nb);
	पूर्ण

	वापस clk;

मुक्त_घड़ी:
	kमुक्त(घड़ी);
	वापस clk;
पूर्ण

अटल व्योम __init cpg_भाग6_घड़ी_init(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	स्थिर अक्षर *clk_name = np->name;
	व्योम __iomem *reg;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents < 1) अणु
		pr_err("%s: no parent found for %pOFn DIV6 clock\n",
		       __func__, np);
		वापस;
	पूर्ण

	parent_names = kदो_स्मृति_array(num_parents, माप(*parent_names),
				GFP_KERNEL);
	अगर (!parent_names)
		वापस;

	reg = of_iomap(np, 0);
	अगर (reg == शून्य) अणु
		pr_err("%s: failed to map %pOFn DIV6 clock register\n",
		       __func__, np);
		जाओ error;
	पूर्ण

	/* Parse the DT properties. */
	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	क्रम (i = 0; i < num_parents; i++)
		parent_names[i] = of_clk_get_parent_name(np, i);

	clk = cpg_भाग6_रेजिस्टर(clk_name, num_parents, parent_names, reg, शून्य);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to register %pOFn DIV6 clock (%ld)\n",
		       __func__, np, PTR_ERR(clk));
		जाओ error;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_simple_get, clk);

	kमुक्त(parent_names);
	वापस;

error:
	अगर (reg)
		iounmap(reg);
	kमुक्त(parent_names);
पूर्ण
CLK_OF_DECLARE(cpg_भाग6_clk, "renesas,cpg-div6-clock", cpg_भाग6_घड़ी_init);
