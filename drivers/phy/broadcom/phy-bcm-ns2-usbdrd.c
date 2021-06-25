<शैली गुरु>
/*
 * Copyright (C) 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#घोषणा ICFG_DRD_AFE		0x0
#घोषणा ICFG_MISC_STAT		0x18
#घोषणा ICFG_DRD_P0CTL		0x1C
#घोषणा ICFG_STRAP_CTRL		0x20
#घोषणा ICFG_FSM_CTRL		0x24

#घोषणा ICFG_DEV_BIT		BIT(2)
#घोषणा IDM_RST_BIT		BIT(0)
#घोषणा AFE_CORERDY_VDDC	BIT(18)
#घोषणा PHY_PLL_RESETB		BIT(15)
#घोषणा PHY_RESETB		BIT(14)
#घोषणा PHY_PLL_LOCK		BIT(0)

#घोषणा DRD_DEV_MODE		BIT(20)
#घोषणा OHCI_OVRCUR_POL		BIT(11)
#घोषणा ICFG_OFF_MODE		BIT(6)
#घोषणा PLL_LOCK_RETRY		1000

#घोषणा EVT_DEVICE		0
#घोषणा EVT_HOST		1

#घोषणा DRD_HOST_MODE		(BIT(2) | BIT(3))
#घोषणा DRD_DEVICE_MODE		(BIT(4) | BIT(5))
#घोषणा DRD_HOST_VAL		0x803
#घोषणा DRD_DEV_VAL		0x807
#घोषणा GPIO_DELAY		20

काष्ठा ns2_phy_data;
काष्ठा ns2_phy_driver अणु
	व्योम __iomem *icfgdrd_regs;
	व्योम __iomem *idmdrd_rst_ctrl;
	व्योम __iomem *crmu_usb2_ctrl;
	व्योम __iomem *usb2h_strap_reg;
	काष्ठा ns2_phy_data *data;
	काष्ठा extcon_dev *edev;
	काष्ठा gpio_desc *vbus_gpiod;
	काष्ठा gpio_desc *id_gpiod;
	पूर्णांक id_irq;
	पूर्णांक vbus_irq;
	अचिन्हित दीर्घ debounce_jअगरfies;
	काष्ठा delayed_work wq_extcon;
पूर्ण;

काष्ठा ns2_phy_data अणु
	काष्ठा ns2_phy_driver *driver;
	काष्ठा phy *phy;
	पूर्णांक new_state;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक usb_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल अंतरभूत पूर्णांक pll_lock_stat(u32 usb_reg, पूर्णांक reg_mask,
				काष्ठा ns2_phy_driver *driver)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout_atomic(driver->icfgdrd_regs + usb_reg,
					 val, (val & reg_mask), 1,
					 PLL_LOCK_RETRY);
पूर्ण

अटल पूर्णांक ns2_drd_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ns2_phy_data *data = phy_get_drvdata(phy);
	काष्ठा ns2_phy_driver *driver = data->driver;
	u32 val;

	val = पढ़ोl(driver->icfgdrd_regs + ICFG_FSM_CTRL);

	अगर (data->new_state == EVT_HOST) अणु
		val &= ~DRD_DEVICE_MODE;
		val |= DRD_HOST_MODE;
	पूर्ण अन्यथा अणु
		val &= ~DRD_HOST_MODE;
		val |= DRD_DEVICE_MODE;
	पूर्ण
	ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक ns2_drd_phy_घातeroff(काष्ठा phy *phy)
अणु
	काष्ठा ns2_phy_data *data = phy_get_drvdata(phy);
	काष्ठा ns2_phy_driver *driver = data->driver;
	u32 val;

	val = पढ़ोl(driver->crmu_usb2_ctrl);
	val &= ~AFE_CORERDY_VDDC;
	ग_लिखोl(val, driver->crmu_usb2_ctrl);

	val = पढ़ोl(driver->crmu_usb2_ctrl);
	val &= ~DRD_DEV_MODE;
	ग_लिखोl(val, driver->crmu_usb2_ctrl);

	/* Disable Host and Device Mode */
	val = पढ़ोl(driver->icfgdrd_regs + ICFG_FSM_CTRL);
	val &= ~(DRD_HOST_MODE | DRD_DEVICE_MODE | ICFG_OFF_MODE);
	ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक ns2_drd_phy_घातeron(काष्ठा phy *phy)
अणु
	काष्ठा ns2_phy_data *data = phy_get_drvdata(phy);
	काष्ठा ns2_phy_driver *driver = data->driver;
	u32 extcon_event = data->new_state;
	पूर्णांक ret;
	u32 val;

	अगर (extcon_event == EVT_DEVICE) अणु
		ग_लिखोl(DRD_DEV_VAL, driver->icfgdrd_regs + ICFG_DRD_P0CTL);

		val = पढ़ोl(driver->idmdrd_rst_ctrl);
		val &= ~IDM_RST_BIT;
		ग_लिखोl(val, driver->idmdrd_rst_ctrl);

		val = पढ़ोl(driver->crmu_usb2_ctrl);
		val |= (AFE_CORERDY_VDDC | DRD_DEV_MODE);
		ग_लिखोl(val, driver->crmu_usb2_ctrl);

		/* Bring PHY and PHY_PLL out of Reset */
		val = पढ़ोl(driver->crmu_usb2_ctrl);
		val |= (PHY_PLL_RESETB | PHY_RESETB);
		ग_लिखोl(val, driver->crmu_usb2_ctrl);

		ret = pll_lock_stat(ICFG_MISC_STAT, PHY_PLL_LOCK, driver);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "Phy PLL lock failed\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl(DRD_HOST_VAL, driver->icfgdrd_regs + ICFG_DRD_P0CTL);

		val = पढ़ोl(driver->crmu_usb2_ctrl);
		val |= AFE_CORERDY_VDDC;
		ग_लिखोl(val, driver->crmu_usb2_ctrl);

		ret = pll_lock_stat(ICFG_MISC_STAT, PHY_PLL_LOCK, driver);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "Phy PLL lock failed\n");
			वापस ret;
		पूर्ण

		val = पढ़ोl(driver->idmdrd_rst_ctrl);
		val &= ~IDM_RST_BIT;
		ग_लिखोl(val, driver->idmdrd_rst_ctrl);

		/* port over current Polarity */
		val = पढ़ोl(driver->usb2h_strap_reg);
		val |= OHCI_OVRCUR_POL;
		ग_लिखोl(val, driver->usb2h_strap_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम connect_change(काष्ठा ns2_phy_driver *driver)
अणु
	u32 extcon_event;
	u32 val;

	extcon_event = driver->data->new_state;
	val = पढ़ोl(driver->icfgdrd_regs + ICFG_FSM_CTRL);

	चयन (extcon_event) अणु
	हाल EVT_DEVICE:
		val &= ~(DRD_HOST_MODE | DRD_DEVICE_MODE);
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = (val & ~DRD_HOST_MODE) | DRD_DEVICE_MODE;
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = पढ़ोl(driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		val |= ICFG_DEV_BIT;
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		अवरोध;

	हाल EVT_HOST:
		val &= ~(DRD_HOST_MODE | DRD_DEVICE_MODE);
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = (val & ~DRD_DEVICE_MODE) | DRD_HOST_MODE;
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = पढ़ोl(driver->usb2h_strap_reg);
		val |= OHCI_OVRCUR_POL;
		ग_लिखोl(val, driver->usb2h_strap_reg);

		val = पढ़ोl(driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		val &= ~ICFG_DEV_BIT;
		ग_लिखोl(val, driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		अवरोध;

	शेष:
		pr_err("Invalid extcon event\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम extcon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ns2_phy_driver *driver;
	पूर्णांक vbus;
	पूर्णांक id;

	driver  = container_of(to_delayed_work(work),
			       काष्ठा ns2_phy_driver, wq_extcon);

	id = gpiod_get_value_cansleep(driver->id_gpiod);
	vbus = gpiod_get_value_cansleep(driver->vbus_gpiod);

	अगर (!id && vbus) अणु /* Host connected */
		extcon_set_state_sync(driver->edev, EXTCON_USB_HOST, true);
		pr_debug("Host cable connected\n");
		driver->data->new_state = EVT_HOST;
		connect_change(driver);
	पूर्ण अन्यथा अगर (id && !vbus) अणु /* Disconnected */
		extcon_set_state_sync(driver->edev, EXTCON_USB_HOST, false);
		extcon_set_state_sync(driver->edev, EXTCON_USB, false);
		pr_debug("Cable disconnected\n");
	पूर्ण अन्यथा अगर (id && vbus) अणु /* Device connected */
		extcon_set_state_sync(driver->edev, EXTCON_USB, true);
		pr_debug("Device cable connected\n");
		driver->data->new_state = EVT_DEVICE;
		connect_change(driver);
	पूर्ण
पूर्ण

अटल irqवापस_t gpio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ns2_phy_driver *driver = dev_id;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &driver->wq_extcon,
			   driver->debounce_jअगरfies);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= ns2_drd_phy_init,
	.घातer_on	= ns2_drd_phy_घातeron,
	.घातer_off	= ns2_drd_phy_घातeroff,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ns2_drd_phy_dt_ids[] = अणु
	अणु .compatible = "brcm,ns2-drd-phy", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ns2_drd_phy_dt_ids);

अटल पूर्णांक ns2_drd_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ns2_phy_driver *driver;
	काष्ठा ns2_phy_data *data;
	पूर्णांक ret;
	u32 val;

	driver = devm_kzalloc(dev, माप(काष्ठा ns2_phy_driver),
			      GFP_KERNEL);
	अगर (!driver)
		वापस -ENOMEM;

	driver->data = devm_kzalloc(dev, माप(काष्ठा ns2_phy_data),
				  GFP_KERNEL);
	अगर (!driver->data)
		वापस -ENOMEM;

	driver->icfgdrd_regs = devm_platक्रमm_ioremap_resource_byname(pdev, "icfg");
	अगर (IS_ERR(driver->icfgdrd_regs))
		वापस PTR_ERR(driver->icfgdrd_regs);

	driver->idmdrd_rst_ctrl = devm_platक्रमm_ioremap_resource_byname(pdev, "rst-ctrl");
	अगर (IS_ERR(driver->idmdrd_rst_ctrl))
		वापस PTR_ERR(driver->idmdrd_rst_ctrl);

	driver->crmu_usb2_ctrl = devm_platक्रमm_ioremap_resource_byname(pdev, "crmu-ctrl");
	अगर (IS_ERR(driver->crmu_usb2_ctrl))
		वापस PTR_ERR(driver->crmu_usb2_ctrl);

	driver->usb2h_strap_reg = devm_platक्रमm_ioremap_resource_byname(pdev, "usb2-strap");
	अगर (IS_ERR(driver->usb2h_strap_reg))
		वापस PTR_ERR(driver->usb2h_strap_reg);

	 /* create extcon */
	driver->id_gpiod = devm_gpiod_get(&pdev->dev, "id", GPIOD_IN);
	अगर (IS_ERR(driver->id_gpiod)) अणु
		dev_err(dev, "failed to get ID GPIO\n");
		वापस PTR_ERR(driver->id_gpiod);
	पूर्ण
	driver->vbus_gpiod = devm_gpiod_get(&pdev->dev, "vbus", GPIOD_IN);
	अगर (IS_ERR(driver->vbus_gpiod)) अणु
		dev_err(dev, "failed to get VBUS GPIO\n");
		वापस PTR_ERR(driver->vbus_gpiod);
	पूर्ण

	driver->edev = devm_extcon_dev_allocate(dev, usb_extcon_cable);
	अगर (IS_ERR(driver->edev)) अणु
		dev_err(dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, driver->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	ret = gpiod_set_debounce(driver->id_gpiod, GPIO_DELAY * 1000);
	अगर (ret < 0)
		driver->debounce_jअगरfies = msecs_to_jअगरfies(GPIO_DELAY);

	INIT_DELAYED_WORK(&driver->wq_extcon, extcon_work);

	driver->id_irq = gpiod_to_irq(driver->id_gpiod);
	अगर (driver->id_irq < 0) अणु
		dev_err(dev, "failed to get ID IRQ\n");
		वापस driver->id_irq;
	पूर्ण

	driver->vbus_irq = gpiod_to_irq(driver->vbus_gpiod);
	अगर (driver->vbus_irq < 0) अणु
		dev_err(dev, "failed to get ID IRQ\n");
		वापस driver->vbus_irq;
	पूर्ण

	ret = devm_request_irq(dev, driver->id_irq, gpio_irq_handler,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			       "usb_id", driver);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request handler for ID IRQ\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, driver->vbus_irq, gpio_irq_handler,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			       "usb_vbus", driver);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request handler for VBUS IRQ\n");
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, driver);

	/* Shutकरोwn all ports. They can be घातered up as required */
	val = पढ़ोl(driver->crmu_usb2_ctrl);
	val &= ~(AFE_CORERDY_VDDC | PHY_RESETB);
	ग_लिखोl(val, driver->crmu_usb2_ctrl);

	data = driver->data;
	data->phy = devm_phy_create(dev, dev->of_node, &ops);
	अगर (IS_ERR(data->phy)) अणु
		dev_err(dev, "Failed to create usb drd phy\n");
		वापस PTR_ERR(data->phy);
	पूर्ण

	data->driver = driver;
	phy_set_drvdata(data->phy, data);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(dev, "Failed to register as phy provider\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	platक्रमm_set_drvdata(pdev, driver);

	dev_info(dev, "Registered NS2 DRD Phy device\n");
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &driver->wq_extcon,
			   driver->debounce_jअगरfies);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ns2_drd_phy_driver = अणु
	.probe = ns2_drd_phy_probe,
	.driver = अणु
		.name = "bcm-ns2-usbphy",
		.of_match_table = of_match_ptr(ns2_drd_phy_dt_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ns2_drd_phy_driver);

MODULE_ALIAS("platform:bcm-ns2-drd-phy");
MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom NS2 USB2 PHY driver");
MODULE_LICENSE("GPL v2");
