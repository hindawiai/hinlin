<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 */
#अगर_अघोषित _CPQPHP_H
#घोषणा _CPQPHP_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>		/* क्रम पढ़ो? and ग_लिखो? functions */
#समावेश <linux/delay.h>	/* क्रम delays */
#समावेश <linux/mutex.h>
#समावेश <linux/sched/संकेत.स>	/* क्रम संकेत_pending() */

#घोषणा MY_NAME	"cpqphp"

#घोषणा dbg(fmt, arg...) करो अणु अगर (cpqhp_debug) prपूर्णांकk(KERN_DEBUG "%s: " fmt, MY_NAME, ## arg); पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)



काष्ठा smbios_प्रणाली_slot अणु
	u8 type;
	u8 length;
	u16 handle;
	u8 name_string_num;
	u8 slot_type;
	u8 slot_width;
	u8 slot_current_usage;
	u8 slot_length;
	u16 slot_number;
	u8 properties1;
	u8 properties2;
पूर्ण __attribute__ ((packed));

/* offsets to the smbios generic type based on the above काष्ठाure layout */
क्रमागत smbios_प्रणाली_slot_offsets अणु
	SMBIOS_SLOT_GENERIC_TYPE =	दुरत्व(काष्ठा smbios_प्रणाली_slot, type),
	SMBIOS_SLOT_GENERIC_LENGTH =	दुरत्व(काष्ठा smbios_प्रणाली_slot, length),
	SMBIOS_SLOT_GENERIC_HANDLE =	दुरत्व(काष्ठा smbios_प्रणाली_slot, handle),
	SMBIOS_SLOT_NAME_STRING_NUM =	दुरत्व(काष्ठा smbios_प्रणाली_slot, name_string_num),
	SMBIOS_SLOT_TYPE =		दुरत्व(काष्ठा smbios_प्रणाली_slot, slot_type),
	SMBIOS_SLOT_WIDTH =		दुरत्व(काष्ठा smbios_प्रणाली_slot, slot_width),
	SMBIOS_SLOT_CURRENT_USAGE =	दुरत्व(काष्ठा smbios_प्रणाली_slot, slot_current_usage),
	SMBIOS_SLOT_LENGTH =		दुरत्व(काष्ठा smbios_प्रणाली_slot, slot_length),
	SMBIOS_SLOT_NUMBER =		दुरत्व(काष्ठा smbios_प्रणाली_slot, slot_number),
	SMBIOS_SLOT_PROPERTIES1 =	दुरत्व(काष्ठा smbios_प्रणाली_slot, properties1),
	SMBIOS_SLOT_PROPERTIES2 =	दुरत्व(काष्ठा smbios_प्रणाली_slot, properties2),
पूर्ण;

काष्ठा smbios_generic अणु
	u8 type;
	u8 length;
	u16 handle;
पूर्ण __attribute__ ((packed));

/* offsets to the smbios generic type based on the above काष्ठाure layout */
क्रमागत smbios_generic_offsets अणु
	SMBIOS_GENERIC_TYPE =	दुरत्व(काष्ठा smbios_generic, type),
	SMBIOS_GENERIC_LENGTH =	दुरत्व(काष्ठा smbios_generic, length),
	SMBIOS_GENERIC_HANDLE =	दुरत्व(काष्ठा smbios_generic, handle),
पूर्ण;

काष्ठा smbios_entry_poपूर्णांक अणु
	अक्षर anchor[4];
	u8 ep_checksum;
	u8 ep_length;
	u8 major_version;
	u8 minor_version;
	u16 max_size_entry;
	u8 ep_rev;
	u8 reserved[5];
	अक्षर पूर्णांक_anchor[5];
	u8 पूर्णांक_checksum;
	u16 st_length;
	u32 st_address;
	u16 number_of_entrys;
	u8 bcd_rev;
पूर्ण __attribute__ ((packed));

/* offsets to the smbios entry poपूर्णांक based on the above काष्ठाure layout */
क्रमागत smbios_entry_poपूर्णांक_offsets अणु
	ANCHOR =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, anchor[0]),
	EP_CHECKSUM =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, ep_checksum),
	EP_LENGTH =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, ep_length),
	MAJOR_VERSION =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, major_version),
	MINOR_VERSION =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, minor_version),
	MAX_SIZE_ENTRY =	दुरत्व(काष्ठा smbios_entry_poपूर्णांक, max_size_entry),
	EP_REV =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, ep_rev),
	INT_ANCHOR =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, पूर्णांक_anchor[0]),
	INT_CHECKSUM =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, पूर्णांक_checksum),
	ST_LENGTH =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, st_length),
	ST_ADDRESS =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, st_address),
	NUMBER_OF_ENTRYS =	दुरत्व(काष्ठा smbios_entry_poपूर्णांक, number_of_entrys),
	BCD_REV =		दुरत्व(काष्ठा smbios_entry_poपूर्णांक, bcd_rev),
पूर्ण;

काष्ठा ctrl_reg अणु			/* offset */
	u8	slot_RST;		/* 0x00 */
	u8	slot_enable;		/* 0x01 */
	u16	misc;			/* 0x02 */
	u32	led_control;		/* 0x04 */
	u32	पूर्णांक_input_clear;	/* 0x08 */
	u32	पूर्णांक_mask;		/* 0x0a */
	u8	reserved0;		/* 0x10 */
	u8	reserved1;		/* 0x11 */
	u8	reserved2;		/* 0x12 */
	u8	gen_output_AB;		/* 0x13 */
	u32	non_पूर्णांक_input;		/* 0x14 */
	u32	reserved3;		/* 0x18 */
	u32	reserved4;		/* 0x1a */
	u32	reserved5;		/* 0x20 */
	u8	reserved6;		/* 0x24 */
	u8	reserved7;		/* 0x25 */
	u16	reserved8;		/* 0x26 */
	u8	slot_mask;		/* 0x28 */
	u8	reserved9;		/* 0x29 */
	u8	reserved10;		/* 0x2a */
	u8	reserved11;		/* 0x2b */
	u8	slot_SERR;		/* 0x2c */
	u8	slot_घातer;		/* 0x2d */
	u8	reserved12;		/* 0x2e */
	u8	reserved13;		/* 0x2f */
	u8	next_curr_freq;		/* 0x30 */
	u8	reset_freq_mode;	/* 0x31 */
पूर्ण __attribute__ ((packed));

/* offsets to the controller रेजिस्टरs based on the above काष्ठाure layout */
क्रमागत ctrl_offsets अणु
	SLOT_RST =		दुरत्व(काष्ठा ctrl_reg, slot_RST),
	SLOT_ENABLE =		दुरत्व(काष्ठा ctrl_reg, slot_enable),
	MISC =			दुरत्व(काष्ठा ctrl_reg, misc),
	LED_CONTROL =		दुरत्व(काष्ठा ctrl_reg, led_control),
	INT_INPUT_CLEAR =	दुरत्व(काष्ठा ctrl_reg, पूर्णांक_input_clear),
	INT_MASK =		दुरत्व(काष्ठा ctrl_reg, पूर्णांक_mask),
	CTRL_RESERVED0 =	दुरत्व(काष्ठा ctrl_reg, reserved0),
	CTRL_RESERVED1 =	दुरत्व(काष्ठा ctrl_reg, reserved1),
	CTRL_RESERVED2 =	दुरत्व(काष्ठा ctrl_reg, reserved1),
	GEN_OUTPUT_AB =		दुरत्व(काष्ठा ctrl_reg, gen_output_AB),
	NON_INT_INPUT =		दुरत्व(काष्ठा ctrl_reg, non_पूर्णांक_input),
	CTRL_RESERVED3 =	दुरत्व(काष्ठा ctrl_reg, reserved3),
	CTRL_RESERVED4 =	दुरत्व(काष्ठा ctrl_reg, reserved4),
	CTRL_RESERVED5 =	दुरत्व(काष्ठा ctrl_reg, reserved5),
	CTRL_RESERVED6 =	दुरत्व(काष्ठा ctrl_reg, reserved6),
	CTRL_RESERVED7 =	दुरत्व(काष्ठा ctrl_reg, reserved7),
	CTRL_RESERVED8 =	दुरत्व(काष्ठा ctrl_reg, reserved8),
	SLOT_MASK =		दुरत्व(काष्ठा ctrl_reg, slot_mask),
	CTRL_RESERVED9 =	दुरत्व(काष्ठा ctrl_reg, reserved9),
	CTRL_RESERVED10 =	दुरत्व(काष्ठा ctrl_reg, reserved10),
	CTRL_RESERVED11 =	दुरत्व(काष्ठा ctrl_reg, reserved11),
	SLOT_SERR =		दुरत्व(काष्ठा ctrl_reg, slot_SERR),
	SLOT_POWER =		दुरत्व(काष्ठा ctrl_reg, slot_घातer),
	NEXT_CURR_FREQ =	दुरत्व(काष्ठा ctrl_reg, next_curr_freq),
	RESET_FREQ_MODE =	दुरत्व(काष्ठा ctrl_reg, reset_freq_mode),
पूर्ण;

काष्ठा hrt अणु
	अक्षर sig0;
	अक्षर sig1;
	अक्षर sig2;
	अक्षर sig3;
	u16 unused_IRQ;
	u16 PCIIRQ;
	u8 number_of_entries;
	u8 revision;
	u16 reserved1;
	u32 reserved2;
पूर्ण __attribute__ ((packed));

/* offsets to the hotplug resource table रेजिस्टरs based on the above
 * काष्ठाure layout
 */
क्रमागत hrt_offsets अणु
	SIG0 =			दुरत्व(काष्ठा hrt, sig0),
	SIG1 =			दुरत्व(काष्ठा hrt, sig1),
	SIG2 =			दुरत्व(काष्ठा hrt, sig2),
	SIG3 =			दुरत्व(काष्ठा hrt, sig3),
	UNUSED_IRQ =		दुरत्व(काष्ठा hrt, unused_IRQ),
	PCIIRQ =		दुरत्व(काष्ठा hrt, PCIIRQ),
	NUMBER_OF_ENTRIES =	दुरत्व(काष्ठा hrt, number_of_entries),
	REVISION =		दुरत्व(काष्ठा hrt, revision),
	HRT_RESERVED1 =		दुरत्व(काष्ठा hrt, reserved1),
	HRT_RESERVED2 =		दुरत्व(काष्ठा hrt, reserved2),
पूर्ण;

काष्ठा slot_rt अणु
	u8 dev_func;
	u8 primary_bus;
	u8 secondary_bus;
	u8 max_bus;
	u16 io_base;
	u16 io_length;
	u16 mem_base;
	u16 mem_length;
	u16 pre_mem_base;
	u16 pre_mem_length;
पूर्ण __attribute__ ((packed));

/* offsets to the hotplug slot resource table रेजिस्टरs based on the above
 * काष्ठाure layout
 */
क्रमागत slot_rt_offsets अणु
	DEV_FUNC =		दुरत्व(काष्ठा slot_rt, dev_func),
	PRIMARY_BUS =		दुरत्व(काष्ठा slot_rt, primary_bus),
	SECONDARY_BUS =		दुरत्व(काष्ठा slot_rt, secondary_bus),
	MAX_BUS =		दुरत्व(काष्ठा slot_rt, max_bus),
	IO_BASE =		दुरत्व(काष्ठा slot_rt, io_base),
	IO_LENGTH =		दुरत्व(काष्ठा slot_rt, io_length),
	MEM_BASE =		दुरत्व(काष्ठा slot_rt, mem_base),
	MEM_LENGTH =		दुरत्व(काष्ठा slot_rt, mem_length),
	PRE_MEM_BASE =		दुरत्व(काष्ठा slot_rt, pre_mem_base),
	PRE_MEM_LENGTH =	दुरत्व(काष्ठा slot_rt, pre_mem_length),
पूर्ण;

काष्ठा pci_func अणु
	काष्ठा pci_func *next;
	u8 bus;
	u8 device;
	u8 function;
	u8 is_a_board;
	u16 status;
	u8 configured;
	u8 चयन_save;
	u8 presence_save;
	u32 base_length[0x06];
	u8 base_type[0x06];
	u16 reserved2;
	u32 config_space[0x20];
	काष्ठा pci_resource *mem_head;
	काष्ठा pci_resource *p_mem_head;
	काष्ठा pci_resource *io_head;
	काष्ठा pci_resource *bus_head;
	काष्ठा समयr_list *p_task_event;
	काष्ठा pci_dev *pci_dev;
पूर्ण;

काष्ठा slot अणु
	काष्ठा slot *next;
	u8 bus;
	u8 device;
	u8 number;
	u8 is_a_board;
	u8 configured;
	u8 state;
	u8 चयन_save;
	u8 presence_save;
	u32 capabilities;
	u16 reserved2;
	काष्ठा समयr_list task_event;
	u8 hp_slot;
	काष्ठा controller *ctrl;
	व्योम __iomem *p_sm_slot;
	काष्ठा hotplug_slot hotplug_slot;
पूर्ण;

काष्ठा pci_resource अणु
	काष्ठा pci_resource *next;
	u32 base;
	u32 length;
पूर्ण;

काष्ठा event_info अणु
	u32 event_type;
	u8 hp_slot;
पूर्ण;

काष्ठा controller अणु
	काष्ठा controller *next;
	u32 ctrl_पूर्णांक_comp;
	काष्ठा mutex crit_sect;	/* critical section mutex */
	व्योम __iomem *hpc_reg;	/* cookie क्रम our pci controller location */
	काष्ठा pci_resource *mem_head;
	काष्ठा pci_resource *p_mem_head;
	काष्ठा pci_resource *io_head;
	काष्ठा pci_resource *bus_head;
	काष्ठा pci_dev *pci_dev;
	काष्ठा pci_bus *pci_bus;
	काष्ठा event_info event_queue[10];
	काष्ठा slot *slot;
	u8 next_event;
	u8 पूर्णांकerrupt;
	u8 cfgspc_irq;
	u8 bus;			/* bus number क्रम the pci hotplug controller */
	u8 rev;
	u8 slot_device_offset;
	u8 first_slot;
	u8 add_support;
	u8 push_flag;
	u8 push_button;			/* 0 = no pushbutton, 1 = pushbutton present */
	u8 slot_चयन_type;		/* 0 = no चयन, 1 = चयन present */
	u8 defeature_PHP;		/* 0 = PHP not supported, 1 = PHP supported */
	u8 alternate_base_address;	/* 0 = not supported, 1 = supported */
	u8 pci_config_space;		/* Index/data access to working रेजिस्टरs 0 = not supported, 1 = supported */
	u8 pcix_speed_capability;	/* PCI-X */
	u8 pcix_support;		/* PCI-X */
	u16 venकरोr_id;
	काष्ठा work_काष्ठा पूर्णांक_task_event;
	रुको_queue_head_t queue;	/* sleep & wake process */
	काष्ठा dentry *dentry;		/* debugfs dentry */
पूर्ण;

काष्ठा irq_mapping अणु
	u8 barber_pole;
	u8 valid_INT;
	u8 पूर्णांकerrupt[4];
पूर्ण;

काष्ठा resource_lists अणु
	काष्ठा pci_resource *mem_head;
	काष्ठा pci_resource *p_mem_head;
	काष्ठा pci_resource *io_head;
	काष्ठा pci_resource *bus_head;
	काष्ठा irq_mapping *irqs;
पूर्ण;

#घोषणा ROM_PHY_ADDR			0x0F0000
#घोषणा ROM_PHY_LEN			0x00ffff

#घोषणा PCI_HPC_ID			0xA0F7
#घोषणा PCI_SUB_HPC_ID			0xA2F7
#घोषणा PCI_SUB_HPC_ID2			0xA2F8
#घोषणा PCI_SUB_HPC_ID3			0xA2F9
#घोषणा PCI_SUB_HPC_ID_INTC		0xA2FA
#घोषणा PCI_SUB_HPC_ID4			0xA2FD

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

#घोषणा PCISLOT_INTERLOCK_CLOSED	0x00000001
#घोषणा PCISLOT_ADAPTER_PRESENT		0x00000002
#घोषणा PCISLOT_POWERED			0x00000004
#घोषणा PCISLOT_66_MHZ_OPERATION	0x00000008
#घोषणा PCISLOT_64_BIT_OPERATION	0x00000010
#घोषणा PCISLOT_REPLACE_SUPPORTED	0x00000020
#घोषणा PCISLOT_ADD_SUPPORTED		0x00000040
#घोषणा PCISLOT_INTERLOCK_SUPPORTED	0x00000080
#घोषणा PCISLOT_66_MHZ_SUPPORTED	0x00000100
#घोषणा PCISLOT_64_BIT_SUPPORTED	0x00000200

#घोषणा PCI_TO_PCI_BRIDGE_CLASS		0x00060400

#घोषणा INTERLOCK_OPEN			0x00000002
#घोषणा ADD_NOT_SUPPORTED		0x00000003
#घोषणा CARD_FUNCTIONING		0x00000005
#घोषणा ADAPTER_NOT_SAME		0x00000006
#घोषणा NO_ADAPTER_PRESENT		0x00000009
#घोषणा NOT_ENOUGH_RESOURCES		0x0000000B
#घोषणा DEVICE_TYPE_NOT_SUPPORTED	0x0000000C
#घोषणा POWER_FAILURE			0x0000000E

#घोषणा REMOVE_NOT_SUPPORTED		0x00000003


/*
 * error Messages
 */
#घोषणा msg_initialization_err	"Initialization failure, error=%d\n"
#घोषणा msg_HPC_rev_error	"Unsupported revision of the PCI hot plug controller found.\n"
#घोषणा msg_HPC_non_compaq_or_पूर्णांकel	"The PCI hot plug controller is not supported by this driver.\n"
#घोषणा msg_HPC_not_supported	"this system is not supported by this version of cpqphpd. Upgrade to a newer version of cpqphpd\n"
#घोषणा msg_unable_to_save	"unable to store PCI hot plug add resource information. This system must be rebooted before adding any PCI devices.\n"
#घोषणा msg_button_on		"PCI slot #%d - powering on due to button press.\n"
#घोषणा msg_button_off		"PCI slot #%d - powering off due to button press.\n"
#घोषणा msg_button_cancel	"PCI slot #%d - action canceled due to button press.\n"
#घोषणा msg_button_ignore	"PCI slot #%d - button press ignored.  (action in progress...)\n"


/* debugfs functions क्रम the hotplug controller info */
व्योम cpqhp_initialize_debugfs(व्योम);
व्योम cpqhp_shutकरोwn_debugfs(व्योम);
व्योम cpqhp_create_debugfs_files(काष्ठा controller *ctrl);
व्योम cpqhp_हटाओ_debugfs_files(काष्ठा controller *ctrl);

/* controller functions */
व्योम cpqhp_pushbutton_thपढ़ो(काष्ठा समयr_list *t);
irqवापस_t cpqhp_ctrl_पूर्णांकr(पूर्णांक IRQ, व्योम *data);
पूर्णांक cpqhp_find_available_resources(काष्ठा controller *ctrl,
				   व्योम __iomem *rom_start);
पूर्णांक cpqhp_event_start_thपढ़ो(व्योम);
व्योम cpqhp_event_stop_thपढ़ो(व्योम);
काष्ठा pci_func *cpqhp_slot_create(अचिन्हित अक्षर busnumber);
काष्ठा pci_func *cpqhp_slot_find(अचिन्हित अक्षर bus, अचिन्हित अक्षर device,
				 अचिन्हित अक्षर index);
पूर्णांक cpqhp_process_SI(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_process_SS(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_hardware_test(काष्ठा controller *ctrl, पूर्णांक test_num);

/* resource functions */
पूर्णांक	cpqhp_resource_sort_and_combine(काष्ठा pci_resource **head);

/* pci functions */
पूर्णांक cpqhp_set_irq(u8 bus_num, u8 dev_num, u8 पूर्णांक_pin, u8 irq_num);
पूर्णांक cpqhp_get_bus_dev(काष्ठा controller *ctrl, u8 *bus_num, u8 *dev_num,
		      u8 slot);
पूर्णांक cpqhp_save_config(काष्ठा controller *ctrl, पूर्णांक busnumber, पूर्णांक is_hot_plug);
पूर्णांक cpqhp_save_base_addr_length(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_save_used_resources(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_configure_board(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_save_slot_config(काष्ठा controller *ctrl, काष्ठा pci_func *new_slot);
पूर्णांक cpqhp_valid_replace(काष्ठा controller *ctrl, काष्ठा pci_func *func);
व्योम cpqhp_destroy_board_resources(काष्ठा pci_func *func);
पूर्णांक cpqhp_वापस_board_resources(काष्ठा pci_func *func,
				 काष्ठा resource_lists *resources);
व्योम cpqhp_destroy_resource_list(काष्ठा resource_lists *resources);
पूर्णांक cpqhp_configure_device(काष्ठा controller *ctrl, काष्ठा pci_func *func);
पूर्णांक cpqhp_unconfigure_device(काष्ठा pci_func *func);

/* Global variables */
बाह्य पूर्णांक cpqhp_debug;
बाह्य पूर्णांक cpqhp_legacy_mode;
बाह्य काष्ठा controller *cpqhp_ctrl_list;
बाह्य काष्ठा pci_func *cpqhp_slot_list[256];
बाह्य काष्ठा irq_routing_table *cpqhp_routing_table;

/* these can be gotten rid of, but क्रम debugging they are purty */
बाह्य u8 cpqhp_nic_irq;
बाह्य u8 cpqhp_disk_irq;


/* अंतरभूत functions */

अटल अंतरभूत स्थिर अक्षर *slot_name(काष्ठा slot *slot)
अणु
	वापस hotplug_slot_name(&slot->hotplug_slot);
पूर्ण

अटल अंतरभूत काष्ठा slot *to_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

/*
 * वापस_resource
 *
 * Puts node back in the resource list poपूर्णांकed to by head
 */
अटल अंतरभूत व्योम वापस_resource(काष्ठा pci_resource **head,
				   काष्ठा pci_resource *node)
अणु
	अगर (!node || !head)
		वापस;
	node->next = *head;
	*head = node;
पूर्ण

अटल अंतरभूत व्योम set_SOGO(काष्ठा controller *ctrl)
अणु
	u16 misc;

	misc = पढ़ोw(ctrl->hpc_reg + MISC);
	misc = (misc | 0x0001) & 0xFFFB;
	ग_लिखोw(misc, ctrl->hpc_reg + MISC);
पूर्ण


अटल अंतरभूत व्योम amber_LED_on(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control |= (0x01010000L << slot);
	ग_लिखोl(led_control, ctrl->hpc_reg + LED_CONTROL);
पूर्ण


अटल अंतरभूत व्योम amber_LED_off(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control &= ~(0x01010000L << slot);
	ग_लिखोl(led_control, ctrl->hpc_reg + LED_CONTROL);
पूर्ण


अटल अंतरभूत पूर्णांक पढ़ो_amber_LED(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control &= (0x01010000L << slot);

	वापस led_control ? 1 : 0;
पूर्ण


अटल अंतरभूत व्योम green_LED_on(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control |= 0x0101L << slot;
	ग_लिखोl(led_control, ctrl->hpc_reg + LED_CONTROL);
पूर्ण

अटल अंतरभूत व्योम green_LED_off(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control &= ~(0x0101L << slot);
	ग_लिखोl(led_control, ctrl->hpc_reg + LED_CONTROL);
पूर्ण


अटल अंतरभूत व्योम green_LED_blink(काष्ठा controller *ctrl, u8 slot)
अणु
	u32 led_control;

	led_control = पढ़ोl(ctrl->hpc_reg + LED_CONTROL);
	led_control &= ~(0x0101L << slot);
	led_control |= (0x0001L << slot);
	ग_लिखोl(led_control, ctrl->hpc_reg + LED_CONTROL);
पूर्ण


अटल अंतरभूत व्योम slot_disable(काष्ठा controller *ctrl, u8 slot)
अणु
	u8 slot_enable;

	slot_enable = पढ़ोb(ctrl->hpc_reg + SLOT_ENABLE);
	slot_enable &= ~(0x01 << slot);
	ग_लिखोb(slot_enable, ctrl->hpc_reg + SLOT_ENABLE);
पूर्ण


अटल अंतरभूत व्योम slot_enable(काष्ठा controller *ctrl, u8 slot)
अणु
	u8 slot_enable;

	slot_enable = पढ़ोb(ctrl->hpc_reg + SLOT_ENABLE);
	slot_enable |= (0x01 << slot);
	ग_लिखोb(slot_enable, ctrl->hpc_reg + SLOT_ENABLE);
पूर्ण


अटल अंतरभूत u8 is_slot_enabled(काष्ठा controller *ctrl, u8 slot)
अणु
	u8 slot_enable;

	slot_enable = पढ़ोb(ctrl->hpc_reg + SLOT_ENABLE);
	slot_enable &= (0x01 << slot);
	वापस slot_enable ? 1 : 0;
पूर्ण


अटल अंतरभूत u8 पढ़ो_slot_enable(काष्ठा controller *ctrl)
अणु
	वापस पढ़ोb(ctrl->hpc_reg + SLOT_ENABLE);
पूर्ण


/**
 * get_controller_speed - find the current frequency/mode of controller.
 *
 * @ctrl: controller to get frequency/mode क्रम.
 *
 * Returns controller speed.
 */
अटल अंतरभूत u8 get_controller_speed(काष्ठा controller *ctrl)
अणु
	u8 curr_freq;
	u16 misc;

	अगर (ctrl->pcix_support) अणु
		curr_freq = पढ़ोb(ctrl->hpc_reg + NEXT_CURR_FREQ);
		अगर ((curr_freq & 0xB0) == 0xB0)
			वापस PCI_SPEED_133MHz_PCIX;
		अगर ((curr_freq & 0xA0) == 0xA0)
			वापस PCI_SPEED_100MHz_PCIX;
		अगर ((curr_freq & 0x90) == 0x90)
			वापस PCI_SPEED_66MHz_PCIX;
		अगर (curr_freq & 0x10)
			वापस PCI_SPEED_66MHz;

		वापस PCI_SPEED_33MHz;
	पूर्ण

	misc = पढ़ोw(ctrl->hpc_reg + MISC);
	वापस (misc & 0x0800) ? PCI_SPEED_66MHz : PCI_SPEED_33MHz;
पूर्ण


/**
 * get_adapter_speed - find the max supported frequency/mode of adapter.
 *
 * @ctrl: hotplug controller.
 * @hp_slot: hotplug slot where adapter is installed.
 *
 * Returns adapter speed.
 */
अटल अंतरभूत u8 get_adapter_speed(काष्ठा controller *ctrl, u8 hp_slot)
अणु
	u32 temp_dword = पढ़ोl(ctrl->hpc_reg + NON_INT_INPUT);
	dbg("slot: %d, PCIXCAP: %8x\n", hp_slot, temp_dword);
	अगर (ctrl->pcix_support) अणु
		अगर (temp_dword & (0x10000 << hp_slot))
			वापस PCI_SPEED_133MHz_PCIX;
		अगर (temp_dword & (0x100 << hp_slot))
			वापस PCI_SPEED_66MHz_PCIX;
	पूर्ण

	अगर (temp_dword & (0x01 << hp_slot))
		वापस PCI_SPEED_66MHz;

	वापस PCI_SPEED_33MHz;
पूर्ण

अटल अंतरभूत व्योम enable_slot_घातer(काष्ठा controller *ctrl, u8 slot)
अणु
	u8 slot_घातer;

	slot_घातer = पढ़ोb(ctrl->hpc_reg + SLOT_POWER);
	slot_घातer |= (0x01 << slot);
	ग_लिखोb(slot_घातer, ctrl->hpc_reg + SLOT_POWER);
पूर्ण

अटल अंतरभूत व्योम disable_slot_घातer(काष्ठा controller *ctrl, u8 slot)
अणु
	u8 slot_घातer;

	slot_घातer = पढ़ोb(ctrl->hpc_reg + SLOT_POWER);
	slot_घातer &= ~(0x01 << slot);
	ग_लिखोb(slot_घातer, ctrl->hpc_reg + SLOT_POWER);
पूर्ण


अटल अंतरभूत पूर्णांक cpq_get_attention_status(काष्ठा controller *ctrl, काष्ठा slot *slot)
अणु
	u8 hp_slot;

	hp_slot = slot->device - ctrl->slot_device_offset;

	वापस पढ़ो_amber_LED(ctrl, hp_slot);
पूर्ण


अटल अंतरभूत पूर्णांक get_slot_enabled(काष्ठा controller *ctrl, काष्ठा slot *slot)
अणु
	u8 hp_slot;

	hp_slot = slot->device - ctrl->slot_device_offset;

	वापस is_slot_enabled(ctrl, hp_slot);
पूर्ण


अटल अंतरभूत पूर्णांक cpq_get_latch_status(काष्ठा controller *ctrl,
				       काष्ठा slot *slot)
अणु
	u32 status;
	u8 hp_slot;

	hp_slot = slot->device - ctrl->slot_device_offset;
	dbg("%s: slot->device = %d, ctrl->slot_device_offset = %d\n",
	    __func__, slot->device, ctrl->slot_device_offset);

	status = (पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR) & (0x01L << hp_slot));

	वापस (status == 0) ? 1 : 0;
पूर्ण


अटल अंतरभूत पूर्णांक get_presence_status(काष्ठा controller *ctrl,
				      काष्ठा slot *slot)
अणु
	पूर्णांक presence_save = 0;
	u8 hp_slot;
	u32 tempdword;

	hp_slot = slot->device - ctrl->slot_device_offset;

	tempdword = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);
	presence_save = (पूर्णांक) ((((~tempdword) >> 23) | ((~tempdword) >> 15))
				>> hp_slot) & 0x02;

	वापस presence_save;
पूर्ण

अटल अंतरभूत पूर्णांक रुको_क्रम_ctrl_irq(काष्ठा controller *ctrl)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक retval = 0;

	dbg("%s - start\n", __func__);
	add_रुको_queue(&ctrl->queue, &रुको);
	/* Sleep क्रम up to 1 second to रुको क्रम the LED to change. */
	msleep_पूर्णांकerruptible(1000);
	हटाओ_रुको_queue(&ctrl->queue, &रुको);
	अगर (संकेत_pending(current))
		retval =  -EINTR;

	dbg("%s - end\n", __func__);
	वापस retval;
पूर्ण

#समावेश <यंत्र/pci_x86.h>
अटल अंतरभूत पूर्णांक cpqhp_routing_table_length(व्योम)
अणु
	BUG_ON(cpqhp_routing_table == शून्य);
	वापस ((cpqhp_routing_table->size - माप(काष्ठा irq_routing_table)) /
		माप(काष्ठा irq_info));
पूर्ण

#पूर्ण_अगर
