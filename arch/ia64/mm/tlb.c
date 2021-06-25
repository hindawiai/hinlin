<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TLB support routines.
 *
 * Copyright (C) 1998-2001, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * 08/02/00 A. Mallick <asit.k.mallick@पूर्णांकel.com>
 *		Modअगरied RID allocation क्रम SMP
 *          Goutham Rao <goutham.rao@पूर्णांकel.com>
 *              IPI based ptc implementation and A-step IPI implementation.
 * Rohit Seth <rohit.seth@पूर्णांकel.com>
 * Ken Chen <kenneth.w.chen@पूर्णांकel.com>
 * Christophe de Dinechin <ddd@hp.com>: Aव्योम ptc.e on memory allocation
 * Copyright (C) 2007 Intel Corp
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Add multiple ptc.g/ptc.ga inकाष्ठाion support in global tlb purge.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/tlb.h>

अटल काष्ठा अणु
	u64 mask;		/* mask of supported purge page-sizes */
	अचिन्हित दीर्घ max_bits;	/* log2 of largest supported purge page-size */
पूर्ण purge;

काष्ठा ia64_ctx ia64_ctx = अणु
	.lock =	__SPIN_LOCK_UNLOCKED(ia64_ctx.lock),
	.next =	1,
	.max_ctx = ~0U
पूर्ण;

DEFINE_PER_CPU(u8, ia64_need_tlb_flush);
DEFINE_PER_CPU(u8, ia64_tr_num);  /*Number of TR slots in current processor*/
DEFINE_PER_CPU(u8, ia64_tr_used); /*Max Slot number used by kernel*/

काष्ठा ia64_tr_entry *ia64_idtrs[NR_CPUS];

/*
 * Initializes the ia64_ctx.biपंचांगap array based on max_ctx+1.
 * Called after cpu_init() has setup ia64_ctx.max_ctx based on
 * maximum RID that is supported by boot CPU.
 */
व्योम __init
mmu_context_init (व्योम)
अणु
	ia64_ctx.biपंचांगap = memblock_alloc((ia64_ctx.max_ctx + 1) >> 3,
					 SMP_CACHE_BYTES);
	अगर (!ia64_ctx.biपंचांगap)
		panic("%s: Failed to allocate %u bytes\n", __func__,
		      (ia64_ctx.max_ctx + 1) >> 3);
	ia64_ctx.flushmap = memblock_alloc((ia64_ctx.max_ctx + 1) >> 3,
					   SMP_CACHE_BYTES);
	अगर (!ia64_ctx.flushmap)
		panic("%s: Failed to allocate %u bytes\n", __func__,
		      (ia64_ctx.max_ctx + 1) >> 3);
पूर्ण

/*
 * Acquire the ia64_ctx.lock beक्रमe calling this function!
 */
व्योम
wrap_mmu_context (काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i, cpu;
	अचिन्हित दीर्घ flush_bit;

	क्रम (i=0; i <= ia64_ctx.max_ctx / BITS_PER_LONG; i++) अणु
		flush_bit = xchg(&ia64_ctx.flushmap[i], 0);
		ia64_ctx.biपंचांगap[i] ^= flush_bit;
	पूर्ण
 
	/* use offset at 300 to skip daemons */
	ia64_ctx.next = find_next_zero_bit(ia64_ctx.biपंचांगap,
				ia64_ctx.max_ctx, 300);
	ia64_ctx.limit = find_next_bit(ia64_ctx.biपंचांगap,
				ia64_ctx.max_ctx, ia64_ctx.next);

	/*
	 * can't call flush_tlb_all() here because of race condition
	 * with O(1) scheduler [EF]
	 */
	cpu = get_cpu(); /* prevent preemption/migration */
	क्रम_each_online_cpu(i)
		अगर (i != cpu)
			per_cpu(ia64_need_tlb_flush, i) = 1;
	put_cpu();
	local_flush_tlb_all();
पूर्ण

/*
 * Implement "spinaphores" ... like counting semaphores, but they
 * spin instead of sleeping.  If there are ever any other users क्रम
 * this primitive it can be moved up to a spinaphore.h header.
 */
काष्ठा spinaphore अणु
	अचिन्हित दीर्घ	ticket;
	अचिन्हित दीर्घ	serve;
पूर्ण;

अटल अंतरभूत व्योम spinaphore_init(काष्ठा spinaphore *ss, पूर्णांक val)
अणु
	ss->ticket = 0;
	ss->serve = val;
पूर्ण

अटल अंतरभूत व्योम करोwn_spin(काष्ठा spinaphore *ss)
अणु
	अचिन्हित दीर्घ t = ia64_fetchadd(1, &ss->ticket, acq), serve;

	अगर (समय_beक्रमe(t, ss->serve))
		वापस;

	ia64_invala();

	क्रम (;;) अणु
		यंत्र अस्थिर ("ld8.c.nc %0=[%1]" : "=r"(serve) : "r"(&ss->serve) : "memory");
		अगर (समय_beक्रमe(t, serve))
			वापस;
		cpu_relax();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम up_spin(काष्ठा spinaphore *ss)
अणु
	ia64_fetchadd(1, &ss->serve, rel);
पूर्ण

अटल काष्ठा spinaphore ptcg_sem;
अटल u16 nptcg = 1;
अटल पूर्णांक need_ptcg_sem = 1;
अटल पूर्णांक toolatetochangeptcgsem = 0;

/*
 * Kernel parameter "nptcg=" overrides max number of concurrent global TLB
 * purges which is reported from either PAL or SAL PALO.
 *
 * We करोn't have sanity checking for nptcg value. It's the user's responsibility
 * क्रम valid nptcg value on the platक्रमm. Otherwise, kernel may hang in some
 * हालs.
 */
अटल पूर्णांक __init
set_nptcg(अक्षर *str)
अणु
	पूर्णांक value = 0;

	get_option(&str, &value);
	setup_ptcg_sem(value, NPTCG_FROM_KERNEL_PARAMETER);

	वापस 1;
पूर्ण

__setup("nptcg=", set_nptcg);

/*
 * Maximum number of simultaneous ptc.g purges in the प्रणाली can
 * be defined by PAL_VM_SUMMARY (in which हाल we should take
 * the smallest value क्रम any cpu in the प्रणाली) or by the PAL
 * override table (in which हाल we should ignore the value from
 * PAL_VM_SUMMARY).
 *
 * Kernel parameter "nptcg=" overrides maximum number of simultanesous ptc.g
 * purges defined in either PAL_VM_SUMMARY or PAL override table. In this हाल,
 * we should ignore the value from either PAL_VM_SUMMARY or PAL override table.
 *
 * Complicating the logic here is the fact that num_possible_cpus()
 * isn't fully setup until we start bringing cpus online.
 */
व्योम
setup_ptcg_sem(पूर्णांक max_purges, पूर्णांक nptcg_from)
अणु
	अटल पूर्णांक kp_override;
	अटल पूर्णांक palo_override;
	अटल पूर्णांक firstcpu = 1;

	अगर (toolatetochangeptcgsem) अणु
		अगर (nptcg_from == NPTCG_FROM_PAL && max_purges == 0)
			BUG_ON(1 < nptcg);
		अन्यथा
			BUG_ON(max_purges < nptcg);
		वापस;
	पूर्ण

	अगर (nptcg_from == NPTCG_FROM_KERNEL_PARAMETER) अणु
		kp_override = 1;
		nptcg = max_purges;
		जाओ resetsema;
	पूर्ण
	अगर (kp_override) अणु
		need_ptcg_sem = num_possible_cpus() > nptcg;
		वापस;
	पूर्ण

	अगर (nptcg_from == NPTCG_FROM_PALO) अणु
		palo_override = 1;

		/* In PALO max_purges == 0 really means it! */
		अगर (max_purges == 0)
			panic("Whoa! Platform does not support global TLB purges.\n");
		nptcg = max_purges;
		अगर (nptcg == PALO_MAX_TLB_PURGES) अणु
			need_ptcg_sem = 0;
			वापस;
		पूर्ण
		जाओ resetsema;
	पूर्ण
	अगर (palo_override) अणु
		अगर (nptcg != PALO_MAX_TLB_PURGES)
			need_ptcg_sem = (num_possible_cpus() > nptcg);
		वापस;
	पूर्ण

	/* In PAL_VM_SUMMARY max_purges == 0 actually means 1 */
	अगर (max_purges == 0) max_purges = 1;

	अगर (firstcpu) अणु
		nptcg = max_purges;
		firstcpu = 0;
	पूर्ण
	अगर (max_purges < nptcg)
		nptcg = max_purges;
	अगर (nptcg == PAL_MAX_PURGES) अणु
		need_ptcg_sem = 0;
		वापस;
	पूर्ण अन्यथा
		need_ptcg_sem = (num_possible_cpus() > nptcg);

resetsema:
	spinaphore_init(&ptcg_sem, max_purges);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम
ia64_global_tlb_purge (काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ end, अचिन्हित दीर्घ nbits)
अणु
	काष्ठा mm_काष्ठा *active_mm = current->active_mm;

	toolatetochangeptcgsem = 1;

	अगर (mm != active_mm) अणु
		/* Restore region IDs क्रम mm */
		अगर (mm && active_mm) अणु
			activate_context(mm);
		पूर्ण अन्यथा अणु
			flush_tlb_all();
			वापस;
		पूर्ण
	पूर्ण

	अगर (need_ptcg_sem)
		करोwn_spin(&ptcg_sem);

	करो अणु
		/*
		 * Flush ALAT entries also.
		 */
		ia64_ptcga(start, (nbits << 2));
		ia64_srlz_i();
		start += (1UL << nbits);
	पूर्ण जबतक (start < end);

	अगर (need_ptcg_sem)
		up_spin(&ptcg_sem);

        अगर (mm != active_mm) अणु
                activate_context(active_mm);
        पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

व्योम
local_flush_tlb_all (व्योम)
अणु
	अचिन्हित दीर्घ i, j, flags, count0, count1, stride0, stride1, addr;

	addr    = local_cpu_data->ptce_base;
	count0  = local_cpu_data->ptce_count[0];
	count1  = local_cpu_data->ptce_count[1];
	stride0 = local_cpu_data->ptce_stride[0];
	stride1 = local_cpu_data->ptce_stride[1];

	local_irq_save(flags);
	क्रम (i = 0; i < count0; ++i) अणु
		क्रम (j = 0; j < count1; ++j) अणु
			ia64_ptce(addr);
			addr += stride1;
		पूर्ण
		addr += stride0;
	पूर्ण
	local_irq_restore(flags);
	ia64_srlz_i();			/* srlz.i implies srlz.d */
पूर्ण

अटल व्योम
__flush_tlb_range (काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		 अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ size = end - start;
	अचिन्हित दीर्घ nbits;

#अगर_अघोषित CONFIG_SMP
	अगर (mm != current->active_mm) अणु
		mm->context = 0;
		वापस;
	पूर्ण
#पूर्ण_अगर

	nbits = ia64_fls(size + 0xfff);
	जबतक (unlikely (((1UL << nbits) & purge.mask) == 0) &&
			(nbits < purge.max_bits))
		++nbits;
	अगर (nbits > purge.max_bits)
		nbits = purge.max_bits;
	start &= ~((1UL << nbits) - 1);

	preempt_disable();
#अगर_घोषित CONFIG_SMP
	अगर (mm != current->active_mm || cpumask_weight(mm_cpumask(mm)) != 1) अणु
		ia64_global_tlb_purge(mm, start, end, nbits);
		preempt_enable();
		वापस;
	पूर्ण
#पूर्ण_अगर
	करो अणु
		ia64_ptcl(start, (nbits<<2));
		start += (1UL << nbits);
	पूर्ण जबतक (start < end);
	preempt_enable();
	ia64_srlz_i();			/* srlz.i implies srlz.d */
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (unlikely(end - start >= 1024*1024*1024*1024UL
			|| REGION_NUMBER(start) != REGION_NUMBER(end - 1))) अणु
		/*
		 * If we flush more than a tera-byte or across regions, we're
		 * probably better off just flushing the entire TLB(s).  This
		 * should be very rare and is not worth optimizing क्रम.
		 */
		flush_tlb_all();
	पूर्ण अन्यथा अणु
		/* flush the address range from the tlb */
		__flush_tlb_range(vma, start, end);
		/* flush the virt. page-table area mapping the addr range */
		__flush_tlb_range(vma, ia64_thash(start), ia64_thash(end));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_tlb_range);

व्योम ia64_tlb_init(व्योम)
अणु
	ia64_ptce_info_t ptce_info;
	u64 tr_pgbits;
	दीर्घ status;
	pal_vm_info_1_u_t vm_info_1;
	pal_vm_info_2_u_t vm_info_2;
	पूर्णांक cpu = smp_processor_id();

	अगर ((status = ia64_pal_vm_page_size(&tr_pgbits, &purge.mask)) != 0) अणु
		prपूर्णांकk(KERN_ERR "PAL_VM_PAGE_SIZE failed with status=%ld; "
		       "defaulting to architected purge page-sizes.\n", status);
		purge.mask = 0x115557000UL;
	पूर्ण
	purge.max_bits = ia64_fls(purge.mask);

	ia64_get_ptce(&ptce_info);
	local_cpu_data->ptce_base = ptce_info.base;
	local_cpu_data->ptce_count[0] = ptce_info.count[0];
	local_cpu_data->ptce_count[1] = ptce_info.count[1];
	local_cpu_data->ptce_stride[0] = ptce_info.stride[0];
	local_cpu_data->ptce_stride[1] = ptce_info.stride[1];

	local_flush_tlb_all();	/* nuke left overs from bootstrapping... */
	status = ia64_pal_vm_summary(&vm_info_1, &vm_info_2);

	अगर (status) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_vm_summary=%ld\n", status);
		per_cpu(ia64_tr_num, cpu) = 8;
		वापस;
	पूर्ण
	per_cpu(ia64_tr_num, cpu) = vm_info_1.pal_vm_info_1_s.max_itr_entry+1;
	अगर (per_cpu(ia64_tr_num, cpu) >
				(vm_info_1.pal_vm_info_1_s.max_dtr_entry+1))
		per_cpu(ia64_tr_num, cpu) =
				vm_info_1.pal_vm_info_1_s.max_dtr_entry+1;
	अगर (per_cpu(ia64_tr_num, cpu) > IA64_TR_ALLOC_MAX) अणु
		अटल पूर्णांक justonce = 1;
		per_cpu(ia64_tr_num, cpu) = IA64_TR_ALLOC_MAX;
		अगर (justonce) अणु
			justonce = 0;
			prपूर्णांकk(KERN_DEBUG "TR register number exceeds "
			       "IA64_TR_ALLOC_MAX!\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * is_tr_overlap
 *
 * Check overlap with inserted TRs.
 */
अटल पूर्णांक is_tr_overlap(काष्ठा ia64_tr_entry *p, u64 va, u64 log_size)
अणु
	u64 tr_log_size;
	u64 tr_end;
	u64 va_rr = ia64_get_rr(va);
	u64 va_rid = RR_TO_RID(va_rr);
	u64 बहु_पूर्ण = va + (1<<log_size) - 1;

	अगर (va_rid != RR_TO_RID(p->rr))
		वापस 0;
	tr_log_size = (p->itir & 0xff) >> 2;
	tr_end = p->अगरa + (1<<tr_log_size) - 1;

	अगर (va > tr_end || p->अगरa > बहु_पूर्ण)
		वापस 0;
	वापस 1;

पूर्ण

/*
 * ia64_insert_tr in भव mode. Allocate a TR slot
 *
 * target_mask : 0x1 : itr, 0x2 : dtr, 0x3 : idtr
 *
 * va 	: भव address.
 * pte 	: pte entries inserted.
 * log_size: range to be covered.
 *
 * Return value:  <0 :  error No.
 *
 *		  >=0 : slot number allocated क्रम TR.
 * Must be called with preemption disabled.
 */
पूर्णांक ia64_itr_entry(u64 target_mask, u64 va, u64 pte, u64 log_size)
अणु
	पूर्णांक i, r;
	अचिन्हित दीर्घ psr;
	काष्ठा ia64_tr_entry *p;
	पूर्णांक cpu = smp_processor_id();

	अगर (!ia64_idtrs[cpu]) अणु
		ia64_idtrs[cpu] = kदो_स्मृति_array(2 * IA64_TR_ALLOC_MAX,
						माप(काष्ठा ia64_tr_entry),
						GFP_KERNEL);
		अगर (!ia64_idtrs[cpu])
			वापस -ENOMEM;
	पूर्ण
	r = -EINVAL;
	/*Check overlap with existing TR entries*/
	अगर (target_mask & 0x1) अणु
		p = ia64_idtrs[cpu];
		क्रम (i = IA64_TR_ALLOC_BASE; i <= per_cpu(ia64_tr_used, cpu);
								i++, p++) अणु
			अगर (p->pte & 0x1)
				अगर (is_tr_overlap(p, va, log_size)) अणु
					prपूर्णांकk(KERN_DEBUG "Overlapped Entry"
						"Inserted for TR Register!!\n");
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (target_mask & 0x2) अणु
		p = ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX;
		क्रम (i = IA64_TR_ALLOC_BASE; i <= per_cpu(ia64_tr_used, cpu);
								i++, p++) अणु
			अगर (p->pte & 0x1)
				अगर (is_tr_overlap(p, va, log_size)) अणु
					prपूर्णांकk(KERN_DEBUG "Overlapped Entry"
						"Inserted for TR Register!!\n");
					जाओ out;
				पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = IA64_TR_ALLOC_BASE; i < per_cpu(ia64_tr_num, cpu); i++) अणु
		चयन (target_mask & 0x3) अणु
		हाल 1:
			अगर (!((ia64_idtrs[cpu] + i)->pte & 0x1))
				जाओ found;
			जारी;
		हाल 2:
			अगर (!((ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX + i)->pte & 0x1))
				जाओ found;
			जारी;
		हाल 3:
			अगर (!((ia64_idtrs[cpu] + i)->pte & 0x1) &&
			    !((ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX + i)->pte & 0x1))
				जाओ found;
			जारी;
		शेष:
			r = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
found:
	अगर (i >= per_cpu(ia64_tr_num, cpu))
		वापस -EBUSY;

	/*Record tr info क्रम mca hander use!*/
	अगर (i > per_cpu(ia64_tr_used, cpu))
		per_cpu(ia64_tr_used, cpu) = i;

	psr = ia64_clear_ic();
	अगर (target_mask & 0x1) अणु
		ia64_itr(0x1, i, va, pte, log_size);
		ia64_srlz_i();
		p = ia64_idtrs[cpu] + i;
		p->अगरa = va;
		p->pte = pte;
		p->itir = log_size << 2;
		p->rr = ia64_get_rr(va);
	पूर्ण
	अगर (target_mask & 0x2) अणु
		ia64_itr(0x2, i, va, pte, log_size);
		ia64_srlz_i();
		p = ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX + i;
		p->अगरa = va;
		p->pte = pte;
		p->itir = log_size << 2;
		p->rr = ia64_get_rr(va);
	पूर्ण
	ia64_set_psr(psr);
	r = i;
out:
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_itr_entry);

/*
 * ia64_purge_tr
 *
 * target_mask: 0x1: purge itr, 0x2 : purge dtr, 0x3 purge idtr.
 * slot: slot number to be मुक्तd.
 *
 * Must be called with preemption disabled.
 */
व्योम ia64_ptr_entry(u64 target_mask, पूर्णांक slot)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक i;
	काष्ठा ia64_tr_entry *p;

	अगर (slot < IA64_TR_ALLOC_BASE || slot >= per_cpu(ia64_tr_num, cpu))
		वापस;

	अगर (target_mask & 0x1) अणु
		p = ia64_idtrs[cpu] + slot;
		अगर ((p->pte&0x1) && is_tr_overlap(p, p->अगरa, p->itir>>2)) अणु
			p->pte = 0;
			ia64_ptr(0x1, p->अगरa, p->itir>>2);
			ia64_srlz_i();
		पूर्ण
	पूर्ण

	अगर (target_mask & 0x2) अणु
		p = ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX + slot;
		अगर ((p->pte & 0x1) && is_tr_overlap(p, p->अगरa, p->itir>>2)) अणु
			p->pte = 0;
			ia64_ptr(0x2, p->अगरa, p->itir>>2);
			ia64_srlz_i();
		पूर्ण
	पूर्ण

	क्रम (i = per_cpu(ia64_tr_used, cpu); i >= IA64_TR_ALLOC_BASE; i--) अणु
		अगर (((ia64_idtrs[cpu] + i)->pte & 0x1) ||
		    ((ia64_idtrs[cpu] + IA64_TR_ALLOC_MAX + i)->pte & 0x1))
			अवरोध;
	पूर्ण
	per_cpu(ia64_tr_used, cpu) = i;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_ptr_entry);
