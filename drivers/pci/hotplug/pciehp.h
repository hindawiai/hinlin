<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
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
#अगर_अघोषित _PCIEHP_H
#घोषणा _PCIEHP_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/workqueue.h>

#समावेश "../pcie/portdrv.h"

बाह्य bool pciehp_poll_mode;
बाह्य पूर्णांक pciehp_poll_समय;

/*
 * Set CONFIG_DYNAMIC_DEBUG=y and boot with 'dyndbg="file pciehp* +p"' to
 * enable debug messages.
 */
#घोषणा ctrl_dbg(ctrl, क्रमmat, arg...)					\
	pci_dbg(ctrl->pcie->port, क्रमmat, ## arg)
#घोषणा ctrl_err(ctrl, क्रमmat, arg...)					\
	pci_err(ctrl->pcie->port, क्रमmat, ## arg)
#घोषणा ctrl_info(ctrl, क्रमmat, arg...)					\
	pci_info(ctrl->pcie->port, क्रमmat, ## arg)
#घोषणा ctrl_warn(ctrl, क्रमmat, arg...)					\
	pci_warn(ctrl->pcie->port, क्रमmat, ## arg)

#घोषणा SLOT_NAME_SIZE 10

/**
 * काष्ठा controller - PCIe hotplug controller
 * @pcie: poपूर्णांकer to the controller's PCIe port service device
 * @slot_cap: cached copy of the Slot Capabilities रेजिस्टर
 * @slot_ctrl: cached copy of the Slot Control रेजिस्टर
 * @ctrl_lock: serializes ग_लिखोs to the Slot Control रेजिस्टर
 * @cmd_started: jअगरfies when the Slot Control रेजिस्टर was last written;
 *	the next ग_लिखो is allowed 1 second later, असलent a Command Completed
 *	पूर्णांकerrupt (PCIe r4.0, sec 6.7.3.2)
 * @cmd_busy: flag set on Slot Control रेजिस्टर ग_लिखो, cleared by IRQ handler
 *	on reception of a Command Completed event
 * @queue: रुको queue to wake up on reception of a Command Completed event,
 *	used क्रम synchronous ग_लिखोs to the Slot Control रेजिस्टर
 * @pending_events: used by the IRQ handler to save events retrieved from the
 *	Slot Status रेजिस्टर क्रम later consumption by the IRQ thपढ़ो
 * @notअगरication_enabled: whether the IRQ was requested successfully
 * @घातer_fault_detected: whether a घातer fault was detected by the hardware
 *	that has not yet been cleared by the user
 * @poll_thपढ़ो: thपढ़ो to poll क्रम slot events अगर no IRQ is available,
 *	enabled with pciehp_poll_mode module parameter
 * @state: current state machine position
 * @state_lock: protects पढ़ोs and ग_लिखोs of @state;
 *	protects scheduling, execution and cancellation of @button_work
 * @button_work: work item to turn the slot on or off after 5 seconds
 *	in response to an Attention Button press
 * @hotplug_slot: काष्ठाure रेजिस्टरed with the PCI hotplug core
 * @reset_lock: prevents access to the Data Link Layer Link Active bit in the
 *	Link Status रेजिस्टर and to the Presence Detect State bit in the Slot
 *	Status रेजिस्टर during a slot reset which may cause them to flap
 * @ist_running: flag to keep user request रुकोing जबतक IRQ thपढ़ो is running
 * @request_result: result of last user request submitted to the IRQ thपढ़ो
 * @requester: रुको queue to wake up on completion of user request,
 *	used क्रम synchronous slot enable/disable request via sysfs
 *
 * PCIe hotplug has a 1:1 relationship between controller and slot, hence
 * unlike other drivers, the two aren't represented by separate काष्ठाures.
 */
काष्ठा controller अणु
	काष्ठा pcie_device *pcie;

	u32 slot_cap;				/* capabilities and quirks */
	अचिन्हित पूर्णांक inband_presence_disabled:1;

	u16 slot_ctrl;				/* control रेजिस्टर access */
	काष्ठा mutex ctrl_lock;
	अचिन्हित दीर्घ cmd_started;
	अचिन्हित पूर्णांक cmd_busy:1;
	रुको_queue_head_t queue;

	atomic_t pending_events;		/* event handling */
	अचिन्हित पूर्णांक notअगरication_enabled:1;
	अचिन्हित पूर्णांक घातer_fault_detected;
	काष्ठा task_काष्ठा *poll_thपढ़ो;

	u8 state;				/* state machine */
	काष्ठा mutex state_lock;
	काष्ठा delayed_work button_work;

	काष्ठा hotplug_slot hotplug_slot;	/* hotplug core पूर्णांकerface */
	काष्ठा rw_semaphore reset_lock;
	अचिन्हित पूर्णांक ist_running;
	पूर्णांक request_result;
	रुको_queue_head_t requester;
पूर्ण;

/**
 * DOC: Slot state
 *
 * @OFF_STATE: slot is घातered off, no subordinate devices are क्रमागतerated
 * @BLINKINGON_STATE: slot will be घातered on after the 5 second delay,
 *	Power Indicator is blinking
 * @BLINKINGOFF_STATE: slot will be घातered off after the 5 second delay,
 *	Power Indicator is blinking
 * @POWERON_STATE: slot is currently घातering on
 * @POWEROFF_STATE: slot is currently घातering off
 * @ON_STATE: slot is घातered on, subordinate devices have been क्रमागतerated
 */
#घोषणा OFF_STATE			0
#घोषणा BLINKINGON_STATE		1
#घोषणा BLINKINGOFF_STATE		2
#घोषणा POWERON_STATE			3
#घोषणा POWEROFF_STATE			4
#घोषणा ON_STATE			5

/**
 * DOC: Flags to request an action from the IRQ thपढ़ो
 *
 * These are stored together with events पढ़ो from the Slot Status रेजिस्टर,
 * hence must be greater than its 16-bit width.
 *
 * %DISABLE_SLOT: Disable the slot in response to a user request via sysfs or
 *	an Attention Button press after the 5 second delay
 * %RERUN_ISR: Used by the IRQ handler to inक्रमm the IRQ thपढ़ो that the
 *	hotplug port was inaccessible when the पूर्णांकerrupt occurred, requiring
 *	that the IRQ handler is rerun by the IRQ thपढ़ो after it has made the
 *	hotplug port accessible by runसमय resuming its parents to D0
 */
#घोषणा DISABLE_SLOT		(1 << 16)
#घोषणा RERUN_ISR		(1 << 17)

#घोषणा ATTN_BUTTN(ctrl)	((ctrl)->slot_cap & PCI_EXP_SLTCAP_ABP)
#घोषणा POWER_CTRL(ctrl)	((ctrl)->slot_cap & PCI_EXP_SLTCAP_PCP)
#घोषणा MRL_SENS(ctrl)		((ctrl)->slot_cap & PCI_EXP_SLTCAP_MRLSP)
#घोषणा ATTN_LED(ctrl)		((ctrl)->slot_cap & PCI_EXP_SLTCAP_AIP)
#घोषणा PWR_LED(ctrl)		((ctrl)->slot_cap & PCI_EXP_SLTCAP_PIP)
#घोषणा NO_CMD_CMPL(ctrl)	((ctrl)->slot_cap & PCI_EXP_SLTCAP_NCCS)
#घोषणा PSN(ctrl)		(((ctrl)->slot_cap & PCI_EXP_SLTCAP_PSN) >> 19)

व्योम pciehp_request(काष्ठा controller *ctrl, पूर्णांक action);
व्योम pciehp_handle_button_press(काष्ठा controller *ctrl);
व्योम pciehp_handle_disable_request(काष्ठा controller *ctrl);
व्योम pciehp_handle_presence_or_link_change(काष्ठा controller *ctrl, u32 events);
पूर्णांक pciehp_configure_device(काष्ठा controller *ctrl);
व्योम pciehp_unconfigure_device(काष्ठा controller *ctrl, bool presence);
व्योम pciehp_queue_pushbutton_work(काष्ठा work_काष्ठा *work);
काष्ठा controller *pcie_init(काष्ठा pcie_device *dev);
पूर्णांक pcie_init_notअगरication(काष्ठा controller *ctrl);
व्योम pcie_shutकरोwn_notअगरication(काष्ठा controller *ctrl);
व्योम pcie_clear_hotplug_events(काष्ठा controller *ctrl);
व्योम pcie_enable_पूर्णांकerrupt(काष्ठा controller *ctrl);
व्योम pcie_disable_पूर्णांकerrupt(काष्ठा controller *ctrl);
पूर्णांक pciehp_घातer_on_slot(काष्ठा controller *ctrl);
व्योम pciehp_घातer_off_slot(काष्ठा controller *ctrl);
व्योम pciehp_get_घातer_status(काष्ठा controller *ctrl, u8 *status);

#घोषणा INDICATOR_NOOP -1	/* Leave indicator unchanged */
व्योम pciehp_set_indicators(काष्ठा controller *ctrl, पूर्णांक pwr, पूर्णांक attn);

व्योम pciehp_get_latch_status(काष्ठा controller *ctrl, u8 *status);
पूर्णांक pciehp_query_घातer_fault(काष्ठा controller *ctrl);
पूर्णांक pciehp_card_present(काष्ठा controller *ctrl);
पूर्णांक pciehp_card_present_or_link_active(काष्ठा controller *ctrl);
पूर्णांक pciehp_check_link_status(काष्ठा controller *ctrl);
पूर्णांक pciehp_check_link_active(काष्ठा controller *ctrl);
व्योम pciehp_release_ctrl(काष्ठा controller *ctrl);

पूर्णांक pciehp_sysfs_enable_slot(काष्ठा hotplug_slot *hotplug_slot);
पूर्णांक pciehp_sysfs_disable_slot(काष्ठा hotplug_slot *hotplug_slot);
पूर्णांक pciehp_reset_slot(काष्ठा hotplug_slot *hotplug_slot, पूर्णांक probe);
पूर्णांक pciehp_get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *status);
पूर्णांक pciehp_set_raw_indicator_status(काष्ठा hotplug_slot *h_slot, u8 status);
पूर्णांक pciehp_get_raw_indicator_status(काष्ठा hotplug_slot *h_slot, u8 *status);

अटल अंतरभूत स्थिर अक्षर *slot_name(काष्ठा controller *ctrl)
अणु
	वापस hotplug_slot_name(&ctrl->hotplug_slot);
पूर्ण

अटल अंतरभूत काष्ठा controller *to_ctrl(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा controller, hotplug_slot);
पूर्ण

#पूर्ण_अगर				/* _PCIEHP_H */
