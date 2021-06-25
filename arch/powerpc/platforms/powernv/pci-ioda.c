<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support PCI/PCIe on PowerNV platक्रमms
 *
 * Copyright 2011 Benjamin Herrenschmidt, IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/msi.h>
#समावेश <linux/iommu.h>
#समावेश <linux/rculist.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/mmzone.h>

#समावेश <misc/cxl-base.h>

#समावेश "powernv.h"
#समावेश "pci.h"
#समावेश "../../../../drivers/pci/pci.h"

#घोषणा PNV_IODA1_M64_NUM	16	/* Number of M64 BARs	*/
#घोषणा PNV_IODA1_M64_SEGS	8	/* Segments per M64 BAR	*/
#घोषणा PNV_IODA1_DMA32_SEGSIZE	0x10000000

अटल स्थिर अक्षर * स्थिर pnv_phb_names[] = अणु "IODA1", "IODA2", "NPU_OCAPI" पूर्ण;

अटल व्योम pnv_pci_ioda2_set_bypass(काष्ठा pnv_ioda_pe *pe, bool enable);
अटल व्योम pnv_pci_configure_bus(काष्ठा pci_bus *bus);

व्योम pe_level_prपूर्णांकk(स्थिर काष्ठा pnv_ioda_pe *pe, स्थिर अक्षर *level,
			    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	अक्षर pfix[32];

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (pe->flags & PNV_IODA_PE_DEV)
		strlcpy(pfix, dev_name(&pe->pdev->dev), माप(pfix));
	अन्यथा अगर (pe->flags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_ALL))
		प्र_लिखो(pfix, "%04x:%02x     ",
			pci_करोमुख्य_nr(pe->pbus), pe->pbus->number);
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अगर (pe->flags & PNV_IODA_PE_VF)
		प्र_लिखो(pfix, "%04x:%02x:%2x.%d",
			pci_करोमुख्य_nr(pe->parent_dev->bus),
			(pe->rid & 0xff00) >> 8,
			PCI_SLOT(pe->rid), PCI_FUNC(pe->rid));
#पूर्ण_अगर /* CONFIG_PCI_IOV*/

	prपूर्णांकk("%spci %s: [PE# %.2x] %pV",
	       level, pfix, pe->pe_number, &vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल bool pnv_iommu_bypass_disabled __पढ़ो_mostly;
अटल bool pci_reset_phbs __पढ़ो_mostly;

अटल पूर्णांक __init iommu_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	जबतक (*str) अणु
		अगर (!म_भेदन(str, "nobypass", 8)) अणु
			pnv_iommu_bypass_disabled = true;
			pr_info("PowerNV: IOMMU bypass window disabled.\n");
			अवरोध;
		पूर्ण
		str += म_खोज(str, ",");
		अगर (*str == ',')
			str++;
	पूर्ण

	वापस 0;
पूर्ण
early_param("iommu", iommu_setup);

अटल पूर्णांक __init pci_reset_phbs_setup(अक्षर *str)
अणु
	pci_reset_phbs = true;
	वापस 0;
पूर्ण

early_param("ppc_pci_reset_phbs", pci_reset_phbs_setup);

अटल काष्ठा pnv_ioda_pe *pnv_ioda_init_pe(काष्ठा pnv_phb *phb, पूर्णांक pe_no)
अणु
	s64 rc;

	phb->ioda.pe_array[pe_no].phb = phb;
	phb->ioda.pe_array[pe_no].pe_number = pe_no;
	phb->ioda.pe_array[pe_no].dma_setup_करोne = false;

	/*
	 * Clear the PE frozen state as it might be put पूर्णांकo frozen state
	 * in the last PCI हटाओ path. It's not harmful to करो so when the
	 * PE is alपढ़ोy in unfrozen state.
	 */
	rc = opal_pci_eeh_मुक्तze_clear(phb->opal_id, pe_no,
				       OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
	अगर (rc != OPAL_SUCCESS && rc != OPAL_UNSUPPORTED)
		pr_warn("%s: Error %lld unfreezing PHB#%x-PE#%x\n",
			__func__, rc, phb->hose->global_number, pe_no);

	वापस &phb->ioda.pe_array[pe_no];
पूर्ण

अटल व्योम pnv_ioda_reserve_pe(काष्ठा pnv_phb *phb, पूर्णांक pe_no)
अणु
	अगर (!(pe_no >= 0 && pe_no < phb->ioda.total_pe_num)) अणु
		pr_warn("%s: Invalid PE %x on PHB#%x\n",
			__func__, pe_no, phb->hose->global_number);
		वापस;
	पूर्ण

	mutex_lock(&phb->ioda.pe_alloc_mutex);
	अगर (test_and_set_bit(pe_no, phb->ioda.pe_alloc))
		pr_debug("%s: PE %x was reserved on PHB#%x\n",
			 __func__, pe_no, phb->hose->global_number);
	mutex_unlock(&phb->ioda.pe_alloc_mutex);

	pnv_ioda_init_pe(phb, pe_no);
पूर्ण

काष्ठा pnv_ioda_pe *pnv_ioda_alloc_pe(काष्ठा pnv_phb *phb, पूर्णांक count)
अणु
	काष्ठा pnv_ioda_pe *ret = शून्य;
	पूर्णांक run = 0, pe, i;

	mutex_lock(&phb->ioda.pe_alloc_mutex);

	/* scan backwards क्रम a run of @count cleared bits */
	क्रम (pe = phb->ioda.total_pe_num - 1; pe >= 0; pe--) अणु
		अगर (test_bit(pe, phb->ioda.pe_alloc)) अणु
			run = 0;
			जारी;
		पूर्ण

		run++;
		अगर (run == count)
			अवरोध;
	पूर्ण
	अगर (run != count)
		जाओ out;

	क्रम (i = pe; i < pe + count; i++) अणु
		set_bit(i, phb->ioda.pe_alloc);
		pnv_ioda_init_pe(phb, i);
	पूर्ण
	ret = &phb->ioda.pe_array[pe];

out:
	mutex_unlock(&phb->ioda.pe_alloc_mutex);
	वापस ret;
पूर्ण

व्योम pnv_ioda_मुक्त_pe(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb;
	अचिन्हित पूर्णांक pe_num = pe->pe_number;

	WARN_ON(pe->pdev);
	स_रखो(pe, 0, माप(काष्ठा pnv_ioda_pe));

	mutex_lock(&phb->ioda.pe_alloc_mutex);
	clear_bit(pe_num, phb->ioda.pe_alloc);
	mutex_unlock(&phb->ioda.pe_alloc_mutex);
पूर्ण

/* The शेष M64 BAR is shared by all PEs */
अटल पूर्णांक pnv_ioda2_init_m64(काष्ठा pnv_phb *phb)
अणु
	स्थिर अक्षर *desc;
	काष्ठा resource *r;
	s64 rc;

	/* Configure the शेष M64 BAR */
	rc = opal_pci_set_phb_mem_winकरोw(phb->opal_id,
					 OPAL_M64_WINDOW_TYPE,
					 phb->ioda.m64_bar_idx,
					 phb->ioda.m64_base,
					 0, /* unused */
					 phb->ioda.m64_size);
	अगर (rc != OPAL_SUCCESS) अणु
		desc = "configuring";
		जाओ fail;
	पूर्ण

	/* Enable the शेष M64 BAR */
	rc = opal_pci_phb_mmio_enable(phb->opal_id,
				      OPAL_M64_WINDOW_TYPE,
				      phb->ioda.m64_bar_idx,
				      OPAL_ENABLE_M64_SPLIT);
	अगर (rc != OPAL_SUCCESS) अणु
		desc = "enabling";
		जाओ fail;
	पूर्ण

	/*
	 * Exclude the segments क्रम reserved and root bus PE, which
	 * are first or last two PEs.
	 */
	r = &phb->hose->mem_resources[1];
	अगर (phb->ioda.reserved_pe_idx == 0)
		r->start += (2 * phb->ioda.m64_segsize);
	अन्यथा अगर (phb->ioda.reserved_pe_idx == (phb->ioda.total_pe_num - 1))
		r->end -= (2 * phb->ioda.m64_segsize);
	अन्यथा
		pr_warn("  Cannot strip M64 segment for reserved PE#%x\n",
			phb->ioda.reserved_pe_idx);

	वापस 0;

fail:
	pr_warn("  Failure %lld %s M64 BAR#%d\n",
		rc, desc, phb->ioda.m64_bar_idx);
	opal_pci_phb_mmio_enable(phb->opal_id,
				 OPAL_M64_WINDOW_TYPE,
				 phb->ioda.m64_bar_idx,
				 OPAL_DISABLE_M64);
	वापस -EIO;
पूर्ण

अटल व्योम pnv_ioda_reserve_dev_m64_pe(काष्ठा pci_dev *pdev,
					 अचिन्हित दीर्घ *pe_biपंचांगap)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा resource *r;
	resource_माप_प्रकार base, sgsz, start, end;
	पूर्णांक segno, i;

	base = phb->ioda.m64_base;
	sgsz = phb->ioda.m64_segsize;
	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
		r = &pdev->resource[i];
		अगर (!r->parent || !pnv_pci_is_m64(phb, r))
			जारी;

		start = ALIGN_DOWN(r->start - base, sgsz);
		end = ALIGN(r->end - base, sgsz);
		क्रम (segno = start / sgsz; segno < end / sgsz; segno++) अणु
			अगर (pe_biपंचांगap)
				set_bit(segno, pe_biपंचांगap);
			अन्यथा
				pnv_ioda_reserve_pe(phb, segno);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_ioda1_init_m64(काष्ठा pnv_phb *phb)
अणु
	काष्ठा resource *r;
	पूर्णांक index;

	/*
	 * There are 16 M64 BARs, each of which has 8 segments. So
	 * there are as many M64 segments as the maximum number of
	 * PEs, which is 128.
	 */
	क्रम (index = 0; index < PNV_IODA1_M64_NUM; index++) अणु
		अचिन्हित दीर्घ base, segsz = phb->ioda.m64_segsize;
		पूर्णांक64_t rc;

		base = phb->ioda.m64_base +
		       index * PNV_IODA1_M64_SEGS * segsz;
		rc = opal_pci_set_phb_mem_winकरोw(phb->opal_id,
				OPAL_M64_WINDOW_TYPE, index, base, 0,
				PNV_IODA1_M64_SEGS * segsz);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("  Error %lld setting M64 PHB#%x-BAR#%d\n",
				rc, phb->hose->global_number, index);
			जाओ fail;
		पूर्ण

		rc = opal_pci_phb_mmio_enable(phb->opal_id,
				OPAL_M64_WINDOW_TYPE, index,
				OPAL_ENABLE_M64_SPLIT);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("  Error %lld enabling M64 PHB#%x-BAR#%d\n",
				rc, phb->hose->global_number, index);
			जाओ fail;
		पूर्ण
	पूर्ण

	क्रम (index = 0; index < phb->ioda.total_pe_num; index++) अणु
		पूर्णांक64_t rc;

		/*
		 * P7IOC supports M64DT, which helps mapping M64 segment
		 * to one particular PE#. However, PHB3 has fixed mapping
		 * between M64 segment and PE#. In order to have same logic
		 * क्रम P7IOC and PHB3, we enक्रमce fixed mapping between M64
		 * segment and PE# on P7IOC.
		 */
		rc = opal_pci_map_pe_mmio_winकरोw(phb->opal_id,
				index, OPAL_M64_WINDOW_TYPE,
				index / PNV_IODA1_M64_SEGS,
				index % PNV_IODA1_M64_SEGS);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Error %lld mapping M64 for PHB#%x-PE#%x\n",
				__func__, rc, phb->hose->global_number,
				index);
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * Exclude the segments क्रम reserved and root bus PE, which
	 * are first or last two PEs.
	 */
	r = &phb->hose->mem_resources[1];
	अगर (phb->ioda.reserved_pe_idx == 0)
		r->start += (2 * phb->ioda.m64_segsize);
	अन्यथा अगर (phb->ioda.reserved_pe_idx == (phb->ioda.total_pe_num - 1))
		r->end -= (2 * phb->ioda.m64_segsize);
	अन्यथा
		WARN(1, "Wrong reserved PE#%x on PHB#%x\n",
		     phb->ioda.reserved_pe_idx, phb->hose->global_number);

	वापस 0;

fail:
	क्रम ( ; index >= 0; index--)
		opal_pci_phb_mmio_enable(phb->opal_id,
			OPAL_M64_WINDOW_TYPE, index, OPAL_DISABLE_M64);

	वापस -EIO;
पूर्ण

अटल व्योम pnv_ioda_reserve_m64_pe(काष्ठा pci_bus *bus,
				    अचिन्हित दीर्घ *pe_biपंचांगap,
				    bool all)
अणु
	काष्ठा pci_dev *pdev;

	list_क्रम_each_entry(pdev, &bus->devices, bus_list) अणु
		pnv_ioda_reserve_dev_m64_pe(pdev, pe_biपंचांगap);

		अगर (all && pdev->subordinate)
			pnv_ioda_reserve_m64_pe(pdev->subordinate,
						pe_biपंचांगap, all);
	पूर्ण
पूर्ण

अटल काष्ठा pnv_ioda_pe *pnv_ioda_pick_m64_pe(काष्ठा pci_bus *bus, bool all)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(bus);
	काष्ठा pnv_ioda_pe *master_pe, *pe;
	अचिन्हित दीर्घ size, *pe_alloc;
	पूर्णांक i;

	/* Root bus shouldn't use M64 */
	अगर (pci_is_root_bus(bus))
		वापस शून्य;

	/* Allocate biपंचांगap */
	size = ALIGN(phb->ioda.total_pe_num / 8, माप(अचिन्हित दीर्घ));
	pe_alloc = kzalloc(size, GFP_KERNEL);
	अगर (!pe_alloc) अणु
		pr_warn("%s: Out of memory !\n",
			__func__);
		वापस शून्य;
	पूर्ण

	/* Figure out reserved PE numbers by the PE */
	pnv_ioda_reserve_m64_pe(bus, pe_alloc, all);

	/*
	 * the current bus might not own M64 winकरोw and that's all
	 * contributed by its child buses. For the हाल, we needn't
	 * pick M64 dependent PE#.
	 */
	अगर (biपंचांगap_empty(pe_alloc, phb->ioda.total_pe_num)) अणु
		kमुक्त(pe_alloc);
		वापस शून्य;
	पूर्ण

	/*
	 * Figure out the master PE and put all slave PEs to master
	 * PE's list to क्रमm compound PE.
	 */
	master_pe = शून्य;
	i = -1;
	जबतक ((i = find_next_bit(pe_alloc, phb->ioda.total_pe_num, i + 1)) <
		phb->ioda.total_pe_num) अणु
		pe = &phb->ioda.pe_array[i];

		phb->ioda.m64_segmap[pe->pe_number] = pe->pe_number;
		अगर (!master_pe) अणु
			pe->flags |= PNV_IODA_PE_MASTER;
			INIT_LIST_HEAD(&pe->slaves);
			master_pe = pe;
		पूर्ण अन्यथा अणु
			pe->flags |= PNV_IODA_PE_SLAVE;
			pe->master = master_pe;
			list_add_tail(&pe->list, &master_pe->slaves);
		पूर्ण
	पूर्ण

	kमुक्त(pe_alloc);
	वापस master_pe;
पूर्ण

अटल व्योम __init pnv_ioda_parse_m64_winकरोw(काष्ठा pnv_phb *phb)
अणु
	काष्ठा pci_controller *hose = phb->hose;
	काष्ठा device_node *dn = hose->dn;
	काष्ठा resource *res;
	u32 m64_range[2], i;
	स्थिर __be32 *r;
	u64 pci_addr;

	अगर (phb->type != PNV_PHB_IODA1 && phb->type != PNV_PHB_IODA2) अणु
		pr_info("  Not support M64 window\n");
		वापस;
	पूर्ण

	अगर (!firmware_has_feature(FW_FEATURE_OPAL)) अणु
		pr_info("  Firmware too old to support M64 window\n");
		वापस;
	पूर्ण

	r = of_get_property(dn, "ibm,opal-m64-window", शून्य);
	अगर (!r) अणु
		pr_info("  No <ibm,opal-m64-window> on %pOF\n",
			dn);
		वापस;
	पूर्ण

	/*
	 * Find the available M64 BAR range and pickup the last one क्रम
	 * covering the whole 64-bits space. We support only one range.
	 */
	अगर (of_property_पढ़ो_u32_array(dn, "ibm,opal-available-m64-ranges",
				       m64_range, 2)) अणु
		/* In असलence of the property, assume 0..15 */
		m64_range[0] = 0;
		m64_range[1] = 16;
	पूर्ण
	/* We only support 64 bits in our allocator */
	अगर (m64_range[1] > 63) अणु
		pr_warn("%s: Limiting M64 range to 63 (from %d) on PHB#%x\n",
			__func__, m64_range[1], phb->hose->global_number);
		m64_range[1] = 63;
	पूर्ण
	/* Empty range, no m64 */
	अगर (m64_range[1] <= m64_range[0]) अणु
		pr_warn("%s: M64 empty, disabling M64 usage on PHB#%x\n",
			__func__, phb->hose->global_number);
		वापस;
	पूर्ण

	/* Configure M64 inक्रमmations */
	res = &hose->mem_resources[1];
	res->name = dn->full_name;
	res->start = of_translate_address(dn, r + 2);
	res->end = res->start + of_पढ़ो_number(r + 4, 2) - 1;
	res->flags = (IORESOURCE_MEM | IORESOURCE_MEM_64 | IORESOURCE_PREFETCH);
	pci_addr = of_पढ़ो_number(r, 2);
	hose->mem_offset[1] = res->start - pci_addr;

	phb->ioda.m64_size = resource_size(res);
	phb->ioda.m64_segsize = phb->ioda.m64_size / phb->ioda.total_pe_num;
	phb->ioda.m64_base = pci_addr;

	/* This lines up nicely with the display from processing OF ranges */
	pr_info(" MEM 0x%016llx..0x%016llx -> 0x%016llx (M64 #%d..%d)\n",
		res->start, res->end, pci_addr, m64_range[0],
		m64_range[0] + m64_range[1] - 1);

	/* Mark all M64 used up by शेष */
	phb->ioda.m64_bar_alloc = (अचिन्हित दीर्घ)-1;

	/* Use last M64 BAR to cover M64 winकरोw */
	m64_range[1]--;
	phb->ioda.m64_bar_idx = m64_range[0] + m64_range[1];

	pr_info(" Using M64 #%d as default window\n", phb->ioda.m64_bar_idx);

	/* Mark reमुख्यing ones मुक्त */
	क्रम (i = m64_range[0]; i < m64_range[1]; i++)
		clear_bit(i, &phb->ioda.m64_bar_alloc);

	/*
	 * Setup init functions क्रम M64 based on IODA version, IODA3 uses
	 * the IODA2 code.
	 */
	अगर (phb->type == PNV_PHB_IODA1)
		phb->init_m64 = pnv_ioda1_init_m64;
	अन्यथा
		phb->init_m64 = pnv_ioda2_init_m64;
पूर्ण

अटल व्योम pnv_ioda_मुक्तze_pe(काष्ठा pnv_phb *phb, पूर्णांक pe_no)
अणु
	काष्ठा pnv_ioda_pe *pe = &phb->ioda.pe_array[pe_no];
	काष्ठा pnv_ioda_pe *slave;
	s64 rc;

	/* Fetch master PE */
	अगर (pe->flags & PNV_IODA_PE_SLAVE) अणु
		pe = pe->master;
		अगर (WARN_ON(!pe || !(pe->flags & PNV_IODA_PE_MASTER)))
			वापस;

		pe_no = pe->pe_number;
	पूर्ण

	/* Freeze master PE */
	rc = opal_pci_eeh_मुक्तze_set(phb->opal_id,
				     pe_no,
				     OPAL_EEH_ACTION_SET_FREEZE_ALL);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld freezing PHB#%x-PE#%x\n",
			__func__, rc, phb->hose->global_number, pe_no);
		वापस;
	पूर्ण

	/* Freeze slave PEs */
	अगर (!(pe->flags & PNV_IODA_PE_MASTER))
		वापस;

	list_क्रम_each_entry(slave, &pe->slaves, list) अणु
		rc = opal_pci_eeh_मुक्तze_set(phb->opal_id,
					     slave->pe_number,
					     OPAL_EEH_ACTION_SET_FREEZE_ALL);
		अगर (rc != OPAL_SUCCESS)
			pr_warn("%s: Failure %lld freezing PHB#%x-PE#%x\n",
				__func__, rc, phb->hose->global_number,
				slave->pe_number);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_ioda_unमुक्तze_pe(काष्ठा pnv_phb *phb, पूर्णांक pe_no, पूर्णांक opt)
अणु
	काष्ठा pnv_ioda_pe *pe, *slave;
	s64 rc;

	/* Find master PE */
	pe = &phb->ioda.pe_array[pe_no];
	अगर (pe->flags & PNV_IODA_PE_SLAVE) अणु
		pe = pe->master;
		WARN_ON(!pe || !(pe->flags & PNV_IODA_PE_MASTER));
		pe_no = pe->pe_number;
	पूर्ण

	/* Clear frozen state क्रम master PE */
	rc = opal_pci_eeh_मुक्तze_clear(phb->opal_id, pe_no, opt);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld clear %d on PHB#%x-PE#%x\n",
			__func__, rc, opt, phb->hose->global_number, pe_no);
		वापस -EIO;
	पूर्ण

	अगर (!(pe->flags & PNV_IODA_PE_MASTER))
		वापस 0;

	/* Clear frozen state क्रम slave PEs */
	list_क्रम_each_entry(slave, &pe->slaves, list) अणु
		rc = opal_pci_eeh_मुक्तze_clear(phb->opal_id,
					     slave->pe_number,
					     opt);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Failure %lld clear %d on PHB#%x-PE#%x\n",
				__func__, rc, opt, phb->hose->global_number,
				slave->pe_number);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_ioda_get_pe_state(काष्ठा pnv_phb *phb, पूर्णांक pe_no)
अणु
	काष्ठा pnv_ioda_pe *slave, *pe;
	u8 ख_स्थितिe = 0, state;
	__be16 pcierr = 0;
	s64 rc;

	/* Sanity check on PE number */
	अगर (pe_no < 0 || pe_no >= phb->ioda.total_pe_num)
		वापस OPAL_EEH_STOPPED_PERM_UNAVAIL;

	/*
	 * Fetch the master PE and the PE instance might be
	 * not initialized yet.
	 */
	pe = &phb->ioda.pe_array[pe_no];
	अगर (pe->flags & PNV_IODA_PE_SLAVE) अणु
		pe = pe->master;
		WARN_ON(!pe || !(pe->flags & PNV_IODA_PE_MASTER));
		pe_no = pe->pe_number;
	पूर्ण

	/* Check the master PE */
	rc = opal_pci_eeh_मुक्तze_status(phb->opal_id, pe_no,
					&state, &pcierr, शून्य);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld getting "
			"PHB#%x-PE#%x state\n",
			__func__, rc,
			phb->hose->global_number, pe_no);
		वापस OPAL_EEH_STOPPED_TEMP_UNAVAIL;
	पूर्ण

	/* Check the slave PE */
	अगर (!(pe->flags & PNV_IODA_PE_MASTER))
		वापस state;

	list_क्रम_each_entry(slave, &pe->slaves, list) अणु
		rc = opal_pci_eeh_मुक्तze_status(phb->opal_id,
						slave->pe_number,
						&ख_स्थितिe,
						&pcierr,
						शून्य);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Failure %lld getting "
				"PHB#%x-PE#%x state\n",
				__func__, rc,
				phb->hose->global_number, slave->pe_number);
			वापस OPAL_EEH_STOPPED_TEMP_UNAVAIL;
		पूर्ण

		/*
		 * Override the result based on the ascending
		 * priority.
		 */
		अगर (ख_स्थितिe > state)
			state = ख_स्थितिe;
	पूर्ण

	वापस state;
पूर्ण

काष्ठा pnv_ioda_pe *pnv_pci_bdfn_to_pe(काष्ठा pnv_phb *phb, u16 bdfn)
अणु
	पूर्णांक pe_number = phb->ioda.pe_rmap[bdfn];

	अगर (pe_number == IODA_INVALID_PE)
		वापस शून्य;

	वापस &phb->ioda.pe_array[pe_number];
पूर्ण

काष्ठा pnv_ioda_pe *pnv_ioda_get_pe(काष्ठा pci_dev *dev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(dev);

	अगर (!pdn)
		वापस शून्य;
	अगर (pdn->pe_number == IODA_INVALID_PE)
		वापस शून्य;
	वापस &phb->ioda.pe_array[pdn->pe_number];
पूर्ण

अटल पूर्णांक pnv_ioda_set_one_peltv(काष्ठा pnv_phb *phb,
				  काष्ठा pnv_ioda_pe *parent,
				  काष्ठा pnv_ioda_pe *child,
				  bool is_add)
अणु
	स्थिर अक्षर *desc = is_add ? "adding" : "removing";
	uपूर्णांक8_t op = is_add ? OPAL_ADD_PE_TO_DOMAIN :
			      OPAL_REMOVE_PE_FROM_DOMAIN;
	काष्ठा pnv_ioda_pe *slave;
	दीर्घ rc;

	/* Parent PE affects child PE */
	rc = opal_pci_set_peltv(phb->opal_id, parent->pe_number,
				child->pe_number, op);
	अगर (rc != OPAL_SUCCESS) अणु
		pe_warn(child, "OPAL error %ld %s to parent PELTV\n",
			rc, desc);
		वापस -ENXIO;
	पूर्ण

	अगर (!(child->flags & PNV_IODA_PE_MASTER))
		वापस 0;

	/* Compound हाल: parent PE affects slave PEs */
	list_क्रम_each_entry(slave, &child->slaves, list) अणु
		rc = opal_pci_set_peltv(phb->opal_id, parent->pe_number,
					slave->pe_number, op);
		अगर (rc != OPAL_SUCCESS) अणु
			pe_warn(slave, "OPAL error %ld %s to parent PELTV\n",
				rc, desc);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_ioda_set_peltv(काष्ठा pnv_phb *phb,
			      काष्ठा pnv_ioda_pe *pe,
			      bool is_add)
अणु
	काष्ठा pnv_ioda_pe *slave;
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक ret;

	/*
	 * Clear PE frozen state. If it's master PE, we need
	 * clear slave PE frozen state as well.
	 */
	अगर (is_add) अणु
		opal_pci_eeh_मुक्तze_clear(phb->opal_id, pe->pe_number,
					  OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
		अगर (pe->flags & PNV_IODA_PE_MASTER) अणु
			list_क्रम_each_entry(slave, &pe->slaves, list)
				opal_pci_eeh_मुक्तze_clear(phb->opal_id,
							  slave->pe_number,
							  OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
		पूर्ण
	पूर्ण

	/*
	 * Associate PE in PELT. We need add the PE पूर्णांकo the
	 * corresponding PELT-V as well. Otherwise, the error
	 * originated from the PE might contribute to other
	 * PEs.
	 */
	ret = pnv_ioda_set_one_peltv(phb, pe, pe, is_add);
	अगर (ret)
		वापस ret;

	/* For compound PEs, any one affects all of them */
	अगर (pe->flags & PNV_IODA_PE_MASTER) अणु
		list_क्रम_each_entry(slave, &pe->slaves, list) अणु
			ret = pnv_ioda_set_one_peltv(phb, slave, pe, is_add);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (pe->flags & (PNV_IODA_PE_BUS_ALL | PNV_IODA_PE_BUS))
		pdev = pe->pbus->self;
	अन्यथा अगर (pe->flags & PNV_IODA_PE_DEV)
		pdev = pe->pdev->bus->self;
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अगर (pe->flags & PNV_IODA_PE_VF)
		pdev = pe->parent_dev;
#पूर्ण_अगर /* CONFIG_PCI_IOV */
	जबतक (pdev) अणु
		काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
		काष्ठा pnv_ioda_pe *parent;

		अगर (pdn && pdn->pe_number != IODA_INVALID_PE) अणु
			parent = &phb->ioda.pe_array[pdn->pe_number];
			ret = pnv_ioda_set_one_peltv(phb, parent, pe, is_add);
			अगर (ret)
				वापस ret;
		पूर्ण

		pdev = pdev->bus->self;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pnv_ioda_unset_peltv(काष्ठा pnv_phb *phb,
				 काष्ठा pnv_ioda_pe *pe,
				 काष्ठा pci_dev *parent)
अणु
	पूर्णांक64_t rc;

	जबतक (parent) अणु
		काष्ठा pci_dn *pdn = pci_get_pdn(parent);

		अगर (pdn && pdn->pe_number != IODA_INVALID_PE) अणु
			rc = opal_pci_set_peltv(phb->opal_id, pdn->pe_number,
						pe->pe_number,
						OPAL_REMOVE_PE_FROM_DOMAIN);
			/* XXX What to करो in हाल of error ? */
		पूर्ण
		parent = parent->bus->self;
	पूर्ण

	opal_pci_eeh_मुक्तze_clear(phb->opal_id, pe->pe_number,
				  OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);

	/* Disassociate PE in PELT */
	rc = opal_pci_set_peltv(phb->opal_id, pe->pe_number,
				pe->pe_number, OPAL_REMOVE_PE_FROM_DOMAIN);
	अगर (rc)
		pe_warn(pe, "OPAL error %lld remove self from PELTV\n", rc);
पूर्ण

पूर्णांक pnv_ioda_deconfigure_pe(काष्ठा pnv_phb *phb, काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pci_dev *parent;
	uपूर्णांक8_t bcomp, dcomp, fcomp;
	पूर्णांक64_t rc;
	दीर्घ rid_end, rid;

	/* Currently, we just deconfigure VF PE. Bus PE will always there.*/
	अगर (pe->pbus) अणु
		पूर्णांक count;

		dcomp = OPAL_IGNORE_RID_DEVICE_NUMBER;
		fcomp = OPAL_IGNORE_RID_FUNCTION_NUMBER;
		parent = pe->pbus->self;
		अगर (pe->flags & PNV_IODA_PE_BUS_ALL)
			count = resource_size(&pe->pbus->busn_res);
		अन्यथा
			count = 1;

		चयन(count) अणु
		हाल  1: bcomp = OpalPciBusAll;         अवरोध;
		हाल  2: bcomp = OpalPciBus7Bits;       अवरोध;
		हाल  4: bcomp = OpalPciBus6Bits;       अवरोध;
		हाल  8: bcomp = OpalPciBus5Bits;       अवरोध;
		हाल 16: bcomp = OpalPciBus4Bits;       अवरोध;
		हाल 32: bcomp = OpalPciBus3Bits;       अवरोध;
		शेष:
			dev_err(&pe->pbus->dev, "Number of subordinate buses %d unsupported\n",
			        count);
			/* Do an exact match only */
			bcomp = OpalPciBusAll;
		पूर्ण
		rid_end = pe->rid + (count << 8);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PCI_IOV
		अगर (pe->flags & PNV_IODA_PE_VF)
			parent = pe->parent_dev;
		अन्यथा
#पूर्ण_अगर
			parent = pe->pdev->bus->self;
		bcomp = OpalPciBusAll;
		dcomp = OPAL_COMPARE_RID_DEVICE_NUMBER;
		fcomp = OPAL_COMPARE_RID_FUNCTION_NUMBER;
		rid_end = pe->rid + 1;
	पूर्ण

	/* Clear the reverse map */
	क्रम (rid = pe->rid; rid < rid_end; rid++)
		phb->ioda.pe_rmap[rid] = IODA_INVALID_PE;

	/*
	 * Release from all parents PELT-V. NPUs करोn't have a PELTV
	 * table
	 */
	अगर (phb->type != PNV_PHB_NPU_OCAPI)
		pnv_ioda_unset_peltv(phb, pe, parent);

	rc = opal_pci_set_pe(phb->opal_id, pe->pe_number, pe->rid,
			     bcomp, dcomp, fcomp, OPAL_UNMAP_PE);
	अगर (rc)
		pe_err(pe, "OPAL error %lld trying to setup PELT table\n", rc);

	pe->pbus = शून्य;
	pe->pdev = शून्य;
#अगर_घोषित CONFIG_PCI_IOV
	pe->parent_dev = शून्य;
#पूर्ण_अगर

	वापस 0;
पूर्ण

पूर्णांक pnv_ioda_configure_pe(काष्ठा pnv_phb *phb, काष्ठा pnv_ioda_pe *pe)
अणु
	uपूर्णांक8_t bcomp, dcomp, fcomp;
	दीर्घ rc, rid_end, rid;

	/* Bus validation ? */
	अगर (pe->pbus) अणु
		पूर्णांक count;

		dcomp = OPAL_IGNORE_RID_DEVICE_NUMBER;
		fcomp = OPAL_IGNORE_RID_FUNCTION_NUMBER;
		अगर (pe->flags & PNV_IODA_PE_BUS_ALL)
			count = resource_size(&pe->pbus->busn_res);
		अन्यथा
			count = 1;

		चयन(count) अणु
		हाल  1: bcomp = OpalPciBusAll;		अवरोध;
		हाल  2: bcomp = OpalPciBus7Bits;	अवरोध;
		हाल  4: bcomp = OpalPciBus6Bits;	अवरोध;
		हाल  8: bcomp = OpalPciBus5Bits;	अवरोध;
		हाल 16: bcomp = OpalPciBus4Bits;	अवरोध;
		हाल 32: bcomp = OpalPciBus3Bits;	अवरोध;
		शेष:
			dev_err(&pe->pbus->dev, "Number of subordinate buses %d unsupported\n",
			        count);
			/* Do an exact match only */
			bcomp = OpalPciBusAll;
		पूर्ण
		rid_end = pe->rid + (count << 8);
	पूर्ण अन्यथा अणु
		bcomp = OpalPciBusAll;
		dcomp = OPAL_COMPARE_RID_DEVICE_NUMBER;
		fcomp = OPAL_COMPARE_RID_FUNCTION_NUMBER;
		rid_end = pe->rid + 1;
	पूर्ण

	/*
	 * Associate PE in PELT. We need add the PE पूर्णांकo the
	 * corresponding PELT-V as well. Otherwise, the error
	 * originated from the PE might contribute to other
	 * PEs.
	 */
	rc = opal_pci_set_pe(phb->opal_id, pe->pe_number, pe->rid,
			     bcomp, dcomp, fcomp, OPAL_MAP_PE);
	अगर (rc) अणु
		pe_err(pe, "OPAL error %ld trying to setup PELT table\n", rc);
		वापस -ENXIO;
	पूर्ण

	/*
	 * Configure PELTV. NPUs करोn't have a PELTV table so skip
	 * configuration on them.
	 */
	अगर (phb->type != PNV_PHB_NPU_OCAPI)
		pnv_ioda_set_peltv(phb, pe, true);

	/* Setup reverse map */
	क्रम (rid = pe->rid; rid < rid_end; rid++)
		phb->ioda.pe_rmap[rid] = pe->pe_number;

	/* Setup one MVTs on IODA1 */
	अगर (phb->type != PNV_PHB_IODA1) अणु
		pe->mve_number = 0;
		जाओ out;
	पूर्ण

	pe->mve_number = pe->pe_number;
	rc = opal_pci_set_mve(phb->opal_id, pe->mve_number, pe->pe_number);
	अगर (rc != OPAL_SUCCESS) अणु
		pe_err(pe, "OPAL error %ld setting up MVE %x\n",
		       rc, pe->mve_number);
		pe->mve_number = -1;
	पूर्ण अन्यथा अणु
		rc = opal_pci_set_mve_enable(phb->opal_id,
					     pe->mve_number, OPAL_ENABLE_MVE);
		अगर (rc) अणु
			pe_err(pe, "OPAL error %ld enabling MVE %x\n",
			       rc, pe->mve_number);
			pe->mve_number = -1;
		पूर्ण
	पूर्ण

out:
	वापस 0;
पूर्ण

अटल काष्ठा pnv_ioda_pe *pnv_ioda_setup_dev_PE(काष्ठा pci_dev *dev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(dev);
	काष्ठा pnv_ioda_pe *pe;

	अगर (!pdn) अणु
		pr_err("%s: Device tree node not associated properly\n",
			   pci_name(dev));
		वापस शून्य;
	पूर्ण
	अगर (pdn->pe_number != IODA_INVALID_PE)
		वापस शून्य;

	pe = pnv_ioda_alloc_pe(phb, 1);
	अगर (!pe) अणु
		pr_warn("%s: Not enough PE# available, disabling device\n",
			pci_name(dev));
		वापस शून्य;
	पूर्ण

	/* NOTE: We करोn't get a reference क्रम the poपूर्णांकer in the PE
	 * data काष्ठाure, both the device and PE काष्ठाures should be
	 * destroyed at the same समय.
	 *
	 * At some poपूर्णांक we want to हटाओ the PDN completely anyways
	 */
	pdn->pe_number = pe->pe_number;
	pe->flags = PNV_IODA_PE_DEV;
	pe->pdev = dev;
	pe->pbus = शून्य;
	pe->mve_number = -1;
	pe->rid = dev->bus->number << 8 | pdn->devfn;
	pe->device_count++;

	pe_info(pe, "Associated device to PE\n");

	अगर (pnv_ioda_configure_pe(phb, pe)) अणु
		/* XXX What करो we करो here ? */
		pnv_ioda_मुक्त_pe(pe);
		pdn->pe_number = IODA_INVALID_PE;
		pe->pdev = शून्य;
		वापस शून्य;
	पूर्ण

	/* Put PE to the list */
	mutex_lock(&phb->ioda.pe_list_mutex);
	list_add_tail(&pe->list, &phb->ioda.pe_list);
	mutex_unlock(&phb->ioda.pe_list_mutex);
	वापस pe;
पूर्ण

/*
 * There're 2 types of PCI bus sensitive PEs: One that is compromised of
 * single PCI bus. Another one that contains the primary PCI bus and its
 * subordinate PCI devices and buses. The second type of PE is normally
 * orgiriated by PCIe-to-PCI bridge or PLX चयन करोwnstream ports.
 */
अटल काष्ठा pnv_ioda_pe *pnv_ioda_setup_bus_PE(काष्ठा pci_bus *bus, bool all)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(bus);
	काष्ठा pnv_ioda_pe *pe = शून्य;
	अचिन्हित पूर्णांक pe_num;

	/*
	 * In partial hotplug हाल, the PE instance might be still alive.
	 * We should reuse it instead of allocating a new one.
	 */
	pe_num = phb->ioda.pe_rmap[bus->number << 8];
	अगर (WARN_ON(pe_num != IODA_INVALID_PE)) अणु
		pe = &phb->ioda.pe_array[pe_num];
		वापस शून्य;
	पूर्ण

	/* PE number क्रम root bus should have been reserved */
	अगर (pci_is_root_bus(bus))
		pe = &phb->ioda.pe_array[phb->ioda.root_pe_idx];

	/* Check अगर PE is determined by M64 */
	अगर (!pe)
		pe = pnv_ioda_pick_m64_pe(bus, all);

	/* The PE number isn't pinned by M64 */
	अगर (!pe)
		pe = pnv_ioda_alloc_pe(phb, 1);

	अगर (!pe) अणु
		pr_warn("%s: Not enough PE# available for PCI bus %04x:%02x\n",
			__func__, pci_करोमुख्य_nr(bus), bus->number);
		वापस शून्य;
	पूर्ण

	pe->flags |= (all ? PNV_IODA_PE_BUS_ALL : PNV_IODA_PE_BUS);
	pe->pbus = bus;
	pe->pdev = शून्य;
	pe->mve_number = -1;
	pe->rid = bus->busn_res.start << 8;

	अगर (all)
		pe_info(pe, "Secondary bus %pad..%pad associated with PE#%x\n",
			&bus->busn_res.start, &bus->busn_res.end,
			pe->pe_number);
	अन्यथा
		pe_info(pe, "Secondary bus %pad associated with PE#%x\n",
			&bus->busn_res.start, pe->pe_number);

	अगर (pnv_ioda_configure_pe(phb, pe)) अणु
		/* XXX What करो we करो here ? */
		pnv_ioda_मुक्त_pe(pe);
		pe->pbus = शून्य;
		वापस शून्य;
	पूर्ण

	/* Put PE to the list */
	list_add_tail(&pe->list, &phb->ioda.pe_list);

	वापस pe;
पूर्ण

अटल व्योम pnv_pci_ioda1_setup_dma_pe(काष्ठा pnv_phb *phb,
				       काष्ठा pnv_ioda_pe *pe);

अटल व्योम pnv_pci_ioda_dma_dev_setup(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
	काष्ठा pnv_ioda_pe *pe;

	/* Check अगर the BDFN क्रम this device is associated with a PE yet */
	pe = pnv_pci_bdfn_to_pe(phb, pdev->devfn | (pdev->bus->number << 8));
	अगर (!pe) अणु
		/* VF PEs should be pre-configured in pnv_pci_sriov_enable() */
		अगर (WARN_ON(pdev->is_virtfn))
			वापस;

		pnv_pci_configure_bus(pdev->bus);
		pe = pnv_pci_bdfn_to_pe(phb, pdev->devfn | (pdev->bus->number << 8));
		pci_info(pdev, "Configured PE#%x\n", pe ? pe->pe_number : 0xfffff);


		/*
		 * If we can't setup the IODA PE something has gone horribly
		 * wrong and we can't enable DMA क्रम the device.
		 */
		अगर (WARN_ON(!pe))
			वापस;
	पूर्ण अन्यथा अणु
		pci_info(pdev, "Added to existing PE#%x\n", pe->pe_number);
	पूर्ण

	/*
	 * We assume that bridges *probably* करोn't need to करो any DMA so we can
	 * skip allocating a TCE table, etc unless we get a non-bridge device.
	 */
	अगर (!pe->dma_setup_करोne && !pci_is_bridge(pdev)) अणु
		चयन (phb->type) अणु
		हाल PNV_PHB_IODA1:
			pnv_pci_ioda1_setup_dma_pe(phb, pe);
			अवरोध;
		हाल PNV_PHB_IODA2:
			pnv_pci_ioda2_setup_dma_pe(phb, pe);
			अवरोध;
		शेष:
			pr_warn("%s: No DMA for PHB#%x (type %d)\n",
				__func__, phb->hose->global_number, phb->type);
		पूर्ण
	पूर्ण

	अगर (pdn)
		pdn->pe_number = pe->pe_number;
	pe->device_count++;

	WARN_ON(get_dma_ops(&pdev->dev) != &dma_iommu_ops);
	pdev->dev.archdata.dma_offset = pe->tce_bypass_base;
	set_iommu_table_base(&pdev->dev, pe->table_group.tables[0]);

	/* PEs with a DMA weight of zero won't have a group */
	अगर (pe->table_group.group)
		iommu_add_device(&pe->table_group, &pdev->dev);
पूर्ण

/*
 * Reconfigure TVE#0 to be usable as 64-bit DMA space.
 *
 * The first 4GB of भव memory क्रम a PE is reserved क्रम 32-bit accesses.
 * Devices can only access more than that अगर bit 59 of the PCI address is set
 * by hardware, which indicates TVE#1 should be used instead of TVE#0.
 * Many PCI devices are not capable of addressing that many bits, and as a
 * result are limited to the 4GB of भव memory made available to 32-bit
 * devices in TVE#0.
 *
 * In order to work around this, reconfigure TVE#0 to be suitable क्रम 64-bit
 * devices by configuring the भव memory past the first 4GB inaccessible
 * by 64-bit DMAs.  This should only be used by devices that want more than
 * 4GB, and only on PEs that have no 32-bit devices.
 *
 * Currently this will only work on PHB3 (POWER8).
 */
अटल पूर्णांक pnv_pci_ioda_dma_64bit_bypass(काष्ठा pnv_ioda_pe *pe)
अणु
	u64 winकरोw_size, table_size, tce_count, addr;
	काष्ठा page *table_pages;
	u64 tce_order = 28; /* 256MB TCEs */
	__be64 *tces;
	s64 rc;

	/*
	 * Winकरोw size needs to be a घातer of two, but needs to account क्रम
	 * shअगरting memory by the 4GB offset required to skip 32bit space.
	 */
	winकरोw_size = roundup_घात_of_two(memory_hotplug_max() + (1ULL << 32));
	tce_count = winकरोw_size >> tce_order;
	table_size = tce_count << 3;

	अगर (table_size < PAGE_SIZE)
		table_size = PAGE_SIZE;

	table_pages = alloc_pages_node(pe->phb->hose->node, GFP_KERNEL,
				       get_order(table_size));
	अगर (!table_pages)
		जाओ err;

	tces = page_address(table_pages);
	अगर (!tces)
		जाओ err;

	स_रखो(tces, 0, table_size);

	क्रम (addr = 0; addr < memory_hotplug_max(); addr += (1 << tce_order)) अणु
		tces[(addr + (1ULL << 32)) >> tce_order] =
			cpu_to_be64(addr | TCE_PCI_READ | TCE_PCI_WRITE);
	पूर्ण

	rc = opal_pci_map_pe_dma_winकरोw(pe->phb->opal_id,
					pe->pe_number,
					/* reconfigure winकरोw 0 */
					(pe->pe_number << 1) + 0,
					1,
					__pa(tces),
					table_size,
					1 << tce_order);
	अगर (rc == OPAL_SUCCESS) अणु
		pe_info(pe, "Using 64-bit DMA iommu bypass (through TVE#0)\n");
		वापस 0;
	पूर्ण
err:
	pe_err(pe, "Error configuring 64-bit DMA bypass\n");
	वापस -EIO;
पूर्ण

अटल bool pnv_pci_ioda_iommu_bypass_supported(काष्ठा pci_dev *pdev,
		u64 dma_mask)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
	काष्ठा pnv_ioda_pe *pe;

	अगर (WARN_ON(!pdn || pdn->pe_number == IODA_INVALID_PE))
		वापस false;

	pe = &phb->ioda.pe_array[pdn->pe_number];
	अगर (pe->tce_bypass_enabled) अणु
		u64 top = pe->tce_bypass_base + memblock_end_of_DRAM() - 1;
		अगर (dma_mask >= top)
			वापस true;
	पूर्ण

	/*
	 * If the device can't set the TCE bypass bit but still wants
	 * to access 4GB or more, on PHB3 we can reconfigure TVE#0 to
	 * bypass the 32-bit region and be usable क्रम 64-bit DMAs.
	 * The device needs to be able to address all of this space.
	 */
	अगर (dma_mask >> 32 &&
	    dma_mask > (memory_hotplug_max() + (1ULL << 32)) &&
	    /* pe->pdev should be set अगर it's a single device, pe->pbus अगर not */
	    (pe->device_count == 1 || !pe->pbus) &&
	    phb->model == PNV_PHB_MODEL_PHB3) अणु
		/* Configure the bypass mode */
		s64 rc = pnv_pci_ioda_dma_64bit_bypass(pe);
		अगर (rc)
			वापस false;
		/* 4GB offset bypasses 32-bit space */
		pdev->dev.archdata.dma_offset = (1ULL << 32);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत __be64 __iomem *pnv_ioda_get_inval_reg(काष्ठा pnv_phb *phb,
						     bool real_mode)
अणु
	वापस real_mode ? (__be64 __iomem *)(phb->regs_phys + 0x210) :
		(phb->regs + 0x210);
पूर्ण

अटल व्योम pnv_pci_p7ioc_tce_invalidate(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ index, अचिन्हित दीर्घ npages, bool rm)
अणु
	काष्ठा iommu_table_group_link *tgl = list_first_entry_or_null(
			&tbl->it_group_list, काष्ठा iommu_table_group_link,
			next);
	काष्ठा pnv_ioda_pe *pe = container_of(tgl->table_group,
			काष्ठा pnv_ioda_pe, table_group);
	__be64 __iomem *invalidate = pnv_ioda_get_inval_reg(pe->phb, rm);
	अचिन्हित दीर्घ start, end, inc;

	start = __pa(((__be64 *)tbl->it_base) + index - tbl->it_offset);
	end = __pa(((__be64 *)tbl->it_base) + index - tbl->it_offset +
			npages - 1);

	/* p7ioc-style invalidation, 2 TCEs per ग_लिखो */
	start |= (1ull << 63);
	end |= (1ull << 63);
	inc = 16;
        end |= inc - 1;	/* round up end to be dअगरferent than start */

        mb(); /* Ensure above stores are visible */
        जबतक (start <= end) अणु
		अगर (rm)
			__raw_rm_ग_लिखोq_be(start, invalidate);
		अन्यथा
			__raw_ग_लिखोq_be(start, invalidate);

                start += inc;
        पूर्ण

	/*
	 * The iommu layer will करो another mb() क्रम us on build()
	 * and we करोn't care on मुक्त()
	 */
पूर्ण

अटल पूर्णांक pnv_ioda1_tce_build(काष्ठा iommu_table *tbl, दीर्घ index,
		दीर्घ npages, अचिन्हित दीर्घ uaddr,
		क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक ret = pnv_tce_build(tbl, index, npages, uaddr, direction,
			attrs);

	अगर (!ret)
		pnv_pci_p7ioc_tce_invalidate(tbl, index, npages, false);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IOMMU_API
/* Common क्रम IODA1 and IODA2 */
अटल पूर्णांक pnv_ioda_tce_xchg_no_समाप्त(काष्ठा iommu_table *tbl, दीर्घ index,
		अचिन्हित दीर्घ *hpa, क्रमागत dma_data_direction *direction,
		bool realmode)
अणु
	वापस pnv_tce_xchg(tbl, index, hpa, direction, !realmode);
पूर्ण
#पूर्ण_अगर

अटल व्योम pnv_ioda1_tce_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index,
		दीर्घ npages)
अणु
	pnv_tce_मुक्त(tbl, index, npages);

	pnv_pci_p7ioc_tce_invalidate(tbl, index, npages, false);
पूर्ण

अटल काष्ठा iommu_table_ops pnv_ioda1_iommu_ops = अणु
	.set = pnv_ioda1_tce_build,
#अगर_घोषित CONFIG_IOMMU_API
	.xchg_no_समाप्त = pnv_ioda_tce_xchg_no_समाप्त,
	.tce_समाप्त = pnv_pci_p7ioc_tce_invalidate,
	.useraddrptr = pnv_tce_useraddrptr,
#पूर्ण_अगर
	.clear = pnv_ioda1_tce_मुक्त,
	.get = pnv_tce_get,
पूर्ण;

#घोषणा PHB3_TCE_KILL_INVAL_ALL		PPC_BIT(0)
#घोषणा PHB3_TCE_KILL_INVAL_PE		PPC_BIT(1)
#घोषणा PHB3_TCE_KILL_INVAL_ONE		PPC_BIT(2)

अटल अंतरभूत व्योम pnv_pci_phb3_tce_invalidate_pe(काष्ठा pnv_ioda_pe *pe)
अणु
	/* 01xb - invalidate TCEs that match the specअगरied PE# */
	__be64 __iomem *invalidate = pnv_ioda_get_inval_reg(pe->phb, false);
	अचिन्हित दीर्घ val = PHB3_TCE_KILL_INVAL_PE | (pe->pe_number & 0xFF);

	mb(); /* Ensure above stores are visible */
	__raw_ग_लिखोq_be(val, invalidate);
पूर्ण

अटल व्योम pnv_pci_phb3_tce_invalidate(काष्ठा pnv_ioda_pe *pe, bool rm,
					अचिन्हित shअगरt, अचिन्हित दीर्घ index,
					अचिन्हित दीर्घ npages)
अणु
	__be64 __iomem *invalidate = pnv_ioda_get_inval_reg(pe->phb, rm);
	अचिन्हित दीर्घ start, end, inc;

	/* We'll invalidate DMA address in PE scope */
	start = PHB3_TCE_KILL_INVAL_ONE;
	start |= (pe->pe_number & 0xFF);
	end = start;

	/* Figure out the start, end and step */
	start |= (index << shअगरt);
	end |= ((index + npages - 1) << shअगरt);
	inc = (0x1ull << shअगरt);
	mb();

	जबतक (start <= end) अणु
		अगर (rm)
			__raw_rm_ग_लिखोq_be(start, invalidate);
		अन्यथा
			__raw_ग_लिखोq_be(start, invalidate);
		start += inc;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pnv_pci_ioda2_tce_invalidate_pe(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb;

	अगर (phb->model == PNV_PHB_MODEL_PHB3 && phb->regs)
		pnv_pci_phb3_tce_invalidate_pe(pe);
	अन्यथा
		opal_pci_tce_समाप्त(phb->opal_id, OPAL_PCI_TCE_KILL_PE,
				  pe->pe_number, 0, 0, 0);
पूर्ण

अटल व्योम pnv_pci_ioda2_tce_invalidate(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ index, अचिन्हित दीर्घ npages, bool rm)
अणु
	काष्ठा iommu_table_group_link *tgl;

	list_क्रम_each_entry_lockless(tgl, &tbl->it_group_list, next) अणु
		काष्ठा pnv_ioda_pe *pe = container_of(tgl->table_group,
				काष्ठा pnv_ioda_pe, table_group);
		काष्ठा pnv_phb *phb = pe->phb;
		अचिन्हित पूर्णांक shअगरt = tbl->it_page_shअगरt;

		अगर (phb->model == PNV_PHB_MODEL_PHB3 && phb->regs)
			pnv_pci_phb3_tce_invalidate(pe, rm, shअगरt,
						    index, npages);
		अन्यथा
			opal_pci_tce_समाप्त(phb->opal_id,
					  OPAL_PCI_TCE_KILL_PAGES,
					  pe->pe_number, 1u << shअगरt,
					  index << shअगरt, npages);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_ioda2_tce_build(काष्ठा iommu_table *tbl, दीर्घ index,
		दीर्घ npages, अचिन्हित दीर्घ uaddr,
		क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक ret = pnv_tce_build(tbl, index, npages, uaddr, direction,
			attrs);

	अगर (!ret)
		pnv_pci_ioda2_tce_invalidate(tbl, index, npages, false);

	वापस ret;
पूर्ण

अटल व्योम pnv_ioda2_tce_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index,
		दीर्घ npages)
अणु
	pnv_tce_मुक्त(tbl, index, npages);

	pnv_pci_ioda2_tce_invalidate(tbl, index, npages, false);
पूर्ण

अटल काष्ठा iommu_table_ops pnv_ioda2_iommu_ops = अणु
	.set = pnv_ioda2_tce_build,
#अगर_घोषित CONFIG_IOMMU_API
	.xchg_no_समाप्त = pnv_ioda_tce_xchg_no_समाप्त,
	.tce_समाप्त = pnv_pci_ioda2_tce_invalidate,
	.useraddrptr = pnv_tce_useraddrptr,
#पूर्ण_अगर
	.clear = pnv_ioda2_tce_मुक्त,
	.get = pnv_tce_get,
	.मुक्त = pnv_pci_ioda2_table_मुक्त_pages,
पूर्ण;

अटल पूर्णांक pnv_pci_ioda_dev_dma_weight(काष्ठा pci_dev *dev, व्योम *data)
अणु
	अचिन्हित पूर्णांक *weight = (अचिन्हित पूर्णांक *)data;

	/* This is quite simplistic. The "base" weight of a device
	 * is 10. 0 means no DMA is to be accounted क्रम it.
	 */
	अगर (dev->hdr_type != PCI_HEADER_TYPE_NORMAL)
		वापस 0;

	अगर (dev->class == PCI_CLASS_SERIAL_USB_UHCI ||
	    dev->class == PCI_CLASS_SERIAL_USB_OHCI ||
	    dev->class == PCI_CLASS_SERIAL_USB_EHCI)
		*weight += 3;
	अन्यथा अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_RAID)
		*weight += 15;
	अन्यथा
		*weight += 10;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pnv_pci_ioda_pe_dma_weight(काष्ठा pnv_ioda_pe *pe)
अणु
	अचिन्हित पूर्णांक weight = 0;

	/* SRIOV VF has same DMA32 weight as its PF */
#अगर_घोषित CONFIG_PCI_IOV
	अगर ((pe->flags & PNV_IODA_PE_VF) && pe->parent_dev) अणु
		pnv_pci_ioda_dev_dma_weight(pe->parent_dev, &weight);
		वापस weight;
	पूर्ण
#पूर्ण_अगर

	अगर ((pe->flags & PNV_IODA_PE_DEV) && pe->pdev) अणु
		pnv_pci_ioda_dev_dma_weight(pe->pdev, &weight);
	पूर्ण अन्यथा अगर ((pe->flags & PNV_IODA_PE_BUS) && pe->pbus) अणु
		काष्ठा pci_dev *pdev;

		list_क्रम_each_entry(pdev, &pe->pbus->devices, bus_list)
			pnv_pci_ioda_dev_dma_weight(pdev, &weight);
	पूर्ण अन्यथा अगर ((pe->flags & PNV_IODA_PE_BUS_ALL) && pe->pbus) अणु
		pci_walk_bus(pe->pbus, pnv_pci_ioda_dev_dma_weight, &weight);
	पूर्ण

	वापस weight;
पूर्ण

अटल व्योम pnv_pci_ioda1_setup_dma_pe(काष्ठा pnv_phb *phb,
				       काष्ठा pnv_ioda_pe *pe)
अणु

	काष्ठा page *tce_mem = शून्य;
	काष्ठा iommu_table *tbl;
	अचिन्हित पूर्णांक weight, total_weight = 0;
	अचिन्हित पूर्णांक tce32_segsz, base, segs, avail, i;
	पूर्णांक64_t rc;
	व्योम *addr;

	/* XXX FIXME: Handle 64-bit only DMA devices */
	/* XXX FIXME: Provide 64-bit DMA facilities & non-4K TCE tables etc.. */
	/* XXX FIXME: Allocate multi-level tables on PHB3 */
	weight = pnv_pci_ioda_pe_dma_weight(pe);
	अगर (!weight)
		वापस;

	pci_walk_bus(phb->hose->bus, pnv_pci_ioda_dev_dma_weight,
		     &total_weight);
	segs = (weight * phb->ioda.dma32_count) / total_weight;
	अगर (!segs)
		segs = 1;

	/*
	 * Allocate contiguous DMA32 segments. We begin with the expected
	 * number of segments. With one more attempt, the number of DMA32
	 * segments to be allocated is decreased by one until one segment
	 * is allocated successfully.
	 */
	करो अणु
		क्रम (base = 0; base <= phb->ioda.dma32_count - segs; base++) अणु
			क्रम (avail = 0, i = base; i < base + segs; i++) अणु
				अगर (phb->ioda.dma32_segmap[i] ==
				    IODA_INVALID_PE)
					avail++;
			पूर्ण

			अगर (avail == segs)
				जाओ found;
		पूर्ण
	पूर्ण जबतक (--segs);

	अगर (!segs) अणु
		pe_warn(pe, "No available DMA32 segments\n");
		वापस;
	पूर्ण

found:
	tbl = pnv_pci_table_alloc(phb->hose->node);
	अगर (WARN_ON(!tbl))
		वापस;

	iommu_रेजिस्टर_group(&pe->table_group, phb->hose->global_number,
			pe->pe_number);
	pnv_pci_link_table_and_group(phb->hose->node, 0, tbl, &pe->table_group);

	/* Grab a 32-bit TCE table */
	pe_info(pe, "DMA weight %d (%d), assigned (%d) %d DMA32 segments\n",
		weight, total_weight, base, segs);
	pe_info(pe, " Setting up 32-bit TCE table at %08x..%08x\n",
		base * PNV_IODA1_DMA32_SEGSIZE,
		(base + segs) * PNV_IODA1_DMA32_SEGSIZE - 1);

	/* XXX Currently, we allocate one big contiguous table क्रम the
	 * TCEs. We only really need one chunk per 256M of TCE space
	 * (ie per segment) but that's an optimization क्रम later, it
	 * requires some added smarts with our get/put_tce implementation
	 *
	 * Each TCE page is 4KB in size and each TCE entry occupies 8
	 * bytes
	 */
	tce32_segsz = PNV_IODA1_DMA32_SEGSIZE >> (IOMMU_PAGE_SHIFT_4K - 3);
	tce_mem = alloc_pages_node(phb->hose->node, GFP_KERNEL,
				   get_order(tce32_segsz * segs));
	अगर (!tce_mem) अणु
		pe_err(pe, " Failed to allocate a 32-bit TCE memory\n");
		जाओ fail;
	पूर्ण
	addr = page_address(tce_mem);
	स_रखो(addr, 0, tce32_segsz * segs);

	/* Configure HW */
	क्रम (i = 0; i < segs; i++) अणु
		rc = opal_pci_map_pe_dma_winकरोw(phb->opal_id,
					      pe->pe_number,
					      base + i, 1,
					      __pa(addr) + tce32_segsz * i,
					      tce32_segsz, IOMMU_PAGE_SIZE_4K);
		अगर (rc) अणु
			pe_err(pe, " Failed to configure 32-bit TCE table, err %lld\n",
			       rc);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Setup DMA32 segment mapping */
	क्रम (i = base; i < base + segs; i++)
		phb->ioda.dma32_segmap[i] = pe->pe_number;

	/* Setup linux iommu table */
	pnv_pci_setup_iommu_table(tbl, addr, tce32_segsz * segs,
				  base * PNV_IODA1_DMA32_SEGSIZE,
				  IOMMU_PAGE_SHIFT_4K);

	tbl->it_ops = &pnv_ioda1_iommu_ops;
	pe->table_group.tce32_start = tbl->it_offset << tbl->it_page_shअगरt;
	pe->table_group.tce32_size = tbl->it_size << tbl->it_page_shअगरt;
	अगर (!iommu_init_table(tbl, phb->hose->node, 0, 0))
		panic("Failed to initialize iommu table");

	pe->dma_setup_करोne = true;
	वापस;
 fail:
	/* XXX Failure: Try to fallback to 64-bit only ? */
	अगर (tce_mem)
		__मुक्त_pages(tce_mem, get_order(tce32_segsz * segs));
	अगर (tbl) अणु
		pnv_pci_unlink_table_and_group(tbl, &pe->table_group);
		iommu_tce_table_put(tbl);
	पूर्ण
पूर्ण

अटल दीर्घ pnv_pci_ioda2_set_winकरोw(काष्ठा iommu_table_group *table_group,
		पूर्णांक num, काष्ठा iommu_table *tbl)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group, काष्ठा pnv_ioda_pe,
			table_group);
	काष्ठा pnv_phb *phb = pe->phb;
	पूर्णांक64_t rc;
	स्थिर अचिन्हित दीर्घ size = tbl->it_indirect_levels ?
			tbl->it_level_size : tbl->it_size;
	स्थिर __u64 start_addr = tbl->it_offset << tbl->it_page_shअगरt;
	स्थिर __u64 win_size = tbl->it_size << tbl->it_page_shअगरt;

	pe_info(pe, "Setting up window#%d %llx..%llx pg=%lx\n",
		num, start_addr, start_addr + win_size - 1,
		IOMMU_PAGE_SIZE(tbl));

	/*
	 * Map TCE table through TVT. The TVE index is the PE number
	 * shअगरted by 1 bit क्रम 32-bits DMA space.
	 */
	rc = opal_pci_map_pe_dma_winकरोw(phb->opal_id,
			pe->pe_number,
			(pe->pe_number << 1) + num,
			tbl->it_indirect_levels + 1,
			__pa(tbl->it_base),
			size << 3,
			IOMMU_PAGE_SIZE(tbl));
	अगर (rc) अणु
		pe_err(pe, "Failed to configure TCE table, err %lld\n", rc);
		वापस rc;
	पूर्ण

	pnv_pci_link_table_and_group(phb->hose->node, num,
			tbl, &pe->table_group);
	pnv_pci_ioda2_tce_invalidate_pe(pe);

	वापस 0;
पूर्ण

अटल व्योम pnv_pci_ioda2_set_bypass(काष्ठा pnv_ioda_pe *pe, bool enable)
अणु
	uपूर्णांक16_t winकरोw_id = (pe->pe_number << 1 ) + 1;
	पूर्णांक64_t rc;

	pe_info(pe, "%sabling 64-bit DMA bypass\n", enable ? "En" : "Dis");
	अगर (enable) अणु
		phys_addr_t top = memblock_end_of_DRAM();

		top = roundup_घात_of_two(top);
		rc = opal_pci_map_pe_dma_winकरोw_real(pe->phb->opal_id,
						     pe->pe_number,
						     winकरोw_id,
						     pe->tce_bypass_base,
						     top);
	पूर्ण अन्यथा अणु
		rc = opal_pci_map_pe_dma_winकरोw_real(pe->phb->opal_id,
						     pe->pe_number,
						     winकरोw_id,
						     pe->tce_bypass_base,
						     0);
	पूर्ण
	अगर (rc)
		pe_err(pe, "OPAL error %lld configuring bypass window\n", rc);
	अन्यथा
		pe->tce_bypass_enabled = enable;
पूर्ण

अटल दीर्घ pnv_pci_ioda2_create_table(काष्ठा iommu_table_group *table_group,
		पूर्णांक num, __u32 page_shअगरt, __u64 winकरोw_size, __u32 levels,
		bool alloc_userspace_copy, काष्ठा iommu_table **ptbl)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group, काष्ठा pnv_ioda_pe,
			table_group);
	पूर्णांक nid = pe->phb->hose->node;
	__u64 bus_offset = num ? pe->tce_bypass_base : table_group->tce32_start;
	दीर्घ ret;
	काष्ठा iommu_table *tbl;

	tbl = pnv_pci_table_alloc(nid);
	अगर (!tbl)
		वापस -ENOMEM;

	tbl->it_ops = &pnv_ioda2_iommu_ops;

	ret = pnv_pci_ioda2_table_alloc_pages(nid,
			bus_offset, page_shअगरt, winकरोw_size,
			levels, alloc_userspace_copy, tbl);
	अगर (ret) अणु
		iommu_tce_table_put(tbl);
		वापस ret;
	पूर्ण

	*ptbl = tbl;

	वापस 0;
पूर्ण

अटल दीर्घ pnv_pci_ioda2_setup_शेष_config(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा iommu_table *tbl = शून्य;
	दीर्घ rc;
	अचिन्हित दीर्घ res_start, res_end;

	/*
	 * crashkernel= specअगरies the kdump kernel's maximum memory at
	 * some offset and there is no guaranteed the result is a घातer
	 * of 2, which will cause errors later.
	 */
	स्थिर u64 max_memory = __roundकरोwn_घात_of_two(memory_hotplug_max());

	/*
	 * In memory स्थिरrained environments, e.g. kdump kernel, the
	 * DMA winकरोw can be larger than available memory, which will
	 * cause errors later.
	 */
	स्थिर u64 maxblock = 1UL << (PAGE_SHIFT + MAX_ORDER - 1);

	/*
	 * We create the शेष winकरोw as big as we can. The स्थिरraपूर्णांक is
	 * the max order of allocation possible. The TCE table is likely to
	 * end up being multilevel and with on-demand allocation in place,
	 * the initial use is not going to be huge as the शेष winकरोw aims
	 * to support crippled devices (i.e. not fully 64bit DMAble) only.
	 */
	/* iommu_table::it_map uses 1 bit per IOMMU page, hence 8 */
	स्थिर u64 winकरोw_size = min((maxblock * 8) << PAGE_SHIFT, max_memory);
	/* Each TCE level cannot exceed maxblock so go multilevel अगर needed */
	अचिन्हित दीर्घ tces_order = ilog2(winकरोw_size >> PAGE_SHIFT);
	अचिन्हित दीर्घ tcelevel_order = ilog2(maxblock >> 3);
	अचिन्हित पूर्णांक levels = tces_order / tcelevel_order;

	अगर (tces_order % tcelevel_order)
		levels += 1;
	/*
	 * We try to stick to शेष levels (which is >1 at the moment) in
	 * order to save memory by relying on on-deमुख्य TCE level allocation.
	 */
	levels = max_t(अचिन्हित पूर्णांक, levels, POWERNV_IOMMU_DEFAULT_LEVELS);

	rc = pnv_pci_ioda2_create_table(&pe->table_group, 0, PAGE_SHIFT,
			winकरोw_size, levels, false, &tbl);
	अगर (rc) अणु
		pe_err(pe, "Failed to create 32-bit TCE table, err %ld",
				rc);
		वापस rc;
	पूर्ण

	/* We use top part of 32bit space क्रम MMIO so exclude it from DMA */
	res_start = 0;
	res_end = 0;
	अगर (winकरोw_size > pe->phb->ioda.m32_pci_base) अणु
		res_start = pe->phb->ioda.m32_pci_base >> tbl->it_page_shअगरt;
		res_end = min(winकरोw_size, SZ_4G) >> tbl->it_page_shअगरt;
	पूर्ण

	अगर (iommu_init_table(tbl, pe->phb->hose->node, res_start, res_end))
		rc = pnv_pci_ioda2_set_winकरोw(&pe->table_group, 0, tbl);
	अन्यथा
		rc = -ENOMEM;
	अगर (rc) अणु
		pe_err(pe, "Failed to configure 32-bit TCE table, err %ld\n", rc);
		iommu_tce_table_put(tbl);
		tbl = शून्य; /* This clears iommu_table_base below */
	पूर्ण
	अगर (!pnv_iommu_bypass_disabled)
		pnv_pci_ioda2_set_bypass(pe, true);

	/*
	 * Set table base क्रम the हाल of IOMMU DMA use. Usually this is करोne
	 * from dma_dev_setup() which is not called when a device is वापसed
	 * from VFIO so करो it here.
	 */
	अगर (pe->pdev)
		set_iommu_table_base(&pe->pdev->dev, tbl);

	वापस 0;
पूर्ण

अटल दीर्घ pnv_pci_ioda2_unset_winकरोw(काष्ठा iommu_table_group *table_group,
		पूर्णांक num)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group, काष्ठा pnv_ioda_pe,
			table_group);
	काष्ठा pnv_phb *phb = pe->phb;
	दीर्घ ret;

	pe_info(pe, "Removing DMA window #%d\n", num);

	ret = opal_pci_map_pe_dma_winकरोw(phb->opal_id, pe->pe_number,
			(pe->pe_number << 1) + num,
			0/* levels */, 0/* table address */,
			0/* table size */, 0/* page size */);
	अगर (ret)
		pe_warn(pe, "Unmapping failed, ret = %ld\n", ret);
	अन्यथा
		pnv_pci_ioda2_tce_invalidate_pe(pe);

	pnv_pci_unlink_table_and_group(table_group->tables[num], table_group);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IOMMU_API
अचिन्हित दीर्घ pnv_pci_ioda2_get_table_size(__u32 page_shअगरt,
		__u64 winकरोw_size, __u32 levels)
अणु
	अचिन्हित दीर्घ bytes = 0;
	स्थिर अचिन्हित winकरोw_shअगरt = ilog2(winकरोw_size);
	अचिन्हित entries_shअगरt = winकरोw_shअगरt - page_shअगरt;
	अचिन्हित table_shअगरt = entries_shअगरt + 3;
	अचिन्हित दीर्घ tce_table_size = max(0x1000UL, 1UL << table_shअगरt);
	अचिन्हित दीर्घ direct_table_size;

	अगर (!levels || (levels > POWERNV_IOMMU_MAX_LEVELS) ||
			!is_घातer_of_2(winकरोw_size))
		वापस 0;

	/* Calculate a direct table size from winकरोw_size and levels */
	entries_shअगरt = (entries_shअगरt + levels - 1) / levels;
	table_shअगरt = entries_shअगरt + 3;
	table_shअगरt = max_t(अचिन्हित, table_shअगरt, PAGE_SHIFT);
	direct_table_size =  1UL << table_shअगरt;

	क्रम ( ; levels; --levels) अणु
		bytes += ALIGN(tce_table_size, direct_table_size);

		tce_table_size /= direct_table_size;
		tce_table_size <<= 3;
		tce_table_size = max_t(अचिन्हित दीर्घ,
				tce_table_size, direct_table_size);
	पूर्ण

	वापस bytes + bytes; /* one क्रम HW table, one क्रम userspace copy */
पूर्ण

अटल दीर्घ pnv_pci_ioda2_create_table_userspace(
		काष्ठा iommu_table_group *table_group,
		पूर्णांक num, __u32 page_shअगरt, __u64 winकरोw_size, __u32 levels,
		काष्ठा iommu_table **ptbl)
अणु
	दीर्घ ret = pnv_pci_ioda2_create_table(table_group,
			num, page_shअगरt, winकरोw_size, levels, true, ptbl);

	अगर (!ret)
		(*ptbl)->it_allocated_size = pnv_pci_ioda2_get_table_size(
				page_shअगरt, winकरोw_size, levels);
	वापस ret;
पूर्ण

अटल व्योम pnv_ioda_setup_bus_dma(काष्ठा pnv_ioda_pe *pe, काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		set_iommu_table_base(&dev->dev, pe->table_group.tables[0]);
		dev->dev.archdata.dma_offset = pe->tce_bypass_base;

		अगर ((pe->flags & PNV_IODA_PE_BUS_ALL) && dev->subordinate)
			pnv_ioda_setup_bus_dma(pe, dev->subordinate);
	पूर्ण
पूर्ण

अटल व्योम pnv_ioda2_take_ownership(काष्ठा iommu_table_group *table_group)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group, काष्ठा pnv_ioda_pe,
						table_group);
	/* Store @tbl as pnv_pci_ioda2_unset_winकरोw() resets it */
	काष्ठा iommu_table *tbl = pe->table_group.tables[0];

	pnv_pci_ioda2_set_bypass(pe, false);
	pnv_pci_ioda2_unset_winकरोw(&pe->table_group, 0);
	अगर (pe->pbus)
		pnv_ioda_setup_bus_dma(pe, pe->pbus);
	अन्यथा अगर (pe->pdev)
		set_iommu_table_base(&pe->pdev->dev, शून्य);
	iommu_tce_table_put(tbl);
पूर्ण

अटल व्योम pnv_ioda2_release_ownership(काष्ठा iommu_table_group *table_group)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group, काष्ठा pnv_ioda_pe,
						table_group);

	pnv_pci_ioda2_setup_शेष_config(pe);
	अगर (pe->pbus)
		pnv_ioda_setup_bus_dma(pe, pe->pbus);
पूर्ण

अटल काष्ठा iommu_table_group_ops pnv_pci_ioda2_ops = अणु
	.get_table_size = pnv_pci_ioda2_get_table_size,
	.create_table = pnv_pci_ioda2_create_table_userspace,
	.set_winकरोw = pnv_pci_ioda2_set_winकरोw,
	.unset_winकरोw = pnv_pci_ioda2_unset_winकरोw,
	.take_ownership = pnv_ioda2_take_ownership,
	.release_ownership = pnv_ioda2_release_ownership,
पूर्ण;
#पूर्ण_अगर

व्योम pnv_pci_ioda2_setup_dma_pe(काष्ठा pnv_phb *phb,
				काष्ठा pnv_ioda_pe *pe)
अणु
	पूर्णांक64_t rc;

	/* TVE #1 is selected by PCI address bit 59 */
	pe->tce_bypass_base = 1ull << 59;

	/* The PE will reserve all possible 32-bits space */
	pe_info(pe, "Setting up 32-bit TCE table at 0..%08x\n",
		phb->ioda.m32_pci_base);

	/* Setup linux iommu table */
	pe->table_group.tce32_start = 0;
	pe->table_group.tce32_size = phb->ioda.m32_pci_base;
	pe->table_group.max_dynamic_winकरोws_supported =
			IOMMU_TABLE_GROUP_MAX_TABLES;
	pe->table_group.max_levels = POWERNV_IOMMU_MAX_LEVELS;
	pe->table_group.pgsizes = pnv_ioda_parse_tce_sizes(phb);

	rc = pnv_pci_ioda2_setup_शेष_config(pe);
	अगर (rc)
		वापस;

#अगर_घोषित CONFIG_IOMMU_API
	pe->table_group.ops = &pnv_pci_ioda2_ops;
	iommu_रेजिस्टर_group(&pe->table_group, phb->hose->global_number,
			     pe->pe_number);
#पूर्ण_अगर
	pe->dma_setup_करोne = true;
पूर्ण

पूर्णांक64_t pnv_opal_pci_msi_eoi(काष्ठा irq_chip *chip, अचिन्हित पूर्णांक hw_irq)
अणु
	काष्ठा pnv_phb *phb = container_of(chip, काष्ठा pnv_phb,
					   ioda.irq_chip);

	वापस opal_pci_msi_eoi(phb->opal_id, hw_irq);
पूर्ण

अटल व्योम pnv_ioda2_msi_eoi(काष्ठा irq_data *d)
अणु
	पूर्णांक64_t rc;
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(d);

	rc = pnv_opal_pci_msi_eoi(chip, hw_irq);
	WARN_ON_ONCE(rc);

	icp_native_eoi(d);
पूर्ण


व्योम pnv_set_msi_irq_chip(काष्ठा pnv_phb *phb, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *idata;
	काष्ठा irq_chip *ichip;

	/* The MSI EOI OPAL call is only needed on PHB3 */
	अगर (phb->model != PNV_PHB_MODEL_PHB3)
		वापस;

	अगर (!phb->ioda.irq_chip_init) अणु
		/*
		 * First समय we setup an MSI IRQ, we need to setup the
		 * corresponding IRQ chip to route correctly.
		 */
		idata = irq_get_irq_data(virq);
		ichip = irq_data_get_irq_chip(idata);
		phb->ioda.irq_chip_init = 1;
		phb->ioda.irq_chip = *ichip;
		phb->ioda.irq_chip.irq_eoi = pnv_ioda2_msi_eoi;
	पूर्ण
	irq_set_chip(virq, &phb->ioda.irq_chip);
पूर्ण

/*
 * Returns true अगरf chip is something that we could call
 * pnv_opal_pci_msi_eoi क्रम.
 */
bool is_pnv_opal_msi(काष्ठा irq_chip *chip)
अणु
	वापस chip->irq_eoi == pnv_ioda2_msi_eoi;
पूर्ण
EXPORT_SYMBOL_GPL(is_pnv_opal_msi);

अटल पूर्णांक pnv_pci_ioda_msi_setup(काष्ठा pnv_phb *phb, काष्ठा pci_dev *dev,
				  अचिन्हित पूर्णांक hwirq, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक is_64, काष्ठा msi_msg *msg)
अणु
	काष्ठा pnv_ioda_pe *pe = pnv_ioda_get_pe(dev);
	अचिन्हित पूर्णांक xive_num = hwirq - phb->msi_base;
	__be32 data;
	पूर्णांक rc;

	/* No PE asचिन्हित ? bail out ... no MSI क्रम you ! */
	अगर (pe == शून्य)
		वापस -ENXIO;

	/* Check अगर we have an MVE */
	अगर (pe->mve_number < 0)
		वापस -ENXIO;

	/* Force 32-bit MSI on some broken devices */
	अगर (dev->no_64bit_msi)
		is_64 = 0;

	/* Assign XIVE to PE */
	rc = opal_pci_set_xive_pe(phb->opal_id, pe->pe_number, xive_num);
	अगर (rc) अणु
		pr_warn("%s: OPAL error %d setting XIVE %d PE\n",
			pci_name(dev), rc, xive_num);
		वापस -EIO;
	पूर्ण

	अगर (is_64) अणु
		__be64 addr64;

		rc = opal_get_msi_64(phb->opal_id, pe->mve_number, xive_num, 1,
				     &addr64, &data);
		अगर (rc) अणु
			pr_warn("%s: OPAL error %d getting 64-bit MSI data\n",
				pci_name(dev), rc);
			वापस -EIO;
		पूर्ण
		msg->address_hi = be64_to_cpu(addr64) >> 32;
		msg->address_lo = be64_to_cpu(addr64) & 0xfffffffful;
	पूर्ण अन्यथा अणु
		__be32 addr32;

		rc = opal_get_msi_32(phb->opal_id, pe->mve_number, xive_num, 1,
				     &addr32, &data);
		अगर (rc) अणु
			pr_warn("%s: OPAL error %d getting 32-bit MSI data\n",
				pci_name(dev), rc);
			वापस -EIO;
		पूर्ण
		msg->address_hi = 0;
		msg->address_lo = be32_to_cpu(addr32);
	पूर्ण
	msg->data = be32_to_cpu(data);

	pnv_set_msi_irq_chip(phb, virq);

	pr_devel("%s: %s-bit MSI on hwirq %x (xive #%d),"
		 " address=%x_%08x data=%x PE# %x\n",
		 pci_name(dev), is_64 ? "64" : "32", hwirq, xive_num,
		 msg->address_hi, msg->address_lo, data, pe->pe_number);

	वापस 0;
पूर्ण

अटल व्योम pnv_pci_init_ioda_msis(काष्ठा pnv_phb *phb)
अणु
	अचिन्हित पूर्णांक count;
	स्थिर __be32 *prop = of_get_property(phb->hose->dn,
					     "ibm,opal-msi-ranges", शून्य);
	अगर (!prop) अणु
		/* BML Fallback */
		prop = of_get_property(phb->hose->dn, "msi-ranges", शून्य);
	पूर्ण
	अगर (!prop)
		वापस;

	phb->msi_base = be32_to_cpup(prop);
	count = be32_to_cpup(prop + 1);
	अगर (msi_biपंचांगap_alloc(&phb->msi_bmp, count, phb->hose->dn)) अणु
		pr_err("PCI %d: Failed to allocate MSI bitmap !\n",
		       phb->hose->global_number);
		वापस;
	पूर्ण

	phb->msi_setup = pnv_pci_ioda_msi_setup;
	phb->msi32_support = 1;
	pr_info("  Allocated bitmap for %d MSIs (base IRQ 0x%x)\n",
		count, phb->msi_base);
पूर्ण

अटल व्योम pnv_ioda_setup_pe_res(काष्ठा pnv_ioda_pe *pe,
				  काष्ठा resource *res)
अणु
	काष्ठा pnv_phb *phb = pe->phb;
	काष्ठा pci_bus_region region;
	पूर्णांक index;
	पूर्णांक64_t rc;

	अगर (!res || !res->flags || res->start > res->end)
		वापस;

	अगर (res->flags & IORESOURCE_IO) अणु
		region.start = res->start - phb->ioda.io_pci_base;
		region.end   = res->end - phb->ioda.io_pci_base;
		index = region.start / phb->ioda.io_segsize;

		जबतक (index < phb->ioda.total_pe_num &&
		       region.start <= region.end) अणु
			phb->ioda.io_segmap[index] = pe->pe_number;
			rc = opal_pci_map_pe_mmio_winकरोw(phb->opal_id,
				pe->pe_number, OPAL_IO_WINDOW_TYPE, 0, index);
			अगर (rc != OPAL_SUCCESS) अणु
				pr_err("%s: Error %lld mapping IO segment#%d to PE#%x\n",
				       __func__, rc, index, pe->pe_number);
				अवरोध;
			पूर्ण

			region.start += phb->ioda.io_segsize;
			index++;
		पूर्ण
	पूर्ण अन्यथा अगर ((res->flags & IORESOURCE_MEM) &&
		   !pnv_pci_is_m64(phb, res)) अणु
		region.start = res->start -
			       phb->hose->mem_offset[0] -
			       phb->ioda.m32_pci_base;
		region.end   = res->end -
			       phb->hose->mem_offset[0] -
			       phb->ioda.m32_pci_base;
		index = region.start / phb->ioda.m32_segsize;

		जबतक (index < phb->ioda.total_pe_num &&
		       region.start <= region.end) अणु
			phb->ioda.m32_segmap[index] = pe->pe_number;
			rc = opal_pci_map_pe_mmio_winकरोw(phb->opal_id,
				pe->pe_number, OPAL_M32_WINDOW_TYPE, 0, index);
			अगर (rc != OPAL_SUCCESS) अणु
				pr_err("%s: Error %lld mapping M32 segment#%d to PE#%x",
				       __func__, rc, index, pe->pe_number);
				अवरोध;
			पूर्ण

			region.start += phb->ioda.m32_segsize;
			index++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function is supposed to be called on basis of PE from top
 * to bottom style. So the the I/O or MMIO segment asचिन्हित to
 * parent PE could be overridden by its child PEs अगर necessary.
 */
अटल व्योम pnv_ioda_setup_pe_seg(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक i;

	/*
	 * NOTE: We only care PCI bus based PE क्रम now. For PCI
	 * device based PE, क्रम example SRIOV sensitive VF should
	 * be figured out later.
	 */
	BUG_ON(!(pe->flags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_ALL)));

	list_क्रम_each_entry(pdev, &pe->pbus->devices, bus_list) अणु
		क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++)
			pnv_ioda_setup_pe_res(pe, &pdev->resource[i]);

		/*
		 * If the PE contains all subordinate PCI buses, the
		 * winकरोws of the child bridges should be mapped to
		 * the PE as well.
		 */
		अगर (!(pe->flags & PNV_IODA_PE_BUS_ALL) || !pci_is_bridge(pdev))
			जारी;
		क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++)
			pnv_ioda_setup_pe_res(pe,
				&pdev->resource[PCI_BRIDGE_RESOURCES + i]);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक pnv_pci_diag_data_set(व्योम *data, u64 val)
अणु
	काष्ठा pnv_phb *phb = data;
	s64 ret;

	/* Retrieve the diag data from firmware */
	ret = opal_pci_get_phb_diag_data2(phb->opal_id, phb->diag_data,
					  phb->diag_data_size);
	अगर (ret != OPAL_SUCCESS)
		वापस -EIO;

	/* Prपूर्णांक the diag data to the kernel log */
	pnv_pci_dump_phb_diag_data(phb->hose, phb->diag_data);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(pnv_pci_diag_data_fops, शून्य, pnv_pci_diag_data_set,
			 "%llu\n");

अटल पूर्णांक pnv_pci_ioda_pe_dump(व्योम *data, u64 val)
अणु
	काष्ठा pnv_phb *phb = data;
	पूर्णांक pe_num;

	क्रम (pe_num = 0; pe_num < phb->ioda.total_pe_num; pe_num++) अणु
		काष्ठा pnv_ioda_pe *pe = &phb->ioda.pe_array[pe_num];

		अगर (!test_bit(pe_num, phb->ioda.pe_alloc))
			जारी;

		pe_warn(pe, "rid: %04x dev count: %2d flags: %s%s%s%s%s%s\n",
			pe->rid, pe->device_count,
			(pe->flags & PNV_IODA_PE_DEV) ? "dev " : "",
			(pe->flags & PNV_IODA_PE_BUS) ? "bus " : "",
			(pe->flags & PNV_IODA_PE_BUS_ALL) ? "all " : "",
			(pe->flags & PNV_IODA_PE_MASTER) ? "master " : "",
			(pe->flags & PNV_IODA_PE_SLAVE) ? "slave " : "",
			(pe->flags & PNV_IODA_PE_VF) ? "vf " : "");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(pnv_pci_ioda_pe_dump_fops, शून्य,
			 pnv_pci_ioda_pe_dump, "%llu\n");

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल व्योम pnv_pci_ioda_create_dbgfs(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा pci_controller *hose, *पंचांगp;
	काष्ठा pnv_phb *phb;
	अक्षर name[16];

	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node) अणु
		phb = hose->निजी_data;

		प्र_लिखो(name, "PCI%04x", hose->global_number);
		phb->dbgfs = debugfs_create_dir(name, घातerpc_debugfs_root);

		debugfs_create_file_unsafe("dump_diag_regs", 0200, phb->dbgfs,
					   phb, &pnv_pci_diag_data_fops);
		debugfs_create_file_unsafe("dump_ioda_pe_state", 0200, phb->dbgfs,
					   phb, &pnv_pci_ioda_pe_dump_fops);
	पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
पूर्ण

अटल व्योम pnv_pci_enable_bridge(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev = bus->self;
	काष्ठा pci_bus *child;

	/* Empty bus ? bail */
	अगर (list_empty(&bus->devices))
		वापस;

	/*
	 * If there's a bridge associated with that bus enable it. This works
	 * around races in the generic code अगर the enabling is करोne during
	 * parallel probing. This can be हटाओd once those races have been
	 * fixed.
	 */
	अगर (dev) अणु
		पूर्णांक rc = pci_enable_device(dev);
		अगर (rc)
			pci_err(dev, "Error enabling bridge (%d)\n", rc);
		pci_set_master(dev);
	पूर्ण

	/* Perक्रमm the same to child busses */
	list_क्रम_each_entry(child, &bus->children, node)
		pnv_pci_enable_bridge(child);
पूर्ण

अटल व्योम pnv_pci_enable_bridges(व्योम)
अणु
	काष्ठा pci_controller *hose;

	list_क्रम_each_entry(hose, &hose_list, list_node)
		pnv_pci_enable_bridge(hose->bus);
पूर्ण

अटल व्योम pnv_pci_ioda_fixup(व्योम)
अणु
	pnv_pci_ioda_create_dbgfs();

	pnv_pci_enable_bridges();

#अगर_घोषित CONFIG_EEH
	pnv_eeh_post_init();
#पूर्ण_अगर
पूर्ण

/*
 * Returns the alignment क्रम I/O or memory winकरोws क्रम P2P
 * bridges. That actually depends on how PEs are segmented.
 * For now, we वापस I/O or M32 segment size क्रम PE sensitive
 * P2P bridges. Otherwise, the शेष values (4KiB क्रम I/O,
 * 1MiB क्रम memory) will be वापसed.
 *
 * The current PCI bus might be put पूर्णांकo one PE, which was
 * create against the parent PCI bridge. For that हाल, we
 * needn't enlarge the alignment so that we can save some
 * resources.
 */
अटल resource_माप_प्रकार pnv_pci_winकरोw_alignment(काष्ठा pci_bus *bus,
						अचिन्हित दीर्घ type)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(bus);
	पूर्णांक num_pci_bridges = 0;
	काष्ठा pci_dev *bridge;

	bridge = bus->self;
	जबतक (bridge) अणु
		अगर (pci_pcie_type(bridge) == PCI_EXP_TYPE_PCI_BRIDGE) अणु
			num_pci_bridges++;
			अगर (num_pci_bridges >= 2)
				वापस 1;
		पूर्ण

		bridge = bridge->bus->self;
	पूर्ण

	/*
	 * We fall back to M32 अगर M64 isn't supported. We enक्रमce the M64
	 * alignment क्रम any 64-bit resource, PCIe करोesn't care and
	 * bridges only करो 64-bit prefetchable anyway.
	 */
	अगर (phb->ioda.m64_segsize && pnv_pci_is_m64_flags(type))
		वापस phb->ioda.m64_segsize;
	अगर (type & IORESOURCE_MEM)
		वापस phb->ioda.m32_segsize;

	वापस phb->ioda.io_segsize;
पूर्ण

/*
 * We are updating root port or the upstream port of the
 * bridge behind the root port with PHB's winकरोws in order
 * to accommodate the changes on required resources during
 * PCI (slot) hotplug, which is connected to either root
 * port or the करोwnstream ports of PCIe चयन behind the
 * root port.
 */
अटल व्योम pnv_pci_fixup_bridge_resources(काष्ठा pci_bus *bus,
					   अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा pci_dev *bridge = bus->self;
	काष्ठा resource *r, *w;
	bool msi_region = false;
	पूर्णांक i;

	/* Check अगर we need apply fixup to the bridge's winकरोws */
	अगर (!pci_is_root_bus(bridge->bus) &&
	    !pci_is_root_bus(bridge->bus->self->bus))
		वापस;

	/* Fixup the resources */
	क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++) अणु
		r = &bridge->resource[PCI_BRIDGE_RESOURCES + i];
		अगर (!r->flags || !r->parent)
			जारी;

		w = शून्य;
		अगर (r->flags & type & IORESOURCE_IO)
			w = &hose->io_resource;
		अन्यथा अगर (pnv_pci_is_m64(phb, r) &&
			 (type & IORESOURCE_PREFETCH) &&
			 phb->ioda.m64_segsize)
			w = &hose->mem_resources[1];
		अन्यथा अगर (r->flags & type & IORESOURCE_MEM) अणु
			w = &hose->mem_resources[0];
			msi_region = true;
		पूर्ण

		r->start = w->start;
		r->end = w->end;

		/* The 64KB 32-bits MSI region shouldn't be included in
		 * the 32-bits bridge winकरोw. Otherwise, we can see strange
		 * issues. One of them is EEH error observed on Garrison.
		 *
		 * Exclude top 1MB region which is the minimal alignment of
		 * 32-bits bridge winकरोw.
		 */
		अगर (msi_region) अणु
			r->end += 0x10000;
			r->end -= 0x100000;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pnv_pci_configure_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *bridge = bus->self;
	काष्ठा pnv_ioda_pe *pe;
	bool all = (bridge && pci_pcie_type(bridge) == PCI_EXP_TYPE_PCI_BRIDGE);

	dev_info(&bus->dev, "Configuring PE for bus\n");

	/* Don't assign PE to PCI bus, which doesn't have subordinate devices */
	अगर (WARN_ON(list_empty(&bus->devices)))
		वापस;

	/* Reserve PEs according to used M64 resources */
	pnv_ioda_reserve_m64_pe(bus, शून्य, all);

	/*
	 * Assign PE. We might run here because of partial hotplug.
	 * For the हाल, we just pick up the existing PE and should
	 * not allocate resources again.
	 */
	pe = pnv_ioda_setup_bus_PE(bus, all);
	अगर (!pe)
		वापस;

	pnv_ioda_setup_pe_seg(pe);
पूर्ण

अटल resource_माप_प्रकार pnv_pci_शेष_alignment(व्योम)
अणु
	वापस PAGE_SIZE;
पूर्ण

/* Prevent enabling devices क्रम which we couldn't properly
 * assign a PE
 */
अटल bool pnv_pci_enable_device_hook(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dn *pdn;

	pdn = pci_get_pdn(dev);
	अगर (!pdn || pdn->pe_number == IODA_INVALID_PE) अणु
		pci_err(dev, "pci_enable_device() blocked, no PE assigned.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool pnv_ocapi_enable_device_hook(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dn *pdn;
	काष्ठा pnv_ioda_pe *pe;

	pdn = pci_get_pdn(dev);
	अगर (!pdn)
		वापस false;

	अगर (pdn->pe_number == IODA_INVALID_PE) अणु
		pe = pnv_ioda_setup_dev_PE(dev);
		अगर (!pe)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल दीर्घ pnv_pci_ioda1_unset_winकरोw(काष्ठा iommu_table_group *table_group,
				       पूर्णांक num)
अणु
	काष्ठा pnv_ioda_pe *pe = container_of(table_group,
					      काष्ठा pnv_ioda_pe, table_group);
	काष्ठा pnv_phb *phb = pe->phb;
	अचिन्हित पूर्णांक idx;
	दीर्घ rc;

	pe_info(pe, "Removing DMA window #%d\n", num);
	क्रम (idx = 0; idx < phb->ioda.dma32_count; idx++) अणु
		अगर (phb->ioda.dma32_segmap[idx] != pe->pe_number)
			जारी;

		rc = opal_pci_map_pe_dma_winकरोw(phb->opal_id, pe->pe_number,
						idx, 0, 0ul, 0ul, 0ul);
		अगर (rc != OPAL_SUCCESS) अणु
			pe_warn(pe, "Failure %ld unmapping DMA32 segment#%d\n",
				rc, idx);
			वापस rc;
		पूर्ण

		phb->ioda.dma32_segmap[idx] = IODA_INVALID_PE;
	पूर्ण

	pnv_pci_unlink_table_and_group(table_group->tables[num], table_group);
	वापस OPAL_SUCCESS;
पूर्ण

अटल व्योम pnv_pci_ioda1_release_pe_dma(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा iommu_table *tbl = pe->table_group.tables[0];
	पूर्णांक64_t rc;

	अगर (!pe->dma_setup_करोne)
		वापस;

	rc = pnv_pci_ioda1_unset_winकरोw(&pe->table_group, 0);
	अगर (rc != OPAL_SUCCESS)
		वापस;

	pnv_pci_p7ioc_tce_invalidate(tbl, tbl->it_offset, tbl->it_size, false);
	अगर (pe->table_group.group) अणु
		iommu_group_put(pe->table_group.group);
		WARN_ON(pe->table_group.group);
	पूर्ण

	मुक्त_pages(tbl->it_base, get_order(tbl->it_size << 3));
	iommu_tce_table_put(tbl);
पूर्ण

व्योम pnv_pci_ioda2_release_pe_dma(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा iommu_table *tbl = pe->table_group.tables[0];
	पूर्णांक64_t rc;

	अगर (!pe->dma_setup_करोne)
		वापस;

	rc = pnv_pci_ioda2_unset_winकरोw(&pe->table_group, 0);
	अगर (rc)
		pe_warn(pe, "OPAL error %lld release DMA window\n", rc);

	pnv_pci_ioda2_set_bypass(pe, false);
	अगर (pe->table_group.group) अणु
		iommu_group_put(pe->table_group.group);
		WARN_ON(pe->table_group.group);
	पूर्ण

	iommu_tce_table_put(tbl);
पूर्ण

अटल व्योम pnv_ioda_मुक्त_pe_seg(काष्ठा pnv_ioda_pe *pe,
				 अचिन्हित लघु win,
				 अचिन्हित पूर्णांक *map)
अणु
	काष्ठा pnv_phb *phb = pe->phb;
	पूर्णांक idx;
	पूर्णांक64_t rc;

	क्रम (idx = 0; idx < phb->ioda.total_pe_num; idx++) अणु
		अगर (map[idx] != pe->pe_number)
			जारी;

		rc = opal_pci_map_pe_mmio_winकरोw(phb->opal_id,
				phb->ioda.reserved_pe_idx, win, 0, idx);

		अगर (rc != OPAL_SUCCESS)
			pe_warn(pe, "Error %lld unmapping (%d) segment#%d\n",
				rc, win, idx);

		map[idx] = IODA_INVALID_PE;
	पूर्ण
पूर्ण

अटल व्योम pnv_ioda_release_pe_seg(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb;

	अगर (phb->type == PNV_PHB_IODA1) अणु
		pnv_ioda_मुक्त_pe_seg(pe, OPAL_IO_WINDOW_TYPE,
				     phb->ioda.io_segmap);
		pnv_ioda_मुक्त_pe_seg(pe, OPAL_M32_WINDOW_TYPE,
				     phb->ioda.m32_segmap);
		/* M64 is pre-configured by pnv_ioda1_init_m64() */
	पूर्ण अन्यथा अगर (phb->type == PNV_PHB_IODA2) अणु
		pnv_ioda_मुक्त_pe_seg(pe, OPAL_M32_WINDOW_TYPE,
				     phb->ioda.m32_segmap);
	पूर्ण
पूर्ण

अटल व्योम pnv_ioda_release_pe(काष्ठा pnv_ioda_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb;
	काष्ठा pnv_ioda_pe *slave, *पंचांगp;

	pe_info(pe, "Releasing PE\n");

	mutex_lock(&phb->ioda.pe_list_mutex);
	list_del(&pe->list);
	mutex_unlock(&phb->ioda.pe_list_mutex);

	चयन (phb->type) अणु
	हाल PNV_PHB_IODA1:
		pnv_pci_ioda1_release_pe_dma(pe);
		अवरोध;
	हाल PNV_PHB_IODA2:
		pnv_pci_ioda2_release_pe_dma(pe);
		अवरोध;
	हाल PNV_PHB_NPU_OCAPI:
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	pnv_ioda_release_pe_seg(pe);
	pnv_ioda_deconfigure_pe(pe->phb, pe);

	/* Release slave PEs in the compound PE */
	अगर (pe->flags & PNV_IODA_PE_MASTER) अणु
		list_क्रम_each_entry_safe(slave, पंचांगp, &pe->slaves, list) अणु
			list_del(&slave->list);
			pnv_ioda_मुक्त_pe(slave);
		पूर्ण
	पूर्ण

	/*
	 * The PE क्रम root bus can be हटाओd because of hotplug in EEH
	 * recovery क्रम fenced PHB error. We need to mark the PE dead so
	 * that it can be populated again in PCI hot add path. The PE
	 * shouldn't be destroyed as it's the global reserved resource.
	 */
	अगर (phb->ioda.root_pe_idx == pe->pe_number)
		वापस;

	pnv_ioda_मुक्त_pe(pe);
पूर्ण

अटल व्योम pnv_pci_release_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
	काष्ठा pnv_ioda_pe *pe;

	/* The VF PE state is torn करोwn when sriov_disable() is called */
	अगर (pdev->is_virtfn)
		वापस;

	अगर (!pdn || pdn->pe_number == IODA_INVALID_PE)
		वापस;

#अगर_घोषित CONFIG_PCI_IOV
	/*
	 * FIXME: Try move this to sriov_disable(). It's here since we allocate
	 * the iov state at probe समय since we need to fiddle with the IOV
	 * resources.
	 */
	अगर (pdev->is_physfn)
		kमुक्त(pdev->dev.archdata.iov_data);
#पूर्ण_अगर

	/*
	 * PCI hotplug can happen as part of EEH error recovery. The @pdn
	 * isn't हटाओd and added afterwards in this scenario. We should
	 * set the PE number in @pdn to an invalid one. Otherwise, the PE's
	 * device count is decreased on removing devices जबतक failing to
	 * be increased on adding devices. It leads to unbalanced PE's device
	 * count and eventually make normal PCI hotplug path broken.
	 */
	pe = &phb->ioda.pe_array[pdn->pe_number];
	pdn->pe_number = IODA_INVALID_PE;

	WARN_ON(--pe->device_count < 0);
	अगर (pe->device_count == 0)
		pnv_ioda_release_pe(pe);
पूर्ण

अटल व्योम pnv_pci_ioda_shutकरोwn(काष्ठा pci_controller *hose)
अणु
	काष्ठा pnv_phb *phb = hose->निजी_data;

	opal_pci_reset(phb->opal_id, OPAL_RESET_PCI_IODA_TABLE,
		       OPAL_ASSERT_RESET);
पूर्ण

अटल व्योम pnv_pci_ioda_dma_bus_setup(काष्ठा pci_bus *bus)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(bus);
	काष्ठा pnv_ioda_pe *pe;

	list_क्रम_each_entry(pe, &phb->ioda.pe_list, list) अणु
		अगर (!(pe->flags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_ALL)))
			जारी;

		अगर (!pe->pbus)
			जारी;

		अगर (bus->number == ((pe->rid >> 8) & 0xFF)) अणु
			pe->pbus = bus;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_controller_ops pnv_pci_ioda_controller_ops = अणु
	.dma_dev_setup		= pnv_pci_ioda_dma_dev_setup,
	.dma_bus_setup		= pnv_pci_ioda_dma_bus_setup,
	.iommu_bypass_supported	= pnv_pci_ioda_iommu_bypass_supported,
	.setup_msi_irqs		= pnv_setup_msi_irqs,
	.tearकरोwn_msi_irqs	= pnv_tearकरोwn_msi_irqs,
	.enable_device_hook	= pnv_pci_enable_device_hook,
	.release_device		= pnv_pci_release_device,
	.winकरोw_alignment	= pnv_pci_winकरोw_alignment,
	.setup_bridge		= pnv_pci_fixup_bridge_resources,
	.reset_secondary_bus	= pnv_pci_reset_secondary_bus,
	.shutकरोwn		= pnv_pci_ioda_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा pci_controller_ops pnv_npu_ocapi_ioda_controller_ops = अणु
	.enable_device_hook	= pnv_ocapi_enable_device_hook,
	.release_device		= pnv_pci_release_device,
	.winकरोw_alignment	= pnv_pci_winकरोw_alignment,
	.reset_secondary_bus	= pnv_pci_reset_secondary_bus,
	.shutकरोwn		= pnv_pci_ioda_shutकरोwn,
पूर्ण;

अटल व्योम __init pnv_pci_init_ioda_phb(काष्ठा device_node *np,
					 u64 hub_id, पूर्णांक ioda_type)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा pnv_phb *phb;
	अचिन्हित दीर्घ size, m64map_off, m32map_off, pemap_off;
	अचिन्हित दीर्घ iomap_off = 0, dma32map_off = 0;
	काष्ठा pnv_ioda_pe *root_pe;
	काष्ठा resource r;
	स्थिर __be64 *prop64;
	स्थिर __be32 *prop32;
	पूर्णांक len;
	अचिन्हित पूर्णांक segno;
	u64 phb_id;
	व्योम *aux;
	दीर्घ rc;

	अगर (!of_device_is_available(np))
		वापस;

	pr_info("Initializing %s PHB (%pOF)\n",	pnv_phb_names[ioda_type], np);

	prop64 = of_get_property(np, "ibm,opal-phbid", शून्य);
	अगर (!prop64) अणु
		pr_err("  Missing \"ibm,opal-phbid\" property !\n");
		वापस;
	पूर्ण
	phb_id = be64_to_cpup(prop64);
	pr_debug("  PHB-ID  : 0x%016llx\n", phb_id);

	phb = kzalloc(माप(*phb), GFP_KERNEL);
	अगर (!phb)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*phb));

	/* Allocate PCI controller */
	phb->hose = hose = pcibios_alloc_controller(np);
	अगर (!phb->hose) अणु
		pr_err("  Can't allocate PCI controller for %pOF\n",
		       np);
		memblock_मुक्त(__pa(phb), माप(काष्ठा pnv_phb));
		वापस;
	पूर्ण

	spin_lock_init(&phb->lock);
	prop32 = of_get_property(np, "bus-range", &len);
	अगर (prop32 && len == 8) अणु
		hose->first_busno = be32_to_cpu(prop32[0]);
		hose->last_busno = be32_to_cpu(prop32[1]);
	पूर्ण अन्यथा अणु
		pr_warn("  Broken <bus-range> on %pOF\n", np);
		hose->first_busno = 0;
		hose->last_busno = 0xff;
	पूर्ण
	hose->निजी_data = phb;
	phb->hub_id = hub_id;
	phb->opal_id = phb_id;
	phb->type = ioda_type;
	mutex_init(&phb->ioda.pe_alloc_mutex);

	/* Detect specअगरic models क्रम error handling */
	अगर (of_device_is_compatible(np, "ibm,p7ioc-pciex"))
		phb->model = PNV_PHB_MODEL_P7IOC;
	अन्यथा अगर (of_device_is_compatible(np, "ibm,power8-pciex"))
		phb->model = PNV_PHB_MODEL_PHB3;
	अन्यथा
		phb->model = PNV_PHB_MODEL_UNKNOWN;

	/* Initialize diagnostic data buffer */
	prop32 = of_get_property(np, "ibm,phb-diag-data-size", शून्य);
	अगर (prop32)
		phb->diag_data_size = be32_to_cpup(prop32);
	अन्यथा
		phb->diag_data_size = PNV_PCI_DIAG_BUF_SIZE;

	phb->diag_data = kzalloc(phb->diag_data_size, GFP_KERNEL);
	अगर (!phb->diag_data)
		panic("%s: Failed to allocate %u bytes\n", __func__,
		      phb->diag_data_size);

	/* Parse 32-bit and IO ranges (अगर any) */
	pci_process_bridge_OF_ranges(hose, np, !hose->global_number);

	/* Get रेजिस्टरs */
	अगर (!of_address_to_resource(np, 0, &r)) अणु
		phb->regs_phys = r.start;
		phb->regs = ioremap(r.start, resource_size(&r));
		अगर (phb->regs == शून्य)
			pr_err("  Failed to map registers !\n");
	पूर्ण

	/* Initialize more IODA stuff */
	phb->ioda.total_pe_num = 1;
	prop32 = of_get_property(np, "ibm,opal-num-pes", शून्य);
	अगर (prop32)
		phb->ioda.total_pe_num = be32_to_cpup(prop32);
	prop32 = of_get_property(np, "ibm,opal-reserved-pe", शून्य);
	अगर (prop32)
		phb->ioda.reserved_pe_idx = be32_to_cpup(prop32);

	/* Invalidate RID to PE# mapping */
	क्रम (segno = 0; segno < ARRAY_SIZE(phb->ioda.pe_rmap); segno++)
		phb->ioda.pe_rmap[segno] = IODA_INVALID_PE;

	/* Parse 64-bit MMIO range */
	pnv_ioda_parse_m64_winकरोw(phb);

	phb->ioda.m32_size = resource_size(&hose->mem_resources[0]);
	/* FW Has alपढ़ोy off top 64k of M32 space (MSI space) */
	phb->ioda.m32_size += 0x10000;

	phb->ioda.m32_segsize = phb->ioda.m32_size / phb->ioda.total_pe_num;
	phb->ioda.m32_pci_base = hose->mem_resources[0].start - hose->mem_offset[0];
	phb->ioda.io_size = hose->pci_io_size;
	phb->ioda.io_segsize = phb->ioda.io_size / phb->ioda.total_pe_num;
	phb->ioda.io_pci_base = 0; /* XXX calculate this ? */

	/* Calculate how many 32-bit TCE segments we have */
	phb->ioda.dma32_count = phb->ioda.m32_pci_base /
				PNV_IODA1_DMA32_SEGSIZE;

	/* Allocate aux data & arrays. We करोn't have IO ports on PHB3 */
	size = ALIGN(max_t(अचिन्हित, phb->ioda.total_pe_num, 8) / 8,
			माप(अचिन्हित दीर्घ));
	m64map_off = size;
	size += phb->ioda.total_pe_num * माप(phb->ioda.m64_segmap[0]);
	m32map_off = size;
	size += phb->ioda.total_pe_num * माप(phb->ioda.m32_segmap[0]);
	अगर (phb->type == PNV_PHB_IODA1) अणु
		iomap_off = size;
		size += phb->ioda.total_pe_num * माप(phb->ioda.io_segmap[0]);
		dma32map_off = size;
		size += phb->ioda.dma32_count *
			माप(phb->ioda.dma32_segmap[0]);
	पूर्ण
	pemap_off = size;
	size += phb->ioda.total_pe_num * माप(काष्ठा pnv_ioda_pe);
	aux = kzalloc(size, GFP_KERNEL);
	अगर (!aux)
		panic("%s: Failed to allocate %lu bytes\n", __func__, size);

	phb->ioda.pe_alloc = aux;
	phb->ioda.m64_segmap = aux + m64map_off;
	phb->ioda.m32_segmap = aux + m32map_off;
	क्रम (segno = 0; segno < phb->ioda.total_pe_num; segno++) अणु
		phb->ioda.m64_segmap[segno] = IODA_INVALID_PE;
		phb->ioda.m32_segmap[segno] = IODA_INVALID_PE;
	पूर्ण
	अगर (phb->type == PNV_PHB_IODA1) अणु
		phb->ioda.io_segmap = aux + iomap_off;
		क्रम (segno = 0; segno < phb->ioda.total_pe_num; segno++)
			phb->ioda.io_segmap[segno] = IODA_INVALID_PE;

		phb->ioda.dma32_segmap = aux + dma32map_off;
		क्रम (segno = 0; segno < phb->ioda.dma32_count; segno++)
			phb->ioda.dma32_segmap[segno] = IODA_INVALID_PE;
	पूर्ण
	phb->ioda.pe_array = aux + pemap_off;

	/*
	 * Choose PE number क्रम root bus, which shouldn't have
	 * M64 resources consumed by its child devices. To pick
	 * the PE number adjacent to the reserved one अगर possible.
	 */
	pnv_ioda_reserve_pe(phb, phb->ioda.reserved_pe_idx);
	अगर (phb->ioda.reserved_pe_idx == 0) अणु
		phb->ioda.root_pe_idx = 1;
		pnv_ioda_reserve_pe(phb, phb->ioda.root_pe_idx);
	पूर्ण अन्यथा अगर (phb->ioda.reserved_pe_idx == (phb->ioda.total_pe_num - 1)) अणु
		phb->ioda.root_pe_idx = phb->ioda.reserved_pe_idx - 1;
		pnv_ioda_reserve_pe(phb, phb->ioda.root_pe_idx);
	पूर्ण अन्यथा अणु
		/* otherwise just allocate one */
		root_pe = pnv_ioda_alloc_pe(phb, 1);
		phb->ioda.root_pe_idx = root_pe->pe_number;
	पूर्ण

	INIT_LIST_HEAD(&phb->ioda.pe_list);
	mutex_init(&phb->ioda.pe_list_mutex);

	/* Calculate how many 32-bit TCE segments we have */
	phb->ioda.dma32_count = phb->ioda.m32_pci_base /
				PNV_IODA1_DMA32_SEGSIZE;

#अगर 0 /* We should really करो that ... */
	rc = opal_pci_set_phb_mem_winकरोw(opal->phb_id,
					 winकरोw_type,
					 winकरोw_num,
					 starting_real_address,
					 starting_pci_address,
					 segment_size);
#पूर्ण_अगर

	pr_info("  %03d (%03d) PE's M32: 0x%x [segment=0x%x]\n",
		phb->ioda.total_pe_num, phb->ioda.reserved_pe_idx,
		phb->ioda.m32_size, phb->ioda.m32_segsize);
	अगर (phb->ioda.m64_size)
		pr_info("                 M64: 0x%lx [segment=0x%lx]\n",
			phb->ioda.m64_size, phb->ioda.m64_segsize);
	अगर (phb->ioda.io_size)
		pr_info("                  IO: 0x%x [segment=0x%x]\n",
			phb->ioda.io_size, phb->ioda.io_segsize);


	phb->hose->ops = &pnv_pci_ops;
	phb->get_pe_state = pnv_ioda_get_pe_state;
	phb->मुक्तze_pe = pnv_ioda_मुक्तze_pe;
	phb->unमुक्तze_pe = pnv_ioda_unमुक्तze_pe;

	/* Setup MSI support */
	pnv_pci_init_ioda_msis(phb);

	/*
	 * We pass the PCI probe flag PCI_REASSIGN_ALL_RSRC here
	 * to let the PCI core करो resource assignment. It's supposed
	 * that the PCI core will करो correct I/O and MMIO alignment
	 * क्रम the P2P bridge bars so that each PCI bus (excluding
	 * the child P2P bridges) can क्रमm inभागidual PE.
	 */
	ppc_md.pcibios_fixup = pnv_pci_ioda_fixup;

	चयन (phb->type) अणु
	हाल PNV_PHB_NPU_OCAPI:
		hose->controller_ops = pnv_npu_ocapi_ioda_controller_ops;
		अवरोध;
	शेष:
		hose->controller_ops = pnv_pci_ioda_controller_ops;
	पूर्ण

	ppc_md.pcibios_शेष_alignment = pnv_pci_शेष_alignment;

#अगर_घोषित CONFIG_PCI_IOV
	ppc_md.pcibios_fixup_sriov = pnv_pci_ioda_fixup_iov;
	ppc_md.pcibios_iov_resource_alignment = pnv_pci_iov_resource_alignment;
	ppc_md.pcibios_sriov_enable = pnv_pcibios_sriov_enable;
	ppc_md.pcibios_sriov_disable = pnv_pcibios_sriov_disable;
#पूर्ण_अगर

	pci_add_flags(PCI_REASSIGN_ALL_RSRC);

	/* Reset IODA tables to a clean state */
	rc = opal_pci_reset(phb_id, OPAL_RESET_PCI_IODA_TABLE, OPAL_ASSERT_RESET);
	अगर (rc)
		pr_warn("  OPAL Error %ld performing IODA table reset !\n", rc);

	/*
	 * If we're running in kdump kernel, the previous kernel never
	 * shutकरोwn PCI devices correctly. We alपढ़ोy got IODA table
	 * cleaned out. So we have to issue PHB reset to stop all PCI
	 * transactions from previous kernel. The ppc_pci_reset_phbs
	 * kernel parameter will क्रमce this reset too. Additionally,
	 * अगर the IODA reset above failed then use a bigger hammer.
	 * This can happen अगर we get a PHB fatal error in very early
	 * boot.
	 */
	अगर (is_kdump_kernel() || pci_reset_phbs || rc) अणु
		pr_info("  Issue PHB reset ...\n");
		pnv_eeh_phb_reset(hose, EEH_RESET_FUNDAMENTAL);
		pnv_eeh_phb_reset(hose, EEH_RESET_DEACTIVATE);
	पूर्ण

	/* Remove M64 resource अगर we can't configure it successfully */
	अगर (!phb->init_m64 || phb->init_m64(phb))
		hose->mem_resources[1].flags = 0;

	/* create pci_dn's क्रम DT nodes under this PHB */
	pci_devs_phb_init_dynamic(hose);
पूर्ण

व्योम __init pnv_pci_init_ioda2_phb(काष्ठा device_node *np)
अणु
	pnv_pci_init_ioda_phb(np, 0, PNV_PHB_IODA2);
पूर्ण

व्योम __init pnv_pci_init_npu2_खोलोcapi_phb(काष्ठा device_node *np)
अणु
	pnv_pci_init_ioda_phb(np, 0, PNV_PHB_NPU_OCAPI);
पूर्ण

अटल व्योम pnv_npu2_खोलोcapi_cfg_size_fixup(काष्ठा pci_dev *dev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);

	अगर (!machine_is(घातernv))
		वापस;

	अगर (phb->type == PNV_PHB_NPU_OCAPI)
		dev->cfg_size = PCI_CFG_SPACE_EXP_SIZE;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_ANY_ID, PCI_ANY_ID, pnv_npu2_खोलोcapi_cfg_size_fixup);

व्योम __init pnv_pci_init_ioda_hub(काष्ठा device_node *np)
अणु
	काष्ठा device_node *phbn;
	स्थिर __be64 *prop64;
	u64 hub_id;

	pr_info("Probing IODA IO-Hub %pOF\n", np);

	prop64 = of_get_property(np, "ibm,opal-hubid", शून्य);
	अगर (!prop64) अणु
		pr_err(" Missing \"ibm,opal-hubid\" property !\n");
		वापस;
	पूर्ण
	hub_id = be64_to_cpup(prop64);
	pr_devel(" HUB-ID : 0x%016llx\n", hub_id);

	/* Count child PHBs */
	क्रम_each_child_of_node(np, phbn) अणु
		/* Look क्रम IODA1 PHBs */
		अगर (of_device_is_compatible(phbn, "ibm,ioda-phb"))
			pnv_pci_init_ioda_phb(phbn, hub_id, PNV_PHB_IODA1);
	पूर्ण
पूर्ण
