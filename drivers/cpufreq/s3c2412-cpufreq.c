<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2412 CPU Frequency scalling
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#घोषणा S3C2412_CLKDIVN_PDIVN		(1<<2)
#घोषणा S3C2412_CLKDIVN_HDIVN_MASK	(3<<0)
#घोषणा S3C2412_CLKDIVN_ARMDIVN		(1<<3)
#घोषणा S3C2412_CLKDIVN_DVSEN		(1<<4)
#घोषणा S3C2412_CLKDIVN_HALFHCLK	(1<<5)
#घोषणा S3C2412_CLKDIVN_USB48DIV	(1<<6)
#घोषणा S3C2412_CLKDIVN_UARTDIV_MASK	(15<<8)
#घोषणा S3C2412_CLKDIVN_UARTDIV_SHIFT	(8)
#घोषणा S3C2412_CLKDIVN_I2SDIV_MASK	(15<<12)
#घोषणा S3C2412_CLKDIVN_I2SDIV_SHIFT	(12)
#घोषणा S3C2412_CLKDIVN_CAMDIV_MASK	(15<<16)
#घोषणा S3C2412_CLKDIVN_CAMDIV_SHIFT	(16)

/* our घड़ी resources. */
अटल काष्ठा clk *xtal;
अटल काष्ठा clk *fclk;
अटल काष्ठा clk *hclk;
अटल काष्ठा clk *armclk;

/* HDIV: 1, 2, 3, 4, 6, 8 */

अटल पूर्णांक s3c2412_cpufreq_calcभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित पूर्णांक hभाग, pभाग, armभाग, dvs;
	अचिन्हित दीर्घ hclk, fclk, armclk, armभाग_clk;
	अचिन्हित दीर्घ hclk_max;

	fclk = cfg->freq.fclk;
	armclk = cfg->freq.armclk;
	hclk_max = cfg->max.hclk;

	/* We can't run hclk above armclk as at the best we have to
	 * have armclk and hclk in dvs mode. */

	अगर (hclk_max > armclk)
		hclk_max = armclk;

	s3c_freq_dbg("%s: fclk=%lu, armclk=%lu, hclk_max=%lu\n",
		     __func__, fclk, armclk, hclk_max);
	s3c_freq_dbg("%s: want f=%lu, arm=%lu, h=%lu, p=%lu\n",
		     __func__, cfg->freq.fclk, cfg->freq.armclk,
		     cfg->freq.hclk, cfg->freq.pclk);

	armभाग = fclk / armclk;

	अगर (armभाग < 1)
		armभाग = 1;
	अगर (armभाग > 2)
		armभाग = 2;

	cfg->भागs.arm_भागisor = armभाग;
	armभाग_clk = fclk / armभाग;

	hभाग = armभाग_clk / hclk_max;
	अगर (hभाग < 1)
		hभाग = 1;

	cfg->freq.hclk = hclk = armभाग_clk / hभाग;

	/* set dvs depending on whether we reached armclk or not. */
	cfg->भागs.dvs = dvs = armclk < armभाग_clk;

	/* update the actual armclk we achieved. */
	cfg->freq.armclk = dvs ? hclk : armभाग_clk;

	s3c_freq_dbg("%s: armclk %lu, hclk %lu, armdiv %d, hdiv %d, dvs %d\n",
		     __func__, armclk, hclk, armभाग, hभाग, cfg->भागs.dvs);

	अगर (hभाग > 4)
		जाओ invalid;

	pभाग = (hclk > cfg->max.pclk) ? 2 : 1;

	अगर ((hclk / pभाग) > cfg->max.pclk)
		pभाग++;

	cfg->freq.pclk = hclk / pभाग;

	s3c_freq_dbg("%s: pdiv %d\n", __func__, pभाग);

	अगर (pभाग > 2)
		जाओ invalid;

	pभाग *= hभाग;

	/* store the result, and then वापस */

	cfg->भागs.h_भागisor = hभाग * armभाग;
	cfg->भागs.p_भागisor = pभाग * armभाग;

	वापस 0;

invalid:
	वापस -EINVAL;
पूर्ण

अटल व्योम s3c2412_cpufreq_setभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित दीर्घ clkभाग;
	अचिन्हित दीर्घ oldभाग;

	oldभाग = clkभाग = s3c24xx_पढ़ो_clkभागn();

	/* clear off current घड़ी info */

	clkभाग &= ~S3C2412_CLKDIVN_ARMDIVN;
	clkभाग &= ~S3C2412_CLKDIVN_HDIVN_MASK;
	clkभाग &= ~S3C2412_CLKDIVN_PDIVN;

	अगर (cfg->भागs.arm_भागisor == 2)
		clkभाग |= S3C2412_CLKDIVN_ARMDIVN;

	clkभाग |= ((cfg->भागs.h_भागisor / cfg->भागs.arm_भागisor) - 1);

	अगर (cfg->भागs.p_भागisor != cfg->भागs.h_भागisor)
		clkभाग |= S3C2412_CLKDIVN_PDIVN;

	s3c_freq_dbg("%s: div %08lx => %08lx\n", __func__, oldभाग, clkभाग);
	s3c24xx_ग_लिखो_clkभागn(clkभाग);

	clk_set_parent(armclk, cfg->भागs.dvs ? hclk : fclk);
पूर्ण

/* set the शेष cpu frequency inक्रमmation, based on an 200MHz part
 * as we have no other way of detecting the speed rating in software.
 */

अटल काष्ठा s3c_cpufreq_info s3c2412_cpufreq_info = अणु
	.max		= अणु
		.fclk	= 200000000,
		.hclk	= 100000000,
		.pclk	=  50000000,
	पूर्ण,

	.latency	= 5000000, /* 5ms */

	.lockसमय_m	= 150,
	.lockसमय_u	= 150,
	.lockसमय_bits	= 16,

	.name		= "s3c2412",
	.set_refresh	= s3c2412_cpufreq_setrefresh,
	.set_भागs	= s3c2412_cpufreq_setभागs,
	.calc_भागs	= s3c2412_cpufreq_calcभागs,

	.calc_iotiming	= s3c2412_iotiming_calc,
	.set_iotiming	= s3c2412_iotiming_set,
	.get_iotiming	= s3c2412_iotiming_get,

	.debug_io_show  = s3c_cpufreq_debugfs_call(s3c2412_iotiming_debugfs),
पूर्ण;

अटल पूर्णांक s3c2412_cpufreq_add(काष्ठा device *dev,
			       काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	अचिन्हित दीर्घ fclk_rate;

	hclk = clk_get(शून्य, "hclk");
	अगर (IS_ERR(hclk)) अणु
		pr_err("cannot find hclk clock\n");
		वापस -ENOENT;
	पूर्ण

	fclk = clk_get(शून्य, "fclk");
	अगर (IS_ERR(fclk)) अणु
		pr_err("cannot find fclk clock\n");
		जाओ err_fclk;
	पूर्ण

	fclk_rate = clk_get_rate(fclk);
	अगर (fclk_rate > 200000000) अणु
		pr_info("fclk %ld MHz, assuming 266MHz capable part\n",
			fclk_rate / 1000000);
		s3c2412_cpufreq_info.max.fclk = 266000000;
		s3c2412_cpufreq_info.max.hclk = 133000000;
		s3c2412_cpufreq_info.max.pclk =  66000000;
	पूर्ण

	armclk = clk_get(शून्य, "armclk");
	अगर (IS_ERR(armclk)) अणु
		pr_err("cannot find arm clock\n");
		जाओ err_armclk;
	पूर्ण

	xtal = clk_get(शून्य, "xtal");
	अगर (IS_ERR(xtal)) अणु
		pr_err("cannot find xtal clock\n");
		जाओ err_xtal;
	पूर्ण

	वापस s3c_cpufreq_रेजिस्टर(&s3c2412_cpufreq_info);

err_xtal:
	clk_put(armclk);
err_armclk:
	clk_put(fclk);
err_fclk:
	clk_put(hclk);

	वापस -ENOENT;
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2412_cpufreq_पूर्णांकerface = अणु
	.name		= "s3c2412_cpufreq",
	.subsys		= &s3c2412_subsys,
	.add_dev	= s3c2412_cpufreq_add,
पूर्ण;

अटल पूर्णांक s3c2412_cpufreq_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2412_cpufreq_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2412_cpufreq_init);
