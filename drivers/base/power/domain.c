<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/करोमुख्य.c - Common code related to device घातer करोमुख्यs.
 *
 * Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */
#घोषणा pr_fmt(fmt) "PM: " fmt

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/suspend.h>
#समावेश <linux/export.h>
#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>

#समावेश "power.h"

#घोषणा GENPD_RETRY_MAX_MS	250		/* Approximate */

#घोषणा GENPD_DEV_CALLBACK(genpd, type, callback, dev)		\
(अणु								\
	type (*__routine)(काष्ठा device *__d); 			\
	type __ret = (type)0;					\
								\
	__routine = genpd->dev_ops.callback; 			\
	अगर (__routine) अणु					\
		__ret = __routine(dev); 			\
	पूर्ण							\
	__ret;							\
पूर्ण)

अटल LIST_HEAD(gpd_list);
अटल DEFINE_MUTEX(gpd_list_lock);

काष्ठा genpd_lock_ops अणु
	व्योम (*lock)(काष्ठा generic_pm_करोमुख्य *genpd);
	व्योम (*lock_nested)(काष्ठा generic_pm_करोमुख्य *genpd, पूर्णांक depth);
	पूर्णांक (*lock_पूर्णांकerruptible)(काष्ठा generic_pm_करोमुख्य *genpd);
	व्योम (*unlock)(काष्ठा generic_pm_करोमुख्य *genpd);
पूर्ण;

अटल व्योम genpd_lock_mtx(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	mutex_lock(&genpd->mlock);
पूर्ण

अटल व्योम genpd_lock_nested_mtx(काष्ठा generic_pm_करोमुख्य *genpd,
					पूर्णांक depth)
अणु
	mutex_lock_nested(&genpd->mlock, depth);
पूर्ण

अटल पूर्णांक genpd_lock_पूर्णांकerruptible_mtx(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&genpd->mlock);
पूर्ण

अटल व्योम genpd_unlock_mtx(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस mutex_unlock(&genpd->mlock);
पूर्ण

अटल स्थिर काष्ठा genpd_lock_ops genpd_mtx_ops = अणु
	.lock = genpd_lock_mtx,
	.lock_nested = genpd_lock_nested_mtx,
	.lock_पूर्णांकerruptible = genpd_lock_पूर्णांकerruptible_mtx,
	.unlock = genpd_unlock_mtx,
पूर्ण;

अटल व्योम genpd_lock_spin(काष्ठा generic_pm_करोमुख्य *genpd)
	__acquires(&genpd->slock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&genpd->slock, flags);
	genpd->lock_flags = flags;
पूर्ण

अटल व्योम genpd_lock_nested_spin(काष्ठा generic_pm_करोमुख्य *genpd,
					पूर्णांक depth)
	__acquires(&genpd->slock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave_nested(&genpd->slock, flags, depth);
	genpd->lock_flags = flags;
पूर्ण

अटल पूर्णांक genpd_lock_पूर्णांकerruptible_spin(काष्ठा generic_pm_करोमुख्य *genpd)
	__acquires(&genpd->slock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&genpd->slock, flags);
	genpd->lock_flags = flags;
	वापस 0;
पूर्ण

अटल व्योम genpd_unlock_spin(काष्ठा generic_pm_करोमुख्य *genpd)
	__releases(&genpd->slock)
अणु
	spin_unlock_irqrestore(&genpd->slock, genpd->lock_flags);
पूर्ण

अटल स्थिर काष्ठा genpd_lock_ops genpd_spin_ops = अणु
	.lock = genpd_lock_spin,
	.lock_nested = genpd_lock_nested_spin,
	.lock_पूर्णांकerruptible = genpd_lock_पूर्णांकerruptible_spin,
	.unlock = genpd_unlock_spin,
पूर्ण;

#घोषणा genpd_lock(p)			p->lock_ops->lock(p)
#घोषणा genpd_lock_nested(p, d)		p->lock_ops->lock_nested(p, d)
#घोषणा genpd_lock_पूर्णांकerruptible(p)	p->lock_ops->lock_पूर्णांकerruptible(p)
#घोषणा genpd_unlock(p)			p->lock_ops->unlock(p)

#घोषणा genpd_status_on(genpd)		(genpd->status == GENPD_STATE_ON)
#घोषणा genpd_is_irq_safe(genpd)	(genpd->flags & GENPD_FLAG_IRQ_SAFE)
#घोषणा genpd_is_always_on(genpd)	(genpd->flags & GENPD_FLAG_ALWAYS_ON)
#घोषणा genpd_is_active_wakeup(genpd)	(genpd->flags & GENPD_FLAG_ACTIVE_WAKEUP)
#घोषणा genpd_is_cpu_करोमुख्य(genpd)	(genpd->flags & GENPD_FLAG_CPU_DOMAIN)
#घोषणा genpd_is_rpm_always_on(genpd)	(genpd->flags & GENPD_FLAG_RPM_ALWAYS_ON)

अटल अंतरभूत bool irq_safe_dev_in_no_sleep_करोमुख्य(काष्ठा device *dev,
		स्थिर काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	bool ret;

	ret = pm_runसमय_is_irq_safe(dev) && !genpd_is_irq_safe(genpd);

	/*
	 * Warn once अगर an IRQ safe device is attached to a no sleep करोमुख्य, as
	 * to indicate a suboptimal configuration क्रम PM. For an always on
	 * करोमुख्य this isn't case, thus don't warn.
	 */
	अगर (ret && !genpd_is_always_on(genpd))
		dev_warn_once(dev, "PM domain %s will not be powered off\n",
				genpd->name);

	वापस ret;
पूर्ण

अटल पूर्णांक genpd_runसमय_suspend(काष्ठा device *dev);

/*
 * Get the generic PM करोमुख्य क्रम a particular काष्ठा device.
 * This validates the काष्ठा device poपूर्णांकer, the PM करोमुख्य poपूर्णांकer,
 * and checks that the PM करोमुख्य poपूर्णांकer is a real generic PM करोमुख्य.
 * Any failure results in शून्य being वापसed.
 */
अटल काष्ठा generic_pm_करोमुख्य *dev_to_genpd_safe(काष्ठा device *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev) || IS_ERR_OR_शून्य(dev->pm_करोमुख्य))
		वापस शून्य;

	/* A genpd's always have its ->runसमय_suspend() callback asचिन्हित. */
	अगर (dev->pm_करोमुख्य->ops.runसमय_suspend == genpd_runसमय_suspend)
		वापस pd_to_genpd(dev->pm_करोमुख्य);

	वापस शून्य;
पूर्ण

/*
 * This should only be used where we are certain that the pm_करोमुख्य
 * attached to the device is a genpd करोमुख्य.
 */
अटल काष्ठा generic_pm_करोमुख्य *dev_to_genpd(काष्ठा device *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev->pm_करोमुख्य))
		वापस ERR_PTR(-EINVAL);

	वापस pd_to_genpd(dev->pm_करोमुख्य);
पूर्ण

अटल पूर्णांक genpd_stop_dev(स्थिर काष्ठा generic_pm_करोमुख्य *genpd,
			  काष्ठा device *dev)
अणु
	वापस GENPD_DEV_CALLBACK(genpd, पूर्णांक, stop, dev);
पूर्ण

अटल पूर्णांक genpd_start_dev(स्थिर काष्ठा generic_pm_करोमुख्य *genpd,
			   काष्ठा device *dev)
अणु
	वापस GENPD_DEV_CALLBACK(genpd, पूर्णांक, start, dev);
पूर्ण

अटल bool genpd_sd_counter_dec(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	bool ret = false;

	अगर (!WARN_ON(atomic_पढ़ो(&genpd->sd_count) == 0))
		ret = !!atomic_dec_and_test(&genpd->sd_count);

	वापस ret;
पूर्ण

अटल व्योम genpd_sd_counter_inc(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	atomic_inc(&genpd->sd_count);
	smp_mb__after_atomic();
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *genpd_debugfs_dir;

अटल व्योम genpd_debug_add(काष्ठा generic_pm_करोमुख्य *genpd);

अटल व्योम genpd_debug_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा dentry *d;

	d = debugfs_lookup(genpd->name, genpd_debugfs_dir);
	debugfs_हटाओ(d);
पूर्ण

अटल व्योम genpd_update_accounting(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	kसमय_प्रकार delta, now;

	now = kसमय_get();
	delta = kसमय_sub(now, genpd->accounting_समय);

	/*
	 * If genpd->status is active, it means we are just
	 * out of off and so update the idle समय and vice
	 * versa.
	 */
	अगर (genpd->status == GENPD_STATE_ON) अणु
		पूर्णांक state_idx = genpd->state_idx;

		genpd->states[state_idx].idle_समय =
			kसमय_add(genpd->states[state_idx].idle_समय, delta);
	पूर्ण अन्यथा अणु
		genpd->on_समय = kसमय_add(genpd->on_समय, delta);
	पूर्ण

	genpd->accounting_समय = now;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम genpd_debug_add(काष्ठा generic_pm_करोमुख्य *genpd) अणुपूर्ण
अटल अंतरभूत व्योम genpd_debug_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd) अणुपूर्ण
अटल अंतरभूत व्योम genpd_update_accounting(काष्ठा generic_pm_करोमुख्य *genpd) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक _genpd_reeval_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *genpd,
					   अचिन्हित पूर्णांक state)
अणु
	काष्ठा generic_pm_करोमुख्य_data *pd_data;
	काष्ठा pm_करोमुख्य_data *pdd;
	काष्ठा gpd_link *link;

	/* New requested state is same as Max requested state */
	अगर (state == genpd->perक्रमmance_state)
		वापस state;

	/* New requested state is higher than Max requested state */
	अगर (state > genpd->perक्रमmance_state)
		वापस state;

	/* Traverse all devices within the करोमुख्य */
	list_क्रम_each_entry(pdd, &genpd->dev_list, list_node) अणु
		pd_data = to_gpd_data(pdd);

		अगर (pd_data->perक्रमmance_state > state)
			state = pd_data->perक्रमmance_state;
	पूर्ण

	/*
	 * Traverse all sub-करोमुख्यs within the करोमुख्य. This can be
	 * करोne without any additional locking as the link->perक्रमmance_state
	 * field is रक्षित by the parent genpd->lock, which is alपढ़ोy taken.
	 *
	 * Also note that link->perक्रमmance_state (subकरोमुख्य's perक्रमmance state
	 * requirement to parent करोमुख्य) is dअगरferent from
	 * link->child->perक्रमmance_state (current perक्रमmance state requirement
	 * of the devices/sub-करोमुख्यs of the subकरोमुख्य) and so can have a
	 * dअगरferent value.
	 *
	 * Note that we also take vote from घातered-off sub-करोमुख्यs पूर्णांकo account
	 * as the same is करोne क्रम devices right now.
	 */
	list_क्रम_each_entry(link, &genpd->parent_links, parent_node) अणु
		अगर (link->perक्रमmance_state > state)
			state = link->perक्रमmance_state;
	पूर्ण

	वापस state;
पूर्ण

अटल पूर्णांक genpd_xlate_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *genpd,
					 काष्ठा generic_pm_करोमुख्य *parent,
					 अचिन्हित पूर्णांक pstate)
अणु
	अगर (!parent->set_perक्रमmance_state)
		वापस pstate;

	वापस dev_pm_opp_xlate_perक्रमmance_state(genpd->opp_table,
						  parent->opp_table,
						  pstate);
पूर्ण

अटल पूर्णांक _genpd_set_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *genpd,
					अचिन्हित पूर्णांक state, पूर्णांक depth)
अणु
	काष्ठा generic_pm_करोमुख्य *parent;
	काष्ठा gpd_link *link;
	पूर्णांक parent_state, ret;

	अगर (state == genpd->perक्रमmance_state)
		वापस 0;

	/* Propagate to parents of genpd */
	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		parent = link->parent;

		/* Find parent's perक्रमmance state */
		ret = genpd_xlate_perक्रमmance_state(genpd, parent, state);
		अगर (unlikely(ret < 0))
			जाओ err;

		parent_state = ret;

		genpd_lock_nested(parent, depth + 1);

		link->prev_perक्रमmance_state = link->perक्रमmance_state;
		link->perक्रमmance_state = parent_state;
		parent_state = _genpd_reeval_perक्रमmance_state(parent,
						parent_state);
		ret = _genpd_set_perक्रमmance_state(parent, parent_state, depth + 1);
		अगर (ret)
			link->perक्रमmance_state = link->prev_perक्रमmance_state;

		genpd_unlock(parent);

		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (genpd->set_perक्रमmance_state) अणु
		ret = genpd->set_perक्रमmance_state(genpd, state);
		अगर (ret)
			जाओ err;
	पूर्ण

	genpd->perक्रमmance_state = state;
	वापस 0;

err:
	/* Encountered an error, lets rollback */
	list_क्रम_each_entry_जारी_reverse(link, &genpd->child_links,
					     child_node) अणु
		parent = link->parent;

		genpd_lock_nested(parent, depth + 1);

		parent_state = link->prev_perक्रमmance_state;
		link->perक्रमmance_state = parent_state;

		parent_state = _genpd_reeval_perक्रमmance_state(parent,
						parent_state);
		अगर (_genpd_set_perक्रमmance_state(parent, parent_state, depth + 1)) अणु
			pr_err("%s: Failed to roll back to %d performance state\n",
			       parent->name, parent_state);
		पूर्ण

		genpd_unlock(parent);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dev_pm_genpd_set_perक्रमmance_state- Set perक्रमmance state of device's घातer
 * करोमुख्य.
 *
 * @dev: Device क्रम which the perक्रमmance-state needs to be set.
 * @state: Target perक्रमmance state of the device. This can be set as 0 when the
 *	   device करोesn't have any perक्रमmance state स्थिरraपूर्णांकs left (And so
 *	   the device wouldn't participate anymore to find the target
 *	   perक्रमmance state of the genpd).
 *
 * It is assumed that the users guarantee that the genpd wouldn't be detached
 * जबतक this routine is getting called.
 *
 * Returns 0 on success and negative error values on failures.
 */
पूर्णांक dev_pm_genpd_set_perक्रमmance_state(काष्ठा device *dev, अचिन्हित पूर्णांक state)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	अचिन्हित पूर्णांक prev;
	पूर्णांक ret;

	genpd = dev_to_genpd_safe(dev);
	अगर (!genpd)
		वापस -ENODEV;

	अगर (WARN_ON(!dev->घातer.subsys_data ||
		     !dev->घातer.subsys_data->करोमुख्य_data))
		वापस -EINVAL;

	genpd_lock(genpd);

	gpd_data = to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
	prev = gpd_data->perक्रमmance_state;
	gpd_data->perक्रमmance_state = state;

	state = _genpd_reeval_perक्रमmance_state(genpd, state);
	ret = _genpd_set_perक्रमmance_state(genpd, state, 0);
	अगर (ret)
		gpd_data->perक्रमmance_state = prev;

	genpd_unlock(genpd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_set_perक्रमmance_state);

/**
 * dev_pm_genpd_set_next_wakeup - Notअगरy PM framework of an impending wakeup.
 *
 * @dev: Device to handle
 * @next: impending पूर्णांकerrupt/wakeup क्रम the device
 *
 *
 * Allow devices to inक्रमm of the next wakeup. It's assumed that the users
 * guarantee that the genpd wouldn't be detached जबतक this routine is getting
 * called. Additionally, it's also assumed that @dev isn't runसमय suspended
 * (RPM_SUSPENDED)."
 * Although devices are expected to update the next_wakeup after the end of
 * their useहाल as well, it is possible the devices themselves may not know
 * about that, so stale @next will be ignored when घातering off the करोमुख्य.
 */
व्योम dev_pm_genpd_set_next_wakeup(काष्ठा device *dev, kसमय_प्रकार next)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	काष्ठा generic_pm_करोमुख्य *genpd;

	genpd = dev_to_genpd_safe(dev);
	अगर (!genpd)
		वापस;

	gpd_data = to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
	gpd_data->next_wakeup = next;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_set_next_wakeup);

अटल पूर्णांक _genpd_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd, bool समयd)
अणु
	अचिन्हित पूर्णांक state_idx = genpd->state_idx;
	kसमय_प्रकार समय_start;
	s64 elapsed_ns;
	पूर्णांक ret;

	/* Notअगरy consumers that we are about to घातer on. */
	ret = raw_notअगरier_call_chain_robust(&genpd->घातer_notअगरiers,
					     GENPD_NOTIFY_PRE_ON,
					     GENPD_NOTIFY_OFF, शून्य);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		वापस ret;

	अगर (!genpd->घातer_on)
		जाओ out;

	अगर (!समयd) अणु
		ret = genpd->घातer_on(genpd);
		अगर (ret)
			जाओ err;

		जाओ out;
	पूर्ण

	समय_start = kसमय_get();
	ret = genpd->घातer_on(genpd);
	अगर (ret)
		जाओ err;

	elapsed_ns = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), समय_start));
	अगर (elapsed_ns <= genpd->states[state_idx].घातer_on_latency_ns)
		जाओ out;

	genpd->states[state_idx].घातer_on_latency_ns = elapsed_ns;
	genpd->max_off_समय_changed = true;
	pr_debug("%s: Power-%s latency exceeded, new value %lld ns\n",
		 genpd->name, "on", elapsed_ns);

out:
	raw_notअगरier_call_chain(&genpd->घातer_notअगरiers, GENPD_NOTIFY_ON, शून्य);
	वापस 0;
err:
	raw_notअगरier_call_chain(&genpd->घातer_notअगरiers, GENPD_NOTIFY_OFF,
				शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक _genpd_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd, bool समयd)
अणु
	अचिन्हित पूर्णांक state_idx = genpd->state_idx;
	kसमय_प्रकार समय_start;
	s64 elapsed_ns;
	पूर्णांक ret;

	/* Notअगरy consumers that we are about to घातer off. */
	ret = raw_notअगरier_call_chain_robust(&genpd->घातer_notअगरiers,
					     GENPD_NOTIFY_PRE_OFF,
					     GENPD_NOTIFY_ON, शून्य);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		वापस ret;

	अगर (!genpd->घातer_off)
		जाओ out;

	अगर (!समयd) अणु
		ret = genpd->घातer_off(genpd);
		अगर (ret)
			जाओ busy;

		जाओ out;
	पूर्ण

	समय_start = kसमय_get();
	ret = genpd->घातer_off(genpd);
	अगर (ret)
		जाओ busy;

	elapsed_ns = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), समय_start));
	अगर (elapsed_ns <= genpd->states[state_idx].घातer_off_latency_ns)
		जाओ out;

	genpd->states[state_idx].घातer_off_latency_ns = elapsed_ns;
	genpd->max_off_समय_changed = true;
	pr_debug("%s: Power-%s latency exceeded, new value %lld ns\n",
		 genpd->name, "off", elapsed_ns);

out:
	raw_notअगरier_call_chain(&genpd->घातer_notअगरiers, GENPD_NOTIFY_OFF,
				शून्य);
	वापस 0;
busy:
	raw_notअगरier_call_chain(&genpd->घातer_notअगरiers, GENPD_NOTIFY_ON, शून्य);
	वापस ret;
पूर्ण

/**
 * genpd_queue_घातer_off_work - Queue up the execution of genpd_घातer_off().
 * @genpd: PM करोमुख्य to घातer off.
 *
 * Queue up the execution of genpd_घातer_off() unless it's alपढ़ोy been करोne
 * beक्रमe.
 */
अटल व्योम genpd_queue_घातer_off_work(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	queue_work(pm_wq, &genpd->घातer_off_work);
पूर्ण

/**
 * genpd_घातer_off - Remove घातer from a given PM करोमुख्य.
 * @genpd: PM करोमुख्य to घातer करोwn.
 * @one_dev_on: If invoked from genpd's ->runसमय_suspend|resume() callback, the
 * RPM status of the releated device is in an पूर्णांकermediate state, not yet turned
 * पूर्णांकo RPM_SUSPENDED. This means genpd_घातer_off() must allow one device to not
 * be RPM_SUSPENDED, जबतक it tries to घातer off the PM करोमुख्य.
 *
 * If all of the @genpd's devices have been suspended and all of its subकरोमुख्यs
 * have been घातered करोwn, हटाओ घातer from @genpd.
 */
अटल पूर्णांक genpd_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd, bool one_dev_on,
			   अचिन्हित पूर्णांक depth)
अणु
	काष्ठा pm_करोमुख्य_data *pdd;
	काष्ठा gpd_link *link;
	अचिन्हित पूर्णांक not_suspended = 0;
	पूर्णांक ret;

	/*
	 * Do not try to घातer off the करोमुख्य in the following situations:
	 * (1) The करोमुख्य is alपढ़ोy in the "power off" state.
	 * (2) System suspend is in progress.
	 */
	अगर (!genpd_status_on(genpd) || genpd->prepared_count > 0)
		वापस 0;

	/*
	 * Abort घातer off क्रम the PM करोमुख्य in the following situations:
	 * (1) The करोमुख्य is configured as always on.
	 * (2) When the करोमुख्य has a subकरोमुख्य being घातered on.
	 */
	अगर (genpd_is_always_on(genpd) ||
			genpd_is_rpm_always_on(genpd) ||
			atomic_पढ़ो(&genpd->sd_count) > 0)
		वापस -EBUSY;

	list_क्रम_each_entry(pdd, &genpd->dev_list, list_node) अणु
		क्रमागत pm_qos_flags_status stat;

		stat = dev_pm_qos_flags(pdd->dev, PM_QOS_FLAG_NO_POWER_OFF);
		अगर (stat > PM_QOS_FLAGS_NONE)
			वापस -EBUSY;

		/*
		 * Do not allow PM करोमुख्य to be घातered off, when an IRQ safe
		 * device is part of a non-IRQ safe करोमुख्य.
		 */
		अगर (!pm_runसमय_suspended(pdd->dev) ||
			irq_safe_dev_in_no_sleep_करोमुख्य(pdd->dev, genpd))
			not_suspended++;
	पूर्ण

	अगर (not_suspended > 1 || (not_suspended == 1 && !one_dev_on))
		वापस -EBUSY;

	अगर (genpd->gov && genpd->gov->घातer_करोwn_ok) अणु
		अगर (!genpd->gov->घातer_करोwn_ok(&genpd->करोमुख्य))
			वापस -EAGAIN;
	पूर्ण

	/* Default to shallowest state. */
	अगर (!genpd->gov)
		genpd->state_idx = 0;

	/* Don't घातer off, अगर a child करोमुख्य is रुकोing to घातer on. */
	अगर (atomic_पढ़ो(&genpd->sd_count) > 0)
		वापस -EBUSY;

	ret = _genpd_घातer_off(genpd, true);
	अगर (ret) अणु
		genpd->states[genpd->state_idx].rejected++;
		वापस ret;
	पूर्ण

	genpd->status = GENPD_STATE_OFF;
	genpd_update_accounting(genpd);
	genpd->states[genpd->state_idx].usage++;

	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		genpd_sd_counter_dec(link->parent);
		genpd_lock_nested(link->parent, depth + 1);
		genpd_घातer_off(link->parent, false, depth + 1);
		genpd_unlock(link->parent);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * genpd_घातer_on - Restore घातer to a given PM करोमुख्य and its parents.
 * @genpd: PM करोमुख्य to घातer up.
 * @depth: nesting count क्रम lockdep.
 *
 * Restore घातer to @genpd and all of its parents so that it is possible to
 * resume a device beदीर्घing to it.
 */
अटल पूर्णांक genpd_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd, अचिन्हित पूर्णांक depth)
अणु
	काष्ठा gpd_link *link;
	पूर्णांक ret = 0;

	अगर (genpd_status_on(genpd))
		वापस 0;

	/*
	 * The list is guaranteed not to change जबतक the loop below is being
	 * executed, unless one of the parents' .घातer_on() callbacks fiddles
	 * with it.
	 */
	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		काष्ठा generic_pm_करोमुख्य *parent = link->parent;

		genpd_sd_counter_inc(parent);

		genpd_lock_nested(parent, depth + 1);
		ret = genpd_घातer_on(parent, depth + 1);
		genpd_unlock(parent);

		अगर (ret) अणु
			genpd_sd_counter_dec(parent);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = _genpd_घातer_on(genpd, true);
	अगर (ret)
		जाओ err;

	genpd->status = GENPD_STATE_ON;
	genpd_update_accounting(genpd);

	वापस 0;

 err:
	list_क्रम_each_entry_जारी_reverse(link,
					&genpd->child_links,
					child_node) अणु
		genpd_sd_counter_dec(link->parent);
		genpd_lock_nested(link->parent, depth + 1);
		genpd_घातer_off(link->parent, false, depth + 1);
		genpd_unlock(link->parent);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक genpd_dev_pm_start(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = dev_to_genpd(dev);

	वापस genpd_start_dev(genpd, dev);
पूर्ण

अटल पूर्णांक genpd_dev_pm_qos_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *ptr)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	काष्ठा device *dev;

	gpd_data = container_of(nb, काष्ठा generic_pm_करोमुख्य_data, nb);
	dev = gpd_data->base.dev;

	क्रम (;;) अणु
		काष्ठा generic_pm_करोमुख्य *genpd;
		काष्ठा pm_करोमुख्य_data *pdd;

		spin_lock_irq(&dev->घातer.lock);

		pdd = dev->घातer.subsys_data ?
				dev->घातer.subsys_data->करोमुख्य_data : शून्य;
		अगर (pdd) अणु
			to_gpd_data(pdd)->td.स्थिरraपूर्णांक_changed = true;
			genpd = dev_to_genpd(dev);
		पूर्ण अन्यथा अणु
			genpd = ERR_PTR(-ENODATA);
		पूर्ण

		spin_unlock_irq(&dev->घातer.lock);

		अगर (!IS_ERR(genpd)) अणु
			genpd_lock(genpd);
			genpd->max_off_समय_changed = true;
			genpd_unlock(genpd);
		पूर्ण

		dev = dev->parent;
		अगर (!dev || dev->घातer.ignore_children)
			अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * genpd_घातer_off_work_fn - Power off PM करोमुख्य whose subकरोमुख्य count is 0.
 * @work: Work काष्ठाure used क्रम scheduling the execution of this function.
 */
अटल व्योम genpd_घातer_off_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;

	genpd = container_of(work, काष्ठा generic_pm_करोमुख्य, घातer_off_work);

	genpd_lock(genpd);
	genpd_घातer_off(genpd, false, 0);
	genpd_unlock(genpd);
पूर्ण

/**
 * __genpd_runसमय_suspend - walk the hierarchy of ->runसमय_suspend() callbacks
 * @dev: Device to handle.
 */
अटल पूर्णांक __genpd_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक (*cb)(काष्ठा device *__dev);

	अगर (dev->type && dev->type->pm)
		cb = dev->type->pm->runसमय_suspend;
	अन्यथा अगर (dev->class && dev->class->pm)
		cb = dev->class->pm->runसमय_suspend;
	अन्यथा अगर (dev->bus && dev->bus->pm)
		cb = dev->bus->pm->runसमय_suspend;
	अन्यथा
		cb = शून्य;

	अगर (!cb && dev->driver && dev->driver->pm)
		cb = dev->driver->pm->runसमय_suspend;

	वापस cb ? cb(dev) : 0;
पूर्ण

/**
 * __genpd_runसमय_resume - walk the hierarchy of ->runसमय_resume() callbacks
 * @dev: Device to handle.
 */
अटल पूर्णांक __genpd_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक (*cb)(काष्ठा device *__dev);

	अगर (dev->type && dev->type->pm)
		cb = dev->type->pm->runसमय_resume;
	अन्यथा अगर (dev->class && dev->class->pm)
		cb = dev->class->pm->runसमय_resume;
	अन्यथा अगर (dev->bus && dev->bus->pm)
		cb = dev->bus->pm->runसमय_resume;
	अन्यथा
		cb = शून्य;

	अगर (!cb && dev->driver && dev->driver->pm)
		cb = dev->driver->pm->runसमय_resume;

	वापस cb ? cb(dev) : 0;
पूर्ण

/**
 * genpd_runसमय_suspend - Suspend a device beदीर्घing to I/O PM करोमुख्य.
 * @dev: Device to suspend.
 *
 * Carry out a runसमय suspend of a device under the assumption that its
 * pm_करोमुख्य field poपूर्णांकs to the करोमुख्य member of an object of type
 * काष्ठा generic_pm_करोमुख्य representing a PM करोमुख्य consisting of I/O devices.
 */
अटल पूर्णांक genpd_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	bool (*suspend_ok)(काष्ठा device *__dev);
	काष्ठा gpd_timing_data *td = &dev_gpd_data(dev)->td;
	bool runसमय_pm = pm_runसमय_enabled(dev);
	kसमय_प्रकार समय_start;
	s64 elapsed_ns;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	/*
	 * A runसमय PM centric subप्रणाली/driver may re-use the runसमय PM
	 * callbacks क्रम other purposes than runसमय PM. In those scenarios
	 * runसमय PM is disabled. Under these circumstances, we shall skip
	 * validating/measuring the PM QoS latency.
	 */
	suspend_ok = genpd->gov ? genpd->gov->suspend_ok : शून्य;
	अगर (runसमय_pm && suspend_ok && !suspend_ok(dev))
		वापस -EBUSY;

	/* Measure suspend latency. */
	समय_start = 0;
	अगर (runसमय_pm)
		समय_start = kसमय_get();

	ret = __genpd_runसमय_suspend(dev);
	अगर (ret)
		वापस ret;

	ret = genpd_stop_dev(genpd, dev);
	अगर (ret) अणु
		__genpd_runसमय_resume(dev);
		वापस ret;
	पूर्ण

	/* Update suspend latency value अगर the measured समय exceeds it. */
	अगर (runसमय_pm) अणु
		elapsed_ns = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), समय_start));
		अगर (elapsed_ns > td->suspend_latency_ns) अणु
			td->suspend_latency_ns = elapsed_ns;
			dev_dbg(dev, "suspend latency exceeded, %lld ns\n",
				elapsed_ns);
			genpd->max_off_समय_changed = true;
			td->स्थिरraपूर्णांक_changed = true;
		पूर्ण
	पूर्ण

	/*
	 * If घातer.irq_safe is set, this routine may be run with
	 * IRQs disabled, so suspend only अगर the PM करोमुख्य also is irq_safe.
	 */
	अगर (irq_safe_dev_in_no_sleep_करोमुख्य(dev, genpd))
		वापस 0;

	genpd_lock(genpd);
	genpd_घातer_off(genpd, true, 0);
	genpd_unlock(genpd);

	वापस 0;
पूर्ण

/**
 * genpd_runसमय_resume - Resume a device beदीर्घing to I/O PM करोमुख्य.
 * @dev: Device to resume.
 *
 * Carry out a runसमय resume of a device under the assumption that its
 * pm_करोमुख्य field poपूर्णांकs to the करोमुख्य member of an object of type
 * काष्ठा generic_pm_करोमुख्य representing a PM करोमुख्य consisting of I/O devices.
 */
अटल पूर्णांक genpd_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा gpd_timing_data *td = &dev_gpd_data(dev)->td;
	bool runसमय_pm = pm_runसमय_enabled(dev);
	kसमय_प्रकार समय_start;
	s64 elapsed_ns;
	पूर्णांक ret;
	bool समयd = true;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	/*
	 * As we करोn't घातer off a non IRQ safe करोमुख्य, which holds
	 * an IRQ safe device, we करोn't need to restore घातer to it.
	 */
	अगर (irq_safe_dev_in_no_sleep_करोमुख्य(dev, genpd)) अणु
		समयd = false;
		जाओ out;
	पूर्ण

	genpd_lock(genpd);
	ret = genpd_घातer_on(genpd, 0);
	genpd_unlock(genpd);

	अगर (ret)
		वापस ret;

 out:
	/* Measure resume latency. */
	समय_start = 0;
	अगर (समयd && runसमय_pm)
		समय_start = kसमय_get();

	ret = genpd_start_dev(genpd, dev);
	अगर (ret)
		जाओ err_घातeroff;

	ret = __genpd_runसमय_resume(dev);
	अगर (ret)
		जाओ err_stop;

	/* Update resume latency value अगर the measured समय exceeds it. */
	अगर (समयd && runसमय_pm) अणु
		elapsed_ns = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), समय_start));
		अगर (elapsed_ns > td->resume_latency_ns) अणु
			td->resume_latency_ns = elapsed_ns;
			dev_dbg(dev, "resume latency exceeded, %lld ns\n",
				elapsed_ns);
			genpd->max_off_समय_changed = true;
			td->स्थिरraपूर्णांक_changed = true;
		पूर्ण
	पूर्ण

	वापस 0;

err_stop:
	genpd_stop_dev(genpd, dev);
err_घातeroff:
	अगर (!pm_runसमय_is_irq_safe(dev) || genpd_is_irq_safe(genpd)) अणु
		genpd_lock(genpd);
		genpd_घातer_off(genpd, true, 0);
		genpd_unlock(genpd);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool pd_ignore_unused;
अटल पूर्णांक __init pd_ignore_unused_setup(अक्षर *__unused)
अणु
	pd_ignore_unused = true;
	वापस 1;
पूर्ण
__setup("pd_ignore_unused", pd_ignore_unused_setup);

/**
 * genpd_घातer_off_unused - Power off all PM करोमुख्यs with no devices in use.
 */
अटल पूर्णांक __init genpd_घातer_off_unused(व्योम)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;

	अगर (pd_ignore_unused) अणु
		pr_warn("genpd: Not disabling unused power domains\n");
		वापस 0;
	पूर्ण

	mutex_lock(&gpd_list_lock);

	list_क्रम_each_entry(genpd, &gpd_list, gpd_list_node)
		genpd_queue_घातer_off_work(genpd);

	mutex_unlock(&gpd_list_lock);

	वापस 0;
पूर्ण
late_initcall(genpd_घातer_off_unused);

#अगर_घोषित CONFIG_PM_SLEEP

/**
 * genpd_sync_घातer_off - Synchronously घातer off a PM करोमुख्य and its parents.
 * @genpd: PM करोमुख्य to घातer off, अगर possible.
 * @use_lock: use the lock.
 * @depth: nesting count क्रम lockdep.
 *
 * Check अगर the given PM करोमुख्य can be घातered off (during प्रणाली suspend or
 * hibernation) and करो that अगर so.  Also, in that हाल propagate to its parents.
 *
 * This function is only called in "noirq" and "syscore" stages of प्रणाली घातer
 * transitions. The "noirq" callbacks may be executed asynchronously, thus in
 * these हालs the lock must be held.
 */
अटल व्योम genpd_sync_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd, bool use_lock,
				 अचिन्हित पूर्णांक depth)
अणु
	काष्ठा gpd_link *link;

	अगर (!genpd_status_on(genpd) || genpd_is_always_on(genpd))
		वापस;

	अगर (genpd->suspended_count != genpd->device_count
	    || atomic_पढ़ो(&genpd->sd_count) > 0)
		वापस;

	/* Choose the deepest state when suspending */
	genpd->state_idx = genpd->state_count - 1;
	अगर (_genpd_घातer_off(genpd, false))
		वापस;

	genpd->status = GENPD_STATE_OFF;

	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		genpd_sd_counter_dec(link->parent);

		अगर (use_lock)
			genpd_lock_nested(link->parent, depth + 1);

		genpd_sync_घातer_off(link->parent, use_lock, depth + 1);

		अगर (use_lock)
			genpd_unlock(link->parent);
	पूर्ण
पूर्ण

/**
 * genpd_sync_घातer_on - Synchronously घातer on a PM करोमुख्य and its parents.
 * @genpd: PM करोमुख्य to घातer on.
 * @use_lock: use the lock.
 * @depth: nesting count क्रम lockdep.
 *
 * This function is only called in "noirq" and "syscore" stages of प्रणाली घातer
 * transitions. The "noirq" callbacks may be executed asynchronously, thus in
 * these हालs the lock must be held.
 */
अटल व्योम genpd_sync_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd, bool use_lock,
				अचिन्हित पूर्णांक depth)
अणु
	काष्ठा gpd_link *link;

	अगर (genpd_status_on(genpd))
		वापस;

	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		genpd_sd_counter_inc(link->parent);

		अगर (use_lock)
			genpd_lock_nested(link->parent, depth + 1);

		genpd_sync_घातer_on(link->parent, use_lock, depth + 1);

		अगर (use_lock)
			genpd_unlock(link->parent);
	पूर्ण

	_genpd_घातer_on(genpd, false);
	genpd->status = GENPD_STATE_ON;
पूर्ण

/**
 * genpd_prepare - Start घातer transition of a device in a PM करोमुख्य.
 * @dev: Device to start the transition of.
 *
 * Start a घातer transition of a device (during a प्रणाली-wide घातer transition)
 * under the assumption that its pm_करोमुख्य field poपूर्णांकs to the करोमुख्य member of
 * an object of type काष्ठा generic_pm_करोमुख्य representing a PM करोमुख्य
 * consisting of I/O devices.
 */
अटल पूर्णांक genpd_prepare(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	genpd_lock(genpd);

	अगर (genpd->prepared_count++ == 0)
		genpd->suspended_count = 0;

	genpd_unlock(genpd);

	ret = pm_generic_prepare(dev);
	अगर (ret < 0) अणु
		genpd_lock(genpd);

		genpd->prepared_count--;

		genpd_unlock(genpd);
	पूर्ण

	/* Never वापस 1, as genpd करोn't cope with the direct_complete path. */
	वापस ret >= 0 ? 0 : ret;
पूर्ण

/**
 * genpd_finish_suspend - Completion of suspend or hibernation of device in an
 *   I/O pm करोमुख्य.
 * @dev: Device to suspend.
 * @घातeroff: Specअगरies अगर this is a घातeroff_noirq or suspend_noirq callback.
 *
 * Stop the device and हटाओ घातer from the करोमुख्य अगर all devices in it have
 * been stopped.
 */
अटल पूर्णांक genpd_finish_suspend(काष्ठा device *dev, bool घातeroff)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret = 0;

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	अगर (घातeroff)
		ret = pm_generic_घातeroff_noirq(dev);
	अन्यथा
		ret = pm_generic_suspend_noirq(dev);
	अगर (ret)
		वापस ret;

	अगर (device_wakeup_path(dev) && genpd_is_active_wakeup(genpd))
		वापस 0;

	अगर (genpd->dev_ops.stop && genpd->dev_ops.start &&
	    !pm_runसमय_status_suspended(dev)) अणु
		ret = genpd_stop_dev(genpd, dev);
		अगर (ret) अणु
			अगर (घातeroff)
				pm_generic_restore_noirq(dev);
			अन्यथा
				pm_generic_resume_noirq(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	genpd_lock(genpd);
	genpd->suspended_count++;
	genpd_sync_घातer_off(genpd, true, 0);
	genpd_unlock(genpd);

	वापस 0;
पूर्ण

/**
 * genpd_suspend_noirq - Completion of suspend of device in an I/O PM करोमुख्य.
 * @dev: Device to suspend.
 *
 * Stop the device and हटाओ घातer from the करोमुख्य अगर all devices in it have
 * been stopped.
 */
अटल पूर्णांक genpd_suspend_noirq(काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s()\n", __func__);

	वापस genpd_finish_suspend(dev, false);
पूर्ण

/**
 * genpd_resume_noirq - Start of resume of device in an I/O PM करोमुख्य.
 * @dev: Device to resume.
 *
 * Restore घातer to the device's PM करोमुख्य, अगर necessary, and start the device.
 */
अटल पूर्णांक genpd_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	अगर (device_wakeup_path(dev) && genpd_is_active_wakeup(genpd))
		वापस pm_generic_resume_noirq(dev);

	genpd_lock(genpd);
	genpd_sync_घातer_on(genpd, true, 0);
	genpd->suspended_count--;
	genpd_unlock(genpd);

	अगर (genpd->dev_ops.stop && genpd->dev_ops.start &&
	    !pm_runसमय_status_suspended(dev)) अणु
		ret = genpd_start_dev(genpd, dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_resume_noirq(dev);
पूर्ण

/**
 * genpd_मुक्तze_noirq - Completion of मुक्तzing a device in an I/O PM करोमुख्य.
 * @dev: Device to मुक्तze.
 *
 * Carry out a late मुक्तze of a device under the assumption that its
 * pm_करोमुख्य field poपूर्णांकs to the करोमुख्य member of an object of type
 * काष्ठा generic_pm_करोमुख्य representing a घातer करोमुख्य consisting of I/O
 * devices.
 */
अटल पूर्णांक genpd_मुक्तze_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret = 0;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	ret = pm_generic_मुक्तze_noirq(dev);
	अगर (ret)
		वापस ret;

	अगर (genpd->dev_ops.stop && genpd->dev_ops.start &&
	    !pm_runसमय_status_suspended(dev))
		ret = genpd_stop_dev(genpd, dev);

	वापस ret;
पूर्ण

/**
 * genpd_thaw_noirq - Early thaw of device in an I/O PM करोमुख्य.
 * @dev: Device to thaw.
 *
 * Start the device, unless घातer has been हटाओd from the करोमुख्य alपढ़ोy
 * beक्रमe the प्रणाली transition.
 */
अटल पूर्णांक genpd_thaw_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret = 0;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	अगर (genpd->dev_ops.stop && genpd->dev_ops.start &&
	    !pm_runसमय_status_suspended(dev)) अणु
		ret = genpd_start_dev(genpd, dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_thaw_noirq(dev);
पूर्ण

/**
 * genpd_घातeroff_noirq - Completion of hibernation of device in an
 *   I/O PM करोमुख्य.
 * @dev: Device to घातeroff.
 *
 * Stop the device and हटाओ घातer from the करोमुख्य अगर all devices in it have
 * been stopped.
 */
अटल पूर्णांक genpd_घातeroff_noirq(काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s()\n", __func__);

	वापस genpd_finish_suspend(dev, true);
पूर्ण

/**
 * genpd_restore_noirq - Start of restore of device in an I/O PM करोमुख्य.
 * @dev: Device to resume.
 *
 * Make sure the करोमुख्य will be in the same घातer state as beक्रमe the
 * hibernation the प्रणाली is resuming from and start the device अगर necessary.
 */
अटल पूर्णांक genpd_restore_noirq(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret = 0;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस -EINVAL;

	/*
	 * At this poपूर्णांक suspended_count == 0 means we are being run क्रम the
	 * first समय क्रम the given करोमुख्य in the present cycle.
	 */
	genpd_lock(genpd);
	अगर (genpd->suspended_count++ == 0) अणु
		/*
		 * The boot kernel might put the करोमुख्य पूर्णांकo arbitrary state,
		 * so make it appear as घातered off to genpd_sync_घातer_on(),
		 * so that it tries to घातer it on in हाल it was really off.
		 */
		genpd->status = GENPD_STATE_OFF;
	पूर्ण

	genpd_sync_घातer_on(genpd, true, 0);
	genpd_unlock(genpd);

	अगर (genpd->dev_ops.stop && genpd->dev_ops.start &&
	    !pm_runसमय_status_suspended(dev)) अणु
		ret = genpd_start_dev(genpd, dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_restore_noirq(dev);
पूर्ण

/**
 * genpd_complete - Complete घातer transition of a device in a घातer करोमुख्य.
 * @dev: Device to complete the transition of.
 *
 * Complete a घातer transition of a device (during a प्रणाली-wide घातer
 * transition) under the assumption that its pm_करोमुख्य field poपूर्णांकs to the
 * करोमुख्य member of an object of type काष्ठा generic_pm_करोमुख्य representing
 * a घातer करोमुख्य consisting of I/O devices.
 */
अटल व्योम genpd_complete(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	अगर (IS_ERR(genpd))
		वापस;

	pm_generic_complete(dev);

	genpd_lock(genpd);

	genpd->prepared_count--;
	अगर (!genpd->prepared_count)
		genpd_queue_घातer_off_work(genpd);

	genpd_unlock(genpd);
पूर्ण

अटल व्योम genpd_चयन_state(काष्ठा device *dev, bool suspend)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	bool use_lock;

	genpd = dev_to_genpd_safe(dev);
	अगर (!genpd)
		वापस;

	use_lock = genpd_is_irq_safe(genpd);

	अगर (use_lock)
		genpd_lock(genpd);

	अगर (suspend) अणु
		genpd->suspended_count++;
		genpd_sync_घातer_off(genpd, use_lock, 0);
	पूर्ण अन्यथा अणु
		genpd_sync_घातer_on(genpd, use_lock, 0);
		genpd->suspended_count--;
	पूर्ण

	अगर (use_lock)
		genpd_unlock(genpd);
पूर्ण

/**
 * dev_pm_genpd_suspend - Synchronously try to suspend the genpd क्रम @dev
 * @dev: The device that is attached to the genpd, that can be suspended.
 *
 * This routine should typically be called क्रम a device that needs to be
 * suspended during the syscore suspend phase. It may also be called during
 * suspend-to-idle to suspend a corresponding CPU device that is attached to a
 * genpd.
 */
व्योम dev_pm_genpd_suspend(काष्ठा device *dev)
अणु
	genpd_चयन_state(dev, true);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_suspend);

/**
 * dev_pm_genpd_resume - Synchronously try to resume the genpd क्रम @dev
 * @dev: The device that is attached to the genpd, which needs to be resumed.
 *
 * This routine should typically be called क्रम a device that needs to be resumed
 * during the syscore resume phase. It may also be called during suspend-to-idle
 * to resume a corresponding CPU device that is attached to a genpd.
 */
व्योम dev_pm_genpd_resume(काष्ठा device *dev)
अणु
	genpd_चयन_state(dev, false);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_resume);

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा genpd_prepare		शून्य
#घोषणा genpd_suspend_noirq	शून्य
#घोषणा genpd_resume_noirq	शून्य
#घोषणा genpd_मुक्तze_noirq	शून्य
#घोषणा genpd_thaw_noirq	शून्य
#घोषणा genpd_घातeroff_noirq	शून्य
#घोषणा genpd_restore_noirq	शून्य
#घोषणा genpd_complete		शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा generic_pm_करोमुख्य_data *genpd_alloc_dev_data(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	पूर्णांक ret;

	ret = dev_pm_get_subsys_data(dev);
	अगर (ret)
		वापस ERR_PTR(ret);

	gpd_data = kzalloc(माप(*gpd_data), GFP_KERNEL);
	अगर (!gpd_data) अणु
		ret = -ENOMEM;
		जाओ err_put;
	पूर्ण

	gpd_data->base.dev = dev;
	gpd_data->td.स्थिरraपूर्णांक_changed = true;
	gpd_data->td.effective_स्थिरraपूर्णांक_ns = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT_NS;
	gpd_data->nb.notअगरier_call = genpd_dev_pm_qos_notअगरier;
	gpd_data->next_wakeup = KTIME_MAX;

	spin_lock_irq(&dev->घातer.lock);

	अगर (dev->घातer.subsys_data->करोमुख्य_data) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	dev->घातer.subsys_data->करोमुख्य_data = &gpd_data->base;

	spin_unlock_irq(&dev->घातer.lock);

	वापस gpd_data;

 err_मुक्त:
	spin_unlock_irq(&dev->घातer.lock);
	kमुक्त(gpd_data);
 err_put:
	dev_pm_put_subsys_data(dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम genpd_मुक्त_dev_data(काष्ठा device *dev,
				काष्ठा generic_pm_करोमुख्य_data *gpd_data)
अणु
	spin_lock_irq(&dev->घातer.lock);

	dev->घातer.subsys_data->करोमुख्य_data = शून्य;

	spin_unlock_irq(&dev->घातer.lock);

	kमुक्त(gpd_data);
	dev_pm_put_subsys_data(dev);
पूर्ण

अटल व्योम genpd_update_cpumask(काष्ठा generic_pm_करोमुख्य *genpd,
				 पूर्णांक cpu, bool set, अचिन्हित पूर्णांक depth)
अणु
	काष्ठा gpd_link *link;

	अगर (!genpd_is_cpu_करोमुख्य(genpd))
		वापस;

	list_क्रम_each_entry(link, &genpd->child_links, child_node) अणु
		काष्ठा generic_pm_करोमुख्य *parent = link->parent;

		genpd_lock_nested(parent, depth + 1);
		genpd_update_cpumask(parent, cpu, set, depth + 1);
		genpd_unlock(parent);
	पूर्ण

	अगर (set)
		cpumask_set_cpu(cpu, genpd->cpus);
	अन्यथा
		cpumask_clear_cpu(cpu, genpd->cpus);
पूर्ण

अटल व्योम genpd_set_cpumask(काष्ठा generic_pm_करोमुख्य *genpd, पूर्णांक cpu)
अणु
	अगर (cpu >= 0)
		genpd_update_cpumask(genpd, cpu, true, 0);
पूर्ण

अटल व्योम genpd_clear_cpumask(काष्ठा generic_pm_करोमुख्य *genpd, पूर्णांक cpu)
अणु
	अगर (cpu >= 0)
		genpd_update_cpumask(genpd, cpu, false, 0);
पूर्ण

अटल पूर्णांक genpd_get_cpu(काष्ठा generic_pm_करोमुख्य *genpd, काष्ठा device *dev)
अणु
	पूर्णांक cpu;

	अगर (!genpd_is_cpu_करोमुख्य(genpd))
		वापस -1;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (get_cpu_device(cpu) == dev)
			वापस cpu;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक genpd_add_device(काष्ठा generic_pm_करोमुख्य *genpd, काष्ठा device *dev,
			    काष्ठा device *base_dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	अगर (IS_ERR_OR_शून्य(genpd) || IS_ERR_OR_शून्य(dev))
		वापस -EINVAL;

	gpd_data = genpd_alloc_dev_data(dev);
	अगर (IS_ERR(gpd_data))
		वापस PTR_ERR(gpd_data);

	gpd_data->cpu = genpd_get_cpu(genpd, base_dev);

	ret = genpd->attach_dev ? genpd->attach_dev(genpd, dev) : 0;
	अगर (ret)
		जाओ out;

	genpd_lock(genpd);

	genpd_set_cpumask(genpd, gpd_data->cpu);
	dev_pm_करोमुख्य_set(dev, &genpd->करोमुख्य);

	genpd->device_count++;
	genpd->max_off_समय_changed = true;

	list_add_tail(&gpd_data->base.list_node, &genpd->dev_list);

	genpd_unlock(genpd);
 out:
	अगर (ret)
		genpd_मुक्त_dev_data(dev, gpd_data);
	अन्यथा
		dev_pm_qos_add_notअगरier(dev, &gpd_data->nb,
					DEV_PM_QOS_RESUME_LATENCY);

	वापस ret;
पूर्ण

/**
 * pm_genpd_add_device - Add a device to an I/O PM करोमुख्य.
 * @genpd: PM करोमुख्य to add the device to.
 * @dev: Device to be added.
 */
पूर्णांक pm_genpd_add_device(काष्ठा generic_pm_करोमुख्य *genpd, काष्ठा device *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);
	ret = genpd_add_device(genpd, dev, dev);
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_add_device);

अटल पूर्णांक genpd_हटाओ_device(काष्ठा generic_pm_करोमुख्य *genpd,
			       काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	काष्ठा pm_करोमुख्य_data *pdd;
	पूर्णांक ret = 0;

	dev_dbg(dev, "%s()\n", __func__);

	pdd = dev->घातer.subsys_data->करोमुख्य_data;
	gpd_data = to_gpd_data(pdd);
	dev_pm_qos_हटाओ_notअगरier(dev, &gpd_data->nb,
				   DEV_PM_QOS_RESUME_LATENCY);

	genpd_lock(genpd);

	अगर (genpd->prepared_count > 0) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	genpd->device_count--;
	genpd->max_off_समय_changed = true;

	genpd_clear_cpumask(genpd, gpd_data->cpu);
	dev_pm_करोमुख्य_set(dev, शून्य);

	list_del_init(&pdd->list_node);

	genpd_unlock(genpd);

	अगर (genpd->detach_dev)
		genpd->detach_dev(genpd, dev);

	genpd_मुक्त_dev_data(dev, gpd_data);

	वापस 0;

 out:
	genpd_unlock(genpd);
	dev_pm_qos_add_notअगरier(dev, &gpd_data->nb, DEV_PM_QOS_RESUME_LATENCY);

	वापस ret;
पूर्ण

/**
 * pm_genpd_हटाओ_device - Remove a device from an I/O PM करोमुख्य.
 * @dev: Device to be हटाओd.
 */
पूर्णांक pm_genpd_हटाओ_device(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = dev_to_genpd_safe(dev);

	अगर (!genpd)
		वापस -EINVAL;

	वापस genpd_हटाओ_device(genpd, dev);
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_हटाओ_device);

/**
 * dev_pm_genpd_add_notअगरier - Add a genpd घातer on/off notअगरier क्रम @dev
 *
 * @dev: Device that should be associated with the notअगरier
 * @nb: The notअगरier block to रेजिस्टर
 *
 * Users may call this function to add a genpd घातer on/off notअगरier क्रम an
 * attached @dev. Only one notअगरier per device is allowed. The notअगरier is
 * sent when genpd is घातering on/off the PM करोमुख्य.
 *
 * It is assumed that the user guarantee that the genpd wouldn't be detached
 * जबतक this routine is getting called.
 *
 * Returns 0 on success and negative error values on failures.
 */
पूर्णांक dev_pm_genpd_add_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	पूर्णांक ret;

	genpd = dev_to_genpd_safe(dev);
	अगर (!genpd)
		वापस -ENODEV;

	अगर (WARN_ON(!dev->घातer.subsys_data ||
		     !dev->घातer.subsys_data->करोमुख्य_data))
		वापस -EINVAL;

	gpd_data = to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
	अगर (gpd_data->घातer_nb)
		वापस -EEXIST;

	genpd_lock(genpd);
	ret = raw_notअगरier_chain_रेजिस्टर(&genpd->घातer_notअगरiers, nb);
	genpd_unlock(genpd);

	अगर (ret) अणु
		dev_warn(dev, "failed to add notifier for PM domain %s\n",
			 genpd->name);
		वापस ret;
	पूर्ण

	gpd_data->घातer_nb = nb;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_add_notअगरier);

/**
 * dev_pm_genpd_हटाओ_notअगरier - Remove a genpd घातer on/off notअगरier क्रम @dev
 *
 * @dev: Device that is associated with the notअगरier
 *
 * Users may call this function to हटाओ a genpd घातer on/off notअगरier क्रम an
 * attached @dev.
 *
 * It is assumed that the user guarantee that the genpd wouldn't be detached
 * जबतक this routine is getting called.
 *
 * Returns 0 on success and negative error values on failures.
 */
पूर्णांक dev_pm_genpd_हटाओ_notअगरier(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;
	पूर्णांक ret;

	genpd = dev_to_genpd_safe(dev);
	अगर (!genpd)
		वापस -ENODEV;

	अगर (WARN_ON(!dev->घातer.subsys_data ||
		     !dev->घातer.subsys_data->करोमुख्य_data))
		वापस -EINVAL;

	gpd_data = to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
	अगर (!gpd_data->घातer_nb)
		वापस -ENODEV;

	genpd_lock(genpd);
	ret = raw_notअगरier_chain_unरेजिस्टर(&genpd->घातer_notअगरiers,
					    gpd_data->घातer_nb);
	genpd_unlock(genpd);

	अगर (ret) अणु
		dev_warn(dev, "failed to remove notifier for PM domain %s\n",
			 genpd->name);
		वापस ret;
	पूर्ण

	gpd_data->घातer_nb = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_genpd_हटाओ_notअगरier);

अटल पूर्णांक genpd_add_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
			       काष्ठा generic_pm_करोमुख्य *subकरोमुख्य)
अणु
	काष्ठा gpd_link *link, *itr;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(genpd) || IS_ERR_OR_शून्य(subकरोमुख्य)
	    || genpd == subकरोमुख्य)
		वापस -EINVAL;

	/*
	 * If the करोमुख्य can be घातered on/off in an IRQ safe
	 * context, ensure that the subकरोमुख्य can also be
	 * घातered on/off in that context.
	 */
	अगर (!genpd_is_irq_safe(genpd) && genpd_is_irq_safe(subकरोमुख्य)) अणु
		WARN(1, "Parent %s of subdomain %s must be IRQ safe\n",
				genpd->name, subकरोमुख्य->name);
		वापस -EINVAL;
	पूर्ण

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	genpd_lock(subकरोमुख्य);
	genpd_lock_nested(genpd, SINGLE_DEPTH_NESTING);

	अगर (!genpd_status_on(genpd) && genpd_status_on(subकरोमुख्य)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(itr, &genpd->parent_links, parent_node) अणु
		अगर (itr->child == subकरोमुख्य && itr->parent == genpd) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	link->parent = genpd;
	list_add_tail(&link->parent_node, &genpd->parent_links);
	link->child = subकरोमुख्य;
	list_add_tail(&link->child_node, &subकरोमुख्य->child_links);
	अगर (genpd_status_on(subकरोमुख्य))
		genpd_sd_counter_inc(genpd);

 out:
	genpd_unlock(genpd);
	genpd_unlock(subकरोमुख्य);
	अगर (ret)
		kमुक्त(link);
	वापस ret;
पूर्ण

/**
 * pm_genpd_add_subकरोमुख्य - Add a subकरोमुख्य to an I/O PM करोमुख्य.
 * @genpd: Leader PM करोमुख्य to add the subकरोमुख्य to.
 * @subकरोमुख्य: Subकरोमुख्य to be added.
 */
पूर्णांक pm_genpd_add_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
			   काष्ठा generic_pm_करोमुख्य *subकरोमुख्य)
अणु
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);
	ret = genpd_add_subकरोमुख्य(genpd, subकरोमुख्य);
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_add_subकरोमुख्य);

/**
 * pm_genpd_हटाओ_subकरोमुख्य - Remove a subकरोमुख्य from an I/O PM करोमुख्य.
 * @genpd: Leader PM करोमुख्य to हटाओ the subकरोमुख्य from.
 * @subकरोमुख्य: Subकरोमुख्य to be हटाओd.
 */
पूर्णांक pm_genpd_हटाओ_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
			      काष्ठा generic_pm_करोमुख्य *subकरोमुख्य)
अणु
	काष्ठा gpd_link *l, *link;
	पूर्णांक ret = -EINVAL;

	अगर (IS_ERR_OR_शून्य(genpd) || IS_ERR_OR_शून्य(subकरोमुख्य))
		वापस -EINVAL;

	genpd_lock(subकरोमुख्य);
	genpd_lock_nested(genpd, SINGLE_DEPTH_NESTING);

	अगर (!list_empty(&subकरोमुख्य->parent_links) || subकरोमुख्य->device_count) अणु
		pr_warn("%s: unable to remove subdomain %s\n",
			genpd->name, subकरोमुख्य->name);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(link, l, &genpd->parent_links, parent_node) अणु
		अगर (link->child != subकरोमुख्य)
			जारी;

		list_del(&link->parent_node);
		list_del(&link->child_node);
		kमुक्त(link);
		अगर (genpd_status_on(subकरोमुख्य))
			genpd_sd_counter_dec(genpd);

		ret = 0;
		अवरोध;
	पूर्ण

out:
	genpd_unlock(genpd);
	genpd_unlock(subकरोमुख्य);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_हटाओ_subकरोमुख्य);

अटल व्योम genpd_मुक्त_शेष_घातer_state(काष्ठा genpd_घातer_state *states,
					   अचिन्हित पूर्णांक state_count)
अणु
	kमुक्त(states);
पूर्ण

अटल पूर्णांक genpd_set_शेष_घातer_state(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा genpd_घातer_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	genpd->states = state;
	genpd->state_count = 1;
	genpd->मुक्त_states = genpd_मुक्त_शेष_घातer_state;

	वापस 0;
पूर्ण

अटल व्योम genpd_lock_init(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	अगर (genpd->flags & GENPD_FLAG_IRQ_SAFE) अणु
		spin_lock_init(&genpd->slock);
		genpd->lock_ops = &genpd_spin_ops;
	पूर्ण अन्यथा अणु
		mutex_init(&genpd->mlock);
		genpd->lock_ops = &genpd_mtx_ops;
	पूर्ण
पूर्ण

/**
 * pm_genpd_init - Initialize a generic I/O PM करोमुख्य object.
 * @genpd: PM करोमुख्य object to initialize.
 * @gov: PM करोमुख्य governor to associate with the करोमुख्य (may be शून्य).
 * @is_off: Initial value of the करोमुख्य's घातer_is_off field.
 *
 * Returns 0 on successful initialization, अन्यथा a negative error code.
 */
पूर्णांक pm_genpd_init(काष्ठा generic_pm_करोमुख्य *genpd,
		  काष्ठा dev_घातer_governor *gov, bool is_off)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(genpd))
		वापस -EINVAL;

	INIT_LIST_HEAD(&genpd->parent_links);
	INIT_LIST_HEAD(&genpd->child_links);
	INIT_LIST_HEAD(&genpd->dev_list);
	RAW_INIT_NOTIFIER_HEAD(&genpd->घातer_notअगरiers);
	genpd_lock_init(genpd);
	genpd->gov = gov;
	INIT_WORK(&genpd->घातer_off_work, genpd_घातer_off_work_fn);
	atomic_set(&genpd->sd_count, 0);
	genpd->status = is_off ? GENPD_STATE_OFF : GENPD_STATE_ON;
	genpd->device_count = 0;
	genpd->max_off_समय_ns = -1;
	genpd->max_off_समय_changed = true;
	genpd->provider = शून्य;
	genpd->has_provider = false;
	genpd->accounting_समय = kसमय_get();
	genpd->करोमुख्य.ops.runसमय_suspend = genpd_runसमय_suspend;
	genpd->करोमुख्य.ops.runसमय_resume = genpd_runसमय_resume;
	genpd->करोमुख्य.ops.prepare = genpd_prepare;
	genpd->करोमुख्य.ops.suspend_noirq = genpd_suspend_noirq;
	genpd->करोमुख्य.ops.resume_noirq = genpd_resume_noirq;
	genpd->करोमुख्य.ops.मुक्तze_noirq = genpd_मुक्तze_noirq;
	genpd->करोमुख्य.ops.thaw_noirq = genpd_thaw_noirq;
	genpd->करोमुख्य.ops.घातeroff_noirq = genpd_घातeroff_noirq;
	genpd->करोमुख्य.ops.restore_noirq = genpd_restore_noirq;
	genpd->करोमुख्य.ops.complete = genpd_complete;
	genpd->करोमुख्य.start = genpd_dev_pm_start;

	अगर (genpd->flags & GENPD_FLAG_PM_CLK) अणु
		genpd->dev_ops.stop = pm_clk_suspend;
		genpd->dev_ops.start = pm_clk_resume;
	पूर्ण

	/* Always-on करोमुख्यs must be घातered on at initialization. */
	अगर ((genpd_is_always_on(genpd) || genpd_is_rpm_always_on(genpd)) &&
			!genpd_status_on(genpd))
		वापस -EINVAL;

	अगर (genpd_is_cpu_करोमुख्य(genpd) &&
	    !zalloc_cpumask_var(&genpd->cpus, GFP_KERNEL))
		वापस -ENOMEM;

	/* Use only one "off" state अगर there were no states declared */
	अगर (genpd->state_count == 0) अणु
		ret = genpd_set_शेष_घातer_state(genpd);
		अगर (ret) अणु
			अगर (genpd_is_cpu_करोमुख्य(genpd))
				मुक्त_cpumask_var(genpd->cpus);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (!gov && genpd->state_count > 1) अणु
		pr_warn("%s: no governor for states\n", genpd->name);
	पूर्ण

	device_initialize(&genpd->dev);
	dev_set_name(&genpd->dev, "%s", genpd->name);

	mutex_lock(&gpd_list_lock);
	list_add(&genpd->gpd_list_node, &gpd_list);
	genpd_debug_add(genpd);
	mutex_unlock(&gpd_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_init);

अटल पूर्णांक genpd_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा gpd_link *l, *link;

	अगर (IS_ERR_OR_शून्य(genpd))
		वापस -EINVAL;

	genpd_lock(genpd);

	अगर (genpd->has_provider) अणु
		genpd_unlock(genpd);
		pr_err("Provider present, unable to remove %s\n", genpd->name);
		वापस -EBUSY;
	पूर्ण

	अगर (!list_empty(&genpd->parent_links) || genpd->device_count) अणु
		genpd_unlock(genpd);
		pr_err("%s: unable to remove %s\n", __func__, genpd->name);
		वापस -EBUSY;
	पूर्ण

	list_क्रम_each_entry_safe(link, l, &genpd->child_links, child_node) अणु
		list_del(&link->parent_node);
		list_del(&link->child_node);
		kमुक्त(link);
	पूर्ण

	genpd_debug_हटाओ(genpd);
	list_del(&genpd->gpd_list_node);
	genpd_unlock(genpd);
	cancel_work_sync(&genpd->घातer_off_work);
	अगर (genpd_is_cpu_करोमुख्य(genpd))
		मुक्त_cpumask_var(genpd->cpus);
	अगर (genpd->मुक्त_states)
		genpd->मुक्त_states(genpd->states, genpd->state_count);

	pr_debug("%s: removed %s\n", __func__, genpd->name);

	वापस 0;
पूर्ण

/**
 * pm_genpd_हटाओ - Remove a generic I/O PM करोमुख्य
 * @genpd: Poपूर्णांकer to PM करोमुख्य that is to be हटाओd.
 *
 * To हटाओ the PM करोमुख्य, this function:
 *  - Removes the PM करोमुख्य as a subकरोमुख्य to any parent करोमुख्यs,
 *    अगर it was added.
 *  - Removes the PM करोमुख्य from the list of रेजिस्टरed PM करोमुख्यs.
 *
 * The PM करोमुख्य will only be हटाओd, अगर the associated provider has
 * been हटाओd, it is not a parent to any other PM करोमुख्य and has no
 * devices associated with it.
 */
पूर्णांक pm_genpd_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);
	ret = genpd_हटाओ(genpd);
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_हटाओ);

#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS_OF

/*
 * Device Tree based PM करोमुख्य providers.
 *
 * The code below implements generic device tree based PM करोमुख्य providers that
 * bind device tree nodes with generic PM करोमुख्यs रेजिस्टरed in the प्रणाली.
 *
 * Any driver that रेजिस्टरs generic PM करोमुख्यs and needs to support binding of
 * devices to these करोमुख्यs is supposed to रेजिस्टर a PM करोमुख्य provider, which
 * maps a PM करोमुख्य specअगरier retrieved from the device tree to a PM करोमुख्य.
 *
 * Two simple mapping functions have been provided क्रम convenience:
 *  - genpd_xlate_simple() क्रम 1:1 device tree node to PM करोमुख्य mapping.
 *  - genpd_xlate_onecell() क्रम mapping of multiple PM करोमुख्यs per node by
 *    index.
 */

/**
 * काष्ठा of_genpd_provider - PM करोमुख्य provider registration काष्ठाure
 * @link: Entry in global list of PM करोमुख्य providers
 * @node: Poपूर्णांकer to device tree node of PM करोमुख्य provider
 * @xlate: Provider-specअगरic xlate callback mapping a set of specअगरier cells
 *         पूर्णांकo a PM करोमुख्य.
 * @data: context poपूर्णांकer to be passed पूर्णांकo @xlate callback
 */
काष्ठा of_genpd_provider अणु
	काष्ठा list_head link;
	काष्ठा device_node *node;
	genpd_xlate_t xlate;
	व्योम *data;
पूर्ण;

/* List of रेजिस्टरed PM करोमुख्य providers. */
अटल LIST_HEAD(of_genpd_providers);
/* Mutex to protect the list above. */
अटल DEFINE_MUTEX(of_genpd_mutex);

/**
 * genpd_xlate_simple() - Xlate function क्रम direct node-करोमुख्य mapping
 * @genpdspec: OF phandle args to map पूर्णांकo a PM करोमुख्य
 * @data: xlate function निजी data - poपूर्णांकer to काष्ठा generic_pm_करोमुख्य
 *
 * This is a generic xlate function that can be used to model PM करोमुख्यs that
 * have their own device tree nodes. The निजी data of xlate function needs
 * to be a valid poपूर्णांकer to काष्ठा generic_pm_करोमुख्य.
 */
अटल काष्ठा generic_pm_करोमुख्य *genpd_xlate_simple(
					काष्ठा of_phandle_args *genpdspec,
					व्योम *data)
अणु
	वापस data;
पूर्ण

/**
 * genpd_xlate_onecell() - Xlate function using a single index.
 * @genpdspec: OF phandle args to map पूर्णांकo a PM करोमुख्य
 * @data: xlate function निजी data - poपूर्णांकer to काष्ठा genpd_onecell_data
 *
 * This is a generic xlate function that can be used to model simple PM करोमुख्य
 * controllers that have one device tree node and provide multiple PM करोमुख्यs.
 * A single cell is used as an index पूर्णांकo an array of PM करोमुख्यs specअगरied in
 * the genpd_onecell_data काष्ठा when रेजिस्टरing the provider.
 */
अटल काष्ठा generic_pm_करोमुख्य *genpd_xlate_onecell(
					काष्ठा of_phandle_args *genpdspec,
					व्योम *data)
अणु
	काष्ठा genpd_onecell_data *genpd_data = data;
	अचिन्हित पूर्णांक idx = genpdspec->args[0];

	अगर (genpdspec->args_count != 1)
		वापस ERR_PTR(-EINVAL);

	अगर (idx >= genpd_data->num_करोमुख्यs) अणु
		pr_err("%s: invalid domain index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!genpd_data->करोमुख्यs[idx])
		वापस ERR_PTR(-ENOENT);

	वापस genpd_data->करोमुख्यs[idx];
पूर्ण

/**
 * genpd_add_provider() - Register a PM करोमुख्य provider क्रम a node
 * @np: Device node poपूर्णांकer associated with the PM करोमुख्य provider.
 * @xlate: Callback क्रम decoding PM करोमुख्य from phandle arguments.
 * @data: Context poपूर्णांकer क्रम @xlate callback.
 */
अटल पूर्णांक genpd_add_provider(काष्ठा device_node *np, genpd_xlate_t xlate,
			      व्योम *data)
अणु
	काष्ठा of_genpd_provider *cp;

	cp = kzalloc(माप(*cp), GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	cp->node = of_node_get(np);
	cp->data = data;
	cp->xlate = xlate;
	fwnode_dev_initialized(&np->fwnode, true);

	mutex_lock(&of_genpd_mutex);
	list_add(&cp->link, &of_genpd_providers);
	mutex_unlock(&of_genpd_mutex);
	pr_debug("Added domain provider from %pOF\n", np);

	वापस 0;
पूर्ण

अटल bool genpd_present(स्थिर काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	स्थिर काष्ठा generic_pm_करोमुख्य *gpd;

	list_क्रम_each_entry(gpd, &gpd_list, gpd_list_node)
		अगर (gpd == genpd)
			वापस true;
	वापस false;
पूर्ण

/**
 * of_genpd_add_provider_simple() - Register a simple PM करोमुख्य provider
 * @np: Device node poपूर्णांकer associated with the PM करोमुख्य provider.
 * @genpd: Poपूर्णांकer to PM करोमुख्य associated with the PM करोमुख्य provider.
 */
पूर्णांक of_genpd_add_provider_simple(काष्ठा device_node *np,
				 काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!np || !genpd)
		वापस -EINVAL;

	mutex_lock(&gpd_list_lock);

	अगर (!genpd_present(genpd))
		जाओ unlock;

	genpd->dev.of_node = np;

	/* Parse genpd OPP table */
	अगर (genpd->set_perक्रमmance_state) अणु
		ret = dev_pm_opp_of_add_table(&genpd->dev);
		अगर (ret) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(&genpd->dev, "Failed to add OPP table: %d\n",
					ret);
			जाओ unlock;
		पूर्ण

		/*
		 * Save table क्रम faster processing जबतक setting perक्रमmance
		 * state.
		 */
		genpd->opp_table = dev_pm_opp_get_opp_table(&genpd->dev);
		WARN_ON(IS_ERR(genpd->opp_table));
	पूर्ण

	ret = genpd_add_provider(np, genpd_xlate_simple, genpd);
	अगर (ret) अणु
		अगर (genpd->set_perक्रमmance_state) अणु
			dev_pm_opp_put_opp_table(genpd->opp_table);
			dev_pm_opp_of_हटाओ_table(&genpd->dev);
		पूर्ण

		जाओ unlock;
	पूर्ण

	genpd->provider = &np->fwnode;
	genpd->has_provider = true;

unlock:
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_add_provider_simple);

/**
 * of_genpd_add_provider_onecell() - Register a onecell PM करोमुख्य provider
 * @np: Device node poपूर्णांकer associated with the PM करोमुख्य provider.
 * @data: Poपूर्णांकer to the data associated with the PM करोमुख्य provider.
 */
पूर्णांक of_genpd_add_provider_onecell(काष्ठा device_node *np,
				  काष्ठा genpd_onecell_data *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	अगर (!np || !data)
		वापस -EINVAL;

	mutex_lock(&gpd_list_lock);

	अगर (!data->xlate)
		data->xlate = genpd_xlate_onecell;

	क्रम (i = 0; i < data->num_करोमुख्यs; i++) अणु
		genpd = data->करोमुख्यs[i];

		अगर (!genpd)
			जारी;
		अगर (!genpd_present(genpd))
			जाओ error;

		genpd->dev.of_node = np;

		/* Parse genpd OPP table */
		अगर (genpd->set_perक्रमmance_state) अणु
			ret = dev_pm_opp_of_add_table_indexed(&genpd->dev, i);
			अगर (ret) अणु
				अगर (ret != -EPROBE_DEFER)
					dev_err(&genpd->dev, "Failed to add OPP table for index %d: %d\n",
						i, ret);
				जाओ error;
			पूर्ण

			/*
			 * Save table क्रम faster processing जबतक setting
			 * perक्रमmance state.
			 */
			genpd->opp_table = dev_pm_opp_get_opp_table(&genpd->dev);
			WARN_ON(IS_ERR(genpd->opp_table));
		पूर्ण

		genpd->provider = &np->fwnode;
		genpd->has_provider = true;
	पूर्ण

	ret = genpd_add_provider(np, data->xlate, data);
	अगर (ret < 0)
		जाओ error;

	mutex_unlock(&gpd_list_lock);

	वापस 0;

error:
	जबतक (i--) अणु
		genpd = data->करोमुख्यs[i];

		अगर (!genpd)
			जारी;

		genpd->provider = शून्य;
		genpd->has_provider = false;

		अगर (genpd->set_perक्रमmance_state) अणु
			dev_pm_opp_put_opp_table(genpd->opp_table);
			dev_pm_opp_of_हटाओ_table(&genpd->dev);
		पूर्ण
	पूर्ण

	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_add_provider_onecell);

/**
 * of_genpd_del_provider() - Remove a previously रेजिस्टरed PM करोमुख्य provider
 * @np: Device node poपूर्णांकer associated with the PM करोमुख्य provider
 */
व्योम of_genpd_del_provider(काष्ठा device_node *np)
अणु
	काष्ठा of_genpd_provider *cp, *पंचांगp;
	काष्ठा generic_pm_करोमुख्य *gpd;

	mutex_lock(&gpd_list_lock);
	mutex_lock(&of_genpd_mutex);
	list_क्रम_each_entry_safe(cp, पंचांगp, &of_genpd_providers, link) अणु
		अगर (cp->node == np) अणु
			/*
			 * For each PM करोमुख्य associated with the
			 * provider, set the 'has_provider' to false
			 * so that the PM करोमुख्य can be safely हटाओd.
			 */
			list_क्रम_each_entry(gpd, &gpd_list, gpd_list_node) अणु
				अगर (gpd->provider == &np->fwnode) अणु
					gpd->has_provider = false;

					अगर (!gpd->set_perक्रमmance_state)
						जारी;

					dev_pm_opp_put_opp_table(gpd->opp_table);
					dev_pm_opp_of_हटाओ_table(&gpd->dev);
				पूर्ण
			पूर्ण

			fwnode_dev_initialized(&cp->node->fwnode, false);
			list_del(&cp->link);
			of_node_put(cp->node);
			kमुक्त(cp);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&of_genpd_mutex);
	mutex_unlock(&gpd_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_del_provider);

/**
 * genpd_get_from_provider() - Look-up PM करोमुख्य
 * @genpdspec: OF phandle args to use क्रम look-up
 *
 * Looks क्रम a PM करोमुख्य provider under the node specअगरied by @genpdspec and अगर
 * found, uses xlate function of the provider to map phandle args to a PM
 * करोमुख्य.
 *
 * Returns a valid poपूर्णांकer to काष्ठा generic_pm_करोमुख्य on success or ERR_PTR()
 * on failure.
 */
अटल काष्ठा generic_pm_करोमुख्य *genpd_get_from_provider(
					काष्ठा of_phandle_args *genpdspec)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = ERR_PTR(-ENOENT);
	काष्ठा of_genpd_provider *provider;

	अगर (!genpdspec)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&of_genpd_mutex);

	/* Check अगर we have such a provider in our array */
	list_क्रम_each_entry(provider, &of_genpd_providers, link) अणु
		अगर (provider->node == genpdspec->np)
			genpd = provider->xlate(genpdspec, provider->data);
		अगर (!IS_ERR(genpd))
			अवरोध;
	पूर्ण

	mutex_unlock(&of_genpd_mutex);

	वापस genpd;
पूर्ण

/**
 * of_genpd_add_device() - Add a device to an I/O PM करोमुख्य
 * @genpdspec: OF phandle args to use क्रम look-up PM करोमुख्य
 * @dev: Device to be added.
 *
 * Looks-up an I/O PM करोमुख्य based upon phandle args provided and adds
 * the device to the PM करोमुख्य. Returns a negative error code on failure.
 */
पूर्णांक of_genpd_add_device(काष्ठा of_phandle_args *genpdspec, काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);

	genpd = genpd_get_from_provider(genpdspec);
	अगर (IS_ERR(genpd)) अणु
		ret = PTR_ERR(genpd);
		जाओ out;
	पूर्ण

	ret = genpd_add_device(genpd, dev, dev);

out:
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_add_device);

/**
 * of_genpd_add_subकरोमुख्य - Add a subकरोमुख्य to an I/O PM करोमुख्य.
 * @parent_spec: OF phandle args to use क्रम parent PM करोमुख्य look-up
 * @subकरोमुख्य_spec: OF phandle args to use क्रम subकरोमुख्य look-up
 *
 * Looks-up a parent PM करोमुख्य and subकरोमुख्य based upon phandle args
 * provided and adds the subकरोमुख्य to the parent PM करोमुख्य. Returns a
 * negative error code on failure.
 */
पूर्णांक of_genpd_add_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
			   काष्ठा of_phandle_args *subकरोमुख्य_spec)
अणु
	काष्ठा generic_pm_करोमुख्य *parent, *subकरोमुख्य;
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);

	parent = genpd_get_from_provider(parent_spec);
	अगर (IS_ERR(parent)) अणु
		ret = PTR_ERR(parent);
		जाओ out;
	पूर्ण

	subकरोमुख्य = genpd_get_from_provider(subकरोमुख्य_spec);
	अगर (IS_ERR(subकरोमुख्य)) अणु
		ret = PTR_ERR(subकरोमुख्य);
		जाओ out;
	पूर्ण

	ret = genpd_add_subकरोमुख्य(parent, subकरोमुख्य);

out:
	mutex_unlock(&gpd_list_lock);

	वापस ret == -ENOENT ? -EPROBE_DEFER : ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_add_subकरोमुख्य);

/**
 * of_genpd_हटाओ_subकरोमुख्य - Remove a subकरोमुख्य from an I/O PM करोमुख्य.
 * @parent_spec: OF phandle args to use क्रम parent PM करोमुख्य look-up
 * @subकरोमुख्य_spec: OF phandle args to use क्रम subकरोमुख्य look-up
 *
 * Looks-up a parent PM करोमुख्य and subकरोमुख्य based upon phandle args
 * provided and हटाओs the subकरोमुख्य from the parent PM करोमुख्य. Returns a
 * negative error code on failure.
 */
पूर्णांक of_genpd_हटाओ_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
			      काष्ठा of_phandle_args *subकरोमुख्य_spec)
अणु
	काष्ठा generic_pm_करोमुख्य *parent, *subकरोमुख्य;
	पूर्णांक ret;

	mutex_lock(&gpd_list_lock);

	parent = genpd_get_from_provider(parent_spec);
	अगर (IS_ERR(parent)) अणु
		ret = PTR_ERR(parent);
		जाओ out;
	पूर्ण

	subकरोमुख्य = genpd_get_from_provider(subकरोमुख्य_spec);
	अगर (IS_ERR(subकरोमुख्य)) अणु
		ret = PTR_ERR(subकरोमुख्य);
		जाओ out;
	पूर्ण

	ret = pm_genpd_हटाओ_subकरोमुख्य(parent, subकरोमुख्य);

out:
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_हटाओ_subकरोमुख्य);

/**
 * of_genpd_हटाओ_last - Remove the last PM करोमुख्य रेजिस्टरed क्रम a provider
 * @provider: Poपूर्णांकer to device काष्ठाure associated with provider
 *
 * Find the last PM करोमुख्य that was added by a particular provider and
 * हटाओ this PM करोमुख्य from the list of PM करोमुख्यs. The provider is
 * identअगरied by the 'provider' device काष्ठाure that is passed. The PM
 * करोमुख्य will only be हटाओd, अगर the provider associated with करोमुख्य
 * has been हटाओd.
 *
 * Returns a valid poपूर्णांकer to काष्ठा generic_pm_करोमुख्य on success or
 * ERR_PTR() on failure.
 */
काष्ठा generic_pm_करोमुख्य *of_genpd_हटाओ_last(काष्ठा device_node *np)
अणु
	काष्ठा generic_pm_करोमुख्य *gpd, *पंचांगp, *genpd = ERR_PTR(-ENOENT);
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(np))
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&gpd_list_lock);
	list_क्रम_each_entry_safe(gpd, पंचांगp, &gpd_list, gpd_list_node) अणु
		अगर (gpd->provider == &np->fwnode) अणु
			ret = genpd_हटाओ(gpd);
			genpd = ret ? ERR_PTR(ret) : gpd;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&gpd_list_lock);

	वापस genpd;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_हटाओ_last);

अटल व्योम genpd_release_dev(काष्ठा device *dev)
अणु
	of_node_put(dev->of_node);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा bus_type genpd_bus_type = अणु
	.name		= "genpd",
पूर्ण;

/**
 * genpd_dev_pm_detach - Detach a device from its PM करोमुख्य.
 * @dev: Device to detach.
 * @घातer_off: Currently not used
 *
 * Try to locate a corresponding generic PM करोमुख्य, which the device was
 * attached to previously. If such is found, the device is detached from it.
 */
अटल व्योम genpd_dev_pm_detach(काष्ठा device *dev, bool घातer_off)
अणु
	काष्ठा generic_pm_करोमुख्य *pd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	pd = dev_to_genpd(dev);
	अगर (IS_ERR(pd))
		वापस;

	dev_dbg(dev, "removing from PM domain %s\n", pd->name);

	क्रम (i = 1; i < GENPD_RETRY_MAX_MS; i <<= 1) अणु
		ret = genpd_हटाओ_device(pd, dev);
		अगर (ret != -EAGAIN)
			अवरोध;

		mdelay(i);
		cond_resched();
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev, "failed to remove from PM domain %s: %d",
			pd->name, ret);
		वापस;
	पूर्ण

	/* Check अगर PM करोमुख्य can be घातered off after removing this device. */
	genpd_queue_घातer_off_work(pd);

	/* Unरेजिस्टर the device अगर it was created by genpd. */
	अगर (dev->bus == &genpd_bus_type)
		device_unरेजिस्टर(dev);
पूर्ण

अटल व्योम genpd_dev_pm_sync(काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य *pd;

	pd = dev_to_genpd(dev);
	अगर (IS_ERR(pd))
		वापस;

	genpd_queue_घातer_off_work(pd);
पूर्ण

अटल पूर्णांक __genpd_dev_pm_attach(काष्ठा device *dev, काष्ठा device *base_dev,
				 अचिन्हित पूर्णांक index, bool घातer_on)
अणु
	काष्ठा of_phandle_args pd_args;
	काष्ठा generic_pm_करोमुख्य *pd;
	पूर्णांक ret;

	ret = of_parse_phandle_with_args(dev->of_node, "power-domains",
				"#power-domain-cells", index, &pd_args);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&gpd_list_lock);
	pd = genpd_get_from_provider(&pd_args);
	of_node_put(pd_args.np);
	अगर (IS_ERR(pd)) अणु
		mutex_unlock(&gpd_list_lock);
		dev_dbg(dev, "%s() failed to find PM domain: %ld\n",
			__func__, PTR_ERR(pd));
		वापस driver_deferred_probe_check_state(base_dev);
	पूर्ण

	dev_dbg(dev, "adding to PM domain %s\n", pd->name);

	ret = genpd_add_device(pd, dev, base_dev);
	mutex_unlock(&gpd_list_lock);

	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to add to PM domain %s: %d",
				pd->name, ret);
		वापस ret;
	पूर्ण

	dev->pm_करोमुख्य->detach = genpd_dev_pm_detach;
	dev->pm_करोमुख्य->sync = genpd_dev_pm_sync;

	अगर (घातer_on) अणु
		genpd_lock(pd);
		ret = genpd_घातer_on(pd, 0);
		genpd_unlock(pd);
	पूर्ण

	अगर (ret)
		genpd_हटाओ_device(pd, dev);

	वापस ret ? -EPROBE_DEFER : 1;
पूर्ण

/**
 * genpd_dev_pm_attach - Attach a device to its PM करोमुख्य using DT.
 * @dev: Device to attach.
 *
 * Parse device's OF node to find a PM करोमुख्य specअगरier. If such is found,
 * attaches the device to retrieved pm_करोमुख्य ops.
 *
 * Returns 1 on successfully attached PM करोमुख्य, 0 when the device करोn't need a
 * PM करोमुख्य or when multiple घातer-करोमुख्यs exists क्रम it, अन्यथा a negative error
 * code. Note that अगर a घातer-करोमुख्य exists क्रम the device, but it cannot be
 * found or turned on, then वापस -EPROBE_DEFER to ensure that the device is
 * not probed and to re-try again later.
 */
पूर्णांक genpd_dev_pm_attach(काष्ठा device *dev)
अणु
	अगर (!dev->of_node)
		वापस 0;

	/*
	 * Devices with multiple PM करोमुख्यs must be attached separately, as we
	 * can only attach one PM करोमुख्य per device.
	 */
	अगर (of_count_phandle_with_args(dev->of_node, "power-domains",
				       "#power-domain-cells") != 1)
		वापस 0;

	वापस __genpd_dev_pm_attach(dev, dev, 0, true);
पूर्ण
EXPORT_SYMBOL_GPL(genpd_dev_pm_attach);

/**
 * genpd_dev_pm_attach_by_id - Associate a device with one of its PM करोमुख्यs.
 * @dev: The device used to lookup the PM करोमुख्य.
 * @index: The index of the PM करोमुख्य.
 *
 * Parse device's OF node to find a PM करोमुख्य specअगरier at the provided @index.
 * If such is found, creates a भव device and attaches it to the retrieved
 * pm_करोमुख्य ops. To deal with detaching of the भव device, the ->detach()
 * callback in the काष्ठा dev_pm_करोमुख्य are asचिन्हित to genpd_dev_pm_detach().
 *
 * Returns the created भव device अगर successfully attached PM करोमुख्य, शून्य
 * when the device करोn't need a PM करोमुख्य, अन्यथा an ERR_PTR() in हाल of
 * failures. If a घातer-करोमुख्य exists क्रम the device, but cannot be found or
 * turned on, then ERR_PTR(-EPROBE_DEFER) is वापसed to ensure that the device
 * is not probed and to re-try again later.
 */
काष्ठा device *genpd_dev_pm_attach_by_id(काष्ठा device *dev,
					 अचिन्हित पूर्णांक index)
अणु
	काष्ठा device *virt_dev;
	पूर्णांक num_करोमुख्यs;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस शून्य;

	/* Verअगरy that the index is within a valid range. */
	num_करोमुख्यs = of_count_phandle_with_args(dev->of_node, "power-domains",
						 "#power-domain-cells");
	अगर (index >= num_करोमुख्यs)
		वापस शून्य;

	/* Allocate and रेजिस्टर device on the genpd bus. */
	virt_dev = kzalloc(माप(*virt_dev), GFP_KERNEL);
	अगर (!virt_dev)
		वापस ERR_PTR(-ENOMEM);

	dev_set_name(virt_dev, "genpd:%u:%s", index, dev_name(dev));
	virt_dev->bus = &genpd_bus_type;
	virt_dev->release = genpd_release_dev;
	virt_dev->of_node = of_node_get(dev->of_node);

	ret = device_रेजिस्टर(virt_dev);
	अगर (ret) अणु
		put_device(virt_dev);
		वापस ERR_PTR(ret);
	पूर्ण

	/* Try to attach the device to the PM करोमुख्य at the specअगरied index. */
	ret = __genpd_dev_pm_attach(virt_dev, dev, index, false);
	अगर (ret < 1) अणु
		device_unरेजिस्टर(virt_dev);
		वापस ret ? ERR_PTR(ret) : शून्य;
	पूर्ण

	pm_runसमय_enable(virt_dev);
	genpd_queue_घातer_off_work(dev_to_genpd(virt_dev));

	वापस virt_dev;
पूर्ण
EXPORT_SYMBOL_GPL(genpd_dev_pm_attach_by_id);

/**
 * genpd_dev_pm_attach_by_name - Associate a device with one of its PM करोमुख्यs.
 * @dev: The device used to lookup the PM करोमुख्य.
 * @name: The name of the PM करोमुख्य.
 *
 * Parse device's OF node to find a PM करोमुख्य specअगरier using the
 * घातer-करोमुख्य-names DT property. For further description see
 * genpd_dev_pm_attach_by_id().
 */
काष्ठा device *genpd_dev_pm_attach_by_name(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	पूर्णांक index;

	अगर (!dev->of_node)
		वापस शून्य;

	index = of_property_match_string(dev->of_node, "power-domain-names",
					 name);
	अगर (index < 0)
		वापस शून्य;

	वापस genpd_dev_pm_attach_by_id(dev, index);
पूर्ण

अटल स्थिर काष्ठा of_device_id idle_state_match[] = अणु
	अणु .compatible = "domain-idle-state", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक genpd_parse_state(काष्ठा genpd_घातer_state *genpd_state,
				    काष्ठा device_node *state_node)
अणु
	पूर्णांक err;
	u32 residency;
	u32 entry_latency, निकास_latency;

	err = of_property_पढ़ो_u32(state_node, "entry-latency-us",
						&entry_latency);
	अगर (err) अणु
		pr_debug(" * %pOF missing entry-latency-us property\n",
			 state_node);
		वापस -EINVAL;
	पूर्ण

	err = of_property_पढ़ो_u32(state_node, "exit-latency-us",
						&निकास_latency);
	अगर (err) अणु
		pr_debug(" * %pOF missing exit-latency-us property\n",
			 state_node);
		वापस -EINVAL;
	पूर्ण

	err = of_property_पढ़ो_u32(state_node, "min-residency-us", &residency);
	अगर (!err)
		genpd_state->residency_ns = 1000 * residency;

	genpd_state->घातer_on_latency_ns = 1000 * निकास_latency;
	genpd_state->घातer_off_latency_ns = 1000 * entry_latency;
	genpd_state->fwnode = &state_node->fwnode;

	वापस 0;
पूर्ण

अटल पूर्णांक genpd_iterate_idle_states(काष्ठा device_node *dn,
				     काष्ठा genpd_घातer_state *states)
अणु
	पूर्णांक ret;
	काष्ठा of_phandle_iterator it;
	काष्ठा device_node *np;
	पूर्णांक i = 0;

	ret = of_count_phandle_with_args(dn, "domain-idle-states", शून्य);
	अगर (ret <= 0)
		वापस ret == -ENOENT ? 0 : ret;

	/* Loop over the phandles until all the requested entry is found */
	of_क्रम_each_phandle(&it, ret, dn, "domain-idle-states", शून्य, 0) अणु
		np = it.node;
		अगर (!of_match_node(idle_state_match, np))
			जारी;
		अगर (states) अणु
			ret = genpd_parse_state(&states[i], np);
			अगर (ret) अणु
				pr_err("Parsing idle state node %pOF failed with err %d\n",
				       np, ret);
				of_node_put(np);
				वापस ret;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	वापस i;
पूर्ण

/**
 * of_genpd_parse_idle_states: Return array of idle states क्रम the genpd.
 *
 * @dn: The genpd device node
 * @states: The poपूर्णांकer to which the state array will be saved.
 * @n: The count of elements in the array वापसed from this function.
 *
 * Returns the device states parsed from the OF node. The memory क्रम the states
 * is allocated by this function and is the responsibility of the caller to
 * मुक्त the memory after use. If any or zero compatible करोमुख्य idle states is
 * found it वापसs 0 and in हाल of errors, a negative error code is वापसed.
 */
पूर्णांक of_genpd_parse_idle_states(काष्ठा device_node *dn,
			काष्ठा genpd_घातer_state **states, पूर्णांक *n)
अणु
	काष्ठा genpd_घातer_state *st;
	पूर्णांक ret;

	ret = genpd_iterate_idle_states(dn, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!ret) अणु
		*states = शून्य;
		*n = 0;
		वापस 0;
	पूर्ण

	st = kसुस्मृति(ret, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	ret = genpd_iterate_idle_states(dn, st);
	अगर (ret <= 0) अणु
		kमुक्त(st);
		वापस ret < 0 ? ret : -EINVAL;
	पूर्ण

	*states = st;
	*n = ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_genpd_parse_idle_states);

/**
 * pm_genpd_opp_to_perक्रमmance_state - Gets perक्रमmance state of the genpd from its OPP node.
 *
 * @genpd_dev: Genpd's device क्रम which the perक्रमmance-state needs to be found.
 * @opp: काष्ठा dev_pm_opp of the OPP क्रम which we need to find perक्रमmance
 *	state.
 *
 * Returns perक्रमmance state encoded in the OPP of the genpd. This calls
 * platक्रमm specअगरic genpd->opp_to_perक्रमmance_state() callback to translate
 * घातer करोमुख्य OPP to perक्रमmance state.
 *
 * Returns perक्रमmance state on success and 0 on failure.
 */
अचिन्हित पूर्णांक pm_genpd_opp_to_perक्रमmance_state(काष्ठा device *genpd_dev,
					       काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = शून्य;
	पूर्णांक state;

	genpd = container_of(genpd_dev, काष्ठा generic_pm_करोमुख्य, dev);

	अगर (unlikely(!genpd->opp_to_perक्रमmance_state))
		वापस 0;

	genpd_lock(genpd);
	state = genpd->opp_to_perक्रमmance_state(genpd, opp);
	genpd_unlock(genpd);

	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(pm_genpd_opp_to_perक्रमmance_state);

अटल पूर्णांक __init genpd_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&genpd_bus_type);
पूर्ण
core_initcall(genpd_bus_init);

#पूर्ण_अगर /* CONFIG_PM_GENERIC_DOMAINS_OF */


/***        debugfs support        ***/

#अगर_घोषित CONFIG_DEBUG_FS
/*
 * TODO: This function is a slightly modअगरied version of rtpm_status_show
 * from sysfs.c, so generalize it.
 */
अटल व्योम rtpm_status_str(काष्ठा seq_file *s, काष्ठा device *dev)
अणु
	अटल स्थिर अक्षर * स्थिर status_lookup[] = अणु
		[RPM_ACTIVE] = "active",
		[RPM_RESUMING] = "resuming",
		[RPM_SUSPENDED] = "suspended",
		[RPM_SUSPENDING] = "suspending"
	पूर्ण;
	स्थिर अक्षर *p = "";

	अगर (dev->घातer.runसमय_error)
		p = "error";
	अन्यथा अगर (dev->घातer.disable_depth)
		p = "unsupported";
	अन्यथा अगर (dev->घातer.runसमय_status < ARRAY_SIZE(status_lookup))
		p = status_lookup[dev->घातer.runसमय_status];
	अन्यथा
		WARN_ON(1);

	seq_म_लिखो(s, "%-25s  ", p);
पूर्ण

अटल व्योम perf_status_str(काष्ठा seq_file *s, काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *gpd_data;

	gpd_data = to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
	seq_put_decimal_ull(s, "", gpd_data->perक्रमmance_state);
पूर्ण

अटल पूर्णांक genpd_summary_one(काष्ठा seq_file *s,
			काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	अटल स्थिर अक्षर * स्थिर status_lookup[] = अणु
		[GENPD_STATE_ON] = "on",
		[GENPD_STATE_OFF] = "off"
	पूर्ण;
	काष्ठा pm_करोमुख्य_data *pm_data;
	स्थिर अक्षर *kobj_path;
	काष्ठा gpd_link *link;
	अक्षर state[16];
	पूर्णांक ret;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	अगर (WARN_ON(genpd->status >= ARRAY_SIZE(status_lookup)))
		जाओ निकास;
	अगर (!genpd_status_on(genpd))
		snम_लिखो(state, माप(state), "%s-%u",
			 status_lookup[genpd->status], genpd->state_idx);
	अन्यथा
		snम_लिखो(state, माप(state), "%s",
			 status_lookup[genpd->status]);
	seq_म_लिखो(s, "%-30s  %-50s %u", genpd->name, state, genpd->perक्रमmance_state);

	/*
	 * Modअगरications on the list require holding locks on both
	 * parent and child, so we are safe.
	 * Also genpd->name is immutable.
	 */
	list_क्रम_each_entry(link, &genpd->parent_links, parent_node) अणु
		अगर (list_is_first(&link->parent_node, &genpd->parent_links))
			seq_म_लिखो(s, "\n%48s", " ");
		seq_म_लिखो(s, "%s", link->child->name);
		अगर (!list_is_last(&link->parent_node, &genpd->parent_links))
			seq_माला_दो(s, ", ");
	पूर्ण

	list_क्रम_each_entry(pm_data, &genpd->dev_list, list_node) अणु
		kobj_path = kobject_get_path(&pm_data->dev->kobj,
				genpd_is_irq_safe(genpd) ?
				GFP_ATOMIC : GFP_KERNEL);
		अगर (kobj_path == शून्य)
			जारी;

		seq_म_लिखो(s, "\n    %-50s  ", kobj_path);
		rtpm_status_str(s, pm_data->dev);
		perf_status_str(s, pm_data->dev);
		kमुक्त(kobj_path);
	पूर्ण

	seq_माला_दो(s, "\n");
निकास:
	genpd_unlock(genpd);

	वापस 0;
पूर्ण

अटल पूर्णांक summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	पूर्णांक ret = 0;

	seq_माला_दो(s, "domain                          status          children                           performance\n");
	seq_माला_दो(s, "    /device                                             runtime status\n");
	seq_माला_दो(s, "----------------------------------------------------------------------------------------------\n");

	ret = mutex_lock_पूर्णांकerruptible(&gpd_list_lock);
	अगर (ret)
		वापस -ERESTARTSYS;

	list_क्रम_each_entry(genpd, &gpd_list, gpd_list_node) अणु
		ret = genpd_summary_one(s, genpd);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&gpd_list_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	अटल स्थिर अक्षर * स्थिर status_lookup[] = अणु
		[GENPD_STATE_ON] = "on",
		[GENPD_STATE_OFF] = "off"
	पूर्ण;

	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	अगर (WARN_ON_ONCE(genpd->status >= ARRAY_SIZE(status_lookup)))
		जाओ निकास;

	अगर (genpd->status == GENPD_STATE_OFF)
		seq_म_लिखो(s, "%s-%u\n", status_lookup[genpd->status],
			genpd->state_idx);
	अन्यथा
		seq_म_लिखो(s, "%s\n", status_lookup[genpd->status]);
निकास:
	genpd_unlock(genpd);
	वापस ret;
पूर्ण

अटल पूर्णांक sub_करोमुख्यs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	काष्ठा gpd_link *link;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	list_क्रम_each_entry(link, &genpd->parent_links, parent_node)
		seq_म_लिखो(s, "%s\n", link->child->name);

	genpd_unlock(genpd);
	वापस ret;
पूर्ण

अटल पूर्णांक idle_states_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	seq_माला_दो(s, "State          Time Spent(ms) Usage          Rejected\n");

	क्रम (i = 0; i < genpd->state_count; i++) अणु
		kसमय_प्रकार delta = 0;
		s64 msecs;

		अगर ((genpd->status == GENPD_STATE_OFF) &&
				(genpd->state_idx == i))
			delta = kसमय_sub(kसमय_get(), genpd->accounting_समय);

		msecs = kसमय_प्रकारo_ms(
			kसमय_add(genpd->states[i].idle_समय, delta));
		seq_म_लिखो(s, "S%-13i %-14lld %-14llu %llu\n", i, msecs,
			      genpd->states[i].usage, genpd->states[i].rejected);
	पूर्ण

	genpd_unlock(genpd);
	वापस ret;
पूर्ण

अटल पूर्णांक active_समय_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	kसमय_प्रकार delta = 0;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	अगर (genpd->status == GENPD_STATE_ON)
		delta = kसमय_sub(kसमय_get(), genpd->accounting_समय);

	seq_म_लिखो(s, "%lld ms\n", kसमय_प्रकारo_ms(
				kसमय_add(genpd->on_समय, delta)));

	genpd_unlock(genpd);
	वापस ret;
पूर्ण

अटल पूर्णांक total_idle_समय_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	kसमय_प्रकार delta = 0, total = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	क्रम (i = 0; i < genpd->state_count; i++) अणु

		अगर ((genpd->status == GENPD_STATE_OFF) &&
				(genpd->state_idx == i))
			delta = kसमय_sub(kसमय_get(), genpd->accounting_समय);

		total = kसमय_add(total, genpd->states[i].idle_समय);
	पूर्ण
	total = kसमय_add(total, delta);

	seq_म_लिखो(s, "%lld ms\n", kसमय_प्रकारo_ms(total));

	genpd_unlock(genpd);
	वापस ret;
पूर्ण


अटल पूर्णांक devices_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;
	काष्ठा pm_करोमुख्य_data *pm_data;
	स्थिर अक्षर *kobj_path;
	पूर्णांक ret = 0;

	ret = genpd_lock_पूर्णांकerruptible(genpd);
	अगर (ret)
		वापस -ERESTARTSYS;

	list_क्रम_each_entry(pm_data, &genpd->dev_list, list_node) अणु
		kobj_path = kobject_get_path(&pm_data->dev->kobj,
				genpd_is_irq_safe(genpd) ?
				GFP_ATOMIC : GFP_KERNEL);
		अगर (kobj_path == शून्य)
			जारी;

		seq_म_लिखो(s, "%s\n", kobj_path);
		kमुक्त(kobj_path);
	पूर्ण

	genpd_unlock(genpd);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_state_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = s->निजी;

	अगर (genpd_lock_पूर्णांकerruptible(genpd))
		वापस -ERESTARTSYS;

	seq_म_लिखो(s, "%u\n", genpd->perक्रमmance_state);

	genpd_unlock(genpd);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(summary);
DEFINE_SHOW_ATTRIBUTE(status);
DEFINE_SHOW_ATTRIBUTE(sub_करोमुख्यs);
DEFINE_SHOW_ATTRIBUTE(idle_states);
DEFINE_SHOW_ATTRIBUTE(active_समय);
DEFINE_SHOW_ATTRIBUTE(total_idle_समय);
DEFINE_SHOW_ATTRIBUTE(devices);
DEFINE_SHOW_ATTRIBUTE(perf_state);

अटल व्योम genpd_debug_add(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा dentry *d;

	अगर (!genpd_debugfs_dir)
		वापस;

	d = debugfs_create_dir(genpd->name, genpd_debugfs_dir);

	debugfs_create_file("current_state", 0444,
			    d, genpd, &status_fops);
	debugfs_create_file("sub_domains", 0444,
			    d, genpd, &sub_करोमुख्यs_fops);
	debugfs_create_file("idle_states", 0444,
			    d, genpd, &idle_states_fops);
	debugfs_create_file("active_time", 0444,
			    d, genpd, &active_समय_fops);
	debugfs_create_file("total_idle_time", 0444,
			    d, genpd, &total_idle_समय_fops);
	debugfs_create_file("devices", 0444,
			    d, genpd, &devices_fops);
	अगर (genpd->set_perक्रमmance_state)
		debugfs_create_file("perf_state", 0444,
				    d, genpd, &perf_state_fops);
पूर्ण

अटल पूर्णांक __init genpd_debug_init(व्योम)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;

	genpd_debugfs_dir = debugfs_create_dir("pm_genpd", शून्य);

	debugfs_create_file("pm_genpd_summary", S_IRUGO, genpd_debugfs_dir,
			    शून्य, &summary_fops);

	list_क्रम_each_entry(genpd, &gpd_list, gpd_list_node)
		genpd_debug_add(genpd);

	वापस 0;
पूर्ण
late_initcall(genpd_debug_init);

अटल व्योम __निकास genpd_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(genpd_debugfs_dir);
पूर्ण
__निकासcall(genpd_debug_निकास);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
