<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Pentium 4/Xeon CPU on demand घड़ी modulation/speed scaling
 *	(C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 *	(C) 2002 Zwane Mwaikambo <zwane@commfireservices.com>
 *	(C) 2002 Arjan van de Ven <arjanv@redhat.com>
 *	(C) 2002 Tora T. Engstad
 *	All Rights Reserved
 *
 *      The author(s) of this software shall not be held liable क्रम damages
 *      of any nature resulting due to the use of this software. This
 *      software is provided AS-IS with no warranties.
 *
 *	Date		Errata			Description
 *	20020525	N44, O17	12.5% or 25% DC causes lockup
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/समयx.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/cpu_device_id.h>

#समावेश "speedstep-lib.h"

/*
 * Duty Cycle (3bits), note DC_DISABLE is not specअगरied in
 * पूर्णांकel करोcs i just use it to mean disable
 */
क्रमागत अणु
	DC_RESV, DC_DFLT, DC_25PT, DC_38PT, DC_50PT,
	DC_64PT, DC_75PT, DC_88PT, DC_DISABLE
पूर्ण;

#घोषणा DC_ENTRIES	8


अटल पूर्णांक has_N44_O17_errata[NR_CPUS];
अटल अचिन्हित पूर्णांक stock_freq;
अटल काष्ठा cpufreq_driver p4घड़ीmod_driver;
अटल अचिन्हित पूर्णांक cpufreq_p4_get(अचिन्हित पूर्णांक cpu);

अटल पूर्णांक cpufreq_p4_setdc(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक newstate)
अणु
	u32 l, h;

	अगर ((newstate > DC_DISABLE) || (newstate == DC_RESV))
		वापस -EINVAL;

	rdmsr_on_cpu(cpu, MSR_IA32_THERM_STATUS, &l, &h);

	अगर (l & 0x01)
		pr_debug("CPU#%d currently thermal throttled\n", cpu);

	अगर (has_N44_O17_errata[cpu] &&
	    (newstate == DC_25PT || newstate == DC_DFLT))
		newstate = DC_38PT;

	rdmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, &l, &h);
	अगर (newstate == DC_DISABLE) अणु
		pr_debug("CPU#%d disabling modulation\n", cpu);
		wrmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, l & ~(1<<4), h);
	पूर्ण अन्यथा अणु
		pr_debug("CPU#%d setting duty cycle to %d%%\n",
			cpu, ((125 * newstate) / 10));
		/* bits 63 - 5	: reserved
		 * bit  4	: enable/disable
		 * bits 3-1	: duty cycle
		 * bit  0	: reserved
		 */
		l = (l & ~14);
		l = l | (1<<4) | ((newstate & 0x7)<<1);
		wrmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, l, h);
	पूर्ण

	वापस 0;
पूर्ण


अटल काष्ठा cpufreq_frequency_table p4घड़ीmod_table[] = अणु
	अणु0, DC_RESV, CPUFREQ_ENTRY_INVALIDपूर्ण,
	अणु0, DC_DFLT, 0पूर्ण,
	अणु0, DC_25PT, 0पूर्ण,
	अणु0, DC_38PT, 0पूर्ण,
	अणु0, DC_50PT, 0पूर्ण,
	अणु0, DC_64PT, 0पूर्ण,
	अणु0, DC_75PT, 0पूर्ण,
	अणु0, DC_88PT, 0पूर्ण,
	अणु0, DC_DISABLE, 0पूर्ण,
	अणु0, DC_RESV, CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;


अटल पूर्णांक cpufreq_p4_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक i;

	/* run on each logical CPU,
	 * see section 13.15.3 of IA32 Intel Architecture Software
	 * Developer's Manual, Volume 3
	 */
	क्रम_each_cpu(i, policy->cpus)
		cpufreq_p4_setdc(i, p4घड़ीmod_table[index].driver_data);

	वापस 0;
पूर्ण


अटल अचिन्हित पूर्णांक cpufreq_p4_get_frequency(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86 == 0x06) अणु
		अगर (cpu_has(c, X86_FEATURE_EST))
			pr_warn_once("Warning: EST-capable CPU detected. The acpi-cpufreq module offers voltage scaling in addition to frequency scaling. You should use that instead of p4-clockmod, if possible.\n");
		चयन (c->x86_model) अणु
		हाल 0x0E: /* Core */
		हाल 0x0F: /* Core Duo */
		हाल 0x16: /* Celeron Core */
		हाल 0x1C: /* Atom */
			p4घड़ीmod_driver.flags |= CPUFREQ_CONST_LOOPS;
			वापस speedstep_get_frequency(SPEEDSTEP_CPU_PCORE);
		हाल 0x0D: /* Pentium M (Dothan) */
			p4घड़ीmod_driver.flags |= CPUFREQ_CONST_LOOPS;
			fallthrough;
		हाल 0x09: /* Pentium M (Banias) */
			वापस speedstep_get_frequency(SPEEDSTEP_CPU_PM);
		पूर्ण
	पूर्ण

	अगर (c->x86 != 0xF)
		वापस 0;

	/* on P-4s, the TSC runs with स्थिरant frequency independent whether
	 * throttling is active or not. */
	p4घड़ीmod_driver.flags |= CPUFREQ_CONST_LOOPS;

	अगर (speedstep_detect_processor() == SPEEDSTEP_CPU_P4M) अणु
		pr_warn("Warning: Pentium 4-M detected. The speedstep-ich or acpi cpufreq modules offer voltage scaling in addition of frequency scaling. You should use either one instead of p4-clockmod, if possible.\n");
		वापस speedstep_get_frequency(SPEEDSTEP_CPU_P4M);
	पूर्ण

	वापस speedstep_get_frequency(SPEEDSTEP_CPU_P4D);
पूर्ण



अटल पूर्णांक cpufreq_p4_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(policy->cpu);
	पूर्णांक cpuid = 0;
	अचिन्हित पूर्णांक i;

#अगर_घोषित CONFIG_SMP
	cpumask_copy(policy->cpus, topology_sibling_cpumask(policy->cpu));
#पूर्ण_अगर

	/* Errata workaround */
	cpuid = (c->x86 << 8) | (c->x86_model << 4) | c->x86_stepping;
	चयन (cpuid) अणु
	हाल 0x0f07:
	हाल 0x0f0a:
	हाल 0x0f11:
	हाल 0x0f12:
		has_N44_O17_errata[policy->cpu] = 1;
		pr_debug("has errata -- disabling low frequencies\n");
	पूर्ण

	अगर (speedstep_detect_processor() == SPEEDSTEP_CPU_P4D &&
	    c->x86_model < 2) अणु
		/* चयन to maximum frequency and measure result */
		cpufreq_p4_setdc(policy->cpu, DC_DISABLE);
		recalibrate_cpu_khz();
	पूर्ण
	/* get max frequency */
	stock_freq = cpufreq_p4_get_frequency(c);
	अगर (!stock_freq)
		वापस -EINVAL;

	/* table init */
	क्रम (i = 1; (p4घड़ीmod_table[i].frequency != CPUFREQ_TABLE_END); i++) अणु
		अगर ((i < 2) && (has_N44_O17_errata[policy->cpu]))
			p4घड़ीmod_table[i].frequency = CPUFREQ_ENTRY_INVALID;
		अन्यथा
			p4घड़ीmod_table[i].frequency = (stock_freq * i)/8;
	पूर्ण

	/* cpuinfo and शेष policy values */

	/* the transition latency is set to be 1 higher than the maximum
	 * transition latency of the ondemand governor */
	policy->cpuinfo.transition_latency = 10000001;
	policy->freq_table = &p4घड़ीmod_table[0];

	वापस 0;
पूर्ण


अटल अचिन्हित पूर्णांक cpufreq_p4_get(अचिन्हित पूर्णांक cpu)
अणु
	u32 l, h;

	rdmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, &l, &h);

	अगर (l & 0x10) अणु
		l = l >> 1;
		l &= 0x7;
	पूर्ण अन्यथा
		l = DC_DISABLE;

	अगर (l != DC_DISABLE)
		वापस stock_freq * l / 8;

	वापस stock_freq;
पूर्ण

अटल काष्ठा cpufreq_driver p4घड़ीmod_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= cpufreq_p4_target,
	.init		= cpufreq_p4_cpu_init,
	.get		= cpufreq_p4_get,
	.name		= "p4-clockmod",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id cpufreq_p4_id[] = अणु
	X86_MATCH_VENDOR_FEATURE(INTEL, X86_FEATURE_ACC, शून्य),
	अणुपूर्ण
पूर्ण;

/*
 * Intentionally no MODULE_DEVICE_TABLE here: this driver should not
 * be स्वतः loaded.  Please करोn't add one.
 */

अटल पूर्णांक __init cpufreq_p4_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * THERM_CONTROL is architectural क्रम IA32 now, so
	 * we can rely on the capability checks
	 */
	अगर (!x86_match_cpu(cpufreq_p4_id) || !boot_cpu_has(X86_FEATURE_ACPI))
		वापस -ENODEV;

	ret = cpufreq_रेजिस्टर_driver(&p4घड़ीmod_driver);
	अगर (!ret)
		pr_info("P4/Xeon(TM) CPU On-Demand Clock Modulation available\n");

	वापस ret;
पूर्ण


अटल व्योम __निकास cpufreq_p4_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&p4घड़ीmod_driver);
पूर्ण


MODULE_AUTHOR("Zwane Mwaikambo <zwane@commfireservices.com>");
MODULE_DESCRIPTION("cpufreq driver for Pentium(TM) 4/Xeon(TM)");
MODULE_LICENSE("GPL");

late_initcall(cpufreq_p4_init);
module_निकास(cpufreq_p4_निकास);
