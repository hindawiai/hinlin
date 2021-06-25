<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS and USBSSP DRD Driver.
 *
 * Copyright (C) 2018-2019 Cadence.
 * Copyright (C) 2017-2018 NXP
 * Copyright (C) 2019 Texas Instruments
 *
 * Author: Peter Chen <peter.chen@nxp.com>
 *         Pawel Laszczak <pawell@cadence.com>
 *         Roger Quadros <rogerq@ti.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>

#समावेश "core.h"
#समावेश "host-export.h"
#समावेश "drd.h"

अटल पूर्णांक cdns_idle_init(काष्ठा cdns *cdns);

अटल पूर्णांक cdns_role_start(काष्ठा cdns *cdns, क्रमागत usb_role role)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(role > USB_ROLE_DEVICE))
		वापस 0;

	mutex_lock(&cdns->mutex);
	cdns->role = role;
	mutex_unlock(&cdns->mutex);

	अगर (!cdns->roles[role])
		वापस -ENXIO;

	अगर (cdns->roles[role]->state == CDNS_ROLE_STATE_ACTIVE)
		वापस 0;

	mutex_lock(&cdns->mutex);
	ret = cdns->roles[role]->start(cdns);
	अगर (!ret)
		cdns->roles[role]->state = CDNS_ROLE_STATE_ACTIVE;
	mutex_unlock(&cdns->mutex);

	वापस ret;
पूर्ण

अटल व्योम cdns_role_stop(काष्ठा cdns *cdns)
अणु
	क्रमागत usb_role role = cdns->role;

	अगर (WARN_ON(role > USB_ROLE_DEVICE))
		वापस;

	अगर (cdns->roles[role]->state == CDNS_ROLE_STATE_INACTIVE)
		वापस;

	mutex_lock(&cdns->mutex);
	cdns->roles[role]->stop(cdns);
	cdns->roles[role]->state = CDNS_ROLE_STATE_INACTIVE;
	mutex_unlock(&cdns->mutex);
पूर्ण

अटल व्योम cdns_निकास_roles(काष्ठा cdns *cdns)
अणु
	cdns_role_stop(cdns);
	cdns_drd_निकास(cdns);
पूर्ण

/**
 * cdns_core_init_role - initialize role of operation
 * @cdns: Poपूर्णांकer to cdns काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
अटल पूर्णांक cdns_core_init_role(काष्ठा cdns *cdns)
अणु
	काष्ठा device *dev = cdns->dev;
	क्रमागत usb_dr_mode best_dr_mode;
	क्रमागत usb_dr_mode dr_mode;
	पूर्णांक ret;

	dr_mode = usb_get_dr_mode(dev);
	cdns->role = USB_ROLE_NONE;

	/*
	 * If driver can't पढ़ो mode by means of usb_get_dr_mode function then
	 * chooses mode according with Kernel configuration. This setting
	 * can be restricted later depending on strap pin configuration.
	 */
	अगर (dr_mode == USB_DR_MODE_UNKNOWN) अणु
		अगर (cdns->version == CDNSP_CONTROLLER_V2) अणु
			अगर (IS_ENABLED(CONFIG_USB_CDNSP_HOST) &&
			    IS_ENABLED(CONFIG_USB_CDNSP_GADGET))
				dr_mode = USB_DR_MODE_OTG;
			अन्यथा अगर (IS_ENABLED(CONFIG_USB_CDNSP_HOST))
				dr_mode = USB_DR_MODE_HOST;
			अन्यथा अगर (IS_ENABLED(CONFIG_USB_CDNSP_GADGET))
				dr_mode = USB_DR_MODE_PERIPHERAL;
		पूर्ण अन्यथा अणु
			अगर (IS_ENABLED(CONFIG_USB_CDNS3_HOST) &&
			    IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
				dr_mode = USB_DR_MODE_OTG;
			अन्यथा अगर (IS_ENABLED(CONFIG_USB_CDNS3_HOST))
				dr_mode = USB_DR_MODE_HOST;
			अन्यथा अगर (IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
				dr_mode = USB_DR_MODE_PERIPHERAL;
		पूर्ण
	पूर्ण

	/*
	 * At this poपूर्णांक cdns->dr_mode contains strap configuration.
	 * Driver try update this setting considering kernel configuration
	 */
	best_dr_mode = cdns->dr_mode;

	ret = cdns_idle_init(cdns);
	अगर (ret)
		वापस ret;

	अगर (dr_mode == USB_DR_MODE_OTG) अणु
		best_dr_mode = cdns->dr_mode;
	पूर्ण अन्यथा अगर (cdns->dr_mode == USB_DR_MODE_OTG) अणु
		best_dr_mode = dr_mode;
	पूर्ण अन्यथा अगर (cdns->dr_mode != dr_mode) अणु
		dev_err(dev, "Incorrect DRD configuration\n");
		वापस -EINVAL;
	पूर्ण

	dr_mode = best_dr_mode;

	अगर (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_HOST) अणु
		अगर ((cdns->version == CDNSP_CONTROLLER_V2 &&
		     IS_ENABLED(CONFIG_USB_CDNSP_HOST)) ||
		    (cdns->version < CDNSP_CONTROLLER_V2 &&
		     IS_ENABLED(CONFIG_USB_CDNS3_HOST)))
			ret = cdns_host_init(cdns);
		अन्यथा
			ret = -ENXIO;

		अगर (ret) अणु
			dev_err(dev, "Host initialization failed with %d\n",
				ret);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_PERIPHERAL) अणु
		अगर (cdns->gadget_init)
			ret = cdns->gadget_init(cdns);
		अन्यथा
			ret = -ENXIO;

		अगर (ret) अणु
			dev_err(dev, "Device initialization failed with %d\n",
				ret);
			जाओ err;
		पूर्ण
	पूर्ण

	cdns->dr_mode = dr_mode;

	ret = cdns_drd_update_mode(cdns);
	अगर (ret)
		जाओ err;

	/* Initialize idle role to start with */
	ret = cdns_role_start(cdns, USB_ROLE_NONE);
	अगर (ret)
		जाओ err;

	चयन (cdns->dr_mode) अणु
	हाल USB_DR_MODE_OTG:
		ret = cdns_hw_role_चयन(cdns);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल USB_DR_MODE_PERIPHERAL:
		ret = cdns_role_start(cdns, USB_ROLE_DEVICE);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल USB_DR_MODE_HOST:
		ret = cdns_role_start(cdns, USB_ROLE_HOST);
		अगर (ret)
			जाओ err;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	cdns_निकास_roles(cdns);
	वापस ret;
पूर्ण

/**
 * cdns_hw_role_state_machine  - role चयन state machine based on hw events.
 * @cdns: Poपूर्णांकer to controller काष्ठाure.
 *
 * Returns next role to be entered based on hw events.
 */
अटल क्रमागत usb_role cdns_hw_role_state_machine(काष्ठा cdns *cdns)
अणु
	क्रमागत usb_role role = USB_ROLE_NONE;
	पूर्णांक id, vbus;

	अगर (cdns->dr_mode != USB_DR_MODE_OTG) अणु
		अगर (cdns_is_host(cdns))
			role = USB_ROLE_HOST;
		अगर (cdns_is_device(cdns))
			role = USB_ROLE_DEVICE;

		वापस role;
	पूर्ण

	id = cdns_get_id(cdns);
	vbus = cdns_get_vbus(cdns);

	/*
	 * Role change state machine
	 * Inमाला_दो: ID, VBUS
	 * Previous state: cdns->role
	 * Next state: role
	 */
	role = cdns->role;

	चयन (role) अणु
	हाल USB_ROLE_NONE:
		/*
		 * Driver treats USB_ROLE_NONE synonymous to IDLE state from
		 * controller specअगरication.
		 */
		अगर (!id)
			role = USB_ROLE_HOST;
		अन्यथा अगर (vbus)
			role = USB_ROLE_DEVICE;
		अवरोध;
	हाल USB_ROLE_HOST: /* from HOST, we can only change to NONE */
		अगर (id)
			role = USB_ROLE_NONE;
		अवरोध;
	हाल USB_ROLE_DEVICE: /* from GADGET, we can only change to NONE*/
		अगर (!vbus)
			role = USB_ROLE_NONE;
		अवरोध;
	पूर्ण

	dev_dbg(cdns->dev, "role %d -> %d\n", cdns->role, role);

	वापस role;
पूर्ण

अटल पूर्णांक cdns_idle_role_start(काष्ठा cdns *cdns)
अणु
	वापस 0;
पूर्ण

अटल व्योम cdns_idle_role_stop(काष्ठा cdns *cdns)
अणु
	/* Program Lane swap and bring PHY out of RESET */
	phy_reset(cdns->usb3_phy);
पूर्ण

अटल पूर्णांक cdns_idle_init(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, माप(*rdrv), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start = cdns_idle_role_start;
	rdrv->stop = cdns_idle_role_stop;
	rdrv->state = CDNS_ROLE_STATE_INACTIVE;
	rdrv->suspend = शून्य;
	rdrv->resume = शून्य;
	rdrv->name = "idle";

	cdns->roles[USB_ROLE_NONE] = rdrv;

	वापस 0;
पूर्ण

/**
 * cdns_hw_role_चयन - चयन roles based on HW state
 * @cdns: controller
 */
पूर्णांक cdns_hw_role_चयन(काष्ठा cdns *cdns)
अणु
	क्रमागत usb_role real_role, current_role;
	पूर्णांक ret = 0;

	/* Depends on role चयन class */
	अगर (cdns->role_sw)
		वापस 0;

	pm_runसमय_get_sync(cdns->dev);

	current_role = cdns->role;
	real_role = cdns_hw_role_state_machine(cdns);

	/* Do nothing अगर nothing changed */
	अगर (current_role == real_role)
		जाओ निकास;

	cdns_role_stop(cdns);

	dev_dbg(cdns->dev, "Switching role %d -> %d", current_role, real_role);

	ret = cdns_role_start(cdns, real_role);
	अगर (ret) अणु
		/* Back to current role */
		dev_err(cdns->dev, "set %d has failed, back to %d\n",
			real_role, current_role);
		ret = cdns_role_start(cdns, current_role);
		अगर (ret)
			dev_err(cdns->dev, "back to %d failed too\n",
				current_role);
	पूर्ण
निकास:
	pm_runसमय_put_sync(cdns->dev);
	वापस ret;
पूर्ण

/**
 * cdsn3_role_get - get current role of controller.
 *
 * @sw: poपूर्णांकer to USB role चयन काष्ठाure
 *
 * Returns role
 */
अटल क्रमागत usb_role cdns_role_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा cdns *cdns = usb_role_चयन_get_drvdata(sw);

	वापस cdns->role;
पूर्ण

/**
 * cdns_role_set - set current role of controller.
 *
 * @sw: poपूर्णांकer to USB role चयन काष्ठाure
 * @role: the previous role
 * Handles below events:
 * - Role चयन क्रम dual-role devices
 * - USB_ROLE_GADGET <--> USB_ROLE_NONE क्रम peripheral-only devices
 */
अटल पूर्णांक cdns_role_set(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	काष्ठा cdns *cdns = usb_role_चयन_get_drvdata(sw);
	पूर्णांक ret = 0;

	pm_runसमय_get_sync(cdns->dev);

	अगर (cdns->role == role)
		जाओ pm_put;

	अगर (cdns->dr_mode == USB_DR_MODE_HOST) अणु
		चयन (role) अणु
		हाल USB_ROLE_NONE:
		हाल USB_ROLE_HOST:
			अवरोध;
		शेष:
			जाओ pm_put;
		पूर्ण
	पूर्ण

	अगर (cdns->dr_mode == USB_DR_MODE_PERIPHERAL) अणु
		चयन (role) अणु
		हाल USB_ROLE_NONE:
		हाल USB_ROLE_DEVICE:
			अवरोध;
		शेष:
			जाओ pm_put;
		पूर्ण
	पूर्ण

	cdns_role_stop(cdns);
	ret = cdns_role_start(cdns, role);
	अगर (ret)
		dev_err(cdns->dev, "set role %d has failed\n", role);

pm_put:
	pm_runसमय_put_sync(cdns->dev);
	वापस ret;
पूर्ण


/**
 * cdns_wakeup_irq - पूर्णांकerrupt handler क्रम wakeup events
 * @irq: irq number क्रम cdns3/cdnsp core device
 * @data: काष्ठाure of cdns
 *
 * Returns IRQ_HANDLED or IRQ_NONE
 */
अटल irqवापस_t cdns_wakeup_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns *cdns = data;

	अगर (cdns->in_lpm) अणु
		disable_irq_nosync(irq);
		cdns->wakeup_pending = true;
		अगर ((cdns->role == USB_ROLE_HOST) && cdns->host_dev)
			pm_request_resume(&cdns->host_dev->dev);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/**
 * cdns_probe - probe क्रम cdns3/cdnsp core device
 * @cdns: Poपूर्णांकer to cdns काष्ठाure.
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
पूर्णांक cdns_init(काष्ठा cdns *cdns)
अणु
	काष्ठा device *dev = cdns->dev;
	पूर्णांक ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "error setting dma mask: %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&cdns->mutex);

	अगर (device_property_पढ़ो_bool(dev, "usb-role-switch")) अणु
		काष्ठा usb_role_चयन_desc sw_desc = अणु पूर्ण;

		sw_desc.set = cdns_role_set;
		sw_desc.get = cdns_role_get;
		sw_desc.allow_userspace_control = true;
		sw_desc.driver_data = cdns;
		sw_desc.fwnode = dev->fwnode;

		cdns->role_sw = usb_role_चयन_रेजिस्टर(dev, &sw_desc);
		अगर (IS_ERR(cdns->role_sw)) अणु
			dev_warn(dev, "Unable to register Role Switch\n");
			वापस PTR_ERR(cdns->role_sw);
		पूर्ण
	पूर्ण

	अगर (cdns->wakeup_irq) अणु
		ret = devm_request_irq(cdns->dev, cdns->wakeup_irq,
						cdns_wakeup_irq,
						IRQF_SHARED,
						dev_name(cdns->dev), cdns);

		अगर (ret) अणु
			dev_err(cdns->dev, "couldn't register wakeup irq handler\n");
			जाओ role_चयन_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = cdns_drd_init(cdns);
	अगर (ret)
		जाओ init_failed;

	ret = cdns_core_init_role(cdns);
	अगर (ret)
		जाओ init_failed;

	spin_lock_init(&cdns->lock);

	dev_dbg(dev, "Cadence USB3 core: probe succeed\n");

	वापस 0;
init_failed:
	cdns_drd_निकास(cdns);
role_चयन_unरेजिस्टर:
	अगर (cdns->role_sw)
		usb_role_चयन_unरेजिस्टर(cdns->role_sw);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_init);

/**
 * cdns_हटाओ - unbind drd driver and clean up
 * @cdns: Poपूर्णांकer to cdns काष्ठाure.
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
पूर्णांक cdns_हटाओ(काष्ठा cdns *cdns)
अणु
	cdns_निकास_roles(cdns);
	usb_role_चयन_unरेजिस्टर(cdns->role_sw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक cdns_suspend(काष्ठा cdns *cdns)
अणु
	काष्ठा device *dev = cdns->dev;
	अचिन्हित दीर्घ flags;

	अगर (pm_runसमय_status_suspended(dev))
		pm_runसमय_resume(dev);

	अगर (cdns->roles[cdns->role]->suspend) अणु
		spin_lock_irqsave(&cdns->lock, flags);
		cdns->roles[cdns->role]->suspend(cdns, false);
		spin_unlock_irqrestore(&cdns->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_suspend);

पूर्णांक cdns_resume(काष्ठा cdns *cdns, u8 set_active)
अणु
	काष्ठा device *dev = cdns->dev;
	क्रमागत usb_role real_role;
	bool role_changed = false;
	पूर्णांक ret = 0;

	अगर (cdns_घातer_is_lost(cdns)) अणु
		अगर (cdns->role_sw) अणु
			cdns->role = cdns_role_get(cdns->role_sw);
		पूर्ण अन्यथा अणु
			real_role = cdns_hw_role_state_machine(cdns);
			अगर (real_role != cdns->role) अणु
				ret = cdns_hw_role_चयन(cdns);
				अगर (ret)
					वापस ret;
				role_changed = true;
			पूर्ण
		पूर्ण

		अगर (!role_changed) अणु
			अगर (cdns->role == USB_ROLE_HOST)
				ret = cdns_drd_host_on(cdns);
			अन्यथा अगर (cdns->role == USB_ROLE_DEVICE)
				ret = cdns_drd_gadget_on(cdns);

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (cdns->roles[cdns->role]->resume)
		cdns->roles[cdns->role]->resume(cdns, cdns_घातer_is_lost(cdns));

	अगर (set_active) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdns_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

MODULE_AUTHOR("Peter Chen <peter.chen@nxp.com>");
MODULE_AUTHOR("Pawel Laszczak <pawell@cadence.com>");
MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_DESCRIPTION("Cadence USBSS and USBSSP DRD Driver");
MODULE_LICENSE("GPL");
