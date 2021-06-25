<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ACPI PCI HotPlug glue functions to ACPI CA subप्रणाली
 *
 * Copyright (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)
 * Copyright (C) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)
 * Copyright (C) 2002,2003 NEC Corporation
 * Copyright (C) 2003-2005 Matthew Wilcox (willy@infradead.org)
 * Copyright (C) 2003-2005 Hewlett Packard
 * Copyright (C) 2005 Rajesh Shah (rajesh.shah@पूर्णांकel.com)
 * Copyright (C) 2005 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <kristen.c.accardi@पूर्णांकel.com>
 *
 */

/*
 * Lअगरeसमय rules क्रम pci_dev:
 *  - The one in acpiphp_bridge has its refcount elevated by pci_get_slot()
 *    when the bridge is scanned and it loses a refcount when the bridge
 *    is हटाओd.
 *  - When a P2P bridge is present, we elevate the refcount on the subordinate
 *    bus. It loses the refcount when the the driver unloads.
 */

#घोषणा pr_fmt(fmt) "acpiphp_glue: " fmt

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#समावेश "../pci.h"
#समावेश "acpiphp.h"

अटल LIST_HEAD(bridge_list);
अटल DEFINE_MUTEX(bridge_mutex);

अटल पूर्णांक acpiphp_hotplug_notअगरy(काष्ठा acpi_device *adev, u32 type);
अटल व्योम acpiphp_post_करोck_fixup(काष्ठा acpi_device *adev);
अटल व्योम acpiphp_sanitize_bus(काष्ठा pci_bus *bus);
अटल व्योम hotplug_event(u32 type, काष्ठा acpiphp_context *context);
अटल व्योम मुक्त_bridge(काष्ठा kref *kref);

/**
 * acpiphp_init_context - Create hotplug context and grab a reference to it.
 * @adev: ACPI device object to create the context क्रम.
 *
 * Call under acpi_hp_context_lock.
 */
अटल काष्ठा acpiphp_context *acpiphp_init_context(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpiphp_context *context;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस शून्य;

	context->refcount = 1;
	context->hp.notअगरy = acpiphp_hotplug_notअगरy;
	context->hp.fixup = acpiphp_post_करोck_fixup;
	acpi_set_hp_context(adev, &context->hp);
	वापस context;
पूर्ण

/**
 * acpiphp_get_context - Get hotplug context and grab a reference to it.
 * @adev: ACPI device object to get the context क्रम.
 *
 * Call under acpi_hp_context_lock.
 */
अटल काष्ठा acpiphp_context *acpiphp_get_context(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpiphp_context *context;

	अगर (!adev->hp)
		वापस शून्य;

	context = to_acpiphp_context(adev->hp);
	context->refcount++;
	वापस context;
पूर्ण

/**
 * acpiphp_put_context - Drop a reference to ACPI hotplug context.
 * @context: ACPI hotplug context to drop a reference to.
 *
 * The context object is हटाओd अगर there are no more references to it.
 *
 * Call under acpi_hp_context_lock.
 */
अटल व्योम acpiphp_put_context(काष्ठा acpiphp_context *context)
अणु
	अगर (--context->refcount)
		वापस;

	WARN_ON(context->bridge);
	context->hp.self->hp = शून्य;
	kमुक्त(context);
पूर्ण

अटल अंतरभूत व्योम get_bridge(काष्ठा acpiphp_bridge *bridge)
अणु
	kref_get(&bridge->ref);
पूर्ण

अटल अंतरभूत व्योम put_bridge(काष्ठा acpiphp_bridge *bridge)
अणु
	kref_put(&bridge->ref, मुक्त_bridge);
पूर्ण

अटल काष्ठा acpiphp_context *acpiphp_grab_context(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpiphp_context *context;

	acpi_lock_hp_context();

	context = acpiphp_get_context(adev);
	अगर (!context)
		जाओ unlock;

	अगर (context->func.parent->is_going_away) अणु
		acpiphp_put_context(context);
		context = शून्य;
		जाओ unlock;
	पूर्ण

	get_bridge(context->func.parent);
	acpiphp_put_context(context);

unlock:
	acpi_unlock_hp_context();
	वापस context;
पूर्ण

अटल व्योम acpiphp_let_context_go(काष्ठा acpiphp_context *context)
अणु
	put_bridge(context->func.parent);
पूर्ण

अटल व्योम मुक्त_bridge(काष्ठा kref *kref)
अणु
	काष्ठा acpiphp_context *context;
	काष्ठा acpiphp_bridge *bridge;
	काष्ठा acpiphp_slot *slot, *next;
	काष्ठा acpiphp_func *func, *पंचांगp;

	acpi_lock_hp_context();

	bridge = container_of(kref, काष्ठा acpiphp_bridge, ref);

	list_क्रम_each_entry_safe(slot, next, &bridge->slots, node) अणु
		list_क्रम_each_entry_safe(func, पंचांगp, &slot->funcs, sibling)
			acpiphp_put_context(func_to_context(func));

		kमुक्त(slot);
	पूर्ण

	context = bridge->context;
	/* Root bridges will not have hotplug context. */
	अगर (context) अणु
		/* Release the reference taken by acpiphp_क्रमागतerate_slots(). */
		put_bridge(context->func.parent);
		context->bridge = शून्य;
		acpiphp_put_context(context);
	पूर्ण

	put_device(&bridge->pci_bus->dev);
	pci_dev_put(bridge->pci_dev);
	kमुक्त(bridge);

	acpi_unlock_hp_context();
पूर्ण

/**
 * acpiphp_post_करोck_fixup - Post-करोck fixups क्रम PCI devices.
 * @adev: ACPI device object corresponding to a PCI device.
 *
 * TBD - figure out a way to only call fixups क्रम प्रणालीs that require them.
 */
अटल व्योम acpiphp_post_करोck_fixup(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpiphp_context *context = acpiphp_grab_context(adev);
	काष्ठा pci_bus *bus;
	u32 buses;

	अगर (!context)
		वापस;

	bus = context->func.slot->bus;
	अगर (!bus->self)
		जाओ out;

	/* fixup bad _DCK function that reग_लिखोs
	 * secondary bridge on slot
	 */
	pci_पढ़ो_config_dword(bus->self, PCI_PRIMARY_BUS, &buses);

	अगर (((buses >> 8) & 0xff) != bus->busn_res.start) अणु
		buses = (buses & 0xff000000)
			| ((अचिन्हित पूर्णांक)(bus->primary)     <<  0)
			| ((अचिन्हित पूर्णांक)(bus->busn_res.start)   <<  8)
			| ((अचिन्हित पूर्णांक)(bus->busn_res.end) << 16);
		pci_ग_लिखो_config_dword(bus->self, PCI_PRIMARY_BUS, buses);
	पूर्ण

 out:
	acpiphp_let_context_go(context);
पूर्ण

/**
 * acpiphp_add_context - Add ACPIPHP context to an ACPI device object.
 * @handle: ACPI handle of the object to add a context to.
 * @lvl: Not used.
 * @data: The object's parent ACPIPHP bridge.
 * @rv: Not used.
 */
अटल acpi_status acpiphp_add_context(acpi_handle handle, u32 lvl, व्योम *data,
				       व्योम **rv)
अणु
	काष्ठा acpiphp_bridge *bridge = data;
	काष्ठा acpiphp_context *context;
	काष्ठा acpi_device *adev;
	काष्ठा acpiphp_slot *slot;
	काष्ठा acpiphp_func *newfunc;
	acpi_status status = AE_OK;
	अचिन्हित दीर्घ दीर्घ adr;
	पूर्णांक device, function;
	काष्ठा pci_bus *pbus = bridge->pci_bus;
	काष्ठा pci_dev *pdev = bridge->pci_dev;
	u32 val;

	status = acpi_evaluate_पूर्णांकeger(handle, "_ADR", शून्य, &adr);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			acpi_handle_warn(handle,
				"can't evaluate _ADR (%#x)\n", status);
		वापस AE_OK;
	पूर्ण
	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	device = (adr >> 16) & 0xffff;
	function = adr & 0xffff;

	acpi_lock_hp_context();
	context = acpiphp_init_context(adev);
	अगर (!context) अणु
		acpi_unlock_hp_context();
		acpi_handle_err(handle, "No hotplug context\n");
		वापस AE_NOT_EXIST;
	पूर्ण
	newfunc = &context->func;
	newfunc->function = function;
	newfunc->parent = bridge;
	acpi_unlock_hp_context();

	/*
	 * If this is a करोck device, its _EJ0 should be executed by the करोck
	 * notअगरy handler after calling _DCK.
	 */
	अगर (!is_करोck_device(adev) && acpi_has_method(handle, "_EJ0"))
		newfunc->flags = FUNC_HAS_EJ0;

	अगर (acpi_has_method(handle, "_STA"))
		newfunc->flags |= FUNC_HAS_STA;

	/* search क्रम objects that share the same slot */
	list_क्रम_each_entry(slot, &bridge->slots, node)
		अगर (slot->device == device)
			जाओ slot_found;

	slot = kzalloc(माप(काष्ठा acpiphp_slot), GFP_KERNEL);
	अगर (!slot) अणु
		acpi_lock_hp_context();
		acpiphp_put_context(context);
		acpi_unlock_hp_context();
		वापस AE_NO_MEMORY;
	पूर्ण

	slot->bus = bridge->pci_bus;
	slot->device = device;
	INIT_LIST_HEAD(&slot->funcs);

	list_add_tail(&slot->node, &bridge->slots);

	/*
	 * Expose slots to user space क्रम functions that have _EJ0 or _RMV or
	 * are located in करोck stations.  Do not expose them क्रम devices handled
	 * by the native PCIe hotplug (PCIeHP) or standard PCI hotplug
	 * (SHPCHP), because that code is supposed to expose slots to user
	 * space in those हालs.
	 */
	अगर ((acpi_pci_check_ejectable(pbus, handle) || is_करोck_device(adev))
	    && !(pdev && hotplug_is_native(pdev))) अणु
		अचिन्हित दीर्घ दीर्घ sun;
		पूर्णांक retval;

		bridge->nr_slots++;
		status = acpi_evaluate_पूर्णांकeger(handle, "_SUN", शून्य, &sun);
		अगर (ACPI_FAILURE(status))
			sun = bridge->nr_slots;

		pr_debug("found ACPI PCI Hotplug slot %llu at PCI %04x:%02x:%02x\n",
		    sun, pci_करोमुख्य_nr(pbus), pbus->number, device);

		retval = acpiphp_रेजिस्टर_hotplug_slot(slot, sun);
		अगर (retval) अणु
			slot->slot = शून्य;
			bridge->nr_slots--;
			अगर (retval == -EBUSY)
				pr_warn("Slot %llu already registered by another hotplug driver\n", sun);
			अन्यथा
				pr_warn("acpiphp_register_hotplug_slot failed (err code = 0x%x)\n", retval);
		पूर्ण
		/* Even अगर the slot registration fails, we can still use it. */
	पूर्ण

 slot_found:
	newfunc->slot = slot;
	list_add_tail(&newfunc->sibling, &slot->funcs);

	अगर (pci_bus_पढ़ो_dev_venकरोr_id(pbus, PCI_DEVFN(device, function),
				       &val, 60*1000))
		slot->flags |= SLOT_ENABLED;

	वापस AE_OK;
पूर्ण

अटल व्योम cleanup_bridge(काष्ठा acpiphp_bridge *bridge)
अणु
	काष्ठा acpiphp_slot *slot;
	काष्ठा acpiphp_func *func;

	list_क्रम_each_entry(slot, &bridge->slots, node) अणु
		list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
			काष्ठा acpi_device *adev = func_to_acpi_device(func);

			acpi_lock_hp_context();
			adev->hp->notअगरy = शून्य;
			adev->hp->fixup = शून्य;
			acpi_unlock_hp_context();
		पूर्ण
		slot->flags |= SLOT_IS_GOING_AWAY;
		अगर (slot->slot)
			acpiphp_unरेजिस्टर_hotplug_slot(slot);
	पूर्ण

	mutex_lock(&bridge_mutex);
	list_del(&bridge->list);
	mutex_unlock(&bridge_mutex);

	acpi_lock_hp_context();
	bridge->is_going_away = true;
	acpi_unlock_hp_context();
पूर्ण

/**
 * acpiphp_max_busnr - वापस the highest reserved bus number under the given bus.
 * @bus: bus to start search with
 */
अटल अचिन्हित अक्षर acpiphp_max_busnr(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *पंचांगp;
	अचिन्हित अक्षर max, n;

	/*
	 * pci_bus_max_busnr will वापस the highest
	 * reserved busnr क्रम all these children.
	 * that is equivalent to the bus->subordinate
	 * value.  We करोn't want to use the parent's
	 * bus->subordinate value because it could have
	 * padding in it.
	 */
	max = bus->busn_res.start;

	list_क्रम_each_entry(पंचांगp, &bus->children, node) अणु
		n = pci_bus_max_busnr(पंचांगp);
		अगर (n > max)
			max = n;
	पूर्ण
	वापस max;
पूर्ण

अटल व्योम acpiphp_set_acpi_region(काष्ठा acpiphp_slot *slot)
अणु
	काष्ठा acpiphp_func *func;

	list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
		/* _REG is optional, we करोn't care about अगर there is failure */
		acpi_evaluate_reg(func_to_handle(func),
				  ACPI_ADR_SPACE_PCI_CONFIG,
				  ACPI_REG_CONNECT);
	पूर्ण
पूर्ण

अटल व्योम check_hotplug_bridge(काष्ठा acpiphp_slot *slot, काष्ठा pci_dev *dev)
अणु
	काष्ठा acpiphp_func *func;

	/* quirk, or pcie could set it alपढ़ोy */
	अगर (dev->is_hotplug_bridge)
		वापस;

	list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
		अगर (PCI_FUNC(dev->devfn) == func->function) अणु
			dev->is_hotplug_bridge = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक acpiphp_rescan_slot(काष्ठा acpiphp_slot *slot)
अणु
	काष्ठा acpiphp_func *func;

	list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
		काष्ठा acpi_device *adev = func_to_acpi_device(func);

		acpi_bus_scan(adev->handle);
		अगर (acpi_device_क्रमागतerated(adev))
			acpi_device_set_घातer(adev, ACPI_STATE_D0);
	पूर्ण
	वापस pci_scan_slot(slot->bus, PCI_DEVFN(slot->device, 0));
पूर्ण

अटल व्योम acpiphp_native_scan_bridge(काष्ठा pci_dev *bridge)
अणु
	काष्ठा pci_bus *bus = bridge->subordinate;
	काष्ठा pci_dev *dev;
	पूर्णांक max;

	अगर (!bus)
		वापस;

	max = bus->busn_res.start;
	/* Scan alपढ़ोy configured non-hotplug bridges */
	क्रम_each_pci_bridge(dev, bus) अणु
		अगर (!hotplug_is_native(dev))
			max = pci_scan_bridge(bus, dev, max, 0);
	पूर्ण

	/* Scan non-hotplug bridges that need to be reconfigured */
	क्रम_each_pci_bridge(dev, bus) अणु
		अगर (hotplug_is_native(dev))
			जारी;

		max = pci_scan_bridge(bus, dev, max, 1);
		अगर (dev->subordinate) अणु
			pcibios_resource_survey_bus(dev->subordinate);
			pci_bus_size_bridges(dev->subordinate);
			pci_bus_assign_resources(dev->subordinate);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * enable_slot - enable, configure a slot
 * @slot: slot to be enabled
 * @bridge: true अगर enable is क्रम the whole bridge (not a single slot)
 *
 * This function should be called per *physical slot*,
 * not per each slot object in ACPI namespace.
 */
अटल व्योम enable_slot(काष्ठा acpiphp_slot *slot, bool bridge)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *bus = slot->bus;
	काष्ठा acpiphp_func *func;

	अगर (bridge && bus->self && hotplug_is_native(bus->self)) अणु
		/*
		 * If native hotplug is used, it will take care of hotplug
		 * slot management and resource allocation क्रम hotplug
		 * bridges. However, ACPI hotplug may still be used क्रम
		 * non-hotplug bridges to bring in additional devices such
		 * as a Thunderbolt host controller.
		 */
		क्रम_each_pci_bridge(dev, bus) अणु
			अगर (PCI_SLOT(dev->devfn) == slot->device)
				acpiphp_native_scan_bridge(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		LIST_HEAD(add_list);
		पूर्णांक max, pass;

		acpiphp_rescan_slot(slot);
		max = acpiphp_max_busnr(bus);
		क्रम (pass = 0; pass < 2; pass++) अणु
			क्रम_each_pci_bridge(dev, bus) अणु
				अगर (PCI_SLOT(dev->devfn) != slot->device)
					जारी;

				max = pci_scan_bridge(bus, dev, max, pass);
				अगर (pass && dev->subordinate) अणु
					check_hotplug_bridge(slot, dev);
					pcibios_resource_survey_bus(dev->subordinate);
					__pci_bus_size_bridges(dev->subordinate,
							       &add_list);
				पूर्ण
			पूर्ण
		पूर्ण
		__pci_bus_assign_resources(bus, &add_list, शून्य);
	पूर्ण

	acpiphp_sanitize_bus(bus);
	pcie_bus_configure_settings(bus);
	acpiphp_set_acpi_region(slot);

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		/* Assume that newly added devices are घातered on alपढ़ोy. */
		अगर (!pci_dev_is_added(dev))
			dev->current_state = PCI_D0;
	पूर्ण

	pci_bus_add_devices(bus);

	slot->flags |= SLOT_ENABLED;
	list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
		dev = pci_get_slot(bus, PCI_DEVFN(slot->device,
						  func->function));
		अगर (!dev) अणु
			/* Do not set SLOT_ENABLED flag अगर some funcs
			   are not added. */
			slot->flags &= ~SLOT_ENABLED;
			जारी;
		पूर्ण
		pci_dev_put(dev);
	पूर्ण
पूर्ण

/**
 * disable_slot - disable a slot
 * @slot: ACPI PHP slot
 */
अटल व्योम disable_slot(काष्ठा acpiphp_slot *slot)
अणु
	काष्ठा pci_bus *bus = slot->bus;
	काष्ठा pci_dev *dev, *prev;
	काष्ठा acpiphp_func *func;

	/*
	 * enable_slot() क्रमागतerates all functions in this device via
	 * pci_scan_slot(), whether they have associated ACPI hotplug
	 * methods (_EJ0, etc.) or not.  Thereक्रमe, we हटाओ all functions
	 * here.
	 */
	list_क्रम_each_entry_safe_reverse(dev, prev, &bus->devices, bus_list)
		अगर (PCI_SLOT(dev->devfn) == slot->device)
			pci_stop_and_हटाओ_bus_device(dev);

	list_क्रम_each_entry(func, &slot->funcs, sibling)
		acpi_bus_trim(func_to_acpi_device(func));

	slot->flags &= ~SLOT_ENABLED;
पूर्ण

अटल bool slot_no_hotplug(काष्ठा acpiphp_slot *slot)
अणु
	काष्ठा pci_bus *bus = slot->bus;
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (PCI_SLOT(dev->devfn) == slot->device && dev->ignore_hotplug)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * get_slot_status - get ACPI slot status
 * @slot: ACPI PHP slot
 *
 * If a slot has _STA क्रम each function and अगर any one of them
 * वापसed non-zero status, वापस it.
 *
 * If a slot करोesn't have _STA and if any one of its functions'
 * configuration space is configured, वापस 0x0f as a _STA.
 *
 * Otherwise वापस 0.
 */
अटल अचिन्हित पूर्णांक get_slot_status(काष्ठा acpiphp_slot *slot)
अणु
	अचिन्हित दीर्घ दीर्घ sta = 0;
	काष्ठा acpiphp_func *func;
	u32 dvid;

	list_क्रम_each_entry(func, &slot->funcs, sibling) अणु
		अगर (func->flags & FUNC_HAS_STA) अणु
			acpi_status status;

			status = acpi_evaluate_पूर्णांकeger(func_to_handle(func),
						       "_STA", शून्य, &sta);
			अगर (ACPI_SUCCESS(status) && sta)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (pci_bus_पढ़ो_dev_venकरोr_id(slot->bus,
					PCI_DEVFN(slot->device, func->function),
					&dvid, 0)) अणु
				sta = ACPI_STA_ALL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!sta) अणु
		/*
		 * Check क्रम the slot itself since it may be that the
		 * ACPI slot is a device below PCIe upstream port so in
		 * that हाल it may not even be reachable yet.
		 */
		अगर (pci_bus_पढ़ो_dev_venकरोr_id(slot->bus,
				PCI_DEVFN(slot->device, 0), &dvid, 0)) अणु
			sta = ACPI_STA_ALL;
		पूर्ण
	पूर्ण

	वापस (अचिन्हित पूर्णांक)sta;
पूर्ण

अटल अंतरभूत bool device_status_valid(अचिन्हित पूर्णांक sta)
अणु
	/*
	 * ACPI spec says that _STA may वापस bit 0 clear with bit 3 set
	 * अगर the device is valid but करोes not require a device driver to be
	 * loaded (Section 6.3.7 of ACPI 5.0A).
	 */
	अचिन्हित पूर्णांक mask = ACPI_STA_DEVICE_ENABLED | ACPI_STA_DEVICE_FUNCTIONING;
	वापस (sta & mask) == mask;
पूर्ण

/**
 * trim_stale_devices - हटाओ PCI devices that are not responding.
 * @dev: PCI device to start walking the hierarchy from.
 */
अटल व्योम trim_stale_devices(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);
	काष्ठा pci_bus *bus = dev->subordinate;
	bool alive = dev->ignore_hotplug;

	अगर (adev) अणु
		acpi_status status;
		अचिन्हित दीर्घ दीर्घ sta;

		status = acpi_evaluate_पूर्णांकeger(adev->handle, "_STA", शून्य, &sta);
		alive = alive || (ACPI_SUCCESS(status) && device_status_valid(sta));
	पूर्ण
	अगर (!alive)
		alive = pci_device_is_present(dev);

	अगर (!alive) अणु
		pci_dev_set_disconnected(dev, शून्य);
		अगर (pci_has_subordinate(dev))
			pci_walk_bus(dev->subordinate, pci_dev_set_disconnected,
				     शून्य);

		pci_stop_and_हटाओ_bus_device(dev);
		अगर (adev)
			acpi_bus_trim(adev);
	पूर्ण अन्यथा अगर (bus) अणु
		काष्ठा pci_dev *child, *पंचांगp;

		/* The device is a bridge. so check the bus below it. */
		pm_runसमय_get_sync(&dev->dev);
		list_क्रम_each_entry_safe_reverse(child, पंचांगp, &bus->devices, bus_list)
			trim_stale_devices(child);

		pm_runसमय_put(&dev->dev);
	पूर्ण
पूर्ण

/**
 * acpiphp_check_bridge - re-क्रमागतerate devices
 * @bridge: where to begin re-क्रमागतeration
 *
 * Iterate over all slots under this bridge and make sure that अगर a
 * card is present they are enabled, and अगर not they are disabled.
 */
अटल व्योम acpiphp_check_bridge(काष्ठा acpiphp_bridge *bridge)
अणु
	काष्ठा acpiphp_slot *slot;

	/* Bail out अगर the bridge is going away. */
	अगर (bridge->is_going_away)
		वापस;

	अगर (bridge->pci_dev)
		pm_runसमय_get_sync(&bridge->pci_dev->dev);

	list_क्रम_each_entry(slot, &bridge->slots, node) अणु
		काष्ठा pci_bus *bus = slot->bus;
		काष्ठा pci_dev *dev, *पंचांगp;

		अगर (slot_no_hotplug(slot)) अणु
			; /* करो nothing */
		पूर्ण अन्यथा अगर (device_status_valid(get_slot_status(slot))) अणु
			/* हटाओ stale devices अगर any */
			list_क्रम_each_entry_safe_reverse(dev, पंचांगp,
							 &bus->devices, bus_list)
				अगर (PCI_SLOT(dev->devfn) == slot->device)
					trim_stale_devices(dev);

			/* configure all functions */
			enable_slot(slot, true);
		पूर्ण अन्यथा अणु
			disable_slot(slot);
		पूर्ण
	पूर्ण

	अगर (bridge->pci_dev)
		pm_runसमय_put(&bridge->pci_dev->dev);
पूर्ण

/*
 * Remove devices क्रम which we could not assign resources, call
 * arch specअगरic code to fix-up the bus
 */
अटल व्योम acpiphp_sanitize_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev, *पंचांगp;
	पूर्णांक i;
	अचिन्हित दीर्घ type_mask = IORESOURCE_IO | IORESOURCE_MEM;

	list_क्रम_each_entry_safe_reverse(dev, पंचांगp, &bus->devices, bus_list) अणु
		क्रम (i = 0; i < PCI_BRIDGE_RESOURCES; i++) अणु
			काष्ठा resource *res = &dev->resource[i];
			अगर ((res->flags & type_mask) && !res->start &&
					res->end) अणु
				/* Could not assign a required resources
				 * क्रम this device, हटाओ it */
				pci_stop_and_हटाओ_bus_device(dev);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ACPI event handlers
 */

व्योम acpiphp_check_host_bridge(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpiphp_bridge *bridge = शून्य;

	acpi_lock_hp_context();
	अगर (adev->hp) अणु
		bridge = to_acpiphp_root_context(adev->hp)->root_bridge;
		अगर (bridge)
			get_bridge(bridge);
	पूर्ण
	acpi_unlock_hp_context();
	अगर (bridge) अणु
		pci_lock_rescan_हटाओ();

		acpiphp_check_bridge(bridge);

		pci_unlock_rescan_हटाओ();
		put_bridge(bridge);
	पूर्ण
पूर्ण

अटल पूर्णांक acpiphp_disable_and_eject_slot(काष्ठा acpiphp_slot *slot);

अटल व्योम hotplug_event(u32 type, काष्ठा acpiphp_context *context)
अणु
	acpi_handle handle = context->hp.self->handle;
	काष्ठा acpiphp_func *func = &context->func;
	काष्ठा acpiphp_slot *slot = func->slot;
	काष्ठा acpiphp_bridge *bridge;

	acpi_lock_hp_context();
	bridge = context->bridge;
	अगर (bridge)
		get_bridge(bridge);

	acpi_unlock_hp_context();

	pci_lock_rescan_हटाओ();

	चयन (type) अणु
	हाल ACPI_NOTIFY_BUS_CHECK:
		/* bus re-क्रमागतerate */
		acpi_handle_debug(handle, "Bus check in %s()\n", __func__);
		अगर (bridge)
			acpiphp_check_bridge(bridge);
		अन्यथा अगर (!(slot->flags & SLOT_IS_GOING_AWAY))
			enable_slot(slot, false);

		अवरोध;

	हाल ACPI_NOTIFY_DEVICE_CHECK:
		/* device check */
		acpi_handle_debug(handle, "Device check in %s()\n", __func__);
		अगर (bridge) अणु
			acpiphp_check_bridge(bridge);
		पूर्ण अन्यथा अगर (!(slot->flags & SLOT_IS_GOING_AWAY)) अणु
			/*
			 * Check अगर anything has changed in the slot and rescan
			 * from the parent अगर that's the हाल.
			 */
			अगर (acpiphp_rescan_slot(slot))
				acpiphp_check_bridge(func->parent);
		पूर्ण
		अवरोध;

	हाल ACPI_NOTIFY_EJECT_REQUEST:
		/* request device eject */
		acpi_handle_debug(handle, "Eject request in %s()\n", __func__);
		acpiphp_disable_and_eject_slot(slot);
		अवरोध;
	पूर्ण

	pci_unlock_rescan_हटाओ();
	अगर (bridge)
		put_bridge(bridge);
पूर्ण

अटल पूर्णांक acpiphp_hotplug_notअगरy(काष्ठा acpi_device *adev, u32 type)
अणु
	काष्ठा acpiphp_context *context;

	context = acpiphp_grab_context(adev);
	अगर (!context)
		वापस -ENODATA;

	hotplug_event(type, context);
	acpiphp_let_context_go(context);
	वापस 0;
पूर्ण

/**
 * acpiphp_क्रमागतerate_slots - Enumerate PCI slots क्रम a given bus.
 * @bus: PCI bus to क्रमागतerate the slots क्रम.
 *
 * A "slot" is an object associated with a PCI device number.  All functions
 * (PCI devices) with the same bus and device number beदीर्घ to the same slot.
 */
व्योम acpiphp_क्रमागतerate_slots(काष्ठा pci_bus *bus)
अणु
	काष्ठा acpiphp_bridge *bridge;
	काष्ठा acpi_device *adev;
	acpi_handle handle;
	acpi_status status;

	अगर (acpiphp_disabled)
		वापस;

	adev = ACPI_COMPANION(bus->bridge);
	अगर (!adev)
		वापस;

	handle = adev->handle;
	bridge = kzalloc(माप(काष्ठा acpiphp_bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस;

	INIT_LIST_HEAD(&bridge->slots);
	kref_init(&bridge->ref);
	bridge->pci_dev = pci_dev_get(bus->self);
	bridge->pci_bus = bus;

	/*
	 * Grab a ref to the subordinate PCI bus in हाल the bus is
	 * हटाओd via PCI core logical hotplug. The ref pins the bus
	 * (which we access during module unload).
	 */
	get_device(&bus->dev);

	acpi_lock_hp_context();
	अगर (pci_is_root_bus(bridge->pci_bus)) अणु
		काष्ठा acpiphp_root_context *root_context;

		root_context = kzalloc(माप(*root_context), GFP_KERNEL);
		अगर (!root_context)
			जाओ err;

		root_context->root_bridge = bridge;
		acpi_set_hp_context(adev, &root_context->hp);
	पूर्ण अन्यथा अणु
		काष्ठा acpiphp_context *context;

		/*
		 * This bridge should have been रेजिस्टरed as a hotplug function
		 * under its parent, so the context should be there, unless the
		 * parent is going to be handled by pciehp, in which हाल this
		 * bridge is not पूर्णांकeresting to us either.
		 */
		context = acpiphp_get_context(adev);
		अगर (!context)
			जाओ err;

		bridge->context = context;
		context->bridge = bridge;
		/* Get a reference to the parent bridge. */
		get_bridge(context->func.parent);
	पूर्ण
	acpi_unlock_hp_context();

	/* Must be added to the list prior to calling acpiphp_add_context(). */
	mutex_lock(&bridge_mutex);
	list_add(&bridge->list, &bridge_list);
	mutex_unlock(&bridge_mutex);

	/* रेजिस्टर all slot objects under this bridge */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     acpiphp_add_context, शून्य, bridge, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(handle, "failed to register slots\n");
		cleanup_bridge(bridge);
		put_bridge(bridge);
	पूर्ण
	वापस;

 err:
	acpi_unlock_hp_context();
	put_device(&bus->dev);
	pci_dev_put(bridge->pci_dev);
	kमुक्त(bridge);
पूर्ण

अटल व्योम acpiphp_drop_bridge(काष्ठा acpiphp_bridge *bridge)
अणु
	अगर (pci_is_root_bus(bridge->pci_bus)) अणु
		काष्ठा acpiphp_root_context *root_context;
		काष्ठा acpi_device *adev;

		acpi_lock_hp_context();
		adev = ACPI_COMPANION(bridge->pci_bus->bridge);
		root_context = to_acpiphp_root_context(adev->hp);
		adev->hp = शून्य;
		acpi_unlock_hp_context();
		kमुक्त(root_context);
	पूर्ण
	cleanup_bridge(bridge);
	put_bridge(bridge);
पूर्ण

/**
 * acpiphp_हटाओ_slots - Remove slot objects associated with a given bus.
 * @bus: PCI bus to हटाओ the slot objects क्रम.
 */
व्योम acpiphp_हटाओ_slots(काष्ठा pci_bus *bus)
अणु
	काष्ठा acpiphp_bridge *bridge;

	अगर (acpiphp_disabled)
		वापस;

	mutex_lock(&bridge_mutex);
	list_क्रम_each_entry(bridge, &bridge_list, list)
		अगर (bridge->pci_bus == bus) अणु
			mutex_unlock(&bridge_mutex);
			acpiphp_drop_bridge(bridge);
			वापस;
		पूर्ण

	mutex_unlock(&bridge_mutex);
पूर्ण

/**
 * acpiphp_enable_slot - घातer on slot
 * @slot: ACPI PHP slot
 */
पूर्णांक acpiphp_enable_slot(काष्ठा acpiphp_slot *slot)
अणु
	pci_lock_rescan_हटाओ();

	अगर (slot->flags & SLOT_IS_GOING_AWAY) अणु
		pci_unlock_rescan_हटाओ();
		वापस -ENODEV;
	पूर्ण

	/* configure all functions */
	अगर (!(slot->flags & SLOT_ENABLED))
		enable_slot(slot, false);

	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण

/**
 * acpiphp_disable_and_eject_slot - घातer off and eject slot
 * @slot: ACPI PHP slot
 */
अटल पूर्णांक acpiphp_disable_and_eject_slot(काष्ठा acpiphp_slot *slot)
अणु
	काष्ठा acpiphp_func *func;

	अगर (slot->flags & SLOT_IS_GOING_AWAY)
		वापस -ENODEV;

	/* unconfigure all functions */
	disable_slot(slot);

	list_क्रम_each_entry(func, &slot->funcs, sibling)
		अगर (func->flags & FUNC_HAS_EJ0) अणु
			acpi_handle handle = func_to_handle(func);

			अगर (ACPI_FAILURE(acpi_evaluate_ej0(handle)))
				acpi_handle_err(handle, "_EJ0 failed\n");

			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

पूर्णांक acpiphp_disable_slot(काष्ठा acpiphp_slot *slot)
अणु
	पूर्णांक ret;

	/*
	 * Acquire acpi_scan_lock to ensure that the execution of _EJ0 in
	 * acpiphp_disable_and_eject_slot() will be synchronized properly.
	 */
	acpi_scan_lock_acquire();
	pci_lock_rescan_हटाओ();
	ret = acpiphp_disable_and_eject_slot(slot);
	pci_unlock_rescan_हटाओ();
	acpi_scan_lock_release();
	वापस ret;
पूर्ण

/*
 * slot enabled:  1
 * slot disabled: 0
 */
u8 acpiphp_get_घातer_status(काष्ठा acpiphp_slot *slot)
अणु
	वापस (slot->flags & SLOT_ENABLED);
पूर्ण

/*
 * latch   खोलो:  1
 * latch बंदd:  0
 */
u8 acpiphp_get_latch_status(काष्ठा acpiphp_slot *slot)
अणु
	वापस !(get_slot_status(slot) & ACPI_STA_DEVICE_UI);
पूर्ण

/*
 * adapter presence : 1
 *          असलence : 0
 */
u8 acpiphp_get_adapter_status(काष्ठा acpiphp_slot *slot)
अणु
	वापस !!get_slot_status(slot);
पूर्ण
