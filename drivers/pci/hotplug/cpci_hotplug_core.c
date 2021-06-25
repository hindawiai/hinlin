<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CompactPCI Hot Plug Driver
 *
 * Copyright (C) 2002,2005 SOMA Networks, Inc.
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "cpci_hotplug.h"

#घोषणा DRIVER_AUTHOR	"Scott Murray <scottm@somanetworks.com>"
#घोषणा DRIVER_DESC	"CompactPCI Hot Plug Core"

#घोषणा MY_NAME	"cpci_hotplug"

#घोषणा dbg(क्रमmat, arg...)					\
	करो अणु							\
		अगर (cpci_debug)					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n",	\
				MY_NAME, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat "\n", MY_NAME, ## arg)

/* local variables */
अटल DECLARE_RWSEM(list_rwsem);
अटल LIST_HEAD(slot_list);
अटल पूर्णांक slots;
अटल atomic_t extracting;
पूर्णांक cpci_debug;
अटल काष्ठा cpci_hp_controller *controller;
अटल काष्ठा task_काष्ठा *cpci_thपढ़ो;
अटल पूर्णांक thपढ़ो_finished;

अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *slot, u8 value);
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *slot, u8 *value);

अटल स्थिर काष्ठा hotplug_slot_ops cpci_hotplug_slot_ops = अणु
	.enable_slot = enable_slot,
	.disable_slot = disable_slot,
	.set_attention_status = set_attention_status,
	.get_घातer_status = get_घातer_status,
	.get_attention_status = get_attention_status,
	.get_adapter_status = get_adapter_status,
	.get_latch_status = get_latch_status,
पूर्ण;

अटल पूर्णांक
enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	पूर्णांक retval = 0;

	dbg("%s - physical_slot = %s", __func__, slot_name(slot));

	अगर (controller->ops->set_घातer)
		retval = controller->ops->set_घातer(slot, 1);
	वापस retval;
पूर्ण

अटल पूर्णांक
disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);
	पूर्णांक retval = 0;

	dbg("%s - physical_slot = %s", __func__, slot_name(slot));

	करोwn_ग_लिखो(&list_rwsem);

	/* Unconfigure device */
	dbg("%s - unconfiguring slot %s", __func__, slot_name(slot));
	retval = cpci_unconfigure_slot(slot);
	अगर (retval) अणु
		err("%s - could not unconfigure slot %s",
		    __func__, slot_name(slot));
		जाओ disable_error;
	पूर्ण
	dbg("%s - finished unconfiguring slot %s", __func__, slot_name(slot));

	/* Clear EXT (by setting it) */
	अगर (cpci_clear_ext(slot)) अणु
		err("%s - could not clear EXT for slot %s",
		    __func__, slot_name(slot));
		retval = -ENODEV;
		जाओ disable_error;
	पूर्ण
	cpci_led_on(slot);

	अगर (controller->ops->set_घातer) अणु
		retval = controller->ops->set_घातer(slot, 0);
		अगर (retval)
			जाओ disable_error;
	पूर्ण

	slot->adapter_status = 0;

	अगर (slot->extracting) अणु
		slot->extracting = 0;
		atomic_dec(&extracting);
	पूर्ण
disable_error:
	up_ग_लिखो(&list_rwsem);
	वापस retval;
पूर्ण

अटल u8
cpci_get_घातer_status(काष्ठा slot *slot)
अणु
	u8 घातer = 1;

	अगर (controller->ops->get_घातer)
		घातer = controller->ops->get_घातer(slot);
	वापस घातer;
पूर्ण

अटल पूर्णांक
get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	*value = cpci_get_घातer_status(slot);
	वापस 0;
पूर्ण

अटल पूर्णांक
get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	*value = cpci_get_attention_status(slot);
	वापस 0;
पूर्ण

अटल पूर्णांक
set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 status)
अणु
	वापस cpci_set_attention_status(to_slot(hotplug_slot), status);
पूर्ण

अटल पूर्णांक
get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	*value = slot->adapter_status;
	वापस 0;
पूर्ण

अटल पूर्णांक
get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	*value = slot->latch_status;
	वापस 0;
पूर्ण

अटल व्योम release_slot(काष्ठा slot *slot)
अणु
	pci_dev_put(slot->dev);
	kमुक्त(slot);
पूर्ण

#घोषणा SLOT_NAME_SIZE	6

पूर्णांक
cpci_hp_रेजिस्टर_bus(काष्ठा pci_bus *bus, u8 first, u8 last)
अणु
	काष्ठा slot *slot;
	अक्षर name[SLOT_NAME_SIZE];
	पूर्णांक status;
	पूर्णांक i;

	अगर (!(controller && bus))
		वापस -ENODEV;

	/*
	 * Create a काष्ठाure क्रम each slot, and रेजिस्टर that slot
	 * with the pci_hotplug subप्रणाली.
	 */
	क्रम (i = first; i <= last; ++i) अणु
		slot = kzalloc(माप(काष्ठा slot), GFP_KERNEL);
		अगर (!slot) अणु
			status = -ENOMEM;
			जाओ error;
		पूर्ण

		slot->bus = bus;
		slot->number = i;
		slot->devfn = PCI_DEVFN(i, 0);

		snम_लिखो(name, SLOT_NAME_SIZE, "%02x:%02x", bus->number, i);

		slot->hotplug_slot.ops = &cpci_hotplug_slot_ops;

		dbg("registering slot %s", name);
		status = pci_hp_रेजिस्टर(&slot->hotplug_slot, bus, i, name);
		अगर (status) अणु
			err("pci_hp_register failed with error %d", status);
			जाओ error_slot;
		पूर्ण
		dbg("slot registered with name: %s", slot_name(slot));

		/* Add slot to our पूर्णांकernal list */
		करोwn_ग_लिखो(&list_rwsem);
		list_add(&slot->slot_list, &slot_list);
		slots++;
		up_ग_लिखो(&list_rwsem);
	पूर्ण
	वापस 0;
error_slot:
	kमुक्त(slot);
error:
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_रेजिस्टर_bus);

पूर्णांक
cpci_hp_unरेजिस्टर_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा slot *slot;
	काष्ठा slot *पंचांगp;
	पूर्णांक status = 0;

	करोwn_ग_लिखो(&list_rwsem);
	अगर (!slots) अणु
		up_ग_लिखो(&list_rwsem);
		वापस -1;
	पूर्ण
	list_क्रम_each_entry_safe(slot, पंचांगp, &slot_list, slot_list) अणु
		अगर (slot->bus == bus) अणु
			list_del(&slot->slot_list);
			slots--;

			dbg("deregistering slot %s", slot_name(slot));
			pci_hp_deरेजिस्टर(&slot->hotplug_slot);
			release_slot(slot);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&list_rwsem);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_unरेजिस्टर_bus);

/* This is the पूर्णांकerrupt mode पूर्णांकerrupt handler */
अटल irqवापस_t
cpci_hp_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	dbg("entered cpci_hp_intr");

	/* Check to see अगर it was our पूर्णांकerrupt */
	अगर ((controller->irq_flags & IRQF_SHARED) &&
	    !controller->ops->check_irq(controller->dev_id)) अणु
		dbg("exited cpci_hp_intr, not our interrupt");
		वापस IRQ_NONE;
	पूर्ण

	/* Disable ENUM पूर्णांकerrupt */
	controller->ops->disable_irq();

	/* Trigger processing by the event thपढ़ो */
	wake_up_process(cpci_thपढ़ो);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * According to PICMG 2.1 R2.0, section 6.3.2, upon
 * initialization, the प्रणाली driver shall clear the
 * INS bits of the cold-inserted devices.
 */
अटल पूर्णांक
init_slots(पूर्णांक clear_ins)
अणु
	काष्ठा slot *slot;
	काष्ठा pci_dev *dev;

	dbg("%s - enter", __func__);
	करोwn_पढ़ो(&list_rwsem);
	अगर (!slots) अणु
		up_पढ़ो(&list_rwsem);
		वापस -1;
	पूर्ण
	list_क्रम_each_entry(slot, &slot_list, slot_list) अणु
		dbg("%s - looking at slot %s", __func__, slot_name(slot));
		अगर (clear_ins && cpci_check_and_clear_ins(slot))
			dbg("%s - cleared INS for slot %s",
			    __func__, slot_name(slot));
		dev = pci_get_slot(slot->bus, PCI_DEVFN(slot->number, 0));
		अगर (dev) अणु
			slot->adapter_status = 1;
			slot->latch_status = 1;
			slot->dev = dev;
		पूर्ण
	पूर्ण
	up_पढ़ो(&list_rwsem);
	dbg("%s - exit", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
check_slots(व्योम)
अणु
	काष्ठा slot *slot;
	पूर्णांक extracted;
	पूर्णांक inserted;
	u16 hs_csr;

	करोwn_पढ़ो(&list_rwsem);
	अगर (!slots) अणु
		up_पढ़ो(&list_rwsem);
		err("no slots registered, shutting down");
		वापस -1;
	पूर्ण
	extracted = inserted = 0;
	list_क्रम_each_entry(slot, &slot_list, slot_list) अणु
		dbg("%s - looking at slot %s", __func__, slot_name(slot));
		अगर (cpci_check_and_clear_ins(slot)) अणु
			/*
			 * Some broken hardware (e.g. PLX 9054AB) निश्चितs
			 * ENUM# twice...
			 */
			अगर (slot->dev) अणु
				warn("slot %s already inserted",
				     slot_name(slot));
				inserted++;
				जारी;
			पूर्ण

			/* Process insertion */
			dbg("%s - slot %s inserted", __func__, slot_name(slot));

			/* GSM, debug */
			hs_csr = cpci_get_hs_csr(slot);
			dbg("%s - slot %s HS_CSR (1) = %04x",
			    __func__, slot_name(slot), hs_csr);

			/* Configure device */
			dbg("%s - configuring slot %s",
			    __func__, slot_name(slot));
			अगर (cpci_configure_slot(slot)) अणु
				err("%s - could not configure slot %s",
				    __func__, slot_name(slot));
				जारी;
			पूर्ण
			dbg("%s - finished configuring slot %s",
			    __func__, slot_name(slot));

			/* GSM, debug */
			hs_csr = cpci_get_hs_csr(slot);
			dbg("%s - slot %s HS_CSR (2) = %04x",
			    __func__, slot_name(slot), hs_csr);

			slot->latch_status = 1;
			slot->adapter_status = 1;

			cpci_led_off(slot);

			/* GSM, debug */
			hs_csr = cpci_get_hs_csr(slot);
			dbg("%s - slot %s HS_CSR (3) = %04x",
			    __func__, slot_name(slot), hs_csr);

			inserted++;
		पूर्ण अन्यथा अगर (cpci_check_ext(slot)) अणु
			/* Process extraction request */
			dbg("%s - slot %s extracted",
			    __func__, slot_name(slot));

			/* GSM, debug */
			hs_csr = cpci_get_hs_csr(slot);
			dbg("%s - slot %s HS_CSR = %04x",
			    __func__, slot_name(slot), hs_csr);

			अगर (!slot->extracting) अणु
				slot->latch_status = 0;
				slot->extracting = 1;
				atomic_inc(&extracting);
			पूर्ण
			extracted++;
		पूर्ण अन्यथा अगर (slot->extracting) अणु
			hs_csr = cpci_get_hs_csr(slot);
			अगर (hs_csr == 0xffff) अणु
				/*
				 * Hmmm, we're likely hosed at this poपूर्णांक, should we
				 * bother trying to tell the driver or not?
				 */
				err("card in slot %s was improperly removed",
				    slot_name(slot));
				slot->adapter_status = 0;
				slot->extracting = 0;
				atomic_dec(&extracting);
			पूर्ण
		पूर्ण
	पूर्ण
	up_पढ़ो(&list_rwsem);
	dbg("inserted=%d, extracted=%d, extracting=%d",
	    inserted, extracted, atomic_पढ़ो(&extracting));
	अगर (inserted || extracted)
		वापस extracted;
	अन्यथा अगर (!atomic_पढ़ो(&extracting)) अणु
		err("cannot find ENUM# source, shutting down");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* This is the पूर्णांकerrupt mode worker thपढ़ो body */
अटल पूर्णांक
event_thपढ़ो(व्योम *data)
अणु
	पूर्णांक rc;

	dbg("%s - event thread started", __func__);
	जबतक (1) अणु
		dbg("event thread sleeping");
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		करो अणु
			rc = check_slots();
			अगर (rc > 0) अणु
				/* Give userspace a chance to handle extraction */
				msleep(500);
			पूर्ण अन्यथा अगर (rc < 0) अणु
				dbg("%s - error checking slots", __func__);
				thपढ़ो_finished = 1;
				जाओ out;
			पूर्ण
		पूर्ण जबतक (atomic_पढ़ो(&extracting) && !kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Re-enable ENUM# पूर्णांकerrupt */
		dbg("%s - re-enabling irq", __func__);
		controller->ops->enable_irq();
	पूर्ण
 out:
	वापस 0;
पूर्ण

/* This is the polling mode worker thपढ़ो body */
अटल पूर्णांक
poll_thपढ़ो(व्योम *data)
अणु
	पूर्णांक rc;

	जबतक (1) अणु
		अगर (kthपढ़ो_should_stop() || संकेत_pending(current))
			अवरोध;
		अगर (controller->ops->query_क्रमागत()) अणु
			करो अणु
				rc = check_slots();
				अगर (rc > 0) अणु
					/* Give userspace a chance to handle extraction */
					msleep(500);
				पूर्ण अन्यथा अगर (rc < 0) अणु
					dbg("%s - error checking slots", __func__);
					thपढ़ो_finished = 1;
					जाओ out;
				पूर्ण
			पूर्ण जबतक (atomic_पढ़ो(&extracting) && !kthपढ़ो_should_stop());
		पूर्ण
		msleep(100);
	पूर्ण
 out:
	वापस 0;
पूर्ण

अटल पूर्णांक
cpci_start_thपढ़ो(व्योम)
अणु
	अगर (controller->irq)
		cpci_thपढ़ो = kthपढ़ो_run(event_thपढ़ो, शून्य, "cpci_hp_eventd");
	अन्यथा
		cpci_thपढ़ो = kthपढ़ो_run(poll_thपढ़ो, शून्य, "cpci_hp_polld");
	अगर (IS_ERR(cpci_thपढ़ो)) अणु
		err("Can't start up our thread");
		वापस PTR_ERR(cpci_thपढ़ो);
	पूर्ण
	thपढ़ो_finished = 0;
	वापस 0;
पूर्ण

अटल व्योम
cpci_stop_thपढ़ो(व्योम)
अणु
	kthपढ़ो_stop(cpci_thपढ़ो);
	thपढ़ो_finished = 1;
पूर्ण

पूर्णांक
cpci_hp_रेजिस्टर_controller(काष्ठा cpci_hp_controller *new_controller)
अणु
	पूर्णांक status = 0;

	अगर (controller)
		वापस -1;
	अगर (!(new_controller && new_controller->ops))
		वापस -EINVAL;
	अगर (new_controller->irq) अणु
		अगर (!(new_controller->ops->enable_irq &&
		     new_controller->ops->disable_irq))
			status = -EINVAL;
		अगर (request_irq(new_controller->irq,
			       cpci_hp_पूर्णांकr,
			       new_controller->irq_flags,
			       MY_NAME,
			       new_controller->dev_id)) अणु
			err("Can't get irq %d for the hotplug cPCI controller",
			    new_controller->irq);
			status = -ENODEV;
		पूर्ण
		dbg("%s - acquired controller irq %d",
		    __func__, new_controller->irq);
	पूर्ण
	अगर (!status)
		controller = new_controller;
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_रेजिस्टर_controller);

अटल व्योम
cleanup_slots(व्योम)
अणु
	काष्ठा slot *slot;
	काष्ठा slot *पंचांगp;

	/*
	 * Unरेजिस्टर all of our slots with the pci_hotplug subप्रणाली,
	 * and मुक्त up all memory that we had allocated.
	 */
	करोwn_ग_लिखो(&list_rwsem);
	अगर (!slots)
		जाओ cleanup_null;
	list_क्रम_each_entry_safe(slot, पंचांगp, &slot_list, slot_list) अणु
		list_del(&slot->slot_list);
		pci_hp_deरेजिस्टर(&slot->hotplug_slot);
		release_slot(slot);
	पूर्ण
cleanup_null:
	up_ग_लिखो(&list_rwsem);
पूर्ण

पूर्णांक
cpci_hp_unरेजिस्टर_controller(काष्ठा cpci_hp_controller *old_controller)
अणु
	पूर्णांक status = 0;

	अगर (controller) अणु
		अगर (!thपढ़ो_finished)
			cpci_stop_thपढ़ो();
		अगर (controller->irq)
			मुक्त_irq(controller->irq, controller->dev_id);
		controller = शून्य;
		cleanup_slots();
	पूर्ण अन्यथा
		status = -ENODEV;
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_unरेजिस्टर_controller);

पूर्णांक
cpci_hp_start(व्योम)
अणु
	अटल पूर्णांक first = 1;
	पूर्णांक status;

	dbg("%s - enter", __func__);
	अगर (!controller)
		वापस -ENODEV;

	करोwn_पढ़ो(&list_rwsem);
	अगर (list_empty(&slot_list)) अणु
		up_पढ़ो(&list_rwsem);
		वापस -ENODEV;
	पूर्ण
	up_पढ़ो(&list_rwsem);

	status = init_slots(first);
	अगर (first)
		first = 0;
	अगर (status)
		वापस status;

	status = cpci_start_thपढ़ो();
	अगर (status)
		वापस status;
	dbg("%s - thread started", __func__);

	अगर (controller->irq) अणु
		/* Start क्रमागत पूर्णांकerrupt processing */
		dbg("%s - enabling irq", __func__);
		controller->ops->enable_irq();
	पूर्ण
	dbg("%s - exit", __func__);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_start);

पूर्णांक
cpci_hp_stop(व्योम)
अणु
	अगर (!controller)
		वापस -ENODEV;
	अगर (controller->irq) अणु
		/* Stop क्रमागत पूर्णांकerrupt processing */
		dbg("%s - disabling irq", __func__);
		controller->ops->disable_irq();
	पूर्ण
	cpci_stop_thपढ़ो();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpci_hp_stop);

पूर्णांक __init
cpci_hotplug_init(पूर्णांक debug)
अणु
	cpci_debug = debug;
	वापस 0;
पूर्ण
