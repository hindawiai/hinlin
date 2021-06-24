<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip Image Sensor Controller (ISC) driver
 *
 * Copyright (C) 2016-2019 Microchip Technology, Inc.
 *
 * Author: Songjun Wu
 * Author: Eugen Hristev <eugen.hristev@microchip.com>
 *
 *
 * Sensor-->PFE-->WB-->CFA-->CC-->GAM-->CSC-->CBC-->SUB-->RLP-->DMA
 *
 * ISC video pipeline पूर्णांकegrates the following submodules:
 * PFE: Parallel Front End to sample the camera sensor input stream
 *  WB: Programmable white balance in the Bayer करोमुख्य
 * CFA: Color filter array पूर्णांकerpolation module
 *  CC: Programmable color correction
 * GAM: Gamma correction
 * CSC: Programmable color space conversion
 * CBC: Contrast and Brightness control
 * SUB: This module perक्रमms YCbCr444 to YCbCr420 chrominance subsampling
 * RLP: This module perक्रमms rounding, range limiting
 *      and packing of the incoming data
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "atmel-isc-regs.h"
#समावेश "atmel-isc.h"

#घोषणा ISC_MAX_SUPPORT_WIDTH   2592
#घोषणा ISC_MAX_SUPPORT_HEIGHT  1944

#घोषणा ISC_CLK_MAX_DIV		255

अटल पूर्णांक isc_parse_dt(काष्ठा device *dev, काष्ठा isc_device *isc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *epn = शून्य;
	काष्ठा isc_subdev_entity *subdev_entity;
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;

	INIT_LIST_HEAD(&isc->subdev_entities);

	जबतक (1) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_epn = अणु .bus_type = 0 पूर्ण;

		epn = of_graph_get_next_endpoपूर्णांक(np, epn);
		अगर (!epn)
			वापस 0;

		ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(epn),
						 &v4l2_epn);
		अगर (ret) अणु
			ret = -EINVAL;
			dev_err(dev, "Could not parse the endpoint\n");
			अवरोध;
		पूर्ण

		subdev_entity = devm_kzalloc(dev, माप(*subdev_entity),
					     GFP_KERNEL);
		अगर (!subdev_entity) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		subdev_entity->epn = epn;

		flags = v4l2_epn.bus.parallel.flags;

		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			subdev_entity->pfe_cfg0 = ISC_PFE_CFG0_HPOL_LOW;

		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_VPOL_LOW;

		अगर (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_PPOL_LOW;

		अगर (v4l2_epn.bus_type == V4L2_MBUS_BT656)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_CCIR_CRC |
					ISC_PFE_CFG0_CCIR656;

		list_add_tail(&subdev_entity->list, &isc->subdev_entities);
	पूर्ण
	of_node_put(epn);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_isc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा isc_device *isc;
	काष्ठा resource *res;
	व्योम __iomem *io_base;
	काष्ठा isc_subdev_entity *subdev_entity;
	पूर्णांक irq;
	पूर्णांक ret;

	isc = devm_kzalloc(dev, माप(*isc), GFP_KERNEL);
	अगर (!isc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, isc);
	isc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	isc->regmap = devm_regmap_init_mmio(dev, io_base, &isc_regmap_config);
	अगर (IS_ERR(isc->regmap)) अणु
		ret = PTR_ERR(isc->regmap);
		dev_err(dev, "failed to init register map: %d\n", ret);
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, isc_पूर्णांकerrupt, 0,
			       ATMEL_ISC_NAME, isc);
	अगर (ret < 0) अणु
		dev_err(dev, "can't register ISR for IRQ %u (ret=%i)\n",
			irq, ret);
		वापस ret;
	पूर्ण

	ret = isc_pipeline_init(isc);
	अगर (ret)
		वापस ret;

	isc->hघड़ी = devm_clk_get(dev, "hclock");
	अगर (IS_ERR(isc->hघड़ी)) अणु
		ret = PTR_ERR(isc->hघड़ी);
		dev_err(dev, "failed to get hclock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(isc->hघड़ी);
	अगर (ret) अणु
		dev_err(dev, "failed to enable hclock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = isc_clk_init(isc);
	अगर (ret) अणु
		dev_err(dev, "failed to init isc clock: %d\n", ret);
		जाओ unprepare_hclk;
	पूर्ण

	isc->ispck = isc->isc_clks[ISC_ISPCK].clk;

	ret = clk_prepare_enable(isc->ispck);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ispck: %d\n", ret);
		जाओ unprepare_hclk;
	पूर्ण

	/* ispck should be greater or equal to hघड़ी */
	ret = clk_set_rate(isc->ispck, clk_get_rate(isc->hघड़ी));
	अगर (ret) अणु
		dev_err(dev, "failed to set ispck rate: %d\n", ret);
		जाओ unprepare_clk;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(dev, &isc->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev, "unable to register v4l2 device.\n");
		जाओ unprepare_clk;
	पूर्ण

	ret = isc_parse_dt(dev, isc);
	अगर (ret) अणु
		dev_err(dev, "fail to parse device tree\n");
		जाओ unरेजिस्टर_v4l2_device;
	पूर्ण

	अगर (list_empty(&isc->subdev_entities)) अणु
		dev_err(dev, "no subdev found\n");
		ret = -ENODEV;
		जाओ unरेजिस्टर_v4l2_device;
	पूर्ण

	list_क्रम_each_entry(subdev_entity, &isc->subdev_entities, list) अणु
		काष्ठा v4l2_async_subdev *asd;

		v4l2_async_notअगरier_init(&subdev_entity->notअगरier);

		asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
					&subdev_entity->notअगरier,
					of_fwnode_handle(subdev_entity->epn),
					काष्ठा v4l2_async_subdev);

		of_node_put(subdev_entity->epn);
		subdev_entity->epn = शून्य;

		अगर (IS_ERR(asd)) अणु
			ret = PTR_ERR(asd);
			जाओ cleanup_subdev;
		पूर्ण

		subdev_entity->notअगरier.ops = &isc_async_ops;

		ret = v4l2_async_notअगरier_रेजिस्टर(&isc->v4l2_dev,
						   &subdev_entity->notअगरier);
		अगर (ret) अणु
			dev_err(dev, "fail to register async notifier\n");
			जाओ cleanup_subdev;
		पूर्ण

		अगर (video_is_रेजिस्टरed(&isc->video_dev))
			अवरोध;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_request_idle(dev);

	वापस 0;

cleanup_subdev:
	isc_subdev_cleanup(isc);

unरेजिस्टर_v4l2_device:
	v4l2_device_unरेजिस्टर(&isc->v4l2_dev);

unprepare_clk:
	clk_disable_unprepare(isc->ispck);
unprepare_hclk:
	clk_disable_unprepare(isc->hघड़ी);

	isc_clk_cleanup(isc);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_isc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा isc_device *isc = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	isc_subdev_cleanup(isc);

	v4l2_device_unरेजिस्टर(&isc->v4l2_dev);

	clk_disable_unprepare(isc->ispck);
	clk_disable_unprepare(isc->hघड़ी);

	isc_clk_cleanup(isc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused isc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा isc_device *isc = dev_get_drvdata(dev);

	clk_disable_unprepare(isc->ispck);
	clk_disable_unprepare(isc->hघड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused isc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा isc_device *isc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(isc->hघड़ी);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(isc->ispck);
	अगर (ret)
		clk_disable_unprepare(isc->hघड़ी);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_isc_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(isc_runसमय_suspend, isc_runसमय_resume, शून्य)
पूर्ण;

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_isc_of_match[] = अणु
	अणु .compatible = "atmel,sama5d2-isc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_isc_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver aपंचांगel_isc_driver = अणु
	.probe	= aपंचांगel_isc_probe,
	.हटाओ	= aपंचांगel_isc_हटाओ,
	.driver	= अणु
		.name		= ATMEL_ISC_NAME,
		.pm		= &aपंचांगel_isc_dev_pm_ops,
		.of_match_table = of_match_ptr(aपंचांगel_isc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_isc_driver);

MODULE_AUTHOR("Songjun Wu");
MODULE_DESCRIPTION("The V4L2 driver for Atmel-ISC");
MODULE_LICENSE("GPL v2");
