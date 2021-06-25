<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amd_freq_sensitivity.c: AMD frequency sensitivity feedback घातersave bias
 *                         क्रम the ondemand governor.
 *
 * Copyright (C) 2013 Advanced Micro Devices, Inc.
 *
 * Author: Jacob Shin <jacob.shin@amd.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpu_device_id.h>

#समावेश "cpufreq_ondemand.h"

#घोषणा MSR_AMD64_FREQ_SENSITIVITY_ACTUAL	0xc0010080
#घोषणा MSR_AMD64_FREQ_SENSITIVITY_REFERENCE	0xc0010081
#घोषणा CLASS_CODE_SHIFT			56
#घोषणा POWERSAVE_BIAS_MAX			1000
#घोषणा POWERSAVE_BIAS_DEF			400

काष्ठा cpu_data_t अणु
	u64 actual;
	u64 reference;
	अचिन्हित पूर्णांक freq_prev;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu_data_t, cpu_data);

अटल अचिन्हित पूर्णांक amd_घातersave_bias_target(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक freq_next,
					      अचिन्हित पूर्णांक relation)
अणु
	पूर्णांक sensitivity;
	दीर्घ d_actual, d_reference;
	काष्ठा msr actual, reference;
	काष्ठा cpu_data_t *data = &per_cpu(cpu_data, policy->cpu);
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *od_data = policy_dbs->dbs_data;
	काष्ठा od_dbs_tuners *od_tuners = od_data->tuners;

	अगर (!policy->freq_table)
		वापस freq_next;

	rdmsr_on_cpu(policy->cpu, MSR_AMD64_FREQ_SENSITIVITY_ACTUAL,
		&actual.l, &actual.h);
	rdmsr_on_cpu(policy->cpu, MSR_AMD64_FREQ_SENSITIVITY_REFERENCE,
		&reference.l, &reference.h);
	actual.h &= 0x00ffffff;
	reference.h &= 0x00ffffff;

	/* counter wrapped around, so stay on current frequency */
	अगर (actual.q < data->actual || reference.q < data->reference) अणु
		freq_next = policy->cur;
		जाओ out;
	पूर्ण

	d_actual = actual.q - data->actual;
	d_reference = reference.q - data->reference;

	/* भागide by 0, so stay on current frequency as well */
	अगर (d_reference == 0) अणु
		freq_next = policy->cur;
		जाओ out;
	पूर्ण

	sensitivity = POWERSAVE_BIAS_MAX -
		(POWERSAVE_BIAS_MAX * (d_reference - d_actual) / d_reference);

	clamp(sensitivity, 0, POWERSAVE_BIAS_MAX);

	/* this workload is not CPU bound, so choose a lower freq */
	अगर (sensitivity < od_tuners->घातersave_bias) अणु
		अगर (data->freq_prev == policy->cur)
			freq_next = policy->cur;

		अगर (freq_next > policy->cur)
			freq_next = policy->cur;
		अन्यथा अगर (freq_next < policy->cur)
			freq_next = policy->min;
		अन्यथा अणु
			अचिन्हित पूर्णांक index;

			index = cpufreq_table_find_index_h(policy,
							   policy->cur - 1);
			freq_next = policy->freq_table[index].frequency;
		पूर्ण

		data->freq_prev = freq_next;
	पूर्ण अन्यथा
		data->freq_prev = 0;

out:
	data->actual = actual.q;
	data->reference = reference.q;
	वापस freq_next;
पूर्ण

अटल पूर्णांक __init amd_freq_sensitivity_init(व्योम)
अणु
	u64 val;
	काष्ठा pci_dev *pcidev;
	अचिन्हित पूर्णांक pci_venकरोr;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		pci_venकरोr = PCI_VENDOR_ID_AMD;
	अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		pci_venकरोr = PCI_VENDOR_ID_HYGON;
	अन्यथा
		वापस -ENODEV;

	pcidev = pci_get_device(pci_venकरोr,
			PCI_DEVICE_ID_AMD_KERNCZ_SMBUS, शून्य);

	अगर (!pcidev) अणु
		अगर (!boot_cpu_has(X86_FEATURE_PROC_FEEDBACK))
			वापस -ENODEV;
	पूर्ण

	अगर (rdmsrl_safe(MSR_AMD64_FREQ_SENSITIVITY_ACTUAL, &val))
		वापस -ENODEV;

	अगर (!(val >> CLASS_CODE_SHIFT))
		वापस -ENODEV;

	od_रेजिस्टर_घातersave_bias_handler(amd_घातersave_bias_target,
			POWERSAVE_BIAS_DEF);
	वापस 0;
पूर्ण
late_initcall(amd_freq_sensitivity_init);

अटल व्योम __निकास amd_freq_sensitivity_निकास(व्योम)
अणु
	od_unरेजिस्टर_घातersave_bias_handler();
पूर्ण
module_निकास(amd_freq_sensitivity_निकास);

अटल स्थिर काष्ठा x86_cpu_id __maybe_unused amd_freq_sensitivity_ids[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_PROC_FEEDBACK, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, amd_freq_sensitivity_ids);

MODULE_AUTHOR("Jacob Shin <jacob.shin@amd.com>");
MODULE_DESCRIPTION("AMD frequency sensitivity feedback powersave bias for "
		"the ondemand governor.");
MODULE_LICENSE("GPL");
