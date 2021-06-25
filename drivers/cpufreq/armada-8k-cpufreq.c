<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CPUFreq support क्रम Armada 8K
 *
 * Copyright (C) 2018 Marvell
 *
 * Omri Itach <omrii@marvell.com>
 * Gregory Clement <gregory.clement@bootlin.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>

/*
 * Setup the opps list with the भागider क्रम the max frequency, that
 * will be filled at runसमय.
 */
अटल स्थिर पूर्णांक opps_भाग[] __initस्थिर = अणु1, 2, 3, 4पूर्ण;

अटल काष्ठा platक्रमm_device *armada_8k_pdev;

काष्ठा freq_table अणु
	काष्ठा device *cpu_dev;
	अचिन्हित पूर्णांक freq[ARRAY_SIZE(opps_भाग)];
पूर्ण;

/* If the CPUs share the same घड़ी, then they are in the same cluster. */
अटल व्योम __init armada_8k_get_sharing_cpus(काष्ठा clk *cur_clk,
					      काष्ठा cpumask *cpumask)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *cpu_dev;
		काष्ठा clk *clk;

		cpu_dev = get_cpu_device(cpu);
		अगर (!cpu_dev) अणु
			pr_warn("Failed to get cpu%d device\n", cpu);
			जारी;
		पूर्ण

		clk = clk_get(cpu_dev, 0);
		अगर (IS_ERR(clk)) अणु
			pr_warn("Cannot get clock for CPU %d\n", cpu);
		पूर्ण अन्यथा अणु
			अगर (clk_is_match(clk, cur_clk))
				cpumask_set_cpu(cpu, cpumask);

			clk_put(clk);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init armada_8k_add_opp(काष्ठा clk *clk, काष्ठा device *cpu_dev,
				    काष्ठा freq_table *freq_tables,
				    पूर्णांक opps_index)
अणु
	अचिन्हित पूर्णांक cur_frequency;
	अचिन्हित पूर्णांक freq;
	पूर्णांक i, ret;

	/* Get nominal (current) CPU frequency. */
	cur_frequency = clk_get_rate(clk);
	अगर (!cur_frequency) अणु
		dev_err(cpu_dev, "Failed to get clock rate for this CPU\n");
		वापस -EINVAL;
	पूर्ण

	freq_tables[opps_index].cpu_dev = cpu_dev;

	क्रम (i = 0; i < ARRAY_SIZE(opps_भाग); i++) अणु
		freq = cur_frequency / opps_भाग[i];

		ret = dev_pm_opp_add(cpu_dev, freq, 0);
		अगर (ret)
			वापस ret;

		freq_tables[opps_index].freq[i] = freq;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम armada_8k_cpufreq_मुक्त_table(काष्ठा freq_table *freq_tables)
अणु
	पूर्णांक opps_index, nb_cpus = num_possible_cpus();

	क्रम (opps_index = 0 ; opps_index <= nb_cpus; opps_index++) अणु
		पूर्णांक i;

		/* If cpu_dev is शून्य then we reached the end of the array */
		अगर (!freq_tables[opps_index].cpu_dev)
			अवरोध;

		क्रम (i = 0; i < ARRAY_SIZE(opps_भाग); i++) अणु
			/*
			 * A 0Hz frequency is not valid, this meant
			 * that it was not yet initialized so there is
			 * no more opp to मुक्त
			 */
			अगर (freq_tables[opps_index].freq[i] == 0)
				अवरोध;

			dev_pm_opp_हटाओ(freq_tables[opps_index].cpu_dev,
					  freq_tables[opps_index].freq[i]);
		पूर्ण
	पूर्ण

	kमुक्त(freq_tables);
पूर्ण

अटल पूर्णांक __init armada_8k_cpufreq_init(व्योम)
अणु
	पूर्णांक ret = 0, opps_index = 0, cpu, nb_cpus;
	काष्ठा freq_table *freq_tables;
	काष्ठा device_node *node;
	काष्ठा cpumask cpus;

	node = of_find_compatible_node(शून्य, शून्य, "marvell,ap806-cpu-clock");
	अगर (!node || !of_device_is_available(node)) अणु
		of_node_put(node);
		वापस -ENODEV;
	पूर्ण
	of_node_put(node);

	nb_cpus = num_possible_cpus();
	freq_tables = kसुस्मृति(nb_cpus, माप(*freq_tables), GFP_KERNEL);
	अगर (!freq_tables)
		वापस -ENOMEM;
	cpumask_copy(&cpus, cpu_possible_mask);

	/*
	 * For each CPU, this loop रेजिस्टरs the operating poपूर्णांकs
	 * supported (which are the nominal CPU frequency and full पूर्णांकeger
	 * भागisions of it).
	 */
	क्रम_each_cpu(cpu, &cpus) अणु
		काष्ठा cpumask shared_cpus;
		काष्ठा device *cpu_dev;
		काष्ठा clk *clk;

		cpu_dev = get_cpu_device(cpu);

		अगर (!cpu_dev) अणु
			pr_err("Cannot get CPU %d\n", cpu);
			जारी;
		पूर्ण

		clk = clk_get(cpu_dev, 0);

		अगर (IS_ERR(clk)) अणु
			pr_err("Cannot get clock for CPU %d\n", cpu);
			ret = PTR_ERR(clk);
			जाओ हटाओ_opp;
		पूर्ण

		ret = armada_8k_add_opp(clk, cpu_dev, freq_tables, opps_index);
		अगर (ret) अणु
			clk_put(clk);
			जाओ हटाओ_opp;
		पूर्ण

		opps_index++;
		cpumask_clear(&shared_cpus);
		armada_8k_get_sharing_cpus(clk, &shared_cpus);
		dev_pm_opp_set_sharing_cpus(cpu_dev, &shared_cpus);
		cpumask_andnot(&cpus, &cpus, &shared_cpus);
		clk_put(clk);
	पूर्ण

	armada_8k_pdev = platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1,
							 शून्य, 0);
	ret = PTR_ERR_OR_ZERO(armada_8k_pdev);
	अगर (ret)
		जाओ हटाओ_opp;

	platक्रमm_set_drvdata(armada_8k_pdev, freq_tables);

	वापस 0;

हटाओ_opp:
	armada_8k_cpufreq_मुक्त_table(freq_tables);
	वापस ret;
पूर्ण
module_init(armada_8k_cpufreq_init);

अटल व्योम __निकास armada_8k_cpufreq_निकास(व्योम)
अणु
	काष्ठा freq_table *freq_tables = platक्रमm_get_drvdata(armada_8k_pdev);

	platक्रमm_device_unरेजिस्टर(armada_8k_pdev);
	armada_8k_cpufreq_मुक्त_table(freq_tables);
पूर्ण
module_निकास(armada_8k_cpufreq_निकास);

अटल स्थिर काष्ठा of_device_id __maybe_unused armada_8k_cpufreq_of_match[] = अणु
	अणु .compatible = "marvell,ap806-cpu-clock" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, armada_8k_cpufreq_of_match);

MODULE_AUTHOR("Gregory Clement <gregory.clement@bootlin.com>");
MODULE_DESCRIPTION("Armada 8K cpufreq driver");
MODULE_LICENSE("GPL");
