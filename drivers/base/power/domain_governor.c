<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/करोमुख्य_governor.c - Governors क्रम device PM करोमुख्यs.
 *
 * Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kसमय.स>

अटल पूर्णांक dev_update_qos_स्थिरraपूर्णांक(काष्ठा device *dev, व्योम *data)
अणु
	s64 *स्थिरraपूर्णांक_ns_p = data;
	s64 स्थिरraपूर्णांक_ns;

	अगर (dev->घातer.subsys_data && dev->घातer.subsys_data->करोमुख्य_data) अणु
		/*
		 * Only take suspend-समय QoS स्थिरraपूर्णांकs of devices पूर्णांकo
		 * account, because स्थिरraपूर्णांकs updated after the device has
		 * been suspended are not guaranteed to be taken पूर्णांकo account
		 * anyway.  In order क्रम them to take effect, the device has to
		 * be resumed and suspended again.
		 */
		स्थिरraपूर्णांक_ns = dev_gpd_data(dev)->td.effective_स्थिरraपूर्णांक_ns;
	पूर्ण अन्यथा अणु
		/*
		 * The child is not in a करोमुख्य and there's no info on its
		 * suspend/resume latencies, so assume them to be negligible and
		 * take its current PM QoS स्थिरraपूर्णांक (that's the only thing
		 * known at this poपूर्णांक anyway).
		 */
		स्थिरraपूर्णांक_ns = dev_pm_qos_पढ़ो_value(dev, DEV_PM_QOS_RESUME_LATENCY);
		स्थिरraपूर्णांक_ns *= NSEC_PER_USEC;
	पूर्ण

	अगर (स्थिरraपूर्णांक_ns < *स्थिरraपूर्णांक_ns_p)
		*स्थिरraपूर्णांक_ns_p = स्थिरraपूर्णांक_ns;

	वापस 0;
पूर्ण

/**
 * शेष_suspend_ok - Default PM करोमुख्य governor routine to suspend devices.
 * @dev: Device to check.
 */
अटल bool शेष_suspend_ok(काष्ठा device *dev)
अणु
	काष्ठा gpd_timing_data *td = &dev_gpd_data(dev)->td;
	अचिन्हित दीर्घ flags;
	s64 स्थिरraपूर्णांक_ns;

	dev_dbg(dev, "%s()\n", __func__);

	spin_lock_irqsave(&dev->घातer.lock, flags);

	अगर (!td->स्थिरraपूर्णांक_changed) अणु
		bool ret = td->cached_suspend_ok;

		spin_unlock_irqrestore(&dev->घातer.lock, flags);
		वापस ret;
	पूर्ण
	td->स्थिरraपूर्णांक_changed = false;
	td->cached_suspend_ok = false;
	td->effective_स्थिरraपूर्णांक_ns = 0;
	स्थिरraपूर्णांक_ns = __dev_pm_qos_resume_latency(dev);

	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	अगर (स्थिरraपूर्णांक_ns == 0)
		वापस false;

	स्थिरraपूर्णांक_ns *= NSEC_PER_USEC;
	/*
	 * We can walk the children without any additional locking, because
	 * they all have been suspended at this poपूर्णांक and their
	 * effective_स्थिरraपूर्णांक_ns fields won't be modअगरied in parallel with us.
	 */
	अगर (!dev->घातer.ignore_children)
		device_क्रम_each_child(dev, &स्थिरraपूर्णांक_ns,
				      dev_update_qos_स्थिरraपूर्णांक);

	अगर (स्थिरraपूर्णांक_ns == PM_QOS_RESUME_LATENCY_NO_CONSTRAINT_NS) अणु
		/* "No restriction", so the device is allowed to suspend. */
		td->effective_स्थिरraपूर्णांक_ns = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT_NS;
		td->cached_suspend_ok = true;
	पूर्ण अन्यथा अगर (स्थिरraपूर्णांक_ns == 0) अणु
		/*
		 * This triggers अगर one of the children that करोn't beदीर्घ to a
		 * करोमुख्य has a zero PM QoS स्थिरraपूर्णांक and it's better not to
		 * suspend then.  effective_स्थिरraपूर्णांक_ns is zero alपढ़ोy and
		 * cached_suspend_ok is false, so bail out.
		 */
		वापस false;
	पूर्ण अन्यथा अणु
		स्थिरraपूर्णांक_ns -= td->suspend_latency_ns +
				td->resume_latency_ns;
		/*
		 * effective_स्थिरraपूर्णांक_ns is zero alपढ़ोy and cached_suspend_ok
		 * is false, so अगर the computed value is not positive, वापस
		 * right away.
		 */
		अगर (स्थिरraपूर्णांक_ns <= 0)
			वापस false;

		td->effective_स्थिरraपूर्णांक_ns = स्थिरraपूर्णांक_ns;
		td->cached_suspend_ok = true;
	पूर्ण

	/*
	 * The children have been suspended alपढ़ोy, so we करोn't need to take
	 * their suspend latencies पूर्णांकo account here.
	 */
	वापस td->cached_suspend_ok;
पूर्ण

अटल व्योम update_करोमुख्य_next_wakeup(काष्ठा generic_pm_करोमुख्य *genpd, kसमय_प्रकार now)
अणु
	kसमय_प्रकार करोमुख्य_wakeup = KTIME_MAX;
	kसमय_प्रकार next_wakeup;
	काष्ठा pm_करोमुख्य_data *pdd;
	काष्ठा gpd_link *link;

	अगर (!(genpd->flags & GENPD_FLAG_MIN_RESIDENCY))
		वापस;

	/*
	 * Devices that have a predictable wakeup pattern, may specअगरy
	 * their next wakeup. Let's find the next wakeup from all the
	 * devices attached to this करोमुख्य and from all the sub-करोमुख्यs.
	 * It is possible that component's a next wakeup may have become
	 * stale when we पढ़ो that here. We will ignore to ensure the करोमुख्य
	 * is able to enter its optimal idle state.
	 */
	list_क्रम_each_entry(pdd, &genpd->dev_list, list_node) अणु
		next_wakeup = to_gpd_data(pdd)->next_wakeup;
		अगर (next_wakeup != KTIME_MAX && !kसमय_beक्रमe(next_wakeup, now))
			अगर (kसमय_beक्रमe(next_wakeup, करोमुख्य_wakeup))
				करोमुख्य_wakeup = next_wakeup;
	पूर्ण

	list_क्रम_each_entry(link, &genpd->parent_links, parent_node) अणु
		next_wakeup = link->child->next_wakeup;
		अगर (next_wakeup != KTIME_MAX && !kसमय_beक्रमe(next_wakeup, now))
			अगर (kसमय_beक्रमe(next_wakeup, करोमुख्य_wakeup))
				करोमुख्य_wakeup = next_wakeup;
	पूर्ण

	genpd->next_wakeup = करोमुख्य_wakeup;
पूर्ण

अटल bool next_wakeup_allows_state(काष्ठा generic_pm_करोमुख्य *genpd,
				     अचिन्हित पूर्णांक state, kसमय_प्रकार now)
अणु
	kसमय_प्रकार करोमुख्य_wakeup = genpd->next_wakeup;
	s64 idle_समय_ns, min_sleep_ns;

	min_sleep_ns = genpd->states[state].घातer_off_latency_ns +
		       genpd->states[state].residency_ns;

	idle_समय_ns = kसमय_प्रकारo_ns(kसमय_sub(करोमुख्य_wakeup, now));

	वापस idle_समय_ns >= min_sleep_ns;
पूर्ण

अटल bool __शेष_घातer_करोwn_ok(काष्ठा dev_pm_करोमुख्य *pd,
				     अचिन्हित पूर्णांक state)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = pd_to_genpd(pd);
	काष्ठा gpd_link *link;
	काष्ठा pm_करोमुख्य_data *pdd;
	s64 min_off_समय_ns;
	s64 off_on_समय_ns;

	off_on_समय_ns = genpd->states[state].घातer_off_latency_ns +
		genpd->states[state].घातer_on_latency_ns;

	min_off_समय_ns = -1;
	/*
	 * Check अगर subकरोमुख्यs can be off क्रम enough समय.
	 *
	 * All subकरोमुख्यs have been घातered off alपढ़ोy at this poपूर्णांक.
	 */
	list_क्रम_each_entry(link, &genpd->parent_links, parent_node) अणु
		काष्ठा generic_pm_करोमुख्य *sd = link->child;
		s64 sd_max_off_ns = sd->max_off_समय_ns;

		अगर (sd_max_off_ns < 0)
			जारी;

		/*
		 * Check अगर the subकरोमुख्य is allowed to be off दीर्घ enough क्रम
		 * the current करोमुख्य to turn off and on (that's how much समय
		 * it will have to रुको worst हाल).
		 */
		अगर (sd_max_off_ns <= off_on_समय_ns)
			वापस false;

		अगर (min_off_समय_ns > sd_max_off_ns || min_off_समय_ns < 0)
			min_off_समय_ns = sd_max_off_ns;
	पूर्ण

	/*
	 * Check अगर the devices in the करोमुख्य can be off enough समय.
	 */
	list_क्रम_each_entry(pdd, &genpd->dev_list, list_node) अणु
		काष्ठा gpd_timing_data *td;
		s64 स्थिरraपूर्णांक_ns;

		/*
		 * Check अगर the device is allowed to be off दीर्घ enough क्रम the
		 * करोमुख्य to turn off and on (that's how much समय it will
		 * have to रुको worst हाल).
		 */
		td = &to_gpd_data(pdd)->td;
		स्थिरraपूर्णांक_ns = td->effective_स्थिरraपूर्णांक_ns;
		/*
		 * Zero means "no suspend at all" and this runs only when all
		 * devices in the करोमुख्य are suspended, so it must be positive.
		 */
		अगर (स्थिरraपूर्णांक_ns == PM_QOS_RESUME_LATENCY_NO_CONSTRAINT_NS)
			जारी;

		अगर (स्थिरraपूर्णांक_ns <= off_on_समय_ns)
			वापस false;

		अगर (min_off_समय_ns > स्थिरraपूर्णांक_ns || min_off_समय_ns < 0)
			min_off_समय_ns = स्थिरraपूर्णांक_ns;
	पूर्ण

	/*
	 * If the computed minimum device off समय is negative, there are no
	 * latency स्थिरraपूर्णांकs, so the करोमुख्य can spend arbitrary समय in the
	 * "off" state.
	 */
	अगर (min_off_समय_ns < 0)
		वापस true;

	/*
	 * The dअगरference between the computed minimum subकरोमुख्य or device off
	 * समय and the समय needed to turn the करोमुख्य on is the maximum
	 * theoretical समय this करोमुख्य can spend in the "off" state.
	 */
	genpd->max_off_समय_ns = min_off_समय_ns -
		genpd->states[state].घातer_on_latency_ns;
	वापस true;
पूर्ण

/**
 * _शेष_घातer_करोwn_ok - Default generic PM करोमुख्य घातer off governor routine.
 * @pd: PM करोमुख्य to check.
 *
 * This routine must be executed under the PM करोमुख्य's lock.
 */
अटल bool _शेष_घातer_करोwn_ok(काष्ठा dev_pm_करोमुख्य *pd, kसमय_प्रकार now)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = pd_to_genpd(pd);
	पूर्णांक state_idx = genpd->state_count - 1;
	काष्ठा gpd_link *link;

	/*
	 * Find the next wakeup from devices that can determine their own wakeup
	 * to find when the करोमुख्य would wakeup and करो it क्रम every device करोwn
	 * the hierarchy. It is not worth जबतक to sleep अगर the state's residency
	 * cannot be met.
	 */
	update_करोमुख्य_next_wakeup(genpd, now);
	अगर ((genpd->flags & GENPD_FLAG_MIN_RESIDENCY) && (genpd->next_wakeup != KTIME_MAX)) अणु
		/* Let's find out the deepest करोमुख्य idle state, the devices prefer */
		जबतक (state_idx >= 0) अणु
			अगर (next_wakeup_allows_state(genpd, state_idx, now)) अणु
				genpd->max_off_समय_changed = true;
				अवरोध;
			पूर्ण
			state_idx--;
		पूर्ण

		अगर (state_idx < 0) अणु
			state_idx = 0;
			genpd->cached_घातer_करोwn_ok = false;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (!genpd->max_off_समय_changed) अणु
		genpd->state_idx = genpd->cached_घातer_करोwn_state_idx;
		वापस genpd->cached_घातer_करोwn_ok;
	पूर्ण

	/*
	 * We have to invalidate the cached results क्रम the parents, so
	 * use the observation that शेष_घातer_करोwn_ok() is not
	 * going to be called क्रम any parent until this instance
	 * वापसs.
	 */
	list_क्रम_each_entry(link, &genpd->child_links, child_node)
		link->parent->max_off_समय_changed = true;

	genpd->max_off_समय_ns = -1;
	genpd->max_off_समय_changed = false;
	genpd->cached_घातer_करोwn_ok = true;

	/*
	 * Find a state to घातer करोwn to, starting from the state
	 * determined by the next wakeup.
	 */
	जबतक (!__शेष_घातer_करोwn_ok(pd, state_idx)) अणु
		अगर (state_idx == 0) अणु
			genpd->cached_घातer_करोwn_ok = false;
			अवरोध;
		पूर्ण
		state_idx--;
	पूर्ण

करोne:
	genpd->state_idx = state_idx;
	genpd->cached_घातer_करोwn_state_idx = genpd->state_idx;
	वापस genpd->cached_घातer_करोwn_ok;
पूर्ण

अटल bool शेष_घातer_करोwn_ok(काष्ठा dev_pm_करोमुख्य *pd)
अणु
	वापस _शेष_घातer_करोwn_ok(pd, kसमय_get());
पूर्ण

अटल bool always_on_घातer_करोwn_ok(काष्ठा dev_pm_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_CPU_IDLE
अटल bool cpu_घातer_करोwn_ok(काष्ठा dev_pm_करोमुख्य *pd)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = pd_to_genpd(pd);
	काष्ठा cpuidle_device *dev;
	kसमय_प्रकार करोमुख्य_wakeup, next_hrसमयr;
	kसमय_प्रकार now = kसमय_get();
	s64 idle_duration_ns;
	पूर्णांक cpu, i;

	/* Validate dev PM QoS स्थिरraपूर्णांकs. */
	अगर (!_शेष_घातer_करोwn_ok(pd, now))
		वापस false;

	अगर (!(genpd->flags & GENPD_FLAG_CPU_DOMAIN))
		वापस true;

	/*
	 * Find the next wakeup क्रम any of the online CPUs within the PM करोमुख्य
	 * and its subकरोमुख्यs. Note, we only need the genpd->cpus, as it alपढ़ोy
	 * contains a mask of all CPUs from subकरोमुख्यs.
	 */
	करोमुख्य_wakeup = kसमय_set(KTIME_SEC_MAX, 0);
	क्रम_each_cpu_and(cpu, genpd->cpus, cpu_online_mask) अणु
		dev = per_cpu(cpuidle_devices, cpu);
		अगर (dev) अणु
			next_hrसमयr = READ_ONCE(dev->next_hrसमयr);
			अगर (kसमय_beक्रमe(next_hrसमयr, करोमुख्य_wakeup))
				करोमुख्य_wakeup = next_hrसमयr;
		पूर्ण
	पूर्ण

	/* The minimum idle duration is from now - until the next wakeup. */
	idle_duration_ns = kसमय_प्रकारo_ns(kसमय_sub(करोमुख्य_wakeup, now));
	अगर (idle_duration_ns <= 0)
		वापस false;

	/*
	 * Find the deepest idle state that has its residency value satisfied
	 * and by also taking पूर्णांकo account the घातer off latency क्रम the state.
	 * Start at the state picked by the dev PM QoS स्थिरraपूर्णांक validation.
	 */
	i = genpd->state_idx;
	करो अणु
		अगर (idle_duration_ns >= (genpd->states[i].residency_ns +
		    genpd->states[i].घातer_off_latency_ns)) अणु
			genpd->state_idx = i;
			वापस true;
		पूर्ण
	पूर्ण जबतक (--i >= 0);

	वापस false;
पूर्ण

काष्ठा dev_घातer_governor pm_करोमुख्य_cpu_gov = अणु
	.suspend_ok = शेष_suspend_ok,
	.घातer_करोwn_ok = cpu_घातer_करोwn_ok,
पूर्ण;
#पूर्ण_अगर

काष्ठा dev_घातer_governor simple_qos_governor = अणु
	.suspend_ok = शेष_suspend_ok,
	.घातer_करोwn_ok = शेष_घातer_करोwn_ok,
पूर्ण;

/**
 * pm_genpd_gov_always_on - A governor implementing an always-on policy
 */
काष्ठा dev_घातer_governor pm_करोमुख्य_always_on_gov = अणु
	.घातer_करोwn_ok = always_on_घातer_करोwn_ok,
	.suspend_ok = शेष_suspend_ok,
पूर्ण;
