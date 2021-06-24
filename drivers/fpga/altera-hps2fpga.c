<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA to/from HPS Bridge Driver क्रम Altera SoCFPGA Devices
 *
 *  Copyright (C) 2013-2016 Altera Corporation, All Rights Reserved.
 *
 * Includes this patch from the mailing list:
 *   fpga: altera-hps2fpga: fix HPS2FPGA bridge visibility to L3 masters
 *   Signed-off-by: Anम_से_दij Gustschin <agust@denx.de>
 */

/*
 * This driver manages bridges on a Altera SOCFPGA between the ARM host
 * processor प्रणाली (HPS) and the embedded FPGA.
 *
 * This driver supports enabling and disabling of the configured ports, which
 * allows क्रम safe reprogramming of the FPGA, assuming that the new FPGA image
 * uses the same port configuration.  Bridges must be disabled beक्रमe
 * reprogramming the FPGA and re-enabled after the FPGA has been programmed.
 */

#समावेश <linux/clk.h>
#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

#घोषणा ALT_L3_REMAP_OFST			0x0
#घोषणा ALT_L3_REMAP_MPUZERO_MSK		0x00000001
#घोषणा ALT_L3_REMAP_H2F_MSK			0x00000008
#घोषणा ALT_L3_REMAP_LWH2F_MSK			0x00000010

#घोषणा HPS2FPGA_BRIDGE_NAME			"hps2fpga"
#घोषणा LWHPS2FPGA_BRIDGE_NAME			"lwhps2fpga"
#घोषणा FPGA2HPS_BRIDGE_NAME			"fpga2hps"

काष्ठा altera_hps2fpga_data अणु
	स्थिर अक्षर *name;
	काष्ठा reset_control *bridge_reset;
	काष्ठा regmap *l3reg;
	अचिन्हित पूर्णांक remap_mask;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक alt_hps2fpga_enable_show(काष्ठा fpga_bridge *bridge)
अणु
	काष्ठा altera_hps2fpga_data *priv = bridge->priv;

	वापस reset_control_status(priv->bridge_reset);
पूर्ण

/* The L3 REMAP रेजिस्टर is ग_लिखो only, so keep a cached value. */
अटल अचिन्हित पूर्णांक l3_remap_shaकरोw;
अटल DEFINE_SPINLOCK(l3_remap_lock);

अटल पूर्णांक _alt_hps2fpga_enable_set(काष्ठा altera_hps2fpga_data *priv,
				    bool enable)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* bring bridge out of reset */
	अगर (enable)
		ret = reset_control_deनिश्चित(priv->bridge_reset);
	अन्यथा
		ret = reset_control_निश्चित(priv->bridge_reset);
	अगर (ret)
		वापस ret;

	/* Allow bridge to be visible to L3 masters or not */
	अगर (priv->remap_mask) अणु
		spin_lock_irqsave(&l3_remap_lock, flags);
		l3_remap_shaकरोw |= ALT_L3_REMAP_MPUZERO_MSK;

		अगर (enable)
			l3_remap_shaकरोw |= priv->remap_mask;
		अन्यथा
			l3_remap_shaकरोw &= ~priv->remap_mask;

		ret = regmap_ग_लिखो(priv->l3reg, ALT_L3_REMAP_OFST,
				   l3_remap_shaकरोw);
		spin_unlock_irqrestore(&l3_remap_lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक alt_hps2fpga_enable_set(काष्ठा fpga_bridge *bridge, bool enable)
अणु
	वापस _alt_hps2fpga_enable_set(bridge->priv, enable);
पूर्ण

अटल स्थिर काष्ठा fpga_bridge_ops altera_hps2fpga_br_ops = अणु
	.enable_set = alt_hps2fpga_enable_set,
	.enable_show = alt_hps2fpga_enable_show,
पूर्ण;

अटल काष्ठा altera_hps2fpga_data hps2fpga_data  = अणु
	.name = HPS2FPGA_BRIDGE_NAME,
	.remap_mask = ALT_L3_REMAP_H2F_MSK,
पूर्ण;

अटल काष्ठा altera_hps2fpga_data lwhps2fpga_data  = अणु
	.name = LWHPS2FPGA_BRIDGE_NAME,
	.remap_mask = ALT_L3_REMAP_LWH2F_MSK,
पूर्ण;

अटल काष्ठा altera_hps2fpga_data fpga2hps_data  = अणु
	.name = FPGA2HPS_BRIDGE_NAME,
पूर्ण;

अटल स्थिर काष्ठा of_device_id altera_fpga_of_match[] = अणु
	अणु .compatible = "altr,socfpga-hps2fpga-bridge",
	  .data = &hps2fpga_data पूर्ण,
	अणु .compatible = "altr,socfpga-lwhps2fpga-bridge",
	  .data = &lwhps2fpga_data पूर्ण,
	अणु .compatible = "altr,socfpga-fpga2hps-bridge",
	  .data = &fpga2hps_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक alt_fpga_bridge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा altera_hps2fpga_data *priv;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा fpga_bridge *br;
	u32 enable;
	पूर्णांक ret;

	of_id = of_match_device(altera_fpga_of_match, dev);
	अगर (!of_id) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	priv = (काष्ठा altera_hps2fpga_data *)of_id->data;

	priv->bridge_reset = of_reset_control_get_exclusive_by_index(dev->of_node,
								     0);
	अगर (IS_ERR(priv->bridge_reset)) अणु
		dev_err(dev, "Could not get %s reset control\n", priv->name);
		वापस PTR_ERR(priv->bridge_reset);
	पूर्ण

	अगर (priv->remap_mask) अणु
		priv->l3reg = syscon_regmap_lookup_by_compatible("altr,l3regs");
		अगर (IS_ERR(priv->l3reg)) अणु
			dev_err(dev, "regmap for altr,l3regs lookup failed\n");
			वापस PTR_ERR(priv->l3reg);
		पूर्ण
	पूर्ण

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "no clock specified\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable clock\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "bridge-enable", &enable)) अणु
		अगर (enable > 1) अणु
			dev_warn(dev, "invalid bridge-enable %u > 1\n", enable);
		पूर्ण अन्यथा अणु
			dev_info(dev, "%s bridge\n",
				 (enable ? "enabling" : "disabling"));

			ret = _alt_hps2fpga_enable_set(priv, enable);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	br = devm_fpga_bridge_create(dev, priv->name,
				     &altera_hps2fpga_br_ops, priv);
	अगर (!br) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, br);

	ret = fpga_bridge_रेजिस्टर(br);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक alt_fpga_bridge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_bridge *bridge = platक्रमm_get_drvdata(pdev);
	काष्ठा altera_hps2fpga_data *priv = bridge->priv;

	fpga_bridge_unरेजिस्टर(bridge);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, altera_fpga_of_match);

अटल काष्ठा platक्रमm_driver alt_fpga_bridge_driver = अणु
	.probe = alt_fpga_bridge_probe,
	.हटाओ = alt_fpga_bridge_हटाओ,
	.driver = अणु
		.name	= "altera_hps2fpga_bridge",
		.of_match_table = of_match_ptr(altera_fpga_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(alt_fpga_bridge_driver);

MODULE_DESCRIPTION("Altera SoCFPGA HPS to FPGA Bridge");
MODULE_AUTHOR("Alan Tull <atull@opensource.altera.com>");
MODULE_LICENSE("GPL v2");
