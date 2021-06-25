<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/cpuidle34xx.c
 *
 * OMAP3 CPU IDLE Routines
 *
 * Copyright (C) 2008 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Karthik Dasu <karthik-dp@ti.com>
 *
 * Copyright (C) 2006 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 *
 * Copyright (C) 2005 Texas Instruments, Inc.
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *
 * Based on pm.c क्रम omap2
 */

#समावेश <linux/sched.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/export.h>
#समावेश <linux/cpu_pm.h>
#समावेश <यंत्र/cpuidle.h>

#समावेश "powerdomain.h"
#समावेश "clockdomain.h"

#समावेश "pm.h"
#समावेश "control.h"
#समावेश "common.h"
#समावेश "soc.h"

/* Mach specअगरic inक्रमmation to be recorded in the C-state driver_data */
काष्ठा omap3_idle_statedata अणु
	u8 mpu_state;
	u8 core_state;
	u8 per_min_state;
	u8 flags;
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *mpu_pd, *core_pd, *per_pd, *cam_pd;

/*
 * Possible flag bits क्रम काष्ठा omap3_idle_statedata.flags:
 *
 * OMAP_CPUIDLE_CX_NO_CLKDM_IDLE: करोn't allow the MPU घड़ीकरोमुख्य to go
 *    inactive.  This in turn prevents the MPU DPLL from entering स्वतःidle
 *    mode, so wakeup latency is greatly reduced, at the cost of additional
 *    energy consumption.  This also prevents the CORE घड़ीकरोमुख्य from
 *    entering idle.
 */
#घोषणा OMAP_CPUIDLE_CX_NO_CLKDM_IDLE		BIT(0)

/*
 * Prevent PER OFF अगर CORE is not in RETention or OFF as this would
 * disable PER wakeups completely.
 */
अटल काष्ठा omap3_idle_statedata omap3_idle_data[] = अणु
	अणु
		.mpu_state = PWRDM_POWER_ON,
		.core_state = PWRDM_POWER_ON,
		/* In C1 करो not allow PER state lower than CORE state */
		.per_min_state = PWRDM_POWER_ON,
		.flags = OMAP_CPUIDLE_CX_NO_CLKDM_IDLE,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_ON,
		.core_state = PWRDM_POWER_ON,
		.per_min_state = PWRDM_POWER_RET,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_RET,
		.core_state = PWRDM_POWER_ON,
		.per_min_state = PWRDM_POWER_RET,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_OFF,
		.core_state = PWRDM_POWER_ON,
		.per_min_state = PWRDM_POWER_RET,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_RET,
		.core_state = PWRDM_POWER_RET,
		.per_min_state = PWRDM_POWER_OFF,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_OFF,
		.core_state = PWRDM_POWER_RET,
		.per_min_state = PWRDM_POWER_OFF,
	पूर्ण,
	अणु
		.mpu_state = PWRDM_POWER_OFF,
		.core_state = PWRDM_POWER_OFF,
		.per_min_state = PWRDM_POWER_OFF,
	पूर्ण,
पूर्ण;

/**
 * omap3_enter_idle - Programs OMAP3 to enter the specअगरied state
 * @dev: cpuidle device
 * @drv: cpuidle driver
 * @index: the index of state to be entered
 */
अटल पूर्णांक omap3_enter_idle(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv,
			    पूर्णांक index)
अणु
	काष्ठा omap3_idle_statedata *cx = &omap3_idle_data[index];
	पूर्णांक error;

	अगर (omap_irq_pending() || need_resched())
		जाओ वापस_sleep_समय;

	/* Deny idle क्रम C1 */
	अगर (cx->flags & OMAP_CPUIDLE_CX_NO_CLKDM_IDLE) अणु
		clkdm_deny_idle(mpu_pd->pwrdm_clkdms[0]);
	पूर्ण अन्यथा अणु
		pwrdm_set_next_pwrst(mpu_pd, cx->mpu_state);
		pwrdm_set_next_pwrst(core_pd, cx->core_state);
	पूर्ण

	/*
	 * Call idle CPU PM enter notअगरier chain so that
	 * VFP context is saved.
	 */
	अगर (cx->mpu_state == PWRDM_POWER_OFF) अणु
		error = cpu_pm_enter();
		अगर (error)
			जाओ out_clkdm_set;
	पूर्ण

	/* Execute ARM wfi */
	omap_sram_idle();

	/*
	 * Call idle CPU PM enter notअगरier chain to restore
	 * VFP context.
	 */
	अगर (cx->mpu_state == PWRDM_POWER_OFF &&
	    pwrdm_पढ़ो_prev_pwrst(mpu_pd) == PWRDM_POWER_OFF)
		cpu_pm_निकास();

out_clkdm_set:
	/* Re-allow idle क्रम C1 */
	अगर (cx->flags & OMAP_CPUIDLE_CX_NO_CLKDM_IDLE)
		clkdm_allow_idle(mpu_pd->pwrdm_clkdms[0]);

वापस_sleep_समय:

	वापस index;
पूर्ण

/**
 * next_valid_state - Find next valid C-state
 * @dev: cpuidle device
 * @drv: cpuidle driver
 * @index: Index of currently selected c-state
 *
 * If the state corresponding to index is valid, index is वापसed back
 * to the caller. Else, this function searches क्रम a lower c-state which is
 * still valid (as defined in omap3_घातer_states[]) and वापसs its index.
 *
 * A state is valid अगर the 'valid' field is enabled and
 * अगर it satisfies the enable_off_mode condition.
 */
अटल पूर्णांक next_valid_state(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा omap3_idle_statedata *cx = &omap3_idle_data[index];
	u32 mpu_deepest_state = PWRDM_POWER_RET;
	u32 core_deepest_state = PWRDM_POWER_RET;
	पूर्णांक idx;
	पूर्णांक next_index = 0; /* C1 is the शेष value */

	अगर (enable_off_mode) अणु
		mpu_deepest_state = PWRDM_POWER_OFF;
		/*
		 * Erratum i583: valable क्रम ES rev < Es1.2 on 3630.
		 * CORE OFF mode is not supported in a stable क्रमm, restrict
		 * instead the CORE state to RET.
		 */
		अगर (!IS_PM34XX_ERRATUM(PM_SDRC_WAKEUP_ERRATUM_i583))
			core_deepest_state = PWRDM_POWER_OFF;
	पूर्ण

	/* Check अगर current state is valid */
	अगर ((cx->mpu_state >= mpu_deepest_state) &&
	    (cx->core_state >= core_deepest_state))
		वापस index;

	/*
	 * Drop to next valid state.
	 * Start search from the next (lower) state.
	 */
	क्रम (idx = index - 1; idx >= 0; idx--) अणु
		cx = &omap3_idle_data[idx];
		अगर ((cx->mpu_state >= mpu_deepest_state) &&
		    (cx->core_state >= core_deepest_state)) अणु
			next_index = idx;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस next_index;
पूर्ण

/**
 * omap3_enter_idle_bm - Checks क्रम any bus activity
 * @dev: cpuidle device
 * @drv: cpuidle driver
 * @index: array index of target state to be programmed
 *
 * This function checks क्रम any pending activity and then programs
 * the device to the specअगरied or a safer state.
 */
अटल पूर्णांक omap3_enter_idle_bm(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv,
			       पूर्णांक index)
अणु
	पूर्णांक new_state_idx, ret;
	u8 per_next_state, per_saved_state;
	काष्ठा omap3_idle_statedata *cx;

	/*
	 * Use only C1 अगर CAM is active.
	 * CAM करोes not have wakeup capability in OMAP3.
	 */
	अगर (pwrdm_पढ़ो_pwrst(cam_pd) == PWRDM_POWER_ON)
		new_state_idx = drv->safe_state_index;
	अन्यथा
		new_state_idx = next_valid_state(dev, drv, index);

	/*
	 * FIXME: we currently manage device-specअगरic idle states
	 *        क्रम PER and CORE in combination with CPU-specअगरic
	 *        idle states.  This is wrong, and device-specअगरic
	 *        idle management needs to be separated out पूर्णांकo
	 *        its own code.
	 */

	/* Program PER state */
	cx = &omap3_idle_data[new_state_idx];

	per_next_state = pwrdm_पढ़ो_next_pwrst(per_pd);
	per_saved_state = per_next_state;
	अगर (per_next_state < cx->per_min_state) अणु
		per_next_state = cx->per_min_state;
		pwrdm_set_next_pwrst(per_pd, per_next_state);
	पूर्ण

	ret = omap3_enter_idle(dev, drv, new_state_idx);

	/* Restore original PER state अगर it was modअगरied */
	अगर (per_next_state != per_saved_state)
		pwrdm_set_next_pwrst(per_pd, per_saved_state);

	वापस ret;
पूर्ण

अटल काष्ठा cpuidle_driver omap3_idle_driver = अणु
	.name             = "omap3_idle",
	.owner            = THIS_MODULE,
	.states = अणु
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 2 + 2,
			.target_residency = 5,
			.name		  = "C1",
			.desc		  = "MPU ON + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 10 + 10,
			.target_residency = 30,
			.name		  = "C2",
			.desc		  = "MPU ON + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 50 + 50,
			.target_residency = 300,
			.name		  = "C3",
			.desc		  = "MPU RET + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 1500 + 1800,
			.target_residency = 4000,
			.name		  = "C4",
			.desc		  = "MPU OFF + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 2500 + 7500,
			.target_residency = 12000,
			.name		  = "C5",
			.desc		  = "MPU RET + CORE RET",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 3000 + 8500,
			.target_residency = 15000,
			.name		  = "C6",
			.desc		  = "MPU OFF + CORE RET",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 10000 + 30000,
			.target_residency = 30000,
			.name		  = "C7",
			.desc		  = "MPU OFF + CORE OFF",
		पूर्ण,
	पूर्ण,
	.state_count = ARRAY_SIZE(omap3_idle_data),
	.safe_state_index = 0,
पूर्ण;

/*
 * Numbers based on measurements made in October 2009 क्रम PM optimized kernel
 * with CPU freq enabled on device Nokia N900. Assumes OPP2 (मुख्य idle OPP,
 * and worst हाल latencies).
 */
अटल काष्ठा cpuidle_driver omap3430_idle_driver = अणु
	.name             = "omap3430_idle",
	.owner            = THIS_MODULE,
	.states = अणु
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 110 + 162,
			.target_residency = 5,
			.name		  = "C1",
			.desc		  = "MPU ON + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 106 + 180,
			.target_residency = 309,
			.name		  = "C2",
			.desc		  = "MPU ON + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 107 + 410,
			.target_residency = 46057,
			.name		  = "C3",
			.desc		  = "MPU RET + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 121 + 3374,
			.target_residency = 46057,
			.name		  = "C4",
			.desc		  = "MPU OFF + CORE ON",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 855 + 1146,
			.target_residency = 46057,
			.name		  = "C5",
			.desc		  = "MPU RET + CORE RET",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 7580 + 4134,
			.target_residency = 484329,
			.name		  = "C6",
			.desc		  = "MPU OFF + CORE RET",
		पूर्ण,
		अणु
			.enter		  = omap3_enter_idle_bm,
			.निकास_latency	  = 7505 + 15274,
			.target_residency = 484329,
			.name		  = "C7",
			.desc		  = "MPU OFF + CORE OFF",
		पूर्ण,
	पूर्ण,
	.state_count = ARRAY_SIZE(omap3_idle_data),
	.safe_state_index = 0,
पूर्ण;

/* Public functions */

/**
 * omap3_idle_init - Init routine क्रम OMAP3 idle
 *
 * Registers the OMAP3 specअगरic cpuidle driver to the cpuidle
 * framework with the valid set of states.
 */
पूर्णांक __init omap3_idle_init(व्योम)
अणु
	mpu_pd = pwrdm_lookup("mpu_pwrdm");
	core_pd = pwrdm_lookup("core_pwrdm");
	per_pd = pwrdm_lookup("per_pwrdm");
	cam_pd = pwrdm_lookup("cam_pwrdm");

	अगर (!mpu_pd || !core_pd || !per_pd || !cam_pd)
		वापस -ENODEV;

	अगर (cpu_is_omap3430())
		वापस cpuidle_रेजिस्टर(&omap3430_idle_driver, शून्य);
	अन्यथा
		वापस cpuidle_रेजिस्टर(&omap3_idle_driver, शून्य);
पूर्ण
