<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 *  Copyright (C) 2004 SAN People (Pty) Ltd.
 *  Copyright (C) 2005 Thibaut VARENE <varenet@parisc-linux.org>
 *
 * AT91 Bus Glue
 *
 * Based on fragments of 2.4 driver by Rick Bronson.
 * Based on ohci-omap.c
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/aपंचांगel.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <soc/at91/aपंचांगel-sfr.h>

#समावेश "ohci.h"

#घोषणा valid_port(index)	((index) >= 0 && (index) < AT91_MAX_USBH_PORTS)
#घोषणा at91_क्रम_each_port(index)	\
		क्रम ((index) = 0; (index) < AT91_MAX_USBH_PORTS; (index)++)

/* पूर्णांकerface, function and usb घड़ीs; someबार also an AHB घड़ी */
#घोषणा hcd_to_ohci_at91_priv(h) \
	((काष्ठा ohci_at91_priv *)hcd_to_ohci(h)->priv)

#घोषणा AT91_MAX_USBH_PORTS	3
काष्ठा at91_usbh_data अणु
	काष्ठा gpio_desc *vbus_pin[AT91_MAX_USBH_PORTS];
	काष्ठा gpio_desc *overcurrent_pin[AT91_MAX_USBH_PORTS];
	u8 ports;				/* number of ports on root hub */
	u8 overcurrent_supported;
	u8 overcurrent_status[AT91_MAX_USBH_PORTS];
	u8 overcurrent_changed[AT91_MAX_USBH_PORTS];
पूर्ण;

काष्ठा ohci_at91_priv अणु
	काष्ठा clk *iclk;
	काष्ठा clk *fclk;
	काष्ठा clk *hclk;
	bool घड़ीed;
	bool wakeup;		/* Saved wake-up state क्रम resume */
	काष्ठा regmap *sfr_regmap;
पूर्ण;
/* पूर्णांकerface and function घड़ीs; someबार also an AHB घड़ी */

#घोषणा DRIVER_DESC "OHCI Atmel driver"

अटल स्थिर अक्षर hcd_name[] = "ohci-atmel";

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_at91_hc_driver;

अटल स्थिर काष्ठा ohci_driver_overrides ohci_at91_drv_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा ohci_at91_priv),
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल व्योम at91_start_घड़ी(काष्ठा ohci_at91_priv *ohci_at91)
अणु
	अगर (ohci_at91->घड़ीed)
		वापस;

	clk_set_rate(ohci_at91->fclk, 48000000);
	clk_prepare_enable(ohci_at91->hclk);
	clk_prepare_enable(ohci_at91->iclk);
	clk_prepare_enable(ohci_at91->fclk);
	ohci_at91->घड़ीed = true;
पूर्ण

अटल व्योम at91_stop_घड़ी(काष्ठा ohci_at91_priv *ohci_at91)
अणु
	अगर (!ohci_at91->घड़ीed)
		वापस;

	clk_disable_unprepare(ohci_at91->fclk);
	clk_disable_unprepare(ohci_at91->iclk);
	clk_disable_unprepare(ohci_at91->hclk);
	ohci_at91->घड़ीed = false;
पूर्ण

अटल व्योम at91_start_hc(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_regs __iomem *regs = hcd->regs;
	काष्ठा ohci_at91_priv *ohci_at91 = hcd_to_ohci_at91_priv(hcd);

	dev_dbg(&pdev->dev, "start\n");

	/*
	 * Start the USB घड़ीs.
	 */
	at91_start_घड़ी(ohci_at91);

	/*
	 * The USB host controller must reमुख्य in reset.
	 */
	ग_लिखोl(0, &regs->control);
पूर्ण

अटल व्योम at91_stop_hc(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_at91_priv *ohci_at91 = hcd_to_ohci_at91_priv(hcd);

	dev_dbg(&pdev->dev, "stop\n");

	/*
	 * Put the USB host controller पूर्णांकo reset.
	 */
	usb_hcd_platक्रमm_shutकरोwn(pdev);

	/*
	 * Stop the USB घड़ीs.
	 */
	at91_stop_घड़ी(ohci_at91);
पूर्ण


/*-------------------------------------------------------------------------*/

अटल व्योम usb_hcd_at91_हटाओ (काष्ठा usb_hcd *, काष्ठा platक्रमm_device *);

अटल काष्ठा regmap *at91_dt_syscon_sfr(व्योम)
अणु
	काष्ठा regmap *regmap;

	regmap = syscon_regmap_lookup_by_compatible("atmel,sama5d2-sfr");
	अगर (IS_ERR(regmap)) अणु
		regmap = syscon_regmap_lookup_by_compatible("microchip,sam9x60-sfr");
		अगर (IS_ERR(regmap))
			regmap = शून्य;
	पूर्ण

	वापस regmap;
पूर्ण

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */


/*
 * usb_hcd_at91_probe - initialize AT91-based HCDs
 * @driver:	Poपूर्णांकer to hc driver instance
 * @pdev:	USB controller to probe
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक usb_hcd_at91_probe(स्थिर काष्ठा hc_driver *driver,
			काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_usbh_data *board;
	काष्ठा ohci_hcd *ohci;
	पूर्णांक retval;
	काष्ठा usb_hcd *hcd;
	काष्ठा ohci_at91_priv *ohci_at91;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_dbg(dev, "hcd probe: missing irq resource\n");
		वापस irq;
	पूर्ण

	hcd = usb_create_hcd(driver, dev, "at91");
	अगर (!hcd)
		वापस -ENOMEM;
	ohci_at91 = hcd_to_ohci_at91_priv(hcd);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ err;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	ohci_at91->iclk = devm_clk_get(dev, "ohci_clk");
	अगर (IS_ERR(ohci_at91->iclk)) अणु
		dev_err(dev, "failed to get ohci_clk\n");
		retval = PTR_ERR(ohci_at91->iclk);
		जाओ err;
	पूर्ण
	ohci_at91->fclk = devm_clk_get(dev, "uhpck");
	अगर (IS_ERR(ohci_at91->fclk)) अणु
		dev_err(dev, "failed to get uhpck\n");
		retval = PTR_ERR(ohci_at91->fclk);
		जाओ err;
	पूर्ण
	ohci_at91->hclk = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(ohci_at91->hclk)) अणु
		dev_err(dev, "failed to get hclk\n");
		retval = PTR_ERR(ohci_at91->hclk);
		जाओ err;
	पूर्ण

	ohci_at91->sfr_regmap = at91_dt_syscon_sfr();
	अगर (!ohci_at91->sfr_regmap)
		dev_dbg(dev, "failed to find sfr node\n");

	board = hcd->self.controller->platक्रमm_data;
	ohci = hcd_to_ohci(hcd);
	ohci->num_ports = board->ports;
	at91_start_hc(pdev);

	/*
	 * The RemoteWakeupConnected bit has to be set explicitly
	 * beक्रमe calling ohci_run. The reset value of this bit is 0.
	 */
	ohci->hc_control = OHCI_CTRL_RWC;

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस retval;
	पूर्ण

	/* Error handling */
	at91_stop_hc(pdev);

 err:
	usb_put_hcd(hcd);
	वापस retval;
पूर्ण


/* may be called with controller, bus, and devices active */

/*
 * usb_hcd_at91_हटाओ - shutकरोwn processing क्रम AT91-based HCDs
 * @hcd:	USB controller to हटाओ
 * @pdev:	Platक्रमm device required क्रम cleanup
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of usb_hcd_at91_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, "rmmod" or something similar.
 */
अटल व्योम usb_hcd_at91_हटाओ(काष्ठा usb_hcd *hcd,
				काष्ठा platक्रमm_device *pdev)
अणु
	usb_हटाओ_hcd(hcd);
	at91_stop_hc(pdev);
	usb_put_hcd(hcd);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम ohci_at91_usb_set_घातer(काष्ठा at91_usbh_data *pdata, पूर्णांक port, पूर्णांक enable)
अणु
	अगर (!valid_port(port))
		वापस;

	gpiod_set_value(pdata->vbus_pin[port], enable);
पूर्ण

अटल पूर्णांक ohci_at91_usb_get_घातer(काष्ठा at91_usbh_data *pdata, पूर्णांक port)
अणु
	अगर (!valid_port(port))
		वापस -EINVAL;

	वापस gpiod_get_value(pdata->vbus_pin[port]);
पूर्ण

/*
 * Update the status data from the hub with the over-current indicator change.
 */
अटल पूर्णांक ohci_at91_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा at91_usbh_data *pdata = hcd->self.controller->platक्रमm_data;
	पूर्णांक length = ohci_hub_status_data(hcd, buf);
	पूर्णांक port;

	at91_क्रम_each_port(port) अणु
		अगर (pdata->overcurrent_changed[port]) अणु
			अगर (!length)
				length = 1;
			buf[0] |= 1 << (port + 1);
		पूर्ण
	पूर्ण

	वापस length;
पूर्ण

अटल पूर्णांक ohci_at91_port_suspend(काष्ठा regmap *regmap, u8 set)
अणु
	u32 regval;
	पूर्णांक ret;

	अगर (!regmap)
		वापस 0;

	ret = regmap_पढ़ो(regmap, AT91_SFR_OHCIICR, &regval);
	अगर (ret)
		वापस ret;

	अगर (set)
		regval |= AT91_OHCIICR_USB_SUSPEND;
	अन्यथा
		regval &= ~AT91_OHCIICR_USB_SUSPEND;

	regmap_ग_लिखो(regmap, AT91_SFR_OHCIICR, regval);

	वापस 0;
पूर्ण

/*
 * Look at the control requests to the root hub and see अगर we need to override.
 */
अटल पूर्णांक ohci_at91_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
				 u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा at91_usbh_data *pdata = dev_get_platdata(hcd->self.controller);
	काष्ठा ohci_at91_priv *ohci_at91 = hcd_to_ohci_at91_priv(hcd);
	काष्ठा usb_hub_descriptor *desc;
	पूर्णांक ret = -EINVAL;
	u32 *data = (u32 *)buf;

	dev_dbg(hcd->self.controller,
		"ohci_at91_hub_control(%p,0x%04x,0x%04x,0x%04x,%p,%04x)\n",
		hcd, typeReq, wValue, wIndex, buf, wLength);

	wIndex--;

	चयन (typeReq) अणु
	हाल SetPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hcd->self.controller, "SetPortFeat: POWER\n");
			अगर (valid_port(wIndex)) अणु
				ohci_at91_usb_set_घातer(pdata, wIndex, 1);
				ret = 0;
			पूर्ण

			जाओ out;

		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(hcd->self.controller, "SetPortFeat: SUSPEND\n");
			अगर (valid_port(wIndex) && ohci_at91->sfr_regmap) अणु
				ohci_at91_port_suspend(ohci_at91->sfr_regmap,
						       1);
				वापस 0;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ClearPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: C_OVER_CURRENT\n");

			अगर (valid_port(wIndex)) अणु
				pdata->overcurrent_changed[wIndex] = 0;
				pdata->overcurrent_status[wIndex] = 0;
			पूर्ण

			जाओ out;

		हाल USB_PORT_FEAT_OVER_CURRENT:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: OVER_CURRENT\n");

			अगर (valid_port(wIndex))
				pdata->overcurrent_status[wIndex] = 0;

			जाओ out;

		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: POWER\n");

			अगर (valid_port(wIndex)) अणु
				ohci_at91_usb_set_घातer(pdata, wIndex, 0);
				वापस 0;
			पूर्ण
			अवरोध;

		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(hcd->self.controller, "ClearPortFeature: SUSPEND\n");
			अगर (valid_port(wIndex) && ohci_at91->sfr_regmap) अणु
				ohci_at91_port_suspend(ohci_at91->sfr_regmap,
						       0);
				वापस 0;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = ohci_hub_control(hcd, typeReq, wValue, wIndex + 1, buf, wLength);
	अगर (ret)
		जाओ out;

	चयन (typeReq) अणु
	हाल GetHubDescriptor:

		/* update the hub's descriptor */

		desc = (काष्ठा usb_hub_descriptor *)buf;

		dev_dbg(hcd->self.controller, "wHubCharacteristics 0x%04x\n",
			desc->wHubCharacteristics);

		/* हटाओ the old configurations क्रम घातer-चयनing, and
		 * over-current protection, and insert our new configuration
		 */

		desc->wHubCharacteristics &= ~cpu_to_le16(HUB_CHAR_LPSM);
		desc->wHubCharacteristics |=
			cpu_to_le16(HUB_CHAR_INDV_PORT_LPSM);

		अगर (pdata->overcurrent_supported) अणु
			desc->wHubCharacteristics &= ~cpu_to_le16(HUB_CHAR_OCPM);
			desc->wHubCharacteristics |=
				cpu_to_le16(HUB_CHAR_INDV_PORT_OCPM);
		पूर्ण

		dev_dbg(hcd->self.controller, "wHubCharacteristics after 0x%04x\n",
			desc->wHubCharacteristics);

		वापस ret;

	हाल GetPortStatus:
		/* check port status */

		dev_dbg(hcd->self.controller, "GetPortStatus(%d)\n", wIndex);

		अगर (valid_port(wIndex)) अणु
			अगर (!ohci_at91_usb_get_घातer(pdata, wIndex))
				*data &= ~cpu_to_le32(RH_PS_PPS);

			अगर (pdata->overcurrent_changed[wIndex])
				*data |= cpu_to_le32(RH_PS_OCIC);

			अगर (pdata->overcurrent_status[wIndex])
				*data |= cpu_to_le32(RH_PS_POCI);
		पूर्ण
	पूर्ण

 out:
	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल irqवापस_t ohci_hcd_at91_overcurrent_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा at91_usbh_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक val, port;

	/* From the GPIO notअगरying the over-current situation, find
	 * out the corresponding port */
	at91_क्रम_each_port(port) अणु
		अगर (gpiod_to_irq(pdata->overcurrent_pin[port]) == irq)
			अवरोध;
	पूर्ण

	अगर (port == AT91_MAX_USBH_PORTS) अणु
		dev_err(& pdev->dev, "overcurrent interrupt from unknown GPIO\n");
		वापस IRQ_HANDLED;
	पूर्ण

	val = gpiod_get_value(pdata->overcurrent_pin[port]);

	/* When notअगरied of an over-current situation, disable घातer
	   on the corresponding port, and mark this port in
	   over-current. */
	अगर (!val) अणु
		ohci_at91_usb_set_घातer(pdata, port, 0);
		pdata->overcurrent_status[port]  = 1;
		pdata->overcurrent_changed[port] = 1;
	पूर्ण

	dev_dbg(& pdev->dev, "overcurrent situation %s\n",
		val ? "exited" : "notified");

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_ohci_dt_ids[] = अणु
	अणु .compatible = "atmel,at91rm9200-ohci" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, at91_ohci_dt_ids);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ohci_hcd_at91_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा at91_usbh_data	*pdata;
	पूर्णांक			i;
	पूर्णांक			ret;
	पूर्णांक			err;
	u32			ports;

	/* Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdev->dev.platक्रमm_data = pdata;

	अगर (!of_property_पढ़ो_u32(np, "num-ports", &ports))
		pdata->ports = ports;

	at91_क्रम_each_port(i) अणु
		अगर (i >= pdata->ports)
			अवरोध;

		pdata->vbus_pin[i] =
			devm_gpiod_get_index_optional(&pdev->dev, "atmel,vbus",
						      i, GPIOD_OUT_HIGH);
		अगर (IS_ERR(pdata->vbus_pin[i])) अणु
			err = PTR_ERR(pdata->vbus_pin[i]);
			dev_err(&pdev->dev, "unable to claim gpio \"vbus\": %d\n", err);
			जारी;
		पूर्ण
	पूर्ण

	at91_क्रम_each_port(i) अणु
		अगर (i >= pdata->ports)
			अवरोध;

		pdata->overcurrent_pin[i] =
			devm_gpiod_get_index_optional(&pdev->dev, "atmel,oc",
						      i, GPIOD_IN);
		अगर (!pdata->overcurrent_pin[i])
			जारी;
		अगर (IS_ERR(pdata->overcurrent_pin[i])) अणु
			err = PTR_ERR(pdata->overcurrent_pin[i]);
			dev_err(&pdev->dev, "unable to claim gpio \"overcurrent\": %d\n", err);
			जारी;
		पूर्ण

		ret = devm_request_irq(&pdev->dev,
				       gpiod_to_irq(pdata->overcurrent_pin[i]),
				       ohci_hcd_at91_overcurrent_irq,
				       IRQF_SHARED,
				       "ohci_overcurrent", pdev);
		अगर (ret)
			dev_info(&pdev->dev, "failed to request gpio \"overcurrent\" IRQ\n");
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);
	वापस usb_hcd_at91_probe(&ohci_at91_hc_driver, pdev);
पूर्ण

अटल पूर्णांक ohci_hcd_at91_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_usbh_data	*pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक			i;

	अगर (pdata) अणु
		at91_क्रम_each_port(i)
			ohci_at91_usb_set_घातer(pdata, i, 0);
	पूर्ण

	device_init_wakeup(&pdev->dev, 0);
	usb_hcd_at91_हटाओ(platक्रमm_get_drvdata(pdev), pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
ohci_hcd_at91_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd	*hcd = dev_get_drvdata(dev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	काष्ठा ohci_at91_priv *ohci_at91 = hcd_to_ohci_at91_priv(hcd);
	पूर्णांक		ret;

	/*
	 * Disable wakeup अगर we are going to sleep with slow घड़ी mode
	 * enabled.
	 */
	ohci_at91->wakeup = device_may_wakeup(dev)
			&& !at91_suspend_entering_slow_घड़ी();

	अगर (ohci_at91->wakeup)
		enable_irq_wake(hcd->irq);

	ohci_at91_port_suspend(ohci_at91->sfr_regmap, 1);

	ret = ohci_suspend(hcd, ohci_at91->wakeup);
	अगर (ret) अणु
		अगर (ohci_at91->wakeup)
			disable_irq_wake(hcd->irq);
		वापस ret;
	पूर्ण
	/*
	 * The पूर्णांकegrated transceivers seem unable to notice disconnect,
	 * reconnect, or wakeup without the 48 MHz घड़ी active.  so क्रम
	 * correctness, always discard connection state (using reset).
	 *
	 * REVISIT: some boards will be able to turn VBUS off...
	 */
	अगर (!ohci_at91->wakeup) अणु
		ohci->rh_state = OHCI_RH_HALTED;

		/* flush the ग_लिखोs */
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
		msleep(1);
		at91_stop_घड़ी(ohci_at91);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused
ohci_hcd_at91_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd	*hcd = dev_get_drvdata(dev);
	काष्ठा ohci_at91_priv *ohci_at91 = hcd_to_ohci_at91_priv(hcd);

	अगर (ohci_at91->wakeup)
		disable_irq_wake(hcd->irq);
	अन्यथा
		at91_start_घड़ी(ohci_at91);

	ohci_resume(hcd, false);

	ohci_at91_port_suspend(ohci_at91->sfr_regmap, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ohci_hcd_at91_pm_ops, ohci_hcd_at91_drv_suspend,
					ohci_hcd_at91_drv_resume);

अटल काष्ठा platक्रमm_driver ohci_hcd_at91_driver = अणु
	.probe		= ohci_hcd_at91_drv_probe,
	.हटाओ		= ohci_hcd_at91_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "at91_ohci",
		.pm	= &ohci_hcd_at91_pm_ops,
		.of_match_table	= at91_ohci_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ohci_at91_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	ohci_init_driver(&ohci_at91_hc_driver, &ohci_at91_drv_overrides);

	/*
	 * The Aपंचांगel HW has some unusual quirks, which require Aपंचांगel-specअगरic
	 * workarounds. We override certain hc_driver functions here to
	 * achieve that. We explicitly करो not enhance ohci_driver_overrides to
	 * allow this more easily, since this is an unusual हाल, and we करोn't
	 * want to encourage others to override these functions by making it
	 * too easy.
	 */

	ohci_at91_hc_driver.hub_status_data	= ohci_at91_hub_status_data;
	ohci_at91_hc_driver.hub_control		= ohci_at91_hub_control;

	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_at91_driver);
पूर्ण
module_init(ohci_at91_init);

अटल व्योम __निकास ohci_at91_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_at91_driver);
पूर्ण
module_निकास(ohci_at91_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at91_ohci");
