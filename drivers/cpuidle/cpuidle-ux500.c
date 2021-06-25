<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Linaro : Daniel Lezcano <daniel.lezcano@linaro.org> (IBM)
 *
 * Based on the work of Rickard Andersson <rickard.andersson@stericsson.com>
 * and Jonas Aaberg <jonas.aberg@stericsson.com>.
 */

#समावेश <linux/init.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/smp.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/platक्रमm_data/arm-ux500-pm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/cpuidle.h>

अटल atomic_t master = ATOMIC_INIT(0);
अटल DEFINE_SPINLOCK(master_lock);

अटल अंतरभूत पूर्णांक ux500_enter_idle(काष्ठा cpuidle_device *dev,
				   काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	पूर्णांक this_cpu = smp_processor_id();
	bool recouple = false;

	अगर (atomic_inc_वापस(&master) == num_online_cpus()) अणु

		/* With this lock, we prevent the other cpu to निकास and enter
		 * this function again and become the master */
		अगर (!spin_trylock(&master_lock))
			जाओ wfi;

		/* decouple the gic from the A9 cores */
		अगर (prcmu_gic_decouple()) अणु
			spin_unlock(&master_lock);
			जाओ out;
		पूर्ण

		/* If an error occur, we will have to recouple the gic
		 * manually */
		recouple = true;

		/* At this state, as the gic is decoupled, अगर the other
		 * cpu is in WFI, we have the guarantee it won't be wake
		 * up, so we can safely go to retention */
		अगर (!prcmu_is_cpu_in_wfi(this_cpu ? 0 : 1))
			जाओ out;

		/* The prcmu will be in अक्षरge of watching the पूर्णांकerrupts
		 * and wake up the cpus */
		अगर (prcmu_copy_gic_settings())
			जाओ out;

		/* Check in the meanसमय an पूर्णांकerrupt did
		 * not occur on the gic ... */
		अगर (prcmu_gic_pending_irq())
			जाओ out;

		/* ... and the prcmu */
		अगर (prcmu_pending_irq())
			जाओ out;

		/* Go to the retention state, the prcmu will रुको क्रम the
		 * cpu to go WFI and this is what happens after निकासing this
		 * 'master' critical section */
		अगर (prcmu_set_घातer_state(PRCMU_AP_IDLE, true, true))
			जाओ out;

		/* When we चयन to retention, the prcmu is in अक्षरge
		 * of recoupling the gic स्वतःmatically */
		recouple = false;

		spin_unlock(&master_lock);
	पूर्ण
wfi:
	cpu_करो_idle();
out:
	atomic_dec(&master);

	अगर (recouple) अणु
		prcmu_gic_recouple();
		spin_unlock(&master_lock);
	पूर्ण

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver ux500_idle_driver = अणु
	.name = "ux500_idle",
	.owner = THIS_MODULE,
	.states = अणु
		ARM_CPUIDLE_WFI_STATE,
		अणु
			.enter		  = ux500_enter_idle,
			.निकास_latency	  = 70,
			.target_residency = 260,
			.flags		  = CPUIDLE_FLAG_TIMER_STOP,
			.name		  = "ApIdle",
			.desc		  = "ARM Retention",
		पूर्ण,
	पूर्ण,
	.safe_state_index = 0,
	.state_count = 2,
पूर्ण;

अटल पूर्णांक dbx500_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* Configure wake up reasons */
	prcmu_enable_wakeups(PRCMU_WAKEUP(ARM) | PRCMU_WAKEUP(RTC) |
			     PRCMU_WAKEUP(ABB));

	वापस cpuidle_रेजिस्टर(&ux500_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver dbx500_cpuidle_plat_driver = अणु
	.driver = अणु
		.name = "cpuidle-dbx500",
	पूर्ण,
	.probe = dbx500_cpuidle_probe,
पूर्ण;
builtin_platक्रमm_driver(dbx500_cpuidle_plat_driver);
