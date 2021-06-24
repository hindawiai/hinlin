<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * S3C2416/2450 CPUfreq Support
 *
 * Copyright 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * based on s3c64xx_cpufreq.c
 *
 * Copyright 2009 Wolfson Microelectronics plc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reboot.h>
#समावेश <linux/module.h>

अटल DEFINE_MUTEX(cpufreq_lock);

काष्ठा s3c2416_data अणु
	काष्ठा clk *armभाग;
	काष्ठा clk *armclk;
	काष्ठा clk *hclk;

	अचिन्हित दीर्घ regulator_latency;
#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	काष्ठा regulator *vddarm;
#पूर्ण_अगर

	काष्ठा cpufreq_frequency_table *freq_table;

	bool is_dvs;
	bool disable_dvs;
पूर्ण;

अटल काष्ठा s3c2416_data s3c2416_cpufreq;

काष्ठा s3c2416_dvfs अणु
	अचिन्हित पूर्णांक vddarm_min;
	अचिन्हित पूर्णांक vddarm_max;
पूर्ण;

/* pseuकरो-frequency क्रम dvs mode */
#घोषणा FREQ_DVS	132333

/* frequency to sleep and reboot in
 * it's essential to leave dvs, as some boards करो not reconfigure the
 * regulator on reboot
 */
#घोषणा FREQ_SLEEP	133333

/* Sources क्रम the ARMCLK */
#घोषणा SOURCE_HCLK	0
#घोषणा SOURCE_ARMDIV	1

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
/* S3C2416 only supports changing the voltage in the dvs-mode.
 * Voltages करोwn to 1.0V seem to work, so we take what the regulator
 * can get us.
 */
अटल काष्ठा s3c2416_dvfs s3c2416_dvfs_table[] = अणु
	[SOURCE_HCLK] = अणु  950000, 1250000 पूर्ण,
	[SOURCE_ARMDIV] = अणु 1250000, 1350000 पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा cpufreq_frequency_table s3c2416_freq_table[] = अणु
	अणु 0, SOURCE_HCLK, FREQ_DVS पूर्ण,
	अणु 0, SOURCE_ARMDIV, 133333 पूर्ण,
	अणु 0, SOURCE_ARMDIV, 266666 पूर्ण,
	अणु 0, SOURCE_ARMDIV, 400000 पूर्ण,
	अणु 0, 0, CPUFREQ_TABLE_END पूर्ण,
पूर्ण;

अटल काष्ठा cpufreq_frequency_table s3c2450_freq_table[] = अणु
	अणु 0, SOURCE_HCLK, FREQ_DVS पूर्ण,
	अणु 0, SOURCE_ARMDIV, 133500 पूर्ण,
	अणु 0, SOURCE_ARMDIV, 267000 पूर्ण,
	अणु 0, SOURCE_ARMDIV, 534000 पूर्ण,
	अणु 0, 0, CPUFREQ_TABLE_END पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक s3c2416_cpufreq_get_speed(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा s3c2416_data *s3c_freq = &s3c2416_cpufreq;

	अगर (cpu != 0)
		वापस 0;

	/* वापस our pseuकरो-frequency when in dvs mode */
	अगर (s3c_freq->is_dvs)
		वापस FREQ_DVS;

	वापस clk_get_rate(s3c_freq->armclk) / 1000;
पूर्ण

अटल पूर्णांक s3c2416_cpufreq_set_armभाग(काष्ठा s3c2416_data *s3c_freq,
				      अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक ret;

	अगर (clk_get_rate(s3c_freq->armभाग) / 1000 != freq) अणु
		ret = clk_set_rate(s3c_freq->armभाग, freq * 1000);
		अगर (ret < 0) अणु
			pr_err("cpufreq: Failed to set armdiv rate %dkHz: %d\n",
			       freq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2416_cpufreq_enter_dvs(काष्ठा s3c2416_data *s3c_freq, पूर्णांक idx)
अणु
#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	काष्ठा s3c2416_dvfs *dvfs;
#पूर्ण_अगर
	पूर्णांक ret;

	अगर (s3c_freq->is_dvs) अणु
		pr_debug("cpufreq: already in dvs mode, nothing to do\n");
		वापस 0;
	पूर्ण

	pr_debug("cpufreq: switching armclk to hclk (%lukHz)\n",
		 clk_get_rate(s3c_freq->hclk) / 1000);
	ret = clk_set_parent(s3c_freq->armclk, s3c_freq->hclk);
	अगर (ret < 0) अणु
		pr_err("cpufreq: Failed to switch armclk to hclk: %d\n", ret);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	/* changing the core voltage is only allowed when in dvs mode */
	अगर (s3c_freq->vddarm) अणु
		dvfs = &s3c2416_dvfs_table[idx];

		pr_debug("cpufreq: setting regulator to %d-%d\n",
			 dvfs->vddarm_min, dvfs->vddarm_max);
		ret = regulator_set_voltage(s3c_freq->vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);

		/* when lowering the voltage failed, there is nothing to करो */
		अगर (ret != 0)
			pr_err("cpufreq: Failed to set VDDARM: %d\n", ret);
	पूर्ण
#पूर्ण_अगर

	s3c_freq->is_dvs = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2416_cpufreq_leave_dvs(काष्ठा s3c2416_data *s3c_freq, पूर्णांक idx)
अणु
#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	काष्ठा s3c2416_dvfs *dvfs;
#पूर्ण_अगर
	पूर्णांक ret;

	अगर (!s3c_freq->is_dvs) अणु
		pr_debug("cpufreq: not in dvs mode, so can't leave\n");
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	अगर (s3c_freq->vddarm) अणु
		dvfs = &s3c2416_dvfs_table[idx];

		pr_debug("cpufreq: setting regulator to %d-%d\n",
			 dvfs->vddarm_min, dvfs->vddarm_max);
		ret = regulator_set_voltage(s3c_freq->vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);
		अगर (ret != 0) अणु
			pr_err("cpufreq: Failed to set VDDARM: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* क्रमce armभाग to hclk frequency क्रम transition from dvs*/
	अगर (clk_get_rate(s3c_freq->armभाग) > clk_get_rate(s3c_freq->hclk)) अणु
		pr_debug("cpufreq: force armdiv to hclk frequency (%lukHz)\n",
			 clk_get_rate(s3c_freq->hclk) / 1000);
		ret = s3c2416_cpufreq_set_armभाग(s3c_freq,
					clk_get_rate(s3c_freq->hclk) / 1000);
		अगर (ret < 0) अणु
			pr_err("cpufreq: Failed to set the armdiv to %lukHz: %d\n",
			       clk_get_rate(s3c_freq->hclk) / 1000, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	pr_debug("cpufreq: switching armclk parent to armdiv (%lukHz)\n",
			clk_get_rate(s3c_freq->armभाग) / 1000);

	ret = clk_set_parent(s3c_freq->armclk, s3c_freq->armभाग);
	अगर (ret < 0) अणु
		pr_err("cpufreq: Failed to switch armclk clock parent to armdiv: %d\n",
		       ret);
		वापस ret;
	पूर्ण

	s3c_freq->is_dvs = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2416_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				      अचिन्हित पूर्णांक index)
अणु
	काष्ठा s3c2416_data *s3c_freq = &s3c2416_cpufreq;
	अचिन्हित पूर्णांक new_freq;
	पूर्णांक idx, ret, to_dvs = 0;

	mutex_lock(&cpufreq_lock);

	idx = s3c_freq->freq_table[index].driver_data;

	अगर (idx == SOURCE_HCLK)
		to_dvs = 1;

	/* चयनing to dvs when it's not allowed */
	अगर (to_dvs && s3c_freq->disable_dvs) अणु
		pr_debug("cpufreq: entering dvs mode not allowed\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* When leavin dvs mode, always चयन the armभाग to the hclk rate
	 * The S3C2416 has stability issues when चयनing directly to
	 * higher frequencies.
	 */
	new_freq = (s3c_freq->is_dvs && !to_dvs)
				? clk_get_rate(s3c_freq->hclk) / 1000
				: s3c_freq->freq_table[index].frequency;

	अगर (to_dvs) अणु
		pr_debug("cpufreq: enter dvs\n");
		ret = s3c2416_cpufreq_enter_dvs(s3c_freq, idx);
	पूर्ण अन्यथा अगर (s3c_freq->is_dvs) अणु
		pr_debug("cpufreq: leave dvs\n");
		ret = s3c2416_cpufreq_leave_dvs(s3c_freq, idx);
	पूर्ण अन्यथा अणु
		pr_debug("cpufreq: change armdiv to %dkHz\n", new_freq);
		ret = s3c2416_cpufreq_set_armभाग(s3c_freq, new_freq);
	पूर्ण

out:
	mutex_unlock(&cpufreq_lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
अटल व्योम s3c2416_cpufreq_cfg_regulator(काष्ठा s3c2416_data *s3c_freq)
अणु
	पूर्णांक count, v, i, found;
	काष्ठा cpufreq_frequency_table *pos;
	काष्ठा s3c2416_dvfs *dvfs;

	count = regulator_count_voltages(s3c_freq->vddarm);
	अगर (count < 0) अणु
		pr_err("cpufreq: Unable to check supported voltages\n");
		वापस;
	पूर्ण

	अगर (!count)
		जाओ out;

	cpufreq_क्रम_each_valid_entry(pos, s3c_freq->freq_table) अणु
		dvfs = &s3c2416_dvfs_table[pos->driver_data];
		found = 0;

		/* Check only the min-voltage, more is always ok on S3C2416 */
		क्रम (i = 0; i < count; i++) अणु
			v = regulator_list_voltage(s3c_freq->vddarm, i);
			अगर (v >= dvfs->vddarm_min)
				found = 1;
		पूर्ण

		अगर (!found) अणु
			pr_debug("cpufreq: %dkHz unsupported by regulator\n",
				 pos->frequency);
			pos->frequency = CPUFREQ_ENTRY_INVALID;
		पूर्ण
	पूर्ण

out:
	/* Guessed */
	s3c_freq->regulator_latency = 1 * 1000 * 1000;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s3c2416_cpufreq_reboot_notअगरier_evt(काष्ठा notअगरier_block *this,
					       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा s3c2416_data *s3c_freq = &s3c2416_cpufreq;
	पूर्णांक ret;
	काष्ठा cpufreq_policy *policy;

	mutex_lock(&cpufreq_lock);

	/* disable further changes */
	s3c_freq->disable_dvs = 1;

	mutex_unlock(&cpufreq_lock);

	/* some boards करोn't reconfigure the regulator on reboot, which
	 * could lead to undervolting the cpu when the घड़ी is reset.
	 * Thereक्रमe we always leave the DVS mode on reboot.
	 */
	अगर (s3c_freq->is_dvs) अणु
		pr_debug("cpufreq: leave dvs on reboot\n");

		policy = cpufreq_cpu_get(0);
		अगर (!policy) अणु
			pr_debug("cpufreq: get no policy for cpu0\n");
			वापस NOTIFY_BAD;
		पूर्ण

		ret = cpufreq_driver_target(policy, FREQ_SLEEP, 0);
		cpufreq_cpu_put(policy);

		अगर (ret < 0)
			वापस NOTIFY_BAD;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block s3c2416_cpufreq_reboot_notअगरier = अणु
	.notअगरier_call = s3c2416_cpufreq_reboot_notअगरier_evt,
पूर्ण;

अटल पूर्णांक s3c2416_cpufreq_driver_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा s3c2416_data *s3c_freq = &s3c2416_cpufreq;
	काष्ठा cpufreq_frequency_table *pos;
	काष्ठा clk *msysclk;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	अगर (policy->cpu != 0)
		वापस -EINVAL;

	msysclk = clk_get(शून्य, "msysclk");
	अगर (IS_ERR(msysclk)) अणु
		ret = PTR_ERR(msysclk);
		pr_err("cpufreq: Unable to obtain msysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * S3C2416 and S3C2450 share the same processor-ID and also provide no
	 * other means to distinguish them other than through the rate of
	 * msysclk. On S3C2416 msysclk runs at 800MHz and on S3C2450 at 533MHz.
	 */
	rate = clk_get_rate(msysclk);
	अगर (rate == 800 * 1000 * 1000) अणु
		pr_info("cpufreq: msysclk running at %lukHz, using S3C2416 frequency table\n",
			rate / 1000);
		s3c_freq->freq_table = s3c2416_freq_table;
		policy->cpuinfo.max_freq = 400000;
	पूर्ण अन्यथा अगर (rate / 1000 == 534000) अणु
		pr_info("cpufreq: msysclk running at %lukHz, using S3C2450 frequency table\n",
			rate / 1000);
		s3c_freq->freq_table = s3c2450_freq_table;
		policy->cpuinfo.max_freq = 534000;
	पूर्ण

	/* not needed anymore */
	clk_put(msysclk);

	अगर (s3c_freq->freq_table == शून्य) अणु
		pr_err("cpufreq: No frequency information for this CPU, msysclk at %lukHz\n",
		       rate / 1000);
		वापस -ENODEV;
	पूर्ण

	s3c_freq->is_dvs = 0;

	s3c_freq->armभाग = clk_get(शून्य, "armdiv");
	अगर (IS_ERR(s3c_freq->armभाग)) अणु
		ret = PTR_ERR(s3c_freq->armभाग);
		pr_err("cpufreq: Unable to obtain ARMDIV: %d\n", ret);
		वापस ret;
	पूर्ण

	s3c_freq->hclk = clk_get(शून्य, "hclk");
	अगर (IS_ERR(s3c_freq->hclk)) अणु
		ret = PTR_ERR(s3c_freq->hclk);
		pr_err("cpufreq: Unable to obtain HCLK: %d\n", ret);
		जाओ err_hclk;
	पूर्ण

	/* chech hclk rate, we only support the common 133MHz क्रम now
	 * hclk could also run at 66MHz, but this not often used
	 */
	rate = clk_get_rate(s3c_freq->hclk);
	अगर (rate < 133 * 1000 * 1000) अणु
		pr_err("cpufreq: HCLK not at 133MHz\n");
		ret = -EINVAL;
		जाओ err_armclk;
	पूर्ण

	s3c_freq->armclk = clk_get(शून्य, "armclk");
	अगर (IS_ERR(s3c_freq->armclk)) अणु
		ret = PTR_ERR(s3c_freq->armclk);
		pr_err("cpufreq: Unable to obtain ARMCLK: %d\n", ret);
		जाओ err_armclk;
	पूर्ण

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	s3c_freq->vddarm = regulator_get(शून्य, "vddarm");
	अगर (IS_ERR(s3c_freq->vddarm)) अणु
		ret = PTR_ERR(s3c_freq->vddarm);
		pr_err("cpufreq: Failed to obtain VDDARM: %d\n", ret);
		जाओ err_vddarm;
	पूर्ण

	s3c2416_cpufreq_cfg_regulator(s3c_freq);
#अन्यथा
	s3c_freq->regulator_latency = 0;
#पूर्ण_अगर

	cpufreq_क्रम_each_entry(pos, s3c_freq->freq_table) अणु
		/* special handling क्रम dvs mode */
		अगर (pos->driver_data == 0) अणु
			अगर (!s3c_freq->hclk) अणु
				pr_debug("cpufreq: %dkHz unsupported as it would need unavailable dvs mode\n",
					 pos->frequency);
				pos->frequency = CPUFREQ_ENTRY_INVALID;
			पूर्ण अन्यथा अणु
				जारी;
			पूर्ण
		पूर्ण

		/* Check क्रम frequencies we can generate */
		rate = clk_round_rate(s3c_freq->armभाग,
				      pos->frequency * 1000);
		rate /= 1000;
		अगर (rate != pos->frequency) अणु
			pr_debug("cpufreq: %dkHz unsupported by clock (clk_round_rate return %lu)\n",
				pos->frequency, rate);
			pos->frequency = CPUFREQ_ENTRY_INVALID;
		पूर्ण
	पूर्ण

	/* Datasheet says PLL stabalisation समय must be at least 300us,
	 * so but add some fudge. (reference in LOCKCON0 रेजिस्टर description)
	 */
	cpufreq_generic_init(policy, s3c_freq->freq_table,
			(500 * 1000) + s3c_freq->regulator_latency);
	रेजिस्टर_reboot_notअगरier(&s3c2416_cpufreq_reboot_notअगरier);

	वापस 0;

#अगर_घोषित CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
err_vddarm:
	clk_put(s3c_freq->armclk);
#पूर्ण_अगर
err_armclk:
	clk_put(s3c_freq->hclk);
err_hclk:
	clk_put(s3c_freq->armभाग);

	वापस ret;
पूर्ण

अटल काष्ठा cpufreq_driver s3c2416_cpufreq_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= s3c2416_cpufreq_set_target,
	.get		= s3c2416_cpufreq_get_speed,
	.init		= s3c2416_cpufreq_driver_init,
	.name		= "s3c2416",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक __init s3c2416_cpufreq_init(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_driver(&s3c2416_cpufreq_driver);
पूर्ण
module_init(s3c2416_cpufreq_init);
