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
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश "../pci.h"
#समावेश "shpchp.h"

अटल व्योम पूर्णांकerrupt_event_handler(काष्ठा work_काष्ठा *work);
अटल पूर्णांक shpchp_enable_slot(काष्ठा slot *p_slot);
अटल पूर्णांक shpchp_disable_slot(काष्ठा slot *p_slot);

अटल पूर्णांक queue_पूर्णांकerrupt_event(काष्ठा slot *p_slot, u32 event_type)
अणु
	काष्ठा event_info *info;

	info = kदो_स्मृति(माप(*info), GFP_ATOMIC);
	अगर (!info)
		वापस -ENOMEM;

	info->event_type = event_type;
	info->p_slot = p_slot;
	INIT_WORK(&info->work, पूर्णांकerrupt_event_handler);

	queue_work(p_slot->wq, &info->work);

	वापस 0;
पूर्ण

u8 shpchp_handle_attention_button(u8 hp_slot, काष्ठा controller *ctrl)
अणु
	काष्ठा slot *p_slot;
	u32 event_type;

	/* Attention Button Change */
	ctrl_dbg(ctrl, "Attention button interrupt received\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));

	/*
	 *  Button pressed - See अगर need to TAKE ACTION!!!
	 */
	ctrl_info(ctrl, "Button pressed on Slot(%s)\n", slot_name(p_slot));
	event_type = INT_BUTTON_PRESS;

	queue_पूर्णांकerrupt_event(p_slot, event_type);

	वापस 0;

पूर्ण

u8 shpchp_handle_चयन_change(u8 hp_slot, काष्ठा controller *ctrl)
अणु
	काष्ठा slot *p_slot;
	u8 माला_लोtatus;
	u32 event_type;

	/* Switch Change */
	ctrl_dbg(ctrl, "Switch interrupt received\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));
	p_slot->hpc_ops->get_latch_status(p_slot, &माला_लोtatus);
	ctrl_dbg(ctrl, "Card present %x Power status %x\n",
		 p_slot->presence_save, p_slot->pwr_save);

	अगर (माला_लोtatus) अणु
		/*
		 * Switch खोलोed
		 */
		ctrl_info(ctrl, "Latch open on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_SWITCH_OPEN;
		अगर (p_slot->pwr_save && p_slot->presence_save) अणु
			event_type = INT_POWER_FAULT;
			ctrl_err(ctrl, "Surprise Removal of card\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 *  Switch बंदd
		 */
		ctrl_info(ctrl, "Latch close on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_SWITCH_CLOSE;
	पूर्ण

	queue_पूर्णांकerrupt_event(p_slot, event_type);

	वापस 1;
पूर्ण

u8 shpchp_handle_presence_change(u8 hp_slot, काष्ठा controller *ctrl)
अणु
	काष्ठा slot *p_slot;
	u32 event_type;

	/* Presence Change */
	ctrl_dbg(ctrl, "Presence/Notify input change\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	/*
	 * Save the presence state
	 */
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));
	अगर (p_slot->presence_save) अणु
		/*
		 * Card Present
		 */
		ctrl_info(ctrl, "Card present on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_PRESENCE_ON;
	पूर्ण अन्यथा अणु
		/*
		 * Not Present
		 */
		ctrl_info(ctrl, "Card not present on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_PRESENCE_OFF;
	पूर्ण

	queue_पूर्णांकerrupt_event(p_slot, event_type);

	वापस 1;
पूर्ण

u8 shpchp_handle_घातer_fault(u8 hp_slot, काष्ठा controller *ctrl)
अणु
	काष्ठा slot *p_slot;
	u32 event_type;

	/* Power fault */
	ctrl_dbg(ctrl, "Power fault interrupt received\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	अगर (!(p_slot->hpc_ops->query_घातer_fault(p_slot))) अणु
		/*
		 * Power fault Cleared
		 */
		ctrl_info(ctrl, "Power fault cleared on Slot(%s)\n",
			  slot_name(p_slot));
		p_slot->status = 0x00;
		event_type = INT_POWER_FAULT_CLEAR;
	पूर्ण अन्यथा अणु
		/*
		 *   Power fault
		 */
		ctrl_info(ctrl, "Power fault on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_POWER_FAULT;
		/* set घातer fault status क्रम this board */
		p_slot->status = 0xFF;
		ctrl_info(ctrl, "Power fault bit %x set\n", hp_slot);
	पूर्ण

	queue_पूर्णांकerrupt_event(p_slot, event_type);

	वापस 1;
पूर्ण

/* The following routines स्थिरitute the bulk of the
   hotplug controller logic
 */
अटल पूर्णांक change_bus_speed(काष्ठा controller *ctrl, काष्ठा slot *p_slot,
		क्रमागत pci_bus_speed speed)
अणु
	पूर्णांक rc = 0;

	ctrl_dbg(ctrl, "Change speed to %d\n", speed);
	rc = p_slot->hpc_ops->set_bus_speed_mode(p_slot, speed);
	अगर (rc) अणु
		ctrl_err(ctrl, "%s: Issue of set bus speed mode command failed\n",
			 __func__);
		वापस WRONG_BUS_FREQUENCY;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक fix_bus_speed(काष्ठा controller *ctrl, काष्ठा slot *pslot,
		u8 flag, क्रमागत pci_bus_speed asp, क्रमागत pci_bus_speed bsp,
		क्रमागत pci_bus_speed msp)
अणु
	पूर्णांक rc = 0;

	/*
	 * If other slots on the same bus are occupied, we cannot
	 * change the bus speed.
	 */
	अगर (flag) अणु
		अगर (asp < bsp) अणु
			ctrl_err(ctrl, "Speed of bus %x and adapter %x mismatch\n",
				 bsp, asp);
			rc = WRONG_BUS_FREQUENCY;
		पूर्ण
		वापस rc;
	पूर्ण

	अगर (asp < msp) अणु
		अगर (bsp != asp)
			rc = change_bus_speed(ctrl, pslot, asp);
	पूर्ण अन्यथा अणु
		अगर (bsp != msp)
			rc = change_bus_speed(ctrl, pslot, msp);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * board_added - Called after a board has been added to the प्रणाली.
 * @p_slot: target &slot
 *
 * Turns घातer on क्रम the board.
 * Configures board.
 */
अटल पूर्णांक board_added(काष्ठा slot *p_slot)
अणु
	u8 hp_slot;
	u8 slots_not_empty = 0;
	पूर्णांक rc = 0;
	क्रमागत pci_bus_speed asp, bsp, msp;
	काष्ठा controller *ctrl = p_slot->ctrl;
	काष्ठा pci_bus *parent = ctrl->pci_dev->subordinate;

	hp_slot = p_slot->device - ctrl->slot_device_offset;

	ctrl_dbg(ctrl, "%s: p_slot->device, slot_offset, hp_slot = %d, %d ,%d\n",
		 __func__, p_slot->device, ctrl->slot_device_offset, hp_slot);

	/* Power on slot without connecting to bus */
	rc = p_slot->hpc_ops->घातer_on_slot(p_slot);
	अगर (rc) अणु
		ctrl_err(ctrl, "Failed to power on slot\n");
		वापस -1;
	पूर्ण

	अगर ((ctrl->pci_dev->venकरोr == 0x8086) && (ctrl->pci_dev->device == 0x0332)) अणु
		rc = p_slot->hpc_ops->set_bus_speed_mode(p_slot, PCI_SPEED_33MHz);
		अगर (rc) अणु
			ctrl_err(ctrl, "%s: Issue of set bus speed mode command failed\n",
				 __func__);
			वापस WRONG_BUS_FREQUENCY;
		पूर्ण

		/* turn on board, blink green LED, turn off Amber LED */
		rc = p_slot->hpc_ops->slot_enable(p_slot);
		अगर (rc) अणु
			ctrl_err(ctrl, "Issue of Slot Enable command failed\n");
			वापस rc;
		पूर्ण
	पूर्ण

	rc = p_slot->hpc_ops->get_adapter_speed(p_slot, &asp);
	अगर (rc) अणु
		ctrl_err(ctrl, "Can't get adapter speed or bus mode mismatch\n");
		वापस WRONG_BUS_FREQUENCY;
	पूर्ण

	bsp = ctrl->pci_dev->subordinate->cur_bus_speed;
	msp = ctrl->pci_dev->subordinate->max_bus_speed;

	/* Check अगर there are other slots or devices on the same bus */
	अगर (!list_empty(&ctrl->pci_dev->subordinate->devices))
		slots_not_empty = 1;

	ctrl_dbg(ctrl, "%s: slots_not_empty %d, adapter_speed %d, bus_speed %d, max_bus_speed %d\n",
		 __func__, slots_not_empty, asp,
		 bsp, msp);

	rc = fix_bus_speed(ctrl, p_slot, slots_not_empty, asp, bsp, msp);
	अगर (rc)
		वापस rc;

	/* turn on board, blink green LED, turn off Amber LED */
	rc = p_slot->hpc_ops->slot_enable(p_slot);
	अगर (rc) अणु
		ctrl_err(ctrl, "Issue of Slot Enable command failed\n");
		वापस rc;
	पूर्ण

	/* Wait क्रम ~1 second */
	msleep(1000);

	ctrl_dbg(ctrl, "%s: slot status = %x\n", __func__, p_slot->status);
	/* Check क्रम a घातer fault */
	अगर (p_slot->status == 0xFF) अणु
		/* घातer fault occurred, but it was benign */
		ctrl_dbg(ctrl, "%s: Power fault\n", __func__);
		p_slot->status = 0;
		जाओ err_निकास;
	पूर्ण

	अगर (shpchp_configure_device(p_slot)) अणु
		ctrl_err(ctrl, "Cannot add device at %04x:%02x:%02x\n",
			 pci_करोमुख्य_nr(parent), p_slot->bus, p_slot->device);
		जाओ err_निकास;
	पूर्ण

	p_slot->status = 0;
	p_slot->is_a_board = 0x01;
	p_slot->pwr_save = 1;

	p_slot->hpc_ops->green_led_on(p_slot);

	वापस 0;

err_निकास:
	/* turn off slot, turn on Amber LED, turn off Green LED */
	rc = p_slot->hpc_ops->slot_disable(p_slot);
	अगर (rc) अणु
		ctrl_err(ctrl, "%s: Issue of Slot Disable command failed\n",
			 __func__);
		वापस rc;
	पूर्ण

	वापस(rc);
पूर्ण


/**
 * हटाओ_board - Turns off slot and LEDs
 * @p_slot: target &slot
 */
अटल पूर्णांक हटाओ_board(काष्ठा slot *p_slot)
अणु
	काष्ठा controller *ctrl = p_slot->ctrl;
	u8 hp_slot;
	पूर्णांक rc;

	shpchp_unconfigure_device(p_slot);

	hp_slot = p_slot->device - ctrl->slot_device_offset;
	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	ctrl_dbg(ctrl, "%s: hp_slot = %d\n", __func__, hp_slot);

	/* Change status to shutकरोwn */
	अगर (p_slot->is_a_board)
		p_slot->status = 0x01;

	/* turn off slot, turn on Amber LED, turn off Green LED */
	rc = p_slot->hpc_ops->slot_disable(p_slot);
	अगर (rc) अणु
		ctrl_err(ctrl, "%s: Issue of Slot Disable command failed\n",
			 __func__);
		वापस rc;
	पूर्ण

	rc = p_slot->hpc_ops->set_attention_status(p_slot, 0);
	अगर (rc) अणु
		ctrl_err(ctrl, "Issue of Set Attention command failed\n");
		वापस rc;
	पूर्ण

	p_slot->pwr_save = 0;
	p_slot->is_a_board = 0;

	वापस 0;
पूर्ण


काष्ठा pushbutton_work_info अणु
	काष्ठा slot *p_slot;
	काष्ठा work_काष्ठा work;
पूर्ण;

/**
 * shpchp_pushbutton_thपढ़ो - handle pushbutton events
 * @work: &काष्ठा work_काष्ठा to be handled
 *
 * Scheduled procedure to handle blocking stuff क्रम the pushbuttons.
 * Handles all pending events and निकासs.
 */
अटल व्योम shpchp_pushbutton_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pushbutton_work_info *info =
		container_of(work, काष्ठा pushbutton_work_info, work);
	काष्ठा slot *p_slot = info->p_slot;

	mutex_lock(&p_slot->lock);
	चयन (p_slot->state) अणु
	हाल POWEROFF_STATE:
		mutex_unlock(&p_slot->lock);
		shpchp_disable_slot(p_slot);
		mutex_lock(&p_slot->lock);
		p_slot->state = STATIC_STATE;
		अवरोध;
	हाल POWERON_STATE:
		mutex_unlock(&p_slot->lock);
		अगर (shpchp_enable_slot(p_slot))
			p_slot->hpc_ops->green_led_off(p_slot);
		mutex_lock(&p_slot->lock);
		p_slot->state = STATIC_STATE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&p_slot->lock);

	kमुक्त(info);
पूर्ण

व्योम shpchp_queue_pushbutton_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा slot *p_slot = container_of(work, काष्ठा slot, work.work);
	काष्ठा pushbutton_work_info *info;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		ctrl_err(p_slot->ctrl, "%s: Cannot allocate memory\n",
			 __func__);
		वापस;
	पूर्ण
	info->p_slot = p_slot;
	INIT_WORK(&info->work, shpchp_pushbutton_thपढ़ो);

	mutex_lock(&p_slot->lock);
	चयन (p_slot->state) अणु
	हाल BLINKINGOFF_STATE:
		p_slot->state = POWEROFF_STATE;
		अवरोध;
	हाल BLINKINGON_STATE:
		p_slot->state = POWERON_STATE;
		अवरोध;
	शेष:
		kमुक्त(info);
		जाओ out;
	पूर्ण
	queue_work(p_slot->wq, &info->work);
 out:
	mutex_unlock(&p_slot->lock);
पूर्ण

अटल व्योम update_slot_info(काष्ठा slot *slot)
अणु
	slot->hpc_ops->get_घातer_status(slot, &slot->pwr_save);
	slot->hpc_ops->get_attention_status(slot, &slot->attention_save);
	slot->hpc_ops->get_latch_status(slot, &slot->latch_save);
	slot->hpc_ops->get_adapter_status(slot, &slot->presence_save);
पूर्ण

/*
 * Note: This function must be called with slot->lock held
 */
अटल व्योम handle_button_press_event(काष्ठा slot *p_slot)
अणु
	u8 माला_लोtatus;
	काष्ठा controller *ctrl = p_slot->ctrl;

	चयन (p_slot->state) अणु
	हाल STATIC_STATE:
		p_slot->hpc_ops->get_घातer_status(p_slot, &माला_लोtatus);
		अगर (माला_लोtatus) अणु
			p_slot->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl, "PCI slot #%s - powering off due to button press\n",
				  slot_name(p_slot));
		पूर्ण अन्यथा अणु
			p_slot->state = BLINKINGON_STATE;
			ctrl_info(ctrl, "PCI slot #%s - powering on due to button press\n",
				  slot_name(p_slot));
		पूर्ण
		/* blink green LED and turn off amber */
		p_slot->hpc_ops->green_led_blink(p_slot);
		p_slot->hpc_ops->set_attention_status(p_slot, 0);

		queue_delayed_work(p_slot->wq, &p_slot->work, 5*HZ);
		अवरोध;
	हाल BLINKINGOFF_STATE:
	हाल BLINKINGON_STATE:
		/*
		 * Cancel अगर we are still blinking; this means that we
		 * press the attention again beक्रमe the 5 sec. limit
		 * expires to cancel hot-add or hot-हटाओ
		 */
		ctrl_info(ctrl, "Button cancel on Slot(%s)\n",
			  slot_name(p_slot));
		cancel_delayed_work(&p_slot->work);
		अगर (p_slot->state == BLINKINGOFF_STATE)
			p_slot->hpc_ops->green_led_on(p_slot);
		अन्यथा
			p_slot->hpc_ops->green_led_off(p_slot);
		p_slot->hpc_ops->set_attention_status(p_slot, 0);
		ctrl_info(ctrl, "PCI slot #%s - action canceled due to button press\n",
			  slot_name(p_slot));
		p_slot->state = STATIC_STATE;
		अवरोध;
	हाल POWEROFF_STATE:
	हाल POWERON_STATE:
		/*
		 * Ignore अगर the slot is on घातer-on or घातer-off state;
		 * this means that the previous attention button action
		 * to hot-add or hot-हटाओ is undergoing
		 */
		ctrl_info(ctrl, "Button ignore on Slot(%s)\n",
			  slot_name(p_slot));
		update_slot_info(p_slot);
		अवरोध;
	शेष:
		ctrl_warn(ctrl, "Not a valid state\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकerrupt_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा event_info *info = container_of(work, काष्ठा event_info, work);
	काष्ठा slot *p_slot = info->p_slot;

	mutex_lock(&p_slot->lock);
	चयन (info->event_type) अणु
	हाल INT_BUTTON_PRESS:
		handle_button_press_event(p_slot);
		अवरोध;
	हाल INT_POWER_FAULT:
		ctrl_dbg(p_slot->ctrl, "%s: Power fault\n", __func__);
		p_slot->hpc_ops->set_attention_status(p_slot, 1);
		p_slot->hpc_ops->green_led_off(p_slot);
		अवरोध;
	शेष:
		update_slot_info(p_slot);
		अवरोध;
	पूर्ण
	mutex_unlock(&p_slot->lock);

	kमुक्त(info);
पूर्ण


अटल पूर्णांक shpchp_enable_slot (काष्ठा slot *p_slot)
अणु
	u8 माला_लोtatus = 0;
	पूर्णांक rc, retval = -ENODEV;
	काष्ठा controller *ctrl = p_slot->ctrl;

	/* Check to see अगर (latch बंदd, card present, घातer off) */
	mutex_lock(&p_slot->ctrl->crit_sect);
	rc = p_slot->hpc_ops->get_adapter_status(p_slot, &माला_लोtatus);
	अगर (rc || !माला_लोtatus) अणु
		ctrl_info(ctrl, "No adapter on slot(%s)\n", slot_name(p_slot));
		जाओ out;
	पूर्ण
	rc = p_slot->hpc_ops->get_latch_status(p_slot, &माला_लोtatus);
	अगर (rc || माला_लोtatus) अणु
		ctrl_info(ctrl, "Latch open on slot(%s)\n", slot_name(p_slot));
		जाओ out;
	पूर्ण
	rc = p_slot->hpc_ops->get_घातer_status(p_slot, &माला_लोtatus);
	अगर (rc || माला_लोtatus) अणु
		ctrl_info(ctrl, "Already enabled on slot(%s)\n",
			  slot_name(p_slot));
		जाओ out;
	पूर्ण

	p_slot->is_a_board = 1;

	/* We have to save the presence info क्रम these slots */
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));
	p_slot->hpc_ops->get_घातer_status(p_slot, &(p_slot->pwr_save));
	ctrl_dbg(ctrl, "%s: p_slot->pwr_save %x\n", __func__, p_slot->pwr_save);
	p_slot->hpc_ops->get_latch_status(p_slot, &माला_लोtatus);

	अगर ((p_slot->ctrl->pci_dev->venकरोr == PCI_VENDOR_ID_AMD &&
	     p_slot->ctrl->pci_dev->device == PCI_DEVICE_ID_AMD_POGO_7458)
	     && p_slot->ctrl->num_slots == 1) अणु
		/* handle AMD POGO errata; this must be करोne beक्रमe enable  */
		amd_pogo_errata_save_misc_reg(p_slot);
		retval = board_added(p_slot);
		/* handle AMD POGO errata; this must be करोne after enable  */
		amd_pogo_errata_restore_misc_reg(p_slot);
	पूर्ण अन्यथा
		retval = board_added(p_slot);

	अगर (retval) अणु
		p_slot->hpc_ops->get_adapter_status(p_slot,
				&(p_slot->presence_save));
		p_slot->hpc_ops->get_latch_status(p_slot, &माला_लोtatus);
	पूर्ण

	update_slot_info(p_slot);
 out:
	mutex_unlock(&p_slot->ctrl->crit_sect);
	वापस retval;
पूर्ण


अटल पूर्णांक shpchp_disable_slot (काष्ठा slot *p_slot)
अणु
	u8 माला_लोtatus = 0;
	पूर्णांक rc, retval = -ENODEV;
	काष्ठा controller *ctrl = p_slot->ctrl;

	अगर (!p_slot->ctrl)
		वापस -ENODEV;

	/* Check to see अगर (latch बंदd, card present, घातer on) */
	mutex_lock(&p_slot->ctrl->crit_sect);

	rc = p_slot->hpc_ops->get_adapter_status(p_slot, &माला_लोtatus);
	अगर (rc || !माला_लोtatus) अणु
		ctrl_info(ctrl, "No adapter on slot(%s)\n", slot_name(p_slot));
		जाओ out;
	पूर्ण
	rc = p_slot->hpc_ops->get_latch_status(p_slot, &माला_लोtatus);
	अगर (rc || माला_लोtatus) अणु
		ctrl_info(ctrl, "Latch open on slot(%s)\n", slot_name(p_slot));
		जाओ out;
	पूर्ण
	rc = p_slot->hpc_ops->get_घातer_status(p_slot, &माला_लोtatus);
	अगर (rc || !माला_लोtatus) अणु
		ctrl_info(ctrl, "Already disabled on slot(%s)\n",
			  slot_name(p_slot));
		जाओ out;
	पूर्ण

	retval = हटाओ_board(p_slot);
	update_slot_info(p_slot);
 out:
	mutex_unlock(&p_slot->ctrl->crit_sect);
	वापस retval;
पूर्ण

पूर्णांक shpchp_sysfs_enable_slot(काष्ठा slot *p_slot)
अणु
	पूर्णांक retval = -ENODEV;
	काष्ठा controller *ctrl = p_slot->ctrl;

	mutex_lock(&p_slot->lock);
	चयन (p_slot->state) अणु
	हाल BLINKINGON_STATE:
		cancel_delayed_work(&p_slot->work);
		fallthrough;
	हाल STATIC_STATE:
		p_slot->state = POWERON_STATE;
		mutex_unlock(&p_slot->lock);
		retval = shpchp_enable_slot(p_slot);
		mutex_lock(&p_slot->lock);
		p_slot->state = STATIC_STATE;
		अवरोध;
	हाल POWERON_STATE:
		ctrl_info(ctrl, "Slot %s is already in powering on state\n",
			  slot_name(p_slot));
		अवरोध;
	हाल BLINKINGOFF_STATE:
	हाल POWEROFF_STATE:
		ctrl_info(ctrl, "Already enabled on slot %s\n",
			  slot_name(p_slot));
		अवरोध;
	शेष:
		ctrl_err(ctrl, "Not a valid state on slot %s\n",
			 slot_name(p_slot));
		अवरोध;
	पूर्ण
	mutex_unlock(&p_slot->lock);

	वापस retval;
पूर्ण

पूर्णांक shpchp_sysfs_disable_slot(काष्ठा slot *p_slot)
अणु
	पूर्णांक retval = -ENODEV;
	काष्ठा controller *ctrl = p_slot->ctrl;

	mutex_lock(&p_slot->lock);
	चयन (p_slot->state) अणु
	हाल BLINKINGOFF_STATE:
		cancel_delayed_work(&p_slot->work);
		fallthrough;
	हाल STATIC_STATE:
		p_slot->state = POWEROFF_STATE;
		mutex_unlock(&p_slot->lock);
		retval = shpchp_disable_slot(p_slot);
		mutex_lock(&p_slot->lock);
		p_slot->state = STATIC_STATE;
		अवरोध;
	हाल POWEROFF_STATE:
		ctrl_info(ctrl, "Slot %s is already in powering off state\n",
			  slot_name(p_slot));
		अवरोध;
	हाल BLINKINGON_STATE:
	हाल POWERON_STATE:
		ctrl_info(ctrl, "Already disabled on slot %s\n",
			  slot_name(p_slot));
		अवरोध;
	शेष:
		ctrl_err(ctrl, "Not a valid state on slot %s\n",
			 slot_name(p_slot));
		अवरोध;
	पूर्ण
	mutex_unlock(&p_slot->lock);

	वापस retval;
पूर्ण
