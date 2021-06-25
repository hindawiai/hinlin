<शैली गुरु>
/*
 * System Control and Power Interface (SCPI) based CPUFreq Interface driver
 *
 * Copyright (C) 2015 ARM Ltd.
 * Sudeep Holla <sudeep.holla@arm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/scpi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

काष्ठा scpi_data अणु
	काष्ठा clk *clk;
	काष्ठा device *cpu_dev;
पूर्ण;

अटल काष्ठा scpi_ops *scpi_ops;

अटल अचिन्हित पूर्णांक scpi_cpufreq_get_rate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get_raw(cpu);
	काष्ठा scpi_data *priv = policy->driver_data;
	अचिन्हित दीर्घ rate = clk_get_rate(priv->clk);

	वापस rate / 1000;
पूर्ण

अटल पूर्णांक
scpi_cpufreq_set_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	u64 rate = policy->freq_table[index].frequency * 1000;
	काष्ठा scpi_data *priv = policy->driver_data;
	पूर्णांक ret;

	ret = clk_set_rate(priv->clk, rate);

	अगर (ret)
		वापस ret;

	अगर (clk_get_rate(priv->clk) != rate)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
scpi_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask)
अणु
	पूर्णांक cpu, करोमुख्य, tकरोमुख्य;
	काष्ठा device *tcpu_dev;

	करोमुख्य = scpi_ops->device_करोमुख्य_id(cpu_dev);
	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == cpu_dev->id)
			जारी;

		tcpu_dev = get_cpu_device(cpu);
		अगर (!tcpu_dev)
			जारी;

		tकरोमुख्य = scpi_ops->device_करोमुख्य_id(tcpu_dev);
		अगर (tकरोमुख्य == करोमुख्य)
			cpumask_set_cpu(cpu, cpumask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scpi_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक latency;
	काष्ठा device *cpu_dev;
	काष्ठा scpi_data *priv;
	काष्ठा cpufreq_frequency_table *freq_table;

	cpu_dev = get_cpu_device(policy->cpu);
	अगर (!cpu_dev) अणु
		pr_err("failed to get cpu%d device\n", policy->cpu);
		वापस -ENODEV;
	पूर्ण

	ret = scpi_ops->add_opps_to_device(cpu_dev);
	अगर (ret) अणु
		dev_warn(cpu_dev, "failed to add opps to the device\n");
		वापस ret;
	पूर्ण

	ret = scpi_get_sharing_cpus(cpu_dev, policy->cpus);
	अगर (ret) अणु
		dev_warn(cpu_dev, "failed to get sharing cpumask\n");
		वापस ret;
	पूर्ण

	ret = dev_pm_opp_set_sharing_cpus(cpu_dev, policy->cpus);
	अगर (ret) अणु
		dev_err(cpu_dev, "%s: failed to mark OPPs as shared: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (ret <= 0) अणु
		dev_dbg(cpu_dev, "OPP table is not ready, deferring probe\n");
		ret = -EPROBE_DEFER;
		जाओ out_मुक्त_opp;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_opp;
	पूर्ण

	ret = dev_pm_opp_init_cpufreq_table(cpu_dev, &freq_table);
	अगर (ret) अणु
		dev_err(cpu_dev, "failed to init cpufreq table: %d\n", ret);
		जाओ out_मुक्त_priv;
	पूर्ण

	priv->cpu_dev = cpu_dev;
	priv->clk = clk_get(cpu_dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(cpu_dev, "%s: Failed to get clk for cpu: %d\n",
			__func__, cpu_dev->id);
		ret = PTR_ERR(priv->clk);
		जाओ out_मुक्त_cpufreq_table;
	पूर्ण

	policy->driver_data = priv;
	policy->freq_table = freq_table;

	/* scpi allows DVFS request क्रम any करोमुख्य from any CPU */
	policy->dvfs_possible_from_any_cpu = true;

	latency = scpi_ops->get_transition_latency(cpu_dev);
	अगर (!latency)
		latency = CPUFREQ_ETERNAL;

	policy->cpuinfo.transition_latency = latency;

	policy->fast_चयन_possible = false;

	dev_pm_opp_of_रेजिस्टर_em(cpu_dev, policy->cpus);

	वापस 0;

out_मुक्त_cpufreq_table:
	dev_pm_opp_मुक्त_cpufreq_table(cpu_dev, &freq_table);
out_मुक्त_priv:
	kमुक्त(priv);
out_मुक्त_opp:
	dev_pm_opp_हटाओ_all_dynamic(cpu_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक scpi_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा scpi_data *priv = policy->driver_data;

	clk_put(priv->clk);
	dev_pm_opp_मुक्त_cpufreq_table(priv->cpu_dev, &policy->freq_table);
	dev_pm_opp_हटाओ_all_dynamic(priv->cpu_dev);
	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver scpi_cpufreq_driver = अणु
	.name	= "scpi-cpufreq",
	.flags	= CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
		  CPUFREQ_NEED_INITIAL_FREQ_CHECK |
		  CPUFREQ_IS_COOLING_DEV,
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.attr	= cpufreq_generic_attr,
	.get	= scpi_cpufreq_get_rate,
	.init	= scpi_cpufreq_init,
	.निकास	= scpi_cpufreq_निकास,
	.target_index	= scpi_cpufreq_set_target,
पूर्ण;

अटल पूर्णांक scpi_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	scpi_ops = get_scpi_ops();
	अगर (!scpi_ops)
		वापस -EIO;

	ret = cpufreq_रेजिस्टर_driver(&scpi_cpufreq_driver);
	अगर (ret)
		dev_err(&pdev->dev, "%s: registering cpufreq failed, err: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक scpi_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&scpi_cpufreq_driver);
	scpi_ops = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver scpi_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "scpi-cpufreq",
	पूर्ण,
	.probe		= scpi_cpufreq_probe,
	.हटाओ		= scpi_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(scpi_cpufreq_platdrv);

MODULE_ALIAS("platform:scpi-cpufreq");
MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCPI CPUFreq interface driver");
MODULE_LICENSE("GPL v2");
