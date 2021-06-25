<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश "../pci.h"
#समावेश "cpqphp.h"
#समावेश "cpqphp_nvram.h"


u8 cpqhp_nic_irq;
u8 cpqhp_disk_irq;

अटल u16 unused_IRQ;

/*
 * detect_HRT_भग्नing_poपूर्णांकer
 *
 * find the Hot Plug Resource Table in the specअगरied region of memory.
 *
 */
अटल व्योम __iomem *detect_HRT_भग्नing_poपूर्णांकer(व्योम __iomem *begin, व्योम __iomem *end)
अणु
	व्योम __iomem *fp;
	व्योम __iomem *endp;
	u8 temp1, temp2, temp3, temp4;
	पूर्णांक status = 0;

	endp = (end - माप(काष्ठा hrt) + 1);

	क्रम (fp = begin; fp <= endp; fp += 16) अणु
		temp1 = पढ़ोb(fp + SIG0);
		temp2 = पढ़ोb(fp + SIG1);
		temp3 = पढ़ोb(fp + SIG2);
		temp4 = पढ़ोb(fp + SIG3);
		अगर (temp1 == '$' &&
		    temp2 == 'H' &&
		    temp3 == 'R' &&
		    temp4 == 'T') अणु
			status = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!status)
		fp = शून्य;

	dbg("Discovered Hotplug Resource Table at %p\n", fp);
	वापस fp;
पूर्ण


पूर्णांक cpqhp_configure_device(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	काष्ठा pci_bus *child;
	पूर्णांक num;

	pci_lock_rescan_हटाओ();

	अगर (func->pci_dev == शून्य)
		func->pci_dev = pci_get_करोमुख्य_bus_and_slot(0, func->bus,
							PCI_DEVFN(func->device,
							func->function));

	/* No pci device, we need to create it then */
	अगर (func->pci_dev == शून्य) अणु
		dbg("INFO: pci_dev still null\n");

		num = pci_scan_slot(ctrl->pci_dev->bus, PCI_DEVFN(func->device, func->function));
		अगर (num)
			pci_bus_add_devices(ctrl->pci_dev->bus);

		func->pci_dev = pci_get_करोमुख्य_bus_and_slot(0, func->bus,
							PCI_DEVFN(func->device,
							func->function));
		अगर (func->pci_dev == शून्य) अणु
			dbg("ERROR: pci_dev still null\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (func->pci_dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) अणु
		pci_hp_add_bridge(func->pci_dev);
		child = func->pci_dev->subordinate;
		अगर (child)
			pci_bus_add_devices(child);
	पूर्ण

	pci_dev_put(func->pci_dev);

 out:
	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण


पूर्णांक cpqhp_unconfigure_device(काष्ठा pci_func *func)
अणु
	पूर्णांक j;

	dbg("%s: bus/dev/func = %x/%x/%x\n", __func__, func->bus, func->device, func->function);

	pci_lock_rescan_हटाओ();
	क्रम (j = 0; j < 8 ; j++) अणु
		काष्ठा pci_dev *temp = pci_get_करोमुख्य_bus_and_slot(0,
							func->bus,
							PCI_DEVFN(func->device,
							j));
		अगर (temp) अणु
			pci_dev_put(temp);
			pci_stop_and_हटाओ_bus_device(temp);
		पूर्ण
	पूर्ण
	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण

अटल पूर्णांक PCI_RefinedAccessConfig(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, u8 offset, u32 *value)
अणु
	u32 vendID = 0;

	अगर (pci_bus_पढ़ो_config_dword(bus, devfn, PCI_VENDOR_ID, &vendID) == -1)
		वापस -1;
	अगर (vendID == 0xffffffff)
		वापस -1;
	वापस pci_bus_पढ़ो_config_dword(bus, devfn, offset, value);
पूर्ण


/*
 * cpqhp_set_irq
 *
 * @bus_num: bus number of PCI device
 * @dev_num: device number of PCI device
 * @slot: poपूर्णांकer to u8 where slot number will be वापसed
 */
पूर्णांक cpqhp_set_irq(u8 bus_num, u8 dev_num, u8 पूर्णांक_pin, u8 irq_num)
अणु
	पूर्णांक rc = 0;

	अगर (cpqhp_legacy_mode) अणु
		काष्ठा pci_dev *fakedev;
		काष्ठा pci_bus *fakebus;
		u16 temp_word;

		fakedev = kदो_स्मृति(माप(*fakedev), GFP_KERNEL);
		fakebus = kदो_स्मृति(माप(*fakebus), GFP_KERNEL);
		अगर (!fakedev || !fakebus) अणु
			kमुक्त(fakedev);
			kमुक्त(fakebus);
			वापस -ENOMEM;
		पूर्ण

		fakedev->devfn = dev_num << 3;
		fakedev->bus = fakebus;
		fakebus->number = bus_num;
		dbg("%s: dev %d, bus %d, pin %d, num %d\n",
		    __func__, dev_num, bus_num, पूर्णांक_pin, irq_num);
		rc = pcibios_set_irq_routing(fakedev, पूर्णांक_pin - 1, irq_num);
		kमुक्त(fakedev);
		kमुक्त(fakebus);
		dbg("%s: rc %d\n", __func__, rc);
		अगर (!rc)
			वापस !rc;

		/* set the Edge Level Control Register (ELCR) */
		temp_word = inb(0x4d0);
		temp_word |= inb(0x4d1) << 8;

		temp_word |= 0x01 << irq_num;

		/* This should only be क्रम x86 as it sets the Edge Level
		 * Control Register
		 */
		outb((u8) (temp_word & 0xFF), 0x4d0); outb((u8) ((temp_word &
		0xFF00) >> 8), 0x4d1); rc = 0; पूर्ण

	वापस rc;
पूर्ण


अटल पूर्णांक PCI_ScanBusForNonBridge(काष्ठा controller *ctrl, u8 bus_num, u8 *dev_num)
अणु
	u16 tdevice;
	u32 work;
	u8 tbus;

	ctrl->pci_bus->number = bus_num;

	क्रम (tdevice = 0; tdevice < 0xFF; tdevice++) अणु
		/* Scan क्रम access first */
		अगर (PCI_RefinedAccessConfig(ctrl->pci_bus, tdevice, 0x08, &work) == -1)
			जारी;
		dbg("Looking for nonbridge bus_num %d dev_num %d\n", bus_num, tdevice);
		/* Yep we got one. Not a bridge ? */
		अगर ((work >> 8) != PCI_TO_PCI_BRIDGE_CLASS) अणु
			*dev_num = tdevice;
			dbg("found it !\n");
			वापस 0;
		पूर्ण
	पूर्ण
	क्रम (tdevice = 0; tdevice < 0xFF; tdevice++) अणु
		/* Scan क्रम access first */
		अगर (PCI_RefinedAccessConfig(ctrl->pci_bus, tdevice, 0x08, &work) == -1)
			जारी;
		dbg("Looking for bridge bus_num %d dev_num %d\n", bus_num, tdevice);
		/* Yep we got one. bridge ? */
		अगर ((work >> 8) == PCI_TO_PCI_BRIDGE_CLASS) अणु
			pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(tdevice, 0), PCI_SECONDARY_BUS, &tbus);
			/* XXX: no recursion, wtf? */
			dbg("Recurse on bus_num %d tdevice %d\n", tbus, tdevice);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण


अटल पूर्णांक PCI_GetBusDevHelper(काष्ठा controller *ctrl, u8 *bus_num, u8 *dev_num, u8 slot, u8 nobridge)
अणु
	पूर्णांक loop, len;
	u32 work;
	u8 tbus, tdevice, tslot;

	len = cpqhp_routing_table_length();
	क्रम (loop = 0; loop < len; ++loop) अणु
		tbus = cpqhp_routing_table->slots[loop].bus;
		tdevice = cpqhp_routing_table->slots[loop].devfn;
		tslot = cpqhp_routing_table->slots[loop].slot;

		अगर (tslot == slot) अणु
			*bus_num = tbus;
			*dev_num = tdevice;
			ctrl->pci_bus->number = tbus;
			pci_bus_पढ़ो_config_dword(ctrl->pci_bus, *dev_num, PCI_VENDOR_ID, &work);
			अगर (!nobridge || (work == 0xffffffff))
				वापस 0;

			dbg("bus_num %d devfn %d\n", *bus_num, *dev_num);
			pci_bus_पढ़ो_config_dword(ctrl->pci_bus, *dev_num, PCI_CLASS_REVISION, &work);
			dbg("work >> 8 (%x) = BRIDGE (%x)\n", work >> 8, PCI_TO_PCI_BRIDGE_CLASS);

			अगर ((work >> 8) == PCI_TO_PCI_BRIDGE_CLASS) अणु
				pci_bus_पढ़ो_config_byte(ctrl->pci_bus, *dev_num, PCI_SECONDARY_BUS, &tbus);
				dbg("Scan bus for Non Bridge: bus %d\n", tbus);
				अगर (PCI_ScanBusForNonBridge(ctrl, tbus, dev_num) == 0) अणु
					*bus_num = tbus;
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण


पूर्णांक cpqhp_get_bus_dev(काष्ठा controller *ctrl, u8 *bus_num, u8 *dev_num, u8 slot)
अणु
	/* plain (bridges allowed) */
	वापस PCI_GetBusDevHelper(ctrl, bus_num, dev_num, slot, 0);
पूर्ण


/* More PCI configuration routines; this समय centered around hotplug
 * controller
 */


/*
 * cpqhp_save_config
 *
 * Reads configuration क्रम all slots in a PCI bus and saves info.
 *
 * Note:  For non-hot plug buses, the slot # saved is the device #
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_save_config(काष्ठा controller *ctrl, पूर्णांक busnumber, पूर्णांक is_hot_plug)
अणु
	दीर्घ rc;
	u8 class_code;
	u8 header_type;
	u32 ID;
	u8 secondary_bus;
	काष्ठा pci_func *new_slot;
	पूर्णांक sub_bus;
	पूर्णांक FirstSupported;
	पूर्णांक LastSupported;
	पूर्णांक max_functions;
	पूर्णांक function;
	u8 DevError;
	पूर्णांक device = 0;
	पूर्णांक cloop = 0;
	पूर्णांक stop_it;
	पूर्णांक index;
	u16 devfn;

	/* Decide which slots are supported */

	अगर (is_hot_plug) अणु
		/*
		 * is_hot_plug is the slot mask
		 */
		FirstSupported = is_hot_plug >> 4;
		LastSupported = FirstSupported + (is_hot_plug & 0x0F) - 1;
	पूर्ण अन्यथा अणु
		FirstSupported = 0;
		LastSupported = 0x1F;
	पूर्ण

	/* Save PCI configuration space क्रम all devices in supported slots */
	ctrl->pci_bus->number = busnumber;
	क्रम (device = FirstSupported; device <= LastSupported; device++) अणु
		ID = 0xFFFFFFFF;
		rc = pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(device, 0), PCI_VENDOR_ID, &ID);

		अगर (ID == 0xFFFFFFFF) अणु
			अगर (is_hot_plug) अणु
				/* Setup slot काष्ठाure with entry क्रम empty
				 * slot
				 */
				new_slot = cpqhp_slot_create(busnumber);
				अगर (new_slot == शून्य)
					वापस 1;

				new_slot->bus = (u8) busnumber;
				new_slot->device = (u8) device;
				new_slot->function = 0;
				new_slot->is_a_board = 0;
				new_slot->presence_save = 0;
				new_slot->चयन_save = 0;
			पूर्ण
			जारी;
		पूर्ण

		rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(device, 0), 0x0B, &class_code);
		अगर (rc)
			वापस rc;

		rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(device, 0), PCI_HEADER_TYPE, &header_type);
		अगर (rc)
			वापस rc;

		/* If multi-function device, set max_functions to 8 */
		अगर (header_type & 0x80)
			max_functions = 8;
		अन्यथा
			max_functions = 1;

		function = 0;

		करो अणु
			DevError = 0;
			अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
				/* Recurse the subordinate bus
				 * get the subordinate bus number
				 */
				rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(device, function), PCI_SECONDARY_BUS, &secondary_bus);
				अगर (rc) अणु
					वापस rc;
				पूर्ण अन्यथा अणु
					sub_bus = (पूर्णांक) secondary_bus;

					/* Save secondary bus cfg spc
					 * with this recursive call.
					 */
					rc = cpqhp_save_config(ctrl, sub_bus, 0);
					अगर (rc)
						वापस rc;
					ctrl->pci_bus->number = busnumber;
				पूर्ण
			पूर्ण

			index = 0;
			new_slot = cpqhp_slot_find(busnumber, device, index++);
			जबतक (new_slot &&
			       (new_slot->function != (u8) function))
				new_slot = cpqhp_slot_find(busnumber, device, index++);

			अगर (!new_slot) अणु
				/* Setup slot काष्ठाure. */
				new_slot = cpqhp_slot_create(busnumber);
				अगर (new_slot == शून्य)
					वापस 1;
			पूर्ण

			new_slot->bus = (u8) busnumber;
			new_slot->device = (u8) device;
			new_slot->function = (u8) function;
			new_slot->is_a_board = 1;
			new_slot->चयन_save = 0x10;
			/* In हाल of unsupported board */
			new_slot->status = DevError;
			devfn = (new_slot->device << 3) | new_slot->function;
			new_slot->pci_dev = pci_get_करोमुख्य_bus_and_slot(0,
							new_slot->bus, devfn);

			क्रम (cloop = 0; cloop < 0x20; cloop++) अणु
				rc = pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(device, function), cloop << 2, (u32 *) &(new_slot->config_space[cloop]));
				अगर (rc)
					वापस rc;
			पूर्ण

			pci_dev_put(new_slot->pci_dev);

			function++;

			stop_it = 0;

			/* this loop skips to the next present function
			 * पढ़ोing in Class Code and Header type.
			 */
			जबतक ((function < max_functions) && (!stop_it)) अणु
				rc = pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(device, function), PCI_VENDOR_ID, &ID);
				अगर (ID == 0xFFFFFFFF) अणु
					function++;
					जारी;
				पूर्ण
				rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(device, function), 0x0B, &class_code);
				अगर (rc)
					वापस rc;

				rc = pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(device, function), PCI_HEADER_TYPE, &header_type);
				अगर (rc)
					वापस rc;

				stop_it++;
			पूर्ण

		पूर्ण जबतक (function < max_functions);
	पूर्ण			/* End of FOR loop */

	वापस 0;
पूर्ण


/*
 * cpqhp_save_slot_config
 *
 * Saves configuration info क्रम all PCI devices in a given slot
 * including subordinate buses.
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_save_slot_config(काष्ठा controller *ctrl, काष्ठा pci_func *new_slot)
अणु
	दीर्घ rc;
	u8 class_code;
	u8 header_type;
	u32 ID;
	u8 secondary_bus;
	पूर्णांक sub_bus;
	पूर्णांक max_functions;
	पूर्णांक function = 0;
	पूर्णांक cloop = 0;
	पूर्णांक stop_it;

	ID = 0xFFFFFFFF;

	ctrl->pci_bus->number = new_slot->bus;
	pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(new_slot->device, 0), PCI_VENDOR_ID, &ID);

	अगर (ID == 0xFFFFFFFF)
		वापस 2;

	pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(new_slot->device, 0), 0x0B, &class_code);
	pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(new_slot->device, 0), PCI_HEADER_TYPE, &header_type);

	अगर (header_type & 0x80)	/* Multi-function device */
		max_functions = 8;
	अन्यथा
		max_functions = 1;

	जबतक (function < max_functions) अणु
		अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
			/*  Recurse the subordinate bus */
			pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(new_slot->device, function), PCI_SECONDARY_BUS, &secondary_bus);

			sub_bus = (पूर्णांक) secondary_bus;

			/* Save the config headers क्रम the secondary
			 * bus.
			 */
			rc = cpqhp_save_config(ctrl, sub_bus, 0);
			अगर (rc)
				वापस(rc);
			ctrl->pci_bus->number = new_slot->bus;

		पूर्ण

		new_slot->status = 0;

		क्रम (cloop = 0; cloop < 0x20; cloop++)
			pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(new_slot->device, function), cloop << 2, (u32 *) &(new_slot->config_space[cloop]));

		function++;

		stop_it = 0;

		/* this loop skips to the next present function
		 * पढ़ोing in the Class Code and the Header type.
		 */
		जबतक ((function < max_functions) && (!stop_it)) अणु
			pci_bus_पढ़ो_config_dword(ctrl->pci_bus, PCI_DEVFN(new_slot->device, function), PCI_VENDOR_ID, &ID);

			अगर (ID == 0xFFFFFFFF)
				function++;
			अन्यथा अणु
				pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(new_slot->device, function), 0x0B, &class_code);
				pci_bus_पढ़ो_config_byte(ctrl->pci_bus, PCI_DEVFN(new_slot->device, function), PCI_HEADER_TYPE, &header_type);
				stop_it++;
			पूर्ण
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण


/*
 * cpqhp_save_base_addr_length
 *
 * Saves the length of all base address रेजिस्टरs क्रम the
 * specअगरied slot.  this is क्रम hot plug REPLACE
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_save_base_addr_length(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	u8 cloop;
	u8 header_type;
	u8 secondary_bus;
	u8 type;
	पूर्णांक sub_bus;
	u32 temp_रेजिस्टर;
	u32 base;
	u32 rc;
	काष्ठा pci_func *next;
	पूर्णांक index = 0;
	काष्ठा pci_bus *pci_bus = ctrl->pci_bus;
	अचिन्हित पूर्णांक devfn;

	func = cpqhp_slot_find(func->bus, func->device, index++);

	जबतक (func != शून्य) अणु
		pci_bus->number = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Check क्रम Bridge */
		pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &header_type);

		अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_SECONDARY_BUS, &secondary_bus);

			sub_bus = (पूर्णांक) secondary_bus;

			next = cpqhp_slot_list[sub_bus];

			जबतक (next != शून्य) अणु
				rc = cpqhp_save_base_addr_length(ctrl, next);
				अगर (rc)
					वापस rc;

				next = next->next;
			पूर्ण
			pci_bus->number = func->bus;

			/* FIXME: this loop is duplicated in the non-bridge
			 * हाल.  The two could be rolled together Figure out
			 * IO and memory base lengths
			 */
			क्रम (cloop = 0x10; cloop <= 0x14; cloop += 4) अणु
				temp_रेजिस्टर = 0xFFFFFFFF;
				pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &base);
				/* If this रेजिस्टर is implemented */
				अगर (base) अणु
					अगर (base & 0x01L) अणु
						/* IO base
						 * set base = amount of IO space
						 * requested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					पूर्ण अन्यथा अणु
						/* memory base */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					पूर्ण
				पूर्ण अन्यथा अणु
					base = 0x0L;
					type = 0;
				पूर्ण

				/* Save inक्रमmation in slot काष्ठाure */
				func->base_length[(cloop - 0x10) >> 2] =
				base;
				func->base_type[(cloop - 0x10) >> 2] = type;

			पूर्ण	/* End of base रेजिस्टर loop */

		पूर्ण अन्यथा अगर ((header_type & 0x7F) == 0x00) अणु
			/* Figure out IO and memory base lengths */
			क्रम (cloop = 0x10; cloop <= 0x24; cloop += 4) अणु
				temp_रेजिस्टर = 0xFFFFFFFF;
				pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &base);

				/* If this रेजिस्टर is implemented */
				अगर (base) अणु
					अगर (base & 0x01L) अणु
						/* IO base
						 * base = amount of IO space
						 * requested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					पूर्ण अन्यथा अणु
						/* memory base
						 * base = amount of memory
						 * space requested
						 */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					पूर्ण
				पूर्ण अन्यथा अणु
					base = 0x0L;
					type = 0;
				पूर्ण

				/* Save inक्रमmation in slot काष्ठाure */
				func->base_length[(cloop - 0x10) >> 2] = base;
				func->base_type[(cloop - 0x10) >> 2] = type;

			पूर्ण	/* End of base रेजिस्टर loop */

		पूर्ण अन्यथा अणु	  /* Some other unknown header type */
		पूर्ण

		/* find the next device in this slot */
		func = cpqhp_slot_find(func->bus, func->device, index++);
	पूर्ण

	वापस(0);
पूर्ण


/*
 * cpqhp_save_used_resources
 *
 * Stores used resource inक्रमmation क्रम existing boards.  this is
 * क्रम boards that were in the प्रणाली when this driver was loaded.
 * this function is क्रम hot plug ADD
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_save_used_resources(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	u8 cloop;
	u8 header_type;
	u8 secondary_bus;
	u8 temp_byte;
	u8 b_base;
	u8 b_length;
	u16 command;
	u16 save_command;
	u16 w_base;
	u16 w_length;
	u32 temp_रेजिस्टर;
	u32 save_base;
	u32 base;
	पूर्णांक index = 0;
	काष्ठा pci_resource *mem_node;
	काष्ठा pci_resource *p_mem_node;
	काष्ठा pci_resource *io_node;
	काष्ठा pci_resource *bus_node;
	काष्ठा pci_bus *pci_bus = ctrl->pci_bus;
	अचिन्हित पूर्णांक devfn;

	func = cpqhp_slot_find(func->bus, func->device, index++);

	जबतक ((func != शून्य) && func->is_a_board) अणु
		pci_bus->number = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Save the command रेजिस्टर */
		pci_bus_पढ़ो_config_word(pci_bus, devfn, PCI_COMMAND, &save_command);

		/* disable card */
		command = 0x00;
		pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_COMMAND, command);

		/* Check क्रम Bridge */
		pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &header_type);

		अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
			/* Clear Bridge Control Register */
			command = 0x00;
			pci_bus_ग_लिखो_config_word(pci_bus, devfn, PCI_BRIDGE_CONTROL, command);
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_SECONDARY_BUS, &secondary_bus);
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_SUBORDINATE_BUS, &temp_byte);

			bus_node = kदो_स्मृति(माप(*bus_node), GFP_KERNEL);
			अगर (!bus_node)
				वापस -ENOMEM;

			bus_node->base = secondary_bus;
			bus_node->length = temp_byte - secondary_bus + 1;

			bus_node->next = func->bus_head;
			func->bus_head = bus_node;

			/* Save IO base and Limit रेजिस्टरs */
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_IO_BASE, &b_base);
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_IO_LIMIT, &b_length);

			अगर ((b_base <= b_length) && (save_command & 0x01)) अणु
				io_node = kदो_स्मृति(माप(*io_node), GFP_KERNEL);
				अगर (!io_node)
					वापस -ENOMEM;

				io_node->base = (b_base & 0xF0) << 8;
				io_node->length = (b_length - b_base + 0x10) << 8;

				io_node->next = func->io_head;
				func->io_head = io_node;
			पूर्ण

			/* Save memory base and Limit रेजिस्टरs */
			pci_bus_पढ़ो_config_word(pci_bus, devfn, PCI_MEMORY_BASE, &w_base);
			pci_bus_पढ़ो_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, &w_length);

			अगर ((w_base <= w_length) && (save_command & 0x02)) अणु
				mem_node = kदो_स्मृति(माप(*mem_node), GFP_KERNEL);
				अगर (!mem_node)
					वापस -ENOMEM;

				mem_node->base = w_base << 16;
				mem_node->length = (w_length - w_base + 0x10) << 16;

				mem_node->next = func->mem_head;
				func->mem_head = mem_node;
			पूर्ण

			/* Save prefetchable memory base and Limit रेजिस्टरs */
			pci_bus_पढ़ो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_BASE, &w_base);
			pci_bus_पढ़ो_config_word(pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, &w_length);

			अगर ((w_base <= w_length) && (save_command & 0x02)) अणु
				p_mem_node = kदो_स्मृति(माप(*p_mem_node), GFP_KERNEL);
				अगर (!p_mem_node)
					वापस -ENOMEM;

				p_mem_node->base = w_base << 16;
				p_mem_node->length = (w_length - w_base + 0x10) << 16;

				p_mem_node->next = func->p_mem_head;
				func->p_mem_head = p_mem_node;
			पूर्ण
			/* Figure out IO and memory base lengths */
			क्रम (cloop = 0x10; cloop <= 0x14; cloop += 4) अणु
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &save_base);

				temp_रेजिस्टर = 0xFFFFFFFF;
				pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &base);

				temp_रेजिस्टर = base;

				/* If this रेजिस्टर is implemented */
				अगर (base) अणु
					अगर (((base & 0x03L) == 0x01)
					    && (save_command & 0x01)) अणु
						/* IO base
						 * set temp_रेजिस्टर = amount
						 * of IO space requested
						 */
						temp_रेजिस्टर = base & 0xFFFFFFFE;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						io_node = kदो_स्मृति(माप(*io_node),
								GFP_KERNEL);
						अगर (!io_node)
							वापस -ENOMEM;

						io_node->base =
						save_base & (~0x03L);
						io_node->length = temp_रेजिस्टर;

						io_node->next = func->io_head;
						func->io_head = io_node;
					पूर्ण अन्यथा
						अगर (((base & 0x0BL) == 0x08)
						    && (save_command & 0x02)) अणु
						/* prefetchable memory base */
						temp_रेजिस्टर = base & 0xFFFFFFF0;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						p_mem_node = kदो_स्मृति(माप(*p_mem_node),
								GFP_KERNEL);
						अगर (!p_mem_node)
							वापस -ENOMEM;

						p_mem_node->base = save_base & (~0x0FL);
						p_mem_node->length = temp_रेजिस्टर;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					पूर्ण अन्यथा
						अगर (((base & 0x0BL) == 0x00)
						    && (save_command & 0x02)) अणु
						/* prefetchable memory base */
						temp_रेजिस्टर = base & 0xFFFFFFF0;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						mem_node = kदो_स्मृति(माप(*mem_node),
								GFP_KERNEL);
						अगर (!mem_node)
							वापस -ENOMEM;

						mem_node->base = save_base & (~0x0FL);
						mem_node->length = temp_रेजिस्टर;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					पूर्ण अन्यथा
						वापस(1);
				पूर्ण
			पूर्ण	/* End of base रेजिस्टर loop */
		/* Standard header */
		पूर्ण अन्यथा अगर ((header_type & 0x7F) == 0x00) अणु
			/* Figure out IO and memory base lengths */
			क्रम (cloop = 0x10; cloop <= 0x24; cloop += 4) अणु
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &save_base);

				temp_रेजिस्टर = 0xFFFFFFFF;
				pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &base);

				temp_रेजिस्टर = base;

				/* If this रेजिस्टर is implemented */
				अगर (base) अणु
					अगर (((base & 0x03L) == 0x01)
					    && (save_command & 0x01)) अणु
						/* IO base
						 * set temp_रेजिस्टर = amount
						 * of IO space requested
						 */
						temp_रेजिस्टर = base & 0xFFFFFFFE;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						io_node = kदो_स्मृति(माप(*io_node),
								GFP_KERNEL);
						अगर (!io_node)
							वापस -ENOMEM;

						io_node->base = save_base & (~0x01L);
						io_node->length = temp_रेजिस्टर;

						io_node->next = func->io_head;
						func->io_head = io_node;
					पूर्ण अन्यथा
						अगर (((base & 0x0BL) == 0x08)
						    && (save_command & 0x02)) अणु
						/* prefetchable memory base */
						temp_रेजिस्टर = base & 0xFFFFFFF0;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						p_mem_node = kदो_स्मृति(माप(*p_mem_node),
								GFP_KERNEL);
						अगर (!p_mem_node)
							वापस -ENOMEM;

						p_mem_node->base = save_base & (~0x0FL);
						p_mem_node->length = temp_रेजिस्टर;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					पूर्ण अन्यथा
						अगर (((base & 0x0BL) == 0x00)
						    && (save_command & 0x02)) अणु
						/* prefetchable memory base */
						temp_रेजिस्टर = base & 0xFFFFFFF0;
						temp_रेजिस्टर = (~temp_रेजिस्टर) + 1;

						mem_node = kदो_स्मृति(माप(*mem_node),
								GFP_KERNEL);
						अगर (!mem_node)
							वापस -ENOMEM;

						mem_node->base = save_base & (~0x0FL);
						mem_node->length = temp_रेजिस्टर;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					पूर्ण अन्यथा
						वापस(1);
				पूर्ण
			पूर्ण	/* End of base रेजिस्टर loop */
		पूर्ण

		/* find the next device in this slot */
		func = cpqhp_slot_find(func->bus, func->device, index++);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * cpqhp_configure_board
 *
 * Copies saved configuration inक्रमmation to one slot.
 * this is called recursively क्रम bridge devices.
 * this is क्रम hot plug REPLACE!
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_configure_board(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	पूर्णांक cloop;
	u8 header_type;
	u8 secondary_bus;
	पूर्णांक sub_bus;
	काष्ठा pci_func *next;
	u32 temp;
	u32 rc;
	पूर्णांक index = 0;
	काष्ठा pci_bus *pci_bus = ctrl->pci_bus;
	अचिन्हित पूर्णांक devfn;

	func = cpqhp_slot_find(func->bus, func->device, index++);

	जबतक (func != शून्य) अणु
		pci_bus->number = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Start at the top of config space so that the control
		 * रेजिस्टरs are programmed last
		 */
		क्रम (cloop = 0x3C; cloop > 0; cloop -= 4)
			pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, func->config_space[cloop >> 2]);

		pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &header_type);

		/* If this is a bridge device, restore subordinate devices */
		अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
			pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_SECONDARY_BUS, &secondary_bus);

			sub_bus = (पूर्णांक) secondary_bus;

			next = cpqhp_slot_list[sub_bus];

			जबतक (next != शून्य) अणु
				rc = cpqhp_configure_board(ctrl, next);
				अगर (rc)
					वापस rc;

				next = next->next;
			पूर्ण
		पूर्ण अन्यथा अणु

			/* Check all the base Address Registers to make sure
			 * they are the same.  If not, the board is dअगरferent.
			 */

			क्रम (cloop = 16; cloop < 40; cloop += 4) अणु
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &temp);

				अगर (temp != func->config_space[cloop >> 2]) अणु
					dbg("Config space compare failure!!! offset = %x\n", cloop);
					dbg("bus = %x, device = %x, function = %x\n", func->bus, func->device, func->function);
					dbg("temp = %x, config space = %x\n\n", temp, func->config_space[cloop >> 2]);
					वापस 1;
				पूर्ण
			पूर्ण
		पूर्ण

		func->configured = 1;

		func = cpqhp_slot_find(func->bus, func->device, index++);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * cpqhp_valid_replace
 *
 * this function checks to see अगर a board is the same as the
 * one it is replacing.  this check will detect अगर the device's
 * venकरोr or device id's are the same
 *
 * वापसs 0 अगर the board is the same nonzero otherwise
 */
पूर्णांक cpqhp_valid_replace(काष्ठा controller *ctrl, काष्ठा pci_func *func)
अणु
	u8 cloop;
	u8 header_type;
	u8 secondary_bus;
	u8 type;
	u32 temp_रेजिस्टर = 0;
	u32 base;
	u32 rc;
	काष्ठा pci_func *next;
	पूर्णांक index = 0;
	काष्ठा pci_bus *pci_bus = ctrl->pci_bus;
	अचिन्हित पूर्णांक devfn;

	अगर (!func->is_a_board)
		वापस(ADD_NOT_SUPPORTED);

	func = cpqhp_slot_find(func->bus, func->device, index++);

	जबतक (func != शून्य) अणु
		pci_bus->number = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		pci_bus_पढ़ो_config_dword(pci_bus, devfn, PCI_VENDOR_ID, &temp_रेजिस्टर);

		/* No adapter present */
		अगर (temp_रेजिस्टर == 0xFFFFFFFF)
			वापस(NO_ADAPTER_PRESENT);

		अगर (temp_रेजिस्टर != func->config_space[0])
			वापस(ADAPTER_NOT_SAME);

		/* Check क्रम same revision number and class code */
		pci_bus_पढ़ो_config_dword(pci_bus, devfn, PCI_CLASS_REVISION, &temp_रेजिस्टर);

		/* Adapter not the same */
		अगर (temp_रेजिस्टर != func->config_space[0x08 >> 2])
			वापस(ADAPTER_NOT_SAME);

		/* Check क्रम Bridge */
		pci_bus_पढ़ो_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &header_type);

		अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
			/* In order to जारी checking, we must program the
			 * bus रेजिस्टरs in the bridge to respond to accesses
			 * क्रम its subordinate bus(es)
			 */

			temp_रेजिस्टर = func->config_space[0x18 >> 2];
			pci_bus_ग_लिखो_config_dword(pci_bus, devfn, PCI_PRIMARY_BUS, temp_रेजिस्टर);

			secondary_bus = (temp_रेजिस्टर >> 8) & 0xFF;

			next = cpqhp_slot_list[secondary_bus];

			जबतक (next != शून्य) अणु
				rc = cpqhp_valid_replace(ctrl, next);
				अगर (rc)
					वापस rc;

				next = next->next;
			पूर्ण

		पूर्ण
		/* Check to see अगर it is a standard config header */
		अन्यथा अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_NORMAL) अणु
			/* Check subप्रणाली venकरोr and ID */
			pci_bus_पढ़ो_config_dword(pci_bus, devfn, PCI_SUBSYSTEM_VENDOR_ID, &temp_रेजिस्टर);

			अगर (temp_रेजिस्टर != func->config_space[0x2C >> 2]) अणु
				/* If it's a SMART-2 and the register isn't
				 * filled in, ignore the dअगरference because
				 * they just have an old rev of the firmware
				 */
				अगर (!((func->config_space[0] == 0xAE100E11)
				      && (temp_रेजिस्टर == 0x00L)))
					वापस(ADAPTER_NOT_SAME);
			पूर्ण
			/* Figure out IO and memory base lengths */
			क्रम (cloop = 0x10; cloop <= 0x24; cloop += 4) अणु
				temp_रेजिस्टर = 0xFFFFFFFF;
				pci_bus_ग_लिखो_config_dword(pci_bus, devfn, cloop, temp_रेजिस्टर);
				pci_bus_पढ़ो_config_dword(pci_bus, devfn, cloop, &base);

				/* If this रेजिस्टर is implemented */
				अगर (base) अणु
					अगर (base & 0x01L) अणु
						/* IO base
						 * set base = amount of IO
						 * space requested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					पूर्ण अन्यथा अणु
						/* memory base */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					पूर्ण
				पूर्ण अन्यथा अणु
					base = 0x0L;
					type = 0;
				पूर्ण

				/* Check inक्रमmation in slot काष्ठाure */
				अगर (func->base_length[(cloop - 0x10) >> 2] != base)
					वापस(ADAPTER_NOT_SAME);

				अगर (func->base_type[(cloop - 0x10) >> 2] != type)
					वापस(ADAPTER_NOT_SAME);

			पूर्ण	/* End of base रेजिस्टर loop */

		पूर्ण		/* End of (type 0 config space) अन्यथा */
		अन्यथा अणु
			/* this is not a type 0 or 1 config space header so
			 * we करोn't know how to करो it
			 */
			वापस(DEVICE_TYPE_NOT_SUPPORTED);
		पूर्ण

		/* Get the next function */
		func = cpqhp_slot_find(func->bus, func->device, index++);
	पूर्ण


	वापस 0;
पूर्ण


/*
 * cpqhp_find_available_resources
 *
 * Finds available memory, IO, and IRQ resources क्रम programming
 * devices which may be added to the प्रणाली
 * this function is क्रम hot plug ADD!
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_find_available_resources(काष्ठा controller *ctrl, व्योम __iomem *rom_start)
अणु
	u8 temp;
	u8 populated_slot;
	u8 bridged_slot;
	व्योम __iomem *one_slot;
	व्योम __iomem *rom_resource_table;
	काष्ठा pci_func *func = शून्य;
	पूर्णांक i = 10, index;
	u32 temp_dword, rc;
	काष्ठा pci_resource *mem_node;
	काष्ठा pci_resource *p_mem_node;
	काष्ठा pci_resource *io_node;
	काष्ठा pci_resource *bus_node;

	rom_resource_table = detect_HRT_भग्नing_poपूर्णांकer(rom_start, rom_start+0xffff);
	dbg("rom_resource_table = %p\n", rom_resource_table);

	अगर (rom_resource_table == शून्य)
		वापस -ENODEV;

	/* Sum all resources and setup resource maps */
	unused_IRQ = पढ़ोl(rom_resource_table + UNUSED_IRQ);
	dbg("unused_IRQ = %x\n", unused_IRQ);

	temp = 0;
	जबतक (unused_IRQ) अणु
		अगर (unused_IRQ & 1) अणु
			cpqhp_disk_irq = temp;
			अवरोध;
		पूर्ण
		unused_IRQ = unused_IRQ >> 1;
		temp++;
	पूर्ण

	dbg("cpqhp_disk_irq= %d\n", cpqhp_disk_irq);
	unused_IRQ = unused_IRQ >> 1;
	temp++;

	जबतक (unused_IRQ) अणु
		अगर (unused_IRQ & 1) अणु
			cpqhp_nic_irq = temp;
			अवरोध;
		पूर्ण
		unused_IRQ = unused_IRQ >> 1;
		temp++;
	पूर्ण

	dbg("cpqhp_nic_irq= %d\n", cpqhp_nic_irq);
	unused_IRQ = पढ़ोl(rom_resource_table + PCIIRQ);

	temp = 0;

	अगर (!cpqhp_nic_irq)
		cpqhp_nic_irq = ctrl->cfgspc_irq;

	अगर (!cpqhp_disk_irq)
		cpqhp_disk_irq = ctrl->cfgspc_irq;

	dbg("cpqhp_disk_irq, cpqhp_nic_irq= %d, %d\n", cpqhp_disk_irq, cpqhp_nic_irq);

	rc = compaq_nvram_load(rom_start, ctrl);
	अगर (rc)
		वापस rc;

	one_slot = rom_resource_table + माप(काष्ठा hrt);

	i = पढ़ोb(rom_resource_table + NUMBER_OF_ENTRIES);
	dbg("number_of_entries = %d\n", i);

	अगर (!पढ़ोb(one_slot + SECONDARY_BUS))
		वापस 1;

	dbg("dev|IO base|length|Mem base|length|Pre base|length|PB SB MB\n");

	जबतक (i && पढ़ोb(one_slot + SECONDARY_BUS)) अणु
		u8 dev_func = पढ़ोb(one_slot + DEV_FUNC);
		u8 primary_bus = पढ़ोb(one_slot + PRIMARY_BUS);
		u8 secondary_bus = पढ़ोb(one_slot + SECONDARY_BUS);
		u8 max_bus = पढ़ोb(one_slot + MAX_BUS);
		u16 io_base = पढ़ोw(one_slot + IO_BASE);
		u16 io_length = पढ़ोw(one_slot + IO_LENGTH);
		u16 mem_base = पढ़ोw(one_slot + MEM_BASE);
		u16 mem_length = पढ़ोw(one_slot + MEM_LENGTH);
		u16 pre_mem_base = पढ़ोw(one_slot + PRE_MEM_BASE);
		u16 pre_mem_length = पढ़ोw(one_slot + PRE_MEM_LENGTH);

		dbg("%2.2x | %4.4x  | %4.4x | %4.4x   | %4.4x | %4.4x   | %4.4x |%2.2x %2.2x %2.2x\n",
		    dev_func, io_base, io_length, mem_base, mem_length, pre_mem_base, pre_mem_length,
		    primary_bus, secondary_bus, max_bus);

		/* If this entry isn't for our controller's bus, ignore it */
		अगर (primary_bus != ctrl->bus) अणु
			i--;
			one_slot += माप(काष्ठा slot_rt);
			जारी;
		पूर्ण
		/* find out अगर this entry is क्रम an occupied slot */
		ctrl->pci_bus->number = primary_bus;
		pci_bus_पढ़ो_config_dword(ctrl->pci_bus, dev_func, PCI_VENDOR_ID, &temp_dword);
		dbg("temp_D_word = %x\n", temp_dword);

		अगर (temp_dword != 0xFFFFFFFF) अणु
			index = 0;
			func = cpqhp_slot_find(primary_bus, dev_func >> 3, 0);

			जबतक (func && (func->function != (dev_func & 0x07))) अणु
				dbg("func = %p (bus, dev, fun) = (%d, %d, %d)\n", func, primary_bus, dev_func >> 3, index);
				func = cpqhp_slot_find(primary_bus, dev_func >> 3, index++);
			पूर्ण

			/* If we can't find a match, skip this table entry */
			अगर (!func) अणु
				i--;
				one_slot += माप(काष्ठा slot_rt);
				जारी;
			पूर्ण
			/* this may not work and shouldn't be used */
			अगर (secondary_bus != primary_bus)
				bridged_slot = 1;
			अन्यथा
				bridged_slot = 0;

			populated_slot = 1;
		पूर्ण अन्यथा अणु
			populated_slot = 0;
			bridged_slot = 0;
		पूर्ण


		/* If we've got a valid IO base, use it */

		temp_dword = io_base + io_length;

		अगर ((io_base) && (temp_dword < 0x10000)) अणु
			io_node = kदो_स्मृति(माप(*io_node), GFP_KERNEL);
			अगर (!io_node)
				वापस -ENOMEM;

			io_node->base = io_base;
			io_node->length = io_length;

			dbg("found io_node(base, length) = %x, %x\n",
					io_node->base, io_node->length);
			dbg("populated slot =%d \n", populated_slot);
			अगर (!populated_slot) अणु
				io_node->next = ctrl->io_head;
				ctrl->io_head = io_node;
			पूर्ण अन्यथा अणु
				io_node->next = func->io_head;
				func->io_head = io_node;
			पूर्ण
		पूर्ण

		/* If we've got a valid memory base, use it */
		temp_dword = mem_base + mem_length;
		अगर ((mem_base) && (temp_dword < 0x10000)) अणु
			mem_node = kदो_स्मृति(माप(*mem_node), GFP_KERNEL);
			अगर (!mem_node)
				वापस -ENOMEM;

			mem_node->base = mem_base << 16;

			mem_node->length = mem_length << 16;

			dbg("found mem_node(base, length) = %x, %x\n",
					mem_node->base, mem_node->length);
			dbg("populated slot =%d \n", populated_slot);
			अगर (!populated_slot) अणु
				mem_node->next = ctrl->mem_head;
				ctrl->mem_head = mem_node;
			पूर्ण अन्यथा अणु
				mem_node->next = func->mem_head;
				func->mem_head = mem_node;
			पूर्ण
		पूर्ण

		/* If we've got a valid prefetchable memory base, and
		 * the base + length isn't greater than 0xFFFF
		 */
		temp_dword = pre_mem_base + pre_mem_length;
		अगर ((pre_mem_base) && (temp_dword < 0x10000)) अणु
			p_mem_node = kदो_स्मृति(माप(*p_mem_node), GFP_KERNEL);
			अगर (!p_mem_node)
				वापस -ENOMEM;

			p_mem_node->base = pre_mem_base << 16;

			p_mem_node->length = pre_mem_length << 16;
			dbg("found p_mem_node(base, length) = %x, %x\n",
					p_mem_node->base, p_mem_node->length);
			dbg("populated slot =%d \n", populated_slot);

			अगर (!populated_slot) अणु
				p_mem_node->next = ctrl->p_mem_head;
				ctrl->p_mem_head = p_mem_node;
			पूर्ण अन्यथा अणु
				p_mem_node->next = func->p_mem_head;
				func->p_mem_head = p_mem_node;
			पूर्ण
		पूर्ण

		/* If we've got a valid bus number, use it
		 * The second condition is to ignore bus numbers on
		 * populated slots that करोn't have PCI-PCI bridges
		 */
		अगर (secondary_bus && (secondary_bus != primary_bus)) अणु
			bus_node = kदो_स्मृति(माप(*bus_node), GFP_KERNEL);
			अगर (!bus_node)
				वापस -ENOMEM;

			bus_node->base = secondary_bus;
			bus_node->length = max_bus - secondary_bus + 1;
			dbg("found bus_node(base, length) = %x, %x\n",
					bus_node->base, bus_node->length);
			dbg("populated slot =%d \n", populated_slot);
			अगर (!populated_slot) अणु
				bus_node->next = ctrl->bus_head;
				ctrl->bus_head = bus_node;
			पूर्ण अन्यथा अणु
				bus_node->next = func->bus_head;
				func->bus_head = bus_node;
			पूर्ण
		पूर्ण

		i--;
		one_slot += माप(काष्ठा slot_rt);
	पूर्ण

	/* If all of the following fail, we करोn't have any resources क्रम
	 * hot plug add
	 */
	rc = 1;
	rc &= cpqhp_resource_sort_and_combine(&(ctrl->mem_head));
	rc &= cpqhp_resource_sort_and_combine(&(ctrl->p_mem_head));
	rc &= cpqhp_resource_sort_and_combine(&(ctrl->io_head));
	rc &= cpqhp_resource_sort_and_combine(&(ctrl->bus_head));

	वापस rc;
पूर्ण


/*
 * cpqhp_वापस_board_resources
 *
 * this routine वापसs all resources allocated to a board to
 * the available pool.
 *
 * वापसs 0 अगर success
 */
पूर्णांक cpqhp_वापस_board_resources(काष्ठा pci_func *func, काष्ठा resource_lists *resources)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_resource *node;
	काष्ठा pci_resource *t_node;
	dbg("%s\n", __func__);

	अगर (!func)
		वापस 1;

	node = func->io_head;
	func->io_head = शून्य;
	जबतक (node) अणु
		t_node = node->next;
		वापस_resource(&(resources->io_head), node);
		node = t_node;
	पूर्ण

	node = func->mem_head;
	func->mem_head = शून्य;
	जबतक (node) अणु
		t_node = node->next;
		वापस_resource(&(resources->mem_head), node);
		node = t_node;
	पूर्ण

	node = func->p_mem_head;
	func->p_mem_head = शून्य;
	जबतक (node) अणु
		t_node = node->next;
		वापस_resource(&(resources->p_mem_head), node);
		node = t_node;
	पूर्ण

	node = func->bus_head;
	func->bus_head = शून्य;
	जबतक (node) अणु
		t_node = node->next;
		वापस_resource(&(resources->bus_head), node);
		node = t_node;
	पूर्ण

	rc |= cpqhp_resource_sort_and_combine(&(resources->mem_head));
	rc |= cpqhp_resource_sort_and_combine(&(resources->p_mem_head));
	rc |= cpqhp_resource_sort_and_combine(&(resources->io_head));
	rc |= cpqhp_resource_sort_and_combine(&(resources->bus_head));

	वापस rc;
पूर्ण


/*
 * cpqhp_destroy_resource_list
 *
 * Puts node back in the resource list poपूर्णांकed to by head
 */
व्योम cpqhp_destroy_resource_list(काष्ठा resource_lists *resources)
अणु
	काष्ठा pci_resource *res, *tres;

	res = resources->io_head;
	resources->io_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = resources->mem_head;
	resources->mem_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = resources->p_mem_head;
	resources->p_mem_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = resources->bus_head;
	resources->bus_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण
पूर्ण


/*
 * cpqhp_destroy_board_resources
 *
 * Puts node back in the resource list poपूर्णांकed to by head
 */
व्योम cpqhp_destroy_board_resources(काष्ठा pci_func *func)
अणु
	काष्ठा pci_resource *res, *tres;

	res = func->io_head;
	func->io_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = func->mem_head;
	func->mem_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = func->p_mem_head;
	func->p_mem_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण

	res = func->bus_head;
	func->bus_head = शून्य;

	जबतक (res) अणु
		tres = res;
		res = res->next;
		kमुक्त(tres);
	पूर्ण
पूर्ण
