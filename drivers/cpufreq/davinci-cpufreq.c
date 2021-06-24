<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU frequency scaling क्रम DaVinci
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Based on linux/arch/arm/plat-omap/cpu-omap.c. Original Copyright follows:
 *
 *  Copyright (C) 2005 Nokia Corporation
 *  Written by Tony Lindgren <tony@atomide.com>
 *
 *  Based on cpu-sa1110.c, Copyright (C) 2001 Russell King
 *
 * Copyright (C) 2007-2008 Texas Instruments, Inc.
 * Updated to support OMAP3
 * Rajendra Nayak <rnayak@ti.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_data/davinci-cpufreq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/export.h>

काष्ठा davinci_cpufreq अणु
	काष्ठा device *dev;
	काष्ठा clk *armclk;
	काष्ठा clk *asyncclk;
	अचिन्हित दीर्घ asyncrate;
पूर्ण;
अटल काष्ठा davinci_cpufreq cpufreq;

अटल पूर्णांक davinci_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा davinci_cpufreq_config *pdata = cpufreq.dev->platक्रमm_data;
	काष्ठा clk *armclk = cpufreq.armclk;
	अचिन्हित पूर्णांक old_freq, new_freq;
	पूर्णांक ret = 0;

	old_freq = policy->cur;
	new_freq = pdata->freq_table[idx].frequency;

	/* अगर moving to higher frequency, up the voltage beक्रमehand */
	अगर (pdata->set_voltage && new_freq > old_freq) अणु
		ret = pdata->set_voltage(idx);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_set_rate(armclk, new_freq * 1000);
	अगर (ret)
		वापस ret;

	अगर (cpufreq.asyncclk) अणु
		ret = clk_set_rate(cpufreq.asyncclk, cpufreq.asyncrate);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* अगर moving to lower freq, lower the voltage after lowering freq */
	अगर (pdata->set_voltage && new_freq < old_freq)
		pdata->set_voltage(idx);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक result = 0;
	काष्ठा davinci_cpufreq_config *pdata = cpufreq.dev->platक्रमm_data;
	काष्ठा cpufreq_frequency_table *freq_table = pdata->freq_table;

	अगर (policy->cpu != 0)
		वापस -EINVAL;

	/* Finish platक्रमm specअगरic initialization */
	अगर (pdata->init) अणु
		result = pdata->init();
		अगर (result)
			वापस result;
	पूर्ण

	policy->clk = cpufreq.armclk;

	/*
	 * Time measurement across the target() function yields ~1500-1800us
	 * समय taken with no drivers on notअगरication list.
	 * Setting the latency to 2000 us to accommodate addition of drivers
	 * to pre/post change notअगरication list.
	 */
	cpufreq_generic_init(policy, freq_table, 2000 * 1000);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver davinci_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= davinci_target,
	.get		= cpufreq_generic_get,
	.init		= davinci_cpu_init,
	.name		= "davinci",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक __init davinci_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_cpufreq_config *pdata = pdev->dev.platक्रमm_data;
	काष्ठा clk *asyncclk;

	अगर (!pdata)
		वापस -EINVAL;
	अगर (!pdata->freq_table)
		वापस -EINVAL;

	cpufreq.dev = &pdev->dev;

	cpufreq.armclk = clk_get(शून्य, "arm");
	अगर (IS_ERR(cpufreq.armclk)) अणु
		dev_err(cpufreq.dev, "Unable to get ARM clock\n");
		वापस PTR_ERR(cpufreq.armclk);
	पूर्ण

	asyncclk = clk_get(cpufreq.dev, "async");
	अगर (!IS_ERR(asyncclk)) अणु
		cpufreq.asyncclk = asyncclk;
		cpufreq.asyncrate = clk_get_rate(asyncclk);
	पूर्ण

	वापस cpufreq_रेजिस्टर_driver(&davinci_driver);
पूर्ण

अटल पूर्णांक __निकास davinci_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	clk_put(cpufreq.armclk);

	अगर (cpufreq.asyncclk)
		clk_put(cpufreq.asyncclk);

	वापस cpufreq_unरेजिस्टर_driver(&davinci_driver);
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_cpufreq_driver = अणु
	.driver = अणु
		.name	 = "cpufreq-davinci",
	पूर्ण,
	.हटाओ = __निकास_p(davinci_cpufreq_हटाओ),
पूर्ण;

पूर्णांक __init davinci_cpufreq_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&davinci_cpufreq_driver,
							davinci_cpufreq_probe);
पूर्ण

