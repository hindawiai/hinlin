<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pci_link.c - ACPI PCI Interrupt Link Device Driver ($Revision: 34 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2002       Dominik Broकरोwski <devel@broकरो.de>
 *
 * TBD:
 *	1. Support more than one IRQ resource entry per link device (index).
 *	2. Implement start/stop mechanism and use ACPI Bus Driver facilities
 *	   क्रम IRQ management (e.g. start()->_SRS).
 */

#घोषणा pr_fmt(fmt) "ACPI: PCI: " fmt

#समावेश <linux/syscore_ops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/irq.h>

#समावेश "internal.h"

#घोषणा ACPI_PCI_LINK_CLASS		"pci_irq_routing"
#घोषणा ACPI_PCI_LINK_DEVICE_NAME	"PCI Interrupt Link"
#घोषणा ACPI_PCI_LINK_MAX_POSSIBLE	16

अटल पूर्णांक acpi_pci_link_add(काष्ठा acpi_device *device,
			     स्थिर काष्ठा acpi_device_id *not_used);
अटल व्योम acpi_pci_link_हटाओ(काष्ठा acpi_device *device);

अटल स्थिर काष्ठा acpi_device_id link_device_ids[] = अणु
	अणु"PNP0C0F", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_scan_handler pci_link_handler = अणु
	.ids = link_device_ids,
	.attach = acpi_pci_link_add,
	.detach = acpi_pci_link_हटाओ,
पूर्ण;

/*
 * If a link is initialized, we never change its active and initialized
 * later even the link is disable. Instead, we just repick the active irq
 */
काष्ठा acpi_pci_link_irq अणु
	u32 active;		/* Current IRQ */
	u8 triggering;		/* All IRQs */
	u8 polarity;		/* All IRQs */
	u8 resource_type;
	u8 possible_count;
	u32 possible[ACPI_PCI_LINK_MAX_POSSIBLE];
	u8 initialized:1;
	u8 reserved:7;
पूर्ण;

काष्ठा acpi_pci_link अणु
	काष्ठा list_head		list;
	काष्ठा acpi_device		*device;
	काष्ठा acpi_pci_link_irq	irq;
	पूर्णांक				refcnt;
पूर्ण;

अटल LIST_HEAD(acpi_link_list);
अटल DEFINE_MUTEX(acpi_link_lock);
अटल पूर्णांक sci_irq = -1, sci_penalty;

/* --------------------------------------------------------------------------
                            PCI Link Device Management
   -------------------------------------------------------------------------- */

/*
 * set context (link) possible list from resource list
 */
अटल acpi_status acpi_pci_link_check_possible(काष्ठा acpi_resource *resource,
						व्योम *context)
अणु
	काष्ठा acpi_pci_link *link = context;
	acpi_handle handle = link->device->handle;
	u32 i;

	चयन (resource->type) अणु
	हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
	हाल ACPI_RESOURCE_TYPE_END_TAG:
		वापस AE_OK;
	हाल ACPI_RESOURCE_TYPE_IRQ:
		अणु
			काष्ठा acpi_resource_irq *p = &resource->data.irq;
			अगर (!p || !p->पूर्णांकerrupt_count) अणु
				acpi_handle_debug(handle,
						  "Blank _PRS IRQ resource\n");
				वापस AE_OK;
			पूर्ण
			क्रम (i = 0;
			     (i < p->पूर्णांकerrupt_count
			      && i < ACPI_PCI_LINK_MAX_POSSIBLE); i++) अणु
				अगर (!p->पूर्णांकerrupts[i]) अणु
					acpi_handle_debug(handle,
							  "Invalid _PRS IRQ %d\n",
							  p->पूर्णांकerrupts[i]);
					जारी;
				पूर्ण
				link->irq.possible[i] = p->पूर्णांकerrupts[i];
				link->irq.possible_count++;
			पूर्ण
			link->irq.triggering = p->triggering;
			link->irq.polarity = p->polarity;
			link->irq.resource_type = ACPI_RESOURCE_TYPE_IRQ;
			अवरोध;
		पूर्ण
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		अणु
			काष्ठा acpi_resource_extended_irq *p =
			    &resource->data.extended_irq;
			अगर (!p || !p->पूर्णांकerrupt_count) अणु
				acpi_handle_debug(handle,
						  "Blank _PRS EXT IRQ resource\n");
				वापस AE_OK;
			पूर्ण
			क्रम (i = 0;
			     (i < p->पूर्णांकerrupt_count
			      && i < ACPI_PCI_LINK_MAX_POSSIBLE); i++) अणु
				अगर (!p->पूर्णांकerrupts[i]) अणु
					acpi_handle_debug(handle,
							  "Invalid _PRS IRQ %d\n",
							  p->पूर्णांकerrupts[i]);
					जारी;
				पूर्ण
				link->irq.possible[i] = p->पूर्णांकerrupts[i];
				link->irq.possible_count++;
			पूर्ण
			link->irq.triggering = p->triggering;
			link->irq.polarity = p->polarity;
			link->irq.resource_type = ACPI_RESOURCE_TYPE_EXTENDED_IRQ;
			अवरोध;
		पूर्ण
	शेष:
		acpi_handle_debug(handle, "_PRS resource type 0x%x is not IRQ\n",
				  resource->type);
		वापस AE_OK;
	पूर्ण

	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल पूर्णांक acpi_pci_link_get_possible(काष्ठा acpi_pci_link *link)
अणु
	acpi_handle handle = link->device->handle;
	acpi_status status;

	status = acpi_walk_resources(handle, METHOD_NAME__PRS,
				     acpi_pci_link_check_possible, link);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "_PRS not present or invalid");
		वापस 0;
	पूर्ण

	acpi_handle_debug(handle, "Found %d possible IRQs\n",
			  link->irq.possible_count);

	वापस 0;
पूर्ण

अटल acpi_status acpi_pci_link_check_current(काष्ठा acpi_resource *resource,
					       व्योम *context)
अणु
	पूर्णांक *irq = context;

	चयन (resource->type) अणु
	हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
	हाल ACPI_RESOURCE_TYPE_END_TAG:
		वापस AE_OK;
	हाल ACPI_RESOURCE_TYPE_IRQ:
		अणु
			काष्ठा acpi_resource_irq *p = &resource->data.irq;
			अगर (!p || !p->पूर्णांकerrupt_count) अणु
				/*
				 * IRQ descriptors may have no IRQ# bits set,
				 * particularly those those w/ _STA disabled
				 */
				pr_debug("Blank _CRS IRQ resource\n");
				वापस AE_OK;
			पूर्ण
			*irq = p->पूर्णांकerrupts[0];
			अवरोध;
		पूर्ण
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		अणु
			काष्ठा acpi_resource_extended_irq *p =
			    &resource->data.extended_irq;
			अगर (!p || !p->पूर्णांकerrupt_count) अणु
				/*
				 * extended IRQ descriptors must
				 * वापस at least 1 IRQ
				 */
				pr_debug("Blank _CRS EXT IRQ resource\n");
				वापस AE_OK;
			पूर्ण
			*irq = p->पूर्णांकerrupts[0];
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		pr_debug("_CRS resource type 0x%x is not IRQ\n",
			 resource->type);
		वापस AE_OK;
	पूर्ण

	वापस AE_CTRL_TERMINATE;
पूर्ण

/*
 * Run _CRS and set link->irq.active
 *
 * वापस value:
 * 0 - success
 * !0 - failure
 */
अटल पूर्णांक acpi_pci_link_get_current(काष्ठा acpi_pci_link *link)
अणु
	acpi_handle handle = link->device->handle;
	acpi_status status;
	पूर्णांक result = 0;
	पूर्णांक irq = 0;

	link->irq.active = 0;

	/* in practice, status disabled is meaningless, ignore it */
	अगर (acpi_strict) अणु
		/* Query _STA, set link->device->status */
		result = acpi_bus_get_status(link->device);
		अगर (result) अणु
			acpi_handle_err(handle, "Unable to read status\n");
			जाओ end;
		पूर्ण

		अगर (!link->device->status.enabled) अणु
			acpi_handle_debug(handle, "Link disabled\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Query and parse _CRS to get the current IRQ assignment.
	 */

	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     acpi_pci_link_check_current, &irq);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(handle, "_CRS", status);
		result = -ENODEV;
		जाओ end;
	पूर्ण

	अगर (acpi_strict && !irq) अणु
		acpi_handle_err(handle, "_CRS returned 0\n");
		result = -ENODEV;
	पूर्ण

	link->irq.active = irq;

	acpi_handle_debug(handle, "Link at IRQ %d \n", link->irq.active);

      end:
	वापस result;
पूर्ण

अटल पूर्णांक acpi_pci_link_set(काष्ठा acpi_pci_link *link, पूर्णांक irq)
अणु
	काष्ठा अणु
		काष्ठा acpi_resource res;
		काष्ठा acpi_resource end;
	पूर्ण *resource;
	काष्ठा acpi_buffer buffer = अणु 0, शून्य पूर्ण;
	acpi_handle handle = link->device->handle;
	acpi_status status;
	पूर्णांक result;

	अगर (!irq)
		वापस -EINVAL;

	resource = kzalloc(माप(*resource) + 1, irqs_disabled() ? GFP_ATOMIC: GFP_KERNEL);
	अगर (!resource)
		वापस -ENOMEM;

	buffer.length = माप(*resource) + 1;
	buffer.poपूर्णांकer = resource;

	चयन (link->irq.resource_type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
		resource->res.type = ACPI_RESOURCE_TYPE_IRQ;
		resource->res.length = माप(काष्ठा acpi_resource);
		resource->res.data.irq.triggering = link->irq.triggering;
		resource->res.data.irq.polarity =
		    link->irq.polarity;
		अगर (link->irq.triggering == ACPI_EDGE_SENSITIVE)
			resource->res.data.irq.shareable =
			    ACPI_EXCLUSIVE;
		अन्यथा
			resource->res.data.irq.shareable = ACPI_SHARED;
		resource->res.data.irq.पूर्णांकerrupt_count = 1;
		resource->res.data.irq.पूर्णांकerrupts[0] = irq;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		resource->res.type = ACPI_RESOURCE_TYPE_EXTENDED_IRQ;
		resource->res.length = माप(काष्ठा acpi_resource);
		resource->res.data.extended_irq.producer_consumer =
		    ACPI_CONSUMER;
		resource->res.data.extended_irq.triggering =
		    link->irq.triggering;
		resource->res.data.extended_irq.polarity =
		    link->irq.polarity;
		अगर (link->irq.triggering == ACPI_EDGE_SENSITIVE)
			resource->res.data.extended_irq.shareable =
			    ACPI_EXCLUSIVE;
		अन्यथा
			resource->res.data.extended_irq.shareable = ACPI_SHARED;
		resource->res.data.extended_irq.पूर्णांकerrupt_count = 1;
		resource->res.data.extended_irq.पूर्णांकerrupts[0] = irq;
		/* ignore resource_source, it's optional */
		अवरोध;
	शेष:
		acpi_handle_err(handle, "Invalid resource type %d\n",
				link->irq.resource_type);
		result = -EINVAL;
		जाओ end;

	पूर्ण
	resource->end.type = ACPI_RESOURCE_TYPE_END_TAG;
	resource->end.length = माप(काष्ठा acpi_resource);

	/* Attempt to set the resource */
	status = acpi_set_current_resources(link->device->handle, &buffer);

	/* check क्रम total failure */
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(handle, "_SRS", status);
		result = -ENODEV;
		जाओ end;
	पूर्ण

	/* Query _STA, set device->status */
	result = acpi_bus_get_status(link->device);
	अगर (result) अणु
		acpi_handle_err(handle, "Unable to read status\n");
		जाओ end;
	पूर्ण
	अगर (!link->device->status.enabled)
		acpi_handle_warn(handle, "Disabled and referenced, BIOS bug\n");

	/* Query _CRS, set link->irq.active */
	result = acpi_pci_link_get_current(link);
	अगर (result) अणु
		जाओ end;
	पूर्ण

	/*
	 * Is current setting not what we set?
	 * set link->irq.active
	 */
	अगर (link->irq.active != irq) अणु
		/*
		 * policy: when _CRS करोesn't वापस what we just _SRS
		 * assume _SRS worked and override _CRS value.
		 */
		acpi_handle_warn(handle, "BIOS reported IRQ %d, using IRQ %d\n",
				 link->irq.active, irq);
		link->irq.active = irq;
	पूर्ण

	acpi_handle_debug(handle, "Set IRQ %d\n", link->irq.active);

      end:
	kमुक्त(resource);
	वापस result;
पूर्ण

/* --------------------------------------------------------------------------
                            PCI Link IRQ Management
   -------------------------------------------------------------------------- */

/*
 * "acpi_irq_balance" (शेष in APIC mode) enables ACPI to use PIC Interrupt
 * Link Devices to move the PIRQs around to minimize sharing.
 *
 * "acpi_irq_nobalance" (शेष in PIC mode) tells ACPI not to move any PIC IRQs
 * that the BIOS has alपढ़ोy set to active.  This is necessary because
 * ACPI has no स्वतःmatic means of knowing what ISA IRQs are used.  Note that
 * अगर the BIOS करोesn't set a Link Device active, ACPI needs to program it
 * even अगर acpi_irq_nobalance is set.
 *
 * A tables of penalties aव्योमs directing PCI पूर्णांकerrupts to well known
 * ISA IRQs. Boot params are available to over-ride the शेष table:
 *
 * List पूर्णांकerrupts that are मुक्त क्रम PCI use.
 * acpi_irq_pci=n[,m]
 *
 * List पूर्णांकerrupts that should not be used क्रम PCI:
 * acpi_irq_isa=n[,m]
 *
 * Note that PCI IRQ routers have a list of possible IRQs,
 * which may not include the IRQs this table says are available.
 *
 * Since this heuristic can't tell the dअगरference between a link
 * that no device will attach to, vs. a link which may be shared
 * by multiple active devices -- it is not optimal.
 *
 * If पूर्णांकerrupt perक्रमmance is that important, get an IO-APIC प्रणाली
 * with a pin dedicated to each device.  Or क्रम that matter, an MSI
 * enabled प्रणाली.
 */

#घोषणा ACPI_MAX_ISA_IRQS	16

#घोषणा PIRQ_PENALTY_PCI_POSSIBLE	(16*16)
#घोषणा PIRQ_PENALTY_PCI_USING		(16*16*16)
#घोषणा PIRQ_PENALTY_ISA_TYPICAL	(16*16*16*16)
#घोषणा PIRQ_PENALTY_ISA_USED		(16*16*16*16*16)
#घोषणा PIRQ_PENALTY_ISA_ALWAYS		(16*16*16*16*16*16)

अटल पूर्णांक acpi_isa_irq_penalty[ACPI_MAX_ISA_IRQS] = अणु
	PIRQ_PENALTY_ISA_ALWAYS,	/* IRQ0 समयr */
	PIRQ_PENALTY_ISA_ALWAYS,	/* IRQ1 keyboard */
	PIRQ_PENALTY_ISA_ALWAYS,	/* IRQ2 cascade */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ3 serial */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ4 serial */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ5 someबार SoundBlaster */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ6 */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ7 parallel, spurious */
	PIRQ_PENALTY_ISA_TYPICAL,	/* IRQ8 rtc, someबार */
	0,				/* IRQ9  PCI, often acpi */
	0,				/* IRQ10 PCI */
	0,				/* IRQ11 PCI */
	PIRQ_PENALTY_ISA_USED,		/* IRQ12 mouse */
	PIRQ_PENALTY_ISA_USED,		/* IRQ13 fpe, someबार */
	PIRQ_PENALTY_ISA_USED,		/* IRQ14 ide0 */
	PIRQ_PENALTY_ISA_USED,		/* IRQ15 ide1 */
	/* >IRQ15 */
पूर्ण;

अटल पूर्णांक acpi_irq_pci_sharing_penalty(पूर्णांक irq)
अणु
	काष्ठा acpi_pci_link *link;
	पूर्णांक penalty = 0;
	पूर्णांक i;

	list_क्रम_each_entry(link, &acpi_link_list, list) अणु
		/*
		 * If a link is active, penalize its IRQ heavily
		 * so we try to choose a dअगरferent IRQ.
		 */
		अगर (link->irq.active && link->irq.active == irq)
			penalty += PIRQ_PENALTY_PCI_USING;

		/*
		 * penalize the IRQs PCI might use, but not as severely.
		 */
		क्रम (i = 0; i < link->irq.possible_count; i++)
			अगर (link->irq.possible[i] == irq)
				penalty += PIRQ_PENALTY_PCI_POSSIBLE /
					link->irq.possible_count;
	पूर्ण

	वापस penalty;
पूर्ण

अटल पूर्णांक acpi_irq_get_penalty(पूर्णांक irq)
अणु
	पूर्णांक penalty = 0;

	अगर (irq == sci_irq)
		penalty += sci_penalty;

	अगर (irq < ACPI_MAX_ISA_IRQS)
		वापस penalty + acpi_isa_irq_penalty[irq];

	वापस penalty + acpi_irq_pci_sharing_penalty(irq);
पूर्ण

पूर्णांक __init acpi_irq_penalty_init(व्योम)
अणु
	काष्ठा acpi_pci_link *link;
	पूर्णांक i;

	/*
	 * Update penalties to facilitate IRQ balancing.
	 */
	list_क्रम_each_entry(link, &acpi_link_list, list) अणु

		/*
		 * reflect the possible and active irqs in the penalty table --
		 * useful क्रम अवरोधing ties.
		 */
		अगर (link->irq.possible_count) अणु
			पूर्णांक penalty =
			    PIRQ_PENALTY_PCI_POSSIBLE /
			    link->irq.possible_count;

			क्रम (i = 0; i < link->irq.possible_count; i++) अणु
				अगर (link->irq.possible[i] < ACPI_MAX_ISA_IRQS)
					acpi_isa_irq_penalty[link->irq.
							 possible[i]] +=
					    penalty;
			पूर्ण

		पूर्ण अन्यथा अगर (link->irq.active &&
				(link->irq.active < ACPI_MAX_ISA_IRQS)) अणु
			acpi_isa_irq_penalty[link->irq.active] +=
			    PIRQ_PENALTY_PCI_POSSIBLE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_irq_balance = -1;	/* 0: अटल, 1: balance */

अटल पूर्णांक acpi_pci_link_allocate(काष्ठा acpi_pci_link *link)
अणु
	acpi_handle handle = link->device->handle;
	पूर्णांक irq;
	पूर्णांक i;

	अगर (link->irq.initialized) अणु
		अगर (link->refcnt == 0)
			/* This means the link is disabled but initialized */
			acpi_pci_link_set(link, link->irq.active);
		वापस 0;
	पूर्ण

	/*
	 * search क्रम active IRQ in list of possible IRQs.
	 */
	क्रम (i = 0; i < link->irq.possible_count; ++i) अणु
		अगर (link->irq.active == link->irq.possible[i])
			अवरोध;
	पूर्ण
	/*
	 * क्रमget active IRQ that is not in possible list
	 */
	अगर (i == link->irq.possible_count) अणु
		अगर (acpi_strict)
			acpi_handle_warn(handle, "_CRS %d not found in _PRS\n",
					 link->irq.active);
		link->irq.active = 0;
	पूर्ण

	/*
	 * अगर active found, use it; अन्यथा pick entry from end of possible list.
	 */
	अगर (link->irq.active)
		irq = link->irq.active;
	अन्यथा
		irq = link->irq.possible[link->irq.possible_count - 1];

	अगर (acpi_irq_balance || !link->irq.active) अणु
		/*
		 * Select the best IRQ.  This is करोne in reverse to promote
		 * the use of IRQs 9, 10, 11, and >15.
		 */
		क्रम (i = (link->irq.possible_count - 1); i >= 0; i--) अणु
			अगर (acpi_irq_get_penalty(irq) >
			    acpi_irq_get_penalty(link->irq.possible[i]))
				irq = link->irq.possible[i];
		पूर्ण
	पूर्ण
	अगर (acpi_irq_get_penalty(irq) >= PIRQ_PENALTY_ISA_ALWAYS) अणु
		acpi_handle_err(handle,
				"No IRQ available. Try pci=noacpi or acpi=off\n");
		वापस -ENODEV;
	पूर्ण

	/* Attempt to enable the link device at this IRQ. */
	अगर (acpi_pci_link_set(link, irq)) अणु
		acpi_handle_err(handle,
				"Unable to set IRQ. Try pci=noacpi or acpi=off\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (link->irq.active < ACPI_MAX_ISA_IRQS)
			acpi_isa_irq_penalty[link->irq.active] +=
				PIRQ_PENALTY_PCI_USING;

		acpi_handle_info(handle, "Enabled at IRQ %d\n",
				 link->irq.active);
	पूर्ण

	link->irq.initialized = 1;
	वापस 0;
पूर्ण

/*
 * acpi_pci_link_allocate_irq
 * success: वापस IRQ >= 0
 * failure: वापस -1
 */
पूर्णांक acpi_pci_link_allocate_irq(acpi_handle handle, पूर्णांक index, पूर्णांक *triggering,
			       पूर्णांक *polarity, अक्षर **name)
अणु
	पूर्णांक result;
	काष्ठा acpi_device *device;
	काष्ठा acpi_pci_link *link;

	result = acpi_bus_get_device(handle, &device);
	अगर (result) अणु
		acpi_handle_err(handle, "Invalid link device\n");
		वापस -1;
	पूर्ण

	link = acpi_driver_data(device);
	अगर (!link) अणु
		acpi_handle_err(handle, "Invalid link context\n");
		वापस -1;
	पूर्ण

	/* TBD: Support multiple index (IRQ) entries per Link Device */
	अगर (index) अणु
		acpi_handle_err(handle, "Invalid index %d\n", index);
		वापस -1;
	पूर्ण

	mutex_lock(&acpi_link_lock);
	अगर (acpi_pci_link_allocate(link)) अणु
		mutex_unlock(&acpi_link_lock);
		वापस -1;
	पूर्ण

	अगर (!link->irq.active) अणु
		mutex_unlock(&acpi_link_lock);
		acpi_handle_err(handle, "Link active IRQ is 0!\n");
		वापस -1;
	पूर्ण
	link->refcnt++;
	mutex_unlock(&acpi_link_lock);

	अगर (triggering)
		*triggering = link->irq.triggering;
	अगर (polarity)
		*polarity = link->irq.polarity;
	अगर (name)
		*name = acpi_device_bid(link->device);
	acpi_handle_debug(handle, "Link is referenced\n");
	वापस link->irq.active;
पूर्ण

/*
 * We करोn't change link's irq inक्रमmation here.  After it is reenabled, we
 * जारी use the info
 */
पूर्णांक acpi_pci_link_मुक्त_irq(acpi_handle handle)
अणु
	काष्ठा acpi_device *device;
	काष्ठा acpi_pci_link *link;
	acpi_status result;

	result = acpi_bus_get_device(handle, &device);
	अगर (result) अणु
		acpi_handle_err(handle, "Invalid link device\n");
		वापस -1;
	पूर्ण

	link = acpi_driver_data(device);
	अगर (!link) अणु
		acpi_handle_err(handle, "Invalid link context\n");
		वापस -1;
	पूर्ण

	mutex_lock(&acpi_link_lock);
	अगर (!link->irq.initialized) अणु
		mutex_unlock(&acpi_link_lock);
		acpi_handle_err(handle, "Link isn't initialized\n");
		वापस -1;
	पूर्ण
#अगर_घोषित	FUTURE_USE
	/*
	 * The Link reference count allows us to _DISable an unused link
	 * and suspend समय, and set it again  on resume.
	 * However, 2.6.12 still has irq_router.resume
	 * which blindly restores the link state.
	 * So we disable the reference count method
	 * to prevent duplicate acpi_pci_link_set()
	 * which would harm some प्रणालीs
	 */
	link->refcnt--;
#पूर्ण_अगर
	acpi_handle_debug(handle, "Link is dereferenced\n");

	अगर (link->refcnt == 0)
		acpi_evaluate_object(link->device->handle, "_DIS", शून्य, शून्य);

	mutex_unlock(&acpi_link_lock);
	वापस link->irq.active;
पूर्ण

/* --------------------------------------------------------------------------
                                 Driver Interface
   -------------------------------------------------------------------------- */

अटल पूर्णांक acpi_pci_link_add(काष्ठा acpi_device *device,
			     स्थिर काष्ठा acpi_device_id *not_used)
अणु
	acpi_handle handle = device->handle;
	काष्ठा acpi_pci_link *link;
	पूर्णांक result;
	पूर्णांक i;

	link = kzalloc(माप(काष्ठा acpi_pci_link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	link->device = device;
	म_नकल(acpi_device_name(device), ACPI_PCI_LINK_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PCI_LINK_CLASS);
	device->driver_data = link;

	mutex_lock(&acpi_link_lock);
	result = acpi_pci_link_get_possible(link);
	अगर (result)
		जाओ end;

	/* query and set link->irq.active */
	acpi_pci_link_get_current(link);

	pr_info("Interrupt link %s configured for IRQ %d\n",
		acpi_device_bid(device), link->irq.active);

	क्रम (i = 0; i < link->irq.possible_count; i++) अणु
		अगर (link->irq.active != link->irq.possible[i])
			acpi_handle_debug(handle, "Possible IRQ %d\n",
					  link->irq.possible[i]);
	पूर्ण

	अगर (!link->device->status.enabled)
		pr_info("Interrupt link %s disabled\n", acpi_device_bid(device));

	list_add_tail(&link->list, &acpi_link_list);

      end:
	/* disable all links -- to be activated on use */
	acpi_evaluate_object(handle, "_DIS", शून्य, शून्य);
	mutex_unlock(&acpi_link_lock);

	अगर (result)
		kमुक्त(link);

	वापस result < 0 ? result : 1;
पूर्ण

अटल पूर्णांक acpi_pci_link_resume(काष्ठा acpi_pci_link *link)
अणु
	अगर (link->refcnt && link->irq.active && link->irq.initialized)
		वापस (acpi_pci_link_set(link, link->irq.active));

	वापस 0;
पूर्ण

अटल व्योम irqrouter_resume(व्योम)
अणु
	काष्ठा acpi_pci_link *link;

	list_क्रम_each_entry(link, &acpi_link_list, list) अणु
		acpi_pci_link_resume(link);
	पूर्ण
पूर्ण

अटल व्योम acpi_pci_link_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_pci_link *link;

	link = acpi_driver_data(device);

	mutex_lock(&acpi_link_lock);
	list_del(&link->list);
	mutex_unlock(&acpi_link_lock);

	kमुक्त(link);
पूर्ण

/*
 * modअगरy acpi_isa_irq_penalty[] from cmdline
 */
अटल पूर्णांक __init acpi_irq_penalty_update(अक्षर *str, पूर्णांक used)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक retval;
		पूर्णांक irq;
		पूर्णांक new_penalty;

		retval = get_option(&str, &irq);

		अगर (!retval)
			अवरोध;	/* no number found */

		/* see अगर this is a ISA IRQ */
		अगर ((irq < 0) || (irq >= ACPI_MAX_ISA_IRQS))
			जारी;

		अगर (used)
			new_penalty = acpi_isa_irq_penalty[irq] +
					PIRQ_PENALTY_ISA_USED;
		अन्यथा
			new_penalty = 0;

		acpi_isa_irq_penalty[irq] = new_penalty;
		अगर (retval != 2)	/* no next number */
			अवरोध;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * We'd like PNP to call this routine क्रम the
 * single ISA_USED value क्रम each legacy device.
 * But instead it calls us with each POSSIBLE setting.
 * There is no ISA_POSSIBLE weight, so we simply use
 * the (small) PCI_USING penalty.
 */
व्योम acpi_penalize_isa_irq(पूर्णांक irq, पूर्णांक active)
अणु
	अगर ((irq >= 0) && (irq < ARRAY_SIZE(acpi_isa_irq_penalty)))
		acpi_isa_irq_penalty[irq] +=
		  (active ? PIRQ_PENALTY_ISA_USED : PIRQ_PENALTY_PCI_USING);
पूर्ण

bool acpi_isa_irq_available(पूर्णांक irq)
अणु
	वापस irq >= 0 && (irq >= ARRAY_SIZE(acpi_isa_irq_penalty) ||
		    acpi_irq_get_penalty(irq) < PIRQ_PENALTY_ISA_ALWAYS);
पूर्ण

व्योम acpi_penalize_sci_irq(पूर्णांक irq, पूर्णांक trigger, पूर्णांक polarity)
अणु
	sci_irq = irq;

	अगर (trigger == ACPI_MADT_TRIGGER_LEVEL &&
	    polarity == ACPI_MADT_POLARITY_ACTIVE_LOW)
		sci_penalty = PIRQ_PENALTY_PCI_USING;
	अन्यथा
		sci_penalty = PIRQ_PENALTY_ISA_ALWAYS;
पूर्ण

/*
 * Over-ride शेष table to reserve additional IRQs क्रम use by ISA
 * e.g. acpi_irq_isa=5
 * Useful क्रम telling ACPI how not to पूर्णांकerfere with your ISA sound card.
 */
अटल पूर्णांक __init acpi_irq_isa(अक्षर *str)
अणु
	वापस acpi_irq_penalty_update(str, 1);
पूर्ण

__setup("acpi_irq_isa=", acpi_irq_isa);

/*
 * Over-ride शेष table to मुक्त additional IRQs क्रम use by PCI
 * e.g. acpi_irq_pci=7,15
 * Used क्रम acpi_irq_balance to मुक्त up IRQs to reduce PCI IRQ sharing.
 */
अटल पूर्णांक __init acpi_irq_pci(अक्षर *str)
अणु
	वापस acpi_irq_penalty_update(str, 0);
पूर्ण

__setup("acpi_irq_pci=", acpi_irq_pci);

अटल पूर्णांक __init acpi_irq_nobalance_set(अक्षर *str)
अणु
	acpi_irq_balance = 0;
	वापस 1;
पूर्ण

__setup("acpi_irq_nobalance", acpi_irq_nobalance_set);

अटल पूर्णांक __init acpi_irq_balance_set(अक्षर *str)
अणु
	acpi_irq_balance = 1;
	वापस 1;
पूर्ण

__setup("acpi_irq_balance", acpi_irq_balance_set);

अटल काष्ठा syscore_ops irqrouter_syscore_ops = अणु
	.resume = irqrouter_resume,
पूर्ण;

व्योम __init acpi_pci_link_init(व्योम)
अणु
	अगर (acpi_noirq)
		वापस;

	अगर (acpi_irq_balance == -1) अणु
		/* no command line चयन: enable balancing in IOAPIC mode */
		अगर (acpi_irq_model == ACPI_IRQ_MODEL_IOAPIC)
			acpi_irq_balance = 1;
		अन्यथा
			acpi_irq_balance = 0;
	पूर्ण
	रेजिस्टर_syscore_ops(&irqrouter_syscore_ops);
	acpi_scan_add_handler(&pci_link_handler);
पूर्ण
