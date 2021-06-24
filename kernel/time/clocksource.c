<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This file contains the functions which manage घड़ीsource drivers.
 *
 * Copyright (C) 2004, 2005 IBM, John Stultz (johnstul@us.ibm.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h> /* क्रम spin_unlock_irq() using preempt_count() m68k */
#समावेश <linux/tick.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "tick-internal.h"
#समावेश "timekeeping_internal.h"

/**
 * घड़ीs_calc_mult_shअगरt - calculate mult/shअगरt factors क्रम scaled math of घड़ीs
 * @mult:	poपूर्णांकer to mult variable
 * @shअगरt:	poपूर्णांकer to shअगरt variable
 * @from:	frequency to convert from
 * @to:		frequency to convert to
 * @maxsec:	guaranteed runसमय conversion range in seconds
 *
 * The function evaluates the shअगरt/mult pair क्रम the scaled math
 * operations of घड़ीsources and घड़ीevents.
 *
 * @to and @from are frequency values in HZ. For घड़ी sources @to is
 * NSEC_PER_SEC == 1GHz and @from is the counter frequency. For घड़ी
 * event @to is the counter frequency and @from is NSEC_PER_SEC.
 *
 * The @maxsec conversion range argument controls the समय frame in
 * seconds which must be covered by the runसमय conversion with the
 * calculated mult and shअगरt factors. This guarantees that no 64bit
 * overflow happens when the input value of the conversion is
 * multiplied with the calculated mult factor. Larger ranges may
 * reduce the conversion accuracy by choosing smaller mult and shअगरt
 * factors.
 */
व्योम
घड़ीs_calc_mult_shअगरt(u32 *mult, u32 *shअगरt, u32 from, u32 to, u32 maxsec)
अणु
	u64 पंचांगp;
	u32 sft, sftacc= 32;

	/*
	 * Calculate the shअगरt factor which is limiting the conversion
	 * range:
	 */
	पंचांगp = ((u64)maxsec * from) >> 32;
	जबतक (पंचांगp) अणु
		पंचांगp >>=1;
		sftacc--;
	पूर्ण

	/*
	 * Find the conversion shअगरt/mult pair which has the best
	 * accuracy and fits the maxsec conversion range:
	 */
	क्रम (sft = 32; sft > 0; sft--) अणु
		पंचांगp = (u64) to << sft;
		पंचांगp += from / 2;
		करो_भाग(पंचांगp, from);
		अगर ((पंचांगp >> sftacc) == 0)
			अवरोध;
	पूर्ण
	*mult = पंचांगp;
	*shअगरt = sft;
पूर्ण
EXPORT_SYMBOL_GPL(घड़ीs_calc_mult_shअगरt);

/*[Clocksource पूर्णांकernal variables]---------
 * curr_घड़ीsource:
 *	currently selected घड़ीsource.
 * suspend_घड़ीsource:
 *	used to calculate the suspend समय.
 * घड़ीsource_list:
 *	linked list with the रेजिस्टरed घड़ीsources
 * घड़ीsource_mutex:
 *	protects manipulations to curr_घड़ीsource and the घड़ीsource_list
 * override_name:
 *	Name of the user-specअगरied घड़ीsource.
 */
अटल काष्ठा घड़ीsource *curr_घड़ीsource;
अटल काष्ठा घड़ीsource *suspend_घड़ीsource;
अटल LIST_HEAD(घड़ीsource_list);
अटल DEFINE_MUTEX(घड़ीsource_mutex);
अटल अक्षर override_name[CS_NAME_LEN];
अटल पूर्णांक finished_booting;
अटल u64 suspend_start;

#अगर_घोषित CONFIG_CLOCKSOURCE_WATCHDOG
अटल व्योम घड़ीsource_watchकरोg_work(काष्ठा work_काष्ठा *work);
अटल व्योम घड़ीsource_select(व्योम);

अटल LIST_HEAD(watchकरोg_list);
अटल काष्ठा घड़ीsource *watchकरोg;
अटल काष्ठा समयr_list watchकरोg_समयr;
अटल DECLARE_WORK(watchकरोg_work, घड़ीsource_watchकरोg_work);
अटल DEFINE_SPINLOCK(watchकरोg_lock);
अटल पूर्णांक watchकरोg_running;
अटल atomic_t watchकरोg_reset_pending;

अटल अंतरभूत व्योम घड़ीsource_watchकरोg_lock(अचिन्हित दीर्घ *flags)
अणु
	spin_lock_irqsave(&watchकरोg_lock, *flags);
पूर्ण

अटल अंतरभूत व्योम घड़ीsource_watchकरोg_unlock(अचिन्हित दीर्घ *flags)
अणु
	spin_unlock_irqrestore(&watchकरोg_lock, *flags);
पूर्ण

अटल पूर्णांक घड़ीsource_watchकरोg_kthपढ़ो(व्योम *data);
अटल व्योम __घड़ीsource_change_rating(काष्ठा घड़ीsource *cs, पूर्णांक rating);

/*
 * Interval: 0.5sec Threshold: 0.0625s
 */
#घोषणा WATCHDOG_INTERVAL (HZ >> 1)
#घोषणा WATCHDOG_THRESHOLD (NSEC_PER_SEC >> 4)

अटल व्योम घड़ीsource_watchकरोg_work(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * We cannot directly run घड़ीsource_watchकरोg_kthपढ़ो() here, because
	 * घड़ीsource_select() calls समयkeeping_notअगरy() which uses
	 * stop_machine(). One cannot use stop_machine() from a workqueue() due
	 * lock inversions wrt CPU hotplug.
	 *
	 * Also, we only ever run this work once or twice during the lअगरeसमय
	 * of the kernel, so there is no poपूर्णांक in creating a more permanent
	 * kthपढ़ो क्रम this.
	 *
	 * If kthपढ़ो_run fails the next watchकरोg scan over the
	 * watchकरोg_list will find the unstable घड़ी again.
	 */
	kthपढ़ो_run(घड़ीsource_watchकरोg_kthपढ़ो, शून्य, "kwatchdog");
पूर्ण

अटल व्योम __घड़ीsource_unstable(काष्ठा घड़ीsource *cs)
अणु
	cs->flags &= ~(CLOCK_SOURCE_VALID_FOR_HRES | CLOCK_SOURCE_WATCHDOG);
	cs->flags |= CLOCK_SOURCE_UNSTABLE;

	/*
	 * If the घड़ीsource is रेजिस्टरed घड़ीsource_watchकरोg_kthपढ़ो() will
	 * re-rate and re-select.
	 */
	अगर (list_empty(&cs->list)) अणु
		cs->rating = 0;
		वापस;
	पूर्ण

	अगर (cs->mark_unstable)
		cs->mark_unstable(cs);

	/* kick घड़ीsource_watchकरोg_kthपढ़ो() */
	अगर (finished_booting)
		schedule_work(&watchकरोg_work);
पूर्ण

/**
 * घड़ीsource_mark_unstable - mark घड़ीsource unstable via watchकरोg
 * @cs:		घड़ीsource to be marked unstable
 *
 * This function is called by the x86 TSC code to mark घड़ीsources as unstable;
 * it defers demotion and re-selection to a kthपढ़ो.
 */
व्योम घड़ीsource_mark_unstable(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&watchकरोg_lock, flags);
	अगर (!(cs->flags & CLOCK_SOURCE_UNSTABLE)) अणु
		अगर (!list_empty(&cs->list) && list_empty(&cs->wd_list))
			list_add(&cs->wd_list, &watchकरोg_list);
		__घड़ीsource_unstable(cs);
	पूर्ण
	spin_unlock_irqrestore(&watchकरोg_lock, flags);
पूर्ण

अटल व्योम घड़ीsource_watchकरोg(काष्ठा समयr_list *unused)
अणु
	काष्ठा घड़ीsource *cs;
	u64 csnow, wdnow, cslast, wdlast, delta;
	पूर्णांक64_t wd_nsec, cs_nsec;
	पूर्णांक next_cpu, reset_pending;

	spin_lock(&watchकरोg_lock);
	अगर (!watchकरोg_running)
		जाओ out;

	reset_pending = atomic_पढ़ो(&watchकरोg_reset_pending);

	list_क्रम_each_entry(cs, &watchकरोg_list, wd_list) अणु

		/* Clocksource alपढ़ोy marked unstable? */
		अगर (cs->flags & CLOCK_SOURCE_UNSTABLE) अणु
			अगर (finished_booting)
				schedule_work(&watchकरोg_work);
			जारी;
		पूर्ण

		local_irq_disable();
		csnow = cs->पढ़ो(cs);
		wdnow = watchकरोg->पढ़ो(watchकरोg);
		local_irq_enable();

		/* Clocksource initialized ? */
		अगर (!(cs->flags & CLOCK_SOURCE_WATCHDOG) ||
		    atomic_पढ़ो(&watchकरोg_reset_pending)) अणु
			cs->flags |= CLOCK_SOURCE_WATCHDOG;
			cs->wd_last = wdnow;
			cs->cs_last = csnow;
			जारी;
		पूर्ण

		delta = घड़ीsource_delta(wdnow, cs->wd_last, watchकरोg->mask);
		wd_nsec = घड़ीsource_cyc2ns(delta, watchकरोg->mult,
					     watchकरोg->shअगरt);

		delta = घड़ीsource_delta(csnow, cs->cs_last, cs->mask);
		cs_nsec = घड़ीsource_cyc2ns(delta, cs->mult, cs->shअगरt);
		wdlast = cs->wd_last; /* save these in हाल we prपूर्णांक them */
		cslast = cs->cs_last;
		cs->cs_last = csnow;
		cs->wd_last = wdnow;

		अगर (atomic_पढ़ो(&watchकरोg_reset_pending))
			जारी;

		/* Check the deviation from the watchकरोg घड़ीsource. */
		अगर (असल(cs_nsec - wd_nsec) > WATCHDOG_THRESHOLD) अणु
			pr_warn("timekeeping watchdog on CPU%d: Marking clocksource '%s' as unstable because the skew is too large:\n",
				smp_processor_id(), cs->name);
			pr_warn("                      '%s' wd_now: %llx wd_last: %llx mask: %llx\n",
				watchकरोg->name, wdnow, wdlast, watchकरोg->mask);
			pr_warn("                      '%s' cs_now: %llx cs_last: %llx mask: %llx\n",
				cs->name, csnow, cslast, cs->mask);
			__घड़ीsource_unstable(cs);
			जारी;
		पूर्ण

		अगर (cs == curr_घड़ीsource && cs->tick_stable)
			cs->tick_stable(cs);

		अगर (!(cs->flags & CLOCK_SOURCE_VALID_FOR_HRES) &&
		    (cs->flags & CLOCK_SOURCE_IS_CONTINUOUS) &&
		    (watchकरोg->flags & CLOCK_SOURCE_IS_CONTINUOUS)) अणु
			/* Mark it valid क्रम high-res. */
			cs->flags |= CLOCK_SOURCE_VALID_FOR_HRES;

			/*
			 * घड़ीsource_करोne_booting() will sort it अगर
			 * finished_booting is not set yet.
			 */
			अगर (!finished_booting)
				जारी;

			/*
			 * If this is not the current घड़ीsource let
			 * the watchकरोg thपढ़ो reselect it. Due to the
			 * change to high res this घड़ीsource might
			 * be preferred now. If it is the current
			 * घड़ीsource let the tick code know about
			 * that change.
			 */
			अगर (cs != curr_घड़ीsource) अणु
				cs->flags |= CLOCK_SOURCE_RESELECT;
				schedule_work(&watchकरोg_work);
			पूर्ण अन्यथा अणु
				tick_घड़ी_notअगरy();
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We only clear the watchकरोg_reset_pending, when we did a
	 * full cycle through all घड़ीsources.
	 */
	अगर (reset_pending)
		atomic_dec(&watchकरोg_reset_pending);

	/*
	 * Cycle through CPUs to check अगर the CPUs stay synchronized
	 * to each other.
	 */
	next_cpu = cpumask_next(raw_smp_processor_id(), cpu_online_mask);
	अगर (next_cpu >= nr_cpu_ids)
		next_cpu = cpumask_first(cpu_online_mask);

	/*
	 * Arm समयr अगर not alपढ़ोy pending: could race with concurrent
	 * pair घड़ीsource_stop_watchकरोg() घड़ीsource_start_watchकरोg().
	 */
	अगर (!समयr_pending(&watchकरोg_समयr)) अणु
		watchकरोg_समयr.expires += WATCHDOG_INTERVAL;
		add_समयr_on(&watchकरोg_समयr, next_cpu);
	पूर्ण
out:
	spin_unlock(&watchकरोg_lock);
पूर्ण

अटल अंतरभूत व्योम घड़ीsource_start_watchकरोg(व्योम)
अणु
	अगर (watchकरोg_running || !watchकरोg || list_empty(&watchकरोg_list))
		वापस;
	समयr_setup(&watchकरोg_समयr, घड़ीsource_watchकरोg, 0);
	watchकरोg_समयr.expires = jअगरfies + WATCHDOG_INTERVAL;
	add_समयr_on(&watchकरोg_समयr, cpumask_first(cpu_online_mask));
	watchकरोg_running = 1;
पूर्ण

अटल अंतरभूत व्योम घड़ीsource_stop_watchकरोg(व्योम)
अणु
	अगर (!watchकरोg_running || (watchकरोg && !list_empty(&watchकरोg_list)))
		वापस;
	del_समयr(&watchकरोg_समयr);
	watchकरोg_running = 0;
पूर्ण

अटल अंतरभूत व्योम घड़ीsource_reset_watchकरोg(व्योम)
अणु
	काष्ठा घड़ीsource *cs;

	list_क्रम_each_entry(cs, &watchकरोg_list, wd_list)
		cs->flags &= ~CLOCK_SOURCE_WATCHDOG;
पूर्ण

अटल व्योम घड़ीsource_resume_watchकरोg(व्योम)
अणु
	atomic_inc(&watchकरोg_reset_pending);
पूर्ण

अटल व्योम घड़ीsource_enqueue_watchकरोg(काष्ठा घड़ीsource *cs)
अणु
	INIT_LIST_HEAD(&cs->wd_list);

	अगर (cs->flags & CLOCK_SOURCE_MUST_VERIFY) अणु
		/* cs is a घड़ीsource to be watched. */
		list_add(&cs->wd_list, &watchकरोg_list);
		cs->flags &= ~CLOCK_SOURCE_WATCHDOG;
	पूर्ण अन्यथा अणु
		/* cs is a watchकरोg. */
		अगर (cs->flags & CLOCK_SOURCE_IS_CONTINUOUS)
			cs->flags |= CLOCK_SOURCE_VALID_FOR_HRES;
	पूर्ण
पूर्ण

अटल व्योम घड़ीsource_select_watchकरोg(bool fallback)
अणु
	काष्ठा घड़ीsource *cs, *old_wd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&watchकरोg_lock, flags);
	/* save current watchकरोg */
	old_wd = watchकरोg;
	अगर (fallback)
		watchकरोg = शून्य;

	list_क्रम_each_entry(cs, &घड़ीsource_list, list) अणु
		/* cs is a घड़ीsource to be watched. */
		अगर (cs->flags & CLOCK_SOURCE_MUST_VERIFY)
			जारी;

		/* Skip current अगर we were requested क्रम a fallback. */
		अगर (fallback && cs == old_wd)
			जारी;

		/* Pick the best watchकरोg. */
		अगर (!watchकरोg || cs->rating > watchकरोg->rating)
			watchकरोg = cs;
	पूर्ण
	/* If we failed to find a fallback restore the old one. */
	अगर (!watchकरोg)
		watchकरोg = old_wd;

	/* If we changed the watchकरोg we need to reset cycles. */
	अगर (watchकरोg != old_wd)
		घड़ीsource_reset_watchकरोg();

	/* Check अगर the watchकरोg समयr needs to be started. */
	घड़ीsource_start_watchकरोg();
	spin_unlock_irqrestore(&watchकरोg_lock, flags);
पूर्ण

अटल व्योम घड़ीsource_dequeue_watchकरोg(काष्ठा घड़ीsource *cs)
अणु
	अगर (cs != watchकरोg) अणु
		अगर (cs->flags & CLOCK_SOURCE_MUST_VERIFY) अणु
			/* cs is a watched घड़ीsource. */
			list_del_init(&cs->wd_list);
			/* Check अगर the watchकरोg समयr needs to be stopped. */
			घड़ीsource_stop_watchकरोg();
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __घड़ीsource_watchकरोg_kthपढ़ो(व्योम)
अणु
	काष्ठा घड़ीsource *cs, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक select = 0;

	spin_lock_irqsave(&watchकरोg_lock, flags);
	list_क्रम_each_entry_safe(cs, पंचांगp, &watchकरोg_list, wd_list) अणु
		अगर (cs->flags & CLOCK_SOURCE_UNSTABLE) अणु
			list_del_init(&cs->wd_list);
			__घड़ीsource_change_rating(cs, 0);
			select = 1;
		पूर्ण
		अगर (cs->flags & CLOCK_SOURCE_RESELECT) अणु
			cs->flags &= ~CLOCK_SOURCE_RESELECT;
			select = 1;
		पूर्ण
	पूर्ण
	/* Check अगर the watchकरोg समयr needs to be stopped. */
	घड़ीsource_stop_watchकरोg();
	spin_unlock_irqrestore(&watchकरोg_lock, flags);

	वापस select;
पूर्ण

अटल पूर्णांक घड़ीsource_watchकरोg_kthपढ़ो(व्योम *data)
अणु
	mutex_lock(&घड़ीsource_mutex);
	अगर (__घड़ीsource_watchकरोg_kthपढ़ो())
		घड़ीsource_select();
	mutex_unlock(&घड़ीsource_mutex);
	वापस 0;
पूर्ण

अटल bool घड़ीsource_is_watchकरोg(काष्ठा घड़ीsource *cs)
अणु
	वापस cs == watchकरोg;
पूर्ण

#अन्यथा /* CONFIG_CLOCKSOURCE_WATCHDOG */

अटल व्योम घड़ीsource_enqueue_watchकरोg(काष्ठा घड़ीsource *cs)
अणु
	अगर (cs->flags & CLOCK_SOURCE_IS_CONTINUOUS)
		cs->flags |= CLOCK_SOURCE_VALID_FOR_HRES;
पूर्ण

अटल व्योम घड़ीsource_select_watchकरोg(bool fallback) अणु पूर्ण
अटल अंतरभूत व्योम घड़ीsource_dequeue_watchकरोg(काष्ठा घड़ीsource *cs) अणु पूर्ण
अटल अंतरभूत व्योम घड़ीsource_resume_watchकरोg(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक __घड़ीsource_watchकरोg_kthपढ़ो(व्योम) अणु वापस 0; पूर्ण
अटल bool घड़ीsource_is_watchकरोg(काष्ठा घड़ीsource *cs) अणु वापस false; पूर्ण
व्योम घड़ीsource_mark_unstable(काष्ठा घड़ीsource *cs) अणु पूर्ण

अटल अंतरभूत व्योम घड़ीsource_watchकरोg_lock(अचिन्हित दीर्घ *flags) अणु पूर्ण
अटल अंतरभूत व्योम घड़ीsource_watchकरोg_unlock(अचिन्हित दीर्घ *flags) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_CLOCKSOURCE_WATCHDOG */

अटल bool घड़ीsource_is_suspend(काष्ठा घड़ीsource *cs)
अणु
	वापस cs == suspend_घड़ीsource;
पूर्ण

अटल व्योम __घड़ीsource_suspend_select(काष्ठा घड़ीsource *cs)
अणु
	/*
	 * Skip the घड़ीsource which will be stopped in suspend state.
	 */
	अगर (!(cs->flags & CLOCK_SOURCE_SUSPEND_NONSTOP))
		वापस;

	/*
	 * The nonstop घड़ीsource can be selected as the suspend घड़ीsource to
	 * calculate the suspend समय, so it should not supply suspend/resume
	 * पूर्णांकerfaces to suspend the nonstop घड़ीsource when प्रणाली suspends.
	 */
	अगर (cs->suspend || cs->resume) अणु
		pr_warn("Nonstop clocksource %s should not supply suspend/resume interfaces\n",
			cs->name);
	पूर्ण

	/* Pick the best rating. */
	अगर (!suspend_घड़ीsource || cs->rating > suspend_घड़ीsource->rating)
		suspend_घड़ीsource = cs;
पूर्ण

/**
 * घड़ीsource_suspend_select - Select the best घड़ीsource क्रम suspend timing
 * @fallback:	अगर select a fallback घड़ीsource
 */
अटल व्योम घड़ीsource_suspend_select(bool fallback)
अणु
	काष्ठा घड़ीsource *cs, *old_suspend;

	old_suspend = suspend_घड़ीsource;
	अगर (fallback)
		suspend_घड़ीsource = शून्य;

	list_क्रम_each_entry(cs, &घड़ीsource_list, list) अणु
		/* Skip current अगर we were requested क्रम a fallback. */
		अगर (fallback && cs == old_suspend)
			जारी;

		__घड़ीsource_suspend_select(cs);
	पूर्ण
पूर्ण

/**
 * घड़ीsource_start_suspend_timing - Start measuring the suspend timing
 * @cs:			current घड़ीsource from समयkeeping
 * @start_cycles:	current cycles from समयkeeping
 *
 * This function will save the start cycle values of suspend समयr to calculate
 * the suspend समय when resuming प्रणाली.
 *
 * This function is called late in the suspend process from समयkeeping_suspend(),
 * that means processes are frozen, non-boot cpus and पूर्णांकerrupts are disabled
 * now. It is thereक्रमe possible to start the suspend समयr without taking the
 * घड़ीsource mutex.
 */
व्योम घड़ीsource_start_suspend_timing(काष्ठा घड़ीsource *cs, u64 start_cycles)
अणु
	अगर (!suspend_घड़ीsource)
		वापस;

	/*
	 * If current घड़ीsource is the suspend समयr, we should use the
	 * tkr_mono.cycle_last value as suspend_start to aव्योम same पढ़ोing
	 * from suspend समयr.
	 */
	अगर (घड़ीsource_is_suspend(cs)) अणु
		suspend_start = start_cycles;
		वापस;
	पूर्ण

	अगर (suspend_घड़ीsource->enable &&
	    suspend_घड़ीsource->enable(suspend_घड़ीsource)) अणु
		pr_warn_once("Failed to enable the non-suspend-able clocksource.\n");
		वापस;
	पूर्ण

	suspend_start = suspend_घड़ीsource->पढ़ो(suspend_घड़ीsource);
पूर्ण

/**
 * घड़ीsource_stop_suspend_timing - Stop measuring the suspend timing
 * @cs:		current घड़ीsource from समयkeeping
 * @cycle_now:	current cycles from समयkeeping
 *
 * This function will calculate the suspend समय from suspend समयr.
 *
 * Returns nanoseconds since suspend started, 0 अगर no usable suspend घड़ीsource.
 *
 * This function is called early in the resume process from समयkeeping_resume(),
 * that means there is only one cpu, no processes are running and the पूर्णांकerrupts
 * are disabled. It is thereक्रमe possible to stop the suspend समयr without
 * taking the घड़ीsource mutex.
 */
u64 घड़ीsource_stop_suspend_timing(काष्ठा घड़ीsource *cs, u64 cycle_now)
अणु
	u64 now, delta, nsec = 0;

	अगर (!suspend_घड़ीsource)
		वापस 0;

	/*
	 * If current घड़ीsource is the suspend समयr, we should use the
	 * tkr_mono.cycle_last value from समयkeeping as current cycle to
	 * aव्योम same पढ़ोing from suspend समयr.
	 */
	अगर (घड़ीsource_is_suspend(cs))
		now = cycle_now;
	अन्यथा
		now = suspend_घड़ीsource->पढ़ो(suspend_घड़ीsource);

	अगर (now > suspend_start) अणु
		delta = घड़ीsource_delta(now, suspend_start,
					  suspend_घड़ीsource->mask);
		nsec = mul_u64_u32_shr(delta, suspend_घड़ीsource->mult,
				       suspend_घड़ीsource->shअगरt);
	पूर्ण

	/*
	 * Disable the suspend समयr to save घातer अगर current घड़ीsource is
	 * not the suspend समयr.
	 */
	अगर (!घड़ीsource_is_suspend(cs) && suspend_घड़ीsource->disable)
		suspend_घड़ीsource->disable(suspend_घड़ीsource);

	वापस nsec;
पूर्ण

/**
 * घड़ीsource_suspend - suspend the घड़ीsource(s)
 */
व्योम घड़ीsource_suspend(व्योम)
अणु
	काष्ठा घड़ीsource *cs;

	list_क्रम_each_entry_reverse(cs, &घड़ीsource_list, list)
		अगर (cs->suspend)
			cs->suspend(cs);
पूर्ण

/**
 * घड़ीsource_resume - resume the घड़ीsource(s)
 */
व्योम घड़ीsource_resume(व्योम)
अणु
	काष्ठा घड़ीsource *cs;

	list_क्रम_each_entry(cs, &घड़ीsource_list, list)
		अगर (cs->resume)
			cs->resume(cs);

	घड़ीsource_resume_watchकरोg();
पूर्ण

/**
 * घड़ीsource_touch_watchकरोg - Update watchकरोg
 *
 * Update the watchकरोg after exception contexts such as kgdb so as not
 * to incorrectly trip the watchकरोg. This might fail when the kernel
 * was stopped in code which holds watchकरोg_lock.
 */
व्योम घड़ीsource_touch_watchकरोg(व्योम)
अणु
	घड़ीsource_resume_watchकरोg();
पूर्ण

/**
 * घड़ीsource_max_adjusपंचांगent- Returns max adjusपंचांगent amount
 * @cs:         Poपूर्णांकer to घड़ीsource
 *
 */
अटल u32 घड़ीsource_max_adjusपंचांगent(काष्ठा घड़ीsource *cs)
अणु
	u64 ret;
	/*
	 * We won't try to correct क्रम more than 11% adjusपंचांगents (110,000 ppm),
	 */
	ret = (u64)cs->mult * 11;
	करो_भाग(ret,100);
	वापस (u32)ret;
पूर्ण

/**
 * घड़ीs_calc_max_nsecs - Returns maximum nanoseconds that can be converted
 * @mult:	cycle to nanosecond multiplier
 * @shअगरt:	cycle to nanosecond भागisor (घातer of two)
 * @maxadj:	maximum adjusपंचांगent value to mult (~11%)
 * @mask:	biपंचांगask क्रम two's complement subtraction of non 64 bit counters
 * @max_cyc:	maximum cycle value beक्रमe potential overflow (करोes not include
 *		any safety margin)
 *
 * NOTE: This function includes a safety margin of 50%, in other words, we
 * वापस half the number of nanoseconds the hardware counter can technically
 * cover. This is करोne so that we can potentially detect problems caused by
 * delayed समयrs or bad hardware, which might result in समय पूर्णांकervals that
 * are larger than what the math used can handle without overflows.
 */
u64 घड़ीs_calc_max_nsecs(u32 mult, u32 shअगरt, u32 maxadj, u64 mask, u64 *max_cyc)
अणु
	u64 max_nsecs, max_cycles;

	/*
	 * Calculate the maximum number of cycles that we can pass to the
	 * cyc2ns() function without overflowing a 64-bit result.
	 */
	max_cycles = ULदीर्घ_उच्च;
	करो_भाग(max_cycles, mult+maxadj);

	/*
	 * The actual maximum number of cycles we can defer the घड़ीsource is
	 * determined by the minimum of max_cycles and mask.
	 * Note: Here we subtract the maxadj to make sure we करोn't sleep क्रम
	 * too दीर्घ अगर there's a large negative adjusपंचांगent.
	 */
	max_cycles = min(max_cycles, mask);
	max_nsecs = घड़ीsource_cyc2ns(max_cycles, mult - maxadj, shअगरt);

	/* वापस the max_cycles value as well अगर requested */
	अगर (max_cyc)
		*max_cyc = max_cycles;

	/* Return 50% of the actual maximum, so we can detect bad values */
	max_nsecs >>= 1;

	वापस max_nsecs;
पूर्ण

/**
 * घड़ीsource_update_max_deferment - Updates the घड़ीsource max_idle_ns & max_cycles
 * @cs:         Poपूर्णांकer to घड़ीsource to be updated
 *
 */
अटल अंतरभूत व्योम घड़ीsource_update_max_deferment(काष्ठा घड़ीsource *cs)
अणु
	cs->max_idle_ns = घड़ीs_calc_max_nsecs(cs->mult, cs->shअगरt,
						cs->maxadj, cs->mask,
						&cs->max_cycles);
पूर्ण

अटल काष्ठा घड़ीsource *घड़ीsource_find_best(bool oneshot, bool skipcur)
अणु
	काष्ठा घड़ीsource *cs;

	अगर (!finished_booting || list_empty(&घड़ीsource_list))
		वापस शून्य;

	/*
	 * We pick the घड़ीsource with the highest rating. If oneshot
	 * mode is active, we pick the highres valid घड़ीsource with
	 * the best rating.
	 */
	list_क्रम_each_entry(cs, &घड़ीsource_list, list) अणु
		अगर (skipcur && cs == curr_घड़ीsource)
			जारी;
		अगर (oneshot && !(cs->flags & CLOCK_SOURCE_VALID_FOR_HRES))
			जारी;
		वापस cs;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __घड़ीsource_select(bool skipcur)
अणु
	bool oneshot = tick_oneshot_mode_active();
	काष्ठा घड़ीsource *best, *cs;

	/* Find the best suitable घड़ीsource */
	best = घड़ीsource_find_best(oneshot, skipcur);
	अगर (!best)
		वापस;

	अगर (!म_माप(override_name))
		जाओ found;

	/* Check क्रम the override घड़ीsource. */
	list_क्रम_each_entry(cs, &घड़ीsource_list, list) अणु
		अगर (skipcur && cs == curr_घड़ीsource)
			जारी;
		अगर (म_भेद(cs->name, override_name) != 0)
			जारी;
		/*
		 * Check to make sure we करोn't चयन to a non-highres
		 * capable घड़ीsource अगर the tick code is in oneshot
		 * mode (highres or nohz)
		 */
		अगर (!(cs->flags & CLOCK_SOURCE_VALID_FOR_HRES) && oneshot) अणु
			/* Override घड़ीsource cannot be used. */
			अगर (cs->flags & CLOCK_SOURCE_UNSTABLE) अणु
				pr_warn("Override clocksource %s is unstable and not HRT compatible - cannot switch while in HRT/NOHZ mode\n",
					cs->name);
				override_name[0] = 0;
			पूर्ण अन्यथा अणु
				/*
				 * The override cannot be currently verअगरied.
				 * Deferring to let the watchकरोg check.
				 */
				pr_info("Override clocksource %s is not currently HRT compatible - deferring\n",
					cs->name);
			पूर्ण
		पूर्ण अन्यथा
			/* Override घड़ीsource can be used. */
			best = cs;
		अवरोध;
	पूर्ण

found:
	अगर (curr_घड़ीsource != best && !समयkeeping_notअगरy(best)) अणु
		pr_info("Switched to clocksource %s\n", best->name);
		curr_घड़ीsource = best;
	पूर्ण
पूर्ण

/**
 * घड़ीsource_select - Select the best घड़ीsource available
 *
 * Private function. Must hold घड़ीsource_mutex when called.
 *
 * Select the घड़ीsource with the best rating, or the घड़ीsource,
 * which is selected by userspace override.
 */
अटल व्योम घड़ीsource_select(व्योम)
अणु
	__घड़ीsource_select(false);
पूर्ण

अटल व्योम घड़ीsource_select_fallback(व्योम)
अणु
	__घड़ीsource_select(true);
पूर्ण

/*
 * घड़ीsource_करोne_booting - Called near the end of core bootup
 *
 * Hack to aव्योम lots of घड़ीsource churn at boot समय.
 * We use fs_initcall because we want this to start beक्रमe
 * device_initcall but after subsys_initcall.
 */
अटल पूर्णांक __init घड़ीsource_करोne_booting(व्योम)
अणु
	mutex_lock(&घड़ीsource_mutex);
	curr_घड़ीsource = घड़ीsource_शेष_घड़ी();
	finished_booting = 1;
	/*
	 * Run the watchकरोg first to eliminate unstable घड़ी sources
	 */
	__घड़ीsource_watchकरोg_kthपढ़ो();
	घड़ीsource_select();
	mutex_unlock(&घड़ीsource_mutex);
	वापस 0;
पूर्ण
fs_initcall(घड़ीsource_करोne_booting);

/*
 * Enqueue the घड़ीsource sorted by rating
 */
अटल व्योम घड़ीsource_enqueue(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा list_head *entry = &घड़ीsource_list;
	काष्ठा घड़ीsource *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &घड़ीsource_list, list) अणु
		/* Keep track of the place, where to insert */
		अगर (पंचांगp->rating < cs->rating)
			अवरोध;
		entry = &पंचांगp->list;
	पूर्ण
	list_add(&cs->list, entry);
पूर्ण

/**
 * __घड़ीsource_update_freq_scale - Used update घड़ीsource with new freq
 * @cs:		घड़ीsource to be रेजिस्टरed
 * @scale:	Scale factor multiplied against freq to get घड़ीsource hz
 * @freq:	घड़ीsource frequency (cycles per second) भागided by scale
 *
 * This should only be called from the घड़ीsource->enable() method.
 *
 * This *SHOULD NOT* be called directly! Please use the
 * __घड़ीsource_update_freq_hz() or __घड़ीsource_update_freq_khz() helper
 * functions.
 */
व्योम __घड़ीsource_update_freq_scale(काष्ठा घड़ीsource *cs, u32 scale, u32 freq)
अणु
	u64 sec;

	/*
	 * Default घड़ीsources are *special* and self-define their mult/shअगरt.
	 * But, you're not special, so you should specअगरy a freq value.
	 */
	अगर (freq) अणु
		/*
		 * Calc the maximum number of seconds which we can run beक्रमe
		 * wrapping around. For घड़ीsources which have a mask > 32-bit
		 * we need to limit the max sleep समय to have a good
		 * conversion precision. 10 minutes is still a reasonable
		 * amount. That results in a shअगरt value of 24 क्रम a
		 * घड़ीsource with mask >= 40-bit and f >= 4GHz. That maps to
		 * ~ 0.06ppm granularity क्रम NTP.
		 */
		sec = cs->mask;
		करो_भाग(sec, freq);
		करो_भाग(sec, scale);
		अगर (!sec)
			sec = 1;
		अन्यथा अगर (sec > 600 && cs->mask > अच_पूर्णांक_उच्च)
			sec = 600;

		घड़ीs_calc_mult_shअगरt(&cs->mult, &cs->shअगरt, freq,
				       NSEC_PER_SEC / scale, sec * scale);
	पूर्ण
	/*
	 * Ensure घड़ीsources that have large 'mult' values don't overflow
	 * when adjusted.
	 */
	cs->maxadj = घड़ीsource_max_adjusपंचांगent(cs);
	जबतक (freq && ((cs->mult + cs->maxadj < cs->mult)
		|| (cs->mult - cs->maxadj > cs->mult))) अणु
		cs->mult >>= 1;
		cs->shअगरt--;
		cs->maxadj = घड़ीsource_max_adjusपंचांगent(cs);
	पूर्ण

	/*
	 * Only warn क्रम *special* घड़ीsources that self-define
	 * their mult/shअगरt values and करोn't specअगरy a freq.
	 */
	WARN_ONCE(cs->mult + cs->maxadj < cs->mult,
		"timekeeping: Clocksource %s might overflow on 11%% adjustment\n",
		cs->name);

	घड़ीsource_update_max_deferment(cs);

	pr_info("%s: mask: 0x%llx max_cycles: 0x%llx, max_idle_ns: %lld ns\n",
		cs->name, cs->mask, cs->max_cycles, cs->max_idle_ns);
पूर्ण
EXPORT_SYMBOL_GPL(__घड़ीsource_update_freq_scale);

/**
 * __घड़ीsource_रेजिस्टर_scale - Used to install new घड़ीsources
 * @cs:		घड़ीsource to be रेजिस्टरed
 * @scale:	Scale factor multiplied against freq to get घड़ीsource hz
 * @freq:	घड़ीsource frequency (cycles per second) भागided by scale
 *
 * Returns -EBUSY अगर registration fails, zero otherwise.
 *
 * This *SHOULD NOT* be called directly! Please use the
 * घड़ीsource_रेजिस्टर_hz() or घड़ीsource_रेजिस्टर_khz helper functions.
 */
पूर्णांक __घड़ीsource_रेजिस्टर_scale(काष्ठा घड़ीsource *cs, u32 scale, u32 freq)
अणु
	अचिन्हित दीर्घ flags;

	घड़ीsource_arch_init(cs);

	अगर (WARN_ON_ONCE((अचिन्हित पूर्णांक)cs->id >= CSID_MAX))
		cs->id = CSID_GENERIC;
	अगर (cs->vdso_घड़ी_mode < 0 ||
	    cs->vdso_घड़ी_mode >= VDSO_CLOCKMODE_MAX) अणु
		pr_warn("clocksource %s registered with invalid VDSO mode %d. Disabling VDSO support.\n",
			cs->name, cs->vdso_घड़ी_mode);
		cs->vdso_घड़ी_mode = VDSO_CLOCKMODE_NONE;
	पूर्ण

	/* Initialize mult/shअगरt and max_idle_ns */
	__घड़ीsource_update_freq_scale(cs, scale, freq);

	/* Add घड़ीsource to the घड़ीsource list */
	mutex_lock(&घड़ीsource_mutex);

	घड़ीsource_watchकरोg_lock(&flags);
	घड़ीsource_enqueue(cs);
	घड़ीsource_enqueue_watchकरोg(cs);
	घड़ीsource_watchकरोg_unlock(&flags);

	घड़ीsource_select();
	घड़ीsource_select_watchकरोg(false);
	__घड़ीsource_suspend_select(cs);
	mutex_unlock(&घड़ीsource_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__घड़ीsource_रेजिस्टर_scale);

अटल व्योम __घड़ीsource_change_rating(काष्ठा घड़ीsource *cs, पूर्णांक rating)
अणु
	list_del(&cs->list);
	cs->rating = rating;
	घड़ीsource_enqueue(cs);
पूर्ण

/**
 * घड़ीsource_change_rating - Change the rating of a रेजिस्टरed घड़ीsource
 * @cs:		घड़ीsource to be changed
 * @rating:	new rating
 */
व्योम घड़ीsource_change_rating(काष्ठा घड़ीsource *cs, पूर्णांक rating)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&घड़ीsource_mutex);
	घड़ीsource_watchकरोg_lock(&flags);
	__घड़ीsource_change_rating(cs, rating);
	घड़ीsource_watchकरोg_unlock(&flags);

	घड़ीsource_select();
	घड़ीsource_select_watchकरोg(false);
	घड़ीsource_suspend_select(false);
	mutex_unlock(&घड़ीsource_mutex);
पूर्ण
EXPORT_SYMBOL(घड़ीsource_change_rating);

/*
 * Unbind घड़ीsource @cs. Called with घड़ीsource_mutex held
 */
अटल पूर्णांक घड़ीsource_unbind(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (घड़ीsource_is_watchकरोg(cs)) अणु
		/* Select and try to install a replacement watchकरोg. */
		घड़ीsource_select_watchकरोg(true);
		अगर (घड़ीsource_is_watchकरोg(cs))
			वापस -EBUSY;
	पूर्ण

	अगर (cs == curr_घड़ीsource) अणु
		/* Select and try to install a replacement घड़ी source */
		घड़ीsource_select_fallback();
		अगर (curr_घड़ीsource == cs)
			वापस -EBUSY;
	पूर्ण

	अगर (घड़ीsource_is_suspend(cs)) अणु
		/*
		 * Select and try to install a replacement suspend घड़ीsource.
		 * If no replacement suspend घड़ीsource, we will just let the
		 * घड़ीsource go and have no suspend घड़ीsource.
		 */
		घड़ीsource_suspend_select(true);
	पूर्ण

	घड़ीsource_watchकरोg_lock(&flags);
	घड़ीsource_dequeue_watchकरोg(cs);
	list_del_init(&cs->list);
	घड़ीsource_watchकरोg_unlock(&flags);

	वापस 0;
पूर्ण

/**
 * घड़ीsource_unरेजिस्टर - हटाओ a रेजिस्टरed घड़ीsource
 * @cs:	घड़ीsource to be unरेजिस्टरed
 */
पूर्णांक घड़ीsource_unरेजिस्टर(काष्ठा घड़ीsource *cs)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&घड़ीsource_mutex);
	अगर (!list_empty(&cs->list))
		ret = घड़ीsource_unbind(cs);
	mutex_unlock(&घड़ीsource_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(घड़ीsource_unरेजिस्टर);

#अगर_घोषित CONFIG_SYSFS
/**
 * current_घड़ीsource_show - sysfs पूर्णांकerface क्रम current घड़ीsource
 * @dev:	unused
 * @attr:	unused
 * @buf:	अक्षर buffer to be filled with घड़ीsource list
 *
 * Provides sysfs पूर्णांकerface क्रम listing current घड़ीsource.
 */
अटल sमाप_प्रकार current_घड़ीsource_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	sमाप_प्रकार count = 0;

	mutex_lock(&घड़ीsource_mutex);
	count = snम_लिखो(buf, PAGE_SIZE, "%s\n", curr_घड़ीsource->name);
	mutex_unlock(&घड़ीsource_mutex);

	वापस count;
पूर्ण

sमाप_प्रकार sysfs_get_uname(स्थिर अक्षर *buf, अक्षर *dst, माप_प्रकार cnt)
अणु
	माप_प्रकार ret = cnt;

	/* strings from sysfs ग_लिखो are not 0 terminated! */
	अगर (!cnt || cnt >= CS_NAME_LEN)
		वापस -EINVAL;

	/* strip of \न: */
	अगर (buf[cnt-1] == '\n')
		cnt--;
	अगर (cnt > 0)
		स_नकल(dst, buf, cnt);
	dst[cnt] = 0;
	वापस ret;
पूर्ण

/**
 * current_घड़ीsource_store - पूर्णांकerface क्रम manually overriding घड़ीsource
 * @dev:	unused
 * @attr:	unused
 * @buf:	name of override घड़ीsource
 * @count:	length of buffer
 *
 * Takes input from sysfs पूर्णांकerface क्रम manually overriding the शेष
 * घड़ीsource selection.
 */
अटल sमाप_प्रकार current_घड़ीsource_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	mutex_lock(&घड़ीsource_mutex);

	ret = sysfs_get_uname(buf, override_name, count);
	अगर (ret >= 0)
		घड़ीsource_select();

	mutex_unlock(&घड़ीsource_mutex);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(current_घड़ीsource);

/**
 * unbind_घड़ीsource_store - पूर्णांकerface क्रम manually unbinding घड़ीsource
 * @dev:	unused
 * @attr:	unused
 * @buf:	unused
 * @count:	length of buffer
 *
 * Takes input from sysfs पूर्णांकerface क्रम manually unbinding a घड़ीsource.
 */
अटल sमाप_प्रकार unbind_घड़ीsource_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा घड़ीsource *cs;
	अक्षर name[CS_NAME_LEN];
	sमाप_प्रकार ret;

	ret = sysfs_get_uname(buf, name, count);
	अगर (ret < 0)
		वापस ret;

	ret = -ENODEV;
	mutex_lock(&घड़ीsource_mutex);
	list_क्रम_each_entry(cs, &घड़ीsource_list, list) अणु
		अगर (म_भेद(cs->name, name))
			जारी;
		ret = घड़ीsource_unbind(cs);
		अवरोध;
	पूर्ण
	mutex_unlock(&घड़ीsource_mutex);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(unbind_घड़ीsource);

/**
 * available_घड़ीsource_show - sysfs पूर्णांकerface क्रम listing घड़ीsource
 * @dev:	unused
 * @attr:	unused
 * @buf:	अक्षर buffer to be filled with घड़ीsource list
 *
 * Provides sysfs पूर्णांकerface क्रम listing रेजिस्टरed घड़ीsources
 */
अटल sमाप_प्रकार available_घड़ीsource_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा घड़ीsource *src;
	sमाप_प्रकार count = 0;

	mutex_lock(&घड़ीsource_mutex);
	list_क्रम_each_entry(src, &घड़ीsource_list, list) अणु
		/*
		 * Don't show non-HRES घड़ीsource अगर the tick code is
		 * in one shot mode (highres=on or nohz=on)
		 */
		अगर (!tick_oneshot_mode_active() ||
		    (src->flags & CLOCK_SOURCE_VALID_FOR_HRES))
			count += snम_लिखो(buf + count,
				  max((sमाप_प्रकार)PAGE_SIZE - count, (sमाप_प्रकार)0),
				  "%s ", src->name);
	पूर्ण
	mutex_unlock(&घड़ीsource_mutex);

	count += snम_लिखो(buf + count,
			  max((sमाप_प्रकार)PAGE_SIZE - count, (sमाप_प्रकार)0), "\n");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(available_घड़ीsource);

अटल काष्ठा attribute *घड़ीsource_attrs[] = अणु
	&dev_attr_current_घड़ीsource.attr,
	&dev_attr_unbind_घड़ीsource.attr,
	&dev_attr_available_घड़ीsource.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(घड़ीsource);

अटल काष्ठा bus_type घड़ीsource_subsys = अणु
	.name = "clocksource",
	.dev_name = "clocksource",
पूर्ण;

अटल काष्ठा device device_घड़ीsource = अणु
	.id	= 0,
	.bus	= &घड़ीsource_subsys,
	.groups	= घड़ीsource_groups,
पूर्ण;

अटल पूर्णांक __init init_घड़ीsource_sysfs(व्योम)
अणु
	पूर्णांक error = subsys_प्रणाली_रेजिस्टर(&घड़ीsource_subsys, शून्य);

	अगर (!error)
		error = device_रेजिस्टर(&device_घड़ीsource);

	वापस error;
पूर्ण

device_initcall(init_घड़ीsource_sysfs);
#पूर्ण_अगर /* CONFIG_SYSFS */

/**
 * boot_override_घड़ीsource - boot घड़ी override
 * @str:	override name
 *
 * Takes a घड़ीsource= boot argument and uses it
 * as the घड़ीsource override name.
 */
अटल पूर्णांक __init boot_override_घड़ीsource(अक्षर* str)
अणु
	mutex_lock(&घड़ीsource_mutex);
	अगर (str)
		strlcpy(override_name, str, माप(override_name));
	mutex_unlock(&घड़ीsource_mutex);
	वापस 1;
पूर्ण

__setup("clocksource=", boot_override_घड़ीsource);

/**
 * boot_override_घड़ी - Compatibility layer क्रम deprecated boot option
 * @str:	override name
 *
 * DEPRECATED! Takes a घड़ी= boot argument and uses it
 * as the घड़ीsource override name
 */
अटल पूर्णांक __init boot_override_घड़ी(अक्षर* str)
अणु
	अगर (!म_भेद(str, "pmtmr")) अणु
		pr_warn("clock=pmtmr is deprecated - use clocksource=acpi_pm\n");
		वापस boot_override_घड़ीsource("acpi_pm");
	पूर्ण
	pr_warn("clock= boot option is deprecated - use clocksource=xyz\n");
	वापस boot_override_घड़ीsource(str);
पूर्ण

__setup("clock=", boot_override_घड़ी);
