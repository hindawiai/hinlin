<शैली गुरु>
/*
 * SuperH घड़ी framework
 *
 *  Copyright (C) 2005 - 2010  Paul Mundt
 *
 * This घड़ी framework is derived from the OMAP version by:
 *
 *	Copyright (C) 2004 - 2008 Nokia Corporation
 *	Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *
 *  Modअगरied क्रम omap shared घड़ी framework by Tony Lindgren <tony@atomide.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "clock: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/clk.h>
#समावेश <linux/sh_clk.h>

अटल LIST_HEAD(घड़ी_list);
अटल DEFINE_SPINLOCK(घड़ी_lock);
अटल DEFINE_MUTEX(घड़ी_list_sem);

/* घड़ी disable operations are not passed on to hardware during boot */
अटल पूर्णांक allow_disable;

व्योम clk_rate_table_build(काष्ठा clk *clk,
			  काष्ठा cpufreq_frequency_table *freq_table,
			  पूर्णांक nr_freqs,
			  काष्ठा clk_भाग_mult_table *src_table,
			  अचिन्हित दीर्घ *biपंचांगap)
अणु
	अचिन्हित दीर्घ mult, भाग;
	अचिन्हित दीर्घ freq;
	पूर्णांक i;

	clk->nr_freqs = nr_freqs;

	क्रम (i = 0; i < nr_freqs; i++) अणु
		भाग = 1;
		mult = 1;

		अगर (src_table->भागisors && i < src_table->nr_भागisors)
			भाग = src_table->भागisors[i];

		अगर (src_table->multipliers && i < src_table->nr_multipliers)
			mult = src_table->multipliers[i];

		अगर (!भाग || !mult || (biपंचांगap && !test_bit(i, biपंचांगap)))
			freq = CPUFREQ_ENTRY_INVALID;
		अन्यथा
			freq = clk->parent->rate * mult / भाग;

		freq_table[i].driver_data = i;
		freq_table[i].frequency = freq;
	पूर्ण

	/* Termination entry */
	freq_table[i].driver_data = i;
	freq_table[i].frequency = CPUFREQ_TABLE_END;
पूर्ण

काष्ठा clk_rate_round_data;

काष्ठा clk_rate_round_data अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक min, max;
	दीर्घ (*func)(अचिन्हित पूर्णांक, काष्ठा clk_rate_round_data *);
	व्योम *arg;
पूर्ण;

#घोषणा क्रम_each_frequency(pos, r, freq)			\
	क्रम (pos = r->min, freq = r->func(pos, r);		\
	     pos <= r->max; pos++, freq = r->func(pos, r))	\
		अगर (unlikely(freq == 0))			\
			;					\
		अन्यथा

अटल दीर्घ clk_rate_round_helper(काष्ठा clk_rate_round_data *rounder)
अणु
	अचिन्हित दीर्घ rate_error, rate_error_prev = ~0UL;
	अचिन्हित दीर्घ highest, lowest, freq;
	दीर्घ rate_best_fit = -ENOENT;
	पूर्णांक i;

	highest = 0;
	lowest = ~0UL;

	क्रम_each_frequency(i, rounder, freq) अणु
		अगर (freq > highest)
			highest = freq;
		अगर (freq < lowest)
			lowest = freq;

		rate_error = असल(freq - rounder->rate);
		अगर (rate_error < rate_error_prev) अणु
			rate_best_fit = freq;
			rate_error_prev = rate_error;
		पूर्ण

		अगर (rate_error == 0)
			अवरोध;
	पूर्ण

	अगर (rounder->rate >= highest)
		rate_best_fit = highest;
	अगर (rounder->rate <= lowest)
		rate_best_fit = lowest;

	वापस rate_best_fit;
पूर्ण

अटल दीर्घ clk_rate_table_iter(अचिन्हित पूर्णांक pos,
				काष्ठा clk_rate_round_data *rounder)
अणु
	काष्ठा cpufreq_frequency_table *freq_table = rounder->arg;
	अचिन्हित दीर्घ freq = freq_table[pos].frequency;

	अगर (freq == CPUFREQ_ENTRY_INVALID)
		freq = 0;

	वापस freq;
पूर्ण

दीर्घ clk_rate_table_round(काष्ठा clk *clk,
			  काष्ठा cpufreq_frequency_table *freq_table,
			  अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_rate_round_data table_round = अणु
		.min	= 0,
		.max	= clk->nr_freqs - 1,
		.func	= clk_rate_table_iter,
		.arg	= freq_table,
		.rate	= rate,
	पूर्ण;

	अगर (clk->nr_freqs < 1)
		वापस -ENOSYS;

	वापस clk_rate_round_helper(&table_round);
पूर्ण

अटल दीर्घ clk_rate_भाग_range_iter(अचिन्हित पूर्णांक pos,
				    काष्ठा clk_rate_round_data *rounder)
अणु
	वापस clk_get_rate(rounder->arg) / pos;
पूर्ण

दीर्घ clk_rate_भाग_range_round(काष्ठा clk *clk, अचिन्हित पूर्णांक भाग_min,
			      अचिन्हित पूर्णांक भाग_max, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_rate_round_data भाग_range_round = अणु
		.min	= भाग_min,
		.max	= भाग_max,
		.func	= clk_rate_भाग_range_iter,
		.arg	= clk_get_parent(clk),
		.rate	= rate,
	पूर्ण;

	वापस clk_rate_round_helper(&भाग_range_round);
पूर्ण

अटल दीर्घ clk_rate_mult_range_iter(अचिन्हित पूर्णांक pos,
				      काष्ठा clk_rate_round_data *rounder)
अणु
	वापस clk_get_rate(rounder->arg) * pos;
पूर्ण

दीर्घ clk_rate_mult_range_round(काष्ठा clk *clk, अचिन्हित पूर्णांक mult_min,
			       अचिन्हित पूर्णांक mult_max, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_rate_round_data mult_range_round = अणु
		.min	= mult_min,
		.max	= mult_max,
		.func	= clk_rate_mult_range_iter,
		.arg	= clk_get_parent(clk),
		.rate	= rate,
	पूर्ण;

	वापस clk_rate_round_helper(&mult_range_round);
पूर्ण

पूर्णांक clk_rate_table_find(काष्ठा clk *clk,
			काष्ठा cpufreq_frequency_table *freq_table,
			अचिन्हित दीर्घ rate)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	पूर्णांक idx;

	cpufreq_क्रम_each_valid_entry_idx(pos, freq_table, idx)
		अगर (pos->frequency == rate)
			वापस idx;

	वापस -ENOENT;
पूर्ण

/* Used क्रम घड़ीs that always have same value as the parent घड़ी */
अचिन्हित दीर्घ followparent_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent ? clk->parent->rate : 0;
पूर्ण

पूर्णांक clk_reparent(काष्ठा clk *child, काष्ठा clk *parent)
अणु
	list_del_init(&child->sibling);
	अगर (parent)
		list_add(&child->sibling, &parent->children);
	child->parent = parent;

	वापस 0;
पूर्ण

/* Propagate rate to children */
व्योम propagate_rate(काष्ठा clk *tclk)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &tclk->children, sibling) अणु
		अगर (clkp->ops && clkp->ops->recalc)
			clkp->rate = clkp->ops->recalc(clkp);

		propagate_rate(clkp);
	पूर्ण
पूर्ण

अटल व्योम __clk_disable(काष्ठा clk *clk)
अणु
	अगर (WARN(!clk->usecount, "Trying to disable clock %p with 0 usecount\n",
		 clk))
		वापस;

	अगर (!(--clk->usecount)) अणु
		अगर (likely(allow_disable && clk->ops && clk->ops->disable))
			clk->ops->disable(clk);
		अगर (likely(clk->parent))
			__clk_disable(clk->parent);
	पूर्ण
पूर्ण

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस;

	spin_lock_irqsave(&घड़ी_lock, flags);
	__clk_disable(clk);
	spin_unlock_irqrestore(&घड़ी_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(clk_disable);

अटल पूर्णांक __clk_enable(काष्ठा clk *clk)
अणु
	पूर्णांक ret = 0;

	अगर (clk->usecount++ == 0) अणु
		अगर (clk->parent) अणु
			ret = __clk_enable(clk->parent);
			अगर (unlikely(ret))
				जाओ err;
		पूर्ण

		अगर (clk->ops && clk->ops->enable) अणु
			ret = clk->ops->enable(clk);
			अगर (ret) अणु
				अगर (clk->parent)
					__clk_disable(clk->parent);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
err:
	clk->usecount--;
	वापस ret;
पूर्ण

पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!clk)
		वापस -EINVAL;

	spin_lock_irqsave(&घड़ी_lock, flags);
	ret = __clk_enable(clk);
	spin_unlock_irqrestore(&घड़ी_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_enable);

अटल LIST_HEAD(root_clks);

/**
 * recalculate_root_घड़ीs - recalculate and propagate all root घड़ीs
 *
 * Recalculates all root घड़ीs (घड़ीs with no parent), which अगर the
 * घड़ी's .recalc is set correctly, should also propagate their rates.
 * Called at init.
 */
व्योम recalculate_root_घड़ीs(व्योम)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &root_clks, sibling) अणु
		अगर (clkp->ops && clkp->ops->recalc)
			clkp->rate = clkp->ops->recalc(clkp);
		propagate_rate(clkp);
	पूर्ण
पूर्ण

अटल काष्ठा clk_mapping dummy_mapping;

अटल काष्ठा clk *lookup_root_घड़ी(काष्ठा clk *clk)
अणु
	जबतक (clk->parent)
		clk = clk->parent;

	वापस clk;
पूर्ण

अटल पूर्णांक clk_establish_mapping(काष्ठा clk *clk)
अणु
	काष्ठा clk_mapping *mapping = clk->mapping;

	/*
	 * Propagate mappings.
	 */
	अगर (!mapping) अणु
		काष्ठा clk *clkp;

		/*
		 * dummy mapping क्रम root घड़ीs with no specअगरied ranges
		 */
		अगर (!clk->parent) अणु
			clk->mapping = &dummy_mapping;
			जाओ out;
		पूर्ण

		/*
		 * If we're on a child घड़ी and it provides no mapping of its
		 * own, inherit the mapping from its root घड़ी.
		 */
		clkp = lookup_root_घड़ी(clk);
		mapping = clkp->mapping;
		BUG_ON(!mapping);
	पूर्ण

	/*
	 * Establish initial mapping.
	 */
	अगर (!mapping->base && mapping->phys) अणु
		kref_init(&mapping->ref);

		mapping->base = ioremap(mapping->phys, mapping->len);
		अगर (unlikely(!mapping->base))
			वापस -ENXIO;
	पूर्ण अन्यथा अगर (mapping->base) अणु
		/*
		 * Bump the refcount क्रम an existing mapping
		 */
		kref_get(&mapping->ref);
	पूर्ण

	clk->mapping = mapping;
out:
	clk->mapped_reg = clk->mapping->base;
	clk->mapped_reg += (phys_addr_t)clk->enable_reg - clk->mapping->phys;
	वापस 0;
पूर्ण

अटल व्योम clk_destroy_mapping(काष्ठा kref *kref)
अणु
	काष्ठा clk_mapping *mapping;

	mapping = container_of(kref, काष्ठा clk_mapping, ref);

	iounmap(mapping->base);
पूर्ण

अटल व्योम clk_tearकरोwn_mapping(काष्ठा clk *clk)
अणु
	काष्ठा clk_mapping *mapping = clk->mapping;

	/* Nothing to करो */
	अगर (mapping == &dummy_mapping)
		जाओ out;

	kref_put(&mapping->ref, clk_destroy_mapping);
	clk->mapping = शून्य;
out:
	clk->mapped_reg = शून्य;
पूर्ण

पूर्णांक clk_रेजिस्टर(काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस -EINVAL;

	/*
	 * trap out alपढ़ोy रेजिस्टरed घड़ीs
	 */
	अगर (clk->node.next || clk->node.prev)
		वापस 0;

	mutex_lock(&घड़ी_list_sem);

	INIT_LIST_HEAD(&clk->children);
	clk->usecount = 0;

	ret = clk_establish_mapping(clk);
	अगर (unlikely(ret))
		जाओ out_unlock;

	अगर (clk->parent)
		list_add(&clk->sibling, &clk->parent->children);
	अन्यथा
		list_add(&clk->sibling, &root_clks);

	list_add(&clk->node, &घड़ी_list);

#अगर_घोषित CONFIG_SH_CLK_CPG_LEGACY
	अगर (clk->ops && clk->ops->init)
		clk->ops->init(clk);
#पूर्ण_अगर

out_unlock:
	mutex_unlock(&घड़ी_list_sem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर);

व्योम clk_unरेजिस्टर(काष्ठा clk *clk)
अणु
	mutex_lock(&घड़ी_list_sem);
	list_del(&clk->sibling);
	list_del(&clk->node);
	clk_tearकरोwn_mapping(clk);
	mutex_unlock(&घड़ी_list_sem);
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर);

व्योम clk_enable_init_घड़ीs(व्योम)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &घड़ी_list, node)
		अगर (clkp->flags & CLK_ENABLE_ON_INIT)
			clk_enable(clkp);
पूर्ण

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk->rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक ret = -EOPNOTSUPP;
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस 0;

	spin_lock_irqsave(&घड़ी_lock, flags);

	अगर (likely(clk->ops && clk->ops->set_rate)) अणु
		ret = clk->ops->set_rate(clk, rate);
		अगर (ret != 0)
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		clk->rate = rate;
		ret = 0;
	पूर्ण

	अगर (clk->ops && clk->ops->recalc)
		clk->rate = clk->ops->recalc(clk);

	propagate_rate(clk);

out_unlock:
	spin_unlock_irqrestore(&घड़ी_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!parent || !clk)
		वापस ret;
	अगर (clk->parent == parent)
		वापस 0;

	spin_lock_irqsave(&घड़ी_lock, flags);
	अगर (clk->usecount == 0) अणु
		अगर (clk->ops->set_parent)
			ret = clk->ops->set_parent(clk, parent);
		अन्यथा
			ret = clk_reparent(clk, parent);

		अगर (ret == 0) अणु
			अगर (clk->ops->recalc)
				clk->rate = clk->ops->recalc(clk);
			pr_debug("set parent of %p to %p (new rate %ld)\n",
				 clk, clk->parent, clk->rate);
			propagate_rate(clk);
		पूर्ण
	पूर्ण अन्यथा
		ret = -EBUSY;
	spin_unlock_irqrestore(&घड़ी_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस शून्य;

	वापस clk->parent;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_parent);

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (!clk)
		वापस 0;

	अगर (likely(clk->ops && clk->ops->round_rate)) अणु
		अचिन्हित दीर्घ flags, rounded;

		spin_lock_irqsave(&घड़ी_lock, flags);
		rounded = clk->ops->round_rate(clk, rate);
		spin_unlock_irqrestore(&घड़ी_lock, flags);

		वापस rounded;
	पूर्ण

	वापस clk_get_rate(clk);
पूर्ण
EXPORT_SYMBOL_GPL(clk_round_rate);

#अगर_घोषित CONFIG_PM
अटल व्योम clks_core_resume(व्योम)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &घड़ी_list, node) अणु
		अगर (likely(clkp->usecount && clkp->ops)) अणु
			अचिन्हित दीर्घ rate = clkp->rate;

			अगर (likely(clkp->ops->set_parent))
				clkp->ops->set_parent(clkp,
					clkp->parent);
			अगर (likely(clkp->ops->set_rate))
				clkp->ops->set_rate(clkp, rate);
			अन्यथा अगर (likely(clkp->ops->recalc))
				clkp->rate = clkp->ops->recalc(clkp);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops clks_syscore_ops = अणु
	.resume = clks_core_resume,
पूर्ण;

अटल पूर्णांक __init clk_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&clks_syscore_ops);

	वापस 0;
पूर्ण
subsys_initcall(clk_syscore_init);
#पूर्ण_अगर

अटल पूर्णांक __init clk_late_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा clk *clk;

	/* disable all घड़ीs with zero use count */
	mutex_lock(&घड़ी_list_sem);
	spin_lock_irqsave(&घड़ी_lock, flags);

	list_क्रम_each_entry(clk, &घड़ी_list, node)
		अगर (!clk->usecount && clk->ops && clk->ops->disable)
			clk->ops->disable(clk);

	/* from now on allow घड़ी disable operations */
	allow_disable = 1;

	spin_unlock_irqrestore(&घड़ी_lock, flags);
	mutex_unlock(&घड़ी_list_sem);
	वापस 0;
पूर्ण
late_initcall(clk_late_init);
