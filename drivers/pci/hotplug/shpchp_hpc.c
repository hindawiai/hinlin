<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Standard PCI Hot Plug Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2003-2004 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>,<kristen.c.accardi@पूर्णांकel.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "shpchp.h"

/* Slot Available Register I field definition */
#घोषणा SLOT_33MHZ		0x0000001f
#घोषणा SLOT_66MHZ_PCIX		0x00001f00
#घोषणा SLOT_100MHZ_PCIX	0x001f0000
#घोषणा SLOT_133MHZ_PCIX	0x1f000000

/* Slot Available Register II field definition */
#घोषणा SLOT_66MHZ		0x0000001f
#घोषणा SLOT_66MHZ_PCIX_266	0x00000f00
#घोषणा SLOT_100MHZ_PCIX_266	0x0000f000
#घोषणा SLOT_133MHZ_PCIX_266	0x000f0000
#घोषणा SLOT_66MHZ_PCIX_533	0x00f00000
#घोषणा SLOT_100MHZ_PCIX_533	0x0f000000
#घोषणा SLOT_133MHZ_PCIX_533	0xf0000000

/* Slot Configuration */
#घोषणा SLOT_NUM		0x0000001F
#घोषणा	FIRST_DEV_NUM		0x00001F00
#घोषणा PSN			0x07FF0000
#घोषणा	UPDOWN			0x20000000
#घोषणा	MRLSENSOR		0x40000000
#घोषणा ATTN_BUTTON		0x80000000

/*
 * Interrupt Locator Register definitions
 */
#घोषणा CMD_INTR_PENDING	(1 << 0)
#घोषणा SLOT_INTR_PENDING(i)	(1 << (i + 1))

/*
 * Controller SERR-INT Register
 */
#घोषणा GLOBAL_INTR_MASK	(1 << 0)
#घोषणा GLOBAL_SERR_MASK	(1 << 1)
#घोषणा COMMAND_INTR_MASK	(1 << 2)
#घोषणा ARBITER_SERR_MASK	(1 << 3)
#घोषणा COMMAND_DETECTED	(1 << 16)
#घोषणा ARBITER_DETECTED	(1 << 17)
#घोषणा SERR_INTR_RSVDZ_MASK	0xfffc0000

/*
 * Logical Slot Register definitions
 */
#घोषणा SLOT_REG(i)		(SLOT1 + (4 * i))

#घोषणा SLOT_STATE_SHIFT	(0)
#घोषणा SLOT_STATE_MASK		(3 << 0)
#घोषणा SLOT_STATE_PWRONLY	(1)
#घोषणा SLOT_STATE_ENABLED	(2)
#घोषणा SLOT_STATE_DISABLED	(3)
#घोषणा PWR_LED_STATE_SHIFT	(2)
#घोषणा PWR_LED_STATE_MASK	(3 << 2)
#घोषणा ATN_LED_STATE_SHIFT	(4)
#घोषणा ATN_LED_STATE_MASK	(3 << 4)
#घोषणा ATN_LED_STATE_ON	(1)
#घोषणा ATN_LED_STATE_BLINK	(2)
#घोषणा ATN_LED_STATE_OFF	(3)
#घोषणा POWER_FAULT		(1 << 6)
#घोषणा ATN_BUTTON		(1 << 7)
#घोषणा MRL_SENSOR		(1 << 8)
#घोषणा MHZ66_CAP		(1 << 9)
#घोषणा PRSNT_SHIFT		(10)
#घोषणा PRSNT_MASK		(3 << 10)
#घोषणा PCIX_CAP_SHIFT		(12)
#घोषणा PCIX_CAP_MASK_PI1	(3 << 12)
#घोषणा PCIX_CAP_MASK_PI2	(7 << 12)
#घोषणा PRSNT_CHANGE_DETECTED	(1 << 16)
#घोषणा ISO_PFAULT_DETECTED	(1 << 17)
#घोषणा BUTTON_PRESS_DETECTED	(1 << 18)
#घोषणा MRL_CHANGE_DETECTED	(1 << 19)
#घोषणा CON_PFAULT_DETECTED	(1 << 20)
#घोषणा PRSNT_CHANGE_INTR_MASK	(1 << 24)
#घोषणा ISO_PFAULT_INTR_MASK	(1 << 25)
#घोषणा BUTTON_PRESS_INTR_MASK	(1 << 26)
#घोषणा MRL_CHANGE_INTR_MASK	(1 << 27)
#घोषणा CON_PFAULT_INTR_MASK	(1 << 28)
#घोषणा MRL_CHANGE_SERR_MASK	(1 << 29)
#घोषणा CON_PFAULT_SERR_MASK	(1 << 30)
#घोषणा SLOT_REG_RSVDZ_MASK	((1 << 15) | (7 << 21))

/*
 * SHPC Command Code definitions
 *
 *     Slot Operation				00h - 3Fh
 *     Set Bus Segment Speed/Mode A		40h - 47h
 *     Power-Only All Slots			48h
 *     Enable All Slots				49h
 *     Set Bus Segment Speed/Mode B (PI=2)	50h - 5Fh
 *     Reserved Command Codes			60h - BFh
 *     Venकरोr Specअगरic Commands			C0h - FFh
 */
#घोषणा SET_SLOT_PWR		0x01	/* Slot Operation */
#घोषणा SET_SLOT_ENABLE		0x02
#घोषणा SET_SLOT_DISABLE	0x03
#घोषणा SET_PWR_ON		0x04
#घोषणा SET_PWR_BLINK		0x08
#घोषणा SET_PWR_OFF		0x0c
#घोषणा SET_ATTN_ON		0x10
#घोषणा SET_ATTN_BLINK		0x20
#घोषणा SET_ATTN_OFF		0x30
#घोषणा SETA_PCI_33MHZ		0x40	/* Set Bus Segment Speed/Mode A */
#घोषणा SETA_PCI_66MHZ		0x41
#घोषणा SETA_PCIX_66MHZ		0x42
#घोषणा SETA_PCIX_100MHZ	0x43
#घोषणा SETA_PCIX_133MHZ	0x44
#घोषणा SETA_RESERVED1		0x45
#घोषणा SETA_RESERVED2		0x46
#घोषणा SETA_RESERVED3		0x47
#घोषणा SET_PWR_ONLY_ALL	0x48	/* Power-Only All Slots */
#घोषणा SET_ENABLE_ALL		0x49	/* Enable All Slots */
#घोषणा	SETB_PCI_33MHZ		0x50	/* Set Bus Segment Speed/Mode B */
#घोषणा SETB_PCI_66MHZ		0x51
#घोषणा SETB_PCIX_66MHZ_PM	0x52
#घोषणा SETB_PCIX_100MHZ_PM	0x53
#घोषणा SETB_PCIX_133MHZ_PM	0x54
#घोषणा SETB_PCIX_66MHZ_EM	0x55
#घोषणा SETB_PCIX_100MHZ_EM	0x56
#घोषणा SETB_PCIX_133MHZ_EM	0x57
#घोषणा SETB_PCIX_66MHZ_266	0x58
#घोषणा SETB_PCIX_100MHZ_266	0x59
#घोषणा SETB_PCIX_133MHZ_266	0x5a
#घोषणा SETB_PCIX_66MHZ_533	0x5b
#घोषणा SETB_PCIX_100MHZ_533	0x5c
#घोषणा SETB_PCIX_133MHZ_533	0x5d
#घोषणा SETB_RESERVED1		0x5e
#घोषणा SETB_RESERVED2		0x5f

/*
 * SHPC controller command error code
 */
#घोषणा SWITCH_OPEN		0x1
#घोषणा INVALID_CMD		0x2
#घोषणा INVALID_SPEED_MODE	0x4

/*
 * For accessing SHPC Working Register Set via PCI Configuration Space
 */
#घोषणा DWORD_SELECT		0x2
#घोषणा DWORD_DATA		0x4

/* Field Offset in Logical Slot Register - byte boundary */
#घोषणा SLOT_EVENT_LATCH	0x2
#घोषणा SLOT_SERR_INT_MASK	0x3

अटल irqवापस_t shpc_isr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम start_पूर्णांक_poll_समयr(काष्ठा controller *ctrl, पूर्णांक sec);
अटल पूर्णांक hpc_check_cmd_status(काष्ठा controller *ctrl);

अटल अंतरभूत u8 shpc_पढ़ोb(काष्ठा controller *ctrl, पूर्णांक reg)
अणु
	वापस पढ़ोb(ctrl->creg + reg);
पूर्ण

अटल अंतरभूत u16 shpc_पढ़ोw(काष्ठा controller *ctrl, पूर्णांक reg)
अणु
	वापस पढ़ोw(ctrl->creg + reg);
पूर्ण

अटल अंतरभूत व्योम shpc_ग_लिखोw(काष्ठा controller *ctrl, पूर्णांक reg, u16 val)
अणु
	ग_लिखोw(val, ctrl->creg + reg);
पूर्ण

अटल अंतरभूत u32 shpc_पढ़ोl(काष्ठा controller *ctrl, पूर्णांक reg)
अणु
	वापस पढ़ोl(ctrl->creg + reg);
पूर्ण

अटल अंतरभूत व्योम shpc_ग_लिखोl(काष्ठा controller *ctrl, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, ctrl->creg + reg);
पूर्ण

अटल अंतरभूत पूर्णांक shpc_indirect_पढ़ो(काष्ठा controller *ctrl, पूर्णांक index,
				     u32 *value)
अणु
	पूर्णांक rc;
	u32 cap_offset = ctrl->cap_offset;
	काष्ठा pci_dev *pdev = ctrl->pci_dev;

	rc = pci_ग_लिखो_config_byte(pdev, cap_offset + DWORD_SELECT, index);
	अगर (rc)
		वापस rc;
	वापस pci_पढ़ो_config_dword(pdev, cap_offset + DWORD_DATA, value);
पूर्ण

/*
 * This is the पूर्णांकerrupt polling समयout function.
 */
अटल व्योम पूर्णांक_poll_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा controller *ctrl = from_समयr(ctrl, t, poll_समयr);

	/* Poll क्रम पूर्णांकerrupt events.  regs == शून्य => polling */
	shpc_isr(0, ctrl);

	अगर (!shpchp_poll_समय)
		shpchp_poll_समय = 2; /* शेष polling पूर्णांकerval is 2 sec */

	start_पूर्णांक_poll_समयr(ctrl, shpchp_poll_समय);
पूर्ण

/*
 * This function starts the पूर्णांकerrupt polling समयr.
 */
अटल व्योम start_पूर्णांक_poll_समयr(काष्ठा controller *ctrl, पूर्णांक sec)
अणु
	/* Clamp to sane value */
	अगर ((sec <= 0) || (sec > 60))
		sec = 2;

	ctrl->poll_समयr.expires = jअगरfies + sec * HZ;
	add_समयr(&ctrl->poll_समयr);
पूर्ण

अटल अंतरभूत पूर्णांक is_ctrl_busy(काष्ठा controller *ctrl)
अणु
	u16 cmd_status = shpc_पढ़ोw(ctrl, CMD_STATUS);
	वापस cmd_status & 0x1;
पूर्ण

/*
 * Returns 1 अगर SHPC finishes executing a command within 1 sec,
 * otherwise वापसs 0.
 */
अटल अंतरभूत पूर्णांक shpc_poll_ctrl_busy(काष्ठा controller *ctrl)
अणु
	पूर्णांक i;

	अगर (!is_ctrl_busy(ctrl))
		वापस 1;

	/* Check every 0.1 sec क्रम a total of 1 sec */
	क्रम (i = 0; i < 10; i++) अणु
		msleep(100);
		अगर (!is_ctrl_busy(ctrl))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक shpc_रुको_cmd(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(1000);
	पूर्णांक rc;

	अगर (shpchp_poll_mode)
		rc = shpc_poll_ctrl_busy(ctrl);
	अन्यथा
		rc = रुको_event_पूर्णांकerruptible_समयout(ctrl->queue,
						!is_ctrl_busy(ctrl), समयout);
	अगर (!rc && is_ctrl_busy(ctrl)) अणु
		retval = -EIO;
		ctrl_err(ctrl, "Command not completed in 1000 msec\n");
	पूर्ण अन्यथा अगर (rc < 0) अणु
		retval = -EINTR;
		ctrl_info(ctrl, "Command was interrupted by a signal\n");
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक shpc_ग_लिखो_cmd(काष्ठा slot *slot, u8 t_slot, u8 cmd)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u16 cmd_status;
	पूर्णांक retval = 0;
	u16 temp_word;

	mutex_lock(&slot->ctrl->cmd_lock);

	अगर (!shpc_poll_ctrl_busy(ctrl)) अणु
		/* After 1 sec and and the controller is still busy */
		ctrl_err(ctrl, "Controller is still busy after 1 sec\n");
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	++t_slot;
	temp_word =  (t_slot << 8) | (cmd & 0xFF);
	ctrl_dbg(ctrl, "%s: t_slot %x cmd %x\n", __func__, t_slot, cmd);

	/* To make sure the Controller Busy bit is 0 beक्रमe we send out the
	 * command.
	 */
	shpc_ग_लिखोw(ctrl, CMD, temp_word);

	/*
	 * Wait क्रम command completion.
	 */
	retval = shpc_रुको_cmd(slot->ctrl);
	अगर (retval)
		जाओ out;

	cmd_status = hpc_check_cmd_status(slot->ctrl);
	अगर (cmd_status) अणु
		ctrl_err(ctrl, "Failed to issued command 0x%x (error code = %d)\n",
			 cmd, cmd_status);
		retval = -EIO;
	पूर्ण
 out:
	mutex_unlock(&slot->ctrl->cmd_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक hpc_check_cmd_status(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval = 0;
	u16 cmd_status = shpc_पढ़ोw(ctrl, CMD_STATUS) & 0x000F;

	चयन (cmd_status >> 1) अणु
	हाल 0:
		retval = 0;
		अवरोध;
	हाल 1:
		retval = SWITCH_OPEN;
		ctrl_err(ctrl, "Switch opened!\n");
		अवरोध;
	हाल 2:
		retval = INVALID_CMD;
		ctrl_err(ctrl, "Invalid HPC command!\n");
		अवरोध;
	हाल 4:
		retval = INVALID_SPEED_MODE;
		ctrl_err(ctrl, "Invalid bus speed/mode!\n");
		अवरोध;
	शेष:
		retval = cmd_status;
	पूर्ण

	वापस retval;
पूर्ण


अटल पूर्णांक hpc_get_attention_status(काष्ठा slot *slot, u8 *status)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));
	u8 state = (slot_reg & ATN_LED_STATE_MASK) >> ATN_LED_STATE_SHIFT;

	चयन (state) अणु
	हाल ATN_LED_STATE_ON:
		*status = 1;	/* On */
		अवरोध;
	हाल ATN_LED_STATE_BLINK:
		*status = 2;	/* Blink */
		अवरोध;
	हाल ATN_LED_STATE_OFF:
		*status = 0;	/* Off */
		अवरोध;
	शेष:
		*status = 0xFF;	/* Reserved */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpc_get_घातer_status(काष्ठा slot *slot, u8 *status)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));
	u8 state = (slot_reg & SLOT_STATE_MASK) >> SLOT_STATE_SHIFT;

	चयन (state) अणु
	हाल SLOT_STATE_PWRONLY:
		*status = 2;	/* Powered only */
		अवरोध;
	हाल SLOT_STATE_ENABLED:
		*status = 1;	/* Enabled */
		अवरोध;
	हाल SLOT_STATE_DISABLED:
		*status = 0;	/* Disabled */
		अवरोध;
	शेष:
		*status = 0xFF;	/* Reserved */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक hpc_get_latch_status(काष्ठा slot *slot, u8 *status)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));

	*status = !!(slot_reg & MRL_SENSOR);	/* 0 -> बंद; 1 -> खोलो */

	वापस 0;
पूर्ण

अटल पूर्णांक hpc_get_adapter_status(काष्ठा slot *slot, u8 *status)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));
	u8 state = (slot_reg & PRSNT_MASK) >> PRSNT_SHIFT;

	*status = (state != 0x3) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hpc_get_prog_पूर्णांक(काष्ठा slot *slot, u8 *prog_पूर्णांक)
अणु
	काष्ठा controller *ctrl = slot->ctrl;

	*prog_पूर्णांक = shpc_पढ़ोb(ctrl, PROG_INTERFACE);

	वापस 0;
पूर्ण

अटल पूर्णांक hpc_get_adapter_speed(काष्ठा slot *slot, क्रमागत pci_bus_speed *value)
अणु
	पूर्णांक retval = 0;
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));
	u8 m66_cap  = !!(slot_reg & MHZ66_CAP);
	u8 pi, pcix_cap;

	retval = hpc_get_prog_पूर्णांक(slot, &pi);
	अगर (retval)
		वापस retval;

	चयन (pi) अणु
	हाल 1:
		pcix_cap = (slot_reg & PCIX_CAP_MASK_PI1) >> PCIX_CAP_SHIFT;
		अवरोध;
	हाल 2:
		pcix_cap = (slot_reg & PCIX_CAP_MASK_PI2) >> PCIX_CAP_SHIFT;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ctrl_dbg(ctrl, "%s: slot_reg = %x, pcix_cap = %x, m66_cap = %x\n",
		 __func__, slot_reg, pcix_cap, m66_cap);

	चयन (pcix_cap) अणु
	हाल 0x0:
		*value = m66_cap ? PCI_SPEED_66MHz : PCI_SPEED_33MHz;
		अवरोध;
	हाल 0x1:
		*value = PCI_SPEED_66MHz_PCIX;
		अवरोध;
	हाल 0x3:
		*value = PCI_SPEED_133MHz_PCIX;
		अवरोध;
	हाल 0x4:
		*value = PCI_SPEED_133MHz_PCIX_266;
		अवरोध;
	हाल 0x5:
		*value = PCI_SPEED_133MHz_PCIX_533;
		अवरोध;
	हाल 0x2:
	शेष:
		*value = PCI_SPEED_UNKNOWN;
		retval = -ENODEV;
		अवरोध;
	पूर्ण

	ctrl_dbg(ctrl, "Adapter speed = %d\n", *value);
	वापस retval;
पूर्ण

अटल पूर्णांक hpc_get_mode1_ECC_cap(काष्ठा slot *slot, u8 *mode)
अणु
	पूर्णांक retval = 0;
	काष्ठा controller *ctrl = slot->ctrl;
	u16 sec_bus_status = shpc_पढ़ोw(ctrl, SEC_BUS_CONFIG);
	u8 pi = shpc_पढ़ोb(ctrl, PROG_INTERFACE);

	अगर (pi == 2) अणु
		*mode = (sec_bus_status & 0x0100) >> 8;
	पूर्ण अन्यथा अणु
		retval = -1;
	पूर्ण

	ctrl_dbg(ctrl, "Mode 1 ECC cap = %d\n", *mode);
	वापस retval;
पूर्ण

अटल पूर्णांक hpc_query_घातer_fault(काष्ठा slot *slot)
अणु
	काष्ठा controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(slot->hp_slot));

	/* Note: Logic 0 => fault */
	वापस !(slot_reg & POWER_FAULT);
पूर्ण

अटल पूर्णांक hpc_set_attention_status(काष्ठा slot *slot, u8 value)
अणु
	u8 slot_cmd = 0;

	चयन (value) अणु
		हाल 0:
			slot_cmd = SET_ATTN_OFF;	/* OFF */
			अवरोध;
		हाल 1:
			slot_cmd = SET_ATTN_ON;		/* ON */
			अवरोध;
		हाल 2:
			slot_cmd = SET_ATTN_BLINK;	/* BLINK */
			अवरोध;
		शेष:
			वापस -1;
	पूर्ण

	वापस shpc_ग_लिखो_cmd(slot, slot->hp_slot, slot_cmd);
पूर्ण


अटल व्योम hpc_set_green_led_on(काष्ठा slot *slot)
अणु
	shpc_ग_लिखो_cmd(slot, slot->hp_slot, SET_PWR_ON);
पूर्ण

अटल व्योम hpc_set_green_led_off(काष्ठा slot *slot)
अणु
	shpc_ग_लिखो_cmd(slot, slot->hp_slot, SET_PWR_OFF);
पूर्ण

अटल व्योम hpc_set_green_led_blink(काष्ठा slot *slot)
अणु
	shpc_ग_लिखो_cmd(slot, slot->hp_slot, SET_PWR_BLINK);
पूर्ण

अटल व्योम hpc_release_ctlr(काष्ठा controller *ctrl)
अणु
	पूर्णांक i;
	u32 slot_reg, serr_पूर्णांक;

	/*
	 * Mask event पूर्णांकerrupts and SERRs of all slots
	 */
	क्रम (i = 0; i < ctrl->num_slots; i++) अणु
		slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(i));
		slot_reg |= (PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			     BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			     CON_PFAULT_INTR_MASK   | MRL_CHANGE_SERR_MASK |
			     CON_PFAULT_SERR_MASK);
		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_ग_लिखोl(ctrl, SLOT_REG(i), slot_reg);
	पूर्ण

	cleanup_slots(ctrl);

	/*
	 * Mask SERR and System Interrupt generation
	 */
	serr_पूर्णांक = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
	serr_पूर्णांक |= (GLOBAL_INTR_MASK  | GLOBAL_SERR_MASK |
		     COMMAND_INTR_MASK | ARBITER_SERR_MASK);
	serr_पूर्णांक &= ~SERR_INTR_RSVDZ_MASK;
	shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, serr_पूर्णांक);

	अगर (shpchp_poll_mode)
		del_समयr(&ctrl->poll_समयr);
	अन्यथा अणु
		मुक्त_irq(ctrl->pci_dev->irq, ctrl);
		pci_disable_msi(ctrl->pci_dev);
	पूर्ण

	iounmap(ctrl->creg);
	release_mem_region(ctrl->mmio_base, ctrl->mmio_size);
पूर्ण

अटल पूर्णांक hpc_घातer_on_slot(काष्ठा slot *slot)
अणु
	पूर्णांक retval;

	retval = shpc_ग_लिखो_cmd(slot, slot->hp_slot, SET_SLOT_PWR);
	अगर (retval)
		ctrl_err(slot->ctrl, "%s: Write command failed!\n", __func__);

	वापस retval;
पूर्ण

अटल पूर्णांक hpc_slot_enable(काष्ठा slot *slot)
अणु
	पूर्णांक retval;

	/* Slot - Enable, Power Indicator - Blink, Attention Indicator - Off */
	retval = shpc_ग_लिखो_cmd(slot, slot->hp_slot,
			SET_SLOT_ENABLE | SET_PWR_BLINK | SET_ATTN_OFF);
	अगर (retval)
		ctrl_err(slot->ctrl, "%s: Write command failed!\n", __func__);

	वापस retval;
पूर्ण

अटल पूर्णांक hpc_slot_disable(काष्ठा slot *slot)
अणु
	पूर्णांक retval;

	/* Slot - Disable, Power Indicator - Off, Attention Indicator - On */
	retval = shpc_ग_लिखो_cmd(slot, slot->hp_slot,
			SET_SLOT_DISABLE | SET_PWR_OFF | SET_ATTN_ON);
	अगर (retval)
		ctrl_err(slot->ctrl, "%s: Write command failed!\n", __func__);

	वापस retval;
पूर्ण

अटल पूर्णांक shpc_get_cur_bus_speed(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval = 0;
	काष्ठा pci_bus *bus = ctrl->pci_dev->subordinate;
	क्रमागत pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u16 sec_bus_reg = shpc_पढ़ोw(ctrl, SEC_BUS_CONFIG);
	u8 pi = shpc_पढ़ोb(ctrl, PROG_INTERFACE);
	u8 speed_mode = (pi == 2) ? (sec_bus_reg & 0xF) : (sec_bus_reg & 0x7);

	अगर ((pi == 1) && (speed_mode > 4)) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (speed_mode) अणु
	हाल 0x0:
		bus_speed = PCI_SPEED_33MHz;
		अवरोध;
	हाल 0x1:
		bus_speed = PCI_SPEED_66MHz;
		अवरोध;
	हाल 0x2:
		bus_speed = PCI_SPEED_66MHz_PCIX;
		अवरोध;
	हाल 0x3:
		bus_speed = PCI_SPEED_100MHz_PCIX;
		अवरोध;
	हाल 0x4:
		bus_speed = PCI_SPEED_133MHz_PCIX;
		अवरोध;
	हाल 0x5:
		bus_speed = PCI_SPEED_66MHz_PCIX_ECC;
		अवरोध;
	हाल 0x6:
		bus_speed = PCI_SPEED_100MHz_PCIX_ECC;
		अवरोध;
	हाल 0x7:
		bus_speed = PCI_SPEED_133MHz_PCIX_ECC;
		अवरोध;
	हाल 0x8:
		bus_speed = PCI_SPEED_66MHz_PCIX_266;
		अवरोध;
	हाल 0x9:
		bus_speed = PCI_SPEED_100MHz_PCIX_266;
		अवरोध;
	हाल 0xa:
		bus_speed = PCI_SPEED_133MHz_PCIX_266;
		अवरोध;
	हाल 0xb:
		bus_speed = PCI_SPEED_66MHz_PCIX_533;
		अवरोध;
	हाल 0xc:
		bus_speed = PCI_SPEED_100MHz_PCIX_533;
		अवरोध;
	हाल 0xd:
		bus_speed = PCI_SPEED_133MHz_PCIX_533;
		अवरोध;
	शेष:
		retval = -ENODEV;
		अवरोध;
	पूर्ण

 out:
	bus->cur_bus_speed = bus_speed;
	dbg("Current bus speed = %d\n", bus_speed);
	वापस retval;
पूर्ण


अटल पूर्णांक hpc_set_bus_speed_mode(काष्ठा slot *slot, क्रमागत pci_bus_speed value)
अणु
	पूर्णांक retval;
	काष्ठा controller *ctrl = slot->ctrl;
	u8 pi, cmd;

	pi = shpc_पढ़ोb(ctrl, PROG_INTERFACE);
	अगर ((pi == 1) && (value > PCI_SPEED_133MHz_PCIX))
		वापस -EINVAL;

	चयन (value) अणु
	हाल PCI_SPEED_33MHz:
		cmd = SETA_PCI_33MHZ;
		अवरोध;
	हाल PCI_SPEED_66MHz:
		cmd = SETA_PCI_66MHZ;
		अवरोध;
	हाल PCI_SPEED_66MHz_PCIX:
		cmd = SETA_PCIX_66MHZ;
		अवरोध;
	हाल PCI_SPEED_100MHz_PCIX:
		cmd = SETA_PCIX_100MHZ;
		अवरोध;
	हाल PCI_SPEED_133MHz_PCIX:
		cmd = SETA_PCIX_133MHZ;
		अवरोध;
	हाल PCI_SPEED_66MHz_PCIX_ECC:
		cmd = SETB_PCIX_66MHZ_EM;
		अवरोध;
	हाल PCI_SPEED_100MHz_PCIX_ECC:
		cmd = SETB_PCIX_100MHZ_EM;
		अवरोध;
	हाल PCI_SPEED_133MHz_PCIX_ECC:
		cmd = SETB_PCIX_133MHZ_EM;
		अवरोध;
	हाल PCI_SPEED_66MHz_PCIX_266:
		cmd = SETB_PCIX_66MHZ_266;
		अवरोध;
	हाल PCI_SPEED_100MHz_PCIX_266:
		cmd = SETB_PCIX_100MHZ_266;
		अवरोध;
	हाल PCI_SPEED_133MHz_PCIX_266:
		cmd = SETB_PCIX_133MHZ_266;
		अवरोध;
	हाल PCI_SPEED_66MHz_PCIX_533:
		cmd = SETB_PCIX_66MHZ_533;
		अवरोध;
	हाल PCI_SPEED_100MHz_PCIX_533:
		cmd = SETB_PCIX_100MHZ_533;
		अवरोध;
	हाल PCI_SPEED_133MHz_PCIX_533:
		cmd = SETB_PCIX_133MHZ_533;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	retval = shpc_ग_लिखो_cmd(slot, 0, cmd);
	अगर (retval)
		ctrl_err(ctrl, "%s: Write command failed!\n", __func__);
	अन्यथा
		shpc_get_cur_bus_speed(ctrl);

	वापस retval;
पूर्ण

अटल irqवापस_t shpc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा controller *ctrl = (काष्ठा controller *)dev_id;
	u32 serr_पूर्णांक, slot_reg, पूर्णांकr_loc, पूर्णांकr_loc2;
	पूर्णांक hp_slot;

	/* Check to see अगर it was our पूर्णांकerrupt */
	पूर्णांकr_loc = shpc_पढ़ोl(ctrl, INTR_LOC);
	अगर (!पूर्णांकr_loc)
		वापस IRQ_NONE;

	ctrl_dbg(ctrl, "%s: intr_loc = %x\n", __func__, पूर्णांकr_loc);

	अगर (!shpchp_poll_mode) अणु
		/*
		 * Mask Global Interrupt Mask - see implementation
		 * note on p. 139 of SHPC spec rev 1.0
		 */
		serr_पूर्णांक = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
		serr_पूर्णांक |= GLOBAL_INTR_MASK;
		serr_पूर्णांक &= ~SERR_INTR_RSVDZ_MASK;
		shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, serr_पूर्णांक);

		पूर्णांकr_loc2 = shpc_पढ़ोl(ctrl, INTR_LOC);
		ctrl_dbg(ctrl, "%s: intr_loc2 = %x\n", __func__, पूर्णांकr_loc2);
	पूर्ण

	अगर (पूर्णांकr_loc & CMD_INTR_PENDING) अणु
		/*
		 * Command Complete Interrupt Pending
		 * RO only - clear by writing 1 to the Command Completion
		 * Detect bit in Controller SERR-INT रेजिस्टर
		 */
		serr_पूर्णांक = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
		serr_पूर्णांक &= ~SERR_INTR_RSVDZ_MASK;
		shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, serr_पूर्णांक);

		wake_up_पूर्णांकerruptible(&ctrl->queue);
	पूर्ण

	अगर (!(पूर्णांकr_loc & ~CMD_INTR_PENDING))
		जाओ out;

	क्रम (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) अणु
		/* To find out which slot has पूर्णांकerrupt pending */
		अगर (!(पूर्णांकr_loc & SLOT_INTR_PENDING(hp_slot)))
			जारी;

		slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Slot %x with intr, slot register = %x\n",
			 hp_slot, slot_reg);

		अगर (slot_reg & MRL_CHANGE_DETECTED)
			shpchp_handle_चयन_change(hp_slot, ctrl);

		अगर (slot_reg & BUTTON_PRESS_DETECTED)
			shpchp_handle_attention_button(hp_slot, ctrl);

		अगर (slot_reg & PRSNT_CHANGE_DETECTED)
			shpchp_handle_presence_change(hp_slot, ctrl);

		अगर (slot_reg & (ISO_PFAULT_DETECTED | CON_PFAULT_DETECTED))
			shpchp_handle_घातer_fault(hp_slot, ctrl);

		/* Clear all slot events */
		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_ग_लिखोl(ctrl, SLOT_REG(hp_slot), slot_reg);
	पूर्ण
 out:
	अगर (!shpchp_poll_mode) अणु
		/* Unmask Global Interrupt Mask */
		serr_पूर्णांक = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
		serr_पूर्णांक &= ~(GLOBAL_INTR_MASK | SERR_INTR_RSVDZ_MASK);
		shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, serr_पूर्णांक);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक shpc_get_max_bus_speed(काष्ठा controller *ctrl)
अणु
	पूर्णांक retval = 0;
	काष्ठा pci_bus *bus = ctrl->pci_dev->subordinate;
	क्रमागत pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u8 pi = shpc_पढ़ोb(ctrl, PROG_INTERFACE);
	u32 slot_avail1 = shpc_पढ़ोl(ctrl, SLOT_AVAIL1);
	u32 slot_avail2 = shpc_पढ़ोl(ctrl, SLOT_AVAIL2);

	अगर (pi == 2) अणु
		अगर (slot_avail2 & SLOT_133MHZ_PCIX_533)
			bus_speed = PCI_SPEED_133MHz_PCIX_533;
		अन्यथा अगर (slot_avail2 & SLOT_100MHZ_PCIX_533)
			bus_speed = PCI_SPEED_100MHz_PCIX_533;
		अन्यथा अगर (slot_avail2 & SLOT_66MHZ_PCIX_533)
			bus_speed = PCI_SPEED_66MHz_PCIX_533;
		अन्यथा अगर (slot_avail2 & SLOT_133MHZ_PCIX_266)
			bus_speed = PCI_SPEED_133MHz_PCIX_266;
		अन्यथा अगर (slot_avail2 & SLOT_100MHZ_PCIX_266)
			bus_speed = PCI_SPEED_100MHz_PCIX_266;
		अन्यथा अगर (slot_avail2 & SLOT_66MHZ_PCIX_266)
			bus_speed = PCI_SPEED_66MHz_PCIX_266;
	पूर्ण

	अगर (bus_speed == PCI_SPEED_UNKNOWN) अणु
		अगर (slot_avail1 & SLOT_133MHZ_PCIX)
			bus_speed = PCI_SPEED_133MHz_PCIX;
		अन्यथा अगर (slot_avail1 & SLOT_100MHZ_PCIX)
			bus_speed = PCI_SPEED_100MHz_PCIX;
		अन्यथा अगर (slot_avail1 & SLOT_66MHZ_PCIX)
			bus_speed = PCI_SPEED_66MHz_PCIX;
		अन्यथा अगर (slot_avail2 & SLOT_66MHZ)
			bus_speed = PCI_SPEED_66MHz;
		अन्यथा अगर (slot_avail1 & SLOT_33MHZ)
			bus_speed = PCI_SPEED_33MHz;
		अन्यथा
			retval = -ENODEV;
	पूर्ण

	bus->max_bus_speed = bus_speed;
	ctrl_dbg(ctrl, "Max bus speed = %d\n", bus_speed);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा hpc_ops shpchp_hpc_ops = अणु
	.घातer_on_slot			= hpc_घातer_on_slot,
	.slot_enable			= hpc_slot_enable,
	.slot_disable			= hpc_slot_disable,
	.set_bus_speed_mode		= hpc_set_bus_speed_mode,
	.set_attention_status	= hpc_set_attention_status,
	.get_घातer_status		= hpc_get_घातer_status,
	.get_attention_status	= hpc_get_attention_status,
	.get_latch_status		= hpc_get_latch_status,
	.get_adapter_status		= hpc_get_adapter_status,

	.get_adapter_speed		= hpc_get_adapter_speed,
	.get_mode1_ECC_cap		= hpc_get_mode1_ECC_cap,
	.get_prog_पूर्णांक			= hpc_get_prog_पूर्णांक,

	.query_घातer_fault		= hpc_query_घातer_fault,
	.green_led_on			= hpc_set_green_led_on,
	.green_led_off			= hpc_set_green_led_off,
	.green_led_blink		= hpc_set_green_led_blink,

	.release_ctlr			= hpc_release_ctlr,
पूर्ण;

पूर्णांक shpc_init(काष्ठा controller *ctrl, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc = -1, num_slots = 0;
	u8 hp_slot;
	u32 shpc_base_offset;
	u32 tempdword, slot_reg, slot_config;
	u8 i;

	ctrl->pci_dev = pdev;  /* pci_dev of the P2P bridge */
	ctrl_dbg(ctrl, "Hotplug Controller:\n");

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_GOLAM_7450) अणु
		/* amd shpc driver करोesn't use Base Offset; assume 0 */
		ctrl->mmio_base = pci_resource_start(pdev, 0);
		ctrl->mmio_size = pci_resource_len(pdev, 0);
	पूर्ण अन्यथा अणु
		ctrl->cap_offset = pci_find_capability(pdev, PCI_CAP_ID_SHPC);
		अगर (!ctrl->cap_offset) अणु
			ctrl_err(ctrl, "Cannot find PCI capability\n");
			जाओ पात;
		पूर्ण
		ctrl_dbg(ctrl, " cap_offset = %x\n", ctrl->cap_offset);

		rc = shpc_indirect_पढ़ो(ctrl, 0, &shpc_base_offset);
		अगर (rc) अणु
			ctrl_err(ctrl, "Cannot read base_offset\n");
			जाओ पात;
		पूर्ण

		rc = shpc_indirect_पढ़ो(ctrl, 3, &tempdword);
		अगर (rc) अणु
			ctrl_err(ctrl, "Cannot read slot config\n");
			जाओ पात;
		पूर्ण
		num_slots = tempdword & SLOT_NUM;
		ctrl_dbg(ctrl, " num_slots (indirect) %x\n", num_slots);

		क्रम (i = 0; i < 9 + num_slots; i++) अणु
			rc = shpc_indirect_पढ़ो(ctrl, i, &tempdword);
			अगर (rc) अणु
				ctrl_err(ctrl, "Cannot read creg (index = %d)\n",
					 i);
				जाओ पात;
			पूर्ण
			ctrl_dbg(ctrl, " offset %d: value %x\n", i, tempdword);
		पूर्ण

		ctrl->mmio_base =
			pci_resource_start(pdev, 0) + shpc_base_offset;
		ctrl->mmio_size = 0x24 + 0x4 * num_slots;
	पूर्ण

	ctrl_info(ctrl, "HPC vendor_id %x device_id %x ss_vid %x ss_did %x\n",
		  pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
		  pdev->subप्रणाली_device);

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		ctrl_err(ctrl, "pci_enable_device failed\n");
		जाओ पात;
	पूर्ण

	अगर (!request_mem_region(ctrl->mmio_base, ctrl->mmio_size, MY_NAME)) अणु
		ctrl_err(ctrl, "Cannot reserve MMIO region\n");
		rc = -1;
		जाओ पात;
	पूर्ण

	ctrl->creg = ioremap(ctrl->mmio_base, ctrl->mmio_size);
	अगर (!ctrl->creg) अणु
		ctrl_err(ctrl, "Cannot remap MMIO region %lx @ %lx\n",
			 ctrl->mmio_size, ctrl->mmio_base);
		release_mem_region(ctrl->mmio_base, ctrl->mmio_size);
		rc = -1;
		जाओ पात;
	पूर्ण
	ctrl_dbg(ctrl, "ctrl->creg %p\n", ctrl->creg);

	mutex_init(&ctrl->crit_sect);
	mutex_init(&ctrl->cmd_lock);

	/* Setup रुको queue */
	init_रुकोqueue_head(&ctrl->queue);

	ctrl->hpc_ops = &shpchp_hpc_ops;

	/* Return PCI Controller Info */
	slot_config = shpc_पढ़ोl(ctrl, SLOT_CONFIG);
	ctrl->slot_device_offset = (slot_config & FIRST_DEV_NUM) >> 8;
	ctrl->num_slots = slot_config & SLOT_NUM;
	ctrl->first_slot = (slot_config & PSN) >> 16;
	ctrl->slot_num_inc = ((slot_config & UPDOWN) >> 29) ? 1 : -1;

	/* Mask Global Interrupt Mask & Command Complete Interrupt Mask */
	tempdword = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
	ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);
	tempdword |= (GLOBAL_INTR_MASK  | GLOBAL_SERR_MASK |
		      COMMAND_INTR_MASK | ARBITER_SERR_MASK);
	tempdword &= ~SERR_INTR_RSVDZ_MASK;
	shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, tempdword);
	tempdword = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
	ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);

	/* Mask the MRL sensor SERR Mask of inभागidual slot in
	 * Slot SERR-INT Mask & clear all the existing event अगर any
	 */
	क्रम (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) अणु
		slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Default Logical Slot Register %d value %x\n",
			 hp_slot, slot_reg);
		slot_reg |= (PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			     BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			     CON_PFAULT_INTR_MASK   | MRL_CHANGE_SERR_MASK |
			     CON_PFAULT_SERR_MASK);
		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_ग_लिखोl(ctrl, SLOT_REG(hp_slot), slot_reg);
	पूर्ण

	अगर (shpchp_poll_mode) अणु
		/* Install पूर्णांकerrupt polling समयr. Start with 10 sec delay */
		समयr_setup(&ctrl->poll_समयr, पूर्णांक_poll_समयout, 0);
		start_पूर्णांक_poll_समयr(ctrl, 10);
	पूर्ण अन्यथा अणु
		/* Installs the पूर्णांकerrupt handler */
		rc = pci_enable_msi(pdev);
		अगर (rc) अणु
			ctrl_info(ctrl, "Can't get msi for the hotplug controller\n");
			ctrl_info(ctrl, "Use INTx for the hotplug controller\n");
		पूर्ण अन्यथा अणु
			pci_set_master(pdev);
		पूर्ण

		rc = request_irq(ctrl->pci_dev->irq, shpc_isr, IRQF_SHARED,
				 MY_NAME, (व्योम *)ctrl);
		ctrl_dbg(ctrl, "request_irq %d (returns %d)\n",
			 ctrl->pci_dev->irq, rc);
		अगर (rc) अणु
			ctrl_err(ctrl, "Can't get irq %d for the hotplug controller\n",
				 ctrl->pci_dev->irq);
			जाओ पात_iounmap;
		पूर्ण
	पूर्ण
	ctrl_dbg(ctrl, "HPC at %s irq=%x\n", pci_name(pdev), pdev->irq);

	shpc_get_max_bus_speed(ctrl);
	shpc_get_cur_bus_speed(ctrl);

	/*
	 * Unmask all event पूर्णांकerrupts of all slots
	 */
	क्रम (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) अणु
		slot_reg = shpc_पढ़ोl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Default Logical Slot Register %d value %x\n",
			 hp_slot, slot_reg);
		slot_reg &= ~(PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			      BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			      CON_PFAULT_INTR_MASK | SLOT_REG_RSVDZ_MASK);
		shpc_ग_लिखोl(ctrl, SLOT_REG(hp_slot), slot_reg);
	पूर्ण
	अगर (!shpchp_poll_mode) अणु
		/* Unmask all general input पूर्णांकerrupts and SERR */
		tempdword = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
		tempdword &= ~(GLOBAL_INTR_MASK | COMMAND_INTR_MASK |
			       SERR_INTR_RSVDZ_MASK);
		shpc_ग_लिखोl(ctrl, SERR_INTR_ENABLE, tempdword);
		tempdword = shpc_पढ़ोl(ctrl, SERR_INTR_ENABLE);
		ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);
	पूर्ण

	वापस 0;

	/* We end up here क्रम the many possible ways to fail this API.  */
पात_iounmap:
	iounmap(ctrl->creg);
पात:
	वापस rc;
पूर्ण
