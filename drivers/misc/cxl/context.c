<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/sched.h>
#समावेश <linux/pid.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmu_context.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/copro.h>

#समावेश "cxl.h"

/*
 * Allocates space क्रम a CXL context.
 */
काष्ठा cxl_context *cxl_context_alloc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा cxl_context), GFP_KERNEL);
पूर्ण

/*
 * Initialises a CXL context.
 */
पूर्णांक cxl_context_init(काष्ठा cxl_context *ctx, काष्ठा cxl_afu *afu, bool master)
अणु
	पूर्णांक i;

	ctx->afu = afu;
	ctx->master = master;
	ctx->pid = शून्य; /* Set in start work ioctl */
	mutex_init(&ctx->mapping_lock);
	ctx->mapping = शून्य;
	ctx->tidr = 0;
	ctx->assign_tidr = false;

	अगर (cxl_is_घातer8()) अणु
		spin_lock_init(&ctx->sste_lock);

		/*
		 * Allocate the segment table beक्रमe we put it in the IDR so that we
		 * can always access it when dereferenced from IDR. For the same
		 * reason, the segment table is only destroyed after the context is
		 * हटाओd from the IDR.  Access to this in the IOCTL is रक्षित by
		 * Linux fileप्रणाली semantics (can't IOCTL until खोलो is complete).
		 */
		i = cxl_alloc_sst(ctx);
		अगर (i)
			वापस i;
	पूर्ण

	INIT_WORK(&ctx->fault_work, cxl_handle_fault);

	init_रुकोqueue_head(&ctx->wq);
	spin_lock_init(&ctx->lock);

	ctx->irq_biपंचांगap = शून्य;
	ctx->pending_irq = false;
	ctx->pending_fault = false;
	ctx->pending_afu_err = false;

	INIT_LIST_HEAD(&ctx->irq_names);

	/*
	 * When we have to destroy all contexts in cxl_context_detach_all() we
	 * end up with afu_release_irqs() called from inside a
	 * idr_क्रम_each_entry(). Hence we need to make sure that anything
	 * dereferenced from this IDR is ok beक्रमe we allocate the IDR here.
	 * This clears out the IRQ ranges to ensure this.
	 */
	क्रम (i = 0; i < CXL_IRQ_RANGES; i++)
		ctx->irqs.range[i] = 0;

	mutex_init(&ctx->status_mutex);

	ctx->status = OPENED;

	/*
	 * Allocating IDR! We better make sure everything's setup that
	 * dereferences from it.
	 */
	mutex_lock(&afu->contexts_lock);
	idr_preload(GFP_KERNEL);
	i = idr_alloc(&ctx->afu->contexts_idr, ctx, 0,
		      ctx->afu->num_procs, GFP_NOWAIT);
	idr_preload_end();
	mutex_unlock(&afu->contexts_lock);
	अगर (i < 0)
		वापस i;

	ctx->pe = i;
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		ctx->elem = &ctx->afu->native->spa[i];
		ctx->बाह्यal_pe = ctx->pe;
	पूर्ण अन्यथा अणु
		ctx->बाह्यal_pe = -1; /* asचिन्हित when attaching */
	पूर्ण
	ctx->pe_inserted = false;

	/*
	 * take a ref on the afu so that it stays alive at-least till
	 * this context is reclaimed inside reclaim_ctx.
	 */
	cxl_afu_get(afu);
	वापस 0;
पूर्ण

व्योम cxl_context_set_mapping(काष्ठा cxl_context *ctx,
			काष्ठा address_space *mapping)
अणु
	mutex_lock(&ctx->mapping_lock);
	ctx->mapping = mapping;
	mutex_unlock(&ctx->mapping_lock);
पूर्ण

अटल vm_fault_t cxl_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा cxl_context *ctx = vma->vm_file->निजी_data;
	u64 area, offset;
	vm_fault_t ret;

	offset = vmf->pgoff << PAGE_SHIFT;

	pr_devel("%s: pe: %i address: 0x%lx offset: 0x%llx\n",
			__func__, ctx->pe, vmf->address, offset);

	अगर (ctx->afu->current_mode == CXL_MODE_DEDICATED) अणु
		area = ctx->afu->psn_phys;
		अगर (offset >= ctx->afu->adapter->ps_size)
			वापस VM_FAULT_SIGBUS;
	पूर्ण अन्यथा अणु
		area = ctx->psn_phys;
		अगर (offset >= ctx->psn_size)
			वापस VM_FAULT_SIGBUS;
	पूर्ण

	mutex_lock(&ctx->status_mutex);

	अगर (ctx->status != STARTED) अणु
		mutex_unlock(&ctx->status_mutex);
		pr_devel("%s: Context not started, failing problem state access\n", __func__);
		अगर (ctx->mmio_err_ff) अणु
			अगर (!ctx->ff_page) अणु
				ctx->ff_page = alloc_page(GFP_USER);
				अगर (!ctx->ff_page)
					वापस VM_FAULT_OOM;
				स_रखो(page_address(ctx->ff_page), 0xff, PAGE_SIZE);
			पूर्ण
			get_page(ctx->ff_page);
			vmf->page = ctx->ff_page;
			vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);
			वापस 0;
		पूर्ण
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	ret = vmf_insert_pfn(vma, vmf->address, (area + offset) >> PAGE_SHIFT);

	mutex_unlock(&ctx->status_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा cxl_mmap_vmops = अणु
	.fault = cxl_mmap_fault,
पूर्ण;

/*
 * Map a per-context mmio space पूर्णांकo the given vma.
 */
पूर्णांक cxl_context_iomap(काष्ठा cxl_context *ctx, काष्ठा vm_area_काष्ठा *vma)
अणु
	u64 start = vma->vm_pgoff << PAGE_SHIFT;
	u64 len = vma->vm_end - vma->vm_start;

	अगर (ctx->afu->current_mode == CXL_MODE_DEDICATED) अणु
		अगर (start + len > ctx->afu->adapter->ps_size)
			वापस -EINVAL;

		अगर (cxl_is_घातer9()) अणु
			/*
			 * Make sure there is a valid problem state
			 * area space क्रम this AFU.
			 */
			अगर (ctx->master && !ctx->afu->psa) अणु
				pr_devel("AFU doesn't support mmio space\n");
				वापस -EINVAL;
			पूर्ण

			/* Can't mmap until the AFU is enabled */
			अगर (!ctx->afu->enabled)
				वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (start + len > ctx->psn_size)
			वापस -EINVAL;

		/* Make sure there is a valid per process space क्रम this AFU */
		अगर ((ctx->master && !ctx->afu->psa) || (!ctx->afu->pp_psa)) अणु
			pr_devel("AFU doesn't support mmio space\n");
			वापस -EINVAL;
		पूर्ण

		/* Can't mmap until the AFU is enabled */
		अगर (!ctx->afu->enabled)
			वापस -EBUSY;
	पूर्ण

	pr_devel("%s: mmio physical: %llx pe: %i master:%i\n", __func__,
		 ctx->psn_phys, ctx->pe , ctx->master);

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &cxl_mmap_vmops;
	वापस 0;
पूर्ण

/*
 * Detach a context from the hardware. This disables पूर्णांकerrupts and करोesn't
 * वापस until all outstanding पूर्णांकerrupts क्रम this context have completed. The
 * hardware should no दीर्घer access *ctx after this has वापसed.
 */
पूर्णांक __detach_context(काष्ठा cxl_context *ctx)
अणु
	क्रमागत cxl_context_status status;

	mutex_lock(&ctx->status_mutex);
	status = ctx->status;
	ctx->status = CLOSED;
	mutex_unlock(&ctx->status_mutex);
	अगर (status != STARTED)
		वापस -EBUSY;

	/* Only warn अगर we detached जबतक the link was OK.
	 * If detach fails when hw is करोwn, we करोn't care.
	 */
	WARN_ON(cxl_ops->detach_process(ctx) &&
		cxl_ops->link_ok(ctx->afu->adapter, ctx->afu));
	flush_work(&ctx->fault_work); /* Only needed क्रम dedicated process */

	/*
	 * Wait until no further पूर्णांकerrupts are presented by the PSL
	 * क्रम this context.
	 */
	अगर (cxl_ops->irq_रुको)
		cxl_ops->irq_रुको(ctx);

	/* release the reference to the group leader and mm handling pid */
	put_pid(ctx->pid);

	cxl_ctx_put();

	/* Decrease the attached context count on the adapter */
	cxl_adapter_context_put(ctx->afu->adapter);

	/* Decrease the mm count on the context */
	cxl_context_mm_count_put(ctx);
	अगर (ctx->mm)
		mm_context_हटाओ_copro(ctx->mm);
	ctx->mm = शून्य;

	वापस 0;
पूर्ण

/*
 * Detach the given context from the AFU. This करोesn't actually
 * मुक्त the context but it should stop the context running in hardware
 * (ie. prevent this context from generating any further पूर्णांकerrupts
 * so that it can be मुक्तd).
 */
व्योम cxl_context_detach(काष्ठा cxl_context *ctx)
अणु
	पूर्णांक rc;

	rc = __detach_context(ctx);
	अगर (rc)
		वापस;

	afu_release_irqs(ctx, ctx);
	wake_up_all(&ctx->wq);
पूर्ण

/*
 * Detach all contexts on the given AFU.
 */
व्योम cxl_context_detach_all(काष्ठा cxl_afu *afu)
अणु
	काष्ठा cxl_context *ctx;
	पूर्णांक पंचांगp;

	mutex_lock(&afu->contexts_lock);
	idr_क्रम_each_entry(&afu->contexts_idr, ctx, पंचांगp) अणु
		/*
		 * Anything करोne in here needs to be setup beक्रमe the IDR is
		 * created and torn करोwn after the IDR हटाओd
		 */
		cxl_context_detach(ctx);

		/*
		 * We are क्रमce detaching - हटाओ any active PSA mappings so
		 * userspace cannot पूर्णांकerfere with the card अगर it comes back.
		 * Easiest way to exercise this is to unbind and rebind the
		 * driver via sysfs जबतक it is in use.
		 */
		mutex_lock(&ctx->mapping_lock);
		अगर (ctx->mapping)
			unmap_mapping_range(ctx->mapping, 0, 0, 1);
		mutex_unlock(&ctx->mapping_lock);
	पूर्ण
	mutex_unlock(&afu->contexts_lock);
पूर्ण

अटल व्योम reclaim_ctx(काष्ठा rcu_head *rcu)
अणु
	काष्ठा cxl_context *ctx = container_of(rcu, काष्ठा cxl_context, rcu);

	अगर (cxl_is_घातer8())
		मुक्त_page((u64)ctx->sstp);
	अगर (ctx->ff_page)
		__मुक्त_page(ctx->ff_page);
	ctx->sstp = शून्य;

	kमुक्त(ctx->irq_biपंचांगap);

	/* Drop ref to the afu device taken during cxl_context_init */
	cxl_afu_put(ctx->afu);

	kमुक्त(ctx);
पूर्ण

व्योम cxl_context_मुक्त(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->kernelapi && ctx->mapping)
		cxl_release_mapping(ctx);
	mutex_lock(&ctx->afu->contexts_lock);
	idr_हटाओ(&ctx->afu->contexts_idr, ctx->pe);
	mutex_unlock(&ctx->afu->contexts_lock);
	call_rcu(&ctx->rcu, reclaim_ctx);
पूर्ण

व्योम cxl_context_mm_count_get(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->mm)
		mmgrab(ctx->mm);
पूर्ण

व्योम cxl_context_mm_count_put(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->mm)
		mmdrop(ctx->mm);
पूर्ण
