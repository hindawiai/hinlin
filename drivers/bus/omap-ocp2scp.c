<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * omap-ocp2scp.c - transक्रमm ocp पूर्णांकerface protocol to scp protocol
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा OCP2SCP_TIMING 0x18
#घोषणा SYNC2_MASK 0xf

अटल पूर्णांक ocp2scp_हटाओ_devices(काष्ठा device *dev, व्योम *c)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ocp2scp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 reg;
	व्योम __iomem *regs;
	काष्ठा resource *res;
	काष्ठा device_node *np = pdev->dev.of_node;

	अगर (np) अणु
		ret = of_platक्रमm_populate(np, शून्य, शून्य, &pdev->dev);
		अगर (ret) अणु
			dev_err(&pdev->dev,
			    "failed to add resources for ocp2scp child\n");
			जाओ err0;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	/*
	 * As per AM572x TRM: http://www.ti.com/lit/ug/spruhz6/spruhz6.pdf
	 * under section 26.3.2.2, table 26-26 OCP2SCP TIMING Caution;
	 * As per OMAP4430 TRM: http://www.ti.com/lit/ug/swpu231ap/swpu231ap.pdf
	 * under section 23.12.6.2.2 , Table 23-1213 OCP2SCP TIMING Caution;
	 * As per OMAP4460 TRM: http://www.ti.com/lit/ug/swpu235ab/swpu235ab.pdf
	 * under section 23.12.6.2.2, Table 23-1213 OCP2SCP TIMING Caution;
	 * As per OMAP543x TRM http://www.ti.com/lit/pdf/swpu249
	 * under section 27.3.2.2, Table 27-27 OCP2SCP TIMING Caution;
	 *
	 * Read path of OCP2SCP is not working properly due to low reset value
	 * of SYNC2 parameter in OCP2SCP. Suggested reset value is 0x6 or more.
	 */
	अगर (!of_device_is_compatible(np, "ti,am437x-ocp2scp")) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		regs = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(regs)) अणु
			ret = PTR_ERR(regs);
			जाओ err1;
		पूर्ण

		pm_runसमय_get_sync(&pdev->dev);
		reg = पढ़ोl_relaxed(regs + OCP2SCP_TIMING);
		reg &= ~(SYNC2_MASK);
		reg |= 0x6;
		ग_लिखोl_relaxed(reg, regs + OCP2SCP_TIMING);
		pm_runसमय_put_sync(&pdev->dev);
	पूर्ण

	वापस 0;

err1:
	pm_runसमय_disable(&pdev->dev);

err0:
	device_क्रम_each_child(&pdev->dev, शून्य, ocp2scp_हटाओ_devices);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_ocp2scp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	device_क्रम_each_child(&pdev->dev, शून्य, ocp2scp_हटाओ_devices);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id omap_ocp2scp_id_table[] = अणु
	अणु .compatible = "ti,omap-ocp2scp" पूर्ण,
	अणु .compatible = "ti,am437x-ocp2scp" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_ocp2scp_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver omap_ocp2scp_driver = अणु
	.probe		= omap_ocp2scp_probe,
	.हटाओ		= omap_ocp2scp_हटाओ,
	.driver		= अणु
		.name	= "omap-ocp2scp",
		.of_match_table = of_match_ptr(omap_ocp2scp_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_ocp2scp_driver);

MODULE_ALIAS("platform:omap-ocp2scp");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("OMAP OCP2SCP driver");
MODULE_LICENSE("GPL v2");
