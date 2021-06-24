<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2006-2009 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C CPU frequency scaling support - core support
 */
#अगर_अघोषित __LINUX_SOC_SAMSUNG_S3C_CPUFREQ_CORE_H
#घोषणा __LINUX_SOC_SAMSUNG_S3C_CPUFREQ_CORE_H

#समावेश <linux/soc/samsung/s3c-cpu-freq.h>

काष्ठा seq_file;

#घोषणा MAX_BANKS (8)
#घोषणा S3C2412_MAX_IO	(8)

/**
 * काष्ठा s3c2410_iobank_timing - IO bank timings क्रम S3C2410 style timings
 * @bankcon: The cached version of settings in this काष्ठाure.
 * @tacp:
 * @tacs: Time from address valid to nCS निश्चितed.
 * @tcos: Time from nCS निश्चितed to nOE or nWE निश्चितed.
 * @tacc: Time that nOE or nWE is निश्चितed.
 * @tcoh: Time nCS is held after nOE or nWE are released.
 * @tcah: Time address is held क्रम after
 * @nरुको_en: Whether nWAIT is enabled क्रम this bank.
 *
 * This काष्ठाure represents the IO timings क्रम a S3C2410 style IO bank
 * used by the CPU frequency support अगर it needs to change the settings
 * of the IO.
 */
काष्ठा s3c2410_iobank_timing अणु
	अचिन्हित दीर्घ	bankcon;
	अचिन्हित पूर्णांक	tacp;
	अचिन्हित पूर्णांक	tacs;
	अचिन्हित पूर्णांक	tcos;
	अचिन्हित पूर्णांक	tacc;
	अचिन्हित पूर्णांक	tcoh;		/* nCS hold after nOE/nWE */
	अचिन्हित पूर्णांक	tcah;		/* Address hold after nCS */
	अचिन्हित अक्षर	nरुको_en;	/* nWait enabled क्रम bank. */
पूर्ण;

/**
 * काष्ठा s3c2412_iobank_timing - io timings क्रम PL092 (S3C2412) style IO
 * @idcy: The idle cycle समय between transactions.
 * @wstrd: nCS release to end of पढ़ो cycle.
 * @wstwr: nCS release to end of ग_लिखो cycle.
 * @wstoen: nCS निश्चितion to nOE निश्चितion समय.
 * @wstwen: nCS निश्चितion to nWE निश्चितion समय.
 * @wstbrd: Burst पढ़ोy delay.
 * @smbidcyr: Register cache क्रम smbidcyr value.
 * @smbwstrd: Register cache क्रम smbwstrd value.
 * @smbwstwr: Register cache क्रम smbwstwr value.
 * @smbwstoen: Register cache क्रम smbwstoen value.
 * @smbwstwen: Register cache क्रम smbwstwen value.
 * @smbwstbrd: Register cache क्रम smbwstbrd value.
 *
 * Timing inक्रमmation क्रम a IO bank on an S3C2412 or similar प्रणाली which
 * uses a PL093 block.
 */
काष्ठा s3c2412_iobank_timing अणु
	अचिन्हित पूर्णांक	idcy;
	अचिन्हित पूर्णांक	wstrd;
	अचिन्हित पूर्णांक	wstwr;
	अचिन्हित पूर्णांक	wstoen;
	अचिन्हित पूर्णांक	wstwen;
	अचिन्हित पूर्णांक	wstbrd;

	/* रेजिस्टर cache */
	अचिन्हित अक्षर	smbidcyr;
	अचिन्हित अक्षर	smbwstrd;
	अचिन्हित अक्षर	smbwstwr;
	अचिन्हित अक्षर	smbwstoen;
	अचिन्हित अक्षर	smbwstwen;
	अचिन्हित अक्षर	smbwstbrd;
पूर्ण;

जोड़ s3c_iobank अणु
	काष्ठा s3c2410_iobank_timing	*io_2410;
	काष्ठा s3c2412_iobank_timing	*io_2412;
पूर्ण;

/**
 * काष्ठा s3c_iotimings - Chip IO timings holder
 * @bank: The timings क्रम each IO bank.
 */
काष्ठा s3c_iotimings अणु
	जोड़ s3c_iobank	bank[MAX_BANKS];
पूर्ण;

/**
 * काष्ठा s3c_plltab - PLL table inक्रमmation.
 * @vals: List of PLL values.
 * @size: Size of the PLL table @vals.
 */
काष्ठा s3c_plltab अणु
	काष्ठा s3c_pllval	*vals;
	पूर्णांक			 size;
पूर्ण;

/**
 * काष्ठा s3c_cpufreq_config - current cpu frequency configuration
 * @freq: The current settings क्रम the core घड़ीs.
 * @max: Maxium settings, derived from core, board and user settings.
 * @pll: The PLL table entry क्रम the current PLL settings.
 * @भागs: The भागisor settings क्रम the core घड़ीs.
 * @info: The current core driver inक्रमmation.
 * @board: The inक्रमmation क्रम the board we are running on.
 * @lock_pll: Set अगर the PLL settings cannot be changed.
 *
 * This is क्रम the core drivers that need to know inक्रमmation about
 * the current settings and values. It should not be needed by any
 * device drivers.
*/
काष्ठा s3c_cpufreq_config अणु
	काष्ठा s3c_freq		freq;
	काष्ठा s3c_freq		max;
	काष्ठा clk		*mpll;
	काष्ठा cpufreq_frequency_table pll;
	काष्ठा s3c_clkभागs	भागs;
	काष्ठा s3c_cpufreq_info *info;	/* क्रम core, not drivers */
	काष्ठा s3c_cpufreq_board *board;

	अचिन्हित पूर्णांक	lock_pll:1;
पूर्ण;

/**
 * काष्ठा s3c_cpufreq_info - Inक्रमmation क्रम the CPU frequency driver.
 * @name: The name of this implementation.
 * @max: The maximum frequencies क्रम the प्रणाली.
 * @latency: Transition latency to give to cpufreq.
 * @lockसमय_m: The lock-समय in uS क्रम the MPLL.
 * @lockसमय_u: The lock-समय in uS क्रम the UPLL.
 * @loctसमय_bits: The number of bits each LOCKTIME field.
 * @need_pll: Set अगर this driver needs to change the PLL values to achieve
 *	any frequency changes. This is really only need by devices like the
 *	S3C2410 where there is no or limited भागider between the PLL and the
 *	ARMCLK.
 * @get_iotiming: Get the current IO timing data, मुख्यly क्रम use at start.
 * @set_iotiming: Update the IO timings from the cached copies calculated
 *	from the @calc_iotiming entry when changing the frequency.
 * @calc_iotiming: Calculate and update the cached copies of the IO timings
 *	from the newly calculated frequencies.
 * @calc_freqtable: Calculate (fill in) the given frequency table from the
 *	current frequency configuration. If the table passed in is शून्य,
 *	then the वापस is the number of elements to be filled क्रम allocation
 *	of the table.
 * @set_refresh: Set the memory refresh configuration.
 * @set_fvco: Set the PLL frequencies.
 * @set_भागs: Update the घड़ी भागisors.
 * @calc_भागs: Calculate the घड़ी भागisors.
 */
काष्ठा s3c_cpufreq_info अणु
	स्थिर अक्षर		*name;
	काष्ठा s3c_freq		max;

	अचिन्हित पूर्णांक		latency;

	अचिन्हित पूर्णांक		lockसमय_m;
	अचिन्हित पूर्णांक		lockसमय_u;
	अचिन्हित अक्षर		lockसमय_bits;

	अचिन्हित पूर्णांक		need_pll:1;

	/* driver routines */

	पूर्णांक		(*get_iotiming)(काष्ठा s3c_cpufreq_config *cfg,
					काष्ठा s3c_iotimings *timings);

	व्योम		(*set_iotiming)(काष्ठा s3c_cpufreq_config *cfg,
					काष्ठा s3c_iotimings *timings);

	पूर्णांक		(*calc_iotiming)(काष्ठा s3c_cpufreq_config *cfg,
					 काष्ठा s3c_iotimings *timings);

	पूर्णांक		(*calc_freqtable)(काष्ठा s3c_cpufreq_config *cfg,
					  काष्ठा cpufreq_frequency_table *t,
					  माप_प्रकार table_size);

	व्योम		(*debug_io_show)(काष्ठा seq_file *seq,
					 काष्ठा s3c_cpufreq_config *cfg,
					 जोड़ s3c_iobank *iob);

	व्योम		(*set_refresh)(काष्ठा s3c_cpufreq_config *cfg);
	व्योम		(*set_fvco)(काष्ठा s3c_cpufreq_config *cfg);
	व्योम		(*set_भागs)(काष्ठा s3c_cpufreq_config *cfg);
	पूर्णांक		(*calc_भागs)(काष्ठा s3c_cpufreq_config *cfg);
पूर्ण;

बाह्य पूर्णांक s3c_cpufreq_रेजिस्टर(काष्ठा s3c_cpufreq_info *info);

बाह्य पूर्णांक s3c_plltab_रेजिस्टर(काष्ठा cpufreq_frequency_table *plls,
			       अचिन्हित पूर्णांक plls_no);

/* exports and utilities क्रम debugfs */
बाह्य काष्ठा s3c_cpufreq_config *s3c_cpufreq_अ_लोonfig(व्योम);
बाह्य काष्ठा s3c_iotimings *s3c_cpufreq_getiotimings(व्योम);

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ_DEBUGFS
#घोषणा s3c_cpufreq_debugfs_call(x) x
#अन्यथा
#घोषणा s3c_cpufreq_debugfs_call(x) शून्य
#पूर्ण_अगर

/* Useful utility functions. */

बाह्य काष्ठा clk *s3c_cpufreq_clk_get(काष्ठा device *, स्थिर अक्षर *);

/* S3C2410 and compatible exported functions */

बाह्य व्योम s3c2410_cpufreq_setrefresh(काष्ठा s3c_cpufreq_config *cfg);
बाह्य व्योम s3c2410_set_fvco(काष्ठा s3c_cpufreq_config *cfg);

#अगर_घोषित CONFIG_S3C2410_IOTIMING
बाह्य व्योम s3c2410_iotiming_debugfs(काष्ठा seq_file *seq,
				     काष्ठा s3c_cpufreq_config *cfg,
				     जोड़ s3c_iobank *iob);

बाह्य पूर्णांक s3c2410_iotiming_calc(काष्ठा s3c_cpufreq_config *cfg,
				 काष्ठा s3c_iotimings *iot);

बाह्य पूर्णांक s3c2410_iotiming_get(काष्ठा s3c_cpufreq_config *cfg,
				काष्ठा s3c_iotimings *timings);

बाह्य व्योम s3c2410_iotiming_set(काष्ठा s3c_cpufreq_config *cfg,
				 काष्ठा s3c_iotimings *iot);
#अन्यथा
#घोषणा s3c2410_iotiming_debugfs शून्य
#घोषणा s3c2410_iotiming_calc शून्य
#घोषणा s3c2410_iotiming_get शून्य
#घोषणा s3c2410_iotiming_set शून्य
#पूर्ण_अगर /* CONFIG_S3C2410_IOTIMING */

/* S3C2412 compatible routines */

#अगर_घोषित CONFIG_S3C2412_IOTIMING
बाह्य व्योम s3c2412_iotiming_debugfs(काष्ठा seq_file *seq,
				     काष्ठा s3c_cpufreq_config *cfg,
				     जोड़ s3c_iobank *iob);

बाह्य पूर्णांक s3c2412_iotiming_get(काष्ठा s3c_cpufreq_config *cfg,
				काष्ठा s3c_iotimings *timings);

बाह्य पूर्णांक s3c2412_iotiming_calc(काष्ठा s3c_cpufreq_config *cfg,
				 काष्ठा s3c_iotimings *iot);

बाह्य व्योम s3c2412_iotiming_set(काष्ठा s3c_cpufreq_config *cfg,
				 काष्ठा s3c_iotimings *iot);
बाह्य व्योम s3c2412_cpufreq_setrefresh(काष्ठा s3c_cpufreq_config *cfg);
#अन्यथा
#घोषणा s3c2412_iotiming_debugfs शून्य
#घोषणा s3c2412_iotiming_calc शून्य
#घोषणा s3c2412_iotiming_get शून्य
#घोषणा s3c2412_iotiming_set शून्य
#पूर्ण_अगर /* CONFIG_S3C2412_IOTIMING */

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ_DEBUG
#घोषणा s3c_freq_dbg(x...) prपूर्णांकk(KERN_INFO x)
#अन्यथा
#घोषणा s3c_freq_dbg(x...) करो अणु अगर (0) prपूर्णांकk(x); पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_ARM_S3C24XX_CPUFREQ_DEBUG */

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ_IODEBUG
#घोषणा s3c_freq_iodbg(x...) prपूर्णांकk(KERN_INFO x)
#अन्यथा
#घोषणा s3c_freq_iodbg(x...) करो अणु अगर (0) prपूर्णांकk(x); पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_ARM_S3C24XX_CPUFREQ_IODEBUG */

अटल अंतरभूत पूर्णांक s3c_cpufreq_addfreq(काष्ठा cpufreq_frequency_table *table,
				      पूर्णांक index, माप_प्रकार table_size,
				      अचिन्हित पूर्णांक freq)
अणु
	अगर (index < 0)
		वापस index;

	अगर (table) अणु
		अगर (index >= table_size)
			वापस -ENOMEM;

		s3c_freq_dbg("%s: { %d = %u kHz }\n",
			     __func__, index, freq);

		table[index].driver_data = index;
		table[index].frequency = freq;
	पूर्ण

	वापस index + 1;
पूर्ण

u32 s3c2440_पढ़ो_camभागn(व्योम);
व्योम s3c2440_ग_लिखो_camभागn(u32 camभाग);
u32 s3c24xx_पढ़ो_clkभागn(व्योम);
व्योम s3c24xx_ग_लिखो_clkभागn(u32 clkभाग);
u32 s3c24xx_पढ़ो_mpllcon(व्योम);
व्योम s3c24xx_ग_लिखो_lockसमय(u32 lockसमय);

#पूर्ण_अगर
