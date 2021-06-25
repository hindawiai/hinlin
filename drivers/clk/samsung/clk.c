<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * This file includes utility functions to रेजिस्टर घड़ीs to common
 * घड़ी framework क्रम Samsung platक्रमms.
*/

#समावेश <linux/slab.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>

#समावेश "clk.h"

अटल LIST_HEAD(घड़ी_reg_cache_list);

व्योम samsung_clk_save(व्योम __iomem *base,
				    काष्ठा samsung_clk_reg_dump *rd,
				    अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd)
		rd->value = पढ़ोl(base + rd->offset);
पूर्ण

व्योम samsung_clk_restore(व्योम __iomem *base,
				      स्थिर काष्ठा samsung_clk_reg_dump *rd,
				      अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd)
		ग_लिखोl(rd->value, base + rd->offset);
पूर्ण

काष्ठा samsung_clk_reg_dump *samsung_clk_alloc_reg_dump(
						स्थिर अचिन्हित दीर्घ *rdump,
						अचिन्हित दीर्घ nr_rdump)
अणु
	काष्ठा samsung_clk_reg_dump *rd;
	अचिन्हित पूर्णांक i;

	rd = kसुस्मृति(nr_rdump, माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस शून्य;

	क्रम (i = 0; i < nr_rdump; ++i)
		rd[i].offset = rdump[i];

	वापस rd;
पूर्ण

/* setup the essentials required to support घड़ी lookup using ccf */
काष्ठा samsung_clk_provider *__init samsung_clk_init(काष्ठा device_node *np,
			व्योम __iomem *base, अचिन्हित दीर्घ nr_clks)
अणु
	काष्ठा samsung_clk_provider *ctx;
	पूर्णांक i;

	ctx = kzalloc(काष्ठा_size(ctx, clk_data.hws, nr_clks), GFP_KERNEL);
	अगर (!ctx)
		panic("could not allocate clock provider context.\n");

	क्रम (i = 0; i < nr_clks; ++i)
		ctx->clk_data.hws[i] = ERR_PTR(-ENOENT);

	ctx->reg_base = base;
	ctx->clk_data.num = nr_clks;
	spin_lock_init(&ctx->lock);

	वापस ctx;
पूर्ण

व्योम __init samsung_clk_of_add_provider(काष्ठा device_node *np,
				काष्ठा samsung_clk_provider *ctx)
अणु
	अगर (np) अणु
		अगर (of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
					&ctx->clk_data))
			panic("could not register clk provider\n");
	पूर्ण
पूर्ण

/* add a घड़ी instance to the घड़ी lookup table used क्रम dt based lookup */
व्योम samsung_clk_add_lookup(काष्ठा samsung_clk_provider *ctx,
			    काष्ठा clk_hw *clk_hw, अचिन्हित पूर्णांक id)
अणु
	अगर (id)
		ctx->clk_data.hws[id] = clk_hw;
पूर्ण

/* रेजिस्टर a list of aliases */
व्योम __init samsung_clk_रेजिस्टर_alias(काष्ठा samsung_clk_provider *ctx,
				स्थिर काष्ठा samsung_घड़ी_alias *list,
				अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx, ret;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		अगर (!list->id) अणु
			pr_err("%s: clock id missing for index %d\n", __func__,
				idx);
			जारी;
		पूर्ण

		clk_hw = ctx->clk_data.hws[list->id];
		अगर (!clk_hw) अणु
			pr_err("%s: failed to find clock %d\n", __func__,
				list->id);
			जारी;
		पूर्ण

		ret = clk_hw_रेजिस्टर_clkdev(clk_hw, list->alias,
					     list->dev_name);
		अगर (ret)
			pr_err("%s: failed to register lookup %s\n",
					__func__, list->alias);
	पूर्ण
पूर्ण

/* रेजिस्टर a list of fixed घड़ीs */
व्योम __init samsung_clk_रेजिस्टर_fixed_rate(काष्ठा samsung_clk_provider *ctx,
		स्थिर काष्ठा samsung_fixed_rate_घड़ी *list,
		अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx, ret;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		clk_hw = clk_hw_रेजिस्टर_fixed_rate(ctx->dev, list->name,
			list->parent_name, list->flags, list->fixed_rate);
		अगर (IS_ERR(clk_hw)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		samsung_clk_add_lookup(ctx, clk_hw, list->id);

		/*
		 * Unconditionally add a घड़ी lookup क्रम the fixed rate घड़ीs.
		 * There are not many of these on any of Samsung platक्रमms.
		 */
		ret = clk_hw_रेजिस्टर_clkdev(clk_hw, list->name, शून्य);
		अगर (ret)
			pr_err("%s: failed to register clock lookup for %s",
				__func__, list->name);
	पूर्ण
पूर्ण

/* रेजिस्टर a list of fixed factor घड़ीs */
व्योम __init samsung_clk_रेजिस्टर_fixed_factor(काष्ठा samsung_clk_provider *ctx,
		स्थिर काष्ठा samsung_fixed_factor_घड़ी *list, अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		clk_hw = clk_hw_रेजिस्टर_fixed_factor(ctx->dev, list->name,
			list->parent_name, list->flags, list->mult, list->भाग);
		अगर (IS_ERR(clk_hw)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		samsung_clk_add_lookup(ctx, clk_hw, list->id);
	पूर्ण
पूर्ण

/* रेजिस्टर a list of mux घड़ीs */
व्योम __init samsung_clk_रेजिस्टर_mux(काष्ठा samsung_clk_provider *ctx,
				स्थिर काष्ठा samsung_mux_घड़ी *list,
				अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		clk_hw = clk_hw_रेजिस्टर_mux(ctx->dev, list->name,
			list->parent_names, list->num_parents, list->flags,
			ctx->reg_base + list->offset,
			list->shअगरt, list->width, list->mux_flags, &ctx->lock);
		अगर (IS_ERR(clk_hw)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		samsung_clk_add_lookup(ctx, clk_hw, list->id);
	पूर्ण
पूर्ण

/* रेजिस्टर a list of भाग घड़ीs */
व्योम __init samsung_clk_रेजिस्टर_भाग(काष्ठा samsung_clk_provider *ctx,
				स्थिर काष्ठा samsung_भाग_घड़ी *list,
				अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		अगर (list->table)
			clk_hw = clk_hw_रेजिस्टर_भागider_table(ctx->dev,
				list->name, list->parent_name, list->flags,
				ctx->reg_base + list->offset,
				list->shअगरt, list->width, list->भाग_flags,
				list->table, &ctx->lock);
		अन्यथा
			clk_hw = clk_hw_रेजिस्टर_भागider(ctx->dev, list->name,
				list->parent_name, list->flags,
				ctx->reg_base + list->offset, list->shअगरt,
				list->width, list->भाग_flags, &ctx->lock);
		अगर (IS_ERR(clk_hw)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		samsung_clk_add_lookup(ctx, clk_hw, list->id);
	पूर्ण
पूर्ण

/* रेजिस्टर a list of gate घड़ीs */
व्योम __init samsung_clk_रेजिस्टर_gate(काष्ठा samsung_clk_provider *ctx,
				स्थिर काष्ठा samsung_gate_घड़ी *list,
				अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *clk_hw;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		clk_hw = clk_hw_रेजिस्टर_gate(ctx->dev, list->name, list->parent_name,
				list->flags, ctx->reg_base + list->offset,
				list->bit_idx, list->gate_flags, &ctx->lock);
		अगर (IS_ERR(clk_hw)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		samsung_clk_add_lookup(ctx, clk_hw, list->id);
	पूर्ण
पूर्ण

/*
 * obtain the घड़ी speed of all बाह्यal fixed घड़ी sources from device
 * tree and रेजिस्टर it
 */
व्योम __init samsung_clk_of_रेजिस्टर_fixed_ext(काष्ठा samsung_clk_provider *ctx,
			काष्ठा samsung_fixed_rate_घड़ी *fixed_rate_clk,
			अचिन्हित पूर्णांक nr_fixed_rate_clk,
			स्थिर काष्ठा of_device_id *clk_matches)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *clk_np;
	u32 freq;

	क्रम_each_matching_node_and_match(clk_np, clk_matches, &match) अणु
		अगर (of_property_पढ़ो_u32(clk_np, "clock-frequency", &freq))
			जारी;
		fixed_rate_clk[(अचिन्हित दीर्घ)match->data].fixed_rate = freq;
	पूर्ण
	samsung_clk_रेजिस्टर_fixed_rate(ctx, fixed_rate_clk, nr_fixed_rate_clk);
पूर्ण

/* utility function to get the rate of a specअगरied घड़ी */
अचिन्हित दीर्घ _get_rate(स्थिर अक्षर *clk_name)
अणु
	काष्ठा clk *clk;

	clk = __clk_lookup(clk_name);
	अगर (!clk) अणु
		pr_err("%s: could not find clock %s\n", __func__, clk_name);
		वापस 0;
	पूर्ण

	वापस clk_get_rate(clk);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक samsung_clk_suspend(व्योम)
अणु
	काष्ठा samsung_घड़ी_reg_cache *reg_cache;

	list_क्रम_each_entry(reg_cache, &घड़ी_reg_cache_list, node) अणु
		samsung_clk_save(reg_cache->reg_base, reg_cache->rdump,
				reg_cache->rd_num);
		samsung_clk_restore(reg_cache->reg_base, reg_cache->rsuspend,
				reg_cache->rsuspend_num);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम samsung_clk_resume(व्योम)
अणु
	काष्ठा samsung_घड़ी_reg_cache *reg_cache;

	list_क्रम_each_entry(reg_cache, &घड़ी_reg_cache_list, node)
		samsung_clk_restore(reg_cache->reg_base, reg_cache->rdump,
				reg_cache->rd_num);
पूर्ण

अटल काष्ठा syscore_ops samsung_clk_syscore_ops = अणु
	.suspend = samsung_clk_suspend,
	.resume = samsung_clk_resume,
पूर्ण;

व्योम samsung_clk_extended_sleep_init(व्योम __iomem *reg_base,
			स्थिर अचिन्हित दीर्घ *rdump,
			अचिन्हित दीर्घ nr_rdump,
			स्थिर काष्ठा samsung_clk_reg_dump *rsuspend,
			अचिन्हित दीर्घ nr_rsuspend)
अणु
	काष्ठा samsung_घड़ी_reg_cache *reg_cache;

	reg_cache = kzalloc(माप(काष्ठा samsung_घड़ी_reg_cache),
			GFP_KERNEL);
	अगर (!reg_cache)
		panic("could not allocate register reg_cache.\n");
	reg_cache->rdump = samsung_clk_alloc_reg_dump(rdump, nr_rdump);

	अगर (!reg_cache->rdump)
		panic("could not allocate register dump storage.\n");

	अगर (list_empty(&घड़ी_reg_cache_list))
		रेजिस्टर_syscore_ops(&samsung_clk_syscore_ops);

	reg_cache->reg_base = reg_base;
	reg_cache->rd_num = nr_rdump;
	reg_cache->rsuspend = rsuspend;
	reg_cache->rsuspend_num = nr_rsuspend;
	list_add_tail(&reg_cache->node, &घड़ी_reg_cache_list);
पूर्ण
#पूर्ण_अगर

/*
 * Common function which रेजिस्टरs plls, muxes, भागiders and gates
 * क्रम each CMU. It also add CMU रेजिस्टर list to रेजिस्टर cache.
 */
काष्ठा samsung_clk_provider * __init samsung_cmu_रेजिस्टर_one(
			काष्ठा device_node *np,
			स्थिर काष्ठा samsung_cmu_info *cmu)
अणु
	व्योम __iomem *reg_base;
	काष्ठा samsung_clk_provider *ctx;

	reg_base = of_iomap(np, 0);
	अगर (!reg_base) अणु
		panic("%s: failed to map registers\n", __func__);
		वापस शून्य;
	पूर्ण

	ctx = samsung_clk_init(np, reg_base, cmu->nr_clk_ids);

	अगर (cmu->pll_clks)
		samsung_clk_रेजिस्टर_pll(ctx, cmu->pll_clks, cmu->nr_pll_clks,
			reg_base);
	अगर (cmu->mux_clks)
		samsung_clk_रेजिस्टर_mux(ctx, cmu->mux_clks,
			cmu->nr_mux_clks);
	अगर (cmu->भाग_clks)
		samsung_clk_रेजिस्टर_भाग(ctx, cmu->भाग_clks, cmu->nr_भाग_clks);
	अगर (cmu->gate_clks)
		samsung_clk_रेजिस्टर_gate(ctx, cmu->gate_clks,
			cmu->nr_gate_clks);
	अगर (cmu->fixed_clks)
		samsung_clk_रेजिस्टर_fixed_rate(ctx, cmu->fixed_clks,
			cmu->nr_fixed_clks);
	अगर (cmu->fixed_factor_clks)
		samsung_clk_रेजिस्टर_fixed_factor(ctx, cmu->fixed_factor_clks,
			cmu->nr_fixed_factor_clks);
	अगर (cmu->clk_regs)
		samsung_clk_extended_sleep_init(reg_base,
			cmu->clk_regs, cmu->nr_clk_regs,
			cmu->suspend_regs, cmu->nr_suspend_regs);

	samsung_clk_of_add_provider(np, ctx);

	वापस ctx;
पूर्ण
