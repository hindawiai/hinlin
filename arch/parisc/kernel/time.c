<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/parisc/kernel/समय.c
 *
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *  Modअगरications क्रम ARM (C) 1994, 1995, 1996,1997 Russell King
 *  Copyright (C) 1999 SuSE GmbH, (Philipp Rumpf, prumpf@tux.org)
 *
 * 1994-07-02  Alan Modra
 *             fixed set_rtc_mmss, fixed समय.year क्रम >= 2000, new स_गढ़ो
 * 1998-12-20  Updated NTP code according to technical memoअक्रमum Jan '96
 *             "A Kernel Model for Precision Timekeeping" by Dave Mills
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/profile.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ftrace.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/led.h>

#समावेश <linux/समयx.h>

अटल अचिन्हित दीर्घ घड़ीtick __ro_after_init;	/* समयr cycles per tick */

/*
 * We keep समय on PA-RISC Linux by using the Interval Timer which is
 * a pair of रेजिस्टरs; one is पढ़ो-only and one is ग_लिखो-only; both
 * accessed through CR16.  The पढ़ो-only रेजिस्टर is 32 or 64 bits wide,
 * and increments by 1 every CPU घड़ी tick.  The architecture only
 * guarantees us a rate between 0.5 and 2, but all implementations use a
 * rate of 1.  The ग_लिखो-only रेजिस्टर is 32-bits wide.  When the lowest
 * 32 bits of the पढ़ो-only रेजिस्टर compare equal to the ग_लिखो-only
 * रेजिस्टर, it उठाओs a maskable बाह्यal पूर्णांकerrupt.  Each processor has
 * an Interval Timer of its own and they are not synchronised.  
 *
 * We want to generate an पूर्णांकerrupt every 1/HZ seconds.  So we program
 * CR16 to पूर्णांकerrupt every @घड़ीtick cycles.  The it_value in cpu_data
 * is programmed with the पूर्णांकended समय of the next tick.  We can be
 * held off क्रम an arbitrarily दीर्घ period of समय by पूर्णांकerrupts being
 * disabled, so we may miss one or more ticks.
 */
irqवापस_t __irq_entry समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ now;
	अचिन्हित दीर्घ next_tick;
	अचिन्हित दीर्घ ticks_elapsed = 0;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा cpuinfo_parisc *cpuinfo = &per_cpu(cpu_data, cpu);

	/* gcc can optimize क्रम "read-only" हाल with a local घड़ीtick */
	अचिन्हित दीर्घ cpt = घड़ीtick;

	/* Initialize next_tick to the old expected tick समय. */
	next_tick = cpuinfo->it_value;

	/* Calculate how many ticks have elapsed. */
	now = mfctl(16);
	करो अणु
		++ticks_elapsed;
		next_tick += cpt;
	पूर्ण जबतक (next_tick - now > cpt);

	/* Store (in CR16 cycles) up to when we are accounting right now. */
	cpuinfo->it_value = next_tick;

	/* Go करो प्रणाली house keeping. */
	अगर (cpu != 0)
		ticks_elapsed = 0;
	legacy_समयr_tick(ticks_elapsed);

	/* Skip घड़ीticks on purpose अगर we know we would miss those.
	 * The new CR16 must be "later" than current CR16 otherwise
	 * iसमयr would not fire until CR16 wrapped - e.g 4 seconds
	 * later on a 1Ghz processor. We'll account क्रम the missed
	 * ticks on the next समयr पूर्णांकerrupt.
	 * We want IT to fire modulo घड़ीtick even अगर we miss/skip some.
	 * But those पूर्णांकerrupts करोn't in fact get delivered that regularly.
	 *
	 * "next_tick - now" will always give the dअगरference regardless
	 * अगर one or the other wrapped. If "now" is "bigger" we'll end up
	 * with a very large अचिन्हित number.
	 */
	now = mfctl(16);
	जबतक (next_tick - now > cpt)
		next_tick += cpt;

	/* Program the IT when to deliver the next पूर्णांकerrupt.
	 * Only bottom 32-bits of next_tick are writable in CR16!
	 * Timer पूर्णांकerrupt will be delivered at least a few hundred cycles
	 * after the IT fires, so अगर we are too बंद (<= 8000 cycles) to the
	 * next cycle, simply skip it.
	 */
	अगर (next_tick - now <= 8000)
		next_tick += cpt;
	mtctl(next_tick, 16);

	वापस IRQ_HANDLED;
पूर्ण


अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (regs->gr[0] & PSW_N)
		pc -= 4;

#अगर_घोषित CONFIG_SMP
	अगर (in_lock_functions(pc))
		pc = regs->gr[2];
#पूर्ण_अगर

	वापस pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);


/* घड़ी source code */

अटल u64 notrace पढ़ो_cr16(काष्ठा घड़ीsource *cs)
अणु
	वापस get_cycles();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_cr16 = अणु
	.name			= "cr16",
	.rating			= 300,
	.पढ़ो			= पढ़ो_cr16,
	.mask			= CLOCKSOURCE_MASK(BITS_PER_LONG),
	.flags			= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

व्योम __init start_cpu_iसमयr(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ next_tick = mfctl(16) + घड़ीtick;

	mtctl(next_tick, 16);		/* kick off Interval Timer (CR16) */

	per_cpu(cpu_data, cpu).it_value = next_tick;
पूर्ण

#अगर IS_ENABLED(CONFIG_RTC_DRV_GENERIC)
अटल पूर्णांक rtc_generic_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pdc_tod tod_data;

	स_रखो(पंचांग, 0, माप(*पंचांग));
	अगर (pdc_tod_पढ़ो(&tod_data) < 0)
		वापस -EOPNOTSUPP;

	/* we treat tod_sec as अचिन्हित, so this can work until year 2106 */
	rtc_समय64_to_पंचांग(tod_data.tod_sec, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_generic_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t secs = rtc_पंचांग_to_समय64(पंचांग);
	पूर्णांक ret;

	/* hppa has Y2K38 problem: pdc_tod_set() takes an u32 value! */
	ret = pdc_tod_set(secs, 0);
	अगर (ret != 0) अणु
		pr_warn("pdc_tod_set(%lld) returned error %d\n", secs, ret);
		अगर (ret == PDC_INVALID_ARG)
			वापस -EINVAL;
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_generic_ops = अणु
	.पढ़ो_समय = rtc_generic_get_समय,
	.set_समय = rtc_generic_set_समय,
पूर्ण;

अटल पूर्णांक __init rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "rtc-generic", -1,
					     &rtc_generic_ops,
					     माप(rtc_generic_ops));

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
device_initcall(rtc_init);
#पूर्ण_अगर

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	अटल काष्ठा pdc_tod tod_data;
	अगर (pdc_tod_पढ़ो(&tod_data) == 0) अणु
		ts->tv_sec = tod_data.tod_sec;
		ts->tv_nsec = tod_data.tod_usec * 1000;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Error reading tod clock\n");
	        ts->tv_sec = 0;
		ts->tv_nsec = 0;
	पूर्ण
पूर्ण


अटल u64 notrace पढ़ो_cr16_sched_घड़ी(व्योम)
अणु
	वापस get_cycles();
पूर्ण


/*
 * समयr पूर्णांकerrupt and sched_घड़ी() initialization
 */

व्योम __init समय_init(व्योम)
अणु
	अचिन्हित दीर्घ cr16_hz;

	घड़ीtick = (100 * PAGE0->mem_10msec) / HZ;
	start_cpu_iसमयr();	/* get CPU 0 started */

	cr16_hz = 100 * PAGE0->mem_10msec;  /* Hz */

	/* रेजिस्टर as sched_घड़ी source */
	sched_घड़ी_रेजिस्टर(पढ़ो_cr16_sched_घड़ी, BITS_PER_LONG, cr16_hz);
पूर्ण

अटल पूर्णांक __init init_cr16_घड़ीsource(व्योम)
अणु
	/*
	 * The cr16 पूर्णांकerval समयrs are not syncronized across CPUs on
	 * dअगरferent sockets, so mark them unstable and lower rating on
	 * multi-socket SMP प्रणालीs.
	 */
	अगर (num_online_cpus() > 1 && !running_on_qemu) अणु
		पूर्णांक cpu;
		अचिन्हित दीर्घ cpu0_loc;
		cpu0_loc = per_cpu(cpu_data, 0).cpu_loc;

		क्रम_each_online_cpu(cpu) अणु
			अगर (cpu == 0)
				जारी;
			अगर ((cpu0_loc != 0) &&
			    (cpu0_loc == per_cpu(cpu_data, cpu).cpu_loc))
				जारी;

			घड़ीsource_cr16.name = "cr16_unstable";
			घड़ीsource_cr16.flags = CLOCK_SOURCE_UNSTABLE;
			घड़ीsource_cr16.rating = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* XXX: We may want to mark sched_घड़ी stable here अगर cr16 घड़ीs are
	 *	in sync:
	 *	(घड़ीsource_cr16.flags == CLOCK_SOURCE_IS_CONTINUOUS) */

	/* रेजिस्टर at घड़ीsource framework */
	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_cr16,
		100 * PAGE0->mem_10msec);

	वापस 0;
पूर्ण

device_initcall(init_cr16_घड़ीsource);
