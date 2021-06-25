<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU complex suspend & resume functions क्रम Tegra SoCs
 *
 * Copyright (c) 2009-2012, NVIDIA Corporation. All rights reserved.
 */

#समावेश <linux/clk/tegra.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/suspend.h>

#समावेश <linux/firmware/trusted_foundations.h>

#समावेश <soc/tegra/flowctrl.h>
#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/pm.h>
#समावेश <soc/tegra/pmc.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "iomap.h"
#समावेश "pm.h"
#समावेश "reset.h"
#समावेश "sleep.h"

#अगर_घोषित CONFIG_PM_SLEEP
अटल DEFINE_SPINLOCK(tegra_lp2_lock);
अटल u32 iram_save_size;
अटल व्योम *iram_save_addr;
काष्ठा tegra_lp1_iram tegra_lp1_iram;
व्योम (*tegra_tear_करोwn_cpu)(व्योम);
व्योम (*tegra_sleep_core_finish)(अचिन्हित दीर्घ v2p);
अटल पूर्णांक (*tegra_sleep_func)(अचिन्हित दीर्घ v2p);

अटल व्योम tegra_tear_करोwn_cpu_init(व्योम)
अणु
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC))
			tegra_tear_करोwn_cpu = tegra20_tear_करोwn_cpu;
		अवरोध;
	हाल TEGRA30:
	हाल TEGRA114:
	हाल TEGRA124:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC))
			tegra_tear_करोwn_cpu = tegra30_tear_करोwn_cpu;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * restore_cpu_complex
 *
 * restores cpu घड़ी setting, clears flow controller
 *
 * Always called on CPU 0.
 */
अटल व्योम restore_cpu_complex(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	BUG_ON(cpu != 0);

#अगर_घोषित CONFIG_SMP
	cpu = cpu_logical_map(cpu);
#पूर्ण_अगर

	/* Restore the CPU घड़ी settings */
	tegra_cpu_घड़ी_resume();

	flowctrl_cpu_suspend_निकास(cpu);
पूर्ण

/*
 * suspend_cpu_complex
 *
 * saves pll state क्रम use by restart_plls, prepares flow controller क्रम
 * transition to suspend state
 *
 * Must always be called on cpu 0.
 */
अटल व्योम suspend_cpu_complex(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	BUG_ON(cpu != 0);

#अगर_घोषित CONFIG_SMP
	cpu = cpu_logical_map(cpu);
#पूर्ण_अगर

	/* Save the CPU घड़ी settings */
	tegra_cpu_घड़ी_suspend();

	flowctrl_cpu_suspend_enter(cpu);
पूर्ण

व्योम tegra_pm_clear_cpu_in_lp2(व्योम)
अणु
	पूर्णांक phy_cpu_id = cpu_logical_map(smp_processor_id());
	u32 *cpu_in_lp2 = tegra_cpu_lp2_mask;

	spin_lock(&tegra_lp2_lock);

	BUG_ON(!(*cpu_in_lp2 & BIT(phy_cpu_id)));
	*cpu_in_lp2 &= ~BIT(phy_cpu_id);

	spin_unlock(&tegra_lp2_lock);
पूर्ण

व्योम tegra_pm_set_cpu_in_lp2(व्योम)
अणु
	पूर्णांक phy_cpu_id = cpu_logical_map(smp_processor_id());
	u32 *cpu_in_lp2 = tegra_cpu_lp2_mask;

	spin_lock(&tegra_lp2_lock);

	BUG_ON((*cpu_in_lp2 & BIT(phy_cpu_id)));
	*cpu_in_lp2 |= BIT(phy_cpu_id);

	spin_unlock(&tegra_lp2_lock);
पूर्ण

अटल पूर्णांक tegra_sleep_cpu(अचिन्हित दीर्घ v2p)
अणु
	अगर (tegra_cpu_car_ops->rail_off_पढ़ोy &&
	    WARN_ON(!tegra_cpu_rail_off_पढ़ोy()))
		वापस -EBUSY;

	/*
	 * L2 cache disabling using kernel API only allowed when all
	 * secondary CPU's are offline. Cache have to be disabled with
	 * MMU-on अगर cache मुख्यtenance is करोne via Trusted Foundations
	 * firmware. Note that CPUIDLE won't ever enter घातergate on Tegra30
	 * अगर any of secondary CPU's is online and this is the LP2-idle
	 * code-path only क्रम Tegra20/30.
	 */
#अगर_घोषित CONFIG_OUTER_CACHE
	अगर (trusted_foundations_रेजिस्टरed() && outer_cache.disable)
		outer_cache.disable();
#पूर्ण_अगर
	/*
	 * Note that besides of setting up CPU reset vector this firmware
	 * call may also करो the following, depending on the FW version:
	 *  1) Disable L2. But this करोesn't matter since we alपढ़ोy
	 *     disabled the L2.
	 *  2) Disable D-cache. This need to be taken पूर्णांकo account in
	 *     particular by the tegra_disable_clean_inv_dcache() which
	 *     shall aव्योम the re-disable.
	 */
	call_firmware_op(prepare_idle, TF_PM_MODE_LP2);

	setup_mm_क्रम_reboot();
	tegra_sleep_cpu_finish(v2p);

	/* should never here */
	BUG();

	वापस 0;
पूर्ण

अटल व्योम tegra_pm_set(क्रमागत tegra_suspend_mode mode)
अणु
	u32 value;

	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
	हाल TEGRA30:
		अवरोध;
	शेष:
		/* Turn off CRAIL */
		value = flowctrl_पढ़ो_cpu_csr(0);
		value &= ~FLOW_CTRL_CSR_ENABLE_EXT_MASK;
		value |= FLOW_CTRL_CSR_ENABLE_EXT_CRAIL;
		flowctrl_ग_लिखो_cpu_csr(0, value);
		अवरोध;
	पूर्ण

	tegra_pmc_enter_suspend_mode(mode);
पूर्ण

पूर्णांक tegra_pm_enter_lp2(व्योम)
अणु
	पूर्णांक err;

	tegra_pm_set(TEGRA_SUSPEND_LP2);

	cpu_cluster_pm_enter();
	suspend_cpu_complex();

	err = cpu_suspend(PHYS_OFFSET - PAGE_OFFSET, &tegra_sleep_cpu);

	/*
	 * Resume L2 cache अगर it wasn't re-enabled early during resume,
	 * which is the हाल क्रम Tegra30 that has to re-enable the cache
	 * via firmware call. In other हालs cache is alपढ़ोy enabled and
	 * hence re-enabling is a no-op. This is always a no-op on Tegra114+.
	 */
	outer_resume();

	restore_cpu_complex();
	cpu_cluster_pm_निकास();

	call_firmware_op(prepare_idle, TF_PM_MODE_NONE);

	वापस err;
पूर्ण

क्रमागत tegra_suspend_mode tegra_pm_validate_suspend_mode(
				क्रमागत tegra_suspend_mode mode)
अणु
	/*
	 * The Tegra devices support suspending to LP1 or lower currently.
	 */
	अगर (mode > TEGRA_SUSPEND_LP1)
		वापस TEGRA_SUSPEND_LP1;

	वापस mode;
पूर्ण

अटल पूर्णांक tegra_sleep_core(अचिन्हित दीर्घ v2p)
अणु
	/*
	 * Cache have to be disabled with MMU-on अगर cache मुख्यtenance is करोne
	 * via Trusted Foundations firmware. This is a no-op on Tegra114+.
	 */
	अगर (trusted_foundations_रेजिस्टरed())
		outer_disable();

	call_firmware_op(prepare_idle, TF_PM_MODE_LP1);

	setup_mm_क्रम_reboot();
	tegra_sleep_core_finish(v2p);

	/* should never here */
	BUG();

	वापस 0;
पूर्ण

/*
 * tegra_lp1_iram_hook
 *
 * Hooking the address of LP1 reset vector and SDRAM self-refresh code in
 * SDRAM. These codes not be copied to IRAM in this fuction. We need to
 * copy these code to IRAM beक्रमe LP0/LP1 suspend and restore the content
 * of IRAM after resume.
 */
अटल bool tegra_lp1_iram_hook(व्योम)
अणु
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC))
			tegra20_lp1_iram_hook();
		अवरोध;
	हाल TEGRA30:
	हाल TEGRA114:
	हाल TEGRA124:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC))
			tegra30_lp1_iram_hook();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!tegra_lp1_iram.start_addr || !tegra_lp1_iram.end_addr)
		वापस false;

	iram_save_size = tegra_lp1_iram.end_addr - tegra_lp1_iram.start_addr;
	iram_save_addr = kदो_स्मृति(iram_save_size, GFP_KERNEL);
	अगर (!iram_save_addr)
		वापस false;

	वापस true;
पूर्ण

अटल bool tegra_sleep_core_init(व्योम)
अणु
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC))
			tegra20_sleep_core_init();
		अवरोध;
	हाल TEGRA30:
	हाल TEGRA114:
	हाल TEGRA124:
		अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) ||
		    IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC))
			tegra30_sleep_core_init();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!tegra_sleep_core_finish)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम tegra_suspend_enter_lp1(व्योम)
अणु
	/* copy the reset vector & SDRAM shutकरोwn code पूर्णांकo IRAM */
	स_नकल(iram_save_addr, IO_ADDRESS(TEGRA_IRAM_LPx_RESUME_AREA),
		iram_save_size);
	स_नकल(IO_ADDRESS(TEGRA_IRAM_LPx_RESUME_AREA),
		tegra_lp1_iram.start_addr, iram_save_size);

	*((u32 *)tegra_cpu_lp1_mask) = 1;
पूर्ण

अटल व्योम tegra_suspend_निकास_lp1(व्योम)
अणु
	/* restore IRAM */
	स_नकल(IO_ADDRESS(TEGRA_IRAM_LPx_RESUME_AREA), iram_save_addr,
		iram_save_size);

	*(u32 *)tegra_cpu_lp1_mask = 0;
पूर्ण

अटल स्थिर अक्षर *lp_state[TEGRA_MAX_SUSPEND_MODE] = अणु
	[TEGRA_SUSPEND_NONE] = "none",
	[TEGRA_SUSPEND_LP2] = "LP2",
	[TEGRA_SUSPEND_LP1] = "LP1",
	[TEGRA_SUSPEND_LP0] = "LP0",
पूर्ण;

अटल पूर्णांक tegra_suspend_enter(suspend_state_t state)
अणु
	क्रमागत tegra_suspend_mode mode = tegra_pmc_get_suspend_mode();

	अगर (WARN_ON(mode < TEGRA_SUSPEND_NONE ||
		    mode >= TEGRA_MAX_SUSPEND_MODE))
		वापस -EINVAL;

	pr_info("Entering suspend state %s\n", lp_state[mode]);

	tegra_pm_set(mode);

	local_fiq_disable();

	suspend_cpu_complex();
	चयन (mode) अणु
	हाल TEGRA_SUSPEND_LP1:
		tegra_suspend_enter_lp1();
		अवरोध;
	हाल TEGRA_SUSPEND_LP2:
		tegra_pm_set_cpu_in_lp2();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cpu_suspend(PHYS_OFFSET - PAGE_OFFSET, tegra_sleep_func);

	/*
	 * Resume L2 cache अगर it wasn't re-enabled early during resume,
	 * which is the हाल क्रम Tegra30 that has to re-enable the cache
	 * via firmware call. In other हालs cache is alपढ़ोy enabled and
	 * hence re-enabling is a no-op.
	 */
	outer_resume();

	चयन (mode) अणु
	हाल TEGRA_SUSPEND_LP1:
		tegra_suspend_निकास_lp1();
		अवरोध;
	हाल TEGRA_SUSPEND_LP2:
		tegra_pm_clear_cpu_in_lp2();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	restore_cpu_complex();

	local_fiq_enable();

	call_firmware_op(prepare_idle, TF_PM_MODE_NONE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops tegra_suspend_ops = अणु
	.valid		= suspend_valid_only_mem,
	.enter		= tegra_suspend_enter,
पूर्ण;

व्योम __init tegra_init_suspend(व्योम)
अणु
	क्रमागत tegra_suspend_mode mode = tegra_pmc_get_suspend_mode();

	अगर (mode == TEGRA_SUSPEND_NONE)
		वापस;

	tegra_tear_करोwn_cpu_init();

	अगर (mode >= TEGRA_SUSPEND_LP1) अणु
		अगर (!tegra_lp1_iram_hook() || !tegra_sleep_core_init()) अणु
			pr_err("%s: unable to allocate memory for SDRAM"
			       "self-refresh -- LP0/LP1 unavailable\n",
			       __func__);
			tegra_pmc_set_suspend_mode(TEGRA_SUSPEND_LP2);
			mode = TEGRA_SUSPEND_LP2;
		पूर्ण
	पूर्ण

	/* set up sleep function क्रम cpu_suspend */
	चयन (mode) अणु
	हाल TEGRA_SUSPEND_LP1:
		tegra_sleep_func = tegra_sleep_core;
		अवरोध;
	हाल TEGRA_SUSPEND_LP2:
		tegra_sleep_func = tegra_sleep_cpu;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	suspend_set_ops(&tegra_suspend_ops);
पूर्ण

पूर्णांक tegra_pm_park_secondary_cpu(अचिन्हित दीर्घ cpu)
अणु
	अगर (cpu > 0) अणु
		tegra_disable_clean_inv_dcache(TEGRA_FLUSH_CACHE_LOUIS);

		अगर (tegra_get_chip_id() == TEGRA20)
			tegra20_hotplug_shutकरोwn();
		अन्यथा
			tegra30_hotplug_shutकरोwn();
	पूर्ण

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
