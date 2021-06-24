<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * acpi-cpufreq.c - ACPI Processor P-States Driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2002 - 2004 Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2006       Denis Sadykov <denis.m.sadykov@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/compiler.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>

#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश <acpi/processor.h>
#समावेश <acpi/cppc_acpi.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpu_device_id.h>

MODULE_AUTHOR("Paul Diefenbaugh, Dominik Brodowski");
MODULE_DESCRIPTION("ACPI Processor P-States Driver");
MODULE_LICENSE("GPL");

क्रमागत अणु
	UNDEFINED_CAPABLE = 0,
	SYSTEM_INTEL_MSR_CAPABLE,
	SYSTEM_AMD_MSR_CAPABLE,
	SYSTEM_IO_CAPABLE,
पूर्ण;

#घोषणा INTEL_MSR_RANGE		(0xffff)
#घोषणा AMD_MSR_RANGE		(0x7)
#घोषणा HYGON_MSR_RANGE		(0x7)

#घोषणा MSR_K7_HWCR_CPB_DIS	(1ULL << 25)

काष्ठा acpi_cpufreq_data अणु
	अचिन्हित पूर्णांक resume;
	अचिन्हित पूर्णांक cpu_feature;
	अचिन्हित पूर्णांक acpi_perf_cpu;
	cpumask_var_t freqकरोमुख्य_cpus;
	व्योम (*cpu_freq_ग_लिखो)(काष्ठा acpi_pct_रेजिस्टर *reg, u32 val);
	u32 (*cpu_freq_पढ़ो)(काष्ठा acpi_pct_रेजिस्टर *reg);
पूर्ण;

/* acpi_perf_data is a poपूर्णांकer to percpu data. */
अटल काष्ठा acpi_processor_perक्रमmance __percpu *acpi_perf_data;

अटल अंतरभूत काष्ठा acpi_processor_perक्रमmance *to_perf_data(काष्ठा acpi_cpufreq_data *data)
अणु
	वापस per_cpu_ptr(acpi_perf_data, data->acpi_perf_cpu);
पूर्ण

अटल काष्ठा cpufreq_driver acpi_cpufreq_driver;

अटल अचिन्हित पूर्णांक acpi_pstate_strict;

अटल bool boost_state(अचिन्हित पूर्णांक cpu)
अणु
	u32 lo, hi;
	u64 msr;

	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		rdmsr_on_cpu(cpu, MSR_IA32_MISC_ENABLE, &lo, &hi);
		msr = lo | ((u64)hi << 32);
		वापस !(msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE);
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
		rdmsr_on_cpu(cpu, MSR_K7_HWCR, &lo, &hi);
		msr = lo | ((u64)hi << 32);
		वापस !(msr & MSR_K7_HWCR_CPB_DIS);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक boost_set_msr(bool enable)
अणु
	u32 msr_addr;
	u64 msr_mask, val;

	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		msr_addr = MSR_IA32_MISC_ENABLE;
		msr_mask = MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
		अवरोध;
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
		msr_addr = MSR_K7_HWCR;
		msr_mask = MSR_K7_HWCR_CPB_DIS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rdmsrl(msr_addr, val);

	अगर (enable)
		val &= ~msr_mask;
	अन्यथा
		val |= msr_mask;

	wrmsrl(msr_addr, val);
	वापस 0;
पूर्ण

अटल व्योम boost_set_msr_each(व्योम *p_en)
अणु
	bool enable = (bool) p_en;

	boost_set_msr(enable);
पूर्ण

अटल पूर्णांक set_boost(काष्ठा cpufreq_policy *policy, पूर्णांक val)
अणु
	on_each_cpu_mask(policy->cpus, boost_set_msr_each,
			 (व्योम *)(दीर्घ)val, 1);
	pr_debug("CPU %*pbl: Core Boosting %sabled.\n",
		 cpumask_pr_args(policy->cpus), val ? "en" : "dis");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_freqकरोमुख्य_cpus(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;

	अगर (unlikely(!data))
		वापस -ENODEV;

	वापस cpufreq_show_cpus(data->freqकरोमुख्य_cpus, buf);
पूर्ण

cpufreq_freq_attr_ro(freqकरोमुख्य_cpus);

#अगर_घोषित CONFIG_X86_ACPI_CPUFREQ_CPB
अटल sमाप_प्रकार store_cpb(काष्ठा cpufreq_policy *policy, स्थिर अक्षर *buf,
			 माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = 0;

	अगर (!acpi_cpufreq_driver.set_boost)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret || val > 1)
		वापस -EINVAL;

	get_online_cpus();
	set_boost(policy, val);
	put_online_cpus();

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_cpb(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", acpi_cpufreq_driver.boost_enabled);
पूर्ण

cpufreq_freq_attr_rw(cpb);
#पूर्ण_अगर

अटल पूर्णांक check_est_cpu(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpuinfo_x86 *cpu = &cpu_data(cpuid);

	वापस cpu_has(cpu, X86_FEATURE_EST);
पूर्ण

अटल पूर्णांक check_amd_hwpstate_cpu(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpuinfo_x86 *cpu = &cpu_data(cpuid);

	वापस cpu_has(cpu, X86_FEATURE_HW_PSTATE);
पूर्ण

अटल अचिन्हित extract_io(काष्ठा cpufreq_policy *policy, u32 value)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;
	काष्ठा acpi_processor_perक्रमmance *perf;
	पूर्णांक i;

	perf = to_perf_data(data);

	क्रम (i = 0; i < perf->state_count; i++) अणु
		अगर (value == perf->states[i].status)
			वापस policy->freq_table[i].frequency;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित extract_msr(काष्ठा cpufreq_policy *policy, u32 msr)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;
	काष्ठा cpufreq_frequency_table *pos;
	काष्ठा acpi_processor_perक्रमmance *perf;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		msr &= AMD_MSR_RANGE;
	अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		msr &= HYGON_MSR_RANGE;
	अन्यथा
		msr &= INTEL_MSR_RANGE;

	perf = to_perf_data(data);

	cpufreq_क्रम_each_entry(pos, policy->freq_table)
		अगर (msr == perf->states[pos->driver_data].status)
			वापस pos->frequency;
	वापस policy->freq_table[0].frequency;
पूर्ण

अटल अचिन्हित extract_freq(काष्ठा cpufreq_policy *policy, u32 val)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;

	चयन (data->cpu_feature) अणु
	हाल SYSTEM_INTEL_MSR_CAPABLE:
	हाल SYSTEM_AMD_MSR_CAPABLE:
		वापस extract_msr(policy, val);
	हाल SYSTEM_IO_CAPABLE:
		वापस extract_io(policy, val);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 cpu_freq_पढ़ो_पूर्णांकel(काष्ठा acpi_pct_रेजिस्टर *not_used)
अणु
	u32 val, dummy __always_unused;

	rdmsr(MSR_IA32_PERF_CTL, val, dummy);
	वापस val;
पूर्ण

अटल व्योम cpu_freq_ग_लिखो_पूर्णांकel(काष्ठा acpi_pct_रेजिस्टर *not_used, u32 val)
अणु
	u32 lo, hi;

	rdmsr(MSR_IA32_PERF_CTL, lo, hi);
	lo = (lo & ~INTEL_MSR_RANGE) | (val & INTEL_MSR_RANGE);
	wrmsr(MSR_IA32_PERF_CTL, lo, hi);
पूर्ण

अटल u32 cpu_freq_पढ़ो_amd(काष्ठा acpi_pct_रेजिस्टर *not_used)
अणु
	u32 val, dummy __always_unused;

	rdmsr(MSR_AMD_PERF_CTL, val, dummy);
	वापस val;
पूर्ण

अटल व्योम cpu_freq_ग_लिखो_amd(काष्ठा acpi_pct_रेजिस्टर *not_used, u32 val)
अणु
	wrmsr(MSR_AMD_PERF_CTL, val, 0);
पूर्ण

अटल u32 cpu_freq_पढ़ो_io(काष्ठा acpi_pct_रेजिस्टर *reg)
अणु
	u32 val;

	acpi_os_पढ़ो_port(reg->address, &val, reg->bit_width);
	वापस val;
पूर्ण

अटल व्योम cpu_freq_ग_लिखो_io(काष्ठा acpi_pct_रेजिस्टर *reg, u32 val)
अणु
	acpi_os_ग_लिखो_port(reg->address, val, reg->bit_width);
पूर्ण

काष्ठा drv_cmd अणु
	काष्ठा acpi_pct_रेजिस्टर *reg;
	u32 val;
	जोड़ अणु
		व्योम (*ग_लिखो)(काष्ठा acpi_pct_रेजिस्टर *reg, u32 val);
		u32 (*पढ़ो)(काष्ठा acpi_pct_रेजिस्टर *reg);
	पूर्ण func;
पूर्ण;

/* Called via smp_call_function_single(), on the target CPU */
अटल व्योम करो_drv_पढ़ो(व्योम *_cmd)
अणु
	काष्ठा drv_cmd *cmd = _cmd;

	cmd->val = cmd->func.पढ़ो(cmd->reg);
पूर्ण

अटल u32 drv_पढ़ो(काष्ठा acpi_cpufreq_data *data, स्थिर काष्ठा cpumask *mask)
अणु
	काष्ठा acpi_processor_perक्रमmance *perf = to_perf_data(data);
	काष्ठा drv_cmd cmd = अणु
		.reg = &perf->control_रेजिस्टर,
		.func.पढ़ो = data->cpu_freq_पढ़ो,
	पूर्ण;
	पूर्णांक err;

	err = smp_call_function_any(mask, करो_drv_पढ़ो, &cmd, 1);
	WARN_ON_ONCE(err);	/* smp_call_function_any() was buggy? */
	वापस cmd.val;
पूर्ण

/* Called via smp_call_function_many(), on the target CPUs */
अटल व्योम करो_drv_ग_लिखो(व्योम *_cmd)
अणु
	काष्ठा drv_cmd *cmd = _cmd;

	cmd->func.ग_लिखो(cmd->reg, cmd->val);
पूर्ण

अटल व्योम drv_ग_लिखो(काष्ठा acpi_cpufreq_data *data,
		      स्थिर काष्ठा cpumask *mask, u32 val)
अणु
	काष्ठा acpi_processor_perक्रमmance *perf = to_perf_data(data);
	काष्ठा drv_cmd cmd = अणु
		.reg = &perf->control_रेजिस्टर,
		.val = val,
		.func.ग_लिखो = data->cpu_freq_ग_लिखो,
	पूर्ण;
	पूर्णांक this_cpu;

	this_cpu = get_cpu();
	अगर (cpumask_test_cpu(this_cpu, mask))
		करो_drv_ग_लिखो(&cmd);

	smp_call_function_many(mask, करो_drv_ग_लिखो, &cmd, 1);
	put_cpu();
पूर्ण

अटल u32 get_cur_val(स्थिर काष्ठा cpumask *mask, काष्ठा acpi_cpufreq_data *data)
अणु
	u32 val;

	अगर (unlikely(cpumask_empty(mask)))
		वापस 0;

	val = drv_पढ़ो(data, mask);

	pr_debug("%s = %u\n", __func__, val);

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक get_cur_freq_on_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_cpufreq_data *data;
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक freq;
	अचिन्हित पूर्णांक cached_freq;

	pr_debug("%s (%d)\n", __func__, cpu);

	policy = cpufreq_cpu_get_raw(cpu);
	अगर (unlikely(!policy))
		वापस 0;

	data = policy->driver_data;
	अगर (unlikely(!data || !policy->freq_table))
		वापस 0;

	cached_freq = policy->freq_table[to_perf_data(data)->state].frequency;
	freq = extract_freq(policy, get_cur_val(cpumask_of(cpu), data));
	अगर (freq != cached_freq) अणु
		/*
		 * The dपढ़ोed BIOS frequency change behind our back.
		 * Force set the frequency on next target call.
		 */
		data->resume = 1;
	पूर्ण

	pr_debug("cur freq = %u\n", freq);

	वापस freq;
पूर्ण

अटल अचिन्हित पूर्णांक check_freqs(काष्ठा cpufreq_policy *policy,
				स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;
	अचिन्हित पूर्णांक cur_freq;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		cur_freq = extract_freq(policy, get_cur_val(mask, data));
		अगर (cur_freq == freq)
			वापस 1;
		udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_cpufreq_target(काष्ठा cpufreq_policy *policy,
			       अचिन्हित पूर्णांक index)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;
	काष्ठा acpi_processor_perक्रमmance *perf;
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक next_perf_state = 0; /* Index पूर्णांकo perf table */
	पूर्णांक result = 0;

	अगर (unlikely(!data)) अणु
		वापस -ENODEV;
	पूर्ण

	perf = to_perf_data(data);
	next_perf_state = policy->freq_table[index].driver_data;
	अगर (perf->state == next_perf_state) अणु
		अगर (unlikely(data->resume)) अणु
			pr_debug("Called after resume, resetting to P%d\n",
				next_perf_state);
			data->resume = 0;
		पूर्ण अन्यथा अणु
			pr_debug("Already at target state (P%d)\n",
				next_perf_state);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * The core won't allow CPUs to go away until the governor has been
	 * stopped, so we can rely on the stability of policy->cpus.
	 */
	mask = policy->shared_type == CPUFREQ_SHARED_TYPE_ANY ?
		cpumask_of(policy->cpu) : policy->cpus;

	drv_ग_लिखो(data, mask, perf->states[next_perf_state].control);

	अगर (acpi_pstate_strict) अणु
		अगर (!check_freqs(policy, mask,
				 policy->freq_table[index].frequency)) अणु
			pr_debug("%s (%d)\n", __func__, policy->cpu);
			result = -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (!result)
		perf->state = next_perf_state;

	वापस result;
पूर्ण

अटल अचिन्हित पूर्णांक acpi_cpufreq_fast_चयन(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;
	काष्ठा acpi_processor_perक्रमmance *perf;
	काष्ठा cpufreq_frequency_table *entry;
	अचिन्हित पूर्णांक next_perf_state, next_freq, index;

	/*
	 * Find the बंदst frequency above target_freq.
	 */
	अगर (policy->cached_target_freq == target_freq)
		index = policy->cached_resolved_idx;
	अन्यथा
		index = cpufreq_table_find_index_dl(policy, target_freq);

	entry = &policy->freq_table[index];
	next_freq = entry->frequency;
	next_perf_state = entry->driver_data;

	perf = to_perf_data(data);
	अगर (perf->state == next_perf_state) अणु
		अगर (unlikely(data->resume))
			data->resume = 0;
		अन्यथा
			वापस next_freq;
	पूर्ण

	data->cpu_freq_ग_लिखो(&perf->control_रेजिस्टर,
			     perf->states[next_perf_state].control);
	perf->state = next_perf_state;
	वापस next_freq;
पूर्ण

अटल अचिन्हित दीर्घ
acpi_cpufreq_guess_freq(काष्ठा acpi_cpufreq_data *data, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_processor_perक्रमmance *perf;

	perf = to_perf_data(data);
	अगर (cpu_khz) अणु
		/* search the बंदst match to cpu_khz */
		अचिन्हित पूर्णांक i;
		अचिन्हित दीर्घ freq;
		अचिन्हित दीर्घ freqn = perf->states[0].core_frequency * 1000;

		क्रम (i = 0; i < (perf->state_count-1); i++) अणु
			freq = freqn;
			freqn = perf->states[i+1].core_frequency * 1000;
			अगर ((2 * cpu_khz) > (freqn + freq)) अणु
				perf->state = i;
				वापस freq;
			पूर्ण
		पूर्ण
		perf->state = perf->state_count-1;
		वापस freqn;
	पूर्ण अन्यथा अणु
		/* assume CPU is at P0... */
		perf->state = 0;
		वापस perf->states[0].core_frequency * 1000;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_acpi_perf_data(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	/* Freeing a शून्य poपूर्णांकer is OK, and alloc_percpu zeroes. */
	क्रम_each_possible_cpu(i)
		मुक्त_cpumask_var(per_cpu_ptr(acpi_perf_data, i)
				 ->shared_cpu_map);
	मुक्त_percpu(acpi_perf_data);
पूर्ण

अटल पूर्णांक cpufreq_boost_online(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * On the CPU_UP path we simply keep the boost-disable flag
	 * in sync with the current global state.
	 */
	वापस boost_set_msr(acpi_cpufreq_driver.boost_enabled);
पूर्ण

अटल पूर्णांक cpufreq_boost_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Clear the boost-disable bit on the CPU_DOWN path so that
	 * this cpu cannot block the reमुख्यing ones from boosting.
	 */
	वापस boost_set_msr(1);
पूर्ण

/*
 * acpi_cpufreq_early_init - initialize ACPI P-States library
 *
 * Initialize the ACPI P-States library (drivers/acpi/processor_perflib.c)
 * in order to determine correct frequency and voltage pairings. We can
 * करो _PDC and _PSD and find out the processor dependency क्रम the
 * actual init that will happen later...
 */
अटल पूर्णांक __init acpi_cpufreq_early_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	pr_debug("%s\n", __func__);

	acpi_perf_data = alloc_percpu(काष्ठा acpi_processor_perक्रमmance);
	अगर (!acpi_perf_data) अणु
		pr_debug("Memory allocation error for acpi_perf_data.\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम_each_possible_cpu(i) अणु
		अगर (!zalloc_cpumask_var_node(
			&per_cpu_ptr(acpi_perf_data, i)->shared_cpu_map,
			GFP_KERNEL, cpu_to_node(i))) अणु

			/* Freeing a शून्य poपूर्णांकer is OK: alloc_percpu zeroes. */
			मुक्त_acpi_perf_data();
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Do initialization in ACPI core */
	acpi_processor_preरेजिस्टर_perक्रमmance(acpi_perf_data);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * Some BIOSes करो SW_ANY coordination पूर्णांकernally, either set it up in hw
 * or करो it in BIOS firmware and won't inक्रमm about it to OS. If not
 * detected, this has a side effect of making CPU run at a dअगरferent speed
 * than OS पूर्णांकended it to run at. Detect it and handle it cleanly.
 */
अटल पूर्णांक bios_with_sw_any_bug;

अटल पूर्णांक sw_any_bug_found(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	bios_with_sw_any_bug = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sw_any_bug_dmi_table[] = अणु
	अणु
		.callback = sw_any_bug_found,
		.ident = "Supermicro Server X6DLP",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Supermicro"),
			DMI_MATCH(DMI_BIOS_VERSION, "080010"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X6DLP"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक acpi_cpufreq_blacklist(काष्ठा cpuinfo_x86 *c)
अणु
	/* Intel Xeon Processor 7100 Series Specअगरication Update
	 * https://www.पूर्णांकel.com/Assets/PDF/specupdate/314554.pdf
	 * AL30: A Machine Check Exception (MCE) Occurring during an
	 * Enhanced Intel SpeedStep Technology Ratio Change May Cause
	 * Both Processor Cores to Lock Up. */
	अगर (c->x86_venकरोr == X86_VENDOR_INTEL) अणु
		अगर ((c->x86 == 15) &&
		    (c->x86_model == 6) &&
		    (c->x86_stepping == 8)) अणु
			pr_info("Intel(R) Xeon(R) 7100 Errata AL30, processors may lock up on frequency changes: disabling acpi-cpufreq\n");
			वापस -ENODEV;
		    पूर्ण
		पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
अटल u64 get_max_boost_ratio(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cppc_perf_caps perf_caps;
	u64 highest_perf, nominal_perf;
	पूर्णांक ret;

	अगर (acpi_pstate_strict)
		वापस 0;

	ret = cppc_get_perf_caps(cpu, &perf_caps);
	अगर (ret) अणु
		pr_debug("CPU%d: Unable to get performance capabilities (%d)\n",
			 cpu, ret);
		वापस 0;
	पूर्ण

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		highest_perf = amd_get_highest_perf();
	अन्यथा
		highest_perf = perf_caps.highest_perf;

	nominal_perf = perf_caps.nominal_perf;

	अगर (!highest_perf || !nominal_perf) अणु
		pr_debug("CPU%d: highest or nominal performance missing\n", cpu);
		वापस 0;
	पूर्ण

	अगर (highest_perf < nominal_perf) अणु
		pr_debug("CPU%d: nominal performance above highest\n", cpu);
		वापस 0;
	पूर्ण

	वापस भाग_u64(highest_perf << SCHED_CAPACITY_SHIFT, nominal_perf);
पूर्ण
#अन्यथा
अटल अंतरभूत u64 get_max_boost_ratio(अचिन्हित पूर्णांक cpu) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक acpi_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *freq_table;
	काष्ठा acpi_processor_perक्रमmance *perf;
	काष्ठा acpi_cpufreq_data *data;
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	अचिन्हित पूर्णांक valid_states = 0;
	अचिन्हित पूर्णांक result = 0;
	u64 max_boost_ratio;
	अचिन्हित पूर्णांक i;
#अगर_घोषित CONFIG_SMP
	अटल पूर्णांक blacklisted;
#पूर्ण_अगर

	pr_debug("%s\n", __func__);

#अगर_घोषित CONFIG_SMP
	अगर (blacklisted)
		वापस blacklisted;
	blacklisted = acpi_cpufreq_blacklist(c);
	अगर (blacklisted)
		वापस blacklisted;
#पूर्ण_अगर

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(&data->freqकरोमुख्य_cpus, GFP_KERNEL)) अणु
		result = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	perf = per_cpu_ptr(acpi_perf_data, cpu);
	data->acpi_perf_cpu = cpu;
	policy->driver_data = data;

	अगर (cpu_has(c, X86_FEATURE_CONSTANT_TSC))
		acpi_cpufreq_driver.flags |= CPUFREQ_CONST_LOOPS;

	result = acpi_processor_रेजिस्टर_perक्रमmance(perf, cpu);
	अगर (result)
		जाओ err_मुक्त_mask;

	policy->shared_type = perf->shared_type;

	/*
	 * Will let policy->cpus know about dependency only when software
	 * coordination is required.
	 */
	अगर (policy->shared_type == CPUFREQ_SHARED_TYPE_ALL ||
	    policy->shared_type == CPUFREQ_SHARED_TYPE_ANY) अणु
		cpumask_copy(policy->cpus, perf->shared_cpu_map);
	पूर्ण
	cpumask_copy(data->freqकरोमुख्य_cpus, perf->shared_cpu_map);

#अगर_घोषित CONFIG_SMP
	dmi_check_प्रणाली(sw_any_bug_dmi_table);
	अगर (bios_with_sw_any_bug && !policy_is_shared(policy)) अणु
		policy->shared_type = CPUFREQ_SHARED_TYPE_ALL;
		cpumask_copy(policy->cpus, topology_core_cpumask(cpu));
	पूर्ण

	अगर (check_amd_hwpstate_cpu(cpu) && boot_cpu_data.x86 < 0x19 &&
	    !acpi_pstate_strict) अणु
		cpumask_clear(policy->cpus);
		cpumask_set_cpu(cpu, policy->cpus);
		cpumask_copy(data->freqकरोमुख्य_cpus,
			     topology_sibling_cpumask(cpu));
		policy->shared_type = CPUFREQ_SHARED_TYPE_HW;
		pr_info_once("overriding BIOS provided _PSD data\n");
	पूर्ण
#पूर्ण_अगर

	/* capability check */
	अगर (perf->state_count <= 1) अणु
		pr_debug("No P-States\n");
		result = -ENODEV;
		जाओ err_unreg;
	पूर्ण

	अगर (perf->control_रेजिस्टर.space_id != perf->status_रेजिस्टर.space_id) अणु
		result = -ENODEV;
		जाओ err_unreg;
	पूर्ण

	चयन (perf->control_रेजिस्टर.space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD &&
		    boot_cpu_data.x86 == 0xf) अणु
			pr_debug("AMD K8 systems must use native drivers.\n");
			result = -ENODEV;
			जाओ err_unreg;
		पूर्ण
		pr_debug("SYSTEM IO addr space\n");
		data->cpu_feature = SYSTEM_IO_CAPABLE;
		data->cpu_freq_पढ़ो = cpu_freq_पढ़ो_io;
		data->cpu_freq_ग_लिखो = cpu_freq_ग_लिखो_io;
		अवरोध;
	हाल ACPI_ADR_SPACE_FIXED_HARDWARE:
		pr_debug("HARDWARE addr space\n");
		अगर (check_est_cpu(cpu)) अणु
			data->cpu_feature = SYSTEM_INTEL_MSR_CAPABLE;
			data->cpu_freq_पढ़ो = cpu_freq_पढ़ो_पूर्णांकel;
			data->cpu_freq_ग_लिखो = cpu_freq_ग_लिखो_पूर्णांकel;
			अवरोध;
		पूर्ण
		अगर (check_amd_hwpstate_cpu(cpu)) अणु
			data->cpu_feature = SYSTEM_AMD_MSR_CAPABLE;
			data->cpu_freq_पढ़ो = cpu_freq_पढ़ो_amd;
			data->cpu_freq_ग_लिखो = cpu_freq_ग_लिखो_amd;
			अवरोध;
		पूर्ण
		result = -ENODEV;
		जाओ err_unreg;
	शेष:
		pr_debug("Unknown addr space %d\n",
			(u32) (perf->control_रेजिस्टर.space_id));
		result = -ENODEV;
		जाओ err_unreg;
	पूर्ण

	freq_table = kसुस्मृति(perf->state_count + 1, माप(*freq_table),
			     GFP_KERNEL);
	अगर (!freq_table) अणु
		result = -ENOMEM;
		जाओ err_unreg;
	पूर्ण

	/* detect transition latency */
	policy->cpuinfo.transition_latency = 0;
	क्रम (i = 0; i < perf->state_count; i++) अणु
		अगर ((perf->states[i].transition_latency * 1000) >
		    policy->cpuinfo.transition_latency)
			policy->cpuinfo.transition_latency =
			    perf->states[i].transition_latency * 1000;
	पूर्ण

	/* Check क्रम high latency (>20uS) from buggy BIOSes, like on T42 */
	अगर (perf->control_रेजिस्टर.space_id == ACPI_ADR_SPACE_FIXED_HARDWARE &&
	    policy->cpuinfo.transition_latency > 20 * 1000) अणु
		policy->cpuinfo.transition_latency = 20 * 1000;
		pr_info_once("P-state transition latency capped at 20 uS\n");
	पूर्ण

	/* table init */
	क्रम (i = 0; i < perf->state_count; i++) अणु
		अगर (i > 0 && perf->states[i].core_frequency >=
		    freq_table[valid_states-1].frequency / 1000)
			जारी;

		freq_table[valid_states].driver_data = i;
		freq_table[valid_states].frequency =
		    perf->states[i].core_frequency * 1000;
		valid_states++;
	पूर्ण
	freq_table[valid_states].frequency = CPUFREQ_TABLE_END;

	max_boost_ratio = get_max_boost_ratio(cpu);
	अगर (max_boost_ratio) अणु
		अचिन्हित पूर्णांक freq = freq_table[0].frequency;

		/*
		 * Because the loop above sorts the freq_table entries in the
		 * descending order, freq is the maximum frequency in the table.
		 * Assume that it corresponds to the CPPC nominal frequency and
		 * use it to set cpuinfo.max_freq.
		 */
		policy->cpuinfo.max_freq = freq * max_boost_ratio >> SCHED_CAPACITY_SHIFT;
	पूर्ण अन्यथा अणु
		/*
		 * If the maximum "boost" frequency is unknown, ask the arch
		 * scale-invariance code to use the "nominal" perक्रमmance क्रम
		 * CPU utilization scaling so as to prevent the schedutil
		 * governor from selecting inadequate CPU frequencies.
		 */
		arch_set_max_freq_ratio(true);
	पूर्ण

	policy->freq_table = freq_table;
	perf->state = 0;

	चयन (perf->control_रेजिस्टर.space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		/*
		 * The core will not set policy->cur, because
		 * cpufreq_driver->get is शून्य, so we need to set it here.
		 * However, we have to guess it, because the current speed is
		 * unknown and not detectable via IO ports.
		 */
		policy->cur = acpi_cpufreq_guess_freq(data, policy->cpu);
		अवरोध;
	हाल ACPI_ADR_SPACE_FIXED_HARDWARE:
		acpi_cpufreq_driver.get = get_cur_freq_on_cpu;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* notअगरy BIOS that we exist */
	acpi_processor_notअगरy_smm(THIS_MODULE);

	pr_debug("CPU%u - ACPI performance management activated.\n", cpu);
	क्रम (i = 0; i < perf->state_count; i++)
		pr_debug("     %cP%d: %d MHz, %d mW, %d uS\n",
			(i == perf->state ? '*' : ' '), i,
			(u32) perf->states[i].core_frequency,
			(u32) perf->states[i].घातer,
			(u32) perf->states[i].transition_latency);

	/*
	 * the first call to ->target() should result in us actually
	 * writing something to the appropriate रेजिस्टरs.
	 */
	data->resume = 1;

	policy->fast_चयन_possible = !acpi_pstate_strict &&
		!(policy_is_shared(policy) && policy->shared_type != CPUFREQ_SHARED_TYPE_ANY);

	वापस result;

err_unreg:
	acpi_processor_unरेजिस्टर_perक्रमmance(cpu);
err_मुक्त_mask:
	मुक्त_cpumask_var(data->freqकरोमुख्य_cpus);
err_मुक्त:
	kमुक्त(data);
	policy->driver_data = शून्य;

	वापस result;
पूर्ण

अटल पूर्णांक acpi_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;

	pr_debug("%s\n", __func__);

	policy->fast_चयन_possible = false;
	policy->driver_data = शून्य;
	acpi_processor_unरेजिस्टर_perक्रमmance(data->acpi_perf_cpu);
	मुक्त_cpumask_var(data->freqकरोमुख्य_cpus);
	kमुक्त(policy->freq_table);
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल व्योम acpi_cpufreq_cpu_पढ़ोy(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा acpi_processor_perक्रमmance *perf = per_cpu_ptr(acpi_perf_data,
							      policy->cpu);
	अचिन्हित पूर्णांक freq = policy->freq_table[0].frequency;

	अगर (perf->states[0].core_frequency * 1000 != freq)
		pr_warn(FW_WARN "P-state 0 is not max freq\n");
पूर्ण

अटल पूर्णांक acpi_cpufreq_resume(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा acpi_cpufreq_data *data = policy->driver_data;

	pr_debug("%s\n", __func__);

	data->resume = 1;

	वापस 0;
पूर्ण

अटल काष्ठा freq_attr *acpi_cpufreq_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	&freqकरोमुख्य_cpus,
#अगर_घोषित CONFIG_X86_ACPI_CPUFREQ_CPB
	&cpb,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल काष्ठा cpufreq_driver acpi_cpufreq_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= acpi_cpufreq_target,
	.fast_चयन	= acpi_cpufreq_fast_चयन,
	.bios_limit	= acpi_processor_get_bios_limit,
	.init		= acpi_cpufreq_cpu_init,
	.निकास		= acpi_cpufreq_cpu_निकास,
	.पढ़ोy		= acpi_cpufreq_cpu_पढ़ोy,
	.resume		= acpi_cpufreq_resume,
	.name		= "acpi-cpufreq",
	.attr		= acpi_cpufreq_attr,
पूर्ण;

अटल क्रमागत cpuhp_state acpi_cpufreq_online;

अटल व्योम __init acpi_cpufreq_boost_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!(boot_cpu_has(X86_FEATURE_CPB) || boot_cpu_has(X86_FEATURE_IDA))) अणु
		pr_debug("Boost capabilities not present in the processor\n");
		वापस;
	पूर्ण

	acpi_cpufreq_driver.set_boost = set_boost;
	acpi_cpufreq_driver.boost_enabled = boost_state(0);

	/*
	 * This calls the online callback on all online cpu and क्रमces all
	 * MSRs to the same value.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "cpufreq/acpi:online",
				cpufreq_boost_online, cpufreq_boost_करोwn_prep);
	अगर (ret < 0) अणु
		pr_err("acpi_cpufreq: failed to register hotplug callbacks\n");
		वापस;
	पूर्ण
	acpi_cpufreq_online = ret;
पूर्ण

अटल व्योम acpi_cpufreq_boost_निकास(व्योम)
अणु
	अगर (acpi_cpufreq_online > 0)
		cpuhp_हटाओ_state_nocalls(acpi_cpufreq_online);
पूर्ण

अटल पूर्णांक __init acpi_cpufreq_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस -ENODEV;

	/* करोn't keep reloading अगर cpufreq_driver exists */
	अगर (cpufreq_get_current_driver())
		वापस -EEXIST;

	pr_debug("%s\n", __func__);

	ret = acpi_cpufreq_early_init();
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_X86_ACPI_CPUFREQ_CPB
	/* this is a sysfs file with a strange name and an even stranger
	 * semantic - per CPU instantiation, but प्रणाली global effect.
	 * Lets enable it only on AMD CPUs क्रम compatibility reasons and
	 * only अगर configured. This is considered legacy code, which
	 * will probably be हटाओd at some poपूर्णांक in the future.
	 */
	अगर (!check_amd_hwpstate_cpu(0)) अणु
		काष्ठा freq_attr **attr;

		pr_debug("CPB unsupported, do not expose it\n");

		क्रम (attr = acpi_cpufreq_attr; *attr; attr++)
			अगर (*attr == &cpb) अणु
				*attr = शून्य;
				अवरोध;
			पूर्ण
	पूर्ण
#पूर्ण_अगर
	acpi_cpufreq_boost_init();

	ret = cpufreq_रेजिस्टर_driver(&acpi_cpufreq_driver);
	अगर (ret) अणु
		मुक्त_acpi_perf_data();
		acpi_cpufreq_boost_निकास();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास acpi_cpufreq_निकास(व्योम)
अणु
	pr_debug("%s\n", __func__);

	acpi_cpufreq_boost_निकास();

	cpufreq_unरेजिस्टर_driver(&acpi_cpufreq_driver);

	मुक्त_acpi_perf_data();
पूर्ण

module_param(acpi_pstate_strict, uपूर्णांक, 0644);
MODULE_PARM_DESC(acpi_pstate_strict,
	"value 0 or non-zero. non-zero -> strict ACPI checks are "
	"performed during frequency changes.");

late_initcall(acpi_cpufreq_init);
module_निकास(acpi_cpufreq_निकास);

अटल स्थिर काष्ठा x86_cpu_id __maybe_unused acpi_cpufreq_ids[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_ACPI, शून्य),
	X86_MATCH_FEATURE(X86_FEATURE_HW_PSTATE, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, acpi_cpufreq_ids);

अटल स्थिर काष्ठा acpi_device_id __maybe_unused processor_device_ids[] = अणु
	अणुACPI_PROCESSOR_OBJECT_HID, पूर्ण,
	अणुACPI_PROCESSOR_DEVICE_HID, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, processor_device_ids);

MODULE_ALIAS("acpi");
