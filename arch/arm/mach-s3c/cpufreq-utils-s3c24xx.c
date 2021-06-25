<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C24XX CPU Frequency scaling - utils क्रम S3C2410/S3C2440/S3C2442

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>

#समावेश "map.h"
#समावेश "regs-clock.h"

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>

#समावेश "regs-mem-s3c24xx.h"

/**
 * s3c2410_cpufreq_setrefresh - set SDRAM refresh value
 * @cfg: The frequency configuration
 *
 * Set the SDRAM refresh value appropriately क्रम the configured
 * frequency.
 */
व्योम s3c2410_cpufreq_setrefresh(काष्ठा s3c_cpufreq_config *cfg)
अणु
	काष्ठा s3c_cpufreq_board *board = cfg->board;
	अचिन्हित दीर्घ refresh;
	अचिन्हित दीर्घ refval;

	/* Reduce both the refresh समय (in ns) and the frequency (in MHz)
	 * करोwn to ensure that we करो not overflow 32 bit numbers.
	 *
	 * This should work क्रम HCLK up to 133MHz and refresh period up
	 * to 30usec.
	 */

	refresh = (cfg->freq.hclk / 100) * (board->refresh / 10);
	refresh = DIV_ROUND_UP(refresh, (1000 * 1000)); /* apply scale  */
	refresh = (1 << 11) + 1 - refresh;

	s3c_freq_dbg("%s: refresh value %lu\n", __func__, refresh);

	refval = __raw_पढ़ोl(S3C2410_REFRESH);
	refval &= ~((1 << 12) - 1);
	refval |= refresh;
	__raw_ग_लिखोl(refval, S3C2410_REFRESH);
पूर्ण

/**
 * s3c2410_set_fvco - set the PLL value
 * @cfg: The frequency configuration
 */
व्योम s3c2410_set_fvco(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अगर (!IS_ERR(cfg->mpll))
		clk_set_rate(cfg->mpll, cfg->pll.frequency);
पूर्ण

#अगर defined(CONFIG_CPU_S3C2440) || defined(CONFIG_CPU_S3C2442)
u32 s3c2440_पढ़ो_camभागn(व्योम)
अणु
	वापस __raw_पढ़ोl(S3C2440_CAMDIVN);
पूर्ण

व्योम s3c2440_ग_लिखो_camभागn(u32 camभाग)
अणु
	__raw_ग_लिखोl(camभाग, S3C2440_CAMDIVN);
पूर्ण
#पूर्ण_अगर

u32 s3c24xx_पढ़ो_clkभागn(व्योम)
अणु
	वापस __raw_पढ़ोl(S3C2410_CLKDIVN);
पूर्ण

व्योम s3c24xx_ग_लिखो_clkभागn(u32 clkभाग)
अणु
	__raw_ग_लिखोl(clkभाग, S3C2410_CLKDIVN);
पूर्ण

u32 s3c24xx_पढ़ो_mpllcon(व्योम)
अणु
	वापस __raw_पढ़ोl(S3C2410_MPLLCON);
पूर्ण

व्योम s3c24xx_ग_लिखो_lockसमय(u32 lockसमय)
अणु
	वापस __raw_ग_लिखोl(lockसमय, S3C2410_LOCKTIME);
पूर्ण
