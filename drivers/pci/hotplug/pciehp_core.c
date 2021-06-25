<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Express Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2003-2004 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>, <kristen.c.accardi@पूर्णांकel.com>
 *
 * Authors:
 *   Dan Zink <dan.zink@compaq.com>
 *   Greg Kroah-Harपंचांगan <greg@kroah.com>
 *   Dely Sy <dely.l.sy@पूर्णांकel.com>"
 */

#घोषणा pr_fmt(fmt) "pciehp: " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "pciehp.h"

#समावेश "../pci.h"

/* Global variables */
bool pciehp_poll_mode;
पूर्णांक pciehp_poll_समय;

/*
 * not really modular, but the easiest way to keep compat with existing
 * bootargs behaviour is to जारी using module_param here.
 */
module_param(pciehp_poll_mode, bool, 0644);
module_param(pciehp_poll_समय, पूर्णांक, 0644);
MODULE_PARM_DESC(pciehp_poll_mode, "Using polling mechanism for hot-plug events or not");
MODULE_PARM_DESC(pciehp_poll_समय, "Polling mechanism frequency, in seconds");

अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *slot, u8 value);
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *slot, u8 *value);

अटल पूर्णांक init_slot(काष्ठा controller *ctrl)
अणु
	काष्ठा hotplug_slot_ops *ops;
	अक्षर name[SLOT_NAME_SIZE];
	पूर्णांक retval;

	/* Setup hotplug slot ops */
	ops = kzalloc(माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	ops->enable_slot = pciehp_sysfs_enable_slot;
	ops->disable_slot = pciehp_sysfs_disable_slot;
	ops->get_घातer_status = get_घातer_status;
	ops->get_adapter_status = get_adapter_status;
	ops->reset_slot = pciehp_reset_slot;
	अगर (MRL_SENS(ctrl))
		ops->get_latch_status = get_latch_status;
	अगर (ATTN_LED(ctrl)) अणु
		ops->get_attention_status = pciehp_get_attention_status;
		ops->set_attention_status = set_attention_status;
	पूर्ण अन्यथा अगर (ctrl->pcie->port->hotplug_user_indicators) अणु
		ops->get_attention_status = pciehp_get_raw_indicator_status;
		ops->set_attention_status = pciehp_set_raw_indicator_status;
	पूर्ण

	/* रेजिस्टर this slot with the hotplug pci core */
	ctrl->hotplug_slot.ops = ops;
	snम_लिखो(name, SLOT_NAME_SIZE, "%u", PSN(ctrl));

	retval = pci_hp_initialize(&ctrl->hotplug_slot,
				   ctrl->pcie->port->subordinate, 0, name);
	अगर (retval) अणु
		ctrl_err(ctrl, "pci_hp_initialize failed: error %d\n", retval);
		kमुक्त(ops);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम cleanup_slot(काष्ठा controller *ctrl)
अणु
	काष्ठा hotplug_slot *hotplug_slot = &ctrl->hotplug_slot;

	pci_hp_destroy(hotplug_slot);
	kमुक्त(hotplug_slot->ops);
पूर्ण

/*
 * set_attention_status - Turns the Attention Indicator on, off or blinking
 */
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 status)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl->pcie->port;

	अगर (status)
		status <<= PCI_EXP_SLTCTL_ATTN_IND_SHIFT;
	अन्यथा
		status = PCI_EXP_SLTCTL_ATTN_IND_OFF;

	pci_config_pm_runसमय_get(pdev);
	pciehp_set_indicators(ctrl, INDICATOR_NOOP, status);
	pci_config_pm_runसमय_put(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl->pcie->port;

	pci_config_pm_runसमय_get(pdev);
	pciehp_get_घातer_status(ctrl, value);
	pci_config_pm_runसमय_put(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl->pcie->port;

	pci_config_pm_runसमय_get(pdev);
	pciehp_get_latch_status(ctrl, value);
	pci_config_pm_runसमय_put(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl->pcie->port;
	पूर्णांक ret;

	pci_config_pm_runसमय_get(pdev);
	ret = pciehp_card_present_or_link_active(ctrl);
	pci_config_pm_runसमय_put(pdev);
	अगर (ret < 0)
		वापस ret;

	*value = ret;
	वापस 0;
पूर्ण

/**
 * pciehp_check_presence() - synthesize event अगर presence has changed
 * @ctrl: controller to check
 *
 * On probe and resume, an explicit presence check is necessary to bring up an
 * occupied slot or bring करोwn an unoccupied slot.  This can't be triggered by
 * events in the Slot Status रेजिस्टर, they may be stale and are thereक्रमe
 * cleared.  Secondly, sending an पूर्णांकerrupt क्रम "events that occur जबतक
 * पूर्णांकerrupt generation is disabled [when] पूर्णांकerrupt generation is subsequently
 * enabled" is optional per PCIe r4.0, sec 6.7.3.4.
 */
अटल व्योम pciehp_check_presence(काष्ठा controller *ctrl)
अणु
	पूर्णांक occupied;

	करोwn_पढ़ो(&ctrl->reset_lock);
	mutex_lock(&ctrl->state_lock);

	occupied = pciehp_card_present_or_link_active(ctrl);
	अगर ((occupied > 0 && (ctrl->state == OFF_STATE ||
			  ctrl->state == BLINKINGON_STATE)) ||
	    (!occupied && (ctrl->state == ON_STATE ||
			   ctrl->state == BLINKINGOFF_STATE)))
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);

	mutex_unlock(&ctrl->state_lock);
	up_पढ़ो(&ctrl->reset_lock);
पूर्ण

अटल पूर्णांक pciehp_probe(काष्ठा pcie_device *dev)
अणु
	पूर्णांक rc;
	काष्ठा controller *ctrl;

	/* If this is not a "hotplug" service, we have no business here. */
	अगर (dev->service != PCIE_PORT_SERVICE_HP)
		वापस -ENODEV;

	अगर (!dev->port->subordinate) अणु
		/* Can happen अगर we run out of bus numbers during probe */
		pci_err(dev->port,
			"Hotplug bridge without secondary bus, ignoring\n");
		वापस -ENODEV;
	पूर्ण

	ctrl = pcie_init(dev);
	अगर (!ctrl) अणु
		pci_err(dev->port, "Controller initialization failed\n");
		वापस -ENODEV;
	पूर्ण
	set_service_data(dev, ctrl);

	/* Setup the slot inक्रमmation काष्ठाures */
	rc = init_slot(ctrl);
	अगर (rc) अणु
		अगर (rc == -EBUSY)
			ctrl_warn(ctrl, "Slot already registered by another hotplug driver\n");
		अन्यथा
			ctrl_err(ctrl, "Slot initialization failed (%d)\n", rc);
		जाओ err_out_release_ctlr;
	पूर्ण

	/* Enable events after we have setup the data काष्ठाures */
	rc = pcie_init_notअगरication(ctrl);
	अगर (rc) अणु
		ctrl_err(ctrl, "Notification initialization failed (%d)\n", rc);
		जाओ err_out_मुक्त_ctrl_slot;
	पूर्ण

	/* Publish to user space */
	rc = pci_hp_add(&ctrl->hotplug_slot);
	अगर (rc) अणु
		ctrl_err(ctrl, "Publication to user space failed (%d)\n", rc);
		जाओ err_out_shutकरोwn_notअगरication;
	पूर्ण

	pciehp_check_presence(ctrl);

	वापस 0;

err_out_shutकरोwn_notअगरication:
	pcie_shutकरोwn_notअगरication(ctrl);
err_out_मुक्त_ctrl_slot:
	cleanup_slot(ctrl);
err_out_release_ctlr:
	pciehp_release_ctrl(ctrl);
	वापस -ENODEV;
पूर्ण

अटल व्योम pciehp_हटाओ(काष्ठा pcie_device *dev)
अणु
	काष्ठा controller *ctrl = get_service_data(dev);

	pci_hp_del(&ctrl->hotplug_slot);
	pcie_shutकरोwn_notअगरication(ctrl);
	cleanup_slot(ctrl);
	pciehp_release_ctrl(ctrl);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल bool pme_is_native(काष्ठा pcie_device *dev)
अणु
	स्थिर काष्ठा pci_host_bridge *host;

	host = pci_find_host_bridge(dev->port->bus);
	वापस pcie_ports_native || host->native_pme;
पूर्ण

अटल व्योम pciehp_disable_पूर्णांकerrupt(काष्ठा pcie_device *dev)
अणु
	/*
	 * Disable hotplug पूर्णांकerrupt so that it करोes not trigger
	 * immediately when the करोwnstream link goes करोwn.
	 */
	अगर (pme_is_native(dev))
		pcie_disable_पूर्णांकerrupt(get_service_data(dev));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pciehp_suspend(काष्ठा pcie_device *dev)
अणु
	/*
	 * If the port is alपढ़ोy runसमय suspended we can keep it that
	 * way.
	 */
	अगर (dev_pm_skip_suspend(&dev->port->dev))
		वापस 0;

	pciehp_disable_पूर्णांकerrupt(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pciehp_resume_noirq(काष्ठा pcie_device *dev)
अणु
	काष्ठा controller *ctrl = get_service_data(dev);

	/* pci_restore_state() just wrote to the Slot Control रेजिस्टर */
	ctrl->cmd_started = jअगरfies;
	ctrl->cmd_busy = true;

	/* clear spurious events from rediscovery of inserted card */
	अगर (ctrl->state == ON_STATE || ctrl->state == BLINKINGOFF_STATE)
		pcie_clear_hotplug_events(ctrl);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pciehp_resume(काष्ठा pcie_device *dev)
अणु
	काष्ठा controller *ctrl = get_service_data(dev);

	अगर (pme_is_native(dev))
		pcie_enable_पूर्णांकerrupt(ctrl);

	pciehp_check_presence(ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक pciehp_runसमय_suspend(काष्ठा pcie_device *dev)
अणु
	pciehp_disable_पूर्णांकerrupt(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pciehp_runसमय_resume(काष्ठा pcie_device *dev)
अणु
	काष्ठा controller *ctrl = get_service_data(dev);

	/* pci_restore_state() just wrote to the Slot Control रेजिस्टर */
	ctrl->cmd_started = jअगरfies;
	ctrl->cmd_busy = true;

	/* clear spurious events from rediscovery of inserted card */
	अगर ((ctrl->state == ON_STATE || ctrl->state == BLINKINGOFF_STATE) &&
	     pme_is_native(dev))
		pcie_clear_hotplug_events(ctrl);

	वापस pciehp_resume(dev);
पूर्ण
#पूर्ण_अगर /* PM */

अटल काष्ठा pcie_port_service_driver hpdriver_portdrv = अणु
	.name		= "pciehp",
	.port_type	= PCIE_ANY_PORT,
	.service	= PCIE_PORT_SERVICE_HP,

	.probe		= pciehp_probe,
	.हटाओ		= pciehp_हटाओ,

#अगर_घोषित	CONFIG_PM
#अगर_घोषित	CONFIG_PM_SLEEP
	.suspend	= pciehp_suspend,
	.resume_noirq	= pciehp_resume_noirq,
	.resume		= pciehp_resume,
#पूर्ण_अगर
	.runसमय_suspend = pciehp_runसमय_suspend,
	.runसमय_resume	= pciehp_runसमय_resume,
#पूर्ण_अगर	/* PM */
पूर्ण;

पूर्णांक __init pcie_hp_init(व्योम)
अणु
	पूर्णांक retval = 0;

	retval = pcie_port_service_रेजिस्टर(&hpdriver_portdrv);
	pr_debug("pcie_port_service_register = %d\n", retval);
	अगर (retval)
		pr_debug("Failure to register service\n");

	वापस retval;
पूर्ण
