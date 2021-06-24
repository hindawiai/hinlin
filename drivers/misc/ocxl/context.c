<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/sched/mm.h>
#समावेश "trace.h"
#समावेश "ocxl_internal.h"

पूर्णांक ocxl_context_alloc(काष्ठा ocxl_context **context, काष्ठा ocxl_afu *afu,
		काष्ठा address_space *mapping)
अणु
	पूर्णांक pasid;
	काष्ठा ocxl_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->afu = afu;
	mutex_lock(&afu->contexts_lock);
	pasid = idr_alloc(&afu->contexts_idr, ctx, afu->pasid_base,
			afu->pasid_base + afu->pasid_max, GFP_KERNEL);
	अगर (pasid < 0) अणु
		mutex_unlock(&afu->contexts_lock);
		kमुक्त(ctx);
		वापस pasid;
	पूर्ण
	afu->pasid_count++;
	mutex_unlock(&afu->contexts_lock);

	ctx->pasid = pasid;
	ctx->status = OPENED;
	mutex_init(&ctx->status_mutex);
	ctx->mapping = mapping;
	mutex_init(&ctx->mapping_lock);
	init_रुकोqueue_head(&ctx->events_wq);
	mutex_init(&ctx->xsl_error_lock);
	mutex_init(&ctx->irq_lock);
	idr_init(&ctx->irq_idr);
	ctx->tidr = 0;

	/*
	 * Keep a reference on the AFU to make sure it's valid क्रम the
	 * duration of the lअगरe of the context
	 */
	ocxl_afu_get(afu);
	*context = ctx;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_context_alloc);

/*
 * Callback क्रम when a translation fault triggers an error
 * data:	a poपूर्णांकer to the context which triggered the fault
 * addr:	the address that triggered the error
 * dsisr:	the value of the PPC64 dsisr रेजिस्टर
 */
अटल व्योम xsl_fault_error(व्योम *data, u64 addr, u64 dsisr)
अणु
	काष्ठा ocxl_context *ctx = (काष्ठा ocxl_context *) data;

	mutex_lock(&ctx->xsl_error_lock);
	ctx->xsl_error.addr = addr;
	ctx->xsl_error.dsisr = dsisr;
	ctx->xsl_error.count++;
	mutex_unlock(&ctx->xsl_error_lock);

	wake_up_all(&ctx->events_wq);
पूर्ण

पूर्णांक ocxl_context_attach(काष्ठा ocxl_context *ctx, u64 amr, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ pidr = 0;
	काष्ठा pci_dev *dev;

	// Locks both status & tidr
	mutex_lock(&ctx->status_mutex);
	अगर (ctx->status != OPENED) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर (mm)
		pidr = mm->context.id;

	dev = to_pci_dev(ctx->afu->fn->dev.parent);
	rc = ocxl_link_add_pe(ctx->afu->fn->link, ctx->pasid, pidr, ctx->tidr,
			      amr, pci_dev_id(dev), mm, xsl_fault_error, ctx);
	अगर (rc)
		जाओ out;

	ctx->status = ATTACHED;
out:
	mutex_unlock(&ctx->status_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_context_attach);

अटल vm_fault_t map_afu_irq(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		u64 offset, काष्ठा ocxl_context *ctx)
अणु
	u64 trigger_addr;
	पूर्णांक irq_id = ocxl_irq_offset_to_id(ctx, offset);

	trigger_addr = ocxl_afu_irq_get_addr(ctx, irq_id);
	अगर (!trigger_addr)
		वापस VM_FAULT_SIGBUS;

	वापस vmf_insert_pfn(vma, address, trigger_addr >> PAGE_SHIFT);
पूर्ण

अटल vm_fault_t map_pp_mmio(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		u64 offset, काष्ठा ocxl_context *ctx)
अणु
	u64 pp_mmio_addr;
	पूर्णांक pasid_off;
	vm_fault_t ret;

	अगर (offset >= ctx->afu->config.pp_mmio_stride)
		वापस VM_FAULT_SIGBUS;

	mutex_lock(&ctx->status_mutex);
	अगर (ctx->status != ATTACHED) अणु
		mutex_unlock(&ctx->status_mutex);
		pr_debug("%s: Context not attached, failing mmio mmap\n",
			__func__);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	pasid_off = ctx->pasid - ctx->afu->pasid_base;
	pp_mmio_addr = ctx->afu->pp_mmio_start +
		pasid_off * ctx->afu->config.pp_mmio_stride +
		offset;

	ret = vmf_insert_pfn(vma, address, pp_mmio_addr >> PAGE_SHIFT);
	mutex_unlock(&ctx->status_mutex);
	वापस ret;
पूर्ण

अटल vm_fault_t ocxl_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा ocxl_context *ctx = vma->vm_file->निजी_data;
	u64 offset;
	vm_fault_t ret;

	offset = vmf->pgoff << PAGE_SHIFT;
	pr_debug("%s: pasid %d address 0x%lx offset 0x%llx\n", __func__,
		ctx->pasid, vmf->address, offset);

	अगर (offset < ctx->afu->irq_base_offset)
		ret = map_pp_mmio(vma, vmf->address, offset, ctx);
	अन्यथा
		ret = map_afu_irq(vma, vmf->address, offset, ctx);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ocxl_vmops = अणु
	.fault = ocxl_mmap_fault,
पूर्ण;

अटल पूर्णांक check_mmap_afu_irq(काष्ठा ocxl_context *ctx,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक irq_id = ocxl_irq_offset_to_id(ctx, vma->vm_pgoff << PAGE_SHIFT);

	/* only one page */
	अगर (vma_pages(vma) != 1)
		वापस -EINVAL;

	/* check offset validty */
	अगर (!ocxl_afu_irq_get_addr(ctx, irq_id))
		वापस -EINVAL;

	/*
	 * trigger page should only be accessible in ग_लिखो mode.
	 *
	 * It's a bit theoretical, as a page mmaped with only
	 * PROT_WRITE is currently पढ़ोable, but it करोesn't hurt.
	 */
	अगर ((vma->vm_flags & VM_READ) || (vma->vm_flags & VM_EXEC) ||
		!(vma->vm_flags & VM_WRITE))
		वापस -EINVAL;
	vma->vm_flags &= ~(VM_MAYREAD | VM_MAYEXEC);
	वापस 0;
पूर्ण

अटल पूर्णांक check_mmap_mmio(काष्ठा ocxl_context *ctx,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर ((vma_pages(vma) + vma->vm_pgoff) >
		(ctx->afu->config.pp_mmio_stride >> PAGE_SHIFT))
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक ocxl_context_mmap(काष्ठा ocxl_context *ctx, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक rc;

	अगर ((vma->vm_pgoff << PAGE_SHIFT) < ctx->afu->irq_base_offset)
		rc = check_mmap_mmio(ctx, vma);
	अन्यथा
		rc = check_mmap_afu_irq(ctx, vma);
	अगर (rc)
		वापस rc;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &ocxl_vmops;
	वापस 0;
पूर्ण

पूर्णांक ocxl_context_detach(काष्ठा ocxl_context *ctx)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक afu_control_pos;
	क्रमागत ocxl_context_status status;
	पूर्णांक rc;

	mutex_lock(&ctx->status_mutex);
	status = ctx->status;
	ctx->status = CLOSED;
	mutex_unlock(&ctx->status_mutex);
	अगर (status != ATTACHED)
		वापस 0;

	dev = to_pci_dev(ctx->afu->fn->dev.parent);
	afu_control_pos = ctx->afu->config.dvsec_afu_control_pos;

	mutex_lock(&ctx->afu->afu_control_lock);
	rc = ocxl_config_terminate_pasid(dev, afu_control_pos, ctx->pasid);
	mutex_unlock(&ctx->afu->afu_control_lock);
	trace_ocxl_terminate_pasid(ctx->pasid, rc);
	अगर (rc) अणु
		/*
		 * If we समयout रुकोing क्रम the AFU to terminate the
		 * pasid, then it's dangerous to clean up the Process
		 * Element entry in the SPA, as it may be referenced
		 * in the future by the AFU. In which हाल, we would
		 * checkstop because of an invalid PE access (FIR
		 * रेजिस्टर 2, bit 42). So leave the PE
		 * defined. Caller shouldn't मुक्त the context so that
		 * PASID reमुख्यs allocated.
		 *
		 * A link reset will be required to cleanup the AFU
		 * and the SPA.
		 */
		अगर (rc == -EBUSY)
			वापस rc;
	पूर्ण
	rc = ocxl_link_हटाओ_pe(ctx->afu->fn->link, ctx->pasid);
	अगर (rc) अणु
		dev_warn(&dev->dev,
			"Couldn't remove PE entry cleanly: %d\n", rc);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_context_detach);

व्योम ocxl_context_detach_all(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_context *ctx;
	पूर्णांक पंचांगp;

	mutex_lock(&afu->contexts_lock);
	idr_क्रम_each_entry(&afu->contexts_idr, ctx, पंचांगp) अणु
		ocxl_context_detach(ctx);
		/*
		 * We are क्रमce detaching - हटाओ any active mmio
		 * mappings so userspace cannot पूर्णांकerfere with the
		 * card अगर it comes back.  Easiest way to exercise
		 * this is to unbind and rebind the driver via sysfs
		 * जबतक it is in use.
		 */
		mutex_lock(&ctx->mapping_lock);
		अगर (ctx->mapping)
			unmap_mapping_range(ctx->mapping, 0, 0, 1);
		mutex_unlock(&ctx->mapping_lock);
	पूर्ण
	mutex_unlock(&afu->contexts_lock);
पूर्ण

व्योम ocxl_context_मुक्त(काष्ठा ocxl_context *ctx)
अणु
	mutex_lock(&ctx->afu->contexts_lock);
	ctx->afu->pasid_count--;
	idr_हटाओ(&ctx->afu->contexts_idr, ctx->pasid);
	mutex_unlock(&ctx->afu->contexts_lock);

	ocxl_afu_irq_मुक्त_all(ctx);
	idr_destroy(&ctx->irq_idr);
	/* reference to the AFU taken in ocxl_context_alloc() */
	ocxl_afu_put(ctx->afu);
	kमुक्त(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_context_मुक्त);
