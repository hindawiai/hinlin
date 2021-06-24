<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Free Electrons
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

काष्ठा sun6i_drc अणु
	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;
	काष्ठा reset_control	*reset;
पूर्ण;

अटल पूर्णांक sun6i_drc_bind(काष्ठा device *dev, काष्ठा device *master,
			 व्योम *data)
अणु
	काष्ठा sun6i_drc *drc;
	पूर्णांक ret;

	drc = devm_kzalloc(dev, माप(*drc), GFP_KERNEL);
	अगर (!drc)
		वापस -ENOMEM;
	dev_set_drvdata(dev, drc);

	drc->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(drc->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(drc->reset);
	पूर्ण

	ret = reset_control_deनिश्चित(drc->reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert our reset line\n");
		वापस ret;
	पूर्ण

	drc->bus_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(drc->bus_clk)) अणु
		dev_err(dev, "Couldn't get our bus clock\n");
		ret = PTR_ERR(drc->bus_clk);
		जाओ err_निश्चित_reset;
	पूर्ण
	clk_prepare_enable(drc->bus_clk);

	drc->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(drc->mod_clk)) अणु
		dev_err(dev, "Couldn't get our mod clock\n");
		ret = PTR_ERR(drc->mod_clk);
		जाओ err_disable_bus_clk;
	पूर्ण

	ret = clk_set_rate_exclusive(drc->mod_clk, 300000000);
	अगर (ret) अणु
		dev_err(dev, "Couldn't set the module clock frequency\n");
		जाओ err_disable_bus_clk;
	पूर्ण

	clk_prepare_enable(drc->mod_clk);

	वापस 0;

err_disable_bus_clk:
	clk_disable_unprepare(drc->bus_clk);
err_निश्चित_reset:
	reset_control_निश्चित(drc->reset);
	वापस ret;
पूर्ण

अटल व्योम sun6i_drc_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा sun6i_drc *drc = dev_get_drvdata(dev);

	clk_rate_exclusive_put(drc->mod_clk);
	clk_disable_unprepare(drc->mod_clk);
	clk_disable_unprepare(drc->bus_clk);
	reset_control_निश्चित(drc->reset);
पूर्ण

अटल स्थिर काष्ठा component_ops sun6i_drc_ops = अणु
	.bind	= sun6i_drc_bind,
	.unbind	= sun6i_drc_unbind,
पूर्ण;

अटल पूर्णांक sun6i_drc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun6i_drc_ops);
पूर्ण

अटल पूर्णांक sun6i_drc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun6i_drc_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_drc_of_table[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-drc" पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31s-drc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-drc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-drc" पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-drc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_drc_of_table);

अटल काष्ठा platक्रमm_driver sun6i_drc_platक्रमm_driver = अणु
	.probe		= sun6i_drc_probe,
	.हटाओ		= sun6i_drc_हटाओ,
	.driver		= अणु
		.name		= "sun6i-drc",
		.of_match_table	= sun6i_drc_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_drc_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A31 Dynamic Range Control (DRC) Driver");
MODULE_LICENSE("GPL");
