<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Power Interface (SCMI) based CPUFreq Interface driver
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 * Sudeep Holla <sudeep.holla@arm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/types.h>

काष्ठा scmi_data अणु
	पूर्णांक करोमुख्य_id;
	काष्ठा device *cpu_dev;
पूर्ण;

अटल काष्ठा scmi_protocol_handle *ph;
अटल स्थिर काष्ठा scmi_perf_proto_ops *perf_ops;

अटल अचिन्हित पूर्णांक scmi_cpufreq_get_rate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get_raw(cpu);
	काष्ठा scmi_data *priv = policy->driver_data;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	ret = perf_ops->freq_get(ph, priv->करोमुख्य_id, &rate, false);
	अगर (ret)
		वापस 0;
	वापस rate / 1000;
पूर्ण

/*
 * perf_ops->freq_set is not a synchronous, the actual OPP change will
 * happen asynchronously and can get notअगरied अगर the events are
 * subscribed क्रम by the SCMI firmware
 */
अटल पूर्णांक
scmi_cpufreq_set_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	काष्ठा scmi_data *priv = policy->driver_data;
	u64 freq = policy->freq_table[index].frequency;

	वापस perf_ops->freq_set(ph, priv->करोमुख्य_id, freq * 1000, false);
पूर्ण

अटल अचिन्हित पूर्णांक scmi_cpufreq_fast_चयन(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा scmi_data *priv = policy->driver_data;

	अगर (!perf_ops->freq_set(ph, priv->करोमुख्य_id,
				target_freq * 1000, true))
		वापस target_freq;

	वापस 0;
पूर्ण

अटल पूर्णांक
scmi_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask)
अणु
	पूर्णांक cpu, करोमुख्य, tकरोमुख्य;
	काष्ठा device *tcpu_dev;

	करोमुख्य = perf_ops->device_करोमुख्य_id(cpu_dev);
	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == cpu_dev->id)
			जारी;

		tcpu_dev = get_cpu_device(cpu);
		अगर (!tcpu_dev)
			जारी;

		tकरोमुख्य = perf_ops->device_करोमुख्य_id(tcpu_dev);
		अगर (tकरोमुख्य == करोमुख्य)
			cpumask_set_cpu(cpu, cpumask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
scmi_get_cpu_घातer(अचिन्हित दीर्घ *घातer, अचिन्हित दीर्घ *KHz,
		   काष्ठा device *cpu_dev)
अणु
	अचिन्हित दीर्घ Hz;
	पूर्णांक ret, करोमुख्य;

	करोमुख्य = perf_ops->device_करोमुख्य_id(cpu_dev);
	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	/* Get the घातer cost of the perक्रमmance करोमुख्य. */
	Hz = *KHz * 1000;
	ret = perf_ops->est_घातer_get(ph, करोमुख्य, &Hz, घातer);
	अगर (ret)
		वापस ret;

	/* The EM framework specअगरies the frequency in KHz. */
	*KHz = Hz / 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret, nr_opp;
	अचिन्हित पूर्णांक latency;
	काष्ठा device *cpu_dev;
	काष्ठा scmi_data *priv;
	काष्ठा cpufreq_frequency_table *freq_table;
	काष्ठा em_data_callback em_cb = EM_DATA_CB(scmi_get_cpu_घातer);
	cpumask_var_t opp_shared_cpus;
	bool घातer_scale_mw;

	cpu_dev = get_cpu_device(policy->cpu);
	अगर (!cpu_dev) अणु
		pr_err("failed to get cpu%d device\n", policy->cpu);
		वापस -ENODEV;
	पूर्ण

	अगर (!zalloc_cpumask_var(&opp_shared_cpus, GFP_KERNEL))
		ret = -ENOMEM;

	/* Obtain CPUs that share SCMI perक्रमmance controls */
	ret = scmi_get_sharing_cpus(cpu_dev, policy->cpus);
	अगर (ret) अणु
		dev_warn(cpu_dev, "failed to get sharing cpumask\n");
		जाओ out_मुक्त_cpumask;
	पूर्ण

	/*
	 * Obtain CPUs that share perक्रमmance levels.
	 * The OPP 'sharing cpus' info may come from DT through an empty opp
	 * table and opp-shared.
	 */
	ret = dev_pm_opp_of_get_sharing_cpus(cpu_dev, opp_shared_cpus);
	अगर (ret || !cpumask_weight(opp_shared_cpus)) अणु
		/*
		 * Either opp-table is not set or no opp-shared was found.
		 * Use the CPU mask from SCMI to designate CPUs sharing an OPP
		 * table.
		 */
		cpumask_copy(opp_shared_cpus, policy->cpus);
	पूर्ण

	 /*
	  * A previous CPU may have marked OPPs as shared क्रम a few CPUs, based on
	  * what OPP core provided. If the current CPU is part of those few, then
	  * there is no need to add OPPs again.
	  */
	nr_opp = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (nr_opp <= 0) अणु
		ret = perf_ops->device_opps_add(ph, cpu_dev);
		अगर (ret) अणु
			dev_warn(cpu_dev, "failed to add opps to the device\n");
			जाओ out_मुक्त_cpumask;
		पूर्ण

		nr_opp = dev_pm_opp_get_opp_count(cpu_dev);
		अगर (nr_opp <= 0) अणु
			dev_err(cpu_dev, "%s: No OPPs for this device: %d\n",
				__func__, ret);

			ret = -ENODEV;
			जाओ out_मुक्त_opp;
		पूर्ण

		ret = dev_pm_opp_set_sharing_cpus(cpu_dev, opp_shared_cpus);
		अगर (ret) अणु
			dev_err(cpu_dev, "%s: failed to mark OPPs as shared: %d\n",
				__func__, ret);

			जाओ out_मुक्त_opp;
		पूर्ण

		घातer_scale_mw = perf_ops->घातer_scale_mw_get(ph);
		em_dev_रेजिस्टर_perf_करोमुख्य(cpu_dev, nr_opp, &em_cb,
					    opp_shared_cpus, घातer_scale_mw);
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
	priv->करोमुख्य_id = perf_ops->device_करोमुख्य_id(cpu_dev);

	policy->driver_data = priv;
	policy->freq_table = freq_table;

	/* SCMI allows DVFS request क्रम any करोमुख्य from any CPU */
	policy->dvfs_possible_from_any_cpu = true;

	latency = perf_ops->transition_latency_get(ph, cpu_dev);
	अगर (!latency)
		latency = CPUFREQ_ETERNAL;

	policy->cpuinfo.transition_latency = latency;

	policy->fast_चयन_possible =
		perf_ops->fast_चयन_possible(ph, cpu_dev);

	मुक्त_cpumask_var(opp_shared_cpus);
	वापस 0;

out_मुक्त_priv:
	kमुक्त(priv);

out_मुक्त_opp:
	dev_pm_opp_हटाओ_all_dynamic(cpu_dev);

out_मुक्त_cpumask:
	मुक्त_cpumask_var(opp_shared_cpus);

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा scmi_data *priv = policy->driver_data;

	dev_pm_opp_मुक्त_cpufreq_table(priv->cpu_dev, &policy->freq_table);
	dev_pm_opp_हटाओ_all_dynamic(priv->cpu_dev);
	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver scmi_cpufreq_driver = अणु
	.name	= "scmi",
	.flags	= CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
		  CPUFREQ_NEED_INITIAL_FREQ_CHECK |
		  CPUFREQ_IS_COOLING_DEV,
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.attr	= cpufreq_generic_attr,
	.target_index	= scmi_cpufreq_set_target,
	.fast_चयन	= scmi_cpufreq_fast_चयन,
	.get	= scmi_cpufreq_get_rate,
	.init	= scmi_cpufreq_init,
	.निकास	= scmi_cpufreq_निकास,
पूर्ण;

अटल पूर्णांक scmi_cpufreq_probe(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &sdev->dev;
	स्थिर काष्ठा scmi_handle *handle;

	handle = sdev->handle;

	अगर (!handle)
		वापस -ENODEV;

	perf_ops = handle->devm_protocol_get(sdev, SCMI_PROTOCOL_PERF, &ph);
	अगर (IS_ERR(perf_ops))
		वापस PTR_ERR(perf_ops);

#अगर_घोषित CONFIG_COMMON_CLK
	/* dummy घड़ी provider as needed by OPP अगर घड़ीs property is used */
	अगर (of_find_property(dev->of_node, "#clock-cells", शून्य))
		devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, शून्य);
#पूर्ण_अगर

	ret = cpufreq_रेजिस्टर_driver(&scmi_cpufreq_driver);
	अगर (ret) अणु
		dev_err(dev, "%s: registering cpufreq failed, err: %d\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम scmi_cpufreq_हटाओ(काष्ठा scmi_device *sdev)
अणु
	cpufreq_unरेजिस्टर_driver(&scmi_cpufreq_driver);
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_PERF, "cpufreq" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_cpufreq_drv = अणु
	.name		= "scmi-cpufreq",
	.probe		= scmi_cpufreq_probe,
	.हटाओ		= scmi_cpufreq_हटाओ,
	.id_table	= scmi_id_table,
पूर्ण;
module_scmi_driver(scmi_cpufreq_drv);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI CPUFreq interface driver");
MODULE_LICENSE("GPL v2");
