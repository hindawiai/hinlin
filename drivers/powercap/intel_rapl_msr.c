<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Running Average Power Limit (RAPL) Driver via MSR पूर्णांकerface
 * Copyright (c) 2019, Intel Corporation.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/cpu.h>
#समावेश <linux/घातercap.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकel_rapl.h>
#समावेश <linux/processor.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/iosf_mbi.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

/* Local defines */
#घोषणा MSR_PLATFORM_POWER_LIMIT	0x0000065C
#घोषणा MSR_VR_CURRENT_CONFIG		0x00000601

/* निजी data क्रम RAPL MSR Interface */
अटल काष्ठा rapl_अगर_priv *rapl_msr_priv;

अटल काष्ठा rapl_अगर_priv rapl_msr_priv_पूर्णांकel = अणु
	.reg_unit = MSR_RAPL_POWER_UNIT,
	.regs[RAPL_DOMAIN_PACKAGE] = अणु
		MSR_PKG_POWER_LIMIT, MSR_PKG_ENERGY_STATUS, MSR_PKG_PERF_STATUS, 0, MSR_PKG_POWER_INFO पूर्ण,
	.regs[RAPL_DOMAIN_PP0] = अणु
		MSR_PP0_POWER_LIMIT, MSR_PP0_ENERGY_STATUS, 0, MSR_PP0_POLICY, 0 पूर्ण,
	.regs[RAPL_DOMAIN_PP1] = अणु
		MSR_PP1_POWER_LIMIT, MSR_PP1_ENERGY_STATUS, 0, MSR_PP1_POLICY, 0 पूर्ण,
	.regs[RAPL_DOMAIN_DRAM] = अणु
		MSR_DRAM_POWER_LIMIT, MSR_DRAM_ENERGY_STATUS, MSR_DRAM_PERF_STATUS, 0, MSR_DRAM_POWER_INFO पूर्ण,
	.regs[RAPL_DOMAIN_PLATFORM] = अणु
		MSR_PLATFORM_POWER_LIMIT, MSR_PLATFORM_ENERGY_STATUS, 0, 0, 0पूर्ण,
	.limits[RAPL_DOMAIN_PACKAGE] = 2,
	.limits[RAPL_DOMAIN_PLATFORM] = 2,
पूर्ण;

अटल काष्ठा rapl_अगर_priv rapl_msr_priv_amd = अणु
	.reg_unit = MSR_AMD_RAPL_POWER_UNIT,
	.regs[RAPL_DOMAIN_PACKAGE] = अणु
		0, MSR_AMD_PKG_ENERGY_STATUS, 0, 0, 0 पूर्ण,
	.regs[RAPL_DOMAIN_PP0] = अणु
		0, MSR_AMD_CORE_ENERGY_STATUS, 0, 0, 0 पूर्ण,
पूर्ण;

/* Handles CPU hotplug on multi-socket प्रणालीs.
 * If a CPU goes online as the first CPU of the physical package
 * we add the RAPL package to the प्रणाली. Similarly, when the last
 * CPU of the package is हटाओd, we हटाओ the RAPL package and its
 * associated करोमुख्यs. Cooling devices are handled accordingly at
 * per-करोमुख्य level.
 */
अटल पूर्णांक rapl_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_package *rp;

	rp = rapl_find_package_करोमुख्य(cpu, rapl_msr_priv);
	अगर (!rp) अणु
		rp = rapl_add_package(cpu, rapl_msr_priv);
		अगर (IS_ERR(rp))
			वापस PTR_ERR(rp);
	पूर्ण
	cpumask_set_cpu(cpu, &rp->cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_package *rp;
	पूर्णांक lead_cpu;

	rp = rapl_find_package_करोमुख्य(cpu, rapl_msr_priv);
	अगर (!rp)
		वापस 0;

	cpumask_clear_cpu(cpu, &rp->cpumask);
	lead_cpu = cpumask_first(&rp->cpumask);
	अगर (lead_cpu >= nr_cpu_ids)
		rapl_हटाओ_package(rp);
	अन्यथा अगर (rp->lead_cpu == cpu)
		rp->lead_cpu = lead_cpu;
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_msr_पढ़ो_raw(पूर्णांक cpu, काष्ठा reg_action *ra)
अणु
	u32 msr = (u32)ra->reg;

	अगर (rdmsrl_safe_on_cpu(cpu, msr, &ra->value)) अणु
		pr_debug("failed to read msr 0x%x on cpu %d\n", msr, cpu);
		वापस -EIO;
	पूर्ण
	ra->value &= ra->mask;
	वापस 0;
पूर्ण

अटल व्योम rapl_msr_update_func(व्योम *info)
अणु
	काष्ठा reg_action *ra = info;
	u32 msr = (u32)ra->reg;
	u64 val;

	ra->err = rdmsrl_safe(msr, &val);
	अगर (ra->err)
		वापस;

	val &= ~ra->mask;
	val |= ra->value;

	ra->err = wrmsrl_safe(msr, val);
पूर्ण

अटल पूर्णांक rapl_msr_ग_लिखो_raw(पूर्णांक cpu, काष्ठा reg_action *ra)
अणु
	पूर्णांक ret;

	ret = smp_call_function_single(cpu, rapl_msr_update_func, ra, 1);
	अगर (WARN_ON_ONCE(ret))
		वापस ret;

	वापस ra->err;
पूर्ण

/* List of verअगरied CPUs. */
अटल स्थिर काष्ठा x86_cpu_id pl4_support_ids[] = अणु
	अणु X86_VENDOR_INTEL, 6, INTEL_FAM6_TIGERLAKE_L, X86_FEATURE_ANY पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक rapl_msr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा x86_cpu_id *id = x86_match_cpu(pl4_support_ids);
	पूर्णांक ret;

	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		rapl_msr_priv = &rapl_msr_priv_पूर्णांकel;
		अवरोध;
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
		rapl_msr_priv = &rapl_msr_priv_amd;
		अवरोध;
	शेष:
		pr_err("intel-rapl does not support CPU vendor %d\n", boot_cpu_data.x86_venकरोr);
		वापस -ENODEV;
	पूर्ण
	rapl_msr_priv->पढ़ो_raw = rapl_msr_पढ़ो_raw;
	rapl_msr_priv->ग_लिखो_raw = rapl_msr_ग_लिखो_raw;

	अगर (id) अणु
		rapl_msr_priv->limits[RAPL_DOMAIN_PACKAGE] = 3;
		rapl_msr_priv->regs[RAPL_DOMAIN_PACKAGE][RAPL_DOMAIN_REG_PL4] =
			MSR_VR_CURRENT_CONFIG;
		pr_info("PL4 support detected.\n");
	पूर्ण

	rapl_msr_priv->control_type = घातercap_रेजिस्टर_control_type(शून्य, "intel-rapl", शून्य);
	अगर (IS_ERR(rapl_msr_priv->control_type)) अणु
		pr_debug("failed to register powercap control_type.\n");
		वापस PTR_ERR(rapl_msr_priv->control_type);
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "powercap/rapl:online",
				rapl_cpu_online, rapl_cpu_करोwn_prep);
	अगर (ret < 0)
		जाओ out;
	rapl_msr_priv->pcap_rapl_online = ret;

	वापस 0;

out:
	अगर (ret)
		घातercap_unरेजिस्टर_control_type(rapl_msr_priv->control_type);
	वापस ret;
पूर्ण

अटल पूर्णांक rapl_msr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpuhp_हटाओ_state(rapl_msr_priv->pcap_rapl_online);
	घातercap_unरेजिस्टर_control_type(rapl_msr_priv->control_type);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id rapl_msr_ids[] = अणु
	अणु .name = "intel_rapl_msr", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rapl_msr_ids);

अटल काष्ठा platक्रमm_driver पूर्णांकel_rapl_msr_driver = अणु
	.probe = rapl_msr_probe,
	.हटाओ = rapl_msr_हटाओ,
	.id_table = rapl_msr_ids,
	.driver = अणु
		.name = "intel_rapl_msr",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_rapl_msr_driver);

MODULE_DESCRIPTION("Driver for Intel RAPL (Running Average Power Limit) control via MSR interface");
MODULE_AUTHOR("Zhang Rui <rui.zhang@intel.com>");
MODULE_LICENSE("GPL v2");
