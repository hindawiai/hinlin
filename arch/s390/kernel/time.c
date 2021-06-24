<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Time of day based समयr functions.
 *
 *  S390 version
 *    Copyright IBM Corp. 1999, 2008
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com),
 *               Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 *
 *  Derived from "arch/i386/kernel/time.c"
 *    Copyright (C) 1991, 1992, 1995  Linus Torvalds
 */

#घोषणा KMSG_COMPONENT "time"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/समय.स>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/profile.h>
#समावेश <linux/समयx.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <vdso/vsyscall.h>
#समावेश <vdso/घड़ीsource.h>
#समावेश <vdso/helpers.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <यंत्र/stp.h>
#समावेश <यंत्र/cपन.स>
#समावेश "entry.h"

जोड़ tod_घड़ी tod_घड़ी_base __section(".data");
EXPORT_SYMBOL_GPL(tod_घड़ी_base);

u64 घड़ी_comparator_max = -1ULL;
EXPORT_SYMBOL_GPL(घड़ी_comparator_max);

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, comparators);

ATOMIC_NOTIFIER_HEAD(s390_epoch_delta_notअगरier);
EXPORT_SYMBOL(s390_epoch_delta_notअगरier);

अचिन्हित अक्षर ptff_function_mask[16];

अटल अचिन्हित दीर्घ lpar_offset;
अटल अचिन्हित दीर्घ initial_leap_seconds;
अटल अचिन्हित दीर्घ tod_steering_end;
अटल दीर्घ tod_steering_delta;

/*
 * Get समय offsets with PTFF
 */
व्योम __init समय_early_init(व्योम)
अणु
	काष्ठा ptff_qto qto;
	काष्ठा ptff_qui qui;
	पूर्णांक cs;

	/* Initialize TOD steering parameters */
	tod_steering_end = tod_घड़ी_base.tod;
	क्रम (cs = 0; cs < CS_BASES; cs++)
		vdso_data[cs].arch_data.tod_steering_end = tod_steering_end;

	अगर (!test_facility(28))
		वापस;

	ptff(&ptff_function_mask, माप(ptff_function_mask), PTFF_QAF);

	/* get LPAR offset */
	अगर (ptff_query(PTFF_QTO) && ptff(&qto, माप(qto), PTFF_QTO) == 0)
		lpar_offset = qto.tod_epoch_dअगरference;

	/* get initial leap seconds */
	अगर (ptff_query(PTFF_QUI) && ptff(&qui, माप(qui), PTFF_QUI) == 0)
		initial_leap_seconds = (अचिन्हित दीर्घ)
			((दीर्घ) qui.old_leap * 4096000000L);
पूर्ण

/*
 * Scheduler घड़ी - वापसs current समय in nanosec units.
 */
अचिन्हित दीर्घ दीर्घ notrace sched_घड़ी(व्योम)
अणु
	वापस tod_to_ns(get_tod_घड़ी_monotonic());
पूर्ण
NOKPROBE_SYMBOL(sched_घड़ी);

अटल व्योम ext_to_बारpec64(जोड़ tod_घड़ी *clk, काष्ठा बारpec64 *xt)
अणु
	अचिन्हित दीर्घ rem, sec, nsec;

	sec = clk->us;
	rem = करो_भाग(sec, 1000000);
	nsec = ((clk->sus + (rem << 12)) * 125) >> 9;
	xt->tv_sec = sec;
	xt->tv_nsec = nsec;
पूर्ण

व्योम घड़ी_comparator_work(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd;

	S390_lowcore.घड़ी_comparator = घड़ी_comparator_max;
	cd = this_cpu_ptr(&comparators);
	cd->event_handler(cd);
पूर्ण

अटल पूर्णांक s390_next_event(अचिन्हित दीर्घ delta,
			   काष्ठा घड़ी_event_device *evt)
अणु
	S390_lowcore.घड़ी_comparator = get_tod_घड़ी() + delta;
	set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);
	वापस 0;
पूर्ण

/*
 * Set up lowcore and control रेजिस्टर of the current cpu to
 * enable TOD घड़ी and घड़ी comparator पूर्णांकerrupts.
 */
व्योम init_cpu_समयr(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd;
	पूर्णांक cpu;

	S390_lowcore.घड़ी_comparator = घड़ी_comparator_max;
	set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);

	cpu = smp_processor_id();
	cd = &per_cpu(comparators, cpu);
	cd->name		= "comparator";
	cd->features		= CLOCK_EVT_FEAT_ONESHOT;
	cd->mult		= 16777;
	cd->shअगरt		= 12;
	cd->min_delta_ns	= 1;
	cd->min_delta_ticks	= 1;
	cd->max_delta_ns	= दीर्घ_उच्च;
	cd->max_delta_ticks	= अच_दीर्घ_उच्च;
	cd->rating		= 400;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= s390_next_event;

	घड़ीevents_रेजिस्टर_device(cd);

	/* Enable घड़ी comparator समयr पूर्णांकerrupt. */
	__ctl_set_bit(0,11);

	/* Always allow the timing alert बाह्यal पूर्णांकerrupt. */
	__ctl_set_bit(0, 4);
पूर्ण

अटल व्योम घड़ी_comparator_पूर्णांकerrupt(काष्ठा ext_code ext_code,
				       अचिन्हित पूर्णांक param32,
				       अचिन्हित दीर्घ param64)
अणु
	inc_irq_stat(IRQEXT_CLK);
	अगर (S390_lowcore.घड़ी_comparator == घड़ी_comparator_max)
		set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);
पूर्ण

अटल व्योम stp_timing_alert(काष्ठा stp_irq_parm *);

अटल व्योम timing_alert_पूर्णांकerrupt(काष्ठा ext_code ext_code,
				   अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	inc_irq_stat(IRQEXT_TLA);
	अगर (param32 & 0x00038000)
		stp_timing_alert((काष्ठा stp_irq_parm *) &param32);
पूर्ण

अटल व्योम stp_reset(व्योम);

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	जोड़ tod_घड़ी clk;
	u64 delta;

	delta = initial_leap_seconds + TOD_UNIX_EPOCH;
	store_tod_घड़ी_ext(&clk);
	clk.eitod -= delta;
	ext_to_बारpec64(&clk, ts);
पूर्ण

व्योम __init पढ़ो_persistent_wall_and_boot_offset(काष्ठा बारpec64 *wall_समय,
						 काष्ठा बारpec64 *boot_offset)
अणु
	काष्ठा बारpec64 boot_समय;
	जोड़ tod_घड़ी clk;
	u64 delta;

	delta = initial_leap_seconds + TOD_UNIX_EPOCH;
	clk = tod_घड़ी_base;
	clk.eitod -= delta;
	ext_to_बारpec64(&clk, &boot_समय);

	पढ़ो_persistent_घड़ी64(wall_समय);
	*boot_offset = बारpec64_sub(*wall_समय, boot_समय);
पूर्ण

अटल u64 पढ़ो_tod_घड़ी(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ now, adj;

	preempt_disable(); /* protect from changes to steering parameters */
	now = get_tod_घड़ी();
	adj = tod_steering_end - now;
	अगर (unlikely((s64) adj > 0))
		/*
		 * manually steer by 1 cycle every 2^16 cycles. This
		 * corresponds to shअगरting the tod delta by 15. 1s is
		 * thereक्रमe steered in ~9h. The adjust will decrease
		 * over समय, until it finally reaches 0.
		 */
		now += (tod_steering_delta < 0) ? (adj >> 15) : -(adj >> 15);
	preempt_enable();
	वापस now;
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_tod = अणु
	.name		= "tod",
	.rating		= 400,
	.पढ़ो		= पढ़ो_tod_घड़ी,
	.mask		= CLOCKSOURCE_MASK(64),
	.mult		= 1000,
	.shअगरt		= 12,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.vdso_घड़ी_mode = VDSO_CLOCKMODE_TOD,
पूर्ण;

काष्ठा घड़ीsource * __init घड़ीsource_शेष_घड़ी(व्योम)
अणु
	वापस &घड़ीsource_tod;
पूर्ण

/*
 * Initialize the TOD घड़ी and the CPU समयr of
 * the boot cpu.
 */
व्योम __init समय_init(व्योम)
अणु
	/* Reset समय synchronization पूर्णांकerfaces. */
	stp_reset();

	/* request the घड़ी comparator बाह्यal पूर्णांकerrupt */
	अगर (रेजिस्टर_बाह्यal_irq(EXT_IRQ_CLK_COMP, घड़ी_comparator_पूर्णांकerrupt))
		panic("Couldn't request external interrupt 0x1004");

	/* request the timing alert बाह्यal पूर्णांकerrupt */
	अगर (रेजिस्टर_बाह्यal_irq(EXT_IRQ_TIMING_ALERT, timing_alert_पूर्णांकerrupt))
		panic("Couldn't request external interrupt 0x1406");

	अगर (__घड़ीsource_रेजिस्टर(&घड़ीsource_tod) != 0)
		panic("Could not register TOD clock source");

	/* Enable TOD घड़ी पूर्णांकerrupts on the boot cpu. */
	init_cpu_समयr();

	/* Enable cpu समयr पूर्णांकerrupts on the boot cpu. */
	vसमय_init();
पूर्ण

अटल DEFINE_PER_CPU(atomic_t, घड़ी_sync_word);
अटल DEFINE_MUTEX(stp_mutex);
अटल अचिन्हित दीर्घ घड़ी_sync_flags;

#घोषणा CLOCK_SYNC_HAS_STP		0
#घोषणा CLOCK_SYNC_STP			1
#घोषणा CLOCK_SYNC_STPINFO_VALID	2

/*
 * The get_घड़ी function क्रम the physical घड़ी. It will get the current
 * TOD घड़ी, subtract the LPAR offset and ग_लिखो the result to *घड़ी.
 * The function वापसs 0 अगर the घड़ी is in sync with the बाह्यal समय
 * source. If the घड़ी mode is local it will वापस -EOPNOTSUPP and
 * -EAGAIN अगर the घड़ी is not in sync with the बाह्यal reference.
 */
पूर्णांक get_phys_घड़ी(अचिन्हित दीर्घ *घड़ी)
अणु
	atomic_t *sw_ptr;
	अचिन्हित पूर्णांक sw0, sw1;

	sw_ptr = &get_cpu_var(घड़ी_sync_word);
	sw0 = atomic_पढ़ो(sw_ptr);
	*घड़ी = get_tod_घड़ी() - lpar_offset;
	sw1 = atomic_पढ़ो(sw_ptr);
	put_cpu_var(घड़ी_sync_word);
	अगर (sw0 == sw1 && (sw0 & 0x80000000U))
		/* Success: समय is in sync. */
		वापस 0;
	अगर (!test_bit(CLOCK_SYNC_HAS_STP, &घड़ी_sync_flags))
		वापस -EOPNOTSUPP;
	अगर (!test_bit(CLOCK_SYNC_STP, &घड़ी_sync_flags))
		वापस -EACCES;
	वापस -EAGAIN;
पूर्ण
EXPORT_SYMBOL(get_phys_घड़ी);

/*
 * Make get_phys_घड़ी() वापस -EAGAIN.
 */
अटल व्योम disable_sync_घड़ी(व्योम *dummy)
अणु
	atomic_t *sw_ptr = this_cpu_ptr(&घड़ी_sync_word);
	/*
	 * Clear the in-sync bit 2^31. All get_phys_घड़ी calls will
	 * fail until the sync bit is turned back on. In addition
	 * increase the "sequence" counter to aव्योम the race of an
	 * stp event and the complete recovery against get_phys_घड़ी.
	 */
	atomic_andnot(0x80000000, sw_ptr);
	atomic_inc(sw_ptr);
पूर्ण

/*
 * Make get_phys_घड़ी() वापस 0 again.
 * Needs to be called from a context disabled क्रम preemption.
 */
अटल व्योम enable_sync_घड़ी(व्योम)
अणु
	atomic_t *sw_ptr = this_cpu_ptr(&घड़ी_sync_word);
	atomic_or(0x80000000, sw_ptr);
पूर्ण

/*
 * Function to check अगर the घड़ी is in sync.
 */
अटल अंतरभूत पूर्णांक check_sync_घड़ी(व्योम)
अणु
	atomic_t *sw_ptr;
	पूर्णांक rc;

	sw_ptr = &get_cpu_var(घड़ी_sync_word);
	rc = (atomic_पढ़ो(sw_ptr) & 0x80000000U) != 0;
	put_cpu_var(घड़ी_sync_word);
	वापस rc;
पूर्ण

/*
 * Apply घड़ी delta to the global data काष्ठाures.
 * This is called once on the CPU that perक्रमmed the घड़ी sync.
 */
अटल व्योम घड़ी_sync_global(अचिन्हित दीर्घ delta)
अणु
	अचिन्हित दीर्घ now, adj;
	काष्ठा ptff_qto qto;
	पूर्णांक cs;

	/* Fixup the monotonic sched घड़ी. */
	tod_घड़ी_base.eitod += delta;
	/* Adjust TOD steering parameters. */
	now = get_tod_घड़ी();
	adj = tod_steering_end - now;
	अगर (unlikely((s64) adj >= 0))
		/* Calculate how much of the old adjusपंचांगent is left. */
		tod_steering_delta = (tod_steering_delta < 0) ?
			-(adj >> 15) : (adj >> 15);
	tod_steering_delta += delta;
	अगर ((असल(tod_steering_delta) >> 48) != 0)
		panic("TOD clock sync offset %li is too large to drift\n",
		      tod_steering_delta);
	tod_steering_end = now + (असल(tod_steering_delta) << 15);
	क्रम (cs = 0; cs < CS_BASES; cs++) अणु
		vdso_data[cs].arch_data.tod_steering_end = tod_steering_end;
		vdso_data[cs].arch_data.tod_steering_delta = tod_steering_delta;
	पूर्ण

	/* Update LPAR offset. */
	अगर (ptff_query(PTFF_QTO) && ptff(&qto, माप(qto), PTFF_QTO) == 0)
		lpar_offset = qto.tod_epoch_dअगरference;
	/* Call the TOD घड़ी change notअगरier. */
	atomic_notअगरier_call_chain(&s390_epoch_delta_notअगरier, 0, &delta);
पूर्ण

/*
 * Apply घड़ी delta to the per-CPU data काष्ठाures of this CPU.
 * This is called क्रम each online CPU after the call to घड़ी_sync_global.
 */
अटल व्योम घड़ी_sync_local(अचिन्हित दीर्घ delta)
अणु
	/* Add the delta to the घड़ी comparator. */
	अगर (S390_lowcore.घड़ी_comparator != घड़ी_comparator_max) अणु
		S390_lowcore.घड़ी_comparator += delta;
		set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);
	पूर्ण
	/* Adjust the last_update_घड़ी समय-stamp. */
	S390_lowcore.last_update_घड़ी += delta;
पूर्ण

/* Single thपढ़ोed workqueue used क्रम stp sync events */
अटल काष्ठा workqueue_काष्ठा *समय_sync_wq;

अटल व्योम __init समय_init_wq(व्योम)
अणु
	अगर (समय_sync_wq)
		वापस;
	समय_sync_wq = create_singlethपढ़ो_workqueue("timesync");
पूर्ण

काष्ठा घड़ी_sync_data अणु
	atomic_t cpus;
	पूर्णांक in_sync;
	अचिन्हित दीर्घ घड़ी_delta;
पूर्ण;

/*
 * Server Time Protocol (STP) code.
 */
अटल bool stp_online;
अटल काष्ठा stp_sstpi stp_info;
अटल व्योम *stp_page;

अटल व्योम stp_work_fn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(stp_work, stp_work_fn);
अटल काष्ठा समयr_list stp_समयr;

अटल पूर्णांक __init early_parse_stp(अक्षर *p)
अणु
	वापस kstrtobool(p, &stp_online);
पूर्ण
early_param("stp", early_parse_stp);

/*
 * Reset STP attachment.
 */
अटल व्योम __init stp_reset(व्योम)
अणु
	पूर्णांक rc;

	stp_page = (व्योम *) get_zeroed_page(GFP_ATOMIC);
	rc = chsc_sstpc(stp_page, STP_OP_CTRL, 0x0000, शून्य);
	अगर (rc == 0)
		set_bit(CLOCK_SYNC_HAS_STP, &घड़ी_sync_flags);
	अन्यथा अगर (stp_online) अणु
		pr_warn("The real or virtual hardware system does not provide an STP interface\n");
		मुक्त_page((अचिन्हित दीर्घ) stp_page);
		stp_page = शून्य;
		stp_online = false;
	पूर्ण
पूर्ण

अटल व्योम stp_समयout(काष्ठा समयr_list *unused)
अणु
	queue_work(समय_sync_wq, &stp_work);
पूर्ण

अटल पूर्णांक __init stp_init(व्योम)
अणु
	अगर (!test_bit(CLOCK_SYNC_HAS_STP, &घड़ी_sync_flags))
		वापस 0;
	समयr_setup(&stp_समयr, stp_समयout, 0);
	समय_init_wq();
	अगर (!stp_online)
		वापस 0;
	queue_work(समय_sync_wq, &stp_work);
	वापस 0;
पूर्ण

arch_initcall(stp_init);

/*
 * STP timing alert. There are three causes:
 * 1) timing status change
 * 2) link availability change
 * 3) समय control parameter change
 * In all three हालs we are only पूर्णांकerested in the घड़ी source state.
 * If a STP घड़ी source is now available use it.
 */
अटल व्योम stp_timing_alert(काष्ठा stp_irq_parm *पूर्णांकparm)
अणु
	अगर (पूर्णांकparm->tsc || पूर्णांकparm->lac || पूर्णांकparm->tcpc)
		queue_work(समय_sync_wq, &stp_work);
पूर्ण

/*
 * STP sync check machine check. This is called when the timing state
 * changes from the synchronized state to the unsynchronized state.
 * After a STP sync check the घड़ी is not in sync. The machine check
 * is broadcasted to all cpus at the same समय.
 */
पूर्णांक stp_sync_check(व्योम)
अणु
	disable_sync_घड़ी(शून्य);
	वापस 1;
पूर्ण

/*
 * STP island condition machine check. This is called when an attached
 * server  attempts to communicate over an STP link and the servers
 * have matching CTN ids and have a valid stratum-1 configuration
 * but the configurations करो not match.
 */
पूर्णांक stp_island_check(व्योम)
अणु
	disable_sync_घड़ी(शून्य);
	वापस 1;
पूर्ण

व्योम stp_queue_work(व्योम)
अणु
	queue_work(समय_sync_wq, &stp_work);
पूर्ण

अटल पूर्णांक __store_stpinfo(व्योम)
अणु
	पूर्णांक rc = chsc_sstpi(stp_page, &stp_info, माप(काष्ठा stp_sstpi));

	अगर (rc)
		clear_bit(CLOCK_SYNC_STPINFO_VALID, &घड़ी_sync_flags);
	अन्यथा
		set_bit(CLOCK_SYNC_STPINFO_VALID, &घड़ी_sync_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक stpinfo_valid(व्योम)
अणु
	वापस stp_online && test_bit(CLOCK_SYNC_STPINFO_VALID, &घड़ी_sync_flags);
पूर्ण

अटल पूर्णांक stp_sync_घड़ी(व्योम *data)
अणु
	काष्ठा घड़ी_sync_data *sync = data;
	u64 घड़ी_delta, flags;
	अटल पूर्णांक first;
	पूर्णांक rc;

	enable_sync_घड़ी();
	अगर (xchg(&first, 1) == 0) अणु
		/* Wait until all other cpus entered the sync function. */
		जबतक (atomic_पढ़ो(&sync->cpus) != 0)
			cpu_relax();
		rc = 0;
		अगर (stp_info.toकरोff[0] || stp_info.toकरोff[1] ||
		    stp_info.toकरोff[2] || stp_info.toकरोff[3] ||
		    stp_info.पंचांगd != 2) अणु
			flags = vdso_update_begin();
			rc = chsc_sstpc(stp_page, STP_OP_SYNC, 0,
					&घड़ी_delta);
			अगर (rc == 0) अणु
				sync->घड़ी_delta = घड़ी_delta;
				घड़ी_sync_global(घड़ी_delta);
				rc = __store_stpinfo();
				अगर (rc == 0 && stp_info.पंचांगd != 2)
					rc = -EAGAIN;
			पूर्ण
			vdso_update_end(flags);
		पूर्ण
		sync->in_sync = rc ? -EAGAIN : 1;
		xchg(&first, 0);
	पूर्ण अन्यथा अणु
		/* Slave */
		atomic_dec(&sync->cpus);
		/* Wait क्रम in_sync to be set. */
		जबतक (READ_ONCE(sync->in_sync) == 0)
			__udelay(1);
	पूर्ण
	अगर (sync->in_sync != 1)
		/* Didn't work. Clear per-cpu in sync bit again. */
		disable_sync_घड़ी(शून्य);
	/* Apply घड़ी delta to per-CPU fields of this CPU. */
	घड़ी_sync_local(sync->घड़ी_delta);

	वापस 0;
पूर्ण

अटल पूर्णांक stp_clear_leap(व्योम)
अणु
	काष्ठा __kernel_समयx txc;
	पूर्णांक ret;

	स_रखो(&txc, 0, माप(txc));

	ret = करो_adjसमयx(&txc);
	अगर (ret < 0)
		वापस ret;

	txc.modes = ADJ_STATUS;
	txc.status &= ~(STA_INS|STA_DEL);
	वापस करो_adjसमयx(&txc);
पूर्ण

अटल व्योम stp_check_leap(व्योम)
अणु
	काष्ठा stp_stzi stzi;
	काष्ठा stp_lsoib *lsoib = &stzi.lsoib;
	काष्ठा __kernel_समयx txc;
	पूर्णांक64_t समयdअगरf;
	पूर्णांक leapdअगरf, ret;

	अगर (!stp_info.lu || !check_sync_घड़ी()) अणु
		/*
		 * Either a scheduled leap second was हटाओd by the चालक,
		 * or STP is out of sync. In both हालs, clear the leap second
		 * kernel flags.
		 */
		अगर (stp_clear_leap() < 0)
			pr_err("failed to clear leap second flags\n");
		वापस;
	पूर्ण

	अगर (chsc_stzi(stp_page, &stzi, माप(stzi))) अणु
		pr_err("stzi failed\n");
		वापस;
	पूर्ण

	समयdअगरf = tod_to_ns(lsoib->nlsout - get_tod_घड़ी()) / NSEC_PER_SEC;
	leapdअगरf = lsoib->nlso - lsoib->also;

	अगर (leapdअगरf != 1 && leapdअगरf != -1) अणु
		pr_err("Cannot schedule %d leap seconds\n", leapdअगरf);
		वापस;
	पूर्ण

	अगर (समयdअगरf < 0) अणु
		अगर (stp_clear_leap() < 0)
			pr_err("failed to clear leap second flags\n");
	पूर्ण अन्यथा अगर (समयdअगरf < 7200) अणु
		स_रखो(&txc, 0, माप(txc));
		ret = करो_adjसमयx(&txc);
		अगर (ret < 0)
			वापस;

		txc.modes = ADJ_STATUS;
		अगर (leapdअगरf > 0)
			txc.status |= STA_INS;
		अन्यथा
			txc.status |= STA_DEL;
		ret = करो_adjसमयx(&txc);
		अगर (ret < 0)
			pr_err("failed to set leap second flags\n");
		/* arm Timer to clear leap second flags */
		mod_समयr(&stp_समयr, jअगरfies + msecs_to_jअगरfies(14400 * MSEC_PER_SEC));
	पूर्ण अन्यथा अणु
		/* The day the leap second is scheduled क्रम hasn't been reached. Retry
		 * in one hour.
		 */
		mod_समयr(&stp_समयr, jअगरfies + msecs_to_jअगरfies(3600 * MSEC_PER_SEC));
	पूर्ण
पूर्ण

/*
 * STP work. Check क्रम the STP state and take over the घड़ी
 * synchronization अगर the STP घड़ी source is usable.
 */
अटल व्योम stp_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा घड़ी_sync_data stp_sync;
	पूर्णांक rc;

	/* prevent multiple execution. */
	mutex_lock(&stp_mutex);

	अगर (!stp_online) अणु
		chsc_sstpc(stp_page, STP_OP_CTRL, 0x0000, शून्य);
		del_समयr_sync(&stp_समयr);
		जाओ out_unlock;
	पूर्ण

	rc = chsc_sstpc(stp_page, STP_OP_CTRL, 0xf0e0, शून्य);
	अगर (rc)
		जाओ out_unlock;

	rc = __store_stpinfo();
	अगर (rc || stp_info.c == 0)
		जाओ out_unlock;

	/* Skip synchronization अगर the घड़ी is alपढ़ोy in sync. */
	अगर (!check_sync_घड़ी()) अणु
		स_रखो(&stp_sync, 0, माप(stp_sync));
		cpus_पढ़ो_lock();
		atomic_set(&stp_sync.cpus, num_online_cpus() - 1);
		stop_machine_cpuslocked(stp_sync_घड़ी, &stp_sync, cpu_online_mask);
		cpus_पढ़ो_unlock();
	पूर्ण

	अगर (!check_sync_घड़ी())
		/*
		 * There is a usable घड़ी but the synchonization failed.
		 * Retry after a second.
		 */
		mod_समयr(&stp_समयr, jअगरfies + msecs_to_jअगरfies(MSEC_PER_SEC));
	अन्यथा अगर (stp_info.lu)
		stp_check_leap();

out_unlock:
	mutex_unlock(&stp_mutex);
पूर्ण

/*
 * STP subsys sysfs पूर्णांकerface functions
 */
अटल काष्ठा bus_type stp_subsys = अणु
	.name		= "stp",
	.dev_name	= "stp",
पूर्ण;

अटल sमाप_प्रकार ctn_id_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid())
		ret = प्र_लिखो(buf, "%016lx\n",
			      *(अचिन्हित दीर्घ *) stp_info.ctnid);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(ctn_id);

अटल sमाप_प्रकार ctn_type_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid())
		ret = प्र_लिखो(buf, "%i\n", stp_info.ctn);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(ctn_type);

अटल sमाप_प्रकार dst_offset_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid() && (stp_info.vbits & 0x2000))
		ret = प्र_लिखो(buf, "%i\n", (पूर्णांक)(s16) stp_info.dsto);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(dst_offset);

अटल sमाप_प्रकार leap_seconds_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid() && (stp_info.vbits & 0x8000))
		ret = प्र_लिखो(buf, "%i\n", (पूर्णांक)(s16) stp_info.leaps);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(leap_seconds);

अटल sमाप_प्रकार leap_seconds_scheduled_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा stp_stzi stzi;
	sमाप_प्रकार ret;

	mutex_lock(&stp_mutex);
	अगर (!stpinfo_valid() || !(stp_info.vbits & 0x8000) || !stp_info.lu) अणु
		mutex_unlock(&stp_mutex);
		वापस -ENODATA;
	पूर्ण

	ret = chsc_stzi(stp_page, &stzi, माप(stzi));
	mutex_unlock(&stp_mutex);
	अगर (ret < 0)
		वापस ret;

	अगर (!stzi.lsoib.p)
		वापस प्र_लिखो(buf, "0,0\n");

	वापस प्र_लिखो(buf, "%lu,%d\n",
		       tod_to_ns(stzi.lsoib.nlsout - TOD_UNIX_EPOCH) / NSEC_PER_SEC,
		       stzi.lsoib.nlso - stzi.lsoib.also);
पूर्ण

अटल DEVICE_ATTR_RO(leap_seconds_scheduled);

अटल sमाप_प्रकार stratum_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid())
		ret = प्र_लिखो(buf, "%i\n", (पूर्णांक)(s16) stp_info.stratum);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(stratum);

अटल sमाप_प्रकार समय_offset_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid() && (stp_info.vbits & 0x0800))
		ret = प्र_लिखो(buf, "%i\n", (पूर्णांक) stp_info.tto);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(समय_offset);

अटल sमाप_प्रकार समय_zone_offset_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid() && (stp_info.vbits & 0x4000))
		ret = प्र_लिखो(buf, "%i\n", (पूर्णांक)(s16) stp_info.tzo);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(समय_zone_offset);

अटल sमाप_प्रकार timing_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid())
		ret = प्र_लिखो(buf, "%i\n", stp_info.पंचांगd);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(timing_mode);

अटल sमाप_प्रकार timing_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	sमाप_प्रकार ret = -ENODATA;

	mutex_lock(&stp_mutex);
	अगर (stpinfo_valid())
		ret = प्र_लिखो(buf, "%i\n", stp_info.tst);
	mutex_unlock(&stp_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(timing_state);

अटल sमाप_प्रकार online_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", stp_online);
पूर्ण

अटल sमाप_प्रकार online_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक value;

	value = simple_म_से_अदीर्घ(buf, शून्य, 0);
	अगर (value != 0 && value != 1)
		वापस -EINVAL;
	अगर (!test_bit(CLOCK_SYNC_HAS_STP, &घड़ी_sync_flags))
		वापस -EOPNOTSUPP;
	mutex_lock(&stp_mutex);
	stp_online = value;
	अगर (stp_online)
		set_bit(CLOCK_SYNC_STP, &घड़ी_sync_flags);
	अन्यथा
		clear_bit(CLOCK_SYNC_STP, &घड़ी_sync_flags);
	queue_work(समय_sync_wq, &stp_work);
	mutex_unlock(&stp_mutex);
	वापस count;
पूर्ण

/*
 * Can't use DEVICE_ATTR because the attribute should be named
 * stp/online but dev_attr_online alपढ़ोy exists in this file ..
 */
अटल DEVICE_ATTR_RW(online);

अटल काष्ठा attribute *stp_dev_attrs[] = अणु
	&dev_attr_ctn_id.attr,
	&dev_attr_ctn_type.attr,
	&dev_attr_dst_offset.attr,
	&dev_attr_leap_seconds.attr,
	&dev_attr_online.attr,
	&dev_attr_leap_seconds_scheduled.attr,
	&dev_attr_stratum.attr,
	&dev_attr_समय_offset.attr,
	&dev_attr_समय_zone_offset.attr,
	&dev_attr_timing_mode.attr,
	&dev_attr_timing_state.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(stp_dev);

अटल पूर्णांक __init stp_init_sysfs(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&stp_subsys, stp_dev_groups);
पूर्ण

device_initcall(stp_init_sysfs);
