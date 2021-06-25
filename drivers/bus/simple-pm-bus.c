<शैली गुरु>
/*
 * Simple Power-Managed Bus Driver
 *
 * Copyright (C) 2014-2015 Glider bvba
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>


अटल पूर्णांक simple_pm_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_dev_auxdata *lookup = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	pm_runसमय_enable(&pdev->dev);

	अगर (np)
		of_platक्रमm_populate(np, शून्य, lookup, &pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक simple_pm_bus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_dbg(&pdev->dev, "%s\n", __func__);

	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id simple_pm_bus_of_match[] = अणु
	अणु .compatible = "simple-pm-bus", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_pm_bus_of_match);

अटल काष्ठा platक्रमm_driver simple_pm_bus_driver = अणु
	.probe = simple_pm_bus_probe,
	.हटाओ = simple_pm_bus_हटाओ,
	.driver = अणु
		.name = "simple-pm-bus",
		.of_match_table = simple_pm_bus_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(simple_pm_bus_driver);

MODULE_DESCRIPTION("Simple Power-Managed Bus Driver");
MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_LICENSE("GPL v2");
