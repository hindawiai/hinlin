<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Precise Delay Loops क्रम i386
 *
 *	Copyright (C) 1993 Linus Torvalds
 *	Copyright (C) 1997 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *	Copyright (C) 2008 Jiri Hladky <hladky _करोt_ jiri _at_ gmail _करोt_ com>
 *
 *	The __delay function must _NOT_ be अंतरभूतd as its execution समय
 *	depends wildly on alignment on many x86 processors. The additional
 *	jump magic is needed to get the timing stable on all the CPU's
 *	we have to worry about.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयx.h>
#समावेश <linux/preempt.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/mरुको.h>

#अगर_घोषित CONFIG_SMP
# include <यंत्र/smp.h>
#पूर्ण_अगर

अटल व्योम delay_loop(u64 __loops);

/*
 * Calibration and selection of the delay mechanism happens only once
 * during boot.
 */
अटल व्योम (*delay_fn)(u64) __ro_after_init = delay_loop;
अटल व्योम (*delay_halt_fn)(u64 start, u64 cycles) __ro_after_init;

/* simple loop based delay: */
अटल व्योम delay_loop(u64 __loops)
अणु
	अचिन्हित दीर्घ loops = (अचिन्हित दीर्घ)__loops;

	यंत्र अस्थिर(
		"	test %0,%0	\n"
		"	jz 3f		\n"
		"	jmp 1f		\n"

		".align 16		\n"
		"1:	jmp 2f		\n"

		".align 16		\n"
		"2:	dec %0		\n"
		"	jnz 2b		\n"
		"3:	dec %0		\n"

		: /* we करोn't need output */
		:"a" (loops)
	);
पूर्ण

/* TSC based delay: */
अटल व्योम delay_tsc(u64 cycles)
अणु
	u64 bघड़ी, now;
	पूर्णांक cpu;

	preempt_disable();
	cpu = smp_processor_id();
	bघड़ी = rdtsc_ordered();
	क्रम (;;) अणु
		now = rdtsc_ordered();
		अगर ((now - bघड़ी) >= cycles)
			अवरोध;

		/* Allow RT tasks to run */
		preempt_enable();
		rep_nop();
		preempt_disable();

		/*
		 * It is possible that we moved to another CPU, and
		 * since TSC's are per-cpu we need to calculate
		 * that. The delay must guarantee that we रुको "at
		 * least" the amount of समय. Being moved to another
		 * CPU could make the रुको दीर्घer but we just need to
		 * make sure we रुकोed दीर्घ enough. Rebalance the
		 * counter क्रम this CPU.
		 */
		अगर (unlikely(cpu != smp_processor_id())) अणु
			cycles -= (now - bघड़ी);
			cpu = smp_processor_id();
			bघड़ी = rdtsc_ordered();
		पूर्ण
	पूर्ण
	preempt_enable();
पूर्ण

/*
 * On Intel the TPAUSE inकाष्ठाion रुकोs until any of:
 * 1) the TSC counter exceeds the value provided in EDX:EAX
 * 2) global समयout in IA32_UMWAIT_CONTROL is exceeded
 * 3) an बाह्यal पूर्णांकerrupt occurs
 */
अटल व्योम delay_halt_tछोड़ो(u64 start, u64 cycles)
अणु
	u64 until = start + cycles;
	u32 eax, edx;

	eax = lower_32_bits(until);
	edx = upper_32_bits(until);

	/*
	 * Hard code the deeper (C0.2) sleep state because निकास latency is
	 * small compared to the "microseconds" that usleep() will delay.
	 */
	__tछोड़ो(TPAUSE_C02_STATE, edx, eax);
पूर्ण

/*
 * On some AMD platक्रमms, MWAITX has a configurable 32-bit समयr, that
 * counts with TSC frequency. The input value is the number of TSC cycles
 * to रुको. MWAITX will also निकास when the समयr expires.
 */
अटल व्योम delay_halt_mरुकोx(u64 unused, u64 cycles)
अणु
	u64 delay;

	delay = min_t(u64, MWAITX_MAX_WAIT_CYCLES, cycles);
	/*
	 * Use cpu_tss_rw as a cacheline-aligned, selकरोmly accessed per-cpu
	 * variable as the monitor target.
	 */
	 __monitorx(raw_cpu_ptr(&cpu_tss_rw), 0, 0);

	/*
	 * AMD, like Intel, supports the EAX hपूर्णांक and EAX=0xf means, करो not
	 * enter any deep C-state and we use it here in delay() to minimize
	 * wakeup latency.
	 */
	__mरुकोx(MWAITX_DISABLE_CSTATES, delay, MWAITX_ECX_TIMER_ENABLE);
पूर्ण

/*
 * Call a venकरोr specअगरic function to delay क्रम a given amount of समय. Because
 * these functions may वापस earlier than requested, check क्रम actual elapsed
 * समय and call again until करोne.
 */
अटल व्योम delay_halt(u64 __cycles)
अणु
	u64 start, end, cycles = __cycles;

	/*
	 * Timer value of 0 causes MWAITX to रुको indefinitely, unless there
	 * is a store on the memory monitored by MONITORX.
	 */
	अगर (!cycles)
		वापस;

	start = rdtsc_ordered();

	क्रम (;;) अणु
		delay_halt_fn(start, cycles);
		end = rdtsc_ordered();

		अगर (cycles <= end - start)
			अवरोध;

		cycles -= end - start;
		start = end;
	पूर्ण
पूर्ण

व्योम __init use_tsc_delay(व्योम)
अणु
	अगर (delay_fn == delay_loop)
		delay_fn = delay_tsc;
पूर्ण

व्योम __init use_tछोड़ो_delay(व्योम)
अणु
	delay_halt_fn = delay_halt_tछोड़ो;
	delay_fn = delay_halt;
पूर्ण

व्योम use_mरुकोx_delay(व्योम)
अणु
	delay_halt_fn = delay_halt_mरुकोx;
	delay_fn = delay_halt;
पूर्ण

पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val)
अणु
	अगर (delay_fn == delay_tsc) अणु
		*समयr_val = rdtsc();
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	delay_fn(loops);
पूर्ण
EXPORT_SYMBOL(__delay);

noअंतरभूत व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	अचिन्हित दीर्घ lpj = this_cpu_पढ़ो(cpu_info.loops_per_jअगरfy) ? : loops_per_jअगरfy;
	पूर्णांक d0;

	xloops *= 4;
	यंत्र("mull %%edx"
		:"=d" (xloops), "=&a" (d0)
		:"1" (xloops), "0" (lpj * (HZ / 4)));

	__delay(++xloops);
पूर्ण
EXPORT_SYMBOL(__स्थिर_udelay);

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__स्थिर_udelay(usecs * 0x000010c7); /* 2**32 / 1000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ nsecs)
अणु
	__स्थिर_udelay(nsecs * 0x00005); /* 2**32 / 1000000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__ndelay);
