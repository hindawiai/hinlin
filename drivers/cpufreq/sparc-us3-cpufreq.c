<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* us3_cpufreq.c: UltraSPARC-III cpu frequency support
 *
 * Copyright (C) 2003 David S. Miller (davem@redhat.com)
 *
 * Many thanks to Dominik Broकरोwski क्रम fixing up the cpufreq
 * infraकाष्ठाure in order to make this driver easier to implement.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/head.h>
#समावेश <यंत्र/समयr.h>

अटल काष्ठा cpufreq_driver *cpufreq_us3_driver;

काष्ठा us3_freq_percpu_info अणु
	काष्ठा cpufreq_frequency_table table[4];
पूर्ण;

/* Indexed by cpu number. */
अटल काष्ठा us3_freq_percpu_info *us3_freq_table;

/* UltraSPARC-III has three भागiders: 1, 2, and 32.  These are controlled
 * in the Safari config रेजिस्टर.
 */
#घोषणा SAFARI_CFG_DIV_1	0x0000000000000000UL
#घोषणा SAFARI_CFG_DIV_2	0x0000000040000000UL
#घोषणा SAFARI_CFG_DIV_32	0x0000000080000000UL
#घोषणा SAFARI_CFG_DIV_MASK	0x00000000C0000000UL

अटल व्योम पढ़ो_safari_cfg(व्योम *arg)
अणु
	अचिन्हित दीर्घ ret, *val = arg;

	__यंत्र__ __अस्थिर__("ldxa	[%%g0] %1, %0"
			     : "=&r" (ret)
			     : "i" (ASI_SAFARI_CONFIG));
	*val = ret;
पूर्ण

अटल व्योम update_safari_cfg(व्योम *arg)
अणु
	अचिन्हित दीर्घ reg, *new_bits = arg;

	पढ़ो_safari_cfg(&reg);
	reg &= ~SAFARI_CFG_DIV_MASK;
	reg |= *new_bits;

	__यंत्र__ __अस्थिर__("stxa	%0, [%%g0] %1\n\t"
			     "membar	#Sync"
			     : /* no outमाला_दो */
			     : "r" (reg), "i" (ASI_SAFARI_CONFIG)
			     : "memory");
पूर्ण

अटल अचिन्हित दीर्घ get_current_freq(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ safari_cfg)
अणु
	अचिन्हित दीर्घ घड़ी_प्रकारick = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	अचिन्हित दीर्घ ret;

	चयन (safari_cfg & SAFARI_CFG_DIV_MASK) अणु
	हाल SAFARI_CFG_DIV_1:
		ret = घड़ी_प्रकारick / 1;
		अवरोध;
	हाल SAFARI_CFG_DIV_2:
		ret = घड़ी_प्रकारick / 2;
		अवरोध;
	हाल SAFARI_CFG_DIV_32:
		ret = घड़ी_प्रकारick / 32;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक us3_freq_get(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ reg;

	अगर (smp_call_function_single(cpu, पढ़ो_safari_cfg, &reg, 1))
		वापस 0;
	वापस get_current_freq(cpu, reg);
पूर्ण

अटल पूर्णांक us3_freq_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	अचिन्हित दीर्घ new_bits, new_freq;

	new_freq = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	चयन (index) अणु
	हाल 0:
		new_bits = SAFARI_CFG_DIV_1;
		new_freq /= 1;
		अवरोध;
	हाल 1:
		new_bits = SAFARI_CFG_DIV_2;
		new_freq /= 2;
		अवरोध;
	हाल 2:
		new_bits = SAFARI_CFG_DIV_32;
		new_freq /= 32;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस smp_call_function_single(cpu, update_safari_cfg, &new_bits, 1);
पूर्ण

अटल पूर्णांक __init us3_freq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	अचिन्हित दीर्घ घड़ी_प्रकारick = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	काष्ठा cpufreq_frequency_table *table =
		&us3_freq_table[cpu].table[0];

	table[0].driver_data = 0;
	table[0].frequency = घड़ी_प्रकारick / 1;
	table[1].driver_data = 1;
	table[1].frequency = घड़ी_प्रकारick / 2;
	table[2].driver_data = 2;
	table[2].frequency = घड़ी_प्रकारick / 32;
	table[3].driver_data = 0;
	table[3].frequency = CPUFREQ_TABLE_END;

	policy->cpuinfo.transition_latency = 0;
	policy->cur = घड़ी_प्रकारick;
	policy->freq_table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक us3_freq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अगर (cpufreq_us3_driver)
		us3_freq_target(policy, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __init us3_freq_init(व्योम)
अणु
	अचिन्हित दीर्घ manuf, impl, ver;
	पूर्णांक ret;

	अगर (tlb_type != cheetah && tlb_type != cheetah_plus)
		वापस -ENODEV;

	__यंत्र__("rdpr %%ver, %0" : "=r" (ver));
	manuf = ((ver >> 48) & 0xffff);
	impl  = ((ver >> 32) & 0xffff);

	अगर (manuf == CHEETAH_MANUF &&
	    (impl == CHEETAH_IMPL ||
	     impl == CHEETAH_PLUS_IMPL ||
	     impl == JAGUAR_IMPL ||
	     impl == PANTHER_IMPL)) अणु
		काष्ठा cpufreq_driver *driver;

		ret = -ENOMEM;
		driver = kzalloc(माप(*driver), GFP_KERNEL);
		अगर (!driver)
			जाओ err_out;

		us3_freq_table = kzalloc((NR_CPUS * माप(*us3_freq_table)),
			GFP_KERNEL);
		अगर (!us3_freq_table)
			जाओ err_out;

		driver->init = us3_freq_cpu_init;
		driver->verअगरy = cpufreq_generic_frequency_table_verअगरy;
		driver->target_index = us3_freq_target;
		driver->get = us3_freq_get;
		driver->निकास = us3_freq_cpu_निकास;
		म_नकल(driver->name, "UltraSPARC-III");

		cpufreq_us3_driver = driver;
		ret = cpufreq_रेजिस्टर_driver(driver);
		अगर (ret)
			जाओ err_out;

		वापस 0;

err_out:
		अगर (driver) अणु
			kमुक्त(driver);
			cpufreq_us3_driver = शून्य;
		पूर्ण
		kमुक्त(us3_freq_table);
		us3_freq_table = शून्य;
		वापस ret;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास us3_freq_निकास(व्योम)
अणु
	अगर (cpufreq_us3_driver) अणु
		cpufreq_unरेजिस्टर_driver(cpufreq_us3_driver);
		kमुक्त(cpufreq_us3_driver);
		cpufreq_us3_driver = शून्य;
		kमुक्त(us3_freq_table);
		us3_freq_table = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("cpufreq driver for UltraSPARC-III");
MODULE_LICENSE("GPL");

module_init(us3_freq_init);
module_निकास(us3_freq_निकास);
