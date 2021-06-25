<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* us2e_cpufreq.c: UltraSPARC-IIe cpu frequency support
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
#समावेश <linux/delay.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/समयr.h>

अटल काष्ठा cpufreq_driver *cpufreq_us2e_driver;

काष्ठा us2e_freq_percpu_info अणु
	काष्ठा cpufreq_frequency_table table[6];
पूर्ण;

/* Indexed by cpu number. */
अटल काष्ठा us2e_freq_percpu_info *us2e_freq_table;

#घोषणा HBIRD_MEM_CNTL0_ADDR	0x1fe0000f010UL
#घोषणा HBIRD_ESTAR_MODE_ADDR	0x1fe0000f080UL

/* UltraSPARC-IIe has five भागiders: 1, 2, 4, 6, and 8.  These are controlled
 * in the ESTAR mode control रेजिस्टर.
 */
#घोषणा ESTAR_MODE_DIV_1	0x0000000000000000UL
#घोषणा ESTAR_MODE_DIV_2	0x0000000000000001UL
#घोषणा ESTAR_MODE_DIV_4	0x0000000000000003UL
#घोषणा ESTAR_MODE_DIV_6	0x0000000000000002UL
#घोषणा ESTAR_MODE_DIV_8	0x0000000000000004UL
#घोषणा ESTAR_MODE_DIV_MASK	0x0000000000000007UL

#घोषणा MCTRL0_SREFRESH_ENAB	0x0000000000010000UL
#घोषणा MCTRL0_REFR_COUNT_MASK	0x0000000000007f00UL
#घोषणा MCTRL0_REFR_COUNT_SHIFT	8
#घोषणा MCTRL0_REFR_INTERVAL	7800
#घोषणा MCTRL0_REFR_CLKS_P_CNT	64

अटल अचिन्हित दीर्घ पढ़ो_hbreg(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=&r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
	वापस ret;
पूर्ण

अटल व्योम ग_लिखो_hbreg(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* no outमाला_दो */
			     : "r" (val), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E)
			     : "memory");
	अगर (addr == HBIRD_ESTAR_MODE_ADDR) अणु
		/* Need to रुको 16 घड़ी cycles क्रम the PLL to lock.  */
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम self_refresh_ctl(पूर्णांक enable)
अणु
	अचिन्हित दीर्घ mctrl = पढ़ो_hbreg(HBIRD_MEM_CNTL0_ADDR);

	अगर (enable)
		mctrl |= MCTRL0_SREFRESH_ENAB;
	अन्यथा
		mctrl &= ~MCTRL0_SREFRESH_ENAB;
	ग_लिखो_hbreg(HBIRD_MEM_CNTL0_ADDR, mctrl);
	(व्योम) पढ़ो_hbreg(HBIRD_MEM_CNTL0_ADDR);
पूर्ण

अटल व्योम frob_mem_refresh(पूर्णांक cpu_slowing_करोwn,
			     अचिन्हित दीर्घ घड़ी_प्रकारick,
			     अचिन्हित दीर्घ old_भागisor, अचिन्हित दीर्घ भागisor)
अणु
	अचिन्हित दीर्घ old_refr_count, refr_count, mctrl;

	refr_count  = (घड़ी_प्रकारick * MCTRL0_REFR_INTERVAL);
	refr_count /= (MCTRL0_REFR_CLKS_P_CNT * भागisor * 1000000000UL);

	mctrl = पढ़ो_hbreg(HBIRD_MEM_CNTL0_ADDR);
	old_refr_count = (mctrl & MCTRL0_REFR_COUNT_MASK)
		>> MCTRL0_REFR_COUNT_SHIFT;

	mctrl &= ~MCTRL0_REFR_COUNT_MASK;
	mctrl |= refr_count << MCTRL0_REFR_COUNT_SHIFT;
	ग_लिखो_hbreg(HBIRD_MEM_CNTL0_ADDR, mctrl);
	mctrl = पढ़ो_hbreg(HBIRD_MEM_CNTL0_ADDR);

	अगर (cpu_slowing_करोwn && !(mctrl & MCTRL0_SREFRESH_ENAB)) अणु
		अचिन्हित दीर्घ usecs;

		/* We have to रुको क्रम both refresh counts (old
		 * and new) to go to zero.
		 */
		usecs = (MCTRL0_REFR_CLKS_P_CNT *
			 (refr_count + old_refr_count) *
			 1000000UL *
			 old_भागisor) / घड़ी_प्रकारick;
		udelay(usecs + 1UL);
	पूर्ण
पूर्ण

अटल व्योम us2e_transition(अचिन्हित दीर्घ estar, अचिन्हित दीर्घ new_bits,
			    अचिन्हित दीर्घ घड़ी_प्रकारick,
			    अचिन्हित दीर्घ old_भागisor, अचिन्हित दीर्घ भागisor)
अणु
	estar &= ~ESTAR_MODE_DIV_MASK;

	/* This is based upon the state transition diagram in the IIe manual.  */
	अगर (old_भागisor == 2 && भागisor == 1) अणु
		self_refresh_ctl(0);
		ग_लिखो_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		frob_mem_refresh(0, घड़ी_प्रकारick, old_भागisor, भागisor);
	पूर्ण अन्यथा अगर (old_भागisor == 1 && भागisor == 2) अणु
		frob_mem_refresh(1, घड़ी_प्रकारick, old_भागisor, भागisor);
		ग_लिखो_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		self_refresh_ctl(1);
	पूर्ण अन्यथा अगर (old_भागisor == 1 && भागisor > 2) अणु
		us2e_transition(estar, ESTAR_MODE_DIV_2, घड़ी_प्रकारick,
				1, 2);
		us2e_transition(estar, new_bits, घड़ी_प्रकारick,
				2, भागisor);
	पूर्ण अन्यथा अगर (old_भागisor > 2 && भागisor == 1) अणु
		us2e_transition(estar, ESTAR_MODE_DIV_2, घड़ी_प्रकारick,
				old_भागisor, 2);
		us2e_transition(estar, new_bits, घड़ी_प्रकारick,
				2, भागisor);
	पूर्ण अन्यथा अगर (old_भागisor < भागisor) अणु
		frob_mem_refresh(0, घड़ी_प्रकारick, old_भागisor, भागisor);
		ग_लिखो_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
	पूर्ण अन्यथा अगर (old_भागisor > भागisor) अणु
		ग_लिखो_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		frob_mem_refresh(1, घड़ी_प्रकारick, old_भागisor, भागisor);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ index_to_estar_mode(अचिन्हित पूर्णांक index)
अणु
	चयन (index) अणु
	हाल 0:
		वापस ESTAR_MODE_DIV_1;

	हाल 1:
		वापस ESTAR_MODE_DIV_2;

	हाल 2:
		वापस ESTAR_MODE_DIV_4;

	हाल 3:
		वापस ESTAR_MODE_DIV_6;

	हाल 4:
		वापस ESTAR_MODE_DIV_8;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ index_to_भागisor(अचिन्हित पूर्णांक index)
अणु
	चयन (index) अणु
	हाल 0:
		वापस 1;

	हाल 1:
		वापस 2;

	हाल 2:
		वापस 4;

	हाल 3:
		वापस 6;

	हाल 4:
		वापस 8;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ estar_to_भागisor(अचिन्हित दीर्घ estar)
अणु
	अचिन्हित दीर्घ ret;

	चयन (estar & ESTAR_MODE_DIV_MASK) अणु
	हाल ESTAR_MODE_DIV_1:
		ret = 1;
		अवरोध;
	हाल ESTAR_MODE_DIV_2:
		ret = 2;
		अवरोध;
	हाल ESTAR_MODE_DIV_4:
		ret = 4;
		अवरोध;
	हाल ESTAR_MODE_DIV_6:
		ret = 6;
		अवरोध;
	हाल ESTAR_MODE_DIV_8:
		ret = 8;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __us2e_freq_get(व्योम *arg)
अणु
	अचिन्हित दीर्घ *estar = arg;

	*estar = पढ़ो_hbreg(HBIRD_ESTAR_MODE_ADDR);
पूर्ण

अटल अचिन्हित पूर्णांक us2e_freq_get(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ घड़ी_प्रकारick, estar;

	घड़ी_प्रकारick = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	अगर (smp_call_function_single(cpu, __us2e_freq_get, &estar, 1))
		वापस 0;

	वापस घड़ी_प्रकारick / estar_to_भागisor(estar);
पूर्ण

अटल व्योम __us2e_freq_target(व्योम *arg)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक *index = arg;
	अचिन्हित दीर्घ new_bits, new_freq;
	अचिन्हित दीर्घ घड़ी_प्रकारick, भागisor, old_भागisor, estar;

	new_freq = घड़ी_प्रकारick = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	new_bits = index_to_estar_mode(*index);
	भागisor = index_to_भागisor(*index);
	new_freq /= भागisor;

	estar = पढ़ो_hbreg(HBIRD_ESTAR_MODE_ADDR);

	old_भागisor = estar_to_भागisor(estar);

	अगर (old_भागisor != भागisor) अणु
		us2e_transition(estar, new_bits, घड़ी_प्रकारick * 1000,
				old_भागisor, भागisor);
	पूर्ण
पूर्ण

अटल पूर्णांक us2e_freq_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;

	वापस smp_call_function_single(cpu, __us2e_freq_target, &index, 1);
पूर्ण

अटल पूर्णांक __init us2e_freq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	अचिन्हित दीर्घ घड़ी_प्रकारick = sparc64_get_घड़ी_प्रकारick(cpu) / 1000;
	काष्ठा cpufreq_frequency_table *table =
		&us2e_freq_table[cpu].table[0];

	table[0].driver_data = 0;
	table[0].frequency = घड़ी_प्रकारick / 1;
	table[1].driver_data = 1;
	table[1].frequency = घड़ी_प्रकारick / 2;
	table[2].driver_data = 2;
	table[2].frequency = घड़ी_प्रकारick / 4;
	table[2].driver_data = 3;
	table[2].frequency = घड़ी_प्रकारick / 6;
	table[2].driver_data = 4;
	table[2].frequency = घड़ी_प्रकारick / 8;
	table[2].driver_data = 5;
	table[3].frequency = CPUFREQ_TABLE_END;

	policy->cpuinfo.transition_latency = 0;
	policy->cur = घड़ी_प्रकारick;
	policy->freq_table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक us2e_freq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अगर (cpufreq_us2e_driver)
		us2e_freq_target(policy, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __init us2e_freq_init(व्योम)
अणु
	अचिन्हित दीर्घ manuf, impl, ver;
	पूर्णांक ret;

	अगर (tlb_type != spitfire)
		वापस -ENODEV;

	__यंत्र__("rdpr %%ver, %0" : "=r" (ver));
	manuf = ((ver >> 48) & 0xffff);
	impl  = ((ver >> 32) & 0xffff);

	अगर (manuf == 0x17 && impl == 0x13) अणु
		काष्ठा cpufreq_driver *driver;

		ret = -ENOMEM;
		driver = kzalloc(माप(*driver), GFP_KERNEL);
		अगर (!driver)
			जाओ err_out;

		us2e_freq_table = kzalloc((NR_CPUS * माप(*us2e_freq_table)),
			GFP_KERNEL);
		अगर (!us2e_freq_table)
			जाओ err_out;

		driver->init = us2e_freq_cpu_init;
		driver->verअगरy = cpufreq_generic_frequency_table_verअगरy;
		driver->target_index = us2e_freq_target;
		driver->get = us2e_freq_get;
		driver->निकास = us2e_freq_cpu_निकास;
		म_नकल(driver->name, "UltraSPARC-IIe");

		cpufreq_us2e_driver = driver;
		ret = cpufreq_रेजिस्टर_driver(driver);
		अगर (ret)
			जाओ err_out;

		वापस 0;

err_out:
		अगर (driver) अणु
			kमुक्त(driver);
			cpufreq_us2e_driver = शून्य;
		पूर्ण
		kमुक्त(us2e_freq_table);
		us2e_freq_table = शून्य;
		वापस ret;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास us2e_freq_निकास(व्योम)
अणु
	अगर (cpufreq_us2e_driver) अणु
		cpufreq_unरेजिस्टर_driver(cpufreq_us2e_driver);
		kमुक्त(cpufreq_us2e_driver);
		cpufreq_us2e_driver = शून्य;
		kमुक्त(us2e_freq_table);
		us2e_freq_table = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("cpufreq driver for UltraSPARC-IIe");
MODULE_LICENSE("GPL");

module_init(us2e_freq_init);
module_निकास(us2e_freq_निकास);
