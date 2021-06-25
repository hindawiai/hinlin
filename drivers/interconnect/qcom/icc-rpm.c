<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Linaro Ltd
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "smd-rpm.h"
#समावेश "icc-rpm.h"

अटल पूर्णांक qcom_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा qcom_icc_provider *qp;
	काष्ठा qcom_icc_node *qn;
	काष्ठा icc_provider *provider;
	काष्ठा icc_node *n;
	u64 sum_bw;
	u64 max_peak_bw;
	u64 rate;
	u32 agg_avg = 0;
	u32 agg_peak = 0;
	पूर्णांक ret, i;

	qn = src->data;
	provider = src->provider;
	qp = to_qcom_provider(provider);

	list_क्रम_each_entry(n, &provider->nodes, node_list)
		provider->aggregate(n, 0, n->avg_bw, n->peak_bw,
				    &agg_avg, &agg_peak);

	sum_bw = icc_units_to_bps(agg_avg);
	max_peak_bw = icc_units_to_bps(agg_peak);

	/* send bandwidth request message to the RPM processor */
	अगर (qn->mas_rpm_id != -1) अणु
		ret = qcom_icc_rpm_smd_send(QCOM_SMD_RPM_ACTIVE_STATE,
					    RPM_BUS_MASTER_REQ,
					    qn->mas_rpm_id,
					    sum_bw);
		अगर (ret) अणु
			pr_err("qcom_icc_rpm_smd_send mas %d error %d\n",
			       qn->mas_rpm_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (qn->slv_rpm_id != -1) अणु
		ret = qcom_icc_rpm_smd_send(QCOM_SMD_RPM_ACTIVE_STATE,
					    RPM_BUS_SLAVE_REQ,
					    qn->slv_rpm_id,
					    sum_bw);
		अगर (ret) अणु
			pr_err("qcom_icc_rpm_smd_send slv %d error %d\n",
			       qn->slv_rpm_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	rate = max(sum_bw, max_peak_bw);

	करो_भाग(rate, qn->buswidth);

	अगर (qn->rate == rate)
		वापस 0;

	क्रम (i = 0; i < qp->num_clks; i++) अणु
		ret = clk_set_rate(qp->bus_clks[i].clk, rate);
		अगर (ret) अणु
			pr_err("%s clk_set_rate error: %d\n",
			       qp->bus_clks[i].id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	qn->rate = rate;

	वापस 0;
पूर्ण

पूर्णांक qnoc_probe(काष्ठा platक्रमm_device *pdev, माप_प्रकार cd_size, पूर्णांक cd_num,
	       स्थिर काष्ठा clk_bulk_data *cd)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा qcom_icc_desc *desc;
	काष्ठा icc_onecell_data *data;
	काष्ठा icc_provider *provider;
	काष्ठा qcom_icc_node **qnodes;
	काष्ठा qcom_icc_provider *qp;
	काष्ठा icc_node *node;
	माप_प्रकार num_nodes, i;
	पूर्णांक ret;

	/* रुको क्रम the RPM proxy */
	अगर (!qcom_icc_rpm_smd_available())
		वापस -EPROBE_DEFER;

	desc = of_device_get_match_data(dev);
	अगर (!desc)
		वापस -EINVAL;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	qp = devm_kzalloc(dev, माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस -ENOMEM;

	data = devm_kzalloc(dev, काष्ठा_size(data, nodes, num_nodes),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	qp->bus_clks = devm_kmemdup(dev, cd, cd_size,
				    GFP_KERNEL);
	अगर (!qp->bus_clks)
		वापस -ENOMEM;

	qp->num_clks = cd_num;
	ret = devm_clk_bulk_get(dev, qp->num_clks, qp->bus_clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(qp->num_clks, qp->bus_clks);
	अगर (ret)
		वापस ret;

	provider = &qp->provider;
	INIT_LIST_HEAD(&provider->nodes);
	provider->dev = dev;
	provider->set = qcom_icc_set;
	provider->aggregate = icc_std_aggregate;
	provider->xlate = of_icc_xlate_onecell;
	provider->data = data;

	ret = icc_provider_add(provider);
	अगर (ret) अणु
		dev_err(dev, "error adding interconnect provider: %d\n", ret);
		clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num_nodes; i++) अणु
		माप_प्रकार j;

		node = icc_node_create(qnodes[i]->id);
		अगर (IS_ERR(node)) अणु
			ret = PTR_ERR(node);
			जाओ err;
		पूर्ण

		node->name = qnodes[i]->name;
		node->data = qnodes[i];
		icc_node_add(node, provider);

		क्रम (j = 0; j < qnodes[i]->num_links; j++)
			icc_link_create(node, qnodes[i]->links[j]);

		data->nodes[i] = node;
	पूर्ण
	data->num_nodes = num_nodes;

	platक्रमm_set_drvdata(pdev, qp);

	वापस 0;
err:
	icc_nodes_हटाओ(provider);
	clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
	icc_provider_del(provider);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qnoc_probe);

पूर्णांक qnoc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_icc_provider *qp = platक्रमm_get_drvdata(pdev);

	icc_nodes_हटाओ(&qp->provider);
	clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
	वापस icc_provider_del(&qp->provider);
पूर्ण
EXPORT_SYMBOL(qnoc_हटाओ);
