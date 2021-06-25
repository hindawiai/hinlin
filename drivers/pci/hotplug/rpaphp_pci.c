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
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/machdep.h>

#समावेश "../pci.h"		/* क्रम pci_add_new_bus */
#समावेश "rpaphp.h"

पूर्णांक rpaphp_get_sensor_state(काष्ठा slot *slot, पूर्णांक *state)
अणु
	पूर्णांक rc;
	पूर्णांक setlevel;

	rc = rtas_get_sensor(DR_ENTITY_SENSE, slot->index, state);

	अगर (rc < 0) अणु
		अगर (rc == -EFAULT || rc == -EEXIST) अणु
			dbg("%s: slot must be power up to get sensor-state\n",
			    __func__);

			/* some slots have to be घातered up
			 * beक्रमe get-sensor will succeed.
			 */
			rc = rtas_set_घातer_level(slot->घातer_करोमुख्य, POWER_ON,
						  &setlevel);
			अगर (rc < 0) अणु
				dbg("%s: power on slot[%s] failed rc=%d.\n",
				    __func__, slot->name, rc);
			पूर्ण अन्यथा अणु
				rc = rtas_get_sensor(DR_ENTITY_SENSE,
						     slot->index, state);
			पूर्ण
		पूर्ण अन्यथा अगर (rc == -ENODEV)
			info("%s: slot is unusable\n", __func__);
		अन्यथा
			err("%s failed to get sensor state\n", __func__);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * rpaphp_enable_slot - record slot state, config pci device
 * @slot: target &slot
 *
 * Initialize values in the slot काष्ठाure to indicate अगर there is a pci card
 * plugged पूर्णांकo the slot. If the slot is not empty, run the pcibios routine
 * to get pcibios stuff correctly set up.
 */
पूर्णांक rpaphp_enable_slot(काष्ठा slot *slot)
अणु
	पूर्णांक rc, level, state;
	काष्ठा pci_bus *bus;

	slot->state = EMPTY;

	/* Find out अगर the घातer is turned on क्रम the slot */
	rc = rtas_get_घातer_level(slot->घातer_करोमुख्य, &level);
	अगर (rc)
		वापस rc;

	/* Figure out अगर there is an adapter in the slot */
	rc = rpaphp_get_sensor_state(slot, &state);
	अगर (rc)
		वापस rc;

	bus = pci_find_bus_by_node(slot->dn);
	अगर (!bus) अणु
		err("%s: no pci_bus for dn %pOF\n", __func__, slot->dn);
		वापस -EINVAL;
	पूर्ण

	slot->bus = bus;
	slot->pci_devs = &bus->devices;

	/* अगर there's an adapter in the slot, go add the pci devices */
	अगर (state == PRESENT) अणु
		slot->state = NOT_CONFIGURED;

		/* non-empty slot has to have child */
		अगर (!slot->dn->child) अणु
			err("%s: slot[%s]'s device_node doesn't have child for adapter\n",
			    __func__, slot->name);
			वापस -EINVAL;
		पूर्ण

		अगर (list_empty(&bus->devices)) अणु
			pseries_eeh_init_edev_recursive(PCI_DN(slot->dn));
			pci_hp_add_devices(bus);
		पूर्ण

		अगर (!list_empty(&bus->devices)) अणु
			slot->state = CONFIGURED;
		पूर्ण

		अगर (rpaphp_debug) अणु
			काष्ठा pci_dev *dev;
			dbg("%s: pci_devs of slot[%pOF]\n", __func__, slot->dn);
			list_क्रम_each_entry(dev, &bus->devices, bus_list)
				dbg("\t%s\n", pci_name(dev));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
