<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2011-2015 John Crispin <blogic@phrozen.org>
 *  Copyright (C) 2015 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 *  Copyright (C) 2017 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#समावेश <lantiq_soc.h>

#घोषणा XBAR_ALWAYS_LAST	0x430
#घोषणा XBAR_FPI_BURST_EN	BIT(1)
#घोषणा XBAR_AHB_BURST_EN	BIT(2)

#घोषणा RCU_VR9_BE_AHB1S	0x00000008

अटल पूर्णांक ltq_fpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *rcu_regmap;
	व्योम __iomem *xbar_membase;
	u32 rcu_ahb_endianness_reg_offset;
	पूर्णांक ret;

	xbar_membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xbar_membase))
		वापस PTR_ERR(xbar_membase);

	/* RCU configuration is optional */
	rcu_regmap = syscon_regmap_lookup_by_phandle(np, "lantiq,rcu");
	अगर (IS_ERR(rcu_regmap))
		वापस PTR_ERR(rcu_regmap);

	ret = device_property_पढ़ो_u32(dev, "lantiq,offset-endianness",
				       &rcu_ahb_endianness_reg_offset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get RCU reg offset\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(rcu_regmap, rcu_ahb_endianness_reg_offset,
				 RCU_VR9_BE_AHB1S, RCU_VR9_BE_AHB1S);
	अगर (ret) अणु
		dev_warn(&pdev->dev,
			 "Failed to configure RCU AHB endianness\n");
		वापस ret;
	पूर्ण

	/* disable fpi burst */
	ltq_w32_mask(XBAR_FPI_BURST_EN, 0, xbar_membase + XBAR_ALWAYS_LAST);

	वापस of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ltq_fpi_match[] = अणु
	अणु .compatible = "lantiq,xrx200-fpi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_fpi_match);

अटल काष्ठा platक्रमm_driver ltq_fpi_driver = अणु
	.probe = ltq_fpi_probe,
	.driver = अणु
		.name = "fpi-xway",
		.of_match_table = ltq_fpi_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ltq_fpi_driver);

MODULE_DESCRIPTION("Lantiq FPI bus driver");
MODULE_LICENSE("GPL");
