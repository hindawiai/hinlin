<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/समयr.h>
#समावेश <linux/acpi_pmपंचांगr.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/percpu.h>
#समावेश <linux/समयx.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/vgtod.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/geode.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/uv/uv.h>

अचिन्हित पूर्णांक __पढ़ो_mostly cpu_khz;	/* TSC घड़ीs / usec, not used here */
EXPORT_SYMBOL(cpu_khz);

अचिन्हित पूर्णांक __पढ़ो_mostly tsc_khz;
EXPORT_SYMBOL(tsc_khz);

#घोषणा KHZ	1000

/*
 * TSC can be unstable due to cpufreq or due to unsynced TSCs
 */
अटल पूर्णांक __पढ़ो_mostly tsc_unstable;
अटल अचिन्हित पूर्णांक __initdata tsc_early_khz;

अटल DEFINE_STATIC_KEY_FALSE(__use_tsc);

पूर्णांक tsc_घड़ीsource_reliable;

अटल u32 art_to_tsc_numerator;
अटल u32 art_to_tsc_denominator;
अटल u64 art_to_tsc_offset;
काष्ठा घड़ीsource *art_related_घड़ीsource;

काष्ठा cyc2ns अणु
	काष्ठा cyc2ns_data data[2];	/*  0 + 2*16 = 32 */
	seqcount_latch_t   seq;		/* 32 + 4    = 36 */

पूर्ण; /* fits one cacheline */

अटल DEFINE_PER_CPU_ALIGNED(काष्ठा cyc2ns, cyc2ns);

अटल पूर्णांक __init tsc_early_khz_setup(अक्षर *buf)
अणु
	वापस kstrtouपूर्णांक(buf, 0, &tsc_early_khz);
पूर्ण
early_param("tsc_early_khz", tsc_early_khz_setup);

__always_अंतरभूत व्योम cyc2ns_पढ़ो_begin(काष्ठा cyc2ns_data *data)
अणु
	पूर्णांक seq, idx;

	preempt_disable_notrace();

	करो अणु
		seq = this_cpu_पढ़ो(cyc2ns.seq.seqcount.sequence);
		idx = seq & 1;

		data->cyc2ns_offset = this_cpu_पढ़ो(cyc2ns.data[idx].cyc2ns_offset);
		data->cyc2ns_mul    = this_cpu_पढ़ो(cyc2ns.data[idx].cyc2ns_mul);
		data->cyc2ns_shअगरt  = this_cpu_पढ़ो(cyc2ns.data[idx].cyc2ns_shअगरt);

	पूर्ण जबतक (unlikely(seq != this_cpu_पढ़ो(cyc2ns.seq.seqcount.sequence)));
पूर्ण

__always_अंतरभूत व्योम cyc2ns_पढ़ो_end(व्योम)
अणु
	preempt_enable_notrace();
पूर्ण

/*
 * Accelerators क्रम sched_घड़ी()
 * convert from cycles(64bits) => nanoseconds (64bits)
 *  basic equation:
 *              ns = cycles / (freq / ns_per_sec)
 *              ns = cycles * (ns_per_sec / freq)
 *              ns = cycles * (10^9 / (cpu_khz * 10^3))
 *              ns = cycles * (10^6 / cpu_khz)
 *
 *      Then we use scaling math (suggested by george@mvista.com) to get:
 *              ns = cycles * (10^6 * SC / cpu_khz) / SC
 *              ns = cycles * cyc2ns_scale / SC
 *
 *      And since SC is a स्थिरant घातer of two, we can convert the भाग
 *  पूर्णांकo a shअगरt. The larger SC is, the more accurate the conversion, but
 *  cyc2ns_scale needs to be a 32-bit value so that 32-bit multiplication
 *  (64-bit result) can be used.
 *
 *  We can use khz भागisor instead of mhz to keep a better precision.
 *  (mathieu.desnoyers@polymtl.ca)
 *
 *                      -johnstul@us.ibm.com "math is hard, lets go shopping!"
 */

अटल __always_अंतरभूत अचिन्हित दीर्घ दीर्घ cycles_2_ns(अचिन्हित दीर्घ दीर्घ cyc)
अणु
	काष्ठा cyc2ns_data data;
	अचिन्हित दीर्घ दीर्घ ns;

	cyc2ns_पढ़ो_begin(&data);

	ns = data.cyc2ns_offset;
	ns += mul_u64_u32_shr(cyc, data.cyc2ns_mul, data.cyc2ns_shअगरt);

	cyc2ns_पढ़ो_end();

	वापस ns;
पूर्ण

अटल व्योम __set_cyc2ns_scale(अचिन्हित दीर्घ khz, पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ tsc_now)
अणु
	अचिन्हित दीर्घ दीर्घ ns_now;
	काष्ठा cyc2ns_data data;
	काष्ठा cyc2ns *c2n;

	ns_now = cycles_2_ns(tsc_now);

	/*
	 * Compute a new multiplier as per the above comment and ensure our
	 * समय function is continuous; see the comment near काष्ठा
	 * cyc2ns_data.
	 */
	घड़ीs_calc_mult_shअगरt(&data.cyc2ns_mul, &data.cyc2ns_shअगरt, khz,
			       NSEC_PER_MSEC, 0);

	/*
	 * cyc2ns_shअगरt is exported via arch_perf_update_userpage() where it is
	 * not expected to be greater than 31 due to the original published
	 * conversion algorithm shअगरting a 32-bit value (now specअगरies a 64-bit
	 * value) - refer perf_event_mmap_page करोcumentation in perf_event.h.
	 */
	अगर (data.cyc2ns_shअगरt == 32) अणु
		data.cyc2ns_shअगरt = 31;
		data.cyc2ns_mul >>= 1;
	पूर्ण

	data.cyc2ns_offset = ns_now -
		mul_u64_u32_shr(tsc_now, data.cyc2ns_mul, data.cyc2ns_shअगरt);

	c2n = per_cpu_ptr(&cyc2ns, cpu);

	raw_ग_लिखो_seqcount_latch(&c2n->seq);
	c2n->data[0] = data;
	raw_ग_लिखो_seqcount_latch(&c2n->seq);
	c2n->data[1] = data;
पूर्ण

अटल व्योम set_cyc2ns_scale(अचिन्हित दीर्घ khz, पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ tsc_now)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sched_घड़ी_idle_sleep_event();

	अगर (khz)
		__set_cyc2ns_scale(khz, cpu, tsc_now);

	sched_घड़ी_idle_wakeup_event();
	local_irq_restore(flags);
पूर्ण

/*
 * Initialize cyc2ns क्रम boot cpu
 */
अटल व्योम __init cyc2ns_init_boot_cpu(व्योम)
अणु
	काष्ठा cyc2ns *c2n = this_cpu_ptr(&cyc2ns);

	seqcount_latch_init(&c2n->seq);
	__set_cyc2ns_scale(tsc_khz, smp_processor_id(), rdtsc());
पूर्ण

/*
 * Secondary CPUs करो not run through tsc_init(), so set up
 * all the scale factors क्रम all CPUs, assuming the same
 * speed as the bootup CPU.
 */
अटल व्योम __init cyc2ns_init_secondary_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, this_cpu = smp_processor_id();
	काष्ठा cyc2ns *c2n = this_cpu_ptr(&cyc2ns);
	काष्ठा cyc2ns_data *data = c2n->data;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu != this_cpu) अणु
			seqcount_latch_init(&c2n->seq);
			c2n = per_cpu_ptr(&cyc2ns, cpu);
			c2n->data[0] = data[0];
			c2n->data[1] = data[1];
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Scheduler घड़ी - वापसs current समय in nanosec units.
 */
u64 native_sched_घड़ी(व्योम)
अणु
	अगर (अटल_branch_likely(&__use_tsc)) अणु
		u64 tsc_now = rdtsc();

		/* वापस the value in ns */
		वापस cycles_2_ns(tsc_now);
	पूर्ण

	/*
	 * Fall back to jअगरfies अगर there's no TSC available:
	 * ( But note that we still use it अगर the TSC is marked
	 *   unstable. We करो this because unlike Time Of Day,
	 *   the scheduler घड़ी tolerates small errors and it's
	 *   very important क्रम it to be as fast as the platक्रमm
	 *   can achieve it. )
	 */

	/* No locking but a rare wrong value is not a big deal: */
	वापस (jअगरfies_64 - INITIAL_JIFFIES) * (1000000000 / HZ);
पूर्ण

/*
 * Generate a sched_घड़ी अगर you alपढ़ोy have a TSC value.
 */
u64 native_sched_घड़ी_from_tsc(u64 tsc)
अणु
	वापस cycles_2_ns(tsc);
पूर्ण

/* We need to define a real function क्रम sched_घड़ी, to override the
   weak शेष version */
#अगर_घोषित CONFIG_PARAVIRT
अचिन्हित दीर्घ दीर्घ sched_घड़ी(व्योम)
अणु
	वापस paravirt_sched_घड़ी();
पूर्ण

bool using_native_sched_घड़ी(व्योम)
अणु
	वापस अटल_call_query(pv_sched_घड़ी) == native_sched_घड़ी;
पूर्ण
#अन्यथा
अचिन्हित दीर्घ दीर्घ
sched_घड़ी(व्योम) __attribute__((alias("native_sched_clock")));

bool using_native_sched_घड़ी(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर

पूर्णांक check_tsc_unstable(व्योम)
अणु
	वापस tsc_unstable;
पूर्ण
EXPORT_SYMBOL_GPL(check_tsc_unstable);

#अगर_घोषित CONFIG_X86_TSC
पूर्णांक __init notsc_setup(अक्षर *str)
अणु
	mark_tsc_unstable("boot parameter notsc");
	वापस 1;
पूर्ण
#अन्यथा
/*
 * disable flag क्रम tsc. Takes effect by clearing the TSC cpu flag
 * in cpu/common.c
 */
पूर्णांक __init notsc_setup(अक्षर *str)
अणु
	setup_clear_cpu_cap(X86_FEATURE_TSC);
	वापस 1;
पूर्ण
#पूर्ण_अगर

__setup("notsc", notsc_setup);

अटल पूर्णांक no_sched_irq_समय;
अटल पूर्णांक no_tsc_watchकरोg;

अटल पूर्णांक __init tsc_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "reliable"))
		tsc_घड़ीsource_reliable = 1;
	अगर (!म_भेदन(str, "noirqtime", 9))
		no_sched_irq_समय = 1;
	अगर (!म_भेद(str, "unstable"))
		mark_tsc_unstable("boot parameter");
	अगर (!म_भेद(str, "nowatchdog"))
		no_tsc_watchकरोg = 1;
	वापस 1;
पूर्ण

__setup("tsc=", tsc_setup);

#घोषणा MAX_RETRIES		5
#घोषणा TSC_DEFAULT_THRESHOLD	0x20000

/*
 * Read TSC and the reference counters. Take care of any disturbances
 */
अटल u64 tsc_पढ़ो_refs(u64 *p, पूर्णांक hpet)
अणु
	u64 t1, t2;
	u64 thresh = tsc_khz ? tsc_khz >> 5 : TSC_DEFAULT_THRESHOLD;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_RETRIES; i++) अणु
		t1 = get_cycles();
		अगर (hpet)
			*p = hpet_पढ़ोl(HPET_COUNTER) & 0xFFFFFFFF;
		अन्यथा
			*p = acpi_pm_पढ़ो_early();
		t2 = get_cycles();
		अगर ((t2 - t1) < thresh)
			वापस t2;
	पूर्ण
	वापस ULदीर्घ_उच्च;
पूर्ण

/*
 * Calculate the TSC frequency from HPET reference
 */
अटल अचिन्हित दीर्घ calc_hpet_ref(u64 deltatsc, u64 hpet1, u64 hpet2)
अणु
	u64 पंचांगp;

	अगर (hpet2 < hpet1)
		hpet2 += 0x100000000ULL;
	hpet2 -= hpet1;
	पंचांगp = ((u64)hpet2 * hpet_पढ़ोl(HPET_PERIOD));
	करो_भाग(पंचांगp, 1000000);
	deltatsc = भाग64_u64(deltatsc, पंचांगp);

	वापस (अचिन्हित दीर्घ) deltatsc;
पूर्ण

/*
 * Calculate the TSC frequency from PMTimer reference
 */
अटल अचिन्हित दीर्घ calc_pmसमयr_ref(u64 deltatsc, u64 pm1, u64 pm2)
अणु
	u64 पंचांगp;

	अगर (!pm1 && !pm2)
		वापस अच_दीर्घ_उच्च;

	अगर (pm2 < pm1)
		pm2 += (u64)ACPI_PM_OVRRUN;
	pm2 -= pm1;
	पंचांगp = pm2 * 1000000000LL;
	करो_भाग(पंचांगp, PMTMR_TICKS_PER_SEC);
	करो_भाग(deltatsc, पंचांगp);

	वापस (अचिन्हित दीर्घ) deltatsc;
पूर्ण

#घोषणा CAL_MS		10
#घोषणा CAL_LATCH	(PIT_TICK_RATE / (1000 / CAL_MS))
#घोषणा CAL_PIT_LOOPS	1000

#घोषणा CAL2_MS		50
#घोषणा CAL2_LATCH	(PIT_TICK_RATE / (1000 / CAL2_MS))
#घोषणा CAL2_PIT_LOOPS	5000


/*
 * Try to calibrate the TSC against the Programmable
 * Interrupt Timer and वापस the frequency of the TSC
 * in kHz.
 *
 * Return अच_दीर्घ_उच्च on failure to calibrate.
 */
अटल अचिन्हित दीर्घ pit_calibrate_tsc(u32 latch, अचिन्हित दीर्घ ms, पूर्णांक loopmin)
अणु
	u64 tsc, t1, t2, delta;
	अचिन्हित दीर्घ tscmin, tscmax;
	पूर्णांक pitcnt;

	अगर (!has_legacy_pic()) अणु
		/*
		 * Relies on tsc_early_delay_calibrate() to have given us semi
		 * usable udelay(), रुको क्रम the same 50ms we would have with
		 * the PIT loop below.
		 */
		udelay(10 * USEC_PER_MSEC);
		udelay(10 * USEC_PER_MSEC);
		udelay(10 * USEC_PER_MSEC);
		udelay(10 * USEC_PER_MSEC);
		udelay(10 * USEC_PER_MSEC);
		वापस अच_दीर्घ_उच्च;
	पूर्ण

	/* Set the Gate high, disable speaker */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Setup CTC channel 2* क्रम mode 0, (पूर्णांकerrupt on terminal
	 * count mode), binary count. Set the latch रेजिस्टर to 50ms
	 * (LSB then MSB) to begin countकरोwn.
	 */
	outb(0xb0, 0x43);
	outb(latch & 0xff, 0x42);
	outb(latch >> 8, 0x42);

	tsc = t1 = t2 = get_cycles();

	pitcnt = 0;
	tscmax = 0;
	tscmin = अच_दीर्घ_उच्च;
	जबतक ((inb(0x61) & 0x20) == 0) अणु
		t2 = get_cycles();
		delta = t2 - tsc;
		tsc = t2;
		अगर ((अचिन्हित दीर्घ) delta < tscmin)
			tscmin = (अचिन्हित पूर्णांक) delta;
		अगर ((अचिन्हित दीर्घ) delta > tscmax)
			tscmax = (अचिन्हित पूर्णांक) delta;
		pitcnt++;
	पूर्ण

	/*
	 * Sanity checks:
	 *
	 * If we were not able to पढ़ो the PIT more than loopmin
	 * बार, then we have been hit by a massive SMI
	 *
	 * If the maximum is 10 बार larger than the minimum,
	 * then we got hit by an SMI as well.
	 */
	अगर (pitcnt < loopmin || tscmax > 10 * tscmin)
		वापस अच_दीर्घ_उच्च;

	/* Calculate the PIT value */
	delta = t2 - t1;
	करो_भाग(delta, ms);
	वापस delta;
पूर्ण

/*
 * This पढ़ोs the current MSB of the PIT counter, and
 * checks अगर we are running on sufficiently fast and
 * non-भवized hardware.
 *
 * Our expectations are:
 *
 *  - the PIT is running at roughly 1.19MHz
 *
 *  - each IO is going to take about 1us on real hardware,
 *    but we allow it to be much faster (by a factor of 10) or
 *    _slightly_ slower (ie we allow up to a 2us पढ़ो+counter
 *    update - anything अन्यथा implies a unacceptably slow CPU
 *    or PIT क्रम the fast calibration to work.
 *
 *  - with 256 PIT ticks to पढ़ो the value, we have 214us to
 *    see the same MSB (and overhead like करोing a single TSC
 *    पढ़ो per MSB value etc).
 *
 *  - We're करोing 2 पढ़ोs per loop (LSB, MSB), and we expect
 *    them each to take about a microsecond on real hardware.
 *    So we expect a count value of around 100. But we'll be
 *    generous, and accept anything over 50.
 *
 *  - अगर the PIT is stuck, and we see *many* more पढ़ोs, we
 *    वापस early (and the next caller of pit_expect_msb()
 *    then consider it a failure when they करोn't see the
 *    next expected value).
 *
 * These expectations mean that we know that we have seen the
 * transition from one expected value to another with a fairly
 * high accuracy, and we didn't miss any events. We can thus
 * use the TSC value at the transitions to calculate a pretty
 * good value क्रम the TSC frequency.
 */
अटल अंतरभूत पूर्णांक pit_verअगरy_msb(अचिन्हित अक्षर val)
अणु
	/* Ignore LSB */
	inb(0x42);
	वापस inb(0x42) == val;
पूर्ण

अटल अंतरभूत पूर्णांक pit_expect_msb(अचिन्हित अक्षर val, u64 *tscp, अचिन्हित दीर्घ *deltap)
अणु
	पूर्णांक count;
	u64 tsc = 0, prev_tsc = 0;

	क्रम (count = 0; count < 50000; count++) अणु
		अगर (!pit_verअगरy_msb(val))
			अवरोध;
		prev_tsc = tsc;
		tsc = get_cycles();
	पूर्ण
	*deltap = get_cycles() - prev_tsc;
	*tscp = tsc;

	/*
	 * We require _some_ success, but the quality control
	 * will be based on the error terms on the TSC values.
	 */
	वापस count > 5;
पूर्ण

/*
 * How many MSB values करो we want to see? We aim क्रम
 * a maximum error rate of 500ppm (in practice the
 * real error is much smaller), but refuse to spend
 * more than 50ms on it.
 */
#घोषणा MAX_QUICK_PIT_MS 50
#घोषणा MAX_QUICK_PIT_ITERATIONS (MAX_QUICK_PIT_MS * PIT_TICK_RATE / 1000 / 256)

अटल अचिन्हित दीर्घ quick_pit_calibrate(व्योम)
अणु
	पूर्णांक i;
	u64 tsc, delta;
	अचिन्हित दीर्घ d1, d2;

	अगर (!has_legacy_pic())
		वापस 0;

	/* Set the Gate high, disable speaker */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Counter 2, mode 0 (one-shot), binary count
	 *
	 * NOTE! Mode 2 decrements by two (and then the
	 * output is flipped each समय, giving the same
	 * final output frequency as a decrement-by-one),
	 * so mode 0 is much better when looking at the
	 * inभागidual counts.
	 */
	outb(0xb0, 0x43);

	/* Start at 0xffff */
	outb(0xff, 0x42);
	outb(0xff, 0x42);

	/*
	 * The PIT starts counting at the next edge, so we
	 * need to delay क्रम a microsecond. The easiest way
	 * to करो that is to just पढ़ो back the 16-bit counter
	 * once from the PIT.
	 */
	pit_verअगरy_msb(0);

	अगर (pit_expect_msb(0xff, &tsc, &d1)) अणु
		क्रम (i = 1; i <= MAX_QUICK_PIT_ITERATIONS; i++) अणु
			अगर (!pit_expect_msb(0xff-i, &delta, &d2))
				अवरोध;

			delta -= tsc;

			/*
			 * Extrapolate the error and fail fast अगर the error will
			 * never be below 500 ppm.
			 */
			अगर (i == 1 &&
			    d1 + d2 >= (delta * MAX_QUICK_PIT_ITERATIONS) >> 11)
				वापस 0;

			/*
			 * Iterate until the error is less than 500 ppm
			 */
			अगर (d1+d2 >= delta >> 11)
				जारी;

			/*
			 * Check the PIT one more समय to verअगरy that
			 * all TSC पढ़ोs were stable wrt the PIT.
			 *
			 * This also guarantees serialization of the
			 * last cycle पढ़ो ('d2') in pit_expect_msb.
			 */
			अगर (!pit_verअगरy_msb(0xfe - i))
				अवरोध;
			जाओ success;
		पूर्ण
	पूर्ण
	pr_info("Fast TSC calibration failed\n");
	वापस 0;

success:
	/*
	 * Ok, अगर we get here, then we've seen the
	 * MSB of the PIT decrement 'i' बार, and the
	 * error has shrunk to less than 500 ppm.
	 *
	 * As a result, we can depend on there not being
	 * any odd delays anywhere, and the TSC पढ़ोs are
	 * reliable (within the error).
	 *
	 * kHz = ticks / समय-in-seconds / 1000;
	 * kHz = (t2 - t1) / (I * 256 / PIT_TICK_RATE) / 1000
	 * kHz = ((t2 - t1) * PIT_TICK_RATE) / (I * 256 * 1000)
	 */
	delta *= PIT_TICK_RATE;
	करो_भाग(delta, i*256*1000);
	pr_info("Fast TSC calibration using PIT\n");
	वापस delta;
पूर्ण

/**
 * native_calibrate_tsc
 * Determine TSC frequency via CPUID, अन्यथा वापस 0.
 */
अचिन्हित दीर्घ native_calibrate_tsc(व्योम)
अणु
	अचिन्हित पूर्णांक eax_denominator, ebx_numerator, ecx_hz, edx;
	अचिन्हित पूर्णांक crystal_khz;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस 0;

	अगर (boot_cpu_data.cpuid_level < 0x15)
		वापस 0;

	eax_denominator = ebx_numerator = ecx_hz = edx = 0;

	/* CPUID 15H TSC/Crystal ratio, plus optionally Crystal Hz */
	cpuid(0x15, &eax_denominator, &ebx_numerator, &ecx_hz, &edx);

	अगर (ebx_numerator == 0 || eax_denominator == 0)
		वापस 0;

	crystal_khz = ecx_hz / 1000;

	/*
	 * Denverton SoCs करोn't report crystal clock, and also don't support
	 * CPUID.0x16 क्रम the calculation below, so hardcode the 25MHz crystal
	 * घड़ी.
	 */
	अगर (crystal_khz == 0 &&
			boot_cpu_data.x86_model == INTEL_FAM6_ATOM_GOLDMONT_D)
		crystal_khz = 25000;

	/*
	 * TSC frequency reported directly by CPUID is a "hardware reported"
	 * frequency and is the most accurate one so far we have. This
	 * is considered a known frequency.
	 */
	अगर (crystal_khz != 0)
		setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	/*
	 * Some Intel SoCs like Skylake and Kabylake करोn't report the crystal
	 * घड़ी, but we can easily calculate it to a high degree of accuracy
	 * by considering the crystal ratio and the CPU speed.
	 */
	अगर (crystal_khz == 0 && boot_cpu_data.cpuid_level >= 0x16) अणु
		अचिन्हित पूर्णांक eax_base_mhz, ebx, ecx, edx;

		cpuid(0x16, &eax_base_mhz, &ebx, &ecx, &edx);
		crystal_khz = eax_base_mhz * 1000 *
			eax_denominator / ebx_numerator;
	पूर्ण

	अगर (crystal_khz == 0)
		वापस 0;

	/*
	 * For Atom SoCs TSC is the only reliable घड़ीsource.
	 * Mark TSC reliable so no watchकरोg on it.
	 */
	अगर (boot_cpu_data.x86_model == INTEL_FAM6_ATOM_GOLDMONT)
		setup_क्रमce_cpu_cap(X86_FEATURE_TSC_RELIABLE);

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	/*
	 * The local APIC appears to be fed by the core crystal घड़ी
	 * (which sounds entirely sensible). We can set the global
	 * lapic_समयr_period here to aव्योम having to calibrate the APIC
	 * समयr later.
	 */
	lapic_समयr_period = crystal_khz * 1000 / HZ;
#पूर्ण_अगर

	वापस crystal_khz * ebx_numerator / eax_denominator;
पूर्ण

अटल अचिन्हित दीर्घ cpu_khz_from_cpuid(व्योम)
अणु
	अचिन्हित पूर्णांक eax_base_mhz, ebx_max_mhz, ecx_bus_mhz, edx;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस 0;

	अगर (boot_cpu_data.cpuid_level < 0x16)
		वापस 0;

	eax_base_mhz = ebx_max_mhz = ecx_bus_mhz = edx = 0;

	cpuid(0x16, &eax_base_mhz, &ebx_max_mhz, &ecx_bus_mhz, &edx);

	वापस eax_base_mhz * 1000;
पूर्ण

/*
 * calibrate cpu using pit, hpet, and pसमयr methods. They are available
 * later in boot after acpi is initialized.
 */
अटल अचिन्हित दीर्घ pit_hpet_pसमयr_calibrate_cpu(व्योम)
अणु
	u64 tsc1, tsc2, delta, ref1, ref2;
	अचिन्हित दीर्घ tsc_pit_min = अच_दीर्घ_उच्च, tsc_ref_min = अच_दीर्घ_उच्च;
	अचिन्हित दीर्घ flags, latch, ms;
	पूर्णांक hpet = is_hpet_enabled(), i, loopmin;

	/*
	 * Run 5 calibration loops to get the lowest frequency value
	 * (the best estimate). We use two dअगरferent calibration modes
	 * here:
	 *
	 * 1) PIT loop. We set the PIT Channel 2 to oneshot mode and
	 * load a समयout of 50ms. We पढ़ो the समय right after we
	 * started the समयr and रुको until the PIT count करोwn reaches
	 * zero. In each रुको loop iteration we पढ़ो the TSC and check
	 * the delta to the previous पढ़ो. We keep track of the min
	 * and max values of that delta. The delta is mostly defined
	 * by the IO समय of the PIT access, so we can detect when
	 * any disturbance happened between the two पढ़ोs. If the
	 * maximum समय is signअगरicantly larger than the minimum समय,
	 * then we discard the result and have another try.
	 *
	 * 2) Reference counter. If available we use the HPET or the
	 * PMTIMER as a reference to check the sanity of that value.
	 * We use separate TSC पढ़ोouts and check inside of the
	 * reference पढ़ो क्रम any possible disturbance. We discard
	 * disturbed values here as well. We करो that around the PIT
	 * calibration delay loop as we have to रुको क्रम a certain
	 * amount of समय anyway.
	 */

	/* Preset PIT loop values */
	latch = CAL_LATCH;
	ms = CAL_MS;
	loopmin = CAL_PIT_LOOPS;

	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित दीर्घ tsc_pit_khz;

		/*
		 * Read the start value and the reference count of
		 * hpet/pmसमयr when available. Then करो the PIT
		 * calibration, which will take at least 50ms, and
		 * पढ़ो the end value.
		 */
		local_irq_save(flags);
		tsc1 = tsc_पढ़ो_refs(&ref1, hpet);
		tsc_pit_khz = pit_calibrate_tsc(latch, ms, loopmin);
		tsc2 = tsc_पढ़ो_refs(&ref2, hpet);
		local_irq_restore(flags);

		/* Pick the lowest PIT TSC calibration so far */
		tsc_pit_min = min(tsc_pit_min, tsc_pit_khz);

		/* hpet or pmसमयr available ? */
		अगर (ref1 == ref2)
			जारी;

		/* Check, whether the sampling was disturbed */
		अगर (tsc1 == ULदीर्घ_उच्च || tsc2 == ULदीर्घ_उच्च)
			जारी;

		tsc2 = (tsc2 - tsc1) * 1000000LL;
		अगर (hpet)
			tsc2 = calc_hpet_ref(tsc2, ref1, ref2);
		अन्यथा
			tsc2 = calc_pmसमयr_ref(tsc2, ref1, ref2);

		tsc_ref_min = min(tsc_ref_min, (अचिन्हित दीर्घ) tsc2);

		/* Check the reference deviation */
		delta = ((u64) tsc_pit_min) * 100;
		करो_भाग(delta, tsc_ref_min);

		/*
		 * If both calibration results are inside a 10% winकरोw
		 * then we can be sure, that the calibration
		 * succeeded. We अवरोध out of the loop right away. We
		 * use the reference value, as it is more precise.
		 */
		अगर (delta >= 90 && delta <= 110) अणु
			pr_info("PIT calibration matches %s. %d loops\n",
				hpet ? "HPET" : "PMTIMER", i + 1);
			वापस tsc_ref_min;
		पूर्ण

		/*
		 * Check whether PIT failed more than once. This
		 * happens in भवized environments. We need to
		 * give the भव PC a slightly दीर्घer समयframe क्रम
		 * the HPET/PMTIMER to make the result precise.
		 */
		अगर (i == 1 && tsc_pit_min == अच_दीर्घ_उच्च) अणु
			latch = CAL2_LATCH;
			ms = CAL2_MS;
			loopmin = CAL2_PIT_LOOPS;
		पूर्ण
	पूर्ण

	/*
	 * Now check the results.
	 */
	अगर (tsc_pit_min == अच_दीर्घ_उच्च) अणु
		/* PIT gave no useful value */
		pr_warn("Unable to calibrate against PIT\n");

		/* We करोn't have an alternative source, disable TSC */
		अगर (!hpet && !ref1 && !ref2) अणु
			pr_notice("No reference (HPET/PMTIMER) available\n");
			वापस 0;
		पूर्ण

		/* The alternative source failed as well, disable TSC */
		अगर (tsc_ref_min == अच_दीर्घ_उच्च) अणु
			pr_warn("HPET/PMTIMER calibration failed\n");
			वापस 0;
		पूर्ण

		/* Use the alternative source */
		pr_info("using %s reference calibration\n",
			hpet ? "HPET" : "PMTIMER");

		वापस tsc_ref_min;
	पूर्ण

	/* We करोn't have an alternative source, use the PIT calibration value */
	अगर (!hpet && !ref1 && !ref2) अणु
		pr_info("Using PIT calibration value\n");
		वापस tsc_pit_min;
	पूर्ण

	/* The alternative source failed, use the PIT calibration value */
	अगर (tsc_ref_min == अच_दीर्घ_उच्च) अणु
		pr_warn("HPET/PMTIMER calibration failed. Using PIT calibration.\n");
		वापस tsc_pit_min;
	पूर्ण

	/*
	 * The calibration values dअगरfer too much. In करोubt, we use
	 * the PIT value as we know that there are PMTIMERs around
	 * running at द्विगुन speed. At least we let the user know:
	 */
	pr_warn("PIT calibration deviates from %s: %lu %lu\n",
		hpet ? "HPET" : "PMTIMER", tsc_pit_min, tsc_ref_min);
	pr_info("Using PIT calibration value\n");
	वापस tsc_pit_min;
पूर्ण

/**
 * native_calibrate_cpu_early - can calibrate the cpu early in boot
 */
अचिन्हित दीर्घ native_calibrate_cpu_early(व्योम)
अणु
	अचिन्हित दीर्घ flags, fast_calibrate = cpu_khz_from_cpuid();

	अगर (!fast_calibrate)
		fast_calibrate = cpu_khz_from_msr();
	अगर (!fast_calibrate) अणु
		local_irq_save(flags);
		fast_calibrate = quick_pit_calibrate();
		local_irq_restore(flags);
	पूर्ण
	वापस fast_calibrate;
पूर्ण


/**
 * native_calibrate_cpu - calibrate the cpu
 */
अटल अचिन्हित दीर्घ native_calibrate_cpu(व्योम)
अणु
	अचिन्हित दीर्घ tsc_freq = native_calibrate_cpu_early();

	अगर (!tsc_freq)
		tsc_freq = pit_hpet_pसमयr_calibrate_cpu();

	वापस tsc_freq;
पूर्ण

व्योम recalibrate_cpu_khz(व्योम)
अणु
#अगर_अघोषित CONFIG_SMP
	अचिन्हित दीर्घ cpu_khz_old = cpu_khz;

	अगर (!boot_cpu_has(X86_FEATURE_TSC))
		वापस;

	cpu_khz = x86_platक्रमm.calibrate_cpu();
	tsc_khz = x86_platक्रमm.calibrate_tsc();
	अगर (tsc_khz == 0)
		tsc_khz = cpu_khz;
	अन्यथा अगर (असल(cpu_khz - tsc_khz) * 10 > tsc_khz)
		cpu_khz = tsc_khz;
	cpu_data(0).loops_per_jअगरfy = cpufreq_scale(cpu_data(0).loops_per_jअगरfy,
						    cpu_khz_old, cpu_khz);
#पूर्ण_अगर
पूर्ण

EXPORT_SYMBOL(recalibrate_cpu_khz);


अटल अचिन्हित दीर्घ दीर्घ cyc2ns_suspend;

व्योम tsc_save_sched_घड़ी_state(व्योम)
अणु
	अगर (!sched_घड़ी_stable())
		वापस;

	cyc2ns_suspend = sched_घड़ी();
पूर्ण

/*
 * Even on processors with invariant TSC, TSC माला_लो reset in some the
 * ACPI प्रणाली sleep states. And in some प्रणालीs BIOS seem to reinit TSC to
 * arbitrary value (still sync'd across cpu's) during resume from such sleep
 * states. To cope up with this, recompute the cyc2ns_offset क्रम each cpu so
 * that sched_घड़ी() जारीs from the poपूर्णांक where it was left off during
 * suspend.
 */
व्योम tsc_restore_sched_घड़ी_state(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	अगर (!sched_घड़ी_stable())
		वापस;

	local_irq_save(flags);

	/*
	 * We're coming out of suspend, there's no concurrency yet; don't
	 * bother being nice about the RCU stuff, just ग_लिखो to both
	 * data fields.
	 */

	this_cpu_ग_लिखो(cyc2ns.data[0].cyc2ns_offset, 0);
	this_cpu_ग_लिखो(cyc2ns.data[1].cyc2ns_offset, 0);

	offset = cyc2ns_suspend - sched_घड़ी();

	क्रम_each_possible_cpu(cpu) अणु
		per_cpu(cyc2ns.data[0].cyc2ns_offset, cpu) = offset;
		per_cpu(cyc2ns.data[1].cyc2ns_offset, cpu) = offset;
	पूर्ण

	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
/*
 * Frequency scaling support. Adjust the TSC based समयr when the CPU frequency
 * changes.
 *
 * NOTE: On SMP the situation is not fixable in general, so simply mark the TSC
 * as unstable and give up in those हालs.
 *
 * Should fix up last_tsc too. Currently समय_लोofday in the
 * first tick after the change will be slightly wrong.
 */

अटल अचिन्हित पूर्णांक  ref_freq;
अटल अचिन्हित दीर्घ loops_per_jअगरfy_ref;
अटल अचिन्हित दीर्घ tsc_khz_ref;

अटल पूर्णांक समय_cpufreq_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;

	अगर (num_online_cpus() > 1) अणु
		mark_tsc_unstable("cpufreq changes on SMP");
		वापस 0;
	पूर्ण

	अगर (!ref_freq) अणु
		ref_freq = freq->old;
		loops_per_jअगरfy_ref = boot_cpu_data.loops_per_jअगरfy;
		tsc_khz_ref = tsc_khz;
	पूर्ण

	अगर ((val == CPUFREQ_PRECHANGE  && freq->old < freq->new) ||
	    (val == CPUFREQ_POSTCHANGE && freq->old > freq->new)) अणु
		boot_cpu_data.loops_per_jअगरfy =
			cpufreq_scale(loops_per_jअगरfy_ref, ref_freq, freq->new);

		tsc_khz = cpufreq_scale(tsc_khz_ref, ref_freq, freq->new);
		अगर (!(freq->flags & CPUFREQ_CONST_LOOPS))
			mark_tsc_unstable("cpufreq changes");

		set_cyc2ns_scale(tsc_khz, freq->policy->cpu, rdtsc());
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block समय_cpufreq_notअगरier_block = अणु
	.notअगरier_call  = समय_cpufreq_notअगरier
पूर्ण;

अटल पूर्णांक __init cpufreq_रेजिस्टर_tsc_scaling(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_TSC))
		वापस 0;
	अगर (boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		वापस 0;
	cpufreq_रेजिस्टर_notअगरier(&समय_cpufreq_notअगरier_block,
				CPUFREQ_TRANSITION_NOTIFIER);
	वापस 0;
पूर्ण

core_initcall(cpufreq_रेजिस्टर_tsc_scaling);

#पूर्ण_अगर /* CONFIG_CPU_FREQ */

#घोषणा ART_CPUID_LEAF (0x15)
#घोषणा ART_MIN_DENOMINATOR (1)


/*
 * If ART is present detect the numerator:denominator to convert to TSC
 */
अटल व्योम __init detect_art(व्योम)
अणु
	अचिन्हित पूर्णांक unused[2];

	अगर (boot_cpu_data.cpuid_level < ART_CPUID_LEAF)
		वापस;

	/*
	 * Don't enable ART in a VM, non-stop TSC and TSC_ADJUST required,
	 * and the TSC counter resets must not occur asynchronously.
	 */
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR) ||
	    !boot_cpu_has(X86_FEATURE_NONSTOP_TSC) ||
	    !boot_cpu_has(X86_FEATURE_TSC_ADJUST) ||
	    tsc_async_resets)
		वापस;

	cpuid(ART_CPUID_LEAF, &art_to_tsc_denominator,
	      &art_to_tsc_numerator, unused, unused+1);

	अगर (art_to_tsc_denominator < ART_MIN_DENOMINATOR)
		वापस;

	rdmsrl(MSR_IA32_TSC_ADJUST, art_to_tsc_offset);

	/* Make this sticky over multiple CPU init calls */
	setup_क्रमce_cpu_cap(X86_FEATURE_ART);
पूर्ण


/* घड़ीsource code */

अटल व्योम tsc_resume(काष्ठा घड़ीsource *cs)
अणु
	tsc_verअगरy_tsc_adjust(true);
पूर्ण

/*
 * We used to compare the TSC to the cycle_last value in the घड़ीsource
 * काष्ठाure to aव्योम a nasty समय-warp. This can be observed in a
 * very small winकरोw right after one CPU updated cycle_last under
 * xसमय/vsyscall_gtod lock and the other CPU पढ़ोs a TSC value which
 * is smaller than the cycle_last reference value due to a TSC which
 * is slightly behind. This delta is nowhere अन्यथा observable, but in
 * that हाल it results in a क्रमward समय jump in the range of hours
 * due to the अचिन्हित delta calculation of the समय keeping core
 * code, which is necessary to support wrapping घड़ीsources like pm
 * समयr.
 *
 * This sanity check is now करोne in the core समयkeeping code.
 * checking the result of पढ़ो_tsc() - cycle_last क्रम being negative.
 * That works because CLOCKSOURCE_MASK(64) करोes not mask out any bit.
 */
अटल u64 पढ़ो_tsc(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)rdtsc_ordered();
पूर्ण

अटल व्योम tsc_cs_mark_unstable(काष्ठा घड़ीsource *cs)
अणु
	अगर (tsc_unstable)
		वापस;

	tsc_unstable = 1;
	अगर (using_native_sched_घड़ी())
		clear_sched_घड़ी_stable();
	disable_sched_घड़ी_irqसमय();
	pr_info("Marking TSC unstable due to clocksource watchdog\n");
पूर्ण

अटल व्योम tsc_cs_tick_stable(काष्ठा घड़ीsource *cs)
अणु
	अगर (tsc_unstable)
		वापस;

	अगर (using_native_sched_घड़ी())
		sched_घड़ी_प्रकारick_stable();
पूर्ण

अटल पूर्णांक tsc_cs_enable(काष्ठा घड़ीsource *cs)
अणु
	vघड़ीs_set_used(VDSO_CLOCKMODE_TSC);
	वापस 0;
पूर्ण

/*
 * .mask MUST be CLOCKSOURCE_MASK(64). See comment above पढ़ो_tsc()
 */
अटल काष्ठा घड़ीsource घड़ीsource_tsc_early = अणु
	.name			= "tsc-early",
	.rating			= 299,
	.पढ़ो			= पढ़ो_tsc,
	.mask			= CLOCKSOURCE_MASK(64),
	.flags			= CLOCK_SOURCE_IS_CONTINUOUS |
				  CLOCK_SOURCE_MUST_VERIFY,
	.vdso_घड़ी_mode	= VDSO_CLOCKMODE_TSC,
	.enable			= tsc_cs_enable,
	.resume			= tsc_resume,
	.mark_unstable		= tsc_cs_mark_unstable,
	.tick_stable		= tsc_cs_tick_stable,
	.list			= LIST_HEAD_INIT(घड़ीsource_tsc_early.list),
पूर्ण;

/*
 * Must mark VALID_FOR_HRES early such that when we unरेजिस्टर tsc_early
 * this one will immediately take over. We will only रेजिस्टर अगर TSC has
 * been found good.
 */
अटल काष्ठा घड़ीsource घड़ीsource_tsc = अणु
	.name			= "tsc",
	.rating			= 300,
	.पढ़ो			= पढ़ो_tsc,
	.mask			= CLOCKSOURCE_MASK(64),
	.flags			= CLOCK_SOURCE_IS_CONTINUOUS |
				  CLOCK_SOURCE_VALID_FOR_HRES |
				  CLOCK_SOURCE_MUST_VERIFY,
	.vdso_घड़ी_mode	= VDSO_CLOCKMODE_TSC,
	.enable			= tsc_cs_enable,
	.resume			= tsc_resume,
	.mark_unstable		= tsc_cs_mark_unstable,
	.tick_stable		= tsc_cs_tick_stable,
	.list			= LIST_HEAD_INIT(घड़ीsource_tsc.list),
पूर्ण;

व्योम mark_tsc_unstable(अक्षर *reason)
अणु
	अगर (tsc_unstable)
		वापस;

	tsc_unstable = 1;
	अगर (using_native_sched_घड़ी())
		clear_sched_घड़ी_stable();
	disable_sched_घड़ी_irqसमय();
	pr_info("Marking TSC unstable due to %s\n", reason);

	घड़ीsource_mark_unstable(&घड़ीsource_tsc_early);
	घड़ीsource_mark_unstable(&घड़ीsource_tsc);
पूर्ण

EXPORT_SYMBOL_GPL(mark_tsc_unstable);

अटल व्योम __init check_प्रणाली_tsc_reliable(व्योम)
अणु
#अगर defined(CONFIG_MGEODEGX1) || defined(CONFIG_MGEODE_LX) || defined(CONFIG_X86_GENERIC)
	अगर (is_geode_lx()) अणु
		/* RTSC counts during suspend */
#घोषणा RTSC_SUSP 0x100
		अचिन्हित दीर्घ res_low, res_high;

		rdmsr_safe(MSR_GEODE_BUSCONT_CONF0, &res_low, &res_high);
		/* Geode_LX - the OLPC CPU has a very reliable TSC */
		अगर (res_low & RTSC_SUSP)
			tsc_घड़ीsource_reliable = 1;
	पूर्ण
#पूर्ण_अगर
	अगर (boot_cpu_has(X86_FEATURE_TSC_RELIABLE))
		tsc_घड़ीsource_reliable = 1;
पूर्ण

/*
 * Make an educated guess अगर the TSC is trustworthy and synchronized
 * over all CPUs.
 */
पूर्णांक unsynchronized_tsc(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_TSC) || tsc_unstable)
		वापस 1;

#अगर_घोषित CONFIG_SMP
	अगर (apic_is_clustered_box())
		वापस 1;
#पूर्ण_अगर

	अगर (boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		वापस 0;

	अगर (tsc_घड़ीsource_reliable)
		वापस 0;
	/*
	 * Intel प्रणालीs are normally all synchronized.
	 * Exceptions must mark TSC as unstable:
	 */
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL) अणु
		/* assume multi socket प्रणालीs are not synchronized: */
		अगर (num_possible_cpus() > 1)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert ART to TSC given numerator/denominator found in detect_art()
 */
काष्ठा प्रणाली_counterval_t convert_art_to_tsc(u64 art)
अणु
	u64 पंचांगp, res, rem;

	rem = करो_भाग(art, art_to_tsc_denominator);

	res = art * art_to_tsc_numerator;
	पंचांगp = rem * art_to_tsc_numerator;

	करो_भाग(पंचांगp, art_to_tsc_denominator);
	res += पंचांगp + art_to_tsc_offset;

	वापस (काष्ठा प्रणाली_counterval_t) अणु.cs = art_related_घड़ीsource,
			.cycles = resपूर्ण;
पूर्ण
EXPORT_SYMBOL(convert_art_to_tsc);

/**
 * convert_art_ns_to_tsc() - Convert ART in nanoseconds to TSC.
 * @art_ns: ART (Always Running Timer) in unit of nanoseconds
 *
 * PTM requires all बारtamps to be in units of nanoseconds. When user
 * software requests a cross-बारtamp, this function converts प्रणाली बारtamp
 * to TSC.
 *
 * This is valid when CPU feature flag X86_FEATURE_TSC_KNOWN_FREQ is set
 * indicating the tsc_khz is derived from CPUID[15H]. Drivers should check
 * that this flag is set beक्रमe conversion to TSC is attempted.
 *
 * Return:
 * काष्ठा प्रणाली_counterval_t - प्रणाली counter value with the poपूर्णांकer to the
 *	corresponding घड़ीsource
 *	@cycles:	System counter value
 *	@cs:		Clocksource corresponding to प्रणाली counter value. Used
 *			by समयkeeping code to verअगरy comparability of two cycle
 *			values.
 */

काष्ठा प्रणाली_counterval_t convert_art_ns_to_tsc(u64 art_ns)
अणु
	u64 पंचांगp, res, rem;

	rem = करो_भाग(art_ns, USEC_PER_SEC);

	res = art_ns * tsc_khz;
	पंचांगp = rem * tsc_khz;

	करो_भाग(पंचांगp, USEC_PER_SEC);
	res += पंचांगp;

	वापस (काष्ठा प्रणाली_counterval_t) अणु .cs = art_related_घड़ीsource,
					      .cycles = resपूर्ण;
पूर्ण
EXPORT_SYMBOL(convert_art_ns_to_tsc);


अटल व्योम tsc_refine_calibration_work(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(tsc_irqwork, tsc_refine_calibration_work);
/**
 * tsc_refine_calibration_work - Further refine tsc freq calibration
 * @work - ignored.
 *
 * This functions uses delayed work over a period of a
 * second to further refine the TSC freq value. Since this is
 * समयr based, instead of loop based, we करोn't block the boot
 * process जबतक this दीर्घer calibration is करोne.
 *
 * If there are any calibration anomalies (too many SMIs, etc),
 * or the refined calibration is off by 1% of the fast early
 * calibration, we throw out the new calibration and use the
 * early calibration.
 */
अटल व्योम tsc_refine_calibration_work(काष्ठा work_काष्ठा *work)
अणु
	अटल u64 tsc_start = ULदीर्घ_उच्च, ref_start;
	अटल पूर्णांक hpet;
	u64 tsc_stop, ref_stop, delta;
	अचिन्हित दीर्घ freq;
	पूर्णांक cpu;

	/* Don't bother refining TSC on unstable प्रणालीs */
	अगर (tsc_unstable)
		जाओ unreg;

	/*
	 * Since the work is started early in boot, we may be
	 * delayed the first समय we expire. So set the workqueue
	 * again once we know समयrs are working.
	 */
	अगर (tsc_start == ULदीर्घ_उच्च) अणु
restart:
		/*
		 * Only set hpet once, to aव्योम mixing hardware
		 * अगर the hpet becomes enabled later.
		 */
		hpet = is_hpet_enabled();
		tsc_start = tsc_पढ़ो_refs(&ref_start, hpet);
		schedule_delayed_work(&tsc_irqwork, HZ);
		वापस;
	पूर्ण

	tsc_stop = tsc_पढ़ो_refs(&ref_stop, hpet);

	/* hpet or pmसमयr available ? */
	अगर (ref_start == ref_stop)
		जाओ out;

	/* Check, whether the sampling was disturbed */
	अगर (tsc_stop == ULदीर्घ_उच्च)
		जाओ restart;

	delta = tsc_stop - tsc_start;
	delta *= 1000000LL;
	अगर (hpet)
		freq = calc_hpet_ref(delta, ref_start, ref_stop);
	अन्यथा
		freq = calc_pmसमयr_ref(delta, ref_start, ref_stop);

	/* Make sure we're within 1% */
	अगर (असल(tsc_khz - freq) > tsc_khz/100)
		जाओ out;

	tsc_khz = freq;
	pr_info("Refined TSC clocksource calibration: %lu.%03lu MHz\n",
		(अचिन्हित दीर्घ)tsc_khz / 1000,
		(अचिन्हित दीर्घ)tsc_khz % 1000);

	/* Inक्रमm the TSC deadline घड़ीevent devices about the recalibration */
	lapic_update_tsc_freq();

	/* Update the sched_घड़ी() rate to match the घड़ीsource one */
	क्रम_each_possible_cpu(cpu)
		set_cyc2ns_scale(tsc_khz, cpu, tsc_stop);

out:
	अगर (tsc_unstable)
		जाओ unreg;

	अगर (boot_cpu_has(X86_FEATURE_ART))
		art_related_घड़ीsource = &घड़ीsource_tsc;
	घड़ीsource_रेजिस्टर_khz(&घड़ीsource_tsc, tsc_khz);
unreg:
	घड़ीsource_unरेजिस्टर(&घड़ीsource_tsc_early);
पूर्ण


अटल पूर्णांक __init init_tsc_घड़ीsource(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_TSC) || !tsc_khz)
		वापस 0;

	अगर (tsc_unstable)
		जाओ unreg;

	अगर (tsc_घड़ीsource_reliable || no_tsc_watchकरोg)
		घड़ीsource_tsc.flags &= ~CLOCK_SOURCE_MUST_VERIFY;

	अगर (boot_cpu_has(X86_FEATURE_NONSTOP_TSC_S3))
		घड़ीsource_tsc.flags |= CLOCK_SOURCE_SUSPEND_NONSTOP;

	/*
	 * When TSC frequency is known (retrieved via MSR or CPUID), we skip
	 * the refined calibration and directly रेजिस्टर it as a घड़ीsource.
	 */
	अगर (boot_cpu_has(X86_FEATURE_TSC_KNOWN_FREQ)) अणु
		अगर (boot_cpu_has(X86_FEATURE_ART))
			art_related_घड़ीsource = &घड़ीsource_tsc;
		घड़ीsource_रेजिस्टर_khz(&घड़ीsource_tsc, tsc_khz);
unreg:
		घड़ीsource_unरेजिस्टर(&घड़ीsource_tsc_early);
		वापस 0;
	पूर्ण

	schedule_delayed_work(&tsc_irqwork, 0);
	वापस 0;
पूर्ण
/*
 * We use device_initcall here, to ensure we run after the hpet
 * is fully initialized, which may occur at fs_initcall समय.
 */
device_initcall(init_tsc_घड़ीsource);

अटल bool __init determine_cpu_tsc_frequencies(bool early)
अणु
	/* Make sure that cpu and tsc are not alपढ़ोy calibrated */
	WARN_ON(cpu_khz || tsc_khz);

	अगर (early) अणु
		cpu_khz = x86_platक्रमm.calibrate_cpu();
		अगर (tsc_early_khz)
			tsc_khz = tsc_early_khz;
		अन्यथा
			tsc_khz = x86_platक्रमm.calibrate_tsc();
	पूर्ण अन्यथा अणु
		/* We should not be here with non-native cpu calibration */
		WARN_ON(x86_platक्रमm.calibrate_cpu != native_calibrate_cpu);
		cpu_khz = pit_hpet_pसमयr_calibrate_cpu();
	पूर्ण

	/*
	 * Trust non-zero tsc_khz as authoritative,
	 * and use it to sanity check cpu_khz,
	 * which will be off अगर प्रणाली समयr is off.
	 */
	अगर (tsc_khz == 0)
		tsc_khz = cpu_khz;
	अन्यथा अगर (असल(cpu_khz - tsc_khz) * 10 > tsc_khz)
		cpu_khz = tsc_khz;

	अगर (tsc_khz == 0)
		वापस false;

	pr_info("Detected %lu.%03lu MHz processor\n",
		(अचिन्हित दीर्घ)cpu_khz / KHZ,
		(अचिन्हित दीर्घ)cpu_khz % KHZ);

	अगर (cpu_khz != tsc_khz) अणु
		pr_info("Detected %lu.%03lu MHz TSC",
			(अचिन्हित दीर्घ)tsc_khz / KHZ,
			(अचिन्हित दीर्घ)tsc_khz % KHZ);
	पूर्ण
	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ __init get_loops_per_jअगरfy(व्योम)
अणु
	u64 lpj = (u64)tsc_khz * KHZ;

	करो_भाग(lpj, HZ);
	वापस lpj;
पूर्ण

अटल व्योम __init tsc_enable_sched_घड़ी(व्योम)
अणु
	/* Sanitize TSC ADJUST beक्रमe cyc2ns माला_लो initialized */
	tsc_store_and_check_tsc_adjust(true);
	cyc2ns_init_boot_cpu();
	अटल_branch_enable(&__use_tsc);
पूर्ण

व्योम __init tsc_early_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_TSC))
		वापस;
	/* Don't change UV TSC multi-chassis synchronization */
	अगर (is_early_uv_प्रणाली())
		वापस;
	अगर (!determine_cpu_tsc_frequencies(true))
		वापस;
	loops_per_jअगरfy = get_loops_per_jअगरfy();

	tsc_enable_sched_घड़ी();
पूर्ण

व्योम __init tsc_init(व्योम)
अणु
	/*
	 * native_calibrate_cpu_early can only calibrate using methods that are
	 * available early in boot.
	 */
	अगर (x86_platक्रमm.calibrate_cpu == native_calibrate_cpu_early)
		x86_platक्रमm.calibrate_cpu = native_calibrate_cpu;

	अगर (!boot_cpu_has(X86_FEATURE_TSC)) अणु
		setup_clear_cpu_cap(X86_FEATURE_TSC_DEADLINE_TIMER);
		वापस;
	पूर्ण

	अगर (!tsc_khz) अणु
		/* We failed to determine frequencies earlier, try again */
		अगर (!determine_cpu_tsc_frequencies(false)) अणु
			mark_tsc_unstable("could not calculate TSC khz");
			setup_clear_cpu_cap(X86_FEATURE_TSC_DEADLINE_TIMER);
			वापस;
		पूर्ण
		tsc_enable_sched_घड़ी();
	पूर्ण

	cyc2ns_init_secondary_cpus();

	अगर (!no_sched_irq_समय)
		enable_sched_घड़ी_irqसमय();

	lpj_fine = get_loops_per_jअगरfy();
	use_tsc_delay();

	check_प्रणाली_tsc_reliable();

	अगर (unsynchronized_tsc()) अणु
		mark_tsc_unstable("TSCs unsynchronized");
		वापस;
	पूर्ण

	अगर (tsc_घड़ीsource_reliable || no_tsc_watchकरोg)
		घड़ीsource_tsc_early.flags &= ~CLOCK_SOURCE_MUST_VERIFY;

	घड़ीsource_रेजिस्टर_khz(&घड़ीsource_tsc_early, tsc_khz);
	detect_art();
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * If we have a स्थिरant TSC and are using the TSC क्रम the delay loop,
 * we can skip घड़ी calibration अगर another cpu in the same socket has alपढ़ोy
 * been calibrated. This assumes that CONSTANT_TSC applies to all
 * cpus in the socket - this should be a safe assumption.
 */
अचिन्हित दीर्घ calibrate_delay_is_known(व्योम)
अणु
	पूर्णांक sibling, cpu = smp_processor_id();
	पूर्णांक स्थिरant_tsc = cpu_has(&cpu_data(cpu), X86_FEATURE_CONSTANT_TSC);
	स्थिर काष्ठा cpumask *mask = topology_core_cpumask(cpu);

	अगर (!स्थिरant_tsc || !mask)
		वापस 0;

	sibling = cpumask_any_but(mask, cpu);
	अगर (sibling < nr_cpu_ids)
		वापस cpu_data(sibling).loops_per_jअगरfy;
	वापस 0;
पूर्ण
#पूर्ण_अगर
