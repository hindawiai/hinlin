<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * clkgen-mux.c: ST GEN-MUX Clock driver
 *
 * Copyright (C) 2014 STMicroelectronics (R&D) Limited
 *
 * Authors: Stephen Gallimore <stephen.gallimore@st.com>
 *	    Pankaj Dev <pankaj.dev@st.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश "clkgen.h"

अटल स्थिर अक्षर ** __init clkgen_mux_get_parents(काष्ठा device_node *np,
						       पूर्णांक *num_parents)
अणु
	स्थिर अक्षर **parents;
	अचिन्हित पूर्णांक nparents;

	nparents = of_clk_get_parent_count(np);
	अगर (WARN_ON(!nparents))
		वापस ERR_PTR(-EINVAL);

	parents = kसुस्मृति(nparents, माप(स्थिर अक्षर *), GFP_KERNEL);
	अगर (!parents)
		वापस ERR_PTR(-ENOMEM);

	*num_parents = of_clk_parent_fill(np, parents, nparents);
	वापस parents;
पूर्ण

काष्ठा clkgen_mux_data अणु
	u32 offset;
	u8 shअगरt;
	u8 width;
	spinlock_t *lock;
	अचिन्हित दीर्घ clk_flags;
	u8 mux_flags;
पूर्ण;

अटल काष्ठा clkgen_mux_data stih407_a9_mux_data = अणु
	.offset = 0x1a4,
	.shअगरt = 0,
	.width = 2,
	.lock = &clkgen_a9_lock,
पूर्ण;

अटल व्योम __init st_of_clkgen_mux_setup(काष्ठा device_node *np,
		काष्ठा clkgen_mux_data *data)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *reg;
	स्थिर अक्षर **parents;
	पूर्णांक num_parents = 0;

	reg = of_iomap(np, 0);
	अगर (!reg) अणु
		pr_err("%s: Failed to get base address\n", __func__);
		वापस;
	पूर्ण

	parents = clkgen_mux_get_parents(np, &num_parents);
	अगर (IS_ERR(parents)) अणु
		pr_err("%s: Failed to get parents (%ld)\n",
				__func__, PTR_ERR(parents));
		जाओ err_parents;
	पूर्ण

	clk = clk_रेजिस्टर_mux(शून्य, np->name, parents, num_parents,
				data->clk_flags | CLK_SET_RATE_PARENT,
				reg + data->offset,
				data->shअगरt, data->width, data->mux_flags,
				data->lock);
	अगर (IS_ERR(clk))
		जाओ err;

	pr_debug("%s: parent %s rate %u\n",
			__clk_get_name(clk),
			__clk_get_name(clk_get_parent(clk)),
			(अचिन्हित पूर्णांक)clk_get_rate(clk));

	kमुक्त(parents);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	वापस;

err:
	kमुक्त(parents);
err_parents:
	iounmap(reg);
पूर्ण

अटल व्योम __init st_of_clkgen_a9_mux_setup(काष्ठा device_node *np)
अणु
	st_of_clkgen_mux_setup(np, &stih407_a9_mux_data);
पूर्ण
CLK_OF_DECLARE(clkgen_a9mux, "st,stih407-clkgen-a9-mux",
		st_of_clkgen_a9_mux_setup);
