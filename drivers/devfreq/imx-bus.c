<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP
 */

#समावेश <linux/clk.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा imx_bus अणु
	काष्ठा devfreq_dev_profile profile;
	काष्ठा devfreq *devfreq;
	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *icc_pdev;
पूर्ण;

अटल पूर्णांक imx_bus_target(काष्ठा device *dev,
		अचिन्हित दीर्घ *freq, u32 flags)
अणु
	काष्ठा dev_pm_opp *new_opp;
	पूर्णांक ret;

	new_opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(new_opp)) अणु
		ret = PTR_ERR(new_opp);
		dev_err(dev, "failed to get recommended opp: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_pm_opp_put(new_opp);

	वापस dev_pm_opp_set_rate(dev, *freq);
पूर्ण

अटल पूर्णांक imx_bus_get_cur_freq(काष्ठा device *dev, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा imx_bus *priv = dev_get_drvdata(dev);

	*freq = clk_get_rate(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_bus_get_dev_status(काष्ठा device *dev,
		काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा imx_bus *priv = dev_get_drvdata(dev);

	stat->busy_समय = 0;
	stat->total_समय = 0;
	stat->current_frequency = clk_get_rate(priv->clk);

	वापस 0;
पूर्ण

अटल व्योम imx_bus_निकास(काष्ठा device *dev)
अणु
	काष्ठा imx_bus *priv = dev_get_drvdata(dev);

	dev_pm_opp_of_हटाओ_table(dev);
	platक्रमm_device_unरेजिस्टर(priv->icc_pdev);
पूर्ण

/* imx_bus_init_icc() - रेजिस्टर matching icc provider अगर required */
अटल पूर्णांक imx_bus_init_icc(काष्ठा device *dev)
अणु
	काष्ठा imx_bus *priv = dev_get_drvdata(dev);
	स्थिर अक्षर *icc_driver_name;

	अगर (!of_get_property(dev->of_node, "#interconnect-cells", 0))
		वापस 0;
	अगर (!IS_ENABLED(CONFIG_INTERCONNECT_IMX)) अणु
		dev_warn(dev, "imx interconnect drivers disabled\n");
		वापस 0;
	पूर्ण

	icc_driver_name = of_device_get_match_data(dev);
	अगर (!icc_driver_name) अणु
		dev_err(dev, "unknown interconnect driver\n");
		वापस 0;
	पूर्ण

	priv->icc_pdev = platक्रमm_device_रेजिस्टर_data(
			dev, icc_driver_name, -1, शून्य, 0);
	अगर (IS_ERR(priv->icc_pdev)) अणु
		dev_err(dev, "failed to register icc provider %s: %ld\n",
				icc_driver_name, PTR_ERR(priv->icc_pdev));
		वापस PTR_ERR(priv->icc_pdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx_bus *priv;
	स्थिर अक्षर *gov = DEVFREQ_GOV_USERSPACE;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/*
	 * Fetch the घड़ी to adjust but करोn't explicitly enable.
	 *
	 * For imx bus घड़ी clk_set_rate is safe no matter अगर the घड़ी is on
	 * or off and some peripheral side-buses might be off unless enabled by
	 * drivers क्रम devices on those specअगरic buses.
	 *
	 * Rate adjusपंचांगent on a disabled bus घड़ी just takes effect later.
	 */
	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		dev_err(dev, "failed to fetch clk: %d\n", ret);
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, priv);

	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get OPP table\n");
		वापस ret;
	पूर्ण

	priv->profile.polling_ms = 1000;
	priv->profile.target = imx_bus_target;
	priv->profile.get_dev_status = imx_bus_get_dev_status;
	priv->profile.निकास = imx_bus_निकास;
	priv->profile.get_cur_freq = imx_bus_get_cur_freq;
	priv->profile.initial_freq = clk_get_rate(priv->clk);

	priv->devfreq = devm_devfreq_add_device(dev, &priv->profile,
						gov, शून्य);
	अगर (IS_ERR(priv->devfreq)) अणु
		ret = PTR_ERR(priv->devfreq);
		dev_err(dev, "failed to add devfreq device: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = imx_bus_init_icc(dev);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_pm_opp_of_हटाओ_table(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_bus_of_match[] = अणु
	अणु .compatible = "fsl,imx8mq-noc", .data = "imx8mq-interconnect", पूर्ण,
	अणु .compatible = "fsl,imx8mm-noc", .data = "imx8mm-interconnect", पूर्ण,
	अणु .compatible = "fsl,imx8mn-noc", .data = "imx8mn-interconnect", पूर्ण,
	अणु .compatible = "fsl,imx8m-noc", पूर्ण,
	अणु .compatible = "fsl,imx8m-nic", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_bus_of_match);

अटल काष्ठा platक्रमm_driver imx_bus_platdrv = अणु
	.probe		= imx_bus_probe,
	.driver = अणु
		.name	= "imx-bus-devfreq",
		.of_match_table = imx_bus_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_bus_platdrv);

MODULE_DESCRIPTION("Generic i.MX bus frequency scaling driver");
MODULE_AUTHOR("Leonard Crestez <leonard.crestez@nxp.com>");
MODULE_LICENSE("GPL v2");
