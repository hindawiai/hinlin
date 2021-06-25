<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

काष्ठा pistachio_clk_provider *
pistachio_clk_alloc_provider(काष्ठा device_node *node, अचिन्हित पूर्णांक num_clks)
अणु
	काष्ठा pistachio_clk_provider *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस p;

	p->clk_data.clks = kसुस्मृति(num_clks, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!p->clk_data.clks)
		जाओ मुक्त_provider;
	p->clk_data.clk_num = num_clks;
	p->node = node;
	p->base = of_iomap(node, 0);
	अगर (!p->base) अणु
		pr_err("Failed to map clock provider registers\n");
		जाओ मुक्त_clks;
	पूर्ण

	वापस p;

मुक्त_clks:
	kमुक्त(p->clk_data.clks);
मुक्त_provider:
	kमुक्त(p);
	वापस शून्य;
पूर्ण

व्योम pistachio_clk_रेजिस्टर_provider(काष्ठा pistachio_clk_provider *p)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < p->clk_data.clk_num; i++) अणु
		अगर (IS_ERR(p->clk_data.clks[i]))
			pr_warn("Failed to register clock %d: %ld\n", i,
				PTR_ERR(p->clk_data.clks[i]));
	पूर्ण

	of_clk_add_provider(p->node, of_clk_src_onecell_get, &p->clk_data);
पूर्ण

व्योम pistachio_clk_रेजिस्टर_gate(काष्ठा pistachio_clk_provider *p,
				 काष्ठा pistachio_gate *gate,
				 अचिन्हित पूर्णांक num)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		clk = clk_रेजिस्टर_gate(शून्य, gate[i].name, gate[i].parent,
					CLK_SET_RATE_PARENT,
					p->base + gate[i].reg, gate[i].shअगरt,
					0, शून्य);
		p->clk_data.clks[gate[i].id] = clk;
	पूर्ण
पूर्ण

व्योम pistachio_clk_रेजिस्टर_mux(काष्ठा pistachio_clk_provider *p,
				काष्ठा pistachio_mux *mux,
				अचिन्हित पूर्णांक num)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		clk = clk_रेजिस्टर_mux(शून्य, mux[i].name, mux[i].parents,
				       mux[i].num_parents,
				       CLK_SET_RATE_NO_REPARENT,
				       p->base + mux[i].reg, mux[i].shअगरt,
				       get_count_order(mux[i].num_parents),
				       0, शून्य);
		p->clk_data.clks[mux[i].id] = clk;
	पूर्ण
पूर्ण

व्योम pistachio_clk_रेजिस्टर_भाग(काष्ठा pistachio_clk_provider *p,
				काष्ठा pistachio_भाग *भाग,
				अचिन्हित पूर्णांक num)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		clk = clk_रेजिस्टर_भागider(शून्य, भाग[i].name, भाग[i].parent,
					   0, p->base + भाग[i].reg, 0,
					   भाग[i].width, भाग[i].भाग_flags,
					   शून्य);
		p->clk_data.clks[भाग[i].id] = clk;
	पूर्ण
पूर्ण

व्योम pistachio_clk_रेजिस्टर_fixed_factor(काष्ठा pistachio_clk_provider *p,
					 काष्ठा pistachio_fixed_factor *ff,
					 अचिन्हित पूर्णांक num)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		clk = clk_रेजिस्टर_fixed_factor(शून्य, ff[i].name, ff[i].parent,
						0, 1, ff[i].भाग);
		p->clk_data.clks[ff[i].id] = clk;
	पूर्ण
पूर्ण

व्योम pistachio_clk_क्रमce_enable(काष्ठा pistachio_clk_provider *p,
				अचिन्हित पूर्णांक *clk_ids, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा clk *clk = p->clk_data.clks[clk_ids[i]];

		अगर (IS_ERR(clk))
			जारी;

		err = clk_prepare_enable(clk);
		अगर (err)
			pr_err("Failed to enable clock %s: %d\n",
			       __clk_get_name(clk), err);
	पूर्ण
पूर्ण
