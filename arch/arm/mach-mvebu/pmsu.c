<शैली गुरु>
/*
 * Power Management Service Unit(PMSU) support क्रम Armada 370/XP platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * Yehuda Yitschak <yehuday@marvell.com>
 * Gregory Clement <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Armada 370 and Armada XP SOCs have a घातer management service
 * unit which is responsible क्रम घातering करोwn and waking up CPUs and
 * other SOC units
 */

#घोषणा pr_fmt(fmt) "mvebu-pmsu: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mbus.h>
#समावेश <linux/mvebu-pmsu.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश "common.h"
#समावेश "pmsu.h"

#घोषणा PMSU_BASE_OFFSET    0x100
#घोषणा PMSU_REG_SIZE	    0x1000

/* PMSU MP रेजिस्टरs */
#घोषणा PMSU_CONTROL_AND_CONFIG(cpu)	    ((cpu * 0x100) + 0x104)
#घोषणा PMSU_CONTROL_AND_CONFIG_DFS_REQ		BIT(18)
#घोषणा PMSU_CONTROL_AND_CONFIG_PWDDN_REQ	BIT(16)
#घोषणा PMSU_CONTROL_AND_CONFIG_L2_PWDDN	BIT(20)

#घोषणा PMSU_CPU_POWER_DOWN_CONTROL(cpu)    ((cpu * 0x100) + 0x108)

#घोषणा PMSU_CPU_POWER_DOWN_DIS_SNP_Q_SKIP	BIT(0)

#घोषणा PMSU_STATUS_AND_MASK(cpu)	    ((cpu * 0x100) + 0x10c)
#घोषणा PMSU_STATUS_AND_MASK_CPU_IDLE_WAIT	BIT(16)
#घोषणा PMSU_STATUS_AND_MASK_SNP_Q_EMPTY_WAIT	BIT(17)
#घोषणा PMSU_STATUS_AND_MASK_IRQ_WAKEUP		BIT(20)
#घोषणा PMSU_STATUS_AND_MASK_FIQ_WAKEUP		BIT(21)
#घोषणा PMSU_STATUS_AND_MASK_DBG_WAKEUP		BIT(22)
#घोषणा PMSU_STATUS_AND_MASK_IRQ_MASK		BIT(24)
#घोषणा PMSU_STATUS_AND_MASK_FIQ_MASK		BIT(25)

#घोषणा PMSU_EVENT_STATUS_AND_MASK(cpu)     ((cpu * 0x100) + 0x120)
#घोषणा PMSU_EVENT_STATUS_AND_MASK_DFS_DONE        BIT(1)
#घोषणा PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK   BIT(17)

#घोषणा PMSU_BOOT_ADDR_REसूचीECT_OFFSET(cpu) ((cpu * 0x100) + 0x124)

/* PMSU fabric रेजिस्टरs */
#घोषणा L2C_NFABRIC_PM_CTL		    0x4
#घोषणा L2C_NFABRIC_PM_CTL_PWR_DOWN		BIT(20)

/* PMSU delay रेजिस्टरs */
#घोषणा PMSU_POWERDOWN_DELAY		    0xF04
#घोषणा PMSU_POWERDOWN_DELAY_PMU		BIT(1)
#घोषणा PMSU_POWERDOWN_DELAY_MASK		0xFFFE
#घोषणा PMSU_DFLT_ARMADA38X_DELAY	        0x64

/* CA9 MPcore SoC Control रेजिस्टरs */

#घोषणा MPCORE_RESET_CTL		    0x64
#घोषणा MPCORE_RESET_CTL_L2			BIT(0)
#घोषणा MPCORE_RESET_CTL_DEBUG			BIT(16)

#घोषणा SRAM_PHYS_BASE  0xFFFF0000
#घोषणा BOOTROM_BASE    0xFFF00000
#घोषणा BOOTROM_SIZE    0x100000

#घोषणा ARMADA_370_CRYPT0_ENG_TARGET   0x9
#घोषणा ARMADA_370_CRYPT0_ENG_ATTR     0x1

बाह्य व्योम ll_disable_coherency(व्योम);
बाह्य व्योम ll_enable_coherency(व्योम);

बाह्य व्योम armada_370_xp_cpu_resume(व्योम);
बाह्य व्योम armada_38x_cpu_resume(व्योम);

अटल phys_addr_t pmsu_mp_phys_base;
अटल व्योम __iomem *pmsu_mp_base;

अटल व्योम *mvebu_cpu_resume;

अटल स्थिर काष्ठा of_device_id of_pmsu_table[] = अणु
	अणु .compatible = "marvell,armada-370-pmsu", पूर्ण,
	अणु .compatible = "marvell,armada-370-xp-pmsu", पूर्ण,
	अणु .compatible = "marvell,armada-380-pmsu", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

व्योम mvebu_pmsu_set_cpu_boot_addr(पूर्णांक hw_cpu, व्योम *boot_addr)
अणु
	ग_लिखोl(__pa_symbol(boot_addr), pmsu_mp_base +
		PMSU_BOOT_ADDR_REसूचीECT_OFFSET(hw_cpu));
पूर्ण

बाह्य अचिन्हित अक्षर mvebu_boot_wa_start[];
बाह्य अचिन्हित अक्षर mvebu_boot_wa_end[];

/*
 * This function sets up the boot address workaround needed क्रम SMP
 * boot on Armada 375 Z1 and cpuidle on Armada 370. It unmaps the
 * BootROM Mbus winकरोw, and instead remaps a crypto SRAM पूर्णांकo which a
 * custom piece of code is copied to replace the problematic BootROM.
 */
पूर्णांक mvebu_setup_boot_addr_wa(अचिन्हित पूर्णांक crypto_eng_target,
			     अचिन्हित पूर्णांक crypto_eng_attribute,
			     phys_addr_t resume_addr_reg)
अणु
	व्योम __iomem *sram_virt_base;
	u32 code_len = mvebu_boot_wa_end - mvebu_boot_wa_start;

	mvebu_mbus_del_winकरोw(BOOTROM_BASE, BOOTROM_SIZE);
	mvebu_mbus_add_winकरोw_by_id(crypto_eng_target, crypto_eng_attribute,
				    SRAM_PHYS_BASE, SZ_64K);

	sram_virt_base = ioremap(SRAM_PHYS_BASE, SZ_64K);
	अगर (!sram_virt_base) अणु
		pr_err("Unable to map SRAM to setup the boot address WA\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(sram_virt_base, &mvebu_boot_wa_start, code_len);

	/*
	 * The last word of the code copied in SRAM must contain the
	 * physical base address of the PMSU रेजिस्टर. We
	 * पूर्णांकentionally store this address in the native endianness
	 * of the प्रणाली.
	 */
	__raw_ग_लिखोl((अचिन्हित दीर्घ)resume_addr_reg,
		     sram_virt_base + code_len - 4);

	iounmap(sram_virt_base);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mvebu_v7_pmsu_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक ret = 0;

	np = of_find_matching_node(शून्य, of_pmsu_table);
	अगर (!np)
		वापस 0;

	pr_info("Initializing Power Management Service Unit\n");

	अगर (of_address_to_resource(np, 0, &res)) अणु
		pr_err("unable to get resource\n");
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (of_device_is_compatible(np, "marvell,armada-370-xp-pmsu")) अणु
		pr_warn(FW_WARN "deprecated pmsu binding\n");
		res.start = res.start - PMSU_BASE_OFFSET;
		res.end = res.start + PMSU_REG_SIZE - 1;
	पूर्ण

	अगर (!request_mem_region(res.start, resource_size(&res),
				np->full_name)) अणु
		pr_err("unable to request region\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	pmsu_mp_phys_base = res.start;

	pmsu_mp_base = ioremap(res.start, resource_size(&res));
	अगर (!pmsu_mp_base) अणु
		pr_err("unable to map registers\n");
		release_mem_region(res.start, resource_size(&res));
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

 out:
	of_node_put(np);
	वापस ret;
पूर्ण

अटल व्योम mvebu_v7_pmsu_enable_l2_घातerकरोwn_onidle(व्योम)
अणु
	u32 reg;

	अगर (pmsu_mp_base == शून्य)
		वापस;

	/* Enable L2 & Fabric घातerकरोwn in Deep-Idle mode - Fabric */
	reg = पढ़ोl(pmsu_mp_base + L2C_NFABRIC_PM_CTL);
	reg |= L2C_NFABRIC_PM_CTL_PWR_DOWN;
	ग_लिखोl(reg, pmsu_mp_base + L2C_NFABRIC_PM_CTL);
पूर्ण

क्रमागत pmsu_idle_prepare_flags अणु
	PMSU_PREPARE_NORMAL = 0,
	PMSU_PREPARE_DEEP_IDLE = BIT(0),
	PMSU_PREPARE_SNOOP_DISABLE = BIT(1),
पूर्ण;

/* No locking is needed because we only access per-CPU रेजिस्टरs */
अटल पूर्णांक mvebu_v7_pmsu_idle_prepare(अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक hw_cpu = cpu_logical_map(smp_processor_id());
	u32 reg;

	अगर (pmsu_mp_base == शून्य)
		वापस -EINVAL;

	/*
	 * Adjust the PMSU configuration to रुको क्रम WFI संकेत, enable
	 * IRQ and FIQ as wakeup events, set रुको क्रम snoop queue empty
	 * indication and mask IRQ and FIQ from CPU
	 */
	reg = पढ़ोl(pmsu_mp_base + PMSU_STATUS_AND_MASK(hw_cpu));
	reg |= PMSU_STATUS_AND_MASK_CPU_IDLE_WAIT    |
	       PMSU_STATUS_AND_MASK_IRQ_WAKEUP       |
	       PMSU_STATUS_AND_MASK_FIQ_WAKEUP       |
	       PMSU_STATUS_AND_MASK_SNP_Q_EMPTY_WAIT |
	       PMSU_STATUS_AND_MASK_IRQ_MASK         |
	       PMSU_STATUS_AND_MASK_FIQ_MASK;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_STATUS_AND_MASK(hw_cpu));

	reg = पढ़ोl(pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(hw_cpu));
	/* ask HW to घातer करोwn the L2 Cache अगर needed */
	अगर (flags & PMSU_PREPARE_DEEP_IDLE)
		reg |= PMSU_CONTROL_AND_CONFIG_L2_PWDDN;

	/* request घातer करोwn */
	reg |= PMSU_CONTROL_AND_CONFIG_PWDDN_REQ;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(hw_cpu));

	अगर (flags & PMSU_PREPARE_SNOOP_DISABLE) अणु
		/* Disable snoop disable by HW - SW is taking care of it */
		reg = पढ़ोl(pmsu_mp_base + PMSU_CPU_POWER_DOWN_CONTROL(hw_cpu));
		reg |= PMSU_CPU_POWER_DOWN_DIS_SNP_Q_SKIP;
		ग_लिखोl(reg, pmsu_mp_base + PMSU_CPU_POWER_DOWN_CONTROL(hw_cpu));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक armada_370_xp_pmsu_idle_enter(अचिन्हित दीर्घ deepidle)
अणु
	अचिन्हित दीर्घ flags = PMSU_PREPARE_SNOOP_DISABLE;
	पूर्णांक ret;

	अगर (deepidle)
		flags |= PMSU_PREPARE_DEEP_IDLE;

	ret = mvebu_v7_pmsu_idle_prepare(flags);
	अगर (ret)
		वापस ret;

	v7_निकास_coherency_flush(all);

	ll_disable_coherency();

	dsb();

	wfi();

	/* If we are here, wfi failed. As processors run out of
	 * coherency क्रम some समय, tlbs might be stale, so flush them
	 */
	local_flush_tlb_all();

	ll_enable_coherency();

	/* Test the CR_C bit and set it अगर it was cleared */
	यंत्र अस्थिर(
	"mrc	p15, 0, r0, c1, c0, 0 \n\t"
	"tst	r0, %0 \n\t"
	"orreq	r0, r0, #(1 << 2) \n\t"
	"mcreq	p15, 0, r0, c1, c0, 0 \n\t"
	"isb	"
	: : "Ir" (CR_C) : "r0");

	pr_debug("Failed to suspend the system\n");

	वापस 0;
पूर्ण

अटल पूर्णांक armada_370_xp_cpu_suspend(अचिन्हित दीर्घ deepidle)
अणु
	वापस cpu_suspend(deepidle, armada_370_xp_pmsu_idle_enter);
पूर्ण

पूर्णांक armada_38x_करो_cpu_suspend(अचिन्हित दीर्घ deepidle)
अणु
	अचिन्हित दीर्घ flags = 0;

	अगर (deepidle)
		flags |= PMSU_PREPARE_DEEP_IDLE;

	mvebu_v7_pmsu_idle_prepare(flags);
	/*
	 * Alपढ़ोy flushed cache, but करो it again as the outer cache
	 * functions dirty the cache with spinlocks
	 */
	v7_निकास_coherency_flush(louis);

	scu_घातer_mode(mvebu_get_scu_base(), SCU_PM_POWEROFF);

	cpu_करो_idle();

	वापस 1;
पूर्ण

अटल पूर्णांक armada_38x_cpu_suspend(अचिन्हित दीर्घ deepidle)
अणु
	वापस cpu_suspend(false, armada_38x_करो_cpu_suspend);
पूर्ण

/* No locking is needed because we only access per-CPU रेजिस्टरs */
व्योम mvebu_v7_pmsu_idle_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक hw_cpu = cpu_logical_map(smp_processor_id());
	u32 reg;

	अगर (pmsu_mp_base == शून्य)
		वापस;
	/* cancel ask HW to घातer करोwn the L2 Cache अगर possible */
	reg = पढ़ोl(pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(hw_cpu));
	reg &= ~PMSU_CONTROL_AND_CONFIG_L2_PWDDN;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(hw_cpu));

	/* cancel Enable wakeup events and mask पूर्णांकerrupts */
	reg = पढ़ोl(pmsu_mp_base + PMSU_STATUS_AND_MASK(hw_cpu));
	reg &= ~(PMSU_STATUS_AND_MASK_IRQ_WAKEUP | PMSU_STATUS_AND_MASK_FIQ_WAKEUP);
	reg &= ~PMSU_STATUS_AND_MASK_CPU_IDLE_WAIT;
	reg &= ~PMSU_STATUS_AND_MASK_SNP_Q_EMPTY_WAIT;
	reg &= ~(PMSU_STATUS_AND_MASK_IRQ_MASK | PMSU_STATUS_AND_MASK_FIQ_MASK);
	ग_लिखोl(reg, pmsu_mp_base + PMSU_STATUS_AND_MASK(hw_cpu));
पूर्ण

अटल पूर्णांक mvebu_v7_cpu_pm_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ action, व्योम *hcpu)
अणु
	अगर (action == CPU_PM_ENTER) अणु
		अचिन्हित पूर्णांक hw_cpu = cpu_logical_map(smp_processor_id());
		mvebu_pmsu_set_cpu_boot_addr(hw_cpu, mvebu_cpu_resume);
	पूर्ण अन्यथा अगर (action == CPU_PM_EXIT) अणु
		mvebu_v7_pmsu_idle_निकास();
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mvebu_v7_cpu_pm_notअगरier = अणु
	.notअगरier_call = mvebu_v7_cpu_pm_notअगरy,
पूर्ण;

अटल काष्ठा platक्रमm_device mvebu_v7_cpuidle_device;

अटल पूर्णांक broken_idle(काष्ठा device_node *np)
अणु
	अगर (of_property_पढ़ो_bool(np, "broken-idle")) अणु
		pr_warn("CPU idle is currently broken: disabling\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init पूर्णांक armada_370_cpuidle_init(व्योम)
अणु
	काष्ठा device_node *np;
	phys_addr_t redirect_reg;

	np = of_find_compatible_node(शून्य, शून्य, "marvell,coherency-fabric");
	अगर (!np)
		वापस -ENODEV;

	अगर (broken_idle(np))
		जाओ end;

	/*
	 * On Armada 370, there is "a slow निकास process from the deep
	 * idle state due to heavy L1/L2 cache cleanup operations
	 * perक्रमmed by the BootROM software". To aव्योम this, we
	 * replace the restart code of the bootrom by a a simple jump
	 * to the boot address. Then the code located at this boot
	 * address will take care of the initialization.
	 */
	redirect_reg = pmsu_mp_phys_base + PMSU_BOOT_ADDR_REसूचीECT_OFFSET(0);
	mvebu_setup_boot_addr_wa(ARMADA_370_CRYPT0_ENG_TARGET,
				 ARMADA_370_CRYPT0_ENG_ATTR,
				 redirect_reg);

	mvebu_cpu_resume = armada_370_xp_cpu_resume;
	mvebu_v7_cpuidle_device.dev.platक्रमm_data = armada_370_xp_cpu_suspend;
	mvebu_v7_cpuidle_device.name = "cpuidle-armada-370";

end:
	of_node_put(np);
	वापस 0;
पूर्ण

अटल __init पूर्णांक armada_38x_cpuidle_init(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *mpsoc_base;
	u32 reg;

	pr_warn("CPU idle is currently broken on Armada 38x: disabling\n");
	वापस 0;

	np = of_find_compatible_node(शून्य, शून्य,
				     "marvell,armada-380-coherency-fabric");
	अगर (!np)
		वापस -ENODEV;

	अगर (broken_idle(np))
		जाओ end;

	of_node_put(np);

	np = of_find_compatible_node(शून्य, शून्य,
				     "marvell,armada-380-mpcore-soc-ctrl");
	अगर (!np)
		वापस -ENODEV;
	mpsoc_base = of_iomap(np, 0);
	BUG_ON(!mpsoc_base);

	/* Set up reset mask when घातering करोwn the cpus */
	reg = पढ़ोl(mpsoc_base + MPCORE_RESET_CTL);
	reg |= MPCORE_RESET_CTL_L2;
	reg |= MPCORE_RESET_CTL_DEBUG;
	ग_लिखोl(reg, mpsoc_base + MPCORE_RESET_CTL);
	iounmap(mpsoc_base);

	/* Set up delay */
	reg = पढ़ोl(pmsu_mp_base + PMSU_POWERDOWN_DELAY);
	reg &= ~PMSU_POWERDOWN_DELAY_MASK;
	reg |= PMSU_DFLT_ARMADA38X_DELAY;
	reg |= PMSU_POWERDOWN_DELAY_PMU;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_POWERDOWN_DELAY);

	mvebu_cpu_resume = armada_38x_cpu_resume;
	mvebu_v7_cpuidle_device.dev.platक्रमm_data = armada_38x_cpu_suspend;
	mvebu_v7_cpuidle_device.name = "cpuidle-armada-38x";

end:
	of_node_put(np);
	वापस 0;
पूर्ण

अटल __init पूर्णांक armada_xp_cpuidle_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "marvell,coherency-fabric");
	अगर (!np)
		वापस -ENODEV;

	अगर (broken_idle(np))
		जाओ end;

	mvebu_cpu_resume = armada_370_xp_cpu_resume;
	mvebu_v7_cpuidle_device.dev.platक्रमm_data = armada_370_xp_cpu_suspend;
	mvebu_v7_cpuidle_device.name = "cpuidle-armada-xp";

end:
	of_node_put(np);
	वापस 0;
पूर्ण

अटल पूर्णांक __init mvebu_v7_cpu_pm_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_matching_node(शून्य, of_pmsu_table);
	अगर (!np)
		वापस 0;
	of_node_put(np);

	/*
	 * Currently the CPU idle support क्रम Armada 38x is broken, as
	 * the CPU hotplug uses some of the CPU idle functions it is
	 * broken too, so let's disable it
	 */
	अगर (of_machine_is_compatible("marvell,armada380")) अणु
		cpu_hotplug_disable();
		pr_warn("CPU hotplug support is currently broken on Armada 38x: disabling\n");
	पूर्ण

	अगर (of_machine_is_compatible("marvell,armadaxp"))
		ret = armada_xp_cpuidle_init();
	अन्यथा अगर (of_machine_is_compatible("marvell,armada370"))
		ret = armada_370_cpuidle_init();
	अन्यथा अगर (of_machine_is_compatible("marvell,armada380"))
		ret = armada_38x_cpuidle_init();
	अन्यथा
		वापस 0;

	अगर (ret)
		वापस ret;

	mvebu_v7_pmsu_enable_l2_घातerकरोwn_onidle();
	अगर (mvebu_v7_cpuidle_device.name)
		platक्रमm_device_रेजिस्टर(&mvebu_v7_cpuidle_device);
	cpu_pm_रेजिस्टर_notअगरier(&mvebu_v7_cpu_pm_notअगरier);

	वापस 0;
पूर्ण

arch_initcall(mvebu_v7_cpu_pm_init);
early_initcall(mvebu_v7_pmsu_init);

अटल व्योम mvebu_pmsu_dfs_request_local(व्योम *data)
अणु
	u32 reg;
	u32 cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* Prepare to enter idle */
	reg = पढ़ोl(pmsu_mp_base + PMSU_STATUS_AND_MASK(cpu));
	reg |= PMSU_STATUS_AND_MASK_CPU_IDLE_WAIT |
	       PMSU_STATUS_AND_MASK_IRQ_MASK     |
	       PMSU_STATUS_AND_MASK_FIQ_MASK;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_STATUS_AND_MASK(cpu));

	/* Request the DFS transition */
	reg = पढ़ोl(pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(cpu));
	reg |= PMSU_CONTROL_AND_CONFIG_DFS_REQ;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_CONTROL_AND_CONFIG(cpu));

	/* The fact of entering idle will trigger the DFS transition */
	wfi();

	/*
	 * We're back from idle, the DFS transition has completed,
	 * clear the idle रुको indication.
	 */
	reg = पढ़ोl(pmsu_mp_base + PMSU_STATUS_AND_MASK(cpu));
	reg &= ~PMSU_STATUS_AND_MASK_CPU_IDLE_WAIT;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_STATUS_AND_MASK(cpu));

	local_irq_restore(flags);
पूर्ण

पूर्णांक mvebu_pmsu_dfs_request(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक hwcpu = cpu_logical_map(cpu);
	u32 reg;

	/* Clear any previous DFS DONE event */
	reg = पढ़ोl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg &= ~PMSU_EVENT_STATUS_AND_MASK_DFS_DONE;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	/* Mask the DFS करोne पूर्णांकerrupt, since we are going to poll */
	reg = पढ़ोl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg |= PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	/* Trigger the DFS on the appropriate CPU */
	smp_call_function_single(cpu, mvebu_pmsu_dfs_request_local,
				 शून्य, false);

	/* Poll until the DFS करोne event is generated */
	समयout = jअगरfies + HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		reg = पढ़ोl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
		अगर (reg & PMSU_EVENT_STATUS_AND_MASK_DFS_DONE)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (समय_after(jअगरfies, समयout))
		वापस -ETIME;

	/* Restore the DFS mask to its original state */
	reg = पढ़ोl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg &= ~PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK;
	ग_लिखोl(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	वापस 0;
पूर्ण
