<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 *	Based on arch/arm/plat-omap/cpu-omap.c, (C) 2005 Nokia Corporation
 */

#समावेश <linux/bits.h>
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/types.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>

अटल bool cpu0_node_has_opp_v2_prop(व्योम)
अणु
	काष्ठा device_node *np = of_cpu_device_node_get(0);
	bool ret = false;

	अगर (of_get_property(np, "operating-points-v2", शून्य))
		ret = true;

	of_node_put(np);
	वापस ret;
पूर्ण

अटल व्योम tegra20_cpufreq_put_supported_hw(व्योम *opp_table)
अणु
	dev_pm_opp_put_supported_hw(opp_table);
पूर्ण

अटल व्योम tegra20_cpufreq_dt_unरेजिस्टर(व्योम *cpufreq_dt)
अणु
	platक्रमm_device_unरेजिस्टर(cpufreq_dt);
पूर्ण

अटल पूर्णांक tegra20_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *cpufreq_dt;
	काष्ठा opp_table *opp_table;
	काष्ठा device *cpu_dev;
	u32 versions[2];
	पूर्णांक err;

	अगर (!cpu0_node_has_opp_v2_prop()) अणु
		dev_err(&pdev->dev, "operating points not found\n");
		dev_err(&pdev->dev, "please update your device tree\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_machine_is_compatible("nvidia,tegra20")) अणु
		versions[0] = BIT(tegra_sku_info.cpu_process_id);
		versions[1] = BIT(tegra_sku_info.soc_speeकरो_id);
	पूर्ण अन्यथा अणु
		versions[0] = BIT(tegra_sku_info.cpu_process_id);
		versions[1] = BIT(tegra_sku_info.cpu_speeकरो_id);
	पूर्ण

	dev_info(&pdev->dev, "hardware version 0x%x 0x%x\n",
		 versions[0], versions[1]);

	cpu_dev = get_cpu_device(0);
	अगर (WARN_ON(!cpu_dev))
		वापस -ENODEV;

	opp_table = dev_pm_opp_set_supported_hw(cpu_dev, versions, 2);
	err = PTR_ERR_OR_ZERO(opp_table);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to set supported hw: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(&pdev->dev,
				       tegra20_cpufreq_put_supported_hw,
				       opp_table);
	अगर (err)
		वापस err;

	cpufreq_dt = platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1, शून्य, 0);
	err = PTR_ERR_OR_ZERO(cpufreq_dt);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed to create cpufreq-dt device: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(&pdev->dev,
				       tegra20_cpufreq_dt_unरेजिस्टर,
				       cpufreq_dt);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra20_cpufreq_driver = अणु
	.probe		= tegra20_cpufreq_probe,
	.driver		= अणु
		.name	= "tegra20-cpufreq",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra20_cpufreq_driver);

MODULE_ALIAS("platform:tegra20-cpufreq");
MODULE_AUTHOR("Colin Cross <ccross@android.com>");
MODULE_DESCRIPTION("NVIDIA Tegra20 cpufreq driver");
MODULE_LICENSE("GPL");
