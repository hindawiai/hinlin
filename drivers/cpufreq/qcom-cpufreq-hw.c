<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>

#घोषणा LUT_MAX_ENTRIES			40U
#घोषणा LUT_SRC				GENMASK(31, 30)
#घोषणा LUT_L_VAL			GENMASK(7, 0)
#घोषणा LUT_CORE_COUNT			GENMASK(18, 16)
#घोषणा LUT_VOLT			GENMASK(11, 0)
#घोषणा CLK_HW_DIV			2
#घोषणा LUT_TURBO_IND			1

काष्ठा qcom_cpufreq_soc_data अणु
	u32 reg_enable;
	u32 reg_freq_lut;
	u32 reg_volt_lut;
	u32 reg_perf_state;
	u8 lut_row_size;
पूर्ण;

काष्ठा qcom_cpufreq_data अणु
	व्योम __iomem *base;
	काष्ठा resource *res;
	स्थिर काष्ठा qcom_cpufreq_soc_data *soc_data;
पूर्ण;

अटल अचिन्हित दीर्घ cpu_hw_rate, xo_rate;
अटल bool icc_scaling_enabled;

अटल पूर्णांक qcom_cpufreq_set_bw(काष्ठा cpufreq_policy *policy,
			       अचिन्हित दीर्घ freq_khz)
अणु
	अचिन्हित दीर्घ freq_hz = freq_khz * 1000;
	काष्ठा dev_pm_opp *opp;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = get_cpu_device(policy->cpu);
	अगर (!dev)
		वापस -ENODEV;

	opp = dev_pm_opp_find_freq_exact(dev, freq_hz, true);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	ret = dev_pm_opp_set_opp(dev, opp);
	dev_pm_opp_put(opp);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_cpufreq_update_opp(काष्ठा device *cpu_dev,
				   अचिन्हित दीर्घ freq_khz,
				   अचिन्हित दीर्घ volt)
अणु
	अचिन्हित दीर्घ freq_hz = freq_khz * 1000;
	पूर्णांक ret;

	/* Skip voltage update अगर the opp table is not available */
	अगर (!icc_scaling_enabled)
		वापस dev_pm_opp_add(cpu_dev, freq_hz, volt);

	ret = dev_pm_opp_adjust_voltage(cpu_dev, freq_hz, volt, volt, volt);
	अगर (ret) अणु
		dev_err(cpu_dev, "Voltage update failed freq=%ld\n", freq_khz);
		वापस ret;
	पूर्ण

	वापस dev_pm_opp_enable(cpu_dev, freq_hz);
पूर्ण

अटल पूर्णांक qcom_cpufreq_hw_target_index(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक index)
अणु
	काष्ठा qcom_cpufreq_data *data = policy->driver_data;
	स्थिर काष्ठा qcom_cpufreq_soc_data *soc_data = data->soc_data;
	अचिन्हित दीर्घ freq = policy->freq_table[index].frequency;

	ग_लिखोl_relaxed(index, data->base + soc_data->reg_perf_state);

	अगर (icc_scaling_enabled)
		qcom_cpufreq_set_bw(policy, freq);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qcom_cpufreq_hw_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qcom_cpufreq_data *data;
	स्थिर काष्ठा qcom_cpufreq_soc_data *soc_data;
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक index;

	policy = cpufreq_cpu_get_raw(cpu);
	अगर (!policy)
		वापस 0;

	data = policy->driver_data;
	soc_data = data->soc_data;

	index = पढ़ोl_relaxed(data->base + soc_data->reg_perf_state);
	index = min(index, LUT_MAX_ENTRIES - 1);

	वापस policy->freq_table[index].frequency;
पूर्ण

अटल अचिन्हित पूर्णांक qcom_cpufreq_hw_fast_चयन(काष्ठा cpufreq_policy *policy,
						अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा qcom_cpufreq_data *data = policy->driver_data;
	स्थिर काष्ठा qcom_cpufreq_soc_data *soc_data = data->soc_data;
	अचिन्हित पूर्णांक index;

	index = policy->cached_resolved_idx;
	ग_लिखोl_relaxed(index, data->base + soc_data->reg_perf_state);

	वापस policy->freq_table[index].frequency;
पूर्ण

अटल पूर्णांक qcom_cpufreq_hw_पढ़ो_lut(काष्ठा device *cpu_dev,
				    काष्ठा cpufreq_policy *policy)
अणु
	u32 data, src, lval, i, core_count, prev_freq = 0, freq;
	u32 volt;
	काष्ठा cpufreq_frequency_table	*table;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;
	काष्ठा qcom_cpufreq_data *drv_data = policy->driver_data;
	स्थिर काष्ठा qcom_cpufreq_soc_data *soc_data = drv_data->soc_data;

	table = kसुस्मृति(LUT_MAX_ENTRIES + 1, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	ret = dev_pm_opp_of_add_table(cpu_dev);
	अगर (!ret) अणु
		/* Disable all opps and cross-validate against LUT later */
		icc_scaling_enabled = true;
		क्रम (rate = 0; ; rate++) अणु
			opp = dev_pm_opp_find_freq_उच्चमान(cpu_dev, &rate);
			अगर (IS_ERR(opp))
				अवरोध;

			dev_pm_opp_put(opp);
			dev_pm_opp_disable(cpu_dev, rate);
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		dev_err(cpu_dev, "Invalid opp table in device tree\n");
		वापस ret;
	पूर्ण अन्यथा अणु
		policy->fast_चयन_possible = true;
		icc_scaling_enabled = false;
	पूर्ण

	क्रम (i = 0; i < LUT_MAX_ENTRIES; i++) अणु
		data = पढ़ोl_relaxed(drv_data->base + soc_data->reg_freq_lut +
				      i * soc_data->lut_row_size);
		src = FIELD_GET(LUT_SRC, data);
		lval = FIELD_GET(LUT_L_VAL, data);
		core_count = FIELD_GET(LUT_CORE_COUNT, data);

		data = पढ़ोl_relaxed(drv_data->base + soc_data->reg_volt_lut +
				      i * soc_data->lut_row_size);
		volt = FIELD_GET(LUT_VOLT, data) * 1000;

		अगर (src)
			freq = xo_rate * lval / 1000;
		अन्यथा
			freq = cpu_hw_rate / 1000;

		अगर (freq != prev_freq && core_count != LUT_TURBO_IND) अणु
			अगर (!qcom_cpufreq_update_opp(cpu_dev, freq, volt)) अणु
				table[i].frequency = freq;
				dev_dbg(cpu_dev, "index=%d freq=%d, core_count %d\n", i,
				freq, core_count);
			पूर्ण अन्यथा अणु
				dev_warn(cpu_dev, "failed to update OPP for freq=%d\n", freq);
				table[i].frequency = CPUFREQ_ENTRY_INVALID;
			पूर्ण

		पूर्ण अन्यथा अगर (core_count == LUT_TURBO_IND) अणु
			table[i].frequency = CPUFREQ_ENTRY_INVALID;
		पूर्ण

		/*
		 * Two of the same frequencies with the same core counts means
		 * end of table
		 */
		अगर (i > 0 && prev_freq == freq) अणु
			काष्ठा cpufreq_frequency_table *prev = &table[i - 1];

			/*
			 * Only treat the last frequency that might be a boost
			 * as the boost frequency
			 */
			अगर (prev->frequency == CPUFREQ_ENTRY_INVALID) अणु
				अगर (!qcom_cpufreq_update_opp(cpu_dev, prev_freq, volt)) अणु
					prev->frequency = prev_freq;
					prev->flags = CPUFREQ_BOOST_FREQ;
				पूर्ण अन्यथा अणु
					dev_warn(cpu_dev, "failed to update OPP for freq=%d\n",
						 freq);
				पूर्ण
			पूर्ण

			अवरोध;
		पूर्ण

		prev_freq = freq;
	पूर्ण

	table[i].frequency = CPUFREQ_TABLE_END;
	policy->freq_table = table;
	dev_pm_opp_set_sharing_cpus(cpu_dev, policy->cpus);

	वापस 0;
पूर्ण

अटल व्योम qcom_get_related_cpus(पूर्णांक index, काष्ठा cpumask *m)
अणु
	काष्ठा device_node *cpu_np;
	काष्ठा of_phandle_args args;
	पूर्णांक cpu, ret;

	क्रम_each_possible_cpu(cpu) अणु
		cpu_np = of_cpu_device_node_get(cpu);
		अगर (!cpu_np)
			जारी;

		ret = of_parse_phandle_with_args(cpu_np, "qcom,freq-domain",
						 "#freq-domain-cells", 0,
						 &args);
		of_node_put(cpu_np);
		अगर (ret < 0)
			जारी;

		अगर (index == args.args[0])
			cpumask_set_cpu(cpu, m);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा qcom_cpufreq_soc_data qcom_soc_data = अणु
	.reg_enable = 0x0,
	.reg_freq_lut = 0x110,
	.reg_volt_lut = 0x114,
	.reg_perf_state = 0x920,
	.lut_row_size = 32,
पूर्ण;

अटल स्थिर काष्ठा qcom_cpufreq_soc_data epss_soc_data = अणु
	.reg_enable = 0x0,
	.reg_freq_lut = 0x100,
	.reg_volt_lut = 0x200,
	.reg_perf_state = 0x320,
	.lut_row_size = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_cpufreq_hw_match[] = अणु
	अणु .compatible = "qcom,cpufreq-hw", .data = &qcom_soc_data पूर्ण,
	अणु .compatible = "qcom,cpufreq-epss", .data = &epss_soc_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_cpufreq_hw_match);

अटल पूर्णांक qcom_cpufreq_hw_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा platक्रमm_device *pdev = cpufreq_get_driver_data();
	काष्ठा device *dev = &pdev->dev;
	काष्ठा of_phandle_args args;
	काष्ठा device_node *cpu_np;
	काष्ठा device *cpu_dev;
	काष्ठा resource *res;
	व्योम __iomem *base;
	काष्ठा qcom_cpufreq_data *data;
	पूर्णांक ret, index;

	cpu_dev = get_cpu_device(policy->cpu);
	अगर (!cpu_dev) अणु
		pr_err("%s: failed to get cpu%d device\n", __func__,
		       policy->cpu);
		वापस -ENODEV;
	पूर्ण

	cpu_np = of_cpu_device_node_get(policy->cpu);
	अगर (!cpu_np)
		वापस -EINVAL;

	ret = of_parse_phandle_with_args(cpu_np, "qcom,freq-domain",
					 "#freq-domain-cells", 0, &args);
	of_node_put(cpu_np);
	अगर (ret)
		वापस ret;

	index = args.args[0];

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index);
	अगर (!res) अणु
		dev_err(dev, "failed to get mem resource %d\n", index);
		वापस -ENODEV;
	पूर्ण

	अगर (!request_mem_region(res->start, resource_size(res), res->name)) अणु
		dev_err(dev, "failed to request resource %pR\n", res);
		वापस -EBUSY;
	पूर्ण

	base = ioremap(res->start, resource_size(res));
	अगर (!base) अणु
		dev_err(dev, "failed to map resource %pR\n", res);
		ret = -ENOMEM;
		जाओ release_region;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ unmap_base;
	पूर्ण

	data->soc_data = of_device_get_match_data(&pdev->dev);
	data->base = base;
	data->res = res;

	/* HW should be in enabled state to proceed */
	अगर (!(पढ़ोl_relaxed(base + data->soc_data->reg_enable) & 0x1)) अणु
		dev_err(dev, "Domain-%d cpufreq hardware not enabled\n", index);
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	qcom_get_related_cpus(index, policy->cpus);
	अगर (!cpumask_weight(policy->cpus)) अणु
		dev_err(dev, "Domain-%d failed to get related CPUs\n", index);
		ret = -ENOENT;
		जाओ error;
	पूर्ण

	policy->driver_data = data;

	ret = qcom_cpufreq_hw_पढ़ो_lut(cpu_dev, policy);
	अगर (ret) अणु
		dev_err(dev, "Domain-%d failed to read LUT\n", index);
		जाओ error;
	पूर्ण

	ret = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (ret <= 0) अणु
		dev_err(cpu_dev, "Failed to add OPPs\n");
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	dev_pm_opp_of_रेजिस्टर_em(cpu_dev, policy->cpus);

	अगर (policy_has_boost_freq(policy)) अणु
		ret = cpufreq_enable_boost_support();
		अगर (ret)
			dev_warn(cpu_dev, "failed to enable boost: %d\n", ret);
	पूर्ण

	वापस 0;
error:
	kमुक्त(data);
unmap_base:
	iounmap(base);
release_region:
	release_mem_region(res->start, resource_size(res));
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_cpufreq_hw_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(policy->cpu);
	काष्ठा qcom_cpufreq_data *data = policy->driver_data;
	काष्ठा resource *res = data->res;
	व्योम __iomem *base = data->base;

	dev_pm_opp_हटाओ_all_dynamic(cpu_dev);
	dev_pm_opp_of_cpumask_हटाओ_table(policy->related_cpus);
	kमुक्त(policy->freq_table);
	kमुक्त(data);
	iounmap(base);
	release_mem_region(res->start, resource_size(res));

	वापस 0;
पूर्ण

अटल काष्ठा freq_attr *qcom_cpufreq_hw_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	&cpufreq_freq_attr_scaling_boost_freqs,
	शून्य
पूर्ण;

अटल काष्ठा cpufreq_driver cpufreq_qcom_hw_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK |
			  CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
			  CPUFREQ_IS_COOLING_DEV,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= qcom_cpufreq_hw_target_index,
	.get		= qcom_cpufreq_hw_get,
	.init		= qcom_cpufreq_hw_cpu_init,
	.निकास		= qcom_cpufreq_hw_cpu_निकास,
	.fast_चयन    = qcom_cpufreq_hw_fast_चयन,
	.name		= "qcom-cpufreq-hw",
	.attr		= qcom_cpufreq_hw_attr,
पूर्ण;

अटल पूर्णांक qcom_cpufreq_hw_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *cpu_dev;
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = clk_get(&pdev->dev, "xo");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	xo_rate = clk_get_rate(clk);
	clk_put(clk);

	clk = clk_get(&pdev->dev, "alternate");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	cpu_hw_rate = clk_get_rate(clk) / CLK_HW_DIV;
	clk_put(clk);

	cpufreq_qcom_hw_driver.driver_data = pdev;

	/* Check क्रम optional पूर्णांकerconnect paths on CPU0 */
	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev)
		वापस -EPROBE_DEFER;

	ret = dev_pm_opp_of_find_icc_paths(cpu_dev, शून्य);
	अगर (ret)
		वापस ret;

	ret = cpufreq_रेजिस्टर_driver(&cpufreq_qcom_hw_driver);
	अगर (ret)
		dev_err(&pdev->dev, "CPUFreq HW driver failed to register\n");
	अन्यथा
		dev_dbg(&pdev->dev, "QCOM CPUFreq HW driver initialized\n");

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_cpufreq_hw_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस cpufreq_unरेजिस्टर_driver(&cpufreq_qcom_hw_driver);
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_cpufreq_hw_driver = अणु
	.probe = qcom_cpufreq_hw_driver_probe,
	.हटाओ = qcom_cpufreq_hw_driver_हटाओ,
	.driver = अणु
		.name = "qcom-cpufreq-hw",
		.of_match_table = qcom_cpufreq_hw_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_cpufreq_hw_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_cpufreq_hw_driver);
पूर्ण
postcore_initcall(qcom_cpufreq_hw_init);

अटल व्योम __निकास qcom_cpufreq_hw_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_cpufreq_hw_driver);
पूर्ण
module_निकास(qcom_cpufreq_hw_निकास);

MODULE_DESCRIPTION("QCOM CPUFREQ HW Driver");
MODULE_LICENSE("GPL v2");
