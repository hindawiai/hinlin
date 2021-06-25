<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2010 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 *         Leo Duran <leo.duran@amd.com>
 */

#घोषणा pr_fmt(fmt)     "AMD-Vi: " fmt
#घोषणा dev_fmt(fmt)    pr_fmt(fmt)

#समावेश <linux/ratelimit.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci-ats.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/delay.h>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/percpu.h>
#समावेश <linux/iova.h>
#समावेश <linux/io-pgtable.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/dma.h>

#समावेश "amd_iommu.h"
#समावेश "../irq_remapping.h"

#घोषणा CMD_SET_TYPE(cmd, t) ((cmd)->data[1] |= ((t) << 28))

#घोषणा LOOP_TIMEOUT	100000

/* IO भव address start page frame number */
#घोषणा IOVA_START_PFN		(1)
#घोषणा IOVA_PFN(addr)		((addr) >> PAGE_SHIFT)

/* Reserved IOVA ranges */
#घोषणा MSI_RANGE_START		(0xfee00000)
#घोषणा MSI_RANGE_END		(0xfeefffff)
#घोषणा HT_RANGE_START		(0xfd00000000ULL)
#घोषणा HT_RANGE_END		(0xffffffffffULL)

#घोषणा DEFAULT_PGTABLE_LEVEL	PAGE_MODE_3_LEVEL

अटल DEFINE_SPINLOCK(pd_biपंचांगap_lock);

/* List of all available dev_data काष्ठाures */
अटल LLIST_HEAD(dev_data_list);

LIST_HEAD(ioapic_map);
LIST_HEAD(hpet_map);
LIST_HEAD(acpihid_map);

/*
 * Doमुख्य क्रम untranslated devices - only allocated
 * अगर iommu=pt passed on kernel cmd line.
 */
स्थिर काष्ठा iommu_ops amd_iommu_ops;

अटल ATOMIC_NOTIFIER_HEAD(ppr_notअगरier);
पूर्णांक amd_iommu_max_glx_val = -1;

/*
 * general काष्ठा to manage commands send to an IOMMU
 */
काष्ठा iommu_cmd अणु
	u32 data[4];
पूर्ण;

काष्ठा kmem_cache *amd_iommu_irq_cache;

अटल व्योम detach_device(काष्ठा device *dev);

/****************************************************************************
 *
 * Helper functions
 *
 ****************************************************************************/

अटल अंतरभूत u16 get_pci_device_id(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस pci_dev_id(pdev);
पूर्ण

अटल अंतरभूत पूर्णांक get_acpihid_device_id(काष्ठा device *dev,
					काष्ठा acpihid_map_entry **entry)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा acpihid_map_entry *p;

	अगर (!adev)
		वापस -ENODEV;

	list_क्रम_each_entry(p, &acpihid_map, list) अणु
		अगर (acpi_dev_hid_uid_match(adev, p->hid,
					   p->uid[0] ? p->uid : शून्य)) अणु
			अगर (entry)
				*entry = p;
			वापस p->devid;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक get_device_id(काष्ठा device *dev)
अणु
	पूर्णांक devid;

	अगर (dev_is_pci(dev))
		devid = get_pci_device_id(dev);
	अन्यथा
		devid = get_acpihid_device_id(dev, शून्य);

	वापस devid;
पूर्ण

अटल काष्ठा protection_करोमुख्य *to_pकरोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा protection_करोमुख्य, करोमुख्य);
पूर्ण

अटल काष्ठा iommu_dev_data *alloc_dev_data(u16 devid)
अणु
	काष्ठा iommu_dev_data *dev_data;

	dev_data = kzalloc(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data)
		वापस शून्य;

	spin_lock_init(&dev_data->lock);
	dev_data->devid = devid;
	ratelimit_शेष_init(&dev_data->rs);

	llist_add(&dev_data->dev_data_list, &dev_data_list);
	वापस dev_data;
पूर्ण

अटल काष्ठा iommu_dev_data *search_dev_data(u16 devid)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा llist_node *node;

	अगर (llist_empty(&dev_data_list))
		वापस शून्य;

	node = dev_data_list.first;
	llist_क्रम_each_entry(dev_data, node, dev_data_list) अणु
		अगर (dev_data->devid == devid)
			वापस dev_data;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक clone_alias(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	u16 devid = pci_dev_id(pdev);

	अगर (devid == alias)
		वापस 0;

	amd_iommu_rlookup_table[alias] =
		amd_iommu_rlookup_table[devid];
	स_नकल(amd_iommu_dev_table[alias].data,
	       amd_iommu_dev_table[devid].data,
	       माप(amd_iommu_dev_table[alias].data));

	वापस 0;
पूर्ण

अटल व्योम clone_aliases(काष्ठा pci_dev *pdev)
अणु
	अगर (!pdev)
		वापस;

	/*
	 * The IVRS alias stored in the alias table may not be
	 * part of the PCI DMA aliases अगर it's bus dअगरfers
	 * from the original device.
	 */
	clone_alias(pdev, amd_iommu_alias_table[pci_dev_id(pdev)], शून्य);

	pci_क्रम_each_dma_alias(pdev, clone_alias, शून्य);
पूर्ण

अटल काष्ठा pci_dev *setup_aliases(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u16 ivrs_alias;

	/* For ACPI HID devices, there are no aliases */
	अगर (!dev_is_pci(dev))
		वापस शून्य;

	/*
	 * Add the IVRS alias to the pci aliases अगर it is on the same
	 * bus. The IVRS table may know about a quirk that we करोn't.
	 */
	ivrs_alias = amd_iommu_alias_table[pci_dev_id(pdev)];
	अगर (ivrs_alias != pci_dev_id(pdev) &&
	    PCI_BUS_NUM(ivrs_alias) == pdev->bus->number)
		pci_add_dma_alias(pdev, ivrs_alias & 0xff, 1);

	clone_aliases(pdev);

	वापस pdev;
पूर्ण

अटल काष्ठा iommu_dev_data *find_dev_data(u16 devid)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[devid];

	dev_data = search_dev_data(devid);

	अगर (dev_data == शून्य) अणु
		dev_data = alloc_dev_data(devid);
		अगर (!dev_data)
			वापस शून्य;

		अगर (translation_pre_enabled(iommu))
			dev_data->defer_attach = true;
	पूर्ण

	वापस dev_data;
पूर्ण

/*
* Find or create an IOMMU group क्रम a acpihid device.
*/
अटल काष्ठा iommu_group *acpihid_device_group(काष्ठा device *dev)
अणु
	काष्ठा acpihid_map_entry *p, *entry = शून्य;
	पूर्णांक devid;

	devid = get_acpihid_device_id(dev, &entry);
	अगर (devid < 0)
		वापस ERR_PTR(devid);

	list_क्रम_each_entry(p, &acpihid_map, list) अणु
		अगर ((devid == p->devid) && p->group)
			entry->group = p->group;
	पूर्ण

	अगर (!entry->group)
		entry->group = generic_device_group(dev);
	अन्यथा
		iommu_group_ref_get(entry->group);

	वापस entry->group;
पूर्ण

अटल bool pci_iommuv2_capable(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर पूर्णांक caps[] = अणु
		PCI_EXT_CAP_ID_PRI,
		PCI_EXT_CAP_ID_PASID,
	पूर्ण;
	पूर्णांक i, pos;

	अगर (!pci_ats_supported(pdev))
		वापस false;

	क्रम (i = 0; i < 2; ++i) अणु
		pos = pci_find_ext_capability(pdev, caps[i]);
		अगर (pos == 0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * This function checks अगर the driver got a valid device from the caller to
 * aव्योम dereferencing invalid poपूर्णांकers.
 */
अटल bool check_device(काष्ठा device *dev)
अणु
	पूर्णांक devid;

	अगर (!dev)
		वापस false;

	devid = get_device_id(dev);
	अगर (devid < 0)
		वापस false;

	/* Out of our scope? */
	अगर (devid > amd_iommu_last_bdf)
		वापस false;

	अगर (amd_iommu_rlookup_table[devid] == शून्य)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक iommu_init_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_dev_data *dev_data;
	पूर्णांक devid;

	अगर (dev_iommu_priv_get(dev))
		वापस 0;

	devid = get_device_id(dev);
	अगर (devid < 0)
		वापस devid;

	dev_data = find_dev_data(devid);
	अगर (!dev_data)
		वापस -ENOMEM;

	dev_data->pdev = setup_aliases(dev);

	/*
	 * By शेष we use passthrough mode क्रम IOMMUv2 capable device.
	 * But अगर amd_iommu=क्रमce_isolation is set (e.g. to debug DMA to
	 * invalid address), we ignore the capability क्रम the device so
	 * it'll be क्रमced to go पूर्णांकo translation mode.
	 */
	अगर ((iommu_शेष_passthrough() || !amd_iommu_क्रमce_isolation) &&
	    dev_is_pci(dev) && pci_iommuv2_capable(to_pci_dev(dev))) अणु
		काष्ठा amd_iommu *iommu;

		iommu = amd_iommu_rlookup_table[dev_data->devid];
		dev_data->iommu_v2 = iommu->is_iommu_v2;
	पूर्ण

	dev_iommu_priv_set(dev, dev_data);

	वापस 0;
पूर्ण

अटल व्योम iommu_ignore_device(काष्ठा device *dev)
अणु
	पूर्णांक devid;

	devid = get_device_id(dev);
	अगर (devid < 0)
		वापस;

	amd_iommu_rlookup_table[devid] = शून्य;
	स_रखो(&amd_iommu_dev_table[devid], 0, माप(काष्ठा dev_table_entry));

	setup_aliases(dev);
पूर्ण

अटल व्योम amd_iommu_uninit_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_dev_data *dev_data;

	dev_data = dev_iommu_priv_get(dev);
	अगर (!dev_data)
		वापस;

	अगर (dev_data->करोमुख्य)
		detach_device(dev);

	dev_iommu_priv_set(dev, शून्य);

	/*
	 * We keep dev_data around क्रम unplugged devices and reuse it when the
	 * device is re-plugged - not करोing so would पूर्णांकroduce a ton of races.
	 */
पूर्ण

/****************************************************************************
 *
 * Interrupt handling functions
 *
 ****************************************************************************/

अटल व्योम dump_dte_entry(u16 devid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		pr_err("DTE[%d]: %016llx\n", i,
			amd_iommu_dev_table[devid].data[i]);
पूर्ण

अटल व्योम dump_command(अचिन्हित दीर्घ phys_addr)
अणु
	काष्ठा iommu_cmd *cmd = iommu_phys_to_virt(phys_addr);
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		pr_err("CMD[%d]: %08x\n", i, cmd->data[i]);
पूर्ण

अटल व्योम amd_iommu_report_rmp_hw_error(अस्थिर u32 *event)
अणु
	काष्ठा iommu_dev_data *dev_data = शून्य;
	पूर्णांक devid, vmg_tag, flags;
	काष्ठा pci_dev *pdev;
	u64 spa;

	devid   = (event[0] >> EVENT_DEVID_SHIFT) & EVENT_DEVID_MASK;
	vmg_tag = (event[1]) & 0xFFFF;
	flags   = (event[1] >> EVENT_FLAGS_SHIFT) & EVENT_FLAGS_MASK;
	spa     = ((u64)event[3] << 32) | (event[2] & 0xFFFFFFF8);

	pdev = pci_get_करोमुख्य_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	अगर (pdev)
		dev_data = dev_iommu_priv_get(&pdev->dev);

	अगर (dev_data && __ratelimit(&dev_data->rs)) अणु
		pci_err(pdev, "Event logged [RMP_HW_ERROR vmg_tag=0x%04x, spa=0x%llx, flags=0x%04x]\n",
			vmg_tag, spa, flags);
	पूर्ण अन्यथा अणु
		pr_err_ratelimited("Event logged [RMP_HW_ERROR device=%02x:%02x.%x, vmg_tag=0x%04x, spa=0x%llx, flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			vmg_tag, spa, flags);
	पूर्ण

	अगर (pdev)
		pci_dev_put(pdev);
पूर्ण

अटल व्योम amd_iommu_report_rmp_fault(अस्थिर u32 *event)
अणु
	काष्ठा iommu_dev_data *dev_data = शून्य;
	पूर्णांक devid, flags_rmp, vmg_tag, flags;
	काष्ठा pci_dev *pdev;
	u64 gpa;

	devid     = (event[0] >> EVENT_DEVID_SHIFT) & EVENT_DEVID_MASK;
	flags_rmp = (event[0] >> EVENT_FLAGS_SHIFT) & 0xFF;
	vmg_tag   = (event[1]) & 0xFFFF;
	flags     = (event[1] >> EVENT_FLAGS_SHIFT) & EVENT_FLAGS_MASK;
	gpa       = ((u64)event[3] << 32) | event[2];

	pdev = pci_get_करोमुख्य_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	अगर (pdev)
		dev_data = dev_iommu_priv_get(&pdev->dev);

	अगर (dev_data && __ratelimit(&dev_data->rs)) अणु
		pci_err(pdev, "Event logged [RMP_PAGE_FAULT vmg_tag=0x%04x, gpa=0x%llx, flags_rmp=0x%04x, flags=0x%04x]\n",
			vmg_tag, gpa, flags_rmp, flags);
	पूर्ण अन्यथा अणु
		pr_err_ratelimited("Event logged [RMP_PAGE_FAULT device=%02x:%02x.%x, vmg_tag=0x%04x, gpa=0x%llx, flags_rmp=0x%04x, flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			vmg_tag, gpa, flags_rmp, flags);
	पूर्ण

	अगर (pdev)
		pci_dev_put(pdev);
पूर्ण

अटल व्योम amd_iommu_report_page_fault(u16 devid, u16 करोमुख्य_id,
					u64 address, पूर्णांक flags)
अणु
	काष्ठा iommu_dev_data *dev_data = शून्य;
	काष्ठा pci_dev *pdev;

	pdev = pci_get_करोमुख्य_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	अगर (pdev)
		dev_data = dev_iommu_priv_get(&pdev->dev);

	अगर (dev_data && __ratelimit(&dev_data->rs)) अणु
		pci_err(pdev, "Event logged [IO_PAGE_FAULT domain=0x%04x address=0x%llx flags=0x%04x]\n",
			करोमुख्य_id, address, flags);
	पूर्ण अन्यथा अगर (prपूर्णांकk_ratelimit()) अणु
		pr_err("Event logged [IO_PAGE_FAULT device=%02x:%02x.%x domain=0x%04x address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			करोमुख्य_id, address, flags);
	पूर्ण

	अगर (pdev)
		pci_dev_put(pdev);
पूर्ण

अटल व्योम iommu_prपूर्णांक_event(काष्ठा amd_iommu *iommu, व्योम *__evt)
अणु
	काष्ठा device *dev = iommu->iommu.dev;
	पूर्णांक type, devid, flags, tag;
	अस्थिर u32 *event = __evt;
	पूर्णांक count = 0;
	u64 address;
	u32 pasid;

retry:
	type    = (event[1] >> EVENT_TYPE_SHIFT)  & EVENT_TYPE_MASK;
	devid   = (event[0] >> EVENT_DEVID_SHIFT) & EVENT_DEVID_MASK;
	pasid   = (event[0] & EVENT_DOMID_MASK_HI) |
		  (event[1] & EVENT_DOMID_MASK_LO);
	flags   = (event[1] >> EVENT_FLAGS_SHIFT) & EVENT_FLAGS_MASK;
	address = (u64)(((u64)event[3]) << 32) | event[2];

	अगर (type == 0) अणु
		/* Did we hit the erratum? */
		अगर (++count == LOOP_TIMEOUT) अणु
			pr_err("No event written to event log\n");
			वापस;
		पूर्ण
		udelay(1);
		जाओ retry;
	पूर्ण

	अगर (type == EVENT_TYPE_IO_FAULT) अणु
		amd_iommu_report_page_fault(devid, pasid, address, flags);
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल EVENT_TYPE_ILL_DEV:
		dev_err(dev, "Event logged [ILLEGAL_DEV_TABLE_ENTRY device=%02x:%02x.%x pasid=0x%05x address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			pasid, address, flags);
		dump_dte_entry(devid);
		अवरोध;
	हाल EVENT_TYPE_DEV_TAB_ERR:
		dev_err(dev, "Event logged [DEV_TAB_HARDWARE_ERROR device=%02x:%02x.%x "
			"address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			address, flags);
		अवरोध;
	हाल EVENT_TYPE_PAGE_TAB_ERR:
		dev_err(dev, "Event logged [PAGE_TAB_HARDWARE_ERROR device=%02x:%02x.%x pasid=0x%04x address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			pasid, address, flags);
		अवरोध;
	हाल EVENT_TYPE_ILL_CMD:
		dev_err(dev, "Event logged [ILLEGAL_COMMAND_ERROR address=0x%llx]\n", address);
		dump_command(address);
		अवरोध;
	हाल EVENT_TYPE_CMD_HARD_ERR:
		dev_err(dev, "Event logged [COMMAND_HARDWARE_ERROR address=0x%llx flags=0x%04x]\n",
			address, flags);
		अवरोध;
	हाल EVENT_TYPE_IOTLB_INV_TO:
		dev_err(dev, "Event logged [IOTLB_INV_TIMEOUT device=%02x:%02x.%x address=0x%llx]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			address);
		अवरोध;
	हाल EVENT_TYPE_INV_DEV_REQ:
		dev_err(dev, "Event logged [INVALID_DEVICE_REQUEST device=%02x:%02x.%x pasid=0x%05x address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			pasid, address, flags);
		अवरोध;
	हाल EVENT_TYPE_RMP_FAULT:
		amd_iommu_report_rmp_fault(event);
		अवरोध;
	हाल EVENT_TYPE_RMP_HW_ERR:
		amd_iommu_report_rmp_hw_error(event);
		अवरोध;
	हाल EVENT_TYPE_INV_PPR_REQ:
		pasid = PPR_PASID(*((u64 *)__evt));
		tag = event[1] & 0x03FF;
		dev_err(dev, "Event logged [INVALID_PPR_REQUEST device=%02x:%02x.%x pasid=0x%05x address=0x%llx flags=0x%04x tag=0x%03x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			pasid, address, flags, tag);
		अवरोध;
	शेष:
		dev_err(dev, "Event logged [UNKNOWN event[0]=0x%08x event[1]=0x%08x event[2]=0x%08x event[3]=0x%08x\n",
			event[0], event[1], event[2], event[3]);
	पूर्ण

	स_रखो(__evt, 0, 4 * माप(u32));
पूर्ण

अटल व्योम iommu_poll_events(काष्ठा amd_iommu *iommu)
अणु
	u32 head, tail;

	head = पढ़ोl(iommu->mmio_base + MMIO_EVT_HEAD_OFFSET);
	tail = पढ़ोl(iommu->mmio_base + MMIO_EVT_TAIL_OFFSET);

	जबतक (head != tail) अणु
		iommu_prपूर्णांक_event(iommu, iommu->evt_buf + head);
		head = (head + EVENT_ENTRY_SIZE) % EVT_BUFFER_SIZE;
	पूर्ण

	ग_लिखोl(head, iommu->mmio_base + MMIO_EVT_HEAD_OFFSET);
पूर्ण

अटल व्योम iommu_handle_ppr_entry(काष्ठा amd_iommu *iommu, u64 *raw)
अणु
	काष्ठा amd_iommu_fault fault;

	अगर (PPR_REQ_TYPE(raw[0]) != PPR_REQ_FAULT) अणु
		pr_err_ratelimited("Unknown PPR request received\n");
		वापस;
	पूर्ण

	fault.address   = raw[1];
	fault.pasid     = PPR_PASID(raw[0]);
	fault.device_id = PPR_DEVID(raw[0]);
	fault.tag       = PPR_TAG(raw[0]);
	fault.flags     = PPR_FLAGS(raw[0]);

	atomic_notअगरier_call_chain(&ppr_notअगरier, 0, &fault);
पूर्ण

अटल व्योम iommu_poll_ppr_log(काष्ठा amd_iommu *iommu)
अणु
	u32 head, tail;

	अगर (iommu->ppr_log == शून्य)
		वापस;

	head = पढ़ोl(iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);
	tail = पढ़ोl(iommu->mmio_base + MMIO_PPR_TAIL_OFFSET);

	जबतक (head != tail) अणु
		अस्थिर u64 *raw;
		u64 entry[2];
		पूर्णांक i;

		raw = (u64 *)(iommu->ppr_log + head);

		/*
		 * Hardware bug: Interrupt may arrive beक्रमe the entry is
		 * written to memory. If this happens we need to रुको क्रम the
		 * entry to arrive.
		 */
		क्रम (i = 0; i < LOOP_TIMEOUT; ++i) अणु
			अगर (PPR_REQ_TYPE(raw[0]) != 0)
				अवरोध;
			udelay(1);
		पूर्ण

		/* Aव्योम स_नकल function-call overhead */
		entry[0] = raw[0];
		entry[1] = raw[1];

		/*
		 * To detect the hardware bug we need to clear the entry
		 * back to zero.
		 */
		raw[0] = raw[1] = 0UL;

		/* Update head poपूर्णांकer of hardware ring-buffer */
		head = (head + PPR_ENTRY_SIZE) % PPR_LOG_SIZE;
		ग_लिखोl(head, iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);

		/* Handle PPR entry */
		iommu_handle_ppr_entry(iommu, entry);

		/* Refresh ring-buffer inक्रमmation */
		head = पढ़ोl(iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);
		tail = पढ़ोl(iommu->mmio_base + MMIO_PPR_TAIL_OFFSET);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
अटल पूर्णांक (*iommu_ga_log_notअगरier)(u32);

पूर्णांक amd_iommu_रेजिस्टर_ga_log_notअगरier(पूर्णांक (*notअगरier)(u32))
अणु
	iommu_ga_log_notअगरier = notअगरier;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amd_iommu_रेजिस्टर_ga_log_notअगरier);

अटल व्योम iommu_poll_ga_log(काष्ठा amd_iommu *iommu)
अणु
	u32 head, tail, cnt = 0;

	अगर (iommu->ga_log == शून्य)
		वापस;

	head = पढ़ोl(iommu->mmio_base + MMIO_GA_HEAD_OFFSET);
	tail = पढ़ोl(iommu->mmio_base + MMIO_GA_TAIL_OFFSET);

	जबतक (head != tail) अणु
		अस्थिर u64 *raw;
		u64 log_entry;

		raw = (u64 *)(iommu->ga_log + head);
		cnt++;

		/* Aव्योम स_नकल function-call overhead */
		log_entry = *raw;

		/* Update head poपूर्णांकer of hardware ring-buffer */
		head = (head + GA_ENTRY_SIZE) % GA_LOG_SIZE;
		ग_लिखोl(head, iommu->mmio_base + MMIO_GA_HEAD_OFFSET);

		/* Handle GA entry */
		चयन (GA_REQ_TYPE(log_entry)) अणु
		हाल GA_GUEST_NR:
			अगर (!iommu_ga_log_notअगरier)
				अवरोध;

			pr_debug("%s: devid=%#x, ga_tag=%#x\n",
				 __func__, GA_DEVID(log_entry),
				 GA_TAG(log_entry));

			अगर (iommu_ga_log_notअगरier(GA_TAG(log_entry)) != 0)
				pr_err("GA log notifier failed.\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
amd_iommu_set_pci_msi_करोमुख्य(काष्ठा device *dev, काष्ठा amd_iommu *iommu)
अणु
	अगर (!irq_remapping_enabled || !dev_is_pci(dev) ||
	    pci_dev_has_special_msi_करोमुख्य(to_pci_dev(dev)))
		वापस;

	dev_set_msi_करोमुख्य(dev, iommu->msi_करोमुख्य);
पूर्ण

#अन्यथा /* CONFIG_IRQ_REMAP */
अटल अंतरभूत व्योम
amd_iommu_set_pci_msi_करोमुख्य(काष्ठा device *dev, काष्ठा amd_iommu *iommu) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_IRQ_REMAP */

#घोषणा AMD_IOMMU_INT_MASK	\
	(MMIO_STATUS_EVT_INT_MASK | \
	 MMIO_STATUS_PPR_INT_MASK | \
	 MMIO_STATUS_GALOG_INT_MASK)

irqवापस_t amd_iommu_पूर्णांक_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा amd_iommu *iommu = (काष्ठा amd_iommu *) data;
	u32 status = पढ़ोl(iommu->mmio_base + MMIO_STATUS_OFFSET);

	जबतक (status & AMD_IOMMU_INT_MASK) अणु
		/* Enable EVT and PPR and GA पूर्णांकerrupts again */
		ग_लिखोl(AMD_IOMMU_INT_MASK,
			iommu->mmio_base + MMIO_STATUS_OFFSET);

		अगर (status & MMIO_STATUS_EVT_INT_MASK) अणु
			pr_devel("Processing IOMMU Event Log\n");
			iommu_poll_events(iommu);
		पूर्ण

		अगर (status & MMIO_STATUS_PPR_INT_MASK) अणु
			pr_devel("Processing IOMMU PPR Log\n");
			iommu_poll_ppr_log(iommu);
		पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
		अगर (status & MMIO_STATUS_GALOG_INT_MASK) अणु
			pr_devel("Processing IOMMU GA Log\n");
			iommu_poll_ga_log(iommu);
		पूर्ण
#पूर्ण_अगर

		/*
		 * Hardware bug: ERBT1312
		 * When re-enabling पूर्णांकerrupt (by writing 1
		 * to clear the bit), the hardware might also try to set
		 * the पूर्णांकerrupt bit in the event status रेजिस्टर.
		 * In this scenario, the bit will be set, and disable
		 * subsequent पूर्णांकerrupts.
		 *
		 * Workaround: The IOMMU driver should पढ़ो back the
		 * status रेजिस्टर and check अगर the पूर्णांकerrupt bits are cleared.
		 * If not, driver will need to go through the पूर्णांकerrupt handler
		 * again and re-clear the bits
		 */
		status = पढ़ोl(iommu->mmio_base + MMIO_STATUS_OFFSET);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t amd_iommu_पूर्णांक_handler(पूर्णांक irq, व्योम *data)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

/****************************************************************************
 *
 * IOMMU command queuing functions
 *
 ****************************************************************************/

अटल पूर्णांक रुको_on_sem(काष्ठा amd_iommu *iommu, u64 data)
अणु
	पूर्णांक i = 0;

	जबतक (*iommu->cmd_sem != data && i < LOOP_TIMEOUT) अणु
		udelay(1);
		i += 1;
	पूर्ण

	अगर (i == LOOP_TIMEOUT) अणु
		pr_alert("Completion-Wait loop timed out\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम copy_cmd_to_buffer(काष्ठा amd_iommu *iommu,
			       काष्ठा iommu_cmd *cmd)
अणु
	u8 *target;
	u32 tail;

	/* Copy command to buffer */
	tail = iommu->cmd_buf_tail;
	target = iommu->cmd_buf + tail;
	स_नकल(target, cmd, माप(*cmd));

	tail = (tail + माप(*cmd)) % CMD_BUFFER_SIZE;
	iommu->cmd_buf_tail = tail;

	/* Tell the IOMMU about it */
	ग_लिखोl(tail, iommu->mmio_base + MMIO_CMD_TAIL_OFFSET);
पूर्ण

अटल व्योम build_completion_रुको(काष्ठा iommu_cmd *cmd,
				  काष्ठा amd_iommu *iommu,
				  u64 data)
अणु
	u64 paddr = iommu_virt_to_phys((व्योम *)iommu->cmd_sem);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->data[0] = lower_32_bits(paddr) | CMD_COMPL_WAIT_STORE_MASK;
	cmd->data[1] = upper_32_bits(paddr);
	cmd->data[2] = data;
	CMD_SET_TYPE(cmd, CMD_COMPL_WAIT);
पूर्ण

अटल व्योम build_inv_dte(काष्ठा iommu_cmd *cmd, u16 devid)
अणु
	स_रखो(cmd, 0, माप(*cmd));
	cmd->data[0] = devid;
	CMD_SET_TYPE(cmd, CMD_INV_DEV_ENTRY);
पूर्ण

/*
 * Builds an invalidation address which is suitable क्रम one page or multiple
 * pages. Sets the size bit (S) as needed is more than one page is flushed.
 */
अटल अंतरभूत u64 build_inv_address(u64 address, माप_प्रकार size)
अणु
	u64 pages, end, msb_dअगरf;

	pages = iommu_num_pages(address, size, PAGE_SIZE);

	अगर (pages == 1)
		वापस address & PAGE_MASK;

	end = address + size - 1;

	/*
	 * msb_dअगरf would hold the index of the most signअगरicant bit that
	 * flipped between the start and end.
	 */
	msb_dअगरf = fls64(end ^ address) - 1;

	/*
	 * Bits 63:52 are sign extended. If क्रम some reason bit 51 is dअगरferent
	 * between the start and the end, invalidate everything.
	 */
	अगर (unlikely(msb_dअगरf > 51)) अणु
		address = CMD_INV_IOMMU_ALL_PAGES_ADDRESS;
	पूर्ण अन्यथा अणु
		/*
		 * The msb-bit must be clear on the address. Just set all the
		 * lower bits.
		 */
		address |= (1ull << msb_dअगरf) - 1;
	पूर्ण

	/* Clear bits 11:0 */
	address &= PAGE_MASK;

	/* Set the size bit - we flush more than one 4kb page */
	वापस address | CMD_INV_IOMMU_PAGES_SIZE_MASK;
पूर्ण

अटल व्योम build_inv_iommu_pages(काष्ठा iommu_cmd *cmd, u64 address,
				  माप_प्रकार size, u16 करोmid, पूर्णांक pde)
अणु
	u64 inv_address = build_inv_address(address, size);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->data[1] |= करोmid;
	cmd->data[2]  = lower_32_bits(inv_address);
	cmd->data[3]  = upper_32_bits(inv_address);
	CMD_SET_TYPE(cmd, CMD_INV_IOMMU_PAGES);
	अगर (pde) /* PDE bit - we want to flush everything, not only the PTEs */
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_PDE_MASK;
पूर्ण

अटल व्योम build_inv_iotlb_pages(काष्ठा iommu_cmd *cmd, u16 devid, पूर्णांक qdep,
				  u64 address, माप_प्रकार size)
अणु
	u64 inv_address = build_inv_address(address, size);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->data[0]  = devid;
	cmd->data[0] |= (qdep & 0xff) << 24;
	cmd->data[1]  = devid;
	cmd->data[2]  = lower_32_bits(inv_address);
	cmd->data[3]  = upper_32_bits(inv_address);
	CMD_SET_TYPE(cmd, CMD_INV_IOTLB_PAGES);
पूर्ण

अटल व्योम build_inv_iommu_pasid(काष्ठा iommu_cmd *cmd, u16 करोmid, u32 pasid,
				  u64 address, bool size)
अणु
	स_रखो(cmd, 0, माप(*cmd));

	address &= ~(0xfffULL);

	cmd->data[0]  = pasid;
	cmd->data[1]  = करोmid;
	cmd->data[2]  = lower_32_bits(address);
	cmd->data[3]  = upper_32_bits(address);
	cmd->data[2] |= CMD_INV_IOMMU_PAGES_PDE_MASK;
	cmd->data[2] |= CMD_INV_IOMMU_PAGES_GN_MASK;
	अगर (size)
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_SIZE_MASK;
	CMD_SET_TYPE(cmd, CMD_INV_IOMMU_PAGES);
पूर्ण

अटल व्योम build_inv_iotlb_pasid(काष्ठा iommu_cmd *cmd, u16 devid, u32 pasid,
				  पूर्णांक qdep, u64 address, bool size)
अणु
	स_रखो(cmd, 0, माप(*cmd));

	address &= ~(0xfffULL);

	cmd->data[0]  = devid;
	cmd->data[0] |= ((pasid >> 8) & 0xff) << 16;
	cmd->data[0] |= (qdep  & 0xff) << 24;
	cmd->data[1]  = devid;
	cmd->data[1] |= (pasid & 0xff) << 16;
	cmd->data[2]  = lower_32_bits(address);
	cmd->data[2] |= CMD_INV_IOMMU_PAGES_GN_MASK;
	cmd->data[3]  = upper_32_bits(address);
	अगर (size)
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_SIZE_MASK;
	CMD_SET_TYPE(cmd, CMD_INV_IOTLB_PAGES);
पूर्ण

अटल व्योम build_complete_ppr(काष्ठा iommu_cmd *cmd, u16 devid, u32 pasid,
			       पूर्णांक status, पूर्णांक tag, bool gn)
अणु
	स_रखो(cmd, 0, माप(*cmd));

	cmd->data[0]  = devid;
	अगर (gn) अणु
		cmd->data[1]  = pasid;
		cmd->data[2]  = CMD_INV_IOMMU_PAGES_GN_MASK;
	पूर्ण
	cmd->data[3]  = tag & 0x1ff;
	cmd->data[3] |= (status & PPR_STATUS_MASK) << PPR_STATUS_SHIFT;

	CMD_SET_TYPE(cmd, CMD_COMPLETE_PPR);
पूर्ण

अटल व्योम build_inv_all(काष्ठा iommu_cmd *cmd)
अणु
	स_रखो(cmd, 0, माप(*cmd));
	CMD_SET_TYPE(cmd, CMD_INV_ALL);
पूर्ण

अटल व्योम build_inv_irt(काष्ठा iommu_cmd *cmd, u16 devid)
अणु
	स_रखो(cmd, 0, माप(*cmd));
	cmd->data[0] = devid;
	CMD_SET_TYPE(cmd, CMD_INV_IRT);
पूर्ण

/*
 * Writes the command to the IOMMUs command buffer and inक्रमms the
 * hardware about the new command.
 */
अटल पूर्णांक __iommu_queue_command_sync(काष्ठा amd_iommu *iommu,
				      काष्ठा iommu_cmd *cmd,
				      bool sync)
अणु
	अचिन्हित पूर्णांक count = 0;
	u32 left, next_tail;

	next_tail = (iommu->cmd_buf_tail + माप(*cmd)) % CMD_BUFFER_SIZE;
again:
	left      = (iommu->cmd_buf_head - next_tail) % CMD_BUFFER_SIZE;

	अगर (left <= 0x20) अणु
		/* Skip udelay() the first समय around */
		अगर (count++) अणु
			अगर (count == LOOP_TIMEOUT) अणु
				pr_err("Command buffer timeout\n");
				वापस -EIO;
			पूर्ण

			udelay(1);
		पूर्ण

		/* Update head and recheck reमुख्यing space */
		iommu->cmd_buf_head = पढ़ोl(iommu->mmio_base +
					    MMIO_CMD_HEAD_OFFSET);

		जाओ again;
	पूर्ण

	copy_cmd_to_buffer(iommu, cmd);

	/* Do we need to make sure all commands are processed? */
	iommu->need_sync = sync;

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_queue_command_sync(काष्ठा amd_iommu *iommu,
				    काष्ठा iommu_cmd *cmd,
				    bool sync)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&iommu->lock, flags);
	ret = __iommu_queue_command_sync(iommu, cmd, sync);
	raw_spin_unlock_irqrestore(&iommu->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक iommu_queue_command(काष्ठा amd_iommu *iommu, काष्ठा iommu_cmd *cmd)
अणु
	वापस iommu_queue_command_sync(iommu, cmd, true);
पूर्ण

/*
 * This function queues a completion रुको command पूर्णांकo the command
 * buffer of an IOMMU
 */
अटल पूर्णांक iommu_completion_रुको(काष्ठा amd_iommu *iommu)
अणु
	काष्ठा iommu_cmd cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u64 data;

	अगर (!iommu->need_sync)
		वापस 0;

	raw_spin_lock_irqsave(&iommu->lock, flags);

	data = ++iommu->cmd_sem_val;
	build_completion_रुको(&cmd, iommu, data);

	ret = __iommu_queue_command_sync(iommu, &cmd, false);
	अगर (ret)
		जाओ out_unlock;

	ret = रुको_on_sem(iommu, data);

out_unlock:
	raw_spin_unlock_irqrestore(&iommu->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक iommu_flush_dte(काष्ठा amd_iommu *iommu, u16 devid)
अणु
	काष्ठा iommu_cmd cmd;

	build_inv_dte(&cmd, devid);

	वापस iommu_queue_command(iommu, &cmd);
पूर्ण

अटल व्योम amd_iommu_flush_dte_all(काष्ठा amd_iommu *iommu)
अणु
	u32 devid;

	क्रम (devid = 0; devid <= 0xffff; ++devid)
		iommu_flush_dte(iommu, devid);

	iommu_completion_रुको(iommu);
पूर्ण

/*
 * This function uses heavy locking and may disable irqs क्रम some समय. But
 * this is no issue because it is only called during resume.
 */
अटल व्योम amd_iommu_flush_tlb_all(काष्ठा amd_iommu *iommu)
अणु
	u32 करोm_id;

	क्रम (करोm_id = 0; करोm_id <= 0xffff; ++करोm_id) अणु
		काष्ठा iommu_cmd cmd;
		build_inv_iommu_pages(&cmd, 0, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
				      करोm_id, 1);
		iommu_queue_command(iommu, &cmd);
	पूर्ण

	iommu_completion_रुको(iommu);
पूर्ण

अटल व्योम amd_iommu_flush_tlb_करोmid(काष्ठा amd_iommu *iommu, u32 करोm_id)
अणु
	काष्ठा iommu_cmd cmd;

	build_inv_iommu_pages(&cmd, 0, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
			      करोm_id, 1);
	iommu_queue_command(iommu, &cmd);

	iommu_completion_रुको(iommu);
पूर्ण

अटल व्योम amd_iommu_flush_all(काष्ठा amd_iommu *iommu)
अणु
	काष्ठा iommu_cmd cmd;

	build_inv_all(&cmd);

	iommu_queue_command(iommu, &cmd);
	iommu_completion_रुको(iommu);
पूर्ण

अटल व्योम iommu_flush_irt(काष्ठा amd_iommu *iommu, u16 devid)
अणु
	काष्ठा iommu_cmd cmd;

	build_inv_irt(&cmd, devid);

	iommu_queue_command(iommu, &cmd);
पूर्ण

अटल व्योम amd_iommu_flush_irt_all(काष्ठा amd_iommu *iommu)
अणु
	u32 devid;

	क्रम (devid = 0; devid <= MAX_DEV_TABLE_ENTRIES; devid++)
		iommu_flush_irt(iommu, devid);

	iommu_completion_रुको(iommu);
पूर्ण

व्योम iommu_flush_all_caches(काष्ठा amd_iommu *iommu)
अणु
	अगर (iommu_feature(iommu, FEATURE_IA)) अणु
		amd_iommu_flush_all(iommu);
	पूर्ण अन्यथा अणु
		amd_iommu_flush_dte_all(iommu);
		amd_iommu_flush_irt_all(iommu);
		amd_iommu_flush_tlb_all(iommu);
	पूर्ण
पूर्ण

/*
 * Command send function क्रम flushing on-device TLB
 */
अटल पूर्णांक device_flush_iotlb(काष्ठा iommu_dev_data *dev_data,
			      u64 address, माप_प्रकार size)
अणु
	काष्ठा amd_iommu *iommu;
	काष्ठा iommu_cmd cmd;
	पूर्णांक qdep;

	qdep     = dev_data->ats.qdep;
	iommu    = amd_iommu_rlookup_table[dev_data->devid];

	build_inv_iotlb_pages(&cmd, dev_data->devid, qdep, address, size);

	वापस iommu_queue_command(iommu, &cmd);
पूर्ण

अटल पूर्णांक device_flush_dte_alias(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	काष्ठा amd_iommu *iommu = data;

	वापस iommu_flush_dte(iommu, alias);
पूर्ण

/*
 * Command send function क्रम invalidating a device table entry
 */
अटल पूर्णांक device_flush_dte(काष्ठा iommu_dev_data *dev_data)
अणु
	काष्ठा amd_iommu *iommu;
	u16 alias;
	पूर्णांक ret;

	iommu = amd_iommu_rlookup_table[dev_data->devid];

	अगर (dev_data->pdev)
		ret = pci_क्रम_each_dma_alias(dev_data->pdev,
					     device_flush_dte_alias, iommu);
	अन्यथा
		ret = iommu_flush_dte(iommu, dev_data->devid);
	अगर (ret)
		वापस ret;

	alias = amd_iommu_alias_table[dev_data->devid];
	अगर (alias != dev_data->devid) अणु
		ret = iommu_flush_dte(iommu, alias);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev_data->ats.enabled)
		ret = device_flush_iotlb(dev_data, 0, ~0UL);

	वापस ret;
पूर्ण

/*
 * TLB invalidation function which is called from the mapping functions.
 * It invalidates a single PTE अगर the range to flush is within a single
 * page. Otherwise it flushes the whole TLB of the IOMMU.
 */
अटल व्योम __करोमुख्य_flush_pages(काष्ठा protection_करोमुख्य *करोमुख्य,
				 u64 address, माप_प्रकार size, पूर्णांक pde)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा iommu_cmd cmd;
	पूर्णांक ret = 0, i;

	build_inv_iommu_pages(&cmd, address, size, करोमुख्य->id, pde);

	क्रम (i = 0; i < amd_iommu_get_num_iommus(); ++i) अणु
		अगर (!करोमुख्य->dev_iommu[i])
			जारी;

		/*
		 * Devices of this करोमुख्य are behind this IOMMU
		 * We need a TLB flush
		 */
		ret |= iommu_queue_command(amd_iommus[i], &cmd);
	पूर्ण

	list_क्रम_each_entry(dev_data, &करोमुख्य->dev_list, list) अणु

		अगर (!dev_data->ats.enabled)
			जारी;

		ret |= device_flush_iotlb(dev_data, address, size);
	पूर्ण

	WARN_ON(ret);
पूर्ण

अटल व्योम करोमुख्य_flush_pages(काष्ठा protection_करोमुख्य *करोमुख्य,
			       u64 address, माप_प्रकार size)
अणु
	__करोमुख्य_flush_pages(करोमुख्य, address, size, 0);
पूर्ण

/* Flush the whole IO/TLB क्रम a given protection करोमुख्य - including PDE */
व्योम amd_iommu_करोमुख्य_flush_tlb_pde(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	__करोमुख्य_flush_pages(करोमुख्य, 0, CMD_INV_IOMMU_ALL_PAGES_ADDRESS, 1);
पूर्ण

व्योम amd_iommu_करोमुख्य_flush_complete(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < amd_iommu_get_num_iommus(); ++i) अणु
		अगर (करोमुख्य && !करोमुख्य->dev_iommu[i])
			जारी;

		/*
		 * Devices of this करोमुख्य are behind this IOMMU
		 * We need to रुको क्रम completion of all commands.
		 */
		iommu_completion_रुको(amd_iommus[i]);
	पूर्ण
पूर्ण

/* Flush the not present cache अगर it exists */
अटल व्योम करोमुख्य_flush_np_cache(काष्ठा protection_करोमुख्य *करोमुख्य,
		dma_addr_t iova, माप_प्रकार size)
अणु
	अगर (unlikely(amd_iommu_np_cache)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&करोमुख्य->lock, flags);
		करोमुख्य_flush_pages(करोमुख्य, iova, size);
		amd_iommu_करोमुख्य_flush_complete(करोमुख्य);
		spin_unlock_irqrestore(&करोमुख्य->lock, flags);
	पूर्ण
पूर्ण


/*
 * This function flushes the DTEs क्रम all devices in करोमुख्य
 */
अटल व्योम करोमुख्य_flush_devices(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dev_data *dev_data;

	list_क्रम_each_entry(dev_data, &करोमुख्य->dev_list, list)
		device_flush_dte(dev_data);
पूर्ण

/****************************************************************************
 *
 * The next functions beदीर्घ to the करोमुख्य allocation. A करोमुख्य is
 * allocated क्रम every IOMMU as the शेष करोमुख्य. If device isolation
 * is enabled, every device get its own करोमुख्य. The most important thing
 * about करोमुख्यs is the page table mapping the DMA address space they
 * contain.
 *
 ****************************************************************************/

अटल u16 करोमुख्य_id_alloc(व्योम)
अणु
	पूर्णांक id;

	spin_lock(&pd_biपंचांगap_lock);
	id = find_first_zero_bit(amd_iommu_pd_alloc_biपंचांगap, MAX_DOMAIN_ID);
	BUG_ON(id == 0);
	अगर (id > 0 && id < MAX_DOMAIN_ID)
		__set_bit(id, amd_iommu_pd_alloc_biपंचांगap);
	अन्यथा
		id = 0;
	spin_unlock(&pd_biपंचांगap_lock);

	वापस id;
पूर्ण

अटल व्योम करोमुख्य_id_मुक्त(पूर्णांक id)
अणु
	spin_lock(&pd_biपंचांगap_lock);
	अगर (id > 0 && id < MAX_DOMAIN_ID)
		__clear_bit(id, amd_iommu_pd_alloc_biपंचांगap);
	spin_unlock(&pd_biपंचांगap_lock);
पूर्ण

अटल व्योम मुक्त_gcr3_tbl_level1(u64 *tbl)
अणु
	u64 *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < 512; ++i) अणु
		अगर (!(tbl[i] & GCR3_VALID))
			जारी;

		ptr = iommu_phys_to_virt(tbl[i] & PAGE_MASK);

		मुक्त_page((अचिन्हित दीर्घ)ptr);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_gcr3_tbl_level2(u64 *tbl)
अणु
	u64 *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < 512; ++i) अणु
		अगर (!(tbl[i] & GCR3_VALID))
			जारी;

		ptr = iommu_phys_to_virt(tbl[i] & PAGE_MASK);

		मुक्त_gcr3_tbl_level1(ptr);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_gcr3_table(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	अगर (करोमुख्य->glx == 2)
		मुक्त_gcr3_tbl_level2(करोमुख्य->gcr3_tbl);
	अन्यथा अगर (करोमुख्य->glx == 1)
		मुक्त_gcr3_tbl_level1(करोमुख्य->gcr3_tbl);
	अन्यथा
		BUG_ON(करोमुख्य->glx != 0);

	मुक्त_page((अचिन्हित दीर्घ)करोमुख्य->gcr3_tbl);
पूर्ण

अटल व्योम set_dte_entry(u16 devid, काष्ठा protection_करोमुख्य *करोमुख्य,
			  bool ats, bool ppr)
अणु
	u64 pte_root = 0;
	u64 flags = 0;
	u32 old_करोmid;

	अगर (करोमुख्य->iop.mode != PAGE_MODE_NONE)
		pte_root = iommu_virt_to_phys(करोमुख्य->iop.root);

	pte_root |= (करोमुख्य->iop.mode & DEV_ENTRY_MODE_MASK)
		    << DEV_ENTRY_MODE_SHIFT;
	pte_root |= DTE_FLAG_IR | DTE_FLAG_IW | DTE_FLAG_V | DTE_FLAG_TV;

	flags = amd_iommu_dev_table[devid].data[1];

	अगर (ats)
		flags |= DTE_FLAG_IOTLB;

	अगर (ppr) अणु
		काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[devid];

		अगर (iommu_feature(iommu, FEATURE_EPHSUP))
			pte_root |= 1ULL << DEV_ENTRY_PPR;
	पूर्ण

	अगर (करोमुख्य->flags & PD_IOMMUV2_MASK) अणु
		u64 gcr3 = iommu_virt_to_phys(करोमुख्य->gcr3_tbl);
		u64 glx  = करोमुख्य->glx;
		u64 पंचांगp;

		pte_root |= DTE_FLAG_GV;
		pte_root |= (glx & DTE_GLX_MASK) << DTE_GLX_SHIFT;

		/* First mask out possible old values क्रम GCR3 table */
		पंचांगp = DTE_GCR3_VAL_B(~0ULL) << DTE_GCR3_SHIFT_B;
		flags    &= ~पंचांगp;

		पंचांगp = DTE_GCR3_VAL_C(~0ULL) << DTE_GCR3_SHIFT_C;
		flags    &= ~पंचांगp;

		/* Encode GCR3 table पूर्णांकo DTE */
		पंचांगp = DTE_GCR3_VAL_A(gcr3) << DTE_GCR3_SHIFT_A;
		pte_root |= पंचांगp;

		पंचांगp = DTE_GCR3_VAL_B(gcr3) << DTE_GCR3_SHIFT_B;
		flags    |= पंचांगp;

		पंचांगp = DTE_GCR3_VAL_C(gcr3) << DTE_GCR3_SHIFT_C;
		flags    |= पंचांगp;
	पूर्ण

	flags &= ~DEV_DOMID_MASK;
	flags |= करोमुख्य->id;

	old_करोmid = amd_iommu_dev_table[devid].data[1] & DEV_DOMID_MASK;
	amd_iommu_dev_table[devid].data[1]  = flags;
	amd_iommu_dev_table[devid].data[0]  = pte_root;

	/*
	 * A kdump kernel might be replacing a करोमुख्य ID that was copied from
	 * the previous kernel--अगर so, it needs to flush the translation cache
	 * entries क्रम the old करोमुख्य ID that is being overwritten
	 */
	अगर (old_करोmid) अणु
		काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[devid];

		amd_iommu_flush_tlb_करोmid(iommu, old_करोmid);
	पूर्ण
पूर्ण

अटल व्योम clear_dte_entry(u16 devid)
अणु
	/* हटाओ entry from the device table seen by the hardware */
	amd_iommu_dev_table[devid].data[0]  = DTE_FLAG_V | DTE_FLAG_TV;
	amd_iommu_dev_table[devid].data[1] &= DTE_FLAG_MASK;

	amd_iommu_apply_erratum_63(devid);
पूर्ण

अटल व्योम करो_attach(काष्ठा iommu_dev_data *dev_data,
		      काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	काष्ठा amd_iommu *iommu;
	bool ats;

	iommu = amd_iommu_rlookup_table[dev_data->devid];
	ats   = dev_data->ats.enabled;

	/* Update data काष्ठाures */
	dev_data->करोमुख्य = करोमुख्य;
	list_add(&dev_data->list, &करोमुख्य->dev_list);

	/* Do reference counting */
	करोमुख्य->dev_iommu[iommu->index] += 1;
	करोमुख्य->dev_cnt                 += 1;

	/* Update device table */
	set_dte_entry(dev_data->devid, करोमुख्य,
		      ats, dev_data->iommu_v2);
	clone_aliases(dev_data->pdev);

	device_flush_dte(dev_data);
पूर्ण

अटल व्योम करो_detach(काष्ठा iommu_dev_data *dev_data)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = dev_data->करोमुख्य;
	काष्ठा amd_iommu *iommu;

	iommu = amd_iommu_rlookup_table[dev_data->devid];

	/* Update data काष्ठाures */
	dev_data->करोमुख्य = शून्य;
	list_del(&dev_data->list);
	clear_dte_entry(dev_data->devid);
	clone_aliases(dev_data->pdev);

	/* Flush the DTE entry */
	device_flush_dte(dev_data);

	/* Flush IOTLB */
	amd_iommu_करोमुख्य_flush_tlb_pde(करोमुख्य);

	/* Wait क्रम the flushes to finish */
	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);

	/* decrease reference counters - needs to happen after the flushes */
	करोमुख्य->dev_iommu[iommu->index] -= 1;
	करोमुख्य->dev_cnt                 -= 1;
पूर्ण

अटल व्योम pdev_iommuv2_disable(काष्ठा pci_dev *pdev)
अणु
	pci_disable_ats(pdev);
	pci_disable_pri(pdev);
	pci_disable_pasid(pdev);
पूर्ण

अटल पूर्णांक pdev_iommuv2_enable(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	/* Only allow access to user-accessible pages */
	ret = pci_enable_pasid(pdev, 0);
	अगर (ret)
		जाओ out_err;

	/* First reset the PRI state of the device */
	ret = pci_reset_pri(pdev);
	अगर (ret)
		जाओ out_err;

	/* Enable PRI */
	/* FIXME: Hardcode number of outstanding requests क्रम now */
	ret = pci_enable_pri(pdev, 32);
	अगर (ret)
		जाओ out_err;

	ret = pci_enable_ats(pdev, PAGE_SHIFT);
	अगर (ret)
		जाओ out_err;

	वापस 0;

out_err:
	pci_disable_pri(pdev);
	pci_disable_pasid(pdev);

	वापस ret;
पूर्ण

/*
 * If a device is not yet associated with a करोमुख्य, this function makes the
 * device visible in the करोमुख्य
 */
अटल पूर्णांक attach_device(काष्ठा device *dev,
			 काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	dev_data = dev_iommu_priv_get(dev);

	spin_lock(&dev_data->lock);

	ret = -EBUSY;
	अगर (dev_data->करोमुख्य != शून्य)
		जाओ out;

	अगर (!dev_is_pci(dev))
		जाओ skip_ats_check;

	pdev = to_pci_dev(dev);
	अगर (करोमुख्य->flags & PD_IOMMUV2_MASK) अणु
		काष्ठा iommu_करोमुख्य *def_करोमुख्य = iommu_get_dma_करोमुख्य(dev);

		ret = -EINVAL;
		अगर (def_करोमुख्य->type != IOMMU_DOMAIN_IDENTITY)
			जाओ out;

		अगर (dev_data->iommu_v2) अणु
			अगर (pdev_iommuv2_enable(pdev) != 0)
				जाओ out;

			dev_data->ats.enabled = true;
			dev_data->ats.qdep    = pci_ats_queue_depth(pdev);
			dev_data->pri_tlp     = pci_prg_resp_pasid_required(pdev);
		पूर्ण
	पूर्ण अन्यथा अगर (amd_iommu_iotlb_sup &&
		   pci_enable_ats(pdev, PAGE_SHIFT) == 0) अणु
		dev_data->ats.enabled = true;
		dev_data->ats.qdep    = pci_ats_queue_depth(pdev);
	पूर्ण

skip_ats_check:
	ret = 0;

	करो_attach(dev_data, करोमुख्य);

	/*
	 * We might boot पूर्णांकo a crash-kernel here. The crashed kernel
	 * left the caches in the IOMMU dirty. So we have to flush
	 * here to evict all dirty stuff.
	 */
	amd_iommu_करोमुख्य_flush_tlb_pde(करोमुख्य);

	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);

out:
	spin_unlock(&dev_data->lock);

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण

/*
 * Removes a device from a protection करोमुख्य (with devtable_lock held)
 */
अटल व्योम detach_device(काष्ठा device *dev)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य;
	काष्ठा iommu_dev_data *dev_data;
	अचिन्हित दीर्घ flags;

	dev_data = dev_iommu_priv_get(dev);
	करोमुख्य   = dev_data->करोमुख्य;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	spin_lock(&dev_data->lock);

	/*
	 * First check अगर the device is still attached. It might alपढ़ोy
	 * be detached from its करोमुख्य because the generic
	 * iommu_detach_group code detached it and we try again here in
	 * our alias handling.
	 */
	अगर (WARN_ON(!dev_data->करोमुख्य))
		जाओ out;

	करो_detach(dev_data);

	अगर (!dev_is_pci(dev))
		जाओ out;

	अगर (करोमुख्य->flags & PD_IOMMUV2_MASK && dev_data->iommu_v2)
		pdev_iommuv2_disable(to_pci_dev(dev));
	अन्यथा अगर (dev_data->ats.enabled)
		pci_disable_ats(to_pci_dev(dev));

	dev_data->ats.enabled = false;

out:
	spin_unlock(&dev_data->lock);

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);
पूर्ण

अटल काष्ठा iommu_device *amd_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_device *iommu_dev;
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret, devid;

	अगर (!check_device(dev))
		वापस ERR_PTR(-ENODEV);

	devid = get_device_id(dev);
	iommu = amd_iommu_rlookup_table[devid];

	अगर (dev_iommu_priv_get(dev))
		वापस &iommu->iommu;

	ret = iommu_init_device(dev);
	अगर (ret) अणु
		अगर (ret != -ENOTSUPP)
			dev_err(dev, "Failed to initialize - trying to proceed anyway\n");
		iommu_dev = ERR_PTR(ret);
		iommu_ignore_device(dev);
	पूर्ण अन्यथा अणु
		amd_iommu_set_pci_msi_करोमुख्य(dev, iommu);
		iommu_dev = &iommu->iommu;
	पूर्ण

	iommu_completion_रुको(iommu);

	वापस iommu_dev;
पूर्ण

अटल व्योम amd_iommu_probe_finalize(काष्ठा device *dev)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	/* Doमुख्यs are initialized क्रम this device - have a look what we ended up with */
	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (करोमुख्य->type == IOMMU_DOMAIN_DMA)
		iommu_setup_dma_ops(dev, IOVA_START_PFN << PAGE_SHIFT, 0);
	अन्यथा
		set_dma_ops(dev, शून्य);
पूर्ण

अटल व्योम amd_iommu_release_device(काष्ठा device *dev)
अणु
	पूर्णांक devid = get_device_id(dev);
	काष्ठा amd_iommu *iommu;

	अगर (!check_device(dev))
		वापस;

	iommu = amd_iommu_rlookup_table[devid];

	amd_iommu_uninit_device(dev);
	iommu_completion_रुको(iommu);
पूर्ण

अटल काष्ठा iommu_group *amd_iommu_device_group(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev))
		वापस pci_device_group(dev);

	वापस acpihid_device_group(dev);
पूर्ण

/*****************************************************************************
 *
 * The next functions beदीर्घ to the dma_ops mapping/unmapping code.
 *
 *****************************************************************************/

अटल व्योम update_device_table(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dev_data *dev_data;

	list_क्रम_each_entry(dev_data, &करोमुख्य->dev_list, list) अणु
		set_dte_entry(dev_data->devid, करोमुख्य,
			      dev_data->ats.enabled, dev_data->iommu_v2);
		clone_aliases(dev_data->pdev);
	पूर्ण
पूर्ण

व्योम amd_iommu_update_and_flush_device_table(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	update_device_table(करोमुख्य);
	करोमुख्य_flush_devices(करोमुख्य);
पूर्ण

व्योम amd_iommu_करोमुख्य_update(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	/* Update device table */
	amd_iommu_update_and_flush_device_table(करोमुख्य);

	/* Flush करोमुख्य TLB(s) and रुको क्रम completion */
	amd_iommu_करोमुख्य_flush_tlb_pde(करोमुख्य);
	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);
पूर्ण

पूर्णांक __init amd_iommu_init_api(व्योम)
अणु
	पूर्णांक ret, err = 0;

	ret = iova_cache_get();
	अगर (ret)
		वापस ret;

	err = bus_set_iommu(&pci_bus_type, &amd_iommu_ops);
	अगर (err)
		वापस err;
#अगर_घोषित CONFIG_ARM_AMBA
	err = bus_set_iommu(&amba_bustype, &amd_iommu_ops);
	अगर (err)
		वापस err;
#पूर्ण_अगर
	err = bus_set_iommu(&platक्रमm_bus_type, &amd_iommu_ops);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक __init amd_iommu_init_dma_ops(व्योम)
अणु
	swiotlb        = (iommu_शेष_passthrough() || sme_me_mask) ? 1 : 0;

	अगर (amd_iommu_unmap_flush)
		pr_info("IO/TLB flush on unmap enabled\n");
	अन्यथा
		pr_info("Lazy IO/TLB flushing enabled\n");
	iommu_set_dma_strict(amd_iommu_unmap_flush);
	वापस 0;

पूर्ण

/*****************************************************************************
 *
 * The following functions beदीर्घ to the exported पूर्णांकerface of AMD IOMMU
 *
 * This पूर्णांकerface allows access to lower level functions of the IOMMU
 * like protection करोमुख्य handling and assignement of devices to करोमुख्यs
 * which is not possible with the dma_ops पूर्णांकerface.
 *
 *****************************************************************************/

अटल व्योम cleanup_करोमुख्य(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dev_data *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	जबतक (!list_empty(&करोमुख्य->dev_list)) अणु
		entry = list_first_entry(&करोमुख्य->dev_list,
					 काष्ठा iommu_dev_data, list);
		BUG_ON(!entry->करोमुख्य);
		करो_detach(entry);
	पूर्ण

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);
पूर्ण

अटल व्योम protection_करोमुख्य_मुक्त(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	अगर (!करोमुख्य)
		वापस;

	अगर (करोमुख्य->id)
		करोमुख्य_id_मुक्त(करोमुख्य->id);

	अगर (करोमुख्य->iop.pgtbl_cfg.tlb)
		मुक्त_io_pgtable_ops(&करोमुख्य->iop.iop.ops);

	kमुक्त(करोमुख्य);
पूर्ण

अटल पूर्णांक protection_करोमुख्य_init_v1(काष्ठा protection_करोमुख्य *करोमुख्य, पूर्णांक mode)
अणु
	u64 *pt_root = शून्य;

	BUG_ON(mode < PAGE_MODE_NONE || mode > PAGE_MODE_6_LEVEL);

	spin_lock_init(&करोमुख्य->lock);
	करोमुख्य->id = करोमुख्य_id_alloc();
	अगर (!करोमुख्य->id)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&करोमुख्य->dev_list);

	अगर (mode != PAGE_MODE_NONE) अणु
		pt_root = (व्योम *)get_zeroed_page(GFP_KERNEL);
		अगर (!pt_root)
			वापस -ENOMEM;
	पूर्ण

	amd_iommu_करोमुख्य_set_pgtable(करोमुख्य, pt_root, mode);

	वापस 0;
पूर्ण

अटल काष्ठा protection_करोमुख्य *protection_करोमुख्य_alloc(अचिन्हित पूर्णांक type)
अणु
	काष्ठा io_pgtable_ops *pgtbl_ops;
	काष्ठा protection_करोमुख्य *करोमुख्य;
	पूर्णांक pgtable = amd_iommu_pgtable;
	पूर्णांक mode = DEFAULT_PGTABLE_LEVEL;
	पूर्णांक ret;

	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
	अगर (!करोमुख्य)
		वापस शून्य;

	/*
	 * Force IOMMU v1 page table when iommu=pt and
	 * when allocating करोमुख्य क्रम pass-through devices.
	 */
	अगर (type == IOMMU_DOMAIN_IDENTITY) अणु
		pgtable = AMD_IOMMU_V1;
		mode = PAGE_MODE_NONE;
	पूर्ण अन्यथा अगर (type == IOMMU_DOMAIN_UNMANAGED) अणु
		pgtable = AMD_IOMMU_V1;
	पूर्ण

	चयन (pgtable) अणु
	हाल AMD_IOMMU_V1:
		ret = protection_करोमुख्य_init_v1(करोमुख्य, mode);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		जाओ out_err;

	pgtbl_ops = alloc_io_pgtable_ops(pgtable, &करोमुख्य->iop.pgtbl_cfg, करोमुख्य);
	अगर (!pgtbl_ops)
		जाओ out_err;

	वापस करोमुख्य;
out_err:
	kमुक्त(करोमुख्य);
	वापस शून्य;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *amd_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य;

	करोमुख्य = protection_करोमुख्य_alloc(type);
	अगर (!करोमुख्य)
		वापस शून्य;

	करोमुख्य->करोमुख्य.geometry.aperture_start = 0;
	करोमुख्य->करोमुख्य.geometry.aperture_end   = ~0ULL;
	करोमुख्य->करोमुख्य.geometry.क्रमce_aperture = true;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&करोमुख्य->करोमुख्य) == -ENOMEM)
		जाओ मुक्त_करोमुख्य;

	वापस &करोमुख्य->करोमुख्य;

मुक्त_करोमुख्य:
	protection_करोमुख्य_मुक्त(करोमुख्य);

	वापस शून्य;
पूर्ण

अटल व्योम amd_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोm)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य;

	करोमुख्य = to_pकरोमुख्य(करोm);

	अगर (करोमुख्य->dev_cnt > 0)
		cleanup_करोमुख्य(करोमुख्य);

	BUG_ON(करोमुख्य->dev_cnt != 0);

	अगर (!करोm)
		वापस;

	अगर (करोm->type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&करोमुख्य->करोमुख्य);

	अगर (करोमुख्य->flags & PD_IOMMUV2_MASK)
		मुक्त_gcr3_table(करोमुख्य);

	protection_करोमुख्य_मुक्त(करोमुख्य);
पूर्ण

अटल व्योम amd_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोm,
				    काष्ठा device *dev)
अणु
	काष्ठा iommu_dev_data *dev_data = dev_iommu_priv_get(dev);
	पूर्णांक devid = get_device_id(dev);
	काष्ठा amd_iommu *iommu;

	अगर (!check_device(dev))
		वापस;

	अगर (dev_data->करोमुख्य != शून्य)
		detach_device(dev);

	iommu = amd_iommu_rlookup_table[devid];
	अगर (!iommu)
		वापस;

#अगर_घोषित CONFIG_IRQ_REMAP
	अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir) &&
	    (करोm->type == IOMMU_DOMAIN_UNMANAGED))
		dev_data->use_vapic = 0;
#पूर्ण_अगर

	iommu_completion_रुको(iommu);
पूर्ण

अटल पूर्णांक amd_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोm,
				   काष्ठा device *dev)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret;

	अगर (!check_device(dev))
		वापस -EINVAL;

	dev_data = dev_iommu_priv_get(dev);
	dev_data->defer_attach = false;

	iommu = amd_iommu_rlookup_table[dev_data->devid];
	अगर (!iommu)
		वापस -EINVAL;

	अगर (dev_data->करोमुख्य)
		detach_device(dev);

	ret = attach_device(dev, करोमुख्य);

#अगर_घोषित CONFIG_IRQ_REMAP
	अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir)) अणु
		अगर (करोm->type == IOMMU_DOMAIN_UNMANAGED)
			dev_data->use_vapic = 1;
		अन्यथा
			dev_data->use_vapic = 0;
	पूर्ण
#पूर्ण_अगर

	iommu_completion_रुको(iommu);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_iommu_map(काष्ठा iommu_करोमुख्य *करोm, अचिन्हित दीर्घ iova,
			 phys_addr_t paddr, माप_प्रकार page_size, पूर्णांक iommu_prot,
			 gfp_t gfp)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	काष्ठा io_pgtable_ops *ops = &करोमुख्य->iop.iop.ops;
	पूर्णांक prot = 0;
	पूर्णांक ret = -EINVAL;

	अगर ((amd_iommu_pgtable == AMD_IOMMU_V1) &&
	    (करोमुख्य->iop.mode == PAGE_MODE_NONE))
		वापस -EINVAL;

	अगर (iommu_prot & IOMMU_READ)
		prot |= IOMMU_PROT_IR;
	अगर (iommu_prot & IOMMU_WRITE)
		prot |= IOMMU_PROT_IW;

	अगर (ops->map) अणु
		ret = ops->map(ops, iova, paddr, page_size, prot, gfp);
		करोमुख्य_flush_np_cache(करोमुख्य, iova, page_size);
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार amd_iommu_unmap(काष्ठा iommu_करोमुख्य *करोm, अचिन्हित दीर्घ iova,
			      माप_प्रकार page_size,
			      काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	काष्ठा io_pgtable_ops *ops = &करोमुख्य->iop.iop.ops;

	अगर ((amd_iommu_pgtable == AMD_IOMMU_V1) &&
	    (करोमुख्य->iop.mode == PAGE_MODE_NONE))
		वापस 0;

	वापस (ops->unmap) ? ops->unmap(ops, iova, page_size, gather) : 0;
पूर्ण

अटल phys_addr_t amd_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोm,
					  dma_addr_t iova)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	काष्ठा io_pgtable_ops *ops = &करोमुख्य->iop.iop.ops;

	वापस ops->iova_to_phys(ops, iova);
पूर्ण

अटल bool amd_iommu_capable(क्रमागत iommu_cap cap)
अणु
	चयन (cap) अणु
	हाल IOMMU_CAP_CACHE_COHERENCY:
		वापस true;
	हाल IOMMU_CAP_INTR_REMAP:
		वापस (irq_remapping_enabled == 1);
	हाल IOMMU_CAP_NOEXEC:
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम amd_iommu_get_resv_regions(काष्ठा device *dev,
				       काष्ठा list_head *head)
अणु
	काष्ठा iommu_resv_region *region;
	काष्ठा unity_map_entry *entry;
	पूर्णांक devid;

	devid = get_device_id(dev);
	अगर (devid < 0)
		वापस;

	list_क्रम_each_entry(entry, &amd_iommu_unity_map, list) अणु
		पूर्णांक type, prot = 0;
		माप_प्रकार length;

		अगर (devid < entry->devid_start || devid > entry->devid_end)
			जारी;

		type   = IOMMU_RESV_सूचीECT;
		length = entry->address_end - entry->address_start;
		अगर (entry->prot & IOMMU_PROT_IR)
			prot |= IOMMU_READ;
		अगर (entry->prot & IOMMU_PROT_IW)
			prot |= IOMMU_WRITE;
		अगर (entry->prot & IOMMU_UNITY_MAP_FLAG_EXCL_RANGE)
			/* Exclusion range */
			type = IOMMU_RESV_RESERVED;

		region = iommu_alloc_resv_region(entry->address_start,
						 length, prot, type);
		अगर (!region) अणु
			dev_err(dev, "Out of memory allocating dm-regions\n");
			वापस;
		पूर्ण
		list_add_tail(&region->list, head);
	पूर्ण

	region = iommu_alloc_resv_region(MSI_RANGE_START,
					 MSI_RANGE_END - MSI_RANGE_START + 1,
					 0, IOMMU_RESV_MSI);
	अगर (!region)
		वापस;
	list_add_tail(&region->list, head);

	region = iommu_alloc_resv_region(HT_RANGE_START,
					 HT_RANGE_END - HT_RANGE_START + 1,
					 0, IOMMU_RESV_RESERVED);
	अगर (!region)
		वापस;
	list_add_tail(&region->list, head);
पूर्ण

bool amd_iommu_is_attach_deferred(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	काष्ठा iommu_dev_data *dev_data = dev_iommu_priv_get(dev);

	वापस dev_data->defer_attach;
पूर्ण
EXPORT_SYMBOL_GPL(amd_iommu_is_attach_deferred);

अटल व्योम amd_iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा protection_करोमुख्य *करोm = to_pकरोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&करोm->lock, flags);
	amd_iommu_करोमुख्य_flush_tlb_pde(करोm);
	amd_iommu_करोमुख्य_flush_complete(करोm);
	spin_unlock_irqrestore(&करोm->lock, flags);
पूर्ण

अटल व्योम amd_iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा iommu_iotlb_gather *gather)
अणु
	amd_iommu_flush_iotlb_all(करोमुख्य);
पूर्ण

अटल पूर्णांक amd_iommu_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	काष्ठा iommu_dev_data *dev_data;

	dev_data = dev_iommu_priv_get(dev);
	अगर (!dev_data)
		वापस 0;

	/*
	 * Do not identity map IOMMUv2 capable devices when memory encryption is
	 * active, because some of those devices (AMD GPUs) करोn't have the
	 * encryption bit in their DMA-mask and require remapping.
	 */
	अगर (!mem_encrypt_active() && dev_data->iommu_v2)
		वापस IOMMU_DOMAIN_IDENTITY;

	वापस 0;
पूर्ण

स्थिर काष्ठा iommu_ops amd_iommu_ops = अणु
	.capable = amd_iommu_capable,
	.करोमुख्य_alloc = amd_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त  = amd_iommu_करोमुख्य_मुक्त,
	.attach_dev = amd_iommu_attach_device,
	.detach_dev = amd_iommu_detach_device,
	.map = amd_iommu_map,
	.unmap = amd_iommu_unmap,
	.iova_to_phys = amd_iommu_iova_to_phys,
	.probe_device = amd_iommu_probe_device,
	.release_device = amd_iommu_release_device,
	.probe_finalize = amd_iommu_probe_finalize,
	.device_group = amd_iommu_device_group,
	.get_resv_regions = amd_iommu_get_resv_regions,
	.put_resv_regions = generic_iommu_put_resv_regions,
	.is_attach_deferred = amd_iommu_is_attach_deferred,
	.pgsize_biपंचांगap	= AMD_IOMMU_PGSIZES,
	.flush_iotlb_all = amd_iommu_flush_iotlb_all,
	.iotlb_sync = amd_iommu_iotlb_sync,
	.def_करोमुख्य_type = amd_iommu_def_करोमुख्य_type,
पूर्ण;

/*****************************************************************************
 *
 * The next functions करो a basic initialization of IOMMU क्रम pass through
 * mode
 *
 * In passthrough mode the IOMMU is initialized and enabled but not used क्रम
 * DMA-API translation.
 *
 *****************************************************************************/

/* IOMMUv2 specअगरic functions */
पूर्णांक amd_iommu_रेजिस्टर_ppr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&ppr_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL(amd_iommu_रेजिस्टर_ppr_notअगरier);

पूर्णांक amd_iommu_unरेजिस्टर_ppr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&ppr_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL(amd_iommu_unरेजिस्टर_ppr_notअगरier);

व्योम amd_iommu_करोमुख्य_direct_map(काष्ठा iommu_करोमुख्य *करोm)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	अगर (करोमुख्य->iop.pgtbl_cfg.tlb)
		मुक्त_io_pgtable_ops(&करोमुख्य->iop.iop.ops);

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);
पूर्ण
EXPORT_SYMBOL(amd_iommu_करोमुख्य_direct_map);

पूर्णांक amd_iommu_करोमुख्य_enable_v2(काष्ठा iommu_करोमुख्य *करोm, पूर्णांक pasids)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;
	पूर्णांक levels, ret;

	/* Number of GCR3 table levels required */
	क्रम (levels = 0; (pasids - 1) & ~0x1ff; pasids >>= 9)
		levels += 1;

	अगर (levels > amd_iommu_max_glx_val)
		वापस -EINVAL;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	/*
	 * Save us all sanity checks whether devices alपढ़ोy in the
	 * करोमुख्य support IOMMUv2. Just क्रमce that the करोमुख्य has no
	 * devices attached when it is चयनed पूर्णांकo IOMMUv2 mode.
	 */
	ret = -EBUSY;
	अगर (करोमुख्य->dev_cnt > 0 || करोमुख्य->flags & PD_IOMMUV2_MASK)
		जाओ out;

	ret = -ENOMEM;
	करोमुख्य->gcr3_tbl = (व्योम *)get_zeroed_page(GFP_ATOMIC);
	अगर (करोमुख्य->gcr3_tbl == शून्य)
		जाओ out;

	करोमुख्य->glx      = levels;
	करोमुख्य->flags   |= PD_IOMMUV2_MASK;

	amd_iommu_करोमुख्य_update(करोमुख्य);

	ret = 0;

out:
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_करोमुख्य_enable_v2);

अटल पूर्णांक __flush_pasid(काष्ठा protection_करोमुख्य *करोमुख्य, u32 pasid,
			 u64 address, bool size)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा iommu_cmd cmd;
	पूर्णांक i, ret;

	अगर (!(करोमुख्य->flags & PD_IOMMUV2_MASK))
		वापस -EINVAL;

	build_inv_iommu_pasid(&cmd, करोमुख्य->id, pasid, address, size);

	/*
	 * IOMMU TLB needs to be flushed beक्रमe Device TLB to
	 * prevent device TLB refill from IOMMU TLB
	 */
	क्रम (i = 0; i < amd_iommu_get_num_iommus(); ++i) अणु
		अगर (करोमुख्य->dev_iommu[i] == 0)
			जारी;

		ret = iommu_queue_command(amd_iommus[i], &cmd);
		अगर (ret != 0)
			जाओ out;
	पूर्ण

	/* Wait until IOMMU TLB flushes are complete */
	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);

	/* Now flush device TLBs */
	list_क्रम_each_entry(dev_data, &करोमुख्य->dev_list, list) अणु
		काष्ठा amd_iommu *iommu;
		पूर्णांक qdep;

		/*
		   There might be non-IOMMUv2 capable devices in an IOMMUv2
		 * करोमुख्य.
		 */
		अगर (!dev_data->ats.enabled)
			जारी;

		qdep  = dev_data->ats.qdep;
		iommu = amd_iommu_rlookup_table[dev_data->devid];

		build_inv_iotlb_pasid(&cmd, dev_data->devid, pasid,
				      qdep, address, size);

		ret = iommu_queue_command(iommu, &cmd);
		अगर (ret != 0)
			जाओ out;
	पूर्ण

	/* Wait until all device TLBs are flushed */
	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);

	ret = 0;

out:

	वापस ret;
पूर्ण

अटल पूर्णांक __amd_iommu_flush_page(काष्ठा protection_करोमुख्य *करोमुख्य, u32 pasid,
				  u64 address)
अणु
	वापस __flush_pasid(करोमुख्य, pasid, address, false);
पूर्ण

पूर्णांक amd_iommu_flush_page(काष्ठा iommu_करोमुख्य *करोm, u32 pasid,
			 u64 address)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	ret = __amd_iommu_flush_page(करोमुख्य, pasid, address);
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_flush_page);

अटल पूर्णांक __amd_iommu_flush_tlb(काष्ठा protection_करोमुख्य *करोमुख्य, u32 pasid)
अणु
	वापस __flush_pasid(करोमुख्य, pasid, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
			     true);
पूर्ण

पूर्णांक amd_iommu_flush_tlb(काष्ठा iommu_करोमुख्य *करोm, u32 pasid)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	ret = __amd_iommu_flush_tlb(करोमुख्य, pasid);
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_flush_tlb);

अटल u64 *__get_gcr3_pte(u64 *root, पूर्णांक level, u32 pasid, bool alloc)
अणु
	पूर्णांक index;
	u64 *pte;

	जबतक (true) अणु

		index = (pasid >> (9 * level)) & 0x1ff;
		pte   = &root[index];

		अगर (level == 0)
			अवरोध;

		अगर (!(*pte & GCR3_VALID)) अणु
			अगर (!alloc)
				वापस शून्य;

			root = (व्योम *)get_zeroed_page(GFP_ATOMIC);
			अगर (root == शून्य)
				वापस शून्य;

			*pte = iommu_virt_to_phys(root) | GCR3_VALID;
		पूर्ण

		root = iommu_phys_to_virt(*pte & PAGE_MASK);

		level -= 1;
	पूर्ण

	वापस pte;
पूर्ण

अटल पूर्णांक __set_gcr3(काष्ठा protection_करोमुख्य *करोमुख्य, u32 pasid,
		      अचिन्हित दीर्घ cr3)
अणु
	u64 *pte;

	अगर (करोमुख्य->iop.mode != PAGE_MODE_NONE)
		वापस -EINVAL;

	pte = __get_gcr3_pte(करोमुख्य->gcr3_tbl, करोमुख्य->glx, pasid, true);
	अगर (pte == शून्य)
		वापस -ENOMEM;

	*pte = (cr3 & PAGE_MASK) | GCR3_VALID;

	वापस __amd_iommu_flush_tlb(करोमुख्य, pasid);
पूर्ण

अटल पूर्णांक __clear_gcr3(काष्ठा protection_करोमुख्य *करोमुख्य, u32 pasid)
अणु
	u64 *pte;

	अगर (करोमुख्य->iop.mode != PAGE_MODE_NONE)
		वापस -EINVAL;

	pte = __get_gcr3_pte(करोमुख्य->gcr3_tbl, करोमुख्य->glx, pasid, false);
	अगर (pte == शून्य)
		वापस 0;

	*pte = 0;

	वापस __amd_iommu_flush_tlb(करोमुख्य, pasid);
पूर्ण

पूर्णांक amd_iommu_करोमुख्य_set_gcr3(काष्ठा iommu_करोमुख्य *करोm, u32 pasid,
			      अचिन्हित दीर्घ cr3)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	ret = __set_gcr3(करोमुख्य, pasid, cr3);
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_करोमुख्य_set_gcr3);

पूर्णांक amd_iommu_करोमुख्य_clear_gcr3(काष्ठा iommu_करोमुख्य *करोm, u32 pasid)
अणु
	काष्ठा protection_करोमुख्य *करोमुख्य = to_pकरोमुख्य(करोm);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	ret = __clear_gcr3(करोमुख्य, pasid);
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_करोमुख्य_clear_gcr3);

पूर्णांक amd_iommu_complete_ppr(काष्ठा pci_dev *pdev, u32 pasid,
			   पूर्णांक status, पूर्णांक tag)
अणु
	काष्ठा iommu_dev_data *dev_data;
	काष्ठा amd_iommu *iommu;
	काष्ठा iommu_cmd cmd;

	dev_data = dev_iommu_priv_get(&pdev->dev);
	iommu    = amd_iommu_rlookup_table[dev_data->devid];

	build_complete_ppr(&cmd, dev_data->devid, pasid, status,
			   tag, dev_data->pri_tlp);

	वापस iommu_queue_command(iommu, &cmd);
पूर्ण
EXPORT_SYMBOL(amd_iommu_complete_ppr);

पूर्णांक amd_iommu_device_info(काष्ठा pci_dev *pdev,
                          काष्ठा amd_iommu_device_info *info)
अणु
	पूर्णांक max_pasids;
	पूर्णांक pos;

	अगर (pdev == शून्य || info == शून्य)
		वापस -EINVAL;

	अगर (!amd_iommu_v2_supported())
		वापस -EINVAL;

	स_रखो(info, 0, माप(*info));

	अगर (pci_ats_supported(pdev))
		info->flags |= AMD_IOMMU_DEVICE_FLAG_ATS_SUP;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_PRI);
	अगर (pos)
		info->flags |= AMD_IOMMU_DEVICE_FLAG_PRI_SUP;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_PASID);
	अगर (pos) अणु
		पूर्णांक features;

		max_pasids = 1 << (9 * (amd_iommu_max_glx_val + 1));
		max_pasids = min(max_pasids, (1 << 20));

		info->flags |= AMD_IOMMU_DEVICE_FLAG_PASID_SUP;
		info->max_pasids = min(pci_max_pasids(pdev), max_pasids);

		features = pci_pasid_features(pdev);
		अगर (features & PCI_PASID_CAP_EXEC)
			info->flags |= AMD_IOMMU_DEVICE_FLAG_EXEC_SUP;
		अगर (features & PCI_PASID_CAP_PRIV)
			info->flags |= AMD_IOMMU_DEVICE_FLAG_PRIV_SUP;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amd_iommu_device_info);

#अगर_घोषित CONFIG_IRQ_REMAP

/*****************************************************************************
 *
 * Interrupt Remapping Implementation
 *
 *****************************************************************************/

अटल काष्ठा irq_chip amd_ir_chip;
अटल DEFINE_SPINLOCK(iommu_table_lock);

अटल व्योम set_dte_irq_entry(u16 devid, काष्ठा irq_remap_table *table)
अणु
	u64 dte;

	dte	= amd_iommu_dev_table[devid].data[2];
	dte	&= ~DTE_IRQ_PHYS_ADDR_MASK;
	dte	|= iommu_virt_to_phys(table->table);
	dte	|= DTE_IRQ_REMAP_INTCTL;
	dte	|= DTE_INTTABLEN;
	dte	|= DTE_IRQ_REMAP_ENABLE;

	amd_iommu_dev_table[devid].data[2] = dte;
पूर्ण

अटल काष्ठा irq_remap_table *get_irq_table(u16 devid)
अणु
	काष्ठा irq_remap_table *table;

	अगर (WARN_ONCE(!amd_iommu_rlookup_table[devid],
		      "%s: no iommu for devid %x\n", __func__, devid))
		वापस शून्य;

	table = irq_lookup_table[devid];
	अगर (WARN_ONCE(!table, "%s: no table for devid %x\n", __func__, devid))
		वापस शून्य;

	वापस table;
पूर्ण

अटल काष्ठा irq_remap_table *__alloc_irq_table(व्योम)
अणु
	काष्ठा irq_remap_table *table;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस शून्य;

	table->table = kmem_cache_alloc(amd_iommu_irq_cache, GFP_KERNEL);
	अगर (!table->table) अणु
		kमुक्त(table);
		वापस शून्य;
	पूर्ण
	raw_spin_lock_init(&table->lock);

	अगर (!AMD_IOMMU_GUEST_IR_GA(amd_iommu_guest_ir))
		स_रखो(table->table, 0,
		       MAX_IRQS_PER_TABLE * माप(u32));
	अन्यथा
		स_रखो(table->table, 0,
		       (MAX_IRQS_PER_TABLE * (माप(u64) * 2)));
	वापस table;
पूर्ण

अटल व्योम set_remap_table_entry(काष्ठा amd_iommu *iommu, u16 devid,
				  काष्ठा irq_remap_table *table)
अणु
	irq_lookup_table[devid] = table;
	set_dte_irq_entry(devid, table);
	iommu_flush_dte(iommu, devid);
पूर्ण

अटल पूर्णांक set_remap_table_entry_alias(काष्ठा pci_dev *pdev, u16 alias,
				       व्योम *data)
अणु
	काष्ठा irq_remap_table *table = data;

	irq_lookup_table[alias] = table;
	set_dte_irq_entry(alias, table);

	iommu_flush_dte(amd_iommu_rlookup_table[alias], alias);

	वापस 0;
पूर्ण

अटल काष्ठा irq_remap_table *alloc_irq_table(u16 devid, काष्ठा pci_dev *pdev)
अणु
	काष्ठा irq_remap_table *table = शून्य;
	काष्ठा irq_remap_table *new_table = शून्य;
	काष्ठा amd_iommu *iommu;
	अचिन्हित दीर्घ flags;
	u16 alias;

	spin_lock_irqsave(&iommu_table_lock, flags);

	iommu = amd_iommu_rlookup_table[devid];
	अगर (!iommu)
		जाओ out_unlock;

	table = irq_lookup_table[devid];
	अगर (table)
		जाओ out_unlock;

	alias = amd_iommu_alias_table[devid];
	table = irq_lookup_table[alias];
	अगर (table) अणु
		set_remap_table_entry(iommu, devid, table);
		जाओ out_रुको;
	पूर्ण
	spin_unlock_irqrestore(&iommu_table_lock, flags);

	/* Nothing there yet, allocate new irq remapping table */
	new_table = __alloc_irq_table();
	अगर (!new_table)
		वापस शून्य;

	spin_lock_irqsave(&iommu_table_lock, flags);

	table = irq_lookup_table[devid];
	अगर (table)
		जाओ out_unlock;

	table = irq_lookup_table[alias];
	अगर (table) अणु
		set_remap_table_entry(iommu, devid, table);
		जाओ out_रुको;
	पूर्ण

	table = new_table;
	new_table = शून्य;

	अगर (pdev)
		pci_क्रम_each_dma_alias(pdev, set_remap_table_entry_alias,
				       table);
	अन्यथा
		set_remap_table_entry(iommu, devid, table);

	अगर (devid != alias)
		set_remap_table_entry(iommu, alias, table);

out_रुको:
	iommu_completion_रुको(iommu);

out_unlock:
	spin_unlock_irqrestore(&iommu_table_lock, flags);

	अगर (new_table) अणु
		kmem_cache_मुक्त(amd_iommu_irq_cache, new_table->table);
		kमुक्त(new_table);
	पूर्ण
	वापस table;
पूर्ण

अटल पूर्णांक alloc_irq_index(u16 devid, पूर्णांक count, bool align,
			   काष्ठा pci_dev *pdev)
अणु
	काष्ठा irq_remap_table *table;
	पूर्णांक index, c, alignment = 1;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[devid];

	अगर (!iommu)
		वापस -ENODEV;

	table = alloc_irq_table(devid, pdev);
	अगर (!table)
		वापस -ENODEV;

	अगर (align)
		alignment = roundup_घात_of_two(count);

	raw_spin_lock_irqsave(&table->lock, flags);

	/* Scan table क्रम मुक्त entries */
	क्रम (index = ALIGN(table->min_index, alignment), c = 0;
	     index < MAX_IRQS_PER_TABLE;) अणु
		अगर (!iommu->irte_ops->is_allocated(table, index)) अणु
			c += 1;
		पूर्ण अन्यथा अणु
			c     = 0;
			index = ALIGN(index + 1, alignment);
			जारी;
		पूर्ण

		अगर (c == count)	अणु
			क्रम (; c != 0; --c)
				iommu->irte_ops->set_allocated(table, index - c + 1);

			index -= count - 1;
			जाओ out;
		पूर्ण

		index++;
	पूर्ण

	index = -ENOSPC;

out:
	raw_spin_unlock_irqrestore(&table->lock, flags);

	वापस index;
पूर्ण

अटल पूर्णांक modअगरy_irte_ga(u16 devid, पूर्णांक index, काष्ठा irte_ga *irte,
			  काष्ठा amd_ir_data *data)
अणु
	bool ret;
	काष्ठा irq_remap_table *table;
	काष्ठा amd_iommu *iommu;
	अचिन्हित दीर्घ flags;
	काष्ठा irte_ga *entry;

	iommu = amd_iommu_rlookup_table[devid];
	अगर (iommu == शून्य)
		वापस -EINVAL;

	table = get_irq_table(devid);
	अगर (!table)
		वापस -ENOMEM;

	raw_spin_lock_irqsave(&table->lock, flags);

	entry = (काष्ठा irte_ga *)table->table;
	entry = &entry[index];

	ret = cmpxchg_द्विगुन(&entry->lo.val, &entry->hi.val,
			     entry->lo.val, entry->hi.val,
			     irte->lo.val, irte->hi.val);
	/*
	 * We use cmpxchg16 to atomically update the 128-bit IRTE,
	 * and it cannot be updated by the hardware or other processors
	 * behind us, so the वापस value of cmpxchg16 should be the
	 * same as the old value.
	 */
	WARN_ON(!ret);

	अगर (data)
		data->ref = entry;

	raw_spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_रुको(iommu);

	वापस 0;
पूर्ण

अटल पूर्णांक modअगरy_irte(u16 devid, पूर्णांक index, जोड़ irte *irte)
अणु
	काष्ठा irq_remap_table *table;
	काष्ठा amd_iommu *iommu;
	अचिन्हित दीर्घ flags;

	iommu = amd_iommu_rlookup_table[devid];
	अगर (iommu == शून्य)
		वापस -EINVAL;

	table = get_irq_table(devid);
	अगर (!table)
		वापस -ENOMEM;

	raw_spin_lock_irqsave(&table->lock, flags);
	table->table[index] = irte->val;
	raw_spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_रुको(iommu);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_irte(u16 devid, पूर्णांक index)
अणु
	काष्ठा irq_remap_table *table;
	काष्ठा amd_iommu *iommu;
	अचिन्हित दीर्घ flags;

	iommu = amd_iommu_rlookup_table[devid];
	अगर (iommu == शून्य)
		वापस;

	table = get_irq_table(devid);
	अगर (!table)
		वापस;

	raw_spin_lock_irqsave(&table->lock, flags);
	iommu->irte_ops->clear_allocated(table, index);
	raw_spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_रुको(iommu);
पूर्ण

अटल व्योम irte_prepare(व्योम *entry,
			 u32 delivery_mode, bool dest_mode,
			 u8 vector, u32 dest_apicid, पूर्णांक devid)
अणु
	जोड़ irte *irte = (जोड़ irte *) entry;

	irte->val                = 0;
	irte->fields.vector      = vector;
	irte->fields.पूर्णांक_type    = delivery_mode;
	irte->fields.destination = dest_apicid;
	irte->fields.dm          = dest_mode;
	irte->fields.valid       = 1;
पूर्ण

अटल व्योम irte_ga_prepare(व्योम *entry,
			    u32 delivery_mode, bool dest_mode,
			    u8 vector, u32 dest_apicid, पूर्णांक devid)
अणु
	काष्ठा irte_ga *irte = (काष्ठा irte_ga *) entry;

	irte->lo.val                      = 0;
	irte->hi.val                      = 0;
	irte->lo.fields_remap.पूर्णांक_type    = delivery_mode;
	irte->lo.fields_remap.dm          = dest_mode;
	irte->hi.fields.vector            = vector;
	irte->lo.fields_remap.destination = APICID_TO_IRTE_DEST_LO(dest_apicid);
	irte->hi.fields.destination       = APICID_TO_IRTE_DEST_HI(dest_apicid);
	irte->lo.fields_remap.valid       = 1;
पूर्ण

अटल व्योम irte_activate(व्योम *entry, u16 devid, u16 index)
अणु
	जोड़ irte *irte = (जोड़ irte *) entry;

	irte->fields.valid = 1;
	modअगरy_irte(devid, index, irte);
पूर्ण

अटल व्योम irte_ga_activate(व्योम *entry, u16 devid, u16 index)
अणु
	काष्ठा irte_ga *irte = (काष्ठा irte_ga *) entry;

	irte->lo.fields_remap.valid = 1;
	modअगरy_irte_ga(devid, index, irte, शून्य);
पूर्ण

अटल व्योम irte_deactivate(व्योम *entry, u16 devid, u16 index)
अणु
	जोड़ irte *irte = (जोड़ irte *) entry;

	irte->fields.valid = 0;
	modअगरy_irte(devid, index, irte);
पूर्ण

अटल व्योम irte_ga_deactivate(व्योम *entry, u16 devid, u16 index)
अणु
	काष्ठा irte_ga *irte = (काष्ठा irte_ga *) entry;

	irte->lo.fields_remap.valid = 0;
	modअगरy_irte_ga(devid, index, irte, शून्य);
पूर्ण

अटल व्योम irte_set_affinity(व्योम *entry, u16 devid, u16 index,
			      u8 vector, u32 dest_apicid)
अणु
	जोड़ irte *irte = (जोड़ irte *) entry;

	irte->fields.vector = vector;
	irte->fields.destination = dest_apicid;
	modअगरy_irte(devid, index, irte);
पूर्ण

अटल व्योम irte_ga_set_affinity(व्योम *entry, u16 devid, u16 index,
				 u8 vector, u32 dest_apicid)
अणु
	काष्ठा irte_ga *irte = (काष्ठा irte_ga *) entry;

	अगर (!irte->lo.fields_remap.guest_mode) अणु
		irte->hi.fields.vector = vector;
		irte->lo.fields_remap.destination =
					APICID_TO_IRTE_DEST_LO(dest_apicid);
		irte->hi.fields.destination =
					APICID_TO_IRTE_DEST_HI(dest_apicid);
		modअगरy_irte_ga(devid, index, irte, शून्य);
	पूर्ण
पूर्ण

#घोषणा IRTE_ALLOCATED (~1U)
अटल व्योम irte_set_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	table->table[index] = IRTE_ALLOCATED;
पूर्ण

अटल व्योम irte_ga_set_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	काष्ठा irte_ga *ptr = (काष्ठा irte_ga *)table->table;
	काष्ठा irte_ga *irte = &ptr[index];

	स_रखो(&irte->lo.val, 0, माप(u64));
	स_रखो(&irte->hi.val, 0, माप(u64));
	irte->hi.fields.vector = 0xff;
पूर्ण

अटल bool irte_is_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	जोड़ irte *ptr = (जोड़ irte *)table->table;
	जोड़ irte *irte = &ptr[index];

	वापस irte->val != 0;
पूर्ण

अटल bool irte_ga_is_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	काष्ठा irte_ga *ptr = (काष्ठा irte_ga *)table->table;
	काष्ठा irte_ga *irte = &ptr[index];

	वापस irte->hi.fields.vector != 0;
पूर्ण

अटल व्योम irte_clear_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	table->table[index] = 0;
पूर्ण

अटल व्योम irte_ga_clear_allocated(काष्ठा irq_remap_table *table, पूर्णांक index)
अणु
	काष्ठा irte_ga *ptr = (काष्ठा irte_ga *)table->table;
	काष्ठा irte_ga *irte = &ptr[index];

	स_रखो(&irte->lo.val, 0, माप(u64));
	स_रखो(&irte->hi.val, 0, माप(u64));
पूर्ण

अटल पूर्णांक get_devid(काष्ठा irq_alloc_info *info)
अणु
	चयन (info->type) अणु
	हाल X86_IRQ_ALLOC_TYPE_IOAPIC:
		वापस get_ioapic_devid(info->devid);
	हाल X86_IRQ_ALLOC_TYPE_HPET:
		वापस get_hpet_devid(info->devid);
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSI:
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSIX:
		वापस get_device_id(msi_desc_to_dev(info->desc));
	शेष:
		WARN_ON_ONCE(1);
		वापस -1;
	पूर्ण
पूर्ण

काष्ठा irq_remap_ops amd_iommu_irq_ops = अणु
	.prepare		= amd_iommu_prepare,
	.enable			= amd_iommu_enable,
	.disable		= amd_iommu_disable,
	.reenable		= amd_iommu_reenable,
	.enable_faulting	= amd_iommu_enable_faulting,
पूर्ण;

अटल व्योम fill_msi_msg(काष्ठा msi_msg *msg, u32 index)
अणु
	msg->data = index;
	msg->address_lo = 0;
	msg->arch_addr_lo.base_address = X86_MSI_BASE_ADDRESS_LOW;
	msg->address_hi = X86_MSI_BASE_ADDRESS_HIGH;
पूर्ण

अटल व्योम irq_remapping_prepare_irte(काष्ठा amd_ir_data *data,
				       काष्ठा irq_cfg *irq_cfg,
				       काष्ठा irq_alloc_info *info,
				       पूर्णांक devid, पूर्णांक index, पूर्णांक sub_handle)
अणु
	काष्ठा irq_2_irte *irte_info = &data->irq_2_irte;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[devid];

	अगर (!iommu)
		वापस;

	data->irq_2_irte.devid = devid;
	data->irq_2_irte.index = index + sub_handle;
	iommu->irte_ops->prepare(data->entry, apic->delivery_mode,
				 apic->dest_mode_logical, irq_cfg->vector,
				 irq_cfg->dest_apicid, devid);

	चयन (info->type) अणु
	हाल X86_IRQ_ALLOC_TYPE_IOAPIC:
	हाल X86_IRQ_ALLOC_TYPE_HPET:
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSI:
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSIX:
		fill_msi_msg(&data->msi_entry, irte_info->index);
		अवरोध;

	शेष:
		BUG_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा amd_irte_ops irte_32_ops = अणु
	.prepare = irte_prepare,
	.activate = irte_activate,
	.deactivate = irte_deactivate,
	.set_affinity = irte_set_affinity,
	.set_allocated = irte_set_allocated,
	.is_allocated = irte_is_allocated,
	.clear_allocated = irte_clear_allocated,
पूर्ण;

काष्ठा amd_irte_ops irte_128_ops = अणु
	.prepare = irte_ga_prepare,
	.activate = irte_ga_activate,
	.deactivate = irte_ga_deactivate,
	.set_affinity = irte_ga_set_affinity,
	.set_allocated = irte_ga_set_allocated,
	.is_allocated = irte_ga_is_allocated,
	.clear_allocated = irte_ga_clear_allocated,
पूर्ण;

अटल पूर्णांक irq_remapping_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा irq_data *irq_data;
	काष्ठा amd_ir_data *data = शून्य;
	काष्ठा irq_cfg *cfg;
	पूर्णांक i, ret, devid;
	पूर्णांक index;

	अगर (!info)
		वापस -EINVAL;
	अगर (nr_irqs > 1 && info->type != X86_IRQ_ALLOC_TYPE_PCI_MSI &&
	    info->type != X86_IRQ_ALLOC_TYPE_PCI_MSIX)
		वापस -EINVAL;

	/*
	 * With IRQ remapping enabled, करोn't need contiguous CPU vectors
	 * to support multiple MSI पूर्णांकerrupts.
	 */
	अगर (info->type == X86_IRQ_ALLOC_TYPE_PCI_MSI)
		info->flags &= ~X86_IRQ_ALLOC_CONTIGUOUS_VECTORS;

	devid = get_devid(info);
	अगर (devid < 0)
		वापस -EINVAL;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0)
		वापस ret;

	अगर (info->type == X86_IRQ_ALLOC_TYPE_IOAPIC) अणु
		काष्ठा irq_remap_table *table;
		काष्ठा amd_iommu *iommu;

		table = alloc_irq_table(devid, शून्य);
		अगर (table) अणु
			अगर (!table->min_index) अणु
				/*
				 * Keep the first 32 indexes मुक्त क्रम IOAPIC
				 * पूर्णांकerrupts.
				 */
				table->min_index = 32;
				iommu = amd_iommu_rlookup_table[devid];
				क्रम (i = 0; i < 32; ++i)
					iommu->irte_ops->set_allocated(table, i);
			पूर्ण
			WARN_ON(table->min_index != 32);
			index = info->ioapic.pin;
		पूर्ण अन्यथा अणु
			index = -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (info->type == X86_IRQ_ALLOC_TYPE_PCI_MSI ||
		   info->type == X86_IRQ_ALLOC_TYPE_PCI_MSIX) अणु
		bool align = (info->type == X86_IRQ_ALLOC_TYPE_PCI_MSI);

		index = alloc_irq_index(devid, nr_irqs, align,
					msi_desc_to_pci_dev(info->desc));
	पूर्ण अन्यथा अणु
		index = alloc_irq_index(devid, nr_irqs, false, शून्य);
	पूर्ण

	अगर (index < 0) अणु
		pr_warn("Failed to allocate IRTE\n");
		ret = index;
		जाओ out_मुक्त_parent;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		cfg = irq_data ? irqd_cfg(irq_data) : शून्य;
		अगर (!cfg) अणु
			ret = -EINVAL;
			जाओ out_मुक्त_data;
		पूर्ण

		ret = -ENOMEM;
		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			जाओ out_मुक्त_data;

		अगर (!AMD_IOMMU_GUEST_IR_GA(amd_iommu_guest_ir))
			data->entry = kzalloc(माप(जोड़ irte), GFP_KERNEL);
		अन्यथा
			data->entry = kzalloc(माप(काष्ठा irte_ga),
						     GFP_KERNEL);
		अगर (!data->entry) अणु
			kमुक्त(data);
			जाओ out_मुक्त_data;
		पूर्ण

		irq_data->hwirq = (devid << 16) + i;
		irq_data->chip_data = data;
		irq_data->chip = &amd_ir_chip;
		irq_remapping_prepare_irte(data, cfg, info, devid, index, i);
		irq_set_status_flags(virq + i, IRQ_MOVE_PCNTXT);
	पूर्ण

	वापस 0;

out_मुक्त_data:
	क्रम (i--; i >= 0; i--) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		अगर (irq_data)
			kमुक्त(irq_data->chip_data);
	पूर्ण
	क्रम (i = 0; i < nr_irqs; i++)
		मुक्त_irte(devid, index + i);
out_मुक्त_parent:
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
	वापस ret;
पूर्ण

अटल व्योम irq_remapping_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_2_irte *irte_info;
	काष्ठा irq_data *irq_data;
	काष्ठा amd_ir_data *data;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq  + i);
		अगर (irq_data && irq_data->chip_data) अणु
			data = irq_data->chip_data;
			irte_info = &data->irq_2_irte;
			मुक्त_irte(irte_info->devid, irte_info->index);
			kमुक्त(data->entry);
			kमुक्त(data);
		पूर्ण
	पूर्ण
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल व्योम amd_ir_update_irte(काष्ठा irq_data *irqd, काष्ठा amd_iommu *iommu,
			       काष्ठा amd_ir_data *ir_data,
			       काष्ठा irq_2_irte *irte_info,
			       काष्ठा irq_cfg *cfg);

अटल पूर्णांक irq_remapping_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				  काष्ठा irq_data *irq_data, bool reserve)
अणु
	काष्ठा amd_ir_data *data = irq_data->chip_data;
	काष्ठा irq_2_irte *irte_info = &data->irq_2_irte;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[irte_info->devid];
	काष्ठा irq_cfg *cfg = irqd_cfg(irq_data);

	अगर (!iommu)
		वापस 0;

	iommu->irte_ops->activate(data->entry, irte_info->devid,
				  irte_info->index);
	amd_ir_update_irte(irq_data, iommu, data, irte_info, cfg);
	वापस 0;
पूर्ण

अटल व्योम irq_remapping_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				     काष्ठा irq_data *irq_data)
अणु
	काष्ठा amd_ir_data *data = irq_data->chip_data;
	काष्ठा irq_2_irte *irte_info = &data->irq_2_irte;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[irte_info->devid];

	अगर (iommu)
		iommu->irte_ops->deactivate(data->entry, irte_info->devid,
					    irte_info->index);
पूर्ण

अटल पूर्णांक irq_remapping_select(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
				क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा amd_iommu *iommu;
	पूर्णांक devid = -1;

	अगर (!amd_iommu_irq_remap)
		वापस 0;

	अगर (x86_fwspec_is_ioapic(fwspec))
		devid = get_ioapic_devid(fwspec->param[0]);
	अन्यथा अगर (x86_fwspec_is_hpet(fwspec))
		devid = get_hpet_devid(fwspec->param[0]);

	अगर (devid < 0)
		वापस 0;

	iommu = amd_iommu_rlookup_table[devid];
	वापस iommu && iommu->ir_करोमुख्य == d;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops amd_ir_करोमुख्य_ops = अणु
	.select = irq_remapping_select,
	.alloc = irq_remapping_alloc,
	.मुक्त = irq_remapping_मुक्त,
	.activate = irq_remapping_activate,
	.deactivate = irq_remapping_deactivate,
पूर्ण;

पूर्णांक amd_iommu_activate_guest_mode(व्योम *data)
अणु
	काष्ठा amd_ir_data *ir_data = (काष्ठा amd_ir_data *)data;
	काष्ठा irte_ga *entry = (काष्ठा irte_ga *) ir_data->entry;
	u64 valid;

	अगर (!AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir) ||
	    !entry || entry->lo.fields_vapic.guest_mode)
		वापस 0;

	valid = entry->lo.fields_vapic.valid;

	entry->lo.val = 0;
	entry->hi.val = 0;

	entry->lo.fields_vapic.valid       = valid;
	entry->lo.fields_vapic.guest_mode  = 1;
	entry->lo.fields_vapic.ga_log_पूर्णांकr = 1;
	entry->hi.fields.ga_root_ptr       = ir_data->ga_root_ptr;
	entry->hi.fields.vector            = ir_data->ga_vector;
	entry->lo.fields_vapic.ga_tag      = ir_data->ga_tag;

	वापस modअगरy_irte_ga(ir_data->irq_2_irte.devid,
			      ir_data->irq_2_irte.index, entry, ir_data);
पूर्ण
EXPORT_SYMBOL(amd_iommu_activate_guest_mode);

पूर्णांक amd_iommu_deactivate_guest_mode(व्योम *data)
अणु
	काष्ठा amd_ir_data *ir_data = (काष्ठा amd_ir_data *)data;
	काष्ठा irte_ga *entry = (काष्ठा irte_ga *) ir_data->entry;
	काष्ठा irq_cfg *cfg = ir_data->cfg;
	u64 valid;

	अगर (!AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir) ||
	    !entry || !entry->lo.fields_vapic.guest_mode)
		वापस 0;

	valid = entry->lo.fields_remap.valid;

	entry->lo.val = 0;
	entry->hi.val = 0;

	entry->lo.fields_remap.valid       = valid;
	entry->lo.fields_remap.dm          = apic->dest_mode_logical;
	entry->lo.fields_remap.पूर्णांक_type    = apic->delivery_mode;
	entry->hi.fields.vector            = cfg->vector;
	entry->lo.fields_remap.destination =
				APICID_TO_IRTE_DEST_LO(cfg->dest_apicid);
	entry->hi.fields.destination =
				APICID_TO_IRTE_DEST_HI(cfg->dest_apicid);

	वापस modअगरy_irte_ga(ir_data->irq_2_irte.devid,
			      ir_data->irq_2_irte.index, entry, ir_data);
पूर्ण
EXPORT_SYMBOL(amd_iommu_deactivate_guest_mode);

अटल पूर्णांक amd_ir_set_vcpu_affinity(काष्ठा irq_data *data, व्योम *vcpu_info)
अणु
	पूर्णांक ret;
	काष्ठा amd_iommu *iommu;
	काष्ठा amd_iommu_pi_data *pi_data = vcpu_info;
	काष्ठा vcpu_data *vcpu_pi_info = pi_data->vcpu_data;
	काष्ठा amd_ir_data *ir_data = data->chip_data;
	काष्ठा irq_2_irte *irte_info = &ir_data->irq_2_irte;
	काष्ठा iommu_dev_data *dev_data = search_dev_data(irte_info->devid);

	/* Note:
	 * This device has never been set up क्रम guest mode.
	 * we should not modअगरy the IRTE
	 */
	अगर (!dev_data || !dev_data->use_vapic)
		वापस 0;

	ir_data->cfg = irqd_cfg(data);
	pi_data->ir_data = ir_data;

	/* Note:
	 * SVM tries to set up क्रम VAPIC mode, but we are in
	 * legacy mode. So, we क्रमce legacy mode instead.
	 */
	अगर (!AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir)) अणु
		pr_debug("%s: Fall back to using intr legacy remap\n",
			 __func__);
		pi_data->is_guest_mode = false;
	पूर्ण

	iommu = amd_iommu_rlookup_table[irte_info->devid];
	अगर (iommu == शून्य)
		वापस -EINVAL;

	pi_data->prev_ga_tag = ir_data->cached_ga_tag;
	अगर (pi_data->is_guest_mode) अणु
		ir_data->ga_root_ptr = (pi_data->base >> 12);
		ir_data->ga_vector = vcpu_pi_info->vector;
		ir_data->ga_tag = pi_data->ga_tag;
		ret = amd_iommu_activate_guest_mode(ir_data);
		अगर (!ret)
			ir_data->cached_ga_tag = pi_data->ga_tag;
	पूर्ण अन्यथा अणु
		ret = amd_iommu_deactivate_guest_mode(ir_data);

		/*
		 * This communicates the ga_tag back to the caller
		 * so that it can करो all the necessary clean up.
		 */
		अगर (!ret)
			ir_data->cached_ga_tag = 0;
	पूर्ण

	वापस ret;
पूर्ण


अटल व्योम amd_ir_update_irte(काष्ठा irq_data *irqd, काष्ठा amd_iommu *iommu,
			       काष्ठा amd_ir_data *ir_data,
			       काष्ठा irq_2_irte *irte_info,
			       काष्ठा irq_cfg *cfg)
अणु

	/*
	 * Atomically updates the IRTE with the new destination, vector
	 * and flushes the पूर्णांकerrupt entry cache.
	 */
	iommu->irte_ops->set_affinity(ir_data->entry, irte_info->devid,
				      irte_info->index, cfg->vector,
				      cfg->dest_apicid);
पूर्ण

अटल पूर्णांक amd_ir_set_affinity(काष्ठा irq_data *data,
			       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा amd_ir_data *ir_data = data->chip_data;
	काष्ठा irq_2_irte *irte_info = &ir_data->irq_2_irte;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	काष्ठा irq_data *parent = data->parent_data;
	काष्ठा amd_iommu *iommu = amd_iommu_rlookup_table[irte_info->devid];
	पूर्णांक ret;

	अगर (!iommu)
		वापस -ENODEV;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	amd_ir_update_irte(data, iommu, ir_data, irte_info, cfg);
	/*
	 * After this poपूर्णांक, all the पूर्णांकerrupts will start arriving
	 * at the new destination. So, समय to cleanup the previous
	 * vector allocation.
	 */
	send_cleanup_vector(cfg);

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण

अटल व्योम ir_compose_msi_msg(काष्ठा irq_data *irq_data, काष्ठा msi_msg *msg)
अणु
	काष्ठा amd_ir_data *ir_data = irq_data->chip_data;

	*msg = ir_data->msi_entry;
पूर्ण

अटल काष्ठा irq_chip amd_ir_chip = अणु
	.name			= "AMD-IR",
	.irq_ack		= apic_ack_irq,
	.irq_set_affinity	= amd_ir_set_affinity,
	.irq_set_vcpu_affinity	= amd_ir_set_vcpu_affinity,
	.irq_compose_msi_msg	= ir_compose_msi_msg,
पूर्ण;

पूर्णांक amd_iommu_create_irq_करोमुख्य(काष्ठा amd_iommu *iommu)
अणु
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_id_fwnode("AMD-IR", iommu->index);
	अगर (!fn)
		वापस -ENOMEM;
	iommu->ir_करोमुख्य = irq_करोमुख्य_create_tree(fn, &amd_ir_करोमुख्य_ops, iommu);
	अगर (!iommu->ir_करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENOMEM;
	पूर्ण

	iommu->ir_करोमुख्य->parent = arch_get_ir_parent_करोमुख्य();
	iommu->msi_करोमुख्य = arch_create_remap_msi_irq_करोमुख्य(iommu->ir_करोमुख्य,
							     "AMD-IR-MSI",
							     iommu->index);
	वापस 0;
पूर्ण

पूर्णांक amd_iommu_update_ga(पूर्णांक cpu, bool is_run, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_iommu *iommu;
	काष्ठा irq_remap_table *table;
	काष्ठा amd_ir_data *ir_data = (काष्ठा amd_ir_data *)data;
	पूर्णांक devid = ir_data->irq_2_irte.devid;
	काष्ठा irte_ga *entry = (काष्ठा irte_ga *) ir_data->entry;
	काष्ठा irte_ga *ref = (काष्ठा irte_ga *) ir_data->ref;

	अगर (!AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir) ||
	    !ref || !entry || !entry->lo.fields_vapic.guest_mode)
		वापस 0;

	iommu = amd_iommu_rlookup_table[devid];
	अगर (!iommu)
		वापस -ENODEV;

	table = get_irq_table(devid);
	अगर (!table)
		वापस -ENODEV;

	raw_spin_lock_irqsave(&table->lock, flags);

	अगर (ref->lo.fields_vapic.guest_mode) अणु
		अगर (cpu >= 0) अणु
			ref->lo.fields_vapic.destination =
						APICID_TO_IRTE_DEST_LO(cpu);
			ref->hi.fields.destination =
						APICID_TO_IRTE_DEST_HI(cpu);
		पूर्ण
		ref->lo.fields_vapic.is_run = is_run;
		barrier();
	पूर्ण

	raw_spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_रुको(iommu);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(amd_iommu_update_ga);
#पूर्ण_अगर
