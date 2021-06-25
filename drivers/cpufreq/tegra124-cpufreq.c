<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra 124 cpufreq driver
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/types.h>

काष्ठा tegra124_cpufreq_priv अणु
	काष्ठा clk *cpu_clk;
	काष्ठा clk *pllp_clk;
	काष्ठा clk *pllx_clk;
	काष्ठा clk *dfll_clk;
	काष्ठा platक्रमm_device *cpufreq_dt_pdev;
पूर्ण;

अटल पूर्णांक tegra124_cpu_चयन_to_dfll(काष्ठा tegra124_cpufreq_priv *priv)
अणु
	काष्ठा clk *orig_parent;
	पूर्णांक ret;

	ret = clk_set_rate(priv->dfll_clk, clk_get_rate(priv->cpu_clk));
	अगर (ret)
		वापस ret;

	orig_parent = clk_get_parent(priv->cpu_clk);
	clk_set_parent(priv->cpu_clk, priv->pllp_clk);

	ret = clk_prepare_enable(priv->dfll_clk);
	अगर (ret)
		जाओ out;

	clk_set_parent(priv->cpu_clk, priv->dfll_clk);

	वापस 0;

out:
	clk_set_parent(priv->cpu_clk, orig_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra124_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra124_cpufreq_priv *priv;
	काष्ठा device_node *np;
	काष्ठा device *cpu_dev;
	काष्ठा platक्रमm_device_info cpufreq_dt_devinfo = अणुपूर्ण;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev)
		वापस -ENODEV;

	np = of_cpu_device_node_get(0);
	अगर (!np)
		वापस -ENODEV;

	priv->cpu_clk = of_clk_get_by_name(np, "cpu_g");
	अगर (IS_ERR(priv->cpu_clk)) अणु
		ret = PTR_ERR(priv->cpu_clk);
		जाओ out_put_np;
	पूर्ण

	priv->dfll_clk = of_clk_get_by_name(np, "dfll");
	अगर (IS_ERR(priv->dfll_clk)) अणु
		ret = PTR_ERR(priv->dfll_clk);
		जाओ out_put_cpu_clk;
	पूर्ण

	priv->pllx_clk = of_clk_get_by_name(np, "pll_x");
	अगर (IS_ERR(priv->pllx_clk)) अणु
		ret = PTR_ERR(priv->pllx_clk);
		जाओ out_put_dfll_clk;
	पूर्ण

	priv->pllp_clk = of_clk_get_by_name(np, "pll_p");
	अगर (IS_ERR(priv->pllp_clk)) अणु
		ret = PTR_ERR(priv->pllp_clk);
		जाओ out_put_pllx_clk;
	पूर्ण

	ret = tegra124_cpu_चयन_to_dfll(priv);
	अगर (ret)
		जाओ out_put_pllp_clk;

	cpufreq_dt_devinfo.name = "cpufreq-dt";
	cpufreq_dt_devinfo.parent = &pdev->dev;

	priv->cpufreq_dt_pdev =
		platक्रमm_device_रेजिस्टर_full(&cpufreq_dt_devinfo);
	अगर (IS_ERR(priv->cpufreq_dt_pdev)) अणु
		ret = PTR_ERR(priv->cpufreq_dt_pdev);
		जाओ out_put_pllp_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	of_node_put(np);

	वापस 0;

out_put_pllp_clk:
	clk_put(priv->pllp_clk);
out_put_pllx_clk:
	clk_put(priv->pllx_clk);
out_put_dfll_clk:
	clk_put(priv->dfll_clk);
out_put_cpu_clk:
	clk_put(priv->cpu_clk);
out_put_np:
	of_node_put(np);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused tegra124_cpufreq_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra124_cpufreq_priv *priv = dev_get_drvdata(dev);
	पूर्णांक err;

	/*
	 * PLLP rate 408Mhz is below the CPU Fmax at Vmin and is safe to
	 * use during suspend and resume. So, चयन the CPU घड़ी source
	 * to PLLP and disable DFLL.
	 */
	err = clk_set_parent(priv->cpu_clk, priv->pllp_clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to reparent to PLLP: %d\n", err);
		वापस err;
	पूर्ण

	clk_disable_unprepare(priv->dfll_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra124_cpufreq_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra124_cpufreq_priv *priv = dev_get_drvdata(dev);
	पूर्णांक err;

	/*
	 * Warmboot code घातers up the CPU with PLLP घड़ी source.
	 * Enable DFLL घड़ी and चयन CPU घड़ी source back to DFLL.
	 */
	err = clk_prepare_enable(priv->dfll_clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable DFLL clock for CPU: %d\n", err);
		जाओ disable_cpufreq;
	पूर्ण

	err = clk_set_parent(priv->cpu_clk, priv->dfll_clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to reparent to DFLL clock: %d\n", err);
		जाओ disable_dfll;
	पूर्ण

	वापस 0;

disable_dfll:
	clk_disable_unprepare(priv->dfll_clk);
disable_cpufreq:
	disable_cpufreq();

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra124_cpufreq_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra124_cpufreq_suspend,
				tegra124_cpufreq_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra124_cpufreq_platdrv = अणु
	.driver.name	= "cpufreq-tegra124",
	.driver.pm	= &tegra124_cpufreq_pm_ops,
	.probe		= tegra124_cpufreq_probe,
पूर्ण;

अटल पूर्णांक __init tegra_cpufreq_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;

	अगर (!(of_machine_is_compatible("nvidia,tegra124") ||
		of_machine_is_compatible("nvidia,tegra210")))
		वापस -ENODEV;

	/*
	 * Platक्रमm driver+device required क्रम handling EPROBE_DEFER with
	 * the regulator and the DFLL घड़ी
	 */
	ret = platक्रमm_driver_रेजिस्टर(&tegra124_cpufreq_platdrv);
	अगर (ret)
		वापस ret;

	pdev = platक्रमm_device_रेजिस्टर_simple("cpufreq-tegra124", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		platक्रमm_driver_unरेजिस्टर(&tegra124_cpufreq_platdrv);
		वापस PTR_ERR(pdev);
	पूर्ण

	वापस 0;
पूर्ण
module_init(tegra_cpufreq_init);

MODULE_AUTHOR("Tuomas Tynkkynen <ttynkkynen@nvidia.com>");
MODULE_DESCRIPTION("cpufreq driver for NVIDIA Tegra124");
MODULE_LICENSE("GPL v2");
