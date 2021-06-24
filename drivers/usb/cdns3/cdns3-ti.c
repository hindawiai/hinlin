<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * cdns3-ti.c - TI specअगरic Glue layer क्रम Cadence USB Controller
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

/* USB Wrapper रेजिस्टर offsets */
#घोषणा USBSS_PID		0x0
#घोषणा	USBSS_W1		0x4
#घोषणा USBSS_STATIC_CONFIG	0x8
#घोषणा USBSS_PHY_TEST		0xc
#घोषणा	USBSS_DEBUG_CTRL	0x10
#घोषणा	USBSS_DEBUG_INFO	0x14
#घोषणा	USBSS_DEBUG_LINK_STATE	0x18
#घोषणा	USBSS_DEVICE_CTRL	0x1c

/* Wrapper 1 रेजिस्टर bits */
#घोषणा USBSS_W1_PWRUP_RST		BIT(0)
#घोषणा USBSS_W1_OVERCURRENT_SEL	BIT(8)
#घोषणा USBSS_W1_MODESTRAP_SEL		BIT(9)
#घोषणा USBSS_W1_OVERCURRENT		BIT(16)
#घोषणा USBSS_W1_MODESTRAP_MASK		GENMASK(18, 17)
#घोषणा USBSS_W1_MODESTRAP_SHIFT	17
#घोषणा USBSS_W1_USB2_ONLY		BIT(19)

/* Static config रेजिस्टर bits */
#घोषणा USBSS1_STATIC_PLL_REF_SEL_MASK	GENMASK(8, 5)
#घोषणा USBSS1_STATIC_PLL_REF_SEL_SHIFT	5
#घोषणा USBSS1_STATIC_LOOPBACK_MODE_MASK	GENMASK(4, 3)
#घोषणा USBSS1_STATIC_LOOPBACK_MODE_SHIFT	3
#घोषणा USBSS1_STATIC_VBUS_SEL_MASK	GENMASK(2, 1)
#घोषणा USBSS1_STATIC_VBUS_SEL_SHIFT	1
#घोषणा USBSS1_STATIC_LANE_REVERSE	BIT(0)

/* Modestrap modes */
क्रमागत modestrap_mode अणु USBSS_MODESTRAP_MODE_NONE,
		      USBSS_MODESTRAP_MODE_HOST,
		      USBSS_MODESTRAP_MODE_PERIPHERALपूर्ण;

काष्ठा cdns_ti अणु
	काष्ठा device *dev;
	व्योम __iomem *usbss;
	अचिन्हित usb2_only:1;
	अचिन्हित vbus_भागider:1;
	काष्ठा clk *usb2_refclk;
	काष्ठा clk *lpm_clk;
पूर्ण;

अटल स्थिर पूर्णांक cdns_ti_rate_table[] = अणु	/* in KHZ */
	9600,
	10000,
	12000,
	19200,
	20000,
	24000,
	25000,
	26000,
	38400,
	40000,
	58000,
	50000,
	52000,
पूर्ण;

अटल अंतरभूत u32 cdns_ti_पढ़ोl(काष्ठा cdns_ti *data, u32 offset)
अणु
	वापस पढ़ोl(data->usbss + offset);
पूर्ण

अटल अंतरभूत व्योम cdns_ti_ग_लिखोl(काष्ठा cdns_ti *data, u32 offset, u32 value)
अणु
	ग_लिखोl(value, data->usbss + offset);
पूर्ण

अटल पूर्णांक cdns_ti_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा cdns_ti *data;
	पूर्णांक error;
	u32 reg;
	पूर्णांक rate_code, i;
	अचिन्हित दीर्घ rate;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);

	data->dev = dev;

	data->usbss = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->usbss)) अणु
		dev_err(dev, "can't map IOMEM resource\n");
		वापस PTR_ERR(data->usbss);
	पूर्ण

	data->usb2_refclk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(data->usb2_refclk)) अणु
		dev_err(dev, "can't get usb2_refclk\n");
		वापस PTR_ERR(data->usb2_refclk);
	पूर्ण

	data->lpm_clk = devm_clk_get(dev, "lpm");
	अगर (IS_ERR(data->lpm_clk)) अणु
		dev_err(dev, "can't get lpm_clk\n");
		वापस PTR_ERR(data->lpm_clk);
	पूर्ण

	rate = clk_get_rate(data->usb2_refclk);
	rate /= 1000;	/* To KHz */
	क्रम (i = 0; i < ARRAY_SIZE(cdns_ti_rate_table); i++) अणु
		अगर (cdns_ti_rate_table[i] == rate)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(cdns_ti_rate_table)) अणु
		dev_err(dev, "unsupported usb2_refclk rate: %lu KHz\n", rate);
		वापस -EINVAL;
	पूर्ण

	rate_code = i;

	pm_runसमय_enable(dev);
	error = pm_runसमय_get_sync(dev);
	अगर (error < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed: %d\n", error);
		जाओ err;
	पूर्ण

	/* निश्चित RESET */
	reg = cdns_ti_पढ़ोl(data, USBSS_W1);
	reg &= ~USBSS_W1_PWRUP_RST;
	cdns_ti_ग_लिखोl(data, USBSS_W1, reg);

	/* set अटल config */
	reg = cdns_ti_पढ़ोl(data, USBSS_STATIC_CONFIG);
	reg &= ~USBSS1_STATIC_PLL_REF_SEL_MASK;
	reg |= rate_code << USBSS1_STATIC_PLL_REF_SEL_SHIFT;

	reg &= ~USBSS1_STATIC_VBUS_SEL_MASK;
	data->vbus_भागider = device_property_पढ़ो_bool(dev, "ti,vbus-divider");
	अगर (data->vbus_भागider)
		reg |= 1 << USBSS1_STATIC_VBUS_SEL_SHIFT;

	cdns_ti_ग_लिखोl(data, USBSS_STATIC_CONFIG, reg);
	reg = cdns_ti_पढ़ोl(data, USBSS_STATIC_CONFIG);

	/* set USB2_ONLY mode अगर requested */
	reg = cdns_ti_पढ़ोl(data, USBSS_W1);
	data->usb2_only = device_property_पढ़ो_bool(dev, "ti,usb2-only");
	अगर (data->usb2_only)
		reg |= USBSS_W1_USB2_ONLY;

	/* set शेष modestrap */
	reg |= USBSS_W1_MODESTRAP_SEL;
	reg &= ~USBSS_W1_MODESTRAP_MASK;
	reg |= USBSS_MODESTRAP_MODE_NONE << USBSS_W1_MODESTRAP_SHIFT;
	cdns_ti_ग_लिखोl(data, USBSS_W1, reg);

	/* de-निश्चित RESET */
	reg |= USBSS_W1_PWRUP_RST;
	cdns_ti_ग_लिखोl(data, USBSS_W1, reg);

	error = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (error) अणु
		dev_err(dev, "failed to create children: %d\n", error);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	pm_runसमय_put_sync(data->dev);
	pm_runसमय_disable(data->dev);

	वापस error;
पूर्ण

अटल पूर्णांक cdns_ti_हटाओ_core(काष्ठा device *dev, व्योम *c)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_ti_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	device_क्रम_each_child(dev, शून्य, cdns_ti_हटाओ_core);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cdns_ti_of_match[] = अणु
	अणु .compatible = "ti,j721e-usb", पूर्ण,
	अणु .compatible = "ti,am64-usb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_ti_of_match);

अटल काष्ठा platक्रमm_driver cdns_ti_driver = अणु
	.probe		= cdns_ti_probe,
	.हटाओ		= cdns_ti_हटाओ,
	.driver		= अणु
		.name	= "cdns3-ti",
		.of_match_table	= cdns_ti_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cdns_ti_driver);

MODULE_ALIAS("platform:cdns3-ti");
MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence USB3 TI Glue Layer");
