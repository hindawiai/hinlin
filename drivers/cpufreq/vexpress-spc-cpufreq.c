<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Versatile Express SPC CPUFreq Interface driver
 *
 * Copyright (C) 2013 - 2019 ARM Ltd.
 * Sudeep Holla <sudeep.holla@arm.com>
 *
 * Copyright (C) 2013 Linaro.
 * Viresh Kumar <viresh.kumar@linaro.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/topology.h>
#समावेश <linux/types.h>

/* Currently we support only two clusters */
#घोषणा A15_CLUSTER	0
#घोषणा A7_CLUSTER	1
#घोषणा MAX_CLUSTERS	2

#अगर_घोषित CONFIG_BL_SWITCHER
#समावेश <यंत्र/bL_चयनer.h>
अटल bool bL_चयनing_enabled;
#घोषणा is_bL_चयनing_enabled()	bL_चयनing_enabled
#घोषणा set_चयनing_enabled(x)	(bL_चयनing_enabled = (x))
#अन्यथा
#घोषणा is_bL_चयनing_enabled()	false
#घोषणा set_चयनing_enabled(x)	करो अणु पूर्ण जबतक (0)
#घोषणा bL_चयन_request(...)		करो अणु पूर्ण जबतक (0)
#घोषणा bL_चयनer_put_enabled()	करो अणु पूर्ण जबतक (0)
#घोषणा bL_चयनer_get_enabled()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा ACTUAL_FREQ(cluster, freq)  ((cluster == A7_CLUSTER) ? freq << 1 : freq)
#घोषणा VIRT_FREQ(cluster, freq)    ((cluster == A7_CLUSTER) ? freq >> 1 : freq)

अटल काष्ठा thermal_cooling_device *cdev[MAX_CLUSTERS];
अटल काष्ठा clk *clk[MAX_CLUSTERS];
अटल काष्ठा cpufreq_frequency_table *freq_table[MAX_CLUSTERS + 1];
अटल atomic_t cluster_usage[MAX_CLUSTERS + 1];

अटल अचिन्हित पूर्णांक clk_big_min;	/* (Big) घड़ी frequencies */
अटल अचिन्हित पूर्णांक clk_little_max;	/* Maximum घड़ी frequency (Little) */

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, physical_cluster);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cpu_last_req_freq);

अटल काष्ठा mutex cluster_lock[MAX_CLUSTERS];

अटल अंतरभूत पूर्णांक raw_cpu_to_cluster(पूर्णांक cpu)
अणु
	वापस topology_physical_package_id(cpu);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_to_cluster(पूर्णांक cpu)
अणु
	वापस is_bL_चयनing_enabled() ?
		MAX_CLUSTERS : raw_cpu_to_cluster(cpu);
पूर्ण

अटल अचिन्हित पूर्णांक find_cluster_maxfreq(पूर्णांक cluster)
अणु
	पूर्णांक j;
	u32 max_freq = 0, cpu_freq;

	क्रम_each_online_cpu(j) अणु
		cpu_freq = per_cpu(cpu_last_req_freq, j);

		अगर (cluster == per_cpu(physical_cluster, j) &&
		    max_freq < cpu_freq)
			max_freq = cpu_freq;
	पूर्ण

	वापस max_freq;
पूर्ण

अटल अचिन्हित पूर्णांक clk_get_cpu_rate(अचिन्हित पूर्णांक cpu)
अणु
	u32 cur_cluster = per_cpu(physical_cluster, cpu);
	u32 rate = clk_get_rate(clk[cur_cluster]) / 1000;

	/* For चयनer we use भव A7 घड़ी rates */
	अगर (is_bL_चयनing_enabled())
		rate = VIRT_FREQ(cur_cluster, rate);

	वापस rate;
पूर्ण

अटल अचिन्हित पूर्णांक ve_spc_cpufreq_get_rate(अचिन्हित पूर्णांक cpu)
अणु
	अगर (is_bL_चयनing_enabled())
		वापस per_cpu(cpu_last_req_freq, cpu);
	अन्यथा
		वापस clk_get_cpu_rate(cpu);
पूर्ण

अटल अचिन्हित पूर्णांक
ve_spc_cpufreq_set_rate(u32 cpu, u32 old_cluster, u32 new_cluster, u32 rate)
अणु
	u32 new_rate, prev_rate;
	पूर्णांक ret;
	bool bLs = is_bL_चयनing_enabled();

	mutex_lock(&cluster_lock[new_cluster]);

	अगर (bLs) अणु
		prev_rate = per_cpu(cpu_last_req_freq, cpu);
		per_cpu(cpu_last_req_freq, cpu) = rate;
		per_cpu(physical_cluster, cpu) = new_cluster;

		new_rate = find_cluster_maxfreq(new_cluster);
		new_rate = ACTUAL_FREQ(new_cluster, new_rate);
	पूर्ण अन्यथा अणु
		new_rate = rate;
	पूर्ण

	ret = clk_set_rate(clk[new_cluster], new_rate * 1000);
	अगर (!ret) अणु
		/*
		 * FIXME: clk_set_rate hasn't वापसed an error here however it
		 * may be that clk_change_rate failed due to hardware or
		 * firmware issues and wasn't able to report that due to the
		 * current design of the clk core layer. To work around this
		 * problem we will पढ़ो back the घड़ी rate and check it is
		 * correct. This needs to be हटाओd once clk core is fixed.
		 */
		अगर (clk_get_rate(clk[new_cluster]) != new_rate * 1000)
			ret = -EIO;
	पूर्ण

	अगर (WARN_ON(ret)) अणु
		अगर (bLs) अणु
			per_cpu(cpu_last_req_freq, cpu) = prev_rate;
			per_cpu(physical_cluster, cpu) = old_cluster;
		पूर्ण

		mutex_unlock(&cluster_lock[new_cluster]);

		वापस ret;
	पूर्ण

	mutex_unlock(&cluster_lock[new_cluster]);

	/* Recalc freq क्रम old cluster when चयनing clusters */
	अगर (old_cluster != new_cluster) अणु
		/* Switch cluster */
		bL_चयन_request(cpu, new_cluster);

		mutex_lock(&cluster_lock[old_cluster]);

		/* Set freq of old cluster अगर there are cpus left on it */
		new_rate = find_cluster_maxfreq(old_cluster);
		new_rate = ACTUAL_FREQ(old_cluster, new_rate);

		अगर (new_rate &&
		    clk_set_rate(clk[old_cluster], new_rate * 1000)) अणु
			pr_err("%s: clk_set_rate failed: %d, old cluster: %d\n",
			       __func__, ret, old_cluster);
		पूर्ण
		mutex_unlock(&cluster_lock[old_cluster]);
	पूर्ण

	वापस 0;
पूर्ण

/* Set घड़ी frequency */
अटल पूर्णांक ve_spc_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				     अचिन्हित पूर्णांक index)
अणु
	u32 cpu = policy->cpu, cur_cluster, new_cluster, actual_cluster;
	अचिन्हित पूर्णांक freqs_new;

	cur_cluster = cpu_to_cluster(cpu);
	new_cluster = actual_cluster = per_cpu(physical_cluster, cpu);

	freqs_new = freq_table[cur_cluster][index].frequency;

	अगर (is_bL_चयनing_enabled()) अणु
		अगर (actual_cluster == A15_CLUSTER && freqs_new < clk_big_min)
			new_cluster = A7_CLUSTER;
		अन्यथा अगर (actual_cluster == A7_CLUSTER &&
			 freqs_new > clk_little_max)
			new_cluster = A15_CLUSTER;
	पूर्ण

	वापस ve_spc_cpufreq_set_rate(cpu, actual_cluster, new_cluster,
				       freqs_new);
पूर्ण

अटल अंतरभूत u32 get_table_count(काष्ठा cpufreq_frequency_table *table)
अणु
	पूर्णांक count;

	क्रम (count = 0; table[count].frequency != CPUFREQ_TABLE_END; count++)
		;

	वापस count;
पूर्ण

/* get the minimum frequency in the cpufreq_frequency_table */
अटल अंतरभूत u32 get_table_min(काष्ठा cpufreq_frequency_table *table)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	u32 min_freq = ~0;

	cpufreq_क्रम_each_entry(pos, table)
		अगर (pos->frequency < min_freq)
			min_freq = pos->frequency;
	वापस min_freq;
पूर्ण

/* get the maximum frequency in the cpufreq_frequency_table */
अटल अंतरभूत u32 get_table_max(काष्ठा cpufreq_frequency_table *table)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	u32 max_freq = 0;

	cpufreq_क्रम_each_entry(pos, table)
		अगर (pos->frequency > max_freq)
			max_freq = pos->frequency;
	वापस max_freq;
पूर्ण

अटल bool search_frequency(काष्ठा cpufreq_frequency_table *table, पूर्णांक size,
			     अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < size; count++) अणु
		अगर (table[count].frequency == freq)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक merge_cluster_tables(व्योम)
अणु
	पूर्णांक i, j, k = 0, count = 1;
	काष्ठा cpufreq_frequency_table *table;

	क्रम (i = 0; i < MAX_CLUSTERS; i++)
		count += get_table_count(freq_table[i]);

	table = kसुस्मृति(count, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	freq_table[MAX_CLUSTERS] = table;

	/* Add in reverse order to get freqs in increasing order */
	क्रम (i = MAX_CLUSTERS - 1; i >= 0; i--, count = k) अणु
		क्रम (j = 0; freq_table[i][j].frequency != CPUFREQ_TABLE_END;
		     j++) अणु
			अगर (i == A15_CLUSTER &&
			    search_frequency(table, count, freq_table[i][j].frequency))
				जारी; /* skip duplicates */
			table[k++].frequency =
				VIRT_FREQ(i, freq_table[i][j].frequency);
		पूर्ण
	पूर्ण

	table[k].driver_data = k;
	table[k].frequency = CPUFREQ_TABLE_END;

	वापस 0;
पूर्ण

अटल व्योम _put_cluster_clk_and_freq_table(काष्ठा device *cpu_dev,
					    स्थिर काष्ठा cpumask *cpumask)
अणु
	u32 cluster = raw_cpu_to_cluster(cpu_dev->id);

	अगर (!freq_table[cluster])
		वापस;

	clk_put(clk[cluster]);
	dev_pm_opp_मुक्त_cpufreq_table(cpu_dev, &freq_table[cluster]);
पूर्ण

अटल व्योम put_cluster_clk_and_freq_table(काष्ठा device *cpu_dev,
					   स्थिर काष्ठा cpumask *cpumask)
अणु
	u32 cluster = cpu_to_cluster(cpu_dev->id);
	पूर्णांक i;

	अगर (atomic_dec_वापस(&cluster_usage[cluster]))
		वापस;

	अगर (cluster < MAX_CLUSTERS)
		वापस _put_cluster_clk_and_freq_table(cpu_dev, cpumask);

	क्रम_each_present_cpu(i) अणु
		काष्ठा device *cdev = get_cpu_device(i);

		अगर (!cdev)
			वापस;

		_put_cluster_clk_and_freq_table(cdev, cpumask);
	पूर्ण

	/* मुक्त भव table */
	kमुक्त(freq_table[cluster]);
पूर्ण

अटल पूर्णांक _get_cluster_clk_and_freq_table(काष्ठा device *cpu_dev,
					   स्थिर काष्ठा cpumask *cpumask)
अणु
	u32 cluster = raw_cpu_to_cluster(cpu_dev->id);
	पूर्णांक ret;

	अगर (freq_table[cluster])
		वापस 0;

	/*
	 * platक्रमm specअगरic SPC code must initialise the opp table
	 * so just check अगर the OPP count is non-zero
	 */
	ret = dev_pm_opp_get_opp_count(cpu_dev) <= 0;
	अगर (ret)
		जाओ out;

	ret = dev_pm_opp_init_cpufreq_table(cpu_dev, &freq_table[cluster]);
	अगर (ret)
		जाओ out;

	clk[cluster] = clk_get(cpu_dev, शून्य);
	अगर (!IS_ERR(clk[cluster]))
		वापस 0;

	dev_err(cpu_dev, "%s: Failed to get clk for cpu: %d, cluster: %d\n",
		__func__, cpu_dev->id, cluster);
	ret = PTR_ERR(clk[cluster]);
	dev_pm_opp_मुक्त_cpufreq_table(cpu_dev, &freq_table[cluster]);

out:
	dev_err(cpu_dev, "%s: Failed to get data for cluster: %d\n", __func__,
		cluster);
	वापस ret;
पूर्ण

अटल पूर्णांक get_cluster_clk_and_freq_table(काष्ठा device *cpu_dev,
					  स्थिर काष्ठा cpumask *cpumask)
अणु
	u32 cluster = cpu_to_cluster(cpu_dev->id);
	पूर्णांक i, ret;

	अगर (atomic_inc_वापस(&cluster_usage[cluster]) != 1)
		वापस 0;

	अगर (cluster < MAX_CLUSTERS) अणु
		ret = _get_cluster_clk_and_freq_table(cpu_dev, cpumask);
		अगर (ret)
			atomic_dec(&cluster_usage[cluster]);
		वापस ret;
	पूर्ण

	/*
	 * Get data क्रम all clusters and fill भव cluster with a merge of
	 * both
	 */
	क्रम_each_present_cpu(i) अणु
		काष्ठा device *cdev = get_cpu_device(i);

		अगर (!cdev)
			वापस -ENODEV;

		ret = _get_cluster_clk_and_freq_table(cdev, cpumask);
		अगर (ret)
			जाओ put_clusters;
	पूर्ण

	ret = merge_cluster_tables();
	अगर (ret)
		जाओ put_clusters;

	/* Assuming 2 cluster, set clk_big_min and clk_little_max */
	clk_big_min = get_table_min(freq_table[A15_CLUSTER]);
	clk_little_max = VIRT_FREQ(A7_CLUSTER,
				   get_table_max(freq_table[A7_CLUSTER]));

	वापस 0;

put_clusters:
	क्रम_each_present_cpu(i) अणु
		काष्ठा device *cdev = get_cpu_device(i);

		अगर (!cdev)
			वापस -ENODEV;

		_put_cluster_clk_and_freq_table(cdev, cpumask);
	पूर्ण

	atomic_dec(&cluster_usage[cluster]);

	वापस ret;
पूर्ण

/* Per-CPU initialization */
अटल पूर्णांक ve_spc_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	u32 cur_cluster = cpu_to_cluster(policy->cpu);
	काष्ठा device *cpu_dev;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(policy->cpu);
	अगर (!cpu_dev) अणु
		pr_err("%s: failed to get cpu%d device\n", __func__,
		       policy->cpu);
		वापस -ENODEV;
	पूर्ण

	अगर (cur_cluster < MAX_CLUSTERS) अणु
		पूर्णांक cpu;

		dev_pm_opp_get_sharing_cpus(cpu_dev, policy->cpus);

		क्रम_each_cpu(cpu, policy->cpus)
			per_cpu(physical_cluster, cpu) = cur_cluster;
	पूर्ण अन्यथा अणु
		/* Assumption: during init, we are always running on A15 */
		per_cpu(physical_cluster, policy->cpu) = A15_CLUSTER;
	पूर्ण

	ret = get_cluster_clk_and_freq_table(cpu_dev, policy->cpus);
	अगर (ret)
		वापस ret;

	policy->freq_table = freq_table[cur_cluster];
	policy->cpuinfo.transition_latency = 1000000; /* 1 ms */

	dev_pm_opp_of_रेजिस्टर_em(cpu_dev, policy->cpus);

	अगर (is_bL_चयनing_enabled())
		per_cpu(cpu_last_req_freq, policy->cpu) =
						clk_get_cpu_rate(policy->cpu);

	dev_info(cpu_dev, "%s: CPU %d initialized\n", __func__, policy->cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक ve_spc_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device *cpu_dev;
	पूर्णांक cur_cluster = cpu_to_cluster(policy->cpu);

	अगर (cur_cluster < MAX_CLUSTERS) अणु
		cpufreq_cooling_unरेजिस्टर(cdev[cur_cluster]);
		cdev[cur_cluster] = शून्य;
	पूर्ण

	cpu_dev = get_cpu_device(policy->cpu);
	अगर (!cpu_dev) अणु
		pr_err("%s: failed to get cpu%d device\n", __func__,
		       policy->cpu);
		वापस -ENODEV;
	पूर्ण

	put_cluster_clk_and_freq_table(cpu_dev, policy->related_cpus);
	वापस 0;
पूर्ण

अटल व्योम ve_spc_cpufreq_पढ़ोy(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक cur_cluster = cpu_to_cluster(policy->cpu);

	/* Do not रेजिस्टर a cpu_cooling device अगर we are in IKS mode */
	अगर (cur_cluster >= MAX_CLUSTERS)
		वापस;

	cdev[cur_cluster] = of_cpufreq_cooling_रेजिस्टर(policy);
पूर्ण

अटल काष्ठा cpufreq_driver ve_spc_cpufreq_driver = अणु
	.name			= "vexpress-spc",
	.flags			= CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
					CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy			= cpufreq_generic_frequency_table_verअगरy,
	.target_index		= ve_spc_cpufreq_set_target,
	.get			= ve_spc_cpufreq_get_rate,
	.init			= ve_spc_cpufreq_init,
	.निकास			= ve_spc_cpufreq_निकास,
	.पढ़ोy			= ve_spc_cpufreq_पढ़ोy,
	.attr			= cpufreq_generic_attr,
पूर्ण;

#अगर_घोषित CONFIG_BL_SWITCHER
अटल पूर्णांक bL_cpufreq_चयनer_notअगरier(काष्ठा notअगरier_block *nfb,
					अचिन्हित दीर्घ action, व्योम *_arg)
अणु
	pr_debug("%s: action: %ld\n", __func__, action);

	चयन (action) अणु
	हाल BL_NOTIFY_PRE_ENABLE:
	हाल BL_NOTIFY_PRE_DISABLE:
		cpufreq_unरेजिस्टर_driver(&ve_spc_cpufreq_driver);
		अवरोध;

	हाल BL_NOTIFY_POST_ENABLE:
		set_चयनing_enabled(true);
		cpufreq_रेजिस्टर_driver(&ve_spc_cpufreq_driver);
		अवरोध;

	हाल BL_NOTIFY_POST_DISABLE:
		set_चयनing_enabled(false);
		cpufreq_रेजिस्टर_driver(&ve_spc_cpufreq_driver);
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block bL_चयनer_notअगरier = अणु
	.notअगरier_call = bL_cpufreq_चयनer_notअगरier,
पूर्ण;

अटल पूर्णांक __bLs_रेजिस्टर_notअगरier(व्योम)
अणु
	वापस bL_चयनer_रेजिस्टर_notअगरier(&bL_चयनer_notअगरier);
पूर्ण

अटल पूर्णांक __bLs_unरेजिस्टर_notअगरier(व्योम)
अणु
	वापस bL_चयनer_unरेजिस्टर_notअगरier(&bL_चयनer_notअगरier);
पूर्ण
#अन्यथा
अटल पूर्णांक __bLs_रेजिस्टर_notअगरier(व्योम) अणु वापस 0; पूर्ण
अटल पूर्णांक __bLs_unरेजिस्टर_notअगरier(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ve_spc_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i;

	set_चयनing_enabled(bL_चयनer_get_enabled());

	क्रम (i = 0; i < MAX_CLUSTERS; i++)
		mutex_init(&cluster_lock[i]);

	ret = cpufreq_रेजिस्टर_driver(&ve_spc_cpufreq_driver);
	अगर (ret) अणु
		pr_info("%s: Failed registering platform driver: %s, err: %d\n",
			__func__, ve_spc_cpufreq_driver.name, ret);
	पूर्ण अन्यथा अणु
		ret = __bLs_रेजिस्टर_notअगरier();
		अगर (ret)
			cpufreq_unरेजिस्टर_driver(&ve_spc_cpufreq_driver);
		अन्यथा
			pr_info("%s: Registered platform driver: %s\n",
				__func__, ve_spc_cpufreq_driver.name);
	पूर्ण

	bL_चयनer_put_enabled();
	वापस ret;
पूर्ण

अटल पूर्णांक ve_spc_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	bL_चयनer_get_enabled();
	__bLs_unरेजिस्टर_notअगरier();
	cpufreq_unरेजिस्टर_driver(&ve_spc_cpufreq_driver);
	bL_चयनer_put_enabled();
	pr_info("%s: Un-registered platform driver: %s\n", __func__,
		ve_spc_cpufreq_driver.name);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ve_spc_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "vexpress-spc-cpufreq",
	पूर्ण,
	.probe		= ve_spc_cpufreq_probe,
	.हटाओ		= ve_spc_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(ve_spc_cpufreq_platdrv);

MODULE_ALIAS("platform:vexpress-spc-cpufreq");
MODULE_AUTHOR("Viresh Kumar <viresh.kumar@linaro.org>");
MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("Vexpress SPC ARM big LITTLE cpufreq driver");
MODULE_LICENSE("GPL v2");
