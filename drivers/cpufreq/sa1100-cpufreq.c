<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cpu-sa1100.c: घड़ी scaling क्रम the SA1100
 *
 * Copyright (C) 2000 2001, The Delft University of Technology
 *
 * Authors:
 * - Johan Pouwअन्यथा (J.A.Pouwअन्यथा@its.tudelft.nl): initial version
 * - Erik Mouw (J.A.K.Mouw@its.tudelft.nl):
 *   - major reग_लिखो क्रम linux-2.3.99
 *   - rewritten क्रम the more generic घातer management scheme in
 *     linux-2.4.5-rmk1
 *
 * This software has been developed जबतक working on the LART
 * computing board (http://www.larपंचांगaker.nl/), which is
 * sponsored by the Mobile Multi-media Communications
 * (http://www.mobimedia.org/) and Ubiquitous Communications
 * (http://www.ubicom.tudelft.nl/) projects.
 *
 * The authors can be reached at:
 *
 *  Erik Mouw
 *  Inक्रमmation and Communication Theory Group
 *  Faculty of Inक्रमmation Technology and Systems
 *  Delft University of Technology
 *  P.O. Box 5031
 *  2600 GA Delft
 *  The Netherlands
 *
 * Theory of operations
 * ====================
 *
 * Clock scaling can be used to lower the घातer consumption of the CPU
 * core. This will give you a somewhat दीर्घer running समय.
 *
 * The SA-1100 has a single रेजिस्टर to change the core घड़ी speed:
 *
 *   PPCR      0x90020014    PLL config
 *
 * However, the DRAM timings are बंदly related to the core घड़ी
 * speed, so we need to change these, too. The used रेजिस्टरs are:
 *
 *   MDCNFG    0xA0000000    DRAM config
 *   MDCAS0    0xA0000004    Access waveक्रमm
 *   MDCAS1    0xA0000008    Access waveक्रमm
 *   MDCAS2    0xA000000C    Access waveक्रमm
 *
 * Care must be taken to change the DRAM parameters the correct way,
 * because otherwise the DRAM becomes unusable and the kernel will
 * crash.
 *
 * The simple solution to aव्योम a kernel crash is to put the actual
 * घड़ी change in ROM and jump to that code from the kernel. The मुख्य
 * disadvantage is that the ROM has to be modअगरied, which is not
 * possible on all SA-1100 platक्रमms. Another disadvantage is that
 * jumping to ROM makes घड़ी चयनing unnecessary complicated.
 *
 * The idea behind this driver is that the memory configuration can be
 * changed जबतक running from DRAM (even with पूर्णांकerrupts turned on!)
 * as दीर्घ as all re-configuration steps yield a valid DRAM
 * configuration. The advantages are clear: it will run on all SA-1100
 * platक्रमms, and the code is very simple.
 *
 * If you really want to understand what is going on in
 * sa1100_update_dram_timings(), you'll have to पढ़ो sections 8.2,
 * 9.5.7.3, and 10.2 from the "Intel StrongARM SA-1100 Microprocessor
 * Developers Manual" (available क्रम मुक्त from Intel).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cputype.h>

#समावेश <mach/generic.h>
#समावेश <mach/hardware.h>

काष्ठा sa1100_dram_regs अणु
	पूर्णांक speed;
	u32 mdcnfg;
	u32 mdcas0;
	u32 mdcas1;
	u32 mdcas2;
पूर्ण;


अटल काष्ठा cpufreq_driver sa1100_driver;

अटल काष्ठा sa1100_dram_regs sa1100_dram_settings[] = अणु
	/*speed,     mdcnfg,     mdcas0,     mdcas1,     mdcas2,   घड़ी freq */
	अणु 59000, 0x00dc88a3, 0xcccccccf, 0xfffffffc, 0xffffffffपूर्ण,/*  59.0 MHz */
	अणु 73700, 0x011490a3, 0xcccccccf, 0xfffffffc, 0xffffffffपूर्ण,/*  73.7 MHz */
	अणु 88500, 0x014e90a3, 0xcccccccf, 0xfffffffc, 0xffffffffपूर्ण,/*  88.5 MHz */
	अणु103200, 0x01889923, 0xcccccccf, 0xfffffffc, 0xffffffffपूर्ण,/* 103.2 MHz */
	अणु118000, 0x01c29923, 0x9999998f, 0xfffffff9, 0xffffffffपूर्ण,/* 118.0 MHz */
	अणु132700, 0x01fb2123, 0x9999998f, 0xfffffff9, 0xffffffffपूर्ण,/* 132.7 MHz */
	अणु147500, 0x02352123, 0x3333330f, 0xfffffff3, 0xffffffffपूर्ण,/* 147.5 MHz */
	अणु162200, 0x026b29a3, 0x38e38e1f, 0xfff8e38e, 0xffffffffपूर्ण,/* 162.2 MHz */
	अणु176900, 0x02a329a3, 0x71c71c1f, 0xfff1c71c, 0xffffffffपूर्ण,/* 176.9 MHz */
	अणु191700, 0x02dd31a3, 0xe38e383f, 0xffe38e38, 0xffffffffपूर्ण,/* 191.7 MHz */
	अणु206400, 0x03153223, 0xc71c703f, 0xffc71c71, 0xffffffffपूर्ण,/* 206.4 MHz */
	अणु221200, 0x034fba23, 0xc71c703f, 0xffc71c71, 0xffffffffपूर्ण,/* 221.2 MHz */
	अणु235900, 0x03853a23, 0xe1e1e07f, 0xe1e1e1e1, 0xffffffe1पूर्ण,/* 235.9 MHz */
	अणु250700, 0x03bf3aa3, 0xc3c3c07f, 0xc3c3c3c3, 0xffffffc3पूर्ण,/* 250.7 MHz */
	अणु265400, 0x03f7c2a3, 0xc3c3c07f, 0xc3c3c3c3, 0xffffffc3पूर्ण,/* 265.4 MHz */
	अणु280200, 0x0431c2a3, 0x878780ff, 0x87878787, 0xffffff87पूर्ण,/* 280.2 MHz */
	अणु 0, 0, 0, 0, 0 पूर्ण /* last entry */
पूर्ण;

अटल व्योम sa1100_update_dram_timings(पूर्णांक current_speed, पूर्णांक new_speed)
अणु
	काष्ठा sa1100_dram_regs *settings = sa1100_dram_settings;

	/* find speed */
	जबतक (settings->speed != 0) अणु
		अगर (new_speed == settings->speed)
			अवरोध;

		settings++;
	पूर्ण

	अगर (settings->speed == 0) अणु
		panic("%s: couldn't find dram setting for speed %d\n",
		      __func__, new_speed);
	पूर्ण

	/* No risk, no fun: run with पूर्णांकerrupts on! */
	अगर (new_speed > current_speed) अणु
		/* We're going FASTER, so first relax the memory
		 * timings beक्रमe changing the core frequency
		 */

		/* Half the memory access घड़ी */
		MDCNFG |= MDCNFG_CDB2;

		/* The order of these statements IS important, keep 8
		 * pulses!!
		 */
		MDCAS2 = settings->mdcas2;
		MDCAS1 = settings->mdcas1;
		MDCAS0 = settings->mdcas0;
		MDCNFG = settings->mdcnfg;
	पूर्ण अन्यथा अणु
		/* We're going SLOWER: first decrease the core
		 * frequency and then tighten the memory settings.
		 */

		/* Half the memory access घड़ी */
		MDCNFG |= MDCNFG_CDB2;

		/* The order of these statements IS important, keep 8
		 * pulses!!
		 */
		MDCAS0 = settings->mdcas0;
		MDCAS1 = settings->mdcas1;
		MDCAS2 = settings->mdcas2;
		MDCNFG = settings->mdcnfg;
	पूर्ण
पूर्ण

अटल पूर्णांक sa1100_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक ppcr)
अणु
	अचिन्हित पूर्णांक cur = sa11x0_माला_लोpeed(0);
	अचिन्हित पूर्णांक new_freq;

	new_freq = sa11x0_freq_table[ppcr].frequency;

	अगर (new_freq > cur)
		sa1100_update_dram_timings(cur, new_freq);

	PPCR = ppcr;

	अगर (new_freq < cur)
		sa1100_update_dram_timings(cur, new_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init sa1100_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, sa11x0_freq_table, 0);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver sa1100_driver __refdata = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK |
			  CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= sa1100_target,
	.get		= sa11x0_माला_लोpeed,
	.init		= sa1100_cpu_init,
	.name		= "sa1100",
पूर्ण;

अटल पूर्णांक __init sa1100_dram_init(व्योम)
अणु
	अगर (cpu_is_sa1100())
		वापस cpufreq_रेजिस्टर_driver(&sa1100_driver);
	अन्यथा
		वापस -ENODEV;
पूर्ण

arch_initcall(sa1100_dram_init);
