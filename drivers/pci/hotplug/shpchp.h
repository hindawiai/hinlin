<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Standard Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM
 * Copyright (C) 2003-2004 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>,<kristen.c.accardi@पूर्णांकel.com>
 *
 */
#अगर_अघोषित _SHPCHP_H
#घोषणा _SHPCHP_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>	/* संकेत_pending(), काष्ठा समयr_list */
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#अगर !defined(MODULE)
	#घोषणा MY_NAME	"shpchp"
#अन्यथा
	#घोषणा MY_NAME	THIS_MODULE->name
#पूर्ण_अगर

बाह्य bool shpchp_poll_mode;
बाह्य पूर्णांक shpchp_poll_समय;
बाह्य bool shpchp_debug;

#घोषणा dbg(क्रमmat, arg...)						\
करो अणु									\
	अगर (shpchp_debug)						\
		prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat, MY_NAME, ## arg);	\
पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...)						\
	prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...)						\
	prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...)						\
	prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)

#घोषणा ctrl_dbg(ctrl, क्रमmat, arg...)					\
	करो अणु								\
		अगर (shpchp_debug)					\
			pci_prपूर्णांकk(KERN_DEBUG, ctrl->pci_dev,		\
					क्रमmat, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा ctrl_err(ctrl, क्रमmat, arg...)					\
	pci_err(ctrl->pci_dev, क्रमmat, ## arg)
#घोषणा ctrl_info(ctrl, क्रमmat, arg...)					\
	pci_info(ctrl->pci_dev, क्रमmat, ## arg)
#घोषणा ctrl_warn(ctrl, क्रमmat, arg...)					\
	pci_warn(ctrl->pci_dev, क्रमmat, ## arg)


#घोषणा SLOT_NAME_SIZE 10
काष्ठा slot अणु
	u8 bus;
	u8 device;
	u16 status;
	u32 number;
	u8 is_a_board;
	u8 state;
	u8 attention_save;
	u8 presence_save;
	u8 latch_save;
	u8 pwr_save;
	काष्ठा controller *ctrl;
	स्थिर काष्ठा hpc_ops *hpc_ops;
	काष्ठा hotplug_slot hotplug_slot;
	काष्ठा list_head	slot_list;
	काष्ठा delayed_work work;	/* work क्रम button event */
	काष्ठा mutex lock;
	काष्ठा workqueue_काष्ठा *wq;
	u8 hp_slot;
पूर्ण;

काष्ठा event_info अणु
	u32 event_type;
	काष्ठा slot *p_slot;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा controller अणु
	काष्ठा mutex crit_sect;		/* critical section mutex */
	काष्ठा mutex cmd_lock;		/* command lock */
	पूर्णांक num_slots;			/* Number of slots on ctlr */
	पूर्णांक slot_num_inc;		/* 1 or -1 */
	काष्ठा pci_dev *pci_dev;
	काष्ठा list_head slot_list;
	स्थिर काष्ठा hpc_ops *hpc_ops;
	रुको_queue_head_t queue;	/* sleep & wake process */
	u8 slot_device_offset;
	u32 pcix_misc2_reg;	/* क्रम amd pogo errata */
	u32 first_slot;		/* First physical slot number */
	u32 cap_offset;
	अचिन्हित दीर्घ mmio_base;
	अचिन्हित दीर्घ mmio_size;
	व्योम __iomem *creg;
	काष्ठा समयr_list poll_समयr;
पूर्ण;

/* Define AMD SHPC ID  */
#घोषणा PCI_DEVICE_ID_AMD_POGO_7458	0x7458

/* AMD PCI-X bridge रेजिस्टरs */
#घोषणा PCIX_MEM_BASE_LIMIT_OFFSET	0x1C
#घोषणा PCIX_MISCII_OFFSET		0x48
#घोषणा PCIX_MISC_BRIDGE_ERRORS_OFFSET	0x80

/* AMD PCIX_MISCII masks and offsets */
#घोषणा PERRNONFATALENABLE_MASK		0x00040000
#घोषणा PERRFATALENABLE_MASK		0x00080000
#घोषणा PERRFLOODENABLE_MASK		0x00100000
#घोषणा SERRNONFATALENABLE_MASK		0x00200000
#घोषणा SERRFATALENABLE_MASK		0x00400000

/* AMD PCIX_MISC_BRIDGE_ERRORS masks and offsets */
#घोषणा PERR_OBSERVED_MASK		0x00000001

/* AMD PCIX_MEM_BASE_LIMIT masks */
#घोषणा RSE_MASK			0x40000000

#घोषणा INT_BUTTON_IGNORE		0
#घोषणा INT_PRESENCE_ON			1
#घोषणा INT_PRESENCE_OFF		2
#घोषणा INT_SWITCH_CLOSE		3
#घोषणा INT_SWITCH_OPEN			4
#घोषणा INT_POWER_FAULT			5
#घोषणा INT_POWER_FAULT_CLEAR		6
#घोषणा INT_BUTTON_PRESS		7
#घोषणा INT_BUTTON_RELEASE		8
#घोषणा INT_BUTTON_CANCEL		9

#घोषणा STATIC_STATE			0
#घोषणा BLINKINGON_STATE		1
#घोषणा BLINKINGOFF_STATE		2
#घोषणा POWERON_STATE			3
#घोषणा POWEROFF_STATE			4

/* Error messages */
#घोषणा INTERLOCK_OPEN			0x00000002
#घोषणा ADD_NOT_SUPPORTED		0x00000003
#घोषणा CARD_FUNCTIONING		0x00000005
#घोषणा ADAPTER_NOT_SAME		0x00000006
#घोषणा NO_ADAPTER_PRESENT		0x00000009
#घोषणा NOT_ENOUGH_RESOURCES		0x0000000B
#घोषणा DEVICE_TYPE_NOT_SUPPORTED	0x0000000C
#घोषणा WRONG_BUS_FREQUENCY		0x0000000D
#घोषणा POWER_FAILURE			0x0000000E

पूर्णांक __must_check shpchp_create_ctrl_files(काष्ठा controller *ctrl);
व्योम shpchp_हटाओ_ctrl_files(काष्ठा controller *ctrl);
पूर्णांक shpchp_sysfs_enable_slot(काष्ठा slot *slot);
पूर्णांक shpchp_sysfs_disable_slot(काष्ठा slot *slot);
u8 shpchp_handle_attention_button(u8 hp_slot, काष्ठा controller *ctrl);
u8 shpchp_handle_चयन_change(u8 hp_slot, काष्ठा controller *ctrl);
u8 shpchp_handle_presence_change(u8 hp_slot, काष्ठा controller *ctrl);
u8 shpchp_handle_घातer_fault(u8 hp_slot, काष्ठा controller *ctrl);
पूर्णांक shpchp_configure_device(काष्ठा slot *p_slot);
व्योम shpchp_unconfigure_device(काष्ठा slot *p_slot);
व्योम cleanup_slots(काष्ठा controller *ctrl);
व्योम shpchp_queue_pushbutton_work(काष्ठा work_काष्ठा *work);
पूर्णांक shpc_init(काष्ठा controller *ctrl, काष्ठा pci_dev *pdev);

अटल अंतरभूत स्थिर अक्षर *slot_name(काष्ठा slot *slot)
अणु
	वापस hotplug_slot_name(&slot->hotplug_slot);
पूर्ण

काष्ठा ctrl_reg अणु
	अस्थिर u32 base_offset;
	अस्थिर u32 slot_avail1;
	अस्थिर u32 slot_avail2;
	अस्थिर u32 slot_config;
	अस्थिर u16 sec_bus_config;
	अस्थिर u8  msi_ctrl;
	अस्थिर u8  prog_पूर्णांकerface;
	अस्थिर u16 cmd;
	अस्थिर u16 cmd_status;
	अस्थिर u32 पूर्णांकr_loc;
	अस्थिर u32 serr_loc;
	अस्थिर u32 serr_पूर्णांकr_enable;
	अस्थिर u32 slot1;
पूर्ण __attribute__ ((packed));

/* offsets to the controller रेजिस्टरs based on the above काष्ठाure layout */
क्रमागत ctrl_offsets अणु
	BASE_OFFSET	 = दुरत्व(काष्ठा ctrl_reg, base_offset),
	SLOT_AVAIL1	 = दुरत्व(काष्ठा ctrl_reg, slot_avail1),
	SLOT_AVAIL2	 = दुरत्व(काष्ठा ctrl_reg, slot_avail2),
	SLOT_CONFIG	 = दुरत्व(काष्ठा ctrl_reg, slot_config),
	SEC_BUS_CONFIG	 = दुरत्व(काष्ठा ctrl_reg, sec_bus_config),
	MSI_CTRL	 = दुरत्व(काष्ठा ctrl_reg, msi_ctrl),
	PROG_INTERFACE	 = दुरत्व(काष्ठा ctrl_reg, prog_पूर्णांकerface),
	CMD		 = दुरत्व(काष्ठा ctrl_reg, cmd),
	CMD_STATUS	 = दुरत्व(काष्ठा ctrl_reg, cmd_status),
	INTR_LOC	 = दुरत्व(काष्ठा ctrl_reg, पूर्णांकr_loc),
	SERR_LOC	 = दुरत्व(काष्ठा ctrl_reg, serr_loc),
	SERR_INTR_ENABLE = दुरत्व(काष्ठा ctrl_reg, serr_पूर्णांकr_enable),
	SLOT1		 = दुरत्व(काष्ठा ctrl_reg, slot1),
पूर्ण;

अटल अंतरभूत काष्ठा slot *get_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

अटल अंतरभूत काष्ठा slot *shpchp_find_slot(काष्ठा controller *ctrl, u8 device)
अणु
	काष्ठा slot *slot;

	list_क्रम_each_entry(slot, &ctrl->slot_list, slot_list) अणु
		अगर (slot->device == device)
			वापस slot;
	पूर्ण

	ctrl_err(ctrl, "Slot (device=0x%02x) not found\n", device);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम amd_pogo_errata_save_misc_reg(काष्ठा slot *p_slot)
अणु
	u32 pcix_misc2_temp;

	/* save MiscII रेजिस्टर */
	pci_पढ़ो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp);

	p_slot->ctrl->pcix_misc2_reg = pcix_misc2_temp;

	/* clear SERR/PERR enable bits */
	pcix_misc2_temp &= ~SERRFATALENABLE_MASK;
	pcix_misc2_temp &= ~SERRNONFATALENABLE_MASK;
	pcix_misc2_temp &= ~PERRFLOODENABLE_MASK;
	pcix_misc2_temp &= ~PERRFATALENABLE_MASK;
	pcix_misc2_temp &= ~PERRNONFATALENABLE_MASK;
	pci_ग_लिखो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
पूर्ण

अटल अंतरभूत व्योम amd_pogo_errata_restore_misc_reg(काष्ठा slot *p_slot)
अणु
	u32 pcix_misc2_temp;
	u32 pcix_bridge_errors_reg;
	u32 pcix_mem_base_reg;
	u8  perr_set;
	u8  rse_set;

	/* ग_लिखो-one-to-clear Bridge_Errors[ PERR_OBSERVED ] */
	pci_पढ़ो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISC_BRIDGE_ERRORS_OFFSET, &pcix_bridge_errors_reg);
	perr_set = pcix_bridge_errors_reg & PERR_OBSERVED_MASK;
	अगर (perr_set) अणु
		ctrl_dbg(p_slot->ctrl,
			 "Bridge_Errors[ PERR_OBSERVED = %08X] (W1C)\n",
			 perr_set);

		pci_ग_लिखो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISC_BRIDGE_ERRORS_OFFSET, perr_set);
	पूर्ण

	/* ग_लिखो-one-to-clear Memory_Base_Limit[ RSE ] */
	pci_पढ़ो_config_dword(p_slot->ctrl->pci_dev, PCIX_MEM_BASE_LIMIT_OFFSET, &pcix_mem_base_reg);
	rse_set = pcix_mem_base_reg & RSE_MASK;
	अगर (rse_set) अणु
		ctrl_dbg(p_slot->ctrl, "Memory_Base_Limit[ RSE ] (W1C)\n");

		pci_ग_लिखो_config_dword(p_slot->ctrl->pci_dev, PCIX_MEM_BASE_LIMIT_OFFSET, rse_set);
	पूर्ण
	/* restore MiscII रेजिस्टर */
	pci_पढ़ो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp);

	अगर (p_slot->ctrl->pcix_misc2_reg & SERRFATALENABLE_MASK)
		pcix_misc2_temp |= SERRFATALENABLE_MASK;
	अन्यथा
		pcix_misc2_temp &= ~SERRFATALENABLE_MASK;

	अगर (p_slot->ctrl->pcix_misc2_reg & SERRNONFATALENABLE_MASK)
		pcix_misc2_temp |= SERRNONFATALENABLE_MASK;
	अन्यथा
		pcix_misc2_temp &= ~SERRNONFATALENABLE_MASK;

	अगर (p_slot->ctrl->pcix_misc2_reg & PERRFLOODENABLE_MASK)
		pcix_misc2_temp |= PERRFLOODENABLE_MASK;
	अन्यथा
		pcix_misc2_temp &= ~PERRFLOODENABLE_MASK;

	अगर (p_slot->ctrl->pcix_misc2_reg & PERRFATALENABLE_MASK)
		pcix_misc2_temp |= PERRFATALENABLE_MASK;
	अन्यथा
		pcix_misc2_temp &= ~PERRFATALENABLE_MASK;

	अगर (p_slot->ctrl->pcix_misc2_reg & PERRNONFATALENABLE_MASK)
		pcix_misc2_temp |= PERRNONFATALENABLE_MASK;
	अन्यथा
		pcix_misc2_temp &= ~PERRNONFATALENABLE_MASK;
	pci_ग_लिखो_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
पूर्ण

काष्ठा hpc_ops अणु
	पूर्णांक (*घातer_on_slot)(काष्ठा slot *slot);
	पूर्णांक (*slot_enable)(काष्ठा slot *slot);
	पूर्णांक (*slot_disable)(काष्ठा slot *slot);
	पूर्णांक (*set_bus_speed_mode)(काष्ठा slot *slot, क्रमागत pci_bus_speed speed);
	पूर्णांक (*get_घातer_status)(काष्ठा slot *slot, u8 *status);
	पूर्णांक (*get_attention_status)(काष्ठा slot *slot, u8 *status);
	पूर्णांक (*set_attention_status)(काष्ठा slot *slot, u8 status);
	पूर्णांक (*get_latch_status)(काष्ठा slot *slot, u8 *status);
	पूर्णांक (*get_adapter_status)(काष्ठा slot *slot, u8 *status);
	पूर्णांक (*get_adapter_speed)(काष्ठा slot *slot, क्रमागत pci_bus_speed *speed);
	पूर्णांक (*get_mode1_ECC_cap)(काष्ठा slot *slot, u8 *mode);
	पूर्णांक (*get_prog_पूर्णांक)(काष्ठा slot *slot, u8 *prog_पूर्णांक);
	पूर्णांक (*query_घातer_fault)(काष्ठा slot *slot);
	व्योम (*green_led_on)(काष्ठा slot *slot);
	व्योम (*green_led_off)(काष्ठा slot *slot);
	व्योम (*green_led_blink)(काष्ठा slot *slot);
	व्योम (*release_ctlr)(काष्ठा controller *ctrl);
	पूर्णांक (*check_cmd_status)(काष्ठा controller *ctrl);
पूर्ण;

#पूर्ण_अगर				/* _SHPCHP_H */
