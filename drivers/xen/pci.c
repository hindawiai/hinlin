<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Intel Corporation.
 *
 * Author: Weiकरोng Han <weiकरोng.han@पूर्णांकel.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci-acpi.h>
#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/पूर्णांकerface/xen.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश "../pci/pci.h"
#अगर_घोषित CONFIG_PCI_MMCONFIG
#समावेश <यंत्र/pci_x86.h>

अटल पूर्णांक xen_mcfg_late(व्योम);
#पूर्ण_अगर

अटल bool __पढ़ो_mostly pci_seg_supported = true;

अटल पूर्णांक xen_add_device(काष्ठा device *dev)
अणु
	पूर्णांक r;
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा pci_dev *physfn = pci_dev->physfn;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_MMCONFIG
	अटल bool pci_mcfg_reserved = false;
	/*
	 * Reserve MCFG areas in Xen on first invocation due to this being
	 * potentially called from inside of acpi_init immediately after
	 * MCFG table has been finally parsed.
	 */
	अगर (!pci_mcfg_reserved) अणु
		xen_mcfg_late();
		pci_mcfg_reserved = true;
	पूर्ण
#पूर्ण_अगर
	अगर (pci_seg_supported) अणु
		काष्ठा अणु
			काष्ठा physdev_pci_device_add add;
			uपूर्णांक32_t pxm;
		पूर्ण add_ext = अणु
			.add.seg = pci_करोमुख्य_nr(pci_dev->bus),
			.add.bus = pci_dev->bus->number,
			.add.devfn = pci_dev->devfn
		पूर्ण;
		काष्ठा physdev_pci_device_add *add = &add_ext.add;

#अगर_घोषित CONFIG_ACPI
		acpi_handle handle;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_IOV
		अगर (pci_dev->is_virtfn) अणु
			add->flags = XEN_PCI_DEV_VIRTFN;
			add->physfn.bus = physfn->bus->number;
			add->physfn.devfn = physfn->devfn;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn))
			add->flags = XEN_PCI_DEV_EXTFN;

#अगर_घोषित CONFIG_ACPI
		handle = ACPI_HANDLE(&pci_dev->dev);
#अगर_घोषित CONFIG_PCI_IOV
		अगर (!handle && pci_dev->is_virtfn)
			handle = ACPI_HANDLE(physfn->bus->bridge);
#पूर्ण_अगर
		अगर (!handle) अणु
			/*
			 * This device was not listed in the ACPI name space at
			 * all. Try to get acpi handle of parent pci bus.
			 */
			काष्ठा pci_bus *pbus;
			क्रम (pbus = pci_dev->bus; pbus; pbus = pbus->parent) अणु
				handle = acpi_pci_get_bridge_handle(pbus);
				अगर (handle)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (handle) अणु
			acpi_status status;

			करो अणु
				अचिन्हित दीर्घ दीर्घ pxm;

				status = acpi_evaluate_पूर्णांकeger(handle, "_PXM",
							       शून्य, &pxm);
				अगर (ACPI_SUCCESS(status)) अणु
					add->optarr[0] = pxm;
					add->flags |= XEN_PCI_DEV_PXM;
					अवरोध;
				पूर्ण
				status = acpi_get_parent(handle, &handle);
			पूर्ण जबतक (ACPI_SUCCESS(status));
		पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

		r = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_add, add);
		अगर (r != -ENOSYS)
			वापस r;
		pci_seg_supported = false;
	पूर्ण

	अगर (pci_करोमुख्य_nr(pci_dev->bus))
		r = -ENOSYS;
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अगर (pci_dev->is_virtfn) अणु
		काष्ठा physdev_manage_pci_ext manage_pci_ext = अणु
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_virtfn 	= 1,
			.physfn.bus	= physfn->bus->number,
			.physfn.devfn	= physfn->devfn,
		पूर्ण;

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	पूर्ण
#पूर्ण_अगर
	अन्यथा अगर (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn)) अणु
		काष्ठा physdev_manage_pci_ext manage_pci_ext = अणु
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_extfn	= 1,
		पूर्ण;

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	पूर्ण अन्यथा अणु
		काष्ठा physdev_manage_pci manage_pci = अणु
			.bus	= pci_dev->bus->number,
			.devfn	= pci_dev->devfn,
		पूर्ण;

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add,
			&manage_pci);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक xen_हटाओ_device(काष्ठा device *dev)
अणु
	पूर्णांक r;
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	अगर (pci_seg_supported) अणु
		काष्ठा physdev_pci_device device = अणु
			.seg = pci_करोमुख्य_nr(pci_dev->bus),
			.bus = pci_dev->bus->number,
			.devfn = pci_dev->devfn
		पूर्ण;

		r = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_हटाओ,
					  &device);
	पूर्ण अन्यथा अगर (pci_करोमुख्य_nr(pci_dev->bus))
		r = -ENOSYS;
	अन्यथा अणु
		काष्ठा physdev_manage_pci manage_pci = अणु
			.bus = pci_dev->bus->number,
			.devfn = pci_dev->devfn
		पूर्ण;

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_हटाओ,
					  &manage_pci);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक xen_pci_notअगरier(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;
	पूर्णांक r = 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		r = xen_add_device(dev);
		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		r = xen_हटाओ_device(dev);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
	अगर (r)
		dev_err(dev, "Failed to %s - passthrough or MSI/MSI-X might fail!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "add" :
			(action == BUS_NOTIFY_DEL_DEVICE ? "delete" : "?"));
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block device_nb = अणु
	.notअगरier_call = xen_pci_notअगरier,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_xen_pci_notअगरier(व्योम)
अणु
	अगर (!xen_initial_करोमुख्य())
		वापस 0;

	वापस bus_रेजिस्टर_notअगरier(&pci_bus_type, &device_nb);
पूर्ण

arch_initcall(रेजिस्टर_xen_pci_notअगरier);

#अगर_घोषित CONFIG_PCI_MMCONFIG
अटल पूर्णांक xen_mcfg_late(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg;
	पूर्णांक rc;

	अगर (!xen_initial_करोमुख्य())
		वापस 0;

	अगर ((pci_probe & PCI_PROBE_MMCONF) == 0)
		वापस 0;

	अगर (list_empty(&pci_mmcfg_list))
		वापस 0;

	/* Check whether they are in the right area. */
	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list) अणु
		काष्ठा physdev_pci_mmcfg_reserved r;

		r.address = cfg->address;
		r.segment = cfg->segment;
		r.start_bus = cfg->start_bus;
		r.end_bus = cfg->end_bus;
		r.flags = XEN_PCI_MMCFG_RESERVED;

		rc = HYPERVISOR_physdev_op(PHYSDEVOP_pci_mmcfg_reserved, &r);
		चयन (rc) अणु
		हाल 0:
		हाल -ENOSYS:
			जारी;

		शेष:
			pr_warn("Failed to report MMCONFIG reservation"
				" state for %s to hypervisor"
				" (%d)\n",
				cfg->name, rc);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर
