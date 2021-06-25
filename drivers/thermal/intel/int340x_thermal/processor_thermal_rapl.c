<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * processor thermal device RFIM control
 * Copyright (c) 2020, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "processor_thermal_device.h"

अटल काष्ठा rapl_अगर_priv rapl_mmio_priv;

अटल स्थिर काष्ठा rapl_mmio_regs rapl_mmio_शेष = अणु
	.reg_unit = 0x5938,
	.regs[RAPL_DOMAIN_PACKAGE] = अणु 0x59a0, 0x593c, 0x58f0, 0, 0x5930पूर्ण,
	.regs[RAPL_DOMAIN_DRAM] = अणु 0x58e0, 0x58e8, 0x58ec, 0, 0पूर्ण,
	.limits[RAPL_DOMAIN_PACKAGE] = 2,
	.limits[RAPL_DOMAIN_DRAM] = 2,
पूर्ण;

अटल पूर्णांक rapl_mmio_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_package *rp;

	/* mmio rapl supports package 0 only क्रम now */
	अगर (topology_physical_package_id(cpu))
		वापस 0;

	rp = rapl_find_package_करोमुख्य(cpu, &rapl_mmio_priv);
	अगर (!rp) अणु
		rp = rapl_add_package(cpu, &rapl_mmio_priv);
		अगर (IS_ERR(rp))
			वापस PTR_ERR(rp);
	पूर्ण
	cpumask_set_cpu(cpu, &rp->cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_mmio_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_package *rp;
	पूर्णांक lead_cpu;

	rp = rapl_find_package_करोमुख्य(cpu, &rapl_mmio_priv);
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

अटल पूर्णांक rapl_mmio_पढ़ो_raw(पूर्णांक cpu, काष्ठा reg_action *ra)
अणु
	अगर (!ra->reg)
		वापस -EINVAL;

	ra->value = पढ़ोq((व्योम __iomem *)ra->reg);
	ra->value &= ra->mask;
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_mmio_ग_लिखो_raw(पूर्णांक cpu, काष्ठा reg_action *ra)
अणु
	u64 val;

	अगर (!ra->reg)
		वापस -EINVAL;

	val = पढ़ोq((व्योम __iomem *)ra->reg);
	val &= ~ra->mask;
	val |= ra->value;
	ग_लिखोq(val, (व्योम __iomem *)ra->reg);
	वापस 0;
पूर्ण

पूर्णांक proc_thermal_rapl_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv)
अणु
	स्थिर काष्ठा rapl_mmio_regs *rapl_regs = &rapl_mmio_शेष;
	क्रमागत rapl_करोमुख्य_reg_id reg;
	क्रमागत rapl_करोमुख्य_type करोमुख्य;
	पूर्णांक ret;

	अगर (!rapl_regs)
		वापस 0;

	क्रम (करोमुख्य = RAPL_DOMAIN_PACKAGE; करोमुख्य < RAPL_DOMAIN_MAX; करोमुख्य++) अणु
		क्रम (reg = RAPL_DOMAIN_REG_LIMIT; reg < RAPL_DOMAIN_REG_MAX; reg++)
			अगर (rapl_regs->regs[करोमुख्य][reg])
				rapl_mmio_priv.regs[करोमुख्य][reg] =
						(u64)proc_priv->mmio_base +
						rapl_regs->regs[करोमुख्य][reg];
		rapl_mmio_priv.limits[करोमुख्य] = rapl_regs->limits[करोमुख्य];
	पूर्ण
	rapl_mmio_priv.reg_unit = (u64)proc_priv->mmio_base + rapl_regs->reg_unit;

	rapl_mmio_priv.पढ़ो_raw = rapl_mmio_पढ़ो_raw;
	rapl_mmio_priv.ग_लिखो_raw = rapl_mmio_ग_लिखो_raw;

	rapl_mmio_priv.control_type = घातercap_रेजिस्टर_control_type(शून्य, "intel-rapl-mmio", शून्य);
	अगर (IS_ERR(rapl_mmio_priv.control_type)) अणु
		pr_debug("failed to register powercap control_type.\n");
		वापस PTR_ERR(rapl_mmio_priv.control_type);
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "powercap/rapl:online",
				rapl_mmio_cpu_online, rapl_mmio_cpu_करोwn_prep);
	अगर (ret < 0) अणु
		घातercap_unरेजिस्टर_control_type(rapl_mmio_priv.control_type);
		rapl_mmio_priv.control_type = शून्य;
		वापस ret;
	पूर्ण
	rapl_mmio_priv.pcap_rapl_online = ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_rapl_add);

व्योम proc_thermal_rapl_हटाओ(व्योम)
अणु
	अगर (IS_ERR_OR_शून्य(rapl_mmio_priv.control_type))
		वापस;

	cpuhp_हटाओ_state(rapl_mmio_priv.pcap_rapl_online);
	घातercap_unरेजिस्टर_control_type(rapl_mmio_priv.control_type);
पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_rapl_हटाओ);

MODULE_LICENSE("GPL v2");
