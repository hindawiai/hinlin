<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2009 Wolfson Microelectronics plc
 *
 * S3C64xx CPUfreq Support
 */

#घोषणा pr_fmt(fmt) "cpufreq: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>

अटल काष्ठा regulator *vddarm;
अटल अचिन्हित दीर्घ regulator_latency;

काष्ठा s3c64xx_dvfs अणु
	अचिन्हित पूर्णांक vddarm_min;
	अचिन्हित पूर्णांक vddarm_max;
पूर्ण;

अटल काष्ठा s3c64xx_dvfs s3c64xx_dvfs_table[] = अणु
	[0] = अणु 1000000, 1150000 पूर्ण,
	[1] = अणु 1050000, 1150000 पूर्ण,
	[2] = अणु 1100000, 1150000 पूर्ण,
	[3] = अणु 1200000, 1350000 पूर्ण,
	[4] = अणु 1300000, 1350000 पूर्ण,
पूर्ण;

अटल काष्ठा cpufreq_frequency_table s3c64xx_freq_table[] = अणु
	अणु 0, 0,  66000 पूर्ण,
	अणु 0, 0, 100000 पूर्ण,
	अणु 0, 0, 133000 पूर्ण,
	अणु 0, 1, 200000 पूर्ण,
	अणु 0, 1, 222000 पूर्ण,
	अणु 0, 1, 266000 पूर्ण,
	अणु 0, 2, 333000 पूर्ण,
	अणु 0, 2, 400000 पूर्ण,
	अणु 0, 2, 532000 पूर्ण,
	अणु 0, 2, 533000 पूर्ण,
	अणु 0, 3, 667000 पूर्ण,
	अणु 0, 4, 800000 पूर्ण,
	अणु 0, 0, CPUFREQ_TABLE_END पूर्ण,
पूर्ण;

अटल पूर्णांक s3c64xx_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				      अचिन्हित पूर्णांक index)
अणु
	काष्ठा s3c64xx_dvfs *dvfs;
	अचिन्हित पूर्णांक old_freq, new_freq;
	पूर्णांक ret;

	old_freq = clk_get_rate(policy->clk) / 1000;
	new_freq = s3c64xx_freq_table[index].frequency;
	dvfs = &s3c64xx_dvfs_table[s3c64xx_freq_table[index].driver_data];

#अगर_घोषित CONFIG_REGULATOR
	अगर (vddarm && new_freq > old_freq) अणु
		ret = regulator_set_voltage(vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);
		अगर (ret != 0) अणु
			pr_err("Failed to set VDDARM for %dkHz: %d\n",
			       new_freq, ret);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	ret = clk_set_rate(policy->clk, new_freq * 1000);
	अगर (ret < 0) अणु
		pr_err("Failed to set rate %dkHz: %d\n",
		       new_freq, ret);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_REGULATOR
	अगर (vddarm && new_freq < old_freq) अणु
		ret = regulator_set_voltage(vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);
		अगर (ret != 0) अणु
			pr_err("Failed to set VDDARM for %dkHz: %d\n",
			       new_freq, ret);
			अगर (clk_set_rate(policy->clk, old_freq * 1000) < 0)
				pr_err("Failed to restore original clock rate\n");

			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	pr_debug("Set actual frequency %lukHz\n",
		 clk_get_rate(policy->clk) / 1000);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_REGULATOR
अटल व्योम s3c64xx_cpufreq_config_regulator(व्योम)
अणु
	पूर्णांक count, v, i, found;
	काष्ठा cpufreq_frequency_table *freq;
	काष्ठा s3c64xx_dvfs *dvfs;

	count = regulator_count_voltages(vddarm);
	अगर (count < 0) अणु
		pr_err("Unable to check supported voltages\n");
	पूर्ण

	अगर (!count)
		जाओ out;

	cpufreq_क्रम_each_valid_entry(freq, s3c64xx_freq_table) अणु
		dvfs = &s3c64xx_dvfs_table[freq->driver_data];
		found = 0;

		क्रम (i = 0; i < count; i++) अणु
			v = regulator_list_voltage(vddarm, i);
			अगर (v >= dvfs->vddarm_min && v <= dvfs->vddarm_max)
				found = 1;
		पूर्ण

		अगर (!found) अणु
			pr_debug("%dkHz unsupported by regulator\n",
				 freq->frequency);
			freq->frequency = CPUFREQ_ENTRY_INVALID;
		पूर्ण
	पूर्ण

out:
	/* Guess based on having to करो an I2C/SPI ग_लिखो; in future we
	 * will be able to query the regulator perक्रमmance here. */
	regulator_latency = 1 * 1000 * 1000;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s3c64xx_cpufreq_driver_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *freq;

	अगर (policy->cpu != 0)
		वापस -EINVAL;

	policy->clk = clk_get(शून्य, "armclk");
	अगर (IS_ERR(policy->clk)) अणु
		pr_err("Unable to obtain ARMCLK: %ld\n",
		       PTR_ERR(policy->clk));
		वापस PTR_ERR(policy->clk);
	पूर्ण

#अगर_घोषित CONFIG_REGULATOR
	vddarm = regulator_get(शून्य, "vddarm");
	अगर (IS_ERR(vddarm)) अणु
		pr_err("Failed to obtain VDDARM: %ld\n", PTR_ERR(vddarm));
		pr_err("Only frequency scaling available\n");
		vddarm = शून्य;
	पूर्ण अन्यथा अणु
		s3c64xx_cpufreq_config_regulator();
	पूर्ण
#पूर्ण_अगर

	cpufreq_क्रम_each_entry(freq, s3c64xx_freq_table) अणु
		अचिन्हित दीर्घ r;

		/* Check क्रम frequencies we can generate */
		r = clk_round_rate(policy->clk, freq->frequency * 1000);
		r /= 1000;
		अगर (r != freq->frequency) अणु
			pr_debug("%dkHz unsupported by clock\n",
				 freq->frequency);
			freq->frequency = CPUFREQ_ENTRY_INVALID;
		पूर्ण

		/* If we have no regulator then assume startup
		 * frequency is the maximum we can support. */
		अगर (!vddarm && freq->frequency > clk_get_rate(policy->clk) / 1000)
			freq->frequency = CPUFREQ_ENTRY_INVALID;
	पूर्ण

	/* Datasheet says PLL stabalisation समय (अगर we were to use
	 * the PLLs, which we करोn't currently) is ~300us worst हाल,
	 * but add some fudge.
	 */
	cpufreq_generic_init(policy, s3c64xx_freq_table,
			(500 * 1000) + regulator_latency);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver s3c64xx_cpufreq_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= s3c64xx_cpufreq_set_target,
	.get		= cpufreq_generic_get,
	.init		= s3c64xx_cpufreq_driver_init,
	.name		= "s3c",
पूर्ण;

अटल पूर्णांक __init s3c64xx_cpufreq_init(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_driver(&s3c64xx_cpufreq_driver);
पूर्ण
module_init(s3c64xx_cpufreq_init);
