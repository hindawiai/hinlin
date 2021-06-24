<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006-2009 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *	Vincent Sanders <vince@simtec.co.uk>
 *
 * S3C2440/S3C2442 CPU Frequency scaling
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

#घोषणा S3C2440_CLKDIVN_PDIVN	     (1<<0)
#घोषणा S3C2440_CLKDIVN_HDIVN_MASK   (3<<1)
#घोषणा S3C2440_CLKDIVN_HDIVN_1      (0<<1)
#घोषणा S3C2440_CLKDIVN_HDIVN_2      (1<<1)
#घोषणा S3C2440_CLKDIVN_HDIVN_4_8    (2<<1)
#घोषणा S3C2440_CLKDIVN_HDIVN_3_6    (3<<1)
#घोषणा S3C2440_CLKDIVN_UCLK         (1<<3)

#घोषणा S3C2440_CAMDIVN_CAMCLK_MASK  (0xf<<0)
#घोषणा S3C2440_CAMDIVN_CAMCLK_SEL   (1<<4)
#घोषणा S3C2440_CAMDIVN_HCLK3_HALF   (1<<8)
#घोषणा S3C2440_CAMDIVN_HCLK4_HALF   (1<<9)
#घोषणा S3C2440_CAMDIVN_DVSEN        (1<<12)

#घोषणा S3C2442_CAMDIVN_CAMCLK_DIV3  (1<<5)

अटल काष्ठा clk *xtal;
अटल काष्ठा clk *fclk;
अटल काष्ठा clk *hclk;
अटल काष्ठा clk *armclk;

/* HDIV: 1, 2, 3, 4, 6, 8 */

अटल अंतरभूत पूर्णांक within_khz(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	दीर्घ dअगरf = a - b;

	वापस (dअगरf >= -1000 && dअगरf <= 1000);
पूर्ण

/**
 * s3c2440_cpufreq_calcभागs - calculate भागider settings
 * @cfg: The cpu frequency settings.
 *
 * Calcualte the भागider values क्रम the given frequency settings
 * specअगरied in @cfg. The values are stored in @cfg क्रम later use
 * by the relevant set routine अगर the request settings can be reached.
 */
अटल पूर्णांक s3c2440_cpufreq_calcभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित पूर्णांक hभाग, pभाग;
	अचिन्हित दीर्घ hclk, fclk, armclk;
	अचिन्हित दीर्घ hclk_max;

	fclk = cfg->freq.fclk;
	armclk = cfg->freq.armclk;
	hclk_max = cfg->max.hclk;

	s3c_freq_dbg("%s: fclk is %lu, armclk %lu, max hclk %lu\n",
		     __func__, fclk, armclk, hclk_max);

	अगर (armclk > fclk) अणु
		pr_warn("%s: armclk > fclk\n", __func__);
		armclk = fclk;
	पूर्ण

	/* अगर we are in DVS, we need HCLK to be <= ARMCLK */
	अगर (armclk < fclk && armclk < hclk_max)
		hclk_max = armclk;

	क्रम (hभाग = 1; hभाग < 9; hभाग++) अणु
		अगर (hभाग == 5 || hभाग == 7)
			hभाग++;

		hclk = (fclk / hभाग);
		अगर (hclk <= hclk_max || within_khz(hclk, hclk_max))
			अवरोध;
	पूर्ण

	s3c_freq_dbg("%s: hclk %lu, div %d\n", __func__, hclk, hभाग);

	अगर (hभाग > 8)
		जाओ invalid;

	pभाग = (hclk > cfg->max.pclk) ? 2 : 1;

	अगर ((hclk / pभाग) > cfg->max.pclk)
		pभाग++;

	s3c_freq_dbg("%s: pdiv %d\n", __func__, pभाग);

	अगर (pभाग > 2)
		जाओ invalid;

	pभाग *= hभाग;

	/* calculate a valid armclk */

	अगर (armclk < hclk)
		armclk = hclk;

	/* अगर we're running armclk lower than fclk, this really means
	 * that the प्रणाली should go पूर्णांकo dvs mode, which means that
	 * armclk is connected to hclk. */
	अगर (armclk < fclk) अणु
		cfg->भागs.dvs = 1;
		armclk = hclk;
	पूर्ण अन्यथा
		cfg->भागs.dvs = 0;

	cfg->freq.armclk = armclk;

	/* store the result, and then वापस */

	cfg->भागs.h_भागisor = hभाग;
	cfg->भागs.p_भागisor = pभाग;

	वापस 0;

 invalid:
	वापस -EINVAL;
पूर्ण

#घोषणा CAMDIVN_HCLK_HALF (S3C2440_CAMDIVN_HCLK3_HALF | \
			   S3C2440_CAMDIVN_HCLK4_HALF)

/**
 * s3c2440_cpufreq_setभागs - set the cpu frequency भागider settings
 * @cfg: The cpu frequency settings.
 *
 * Set the भागisors from the settings in @cfg, which where generated
 * during the calculation phase by s3c2440_cpufreq_calcभागs().
 */
अटल व्योम s3c2440_cpufreq_setभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित दीर्घ clkभाग, camभाग;

	s3c_freq_dbg("%s: divisors: h=%d, p=%d\n", __func__,
		     cfg->भागs.h_भागisor, cfg->भागs.p_भागisor);

	clkभाग = s3c24xx_पढ़ो_clkभागn();
	camभाग = s3c2440_पढ़ो_camभागn();

	clkभाग &= ~(S3C2440_CLKDIVN_HDIVN_MASK | S3C2440_CLKDIVN_PDIVN);
	camभाग &= ~CAMDIVN_HCLK_HALF;

	चयन (cfg->भागs.h_भागisor) अणु
	हाल 1:
		clkभाग |= S3C2440_CLKDIVN_HDIVN_1;
		अवरोध;

	हाल 2:
		clkभाग |= S3C2440_CLKDIVN_HDIVN_2;
		अवरोध;

	हाल 6:
		camभाग |= S3C2440_CAMDIVN_HCLK3_HALF;
	हाल 3:
		clkभाग |= S3C2440_CLKDIVN_HDIVN_3_6;
		अवरोध;

	हाल 8:
		camभाग |= S3C2440_CAMDIVN_HCLK4_HALF;
	हाल 4:
		clkभाग |= S3C2440_CLKDIVN_HDIVN_4_8;
		अवरोध;

	शेष:
		BUG();	/* we करोn't expect to get here. */
	पूर्ण

	अगर (cfg->भागs.p_भागisor != cfg->भागs.h_भागisor)
		clkभाग |= S3C2440_CLKDIVN_PDIVN;

	/* toकरो - set pclk. */

	/* Write the भागisors first with hclk पूर्णांकentionally halved so that
	 * when we ग_लिखो clkभाग we will under-frequency instead of over. We
	 * then make a लघु delay and हटाओ the hclk halving अगर necessary.
	 */

	s3c2440_ग_लिखो_camभागn(camभाग | CAMDIVN_HCLK_HALF);
	s3c24xx_ग_लिखो_clkभागn(clkभाग);

	ndelay(20);
	s3c2440_ग_लिखो_camभागn(camभाग);

	clk_set_parent(armclk, cfg->भागs.dvs ? hclk : fclk);
पूर्ण

अटल पूर्णांक run_freq_क्रम(अचिन्हित दीर्घ max_hclk, अचिन्हित दीर्घ fclk,
			पूर्णांक *भागs,
			काष्ठा cpufreq_frequency_table *table,
			माप_प्रकार table_size)
अणु
	अचिन्हित दीर्घ freq;
	पूर्णांक index = 0;
	पूर्णांक भाग;

	क्रम (भाग = *भागs; भाग > 0; भाग = *भागs++) अणु
		freq = fclk / भाग;

		अगर (freq > max_hclk && भाग != 1)
			जारी;

		freq /= 1000; /* table is in kHz */
		index = s3c_cpufreq_addfreq(table, index, table_size, freq);
		अगर (index < 0)
			अवरोध;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक hclk_भागs[] = अणु 1, 2, 3, 4, 6, 8, -1 पूर्ण;

अटल पूर्णांक s3c2440_cpufreq_calctable(काष्ठा s3c_cpufreq_config *cfg,
				     काष्ठा cpufreq_frequency_table *table,
				     माप_प्रकार table_size)
अणु
	पूर्णांक ret;

	WARN_ON(cfg->info == शून्य);
	WARN_ON(cfg->board == शून्य);

	ret = run_freq_क्रम(cfg->info->max.hclk,
			   cfg->info->max.fclk,
			   hclk_भागs,
			   table, table_size);

	s3c_freq_dbg("%s: returning %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल काष्ठा s3c_cpufreq_info s3c2440_cpufreq_info = अणु
	.max		= अणु
		.fclk	= 400000000,
		.hclk	= 133333333,
		.pclk	=  66666666,
	पूर्ण,

	.lockसमय_m	= 300,
	.lockसमय_u	= 300,
	.lockसमय_bits	= 16,

	.name		= "s3c244x",
	.calc_iotiming	= s3c2410_iotiming_calc,
	.set_iotiming	= s3c2410_iotiming_set,
	.get_iotiming	= s3c2410_iotiming_get,
	.set_fvco	= s3c2410_set_fvco,

	.set_refresh	= s3c2410_cpufreq_setrefresh,
	.set_भागs	= s3c2440_cpufreq_setभागs,
	.calc_भागs	= s3c2440_cpufreq_calcभागs,
	.calc_freqtable	= s3c2440_cpufreq_calctable,

	.debug_io_show  = s3c_cpufreq_debugfs_call(s3c2410_iotiming_debugfs),
पूर्ण;

अटल पूर्णांक s3c2440_cpufreq_add(काष्ठा device *dev,
			       काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	xtal = s3c_cpufreq_clk_get(शून्य, "xtal");
	hclk = s3c_cpufreq_clk_get(शून्य, "hclk");
	fclk = s3c_cpufreq_clk_get(शून्य, "fclk");
	armclk = s3c_cpufreq_clk_get(शून्य, "armclk");

	अगर (IS_ERR(xtal) || IS_ERR(hclk) || IS_ERR(fclk) || IS_ERR(armclk)) अणु
		pr_err("%s: failed to get clocks\n", __func__);
		वापस -ENOENT;
	पूर्ण

	वापस s3c_cpufreq_रेजिस्टर(&s3c2440_cpufreq_info);
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2440_cpufreq_पूर्णांकerface = अणु
	.name		= "s3c2440_cpufreq",
	.subsys		= &s3c2440_subsys,
	.add_dev	= s3c2440_cpufreq_add,
पूर्ण;

अटल पूर्णांक s3c2440_cpufreq_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2440_cpufreq_पूर्णांकerface);
पूर्ण

/* arch_initcall adds the घड़ीs we need, so use subsys_initcall. */
subsys_initcall(s3c2440_cpufreq_init);

अटल काष्ठा subsys_पूर्णांकerface s3c2442_cpufreq_पूर्णांकerface = अणु
	.name		= "s3c2442_cpufreq",
	.subsys		= &s3c2442_subsys,
	.add_dev	= s3c2440_cpufreq_add,
पूर्ण;

अटल पूर्णांक s3c2442_cpufreq_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2442_cpufreq_पूर्णांकerface);
पूर्ण
subsys_initcall(s3c2442_cpufreq_init);
