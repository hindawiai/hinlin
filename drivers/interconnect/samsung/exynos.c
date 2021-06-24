<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Exynos generic पूर्णांकerconnect provider driver
 *
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
 *
 * Authors: Artur धwigoध <a.swigon@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>

#घोषणा EXYNOS_ICC_DEFAULT_BUS_CLK_RATIO	8

काष्ठा exynos_icc_priv अणु
	काष्ठा device *dev;

	/* One पूर्णांकerconnect node per provider */
	काष्ठा icc_provider provider;
	काष्ठा icc_node *node;

	काष्ठा dev_pm_qos_request qos_req;
	u32 bus_clk_ratio;
पूर्ण;

अटल काष्ठा icc_node *exynos_icc_get_parent(काष्ठा device_node *np)
अणु
	काष्ठा of_phandle_args args;
	काष्ठा icc_node_data *icc_node_data;
	काष्ठा icc_node *icc_node;
	पूर्णांक num, ret;

	num = of_count_phandle_with_args(np, "interconnects",
					 "#interconnect-cells");
	अगर (num < 1)
		वापस शून्य; /* parent nodes are optional */

	/* Get the पूर्णांकerconnect target node */
	ret = of_parse_phandle_with_args(np, "interconnects",
					"#interconnect-cells", 0, &args);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	icc_node_data = of_icc_get_from_provider(&args);
	of_node_put(args.np);

	अगर (IS_ERR(icc_node_data))
		वापस ERR_CAST(icc_node_data);

	icc_node = icc_node_data->node;
	kमुक्त(icc_node_data);

	वापस icc_node;
पूर्ण

अटल पूर्णांक exynos_generic_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा exynos_icc_priv *src_priv = src->data, *dst_priv = dst->data;
	s32 src_freq = max(src->avg_bw, src->peak_bw) / src_priv->bus_clk_ratio;
	s32 dst_freq = max(dst->avg_bw, dst->peak_bw) / dst_priv->bus_clk_ratio;
	पूर्णांक ret;

	ret = dev_pm_qos_update_request(&src_priv->qos_req, src_freq);
	अगर (ret < 0) अणु
		dev_err(src_priv->dev, "failed to update PM QoS of %s (src)\n",
			src->name);
		वापस ret;
	पूर्ण

	ret = dev_pm_qos_update_request(&dst_priv->qos_req, dst_freq);
	अगर (ret < 0) अणु
		dev_err(dst_priv->dev, "failed to update PM QoS of %s (dst)\n",
			dst->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा icc_node *exynos_generic_icc_xlate(काष्ठा of_phandle_args *spec,
						 व्योम *data)
अणु
	काष्ठा exynos_icc_priv *priv = data;

	अगर (spec->np != priv->dev->parent->of_node)
		वापस ERR_PTR(-EINVAL);

	वापस priv->node;
पूर्ण

अटल पूर्णांक exynos_generic_icc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_icc_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा icc_node *parent_node, *node = priv->node;

	parent_node = exynos_icc_get_parent(priv->dev->parent->of_node);
	अगर (parent_node && !IS_ERR(parent_node))
		icc_link_destroy(node, parent_node);

	icc_nodes_हटाओ(&priv->provider);
	icc_provider_del(&priv->provider);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_generic_icc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *bus_dev = pdev->dev.parent;
	काष्ठा exynos_icc_priv *priv;
	काष्ठा icc_provider *provider;
	काष्ठा icc_node *icc_node, *icc_parent_node;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, priv);

	provider = &priv->provider;

	provider->set = exynos_generic_icc_set;
	provider->aggregate = icc_std_aggregate;
	provider->xlate = exynos_generic_icc_xlate;
	provider->dev = bus_dev;
	provider->पूर्णांकer_set = true;
	provider->data = priv;

	ret = icc_provider_add(provider);
	अगर (ret < 0)
		वापस ret;

	icc_node = icc_node_create(pdev->id);
	अगर (IS_ERR(icc_node)) अणु
		ret = PTR_ERR(icc_node);
		जाओ err_prov_del;
	पूर्ण

	priv->node = icc_node;
	icc_node->name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%pOFn",
					bus_dev->of_node);
	अगर (of_property_पढ़ो_u32(bus_dev->of_node, "samsung,data-clock-ratio",
				 &priv->bus_clk_ratio))
		priv->bus_clk_ratio = EXYNOS_ICC_DEFAULT_BUS_CLK_RATIO;

	/*
	 * Register a PM QoS request क्रम the parent (devfreq) device.
	 */
	ret = dev_pm_qos_add_request(bus_dev, &priv->qos_req,
				     DEV_PM_QOS_MIN_FREQUENCY, 0);
	अगर (ret < 0)
		जाओ err_node_del;

	icc_node->data = priv;
	icc_node_add(icc_node, provider);

	icc_parent_node = exynos_icc_get_parent(bus_dev->of_node);
	अगर (IS_ERR(icc_parent_node)) अणु
		ret = PTR_ERR(icc_parent_node);
		जाओ err_pmqos_del;
	पूर्ण
	अगर (icc_parent_node) अणु
		ret = icc_link_create(icc_node, icc_parent_node->id);
		अगर (ret < 0)
			जाओ err_pmqos_del;
	पूर्ण

	वापस 0;

err_pmqos_del:
	dev_pm_qos_हटाओ_request(&priv->qos_req);
err_node_del:
	icc_nodes_हटाओ(provider);
err_prov_del:
	icc_provider_del(provider);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_generic_icc_driver = अणु
	.driver = अणु
		.name = "exynos-generic-icc",
		.sync_state = icc_sync_state,
	पूर्ण,
	.probe = exynos_generic_icc_probe,
	.हटाओ = exynos_generic_icc_हटाओ,
पूर्ण;
module_platक्रमm_driver(exynos_generic_icc_driver);

MODULE_DESCRIPTION("Exynos generic interconnect driver");
MODULE_AUTHOR("Artur धwigoध <a.swigon@samsung.com>");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:exynos-generic-icc");
