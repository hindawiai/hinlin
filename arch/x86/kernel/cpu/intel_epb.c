<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Perक्रमmance and Energy Bias Hपूर्णांक support.
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * Author:
 *	Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/msr.h>

/**
 * DOC: overview
 *
 * The Perक्रमmance and Energy Bias Hपूर्णांक (EPB) allows software to specअगरy its
 * preference with respect to the घातer-perक्रमmance tradeoffs present in the
 * processor.  Generally, the EPB is expected to be set by user space (directly
 * via sysfs or with the help of the x86_energy_perf_policy tool), but there are
 * two reasons क्रम the kernel to update it.
 *
 * First, there are प्रणालीs where the platक्रमm firmware resets the EPB during
 * प्रणाली-wide transitions from sleep states back पूर्णांकo the working state
 * effectively causing the previous EPB updates by user space to be lost.
 * Thus the kernel needs to save the current EPB values क्रम all CPUs during
 * प्रणाली-wide transitions to sleep states and restore them on the way back to
 * the working state.  That can be achieved by saving EPB क्रम secondary CPUs
 * when they are taken offline during transitions पूर्णांकo प्रणाली sleep states and
 * क्रम the boot CPU in a syscore suspend operation, so that it can be restored
 * क्रम the boot CPU in a syscore resume operation and क्रम the other CPUs when
 * they are brought back online.  However, CPUs that are alपढ़ोy offline when
 * a प्रणाली-wide PM transition is started are not taken offline again, but their
 * EPB values may still be reset by the platक्रमm firmware during the transition,
 * so in fact it is necessary to save the EPB of any CPU taken offline and to
 * restore it when the given CPU goes back online at all बार.
 *
 * Second, on many प्रणालीs the initial EPB value coming from the platक्रमm
 * firmware is 0 ('performance') and at least on some of them that is because
 * the platक्रमm firmware करोes not initialize EPB at all with the assumption that
 * the OS will करो that anyway.  That someबार is problematic, as it may cause
 * the प्रणाली battery to drain too fast, क्रम example, so it is better to adjust
 * it on CPU bring-up and अगर the initial EPB value क्रम a given CPU is 0, the
 * kernel changes it to 6 ('normal').
 */

अटल DEFINE_PER_CPU(u8, saved_epb);

#घोषणा EPB_MASK	0x0fULL
#घोषणा EPB_SAVED	0x10ULL
#घोषणा MAX_EPB		EPB_MASK

अटल पूर्णांक पूर्णांकel_epb_save(व्योम)
अणु
	u64 epb;

	rdmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
	/*
	 * Ensure that saved_epb will always be nonzero after this ग_लिखो even अगर
	 * the EPB value पढ़ो from the MSR is 0.
	 */
	this_cpu_ग_लिखो(saved_epb, (epb & EPB_MASK) | EPB_SAVED);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_epb_restore(व्योम)
अणु
	u64 val = this_cpu_पढ़ो(saved_epb);
	u64 epb;

	rdmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
	अगर (val) अणु
		val &= EPB_MASK;
	पूर्ण अन्यथा अणु
		/*
		 * Because पूर्णांकel_epb_save() has not run क्रम the current CPU yet,
		 * it is going online क्रम the first समय, so अगर its EPB value is
		 * 0 ('performance') at this poपूर्णांक, assume that it has not been
		 * initialized by the platक्रमm firmware and set it to 6
		 * ('normal').
		 */
		val = epb & EPB_MASK;
		अगर (val == ENERGY_PERF_BIAS_PERFORMANCE) अणु
			val = ENERGY_PERF_BIAS_NORMAL;
			pr_warn_once("ENERGY_PERF_BIAS: Set to 'normal', was 'performance'\n");
		पूर्ण
	पूर्ण
	wrmsrl(MSR_IA32_ENERGY_PERF_BIAS, (epb & ~EPB_MASK) | val);
पूर्ण

अटल काष्ठा syscore_ops पूर्णांकel_epb_syscore_ops = अणु
	.suspend = पूर्णांकel_epb_save,
	.resume = पूर्णांकel_epb_restore,
पूर्ण;

अटल स्थिर अक्षर * स्थिर energy_perf_strings[] = अणु
	"performance",
	"balance-performance",
	"normal",
	"balance-power",
	"power"
पूर्ण;
अटल स्थिर u8 energ_perf_values[] = अणु
	ENERGY_PERF_BIAS_PERFORMANCE,
	ENERGY_PERF_BIAS_BALANCE_PERFORMANCE,
	ENERGY_PERF_BIAS_NORMAL,
	ENERGY_PERF_BIAS_BALANCE_POWERSAVE,
	ENERGY_PERF_BIAS_POWERSAVE
पूर्ण;

अटल sमाप_प्रकार energy_perf_bias_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	अचिन्हित पूर्णांक cpu = dev->id;
	u64 epb;
	पूर्णांक ret;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%llu\n", epb);
पूर्ण

अटल sमाप_प्रकार energy_perf_bias_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक cpu = dev->id;
	u64 epb, val;
	पूर्णांक ret;

	ret = __sysfs_match_string(energy_perf_strings,
				   ARRAY_SIZE(energy_perf_strings), buf);
	अगर (ret >= 0)
		val = energ_perf_values[ret];
	अन्यथा अगर (kstrtou64(buf, 0, &val) || val > MAX_EPB)
		वापस -EINVAL;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	अगर (ret < 0)
		वापस ret;

	ret = wrmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS,
			    (epb & ~EPB_MASK) | val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(energy_perf_bias);

अटल काष्ठा attribute *पूर्णांकel_epb_attrs[] = अणु
	&dev_attr_energy_perf_bias.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकel_epb_attr_group = अणु
	.name = घातer_group_name,
	.attrs =  पूर्णांकel_epb_attrs
पूर्ण;

अटल पूर्णांक पूर्णांकel_epb_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(cpu);

	पूर्णांकel_epb_restore();
	अगर (!cpuhp_tasks_frozen)
		sysfs_merge_group(&cpu_dev->kobj, &पूर्णांकel_epb_attr_group);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_epb_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(cpu);

	अगर (!cpuhp_tasks_frozen)
		sysfs_unmerge_group(&cpu_dev->kobj, &पूर्णांकel_epb_attr_group);

	पूर्णांकel_epb_save();
	वापस 0;
पूर्ण

अटल __init पूर्णांक पूर्णांकel_epb_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_EPB))
		वापस -ENODEV;

	ret = cpuhp_setup_state(CPUHP_AP_X86_INTEL_EPB_ONLINE,
				"x86/intel/epb:online", पूर्णांकel_epb_online,
				पूर्णांकel_epb_offline);
	अगर (ret < 0)
		जाओ err_out_online;

	रेजिस्टर_syscore_ops(&पूर्णांकel_epb_syscore_ops);
	वापस 0;

err_out_online:
	cpuhp_हटाओ_state(CPUHP_AP_X86_INTEL_EPB_ONLINE);
	वापस ret;
पूर्ण
subsys_initcall(पूर्णांकel_epb_init);
