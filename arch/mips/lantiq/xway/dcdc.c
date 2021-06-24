<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 *  Copyright (C) 2010 Sameer Ahmad, Lantiq GmbH
 */

#समावेश <linux/ioport.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <lantiq_soc.h>

/* Bias and regulator Setup Register */
#घोषणा DCDC_BIAS_VREG0	0xa
/* Bias and regulator Setup Register */
#घोषणा DCDC_BIAS_VREG1	0xb

#घोषणा dcdc_w8(x, y)	ltq_w8((x), dcdc_membase + (y))
#घोषणा dcdc_r8(x)	ltq_r8(dcdc_membase + (x))

अटल व्योम __iomem *dcdc_membase;

अटल पूर्णांक dcdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dcdc_membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dcdc_membase))
		वापस PTR_ERR(dcdc_membase);

	dev_info(&pdev->dev, "Core Voltage : %d mV\n",
		dcdc_r8(DCDC_BIAS_VREG1) * 8);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dcdc_match[] = अणु
	अणु .compatible = "lantiq,dcdc-xrx200" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver dcdc_driver = अणु
	.probe = dcdc_probe,
	.driver = अणु
		.name = "dcdc-xrx200",
		.of_match_table = dcdc_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init dcdc_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&dcdc_driver);

	अगर (ret)
		pr_info("dcdc: Error registering platform driver\n");
	वापस ret;
पूर्ण

arch_initcall(dcdc_init);
