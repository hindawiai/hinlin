<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Low-level SPU handling
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/linux_logo.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/kexec.h>

स्थिर काष्ठा spu_management_ops *spu_management_ops;
EXPORT_SYMBOL_GPL(spu_management_ops);

स्थिर काष्ठा spu_priv1_ops *spu_priv1_ops;
EXPORT_SYMBOL_GPL(spu_priv1_ops);

काष्ठा cbe_spu_info cbe_spu_info[MAX_NUMNODES];
EXPORT_SYMBOL_GPL(cbe_spu_info);

/*
 * The spufs fault-handling code needs to call क्रमce_sig_fault to उठाओ संकेतs
 * on DMA errors. Export it here to aव्योम general kernel-wide access to this
 * function
 */
EXPORT_SYMBOL_GPL(क्रमce_sig_fault);

/*
 * Protects cbe_spu_info and spu->number.
 */
अटल DEFINE_SPINLOCK(spu_lock);

/*
 * List of all spus in the प्रणाली.
 *
 * This list is iterated by callers from irq context and callers that
 * want to sleep.  Thus modअगरications need to be करोne with both
 * spu_full_list_lock and spu_full_list_mutex held, जबतक iterating
 * through it requires either of these locks.
 *
 * In addition spu_full_list_lock protects all assignments to
 * spu->mm.
 */
अटल LIST_HEAD(spu_full_list);
अटल DEFINE_SPINLOCK(spu_full_list_lock);
अटल DEFINE_MUTEX(spu_full_list_mutex);

व्योम spu_invalidate_slbs(काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spu->रेजिस्टर_lock, flags);
	अगर (spu_mfc_sr1_get(spu) & MFC_STATE1_RELOCATE_MASK)
		out_be64(&priv2->slb_invalidate_all_W, 0UL);
	spin_unlock_irqrestore(&spu->रेजिस्टर_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(spu_invalidate_slbs);

/* This is called by the MM core when a segment size is changed, to
 * request a flush of all the SPEs using a given mm
 */
व्योम spu_flush_all_slbs(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा spu *spu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spu_full_list_lock, flags);
	list_क्रम_each_entry(spu, &spu_full_list, full_list) अणु
		अगर (spu->mm == mm)
			spu_invalidate_slbs(spu);
	पूर्ण
	spin_unlock_irqrestore(&spu_full_list_lock, flags);
पूर्ण

/* The hack below stinks... try to करो something better one of
 * these days... Does it even work properly with NR_CPUS == 1 ?
 */
अटल अंतरभूत व्योम mm_needs_global_tlbie(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक nr = (NR_CPUS > 1) ? NR_CPUS : NR_CPUS + 1;

	/* Global TLBIE broadcast required with SPEs. */
	biपंचांगap_fill(cpumask_bits(mm_cpumask(mm)), nr);
पूर्ण

व्योम spu_associate_mm(काष्ठा spu *spu, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spu_full_list_lock, flags);
	spu->mm = mm;
	spin_unlock_irqrestore(&spu_full_list_lock, flags);
	अगर (mm)
		mm_needs_global_tlbie(mm);
पूर्ण
EXPORT_SYMBOL_GPL(spu_associate_mm);

पूर्णांक spu_64k_pages_available(व्योम)
अणु
	वापस mmu_psize_defs[MMU_PAGE_64K].shअगरt != 0;
पूर्ण
EXPORT_SYMBOL_GPL(spu_64k_pages_available);

अटल व्योम spu_restart_dma(काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	अगर (!test_bit(SPU_CONTEXT_SWITCH_PENDING, &spu->flags))
		out_be64(&priv2->mfc_control_RW, MFC_CNTL_RESTART_DMA_COMMAND);
	अन्यथा अणु
		set_bit(SPU_CONTEXT_FAULT_PENDING, &spu->flags);
		mb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम spu_load_slb(काष्ठा spu *spu, पूर्णांक slbe, काष्ठा copro_slb *slb)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	pr_debug("%s: adding SLB[%d] 0x%016llx 0x%016llx\n",
			__func__, slbe, slb->vsid, slb->esid);

	out_be64(&priv2->slb_index_W, slbe);
	/* set invalid beक्रमe writing vsid */
	out_be64(&priv2->slb_esid_RW, 0);
	/* now it's safe to ग_लिखो the vsid */
	out_be64(&priv2->slb_vsid_RW, slb->vsid);
	/* setting the new esid makes the entry valid again */
	out_be64(&priv2->slb_esid_RW, slb->esid);
पूर्ण

अटल पूर्णांक __spu_trap_data_seg(काष्ठा spu *spu, अचिन्हित दीर्घ ea)
अणु
	काष्ठा copro_slb slb;
	पूर्णांक ret;

	ret = copro_calculate_slb(spu->mm, ea, &slb);
	अगर (ret)
		वापस ret;

	spu_load_slb(spu, spu->slb_replace, &slb);

	spu->slb_replace++;
	अगर (spu->slb_replace >= 8)
		spu->slb_replace = 0;

	spu_restart_dma(spu);
	spu->stats.slb_flt++;
	वापस 0;
पूर्ण

बाह्य पूर्णांक hash_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
		     अचिन्हित दीर्घ trap, अचिन्हित दीर्घ dsisr); //XXX
अटल पूर्णांक __spu_trap_data_map(काष्ठा spu *spu, अचिन्हित दीर्घ ea, u64 dsisr)
अणु
	पूर्णांक ret;

	pr_debug("%s, %llx, %lx\n", __func__, dsisr, ea);

	/*
	 * Handle kernel space hash faults immediately. User hash
	 * faults need to be deferred to process context.
	 */
	अगर ((dsisr & MFC_DSISR_PTE_NOT_FOUND) &&
	    (get_region_id(ea) != USER_REGION_ID)) अणु

		spin_unlock(&spu->रेजिस्टर_lock);
		ret = hash_page(ea,
				_PAGE_PRESENT | _PAGE_READ | _PAGE_PRIVILEGED,
				0x300, dsisr);
		spin_lock(&spu->रेजिस्टर_lock);

		अगर (!ret) अणु
			spu_restart_dma(spu);
			वापस 0;
		पूर्ण
	पूर्ण

	spu->class_1_dar = ea;
	spu->class_1_dsisr = dsisr;

	spu->stop_callback(spu, 1);

	spu->class_1_dar = 0;
	spu->class_1_dsisr = 0;

	वापस 0;
पूर्ण

अटल व्योम __spu_kernel_slb(व्योम *addr, काष्ठा copro_slb *slb)
अणु
	अचिन्हित दीर्घ ea = (अचिन्हित दीर्घ)addr;
	u64 llp;

	अगर (get_region_id(ea) == LINEAR_MAP_REGION_ID)
		llp = mmu_psize_defs[mmu_linear_psize].sllp;
	अन्यथा
		llp = mmu_psize_defs[mmu_भव_psize].sllp;

	slb->vsid = (get_kernel_vsid(ea, MMU_SEGSIZE_256M) << SLB_VSID_SHIFT) |
		SLB_VSID_KERNEL | llp;
	slb->esid = (ea & ESID_MASK) | SLB_ESID_V;
पूर्ण

/**
 * Given an array of @nr_slbs SLB entries, @slbs, वापस non-zero अगर the
 * address @new_addr is present.
 */
अटल अंतरभूत पूर्णांक __slb_present(काष्ठा copro_slb *slbs, पूर्णांक nr_slbs,
		व्योम *new_addr)
अणु
	अचिन्हित दीर्घ ea = (अचिन्हित दीर्घ)new_addr;
	पूर्णांक i;

	क्रम (i = 0; i < nr_slbs; i++)
		अगर (!((slbs[i].esid ^ ea) & ESID_MASK))
			वापस 1;

	वापस 0;
पूर्ण

/**
 * Setup the SPU kernel SLBs, in preparation क्रम a context save/restore. We
 * need to map both the context save area, and the save/restore code.
 *
 * Because the lscsa and code may cross segment boundaries, we check to see
 * अगर mappings are required क्रम the start and end of each range. We currently
 * assume that the mappings are smaller that one segment - अगर not, something
 * is seriously wrong.
 */
व्योम spu_setup_kernel_slbs(काष्ठा spu *spu, काष्ठा spu_lscsa *lscsa,
		व्योम *code, पूर्णांक code_size)
अणु
	काष्ठा copro_slb slbs[4];
	पूर्णांक i, nr_slbs = 0;
	/* start and end addresses of both mappings */
	व्योम *addrs[] = अणु
		lscsa, (व्योम *)lscsa + माप(*lscsa) - 1,
		code, code + code_size - 1
	पूर्ण;

	/* check the set of addresses, and create a new entry in the slbs array
	 * अगर there isn't alपढ़ोy a SLB क्रम that address */
	क्रम (i = 0; i < ARRAY_SIZE(addrs); i++) अणु
		अगर (__slb_present(slbs, nr_slbs, addrs[i]))
			जारी;

		__spu_kernel_slb(addrs[i], &slbs[nr_slbs]);
		nr_slbs++;
	पूर्ण

	spin_lock_irq(&spu->रेजिस्टर_lock);
	/* Add the set of SLBs */
	क्रम (i = 0; i < nr_slbs; i++)
		spu_load_slb(spu, i, &slbs[i]);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण
EXPORT_SYMBOL_GPL(spu_setup_kernel_slbs);

अटल irqवापस_t
spu_irq_class_0(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spu *spu;
	अचिन्हित दीर्घ stat, mask;

	spu = data;

	spin_lock(&spu->रेजिस्टर_lock);
	mask = spu_पूर्णांक_mask_get(spu, 0);
	stat = spu_पूर्णांक_stat_get(spu, 0) & mask;

	spu->class_0_pending |= stat;
	spu->class_0_dar = spu_mfc_dar_get(spu);
	spu->stop_callback(spu, 0);
	spu->class_0_pending = 0;
	spu->class_0_dar = 0;

	spu_पूर्णांक_stat_clear(spu, 0, stat);
	spin_unlock(&spu->रेजिस्टर_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
spu_irq_class_1(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spu *spu;
	अचिन्हित दीर्घ stat, mask, dar, dsisr;

	spu = data;

	/* atomically पढ़ो & clear class1 status. */
	spin_lock(&spu->रेजिस्टर_lock);
	mask  = spu_पूर्णांक_mask_get(spu, 1);
	stat  = spu_पूर्णांक_stat_get(spu, 1) & mask;
	dar   = spu_mfc_dar_get(spu);
	dsisr = spu_mfc_dsisr_get(spu);
	अगर (stat & CLASS1_STORAGE_FAULT_INTR)
		spu_mfc_dsisr_set(spu, 0ul);
	spu_पूर्णांक_stat_clear(spu, 1, stat);

	pr_debug("%s: %lx %lx %lx %lx\n", __func__, mask, stat,
			dar, dsisr);

	अगर (stat & CLASS1_SEGMENT_FAULT_INTR)
		__spu_trap_data_seg(spu, dar);

	अगर (stat & CLASS1_STORAGE_FAULT_INTR)
		__spu_trap_data_map(spu, dar, dsisr);

	अगर (stat & CLASS1_LS_COMPARE_SUSPEND_ON_GET_INTR)
		;

	अगर (stat & CLASS1_LS_COMPARE_SUSPEND_ON_PUT_INTR)
		;

	spu->class_1_dsisr = 0;
	spu->class_1_dar = 0;

	spin_unlock(&spu->रेजिस्टर_lock);

	वापस stat ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल irqवापस_t
spu_irq_class_2(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spu *spu;
	अचिन्हित दीर्घ stat;
	अचिन्हित दीर्घ mask;
	स्थिर पूर्णांक mailbox_पूर्णांकrs =
		CLASS2_MAILBOX_THRESHOLD_INTR | CLASS2_MAILBOX_INTR;

	spu = data;
	spin_lock(&spu->रेजिस्टर_lock);
	stat = spu_पूर्णांक_stat_get(spu, 2);
	mask = spu_पूर्णांक_mask_get(spu, 2);
	/* ignore पूर्णांकerrupts we're not रुकोing क्रम */
	stat &= mask;
	/* mailbox पूर्णांकerrupts are level triggered. mask them now beक्रमe
	 * acknowledging */
	अगर (stat & mailbox_पूर्णांकrs)
		spu_पूर्णांक_mask_and(spu, 2, ~(stat & mailbox_पूर्णांकrs));
	/* acknowledge all पूर्णांकerrupts beक्रमe the callbacks */
	spu_पूर्णांक_stat_clear(spu, 2, stat);

	pr_debug("class 2 interrupt %d, %lx, %lx\n", irq, stat, mask);

	अगर (stat & CLASS2_MAILBOX_INTR)
		spu->ibox_callback(spu);

	अगर (stat & CLASS2_SPU_STOP_INTR)
		spu->stop_callback(spu, 2);

	अगर (stat & CLASS2_SPU_HALT_INTR)
		spu->stop_callback(spu, 2);

	अगर (stat & CLASS2_SPU_DMA_TAG_GROUP_COMPLETE_INTR)
		spu->mfc_callback(spu);

	अगर (stat & CLASS2_MAILBOX_THRESHOLD_INTR)
		spu->wbox_callback(spu);

	spu->stats.class2_पूर्णांकr++;

	spin_unlock(&spu->रेजिस्टर_lock);

	वापस stat ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक spu_request_irqs(काष्ठा spu *spu)
अणु
	पूर्णांक ret = 0;

	अगर (spu->irqs[0]) अणु
		snम_लिखो(spu->irq_c0, माप (spu->irq_c0), "spe%02d.0",
			 spu->number);
		ret = request_irq(spu->irqs[0], spu_irq_class_0,
				  0, spu->irq_c0, spu);
		अगर (ret)
			जाओ bail0;
	पूर्ण
	अगर (spu->irqs[1]) अणु
		snम_लिखो(spu->irq_c1, माप (spu->irq_c1), "spe%02d.1",
			 spu->number);
		ret = request_irq(spu->irqs[1], spu_irq_class_1,
				  0, spu->irq_c1, spu);
		अगर (ret)
			जाओ bail1;
	पूर्ण
	अगर (spu->irqs[2]) अणु
		snम_लिखो(spu->irq_c2, माप (spu->irq_c2), "spe%02d.2",
			 spu->number);
		ret = request_irq(spu->irqs[2], spu_irq_class_2,
				  0, spu->irq_c2, spu);
		अगर (ret)
			जाओ bail2;
	पूर्ण
	वापस 0;

bail2:
	अगर (spu->irqs[1])
		मुक्त_irq(spu->irqs[1], spu);
bail1:
	अगर (spu->irqs[0])
		मुक्त_irq(spu->irqs[0], spu);
bail0:
	वापस ret;
पूर्ण

अटल व्योम spu_मुक्त_irqs(काष्ठा spu *spu)
अणु
	अगर (spu->irqs[0])
		मुक्त_irq(spu->irqs[0], spu);
	अगर (spu->irqs[1])
		मुक्त_irq(spu->irqs[1], spu);
	अगर (spu->irqs[2])
		मुक्त_irq(spu->irqs[2], spu);
पूर्ण

व्योम spu_init_channels(काष्ठा spu *spu)
अणु
	अटल स्थिर काष्ठा अणु
		 अचिन्हित channel;
		 अचिन्हित count;
	पूर्ण zero_list[] = अणु
		अणु 0x00, 1, पूर्ण, अणु 0x01, 1, पूर्ण, अणु 0x03, 1, पूर्ण, अणु 0x04, 1, पूर्ण,
		अणु 0x18, 1, पूर्ण, अणु 0x19, 1, पूर्ण, अणु 0x1b, 1, पूर्ण, अणु 0x1d, 1, पूर्ण,
	पूर्ण, count_list[] = अणु
		अणु 0x00, 0, पूर्ण, अणु 0x03, 0, पूर्ण, अणु 0x04, 0, पूर्ण, अणु 0x15, 16, पूर्ण,
		अणु 0x17, 1, पूर्ण, अणु 0x18, 0, पूर्ण, अणु 0x19, 0, पूर्ण, अणु 0x1b, 0, पूर्ण,
		अणु 0x1c, 1, पूर्ण, अणु 0x1d, 0, पूर्ण, अणु 0x1e, 1, पूर्ण,
	पूर्ण;
	काष्ठा spu_priv2 __iomem *priv2;
	पूर्णांक i;

	priv2 = spu->priv2;

	/* initialize all channel data to zero */
	क्रम (i = 0; i < ARRAY_SIZE(zero_list); i++) अणु
		पूर्णांक count;

		out_be64(&priv2->spu_chnlcntptr_RW, zero_list[i].channel);
		क्रम (count = 0; count < zero_list[i].count; count++)
			out_be64(&priv2->spu_chnldata_RW, 0);
	पूर्ण

	/* initialize channel counts to meaningful values */
	क्रम (i = 0; i < ARRAY_SIZE(count_list); i++) अणु
		out_be64(&priv2->spu_chnlcntptr_RW, count_list[i].channel);
		out_be64(&priv2->spu_chnlcnt_RW, count_list[i].count);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(spu_init_channels);

अटल काष्ठा bus_type spu_subsys = अणु
	.name = "spu",
	.dev_name = "spu",
पूर्ण;

पूर्णांक spu_add_dev_attr(काष्ठा device_attribute *attr)
अणु
	काष्ठा spu *spu;

	mutex_lock(&spu_full_list_mutex);
	list_क्रम_each_entry(spu, &spu_full_list, full_list)
		device_create_file(&spu->dev, attr);
	mutex_unlock(&spu_full_list_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spu_add_dev_attr);

पूर्णांक spu_add_dev_attr_group(काष्ठा attribute_group *attrs)
अणु
	काष्ठा spu *spu;
	पूर्णांक rc = 0;

	mutex_lock(&spu_full_list_mutex);
	list_क्रम_each_entry(spu, &spu_full_list, full_list) अणु
		rc = sysfs_create_group(&spu->dev.kobj, attrs);

		/* we're in trouble here, but try unwinding anyway */
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: can't create sysfs group '%s'\n",
					__func__, attrs->name);

			list_क्रम_each_entry_जारी_reverse(spu,
					&spu_full_list, full_list)
				sysfs_हटाओ_group(&spu->dev.kobj, attrs);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&spu_full_list_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(spu_add_dev_attr_group);


व्योम spu_हटाओ_dev_attr(काष्ठा device_attribute *attr)
अणु
	काष्ठा spu *spu;

	mutex_lock(&spu_full_list_mutex);
	list_क्रम_each_entry(spu, &spu_full_list, full_list)
		device_हटाओ_file(&spu->dev, attr);
	mutex_unlock(&spu_full_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(spu_हटाओ_dev_attr);

व्योम spu_हटाओ_dev_attr_group(काष्ठा attribute_group *attrs)
अणु
	काष्ठा spu *spu;

	mutex_lock(&spu_full_list_mutex);
	list_क्रम_each_entry(spu, &spu_full_list, full_list)
		sysfs_हटाओ_group(&spu->dev.kobj, attrs);
	mutex_unlock(&spu_full_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(spu_हटाओ_dev_attr_group);

अटल पूर्णांक spu_create_dev(काष्ठा spu *spu)
अणु
	पूर्णांक ret;

	spu->dev.id = spu->number;
	spu->dev.bus = &spu_subsys;
	ret = device_रेजिस्टर(&spu->dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Can't register SPU %d with sysfs\n",
				spu->number);
		वापस ret;
	पूर्ण

	sysfs_add_device_to_node(&spu->dev, spu->node);

	वापस 0;
पूर्ण

अटल पूर्णांक __init create_spu(व्योम *data)
अणु
	काष्ठा spu *spu;
	पूर्णांक ret;
	अटल पूर्णांक number;
	अचिन्हित दीर्घ flags;

	ret = -ENOMEM;
	spu = kzalloc(माप (*spu), GFP_KERNEL);
	अगर (!spu)
		जाओ out;

	spu->alloc_state = SPU_FREE;

	spin_lock_init(&spu->रेजिस्टर_lock);
	spin_lock(&spu_lock);
	spu->number = number++;
	spin_unlock(&spu_lock);

	ret = spu_create_spu(spu, data);

	अगर (ret)
		जाओ out_मुक्त;

	spu_mfc_sdr_setup(spu);
	spu_mfc_sr1_set(spu, 0x33);
	ret = spu_request_irqs(spu);
	अगर (ret)
		जाओ out_destroy;

	ret = spu_create_dev(spu);
	अगर (ret)
		जाओ out_मुक्त_irqs;

	mutex_lock(&cbe_spu_info[spu->node].list_mutex);
	list_add(&spu->cbe_list, &cbe_spu_info[spu->node].spus);
	cbe_spu_info[spu->node].n_spus++;
	mutex_unlock(&cbe_spu_info[spu->node].list_mutex);

	mutex_lock(&spu_full_list_mutex);
	spin_lock_irqsave(&spu_full_list_lock, flags);
	list_add(&spu->full_list, &spu_full_list);
	spin_unlock_irqrestore(&spu_full_list_lock, flags);
	mutex_unlock(&spu_full_list_mutex);

	spu->stats.util_state = SPU_UTIL_IDLE_LOADED;
	spu->stats.tstamp = kसमय_get_ns();

	INIT_LIST_HEAD(&spu->aff_list);

	जाओ out;

out_मुक्त_irqs:
	spu_मुक्त_irqs(spu);
out_destroy:
	spu_destroy_spu(spu);
out_मुक्त:
	kमुक्त(spu);
out:
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *spu_state_names[] = अणु
	"user", "system", "iowait", "idle"
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ spu_acct_समय(काष्ठा spu *spu,
		क्रमागत spu_utilization_state state)
अणु
	अचिन्हित दीर्घ दीर्घ समय = spu->stats.बार[state];

	/*
	 * If the spu is idle or the context is stopped, utilization
	 * statistics are not updated.  Apply the समय delta from the
	 * last recorded state of the spu.
	 */
	अगर (spu->stats.util_state == state)
		समय += kसमय_get_ns() - spu->stats.tstamp;

	वापस समय / NSEC_PER_MSEC;
पूर्ण


अटल sमाप_प्रकार spu_stat_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा spu *spu = container_of(dev, काष्ठा spu, dev);

	वापस प्र_लिखो(buf, "%s %llu %llu %llu %llu "
		      "%llu %llu %llu %llu %llu %llu %llu %llu\n",
		spu_state_names[spu->stats.util_state],
		spu_acct_समय(spu, SPU_UTIL_USER),
		spu_acct_समय(spu, SPU_UTIL_SYSTEM),
		spu_acct_समय(spu, SPU_UTIL_IOWAIT),
		spu_acct_समय(spu, SPU_UTIL_IDLE_LOADED),
		spu->stats.vol_ctx_चयन,
		spu->stats.invol_ctx_चयन,
		spu->stats.slb_flt,
		spu->stats.hash_flt,
		spu->stats.min_flt,
		spu->stats.maj_flt,
		spu->stats.class2_पूर्णांकr,
		spu->stats.libassist);
पूर्ण

अटल DEVICE_ATTR(stat, 0444, spu_stat_show, शून्य);

#अगर_घोषित CONFIG_KEXEC_CORE

काष्ठा crash_spu_info अणु
	काष्ठा spu *spu;
	u32 saved_spu_runcntl_RW;
	u32 saved_spu_status_R;
	u32 saved_spu_npc_RW;
	u64 saved_mfc_sr1_RW;
	u64 saved_mfc_dar;
	u64 saved_mfc_dsisr;
पूर्ण;

#घोषणा CRASH_NUM_SPUS	16	/* Enough क्रम current hardware */
अटल काष्ठा crash_spu_info crash_spu_info[CRASH_NUM_SPUS];

अटल व्योम crash_kexec_stop_spus(व्योम)
अणु
	काष्ठा spu *spu;
	पूर्णांक i;
	u64 पंचांगp;

	क्रम (i = 0; i < CRASH_NUM_SPUS; i++) अणु
		अगर (!crash_spu_info[i].spu)
			जारी;

		spu = crash_spu_info[i].spu;

		crash_spu_info[i].saved_spu_runcntl_RW =
			in_be32(&spu->problem->spu_runcntl_RW);
		crash_spu_info[i].saved_spu_status_R =
			in_be32(&spu->problem->spu_status_R);
		crash_spu_info[i].saved_spu_npc_RW =
			in_be32(&spu->problem->spu_npc_RW);

		crash_spu_info[i].saved_mfc_dar    = spu_mfc_dar_get(spu);
		crash_spu_info[i].saved_mfc_dsisr  = spu_mfc_dsisr_get(spu);
		पंचांगp = spu_mfc_sr1_get(spu);
		crash_spu_info[i].saved_mfc_sr1_RW = पंचांगp;

		पंचांगp &= ~MFC_STATE1_MASTER_RUN_CONTROL_MASK;
		spu_mfc_sr1_set(spu, पंचांगp);

		__delay(200);
	पूर्ण
पूर्ण

अटल व्योम crash_रेजिस्टर_spus(काष्ठा list_head *list)
अणु
	काष्ठा spu *spu;
	पूर्णांक ret;

	list_क्रम_each_entry(spu, list, full_list) अणु
		अगर (WARN_ON(spu->number >= CRASH_NUM_SPUS))
			जारी;

		crash_spu_info[spu->number].spu = spu;
	पूर्ण

	ret = crash_shutकरोwn_रेजिस्टर(&crash_kexec_stop_spus);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "Could not register SPU crash handler");
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम crash_रेजिस्टर_spus(काष्ठा list_head *list)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम spu_shutकरोwn(व्योम)
अणु
	काष्ठा spu *spu;

	mutex_lock(&spu_full_list_mutex);
	list_क्रम_each_entry(spu, &spu_full_list, full_list) अणु
		spu_मुक्त_irqs(spu);
		spu_destroy_spu(spu);
	पूर्ण
	mutex_unlock(&spu_full_list_mutex);
पूर्ण

अटल काष्ठा syscore_ops spu_syscore_ops = अणु
	.shutकरोwn = spu_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init init_spu_base(व्योम)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		mutex_init(&cbe_spu_info[i].list_mutex);
		INIT_LIST_HEAD(&cbe_spu_info[i].spus);
	पूर्ण

	अगर (!spu_management_ops)
		जाओ out;

	/* create प्रणाली subप्रणाली क्रम spus */
	ret = subsys_प्रणाली_रेजिस्टर(&spu_subsys, शून्य);
	अगर (ret)
		जाओ out;

	ret = spu_क्रमागतerate_spus(create_spu);

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error initializing spus\n",
			__func__);
		जाओ out_unरेजिस्टर_subsys;
	पूर्ण

	अगर (ret > 0)
		fb_append_extra_logo(&logo_spe_clut224, ret);

	mutex_lock(&spu_full_list_mutex);
	xmon_रेजिस्टर_spus(&spu_full_list);
	crash_रेजिस्टर_spus(&spu_full_list);
	mutex_unlock(&spu_full_list_mutex);
	spu_add_dev_attr(&dev_attr_stat);
	रेजिस्टर_syscore_ops(&spu_syscore_ops);

	spu_init_affinity();

	वापस 0;

 out_unरेजिस्टर_subsys:
	bus_unरेजिस्टर(&spu_subsys);
 out:
	वापस ret;
पूर्ण
device_initcall(init_spu_base);
