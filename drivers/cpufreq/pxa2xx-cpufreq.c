<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2002,2003 Intrinsyc Software
 *
 * History:
 *   31-Jul-2002 : Initial version [FB]
 *   29-Jan-2003 : added PXA255 support [FB]
 *   20-Apr-2003 : ported to v2.5 (Dustin McIntire, Sensoria Corp.)
 *
 * Note:
 *   This driver may change the memory bus घड़ी rate, but will not करो any
 *   platक्रमm specअगरic access timing changes... क्रम example अगर you have flash
 *   memory connected to CS0, you will need to रेजिस्टर a platक्रमm specअगरic
 *   notअगरier which will adjust the memory access strobes to मुख्यtain a
 *   minimum strobe width.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/पन.स>

#समावेश <mach/pxa2xx-regs.h>
#समावेश <mach/smemc.h>

#अगर_घोषित DEBUG
अटल अचिन्हित पूर्णांक freq_debug;
module_param(freq_debug, uपूर्णांक, 0);
MODULE_PARM_DESC(freq_debug, "Set the debug messages to on=1/off=0");
#अन्यथा
#घोषणा freq_debug  0
#पूर्ण_अगर

अटल काष्ठा regulator *vcc_core;

अटल अचिन्हित पूर्णांक pxa27x_maxfreq;
module_param(pxa27x_maxfreq, uपूर्णांक, 0);
MODULE_PARM_DESC(pxa27x_maxfreq, "Set the pxa27x maxfreq in MHz"
		 "(typically 624=>pxa270, 416=>pxa271, 520=>pxa272)");

काष्ठा pxa_cpufreq_data अणु
	काष्ठा clk *clk_core;
पूर्ण;
अटल काष्ठा pxa_cpufreq_data  pxa_cpufreq_data;

काष्ठा pxa_freqs अणु
	अचिन्हित पूर्णांक khz;
	पूर्णांक vmin;
	पूर्णांक vmax;
पूर्ण;

/*
 * PXA255 definitions
 */
अटल स्थिर काष्ठा pxa_freqs pxa255_run_freqs[] =
अणु
	/* CPU   MEMBUS		   run  turbo PXbus SDRAM */
	अणु 99500, -1, -1पूर्ण,	/*  99,   99,   50,   50  */
	अणु132700, -1, -1पूर्ण,	/* 133,  133,   66,   66  */
	अणु199100, -1, -1पूर्ण,	/* 199,  199,   99,   99  */
	अणु265400, -1, -1पूर्ण,	/* 265,  265,  133,   66  */
	अणु331800, -1, -1पूर्ण,	/* 331,  331,  166,   83  */
	अणु398100, -1, -1पूर्ण,	/* 398,  398,  196,   99  */
पूर्ण;

/* Use the turbo mode frequencies क्रम the CPUFREQ_POLICY_POWERSAVE policy */
अटल स्थिर काष्ठा pxa_freqs pxa255_turbo_freqs[] =
अणु
	/* CPU			   run  turbo PXbus SDRAM */
	अणु 99500, -1, -1पूर्ण,	/*  99,   99,   50,   50  */
	अणु199100, -1, -1पूर्ण,	/*  99,  199,   50,   99  */
	अणु298500, -1, -1पूर्ण,	/*  99,  287,   50,   99  */
	अणु298600, -1, -1पूर्ण,	/* 199,  287,   99,   99  */
	अणु398100, -1, -1पूर्ण,	/* 199,  398,   99,   99  */
पूर्ण;

#घोषणा NUM_PXA25x_RUN_FREQS ARRAY_SIZE(pxa255_run_freqs)
#घोषणा NUM_PXA25x_TURBO_FREQS ARRAY_SIZE(pxa255_turbo_freqs)

अटल काष्ठा cpufreq_frequency_table
	pxa255_run_freq_table[NUM_PXA25x_RUN_FREQS+1];
अटल काष्ठा cpufreq_frequency_table
	pxa255_turbo_freq_table[NUM_PXA25x_TURBO_FREQS+1];

अटल अचिन्हित पूर्णांक pxa255_turbo_table;
module_param(pxa255_turbo_table, uपूर्णांक, 0);
MODULE_PARM_DESC(pxa255_turbo_table, "Selects the frequency table (0 = run table, !0 = turbo table)");

अटल काष्ठा pxa_freqs pxa27x_freqs[] = अणु
	अणु104000,  900000, 1705000 पूर्ण,
	अणु156000, 1000000, 1705000 पूर्ण,
	अणु208000, 1180000, 1705000 पूर्ण,
	अणु312000, 1250000, 1705000 पूर्ण,
	अणु416000, 1350000, 1705000 पूर्ण,
	अणु520000, 1450000, 1705000 पूर्ण,
	अणु624000, 1550000, 1705000 पूर्ण
पूर्ण;

#घोषणा NUM_PXA27x_FREQS ARRAY_SIZE(pxa27x_freqs)
अटल काष्ठा cpufreq_frequency_table
	pxa27x_freq_table[NUM_PXA27x_FREQS+1];

बाह्य अचिन्हित get_clk_frequency_khz(पूर्णांक info);

#अगर_घोषित CONFIG_REGULATOR

अटल पूर्णांक pxa_cpufreq_change_voltage(स्थिर काष्ठा pxa_freqs *pxa_freq)
अणु
	पूर्णांक ret = 0;
	पूर्णांक vmin, vmax;

	अगर (!cpu_is_pxa27x())
		वापस 0;

	vmin = pxa_freq->vmin;
	vmax = pxa_freq->vmax;
	अगर ((vmin == -1) || (vmax == -1))
		वापस 0;

	ret = regulator_set_voltage(vcc_core, vmin, vmax);
	अगर (ret)
		pr_err("Failed to set vcc_core in [%dmV..%dmV]\n", vmin, vmax);
	वापस ret;
पूर्ण

अटल व्योम pxa_cpufreq_init_voltages(व्योम)
अणु
	vcc_core = regulator_get(शून्य, "vcc_core");
	अगर (IS_ERR(vcc_core)) अणु
		pr_info("Didn't find vcc_core regulator\n");
		vcc_core = शून्य;
	पूर्ण अन्यथा अणु
		pr_info("Found vcc_core regulator\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल पूर्णांक pxa_cpufreq_change_voltage(स्थिर काष्ठा pxa_freqs *pxa_freq)
अणु
	वापस 0;
पूर्ण

अटल व्योम pxa_cpufreq_init_voltages(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम find_freq_tables(काष्ठा cpufreq_frequency_table **freq_table,
			     स्थिर काष्ठा pxa_freqs **pxa_freqs)
अणु
	अगर (cpu_is_pxa25x()) अणु
		अगर (!pxa255_turbo_table) अणु
			*pxa_freqs = pxa255_run_freqs;
			*freq_table = pxa255_run_freq_table;
		पूर्ण अन्यथा अणु
			*pxa_freqs = pxa255_turbo_freqs;
			*freq_table = pxa255_turbo_freq_table;
		पूर्ण
	पूर्ण अन्यथा अगर (cpu_is_pxa27x()) अणु
		*pxa_freqs = pxa27x_freqs;
		*freq_table = pxa27x_freq_table;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण

अटल व्योम pxa27x_guess_max_freq(व्योम)
अणु
	अगर (!pxa27x_maxfreq) अणु
		pxa27x_maxfreq = 416000;
		pr_info("PXA CPU 27x max frequency not defined (pxa27x_maxfreq), assuming pxa271 with %dkHz maxfreq\n",
			pxa27x_maxfreq);
	पूर्ण अन्यथा अणु
		pxa27x_maxfreq *= 1000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक pxa_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pxa_cpufreq_data *data = cpufreq_get_driver_data();

	वापस (अचिन्हित पूर्णांक) clk_get_rate(data->clk_core) / 1000;
पूर्ण

अटल पूर्णांक pxa_set_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा cpufreq_frequency_table *pxa_freqs_table;
	स्थिर काष्ठा pxa_freqs *pxa_freq_settings;
	काष्ठा pxa_cpufreq_data *data = cpufreq_get_driver_data();
	अचिन्हित पूर्णांक new_freq_cpu;
	पूर्णांक ret = 0;

	/* Get the current policy */
	find_freq_tables(&pxa_freqs_table, &pxa_freq_settings);

	new_freq_cpu = pxa_freq_settings[idx].khz;

	अगर (freq_debug)
		pr_debug("Changing CPU frequency from %d Mhz to %d Mhz\n",
			 policy->cur / 1000,  new_freq_cpu / 1000);

	अगर (vcc_core && new_freq_cpu > policy->cur) अणु
		ret = pxa_cpufreq_change_voltage(&pxa_freq_settings[idx]);
		अगर (ret)
			वापस ret;
	पूर्ण

	clk_set_rate(data->clk_core, new_freq_cpu * 1000);

	/*
	 * Even अगर voltage setting fails, we करोn't report it, as the frequency
	 * change succeeded. The voltage reduction is not a critical failure,
	 * only घातer savings will suffer from this.
	 *
	 * Note: अगर the voltage change fails, and a वापस value is वापसed, a
	 * bug is triggered (seems a deadlock). Should anybody find out where,
	 * the "return 0" should become a "return ret".
	 */
	अगर (vcc_core && new_freq_cpu < policy->cur)
		ret = pxa_cpufreq_change_voltage(&pxa_freq_settings[idx]);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक freq;
	काष्ठा cpufreq_frequency_table *pxa255_freq_table;
	स्थिर काष्ठा pxa_freqs *pxa255_freqs;

	/* try to guess pxa27x cpu */
	अगर (cpu_is_pxa27x())
		pxa27x_guess_max_freq();

	pxa_cpufreq_init_voltages();

	/* set शेष policy and cpuinfo */
	policy->cpuinfo.transition_latency = 1000; /* FIXME: 1 ms, assumed */

	/* Generate pxa25x the run cpufreq_frequency_table काष्ठा */
	क्रम (i = 0; i < NUM_PXA25x_RUN_FREQS; i++) अणु
		pxa255_run_freq_table[i].frequency = pxa255_run_freqs[i].khz;
		pxa255_run_freq_table[i].driver_data = i;
	पूर्ण
	pxa255_run_freq_table[i].frequency = CPUFREQ_TABLE_END;

	/* Generate pxa25x the turbo cpufreq_frequency_table काष्ठा */
	क्रम (i = 0; i < NUM_PXA25x_TURBO_FREQS; i++) अणु
		pxa255_turbo_freq_table[i].frequency =
			pxa255_turbo_freqs[i].khz;
		pxa255_turbo_freq_table[i].driver_data = i;
	पूर्ण
	pxa255_turbo_freq_table[i].frequency = CPUFREQ_TABLE_END;

	pxa255_turbo_table = !!pxa255_turbo_table;

	/* Generate the pxa27x cpufreq_frequency_table काष्ठा */
	क्रम (i = 0; i < NUM_PXA27x_FREQS; i++) अणु
		freq = pxa27x_freqs[i].khz;
		अगर (freq > pxa27x_maxfreq)
			अवरोध;
		pxa27x_freq_table[i].frequency = freq;
		pxa27x_freq_table[i].driver_data = i;
	पूर्ण
	pxa27x_freq_table[i].driver_data = i;
	pxa27x_freq_table[i].frequency = CPUFREQ_TABLE_END;

	/*
	 * Set the policy's minimum and maximum frequencies from the tables
	 * just स्थिरructed.  This sets cpuinfo.mxx_freq, min and max.
	 */
	अगर (cpu_is_pxa25x()) अणु
		find_freq_tables(&pxa255_freq_table, &pxa255_freqs);
		pr_info("using %s frequency table\n",
			pxa255_turbo_table ? "turbo" : "run");

		policy->freq_table = pxa255_freq_table;
	पूर्ण
	अन्यथा अगर (cpu_is_pxa27x()) अणु
		policy->freq_table = pxa27x_freq_table;
	पूर्ण

	pr_info("frequency change support initialized\n");

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver pxa_cpufreq_driver = अणु
	.flags	= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.target_index = pxa_set_target,
	.init	= pxa_cpufreq_init,
	.get	= pxa_cpufreq_get,
	.name	= "PXA2xx",
	.driver_data = &pxa_cpufreq_data,
पूर्ण;

अटल पूर्णांक __init pxa_cpu_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	pxa_cpufreq_data.clk_core = clk_get_sys(शून्य, "core");
	अगर (IS_ERR(pxa_cpufreq_data.clk_core))
		वापस PTR_ERR(pxa_cpufreq_data.clk_core);

	अगर (cpu_is_pxa25x() || cpu_is_pxa27x())
		ret = cpufreq_रेजिस्टर_driver(&pxa_cpufreq_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास pxa_cpu_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&pxa_cpufreq_driver);
पूर्ण


MODULE_AUTHOR("Intrinsyc Software Inc.");
MODULE_DESCRIPTION("CPU frequency changing driver for the PXA architecture");
MODULE_LICENSE("GPL");
module_init(pxa_cpu_init);
module_निकास(pxa_cpu_निकास);
