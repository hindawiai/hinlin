<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/workqueue.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/pid.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleparam.h>

#अघोषित MODULE_PARAM_PREFIX
#घोषणा MODULE_PARAM_PREFIX "cxl" "."
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/copro.h>
#समावेश <यंत्र/mmu.h>

#समावेश "cxl.h"
#समावेश "trace.h"

अटल bool sste_matches(काष्ठा cxl_sste *sste, काष्ठा copro_slb *slb)
अणु
	वापस ((sste->vsid_data == cpu_to_be64(slb->vsid)) &&
		(sste->esid_data == cpu_to_be64(slb->esid)));
पूर्ण

/*
 * This finds a मुक्त SSTE क्रम the given SLB, or वापसs शून्य अगर it's alपढ़ोy in
 * the segment table.
 */
अटल काष्ठा cxl_sste *find_मुक्त_sste(काष्ठा cxl_context *ctx,
				       काष्ठा copro_slb *slb)
अणु
	काष्ठा cxl_sste *primary, *sste, *ret = शून्य;
	अचिन्हित पूर्णांक mask = (ctx->sst_size >> 7) - 1; /* SSTP0[SegTableSize] */
	अचिन्हित पूर्णांक entry;
	अचिन्हित पूर्णांक hash;

	अगर (slb->vsid & SLB_VSID_B_1T)
		hash = (slb->esid >> SID_SHIFT_1T) & mask;
	अन्यथा /* 256M */
		hash = (slb->esid >> SID_SHIFT) & mask;

	primary = ctx->sstp + (hash << 3);

	क्रम (entry = 0, sste = primary; entry < 8; entry++, sste++) अणु
		अगर (!ret && !(be64_to_cpu(sste->esid_data) & SLB_ESID_V))
			ret = sste;
		अगर (sste_matches(sste, slb))
			वापस शून्य;
	पूर्ण
	अगर (ret)
		वापस ret;

	/* Nothing मुक्त, select an entry to cast out */
	ret = primary + ctx->sst_lru;
	ctx->sst_lru = (ctx->sst_lru + 1) & 0x7;

	वापस ret;
पूर्ण

अटल व्योम cxl_load_segment(काष्ठा cxl_context *ctx, काष्ठा copro_slb *slb)
अणु
	/* mask is the group index, we search primary and secondary here. */
	काष्ठा cxl_sste *sste;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->sste_lock, flags);
	sste = find_मुक्त_sste(ctx, slb);
	अगर (!sste)
		जाओ out_unlock;

	pr_devel("CXL Populating SST[%li]: %#llx %#llx\n",
			sste - ctx->sstp, slb->vsid, slb->esid);
	trace_cxl_ste_ग_लिखो(ctx, sste - ctx->sstp, slb->esid, slb->vsid);

	sste->vsid_data = cpu_to_be64(slb->vsid);
	sste->esid_data = cpu_to_be64(slb->esid);
out_unlock:
	spin_unlock_irqrestore(&ctx->sste_lock, flags);
पूर्ण

अटल पूर्णांक cxl_fault_segment(काष्ठा cxl_context *ctx, काष्ठा mm_काष्ठा *mm,
			     u64 ea)
अणु
	काष्ठा copro_slb slb = अणु0,0पूर्ण;
	पूर्णांक rc;

	अगर (!(rc = copro_calculate_slb(mm, ea, &slb))) अणु
		cxl_load_segment(ctx, &slb);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम cxl_ack_ae(काष्ठा cxl_context *ctx)
अणु
	अचिन्हित दीर्घ flags;

	cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_AE, 0);

	spin_lock_irqsave(&ctx->lock, flags);
	ctx->pending_fault = true;
	ctx->fault_addr = ctx->dar;
	ctx->fault_dsisr = ctx->dsisr;
	spin_unlock_irqrestore(&ctx->lock, flags);

	wake_up_all(&ctx->wq);
पूर्ण

अटल पूर्णांक cxl_handle_segment_miss(काष्ठा cxl_context *ctx,
				   काष्ठा mm_काष्ठा *mm, u64 ea)
अणु
	पूर्णांक rc;

	pr_devel("CXL interrupt: Segment fault pe: %i ea: %#llx\n", ctx->pe, ea);
	trace_cxl_ste_miss(ctx, ea);

	अगर ((rc = cxl_fault_segment(ctx, mm, ea)))
		cxl_ack_ae(ctx);
	अन्यथा अणु

		mb(); /* Order seg table ग_लिखो to TFC MMIO ग_लिखो */
		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_R, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक cxl_handle_mm_fault(काष्ठा mm_काष्ठा *mm, u64 dsisr, u64 dar)
अणु
	vm_fault_t flt = 0;
	पूर्णांक result;
	अचिन्हित दीर्घ access, flags, inv_flags = 0;

	/*
	 * Add the fault handling cpu to task mm cpumask so that we
	 * can करो a safe lockless page table walk when inserting the
	 * hash page table entry. This function get called with a
	 * valid mm क्रम user space addresses. Hence using the अगर (mm)
	 * check is sufficient here.
	 */
	अगर (mm && !cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm))) अणु
		cpumask_set_cpu(smp_processor_id(), mm_cpumask(mm));
		/*
		 * We need to make sure we walk the table only after
		 * we update the cpumask. The other side of the barrier
		 * is explained in serialize_against_pte_lookup()
		 */
		smp_mb();
	पूर्ण
	अगर ((result = copro_handle_mm_fault(mm, dar, dsisr, &flt))) अणु
		pr_devel("copro_handle_mm_fault failed: %#x\n", result);
		वापस result;
	पूर्ण

	अगर (!radix_enabled()) अणु
		/*
		 * update_mmu_cache() will not have loaded the hash since current->trap
		 * is not a 0x400 or 0x300, so just call hash_page_mm() here.
		 */
		access = _PAGE_PRESENT | _PAGE_READ;
		अगर (dsisr & CXL_PSL_DSISR_An_S)
			access |= _PAGE_WRITE;

		अगर (!mm && (get_region_id(dar) != USER_REGION_ID))
			access |= _PAGE_PRIVILEGED;

		अगर (dsisr & DSISR_NOHPTE)
			inv_flags |= HPTE_NOHPTE_UPDATE;

		local_irq_save(flags);
		hash_page_mm(mm, dar, access, 0x300, inv_flags);
		local_irq_restore(flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cxl_handle_page_fault(काष्ठा cxl_context *ctx,
				  काष्ठा mm_काष्ठा *mm,
				  u64 dsisr, u64 dar)
अणु
	trace_cxl_pte_miss(ctx, dsisr, dar);

	अगर (cxl_handle_mm_fault(mm, dsisr, dar)) अणु
		cxl_ack_ae(ctx);
	पूर्ण अन्यथा अणु
		pr_devel("Page fault successfully handled for pe: %i!\n", ctx->pe);
		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_R, 0);
	पूर्ण
पूर्ण

/*
 * Returns the mm_काष्ठा corresponding to the context ctx.
 * mm_users == 0, the context may be in the process of being बंदd.
 */
अटल काष्ठा mm_काष्ठा *get_mem_context(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->mm == शून्य)
		वापस शून्य;

	अगर (!mmget_not_zero(ctx->mm))
		वापस शून्य;

	वापस ctx->mm;
पूर्ण

अटल bool cxl_is_segment_miss(काष्ठा cxl_context *ctx, u64 dsisr)
अणु
	अगर ((cxl_is_घातer8() && (dsisr & CXL_PSL_DSISR_An_DS)))
		वापस true;

	वापस false;
पूर्ण

अटल bool cxl_is_page_fault(काष्ठा cxl_context *ctx, u64 dsisr)
अणु
	अगर ((cxl_is_घातer8()) && (dsisr & CXL_PSL_DSISR_An_DM))
		वापस true;

	अगर (cxl_is_घातer9())
		वापस true;

	वापस false;
पूर्ण

व्योम cxl_handle_fault(काष्ठा work_काष्ठा *fault_work)
अणु
	काष्ठा cxl_context *ctx =
		container_of(fault_work, काष्ठा cxl_context, fault_work);
	u64 dsisr = ctx->dsisr;
	u64 dar = ctx->dar;
	काष्ठा mm_काष्ठा *mm = शून्य;

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		अगर (cxl_p2n_पढ़ो(ctx->afu, CXL_PSL_DSISR_An) != dsisr ||
		    cxl_p2n_पढ़ो(ctx->afu, CXL_PSL_DAR_An) != dar ||
		    cxl_p2n_पढ़ो(ctx->afu, CXL_PSL_PEHandle_An) != ctx->pe) अणु
			/* Most likely explanation is harmless - a dedicated
			 * process has detached and these were cleared by the
			 * PSL purge, but warn about it just in हाल
			 */
			dev_notice(&ctx->afu->dev, "cxl_handle_fault: Translation fault regs changed\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Early वापस अगर the context is being / has been detached */
	अगर (ctx->status == CLOSED) अणु
		cxl_ack_ae(ctx);
		वापस;
	पूर्ण

	pr_devel("CXL BOTTOM HALF handling fault for afu pe: %i. "
		"DSISR: %#llx DAR: %#llx\n", ctx->pe, dsisr, dar);

	अगर (!ctx->kernel) अणु

		mm = get_mem_context(ctx);
		अगर (mm == शून्य) अणु
			pr_devel("%s: unable to get mm for pe=%d pid=%i\n",
				 __func__, ctx->pe, pid_nr(ctx->pid));
			cxl_ack_ae(ctx);
			वापस;
		पूर्ण अन्यथा अणु
			pr_devel("Handling page fault for pe=%d pid=%i\n",
				 ctx->pe, pid_nr(ctx->pid));
		पूर्ण
	पूर्ण

	अगर (cxl_is_segment_miss(ctx, dsisr))
		cxl_handle_segment_miss(ctx, mm, dar);
	अन्यथा अगर (cxl_is_page_fault(ctx, dsisr))
		cxl_handle_page_fault(ctx, mm, dsisr, dar);
	अन्यथा
		WARN(1, "cxl_handle_fault has nothing to handle\n");

	अगर (mm)
		mmput(mm);
पूर्ण

अटल व्योम cxl_prefault_one(काष्ठा cxl_context *ctx, u64 ea)
अणु
	काष्ठा mm_काष्ठा *mm;

	mm = get_mem_context(ctx);
	अगर (mm == शून्य) अणु
		pr_devel("cxl_prefault_one unable to get mm %i\n",
			 pid_nr(ctx->pid));
		वापस;
	पूर्ण

	cxl_fault_segment(ctx, mm, ea);

	mmput(mm);
पूर्ण

अटल u64 next_segment(u64 ea, u64 vsid)
अणु
	अगर (vsid & SLB_VSID_B_1T)
		ea |= (1ULL << 40) - 1;
	अन्यथा
		ea |= (1ULL << 28) - 1;

	वापस ea + 1;
पूर्ण

अटल व्योम cxl_prefault_vma(काष्ठा cxl_context *ctx)
अणु
	u64 ea, last_esid = 0;
	काष्ठा copro_slb slb;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक rc;
	काष्ठा mm_काष्ठा *mm;

	mm = get_mem_context(ctx);
	अगर (mm == शून्य) अणु
		pr_devel("cxl_prefault_vm unable to get mm %i\n",
			 pid_nr(ctx->pid));
		वापस;
	पूर्ण

	mmap_पढ़ो_lock(mm);
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		क्रम (ea = vma->vm_start; ea < vma->vm_end;
				ea = next_segment(ea, slb.vsid)) अणु
			rc = copro_calculate_slb(mm, ea, &slb);
			अगर (rc)
				जारी;

			अगर (last_esid == slb.esid)
				जारी;

			cxl_load_segment(ctx, &slb);
			last_esid = slb.esid;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	mmput(mm);
पूर्ण

व्योम cxl_prefault(काष्ठा cxl_context *ctx, u64 wed)
अणु
	चयन (ctx->afu->prefault_mode) अणु
	हाल CXL_PREFAULT_WED:
		cxl_prefault_one(ctx, wed);
		अवरोध;
	हाल CXL_PREFAULT_ALL:
		cxl_prefault_vma(ctx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
