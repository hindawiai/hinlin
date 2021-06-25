<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ulpi.h>

#समावेश "ci.h"

काष्ठा ci_hdrc_usb2_priv अणु
	काष्ठा platक्रमm_device	*ci_pdev;
	काष्ठा clk		*clk;
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_platक्रमm_data ci_शेष_pdata = अणु
	.capoffset	= DEF_CAPOFFSET,
	.flags		= CI_HDRC_DISABLE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_platक्रमm_data ci_zynq_pdata = अणु
	.capoffset	= DEF_CAPOFFSET,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_platक्रमm_data ci_zevio_pdata = अणु
	.capoffset	= DEF_CAPOFFSET,
	.flags		= CI_HDRC_REGS_SHARED | CI_HDRC_FORCE_FULLSPEED,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ci_hdrc_usb2_of_match[] = अणु
	अणु .compatible = "chipidea,usb2" पूर्ण,
	अणु .compatible = "xlnx,zynq-usb-2.20a", .data = &ci_zynq_pdata पूर्ण,
	अणु .compatible = "lsi,zevio-usb", .data = &ci_zevio_pdata पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ci_hdrc_usb2_of_match);

अटल पूर्णांक ci_hdrc_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ci_hdrc_usb2_priv *priv;
	काष्ठा ci_hdrc_platक्रमm_data *ci_pdata = dev_get_platdata(dev);
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;

	अगर (!ci_pdata) अणु
		ci_pdata = devm_kदो_स्मृति(dev, माप(*ci_pdata), GFP_KERNEL);
		अगर (!ci_pdata)
			वापस -ENOMEM;
		*ci_pdata = ci_शेष_pdata;	/* काष्ठा copy */
	पूर्ण

	match = of_match_device(ci_hdrc_usb2_of_match, &pdev->dev);
	अगर (match && match->data) अणु
		/* काष्ठा copy */
		*ci_pdata = *(काष्ठा ci_hdrc_platक्रमm_data *)match->data;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable the clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ci_pdata->name = dev_name(dev);

	priv->ci_pdev = ci_hdrc_add_device(dev, pdev->resource,
					   pdev->num_resources, ci_pdata);
	अगर (IS_ERR(priv->ci_pdev)) अणु
		ret = PTR_ERR(priv->ci_pdev);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev,
				"failed to register ci_hdrc platform device: %d\n",
				ret);
		जाओ clk_err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	pm_runसमय_no_callbacks(dev);
	pm_runसमय_enable(dev);

	वापस 0;

clk_err:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ci_hdrc_usb2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc_usb2_priv *priv = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	ci_hdrc_हटाओ_device(priv->ci_pdev);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ci_hdrc_usb2_driver = अणु
	.probe	= ci_hdrc_usb2_probe,
	.हटाओ	= ci_hdrc_usb2_हटाओ,
	.driver	= अणु
		.name		= "chipidea-usb2",
		.of_match_table	= of_match_ptr(ci_hdrc_usb2_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ci_hdrc_usb2_driver);

MODULE_DESCRIPTION("ChipIdea HDRC USB2 binding for ci13xxx");
MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_LICENSE("GPL");
