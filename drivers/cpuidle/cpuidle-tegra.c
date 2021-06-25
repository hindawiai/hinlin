<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU idle driver क्रम Tegra CPUs
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 * Copyright (c) 2011 Google, Inc.
 * Author: Colin Cross <ccross@android.com>
 *         Gary King <gking@nvidia.com>
 *
 * Rework क्रम 3.3 by Peter De Schrijver <pdeschrijver@nvidia.com>
 *
 * Tegra20/124 driver unअगरication by Dmitry Osipenko <digetx@gmail.com>
 */

#घोषणा pr_fmt(fmt)	"tegra-cpuidle: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <linux/clk/tegra.h>
#समावेश <linux/firmware/trusted_foundations.h>

#समावेश <soc/tegra/cpuidle.h>
#समावेश <soc/tegra/flowctrl.h>
#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/irq.h>
#समावेश <soc/tegra/pm.h>
#समावेश <soc/tegra/pmc.h>

#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

क्रमागत tegra_state अणु
	TEGRA_C1,
	TEGRA_C7,
	TEGRA_CC6,
	TEGRA_STATE_COUNT,
पूर्ण;

अटल atomic_t tegra_idle_barrier;
अटल atomic_t tegra_पात_flag;

अटल व्योम tegra_cpuidle_report_cpus_state(व्योम)
अणु
	अचिन्हित दीर्घ cpu, lcpu, csr;

	क्रम_each_cpu(lcpu, cpu_possible_mask) अणु
		cpu = cpu_logical_map(lcpu);
		csr = flowctrl_पढ़ो_cpu_csr(cpu);

		pr_err("cpu%lu: online=%d flowctrl_csr=0x%08lx\n",
		       cpu, cpu_online(lcpu), csr);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_cpuidle_रुको_क्रम_secondary_cpus_parking(व्योम)
अणु
	अचिन्हित पूर्णांक retries = 3;

	जबतक (retries--) अणु
		अचिन्हित पूर्णांक delay_us = 10;
		अचिन्हित पूर्णांक समयout_us = 500 * 1000 / delay_us;

		/*
		 * The primary CPU0 core shall रुको क्रम the secondaries
		 * shutकरोwn in order to घातer-off CPU's cluster safely.
		 * The समयout value depends on the current CPU frequency,
		 * it takes about 40-150us in average and over 1000us in
		 * a worst हाल scenario.
		 */
		करो अणु
			अगर (tegra_cpu_rail_off_पढ़ोy())
				वापस 0;

			udelay(delay_us);

		पूर्ण जबतक (समयout_us--);

		pr_err("secondary CPU taking too long to park\n");

		tegra_cpuidle_report_cpus_state();
	पूर्ण

	pr_err("timed out waiting secondaries to park\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_cpuidle_unpark_secondary_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, lcpu;

	क्रम_each_cpu(lcpu, cpu_online_mask) अणु
		cpu = cpu_logical_map(lcpu);

		अगर (cpu > 0) अणु
			tegra_enable_cpu_घड़ी(cpu);
			tegra_cpu_out_of_reset(cpu);
			flowctrl_ग_लिखो_cpu_halt(cpu, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_cpuidle_cc6_enter(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret;

	अगर (cpu > 0) अणु
		ret = cpu_suspend(cpu, tegra_pm_park_secondary_cpu);
	पूर्ण अन्यथा अणु
		ret = tegra_cpuidle_रुको_क्रम_secondary_cpus_parking();
		अगर (!ret)
			ret = tegra_pm_enter_lp2();

		tegra_cpuidle_unpark_secondary_cpus();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_cpuidle_c7_enter(व्योम)
अणु
	पूर्णांक err;

	err = call_firmware_op(prepare_idle, TF_PM_MODE_LP2_NOFLUSH_L2);
	अगर (err && err != -ENOSYS)
		वापस err;

	वापस cpu_suspend(0, tegra30_pm_secondary_cpu_suspend);
पूर्ण

अटल पूर्णांक tegra_cpuidle_coupled_barrier(काष्ठा cpuidle_device *dev)
अणु
	अगर (tegra_pending_sgi()) अणु
		/*
		 * CPU got local पूर्णांकerrupt that will be lost after GIC's
		 * shutकरोwn because GIC driver करोesn't save/restore the
		 * pending SGI state across CPU cluster PM.  Abort and retry
		 * next समय.
		 */
		atomic_set(&tegra_पात_flag, 1);
	पूर्ण

	cpuidle_coupled_parallel_barrier(dev, &tegra_idle_barrier);

	अगर (atomic_पढ़ो(&tegra_पात_flag)) अणु
		cpuidle_coupled_parallel_barrier(dev, &tegra_idle_barrier);
		atomic_set(&tegra_पात_flag, 0);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_cpuidle_state_enter(काष्ठा cpuidle_device *dev,
				     पूर्णांक index, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;

	/*
	 * CC6 state is the "CPU cluster power-off" state.  In order to
	 * enter this state, at first the secondary CPU cores need to be
	 * parked पूर्णांकo offline mode, then the last CPU should clean out
	 * reमुख्यing dirty cache lines पूर्णांकo DRAM and trigger Flow Controller
	 * logic that turns off the cluster's घातer करोमुख्य (which includes
	 * CPU cores, GIC and L2 cache).
	 */
	अगर (index == TEGRA_CC6) अणु
		err = tegra_cpuidle_coupled_barrier(dev);
		अगर (err)
			वापस err;
	पूर्ण

	local_fiq_disable();
	RCU_NONIDLE(tegra_pm_set_cpu_in_lp2());
	cpu_pm_enter();

	चयन (index) अणु
	हाल TEGRA_C7:
		err = tegra_cpuidle_c7_enter();
		अवरोध;

	हाल TEGRA_CC6:
		err = tegra_cpuidle_cc6_enter(cpu);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	cpu_pm_निकास();
	RCU_NONIDLE(tegra_pm_clear_cpu_in_lp2());
	local_fiq_enable();

	वापस err ?: index;
पूर्ण

अटल पूर्णांक tegra_cpuidle_adjust_state_index(पूर्णांक index, अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * On Tegra30 CPU0 can't be घातer-gated separately from secondary
	 * cores because it gates the whole CPU cluster.
	 */
	अगर (cpu > 0 || index != TEGRA_C7 || tegra_get_chip_id() != TEGRA30)
		वापस index;

	/* put CPU0 पूर्णांकo C1 अगर C7 is requested and secondaries are online */
	अगर (!IS_ENABLED(CONFIG_PM_SLEEP) || num_online_cpus() > 1)
		index = TEGRA_C1;
	अन्यथा
		index = TEGRA_CC6;

	वापस index;
पूर्ण

अटल पूर्णांक tegra_cpuidle_enter(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv,
			       पूर्णांक index)
अणु
	अचिन्हित पूर्णांक cpu = cpu_logical_map(dev->cpu);
	पूर्णांक ret;

	index = tegra_cpuidle_adjust_state_index(index, cpu);
	अगर (dev->states_usage[index].disable)
		वापस -1;

	अगर (index == TEGRA_C1)
		ret = arm_cpuidle_simple_enter(dev, drv, index);
	अन्यथा
		ret = tegra_cpuidle_state_enter(dev, index, cpu);

	अगर (ret < 0) अणु
		अगर (ret != -EINTR || index != TEGRA_CC6)
			pr_err_once("failed to enter state %d err: %d\n",
				    index, ret);
		index = -1;
	पूर्ण अन्यथा अणु
		index = ret;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक tegra114_enter_s2idle(काष्ठा cpuidle_device *dev,
				 काष्ठा cpuidle_driver *drv,
				 पूर्णांक index)
अणु
	tegra_cpuidle_enter(dev, drv, index);

	वापस 0;
पूर्ण

/*
 * The previous versions of Tegra CPUIDLE driver used a dअगरferent "legacy"
 * terminology क्रम naming of the idling states, जबतक this driver uses the
 * new terminology.
 *
 * Mapping of the old terms पूर्णांकo the new ones:
 *
 * Old | New
 * ---------
 * LP3 | C1	(CPU core घड़ी gating)
 * LP2 | C7	(CPU core घातer gating)
 * LP2 | CC6	(CPU cluster घातer gating)
 *
 * Note that that the older CPUIDLE driver versions didn't explicitly
 * dअगरferentiate the LP2 states because these states either used the same
 * code path or because CC6 wasn't supported.
 */
अटल काष्ठा cpuidle_driver tegra_idle_driver = अणु
	.name = "tegra_idle",
	.states = अणु
		[TEGRA_C1] = ARM_CPUIDLE_WFI_STATE_PWR(600),
		[TEGRA_C7] = अणु
			.enter			= tegra_cpuidle_enter,
			.निकास_latency		= 2000,
			.target_residency	= 2200,
			.घातer_usage		= 100,
			.flags			= CPUIDLE_FLAG_TIMER_STOP,
			.name			= "C7",
			.desc			= "CPU core powered off",
		पूर्ण,
		[TEGRA_CC6] = अणु
			.enter			= tegra_cpuidle_enter,
			.निकास_latency		= 5000,
			.target_residency	= 10000,
			.घातer_usage		= 0,
			.flags			= CPUIDLE_FLAG_TIMER_STOP |
						  CPUIDLE_FLAG_COUPLED,
			.name			= "CC6",
			.desc			= "CPU cluster powered off",
		पूर्ण,
	पूर्ण,
	.state_count = TEGRA_STATE_COUNT,
	.safe_state_index = TEGRA_C1,
पूर्ण;

अटल अंतरभूत व्योम tegra_cpuidle_disable_state(क्रमागत tegra_state state)
अणु
	cpuidle_driver_state_disabled(&tegra_idle_driver, state, true);
पूर्ण

/*
 * Tegra20 HW appears to have a bug such that PCIe device पूर्णांकerrupts, whether
 * they are legacy IRQs or MSI, are lost when CC6 is enabled.  To work around
 * this, simply disable CC6 अगर the PCI driver and DT node are both enabled.
 */
व्योम tegra_cpuidle_pcie_irqs_in_use(व्योम)
अणु
	काष्ठा cpuidle_state *state_cc6 = &tegra_idle_driver.states[TEGRA_CC6];

	अगर ((state_cc6->flags & CPUIDLE_FLAG_UNUSABLE) ||
	    tegra_get_chip_id() != TEGRA20)
		वापस;

	pr_info("disabling CC6 state, since PCIe IRQs are in use\n");
	tegra_cpuidle_disable_state(TEGRA_CC6);
पूर्ण

अटल व्योम tegra_cpuidle_setup_tegra114_c7_state(व्योम)
अणु
	काष्ठा cpuidle_state *s = &tegra_idle_driver.states[TEGRA_C7];

	s->enter_s2idle = tegra114_enter_s2idle;
	s->target_residency = 1000;
	s->निकास_latency = 500;
पूर्ण

अटल पूर्णांक tegra_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* LP2 could be disabled in device-tree */
	अगर (tegra_pmc_get_suspend_mode() < TEGRA_SUSPEND_LP2)
		tegra_cpuidle_disable_state(TEGRA_CC6);

	/*
	 * Required suspend-resume functionality, which is provided by the
	 * Tegra-arch core and PMC driver, is unavailable अगर PM-sleep option
	 * is disabled.
	 */
	अगर (!IS_ENABLED(CONFIG_PM_SLEEP)) अणु
		tegra_cpuidle_disable_state(TEGRA_C7);
		tegra_cpuidle_disable_state(TEGRA_CC6);
	पूर्ण

	/*
	 * Generic WFI state (also known as C1 or LP3) and the coupled CPU
	 * cluster घातer-off (CC6 or LP2) states are common क्रम all Tegra SoCs.
	 */
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		/* Tegra20 isn't capable to घातer-off inभागidual CPU cores */
		tegra_cpuidle_disable_state(TEGRA_C7);
		अवरोध;

	हाल TEGRA30:
		अवरोध;

	हाल TEGRA114:
	हाल TEGRA124:
		tegra_cpuidle_setup_tegra114_c7_state();

		/* coupled CC6 (LP2) state isn't implemented yet */
		tegra_cpuidle_disable_state(TEGRA_CC6);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cpuidle_रेजिस्टर(&tegra_idle_driver, cpu_possible_mask);
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_cpuidle_driver = अणु
	.probe = tegra_cpuidle_probe,
	.driver = अणु
		.name = "tegra-cpuidle",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(tegra_cpuidle_driver);
