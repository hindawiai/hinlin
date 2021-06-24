<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010-2011 Canonical Ltd <jeremy.kerr@canonical.com>
 * Copyright (C) 2011-2012 Linaro Ltd <mturquette@linaro.org>
 *
 * Standard functionality क्रम the common घड़ी API.  See Documentation/driver-api/clk.rst
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/clkdev.h>

#समावेश "clk.h"

अटल DEFINE_SPINLOCK(enable_lock);
अटल DEFINE_MUTEX(prepare_lock);

अटल काष्ठा task_काष्ठा *prepare_owner;
अटल काष्ठा task_काष्ठा *enable_owner;

अटल पूर्णांक prepare_refcnt;
अटल पूर्णांक enable_refcnt;

अटल HLIST_HEAD(clk_root_list);
अटल HLIST_HEAD(clk_orphan_list);
अटल LIST_HEAD(clk_notअगरier_list);

अटल काष्ठा hlist_head *all_lists[] = अणु
	&clk_root_list,
	&clk_orphan_list,
	शून्य,
पूर्ण;

/***    निजी data काष्ठाures    ***/

काष्ठा clk_parent_map अणु
	स्थिर काष्ठा clk_hw	*hw;
	काष्ठा clk_core		*core;
	स्थिर अक्षर		*fw_name;
	स्थिर अक्षर		*name;
	पूर्णांक			index;
पूर्ण;

काष्ठा clk_core अणु
	स्थिर अक्षर		*name;
	स्थिर काष्ठा clk_ops	*ops;
	काष्ठा clk_hw		*hw;
	काष्ठा module		*owner;
	काष्ठा device		*dev;
	काष्ठा device_node	*of_node;
	काष्ठा clk_core		*parent;
	काष्ठा clk_parent_map	*parents;
	u8			num_parents;
	u8			new_parent_index;
	अचिन्हित दीर्घ		rate;
	अचिन्हित दीर्घ		req_rate;
	अचिन्हित दीर्घ		new_rate;
	काष्ठा clk_core		*new_parent;
	काष्ठा clk_core		*new_child;
	अचिन्हित दीर्घ		flags;
	bool			orphan;
	bool			rpm_enabled;
	अचिन्हित पूर्णांक		enable_count;
	अचिन्हित पूर्णांक		prepare_count;
	अचिन्हित पूर्णांक		protect_count;
	अचिन्हित दीर्घ		min_rate;
	अचिन्हित दीर्घ		max_rate;
	अचिन्हित दीर्घ		accuracy;
	पूर्णांक			phase;
	काष्ठा clk_duty		duty;
	काष्ठा hlist_head	children;
	काष्ठा hlist_node	child_node;
	काष्ठा hlist_head	clks;
	अचिन्हित पूर्णांक		notअगरier_count;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry		*dentry;
	काष्ठा hlist_node	debug_node;
#पूर्ण_अगर
	काष्ठा kref		ref;
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/clk.h>

काष्ठा clk अणु
	काष्ठा clk_core	*core;
	काष्ठा device *dev;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *con_id;
	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
	अचिन्हित पूर्णांक exclusive_count;
	काष्ठा hlist_node clks_node;
पूर्ण;

/***           runसमय pm          ***/
अटल पूर्णांक clk_pm_runसमय_get(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;

	अगर (!core->rpm_enabled)
		वापस 0;

	ret = pm_runसमय_get_sync(core->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(core->dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम clk_pm_runसमय_put(काष्ठा clk_core *core)
अणु
	अगर (!core->rpm_enabled)
		वापस;

	pm_runसमय_put_sync(core->dev);
पूर्ण

/***           locking             ***/
अटल व्योम clk_prepare_lock(व्योम)
अणु
	अगर (!mutex_trylock(&prepare_lock)) अणु
		अगर (prepare_owner == current) अणु
			prepare_refcnt++;
			वापस;
		पूर्ण
		mutex_lock(&prepare_lock);
	पूर्ण
	WARN_ON_ONCE(prepare_owner != शून्य);
	WARN_ON_ONCE(prepare_refcnt != 0);
	prepare_owner = current;
	prepare_refcnt = 1;
पूर्ण

अटल व्योम clk_prepare_unlock(व्योम)
अणु
	WARN_ON_ONCE(prepare_owner != current);
	WARN_ON_ONCE(prepare_refcnt == 0);

	अगर (--prepare_refcnt)
		वापस;
	prepare_owner = शून्य;
	mutex_unlock(&prepare_lock);
पूर्ण

अटल अचिन्हित दीर्घ clk_enable_lock(व्योम)
	__acquires(enable_lock)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * On UP प्रणालीs, spin_trylock_irqsave() always वापसs true, even अगर
	 * we alपढ़ोy hold the lock. So, in that हाल, we rely only on
	 * reference counting.
	 */
	अगर (!IS_ENABLED(CONFIG_SMP) ||
	    !spin_trylock_irqsave(&enable_lock, flags)) अणु
		अगर (enable_owner == current) अणु
			enable_refcnt++;
			__acquire(enable_lock);
			अगर (!IS_ENABLED(CONFIG_SMP))
				local_save_flags(flags);
			वापस flags;
		पूर्ण
		spin_lock_irqsave(&enable_lock, flags);
	पूर्ण
	WARN_ON_ONCE(enable_owner != शून्य);
	WARN_ON_ONCE(enable_refcnt != 0);
	enable_owner = current;
	enable_refcnt = 1;
	वापस flags;
पूर्ण

अटल व्योम clk_enable_unlock(अचिन्हित दीर्घ flags)
	__releases(enable_lock)
अणु
	WARN_ON_ONCE(enable_owner != current);
	WARN_ON_ONCE(enable_refcnt == 0);

	अगर (--enable_refcnt) अणु
		__release(enable_lock);
		वापस;
	पूर्ण
	enable_owner = शून्य;
	spin_unlock_irqrestore(&enable_lock, flags);
पूर्ण

अटल bool clk_core_rate_is_रक्षित(काष्ठा clk_core *core)
अणु
	वापस core->protect_count;
पूर्ण

अटल bool clk_core_is_prepared(काष्ठा clk_core *core)
अणु
	bool ret = false;

	/*
	 * .is_prepared is optional क्रम घड़ीs that can prepare
	 * fall back to software usage counter अगर it is missing
	 */
	अगर (!core->ops->is_prepared)
		वापस core->prepare_count;

	अगर (!clk_pm_runसमय_get(core)) अणु
		ret = core->ops->is_prepared(core->hw);
		clk_pm_runसमय_put(core);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool clk_core_is_enabled(काष्ठा clk_core *core)
अणु
	bool ret = false;

	/*
	 * .is_enabled is only mandatory क्रम घड़ीs that gate
	 * fall back to software usage counter अगर .is_enabled is missing
	 */
	अगर (!core->ops->is_enabled)
		वापस core->enable_count;

	/*
	 * Check अगर घड़ी controller's device is runसमय active beक्रमe
	 * calling .is_enabled callback. If not, assume that घड़ी is
	 * disabled, because we might be called from atomic context, from
	 * which pm_runसमय_get() is not allowed.
	 * This function is called मुख्यly from clk_disable_unused_subtree,
	 * which ensures proper runसमय pm activation of controller beक्रमe
	 * taking enable spinlock, but the below check is needed अगर one tries
	 * to call it from other places.
	 */
	अगर (core->rpm_enabled) अणु
		pm_runसमय_get_noresume(core->dev);
		अगर (!pm_runसमय_active(core->dev)) अणु
			ret = false;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = core->ops->is_enabled(core->hw);
करोne:
	अगर (core->rpm_enabled)
		pm_runसमय_put(core->dev);

	वापस ret;
पूर्ण

/***    helper functions   ***/

स्थिर अक्षर *__clk_get_name(स्थिर काष्ठा clk *clk)
अणु
	वापस !clk ? शून्य : clk->core->name;
पूर्ण
EXPORT_SYMBOL_GPL(__clk_get_name);

स्थिर अक्षर *clk_hw_get_name(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस hw->core->name;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_name);

काष्ठा clk_hw *__clk_get_hw(काष्ठा clk *clk)
अणु
	वापस !clk ? शून्य : clk->core->hw;
पूर्ण
EXPORT_SYMBOL_GPL(__clk_get_hw);

अचिन्हित पूर्णांक clk_hw_get_num_parents(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस hw->core->num_parents;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_num_parents);

काष्ठा clk_hw *clk_hw_get_parent(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस hw->core->parent ? hw->core->parent->hw : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_parent);

अटल काष्ठा clk_core *__clk_lookup_subtree(स्थिर अक्षर *name,
					     काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;
	काष्ठा clk_core *ret;

	अगर (!म_भेद(core->name, name))
		वापस core;

	hlist_क्रम_each_entry(child, &core->children, child_node) अणु
		ret = __clk_lookup_subtree(name, child);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा clk_core *clk_core_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा clk_core *root_clk;
	काष्ठा clk_core *ret;

	अगर (!name)
		वापस शून्य;

	/* search the 'proper' clk tree first */
	hlist_क्रम_each_entry(root_clk, &clk_root_list, child_node) अणु
		ret = __clk_lookup_subtree(name, root_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* अगर not found, then search the orphan tree */
	hlist_क्रम_each_entry(root_clk, &clk_orphan_list, child_node) अणु
		ret = __clk_lookup_subtree(name, root_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक of_parse_clkspec(स्थिर काष्ठा device_node *np, पूर्णांक index,
			    स्थिर अक्षर *name, काष्ठा of_phandle_args *out_args);
अटल काष्ठा clk_hw *
of_clk_get_hw_from_clkspec(काष्ठा of_phandle_args *clkspec);
#अन्यथा
अटल अंतरभूत पूर्णांक of_parse_clkspec(स्थिर काष्ठा device_node *np, पूर्णांक index,
				   स्थिर अक्षर *name,
				   काष्ठा of_phandle_args *out_args)
अणु
	वापस -ENOENT;
पूर्ण
अटल अंतरभूत काष्ठा clk_hw *
of_clk_get_hw_from_clkspec(काष्ठा of_phandle_args *clkspec)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
#पूर्ण_अगर

/**
 * clk_core_get - Find the clk_core parent of a clk
 * @core: clk to find parent of
 * @p_index: parent index to search क्रम
 *
 * This is the preferred method क्रम clk providers to find the parent of a
 * clk when that parent is बाह्यal to the clk controller. The parent_names
 * array is indexed and treated as a local name matching a string in the device
 * node's 'clock-names' property or as the 'con_id' matching the device's
 * dev_name() in a clk_lookup. This allows clk providers to use their own
 * namespace instead of looking क्रम a globally unique parent string.
 *
 * For example the following DT snippet would allow a घड़ी रेजिस्टरed by the
 * घड़ी-controller@c001 that has a clk_init_data::parent_data array
 * with 'xtal' in the 'name' member to find the घड़ी provided by the
 * घड़ी-controller@f00abcd without needing to get the globally unique name of
 * the xtal clk.
 *
 *      parent: घड़ी-controller@f00abcd अणु
 *              reg = <0xf00abcd 0xabcd>;
 *              #घड़ी-cells = <0>;
 *      पूर्ण;
 *
 *      घड़ी-controller@c001 अणु
 *              reg = <0xc001 0xf00d>;
 *              घड़ीs = <&parent>;
 *              घड़ी-names = "xtal";
 *              #घड़ी-cells = <1>;
 *      पूर्ण;
 *
 * Returns: -ENOENT when the provider can't be found or the clk doesn't
 * exist in the provider or the name can't be found in the DT node or
 * in a clkdev lookup. शून्य when the provider knows about the clk but it
 * isn't provided on this प्रणाली.
 * A valid clk_core poपूर्णांकer when the clk can be found in the provider.
 */
अटल काष्ठा clk_core *clk_core_get(काष्ठा clk_core *core, u8 p_index)
अणु
	स्थिर अक्षर *name = core->parents[p_index].fw_name;
	पूर्णांक index = core->parents[p_index].index;
	काष्ठा clk_hw *hw = ERR_PTR(-ENOENT);
	काष्ठा device *dev = core->dev;
	स्थिर अक्षर *dev_id = dev ? dev_name(dev) : शून्य;
	काष्ठा device_node *np = core->of_node;
	काष्ठा of_phandle_args clkspec;

	अगर (np && (name || index >= 0) &&
	    !of_parse_clkspec(np, index, name, &clkspec)) अणु
		hw = of_clk_get_hw_from_clkspec(&clkspec);
		of_node_put(clkspec.np);
	पूर्ण अन्यथा अगर (name) अणु
		/*
		 * If the DT search above couldn't find the provider fallback to
		 * looking up via clkdev based clk_lookups.
		 */
		hw = clk_find_hw(dev_id, name);
	पूर्ण

	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);

	वापस hw->core;
पूर्ण

अटल व्योम clk_core_fill_parent_index(काष्ठा clk_core *core, u8 index)
अणु
	काष्ठा clk_parent_map *entry = &core->parents[index];
	काष्ठा clk_core *parent;

	अगर (entry->hw) अणु
		parent = entry->hw->core;
		/*
		 * We have a direct reference but it isn't रेजिस्टरed yet?
		 * Orphan it and let clk_reparent() update the orphan status
		 * when the parent is रेजिस्टरed.
		 */
		अगर (!parent)
			parent = ERR_PTR(-EPROBE_DEFER);
	पूर्ण अन्यथा अणु
		parent = clk_core_get(core, index);
		अगर (PTR_ERR(parent) == -ENOENT && entry->name)
			parent = clk_core_lookup(entry->name);
	पूर्ण

	/* Only cache it अगर it's not an error */
	अगर (!IS_ERR(parent))
		entry->core = parent;
पूर्ण

अटल काष्ठा clk_core *clk_core_get_parent_by_index(काष्ठा clk_core *core,
							 u8 index)
अणु
	अगर (!core || index >= core->num_parents || !core->parents)
		वापस शून्य;

	अगर (!core->parents[index].core)
		clk_core_fill_parent_index(core, index);

	वापस core->parents[index].core;
पूर्ण

काष्ठा clk_hw *
clk_hw_get_parent_by_index(स्थिर काष्ठा clk_hw *hw, अचिन्हित पूर्णांक index)
अणु
	काष्ठा clk_core *parent;

	parent = clk_core_get_parent_by_index(hw->core, index);

	वापस !parent ? शून्य : parent->hw;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_parent_by_index);

अचिन्हित पूर्णांक __clk_get_enable_count(काष्ठा clk *clk)
अणु
	वापस !clk ? 0 : clk->core->enable_count;
पूर्ण

अटल अचिन्हित दीर्घ clk_core_get_rate_nolock(काष्ठा clk_core *core)
अणु
	अगर (!core)
		वापस 0;

	अगर (!core->num_parents || core->parent)
		वापस core->rate;

	/*
	 * Clk must have a parent because num_parents > 0 but the parent isn't
	 * known yet. Best to वापस 0 as the rate of this clk until we can
	 * properly recalc the rate based on the parent's rate.
	 */
	वापस 0;
पूर्ण

अचिन्हित दीर्घ clk_hw_get_rate(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस clk_core_get_rate_nolock(hw->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_rate);

अटल अचिन्हित दीर्घ clk_core_get_accuracy_no_lock(काष्ठा clk_core *core)
अणु
	अगर (!core)
		वापस 0;

	वापस core->accuracy;
पूर्ण

अचिन्हित दीर्घ clk_hw_get_flags(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस hw->core->flags;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_flags);

bool clk_hw_is_prepared(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस clk_core_is_prepared(hw->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_is_prepared);

bool clk_hw_rate_is_रक्षित(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस clk_core_rate_is_रक्षित(hw->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_rate_is_रक्षित);

bool clk_hw_is_enabled(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस clk_core_is_enabled(hw->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_is_enabled);

bool __clk_is_enabled(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस false;

	वापस clk_core_is_enabled(clk->core);
पूर्ण
EXPORT_SYMBOL_GPL(__clk_is_enabled);

अटल bool mux_is_better_rate(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ now,
			   अचिन्हित दीर्घ best, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_MUX_ROUND_CLOSEST)
		वापस असल(now - rate) < असल(best - rate);

	वापस now <= rate && now > best;
पूर्ण

पूर्णांक clk_mux_determine_rate_flags(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req,
				 अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_core *core = hw->core, *parent, *best_parent = शून्य;
	पूर्णांक i, num_parents, ret;
	अचिन्हित दीर्घ best = 0;
	काष्ठा clk_rate_request parent_req = *req;

	/* अगर NO_REPARENT flag set, pass through to current parent */
	अगर (core->flags & CLK_SET_RATE_NO_REPARENT) अणु
		parent = core->parent;
		अगर (core->flags & CLK_SET_RATE_PARENT) अणु
			ret = __clk_determine_rate(parent ? parent->hw : शून्य,
						   &parent_req);
			अगर (ret)
				वापस ret;

			best = parent_req.rate;
		पूर्ण अन्यथा अगर (parent) अणु
			best = clk_core_get_rate_nolock(parent);
		पूर्ण अन्यथा अणु
			best = clk_core_get_rate_nolock(core);
		पूर्ण

		जाओ out;
	पूर्ण

	/* find the parent that can provide the fastest rate <= rate */
	num_parents = core->num_parents;
	क्रम (i = 0; i < num_parents; i++) अणु
		parent = clk_core_get_parent_by_index(core, i);
		अगर (!parent)
			जारी;

		अगर (core->flags & CLK_SET_RATE_PARENT) अणु
			parent_req = *req;
			ret = __clk_determine_rate(parent->hw, &parent_req);
			अगर (ret)
				जारी;
		पूर्ण अन्यथा अणु
			parent_req.rate = clk_core_get_rate_nolock(parent);
		पूर्ण

		अगर (mux_is_better_rate(req->rate, parent_req.rate,
				       best, flags)) अणु
			best_parent = parent;
			best = parent_req.rate;
		पूर्ण
	पूर्ण

	अगर (!best_parent)
		वापस -EINVAL;

out:
	अगर (best_parent)
		req->best_parent_hw = best_parent->hw;
	req->best_parent_rate = best;
	req->rate = best;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_mux_determine_rate_flags);

काष्ठा clk *__clk_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा clk_core *core = clk_core_lookup(name);

	वापस !core ? शून्य : core->hw->clk;
पूर्ण

अटल व्योम clk_core_get_boundaries(काष्ठा clk_core *core,
				    अचिन्हित दीर्घ *min_rate,
				    अचिन्हित दीर्घ *max_rate)
अणु
	काष्ठा clk *clk_user;

	lockdep_निश्चित_held(&prepare_lock);

	*min_rate = core->min_rate;
	*max_rate = core->max_rate;

	hlist_क्रम_each_entry(clk_user, &core->clks, clks_node)
		*min_rate = max(*min_rate, clk_user->min_rate);

	hlist_क्रम_each_entry(clk_user, &core->clks, clks_node)
		*max_rate = min(*max_rate, clk_user->max_rate);
पूर्ण

व्योम clk_hw_set_rate_range(काष्ठा clk_hw *hw, अचिन्हित दीर्घ min_rate,
			   अचिन्हित दीर्घ max_rate)
अणु
	hw->core->min_rate = min_rate;
	hw->core->max_rate = max_rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_set_rate_range);

/*
 * __clk_mux_determine_rate - clk_ops::determine_rate implementation क्रम a mux type clk
 * @hw: mux type clk to determine rate on
 * @req: rate request, also used to वापस preferred parent and frequencies
 *
 * Helper क्रम finding best parent to provide a given frequency. This can be used
 * directly as a determine_rate callback (e.g. क्रम a mux), or from a more
 * complex घड़ी that may combine a mux with other operations.
 *
 * Returns: 0 on success, -EERROR value on error
 */
पूर्णांक __clk_mux_determine_rate(काष्ठा clk_hw *hw,
			     काष्ठा clk_rate_request *req)
अणु
	वापस clk_mux_determine_rate_flags(hw, req, 0);
पूर्ण
EXPORT_SYMBOL_GPL(__clk_mux_determine_rate);

पूर्णांक __clk_mux_determine_rate_बंदst(काष्ठा clk_hw *hw,
				     काष्ठा clk_rate_request *req)
अणु
	वापस clk_mux_determine_rate_flags(hw, req, CLK_MUX_ROUND_CLOSEST);
पूर्ण
EXPORT_SYMBOL_GPL(__clk_mux_determine_rate_बंदst);

/***        clk api        ***/

अटल व्योम clk_core_rate_unprotect(काष्ठा clk_core *core)
अणु
	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस;

	अगर (WARN(core->protect_count == 0,
	    "%s already unprotected\n", core->name))
		वापस;

	अगर (--core->protect_count > 0)
		वापस;

	clk_core_rate_unprotect(core->parent);
पूर्ण

अटल पूर्णांक clk_core_rate_nuke_protect(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस -EINVAL;

	अगर (core->protect_count == 0)
		वापस 0;

	ret = core->protect_count;
	core->protect_count = 1;
	clk_core_rate_unprotect(core);

	वापस ret;
पूर्ण

/**
 * clk_rate_exclusive_put - release exclusivity over घड़ी rate control
 * @clk: the clk over which the exclusivity is released
 *
 * clk_rate_exclusive_put() completes a critical section during which a घड़ी
 * consumer cannot tolerate any other consumer making any operation on the
 * घड़ी which could result in a rate change or rate glitch. Exclusive घड़ीs
 * cannot have their rate changed, either directly or indirectly due to changes
 * further up the parent chain of घड़ीs. As a result, घड़ीs up parent chain
 * also get under exclusive control of the calling consumer.
 *
 * If exlusivity is claimed more than once on घड़ी, even by the same consumer,
 * the rate effectively माला_लो locked as exclusivity can't be preempted.
 *
 * Calls to clk_rate_exclusive_put() must be balanced with calls to
 * clk_rate_exclusive_get(). Calls to this function may sleep, and करो not वापस
 * error status.
 */
व्योम clk_rate_exclusive_put(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस;

	clk_prepare_lock();

	/*
	 * अगर there is something wrong with this consumer protect count, stop
	 * here beक्रमe messing with the provider
	 */
	अगर (WARN_ON(clk->exclusive_count <= 0))
		जाओ out;

	clk_core_rate_unprotect(clk->core);
	clk->exclusive_count--;
out:
	clk_prepare_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(clk_rate_exclusive_put);

अटल व्योम clk_core_rate_protect(काष्ठा clk_core *core)
अणु
	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस;

	अगर (core->protect_count == 0)
		clk_core_rate_protect(core->parent);

	core->protect_count++;
पूर्ण

अटल व्योम clk_core_rate_restore_protect(काष्ठा clk_core *core, पूर्णांक count)
अणु
	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस;

	अगर (count == 0)
		वापस;

	clk_core_rate_protect(core);
	core->protect_count = count;
पूर्ण

/**
 * clk_rate_exclusive_get - get exclusivity over the clk rate control
 * @clk: the clk over which the exclusity of rate control is requested
 *
 * clk_rate_exclusive_get() begins a critical section during which a घड़ी
 * consumer cannot tolerate any other consumer making any operation on the
 * घड़ी which could result in a rate change or rate glitch. Exclusive घड़ीs
 * cannot have their rate changed, either directly or indirectly due to changes
 * further up the parent chain of घड़ीs. As a result, घड़ीs up parent chain
 * also get under exclusive control of the calling consumer.
 *
 * If exlusivity is claimed more than once on घड़ी, even by the same consumer,
 * the rate effectively माला_लो locked as exclusivity can't be preempted.
 *
 * Calls to clk_rate_exclusive_get() should be balanced with calls to
 * clk_rate_exclusive_put(). Calls to this function may sleep.
 * Returns 0 on success, -EERROR otherwise
 */
पूर्णांक clk_rate_exclusive_get(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	clk_prepare_lock();
	clk_core_rate_protect(clk->core);
	clk->exclusive_count++;
	clk_prepare_unlock();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_rate_exclusive_get);

अटल व्योम clk_core_unprepare(काष्ठा clk_core *core)
अणु
	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस;

	अगर (WARN(core->prepare_count == 0,
	    "%s already unprepared\n", core->name))
		वापस;

	अगर (WARN(core->prepare_count == 1 && core->flags & CLK_IS_CRITICAL,
	    "Unpreparing critical %s\n", core->name))
		वापस;

	अगर (core->flags & CLK_SET_RATE_GATE)
		clk_core_rate_unprotect(core);

	अगर (--core->prepare_count > 0)
		वापस;

	WARN(core->enable_count > 0, "Unpreparing enabled %s\n", core->name);

	trace_clk_unprepare(core);

	अगर (core->ops->unprepare)
		core->ops->unprepare(core->hw);

	clk_pm_runसमय_put(core);

	trace_clk_unprepare_complete(core);
	clk_core_unprepare(core->parent);
पूर्ण

अटल व्योम clk_core_unprepare_lock(काष्ठा clk_core *core)
अणु
	clk_prepare_lock();
	clk_core_unprepare(core);
	clk_prepare_unlock();
पूर्ण

/**
 * clk_unprepare - unकरो preparation of a घड़ी source
 * @clk: the clk being unprepared
 *
 * clk_unprepare may sleep, which dअगरferentiates it from clk_disable.  In a
 * simple हाल, clk_unprepare can be used instead of clk_disable to gate a clk
 * अगर the operation may sleep.  One example is a clk which is accessed over
 * I2c.  In the complex हाल a clk gate operation may require a fast and a slow
 * part.  It is this reason that clk_unprepare and clk_disable are not mutually
 * exclusive.  In fact clk_disable must be called beक्रमe clk_unprepare.
 */
व्योम clk_unprepare(काष्ठा clk *clk)
अणु
	अगर (IS_ERR_OR_शून्य(clk))
		वापस;

	clk_core_unprepare_lock(clk->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_unprepare);

अटल पूर्णांक clk_core_prepare(काष्ठा clk_core *core)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस 0;

	अगर (core->prepare_count == 0) अणु
		ret = clk_pm_runसमय_get(core);
		अगर (ret)
			वापस ret;

		ret = clk_core_prepare(core->parent);
		अगर (ret)
			जाओ runसमय_put;

		trace_clk_prepare(core);

		अगर (core->ops->prepare)
			ret = core->ops->prepare(core->hw);

		trace_clk_prepare_complete(core);

		अगर (ret)
			जाओ unprepare;
	पूर्ण

	core->prepare_count++;

	/*
	 * CLK_SET_RATE_GATE is a special हाल of घड़ी protection
	 * Instead of a consumer claiming exclusive rate control, it is
	 * actually the provider which prevents any consumer from making any
	 * operation which could result in a rate change or rate glitch जबतक
	 * the घड़ी is prepared.
	 */
	अगर (core->flags & CLK_SET_RATE_GATE)
		clk_core_rate_protect(core);

	वापस 0;
unprepare:
	clk_core_unprepare(core->parent);
runसमय_put:
	clk_pm_runसमय_put(core);
	वापस ret;
पूर्ण

अटल पूर्णांक clk_core_prepare_lock(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;

	clk_prepare_lock();
	ret = clk_core_prepare(core);
	clk_prepare_unlock();

	वापस ret;
पूर्ण

/**
 * clk_prepare - prepare a घड़ी source
 * @clk: the clk being prepared
 *
 * clk_prepare may sleep, which dअगरferentiates it from clk_enable.  In a simple
 * हाल, clk_prepare can be used instead of clk_enable to ungate a clk अगर the
 * operation may sleep.  One example is a clk which is accessed over I2c.  In
 * the complex हाल a clk ungate operation may require a fast and a slow part.
 * It is this reason that clk_prepare and clk_enable are not mutually
 * exclusive.  In fact clk_prepare must be called beक्रमe clk_enable.
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक clk_prepare(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk_core_prepare_lock(clk->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_prepare);

अटल व्योम clk_core_disable(काष्ठा clk_core *core)
अणु
	lockdep_निश्चित_held(&enable_lock);

	अगर (!core)
		वापस;

	अगर (WARN(core->enable_count == 0, "%s already disabled\n", core->name))
		वापस;

	अगर (WARN(core->enable_count == 1 && core->flags & CLK_IS_CRITICAL,
	    "Disabling critical %s\n", core->name))
		वापस;

	अगर (--core->enable_count > 0)
		वापस;

	trace_clk_disable_rcuidle(core);

	अगर (core->ops->disable)
		core->ops->disable(core->hw);

	trace_clk_disable_complete_rcuidle(core);

	clk_core_disable(core->parent);
पूर्ण

अटल व्योम clk_core_disable_lock(काष्ठा clk_core *core)
अणु
	अचिन्हित दीर्घ flags;

	flags = clk_enable_lock();
	clk_core_disable(core);
	clk_enable_unlock(flags);
पूर्ण

/**
 * clk_disable - gate a घड़ी
 * @clk: the clk being gated
 *
 * clk_disable must not sleep, which dअगरferentiates it from clk_unprepare.  In
 * a simple हाल, clk_disable can be used instead of clk_unprepare to gate a
 * clk अगर the operation is fast and will never sleep.  One example is a
 * SoC-पूर्णांकernal clk which is controlled via simple रेजिस्टर ग_लिखोs.  In the
 * complex हाल a clk gate operation may require a fast and a slow part.  It is
 * this reason that clk_unprepare and clk_disable are not mutually exclusive.
 * In fact clk_disable must be called beक्रमe clk_unprepare.
 */
व्योम clk_disable(काष्ठा clk *clk)
अणु
	अगर (IS_ERR_OR_शून्य(clk))
		वापस;

	clk_core_disable_lock(clk->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_disable);

अटल पूर्णांक clk_core_enable(काष्ठा clk_core *core)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&enable_lock);

	अगर (!core)
		वापस 0;

	अगर (WARN(core->prepare_count == 0,
	    "Enabling unprepared %s\n", core->name))
		वापस -ESHUTDOWN;

	अगर (core->enable_count == 0) अणु
		ret = clk_core_enable(core->parent);

		अगर (ret)
			वापस ret;

		trace_clk_enable_rcuidle(core);

		अगर (core->ops->enable)
			ret = core->ops->enable(core->hw);

		trace_clk_enable_complete_rcuidle(core);

		अगर (ret) अणु
			clk_core_disable(core->parent);
			वापस ret;
		पूर्ण
	पूर्ण

	core->enable_count++;
	वापस 0;
पूर्ण

अटल पूर्णांक clk_core_enable_lock(काष्ठा clk_core *core)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	flags = clk_enable_lock();
	ret = clk_core_enable(core);
	clk_enable_unlock(flags);

	वापस ret;
पूर्ण

/**
 * clk_gate_restore_context - restore context क्रम घातeroff
 * @hw: the clk_hw poपूर्णांकer of घड़ी whose state is to be restored
 *
 * The घड़ी gate restore context function enables or disables
 * the gate घड़ीs based on the enable_count. This is करोne in हालs
 * where the घड़ी context is lost and based on the enable_count
 * the घड़ी either needs to be enabled/disabled. This
 * helps restore the state of gate घड़ीs.
 */
व्योम clk_gate_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_core *core = hw->core;

	अगर (core->enable_count)
		core->ops->enable(hw);
	अन्यथा
		core->ops->disable(hw);
पूर्ण
EXPORT_SYMBOL_GPL(clk_gate_restore_context);

अटल पूर्णांक clk_core_save_context(काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;
	पूर्णांक ret = 0;

	hlist_क्रम_each_entry(child, &core->children, child_node) अणु
		ret = clk_core_save_context(child);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (core->ops && core->ops->save_context)
		ret = core->ops->save_context(core->hw);

	वापस ret;
पूर्ण

अटल व्योम clk_core_restore_context(काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;

	अगर (core->ops && core->ops->restore_context)
		core->ops->restore_context(core->hw);

	hlist_क्रम_each_entry(child, &core->children, child_node)
		clk_core_restore_context(child);
पूर्ण

/**
 * clk_save_context - save घड़ी context क्रम घातeroff
 *
 * Saves the context of the घड़ी रेजिस्टर क्रम घातerstates in which the
 * contents of the रेजिस्टरs will be lost. Occurs deep within the suspend
 * code.  Returns 0 on success.
 */
पूर्णांक clk_save_context(व्योम)
अणु
	काष्ठा clk_core *clk;
	पूर्णांक ret;

	hlist_क्रम_each_entry(clk, &clk_root_list, child_node) अणु
		ret = clk_core_save_context(clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	hlist_क्रम_each_entry(clk, &clk_orphan_list, child_node) अणु
		ret = clk_core_save_context(clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_save_context);

/**
 * clk_restore_context - restore घड़ी context after घातeroff
 *
 * Restore the saved घड़ी context upon resume.
 *
 */
व्योम clk_restore_context(व्योम)
अणु
	काष्ठा clk_core *core;

	hlist_क्रम_each_entry(core, &clk_root_list, child_node)
		clk_core_restore_context(core);

	hlist_क्रम_each_entry(core, &clk_orphan_list, child_node)
		clk_core_restore_context(core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_restore_context);

/**
 * clk_enable - ungate a घड़ी
 * @clk: the clk being ungated
 *
 * clk_enable must not sleep, which dअगरferentiates it from clk_prepare.  In a
 * simple हाल, clk_enable can be used instead of clk_prepare to ungate a clk
 * अगर the operation will never sleep.  One example is a SoC-पूर्णांकernal clk which
 * is controlled via simple रेजिस्टर ग_लिखोs.  In the complex हाल a clk ungate
 * operation may require a fast and a slow part.  It is this reason that
 * clk_enable and clk_prepare are not mutually exclusive.  In fact clk_prepare
 * must be called beक्रमe clk_enable.  Returns 0 on success, -EERROR
 * otherwise.
 */
पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk_core_enable_lock(clk->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_enable);

/**
 * clk_is_enabled_when_prepared - indicate अगर preparing a घड़ी also enables it.
 * @clk: घड़ी source
 *
 * Returns true अगर clk_prepare() implicitly enables the घड़ी, effectively
 * making clk_enable()/clk_disable() no-ops, false otherwise.
 *
 * This is of पूर्णांकerest मुख्यly to घातer management code where actually
 * disabling the घड़ी also requires unpreparing it to have any material
 * effect.
 *
 * Regardless of the value वापसed here, the caller must always invoke
 * clk_enable() or clk_prepare_enable()  and counterparts क्रम usage counts
 * to be right.
 */
bool clk_is_enabled_when_prepared(काष्ठा clk *clk)
अणु
	वापस clk && !(clk->core->ops->enable && clk->core->ops->disable);
पूर्ण
EXPORT_SYMBOL_GPL(clk_is_enabled_when_prepared);

अटल पूर्णांक clk_core_prepare_enable(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;

	ret = clk_core_prepare_lock(core);
	अगर (ret)
		वापस ret;

	ret = clk_core_enable_lock(core);
	अगर (ret)
		clk_core_unprepare_lock(core);

	वापस ret;
पूर्ण

अटल व्योम clk_core_disable_unprepare(काष्ठा clk_core *core)
अणु
	clk_core_disable_lock(core);
	clk_core_unprepare_lock(core);
पूर्ण

अटल व्योम __init clk_unprepare_unused_subtree(काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;

	lockdep_निश्चित_held(&prepare_lock);

	hlist_क्रम_each_entry(child, &core->children, child_node)
		clk_unprepare_unused_subtree(child);

	अगर (core->prepare_count)
		वापस;

	अगर (core->flags & CLK_IGNORE_UNUSED)
		वापस;

	अगर (clk_pm_runसमय_get(core))
		वापस;

	अगर (clk_core_is_prepared(core)) अणु
		trace_clk_unprepare(core);
		अगर (core->ops->unprepare_unused)
			core->ops->unprepare_unused(core->hw);
		अन्यथा अगर (core->ops->unprepare)
			core->ops->unprepare(core->hw);
		trace_clk_unprepare_complete(core);
	पूर्ण

	clk_pm_runसमय_put(core);
पूर्ण

अटल व्योम __init clk_disable_unused_subtree(काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_held(&prepare_lock);

	hlist_क्रम_each_entry(child, &core->children, child_node)
		clk_disable_unused_subtree(child);

	अगर (core->flags & CLK_OPS_PARENT_ENABLE)
		clk_core_prepare_enable(core->parent);

	अगर (clk_pm_runसमय_get(core))
		जाओ unprepare_out;

	flags = clk_enable_lock();

	अगर (core->enable_count)
		जाओ unlock_out;

	अगर (core->flags & CLK_IGNORE_UNUSED)
		जाओ unlock_out;

	/*
	 * some gate घड़ीs have special needs during the disable-unused
	 * sequence.  call .disable_unused अगर available, otherwise fall
	 * back to .disable
	 */
	अगर (clk_core_is_enabled(core)) अणु
		trace_clk_disable(core);
		अगर (core->ops->disable_unused)
			core->ops->disable_unused(core->hw);
		अन्यथा अगर (core->ops->disable)
			core->ops->disable(core->hw);
		trace_clk_disable_complete(core);
	पूर्ण

unlock_out:
	clk_enable_unlock(flags);
	clk_pm_runसमय_put(core);
unprepare_out:
	अगर (core->flags & CLK_OPS_PARENT_ENABLE)
		clk_core_disable_unprepare(core->parent);
पूर्ण

अटल bool clk_ignore_unused __initdata;
अटल पूर्णांक __init clk_ignore_unused_setup(अक्षर *__unused)
अणु
	clk_ignore_unused = true;
	वापस 1;
पूर्ण
__setup("clk_ignore_unused", clk_ignore_unused_setup);

अटल पूर्णांक __init clk_disable_unused(व्योम)
अणु
	काष्ठा clk_core *core;

	अगर (clk_ignore_unused) अणु
		pr_warn("clk: Not disabling unused clocks\n");
		वापस 0;
	पूर्ण

	clk_prepare_lock();

	hlist_क्रम_each_entry(core, &clk_root_list, child_node)
		clk_disable_unused_subtree(core);

	hlist_क्रम_each_entry(core, &clk_orphan_list, child_node)
		clk_disable_unused_subtree(core);

	hlist_क्रम_each_entry(core, &clk_root_list, child_node)
		clk_unprepare_unused_subtree(core);

	hlist_क्रम_each_entry(core, &clk_orphan_list, child_node)
		clk_unprepare_unused_subtree(core);

	clk_prepare_unlock();

	वापस 0;
पूर्ण
late_initcall_sync(clk_disable_unused);

अटल पूर्णांक clk_core_determine_round_nolock(काष्ठा clk_core *core,
					   काष्ठा clk_rate_request *req)
अणु
	दीर्घ rate;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस 0;

	/*
	 * At this poपूर्णांक, core protection will be disabled
	 * - अगर the provider is not रक्षित at all
	 * - अगर the calling consumer is the only one which has exclusivity
	 *   over the provider
	 */
	अगर (clk_core_rate_is_रक्षित(core)) अणु
		req->rate = core->rate;
	पूर्ण अन्यथा अगर (core->ops->determine_rate) अणु
		वापस core->ops->determine_rate(core->hw, req);
	पूर्ण अन्यथा अगर (core->ops->round_rate) अणु
		rate = core->ops->round_rate(core->hw, req->rate,
					     &req->best_parent_rate);
		अगर (rate < 0)
			वापस rate;

		req->rate = rate;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clk_core_init_rate_req(काष्ठा clk_core * स्थिर core,
				   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_core *parent;

	अगर (WARN_ON(!core || !req))
		वापस;

	parent = core->parent;
	अगर (parent) अणु
		req->best_parent_hw = parent->hw;
		req->best_parent_rate = parent->rate;
	पूर्ण अन्यथा अणु
		req->best_parent_hw = शून्य;
		req->best_parent_rate = 0;
	पूर्ण
पूर्ण

अटल bool clk_core_can_round(काष्ठा clk_core * स्थिर core)
अणु
	वापस core->ops->determine_rate || core->ops->round_rate;
पूर्ण

अटल पूर्णांक clk_core_round_rate_nolock(काष्ठा clk_core *core,
				      काष्ठा clk_rate_request *req)
अणु
	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core) अणु
		req->rate = 0;
		वापस 0;
	पूर्ण

	clk_core_init_rate_req(core, req);

	अगर (clk_core_can_round(core))
		वापस clk_core_determine_round_nolock(core, req);
	अन्यथा अगर (core->flags & CLK_SET_RATE_PARENT)
		वापस clk_core_round_rate_nolock(core->parent, req);

	req->rate = core->rate;
	वापस 0;
पूर्ण

/**
 * __clk_determine_rate - get the बंदst rate actually supported by a घड़ी
 * @hw: determine the rate of this घड़ी
 * @req: target rate request
 *
 * Useful क्रम clk_ops such as .set_rate and .determine_rate.
 */
पूर्णांक __clk_determine_rate(काष्ठा clk_hw *hw, काष्ठा clk_rate_request *req)
अणु
	अगर (!hw) अणु
		req->rate = 0;
		वापस 0;
	पूर्ण

	वापस clk_core_round_rate_nolock(hw->core, req);
पूर्ण
EXPORT_SYMBOL_GPL(__clk_determine_rate);

/**
 * clk_hw_round_rate() - round the given rate क्रम a hw clk
 * @hw: the hw clk क्रम which we are rounding a rate
 * @rate: the rate which is to be rounded
 *
 * Takes in a rate as input and rounds it to a rate that the clk can actually
 * use.
 *
 * Context: prepare_lock must be held.
 *          For clk providers to call from within clk_ops such as .round_rate,
 *          .determine_rate.
 *
 * Return: वापसs rounded rate of hw clk अगर clk supports round_rate operation
 *         अन्यथा वापसs the parent rate.
 */
अचिन्हित दीर्घ clk_hw_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक ret;
	काष्ठा clk_rate_request req;

	clk_core_get_boundaries(hw->core, &req.min_rate, &req.max_rate);
	req.rate = rate;

	ret = clk_core_round_rate_nolock(hw->core, &req);
	अगर (ret)
		वापस 0;

	वापस req.rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_round_rate);

/**
 * clk_round_rate - round the given rate क्रम a clk
 * @clk: the clk क्रम which we are rounding a rate
 * @rate: the rate which is to be rounded
 *
 * Takes in a rate as input and rounds it to a rate that the clk can actually
 * use which is then वापसed.  If clk करोesn't support round_rate operation
 * then the parent rate is वापसed.
 */
दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_rate_request req;
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	clk_core_get_boundaries(clk->core, &req.min_rate, &req.max_rate);
	req.rate = rate;

	ret = clk_core_round_rate_nolock(clk->core, &req);

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	अगर (ret)
		वापस ret;

	वापस req.rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_round_rate);

/**
 * __clk_notअगरy - call clk notअगरier chain
 * @core: clk that is changing rate
 * @msg: clk notअगरier type (see include/linux/clk.h)
 * @old_rate: old clk rate
 * @new_rate: new clk rate
 *
 * Triggers a notअगरier call chain on the clk rate-change notअगरication
 * क्रम 'clk'.  Passes a poपूर्णांकer to the काष्ठा clk and the previous
 * and current rates to the notअगरier callback.  Intended to be called by
 * पूर्णांकernal घड़ी code only.  Returns NOTIFY_DONE from the last driver
 * called अगर all went well, or NOTIFY_STOP or NOTIFY_BAD immediately अगर
 * a driver वापसs that.
 */
अटल पूर्णांक __clk_notअगरy(काष्ठा clk_core *core, अचिन्हित दीर्घ msg,
		अचिन्हित दीर्घ old_rate, अचिन्हित दीर्घ new_rate)
अणु
	काष्ठा clk_notअगरier *cn;
	काष्ठा clk_notअगरier_data cnd;
	पूर्णांक ret = NOTIFY_DONE;

	cnd.old_rate = old_rate;
	cnd.new_rate = new_rate;

	list_क्रम_each_entry(cn, &clk_notअगरier_list, node) अणु
		अगर (cn->clk->core == core) अणु
			cnd.clk = cn->clk;
			ret = srcu_notअगरier_call_chain(&cn->notअगरier_head, msg,
					&cnd);
			अगर (ret & NOTIFY_STOP_MASK)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * __clk_recalc_accuracies
 * @core: first clk in the subtree
 *
 * Walks the subtree of clks starting with clk and recalculates accuracies as
 * it goes.  Note that अगर a clk करोes not implement the .recalc_accuracy
 * callback then it is assumed that the घड़ी will take on the accuracy of its
 * parent.
 */
अटल व्योम __clk_recalc_accuracies(काष्ठा clk_core *core)
अणु
	अचिन्हित दीर्घ parent_accuracy = 0;
	काष्ठा clk_core *child;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (core->parent)
		parent_accuracy = core->parent->accuracy;

	अगर (core->ops->recalc_accuracy)
		core->accuracy = core->ops->recalc_accuracy(core->hw,
							  parent_accuracy);
	अन्यथा
		core->accuracy = parent_accuracy;

	hlist_क्रम_each_entry(child, &core->children, child_node)
		__clk_recalc_accuracies(child);
पूर्ण

अटल दीर्घ clk_core_get_accuracy_recalc(काष्ठा clk_core *core)
अणु
	अगर (core && (core->flags & CLK_GET_ACCURACY_NOCACHE))
		__clk_recalc_accuracies(core);

	वापस clk_core_get_accuracy_no_lock(core);
पूर्ण

/**
 * clk_get_accuracy - वापस the accuracy of clk
 * @clk: the clk whose accuracy is being वापसed
 *
 * Simply वापसs the cached accuracy of the clk, unless
 * CLK_GET_ACCURACY_NOCACHE flag is set, which means a recalc_rate will be
 * issued.
 * If clk is शून्य then वापसs 0.
 */
दीर्घ clk_get_accuracy(काष्ठा clk *clk)
अणु
	दीर्घ accuracy;

	अगर (!clk)
		वापस 0;

	clk_prepare_lock();
	accuracy = clk_core_get_accuracy_recalc(clk->core);
	clk_prepare_unlock();

	वापस accuracy;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_accuracy);

अटल अचिन्हित दीर्घ clk_recalc(काष्ठा clk_core *core,
				अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ rate = parent_rate;

	अगर (core->ops->recalc_rate && !clk_pm_runसमय_get(core)) अणु
		rate = core->ops->recalc_rate(core->hw, parent_rate);
		clk_pm_runसमय_put(core);
	पूर्ण
	वापस rate;
पूर्ण

/**
 * __clk_recalc_rates
 * @core: first clk in the subtree
 * @msg: notअगरication type (see include/linux/clk.h)
 *
 * Walks the subtree of clks starting with clk and recalculates rates as it
 * goes.  Note that अगर a clk करोes not implement the .recalc_rate callback then
 * it is assumed that the घड़ी will take on the rate of its parent.
 *
 * clk_recalc_rates also propagates the POST_RATE_CHANGE notअगरication,
 * अगर necessary.
 */
अटल व्योम __clk_recalc_rates(काष्ठा clk_core *core, अचिन्हित दीर्घ msg)
अणु
	अचिन्हित दीर्घ old_rate;
	अचिन्हित दीर्घ parent_rate = 0;
	काष्ठा clk_core *child;

	lockdep_निश्चित_held(&prepare_lock);

	old_rate = core->rate;

	अगर (core->parent)
		parent_rate = core->parent->rate;

	core->rate = clk_recalc(core, parent_rate);

	/*
	 * ignore NOTIFY_STOP and NOTIFY_BAD वापस values क्रम POST_RATE_CHANGE
	 * & ABORT_RATE_CHANGE notअगरiers
	 */
	अगर (core->notअगरier_count && msg)
		__clk_notअगरy(core, msg, old_rate, core->rate);

	hlist_क्रम_each_entry(child, &core->children, child_node)
		__clk_recalc_rates(child, msg);
पूर्ण

अटल अचिन्हित दीर्घ clk_core_get_rate_recalc(काष्ठा clk_core *core)
अणु
	अगर (core && (core->flags & CLK_GET_RATE_NOCACHE))
		__clk_recalc_rates(core, 0);

	वापस clk_core_get_rate_nolock(core);
पूर्ण

/**
 * clk_get_rate - वापस the rate of clk
 * @clk: the clk whose rate is being वापसed
 *
 * Simply वापसs the cached rate of the clk, unless CLK_GET_RATE_NOCACHE flag
 * is set, which means a recalc_rate will be issued.
 * If clk is शून्य then वापसs 0.
 */
अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ rate;

	अगर (!clk)
		वापस 0;

	clk_prepare_lock();
	rate = clk_core_get_rate_recalc(clk->core);
	clk_prepare_unlock();

	वापस rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_rate);

अटल पूर्णांक clk_fetch_parent_index(काष्ठा clk_core *core,
				  काष्ठा clk_core *parent)
अणु
	पूर्णांक i;

	अगर (!parent)
		वापस -EINVAL;

	क्रम (i = 0; i < core->num_parents; i++) अणु
		/* Found it first try! */
		अगर (core->parents[i].core == parent)
			वापस i;

		/* Something अन्यथा is here, so keep looking */
		अगर (core->parents[i].core)
			जारी;

		/* Maybe core hasn't been cached but the hw is all we know? */
		अगर (core->parents[i].hw) अणु
			अगर (core->parents[i].hw == parent->hw)
				अवरोध;

			/* Didn't match, but we're expecting a clk_hw */
			जारी;
		पूर्ण

		/* Maybe it hasn't been cached (clk_set_parent() path) */
		अगर (parent == clk_core_get(core, i))
			अवरोध;

		/* Fallback to comparing globally unique names */
		अगर (core->parents[i].name &&
		    !म_भेद(parent->name, core->parents[i].name))
			अवरोध;
	पूर्ण

	अगर (i == core->num_parents)
		वापस -EINVAL;

	core->parents[i].core = parent;
	वापस i;
पूर्ण

/**
 * clk_hw_get_parent_index - वापस the index of the parent घड़ी
 * @hw: clk_hw associated with the clk being consumed
 *
 * Fetches and वापसs the index of parent घड़ी. Returns -EINVAL अगर the given
 * घड़ी करोes not have a current parent.
 */
पूर्णांक clk_hw_get_parent_index(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);

	अगर (WARN_ON(parent == शून्य))
		वापस -EINVAL;

	वापस clk_fetch_parent_index(hw->core, parent->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_get_parent_index);

/*
 * Update the orphan status of @core and all its children.
 */
अटल व्योम clk_core_update_orphan_status(काष्ठा clk_core *core, bool is_orphan)
अणु
	काष्ठा clk_core *child;

	core->orphan = is_orphan;

	hlist_क्रम_each_entry(child, &core->children, child_node)
		clk_core_update_orphan_status(child, is_orphan);
पूर्ण

अटल व्योम clk_reparent(काष्ठा clk_core *core, काष्ठा clk_core *new_parent)
अणु
	bool was_orphan = core->orphan;

	hlist_del(&core->child_node);

	अगर (new_parent) अणु
		bool becomes_orphan = new_parent->orphan;

		/* aव्योम duplicate POST_RATE_CHANGE notअगरications */
		अगर (new_parent->new_child == core)
			new_parent->new_child = शून्य;

		hlist_add_head(&core->child_node, &new_parent->children);

		अगर (was_orphan != becomes_orphan)
			clk_core_update_orphan_status(core, becomes_orphan);
	पूर्ण अन्यथा अणु
		hlist_add_head(&core->child_node, &clk_orphan_list);
		अगर (!was_orphan)
			clk_core_update_orphan_status(core, true);
	पूर्ण

	core->parent = new_parent;
पूर्ण

अटल काष्ठा clk_core *__clk_set_parent_beक्रमe(काष्ठा clk_core *core,
					   काष्ठा clk_core *parent)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा clk_core *old_parent = core->parent;

	/*
	 * 1. enable parents क्रम CLK_OPS_PARENT_ENABLE घड़ी
	 *
	 * 2. Migrate prepare state between parents and prevent race with
	 * clk_enable().
	 *
	 * If the घड़ी is not prepared, then a race with
	 * clk_enable/disable() is impossible since we alपढ़ोy have the
	 * prepare lock (future calls to clk_enable() need to be preceded by
	 * a clk_prepare()).
	 *
	 * If the घड़ी is prepared, migrate the prepared state to the new
	 * parent and also protect against a race with clk_enable() by
	 * क्रमcing the घड़ी and the new parent on.  This ensures that all
	 * future calls to clk_enable() are practically NOPs with respect to
	 * hardware and software states.
	 *
	 * See also: Comment क्रम clk_set_parent() below.
	 */

	/* enable old_parent & parent अगर CLK_OPS_PARENT_ENABLE is set */
	अगर (core->flags & CLK_OPS_PARENT_ENABLE) अणु
		clk_core_prepare_enable(old_parent);
		clk_core_prepare_enable(parent);
	पूर्ण

	/* migrate prepare count अगर > 0 */
	अगर (core->prepare_count) अणु
		clk_core_prepare_enable(parent);
		clk_core_enable_lock(core);
	पूर्ण

	/* update the clk tree topology */
	flags = clk_enable_lock();
	clk_reparent(core, parent);
	clk_enable_unlock(flags);

	वापस old_parent;
पूर्ण

अटल व्योम __clk_set_parent_after(काष्ठा clk_core *core,
				   काष्ठा clk_core *parent,
				   काष्ठा clk_core *old_parent)
अणु
	/*
	 * Finish the migration of prepare state and unकरो the changes करोne
	 * क्रम preventing a race with clk_enable().
	 */
	अगर (core->prepare_count) अणु
		clk_core_disable_lock(core);
		clk_core_disable_unprepare(old_parent);
	पूर्ण

	/* re-balance ref counting अगर CLK_OPS_PARENT_ENABLE is set */
	अगर (core->flags & CLK_OPS_PARENT_ENABLE) अणु
		clk_core_disable_unprepare(parent);
		clk_core_disable_unprepare(old_parent);
	पूर्ण
पूर्ण

अटल पूर्णांक __clk_set_parent(काष्ठा clk_core *core, काष्ठा clk_core *parent,
			    u8 p_index)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	काष्ठा clk_core *old_parent;

	old_parent = __clk_set_parent_beक्रमe(core, parent);

	trace_clk_set_parent(core, parent);

	/* change घड़ी input source */
	अगर (parent && core->ops->set_parent)
		ret = core->ops->set_parent(core->hw, p_index);

	trace_clk_set_parent_complete(core, parent);

	अगर (ret) अणु
		flags = clk_enable_lock();
		clk_reparent(core, old_parent);
		clk_enable_unlock(flags);
		__clk_set_parent_after(core, old_parent, parent);

		वापस ret;
	पूर्ण

	__clk_set_parent_after(core, parent, old_parent);

	वापस 0;
पूर्ण

/**
 * __clk_speculate_rates
 * @core: first clk in the subtree
 * @parent_rate: the "future" rate of clk's parent
 *
 * Walks the subtree of clks starting with clk, speculating rates as it
 * goes and firing off PRE_RATE_CHANGE notअगरications as necessary.
 *
 * Unlike clk_recalc_rates, clk_speculate_rates exists only क्रम sending
 * pre-rate change notअगरications and वापसs early अगर no clks in the
 * subtree have subscribed to the notअगरications.  Note that अगर a clk करोes not
 * implement the .recalc_rate callback then it is assumed that the घड़ी will
 * take on the rate of its parent.
 */
अटल पूर्णांक __clk_speculate_rates(काष्ठा clk_core *core,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_core *child;
	अचिन्हित दीर्घ new_rate;
	पूर्णांक ret = NOTIFY_DONE;

	lockdep_निश्चित_held(&prepare_lock);

	new_rate = clk_recalc(core, parent_rate);

	/* पात rate change अगर a driver वापसs NOTIFY_BAD or NOTIFY_STOP */
	अगर (core->notअगरier_count)
		ret = __clk_notअगरy(core, PRE_RATE_CHANGE, core->rate, new_rate);

	अगर (ret & NOTIFY_STOP_MASK) अणु
		pr_debug("%s: clk notifier callback for clock %s aborted with error %d\n",
				__func__, core->name, ret);
		जाओ out;
	पूर्ण

	hlist_क्रम_each_entry(child, &core->children, child_node) अणु
		ret = __clk_speculate_rates(child, new_rate);
		अगर (ret & NOTIFY_STOP_MASK)
			अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम clk_calc_subtree(काष्ठा clk_core *core, अचिन्हित दीर्घ new_rate,
			     काष्ठा clk_core *new_parent, u8 p_index)
अणु
	काष्ठा clk_core *child;

	core->new_rate = new_rate;
	core->new_parent = new_parent;
	core->new_parent_index = p_index;
	/* include clk in new parent's PRE_RATE_CHANGE notअगरications */
	core->new_child = शून्य;
	अगर (new_parent && new_parent != core->parent)
		new_parent->new_child = core;

	hlist_क्रम_each_entry(child, &core->children, child_node) अणु
		child->new_rate = clk_recalc(child, new_rate);
		clk_calc_subtree(child, child->new_rate, शून्य, 0);
	पूर्ण
पूर्ण

/*
 * calculate the new rates वापसing the topmost घड़ी that has to be
 * changed.
 */
अटल काष्ठा clk_core *clk_calc_new_rates(काष्ठा clk_core *core,
					   अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_core *top = core;
	काष्ठा clk_core *old_parent, *parent;
	अचिन्हित दीर्घ best_parent_rate = 0;
	अचिन्हित दीर्घ new_rate;
	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
	पूर्णांक p_index = 0;
	दीर्घ ret;

	/* sanity */
	अगर (IS_ERR_OR_शून्य(core))
		वापस शून्य;

	/* save parent rate, अगर it exists */
	parent = old_parent = core->parent;
	अगर (parent)
		best_parent_rate = parent->rate;

	clk_core_get_boundaries(core, &min_rate, &max_rate);

	/* find the बंदst rate and parent clk/rate */
	अगर (clk_core_can_round(core)) अणु
		काष्ठा clk_rate_request req;

		req.rate = rate;
		req.min_rate = min_rate;
		req.max_rate = max_rate;

		clk_core_init_rate_req(core, &req);

		ret = clk_core_determine_round_nolock(core, &req);
		अगर (ret < 0)
			वापस शून्य;

		best_parent_rate = req.best_parent_rate;
		new_rate = req.rate;
		parent = req.best_parent_hw ? req.best_parent_hw->core : शून्य;

		अगर (new_rate < min_rate || new_rate > max_rate)
			वापस शून्य;
	पूर्ण अन्यथा अगर (!parent || !(core->flags & CLK_SET_RATE_PARENT)) अणु
		/* pass-through घड़ी without adjustable parent */
		core->new_rate = core->rate;
		वापस शून्य;
	पूर्ण अन्यथा अणु
		/* pass-through घड़ी with adjustable parent */
		top = clk_calc_new_rates(parent, rate);
		new_rate = parent->new_rate;
		जाओ out;
	पूर्ण

	/* some घड़ीs must be gated to change parent */
	अगर (parent != old_parent &&
	    (core->flags & CLK_SET_PARENT_GATE) && core->prepare_count) अणु
		pr_debug("%s: %s not gated but wants to reparent\n",
			 __func__, core->name);
		वापस शून्य;
	पूर्ण

	/* try finding the new parent index */
	अगर (parent && core->num_parents > 1) अणु
		p_index = clk_fetch_parent_index(core, parent);
		अगर (p_index < 0) अणु
			pr_debug("%s: clk %s can not be parent of clk %s\n",
				 __func__, parent->name, core->name);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर ((core->flags & CLK_SET_RATE_PARENT) && parent &&
	    best_parent_rate != parent->rate)
		top = clk_calc_new_rates(parent, best_parent_rate);

out:
	clk_calc_subtree(core, new_rate, parent, p_index);

	वापस top;
पूर्ण

/*
 * Notअगरy about rate changes in a subtree. Always walk करोwn the whole tree
 * so that in हाल of an error we can walk करोwn the whole tree again and
 * पात the change.
 */
अटल काष्ठा clk_core *clk_propagate_rate_change(काष्ठा clk_core *core,
						  अचिन्हित दीर्घ event)
अणु
	काष्ठा clk_core *child, *पंचांगp_clk, *fail_clk = शून्य;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (core->rate == core->new_rate)
		वापस शून्य;

	अगर (core->notअगरier_count) अणु
		ret = __clk_notअगरy(core, event, core->rate, core->new_rate);
		अगर (ret & NOTIFY_STOP_MASK)
			fail_clk = core;
	पूर्ण

	hlist_क्रम_each_entry(child, &core->children, child_node) अणु
		/* Skip children who will be reparented to another घड़ी */
		अगर (child->new_parent && child->new_parent != core)
			जारी;
		पंचांगp_clk = clk_propagate_rate_change(child, event);
		अगर (पंचांगp_clk)
			fail_clk = पंचांगp_clk;
	पूर्ण

	/* handle the new child who might not be in core->children yet */
	अगर (core->new_child) अणु
		पंचांगp_clk = clk_propagate_rate_change(core->new_child, event);
		अगर (पंचांगp_clk)
			fail_clk = पंचांगp_clk;
	पूर्ण

	वापस fail_clk;
पूर्ण

/*
 * walk करोwn a subtree and set the new rates notअगरying the rate
 * change on the way
 */
अटल व्योम clk_change_rate(काष्ठा clk_core *core)
अणु
	काष्ठा clk_core *child;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित दीर्घ old_rate;
	अचिन्हित दीर्घ best_parent_rate = 0;
	bool skip_set_rate = false;
	काष्ठा clk_core *old_parent;
	काष्ठा clk_core *parent = शून्य;

	old_rate = core->rate;

	अगर (core->new_parent) अणु
		parent = core->new_parent;
		best_parent_rate = core->new_parent->rate;
	पूर्ण अन्यथा अगर (core->parent) अणु
		parent = core->parent;
		best_parent_rate = core->parent->rate;
	पूर्ण

	अगर (clk_pm_runसमय_get(core))
		वापस;

	अगर (core->flags & CLK_SET_RATE_UNGATE) अणु
		clk_core_prepare(core);
		clk_core_enable_lock(core);
	पूर्ण

	अगर (core->new_parent && core->new_parent != core->parent) अणु
		old_parent = __clk_set_parent_beक्रमe(core, core->new_parent);
		trace_clk_set_parent(core, core->new_parent);

		अगर (core->ops->set_rate_and_parent) अणु
			skip_set_rate = true;
			core->ops->set_rate_and_parent(core->hw, core->new_rate,
					best_parent_rate,
					core->new_parent_index);
		पूर्ण अन्यथा अगर (core->ops->set_parent) अणु
			core->ops->set_parent(core->hw, core->new_parent_index);
		पूर्ण

		trace_clk_set_parent_complete(core, core->new_parent);
		__clk_set_parent_after(core, core->new_parent, old_parent);
	पूर्ण

	अगर (core->flags & CLK_OPS_PARENT_ENABLE)
		clk_core_prepare_enable(parent);

	trace_clk_set_rate(core, core->new_rate);

	अगर (!skip_set_rate && core->ops->set_rate)
		core->ops->set_rate(core->hw, core->new_rate, best_parent_rate);

	trace_clk_set_rate_complete(core, core->new_rate);

	core->rate = clk_recalc(core, best_parent_rate);

	अगर (core->flags & CLK_SET_RATE_UNGATE) अणु
		clk_core_disable_lock(core);
		clk_core_unprepare(core);
	पूर्ण

	अगर (core->flags & CLK_OPS_PARENT_ENABLE)
		clk_core_disable_unprepare(parent);

	अगर (core->notअगरier_count && old_rate != core->rate)
		__clk_notअगरy(core, POST_RATE_CHANGE, old_rate, core->rate);

	अगर (core->flags & CLK_RECALC_NEW_RATES)
		(व्योम)clk_calc_new_rates(core, core->new_rate);

	/*
	 * Use safe iteration, as change_rate can actually swap parents
	 * क्रम certain घड़ी types.
	 */
	hlist_क्रम_each_entry_safe(child, पंचांगp, &core->children, child_node) अणु
		/* Skip children who will be reparented to another घड़ी */
		अगर (child->new_parent && child->new_parent != core)
			जारी;
		clk_change_rate(child);
	पूर्ण

	/* handle the new child who might not be in core->children yet */
	अगर (core->new_child)
		clk_change_rate(core->new_child);

	clk_pm_runसमय_put(core);
पूर्ण

अटल अचिन्हित दीर्घ clk_core_req_round_rate_nolock(काष्ठा clk_core *core,
						     अचिन्हित दीर्घ req_rate)
अणु
	पूर्णांक ret, cnt;
	काष्ठा clk_rate_request req;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस 0;

	/* simulate what the rate would be अगर it could be मुक्तly set */
	cnt = clk_core_rate_nuke_protect(core);
	अगर (cnt < 0)
		वापस cnt;

	clk_core_get_boundaries(core, &req.min_rate, &req.max_rate);
	req.rate = req_rate;

	ret = clk_core_round_rate_nolock(core, &req);

	/* restore the protection */
	clk_core_rate_restore_protect(core, cnt);

	वापस ret ? 0 : req.rate;
पूर्ण

अटल पूर्णांक clk_core_set_rate_nolock(काष्ठा clk_core *core,
				    अचिन्हित दीर्घ req_rate)
अणु
	काष्ठा clk_core *top, *fail_clk;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret = 0;

	अगर (!core)
		वापस 0;

	rate = clk_core_req_round_rate_nolock(core, req_rate);

	/* bail early अगर nothing to करो */
	अगर (rate == clk_core_get_rate_nolock(core))
		वापस 0;

	/* fail on a direct rate set of a रक्षित provider */
	अगर (clk_core_rate_is_रक्षित(core))
		वापस -EBUSY;

	/* calculate new rates and get the topmost changed घड़ी */
	top = clk_calc_new_rates(core, req_rate);
	अगर (!top)
		वापस -EINVAL;

	ret = clk_pm_runसमय_get(core);
	अगर (ret)
		वापस ret;

	/* notअगरy that we are about to change rates */
	fail_clk = clk_propagate_rate_change(top, PRE_RATE_CHANGE);
	अगर (fail_clk) अणु
		pr_debug("%s: failed to set %s rate\n", __func__,
				fail_clk->name);
		clk_propagate_rate_change(top, ABORT_RATE_CHANGE);
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* change the rates */
	clk_change_rate(top);

	core->req_rate = req_rate;
err:
	clk_pm_runसमय_put(core);

	वापस ret;
पूर्ण

/**
 * clk_set_rate - specअगरy a new rate क्रम clk
 * @clk: the clk whose rate is being changed
 * @rate: the new rate क्रम clk
 *
 * In the simplest हाल clk_set_rate will only adjust the rate of clk.
 *
 * Setting the CLK_SET_RATE_PARENT flag allows the rate change operation to
 * propagate up to clk's parent; whether or not this happens depends on the
 * outcome of clk's .round_rate implementation.  If *parent_rate is unchanged
 * after calling .round_rate then upstream parent propagation is ignored.  If
 * *parent_rate comes back with a new rate क्रम clk's parent then we propagate
 * up to clk's parent and set its rate.  Upward propagation will जारी
 * until either a clk करोes not support the CLK_SET_RATE_PARENT flag or
 * .round_rate stops requesting changes to clk's parent_rate.
 *
 * Rate changes are accomplished via tree traversal that also recalculates the
 * rates क्रम the घड़ीs and fires off POST_RATE_CHANGE notअगरiers.
 *
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	/* prevent racing with updates to the घड़ी topology */
	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	ret = clk_core_set_rate_nolock(clk->core, rate);

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate);

/**
 * clk_set_rate_exclusive - specअगरy a new rate and get exclusive control
 * @clk: the clk whose rate is being changed
 * @rate: the new rate क्रम clk
 *
 * This is a combination of clk_set_rate() and clk_rate_exclusive_get()
 * within a critical section
 *
 * This can be used initially to ensure that at least 1 consumer is
 * satisfied when several consumers are competing क्रम exclusivity over the
 * same घड़ी provider.
 *
 * The exclusivity is not applied अगर setting the rate failed.
 *
 * Calls to clk_rate_exclusive_get() should be balanced with calls to
 * clk_rate_exclusive_put().
 *
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक clk_set_rate_exclusive(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	/* prevent racing with updates to the घड़ी topology */
	clk_prepare_lock();

	/*
	 * The temporary protection removal is not here, on purpose
	 * This function is meant to be used instead of clk_rate_protect,
	 * so beक्रमe the consumer code path protect the घड़ी provider
	 */

	ret = clk_core_set_rate_nolock(clk->core, rate);
	अगर (!ret) अणु
		clk_core_rate_protect(clk->core);
		clk->exclusive_count++;
	पूर्ण

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate_exclusive);

/**
 * clk_set_rate_range - set a rate range क्रम a घड़ी source
 * @clk: घड़ी source
 * @min: desired minimum घड़ी rate in Hz, inclusive
 * @max: desired maximum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_rate_range(काष्ठा clk *clk, अचिन्हित दीर्घ min, अचिन्हित दीर्घ max)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ old_min, old_max, rate;

	अगर (!clk)
		वापस 0;

	trace_clk_set_rate_range(clk->core, min, max);

	अगर (min > max) अणु
		pr_err("%s: clk %s dev %s con %s: invalid range [%lu, %lu]\n",
		       __func__, clk->core->name, clk->dev_id, clk->con_id,
		       min, max);
		वापस -EINVAL;
	पूर्ण

	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	/* Save the current values in हाल we need to rollback the change */
	old_min = clk->min_rate;
	old_max = clk->max_rate;
	clk->min_rate = min;
	clk->max_rate = max;

	rate = clk_core_get_rate_nolock(clk->core);
	अगर (rate < min || rate > max) अणु
		/*
		 * FIXME:
		 * We are in bit of trouble here, current rate is outside the
		 * the requested range. We are going try to request appropriate
		 * range boundary but there is a catch. It may fail क्रम the
		 * usual reason (घड़ी broken, घड़ी रक्षित, etc) but also
		 * because:
		 * - round_rate() was not favorable and fell on the wrong
		 *   side of the boundary
		 * - the determine_rate() callback करोes not really check क्रम
		 *   this corner हाल when determining the rate
		 */

		अगर (rate < min)
			rate = min;
		अन्यथा
			rate = max;

		ret = clk_core_set_rate_nolock(clk->core, rate);
		अगर (ret) अणु
			/* rollback the changes */
			clk->min_rate = old_min;
			clk->max_rate = old_max;
		पूर्ण
	पूर्ण

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate_range);

/**
 * clk_set_min_rate - set a minimum घड़ी rate क्रम a घड़ी source
 * @clk: घड़ी source
 * @rate: desired minimum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_min_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (!clk)
		वापस 0;

	trace_clk_set_min_rate(clk->core, rate);

	वापस clk_set_rate_range(clk, rate, clk->max_rate);
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_min_rate);

/**
 * clk_set_max_rate - set a maximum घड़ी rate क्रम a घड़ी source
 * @clk: घड़ी source
 * @rate: desired maximum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_max_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (!clk)
		वापस 0;

	trace_clk_set_max_rate(clk->core, rate);

	वापस clk_set_rate_range(clk, clk->min_rate, rate);
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_max_rate);

/**
 * clk_get_parent - वापस the parent of a clk
 * @clk: the clk whose parent माला_लो वापसed
 *
 * Simply वापसs clk->parent.  Returns शून्य अगर clk is शून्य.
 */
काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	काष्ठा clk *parent;

	अगर (!clk)
		वापस शून्य;

	clk_prepare_lock();
	/* TODO: Create a per-user clk and change callers to call clk_put */
	parent = !clk->core->parent ? शून्य : clk->core->parent->hw->clk;
	clk_prepare_unlock();

	वापस parent;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_parent);

अटल काष्ठा clk_core *__clk_init_parent(काष्ठा clk_core *core)
अणु
	u8 index = 0;

	अगर (core->num_parents > 1 && core->ops->get_parent)
		index = core->ops->get_parent(core->hw);

	वापस clk_core_get_parent_by_index(core, index);
पूर्ण

अटल व्योम clk_core_reparent(काष्ठा clk_core *core,
				  काष्ठा clk_core *new_parent)
अणु
	clk_reparent(core, new_parent);
	__clk_recalc_accuracies(core);
	__clk_recalc_rates(core, POST_RATE_CHANGE);
पूर्ण

व्योम clk_hw_reparent(काष्ठा clk_hw *hw, काष्ठा clk_hw *new_parent)
अणु
	अगर (!hw)
		वापस;

	clk_core_reparent(hw->core, !new_parent ? शून्य : new_parent->core);
पूर्ण

/**
 * clk_has_parent - check अगर a घड़ी is a possible parent क्रम another
 * @clk: घड़ी source
 * @parent: parent घड़ी source
 *
 * This function can be used in drivers that need to check that a घड़ी can be
 * the parent of another without actually changing the parent.
 *
 * Returns true अगर @parent is a possible parent क्रम @clk, false otherwise.
 */
bool clk_has_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	काष्ठा clk_core *core, *parent_core;
	पूर्णांक i;

	/* शून्य घड़ीs should be nops, so वापस success अगर either is शून्य. */
	अगर (!clk || !parent)
		वापस true;

	core = clk->core;
	parent_core = parent->core;

	/* Optimize क्रम the हाल where the parent is alपढ़ोy the parent. */
	अगर (core->parent == parent_core)
		वापस true;

	क्रम (i = 0; i < core->num_parents; i++)
		अगर (!म_भेद(core->parents[i].name, parent_core->name))
			वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(clk_has_parent);

अटल पूर्णांक clk_core_set_parent_nolock(काष्ठा clk_core *core,
				      काष्ठा clk_core *parent)
अणु
	पूर्णांक ret = 0;
	पूर्णांक p_index = 0;
	अचिन्हित दीर्घ p_rate = 0;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस 0;

	अगर (core->parent == parent)
		वापस 0;

	/* verअगरy ops क्रम multi-parent clks */
	अगर (core->num_parents > 1 && !core->ops->set_parent)
		वापस -EPERM;

	/* check that we are allowed to re-parent अगर the घड़ी is in use */
	अगर ((core->flags & CLK_SET_PARENT_GATE) && core->prepare_count)
		वापस -EBUSY;

	अगर (clk_core_rate_is_रक्षित(core))
		वापस -EBUSY;

	/* try finding the new parent index */
	अगर (parent) अणु
		p_index = clk_fetch_parent_index(core, parent);
		अगर (p_index < 0) अणु
			pr_debug("%s: clk %s can not be parent of clk %s\n",
					__func__, parent->name, core->name);
			वापस p_index;
		पूर्ण
		p_rate = parent->rate;
	पूर्ण

	ret = clk_pm_runसमय_get(core);
	अगर (ret)
		वापस ret;

	/* propagate PRE_RATE_CHANGE notअगरications */
	ret = __clk_speculate_rates(core, p_rate);

	/* पात अगर a driver objects */
	अगर (ret & NOTIFY_STOP_MASK)
		जाओ runसमय_put;

	/* करो the re-parent */
	ret = __clk_set_parent(core, parent, p_index);

	/* propagate rate an accuracy recalculation accordingly */
	अगर (ret) अणु
		__clk_recalc_rates(core, ABORT_RATE_CHANGE);
	पूर्ण अन्यथा अणु
		__clk_recalc_rates(core, POST_RATE_CHANGE);
		__clk_recalc_accuracies(core);
	पूर्ण

runसमय_put:
	clk_pm_runसमय_put(core);

	वापस ret;
पूर्ण

पूर्णांक clk_hw_set_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent)
अणु
	वापस clk_core_set_parent_nolock(hw->core, parent->core);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_set_parent);

/**
 * clk_set_parent - चयन the parent of a mux clk
 * @clk: the mux clk whose input we are चयनing
 * @parent: the new input to clk
 *
 * Re-parent clk to use parent as its new input source.  If clk is in
 * prepared state, the clk will get enabled क्रम the duration of this call. If
 * that's not acceptable for a specific clk (Eg: the consumer can't handle
 * that, the reparenting is glitchy in hardware, etc), use the
 * CLK_SET_PARENT_GATE flag to allow reparenting only when clk is unprepared.
 *
 * After successfully changing clk's parent clk_set_parent will update the
 * clk topology, sysfs topology and propagate rate recalculation via
 * __clk_recalc_rates.
 *
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	ret = clk_core_set_parent_nolock(clk->core,
					 parent ? parent->core : शून्य);

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_parent);

अटल पूर्णांक clk_core_set_phase_nolock(काष्ठा clk_core *core, पूर्णांक degrees)
अणु
	पूर्णांक ret = -EINVAL;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (!core)
		वापस 0;

	अगर (clk_core_rate_is_रक्षित(core))
		वापस -EBUSY;

	trace_clk_set_phase(core, degrees);

	अगर (core->ops->set_phase) अणु
		ret = core->ops->set_phase(core->hw, degrees);
		अगर (!ret)
			core->phase = degrees;
	पूर्ण

	trace_clk_set_phase_complete(core, degrees);

	वापस ret;
पूर्ण

/**
 * clk_set_phase - adjust the phase shअगरt of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @degrees: number of degrees the संकेत is shअगरted
 *
 * Shअगरts the phase of a घड़ी संकेत by the specअगरied
 * degrees. Returns 0 on success, -EERROR otherwise.
 *
 * This function makes no distinction about the input or reference
 * संकेत that we adjust the घड़ी संकेत phase against. For example
 * phase locked-loop घड़ी संकेत generators we may shअगरt phase with
 * respect to feedback घड़ी संकेत input, but क्रम other हालs the
 * घड़ी phase may be shअगरted with respect to some other, unspecअगरied
 * संकेत.
 *
 * Additionally the concept of phase shअगरt करोes not propagate through
 * the घड़ी tree hierarchy, which sets it apart from घड़ी rates and
 * घड़ी accuracy. A parent घड़ी phase attribute करोes not have an
 * impact on the phase attribute of a child घड़ी.
 */
पूर्णांक clk_set_phase(काष्ठा clk *clk, पूर्णांक degrees)
अणु
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	/* sanity check degrees */
	degrees %= 360;
	अगर (degrees < 0)
		degrees += 360;

	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	ret = clk_core_set_phase_nolock(clk->core, degrees);

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_phase);

अटल पूर्णांक clk_core_get_phase(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&prepare_lock);
	अगर (!core->ops->get_phase)
		वापस 0;

	/* Always try to update cached phase अगर possible */
	ret = core->ops->get_phase(core->hw);
	अगर (ret >= 0)
		core->phase = ret;

	वापस ret;
पूर्ण

/**
 * clk_get_phase - वापस the phase shअगरt of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 *
 * Returns the phase shअगरt of a घड़ी node in degrees, otherwise वापसs
 * -EERROR.
 */
पूर्णांक clk_get_phase(काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	अगर (!clk)
		वापस 0;

	clk_prepare_lock();
	ret = clk_core_get_phase(clk->core);
	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_phase);

अटल व्योम clk_core_reset_duty_cycle_nolock(काष्ठा clk_core *core)
अणु
	/* Assume a शेष value of 50% */
	core->duty.num = 1;
	core->duty.den = 2;
पूर्ण

अटल पूर्णांक clk_core_update_duty_cycle_parent_nolock(काष्ठा clk_core *core);

अटल पूर्णांक clk_core_update_duty_cycle_nolock(काष्ठा clk_core *core)
अणु
	काष्ठा clk_duty *duty = &core->duty;
	पूर्णांक ret = 0;

	अगर (!core->ops->get_duty_cycle)
		वापस clk_core_update_duty_cycle_parent_nolock(core);

	ret = core->ops->get_duty_cycle(core->hw, duty);
	अगर (ret)
		जाओ reset;

	/* Don't trust the घड़ी provider too much */
	अगर (duty->den == 0 || duty->num > duty->den) अणु
		ret = -EINVAL;
		जाओ reset;
	पूर्ण

	वापस 0;

reset:
	clk_core_reset_duty_cycle_nolock(core);
	वापस ret;
पूर्ण

अटल पूर्णांक clk_core_update_duty_cycle_parent_nolock(काष्ठा clk_core *core)
अणु
	पूर्णांक ret = 0;

	अगर (core->parent &&
	    core->flags & CLK_DUTY_CYCLE_PARENT) अणु
		ret = clk_core_update_duty_cycle_nolock(core->parent);
		स_नकल(&core->duty, &core->parent->duty, माप(core->duty));
	पूर्ण अन्यथा अणु
		clk_core_reset_duty_cycle_nolock(core);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_core_set_duty_cycle_parent_nolock(काष्ठा clk_core *core,
						 काष्ठा clk_duty *duty);

अटल पूर्णांक clk_core_set_duty_cycle_nolock(काष्ठा clk_core *core,
					  काष्ठा clk_duty *duty)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&prepare_lock);

	अगर (clk_core_rate_is_रक्षित(core))
		वापस -EBUSY;

	trace_clk_set_duty_cycle(core, duty);

	अगर (!core->ops->set_duty_cycle)
		वापस clk_core_set_duty_cycle_parent_nolock(core, duty);

	ret = core->ops->set_duty_cycle(core->hw, duty);
	अगर (!ret)
		स_नकल(&core->duty, duty, माप(*duty));

	trace_clk_set_duty_cycle_complete(core, duty);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_core_set_duty_cycle_parent_nolock(काष्ठा clk_core *core,
						 काष्ठा clk_duty *duty)
अणु
	पूर्णांक ret = 0;

	अगर (core->parent &&
	    core->flags & (CLK_DUTY_CYCLE_PARENT | CLK_SET_RATE_PARENT)) अणु
		ret = clk_core_set_duty_cycle_nolock(core->parent, duty);
		स_नकल(&core->duty, &core->parent->duty, माप(core->duty));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * clk_set_duty_cycle - adjust the duty cycle ratio of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @num: numerator of the duty cycle ratio to be applied
 * @den: denominator of the duty cycle ratio to be applied
 *
 * Apply the duty cycle ratio अगर the ratio is valid and the घड़ी can
 * perक्रमm this operation
 *
 * Returns (0) on success, a negative त्रुटि_सं otherwise.
 */
पूर्णांक clk_set_duty_cycle(काष्ठा clk *clk, अचिन्हित पूर्णांक num, अचिन्हित पूर्णांक den)
अणु
	पूर्णांक ret;
	काष्ठा clk_duty duty;

	अगर (!clk)
		वापस 0;

	/* sanity check the ratio */
	अगर (den == 0 || num > den)
		वापस -EINVAL;

	duty.num = num;
	duty.den = den;

	clk_prepare_lock();

	अगर (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	ret = clk_core_set_duty_cycle_nolock(clk->core, &duty);

	अगर (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_duty_cycle);

अटल पूर्णांक clk_core_get_scaled_duty_cycle(काष्ठा clk_core *core,
					  अचिन्हित पूर्णांक scale)
अणु
	काष्ठा clk_duty *duty = &core->duty;
	पूर्णांक ret;

	clk_prepare_lock();

	ret = clk_core_update_duty_cycle_nolock(core);
	अगर (!ret)
		ret = mult_frac(scale, duty->num, duty->den);

	clk_prepare_unlock();

	वापस ret;
पूर्ण

/**
 * clk_get_scaled_duty_cycle - वापस the duty cycle ratio of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @scale: scaling factor to be applied to represent the ratio as an पूर्णांकeger
 *
 * Returns the duty cycle ratio of a घड़ी node multiplied by the provided
 * scaling factor, or negative त्रुटि_सं on error.
 */
पूर्णांक clk_get_scaled_duty_cycle(काष्ठा clk *clk, अचिन्हित पूर्णांक scale)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk_core_get_scaled_duty_cycle(clk->core, scale);
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_scaled_duty_cycle);

/**
 * clk_is_match - check अगर two clk's poपूर्णांक to the same hardware घड़ी
 * @p: clk compared against q
 * @q: clk compared against p
 *
 * Returns true अगर the two काष्ठा clk poपूर्णांकers both poपूर्णांक to the same hardware
 * घड़ी node. Put dअगरferently, वापसs true अगर काष्ठा clk *p and काष्ठा clk *q
 * share the same काष्ठा clk_core object.
 *
 * Returns false otherwise. Note that two शून्य clks are treated as matching.
 */
bool clk_is_match(स्थिर काष्ठा clk *p, स्थिर काष्ठा clk *q)
अणु
	/* trivial हाल: identical काष्ठा clk's or both शून्य */
	अगर (p == q)
		वापस true;

	/* true अगर clk->core poपूर्णांकers match. Aव्योम dereferencing garbage */
	अगर (!IS_ERR_OR_शून्य(p) && !IS_ERR_OR_शून्य(q))
		अगर (p->core == q->core)
			वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(clk_is_match);

/***        debugfs support        ***/

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

अटल काष्ठा dentry *rootdir;
अटल पूर्णांक inited = 0;
अटल DEFINE_MUTEX(clk_debug_lock);
अटल HLIST_HEAD(clk_debug_list);

अटल काष्ठा hlist_head *orphan_list[] = अणु
	&clk_orphan_list,
	शून्य,
पूर्ण;

अटल व्योम clk_summary_show_one(काष्ठा seq_file *s, काष्ठा clk_core *c,
				 पूर्णांक level)
अणु
	पूर्णांक phase;

	seq_म_लिखो(s, "%*s%-*s %7d %8d %8d %11lu %10lu ",
		   level * 3 + 1, "",
		   30 - level * 3, c->name,
		   c->enable_count, c->prepare_count, c->protect_count,
		   clk_core_get_rate_recalc(c),
		   clk_core_get_accuracy_recalc(c));

	phase = clk_core_get_phase(c);
	अगर (phase >= 0)
		seq_म_लिखो(s, "%5d", phase);
	अन्यथा
		seq_माला_दो(s, "-----");

	seq_म_लिखो(s, " %6d", clk_core_get_scaled_duty_cycle(c, 100000));

	अगर (c->ops->is_enabled)
		seq_म_लिखो(s, " %9c\n", clk_core_is_enabled(c) ? 'Y' : 'N');
	अन्यथा अगर (!c->ops->enable)
		seq_म_लिखो(s, " %9c\n", 'Y');
	अन्यथा
		seq_म_लिखो(s, " %9c\n", '?');
पूर्ण

अटल व्योम clk_summary_show_subtree(काष्ठा seq_file *s, काष्ठा clk_core *c,
				     पूर्णांक level)
अणु
	काष्ठा clk_core *child;

	clk_summary_show_one(s, c, level);

	hlist_क्रम_each_entry(child, &c->children, child_node)
		clk_summary_show_subtree(s, child, level + 1);
पूर्ण

अटल पूर्णांक clk_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *c;
	काष्ठा hlist_head **lists = (काष्ठा hlist_head **)s->निजी;

	seq_माला_दो(s, "                                 enable  prepare  protect                                duty  hardware\n");
	seq_माला_दो(s, "   clock                          count    count    count        rate   accuracy phase  cycle    enable\n");
	seq_माला_दो(s, "-------------------------------------------------------------------------------------------------------\n");

	clk_prepare_lock();

	क्रम (; *lists; lists++)
		hlist_क्रम_each_entry(c, *lists, child_node)
			clk_summary_show_subtree(s, c, 0);

	clk_prepare_unlock();

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_summary);

अटल व्योम clk_dump_one(काष्ठा seq_file *s, काष्ठा clk_core *c, पूर्णांक level)
अणु
	पूर्णांक phase;
	अचिन्हित दीर्घ min_rate, max_rate;

	clk_core_get_boundaries(c, &min_rate, &max_rate);

	/* This should be JSON क्रमmat, i.e. elements separated with a comma */
	seq_म_लिखो(s, "\"%s\": { ", c->name);
	seq_म_लिखो(s, "\"enable_count\": %d,", c->enable_count);
	seq_म_लिखो(s, "\"prepare_count\": %d,", c->prepare_count);
	seq_म_लिखो(s, "\"protect_count\": %d,", c->protect_count);
	seq_म_लिखो(s, "\"rate\": %lu,", clk_core_get_rate_recalc(c));
	seq_म_लिखो(s, "\"min_rate\": %lu,", min_rate);
	seq_म_लिखो(s, "\"max_rate\": %lu,", max_rate);
	seq_म_लिखो(s, "\"accuracy\": %lu,", clk_core_get_accuracy_recalc(c));
	phase = clk_core_get_phase(c);
	अगर (phase >= 0)
		seq_म_लिखो(s, "\"phase\": %d,", phase);
	seq_म_लिखो(s, "\"duty_cycle\": %u",
		   clk_core_get_scaled_duty_cycle(c, 100000));
पूर्ण

अटल व्योम clk_dump_subtree(काष्ठा seq_file *s, काष्ठा clk_core *c, पूर्णांक level)
अणु
	काष्ठा clk_core *child;

	clk_dump_one(s, c, level);

	hlist_क्रम_each_entry(child, &c->children, child_node) अणु
		seq_अ_दो(s, ',');
		clk_dump_subtree(s, child, level + 1);
	पूर्ण

	seq_अ_दो(s, '}');
पूर्ण

अटल पूर्णांक clk_dump_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *c;
	bool first_node = true;
	काष्ठा hlist_head **lists = (काष्ठा hlist_head **)s->निजी;

	seq_अ_दो(s, '{');
	clk_prepare_lock();

	क्रम (; *lists; lists++) अणु
		hlist_क्रम_each_entry(c, *lists, child_node) अणु
			अगर (!first_node)
				seq_अ_दो(s, ',');
			first_node = false;
			clk_dump_subtree(s, c, 0);
		पूर्ण
	पूर्ण

	clk_prepare_unlock();

	seq_माला_दो(s, "}\n");
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_dump);

#अघोषित CLOCK_ALLOW_WRITE_DEBUGFS
#अगर_घोषित CLOCK_ALLOW_WRITE_DEBUGFS
/*
 * This can be dangerous, thereक्रमe करोn't provide any real compile समय
 * configuration option क्रम this feature.
 * People who want to use this will need to modअगरy the source code directly.
 */
अटल पूर्णांक clk_rate_set(व्योम *data, u64 val)
अणु
	काष्ठा clk_core *core = data;
	पूर्णांक ret;

	clk_prepare_lock();
	ret = clk_core_set_rate_nolock(core, val);
	clk_prepare_unlock();

	वापस ret;
पूर्ण

#घोषणा clk_rate_mode	0644

अटल पूर्णांक clk_prepare_enable_set(व्योम *data, u64 val)
अणु
	काष्ठा clk_core *core = data;
	पूर्णांक ret = 0;

	अगर (val)
		ret = clk_prepare_enable(core->hw->clk);
	अन्यथा
		clk_disable_unprepare(core->hw->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_prepare_enable_get(व्योम *data, u64 *val)
अणु
	काष्ठा clk_core *core = data;

	*val = core->enable_count && core->prepare_count;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(clk_prepare_enable_fops, clk_prepare_enable_get,
			 clk_prepare_enable_set, "%llu\n");

#अन्यथा
#घोषणा clk_rate_set	शून्य
#घोषणा clk_rate_mode	0444
#पूर्ण_अगर

अटल पूर्णांक clk_rate_get(व्योम *data, u64 *val)
अणु
	काष्ठा clk_core *core = data;

	*val = core->rate;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(clk_rate_fops, clk_rate_get, clk_rate_set, "%llu\n");

अटल स्थिर काष्ठा अणु
	अचिन्हित दीर्घ flag;
	स्थिर अक्षर *name;
पूर्ण clk_flags[] = अणु
#घोषणा ENTRY(f) अणु f, #f पूर्ण
	ENTRY(CLK_SET_RATE_GATE),
	ENTRY(CLK_SET_PARENT_GATE),
	ENTRY(CLK_SET_RATE_PARENT),
	ENTRY(CLK_IGNORE_UNUSED),
	ENTRY(CLK_GET_RATE_NOCACHE),
	ENTRY(CLK_SET_RATE_NO_REPARENT),
	ENTRY(CLK_GET_ACCURACY_NOCACHE),
	ENTRY(CLK_RECALC_NEW_RATES),
	ENTRY(CLK_SET_RATE_UNGATE),
	ENTRY(CLK_IS_CRITICAL),
	ENTRY(CLK_OPS_PARENT_ENABLE),
	ENTRY(CLK_DUTY_CYCLE_PARENT),
#अघोषित ENTRY
पूर्ण;

अटल पूर्णांक clk_flags_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;
	अचिन्हित दीर्घ flags = core->flags;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; flags && i < ARRAY_SIZE(clk_flags); i++) अणु
		अगर (flags & clk_flags[i].flag) अणु
			seq_म_लिखो(s, "%s\n", clk_flags[i].name);
			flags &= ~clk_flags[i].flag;
		पूर्ण
	पूर्ण
	अगर (flags) अणु
		/* Unknown flags */
		seq_म_लिखो(s, "0x%lx\n", flags);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_flags);

अटल व्योम possible_parent_show(काष्ठा seq_file *s, काष्ठा clk_core *core,
				 अचिन्हित पूर्णांक i, अक्षर terminator)
अणु
	काष्ठा clk_core *parent;

	/*
	 * Go through the following options to fetch a parent's name.
	 *
	 * 1. Fetch the रेजिस्टरed parent घड़ी and use its name
	 * 2. Use the global (fallback) name अगर specअगरied
	 * 3. Use the local fw_name अगर provided
	 * 4. Fetch parent घड़ी's घड़ी-output-name अगर DT index was set
	 *
	 * This may still fail in some हालs, such as when the parent is
	 * specअगरied directly via a काष्ठा clk_hw poपूर्णांकer, but it isn't
	 * रेजिस्टरed (yet).
	 */
	parent = clk_core_get_parent_by_index(core, i);
	अगर (parent)
		seq_माला_दो(s, parent->name);
	अन्यथा अगर (core->parents[i].name)
		seq_माला_दो(s, core->parents[i].name);
	अन्यथा अगर (core->parents[i].fw_name)
		seq_म_लिखो(s, "<%s>(fw)", core->parents[i].fw_name);
	अन्यथा अगर (core->parents[i].index >= 0)
		seq_माला_दो(s,
			 of_clk_get_parent_name(core->of_node,
						core->parents[i].index));
	अन्यथा
		seq_माला_दो(s, "(missing)");

	seq_अ_दो(s, terminator);
पूर्ण

अटल पूर्णांक possible_parents_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < core->num_parents - 1; i++)
		possible_parent_show(s, core, i, ' ');

	possible_parent_show(s, core, i, '\n');

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(possible_parents);

अटल पूर्णांक current_parent_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;

	अगर (core->parent)
		seq_म_लिखो(s, "%s\n", core->parent->name);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(current_parent);

अटल पूर्णांक clk_duty_cycle_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;
	काष्ठा clk_duty *duty = &core->duty;

	seq_म_लिखो(s, "%u/%u\n", duty->num, duty->den);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_duty_cycle);

अटल पूर्णांक clk_min_rate_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;
	अचिन्हित दीर्घ min_rate, max_rate;

	clk_prepare_lock();
	clk_core_get_boundaries(core, &min_rate, &max_rate);
	clk_prepare_unlock();
	seq_म_लिखो(s, "%lu\n", min_rate);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_min_rate);

अटल पूर्णांक clk_max_rate_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा clk_core *core = s->निजी;
	अचिन्हित दीर्घ min_rate, max_rate;

	clk_prepare_lock();
	clk_core_get_boundaries(core, &min_rate, &max_rate);
	clk_prepare_unlock();
	seq_म_लिखो(s, "%lu\n", max_rate);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_max_rate);

अटल व्योम clk_debug_create_one(काष्ठा clk_core *core, काष्ठा dentry *pdentry)
अणु
	काष्ठा dentry *root;

	अगर (!core || !pdentry)
		वापस;

	root = debugfs_create_dir(core->name, pdentry);
	core->dentry = root;

	debugfs_create_file("clk_rate", clk_rate_mode, root, core,
			    &clk_rate_fops);
	debugfs_create_file("clk_min_rate", 0444, root, core, &clk_min_rate_fops);
	debugfs_create_file("clk_max_rate", 0444, root, core, &clk_max_rate_fops);
	debugfs_create_uदीर्घ("clk_accuracy", 0444, root, &core->accuracy);
	debugfs_create_u32("clk_phase", 0444, root, &core->phase);
	debugfs_create_file("clk_flags", 0444, root, core, &clk_flags_fops);
	debugfs_create_u32("clk_prepare_count", 0444, root, &core->prepare_count);
	debugfs_create_u32("clk_enable_count", 0444, root, &core->enable_count);
	debugfs_create_u32("clk_protect_count", 0444, root, &core->protect_count);
	debugfs_create_u32("clk_notifier_count", 0444, root, &core->notअगरier_count);
	debugfs_create_file("clk_duty_cycle", 0444, root, core,
			    &clk_duty_cycle_fops);
#अगर_घोषित CLOCK_ALLOW_WRITE_DEBUGFS
	debugfs_create_file("clk_prepare_enable", 0644, root, core,
			    &clk_prepare_enable_fops);
#पूर्ण_अगर

	अगर (core->num_parents > 0)
		debugfs_create_file("clk_parent", 0444, root, core,
				    &current_parent_fops);

	अगर (core->num_parents > 1)
		debugfs_create_file("clk_possible_parents", 0444, root, core,
				    &possible_parents_fops);

	अगर (core->ops->debug_init)
		core->ops->debug_init(core->hw, core->dentry);
पूर्ण

/**
 * clk_debug_रेजिस्टर - add a clk node to the debugfs clk directory
 * @core: the clk being added to the debugfs clk directory
 *
 * Dynamically adds a clk to the debugfs clk directory अगर debugfs has been
 * initialized.  Otherwise it bails out early since the debugfs clk directory
 * will be created lazily by clk_debug_init as part of a late_initcall.
 */
अटल व्योम clk_debug_रेजिस्टर(काष्ठा clk_core *core)
अणु
	mutex_lock(&clk_debug_lock);
	hlist_add_head(&core->debug_node, &clk_debug_list);
	अगर (inited)
		clk_debug_create_one(core, rootdir);
	mutex_unlock(&clk_debug_lock);
पूर्ण

 /**
 * clk_debug_unरेजिस्टर - हटाओ a clk node from the debugfs clk directory
 * @core: the clk being हटाओd from the debugfs clk directory
 *
 * Dynamically हटाओs a clk and all its child nodes from the
 * debugfs clk directory अगर clk->dentry poपूर्णांकs to debugfs created by
 * clk_debug_रेजिस्टर in __clk_core_init.
 */
अटल व्योम clk_debug_unरेजिस्टर(काष्ठा clk_core *core)
अणु
	mutex_lock(&clk_debug_lock);
	hlist_del_init(&core->debug_node);
	debugfs_हटाओ_recursive(core->dentry);
	core->dentry = शून्य;
	mutex_unlock(&clk_debug_lock);
पूर्ण

/**
 * clk_debug_init - lazily populate the debugfs clk directory
 *
 * clks are often initialized very early during boot beक्रमe memory can be
 * dynamically allocated and well beक्रमe debugfs is setup. This function
 * populates the debugfs clk directory once at boot-समय when we know that
 * debugfs is setup. It should only be called once at boot-समय, all other clks
 * added dynamically will be करोne so with clk_debug_रेजिस्टर.
 */
अटल पूर्णांक __init clk_debug_init(व्योम)
अणु
	काष्ठा clk_core *core;

	rootdir = debugfs_create_dir("clk", शून्य);

	debugfs_create_file("clk_summary", 0444, rootdir, &all_lists,
			    &clk_summary_fops);
	debugfs_create_file("clk_dump", 0444, rootdir, &all_lists,
			    &clk_dump_fops);
	debugfs_create_file("clk_orphan_summary", 0444, rootdir, &orphan_list,
			    &clk_summary_fops);
	debugfs_create_file("clk_orphan_dump", 0444, rootdir, &orphan_list,
			    &clk_dump_fops);

	mutex_lock(&clk_debug_lock);
	hlist_क्रम_each_entry(core, &clk_debug_list, debug_node)
		clk_debug_create_one(core, rootdir);

	inited = 1;
	mutex_unlock(&clk_debug_lock);

	वापस 0;
पूर्ण
late_initcall(clk_debug_init);
#अन्यथा
अटल अंतरभूत व्योम clk_debug_रेजिस्टर(काष्ठा clk_core *core) अणु पूर्ण
अटल अंतरभूत व्योम clk_debug_unरेजिस्टर(काष्ठा clk_core *core)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम clk_core_reparent_orphans_nolock(व्योम)
अणु
	काष्ठा clk_core *orphan;
	काष्ठा hlist_node *पंचांगp2;

	/*
	 * walk the list of orphan घड़ीs and reparent any that newly finds a
	 * parent.
	 */
	hlist_क्रम_each_entry_safe(orphan, पंचांगp2, &clk_orphan_list, child_node) अणु
		काष्ठा clk_core *parent = __clk_init_parent(orphan);

		/*
		 * We need to use __clk_set_parent_beक्रमe() and _after() to
		 * to properly migrate any prepare/enable count of the orphan
		 * घड़ी. This is important क्रम CLK_IS_CRITICAL घड़ीs, which
		 * are enabled during init but might not have a parent yet.
		 */
		अगर (parent) अणु
			/* update the clk tree topology */
			__clk_set_parent_beक्रमe(orphan, parent);
			__clk_set_parent_after(orphan, parent, शून्य);
			__clk_recalc_accuracies(orphan);
			__clk_recalc_rates(orphan, 0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __clk_core_init - initialize the data काष्ठाures in a काष्ठा clk_core
 * @core:	clk_core being initialized
 *
 * Initializes the lists in काष्ठा clk_core, queries the hardware क्रम the
 * parent and rate and sets them both.
 */
अटल पूर्णांक __clk_core_init(काष्ठा clk_core *core)
अणु
	पूर्णांक ret;
	काष्ठा clk_core *parent;
	अचिन्हित दीर्घ rate;
	पूर्णांक phase;

	अगर (!core)
		वापस -EINVAL;

	clk_prepare_lock();

	ret = clk_pm_runसमय_get(core);
	अगर (ret)
		जाओ unlock;

	/* check to see अगर a घड़ी with this name is alपढ़ोy रेजिस्टरed */
	अगर (clk_core_lookup(core->name)) अणु
		pr_debug("%s: clk %s already initialized\n",
				__func__, core->name);
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	/* check that clk_ops are sane.  See Documentation/driver-api/clk.rst */
	अगर (core->ops->set_rate &&
	    !((core->ops->round_rate || core->ops->determine_rate) &&
	      core->ops->recalc_rate)) अणु
		pr_err("%s: %s must implement .round_rate or .determine_rate in addition to .recalc_rate\n",
		       __func__, core->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (core->ops->set_parent && !core->ops->get_parent) अणु
		pr_err("%s: %s must implement .get_parent & .set_parent\n",
		       __func__, core->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (core->num_parents > 1 && !core->ops->get_parent) अणु
		pr_err("%s: %s must implement .get_parent as it has multi parents\n",
		       __func__, core->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (core->ops->set_rate_and_parent &&
			!(core->ops->set_parent && core->ops->set_rate)) अणु
		pr_err("%s: %s must implement .set_parent & .set_rate\n",
				__func__, core->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * optional platक्रमm-specअगरic magic
	 *
	 * The .init callback is not used by any of the basic घड़ी types, but
	 * exists क्रम weird hardware that must perक्रमm initialization magic क्रम
	 * CCF to get an accurate view of घड़ी क्रम any other callbacks. It may
	 * also be used needs to perक्रमm dynamic allocations. Such allocation
	 * must be मुक्तd in the terminate() callback.
	 * This callback shall not be used to initialize the parameters state,
	 * such as rate, parent, etc ...
	 *
	 * If it exist, this callback should called beक्रमe any other callback of
	 * the घड़ी
	 */
	अगर (core->ops->init) अणु
		ret = core->ops->init(core->hw);
		अगर (ret)
			जाओ out;
	पूर्ण

	parent = core->parent = __clk_init_parent(core);

	/*
	 * Populate core->parent अगर parent has alपढ़ोy been clk_core_init'd. If
	 * parent has not yet been clk_core_init'd then place clk in the orphan
	 * list.  If clk करोesn't have any parents then place it in the root
	 * clk list.
	 *
	 * Every समय a new clk is clk_init'd then we walk the list of orphan
	 * घड़ीs and re-parent any that are children of the घड़ी currently
	 * being clk_init'd.
	 */
	अगर (parent) अणु
		hlist_add_head(&core->child_node, &parent->children);
		core->orphan = parent->orphan;
	पूर्ण अन्यथा अगर (!core->num_parents) अणु
		hlist_add_head(&core->child_node, &clk_root_list);
		core->orphan = false;
	पूर्ण अन्यथा अणु
		hlist_add_head(&core->child_node, &clk_orphan_list);
		core->orphan = true;
	पूर्ण

	/*
	 * Set clk's accuracy.  The preferred method is to use
	 * .recalc_accuracy. For simple घड़ीs and lazy developers the शेष
	 * fallback is to use the parent's accuracy.  If a clock doesn't have a
	 * parent (or is orphaned) then accuracy is set to zero (perfect
	 * घड़ी).
	 */
	अगर (core->ops->recalc_accuracy)
		core->accuracy = core->ops->recalc_accuracy(core->hw,
					clk_core_get_accuracy_no_lock(parent));
	अन्यथा अगर (parent)
		core->accuracy = parent->accuracy;
	अन्यथा
		core->accuracy = 0;

	/*
	 * Set clk's phase by clk_core_get_phase() caching the phase.
	 * Since a phase is by definition relative to its parent, just
	 * query the current घड़ी phase, or just assume it's in phase.
	 */
	phase = clk_core_get_phase(core);
	अगर (phase < 0) अणु
		ret = phase;
		pr_warn("%s: Failed to get phase for clk '%s'\n", __func__,
			core->name);
		जाओ out;
	पूर्ण

	/*
	 * Set clk's duty cycle.
	 */
	clk_core_update_duty_cycle_nolock(core);

	/*
	 * Set clk's rate.  The preferred method is to use .recalc_rate.  For
	 * simple घड़ीs and lazy developers the शेष fallback is to use the
	 * parent's rate.  If a clock doesn't have a parent (or is orphaned)
	 * then rate is set to zero.
	 */
	अगर (core->ops->recalc_rate)
		rate = core->ops->recalc_rate(core->hw,
				clk_core_get_rate_nolock(parent));
	अन्यथा अगर (parent)
		rate = parent->rate;
	अन्यथा
		rate = 0;
	core->rate = core->req_rate = rate;

	/*
	 * Enable CLK_IS_CRITICAL घड़ीs so newly added critical घड़ीs
	 * करोn't get accidentally disabled when walking the orphan tree and
	 * reparenting घड़ीs
	 */
	अगर (core->flags & CLK_IS_CRITICAL) अणु
		ret = clk_core_prepare(core);
		अगर (ret) अणु
			pr_warn("%s: critical clk '%s' failed to prepare\n",
			       __func__, core->name);
			जाओ out;
		पूर्ण

		ret = clk_core_enable_lock(core);
		अगर (ret) अणु
			pr_warn("%s: critical clk '%s' failed to enable\n",
			       __func__, core->name);
			clk_core_unprepare(core);
			जाओ out;
		पूर्ण
	पूर्ण

	clk_core_reparent_orphans_nolock();


	kref_init(&core->ref);
out:
	clk_pm_runसमय_put(core);
unlock:
	अगर (ret)
		hlist_del_init(&core->child_node);

	clk_prepare_unlock();

	अगर (!ret)
		clk_debug_रेजिस्टर(core);

	वापस ret;
पूर्ण

/**
 * clk_core_link_consumer - Add a clk consumer to the list of consumers in a clk_core
 * @core: clk to add consumer to
 * @clk: consumer to link to a clk
 */
अटल व्योम clk_core_link_consumer(काष्ठा clk_core *core, काष्ठा clk *clk)
अणु
	clk_prepare_lock();
	hlist_add_head(&clk->clks_node, &core->clks);
	clk_prepare_unlock();
पूर्ण

/**
 * clk_core_unlink_consumer - Remove a clk consumer from the list of consumers in a clk_core
 * @clk: consumer to unlink
 */
अटल व्योम clk_core_unlink_consumer(काष्ठा clk *clk)
अणु
	lockdep_निश्चित_held(&prepare_lock);
	hlist_del(&clk->clks_node);
पूर्ण

/**
 * alloc_clk - Allocate a clk consumer, but leave it unlinked to the clk_core
 * @core: clk to allocate a consumer क्रम
 * @dev_id: string describing device name
 * @con_id: connection ID string on device
 *
 * Returns: clk consumer left unlinked from the consumer list
 */
अटल काष्ठा clk *alloc_clk(काष्ठा clk_core *core, स्थिर अक्षर *dev_id,
			     स्थिर अक्षर *con_id)
अणु
	काष्ठा clk *clk;

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->core = core;
	clk->dev_id = dev_id;
	clk->con_id = kstrdup_स्थिर(con_id, GFP_KERNEL);
	clk->max_rate = अच_दीर्घ_उच्च;

	वापस clk;
पूर्ण

/**
 * मुक्त_clk - Free a clk consumer
 * @clk: clk consumer to मुक्त
 *
 * Note, this assumes the clk has been unlinked from the clk_core consumer
 * list.
 */
अटल व्योम मुक्त_clk(काष्ठा clk *clk)
अणु
	kमुक्त_स्थिर(clk->con_id);
	kमुक्त(clk);
पूर्ण

/**
 * clk_hw_create_clk: Allocate and link a clk consumer to a clk_core given
 * a clk_hw
 * @dev: clk consumer device
 * @hw: clk_hw associated with the clk being consumed
 * @dev_id: string describing device name
 * @con_id: connection ID string on device
 *
 * This is the मुख्य function used to create a clk poपूर्णांकer क्रम use by clk
 * consumers. It connects a consumer to the clk_core and clk_hw काष्ठाures
 * used by the framework and clk provider respectively.
 */
काष्ठा clk *clk_hw_create_clk(काष्ठा device *dev, काष्ठा clk_hw *hw,
			      स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_core *core;

	/* This is to allow this function to be chained to others */
	अगर (IS_ERR_OR_शून्य(hw))
		वापस ERR_CAST(hw);

	core = hw->core;
	clk = alloc_clk(core, dev_id, con_id);
	अगर (IS_ERR(clk))
		वापस clk;
	clk->dev = dev;

	अगर (!try_module_get(core->owner)) अणु
		मुक्त_clk(clk);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	kref_get(&core->ref);
	clk_core_link_consumer(core, clk);

	वापस clk;
पूर्ण

/**
 * clk_hw_get_clk - get clk consumer given an clk_hw
 * @hw: clk_hw associated with the clk being consumed
 * @con_id: connection ID string on device
 *
 * Returns: new clk consumer
 * This is the function to be used by providers which need
 * to get a consumer clk and act on the घड़ी element
 * Calls to this function must be balanced with calls clk_put()
 */
काष्ठा clk *clk_hw_get_clk(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id)
अणु
	काष्ठा device *dev = hw->core->dev;

	वापस clk_hw_create_clk(dev, hw, dev_name(dev), con_id);
पूर्ण
EXPORT_SYMBOL(clk_hw_get_clk);

अटल पूर्णांक clk_cpy_name(स्थिर अक्षर **dst_p, स्थिर अक्षर *src, bool must_exist)
अणु
	स्थिर अक्षर *dst;

	अगर (!src) अणु
		अगर (must_exist)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	*dst_p = dst = kstrdup_स्थिर(src, GFP_KERNEL);
	अगर (!dst)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_core_populate_parent_map(काष्ठा clk_core *core,
					स्थिर काष्ठा clk_init_data *init)
अणु
	u8 num_parents = init->num_parents;
	स्थिर अक्षर * स्थिर *parent_names = init->parent_names;
	स्थिर काष्ठा clk_hw **parent_hws = init->parent_hws;
	स्थिर काष्ठा clk_parent_data *parent_data = init->parent_data;
	पूर्णांक i, ret = 0;
	काष्ठा clk_parent_map *parents, *parent;

	अगर (!num_parents)
		वापस 0;

	/*
	 * Aव्योम unnecessary string look-ups of clk_core's possible parents by
	 * having a cache of names/clk_hw poपूर्णांकers to clk_core poपूर्णांकers.
	 */
	parents = kसुस्मृति(num_parents, माप(*parents), GFP_KERNEL);
	core->parents = parents;
	अगर (!parents)
		वापस -ENOMEM;

	/* Copy everything over because it might be __initdata */
	क्रम (i = 0, parent = parents; i < num_parents; i++, parent++) अणु
		parent->index = -1;
		अगर (parent_names) अणु
			/* throw a WARN अगर any entries are शून्य */
			WARN(!parent_names[i],
				"%s: invalid NULL in %s's .parent_names\n",
				__func__, core->name);
			ret = clk_cpy_name(&parent->name, parent_names[i],
					   true);
		पूर्ण अन्यथा अगर (parent_data) अणु
			parent->hw = parent_data[i].hw;
			parent->index = parent_data[i].index;
			ret = clk_cpy_name(&parent->fw_name,
					   parent_data[i].fw_name, false);
			अगर (!ret)
				ret = clk_cpy_name(&parent->name,
						   parent_data[i].name,
						   false);
		पूर्ण अन्यथा अगर (parent_hws) अणु
			parent->hw = parent_hws[i];
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			WARN(1, "Must specify parents if num_parents > 0\n");
		पूर्ण

		अगर (ret) अणु
			करो अणु
				kमुक्त_स्थिर(parents[i].name);
				kमुक्त_स्थिर(parents[i].fw_name);
			पूर्ण जबतक (--i >= 0);
			kमुक्त(parents);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clk_core_मुक्त_parent_map(काष्ठा clk_core *core)
अणु
	पूर्णांक i = core->num_parents;

	अगर (!core->num_parents)
		वापस;

	जबतक (--i >= 0) अणु
		kमुक्त_स्थिर(core->parents[i].name);
		kमुक्त_स्थिर(core->parents[i].fw_name);
	पूर्ण

	kमुक्त(core->parents);
पूर्ण

अटल काष्ठा clk *
__clk_रेजिस्टर(काष्ठा device *dev, काष्ठा device_node *np, काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_core *core;
	स्थिर काष्ठा clk_init_data *init = hw->init;

	/*
	 * The init data is not supposed to be used outside of registration path.
	 * Set it to शून्य so that provider drivers can't use it either and so that
	 * we catch use of hw->init early on in the core.
	 */
	hw->init = शून्य;

	core = kzalloc(माप(*core), GFP_KERNEL);
	अगर (!core) अणु
		ret = -ENOMEM;
		जाओ fail_out;
	पूर्ण

	core->name = kstrdup_स्थिर(init->name, GFP_KERNEL);
	अगर (!core->name) अणु
		ret = -ENOMEM;
		जाओ fail_name;
	पूर्ण

	अगर (WARN_ON(!init->ops)) अणु
		ret = -EINVAL;
		जाओ fail_ops;
	पूर्ण
	core->ops = init->ops;

	अगर (dev && pm_runसमय_enabled(dev))
		core->rpm_enabled = true;
	core->dev = dev;
	core->of_node = np;
	अगर (dev && dev->driver)
		core->owner = dev->driver->owner;
	core->hw = hw;
	core->flags = init->flags;
	core->num_parents = init->num_parents;
	core->min_rate = 0;
	core->max_rate = अच_दीर्घ_उच्च;
	hw->core = core;

	ret = clk_core_populate_parent_map(core, init);
	अगर (ret)
		जाओ fail_parents;

	INIT_HLIST_HEAD(&core->clks);

	/*
	 * Don't call clk_hw_create_clk() here because that would pin the
	 * provider module to itself and prevent it from ever being हटाओd.
	 */
	hw->clk = alloc_clk(core, शून्य, शून्य);
	अगर (IS_ERR(hw->clk)) अणु
		ret = PTR_ERR(hw->clk);
		जाओ fail_create_clk;
	पूर्ण

	clk_core_link_consumer(hw->core, hw->clk);

	ret = __clk_core_init(core);
	अगर (!ret)
		वापस hw->clk;

	clk_prepare_lock();
	clk_core_unlink_consumer(hw->clk);
	clk_prepare_unlock();

	मुक्त_clk(hw->clk);
	hw->clk = शून्य;

fail_create_clk:
	clk_core_मुक्त_parent_map(core);
fail_parents:
fail_ops:
	kमुक्त_स्थिर(core->name);
fail_name:
	kमुक्त(core);
fail_out:
	वापस ERR_PTR(ret);
पूर्ण

/**
 * dev_or_parent_of_node() - Get device node of @dev or @dev's parent
 * @dev: Device to get device node of
 *
 * Return: device node poपूर्णांकer of @dev, or the device node poपूर्णांकer of
 * @dev->parent अगर dev करोesn't have a device node, or शून्य अगर neither
 * @dev or @dev->parent have a device node.
 */
अटल काष्ठा device_node *dev_or_parent_of_node(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;

	अगर (!dev)
		वापस शून्य;

	np = dev_of_node(dev);
	अगर (!np)
		np = dev_of_node(dev->parent);

	वापस np;
पूर्ण

/**
 * clk_रेजिस्टर - allocate a new घड़ी, रेजिस्टर it and वापस an opaque cookie
 * @dev: device that is रेजिस्टरing this घड़ी
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * clk_रेजिस्टर is the *deprecated* पूर्णांकerface क्रम populating the घड़ी tree with
 * new घड़ी nodes. Use clk_hw_रेजिस्टर() instead.
 *
 * Returns: a poपूर्णांकer to the newly allocated काष्ठा clk which
 * cannot be dereferenced by driver code but may be used in conjunction with the
 * rest of the घड़ी API.  In the event of an error clk_रेजिस्टर will वापस an
 * error code; drivers must test क्रम an error code after calling clk_रेजिस्टर.
 */
काष्ठा clk *clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw)
अणु
	वापस __clk_रेजिस्टर(dev, dev_or_parent_of_node(dev), hw);
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर);

/**
 * clk_hw_रेजिस्टर - रेजिस्टर a clk_hw and वापस an error code
 * @dev: device that is रेजिस्टरing this घड़ी
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * clk_hw_रेजिस्टर is the primary पूर्णांकerface क्रम populating the घड़ी tree with
 * new घड़ी nodes. It वापसs an पूर्णांकeger equal to zero indicating success or
 * less than zero indicating failure. Drivers must test क्रम an error code after
 * calling clk_hw_रेजिस्टर().
 */
पूर्णांक clk_hw_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw)
अणु
	वापस PTR_ERR_OR_ZERO(__clk_रेजिस्टर(dev, dev_or_parent_of_node(dev),
			       hw));
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_रेजिस्टर);

/*
 * of_clk_hw_रेजिस्टर - रेजिस्टर a clk_hw and वापस an error code
 * @node: device_node of device that is रेजिस्टरing this घड़ी
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * of_clk_hw_रेजिस्टर() is the primary पूर्णांकerface क्रम populating the घड़ी tree
 * with new घड़ी nodes when a काष्ठा device is not available, but a काष्ठा
 * device_node is. It वापसs an पूर्णांकeger equal to zero indicating success or
 * less than zero indicating failure. Drivers must test क्रम an error code after
 * calling of_clk_hw_रेजिस्टर().
 */
पूर्णांक of_clk_hw_रेजिस्टर(काष्ठा device_node *node, काष्ठा clk_hw *hw)
अणु
	वापस PTR_ERR_OR_ZERO(__clk_रेजिस्टर(शून्य, node, hw));
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_hw_रेजिस्टर);

/* Free memory allocated क्रम a घड़ी. */
अटल व्योम __clk_release(काष्ठा kref *ref)
अणु
	काष्ठा clk_core *core = container_of(ref, काष्ठा clk_core, ref);

	lockdep_निश्चित_held(&prepare_lock);

	clk_core_मुक्त_parent_map(core);
	kमुक्त_स्थिर(core->name);
	kमुक्त(core);
पूर्ण

/*
 * Empty clk_ops क्रम unरेजिस्टरed घड़ीs. These are used temporarily
 * after clk_unरेजिस्टर() was called on a घड़ी and until last घड़ी
 * consumer calls clk_put() and the काष्ठा clk object is मुक्तd.
 */
अटल पूर्णांक clk_nodrv_prepare_enable(काष्ठा clk_hw *hw)
अणु
	वापस -ENXIO;
पूर्ण

अटल व्योम clk_nodrv_disable_unprepare(काष्ठा clk_hw *hw)
अणु
	WARN_ON_ONCE(1);
पूर्ण

अटल पूर्णांक clk_nodrv_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक clk_nodrv_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	वापस -ENXIO;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_nodrv_ops = अणु
	.enable		= clk_nodrv_prepare_enable,
	.disable	= clk_nodrv_disable_unprepare,
	.prepare	= clk_nodrv_prepare_enable,
	.unprepare	= clk_nodrv_disable_unprepare,
	.set_rate	= clk_nodrv_set_rate,
	.set_parent	= clk_nodrv_set_parent,
पूर्ण;

अटल व्योम clk_core_evict_parent_cache_subtree(काष्ठा clk_core *root,
						काष्ठा clk_core *target)
अणु
	पूर्णांक i;
	काष्ठा clk_core *child;

	क्रम (i = 0; i < root->num_parents; i++)
		अगर (root->parents[i].core == target)
			root->parents[i].core = शून्य;

	hlist_क्रम_each_entry(child, &root->children, child_node)
		clk_core_evict_parent_cache_subtree(child, target);
पूर्ण

/* Remove this clk from all parent caches */
अटल व्योम clk_core_evict_parent_cache(काष्ठा clk_core *core)
अणु
	काष्ठा hlist_head **lists;
	काष्ठा clk_core *root;

	lockdep_निश्चित_held(&prepare_lock);

	क्रम (lists = all_lists; *lists; lists++)
		hlist_क्रम_each_entry(root, *lists, child_node)
			clk_core_evict_parent_cache_subtree(root, core);

पूर्ण

/**
 * clk_unरेजिस्टर - unरेजिस्टर a currently रेजिस्टरed घड़ी
 * @clk: घड़ी to unरेजिस्टर
 */
व्योम clk_unरेजिस्टर(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा clk_ops *ops;

	अगर (!clk || WARN_ON_ONCE(IS_ERR(clk)))
		वापस;

	clk_debug_unरेजिस्टर(clk->core);

	clk_prepare_lock();

	ops = clk->core->ops;
	अगर (ops == &clk_nodrv_ops) अणु
		pr_err("%s: unregistered clock: %s\n", __func__,
		       clk->core->name);
		जाओ unlock;
	पूर्ण
	/*
	 * Assign empty घड़ी ops क्रम consumers that might still hold
	 * a reference to this घड़ी.
	 */
	flags = clk_enable_lock();
	clk->core->ops = &clk_nodrv_ops;
	clk_enable_unlock(flags);

	अगर (ops->terminate)
		ops->terminate(clk->core->hw);

	अगर (!hlist_empty(&clk->core->children)) अणु
		काष्ठा clk_core *child;
		काष्ठा hlist_node *t;

		/* Reparent all children to the orphan list. */
		hlist_क्रम_each_entry_safe(child, t, &clk->core->children,
					  child_node)
			clk_core_set_parent_nolock(child, शून्य);
	पूर्ण

	clk_core_evict_parent_cache(clk->core);

	hlist_del_init(&clk->core->child_node);

	अगर (clk->core->prepare_count)
		pr_warn("%s: unregistering prepared clock: %s\n",
					__func__, clk->core->name);

	अगर (clk->core->protect_count)
		pr_warn("%s: unregistering protected clock: %s\n",
					__func__, clk->core->name);

	kref_put(&clk->core->ref, __clk_release);
	मुक्त_clk(clk);
unlock:
	clk_prepare_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर);

/**
 * clk_hw_unरेजिस्टर - unरेजिस्टर a currently रेजिस्टरed clk_hw
 * @hw: hardware-specअगरic घड़ी data to unरेजिस्टर
 */
व्योम clk_hw_unरेजिस्टर(काष्ठा clk_hw *hw)
अणु
	clk_unरेजिस्टर(hw->clk);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर);

अटल व्योम devm_clk_unरेजिस्टर_cb(काष्ठा device *dev, व्योम *res)
अणु
	clk_unरेजिस्टर(*(काष्ठा clk **)res);
पूर्ण

अटल व्योम devm_clk_hw_unरेजिस्टर_cb(काष्ठा device *dev, व्योम *res)
अणु
	clk_hw_unरेजिस्टर(*(काष्ठा clk_hw **)res);
पूर्ण

/**
 * devm_clk_रेजिस्टर - resource managed clk_रेजिस्टर()
 * @dev: device that is रेजिस्टरing this घड़ी
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * Managed clk_रेजिस्टर(). This function is *deprecated*, use devm_clk_hw_रेजिस्टर() instead.
 *
 * Clocks वापसed from this function are स्वतःmatically clk_unरेजिस्टर()ed on
 * driver detach. See clk_रेजिस्टर() क्रम more inक्रमmation.
 */
काष्ठा clk *devm_clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **clkp;

	clkp = devres_alloc(devm_clk_unरेजिस्टर_cb, माप(*clkp), GFP_KERNEL);
	अगर (!clkp)
		वापस ERR_PTR(-ENOMEM);

	clk = clk_रेजिस्टर(dev, hw);
	अगर (!IS_ERR(clk)) अणु
		*clkp = clk;
		devres_add(dev, clkp);
	पूर्ण अन्यथा अणु
		devres_मुक्त(clkp);
	पूर्ण

	वापस clk;
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_रेजिस्टर);

/**
 * devm_clk_hw_रेजिस्टर - resource managed clk_hw_रेजिस्टर()
 * @dev: device that is रेजिस्टरing this घड़ी
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * Managed clk_hw_रेजिस्टर(). Clocks रेजिस्टरed by this function are
 * स्वतःmatically clk_hw_unरेजिस्टर()ed on driver detach. See clk_hw_रेजिस्टर()
 * क्रम more inक्रमmation.
 */
पूर्णांक devm_clk_hw_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw **hwp;
	पूर्णांक ret;

	hwp = devres_alloc(devm_clk_hw_unरेजिस्टर_cb, माप(*hwp), GFP_KERNEL);
	अगर (!hwp)
		वापस -ENOMEM;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (!ret) अणु
		*hwp = hw;
		devres_add(dev, hwp);
	पूर्ण अन्यथा अणु
		devres_मुक्त(hwp);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_hw_रेजिस्टर);

अटल पूर्णांक devm_clk_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा clk *c = res;
	अगर (WARN_ON(!c))
		वापस 0;
	वापस c == data;
पूर्ण

अटल पूर्णांक devm_clk_hw_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा clk_hw *hw = res;

	अगर (WARN_ON(!hw))
		वापस 0;
	वापस hw == data;
पूर्ण

/**
 * devm_clk_unरेजिस्टर - resource managed clk_unरेजिस्टर()
 * @dev: device that is unरेजिस्टरing the घड़ी data
 * @clk: घड़ी to unरेजिस्टर
 *
 * Deallocate a घड़ी allocated with devm_clk_रेजिस्टर(). Normally
 * this function will not need to be called and the resource management
 * code will ensure that the resource is मुक्तd.
 */
व्योम devm_clk_unरेजिस्टर(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	WARN_ON(devres_release(dev, devm_clk_unरेजिस्टर_cb, devm_clk_match, clk));
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_unरेजिस्टर);

/**
 * devm_clk_hw_unरेजिस्टर - resource managed clk_hw_unरेजिस्टर()
 * @dev: device that is unरेजिस्टरing the hardware-specअगरic घड़ी data
 * @hw: link to hardware-specअगरic घड़ी data
 *
 * Unरेजिस्टर a clk_hw रेजिस्टरed with devm_clk_hw_रेजिस्टर(). Normally
 * this function will not need to be called and the resource management
 * code will ensure that the resource is मुक्तd.
 */
व्योम devm_clk_hw_unरेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw)
अणु
	WARN_ON(devres_release(dev, devm_clk_hw_unरेजिस्टर_cb, devm_clk_hw_match,
				hw));
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_hw_unरेजिस्टर);

अटल व्योम devm_clk_release(काष्ठा device *dev, व्योम *res)
अणु
	clk_put(*(काष्ठा clk **)res);
पूर्ण

/**
 * devm_clk_hw_get_clk - resource managed clk_hw_get_clk()
 * @dev: device that is रेजिस्टरing this घड़ी
 * @hw: clk_hw associated with the clk being consumed
 * @con_id: connection ID string on device
 *
 * Managed clk_hw_get_clk(). Clocks got with this function are
 * स्वतःmatically clk_put() on driver detach. See clk_put()
 * क्रम more inक्रमmation.
 */
काष्ठा clk *devm_clk_hw_get_clk(काष्ठा device *dev, काष्ठा clk_hw *hw,
				स्थिर अक्षर *con_id)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **clkp;

	/* This should not happen because it would mean we have drivers
	 * passing around clk_hw poपूर्णांकers instead of having the caller use
	 * proper clk_get() style APIs
	 */
	WARN_ON_ONCE(dev != hw->core->dev);

	clkp = devres_alloc(devm_clk_release, माप(*clkp), GFP_KERNEL);
	अगर (!clkp)
		वापस ERR_PTR(-ENOMEM);

	clk = clk_hw_get_clk(hw, con_id);
	अगर (!IS_ERR(clk)) अणु
		*clkp = clk;
		devres_add(dev, clkp);
	पूर्ण अन्यथा अणु
		devres_मुक्त(clkp);
	पूर्ण

	वापस clk;
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_hw_get_clk);

/*
 * clkdev helpers
 */

व्योम __clk_put(काष्ठा clk *clk)
अणु
	काष्ठा module *owner;

	अगर (!clk || WARN_ON_ONCE(IS_ERR(clk)))
		वापस;

	clk_prepare_lock();

	/*
	 * Beक्रमe calling clk_put, all calls to clk_rate_exclusive_get() from a
	 * given user should be balanced with calls to clk_rate_exclusive_put()
	 * and by that same consumer
	 */
	अगर (WARN_ON(clk->exclusive_count)) अणु
		/* We voiced our concern, let's sanitize the situation */
		clk->core->protect_count -= (clk->exclusive_count - 1);
		clk_core_rate_unprotect(clk->core);
		clk->exclusive_count = 0;
	पूर्ण

	hlist_del(&clk->clks_node);
	अगर (clk->min_rate > clk->core->req_rate ||
	    clk->max_rate < clk->core->req_rate)
		clk_core_set_rate_nolock(clk->core, clk->core->req_rate);

	owner = clk->core->owner;
	kref_put(&clk->core->ref, __clk_release);

	clk_prepare_unlock();

	module_put(owner);

	मुक्त_clk(clk);
पूर्ण

/***        clk rate change notअगरiers        ***/

/**
 * clk_notअगरier_रेजिस्टर - add a clk rate change notअगरier
 * @clk: काष्ठा clk * to watch
 * @nb: काष्ठा notअगरier_block * with callback info
 *
 * Request notअगरication when clk's rate changes.  This uses an SRCU
 * notअगरier because we want it to block and notअगरier unregistrations are
 * uncommon.  The callbacks associated with the notअगरier must not
 * re-enter पूर्णांकo the clk framework by calling any top-level clk APIs;
 * this will cause a nested prepare_lock mutex.
 *
 * In all notअगरication हालs (pre, post and पात rate change) the original
 * घड़ी rate is passed to the callback via काष्ठा clk_notअगरier_data.old_rate
 * and the new frequency is passed via काष्ठा clk_notअगरier_data.new_rate.
 *
 * clk_notअगरier_रेजिस्टर() must be called from non-atomic context.
 * Returns -EINVAL अगर called with null arguments, -ENOMEM upon
 * allocation failure; otherwise, passes aदीर्घ the वापस value of
 * srcu_notअगरier_chain_रेजिस्टर().
 */
पूर्णांक clk_notअगरier_रेजिस्टर(काष्ठा clk *clk, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा clk_notअगरier *cn;
	पूर्णांक ret = -ENOMEM;

	अगर (!clk || !nb)
		वापस -EINVAL;

	clk_prepare_lock();

	/* search the list of notअगरiers क्रम this clk */
	list_क्रम_each_entry(cn, &clk_notअगरier_list, node)
		अगर (cn->clk == clk)
			जाओ found;

	/* अगर clk wasn't in the notअगरier list, allocate new clk_notअगरier */
	cn = kzalloc(माप(*cn), GFP_KERNEL);
	अगर (!cn)
		जाओ out;

	cn->clk = clk;
	srcu_init_notअगरier_head(&cn->notअगरier_head);

	list_add(&cn->node, &clk_notअगरier_list);

found:
	ret = srcu_notअगरier_chain_रेजिस्टर(&cn->notअगरier_head, nb);

	clk->core->notअगरier_count++;

out:
	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_notअगरier_रेजिस्टर);

/**
 * clk_notअगरier_unरेजिस्टर - हटाओ a clk rate change notअगरier
 * @clk: काष्ठा clk *
 * @nb: काष्ठा notअगरier_block * with callback info
 *
 * Request no further notअगरication क्रम changes to 'clk' and मुक्तs memory
 * allocated in clk_notअगरier_रेजिस्टर.
 *
 * Returns -EINVAL अगर called with null arguments; otherwise, passes
 * aदीर्घ the वापस value of srcu_notअगरier_chain_unरेजिस्टर().
 */
पूर्णांक clk_notअगरier_unरेजिस्टर(काष्ठा clk *clk, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा clk_notअगरier *cn;
	पूर्णांक ret = -ENOENT;

	अगर (!clk || !nb)
		वापस -EINVAL;

	clk_prepare_lock();

	list_क्रम_each_entry(cn, &clk_notअगरier_list, node) अणु
		अगर (cn->clk == clk) अणु
			ret = srcu_notअगरier_chain_unरेजिस्टर(&cn->notअगरier_head, nb);

			clk->core->notअगरier_count--;

			/* XXX the notअगरier code should handle this better */
			अगर (!cn->notअगरier_head.head) अणु
				srcu_cleanup_notअगरier_head(&cn->notअगरier_head);
				list_del(&cn->node);
				kमुक्त(cn);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	clk_prepare_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_notअगरier_unरेजिस्टर);

काष्ठा clk_notअगरier_devres अणु
	काष्ठा clk *clk;
	काष्ठा notअगरier_block *nb;
पूर्ण;

अटल व्योम devm_clk_notअगरier_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा clk_notअगरier_devres *devres = res;

	clk_notअगरier_unरेजिस्टर(devres->clk, devres->nb);
पूर्ण

पूर्णांक devm_clk_notअगरier_रेजिस्टर(काष्ठा device *dev, काष्ठा clk *clk,
			       काष्ठा notअगरier_block *nb)
अणु
	काष्ठा clk_notअगरier_devres *devres;
	पूर्णांक ret;

	devres = devres_alloc(devm_clk_notअगरier_release,
			      माप(*devres), GFP_KERNEL);

	अगर (!devres)
		वापस -ENOMEM;

	ret = clk_notअगरier_रेजिस्टर(clk, nb);
	अगर (!ret) अणु
		devres->clk = clk;
		devres->nb = nb;
	पूर्ण अन्यथा अणु
		devres_मुक्त(devres);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_notअगरier_रेजिस्टर);

#अगर_घोषित CONFIG_OF
अटल व्योम clk_core_reparent_orphans(व्योम)
अणु
	clk_prepare_lock();
	clk_core_reparent_orphans_nolock();
	clk_prepare_unlock();
पूर्ण

/**
 * काष्ठा of_clk_provider - Clock provider registration काष्ठाure
 * @link: Entry in global list of घड़ी providers
 * @node: Poपूर्णांकer to device tree node of घड़ी provider
 * @get: Get घड़ी callback.  Returns शून्य or a काष्ठा clk क्रम the
 *       given घड़ी specअगरier
 * @get_hw: Get clk_hw callback.  Returns शून्य, ERR_PTR or a
 *       काष्ठा clk_hw क्रम the given घड़ी specअगरier
 * @data: context poपूर्णांकer to be passed पूर्णांकo @get callback
 */
काष्ठा of_clk_provider अणु
	काष्ठा list_head link;

	काष्ठा device_node *node;
	काष्ठा clk *(*get)(काष्ठा of_phandle_args *clkspec, व्योम *data);
	काष्ठा clk_hw *(*get_hw)(काष्ठा of_phandle_args *clkspec, व्योम *data);
	व्योम *data;
पूर्ण;

बाह्य काष्ठा of_device_id __clk_of_table;
अटल स्थिर काष्ठा of_device_id __clk_of_table_sentinel
	__used __section("__clk_of_table_end");

अटल LIST_HEAD(of_clk_providers);
अटल DEFINE_MUTEX(of_clk_mutex);

काष्ठा clk *of_clk_src_simple_get(काष्ठा of_phandle_args *clkspec,
				     व्योम *data)
अणु
	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_src_simple_get);

काष्ठा clk_hw *of_clk_hw_simple_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_hw_simple_get);

काष्ठा clk *of_clk_src_onecell_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा clk_onecell_data *clk_data = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= clk_data->clk_num) अणु
		pr_err("%s: invalid clock index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस clk_data->clks[idx];
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_src_onecell_get);

काष्ठा clk_hw *
of_clk_hw_onecell_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा clk_hw_onecell_data *hw_data = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= hw_data->num) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस hw_data->hws[idx];
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_hw_onecell_get);

/**
 * of_clk_add_provider() - Register a घड़ी provider क्रम a node
 * @np: Device node poपूर्णांकer associated with घड़ी provider
 * @clk_src_get: callback क्रम decoding घड़ी
 * @data: context poपूर्णांकer क्रम @clk_src_get callback.
 *
 * This function is *deprecated*. Use of_clk_add_hw_provider() instead.
 */
पूर्णांक of_clk_add_provider(काष्ठा device_node *np,
			काष्ठा clk *(*clk_src_get)(काष्ठा of_phandle_args *clkspec,
						   व्योम *data),
			व्योम *data)
अणु
	काष्ठा of_clk_provider *cp;
	पूर्णांक ret;

	अगर (!np)
		वापस 0;

	cp = kzalloc(माप(*cp), GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	cp->node = of_node_get(np);
	cp->data = data;
	cp->get = clk_src_get;

	mutex_lock(&of_clk_mutex);
	list_add(&cp->link, &of_clk_providers);
	mutex_unlock(&of_clk_mutex);
	pr_debug("Added clock from %pOF\n", np);

	clk_core_reparent_orphans();

	ret = of_clk_set_शेषs(np, true);
	अगर (ret < 0)
		of_clk_del_provider(np);

	fwnode_dev_initialized(&np->fwnode, true);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_add_provider);

/**
 * of_clk_add_hw_provider() - Register a घड़ी provider क्रम a node
 * @np: Device node poपूर्णांकer associated with घड़ी provider
 * @get: callback क्रम decoding clk_hw
 * @data: context poपूर्णांकer क्रम @get callback.
 */
पूर्णांक of_clk_add_hw_provider(काष्ठा device_node *np,
			   काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
						 व्योम *data),
			   व्योम *data)
अणु
	काष्ठा of_clk_provider *cp;
	पूर्णांक ret;

	अगर (!np)
		वापस 0;

	cp = kzalloc(माप(*cp), GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	cp->node = of_node_get(np);
	cp->data = data;
	cp->get_hw = get;

	mutex_lock(&of_clk_mutex);
	list_add(&cp->link, &of_clk_providers);
	mutex_unlock(&of_clk_mutex);
	pr_debug("Added clk_hw provider from %pOF\n", np);

	clk_core_reparent_orphans();

	ret = of_clk_set_शेषs(np, true);
	अगर (ret < 0)
		of_clk_del_provider(np);

	fwnode_dev_initialized(&np->fwnode, true);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_add_hw_provider);

अटल व्योम devm_of_clk_release_provider(काष्ठा device *dev, व्योम *res)
अणु
	of_clk_del_provider(*(काष्ठा device_node **)res);
पूर्ण

/*
 * We allow a child device to use its parent device as the घड़ी provider node
 * क्रम हालs like MFD sub-devices where the child device driver wants to use
 * devm_*() APIs but not list the device in DT as a sub-node.
 */
अटल काष्ठा device_node *get_clk_provider_node(काष्ठा device *dev)
अणु
	काष्ठा device_node *np, *parent_np;

	np = dev->of_node;
	parent_np = dev->parent ? dev->parent->of_node : शून्य;

	अगर (!of_find_property(np, "#clock-cells", शून्य))
		अगर (of_find_property(parent_np, "#clock-cells", शून्य))
			np = parent_np;

	वापस np;
पूर्ण

/**
 * devm_of_clk_add_hw_provider() - Managed clk provider node registration
 * @dev: Device acting as the घड़ी provider (used क्रम DT node and lअगरeसमय)
 * @get: callback क्रम decoding clk_hw
 * @data: context poपूर्णांकer क्रम @get callback
 *
 * Registers घड़ी provider क्रम given device's node. If the device has no DT
 * node or अगर the device node lacks of घड़ी provider inक्रमmation (#घड़ी-cells)
 * then the parent device's node is scanned क्रम this inक्रमmation. If parent node
 * has the #घड़ी-cells then it is used in registration. Provider is
 * स्वतःmatically released at device निकास.
 *
 * Return: 0 on success or an त्रुटि_सं on failure.
 */
पूर्णांक devm_of_clk_add_hw_provider(काष्ठा device *dev,
			काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
					      व्योम *data),
			व्योम *data)
अणु
	काष्ठा device_node **ptr, *np;
	पूर्णांक ret;

	ptr = devres_alloc(devm_of_clk_release_provider, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	np = get_clk_provider_node(dev);
	ret = of_clk_add_hw_provider(np, get, data);
	अगर (!ret) अणु
		*ptr = np;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_clk_add_hw_provider);

/**
 * of_clk_del_provider() - Remove a previously रेजिस्टरed घड़ी provider
 * @np: Device node poपूर्णांकer associated with घड़ी provider
 */
व्योम of_clk_del_provider(काष्ठा device_node *np)
अणु
	काष्ठा of_clk_provider *cp;

	अगर (!np)
		वापस;

	mutex_lock(&of_clk_mutex);
	list_क्रम_each_entry(cp, &of_clk_providers, link) अणु
		अगर (cp->node == np) अणु
			list_del(&cp->link);
			fwnode_dev_initialized(&np->fwnode, false);
			of_node_put(cp->node);
			kमुक्त(cp);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&of_clk_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_del_provider);

अटल पूर्णांक devm_clk_provider_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा device_node **np = res;

	अगर (WARN_ON(!np || !*np))
		वापस 0;

	वापस *np == data;
पूर्ण

/**
 * devm_of_clk_del_provider() - Remove घड़ी provider रेजिस्टरed using devm
 * @dev: Device to whose lअगरeसमय the घड़ी provider was bound
 */
व्योम devm_of_clk_del_provider(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = get_clk_provider_node(dev);

	ret = devres_release(dev, devm_of_clk_release_provider,
			     devm_clk_provider_match, np);

	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL(devm_of_clk_del_provider);

/**
 * of_parse_clkspec() - Parse a DT घड़ी specअगरier क्रम a given device node
 * @np: device node to parse घड़ी specअगरier from
 * @index: index of phandle to parse घड़ी out of. If index < 0, @name is used
 * @name: घड़ी name to find and parse. If name is शून्य, the index is used
 * @out_args: Result of parsing the घड़ी specअगरier
 *
 * Parses a device node's "clocks" and "clock-names" properties to find the
 * phandle and cells क्रम the index or name that is desired. The resulting घड़ी
 * specअगरier is placed पूर्णांकo @out_args, or an त्रुटि_सं is वापसed when there's a
 * parsing error. The @index argument is ignored अगर @name is non-शून्य.
 *
 * Example:
 *
 * phandle1: घड़ी-controller@1 अणु
 *	#घड़ी-cells = <2>;
 * पूर्ण
 *
 * phandle2: घड़ी-controller@2 अणु
 *	#घड़ी-cells = <1>;
 * पूर्ण
 *
 * घड़ी-consumer@3 अणु
 *	घड़ीs = <&phandle1 1 2 &phandle2 3>;
 *	घड़ी-names = "name1", "name2";
 * पूर्ण
 *
 * To get a device_node क्रम `घड़ी-controller@2' node you may call this
 * function a few dअगरferent ways:
 *
 *   of_parse_clkspec(घड़ी-consumer@3, -1, "name2", &args);
 *   of_parse_clkspec(घड़ी-consumer@3, 1, शून्य, &args);
 *   of_parse_clkspec(घड़ी-consumer@3, 1, "name2", &args);
 *
 * Return: 0 upon successfully parsing the घड़ी specअगरier. Otherwise, -ENOENT
 * अगर @name is शून्य or -EINVAL अगर @name is non-शून्य and it can't be found in
 * the "clock-names" property of @np.
 */
अटल पूर्णांक of_parse_clkspec(स्थिर काष्ठा device_node *np, पूर्णांक index,
			    स्थिर अक्षर *name, काष्ठा of_phandle_args *out_args)
अणु
	पूर्णांक ret = -ENOENT;

	/* Walk up the tree of devices looking क्रम a घड़ी property that matches */
	जबतक (np) अणु
		/*
		 * For named घड़ीs, first look up the name in the
		 * "clock-names" property.  If it cannot be found, then index
		 * will be an error code and of_parse_phandle_with_args() will
		 * वापस -EINVAL.
		 */
		अगर (name)
			index = of_property_match_string(np, "clock-names", name);
		ret = of_parse_phandle_with_args(np, "clocks", "#clock-cells",
						 index, out_args);
		अगर (!ret)
			अवरोध;
		अगर (name && index >= 0)
			अवरोध;

		/*
		 * No matching घड़ी found on this node.  If the parent node
		 * has a "clock-ranges" property, then we can try one of its
		 * घड़ीs.
		 */
		np = np->parent;
		अगर (np && !of_get_property(np, "clock-ranges", शून्य))
			अवरोध;
		index = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा clk_hw *
__of_clk_get_hw_from_provider(काष्ठा of_clk_provider *provider,
			      काष्ठा of_phandle_args *clkspec)
अणु
	काष्ठा clk *clk;

	अगर (provider->get_hw)
		वापस provider->get_hw(clkspec, provider->data);

	clk = provider->get(clkspec, provider->data);
	अगर (IS_ERR(clk))
		वापस ERR_CAST(clk);
	वापस __clk_get_hw(clk);
पूर्ण

अटल काष्ठा clk_hw *
of_clk_get_hw_from_clkspec(काष्ठा of_phandle_args *clkspec)
अणु
	काष्ठा of_clk_provider *provider;
	काष्ठा clk_hw *hw = ERR_PTR(-EPROBE_DEFER);

	अगर (!clkspec)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&of_clk_mutex);
	list_क्रम_each_entry(provider, &of_clk_providers, link) अणु
		अगर (provider->node == clkspec->np) अणु
			hw = __of_clk_get_hw_from_provider(provider, clkspec);
			अगर (!IS_ERR(hw))
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&of_clk_mutex);

	वापस hw;
पूर्ण

/**
 * of_clk_get_from_provider() - Lookup a घड़ी from a घड़ी provider
 * @clkspec: poपूर्णांकer to a घड़ी specअगरier data काष्ठाure
 *
 * This function looks up a काष्ठा clk from the रेजिस्टरed list of घड़ी
 * providers, an input is a घड़ी specअगरier data काष्ठाure as वापसed
 * from the of_parse_phandle_with_args() function call.
 */
काष्ठा clk *of_clk_get_from_provider(काष्ठा of_phandle_args *clkspec)
अणु
	काष्ठा clk_hw *hw = of_clk_get_hw_from_clkspec(clkspec);

	वापस clk_hw_create_clk(शून्य, hw, शून्य, __func__);
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_get_from_provider);

काष्ठा clk_hw *of_clk_get_hw(काष्ठा device_node *np, पूर्णांक index,
			     स्थिर अक्षर *con_id)
अणु
	पूर्णांक ret;
	काष्ठा clk_hw *hw;
	काष्ठा of_phandle_args clkspec;

	ret = of_parse_clkspec(np, index, con_id, &clkspec);
	अगर (ret)
		वापस ERR_PTR(ret);

	hw = of_clk_get_hw_from_clkspec(&clkspec);
	of_node_put(clkspec.np);

	वापस hw;
पूर्ण

अटल काष्ठा clk *__of_clk_get(काष्ठा device_node *np,
				पूर्णांक index, स्थिर अक्षर *dev_id,
				स्थिर अक्षर *con_id)
अणु
	काष्ठा clk_hw *hw = of_clk_get_hw(np, index, con_id);

	वापस clk_hw_create_clk(शून्य, hw, dev_id, con_id);
पूर्ण

काष्ठा clk *of_clk_get(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस __of_clk_get(np, index, np->full_name, शून्य);
पूर्ण
EXPORT_SYMBOL(of_clk_get);

/**
 * of_clk_get_by_name() - Parse and lookup a घड़ी referenced by a device node
 * @np: poपूर्णांकer to घड़ी consumer node
 * @name: name of consumer's घड़ी input, or शून्य क्रम the first घड़ी reference
 *
 * This function parses the घड़ीs and घड़ी-names properties,
 * and uses them to look up the काष्ठा clk from the रेजिस्टरed list of घड़ी
 * providers.
 */
काष्ठा clk *of_clk_get_by_name(काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	अगर (!np)
		वापस ERR_PTR(-ENOENT);

	वापस __of_clk_get(np, 0, np->full_name, name);
पूर्ण
EXPORT_SYMBOL(of_clk_get_by_name);

/**
 * of_clk_get_parent_count() - Count the number of घड़ीs a device node has
 * @np: device node to count
 *
 * Returns: The number of घड़ीs that are possible parents of this node
 */
अचिन्हित पूर्णांक of_clk_get_parent_count(स्थिर काष्ठा device_node *np)
अणु
	पूर्णांक count;

	count = of_count_phandle_with_args(np, "clocks", "#clock-cells");
	अगर (count < 0)
		वापस 0;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_get_parent_count);

स्थिर अक्षर *of_clk_get_parent_name(स्थिर काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा of_phandle_args clkspec;
	काष्ठा property *prop;
	स्थिर अक्षर *clk_name;
	स्थिर __be32 *vp;
	u32 pv;
	पूर्णांक rc;
	पूर्णांक count;
	काष्ठा clk *clk;

	rc = of_parse_phandle_with_args(np, "clocks", "#clock-cells", index,
					&clkspec);
	अगर (rc)
		वापस शून्य;

	index = clkspec.args_count ? clkspec.args[0] : 0;
	count = 0;

	/* अगर there is an indices property, use it to transfer the index
	 * specअगरied पूर्णांकo an array offset क्रम the घड़ी-output-names property.
	 */
	of_property_क्रम_each_u32(clkspec.np, "clock-indices", prop, vp, pv) अणु
		अगर (index == pv) अणु
			index = count;
			अवरोध;
		पूर्ण
		count++;
	पूर्ण
	/* We went off the end of 'clock-indices' without finding it */
	अगर (prop && !vp)
		वापस शून्य;

	अगर (of_property_पढ़ो_string_index(clkspec.np, "clock-output-names",
					  index,
					  &clk_name) < 0) अणु
		/*
		 * Best efक्रमt to get the name अगर the घड़ी has been
		 * रेजिस्टरed with the framework. If the घड़ी isn't
		 * रेजिस्टरed, we वापस the node name as the name of
		 * the घड़ी as दीर्घ as #घड़ी-cells = 0.
		 */
		clk = of_clk_get_from_provider(&clkspec);
		अगर (IS_ERR(clk)) अणु
			अगर (clkspec.args_count == 0)
				clk_name = clkspec.np->name;
			अन्यथा
				clk_name = शून्य;
		पूर्ण अन्यथा अणु
			clk_name = __clk_get_name(clk);
			clk_put(clk);
		पूर्ण
	पूर्ण


	of_node_put(clkspec.np);
	वापस clk_name;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_get_parent_name);

/**
 * of_clk_parent_fill() - Fill @parents with names of @np's parents and वापस
 * number of parents
 * @np: Device node poपूर्णांकer associated with घड़ी provider
 * @parents: poपूर्णांकer to अक्षर array that hold the parents' names
 * @size: size of the @parents array
 *
 * Return: number of parents क्रम the घड़ी node.
 */
पूर्णांक of_clk_parent_fill(काष्ठा device_node *np, स्थिर अक्षर **parents,
		       अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (i < size && (parents[i] = of_clk_get_parent_name(np, i)) != शून्य)
		i++;

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_parent_fill);

काष्ठा घड़ी_provider अणु
	व्योम (*clk_init_cb)(काष्ठा device_node *);
	काष्ठा device_node *np;
	काष्ठा list_head node;
पूर्ण;

/*
 * This function looks क्रम a parent घड़ी. If there is one, then it
 * checks that the provider क्रम this parent घड़ी was initialized, in
 * this हाल the parent घड़ी will be पढ़ोy.
 */
अटल पूर्णांक parent_पढ़ोy(काष्ठा device_node *np)
अणु
	पूर्णांक i = 0;

	जबतक (true) अणु
		काष्ठा clk *clk = of_clk_get(np, i);

		/* this parent is पढ़ोy we can check the next one */
		अगर (!IS_ERR(clk)) अणु
			clk_put(clk);
			i++;
			जारी;
		पूर्ण

		/* at least one parent is not पढ़ोy, we निकास now */
		अगर (PTR_ERR(clk) == -EPROBE_DEFER)
			वापस 0;

		/*
		 * Here we make assumption that the device tree is
		 * written correctly. So an error means that there is
		 * no more parent. As we didn't निकास yet, then the
		 * previous parent are पढ़ोy. If there is no घड़ी
		 * parent, no need to रुको क्रम them, then we can
		 * consider their असलence as being पढ़ोy
		 */
		वापस 1;
	पूर्ण
पूर्ण

/**
 * of_clk_detect_critical() - set CLK_IS_CRITICAL flag from Device Tree
 * @np: Device node poपूर्णांकer associated with घड़ी provider
 * @index: घड़ी index
 * @flags: poपूर्णांकer to top-level framework flags
 *
 * Detects अगर the घड़ी-critical property exists and, अगर so, sets the
 * corresponding CLK_IS_CRITICAL flag.
 *
 * Do not use this function. It exists only क्रम legacy Device Tree
 * bindings, such as the one-घड़ी-per-node style that are outdated.
 * Those bindings typically put all घड़ी data पूर्णांकo .dts and the Linux
 * driver has no घड़ी data, thus making it impossible to set this flag
 * correctly from the driver. Only those drivers may call
 * of_clk_detect_critical from their setup functions.
 *
 * Return: error code or zero on success
 */
पूर्णांक of_clk_detect_critical(काष्ठा device_node *np, पूर्णांक index,
			   अचिन्हित दीर्घ *flags)
अणु
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	uपूर्णांक32_t idx;

	अगर (!np || !flags)
		वापस -EINVAL;

	of_property_क्रम_each_u32(np, "clock-critical", prop, cur, idx)
		अगर (index == idx)
			*flags |= CLK_IS_CRITICAL;

	वापस 0;
पूर्ण

/**
 * of_clk_init() - Scan and init घड़ी providers from the DT
 * @matches: array of compatible values and init functions क्रम providers.
 *
 * This function scans the device tree क्रम matching घड़ी providers
 * and calls their initialization functions. It also करोes it by trying
 * to follow the dependencies.
 */
व्योम __init of_clk_init(स्थिर काष्ठा of_device_id *matches)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	काष्ठा घड़ी_provider *clk_provider, *next;
	bool is_init_करोne;
	bool क्रमce = false;
	LIST_HEAD(clk_provider_list);

	अगर (!matches)
		matches = &__clk_of_table;

	/* First prepare the list of the घड़ीs providers */
	क्रम_each_matching_node_and_match(np, matches, &match) अणु
		काष्ठा घड़ी_provider *parent;

		अगर (!of_device_is_available(np))
			जारी;

		parent = kzalloc(माप(*parent), GFP_KERNEL);
		अगर (!parent) अणु
			list_क्रम_each_entry_safe(clk_provider, next,
						 &clk_provider_list, node) अणु
				list_del(&clk_provider->node);
				of_node_put(clk_provider->np);
				kमुक्त(clk_provider);
			पूर्ण
			of_node_put(np);
			वापस;
		पूर्ण

		parent->clk_init_cb = match->data;
		parent->np = of_node_get(np);
		list_add_tail(&parent->node, &clk_provider_list);
	पूर्ण

	जबतक (!list_empty(&clk_provider_list)) अणु
		is_init_करोne = false;
		list_क्रम_each_entry_safe(clk_provider, next,
					&clk_provider_list, node) अणु
			अगर (क्रमce || parent_पढ़ोy(clk_provider->np)) अणु

				/* Don't populate platक्रमm devices */
				of_node_set_flag(clk_provider->np,
						 OF_POPULATED);

				clk_provider->clk_init_cb(clk_provider->np);
				of_clk_set_शेषs(clk_provider->np, true);

				list_del(&clk_provider->node);
				of_node_put(clk_provider->np);
				kमुक्त(clk_provider);
				is_init_करोne = true;
			पूर्ण
		पूर्ण

		/*
		 * We didn't manage to initialize any of the
		 * reमुख्यing providers during the last loop, so now we
		 * initialize all the reमुख्यing ones unconditionally
		 * in हाल the घड़ी parent was not mandatory
		 */
		अगर (!is_init_करोne)
			क्रमce = true;
	पूर्ण
पूर्ण
#पूर्ण_अगर
