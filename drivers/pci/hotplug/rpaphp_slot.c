<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RPA Virtual I/O device functions
 * Copyright (C) 2004 Linda Xie <lxie@us.ibm.com>
 *
 * All rights reserved.
 *
 * Send feedback to <lxie@us.ibm.com>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/rtas.h>
#समावेश "rpaphp.h"

/* मुक्त up the memory used by a slot */
व्योम dealloc_slot_काष्ठा(काष्ठा slot *slot)
अणु
	of_node_put(slot->dn);
	kमुक्त(slot->name);
	kमुक्त(slot);
पूर्ण

काष्ठा slot *alloc_slot_काष्ठा(काष्ठा device_node *dn,
		पूर्णांक drc_index, अक्षर *drc_name, पूर्णांक घातer_करोमुख्य)
अणु
	काष्ठा slot *slot;

	slot = kzalloc(माप(काष्ठा slot), GFP_KERNEL);
	अगर (!slot)
		जाओ error_nomem;
	slot->name = kstrdup(drc_name, GFP_KERNEL);
	अगर (!slot->name)
		जाओ error_slot;
	slot->dn = of_node_get(dn);
	slot->index = drc_index;
	slot->घातer_करोमुख्य = घातer_करोमुख्य;
	slot->hotplug_slot.ops = &rpaphp_hotplug_slot_ops;

	वापस (slot);

error_slot:
	kमुक्त(slot);
error_nomem:
	वापस शून्य;
पूर्ण

अटल पूर्णांक is_रेजिस्टरed(काष्ठा slot *slot)
अणु
	काष्ठा slot *पंचांगp_slot;

	list_क्रम_each_entry(पंचांगp_slot, &rpaphp_slot_head, rpaphp_slot_list) अणु
		अगर (!म_भेद(पंचांगp_slot->name, slot->name))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rpaphp_deरेजिस्टर_slot(काष्ठा slot *slot)
अणु
	पूर्णांक retval = 0;
	काष्ठा hotplug_slot *php_slot = &slot->hotplug_slot;

	 dbg("%s - Entry: deregistering slot=%s\n",
		__func__, slot->name);

	list_del(&slot->rpaphp_slot_list);
	pci_hp_deरेजिस्टर(php_slot);
	dealloc_slot_काष्ठा(slot);

	dbg("%s - Exit: rc[%d]\n", __func__, retval);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rpaphp_deरेजिस्टर_slot);

पूर्णांक rpaphp_रेजिस्टर_slot(काष्ठा slot *slot)
अणु
	काष्ठा hotplug_slot *php_slot = &slot->hotplug_slot;
	काष्ठा device_node *child;
	u32 my_index;
	पूर्णांक retval;
	पूर्णांक slotno = -1;

	dbg("%s registering slot:path[%pOF] index[%x], name[%s] pdomain[%x] type[%d]\n",
		__func__, slot->dn, slot->index, slot->name,
		slot->घातer_करोमुख्य, slot->type);

	/* should not try to रेजिस्टर the same slot twice */
	अगर (is_रेजिस्टरed(slot)) अणु
		err("rpaphp_register_slot: slot[%s] is already registered\n", slot->name);
		वापस -EAGAIN;
	पूर्ण

	क्रम_each_child_of_node(slot->dn, child) अणु
		retval = of_property_पढ़ो_u32(child, "ibm,my-drc-index", &my_index);
		अगर (my_index == slot->index) अणु
			slotno = PCI_SLOT(PCI_DN(child)->devfn);
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	retval = pci_hp_रेजिस्टर(php_slot, slot->bus, slotno, slot->name);
	अगर (retval) अणु
		err("pci_hp_register failed with error %d\n", retval);
		वापस retval;
	पूर्ण

	/* add slot to our पूर्णांकernal list */
	list_add(&slot->rpaphp_slot_list, &rpaphp_slot_head);
	info("Slot [%s] registered\n", slot->name);
	वापस 0;
पूर्ण
