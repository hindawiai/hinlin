<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2012 Samsung Electronics.
// Kyungmin Park <kyungmin.park@samsung.com>
// Tomasz Figa <t.figa@samsung.com>

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/suspend.h>

#समावेश "common.h"
#समावेश "smc.h"

#घोषणा EXYNOS_BOOT_ADDR	0x8
#घोषणा EXYNOS_BOOT_FLAG	0xc

अटल व्योम exynos_save_cp15(व्योम)
अणु
	/* Save Power control and Diagnostic रेजिस्टरs */
	यंत्र ("mrc p15, 0, %0, c15, c0, 0\n"
	     "mrc p15, 0, %1, c15, c0, 1\n"
	     : "=r" (cp15_save_घातer), "=r" (cp15_save_diag)
	     : : "cc");
पूर्ण

अटल पूर्णांक exynos_करो_idle(अचिन्हित दीर्घ mode)
अणु
	चयन (mode) अणु
	हाल FW_DO_IDLE_AFTR:
		अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
			exynos_save_cp15();
		ग_लिखोl_relaxed(__pa_symbol(exynos_cpu_resume_ns),
			       sysram_ns_base_addr + 0x24);
		ग_लिखोl_relaxed(EXYNOS_AFTR_MAGIC, sysram_ns_base_addr + 0x20);
		अगर (soc_is_exynos3250()) अणु
			flush_cache_all();
			exynos_smc(SMC_CMD_SAVE, OP_TYPE_CORE,
				   SMC_POWERSTATE_IDLE, 0);
			exynos_smc(SMC_CMD_SHUTDOWN, OP_TYPE_CLUSTER,
				   SMC_POWERSTATE_IDLE, 0);
		पूर्ण अन्यथा
			exynos_smc(SMC_CMD_CPU0AFTR, 0, 0, 0);
		अवरोध;
	हाल FW_DO_IDLE_SLEEP:
		exynos_smc(SMC_CMD_SLEEP, 0, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_cpu_boot(पूर्णांक cpu)
अणु
	/*
	 * Exynos3250 करोesn't need to send smc command क्रम secondary CPU boot
	 * because Exynos3250 हटाओs WFE in secure mode.
	 */
	अगर (soc_is_exynos3250())
		वापस 0;

	/*
	 * The second parameter of SMC_CMD_CPU1BOOT command means CPU id.
	 */
	exynos_smc(SMC_CMD_CPU1BOOT, cpu, 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_set_cpu_boot_addr(पूर्णांक cpu, अचिन्हित दीर्घ boot_addr)
अणु
	व्योम __iomem *boot_reg;

	अगर (!sysram_ns_base_addr)
		वापस -ENODEV;

	boot_reg = sysram_ns_base_addr + 0x1c;

	/*
	 * Almost all Exynos-series of SoCs that run in secure mode करोn't need
	 * additional offset क्रम every CPU, with Exynos4412 being the only
	 * exception.
	 */
	अगर (soc_is_exynos4412())
		boot_reg += 4 * cpu;

	ग_लिखोl_relaxed(boot_addr, boot_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_get_cpu_boot_addr(पूर्णांक cpu, अचिन्हित दीर्घ *boot_addr)
अणु
	व्योम __iomem *boot_reg;

	अगर (!sysram_ns_base_addr)
		वापस -ENODEV;

	boot_reg = sysram_ns_base_addr + 0x1c;

	अगर (soc_is_exynos4412())
		boot_reg += 4 * cpu;

	*boot_addr = पढ़ोl_relaxed(boot_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	flush_cache_all();
	outer_flush_all();

	exynos_smc(SMC_CMD_SLEEP, 0, 0, 0);

	pr_info("Failed to suspend the system\n");
	ग_लिखोl(0, sysram_ns_base_addr + EXYNOS_BOOT_FLAG);
	वापस 1;
पूर्ण

अटल पूर्णांक exynos_suspend(व्योम)
अणु
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
		exynos_save_cp15();

	ग_लिखोl(EXYNOS_SLEEP_MAGIC, sysram_ns_base_addr + EXYNOS_BOOT_FLAG);
	ग_लिखोl(__pa_symbol(exynos_cpu_resume_ns),
		sysram_ns_base_addr + EXYNOS_BOOT_ADDR);

	वापस cpu_suspend(0, exynos_cpu_suspend);
पूर्ण

अटल पूर्णांक exynos_resume(व्योम)
अणु
	ग_लिखोl(0, sysram_ns_base_addr + EXYNOS_BOOT_FLAG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा firmware_ops exynos_firmware_ops = अणु
	.करो_idle		= IS_ENABLED(CONFIG_EXYNOS_CPU_SUSPEND) ? exynos_करो_idle : शून्य,
	.set_cpu_boot_addr	= exynos_set_cpu_boot_addr,
	.get_cpu_boot_addr	= exynos_get_cpu_boot_addr,
	.cpu_boot		= exynos_cpu_boot,
	.suspend		= IS_ENABLED(CONFIG_PM_SLEEP) ? exynos_suspend : शून्य,
	.resume			= IS_ENABLED(CONFIG_EXYNOS_CPU_SUSPEND) ? exynos_resume : शून्य,
पूर्ण;

अटल व्योम exynos_l2_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg)
अणु
	अटल पूर्णांक l2cache_enabled;

	चयन (reg) अणु
	हाल L2X0_CTRL:
		अगर (val & L2X0_CTRL_EN) अणु
			/*
			 * Beक्रमe the cache can be enabled, due to firmware
			 * design, SMC_CMD_L2X0INVALL must be called.
			 */
			अगर (!l2cache_enabled) अणु
				exynos_smc(SMC_CMD_L2X0INVALL, 0, 0, 0);
				l2cache_enabled = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			l2cache_enabled = 0;
		पूर्ण
		exynos_smc(SMC_CMD_L2X0CTRL, val, 0, 0);
		अवरोध;

	हाल L2X0_DEBUG_CTRL:
		exynos_smc(SMC_CMD_L2X0DEBUG, val, 0, 0);
		अवरोध;

	शेष:
		WARN_ONCE(1, "%s: ignoring write to reg 0x%x\n", __func__, reg);
	पूर्ण
पूर्ण

अटल व्योम exynos_l2_configure(स्थिर काष्ठा l2x0_regs *regs)
अणु
	exynos_smc(SMC_CMD_L2X0SETUP1, regs->tag_latency, regs->data_latency,
		   regs->prefetch_ctrl);
	exynos_smc(SMC_CMD_L2X0SETUP2, regs->pwr_ctrl, regs->aux_ctrl, 0);
पूर्ण

bool __init exynos_secure_firmware_available(व्योम)
अणु
	काष्ठा device_node *nd;
	स्थिर __be32 *addr;

	nd = of_find_compatible_node(शून्य, शून्य,
					"samsung,secure-firmware");
	अगर (!nd)
		वापस false;

	addr = of_get_address(nd, 0, शून्य, शून्य);
	of_node_put(nd);
	अगर (!addr) अणु
		pr_err("%s: No address specified.\n", __func__);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम __init exynos_firmware_init(व्योम)
अणु
	अगर (!exynos_secure_firmware_available())
		वापस;

	pr_info("Running under secure firmware.\n");

	रेजिस्टर_firmware_ops(&exynos_firmware_ops);

	/*
	 * Exynos 4 SoCs (based on Cortex A9 and equipped with L2C-310),
	 * running under secure firmware, require certain रेजिस्टरs of L2
	 * cache controller to be written in secure mode. Here .ग_लिखो_sec
	 * callback is provided to perक्रमm necessary SMC calls.
	 */
	अगर (IS_ENABLED(CONFIG_CACHE_L2X0) &&
	    पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9) अणु
		outer_cache.ग_लिखो_sec = exynos_l2_ग_लिखो_sec;
		outer_cache.configure = exynos_l2_configure;
	पूर्ण
पूर्ण

#घोषणा REG_CPU_STATE_ADDR	(sysram_ns_base_addr + 0x28)
#घोषणा BOOT_MODE_MASK		0x1f

व्योम exynos_set_boot_flag(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl_relaxed(REG_CPU_STATE_ADDR + cpu * 4);

	अगर (mode & BOOT_MODE_MASK)
		पंचांगp &= ~BOOT_MODE_MASK;

	पंचांगp |= mode;
	ग_लिखोl_relaxed(पंचांगp, REG_CPU_STATE_ADDR + cpu * 4);
पूर्ण

व्योम exynos_clear_boot_flag(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl_relaxed(REG_CPU_STATE_ADDR + cpu * 4);
	पंचांगp &= ~mode;
	ग_लिखोl_relaxed(पंचांगp, REG_CPU_STATE_ADDR + cpu * 4);
पूर्ण
