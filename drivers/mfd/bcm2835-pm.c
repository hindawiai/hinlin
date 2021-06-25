<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PM MFD driver क्रम Broadcom BCM2835
 *
 * This driver binds to the PM block and creates the MFD device क्रम
 * the WDT and घातer drivers.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/bcm2835-pm.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

अटल स्थिर काष्ठा mfd_cell bcm2835_pm_devs[] = अणु
	अणु .name = "bcm2835-wdt" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell bcm2835_घातer_devs[] = अणु
	अणु .name = "bcm2835-power" पूर्ण,
पूर्ण;

अटल पूर्णांक bcm2835_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm2835_pm *pm;
	पूर्णांक ret;

	pm = devm_kzalloc(dev, माप(*pm), GFP_KERNEL);
	अगर (!pm)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, pm);

	pm->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pm->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pm->base))
		वापस PTR_ERR(pm->base);

	ret = devm_mfd_add_devices(dev, -1,
				   bcm2835_pm_devs, ARRAY_SIZE(bcm2835_pm_devs),
				   शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	/* We'll use the presence of the AXI ASB regs in the
	 * bcm2835-pm binding as the key क्रम whether we can reference
	 * the full PM रेजिस्टर range and support घातer करोमुख्यs.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		pm->asb = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(pm->asb))
			वापस PTR_ERR(pm->asb);

		ret = devm_mfd_add_devices(dev, -1,
					   bcm2835_घातer_devs,
					   ARRAY_SIZE(bcm2835_घातer_devs),
					   शून्य, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_pm_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-pm-wdt", पूर्ण,
	अणु .compatible = "brcm,bcm2835-pm", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_pm_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_pm_driver = अणु
	.probe		= bcm2835_pm_probe,
	.driver = अणु
		.name =	"bcm2835-pm",
		.of_match_table = bcm2835_pm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_pm_driver);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Driver for Broadcom BCM2835 PM MFD");
MODULE_LICENSE("GPL");
