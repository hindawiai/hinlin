<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common समय routines among all ppc machines.
 *
 * Written by Cort Dougan (cort@cs.nmt.edu) to merge
 * Paul Mackerras' version and mine क्रम PReP and Pmac.
 * MPC8xx/MBX changes by Dan Malek (dmalek@jlc.net).
 * Converted क्रम 64-bit by Mike Corrigan (mikejc@us.ibm.com)
 *
 * First round of bugfixes by Gabriel Paubert (paubert@iram.es)
 * to make घड़ी more stable (2.4.0-test5). The only thing
 * that this code assumes is that the समयbases have been synchronized
 * by firmware on SMP and are never stopped (never करो sleep
 * on SMP then, nap and करोze are OK).
 * 
 * Speeded up करो_समय_लोofday by getting rid of references to
 * xसमय (which required locks क्रम consistency). (mikejc@us.ibm.com)
 *
 * TODO (not necessarily in this file):
 * - improve precision and reproducibility of समयbase frequency
 * measurement at boot समय.
 * - क्रम astronomical applications: add a new function to get
 * non ambiguous बारtamps even around leap seconds. This needs
 * a new बारtamp क्रमmat and a good name.
 *
 * 1997-09-10  Updated NTP code according to technical memoअक्रमum Jan '96
 *             "A Kernel Model for Precision Timekeeping" by Dave Mills
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयx.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/profile.h>
#समावेश <linux/cpu.h>
#समावेश <linux/security.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rtc.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/suspend.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/processor.h>
#समावेश <यंत्र/trace.h>

#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

/* घातerpc घड़ीsource/घड़ीevent code */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>

अटल u64 समयbase_पढ़ो(काष्ठा घड़ीsource *);
अटल काष्ठा घड़ीsource घड़ीsource_समयbase = अणु
	.name         = "timebase",
	.rating       = 400,
	.flags        = CLOCK_SOURCE_IS_CONTINUOUS,
	.mask         = CLOCKSOURCE_MASK(64),
	.पढ़ो         = समयbase_पढ़ो,
	.vdso_घड़ी_mode	= VDSO_CLOCKMODE_ARCHTIMER,
पूर्ण;

#घोषणा DECREMENTER_DEFAULT_MAX 0x7FFFFFFF
u64 decrementer_max = DECREMENTER_DEFAULT_MAX;

अटल पूर्णांक decrementer_set_next_event(अचिन्हित दीर्घ evt,
				      काष्ठा घड़ी_event_device *dev);
अटल पूर्णांक decrementer_shutकरोwn(काष्ठा घड़ी_event_device *evt);

काष्ठा घड़ी_event_device decrementer_घड़ीevent = अणु
	.name			= "decrementer",
	.rating			= 200,
	.irq			= 0,
	.set_next_event		= decrementer_set_next_event,
	.set_state_oneshot_stopped = decrementer_shutकरोwn,
	.set_state_shutकरोwn	= decrementer_shutकरोwn,
	.tick_resume		= decrementer_shutकरोwn,
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_C3STOP,
पूर्ण;
EXPORT_SYMBOL(decrementer_घड़ीevent);

DEFINE_PER_CPU(u64, decrementers_next_tb);
अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, decrementers);

#घोषणा XSEC_PER_SEC (1024*1024)

#अगर_घोषित CONFIG_PPC64
#घोषणा SCALE_XSEC(xsec, max)	(((xsec) * max) / XSEC_PER_SEC)
#अन्यथा
/* compute ((xsec << 12) * max) >> 32 */
#घोषणा SCALE_XSEC(xsec, max)	mulhwu((xsec) << 12, max)
#पूर्ण_अगर

अचिन्हित दीर्घ tb_ticks_per_jअगरfy;
अचिन्हित दीर्घ tb_ticks_per_usec = 100; /* sane शेष */
EXPORT_SYMBOL(tb_ticks_per_usec);
अचिन्हित दीर्घ tb_ticks_per_sec;
EXPORT_SYMBOL(tb_ticks_per_sec);	/* क्रम cpuसमय_प्रकार conversions */

DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL_GPL(rtc_lock);

अटल u64 tb_to_ns_scale __पढ़ो_mostly;
अटल अचिन्हित tb_to_ns_shअगरt __पढ़ो_mostly;
अटल u64 boot_tb __पढ़ो_mostly;

बाह्य काष्ठा समयzone sys_tz;
अटल दीर्घ समयzone_offset;

अचिन्हित दीर्घ ppc_proc_freq;
EXPORT_SYMBOL_GPL(ppc_proc_freq);
अचिन्हित दीर्घ ppc_tb_freq;
EXPORT_SYMBOL_GPL(ppc_tb_freq);

bool tb_invalid;

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
/*
 * Factor क्रम converting from cpuसमय_प्रकार (समयbase ticks) to
 * microseconds. This is stored as 0.64 fixed-poपूर्णांक binary fraction.
 */
u64 __cpuसमय_usec_factor;
EXPORT_SYMBOL(__cpuसमय_usec_factor);

#अगर_घोषित CONFIG_PPC_SPLPAR
व्योम (*dtl_consumer)(काष्ठा dtl_entry *, u64);
#पूर्ण_अगर

अटल व्योम calc_cpuसमय_factors(व्योम)
अणु
	काष्ठा भाग_result res;

	भाग128_by_32(1000000, 0, tb_ticks_per_sec, &res);
	__cpuसमय_usec_factor = res.result_low;
पूर्ण

/*
 * Read the SPURR on प्रणालीs that have it, otherwise the PURR,
 * or अगर that करोesn't exist वापस the समयbase value passed in.
 */
अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_spurr(अचिन्हित दीर्घ tb)
अणु
	अगर (cpu_has_feature(CPU_FTR_SPURR))
		वापस mfspr(SPRN_SPURR);
	अगर (cpu_has_feature(CPU_FTR_PURR))
		वापस mfspr(SPRN_PURR);
	वापस tb;
पूर्ण

#अगर_घोषित CONFIG_PPC_SPLPAR

#समावेश <यंत्र/dtl.h>

/*
 * Scan the dispatch trace log and count up the stolen समय.
 * Should be called with पूर्णांकerrupts disabled.
 */
अटल u64 scan_dispatch_log(u64 stop_tb)
अणु
	u64 i = local_paca->dtl_ridx;
	काष्ठा dtl_entry *dtl = local_paca->dtl_curr;
	काष्ठा dtl_entry *dtl_end = local_paca->dispatch_log_end;
	काष्ठा lppaca *vpa = local_paca->lppaca_ptr;
	u64 tb_delta;
	u64 stolen = 0;
	u64 dtb;

	अगर (!dtl)
		वापस 0;

	अगर (i == be64_to_cpu(vpa->dtl_idx))
		वापस 0;
	जबतक (i < be64_to_cpu(vpa->dtl_idx)) अणु
		dtb = be64_to_cpu(dtl->समयbase);
		tb_delta = be32_to_cpu(dtl->enqueue_to_dispatch_समय) +
			be32_to_cpu(dtl->पढ़ोy_to_enqueue_समय);
		barrier();
		अगर (i + N_DISPATCH_LOG < be64_to_cpu(vpa->dtl_idx)) अणु
			/* buffer has overflowed */
			i = be64_to_cpu(vpa->dtl_idx) - N_DISPATCH_LOG;
			dtl = local_paca->dispatch_log + (i % N_DISPATCH_LOG);
			जारी;
		पूर्ण
		अगर (dtb > stop_tb)
			अवरोध;
		अगर (dtl_consumer)
			dtl_consumer(dtl, i);
		stolen += tb_delta;
		++i;
		++dtl;
		अगर (dtl == dtl_end)
			dtl = local_paca->dispatch_log;
	पूर्ण
	local_paca->dtl_ridx = i;
	local_paca->dtl_curr = dtl;
	वापस stolen;
पूर्ण

/*
 * Accumulate stolen समय by scanning the dispatch trace log.
 * Called on entry from user mode.
 */
व्योम notrace accumulate_stolen_समय(व्योम)
अणु
	u64 sst, ust;
	अचिन्हित दीर्घ save_irq_soft_mask = irq_soft_mask_वापस();
	काष्ठा cpu_accounting_data *acct = &local_paca->accounting;

	/* We are called early in the exception entry, beक्रमe
	 * soft/hard_enabled are sync'ed to the expected state
	 * क्रम the exception. We are hard disabled but the PACA
	 * needs to reflect that so various debug stuff करोesn't
	 * complain
	 */
	irq_soft_mask_set(IRQS_DISABLED);

	sst = scan_dispatch_log(acct->startसमय_user);
	ust = scan_dispatch_log(acct->startसमय);
	acct->sसमय -= sst;
	acct->uसमय -= ust;
	acct->steal_समय += ust + sst;

	irq_soft_mask_set(save_irq_soft_mask);
पूर्ण

अटल अंतरभूत u64 calculate_stolen_समय(u64 stop_tb)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस 0;

	अगर (get_paca()->dtl_ridx != be64_to_cpu(get_lppaca()->dtl_idx))
		वापस scan_dispatch_log(stop_tb);

	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_PPC_SPLPAR */
अटल अंतरभूत u64 calculate_stolen_समय(u64 stop_tb)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_SPLPAR */

/*
 * Account समय क्रम a transition between प्रणाली, hard irq
 * or soft irq state.
 */
अटल अचिन्हित दीर्घ vसमय_delta_scaled(काष्ठा cpu_accounting_data *acct,
					अचिन्हित दीर्घ now, अचिन्हित दीर्घ sसमय)
अणु
	अचिन्हित दीर्घ sसमय_scaled = 0;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	अचिन्हित दीर्घ nowscaled, deltascaled;
	अचिन्हित दीर्घ uसमय, uसमय_scaled;

	nowscaled = पढ़ो_spurr(now);
	deltascaled = nowscaled - acct->startspurr;
	acct->startspurr = nowscaled;
	uसमय = acct->uसमय - acct->uसमय_sspurr;
	acct->uसमय_sspurr = acct->uसमय;

	/*
	 * Because we करोn't पढ़ो the SPURR on every kernel entry/निकास,
	 * deltascaled includes both user and प्रणाली SPURR ticks.
	 * Apportion these ticks to प्रणाली SPURR ticks and user
	 * SPURR ticks in the same ratio as the प्रणाली समय (delta)
	 * and user समय (udelta) values obtained from the समयbase
	 * over the same पूर्णांकerval.  The प्रणाली ticks get accounted here;
	 * the user ticks get saved up in paca->user_समय_scaled to be
	 * used by account_process_tick.
	 */
	sसमय_scaled = sसमय;
	uसमय_scaled = uसमय;
	अगर (deltascaled != sसमय + uसमय) अणु
		अगर (uसमय) अणु
			sसमय_scaled = deltascaled * sसमय / (sसमय + uसमय);
			uसमय_scaled = deltascaled - sसमय_scaled;
		पूर्ण अन्यथा अणु
			sसमय_scaled = deltascaled;
		पूर्ण
	पूर्ण
	acct->uसमय_scaled += uसमय_scaled;
#पूर्ण_अगर

	वापस sसमय_scaled;
पूर्ण

अटल अचिन्हित दीर्घ vसमय_delta(काष्ठा cpu_accounting_data *acct,
				 अचिन्हित दीर्घ *sसमय_scaled,
				 अचिन्हित दीर्घ *steal_समय)
अणु
	अचिन्हित दीर्घ now, sसमय;

	WARN_ON_ONCE(!irqs_disabled());

	now = mftb();
	sसमय = now - acct->startसमय;
	acct->startसमय = now;

	*sसमय_scaled = vसमय_delta_scaled(acct, now, sसमय);

	*steal_समय = calculate_stolen_समय(now);

	वापस sसमय;
पूर्ण

अटल व्योम vसमय_delta_kernel(काष्ठा cpu_accounting_data *acct,
			       अचिन्हित दीर्घ *sसमय, अचिन्हित दीर्घ *sसमय_scaled)
अणु
	अचिन्हित दीर्घ steal_समय;

	*sसमय = vसमय_delta(acct, sसमय_scaled, &steal_समय);
	*sसमय -= min(*sसमय, steal_समय);
	acct->steal_समय += steal_समय;
पूर्ण

व्योम vसमय_account_kernel(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cpu_accounting_data *acct = get_accounting(tsk);
	अचिन्हित दीर्घ sसमय, sसमय_scaled;

	vसमय_delta_kernel(acct, &sसमय, &sसमय_scaled);

	अगर (tsk->flags & PF_VCPU) अणु
		acct->gसमय += sसमय;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
		acct->uसमय_scaled += sसमय_scaled;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		acct->sसमय += sसमय;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
		acct->sसमय_scaled += sसमय_scaled;
#पूर्ण_अगर
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vसमय_account_kernel);

व्योम vसमय_account_idle(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ sसमय, sसमय_scaled, steal_समय;
	काष्ठा cpu_accounting_data *acct = get_accounting(tsk);

	sसमय = vसमय_delta(acct, &sसमय_scaled, &steal_समय);
	acct->idle_समय += sसमय + steal_समय;
पूर्ण

अटल व्योम vसमय_account_irq_field(काष्ठा cpu_accounting_data *acct,
				    अचिन्हित दीर्घ *field)
अणु
	अचिन्हित दीर्घ sसमय, sसमय_scaled;

	vसमय_delta_kernel(acct, &sसमय, &sसमय_scaled);
	*field += sसमय;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	acct->sसमय_scaled += sसमय_scaled;
#पूर्ण_अगर
पूर्ण

व्योम vसमय_account_softirq(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cpu_accounting_data *acct = get_accounting(tsk);
	vसमय_account_irq_field(acct, &acct->softirq_समय);
पूर्ण

व्योम vसमय_account_hardirq(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cpu_accounting_data *acct = get_accounting(tsk);
	vसमय_account_irq_field(acct, &acct->hardirq_समय);
पूर्ण

अटल व्योम vसमय_flush_scaled(काष्ठा task_काष्ठा *tsk,
			       काष्ठा cpu_accounting_data *acct)
अणु
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	अगर (acct->uसमय_scaled)
		tsk->uबारcaled += cpuसमय_प्रकारo_nsecs(acct->uसमय_scaled);
	अगर (acct->sसमय_scaled)
		tsk->sबारcaled += cpuसमय_प्रकारo_nsecs(acct->sसमय_scaled);

	acct->uसमय_scaled = 0;
	acct->uसमय_sspurr = 0;
	acct->sसमय_scaled = 0;
#पूर्ण_अगर
पूर्ण

/*
 * Account the whole cpuसमय accumulated in the paca
 * Must be called with पूर्णांकerrupts disabled.
 * Assumes that vसमय_account_kernel/idle() has been called
 * recently (i.e. since the last entry from usermode) so that
 * get_paca()->user_समय_scaled is up to date.
 */
व्योम vसमय_flush(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cpu_accounting_data *acct = get_accounting(tsk);

	अगर (acct->uसमय)
		account_user_समय(tsk, cpuसमय_प्रकारo_nsecs(acct->uसमय));

	अगर (acct->gसमय)
		account_guest_समय(tsk, cpuसमय_प्रकारo_nsecs(acct->gसमय));

	अगर (IS_ENABLED(CONFIG_PPC_SPLPAR) && acct->steal_समय) अणु
		account_steal_समय(cpuसमय_प्रकारo_nsecs(acct->steal_समय));
		acct->steal_समय = 0;
	पूर्ण

	अगर (acct->idle_समय)
		account_idle_समय(cpuसमय_प्रकारo_nsecs(acct->idle_समय));

	अगर (acct->sसमय)
		account_प्रणाली_index_समय(tsk, cpuसमय_प्रकारo_nsecs(acct->sसमय),
					  CPUTIME_SYSTEM);

	अगर (acct->hardirq_समय)
		account_प्रणाली_index_समय(tsk, cpuसमय_प्रकारo_nsecs(acct->hardirq_समय),
					  CPUTIME_IRQ);
	अगर (acct->softirq_समय)
		account_प्रणाली_index_समय(tsk, cpuसमय_प्रकारo_nsecs(acct->softirq_समय),
					  CPUTIME_SOFTIRQ);

	vसमय_flush_scaled(tsk, acct);

	acct->uसमय = 0;
	acct->gसमय = 0;
	acct->idle_समय = 0;
	acct->sसमय = 0;
	acct->hardirq_समय = 0;
	acct->softirq_समय = 0;
पूर्ण

#अन्यथा /* ! CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */
#घोषणा calc_cpuसमय_factors()
#पूर्ण_अगर

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	अचिन्हित दीर्घ start;

	spin_begin();
	अगर (tb_invalid) अणु
		/*
		 * TB is in error state and isn't ticking anymore.
		 * HMI handler was unable to recover from TB error.
		 * Return immediately, so that kernel won't get stuck here.
		 */
		spin_cpu_relax();
	पूर्ण अन्यथा अणु
		start = mftb();
		जबतक (mftb() - start < loops)
			spin_cpu_relax();
	पूर्ण
	spin_end();
पूर्ण
EXPORT_SYMBOL(__delay);

व्योम udelay(अचिन्हित दीर्घ usecs)
अणु
	__delay(tb_ticks_per_usec * usecs);
पूर्ण
EXPORT_SYMBOL(udelay);

#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (in_lock_functions(pc))
		वापस regs->link;

	वापस pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_WORK

/*
 * 64-bit uses a byte in the PACA, 32-bit uses a per-cpu variable...
 */
#अगर_घोषित CONFIG_PPC64
अटल अंतरभूत अचिन्हित दीर्घ test_irq_work_pending(व्योम)
अणु
	अचिन्हित दीर्घ x;

	यंत्र अस्थिर("lbz %0,%1(13)"
		: "=r" (x)
		: "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_work_pending)));
	वापस x;
पूर्ण

अटल अंतरभूत व्योम set_irq_work_pending_flag(व्योम)
अणु
	यंत्र अस्थिर("stb %0,%1(13)" : :
		"r" (1),
		"i" (दुरत्व(काष्ठा paca_काष्ठा, irq_work_pending)));
पूर्ण

अटल अंतरभूत व्योम clear_irq_work_pending(व्योम)
अणु
	यंत्र अस्थिर("stb %0,%1(13)" : :
		"r" (0),
		"i" (दुरत्व(काष्ठा paca_काष्ठा, irq_work_pending)));
पूर्ण

#अन्यथा /* 32-bit */

DEFINE_PER_CPU(u8, irq_work_pending);

#घोषणा set_irq_work_pending_flag()	__this_cpu_ग_लिखो(irq_work_pending, 1)
#घोषणा test_irq_work_pending()		__this_cpu_पढ़ो(irq_work_pending)
#घोषणा clear_irq_work_pending()	__this_cpu_ग_लिखो(irq_work_pending, 0)

#पूर्ण_अगर /* 32 vs 64 bit */

व्योम arch_irq_work_उठाओ(व्योम)
अणु
	/*
	 * 64-bit code that uses irq soft-mask can just cause an immediate
	 * पूर्णांकerrupt here that माला_लो soft masked, अगर this is called under
	 * local_irq_disable(). It might be possible to prevent that happening
	 * by noticing पूर्णांकerrupts are disabled and setting decrementer pending
	 * to be replayed when irqs are enabled. The problem there is that
	 * tracing can call irq_work_उठाओ, including in code that करोes low
	 * level manipulations of irq soft-mask state (e.g., trace_hardirqs_on)
	 * which could get tangled up अगर we're messing with the same state
	 * here.
	 */
	preempt_disable();
	set_irq_work_pending_flag();
	set_dec(1);
	preempt_enable();
पूर्ण

#अन्यथा  /* CONFIG_IRQ_WORK */

#घोषणा test_irq_work_pending()	0
#घोषणा clear_irq_work_pending()

#पूर्ण_अगर /* CONFIG_IRQ_WORK */

/*
 * समयr_पूर्णांकerrupt - माला_लो called when the decrementer overflows,
 * with पूर्णांकerrupts disabled.
 */
DEFINE_INTERRUPT_HANDLER_ASYNC(समयr_पूर्णांकerrupt)
अणु
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&decrementers);
	u64 *next_tb = this_cpu_ptr(&decrementers_next_tb);
	काष्ठा pt_regs *old_regs;
	u64 now;

	/*
	 * Some implementations of hotplug will get समयr पूर्णांकerrupts जबतक
	 * offline, just ignore these.
	 */
	अगर (unlikely(!cpu_online(smp_processor_id()))) अणु
		set_dec(decrementer_max);
		वापस;
	पूर्ण

	/* Ensure a positive value is written to the decrementer, or अन्यथा
	 * some CPUs will जारी to take decrementer exceptions. When the
	 * PPC_WATCHDOG (decrementer based) is configured, keep this at most
	 * 31 bits, which is about 4 seconds on most प्रणालीs, which gives
	 * the watchकरोg a chance of catching समयr पूर्णांकerrupt hard lockups.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_WATCHDOG))
		set_dec(0x7fffffff);
	अन्यथा
		set_dec(decrementer_max);

	/* Conditionally hard-enable पूर्णांकerrupts now that the DEC has been
	 * bumped to its maximum value
	 */
	may_hard_irq_enable();


#अगर defined(CONFIG_PPC32) && defined(CONFIG_PPC_PMAC)
	अगर (atomic_पढ़ो(&ppc_n_lost_पूर्णांकerrupts) != 0)
		करो_IRQ(regs);
#पूर्ण_अगर

	old_regs = set_irq_regs(regs);

	trace_समयr_पूर्णांकerrupt_entry(regs);

	अगर (test_irq_work_pending()) अणु
		clear_irq_work_pending();
		irq_work_run();
	पूर्ण

	now = get_tb();
	अगर (now >= *next_tb) अणु
		*next_tb = ~(u64)0;
		अगर (evt->event_handler)
			evt->event_handler(evt);
		__this_cpu_inc(irq_stat.समयr_irqs_event);
	पूर्ण अन्यथा अणु
		now = *next_tb - now;
		अगर (now <= decrementer_max)
			set_dec(now);
		/* We may have raced with new irq work */
		अगर (test_irq_work_pending())
			set_dec(1);
		__this_cpu_inc(irq_stat.समयr_irqs_others);
	पूर्ण

	trace_समयr_पूर्णांकerrupt_निकास(regs);

	set_irq_regs(old_regs);
पूर्ण
EXPORT_SYMBOL(समयr_पूर्णांकerrupt);

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम समयr_broadcast_पूर्णांकerrupt(व्योम)
अणु
	u64 *next_tb = this_cpu_ptr(&decrementers_next_tb);

	*next_tb = ~(u64)0;
	tick_receive_broadcast();
	__this_cpu_inc(irq_stat.broadcast_irqs_event);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUSPEND
अटल व्योम generic_suspend_disable_irqs(व्योम)
अणु
	/* Disable the decrementer, so that it करोesn't पूर्णांकerfere
	 * with suspending.
	 */

	set_dec(decrementer_max);
	local_irq_disable();
	set_dec(decrementer_max);
पूर्ण

अटल व्योम generic_suspend_enable_irqs(व्योम)
अणु
	local_irq_enable();
पूर्ण

/* Overrides the weak version in kernel/घातer/मुख्य.c */
व्योम arch_suspend_disable_irqs(व्योम)
अणु
	अगर (ppc_md.suspend_disable_irqs)
		ppc_md.suspend_disable_irqs();
	generic_suspend_disable_irqs();
पूर्ण

/* Overrides the weak version in kernel/घातer/मुख्य.c */
व्योम arch_suspend_enable_irqs(व्योम)
अणु
	generic_suspend_enable_irqs();
	अगर (ppc_md.suspend_enable_irqs)
		ppc_md.suspend_enable_irqs();
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ दीर्घ tb_to_ns(अचिन्हित दीर्घ दीर्घ ticks)
अणु
	वापस mulhdu(ticks, tb_to_ns_scale) << tb_to_ns_shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(tb_to_ns);

/*
 * Scheduler घड़ी - वापसs current समय in nanosec units.
 *
 * Note: mulhdu(a, b) (multiply high द्विगुन अचिन्हित) वापसs
 * the high 64 bits of a * b, i.e. (a * b) >> 64, where a and b
 * are 64-bit अचिन्हित numbers.
 */
notrace अचिन्हित दीर्घ दीर्घ sched_घड़ी(व्योम)
अणु
	वापस mulhdu(get_tb() - boot_tb, tb_to_ns_scale) << tb_to_ns_shअगरt;
पूर्ण


#अगर_घोषित CONFIG_PPC_PSERIES

/*
 * Running घड़ी - attempts to give a view of समय passing क्रम a भवised
 * kernels.
 * Uses the VTB रेजिस्टर अगर available otherwise a next best guess.
 */
अचिन्हित दीर्घ दीर्घ running_घड़ी(व्योम)
अणु
	/*
	 * Don't पढ़ो the VTB as a host since KVM करोes not चयन in host
	 * समयbase पूर्णांकo the VTB when it takes a guest off the CPU, पढ़ोing the
	 * VTB would result in पढ़ोing 'last switched out' guest VTB.
	 *
	 * Host kernels are often compiled with CONFIG_PPC_PSERIES checked, it
	 * would be unsafe to rely only on the #अगर_घोषित above.
	 */
	अगर (firmware_has_feature(FW_FEATURE_LPAR) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस mulhdu(get_vtb() - boot_tb, tb_to_ns_scale) << tb_to_ns_shअगरt;

	/*
	 * This is a next best approximation without a VTB.
	 * On a host which is running bare metal there should never be any stolen
	 * समय and on a host which करोesn't करो any भवisation TB *should* equal
	 * VTB so it makes no dअगरference anyway.
	 */
	वापस local_घड़ी() - kcpustat_this_cpu->cpustat[CPUTIME_STEAL];
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init get_freq(अक्षर *name, पूर्णांक cells, अचिन्हित दीर्घ *val)
अणु
	काष्ठा device_node *cpu;
	स्थिर __be32 *fp;
	पूर्णांक found = 0;

	/* The cpu node should have समयbase and घड़ी frequency properties */
	cpu = of_find_node_by_type(शून्य, "cpu");

	अगर (cpu) अणु
		fp = of_get_property(cpu, name, शून्य);
		अगर (fp) अणु
			found = 1;
			*val = of_पढ़ो_uदीर्घ(fp, cells);
		पूर्ण

		of_node_put(cpu);
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम start_cpu_decrementer(व्योम)
अणु
#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
	अचिन्हित पूर्णांक tcr;

	/* Clear any pending समयr पूर्णांकerrupts */
	mtspr(SPRN_TSR, TSR_ENW | TSR_WIS | TSR_DIS | TSR_FIS);

	tcr = mfspr(SPRN_TCR);
	/*
	 * The watchकरोg may have alपढ़ोy been enabled by u-boot. So leave
	 * TRC[WP] (Watchकरोg Period) alone.
	 */
	tcr &= TCR_WP_MASK;	/* Clear all bits except क्रम TCR[WP] */
	tcr |= TCR_DIE;		/* Enable decrementer */
	mtspr(SPRN_TCR, tcr);
#पूर्ण_अगर
पूर्ण

व्योम __init generic_calibrate_decr(व्योम)
अणु
	ppc_tb_freq = DEFAULT_TB_FREQ;		/* hardcoded शेष */

	अगर (!get_freq("ibm,extended-timebase-frequency", 2, &ppc_tb_freq) &&
	    !get_freq("timebase-frequency", 1, &ppc_tb_freq)) अणु

		prपूर्णांकk(KERN_ERR "WARNING: Estimating decrementer frequency "
				"(not found)\n");
	पूर्ण

	ppc_proc_freq = DEFAULT_PROC_FREQ;	/* hardcoded शेष */

	अगर (!get_freq("ibm,extended-clock-frequency", 2, &ppc_proc_freq) &&
	    !get_freq("clock-frequency", 1, &ppc_proc_freq)) अणु

		prपूर्णांकk(KERN_ERR "WARNING: Estimating processor frequency "
				"(not found)\n");
	पूर्ण
पूर्ण

पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now)
अणु
	काष्ठा rtc_समय पंचांग;

	अगर (!ppc_md.set_rtc_समय)
		वापस -ENODEV;

	rtc_समय64_to_पंचांग(now.tv_sec + 1 + समयzone_offset, &पंचांग);

	वापस ppc_md.set_rtc_समय(&पंचांग);
पूर्ण

अटल व्योम __पढ़ो_persistent_घड़ी(काष्ठा बारpec64 *ts)
अणु
	काष्ठा rtc_समय पंचांग;
	अटल पूर्णांक first = 1;

	ts->tv_nsec = 0;
	/* XXX this is a litle fragile but will work okay in the लघु term */
	अगर (first) अणु
		first = 0;
		अगर (ppc_md.समय_init)
			समयzone_offset = ppc_md.समय_init();

		/* get_boot_समय() isn't guaranteed to be safe to call late */
		अगर (ppc_md.get_boot_समय) अणु
			ts->tv_sec = ppc_md.get_boot_समय() - समयzone_offset;
			वापस;
		पूर्ण
	पूर्ण
	अगर (!ppc_md.get_rtc_समय) अणु
		ts->tv_sec = 0;
		वापस;
	पूर्ण
	ppc_md.get_rtc_समय(&पंचांग);

	ts->tv_sec = rtc_पंचांग_to_समय64(&पंचांग);
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	__पढ़ो_persistent_घड़ी(ts);

	/* Sanitize it in हाल real समय घड़ी is set below EPOCH */
	अगर (ts->tv_sec < 0) अणु
		ts->tv_sec = 0;
		ts->tv_nsec = 0;
	पूर्ण
		
पूर्ण

/* घड़ीsource code */
अटल notrace u64 समयbase_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)get_tb();
पूर्ण

अटल व्योम __init घड़ीsource_init(व्योम)
अणु
	काष्ठा घड़ीsource *घड़ी = &घड़ीsource_समयbase;

	अगर (घड़ीsource_रेजिस्टर_hz(घड़ी, tb_ticks_per_sec)) अणु
		prपूर्णांकk(KERN_ERR "clocksource: %s is already registered\n",
		       घड़ी->name);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "clocksource: %s mult[%x] shift[%d] registered\n",
	       घड़ी->name, घड़ी->mult, घड़ी->shअगरt);
पूर्ण

अटल पूर्णांक decrementer_set_next_event(अचिन्हित दीर्घ evt,
				      काष्ठा घड़ी_event_device *dev)
अणु
	__this_cpu_ग_लिखो(decrementers_next_tb, get_tb() + evt);
	set_dec(evt);

	/* We may have raced with new irq work */
	अगर (test_irq_work_pending())
		set_dec(1);

	वापस 0;
पूर्ण

अटल पूर्णांक decrementer_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	decrementer_set_next_event(decrementer_max, dev);
	वापस 0;
पूर्ण

अटल व्योम रेजिस्टर_decrementer_घड़ीevent(पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *dec = &per_cpu(decrementers, cpu);

	*dec = decrementer_घड़ीevent;
	dec->cpumask = cpumask_of(cpu);

	घड़ीevents_config_and_रेजिस्टर(dec, ppc_tb_freq, 2, decrementer_max);

	prपूर्णांकk_once(KERN_DEBUG "clockevent: %s mult[%x] shift[%d] cpu[%d]\n",
		    dec->name, dec->mult, dec->shअगरt, cpu);

	/* Set values क्रम KVM, see kvm_emulate_dec() */
	decrementer_घड़ीevent.mult = dec->mult;
	decrementer_घड़ीevent.shअगरt = dec->shअगरt;
पूर्ण

अटल व्योम enable_large_decrementer(व्योम)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस;

	अगर (decrementer_max <= DECREMENTER_DEFAULT_MAX)
		वापस;

	/*
	 * If we're running as the hypervisor we need to enable the LD manually
	 * otherwise firmware should have करोne it क्रम us.
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) | LPCR_LD);
पूर्ण

अटल व्योम __init set_decrementer_max(व्योम)
अणु
	काष्ठा device_node *cpu;
	u32 bits = 32;

	/* Prior to ISAv3 the decrementer is always 32 bit */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस;

	cpu = of_find_node_by_type(शून्य, "cpu");

	अगर (of_property_पढ़ो_u32(cpu, "ibm,dec-bits", &bits) == 0) अणु
		अगर (bits > 64 || bits < 32) अणु
			pr_warn("time_init: firmware supplied invalid ibm,dec-bits");
			bits = 32;
		पूर्ण

		/* calculate the चिन्हित maximum given this many bits */
		decrementer_max = (1ul << (bits - 1)) - 1;
	पूर्ण

	of_node_put(cpu);

	pr_info("time_init: %u bit decrementer (max: %llx)\n",
		bits, decrementer_max);
पूर्ण

अटल व्योम __init init_decrementer_घड़ीevent(व्योम)
अणु
	रेजिस्टर_decrementer_घड़ीevent(smp_processor_id());
पूर्ण

व्योम secondary_cpu_समय_init(व्योम)
अणु
	/* Enable and test the large decrementer क्रम this cpu */
	enable_large_decrementer();

	/* Start the decrementer on CPUs that have manual control
	 * such as BookE
	 */
	start_cpu_decrementer();

	/* FIME: Should make unrelatred change to move snapshot_समयbase
	 * call here ! */
	रेजिस्टर_decrementer_घड़ीevent(smp_processor_id());
पूर्ण

/* This function is only called on the boot processor */
व्योम __init समय_init(व्योम)
अणु
	काष्ठा भाग_result res;
	u64 scale;
	अचिन्हित shअगरt;

	/* Normal PowerPC with समयbase रेजिस्टर */
	ppc_md.calibrate_decr();
	prपूर्णांकk(KERN_DEBUG "time_init: decrementer frequency = %lu.%.6lu MHz\n",
	       ppc_tb_freq / 1000000, ppc_tb_freq % 1000000);
	prपूर्णांकk(KERN_DEBUG "time_init: processor frequency   = %lu.%.6lu MHz\n",
	       ppc_proc_freq / 1000000, ppc_proc_freq % 1000000);

	tb_ticks_per_jअगरfy = ppc_tb_freq / HZ;
	tb_ticks_per_sec = ppc_tb_freq;
	tb_ticks_per_usec = ppc_tb_freq / 1000000;
	calc_cpuसमय_factors();

	/*
	 * Compute scale factor क्रम sched_घड़ी.
	 * The calibrate_decr() function has set tb_ticks_per_sec,
	 * which is the समयbase frequency.
	 * We compute 1e9 * 2^64 / tb_ticks_per_sec and पूर्णांकerpret
	 * the 128-bit result as a 64.64 fixed-poपूर्णांक number.
	 * We then shअगरt that number right until it is less than 1.0,
	 * giving us the scale factor and shअगरt count to use in
	 * sched_घड़ी().
	 */
	भाग128_by_32(1000000000, 0, tb_ticks_per_sec, &res);
	scale = res.result_low;
	क्रम (shअगरt = 0; res.result_high != 0; ++shअगरt) अणु
		scale = (scale >> 1) | (res.result_high << 63);
		res.result_high >>= 1;
	पूर्ण
	tb_to_ns_scale = scale;
	tb_to_ns_shअगरt = shअगरt;
	/* Save the current समयbase to pretty up CONFIG_PRINTK_TIME */
	boot_tb = get_tb();

	/* If platक्रमm provided a समयzone (pmac), we correct the समय */
	अगर (समयzone_offset) अणु
		sys_tz.tz_minuteswest = -समयzone_offset / 60;
		sys_tz.tz_dstसमय = 0;
	पूर्ण

	vdso_data->tb_ticks_per_sec = tb_ticks_per_sec;

	/* initialise and enable the large decrementer (अगर we have one) */
	set_decrementer_max();
	enable_large_decrementer();

	/* Start the decrementer on CPUs that have manual control
	 * such as BookE
	 */
	start_cpu_decrementer();

	/* Register the घड़ीsource */
	घड़ीsource_init();

	init_decrementer_घड़ीevent();
	tick_setup_hrसमयr_broadcast();

	of_clk_init(शून्य);
	enable_sched_घड़ी_irqसमय();
पूर्ण

/*
 * Divide a 128-bit भागidend by a 32-bit भागisor, leaving a 128 bit
 * result.
 */
व्योम भाग128_by_32(u64 भागidend_high, u64 भागidend_low,
		  अचिन्हित भागisor, काष्ठा भाग_result *dr)
अणु
	अचिन्हित दीर्घ a, b, c, d;
	अचिन्हित दीर्घ w, x, y, z;
	u64 ra, rb, rc;

	a = भागidend_high >> 32;
	b = भागidend_high & 0xffffffff;
	c = भागidend_low >> 32;
	d = भागidend_low & 0xffffffff;

	w = a / भागisor;
	ra = ((u64)(a - (w * भागisor)) << 32) + b;

	rb = ((u64) करो_भाग(ra, भागisor) << 32) + c;
	x = ra;

	rc = ((u64) करो_भाग(rb, भागisor) << 32) + d;
	y = rb;

	करो_भाग(rc, भागisor);
	z = rc;

	dr->result_high = ((u64)w << 32) + x;
	dr->result_low  = ((u64)y << 32) + z;

पूर्ण

/* We करोn't need to calibrate delay, we use the CPU समयbase क्रम that */
व्योम calibrate_delay(व्योम)
अणु
	/* Some generic code (such as spinlock debug) use loops_per_jअगरfy
	 * as the number of __delay(1) in a jअगरfy, so make it so
	 */
	loops_per_jअगरfy = tb_ticks_per_jअगरfy;
पूर्ण

#अगर IS_ENABLED(CONFIG_RTC_DRV_GENERIC)
अटल पूर्णांक rtc_generic_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	ppc_md.get_rtc_समय(पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_generic_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अगर (!ppc_md.set_rtc_समय)
		वापस -EOPNOTSUPP;

	अगर (ppc_md.set_rtc_समय(पंचांग) < 0)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_generic_ops = अणु
	.पढ़ो_समय = rtc_generic_get_समय,
	.set_समय = rtc_generic_set_समय,
पूर्ण;

अटल पूर्णांक __init rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!ppc_md.get_rtc_समय)
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "rtc-generic", -1,
					     &rtc_generic_ops,
					     माप(rtc_generic_ops));

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

device_initcall(rtc_init);
#पूर्ण_अगर
