<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Based on करोcumentation provided by Dave Jones. Thanks!
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/tsc.h>

#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#पूर्ण_अगर

#घोषणा EPS_BRAND_C7M	0
#घोषणा EPS_BRAND_C7	1
#घोषणा EPS_BRAND_EDEN	2
#घोषणा EPS_BRAND_C3	3
#घोषणा EPS_BRAND_C7D	4

काष्ठा eps_cpu_data अणु
	u32 fsb;
#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
	u32 bios_limit;
#पूर्ण_अगर
	काष्ठा cpufreq_frequency_table freq_table[];
पूर्ण;

अटल काष्ठा eps_cpu_data *eps_cpu[NR_CPUS];

/* Module parameters */
अटल पूर्णांक freq_failsafe_off;
अटल पूर्णांक voltage_failsafe_off;
अटल पूर्णांक set_max_voltage;

#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
अटल पूर्णांक ignore_acpi_limit;

अटल काष्ठा acpi_processor_perक्रमmance *eps_acpi_cpu_perf;

/* Minimum necessary to get acpi_processor_get_bios_limit() working */
अटल पूर्णांक eps_acpi_init(व्योम)
अणु
	eps_acpi_cpu_perf = kzalloc(माप(*eps_acpi_cpu_perf),
				      GFP_KERNEL);
	अगर (!eps_acpi_cpu_perf)
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(&eps_acpi_cpu_perf->shared_cpu_map,
								GFP_KERNEL)) अणु
		kमुक्त(eps_acpi_cpu_perf);
		eps_acpi_cpu_perf = शून्य;
		वापस -ENOMEM;
	पूर्ण

	अगर (acpi_processor_रेजिस्टर_perक्रमmance(eps_acpi_cpu_perf, 0)) अणु
		मुक्त_cpumask_var(eps_acpi_cpu_perf->shared_cpu_map);
		kमुक्त(eps_acpi_cpu_perf);
		eps_acpi_cpu_perf = शून्य;
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक eps_acpi_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अगर (eps_acpi_cpu_perf) अणु
		acpi_processor_unरेजिस्टर_perक्रमmance(0);
		मुक्त_cpumask_var(eps_acpi_cpu_perf->shared_cpu_map);
		kमुक्त(eps_acpi_cpu_perf);
		eps_acpi_cpu_perf = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक eps_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा eps_cpu_data *centaur;
	u32 lo, hi;

	अगर (cpu)
		वापस 0;
	centaur = eps_cpu[cpu];
	अगर (centaur == शून्य)
		वापस 0;

	/* Return current frequency */
	rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
	वापस centaur->fsb * ((lo >> 8) & 0xff);
पूर्ण

अटल पूर्णांक eps_set_state(काष्ठा eps_cpu_data *centaur,
			 काष्ठा cpufreq_policy *policy,
			 u32 dest_state)
अणु
	u32 lo, hi;
	पूर्णांक i;

	/* Wait जबतक CPU is busy */
	rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
	i = 0;
	जबतक (lo & ((1 << 16) | (1 << 17))) अणु
		udelay(16);
		rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
		i++;
		अगर (unlikely(i > 64)) अणु
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	/* Set new multiplier and voltage */
	wrmsr(MSR_IA32_PERF_CTL, dest_state & 0xffff, 0);
	/* Wait until transition end */
	i = 0;
	करो अणु
		udelay(16);
		rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
		i++;
		अगर (unlikely(i > 64)) अणु
			वापस -ENODEV;
		पूर्ण
	पूर्ण जबतक (lo & ((1 << 16) | (1 << 17)));

#अगर_घोषित DEBUG
	अणु
	u8 current_multiplier, current_voltage;

	/* Prपूर्णांक voltage and multiplier */
	rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
	current_voltage = lo & 0xff;
	pr_info("Current voltage = %dmV\n", current_voltage * 16 + 700);
	current_multiplier = (lo >> 8) & 0xff;
	pr_info("Current multiplier = %d\n", current_multiplier);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक eps_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	काष्ठा eps_cpu_data *centaur;
	अचिन्हित पूर्णांक cpu = policy->cpu;
	अचिन्हित पूर्णांक dest_state;
	पूर्णांक ret;

	अगर (unlikely(eps_cpu[cpu] == शून्य))
		वापस -ENODEV;
	centaur = eps_cpu[cpu];

	/* Make frequency transition */
	dest_state = centaur->freq_table[index].driver_data & 0xffff;
	ret = eps_set_state(centaur, policy, dest_state);
	अगर (ret)
		pr_err("Timeout!\n");
	वापस ret;
पूर्ण

अटल पूर्णांक eps_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक i;
	u32 lo, hi;
	u64 val;
	u8 current_multiplier, current_voltage;
	u8 max_multiplier, max_voltage;
	u8 min_multiplier, min_voltage;
	u8 bअक्रम = 0;
	u32 fsb;
	काष्ठा eps_cpu_data *centaur;
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	काष्ठा cpufreq_frequency_table *f_table;
	पूर्णांक k, step, voltage;
	पूर्णांक states;
#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
	अचिन्हित पूर्णांक limit;
#पूर्ण_अगर

	अगर (policy->cpu != 0)
		वापस -ENODEV;

	/* Check bअक्रम */
	pr_info("Detected VIA ");

	चयन (c->x86_model) अणु
	हाल 10:
		rdmsr(0x1153, lo, hi);
		bअक्रम = (((lo >> 2) ^ lo) >> 18) & 3;
		pr_cont("Model A ");
		अवरोध;
	हाल 13:
		rdmsr(0x1154, lo, hi);
		bअक्रम = (((lo >> 4) ^ (lo >> 2))) & 0x000000ff;
		pr_cont("Model D ");
		अवरोध;
	पूर्ण

	चयन (bअक्रम) अणु
	हाल EPS_BRAND_C7M:
		pr_cont("C7-M\n");
		अवरोध;
	हाल EPS_BRAND_C7:
		pr_cont("C7\n");
		अवरोध;
	हाल EPS_BRAND_EDEN:
		pr_cont("Eden\n");
		अवरोध;
	हाल EPS_BRAND_C7D:
		pr_cont("C7-D\n");
		अवरोध;
	हाल EPS_BRAND_C3:
		pr_cont("C3\n");
		वापस -ENODEV;
	पूर्ण
	/* Enable Enhanced PowerSaver */
	rdmsrl(MSR_IA32_MISC_ENABLE, val);
	अगर (!(val & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP)) अणु
		val |= MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP;
		wrmsrl(MSR_IA32_MISC_ENABLE, val);
		/* Can be locked at 0 */
		rdmsrl(MSR_IA32_MISC_ENABLE, val);
		अगर (!(val & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP)) अणु
			pr_info("Can't enable Enhanced PowerSaver\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Prपूर्णांक voltage and multiplier */
	rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
	current_voltage = lo & 0xff;
	pr_info("Current voltage = %dmV\n", current_voltage * 16 + 700);
	current_multiplier = (lo >> 8) & 0xff;
	pr_info("Current multiplier = %d\n", current_multiplier);

	/* Prपूर्णांक limits */
	max_voltage = hi & 0xff;
	pr_info("Highest voltage = %dmV\n", max_voltage * 16 + 700);
	max_multiplier = (hi >> 8) & 0xff;
	pr_info("Highest multiplier = %d\n", max_multiplier);
	min_voltage = (hi >> 16) & 0xff;
	pr_info("Lowest voltage = %dmV\n", min_voltage * 16 + 700);
	min_multiplier = (hi >> 24) & 0xff;
	pr_info("Lowest multiplier = %d\n", min_multiplier);

	/* Sanity checks */
	अगर (current_multiplier == 0 || max_multiplier == 0
	    || min_multiplier == 0)
		वापस -EINVAL;
	अगर (current_multiplier > max_multiplier
	    || max_multiplier <= min_multiplier)
		वापस -EINVAL;
	अगर (current_voltage > 0x1f || max_voltage > 0x1f)
		वापस -EINVAL;
	अगर (max_voltage < min_voltage
	    || current_voltage < min_voltage
	    || current_voltage > max_voltage)
		वापस -EINVAL;

	/* Check क्रम प्रणालीs using underघड़ीed CPU */
	अगर (!freq_failsafe_off && max_multiplier != current_multiplier) अणु
		pr_info("Your processor is running at different frequency then its maximum. Aborting.\n");
		pr_info("You can use freq_failsafe_off option to disable this check.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!voltage_failsafe_off && max_voltage != current_voltage) अणु
		pr_info("Your processor is running at different voltage then its maximum. Aborting.\n");
		pr_info("You can use voltage_failsafe_off option to disable this check.\n");
		वापस -EINVAL;
	पूर्ण

	/* Calc FSB speed */
	fsb = cpu_khz / current_multiplier;

#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
	/* Check क्रम ACPI processor speed limit */
	अगर (!ignore_acpi_limit && !eps_acpi_init()) अणु
		अगर (!acpi_processor_get_bios_limit(policy->cpu, &limit)) अणु
			pr_info("ACPI limit %u.%uGHz\n",
				limit/1000000,
				(limit%1000000)/10000);
			eps_acpi_निकास(policy);
			/* Check अगर max_multiplier is in BIOS limits */
			अगर (limit && max_multiplier * fsb > limit) अणु
				pr_info("Aborting\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Allow user to set lower maximum voltage then that reported
	 * by processor */
	अगर (bअक्रम == EPS_BRAND_C7M && set_max_voltage) अणु
		u32 v;

		/* Change mV to something hardware can use */
		v = (set_max_voltage - 700) / 16;
		/* Check अगर voltage is within limits */
		अगर (v >= min_voltage && v <= max_voltage) अणु
			pr_info("Setting %dmV as maximum\n", v * 16 + 700);
			max_voltage = v;
		पूर्ण
	पूर्ण

	/* Calc number of p-states supported */
	अगर (bअक्रम == EPS_BRAND_C7M)
		states = max_multiplier - min_multiplier + 1;
	अन्यथा
		states = 2;

	/* Allocate निजी data and frequency table क्रम current cpu */
	centaur = kzalloc(काष्ठा_size(centaur, freq_table, states + 1),
			  GFP_KERNEL);
	अगर (!centaur)
		वापस -ENOMEM;
	eps_cpu[0] = centaur;

	/* Copy basic values */
	centaur->fsb = fsb;
#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
	centaur->bios_limit = limit;
#पूर्ण_अगर

	/* Fill frequency and MSR value table */
	f_table = &centaur->freq_table[0];
	अगर (bअक्रम != EPS_BRAND_C7M) अणु
		f_table[0].frequency = fsb * min_multiplier;
		f_table[0].driver_data = (min_multiplier << 8) | min_voltage;
		f_table[1].frequency = fsb * max_multiplier;
		f_table[1].driver_data = (max_multiplier << 8) | max_voltage;
		f_table[2].frequency = CPUFREQ_TABLE_END;
	पूर्ण अन्यथा अणु
		k = 0;
		step = ((max_voltage - min_voltage) * 256)
			/ (max_multiplier - min_multiplier);
		क्रम (i = min_multiplier; i <= max_multiplier; i++) अणु
			voltage = (k * step) / 256 + min_voltage;
			f_table[k].frequency = fsb * i;
			f_table[k].driver_data = (i << 8) | voltage;
			k++;
		पूर्ण
		f_table[k].frequency = CPUFREQ_TABLE_END;
	पूर्ण

	policy->cpuinfo.transition_latency = 140000; /* 844mV -> 700mV in ns */
	policy->freq_table = &centaur->freq_table[0];

	वापस 0;
पूर्ण

अटल पूर्णांक eps_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;

	/* Bye */
	kमुक्त(eps_cpu[cpu]);
	eps_cpu[cpu] = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver eps_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= eps_target,
	.init		= eps_cpu_init,
	.निकास		= eps_cpu_निकास,
	.get		= eps_get,
	.name		= "e_powersaver",
	.attr		= cpufreq_generic_attr,
पूर्ण;


/* This driver will work only on Centaur C7 processors with
 * Enhanced SpeedStep/PowerSaver रेजिस्टरs */
अटल स्थिर काष्ठा x86_cpu_id eps_cpu_id[] = अणु
	X86_MATCH_VENDOR_FAM_FEATURE(CENTAUR, 6, X86_FEATURE_EST, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, eps_cpu_id);

अटल पूर्णांक __init eps_init(व्योम)
अणु
	अगर (!x86_match_cpu(eps_cpu_id) || boot_cpu_data.x86_model < 10)
		वापस -ENODEV;
	अगर (cpufreq_रेजिस्टर_driver(&eps_driver))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम __निकास eps_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&eps_driver);
पूर्ण

/* Allow user to overघड़ी his machine or to change frequency to higher after
 * unloading module */
module_param(freq_failsafe_off, पूर्णांक, 0644);
MODULE_PARM_DESC(freq_failsafe_off, "Disable current vs max frequency check");
module_param(voltage_failsafe_off, पूर्णांक, 0644);
MODULE_PARM_DESC(voltage_failsafe_off, "Disable current vs max voltage check");
#अगर IS_ENABLED(CONFIG_ACPI_PROCESSOR)
module_param(ignore_acpi_limit, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_acpi_limit, "Don't check ACPI's processor speed limit");
#पूर्ण_अगर
module_param(set_max_voltage, पूर्णांक, 0644);
MODULE_PARM_DESC(set_max_voltage, "Set maximum CPU voltage (mV) C7-M only");

MODULE_AUTHOR("Rafal Bilski <rafalbilski@interia.pl>");
MODULE_DESCRIPTION("Enhanced PowerSaver driver for VIA C7 CPU's.");
MODULE_LICENSE("GPL");

module_init(eps_init);
module_निकास(eps_निकास);
