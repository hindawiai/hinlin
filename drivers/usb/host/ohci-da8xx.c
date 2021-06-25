<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * TI DA8xx (OMAP-L1x) Bus Glue
 *
 * Derived from: ohci-omap.c and ohci-s3c2410.c
 * Copyright (C) 2008-2009 MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ohci.h"

#घोषणा DRIVER_DESC "DA8XX"
#घोषणा DRV_NAME "ohci-da8xx"

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_da8xx_hc_driver;

अटल पूर्णांक (*orig_ohci_hub_control)(काष्ठा usb_hcd  *hcd, u16 typeReq,
			u16 wValue, u16 wIndex, अक्षर *buf, u16 wLength);
अटल पूर्णांक (*orig_ohci_hub_status_data)(काष्ठा usb_hcd *hcd, अक्षर *buf);

काष्ठा da8xx_ohci_hcd अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा clk *usb11_clk;
	काष्ठा phy *usb11_phy;
	काष्ठा regulator *vbus_reg;
	काष्ठा notअगरier_block nb;
	काष्ठा gpio_desc *oc_gpio;
पूर्ण;

#घोषणा to_da8xx_ohci(hcd) (काष्ठा da8xx_ohci_hcd *)(hcd_to_ohci(hcd)->priv)

/* Over-current indicator change biपंचांगask */
अटल अस्थिर u16 ocic_mask;

अटल पूर्णांक ohci_da8xx_enable(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	पूर्णांक ret;

	ret = clk_prepare_enable(da8xx_ohci->usb11_clk);
	अगर (ret)
		वापस ret;

	ret = phy_init(da8xx_ohci->usb11_phy);
	अगर (ret)
		जाओ err_phy_init;

	ret = phy_घातer_on(da8xx_ohci->usb11_phy);
	अगर (ret)
		जाओ err_phy_घातer_on;

	वापस 0;

err_phy_घातer_on:
	phy_निकास(da8xx_ohci->usb11_phy);
err_phy_init:
	clk_disable_unprepare(da8xx_ohci->usb11_clk);

	वापस ret;
पूर्ण

अटल व्योम ohci_da8xx_disable(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);

	phy_घातer_off(da8xx_ohci->usb11_phy);
	phy_निकास(da8xx_ohci->usb11_phy);
	clk_disable_unprepare(da8xx_ohci->usb11_clk);
पूर्ण

अटल पूर्णांक ohci_da8xx_set_घातer(काष्ठा usb_hcd *hcd, पूर्णांक on)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	काष्ठा device *dev = hcd->self.controller;
	पूर्णांक ret;

	अगर (!da8xx_ohci->vbus_reg)
		वापस 0;

	अगर (on) अणु
		ret = regulator_enable(da8xx_ohci->vbus_reg);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = regulator_disable(da8xx_ohci->vbus_reg);
		अगर (ret) अणु
			dev_err(dev, "Failed  to disable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_da8xx_get_घातer(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);

	अगर (da8xx_ohci->vbus_reg)
		वापस regulator_is_enabled(da8xx_ohci->vbus_reg);

	वापस 1;
पूर्ण

अटल पूर्णांक ohci_da8xx_get_oci(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;

	अगर (da8xx_ohci->oc_gpio)
		वापस gpiod_get_value_cansleep(da8xx_ohci->oc_gpio);

	अगर (!da8xx_ohci->vbus_reg)
		वापस 0;

	ret = regulator_get_error_flags(da8xx_ohci->vbus_reg, &flags);
	अगर (ret)
		वापस ret;

	अगर (flags & REGULATOR_ERROR_OVER_CURRENT)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_da8xx_has_set_घातer(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);

	अगर (da8xx_ohci->vbus_reg)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_da8xx_has_oci(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);

	अगर (da8xx_ohci->oc_gpio)
		वापस 1;

	अगर (da8xx_ohci->vbus_reg)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_da8xx_has_potpgt(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev		= hcd->self.controller;
	काष्ठा da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);

	अगर (hub && hub->potpgt)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_da8xx_regulator_event(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci =
				container_of(nb, काष्ठा da8xx_ohci_hcd, nb);

	अगर (event & REGULATOR_EVENT_OVER_CURRENT) अणु
		ocic_mask |= 1 << 1;
		ohci_da8xx_set_घातer(da8xx_ohci->hcd, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t ohci_da8xx_oc_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = data;
	काष्ठा device *dev = da8xx_ohci->hcd->self.controller;
	पूर्णांक ret;

	अगर (gpiod_get_value_cansleep(da8xx_ohci->oc_gpio) &&
	    da8xx_ohci->vbus_reg) अणु
		ret = regulator_disable(da8xx_ohci->vbus_reg);
		अगर (ret)
			dev_err(dev, "Failed to disable regulator: %d\n", ret);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ohci_da8xx_रेजिस्टर_notअगरy(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	काष्ठा device *dev		= hcd->self.controller;
	पूर्णांक ret = 0;

	अगर (!da8xx_ohci->oc_gpio && da8xx_ohci->vbus_reg) अणु
		da8xx_ohci->nb.notअगरier_call = ohci_da8xx_regulator_event;
		ret = devm_regulator_रेजिस्टर_notअगरier(da8xx_ohci->vbus_reg,
						&da8xx_ohci->nb);
	पूर्ण

	अगर (ret)
		dev_err(dev, "Failed to register notifier: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_da8xx_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev		= hcd->self.controller;
	काष्ठा da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);
	काष्ठा ohci_hcd	*ohci		= hcd_to_ohci(hcd);
	पूर्णांक result;
	u32 rh_a;

	dev_dbg(dev, "starting USB controller\n");

	result = ohci_da8xx_enable(hcd);
	अगर (result < 0)
		वापस result;

	/*
	 * DA8xx only have 1 port connected to the pins but the HC root hub
	 * रेजिस्टर A reports 2 ports, thus we'll have to override it...
	 */
	ohci->num_ports = 1;

	result = ohci_setup(hcd);
	अगर (result < 0) अणु
		ohci_da8xx_disable(hcd);
		वापस result;
	पूर्ण

	/*
	 * Since we're providing a board-specअगरic root hub port घातer control
	 * and over-current reporting, we have to override the HC root hub A
	 * रेजिस्टर's शेष value, so that ohci_hub_control() could वापस
	 * the correct hub descriptor...
	 */
	rh_a = ohci_पढ़ोl(ohci, &ohci->regs->roothub.a);
	अगर (ohci_da8xx_has_set_घातer(hcd)) अणु
		rh_a &= ~RH_A_NPS;
		rh_a |=  RH_A_PSM;
	पूर्ण
	अगर (ohci_da8xx_has_oci(hcd)) अणु
		rh_a &= ~RH_A_NOCP;
		rh_a |=  RH_A_OCPM;
	पूर्ण
	अगर (ohci_da8xx_has_potpgt(hcd)) अणु
		rh_a &= ~RH_A_POTPGT;
		rh_a |= hub->potpgt << 24;
	पूर्ण
	ohci_ग_लिखोl(ohci, rh_a, &ohci->regs->roothub.a);

	वापस result;
पूर्ण

/*
 * Update the status data from the hub with the over-current indicator change.
 */
अटल पूर्णांक ohci_da8xx_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	पूर्णांक length		= orig_ohci_hub_status_data(hcd, buf);

	/* See अगर we have OCIC bit set on port 1 */
	अगर (ocic_mask & (1 << 1)) अणु
		dev_dbg(hcd->self.controller, "over-current indicator change "
			"on port 1\n");

		अगर (!length)
			length = 1;

		buf[0] |= 1 << 1;
	पूर्ण
	वापस length;
पूर्ण

/*
 * Look at the control requests to the root hub and see अगर we need to override.
 */
अटल पूर्णांक ohci_da8xx_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
				  u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा device *dev		= hcd->self.controller;
	पूर्णांक temp;

	चयन (typeReq) अणु
	हाल GetPortStatus:
		/* Check the port number */
		अगर (wIndex != 1)
			अवरोध;

		dev_dbg(dev, "GetPortStatus(%u)\n", wIndex);

		temp = roothub_portstatus(hcd_to_ohci(hcd), wIndex - 1);

		/* The port घातer status (PPS) bit शेषs to 1 */
		अगर (!ohci_da8xx_get_घातer(hcd))
			temp &= ~RH_PS_PPS;

		/* The port over-current indicator (POCI) bit is always 0 */
		अगर (ohci_da8xx_get_oci(hcd) > 0)
			temp |=  RH_PS_POCI;

		/* The over-current indicator change (OCIC) bit is 0 too */
		अगर (ocic_mask & (1 << wIndex))
			temp |=  RH_PS_OCIC;

		put_unaligned(cpu_to_le32(temp), (__le32 *)buf);
		वापस 0;
	हाल SetPortFeature:
		temp = 1;
		जाओ check_port;
	हाल ClearPortFeature:
		temp = 0;

check_port:
		/* Check the port number */
		अगर (wIndex != 1)
			अवरोध;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(dev, "%sPortFeature(%u): %s\n",
				temp ? "Set" : "Clear", wIndex, "POWER");

			वापस ohci_da8xx_set_घातer(hcd, temp) ? -EPIPE : 0;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(dev, "%sPortFeature(%u): %s\n",
				temp ? "Set" : "Clear", wIndex,
				"C_OVER_CURRENT");

			अगर (temp)
				ocic_mask |= 1 << wIndex;
			अन्यथा
				ocic_mask &= ~(1 << wIndex);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस orig_ohci_hub_control(hcd, typeReq, wValue,
			wIndex, buf, wLength);
पूर्ण

/*-------------------------------------------------------------------------*/
#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da8xx_ohci_ids[] = अणु
	अणु .compatible = "ti,da830-ohci" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da8xx_ohci_ids);
#पूर्ण_अगर

अटल पूर्णांक ohci_da8xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da8xx_ohci_hcd *da8xx_ohci;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error, hcd_irq, oc_irq;
	काष्ठा usb_hcd	*hcd;
	काष्ठा resource *mem;

	hcd = usb_create_hcd(&ohci_da8xx_hc_driver, dev, dev_name(dev));
	अगर (!hcd)
		वापस -ENOMEM;

	da8xx_ohci = to_da8xx_ohci(hcd);
	da8xx_ohci->hcd = hcd;

	da8xx_ohci->usb11_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(da8xx_ohci->usb11_clk)) अणु
		error = PTR_ERR(da8xx_ohci->usb11_clk);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get clock.\n");
		जाओ err;
	पूर्ण

	da8xx_ohci->usb11_phy = devm_phy_get(dev, "usb-phy");
	अगर (IS_ERR(da8xx_ohci->usb11_phy)) अणु
		error = PTR_ERR(da8xx_ohci->usb11_phy);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get phy.\n");
		जाओ err;
	पूर्ण

	da8xx_ohci->vbus_reg = devm_regulator_get_optional(dev, "vbus");
	अगर (IS_ERR(da8xx_ohci->vbus_reg)) अणु
		error = PTR_ERR(da8xx_ohci->vbus_reg);
		अगर (error == -ENODEV) अणु
			da8xx_ohci->vbus_reg = शून्य;
		पूर्ण अन्यथा अगर (error == -EPROBE_DEFER) अणु
			जाओ err;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Failed to get regulator\n");
			जाओ err;
		पूर्ण
	पूर्ण

	da8xx_ohci->oc_gpio = devm_gpiod_get_optional(dev, "oc", GPIOD_IN);
	अगर (IS_ERR(da8xx_ohci->oc_gpio)) अणु
		error = PTR_ERR(da8xx_ohci->oc_gpio);
		जाओ err;
	पूर्ण

	अगर (da8xx_ohci->oc_gpio) अणु
		oc_irq = gpiod_to_irq(da8xx_ohci->oc_gpio);
		अगर (oc_irq < 0) अणु
			error = oc_irq;
			जाओ err;
		पूर्ण

		error = devm_request_thपढ़ोed_irq(dev, oc_irq, शून्य,
				ohci_da8xx_oc_thपढ़ो, IRQF_TRIGGER_RISING |
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"OHCI over-current indicator", da8xx_ohci);
		अगर (error)
			जाओ err;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(hcd->regs)) अणु
		error = PTR_ERR(hcd->regs);
		जाओ err;
	पूर्ण
	hcd->rsrc_start = mem->start;
	hcd->rsrc_len = resource_size(mem);

	hcd_irq = platक्रमm_get_irq(pdev, 0);
	अगर (hcd_irq < 0) अणु
		error = -ENODEV;
		जाओ err;
	पूर्ण

	error = usb_add_hcd(hcd, hcd_irq, 0);
	अगर (error)
		जाओ err;

	device_wakeup_enable(hcd->self.controller);

	error = ohci_da8xx_रेजिस्टर_notअगरy(hcd);
	अगर (error)
		जाओ err_हटाओ_hcd;

	वापस 0;

err_हटाओ_hcd:
	usb_हटाओ_hcd(hcd);
err:
	usb_put_hcd(hcd);
	वापस error;
पूर्ण

अटल पूर्णांक ohci_da8xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ohci_da8xx_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t message)
अणु
	काष्ठा usb_hcd	*hcd	= platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_hcd	*ohci	= hcd_to_ohci(hcd);
	bool		करो_wakeup	= device_may_wakeup(&pdev->dev);
	पूर्णांक		ret;


	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	ohci_da8xx_disable(hcd);
	hcd->state = HC_STATE_SUSPENDED;

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_da8xx_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd	*hcd	= platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd	*ohci	= hcd_to_ohci(hcd);
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_da8xx_enable(hcd);
	अगर (ret)
		वापस ret;

	ohci_resume(hcd, false);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ohci_driver_overrides da8xx_overrides __initस्थिर = अणु
	.reset		 = ohci_da8xx_reset,
	.extra_priv_size = माप(काष्ठा da8xx_ohci_hcd),
पूर्ण;

/*
 * Driver definition to रेजिस्टर with platक्रमm काष्ठाure.
 */
अटल काष्ठा platक्रमm_driver ohci_hcd_da8xx_driver = अणु
	.probe		= ohci_da8xx_probe,
	.हटाओ		= ohci_da8xx_हटाओ,
	.shutकरोwn 	= usb_hcd_platक्रमm_shutकरोwn,
#अगर_घोषित	CONFIG_PM
	.suspend	= ohci_da8xx_suspend,
	.resume		= ohci_da8xx_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = of_match_ptr(da8xx_ohci_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ohci_da8xx_init(व्योम)
अणु

	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", DRV_NAME);
	ohci_init_driver(&ohci_da8xx_hc_driver, &da8xx_overrides);

	/*
	 * The Davinci da8xx HW has some unusual quirks, which require
	 * da8xx-specअगरic workarounds. We override certain hc_driver
	 * functions here to achieve that. We explicitly करो not enhance
	 * ohci_driver_overrides to allow this more easily, since this
	 * is an unusual हाल, and we करोn't want to encourage others to
	 * override these functions by making it too easy.
	 */

	orig_ohci_hub_control = ohci_da8xx_hc_driver.hub_control;
	orig_ohci_hub_status_data = ohci_da8xx_hc_driver.hub_status_data;

	ohci_da8xx_hc_driver.hub_status_data     = ohci_da8xx_hub_status_data;
	ohci_da8xx_hc_driver.hub_control         = ohci_da8xx_hub_control;

	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_da8xx_driver);
पूर्ण
module_init(ohci_da8xx_init);

अटल व्योम __निकास ohci_da8xx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_da8xx_driver);
पूर्ण
module_निकास(ohci_da8xx_निकास);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
