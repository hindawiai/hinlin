<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/ia64/kernel/समय.c
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 *	David Mosberger <davidm@hpl.hp.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 * Copyright (C) 1999-2000 VA Linux Systems
 * Copyright (C) 1999-2000 Walt Drummond <drummond@valinux.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/nmi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/efi.h>
#समावेश <linux/समयx.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched/cpuसमय.स>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/sections.h>

#समावेश "fsyscall_gtod_data.h"
#समावेश "irq.h"

अटल u64 itc_get_cycles(काष्ठा घड़ीsource *cs);

काष्ठा fsyscall_gtod_data_t fsyscall_gtod_data;

काष्ठा itc_jitter_data_t itc_jitter_data;

अस्थिर पूर्णांक समय_keeper_id = 0; /* smp_processor_id() of समय-keeper */

#अगर_घोषित CONFIG_IA64_DEBUG_IRQ

अचिन्हित दीर्घ last_cli_ip;
EXPORT_SYMBOL(last_cli_ip);

#पूर्ण_अगर

अटल काष्ठा घड़ीsource घड़ीsource_itc = अणु
	.name           = "itc",
	.rating         = 350,
	.पढ़ो           = itc_get_cycles,
	.mask           = CLOCKSOURCE_MASK(64),
	.flags          = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;
अटल काष्ठा घड़ीsource *itc_घड़ीsource;

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE

#समावेश <linux/kernel_स्थिति.स>

बाह्य u64 cycle_to_nsec(u64 cyc);

व्योम vसमय_flush(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);
	u64 delta;

	अगर (ti->uसमय)
		account_user_समय(tsk, cycle_to_nsec(ti->uसमय));

	अगर (ti->gसमय)
		account_guest_समय(tsk, cycle_to_nsec(ti->gसमय));

	अगर (ti->idle_समय)
		account_idle_समय(cycle_to_nsec(ti->idle_समय));

	अगर (ti->sसमय) अणु
		delta = cycle_to_nsec(ti->sसमय);
		account_प्रणाली_index_समय(tsk, delta, CPUTIME_SYSTEM);
	पूर्ण

	अगर (ti->hardirq_समय) अणु
		delta = cycle_to_nsec(ti->hardirq_समय);
		account_प्रणाली_index_समय(tsk, delta, CPUTIME_IRQ);
	पूर्ण

	अगर (ti->softirq_समय) अणु
		delta = cycle_to_nsec(ti->softirq_समय);
		account_प्रणाली_index_समय(tsk, delta, CPUTIME_SOFTIRQ);
	पूर्ण

	ti->uसमय = 0;
	ti->gसमय = 0;
	ti->idle_समय = 0;
	ti->sसमय = 0;
	ti->hardirq_समय = 0;
	ti->softirq_समय = 0;
पूर्ण

/*
 * Called from the context चयन with पूर्णांकerrupts disabled, to अक्षरge all
 * accumulated बार to the current process, and to prepare accounting on
 * the next process.
 */
व्योम arch_vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev)
अणु
	काष्ठा thपढ़ो_info *pi = task_thपढ़ो_info(prev);
	काष्ठा thपढ़ो_info *ni = task_thपढ़ो_info(current);

	ni->ac_stamp = pi->ac_stamp;
	ni->ac_sसमय = ni->ac_uसमय = 0;
पूर्ण

/*
 * Account समय क्रम a transition between प्रणाली, hard irq or soft irq state.
 * Note that this function is called with पूर्णांकerrupts enabled.
 */
अटल __u64 vसमय_delta(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);
	__u64 now, delta_sसमय;

	WARN_ON_ONCE(!irqs_disabled());

	now = ia64_get_itc();
	delta_sसमय = now - ti->ac_stamp;
	ti->ac_stamp = now;

	वापस delta_sसमय;
पूर्ण

व्योम vसमय_account_kernel(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);
	__u64 sसमय = vसमय_delta(tsk);

	अगर (tsk->flags & PF_VCPU)
		ti->gसमय += sसमय;
	अन्यथा
		ti->sसमय += sसमय;
पूर्ण
EXPORT_SYMBOL_GPL(vसमय_account_kernel);

व्योम vसमय_account_idle(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);

	ti->idle_समय += vसमय_delta(tsk);
पूर्ण

व्योम vसमय_account_softirq(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);

	ti->softirq_समय += vसमय_delta(tsk);
पूर्ण

व्योम vसमय_account_hardirq(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(tsk);

	ti->hardirq_समय += vसमय_delta(tsk);
पूर्ण

#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

अटल irqवापस_t
समयr_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ new_iपंचांग;

	अगर (cpu_is_offline(smp_processor_id())) अणु
		वापस IRQ_HANDLED;
	पूर्ण

	new_iपंचांग = local_cpu_data->iपंचांग_next;

	अगर (!समय_after(ia64_get_itc(), new_iपंचांग))
		prपूर्णांकk(KERN_ERR "Oops: timer tick before it's due (itc=%lx,itm=%lx)\n",
		       ia64_get_itc(), new_iपंचांग);

	जबतक (1) अणु
		new_iपंचांग += local_cpu_data->iपंचांग_delta;

		legacy_समयr_tick(smp_processor_id() == समय_keeper_id);

		local_cpu_data->iपंचांग_next = new_iपंचांग;

		अगर (समय_after(new_iपंचांग, ia64_get_itc()))
			अवरोध;

		/*
		 * Allow IPIs to पूर्णांकerrupt the समयr loop.
		 */
		local_irq_enable();
		local_irq_disable();
	पूर्ण

	करो अणु
		/*
		 * If we're too बंद to the next घड़ी tick क्रम
		 * comक्रमt, we increase the safety margin by
		 * पूर्णांकentionally dropping the next tick(s).  We करो NOT
		 * update iपंचांग.next because that would क्रमce us to call
		 * xसमय_update() which in turn would let our घड़ी run
		 * too fast (with the potentially devastating effect
		 * of losing monotony of समय).
		 */
		जबतक (!समय_after(new_iपंचांग, ia64_get_itc() + local_cpu_data->iपंचांग_delta/2))
			new_iपंचांग += local_cpu_data->iपंचांग_delta;
		ia64_set_iपंचांग(new_iपंचांग);
		/* द्विगुन check, in हाल we got hit by a (slow) PMI: */
	पूर्ण जबतक (समय_after_eq(ia64_get_itc(), new_iपंचांग));
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Encapsulate access to the iपंचांग काष्ठाure क्रम SMP.
 */
व्योम
ia64_cpu_local_tick (व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ shअगरt = 0, delta;

	/* arrange क्रम the cycle counter to generate a समयr पूर्णांकerrupt: */
	ia64_set_itv(IA64_TIMER_VECTOR);

	delta = local_cpu_data->iपंचांग_delta;
	/*
	 * Stagger the समयr tick क्रम each CPU so they करोn't occur all at (almost) the
	 * same समय:
	 */
	अगर (cpu) अणु
		अचिन्हित दीर्घ hi = 1UL << ia64_fls(cpu);
		shअगरt = (2*(cpu - hi) + 1) * delta/hi/2;
	पूर्ण
	local_cpu_data->iपंचांग_next = ia64_get_itc() + delta + shअगरt;
	ia64_set_iपंचांग(local_cpu_data->iपंचांग_next);
पूर्ण

अटल पूर्णांक nojitter;

अटल पूर्णांक __init nojitter_setup(अक्षर *str)
अणु
	nojitter = 1;
	prपूर्णांकk("Jitter checking for ITC timers disabled\n");
	वापस 1;
पूर्ण

__setup("nojitter", nojitter_setup);


व्योम ia64_init_iपंचांग(व्योम)
अणु
	अचिन्हित दीर्घ platक्रमm_base_freq, itc_freq;
	काष्ठा pal_freq_ratio itc_ratio, proc_ratio;
	दीर्घ status, platक्रमm_base_drअगरt, itc_drअगरt;

	/*
	 * According to SAL v2.6, we need to use a SAL call to determine the platक्रमm base
	 * frequency and then a PAL call to determine the frequency ratio between the ITC
	 * and the base frequency.
	 */
	status = ia64_sal_freq_base(SAL_FREQ_BASE_PLATFORM,
				    &platक्रमm_base_freq, &platक्रमm_base_drअगरt);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "SAL_FREQ_BASE_PLATFORM failed: %s\n", ia64_sal_म_त्रुटि(status));
	पूर्ण अन्यथा अणु
		status = ia64_pal_freq_ratios(&proc_ratio, शून्य, &itc_ratio);
		अगर (status != 0)
			prपूर्णांकk(KERN_ERR "PAL_FREQ_RATIOS failed with status=%ld\n", status);
	पूर्ण
	अगर (status != 0) अणु
		/* invent "random" values */
		prपूर्णांकk(KERN_ERR
		       "SAL/PAL failed to obtain frequency info---inventing reasonable values\n");
		platक्रमm_base_freq = 100000000;
		platक्रमm_base_drअगरt = -1;	/* no drअगरt info */
		itc_ratio.num = 3;
		itc_ratio.den = 1;
	पूर्ण
	अगर (platक्रमm_base_freq < 40000000) अणु
		prपूर्णांकk(KERN_ERR "Platform base frequency %lu bogus---resetting to 75MHz!\n",
		       platक्रमm_base_freq);
		platक्रमm_base_freq = 75000000;
		platक्रमm_base_drअगरt = -1;
	पूर्ण
	अगर (!proc_ratio.den)
		proc_ratio.den = 1;	/* aव्योम भागision by zero */
	अगर (!itc_ratio.den)
		itc_ratio.den = 1;	/* aव्योम भागision by zero */

	itc_freq = (platक्रमm_base_freq*itc_ratio.num)/itc_ratio.den;

	local_cpu_data->iपंचांग_delta = (itc_freq + HZ/2) / HZ;
	prपूर्णांकk(KERN_DEBUG "CPU %d: base freq=%lu.%03luMHz, ITC ratio=%u/%u, "
	       "ITC freq=%lu.%03luMHz", smp_processor_id(),
	       platक्रमm_base_freq / 1000000, (platक्रमm_base_freq / 1000) % 1000,
	       itc_ratio.num, itc_ratio.den, itc_freq / 1000000, (itc_freq / 1000) % 1000);

	अगर (platक्रमm_base_drअगरt != -1) अणु
		itc_drअगरt = platक्रमm_base_drअगरt*itc_ratio.num/itc_ratio.den;
		prपूर्णांकk("+/-%ldppm\n", itc_drअगरt);
	पूर्ण अन्यथा अणु
		itc_drअगरt = -1;
		prपूर्णांकk("\n");
	पूर्ण

	local_cpu_data->proc_freq = (platक्रमm_base_freq*proc_ratio.num)/proc_ratio.den;
	local_cpu_data->itc_freq = itc_freq;
	local_cpu_data->cyc_per_usec = (itc_freq + USEC_PER_SEC/2) / USEC_PER_SEC;
	local_cpu_data->nsec_per_cyc = ((NSEC_PER_SEC<<IA64_NSEC_PER_CYC_SHIFT)
					+ itc_freq/2)/itc_freq;

	अगर (!(sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT)) अणु
#अगर_घोषित CONFIG_SMP
		/* On IA64 in an SMP configuration ITCs are never accurately synchronized.
		 * Jitter compensation requires a cmpxchg which may limit
		 * the scalability of the syscalls क्रम retrieving समय.
		 * The ITC synchronization is usually successful to within a few
		 * ITC ticks but this is not a sure thing. If you need to improve
		 * समयr perक्रमmance in SMP situations then boot the kernel with the
		 * "nojitter" option. However, करोing so may result in समय fluctuating (maybe
		 * even going backward) अगर the ITC offsets between the inभागidual CPUs
		 * are too large.
		 */
		अगर (!nojitter)
			itc_jitter_data.itc_jitter = 1;
#पूर्ण_अगर
	पूर्ण अन्यथा
		/*
		 * ITC is drअगरty and we have not synchronized the ITCs in smpboot.c.
		 * ITC values may fluctuate signअगरicantly between processors.
		 * Clock should not be used क्रम hrसमयrs. Mark itc as only
		 * useful क्रम boot and testing.
		 *
		 * Note that jitter compensation is off! There is no poपूर्णांक of
		 * synchronizing ITCs since they may be large dअगरferentials
		 * that change over समय.
		 *
		 * The only way to fix this would be to repeatedly sync the
		 * ITCs. Until that समय we have to aव्योम ITC.
		 */
		घड़ीsource_itc.rating = 50;

	/* aव्योम softlock up message when cpu is unplug and plugged again. */
	touch_softlockup_watchकरोg();

	/* Setup the CPU local समयr tick */
	ia64_cpu_local_tick();

	अगर (!itc_घड़ीsource) अणु
		घड़ीsource_रेजिस्टर_hz(&घड़ीsource_itc,
						local_cpu_data->itc_freq);
		itc_घड़ीsource = &घड़ीsource_itc;
	पूर्ण
पूर्ण

अटल u64 itc_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ lcycle, now, ret;

	अगर (!itc_jitter_data.itc_jitter)
		वापस get_cycles();

	lcycle = itc_jitter_data.itc_lastcycle;
	now = get_cycles();
	अगर (lcycle && समय_after(lcycle, now))
		वापस lcycle;

	/*
	 * Keep track of the last समयr value वापसed.
	 * In an SMP environment, you could lose out in contention of
	 * cmpxchg. If so, your cmpxchg वापसs new value which the
	 * winner of contention updated to. Use the new value instead.
	 */
	ret = cmpxchg(&itc_jitter_data.itc_lastcycle, lcycle, now);
	अगर (unlikely(ret != lcycle))
		वापस ret;

	वापस now;
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	efi_समय_लोofday(ts);
पूर्ण

व्योम __init
समय_init (व्योम)
अणु
	रेजिस्टर_percpu_irq(IA64_TIMER_VECTOR, समयr_पूर्णांकerrupt, IRQF_IRQPOLL,
			    "timer");
	ia64_init_iपंचांग();
पूर्ण

/*
 * Generic udelay assumes that अगर preemption is allowed and the thपढ़ो
 * migrates to another CPU, that the ITC values are synchronized across
 * all CPUs.
 */
अटल व्योम
ia64_itc_udelay (अचिन्हित दीर्घ usecs)
अणु
	अचिन्हित दीर्घ start = ia64_get_itc();
	अचिन्हित दीर्घ end = start + usecs*local_cpu_data->cyc_per_usec;

	जबतक (समय_beक्रमe(ia64_get_itc(), end))
		cpu_relax();
पूर्ण

व्योम (*ia64_udelay)(अचिन्हित दीर्घ usecs) = &ia64_itc_udelay;

व्योम
udelay (अचिन्हित दीर्घ usecs)
अणु
	(*ia64_udelay)(usecs);
पूर्ण
EXPORT_SYMBOL(udelay);

/* IA64 करोesn't cache the समयzone */
व्योम update_vsyscall_tz(व्योम)
अणु
पूर्ण

व्योम update_vsyscall(काष्ठा समयkeeper *tk)
अणु
	ग_लिखो_seqcount_begin(&fsyscall_gtod_data.seq);

	/* copy vsyscall data */
	fsyscall_gtod_data.clk_mask = tk->tkr_mono.mask;
	fsyscall_gtod_data.clk_mult = tk->tkr_mono.mult;
	fsyscall_gtod_data.clk_shअगरt = tk->tkr_mono.shअगरt;
	fsyscall_gtod_data.clk_fsys_mmio = tk->tkr_mono.घड़ी->archdata.fsys_mmio;
	fsyscall_gtod_data.clk_cycle_last = tk->tkr_mono.cycle_last;

	fsyscall_gtod_data.wall_समय.sec = tk->xसमय_sec;
	fsyscall_gtod_data.wall_समय.snsec = tk->tkr_mono.xसमय_nsec;

	fsyscall_gtod_data.monotonic_समय.sec = tk->xसमय_sec
					      + tk->wall_to_monotonic.tv_sec;
	fsyscall_gtod_data.monotonic_समय.snsec = tk->tkr_mono.xसमय_nsec
						+ ((u64)tk->wall_to_monotonic.tv_nsec
							<< tk->tkr_mono.shअगरt);

	/* normalize */
	जबतक (fsyscall_gtod_data.monotonic_समय.snsec >=
					(((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt)) अणु
		fsyscall_gtod_data.monotonic_समय.snsec -=
					((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt;
		fsyscall_gtod_data.monotonic_समय.sec++;
	पूर्ण

	ग_लिखो_seqcount_end(&fsyscall_gtod_data.seq);
पूर्ण

