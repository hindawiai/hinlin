<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ACPI PCI Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)
 * Copyright (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)
 * Copyright (C) 2002,2003 NEC Corporation
 * Copyright (C) 2003-2005 Matthew Wilcox (willy@infradead.org)
 * Copyright (C) 2003-2005 Hewlett Packard
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>,
 *		    <t-kochi@bq.jp.nec.com>
 *
 */

#अगर_अघोषित _ACPIPHP_H
#घोषणा _ACPIPHP_H

#समावेश <linux/acpi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci_hotplug.h>

काष्ठा acpiphp_context;
काष्ठा acpiphp_bridge;
काष्ठा acpiphp_slot;

/*
 * काष्ठा slot - slot inक्रमmation क्रम each *physical* slot
 */
काष्ठा slot अणु
	काष्ठा hotplug_slot	hotplug_slot;
	काष्ठा acpiphp_slot	*acpi_slot;
	अचिन्हित पूर्णांक sun;	/* ACPI _SUN (Slot User Number) value */
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *slot_name(काष्ठा slot *slot)
अणु
	वापस hotplug_slot_name(&slot->hotplug_slot);
पूर्ण

अटल अंतरभूत काष्ठा slot *to_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

/*
 * काष्ठा acpiphp_bridge - PCI bridge inक्रमmation
 *
 * क्रम each bridge device in ACPI namespace
 */
काष्ठा acpiphp_bridge अणु
	काष्ठा list_head list;
	काष्ठा list_head slots;
	काष्ठा kref ref;

	काष्ठा acpiphp_context *context;

	पूर्णांक nr_slots;

	/* This bus (host bridge) or Secondary bus (PCI-to-PCI bridge) */
	काष्ठा pci_bus *pci_bus;

	/* PCI-to-PCI bridge device */
	काष्ठा pci_dev *pci_dev;

	bool is_going_away;
पूर्ण;


/*
 * काष्ठा acpiphp_slot - PCI slot inक्रमmation
 *
 * PCI slot inक्रमmation क्रम each *physical* PCI slot
 */
काष्ठा acpiphp_slot अणु
	काष्ठा list_head node;
	काष्ठा pci_bus *bus;
	काष्ठा list_head funcs;		/* one slot may have dअगरferent
					   objects (i.e. क्रम each function) */
	काष्ठा slot *slot;

	u8		device;		/* pci device# */
	u32		flags;		/* see below */
पूर्ण;


/*
 * काष्ठा acpiphp_func - PCI function inक्रमmation
 *
 * PCI function inक्रमmation क्रम each object in ACPI namespace
 * typically 8 objects per slot (i.e. क्रम each PCI function)
 */
काष्ठा acpiphp_func अणु
	काष्ठा acpiphp_bridge *parent;
	काष्ठा acpiphp_slot *slot;

	काष्ठा list_head sibling;

	u8		function;	/* pci function# */
	u32		flags;		/* see below */
पूर्ण;

काष्ठा acpiphp_context अणु
	काष्ठा acpi_hotplug_context hp;
	काष्ठा acpiphp_func func;
	काष्ठा acpiphp_bridge *bridge;
	अचिन्हित पूर्णांक refcount;
पूर्ण;

अटल अंतरभूत काष्ठा acpiphp_context *to_acpiphp_context(काष्ठा acpi_hotplug_context *hp)
अणु
	वापस container_of(hp, काष्ठा acpiphp_context, hp);
पूर्ण

अटल अंतरभूत काष्ठा acpiphp_context *func_to_context(काष्ठा acpiphp_func *func)
अणु
	वापस container_of(func, काष्ठा acpiphp_context, func);
पूर्ण

अटल अंतरभूत काष्ठा acpi_device *func_to_acpi_device(काष्ठा acpiphp_func *func)
अणु
	वापस func_to_context(func)->hp.self;
पूर्ण

अटल अंतरभूत acpi_handle func_to_handle(काष्ठा acpiphp_func *func)
अणु
	वापस func_to_acpi_device(func)->handle;
पूर्ण

काष्ठा acpiphp_root_context अणु
	काष्ठा acpi_hotplug_context hp;
	काष्ठा acpiphp_bridge *root_bridge;
पूर्ण;

अटल अंतरभूत काष्ठा acpiphp_root_context *to_acpiphp_root_context(काष्ठा acpi_hotplug_context *hp)
अणु
	वापस container_of(hp, काष्ठा acpiphp_root_context, hp);
पूर्ण

/*
 * काष्ठा acpiphp_attention_info - device specअगरic attention registration
 *
 * ACPI has no generic method of setting/getting attention status
 * this allows क्रम device specअगरic driver registration
 */
काष्ठा acpiphp_attention_info अणु
	पूर्णांक (*set_attn)(काष्ठा hotplug_slot *slot, u8 status);
	पूर्णांक (*get_attn)(काष्ठा hotplug_slot *slot, u8 *status);
	काष्ठा module *owner;
पूर्ण;

/* ACPI _STA method value (ignore bit 4; battery present) */
#घोषणा ACPI_STA_ALL			(0x0000000f)

/* slot flags */

#घोषणा SLOT_ENABLED		(0x00000001)
#घोषणा SLOT_IS_GOING_AWAY	(0x00000002)

/* function flags */

#घोषणा FUNC_HAS_STA		(0x00000001)
#घोषणा FUNC_HAS_EJ0		(0x00000002)

/* function prototypes */

/* acpiphp_core.c */
पूर्णांक acpiphp_रेजिस्टर_attention(काष्ठा acpiphp_attention_info *info);
पूर्णांक acpiphp_unरेजिस्टर_attention(काष्ठा acpiphp_attention_info *info);
पूर्णांक acpiphp_रेजिस्टर_hotplug_slot(काष्ठा acpiphp_slot *slot, अचिन्हित पूर्णांक sun);
व्योम acpiphp_unरेजिस्टर_hotplug_slot(काष्ठा acpiphp_slot *slot);

पूर्णांक acpiphp_enable_slot(काष्ठा acpiphp_slot *slot);
पूर्णांक acpiphp_disable_slot(काष्ठा acpiphp_slot *slot);
u8 acpiphp_get_घातer_status(काष्ठा acpiphp_slot *slot);
u8 acpiphp_get_attention_status(काष्ठा acpiphp_slot *slot);
u8 acpiphp_get_latch_status(काष्ठा acpiphp_slot *slot);
u8 acpiphp_get_adapter_status(काष्ठा acpiphp_slot *slot);

/* variables */
बाह्य bool acpiphp_disabled;

#पूर्ण_अगर /* _ACPIPHP_H */
