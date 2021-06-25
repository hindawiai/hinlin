<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Author: Pi-Cheng Chen <pi-cheng.chen@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#घोषणा MIN_VOLT_SHIFT		(100000)
#घोषणा MAX_VOLT_SHIFT		(200000)
#घोषणा MAX_VOLT_LIMIT		(1150000)
#घोषणा VOLT_TOL		(10000)

/*
 * The काष्ठा mtk_cpu_dvfs_info holds necessary inक्रमmation क्रम करोing CPU DVFS
 * on each CPU घातer/घड़ी करोमुख्य of Mediatek SoCs. Each CPU cluster in
 * Mediatek SoCs has two voltage inमाला_दो, Vproc and Vsram. In some हालs the two
 * voltage inमाला_दो need to be controlled under a hardware limitation:
 * 100mV < Vsram - Vproc < 200mV
 *
 * When scaling the घड़ी frequency of a CPU घड़ी करोमुख्य, the घड़ी source
 * needs to be चयनed to another stable PLL घड़ी temporarily until
 * the original PLL becomes stable at target frequency.
 */
काष्ठा mtk_cpu_dvfs_info अणु
	काष्ठा cpumask cpus;
	काष्ठा device *cpu_dev;
	काष्ठा regulator *proc_reg;
	काष्ठा regulator *sram_reg;
	काष्ठा clk *cpu_clk;
	काष्ठा clk *पूर्णांकer_clk;
	काष्ठा list_head list_head;
	पूर्णांक पूर्णांकermediate_voltage;
	bool need_voltage_tracking;
पूर्ण;

अटल LIST_HEAD(dvfs_info_list);

अटल काष्ठा mtk_cpu_dvfs_info *mtk_cpu_dvfs_info_lookup(पूर्णांक cpu)
अणु
	काष्ठा mtk_cpu_dvfs_info *info;

	list_क्रम_each_entry(info, &dvfs_info_list, list_head) अणु
		अगर (cpumask_test_cpu(cpu, &info->cpus))
			वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_cpufreq_voltage_tracking(काष्ठा mtk_cpu_dvfs_info *info,
					पूर्णांक new_vproc)
अणु
	काष्ठा regulator *proc_reg = info->proc_reg;
	काष्ठा regulator *sram_reg = info->sram_reg;
	पूर्णांक old_vproc, old_vsram, new_vsram, vsram, vproc, ret;

	old_vproc = regulator_get_voltage(proc_reg);
	अगर (old_vproc < 0) अणु
		pr_err("%s: invalid Vproc value: %d\n", __func__, old_vproc);
		वापस old_vproc;
	पूर्ण
	/* Vsram should not exceed the maximum allowed voltage of SoC. */
	new_vsram = min(new_vproc + MIN_VOLT_SHIFT, MAX_VOLT_LIMIT);

	अगर (old_vproc < new_vproc) अणु
		/*
		 * When scaling up voltages, Vsram and Vproc scale up step
		 * by step. At each step, set Vsram to (Vproc + 200mV) first,
		 * then set Vproc to (Vsram - 100mV).
		 * Keep करोing it until Vsram and Vproc hit target voltages.
		 */
		करो अणु
			old_vsram = regulator_get_voltage(sram_reg);
			अगर (old_vsram < 0) अणु
				pr_err("%s: invalid Vsram value: %d\n",
				       __func__, old_vsram);
				वापस old_vsram;
			पूर्ण
			old_vproc = regulator_get_voltage(proc_reg);
			अगर (old_vproc < 0) अणु
				pr_err("%s: invalid Vproc value: %d\n",
				       __func__, old_vproc);
				वापस old_vproc;
			पूर्ण

			vsram = min(new_vsram, old_vproc + MAX_VOLT_SHIFT);

			अगर (vsram + VOLT_TOL >= MAX_VOLT_LIMIT) अणु
				vsram = MAX_VOLT_LIMIT;

				/*
				 * If the target Vsram hits the maximum voltage,
				 * try to set the exact voltage value first.
				 */
				ret = regulator_set_voltage(sram_reg, vsram,
							    vsram);
				अगर (ret)
					ret = regulator_set_voltage(sram_reg,
							vsram - VOLT_TOL,
							vsram);

				vproc = new_vproc;
			पूर्ण अन्यथा अणु
				ret = regulator_set_voltage(sram_reg, vsram,
							    vsram + VOLT_TOL);

				vproc = vsram - MIN_VOLT_SHIFT;
			पूर्ण
			अगर (ret)
				वापस ret;

			ret = regulator_set_voltage(proc_reg, vproc,
						    vproc + VOLT_TOL);
			अगर (ret) अणु
				regulator_set_voltage(sram_reg, old_vsram,
						      old_vsram);
				वापस ret;
			पूर्ण
		पूर्ण जबतक (vproc < new_vproc || vsram < new_vsram);
	पूर्ण अन्यथा अगर (old_vproc > new_vproc) अणु
		/*
		 * When scaling करोwn voltages, Vsram and Vproc scale करोwn step
		 * by step. At each step, set Vproc to (Vsram - 200mV) first,
		 * then set Vproc to (Vproc + 100mV).
		 * Keep करोing it until Vsram and Vproc hit target voltages.
		 */
		करो अणु
			old_vproc = regulator_get_voltage(proc_reg);
			अगर (old_vproc < 0) अणु
				pr_err("%s: invalid Vproc value: %d\n",
				       __func__, old_vproc);
				वापस old_vproc;
			पूर्ण
			old_vsram = regulator_get_voltage(sram_reg);
			अगर (old_vsram < 0) अणु
				pr_err("%s: invalid Vsram value: %d\n",
				       __func__, old_vsram);
				वापस old_vsram;
			पूर्ण

			vproc = max(new_vproc, old_vsram - MAX_VOLT_SHIFT);
			ret = regulator_set_voltage(proc_reg, vproc,
						    vproc + VOLT_TOL);
			अगर (ret)
				वापस ret;

			अगर (vproc == new_vproc)
				vsram = new_vsram;
			अन्यथा
				vsram = max(new_vsram, vproc + MIN_VOLT_SHIFT);

			अगर (vsram + VOLT_TOL >= MAX_VOLT_LIMIT) अणु
				vsram = MAX_VOLT_LIMIT;

				/*
				 * If the target Vsram hits the maximum voltage,
				 * try to set the exact voltage value first.
				 */
				ret = regulator_set_voltage(sram_reg, vsram,
							    vsram);
				अगर (ret)
					ret = regulator_set_voltage(sram_reg,
							vsram - VOLT_TOL,
							vsram);
			पूर्ण अन्यथा अणु
				ret = regulator_set_voltage(sram_reg, vsram,
							    vsram + VOLT_TOL);
			पूर्ण

			अगर (ret) अणु
				regulator_set_voltage(proc_reg, old_vproc,
						      old_vproc);
				वापस ret;
			पूर्ण
		पूर्ण जबतक (vproc > new_vproc + VOLT_TOL ||
			 vsram > new_vsram + VOLT_TOL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_cpufreq_set_voltage(काष्ठा mtk_cpu_dvfs_info *info, पूर्णांक vproc)
अणु
	अगर (info->need_voltage_tracking)
		वापस mtk_cpufreq_voltage_tracking(info, vproc);
	अन्यथा
		वापस regulator_set_voltage(info->proc_reg, vproc,
					     vproc + VOLT_TOL);
पूर्ण

अटल पूर्णांक mtk_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				  अचिन्हित पूर्णांक index)
अणु
	काष्ठा cpufreq_frequency_table *freq_table = policy->freq_table;
	काष्ठा clk *cpu_clk = policy->clk;
	काष्ठा clk *armpll = clk_get_parent(cpu_clk);
	काष्ठा mtk_cpu_dvfs_info *info = policy->driver_data;
	काष्ठा device *cpu_dev = info->cpu_dev;
	काष्ठा dev_pm_opp *opp;
	दीर्घ freq_hz, old_freq_hz;
	पूर्णांक vproc, old_vproc, पूर्णांकer_vproc, target_vproc, ret;

	पूर्णांकer_vproc = info->पूर्णांकermediate_voltage;

	old_freq_hz = clk_get_rate(cpu_clk);
	old_vproc = regulator_get_voltage(info->proc_reg);
	अगर (old_vproc < 0) अणु
		pr_err("%s: invalid Vproc value: %d\n", __func__, old_vproc);
		वापस old_vproc;
	पूर्ण

	freq_hz = freq_table[index].frequency * 1000;

	opp = dev_pm_opp_find_freq_उच्चमान(cpu_dev, &freq_hz);
	अगर (IS_ERR(opp)) अणु
		pr_err("cpu%d: failed to find OPP for %ld\n",
		       policy->cpu, freq_hz);
		वापस PTR_ERR(opp);
	पूर्ण
	vproc = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	/*
	 * If the new voltage or the पूर्णांकermediate voltage is higher than the
	 * current voltage, scale up voltage first.
	 */
	target_vproc = (पूर्णांकer_vproc > vproc) ? पूर्णांकer_vproc : vproc;
	अगर (old_vproc < target_vproc) अणु
		ret = mtk_cpufreq_set_voltage(info, target_vproc);
		अगर (ret) अणु
			pr_err("cpu%d: failed to scale up voltage!\n",
			       policy->cpu);
			mtk_cpufreq_set_voltage(info, old_vproc);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Reparent the CPU घड़ी to पूर्णांकermediate घड़ी. */
	ret = clk_set_parent(cpu_clk, info->पूर्णांकer_clk);
	अगर (ret) अणु
		pr_err("cpu%d: failed to re-parent cpu clock!\n",
		       policy->cpu);
		mtk_cpufreq_set_voltage(info, old_vproc);
		WARN_ON(1);
		वापस ret;
	पूर्ण

	/* Set the original PLL to target rate. */
	ret = clk_set_rate(armpll, freq_hz);
	अगर (ret) अणु
		pr_err("cpu%d: failed to scale cpu clock rate!\n",
		       policy->cpu);
		clk_set_parent(cpu_clk, armpll);
		mtk_cpufreq_set_voltage(info, old_vproc);
		वापस ret;
	पूर्ण

	/* Set parent of CPU घड़ी back to the original PLL. */
	ret = clk_set_parent(cpu_clk, armpll);
	अगर (ret) अणु
		pr_err("cpu%d: failed to re-parent cpu clock!\n",
		       policy->cpu);
		mtk_cpufreq_set_voltage(info, पूर्णांकer_vproc);
		WARN_ON(1);
		वापस ret;
	पूर्ण

	/*
	 * If the new voltage is lower than the पूर्णांकermediate voltage or the
	 * original voltage, scale करोwn to the new voltage.
	 */
	अगर (vproc < पूर्णांकer_vproc || vproc < old_vproc) अणु
		ret = mtk_cpufreq_set_voltage(info, vproc);
		अगर (ret) अणु
			pr_err("cpu%d: failed to scale down voltage!\n",
			       policy->cpu);
			clk_set_parent(cpu_clk, info->पूर्णांकer_clk);
			clk_set_rate(armpll, old_freq_hz);
			clk_set_parent(cpu_clk, armpll);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DYNAMIC_POWER "dynamic-power-coefficient"

अटल पूर्णांक mtk_cpu_dvfs_info_init(काष्ठा mtk_cpu_dvfs_info *info, पूर्णांक cpu)
अणु
	काष्ठा device *cpu_dev;
	काष्ठा regulator *proc_reg = ERR_PTR(-ENODEV);
	काष्ठा regulator *sram_reg = ERR_PTR(-ENODEV);
	काष्ठा clk *cpu_clk = ERR_PTR(-ENODEV);
	काष्ठा clk *पूर्णांकer_clk = ERR_PTR(-ENODEV);
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(cpu);
	अगर (!cpu_dev) अणु
		pr_err("failed to get cpu%d device\n", cpu);
		वापस -ENODEV;
	पूर्ण

	cpu_clk = clk_get(cpu_dev, "cpu");
	अगर (IS_ERR(cpu_clk)) अणु
		अगर (PTR_ERR(cpu_clk) == -EPROBE_DEFER)
			pr_warn("cpu clk for cpu%d not ready, retry.\n", cpu);
		अन्यथा
			pr_err("failed to get cpu clk for cpu%d\n", cpu);

		ret = PTR_ERR(cpu_clk);
		वापस ret;
	पूर्ण

	पूर्णांकer_clk = clk_get(cpu_dev, "intermediate");
	अगर (IS_ERR(पूर्णांकer_clk)) अणु
		अगर (PTR_ERR(पूर्णांकer_clk) == -EPROBE_DEFER)
			pr_warn("intermediate clk for cpu%d not ready, retry.\n",
				cpu);
		अन्यथा
			pr_err("failed to get intermediate clk for cpu%d\n",
			       cpu);

		ret = PTR_ERR(पूर्णांकer_clk);
		जाओ out_मुक्त_resources;
	पूर्ण

	proc_reg = regulator_get_optional(cpu_dev, "proc");
	अगर (IS_ERR(proc_reg)) अणु
		अगर (PTR_ERR(proc_reg) == -EPROBE_DEFER)
			pr_warn("proc regulator for cpu%d not ready, retry.\n",
				cpu);
		अन्यथा
			pr_err("failed to get proc regulator for cpu%d\n",
			       cpu);

		ret = PTR_ERR(proc_reg);
		जाओ out_मुक्त_resources;
	पूर्ण

	/* Both presence and असलence of sram regulator are valid हालs. */
	sram_reg = regulator_get_exclusive(cpu_dev, "sram");

	/* Get OPP-sharing inक्रमmation from "operating-points-v2" bindings */
	ret = dev_pm_opp_of_get_sharing_cpus(cpu_dev, &info->cpus);
	अगर (ret) अणु
		pr_err("failed to get OPP-sharing information for cpu%d\n",
		       cpu);
		जाओ out_मुक्त_resources;
	पूर्ण

	ret = dev_pm_opp_of_cpumask_add_table(&info->cpus);
	अगर (ret) अणु
		pr_warn("no OPP table for cpu%d\n", cpu);
		जाओ out_मुक्त_resources;
	पूर्ण

	/* Search a safe voltage क्रम पूर्णांकermediate frequency. */
	rate = clk_get_rate(पूर्णांकer_clk);
	opp = dev_pm_opp_find_freq_उच्चमान(cpu_dev, &rate);
	अगर (IS_ERR(opp)) अणु
		pr_err("failed to get intermediate opp for cpu%d\n", cpu);
		ret = PTR_ERR(opp);
		जाओ out_मुक्त_opp_table;
	पूर्ण
	info->पूर्णांकermediate_voltage = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	info->cpu_dev = cpu_dev;
	info->proc_reg = proc_reg;
	info->sram_reg = IS_ERR(sram_reg) ? शून्य : sram_reg;
	info->cpu_clk = cpu_clk;
	info->पूर्णांकer_clk = पूर्णांकer_clk;

	/*
	 * If SRAM regulator is present, software "voltage tracking" is needed
	 * क्रम this CPU घातer करोमुख्य.
	 */
	info->need_voltage_tracking = !IS_ERR(sram_reg);

	वापस 0;

out_मुक्त_opp_table:
	dev_pm_opp_of_cpumask_हटाओ_table(&info->cpus);

out_मुक्त_resources:
	अगर (!IS_ERR(proc_reg))
		regulator_put(proc_reg);
	अगर (!IS_ERR(sram_reg))
		regulator_put(sram_reg);
	अगर (!IS_ERR(cpu_clk))
		clk_put(cpu_clk);
	अगर (!IS_ERR(पूर्णांकer_clk))
		clk_put(पूर्णांकer_clk);

	वापस ret;
पूर्ण

अटल व्योम mtk_cpu_dvfs_info_release(काष्ठा mtk_cpu_dvfs_info *info)
अणु
	अगर (!IS_ERR(info->proc_reg))
		regulator_put(info->proc_reg);
	अगर (!IS_ERR(info->sram_reg))
		regulator_put(info->sram_reg);
	अगर (!IS_ERR(info->cpu_clk))
		clk_put(info->cpu_clk);
	अगर (!IS_ERR(info->पूर्णांकer_clk))
		clk_put(info->पूर्णांकer_clk);

	dev_pm_opp_of_cpumask_हटाओ_table(&info->cpus);
पूर्ण

अटल पूर्णांक mtk_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा mtk_cpu_dvfs_info *info;
	काष्ठा cpufreq_frequency_table *freq_table;
	पूर्णांक ret;

	info = mtk_cpu_dvfs_info_lookup(policy->cpu);
	अगर (!info) अणु
		pr_err("dvfs info for cpu%d is not initialized.\n",
		       policy->cpu);
		वापस -EINVAL;
	पूर्ण

	ret = dev_pm_opp_init_cpufreq_table(info->cpu_dev, &freq_table);
	अगर (ret) अणु
		pr_err("failed to init cpufreq table for cpu%d: %d\n",
		       policy->cpu, ret);
		वापस ret;
	पूर्ण

	cpumask_copy(policy->cpus, &info->cpus);
	policy->freq_table = freq_table;
	policy->driver_data = info;
	policy->clk = info->cpu_clk;

	dev_pm_opp_of_रेजिस्टर_em(info->cpu_dev, policy->cpus);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा mtk_cpu_dvfs_info *info = policy->driver_data;

	dev_pm_opp_मुक्त_cpufreq_table(info->cpu_dev, &policy->freq_table);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver mtk_cpufreq_driver = अणु
	.flags = CPUFREQ_NEED_INITIAL_FREQ_CHECK |
		 CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
		 CPUFREQ_IS_COOLING_DEV,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = mtk_cpufreq_set_target,
	.get = cpufreq_generic_get,
	.init = mtk_cpufreq_init,
	.निकास = mtk_cpufreq_निकास,
	.name = "mtk-cpufreq",
	.attr = cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक mtk_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_cpu_dvfs_info *info, *पंचांगp;
	पूर्णांक cpu, ret;

	क्रम_each_possible_cpu(cpu) अणु
		info = mtk_cpu_dvfs_info_lookup(cpu);
		अगर (info)
			जारी;

		info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
		अगर (!info) अणु
			ret = -ENOMEM;
			जाओ release_dvfs_info_list;
		पूर्ण

		ret = mtk_cpu_dvfs_info_init(info, cpu);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to initialize dvfs info for cpu%d\n",
				cpu);
			जाओ release_dvfs_info_list;
		पूर्ण

		list_add(&info->list_head, &dvfs_info_list);
	पूर्ण

	ret = cpufreq_रेजिस्टर_driver(&mtk_cpufreq_driver);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register mtk cpufreq driver\n");
		जाओ release_dvfs_info_list;
	पूर्ण

	वापस 0;

release_dvfs_info_list:
	list_क्रम_each_entry_safe(info, पंचांगp, &dvfs_info_list, list_head) अणु
		mtk_cpu_dvfs_info_release(info);
		list_del(&info->list_head);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "mtk-cpufreq",
	पूर्ण,
	.probe		= mtk_cpufreq_probe,
पूर्ण;

/* List of machines supported by this driver */
अटल स्थिर काष्ठा of_device_id mtk_cpufreq_machines[] __initस्थिर = अणु
	अणु .compatible = "mediatek,mt2701", पूर्ण,
	अणु .compatible = "mediatek,mt2712", पूर्ण,
	अणु .compatible = "mediatek,mt7622", पूर्ण,
	अणु .compatible = "mediatek,mt7623", पूर्ण,
	अणु .compatible = "mediatek,mt8167", पूर्ण,
	अणु .compatible = "mediatek,mt817x", पूर्ण,
	अणु .compatible = "mediatek,mt8173", पूर्ण,
	अणु .compatible = "mediatek,mt8176", पूर्ण,
	अणु .compatible = "mediatek,mt8183", पूर्ण,
	अणु .compatible = "mediatek,mt8516", पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_cpufreq_machines);

अटल पूर्णांक __init mtk_cpufreq_driver_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	np = of_find_node_by_path("/");
	अगर (!np)
		वापस -ENODEV;

	match = of_match_node(mtk_cpufreq_machines, np);
	of_node_put(np);
	अगर (!match) अणु
		pr_debug("Machine is not compatible with mtk-cpufreq\n");
		वापस -ENODEV;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&mtk_cpufreq_platdrv);
	अगर (err)
		वापस err;

	/*
	 * Since there's no place to hold device registration code and no
	 * device tree based way to match cpufreq driver yet, both the driver
	 * and the device registration codes are put here to handle defer
	 * probing.
	 */
	pdev = platक्रमm_device_रेजिस्टर_simple("mtk-cpufreq", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		pr_err("failed to register mtk-cpufreq platform device\n");
		platक्रमm_driver_unरेजिस्टर(&mtk_cpufreq_platdrv);
		वापस PTR_ERR(pdev);
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(mtk_cpufreq_driver_init);

MODULE_DESCRIPTION("MediaTek CPUFreq driver");
MODULE_AUTHOR("Pi-Cheng Chen <pi-cheng.chen@linaro.org>");
MODULE_LICENSE("GPL v2");
