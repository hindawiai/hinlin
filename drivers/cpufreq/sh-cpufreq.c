<शैली गुरु>
/*
 * cpufreq driver क्रम the SuperH processors.
 *
 * Copyright (C) 2002 - 2012 Paul Mundt
 * Copyright (C) 2002 M. R. Brown
 *
 * Clock framework bits from arch/avr32/mach-at32ap/cpufreq.c
 *
 *   Copyright (C) 2004-2007 Aपंचांगel Corporation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "cpufreq: " fmt

#समावेश <linux/types.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>	/* set_cpus_allowed() */
#समावेश <linux/clk.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sh_clk.h>

अटल DEFINE_PER_CPU(काष्ठा clk, sh_cpuclk);

काष्ठा cpufreq_target अणु
	काष्ठा cpufreq_policy	*policy;
	अचिन्हित पूर्णांक		freq;
पूर्ण;

अटल अचिन्हित पूर्णांक sh_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	वापस (clk_get_rate(&per_cpu(sh_cpuclk, cpu)) + 500) / 1000;
पूर्ण

अटल दीर्घ __sh_cpufreq_target(व्योम *arg)
अणु
	काष्ठा cpufreq_target *target = arg;
	काष्ठा cpufreq_policy *policy = target->policy;
	पूर्णांक cpu = policy->cpu;
	काष्ठा clk *cpuclk = &per_cpu(sh_cpuclk, cpu);
	काष्ठा cpufreq_freqs freqs;
	काष्ठा device *dev;
	दीर्घ freq;

	अगर (smp_processor_id() != cpu)
		वापस -ENODEV;

	dev = get_cpu_device(cpu);

	/* Convert target_freq from kHz to Hz */
	freq = clk_round_rate(cpuclk, target->freq * 1000);

	अगर (freq < (policy->min * 1000) || freq > (policy->max * 1000))
		वापस -EINVAL;

	dev_dbg(dev, "requested frequency %u Hz\n", target->freq * 1000);

	freqs.old	= sh_cpufreq_get(cpu);
	freqs.new	= (freq + 500) / 1000;
	freqs.flags	= 0;

	cpufreq_freq_transition_begin(target->policy, &freqs);
	clk_set_rate(cpuclk, freq);
	cpufreq_freq_transition_end(target->policy, &freqs, 0);

	dev_dbg(dev, "set frequency %lu Hz\n", freq);
	वापस 0;
पूर्ण

/*
 * Here we notअगरy other drivers of the proposed change and the final change.
 */
अटल पूर्णांक sh_cpufreq_target(काष्ठा cpufreq_policy *policy,
			     अचिन्हित पूर्णांक target_freq,
			     अचिन्हित पूर्णांक relation)
अणु
	काष्ठा cpufreq_target data = अणु .policy = policy, .freq = target_freq पूर्ण;

	वापस work_on_cpu(policy->cpu, __sh_cpufreq_target, &data);
पूर्ण

अटल पूर्णांक sh_cpufreq_verअगरy(काष्ठा cpufreq_policy_data *policy)
अणु
	काष्ठा clk *cpuclk = &per_cpu(sh_cpuclk, policy->cpu);
	काष्ठा cpufreq_frequency_table *freq_table;

	freq_table = cpuclk->nr_freqs ? cpuclk->freq_table : शून्य;
	अगर (freq_table)
		वापस cpufreq_frequency_table_verअगरy(policy, freq_table);

	cpufreq_verअगरy_within_cpu_limits(policy);

	policy->min = (clk_round_rate(cpuclk, 1) + 500) / 1000;
	policy->max = (clk_round_rate(cpuclk, ~0UL) + 500) / 1000;

	cpufreq_verअगरy_within_cpu_limits(policy);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा clk *cpuclk = &per_cpu(sh_cpuclk, cpu);
	काष्ठा cpufreq_frequency_table *freq_table;
	काष्ठा device *dev;

	dev = get_cpu_device(cpu);

	cpuclk = clk_get(dev, "cpu_clk");
	अगर (IS_ERR(cpuclk)) अणु
		dev_err(dev, "couldn't get CPU clk\n");
		वापस PTR_ERR(cpuclk);
	पूर्ण

	freq_table = cpuclk->nr_freqs ? cpuclk->freq_table : शून्य;
	अगर (freq_table) अणु
		policy->freq_table = freq_table;
	पूर्ण अन्यथा अणु
		dev_notice(dev, "no frequency table found, falling back "
			   "to rate rounding.\n");

		policy->min = policy->cpuinfo.min_freq =
			(clk_round_rate(cpuclk, 1) + 500) / 1000;
		policy->max = policy->cpuinfo.max_freq =
			(clk_round_rate(cpuclk, ~0UL) + 500) / 1000;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा clk *cpuclk = &per_cpu(sh_cpuclk, cpu);

	clk_put(cpuclk);

	वापस 0;
पूर्ण

अटल व्योम sh_cpufreq_cpu_पढ़ोy(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device *dev = get_cpu_device(policy->cpu);

	dev_info(dev, "CPU Frequencies - Minimum %u.%03u MHz, "
	       "Maximum %u.%03u MHz.\n",
	       policy->min / 1000, policy->min % 1000,
	       policy->max / 1000, policy->max % 1000);
पूर्ण

अटल काष्ठा cpufreq_driver sh_cpufreq_driver = अणु
	.name		= "sh",
	.flags		= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.get		= sh_cpufreq_get,
	.target		= sh_cpufreq_target,
	.verअगरy		= sh_cpufreq_verअगरy,
	.init		= sh_cpufreq_cpu_init,
	.निकास		= sh_cpufreq_cpu_निकास,
	.पढ़ोy		= sh_cpufreq_cpu_पढ़ोy,
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक __init sh_cpufreq_module_init(व्योम)
अणु
	pr_notice("SuperH CPU frequency driver.\n");
	वापस cpufreq_रेजिस्टर_driver(&sh_cpufreq_driver);
पूर्ण

अटल व्योम __निकास sh_cpufreq_module_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&sh_cpufreq_driver);
पूर्ण

module_init(sh_cpufreq_module_init);
module_निकास(sh_cpufreq_module_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("cpufreq driver for SuperH");
MODULE_LICENSE("GPL");
