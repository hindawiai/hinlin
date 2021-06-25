<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006, Intel Corporation.
 *
 * Copyright (C) 2006-2008 Intel Corporation
 * Author: Ashok Raj <ashok.raj@पूर्णांकel.com>
 * Author: Shaohua Li <shaohua.li@पूर्णांकel.com>
 * Author: Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *
 * This file implements early detection/parsing of Remapping Devices
 * reported to OS through BIOS via DMA remapping reporting (DMAR) ACPI
 * tables.
 *
 * These routines are used by both DMA-remapping and Interrupt-remapping
 */

#घोषणा pr_fmt(fmt)     "DMAR: " fmt

#समावेश <linux/pci.h>
#समावेश <linux/dmar.h>
#समावेश <linux/iova.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/समयr.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tboot.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/iommu.h>
#समावेश <linux/numa.h>
#समावेश <linux/सीमा.स>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/iommu_table.h>
#समावेश <trace/events/पूर्णांकel_iommu.h>

#समावेश "../irq_remapping.h"

प्रकार पूर्णांक (*dmar_res_handler_t)(काष्ठा acpi_dmar_header *, व्योम *);
काष्ठा dmar_res_callback अणु
	dmar_res_handler_t	cb[ACPI_DMAR_TYPE_RESERVED];
	व्योम			*arg[ACPI_DMAR_TYPE_RESERVED];
	bool			ignore_unhandled;
	bool			prपूर्णांक_entry;
पूर्ण;

/*
 * Assumptions:
 * 1) The hotplug framework guarentees that DMAR unit will be hot-added
 *    beक्रमe IO devices managed by that unit.
 * 2) The hotplug framework guarantees that DMAR unit will be hot-हटाओd
 *    after IO devices managed by that unit.
 * 3) Hotplug events are rare.
 *
 * Locking rules क्रम DMA and पूर्णांकerrupt remapping related global data काष्ठाures:
 * 1) Use dmar_global_lock in process context
 * 2) Use RCU in पूर्णांकerrupt context
 */
DECLARE_RWSEM(dmar_global_lock);
LIST_HEAD(dmar_drhd_units);

काष्ठा acpi_table_header * __initdata dmar_tbl;
अटल पूर्णांक dmar_dev_scope_status = 1;
अटल अचिन्हित दीर्घ dmar_seq_ids[BITS_TO_LONGS(DMAR_UNITS_SUPPORTED)];

अटल पूर्णांक alloc_iommu(काष्ठा dmar_drhd_unit *drhd);
अटल व्योम मुक्त_iommu(काष्ठा पूर्णांकel_iommu *iommu);

बाह्य स्थिर काष्ठा iommu_ops पूर्णांकel_iommu_ops;

अटल व्योम dmar_रेजिस्टर_drhd_unit(काष्ठा dmar_drhd_unit *drhd)
अणु
	/*
	 * add INCLUDE_ALL at the tail, so scan the list will find it at
	 * the very end.
	 */
	अगर (drhd->include_all)
		list_add_tail_rcu(&drhd->list, &dmar_drhd_units);
	अन्यथा
		list_add_rcu(&drhd->list, &dmar_drhd_units);
पूर्ण

व्योम *dmar_alloc_dev_scope(व्योम *start, व्योम *end, पूर्णांक *cnt)
अणु
	काष्ठा acpi_dmar_device_scope *scope;

	*cnt = 0;
	जबतक (start < end) अणु
		scope = start;
		अगर (scope->entry_type == ACPI_DMAR_SCOPE_TYPE_NAMESPACE ||
		    scope->entry_type == ACPI_DMAR_SCOPE_TYPE_ENDPOINT ||
		    scope->entry_type == ACPI_DMAR_SCOPE_TYPE_BRIDGE)
			(*cnt)++;
		अन्यथा अगर (scope->entry_type != ACPI_DMAR_SCOPE_TYPE_IOAPIC &&
			scope->entry_type != ACPI_DMAR_SCOPE_TYPE_HPET) अणु
			pr_warn("Unsupported device scope\n");
		पूर्ण
		start += scope->length;
	पूर्ण
	अगर (*cnt == 0)
		वापस शून्य;

	वापस kसुस्मृति(*cnt, माप(काष्ठा dmar_dev_scope), GFP_KERNEL);
पूर्ण

व्योम dmar_मुक्त_dev_scope(काष्ठा dmar_dev_scope **devices, पूर्णांक *cnt)
अणु
	पूर्णांक i;
	काष्ठा device *पंचांगp_dev;

	अगर (*devices && *cnt) अणु
		क्रम_each_active_dev_scope(*devices, *cnt, i, पंचांगp_dev)
			put_device(पंचांगp_dev);
		kमुक्त(*devices);
	पूर्ण

	*devices = शून्य;
	*cnt = 0;
पूर्ण

/* Optimize out kzalloc()/kमुक्त() क्रम normal हालs */
अटल अक्षर dmar_pci_notअगरy_info_buf[64];

अटल काष्ठा dmar_pci_notअगरy_info *
dmar_alloc_pci_notअगरy_info(काष्ठा pci_dev *dev, अचिन्हित दीर्घ event)
अणु
	पूर्णांक level = 0;
	माप_प्रकार size;
	काष्ठा pci_dev *पंचांगp;
	काष्ठा dmar_pci_notअगरy_info *info;

	BUG_ON(dev->is_virtfn);

	/*
	 * Ignore devices that have a करोमुख्य number higher than what can
	 * be looked up in DMAR, e.g. VMD subdevices with करोमुख्य 0x10000
	 */
	अगर (pci_करोमुख्य_nr(dev->bus) > U16_MAX)
		वापस शून्य;

	/* Only generate path[] क्रम device addition event */
	अगर (event == BUS_NOTIFY_ADD_DEVICE)
		क्रम (पंचांगp = dev; पंचांगp; पंचांगp = पंचांगp->bus->self)
			level++;

	size = काष्ठा_size(info, path, level);
	अगर (size <= माप(dmar_pci_notअगरy_info_buf)) अणु
		info = (काष्ठा dmar_pci_notअगरy_info *)dmar_pci_notअगरy_info_buf;
	पूर्ण अन्यथा अणु
		info = kzalloc(size, GFP_KERNEL);
		अगर (!info) अणु
			pr_warn("Out of memory when allocating notify_info "
				"for %s.\n", pci_name(dev));
			अगर (dmar_dev_scope_status == 0)
				dmar_dev_scope_status = -ENOMEM;
			वापस शून्य;
		पूर्ण
	पूर्ण

	info->event = event;
	info->dev = dev;
	info->seg = pci_करोमुख्य_nr(dev->bus);
	info->level = level;
	अगर (event == BUS_NOTIFY_ADD_DEVICE) अणु
		क्रम (पंचांगp = dev; पंचांगp; पंचांगp = पंचांगp->bus->self) अणु
			level--;
			info->path[level].bus = पंचांगp->bus->number;
			info->path[level].device = PCI_SLOT(पंचांगp->devfn);
			info->path[level].function = PCI_FUNC(पंचांगp->devfn);
			अगर (pci_is_root_bus(पंचांगp->bus))
				info->bus = पंचांगp->bus->number;
		पूर्ण
	पूर्ण

	वापस info;
पूर्ण

अटल अंतरभूत व्योम dmar_मुक्त_pci_notअगरy_info(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	अगर ((व्योम *)info != dmar_pci_notअगरy_info_buf)
		kमुक्त(info);
पूर्ण

अटल bool dmar_match_pci_path(काष्ठा dmar_pci_notअगरy_info *info, पूर्णांक bus,
				काष्ठा acpi_dmar_pci_path *path, पूर्णांक count)
अणु
	पूर्णांक i;

	अगर (info->bus != bus)
		जाओ fallback;
	अगर (info->level != count)
		जाओ fallback;

	क्रम (i = 0; i < count; i++) अणु
		अगर (path[i].device != info->path[i].device ||
		    path[i].function != info->path[i].function)
			जाओ fallback;
	पूर्ण

	वापस true;

fallback:

	अगर (count != 1)
		वापस false;

	i = info->level - 1;
	अगर (bus              == info->path[i].bus &&
	    path[0].device   == info->path[i].device &&
	    path[0].function == info->path[i].function) अणु
		pr_info(FW_BUG "RMRR entry for device %02x:%02x.%x is broken - applying workaround\n",
			bus, path[0].device, path[0].function);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Return: > 0 अगर match found, 0 अगर no match found, < 0 अगर error happens */
पूर्णांक dmar_insert_dev_scope(काष्ठा dmar_pci_notअगरy_info *info,
			  व्योम *start, व्योम*end, u16 segment,
			  काष्ठा dmar_dev_scope *devices,
			  पूर्णांक devices_cnt)
अणु
	पूर्णांक i, level;
	काष्ठा device *पंचांगp, *dev = &info->dev->dev;
	काष्ठा acpi_dmar_device_scope *scope;
	काष्ठा acpi_dmar_pci_path *path;

	अगर (segment != info->seg)
		वापस 0;

	क्रम (; start < end; start += scope->length) अणु
		scope = start;
		अगर (scope->entry_type != ACPI_DMAR_SCOPE_TYPE_ENDPOINT &&
		    scope->entry_type != ACPI_DMAR_SCOPE_TYPE_BRIDGE)
			जारी;

		path = (काष्ठा acpi_dmar_pci_path *)(scope + 1);
		level = (scope->length - माप(*scope)) / माप(*path);
		अगर (!dmar_match_pci_path(info, scope->bus, path, level))
			जारी;

		/*
		 * We expect devices with endpoपूर्णांक scope to have normal PCI
		 * headers, and devices with bridge scope to have bridge PCI
		 * headers.  However PCI NTB devices may be listed in the
		 * DMAR table with bridge scope, even though they have a
		 * normal PCI header.  NTB devices are identअगरied by class
		 * "BRIDGE_OTHER" (0680h) - we करोn't declare a socpe mismatch
		 * क्रम this special हाल.
		 */
		अगर ((scope->entry_type == ACPI_DMAR_SCOPE_TYPE_ENDPOINT &&
		     info->dev->hdr_type != PCI_HEADER_TYPE_NORMAL) ||
		    (scope->entry_type == ACPI_DMAR_SCOPE_TYPE_BRIDGE &&
		     (info->dev->hdr_type == PCI_HEADER_TYPE_NORMAL &&
		      info->dev->class >> 16 != PCI_BASE_CLASS_BRIDGE))) अणु
			pr_warn("Device scope type does not match for %s\n",
				pci_name(info->dev));
			वापस -EINVAL;
		पूर्ण

		क्रम_each_dev_scope(devices, devices_cnt, i, पंचांगp)
			अगर (पंचांगp == शून्य) अणु
				devices[i].bus = info->dev->bus->number;
				devices[i].devfn = info->dev->devfn;
				rcu_assign_poपूर्णांकer(devices[i].dev,
						   get_device(dev));
				वापस 1;
			पूर्ण
		BUG_ON(i >= devices_cnt);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dmar_हटाओ_dev_scope(काष्ठा dmar_pci_notअगरy_info *info, u16 segment,
			  काष्ठा dmar_dev_scope *devices, पूर्णांक count)
अणु
	पूर्णांक index;
	काष्ठा device *पंचांगp;

	अगर (info->seg != segment)
		वापस 0;

	क्रम_each_active_dev_scope(devices, count, index, पंचांगp)
		अगर (पंचांगp == &info->dev->dev) अणु
			RCU_INIT_POINTER(devices[index].dev, शून्य);
			synchronize_rcu();
			put_device(पंचांगp);
			वापस 1;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmar_pci_bus_add_dev(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	पूर्णांक ret = 0;
	काष्ठा dmar_drhd_unit *dmaru;
	काष्ठा acpi_dmar_hardware_unit *drhd;

	क्रम_each_drhd_unit(dmaru) अणु
		अगर (dmaru->include_all)
			जारी;

		drhd = container_of(dmaru->hdr,
				    काष्ठा acpi_dmar_hardware_unit, header);
		ret = dmar_insert_dev_scope(info, (व्योम *)(drhd + 1),
				((व्योम *)drhd) + drhd->header.length,
				dmaru->segment,
				dmaru->devices, dmaru->devices_cnt);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (ret >= 0)
		ret = dmar_iommu_notअगरy_scope_dev(info);
	अगर (ret < 0 && dmar_dev_scope_status == 0)
		dmar_dev_scope_status = ret;

	अगर (ret >= 0)
		पूर्णांकel_irq_remap_add_device(info);

	वापस ret;
पूर्ण

अटल व्योम  dmar_pci_bus_del_dev(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	काष्ठा dmar_drhd_unit *dmaru;

	क्रम_each_drhd_unit(dmaru)
		अगर (dmar_हटाओ_dev_scope(info, dmaru->segment,
			dmaru->devices, dmaru->devices_cnt))
			अवरोध;
	dmar_iommu_notअगरy_scope_dev(info);
पूर्ण

अटल अंतरभूत व्योम vf_inherit_msi_करोमुख्य(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *physfn = pci_physfn(pdev);

	dev_set_msi_करोमुख्य(&pdev->dev, dev_get_msi_करोमुख्य(&physfn->dev));
पूर्ण

अटल पूर्णांक dmar_pci_bus_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(data);
	काष्ठा dmar_pci_notअगरy_info *info;

	/* Only care about add/हटाओ events क्रम physical functions.
	 * For VFs we actually करो the lookup based on the corresponding
	 * PF in device_to_iommu() anyway. */
	अगर (pdev->is_virtfn) अणु
		/*
		 * Ensure that the VF device inherits the irq करोमुख्य of the
		 * PF device. Ideally the device would inherit the करोमुख्य
		 * from the bus, but DMAR can have multiple units per bus
		 * which makes this impossible. The VF 'bus' could inherit
		 * from the PF device, but that's yet another x86'sism to
		 * inflict on everybody अन्यथा.
		 */
		अगर (action == BUS_NOTIFY_ADD_DEVICE)
			vf_inherit_msi_करोमुख्य(pdev);
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (action != BUS_NOTIFY_ADD_DEVICE &&
	    action != BUS_NOTIFY_REMOVED_DEVICE)
		वापस NOTIFY_DONE;

	info = dmar_alloc_pci_notअगरy_info(pdev, action);
	अगर (!info)
		वापस NOTIFY_DONE;

	करोwn_ग_लिखो(&dmar_global_lock);
	अगर (action == BUS_NOTIFY_ADD_DEVICE)
		dmar_pci_bus_add_dev(info);
	अन्यथा अगर (action == BUS_NOTIFY_REMOVED_DEVICE)
		dmar_pci_bus_del_dev(info);
	up_ग_लिखो(&dmar_global_lock);

	dmar_मुक्त_pci_notअगरy_info(info);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dmar_pci_bus_nb = अणु
	.notअगरier_call = dmar_pci_bus_notअगरier,
	.priority = पूर्णांक_न्यून,
पूर्ण;

अटल काष्ठा dmar_drhd_unit *
dmar_find_dmaru(काष्ठा acpi_dmar_hardware_unit *drhd)
अणु
	काष्ठा dmar_drhd_unit *dmaru;

	list_क्रम_each_entry_rcu(dmaru, &dmar_drhd_units, list,
				dmar_rcu_check())
		अगर (dmaru->segment == drhd->segment &&
		    dmaru->reg_base_addr == drhd->address)
			वापस dmaru;

	वापस शून्य;
पूर्ण

/*
 * dmar_parse_one_drhd - parses exactly one DMA remapping hardware definition
 * काष्ठाure which uniquely represent one DMA remapping hardware unit
 * present in the platक्रमm
 */
अटल पूर्णांक dmar_parse_one_drhd(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	काष्ठा acpi_dmar_hardware_unit *drhd;
	काष्ठा dmar_drhd_unit *dmaru;
	पूर्णांक ret;

	drhd = (काष्ठा acpi_dmar_hardware_unit *)header;
	dmaru = dmar_find_dmaru(drhd);
	अगर (dmaru)
		जाओ out;

	dmaru = kzalloc(माप(*dmaru) + header->length, GFP_KERNEL);
	अगर (!dmaru)
		वापस -ENOMEM;

	/*
	 * If header is allocated from slab by ACPI _DSM method, we need to
	 * copy the content because the memory buffer will be मुक्तd on वापस.
	 */
	dmaru->hdr = (व्योम *)(dmaru + 1);
	स_नकल(dmaru->hdr, header, header->length);
	dmaru->reg_base_addr = drhd->address;
	dmaru->segment = drhd->segment;
	dmaru->include_all = drhd->flags & 0x1; /* BIT0: INCLUDE_ALL */
	dmaru->devices = dmar_alloc_dev_scope((व्योम *)(drhd + 1),
					      ((व्योम *)drhd) + drhd->header.length,
					      &dmaru->devices_cnt);
	अगर (dmaru->devices_cnt && dmaru->devices == शून्य) अणु
		kमुक्त(dmaru);
		वापस -ENOMEM;
	पूर्ण

	ret = alloc_iommu(dmaru);
	अगर (ret) अणु
		dmar_मुक्त_dev_scope(&dmaru->devices,
				    &dmaru->devices_cnt);
		kमुक्त(dmaru);
		वापस ret;
	पूर्ण
	dmar_रेजिस्टर_drhd_unit(dmaru);

out:
	अगर (arg)
		(*(पूर्णांक *)arg)++;

	वापस 0;
पूर्ण

अटल व्योम dmar_मुक्त_drhd(काष्ठा dmar_drhd_unit *dmaru)
अणु
	अगर (dmaru->devices && dmaru->devices_cnt)
		dmar_मुक्त_dev_scope(&dmaru->devices, &dmaru->devices_cnt);
	अगर (dmaru->iommu)
		मुक्त_iommu(dmaru->iommu);
	kमुक्त(dmaru);
पूर्ण

अटल पूर्णांक __init dmar_parse_one_andd(काष्ठा acpi_dmar_header *header,
				      व्योम *arg)
अणु
	काष्ठा acpi_dmar_andd *andd = (व्योम *)header;

	/* Check क्रम NUL termination within the designated length */
	अगर (strnlen(andd->device_name, header->length - 8) == header->length - 8) अणु
		pr_warn(FW_BUG
			   "Your BIOS is broken; ANDD object name is not NUL-terminated\n"
			   "BIOS vendor: %s; Ver: %s; Product Version: %s\n",
			   dmi_get_प्रणाली_info(DMI_BIOS_VENDOR),
			   dmi_get_प्रणाली_info(DMI_BIOS_VERSION),
			   dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION));
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
		वापस -EINVAL;
	पूर्ण
	pr_info("ANDD device: %x name: %s\n", andd->device_number,
		andd->device_name);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_NUMA
अटल पूर्णांक dmar_parse_one_rhsa(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	काष्ठा acpi_dmar_rhsa *rhsa;
	काष्ठा dmar_drhd_unit *drhd;

	rhsa = (काष्ठा acpi_dmar_rhsa *)header;
	क्रम_each_drhd_unit(drhd) अणु
		अगर (drhd->reg_base_addr == rhsa->base_address) अणु
			पूर्णांक node = pxm_to_node(rhsa->proximity_करोमुख्य);

			अगर (!node_online(node))
				node = NUMA_NO_NODE;
			drhd->iommu->node = node;
			वापस 0;
		पूर्ण
	पूर्ण
	pr_warn(FW_BUG
		"Your BIOS is broken; RHSA refers to non-existent DMAR unit at %llx\n"
		"BIOS vendor: %s; Ver: %s; Product Version: %s\n",
		rhsa->base_address,
		dmi_get_प्रणाली_info(DMI_BIOS_VENDOR),
		dmi_get_प्रणाली_info(DMI_BIOS_VERSION),
		dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION));
	add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा	dmar_parse_one_rhsa		dmar_res_noop
#पूर्ण_अगर

अटल व्योम
dmar_table_prपूर्णांक_dmar_entry(काष्ठा acpi_dmar_header *header)
अणु
	काष्ठा acpi_dmar_hardware_unit *drhd;
	काष्ठा acpi_dmar_reserved_memory *rmrr;
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा acpi_dmar_rhsa *rhsa;
	काष्ठा acpi_dmar_satc *satc;

	चयन (header->type) अणु
	हाल ACPI_DMAR_TYPE_HARDWARE_UNIT:
		drhd = container_of(header, काष्ठा acpi_dmar_hardware_unit,
				    header);
		pr_info("DRHD base: %#016Lx flags: %#x\n",
			(अचिन्हित दीर्घ दीर्घ)drhd->address, drhd->flags);
		अवरोध;
	हाल ACPI_DMAR_TYPE_RESERVED_MEMORY:
		rmrr = container_of(header, काष्ठा acpi_dmar_reserved_memory,
				    header);
		pr_info("RMRR base: %#016Lx end: %#016Lx\n",
			(अचिन्हित दीर्घ दीर्घ)rmrr->base_address,
			(अचिन्हित दीर्घ दीर्घ)rmrr->end_address);
		अवरोध;
	हाल ACPI_DMAR_TYPE_ROOT_ATS:
		atsr = container_of(header, काष्ठा acpi_dmar_atsr, header);
		pr_info("ATSR flags: %#x\n", atsr->flags);
		अवरोध;
	हाल ACPI_DMAR_TYPE_HARDWARE_AFFINITY:
		rhsa = container_of(header, काष्ठा acpi_dmar_rhsa, header);
		pr_info("RHSA base: %#016Lx proximity domain: %#x\n",
		       (अचिन्हित दीर्घ दीर्घ)rhsa->base_address,
		       rhsa->proximity_करोमुख्य);
		अवरोध;
	हाल ACPI_DMAR_TYPE_NAMESPACE:
		/* We करोn't prपूर्णांक this here because we need to sanity-check
		   it first. So prपूर्णांक it in dmar_parse_one_andd() instead. */
		अवरोध;
	हाल ACPI_DMAR_TYPE_SATC:
		satc = container_of(header, काष्ठा acpi_dmar_satc, header);
		pr_info("SATC flags: 0x%x\n", satc->flags);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * dmar_table_detect - checks to see अगर the platक्रमm supports DMAR devices
 */
अटल पूर्णांक __init dmar_table_detect(व्योम)
अणु
	acpi_status status = AE_OK;

	/* अगर we could find DMAR table, then there are DMAR devices */
	status = acpi_get_table(ACPI_SIG_DMAR, 0, &dmar_tbl);

	अगर (ACPI_SUCCESS(status) && !dmar_tbl) अणु
		pr_warn("Unable to map DMAR\n");
		status = AE_NOT_FOUND;
	पूर्ण

	वापस ACPI_SUCCESS(status) ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक dmar_walk_remapping_entries(काष्ठा acpi_dmar_header *start,
				       माप_प्रकार len, काष्ठा dmar_res_callback *cb)
अणु
	काष्ठा acpi_dmar_header *iter, *next;
	काष्ठा acpi_dmar_header *end = ((व्योम *)start) + len;

	क्रम (iter = start; iter < end; iter = next) अणु
		next = (व्योम *)iter + iter->length;
		अगर (iter->length == 0) अणु
			/* Aव्योम looping क्रमever on bad ACPI tables */
			pr_debug(FW_BUG "Invalid 0-length structure\n");
			अवरोध;
		पूर्ण अन्यथा अगर (next > end) अणु
			/* Aव्योम passing table end */
			pr_warn(FW_BUG "Record passes table end\n");
			वापस -EINVAL;
		पूर्ण

		अगर (cb->prपूर्णांक_entry)
			dmar_table_prपूर्णांक_dmar_entry(iter);

		अगर (iter->type >= ACPI_DMAR_TYPE_RESERVED) अणु
			/* जारी क्रम क्रमward compatibility */
			pr_debug("Unknown DMAR structure type %d\n",
				 iter->type);
		पूर्ण अन्यथा अगर (cb->cb[iter->type]) अणु
			पूर्णांक ret;

			ret = cb->cb[iter->type](iter, cb->arg[iter->type]);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (!cb->ignore_unhandled) अणु
			pr_warn("No handler for DMAR structure type %d\n",
				iter->type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dmar_walk_dmar_table(काष्ठा acpi_table_dmar *dmar,
				       काष्ठा dmar_res_callback *cb)
अणु
	वापस dmar_walk_remapping_entries((व्योम *)(dmar + 1),
			dmar->header.length - माप(*dmar), cb);
पूर्ण

/**
 * parse_dmar_table - parses the DMA reporting table
 */
अटल पूर्णांक __init
parse_dmar_table(व्योम)
अणु
	काष्ठा acpi_table_dmar *dmar;
	पूर्णांक drhd_count = 0;
	पूर्णांक ret;
	काष्ठा dmar_res_callback cb = अणु
		.prपूर्णांक_entry = true,
		.ignore_unhandled = true,
		.arg[ACPI_DMAR_TYPE_HARDWARE_UNIT] = &drhd_count,
		.cb[ACPI_DMAR_TYPE_HARDWARE_UNIT] = &dmar_parse_one_drhd,
		.cb[ACPI_DMAR_TYPE_RESERVED_MEMORY] = &dmar_parse_one_rmrr,
		.cb[ACPI_DMAR_TYPE_ROOT_ATS] = &dmar_parse_one_atsr,
		.cb[ACPI_DMAR_TYPE_HARDWARE_AFFINITY] = &dmar_parse_one_rhsa,
		.cb[ACPI_DMAR_TYPE_NAMESPACE] = &dmar_parse_one_andd,
		.cb[ACPI_DMAR_TYPE_SATC] = &dmar_parse_one_satc,
	पूर्ण;

	/*
	 * Do it again, earlier dmar_tbl mapping could be mapped with
	 * fixed map.
	 */
	dmar_table_detect();

	/*
	 * ACPI tables may not be DMA रक्षित by tboot, so use DMAR copy
	 * SINIT saved in SinitMleData in TXT heap (which is DMA रक्षित)
	 */
	dmar_tbl = tboot_get_dmar_table(dmar_tbl);

	dmar = (काष्ठा acpi_table_dmar *)dmar_tbl;
	अगर (!dmar)
		वापस -ENODEV;

	अगर (dmar->width < PAGE_SHIFT - 1) अणु
		pr_warn("Invalid DMAR haw\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("Host address width %d\n", dmar->width + 1);
	ret = dmar_walk_dmar_table(dmar, &cb);
	अगर (ret == 0 && drhd_count == 0)
		pr_warn(FW_BUG "No DRHD structure found in DMAR table\n");

	वापस ret;
पूर्ण

अटल पूर्णांक dmar_pci_device_match(काष्ठा dmar_dev_scope devices[],
				 पूर्णांक cnt, काष्ठा pci_dev *dev)
अणु
	पूर्णांक index;
	काष्ठा device *पंचांगp;

	जबतक (dev) अणु
		क्रम_each_active_dev_scope(devices, cnt, index, पंचांगp)
			अगर (dev_is_pci(पंचांगp) && dev == to_pci_dev(पंचांगp))
				वापस 1;

		/* Check our parent */
		dev = dev->bus->self;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा dmar_drhd_unit *
dmar_find_matched_drhd_unit(काष्ठा pci_dev *dev)
अणु
	काष्ठा dmar_drhd_unit *dmaru;
	काष्ठा acpi_dmar_hardware_unit *drhd;

	dev = pci_physfn(dev);

	rcu_पढ़ो_lock();
	क्रम_each_drhd_unit(dmaru) अणु
		drhd = container_of(dmaru->hdr,
				    काष्ठा acpi_dmar_hardware_unit,
				    header);

		अगर (dmaru->include_all &&
		    drhd->segment == pci_करोमुख्य_nr(dev->bus))
			जाओ out;

		अगर (dmar_pci_device_match(dmaru->devices,
					  dmaru->devices_cnt, dev))
			जाओ out;
	पूर्ण
	dmaru = शून्य;
out:
	rcu_पढ़ो_unlock();

	वापस dmaru;
पूर्ण

अटल व्योम __init dmar_acpi_insert_dev_scope(u8 device_number,
					      काष्ठा acpi_device *adev)
अणु
	काष्ठा dmar_drhd_unit *dmaru;
	काष्ठा acpi_dmar_hardware_unit *drhd;
	काष्ठा acpi_dmar_device_scope *scope;
	काष्ठा device *पंचांगp;
	पूर्णांक i;
	काष्ठा acpi_dmar_pci_path *path;

	क्रम_each_drhd_unit(dmaru) अणु
		drhd = container_of(dmaru->hdr,
				    काष्ठा acpi_dmar_hardware_unit,
				    header);

		क्रम (scope = (व्योम *)(drhd + 1);
		     (अचिन्हित दीर्घ)scope < ((अचिन्हित दीर्घ)drhd) + drhd->header.length;
		     scope = ((व्योम *)scope) + scope->length) अणु
			अगर (scope->entry_type != ACPI_DMAR_SCOPE_TYPE_NAMESPACE)
				जारी;
			अगर (scope->क्रमागतeration_id != device_number)
				जारी;

			path = (व्योम *)(scope + 1);
			pr_info("ACPI device \"%s\" under DMAR at %llx as %02x:%02x.%d\n",
				dev_name(&adev->dev), dmaru->reg_base_addr,
				scope->bus, path->device, path->function);
			क्रम_each_dev_scope(dmaru->devices, dmaru->devices_cnt, i, पंचांगp)
				अगर (पंचांगp == शून्य) अणु
					dmaru->devices[i].bus = scope->bus;
					dmaru->devices[i].devfn = PCI_DEVFN(path->device,
									    path->function);
					rcu_assign_poपूर्णांकer(dmaru->devices[i].dev,
							   get_device(&adev->dev));
					वापस;
				पूर्ण
			BUG_ON(i >= dmaru->devices_cnt);
		पूर्ण
	पूर्ण
	pr_warn("No IOMMU scope found for ANDD enumeration ID %d (%s)\n",
		device_number, dev_name(&adev->dev));
पूर्ण

अटल पूर्णांक __init dmar_acpi_dev_scope_init(व्योम)
अणु
	काष्ठा acpi_dmar_andd *andd;

	अगर (dmar_tbl == शून्य)
		वापस -ENODEV;

	क्रम (andd = (व्योम *)dmar_tbl + माप(काष्ठा acpi_table_dmar);
	     ((अचिन्हित दीर्घ)andd) < ((अचिन्हित दीर्घ)dmar_tbl) + dmar_tbl->length;
	     andd = ((व्योम *)andd) + andd->header.length) अणु
		अगर (andd->header.type == ACPI_DMAR_TYPE_NAMESPACE) अणु
			acpi_handle h;
			काष्ठा acpi_device *adev;

			अगर (!ACPI_SUCCESS(acpi_get_handle(ACPI_ROOT_OBJECT,
							  andd->device_name,
							  &h))) अणु
				pr_err("Failed to find handle for ACPI object %s\n",
				       andd->device_name);
				जारी;
			पूर्ण
			अगर (acpi_bus_get_device(h, &adev)) अणु
				pr_err("Failed to get device for ACPI object %s\n",
				       andd->device_name);
				जारी;
			पूर्ण
			dmar_acpi_insert_dev_scope(andd->device_number, adev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init dmar_dev_scope_init(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा dmar_pci_notअगरy_info *info;

	अगर (dmar_dev_scope_status != 1)
		वापस dmar_dev_scope_status;

	अगर (list_empty(&dmar_drhd_units)) अणु
		dmar_dev_scope_status = -ENODEV;
	पूर्ण अन्यथा अणु
		dmar_dev_scope_status = 0;

		dmar_acpi_dev_scope_init();

		क्रम_each_pci_dev(dev) अणु
			अगर (dev->is_virtfn)
				जारी;

			info = dmar_alloc_pci_notअगरy_info(dev,
					BUS_NOTIFY_ADD_DEVICE);
			अगर (!info) अणु
				वापस dmar_dev_scope_status;
			पूर्ण अन्यथा अणु
				dmar_pci_bus_add_dev(info);
				dmar_मुक्त_pci_notअगरy_info(info);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस dmar_dev_scope_status;
पूर्ण

व्योम __init dmar_रेजिस्टर_bus_notअगरier(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&pci_bus_type, &dmar_pci_bus_nb);
पूर्ण


पूर्णांक __init dmar_table_init(व्योम)
अणु
	अटल पूर्णांक dmar_table_initialized;
	पूर्णांक ret;

	अगर (dmar_table_initialized == 0) अणु
		ret = parse_dmar_table();
		अगर (ret < 0) अणु
			अगर (ret != -ENODEV)
				pr_info("Parse DMAR table failure.\n");
		पूर्ण अन्यथा  अगर (list_empty(&dmar_drhd_units)) अणु
			pr_info("No DMAR devices found\n");
			ret = -ENODEV;
		पूर्ण

		अगर (ret < 0)
			dmar_table_initialized = ret;
		अन्यथा
			dmar_table_initialized = 1;
	पूर्ण

	वापस dmar_table_initialized < 0 ? dmar_table_initialized : 0;
पूर्ण

अटल व्योम warn_invalid_dmar(u64 addr, स्थिर अक्षर *message)
अणु
	pr_warn_once(FW_BUG
		"Your BIOS is broken; DMAR reported at address %llx%s!\n"
		"BIOS vendor: %s; Ver: %s; Product Version: %s\n",
		addr, message,
		dmi_get_प्रणाली_info(DMI_BIOS_VENDOR),
		dmi_get_प्रणाली_info(DMI_BIOS_VERSION),
		dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION));
	add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
पूर्ण

अटल पूर्णांक __ref
dmar_validate_one_drhd(काष्ठा acpi_dmar_header *entry, व्योम *arg)
अणु
	काष्ठा acpi_dmar_hardware_unit *drhd;
	व्योम __iomem *addr;
	u64 cap, ecap;

	drhd = (व्योम *)entry;
	अगर (!drhd->address) अणु
		warn_invalid_dmar(0, "");
		वापस -EINVAL;
	पूर्ण

	अगर (arg)
		addr = ioremap(drhd->address, VTD_PAGE_SIZE);
	अन्यथा
		addr = early_ioremap(drhd->address, VTD_PAGE_SIZE);
	अगर (!addr) अणु
		pr_warn("Can't validate DRHD address: %llx\n", drhd->address);
		वापस -EINVAL;
	पूर्ण

	cap = dmar_पढ़ोq(addr + DMAR_CAP_REG);
	ecap = dmar_पढ़ोq(addr + DMAR_ECAP_REG);

	अगर (arg)
		iounmap(addr);
	अन्यथा
		early_iounmap(addr, VTD_PAGE_SIZE);

	अगर (cap == (uपूर्णांक64_t)-1 && ecap == (uपूर्णांक64_t)-1) अणु
		warn_invalid_dmar(drhd->address, " returns all ones");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init detect_पूर्णांकel_iommu(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा dmar_res_callback validate_drhd_cb = अणु
		.cb[ACPI_DMAR_TYPE_HARDWARE_UNIT] = &dmar_validate_one_drhd,
		.ignore_unhandled = true,
	पूर्ण;

	करोwn_ग_लिखो(&dmar_global_lock);
	ret = dmar_table_detect();
	अगर (!ret)
		ret = dmar_walk_dmar_table((काष्ठा acpi_table_dmar *)dmar_tbl,
					   &validate_drhd_cb);
	अगर (!ret && !no_iommu && !iommu_detected &&
	    (!dmar_disabled || dmar_platक्रमm_optin())) अणु
		iommu_detected = 1;
		/* Make sure ACS will be enabled */
		pci_request_acs();
	पूर्ण

#अगर_घोषित CONFIG_X86
	अगर (!ret) अणु
		x86_init.iommu.iommu_init = पूर्णांकel_iommu_init;
		x86_platक्रमm.iommu_shutकरोwn = पूर्णांकel_iommu_shutकरोwn;
	पूर्ण

#पूर्ण_अगर

	अगर (dmar_tbl) अणु
		acpi_put_table(dmar_tbl);
		dmar_tbl = शून्य;
	पूर्ण
	up_ग_लिखो(&dmar_global_lock);

	वापस ret ? ret : 1;
पूर्ण

अटल व्योम unmap_iommu(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	iounmap(iommu->reg);
	release_mem_region(iommu->reg_phys, iommu->reg_size);
पूर्ण

/**
 * map_iommu: map the iommu's रेजिस्टरs
 * @iommu: the iommu to map
 * @phys_addr: the physical address of the base resgister
 *
 * Memory map the iommu's रेजिस्टरs.  Start w/ a single page, and
 * possibly expand अगर that turns out to be insufficent.
 */
अटल पूर्णांक map_iommu(काष्ठा पूर्णांकel_iommu *iommu, u64 phys_addr)
अणु
	पूर्णांक map_size, err=0;

	iommu->reg_phys = phys_addr;
	iommu->reg_size = VTD_PAGE_SIZE;

	अगर (!request_mem_region(iommu->reg_phys, iommu->reg_size, iommu->name)) अणु
		pr_err("Can't reserve memory\n");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	iommu->reg = ioremap(iommu->reg_phys, iommu->reg_size);
	अगर (!iommu->reg) अणु
		pr_err("Can't map the region\n");
		err = -ENOMEM;
		जाओ release;
	पूर्ण

	iommu->cap = dmar_पढ़ोq(iommu->reg + DMAR_CAP_REG);
	iommu->ecap = dmar_पढ़ोq(iommu->reg + DMAR_ECAP_REG);

	अगर (iommu->cap == (uपूर्णांक64_t)-1 && iommu->ecap == (uपूर्णांक64_t)-1) अणु
		err = -EINVAL;
		warn_invalid_dmar(phys_addr, " returns all ones");
		जाओ unmap;
	पूर्ण
	अगर (ecap_vcs(iommu->ecap))
		iommu->vccap = dmar_पढ़ोq(iommu->reg + DMAR_VCCAP_REG);

	/* the रेजिस्टरs might be more than one page */
	map_size = max_t(पूर्णांक, ecap_max_iotlb_offset(iommu->ecap),
			 cap_max_fault_reg_offset(iommu->cap));
	map_size = VTD_PAGE_ALIGN(map_size);
	अगर (map_size > iommu->reg_size) अणु
		iounmap(iommu->reg);
		release_mem_region(iommu->reg_phys, iommu->reg_size);
		iommu->reg_size = map_size;
		अगर (!request_mem_region(iommu->reg_phys, iommu->reg_size,
					iommu->name)) अणु
			pr_err("Can't reserve memory\n");
			err = -EBUSY;
			जाओ out;
		पूर्ण
		iommu->reg = ioremap(iommu->reg_phys, iommu->reg_size);
		अगर (!iommu->reg) अणु
			pr_err("Can't map the region\n");
			err = -ENOMEM;
			जाओ release;
		पूर्ण
	पूर्ण
	err = 0;
	जाओ out;

unmap:
	iounmap(iommu->reg);
release:
	release_mem_region(iommu->reg_phys, iommu->reg_size);
out:
	वापस err;
पूर्ण

अटल पूर्णांक dmar_alloc_seq_id(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	iommu->seq_id = find_first_zero_bit(dmar_seq_ids,
					    DMAR_UNITS_SUPPORTED);
	अगर (iommu->seq_id >= DMAR_UNITS_SUPPORTED) अणु
		iommu->seq_id = -1;
	पूर्ण अन्यथा अणु
		set_bit(iommu->seq_id, dmar_seq_ids);
		प्र_लिखो(iommu->name, "dmar%d", iommu->seq_id);
	पूर्ण

	वापस iommu->seq_id;
पूर्ण

अटल व्योम dmar_मुक्त_seq_id(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अगर (iommu->seq_id >= 0) अणु
		clear_bit(iommu->seq_id, dmar_seq_ids);
		iommu->seq_id = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_iommu(काष्ठा dmar_drhd_unit *drhd)
अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	u32 ver, sts;
	पूर्णांक agaw = -1;
	पूर्णांक msagaw = -1;
	पूर्णांक err;

	अगर (!drhd->reg_base_addr) अणु
		warn_invalid_dmar(0, "");
		वापस -EINVAL;
	पूर्ण

	iommu = kzalloc(माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस -ENOMEM;

	अगर (dmar_alloc_seq_id(iommu) < 0) अणु
		pr_err("Failed to allocate seq_id\n");
		err = -ENOSPC;
		जाओ error;
	पूर्ण

	err = map_iommu(iommu, drhd->reg_base_addr);
	अगर (err) अणु
		pr_err("Failed to map %s\n", iommu->name);
		जाओ error_मुक्त_seq_id;
	पूर्ण

	err = -EINVAL;
	अगर (cap_sagaw(iommu->cap) == 0) अणु
		pr_info("%s: No supported address widths. Not attempting DMA translation.\n",
			iommu->name);
		drhd->ignored = 1;
	पूर्ण

	अगर (!drhd->ignored) अणु
		agaw = iommu_calculate_agaw(iommu);
		अगर (agaw < 0) अणु
			pr_err("Cannot get a valid agaw for iommu (seq_id = %d)\n",
			       iommu->seq_id);
			drhd->ignored = 1;
		पूर्ण
	पूर्ण
	अगर (!drhd->ignored) अणु
		msagaw = iommu_calculate_max_sagaw(iommu);
		अगर (msagaw < 0) अणु
			pr_err("Cannot get a valid max agaw for iommu (seq_id = %d)\n",
			       iommu->seq_id);
			drhd->ignored = 1;
			agaw = -1;
		पूर्ण
	पूर्ण
	iommu->agaw = agaw;
	iommu->msagaw = msagaw;
	iommu->segment = drhd->segment;

	iommu->node = NUMA_NO_NODE;

	ver = पढ़ोl(iommu->reg + DMAR_VER_REG);
	pr_info("%s: reg_base_addr %llx ver %d:%d cap %llx ecap %llx\n",
		iommu->name,
		(अचिन्हित दीर्घ दीर्घ)drhd->reg_base_addr,
		DMAR_VER_MAJOR(ver), DMAR_VER_MINOR(ver),
		(अचिन्हित दीर्घ दीर्घ)iommu->cap,
		(अचिन्हित दीर्घ दीर्घ)iommu->ecap);

	/* Reflect status in gcmd */
	sts = पढ़ोl(iommu->reg + DMAR_GSTS_REG);
	अगर (sts & DMA_GSTS_IRES)
		iommu->gcmd |= DMA_GCMD_IRE;
	अगर (sts & DMA_GSTS_TES)
		iommu->gcmd |= DMA_GCMD_TE;
	अगर (sts & DMA_GSTS_QIES)
		iommu->gcmd |= DMA_GCMD_QIE;

	raw_spin_lock_init(&iommu->रेजिस्टर_lock);

	/*
	 * This is only क्रम hotplug; at boot समय पूर्णांकel_iommu_enabled won't
	 * be set yet. When पूर्णांकel_iommu_init() runs, it रेजिस्टरs the units
	 * present at boot समय, then sets पूर्णांकel_iommu_enabled.
	 */
	अगर (पूर्णांकel_iommu_enabled && !drhd->ignored) अणु
		err = iommu_device_sysfs_add(&iommu->iommu, शून्य,
					     पूर्णांकel_iommu_groups,
					     "%s", iommu->name);
		अगर (err)
			जाओ err_unmap;

		err = iommu_device_रेजिस्टर(&iommu->iommu, &पूर्णांकel_iommu_ops, शून्य);
		अगर (err)
			जाओ err_sysfs;
	पूर्ण

	drhd->iommu = iommu;
	iommu->drhd = drhd;

	वापस 0;

err_sysfs:
	iommu_device_sysfs_हटाओ(&iommu->iommu);
err_unmap:
	unmap_iommu(iommu);
error_मुक्त_seq_id:
	dmar_मुक्त_seq_id(iommu);
error:
	kमुक्त(iommu);
	वापस err;
पूर्ण

अटल व्योम मुक्त_iommu(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अगर (पूर्णांकel_iommu_enabled && !iommu->drhd->ignored) अणु
		iommu_device_unरेजिस्टर(&iommu->iommu);
		iommu_device_sysfs_हटाओ(&iommu->iommu);
	पूर्ण

	अगर (iommu->irq) अणु
		अगर (iommu->pr_irq) अणु
			मुक्त_irq(iommu->pr_irq, iommu);
			dmar_मुक्त_hwirq(iommu->pr_irq);
			iommu->pr_irq = 0;
		पूर्ण
		मुक्त_irq(iommu->irq, iommu);
		dmar_मुक्त_hwirq(iommu->irq);
		iommu->irq = 0;
	पूर्ण

	अगर (iommu->qi) अणु
		मुक्त_page((अचिन्हित दीर्घ)iommu->qi->desc);
		kमुक्त(iommu->qi->desc_status);
		kमुक्त(iommu->qi);
	पूर्ण

	अगर (iommu->reg)
		unmap_iommu(iommu);

	dmar_मुक्त_seq_id(iommu);
	kमुक्त(iommu);
पूर्ण

/*
 * Reclaim all the submitted descriptors which have completed its work.
 */
अटल अंतरभूत व्योम reclaim_मुक्त_desc(काष्ठा q_inval *qi)
अणु
	जबतक (qi->desc_status[qi->मुक्त_tail] == QI_DONE ||
	       qi->desc_status[qi->मुक्त_tail] == QI_ABORT) अणु
		qi->desc_status[qi->मुक्त_tail] = QI_FREE;
		qi->मुक्त_tail = (qi->मुक्त_tail + 1) % QI_LENGTH;
		qi->मुक्त_cnt++;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *qi_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल QI_CC_TYPE:
		वापस "Context-cache Invalidation";
	हाल QI_IOTLB_TYPE:
		वापस "IOTLB Invalidation";
	हाल QI_DIOTLB_TYPE:
		वापस "Device-TLB Invalidation";
	हाल QI_IEC_TYPE:
		वापस "Interrupt Entry Cache Invalidation";
	हाल QI_IWD_TYPE:
		वापस "Invalidation Wait";
	हाल QI_EIOTLB_TYPE:
		वापस "PASID-based IOTLB Invalidation";
	हाल QI_PC_TYPE:
		वापस "PASID-cache Invalidation";
	हाल QI_DEIOTLB_TYPE:
		वापस "PASID-based Device-TLB Invalidation";
	हाल QI_PGRP_RESP_TYPE:
		वापस "Page Group Response";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम qi_dump_fault(काष्ठा पूर्णांकel_iommu *iommu, u32 fault)
अणु
	अचिन्हित पूर्णांक head = dmar_पढ़ोl(iommu->reg + DMAR_IQH_REG);
	u64 iqe_err = dmar_पढ़ोq(iommu->reg + DMAR_IQER_REG);
	काष्ठा qi_desc *desc = iommu->qi->desc + head;

	अगर (fault & DMA_FSTS_IQE)
		pr_err("VT-d detected Invalidation Queue Error: Reason %llx",
		       DMAR_IQER_REG_IQEI(iqe_err));
	अगर (fault & DMA_FSTS_ITE)
		pr_err("VT-d detected Invalidation Time-out Error: SID %llx",
		       DMAR_IQER_REG_ITESID(iqe_err));
	अगर (fault & DMA_FSTS_ICE)
		pr_err("VT-d detected Invalidation Completion Error: SID %llx",
		       DMAR_IQER_REG_ICESID(iqe_err));

	pr_err("QI HEAD: %s qw0 = 0x%llx, qw1 = 0x%llx\n",
	       qi_type_string(desc->qw0 & 0xf),
	       (अचिन्हित दीर्घ दीर्घ)desc->qw0,
	       (अचिन्हित दीर्घ दीर्घ)desc->qw1);

	head = ((head >> qi_shअगरt(iommu)) + QI_LENGTH - 1) % QI_LENGTH;
	head <<= qi_shअगरt(iommu);
	desc = iommu->qi->desc + head;

	pr_err("QI PRIOR: %s qw0 = 0x%llx, qw1 = 0x%llx\n",
	       qi_type_string(desc->qw0 & 0xf),
	       (अचिन्हित दीर्घ दीर्घ)desc->qw0,
	       (अचिन्हित दीर्घ दीर्घ)desc->qw1);
पूर्ण

अटल पूर्णांक qi_check_fault(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक index, पूर्णांक रुको_index)
अणु
	u32 fault;
	पूर्णांक head, tail;
	काष्ठा q_inval *qi = iommu->qi;
	पूर्णांक shअगरt = qi_shअगरt(iommu);

	अगर (qi->desc_status[रुको_index] == QI_ABORT)
		वापस -EAGAIN;

	fault = पढ़ोl(iommu->reg + DMAR_FSTS_REG);
	अगर (fault & (DMA_FSTS_IQE | DMA_FSTS_ITE | DMA_FSTS_ICE))
		qi_dump_fault(iommu, fault);

	/*
	 * If IQE happens, the head poपूर्णांकs to the descriptor associated
	 * with the error. No new descriptors are fetched until the IQE
	 * is cleared.
	 */
	अगर (fault & DMA_FSTS_IQE) अणु
		head = पढ़ोl(iommu->reg + DMAR_IQH_REG);
		अगर ((head >> shअगरt) == index) अणु
			काष्ठा qi_desc *desc = qi->desc + head;

			/*
			 * desc->qw2 and desc->qw3 are either reserved or
			 * used by software as निजी data. We won't prपूर्णांक
			 * out these two qw's क्रम security consideration.
			 */
			स_नकल(desc, qi->desc + (रुको_index << shअगरt),
			       1 << shअगरt);
			ग_लिखोl(DMA_FSTS_IQE, iommu->reg + DMAR_FSTS_REG);
			pr_info("Invalidation Queue Error (IQE) cleared\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * If ITE happens, all pending रुको_desc commands are पातed.
	 * No new descriptors are fetched until the ITE is cleared.
	 */
	अगर (fault & DMA_FSTS_ITE) अणु
		head = पढ़ोl(iommu->reg + DMAR_IQH_REG);
		head = ((head >> shअगरt) - 1 + QI_LENGTH) % QI_LENGTH;
		head |= 1;
		tail = पढ़ोl(iommu->reg + DMAR_IQT_REG);
		tail = ((tail >> shअगरt) - 1 + QI_LENGTH) % QI_LENGTH;

		ग_लिखोl(DMA_FSTS_ITE, iommu->reg + DMAR_FSTS_REG);
		pr_info("Invalidation Time-out Error (ITE) cleared\n");

		करो अणु
			अगर (qi->desc_status[head] == QI_IN_USE)
				qi->desc_status[head] = QI_ABORT;
			head = (head - 2 + QI_LENGTH) % QI_LENGTH;
		पूर्ण जबतक (head != tail);

		अगर (qi->desc_status[रुको_index] == QI_ABORT)
			वापस -EAGAIN;
	पूर्ण

	अगर (fault & DMA_FSTS_ICE) अणु
		ग_लिखोl(DMA_FSTS_ICE, iommu->reg + DMAR_FSTS_REG);
		pr_info("Invalidation Completion Error (ICE) cleared\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to submit invalidation descriptors of all types to the queued
 * invalidation पूर्णांकerface(QI). Multiple descriptors can be submitted at a
 * समय, a रुको descriptor will be appended to each submission to ensure
 * hardware has completed the invalidation beक्रमe वापस. Wait descriptors
 * can be part of the submission but it will not be polled क्रम completion.
 */
पूर्णांक qi_submit_sync(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा qi_desc *desc,
		   अचिन्हित पूर्णांक count, अचिन्हित दीर्घ options)
अणु
	काष्ठा q_inval *qi = iommu->qi;
	काष्ठा qi_desc रुको_desc;
	पूर्णांक रुको_index, index;
	अचिन्हित दीर्घ flags;
	पूर्णांक offset, shअगरt;
	पूर्णांक rc, i;

	अगर (!qi)
		वापस 0;

restart:
	rc = 0;

	raw_spin_lock_irqsave(&qi->q_lock, flags);
	/*
	 * Check अगर we have enough empty slots in the queue to submit,
	 * the calculation is based on:
	 * # of desc + 1 रुको desc + 1 space between head and tail
	 */
	जबतक (qi->मुक्त_cnt < count + 2) अणु
		raw_spin_unlock_irqrestore(&qi->q_lock, flags);
		cpu_relax();
		raw_spin_lock_irqsave(&qi->q_lock, flags);
	पूर्ण

	index = qi->मुक्त_head;
	रुको_index = (index + count) % QI_LENGTH;
	shअगरt = qi_shअगरt(iommu);

	क्रम (i = 0; i < count; i++) अणु
		offset = ((index + i) % QI_LENGTH) << shअगरt;
		स_नकल(qi->desc + offset, &desc[i], 1 << shअगरt);
		qi->desc_status[(index + i) % QI_LENGTH] = QI_IN_USE;
		trace_qi_submit(iommu, desc[i].qw0, desc[i].qw1,
				desc[i].qw2, desc[i].qw3);
	पूर्ण
	qi->desc_status[रुको_index] = QI_IN_USE;

	रुको_desc.qw0 = QI_IWD_STATUS_DATA(QI_DONE) |
			QI_IWD_STATUS_WRITE | QI_IWD_TYPE;
	अगर (options & QI_OPT_WAIT_DRAIN)
		रुको_desc.qw0 |= QI_IWD_PRQ_DRAIN;
	रुको_desc.qw1 = virt_to_phys(&qi->desc_status[रुको_index]);
	रुको_desc.qw2 = 0;
	रुको_desc.qw3 = 0;

	offset = रुको_index << shअगरt;
	स_नकल(qi->desc + offset, &रुको_desc, 1 << shअगरt);

	qi->मुक्त_head = (qi->मुक्त_head + count + 1) % QI_LENGTH;
	qi->मुक्त_cnt -= count + 1;

	/*
	 * update the HW tail रेजिस्टर indicating the presence of
	 * new descriptors.
	 */
	ग_लिखोl(qi->मुक्त_head << shअगरt, iommu->reg + DMAR_IQT_REG);

	जबतक (qi->desc_status[रुको_index] != QI_DONE) अणु
		/*
		 * We will leave the पूर्णांकerrupts disabled, to prevent पूर्णांकerrupt
		 * context to queue another cmd जबतक a cmd is alपढ़ोy submitted
		 * and रुकोing क्रम completion on this cpu. This is to aव्योम
		 * a deadlock where the पूर्णांकerrupt context can रुको indefinitely
		 * क्रम मुक्त slots in the queue.
		 */
		rc = qi_check_fault(iommu, index, रुको_index);
		अगर (rc)
			अवरोध;

		raw_spin_unlock(&qi->q_lock);
		cpu_relax();
		raw_spin_lock(&qi->q_lock);
	पूर्ण

	क्रम (i = 0; i < count; i++)
		qi->desc_status[(index + i) % QI_LENGTH] = QI_DONE;

	reclaim_मुक्त_desc(qi);
	raw_spin_unlock_irqrestore(&qi->q_lock, flags);

	अगर (rc == -EAGAIN)
		जाओ restart;

	वापस rc;
पूर्ण

/*
 * Flush the global पूर्णांकerrupt entry cache.
 */
व्योम qi_global_iec(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा qi_desc desc;

	desc.qw0 = QI_IEC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	/* should never fail */
	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

व्योम qi_flush_context(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u16 sid, u8 fm,
		      u64 type)
अणु
	काष्ठा qi_desc desc;

	desc.qw0 = QI_CC_FM(fm) | QI_CC_SID(sid) | QI_CC_DID(did)
			| QI_CC_GRAN(type) | QI_CC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

व्योम qi_flush_iotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u64 addr,
		    अचिन्हित पूर्णांक size_order, u64 type)
अणु
	u8 dw = 0, dr = 0;

	काष्ठा qi_desc desc;
	पूर्णांक ih = 0;

	अगर (cap_ग_लिखो_drain(iommu->cap))
		dw = 1;

	अगर (cap_पढ़ो_drain(iommu->cap))
		dr = 1;

	desc.qw0 = QI_IOTLB_DID(did) | QI_IOTLB_DR(dr) | QI_IOTLB_DW(dw)
		| QI_IOTLB_GRAN(type) | QI_IOTLB_TYPE;
	desc.qw1 = QI_IOTLB_ADDR(addr) | QI_IOTLB_IH(ih)
		| QI_IOTLB_AM(size_order);
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

व्योम qi_flush_dev_iotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 sid, u16 pfsid,
			u16 qdep, u64 addr, अचिन्हित mask)
अणु
	काष्ठा qi_desc desc;

	अगर (mask) अणु
		addr |= (1ULL << (VTD_PAGE_SHIFT + mask - 1)) - 1;
		desc.qw1 = QI_DEV_IOTLB_ADDR(addr) | QI_DEV_IOTLB_SIZE;
	पूर्ण अन्यथा
		desc.qw1 = QI_DEV_IOTLB_ADDR(addr);

	अगर (qdep >= QI_DEV_IOTLB_MAX_INVS)
		qdep = 0;

	desc.qw0 = QI_DEV_IOTLB_SID(sid) | QI_DEV_IOTLB_QDEP(qdep) |
		   QI_DIOTLB_TYPE | QI_DEV_IOTLB_PFSID(pfsid);
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

/* PASID-based IOTLB invalidation */
व्योम qi_flush_piotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u32 pasid, u64 addr,
		     अचिन्हित दीर्घ npages, bool ih)
अणु
	काष्ठा qi_desc desc = अणु.qw2 = 0, .qw3 = 0पूर्ण;

	/*
	 * npages == -1 means a PASID-selective invalidation, otherwise,
	 * a positive value क्रम Page-selective-within-PASID invalidation.
	 * 0 is not a valid input.
	 */
	अगर (WARN_ON(!npages)) अणु
		pr_err("Invalid input npages = %ld\n", npages);
		वापस;
	पूर्ण

	अगर (npages == -1) अणु
		desc.qw0 = QI_EIOTLB_PASID(pasid) |
				QI_EIOTLB_DID(did) |
				QI_EIOTLB_GRAN(QI_GRAN_NONG_PASID) |
				QI_EIOTLB_TYPE;
		desc.qw1 = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक mask = ilog2(__roundup_घात_of_two(npages));
		अचिन्हित दीर्घ align = (1ULL << (VTD_PAGE_SHIFT + mask));

		अगर (WARN_ON_ONCE(!IS_ALIGNED(addr, align)))
			addr = ALIGN_DOWN(addr, align);

		desc.qw0 = QI_EIOTLB_PASID(pasid) |
				QI_EIOTLB_DID(did) |
				QI_EIOTLB_GRAN(QI_GRAN_PSI_PASID) |
				QI_EIOTLB_TYPE;
		desc.qw1 = QI_EIOTLB_ADDR(addr) |
				QI_EIOTLB_IH(ih) |
				QI_EIOTLB_AM(mask);
	पूर्ण

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

/* PASID-based device IOTLB Invalidate */
व्योम qi_flush_dev_iotlb_pasid(काष्ठा पूर्णांकel_iommu *iommu, u16 sid, u16 pfsid,
			      u32 pasid,  u16 qdep, u64 addr, अचिन्हित पूर्णांक size_order)
अणु
	अचिन्हित दीर्घ mask = 1UL << (VTD_PAGE_SHIFT + size_order - 1);
	काष्ठा qi_desc desc = अणु.qw1 = 0, .qw2 = 0, .qw3 = 0पूर्ण;

	desc.qw0 = QI_DEV_EIOTLB_PASID(pasid) | QI_DEV_EIOTLB_SID(sid) |
		QI_DEV_EIOTLB_QDEP(qdep) | QI_DEIOTLB_TYPE |
		QI_DEV_IOTLB_PFSID(pfsid);

	/*
	 * If S bit is 0, we only flush a single page. If S bit is set,
	 * The least signअगरicant zero bit indicates the invalidation address
	 * range. VT-d spec 6.5.2.6.
	 * e.g. address bit 12[0] indicates 8KB, 13[0] indicates 16KB.
	 * size order = 0 is PAGE_SIZE 4KB
	 * Max Invs Pending (MIP) is set to 0 क्रम now until we have DIT in
	 * ECAP.
	 */
	अगर (!IS_ALIGNED(addr, VTD_PAGE_SIZE << size_order))
		pr_warn_ratelimited("Invalidate non-aligned address %llx, order %d\n",
				    addr, size_order);

	/* Take page address */
	desc.qw1 = QI_DEV_EIOTLB_ADDR(addr);

	अगर (size_order) अणु
		/*
		 * Existing 0s in address below size_order may be the least
		 * signअगरicant bit, we must set them to 1s to aव्योम having
		 * smaller size than desired.
		 */
		desc.qw1 |= GENMASK_ULL(size_order + VTD_PAGE_SHIFT - 1,
					VTD_PAGE_SHIFT);
		/* Clear size_order bit to indicate size */
		desc.qw1 &= ~mask;
		/* Set the S bit to indicate flushing more than 1 page */
		desc.qw1 |= QI_DEV_EIOTLB_SIZE;
	पूर्ण

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

व्योम qi_flush_pasid_cache(काष्ठा पूर्णांकel_iommu *iommu, u16 did,
			  u64 granu, u32 pasid)
अणु
	काष्ठा qi_desc desc = अणु.qw1 = 0, .qw2 = 0, .qw3 = 0पूर्ण;

	desc.qw0 = QI_PC_PASID(pasid) | QI_PC_DID(did) |
			QI_PC_GRAN(granu) | QI_PC_TYPE;
	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

/*
 * Disable Queued Invalidation पूर्णांकerface.
 */
व्योम dmar_disable_qi(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अचिन्हित दीर्घ flags;
	u32 sts;
	cycles_t start_समय = get_cycles();

	अगर (!ecap_qis(iommu->ecap))
		वापस;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);

	sts =  पढ़ोl(iommu->reg + DMAR_GSTS_REG);
	अगर (!(sts & DMA_GSTS_QIES))
		जाओ end;

	/*
	 * Give a chance to HW to complete the pending invalidation requests.
	 */
	जबतक ((पढ़ोl(iommu->reg + DMAR_IQT_REG) !=
		पढ़ोl(iommu->reg + DMAR_IQH_REG)) &&
		(DMAR_OPERATION_TIMEOUT > (get_cycles() - start_समय)))
		cpu_relax();

	iommu->gcmd &= ~DMA_GCMD_QIE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG, पढ़ोl,
		      !(sts & DMA_GSTS_QIES), sts);
end:
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

/*
 * Enable queued invalidation.
 */
अटल व्योम __dmar_enable_qi(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 sts;
	अचिन्हित दीर्घ flags;
	काष्ठा q_inval *qi = iommu->qi;
	u64 val = virt_to_phys(qi->desc);

	qi->मुक्त_head = qi->मुक्त_tail = 0;
	qi->मुक्त_cnt = QI_LENGTH;

	/*
	 * Set DW=1 and QS=1 in IQA_REG when Scalable Mode capability
	 * is present.
	 */
	अगर (ecap_smts(iommu->ecap))
		val |= (1 << 11) | 1;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);

	/* ग_लिखो zero to the tail reg */
	ग_लिखोl(0, iommu->reg + DMAR_IQT_REG);

	dmar_ग_लिखोq(iommu->reg + DMAR_IQA_REG, val);

	iommu->gcmd |= DMA_GCMD_QIE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG, पढ़ोl, (sts & DMA_GSTS_QIES), sts);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

/*
 * Enable Queued Invalidation पूर्णांकerface. This is a must to support
 * पूर्णांकerrupt-remapping. Also used by DMA-remapping, which replaces
 * रेजिस्टर based IOTLB invalidation.
 */
पूर्णांक dmar_enable_qi(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा q_inval *qi;
	काष्ठा page *desc_page;

	अगर (!ecap_qis(iommu->ecap))
		वापस -ENOENT;

	/*
	 * queued invalidation is alपढ़ोy setup and enabled.
	 */
	अगर (iommu->qi)
		वापस 0;

	iommu->qi = kदो_स्मृति(माप(*qi), GFP_ATOMIC);
	अगर (!iommu->qi)
		वापस -ENOMEM;

	qi = iommu->qi;

	/*
	 * Need two pages to accommodate 256 descriptors of 256 bits each
	 * अगर the remapping hardware supports scalable mode translation.
	 */
	desc_page = alloc_pages_node(iommu->node, GFP_ATOMIC | __GFP_ZERO,
				     !!ecap_smts(iommu->ecap));
	अगर (!desc_page) अणु
		kमुक्त(qi);
		iommu->qi = शून्य;
		वापस -ENOMEM;
	पूर्ण

	qi->desc = page_address(desc_page);

	qi->desc_status = kसुस्मृति(QI_LENGTH, माप(पूर्णांक), GFP_ATOMIC);
	अगर (!qi->desc_status) अणु
		मुक्त_page((अचिन्हित दीर्घ) qi->desc);
		kमुक्त(qi);
		iommu->qi = शून्य;
		वापस -ENOMEM;
	पूर्ण

	raw_spin_lock_init(&qi->q_lock);

	__dmar_enable_qi(iommu);

	वापस 0;
पूर्ण

/* iommu पूर्णांकerrupt handling. Most stuff are MSI-like. */

क्रमागत faulttype अणु
	DMA_REMAP,
	INTR_REMAP,
	UNKNOWN,
पूर्ण;

अटल स्थिर अक्षर *dma_remap_fault_reasons[] =
अणु
	"Software",
	"Present bit in root entry is clear",
	"Present bit in context entry is clear",
	"Invalid context entry",
	"Access beyond MGAW",
	"PTE Write access is not set",
	"PTE Read access is not set",
	"Next page table ptr is invalid",
	"Root table address invalid",
	"Context table ptr is invalid",
	"non-zero reserved fields in RTP",
	"non-zero reserved fields in CTP",
	"non-zero reserved fields in PTE",
	"PCE for translation request specifies blocking",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dma_remap_sm_fault_reasons[] = अणु
	"SM: Invalid Root Table Address",
	"SM: TTM 0 for request with PASID",
	"SM: TTM 0 for page group request",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x33-0x37 */
	"SM: Error attempting to access Root Entry",
	"SM: Present bit in Root Entry is clear",
	"SM: Non-zero reserved field set in Root Entry",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x3B-0x3F */
	"SM: Error attempting to access Context Entry",
	"SM: Present bit in Context Entry is clear",
	"SM: Non-zero reserved field set in the Context Entry",
	"SM: Invalid Context Entry",
	"SM: DTE field in Context Entry is clear",
	"SM: PASID Enable field in Context Entry is clear",
	"SM: PASID is larger than the max in Context Entry",
	"SM: PRE field in Context-Entry is clear",
	"SM: RID_PASID field error in Context-Entry",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x49-0x4F */
	"SM: Error attempting to access the PASID Directory Entry",
	"SM: Present bit in Directory Entry is clear",
	"SM: Non-zero reserved field set in PASID Directory Entry",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x53-0x57 */
	"SM: Error attempting to access PASID Table Entry",
	"SM: Present bit in PASID Table Entry is clear",
	"SM: Non-zero reserved field set in PASID Table Entry",
	"SM: Invalid Scalable-Mode PASID Table Entry",
	"SM: ERE field is clear in PASID Table Entry",
	"SM: SRE field is clear in PASID Table Entry",
	"Unknown", "Unknown",/* 0x5E-0x5F */
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x60-0x67 */
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x68-0x6F */
	"SM: Error attempting to access first-level paging entry",
	"SM: Present bit in first-level paging entry is clear",
	"SM: Non-zero reserved field set in first-level paging entry",
	"SM: Error attempting to access FL-PML4 entry",
	"SM: First-level entry address beyond MGAW in Nested translation",
	"SM: Read permission error in FL-PML4 entry in Nested translation",
	"SM: Read permission error in first-level paging entry in Nested translation",
	"SM: Write permission error in first-level paging entry in Nested translation",
	"SM: Error attempting to access second-level paging entry",
	"SM: Read/Write permission error in second-level paging entry",
	"SM: Non-zero reserved field set in second-level paging entry",
	"SM: Invalid second-level page table pointer",
	"SM: A/D bit update needed in second-level entry when set up in no snoop",
	"Unknown", "Unknown", "Unknown", /* 0x7D-0x7F */
	"SM: Address in first-level translation is not canonical",
	"SM: U/S set 0 for first-level translation with user privilege",
	"SM: No execute permission for request with PASID and ER=1",
	"SM: Address beyond the DMA hardware max",
	"SM: Second-level entry address beyond the max",
	"SM: No write permission for Write/AtomicOp request",
	"SM: No read permission for Read/AtomicOp request",
	"SM: Invalid address-interrupt address",
	"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", /* 0x88-0x8F */
	"SM: A/D bit update needed in first-level entry when set up in no snoop",
पूर्ण;

अटल स्थिर अक्षर *irq_remap_fault_reasons[] =
अणु
	"Detected reserved fields in the decoded interrupt-remapped request",
	"Interrupt index exceeded the interrupt-remapping table size",
	"Present field in the IRTE entry is clear",
	"Error accessing interrupt-remapping table pointed by IRTA_REG",
	"Detected reserved fields in the IRTE entry",
	"Blocked a compatibility format interrupt request",
	"Blocked an interrupt request due to source-id verification failure",
पूर्ण;

अटल स्थिर अक्षर *dmar_get_fault_reason(u8 fault_reason, पूर्णांक *fault_type)
अणु
	अगर (fault_reason >= 0x20 && (fault_reason - 0x20 <
					ARRAY_SIZE(irq_remap_fault_reasons))) अणु
		*fault_type = INTR_REMAP;
		वापस irq_remap_fault_reasons[fault_reason - 0x20];
	पूर्ण अन्यथा अगर (fault_reason >= 0x30 && (fault_reason - 0x30 <
			ARRAY_SIZE(dma_remap_sm_fault_reasons))) अणु
		*fault_type = DMA_REMAP;
		वापस dma_remap_sm_fault_reasons[fault_reason - 0x30];
	पूर्ण अन्यथा अगर (fault_reason < ARRAY_SIZE(dma_remap_fault_reasons)) अणु
		*fault_type = DMA_REMAP;
		वापस dma_remap_fault_reasons[fault_reason];
	पूर्ण अन्यथा अणु
		*fault_type = UNKNOWN;
		वापस "Unknown";
	पूर्ण
पूर्ण


अटल अंतरभूत पूर्णांक dmar_msi_reg(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक irq)
अणु
	अगर (iommu->irq == irq)
		वापस DMAR_FECTL_REG;
	अन्यथा अगर (iommu->pr_irq == irq)
		वापस DMAR_PECTL_REG;
	अन्यथा
		BUG();
पूर्ण

व्योम dmar_msi_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = irq_data_get_irq_handler_data(data);
	पूर्णांक reg = dmar_msi_reg(iommu, data->irq);
	अचिन्हित दीर्घ flag;

	/* unmask it */
	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	ग_लिखोl(0, iommu->reg + reg);
	/* Read a reg to क्रमce flush the post ग_लिखो */
	पढ़ोl(iommu->reg + reg);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

व्योम dmar_msi_mask(काष्ठा irq_data *data)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = irq_data_get_irq_handler_data(data);
	पूर्णांक reg = dmar_msi_reg(iommu, data->irq);
	अचिन्हित दीर्घ flag;

	/* mask it */
	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	ग_लिखोl(DMA_FECTL_IM, iommu->reg + reg);
	/* Read a reg to क्रमce flush the post ग_लिखो */
	पढ़ोl(iommu->reg + reg);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

व्योम dmar_msi_ग_लिखो(पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = irq_get_handler_data(irq);
	पूर्णांक reg = dmar_msi_reg(iommu, irq);
	अचिन्हित दीर्घ flag;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	ग_लिखोl(msg->data, iommu->reg + reg + 4);
	ग_लिखोl(msg->address_lo, iommu->reg + reg + 8);
	ग_लिखोl(msg->address_hi, iommu->reg + reg + 12);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

व्योम dmar_msi_पढ़ो(पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = irq_get_handler_data(irq);
	पूर्णांक reg = dmar_msi_reg(iommu, irq);
	अचिन्हित दीर्घ flag;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	msg->data = पढ़ोl(iommu->reg + reg + 4);
	msg->address_lo = पढ़ोl(iommu->reg + reg + 8);
	msg->address_hi = पढ़ोl(iommu->reg + reg + 12);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

अटल पूर्णांक dmar_fault_करो_one(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक type,
		u8 fault_reason, u32 pasid, u16 source_id,
		अचिन्हित दीर्घ दीर्घ addr)
अणु
	स्थिर अक्षर *reason;
	पूर्णांक fault_type;

	reason = dmar_get_fault_reason(fault_reason, &fault_type);

	अगर (fault_type == INTR_REMAP)
		pr_err("[INTR-REMAP] Request device [%02x:%02x.%d] fault index %llx [fault reason %02d] %s\n",
			source_id >> 8, PCI_SLOT(source_id & 0xFF),
			PCI_FUNC(source_id & 0xFF), addr >> 48,
			fault_reason, reason);
	अन्यथा
		pr_err("[%s] Request device [%02x:%02x.%d] PASID %x fault addr %llx [fault reason %02d] %s\n",
		       type ? "DMA Read" : "DMA Write",
		       source_id >> 8, PCI_SLOT(source_id & 0xFF),
		       PCI_FUNC(source_id & 0xFF), pasid, addr,
		       fault_reason, reason);
	वापस 0;
पूर्ण

#घोषणा PRIMARY_FAULT_REG_LEN (16)
irqवापस_t dmar_fault(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_id;
	पूर्णांक reg, fault_index;
	u32 fault_status;
	अचिन्हित दीर्घ flag;
	अटल DEFINE_RATELIMIT_STATE(rs,
				      DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	fault_status = पढ़ोl(iommu->reg + DMAR_FSTS_REG);
	अगर (fault_status && __ratelimit(&rs))
		pr_err("DRHD: handling fault status reg %x\n", fault_status);

	/* TBD: ignore advanced fault log currently */
	अगर (!(fault_status & DMA_FSTS_PPF))
		जाओ unlock_निकास;

	fault_index = dma_fsts_fault_record_index(fault_status);
	reg = cap_fault_reg_offset(iommu->cap);
	जबतक (1) अणु
		/* Disable prपूर्णांकing, simply clear the fault when ratelimited */
		bool ratelimited = !__ratelimit(&rs);
		u8 fault_reason;
		u16 source_id;
		u64 guest_addr;
		u32 pasid;
		पूर्णांक type;
		u32 data;
		bool pasid_present;

		/* highest 32 bits */
		data = पढ़ोl(iommu->reg + reg +
				fault_index * PRIMARY_FAULT_REG_LEN + 12);
		अगर (!(data & DMA_FRCD_F))
			अवरोध;

		अगर (!ratelimited) अणु
			fault_reason = dma_frcd_fault_reason(data);
			type = dma_frcd_type(data);

			pasid = dma_frcd_pasid_value(data);
			data = पढ़ोl(iommu->reg + reg +
				     fault_index * PRIMARY_FAULT_REG_LEN + 8);
			source_id = dma_frcd_source_id(data);

			pasid_present = dma_frcd_pasid_present(data);
			guest_addr = dmar_पढ़ोq(iommu->reg + reg +
					fault_index * PRIMARY_FAULT_REG_LEN);
			guest_addr = dma_frcd_page_addr(guest_addr);
		पूर्ण

		/* clear the fault */
		ग_लिखोl(DMA_FRCD_F, iommu->reg + reg +
			fault_index * PRIMARY_FAULT_REG_LEN + 12);

		raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);

		अगर (!ratelimited)
			/* Using pasid -1 अगर pasid is not present */
			dmar_fault_करो_one(iommu, type, fault_reason,
					  pasid_present ? pasid : -1,
					  source_id, guest_addr);

		fault_index++;
		अगर (fault_index >= cap_num_fault_regs(iommu->cap))
			fault_index = 0;
		raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	पूर्ण

	ग_लिखोl(DMA_FSTS_PFO | DMA_FSTS_PPF | DMA_FSTS_PRO,
	       iommu->reg + DMAR_FSTS_REG);

unlock_निकास:
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक dmar_set_पूर्णांकerrupt(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक irq, ret;

	/*
	 * Check अगर the fault पूर्णांकerrupt is alपढ़ोy initialized.
	 */
	अगर (iommu->irq)
		वापस 0;

	irq = dmar_alloc_hwirq(iommu->seq_id, iommu->node, iommu);
	अगर (irq > 0) अणु
		iommu->irq = irq;
	पूर्ण अन्यथा अणु
		pr_err("No free IRQ vectors\n");
		वापस -EINVAL;
	पूर्ण

	ret = request_irq(irq, dmar_fault, IRQF_NO_THREAD, iommu->name, iommu);
	अगर (ret)
		pr_err("Can't request irq\n");
	वापस ret;
पूर्ण

पूर्णांक __init enable_drhd_fault_handling(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;

	/*
	 * Enable fault control पूर्णांकerrupt.
	 */
	क्रम_each_iommu(iommu, drhd) अणु
		u32 fault_status;
		पूर्णांक ret = dmar_set_पूर्णांकerrupt(iommu);

		अगर (ret) अणु
			pr_err("DRHD %Lx: failed to enable fault, interrupt, ret %d\n",
			       (अचिन्हित दीर्घ दीर्घ)drhd->reg_base_addr, ret);
			वापस -1;
		पूर्ण

		/*
		 * Clear any previous faults.
		 */
		dmar_fault(iommu->irq, iommu);
		fault_status = पढ़ोl(iommu->reg + DMAR_FSTS_REG);
		ग_लिखोl(fault_status, iommu->reg + DMAR_FSTS_REG);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Re-enable Queued Invalidation पूर्णांकerface.
 */
पूर्णांक dmar_reenable_qi(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अगर (!ecap_qis(iommu->ecap))
		वापस -ENOENT;

	अगर (!iommu->qi)
		वापस -ENOENT;

	/*
	 * First disable queued invalidation.
	 */
	dmar_disable_qi(iommu);
	/*
	 * Then enable queued invalidation again. Since there is no pending
	 * invalidation requests now, it's safe to re-enable queued
	 * invalidation.
	 */
	__dmar_enable_qi(iommu);

	वापस 0;
पूर्ण

/*
 * Check पूर्णांकerrupt remapping support in DMAR table description.
 */
पूर्णांक __init dmar_ir_support(व्योम)
अणु
	काष्ठा acpi_table_dmar *dmar;
	dmar = (काष्ठा acpi_table_dmar *)dmar_tbl;
	अगर (!dmar)
		वापस 0;
	वापस dmar->flags & 0x1;
पूर्ण

/* Check whether DMAR units are in use */
अटल अंतरभूत bool dmar_in_use(व्योम)
अणु
	वापस irq_remapping_enabled || पूर्णांकel_iommu_enabled;
पूर्ण

अटल पूर्णांक __init dmar_मुक्त_unused_resources(व्योम)
अणु
	काष्ठा dmar_drhd_unit *dmaru, *dmaru_n;

	अगर (dmar_in_use())
		वापस 0;

	अगर (dmar_dev_scope_status != 1 && !list_empty(&dmar_drhd_units))
		bus_unरेजिस्टर_notअगरier(&pci_bus_type, &dmar_pci_bus_nb);

	करोwn_ग_लिखो(&dmar_global_lock);
	list_क्रम_each_entry_safe(dmaru, dmaru_n, &dmar_drhd_units, list) अणु
		list_del(&dmaru->list);
		dmar_मुक्त_drhd(dmaru);
	पूर्ण
	up_ग_लिखो(&dmar_global_lock);

	वापस 0;
पूर्ण

late_initcall(dmar_मुक्त_unused_resources);
IOMMU_INIT_POST(detect_पूर्णांकel_iommu);

/*
 * DMAR Hotplug Support
 * For more details, please refer to Intel(R) Virtualization Technology
 * क्रम Directed-IO Architecture Specअगरiction, Rev 2.2, Section 8.8
 * "Remapping Hardware Unit Hot Plug".
 */
अटल guid_t dmar_hp_guid =
	GUID_INIT(0xD8C1A3A6, 0xBE9B, 0x4C9B,
		  0x91, 0xBF, 0xC3, 0xCB, 0x81, 0xFC, 0x5D, 0xAF);

/*
 * Currently there's only one revision and BIOS will not check the revision id,
 * so use 0 क्रम safety.
 */
#घोषणा	DMAR_DSM_REV_ID			0
#घोषणा	DMAR_DSM_FUNC_DRHD		1
#घोषणा	DMAR_DSM_FUNC_ATSR		2
#घोषणा	DMAR_DSM_FUNC_RHSA		3
#घोषणा	DMAR_DSM_FUNC_SATC		4

अटल अंतरभूत bool dmar_detect_dsm(acpi_handle handle, पूर्णांक func)
अणु
	वापस acpi_check_dsm(handle, &dmar_hp_guid, DMAR_DSM_REV_ID, 1 << func);
पूर्ण

अटल पूर्णांक dmar_walk_dsm_resource(acpi_handle handle, पूर्णांक func,
				  dmar_res_handler_t handler, व्योम *arg)
अणु
	पूर्णांक ret = -ENODEV;
	जोड़ acpi_object *obj;
	काष्ठा acpi_dmar_header *start;
	काष्ठा dmar_res_callback callback;
	अटल पूर्णांक res_type[] = अणु
		[DMAR_DSM_FUNC_DRHD] = ACPI_DMAR_TYPE_HARDWARE_UNIT,
		[DMAR_DSM_FUNC_ATSR] = ACPI_DMAR_TYPE_ROOT_ATS,
		[DMAR_DSM_FUNC_RHSA] = ACPI_DMAR_TYPE_HARDWARE_AFFINITY,
		[DMAR_DSM_FUNC_SATC] = ACPI_DMAR_TYPE_SATC,
	पूर्ण;

	अगर (!dmar_detect_dsm(handle, func))
		वापस 0;

	obj = acpi_evaluate_dsm_typed(handle, &dmar_hp_guid, DMAR_DSM_REV_ID,
				      func, शून्य, ACPI_TYPE_BUFFER);
	अगर (!obj)
		वापस -ENODEV;

	स_रखो(&callback, 0, माप(callback));
	callback.cb[res_type[func]] = handler;
	callback.arg[res_type[func]] = arg;
	start = (काष्ठा acpi_dmar_header *)obj->buffer.poपूर्णांकer;
	ret = dmar_walk_remapping_entries(start, obj->buffer.length, &callback);

	ACPI_FREE(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक dmar_hp_add_drhd(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	पूर्णांक ret;
	काष्ठा dmar_drhd_unit *dmaru;

	dmaru = dmar_find_dmaru((काष्ठा acpi_dmar_hardware_unit *)header);
	अगर (!dmaru)
		वापस -ENODEV;

	ret = dmar_ir_hotplug(dmaru, true);
	अगर (ret == 0)
		ret = dmar_iommu_hotplug(dmaru, true);

	वापस ret;
पूर्ण

अटल पूर्णांक dmar_hp_हटाओ_drhd(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	पूर्णांक i, ret;
	काष्ठा device *dev;
	काष्ठा dmar_drhd_unit *dmaru;

	dmaru = dmar_find_dmaru((काष्ठा acpi_dmar_hardware_unit *)header);
	अगर (!dmaru)
		वापस 0;

	/*
	 * All PCI devices managed by this unit should have been destroyed.
	 */
	अगर (!dmaru->include_all && dmaru->devices && dmaru->devices_cnt) अणु
		क्रम_each_active_dev_scope(dmaru->devices,
					  dmaru->devices_cnt, i, dev)
			वापस -EBUSY;
	पूर्ण

	ret = dmar_ir_hotplug(dmaru, false);
	अगर (ret == 0)
		ret = dmar_iommu_hotplug(dmaru, false);

	वापस ret;
पूर्ण

अटल पूर्णांक dmar_hp_release_drhd(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	काष्ठा dmar_drhd_unit *dmaru;

	dmaru = dmar_find_dmaru((काष्ठा acpi_dmar_hardware_unit *)header);
	अगर (dmaru) अणु
		list_del_rcu(&dmaru->list);
		synchronize_rcu();
		dmar_मुक्त_drhd(dmaru);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmar_hotplug_insert(acpi_handle handle)
अणु
	पूर्णांक ret;
	पूर्णांक drhd_count = 0;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				     &dmar_validate_one_drhd, (व्योम *)1);
	अगर (ret)
		जाओ out;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				     &dmar_parse_one_drhd, (व्योम *)&drhd_count);
	अगर (ret == 0 && drhd_count == 0) अणु
		pr_warn(FW_BUG "No DRHD structures in buffer returned by _DSM method\n");
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ release_drhd;
	पूर्ण

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_RHSA,
				     &dmar_parse_one_rhsa, शून्य);
	अगर (ret)
		जाओ release_drhd;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
				     &dmar_parse_one_atsr, शून्य);
	अगर (ret)
		जाओ release_atsr;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				     &dmar_hp_add_drhd, शून्य);
	अगर (!ret)
		वापस 0;

	dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
			       &dmar_hp_हटाओ_drhd, शून्य);
release_atsr:
	dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
			       &dmar_release_one_atsr, शून्य);
release_drhd:
	dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
			       &dmar_hp_release_drhd, शून्य);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक dmar_hotplug_हटाओ(acpi_handle handle)
अणु
	पूर्णांक ret;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
				     &dmar_check_one_atsr, शून्य);
	अगर (ret)
		वापस ret;

	ret = dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				     &dmar_hp_हटाओ_drhd, शून्य);
	अगर (ret == 0) अणु
		WARN_ON(dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_ATSR,
					       &dmar_release_one_atsr, शून्य));
		WARN_ON(dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
					       &dmar_hp_release_drhd, शून्य));
	पूर्ण अन्यथा अणु
		dmar_walk_dsm_resource(handle, DMAR_DSM_FUNC_DRHD,
				       &dmar_hp_add_drhd, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल acpi_status dmar_get_dsm_handle(acpi_handle handle, u32 lvl,
				       व्योम *context, व्योम **retval)
अणु
	acpi_handle *phdl = retval;

	अगर (dmar_detect_dsm(handle, DMAR_DSM_FUNC_DRHD)) अणु
		*phdl = handle;
		वापस AE_CTRL_TERMINATE;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक dmar_device_hotplug(acpi_handle handle, bool insert)
अणु
	पूर्णांक ret;
	acpi_handle पंचांगp = शून्य;
	acpi_status status;

	अगर (!dmar_in_use())
		वापस 0;

	अगर (dmar_detect_dsm(handle, DMAR_DSM_FUNC_DRHD)) अणु
		पंचांगp = handle;
	पूर्ण अन्यथा अणु
		status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle,
					     ACPI_UINT32_MAX,
					     dmar_get_dsm_handle,
					     शून्य, शून्य, &पंचांगp);
		अगर (ACPI_FAILURE(status)) अणु
			pr_warn("Failed to locate _DSM method.\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	अगर (पंचांगp == शून्य)
		वापस 0;

	करोwn_ग_लिखो(&dmar_global_lock);
	अगर (insert)
		ret = dmar_hotplug_insert(पंचांगp);
	अन्यथा
		ret = dmar_hotplug_हटाओ(पंचांगp);
	up_ग_लिखो(&dmar_global_lock);

	वापस ret;
पूर्ण

पूर्णांक dmar_device_add(acpi_handle handle)
अणु
	वापस dmar_device_hotplug(handle, true);
पूर्ण

पूर्णांक dmar_device_हटाओ(acpi_handle handle)
अणु
	वापस dmar_device_hotplug(handle, false);
पूर्ण

/*
 * dmar_platक्रमm_optin - Is %DMA_CTRL_PLATFORM_OPT_IN_FLAG set in DMAR table
 *
 * Returns true अगर the platक्रमm has %DMA_CTRL_PLATFORM_OPT_IN_FLAG set in
 * the ACPI DMAR table. This means that the platक्रमm boot firmware has made
 * sure no device can issue DMA outside of RMRR regions.
 */
bool dmar_platक्रमm_optin(व्योम)
अणु
	काष्ठा acpi_table_dmar *dmar;
	acpi_status status;
	bool ret;

	status = acpi_get_table(ACPI_SIG_DMAR, 0,
				(काष्ठा acpi_table_header **)&dmar);
	अगर (ACPI_FAILURE(status))
		वापस false;

	ret = !!(dmar->flags & DMAR_PLATFORM_OPT_IN);
	acpi_put_table((काष्ठा acpi_table_header *)dmar);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dmar_platक्रमm_optin);
