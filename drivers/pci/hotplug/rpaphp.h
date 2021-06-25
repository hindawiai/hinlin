<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PCI Hot Plug Controller Driver क्रम RPA-compliant PPC64 platक्रमm.
 *
 * Copyright (C) 2003 Linda Xie <lxie@us.ibm.com>
 *
 * All rights reserved.
 *
 * Send feedback to <lxie@us.ibm.com>,
 *
 */

#अगर_अघोषित _PPC64PHP_H
#घोषणा _PPC64PHP_H

#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>

#घोषणा DR_INDICATOR 9002
#घोषणा DR_ENTITY_SENSE 9003

#घोषणा POWER_ON	100
#घोषणा POWER_OFF	0

#घोषणा LED_OFF		0
#घोषणा LED_ON		1	/* continuous on */
#घोषणा LED_ID		2	/* slow blinking */
#घोषणा LED_ACTION	3	/* fast blinking */

/* Sensor values from rtas_get-sensor */
#घोषणा EMPTY           0	/* No card in slot */
#घोषणा PRESENT         1	/* Card in slot */

#घोषणा MY_NAME "rpaphp"
बाह्य bool rpaphp_debug;
#घोषणा dbg(क्रमmat, arg...)					\
	करो अणु							\
		अगर (rpaphp_debug)				\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat,	\
				MY_NAME, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)

/* slot states */

#घोषणा	NOT_VALID	3
#घोषणा	NOT_CONFIGURED	2
#घोषणा	CONFIGURED	1
#घोषणा	EMPTY		0

/* DRC स्थिरants */

#घोषणा MAX_DRC_NAME_LEN 64

/*
 * काष्ठा slot - slot inक्रमmation क्रम each *physical* slot
 */
काष्ठा slot अणु
	काष्ठा list_head rpaphp_slot_list;
	पूर्णांक state;
	u32 index;
	u32 type;
	u32 घातer_करोमुख्य;
	u8 attention_status;
	अक्षर *name;
	काष्ठा device_node *dn;
	काष्ठा pci_bus *bus;
	काष्ठा list_head *pci_devs;
	काष्ठा hotplug_slot hotplug_slot;
पूर्ण;

बाह्य स्थिर काष्ठा hotplug_slot_ops rpaphp_hotplug_slot_ops;
बाह्य काष्ठा list_head rpaphp_slot_head;

अटल अंतरभूत काष्ठा slot *to_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

/* function prototypes */

/* rpaphp_pci.c */
पूर्णांक rpaphp_enable_slot(काष्ठा slot *slot);
पूर्णांक rpaphp_get_sensor_state(काष्ठा slot *slot, पूर्णांक *state);

/* rpaphp_core.c */
पूर्णांक rpaphp_add_slot(काष्ठा device_node *dn);
पूर्णांक rpaphp_check_drc_props(काष्ठा device_node *dn, अक्षर *drc_name,
		अक्षर *drc_type);

/* rpaphp_slot.c */
व्योम dealloc_slot_काष्ठा(काष्ठा slot *slot);
काष्ठा slot *alloc_slot_काष्ठा(काष्ठा device_node *dn, पूर्णांक drc_index, अक्षर *drc_name, पूर्णांक घातer_करोमुख्य);
पूर्णांक rpaphp_रेजिस्टर_slot(काष्ठा slot *slot);
पूर्णांक rpaphp_deरेजिस्टर_slot(काष्ठा slot *slot);

#पूर्ण_अगर				/* _PPC64PHP_H */
