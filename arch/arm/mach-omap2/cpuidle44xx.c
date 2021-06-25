<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4+ CPU idle Routines
 *
 * Copyright (C) 2011-2013 Texas Instruments, Inc.
 * Santosh Shilimkar <santosh.shilimkar@ti.com>
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/export.h>
#समावेश <linux/tick.h>

#समावेश <यंत्र/cpuidle.h>

#समावेश "common.h"
#समावेश "pm.h"
#समावेश "prm.h"
#समावेश "soc.h"
#समावेश "clockdomain.h"

#घोषणा MAX_CPUS	2

/* Machine specअगरic inक्रमmation */
काष्ठा idle_statedata अणु
	u32 cpu_state;
	u32 mpu_logic_state;
	u32 mpu_state;
	u32 mpu_state_vote;
पूर्ण;

अटल काष्ठा idle_statedata omap4_idle_data[] = अणु
	अणु
		.cpu_state = PWRDM_POWER_ON,
		.mpu_state = PWRDM_POWER_ON,
		.mpu_logic_state = PWRDM_POWER_RET,
	पूर्ण,
	अणु
		.cpu_state = PWRDM_POWER_OFF,
		.mpu_state = PWRDM_POWER_RET,
		.mpu_logic_state = PWRDM_POWER_RET,
	पूर्ण,
	अणु
		.cpu_state = PWRDM_POWER_OFF,
		.mpu_state = PWRDM_POWER_RET,
		.mpu_logic_state = PWRDM_POWER_OFF,
	पूर्ण,
पूर्ण;

अटल काष्ठा idle_statedata omap5_idle_data[] = अणु
	अणु
		.cpu_state = PWRDM_POWER_ON,
		.mpu_state = PWRDM_POWER_ON,
		.mpu_logic_state = PWRDM_POWER_ON,
	पूर्ण,
	अणु
		.cpu_state = PWRDM_POWER_RET,
		.mpu_state = PWRDM_POWER_RET,
		.mpu_logic_state = PWRDM_POWER_RET,
	पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *mpu_pd, *cpu_pd[MAX_CPUS];
अटल काष्ठा घड़ीकरोमुख्य *cpu_clkdm[MAX_CPUS];

अटल atomic_t पात_barrier;
अटल bool cpu_करोne[MAX_CPUS];
अटल काष्ठा idle_statedata *state_ptr = &omap4_idle_data[0];
अटल DEFINE_RAW_SPINLOCK(mpu_lock);

/* Private functions */

/**
 * omap_enter_idle_[simple/coupled] - OMAP4PLUS cpuidle entry functions
 * @dev: cpuidle device
 * @drv: cpuidle driver
 * @index: the index of state to be entered
 *
 * Called from the CPUidle framework to program the device to the
 * specअगरied low घातer state selected by the governor.
 * Returns the amount of समय spent in the low घातer state.
 */
अटल पूर्णांक omap_enter_idle_simple(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			पूर्णांक index)
अणु
	omap_करो_wfi();
	वापस index;
पूर्ण

अटल पूर्णांक omap_enter_idle_smp(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv,
			       पूर्णांक index)
अणु
	काष्ठा idle_statedata *cx = state_ptr + index;
	अचिन्हित दीर्घ flag;

	raw_spin_lock_irqsave(&mpu_lock, flag);
	cx->mpu_state_vote++;
	अगर (cx->mpu_state_vote == num_online_cpus()) अणु
		pwrdm_set_logic_retst(mpu_pd, cx->mpu_logic_state);
		omap_set_pwrdm_state(mpu_pd, cx->mpu_state);
	पूर्ण
	raw_spin_unlock_irqrestore(&mpu_lock, flag);

	omap4_enter_lowघातer(dev->cpu, cx->cpu_state);

	raw_spin_lock_irqsave(&mpu_lock, flag);
	अगर (cx->mpu_state_vote == num_online_cpus())
		omap_set_pwrdm_state(mpu_pd, PWRDM_POWER_ON);
	cx->mpu_state_vote--;
	raw_spin_unlock_irqrestore(&mpu_lock, flag);

	वापस index;
पूर्ण

अटल पूर्णांक omap_enter_idle_coupled(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			पूर्णांक index)
अणु
	काष्ठा idle_statedata *cx = state_ptr + index;
	u32 mpuss_can_lose_context = 0;
	पूर्णांक error;

	/*
	 * CPU0 has to रुको and stay ON until CPU1 is OFF state.
	 * This is necessary to honour hardware recommondation
	 * of triggeing all the possible low घातer modes once CPU1 is
	 * out of coherency and in OFF mode.
	 */
	अगर (dev->cpu == 0 && cpumask_test_cpu(1, cpu_online_mask)) अणु
		जबतक (pwrdm_पढ़ो_pwrst(cpu_pd[1]) != PWRDM_POWER_OFF) अणु
			cpu_relax();

			/*
			 * CPU1 could have alपढ़ोy entered & निकासed idle
			 * without hitting off because of a wakeup
			 * or a failed attempt to hit off mode.  Check क्रम
			 * that here, otherwise we could spin क्रमever
			 * रुकोing क्रम CPU1 off.
			 */
			अगर (cpu_करोne[1])
			    जाओ fail;

		पूर्ण
	पूर्ण

	mpuss_can_lose_context = (cx->mpu_state == PWRDM_POWER_RET) &&
				 (cx->mpu_logic_state == PWRDM_POWER_OFF);

	/* Enter broadcast mode क्रम periodic समयrs */
	RCU_NONIDLE(tick_broadcast_enable());

	/* Enter broadcast mode क्रम one-shot समयrs */
	RCU_NONIDLE(tick_broadcast_enter());

	/*
	 * Call idle CPU PM enter notअगरier chain so that
	 * VFP and per CPU पूर्णांकerrupt context is saved.
	 */
	error = cpu_pm_enter();
	अगर (error)
		जाओ cpu_pm_out;

	अगर (dev->cpu == 0) अणु
		pwrdm_set_logic_retst(mpu_pd, cx->mpu_logic_state);
		RCU_NONIDLE(omap_set_pwrdm_state(mpu_pd, cx->mpu_state));

		/*
		 * Call idle CPU cluster PM enter notअगरier chain
		 * to save GIC and wakeupgen context.
		 */
		अगर (mpuss_can_lose_context) अणु
			error = cpu_cluster_pm_enter();
			अगर (error) अणु
				index = 0;
				cx = state_ptr + index;
				pwrdm_set_logic_retst(mpu_pd, cx->mpu_logic_state);
				RCU_NONIDLE(omap_set_pwrdm_state(mpu_pd, cx->mpu_state));
				mpuss_can_lose_context = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	omap4_enter_lowघातer(dev->cpu, cx->cpu_state);
	cpu_करोne[dev->cpu] = true;

	/* Wakeup CPU1 only अगर it is not offlined */
	अगर (dev->cpu == 0 && cpumask_test_cpu(1, cpu_online_mask)) अणु

		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD) &&
		    mpuss_can_lose_context)
			gic_dist_disable();

		RCU_NONIDLE(clkdm_deny_idle(cpu_clkdm[1]));
		RCU_NONIDLE(omap_set_pwrdm_state(cpu_pd[1], PWRDM_POWER_ON));
		RCU_NONIDLE(clkdm_allow_idle(cpu_clkdm[1]));

		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD) &&
		    mpuss_can_lose_context) अणु
			जबतक (gic_dist_disabled()) अणु
				udelay(1);
				cpu_relax();
			पूर्ण
			gic_समयr_retrigger();
		पूर्ण
	पूर्ण

	/*
	 * Call idle CPU cluster PM निकास notअगरier chain
	 * to restore GIC and wakeupgen context.
	 */
	अगर (dev->cpu == 0 && mpuss_can_lose_context)
		cpu_cluster_pm_निकास();

	/*
	 * Call idle CPU PM निकास notअगरier chain to restore
	 * VFP and per CPU IRQ context.
	 */
	cpu_pm_निकास();

cpu_pm_out:
	RCU_NONIDLE(tick_broadcast_निकास());

fail:
	cpuidle_coupled_parallel_barrier(dev, &पात_barrier);
	cpu_करोne[dev->cpu] = false;

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver omap4_idle_driver = अणु
	.name				= "omap4_idle",
	.owner				= THIS_MODULE,
	.states = अणु
		अणु
			/* C1 - CPU0 ON + CPU1 ON + MPU ON */
			.निकास_latency = 2 + 2,
			.target_residency = 5,
			.enter = omap_enter_idle_simple,
			.name = "C1",
			.desc = "CPUx ON, MPUSS ON"
		पूर्ण,
		अणु
			/* C2 - CPU0 OFF + CPU1 OFF + MPU CSWR */
			.निकास_latency = 328 + 440,
			.target_residency = 960,
			.flags = CPUIDLE_FLAG_COUPLED,
			.enter = omap_enter_idle_coupled,
			.name = "C2",
			.desc = "CPUx OFF, MPUSS CSWR",
		पूर्ण,
		अणु
			/* C3 - CPU0 OFF + CPU1 OFF + MPU OSWR */
			.निकास_latency = 460 + 518,
			.target_residency = 1100,
			.flags = CPUIDLE_FLAG_COUPLED,
			.enter = omap_enter_idle_coupled,
			.name = "C3",
			.desc = "CPUx OFF, MPUSS OSWR",
		पूर्ण,
	पूर्ण,
	.state_count = ARRAY_SIZE(omap4_idle_data),
	.safe_state_index = 0,
पूर्ण;

अटल काष्ठा cpuidle_driver omap5_idle_driver = अणु
	.name				= "omap5_idle",
	.owner				= THIS_MODULE,
	.states = अणु
		अणु
			/* C1 - CPU0 ON + CPU1 ON + MPU ON */
			.निकास_latency = 2 + 2,
			.target_residency = 5,
			.enter = omap_enter_idle_simple,
			.name = "C1",
			.desc = "CPUx WFI, MPUSS ON"
		पूर्ण,
		अणु
			/* C2 - CPU0 RET + CPU1 RET + MPU CSWR */
			.निकास_latency = 48 + 60,
			.target_residency = 100,
			.flags = CPUIDLE_FLAG_TIMER_STOP,
			.enter = omap_enter_idle_smp,
			.name = "C2",
			.desc = "CPUx CSWR, MPUSS CSWR",
		पूर्ण,
	पूर्ण,
	.state_count = ARRAY_SIZE(omap5_idle_data),
	.safe_state_index = 0,
पूर्ण;

/* Public functions */

/**
 * omap4_idle_init - Init routine क्रम OMAP4+ idle
 *
 * Registers the OMAP4+ specअगरic cpuidle driver to the cpuidle
 * framework with the valid set of states.
 */
पूर्णांक __init omap4_idle_init(व्योम)
अणु
	काष्ठा cpuidle_driver *idle_driver;

	अगर (soc_is_omap54xx()) अणु
		state_ptr = &omap5_idle_data[0];
		idle_driver = &omap5_idle_driver;
	पूर्ण अन्यथा अणु
		state_ptr = &omap4_idle_data[0];
		idle_driver = &omap4_idle_driver;
	पूर्ण

	mpu_pd = pwrdm_lookup("mpu_pwrdm");
	cpu_pd[0] = pwrdm_lookup("cpu0_pwrdm");
	cpu_pd[1] = pwrdm_lookup("cpu1_pwrdm");
	अगर ((!mpu_pd) || (!cpu_pd[0]) || (!cpu_pd[1]))
		वापस -ENODEV;

	cpu_clkdm[0] = clkdm_lookup("mpu0_clkdm");
	cpu_clkdm[1] = clkdm_lookup("mpu1_clkdm");
	अगर (!cpu_clkdm[0] || !cpu_clkdm[1])
		वापस -ENODEV;

	वापस cpuidle_रेजिस्टर(idle_driver, cpu_online_mask);
पूर्ण
