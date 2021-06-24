<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * CompactPCI Hot Plug Core Functions
 *
 * Copyright (C) 2002 SOMA Networks, Inc.
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#अगर_अघोषित _CPCI_HOTPLUG_H
#घोषणा _CPCI_HOTPLUG_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>

/* PICMG 2.1 R2.0 HS CSR bits: */
#घोषणा HS_CSR_INS	0x0080
#घोषणा HS_CSR_EXT	0x0040
#घोषणा HS_CSR_PI	0x0030
#घोषणा HS_CSR_LOO	0x0008
#घोषणा HS_CSR_PIE	0x0004
#घोषणा HS_CSR_EIM	0x0002
#घोषणा HS_CSR_DHA	0x0001

काष्ठा slot अणु
	u8 number;
	अचिन्हित पूर्णांक devfn;
	काष्ठा pci_bus *bus;
	काष्ठा pci_dev *dev;
	अचिन्हित पूर्णांक latch_status:1;
	अचिन्हित पूर्णांक adapter_status:1;
	अचिन्हित पूर्णांक extracting;
	काष्ठा hotplug_slot hotplug_slot;
	काष्ठा list_head slot_list;
पूर्ण;

काष्ठा cpci_hp_controller_ops अणु
	पूर्णांक (*query_क्रमागत)(व्योम);
	पूर्णांक (*enable_irq)(व्योम);
	पूर्णांक (*disable_irq)(व्योम);
	पूर्णांक (*check_irq)(व्योम *dev_id);
	पूर्णांक (*hardware_test)(काष्ठा slot *slot, u32 value);
	u8  (*get_घातer)(काष्ठा slot *slot);
	पूर्णांक (*set_घातer)(काष्ठा slot *slot, पूर्णांक value);
पूर्ण;

काष्ठा cpci_hp_controller अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ irq_flags;
	अक्षर *devname;
	व्योम *dev_id;
	अक्षर *name;
	काष्ठा cpci_hp_controller_ops *ops;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *slot_name(काष्ठा slot *slot)
अणु
	वापस hotplug_slot_name(&slot->hotplug_slot);
पूर्ण

अटल अंतरभूत काष्ठा slot *to_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

पूर्णांक cpci_hp_रेजिस्टर_controller(काष्ठा cpci_hp_controller *controller);
पूर्णांक cpci_hp_unरेजिस्टर_controller(काष्ठा cpci_hp_controller *controller);
पूर्णांक cpci_hp_रेजिस्टर_bus(काष्ठा pci_bus *bus, u8 first, u8 last);
पूर्णांक cpci_hp_unरेजिस्टर_bus(काष्ठा pci_bus *bus);
पूर्णांक cpci_hp_start(व्योम);
पूर्णांक cpci_hp_stop(व्योम);

/*
 * Internal function prototypes, these functions should not be used by
 * board/chassis drivers.
 */
u8 cpci_get_attention_status(काष्ठा slot *slot);
u8 cpci_get_latch_status(काष्ठा slot *slot);
u8 cpci_get_adapter_status(काष्ठा slot *slot);
u16 cpci_get_hs_csr(काष्ठा slot *slot);
पूर्णांक cpci_set_attention_status(काष्ठा slot *slot, पूर्णांक status);
पूर्णांक cpci_check_and_clear_ins(काष्ठा slot *slot);
पूर्णांक cpci_check_ext(काष्ठा slot *slot);
पूर्णांक cpci_clear_ext(काष्ठा slot *slot);
पूर्णांक cpci_led_on(काष्ठा slot *slot);
पूर्णांक cpci_led_off(काष्ठा slot *slot);
पूर्णांक cpci_configure_slot(काष्ठा slot *slot);
पूर्णांक cpci_unconfigure_slot(काष्ठा slot *slot);

#अगर_घोषित CONFIG_HOTPLUG_PCI_CPCI
पूर्णांक cpci_hotplug_init(पूर्णांक debug);
#अन्यथा
अटल अंतरभूत पूर्णांक cpci_hotplug_init(पूर्णांक debug) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _CPCI_HOTPLUG_H */
