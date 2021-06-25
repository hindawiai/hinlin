<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS and USBSSP DRD Driver.
 *
 * Copyright (C) 2018-2020 Cadence.
 * Copyright (C) 2019 Texas Instruments
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *         Roger Quadros <rogerq@ti.com>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/usb/otg.h>

#समावेश "drd.h"
#समावेश "core.h"

/**
 * cdns_set_mode - change mode of OTG Core
 * @cdns: poपूर्णांकer to context काष्ठाure
 * @mode: selected mode from cdns_role
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
अटल पूर्णांक cdns_set_mode(काष्ठा cdns *cdns, क्रमागत usb_dr_mode mode)
अणु
	व्योम __iomem  *override_reg;
	u32 reg;

	चयन (mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		अवरोध;
	हाल USB_DR_MODE_HOST:
		अवरोध;
	हाल USB_DR_MODE_OTG:
		dev_dbg(cdns->dev, "Set controller to OTG mode\n");

		अगर (cdns->version == CDNSP_CONTROLLER_V2)
			override_reg = &cdns->otg_cdnsp_regs->override;
		अन्यथा अगर (cdns->version == CDNS3_CONTROLLER_V1)
			override_reg = &cdns->otg_v1_regs->override;
		अन्यथा
			override_reg = &cdns->otg_v0_regs->ctrl1;

		reg = पढ़ोl(override_reg);

		अगर (cdns->version != CDNS3_CONTROLLER_V0)
			reg |= OVERRIDE_IDPULLUP;
		अन्यथा
			reg |= OVERRIDE_IDPULLUP_V0;

		ग_लिखोl(reg, override_reg);

		अगर (cdns->version == CDNS3_CONTROLLER_V1) अणु
			/*
			 * Enable work around feature built पूर्णांकo the
			 * controller to address issue with RX Sensitivity
			 * est (EL_17) क्रम USB2 PHY. The issue only occures
			 * क्रम 0x0002450D controller version.
			 */
			अगर (cdns->phyrst_a_enable) अणु
				reg = पढ़ोl(&cdns->otg_v1_regs->phyrst_cfg);
				reg |= PHYRST_CFG_PHYRST_A_ENABLE;
				ग_लिखोl(reg, &cdns->otg_v1_regs->phyrst_cfg);
			पूर्ण
		पूर्ण

		/*
		 * Hardware specअगरication says: "ID_VALUE must be valid within
		 * 50ms after idpullup is set to '1" so driver must रुको
		 * 50ms beक्रमe पढ़ोing this pin.
		 */
		usleep_range(50000, 60000);
		अवरोध;
	शेष:
		dev_err(cdns->dev, "Unsupported mode of operation %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cdns_get_id(काष्ठा cdns *cdns)
अणु
	पूर्णांक id;

	id = पढ़ोl(&cdns->otg_regs->sts) & OTGSTS_ID_VALUE;
	dev_dbg(cdns->dev, "OTG ID: %d", id);

	वापस id;
पूर्ण

पूर्णांक cdns_get_vbus(काष्ठा cdns *cdns)
अणु
	पूर्णांक vbus;

	vbus = !!(पढ़ोl(&cdns->otg_regs->sts) & OTGSTS_VBUS_VALID);
	dev_dbg(cdns->dev, "OTG VBUS: %d", vbus);

	वापस vbus;
पूर्ण

व्योम cdns_clear_vbus(काष्ठा cdns *cdns)
अणु
	u32 reg;

	अगर (cdns->version != CDNSP_CONTROLLER_V2)
		वापस;

	reg = पढ़ोl(&cdns->otg_cdnsp_regs->override);
	reg |= OVERRIDE_SESS_VLD_SEL;
	ग_लिखोl(reg, &cdns->otg_cdnsp_regs->override);
पूर्ण
EXPORT_SYMBOL_GPL(cdns_clear_vbus);

व्योम cdns_set_vbus(काष्ठा cdns *cdns)
अणु
	u32 reg;

	अगर (cdns->version != CDNSP_CONTROLLER_V2)
		वापस;

	reg = पढ़ोl(&cdns->otg_cdnsp_regs->override);
	reg &= ~OVERRIDE_SESS_VLD_SEL;
	ग_लिखोl(reg, &cdns->otg_cdnsp_regs->override);
पूर्ण
EXPORT_SYMBOL_GPL(cdns_set_vbus);

bool cdns_is_host(काष्ठा cdns *cdns)
अणु
	अगर (cdns->dr_mode == USB_DR_MODE_HOST)
		वापस true;
	अन्यथा अगर (cdns_get_id(cdns) == CDNS3_ID_HOST)
		वापस true;

	वापस false;
पूर्ण

bool cdns_is_device(काष्ठा cdns *cdns)
अणु
	अगर (cdns->dr_mode == USB_DR_MODE_PERIPHERAL)
		वापस true;
	अन्यथा अगर (cdns->dr_mode == USB_DR_MODE_OTG)
		अगर (cdns_get_id(cdns) == CDNS3_ID_PERIPHERAL)
			वापस true;

	वापस false;
पूर्ण

/**
 * cdns_otg_disable_irq - Disable all OTG पूर्णांकerrupts
 * @cdns: Poपूर्णांकer to controller context काष्ठाure
 */
अटल व्योम cdns_otg_disable_irq(काष्ठा cdns *cdns)
अणु
	ग_लिखोl(0, &cdns->otg_irq_regs->ien);
पूर्ण

/**
 * cdns_otg_enable_irq - enable id and sess_valid पूर्णांकerrupts
 * @cdns: Poपूर्णांकer to controller context काष्ठाure
 */
अटल व्योम cdns_otg_enable_irq(काष्ठा cdns *cdns)
अणु
	ग_लिखोl(OTGIEN_ID_CHANGE_INT | OTGIEN_VBUSVALID_RISE_INT |
	       OTGIEN_VBUSVALID_FALL_INT, &cdns->otg_irq_regs->ien);
पूर्ण

/**
 * cdns_drd_host_on - start host.
 * @cdns: Poपूर्णांकer to controller context काष्ठाure.
 *
 * Returns 0 on success otherwise negative त्रुटि_सं.
 */
पूर्णांक cdns_drd_host_on(काष्ठा cdns *cdns)
अणु
	u32 val, पढ़ोy_bit;
	पूर्णांक ret;

	/* Enable host mode. */
	ग_लिखोl(OTGCMD_HOST_BUS_REQ | OTGCMD_OTG_DIS,
	       &cdns->otg_regs->cmd);

	अगर (cdns->version == CDNSP_CONTROLLER_V2)
		पढ़ोy_bit = OTGSTS_CDNSP_XHCI_READY;
	अन्यथा
		पढ़ोy_bit = OTGSTS_CDNS3_XHCI_READY;

	dev_dbg(cdns->dev, "Waiting till Host mode is turned on\n");
	ret = पढ़ोl_poll_समयout_atomic(&cdns->otg_regs->sts, val,
					val & पढ़ोy_bit, 1, 100000);

	अगर (ret)
		dev_err(cdns->dev, "timeout waiting for xhci_ready\n");

	phy_set_mode(cdns->usb3_phy, PHY_MODE_USB_HOST);
	वापस ret;
पूर्ण

/**
 * cdns_drd_host_off - stop host.
 * @cdns: Poपूर्णांकer to controller context काष्ठाure.
 */
व्योम cdns_drd_host_off(काष्ठा cdns *cdns)
अणु
	u32 val;

	ग_लिखोl(OTGCMD_HOST_BUS_DROP | OTGCMD_DEV_BUS_DROP |
	       OTGCMD_DEV_POWER_OFF | OTGCMD_HOST_POWER_OFF,
	       &cdns->otg_regs->cmd);

	/* Waiting till H_IDLE state.*/
	पढ़ोl_poll_समयout_atomic(&cdns->otg_regs->state, val,
				  !(val & OTGSTATE_HOST_STATE_MASK),
				  1, 2000000);
	phy_set_mode(cdns->usb3_phy, PHY_MODE_INVALID);
पूर्ण

/**
 * cdns_drd_gadget_on - start gadget.
 * @cdns: Poपूर्णांकer to controller context काष्ठाure.
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
पूर्णांक cdns_drd_gadget_on(काष्ठा cdns *cdns)
अणु
	u32 reg = OTGCMD_OTG_DIS;
	u32 पढ़ोy_bit;
	पूर्णांक ret, val;

	/* चयन OTG core */
	ग_लिखोl(OTGCMD_DEV_BUS_REQ | reg, &cdns->otg_regs->cmd);

	dev_dbg(cdns->dev, "Waiting till Device mode is turned on\n");

	अगर (cdns->version == CDNSP_CONTROLLER_V2)
		पढ़ोy_bit = OTGSTS_CDNSP_DEV_READY;
	अन्यथा
		पढ़ोy_bit = OTGSTS_CDNS3_DEV_READY;

	ret = पढ़ोl_poll_समयout_atomic(&cdns->otg_regs->sts, val,
					val & पढ़ोy_bit, 1, 100000);
	अगर (ret) अणु
		dev_err(cdns->dev, "timeout waiting for dev_ready\n");
		वापस ret;
	पूर्ण

	phy_set_mode(cdns->usb3_phy, PHY_MODE_USB_DEVICE);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_drd_gadget_on);

/**
 * cdns_drd_gadget_off - stop gadget.
 * @cdns: Poपूर्णांकer to controller context काष्ठाure.
 */
व्योम cdns_drd_gadget_off(काष्ठा cdns *cdns)
अणु
	u32 val;

	/*
	 * Driver should रुको at least 10us after disabling Device
	 * beक्रमe turning-off Device (DEV_BUS_DROP).
	 */
	usleep_range(20, 30);
	ग_लिखोl(OTGCMD_HOST_BUS_DROP | OTGCMD_DEV_BUS_DROP |
	       OTGCMD_DEV_POWER_OFF | OTGCMD_HOST_POWER_OFF,
	       &cdns->otg_regs->cmd);
	/* Waiting till DEV_IDLE state.*/
	पढ़ोl_poll_समयout_atomic(&cdns->otg_regs->state, val,
				  !(val & OTGSTATE_DEV_STATE_MASK),
				  1, 2000000);
	phy_set_mode(cdns->usb3_phy, PHY_MODE_INVALID);
पूर्ण
EXPORT_SYMBOL_GPL(cdns_drd_gadget_off);

/**
 * cdns_init_otg_mode - initialize drd controller
 * @cdns: Poपूर्णांकer to controller context काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
अटल पूर्णांक cdns_init_otg_mode(काष्ठा cdns *cdns)
अणु
	पूर्णांक ret;

	cdns_otg_disable_irq(cdns);
	/* clear all पूर्णांकerrupts */
	ग_लिखोl(~0, &cdns->otg_irq_regs->ivect);

	ret = cdns_set_mode(cdns, USB_DR_MODE_OTG);
	अगर (ret)
		वापस ret;

	cdns_otg_enable_irq(cdns);

	वापस 0;
पूर्ण

/**
 * cdns_drd_update_mode - initialize mode of operation
 * @cdns: Poपूर्णांकer to controller context काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
पूर्णांक cdns_drd_update_mode(काष्ठा cdns *cdns)
अणु
	पूर्णांक ret;

	चयन (cdns->dr_mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		ret = cdns_set_mode(cdns, USB_DR_MODE_PERIPHERAL);
		अवरोध;
	हाल USB_DR_MODE_HOST:
		ret = cdns_set_mode(cdns, USB_DR_MODE_HOST);
		अवरोध;
	हाल USB_DR_MODE_OTG:
		ret = cdns_init_otg_mode(cdns);
		अवरोध;
	शेष:
		dev_err(cdns->dev, "Unsupported mode of operation %d\n",
			cdns->dr_mode);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t cdns_drd_thपढ़ो_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns *cdns = data;

	cdns_hw_role_चयन(cdns);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * cdns_drd_irq - पूर्णांकerrupt handler क्रम OTG events
 *
 * @irq: irq number क्रम cdns core device
 * @data: काष्ठाure of cdns
 *
 * Returns IRQ_HANDLED or IRQ_NONE
 */
अटल irqवापस_t cdns_drd_irq(पूर्णांक irq, व्योम *data)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा cdns *cdns = data;
	u32 reg;

	अगर (cdns->dr_mode != USB_DR_MODE_OTG)
		वापस IRQ_NONE;

	अगर (cdns->in_lpm)
		वापस ret;

	reg = पढ़ोl(&cdns->otg_irq_regs->ivect);

	अगर (!reg)
		वापस IRQ_NONE;

	अगर (reg & OTGIEN_ID_CHANGE_INT) अणु
		dev_dbg(cdns->dev, "OTG IRQ: new ID: %d\n",
			cdns_get_id(cdns));

		ret = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (reg & (OTGIEN_VBUSVALID_RISE_INT | OTGIEN_VBUSVALID_FALL_INT)) अणु
		dev_dbg(cdns->dev, "OTG IRQ: new VBUS: %d\n",
			cdns_get_vbus(cdns));

		ret = IRQ_WAKE_THREAD;
	पूर्ण

	ग_लिखोl(~0, &cdns->otg_irq_regs->ivect);
	वापस ret;
पूर्ण

पूर्णांक cdns_drd_init(काष्ठा cdns *cdns)
अणु
	व्योम __iomem *regs;
	u32 state;
	पूर्णांक ret;

	regs = devm_ioremap_resource(cdns->dev, &cdns->otg_res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	/* Detection of DRD version. Controller has been released
	 * in three versions. All are very similar and are software compatible,
	 * but they have same changes in रेजिस्टर maps.
	 * The first रेजिस्टर in oldest version is command रेजिस्टर and it's
	 * पढ़ो only. Driver should पढ़ो 0 from it. On the other hand, in v1
	 * and v2 the first रेजिस्टर contains device ID number which is not
	 * set to 0. Driver uses this fact to detect the proper version of
	 * controller.
	 */
	cdns->otg_v0_regs = regs;
	अगर (!पढ़ोl(&cdns->otg_v0_regs->cmd)) अणु
		cdns->version  = CDNS3_CONTROLLER_V0;
		cdns->otg_v1_regs = शून्य;
		cdns->otg_cdnsp_regs = शून्य;
		cdns->otg_regs = regs;
		cdns->otg_irq_regs = (काष्ठा cdns_otg_irq_regs __iomem  *)
				     &cdns->otg_v0_regs->ien;
		ग_लिखोl(1, &cdns->otg_v0_regs->simulate);
		dev_dbg(cdns->dev, "DRD version v0 (%08x)\n",
			 पढ़ोl(&cdns->otg_v0_regs->version));
	पूर्ण अन्यथा अणु
		cdns->otg_v0_regs = शून्य;
		cdns->otg_v1_regs = regs;
		cdns->otg_cdnsp_regs = regs;

		cdns->otg_regs = (व्योम __iomem *)&cdns->otg_v1_regs->cmd;

		अगर (पढ़ोl(&cdns->otg_cdnsp_regs->did) == OTG_CDNSP_DID) अणु
			cdns->otg_irq_regs = (काष्ठा cdns_otg_irq_regs __iomem *)
					      &cdns->otg_cdnsp_regs->ien;
			cdns->version  = CDNSP_CONTROLLER_V2;
		पूर्ण अन्यथा अणु
			cdns->otg_irq_regs = (काष्ठा cdns_otg_irq_regs __iomem *)
					      &cdns->otg_v1_regs->ien;
			ग_लिखोl(1, &cdns->otg_v1_regs->simulate);
			cdns->version  = CDNS3_CONTROLLER_V1;
		पूर्ण

		dev_dbg(cdns->dev, "DRD version v1 (ID: %08x, rev: %08x)\n",
			 पढ़ोl(&cdns->otg_v1_regs->did),
			 पढ़ोl(&cdns->otg_v1_regs->rid));
	पूर्ण

	state = OTGSTS_STRAP(पढ़ोl(&cdns->otg_regs->sts));

	/* Update dr_mode according to STRAP configuration. */
	cdns->dr_mode = USB_DR_MODE_OTG;

	अगर ((cdns->version == CDNSP_CONTROLLER_V2 &&
	     state == OTGSTS_CDNSP_STRAP_HOST) ||
	    (cdns->version != CDNSP_CONTROLLER_V2 &&
	     state == OTGSTS_STRAP_HOST)) अणु
		dev_dbg(cdns->dev, "Controller strapped to HOST\n");
		cdns->dr_mode = USB_DR_MODE_HOST;
	पूर्ण अन्यथा अगर ((cdns->version == CDNSP_CONTROLLER_V2 &&
		    state == OTGSTS_CDNSP_STRAP_GADGET) ||
		   (cdns->version != CDNSP_CONTROLLER_V2 &&
		    state == OTGSTS_STRAP_GADGET)) अणु
		dev_dbg(cdns->dev, "Controller strapped to PERIPHERAL\n");
		cdns->dr_mode = USB_DR_MODE_PERIPHERAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(cdns->dev, cdns->otg_irq,
					cdns_drd_irq,
					cdns_drd_thपढ़ो_irq,
					IRQF_SHARED,
					dev_name(cdns->dev), cdns);
	अगर (ret) अणु
		dev_err(cdns->dev, "couldn't get otg_irq\n");
		वापस ret;
	पूर्ण

	state = पढ़ोl(&cdns->otg_regs->sts);
	अगर (OTGSTS_OTG_NRDY(state)) अणु
		dev_err(cdns->dev, "Cadence USB3 OTG device not ready\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cdns_drd_निकास(काष्ठा cdns *cdns)
अणु
	cdns_otg_disable_irq(cdns);

	वापस 0;
पूर्ण


/* Indicate the cdns3 core was घातer lost beक्रमe */
bool cdns_घातer_is_lost(काष्ठा cdns *cdns)
अणु
	अगर (cdns->version == CDNS3_CONTROLLER_V1) अणु
		अगर (!(पढ़ोl(&cdns->otg_v1_regs->simulate) & BIT(0)))
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (!(पढ़ोl(&cdns->otg_v0_regs->simulate) & BIT(0)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_घातer_is_lost);
