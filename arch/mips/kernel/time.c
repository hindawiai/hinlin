<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 * Copyright (c) 2003, 2004  Maciej W. Rozycki
 *
 * Common समय service routines क्रम MIPS machines.
 */
#समावेश <linux/bug.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/param.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/समय.स>

#अगर_घोषित CONFIG_CPU_FREQ

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, pcp_lpj_ref);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, pcp_lpj_ref_freq);
अटल अचिन्हित दीर्घ glb_lpj_ref;
अटल अचिन्हित दीर्घ glb_lpj_ref_freq;

अटल पूर्णांक cpufreq_callback(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	काष्ठा cpumask *cpus = freq->policy->cpus;
	अचिन्हित दीर्घ lpj;
	पूर्णांक cpu;

	/*
	 * Skip lpj numbers adjusपंचांगent अगर the CPU-freq transition is safe क्रम
	 * the loops delay. (Is this possible?)
	 */
	अगर (freq->flags & CPUFREQ_CONST_LOOPS)
		वापस NOTIFY_OK;

	/* Save the initial values of the lpjes क्रम future scaling. */
	अगर (!glb_lpj_ref) अणु
		glb_lpj_ref = boot_cpu_data.udelay_val;
		glb_lpj_ref_freq = freq->old;

		क्रम_each_online_cpu(cpu) अणु
			per_cpu(pcp_lpj_ref, cpu) =
				cpu_data[cpu].udelay_val;
			per_cpu(pcp_lpj_ref_freq, cpu) = freq->old;
		पूर्ण
	पूर्ण

	/*
	 * Adjust global lpj variable and per-CPU udelay_val number in
	 * accordance with the new CPU frequency.
	 */
	अगर ((val == CPUFREQ_PRECHANGE  && freq->old < freq->new) ||
	    (val == CPUFREQ_POSTCHANGE && freq->old > freq->new)) अणु
		loops_per_jअगरfy = cpufreq_scale(glb_lpj_ref,
						glb_lpj_ref_freq,
						freq->new);

		क्रम_each_cpu(cpu, cpus) अणु
			lpj = cpufreq_scale(per_cpu(pcp_lpj_ref, cpu),
					    per_cpu(pcp_lpj_ref_freq, cpu),
					    freq->new);
			cpu_data[cpu].udelay_val = (अचिन्हित पूर्णांक)lpj;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cpufreq_notअगरier = अणु
	.notअगरier_call  = cpufreq_callback,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_cpufreq_notअगरier(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_notअगरier(&cpufreq_notअगरier,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण
core_initcall(रेजिस्टर_cpufreq_notअगरier);

#पूर्ण_अगर /* CONFIG_CPU_FREQ */

/*
 * क्रमward reference
 */
DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

अटल पूर्णांक null_perf_irq(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक (*perf_irq)(व्योम) = null_perf_irq;

EXPORT_SYMBOL(perf_irq);

/*
 * समय_init() - it करोes the following things.
 *
 * 1) plat_समय_init() -
 *	a) (optional) set up RTC routines,
 *	b) (optional) calibrate and set the mips_hpt_frequency
 *	    (only needed अगर you पूर्णांकended to use cpu counter as समयr पूर्णांकerrupt
 *	     source)
 * 2) calculate a couple of cached variables क्रम later usage
 */

अचिन्हित पूर्णांक mips_hpt_frequency;
EXPORT_SYMBOL_GPL(mips_hpt_frequency);

अटल __init पूर्णांक cpu_has_mfc0_count_bug(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_R4000PC:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
		/*
		 * V3.0 is करोcumented as suffering from the mfc0 from count bug.
		 * Afaik this is the last version of the R4000.	 Later versions
		 * were marketed as R4400.
		 */
		वापस 1;

	हाल CPU_R4400PC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
		/*
		 * The published errata क्रम the R4400 up to 3.0 say the CPU
		 * has the mfc0 from count bug.
		 */
		अगर ((current_cpu_data.processor_id & 0xff) <= 0x30)
			वापस 1;

		/*
		 * we assume newer revisions are ok
		 */
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	plat_समय_init();

	/*
	 * The use of the R4k समयr as a घड़ी event takes precedence;
	 * अगर पढ़ोing the Count रेजिस्टर might पूर्णांकerfere with the समयr
	 * पूर्णांकerrupt, then we करोn't use the समयr as a घड़ी source.
	 * We may still use the समयr as a घड़ी source though अगर the
	 * समयr पूर्णांकerrupt isn't reliable; the interference doesn't
	 * matter then, because we करोn't use the पूर्णांकerrupt.
	 */
	अगर (mips_घड़ीevent_init() != 0 || !cpu_has_mfc0_count_bug())
		init_mips_घड़ीsource();
पूर्ण
