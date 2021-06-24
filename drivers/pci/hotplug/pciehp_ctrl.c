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
 */

#घोषणा dev_fmt(fmt) "pciehp: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pci.h>
#समावेश "pciehp.h"

/* The following routines स्थिरitute the bulk of the
   hotplug controller logic
 */

#घोषणा SAFE_REMOVAL	 true
#घोषणा SURPRISE_REMOVAL false

अटल व्योम set_slot_off(काष्ठा controller *ctrl)
अणु
	/*
	 * Turn off slot, turn on attention indicator, turn off घातer
	 * indicator
	 */
	अगर (POWER_CTRL(ctrl)) अणु
		pciehp_घातer_off_slot(ctrl);

		/*
		 * After turning घातer off, we must रुको क्रम at least 1 second
		 * beक्रमe taking any action that relies on घातer having been
		 * हटाओd from the slot/adapter.
		 */
		msleep(1000);
	पूर्ण

	pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
			      PCI_EXP_SLTCTL_ATTN_IND_ON);
पूर्ण

/**
 * board_added - Called after a board has been added to the प्रणाली.
 * @ctrl: PCIe hotplug controller where board is added
 *
 * Turns घातer on क्रम the board.
 * Configures board.
 */
अटल पूर्णांक board_added(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval = 0;
	काष्ठा pci_bus *parent = ctrl->pcie->port->subordinate;

	अगर (POWER_CTRL(ctrl)) अणु
		/* Power on slot */
		retval = pciehp_घातer_on_slot(ctrl);
		अगर (retval)
			वापस retval;
	पूर्ण

	pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_BLINK,
			      INDICATOR_NOOP);

	/* Check link training status */
	retval = pciehp_check_link_status(ctrl);
	अगर (retval)
		जाओ err_निकास;

	/* Check क्रम a घातer fault */
	अगर (ctrl->घातer_fault_detected || pciehp_query_घातer_fault(ctrl)) अणु
		ctrl_err(ctrl, "Slot(%s): Power fault\n", slot_name(ctrl));
		retval = -EIO;
		जाओ err_निकास;
	पूर्ण

	retval = pciehp_configure_device(ctrl);
	अगर (retval) अणु
		अगर (retval != -EEXIST) अणु
			ctrl_err(ctrl, "Cannot add device at %04x:%02x:00\n",
				 pci_करोमुख्य_nr(parent), parent->number);
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_ON,
			      PCI_EXP_SLTCTL_ATTN_IND_OFF);
	वापस 0;

err_निकास:
	set_slot_off(ctrl);
	वापस retval;
पूर्ण

/**
 * हटाओ_board - Turn off slot and Power Indicator
 * @ctrl: PCIe hotplug controller where board is being हटाओd
 * @safe_removal: whether the board is safely हटाओd (versus surprise हटाओd)
 */
अटल व्योम हटाओ_board(काष्ठा controller *ctrl, bool safe_removal)
अणु
	pciehp_unconfigure_device(ctrl, safe_removal);

	अगर (POWER_CTRL(ctrl)) अणु
		pciehp_घातer_off_slot(ctrl);

		/*
		 * After turning घातer off, we must रुको क्रम at least 1 second
		 * beक्रमe taking any action that relies on घातer having been
		 * हटाओd from the slot/adapter.
		 */
		msleep(1000);

		/* Ignore link or presence changes caused by घातer off */
		atomic_and(~(PCI_EXP_SLTSTA_DLLSC | PCI_EXP_SLTSTA_PDC),
			   &ctrl->pending_events);
	पूर्ण

	pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
			      INDICATOR_NOOP);
पूर्ण

अटल पूर्णांक pciehp_enable_slot(काष्ठा controller *ctrl);
अटल पूर्णांक pciehp_disable_slot(काष्ठा controller *ctrl, bool safe_removal);

व्योम pciehp_request(काष्ठा controller *ctrl, पूर्णांक action)
अणु
	atomic_or(action, &ctrl->pending_events);
	अगर (!pciehp_poll_mode)
		irq_wake_thपढ़ो(ctrl->pcie->irq, ctrl);
पूर्ण

व्योम pciehp_queue_pushbutton_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा controller *ctrl = container_of(work, काष्ठा controller,
					       button_work.work);

	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल BLINKINGOFF_STATE:
		pciehp_request(ctrl, DISABLE_SLOT);
		अवरोध;
	हाल BLINKINGON_STATE:
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&ctrl->state_lock);
पूर्ण

व्योम pciehp_handle_button_press(काष्ठा controller *ctrl)
अणु
	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल OFF_STATE:
	हाल ON_STATE:
		अगर (ctrl->state == ON_STATE) अणु
			ctrl->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl, "Slot(%s): Powering off due to button press\n",
				  slot_name(ctrl));
		पूर्ण अन्यथा अणु
			ctrl->state = BLINKINGON_STATE;
			ctrl_info(ctrl, "Slot(%s) Powering on due to button press\n",
				  slot_name(ctrl));
		पूर्ण
		/* blink घातer indicator and turn off attention */
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_BLINK,
				      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		schedule_delayed_work(&ctrl->button_work, 5 * HZ);
		अवरोध;
	हाल BLINKINGOFF_STATE:
	हाल BLINKINGON_STATE:
		/*
		 * Cancel अगर we are still blinking; this means that we
		 * press the attention again beक्रमe the 5 sec. limit
		 * expires to cancel hot-add or hot-हटाओ
		 */
		ctrl_info(ctrl, "Slot(%s): Button cancel\n", slot_name(ctrl));
		cancel_delayed_work(&ctrl->button_work);
		अगर (ctrl->state == BLINKINGOFF_STATE) अणु
			ctrl->state = ON_STATE;
			pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_ON,
					      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		पूर्ण अन्यथा अणु
			ctrl->state = OFF_STATE;
			pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
					      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		पूर्ण
		ctrl_info(ctrl, "Slot(%s): Action canceled due to button press\n",
			  slot_name(ctrl));
		अवरोध;
	शेष:
		ctrl_err(ctrl, "Slot(%s): Ignoring invalid state %#x\n",
			 slot_name(ctrl), ctrl->state);
		अवरोध;
	पूर्ण
	mutex_unlock(&ctrl->state_lock);
पूर्ण

व्योम pciehp_handle_disable_request(काष्ठा controller *ctrl)
अणु
	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल BLINKINGON_STATE:
	हाल BLINKINGOFF_STATE:
		cancel_delayed_work(&ctrl->button_work);
		अवरोध;
	पूर्ण
	ctrl->state = POWEROFF_STATE;
	mutex_unlock(&ctrl->state_lock);

	ctrl->request_result = pciehp_disable_slot(ctrl, SAFE_REMOVAL);
पूर्ण

व्योम pciehp_handle_presence_or_link_change(काष्ठा controller *ctrl, u32 events)
अणु
	पूर्णांक present, link_active;

	/*
	 * If the slot is on and presence or link has changed, turn it off.
	 * Even अगर it's occupied again, we cannot assume the card is the same.
	 */
	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल BLINKINGOFF_STATE:
		cancel_delayed_work(&ctrl->button_work);
		fallthrough;
	हाल ON_STATE:
		ctrl->state = POWEROFF_STATE;
		mutex_unlock(&ctrl->state_lock);
		अगर (events & PCI_EXP_SLTSTA_DLLSC)
			ctrl_info(ctrl, "Slot(%s): Link Down\n",
				  slot_name(ctrl));
		अगर (events & PCI_EXP_SLTSTA_PDC)
			ctrl_info(ctrl, "Slot(%s): Card not present\n",
				  slot_name(ctrl));
		pciehp_disable_slot(ctrl, SURPRISE_REMOVAL);
		अवरोध;
	शेष:
		mutex_unlock(&ctrl->state_lock);
		अवरोध;
	पूर्ण

	/* Turn the slot on अगर it's occupied or link is up */
	mutex_lock(&ctrl->state_lock);
	present = pciehp_card_present(ctrl);
	link_active = pciehp_check_link_active(ctrl);
	अगर (present <= 0 && link_active <= 0) अणु
		mutex_unlock(&ctrl->state_lock);
		वापस;
	पूर्ण

	चयन (ctrl->state) अणु
	हाल BLINKINGON_STATE:
		cancel_delayed_work(&ctrl->button_work);
		fallthrough;
	हाल OFF_STATE:
		ctrl->state = POWERON_STATE;
		mutex_unlock(&ctrl->state_lock);
		अगर (present)
			ctrl_info(ctrl, "Slot(%s): Card present\n",
				  slot_name(ctrl));
		अगर (link_active)
			ctrl_info(ctrl, "Slot(%s): Link Up\n",
				  slot_name(ctrl));
		ctrl->request_result = pciehp_enable_slot(ctrl);
		अवरोध;
	शेष:
		mutex_unlock(&ctrl->state_lock);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __pciehp_enable_slot(काष्ठा controller *ctrl)
अणु
	u8 माला_लोtatus = 0;

	अगर (MRL_SENS(ctrl)) अणु
		pciehp_get_latch_status(ctrl, &माला_लोtatus);
		अगर (माला_लोtatus) अणु
			ctrl_info(ctrl, "Slot(%s): Latch open\n",
				  slot_name(ctrl));
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (POWER_CTRL(ctrl)) अणु
		pciehp_get_घातer_status(ctrl, &माला_लोtatus);
		अगर (माला_लोtatus) अणु
			ctrl_info(ctrl, "Slot(%s): Already enabled\n",
				  slot_name(ctrl));
			वापस 0;
		पूर्ण
	पूर्ण

	वापस board_added(ctrl);
पूर्ण

अटल पूर्णांक pciehp_enable_slot(काष्ठा controller *ctrl)
अणु
	पूर्णांक ret;

	pm_runसमय_get_sync(&ctrl->pcie->port->dev);
	ret = __pciehp_enable_slot(ctrl);
	अगर (ret && ATTN_BUTTN(ctrl))
		/* may be blinking */
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
				      INDICATOR_NOOP);
	pm_runसमय_put(&ctrl->pcie->port->dev);

	mutex_lock(&ctrl->state_lock);
	ctrl->state = ret ? OFF_STATE : ON_STATE;
	mutex_unlock(&ctrl->state_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __pciehp_disable_slot(काष्ठा controller *ctrl, bool safe_removal)
अणु
	u8 माला_लोtatus = 0;

	अगर (POWER_CTRL(ctrl)) अणु
		pciehp_get_घातer_status(ctrl, &माला_लोtatus);
		अगर (!माला_लोtatus) अणु
			ctrl_info(ctrl, "Slot(%s): Already disabled\n",
				  slot_name(ctrl));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	हटाओ_board(ctrl, safe_removal);
	वापस 0;
पूर्ण

अटल पूर्णांक pciehp_disable_slot(काष्ठा controller *ctrl, bool safe_removal)
अणु
	पूर्णांक ret;

	pm_runसमय_get_sync(&ctrl->pcie->port->dev);
	ret = __pciehp_disable_slot(ctrl, safe_removal);
	pm_runसमय_put(&ctrl->pcie->port->dev);

	mutex_lock(&ctrl->state_lock);
	ctrl->state = OFF_STATE;
	mutex_unlock(&ctrl->state_lock);

	वापस ret;
पूर्ण

पूर्णांक pciehp_sysfs_enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);

	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल BLINKINGON_STATE:
	हाल OFF_STATE:
		mutex_unlock(&ctrl->state_lock);
		/*
		 * The IRQ thपढ़ो becomes a no-op अगर the user pulls out the
		 * card beक्रमe the thपढ़ो wakes up, so initialize to -ENODEV.
		 */
		ctrl->request_result = -ENODEV;
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);
		रुको_event(ctrl->requester,
			   !atomic_पढ़ो(&ctrl->pending_events) &&
			   !ctrl->ist_running);
		वापस ctrl->request_result;
	हाल POWERON_STATE:
		ctrl_info(ctrl, "Slot(%s): Already in powering on state\n",
			  slot_name(ctrl));
		अवरोध;
	हाल BLINKINGOFF_STATE:
	हाल ON_STATE:
	हाल POWEROFF_STATE:
		ctrl_info(ctrl, "Slot(%s): Already enabled\n",
			  slot_name(ctrl));
		अवरोध;
	शेष:
		ctrl_err(ctrl, "Slot(%s): Invalid state %#x\n",
			 slot_name(ctrl), ctrl->state);
		अवरोध;
	पूर्ण
	mutex_unlock(&ctrl->state_lock);

	वापस -ENODEV;
पूर्ण

पूर्णांक pciehp_sysfs_disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);

	mutex_lock(&ctrl->state_lock);
	चयन (ctrl->state) अणु
	हाल BLINKINGOFF_STATE:
	हाल ON_STATE:
		mutex_unlock(&ctrl->state_lock);
		pciehp_request(ctrl, DISABLE_SLOT);
		रुको_event(ctrl->requester,
			   !atomic_पढ़ो(&ctrl->pending_events) &&
			   !ctrl->ist_running);
		वापस ctrl->request_result;
	हाल POWEROFF_STATE:
		ctrl_info(ctrl, "Slot(%s): Already in powering off state\n",
			  slot_name(ctrl));
		अवरोध;
	हाल BLINKINGON_STATE:
	हाल OFF_STATE:
	हाल POWERON_STATE:
		ctrl_info(ctrl, "Slot(%s): Already disabled\n",
			  slot_name(ctrl));
		अवरोध;
	शेष:
		ctrl_err(ctrl, "Slot(%s): Invalid state %#x\n",
			 slot_name(ctrl), ctrl->state);
		अवरोध;
	पूर्ण
	mutex_unlock(&ctrl->state_lock);

	वापस -ENODEV;
पूर्ण
