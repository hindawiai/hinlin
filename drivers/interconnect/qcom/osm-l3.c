<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/पूर्णांकerconnect/qcom,osm-l3.h>

#समावेश "sc7180.h"
#समावेश "sdm845.h"
#समावेश "sm8150.h"
#समावेश "sm8250.h"

#घोषणा LUT_MAX_ENTRIES			40U
#घोषणा LUT_SRC				GENMASK(31, 30)
#घोषणा LUT_L_VAL			GENMASK(7, 0)
#घोषणा CLK_HW_DIV			2

/* OSM Register offsets */
#घोषणा REG_ENABLE			0x0
#घोषणा OSM_LUT_ROW_SIZE		32
#घोषणा OSM_REG_FREQ_LUT		0x110
#घोषणा OSM_REG_PERF_STATE		0x920

/* EPSS Register offsets */
#घोषणा EPSS_LUT_ROW_SIZE		4
#घोषणा EPSS_REG_FREQ_LUT		0x100
#घोषणा EPSS_REG_PERF_STATE		0x320

#घोषणा OSM_L3_MAX_LINKS		1

#घोषणा to_qcom_provider(_provider) \
	container_of(_provider, काष्ठा qcom_osm_l3_icc_provider, provider)

काष्ठा qcom_osm_l3_icc_provider अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक max_state;
	अचिन्हित पूर्णांक reg_perf_state;
	अचिन्हित दीर्घ lut_tables[LUT_MAX_ENTRIES];
	काष्ठा icc_provider provider;
पूर्ण;

/**
 * काष्ठा qcom_icc_node - Qualcomm specअगरic पूर्णांकerconnect nodes
 * @name: the node name used in debugfs
 * @links: an array of nodes where we can go next जबतक traversing
 * @id: a unique node identअगरier
 * @num_links: the total number of @links
 * @buswidth: width of the पूर्णांकerconnect between a node and the bus
 */
काष्ठा qcom_icc_node अणु
	स्थिर अक्षर *name;
	u16 links[OSM_L3_MAX_LINKS];
	u16 id;
	u16 num_links;
	u16 buswidth;
पूर्ण;

काष्ठा qcom_icc_desc अणु
	स्थिर काष्ठा qcom_icc_node **nodes;
	माप_प्रकार num_nodes;
	अचिन्हित पूर्णांक lut_row_size;
	अचिन्हित पूर्णांक reg_freq_lut;
	अचिन्हित पूर्णांक reg_perf_state;
पूर्ण;

#घोषणा DEFINE_QNODE(_name, _id, _buswidth, ...)			\
	अटल स्थिर काष्ठा qcom_icc_node _name = अणु			\
		.name = #_name,						\
		.id = _id,						\
		.buswidth = _buswidth,					\
		.num_links = ARRAY_SIZE(((पूर्णांक[])अणु __VA_ARGS__ पूर्ण)),	\
		.links = अणु __VA_ARGS__ पूर्ण,				\
	पूर्ण

DEFINE_QNODE(sdm845_osm_apps_l3, SDM845_MASTER_OSM_L3_APPS, 16, SDM845_SLAVE_OSM_L3);
DEFINE_QNODE(sdm845_osm_l3, SDM845_SLAVE_OSM_L3, 16);

अटल स्थिर काष्ठा qcom_icc_node *sdm845_osm_l3_nodes[] = अणु
	[MASTER_OSM_L3_APPS] = &sdm845_osm_apps_l3,
	[SLAVE_OSM_L3] = &sdm845_osm_l3,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sdm845_icc_osm_l3 = अणु
	.nodes = sdm845_osm_l3_nodes,
	.num_nodes = ARRAY_SIZE(sdm845_osm_l3_nodes),
	.lut_row_size = OSM_LUT_ROW_SIZE,
	.reg_freq_lut = OSM_REG_FREQ_LUT,
	.reg_perf_state = OSM_REG_PERF_STATE,
पूर्ण;

DEFINE_QNODE(sc7180_osm_apps_l3, SC7180_MASTER_OSM_L3_APPS, 16, SC7180_SLAVE_OSM_L3);
DEFINE_QNODE(sc7180_osm_l3, SC7180_SLAVE_OSM_L3, 16);

अटल स्थिर काष्ठा qcom_icc_node *sc7180_osm_l3_nodes[] = अणु
	[MASTER_OSM_L3_APPS] = &sc7180_osm_apps_l3,
	[SLAVE_OSM_L3] = &sc7180_osm_l3,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sc7180_icc_osm_l3 = अणु
	.nodes = sc7180_osm_l3_nodes,
	.num_nodes = ARRAY_SIZE(sc7180_osm_l3_nodes),
	.lut_row_size = OSM_LUT_ROW_SIZE,
	.reg_freq_lut = OSM_REG_FREQ_LUT,
	.reg_perf_state = OSM_REG_PERF_STATE,
पूर्ण;

DEFINE_QNODE(sm8150_osm_apps_l3, SM8150_MASTER_OSM_L3_APPS, 32, SM8150_SLAVE_OSM_L3);
DEFINE_QNODE(sm8150_osm_l3, SM8150_SLAVE_OSM_L3, 32);

अटल स्थिर काष्ठा qcom_icc_node *sm8150_osm_l3_nodes[] = अणु
	[MASTER_OSM_L3_APPS] = &sm8150_osm_apps_l3,
	[SLAVE_OSM_L3] = &sm8150_osm_l3,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sm8150_icc_osm_l3 = अणु
	.nodes = sm8150_osm_l3_nodes,
	.num_nodes = ARRAY_SIZE(sm8150_osm_l3_nodes),
	.lut_row_size = OSM_LUT_ROW_SIZE,
	.reg_freq_lut = OSM_REG_FREQ_LUT,
	.reg_perf_state = OSM_REG_PERF_STATE,
पूर्ण;

DEFINE_QNODE(sm8250_epss_apps_l3, SM8250_MASTER_EPSS_L3_APPS, 32, SM8250_SLAVE_EPSS_L3);
DEFINE_QNODE(sm8250_epss_l3, SM8250_SLAVE_EPSS_L3, 32);

अटल स्थिर काष्ठा qcom_icc_node *sm8250_epss_l3_nodes[] = अणु
	[MASTER_EPSS_L3_APPS] = &sm8250_epss_apps_l3,
	[SLAVE_EPSS_L3_SHARED] = &sm8250_epss_l3,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sm8250_icc_epss_l3 = अणु
	.nodes = sm8250_epss_l3_nodes,
	.num_nodes = ARRAY_SIZE(sm8250_epss_l3_nodes),
	.lut_row_size = EPSS_LUT_ROW_SIZE,
	.reg_freq_lut = EPSS_REG_FREQ_LUT,
	.reg_perf_state = EPSS_REG_PERF_STATE,
पूर्ण;

अटल पूर्णांक qcom_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा qcom_osm_l3_icc_provider *qp;
	काष्ठा icc_provider *provider;
	स्थिर काष्ठा qcom_icc_node *qn;
	काष्ठा icc_node *n;
	अचिन्हित पूर्णांक index;
	u32 agg_peak = 0;
	u32 agg_avg = 0;
	u64 rate;

	qn = src->data;
	provider = src->provider;
	qp = to_qcom_provider(provider);

	list_क्रम_each_entry(n, &provider->nodes, node_list)
		provider->aggregate(n, 0, n->avg_bw, n->peak_bw,
				    &agg_avg, &agg_peak);

	rate = max(agg_avg, agg_peak);
	rate = icc_units_to_bps(rate);
	करो_भाग(rate, qn->buswidth);

	क्रम (index = 0; index < qp->max_state - 1; index++) अणु
		अगर (qp->lut_tables[index] >= rate)
			अवरोध;
	पूर्ण

	ग_लिखोl_relaxed(index, qp->base + qp->reg_perf_state);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_osm_l3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_osm_l3_icc_provider *qp = platक्रमm_get_drvdata(pdev);

	icc_nodes_हटाओ(&qp->provider);
	वापस icc_provider_del(&qp->provider);
पूर्ण

अटल पूर्णांक qcom_osm_l3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 info, src, lval, i, prev_freq = 0, freq;
	अटल अचिन्हित दीर्घ hw_rate, xo_rate;
	काष्ठा qcom_osm_l3_icc_provider *qp;
	स्थिर काष्ठा qcom_icc_desc *desc;
	काष्ठा icc_onecell_data *data;
	काष्ठा icc_provider *provider;
	स्थिर काष्ठा qcom_icc_node **qnodes;
	काष्ठा icc_node *node;
	माप_प्रकार num_nodes;
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

	hw_rate = clk_get_rate(clk) / CLK_HW_DIV;
	clk_put(clk);

	qp = devm_kzalloc(&pdev->dev, माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस -ENOMEM;

	qp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(qp->base))
		वापस PTR_ERR(qp->base);

	/* HW should be in enabled state to proceed */
	अगर (!(पढ़ोl_relaxed(qp->base + REG_ENABLE) & 0x1)) अणु
		dev_err(&pdev->dev, "error hardware not enabled\n");
		वापस -ENODEV;
	पूर्ण

	desc = device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	qp->reg_perf_state = desc->reg_perf_state;

	क्रम (i = 0; i < LUT_MAX_ENTRIES; i++) अणु
		info = पढ़ोl_relaxed(qp->base + desc->reg_freq_lut +
				     i * desc->lut_row_size);
		src = FIELD_GET(LUT_SRC, info);
		lval = FIELD_GET(LUT_L_VAL, info);
		अगर (src)
			freq = xo_rate * lval;
		अन्यथा
			freq = hw_rate;

		/* Two of the same frequencies signअगरy end of table */
		अगर (i > 0 && prev_freq == freq)
			अवरोध;

		dev_dbg(&pdev->dev, "index=%d freq=%d\n", i, freq);

		qp->lut_tables[i] = freq;
		prev_freq = freq;
	पूर्ण
	qp->max_state = i;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	data = devm_kसुस्मृति(&pdev->dev, num_nodes, माप(*node), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	provider = &qp->provider;
	provider->dev = &pdev->dev;
	provider->set = qcom_icc_set;
	provider->aggregate = icc_std_aggregate;
	provider->xlate = of_icc_xlate_onecell;
	INIT_LIST_HEAD(&provider->nodes);
	provider->data = data;

	ret = icc_provider_add(provider);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error adding interconnect provider\n");
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
		/* Cast away स्थिर and add it back in qcom_icc_set() */
		node->data = (व्योम *)qnodes[i];
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
	icc_provider_del(provider);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id osm_l3_of_match[] = अणु
	अणु .compatible = "qcom,sc7180-osm-l3", .data = &sc7180_icc_osm_l3 पूर्ण,
	अणु .compatible = "qcom,sdm845-osm-l3", .data = &sdm845_icc_osm_l3 पूर्ण,
	अणु .compatible = "qcom,sm8150-osm-l3", .data = &sm8150_icc_osm_l3 पूर्ण,
	अणु .compatible = "qcom,sm8250-epss-l3", .data = &sm8250_icc_epss_l3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, osm_l3_of_match);

अटल काष्ठा platक्रमm_driver osm_l3_driver = अणु
	.probe = qcom_osm_l3_probe,
	.हटाओ = qcom_osm_l3_हटाओ,
	.driver = अणु
		.name = "osm-l3",
		.of_match_table = osm_l3_of_match,
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(osm_l3_driver);

MODULE_DESCRIPTION("Qualcomm OSM L3 interconnect driver");
MODULE_LICENSE("GPL v2");
