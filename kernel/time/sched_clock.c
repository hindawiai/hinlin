<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic sched_घड़ी() support, to extend low level hardware समय
 * counters to full 64-bit ns values.
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/bitops.h>

#समावेश "timekeeping.h"

/**
 * काष्ठा घड़ी_data - all data needed क्रम sched_घड़ी() (including
 *                     registration of a new घड़ी source)
 *
 * @seq:		Sequence counter क्रम protecting updates. The lowest
 *			bit is the index क्रम @पढ़ो_data.
 * @पढ़ो_data:		Data required to पढ़ो from sched_घड़ी.
 * @wrap_kt:		Duration क्रम which घड़ी can run beक्रमe wrapping.
 * @rate:		Tick rate of the रेजिस्टरed घड़ी.
 * @actual_पढ़ो_sched_घड़ी: Registered hardware level घड़ी पढ़ो function.
 *
 * The ordering of this काष्ठाure has been chosen to optimize cache
 * perक्रमmance. In particular 'seq' and 'read_data[0]' (combined) should fit
 * पूर्णांकo a single 64-byte cache line.
 */
काष्ठा घड़ी_data अणु
	seqcount_latch_t	seq;
	काष्ठा घड़ी_पढ़ो_data	पढ़ो_data[2];
	kसमय_प्रकार			wrap_kt;
	अचिन्हित दीर्घ		rate;

	u64 (*actual_पढ़ो_sched_घड़ी)(व्योम);
पूर्ण;

अटल काष्ठा hrसमयr sched_घड़ी_प्रकारimer;
अटल पूर्णांक irqसमय = -1;

core_param(irqसमय, irqसमय, पूर्णांक, 0400);

अटल u64 notrace jअगरfy_sched_घड़ी_पढ़ो(व्योम)
अणु
	/*
	 * We करोn't need to use get_jअगरfies_64 on 32-bit arches here
	 * because we रेजिस्टर with BITS_PER_LONG
	 */
	वापस (u64)(jअगरfies - INITIAL_JIFFIES);
पूर्ण

अटल काष्ठा घड़ी_data cd ____cacheline_aligned = अणु
	.पढ़ो_data[0] = अणु .mult = NSEC_PER_SEC / HZ,
			  .पढ़ो_sched_घड़ी = jअगरfy_sched_घड़ी_पढ़ो, पूर्ण,
	.actual_पढ़ो_sched_घड़ी = jअगरfy_sched_घड़ी_पढ़ो,
पूर्ण;

अटल अंतरभूत u64 notrace cyc_to_ns(u64 cyc, u32 mult, u32 shअगरt)
अणु
	वापस (cyc * mult) >> shअगरt;
पूर्ण

notrace काष्ठा घड़ी_पढ़ो_data *sched_घड़ी_पढ़ो_begin(अचिन्हित पूर्णांक *seq)
अणु
	*seq = raw_पढ़ो_seqcount_latch(&cd.seq);
	वापस cd.पढ़ो_data + (*seq & 1);
पूर्ण

notrace पूर्णांक sched_घड़ी_पढ़ो_retry(अचिन्हित पूर्णांक seq)
अणु
	वापस पढ़ो_seqcount_latch_retry(&cd.seq, seq);
पूर्ण

अचिन्हित दीर्घ दीर्घ notrace sched_घड़ी(व्योम)
अणु
	u64 cyc, res;
	अचिन्हित पूर्णांक seq;
	काष्ठा घड़ी_पढ़ो_data *rd;

	करो अणु
		rd = sched_घड़ी_पढ़ो_begin(&seq);

		cyc = (rd->पढ़ो_sched_घड़ी() - rd->epoch_cyc) &
		      rd->sched_घड़ी_mask;
		res = rd->epoch_ns + cyc_to_ns(cyc, rd->mult, rd->shअगरt);
	पूर्ण जबतक (sched_घड़ी_पढ़ो_retry(seq));

	वापस res;
पूर्ण

/*
 * Updating the data required to पढ़ो the घड़ी.
 *
 * sched_घड़ी() will never observe mis-matched data even अगर called from
 * an NMI. We करो this by मुख्यtaining an odd/even copy of the data and
 * steering sched_घड़ी() to one or the other using a sequence counter.
 * In order to preserve the data cache profile of sched_घड़ी() as much
 * as possible the प्रणाली reverts back to the even copy when the update
 * completes; the odd copy is used *only* during an update.
 */
अटल व्योम update_घड़ी_पढ़ो_data(काष्ठा घड़ी_पढ़ो_data *rd)
अणु
	/* update the backup (odd) copy with the new data */
	cd.पढ़ो_data[1] = *rd;

	/* steer पढ़ोers towards the odd copy */
	raw_ग_लिखो_seqcount_latch(&cd.seq);

	/* now its safe क्रम us to update the normal (even) copy */
	cd.पढ़ो_data[0] = *rd;

	/* चयन पढ़ोers back to the even copy */
	raw_ग_लिखो_seqcount_latch(&cd.seq);
पूर्ण

/*
 * Atomically update the sched_घड़ी() epoch.
 */
अटल व्योम update_sched_घड़ी(व्योम)
अणु
	u64 cyc;
	u64 ns;
	काष्ठा घड़ी_पढ़ो_data rd;

	rd = cd.पढ़ो_data[0];

	cyc = cd.actual_पढ़ो_sched_घड़ी();
	ns = rd.epoch_ns + cyc_to_ns((cyc - rd.epoch_cyc) & rd.sched_घड़ी_mask, rd.mult, rd.shअगरt);

	rd.epoch_ns = ns;
	rd.epoch_cyc = cyc;

	update_घड़ी_पढ़ो_data(&rd);
पूर्ण

अटल क्रमागत hrसमयr_restart sched_घड़ी_poll(काष्ठा hrसमयr *hrt)
अणु
	update_sched_घड़ी();
	hrसमयr_क्रमward_now(hrt, cd.wrap_kt);

	वापस HRTIMER_RESTART;
पूर्ण

व्योम __init
sched_घड़ी_रेजिस्टर(u64 (*पढ़ो)(व्योम), पूर्णांक bits, अचिन्हित दीर्घ rate)
अणु
	u64 res, wrap, new_mask, new_epoch, cyc, ns;
	u32 new_mult, new_shअगरt;
	अचिन्हित दीर्घ r, flags;
	अक्षर r_unit;
	काष्ठा घड़ी_पढ़ो_data rd;

	अगर (cd.rate > rate)
		वापस;

	/* Cannot रेजिस्टर a sched_घड़ी with पूर्णांकerrupts on */
	local_irq_save(flags);

	/* Calculate the mult/shअगरt to convert counter ticks to ns. */
	घड़ीs_calc_mult_shअगरt(&new_mult, &new_shअगरt, rate, NSEC_PER_SEC, 3600);

	new_mask = CLOCKSOURCE_MASK(bits);
	cd.rate = rate;

	/* Calculate how many nanosecs until we risk wrapping */
	wrap = घड़ीs_calc_max_nsecs(new_mult, new_shअगरt, 0, new_mask, शून्य);
	cd.wrap_kt = ns_to_kसमय(wrap);

	rd = cd.पढ़ो_data[0];

	/* Update epoch क्रम new counter and update 'epoch_ns' from old counter*/
	new_epoch = पढ़ो();
	cyc = cd.actual_पढ़ो_sched_घड़ी();
	ns = rd.epoch_ns + cyc_to_ns((cyc - rd.epoch_cyc) & rd.sched_घड़ी_mask, rd.mult, rd.shअगरt);
	cd.actual_पढ़ो_sched_घड़ी = पढ़ो;

	rd.पढ़ो_sched_घड़ी	= पढ़ो;
	rd.sched_घड़ी_mask	= new_mask;
	rd.mult			= new_mult;
	rd.shअगरt		= new_shअगरt;
	rd.epoch_cyc		= new_epoch;
	rd.epoch_ns		= ns;

	update_घड़ी_पढ़ो_data(&rd);

	अगर (sched_घड़ी_प्रकारimer.function != शून्य) अणु
		/* update समयout क्रम घड़ी wrap */
		hrसमयr_start(&sched_घड़ी_प्रकारimer, cd.wrap_kt,
			      HRTIMER_MODE_REL_HARD);
	पूर्ण

	r = rate;
	अगर (r >= 4000000) अणु
		r /= 1000000;
		r_unit = 'M';
	पूर्ण अन्यथा अणु
		अगर (r >= 1000) अणु
			r /= 1000;
			r_unit = 'k';
		पूर्ण अन्यथा अणु
			r_unit = ' ';
		पूर्ण
	पूर्ण

	/* Calculate the ns resolution of this counter */
	res = cyc_to_ns(1ULL, new_mult, new_shअगरt);

	pr_info("sched_clock: %u bits at %lu%cHz, resolution %lluns, wraps every %lluns\n",
		bits, r, r_unit, res, wrap);

	/* Enable IRQ समय accounting अगर we have a fast enough sched_घड़ी() */
	अगर (irqसमय > 0 || (irqसमय == -1 && rate >= 1000000))
		enable_sched_घड़ी_irqसमय();

	local_irq_restore(flags);

	pr_debug("Registered %pS as sched_clock source\n", पढ़ो);
पूर्ण

व्योम __init generic_sched_घड़ी_init(व्योम)
अणु
	/*
	 * If no sched_घड़ी() function has been provided at that poपूर्णांक,
	 * make it the final one.
	 */
	अगर (cd.actual_पढ़ो_sched_घड़ी == jअगरfy_sched_घड़ी_पढ़ो)
		sched_घड़ी_रेजिस्टर(jअगरfy_sched_घड़ी_पढ़ो, BITS_PER_LONG, HZ);

	update_sched_घड़ी();

	/*
	 * Start the समयr to keep sched_घड़ी() properly updated and
	 * sets the initial epoch.
	 */
	hrसमयr_init(&sched_घड़ी_प्रकारimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	sched_घड़ी_प्रकारimer.function = sched_घड़ी_poll;
	hrसमयr_start(&sched_घड़ी_प्रकारimer, cd.wrap_kt, HRTIMER_MODE_REL_HARD);
पूर्ण

/*
 * Clock पढ़ो function क्रम use when the घड़ी is suspended.
 *
 * This function makes it appear to sched_घड़ी() as अगर the घड़ी
 * stopped counting at its last update.
 *
 * This function must only be called from the critical
 * section in sched_घड़ी(). It relies on the पढ़ो_seqcount_retry()
 * at the end of the critical section to be sure we observe the
 * correct copy of 'epoch_cyc'.
 */
अटल u64 notrace suspended_sched_घड़ी_पढ़ो(व्योम)
अणु
	अचिन्हित पूर्णांक seq = raw_पढ़ो_seqcount_latch(&cd.seq);

	वापस cd.पढ़ो_data[seq & 1].epoch_cyc;
पूर्ण

पूर्णांक sched_घड़ी_suspend(व्योम)
अणु
	काष्ठा घड़ी_पढ़ो_data *rd = &cd.पढ़ो_data[0];

	update_sched_घड़ी();
	hrसमयr_cancel(&sched_घड़ी_प्रकारimer);
	rd->पढ़ो_sched_घड़ी = suspended_sched_घड़ी_पढ़ो;

	वापस 0;
पूर्ण

व्योम sched_घड़ी_resume(व्योम)
अणु
	काष्ठा घड़ी_पढ़ो_data *rd = &cd.पढ़ो_data[0];

	rd->epoch_cyc = cd.actual_पढ़ो_sched_घड़ी();
	hrसमयr_start(&sched_घड़ी_प्रकारimer, cd.wrap_kt, HRTIMER_MODE_REL_HARD);
	rd->पढ़ो_sched_घड़ी = cd.actual_पढ़ो_sched_घड़ी;
पूर्ण

अटल काष्ठा syscore_ops sched_घड़ी_ops = अणु
	.suspend	= sched_घड़ी_suspend,
	.resume		= sched_घड़ी_resume,
पूर्ण;

अटल पूर्णांक __init sched_घड़ी_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&sched_घड़ी_ops);

	वापस 0;
पूर्ण
device_initcall(sched_घड़ी_syscore_init);
