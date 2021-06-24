<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 * Author: Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Simplअगरied generic voltage coupler from regulator core.c
 * The मुख्य dअगरference is that it keeps current regulator voltage
 * अगर consumers didn't apply their स्थिरraपूर्णांकs yet.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/coupler.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

अटल पूर्णांक regulator_get_optimal_voltage(काष्ठा regulator_dev *rdev,
					 पूर्णांक *current_uV,
					 पूर्णांक *min_uV, पूर्णांक *max_uV,
					 suspend_state_t state)
अणु
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	काष्ठा regulator_dev **c_rdevs = c_desc->coupled_rdevs;
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;
	पूर्णांक desired_min_uV = 0, desired_max_uV = पूर्णांक_उच्च;
	पूर्णांक max_current_uV = 0, min_current_uV = पूर्णांक_उच्च;
	पूर्णांक highest_min_uV = 0, target_uV, possible_uV;
	पूर्णांक i, ret, max_spपढ़ो, n_coupled = c_desc->n_coupled;
	bool करोne;

	*current_uV = -1;

	/* Find highest min desired voltage */
	क्रम (i = 0; i < n_coupled; i++) अणु
		पूर्णांक पंचांगp_min = 0;
		पूर्णांक पंचांगp_max = पूर्णांक_उच्च;

		lockdep_निश्चित_held_once(&c_rdevs[i]->mutex.base);

		ret = regulator_check_consumers(c_rdevs[i],
						&पंचांगp_min,
						&पंचांगp_max, state);
		अगर (ret < 0)
			वापस ret;

		अगर (पंचांगp_min == 0) अणु
			ret = regulator_get_voltage_rdev(c_rdevs[i]);
			अगर (ret < 0)
				वापस ret;
			पंचांगp_min = ret;
		पूर्ण

		/* apply स्थिरraपूर्णांकs */
		ret = regulator_check_voltage(c_rdevs[i], &पंचांगp_min, &पंचांगp_max);
		अगर (ret < 0)
			वापस ret;

		highest_min_uV = max(highest_min_uV, पंचांगp_min);

		अगर (i == 0) अणु
			desired_min_uV = पंचांगp_min;
			desired_max_uV = पंचांगp_max;
		पूर्ण
	पूर्ण

	max_spपढ़ो = स्थिरraपूर्णांकs->max_spपढ़ो[0];

	/*
	 * Let target_uV be equal to the desired one अगर possible.
	 * If not, set it to minimum voltage, allowed by other coupled
	 * regulators.
	 */
	target_uV = max(desired_min_uV, highest_min_uV - max_spपढ़ो);

	/*
	 * Find min and max voltages, which currently aren't violating
	 * max_spपढ़ो.
	 */
	क्रम (i = 1; i < n_coupled; i++) अणु
		पूर्णांक पंचांगp_act;

		पंचांगp_act = regulator_get_voltage_rdev(c_rdevs[i]);
		अगर (पंचांगp_act < 0)
			वापस पंचांगp_act;

		min_current_uV = min(पंचांगp_act, min_current_uV);
		max_current_uV = max(पंचांगp_act, max_current_uV);
	पूर्ण

	/*
	 * Correct target voltage, so as it currently isn't
	 * violating max_spपढ़ो
	 */
	possible_uV = max(target_uV, max_current_uV - max_spपढ़ो);
	possible_uV = min(possible_uV, min_current_uV + max_spपढ़ो);

	अगर (possible_uV > desired_max_uV)
		वापस -EINVAL;

	करोne = (possible_uV == target_uV);
	desired_min_uV = possible_uV;

	/* Set current_uV अगर wasn't करोne earlier in the code and अगर necessary */
	अगर (*current_uV == -1) अणु
		ret = regulator_get_voltage_rdev(rdev);
		अगर (ret < 0)
			वापस ret;
		*current_uV = ret;
	पूर्ण

	*min_uV = desired_min_uV;
	*max_uV = desired_max_uV;

	वापस करोne;
पूर्ण

अटल पूर्णांक exynos_coupler_balance_voltage(काष्ठा regulator_coupler *coupler,
					  काष्ठा regulator_dev *rdev,
					  suspend_state_t state)
अणु
	काष्ठा regulator_dev **c_rdevs;
	काष्ठा regulator_dev *best_rdev;
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	पूर्णांक i, ret, n_coupled, best_min_uV, best_max_uV, best_c_rdev;
	अचिन्हित पूर्णांक delta, best_delta;
	अचिन्हित दीर्घ c_rdev_करोne = 0;
	bool best_c_rdev_करोne;

	c_rdevs = c_desc->coupled_rdevs;
	n_coupled = c_desc->n_coupled;

	/*
	 * Find the best possible voltage change on each loop. Leave the loop
	 * अगर there isn't any possible change.
	 */
	करो अणु
		best_c_rdev_करोne = false;
		best_delta = 0;
		best_min_uV = 0;
		best_max_uV = 0;
		best_c_rdev = 0;
		best_rdev = शून्य;

		/*
		 * Find highest dअगरference between optimal voltage
		 * and current voltage.
		 */
		क्रम (i = 0; i < n_coupled; i++) अणु
			/*
			 * optimal_uV is the best voltage that can be set क्रम
			 * i-th regulator at the moment without violating
			 * max_spपढ़ो स्थिरraपूर्णांक in order to balance
			 * the coupled voltages.
			 */
			पूर्णांक optimal_uV = 0, optimal_max_uV = 0, current_uV = 0;

			अगर (test_bit(i, &c_rdev_करोne))
				जारी;

			ret = regulator_get_optimal_voltage(c_rdevs[i],
							    &current_uV,
							    &optimal_uV,
							    &optimal_max_uV,
							    state);
			अगर (ret < 0)
				जाओ out;

			delta = असल(optimal_uV - current_uV);

			अगर (delta && best_delta <= delta) अणु
				best_c_rdev_करोne = ret;
				best_delta = delta;
				best_rdev = c_rdevs[i];
				best_min_uV = optimal_uV;
				best_max_uV = optimal_max_uV;
				best_c_rdev = i;
			पूर्ण
		पूर्ण

		/* Nothing to change, वापस successfully */
		अगर (!best_rdev) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		ret = regulator_set_voltage_rdev(best_rdev, best_min_uV,
						 best_max_uV, state);

		अगर (ret < 0)
			जाओ out;

		अगर (best_c_rdev_करोne)
			set_bit(best_c_rdev, &c_rdev_करोne);

	पूर्ण जबतक (n_coupled > 1);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_coupler_attach(काष्ठा regulator_coupler *coupler,
				 काष्ठा regulator_dev *rdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा regulator_coupler exynos_coupler = अणु
	.attach_regulator = exynos_coupler_attach,
	.balance_voltage  = exynos_coupler_balance_voltage,
पूर्ण;

अटल पूर्णांक __init exynos_coupler_init(व्योम)
अणु
	अगर (!of_machine_is_compatible("samsung,exynos5800"))
		वापस 0;

	वापस regulator_coupler_रेजिस्टर(&exynos_coupler);
पूर्ण
arch_initcall(exynos_coupler_init);
