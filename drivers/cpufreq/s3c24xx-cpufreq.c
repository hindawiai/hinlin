<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX CPU Frequency scaling
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

/* note, cpufreq support deals in kHz, no Hz */
अटल काष्ठा cpufreq_driver s3c24xx_driver;
अटल काष्ठा s3c_cpufreq_config cpu_cur;
अटल काष्ठा s3c_iotimings s3c24xx_iotiming;
अटल काष्ठा cpufreq_frequency_table *pll_reg;
अटल अचिन्हित पूर्णांक last_target = ~0;
अटल अचिन्हित पूर्णांक ftab_size;
अटल काष्ठा cpufreq_frequency_table *ftab;

अटल काष्ठा clk *_clk_mpll;
अटल काष्ठा clk *_clk_xtal;
अटल काष्ठा clk *clk_fclk;
अटल काष्ठा clk *clk_hclk;
अटल काष्ठा clk *clk_pclk;
अटल काष्ठा clk *clk_arm;

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ_DEBUGFS
काष्ठा s3c_cpufreq_config *s3c_cpufreq_अ_लोonfig(व्योम)
अणु
	वापस &cpu_cur;
पूर्ण

काष्ठा s3c_iotimings *s3c_cpufreq_getiotimings(व्योम)
अणु
	वापस &s3c24xx_iotiming;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_S3C24XX_CPUFREQ_DEBUGFS */

अटल व्योम s3c_cpufreq_अ_लोur(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित दीर्घ fclk, pclk, hclk, armclk;

	cfg->freq.fclk = fclk = clk_get_rate(clk_fclk);
	cfg->freq.hclk = hclk = clk_get_rate(clk_hclk);
	cfg->freq.pclk = pclk = clk_get_rate(clk_pclk);
	cfg->freq.armclk = armclk = clk_get_rate(clk_arm);

	cfg->pll.driver_data = s3c24xx_पढ़ो_mpllcon();
	cfg->pll.frequency = fclk;

	cfg->freq.hclk_tns = 1000000000 / (cfg->freq.hclk / 10);

	cfg->भागs.h_भागisor = fclk / hclk;
	cfg->भागs.p_भागisor = fclk / pclk;
पूर्ण

अटल अंतरभूत व्योम s3c_cpufreq_calc(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अचिन्हित दीर्घ pll = cfg->pll.frequency;

	cfg->freq.fclk = pll;
	cfg->freq.hclk = pll / cfg->भागs.h_भागisor;
	cfg->freq.pclk = pll / cfg->भागs.p_भागisor;

	/* convert hclk पूर्णांकo 10ths of nanoseconds क्रम io calcs */
	cfg->freq.hclk_tns = 1000000000 / (cfg->freq.hclk / 10);
पूर्ण

अटल अंतरभूत पूर्णांक बंदr(अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक c)
अणु
	पूर्णांक dअगरf_cur = असल(target - c);
	पूर्णांक dअगरf_new = असल(target - n);

	वापस (dअगरf_new < dअगरf_cur);
पूर्ण

अटल व्योम s3c_cpufreq_show(स्थिर अक्षर *pfx,
				 काष्ठा s3c_cpufreq_config *cfg)
अणु
	s3c_freq_dbg("%s: Fvco=%u, F=%lu, A=%lu, H=%lu (%u), P=%lu (%u)\n",
		     pfx, cfg->pll.frequency, cfg->freq.fclk, cfg->freq.armclk,
		     cfg->freq.hclk, cfg->भागs.h_भागisor,
		     cfg->freq.pclk, cfg->भागs.p_भागisor);
पूर्ण

/* functions to wrapper the driver info calls to करो the cpu specअगरic work */

अटल व्योम s3c_cpufreq_setio(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अगर (cfg->info->set_iotiming)
		(cfg->info->set_iotiming)(cfg, &s3c24xx_iotiming);
पूर्ण

अटल पूर्णांक s3c_cpufreq_calcio(काष्ठा s3c_cpufreq_config *cfg)
अणु
	अगर (cfg->info->calc_iotiming)
		वापस (cfg->info->calc_iotiming)(cfg, &s3c24xx_iotiming);

	वापस 0;
पूर्ण

अटल व्योम s3c_cpufreq_setrefresh(काष्ठा s3c_cpufreq_config *cfg)
अणु
	(cfg->info->set_refresh)(cfg);
पूर्ण

अटल व्योम s3c_cpufreq_setभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	(cfg->info->set_भागs)(cfg);
पूर्ण

अटल पूर्णांक s3c_cpufreq_calcभागs(काष्ठा s3c_cpufreq_config *cfg)
अणु
	वापस (cfg->info->calc_भागs)(cfg);
पूर्ण

अटल व्योम s3c_cpufreq_setfvco(काष्ठा s3c_cpufreq_config *cfg)
अणु
	cfg->mpll = _clk_mpll;
	(cfg->info->set_fvco)(cfg);
पूर्ण

अटल अंतरभूत व्योम s3c_cpufreq_updateclk(काष्ठा clk *clk,
					 अचिन्हित पूर्णांक freq)
अणु
	clk_set_rate(clk, freq);
पूर्ण

अटल पूर्णांक s3c_cpufreq_settarget(काष्ठा cpufreq_policy *policy,
				 अचिन्हित पूर्णांक target_freq,
				 काष्ठा cpufreq_frequency_table *pll)
अणु
	काष्ठा s3c_cpufreq_freqs freqs;
	काष्ठा s3c_cpufreq_config cpu_new;
	अचिन्हित दीर्घ flags;

	cpu_new = cpu_cur;  /* copy new from current */

	s3c_cpufreq_show("cur", &cpu_cur);

	/* TODO - check क्रम DMA currently outstanding */

	cpu_new.pll = pll ? *pll : cpu_cur.pll;

	अगर (pll)
		freqs.pll_changing = 1;

	/* update our frequencies */

	cpu_new.freq.armclk = target_freq;
	cpu_new.freq.fclk = cpu_new.pll.frequency;

	अगर (s3c_cpufreq_calcभागs(&cpu_new) < 0) अणु
		pr_err("no divisors for %d\n", target_freq);
		जाओ err_notpossible;
	पूर्ण

	s3c_freq_dbg("%s: got divs\n", __func__);

	s3c_cpufreq_calc(&cpu_new);

	s3c_freq_dbg("%s: calculated frequencies for new\n", __func__);

	अगर (cpu_new.freq.hclk != cpu_cur.freq.hclk) अणु
		अगर (s3c_cpufreq_calcio(&cpu_new) < 0) अणु
			pr_err("%s: no IO timings\n", __func__);
			जाओ err_notpossible;
		पूर्ण
	पूर्ण

	s3c_cpufreq_show("new", &cpu_new);

	/* setup our cpufreq parameters */

	freqs.old = cpu_cur.freq;
	freqs.new = cpu_new.freq;

	freqs.freqs.old = cpu_cur.freq.armclk / 1000;
	freqs.freqs.new = cpu_new.freq.armclk / 1000;

	/* update f/h/p घड़ी settings beक्रमe we issue the change
	 * notअगरication, so that drivers करो not need to करो anything
	 * special अगर they want to recalculate on CPUFREQ_PRECHANGE. */

	s3c_cpufreq_updateclk(_clk_mpll, cpu_new.pll.frequency);
	s3c_cpufreq_updateclk(clk_fclk, cpu_new.freq.fclk);
	s3c_cpufreq_updateclk(clk_hclk, cpu_new.freq.hclk);
	s3c_cpufreq_updateclk(clk_pclk, cpu_new.freq.pclk);

	/* start the frequency change */
	cpufreq_freq_transition_begin(policy, &freqs.freqs);

	/* If hclk is staying the same, then we करो not need to
	 * re-ग_लिखो the IO or the refresh timings whilst we are changing
	 * speed. */

	local_irq_save(flags);

	/* is our memory घड़ी slowing करोwn? */
	अगर (cpu_new.freq.hclk < cpu_cur.freq.hclk) अणु
		s3c_cpufreq_setrefresh(&cpu_new);
		s3c_cpufreq_setio(&cpu_new);
	पूर्ण

	अगर (cpu_new.freq.fclk == cpu_cur.freq.fclk) अणु
		/* not changing PLL, just set the भागisors */

		s3c_cpufreq_setभागs(&cpu_new);
	पूर्ण अन्यथा अणु
		अगर (cpu_new.freq.fclk < cpu_cur.freq.fclk) अणु
			/* slow the cpu करोwn, then set भागisors */

			s3c_cpufreq_setfvco(&cpu_new);
			s3c_cpufreq_setभागs(&cpu_new);
		पूर्ण अन्यथा अणु
			/* set the भागisors, then speed up */

			s3c_cpufreq_setभागs(&cpu_new);
			s3c_cpufreq_setfvco(&cpu_new);
		पूर्ण
	पूर्ण

	/* did our memory घड़ी speed up */
	अगर (cpu_new.freq.hclk > cpu_cur.freq.hclk) अणु
		s3c_cpufreq_setrefresh(&cpu_new);
		s3c_cpufreq_setio(&cpu_new);
	पूर्ण

	/* update our current settings */
	cpu_cur = cpu_new;

	local_irq_restore(flags);

	/* notअगरy everyone we've करोne this */
	cpufreq_freq_transition_end(policy, &freqs.freqs, 0);

	s3c_freq_dbg("%s: finished\n", __func__);
	वापस 0;

 err_notpossible:
	pr_err("no compatible settings for %d\n", target_freq);
	वापस -EINVAL;
पूर्ण

/* s3c_cpufreq_target
 *
 * called by the cpufreq core to adjust the frequency that the CPU
 * is currently running at.
 */

अटल पूर्णांक s3c_cpufreq_target(काष्ठा cpufreq_policy *policy,
			      अचिन्हित पूर्णांक target_freq,
			      अचिन्हित पूर्णांक relation)
अणु
	काष्ठा cpufreq_frequency_table *pll;
	अचिन्हित पूर्णांक index;

	/* aव्योम repeated calls which cause a needless amout of duplicated
	 * logging output (and CPU समय as the calculation process is
	 * करोne) */
	अगर (target_freq == last_target)
		वापस 0;

	last_target = target_freq;

	s3c_freq_dbg("%s: policy %p, target %u, relation %u\n",
		     __func__, policy, target_freq, relation);

	अगर (ftab) अणु
		index = cpufreq_frequency_table_target(policy, target_freq,
						       relation);

		s3c_freq_dbg("%s: adjust %d to entry %d (%u)\n", __func__,
			     target_freq, index, ftab[index].frequency);
		target_freq = ftab[index].frequency;
	पूर्ण

	target_freq *= 1000;  /* convert target to Hz */

	/* find the settings क्रम our new frequency */

	अगर (!pll_reg || cpu_cur.lock_pll) अणु
		/* either we've not got any PLL values, or we've locked
		 * to the current one. */
		pll = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा cpufreq_policy पंचांगp_policy;

		/* we keep the cpu pll table in Hz, to ensure we get an
		 * accurate value क्रम the PLL output. */

		पंचांगp_policy.min = policy->min * 1000;
		पंचांगp_policy.max = policy->max * 1000;
		पंचांगp_policy.cpu = policy->cpu;
		पंचांगp_policy.freq_table = pll_reg;

		/* cpufreq_frequency_table_target वापसs the index
		 * of the table entry, not the value of
		 * the table entry's index field. */

		index = cpufreq_frequency_table_target(&पंचांगp_policy, target_freq,
						       relation);
		pll = pll_reg + index;

		s3c_freq_dbg("%s: target %u => %u\n",
			     __func__, target_freq, pll->frequency);

		target_freq = pll->frequency;
	पूर्ण

	वापस s3c_cpufreq_settarget(policy, target_freq, pll);
पूर्ण

काष्ठा clk *s3c_cpufreq_clk_get(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;

	clk = clk_get(dev, name);
	अगर (IS_ERR(clk))
		pr_err("failed to get clock '%s'\n", name);

	वापस clk;
पूर्ण

अटल पूर्णांक s3c_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	policy->clk = clk_arm;
	policy->cpuinfo.transition_latency = cpu_cur.info->latency;
	policy->freq_table = ftab;

	वापस 0;
पूर्ण

अटल पूर्णांक __init s3c_cpufreq_initclks(व्योम)
अणु
	_clk_mpll = s3c_cpufreq_clk_get(शून्य, "mpll");
	_clk_xtal = s3c_cpufreq_clk_get(शून्य, "xtal");
	clk_fclk = s3c_cpufreq_clk_get(शून्य, "fclk");
	clk_hclk = s3c_cpufreq_clk_get(शून्य, "hclk");
	clk_pclk = s3c_cpufreq_clk_get(शून्य, "pclk");
	clk_arm = s3c_cpufreq_clk_get(शून्य, "armclk");

	अगर (IS_ERR(clk_fclk) || IS_ERR(clk_hclk) || IS_ERR(clk_pclk) ||
	    IS_ERR(_clk_mpll) || IS_ERR(clk_arm) || IS_ERR(_clk_xtal)) अणु
		pr_err("%s: could not get clock(s)\n", __func__);
		वापस -ENOENT;
	पूर्ण

	pr_info("%s: clocks f=%lu,h=%lu,p=%lu,a=%lu\n",
		__func__,
		clk_get_rate(clk_fclk) / 1000,
		clk_get_rate(clk_hclk) / 1000,
		clk_get_rate(clk_pclk) / 1000,
		clk_get_rate(clk_arm) / 1000);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल काष्ठा cpufreq_frequency_table suspend_pll;
अटल अचिन्हित पूर्णांक suspend_freq;

अटल पूर्णांक s3c_cpufreq_suspend(काष्ठा cpufreq_policy *policy)
अणु
	suspend_pll.frequency = clk_get_rate(_clk_mpll);
	suspend_pll.driver_data = s3c24xx_पढ़ो_mpllcon();
	suspend_freq = clk_get_rate(clk_arm);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_cpufreq_resume(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;

	s3c_freq_dbg("%s: resuming with policy %p\n", __func__, policy);

	last_target = ~0;	/* invalidate last_target setting */

	/* whilst we will be called later on, we try and re-set the
	 * cpu frequencies as soon as possible so that we करो not end
	 * up resuming devices and then immediately having to re-set
	 * a number of settings once these devices have restarted.
	 *
	 * as a note, it is expected devices are not used until they
	 * have been un-suspended and at that समय they should have
	 * used the updated घड़ी settings.
	 */

	ret = s3c_cpufreq_settarget(शून्य, suspend_freq, &suspend_pll);
	अगर (ret) अणु
		pr_err("%s: failed to reset pll/freq\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा s3c_cpufreq_resume शून्य
#घोषणा s3c_cpufreq_suspend शून्य
#पूर्ण_अगर

अटल काष्ठा cpufreq_driver s3c24xx_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.target		= s3c_cpufreq_target,
	.get		= cpufreq_generic_get,
	.init		= s3c_cpufreq_init,
	.suspend	= s3c_cpufreq_suspend,
	.resume		= s3c_cpufreq_resume,
	.name		= "s3c24xx",
पूर्ण;


पूर्णांक s3c_cpufreq_रेजिस्टर(काष्ठा s3c_cpufreq_info *info)
अणु
	अगर (!info || !info->name) अणु
		pr_err("%s: failed to pass valid information\n", __func__);
		वापस -EINVAL;
	पूर्ण

	pr_info("S3C24XX CPU Frequency driver, %s cpu support\n",
		info->name);

	/* check our driver info has valid data */

	BUG_ON(info->set_refresh == शून्य);
	BUG_ON(info->set_भागs == शून्य);
	BUG_ON(info->calc_भागs == शून्य);

	/* info->set_fvco is optional, depending on whether there
	 * is a need to set the घड़ी code. */

	cpu_cur.info = info;

	/* Note, driver रेजिस्टरing should probably update lockसमय */

	वापस 0;
पूर्ण

पूर्णांक __init s3c_cpufreq_setboard(काष्ठा s3c_cpufreq_board *board)
अणु
	काष्ठा s3c_cpufreq_board *ours;

	अगर (!board) अणु
		pr_info("%s: no board data\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Copy the board inक्रमmation so that each board can make this
	 * initdata. */

	ours = kzalloc(माप(*ours), GFP_KERNEL);
	अगर (!ours)
		वापस -ENOMEM;

	*ours = *board;
	cpu_cur.board = ours;

	वापस 0;
पूर्ण

अटल पूर्णांक __init s3c_cpufreq_स्वतः_io(व्योम)
अणु
	पूर्णांक ret;

	अगर (!cpu_cur.info->get_iotiming) अणु
		pr_err("%s: get_iotiming undefined\n", __func__);
		वापस -ENOENT;
	पूर्ण

	pr_info("%s: working out IO settings\n", __func__);

	ret = (cpu_cur.info->get_iotiming)(&cpu_cur, &s3c24xx_iotiming);
	अगर (ret)
		pr_err("%s: failed to get timings\n", __func__);

	वापस ret;
पूर्ण

/* अगर one or is zero, then वापस the other, otherwise वापस the min */
#घोषणा करो_min(_a, _b) ((_a) == 0 ? (_b) : (_b) == 0 ? (_a) : min(_a, _b))

/**
 * s3c_cpufreq_freq_min - find the minimum settings क्रम the given freq.
 * @dst: The destination काष्ठाure
 * @a: One argument.
 * @b: The other argument.
 *
 * Create a minimum of each frequency entry in the 'struct s3c_freq',
 * unless the entry is zero when it is ignored and the non-zero argument
 * used.
 */
अटल व्योम s3c_cpufreq_freq_min(काष्ठा s3c_freq *dst,
				 काष्ठा s3c_freq *a, काष्ठा s3c_freq *b)
अणु
	dst->fclk = करो_min(a->fclk, b->fclk);
	dst->hclk = करो_min(a->hclk, b->hclk);
	dst->pclk = करो_min(a->pclk, b->pclk);
	dst->armclk = करो_min(a->armclk, b->armclk);
पूर्ण

अटल अंतरभूत u32 calc_lockसमय(u32 freq, u32 समय_us)
अणु
	u32 result;

	result = freq * समय_us;
	result = DIV_ROUND_UP(result, 1000 * 1000);

	वापस result;
पूर्ण

अटल व्योम s3c_cpufreq_update_loctkime(व्योम)
अणु
	अचिन्हित पूर्णांक bits = cpu_cur.info->lockसमय_bits;
	u32 rate = (u32)clk_get_rate(_clk_xtal);
	u32 val;

	अगर (bits == 0) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	val = calc_lockसमय(rate, cpu_cur.info->lockसमय_u) << bits;
	val |= calc_lockसमय(rate, cpu_cur.info->lockसमय_m);

	pr_info("%s: new locktime is 0x%08x\n", __func__, val);
	s3c24xx_ग_लिखो_lockसमय(val);
पूर्ण

अटल पूर्णांक s3c_cpufreq_build_freq(व्योम)
अणु
	पूर्णांक size, ret;

	kमुक्त(ftab);

	size = cpu_cur.info->calc_freqtable(&cpu_cur, शून्य, 0);
	size++;

	ftab = kसुस्मृति(size, माप(*ftab), GFP_KERNEL);
	अगर (!ftab)
		वापस -ENOMEM;

	ftab_size = size;

	ret = cpu_cur.info->calc_freqtable(&cpu_cur, ftab, size);
	s3c_cpufreq_addfreq(ftab, ret, size, CPUFREQ_TABLE_END);

	वापस 0;
पूर्ण

अटल पूर्णांक __init s3c_cpufreq_initcall(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_cur.info && cpu_cur.board) अणु
		ret = s3c_cpufreq_initclks();
		अगर (ret)
			जाओ out;

		/* get current settings */
		s3c_cpufreq_अ_लोur(&cpu_cur);
		s3c_cpufreq_show("cur", &cpu_cur);

		अगर (cpu_cur.board->स्वतः_io) अणु
			ret = s3c_cpufreq_स्वतः_io();
			अगर (ret) अणु
				pr_err("%s: failed to get io timing\n",
				       __func__);
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (cpu_cur.board->need_io && !cpu_cur.info->set_iotiming) अणु
			pr_err("%s: no IO support registered\n", __func__);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!cpu_cur.info->need_pll)
			cpu_cur.lock_pll = 1;

		s3c_cpufreq_update_loctkime();

		s3c_cpufreq_freq_min(&cpu_cur.max, &cpu_cur.board->max,
				     &cpu_cur.info->max);

		अगर (cpu_cur.info->calc_freqtable)
			s3c_cpufreq_build_freq();

		ret = cpufreq_रेजिस्टर_driver(&s3c24xx_driver);
	पूर्ण

 out:
	वापस ret;
पूर्ण

late_initcall(s3c_cpufreq_initcall);

/**
 * s3c_plltab_रेजिस्टर - रेजिस्टर CPU PLL table.
 * @plls: The list of PLL entries.
 * @plls_no: The size of the PLL entries @plls.
 *
 * Register the given set of PLLs with the प्रणाली.
 */
पूर्णांक s3c_plltab_रेजिस्टर(काष्ठा cpufreq_frequency_table *plls,
			       अचिन्हित पूर्णांक plls_no)
अणु
	काष्ठा cpufreq_frequency_table *vals;
	अचिन्हित पूर्णांक size;

	size = माप(*vals) * (plls_no + 1);

	vals = kzalloc(size, GFP_KERNEL);
	अगर (vals) अणु
		स_नकल(vals, plls, size);
		pll_reg = vals;

		/* ग_लिखो a terminating entry, we करोn't store it in the
		 * table that is stored in the kernel */
		vals += plls_no;
		vals->frequency = CPUFREQ_TABLE_END;

		pr_info("%d PLL entries\n", plls_no);
	पूर्ण अन्यथा
		pr_err("no memory for PLL tables\n");

	वापस vals ? 0 : -ENOMEM;
पूर्ण
