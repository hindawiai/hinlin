<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * CPU Frequency Scaling driver क्रम Freescale QorIQ SoCs.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/platक्रमm_device.h>

/**
 * काष्ठा cpu_data
 * @pclk: the parent घड़ी of cpu
 * @table: frequency table
 */
काष्ठा cpu_data अणु
	काष्ठा clk **pclk;
	काष्ठा cpufreq_frequency_table *table;
पूर्ण;

/**
 * काष्ठा soc_data - SoC specअगरic data
 * @flags: SOC_xxx
 */
काष्ठा soc_data अणु
	u32 flags;
पूर्ण;

अटल u32 get_bus_freq(व्योम)
अणु
	काष्ठा device_node *soc;
	u32 sysfreq;
	काष्ठा clk *pltclk;
	पूर्णांक ret;

	/* get platक्रमm freq by searching bus-frequency property */
	soc = of_find_node_by_type(शून्य, "soc");
	अगर (soc) अणु
		ret = of_property_पढ़ो_u32(soc, "bus-frequency", &sysfreq);
		of_node_put(soc);
		अगर (!ret)
			वापस sysfreq;
	पूर्ण

	/* get platक्रमm freq by its घड़ी name */
	pltclk = clk_get(शून्य, "cg-pll0-div1");
	अगर (IS_ERR(pltclk)) अणु
		pr_err("%s: can't get bus frequency %ld\n",
		       __func__, PTR_ERR(pltclk));
		वापस PTR_ERR(pltclk);
	पूर्ण

	वापस clk_get_rate(pltclk);
पूर्ण

अटल काष्ठा clk *cpu_to_clk(पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *clk;

	अगर (!cpu_present(cpu))
		वापस शून्य;

	np = of_get_cpu_node(cpu, शून्य);
	अगर (!np)
		वापस शून्य;

	clk = of_clk_get(np, 0);
	of_node_put(np);
	वापस clk;
पूर्ण

/* traverse cpu nodes to get cpu mask of sharing घड़ी wire */
अटल व्योम set_affected_cpus(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpumask *dstp = policy->cpus;
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम_each_present_cpu(i) अणु
		clk = cpu_to_clk(i);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: no clock for cpu %d\n", __func__, i);
			जारी;
		पूर्ण

		अगर (clk_is_match(policy->clk, clk))
			cpumask_set_cpu(i, dstp);
	पूर्ण
पूर्ण

/* reduce the duplicated frequencies in frequency table */
अटल व्योम freq_table_redup(काष्ठा cpufreq_frequency_table *freq_table,
		पूर्णांक count)
अणु
	पूर्णांक i, j;

	क्रम (i = 1; i < count; i++) अणु
		क्रम (j = 0; j < i; j++) अणु
			अगर (freq_table[j].frequency == CPUFREQ_ENTRY_INVALID ||
					freq_table[j].frequency !=
					freq_table[i].frequency)
				जारी;

			freq_table[i].frequency = CPUFREQ_ENTRY_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* sort the frequencies in frequency table in descenting order */
अटल व्योम freq_table_sort(काष्ठा cpufreq_frequency_table *freq_table,
		पूर्णांक count)
अणु
	पूर्णांक i, j, ind;
	अचिन्हित पूर्णांक freq, max_freq;
	काष्ठा cpufreq_frequency_table table;

	क्रम (i = 0; i < count - 1; i++) अणु
		max_freq = freq_table[i].frequency;
		ind = i;
		क्रम (j = i + 1; j < count; j++) अणु
			freq = freq_table[j].frequency;
			अगर (freq == CPUFREQ_ENTRY_INVALID ||
					freq <= max_freq)
				जारी;
			ind = j;
			max_freq = freq;
		पूर्ण

		अगर (ind != i) अणु
			/* exchange the frequencies */
			table.driver_data = freq_table[i].driver_data;
			table.frequency = freq_table[i].frequency;
			freq_table[i].driver_data = freq_table[ind].driver_data;
			freq_table[i].frequency = freq_table[ind].frequency;
			freq_table[ind].driver_data = table.driver_data;
			freq_table[ind].frequency = table.frequency;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qoriq_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device_node *np;
	पूर्णांक i, count;
	u32 freq;
	काष्ठा clk *clk;
	स्थिर काष्ठा clk_hw *hwclk;
	काष्ठा cpufreq_frequency_table *table;
	काष्ठा cpu_data *data;
	अचिन्हित पूर्णांक cpu = policy->cpu;
	u64 u64temp;

	np = of_get_cpu_node(cpu, शून्य);
	अगर (!np)
		वापस -ENODEV;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ err_np;

	policy->clk = of_clk_get(np, 0);
	अगर (IS_ERR(policy->clk)) अणु
		pr_err("%s: no clock information\n", __func__);
		जाओ err_nomem2;
	पूर्ण

	hwclk = __clk_get_hw(policy->clk);
	count = clk_hw_get_num_parents(hwclk);

	data->pclk = kसुस्मृति(count, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!data->pclk)
		जाओ err_nomem2;

	table = kसुस्मृति(count + 1, माप(*table), GFP_KERNEL);
	अगर (!table)
		जाओ err_pclk;

	क्रम (i = 0; i < count; i++) अणु
		clk = clk_hw_get_parent_by_index(hwclk, i)->clk;
		data->pclk[i] = clk;
		freq = clk_get_rate(clk);
		table[i].frequency = freq / 1000;
		table[i].driver_data = i;
	पूर्ण
	freq_table_redup(table, count);
	freq_table_sort(table, count);
	table[i].frequency = CPUFREQ_TABLE_END;
	policy->freq_table = table;
	data->table = table;

	/* update ->cpus अगर we have cluster, no harm अगर not */
	set_affected_cpus(policy);
	policy->driver_data = data;

	/* Minimum transition latency is 12 platक्रमm घड़ीs */
	u64temp = 12ULL * NSEC_PER_SEC;
	करो_भाग(u64temp, get_bus_freq());
	policy->cpuinfo.transition_latency = u64temp + 1;

	of_node_put(np);

	वापस 0;

err_pclk:
	kमुक्त(data->pclk);
err_nomem2:
	kमुक्त(data);
err_np:
	of_node_put(np);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक qoriq_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpu_data *data = policy->driver_data;

	kमुक्त(data->pclk);
	kमुक्त(data->table);
	kमुक्त(data);
	policy->driver_data = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक qoriq_cpufreq_target(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक index)
अणु
	काष्ठा clk *parent;
	काष्ठा cpu_data *data = policy->driver_data;

	parent = data->pclk[data->table[index].driver_data];
	वापस clk_set_parent(policy->clk, parent);
पूर्ण

अटल काष्ठा cpufreq_driver qoriq_cpufreq_driver = अणु
	.name		= "qoriq_cpufreq",
	.flags		= CPUFREQ_CONST_LOOPS |
			  CPUFREQ_IS_COOLING_DEV,
	.init		= qoriq_cpufreq_cpu_init,
	.निकास		= qoriq_cpufreq_cpu_निकास,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= qoriq_cpufreq_target,
	.get		= cpufreq_generic_get,
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qoriq_cpufreq_blacklist[] = अणु
	/* e6500 cannot use cpufreq due to erratum A-008083 */
	अणु .compatible = "fsl,b4420-clockgen", पूर्ण,
	अणु .compatible = "fsl,b4860-clockgen", पूर्ण,
	अणु .compatible = "fsl,t2080-clockgen", पूर्ण,
	अणु .compatible = "fsl,t4240-clockgen", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक qoriq_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, qoriq_cpufreq_blacklist);
	अगर (np) अणु
		dev_info(&pdev->dev, "Disabling due to erratum A-008083");
		वापस -ENODEV;
	पूर्ण

	ret = cpufreq_रेजिस्टर_driver(&qoriq_cpufreq_driver);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "Freescale QorIQ CPU frequency scaling driver\n");
	वापस 0;
पूर्ण

अटल पूर्णांक qoriq_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&qoriq_cpufreq_driver);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qoriq_cpufreq_platक्रमm_driver = अणु
	.driver = अणु
		.name = "qoriq-cpufreq",
	पूर्ण,
	.probe = qoriq_cpufreq_probe,
	.हटाओ = qoriq_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(qoriq_cpufreq_platक्रमm_driver);

MODULE_ALIAS("platform:qoriq-cpufreq");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tang Yuantian <Yuantian.Tang@freescale.com>");
MODULE_DESCRIPTION("cpufreq driver for Freescale QorIQ series SoCs");
