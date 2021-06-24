<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 CPU Frequency scaling
*/

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#घोषणा S3C2410_CLKDIVN_PDIVN	     (1<<0)
#घोषणा S3C2410_CLKDIVN_HDIVN	     (1<<1)

/* Note, 2410A has an extra mode क्रम 1:4:4 ratio, bit 2 of CLKDIV */

अटल व्योम s3c2410_cpufreq_setभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	u32 clkभाग = 0;

	अगर (cfg->भागs.h_भागisor == 2)
		clkभाग |= S3C2410_CLKDIVN_HDIVN;

	अगर (cfg->भागs.p_भागisor != cfg->भागs.h_भागisor)
		clkभाग |= S3C2410_CLKDIVN_PDIVN;

	s3c24xx_ग_लिखो_clkभागn(clkभाग);
पूर्ण

अटल पूर्णांक s3c2410_cpufreq_calcभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित दीर्घ hclk, fclk, pclk;
	अचिन्हित पूर्णांक hभाग, pभाग;
	अचिन्हित दीर्घ hclk_max;

	fclk = cfg->freq.fclk;
	hclk_max = cfg->max.hclk;

	cfg->freq.armclk = fclk;

	s3c_freq_dbg("%s: fclk is %lu, max hclk %lu\n",
		      __func__, fclk, hclk_max);

	hभाग = (fclk > cfg->max.hclk) ? 2 : 1;
	hclk = fclk / hभाग;

	अगर (hclk > cfg->max.hclk) अणु
		s3c_freq_dbg("%s: hclk too big\n", __func__);
		वापस -EINVAL;
	पूर्ण

	pभाग = (hclk > cfg->max.pclk) ? 2 : 1;
	pclk = hclk / pभाग;

	अगर (pclk > cfg->max.pclk) अणु
		s3c_freq_dbg("%s: pclk too big\n", __func__);
		वापस -EINVAL;
	पूर्ण

	pभाग *= hभाग;

	/* record the result */
	cfg->भागs.p_भागisor = pभाग;
	cfg->भागs.h_भागisor = hभाग;

	वापस 0;
पूर्ण

अटल काष्ठा s3c_cpufreq_info s3c2410_cpufreq_info = अणु
	.max		= अणु
		.fclk	= 200000000,
		.hclk	= 100000000,
		.pclk	=  50000000,
	पूर्ण,

	/* transition latency is about 5ms worst-हाल, so
	 * set 10ms to be sure */
	.latency	= 10000000,

	.lockसमय_m	= 150,
	.lockसमय_u	= 150,
	.lockसमय_bits	= 12,

	.need_pll	= 1,

	.name		= "s3c2410",
	.calc_iotiming	= s3c2410_iotiming_calc,
	.set_iotiming	= s3c2410_iotiming_set,
	.get_iotiming	= s3c2410_iotiming_get,

	.set_fvco	= s3c2410_set_fvco,
	.set_refresh	= s3c2410_cpufreq_setrefresh,
	.set_भागs	= s3c2410_cpufreq_setभागs,
	.calc_भागs	= s3c2410_cpufreq_calcभागs,

	.debug_io_show	= s3c_cpufreq_debugfs_call(s3c2410_iotiming_debugfs),
पूर्ण;

अटल पूर्णांक s3c2410_cpufreq_add(काष्ठा device *dev,
			       काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	वापस s3c_cpufreq_रेजिस्टर(&s3c2410_cpufreq_info);
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2410_cpufreq_पूर्णांकerface = अणु
	.name		= "s3c2410_cpufreq",
	.subsys		= &s3c2410_subsys,
	.add_dev	= s3c2410_cpufreq_add,
पूर्ण;

अटल पूर्णांक __init s3c2410_cpufreq_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2410_cpufreq_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2410_cpufreq_init);

अटल पूर्णांक s3c2410a_cpufreq_add(काष्ठा device *dev,
				काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	/* alter the maximum freq settings क्रम S3C2410A. If a board knows
	 * it only has a maximum of 200, then it should रेजिस्टर its own
	 * limits. */

	s3c2410_cpufreq_info.max.fclk = 266000000;
	s3c2410_cpufreq_info.max.hclk = 133000000;
	s3c2410_cpufreq_info.max.pclk =  66500000;
	s3c2410_cpufreq_info.name = "s3c2410a";

	वापस s3c2410_cpufreq_add(dev, sअगर);
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2410a_cpufreq_पूर्णांकerface = अणु
	.name		= "s3c2410a_cpufreq",
	.subsys		= &s3c2410a_subsys,
	.add_dev	= s3c2410a_cpufreq_add,
पूर्ण;

अटल पूर्णांक __init s3c2410a_cpufreq_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2410a_cpufreq_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2410a_cpufreq_init);
