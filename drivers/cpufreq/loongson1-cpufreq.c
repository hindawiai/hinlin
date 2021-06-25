<शैली गुरु>
/*
 * CPU Frequency Scaling क्रम Loongson 1 SoC
 *
 * Copyright (C) 2014-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <cpufreq.h>
#समावेश <loongson1.h>

काष्ठा ls1x_cpufreq अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;	/* CPU clk */
	काष्ठा clk *mux_clk;	/* MUX of CPU clk */
	काष्ठा clk *pll_clk;	/* PLL clk */
	काष्ठा clk *osc_clk;	/* OSC clk */
	अचिन्हित पूर्णांक max_freq;
	अचिन्हित पूर्णांक min_freq;
पूर्ण;

अटल काष्ठा ls1x_cpufreq *cpufreq;

अटल पूर्णांक ls1x_cpufreq_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	अगर (val == CPUFREQ_POSTCHANGE)
		current_cpu_data.udelay_val = loops_per_jअगरfy;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block ls1x_cpufreq_notअगरier_block = अणु
	.notअगरier_call = ls1x_cpufreq_notअगरier
पूर्ण;

अटल पूर्णांक ls1x_cpufreq_target(काष्ठा cpufreq_policy *policy,
			       अचिन्हित पूर्णांक index)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(policy->cpu);
	अचिन्हित पूर्णांक old_freq, new_freq;

	old_freq = policy->cur;
	new_freq = policy->freq_table[index].frequency;

	/*
	 * The procedure of reconfiguring CPU clk is as below.
	 *
	 *  - Reparent CPU clk to OSC clk
	 *  - Reset CPU घड़ी (very important)
	 *  - Reconfigure CPU DIV
	 *  - Reparent CPU clk back to CPU DIV clk
	 */

	clk_set_parent(policy->clk, cpufreq->osc_clk);
	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_CLK_PLL_DIV) | RST_CPU_EN | RST_CPU,
		     LS1X_CLK_PLL_DIV);
	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_CLK_PLL_DIV) & ~(RST_CPU_EN | RST_CPU),
		     LS1X_CLK_PLL_DIV);
	clk_set_rate(cpufreq->mux_clk, new_freq * 1000);
	clk_set_parent(policy->clk, cpufreq->mux_clk);
	dev_dbg(cpu_dev, "%u KHz --> %u KHz\n", old_freq, new_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(policy->cpu);
	काष्ठा cpufreq_frequency_table *freq_tbl;
	अचिन्हित पूर्णांक pll_freq, freq;
	पूर्णांक steps, i;

	pll_freq = clk_get_rate(cpufreq->pll_clk) / 1000;

	steps = 1 << DIV_CPU_WIDTH;
	freq_tbl = kसुस्मृति(steps, माप(*freq_tbl), GFP_KERNEL);
	अगर (!freq_tbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < (steps - 1); i++) अणु
		freq = pll_freq / (i + 1);
		अगर ((freq < cpufreq->min_freq) || (freq > cpufreq->max_freq))
			freq_tbl[i].frequency = CPUFREQ_ENTRY_INVALID;
		अन्यथा
			freq_tbl[i].frequency = freq;
		dev_dbg(cpu_dev,
			"cpufreq table: index %d: frequency %d\n", i,
			freq_tbl[i].frequency);
	पूर्ण
	freq_tbl[i].frequency = CPUFREQ_TABLE_END;

	policy->clk = cpufreq->clk;
	cpufreq_generic_init(policy, freq_tbl, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	kमुक्त(policy->freq_table);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver ls1x_cpufreq_driver = अणु
	.name		= "cpufreq-ls1x",
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= ls1x_cpufreq_target,
	.get		= cpufreq_generic_get,
	.init		= ls1x_cpufreq_init,
	.निकास		= ls1x_cpufreq_निकास,
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक ls1x_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&ls1x_cpufreq_notअगरier_block,
				    CPUFREQ_TRANSITION_NOTIFIER);
	cpufreq_unरेजिस्टर_driver(&ls1x_cpufreq_driver);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_ls1x_cpufreq *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (!pdata || !pdata->clk_name || !pdata->osc_clk_name) अणु
		dev_err(&pdev->dev, "platform data missing\n");
		वापस -EINVAL;
	पूर्ण

	cpufreq =
	    devm_kzalloc(&pdev->dev, माप(काष्ठा ls1x_cpufreq), GFP_KERNEL);
	अगर (!cpufreq)
		वापस -ENOMEM;

	cpufreq->dev = &pdev->dev;

	clk = devm_clk_get(&pdev->dev, pdata->clk_name);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get %s clock\n",
			pdata->clk_name);
		वापस PTR_ERR(clk);
	पूर्ण
	cpufreq->clk = clk;

	clk = clk_get_parent(clk);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get parent of %s clock\n",
			__clk_get_name(cpufreq->clk));
		वापस PTR_ERR(clk);
	पूर्ण
	cpufreq->mux_clk = clk;

	clk = clk_get_parent(clk);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get parent of %s clock\n",
			__clk_get_name(cpufreq->mux_clk));
		वापस PTR_ERR(clk);
	पूर्ण
	cpufreq->pll_clk = clk;

	clk = devm_clk_get(&pdev->dev, pdata->osc_clk_name);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get %s clock\n",
			pdata->osc_clk_name);
		वापस PTR_ERR(clk);
	पूर्ण
	cpufreq->osc_clk = clk;

	cpufreq->max_freq = pdata->max_freq;
	cpufreq->min_freq = pdata->min_freq;

	ret = cpufreq_रेजिस्टर_driver(&ls1x_cpufreq_driver);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to register CPUFreq driver: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cpufreq_रेजिस्टर_notअगरier(&ls1x_cpufreq_notअगरier_block,
					CPUFREQ_TRANSITION_NOTIFIER);

	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to register CPUFreq notifier: %d\n",ret);
		cpufreq_unरेजिस्टर_driver(&ls1x_cpufreq_driver);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ls1x_cpufreq_platdrv = अणु
	.probe	= ls1x_cpufreq_probe,
	.हटाओ	= ls1x_cpufreq_हटाओ,
	.driver	= अणु
		.name	= "ls1x-cpufreq",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ls1x_cpufreq_platdrv);

MODULE_ALIAS("platform:ls1x-cpufreq");
MODULE_AUTHOR("Kelvin Cheung <keguang.zhang@gmail.com>");
MODULE_DESCRIPTION("Loongson1 CPUFreq driver");
MODULE_LICENSE("GPL");
