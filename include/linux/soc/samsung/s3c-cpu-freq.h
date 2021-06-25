<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2006-2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C CPU frequency scaling support - driver and board
 */
#अगर_अघोषित __LINUX_SOC_SAMSUNG_S3C_CPU_FREQ_H
#घोषणा __LINUX_SOC_SAMSUNG_S3C_CPU_FREQ_H

#समावेश <linux/cpufreq.h>

काष्ठा s3c_cpufreq_info;
काष्ठा s3c_cpufreq_board;
काष्ठा s3c_iotimings;

/**
 * काष्ठा s3c_freq - frequency inक्रमmation (मुख्यly क्रम core drivers)
 * @fclk: The FCLK frequency in Hz.
 * @armclk: The ARMCLK frequency in Hz.
 * @hclk_tns: HCLK cycle समय in 10ths of nano-seconds.
 * @hclk: The HCLK frequency in Hz.
 * @pclk: The PCLK frequency in Hz.
 *
 * This contains the frequency inक्रमmation about the current configuration
 * मुख्यly क्रम the core drivers to ensure we करो not end up passing about
 * a large number of parameters.
 *
 * The @hclk_tns field is a useful cache क्रम the parts of the drivers that
 * need to calculate IO timings and suchlike.
 */
काष्ठा s3c_freq अणु
	अचिन्हित दीर्घ	fclk;
	अचिन्हित दीर्घ	armclk;
	अचिन्हित दीर्घ	hclk_tns;	/* in 10ths of ns */
	अचिन्हित दीर्घ	hclk;
	अचिन्हित दीर्घ	pclk;
पूर्ण;

/**
 * काष्ठा s3c_cpufreq_freqs - s3c cpufreq notअगरication inक्रमmation.
 * @freqs: The cpufreq setting inक्रमmation.
 * @old: The old घड़ी settings.
 * @new: The new घड़ी settings.
 * @pll_changing: Set अगर the PLL is changing.
 *
 * Wrapper 'struct cpufreq_freqs' so that any drivers receiving the
 * notअगरication can use this inक्रमmation that is not provided by just
 * having the core frequency alone.
 *
 * The pll_changing flag is used to indicate अगर the PLL itself is
 * being set during this change. This is important as the घड़ीs
 * will temporarily be set to the XTAL घड़ी during this समय, so
 * drivers may want to बंद करोwn their output during this समय.
 *
 * Note, this is not being used by any current drivers and thereक्रमe
 * may be हटाओd in the future.
 */
काष्ठा s3c_cpufreq_freqs अणु
	काष्ठा cpufreq_freqs	freqs;
	काष्ठा s3c_freq		old;
	काष्ठा s3c_freq		new;

	अचिन्हित पूर्णांक		pll_changing:1;
पूर्ण;

#घोषणा to_s3c_cpufreq(_cf) container_of(_cf, काष्ठा s3c_cpufreq_freqs, freqs)

/**
 * काष्ठा s3c_clkभागs - घड़ी भागisor inक्रमmation
 * @p_भागisor: Divisor from FCLK to PCLK.
 * @h_भागisor: Divisor from FCLK to HCLK.
 * @arm_भागisor: Divisor from FCLK to ARMCLK (not all CPUs).
 * @dvs: Non-zero अगर using DVS mode क्रम ARMCLK.
 *
 * Divisor settings क्रम the core घड़ीs.
 */
काष्ठा s3c_clkभागs अणु
	पूर्णांक		p_भागisor;
	पूर्णांक		h_भागisor;
	पूर्णांक		arm_भागisor;
	अचिन्हित अक्षर	dvs;
पूर्ण;

#घोषणा PLLVAL(_m, _p, _s) (((_m) << 12) | ((_p) << 4) | (_s))

/**
 * काष्ठा s3c_pllval - PLL value entry.
 * @freq: The frequency क्रम this entry in Hz.
 * @pll_reg: The PLL रेजिस्टर setting क्रम this PLL value.
 */
काष्ठा s3c_pllval अणु
	अचिन्हित दीर्घ		freq;
	अचिन्हित दीर्घ		pll_reg;
पूर्ण;

/**
 * काष्ठा s3c_cpufreq_board - per-board cpu frequency inक्रमmatin
 * @refresh: The SDRAM refresh period in nanoseconds.
 * @स्वतः_io: Set अगर the IO timing settings should be generated from the
 *	initialisation समय hardware रेजिस्टरs.
 * @need_io: Set अगर the board has बाह्यal IO on any of the chipselect
 *	lines that will require the hardware timing रेजिस्टरs to be
 *	updated on a घड़ी change.
 * @max: The maxium frequency limits क्रम the प्रणाली. Any field that
 *	is left at zero will use the CPU's settings.
 *
 * This contains the board specअगरic settings that affect how the CPU
 * drivers chose settings. These include the memory refresh and IO
 * timing inक्रमmation.
 *
 * Registration depends on the driver being used, the ARMCLK only
 * implementation करोes not currently need this but the older style
 * driver requires this to be available.
 */
काष्ठा s3c_cpufreq_board अणु
	अचिन्हित पूर्णांक	refresh;
	अचिन्हित पूर्णांक	स्वतः_io:1;	/* स्वतःmatically init io timings. */
	अचिन्हित पूर्णांक	need_io:1;	/* set अगर needs io timing support. */

	/* any non-zero field in here is taken as an upper limit. */
	काष्ठा s3c_freq	max;	/* frequency limits */
पूर्ण;

/* Things depending on frequency scaling. */
#अगर_घोषित CONFIG_ARM_S3C_CPUFREQ
#घोषणा __init_or_cpufreq
#अन्यथा
#घोषणा __init_or_cpufreq __init
#पूर्ण_अगर

/* Board functions */

#अगर_घोषित CONFIG_ARM_S3C_CPUFREQ
बाह्य पूर्णांक s3c_cpufreq_setboard(काष्ठा s3c_cpufreq_board *board);
#अन्यथा

अटल अंतरभूत पूर्णांक s3c_cpufreq_setboard(काष्ठा s3c_cpufreq_board *board)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर  /* CONFIG_ARM_S3C_CPUFREQ */

#पूर्ण_अगर
