<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Coupled cpuidle support based on the work of:
 *	Colin Cross <ccross@android.com>
 *	Daniel Lezcano <daniel.lezcano@linaro.org>
*/

#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cpuidle-exynos.h>

#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/cpuidle.h>

अटल atomic_t exynos_idle_barrier;

अटल काष्ठा cpuidle_exynos_data *exynos_cpuidle_pdata;
अटल व्योम (*exynos_enter_aftr)(व्योम);

अटल पूर्णांक exynos_enter_coupled_lowघातer(काष्ठा cpuidle_device *dev,
					 काष्ठा cpuidle_driver *drv,
					 पूर्णांक index)
अणु
	पूर्णांक ret;

	exynos_cpuidle_pdata->pre_enter_aftr();

	/*
	 * Waiting all cpus to reach this poपूर्णांक at the same moment
	 */
	cpuidle_coupled_parallel_barrier(dev, &exynos_idle_barrier);

	/*
	 * Both cpus will reach this poपूर्णांक at the same समय
	 */
	ret = dev->cpu ? exynos_cpuidle_pdata->cpu1_घातerकरोwn()
		       : exynos_cpuidle_pdata->cpu0_enter_aftr();
	अगर (ret)
		index = ret;

	/*
	 * Waiting all cpus to finish the घातer sequence beक्रमe going further
	 */
	cpuidle_coupled_parallel_barrier(dev, &exynos_idle_barrier);

	exynos_cpuidle_pdata->post_enter_aftr();

	वापस index;
पूर्ण

अटल पूर्णांक exynos_enter_lowघातer(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv,
				पूर्णांक index)
अणु
	पूर्णांक new_index = index;

	/* AFTR can only be entered when cores other than CPU0 are offline */
	अगर (num_online_cpus() > 1 || dev->cpu != 0)
		new_index = drv->safe_state_index;

	अगर (new_index == 0)
		वापस arm_cpuidle_simple_enter(dev, drv, new_index);

	exynos_enter_aftr();

	वापस new_index;
पूर्ण

अटल काष्ठा cpuidle_driver exynos_idle_driver = अणु
	.name			= "exynos_idle",
	.owner			= THIS_MODULE,
	.states = अणु
		[0] = ARM_CPUIDLE_WFI_STATE,
		[1] = अणु
			.enter			= exynos_enter_lowघातer,
			.निकास_latency		= 300,
			.target_residency	= 10000,
			.name			= "C1",
			.desc			= "ARM power down",
		पूर्ण,
	पूर्ण,
	.state_count = 2,
	.safe_state_index = 0,
पूर्ण;

अटल काष्ठा cpuidle_driver exynos_coupled_idle_driver = अणु
	.name			= "exynos_coupled_idle",
	.owner			= THIS_MODULE,
	.states = अणु
		[0] = ARM_CPUIDLE_WFI_STATE,
		[1] = अणु
			.enter			= exynos_enter_coupled_lowघातer,
			.निकास_latency		= 5000,
			.target_residency	= 10000,
			.flags			= CPUIDLE_FLAG_COUPLED |
						  CPUIDLE_FLAG_TIMER_STOP,
			.name			= "C1",
			.desc			= "ARM power down",
		पूर्ण,
	पूर्ण,
	.state_count = 2,
	.safe_state_index = 0,
पूर्ण;

अटल पूर्णांक exynos_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_SMP) &&
	    (of_machine_is_compatible("samsung,exynos4210") ||
	     of_machine_is_compatible("samsung,exynos3250"))) अणु
		exynos_cpuidle_pdata = pdev->dev.platक्रमm_data;

		ret = cpuidle_रेजिस्टर(&exynos_coupled_idle_driver,
				       cpu_possible_mask);
	पूर्ण अन्यथा अणु
		exynos_enter_aftr = (व्योम *)(pdev->dev.platक्रमm_data);

		ret = cpuidle_रेजिस्टर(&exynos_idle_driver, शून्य);
	पूर्ण

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register cpuidle driver\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_cpuidle_driver = अणु
	.probe	= exynos_cpuidle_probe,
	.driver = अणु
		.name = "exynos_cpuidle",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(exynos_cpuidle_driver);
