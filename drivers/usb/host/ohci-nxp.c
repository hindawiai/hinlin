<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * driver क्रम NXP USB Host devices
 *
 * Currently supported OHCI host devices:
 * - NXP LPC32xx
 *
 * Authors: Dmitry Chigirev <source@mvista.com>
 *	    Vitaly Wool <vitalywool@gmail.com>
 *
 * रेजिस्टर initialization is based on code examples provided by Philips
 * Copyright (c) 2005 Koninklijke Philips Electronics N.V.
 *
 * NOTE: This driver करोes not have suspend/resume functionality
 * This driver is पूर्णांकended क्रम engineering development purposes only
 *
 * 2005-2006 (c) MontaVista Software, Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/isp1301.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"

#घोषणा USB_CONFIG_BASE		0x31020000

/* USB_OTG_STAT_CONTROL bit defines */
#घोषणा TRANSPARENT_I2C_EN	(1 << 7)
#घोषणा HOST_EN			(1 << 0)

/* On LPC32xx, those are undefined */
#अगर_अघोषित start_पूर्णांक_set_falling_edge
#घोषणा start_पूर्णांक_set_falling_edge(irq)
#घोषणा start_पूर्णांक_set_rising_edge(irq)
#घोषणा start_पूर्णांक_ack(irq)
#घोषणा start_पूर्णांक_mask(irq)
#घोषणा start_पूर्णांक_umask(irq)
#पूर्ण_अगर

#घोषणा DRIVER_DESC "OHCI NXP driver"

अटल स्थिर अक्षर hcd_name[] = "ohci-nxp";
अटल काष्ठा hc_driver __पढ़ो_mostly ohci_nxp_hc_driver;

अटल काष्ठा i2c_client *isp1301_i2c_client;

अटल काष्ठा clk *usb_host_clk;

अटल व्योम isp1301_configure_lpc32xx(व्योम)
अणु
	/* LPC32XX only supports DAT_SE0 USB mode */
	/* This sequence is important */

	/* Disable transparent UART mode first */
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		MC1_UART_EN);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		~MC1_SPEED_REG);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
				  ISP1301_I2C_MODE_CONTROL_1, MC1_SPEED_REG);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		  (ISP1301_I2C_MODE_CONTROL_2 | ISP1301_I2C_REG_CLEAR_ADDR),
		  ~0);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_2,
		(MC2_BI_DI | MC2_PSW_EN | MC2_SPD_SUSP_CTRL));
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_1, MC1_DAT_SE0);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1,
		(OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN));
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		(OTG1_DM_PULLUP | OTG1_DP_PULLUP));
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_LATCH | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING | ISP1301_I2C_REG_CLEAR_ADDR,
		~0);
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);

	prपूर्णांकk(KERN_INFO "ISP1301 Vendor ID  : 0x%04x\n",
	      i2c_smbus_पढ़ो_word_data(isp1301_i2c_client, 0x00));
	prपूर्णांकk(KERN_INFO "ISP1301 Product ID : 0x%04x\n",
	      i2c_smbus_पढ़ो_word_data(isp1301_i2c_client, 0x02));
	prपूर्णांकk(KERN_INFO "ISP1301 Version ID : 0x%04x\n",
	      i2c_smbus_पढ़ो_word_data(isp1301_i2c_client, 0x14));
पूर्ण

अटल व्योम isp1301_configure(व्योम)
अणु
	isp1301_configure_lpc32xx();
पूर्ण

अटल अंतरभूत व्योम isp1301_vbus_on(व्योम)
अणु
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client, ISP1301_I2C_OTG_CONTROL_1,
				  OTG1_VBUS_DRV);
पूर्ण

अटल अंतरभूत व्योम isp1301_vbus_off(व्योम)
अणु
	i2c_smbus_ग_लिखो_byte_data(isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
		OTG1_VBUS_DRV);
पूर्ण

अटल व्योम ohci_nxp_start_hc(व्योम)
अणु
	व्योम __iomem *usb_otg_stat_control = ioremap(USB_CONFIG_BASE + 0x110, 4);
	अचिन्हित दीर्घ पंचांगp;

	अगर (WARN_ON(!usb_otg_stat_control))
		वापस;

	पंचांगp = __raw_पढ़ोl(usb_otg_stat_control) | HOST_EN;

	__raw_ग_लिखोl(पंचांगp, usb_otg_stat_control);
	isp1301_vbus_on();

	iounmap(usb_otg_stat_control);
पूर्ण

अटल व्योम ohci_nxp_stop_hc(व्योम)
अणु
	व्योम __iomem *usb_otg_stat_control = ioremap(USB_CONFIG_BASE + 0x110, 4);
	अचिन्हित दीर्घ पंचांगp;

	अगर (WARN_ON(!usb_otg_stat_control))
		वापस;

	isp1301_vbus_off();
	पंचांगp = __raw_पढ़ोl(usb_otg_stat_control) & ~HOST_EN;
	__raw_ग_लिखोl(पंचांगp, usb_otg_stat_control);

	iounmap(usb_otg_stat_control);
पूर्ण

अटल पूर्णांक ohci_hcd_nxp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = शून्य;
	स्थिर काष्ठा hc_driver *driver = &ohci_nxp_hc_driver;
	काष्ठा resource *res;
	पूर्णांक ret = 0, irq;
	काष्ठा device_node *isp1301_node;

	अगर (pdev->dev.of_node) अणु
		isp1301_node = of_parse_phandle(pdev->dev.of_node,
						"transceiver", 0);
	पूर्ण अन्यथा अणु
		isp1301_node = शून्य;
	पूर्ण

	isp1301_i2c_client = isp1301_get_client(isp1301_node);
	अगर (!isp1301_i2c_client)
		वापस -EPROBE_DEFER;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ fail_disable;

	dev_dbg(&pdev->dev, "%s: " DRIVER_DESC " (nxp)\n", hcd_name);
	अगर (usb_disabled()) अणु
		dev_err(&pdev->dev, "USB is disabled\n");
		ret = -ENODEV;
		जाओ fail_disable;
	पूर्ण

	/* Enable USB host घड़ी */
	usb_host_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(usb_host_clk)) अणु
		dev_err(&pdev->dev, "failed to acquire USB OHCI clock\n");
		ret = PTR_ERR(usb_host_clk);
		जाओ fail_disable;
	पूर्ण

	ret = clk_prepare_enable(usb_host_clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to start USB OHCI clock\n");
		जाओ fail_disable;
	पूर्ण

	isp1301_configure();

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		dev_err(&pdev->dev, "Failed to allocate HC buffer\n");
		ret = -ENOMEM;
		जाओ fail_hcd;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		ret = PTR_ERR(hcd->regs);
		जाओ fail_resource;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ fail_resource;
	पूर्ण

	ohci_nxp_start_hc();
	platक्रमm_set_drvdata(pdev, hcd);

	dev_info(&pdev->dev, "at 0x%p, irq %d\n", hcd->regs, hcd->irq);
	ret = usb_add_hcd(hcd, irq, 0);
	अगर (ret == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस ret;
	पूर्ण

	ohci_nxp_stop_hc();
fail_resource:
	usb_put_hcd(hcd);
fail_hcd:
	clk_disable_unprepare(usb_host_clk);
fail_disable:
	isp1301_i2c_client = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक ohci_hcd_nxp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_hcd(hcd);
	ohci_nxp_stop_hc();
	usb_put_hcd(hcd);
	clk_disable_unprepare(usb_host_clk);
	isp1301_i2c_client = शून्य;

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:usb-ohci");

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ohci_hcd_nxp_match[] = अणु
	अणु .compatible = "nxp,ohci-nxp" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ohci_hcd_nxp_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ohci_hcd_nxp_driver = अणु
	.driver = अणु
		.name = "usb-ohci",
		.of_match_table = of_match_ptr(ohci_hcd_nxp_match),
	पूर्ण,
	.probe = ohci_hcd_nxp_probe,
	.हटाओ = ohci_hcd_nxp_हटाओ,
पूर्ण;

अटल पूर्णांक __init ohci_nxp_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_nxp_hc_driver, शून्य);
	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_nxp_driver);
पूर्ण
module_init(ohci_nxp_init);

अटल व्योम __निकास ohci_nxp_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_nxp_driver);
पूर्ण
module_निकास(ohci_nxp_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
