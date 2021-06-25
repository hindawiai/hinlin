<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Copyright (C) 2014 Linaro.
 * Viresh Kumar <viresh.kumar@linaro.org>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश "cpufreq-dt.h"

काष्ठा निजी_data अणु
	काष्ठा list_head node;

	cpumask_var_t cpus;
	काष्ठा device *cpu_dev;
	काष्ठा opp_table *opp_table;
	काष्ठा cpufreq_frequency_table *freq_table;
	bool have_अटल_opps;
पूर्ण;

अटल LIST_HEAD(priv_list);

अटल काष्ठा freq_attr *cpufreq_dt_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	शून्य,   /* Extra space क्रम boost-attr अगर required */
	शून्य,
पूर्ण;

अटल काष्ठा निजी_data *cpufreq_dt_find_data(पूर्णांक cpu)
अणु
	काष्ठा निजी_data *priv;

	list_क्रम_each_entry(priv, &priv_list, node) अणु
		अगर (cpumask_test_cpu(cpu, priv->cpus))
			वापस priv;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक set_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;
	अचिन्हित दीर्घ freq = policy->freq_table[index].frequency;

	वापस dev_pm_opp_set_rate(priv->cpu_dev, freq * 1000);
पूर्ण

/*
 * An earlier version of opp-v1 bindings used to name the regulator
 * "cpu0-supply", we still need to handle that क्रम backwards compatibility.
 */
अटल स्थिर अक्षर *find_supply_name(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	काष्ठा property *pp;
	पूर्णांक cpu = dev->id;
	स्थिर अक्षर *name = शून्य;

	np = of_node_get(dev->of_node);

	/* This must be valid क्रम sure */
	अगर (WARN_ON(!np))
		वापस शून्य;

	/* Try "cpu0" क्रम older DTs */
	अगर (!cpu) अणु
		pp = of_find_property(np, "cpu0-supply", शून्य);
		अगर (pp) अणु
			name = "cpu0";
			जाओ node_put;
		पूर्ण
	पूर्ण

	pp = of_find_property(np, "cpu-supply", शून्य);
	अगर (pp) अणु
		name = "cpu";
		जाओ node_put;
	पूर्ण

	dev_dbg(dev, "no regulator for cpu%d\n", cpu);
node_put:
	of_node_put(np);
	वापस name;
पूर्ण

अटल पूर्णांक cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा निजी_data *priv;
	काष्ठा device *cpu_dev;
	काष्ठा clk *cpu_clk;
	अचिन्हित पूर्णांक transition_latency;
	पूर्णांक ret;

	priv = cpufreq_dt_find_data(policy->cpu);
	अगर (!priv) अणु
		pr_err("failed to find data for cpu%d\n", policy->cpu);
		वापस -ENODEV;
	पूर्ण
	cpu_dev = priv->cpu_dev;

	cpu_clk = clk_get(cpu_dev, शून्य);
	अगर (IS_ERR(cpu_clk)) अणु
		ret = PTR_ERR(cpu_clk);
		dev_err(cpu_dev, "%s: failed to get clk: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	transition_latency = dev_pm_opp_get_max_transition_latency(cpu_dev);
	अगर (!transition_latency)
		transition_latency = CPUFREQ_ETERNAL;

	cpumask_copy(policy->cpus, priv->cpus);
	policy->driver_data = priv;
	policy->clk = cpu_clk;
	policy->freq_table = priv->freq_table;
	policy->suspend_freq = dev_pm_opp_get_suspend_opp_freq(cpu_dev) / 1000;
	policy->cpuinfo.transition_latency = transition_latency;
	policy->dvfs_possible_from_any_cpu = true;

	/* Support turbo/boost mode */
	अगर (policy_has_boost_freq(policy)) अणु
		/* This माला_लो disabled by core on driver unरेजिस्टर */
		ret = cpufreq_enable_boost_support();
		अगर (ret)
			जाओ out_clk_put;
		cpufreq_dt_attr[1] = &cpufreq_freq_attr_scaling_boost_freqs;
	पूर्ण

	dev_pm_opp_of_रेजिस्टर_em(cpu_dev, policy->cpus);

	वापस 0;

out_clk_put:
	clk_put(cpu_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक cpufreq_online(काष्ठा cpufreq_policy *policy)
अणु
	/* We did light-weight tear करोwn earlier, nothing to करो here */
	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_offline(काष्ठा cpufreq_policy *policy)
अणु
	/*
	 * Preserve policy->driver_data and करोn't मुक्त resources on light-weight
	 * tear करोwn.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	clk_put(policy->clk);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver dt_cpufreq_driver = अणु
	.flags = CPUFREQ_NEED_INITIAL_FREQ_CHECK |
		 CPUFREQ_IS_COOLING_DEV,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = set_target,
	.get = cpufreq_generic_get,
	.init = cpufreq_init,
	.निकास = cpufreq_निकास,
	.online = cpufreq_online,
	.offline = cpufreq_offline,
	.name = "cpufreq-dt",
	.attr = cpufreq_dt_attr,
	.suspend = cpufreq_generic_suspend,
पूर्ण;

अटल पूर्णांक dt_cpufreq_early_init(काष्ठा device *dev, पूर्णांक cpu)
अणु
	काष्ठा निजी_data *priv;
	काष्ठा device *cpu_dev;
	bool fallback = false;
	स्थिर अक्षर *reg_name;
	पूर्णांक ret;

	/* Check अगर this CPU is alपढ़ोy covered by some other policy */
	अगर (cpufreq_dt_find_data(cpu))
		वापस 0;

	cpu_dev = get_cpu_device(cpu);
	अगर (!cpu_dev)
		वापस -EPROBE_DEFER;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (!alloc_cpumask_var(&priv->cpus, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_set_cpu(cpu, priv->cpus);
	priv->cpu_dev = cpu_dev;

	/*
	 * OPP layer will be taking care of regulators now, but it needs to know
	 * the name of the regulator first.
	 */
	reg_name = find_supply_name(cpu_dev);
	अगर (reg_name) अणु
		priv->opp_table = dev_pm_opp_set_regulators(cpu_dev, &reg_name,
							    1);
		अगर (IS_ERR(priv->opp_table)) अणु
			ret = PTR_ERR(priv->opp_table);
			अगर (ret != -EPROBE_DEFER)
				dev_err(cpu_dev, "failed to set regulators: %d\n",
					ret);
			जाओ मुक्त_cpumask;
		पूर्ण
	पूर्ण

	/* Get OPP-sharing inक्रमmation from "operating-points-v2" bindings */
	ret = dev_pm_opp_of_get_sharing_cpus(cpu_dev, priv->cpus);
	अगर (ret) अणु
		अगर (ret != -ENOENT)
			जाओ out;

		/*
		 * operating-poपूर्णांकs-v2 not supported, fallback to all CPUs share
		 * OPP क्रम backward compatibility अगर the platक्रमm hasn't set
		 * sharing CPUs.
		 */
		अगर (dev_pm_opp_get_sharing_cpus(cpu_dev, priv->cpus))
			fallback = true;
	पूर्ण

	/*
	 * Initialize OPP tables क्रम all priv->cpus. They will be shared by
	 * all CPUs which have marked their CPUs shared with OPP bindings.
	 *
	 * For platक्रमms not using operating-poपूर्णांकs-v2 bindings, we करो this
	 * beक्रमe updating priv->cpus. Otherwise, we will end up creating
	 * duplicate OPPs क्रम the CPUs.
	 *
	 * OPPs might be populated at runसमय, करोn't fail क्रम error here unless
	 * it is -EPROBE_DEFER.
	 */
	ret = dev_pm_opp_of_cpumask_add_table(priv->cpus);
	अगर (!ret) अणु
		priv->have_अटल_opps = true;
	पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
		जाओ out;
	पूर्ण

	/*
	 * The OPP table must be initialized, अटलally or dynamically, by this
	 * poपूर्णांक.
	 */
	ret = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (ret <= 0) अणु
		dev_err(cpu_dev, "OPP table can't be empty\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (fallback) अणु
		cpumask_setall(priv->cpus);
		ret = dev_pm_opp_set_sharing_cpus(cpu_dev, priv->cpus);
		अगर (ret)
			dev_err(cpu_dev, "%s: failed to mark OPPs as shared: %d\n",
				__func__, ret);
	पूर्ण

	ret = dev_pm_opp_init_cpufreq_table(cpu_dev, &priv->freq_table);
	अगर (ret) अणु
		dev_err(cpu_dev, "failed to init cpufreq table: %d\n", ret);
		जाओ out;
	पूर्ण

	list_add(&priv->node, &priv_list);
	वापस 0;

out:
	अगर (priv->have_अटल_opps)
		dev_pm_opp_of_cpumask_हटाओ_table(priv->cpus);
	dev_pm_opp_put_regulators(priv->opp_table);
मुक्त_cpumask:
	मुक्त_cpumask_var(priv->cpus);
	वापस ret;
पूर्ण

अटल व्योम dt_cpufreq_release(व्योम)
अणु
	काष्ठा निजी_data *priv, *पंचांगp;

	list_क्रम_each_entry_safe(priv, पंचांगp, &priv_list, node) अणु
		dev_pm_opp_मुक्त_cpufreq_table(priv->cpu_dev, &priv->freq_table);
		अगर (priv->have_अटल_opps)
			dev_pm_opp_of_cpumask_हटाओ_table(priv->cpus);
		dev_pm_opp_put_regulators(priv->opp_table);
		मुक्त_cpumask_var(priv->cpus);
		list_del(&priv->node);
	पूर्ण
पूर्ण

अटल पूर्णांक dt_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpufreq_dt_platक्रमm_data *data = dev_get_platdata(&pdev->dev);
	पूर्णांक ret, cpu;

	/* Request resources early so we can वापस in हाल of -EPROBE_DEFER */
	क्रम_each_possible_cpu(cpu) अणु
		ret = dt_cpufreq_early_init(&pdev->dev, cpu);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (data) अणु
		अगर (data->have_governor_per_policy)
			dt_cpufreq_driver.flags |= CPUFREQ_HAVE_GOVERNOR_PER_POLICY;

		dt_cpufreq_driver.resume = data->resume;
		अगर (data->suspend)
			dt_cpufreq_driver.suspend = data->suspend;
		अगर (data->get_पूर्णांकermediate) अणु
			dt_cpufreq_driver.target_पूर्णांकermediate = data->target_पूर्णांकermediate;
			dt_cpufreq_driver.get_पूर्णांकermediate = data->get_पूर्णांकermediate;
		पूर्ण
	पूर्ण

	ret = cpufreq_रेजिस्टर_driver(&dt_cpufreq_driver);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed register driver: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dt_cpufreq_release();
	वापस ret;
पूर्ण

अटल पूर्णांक dt_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&dt_cpufreq_driver);
	dt_cpufreq_release();
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dt_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "cpufreq-dt",
	पूर्ण,
	.probe		= dt_cpufreq_probe,
	.हटाओ		= dt_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(dt_cpufreq_platdrv);

MODULE_ALIAS("platform:cpufreq-dt");
MODULE_AUTHOR("Viresh Kumar <viresh.kumar@linaro.org>");
MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("Generic cpufreq driver");
MODULE_LICENSE("GPL");
