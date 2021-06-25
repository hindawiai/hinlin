<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved
 */

#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/smp_plat.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

#घोषणा KHZ                     1000
#घोषणा REF_CLK_MHZ             408 /* 408 MHz */
#घोषणा US_DELAY                500
#घोषणा CPUFREQ_TBL_STEP_HZ     (50 * KHZ * KHZ)
#घोषणा MAX_CNT                 ~0U

/* cpufreq transisition latency */
#घोषणा TEGRA_CPUFREQ_TRANSITION_LATENCY (300 * 1000) /* unit in nanoseconds */

क्रमागत cluster अणु
	CLUSTER0,
	CLUSTER1,
	CLUSTER2,
	CLUSTER3,
	MAX_CLUSTERS,
पूर्ण;

काष्ठा tegra194_cpufreq_data अणु
	व्योम __iomem *regs;
	माप_प्रकार num_clusters;
	काष्ठा cpufreq_frequency_table **tables;
पूर्ण;

काष्ठा tegra_cpu_ctr अणु
	u32 cpu;
	u32 coreclk_cnt, last_coreclk_cnt;
	u32 refclk_cnt, last_refclk_cnt;
पूर्ण;

काष्ठा पढ़ो_counters_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा tegra_cpu_ctr c;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *पढ़ो_counters_wq;

अटल व्योम get_cpu_cluster(व्योम *cluster)
अणु
	u64 mpidr = पढ़ो_cpuid_mpidr() & MPIDR_HWID_BITMASK;

	*((uपूर्णांक32_t *)cluster) = MPIDR_AFFINITY_LEVEL(mpidr, 1);
पूर्ण

/*
 * Read per-core Read-only प्रणाली रेजिस्टर NVFREQ_FEEDBACK_EL1.
 * The रेजिस्टर provides frequency feedback inक्रमmation to
 * determine the average actual frequency a core has run at over
 * a period of समय.
 *	[31:0] PLLP counter: Counts at fixed frequency (408 MHz)
 *	[63:32] Core घड़ी counter: counts on every core घड़ी cycle
 *			where the core is architecturally घड़ीing
 */
अटल u64 पढ़ो_freq_feedback(व्योम)
अणु
	u64 val = 0;

	यंत्र अस्थिर("mrs %0, s3_0_c15_c0_5" : "=r" (val) : );

	वापस val;
पूर्ण

अटल अंतरभूत u32 map_nभाग_प्रकारo_freq(काष्ठा mrq_cpu_nभाग_limits_response
				   *nltbl, u16 nभाग)
अणु
	वापस nltbl->ref_clk_hz / KHZ * nभाग / (nltbl->pभाग * nltbl->mभाग);
पूर्ण

अटल व्योम tegra_पढ़ो_counters(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पढ़ो_counters_work *पढ़ो_counters_work;
	काष्ठा tegra_cpu_ctr *c;
	u64 val;

	/*
	 * ref_clk_counter(32 bit counter) runs on स्थिरant clk,
	 * pll_p(408MHz).
	 * It will take = 2 ^ 32 / 408 MHz to overflow ref clk counter
	 *              = 10526880 usec = 10.527 sec to overflow
	 *
	 * Like wise core_clk_counter(32 bit counter) runs on core घड़ी.
	 * It's synchronized to crab_clk (cpu_crab_clk) which runs at
	 * freq of cluster. Assuming max cluster घड़ी ~2000MHz,
	 * It will take = 2 ^ 32 / 2000 MHz to overflow core clk counter
	 *              = ~2.147 sec to overflow
	 */
	पढ़ो_counters_work = container_of(work, काष्ठा पढ़ो_counters_work,
					  work);
	c = &पढ़ो_counters_work->c;

	val = पढ़ो_freq_feedback();
	c->last_refclk_cnt = lower_32_bits(val);
	c->last_coreclk_cnt = upper_32_bits(val);
	udelay(US_DELAY);
	val = पढ़ो_freq_feedback();
	c->refclk_cnt = lower_32_bits(val);
	c->coreclk_cnt = upper_32_bits(val);
पूर्ण

/*
 * Return instantaneous cpu speed
 * Instantaneous freq is calculated as -
 * -Takes sample on every query of getting the freq.
 *	- Read core and ref घड़ी counters;
 *	- Delay क्रम X us
 *	- Read above cycle counters again
 *	- Calculates freq by subtracting current and previous counters
 *	  भागided by the delay समय or eqv. of ref_clk_counter in delta समय
 *	- Return Kcycles/second, freq in KHz
 *
 *	delta समय period = x sec
 *			  = delta ref_clk_counter / (408 * 10^6) sec
 *	freq in Hz = cycles/sec
 *		   = (delta cycles / x sec
 *		   = (delta cycles * 408 * 10^6) / delta ref_clk_counter
 *	in KHz	   = (delta cycles * 408 * 10^3) / delta ref_clk_counter
 *
 * @cpu - logical cpu whose freq to be updated
 * Returns freq in KHz on success, 0 अगर cpu is offline
 */
अटल अचिन्हित पूर्णांक tegra194_calculate_speed(u32 cpu)
अणु
	काष्ठा पढ़ो_counters_work पढ़ो_counters_work;
	काष्ठा tegra_cpu_ctr c;
	u32 delta_refcnt;
	u32 delta_ccnt;
	u32 rate_mhz;

	/*
	 * udelay() is required to reस्थिरruct cpu frequency over an
	 * observation winकरोw. Using workqueue to call udelay() with
	 * पूर्णांकerrupts enabled.
	 */
	पढ़ो_counters_work.c.cpu = cpu;
	INIT_WORK_ONSTACK(&पढ़ो_counters_work.work, tegra_पढ़ो_counters);
	queue_work_on(cpu, पढ़ो_counters_wq, &पढ़ो_counters_work.work);
	flush_work(&पढ़ो_counters_work.work);
	c = पढ़ो_counters_work.c;

	अगर (c.coreclk_cnt < c.last_coreclk_cnt)
		delta_ccnt = c.coreclk_cnt + (MAX_CNT - c.last_coreclk_cnt);
	अन्यथा
		delta_ccnt = c.coreclk_cnt - c.last_coreclk_cnt;
	अगर (!delta_ccnt)
		वापस 0;

	/* ref घड़ी is 32 bits */
	अगर (c.refclk_cnt < c.last_refclk_cnt)
		delta_refcnt = c.refclk_cnt + (MAX_CNT - c.last_refclk_cnt);
	अन्यथा
		delta_refcnt = c.refclk_cnt - c.last_refclk_cnt;
	अगर (!delta_refcnt) अणु
		pr_debug("cpufreq: %d is idle, delta_refcnt: 0\n", cpu);
		वापस 0;
	पूर्ण
	rate_mhz = ((अचिन्हित दीर्घ)(delta_ccnt * REF_CLK_MHZ)) / delta_refcnt;

	वापस (rate_mhz * KHZ); /* in KHz */
पूर्ण

अटल व्योम get_cpu_nभाग(व्योम *nभाग)
अणु
	u64 nभाग_val;

	यंत्र अस्थिर("mrs %0, s3_0_c15_c0_4" : "=r" (nभाग_val) : );

	*(u64 *)nभाग = nभाग_val;
पूर्ण

अटल व्योम set_cpu_nभाग(व्योम *data)
अणु
	काष्ठा cpufreq_frequency_table *tbl = data;
	u64 nभाग_val = (u64)tbl->driver_data;

	यंत्र अस्थिर("msr s3_0_c15_c0_4, %0" : : "r" (nभाग_val));
पूर्ण

अटल अचिन्हित पूर्णांक tegra194_get_speed(u32 cpu)
अणु
	काष्ठा tegra194_cpufreq_data *data = cpufreq_get_driver_data();
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक rate;
	u64 nभाग;
	पूर्णांक ret;
	u32 cl;

	smp_call_function_single(cpu, get_cpu_cluster, &cl, true);

	/* reस्थिरruct actual cpu freq using counters */
	rate = tegra194_calculate_speed(cpu);

	/* get last written nभाग value */
	ret = smp_call_function_single(cpu, get_cpu_nभाग, &nभाग, true);
	अगर (WARN_ON_ONCE(ret))
		वापस rate;

	/*
	 * If the reस्थिरructed frequency has acceptable delta from
	 * the last written value, then वापस freq corresponding
	 * to the last written nभाग value from freq_table. This is
	 * करोne to वापस consistent value.
	 */
	cpufreq_क्रम_each_valid_entry(pos, data->tables[cl]) अणु
		अगर (pos->driver_data != nभाग)
			जारी;

		अगर (असल(pos->frequency - rate) > 115200) अणु
			pr_warn("cpufreq: cpu%d,cur:%u,set:%u,set ndiv:%llu\n",
				cpu, rate, pos->frequency, nभाग);
		पूर्ण अन्यथा अणु
			rate = pos->frequency;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस rate;
पूर्ण

अटल पूर्णांक tegra194_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा tegra194_cpufreq_data *data = cpufreq_get_driver_data();
	u32 cpu;
	u32 cl;

	smp_call_function_single(policy->cpu, get_cpu_cluster, &cl, true);

	अगर (cl >= data->num_clusters)
		वापस -EINVAL;

	/* set same policy क्रम all cpus in a cluster */
	क्रम (cpu = (cl * 2); cpu < ((cl + 1) * 2); cpu++)
		cpumask_set_cpu(cpu, policy->cpus);

	policy->freq_table = data->tables[cl];
	policy->cpuinfo.transition_latency = TEGRA_CPUFREQ_TRANSITION_LATENCY;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra194_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				       अचिन्हित पूर्णांक index)
अणु
	काष्ठा cpufreq_frequency_table *tbl = policy->freq_table + index;

	/*
	 * Each core ग_लिखोs frequency in per core रेजिस्टर. Then both cores
	 * in a cluster run at same frequency which is the maximum frequency
	 * request out of the values requested by both cores in that cluster.
	 */
	on_each_cpu_mask(policy->cpus, set_cpu_nभाग, tbl, true);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver tegra194_cpufreq_driver = अणु
	.name = "tegra194",
	.flags = CPUFREQ_CONST_LOOPS | CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = tegra194_cpufreq_set_target,
	.get = tegra194_get_speed,
	.init = tegra194_cpufreq_init,
	.attr = cpufreq_generic_attr,
पूर्ण;

अटल व्योम tegra194_cpufreq_मुक्त_resources(व्योम)
अणु
	destroy_workqueue(पढ़ो_counters_wq);
पूर्ण

अटल काष्ठा cpufreq_frequency_table *
init_freq_table(काष्ठा platक्रमm_device *pdev, काष्ठा tegra_bpmp *bpmp,
		अचिन्हित पूर्णांक cluster_id)
अणु
	काष्ठा cpufreq_frequency_table *freq_table;
	काष्ठा mrq_cpu_nभाग_limits_response resp;
	अचिन्हित पूर्णांक num_freqs, nभाग, delta_nभाग;
	काष्ठा mrq_cpu_nभाग_limits_request req;
	काष्ठा tegra_bpmp_message msg;
	u16 freq_table_step_size;
	पूर्णांक err, index;

	स_रखो(&req, 0, माप(req));
	req.cluster_id = cluster_id;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_CPU_NDIV_LIMITS;
	msg.tx.data = &req;
	msg.tx.size = माप(req);
	msg.rx.data = &resp;
	msg.rx.size = माप(resp);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err)
		वापस ERR_PTR(err);

	/*
	 * Make sure frequency table step is a multiple of mभाग to match
	 * vhपूर्णांक table granularity.
	 */
	freq_table_step_size = resp.mभाग *
			DIV_ROUND_UP(CPUFREQ_TBL_STEP_HZ, resp.ref_clk_hz);

	dev_dbg(&pdev->dev, "cluster %d: frequency table step size: %d\n",
		cluster_id, freq_table_step_size);

	delta_nभाग = resp.nभाग_max - resp.nभाग_min;

	अगर (unlikely(delta_nभाग == 0)) अणु
		num_freqs = 1;
	पूर्ण अन्यथा अणु
		/* We store both nभाग_min and nभाग_max hence the +1 */
		num_freqs = delta_nभाग / freq_table_step_size + 1;
	पूर्ण

	num_freqs += (delta_nभाग % freq_table_step_size) ? 1 : 0;

	freq_table = devm_kसुस्मृति(&pdev->dev, num_freqs + 1,
				  माप(*freq_table), GFP_KERNEL);
	अगर (!freq_table)
		वापस ERR_PTR(-ENOMEM);

	क्रम (index = 0, nभाग = resp.nभाग_min;
			nभाग < resp.nभाग_max;
			index++, nभाग += freq_table_step_size) अणु
		freq_table[index].driver_data = nभाग;
		freq_table[index].frequency = map_nभाग_प्रकारo_freq(&resp, nभाग);
	पूर्ण

	freq_table[index].driver_data = resp.nभाग_max;
	freq_table[index++].frequency = map_nभाग_प्रकारo_freq(&resp, resp.nभाग_max);
	freq_table[index].frequency = CPUFREQ_TABLE_END;

	वापस freq_table;
पूर्ण

अटल पूर्णांक tegra194_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra194_cpufreq_data *data;
	काष्ठा tegra_bpmp *bpmp;
	पूर्णांक err, i;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->num_clusters = MAX_CLUSTERS;
	data->tables = devm_kसुस्मृति(&pdev->dev, data->num_clusters,
				    माप(*data->tables), GFP_KERNEL);
	अगर (!data->tables)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);

	bpmp = tegra_bpmp_get(&pdev->dev);
	अगर (IS_ERR(bpmp))
		वापस PTR_ERR(bpmp);

	पढ़ो_counters_wq = alloc_workqueue("read_counters_wq", __WQ_LEGACY, 1);
	अगर (!पढ़ो_counters_wq) अणु
		dev_err(&pdev->dev, "fail to create_workqueue\n");
		err = -EINVAL;
		जाओ put_bpmp;
	पूर्ण

	क्रम (i = 0; i < data->num_clusters; i++) अणु
		data->tables[i] = init_freq_table(pdev, bpmp, i);
		अगर (IS_ERR(data->tables[i])) अणु
			err = PTR_ERR(data->tables[i]);
			जाओ err_मुक्त_res;
		पूर्ण
	पूर्ण

	tegra194_cpufreq_driver.driver_data = data;

	err = cpufreq_रेजिस्टर_driver(&tegra194_cpufreq_driver);
	अगर (!err)
		जाओ put_bpmp;

err_मुक्त_res:
	tegra194_cpufreq_मुक्त_resources();
put_bpmp:
	tegra_bpmp_put(bpmp);
	वापस err;
पूर्ण

अटल पूर्णांक tegra194_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&tegra194_cpufreq_driver);
	tegra194_cpufreq_मुक्त_resources();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra194_cpufreq_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-ccplex", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra194_cpufreq_of_match);

अटल काष्ठा platक्रमm_driver tegra194_ccplex_driver = अणु
	.driver = अणु
		.name = "tegra194-cpufreq",
		.of_match_table = tegra194_cpufreq_of_match,
	पूर्ण,
	.probe = tegra194_cpufreq_probe,
	.हटाओ = tegra194_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra194_ccplex_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_AUTHOR("Sumit Gupta <sumitg@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra194 cpufreq driver");
MODULE_LICENSE("GPL v2");
