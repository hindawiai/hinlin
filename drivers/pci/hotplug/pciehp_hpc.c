<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Express PCI Hot Plug Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2003-2004 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>,<kristen.c.accardi@पूर्णांकel.com>
 */

#घोषणा dev_fmt(fmt) "pciehp: " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश "../pci.h"
#समावेश "pciehp.h"

अटल स्थिर काष्ठा dmi_प्रणाली_id inband_presence_disabled_dmi_table[] = अणु
	/*
	 * Match all Dell प्रणालीs, as some Dell प्रणालीs have inband
	 * presence disabled on NVMe slots (but करोn't support the bit to
	 * report it). Setting inband presence disabled should have no
	 * negative effect, except on broken hotplug slots that never
	 * निश्चित presence detect--and those will still work, they will
	 * just have a bit of extra delay beक्रमe being probed.
	 */
	अणु
		.ident = "Dell System",
		.matches = अणु
			DMI_MATCH(DMI_OEM_STRING, "Dell System"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत काष्ठा pci_dev *ctrl_dev(काष्ठा controller *ctrl)
अणु
	वापस ctrl->pcie->port;
पूर्ण

अटल irqवापस_t pciehp_isr(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t pciehp_ist(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक pciehp_poll(व्योम *data);

अटल अंतरभूत पूर्णांक pciehp_request_irq(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval, irq = ctrl->pcie->irq;

	अगर (pciehp_poll_mode) अणु
		ctrl->poll_thपढ़ो = kthपढ़ो_run(&pciehp_poll, ctrl,
						"pciehp_poll-%s",
						slot_name(ctrl));
		वापस PTR_ERR_OR_ZERO(ctrl->poll_thपढ़ो);
	पूर्ण

	/* Installs the पूर्णांकerrupt handler */
	retval = request_thपढ़ोed_irq(irq, pciehp_isr, pciehp_ist,
				      IRQF_SHARED, "pciehp", ctrl);
	अगर (retval)
		ctrl_err(ctrl, "Cannot get irq %d for the hotplug controller\n",
			 irq);
	वापस retval;
पूर्ण

अटल अंतरभूत व्योम pciehp_मुक्त_irq(काष्ठा controller *ctrl)
अणु
	अगर (pciehp_poll_mode)
		kthपढ़ो_stop(ctrl->poll_thपढ़ो);
	अन्यथा
		मुक्त_irq(ctrl->pcie->irq, ctrl);
पूर्ण

अटल पूर्णांक pcie_poll_cmd(काष्ठा controller *ctrl, पूर्णांक समयout)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_status;

	करो अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
		अगर (slot_status == (u16) ~0) अणु
			ctrl_info(ctrl, "%s: no response from device\n",
				  __func__);
			वापस 0;
		पूर्ण

		अगर (slot_status & PCI_EXP_SLTSTA_CC) अणु
			pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA,
						   PCI_EXP_SLTSTA_CC);
			वापस 1;
		पूर्ण
		msleep(10);
		समयout -= 10;
	पूर्ण जबतक (समयout >= 0);
	वापस 0;	/* समयout */
पूर्ण

अटल व्योम pcie_रुको_cmd(काष्ठा controller *ctrl)
अणु
	अचिन्हित पूर्णांक msecs = pciehp_poll_mode ? 2500 : 1000;
	अचिन्हित दीर्घ duration = msecs_to_jअगरfies(msecs);
	अचिन्हित दीर्घ cmd_समयout = ctrl->cmd_started + duration;
	अचिन्हित दीर्घ now, समयout;
	पूर्णांक rc;

	/*
	 * If the controller करोes not generate notअगरications क्रम command
	 * completions, we never need to रुको between ग_लिखोs.
	 */
	अगर (NO_CMD_CMPL(ctrl))
		वापस;

	अगर (!ctrl->cmd_busy)
		वापस;

	/*
	 * Even अगर the command has alपढ़ोy समयd out, we want to call
	 * pcie_poll_cmd() so it can clear PCI_EXP_SLTSTA_CC.
	 */
	now = jअगरfies;
	अगर (समय_beक्रमe_eq(cmd_समयout, now))
		समयout = 1;
	अन्यथा
		समयout = cmd_समयout - now;

	अगर (ctrl->slot_ctrl & PCI_EXP_SLTCTL_HPIE &&
	    ctrl->slot_ctrl & PCI_EXP_SLTCTL_CCIE)
		rc = रुको_event_समयout(ctrl->queue, !ctrl->cmd_busy, समयout);
	अन्यथा
		rc = pcie_poll_cmd(ctrl, jअगरfies_to_msecs(समयout));

	अगर (!rc)
		ctrl_info(ctrl, "Timeout on hotplug command %#06x (issued %u msec ago)\n",
			  ctrl->slot_ctrl,
			  jअगरfies_to_msecs(jअगरfies - ctrl->cmd_started));
पूर्ण

#घोषणा CC_ERRATUM_MASK		(PCI_EXP_SLTCTL_PCC |	\
				 PCI_EXP_SLTCTL_PIC |	\
				 PCI_EXP_SLTCTL_AIC |	\
				 PCI_EXP_SLTCTL_EIC)

अटल व्योम pcie_करो_ग_लिखो_cmd(काष्ठा controller *ctrl, u16 cmd,
			      u16 mask, bool रुको)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_ctrl_orig, slot_ctrl;

	mutex_lock(&ctrl->ctrl_lock);

	/*
	 * Always रुको क्रम any previous command that might still be in progress
	 */
	pcie_रुको_cmd(ctrl);

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &slot_ctrl);
	अगर (slot_ctrl == (u16) ~0) अणु
		ctrl_info(ctrl, "%s: no response from device\n", __func__);
		जाओ out;
	पूर्ण

	slot_ctrl_orig = slot_ctrl;
	slot_ctrl &= ~mask;
	slot_ctrl |= (cmd & mask);
	ctrl->cmd_busy = 1;
	smp_mb();
	ctrl->slot_ctrl = slot_ctrl;
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTCTL, slot_ctrl);
	ctrl->cmd_started = jअगरfies;

	/*
	 * Controllers with the Intel CF118 and similar errata advertise
	 * Command Completed support, but they only set Command Completed
	 * अगर we change the "Control" bits क्रम घातer, घातer indicator,
	 * attention indicator, or पूर्णांकerlock.  If we only change the
	 * "Enable" bits, they never set the Command Completed bit.
	 */
	अगर (pdev->broken_cmd_compl &&
	    (slot_ctrl_orig & CC_ERRATUM_MASK) == (slot_ctrl & CC_ERRATUM_MASK))
		ctrl->cmd_busy = 0;

	/*
	 * Optionally रुको क्रम the hardware to be पढ़ोy क्रम a new command,
	 * indicating completion of the above issued command.
	 */
	अगर (रुको)
		pcie_रुको_cmd(ctrl);

out:
	mutex_unlock(&ctrl->ctrl_lock);
पूर्ण

/**
 * pcie_ग_लिखो_cmd - Issue controller command
 * @ctrl: controller to which the command is issued
 * @cmd:  command value written to slot control रेजिस्टर
 * @mask: biपंचांगask of slot control रेजिस्टर to be modअगरied
 */
अटल व्योम pcie_ग_लिखो_cmd(काष्ठा controller *ctrl, u16 cmd, u16 mask)
अणु
	pcie_करो_ग_लिखो_cmd(ctrl, cmd, mask, true);
पूर्ण

/* Same as above without रुकोing क्रम the hardware to latch */
अटल व्योम pcie_ग_लिखो_cmd_noरुको(काष्ठा controller *ctrl, u16 cmd, u16 mask)
अणु
	pcie_करो_ग_लिखो_cmd(ctrl, cmd, mask, false);
पूर्ण

/**
 * pciehp_check_link_active() - Is the link active
 * @ctrl: PCIe hotplug controller
 *
 * Check whether the करोwnstream link is currently active. Note it is
 * possible that the card is हटाओd immediately after this so the
 * caller may need to take it पूर्णांकo account.
 *
 * If the hotplug controller itself is not available anymore वापसs
 * %-ENODEV.
 */
पूर्णांक pciehp_check_link_active(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 lnk_status;
	पूर्णांक ret;

	ret = pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKSTA, &lnk_status);
	अगर (ret == PCIBIOS_DEVICE_NOT_FOUND || lnk_status == (u16)~0)
		वापस -ENODEV;

	ret = !!(lnk_status & PCI_EXP_LNKSTA_DLLLA);
	ctrl_dbg(ctrl, "%s: lnk_status = %x\n", __func__, lnk_status);

	वापस ret;
पूर्ण

अटल bool pci_bus_check_dev(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	u32 l;
	पूर्णांक count = 0;
	पूर्णांक delay = 1000, step = 20;
	bool found = false;

	करो अणु
		found = pci_bus_पढ़ो_dev_venकरोr_id(bus, devfn, &l, 0);
		count++;

		अगर (found)
			अवरोध;

		msleep(step);
		delay -= step;
	पूर्ण जबतक (delay > 0);

	अगर (count > 1)
		pr_debug("pci %04x:%02x:%02x.%d id reading try %d times with interval %d ms to get %08x\n",
			pci_करोमुख्य_nr(bus), bus->number, PCI_SLOT(devfn),
			PCI_FUNC(devfn), count, step, l);

	वापस found;
पूर्ण

अटल व्योम pcie_रुको_क्रम_presence(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक समयout = 1250;
	u16 slot_status;

	करो अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
		अगर (slot_status & PCI_EXP_SLTSTA_PDS)
			वापस;
		msleep(10);
		समयout -= 10;
	पूर्ण जबतक (समयout > 0);
पूर्ण

पूर्णांक pciehp_check_link_status(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	bool found;
	u16 lnk_status;

	अगर (!pcie_रुको_क्रम_link(pdev, true)) अणु
		ctrl_info(ctrl, "Slot(%s): No link\n", slot_name(ctrl));
		वापस -1;
	पूर्ण

	अगर (ctrl->inband_presence_disabled)
		pcie_रुको_क्रम_presence(pdev);

	found = pci_bus_check_dev(ctrl->pcie->port->subordinate,
					PCI_DEVFN(0, 0));

	/* ignore link or presence changes up to this poपूर्णांक */
	अगर (found)
		atomic_and(~(PCI_EXP_SLTSTA_DLLSC | PCI_EXP_SLTSTA_PDC),
			   &ctrl->pending_events);

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKSTA, &lnk_status);
	ctrl_dbg(ctrl, "%s: lnk_status = %x\n", __func__, lnk_status);
	अगर ((lnk_status & PCI_EXP_LNKSTA_LT) ||
	    !(lnk_status & PCI_EXP_LNKSTA_NLW)) अणु
		ctrl_info(ctrl, "Slot(%s): Cannot train link: status %#06x\n",
			  slot_name(ctrl), lnk_status);
		वापस -1;
	पूर्ण

	pcie_update_link_speed(ctrl->pcie->port->subordinate, lnk_status);

	अगर (!found) अणु
		ctrl_info(ctrl, "Slot(%s): No device found\n",
			  slot_name(ctrl));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __pciehp_link_set(काष्ठा controller *ctrl, bool enable)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 lnk_ctrl;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &lnk_ctrl);

	अगर (enable)
		lnk_ctrl &= ~PCI_EXP_LNKCTL_LD;
	अन्यथा
		lnk_ctrl |= PCI_EXP_LNKCTL_LD;

	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_LNKCTL, lnk_ctrl);
	ctrl_dbg(ctrl, "%s: lnk_ctrl = %x\n", __func__, lnk_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक pciehp_link_enable(काष्ठा controller *ctrl)
अणु
	वापस __pciehp_link_set(ctrl, true);
पूर्ण

पूर्णांक pciehp_get_raw_indicator_status(काष्ठा hotplug_slot *hotplug_slot,
				    u8 *status)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_ctrl;

	pci_config_pm_runसमय_get(pdev);
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &slot_ctrl);
	pci_config_pm_runसमय_put(pdev);
	*status = (slot_ctrl & (PCI_EXP_SLTCTL_AIC | PCI_EXP_SLTCTL_PIC)) >> 6;
	वापस 0;
पूर्ण

पूर्णांक pciehp_get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *status)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_ctrl;

	pci_config_pm_runसमय_get(pdev);
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &slot_ctrl);
	pci_config_pm_runसमय_put(pdev);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x, value read %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, slot_ctrl);

	चयन (slot_ctrl & PCI_EXP_SLTCTL_AIC) अणु
	हाल PCI_EXP_SLTCTL_ATTN_IND_ON:
		*status = 1;	/* On */
		अवरोध;
	हाल PCI_EXP_SLTCTL_ATTN_IND_BLINK:
		*status = 2;	/* Blink */
		अवरोध;
	हाल PCI_EXP_SLTCTL_ATTN_IND_OFF:
		*status = 0;	/* Off */
		अवरोध;
	शेष:
		*status = 0xFF;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम pciehp_get_घातer_status(काष्ठा controller *ctrl, u8 *status)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_ctrl;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &slot_ctrl);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x value read %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, slot_ctrl);

	चयन (slot_ctrl & PCI_EXP_SLTCTL_PCC) अणु
	हाल PCI_EXP_SLTCTL_PWR_ON:
		*status = 1;	/* On */
		अवरोध;
	हाल PCI_EXP_SLTCTL_PWR_OFF:
		*status = 0;	/* Off */
		अवरोध;
	शेष:
		*status = 0xFF;
		अवरोध;
	पूर्ण
पूर्ण

व्योम pciehp_get_latch_status(काष्ठा controller *ctrl, u8 *status)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_status;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
	*status = !!(slot_status & PCI_EXP_SLTSTA_MRLSS);
पूर्ण

/**
 * pciehp_card_present() - Is the card present
 * @ctrl: PCIe hotplug controller
 *
 * Function checks whether the card is currently present in the slot and
 * in that हाल वापसs true. Note it is possible that the card is
 * हटाओd immediately after the check so the caller may need to take
 * this पूर्णांकo account.
 *
 * It the hotplug controller itself is not available anymore वापसs
 * %-ENODEV.
 */
पूर्णांक pciehp_card_present(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_status;
	पूर्णांक ret;

	ret = pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
	अगर (ret == PCIBIOS_DEVICE_NOT_FOUND || slot_status == (u16)~0)
		वापस -ENODEV;

	वापस !!(slot_status & PCI_EXP_SLTSTA_PDS);
पूर्ण

/**
 * pciehp_card_present_or_link_active() - whether given slot is occupied
 * @ctrl: PCIe hotplug controller
 *
 * Unlike pciehp_card_present(), which determines presence solely from the
 * Presence Detect State bit, this helper also वापसs true अगर the Link Active
 * bit is set.  This is a concession to broken hotplug ports which hardwire
 * Presence Detect State to zero, such as Wilocity's [1ae9:0200].
 *
 * Returns: %1 अगर the slot is occupied and %0 अगर it is not. If the hotplug
 *	    port is not present anymore वापसs %-ENODEV.
 */
पूर्णांक pciehp_card_present_or_link_active(काष्ठा controller *ctrl)
अणु
	पूर्णांक ret;

	ret = pciehp_card_present(ctrl);
	अगर (ret)
		वापस ret;

	वापस pciehp_check_link_active(ctrl);
पूर्ण

पूर्णांक pciehp_query_घातer_fault(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_status;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
	वापस !!(slot_status & PCI_EXP_SLTSTA_PFD);
पूर्ण

पूर्णांक pciehp_set_raw_indicator_status(काष्ठा hotplug_slot *hotplug_slot,
				    u8 status)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);

	pci_config_pm_runसमय_get(pdev);
	pcie_ग_लिखो_cmd_noरुको(ctrl, status << 6,
			      PCI_EXP_SLTCTL_AIC | PCI_EXP_SLTCTL_PIC);
	pci_config_pm_runसमय_put(pdev);
	वापस 0;
पूर्ण

/**
 * pciehp_set_indicators() - set attention indicator, घातer indicator, or both
 * @ctrl: PCIe hotplug controller
 * @pwr: one of:
 *	PCI_EXP_SLTCTL_PWR_IND_ON
 *	PCI_EXP_SLTCTL_PWR_IND_BLINK
 *	PCI_EXP_SLTCTL_PWR_IND_OFF
 * @attn: one of:
 *	PCI_EXP_SLTCTL_ATTN_IND_ON
 *	PCI_EXP_SLTCTL_ATTN_IND_BLINK
 *	PCI_EXP_SLTCTL_ATTN_IND_OFF
 *
 * Either @pwr or @attn can also be INDICATOR_NOOP to leave that indicator
 * unchanged.
 */
व्योम pciehp_set_indicators(काष्ठा controller *ctrl, पूर्णांक pwr, पूर्णांक attn)
अणु
	u16 cmd = 0, mask = 0;

	अगर (PWR_LED(ctrl) && pwr != INDICATOR_NOOP) अणु
		cmd |= (pwr & PCI_EXP_SLTCTL_PIC);
		mask |= PCI_EXP_SLTCTL_PIC;
	पूर्ण

	अगर (ATTN_LED(ctrl) && attn != INDICATOR_NOOP) अणु
		cmd |= (attn & PCI_EXP_SLTCTL_AIC);
		mask |= PCI_EXP_SLTCTL_AIC;
	पूर्ण

	अगर (cmd) अणु
		pcie_ग_लिखो_cmd_noरुको(ctrl, cmd, mask);
		ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
			 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, cmd);
	पूर्ण
पूर्ण

पूर्णांक pciehp_घातer_on_slot(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 slot_status;
	पूर्णांक retval;

	/* Clear घातer-fault bit from previous घातer failures */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &slot_status);
	अगर (slot_status & PCI_EXP_SLTSTA_PFD)
		pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA,
					   PCI_EXP_SLTSTA_PFD);
	ctrl->घातer_fault_detected = 0;

	pcie_ग_लिखो_cmd(ctrl, PCI_EXP_SLTCTL_PWR_ON, PCI_EXP_SLTCTL_PCC);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL,
		 PCI_EXP_SLTCTL_PWR_ON);

	retval = pciehp_link_enable(ctrl);
	अगर (retval)
		ctrl_err(ctrl, "%s: Can not enable the link!\n", __func__);

	वापस retval;
पूर्ण

व्योम pciehp_घातer_off_slot(काष्ठा controller *ctrl)
अणु
	pcie_ग_लिखो_cmd(ctrl, PCI_EXP_SLTCTL_PWR_OFF, PCI_EXP_SLTCTL_PCC);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL,
		 PCI_EXP_SLTCTL_PWR_OFF);
पूर्ण

अटल irqवापस_t pciehp_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा controller *ctrl = (काष्ठा controller *)dev_id;
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	काष्ठा device *parent = pdev->dev.parent;
	u16 status, events = 0;

	/*
	 * Interrupts only occur in D3hot or shallower and only अगर enabled
	 * in the Slot Control रेजिस्टर (PCIe r4.0, sec 6.7.3.4).
	 */
	अगर (pdev->current_state == PCI_D3cold ||
	    (!(ctrl->slot_ctrl & PCI_EXP_SLTCTL_HPIE) && !pciehp_poll_mode))
		वापस IRQ_NONE;

	/*
	 * Keep the port accessible by holding a runसमय PM ref on its parent.
	 * Defer resume of the parent to the IRQ thपढ़ो अगर it's suspended.
	 * Mask the पूर्णांकerrupt until then.
	 */
	अगर (parent) अणु
		pm_runसमय_get_noresume(parent);
		अगर (!pm_runसमय_active(parent)) अणु
			pm_runसमय_put(parent);
			disable_irq_nosync(irq);
			atomic_or(RERUN_ISR, &ctrl->pending_events);
			वापस IRQ_WAKE_THREAD;
		पूर्ण
	पूर्ण

पढ़ो_status:
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &status);
	अगर (status == (u16) ~0) अणु
		ctrl_info(ctrl, "%s: no response from device\n", __func__);
		अगर (parent)
			pm_runसमय_put(parent);
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * Slot Status contains plain status bits as well as event
	 * notअगरication bits; right now we only want the event bits.
	 */
	status &= PCI_EXP_SLTSTA_ABP | PCI_EXP_SLTSTA_PFD |
		  PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_CC |
		  PCI_EXP_SLTSTA_DLLSC;

	/*
	 * If we've already reported a power fault, don't report it again
	 * until we've करोne something to handle it.
	 */
	अगर (ctrl->घातer_fault_detected)
		status &= ~PCI_EXP_SLTSTA_PFD;

	events |= status;
	अगर (!events) अणु
		अगर (parent)
			pm_runसमय_put(parent);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status) अणु
		pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA, events);

		/*
		 * In MSI mode, all event bits must be zero beक्रमe the port
		 * will send a new पूर्णांकerrupt (PCIe Base Spec r5.0 sec 6.7.3.4).
		 * So re-पढ़ो the Slot Status रेजिस्टर in हाल a bit was set
		 * between पढ़ो and ग_लिखो.
		 */
		अगर (pci_dev_msi_enabled(pdev) && !pciehp_poll_mode)
			जाओ पढ़ो_status;
	पूर्ण

	ctrl_dbg(ctrl, "pending interrupts %#06x from Slot Status\n", events);
	अगर (parent)
		pm_runसमय_put(parent);

	/*
	 * Command Completed notअगरications are not deferred to the
	 * IRQ thपढ़ो because it may be रुकोing क्रम their arrival.
	 */
	अगर (events & PCI_EXP_SLTSTA_CC) अणु
		ctrl->cmd_busy = 0;
		smp_mb();
		wake_up(&ctrl->queue);

		अगर (events == PCI_EXP_SLTSTA_CC)
			वापस IRQ_HANDLED;

		events &= ~PCI_EXP_SLTSTA_CC;
	पूर्ण

	अगर (pdev->ignore_hotplug) अणु
		ctrl_dbg(ctrl, "ignoring hotplug event %#06x\n", events);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Save pending events क्रम consumption by IRQ thपढ़ो. */
	atomic_or(events, &ctrl->pending_events);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t pciehp_ist(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा controller *ctrl = (काष्ठा controller *)dev_id;
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	irqवापस_t ret;
	u32 events;

	ctrl->ist_running = true;
	pci_config_pm_runसमय_get(pdev);

	/* rerun pciehp_isr() अगर the port was inaccessible on पूर्णांकerrupt */
	अगर (atomic_fetch_and(~RERUN_ISR, &ctrl->pending_events) & RERUN_ISR) अणु
		ret = pciehp_isr(irq, dev_id);
		enable_irq(irq);
		अगर (ret != IRQ_WAKE_THREAD)
			जाओ out;
	पूर्ण

	synchronize_hardirq(irq);
	events = atomic_xchg(&ctrl->pending_events, 0);
	अगर (!events) अणु
		ret = IRQ_NONE;
		जाओ out;
	पूर्ण

	/* Check Attention Button Pressed */
	अगर (events & PCI_EXP_SLTSTA_ABP) अणु
		ctrl_info(ctrl, "Slot(%s): Attention button pressed\n",
			  slot_name(ctrl));
		pciehp_handle_button_press(ctrl);
	पूर्ण

	/* Check Power Fault Detected */
	अगर ((events & PCI_EXP_SLTSTA_PFD) && !ctrl->घातer_fault_detected) अणु
		ctrl->घातer_fault_detected = 1;
		ctrl_err(ctrl, "Slot(%s): Power fault\n", slot_name(ctrl));
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
				      PCI_EXP_SLTCTL_ATTN_IND_ON);
	पूर्ण

	/*
	 * Disable requests have higher priority than Presence Detect Changed
	 * or Data Link Layer State Changed events.
	 */
	करोwn_पढ़ो(&ctrl->reset_lock);
	अगर (events & DISABLE_SLOT)
		pciehp_handle_disable_request(ctrl);
	अन्यथा अगर (events & (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC))
		pciehp_handle_presence_or_link_change(ctrl, events);
	up_पढ़ो(&ctrl->reset_lock);

	ret = IRQ_HANDLED;
out:
	pci_config_pm_runसमय_put(pdev);
	ctrl->ist_running = false;
	wake_up(&ctrl->requester);
	वापस ret;
पूर्ण

अटल पूर्णांक pciehp_poll(व्योम *data)
अणु
	काष्ठा controller *ctrl = data;

	schedule_समयout_idle(10 * HZ); /* start with 10 sec delay */

	जबतक (!kthपढ़ो_should_stop()) अणु
		/* poll क्रम पूर्णांकerrupt events or user requests */
		जबतक (pciehp_isr(IRQ_NOTCONNECTED, ctrl) == IRQ_WAKE_THREAD ||
		       atomic_पढ़ो(&ctrl->pending_events))
			pciehp_ist(IRQ_NOTCONNECTED, ctrl);

		अगर (pciehp_poll_समय <= 0 || pciehp_poll_समय > 60)
			pciehp_poll_समय = 2; /* clamp to sane value */

		schedule_समयout_idle(pciehp_poll_समय * HZ);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcie_enable_notअगरication(काष्ठा controller *ctrl)
अणु
	u16 cmd, mask;

	/*
	 * TBD: Power fault detected software notअगरication support.
	 *
	 * Power fault detected software notअगरication is not enabled
	 * now, because it caused घातer fault detected पूर्णांकerrupt storm
	 * on some machines. On those machines, घातer fault detected
	 * bit in the slot status रेजिस्टर was set again immediately
	 * when it is cleared in the पूर्णांकerrupt service routine, and
	 * next घातer fault detected पूर्णांकerrupt was notअगरied again.
	 */

	/*
	 * Always enable link events: thus link-up and link-करोwn shall
	 * always be treated as hotplug and unplug respectively. Enable
	 * presence detect only अगर Attention Button is not present.
	 */
	cmd = PCI_EXP_SLTCTL_DLLSCE;
	अगर (ATTN_BUTTN(ctrl))
		cmd |= PCI_EXP_SLTCTL_ABPE;
	अन्यथा
		cmd |= PCI_EXP_SLTCTL_PDCE;
	अगर (!pciehp_poll_mode)
		cmd |= PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE;

	mask = (PCI_EXP_SLTCTL_PDCE | PCI_EXP_SLTCTL_ABPE |
		PCI_EXP_SLTCTL_PFDE |
		PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE |
		PCI_EXP_SLTCTL_DLLSCE);

	pcie_ग_लिखो_cmd_noरुको(ctrl, cmd, mask);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, cmd);
पूर्ण

अटल व्योम pcie_disable_notअगरication(काष्ठा controller *ctrl)
अणु
	u16 mask;

	mask = (PCI_EXP_SLTCTL_PDCE | PCI_EXP_SLTCTL_ABPE |
		PCI_EXP_SLTCTL_MRLSCE | PCI_EXP_SLTCTL_PFDE |
		PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE |
		PCI_EXP_SLTCTL_DLLSCE);
	pcie_ग_लिखो_cmd(ctrl, 0, mask);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, 0);
पूर्ण

व्योम pcie_clear_hotplug_events(काष्ठा controller *ctrl)
अणु
	pcie_capability_ग_लिखो_word(ctrl_dev(ctrl), PCI_EXP_SLTSTA,
				   PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
पूर्ण

व्योम pcie_enable_पूर्णांकerrupt(काष्ठा controller *ctrl)
अणु
	u16 mask;

	mask = PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_DLLSCE;
	pcie_ग_लिखो_cmd(ctrl, mask, mask);
पूर्ण

व्योम pcie_disable_पूर्णांकerrupt(काष्ठा controller *ctrl)
अणु
	u16 mask;

	/*
	 * Mask hot-plug पूर्णांकerrupt to prevent it triggering immediately
	 * when the link goes inactive (we still get PME when any of the
	 * enabled events is detected). Same goes with Link Layer State
	 * changed event which generates PME immediately when the link goes
	 * inactive so mask it as well.
	 */
	mask = PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_DLLSCE;
	pcie_ग_लिखो_cmd(ctrl, 0, mask);
पूर्ण

/*
 * pciehp has a 1:1 bus:slot relationship so we ultimately want a secondary
 * bus reset of the bridge, but at the same समय we want to ensure that it is
 * not seen as a hot-unplug, followed by the hot-plug of the device. Thus,
 * disable link state notअगरication and presence detection change notअगरication
 * momentarily, अगर we see that they could पूर्णांकerfere. Also, clear any spurious
 * events after.
 */
पूर्णांक pciehp_reset_slot(काष्ठा hotplug_slot *hotplug_slot, पूर्णांक probe)
अणु
	काष्ठा controller *ctrl = to_ctrl(hotplug_slot);
	काष्ठा pci_dev *pdev = ctrl_dev(ctrl);
	u16 stat_mask = 0, ctrl_mask = 0;
	पूर्णांक rc;

	अगर (probe)
		वापस 0;

	करोwn_ग_लिखो(&ctrl->reset_lock);

	अगर (!ATTN_BUTTN(ctrl)) अणु
		ctrl_mask |= PCI_EXP_SLTCTL_PDCE;
		stat_mask |= PCI_EXP_SLTSTA_PDC;
	पूर्ण
	ctrl_mask |= PCI_EXP_SLTCTL_DLLSCE;
	stat_mask |= PCI_EXP_SLTSTA_DLLSC;

	pcie_ग_लिखो_cmd(ctrl, 0, ctrl_mask);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, 0);

	rc = pci_bridge_secondary_bus_reset(ctrl->pcie->port);

	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA, stat_mask);
	pcie_ग_लिखो_cmd_noरुको(ctrl, ctrl_mask, ctrl_mask);
	ctrl_dbg(ctrl, "%s: SLOTCTRL %x write cmd %x\n", __func__,
		 pci_pcie_cap(ctrl->pcie->port) + PCI_EXP_SLTCTL, ctrl_mask);

	up_ग_लिखो(&ctrl->reset_lock);
	वापस rc;
पूर्ण

पूर्णांक pcie_init_notअगरication(काष्ठा controller *ctrl)
अणु
	अगर (pciehp_request_irq(ctrl))
		वापस -1;
	pcie_enable_notअगरication(ctrl);
	ctrl->notअगरication_enabled = 1;
	वापस 0;
पूर्ण

व्योम pcie_shutकरोwn_notअगरication(काष्ठा controller *ctrl)
अणु
	अगर (ctrl->notअगरication_enabled) अणु
		pcie_disable_notअगरication(ctrl);
		pciehp_मुक्त_irq(ctrl);
		ctrl->notअगरication_enabled = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dbg_ctrl(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *pdev = ctrl->pcie->port;
	u16 reg16;

	ctrl_dbg(ctrl, "Slot Capabilities      : 0x%08x\n", ctrl->slot_cap);
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &reg16);
	ctrl_dbg(ctrl, "Slot Status            : 0x%04x\n", reg16);
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &reg16);
	ctrl_dbg(ctrl, "Slot Control           : 0x%04x\n", reg16);
पूर्ण

#घोषणा FLAG(x, y)	(((x) & (y)) ? '+' : '-')

काष्ठा controller *pcie_init(काष्ठा pcie_device *dev)
अणु
	काष्ठा controller *ctrl;
	u32 slot_cap, slot_cap2, link_cap;
	u8 घातeron;
	काष्ठा pci_dev *pdev = dev->port;
	काष्ठा pci_bus *subordinate = pdev->subordinate;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस शून्य;

	ctrl->pcie = dev;
	pcie_capability_पढ़ो_dword(pdev, PCI_EXP_SLTCAP, &slot_cap);

	अगर (pdev->hotplug_user_indicators)
		slot_cap &= ~(PCI_EXP_SLTCAP_AIP | PCI_EXP_SLTCAP_PIP);

	/*
	 * We assume no Thunderbolt controllers support Command Complete events,
	 * but some controllers falsely claim they करो.
	 */
	अगर (pdev->is_thunderbolt)
		slot_cap |= PCI_EXP_SLTCAP_NCCS;

	ctrl->slot_cap = slot_cap;
	mutex_init(&ctrl->ctrl_lock);
	mutex_init(&ctrl->state_lock);
	init_rwsem(&ctrl->reset_lock);
	init_रुकोqueue_head(&ctrl->requester);
	init_रुकोqueue_head(&ctrl->queue);
	INIT_DELAYED_WORK(&ctrl->button_work, pciehp_queue_pushbutton_work);
	dbg_ctrl(ctrl);

	करोwn_पढ़ो(&pci_bus_sem);
	ctrl->state = list_empty(&subordinate->devices) ? OFF_STATE : ON_STATE;
	up_पढ़ो(&pci_bus_sem);

	pcie_capability_पढ़ो_dword(pdev, PCI_EXP_SLTCAP2, &slot_cap2);
	अगर (slot_cap2 & PCI_EXP_SLTCAP2_IBPD) अणु
		pcie_ग_लिखो_cmd_noरुको(ctrl, PCI_EXP_SLTCTL_IBPD_DISABLE,
				      PCI_EXP_SLTCTL_IBPD_DISABLE);
		ctrl->inband_presence_disabled = 1;
	पूर्ण

	अगर (dmi_first_match(inband_presence_disabled_dmi_table))
		ctrl->inband_presence_disabled = 1;

	/* Check अगर Data Link Layer Link Active Reporting is implemented */
	pcie_capability_पढ़ो_dword(pdev, PCI_EXP_LNKCAP, &link_cap);

	/* Clear all reमुख्यing event bits in Slot Status रेजिस्टर. */
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA,
		PCI_EXP_SLTSTA_ABP | PCI_EXP_SLTSTA_PFD |
		PCI_EXP_SLTSTA_MRLSC | PCI_EXP_SLTSTA_CC |
		PCI_EXP_SLTSTA_DLLSC | PCI_EXP_SLTSTA_PDC);

	ctrl_info(ctrl, "Slot #%d AttnBtn%c PwrCtrl%c MRL%c AttnInd%c PwrInd%c HotPlug%c Surprise%c Interlock%c NoCompl%c IbPresDis%c LLActRep%c%s\n",
		(slot_cap & PCI_EXP_SLTCAP_PSN) >> 19,
		FLAG(slot_cap, PCI_EXP_SLTCAP_ABP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_PCP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_MRLSP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_AIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_PIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_HPC),
		FLAG(slot_cap, PCI_EXP_SLTCAP_HPS),
		FLAG(slot_cap, PCI_EXP_SLTCAP_EIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_NCCS),
		FLAG(slot_cap2, PCI_EXP_SLTCAP2_IBPD),
		FLAG(link_cap, PCI_EXP_LNKCAP_DLLLARC),
		pdev->broken_cmd_compl ? " (with Cmd Compl erratum)" : "");

	/*
	 * If empty slot's power status is on, turn power off.  The IRQ isn't
	 * requested yet, so aव्योम triggering a notअगरication with this command.
	 */
	अगर (POWER_CTRL(ctrl)) अणु
		pciehp_get_घातer_status(ctrl, &घातeron);
		अगर (!pciehp_card_present_or_link_active(ctrl) && घातeron) अणु
			pcie_disable_notअगरication(ctrl);
			pciehp_घातer_off_slot(ctrl);
		पूर्ण
	पूर्ण

	वापस ctrl;
पूर्ण

व्योम pciehp_release_ctrl(काष्ठा controller *ctrl)
अणु
	cancel_delayed_work_sync(&ctrl->button_work);
	kमुक्त(ctrl);
पूर्ण

अटल व्योम quirk_cmd_compl(काष्ठा pci_dev *pdev)
अणु
	u32 slot_cap;

	अगर (pci_is_pcie(pdev)) अणु
		pcie_capability_पढ़ो_dword(pdev, PCI_EXP_SLTCAP, &slot_cap);
		अगर (slot_cap & PCI_EXP_SLTCAP_HPC &&
		    !(slot_cap & PCI_EXP_SLTCAP_NCCS))
			pdev->broken_cmd_compl = 1;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_cmd_compl);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_QCOM, 0x0400,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_cmd_compl);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_QCOM, 0x0401,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_cmd_compl);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_HXT, 0x0401,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_cmd_compl);
