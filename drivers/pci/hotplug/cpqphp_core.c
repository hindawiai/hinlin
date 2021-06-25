<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 * Jan 12, 2003 -	Added 66/100/133MHz PCI-X support,
 *			Torben Mathiasen <torben.mathiasen@hp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/uaccess.h>

#समावेश "cpqphp.h"
#समावेश "cpqphp_nvram.h"


/* Global variables */
पूर्णांक cpqhp_debug;
पूर्णांक cpqhp_legacy_mode;
काष्ठा controller *cpqhp_ctrl_list;	/* = शून्य */
काष्ठा pci_func *cpqhp_slot_list[256];
काष्ठा irq_routing_table *cpqhp_routing_table;

/* local variables */
अटल व्योम __iomem *smbios_table;
अटल व्योम __iomem *smbios_start;
अटल व्योम __iomem *cpqhp_rom_start;
अटल bool घातer_mode;
अटल bool debug;
अटल पूर्णांक initialized;

#घोषणा DRIVER_VERSION	"0.9.8"
#घोषणा DRIVER_AUTHOR	"Dan Zink <dan.zink@compaq.com>, Greg Kroah-Hartman <greg@kroah.com>"
#घोषणा DRIVER_DESC	"Compaq Hot Plug PCI Controller Driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(घातer_mode, bool, 0644);
MODULE_PARM_DESC(घातer_mode, "Power mode enabled or not");

module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debugging mode enabled or not");

#घोषणा CPQHPC_MODULE_MINOR 208

अटल अंतरभूत पूर्णांक is_slot64bit(काष्ठा slot *slot)
अणु
	वापस (पढ़ोb(slot->p_sm_slot + SMBIOS_SLOT_WIDTH) == 0x06) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_slot66mhz(काष्ठा slot *slot)
अणु
	वापस (पढ़ोb(slot->p_sm_slot + SMBIOS_SLOT_TYPE) == 0x0E) ? 1 : 0;
पूर्ण

/**
 * detect_SMBIOS_poपूर्णांकer - find the System Management BIOS Table in mem region.
 * @begin: begin poपूर्णांकer क्रम region to be scanned.
 * @end: end poपूर्णांकer क्रम region to be scanned.
 *
 * Returns poपूर्णांकer to the head of the SMBIOS tables (or %शून्य).
 */
अटल व्योम __iomem *detect_SMBIOS_poपूर्णांकer(व्योम __iomem *begin, व्योम __iomem *end)
अणु
	व्योम __iomem *fp;
	व्योम __iomem *endp;
	u8 temp1, temp2, temp3, temp4;
	पूर्णांक status = 0;

	endp = (end - माप(u32) + 1);

	क्रम (fp = begin; fp <= endp; fp += 16) अणु
		temp1 = पढ़ोb(fp);
		temp2 = पढ़ोb(fp+1);
		temp3 = पढ़ोb(fp+2);
		temp4 = पढ़ोb(fp+3);
		अगर (temp1 == '_' &&
		    temp2 == 'S' &&
		    temp3 == 'M' &&
		    temp4 == '_') अणु
			status = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!status)
		fp = शून्य;

	dbg("Discovered SMBIOS Entry point at %p\n", fp);

	वापस fp;
पूर्ण

/**
 * init_SERR - Initializes the per slot SERR generation.
 * @ctrl: controller to use
 *
 * For unexpected चयन खोलोs
 */
अटल पूर्णांक init_SERR(काष्ठा controller *ctrl)
अणु
	u32 tempdword;
	u32 number_of_slots;

	अगर (!ctrl)
		वापस 1;

	tempdword = ctrl->first_slot;

	number_of_slots = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) & 0x0F;
	/* Loop through slots */
	जबतक (number_of_slots) अणु
		ग_लिखोb(0, ctrl->hpc_reg + SLOT_SERR);
		tempdword++;
		number_of_slots--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_cpqhp_routing_table(व्योम)
अणु
	पूर्णांक len;

	cpqhp_routing_table = pcibios_get_irq_routing_table();
	अगर (cpqhp_routing_table == शून्य)
		वापस -ENOMEM;

	len = cpqhp_routing_table_length();
	अगर (len == 0) अणु
		kमुक्त(cpqhp_routing_table);
		cpqhp_routing_table = शून्य;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* nice debugging output */
अटल व्योम pci_prपूर्णांक_IRQ_route(व्योम)
अणु
	पूर्णांक len;
	पूर्णांक loop;
	u8 tbus, tdevice, tslot;

	len = cpqhp_routing_table_length();

	dbg("bus dev func slot\n");
	क्रम (loop = 0; loop < len; ++loop) अणु
		tbus = cpqhp_routing_table->slots[loop].bus;
		tdevice = cpqhp_routing_table->slots[loop].devfn;
		tslot = cpqhp_routing_table->slots[loop].slot;
		dbg("%d %d %d %d\n", tbus, tdevice >> 3, tdevice & 0x7, tslot);

	पूर्ण
पूर्ण


/**
 * get_subsequent_smbios_entry: get the next entry from bios table.
 * @smbios_start: where to start in the SMBIOS table
 * @smbios_table: location of the SMBIOS table
 * @curr: %शून्य or poपूर्णांकer to previously वापसed काष्ठाure
 *
 * Gets the first entry अगर previous == शून्य;
 * otherwise, वापसs the next entry.
 * Uses global SMBIOS Table poपूर्णांकer.
 *
 * Returns a poपूर्णांकer to an SMBIOS काष्ठाure or शून्य अगर none found.
 */
अटल व्योम __iomem *get_subsequent_smbios_entry(व्योम __iomem *smbios_start,
						व्योम __iomem *smbios_table,
						व्योम __iomem *curr)
अणु
	u8 bail = 0;
	u8 previous_byte = 1;
	व्योम __iomem *p_temp;
	व्योम __iomem *p_max;

	अगर (!smbios_table || !curr)
		वापस शून्य;

	/* set p_max to the end of the table */
	p_max = smbios_start + पढ़ोw(smbios_table + ST_LENGTH);

	p_temp = curr;
	p_temp += पढ़ोb(curr + SMBIOS_GENERIC_LENGTH);

	जबतक ((p_temp < p_max) && !bail) अणु
		/* Look क्रम the द्विगुन शून्य terminator
		 * The first condition is the previous byte
		 * and the second is the curr
		 */
		अगर (!previous_byte && !(पढ़ोb(p_temp)))
			bail = 1;

		previous_byte = पढ़ोb(p_temp);
		p_temp++;
	पूर्ण

	अगर (p_temp < p_max)
		वापस p_temp;
	अन्यथा
		वापस शून्य;
पूर्ण


/**
 * get_SMBIOS_entry - वापस the requested SMBIOS entry or %शून्य
 * @smbios_start: where to start in the SMBIOS table
 * @smbios_table: location of the SMBIOS table
 * @type: SMBIOS काष्ठाure type to be वापसed
 * @previous: %शून्य or poपूर्णांकer to previously वापसed काष्ठाure
 *
 * Gets the first entry of the specअगरied type अगर previous == %शून्य;
 * Otherwise, वापसs the next entry of the given type.
 * Uses global SMBIOS Table poपूर्णांकer.
 * Uses get_subsequent_smbios_entry.
 *
 * Returns a poपूर्णांकer to an SMBIOS काष्ठाure or %शून्य अगर none found.
 */
अटल व्योम __iomem *get_SMBIOS_entry(व्योम __iomem *smbios_start,
					व्योम __iomem *smbios_table,
					u8 type,
					व्योम __iomem *previous)
अणु
	अगर (!smbios_table)
		वापस शून्य;

	अगर (!previous)
		previous = smbios_start;
	अन्यथा
		previous = get_subsequent_smbios_entry(smbios_start,
					smbios_table, previous);

	जबतक (previous)
		अगर (पढ़ोb(previous + SMBIOS_GENERIC_TYPE) != type)
			previous = get_subsequent_smbios_entry(smbios_start,
						smbios_table, previous);
		अन्यथा
			अवरोध;

	वापस previous;
पूर्ण

अटल पूर्णांक ctrl_slot_cleanup(काष्ठा controller *ctrl)
अणु
	काष्ठा slot *old_slot, *next_slot;

	old_slot = ctrl->slot;
	ctrl->slot = शून्य;

	जबतक (old_slot) अणु
		next_slot = old_slot->next;
		pci_hp_deरेजिस्टर(&old_slot->hotplug_slot);
		kमुक्त(old_slot);
		old_slot = next_slot;
	पूर्ण

	cpqhp_हटाओ_debugfs_files(ctrl);

	/* Free IRQ associated with hot plug device */
	मुक्त_irq(ctrl->पूर्णांकerrupt, ctrl);
	/* Unmap the memory */
	iounmap(ctrl->hpc_reg);
	/* Finally reclaim PCI mem */
	release_mem_region(pci_resource_start(ctrl->pci_dev, 0),
			   pci_resource_len(ctrl->pci_dev, 0));

	वापस 0;
पूर्ण


/**
 * get_slot_mapping - determine logical slot mapping क्रम PCI device
 *
 * Won't work क्रम more than one PCI-PCI bridge in a slot.
 *
 * @bus_num - bus number of PCI device
 * @dev_num - device number of PCI device
 * @slot - Poपूर्णांकer to u8 where slot number will	be वापसed
 *
 * Output:	SUCCESS or FAILURE
 */
अटल पूर्णांक
get_slot_mapping(काष्ठा pci_bus *bus, u8 bus_num, u8 dev_num, u8 *slot)
अणु
	u32 work;
	दीर्घ len;
	दीर्घ loop;

	u8 tbus, tdevice, tslot, bridgeSlot;

	dbg("%s: %p, %d, %d, %p\n", __func__, bus, bus_num, dev_num, slot);

	bridgeSlot = 0xFF;

	len = cpqhp_routing_table_length();
	क्रम (loop = 0; loop < len; ++loop) अणु
		tbus = cpqhp_routing_table->slots[loop].bus;
		tdevice = cpqhp_routing_table->slots[loop].devfn >> 3;
		tslot = cpqhp_routing_table->slots[loop].slot;

		अगर ((tbus == bus_num) && (tdevice == dev_num)) अणु
			*slot = tslot;
			वापस 0;
		पूर्ण अन्यथा अणु
			/* Did not get a match on the target PCI device. Check
			 * अगर the current IRQ table entry is a PCI-to-PCI
			 * bridge device.  If so, and it's secondary bus
			 * matches the bus number क्रम the target device, I need
			 * to save the bridge's slot number.  If I can not find
			 * an entry क्रम the target device, I will have to
			 * assume it's on the other side of the bridge, and
			 * assign it the bridge's slot.
			 */
			bus->number = tbus;
			pci_bus_पढ़ो_config_dword(bus, PCI_DEVFN(tdevice, 0),
						PCI_CLASS_REVISION, &work);

			अगर ((work >> 8) == PCI_TO_PCI_BRIDGE_CLASS) अणु
				pci_bus_पढ़ो_config_dword(bus,
							PCI_DEVFN(tdevice, 0),
							PCI_PRIMARY_BUS, &work);
				// See अगर bridge's secondary bus matches target bus.
				अगर (((work >> 8) & 0x000000FF) == (दीर्घ) bus_num)
					bridgeSlot = tslot;
			पूर्ण
		पूर्ण

	पूर्ण

	/* If we got here, we didn't find an entry in the IRQ mapping table क्रम
	 * the target PCI device.  If we did determine that the target device
	 * is on the other side of a PCI-to-PCI bridge, वापस the slot number
	 * क्रम the bridge.
	 */
	अगर (bridgeSlot != 0xFF) अणु
		*slot = bridgeSlot;
		वापस 0;
	पूर्ण
	/* Couldn't find an entry in the routing table क्रम this PCI device */
	वापस -1;
पूर्ण


/**
 * cpqhp_set_attention_status - Turns the Amber LED क्रम a slot on or off
 * @ctrl: काष्ठा controller to use
 * @func: PCI device/function info
 * @status: LED control flag: 1 = LED on, 0 = LED off
 */
अटल पूर्णांक
cpqhp_set_attention_status(काष्ठा controller *ctrl, काष्ठा pci_func *func,
				u32 status)
अणु
	u8 hp_slot;

	अगर (func == शून्य)
		वापस 1;

	hp_slot = func->device - ctrl->slot_device_offset;

	/* Wait क्रम exclusive access to hardware */
	mutex_lock(&ctrl->crit_sect);

	अगर (status == 1)
		amber_LED_on(ctrl, hp_slot);
	अन्यथा अगर (status == 0)
		amber_LED_off(ctrl, hp_slot);
	अन्यथा अणु
		/* Done with exclusive hardware access */
		mutex_unlock(&ctrl->crit_sect);
		वापस 1;
	पूर्ण

	set_SOGO(ctrl);

	/* Wait क्रम SOBS to be unset */
	रुको_क्रम_ctrl_irq(ctrl);

	/* Done with exclusive hardware access */
	mutex_unlock(&ctrl->crit_sect);

	वापस 0;
पूर्ण


/**
 * set_attention_status - Turns the Amber LED क्रम a slot on or off
 * @hotplug_slot: slot to change LED on
 * @status: LED control flag
 */
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 status)
अणु
	काष्ठा pci_func *slot_func;
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;
	u8 bus;
	u8 devfn;
	u8 device;
	u8 function;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	अगर (cpqhp_get_bus_dev(ctrl, &bus, &devfn, slot->number) == -1)
		वापस -ENODEV;

	device = devfn >> 3;
	function = devfn & 0x7;
	dbg("bus, dev, fn = %d, %d, %d\n", bus, device, function);

	slot_func = cpqhp_slot_find(bus, device, function);
	अगर (!slot_func)
		वापस -ENODEV;

	वापस cpqhp_set_attention_status(ctrl, slot_func, status);
पूर्ण


अटल पूर्णांक process_SI(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा pci_func *slot_func;
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;
	u8 bus;
	u8 devfn;
	u8 device;
	u8 function;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	अगर (cpqhp_get_bus_dev(ctrl, &bus, &devfn, slot->number) == -1)
		वापस -ENODEV;

	device = devfn >> 3;
	function = devfn & 0x7;
	dbg("bus, dev, fn = %d, %d, %d\n", bus, device, function);

	slot_func = cpqhp_slot_find(bus, device, function);
	अगर (!slot_func)
		वापस -ENODEV;

	slot_func->bus = bus;
	slot_func->device = device;
	slot_func->function = function;
	slot_func->configured = 0;
	dbg("board_added(%p, %p)\n", slot_func, ctrl);
	वापस cpqhp_process_SI(ctrl, slot_func);
पूर्ण


अटल पूर्णांक process_SS(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा pci_func *slot_func;
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;
	u8 bus;
	u8 devfn;
	u8 device;
	u8 function;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	अगर (cpqhp_get_bus_dev(ctrl, &bus, &devfn, slot->number) == -1)
		वापस -ENODEV;

	device = devfn >> 3;
	function = devfn & 0x7;
	dbg("bus, dev, fn = %d, %d, %d\n", bus, device, function);

	slot_func = cpqhp_slot_find(bus, device, function);
	अगर (!slot_func)
		वापस -ENODEV;

	dbg("In %s, slot_func = %p, ctrl = %p\n", __func__, slot_func, ctrl);
	वापस cpqhp_process_SS(ctrl, slot_func);
पूर्ण


अटल पूर्णांक hardware_test(काष्ठा hotplug_slot *hotplug_slot, u32 value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	वापस cpqhp_hardware_test(ctrl, value);
पूर्ण


अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = get_slot_enabled(ctrl, slot);
	वापस 0;
पूर्ण

अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = cpq_get_attention_status(ctrl, slot);
	वापस 0;
पूर्ण

अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = cpq_get_latch_status(ctrl, slot);

	वापस 0;
पूर्ण

अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	काष्ठा controller *ctrl = slot->ctrl;

	dbg("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = get_presence_status(ctrl, slot);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hotplug_slot_ops cpqphp_hotplug_slot_ops = अणु
	.set_attention_status =	set_attention_status,
	.enable_slot =		process_SI,
	.disable_slot =		process_SS,
	.hardware_test =	hardware_test,
	.get_घातer_status =	get_घातer_status,
	.get_attention_status =	get_attention_status,
	.get_latch_status =	get_latch_status,
	.get_adapter_status =	get_adapter_status,
पूर्ण;

#घोषणा SLOT_NAME_SIZE 10

अटल पूर्णांक ctrl_slot_setup(काष्ठा controller *ctrl,
			व्योम __iomem *smbios_start,
			व्योम __iomem *smbios_table)
अणु
	काष्ठा slot *slot;
	काष्ठा pci_bus *bus = ctrl->pci_bus;
	u8 number_of_slots;
	u8 slot_device;
	u8 slot_number;
	u8 ctrl_slot;
	u32 tempdword;
	अक्षर name[SLOT_NAME_SIZE];
	व्योम __iomem *slot_entry = शून्य;
	पूर्णांक result;

	dbg("%s\n", __func__);

	tempdword = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);

	number_of_slots = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) & 0x0F;
	slot_device = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4;
	slot_number = ctrl->first_slot;

	जबतक (number_of_slots) अणु
		slot = kzalloc(माप(*slot), GFP_KERNEL);
		अगर (!slot) अणु
			result = -ENOMEM;
			जाओ error;
		पूर्ण

		slot->ctrl = ctrl;
		slot->bus = ctrl->bus;
		slot->device = slot_device;
		slot->number = slot_number;
		dbg("slot->number = %u\n", slot->number);

		slot_entry = get_SMBIOS_entry(smbios_start, smbios_table, 9,
					slot_entry);

		जबतक (slot_entry && (पढ़ोw(slot_entry + SMBIOS_SLOT_NUMBER) !=
				slot->number)) अणु
			slot_entry = get_SMBIOS_entry(smbios_start,
						smbios_table, 9, slot_entry);
		पूर्ण

		slot->p_sm_slot = slot_entry;

		समयr_setup(&slot->task_event, cpqhp_pushbutton_thपढ़ो, 0);
		slot->task_event.expires = jअगरfies + 5 * HZ;

		/*FIXME: these capabilities aren't used but अगर they are
		 *	 they need to be correctly implemented
		 */
		slot->capabilities |= PCISLOT_REPLACE_SUPPORTED;
		slot->capabilities |= PCISLOT_INTERLOCK_SUPPORTED;

		अगर (is_slot64bit(slot))
			slot->capabilities |= PCISLOT_64_BIT_SUPPORTED;
		अगर (is_slot66mhz(slot))
			slot->capabilities |= PCISLOT_66_MHZ_SUPPORTED;
		अगर (bus->cur_bus_speed == PCI_SPEED_66MHz)
			slot->capabilities |= PCISLOT_66_MHZ_OPERATION;

		ctrl_slot =
			slot_device - (पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4);

		/* Check presence */
		slot->capabilities |=
			((((~tempdword) >> 23) |
			 ((~tempdword) >> 15)) >> ctrl_slot) & 0x02;
		/* Check the चयन state */
		slot->capabilities |=
			((~tempdword & 0xFF) >> ctrl_slot) & 0x01;
		/* Check the slot enable */
		slot->capabilities |=
			((पढ़ो_slot_enable(ctrl) << 2) >> ctrl_slot) & 0x04;

		/* रेजिस्टर this slot with the hotplug pci core */
		snम_लिखो(name, SLOT_NAME_SIZE, "%u", slot->number);
		slot->hotplug_slot.ops = &cpqphp_hotplug_slot_ops;

		dbg("registering bus %d, dev %d, number %d, ctrl->slot_device_offset %d, slot %d\n",
				slot->bus, slot->device,
				slot->number, ctrl->slot_device_offset,
				slot_number);
		result = pci_hp_रेजिस्टर(&slot->hotplug_slot,
					 ctrl->pci_dev->bus,
					 slot->device,
					 name);
		अगर (result) अणु
			err("pci_hp_register failed with error %d\n", result);
			जाओ error_slot;
		पूर्ण

		slot->next = ctrl->slot;
		ctrl->slot = slot;

		number_of_slots--;
		slot_device++;
		slot_number++;
	पूर्ण

	वापस 0;
error_slot:
	kमुक्त(slot);
error:
	वापस result;
पूर्ण

अटल पूर्णांक one_समय_init(व्योम)
अणु
	पूर्णांक loop;
	पूर्णांक retval = 0;

	अगर (initialized)
		वापस 0;

	घातer_mode = 0;

	retval = init_cpqhp_routing_table();
	अगर (retval)
		जाओ error;

	अगर (cpqhp_debug)
		pci_prपूर्णांक_IRQ_route();

	dbg("Initialize + Start the notification mechanism\n");

	retval = cpqhp_event_start_thपढ़ो();
	अगर (retval)
		जाओ error;

	dbg("Initialize slot lists\n");
	क्रम (loop = 0; loop < 256; loop++)
		cpqhp_slot_list[loop] = शून्य;

	/* FIXME: We also need to hook the NMI handler eventually.
	 * this also needs to be worked with Christoph
	 * रेजिस्टर_NMI_handler();
	 */
	/* Map rom address */
	cpqhp_rom_start = ioremap(ROM_PHY_ADDR, ROM_PHY_LEN);
	अगर (!cpqhp_rom_start) अणु
		err("Could not ioremap memory region for ROM\n");
		retval = -EIO;
		जाओ error;
	पूर्ण

	/* Now, map the पूर्णांक15 entry poपूर्णांक अगर we are on compaq specअगरic
	 * hardware
	 */
	compaq_nvram_init(cpqhp_rom_start);

	/* Map smbios table entry poपूर्णांक काष्ठाure */
	smbios_table = detect_SMBIOS_poपूर्णांकer(cpqhp_rom_start,
					cpqhp_rom_start + ROM_PHY_LEN);
	अगर (!smbios_table) अणु
		err("Could not find the SMBIOS pointer in memory\n");
		retval = -EIO;
		जाओ error_rom_start;
	पूर्ण

	smbios_start = ioremap(पढ़ोl(smbios_table + ST_ADDRESS),
					पढ़ोw(smbios_table + ST_LENGTH));
	अगर (!smbios_start) अणु
		err("Could not ioremap memory region taken from SMBIOS values\n");
		retval = -EIO;
		जाओ error_smbios_start;
	पूर्ण

	initialized = 1;

	वापस retval;

error_smbios_start:
	iounmap(smbios_start);
error_rom_start:
	iounmap(cpqhp_rom_start);
error:
	वापस retval;
पूर्ण

अटल पूर्णांक cpqhpc_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	u8 num_of_slots = 0;
	u8 hp_slot = 0;
	u8 device;
	u8 bus_cap;
	u16 temp_word;
	u16 venकरोr_id;
	u16 subप्रणाली_vid;
	u16 subप्रणाली_deviceid;
	u32 rc;
	काष्ठा controller *ctrl;
	काष्ठा pci_func *func;
	काष्ठा pci_bus *bus;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR MY_NAME ": cannot enable PCI device %s (%d)\n",
			pci_name(pdev), err);
		वापस err;
	पूर्ण

	bus = pdev->subordinate;
	अगर (!bus) अणु
		pci_notice(pdev, "the device is not a bridge, skipping\n");
		rc = -ENODEV;
		जाओ err_disable_device;
	पूर्ण

	/* Need to पढ़ो VID early b/c it's used to dअगरferentiate CPQ and INTC
	 * discovery
	 */
	venकरोr_id = pdev->venकरोr;
	अगर ((venकरोr_id != PCI_VENDOR_ID_COMPAQ) &&
	    (venकरोr_id != PCI_VENDOR_ID_INTEL)) अणु
		err(msg_HPC_non_compaq_or_पूर्णांकel);
		rc = -ENODEV;
		जाओ err_disable_device;
	पूर्ण
	dbg("Vendor ID: %x\n", venकरोr_id);

	dbg("revision: %d\n", pdev->revision);
	अगर ((venकरोr_id == PCI_VENDOR_ID_COMPAQ) && (!pdev->revision)) अणु
		err(msg_HPC_rev_error);
		rc = -ENODEV;
		जाओ err_disable_device;
	पूर्ण

	/* Check क्रम the proper subप्रणाली IDs
	 * Intel uses a dअगरferent SSID programming model than Compaq.
	 * For Intel, each SSID bit identअगरies a PHP capability.
	 * Also Intel HPCs may have RID=0.
	 */
	अगर ((pdev->revision <= 2) && (venकरोr_id != PCI_VENDOR_ID_INTEL)) अणु
		err(msg_HPC_not_supported);
		rc = -ENODEV;
		जाओ err_disable_device;
	पूर्ण

	/* TODO: This code can be made to support non-Compaq or Intel
	 * subप्रणाली IDs
	 */
	subप्रणाली_vid = pdev->subप्रणाली_venकरोr;
	dbg("Subsystem Vendor ID: %x\n", subप्रणाली_vid);
	अगर ((subप्रणाली_vid != PCI_VENDOR_ID_COMPAQ) && (subप्रणाली_vid != PCI_VENDOR_ID_INTEL)) अणु
		err(msg_HPC_non_compaq_or_पूर्णांकel);
		rc = -ENODEV;
		जाओ err_disable_device;
	पूर्ण

	ctrl = kzalloc(माप(काष्ठा controller), GFP_KERNEL);
	अगर (!ctrl) अणु
		rc = -ENOMEM;
		जाओ err_disable_device;
	पूर्ण

	subप्रणाली_deviceid = pdev->subप्रणाली_device;

	info("Hot Plug Subsystem Device ID: %x\n", subप्रणाली_deviceid);

	/* Set Venकरोr ID, so it can be accessed later from other
	 * functions
	 */
	ctrl->venकरोr_id = venकरोr_id;

	चयन (subप्रणाली_vid) अणु
	हाल PCI_VENDOR_ID_COMPAQ:
		अगर (pdev->revision >= 0x13) अणु /* CIOBX */
			ctrl->push_flag = 1;
			ctrl->slot_चयन_type = 1;
			ctrl->push_button = 1;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 1;
			ctrl->pcix_speed_capability = 1;
			pci_पढ़ो_config_byte(pdev, 0x41, &bus_cap);
			अगर (bus_cap & 0x80) अणु
				dbg("bus max supports 133MHz PCI-X\n");
				bus->max_bus_speed = PCI_SPEED_133MHz_PCIX;
				अवरोध;
			पूर्ण
			अगर (bus_cap & 0x40) अणु
				dbg("bus max supports 100MHz PCI-X\n");
				bus->max_bus_speed = PCI_SPEED_100MHz_PCIX;
				अवरोध;
			पूर्ण
			अगर (bus_cap & 0x20) अणु
				dbg("bus max supports 66MHz PCI-X\n");
				bus->max_bus_speed = PCI_SPEED_66MHz_PCIX;
				अवरोध;
			पूर्ण
			अगर (bus_cap & 0x10) अणु
				dbg("bus max supports 66MHz PCI\n");
				bus->max_bus_speed = PCI_SPEED_66MHz;
				अवरोध;
			पूर्ण

			अवरोध;
		पूर्ण

		चयन (subप्रणाली_deviceid) अणु
		हाल PCI_SUB_HPC_ID:
			/* Original 6500/7000 implementation */
			ctrl->slot_चयन_type = 1;
			bus->max_bus_speed = PCI_SPEED_33MHz;
			ctrl->push_button = 0;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 0;
			ctrl->pcix_speed_capability = 0;
			अवरोध;
		हाल PCI_SUB_HPC_ID2:
			/* First Pushbutton implementation */
			ctrl->push_flag = 1;
			ctrl->slot_चयन_type = 1;
			bus->max_bus_speed = PCI_SPEED_33MHz;
			ctrl->push_button = 1;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 0;
			ctrl->pcix_speed_capability = 0;
			अवरोध;
		हाल PCI_SUB_HPC_ID_INTC:
			/* Third party (6500/7000) */
			ctrl->slot_चयन_type = 1;
			bus->max_bus_speed = PCI_SPEED_33MHz;
			ctrl->push_button = 0;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 0;
			ctrl->pcix_speed_capability = 0;
			अवरोध;
		हाल PCI_SUB_HPC_ID3:
			/* First 66 Mhz implementation */
			ctrl->push_flag = 1;
			ctrl->slot_चयन_type = 1;
			bus->max_bus_speed = PCI_SPEED_66MHz;
			ctrl->push_button = 1;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 0;
			ctrl->pcix_speed_capability = 0;
			अवरोध;
		हाल PCI_SUB_HPC_ID4:
			/* First PCI-X implementation, 100MHz */
			ctrl->push_flag = 1;
			ctrl->slot_चयन_type = 1;
			bus->max_bus_speed = PCI_SPEED_100MHz_PCIX;
			ctrl->push_button = 1;
			ctrl->pci_config_space = 1;
			ctrl->defeature_PHP = 1;
			ctrl->pcix_support = 1;
			ctrl->pcix_speed_capability = 0;
			अवरोध;
		शेष:
			err(msg_HPC_not_supported);
			rc = -ENODEV;
			जाओ err_मुक्त_ctrl;
		पूर्ण
		अवरोध;

	हाल PCI_VENDOR_ID_INTEL:
		/* Check क्रम speed capability (0=33, 1=66) */
		अगर (subप्रणाली_deviceid & 0x0001)
			bus->max_bus_speed = PCI_SPEED_66MHz;
		अन्यथा
			bus->max_bus_speed = PCI_SPEED_33MHz;

		/* Check क्रम push button */
		अगर (subप्रणाली_deviceid & 0x0002)
			ctrl->push_button = 0;
		अन्यथा
			ctrl->push_button = 1;

		/* Check क्रम slot चयन type (0=mechanical, 1=not mechanical) */
		अगर (subप्रणाली_deviceid & 0x0004)
			ctrl->slot_चयन_type = 0;
		अन्यथा
			ctrl->slot_चयन_type = 1;

		/* PHP Status (0=De-feature PHP, 1=Normal operation) */
		अगर (subप्रणाली_deviceid & 0x0008)
			ctrl->defeature_PHP = 1;	/* PHP supported */
		अन्यथा
			ctrl->defeature_PHP = 0;	/* PHP not supported */

		/* Alternate Base Address Register Interface
		 * (0=not supported, 1=supported)
		 */
		अगर (subप्रणाली_deviceid & 0x0010)
			ctrl->alternate_base_address = 1;
		अन्यथा
			ctrl->alternate_base_address = 0;

		/* PCI Config Space Index (0=not supported, 1=supported) */
		अगर (subप्रणाली_deviceid & 0x0020)
			ctrl->pci_config_space = 1;
		अन्यथा
			ctrl->pci_config_space = 0;

		/* PCI-X support */
		अगर (subप्रणाली_deviceid & 0x0080) अणु
			ctrl->pcix_support = 1;
			अगर (subप्रणाली_deviceid & 0x0040)
				/* 133MHz PCI-X अगर bit 7 is 1 */
				ctrl->pcix_speed_capability = 1;
			अन्यथा
				/* 100MHz PCI-X अगर bit 7 is 1 and bit 0 is 0, */
				/* 66MHz PCI-X अगर bit 7 is 1 and bit 0 is 1 */
				ctrl->pcix_speed_capability = 0;
		पूर्ण अन्यथा अणु
			/* Conventional PCI */
			ctrl->pcix_support = 0;
			ctrl->pcix_speed_capability = 0;
		पूर्ण
		अवरोध;

	शेष:
		err(msg_HPC_not_supported);
		rc = -ENODEV;
		जाओ err_मुक्त_ctrl;
	पूर्ण

	/* Tell the user that we found one. */
	info("Initializing the PCI hot plug controller residing on PCI bus %d\n",
					pdev->bus->number);

	dbg("Hotplug controller capabilities:\n");
	dbg("    speed_capability       %d\n", bus->max_bus_speed);
	dbg("    slot_switch_type       %s\n", ctrl->slot_चयन_type ?
					"switch present" : "no switch");
	dbg("    defeature_PHP          %s\n", ctrl->defeature_PHP ?
					"PHP supported" : "PHP not supported");
	dbg("    alternate_base_address %s\n", ctrl->alternate_base_address ?
					"supported" : "not supported");
	dbg("    pci_config_space       %s\n", ctrl->pci_config_space ?
					"supported" : "not supported");
	dbg("    pcix_speed_capability  %s\n", ctrl->pcix_speed_capability ?
					"supported" : "not supported");
	dbg("    pcix_support           %s\n", ctrl->pcix_support ?
					"supported" : "not supported");

	ctrl->pci_dev = pdev;
	pci_set_drvdata(pdev, ctrl);

	/* make our own copy of the pci bus काष्ठाure,
	 * as we like tweaking it a lot */
	ctrl->pci_bus = kmemdup(pdev->bus, माप(*ctrl->pci_bus), GFP_KERNEL);
	अगर (!ctrl->pci_bus) अणु
		err("out of memory\n");
		rc = -ENOMEM;
		जाओ err_मुक्त_ctrl;
	पूर्ण

	ctrl->bus = pdev->bus->number;
	ctrl->rev = pdev->revision;
	dbg("bus device function rev: %d %d %d %d\n", ctrl->bus,
		PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn), ctrl->rev);

	mutex_init(&ctrl->crit_sect);
	init_रुकोqueue_head(&ctrl->queue);

	/* initialize our thपढ़ोs अगर they haven't alपढ़ोy been started up */
	rc = one_समय_init();
	अगर (rc)
		जाओ err_मुक्त_bus;

	dbg("pdev = %p\n", pdev);
	dbg("pci resource start %llx\n", (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0));
	dbg("pci resource len %llx\n", (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 0));

	अगर (!request_mem_region(pci_resource_start(pdev, 0),
				pci_resource_len(pdev, 0), MY_NAME)) अणु
		err("cannot reserve MMIO region\n");
		rc = -ENOMEM;
		जाओ err_मुक्त_bus;
	पूर्ण

	ctrl->hpc_reg = ioremap(pci_resource_start(pdev, 0),
					pci_resource_len(pdev, 0));
	अगर (!ctrl->hpc_reg) अणु
		err("cannot remap MMIO region %llx @ %llx\n",
		    (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 0),
		    (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0));
		rc = -ENODEV;
		जाओ err_मुक्त_mem_region;
	पूर्ण

	/* Check क्रम 66Mhz operation */
	bus->cur_bus_speed = get_controller_speed(ctrl);


	/********************************************************
	 *
	 *              Save configuration headers क्रम this and
	 *              subordinate PCI buses
	 *
	 ********************************************************/

	/* find the physical slot number of the first hot plug slot */

	/* Get slot won't work क्रम devices behind bridges, but
	 * in this हाल it will always be called क्रम the "base"
	 * bus/dev/func of a slot.
	 * CS: this is leveraging the PCIIRQ routing code from the kernel
	 * (pci-pc.c: get_irq_routing_table) */
	rc = get_slot_mapping(ctrl->pci_bus, pdev->bus->number,
				(पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4),
				&(ctrl->first_slot));
	dbg("get_slot_mapping: first_slot = %d, returned = %d\n",
				ctrl->first_slot, rc);
	अगर (rc) अणु
		err(msg_initialization_err, rc);
		जाओ err_iounmap;
	पूर्ण

	/* Store PCI Config Space क्रम all devices on this bus */
	rc = cpqhp_save_config(ctrl, ctrl->bus, पढ़ोb(ctrl->hpc_reg + SLOT_MASK));
	अगर (rc) अणु
		err("%s: unable to save PCI configuration data, error %d\n",
				__func__, rc);
		जाओ err_iounmap;
	पूर्ण

	/*
	 * Get IO, memory, and IRQ resources क्रम new devices
	 */
	/* The next line is required क्रम cpqhp_find_available_resources */
	ctrl->पूर्णांकerrupt = pdev->irq;
	अगर (ctrl->पूर्णांकerrupt < 0x10) अणु
		cpqhp_legacy_mode = 1;
		dbg("System seems to be configured for Full Table Mapped MPS mode\n");
	पूर्ण

	ctrl->cfgspc_irq = 0;
	pci_पढ़ो_config_byte(pdev, PCI_INTERRUPT_LINE, &ctrl->cfgspc_irq);

	rc = cpqhp_find_available_resources(ctrl, cpqhp_rom_start);
	ctrl->add_support = !rc;
	अगर (rc) अणु
		dbg("cpqhp_find_available_resources = 0x%x\n", rc);
		err("unable to locate PCI configuration resources for hot plug add.\n");
		जाओ err_iounmap;
	पूर्ण

	/*
	 * Finish setting up the hot plug ctrl device
	 */
	ctrl->slot_device_offset = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4;
	dbg("NumSlots %d\n", ctrl->slot_device_offset);

	ctrl->next_event = 0;

	/* Setup the slot inक्रमmation काष्ठाures */
	rc = ctrl_slot_setup(ctrl, smbios_start, smbios_table);
	अगर (rc) अणु
		err(msg_initialization_err, 6);
		err("%s: unable to save PCI configuration data, error %d\n",
			__func__, rc);
		जाओ err_iounmap;
	पूर्ण

	/* Mask all general input पूर्णांकerrupts */
	ग_लिखोl(0xFFFFFFFFL, ctrl->hpc_reg + INT_MASK);

	/* set up the पूर्णांकerrupt */
	dbg("HPC interrupt = %d\n", ctrl->पूर्णांकerrupt);
	अगर (request_irq(ctrl->पूर्णांकerrupt, cpqhp_ctrl_पूर्णांकr,
			IRQF_SHARED, MY_NAME, ctrl)) अणु
		err("Can't get irq %d for the hotplug pci controller\n",
			ctrl->पूर्णांकerrupt);
		rc = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	/* Enable Shअगरt Out पूर्णांकerrupt and clear it, also enable SERR on घातer
	 * fault
	 */
	temp_word = पढ़ोw(ctrl->hpc_reg + MISC);
	temp_word |= 0x4006;
	ग_लिखोw(temp_word, ctrl->hpc_reg + MISC);

	/* Changed 05/05/97 to clear all पूर्णांकerrupts at start */
	ग_लिखोl(0xFFFFFFFFL, ctrl->hpc_reg + INT_INPUT_CLEAR);

	ctrl->ctrl_पूर्णांक_comp = पढ़ोl(ctrl->hpc_reg + INT_INPUT_CLEAR);

	ग_लिखोl(0x0L, ctrl->hpc_reg + INT_MASK);

	अगर (!cpqhp_ctrl_list) अणु
		cpqhp_ctrl_list = ctrl;
		ctrl->next = शून्य;
	पूर्ण अन्यथा अणु
		ctrl->next = cpqhp_ctrl_list;
		cpqhp_ctrl_list = ctrl;
	पूर्ण

	/* turn off empty slots here unless command line option "ON" set
	 * Wait क्रम exclusive access to hardware
	 */
	mutex_lock(&ctrl->crit_sect);

	num_of_slots = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) & 0x0F;

	/* find first device number क्रम the ctrl */
	device = पढ़ोb(ctrl->hpc_reg + SLOT_MASK) >> 4;

	जबतक (num_of_slots) अणु
		dbg("num_of_slots: %d\n", num_of_slots);
		func = cpqhp_slot_find(ctrl->bus, device, 0);
		अगर (!func)
			अवरोध;

		hp_slot = func->device - ctrl->slot_device_offset;
		dbg("hp_slot: %d\n", hp_slot);

		/* We have to save the presence info क्रम these slots */
		temp_word = ctrl->ctrl_पूर्णांक_comp >> 16;
		func->presence_save = (temp_word >> hp_slot) & 0x01;
		func->presence_save |= (temp_word >> (hp_slot + 7)) & 0x02;

		अगर (ctrl->ctrl_पूर्णांक_comp & (0x1L << hp_slot))
			func->चयन_save = 0;
		अन्यथा
			func->चयन_save = 0x10;

		अगर (!घातer_mode)
			अगर (!func->is_a_board) अणु
				green_LED_off(ctrl, hp_slot);
				slot_disable(ctrl, hp_slot);
			पूर्ण

		device++;
		num_of_slots--;
	पूर्ण

	अगर (!घातer_mode) अणु
		set_SOGO(ctrl);
		/* Wait क्रम SOBS to be unset */
		रुको_क्रम_ctrl_irq(ctrl);
	पूर्ण

	rc = init_SERR(ctrl);
	अगर (rc) अणु
		err("init_SERR failed\n");
		mutex_unlock(&ctrl->crit_sect);
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Done with exclusive hardware access */
	mutex_unlock(&ctrl->crit_sect);

	cpqhp_create_debugfs_files(ctrl);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(ctrl->पूर्णांकerrupt, ctrl);
err_iounmap:
	iounmap(ctrl->hpc_reg);
err_मुक्त_mem_region:
	release_mem_region(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
err_मुक्त_bus:
	kमुक्त(ctrl->pci_bus);
err_मुक्त_ctrl:
	kमुक्त(ctrl);
err_disable_device:
	pci_disable_device(pdev);
	वापस rc;
पूर्ण

अटल व्योम __निकास unload_cpqphpd(व्योम)
अणु
	काष्ठा pci_func *next;
	काष्ठा pci_func *TempSlot;
	पूर्णांक loop;
	u32 rc;
	काष्ठा controller *ctrl;
	काष्ठा controller *tctrl;
	काष्ठा pci_resource *res;
	काष्ठा pci_resource *tres;

	rc = compaq_nvram_store(cpqhp_rom_start);

	ctrl = cpqhp_ctrl_list;

	जबतक (ctrl) अणु
		अगर (ctrl->hpc_reg) अणु
			u16 misc;
			rc = पढ़ो_slot_enable(ctrl);

			ग_लिखोb(0, ctrl->hpc_reg + SLOT_SERR);
			ग_लिखोl(0xFFFFFFC0L | ~rc, ctrl->hpc_reg + INT_MASK);

			misc = पढ़ोw(ctrl->hpc_reg + MISC);
			misc &= 0xFFFD;
			ग_लिखोw(misc, ctrl->hpc_reg + MISC);
		पूर्ण

		ctrl_slot_cleanup(ctrl);

		res = ctrl->io_head;
		जबतक (res) अणु
			tres = res;
			res = res->next;
			kमुक्त(tres);
		पूर्ण

		res = ctrl->mem_head;
		जबतक (res) अणु
			tres = res;
			res = res->next;
			kमुक्त(tres);
		पूर्ण

		res = ctrl->p_mem_head;
		जबतक (res) अणु
			tres = res;
			res = res->next;
			kमुक्त(tres);
		पूर्ण

		res = ctrl->bus_head;
		जबतक (res) अणु
			tres = res;
			res = res->next;
			kमुक्त(tres);
		पूर्ण

		kमुक्त(ctrl->pci_bus);

		tctrl = ctrl;
		ctrl = ctrl->next;
		kमुक्त(tctrl);
	पूर्ण

	क्रम (loop = 0; loop < 256; loop++) अणु
		next = cpqhp_slot_list[loop];
		जबतक (next != शून्य) अणु
			res = next->io_head;
			जबतक (res) अणु
				tres = res;
				res = res->next;
				kमुक्त(tres);
			पूर्ण

			res = next->mem_head;
			जबतक (res) अणु
				tres = res;
				res = res->next;
				kमुक्त(tres);
			पूर्ण

			res = next->p_mem_head;
			जबतक (res) अणु
				tres = res;
				res = res->next;
				kमुक्त(tres);
			पूर्ण

			res = next->bus_head;
			जबतक (res) अणु
				tres = res;
				res = res->next;
				kमुक्त(tres);
			पूर्ण

			TempSlot = next;
			next = next->next;
			kमुक्त(TempSlot);
		पूर्ण
	पूर्ण

	/* Stop the notअगरication mechanism */
	अगर (initialized)
		cpqhp_event_stop_thपढ़ो();

	/* unmap the rom address */
	अगर (cpqhp_rom_start)
		iounmap(cpqhp_rom_start);
	अगर (smbios_start)
		iounmap(smbios_start);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hpcd_pci_tbl[] = अणु
	अणु
	/* handle any PCI Hotplug controller */
	.class =        ((PCI_CLASS_SYSTEM_PCI_HOTPLUG << 8) | 0x00),
	.class_mask =   ~0,

	/* no matter who makes it */
	.venकरोr =       PCI_ANY_ID,
	.device =       PCI_ANY_ID,
	.subvenकरोr =    PCI_ANY_ID,
	.subdevice =    PCI_ANY_ID,

	पूर्ण, अणु /* end: all zeroes */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hpcd_pci_tbl);

अटल काष्ठा pci_driver cpqhpc_driver = अणु
	.name =		"compaq_pci_hotplug",
	.id_table =	hpcd_pci_tbl,
	.probe =	cpqhpc_probe,
	/* हटाओ:	cpqhpc_हटाओ_one, */
पूर्ण;

अटल पूर्णांक __init cpqhpc_init(व्योम)
अणु
	पूर्णांक result;

	cpqhp_debug = debug;

	info(DRIVER_DESC " version: " DRIVER_VERSION "\n");
	cpqhp_initialize_debugfs();
	result = pci_रेजिस्टर_driver(&cpqhpc_driver);
	dbg("pci_register_driver = %d\n", result);
	वापस result;
पूर्ण

अटल व्योम __निकास cpqhpc_cleanup(व्योम)
अणु
	dbg("unload_cpqphpd()\n");
	unload_cpqphpd();

	dbg("pci_unregister_driver\n");
	pci_unरेजिस्टर_driver(&cpqhpc_driver);
	cpqhp_shutकरोwn_debugfs();
पूर्ण

module_init(cpqhpc_init);
module_निकास(cpqhpc_cleanup);
