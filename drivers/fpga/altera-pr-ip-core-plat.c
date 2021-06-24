<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Altera Partial Reconfiguration IP Core
 *
 * Copyright (C) 2016-2017 Intel Corporation
 *
 * Based on socfpga-a10.c Copyright (C) 2015-2016 Altera Corporation
 *  by Alan Tull <atull@खोलोsource.altera.com>
 */
#समावेश <linux/fpga/altera-pr-ip-core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

अटल पूर्णांक alt_pr_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *reg_base;
	काष्ठा resource *res;

	/* First mmio base is क्रम रेजिस्टर access */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	reg_base = devm_ioremap_resource(dev, res);

	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	वापस alt_pr_रेजिस्टर(dev, reg_base);
पूर्ण

अटल स्थिर काष्ठा of_device_id alt_pr_of_match[] = अणु
	अणु .compatible = "altr,a10-pr-ip", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, alt_pr_of_match);

अटल काष्ठा platक्रमm_driver alt_pr_platक्रमm_driver = अणु
	.probe = alt_pr_platक्रमm_probe,
	.driver = अणु
		.name	= "alt_a10_pr_ip",
		.of_match_table = alt_pr_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(alt_pr_platक्रमm_driver);
MODULE_AUTHOR("Matthew Gerlach <matthew.gerlach@linux.intel.com>");
MODULE_DESCRIPTION("Altera Partial Reconfiguration IP Platform Driver");
MODULE_LICENSE("GPL v2");
