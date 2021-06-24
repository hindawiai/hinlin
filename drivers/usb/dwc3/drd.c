<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drd.c - DesignWare USB3 DRD Controller Dual-role support
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Roger Quadros <rogerq@ti.com>
 */

#समावेश <linux/extcon.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#समावेश "debug.h"
#समावेश "core.h"
#समावेश "gadget.h"

अटल व्योम dwc3_otg_disable_events(काष्ठा dwc3 *dwc, u32 disable_mask)
अणु
	u32 reg = dwc3_पढ़ोl(dwc->regs, DWC3_OEVTEN);

	reg &= ~(disable_mask);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OEVTEN, reg);
पूर्ण

अटल व्योम dwc3_otg_enable_events(काष्ठा dwc3 *dwc, u32 enable_mask)
अणु
	u32 reg = dwc3_पढ़ोl(dwc->regs, DWC3_OEVTEN);

	reg |= (enable_mask);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OEVTEN, reg);
पूर्ण

अटल व्योम dwc3_otg_clear_events(काष्ठा dwc3 *dwc)
अणु
	u32 reg = dwc3_पढ़ोl(dwc->regs, DWC3_OEVT);

	dwc3_ग_लिखोl(dwc->regs, DWC3_OEVTEN, reg);
पूर्ण

#घोषणा DWC3_OTG_ALL_EVENTS	(DWC3_OEVTEN_XHCIRUNSTPSETEN | \
		DWC3_OEVTEN_DEVRUNSTPSETEN | DWC3_OEVTEN_HIBENTRYEN | \
		DWC3_OEVTEN_CONIDSTSCHNGEN | DWC3_OEVTEN_HRRCONFNOTIFEN | \
		DWC3_OEVTEN_HRRINITNOTIFEN | DWC3_OEVTEN_ADEVIDLEEN | \
		DWC3_OEVTEN_ADEVBHOSTENDEN | DWC3_OEVTEN_ADEVHOSTEN | \
		DWC3_OEVTEN_ADEVHNPCHNGEN | DWC3_OEVTEN_ADEVSRPDETEN | \
		DWC3_OEVTEN_ADEVSESSENDDETEN | DWC3_OEVTEN_BDEVBHOSTENDEN | \
		DWC3_OEVTEN_BDEVHNPCHNGEN | DWC3_OEVTEN_BDEVSESSVLDDETEN | \
		DWC3_OEVTEN_BDEVVBUSCHNGEN)

अटल irqवापस_t dwc3_otg_thपढ़ो_irq(पूर्णांक irq, व्योम *_dwc)
अणु
	काष्ठा dwc3 *dwc = _dwc;

	spin_lock(&dwc->lock);
	अगर (dwc->otg_restart_host) अणु
		dwc3_otg_host_init(dwc);
		dwc->otg_restart_host = false;
	पूर्ण

	spin_unlock(&dwc->lock);

	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_OTG);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dwc3_otg_irq(पूर्णांक irq, व्योम *_dwc)
अणु
	u32 reg;
	काष्ठा dwc3 *dwc = _dwc;
	irqवापस_t ret = IRQ_NONE;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OEVT);
	अगर (reg) अणु
		/* ignore non OTG events, we can't disable them in OEVTEN */
		अगर (!(reg & DWC3_OTG_ALL_EVENTS)) अणु
			dwc3_ग_लिखोl(dwc->regs, DWC3_OEVT, reg);
			वापस IRQ_NONE;
		पूर्ण

		अगर (dwc->current_otg_role == DWC3_OTG_ROLE_HOST &&
		    !(reg & DWC3_OEVT_DEVICEMODE))
			dwc->otg_restart_host = true;
		dwc3_ग_लिखोl(dwc->regs, DWC3_OEVT, reg);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dwc3_otgregs_init(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/*
	 * Prevent host/device reset from resetting OTG core.
	 * If we करोn't करो this then xhci_reset (USBCMD.HCRST) will reset
	 * the संकेत outमाला_दो sent to the PHY, the OTG FSM logic of the
	 * core and also the resets to the VBUS filters inside the core.
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCFG);
	reg |= DWC3_OCFG_SFTRSTMASK;
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCFG, reg);

	/* Disable hibernation क्रम simplicity */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
	reg &= ~DWC3_GCTL_GBLHIBERNATIONEN;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GCTL, reg);

	/*
	 * Initialize OTG रेजिस्टरs as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */
	/* OCFG.SRPCap = 0, OCFG.HNPCap = 0 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCFG);
	reg &= ~(DWC3_OCFG_SRPCAP | DWC3_OCFG_HNPCAP);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCFG, reg);
	/* OEVT = FFFF */
	dwc3_otg_clear_events(dwc);
	/* OEVTEN = 0 */
	dwc3_otg_disable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/* OEVTEN.ConIDStsChngEn = 1. Instead we enable all events */
	dwc3_otg_enable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/*
	 * OCTL.PeriMode = 1, OCTL.DevSetHNPEn = 0, OCTL.HstSetHNPEn = 0,
	 * OCTL.HNPReq = 0
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PERIMODE;
	reg &= ~(DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN |
		 DWC3_OCTL_HNPREQ);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);
पूर्ण

अटल पूर्णांक dwc3_otg_get_irq(काष्ठा dwc3 *dwc)
अणु
	काष्ठा platक्रमm_device *dwc3_pdev = to_platक्रमm_device(dwc->dev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "otg");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "dwc_usb3");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq(dwc3_pdev, 0);
	अगर (irq > 0)
		जाओ out;

	अगर (!irq)
		irq = -EINVAL;

out:
	वापस irq;
पूर्ण

व्योम dwc3_otg_init(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/*
	 * As per Figure 11-4 OTG Driver Overall Programming Flow,
	 * block "Initialize GCTL for OTG operation".
	 */
	/* GCTL.PrtCapDir=2'b11 */
	dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_OTG);
	/* GUSB2PHYCFG0.SusPHY=0 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
	reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

	/* Initialize OTG रेजिस्टरs */
	dwc3_otgregs_init(dwc);
पूर्ण

व्योम dwc3_otg_निकास(काष्ठा dwc3 *dwc)
अणु
	/* disable all OTG IRQs */
	dwc3_otg_disable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/* clear all events */
	dwc3_otg_clear_events(dwc);
पूर्ण

/* should be called beक्रमe Host controller driver is started */
व्योम dwc3_otg_host_init(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/* As per Figure 11-10 A-Device Flow Diagram */
	/* OCFG.HNPCap = 0, OCFG.SRPCap = 0. Alपढ़ोy 0 */

	/*
	 * OCTL.PeriMode=0, OCTL.TermSelDLPulse = 0,
	 * OCTL.DevSetHNPEn = 0, OCTL.HstSetHNPEn = 0
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_PERIMODE | DWC3_OCTL_TERMSELIDPULSE |
			DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);

	/*
	 * OCFG.DisPrtPwrCutoff = 0/1
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCFG);
	reg &= ~DWC3_OCFG_DISPWRCUTTOFF;
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCFG, reg);

	/*
	 * OCFG.SRPCap = 1, OCFG.HNPCap = GHWPARAMS6.HNP_CAP
	 * We करोn't want SRP/HNP क्रम simple dual-role so leave
	 * these disabled.
	 */

	/*
	 * OEVTEN.OTGADevHostEvntEn = 1
	 * OEVTEN.OTGADevSessEndDetEvntEn = 1
	 * We करोn't want HNP/role-swap so leave these disabled.
	 */

	/* GUSB2PHYCFG.ULPIAutoRes = 1/0, GUSB2PHYCFG.SusPHY = 1 */
	अगर (!dwc->dis_u2_susphy_quirk) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		reg |= DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	पूर्ण

	/* Set Port Power to enable VBUS: OCTL.PrtPwrCtl = 1 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PRTPWRCTL;
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);
पूर्ण

/* should be called after Host controller driver is stopped */
अटल व्योम dwc3_otg_host_निकास(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/*
	 * Exit from A-device flow as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */

	/*
	 * OEVTEN.OTGADevBHostEndEvntEn=0, OEVTEN.OTGADevHNPChngEvntEn=0
	 * OEVTEN.OTGADevSessEndDetEvntEn=0,
	 * OEVTEN.OTGADevHostEvntEn = 0
	 * But we करोn't disable any OTG events
	 */

	/* OCTL.HstSetHNPEn = 0, OCTL.PrtPwrCtl=0 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_HSTSETHNPEN | DWC3_OCTL_PRTPWRCTL);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);
पूर्ण

/* should be called beक्रमe the gadget controller driver is started */
अटल व्योम dwc3_otg_device_init(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/* As per Figure 11-20 B-Device Flow Diagram */

	/*
	 * OCFG.HNPCap = GHWPARAMS6.HNP_CAP, OCFG.SRPCap = 1
	 * but we keep them 0 क्रम simple dual-role operation.
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCFG);
	/* OCFG.OTGSftRstMsk = 0/1 */
	reg |= DWC3_OCFG_SFTRSTMASK;
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCFG, reg);
	/*
	 * OCTL.PeriMode = 1
	 * OCTL.TermSelDLPulse = 0/1, OCTL.HNPReq = 0
	 * OCTL.DevSetHNPEn = 0, OCTL.HstSetHNPEn = 0
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PERIMODE;
	reg &= ~(DWC3_OCTL_TERMSELIDPULSE | DWC3_OCTL_HNPREQ |
			DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN);
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);
	/* OEVTEN.OTGBDevSesVldDetEvntEn = 1 */
	dwc3_otg_enable_events(dwc, DWC3_OEVTEN_BDEVSESSVLDDETEN);
	/* GUSB2PHYCFG.ULPIAutoRes = 0, GUSB2PHYCFG0.SusPHY = 1 */
	अगर (!dwc->dis_u2_susphy_quirk) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		reg |= DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	पूर्ण
	/* GCTL.GblHibernationEn = 0. Alपढ़ोy 0. */
पूर्ण

/* should be called after the gadget controller driver is stopped */
अटल व्योम dwc3_otg_device_निकास(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	/*
	 * Exit from B-device flow as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */

	/*
	 * OEVTEN.OTGBDevHNPChngEvntEn = 0
	 * OEVTEN.OTGBDevVBusChngEvntEn = 0
	 * OEVTEN.OTGBDevBHostEndEvntEn = 0
	 */
	dwc3_otg_disable_events(dwc, DWC3_OEVTEN_BDEVHNPCHNGEN |
				DWC3_OEVTEN_BDEVVBUSCHNGEN |
				DWC3_OEVTEN_BDEVBHOSTENDEN);

	/* OCTL.DevSetHNPEn = 0, OCTL.HNPReq = 0, OCTL.PeriMode=1 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HNPREQ);
	reg |= DWC3_OCTL_PERIMODE;
	dwc3_ग_लिखोl(dwc->regs, DWC3_OCTL, reg);
पूर्ण

व्योम dwc3_otg_update(काष्ठा dwc3 *dwc, bool ignore_idstatus)
अणु
	पूर्णांक ret;
	u32 reg;
	पूर्णांक id;
	अचिन्हित दीर्घ flags;

	अगर (dwc->dr_mode != USB_DR_MODE_OTG)
		वापस;

	/* करोn't करो anything अगर debug user changed role to not OTG */
	अगर (dwc->current_dr_role != DWC3_GCTL_PRTCAP_OTG)
		वापस;

	अगर (!ignore_idstatus) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_OSTS);
		id = !!(reg & DWC3_OSTS_CONIDSTS);

		dwc->desired_otg_role = id ? DWC3_OTG_ROLE_DEVICE :
					DWC3_OTG_ROLE_HOST;
	पूर्ण

	अगर (dwc->desired_otg_role == dwc->current_otg_role)
		वापस;

	चयन (dwc->current_otg_role) अणु
	हाल DWC3_OTG_ROLE_HOST:
		dwc3_host_निकास(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_otg_host_निकास(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);
		अवरोध;
	हाल DWC3_OTG_ROLE_DEVICE:
		dwc3_gadget_निकास(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_event_buffers_cleanup(dwc);
		dwc3_otg_device_निकास(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dwc->lock, flags);

	dwc->current_otg_role = dwc->desired_otg_role;

	spin_unlock_irqrestore(&dwc->lock, flags);

	चयन (dwc->desired_otg_role) अणु
	हाल DWC3_OTG_ROLE_HOST:
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_otgregs_init(dwc);
		dwc3_otg_host_init(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);
		ret = dwc3_host_init(dwc);
		अगर (ret) अणु
			dev_err(dwc->dev, "failed to initialize host\n");
		पूर्ण अन्यथा अणु
			अगर (dwc->usb2_phy)
				otg_set_vbus(dwc->usb2_phy->otg, true);
			अगर (dwc->usb2_generic_phy)
				phy_set_mode(dwc->usb2_generic_phy,
					     PHY_MODE_USB_HOST);
		पूर्ण
		अवरोध;
	हाल DWC3_OTG_ROLE_DEVICE:
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_otgregs_init(dwc);
		dwc3_otg_device_init(dwc);
		dwc3_event_buffers_setup(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);

		अगर (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, false);
		अगर (dwc->usb2_generic_phy)
			phy_set_mode(dwc->usb2_generic_phy,
				     PHY_MODE_USB_DEVICE);
		ret = dwc3_gadget_init(dwc);
		अगर (ret)
			dev_err(dwc->dev, "failed to initialize peripheral\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dwc3_drd_update(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक id;

	अगर (dwc->edev) अणु
		id = extcon_get_state(dwc->edev, EXTCON_USB_HOST);
		अगर (id < 0)
			id = 0;
		dwc3_set_mode(dwc, id ?
			      DWC3_GCTL_PRTCAP_HOST :
			      DWC3_GCTL_PRTCAP_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_drd_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dwc3 *dwc = container_of(nb, काष्ठा dwc3, edev_nb);

	dwc3_set_mode(dwc, event ?
		      DWC3_GCTL_PRTCAP_HOST :
		      DWC3_GCTL_PRTCAP_DEVICE);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा extcon_dev *dwc3_get_extcon(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device *dev = dwc->dev;
	काष्ठा device_node *np_phy;
	काष्ठा extcon_dev *edev = शून्य;
	स्थिर अक्षर *name;

	अगर (device_property_पढ़ो_bool(dev, "extcon"))
		वापस extcon_get_edev_by_phandle(dev, 0);

	/*
	 * Device tree platक्रमms should get extcon via phandle.
	 * On ACPI platक्रमms, we get the name from a device property.
	 * This device property is क्रम kernel पूर्णांकernal use only and
	 * is expected to be set by the glue code.
	 */
	अगर (device_property_पढ़ो_string(dev, "linux,extcon-name", &name) == 0) अणु
		edev = extcon_get_extcon_dev(name);
		अगर (!edev)
			वापस ERR_PTR(-EPROBE_DEFER);

		वापस edev;
	पूर्ण

	/*
	 * Try to get an extcon device from the USB PHY controller's "port"
	 * node. Check अगर it has the "port" node first, to aव्योम prपूर्णांकing the
	 * error message from underlying code, as it's a valid हाल: extcon
	 * device (and "port" node) may be missing in हाल of "usb-role-switch"
	 * or OTG mode.
	 */
	np_phy = of_parse_phandle(dev->of_node, "phys", 0);
	अगर (of_graph_is_present(np_phy)) अणु
		काष्ठा device_node *np_conn;

		np_conn = of_graph_get_remote_node(np_phy, -1, -1);
		अगर (np_conn)
			edev = extcon_find_edev_by_node(np_conn);
		of_node_put(np_conn);
	पूर्ण
	of_node_put(np_phy);

	वापस edev;
पूर्ण

#अगर IS_ENABLED(CONFIG_USB_ROLE_SWITCH)
#घोषणा ROLE_SWITCH 1
अटल पूर्णांक dwc3_usb_role_चयन_set(काष्ठा usb_role_चयन *sw,
				    क्रमागत usb_role role)
अणु
	काष्ठा dwc3 *dwc = usb_role_चयन_get_drvdata(sw);
	u32 mode;

	चयन (role) अणु
	हाल USB_ROLE_HOST:
		mode = DWC3_GCTL_PRTCAP_HOST;
		अवरोध;
	हाल USB_ROLE_DEVICE:
		mode = DWC3_GCTL_PRTCAP_DEVICE;
		अवरोध;
	शेष:
		अगर (dwc->role_चयन_शेष_mode == USB_DR_MODE_HOST)
			mode = DWC3_GCTL_PRTCAP_HOST;
		अन्यथा
			mode = DWC3_GCTL_PRTCAP_DEVICE;
		अवरोध;
	पूर्ण

	dwc3_set_mode(dwc, mode);
	वापस 0;
पूर्ण

अटल क्रमागत usb_role dwc3_usb_role_चयन_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा dwc3 *dwc = usb_role_चयन_get_drvdata(sw);
	अचिन्हित दीर्घ flags;
	क्रमागत usb_role role;

	spin_lock_irqsave(&dwc->lock, flags);
	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_HOST:
		role = USB_ROLE_HOST;
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		role = USB_ROLE_DEVICE;
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		role = dwc->current_otg_role;
		अवरोध;
	शेष:
		अगर (dwc->role_चयन_शेष_mode == USB_DR_MODE_HOST)
			role = USB_ROLE_HOST;
		अन्यथा
			role = USB_ROLE_DEVICE;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dwc->lock, flags);
	वापस role;
पूर्ण

अटल पूर्णांक dwc3_setup_role_चयन(काष्ठा dwc3 *dwc)
अणु
	काष्ठा usb_role_चयन_desc dwc3_role_चयन = अणुशून्यपूर्ण;
	स्थिर अक्षर *str;
	u32 mode;
	पूर्णांक ret;

	ret = device_property_पढ़ो_string(dwc->dev, "role-switch-default-mode",
					  &str);
	अगर (ret >= 0  && !म_भेदन(str, "host", म_माप("host"))) अणु
		dwc->role_चयन_शेष_mode = USB_DR_MODE_HOST;
		mode = DWC3_GCTL_PRTCAP_HOST;
	पूर्ण अन्यथा अणु
		dwc->role_चयन_शेष_mode = USB_DR_MODE_PERIPHERAL;
		mode = DWC3_GCTL_PRTCAP_DEVICE;
	पूर्ण

	dwc3_role_चयन.fwnode = dev_fwnode(dwc->dev);
	dwc3_role_चयन.set = dwc3_usb_role_चयन_set;
	dwc3_role_चयन.get = dwc3_usb_role_चयन_get;
	dwc3_role_चयन.driver_data = dwc;
	dwc->role_sw = usb_role_चयन_रेजिस्टर(dwc->dev, &dwc3_role_चयन);
	अगर (IS_ERR(dwc->role_sw))
		वापस PTR_ERR(dwc->role_sw);

	dwc3_set_mode(dwc, mode);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ROLE_SWITCH 0
#घोषणा dwc3_setup_role_चयन(x) 0
#पूर्ण_अगर

पूर्णांक dwc3_drd_init(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक ret, irq;

	dwc->edev = dwc3_get_extcon(dwc);
	अगर (IS_ERR(dwc->edev))
		वापस PTR_ERR(dwc->edev);

	अगर (ROLE_SWITCH &&
	    device_property_पढ़ो_bool(dwc->dev, "usb-role-switch")) अणु
		ret = dwc3_setup_role_चयन(dwc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (dwc->edev) अणु
		dwc->edev_nb.notअगरier_call = dwc3_drd_notअगरier;
		ret = extcon_रेजिस्टर_notअगरier(dwc->edev, EXTCON_USB_HOST,
					       &dwc->edev_nb);
		अगर (ret < 0) अणु
			dev_err(dwc->dev, "couldn't register cable notifier\n");
			वापस ret;
		पूर्ण

		dwc3_drd_update(dwc);
	पूर्ण अन्यथा अणु
		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_OTG);
		dwc->current_dr_role = DWC3_GCTL_PRTCAP_OTG;

		/* use OTG block to get ID event */
		irq = dwc3_otg_get_irq(dwc);
		अगर (irq < 0)
			वापस irq;

		dwc->otg_irq = irq;

		/* disable all OTG IRQs */
		dwc3_otg_disable_events(dwc, DWC3_OTG_ALL_EVENTS);
		/* clear all events */
		dwc3_otg_clear_events(dwc);

		ret = request_thपढ़ोed_irq(dwc->otg_irq, dwc3_otg_irq,
					   dwc3_otg_thपढ़ो_irq,
					   IRQF_SHARED, "dwc3-otg", dwc);
		अगर (ret) अणु
			dev_err(dwc->dev, "failed to request irq #%d --> %d\n",
				dwc->otg_irq, ret);
			ret = -ENODEV;
			वापस ret;
		पूर्ण

		dwc3_otg_init(dwc);
		dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_OTG);
	पूर्ण

	वापस 0;
पूर्ण

व्योम dwc3_drd_निकास(काष्ठा dwc3 *dwc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (dwc->role_sw)
		usb_role_चयन_unरेजिस्टर(dwc->role_sw);

	अगर (dwc->edev)
		extcon_unरेजिस्टर_notअगरier(dwc->edev, EXTCON_USB_HOST,
					   &dwc->edev_nb);

	cancel_work_sync(&dwc->drd_work);

	/* debug user might have changed role, clean based on current role */
	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_HOST:
		dwc3_host_निकास(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_gadget_निकास(dwc);
		dwc3_event_buffers_cleanup(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_निकास(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc->desired_otg_role = DWC3_OTG_ROLE_IDLE;
		spin_unlock_irqrestore(&dwc->lock, flags);
		dwc3_otg_update(dwc, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dwc->otg_irq)
		मुक्त_irq(dwc->otg_irq, dwc);
पूर्ण
