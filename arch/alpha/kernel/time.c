<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/समय.c
 *
 *  Copyright (C) 1991, 1992, 1995, 1999, 2000  Linus Torvalds
 *
 * This file contains the घड़ीsource समय handling.
 * 1997-09-10	Updated NTP code according to technical memoअक्रमum Jan '96
 *		"A Kernel Model for Precision Timekeeping" by Dave Mills
 * 1997-01-09    Adrian Sun
 *      use पूर्णांकerval समयr अगर CONFIG_RTC=y
 * 1997-10-29    John Bowman (bowman@math.ualberta.ca)
 *      fixed tick loss calculation in समयr_पूर्णांकerrupt
 *      (round प्रणाली घड़ी to nearest tick instead of truncating)
 *      fixed algorithm in समय_init क्रम getting समय from CMOS घड़ी
 * 1999-04-16	Thorsten Kranzkowski (dl8bcu@gmx.net)
 *	fixed algorithm in करो_समय_लोofday() क्रम calculating the precise समय
 *	from processor cycle counter (now taking lost_ticks पूर्णांकo account)
 * 2003-06-03	R. Scott Bailey <scott.bailey@eds.com>
 *	Tighten sanity in समय_init from 1% (10,000 PPM) to 250 PPM
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/bcd.h>
#समावेश <linux/profile.h>
#समावेश <linux/irq_work.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwrpb.h>

#समावेश <linux/mc146818rtc.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"

DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

अचिन्हित दीर्घ est_cycle_freq;

#अगर_घोषित CONFIG_IRQ_WORK

DEFINE_PER_CPU(u8, irq_work_pending);

#घोषणा set_irq_work_pending_flag()  __this_cpu_ग_लिखो(irq_work_pending, 1)
#घोषणा test_irq_work_pending()      __this_cpu_पढ़ो(irq_work_pending)
#घोषणा clear_irq_work_pending()     __this_cpu_ग_लिखो(irq_work_pending, 0)

व्योम arch_irq_work_उठाओ(व्योम)
अणु
	set_irq_work_pending_flag();
पूर्ण

#अन्यथा  /* CONFIG_IRQ_WORK */

#घोषणा test_irq_work_pending()      0
#घोषणा clear_irq_work_pending()

#पूर्ण_अगर /* CONFIG_IRQ_WORK */


अटल अंतरभूत __u32 rpcc(व्योम)
अणु
	वापस __builtin_alpha_rpcc();
पूर्ण



/*
 * The RTC as a घड़ी_event_device primitive.
 */

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, cpu_ce);

irqवापस_t
rtc_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce = &per_cpu(cpu_ce, cpu);

	/* Don't run the hook क्रम UNUSED or SHUTDOWN.  */
	अगर (likely(घड़ीevent_state_periodic(ce)))
		ce->event_handler(ce);

	अगर (test_irq_work_pending()) अणु
		clear_irq_work_pending();
		irq_work_run();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
rtc_ce_set_next_event(अचिन्हित दीर्घ evt, काष्ठा घड़ी_event_device *ce)
अणु
	/* This hook is क्रम oneshot mode, which we करोn't support.  */
	वापस -EINVAL;
पूर्ण

अटल व्योम __init
init_rtc_घड़ीevent(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce = &per_cpu(cpu_ce, cpu);

	*ce = (काष्ठा घड़ी_event_device)अणु
		.name = "rtc",
		.features = CLOCK_EVT_FEAT_PERIODIC,
		.rating = 100,
		.cpumask = cpumask_of(cpu),
		.set_next_event = rtc_ce_set_next_event,
	पूर्ण;

	घड़ीevents_config_and_रेजिस्टर(ce, CONFIG_HZ, 0, 0);
पूर्ण


/*
 * The QEMU घड़ी as a घड़ीsource primitive.
 */

अटल u64
qemu_cs_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस qemu_get_vmसमय();
पूर्ण

अटल काष्ठा घड़ीsource qemu_cs = अणु
	.name                   = "qemu",
	.rating                 = 400,
	.पढ़ो                   = qemu_cs_पढ़ो,
	.mask                   = CLOCKSOURCE_MASK(64),
	.flags                  = CLOCK_SOURCE_IS_CONTINUOUS,
	.max_idle_ns		= दीर्घ_उच्च
पूर्ण;


/*
 * The QEMU alarm as a घड़ी_event_device primitive.
 */

अटल पूर्णांक qemu_ce_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	/* The mode member of CE is updated क्रम us in generic code.
	   Just make sure that the event is disabled.  */
	qemu_set_alarm_असल(0);
	वापस 0;
पूर्ण

अटल पूर्णांक
qemu_ce_set_next_event(अचिन्हित दीर्घ evt, काष्ठा घड़ी_event_device *ce)
अणु
	qemu_set_alarm_rel(evt);
	वापस 0;
पूर्ण

अटल irqवापस_t
qemu_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce = &per_cpu(cpu_ce, cpu);

	ce->event_handler(ce);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init
init_qemu_घड़ीevent(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce = &per_cpu(cpu_ce, cpu);

	*ce = (काष्ठा घड़ी_event_device)अणु
		.name = "qemu",
		.features = CLOCK_EVT_FEAT_ONESHOT,
		.rating = 400,
		.cpumask = cpumask_of(cpu),
		.set_state_shutकरोwn = qemu_ce_shutकरोwn,
		.set_state_oneshot = qemu_ce_shutकरोwn,
		.tick_resume = qemu_ce_shutकरोwn,
		.set_next_event = qemu_ce_set_next_event,
	पूर्ण;

	घड़ीevents_config_and_रेजिस्टर(ce, NSEC_PER_SEC, 1000, दीर्घ_उच्च);
पूर्ण


व्योम __init
common_init_rtc(व्योम)
अणु
	अचिन्हित अक्षर x, sel = 0;

	/* Reset periodic पूर्णांकerrupt frequency.  */
#अगर CONFIG_HZ == 1024 || CONFIG_HZ == 1200
 	x = CMOS_READ(RTC_FREQ_SELECT) & 0x3f;
	/* Test includes known working values on various platक्रमms
	   where 0x26 is wrong; we refuse to change those. */
 	अगर (x != 0x26 && x != 0x25 && x != 0x19 && x != 0x06) अणु
		sel = RTC_REF_CLCK_32KHZ + 6;
	पूर्ण
#या_अगर CONFIG_HZ == 256 || CONFIG_HZ == 128 || CONFIG_HZ == 64 || CONFIG_HZ == 32
	sel = RTC_REF_CLCK_32KHZ + __builtin_ffs(32768 / CONFIG_HZ);
#अन्यथा
# error "Unknown HZ from arch/alpha/Kconfig"
#पूर्ण_अगर
	अगर (sel) अणु
		prपूर्णांकk(KERN_INFO "Setting RTC_FREQ to %d Hz (%x)\n",
		       CONFIG_HZ, sel);
		CMOS_WRITE(sel, RTC_FREQ_SELECT);
 	पूर्ण

	/* Turn on periodic पूर्णांकerrupts.  */
	x = CMOS_READ(RTC_CONTROL);
	अगर (!(x & RTC_PIE)) अणु
		prपूर्णांकk("Turning on RTC interrupts.\n");
		x |= RTC_PIE;
		x &= ~(RTC_AIE | RTC_UIE);
		CMOS_WRITE(x, RTC_CONTROL);
	पूर्ण
	(व्योम) CMOS_READ(RTC_INTR_FLAGS);

	outb(0x36, 0x43);	/* pit counter 0: प्रणाली समयr */
	outb(0x00, 0x40);
	outb(0x00, 0x40);

	outb(0xb6, 0x43);	/* pit counter 2: speaker */
	outb(0x31, 0x42);
	outb(0x13, 0x42);

	init_rtc_irq(शून्य);
पूर्ण


#अगर_अघोषित CONFIG_ALPHA_WTINT
/*
 * The RPCC as a घड़ीsource primitive.
 *
 * While we have मुक्त-running समयcounters running on all CPUs, and we make
 * a half-hearted attempt in init_rtc_rpcc_info to sync the समयcounter
 * with the wall घड़ी, that initialization isn't kept up-to-date across
 * dअगरferent समय counters in SMP mode.  Thereक्रमe we can only use this
 * method when there's only one CPU enabled.
 *
 * When using the WTINT PALcall, the RPCC may shअगरt to a lower frequency,
 * or stop altogether, जबतक रुकोing क्रम the पूर्णांकerrupt.  Thereक्रमe we cannot
 * use this method when WTINT is in use.
 */

अटल u64 पढ़ो_rpcc(काष्ठा घड़ीsource *cs)
अणु
	वापस rpcc();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_rpcc = अणु
	.name                   = "rpcc",
	.rating                 = 300,
	.पढ़ो                   = पढ़ो_rpcc,
	.mask                   = CLOCKSOURCE_MASK(32),
	.flags                  = CLOCK_SOURCE_IS_CONTINUOUS
पूर्ण;
#पूर्ण_अगर /* ALPHA_WTINT */


/* Validate a computed cycle counter result against the known bounds क्रम
   the given processor core.  There's too much brokenness in the way of
   timing hardware क्रम any one method to work everywhere.  :-(

   Return 0 अगर the result cannot be trusted, otherwise वापस the argument.  */

अटल अचिन्हित दीर्घ __init
validate_cc_value(अचिन्हित दीर्घ cc)
अणु
	अटल काष्ठा bounds अणु
		अचिन्हित पूर्णांक min, max;
	पूर्ण cpu_hz[] __initdata = अणु
		[EV3_CPU]    = अणु   50000000,  200000000 पूर्ण,	/* guess */
		[EV4_CPU]    = अणु  100000000,  300000000 पूर्ण,
		[LCA4_CPU]   = अणु  100000000,  300000000 पूर्ण,	/* guess */
		[EV45_CPU]   = अणु  200000000,  300000000 पूर्ण,
		[EV5_CPU]    = अणु  250000000,  433000000 पूर्ण,
		[EV56_CPU]   = अणु  333000000,  667000000 पूर्ण,
		[PCA56_CPU]  = अणु  400000000,  600000000 पूर्ण,	/* guess */
		[PCA57_CPU]  = अणु  500000000,  600000000 पूर्ण,	/* guess */
		[EV6_CPU]    = अणु  466000000,  600000000 पूर्ण,
		[EV67_CPU]   = अणु  600000000,  750000000 पूर्ण,
		[EV68AL_CPU] = अणु  750000000,  940000000 पूर्ण,
		[EV68CB_CPU] = अणु 1000000000, 1333333333 पूर्ण,
		/* None of the following are shipping as of 2001-11-01.  */
		[EV68CX_CPU] = अणु 1000000000, 1700000000 पूर्ण,	/* guess */
		[EV69_CPU]   = अणु 1000000000, 1700000000 पूर्ण,	/* guess */
		[EV7_CPU]    = अणु  800000000, 1400000000 पूर्ण,	/* guess */
		[EV79_CPU]   = अणु 1000000000, 2000000000 पूर्ण,	/* guess */
	पूर्ण;

	/* Allow क्रम some drअगरt in the crystal.  10MHz is more than enough.  */
	स्थिर अचिन्हित पूर्णांक deviation = 10000000;

	काष्ठा percpu_काष्ठा *cpu;
	अचिन्हित पूर्णांक index;

	cpu = (काष्ठा percpu_काष्ठा *)((अक्षर*)hwrpb + hwrpb->processor_offset);
	index = cpu->type & 0xffffffff;

	/* If index out of bounds, no way to validate.  */
	अगर (index >= ARRAY_SIZE(cpu_hz))
		वापस cc;

	/* If index contains no data, no way to validate.  */
	अगर (cpu_hz[index].max == 0)
		वापस cc;

	अगर (cc < cpu_hz[index].min - deviation
	    || cc > cpu_hz[index].max + deviation)
		वापस 0;

	वापस cc;
पूर्ण


/*
 * Calibrate CPU घड़ी using legacy 8254 समयr/counter. Stolen from
 * arch/i386/समय.c.
 */

#घोषणा CALIBRATE_LATCH	0xffff
#घोषणा TIMEOUT_COUNT	0x100000

अटल अचिन्हित दीर्घ __init
calibrate_cc_with_pit(व्योम)
अणु
	पूर्णांक cc, count = 0;

	/* Set the Gate high, disable speaker */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Now let's take care of CTC channel 2
	 *
	 * Set the Gate high, program CTC channel 2 क्रम mode 0,
	 * (पूर्णांकerrupt on terminal count mode), binary count,
	 * load 5 * LATCH count, (LSB and MSB) to begin countकरोwn.
	 */
	outb(0xb0, 0x43);		/* binary, mode 0, LSB/MSB, Ch 2 */
	outb(CALIBRATE_LATCH & 0xff, 0x42);	/* LSB of count */
	outb(CALIBRATE_LATCH >> 8, 0x42);	/* MSB of count */

	cc = rpcc();
	करो अणु
		count++;
	पूर्ण जबतक ((inb(0x61) & 0x20) == 0 && count < TIMEOUT_COUNT);
	cc = rpcc() - cc;

	/* Error: ECTCNEVERSET or ECPUTOOFAST.  */
	अगर (count <= 1 || count == TIMEOUT_COUNT)
		वापस 0;

	वापस ((दीर्घ)cc * PIT_TICK_RATE) / (CALIBRATE_LATCH + 1);
पूर्ण

/* The Linux पूर्णांकerpretation of the CMOS घड़ी रेजिस्टर contents:
   When the Update-In-Progress (UIP) flag goes from 1 to 0, the
   RTC रेजिस्टरs show the second which has precisely just started.
   Let's hope other operating प्रणालीs पूर्णांकerpret the RTC the same way.  */

अटल अचिन्हित दीर्घ __init
rpcc_after_update_in_progress(व्योम)
अणु
	करो अणु पूर्ण जबतक (!(CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP));
	करो अणु पूर्ण जबतक (CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP);

	वापस rpcc();
पूर्ण

व्योम __init
समय_init(व्योम)
अणु
	अचिन्हित पूर्णांक cc1, cc2;
	अचिन्हित दीर्घ cycle_freq, tolerance;
	दीर्घ dअगरf;

	अगर (alpha_using_qemu) अणु
		घड़ीsource_रेजिस्टर_hz(&qemu_cs, NSEC_PER_SEC);
		init_qemu_घड़ीevent();
		init_rtc_irq(qemu_समयr_पूर्णांकerrupt);
		वापस;
	पूर्ण

	/* Calibrate CPU घड़ी -- attempt #1.  */
	अगर (!est_cycle_freq)
		est_cycle_freq = validate_cc_value(calibrate_cc_with_pit());

	cc1 = rpcc();

	/* Calibrate CPU घड़ी -- attempt #2.  */
	अगर (!est_cycle_freq) अणु
		cc1 = rpcc_after_update_in_progress();
		cc2 = rpcc_after_update_in_progress();
		est_cycle_freq = validate_cc_value(cc2 - cc1);
		cc1 = cc2;
	पूर्ण

	cycle_freq = hwrpb->cycle_freq;
	अगर (est_cycle_freq) अणु
		/* If the given value is within 250 PPM of what we calculated,
		   accept it.  Otherwise, use what we found.  */
		tolerance = cycle_freq / 4000;
		dअगरf = cycle_freq - est_cycle_freq;
		अगर (dअगरf < 0)
			dअगरf = -dअगरf;
		अगर ((अचिन्हित दीर्घ)dअगरf > tolerance) अणु
			cycle_freq = est_cycle_freq;
			prपूर्णांकk("HWRPB cycle frequency bogus.  "
			       "Estimated %lu Hz\n", cycle_freq);
		पूर्ण अन्यथा अणु
			est_cycle_freq = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (! validate_cc_value (cycle_freq)) अणु
		prपूर्णांकk("HWRPB cycle frequency bogus, "
		       "and unable to estimate a proper value!\n");
	पूर्ण

	/* See above क्रम restrictions on using घड़ीsource_rpcc.  */
#अगर_अघोषित CONFIG_ALPHA_WTINT
	अगर (hwrpb->nr_processors == 1)
		घड़ीsource_रेजिस्टर_hz(&घड़ीsource_rpcc, cycle_freq);
#पूर्ण_अगर

	/* Startup the समयr source. */
	alpha_mv.init_rtc();
	init_rtc_घड़ीevent();
पूर्ण

/* Initialize the घड़ी_event_device क्रम secondary cpus.  */
#अगर_घोषित CONFIG_SMP
व्योम __init
init_घड़ीevent(व्योम)
अणु
	अगर (alpha_using_qemu)
		init_qemu_घड़ीevent();
	अन्यथा
		init_rtc_घड़ीevent();
पूर्ण
#पूर्ण_अगर
