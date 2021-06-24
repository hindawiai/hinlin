<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  CPU frequency scaling क्रम OMAP using OPP inक्रमmation
 *
 *  Copyright (C) 2005 Nokia Corporation
 *  Written by Tony Lindgren <tony@atomide.com>
 *
 *  Based on cpu-sa1110.c, Copyright (C) 2001 Russell King
 *
 * Copyright (C) 2007-2011 Texas Instruments, Inc.
 * - OMAP3/4 support by Rajendra Nayak, Santosh Shilimkar
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_opp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/cpu.h>

/* OPP tolerance in percentage */
#घोषणा	OPP_TOLERANCE	4

अटल काष्ठा cpufreq_frequency_table *freq_table;
अटल atomic_t freq_table_users = ATOMIC_INIT(0);
अटल काष्ठा device *mpu_dev;
अटल काष्ठा regulator *mpu_reg;

अटल पूर्णांक omap_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक r, ret;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ freq, volt = 0, volt_old = 0, tol = 0;
	अचिन्हित पूर्णांक old_freq, new_freq;

	old_freq = policy->cur;
	new_freq = freq_table[index].frequency;

	freq = new_freq * 1000;
	ret = clk_round_rate(policy->clk, freq);
	अगर (ret < 0) अणु
		dev_warn(mpu_dev,
			 "CPUfreq: Cannot find matching frequency for %lu\n",
			 freq);
		वापस ret;
	पूर्ण
	freq = ret;

	अगर (mpu_reg) अणु
		opp = dev_pm_opp_find_freq_उच्चमान(mpu_dev, &freq);
		अगर (IS_ERR(opp)) अणु
			dev_err(mpu_dev, "%s: unable to find MPU OPP for %d\n",
				__func__, new_freq);
			वापस -EINVAL;
		पूर्ण
		volt = dev_pm_opp_get_voltage(opp);
		dev_pm_opp_put(opp);
		tol = volt * OPP_TOLERANCE / 100;
		volt_old = regulator_get_voltage(mpu_reg);
	पूर्ण

	dev_dbg(mpu_dev, "cpufreq-omap: %u MHz, %ld mV --> %u MHz, %ld mV\n", 
		old_freq / 1000, volt_old ? volt_old / 1000 : -1,
		new_freq / 1000, volt ? volt / 1000 : -1);

	/* scaling up?  scale voltage beक्रमe frequency */
	अगर (mpu_reg && (new_freq > old_freq)) अणु
		r = regulator_set_voltage(mpu_reg, volt - tol, volt + tol);
		अगर (r < 0) अणु
			dev_warn(mpu_dev, "%s: unable to scale voltage up.\n",
				 __func__);
			वापस r;
		पूर्ण
	पूर्ण

	ret = clk_set_rate(policy->clk, new_freq * 1000);

	/* scaling करोwn?  scale voltage after frequency */
	अगर (mpu_reg && (new_freq < old_freq)) अणु
		r = regulator_set_voltage(mpu_reg, volt - tol, volt + tol);
		अगर (r < 0) अणु
			dev_warn(mpu_dev, "%s: unable to scale voltage down.\n",
				 __func__);
			clk_set_rate(policy->clk, old_freq * 1000);
			वापस r;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम freq_table_मुक्त(व्योम)
अणु
	अगर (atomic_dec_and_test(&freq_table_users))
		dev_pm_opp_मुक्त_cpufreq_table(mpu_dev, &freq_table);
पूर्ण

अटल पूर्णांक omap_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक result;

	policy->clk = clk_get(शून्य, "cpufreq_ck");
	अगर (IS_ERR(policy->clk))
		वापस PTR_ERR(policy->clk);

	अगर (!freq_table) अणु
		result = dev_pm_opp_init_cpufreq_table(mpu_dev, &freq_table);
		अगर (result) अणु
			dev_err(mpu_dev,
				"%s: cpu%d: failed creating freq table[%d]\n",
				__func__, policy->cpu, result);
			clk_put(policy->clk);
			वापस result;
		पूर्ण
	पूर्ण

	atomic_inc_वापस(&freq_table_users);

	/* FIXME: what's the actual transition समय? */
	cpufreq_generic_init(policy, freq_table, 300 * 1000);
	dev_pm_opp_of_रेजिस्टर_em(mpu_dev, policy->cpus);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	freq_table_मुक्त();
	clk_put(policy->clk);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver omap_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= omap_target,
	.get		= cpufreq_generic_get,
	.init		= omap_cpu_init,
	.निकास		= omap_cpu_निकास,
	.name		= "omap",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक omap_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	mpu_dev = get_cpu_device(0);
	अगर (!mpu_dev) अणु
		pr_warn("%s: unable to get the MPU device\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mpu_reg = regulator_get(mpu_dev, "vcc");
	अगर (IS_ERR(mpu_reg)) अणु
		pr_warn("%s: unable to get MPU regulator\n", __func__);
		mpu_reg = शून्य;
	पूर्ण अन्यथा अणु
		/* 
		 * Ensure physical regulator is present.
		 * (e.g. could be dummy regulator.)
		 */
		अगर (regulator_get_voltage(mpu_reg) < 0) अणु
			pr_warn("%s: physical regulator not present for MPU\n",
				__func__);
			regulator_put(mpu_reg);
			mpu_reg = शून्य;
		पूर्ण
	पूर्ण

	वापस cpufreq_रेजिस्टर_driver(&omap_driver);
पूर्ण

अटल पूर्णांक omap_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस cpufreq_unरेजिस्टर_driver(&omap_driver);
पूर्ण

अटल काष्ठा platक्रमm_driver omap_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "omap-cpufreq",
	पूर्ण,
	.probe		= omap_cpufreq_probe,
	.हटाओ		= omap_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(omap_cpufreq_platdrv);

MODULE_DESCRIPTION("cpufreq driver for OMAP SoCs");
MODULE_LICENSE("GPL");
