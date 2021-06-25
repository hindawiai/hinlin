<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cpufreq driver क्रम Enhanced SpeedStep, as found in Intel's Pentium
 * M (part of the Centrino chipset).
 *
 * Since the original Pentium M, most new Intel CPUs support Enhanced
 * SpeedStep.
 *
 * Despite the "SpeedStep" in the name, this is almost entirely unlike
 * traditional SpeedStep.
 *
 * Modelled on speedstep.c
 *
 * Copyright (C) 2003 Jeremy Fitzhardinge <jeremy@goop.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/sched.h>	/* current */
#समावेश <linux/delay.h>
#समावेश <linux/compiler.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpu_device_id.h>

#घोषणा MAINTAINER	"linux-pm@vger.kernel.org"

#घोषणा INTEL_MSR_RANGE	(0xffff)

काष्ठा cpu_id
अणु
	__u8	x86;            /* CPU family */
	__u8	x86_model;	/* model */
	__u8	x86_stepping;	/* stepping */
पूर्ण;

क्रमागत अणु
	CPU_BANIAS,
	CPU_DOTHAN_A1,
	CPU_DOTHAN_A2,
	CPU_DOTHAN_B0,
	CPU_MP4HT_D0,
	CPU_MP4HT_E0,
पूर्ण;

अटल स्थिर काष्ठा cpu_id cpu_ids[] = अणु
	[CPU_BANIAS]	= अणु 6,  9, 5 पूर्ण,
	[CPU_DOTHAN_A1]	= अणु 6, 13, 1 पूर्ण,
	[CPU_DOTHAN_A2]	= अणु 6, 13, 2 पूर्ण,
	[CPU_DOTHAN_B0]	= अणु 6, 13, 6 पूर्ण,
	[CPU_MP4HT_D0]	= अणु15,  3, 4 पूर्ण,
	[CPU_MP4HT_E0]	= अणु15,  4, 1 पूर्ण,
पूर्ण;
#घोषणा N_IDS	ARRAY_SIZE(cpu_ids)

काष्ठा cpu_model
अणु
	स्थिर काष्ठा cpu_id *cpu_id;
	स्थिर अक्षर	*model_name;
	अचिन्हित	max_freq; /* max घड़ी in kHz */

	काष्ठा cpufreq_frequency_table *op_poपूर्णांकs; /* घड़ी/voltage pairs */
पूर्ण;
अटल पूर्णांक centrino_verअगरy_cpu_id(स्थिर काष्ठा cpuinfo_x86 *c,
				  स्थिर काष्ठा cpu_id *x);

/* Operating poपूर्णांकs क्रम current CPU */
अटल DEFINE_PER_CPU(काष्ठा cpu_model *, centrino_model);
अटल DEFINE_PER_CPU(स्थिर काष्ठा cpu_id *, centrino_cpu);

अटल काष्ठा cpufreq_driver centrino_driver;

#अगर_घोषित CONFIG_X86_SPEEDSTEP_CENTRINO_TABLE

/* Computes the correct क्रमm क्रम IA32_PERF_CTL MSR क्रम a particular
   frequency/voltage operating poपूर्णांक; frequency in MHz, volts in mV.
   This is stored as "driver_data" in the काष्ठाure. */
#घोषणा OP(mhz, mv)							\
	अणु								\
		.frequency = (mhz) * 1000,				\
		.driver_data = (((mhz)/100) << 8) | ((mv - 700) / 16)		\
	पूर्ण

/*
 * These voltage tables were derived from the Intel Pentium M
 * datasheet, करोcument 25261202.pdf, Table 5.  I have verअगरied they
 * are consistent with my IBM ThinkPad X31, which has a 1.3GHz Pentium
 * M.
 */

/* Ultra Low Voltage Intel Pentium M processor 900MHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_900[] =
अणु
	OP(600,  844),
	OP(800,  988),
	OP(900, 1004),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Ultra Low Voltage Intel Pentium M processor 1000MHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1000[] =
अणु
	OP(600,   844),
	OP(800,   972),
	OP(900,   988),
	OP(1000, 1004),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Low Voltage Intel Pentium M processor 1.10GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1100[] =
अणु
	OP( 600,  956),
	OP( 800, 1020),
	OP( 900, 1100),
	OP(1000, 1164),
	OP(1100, 1180),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;


/* Low Voltage Intel Pentium M processor 1.20GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1200[] =
अणु
	OP( 600,  956),
	OP( 800, 1004),
	OP( 900, 1020),
	OP(1000, 1100),
	OP(1100, 1164),
	OP(1200, 1180),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Intel Pentium M processor 1.30GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1300[] =
अणु
	OP( 600,  956),
	OP( 800, 1260),
	OP(1000, 1292),
	OP(1200, 1356),
	OP(1300, 1388),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Intel Pentium M processor 1.40GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1400[] =
अणु
	OP( 600,  956),
	OP( 800, 1180),
	OP(1000, 1308),
	OP(1200, 1436),
	OP(1400, 1484),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Intel Pentium M processor 1.50GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1500[] =
अणु
	OP( 600,  956),
	OP( 800, 1116),
	OP(1000, 1228),
	OP(1200, 1356),
	OP(1400, 1452),
	OP(1500, 1484),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Intel Pentium M processor 1.60GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1600[] =
अणु
	OP( 600,  956),
	OP( 800, 1036),
	OP(1000, 1164),
	OP(1200, 1276),
	OP(1400, 1420),
	OP(1600, 1484),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;

/* Intel Pentium M processor 1.70GHz (Banias) */
अटल काष्ठा cpufreq_frequency_table banias_1700[] =
अणु
	OP( 600,  956),
	OP( 800, 1004),
	OP(1000, 1116),
	OP(1200, 1228),
	OP(1400, 1308),
	OP(1700, 1484),
	अणु .frequency = CPUFREQ_TABLE_END पूर्ण
पूर्ण;
#अघोषित OP

#घोषणा _BANIAS(cpuid, max, name)	\
अणु	.cpu_id		= cpuid,	\
	.model_name	= "Intel(R) Pentium(R) M processor " name "MHz", \
	.max_freq	= (max)*1000,	\
	.op_poपूर्णांकs	= banias_##max,	\
पूर्ण
#घोषणा BANIAS(max)	_BANIAS(&cpu_ids[CPU_BANIAS], max, #max)

/* CPU models, their operating frequency range, and freq/voltage
   operating poपूर्णांकs */
अटल काष्ठा cpu_model models[] =
अणु
	_BANIAS(&cpu_ids[CPU_BANIAS], 900, " 900"),
	BANIAS(1000),
	BANIAS(1100),
	BANIAS(1200),
	BANIAS(1300),
	BANIAS(1400),
	BANIAS(1500),
	BANIAS(1600),
	BANIAS(1700),

	/* शून्य model_name is a wildcard */
	अणु &cpu_ids[CPU_DOTHAN_A1], शून्य, 0, शून्य पूर्ण,
	अणु &cpu_ids[CPU_DOTHAN_A2], शून्य, 0, शून्य पूर्ण,
	अणु &cpu_ids[CPU_DOTHAN_B0], शून्य, 0, शून्य पूर्ण,
	अणु &cpu_ids[CPU_MP4HT_D0], शून्य, 0, शून्य पूर्ण,
	अणु &cpu_ids[CPU_MP4HT_E0], शून्य, 0, शून्य पूर्ण,

	अणु शून्य, पूर्ण
पूर्ण;
#अघोषित _BANIAS
#अघोषित BANIAS

अटल पूर्णांक centrino_cpu_init_table(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *cpu = &cpu_data(policy->cpu);
	काष्ठा cpu_model *model;

	क्रम(model = models; model->cpu_id != शून्य; model++)
		अगर (centrino_verअगरy_cpu_id(cpu, model->cpu_id) &&
		    (model->model_name == शून्य ||
		     म_भेद(cpu->x86_model_id, model->model_name) == 0))
			अवरोध;

	अगर (model->cpu_id == शून्य) अणु
		/* No match at all */
		pr_debug("no support for CPU model \"%s\": "
		       "send /proc/cpuinfo to " MAINTAINER "\n",
		       cpu->x86_model_id);
		वापस -ENOENT;
	पूर्ण

	अगर (model->op_poपूर्णांकs == शून्य) अणु
		/* Matched a non-match */
		pr_debug("no table support for CPU model \"%s\"\n",
		       cpu->x86_model_id);
		pr_debug("try using the acpi-cpufreq driver\n");
		वापस -ENOENT;
	पूर्ण

	per_cpu(centrino_model, policy->cpu) = model;

	pr_debug("found \"%s\": max frequency: %dkHz\n",
	       model->model_name, model->max_freq);

	वापस 0;
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक centrino_cpu_init_table(काष्ठा cpufreq_policy *policy)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_SPEEDSTEP_CENTRINO_TABLE */

अटल पूर्णांक centrino_verअगरy_cpu_id(स्थिर काष्ठा cpuinfo_x86 *c,
				  स्थिर काष्ठा cpu_id *x)
अणु
	अगर ((c->x86 == x->x86) &&
	    (c->x86_model == x->x86_model) &&
	    (c->x86_stepping == x->x86_stepping))
		वापस 1;
	वापस 0;
पूर्ण

/* To be called only after centrino_model is initialized */
अटल अचिन्हित extract_घड़ी(अचिन्हित msr, अचिन्हित पूर्णांक cpu, पूर्णांक failsafe)
अणु
	पूर्णांक i;

	/*
	 * Extract घड़ी in kHz from PERF_CTL value
	 * क्रम centrino, as some DSDTs are buggy.
	 * Ideally, this can be करोne using the acpi_data काष्ठाure.
	 */
	अगर ((per_cpu(centrino_cpu, cpu) == &cpu_ids[CPU_BANIAS]) ||
	    (per_cpu(centrino_cpu, cpu) == &cpu_ids[CPU_DOTHAN_A1]) ||
	    (per_cpu(centrino_cpu, cpu) == &cpu_ids[CPU_DOTHAN_B0])) अणु
		msr = (msr >> 8) & 0xff;
		वापस msr * 100000;
	पूर्ण

	अगर ((!per_cpu(centrino_model, cpu)) ||
	    (!per_cpu(centrino_model, cpu)->op_poपूर्णांकs))
		वापस 0;

	msr &= 0xffff;
	क्रम (i = 0;
		per_cpu(centrino_model, cpu)->op_poपूर्णांकs[i].frequency
							!= CPUFREQ_TABLE_END;
	     i++) अणु
		अगर (msr == per_cpu(centrino_model, cpu)->op_poपूर्णांकs[i].driver_data)
			वापस per_cpu(centrino_model, cpu)->
							op_poपूर्णांकs[i].frequency;
	पूर्ण
	अगर (failsafe)
		वापस per_cpu(centrino_model, cpu)->op_poपूर्णांकs[i-1].frequency;
	अन्यथा
		वापस 0;
पूर्ण

/* Return the current CPU frequency in kHz */
अटल अचिन्हित पूर्णांक get_cur_freq(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित l, h;
	अचिन्हित घड़ी_freq;

	rdmsr_on_cpu(cpu, MSR_IA32_PERF_STATUS, &l, &h);
	घड़ी_freq = extract_घड़ी(l, cpu, 0);

	अगर (unlikely(घड़ी_freq == 0)) अणु
		/*
		 * On some CPUs, we can see transient MSR values (which are
		 * not present in _PSS), जबतक CPU is करोing some स्वतःmatic
		 * P-state transition (like TM2). Get the last freq set 
		 * in PERF_CTL.
		 */
		rdmsr_on_cpu(cpu, MSR_IA32_PERF_CTL, &l, &h);
		घड़ी_freq = extract_घड़ी(l, cpu, 1);
	पूर्ण
	वापस घड़ी_freq;
पूर्ण


अटल पूर्णांक centrino_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *cpu = &cpu_data(policy->cpu);
	अचिन्हित l, h;
	पूर्णांक i;

	/* Only Intel makes Enhanced Speedstep-capable CPUs */
	अगर (cpu->x86_venकरोr != X86_VENDOR_INTEL ||
	    !cpu_has(cpu, X86_FEATURE_EST))
		वापस -ENODEV;

	अगर (cpu_has(cpu, X86_FEATURE_CONSTANT_TSC))
		centrino_driver.flags |= CPUFREQ_CONST_LOOPS;

	अगर (policy->cpu != 0)
		वापस -ENODEV;

	क्रम (i = 0; i < N_IDS; i++)
		अगर (centrino_verअगरy_cpu_id(cpu, &cpu_ids[i]))
			अवरोध;

	अगर (i != N_IDS)
		per_cpu(centrino_cpu, policy->cpu) = &cpu_ids[i];

	अगर (!per_cpu(centrino_cpu, policy->cpu)) अणु
		pr_debug("found unsupported CPU with "
		"Enhanced SpeedStep: send /proc/cpuinfo to "
		MAINTAINER "\n");
		वापस -ENODEV;
	पूर्ण

	अगर (centrino_cpu_init_table(policy))
		वापस -ENODEV;

	/* Check to see अगर Enhanced SpeedStep is enabled, and try to
	   enable it अगर not. */
	rdmsr(MSR_IA32_MISC_ENABLE, l, h);

	अगर (!(l & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP)) अणु
		l |= MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP;
		pr_debug("trying to enable Enhanced SpeedStep (%x)\n", l);
		wrmsr(MSR_IA32_MISC_ENABLE, l, h);

		/* check to see अगर it stuck */
		rdmsr(MSR_IA32_MISC_ENABLE, l, h);
		अगर (!(l & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP)) अणु
			pr_info("couldn't enable Enhanced SpeedStep\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	policy->cpuinfo.transition_latency = 10000;
						/* 10uS transition latency */
	policy->freq_table = per_cpu(centrino_model, policy->cpu)->op_poपूर्णांकs;

	वापस 0;
पूर्ण

अटल पूर्णांक centrino_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;

	अगर (!per_cpu(centrino_model, cpu))
		वापस -ENODEV;

	per_cpu(centrino_model, cpu) = शून्य;

	वापस 0;
पूर्ण

/**
 * centrino_target - set a new CPUFreq policy
 * @policy: new policy
 * @index: index of target frequency
 *
 * Sets a new CPUFreq policy.
 */
अटल पूर्णांक centrino_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक	msr, oldmsr = 0, h = 0, cpu = policy->cpu;
	पूर्णांक			retval = 0;
	अचिन्हित पूर्णांक		j, first_cpu;
	काष्ठा cpufreq_frequency_table *op_poपूर्णांकs;
	cpumask_var_t covered_cpus;

	अगर (unlikely(!zalloc_cpumask_var(&covered_cpus, GFP_KERNEL)))
		वापस -ENOMEM;

	अगर (unlikely(per_cpu(centrino_model, cpu) == शून्य)) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	first_cpu = 1;
	op_poपूर्णांकs = &per_cpu(centrino_model, cpu)->op_poपूर्णांकs[index];
	क्रम_each_cpu(j, policy->cpus) अणु
		पूर्णांक good_cpu;

		/*
		 * Support क्रम SMP प्रणालीs.
		 * Make sure we are running on CPU that wants to change freq
		 */
		अगर (policy->shared_type == CPUFREQ_SHARED_TYPE_ANY)
			good_cpu = cpumask_any_and(policy->cpus,
						   cpu_online_mask);
		अन्यथा
			good_cpu = j;

		अगर (good_cpu >= nr_cpu_ids) अणु
			pr_debug("couldn't limit to CPUs in this domain\n");
			retval = -EAGAIN;
			अगर (first_cpu) अणु
				/* We haven't started the transition yet. */
				जाओ out;
			पूर्ण
			अवरोध;
		पूर्ण

		msr = op_poपूर्णांकs->driver_data;

		अगर (first_cpu) अणु
			rdmsr_on_cpu(good_cpu, MSR_IA32_PERF_CTL, &oldmsr, &h);
			अगर (msr == (oldmsr & 0xffff)) अणु
				pr_debug("no change needed - msr was and needs "
					"to be %x\n", oldmsr);
				retval = 0;
				जाओ out;
			पूर्ण

			first_cpu = 0;
			/* all but 16 LSB are reserved, treat them with care */
			oldmsr &= ~0xffff;
			msr &= 0xffff;
			oldmsr |= msr;
		पूर्ण

		wrmsr_on_cpu(good_cpu, MSR_IA32_PERF_CTL, oldmsr, h);
		अगर (policy->shared_type == CPUFREQ_SHARED_TYPE_ANY)
			अवरोध;

		cpumask_set_cpu(j, covered_cpus);
	पूर्ण

	अगर (unlikely(retval)) अणु
		/*
		 * We have failed halfway through the frequency change.
		 * We have sent callbacks to policy->cpus and
		 * MSRs have alपढ़ोy been written on coverd_cpus.
		 * Best efक्रमt unकरो..
		 */

		क्रम_each_cpu(j, covered_cpus)
			wrmsr_on_cpu(j, MSR_IA32_PERF_CTL, oldmsr, h);
	पूर्ण
	retval = 0;

out:
	मुक्त_cpumask_var(covered_cpus);
	वापस retval;
पूर्ण

अटल काष्ठा cpufreq_driver centrino_driver = अणु
	.name		= "centrino", /* should be speedstep-centrino,
					 but there's a 16 अक्षर limit */
	.init		= centrino_cpu_init,
	.निकास		= centrino_cpu_निकास,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= centrino_target,
	.get		= get_cur_freq,
	.attr		= cpufreq_generic_attr,
पूर्ण;

/*
 * This करोesn't replace the detailed checks above because
 * the generic CPU IDs करोn't have a way to match क्रम steppings
 * or ASCII model IDs.
 */
अटल स्थिर काष्ठा x86_cpu_id centrino_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL,  6,  9, X86_FEATURE_EST, शून्य),
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL,  6, 13, X86_FEATURE_EST, शून्य),
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 15,  3, X86_FEATURE_EST, शून्य),
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 15,  4, X86_FEATURE_EST, शून्य),
	अणुपूर्ण
पूर्ण;

/**
 * centrino_init - initializes the Enhanced SpeedStep CPUFreq driver
 *
 * Initializes the Enhanced SpeedStep support. Returns -ENODEV on
 * unsupported devices, -ENOENT अगर there's no voltage table क्रम this
 * particular CPU model, -EINVAL on problems during initiatization,
 * and zero on success.
 *
 * This is quite picky.  Not only करोes the CPU have to advertise the
 * "est" flag in the cpuid capability flags, we look क्रम a specअगरic
 * CPU model and stepping, and we need to have the exact model name in
 * our voltage tables.  That is, be paranoid about not releasing
 * someone's valuable magic smoke.
 */
अटल पूर्णांक __init centrino_init(व्योम)
अणु
	अगर (!x86_match_cpu(centrino_ids))
		वापस -ENODEV;
	वापस cpufreq_रेजिस्टर_driver(&centrino_driver);
पूर्ण

अटल व्योम __निकास centrino_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&centrino_driver);
पूर्ण

MODULE_AUTHOR ("Jeremy Fitzhardinge <jeremy@goop.org>");
MODULE_DESCRIPTION ("Enhanced SpeedStep driver for Intel Pentium M processors.");
MODULE_LICENSE ("GPL");

late_initcall(centrino_init);
module_निकास(centrino_निकास);
