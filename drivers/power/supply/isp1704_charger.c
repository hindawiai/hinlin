<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ISP1704 USB Charger Detection driver
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2012 - 2013 Pali Rohथँr <pali@kernel.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/ulpi.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

/* Venकरोr specअगरic Power Control रेजिस्टर */
#घोषणा ISP1704_PWR_CTRL		0x3d
#घोषणा ISP1704_PWR_CTRL_SWCTRL		(1 << 0)
#घोषणा ISP1704_PWR_CTRL_DET_COMP	(1 << 1)
#घोषणा ISP1704_PWR_CTRL_BVALID_RISE	(1 << 2)
#घोषणा ISP1704_PWR_CTRL_BVALID_FALL	(1 << 3)
#घोषणा ISP1704_PWR_CTRL_DP_WKPU_EN	(1 << 4)
#घोषणा ISP1704_PWR_CTRL_VDAT_DET	(1 << 5)
#घोषणा ISP1704_PWR_CTRL_DPVSRC_EN	(1 << 6)
#घोषणा ISP1704_PWR_CTRL_HWDETECT	(1 << 7)

#घोषणा NXP_VENDOR_ID			0x04cc

अटल u16 isp170x_id[] = अणु
	0x1704,
	0x1707,
पूर्ण;

काष्ठा isp1704_अक्षरger अणु
	काष्ठा device			*dev;
	काष्ठा घातer_supply		*psy;
	काष्ठा घातer_supply_desc	psy_desc;
	काष्ठा gpio_desc		*enable_gpio;
	काष्ठा usb_phy			*phy;
	काष्ठा notअगरier_block		nb;
	काष्ठा work_काष्ठा		work;

	/* properties */
	अक्षर			model[8];
	अचिन्हित		present:1;
	अचिन्हित		online:1;
	अचिन्हित		current_max;
पूर्ण;

अटल अंतरभूत पूर्णांक isp1704_पढ़ो(काष्ठा isp1704_अक्षरger *isp, u32 reg)
अणु
	वापस usb_phy_io_पढ़ो(isp->phy, reg);
पूर्ण

अटल अंतरभूत पूर्णांक isp1704_ग_लिखो(काष्ठा isp1704_अक्षरger *isp, u32 reg, u32 val)
अणु
	वापस usb_phy_io_ग_लिखो(isp->phy, val, reg);
पूर्ण

अटल व्योम isp1704_अक्षरger_set_घातer(काष्ठा isp1704_अक्षरger *isp, bool on)
अणु
	gpiod_set_value(isp->enable_gpio, on);
पूर्ण

/*
 * Determine is the अक्षरging port DCP (dedicated अक्षरger) or CDP (Host/HUB
 * अक्षरgers).
 *
 * REVISIT: The method is defined in Battery Charging Specअगरication and is
 * applicable to any ULPI transceiver. Nothing isp170x specअगरic here.
 */
अटल अंतरभूत पूर्णांक isp1704_अक्षरger_type(काष्ठा isp1704_अक्षरger *isp)
अणु
	u8 reg;
	u8 func_ctrl;
	u8 otg_ctrl;
	पूर्णांक type = POWER_SUPPLY_TYPE_USB_DCP;

	func_ctrl = isp1704_पढ़ो(isp, ULPI_FUNC_CTRL);
	otg_ctrl = isp1704_पढ़ो(isp, ULPI_OTG_CTRL);

	/* disable pullकरोwns */
	reg = ULPI_OTG_CTRL_DM_PULLDOWN | ULPI_OTG_CTRL_DP_PULLDOWN;
	isp1704_ग_लिखो(isp, ULPI_CLR(ULPI_OTG_CTRL), reg);

	/* full speed */
	isp1704_ग_लिखो(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_XCVRSEL_MASK);
	isp1704_ग_लिखो(isp, ULPI_SET(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_FULL_SPEED);

	/* Enable strong pull-up on DP (1.5K) and reset */
	reg = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	isp1704_ग_लिखो(isp, ULPI_SET(ULPI_FUNC_CTRL), reg);
	usleep_range(1000, 2000);

	reg = isp1704_पढ़ो(isp, ULPI_DEBUG);
	अगर ((reg & 3) != 3)
		type = POWER_SUPPLY_TYPE_USB_CDP;

	/* recover original state */
	isp1704_ग_लिखो(isp, ULPI_FUNC_CTRL, func_ctrl);
	isp1704_ग_लिखो(isp, ULPI_OTG_CTRL, otg_ctrl);

	वापस type;
पूर्ण

/*
 * ISP1704 detects PS/2 adapters as अक्षरger. To make sure the detected अक्षरger
 * is actually a dedicated अक्षरger, the following steps need to be taken.
 */
अटल अंतरभूत पूर्णांक isp1704_अक्षरger_verअगरy(काष्ठा isp1704_अक्षरger *isp)
अणु
	पूर्णांक	ret = 0;
	u8	r;

	/* Reset the transceiver */
	r = isp1704_पढ़ो(isp, ULPI_FUNC_CTRL);
	r |= ULPI_FUNC_CTRL_RESET;
	isp1704_ग_लिखो(isp, ULPI_FUNC_CTRL, r);
	usleep_range(1000, 2000);

	/* Set normal mode */
	r &= ~(ULPI_FUNC_CTRL_RESET | ULPI_FUNC_CTRL_OPMODE_MASK);
	isp1704_ग_लिखो(isp, ULPI_FUNC_CTRL, r);

	/* Clear the DP and DM pull-करोwn bits */
	r = ULPI_OTG_CTRL_DP_PULLDOWN | ULPI_OTG_CTRL_DM_PULLDOWN;
	isp1704_ग_लिखो(isp, ULPI_CLR(ULPI_OTG_CTRL), r);

	/* Enable strong pull-up on DP (1.5K) and reset */
	r = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	isp1704_ग_लिखो(isp, ULPI_SET(ULPI_FUNC_CTRL), r);
	usleep_range(1000, 2000);

	/* Read the line state */
	अगर (!isp1704_पढ़ो(isp, ULPI_DEBUG)) अणु
		/* Disable strong pull-up on DP (1.5K) */
		isp1704_ग_लिखो(isp, ULPI_CLR(ULPI_FUNC_CTRL),
				ULPI_FUNC_CTRL_TERMSELECT);
		वापस 1;
	पूर्ण

	/* Is it a अक्षरger or PS/2 connection */

	/* Enable weak pull-up resistor on DP */
	isp1704_ग_लिखो(isp, ULPI_SET(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	/* Disable strong pull-up on DP (1.5K) */
	isp1704_ग_लिखो(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_TERMSELECT);

	/* Enable weak pull-करोwn resistor on DM */
	isp1704_ग_लिखो(isp, ULPI_SET(ULPI_OTG_CTRL),
			ULPI_OTG_CTRL_DM_PULLDOWN);

	/* It's a अक्षरger अगर the line states are clear */
	अगर (!(isp1704_पढ़ो(isp, ULPI_DEBUG)))
		ret = 1;

	/* Disable weak pull-up resistor on DP */
	isp1704_ग_लिखो(isp, ULPI_CLR(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक isp1704_अक्षरger_detect(काष्ठा isp1704_अक्षरger *isp)
अणु
	अचिन्हित दीर्घ	समयout;
	u8		pwr_ctrl;
	पूर्णांक		ret = 0;

	pwr_ctrl = isp1704_पढ़ो(isp, ISP1704_PWR_CTRL);

	/* set SW control bit in PWR_CTRL रेजिस्टर */
	isp1704_ग_लिखो(isp, ISP1704_PWR_CTRL,
			ISP1704_PWR_CTRL_SWCTRL);

	/* enable manual अक्षरger detection */
	isp1704_ग_लिखो(isp, ULPI_SET(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_SWCTRL
			| ISP1704_PWR_CTRL_DPVSRC_EN);
	usleep_range(1000, 2000);

	समयout = jअगरfies + msecs_to_jअगरfies(300);
	करो अणु
		/* Check अगर there is a अक्षरger */
		अगर (isp1704_पढ़ो(isp, ISP1704_PWR_CTRL)
				& ISP1704_PWR_CTRL_VDAT_DET) अणु
			ret = isp1704_अक्षरger_verअगरy(isp);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!समय_after(jअगरfies, समयout) && isp->online);

	/* recover original state */
	isp1704_ग_लिखो(isp, ISP1704_PWR_CTRL, pwr_ctrl);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक isp1704_अक्षरger_detect_dcp(काष्ठा isp1704_अक्षरger *isp)
अणु
	अगर (isp1704_अक्षरger_detect(isp) &&
			isp1704_अक्षरger_type(isp) == POWER_SUPPLY_TYPE_USB_DCP)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम isp1704_अक्षरger_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा isp1704_अक्षरger	*isp =
		container_of(data, काष्ठा isp1704_अक्षरger, work);
	अटल DEFINE_MUTEX(lock);

	mutex_lock(&lock);

	चयन (isp->phy->last_event) अणु
	हाल USB_EVENT_VBUS:
		/* करो not call wall अक्षरger detection more बार */
		अगर (!isp->present) अणु
			isp->online = true;
			isp->present = 1;
			isp1704_अक्षरger_set_घातer(isp, 1);

			/* detect wall अक्षरger */
			अगर (isp1704_अक्षरger_detect_dcp(isp)) अणु
				isp->psy_desc.type = POWER_SUPPLY_TYPE_USB_DCP;
				isp->current_max = 1800;
			पूर्ण अन्यथा अणु
				isp->psy_desc.type = POWER_SUPPLY_TYPE_USB;
				isp->current_max = 500;
			पूर्ण

			/* enable data pullups */
			अगर (isp->phy->otg->gadget)
				usb_gadget_connect(isp->phy->otg->gadget);
		पूर्ण

		अगर (isp->psy_desc.type != POWER_SUPPLY_TYPE_USB_DCP) अणु
			/*
			 * Only 500mA here or high speed chirp
			 * handshaking may अवरोध
			 */
			अगर (isp->current_max > 500)
				isp->current_max = 500;

			अगर (isp->current_max > 100)
				isp->psy_desc.type = POWER_SUPPLY_TYPE_USB_CDP;
		पूर्ण
		अवरोध;
	हाल USB_EVENT_NONE:
		isp->online = false;
		isp->present = 0;
		isp->current_max = 0;
		isp->psy_desc.type = POWER_SUPPLY_TYPE_USB;

		/*
		 * Disable data pullups. We need to prevent the controller from
		 * क्रमागतerating.
		 *
		 * FIXME: This is here to allow अक्षरger detection with Host/HUB
		 * अक्षरgers. The pullups may be enabled अन्यथाwhere, so this can
		 * not be the final solution.
		 */
		अगर (isp->phy->otg->gadget)
			usb_gadget_disconnect(isp->phy->otg->gadget);

		isp1704_अक्षरger_set_घातer(isp, 0);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	घातer_supply_changed(isp->psy);
out:
	mutex_unlock(&lock);
पूर्ण

अटल पूर्णांक isp1704_notअगरier_call(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ val, व्योम *v)
अणु
	काष्ठा isp1704_अक्षरger *isp =
		container_of(nb, काष्ठा isp1704_अक्षरger, nb);

	schedule_work(&isp->work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक isp1704_अक्षरger_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा isp1704_अक्षरger *isp = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = isp->present;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = isp->online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		val->पूर्णांकval = isp->current_max;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = isp->model;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = "NXP";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property घातer_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल अंतरभूत पूर्णांक isp1704_test_ulpi(काष्ठा isp1704_अक्षरger *isp)
अणु
	पूर्णांक venकरोr;
	पूर्णांक product;
	पूर्णांक i;
	पूर्णांक ret;

	/* Test ULPI पूर्णांकerface */
	ret = isp1704_ग_लिखो(isp, ULPI_SCRATCH, 0xaa);
	अगर (ret < 0)
		वापस ret;

	ret = isp1704_पढ़ो(isp, ULPI_SCRATCH);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != 0xaa)
		वापस -ENODEV;

	/* Verअगरy the product and venकरोr id matches */
	venकरोr = isp1704_पढ़ो(isp, ULPI_VENDOR_ID_LOW);
	venकरोr |= isp1704_पढ़ो(isp, ULPI_VENDOR_ID_HIGH) << 8;
	अगर (venकरोr != NXP_VENDOR_ID)
		वापस -ENODEV;

	product = isp1704_पढ़ो(isp, ULPI_PRODUCT_ID_LOW);
	product |= isp1704_पढ़ो(isp, ULPI_PRODUCT_ID_HIGH) << 8;

	क्रम (i = 0; i < ARRAY_SIZE(isp170x_id); i++) अणु
		अगर (product == isp170x_id[i]) अणु
			प्र_लिखो(isp->model, "isp%x", product);
			वापस product;
		पूर्ण
	पूर्ण

	dev_err(isp->dev, "product id %x not matching known ids", product);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक isp1704_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा isp1704_अक्षरger	*isp;
	पूर्णांक			ret = -ENODEV;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	isp = devm_kzalloc(&pdev->dev, माप(*isp), GFP_KERNEL);
	अगर (!isp)
		वापस -ENOMEM;

	isp->enable_gpio = devm_gpiod_get(&pdev->dev, "nxp,enable",
					  GPIOD_OUT_HIGH);
	अगर (IS_ERR(isp->enable_gpio)) अणु
		ret = PTR_ERR(isp->enable_gpio);
		dev_err(&pdev->dev, "Could not get reset gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdev->dev.of_node)
		isp->phy = devm_usb_get_phy_by_phandle(&pdev->dev, "usb-phy", 0);
	अन्यथा
		isp->phy = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);

	अगर (IS_ERR(isp->phy)) अणु
		ret = PTR_ERR(isp->phy);
		dev_err(&pdev->dev, "usb_get_phy failed\n");
		जाओ fail0;
	पूर्ण

	isp->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, isp);

	isp1704_अक्षरger_set_घातer(isp, 1);

	ret = isp1704_test_ulpi(isp);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "isp1704_test_ulpi failed\n");
		जाओ fail1;
	पूर्ण

	isp->psy_desc.name		= "isp1704";
	isp->psy_desc.type		= POWER_SUPPLY_TYPE_USB;
	isp->psy_desc.properties	= घातer_props;
	isp->psy_desc.num_properties	= ARRAY_SIZE(घातer_props);
	isp->psy_desc.get_property	= isp1704_अक्षरger_get_property;

	psy_cfg.drv_data		= isp;

	isp->psy = घातer_supply_रेजिस्टर(isp->dev, &isp->psy_desc, &psy_cfg);
	अगर (IS_ERR(isp->psy)) अणु
		ret = PTR_ERR(isp->psy);
		dev_err(&pdev->dev, "power_supply_register failed\n");
		जाओ fail1;
	पूर्ण

	/*
	 * REVISIT: using work in order to allow the usb notअगरications to be
	 * made atomically in the future.
	 */
	INIT_WORK(&isp->work, isp1704_अक्षरger_work);

	isp->nb.notअगरier_call = isp1704_notअगरier_call;

	ret = usb_रेजिस्टर_notअगरier(isp->phy, &isp->nb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "usb_register_notifier failed\n");
		जाओ fail2;
	पूर्ण

	dev_info(isp->dev, "registered with product id %s\n", isp->model);

	/*
	 * Taking over the D+ pullup.
	 *
	 * FIXME: The device will be disconnected अगर it was alपढ़ोy
	 * क्रमागतerated. The अक्षरger driver should be always loaded beक्रमe any
	 * gadget is loaded.
	 */
	अगर (isp->phy->otg->gadget)
		usb_gadget_disconnect(isp->phy->otg->gadget);

	अगर (isp->phy->last_event == USB_EVENT_NONE)
		isp1704_अक्षरger_set_घातer(isp, 0);

	/* Detect अक्षरger अगर VBUS is valid (the cable was alपढ़ोy plugged). */
	अगर (isp->phy->last_event == USB_EVENT_VBUS &&
			!isp->phy->otg->शेष_a)
		schedule_work(&isp->work);

	वापस 0;
fail2:
	घातer_supply_unरेजिस्टर(isp->psy);
fail1:
	isp1704_अक्षरger_set_घातer(isp, 0);
fail0:
	dev_err(&pdev->dev, "failed to register isp1704 with error %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक isp1704_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा isp1704_अक्षरger *isp = platक्रमm_get_drvdata(pdev);

	usb_unरेजिस्टर_notअगरier(isp->phy, &isp->nb);
	घातer_supply_unरेजिस्टर(isp->psy);
	isp1704_अक्षरger_set_घातer(isp, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id omap_isp1704_of_match[] = अणु
	अणु .compatible = "nxp,isp1704", पूर्ण,
	अणु .compatible = "nxp,isp1707", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_isp1704_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver isp1704_अक्षरger_driver = अणु
	.driver = अणु
		.name = "isp1704_charger",
		.of_match_table = of_match_ptr(omap_isp1704_of_match),
	पूर्ण,
	.probe = isp1704_अक्षरger_probe,
	.हटाओ = isp1704_अक्षरger_हटाओ,
पूर्ण;

module_platक्रमm_driver(isp1704_अक्षरger_driver);

MODULE_ALIAS("platform:isp1704_charger");
MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("ISP170x USB Charger driver");
MODULE_LICENSE("GPL");
