<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt)     "DMAR-IR: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmar.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hpet.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/acpi.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/crash_dump.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/pci-direct.h>

#समावेश "../irq_remapping.h"
#समावेश "cap_audit.h"

क्रमागत irq_mode अणु
	IRQ_REMAPPING,
	IRQ_POSTING,
पूर्ण;

काष्ठा ioapic_scope अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक bus;	/* PCI bus number */
	अचिन्हित पूर्णांक devfn;	/* PCI devfn number */
पूर्ण;

काष्ठा hpet_scope अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	u8 id;
	अचिन्हित पूर्णांक bus;
	अचिन्हित पूर्णांक devfn;
पूर्ण;

काष्ठा irq_2_iommu अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	u16 irte_index;
	u16 sub_handle;
	u8  irte_mask;
	क्रमागत irq_mode mode;
पूर्ण;

काष्ठा पूर्णांकel_ir_data अणु
	काष्ठा irq_2_iommu			irq_2_iommu;
	काष्ठा irte				irte_entry;
	जोड़ अणु
		काष्ठा msi_msg			msi_entry;
	पूर्ण;
पूर्ण;

#घोषणा IR_X2APIC_MODE(mode) (mode ? (1 << 11) : 0)
#घोषणा IRTE_DEST(dest) ((eim_mode) ? dest : dest << 8)

अटल पूर्णांक __पढ़ो_mostly eim_mode;
अटल काष्ठा ioapic_scope ir_ioapic[MAX_IO_APICS];
अटल काष्ठा hpet_scope ir_hpet[MAX_HPET_TBS];

/*
 * Lock ordering:
 * ->dmar_global_lock
 *	->irq_2_ir_lock
 *		->qi->q_lock
 *	->iommu->रेजिस्टर_lock
 * Note:
 * पूर्णांकel_irq_remap_ops.अणुsupported,prepare,enable,disable,reenableपूर्ण are called
 * in single-thपढ़ोed environment with पूर्णांकerrupt disabled, so no need to tabke
 * the dmar_global_lock.
 */
DEFINE_RAW_SPINLOCK(irq_2_ir_lock);
अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकel_ir_करोमुख्य_ops;

अटल व्योम iommu_disable_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu);
अटल पूर्णांक __init parse_ioapics_under_ir(व्योम);

अटल bool ir_pre_enabled(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस (iommu->flags & VTD_FLAG_IRQ_REMAP_PRE_ENABLED);
पूर्ण

अटल व्योम clear_ir_pre_enabled(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	iommu->flags &= ~VTD_FLAG_IRQ_REMAP_PRE_ENABLED;
पूर्ण

अटल व्योम init_ir_status(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 gsts;

	gsts = पढ़ोl(iommu->reg + DMAR_GSTS_REG);
	अगर (gsts & DMA_GSTS_IRES)
		iommu->flags |= VTD_FLAG_IRQ_REMAP_PRE_ENABLED;
पूर्ण

अटल पूर्णांक alloc_irte(काष्ठा पूर्णांकel_iommu *iommu,
		      काष्ठा irq_2_iommu *irq_iommu, u16 count)
अणु
	काष्ठा ir_table *table = iommu->ir_table;
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	अगर (!count || !irq_iommu)
		वापस -1;

	अगर (count > 1) अणु
		count = __roundup_घात_of_two(count);
		mask = ilog2(count);
	पूर्ण

	अगर (mask > ecap_max_handle_mask(iommu->ecap)) अणु
		pr_err("Requested mask %x exceeds the max invalidation handle"
		       " mask value %Lx\n", mask,
		       ecap_max_handle_mask(iommu->ecap));
		वापस -1;
	पूर्ण

	raw_spin_lock_irqsave(&irq_2_ir_lock, flags);
	index = biपंचांगap_find_मुक्त_region(table->biपंचांगap,
					INTR_REMAP_TABLE_ENTRIES, mask);
	अगर (index < 0) अणु
		pr_warn("IR%d: can't allocate an IRTE\n", iommu->seq_id);
	पूर्ण अन्यथा अणु
		irq_iommu->iommu = iommu;
		irq_iommu->irte_index =  index;
		irq_iommu->sub_handle = 0;
		irq_iommu->irte_mask = mask;
		irq_iommu->mode = IRQ_REMAPPING;
	पूर्ण
	raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);

	वापस index;
पूर्ण

अटल पूर्णांक qi_flush_iec(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक index, पूर्णांक mask)
अणु
	काष्ठा qi_desc desc;

	desc.qw0 = QI_IEC_IIDEX(index) | QI_IEC_TYPE | QI_IEC_IM(mask)
		   | QI_IEC_SELECTIVE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	वापस qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

अटल पूर्णांक modअगरy_irte(काष्ठा irq_2_iommu *irq_iommu,
		       काष्ठा irte *irte_modअगरied)
अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;
	काष्ठा irte *irte;
	पूर्णांक rc, index;

	अगर (!irq_iommu)
		वापस -1;

	raw_spin_lock_irqsave(&irq_2_ir_lock, flags);

	iommu = irq_iommu->iommu;

	index = irq_iommu->irte_index + irq_iommu->sub_handle;
	irte = &iommu->ir_table->base[index];

#अगर defined(CONFIG_HAVE_CMPXCHG_DOUBLE)
	अगर ((irte->pst == 1) || (irte_modअगरied->pst == 1)) अणु
		bool ret;

		ret = cmpxchg_द्विगुन(&irte->low, &irte->high,
				     irte->low, irte->high,
				     irte_modअगरied->low, irte_modअगरied->high);
		/*
		 * We use cmpxchg16 to atomically update the 128-bit IRTE,
		 * and it cannot be updated by the hardware or other processors
		 * behind us, so the वापस value of cmpxchg16 should be the
		 * same as the old value.
		 */
		WARN_ON(!ret);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		set_64bit(&irte->low, irte_modअगरied->low);
		set_64bit(&irte->high, irte_modअगरied->high);
	पूर्ण
	__iommu_flush_cache(iommu, irte, माप(*irte));

	rc = qi_flush_iec(iommu, index, 0);

	/* Update iommu mode according to the IRTE mode */
	irq_iommu->mode = irte->pst ? IRQ_POSTING : IRQ_REMAPPING;
	raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);

	वापस rc;
पूर्ण

अटल काष्ठा पूर्णांकel_iommu *map_hpet_to_iommu(u8 hpet_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_HPET_TBS; i++) अणु
		अगर (ir_hpet[i].id == hpet_id && ir_hpet[i].iommu)
			वापस ir_hpet[i].iommu;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा पूर्णांकel_iommu *map_ioapic_to_iommu(पूर्णांक apic)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_IO_APICS; i++) अणु
		अगर (ir_ioapic[i].id == apic && ir_ioapic[i].iommu)
			वापस ir_ioapic[i].iommu;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा irq_करोमुख्य *map_dev_to_ir(काष्ठा pci_dev *dev)
अणु
	काष्ठा dmar_drhd_unit *drhd = dmar_find_matched_drhd_unit(dev);

	वापस drhd ? drhd->iommu->ir_msi_करोमुख्य : शून्य;
पूर्ण

अटल पूर्णांक clear_entries(काष्ठा irq_2_iommu *irq_iommu)
अणु
	काष्ठा irte *start, *entry, *end;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक index;

	अगर (irq_iommu->sub_handle)
		वापस 0;

	iommu = irq_iommu->iommu;
	index = irq_iommu->irte_index;

	start = iommu->ir_table->base + index;
	end = start + (1 << irq_iommu->irte_mask);

	क्रम (entry = start; entry < end; entry++) अणु
		set_64bit(&entry->low, 0);
		set_64bit(&entry->high, 0);
	पूर्ण
	biपंचांगap_release_region(iommu->ir_table->biपंचांगap, index,
			      irq_iommu->irte_mask);

	वापस qi_flush_iec(iommu, index, irq_iommu->irte_mask);
पूर्ण

/*
 * source validation type
 */
#घोषणा SVT_NO_VERIFY		0x0  /* no verअगरication is required */
#घोषणा SVT_VERIFY_SID_SQ	0x1  /* verअगरy using SID and SQ fields */
#घोषणा SVT_VERIFY_BUS		0x2  /* verअगरy bus of request-id */

/*
 * source-id qualअगरier
 */
#घोषणा SQ_ALL_16	0x0  /* verअगरy all 16 bits of request-id */
#घोषणा SQ_13_IGNORE_1	0x1  /* verअगरy most signअगरicant 13 bits, ignore
			      * the third least signअगरicant bit
			      */
#घोषणा SQ_13_IGNORE_2	0x2  /* verअगरy most signअगरicant 13 bits, ignore
			      * the second and third least signअगरicant bits
			      */
#घोषणा SQ_13_IGNORE_3	0x3  /* verअगरy most signअगरicant 13 bits, ignore
			      * the least three signअगरicant bits
			      */

/*
 * set SVT, SQ and SID fields of irte to verअगरy
 * source ids of पूर्णांकerrupt requests
 */
अटल व्योम set_irte_sid(काष्ठा irte *irte, अचिन्हित पूर्णांक svt,
			 अचिन्हित पूर्णांक sq, अचिन्हित पूर्णांक sid)
अणु
	अगर (disable_sourceid_checking)
		svt = SVT_NO_VERIFY;
	irte->svt = svt;
	irte->sq = sq;
	irte->sid = sid;
पूर्ण

/*
 * Set an IRTE to match only the bus number. Interrupt requests that reference
 * this IRTE must have a requester-id whose bus number is between or equal
 * to the start_bus and end_bus arguments.
 */
अटल व्योम set_irte_verअगरy_bus(काष्ठा irte *irte, अचिन्हित पूर्णांक start_bus,
				अचिन्हित पूर्णांक end_bus)
अणु
	set_irte_sid(irte, SVT_VERIFY_BUS, SQ_ALL_16,
		     (start_bus << 8) | end_bus);
पूर्ण

अटल पूर्णांक set_ioapic_sid(काष्ठा irte *irte, पूर्णांक apic)
अणु
	पूर्णांक i;
	u16 sid = 0;

	अगर (!irte)
		वापस -1;

	करोwn_पढ़ो(&dmar_global_lock);
	क्रम (i = 0; i < MAX_IO_APICS; i++) अणु
		अगर (ir_ioapic[i].iommu && ir_ioapic[i].id == apic) अणु
			sid = (ir_ioapic[i].bus << 8) | ir_ioapic[i].devfn;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&dmar_global_lock);

	अगर (sid == 0) अणु
		pr_warn("Failed to set source-id of IOAPIC (%d)\n", apic);
		वापस -1;
	पूर्ण

	set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16, sid);

	वापस 0;
पूर्ण

अटल पूर्णांक set_hpet_sid(काष्ठा irte *irte, u8 id)
अणु
	पूर्णांक i;
	u16 sid = 0;

	अगर (!irte)
		वापस -1;

	करोwn_पढ़ो(&dmar_global_lock);
	क्रम (i = 0; i < MAX_HPET_TBS; i++) अणु
		अगर (ir_hpet[i].iommu && ir_hpet[i].id == id) अणु
			sid = (ir_hpet[i].bus << 8) | ir_hpet[i].devfn;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&dmar_global_lock);

	अगर (sid == 0) अणु
		pr_warn("Failed to set source-id of HPET block (%d)\n", id);
		वापस -1;
	पूर्ण

	/*
	 * Should really use SQ_ALL_16. Some platक्रमms are broken.
	 * While we figure out the right quirks क्रम these broken platक्रमms, use
	 * SQ_13_IGNORE_3 क्रम now.
	 */
	set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_13_IGNORE_3, sid);

	वापस 0;
पूर्ण

काष्ठा set_msi_sid_data अणु
	काष्ठा pci_dev *pdev;
	u16 alias;
	पूर्णांक count;
	पूर्णांक busmatch_count;
पूर्ण;

अटल पूर्णांक set_msi_sid_cb(काष्ठा pci_dev *pdev, u16 alias, व्योम *opaque)
अणु
	काष्ठा set_msi_sid_data *data = opaque;

	अगर (data->count == 0 || PCI_BUS_NUM(alias) == PCI_BUS_NUM(data->alias))
		data->busmatch_count++;

	data->pdev = pdev;
	data->alias = alias;
	data->count++;

	वापस 0;
पूर्ण

अटल पूर्णांक set_msi_sid(काष्ठा irte *irte, काष्ठा pci_dev *dev)
अणु
	काष्ठा set_msi_sid_data data;

	अगर (!irte || !dev)
		वापस -1;

	data.count = 0;
	data.busmatch_count = 0;
	pci_क्रम_each_dma_alias(dev, set_msi_sid_cb, &data);

	/*
	 * DMA alias provides us with a PCI device and alias.  The only हाल
	 * where the it will वापस an alias on a dअगरferent bus than the
	 * device is the हाल of a PCIe-to-PCI bridge, where the alias is क्रम
	 * the subordinate bus.  In this हाल we can only verअगरy the bus.
	 *
	 * If there are multiple aliases, all with the same bus number,
	 * then all we can करो is verअगरy the bus. This is typical in NTB
	 * hardware which use proxy IDs where the device will generate traffic
	 * from multiple devfn numbers on the same bus.
	 *
	 * If the alias device is on a dअगरferent bus than our source device
	 * then we have a topology based alias, use it.
	 *
	 * Otherwise, the alias is क्रम a device DMA quirk and we cannot
	 * assume that MSI uses the same requester ID.  Thereक्रमe use the
	 * original device.
	 */
	अगर (PCI_BUS_NUM(data.alias) != data.pdev->bus->number)
		set_irte_verअगरy_bus(irte, PCI_BUS_NUM(data.alias),
				    dev->bus->number);
	अन्यथा अगर (data.count >= 2 && data.busmatch_count == data.count)
		set_irte_verअगरy_bus(irte, dev->bus->number, dev->bus->number);
	अन्यथा अगर (data.pdev->bus->number != dev->bus->number)
		set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16, data.alias);
	अन्यथा
		set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16,
			     pci_dev_id(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_load_old_irte(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा irte *old_ir_table;
	phys_addr_t irt_phys;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;
	u64 irta;

	/* Check whether the old ir-table has the same size as ours */
	irta = dmar_पढ़ोq(iommu->reg + DMAR_IRTA_REG);
	अगर ((irta & INTR_REMAP_TABLE_REG_SIZE_MASK)
	     != INTR_REMAP_TABLE_REG_SIZE)
		वापस -EINVAL;

	irt_phys = irta & VTD_PAGE_MASK;
	size     = INTR_REMAP_TABLE_ENTRIES*माप(काष्ठा irte);

	/* Map the old IR table */
	old_ir_table = memremap(irt_phys, size, MEMREMAP_WB);
	अगर (!old_ir_table)
		वापस -ENOMEM;

	/* Copy data over */
	स_नकल(iommu->ir_table->base, old_ir_table, size);

	__iommu_flush_cache(iommu, iommu->ir_table->base, size);

	/*
	 * Now check the table क्रम used entries and mark those as
	 * allocated in the biपंचांगap
	 */
	क्रम (i = 0; i < INTR_REMAP_TABLE_ENTRIES; i++) अणु
		अगर (iommu->ir_table->base[i].present)
			biपंचांगap_set(iommu->ir_table->biपंचांगap, i, 1);
	पूर्ण

	memunmap(old_ir_table);

	वापस 0;
पूर्ण


अटल व्योम iommu_set_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;
	u64 addr;
	u32 sts;

	addr = virt_to_phys((व्योम *)iommu->ir_table->base);

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);

	dmar_ग_लिखोq(iommu->reg + DMAR_IRTA_REG,
		    (addr) | IR_X2APIC_MODE(mode) | INTR_REMAP_TABLE_REG_SIZE);

	/* Set पूर्णांकerrupt-remapping table poपूर्णांकer */
	ग_लिखोl(iommu->gcmd | DMA_GCMD_SIRTP, iommu->reg + DMAR_GCMD_REG);

	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (sts & DMA_GSTS_IRTPS), sts);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);

	/*
	 * Global invalidation of पूर्णांकerrupt entry cache to make sure the
	 * hardware uses the new irq remapping table.
	 */
	qi_global_iec(iommu);
पूर्ण

अटल व्योम iommu_enable_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अचिन्हित दीर्घ flags;
	u32 sts;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);

	/* Enable पूर्णांकerrupt-remapping */
	iommu->gcmd |= DMA_GCMD_IRE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (sts & DMA_GSTS_IRES), sts);

	/* Block compatibility-क्रमmat MSIs */
	अगर (sts & DMA_GSTS_CFIS) अणु
		iommu->gcmd &= ~DMA_GCMD_CFI;
		ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);
		IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
			      पढ़ोl, !(sts & DMA_GSTS_CFIS), sts);
	पूर्ण

	/*
	 * With CFI clear in the Global Command रेजिस्टर, we should be
	 * रक्षित from dangerous (i.e. compatibility) पूर्णांकerrupts
	 * regardless of x2apic status.  Check just to be sure.
	 */
	अगर (sts & DMA_GSTS_CFIS)
		WARN(1, KERN_WARNING
			"Compatibility-format IRQs enabled despite intr remapping;\n"
			"you are vulnerable to IRQ injection.\n");

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

अटल पूर्णांक पूर्णांकel_setup_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा ir_table *ir_table;
	काष्ठा fwnode_handle *fn;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा page *pages;

	अगर (iommu->ir_table)
		वापस 0;

	ir_table = kzalloc(माप(काष्ठा ir_table), GFP_KERNEL);
	अगर (!ir_table)
		वापस -ENOMEM;

	pages = alloc_pages_node(iommu->node, GFP_KERNEL | __GFP_ZERO,
				 INTR_REMAP_PAGE_ORDER);
	अगर (!pages) अणु
		pr_err("IR%d: failed to allocate pages of order %d\n",
		       iommu->seq_id, INTR_REMAP_PAGE_ORDER);
		जाओ out_मुक्त_table;
	पूर्ण

	biपंचांगap = biपंचांगap_zalloc(INTR_REMAP_TABLE_ENTRIES, GFP_ATOMIC);
	अगर (biपंचांगap == शून्य) अणु
		pr_err("IR%d: failed to allocate bitmap\n", iommu->seq_id);
		जाओ out_मुक्त_pages;
	पूर्ण

	fn = irq_करोमुख्य_alloc_named_id_fwnode("INTEL-IR", iommu->seq_id);
	अगर (!fn)
		जाओ out_मुक्त_biपंचांगap;

	iommu->ir_करोमुख्य =
		irq_करोमुख्य_create_hierarchy(arch_get_ir_parent_करोमुख्य(),
					    0, INTR_REMAP_TABLE_ENTRIES,
					    fn, &पूर्णांकel_ir_करोमुख्य_ops,
					    iommu);
	अगर (!iommu->ir_करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		pr_err("IR%d: failed to allocate irqdomain\n", iommu->seq_id);
		जाओ out_मुक्त_biपंचांगap;
	पूर्ण
	iommu->ir_msi_करोमुख्य =
		arch_create_remap_msi_irq_करोमुख्य(iommu->ir_करोमुख्य,
						 "INTEL-IR-MSI",
						 iommu->seq_id);

	ir_table->base = page_address(pages);
	ir_table->biपंचांगap = biपंचांगap;
	iommu->ir_table = ir_table;

	/*
	 * If the queued invalidation is alपढ़ोy initialized,
	 * shouldn't disable it.
	 */
	अगर (!iommu->qi) अणु
		/*
		 * Clear previous faults.
		 */
		dmar_fault(-1, iommu);
		dmar_disable_qi(iommu);

		अगर (dmar_enable_qi(iommu)) अणु
			pr_err("Failed to enable queued invalidation\n");
			जाओ out_मुक्त_biपंचांगap;
		पूर्ण
	पूर्ण

	init_ir_status(iommu);

	अगर (ir_pre_enabled(iommu)) अणु
		अगर (!is_kdump_kernel()) अणु
			pr_warn("IRQ remapping was enabled on %s but we are not in kdump mode\n",
				iommu->name);
			clear_ir_pre_enabled(iommu);
			iommu_disable_irq_remapping(iommu);
		पूर्ण अन्यथा अगर (iommu_load_old_irte(iommu))
			pr_err("Failed to copy IR table for %s from previous kernel\n",
			       iommu->name);
		अन्यथा
			pr_info("Copied IR table for %s from previous kernel\n",
				iommu->name);
	पूर्ण

	iommu_set_irq_remapping(iommu, eim_mode);

	वापस 0;

out_मुक्त_biपंचांगap:
	biपंचांगap_मुक्त(biपंचांगap);
out_मुक्त_pages:
	__मुक्त_pages(pages, INTR_REMAP_PAGE_ORDER);
out_मुक्त_table:
	kमुक्त(ir_table);

	iommu->ir_table  = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल व्योम पूर्णांकel_tearकरोwn_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा fwnode_handle *fn;

	अगर (iommu && iommu->ir_table) अणु
		अगर (iommu->ir_msi_करोमुख्य) अणु
			fn = iommu->ir_msi_करोमुख्य->fwnode;

			irq_करोमुख्य_हटाओ(iommu->ir_msi_करोमुख्य);
			irq_करोमुख्य_मुक्त_fwnode(fn);
			iommu->ir_msi_करोमुख्य = शून्य;
		पूर्ण
		अगर (iommu->ir_करोमुख्य) अणु
			fn = iommu->ir_करोमुख्य->fwnode;

			irq_करोमुख्य_हटाओ(iommu->ir_करोमुख्य);
			irq_करोमुख्य_मुक्त_fwnode(fn);
			iommu->ir_करोमुख्य = शून्य;
		पूर्ण
		मुक्त_pages((अचिन्हित दीर्घ)iommu->ir_table->base,
			   INTR_REMAP_PAGE_ORDER);
		biपंचांगap_मुक्त(iommu->ir_table->biपंचांगap);
		kमुक्त(iommu->ir_table);
		iommu->ir_table = शून्य;
	पूर्ण
पूर्ण

/*
 * Disable Interrupt Remapping.
 */
अटल व्योम iommu_disable_irq_remapping(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अचिन्हित दीर्घ flags;
	u32 sts;

	अगर (!ecap_ir_support(iommu->ecap))
		वापस;

	/*
	 * global invalidation of पूर्णांकerrupt entry cache beक्रमe disabling
	 * पूर्णांकerrupt-remapping.
	 */
	qi_global_iec(iommu);

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);

	sts = पढ़ोl(iommu->reg + DMAR_GSTS_REG);
	अगर (!(sts & DMA_GSTS_IRES))
		जाओ end;

	iommu->gcmd &= ~DMA_GCMD_IRE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, !(sts & DMA_GSTS_IRES), sts);

end:
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

अटल पूर्णांक __init dmar_x2apic_optout(व्योम)
अणु
	काष्ठा acpi_table_dmar *dmar;
	dmar = (काष्ठा acpi_table_dmar *)dmar_tbl;
	अगर (!dmar || no_x2apic_optout)
		वापस 0;
	वापस dmar->flags & DMAR_X2APIC_OPT_OUT;
पूर्ण

अटल व्योम __init पूर्णांकel_cleanup_irq_remapping(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;

	क्रम_each_iommu(iommu, drhd) अणु
		अगर (ecap_ir_support(iommu->ecap)) अणु
			iommu_disable_irq_remapping(iommu);
			पूर्णांकel_tearकरोwn_irq_remapping(iommu);
		पूर्ण
	पूर्ण

	अगर (x2apic_supported())
		pr_warn("Failed to enable irq remapping. You are vulnerable to irq-injection attacks.\n");
पूर्ण

अटल पूर्णांक __init पूर्णांकel_prepare_irq_remapping(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक eim = 0;

	अगर (irq_remap_broken) अणु
		pr_warn("This system BIOS has enabled interrupt remapping\n"
			"on a chipset that contains an erratum making that\n"
			"feature unstable.  To maintain system stability\n"
			"interrupt remapping is being disabled.  Please\n"
			"contact your BIOS vendor for an update\n");
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
		वापस -ENODEV;
	पूर्ण

	अगर (dmar_table_init() < 0)
		वापस -ENODEV;

	अगर (पूर्णांकel_cap_audit(CAP_AUDIT_STATIC_IRQR, शून्य))
		वापस -ENODEV;

	अगर (!dmar_ir_support())
		वापस -ENODEV;

	अगर (parse_ioapics_under_ir()) अणु
		pr_info("Not enabling interrupt remapping\n");
		जाओ error;
	पूर्ण

	/* First make sure all IOMMUs support IRQ remapping */
	क्रम_each_iommu(iommu, drhd)
		अगर (!ecap_ir_support(iommu->ecap))
			जाओ error;

	/* Detect remapping mode: lapic or x2apic */
	अगर (x2apic_supported()) अणु
		eim = !dmar_x2apic_optout();
		अगर (!eim) अणु
			pr_info("x2apic is disabled because BIOS sets x2apic opt out bit.");
			pr_info("Use 'intremap=no_x2apic_optout' to override the BIOS setting.\n");
		पूर्ण
	पूर्ण

	क्रम_each_iommu(iommu, drhd) अणु
		अगर (eim && !ecap_eim_support(iommu->ecap)) अणु
			pr_info("%s does not support EIM\n", iommu->name);
			eim = 0;
		पूर्ण
	पूर्ण

	eim_mode = eim;
	अगर (eim)
		pr_info("Queued invalidation will be enabled to support x2apic and Intr-remapping.\n");

	/* Do the initializations early */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (पूर्णांकel_setup_irq_remapping(iommu)) अणु
			pr_err("Failed to setup irq remapping for %s\n",
			       iommu->name);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	पूर्णांकel_cleanup_irq_remapping();
	वापस -ENODEV;
पूर्ण

/*
 * Set Posted-Interrupts capability.
 */
अटल अंतरभूत व्योम set_irq_posting_cap(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;

	अगर (!disable_irq_post) अणु
		/*
		 * If IRTE is in posted क्रमmat, the 'pda' field goes across the
		 * 64-bit boundary, we need use cmpxchg16b to atomically update
		 * it. We only expose posted-पूर्णांकerrupt when X86_FEATURE_CX16
		 * is supported. Actually, hardware platक्रमms supporting PI
		 * should have X86_FEATURE_CX16 support, this has been confirmed
		 * with Intel hardware guys.
		 */
		अगर (boot_cpu_has(X86_FEATURE_CX16))
			पूर्णांकel_irq_remap_ops.capability |= 1 << IRQ_POSTING_CAP;

		क्रम_each_iommu(iommu, drhd)
			अगर (!cap_pi_support(iommu->cap)) अणु
				पूर्णांकel_irq_remap_ops.capability &=
						~(1 << IRQ_POSTING_CAP);
				अवरोध;
			पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init पूर्णांकel_enable_irq_remapping(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	bool setup = false;

	/*
	 * Setup Interrupt-remapping क्रम all the DRHD's now.
	 */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (!ir_pre_enabled(iommu))
			iommu_enable_irq_remapping(iommu);
		setup = true;
	पूर्ण

	अगर (!setup)
		जाओ error;

	irq_remapping_enabled = 1;

	set_irq_posting_cap();

	pr_info("Enabled IRQ remapping in %s mode\n", eim_mode ? "x2apic" : "xapic");

	वापस eim_mode ? IRQ_REMAP_X2APIC_MODE : IRQ_REMAP_XAPIC_MODE;

error:
	पूर्णांकel_cleanup_irq_remapping();
	वापस -1;
पूर्ण

अटल पूर्णांक ir_parse_one_hpet_scope(काष्ठा acpi_dmar_device_scope *scope,
				   काष्ठा पूर्णांकel_iommu *iommu,
				   काष्ठा acpi_dmar_hardware_unit *drhd)
अणु
	काष्ठा acpi_dmar_pci_path *path;
	u8 bus;
	पूर्णांक count, मुक्त = -1;

	bus = scope->bus;
	path = (काष्ठा acpi_dmar_pci_path *)(scope + 1);
	count = (scope->length - माप(काष्ठा acpi_dmar_device_scope))
		/ माप(काष्ठा acpi_dmar_pci_path);

	जबतक (--count > 0) अणु
		/*
		 * Access PCI directly due to the PCI
		 * subप्रणाली isn't initialized yet.
		 */
		bus = पढ़ो_pci_config_byte(bus, path->device, path->function,
					   PCI_SECONDARY_BUS);
		path++;
	पूर्ण

	क्रम (count = 0; count < MAX_HPET_TBS; count++) अणु
		अगर (ir_hpet[count].iommu == iommu &&
		    ir_hpet[count].id == scope->क्रमागतeration_id)
			वापस 0;
		अन्यथा अगर (ir_hpet[count].iommu == शून्य && मुक्त == -1)
			मुक्त = count;
	पूर्ण
	अगर (मुक्त == -1) अणु
		pr_warn("Exceeded Max HPET blocks\n");
		वापस -ENOSPC;
	पूर्ण

	ir_hpet[मुक्त].iommu = iommu;
	ir_hpet[मुक्त].id    = scope->क्रमागतeration_id;
	ir_hpet[मुक्त].bus   = bus;
	ir_hpet[मुक्त].devfn = PCI_DEVFN(path->device, path->function);
	pr_info("HPET id %d under DRHD base 0x%Lx\n",
		scope->क्रमागतeration_id, drhd->address);

	वापस 0;
पूर्ण

अटल पूर्णांक ir_parse_one_ioapic_scope(काष्ठा acpi_dmar_device_scope *scope,
				     काष्ठा पूर्णांकel_iommu *iommu,
				     काष्ठा acpi_dmar_hardware_unit *drhd)
अणु
	काष्ठा acpi_dmar_pci_path *path;
	u8 bus;
	पूर्णांक count, मुक्त = -1;

	bus = scope->bus;
	path = (काष्ठा acpi_dmar_pci_path *)(scope + 1);
	count = (scope->length - माप(काष्ठा acpi_dmar_device_scope))
		/ माप(काष्ठा acpi_dmar_pci_path);

	जबतक (--count > 0) अणु
		/*
		 * Access PCI directly due to the PCI
		 * subप्रणाली isn't initialized yet.
		 */
		bus = पढ़ो_pci_config_byte(bus, path->device, path->function,
					   PCI_SECONDARY_BUS);
		path++;
	पूर्ण

	क्रम (count = 0; count < MAX_IO_APICS; count++) अणु
		अगर (ir_ioapic[count].iommu == iommu &&
		    ir_ioapic[count].id == scope->क्रमागतeration_id)
			वापस 0;
		अन्यथा अगर (ir_ioapic[count].iommu == शून्य && मुक्त == -1)
			मुक्त = count;
	पूर्ण
	अगर (मुक्त == -1) अणु
		pr_warn("Exceeded Max IO APICS\n");
		वापस -ENOSPC;
	पूर्ण

	ir_ioapic[मुक्त].bus   = bus;
	ir_ioapic[मुक्त].devfn = PCI_DEVFN(path->device, path->function);
	ir_ioapic[मुक्त].iommu = iommu;
	ir_ioapic[मुक्त].id    = scope->क्रमागतeration_id;
	pr_info("IOAPIC id %d under DRHD base  0x%Lx IOMMU %d\n",
		scope->क्रमागतeration_id, drhd->address, iommu->seq_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ir_parse_ioapic_hpet_scope(काष्ठा acpi_dmar_header *header,
				      काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक ret = 0;
	काष्ठा acpi_dmar_hardware_unit *drhd;
	काष्ठा acpi_dmar_device_scope *scope;
	व्योम *start, *end;

	drhd = (काष्ठा acpi_dmar_hardware_unit *)header;
	start = (व्योम *)(drhd + 1);
	end = ((व्योम *)drhd) + header->length;

	जबतक (start < end && ret == 0) अणु
		scope = start;
		अगर (scope->entry_type == ACPI_DMAR_SCOPE_TYPE_IOAPIC)
			ret = ir_parse_one_ioapic_scope(scope, iommu, drhd);
		अन्यथा अगर (scope->entry_type == ACPI_DMAR_SCOPE_TYPE_HPET)
			ret = ir_parse_one_hpet_scope(scope, iommu, drhd);
		start += scope->length;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ir_हटाओ_ioapic_hpet_scope(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_HPET_TBS; i++)
		अगर (ir_hpet[i].iommu == iommu)
			ir_hpet[i].iommu = शून्य;

	क्रम (i = 0; i < MAX_IO_APICS; i++)
		अगर (ir_ioapic[i].iommu == iommu)
			ir_ioapic[i].iommu = शून्य;
पूर्ण

/*
 * Finds the assocaition between IOAPIC's and its Interrupt-remapping
 * hardware unit.
 */
अटल पूर्णांक __init parse_ioapics_under_ir(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	bool ir_supported = false;
	पूर्णांक ioapic_idx;

	क्रम_each_iommu(iommu, drhd) अणु
		पूर्णांक ret;

		अगर (!ecap_ir_support(iommu->ecap))
			जारी;

		ret = ir_parse_ioapic_hpet_scope(drhd->hdr, iommu);
		अगर (ret)
			वापस ret;

		ir_supported = true;
	पूर्ण

	अगर (!ir_supported)
		वापस -ENODEV;

	क्रम (ioapic_idx = 0; ioapic_idx < nr_ioapics; ioapic_idx++) अणु
		पूर्णांक ioapic_id = mpc_ioapic_id(ioapic_idx);
		अगर (!map_ioapic_to_iommu(ioapic_id)) अणु
			pr_err(FW_BUG "ioapic %d has no mapping iommu, "
			       "interrupt remapping will be disabled\n",
			       ioapic_id);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init ir_dev_scope_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!irq_remapping_enabled)
		वापस 0;

	करोwn_ग_लिखो(&dmar_global_lock);
	ret = dmar_dev_scope_init();
	up_ग_लिखो(&dmar_global_lock);

	वापस ret;
पूर्ण
rootfs_initcall(ir_dev_scope_init);

अटल व्योम disable_irq_remapping(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;

	/*
	 * Disable Interrupt-remapping क्रम all the DRHD's now.
	 */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (!ecap_ir_support(iommu->ecap))
			जारी;

		iommu_disable_irq_remapping(iommu);
	पूर्ण

	/*
	 * Clear Posted-Interrupts capability.
	 */
	अगर (!disable_irq_post)
		पूर्णांकel_irq_remap_ops.capability &= ~(1 << IRQ_POSTING_CAP);
पूर्ण

अटल पूर्णांक reenable_irq_remapping(पूर्णांक eim)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	bool setup = false;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;

	क्रम_each_iommu(iommu, drhd)
		अगर (iommu->qi)
			dmar_reenable_qi(iommu);

	/*
	 * Setup Interrupt-remapping क्रम all the DRHD's now.
	 */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (!ecap_ir_support(iommu->ecap))
			जारी;

		/* Set up पूर्णांकerrupt remapping क्रम iommu.*/
		iommu_set_irq_remapping(iommu, eim);
		iommu_enable_irq_remapping(iommu);
		setup = true;
	पूर्ण

	अगर (!setup)
		जाओ error;

	set_irq_posting_cap();

	वापस 0;

error:
	/*
	 * handle error condition gracefully here!
	 */
	वापस -1;
पूर्ण

/*
 * Store the MSI remapping करोमुख्य poपूर्णांकer in the device अगर enabled.
 *
 * This is called from dmar_pci_bus_add_dev() so it works even when DMA
 * remapping is disabled. Only update the poपूर्णांकer अगर the device is not
 * alपढ़ोy handled by a non शेष PCI/MSI पूर्णांकerrupt करोमुख्य. This protects
 * e.g. VMD devices.
 */
व्योम पूर्णांकel_irq_remap_add_device(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	अगर (!irq_remapping_enabled || pci_dev_has_special_msi_करोमुख्य(info->dev))
		वापस;

	dev_set_msi_करोमुख्य(&info->dev->dev, map_dev_to_ir(info->dev));
पूर्ण

अटल व्योम prepare_irte(काष्ठा irte *irte, पूर्णांक vector, अचिन्हित पूर्णांक dest)
अणु
	स_रखो(irte, 0, माप(*irte));

	irte->present = 1;
	irte->dst_mode = apic->dest_mode_logical;
	/*
	 * Trigger mode in the IRTE will always be edge, and क्रम IO-APIC, the
	 * actual level or edge trigger will be setup in the IO-APIC
	 * RTE. This will help simplअगरy level triggered irq migration.
	 * For more details, see the comments (in io_apic.c) explainig IO-APIC
	 * irq migration in the presence of पूर्णांकerrupt-remapping.
	*/
	irte->trigger_mode = 0;
	irte->dlvry_mode = apic->delivery_mode;
	irte->vector = vector;
	irte->dest_id = IRTE_DEST(dest);
	irte->redir_hपूर्णांक = 1;
पूर्ण

काष्ठा irq_remap_ops पूर्णांकel_irq_remap_ops = अणु
	.prepare		= पूर्णांकel_prepare_irq_remapping,
	.enable			= पूर्णांकel_enable_irq_remapping,
	.disable		= disable_irq_remapping,
	.reenable		= reenable_irq_remapping,
	.enable_faulting	= enable_drhd_fault_handling,
पूर्ण;

अटल व्योम पूर्णांकel_ir_reconfigure_irte(काष्ठा irq_data *irqd, bool क्रमce)
अणु
	काष्ठा पूर्णांकel_ir_data *ir_data = irqd->chip_data;
	काष्ठा irte *irte = &ir_data->irte_entry;
	काष्ठा irq_cfg *cfg = irqd_cfg(irqd);

	/*
	 * Atomically updates the IRTE with the new destination, vector
	 * and flushes the पूर्णांकerrupt entry cache.
	 */
	irte->vector = cfg->vector;
	irte->dest_id = IRTE_DEST(cfg->dest_apicid);

	/* Update the hardware only अगर the पूर्णांकerrupt is in remapped mode. */
	अगर (क्रमce || ir_data->irq_2_iommu.mode == IRQ_REMAPPING)
		modअगरy_irte(&ir_data->irq_2_iommu, irte);
पूर्ण

/*
 * Migrate the IO-APIC irq in the presence of पूर्णांकr-remapping.
 *
 * For both level and edge triggered, irq migration is a simple atomic
 * update(of vector and cpu destination) of IRTE and flush the hardware cache.
 *
 * For level triggered, we eliminate the io-apic RTE modअगरication (with the
 * updated vector inक्रमmation), by using a भव vector (io-apic pin number).
 * Real vector that is used क्रम पूर्णांकerrupting cpu will be coming from
 * the पूर्णांकerrupt-remapping table entry.
 *
 * As the migration is a simple atomic update of IRTE, the same mechanism
 * is used to migrate MSI irq's in the presence of पूर्णांकerrupt-remapping.
 */
अटल पूर्णांक
पूर्णांकel_ir_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
		      bool क्रमce)
अणु
	काष्ठा irq_data *parent = data->parent_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	पूर्णांकel_ir_reconfigure_irte(data, false);
	/*
	 * After this poपूर्णांक, all the पूर्णांकerrupts will start arriving
	 * at the new destination. So, समय to cleanup the previous
	 * vector allocation.
	 */
	send_cleanup_vector(cfg);

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण

अटल व्योम पूर्णांकel_ir_compose_msi_msg(काष्ठा irq_data *irq_data,
				     काष्ठा msi_msg *msg)
अणु
	काष्ठा पूर्णांकel_ir_data *ir_data = irq_data->chip_data;

	*msg = ir_data->msi_entry;
पूर्ण

अटल पूर्णांक पूर्णांकel_ir_set_vcpu_affinity(काष्ठा irq_data *data, व्योम *info)
अणु
	काष्ठा पूर्णांकel_ir_data *ir_data = data->chip_data;
	काष्ठा vcpu_data *vcpu_pi_info = info;

	/* stop posting पूर्णांकerrupts, back to remapping mode */
	अगर (!vcpu_pi_info) अणु
		modअगरy_irte(&ir_data->irq_2_iommu, &ir_data->irte_entry);
	पूर्ण अन्यथा अणु
		काष्ठा irte irte_pi;

		/*
		 * We are not caching the posted पूर्णांकerrupt entry. We
		 * copy the data from the remapped entry and modअगरy
		 * the fields which are relevant क्रम posted mode. The
		 * cached remapped entry is used क्रम चयनing back to
		 * remapped mode.
		 */
		स_रखो(&irte_pi, 0, माप(irte_pi));
		dmar_copy_shared_irte(&irte_pi, &ir_data->irte_entry);

		/* Update the posted mode fields */
		irte_pi.p_pst = 1;
		irte_pi.p_urgent = 0;
		irte_pi.p_vector = vcpu_pi_info->vector;
		irte_pi.pda_l = (vcpu_pi_info->pi_desc_addr >>
				(32 - PDA_LOW_BIT)) & ~(-1UL << PDA_LOW_BIT);
		irte_pi.pda_h = (vcpu_pi_info->pi_desc_addr >> 32) &
				~(-1UL << PDA_HIGH_BIT);

		modअगरy_irte(&ir_data->irq_2_iommu, &irte_pi);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip पूर्णांकel_ir_chip = अणु
	.name			= "INTEL-IR",
	.irq_ack		= apic_ack_irq,
	.irq_set_affinity	= पूर्णांकel_ir_set_affinity,
	.irq_compose_msi_msg	= पूर्णांकel_ir_compose_msi_msg,
	.irq_set_vcpu_affinity	= पूर्णांकel_ir_set_vcpu_affinity,
पूर्ण;

अटल व्योम fill_msi_msg(काष्ठा msi_msg *msg, u32 index, u32 subhandle)
अणु
	स_रखो(msg, 0, माप(*msg));

	msg->arch_addr_lo.dmar_base_address = X86_MSI_BASE_ADDRESS_LOW;
	msg->arch_addr_lo.dmar_subhandle_valid = true;
	msg->arch_addr_lo.dmar_क्रमmat = true;
	msg->arch_addr_lo.dmar_index_0_14 = index & 0x7FFF;
	msg->arch_addr_lo.dmar_index_15 = !!(index & 0x8000);

	msg->address_hi = X86_MSI_BASE_ADDRESS_HIGH;

	msg->arch_data.dmar_subhandle = subhandle;
पूर्ण

अटल व्योम पूर्णांकel_irq_remapping_prepare_irte(काष्ठा पूर्णांकel_ir_data *data,
					     काष्ठा irq_cfg *irq_cfg,
					     काष्ठा irq_alloc_info *info,
					     पूर्णांक index, पूर्णांक sub_handle)
अणु
	काष्ठा irte *irte = &data->irte_entry;

	prepare_irte(irte, irq_cfg->vector, irq_cfg->dest_apicid);

	चयन (info->type) अणु
	हाल X86_IRQ_ALLOC_TYPE_IOAPIC:
		/* Set source-id of पूर्णांकerrupt request */
		set_ioapic_sid(irte, info->devid);
		apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG "IOAPIC[%d]: Set IRTE entry (P:%d FPD:%d Dst_Mode:%d Redir_hint:%d Trig_Mode:%d Dlvry_Mode:%X Avail:%X Vector:%02X Dest:%08X SID:%04X SQ:%X SVT:%X)\n",
			info->devid, irte->present, irte->fpd,
			irte->dst_mode, irte->redir_hपूर्णांक,
			irte->trigger_mode, irte->dlvry_mode,
			irte->avail, irte->vector, irte->dest_id,
			irte->sid, irte->sq, irte->svt);
		sub_handle = info->ioapic.pin;
		अवरोध;
	हाल X86_IRQ_ALLOC_TYPE_HPET:
		set_hpet_sid(irte, info->devid);
		अवरोध;
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSI:
	हाल X86_IRQ_ALLOC_TYPE_PCI_MSIX:
		set_msi_sid(irte,
			    pci_real_dma_dev(msi_desc_to_pci_dev(info->desc)));
		अवरोध;
	शेष:
		BUG_ON(1);
		अवरोध;
	पूर्ण
	fill_msi_msg(&data->msi_entry, index, sub_handle);
पूर्ण

अटल व्योम पूर्णांकel_मुक्त_irq_resources(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data;
	काष्ठा पूर्णांकel_ir_data *data;
	काष्ठा irq_2_iommu *irq_iommu;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq  + i);
		अगर (irq_data && irq_data->chip_data) अणु
			data = irq_data->chip_data;
			irq_iommu = &data->irq_2_iommu;
			raw_spin_lock_irqsave(&irq_2_ir_lock, flags);
			clear_entries(irq_iommu);
			raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);
			irq_करोमुख्य_reset_irq_data(irq_data);
			kमुक्त(data);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_irq_remapping_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				     व्योम *arg)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = करोमुख्य->host_data;
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा पूर्णांकel_ir_data *data, *ird;
	काष्ठा irq_data *irq_data;
	काष्ठा irq_cfg *irq_cfg;
	पूर्णांक i, ret, index;

	अगर (!info || !iommu)
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

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0)
		वापस ret;

	ret = -ENOMEM;
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ out_मुक्त_parent;

	करोwn_पढ़ो(&dmar_global_lock);
	index = alloc_irte(iommu, &data->irq_2_iommu, nr_irqs);
	up_पढ़ो(&dmar_global_lock);
	अगर (index < 0) अणु
		pr_warn("Failed to allocate IRTE\n");
		kमुक्त(data);
		जाओ out_मुक्त_parent;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		irq_cfg = irqd_cfg(irq_data);
		अगर (!irq_data || !irq_cfg) अणु
			अगर (!i)
				kमुक्त(data);
			ret = -EINVAL;
			जाओ out_मुक्त_data;
		पूर्ण

		अगर (i > 0) अणु
			ird = kzalloc(माप(*ird), GFP_KERNEL);
			अगर (!ird)
				जाओ out_मुक्त_data;
			/* Initialize the common data */
			ird->irq_2_iommu = data->irq_2_iommu;
			ird->irq_2_iommu.sub_handle = i;
		पूर्ण अन्यथा अणु
			ird = data;
		पूर्ण

		irq_data->hwirq = (index << 16) + i;
		irq_data->chip_data = ird;
		irq_data->chip = &पूर्णांकel_ir_chip;
		पूर्णांकel_irq_remapping_prepare_irte(ird, irq_cfg, info, index, i);
		irq_set_status_flags(virq + i, IRQ_MOVE_PCNTXT);
	पूर्ण
	वापस 0;

out_मुक्त_data:
	पूर्णांकel_मुक्त_irq_resources(करोमुख्य, virq, i);
out_मुक्त_parent:
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_irq_remapping_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांकel_मुक्त_irq_resources(करोमुख्य, virq, nr_irqs);
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल पूर्णांक पूर्णांकel_irq_remapping_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
					काष्ठा irq_data *irq_data, bool reserve)
अणु
	पूर्णांकel_ir_reconfigure_irte(irq_data, true);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_irq_remapping_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
					   काष्ठा irq_data *irq_data)
अणु
	काष्ठा पूर्णांकel_ir_data *data = irq_data->chip_data;
	काष्ठा irte entry;

	स_रखो(&entry, 0, माप(entry));
	modअगरy_irte(&data->irq_2_iommu, &entry);
पूर्ण

अटल पूर्णांक पूर्णांकel_irq_remapping_select(काष्ठा irq_करोमुख्य *d,
				      काष्ठा irq_fwspec *fwspec,
				      क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;

	अगर (x86_fwspec_is_ioapic(fwspec))
		iommu = map_ioapic_to_iommu(fwspec->param[0]);
	अन्यथा अगर (x86_fwspec_is_hpet(fwspec))
		iommu = map_hpet_to_iommu(fwspec->param[0]);

	वापस iommu && d == iommu->ir_करोमुख्य;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकel_ir_करोमुख्य_ops = अणु
	.select = पूर्णांकel_irq_remapping_select,
	.alloc = पूर्णांकel_irq_remapping_alloc,
	.मुक्त = पूर्णांकel_irq_remapping_मुक्त,
	.activate = पूर्णांकel_irq_remapping_activate,
	.deactivate = पूर्णांकel_irq_remapping_deactivate,
पूर्ण;

/*
 * Support of Interrupt Remapping Unit Hotplug
 */
अटल पूर्णांक dmar_ir_add(काष्ठा dmar_drhd_unit *dmaru, काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक ret;
	पूर्णांक eim = x2apic_enabled();

	ret = पूर्णांकel_cap_audit(CAP_AUDIT_HOTPLUG_IRQR, iommu);
	अगर (ret)
		वापस ret;

	अगर (eim && !ecap_eim_support(iommu->ecap)) अणु
		pr_info("DRHD %Lx: EIM not supported by DRHD, ecap %Lx\n",
			iommu->reg_phys, iommu->ecap);
		वापस -ENODEV;
	पूर्ण

	अगर (ir_parse_ioapic_hpet_scope(dmaru->hdr, iommu)) अणु
		pr_warn("DRHD %Lx: failed to parse managed IOAPIC/HPET\n",
			iommu->reg_phys);
		वापस -ENODEV;
	पूर्ण

	/* TODO: check all IOAPICs are covered by IOMMU */

	/* Setup Interrupt-remapping now. */
	ret = पूर्णांकel_setup_irq_remapping(iommu);
	अगर (ret) अणु
		pr_err("Failed to setup irq remapping for %s\n",
		       iommu->name);
		पूर्णांकel_tearकरोwn_irq_remapping(iommu);
		ir_हटाओ_ioapic_hpet_scope(iommu);
	पूर्ण अन्यथा अणु
		iommu_enable_irq_remapping(iommu);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dmar_ir_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert)
अणु
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_iommu *iommu = dmaru->iommu;

	अगर (!irq_remapping_enabled)
		वापस 0;
	अगर (iommu == शून्य)
		वापस -EINVAL;
	अगर (!ecap_ir_support(iommu->ecap))
		वापस 0;
	अगर (irq_remapping_cap(IRQ_POSTING_CAP) &&
	    !cap_pi_support(iommu->cap))
		वापस -EBUSY;

	अगर (insert) अणु
		अगर (!iommu->ir_table)
			ret = dmar_ir_add(dmaru, iommu);
	पूर्ण अन्यथा अणु
		अगर (iommu->ir_table) अणु
			अगर (!biपंचांगap_empty(iommu->ir_table->biपंचांगap,
					  INTR_REMAP_TABLE_ENTRIES)) अणु
				ret = -EBUSY;
			पूर्ण अन्यथा अणु
				iommu_disable_irq_remapping(iommu);
				पूर्णांकel_tearकरोwn_irq_remapping(iommu);
				ir_हटाओ_ioapic_hpet_scope(iommu);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
