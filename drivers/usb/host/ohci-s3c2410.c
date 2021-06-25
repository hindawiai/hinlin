<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 * (C) Copyright 2002 Hewlett-Packard Company
 *
 * USB Bus Glue क्रम Samsung S3C2410
 *
 * Written by Christopher Hoover <ch@hpl.hp.com>
 * Based on fragments of previous driver by Russell King et al.
 *
 * Modअगरied क्रम S3C2410 from ohci-sa1111.c, ohci-omap.c and ohci-lh7a40.c
 *	by Ben Dooks, <ben@simtec.co.uk>
 *	Copyright (C) 2004 Simtec Electronics
 *
 * Thanks to basprog@mail.ru क्रम updates to newer kernels
 *
 * This file is licenced under the GPL.
*/

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/usb-ohci-s3c2410.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"


#घोषणा valid_port(idx) ((idx) == 1 || (idx) == 2)

/* घड़ी device associated with the hcd */


#घोषणा DRIVER_DESC "OHCI S3C2410 driver"

अटल स्थिर अक्षर hcd_name[] = "ohci-s3c2410";

अटल काष्ठा clk *clk;
अटल काष्ठा clk *usb_clk;

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_s3c2410_hc_driver;

/* क्रमward definitions */

अटल व्योम s3c2410_hcd_oc(काष्ठा s3c2410_hcd_info *info, पूर्णांक port_oc);

/* conversion functions */

अटल काष्ठा s3c2410_hcd_info *to_s3c2410_info(काष्ठा usb_hcd *hcd)
अणु
	वापस dev_get_platdata(hcd->self.controller);
पूर्ण

अटल व्योम s3c2410_start_hc(काष्ठा platक्रमm_device *dev, काष्ठा usb_hcd *hcd)
अणु
	काष्ठा s3c2410_hcd_info *info = dev_get_platdata(&dev->dev);

	dev_dbg(&dev->dev, "s3c2410_start_hc:\n");

	clk_prepare_enable(usb_clk);
	mdelay(2);			/* let the bus घड़ी stabilise */

	clk_prepare_enable(clk);

	अगर (info != शून्य) अणु
		info->hcd	= hcd;
		info->report_oc = s3c2410_hcd_oc;

		अगर (info->enable_oc != शून्य)
			(info->enable_oc)(info, 1);
	पूर्ण
पूर्ण

अटल व्योम s3c2410_stop_hc(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c2410_hcd_info *info = dev_get_platdata(&dev->dev);

	dev_dbg(&dev->dev, "s3c2410_stop_hc:\n");

	अगर (info != शून्य) अणु
		info->report_oc = शून्य;
		info->hcd	= शून्य;

		अगर (info->enable_oc != शून्य)
			(info->enable_oc)(info, 0);
	पूर्ण

	clk_disable_unprepare(clk);
	clk_disable_unprepare(usb_clk);
पूर्ण

/* ohci_s3c2410_hub_status_data
 *
 * update the status data from the hub with anything that
 * has been detected by our प्रणाली
*/

अटल पूर्णांक
ohci_s3c2410_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा s3c2410_hcd_info *info = to_s3c2410_info(hcd);
	काष्ठा s3c2410_hcd_port *port;
	पूर्णांक orig;
	पूर्णांक portno;

	orig = ohci_hub_status_data(hcd, buf);

	अगर (info == शून्य)
		वापस orig;

	port = &info->port[0];

	/* mark any changed port as changed */

	क्रम (portno = 0; portno < 2; port++, portno++) अणु
		अगर (port->oc_changed == 1 &&
		    port->flags & S3C_HCDFLG_USED) अणु
			dev_dbg(hcd->self.controller,
				"oc change on port %d\n", portno);

			अगर (orig < 1)
				orig = 1;

			buf[0] |= 1<<(portno+1);
		पूर्ण
	पूर्ण

	वापस orig;
पूर्ण

/* s3c2410_usb_set_घातer
 *
 * configure the घातer on a port, by calling the platक्रमm device
 * routine रेजिस्टरed with the platक्रमm device
*/

अटल व्योम s3c2410_usb_set_घातer(काष्ठा s3c2410_hcd_info *info,
				  पूर्णांक port, पूर्णांक to)
अणु
	अगर (info == शून्य)
		वापस;

	अगर (info->घातer_control != शून्य) अणु
		info->port[port-1].घातer = to;
		(info->घातer_control)(port-1, to);
	पूर्ण
पूर्ण

/* ohci_s3c2410_hub_control
 *
 * look at control requests to the hub, and see अगर we need
 * to take any action or over-ride the results from the
 * request.
*/

अटल पूर्णांक ohci_s3c2410_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength)
अणु
	काष्ठा s3c2410_hcd_info *info = to_s3c2410_info(hcd);
	काष्ठा usb_hub_descriptor *desc;
	पूर्णांक ret = -EINVAL;
	u32 *data = (u32 *)buf;

	dev_dbg(hcd->self.controller,
		"s3c2410_hub_control(%p,0x%04x,0x%04x,0x%04x,%p,%04x)\n",
		hcd, typeReq, wValue, wIndex, buf, wLength);

	/* अगर we are only an humble host without any special capabilities
	 * process the request straight away and निकास */

	अगर (info == शून्य) अणु
		ret = ohci_hub_control(hcd, typeReq, wValue,
				       wIndex, buf, wLength);
		जाओ out;
	पूर्ण

	/* check the request to see अगर it needs handling */

	चयन (typeReq) अणु
	हाल SetPortFeature:
		अगर (wValue == USB_PORT_FEAT_POWER) अणु
			dev_dbg(hcd->self.controller, "SetPortFeat: POWER\n");
			s3c2410_usb_set_घातer(info, wIndex, 1);
			जाओ out;
		पूर्ण
		अवरोध;

	हाल ClearPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: C_OVER_CURRENT\n");

			अगर (valid_port(wIndex)) अणु
				info->port[wIndex-1].oc_changed = 0;
				info->port[wIndex-1].oc_status = 0;
			पूर्ण

			जाओ out;

		हाल USB_PORT_FEAT_OVER_CURRENT:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: OVER_CURRENT\n");

			अगर (valid_port(wIndex))
				info->port[wIndex-1].oc_status = 0;

			जाओ out;

		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hcd->self.controller,
				"ClearPortFeature: POWER\n");

			अगर (valid_port(wIndex)) अणु
				s3c2410_usb_set_घातer(info, wIndex, 0);
				वापस 0;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	ret = ohci_hub_control(hcd, typeReq, wValue, wIndex, buf, wLength);
	अगर (ret)
		जाओ out;

	चयन (typeReq) अणु
	हाल GetHubDescriptor:

		/* update the hub's descriptor */

		desc = (काष्ठा usb_hub_descriptor *)buf;

		अगर (info->घातer_control == शून्य)
			वापस ret;

		dev_dbg(hcd->self.controller, "wHubCharacteristics 0x%04x\n",
			desc->wHubCharacteristics);

		/* हटाओ the old configurations क्रम घातer-चयनing, and
		 * over-current protection, and insert our new configuration
		 */

		desc->wHubCharacteristics &= ~cpu_to_le16(HUB_CHAR_LPSM);
		desc->wHubCharacteristics |= cpu_to_le16(
			HUB_CHAR_INDV_PORT_LPSM);

		अगर (info->enable_oc) अणु
			desc->wHubCharacteristics &= ~cpu_to_le16(
				HUB_CHAR_OCPM);
			desc->wHubCharacteristics |=  cpu_to_le16(
				HUB_CHAR_INDV_PORT_OCPM);
		पूर्ण

		dev_dbg(hcd->self.controller, "wHubCharacteristics after 0x%04x\n",
			desc->wHubCharacteristics);

		वापस ret;

	हाल GetPortStatus:
		/* check port status */

		dev_dbg(hcd->self.controller, "GetPortStatus(%d)\n", wIndex);

		अगर (valid_port(wIndex)) अणु
			अगर (info->port[wIndex-1].oc_changed)
				*data |= cpu_to_le32(RH_PS_OCIC);

			अगर (info->port[wIndex-1].oc_status)
				*data |= cpu_to_le32(RH_PS_POCI);
		पूर्ण
	पूर्ण

 out:
	वापस ret;
पूर्ण

/* s3c2410_hcd_oc
 *
 * handle an over-current report
*/

अटल व्योम s3c2410_hcd_oc(काष्ठा s3c2410_hcd_info *info, पूर्णांक port_oc)
अणु
	काष्ठा s3c2410_hcd_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक portno;

	अगर (info == शून्य)
		वापस;

	port = &info->port[0];

	local_irq_save(flags);

	क्रम (portno = 0; portno < 2; port++, portno++) अणु
		अगर (port_oc & (1<<portno) &&
		    port->flags & S3C_HCDFLG_USED) अणु
			port->oc_status = 1;
			port->oc_changed = 1;

			/* ok, once over-current is detected,
			   the port needs to be घातered करोwn */
			s3c2410_usb_set_घातer(info, portno+1, 0);
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/* may be called without controller electrically present */
/* may be called with controller, bus, and devices active */

/*
 * ohci_hcd_s3c2410_हटाओ - shutकरोwn processing क्रम HCD
 * @dev: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of ohci_hcd_3c2410_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 */
अटल पूर्णांक
ohci_hcd_s3c2410_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);

	usb_हटाओ_hcd(hcd);
	s3c2410_stop_hc(dev);
	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

/*
 * ohci_hcd_s3c2410_probe - initialize S3C2410-based HCDs
 * @dev: USB Host Controller to be probed
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक ohci_hcd_s3c2410_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = शून्य;
	काष्ठा s3c2410_hcd_info *info = dev_get_platdata(&dev->dev);
	पूर्णांक retval;

	s3c2410_usb_set_घातer(info, 1, 1);
	s3c2410_usb_set_घातer(info, 2, 1);

	hcd = usb_create_hcd(&ohci_s3c2410_hc_driver, &dev->dev, "s3c24xx");
	अगर (hcd == शून्य)
		वापस -ENOMEM;

	hcd->rsrc_start = dev->resource[0].start;
	hcd->rsrc_len	= resource_size(&dev->resource[0]);

	hcd->regs = devm_ioremap_resource(&dev->dev, &dev->resource[0]);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ err_put;
	पूर्ण

	clk = devm_clk_get(&dev->dev, "usb-host");
	अगर (IS_ERR(clk)) अणु
		dev_err(&dev->dev, "cannot get usb-host clock\n");
		retval = PTR_ERR(clk);
		जाओ err_put;
	पूर्ण

	usb_clk = devm_clk_get(&dev->dev, "usb-bus-host");
	अगर (IS_ERR(usb_clk)) अणु
		dev_err(&dev->dev, "cannot get usb-bus-host clock\n");
		retval = PTR_ERR(usb_clk);
		जाओ err_put;
	पूर्ण

	s3c2410_start_hc(dev, hcd);

	retval = usb_add_hcd(hcd, dev->resource[1].start, 0);
	अगर (retval != 0)
		जाओ err_ioremap;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;

 err_ioremap:
	s3c2410_stop_hc(dev);

 err_put:
	usb_put_hcd(hcd);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ohci_hcd_s3c2410_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक rc = 0;

	rc = ohci_suspend(hcd, करो_wakeup);
	अगर (rc)
		वापस rc;

	s3c2410_stop_hc(pdev);

	वापस rc;
पूर्ण

अटल पूर्णांक ohci_hcd_s3c2410_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	s3c2410_start_hc(pdev, hcd);

	ohci_resume(hcd, false);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ohci_hcd_s3c2410_drv_suspend	शून्य
#घोषणा ohci_hcd_s3c2410_drv_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ohci_hcd_s3c2410_pm_ops = अणु
	.suspend	= ohci_hcd_s3c2410_drv_suspend,
	.resume		= ohci_hcd_s3c2410_drv_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ohci_hcd_s3c2410_dt_ids[] = अणु
	अणु .compatible = "samsung,s3c2410-ohci" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ohci_hcd_s3c2410_dt_ids);

अटल काष्ठा platक्रमm_driver ohci_hcd_s3c2410_driver = अणु
	.probe		= ohci_hcd_s3c2410_probe,
	.हटाओ		= ohci_hcd_s3c2410_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "s3c2410-ohci",
		.pm	= &ohci_hcd_s3c2410_pm_ops,
		.of_match_table	= ohci_hcd_s3c2410_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ohci_s3c2410_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	ohci_init_driver(&ohci_s3c2410_hc_driver, शून्य);

	/*
	 * The Samsung HW has some unusual quirks, which require
	 * Sumsung-specअगरic workarounds. We override certain hc_driver
	 * functions here to achieve that. We explicitly करो not enhance
	 * ohci_driver_overrides to allow this more easily, since this
	 * is an unusual हाल, and we करोn't want to encourage others to
	 * override these functions by making it too easy.
	 */

	ohci_s3c2410_hc_driver.hub_status_data	= ohci_s3c2410_hub_status_data;
	ohci_s3c2410_hc_driver.hub_control	= ohci_s3c2410_hub_control;

	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_s3c2410_driver);
पूर्ण
module_init(ohci_s3c2410_init);

अटल व्योम __निकास ohci_s3c2410_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_s3c2410_driver);
पूर्ण
module_निकास(ohci_s3c2410_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c2410-ohci");
