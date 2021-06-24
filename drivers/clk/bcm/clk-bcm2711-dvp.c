<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright 2020 Cerno

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset/reset-simple.h>

#घोषणा DVP_HT_RPI_SW_INIT	0x04
#घोषणा DVP_HT_RPI_MISC_CONFIG	0x08

#घोषणा NR_CLOCKS	2
#घोषणा NR_RESETS	6

काष्ठा clk_dvp अणु
	काष्ठा clk_hw_onecell_data	*data;
	काष्ठा reset_simple_data	reset;
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data clk_dvp_parent = अणु
	.index	= 0,
पूर्ण;

अटल पूर्णांक clk_dvp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw_onecell_data *data;
	काष्ठा clk_dvp *dvp;
	व्योम __iomem *base;
	पूर्णांक ret;

	dvp = devm_kzalloc(&pdev->dev, माप(*dvp), GFP_KERNEL);
	अगर (!dvp)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, dvp);

	dvp->data = devm_kzalloc(&pdev->dev,
				 काष्ठा_size(dvp->data, hws, NR_CLOCKS),
				 GFP_KERNEL);
	अगर (!dvp->data)
		वापस -ENOMEM;
	data = dvp->data;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	dvp->reset.rcdev.owner = THIS_MODULE;
	dvp->reset.rcdev.nr_resets = NR_RESETS;
	dvp->reset.rcdev.ops = &reset_simple_ops;
	dvp->reset.rcdev.of_node = pdev->dev.of_node;
	dvp->reset.membase = base + DVP_HT_RPI_SW_INIT;
	spin_lock_init(&dvp->reset.lock);

	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &dvp->reset.rcdev);
	अगर (ret)
		वापस ret;

	data->hws[0] = clk_hw_रेजिस्टर_gate_parent_data(&pdev->dev,
							"hdmi0-108MHz",
							&clk_dvp_parent, 0,
							base + DVP_HT_RPI_MISC_CONFIG, 3,
							CLK_GATE_SET_TO_DISABLE,
							&dvp->reset.lock);
	अगर (IS_ERR(data->hws[0]))
		वापस PTR_ERR(data->hws[0]);

	data->hws[1] = clk_hw_रेजिस्टर_gate_parent_data(&pdev->dev,
							"hdmi1-108MHz",
							&clk_dvp_parent, 0,
							base + DVP_HT_RPI_MISC_CONFIG, 4,
							CLK_GATE_SET_TO_DISABLE,
							&dvp->reset.lock);
	अगर (IS_ERR(data->hws[1])) अणु
		ret = PTR_ERR(data->hws[1]);
		जाओ unरेजिस्टर_clk0;
	पूर्ण

	data->num = NR_CLOCKS;
	ret = of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_onecell_get,
				     data);
	अगर (ret)
		जाओ unरेजिस्टर_clk1;

	वापस 0;

unरेजिस्टर_clk1:
	clk_hw_unरेजिस्टर_gate(data->hws[1]);

unरेजिस्टर_clk0:
	clk_hw_unरेजिस्टर_gate(data->hws[0]);
	वापस ret;
पूर्ण;

अटल पूर्णांक clk_dvp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_dvp *dvp = platक्रमm_get_drvdata(pdev);
	काष्ठा clk_hw_onecell_data *data = dvp->data;

	clk_hw_unरेजिस्टर_gate(data->hws[1]);
	clk_hw_unरेजिस्टर_gate(data->hws[0]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_dvp_dt_ids[] = अणु
	अणु .compatible = "brcm,brcm2711-dvp", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_dvp_dt_ids);

अटल काष्ठा platक्रमm_driver clk_dvp_driver = अणु
	.probe	= clk_dvp_probe,
	.हटाओ	= clk_dvp_हटाओ,
	.driver	= अणु
		.name		= "brcm2711-dvp",
		.of_match_table	= clk_dvp_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(clk_dvp_driver);

MODULE_AUTHOR("Maxime Ripard <maxime@cerno.tech>");
MODULE_DESCRIPTION("BCM2711 DVP clock driver");
MODULE_LICENSE("GPL");
