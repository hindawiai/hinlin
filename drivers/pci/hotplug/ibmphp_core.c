<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM Hot Plug Controller Driver
 *
 * Written By: Chuck Cole, Jyoti Shah, Tong Yu, Irene Zubarev, IBM Corporation
 *
 * Copyright (C) 2001,2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001-2003 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश "../pci.h"
#समावेश <यंत्र/pci_x86.h>		/* क्रम काष्ठा irq_routing_table */
#समावेश <यंत्र/io_apic.h>
#समावेश "ibmphp.h"

#घोषणा attn_on(sl)  ibmphp_hpc_ग_लिखोslot(sl, HPC_SLOT_ATTNON)
#घोषणा attn_off(sl) ibmphp_hpc_ग_लिखोslot(sl, HPC_SLOT_ATTNOFF)
#घोषणा attn_LED_blink(sl) ibmphp_hpc_ग_लिखोslot(sl, HPC_SLOT_BLINKLED)
#घोषणा get_ctrl_revision(sl, rev) ibmphp_hpc_पढ़ोslot(sl, READ_REVLEVEL, rev)
#घोषणा get_hpc_options(sl, opt) ibmphp_hpc_पढ़ोslot(sl, READ_HPCOPTIONS, opt)

#घोषणा DRIVER_VERSION	"0.6"
#घोषणा DRIVER_DESC	"IBM Hot Plug PCI Controller Driver"

पूर्णांक ibmphp_debug;

अटल bool debug;
module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debugging mode enabled or not");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);

काष्ठा pci_bus *ibmphp_pci_bus;
अटल पूर्णांक max_slots;

अटल पूर्णांक irqs[16];    /* PIC mode IRQs we're using so far (in हाल MPS
			 * tables करोn't provide शेष info क्रम empty slots */

अटल पूर्णांक init_flag;

/*
अटल पूर्णांक get_max_adapter_speed_1 (काष्ठा hotplug_slot *, u8 *, u8);

अटल अंतरभूत पूर्णांक get_max_adapter_speed (काष्ठा hotplug_slot *hs, u8 *value)
अणु
	वापस get_max_adapter_speed_1 (hs, value, 1);
पूर्ण
*/
अटल अंतरभूत पूर्णांक get_cur_bus_info(काष्ठा slot **sl)
अणु
	पूर्णांक rc = 1;
	काष्ठा slot *slot_cur = *sl;

	debug("options = %x\n", slot_cur->ctrl->options);
	debug("revision = %x\n", slot_cur->ctrl->revision);

	अगर (READ_BUS_STATUS(slot_cur->ctrl))
		rc = ibmphp_hpc_पढ़ोslot(slot_cur, READ_BUSSTATUS, शून्य);

	अगर (rc)
		वापस rc;

	slot_cur->bus_on->current_speed = CURRENT_BUS_SPEED(slot_cur->busstatus);
	अगर (READ_BUS_MODE(slot_cur->ctrl))
		slot_cur->bus_on->current_bus_mode =
				CURRENT_BUS_MODE(slot_cur->busstatus);
	अन्यथा
		slot_cur->bus_on->current_bus_mode = 0xFF;

	debug("busstatus = %x, bus_speed = %x, bus_mode = %x\n",
			slot_cur->busstatus,
			slot_cur->bus_on->current_speed,
			slot_cur->bus_on->current_bus_mode);

	*sl = slot_cur;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक slot_update(काष्ठा slot **sl)
अणु
	पूर्णांक rc;
	rc = ibmphp_hpc_पढ़ोslot(*sl, READ_ALLSTAT, शून्य);
	अगर (rc)
		वापस rc;
	अगर (!init_flag)
		rc = get_cur_bus_info(sl);
	वापस rc;
पूर्ण

अटल पूर्णांक __init get_max_slots(व्योम)
अणु
	काष्ठा slot *slot_cur;
	u8 slot_count = 0;

	list_क्रम_each_entry(slot_cur, &ibmphp_slot_head, ibm_slot_list) अणु
		/* someबार the hot-pluggable slots start with 4 (not always from 1) */
		slot_count = max(slot_count, slot_cur->number);
	पूर्ण
	वापस slot_count;
पूर्ण

/* This routine will put the correct slot->device inक्रमmation per slot.  It's
 * called from initialization of the slot काष्ठाures. It will also assign
 * पूर्णांकerrupt numbers per each slot.
 * Parameters: काष्ठा slot
 * Returns 0 or errors
 */
पूर्णांक ibmphp_init_devno(काष्ठा slot **cur_slot)
अणु
	काष्ठा irq_routing_table *rtable;
	पूर्णांक len;
	पूर्णांक loop;
	पूर्णांक i;

	rtable = pcibios_get_irq_routing_table();
	अगर (!rtable) अणु
		err("no BIOS routing table...\n");
		वापस -ENOMEM;
	पूर्ण

	len = (rtable->size - माप(काष्ठा irq_routing_table)) /
			माप(काष्ठा irq_info);

	अगर (!len) अणु
		kमुक्त(rtable);
		वापस -1;
	पूर्ण
	क्रम (loop = 0; loop < len; loop++) अणु
		अगर ((*cur_slot)->number == rtable->slots[loop].slot &&
		    (*cur_slot)->bus == rtable->slots[loop].bus) अणु
			(*cur_slot)->device = PCI_SLOT(rtable->slots[loop].devfn);
			क्रम (i = 0; i < 4; i++)
				(*cur_slot)->irq[i] = IO_APIC_get_PCI_irq_vector((पूर्णांक) (*cur_slot)->bus,
						(पूर्णांक) (*cur_slot)->device, i);

			debug("(*cur_slot)->irq[0] = %x\n",
					(*cur_slot)->irq[0]);
			debug("(*cur_slot)->irq[1] = %x\n",
					(*cur_slot)->irq[1]);
			debug("(*cur_slot)->irq[2] = %x\n",
					(*cur_slot)->irq[2]);
			debug("(*cur_slot)->irq[3] = %x\n",
					(*cur_slot)->irq[3]);

			debug("rtable->exclusive_irqs = %x\n",
					rtable->exclusive_irqs);
			debug("rtable->slots[loop].irq[0].bitmap = %x\n",
					rtable->slots[loop].irq[0].biपंचांगap);
			debug("rtable->slots[loop].irq[1].bitmap = %x\n",
					rtable->slots[loop].irq[1].biपंचांगap);
			debug("rtable->slots[loop].irq[2].bitmap = %x\n",
					rtable->slots[loop].irq[2].biपंचांगap);
			debug("rtable->slots[loop].irq[3].bitmap = %x\n",
					rtable->slots[loop].irq[3].biपंचांगap);

			debug("rtable->slots[loop].irq[0].link = %x\n",
					rtable->slots[loop].irq[0].link);
			debug("rtable->slots[loop].irq[1].link = %x\n",
					rtable->slots[loop].irq[1].link);
			debug("rtable->slots[loop].irq[2].link = %x\n",
					rtable->slots[loop].irq[2].link);
			debug("rtable->slots[loop].irq[3].link = %x\n",
					rtable->slots[loop].irq[3].link);
			debug("end of init_devno\n");
			kमुक्त(rtable);
			वापस 0;
		पूर्ण
	पूर्ण

	kमुक्त(rtable);
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक घातer_on(काष्ठा slot *slot_cur)
अणु
	u8 cmd = HPC_SLOT_ON;
	पूर्णांक retval;

	retval = ibmphp_hpc_ग_लिखोslot(slot_cur, cmd);
	अगर (retval) अणु
		err("power on failed\n");
		वापस retval;
	पूर्ण
	अगर (CTLR_RESULT(slot_cur->ctrl->status)) अणु
		err("command not completed successfully in power_on\n");
		वापस -EIO;
	पूर्ण
	msleep(3000);	/* For ServeRAID cards, and some 66 PCI */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक घातer_off(काष्ठा slot *slot_cur)
अणु
	u8 cmd = HPC_SLOT_OFF;
	पूर्णांक retval;

	retval = ibmphp_hpc_ग_लिखोslot(slot_cur, cmd);
	अगर (retval) अणु
		err("power off failed\n");
		वापस retval;
	पूर्ण
	अगर (CTLR_RESULT(slot_cur->ctrl->status)) अणु
		err("command not completed successfully in power_off\n");
		retval = -EIO;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 value)
अणु
	पूर्णांक rc = 0;
	काष्ठा slot *pslot;
	u8 cmd = 0x00;     /* aव्योम compiler warning */

	debug("set_attention_status - Entry hotplug_slot[%lx] value[%x]\n",
			(uदीर्घ) hotplug_slot, value);
	ibmphp_lock_operations();


	अगर (hotplug_slot) अणु
		चयन (value) अणु
		हाल HPC_SLOT_ATTN_OFF:
			cmd = HPC_SLOT_ATTNOFF;
			अवरोध;
		हाल HPC_SLOT_ATTN_ON:
			cmd = HPC_SLOT_ATTNON;
			अवरोध;
		हाल HPC_SLOT_ATTN_BLINK:
			cmd = HPC_SLOT_BLINKLED;
			अवरोध;
		शेष:
			rc = -ENODEV;
			err("set_attention_status - Error : invalid input [%x]\n",
					value);
			अवरोध;
		पूर्ण
		अगर (rc == 0) अणु
			pslot = to_slot(hotplug_slot);
			rc = ibmphp_hpc_ग_लिखोslot(pslot, cmd);
		पूर्ण
	पूर्ण अन्यथा
		rc = -ENODEV;

	ibmphp_unlock_operations();

	debug("set_attention_status - Exit rc[%d]\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot;
	काष्ठा slot myslot;

	debug("get_attention_status - Entry hotplug_slot[%lx] pvalue[%lx]\n",
					(uदीर्घ) hotplug_slot, (uदीर्घ) value);

	ibmphp_lock_operations();
	अगर (hotplug_slot) अणु
		pslot = to_slot(hotplug_slot);
		स_नकल(&myslot, pslot, माप(काष्ठा slot));
		rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS,
					 &myslot.status);
		अगर (!rc)
			rc = ibmphp_hpc_पढ़ोslot(pslot, READ_EXTSLOTSTATUS,
						 &myslot.ext_status);
		अगर (!rc)
			*value = SLOT_ATTN(myslot.status, myslot.ext_status);
	पूर्ण

	ibmphp_unlock_operations();
	debug("get_attention_status - Exit rc[%d] value[%x]\n", rc, *value);
	वापस rc;
पूर्ण

अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot;
	काष्ठा slot myslot;

	debug("get_latch_status - Entry hotplug_slot[%lx] pvalue[%lx]\n",
					(uदीर्घ) hotplug_slot, (uदीर्घ) value);
	ibmphp_lock_operations();
	अगर (hotplug_slot) अणु
		pslot = to_slot(hotplug_slot);
		स_नकल(&myslot, pslot, माप(काष्ठा slot));
		rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS,
					 &myslot.status);
		अगर (!rc)
			*value = SLOT_LATCH(myslot.status);
	पूर्ण

	ibmphp_unlock_operations();
	debug("get_latch_status - Exit rc[%d] rc[%x] value[%x]\n",
			rc, rc, *value);
	वापस rc;
पूर्ण


अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot;
	काष्ठा slot myslot;

	debug("get_power_status - Entry hotplug_slot[%lx] pvalue[%lx]\n",
					(uदीर्घ) hotplug_slot, (uदीर्घ) value);
	ibmphp_lock_operations();
	अगर (hotplug_slot) अणु
		pslot = to_slot(hotplug_slot);
		स_नकल(&myslot, pslot, माप(काष्ठा slot));
		rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS,
					 &myslot.status);
		अगर (!rc)
			*value = SLOT_PWRGD(myslot.status);
	पूर्ण

	ibmphp_unlock_operations();
	debug("get_power_status - Exit rc[%d] rc[%x] value[%x]\n",
			rc, rc, *value);
	वापस rc;
पूर्ण

अटल पूर्णांक get_adapter_present(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot;
	u8 present;
	काष्ठा slot myslot;

	debug("get_adapter_status - Entry hotplug_slot[%lx] pvalue[%lx]\n",
					(uदीर्घ) hotplug_slot, (uदीर्घ) value);
	ibmphp_lock_operations();
	अगर (hotplug_slot) अणु
		pslot = to_slot(hotplug_slot);
		स_नकल(&myslot, pslot, माप(काष्ठा slot));
		rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS,
					 &myslot.status);
		अगर (!rc) अणु
			present = SLOT_PRESENT(myslot.status);
			अगर (present == HPC_SLOT_EMPTY)
				*value = 0;
			अन्यथा
				*value = 1;
		पूर्ण
	पूर्ण

	ibmphp_unlock_operations();
	debug("get_adapter_present - Exit rc[%d] value[%x]\n", rc, *value);
	वापस rc;
पूर्ण

अटल पूर्णांक get_max_bus_speed(काष्ठा slot *slot)
अणु
	पूर्णांक rc = 0;
	u8 mode = 0;
	क्रमागत pci_bus_speed speed;
	काष्ठा pci_bus *bus = slot->hotplug_slot.pci_slot->bus;

	debug("%s - Entry slot[%p]\n", __func__, slot);

	ibmphp_lock_operations();
	mode = slot->supported_bus_mode;
	speed = slot->supported_speed;
	ibmphp_unlock_operations();

	चयन (speed) अणु
	हाल BUS_SPEED_33:
		अवरोध;
	हाल BUS_SPEED_66:
		अगर (mode == BUS_MODE_PCIX)
			speed += 0x01;
		अवरोध;
	हाल BUS_SPEED_100:
	हाल BUS_SPEED_133:
		speed += 0x01;
		अवरोध;
	शेष:
		/* Note (will need to change): there would be soon 256, 512 also */
		rc = -ENODEV;
	पूर्ण

	अगर (!rc)
		bus->max_bus_speed = speed;

	debug("%s - Exit rc[%d] speed[%x]\n", __func__, rc, speed);
	वापस rc;
पूर्ण

/*
अटल पूर्णांक get_max_adapter_speed_1(काष्ठा hotplug_slot *hotplug_slot, u8 *value, u8 flag)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot;
	काष्ठा slot myslot;

	debug("get_max_adapter_speed_1 - Entry hotplug_slot[%lx] pvalue[%lx]\n",
						(uदीर्घ)hotplug_slot, (uदीर्घ) value);

	अगर (flag)
		ibmphp_lock_operations();

	अगर (hotplug_slot && value) अणु
		pslot = hotplug_slot->निजी;
		अगर (pslot) अणु
			स_नकल(&myslot, pslot, माप(काष्ठा slot));
			rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS,
						&(myslot.status));

			अगर (!(SLOT_LATCH (myslot.status)) &&
					(SLOT_PRESENT (myslot.status))) अणु
				rc = ibmphp_hpc_पढ़ोslot(pslot,
						READ_EXTSLOTSTATUS,
						&(myslot.ext_status));
				अगर (!rc)
					*value = SLOT_SPEED(myslot.ext_status);
			पूर्ण अन्यथा
				*value = MAX_ADAPTER_NONE;
		पूर्ण
	पूर्ण

	अगर (flag)
		ibmphp_unlock_operations();

	debug("get_max_adapter_speed_1 - Exit rc[%d] value[%x]\n", rc, *value);
	वापस rc;
पूर्ण

अटल पूर्णांक get_bus_name(काष्ठा hotplug_slot *hotplug_slot, अक्षर *value)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा slot *pslot = शून्य;

	debug("get_bus_name - Entry hotplug_slot[%lx]\n", (uदीर्घ)hotplug_slot);

	ibmphp_lock_operations();

	अगर (hotplug_slot) अणु
		pslot = hotplug_slot->निजी;
		अगर (pslot) अणु
			rc = 0;
			snम_लिखो(value, 100, "Bus %x", pslot->bus);
		पूर्ण
	पूर्ण अन्यथा
		rc = -ENODEV;

	ibmphp_unlock_operations();
	debug("get_bus_name - Exit rc[%d] value[%x]\n", rc, *value);
	वापस rc;
पूर्ण
*/

/****************************************************************************
 * This routine will initialize the ops data काष्ठाure used in the validate
 * function. It will also घातer off empty slots that are घातered on since BIOS
 * leaves those on, albeit disconnected
 ****************************************************************************/
अटल पूर्णांक __init init_ops(व्योम)
अणु
	काष्ठा slot *slot_cur;
	पूर्णांक retval;
	पूर्णांक rc;

	list_क्रम_each_entry(slot_cur, &ibmphp_slot_head, ibm_slot_list) अणु
		debug("BEFORE GETTING SLOT STATUS, slot # %x\n",
							slot_cur->number);
		अगर (slot_cur->ctrl->revision == 0xFF)
			अगर (get_ctrl_revision(slot_cur,
						&slot_cur->ctrl->revision))
				वापस -1;

		अगर (slot_cur->bus_on->current_speed == 0xFF)
			अगर (get_cur_bus_info(&slot_cur))
				वापस -1;
		get_max_bus_speed(slot_cur);

		अगर (slot_cur->ctrl->options == 0xFF)
			अगर (get_hpc_options(slot_cur, &slot_cur->ctrl->options))
				वापस -1;

		retval = slot_update(&slot_cur);
		अगर (retval)
			वापस retval;

		debug("status = %x\n", slot_cur->status);
		debug("ext_status = %x\n", slot_cur->ext_status);
		debug("SLOT_POWER = %x\n", SLOT_POWER(slot_cur->status));
		debug("SLOT_PRESENT = %x\n", SLOT_PRESENT(slot_cur->status));
		debug("SLOT_LATCH = %x\n", SLOT_LATCH(slot_cur->status));

		अगर ((SLOT_PWRGD(slot_cur->status)) &&
		    !(SLOT_PRESENT(slot_cur->status)) &&
		    !(SLOT_LATCH(slot_cur->status))) अणु
			debug("BEFORE POWER OFF COMMAND\n");
				rc = घातer_off(slot_cur);
				अगर (rc)
					वापस rc;

	/*		retval = slot_update(&slot_cur);
	 *		अगर (retval)
	 *			वापस retval;
	 *		ibmphp_update_slot_info(slot_cur);
	 */
		पूर्ण
	पूर्ण
	init_flag = 0;
	वापस 0;
पूर्ण

/* This operation will check whether the slot is within the bounds and
 * the operation is valid to perक्रमm on that slot
 * Parameters: slot, operation
 * Returns: 0 or error codes
 */
अटल पूर्णांक validate(काष्ठा slot *slot_cur, पूर्णांक opn)
अणु
	पूर्णांक number;
	पूर्णांक retval;

	अगर (!slot_cur)
		वापस -ENODEV;
	number = slot_cur->number;
	अगर ((number > max_slots) || (number < 0))
		वापस -EBADSLT;
	debug("slot_number in validate is %d\n", slot_cur->number);

	retval = slot_update(&slot_cur);
	अगर (retval)
		वापस retval;

	चयन (opn) अणु
		हाल ENABLE:
			अगर (!(SLOT_PWRGD(slot_cur->status)) &&
			     (SLOT_PRESENT(slot_cur->status)) &&
			     !(SLOT_LATCH(slot_cur->status)))
				वापस 0;
			अवरोध;
		हाल DISABLE:
			अगर ((SLOT_PWRGD(slot_cur->status)) &&
			    (SLOT_PRESENT(slot_cur->status)) &&
			    !(SLOT_LATCH(slot_cur->status)))
				वापस 0;
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण
	err("validate failed....\n");
	वापस -EINVAL;
पूर्ण

/****************************************************************************
 * This routine is क्रम updating the data काष्ठाures in the hotplug core
 * Parameters: काष्ठा slot
 * Returns: 0 or error
 ****************************************************************************/
पूर्णांक ibmphp_update_slot_info(काष्ठा slot *slot_cur)
अणु
	काष्ठा pci_bus *bus = slot_cur->hotplug_slot.pci_slot->bus;
	u8 bus_speed;
	u8 mode;

	bus_speed = slot_cur->bus_on->current_speed;
	mode = slot_cur->bus_on->current_bus_mode;

	चयन (bus_speed) अणु
		हाल BUS_SPEED_33:
			अवरोध;
		हाल BUS_SPEED_66:
			अगर (mode == BUS_MODE_PCIX)
				bus_speed += 0x01;
			अन्यथा अगर (mode == BUS_MODE_PCI)
				;
			अन्यथा
				bus_speed = PCI_SPEED_UNKNOWN;
			अवरोध;
		हाल BUS_SPEED_100:
		हाल BUS_SPEED_133:
			bus_speed += 0x01;
			अवरोध;
		शेष:
			bus_speed = PCI_SPEED_UNKNOWN;
	पूर्ण

	bus->cur_bus_speed = bus_speed;
	// To करो: bus_names

	वापस 0;
पूर्ण


/******************************************************************************
 * This function will वापस the pci_func, given bus and devfunc, or शून्य.  It
 * is called from visit routines
 ******************************************************************************/

अटल काष्ठा pci_func *ibm_slot_find(u8 busno, u8 device, u8 function)
अणु
	काष्ठा pci_func *func_cur;
	काष्ठा slot *slot_cur;
	list_क्रम_each_entry(slot_cur, &ibmphp_slot_head, ibm_slot_list) अणु
		अगर (slot_cur->func) अणु
			func_cur = slot_cur->func;
			जबतक (func_cur) अणु
				अगर ((func_cur->busno == busno) &&
						(func_cur->device == device) &&
						(func_cur->function == function))
					वापस func_cur;
				func_cur = func_cur->next;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*************************************************************
 * This routine मुक्तs up memory used by काष्ठा slot, including
 * the poपूर्णांकers to pci_func, bus, hotplug_slot, controller,
 * and deरेजिस्टरing from the hotplug core
 *************************************************************/
अटल व्योम मुक्त_slots(व्योम)
अणु
	काष्ठा slot *slot_cur, *next;

	debug("%s -- enter\n", __func__);

	list_क्रम_each_entry_safe(slot_cur, next, &ibmphp_slot_head,
				 ibm_slot_list) अणु
		pci_hp_del(&slot_cur->hotplug_slot);
		slot_cur->ctrl = शून्य;
		slot_cur->bus_on = शून्य;

		/*
		 * We करोn't want to actually हटाओ the resources,
		 * since ibmphp_मुक्त_resources() will करो just that.
		 */
		ibmphp_unconfigure_card(&slot_cur, -1);

		pci_hp_destroy(&slot_cur->hotplug_slot);
		kमुक्त(slot_cur);
	पूर्ण
	debug("%s -- exit\n", __func__);
पूर्ण

अटल व्योम ibm_unconfigure_device(काष्ठा pci_func *func)
अणु
	काष्ठा pci_dev *temp;
	u8 j;

	debug("inside %s\n", __func__);
	debug("func->device = %x, func->function = %x\n",
					func->device, func->function);
	debug("func->device << 3 | 0x0  = %x\n", func->device << 3 | 0x0);

	pci_lock_rescan_हटाओ();

	क्रम (j = 0; j < 0x08; j++) अणु
		temp = pci_get_करोमुख्य_bus_and_slot(0, func->busno,
						   (func->device << 3) | j);
		अगर (temp) अणु
			pci_stop_and_हटाओ_bus_device(temp);
			pci_dev_put(temp);
		पूर्ण
	पूर्ण

	pci_dev_put(func->dev);

	pci_unlock_rescan_हटाओ();
पूर्ण

/*
 * The following function is to fix kernel bug regarding
 * getting bus entries, here we manually add those primary
 * bus entries to kernel bus काष्ठाure whenever apply
 */
अटल u8 bus_काष्ठाure_fixup(u8 busno)
अणु
	काष्ठा pci_bus *bus, *b;
	काष्ठा pci_dev *dev;
	u16 l;

	अगर (pci_find_bus(0, busno) || !(ibmphp_find_same_bus_num(busno)))
		वापस 1;

	bus = kदो_स्मृति(माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस 1;

	dev = kदो_स्मृति(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		kमुक्त(bus);
		वापस 1;
	पूर्ण

	bus->number = busno;
	bus->ops = ibmphp_pci_bus->ops;
	dev->bus = bus;
	क्रम (dev->devfn = 0; dev->devfn < 256; dev->devfn += 8) अणु
		अगर (!pci_पढ़ो_config_word(dev, PCI_VENDOR_ID, &l) &&
					(l != 0x0000) && (l != 0xffff)) अणु
			debug("%s - Inside bus_structure_fixup()\n",
							__func__);
			b = pci_scan_bus(busno, ibmphp_pci_bus->ops, शून्य);
			अगर (!b)
				जारी;

			pci_bus_add_devices(b);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(dev);
	kमुक्त(bus);

	वापस 0;
पूर्ण

अटल पूर्णांक ibm_configure_device(काष्ठा pci_func *func)
अणु
	काष्ठा pci_bus *child;
	पूर्णांक num;
	पूर्णांक flag = 0;	/* this is to make sure we करोn't द्विगुन scan the bus,
					क्रम bridged devices primarily */

	pci_lock_rescan_हटाओ();

	अगर (!(bus_काष्ठाure_fixup(func->busno)))
		flag = 1;
	अगर (func->dev == शून्य)
		func->dev = pci_get_करोमुख्य_bus_and_slot(0, func->busno,
				PCI_DEVFN(func->device, func->function));

	अगर (func->dev == शून्य) अणु
		काष्ठा pci_bus *bus = pci_find_bus(0, func->busno);
		अगर (!bus)
			जाओ out;

		num = pci_scan_slot(bus,
				PCI_DEVFN(func->device, func->function));
		अगर (num)
			pci_bus_add_devices(bus);

		func->dev = pci_get_करोमुख्य_bus_and_slot(0, func->busno,
				PCI_DEVFN(func->device, func->function));
		अगर (func->dev == शून्य) अणु
			err("ERROR... : pci_dev still NULL\n");
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (!(flag) && (func->dev->hdr_type == PCI_HEADER_TYPE_BRIDGE)) अणु
		pci_hp_add_bridge(func->dev);
		child = func->dev->subordinate;
		अगर (child)
			pci_bus_add_devices(child);
	पूर्ण

 out:
	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण

/*******************************************************
 * Returns whether the bus is empty or not
 *******************************************************/
अटल पूर्णांक is_bus_empty(काष्ठा slot *slot_cur)
अणु
	पूर्णांक rc;
	काष्ठा slot *पंचांगp_slot;
	u8 i = slot_cur->bus_on->slot_min;

	जबतक (i <= slot_cur->bus_on->slot_max) अणु
		अगर (i == slot_cur->number) अणु
			i++;
			जारी;
		पूर्ण
		पंचांगp_slot = ibmphp_get_slot_from_physical_num(i);
		अगर (!पंचांगp_slot)
			वापस 0;
		rc = slot_update(&पंचांगp_slot);
		अगर (rc)
			वापस 0;
		अगर (SLOT_PRESENT(पंचांगp_slot->status) &&
					SLOT_PWRGD(पंचांगp_slot->status))
			वापस 0;
		i++;
	पूर्ण
	वापस 1;
पूर्ण

/***********************************************************
 * If the HPC permits and the bus currently empty, tries to set the
 * bus speed and mode at the maximum card and bus capability
 * Parameters: slot
 * Returns: bus is set (0) or error code
 ***********************************************************/
अटल पूर्णांक set_bus(काष्ठा slot *slot_cur)
अणु
	पूर्णांक rc;
	u8 speed;
	u8 cmd = 0x0;
	पूर्णांक retval;
	अटल स्थिर काष्ठा pci_device_id ciobx[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS, 0x0101) पूर्ण,
		अणु पूर्ण,
	पूर्ण;

	debug("%s - entry slot # %d\n", __func__, slot_cur->number);
	अगर (SET_BUS_STATUS(slot_cur->ctrl) && is_bus_empty(slot_cur)) अणु
		rc = slot_update(&slot_cur);
		अगर (rc)
			वापस rc;
		speed = SLOT_SPEED(slot_cur->ext_status);
		debug("ext_status = %x, speed = %x\n", slot_cur->ext_status, speed);
		चयन (speed) अणु
		हाल HPC_SLOT_SPEED_33:
			cmd = HPC_BUS_33CONVMODE;
			अवरोध;
		हाल HPC_SLOT_SPEED_66:
			अगर (SLOT_PCIX(slot_cur->ext_status)) अणु
				अगर ((slot_cur->supported_speed >= BUS_SPEED_66) &&
						(slot_cur->supported_bus_mode == BUS_MODE_PCIX))
					cmd = HPC_BUS_66PCIXMODE;
				अन्यथा अगर (!SLOT_BUS_MODE(slot_cur->ext_status))
					/* अगर max slot/bus capability is 66 pci
					and there's no bus mode mismatch, then
					the adapter supports 66 pci */
					cmd = HPC_BUS_66CONVMODE;
				अन्यथा
					cmd = HPC_BUS_33CONVMODE;
			पूर्ण अन्यथा अणु
				अगर (slot_cur->supported_speed >= BUS_SPEED_66)
					cmd = HPC_BUS_66CONVMODE;
				अन्यथा
					cmd = HPC_BUS_33CONVMODE;
			पूर्ण
			अवरोध;
		हाल HPC_SLOT_SPEED_133:
			चयन (slot_cur->supported_speed) अणु
			हाल BUS_SPEED_33:
				cmd = HPC_BUS_33CONVMODE;
				अवरोध;
			हाल BUS_SPEED_66:
				अगर (slot_cur->supported_bus_mode == BUS_MODE_PCIX)
					cmd = HPC_BUS_66PCIXMODE;
				अन्यथा
					cmd = HPC_BUS_66CONVMODE;
				अवरोध;
			हाल BUS_SPEED_100:
				cmd = HPC_BUS_100PCIXMODE;
				अवरोध;
			हाल BUS_SPEED_133:
				/* This is to take care of the bug in CIOBX chip */
				अगर (pci_dev_present(ciobx))
					ibmphp_hpc_ग_लिखोslot(slot_cur,
							HPC_BUS_100PCIXMODE);
				cmd = HPC_BUS_133PCIXMODE;
				अवरोध;
			शेष:
				err("Wrong bus speed\n");
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		शेष:
			err("wrong slot speed\n");
			वापस -ENODEV;
		पूर्ण
		debug("setting bus speed for slot %d, cmd %x\n",
						slot_cur->number, cmd);
		retval = ibmphp_hpc_ग_लिखोslot(slot_cur, cmd);
		अगर (retval) अणु
			err("setting bus speed failed\n");
			वापस retval;
		पूर्ण
		अगर (CTLR_RESULT(slot_cur->ctrl->status)) अणु
			err("command not completed successfully in set_bus\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	/* This is क्रम x440, once Bअक्रमon fixes the firmware,
	will not need this delay */
	msleep(1000);
	debug("%s -Exit\n", __func__);
	वापस 0;
पूर्ण

/* This routine checks the bus limitations that the slot is on from the BIOS.
 * This is used in deciding whether or not to घातer up the slot.
 * (electrical/spec limitations. For example, >1 133 MHz or >2 66 PCI cards on
 * same bus)
 * Parameters: slot
 * Returns: 0 = no limitations, -EINVAL = exceeded limitations on the bus
 */
अटल पूर्णांक check_limitations(काष्ठा slot *slot_cur)
अणु
	u8 i;
	काष्ठा slot *पंचांगp_slot;
	u8 count = 0;
	u8 limitation = 0;

	क्रम (i = slot_cur->bus_on->slot_min; i <= slot_cur->bus_on->slot_max; i++) अणु
		पंचांगp_slot = ibmphp_get_slot_from_physical_num(i);
		अगर (!पंचांगp_slot)
			वापस -ENODEV;
		अगर ((SLOT_PWRGD(पंचांगp_slot->status)) &&
					!(SLOT_CONNECT(पंचांगp_slot->status)))
			count++;
	पूर्ण
	get_cur_bus_info(&slot_cur);
	चयन (slot_cur->bus_on->current_speed) अणु
	हाल BUS_SPEED_33:
		limitation = slot_cur->bus_on->slots_at_33_conv;
		अवरोध;
	हाल BUS_SPEED_66:
		अगर (slot_cur->bus_on->current_bus_mode == BUS_MODE_PCIX)
			limitation = slot_cur->bus_on->slots_at_66_pcix;
		अन्यथा
			limitation = slot_cur->bus_on->slots_at_66_conv;
		अवरोध;
	हाल BUS_SPEED_100:
		limitation = slot_cur->bus_on->slots_at_100_pcix;
		अवरोध;
	हाल BUS_SPEED_133:
		limitation = slot_cur->bus_on->slots_at_133_pcix;
		अवरोध;
	पूर्ण

	अगर ((count + 1) > limitation)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_card_capability(काष्ठा slot *slot_cur)
अणु
	info("capability of the card is ");
	अगर ((slot_cur->ext_status & CARD_INFO) == PCIX133)
		info("   133 MHz PCI-X\n");
	अन्यथा अगर ((slot_cur->ext_status & CARD_INFO) == PCIX66)
		info("    66 MHz PCI-X\n");
	अन्यथा अगर ((slot_cur->ext_status & CARD_INFO) == PCI66)
		info("    66 MHz PCI\n");
	अन्यथा
		info("    33 MHz PCI\n");

पूर्ण

/* This routine will घातer on the slot, configure the device(s) and find the
 * drivers क्रम them.
 * Parameters: hotplug_slot
 * Returns: 0 or failure codes
 */
अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *hs)
अणु
	पूर्णांक rc, i, rcpr;
	काष्ठा slot *slot_cur;
	u8 function;
	काष्ठा pci_func *पंचांगp_func;

	ibmphp_lock_operations();

	debug("ENABLING SLOT........\n");
	slot_cur = to_slot(hs);

	rc = validate(slot_cur, ENABLE);
	अगर (rc) अणु
		err("validate function failed\n");
		जाओ error_noघातer;
	पूर्ण

	attn_LED_blink(slot_cur);

	rc = set_bus(slot_cur);
	अगर (rc) अणु
		err("was not able to set the bus\n");
		जाओ error_noघातer;
	पूर्ण

	/*-----------------debugging------------------------------*/
	get_cur_bus_info(&slot_cur);
	debug("the current bus speed right after set_bus = %x\n",
					slot_cur->bus_on->current_speed);
	/*----------------------------------------------------------*/

	rc = check_limitations(slot_cur);
	अगर (rc) अणु
		err("Adding this card exceeds the limitations of this bus.\n");
		err("(i.e., >1 133MHz cards running on same bus, or >2 66 PCI cards running on same bus.\n");
		err("Try hot-adding into another bus\n");
		rc = -EINVAL;
		जाओ error_noघातer;
	पूर्ण

	rc = घातer_on(slot_cur);

	अगर (rc) अणु
		err("something wrong when powering up... please see below for details\n");
		/* need to turn off beक्रमe on, otherwise, blinking overग_लिखोs */
		attn_off(slot_cur);
		attn_on(slot_cur);
		अगर (slot_update(&slot_cur)) अणु
			attn_off(slot_cur);
			attn_on(slot_cur);
			rc = -ENODEV;
			जाओ निकास;
		पूर्ण
		/* Check to see the error of why it failed */
		अगर ((SLOT_POWER(slot_cur->status)) &&
					!(SLOT_PWRGD(slot_cur->status)))
			err("power fault occurred trying to power up\n");
		अन्यथा अगर (SLOT_BUS_SPEED(slot_cur->status)) अणु
			err("bus speed mismatch occurred.  please check current bus speed and card capability\n");
			prपूर्णांक_card_capability(slot_cur);
		पूर्ण अन्यथा अगर (SLOT_BUS_MODE(slot_cur->ext_status)) अणु
			err("bus mode mismatch occurred.  please check current bus mode and card capability\n");
			prपूर्णांक_card_capability(slot_cur);
		पूर्ण
		ibmphp_update_slot_info(slot_cur);
		जाओ निकास;
	पूर्ण
	debug("after power_on\n");
	/*-----------------------debugging---------------------------*/
	get_cur_bus_info(&slot_cur);
	debug("the current bus speed right after power_on = %x\n",
					slot_cur->bus_on->current_speed);
	/*----------------------------------------------------------*/

	rc = slot_update(&slot_cur);
	अगर (rc)
		जाओ error_घातer;

	rc = -EINVAL;
	अगर (SLOT_POWER(slot_cur->status) && !(SLOT_PWRGD(slot_cur->status))) अणु
		err("power fault occurred trying to power up...\n");
		जाओ error_घातer;
	पूर्ण
	अगर (SLOT_POWER(slot_cur->status) && (SLOT_BUS_SPEED(slot_cur->status))) अणु
		err("bus speed mismatch occurred.  please check current bus speed and card capability\n");
		prपूर्णांक_card_capability(slot_cur);
		जाओ error_घातer;
	पूर्ण
	/* Don't think this हाल will happen after above checks...
	 * but just in हाल, क्रम paranoia sake */
	अगर (!(SLOT_POWER(slot_cur->status))) अणु
		err("power on failed...\n");
		जाओ error_घातer;
	पूर्ण

	slot_cur->func = kzalloc(माप(काष्ठा pci_func), GFP_KERNEL);
	अगर (!slot_cur->func) अणु
		/* करो update_slot_info here? */
		rc = -ENOMEM;
		जाओ error_घातer;
	पूर्ण
	slot_cur->func->busno = slot_cur->bus;
	slot_cur->func->device = slot_cur->device;
	क्रम (i = 0; i < 4; i++)
		slot_cur->func->irq[i] = slot_cur->irq[i];

	debug("b4 configure_card, slot_cur->bus = %x, slot_cur->device = %x\n",
					slot_cur->bus, slot_cur->device);

	अगर (ibmphp_configure_card(slot_cur->func, slot_cur->number)) अणु
		err("configure_card was unsuccessful...\n");
		/* true because करोn't need to actually deallocate resources,
		 * just हटाओ references */
		ibmphp_unconfigure_card(&slot_cur, 1);
		debug("after unconfigure_card\n");
		slot_cur->func = शून्य;
		rc = -ENOMEM;
		जाओ error_घातer;
	पूर्ण

	function = 0x00;
	करो अणु
		पंचांगp_func = ibm_slot_find(slot_cur->bus, slot_cur->func->device,
							function++);
		अगर (पंचांगp_func && !(पंचांगp_func->dev))
			ibm_configure_device(पंचांगp_func);
	पूर्ण जबतक (पंचांगp_func);

	attn_off(slot_cur);
	अगर (slot_update(&slot_cur)) अणु
		rc = -EFAULT;
		जाओ निकास;
	पूर्ण
	ibmphp_prपूर्णांक_test();
	rc = ibmphp_update_slot_info(slot_cur);
निकास:
	ibmphp_unlock_operations();
	वापस rc;

error_noघातer:
	attn_off(slot_cur);	/* need to turn off अगर was blinking b4 */
	attn_on(slot_cur);
error_cont:
	rcpr = slot_update(&slot_cur);
	अगर (rcpr) अणु
		rc = rcpr;
		जाओ निकास;
	पूर्ण
	ibmphp_update_slot_info(slot_cur);
	जाओ निकास;

error_घातer:
	attn_off(slot_cur);	/* need to turn off अगर was blinking b4 */
	attn_on(slot_cur);
	rcpr = घातer_off(slot_cur);
	अगर (rcpr) अणु
		rc = rcpr;
		जाओ निकास;
	पूर्ण
	जाओ error_cont;
पूर्ण

/**************************************************************
* HOT REMOVING ADAPTER CARD                                   *
* INPUT: POINTER TO THE HOTPLUG SLOT STRUCTURE                *
* OUTPUT: SUCCESS 0 ; FAILURE: UNCONFIGURE , VALIDATE         *
*		DISABLE POWER ,                               *
**************************************************************/
अटल पूर्णांक ibmphp_disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	पूर्णांक rc;

	ibmphp_lock_operations();
	rc = ibmphp_करो_disable_slot(slot);
	ibmphp_unlock_operations();
	वापस rc;
पूर्ण

पूर्णांक ibmphp_करो_disable_slot(काष्ठा slot *slot_cur)
अणु
	पूर्णांक rc;
	u8 flag;

	debug("DISABLING SLOT...\n");

	अगर ((slot_cur == शून्य) || (slot_cur->ctrl == शून्य))
		वापस -ENODEV;

	flag = slot_cur->flag;
	slot_cur->flag = 1;

	अगर (flag == 1) अणु
		rc = validate(slot_cur, DISABLE);
			/* checking अगर घातered off alपढ़ोy & valid slot # */
		अगर (rc)
			जाओ error;
	पूर्ण
	attn_LED_blink(slot_cur);

	अगर (slot_cur->func == शून्य) अणु
		/* We need this क्रम functions that were there on bootup */
		slot_cur->func = kzalloc(माप(काष्ठा pci_func), GFP_KERNEL);
		अगर (!slot_cur->func) अणु
			rc = -ENOMEM;
			जाओ error;
		पूर्ण
		slot_cur->func->busno = slot_cur->bus;
		slot_cur->func->device = slot_cur->device;
	पूर्ण

	ibm_unconfigure_device(slot_cur->func);

	/*
	 * If we got here from latch suddenly खोलोing on operating card or
	 * a घातer fault, there's no घातer to the card, so cannot
	 * पढ़ो from it to determine what resources it occupied.  This operation
	 * is क्रमbidden anyhow.  The best we can करो is हटाओ it from kernel
	 * lists at least */

	अगर (!flag) अणु
		attn_off(slot_cur);
		वापस 0;
	पूर्ण

	rc = ibmphp_unconfigure_card(&slot_cur, 0);
	slot_cur->func = शून्य;
	debug("in disable_slot. after unconfigure_card\n");
	अगर (rc) अणु
		err("could not unconfigure card.\n");
		जाओ error;
	पूर्ण

	rc = ibmphp_hpc_ग_लिखोslot(slot_cur, HPC_SLOT_OFF);
	अगर (rc)
		जाओ error;

	attn_off(slot_cur);
	rc = slot_update(&slot_cur);
	अगर (rc)
		जाओ निकास;

	rc = ibmphp_update_slot_info(slot_cur);
	ibmphp_prपूर्णांक_test();
निकास:
	वापस rc;

error:
	/*  Need to turn off अगर was blinking b4 */
	attn_off(slot_cur);
	attn_on(slot_cur);
	अगर (slot_update(&slot_cur)) अणु
		rc = -EFAULT;
		जाओ निकास;
	पूर्ण
	अगर (flag)
		ibmphp_update_slot_info(slot_cur);
	जाओ निकास;
पूर्ण

स्थिर काष्ठा hotplug_slot_ops ibmphp_hotplug_slot_ops = अणु
	.set_attention_status =		set_attention_status,
	.enable_slot =			enable_slot,
	.disable_slot =			ibmphp_disable_slot,
	.hardware_test =		शून्य,
	.get_घातer_status =		get_घातer_status,
	.get_attention_status =		get_attention_status,
	.get_latch_status =		get_latch_status,
	.get_adapter_status =		get_adapter_present,
/*	.get_max_adapter_speed =	get_max_adapter_speed,
	.get_bus_name_status =		get_bus_name,
*/
पूर्ण;

अटल व्योम ibmphp_unload(व्योम)
अणु
	मुक्त_slots();
	debug("after slots\n");
	ibmphp_मुक्त_resources();
	debug("after resources\n");
	ibmphp_मुक्त_bus_info_queue();
	debug("after bus info\n");
	ibmphp_मुक्त_ebda_hpc_queue();
	debug("after ebda hpc\n");
	ibmphp_मुक्त_ebda_pci_rsrc_queue();
	debug("after ebda pci rsrc\n");
	kमुक्त(ibmphp_pci_bus);
पूर्ण

अटल पूर्णांक __init ibmphp_init(व्योम)
अणु
	काष्ठा pci_bus *bus;
	पूर्णांक i = 0;
	पूर्णांक rc = 0;

	init_flag = 1;

	info(DRIVER_DESC " version: " DRIVER_VERSION "\n");

	ibmphp_pci_bus = kदो_स्मृति(माप(*ibmphp_pci_bus), GFP_KERNEL);
	अगर (!ibmphp_pci_bus) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	bus = pci_find_bus(0, 0);
	अगर (!bus) अणु
		err("Can't find the root pci bus, can not continue\n");
		rc = -ENODEV;
		जाओ error;
	पूर्ण
	स_नकल(ibmphp_pci_bus, bus, माप(*ibmphp_pci_bus));

	ibmphp_debug = debug;

	क्रम (i = 0; i < 16; i++)
		irqs[i] = 0;

	rc = ibmphp_access_ebda();
	अगर (rc)
		जाओ error;
	debug("after ibmphp_access_ebda()\n");

	rc = ibmphp_rsrc_init();
	अगर (rc)
		जाओ error;
	debug("AFTER Resource & EBDA INITIALIZATIONS\n");

	max_slots = get_max_slots();

	rc = ibmphp_रेजिस्टर_pci();
	अगर (rc)
		जाओ error;

	अगर (init_ops()) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	ibmphp_prपूर्णांक_test();
	rc = ibmphp_hpc_start_poll_thपढ़ो();
	अगर (rc)
		जाओ error;

निकास:
	वापस rc;

error:
	ibmphp_unload();
	जाओ निकास;
पूर्ण

अटल व्योम __निकास ibmphp_निकास(व्योम)
अणु
	ibmphp_hpc_stop_poll_thपढ़ो();
	debug("after polling\n");
	ibmphp_unload();
	debug("done\n");
पूर्ण

module_init(ibmphp_init);
module_निकास(ibmphp_निकास);
