<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008 Marvell International Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <mach/generic.h>
#समावेश <mach/pxa3xx-regs.h>

#घोषणा HSS_104M	(0)
#घोषणा HSS_156M	(1)
#घोषणा HSS_208M	(2)
#घोषणा HSS_312M	(3)

#घोषणा SMCFS_78M	(0)
#घोषणा SMCFS_104M	(2)
#घोषणा SMCFS_208M	(5)

#घोषणा SFLFS_104M	(0)
#घोषणा SFLFS_156M	(1)
#घोषणा SFLFS_208M	(2)
#घोषणा SFLFS_312M	(3)

#घोषणा XSPCLK_156M	(0)
#घोषणा XSPCLK_NONE	(3)

#घोषणा DMCFS_26M	(0)
#घोषणा DMCFS_260M	(3)

काष्ठा pxa3xx_freq_info अणु
	अचिन्हित पूर्णांक cpufreq_mhz;
	अचिन्हित पूर्णांक core_xl : 5;
	अचिन्हित पूर्णांक core_xn : 3;
	अचिन्हित पूर्णांक hss : 2;
	अचिन्हित पूर्णांक dmcfs : 2;
	अचिन्हित पूर्णांक smcfs : 3;
	अचिन्हित पूर्णांक sflfs : 2;
	अचिन्हित पूर्णांक df_clkभाग : 3;

	पूर्णांक	vcc_core;	/* in mV */
	पूर्णांक	vcc_sram;	/* in mV */
पूर्ण;

#घोषणा OP(cpufreq, _xl, _xn, _hss, _dmc, _smc, _sfl, _dfi, vcore, vsram) \
अणु									\
	.cpufreq_mhz	= cpufreq,					\
	.core_xl	= _xl,						\
	.core_xn	= _xn,						\
	.hss		= HSS_##_hss##M,				\
	.dmcfs		= DMCFS_##_dmc##M,				\
	.smcfs		= SMCFS_##_smc##M,				\
	.sflfs		= SFLFS_##_sfl##M,				\
	.df_clkभाग	= _dfi,						\
	.vcc_core	= vcore,					\
	.vcc_sram	= vsram,					\
पूर्ण

अटल काष्ठा pxa3xx_freq_info pxa300_freqs[] = अणु
	/*  CPU XL XN  HSS DMEM SMEM SRAM DFI VCC_CORE VCC_SRAM */
	OP(104,  8, 1, 104, 260,  78, 104, 3, 1000, 1100), /* 104MHz */
	OP(208, 16, 1, 104, 260, 104, 156, 2, 1000, 1100), /* 208MHz */
	OP(416, 16, 2, 156, 260, 104, 208, 2, 1100, 1200), /* 416MHz */
	OP(624, 24, 2, 208, 260, 208, 312, 3, 1375, 1400), /* 624MHz */
पूर्ण;

अटल काष्ठा pxa3xx_freq_info pxa320_freqs[] = अणु
	/*  CPU XL XN  HSS DMEM SMEM SRAM DFI VCC_CORE VCC_SRAM */
	OP(104,  8, 1, 104, 260,  78, 104, 3, 1000, 1100), /* 104MHz */
	OP(208, 16, 1, 104, 260, 104, 156, 2, 1000, 1100), /* 208MHz */
	OP(416, 16, 2, 156, 260, 104, 208, 2, 1100, 1200), /* 416MHz */
	OP(624, 24, 2, 208, 260, 208, 312, 3, 1375, 1400), /* 624MHz */
	OP(806, 31, 2, 208, 260, 208, 312, 3, 1400, 1400), /* 806MHz */
पूर्ण;

अटल अचिन्हित पूर्णांक pxa3xx_freqs_num;
अटल काष्ठा pxa3xx_freq_info *pxa3xx_freqs;
अटल काष्ठा cpufreq_frequency_table *pxa3xx_freqs_table;

अटल पूर्णांक setup_freqs_table(काष्ठा cpufreq_policy *policy,
			     काष्ठा pxa3xx_freq_info *freqs, पूर्णांक num)
अणु
	काष्ठा cpufreq_frequency_table *table;
	पूर्णांक i;

	table = kसुस्मृति(num + 1, माप(*table), GFP_KERNEL);
	अगर (table == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		table[i].driver_data = i;
		table[i].frequency = freqs[i].cpufreq_mhz * 1000;
	पूर्ण
	table[num].driver_data = i;
	table[num].frequency = CPUFREQ_TABLE_END;

	pxa3xx_freqs = freqs;
	pxa3xx_freqs_num = num;
	pxa3xx_freqs_table = table;

	policy->freq_table = table;

	वापस 0;
पूर्ण

अटल व्योम __update_core_freq(काष्ठा pxa3xx_freq_info *info)
अणु
	uपूर्णांक32_t mask = ACCR_XN_MASK | ACCR_XL_MASK;
	uपूर्णांक32_t accr = ACCR;
	uपूर्णांक32_t xclkcfg;

	accr &= ~(ACCR_XN_MASK | ACCR_XL_MASK | ACCR_XSPCLK_MASK);
	accr |= ACCR_XN(info->core_xn) | ACCR_XL(info->core_xl);

	/* No घड़ी until core PLL is re-locked */
	accr |= ACCR_XSPCLK(XSPCLK_NONE);

	xclkcfg = (info->core_xn == 2) ? 0x3 : 0x2;	/* turbo bit */

	ACCR = accr;
	__यंत्र__("mcr p14, 0, %0, c6, c0, 0\n" : : "r"(xclkcfg));

	जबतक ((ACSR & mask) != (accr & mask))
		cpu_relax();
पूर्ण

अटल व्योम __update_bus_freq(काष्ठा pxa3xx_freq_info *info)
अणु
	uपूर्णांक32_t mask;
	uपूर्णांक32_t accr = ACCR;

	mask = ACCR_SMCFS_MASK | ACCR_SFLFS_MASK | ACCR_HSS_MASK |
		ACCR_DMCFS_MASK;

	accr &= ~mask;
	accr |= ACCR_SMCFS(info->smcfs) | ACCR_SFLFS(info->sflfs) |
		ACCR_HSS(info->hss) | ACCR_DMCFS(info->dmcfs);

	ACCR = accr;

	जबतक ((ACSR & mask) != (accr & mask))
		cpu_relax();
पूर्ण

अटल अचिन्हित पूर्णांक pxa3xx_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	वापस pxa3xx_get_clk_frequency_khz(0);
पूर्ण

अटल पूर्णांक pxa3xx_cpufreq_set(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	काष्ठा pxa3xx_freq_info *next;
	अचिन्हित दीर्घ flags;

	अगर (policy->cpu != 0)
		वापस -EINVAL;

	next = &pxa3xx_freqs[index];

	local_irq_save(flags);
	__update_core_freq(next);
	__update_bus_freq(next);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa3xx_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret = -EINVAL;

	/* set शेष policy and cpuinfo */
	policy->min = policy->cpuinfo.min_freq = 104000;
	policy->max = policy->cpuinfo.max_freq =
		(cpu_is_pxa320()) ? 806000 : 624000;
	policy->cpuinfo.transition_latency = 1000; /* FIXME: 1 ms, assumed */

	अगर (cpu_is_pxa300() || cpu_is_pxa310())
		ret = setup_freqs_table(policy, pxa300_freqs,
					ARRAY_SIZE(pxa300_freqs));

	अगर (cpu_is_pxa320())
		ret = setup_freqs_table(policy, pxa320_freqs,
					ARRAY_SIZE(pxa320_freqs));

	अगर (ret) अणु
		pr_err("failed to setup frequency table\n");
		वापस ret;
	पूर्ण

	pr_info("CPUFREQ support for PXA3xx initialized\n");
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver pxa3xx_cpufreq_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= pxa3xx_cpufreq_set,
	.init		= pxa3xx_cpufreq_init,
	.get		= pxa3xx_cpufreq_get,
	.name		= "pxa3xx-cpufreq",
पूर्ण;

अटल पूर्णांक __init cpufreq_init(व्योम)
अणु
	अगर (cpu_is_pxa3xx())
		वापस cpufreq_रेजिस्टर_driver(&pxa3xx_cpufreq_driver);

	वापस 0;
पूर्ण
module_init(cpufreq_init);

अटल व्योम __निकास cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&pxa3xx_cpufreq_driver);
पूर्ण
module_निकास(cpufreq_निकास);

MODULE_DESCRIPTION("CPU frequency scaling driver for PXA3xx");
MODULE_LICENSE("GPL");
