<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, National Instruments Corp.
 * Copyright (c) 2017, Xilinx Inc
 *
 * FPGA Bridge Driver क्रम the Xilinx LogiCORE Partial Reconfiguration
 * Decoupler IP Core.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/fpga/fpga-bridge.h>

#घोषणा CTRL_CMD_DECOUPLE	BIT(0)
#घोषणा CTRL_CMD_COUPLE		0
#घोषणा CTRL_OFFSET		0

काष्ठा xlnx_config_data अणु
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा xlnx_pr_decoupler_data अणु
	स्थिर काष्ठा xlnx_config_data *ipconfig;
	व्योम __iomem *io_base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत व्योम xlnx_pr_decoupler_ग_लिखो(काष्ठा xlnx_pr_decoupler_data *d,
					   u32 offset, u32 val)
अणु
	ग_लिखोl(val, d->io_base + offset);
पूर्ण

अटल अंतरभूत u32 xlnx_pr_decouple_पढ़ो(स्थिर काष्ठा xlnx_pr_decoupler_data *d,
					u32 offset)
अणु
	वापस पढ़ोl(d->io_base + offset);
पूर्ण

अटल पूर्णांक xlnx_pr_decoupler_enable_set(काष्ठा fpga_bridge *bridge, bool enable)
अणु
	पूर्णांक err;
	काष्ठा xlnx_pr_decoupler_data *priv = bridge->priv;

	err = clk_enable(priv->clk);
	अगर (err)
		वापस err;

	अगर (enable)
		xlnx_pr_decoupler_ग_लिखो(priv, CTRL_OFFSET, CTRL_CMD_COUPLE);
	अन्यथा
		xlnx_pr_decoupler_ग_लिखो(priv, CTRL_OFFSET, CTRL_CMD_DECOUPLE);

	clk_disable(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_pr_decoupler_enable_show(काष्ठा fpga_bridge *bridge)
अणु
	स्थिर काष्ठा xlnx_pr_decoupler_data *priv = bridge->priv;
	u32 status;
	पूर्णांक err;

	err = clk_enable(priv->clk);
	अगर (err)
		वापस err;

	status = पढ़ोl(priv->io_base);

	clk_disable(priv->clk);

	वापस !status;
पूर्ण

अटल स्थिर काष्ठा fpga_bridge_ops xlnx_pr_decoupler_br_ops = अणु
	.enable_set = xlnx_pr_decoupler_enable_set,
	.enable_show = xlnx_pr_decoupler_enable_show,
पूर्ण;

अटल स्थिर काष्ठा xlnx_config_data decoupler_config = अणु
	.name = "Xilinx PR Decoupler",
पूर्ण;

अटल स्थिर काष्ठा xlnx_config_data shutकरोwn_config = अणु
	.name = "Xilinx DFX AXI Shutdown Manager",
पूर्ण;

अटल स्थिर काष्ठा of_device_id xlnx_pr_decoupler_of_match[] = अणु
	अणु .compatible = "xlnx,pr-decoupler-1.00", .data = &decoupler_config पूर्ण,
	अणु .compatible = "xlnx,pr-decoupler", .data = &decoupler_config पूर्ण,
	अणु .compatible = "xlnx,dfx-axi-shutdown-manager-1.00",
					.data = &shutकरोwn_config पूर्ण,
	अणु .compatible = "xlnx,dfx-axi-shutdown-manager",
					.data = &shutकरोwn_config पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_pr_decoupler_of_match);

अटल पूर्णांक xlnx_pr_decoupler_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा xlnx_pr_decoupler_data *priv;
	काष्ठा fpga_bridge *br;
	पूर्णांक err;
	काष्ठा resource *res;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (np) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(xlnx_pr_decoupler_of_match, np);
		अगर (match && match->data)
			priv->ipconfig = match->data;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->io_base))
		वापस PTR_ERR(priv->io_base);

	priv->clk = devm_clk_get(&pdev->dev, "aclk");
	अगर (IS_ERR(priv->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->clk),
				     "input clock not found\n");

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to enable clock\n");
		वापस err;
	पूर्ण

	clk_disable(priv->clk);

	br = devm_fpga_bridge_create(&pdev->dev, priv->ipconfig->name,
				     &xlnx_pr_decoupler_br_ops, priv);
	अगर (!br) अणु
		err = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, br);

	err = fpga_bridge_रेजिस्टर(br);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to register %s",
			priv->ipconfig->name);
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk:
	clk_unprepare(priv->clk);

	वापस err;
पूर्ण

अटल पूर्णांक xlnx_pr_decoupler_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_bridge *bridge = platक्रमm_get_drvdata(pdev);
	काष्ठा xlnx_pr_decoupler_data *p = bridge->priv;

	fpga_bridge_unरेजिस्टर(bridge);

	clk_unprepare(p->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xlnx_pr_decoupler_driver = अणु
	.probe = xlnx_pr_decoupler_probe,
	.हटाओ = xlnx_pr_decoupler_हटाओ,
	.driver = अणु
		.name = "xlnx_pr_decoupler",
		.of_match_table = of_match_ptr(xlnx_pr_decoupler_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlnx_pr_decoupler_driver);

MODULE_DESCRIPTION("Xilinx Partial Reconfiguration Decoupler");
MODULE_AUTHOR("Moritz Fischer <mdf@kernel.org>");
MODULE_AUTHOR("Michal Simek <michal.simek@xilinx.com>");
MODULE_LICENSE("GPL v2");
