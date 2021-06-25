<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PCI HotPlug Core Functions
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <kristen.c.accardi@पूर्णांकel.com>
 *
 */
#अगर_अघोषित _PCI_HOTPLUG_H
#घोषणा _PCI_HOTPLUG_H

/**
 * काष्ठा hotplug_slot_ops -the callbacks that the hotplug pci core can use
 * @enable_slot: Called when the user wants to enable a specअगरic pci slot
 * @disable_slot: Called when the user wants to disable a specअगरic pci slot
 * @set_attention_status: Called to set the specअगरic slot's attention LED to
 * the specअगरied value
 * @hardware_test: Called to run a specअगरied hardware test on the specअगरied
 * slot.
 * @get_घातer_status: Called to get the current घातer status of a slot.
 * @get_attention_status: Called to get the current attention status of a slot.
 * @get_latch_status: Called to get the current latch status of a slot.
 * @get_adapter_status: Called to get see अगर an adapter is present in the slot or not.
 * @reset_slot: Optional पूर्णांकerface to allow override of a bus reset क्रम the
 *	slot क्रम हालs where a secondary bus reset can result in spurious
 *	hotplug events or where a slot can be reset independent of the bus.
 *
 * The table of function poपूर्णांकers that is passed to the hotplug pci core by a
 * hotplug pci driver.  These functions are called by the hotplug pci core when
 * the user wants to करो something to a specअगरic slot (query it क्रम inक्रमmation,
 * set an LED, enable / disable घातer, etc.)
 */
काष्ठा hotplug_slot_ops अणु
	पूर्णांक (*enable_slot)		(काष्ठा hotplug_slot *slot);
	पूर्णांक (*disable_slot)		(काष्ठा hotplug_slot *slot);
	पूर्णांक (*set_attention_status)	(काष्ठा hotplug_slot *slot, u8 value);
	पूर्णांक (*hardware_test)		(काष्ठा hotplug_slot *slot, u32 value);
	पूर्णांक (*get_घातer_status)		(काष्ठा hotplug_slot *slot, u8 *value);
	पूर्णांक (*get_attention_status)	(काष्ठा hotplug_slot *slot, u8 *value);
	पूर्णांक (*get_latch_status)		(काष्ठा hotplug_slot *slot, u8 *value);
	पूर्णांक (*get_adapter_status)	(काष्ठा hotplug_slot *slot, u8 *value);
	पूर्णांक (*reset_slot)		(काष्ठा hotplug_slot *slot, पूर्णांक probe);
पूर्ण;

/**
 * काष्ठा hotplug_slot - used to रेजिस्टर a physical slot with the hotplug pci core
 * @ops: poपूर्णांकer to the &काष्ठा hotplug_slot_ops to be used क्रम this slot
 * @owner: The module owner of this काष्ठाure
 * @mod_name: The module name (KBUILD_MODNAME) of this काष्ठाure
 */
काष्ठा hotplug_slot अणु
	स्थिर काष्ठा hotplug_slot_ops	*ops;

	/* Variables below this are क्रम use only by the hotplug pci core. */
	काष्ठा list_head		slot_list;
	काष्ठा pci_slot			*pci_slot;
	काष्ठा module			*owner;
	स्थिर अक्षर			*mod_name;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *hotplug_slot_name(स्थिर काष्ठा hotplug_slot *slot)
अणु
	वापस pci_slot_name(slot->pci_slot);
पूर्ण

पूर्णांक __pci_hp_रेजिस्टर(काष्ठा hotplug_slot *slot, काष्ठा pci_bus *pbus, पूर्णांक nr,
		      स्थिर अक्षर *name, काष्ठा module *owner,
		      स्थिर अक्षर *mod_name);
पूर्णांक __pci_hp_initialize(काष्ठा hotplug_slot *slot, काष्ठा pci_bus *bus, पूर्णांक nr,
			स्थिर अक्षर *name, काष्ठा module *owner,
			स्थिर अक्षर *mod_name);
पूर्णांक pci_hp_add(काष्ठा hotplug_slot *slot);

व्योम pci_hp_del(काष्ठा hotplug_slot *slot);
व्योम pci_hp_destroy(काष्ठा hotplug_slot *slot);
व्योम pci_hp_deरेजिस्टर(काष्ठा hotplug_slot *slot);

/* use a define to aव्योम include chaining to get THIS_MODULE & मित्रs */
#घोषणा pci_hp_रेजिस्टर(slot, pbus, devnr, name) \
	__pci_hp_रेजिस्टर(slot, pbus, devnr, name, THIS_MODULE, KBUILD_MODNAME)
#घोषणा pci_hp_initialize(slot, bus, nr, name) \
	__pci_hp_initialize(slot, bus, nr, name, THIS_MODULE, KBUILD_MODNAME)

#अगर_घोषित CONFIG_ACPI
#समावेश <linux/acpi.h>
bool pciehp_is_native(काष्ठा pci_dev *bridge);
पूर्णांक acpi_get_hp_hw_control_from_firmware(काष्ठा pci_dev *bridge);
bool shpchp_is_native(काष्ठा pci_dev *bridge);
पूर्णांक acpi_pci_check_ejectable(काष्ठा pci_bus *pbus, acpi_handle handle);
पूर्णांक acpi_pci_detect_ejectable(acpi_handle handle);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_get_hp_hw_control_from_firmware(काष्ठा pci_dev *bridge)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool pciehp_is_native(काष्ठा pci_dev *bridge) अणु वापस true; पूर्ण
अटल अंतरभूत bool shpchp_is_native(काष्ठा pci_dev *bridge) अणु वापस true; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool hotplug_is_native(काष्ठा pci_dev *bridge)
अणु
	वापस pciehp_is_native(bridge) || shpchp_is_native(bridge);
पूर्ण
#पूर्ण_अगर
