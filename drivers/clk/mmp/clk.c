<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "clk.h"

व्योम mmp_clk_init(काष्ठा device_node *np, काष्ठा mmp_clk_unit *unit,
		पूर्णांक nr_clks)
अणु
	काष्ठा clk **clk_table;

	clk_table = kसुस्मृति(nr_clks, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_table)
		वापस;

	unit->clk_table = clk_table;
	unit->nr_clks = nr_clks;
	unit->clk_data.clks = clk_table;
	unit->clk_data.clk_num = nr_clks;
	of_clk_add_provider(np, of_clk_src_onecell_get, &unit->clk_data);
पूर्ण

व्योम mmp_रेजिस्टर_fixed_rate_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_fixed_rate_clk *clks,
				पूर्णांक size)
अणु
	पूर्णांक i;
	काष्ठा clk *clk;

	क्रम (i = 0; i < size; i++) अणु
		clk = clk_रेजिस्टर_fixed_rate(शून्य, clks[i].name,
					clks[i].parent_name,
					clks[i].flags,
					clks[i].fixed_rate);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_रेजिस्टर_fixed_factor_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_fixed_factor_clk *clks,
				पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		clk = clk_रेजिस्टर_fixed_factor(शून्य, clks[i].name,
						clks[i].parent_name,
						clks[i].flags, clks[i].mult,
						clks[i].भाग);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_रेजिस्टर_general_gate_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_general_gate_clk *clks,
				व्योम __iomem *base, पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		clk = clk_रेजिस्टर_gate(शून्य, clks[i].name,
					clks[i].parent_name,
					clks[i].flags,
					base + clks[i].offset,
					clks[i].bit_idx,
					clks[i].gate_flags,
					clks[i].lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_रेजिस्टर_gate_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_gate_clk *clks,
			व्योम __iomem *base, पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		clk = mmp_clk_रेजिस्टर_gate(शून्य, clks[i].name,
					clks[i].parent_name,
					clks[i].flags,
					base + clks[i].offset,
					clks[i].mask,
					clks[i].val_enable,
					clks[i].val_disable,
					clks[i].gate_flags,
					clks[i].lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_रेजिस्टर_mux_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_mux_clk *clks,
			व्योम __iomem *base, पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		clk = clk_रेजिस्टर_mux(शून्य, clks[i].name,
					clks[i].parent_name,
					clks[i].num_parents,
					clks[i].flags,
					base + clks[i].offset,
					clks[i].shअगरt,
					clks[i].width,
					clks[i].mux_flags,
					clks[i].lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_रेजिस्टर_भाग_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_भाग_clk *clks,
			व्योम __iomem *base, पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		clk = clk_रेजिस्टर_भागider(शून्य, clks[i].name,
					clks[i].parent_name,
					clks[i].flags,
					base + clks[i].offset,
					clks[i].shअगरt,
					clks[i].width,
					clks[i].भाग_flags,
					clks[i].lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण

व्योम mmp_clk_add(काष्ठा mmp_clk_unit *unit, अचिन्हित पूर्णांक id,
			काष्ठा clk *clk)
अणु
	अगर (IS_ERR_OR_शून्य(clk)) अणु
		pr_err("CLK %d has invalid pointer %p\n", id, clk);
		वापस;
	पूर्ण
	अगर (id >= unit->nr_clks) अणु
		pr_err("CLK %d is invalid\n", id);
		वापस;
	पूर्ण

	unit->clk_table[id] = clk;
पूर्ण
