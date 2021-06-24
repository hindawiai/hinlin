<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interconnect framework driver क्रम i.MX SoC
 *
 * Copyright (c) 2019, BayLibre
 * Copyright (c) 2019-2020, NXP
 * Author: Alexandre Bailon <abailon@baylibre.com>
 * Author: Leonard Crestez <leonard.crestez@nxp.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_qos.h>

#समावेश "imx.h"

/* निजी icc_node data */
काष्ठा imx_icc_node अणु
	स्थिर काष्ठा imx_icc_node_desc *desc;
	काष्ठा device *qos_dev;
	काष्ठा dev_pm_qos_request qos_req;
पूर्ण;

अटल पूर्णांक imx_icc_node_set(काष्ठा icc_node *node)
अणु
	काष्ठा device *dev = node->provider->dev;
	काष्ठा imx_icc_node *node_data = node->data;
	u64 freq;

	अगर (!node_data->qos_dev)
		वापस 0;

	freq = (node->avg_bw + node->peak_bw) * node_data->desc->adj->bw_mul;
	करो_भाग(freq, node_data->desc->adj->bw_भाग);
	dev_dbg(dev, "node %s device %s avg_bw %ukBps peak_bw %ukBps min_freq %llukHz\n",
		node->name, dev_name(node_data->qos_dev),
		node->avg_bw, node->peak_bw, freq);

	अगर (freq > S32_MAX) अणु
		dev_err(dev, "%s can't request more than S32_MAX freq\n",
				node->name);
		वापस -दुस्फल;
	पूर्ण

	dev_pm_qos_update_request(&node_data->qos_req, freq);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	वापस imx_icc_node_set(dst);
पूर्ण

/* imx_icc_node_destroy() - Destroy an imx icc_node, including निजी data */
अटल व्योम imx_icc_node_destroy(काष्ठा icc_node *node)
अणु
	काष्ठा imx_icc_node *node_data = node->data;
	पूर्णांक ret;

	अगर (dev_pm_qos_request_active(&node_data->qos_req)) अणु
		ret = dev_pm_qos_हटाओ_request(&node_data->qos_req);
		अगर (ret)
			dev_warn(node->provider->dev,
				 "failed to remove qos request for %s\n",
				 dev_name(node_data->qos_dev));
	पूर्ण

	put_device(node_data->qos_dev);
	icc_node_del(node);
	icc_node_destroy(node->id);
पूर्ण

अटल पूर्णांक imx_icc_node_init_qos(काष्ठा icc_provider *provider,
				 काष्ठा icc_node *node)
अणु
	काष्ठा imx_icc_node *node_data = node->data;
	स्थिर काष्ठा imx_icc_node_adj_desc *adj = node_data->desc->adj;
	काष्ठा device *dev = provider->dev;
	काष्ठा device_node *dn = शून्य;
	काष्ठा platक्रमm_device *pdev;

	अगर (adj->मुख्य_noc) अणु
		node_data->qos_dev = dev;
		dev_dbg(dev, "icc node %s[%d] is main noc itself\n",
			node->name, node->id);
	पूर्ण अन्यथा अणु
		dn = of_parse_phandle(dev->of_node, adj->phandle_name, 0);
		अगर (!dn) अणु
			dev_warn(dev, "Failed to parse %s\n",
				 adj->phandle_name);
			वापस -ENODEV;
		पूर्ण
		/* Allow scaling to be disabled on a per-node basis */
		अगर (!of_device_is_available(dn)) अणु
			dev_warn(dev, "Missing property %s, skip scaling %s\n",
				 adj->phandle_name, node->name);
			of_node_put(dn);
			वापस 0;
		पूर्ण

		pdev = of_find_device_by_node(dn);
		of_node_put(dn);
		अगर (!pdev) अणु
			dev_warn(dev, "node %s[%d] missing device for %pOF\n",
				 node->name, node->id, dn);
			वापस -EPROBE_DEFER;
		पूर्ण
		node_data->qos_dev = &pdev->dev;
		dev_dbg(dev, "node %s[%d] has device node %pOF\n",
			node->name, node->id, dn);
	पूर्ण

	वापस dev_pm_qos_add_request(node_data->qos_dev,
				      &node_data->qos_req,
				      DEV_PM_QOS_MIN_FREQUENCY, 0);
पूर्ण

अटल काष्ठा icc_node *imx_icc_node_add(काष्ठा icc_provider *provider,
					 स्थिर काष्ठा imx_icc_node_desc *node_desc)
अणु
	काष्ठा device *dev = provider->dev;
	काष्ठा imx_icc_node *node_data;
	काष्ठा icc_node *node;
	पूर्णांक ret;

	node = icc_node_create(node_desc->id);
	अगर (IS_ERR(node)) अणु
		dev_err(dev, "failed to create node %d\n", node_desc->id);
		वापस node;
	पूर्ण

	अगर (node->data) अणु
		dev_err(dev, "already created node %s id=%d\n",
			node_desc->name, node_desc->id);
		वापस ERR_PTR(-EEXIST);
	पूर्ण

	node_data = devm_kzalloc(dev, माप(*node_data), GFP_KERNEL);
	अगर (!node_data) अणु
		icc_node_destroy(node->id);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	node->name = node_desc->name;
	node->data = node_data;
	node_data->desc = node_desc;
	icc_node_add(node, provider);

	अगर (node_desc->adj) अणु
		ret = imx_icc_node_init_qos(provider, node);
		अगर (ret < 0) अणु
			imx_icc_node_destroy(node);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस node;
पूर्ण

अटल व्योम imx_icc_unरेजिस्टर_nodes(काष्ठा icc_provider *provider)
अणु
	काष्ठा icc_node *node, *पंचांगp;

	list_क्रम_each_entry_safe(node, पंचांगp, &provider->nodes, node_list)
		imx_icc_node_destroy(node);
पूर्ण

अटल पूर्णांक imx_icc_रेजिस्टर_nodes(काष्ठा icc_provider *provider,
				  स्थिर काष्ठा imx_icc_node_desc *descs,
				  पूर्णांक count)
अणु
	काष्ठा icc_onecell_data *provider_data = provider->data;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा icc_node *node;
		स्थिर काष्ठा imx_icc_node_desc *node_desc = &descs[i];
		माप_प्रकार j;

		node = imx_icc_node_add(provider, node_desc);
		अगर (IS_ERR(node)) अणु
			ret = dev_err_probe(provider->dev, PTR_ERR(node),
					    "failed to add %s\n", node_desc->name);
			जाओ err;
		पूर्ण
		provider_data->nodes[node->id] = node;

		क्रम (j = 0; j < node_desc->num_links; j++) अणु
			ret = icc_link_create(node, node_desc->links[j]);
			अगर (ret) अणु
				dev_err(provider->dev, "failed to link node %d to %d: %d\n",
					node->id, node_desc->links[j], ret);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err:
	imx_icc_unरेजिस्टर_nodes(provider);

	वापस ret;
पूर्ण

अटल पूर्णांक get_max_node_id(काष्ठा imx_icc_node_desc *nodes, पूर्णांक nodes_count)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < nodes_count; ++i)
		अगर (nodes[i].id > ret)
			ret = nodes[i].id;

	वापस ret;
पूर्ण

पूर्णांक imx_icc_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
		     काष्ठा imx_icc_node_desc *nodes, पूर्णांक nodes_count)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा icc_onecell_data *data;
	काष्ठा icc_provider *provider;
	पूर्णांक max_node_id;
	पूर्णांक ret;

	/* icc_onecell_data is indexed by node_id, unlike nodes param */
	max_node_id = get_max_node_id(nodes, nodes_count);
	data = devm_kzalloc(dev, काष्ठा_size(data, nodes, max_node_id),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->num_nodes = max_node_id;

	provider = devm_kzalloc(dev, माप(*provider), GFP_KERNEL);
	अगर (!provider)
		वापस -ENOMEM;
	provider->set = imx_icc_set;
	provider->aggregate = icc_std_aggregate;
	provider->xlate = of_icc_xlate_onecell;
	provider->data = data;
	provider->dev = dev->parent;
	platक्रमm_set_drvdata(pdev, provider);

	ret = icc_provider_add(provider);
	अगर (ret) अणु
		dev_err(dev, "error adding interconnect provider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = imx_icc_रेजिस्टर_nodes(provider, nodes, nodes_count);
	अगर (ret)
		जाओ provider_del;

	वापस 0;

provider_del:
	icc_provider_del(provider);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_icc_रेजिस्टर);

पूर्णांक imx_icc_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा icc_provider *provider = platक्रमm_get_drvdata(pdev);

	imx_icc_unरेजिस्टर_nodes(provider);

	वापस icc_provider_del(provider);
पूर्ण
EXPORT_SYMBOL_GPL(imx_icc_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
