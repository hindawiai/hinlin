<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश "clk.h"

अटल अचिन्हित दीर्घ clk_sync_source_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_sync_source *sync = to_clk_sync_source(hw);

	वापस sync->rate;
पूर्ण

अटल दीर्घ clk_sync_source_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_sync_source *sync = to_clk_sync_source(hw);

	अगर (rate > sync->max_rate)
		वापस -EINVAL;
	अन्यथा
		वापस rate;
पूर्ण

अटल पूर्णांक clk_sync_source_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_sync_source *sync = to_clk_sync_source(hw);

	sync->rate = rate;
	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_sync_source_ops = अणु
	.round_rate = clk_sync_source_round_rate,
	.set_rate = clk_sync_source_set_rate,
	.recalc_rate = clk_sync_source_recalc_rate,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_sync_source(स्थिर अक्षर *name,
					   अचिन्हित दीर्घ max_rate)
अणु
	काष्ठा tegra_clk_sync_source *sync;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	sync = kzalloc(माप(*sync), GFP_KERNEL);
	अगर (!sync) अणु
		pr_err("%s: could not allocate sync source clk\n", __func__);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	sync->max_rate = max_rate;

	init.ops = &tegra_clk_sync_source_ops;
	init.name = name;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	sync->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &sync->hw);
	अगर (IS_ERR(clk))
		kमुक्त(sync);

	वापस clk;
पूर्ण
