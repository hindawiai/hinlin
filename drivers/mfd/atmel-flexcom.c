<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel Flexcom
 *
 * Copyright (C) 2015 Aपंचांगel Corporation
 *
 * Author: Cyrille Pitchen <cyrille.pitchen@aपंचांगel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <dt-bindings/mfd/aपंचांगel-flexcom.h>

/* I/O रेजिस्टर offsets */
#घोषणा FLEX_MR		0x0	/* Mode Register */
#घोषणा FLEX_VERSION	0xfc	/* Version Register */

/* Mode Register bit fields */
#घोषणा FLEX_MR_OPMODE_OFFSET	(0)  /* Operating Mode */
#घोषणा FLEX_MR_OPMODE_MASK	(0x3 << FLEX_MR_OPMODE_OFFSET)
#घोषणा FLEX_MR_OPMODE(opmode)	(((opmode) << FLEX_MR_OPMODE_OFFSET) &	\
				 FLEX_MR_OPMODE_MASK)

काष्ठा aपंचांगel_flexcom अणु
	व्योम __iomem *base;
	u32 opmode;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक aपंचांगel_flexcom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	काष्ठा aपंचांगel_flexcom *ddata;
	पूर्णांक err;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	err = of_property_पढ़ो_u32(np, "atmel,flexcom-mode", &ddata->opmode);
	अगर (err)
		वापस err;

	अगर (ddata->opmode < ATMEL_FLEXCOM_MODE_USART ||
	    ddata->opmode > ATMEL_FLEXCOM_MODE_TWI)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ddata->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ddata->base))
		वापस PTR_ERR(ddata->base);

	ddata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ddata->clk))
		वापस PTR_ERR(ddata->clk);

	err = clk_prepare_enable(ddata->clk);
	अगर (err)
		वापस err;

	/*
	 * Set the Operating Mode in the Mode Register: only the selected device
	 * is घड़ीed. Hence, रेजिस्टरs of the other serial devices reमुख्य
	 * inaccessible and are पढ़ो as zero. Also the बाह्यal I/O lines of the
	 * Flexcom are muxed to reach the selected device.
	 */
	ग_लिखोl(FLEX_MR_OPMODE(ddata->opmode), ddata->base + FLEX_MR);

	clk_disable_unprepare(ddata->clk);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_flexcom_of_match[] = अणु
	अणु .compatible = "atmel,sama5d2-flexcom" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_flexcom_of_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_flexcom_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_flexcom *ddata = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 val;

	err = clk_prepare_enable(ddata->clk);
	अगर (err)
		वापस err;

	val = FLEX_MR_OPMODE(ddata->opmode),
	ग_लिखोl(val, ddata->base + FLEX_MR);

	clk_disable_unprepare(ddata->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_flexcom_pm_ops, शून्य,
			 aपंचांगel_flexcom_resume);

अटल काष्ठा platक्रमm_driver aपंचांगel_flexcom_driver = अणु
	.probe	= aपंचांगel_flexcom_probe,
	.driver	= अणु
		.name		= "atmel_flexcom",
		.pm		= &aपंचांगel_flexcom_pm_ops,
		.of_match_table	= aपंचांगel_flexcom_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_flexcom_driver);

MODULE_AUTHOR("Cyrille Pitchen <cyrille.pitchen@atmel.com>");
MODULE_DESCRIPTION("Atmel Flexcom MFD driver");
MODULE_LICENSE("GPL v2");
