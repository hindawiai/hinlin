<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Standard Hot Plug Controller Driver
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
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश "shpchp.h"

/* Global variables */
bool shpchp_debug;
bool shpchp_poll_mode;
पूर्णांक shpchp_poll_समय;

#घोषणा DRIVER_VERSION	"0.4"
#घोषणा DRIVER_AUTHOR	"Dan Zink <dan.zink@compaq.com>, Greg Kroah-Hartman <greg@kroah.com>, Dely Sy <dely.l.sy@intel.com>"
#घोषणा DRIVER_DESC	"Standard Hot Plug PCI Controller Driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(shpchp_debug, bool, 0644);
module_param(shpchp_poll_mode, bool, 0644);
module_param(shpchp_poll_समय, पूर्णांक, 0644);
MODULE_PARM_DESC(shpchp_debug, "Debugging mode enabled or not");
MODULE_PARM_DESC(shpchp_poll_mode, "Using polling mechanism for hot-plug events or not");
MODULE_PARM_DESC(shpchp_poll_समय, "Polling mechanism frequency, in seconds");

#घोषणा SHPC_MODULE_NAME "shpchp"

अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *slot, u8 value);
अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *slot, u8 *value);

अटल स्थिर काष्ठा hotplug_slot_ops shpchp_hotplug_slot_ops = अणु
	.set_attention_status =	set_attention_status,
	.enable_slot =		enable_slot,
	.disable_slot =		disable_slot,
	.get_घातer_status =	get_घातer_status,
	.get_attention_status =	get_attention_status,
	.get_latch_status =	get_latch_status,
	.get_adapter_status =	get_adapter_status,
पूर्ण;

अटल पूर्णांक init_slots(काष्ठा controller *ctrl)
अणु
	काष्ठा slot *slot;
	काष्ठा hotplug_slot *hotplug_slot;
	अक्षर name[SLOT_NAME_SIZE];
	पूर्णांक retval;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->num_slots; i++) अणु
		slot = kzalloc(माप(*slot), GFP_KERNEL);
		अगर (!slot) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण

		hotplug_slot = &slot->hotplug_slot;

		slot->hp_slot = i;
		slot->ctrl = ctrl;
		slot->bus = ctrl->pci_dev->subordinate->number;
		slot->device = ctrl->slot_device_offset + i;
		slot->hpc_ops = ctrl->hpc_ops;
		slot->number = ctrl->first_slot + (ctrl->slot_num_inc * i);

		slot->wq = alloc_workqueue("shpchp-%d", 0, 0, slot->number);
		अगर (!slot->wq) अणु
			retval = -ENOMEM;
			जाओ error_slot;
		पूर्ण

		mutex_init(&slot->lock);
		INIT_DELAYED_WORK(&slot->work, shpchp_queue_pushbutton_work);

		/* रेजिस्टर this slot with the hotplug pci core */
		snम_लिखो(name, SLOT_NAME_SIZE, "%d", slot->number);
		hotplug_slot->ops = &shpchp_hotplug_slot_ops;

		ctrl_dbg(ctrl, "Registering domain:bus:dev=%04x:%02x:%02x hp_slot=%x sun=%x slot_device_offset=%x\n",
			 pci_करोमुख्य_nr(ctrl->pci_dev->subordinate),
			 slot->bus, slot->device, slot->hp_slot, slot->number,
			 ctrl->slot_device_offset);
		retval = pci_hp_रेजिस्टर(hotplug_slot,
				ctrl->pci_dev->subordinate, slot->device, name);
		अगर (retval) अणु
			ctrl_err(ctrl, "pci_hp_register failed with error %d\n",
				 retval);
			जाओ error_slotwq;
		पूर्ण

		get_घातer_status(hotplug_slot, &slot->pwr_save);
		get_attention_status(hotplug_slot, &slot->attention_save);
		get_latch_status(hotplug_slot, &slot->latch_save);
		get_adapter_status(hotplug_slot, &slot->presence_save);

		list_add(&slot->slot_list, &ctrl->slot_list);
	पूर्ण

	वापस 0;
error_slotwq:
	destroy_workqueue(slot->wq);
error_slot:
	kमुक्त(slot);
error:
	वापस retval;
पूर्ण

व्योम cleanup_slots(काष्ठा controller *ctrl)
अणु
	काष्ठा slot *slot, *next;

	list_क्रम_each_entry_safe(slot, next, &ctrl->slot_list, slot_list) अणु
		list_del(&slot->slot_list);
		cancel_delayed_work(&slot->work);
		destroy_workqueue(slot->wq);
		pci_hp_deरेजिस्टर(&slot->hotplug_slot);
		kमुक्त(slot);
	पूर्ण
पूर्ण

/*
 * set_attention_status - Turns the Amber LED क्रम a slot on, off or blink
 */
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 status)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	slot->attention_save = status;
	slot->hpc_ops->set_attention_status(slot, status);

	वापस 0;
पूर्ण

अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	वापस shpchp_sysfs_enable_slot(slot);
पूर्ण

अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	वापस shpchp_sysfs_disable_slot(slot);
पूर्ण

अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);
	पूर्णांक retval;

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	retval = slot->hpc_ops->get_घातer_status(slot, value);
	अगर (retval < 0)
		*value = slot->pwr_save;

	वापस 0;
पूर्ण

अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);
	पूर्णांक retval;

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	retval = slot->hpc_ops->get_attention_status(slot, value);
	अगर (retval < 0)
		*value = slot->attention_save;

	वापस 0;
पूर्ण

अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);
	पूर्णांक retval;

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	retval = slot->hpc_ops->get_latch_status(slot, value);
	अगर (retval < 0)
		*value = slot->latch_save;

	वापस 0;
पूर्ण

अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = get_slot(hotplug_slot);
	पूर्णांक retval;

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	retval = slot->hpc_ops->get_adapter_status(slot, value);
	अगर (retval < 0)
		*value = slot->presence_save;

	वापस 0;
पूर्ण

अटल bool shpc_capable(काष्ठा pci_dev *bridge)
अणु
	/*
	 * It is assumed that AMD GOLAM chips support SHPC but they करो not
	 * have SHPC capability.
	 */
	अगर (bridge->venकरोr == PCI_VENDOR_ID_AMD &&
	    bridge->device == PCI_DEVICE_ID_AMD_GOLAM_7450)
		वापस true;

	अगर (pci_find_capability(bridge, PCI_CAP_ID_SHPC))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक shpc_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;
	काष्ठा controller *ctrl;

	अगर (!shpc_capable(pdev))
		वापस -ENODEV;

	अगर (acpi_get_hp_hw_control_from_firmware(pdev))
		वापस -ENODEV;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		जाओ err_out_none;

	INIT_LIST_HEAD(&ctrl->slot_list);

	rc = shpc_init(ctrl, pdev);
	अगर (rc) अणु
		ctrl_dbg(ctrl, "Controller initialization failed\n");
		जाओ err_out_मुक्त_ctrl;
	पूर्ण

	pci_set_drvdata(pdev, ctrl);

	/* Setup the slot inक्रमmation काष्ठाures */
	rc = init_slots(ctrl);
	अगर (rc) अणु
		ctrl_err(ctrl, "Slot initialization failed\n");
		जाओ err_out_release_ctlr;
	पूर्ण

	rc = shpchp_create_ctrl_files(ctrl);
	अगर (rc)
		जाओ err_cleanup_slots;

	pdev->shpc_managed = 1;
	वापस 0;

err_cleanup_slots:
	cleanup_slots(ctrl);
err_out_release_ctlr:
	ctrl->hpc_ops->release_ctlr(ctrl);
err_out_मुक्त_ctrl:
	kमुक्त(ctrl);
err_out_none:
	वापस -ENODEV;
पूर्ण

अटल व्योम shpc_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा controller *ctrl = pci_get_drvdata(dev);

	dev->shpc_managed = 0;
	shpchp_हटाओ_ctrl_files(ctrl);
	ctrl->hpc_ops->release_ctlr(ctrl);
	kमुक्त(ctrl);
पूर्ण

अटल स्थिर काष्ठा pci_device_id shpcd_pci_tbl[] = अणु
	अणुPCI_DEVICE_CLASS(((PCI_CLASS_BRIDGE_PCI << 8) | 0x00), ~0)पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, shpcd_pci_tbl);

अटल काष्ठा pci_driver shpc_driver = अणु
	.name =		SHPC_MODULE_NAME,
	.id_table =	shpcd_pci_tbl,
	.probe =	shpc_probe,
	.हटाओ =	shpc_हटाओ,
पूर्ण;

अटल पूर्णांक __init shpcd_init(व्योम)
अणु
	पूर्णांक retval;

	retval = pci_रेजिस्टर_driver(&shpc_driver);
	dbg("%s: pci_register_driver = %d\n", __func__, retval);
	info(DRIVER_DESC " version: " DRIVER_VERSION "\n");

	वापस retval;
पूर्ण

अटल व्योम __निकास shpcd_cleanup(व्योम)
अणु
	dbg("unload_shpchpd()\n");
	pci_unरेजिस्टर_driver(&shpc_driver);
	info(DRIVER_DESC " version: " DRIVER_VERSION " unloaded\n");
पूर्ण

module_init(shpcd_init);
module_निकास(shpcd_cleanup);
