<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2018 Intel Corporation.
 *
 * Authors: Gayatri Kammela <gayatri.kammela@पूर्णांकel.com>
 *	    Sohil Mehta <sohil.mehta@पूर्णांकel.com>
 *	    Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 *	    Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/dmar.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/irq_remapping.h>

#समावेश "pasid.h"

काष्ठा tbl_walk अणु
	u16 bus;
	u16 devfn;
	u32 pasid;
	काष्ठा root_entry *rt_entry;
	काष्ठा context_entry *ctx_entry;
	काष्ठा pasid_entry *pasid_tbl_entry;
पूर्ण;

काष्ठा iommu_regset अणु
	पूर्णांक offset;
	स्थिर अक्षर *regs;
पूर्ण;

#घोषणा IOMMU_REGSET_ENTRY(_reg_)					\
	अणु DMAR_##_reg_##_REG, __stringअगरy(_reg_) पूर्ण

अटल स्थिर काष्ठा iommu_regset iommu_regs_32[] = अणु
	IOMMU_REGSET_ENTRY(VER),
	IOMMU_REGSET_ENTRY(GCMD),
	IOMMU_REGSET_ENTRY(GSTS),
	IOMMU_REGSET_ENTRY(FSTS),
	IOMMU_REGSET_ENTRY(FECTL),
	IOMMU_REGSET_ENTRY(FEDATA),
	IOMMU_REGSET_ENTRY(FEADDR),
	IOMMU_REGSET_ENTRY(FEUADDR),
	IOMMU_REGSET_ENTRY(PMEN),
	IOMMU_REGSET_ENTRY(PLMBASE),
	IOMMU_REGSET_ENTRY(PLMLIMIT),
	IOMMU_REGSET_ENTRY(ICS),
	IOMMU_REGSET_ENTRY(PRS),
	IOMMU_REGSET_ENTRY(PECTL),
	IOMMU_REGSET_ENTRY(PEDATA),
	IOMMU_REGSET_ENTRY(PEADDR),
	IOMMU_REGSET_ENTRY(PEUADDR),
पूर्ण;

अटल स्थिर काष्ठा iommu_regset iommu_regs_64[] = अणु
	IOMMU_REGSET_ENTRY(CAP),
	IOMMU_REGSET_ENTRY(ECAP),
	IOMMU_REGSET_ENTRY(RTADDR),
	IOMMU_REGSET_ENTRY(CCMD),
	IOMMU_REGSET_ENTRY(AFLOG),
	IOMMU_REGSET_ENTRY(PHMBASE),
	IOMMU_REGSET_ENTRY(PHMLIMIT),
	IOMMU_REGSET_ENTRY(IQH),
	IOMMU_REGSET_ENTRY(IQT),
	IOMMU_REGSET_ENTRY(IQA),
	IOMMU_REGSET_ENTRY(IRTA),
	IOMMU_REGSET_ENTRY(PQH),
	IOMMU_REGSET_ENTRY(PQT),
	IOMMU_REGSET_ENTRY(PQA),
	IOMMU_REGSET_ENTRY(MTRRCAP),
	IOMMU_REGSET_ENTRY(MTRRDEF),
	IOMMU_REGSET_ENTRY(MTRR_FIX64K_00000),
	IOMMU_REGSET_ENTRY(MTRR_FIX16K_80000),
	IOMMU_REGSET_ENTRY(MTRR_FIX16K_A0000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_C0000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_C8000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_D0000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_D8000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_E0000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_E8000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_F0000),
	IOMMU_REGSET_ENTRY(MTRR_FIX4K_F8000),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE0),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK0),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE1),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK1),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE2),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK2),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE3),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK3),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE4),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK4),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE5),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK5),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE6),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK6),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE7),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK7),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE8),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK8),
	IOMMU_REGSET_ENTRY(MTRR_PHYSBASE9),
	IOMMU_REGSET_ENTRY(MTRR_PHYSMASK9),
	IOMMU_REGSET_ENTRY(VCCAP),
	IOMMU_REGSET_ENTRY(VCMD),
	IOMMU_REGSET_ENTRY(VCRSP),
पूर्ण;

अटल पूर्णांक iommu_regset_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flag;
	पूर्णांक i, ret = 0;
	u64 value;

	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (!drhd->reg_base_addr) अणु
			seq_माला_दो(m, "IOMMU: Invalid base address\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		seq_म_लिखो(m, "IOMMU: %s Register Base Address: %llx\n",
			   iommu->name, drhd->reg_base_addr);
		seq_माला_दो(m, "Name\t\t\tOffset\t\tContents\n");
		/*
		 * Publish the contents of the 64-bit hardware रेजिस्टरs
		 * by adding the offset to the poपूर्णांकer (भव address).
		 */
		raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
		क्रम (i = 0 ; i < ARRAY_SIZE(iommu_regs_32); i++) अणु
			value = dmar_पढ़ोl(iommu->reg + iommu_regs_32[i].offset);
			seq_म_लिखो(m, "%-16s\t0x%02x\t\t0x%016llx\n",
				   iommu_regs_32[i].regs, iommu_regs_32[i].offset,
				   value);
		पूर्ण
		क्रम (i = 0 ; i < ARRAY_SIZE(iommu_regs_64); i++) अणु
			value = dmar_पढ़ोq(iommu->reg + iommu_regs_64[i].offset);
			seq_म_लिखो(m, "%-16s\t0x%02x\t\t0x%016llx\n",
				   iommu_regs_64[i].regs, iommu_regs_64[i].offset,
				   value);
		पूर्ण
		raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
		seq_अ_दो(m, '\n');
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(iommu_regset);

अटल अंतरभूत व्योम prपूर्णांक_tbl_walk(काष्ठा seq_file *m)
अणु
	काष्ठा tbl_walk *tbl_wlk = m->निजी;

	seq_म_लिखो(m, "%02x:%02x.%x\t0x%016llx:0x%016llx\t0x%016llx:0x%016llx\t",
		   tbl_wlk->bus, PCI_SLOT(tbl_wlk->devfn),
		   PCI_FUNC(tbl_wlk->devfn), tbl_wlk->rt_entry->hi,
		   tbl_wlk->rt_entry->lo, tbl_wlk->ctx_entry->hi,
		   tbl_wlk->ctx_entry->lo);

	/*
	 * A legacy mode DMAR करोesn't support PASID, hence शेष it to -1
	 * indicating that it's invalid. Also, शेष all PASID related fields
	 * to 0.
	 */
	अगर (!tbl_wlk->pasid_tbl_entry)
		seq_म_लिखो(m, "%-6d\t0x%016llx:0x%016llx:0x%016llx\n", -1,
			   (u64)0, (u64)0, (u64)0);
	अन्यथा
		seq_म_लिखो(m, "%-6d\t0x%016llx:0x%016llx:0x%016llx\n",
			   tbl_wlk->pasid, tbl_wlk->pasid_tbl_entry->val[2],
			   tbl_wlk->pasid_tbl_entry->val[1],
			   tbl_wlk->pasid_tbl_entry->val[0]);
पूर्ण

अटल व्योम pasid_tbl_walk(काष्ठा seq_file *m, काष्ठा pasid_entry *tbl_entry,
			   u16 dir_idx)
अणु
	काष्ठा tbl_walk *tbl_wlk = m->निजी;
	u8 tbl_idx;

	क्रम (tbl_idx = 0; tbl_idx < PASID_TBL_ENTRIES; tbl_idx++) अणु
		अगर (pasid_pte_is_present(tbl_entry)) अणु
			tbl_wlk->pasid_tbl_entry = tbl_entry;
			tbl_wlk->pasid = (dir_idx << PASID_PDE_SHIFT) + tbl_idx;
			prपूर्णांक_tbl_walk(m);
		पूर्ण

		tbl_entry++;
	पूर्ण
पूर्ण

अटल व्योम pasid_dir_walk(काष्ठा seq_file *m, u64 pasid_dir_ptr,
			   u16 pasid_dir_size)
अणु
	काष्ठा pasid_dir_entry *dir_entry = phys_to_virt(pasid_dir_ptr);
	काष्ठा pasid_entry *pasid_tbl;
	u16 dir_idx;

	क्रम (dir_idx = 0; dir_idx < pasid_dir_size; dir_idx++) अणु
		pasid_tbl = get_pasid_table_from_pde(dir_entry);
		अगर (pasid_tbl)
			pasid_tbl_walk(m, pasid_tbl, dir_idx);

		dir_entry++;
	पूर्ण
पूर्ण

अटल व्योम ctx_tbl_walk(काष्ठा seq_file *m, काष्ठा पूर्णांकel_iommu *iommu, u16 bus)
अणु
	काष्ठा context_entry *context;
	u16 devfn, pasid_dir_size;
	u64 pasid_dir_ptr;

	क्रम (devfn = 0; devfn < 256; devfn++) अणु
		काष्ठा tbl_walk tbl_wlk = अणु0पूर्ण;

		/*
		 * Scalable mode root entry poपूर्णांकs to upper scalable mode
		 * context table and lower scalable mode context table. Each
		 * scalable mode context table has 128 context entries where as
		 * legacy mode context table has 256 context entries. So in
		 * scalable mode, the context entries क्रम क्रमmer 128 devices are
		 * in the lower scalable mode context table, जबतक the latter
		 * 128 devices are in the upper scalable mode context table.
		 * In scalable mode, when devfn > 127, iommu_context_addr()
		 * स्वतःmatically refers to upper scalable mode context table and
		 * hence the caller करोesn't have to worry about dअगरferences
		 * between scalable mode and non scalable mode.
		 */
		context = iommu_context_addr(iommu, bus, devfn, 0);
		अगर (!context)
			वापस;

		अगर (!context_present(context))
			जारी;

		tbl_wlk.bus = bus;
		tbl_wlk.devfn = devfn;
		tbl_wlk.rt_entry = &iommu->root_entry[bus];
		tbl_wlk.ctx_entry = context;
		m->निजी = &tbl_wlk;

		अगर (dmar_पढ़ोq(iommu->reg + DMAR_RTADDR_REG) & DMA_RTADDR_SMT) अणु
			pasid_dir_ptr = context->lo & VTD_PAGE_MASK;
			pasid_dir_size = get_pasid_dir_size(context);
			pasid_dir_walk(m, pasid_dir_ptr, pasid_dir_size);
			जारी;
		पूर्ण

		prपूर्णांक_tbl_walk(m);
	पूर्ण
पूर्ण

अटल व्योम root_tbl_walk(काष्ठा seq_file *m, काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अचिन्हित दीर्घ flags;
	u16 bus;

	spin_lock_irqsave(&iommu->lock, flags);
	seq_म_लिखो(m, "IOMMU %s: Root Table Address: 0x%llx\n", iommu->name,
		   (u64)virt_to_phys(iommu->root_entry));
	seq_माला_दो(m, "B.D.F\tRoot_entry\t\t\t\tContext_entry\t\t\t\tPASID\tPASID_table_entry\n");

	/*
	 * No need to check अगर the root entry is present or not because
	 * iommu_context_addr() perक्रमms the same check beक्रमe वापसing
	 * context entry.
	 */
	क्रम (bus = 0; bus < 256; bus++)
		ctx_tbl_walk(m, iommu, bus);

	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल पूर्णांक dmar_translation_काष्ठा_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	u32 sts;

	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		sts = dmar_पढ़ोl(iommu->reg + DMAR_GSTS_REG);
		अगर (!(sts & DMA_GSTS_TES)) अणु
			seq_म_लिखो(m, "DMA Remapping is not enabled on %s\n",
				   iommu->name);
			जारी;
		पूर्ण
		root_tbl_walk(m, iommu);
		seq_अ_दो(m, '\n');
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dmar_translation_काष्ठा);

अटल अंतरभूत अचिन्हित दीर्घ level_to_directory_size(पूर्णांक level)
अणु
	वापस BIT_ULL(VTD_PAGE_SHIFT + VTD_STRIDE_SHIFT * (level - 1));
पूर्ण

अटल अंतरभूत व्योम
dump_page_info(काष्ठा seq_file *m, अचिन्हित दीर्घ iova, u64 *path)
अणु
	seq_म_लिखो(m, "0x%013lx |\t0x%016llx\t0x%016llx\t0x%016llx\t0x%016llx\t0x%016llx\n",
		   iova >> VTD_PAGE_SHIFT, path[5], path[4],
		   path[3], path[2], path[1]);
पूर्ण

अटल व्योम pgtable_walk_level(काष्ठा seq_file *m, काष्ठा dma_pte *pde,
			       पूर्णांक level, अचिन्हित दीर्घ start,
			       u64 *path)
अणु
	पूर्णांक i;

	अगर (level > 5 || level < 1)
		वापस;

	क्रम (i = 0; i < BIT_ULL(VTD_STRIDE_SHIFT);
			i++, pde++, start += level_to_directory_size(level)) अणु
		अगर (!dma_pte_present(pde))
			जारी;

		path[level] = pde->val;
		अगर (dma_pte_superpage(pde) || level == 1)
			dump_page_info(m, start, path);
		अन्यथा
			pgtable_walk_level(m, phys_to_virt(dma_pte_addr(pde)),
					   level - 1, start, path);
		path[level] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक show_device_करोमुख्य_translation(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा dmar_करोमुख्य *करोमुख्य = find_करोमुख्य(dev);
	काष्ठा seq_file *m = data;
	u64 path[6] = अणु 0 पूर्ण;

	अगर (!करोमुख्य)
		वापस 0;

	seq_म_लिखो(m, "Device %s with pasid %d @0x%llx\n",
		   dev_name(dev), करोमुख्य->शेष_pasid,
		   (u64)virt_to_phys(करोमुख्य->pgd));
	seq_माला_दो(m, "IOVA_PFN\t\tPML5E\t\t\tPML4E\t\t\tPDPE\t\t\tPDE\t\t\tPTE\n");

	pgtable_walk_level(m, करोमुख्य->pgd, करोमुख्य->agaw + 2, 0, path);
	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल पूर्णांक करोमुख्य_translation_काष्ठा_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	ret = bus_क्रम_each_dev(&pci_bus_type, शून्य, m,
			       show_device_करोमुख्य_translation);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस ret;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(करोमुख्य_translation_काष्ठा);

अटल व्योम invalidation_queue_entry_show(काष्ठा seq_file *m,
					  काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक index, shअगरt = qi_shअगरt(iommu);
	काष्ठा qi_desc *desc;
	पूर्णांक offset;

	अगर (ecap_smts(iommu->ecap))
		seq_माला_दो(m, "Index\t\tqw0\t\t\tqw1\t\t\tqw2\t\t\tqw3\t\t\tstatus\n");
	अन्यथा
		seq_माला_दो(m, "Index\t\tqw0\t\t\tqw1\t\t\tstatus\n");

	क्रम (index = 0; index < QI_LENGTH; index++) अणु
		offset = index << shअगरt;
		desc = iommu->qi->desc + offset;
		अगर (ecap_smts(iommu->ecap))
			seq_म_लिखो(m, "%5d\t%016llx\t%016llx\t%016llx\t%016llx\t%016x\n",
				   index, desc->qw0, desc->qw1,
				   desc->qw2, desc->qw3,
				   iommu->qi->desc_status[index]);
		अन्यथा
			seq_म_लिखो(m, "%5d\t%016llx\t%016llx\t%016x\n",
				   index, desc->qw0, desc->qw1,
				   iommu->qi->desc_status[index]);
	पूर्ण
पूर्ण

अटल पूर्णांक invalidation_queue_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;
	काष्ठा q_inval *qi;
	पूर्णांक shअगरt;

	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		qi = iommu->qi;
		shअगरt = qi_shअगरt(iommu);

		अगर (!qi || !ecap_qis(iommu->ecap))
			जारी;

		seq_म_लिखो(m, "Invalidation queue on IOMMU: %s\n", iommu->name);

		raw_spin_lock_irqsave(&qi->q_lock, flags);
		seq_म_लिखो(m, " Base: 0x%llx\tHead: %lld\tTail: %lld\n",
			   (u64)virt_to_phys(qi->desc),
			   dmar_पढ़ोq(iommu->reg + DMAR_IQH_REG) >> shअगरt,
			   dmar_पढ़ोq(iommu->reg + DMAR_IQT_REG) >> shअगरt);
		invalidation_queue_entry_show(m, iommu);
		raw_spin_unlock_irqrestore(&qi->q_lock, flags);
		seq_अ_दो(m, '\n');
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(invalidation_queue);

#अगर_घोषित CONFIG_IRQ_REMAP
अटल व्योम ir_tbl_remap_entry_show(काष्ठा seq_file *m,
				    काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा irte *ri_entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	seq_माला_दो(m, " Entry SrcID   DstID    Vct IRTE_high\t\tIRTE_low\n");

	raw_spin_lock_irqsave(&irq_2_ir_lock, flags);
	क्रम (idx = 0; idx < INTR_REMAP_TABLE_ENTRIES; idx++) अणु
		ri_entry = &iommu->ir_table->base[idx];
		अगर (!ri_entry->present || ri_entry->p_pst)
			जारी;

		seq_म_लिखो(m, " %-5d %02x:%02x.%01x %08x %02x  %016llx\t%016llx\n",
			   idx, PCI_BUS_NUM(ri_entry->sid),
			   PCI_SLOT(ri_entry->sid), PCI_FUNC(ri_entry->sid),
			   ri_entry->dest_id, ri_entry->vector,
			   ri_entry->high, ri_entry->low);
	पूर्ण
	raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);
पूर्ण

अटल व्योम ir_tbl_posted_entry_show(काष्ठा seq_file *m,
				     काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा irte *pi_entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	seq_माला_दो(m, " Entry SrcID   PDA_high PDA_low  Vct IRTE_high\t\tIRTE_low\n");

	raw_spin_lock_irqsave(&irq_2_ir_lock, flags);
	क्रम (idx = 0; idx < INTR_REMAP_TABLE_ENTRIES; idx++) अणु
		pi_entry = &iommu->ir_table->base[idx];
		अगर (!pi_entry->present || !pi_entry->p_pst)
			जारी;

		seq_म_लिखो(m, " %-5d %02x:%02x.%01x %08x %08x %02x  %016llx\t%016llx\n",
			   idx, PCI_BUS_NUM(pi_entry->sid),
			   PCI_SLOT(pi_entry->sid), PCI_FUNC(pi_entry->sid),
			   pi_entry->pda_h, pi_entry->pda_l << 6,
			   pi_entry->vector, pi_entry->high,
			   pi_entry->low);
	पूर्ण
	raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);
पूर्ण

/*
 * For active IOMMUs go through the Interrupt remapping
 * table and prपूर्णांक valid entries in a table क्रमmat क्रम
 * Remapped and Posted Interrupts.
 */
अटल पूर्णांक ir_translation_काष्ठा_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	u64 irta;
	u32 sts;

	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (!ecap_ir_support(iommu->ecap))
			जारी;

		seq_म_लिखो(m, "Remapped Interrupt supported on IOMMU: %s\n",
			   iommu->name);

		sts = dmar_पढ़ोl(iommu->reg + DMAR_GSTS_REG);
		अगर (iommu->ir_table && (sts & DMA_GSTS_IRES)) अणु
			irta = virt_to_phys(iommu->ir_table->base);
			seq_म_लिखो(m, " IR table address:%llx\n", irta);
			ir_tbl_remap_entry_show(m, iommu);
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, "Interrupt Remapping is not enabled\n");
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण

	seq_माला_दो(m, "****\n\n");

	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (!cap_pi_support(iommu->cap))
			जारी;

		seq_म_लिखो(m, "Posted Interrupt supported on IOMMU: %s\n",
			   iommu->name);

		अगर (iommu->ir_table) अणु
			irta = virt_to_phys(iommu->ir_table->base);
			seq_म_लिखो(m, " IR table address:%llx\n", irta);
			ir_tbl_posted_entry_show(m, iommu);
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, "Interrupt Remapping is not enabled\n");
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ir_translation_काष्ठा);
#पूर्ण_अगर

व्योम __init पूर्णांकel_iommu_debugfs_init(व्योम)
अणु
	काष्ठा dentry *पूर्णांकel_iommu_debug = debugfs_create_dir("intel",
						iommu_debugfs_dir);

	debugfs_create_file("iommu_regset", 0444, पूर्णांकel_iommu_debug, शून्य,
			    &iommu_regset_fops);
	debugfs_create_file("dmar_translation_struct", 0444, पूर्णांकel_iommu_debug,
			    शून्य, &dmar_translation_काष्ठा_fops);
	debugfs_create_file("domain_translation_struct", 0444,
			    पूर्णांकel_iommu_debug, शून्य,
			    &करोमुख्य_translation_काष्ठा_fops);
	debugfs_create_file("invalidation_queue", 0444, पूर्णांकel_iommu_debug,
			    शून्य, &invalidation_queue_fops);
#अगर_घोषित CONFIG_IRQ_REMAP
	debugfs_create_file("ir_translation_struct", 0444, पूर्णांकel_iommu_debug,
			    शून्य, &ir_translation_काष्ठा_fops);
#पूर्ण_अगर
पूर्ण
