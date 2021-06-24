<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cpufreq driver क्रम the cell processor
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005-2007
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "ppc_cbe_cpufreq.h"

/* the CBE supports an 8 step frequency scaling */
अटल काष्ठा cpufreq_frequency_table cbe_freqs[] = अणु
	अणु0, 1,	0पूर्ण,
	अणु0, 2,	0पूर्ण,
	अणु0, 3,	0पूर्ण,
	अणु0, 4,	0पूर्ण,
	अणु0, 5,	0पूर्ण,
	अणु0, 6,	0पूर्ण,
	अणु0, 8,	0पूर्ण,
	अणु0, 10,	0पूर्ण,
	अणु0, 0,	CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

/*
 * hardware specअगरic functions
 */

अटल पूर्णांक set_pmode(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक slow_mode)
अणु
	पूर्णांक rc;

	अगर (cbe_cpufreq_has_pmi)
		rc = cbe_cpufreq_set_pmode_pmi(cpu, slow_mode);
	अन्यथा
		rc = cbe_cpufreq_set_pmode(cpu, slow_mode);

	pr_debug("register contains slow mode %d\n", cbe_cpufreq_get_pmode(cpu));

	वापस rc;
पूर्ण

/*
 * cpufreq functions
 */

अटल पूर्णांक cbe_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	स्थिर u32 *max_freqp;
	u32 max_freq;
	पूर्णांक cur_pmode;
	काष्ठा device_node *cpu;

	cpu = of_get_cpu_node(policy->cpu, शून्य);

	अगर (!cpu)
		वापस -ENODEV;

	pr_debug("init cpufreq on CPU %d\n", policy->cpu);

	/*
	 * Let's check we can actually get to the CELL regs
	 */
	अगर (!cbe_get_cpu_pmd_regs(policy->cpu) ||
	    !cbe_get_cpu_mic_पंचांग_regs(policy->cpu)) अणु
		pr_info("invalid CBE regs pointers for cpufreq\n");
		of_node_put(cpu);
		वापस -EINVAL;
	पूर्ण

	max_freqp = of_get_property(cpu, "clock-frequency", शून्य);

	of_node_put(cpu);

	अगर (!max_freqp)
		वापस -EINVAL;

	/* we need the freq in kHz */
	max_freq = *max_freqp / 1000;

	pr_debug("max clock-frequency is at %u kHz\n", max_freq);
	pr_debug("initializing frequency table\n");

	/* initialize frequency table */
	cpufreq_क्रम_each_entry(pos, cbe_freqs) अणु
		pos->frequency = max_freq / pos->driver_data;
		pr_debug("%d: %d\n", (पूर्णांक)(pos - cbe_freqs), pos->frequency);
	पूर्ण

	/* अगर DEBUG is enabled set_pmode() measures the latency
	 * of a transition */
	policy->cpuinfo.transition_latency = 25000;

	cur_pmode = cbe_cpufreq_get_pmode(policy->cpu);
	pr_debug("current pmode is at %d\n",cur_pmode);

	policy->cur = cbe_freqs[cur_pmode].frequency;

#अगर_घोषित CONFIG_SMP
	cpumask_copy(policy->cpus, cpu_sibling_mask(policy->cpu));
#पूर्ण_अगर

	policy->freq_table = cbe_freqs;
	cbe_cpufreq_pmi_policy_init(policy);
	वापस 0;
पूर्ण

अटल पूर्णांक cbe_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	cbe_cpufreq_pmi_policy_निकास(policy);
	वापस 0;
पूर्ण

अटल पूर्णांक cbe_cpufreq_target(काष्ठा cpufreq_policy *policy,
			      अचिन्हित पूर्णांक cbe_pmode_new)
अणु
	pr_debug("setting frequency for cpu %d to %d kHz, " \
		 "1/%d of max frequency\n",
		 policy->cpu,
		 cbe_freqs[cbe_pmode_new].frequency,
		 cbe_freqs[cbe_pmode_new].driver_data);

	वापस set_pmode(policy->cpu, cbe_pmode_new);
पूर्ण

अटल काष्ठा cpufreq_driver cbe_cpufreq_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= cbe_cpufreq_target,
	.init		= cbe_cpufreq_cpu_init,
	.निकास		= cbe_cpufreq_cpu_निकास,
	.name		= "cbe-cpufreq",
	.flags		= CPUFREQ_CONST_LOOPS,
पूर्ण;

/*
 * module init and destoy
 */

अटल पूर्णांक __init cbe_cpufreq_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is(cell))
		वापस -ENODEV;

	cbe_cpufreq_pmi_init();

	ret = cpufreq_रेजिस्टर_driver(&cbe_cpufreq_driver);
	अगर (ret)
		cbe_cpufreq_pmi_निकास();

	वापस ret;
पूर्ण

अटल व्योम __निकास cbe_cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&cbe_cpufreq_driver);
	cbe_cpufreq_pmi_निकास();
पूर्ण

module_init(cbe_cpufreq_init);
module_निकास(cbe_cpufreq_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Krafft <krafft@de.ibm.com>");
