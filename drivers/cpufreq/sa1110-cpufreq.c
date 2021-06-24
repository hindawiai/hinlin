<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-sa1100/cpu-sa1110.c
 *
 *  Copyright (C) 2001 Russell King
 *
 * Note: there are two erratas that apply to the SA1110 here:
 *  7 - SDRAM स्वतः-घातer-up failure (rev A0)
 * 13 - Corruption of पूर्णांकernal रेजिस्टर पढ़ोs/ग_लिखोs following
 *      SDRAM पढ़ोs (rev A0, B0, B1)
 *
 * We ignore rev. A0 and B0 devices; I करोn't think they're worth supporting.
 *
 * The SDRAM type can be passed on the command line as cpu_sa1110.sdram=type
 */
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/generic.h>
#समावेश <mach/hardware.h>

#अघोषित DEBUG

काष्ठा sdram_params अणु
	स्थिर अक्षर name[20];
	u_अक्षर  rows;		/* bits				 */
	u_अक्षर  cas_latency;	/* cycles			 */
	u_अक्षर  tck;		/* घड़ी cycle समय (ns)	 */
	u_अक्षर  trcd;		/* activate to r/w (ns)		 */
	u_अक्षर  trp;		/* preअक्षरge to activate (ns)	 */
	u_अक्षर  twr;		/* ग_लिखो recovery समय (ns)	 */
	u_लघु refresh;	/* refresh समय क्रम array (us)	 */
पूर्ण;

काष्ठा sdram_info अणु
	u_पूर्णांक	mdcnfg;
	u_पूर्णांक	mdrefr;
	u_पूर्णांक	mdcas[3];
पूर्ण;

अटल काष्ठा sdram_params sdram_tbl[] __initdata = अणु
	अणु	/* Toshiba TC59SM716 CL2 */
		.name		= "TC59SM716-CL2",
		.rows		= 12,
		.tck		= 10,
		.trcd		= 20,
		.trp		= 20,
		.twr		= 10,
		.refresh	= 64000,
		.cas_latency	= 2,
	पूर्ण, अणु	/* Toshiba TC59SM716 CL3 */
		.name		= "TC59SM716-CL3",
		.rows		= 12,
		.tck		= 8,
		.trcd		= 20,
		.trp		= 20,
		.twr		= 8,
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण, अणु	/* Samsung K4S641632D TC75 */
		.name		= "K4S641632D",
		.rows		= 14,
		.tck		= 9,
		.trcd		= 27,
		.trp		= 20,
		.twr		= 9,
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण, अणु	/* Samsung K4S281632B-1H */
		.name           = "K4S281632B-1H",
		.rows		= 12,
		.tck		= 10,
		.trp		= 20,
		.twr		= 10,
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण, अणु	/* Samsung KM416S4030CT */
		.name		= "KM416S4030CT",
		.rows		= 13,
		.tck		= 8,
		.trcd		= 24,	/* 3 CLKs */
		.trp		= 24,	/* 3 CLKs */
		.twr		= 16,	/* Trdl: 2 CLKs */
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण, अणु	/* Winbond W982516AH75L CL3 */
		.name		= "W982516AH75L",
		.rows		= 16,
		.tck		= 8,
		.trcd		= 20,
		.trp		= 20,
		.twr		= 8,
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण, अणु	/* Micron MT48LC8M16A2TG-75 */
		.name		= "MT48LC8M16A2TG-75",
		.rows		= 12,
		.tck		= 8,
		.trcd		= 20,
		.trp		= 20,
		.twr		= 8,
		.refresh	= 64000,
		.cas_latency	= 3,
	पूर्ण,
पूर्ण;

अटल काष्ठा sdram_params sdram_params;

/*
 * Given a period in ns and frequency in khz, calculate the number of
 * cycles of frequency in period.  Note that we round up to the next
 * cycle, even अगर we are only slightly over.
 */
अटल अंतरभूत u_पूर्णांक ns_to_cycles(u_पूर्णांक ns, u_पूर्णांक khz)
अणु
	वापस (ns * khz + 999999) / 1000000;
पूर्ण

/*
 * Create the MDCAS रेजिस्टर bit pattern.
 */
अटल अंतरभूत व्योम set_mdcas(u_पूर्णांक *mdcas, पूर्णांक delayed, u_पूर्णांक rcd)
अणु
	u_पूर्णांक shअगरt;

	rcd = 2 * rcd - 1;
	shअगरt = delayed + 1 + rcd;

	mdcas[0]  = (1 << rcd) - 1;
	mdcas[0] |= 0x55555555 << shअगरt;
	mdcas[1]  = mdcas[2] = 0x55555555 << (shअगरt & 1);
पूर्ण

अटल व्योम
sdram_calculate_timing(काष्ठा sdram_info *sd, u_पूर्णांक cpu_khz,
		       काष्ठा sdram_params *sdram)
अणु
	u_पूर्णांक mem_khz, sd_khz, trp, twr;

	mem_khz = cpu_khz / 2;
	sd_khz = mem_khz;

	/*
	 * If SDCLK would invalidate the SDRAM timings,
	 * run SDCLK at half speed.
	 *
	 * CPU steppings prior to B2 must either run the memory at
	 * half speed or use delayed पढ़ो latching (errata 13).
	 */
	अगर ((ns_to_cycles(sdram->tck, sd_khz) > 1) ||
	    (पढ़ो_cpuid_revision() < ARM_CPU_REV_SA1110_B2 && sd_khz < 62000))
		sd_khz /= 2;

	sd->mdcnfg = MDCNFG & 0x007f007f;

	twr = ns_to_cycles(sdram->twr, mem_khz);

	/* trp should always be >1 */
	trp = ns_to_cycles(sdram->trp, mem_khz) - 1;
	अगर (trp < 1)
		trp = 1;

	sd->mdcnfg |= trp << 8;
	sd->mdcnfg |= trp << 24;
	sd->mdcnfg |= sdram->cas_latency << 12;
	sd->mdcnfg |= sdram->cas_latency << 28;
	sd->mdcnfg |= twr << 14;
	sd->mdcnfg |= twr << 30;

	sd->mdrefr = MDREFR & 0xffbffff0;
	sd->mdrefr |= 7;

	अगर (sd_khz != mem_khz)
		sd->mdrefr |= MDREFR_K1DB2;

	/* initial number of '1's in MDCAS + 1 */
	set_mdcas(sd->mdcas, sd_khz >= 62000,
		ns_to_cycles(sdram->trcd, mem_khz));

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "MDCNFG: %08x MDREFR: %08x MDCAS0: %08x MDCAS1: %08x MDCAS2: %08x\n",
		sd->mdcnfg, sd->mdrefr, sd->mdcas[0], sd->mdcas[1],
		sd->mdcas[2]);
#पूर्ण_अगर
पूर्ण

/*
 * Set the SDRAM refresh rate.
 */
अटल अंतरभूत व्योम sdram_set_refresh(u_पूर्णांक dri)
अणु
	MDREFR = (MDREFR & 0xffff000f) | (dri << 4);
	(व्योम) MDREFR;
पूर्ण

/*
 * Update the refresh period.  We करो this such that we always refresh
 * the SDRAMs within their permissible period.  The refresh period is
 * always a multiple of the memory घड़ी (fixed at cpu_घड़ी / 2).
 *
 * FIXME: we करोn't currently take account of burst accesses here,
 * but neither करो Intels DM nor Angel.
 */
अटल व्योम
sdram_update_refresh(u_पूर्णांक cpu_khz, काष्ठा sdram_params *sdram)
अणु
	u_पूर्णांक ns_row = (sdram->refresh * 1000) >> sdram->rows;
	u_पूर्णांक dri = ns_to_cycles(ns_row, cpu_khz / 2) / 32;

#अगर_घोषित DEBUG
	mdelay(250);
	prपूर्णांकk(KERN_DEBUG "new dri value = %d\n", dri);
#पूर्ण_अगर

	sdram_set_refresh(dri);
पूर्ण

/*
 * Ok, set the CPU frequency.
 */
अटल पूर्णांक sa1110_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक ppcr)
अणु
	काष्ठा sdram_params *sdram = &sdram_params;
	काष्ठा sdram_info sd;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक unused;

	sdram_calculate_timing(&sd, sa11x0_freq_table[ppcr].frequency, sdram);

#अगर 0
	/*
	 * These values are wrong according to the SA1110 करोcumentation
	 * and errata, but they seem to work.  Need to get a storage
	 * scope on to the SDRAM संकेतs to work out why.
	 */
	अगर (policy->max < 147500) अणु
		sd.mdrefr |= MDREFR_K1DB2;
		sd.mdcas[0] = 0xaaaaaa7f;
	पूर्ण अन्यथा अणु
		sd.mdrefr &= ~MDREFR_K1DB2;
		sd.mdcas[0] = 0xaaaaaa9f;
	पूर्ण
	sd.mdcas[1] = 0xaaaaaaaa;
	sd.mdcas[2] = 0xaaaaaaaa;
#पूर्ण_अगर

	/*
	 * The घड़ी could be going away क्रम some समय.  Set the SDRAMs
	 * to refresh rapidly (every 64 memory घड़ी cycles).  To get
	 * through the whole array, we need to रुको 262144 mclk cycles.
	 * We रुको 20ms to be safe.
	 */
	sdram_set_refresh(2);
	अगर (!irqs_disabled())
		msleep(20);
	अन्यथा
		mdelay(20);

	/*
	 * Reprogram the DRAM timings with पूर्णांकerrupts disabled, and
	 * ensure that we are करोing this within a complete cache line.
	 * This means that we won't access SDRAM क्रम the duration of
	 * the programming.
	 */
	local_irq_save(flags);
	यंत्र("mcr p15, 0, %0, c7, c10, 4" : : "r" (0));
	udelay(10);
	__यंत्र__ __अस्थिर__("\न\
		b	2f					\न\
		.align	5					\न\
1:		str	%3, [%1, #0]		@ MDCNFG	\न\
		str	%4, [%1, #28]		@ MDREFR	\न\
		str	%5, [%1, #4]		@ MDCAS0	\न\
		str	%6, [%1, #8]		@ MDCAS1	\न\
		str	%7, [%1, #12]		@ MDCAS2	\न\
		str	%8, [%2, #0]		@ PPCR		\न\
		ldr	%0, [%1, #0]				\न\
		b	3f					\न\
2:		b	1b					\न\
3:		nop						\न\
		nop"
		: "=&r" (unused)
		: "r" (&MDCNFG), "r" (&PPCR), "0" (sd.mdcnfg),
		  "r" (sd.mdrefr), "r" (sd.mdcas[0]),
		  "r" (sd.mdcas[1]), "r" (sd.mdcas[2]), "r" (ppcr));
	local_irq_restore(flags);

	/*
	 * Now, वापस the SDRAM refresh back to normal.
	 */
	sdram_update_refresh(sa11x0_freq_table[ppcr].frequency, sdram);

	वापस 0;
पूर्ण

अटल पूर्णांक __init sa1110_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, sa11x0_freq_table, 0);
	वापस 0;
पूर्ण

/* sa1110_driver needs __refdata because it must reमुख्य after init रेजिस्टरs
 * it with cpufreq_रेजिस्टर_driver() */
अटल काष्ठा cpufreq_driver sa1110_driver __refdata = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK |
			  CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= sa1110_target,
	.get		= sa11x0_माला_लोpeed,
	.init		= sa1110_cpu_init,
	.name		= "sa1110",
पूर्ण;

अटल काष्ठा sdram_params *sa1110_find_sdram(स्थिर अक्षर *name)
अणु
	काष्ठा sdram_params *sdram;

	क्रम (sdram = sdram_tbl; sdram < sdram_tbl + ARRAY_SIZE(sdram_tbl);
	     sdram++)
		अगर (म_भेद(name, sdram->name) == 0)
			वापस sdram;

	वापस शून्य;
पूर्ण

अटल अक्षर sdram_name[16];

अटल पूर्णांक __init sa1110_clk_init(व्योम)
अणु
	काष्ठा sdram_params *sdram;
	स्थिर अक्षर *name = sdram_name;

	अगर (!cpu_is_sa1110())
		वापस -ENODEV;

	अगर (!name[0]) अणु
		अगर (machine_is_assabet())
			name = "TC59SM716-CL3";
		अगर (machine_is_pt_प्रणाली3())
			name = "K4S641632D";
		अगर (machine_is_h3100())
			name = "KM416S4030CT";
		अगर (machine_is_jornada720() || machine_is_h3600())
			name = "K4S281632B-1H";
		अगर (machine_is_nanoengine())
			name = "MT48LC8M16A2TG-75";
	पूर्ण

	sdram = sa1110_find_sdram(name);
	अगर (sdram) अणु
		prपूर्णांकk(KERN_DEBUG "SDRAM: tck: %d trcd: %d trp: %d"
			" twr: %d refresh: %d cas_latency: %d\n",
			sdram->tck, sdram->trcd, sdram->trp,
			sdram->twr, sdram->refresh, sdram->cas_latency);

		स_नकल(&sdram_params, sdram, माप(sdram_params));

		वापस cpufreq_रेजिस्टर_driver(&sa1110_driver);
	पूर्ण

	वापस 0;
पूर्ण

module_param_string(sdram, sdram_name, माप(sdram_name), 0);
arch_initcall(sa1110_clk_init);
