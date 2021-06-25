<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPPC (Collaborative Processor Perक्रमmance Control) driver क्रम
 * पूर्णांकerfacing with the CPUfreq layer and governors. See
 * cppc_acpi.c क्रम CPPC specअगरic methods.
 *
 * (C) Copyright 2014, 2015 Linaro Ltd.
 * Author: Ashwin Chaugule <ashwin.chaugule@linaro.org>
 */

#घोषणा pr_fmt(fmt)	"CPPC Cpufreq:"	fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/dmi.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <acpi/cppc_acpi.h>

/* Minimum काष्ठा length needed क्रम the DMI processor entry we want */
#घोषणा DMI_ENTRY_PROCESSOR_MIN_LENGTH	48

/* Offset in the DMI processor काष्ठाure क्रम the max frequency */
#घोषणा DMI_PROCESSOR_MAX_SPEED		0x14

/*
 * This list contains inक्रमmation parsed from per CPU ACPI _CPC and _PSD
 * काष्ठाures: e.g. the highest and lowest supported perक्रमmance, capabilities,
 * desired perक्रमmance, level requested etc. Depending on the share_type, not
 * all CPUs will have an entry in the list.
 */
अटल LIST_HEAD(cpu_data_list);

अटल bool boost_supported;

काष्ठा cppc_workaround_oem_info अणु
	अक्षर oem_id[ACPI_OEM_ID_SIZE + 1];
	अक्षर oem_table_id[ACPI_OEM_TABLE_ID_SIZE + 1];
	u32 oem_revision;
पूर्ण;

अटल काष्ठा cppc_workaround_oem_info wa_info[] = अणु
	अणु
		.oem_id		= "HISI  ",
		.oem_table_id	= "HIP07   ",
		.oem_revision	= 0,
	पूर्ण, अणु
		.oem_id		= "HISI  ",
		.oem_table_id	= "HIP08   ",
		.oem_revision	= 0,
	पूर्ण
पूर्ण;

/* Callback function used to retrieve the max frequency from DMI */
अटल व्योम cppc_find_dmi_mhz(स्थिर काष्ठा dmi_header *dm, व्योम *निजी)
अणु
	स्थिर u8 *dmi_data = (स्थिर u8 *)dm;
	u16 *mhz = (u16 *)निजी;

	अगर (dm->type == DMI_ENTRY_PROCESSOR &&
	    dm->length >= DMI_ENTRY_PROCESSOR_MIN_LENGTH) अणु
		u16 val = (u16)get_unaligned((स्थिर u16 *)
				(dmi_data + DMI_PROCESSOR_MAX_SPEED));
		*mhz = val > *mhz ? val : *mhz;
	पूर्ण
पूर्ण

/* Look up the max frequency in DMI */
अटल u64 cppc_get_dmi_max_khz(व्योम)
अणु
	u16 mhz = 0;

	dmi_walk(cppc_find_dmi_mhz, &mhz);

	/*
	 * Real stupid fallback value, just in हाल there is no
	 * actual value set.
	 */
	mhz = mhz ? mhz : 1;

	वापस (1000 * mhz);
पूर्ण

/*
 * If CPPC lowest_freq and nominal_freq रेजिस्टरs are exposed then we can
 * use them to convert perf to freq and vice versa
 *
 * If the perf/freq poपूर्णांक lies between Nominal and Lowest, we can treat
 * (Low perf, Low freq) and (Nom Perf, Nom freq) as 2D co-ordinates of a line
 * and extrapolate the rest
 * For perf/freq > Nominal, we use the ratio perf:freq at Nominal क्रम conversion
 */
अटल अचिन्हित पूर्णांक cppc_cpufreq_perf_to_khz(काष्ठा cppc_cpudata *cpu_data,
					     अचिन्हित पूर्णांक perf)
अणु
	काष्ठा cppc_perf_caps *caps = &cpu_data->perf_caps;
	अटल u64 max_khz;
	u64 mul, भाग;

	अगर (caps->lowest_freq && caps->nominal_freq) अणु
		अगर (perf >= caps->nominal_perf) अणु
			mul = caps->nominal_freq;
			भाग = caps->nominal_perf;
		पूर्ण अन्यथा अणु
			mul = caps->nominal_freq - caps->lowest_freq;
			भाग = caps->nominal_perf - caps->lowest_perf;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		mul = max_khz;
		भाग = caps->highest_perf;
	पूर्ण
	वापस (u64)perf * mul / भाग;
पूर्ण

अटल अचिन्हित पूर्णांक cppc_cpufreq_khz_to_perf(काष्ठा cppc_cpudata *cpu_data,
					     अचिन्हित पूर्णांक freq)
अणु
	काष्ठा cppc_perf_caps *caps = &cpu_data->perf_caps;
	अटल u64 max_khz;
	u64  mul, भाग;

	अगर (caps->lowest_freq && caps->nominal_freq) अणु
		अगर (freq >= caps->nominal_freq) अणु
			mul = caps->nominal_perf;
			भाग = caps->nominal_freq;
		पूर्ण अन्यथा अणु
			mul = caps->lowest_perf;
			भाग = caps->lowest_freq;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		mul = caps->highest_perf;
		भाग = max_khz;
	पूर्ण

	वापस (u64)freq * mul / भाग;
पूर्ण

अटल पूर्णांक cppc_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				   अचिन्हित पूर्णांक target_freq,
				   अचिन्हित पूर्णांक relation)

अणु
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा cpufreq_freqs freqs;
	u32 desired_perf;
	पूर्णांक ret = 0;

	desired_perf = cppc_cpufreq_khz_to_perf(cpu_data, target_freq);
	/* Return अगर it is exactly the same perf */
	अगर (desired_perf == cpu_data->perf_ctrls.desired_perf)
		वापस ret;

	cpu_data->perf_ctrls.desired_perf = desired_perf;
	freqs.old = policy->cur;
	freqs.new = target_freq;

	cpufreq_freq_transition_begin(policy, &freqs);
	ret = cppc_set_perf(cpu, &cpu_data->perf_ctrls);
	cpufreq_freq_transition_end(policy, &freqs, ret != 0);

	अगर (ret)
		pr_debug("Failed to set target on CPU:%d. ret:%d\n",
			 cpu, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cppc_verअगरy_policy(काष्ठा cpufreq_policy_data *policy)
अणु
	cpufreq_verअगरy_within_cpu_limits(policy);
	वापस 0;
पूर्ण

अटल व्योम cppc_cpufreq_stop_cpu(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;
	काष्ठा cppc_perf_caps *caps = &cpu_data->perf_caps;
	अचिन्हित पूर्णांक cpu = policy->cpu;
	पूर्णांक ret;

	cpu_data->perf_ctrls.desired_perf = caps->lowest_perf;

	ret = cppc_set_perf(cpu, &cpu_data->perf_ctrls);
	अगर (ret)
		pr_debug("Err setting perf value:%d on CPU:%d. ret:%d\n",
			 caps->lowest_perf, cpu, ret);

	/* Remove CPU node from list and मुक्त driver data क्रम policy */
	मुक्त_cpumask_var(cpu_data->shared_cpu_map);
	list_del(&cpu_data->node);
	kमुक्त(policy->driver_data);
	policy->driver_data = शून्य;
पूर्ण

/*
 * The PCC subspace describes the rate at which platक्रमm can accept commands
 * on the shared PCC channel (including READs which करो not count towards freq
 * transition requests), so ideally we need to use the PCC values as a fallback
 * अगर we करोn't have a platक्रमm specअगरic transition_delay_us
 */
#अगर_घोषित CONFIG_ARM64
#समावेश <यंत्र/cputype.h>

अटल अचिन्हित पूर्णांक cppc_cpufreq_get_transition_delay_us(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ implementor = पढ़ो_cpuid_implementor();
	अचिन्हित दीर्घ part_num = पढ़ो_cpuid_part_number();

	चयन (implementor) अणु
	हाल ARM_CPU_IMP_QCOM:
		चयन (part_num) अणु
		हाल QCOM_CPU_PART_FALKOR_V1:
		हाल QCOM_CPU_PART_FALKOR:
			वापस 10000;
		पूर्ण
	पूर्ण
	वापस cppc_get_transition_latency(cpu) / NSEC_PER_USEC;
पूर्ण

#अन्यथा

अटल अचिन्हित पूर्णांक cppc_cpufreq_get_transition_delay_us(अचिन्हित पूर्णांक cpu)
अणु
	वापस cppc_get_transition_latency(cpu) / NSEC_PER_USEC;
पूर्ण
#पूर्ण_अगर


अटल काष्ठा cppc_cpudata *cppc_cpufreq_get_cpu_data(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cppc_cpudata *cpu_data;
	पूर्णांक ret;

	cpu_data = kzalloc(माप(काष्ठा cppc_cpudata), GFP_KERNEL);
	अगर (!cpu_data)
		जाओ out;

	अगर (!zalloc_cpumask_var(&cpu_data->shared_cpu_map, GFP_KERNEL))
		जाओ मुक्त_cpu;

	ret = acpi_get_psd_map(cpu, cpu_data);
	अगर (ret) अणु
		pr_debug("Err parsing CPU%d PSD data: ret:%d\n", cpu, ret);
		जाओ मुक्त_mask;
	पूर्ण

	ret = cppc_get_perf_caps(cpu, &cpu_data->perf_caps);
	अगर (ret) अणु
		pr_debug("Err reading CPU%d perf caps: ret:%d\n", cpu, ret);
		जाओ मुक्त_mask;
	पूर्ण

	/* Convert the lowest and nominal freq from MHz to KHz */
	cpu_data->perf_caps.lowest_freq *= 1000;
	cpu_data->perf_caps.nominal_freq *= 1000;

	list_add(&cpu_data->node, &cpu_data_list);

	वापस cpu_data;

मुक्त_mask:
	मुक्त_cpumask_var(cpu_data->shared_cpu_map);
मुक्त_cpu:
	kमुक्त(cpu_data);
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक cppc_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा cppc_cpudata *cpu_data;
	काष्ठा cppc_perf_caps *caps;
	पूर्णांक ret;

	cpu_data = cppc_cpufreq_get_cpu_data(cpu);
	अगर (!cpu_data) अणु
		pr_err("Error in acquiring _CPC/_PSD data for CPU%d.\n", cpu);
		वापस -ENODEV;
	पूर्ण
	caps = &cpu_data->perf_caps;
	policy->driver_data = cpu_data;

	/*
	 * Set min to lowest nonlinear perf to aव्योम any efficiency penalty (see
	 * Section 8.4.7.1.1.5 of ACPI 6.1 spec)
	 */
	policy->min = cppc_cpufreq_perf_to_khz(cpu_data,
					       caps->lowest_nonlinear_perf);
	policy->max = cppc_cpufreq_perf_to_khz(cpu_data,
					       caps->nominal_perf);

	/*
	 * Set cpuinfo.min_freq to Lowest to make the full range of perक्रमmance
	 * available अगर userspace wants to use any perf between lowest & lowest
	 * nonlinear perf
	 */
	policy->cpuinfo.min_freq = cppc_cpufreq_perf_to_khz(cpu_data,
							    caps->lowest_perf);
	policy->cpuinfo.max_freq = cppc_cpufreq_perf_to_khz(cpu_data,
							    caps->nominal_perf);

	policy->transition_delay_us = cppc_cpufreq_get_transition_delay_us(cpu);
	policy->shared_type = cpu_data->shared_type;

	चयन (policy->shared_type) अणु
	हाल CPUFREQ_SHARED_TYPE_HW:
	हाल CPUFREQ_SHARED_TYPE_NONE:
		/* Nothing to be करोne - we'll have a policy क्रम each CPU */
		अवरोध;
	हाल CPUFREQ_SHARED_TYPE_ANY:
		/*
		 * All CPUs in the करोमुख्य will share a policy and all cpufreq
		 * operations will use a single cppc_cpudata काष्ठाure stored
		 * in policy->driver_data.
		 */
		cpumask_copy(policy->cpus, cpu_data->shared_cpu_map);
		अवरोध;
	शेष:
		pr_debug("Unsupported CPU co-ord type: %d\n",
			 policy->shared_type);
		वापस -EFAULT;
	पूर्ण

	/*
	 * If 'highest_perf' is greater than 'nominal_perf', we assume CPU Boost
	 * is supported.
	 */
	अगर (caps->highest_perf > caps->nominal_perf)
		boost_supported = true;

	/* Set policy->cur to max now. The governors will adjust later. */
	policy->cur = cppc_cpufreq_perf_to_khz(cpu_data, caps->highest_perf);
	cpu_data->perf_ctrls.desired_perf =  caps->highest_perf;

	ret = cppc_set_perf(cpu, &cpu_data->perf_ctrls);
	अगर (ret)
		pr_debug("Err setting perf value:%d on CPU:%d. ret:%d\n",
			 caps->highest_perf, cpu, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत u64 get_delta(u64 t1, u64 t0)
अणु
	अगर (t1 > t0 || t0 > ~(u32)0)
		वापस t1 - t0;

	वापस (u32)t1 - (u32)t0;
पूर्ण

अटल पूर्णांक cppc_get_rate_from_fbctrs(काष्ठा cppc_cpudata *cpu_data,
				     काष्ठा cppc_perf_fb_ctrs fb_ctrs_t0,
				     काष्ठा cppc_perf_fb_ctrs fb_ctrs_t1)
अणु
	u64 delta_reference, delta_delivered;
	u64 reference_perf, delivered_perf;

	reference_perf = fb_ctrs_t0.reference_perf;

	delta_reference = get_delta(fb_ctrs_t1.reference,
				    fb_ctrs_t0.reference);
	delta_delivered = get_delta(fb_ctrs_t1.delivered,
				    fb_ctrs_t0.delivered);

	/* Check to aव्योम भागide-by zero */
	अगर (delta_reference || delta_delivered)
		delivered_perf = (reference_perf * delta_delivered) /
					delta_reference;
	अन्यथा
		delivered_perf = cpu_data->perf_ctrls.desired_perf;

	वापस cppc_cpufreq_perf_to_khz(cpu_data, delivered_perf);
पूर्ण

अटल अचिन्हित पूर्णांक cppc_cpufreq_get_rate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cppc_perf_fb_ctrs fb_ctrs_t0 = अणु0पूर्ण, fb_ctrs_t1 = अणु0पूर्ण;
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;
	पूर्णांक ret;

	cpufreq_cpu_put(policy);

	ret = cppc_get_perf_ctrs(cpu, &fb_ctrs_t0);
	अगर (ret)
		वापस ret;

	udelay(2); /* 2usec delay between sampling */

	ret = cppc_get_perf_ctrs(cpu, &fb_ctrs_t1);
	अगर (ret)
		वापस ret;

	वापस cppc_get_rate_from_fbctrs(cpu_data, fb_ctrs_t0, fb_ctrs_t1);
पूर्ण

अटल पूर्णांक cppc_cpufreq_set_boost(काष्ठा cpufreq_policy *policy, पूर्णांक state)
अणु
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;
	काष्ठा cppc_perf_caps *caps = &cpu_data->perf_caps;
	पूर्णांक ret;

	अगर (!boost_supported) अणु
		pr_err("BOOST not supported by CPU or firmware\n");
		वापस -EINVAL;
	पूर्ण

	अगर (state)
		policy->max = cppc_cpufreq_perf_to_khz(cpu_data,
						       caps->highest_perf);
	अन्यथा
		policy->max = cppc_cpufreq_perf_to_khz(cpu_data,
						       caps->nominal_perf);
	policy->cpuinfo.max_freq = policy->max;

	ret = freq_qos_update_request(policy->max_freq_req, policy->max);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_freqकरोमुख्य_cpus(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;

	वापस cpufreq_show_cpus(cpu_data->shared_cpu_map, buf);
पूर्ण
cpufreq_freq_attr_ro(freqकरोमुख्य_cpus);

अटल काष्ठा freq_attr *cppc_cpufreq_attr[] = अणु
	&freqकरोमुख्य_cpus,
	शून्य,
पूर्ण;

अटल काष्ठा cpufreq_driver cppc_cpufreq_driver = अणु
	.flags = CPUFREQ_CONST_LOOPS,
	.verअगरy = cppc_verअगरy_policy,
	.target = cppc_cpufreq_set_target,
	.get = cppc_cpufreq_get_rate,
	.init = cppc_cpufreq_cpu_init,
	.stop_cpu = cppc_cpufreq_stop_cpu,
	.set_boost = cppc_cpufreq_set_boost,
	.attr = cppc_cpufreq_attr,
	.name = "cppc_cpufreq",
पूर्ण;

/*
 * HISI platक्रमm करोes not support delivered perक्रमmance counter and
 * reference perक्रमmance counter. It can calculate the perक्रमmance using the
 * platक्रमm specअगरic mechanism. We reuse the desired perक्रमmance रेजिस्टर to
 * store the real perक्रमmance calculated by the platक्रमm.
 */
अटल अचिन्हित पूर्णांक hisi_cppc_cpufreq_get_rate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	काष्ठा cppc_cpudata *cpu_data = policy->driver_data;
	u64 desired_perf;
	पूर्णांक ret;

	cpufreq_cpu_put(policy);

	ret = cppc_get_desired_perf(cpu, &desired_perf);
	अगर (ret < 0)
		वापस -EIO;

	वापस cppc_cpufreq_perf_to_khz(cpu_data, desired_perf);
पूर्ण

अटल व्योम cppc_check_hisi_workaround(व्योम)
अणु
	काष्ठा acpi_table_header *tbl;
	acpi_status status = AE_OK;
	पूर्णांक i;

	status = acpi_get_table(ACPI_SIG_PCCT, 0, &tbl);
	अगर (ACPI_FAILURE(status) || !tbl)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(wa_info); i++) अणु
		अगर (!स_भेद(wa_info[i].oem_id, tbl->oem_id, ACPI_OEM_ID_SIZE) &&
		    !स_भेद(wa_info[i].oem_table_id, tbl->oem_table_id, ACPI_OEM_TABLE_ID_SIZE) &&
		    wa_info[i].oem_revision == tbl->oem_revision) अणु
			/* Overग_लिखो the get() callback */
			cppc_cpufreq_driver.get = hisi_cppc_cpufreq_get_rate;
			अवरोध;
		पूर्ण
	पूर्ण

	acpi_put_table(tbl);
पूर्ण

अटल पूर्णांक __init cppc_cpufreq_init(व्योम)
अणु
	अगर ((acpi_disabled) || !acpi_cpc_valid())
		वापस -ENODEV;

	INIT_LIST_HEAD(&cpu_data_list);

	cppc_check_hisi_workaround();

	वापस cpufreq_रेजिस्टर_driver(&cppc_cpufreq_driver);
पूर्ण

अटल अंतरभूत व्योम मुक्त_cpu_data(व्योम)
अणु
	काष्ठा cppc_cpudata *iter, *पंचांगp;

	list_क्रम_each_entry_safe(iter, पंचांगp, &cpu_data_list, node) अणु
		मुक्त_cpumask_var(iter->shared_cpu_map);
		list_del(&iter->node);
		kमुक्त(iter);
	पूर्ण

पूर्ण

अटल व्योम __निकास cppc_cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&cppc_cpufreq_driver);

	मुक्त_cpu_data();
पूर्ण

module_निकास(cppc_cpufreq_निकास);
MODULE_AUTHOR("Ashwin Chaugule");
MODULE_DESCRIPTION("CPUFreq driver based on the ACPI CPPC v5.0+ spec");
MODULE_LICENSE("GPL");

late_initcall(cppc_cpufreq_init);

अटल स्थिर काष्ठा acpi_device_id cppc_acpi_ids[] __used = अणु
	अणुACPI_PROCESSOR_DEVICE_HID, पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, cppc_acpi_ids);
