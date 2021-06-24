<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/sched/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <यंत्र/copro.h>
#समावेश <यंत्र/pnv-ocxl.h>
#समावेश <यंत्र/xive.h>
#समावेश <misc/ocxl.h>
#समावेश "ocxl_internal.h"
#समावेश "trace.h"


#घोषणा SPA_PASID_BITS		15
#घोषणा SPA_PASID_MAX		((1 << SPA_PASID_BITS) - 1)
#घोषणा SPA_PE_MASK		SPA_PASID_MAX
#घोषणा SPA_SPA_SIZE_LOG	22 /* Each SPA is 4 Mb */

#घोषणा SPA_CFG_SF		(1ull << (63-0))
#घोषणा SPA_CFG_TA		(1ull << (63-1))
#घोषणा SPA_CFG_HV		(1ull << (63-3))
#घोषणा SPA_CFG_UV		(1ull << (63-4))
#घोषणा SPA_CFG_XLAT_hpt	(0ull << (63-6)) /* Hashed page table (HPT) mode */
#घोषणा SPA_CFG_XLAT_roh	(2ull << (63-6)) /* Radix on HPT mode */
#घोषणा SPA_CFG_XLAT_ror	(3ull << (63-6)) /* Radix on Radix mode */
#घोषणा SPA_CFG_PR		(1ull << (63-49))
#घोषणा SPA_CFG_TC		(1ull << (63-54))
#घोषणा SPA_CFG_DR		(1ull << (63-59))

#घोषणा SPA_XSL_TF		(1ull << (63-3))  /* Translation fault */
#घोषणा SPA_XSL_S		(1ull << (63-38)) /* Store operation */

#घोषणा SPA_PE_VALID		0x80000000

काष्ठा ocxl_link;

काष्ठा pe_data अणु
	काष्ठा mm_काष्ठा *mm;
	/* callback to trigger when a translation fault occurs */
	व्योम (*xsl_err_cb)(व्योम *data, u64 addr, u64 dsisr);
	/* opaque poपूर्णांकer to be passed to the above callback */
	व्योम *xsl_err_data;
	काष्ठा rcu_head rcu;
	काष्ठा ocxl_link *link;
	काष्ठा mmu_notअगरier mmu_notअगरier;
पूर्ण;

काष्ठा spa अणु
	काष्ठा ocxl_process_element *spa_mem;
	पूर्णांक spa_order;
	काष्ठा mutex spa_lock;
	काष्ठा radix_tree_root pe_tree; /* Maps PE handles to pe_data */
	अक्षर *irq_name;
	पूर्णांक virq;
	व्योम __iomem *reg_dsisr;
	व्योम __iomem *reg_dar;
	व्योम __iomem *reg_tfc;
	व्योम __iomem *reg_pe_handle;
	/*
	 * The following field are used by the memory fault
	 * पूर्णांकerrupt handler. We can only have one पूर्णांकerrupt at a
	 * समय. The NPU won't उठाओ another पूर्णांकerrupt until the
	 * previous one has been ack'd by writing to the TFC रेजिस्टर
	 */
	काष्ठा xsl_fault अणु
		काष्ठा work_काष्ठा fault_work;
		u64 pe;
		u64 dsisr;
		u64 dar;
		काष्ठा pe_data pe_data;
	पूर्ण xsl_fault;
पूर्ण;

/*
 * A खोलोcapi link can be used be by several PCI functions. We have
 * one link per device slot.
 *
 * A linked list of खोलोcapi links should suffice, as there's a
 * limited number of खोलोcapi slots on a प्रणाली and lookup is only
 * करोne when the device is probed
 */
काष्ठा ocxl_link अणु
	काष्ठा list_head list;
	काष्ठा kref ref;
	पूर्णांक करोमुख्य;
	पूर्णांक bus;
	पूर्णांक dev;
	व्योम __iomem *arva;     /* ATSD रेजिस्टर भव address */
	spinlock_t atsd_lock;   /* to serialize shootकरोwns */
	atomic_t irq_available;
	काष्ठा spa *spa;
	व्योम *platक्रमm_data;
पूर्ण;
अटल काष्ठा list_head links_list = LIST_HEAD_INIT(links_list);
अटल DEFINE_MUTEX(links_list_lock);

क्रमागत xsl_response अणु
	CONTINUE,
	ADDRESS_ERROR,
	RESTART,
पूर्ण;


अटल व्योम पढ़ो_irq(काष्ठा spa *spa, u64 *dsisr, u64 *dar, u64 *pe)
अणु
	u64 reg;

	*dsisr = in_be64(spa->reg_dsisr);
	*dar = in_be64(spa->reg_dar);
	reg = in_be64(spa->reg_pe_handle);
	*pe = reg & SPA_PE_MASK;
पूर्ण

अटल व्योम ack_irq(काष्ठा spa *spa, क्रमागत xsl_response r)
अणु
	u64 reg = 0;

	/* जारी is not supported */
	अगर (r == RESTART)
		reg = PPC_BIT(31);
	अन्यथा अगर (r == ADDRESS_ERROR)
		reg = PPC_BIT(30);
	अन्यथा
		WARN(1, "Invalid irq response %d\n", r);

	अगर (reg) अणु
		trace_ocxl_fault_ack(spa->spa_mem, spa->xsl_fault.pe,
				spa->xsl_fault.dsisr, spa->xsl_fault.dar, reg);
		out_be64(spa->reg_tfc, reg);
	पूर्ण
पूर्ण

अटल व्योम xsl_fault_handler_bh(काष्ठा work_काष्ठा *fault_work)
अणु
	vm_fault_t flt = 0;
	अचिन्हित दीर्घ access, flags, inv_flags = 0;
	क्रमागत xsl_response r;
	काष्ठा xsl_fault *fault = container_of(fault_work, काष्ठा xsl_fault,
					fault_work);
	काष्ठा spa *spa = container_of(fault, काष्ठा spa, xsl_fault);

	पूर्णांक rc;

	/*
	 * We must release a reference on mm_users whenever निकासing this
	 * function (taken in the memory fault पूर्णांकerrupt handler)
	 */
	rc = copro_handle_mm_fault(fault->pe_data.mm, fault->dar, fault->dsisr,
				&flt);
	अगर (rc) अणु
		pr_debug("copro_handle_mm_fault failed: %d\n", rc);
		अगर (fault->pe_data.xsl_err_cb) अणु
			fault->pe_data.xsl_err_cb(
				fault->pe_data.xsl_err_data,
				fault->dar, fault->dsisr);
		पूर्ण
		r = ADDRESS_ERROR;
		जाओ ack;
	पूर्ण

	अगर (!radix_enabled()) अणु
		/*
		 * update_mmu_cache() will not have loaded the hash
		 * since current->trap is not a 0x400 or 0x300, so
		 * just call hash_page_mm() here.
		 */
		access = _PAGE_PRESENT | _PAGE_READ;
		अगर (fault->dsisr & SPA_XSL_S)
			access |= _PAGE_WRITE;

		अगर (get_region_id(fault->dar) != USER_REGION_ID)
			access |= _PAGE_PRIVILEGED;

		local_irq_save(flags);
		hash_page_mm(fault->pe_data.mm, fault->dar, access, 0x300,
			inv_flags);
		local_irq_restore(flags);
	पूर्ण
	r = RESTART;
ack:
	mmput(fault->pe_data.mm);
	ack_irq(spa, r);
पूर्ण

अटल irqवापस_t xsl_fault_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) data;
	काष्ठा spa *spa = link->spa;
	u64 dsisr, dar, pe_handle;
	काष्ठा pe_data *pe_data;
	काष्ठा ocxl_process_element *pe;
	पूर्णांक pid;
	bool schedule = false;

	पढ़ो_irq(spa, &dsisr, &dar, &pe_handle);
	trace_ocxl_fault(spa->spa_mem, pe_handle, dsisr, dar, -1);

	WARN_ON(pe_handle > SPA_PE_MASK);
	pe = spa->spa_mem + pe_handle;
	pid = be32_to_cpu(pe->pid);
	/* We could be पढ़ोing all null values here अगर the PE is being
	 * हटाओd जबतक an पूर्णांकerrupt kicks in. It's not supposed to
	 * happen अगर the driver notअगरied the AFU to terminate the
	 * PASID, and the AFU रुकोed क्रम pending operations beक्रमe
	 * acknowledging. But even अगर it happens, we won't find a
	 * memory context below and fail silently, so it should be ok.
	 */
	अगर (!(dsisr & SPA_XSL_TF)) अणु
		WARN(1, "Invalid xsl interrupt fault register %#llx\n", dsisr);
		ack_irq(spa, ADDRESS_ERROR);
		वापस IRQ_HANDLED;
	पूर्ण

	rcu_पढ़ो_lock();
	pe_data = radix_tree_lookup(&spa->pe_tree, pe_handle);
	अगर (!pe_data) अणु
		/*
		 * Could only happen अगर the driver didn't notअगरy the
		 * AFU about PASID termination beक्रमe removing the PE,
		 * or the AFU didn't रुको क्रम all memory access to
		 * have completed.
		 *
		 * Either way, we fail early, but we shouldn't log an
		 * error message, as it is a valid (अगर unexpected)
		 * scenario
		 */
		rcu_पढ़ो_unlock();
		pr_debug("Unknown mm context for xsl interrupt\n");
		ack_irq(spa, ADDRESS_ERROR);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!pe_data->mm) अणु
		/*
		 * translation fault from a kernel context - an OpenCAPI
		 * device tried to access a bad kernel address
		 */
		rcu_पढ़ो_unlock();
		pr_warn("Unresolved OpenCAPI xsl fault in kernel context\n");
		ack_irq(spa, ADDRESS_ERROR);
		वापस IRQ_HANDLED;
	पूर्ण
	WARN_ON(pe_data->mm->context.id != pid);

	अगर (mmget_not_zero(pe_data->mm)) अणु
			spa->xsl_fault.pe = pe_handle;
			spa->xsl_fault.dar = dar;
			spa->xsl_fault.dsisr = dsisr;
			spa->xsl_fault.pe_data = *pe_data;
			schedule = true;
			/* mm_users count released by bottom half */
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (schedule)
		schedule_work(&spa->xsl_fault.fault_work);
	अन्यथा
		ack_irq(spa, ADDRESS_ERROR);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम unmap_irq_रेजिस्टरs(काष्ठा spa *spa)
अणु
	pnv_ocxl_unmap_xsl_regs(spa->reg_dsisr, spa->reg_dar, spa->reg_tfc,
				spa->reg_pe_handle);
पूर्ण

अटल पूर्णांक map_irq_रेजिस्टरs(काष्ठा pci_dev *dev, काष्ठा spa *spa)
अणु
	वापस pnv_ocxl_map_xsl_regs(dev, &spa->reg_dsisr, &spa->reg_dar,
				&spa->reg_tfc, &spa->reg_pe_handle);
पूर्ण

अटल पूर्णांक setup_xsl_irq(काष्ठा pci_dev *dev, काष्ठा ocxl_link *link)
अणु
	काष्ठा spa *spa = link->spa;
	पूर्णांक rc;
	पूर्णांक hwirq;

	rc = pnv_ocxl_get_xsl_irq(dev, &hwirq);
	अगर (rc)
		वापस rc;

	rc = map_irq_रेजिस्टरs(dev, spa);
	अगर (rc)
		वापस rc;

	spa->irq_name = kaप्र_लिखो(GFP_KERNEL, "ocxl-xsl-%x-%x-%x",
				link->करोमुख्य, link->bus, link->dev);
	अगर (!spa->irq_name) अणु
		dev_err(&dev->dev, "Can't allocate name for xsl interrupt\n");
		rc = -ENOMEM;
		जाओ err_xsl;
	पूर्ण
	/*
	 * At some poपूर्णांक, we'll need to look पूर्णांकo allowing a higher
	 * number of पूर्णांकerrupts. Could we have an IRQ करोमुख्य per link?
	 */
	spa->virq = irq_create_mapping(शून्य, hwirq);
	अगर (!spa->virq) अणु
		dev_err(&dev->dev,
			"irq_create_mapping failed for translation interrupt\n");
		rc = -EINVAL;
		जाओ err_name;
	पूर्ण

	dev_dbg(&dev->dev, "hwirq %d mapped to virq %d\n", hwirq, spa->virq);

	rc = request_irq(spa->virq, xsl_fault_handler, 0, spa->irq_name,
			link);
	अगर (rc) अणु
		dev_err(&dev->dev,
			"request_irq failed for translation interrupt: %d\n",
			rc);
		rc = -EINVAL;
		जाओ err_mapping;
	पूर्ण
	वापस 0;

err_mapping:
	irq_dispose_mapping(spa->virq);
err_name:
	kमुक्त(spa->irq_name);
err_xsl:
	unmap_irq_रेजिस्टरs(spa);
	वापस rc;
पूर्ण

अटल व्योम release_xsl_irq(काष्ठा ocxl_link *link)
अणु
	काष्ठा spa *spa = link->spa;

	अगर (spa->virq) अणु
		मुक्त_irq(spa->virq, link);
		irq_dispose_mapping(spa->virq);
	पूर्ण
	kमुक्त(spa->irq_name);
	unmap_irq_रेजिस्टरs(spa);
पूर्ण

अटल पूर्णांक alloc_spa(काष्ठा pci_dev *dev, काष्ठा ocxl_link *link)
अणु
	काष्ठा spa *spa;

	spa = kzalloc(माप(काष्ठा spa), GFP_KERNEL);
	अगर (!spa)
		वापस -ENOMEM;

	mutex_init(&spa->spa_lock);
	INIT_RADIX_TREE(&spa->pe_tree, GFP_KERNEL);
	INIT_WORK(&spa->xsl_fault.fault_work, xsl_fault_handler_bh);

	spa->spa_order = SPA_SPA_SIZE_LOG - PAGE_SHIFT;
	spa->spa_mem = (काष्ठा ocxl_process_element *)
		__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, spa->spa_order);
	अगर (!spa->spa_mem) अणु
		dev_err(&dev->dev, "Can't allocate Shared Process Area\n");
		kमुक्त(spa);
		वापस -ENOMEM;
	पूर्ण
	pr_debug("Allocated SPA for %x:%x:%x at %p\n", link->करोमुख्य, link->bus,
		link->dev, spa->spa_mem);

	link->spa = spa;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_spa(काष्ठा ocxl_link *link)
अणु
	काष्ठा spa *spa = link->spa;

	pr_debug("Freeing SPA for %x:%x:%x\n", link->करोमुख्य, link->bus,
		link->dev);

	अगर (spa && spa->spa_mem) अणु
		मुक्त_pages((अचिन्हित दीर्घ) spa->spa_mem, spa->spa_order);
		kमुक्त(spa);
		link->spa = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_link(काष्ठा pci_dev *dev, पूर्णांक PE_mask, काष्ठा ocxl_link **out_link)
अणु
	काष्ठा ocxl_link *link;
	पूर्णांक rc;

	link = kzalloc(माप(काष्ठा ocxl_link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	kref_init(&link->ref);
	link->करोमुख्य = pci_करोमुख्य_nr(dev->bus);
	link->bus = dev->bus->number;
	link->dev = PCI_SLOT(dev->devfn);
	atomic_set(&link->irq_available, MAX_IRQ_PER_LINK);
	spin_lock_init(&link->atsd_lock);

	rc = alloc_spa(dev, link);
	अगर (rc)
		जाओ err_मुक्त;

	rc = setup_xsl_irq(dev, link);
	अगर (rc)
		जाओ err_spa;

	/* platक्रमm specअगरic hook */
	rc = pnv_ocxl_spa_setup(dev, link->spa->spa_mem, PE_mask,
				&link->platक्रमm_data);
	अगर (rc)
		जाओ err_xsl_irq;

	/* अगर link->arva is not defeined, MMIO रेजिस्टरs are not used to
	 * generate TLB invalidate. PowerBus snooping is enabled.
	 * Otherwise, PowerBus snooping is disabled. TLB Invalidates are
	 * initiated using MMIO रेजिस्टरs.
	 */
	pnv_ocxl_map_lpar(dev, mfspr(SPRN_LPID), 0, &link->arva);

	*out_link = link;
	वापस 0;

err_xsl_irq:
	release_xsl_irq(link);
err_spa:
	मुक्त_spa(link);
err_मुक्त:
	kमुक्त(link);
	वापस rc;
पूर्ण

अटल व्योम मुक्त_link(काष्ठा ocxl_link *link)
अणु
	release_xsl_irq(link);
	मुक्त_spa(link);
	kमुक्त(link);
पूर्ण

पूर्णांक ocxl_link_setup(काष्ठा pci_dev *dev, पूर्णांक PE_mask, व्योम **link_handle)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocxl_link *link;

	mutex_lock(&links_list_lock);
	list_क्रम_each_entry(link, &links_list, list) अणु
		/* The functions of a device all share the same link */
		अगर (link->करोमुख्य == pci_करोमुख्य_nr(dev->bus) &&
			link->bus == dev->bus->number &&
			link->dev == PCI_SLOT(dev->devfn)) अणु
			kref_get(&link->ref);
			*link_handle = link;
			जाओ unlock;
		पूर्ण
	पूर्ण
	rc = alloc_link(dev, PE_mask, &link);
	अगर (rc)
		जाओ unlock;

	list_add(&link->list, &links_list);
	*link_handle = link;
unlock:
	mutex_unlock(&links_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_setup);

अटल व्योम release_xsl(काष्ठा kref *ref)
अणु
	काष्ठा ocxl_link *link = container_of(ref, काष्ठा ocxl_link, ref);

	अगर (link->arva) अणु
		pnv_ocxl_unmap_lpar(link->arva);
		link->arva = शून्य;
	पूर्ण

	list_del(&link->list);
	/* call platक्रमm code beक्रमe releasing data */
	pnv_ocxl_spa_release(link->platक्रमm_data);
	मुक्त_link(link);
पूर्ण

व्योम ocxl_link_release(काष्ठा pci_dev *dev, व्योम *link_handle)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;

	mutex_lock(&links_list_lock);
	kref_put(&link->ref, release_xsl);
	mutex_unlock(&links_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_release);

अटल व्योम invalidate_range(काष्ठा mmu_notअगरier *mn,
			     काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा pe_data *pe_data = container_of(mn, काष्ठा pe_data, mmu_notअगरier);
	काष्ठा ocxl_link *link = pe_data->link;
	अचिन्हित दीर्घ addr, pid, page_size = PAGE_SIZE;

	pid = mm->context.id;
	trace_ocxl_mmu_notअगरier_range(start, end, pid);

	spin_lock(&link->atsd_lock);
	क्रम (addr = start; addr < end; addr += page_size)
		pnv_ocxl_tlb_invalidate(link->arva, pid, addr, page_size);
	spin_unlock(&link->atsd_lock);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops ocxl_mmu_notअगरier_ops = अणु
	.invalidate_range = invalidate_range,
पूर्ण;

अटल u64 calculate_cfg_state(bool kernel)
अणु
	u64 state;

	state = SPA_CFG_DR;
	अगर (mfspr(SPRN_LPCR) & LPCR_TC)
		state |= SPA_CFG_TC;
	अगर (radix_enabled())
		state |= SPA_CFG_XLAT_ror;
	अन्यथा
		state |= SPA_CFG_XLAT_hpt;
	state |= SPA_CFG_HV;
	अगर (kernel) अणु
		अगर (mfmsr() & MSR_SF)
			state |= SPA_CFG_SF;
	पूर्ण अन्यथा अणु
		state |= SPA_CFG_PR;
		अगर (!test_tsk_thपढ़ो_flag(current, TIF_32BIT))
			state |= SPA_CFG_SF;
	पूर्ण
	वापस state;
पूर्ण

पूर्णांक ocxl_link_add_pe(व्योम *link_handle, पूर्णांक pasid, u32 pidr, u32 tidr,
		u64 amr, u16 bdf, काष्ठा mm_काष्ठा *mm,
		व्योम (*xsl_err_cb)(व्योम *data, u64 addr, u64 dsisr),
		व्योम *xsl_err_data)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;
	काष्ठा spa *spa = link->spa;
	काष्ठा ocxl_process_element *pe;
	पूर्णांक pe_handle, rc = 0;
	काष्ठा pe_data *pe_data;

	BUILD_BUG_ON(माप(काष्ठा ocxl_process_element) != 128);
	अगर (pasid > SPA_PASID_MAX)
		वापस -EINVAL;

	mutex_lock(&spa->spa_lock);
	pe_handle = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handle;

	अगर (pe->software_state) अणु
		rc = -EBUSY;
		जाओ unlock;
	पूर्ण

	pe_data = kदो_स्मृति(माप(*pe_data), GFP_KERNEL);
	अगर (!pe_data) अणु
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	pe_data->mm = mm;
	pe_data->xsl_err_cb = xsl_err_cb;
	pe_data->xsl_err_data = xsl_err_data;
	pe_data->link = link;
	pe_data->mmu_notअगरier.ops = &ocxl_mmu_notअगरier_ops;

	स_रखो(pe, 0, माप(काष्ठा ocxl_process_element));
	pe->config_state = cpu_to_be64(calculate_cfg_state(pidr == 0));
	pe->pasid = cpu_to_be32(pasid << (31 - 19));
	pe->bdf = cpu_to_be16(bdf);
	pe->lpid = cpu_to_be32(mfspr(SPRN_LPID));
	pe->pid = cpu_to_be32(pidr);
	pe->tid = cpu_to_be32(tidr);
	pe->amr = cpu_to_be64(amr);
	pe->software_state = cpu_to_be32(SPA_PE_VALID);

	/*
	 * For user contexts, रेजिस्टर a copro so that TLBIs are seen
	 * by the nest MMU. If we have a kernel context, TLBIs are
	 * alपढ़ोy global.
	 */
	अगर (mm) अणु
		mm_context_add_copro(mm);
		अगर (link->arva) अणु
			/* Use MMIO रेजिस्टरs क्रम the TLB Invalidate
			 * operations.
			 */
			trace_ocxl_init_mmu_notअगरier(pasid, mm->context.id);
			mmu_notअगरier_रेजिस्टर(&pe_data->mmu_notअगरier, mm);
		पूर्ण
	पूर्ण

	/*
	 * Barrier is to make sure PE is visible in the SPA beक्रमe it
	 * is used by the device. It also helps with the global TLBI
	 * invalidation
	 */
	mb();
	radix_tree_insert(&spa->pe_tree, pe_handle, pe_data);

	/*
	 * The mm must stay valid क्रम as दीर्घ as the device uses it. We
	 * lower the count when the context is हटाओd from the SPA.
	 *
	 * We grab mm_count (and not mm_users), as we करोn't want to
	 * end up in a circular dependency अगर a process mmaps its
	 * mmio, thereक्रमe incrementing the file ref count when
	 * calling mmap(), and क्रममाला_लो to unmap beक्रमe निकासing. In
	 * that scenario, when the kernel handles the death of the
	 * process, the file is not cleaned because unmap was not
	 * called, and the mm wouldn't be मुक्तd because we would still
	 * have a reference on mm_users. Incrementing mm_count solves
	 * the problem.
	 */
	अगर (mm)
		mmgrab(mm);
	trace_ocxl_context_add(current->pid, spa->spa_mem, pasid, pidr, tidr);
unlock:
	mutex_unlock(&spa->spa_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_add_pe);

पूर्णांक ocxl_link_update_pe(व्योम *link_handle, पूर्णांक pasid, __u16 tid)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;
	काष्ठा spa *spa = link->spa;
	काष्ठा ocxl_process_element *pe;
	पूर्णांक pe_handle, rc;

	अगर (pasid > SPA_PASID_MAX)
		वापस -EINVAL;

	pe_handle = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handle;

	mutex_lock(&spa->spa_lock);

	pe->tid = cpu_to_be32(tid);

	/*
	 * The barrier makes sure the PE is updated
	 * beक्रमe we clear the NPU context cache below, so that the
	 * old PE cannot be reloaded erroneously.
	 */
	mb();

	/*
	 * hook to platक्रमm code
	 * On घातerpc, the entry needs to be cleared from the context
	 * cache of the NPU.
	 */
	rc = pnv_ocxl_spa_हटाओ_pe_from_cache(link->platक्रमm_data, pe_handle);
	WARN_ON(rc);

	mutex_unlock(&spa->spa_lock);
	वापस rc;
पूर्ण

पूर्णांक ocxl_link_हटाओ_pe(व्योम *link_handle, पूर्णांक pasid)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;
	काष्ठा spa *spa = link->spa;
	काष्ठा ocxl_process_element *pe;
	काष्ठा pe_data *pe_data;
	पूर्णांक pe_handle, rc;

	अगर (pasid > SPA_PASID_MAX)
		वापस -EINVAL;

	/*
	 * About synchronization with our memory fault handler:
	 *
	 * Beक्रमe removing the PE, the driver is supposed to have
	 * notअगरied the AFU, which should have cleaned up and make
	 * sure the PASID is no दीर्घer in use, including pending
	 * पूर्णांकerrupts. However, there's no way to be sure...
	 *
	 * We clear the PE and हटाओ the context from our radix
	 * tree. From that poपूर्णांक on, any new पूर्णांकerrupt क्रम that
	 * context will fail silently, which is ok. As mentioned
	 * above, that's not expected, but it could happen अगर the
	 * driver or AFU didn't करो the right thing.
	 *
	 * There could still be a bottom half running, but we करोn't
	 * need to रुको/flush, as it is managing a reference count on
	 * the mm it पढ़ोs from the radix tree.
	 */
	pe_handle = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handle;

	mutex_lock(&spa->spa_lock);

	अगर (!(be32_to_cpu(pe->software_state) & SPA_PE_VALID)) अणु
		rc = -EINVAL;
		जाओ unlock;
	पूर्ण

	trace_ocxl_context_हटाओ(current->pid, spa->spa_mem, pasid,
				be32_to_cpu(pe->pid), be32_to_cpu(pe->tid));

	स_रखो(pe, 0, माप(काष्ठा ocxl_process_element));
	/*
	 * The barrier makes sure the PE is हटाओd from the SPA
	 * beक्रमe we clear the NPU context cache below, so that the
	 * old PE cannot be reloaded erroneously.
	 */
	mb();

	/*
	 * hook to platक्रमm code
	 * On घातerpc, the entry needs to be cleared from the context
	 * cache of the NPU.
	 */
	rc = pnv_ocxl_spa_हटाओ_pe_from_cache(link->platक्रमm_data, pe_handle);
	WARN_ON(rc);

	pe_data = radix_tree_delete(&spa->pe_tree, pe_handle);
	अगर (!pe_data) अणु
		WARN(1, "Couldn't find pe data when removing PE\n");
	पूर्ण अन्यथा अणु
		अगर (pe_data->mm) अणु
			अगर (link->arva) अणु
				trace_ocxl_release_mmu_notअगरier(pasid,
								pe_data->mm->context.id);
				mmu_notअगरier_unरेजिस्टर(&pe_data->mmu_notअगरier,
							pe_data->mm);
				spin_lock(&link->atsd_lock);
				pnv_ocxl_tlb_invalidate(link->arva,
							pe_data->mm->context.id,
							0ull,
							PAGE_SIZE);
				spin_unlock(&link->atsd_lock);
			पूर्ण
			mm_context_हटाओ_copro(pe_data->mm);
			mmdrop(pe_data->mm);
		पूर्ण
		kमुक्त_rcu(pe_data, rcu);
	पूर्ण
unlock:
	mutex_unlock(&spa->spa_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_हटाओ_pe);

पूर्णांक ocxl_link_irq_alloc(व्योम *link_handle, पूर्णांक *hw_irq)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;
	पूर्णांक irq;

	अगर (atomic_dec_अगर_positive(&link->irq_available) < 0)
		वापस -ENOSPC;

	irq = xive_native_alloc_irq();
	अगर (!irq) अणु
		atomic_inc(&link->irq_available);
		वापस -ENXIO;
	पूर्ण

	*hw_irq = irq;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_irq_alloc);

व्योम ocxl_link_मुक्त_irq(व्योम *link_handle, पूर्णांक hw_irq)
अणु
	काष्ठा ocxl_link *link = (काष्ठा ocxl_link *) link_handle;

	xive_native_मुक्त_irq(hw_irq);
	atomic_inc(&link->irq_available);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_link_मुक्त_irq);
