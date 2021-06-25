<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Hot Plug Controller Driver क्रम RPA-compliant PPC64 platक्रमm.
 * Copyright (C) 2003 Linda Xie <lxie@us.ibm.com>
 *
 * All rights reserved.
 *
 * Send feedback to <lxie@us.ibm.com>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh.h>       /* क्रम eeh_add_device() */
#समावेश <यंत्र/rtas.h>		/* rtas_call */
#समावेश <यंत्र/pci-bridge.h>	/* क्रम pci_controller */
#समावेश "../pci.h"		/* क्रम pci_add_new_bus */
				/* and pci_करो_scan_bus */
#समावेश "rpaphp.h"

bool rpaphp_debug;
LIST_HEAD(rpaphp_slot_head);
EXPORT_SYMBOL_GPL(rpaphp_slot_head);

#घोषणा DRIVER_VERSION	"0.1"
#घोषणा DRIVER_AUTHOR	"Linda Xie <lxie@us.ibm.com>"
#घोषणा DRIVER_DESC	"RPA HOT Plug PCI Controller Driver"

#घोषणा MAX_LOC_CODE 128

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param_named(debug, rpaphp_debug, bool, 0644);

/**
 * set_attention_status - set attention LED
 * @hotplug_slot: target &hotplug_slot
 * @value: LED control value
 *
 * echo 0 > attention -- set LED OFF
 * echo 1 > attention -- set LED ON
 * echo 2 > attention -- set LED ID(identअगरy, light is blinking)
 */
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 value)
अणु
	पूर्णांक rc;
	काष्ठा slot *slot = to_slot(hotplug_slot);

	चयन (value) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		अवरोध;
	शेष:
		value = 1;
		अवरोध;
	पूर्ण

	rc = rtas_set_indicator(DR_INDICATOR, slot->index, value);
	अगर (!rc)
		slot->attention_status = value;

	वापस rc;
पूर्ण

/**
 * get_घातer_status - get घातer status of a slot
 * @hotplug_slot: slot to get status
 * @value: poपूर्णांकer to store status
 */
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक retval, level;
	काष्ठा slot *slot = to_slot(hotplug_slot);

	retval = rtas_get_घातer_level(slot->घातer_करोमुख्य, &level);
	अगर (!retval)
		*value = level;
	वापस retval;
पूर्ण

/**
 * get_attention_status - get attention LED status
 * @hotplug_slot: slot to get status
 * @value: poपूर्णांकer to store status
 */
अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	*value = slot->attention_status;
	वापस 0;
पूर्ण

अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	पूर्णांक rc, state;

	rc = rpaphp_get_sensor_state(slot, &state);

	*value = NOT_VALID;
	अगर (rc)
		वापस rc;

	अगर (state == EMPTY)
		*value = EMPTY;
	अन्यथा अगर (state == PRESENT)
		*value = slot->state;

	वापस 0;
पूर्ण

अटल क्रमागत pci_bus_speed get_max_bus_speed(काष्ठा slot *slot)
अणु
	क्रमागत pci_bus_speed speed;
	चयन (slot->type) अणु
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
	हाल 5:
	हाल 6:
		speed = PCI_SPEED_33MHz;	/* speed क्रम हाल 1-6 */
		अवरोध;
	हाल 7:
	हाल 8:
		speed = PCI_SPEED_66MHz;
		अवरोध;
	हाल 11:
	हाल 14:
		speed = PCI_SPEED_66MHz_PCIX;
		अवरोध;
	हाल 12:
	हाल 15:
		speed = PCI_SPEED_100MHz_PCIX;
		अवरोध;
	हाल 13:
	हाल 16:
		speed = PCI_SPEED_133MHz_PCIX;
		अवरोध;
	शेष:
		speed = PCI_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस speed;
पूर्ण

अटल पूर्णांक get_children_props(काष्ठा device_node *dn, स्थिर __be32 **drc_indexes,
			      स्थिर __be32 **drc_names, स्थिर __be32 **drc_types,
			      स्थिर __be32 **drc_घातer_करोमुख्यs)
अणु
	स्थिर __be32 *indexes, *names, *types, *करोमुख्यs;

	indexes = of_get_property(dn, "ibm,drc-indexes", शून्य);
	names = of_get_property(dn, "ibm,drc-names", शून्य);
	types = of_get_property(dn, "ibm,drc-types", शून्य);
	करोमुख्यs = of_get_property(dn, "ibm,drc-power-domains", शून्य);

	अगर (!indexes || !names || !types || !करोमुख्यs) अणु
		/* Slot करोes not have dynamically-removable children */
		वापस -EINVAL;
	पूर्ण
	अगर (drc_indexes)
		*drc_indexes = indexes;
	अगर (drc_names)
		/* &drc_names[1] contains शून्य terminated slot names */
		*drc_names = names;
	अगर (drc_types)
		/* &drc_types[1] contains शून्य terminated slot types */
		*drc_types = types;
	अगर (drc_घातer_करोमुख्यs)
		*drc_घातer_करोमुख्यs = करोमुख्यs;

	वापस 0;
पूर्ण


/* Verअगरy the existence of 'drc_name' and/or 'drc_type' within the
 * current node.  First obtain its my-drc-index property.  Next,
 * obtain the DRC info from its parent.  Use the my-drc-index क्रम
 * correlation, and obtain/validate the requested properties.
 */

अटल पूर्णांक rpaphp_check_drc_props_v1(काष्ठा device_node *dn, अक्षर *drc_name,
				अक्षर *drc_type, अचिन्हित पूर्णांक my_index)
अणु
	अक्षर *name_पंचांगp, *type_पंचांगp;
	स्थिर __be32 *indexes, *names;
	स्थिर __be32 *types, *करोमुख्यs;
	पूर्णांक i, rc;

	rc = get_children_props(dn->parent, &indexes, &names, &types, &करोमुख्यs);
	अगर (rc < 0) अणु
		वापस -EINVAL;
	पूर्ण

	name_पंचांगp = (अक्षर *) &names[1];
	type_पंचांगp = (अक्षर *) &types[1];

	/* Iterate through parent properties, looking क्रम my-drc-index */
	क्रम (i = 0; i < be32_to_cpu(indexes[0]); i++) अणु
		अगर (be32_to_cpu(indexes[i + 1]) == my_index)
			अवरोध;

		name_पंचांगp += (म_माप(name_पंचांगp) + 1);
		type_पंचांगp += (म_माप(type_पंचांगp) + 1);
	पूर्ण

	अगर (((drc_name == शून्य) || (drc_name && !म_भेद(drc_name, name_पंचांगp))) &&
	    ((drc_type == शून्य) || (drc_type && !म_भेद(drc_type, type_पंचांगp))))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rpaphp_check_drc_props_v2(काष्ठा device_node *dn, अक्षर *drc_name,
				अक्षर *drc_type, अचिन्हित पूर्णांक my_index)
अणु
	काष्ठा property *info;
	अचिन्हित पूर्णांक entries;
	काष्ठा of_drc_info drc;
	स्थिर __be32 *value;
	अक्षर cell_drc_name[MAX_DRC_NAME_LEN];
	पूर्णांक j;

	info = of_find_property(dn->parent, "ibm,drc-info", शून्य);
	अगर (info == शून्य)
		वापस -EINVAL;

	value = of_prop_next_u32(info, शून्य, &entries);
	अगर (!value)
		वापस -EINVAL;
	अन्यथा
		value++;

	क्रम (j = 0; j < entries; j++) अणु
		of_पढ़ो_drc_info_cell(&info, &value, &drc);

		/* Should now know end of current entry */

		/* Found it */
		अगर (my_index >= drc.drc_index_start && my_index <= drc.last_drc_index) अणु
			पूर्णांक index = my_index - drc.drc_index_start;
			प्र_लिखो(cell_drc_name, "%s%d", drc.drc_name_prefix,
				drc.drc_name_suffix_start + index);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (((drc_name == शून्य) ||
	     (drc_name && !म_भेद(drc_name, cell_drc_name))) &&
	    ((drc_type == शून्य) ||
	     (drc_type && !म_भेद(drc_type, drc.drc_type))))
		वापस 0;

	वापस -EINVAL;
पूर्ण

पूर्णांक rpaphp_check_drc_props(काष्ठा device_node *dn, अक्षर *drc_name,
			अक्षर *drc_type)
अणु
	स्थिर __be32 *my_index;

	my_index = of_get_property(dn, "ibm,my-drc-index", शून्य);
	अगर (!my_index) अणु
		/* Node isn't DLPAR/hotplug capable */
		वापस -EINVAL;
	पूर्ण

	अगर (of_find_property(dn->parent, "ibm,drc-info", शून्य))
		वापस rpaphp_check_drc_props_v2(dn, drc_name, drc_type,
						be32_to_cpu(*my_index));
	अन्यथा
		वापस rpaphp_check_drc_props_v1(dn, drc_name, drc_type,
						be32_to_cpu(*my_index));
पूर्ण
EXPORT_SYMBOL_GPL(rpaphp_check_drc_props);


अटल पूर्णांक is_php_type(अक्षर *drc_type)
अणु
	अक्षर *endptr;

	/* PCI Hotplug nodes have an पूर्णांकeger क्रम drc_type */
	simple_म_से_अदीर्घ(drc_type, &endptr, 10);
	अगर (endptr == drc_type)
		वापस 0;

	वापस 1;
पूर्ण

/**
 * is_php_dn() - वापस 1 अगर this is a hotpluggable pci slot, अन्यथा 0
 * @dn: target &device_node
 * @indexes: passed to get_children_props()
 * @names: passed to get_children_props()
 * @types: वापसed from get_children_props()
 * @घातer_करोमुख्यs:
 *
 * This routine will वापस true only अगर the device node is
 * a hotpluggable slot. This routine will वापस false
 * क्रम built-in pci slots (even when the built-in slots are
 * dlparable.)
 */
अटल पूर्णांक is_php_dn(काष्ठा device_node *dn, स्थिर __be32 **indexes,
		     स्थिर __be32 **names, स्थिर __be32 **types,
		     स्थिर __be32 **घातer_करोमुख्यs)
अणु
	स्थिर __be32 *drc_types;
	पूर्णांक rc;

	rc = get_children_props(dn, indexes, names, &drc_types, घातer_करोमुख्यs);
	अगर (rc < 0)
		वापस 0;

	अगर (!is_php_type((अक्षर *) &drc_types[1]))
		वापस 0;

	*types = drc_types;
	वापस 1;
पूर्ण

अटल पूर्णांक rpaphp_drc_info_add_slot(काष्ठा device_node *dn)
अणु
	काष्ठा slot *slot;
	काष्ठा property *info;
	काष्ठा of_drc_info drc;
	अक्षर drc_name[MAX_DRC_NAME_LEN];
	स्थिर __be32 *cur;
	u32 count;
	पूर्णांक retval = 0;

	info = of_find_property(dn, "ibm,drc-info", शून्य);
	अगर (!info)
		वापस 0;

	cur = of_prop_next_u32(info, शून्य, &count);
	अगर (cur)
		cur++;
	अन्यथा
		वापस 0;

	of_पढ़ो_drc_info_cell(&info, &cur, &drc);
	अगर (!is_php_type(drc.drc_type))
		वापस 0;

	प्र_लिखो(drc_name, "%s%d", drc.drc_name_prefix, drc.drc_name_suffix_start);

	slot = alloc_slot_काष्ठा(dn, drc.drc_index_start, drc_name, drc.drc_घातer_करोमुख्य);
	अगर (!slot)
		वापस -ENOMEM;

	slot->type = simple_म_से_अदीर्घ(drc.drc_type, शून्य, 10);
	retval = rpaphp_enable_slot(slot);
	अगर (!retval)
		retval = rpaphp_रेजिस्टर_slot(slot);

	अगर (retval)
		dealloc_slot_काष्ठा(slot);

	वापस retval;
पूर्ण

अटल पूर्णांक rpaphp_drc_add_slot(काष्ठा device_node *dn)
अणु
	काष्ठा slot *slot;
	पूर्णांक retval = 0;
	पूर्णांक i;
	स्थिर __be32 *indexes, *names, *types, *घातer_करोमुख्यs;
	अक्षर *name, *type;

	/* If this is not a hotplug slot, वापस without करोing anything. */
	अगर (!is_php_dn(dn, &indexes, &names, &types, &घातer_करोमुख्यs))
		वापस 0;

	dbg("Entry %s: dn=%pOF\n", __func__, dn);

	/* रेजिस्टर PCI devices */
	name = (अक्षर *) &names[1];
	type = (अक्षर *) &types[1];
	क्रम (i = 0; i < be32_to_cpu(indexes[0]); i++) अणु
		पूर्णांक index;

		index = be32_to_cpu(indexes[i + 1]);
		slot = alloc_slot_काष्ठा(dn, index, name,
					 be32_to_cpu(घातer_करोमुख्यs[i + 1]));
		अगर (!slot)
			वापस -ENOMEM;

		slot->type = simple_म_से_अदीर्घ(type, शून्य, 10);

		dbg("Found drc-index:0x%x drc-name:%s drc-type:%s\n",
				index, name, type);

		retval = rpaphp_enable_slot(slot);
		अगर (!retval)
			retval = rpaphp_रेजिस्टर_slot(slot);

		अगर (retval)
			dealloc_slot_काष्ठा(slot);

		name += म_माप(name) + 1;
		type += म_माप(type) + 1;
	पूर्ण
	dbg("%s - Exit: rc[%d]\n", __func__, retval);

	/* XXX FIXME: reports a failure only अगर last entry in loop failed */
	वापस retval;
पूर्ण

/**
 * rpaphp_add_slot -- declare a hotplug slot to the hotplug subप्रणाली.
 * @dn: device node of slot
 *
 * This subroutine will रेजिस्टर a hotpluggable slot with the
 * PCI hotplug infraकाष्ठाure. This routine is typically called
 * during boot समय, अगर the hotplug slots are present at boot समय,
 * or is called later, by the dlpar add code, अगर the slot is
 * being dynamically added during runसमय.
 *
 * If the device node poपूर्णांकs at an embedded (built-in) slot, this
 * routine will just वापस without करोing anything, since embedded
 * slots cannot be hotplugged.
 *
 * To हटाओ a slot, it suffices to call rpaphp_deरेजिस्टर_slot().
 */
पूर्णांक rpaphp_add_slot(काष्ठा device_node *dn)
अणु
	अगर (!of_node_name_eq(dn, "pci"))
		वापस 0;

	अगर (of_find_property(dn, "ibm,drc-info", शून्य))
		वापस rpaphp_drc_info_add_slot(dn);
	अन्यथा
		वापस rpaphp_drc_add_slot(dn);
पूर्ण
EXPORT_SYMBOL_GPL(rpaphp_add_slot);

अटल व्योम __निकास cleanup_slots(व्योम)
अणु
	काष्ठा slot *slot, *next;

	/*
	 * Unरेजिस्टर all of our slots with the pci_hotplug subप्रणाली,
	 * and मुक्त up all memory that we had allocated.
	 */

	list_क्रम_each_entry_safe(slot, next, &rpaphp_slot_head,
				 rpaphp_slot_list) अणु
		list_del(&slot->rpaphp_slot_list);
		pci_hp_deरेजिस्टर(&slot->hotplug_slot);
		dealloc_slot_काष्ठा(slot);
	पूर्ण
पूर्ण

अटल पूर्णांक __init rpaphp_init(व्योम)
अणु
	काष्ठा device_node *dn;

	info(DRIVER_DESC " version: " DRIVER_VERSION "\n");

	क्रम_each_node_by_name(dn, "pci")
		rpaphp_add_slot(dn);

	वापस 0;
पूर्ण

अटल व्योम __निकास rpaphp_निकास(व्योम)
अणु
	cleanup_slots();
पूर्ण

अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	पूर्णांक state;
	पूर्णांक retval;

	अगर (slot->state == CONFIGURED)
		वापस 0;

	retval = rpaphp_get_sensor_state(slot, &state);
	अगर (retval)
		वापस retval;

	अगर (state == PRESENT) अणु
		pseries_eeh_init_edev_recursive(PCI_DN(slot->dn));

		pci_lock_rescan_हटाओ();
		pci_hp_add_devices(slot->bus);
		pci_unlock_rescan_हटाओ();
		slot->state = CONFIGURED;
	पूर्ण अन्यथा अगर (state == EMPTY) अणु
		slot->state = EMPTY;
	पूर्ण अन्यथा अणु
		err("%s: slot[%s] is in invalid state\n", __func__, slot->name);
		slot->state = NOT_VALID;
		वापस -EINVAL;
	पूर्ण

	slot->bus->max_bus_speed = get_max_bus_speed(slot);
	वापस 0;
पूर्ण

अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	अगर (slot->state == NOT_CONFIGURED)
		वापस -EINVAL;

	pci_lock_rescan_हटाओ();
	pci_hp_हटाओ_devices(slot->bus);
	pci_unlock_rescan_हटाओ();
	vm_unmap_aliases();

	slot->state = NOT_CONFIGURED;
	वापस 0;
पूर्ण

स्थिर काष्ठा hotplug_slot_ops rpaphp_hotplug_slot_ops = अणु
	.enable_slot = enable_slot,
	.disable_slot = disable_slot,
	.set_attention_status = set_attention_status,
	.get_घातer_status = get_घातer_status,
	.get_attention_status = get_attention_status,
	.get_adapter_status = get_adapter_status,
पूर्ण;

module_init(rpaphp_init);
module_निकास(rpaphp_निकास);
