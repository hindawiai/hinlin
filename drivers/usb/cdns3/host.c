<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS and USBSSP DRD Driver - host side
 *
 * Copyright (C) 2018-2019 Cadence Design Systems.
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 *          Pawel Laszczak <pawell@cadence.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश "core.h"
#समावेश "drd.h"
#समावेश "host-export.h"
#समावेश <linux/usb/hcd.h>
#समावेश "../host/xhci.h"
#समावेश "../host/xhci-plat.h"

#घोषणा XECP_PORT_CAP_REG	0x8000
#घोषणा XECP_AUX_CTRL_REG1	0x8120

#घोषणा CFG_RXDET_P3_EN		BIT(15)
#घोषणा LPM_2_STB_SWITCH_EN	BIT(25)

अटल पूर्णांक xhci_cdns3_suspend_quirk(काष्ठा usb_hcd *hcd);

अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_cdns3_xhci = अणु
	.quirks = XHCI_SKIP_PHY_INIT | XHCI_AVOID_BEI,
	.suspend_quirk = xhci_cdns3_suspend_quirk,
पूर्ण;

अटल पूर्णांक __cdns_host_init(काष्ठा cdns *cdns)
अणु
	काष्ठा platक्रमm_device *xhci;
	पूर्णांक ret;
	काष्ठा usb_hcd *hcd;

	cdns_drd_host_on(cdns);

	xhci = platक्रमm_device_alloc("xhci-hcd", PLATFORM_DEVID_AUTO);
	अगर (!xhci) अणु
		dev_err(cdns->dev, "couldn't allocate xHCI device\n");
		वापस -ENOMEM;
	पूर्ण

	xhci->dev.parent = cdns->dev;
	cdns->host_dev = xhci;

	ret = platक्रमm_device_add_resources(xhci, cdns->xhci_res,
					    CDNS_XHCI_RESOURCES_NUM);
	अगर (ret) अणु
		dev_err(cdns->dev, "couldn't add resources to xHCI device\n");
		जाओ err1;
	पूर्ण

	cdns->xhci_plat_data = kmemdup(&xhci_plat_cdns3_xhci,
			माप(काष्ठा xhci_plat_priv), GFP_KERNEL);
	अगर (!cdns->xhci_plat_data) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (cdns->pdata && (cdns->pdata->quirks & CDNS3_DEFAULT_PM_RUNTIME_ALLOW))
		cdns->xhci_plat_data->quirks |= XHCI_DEFAULT_PM_RUNTIME_ALLOW;

	ret = platक्रमm_device_add_data(xhci, cdns->xhci_plat_data,
			माप(काष्ठा xhci_plat_priv));
	अगर (ret)
		जाओ मुक्त_memory;

	ret = platक्रमm_device_add(xhci);
	अगर (ret) अणु
		dev_err(cdns->dev, "failed to register xHCI device\n");
		जाओ मुक्त_memory;
	पूर्ण

	/* Glue needs to access xHCI region रेजिस्टर क्रम Power management */
	hcd = platक्रमm_get_drvdata(xhci);
	अगर (hcd)
		cdns->xhci_regs = hcd->regs;

	वापस 0;

मुक्त_memory:
	kमुक्त(cdns->xhci_plat_data);
err1:
	platक्रमm_device_put(xhci);
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_cdns3_suspend_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	u32 value;

	अगर (pm_runसमय_status_suspended(hcd->self.controller))
		वापस 0;

	/* set usbcmd.EU3S */
	value = पढ़ोl(&xhci->op_regs->command);
	value |= CMD_PM_INDEX;
	ग_लिखोl(value, &xhci->op_regs->command);

	अगर (hcd->regs) अणु
		value = पढ़ोl(hcd->regs + XECP_AUX_CTRL_REG1);
		value |= CFG_RXDET_P3_EN;
		ग_लिखोl(value, hcd->regs + XECP_AUX_CTRL_REG1);

		value = पढ़ोl(hcd->regs + XECP_PORT_CAP_REG);
		value |= LPM_2_STB_SWITCH_EN;
		ग_लिखोl(value, hcd->regs + XECP_PORT_CAP_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns_host_निकास(काष्ठा cdns *cdns)
अणु
	kमुक्त(cdns->xhci_plat_data);
	platक्रमm_device_unरेजिस्टर(cdns->host_dev);
	cdns->host_dev = शून्य;
	cdns_drd_host_off(cdns);
पूर्ण

पूर्णांक cdns_host_init(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, माप(*rdrv), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start	= __cdns_host_init;
	rdrv->stop	= cdns_host_निकास;
	rdrv->state	= CDNS_ROLE_STATE_INACTIVE;
	rdrv->name	= "host";

	cdns->roles[USB_ROLE_HOST] = rdrv;

	वापस 0;
पूर्ण
