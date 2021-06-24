<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/pid.h>
#समावेश <यंत्र/cputable.h>
#समावेश <misc/cxl-base.h>

#समावेश "cxl.h"
#समावेश "trace.h"

अटल पूर्णांक afu_irq_range_start(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		वापस 1;
	वापस 0;
पूर्ण

अटल irqवापस_t schedule_cxl_fault(काष्ठा cxl_context *ctx, u64 dsisr, u64 dar)
अणु
	ctx->dsisr = dsisr;
	ctx->dar = dar;
	schedule_work(&ctx->fault_work);
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t cxl_irq_psl9(पूर्णांक irq, काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *irq_info)
अणु
	u64 dsisr, dar;

	dsisr = irq_info->dsisr;
	dar = irq_info->dar;

	trace_cxl_psl9_irq(ctx, irq, dsisr, dar);

	pr_devel("CXL interrupt %i for afu pe: %i DSISR: %#llx DAR: %#llx\n", irq, ctx->pe, dsisr, dar);

	अगर (dsisr & CXL_PSL9_DSISR_An_TF) अणु
		pr_devel("CXL interrupt: Scheduling translation fault handling for later (pe: %i)\n", ctx->pe);
		वापस schedule_cxl_fault(ctx, dsisr, dar);
	पूर्ण

	अगर (dsisr & CXL_PSL9_DSISR_An_PE)
		वापस cxl_ops->handle_psl_slice_error(ctx, dsisr,
						irq_info->errstat);
	अगर (dsisr & CXL_PSL9_DSISR_An_AE) अणु
		pr_devel("CXL interrupt: AFU Error 0x%016llx\n", irq_info->afu_err);

		अगर (ctx->pending_afu_err) अणु
			/*
			 * This shouldn't happen - the PSL treats these errors
			 * as fatal and will have reset the AFU, so there's not
			 * much poपूर्णांक buffering multiple AFU errors.
			 * OTOH अगर we DO ever see a storm of these come in it's
			 * probably best that we log them somewhere:
			 */
			dev_err_ratelimited(&ctx->afu->dev, "CXL AFU Error undelivered to pe %i: 0x%016llx\n",
					    ctx->pe, irq_info->afu_err);
		पूर्ण अन्यथा अणु
			spin_lock(&ctx->lock);
			ctx->afu_err = irq_info->afu_err;
			ctx->pending_afu_err = 1;
			spin_unlock(&ctx->lock);

			wake_up_all(&ctx->wq);
		पूर्ण

		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_A, 0);
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (dsisr & CXL_PSL9_DSISR_An_OC)
		pr_devel("CXL interrupt: OS Context Warning\n");

	WARN(1, "Unhandled CXL PSL IRQ\n");
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t cxl_irq_psl8(पूर्णांक irq, काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *irq_info)
अणु
	u64 dsisr, dar;

	dsisr = irq_info->dsisr;
	dar = irq_info->dar;

	trace_cxl_psl_irq(ctx, irq, dsisr, dar);

	pr_devel("CXL interrupt %i for afu pe: %i DSISR: %#llx DAR: %#llx\n", irq, ctx->pe, dsisr, dar);

	अगर (dsisr & CXL_PSL_DSISR_An_DS) अणु
		/*
		 * We करोn't inherently need to sleep to handle this, but we करो
		 * need to get a ref to the task's mm, which we can't करो from
		 * irq context without the potential क्रम a deadlock since it
		 * takes the task_lock. An alternate option would be to keep a
		 * reference to the task's mm the entire समय it has cxl खोलो,
		 * but to करो that we need to solve the issue where we hold a
		 * ref to the mm, but the mm can hold a ref to the fd after an
		 * mmap preventing anything from being cleaned up.
		 */
		pr_devel("Scheduling segment miss handling for later pe: %i\n", ctx->pe);
		वापस schedule_cxl_fault(ctx, dsisr, dar);
	पूर्ण

	अगर (dsisr & CXL_PSL_DSISR_An_M)
		pr_devel("CXL interrupt: PTE not found\n");
	अगर (dsisr & CXL_PSL_DSISR_An_P)
		pr_devel("CXL interrupt: Storage protection violation\n");
	अगर (dsisr & CXL_PSL_DSISR_An_A)
		pr_devel("CXL interrupt: AFU lock access to write through or cache inhibited storage\n");
	अगर (dsisr & CXL_PSL_DSISR_An_S)
		pr_devel("CXL interrupt: Access was afu_wr or afu_zero\n");
	अगर (dsisr & CXL_PSL_DSISR_An_K)
		pr_devel("CXL interrupt: Access not permitted by virtual page class key protection\n");

	अगर (dsisr & CXL_PSL_DSISR_An_DM) अणु
		/*
		 * In some हालs we might be able to handle the fault
		 * immediately अगर hash_page would succeed, but we still need
		 * the task's mm, which as above we can't get without a lock
		 */
		pr_devel("Scheduling page fault handling for later pe: %i\n", ctx->pe);
		वापस schedule_cxl_fault(ctx, dsisr, dar);
	पूर्ण
	अगर (dsisr & CXL_PSL_DSISR_An_ST)
		WARN(1, "CXL interrupt: Segment Table PTE not found\n");
	अगर (dsisr & CXL_PSL_DSISR_An_UR)
		pr_devel("CXL interrupt: AURP PTE not found\n");
	अगर (dsisr & CXL_PSL_DSISR_An_PE)
		वापस cxl_ops->handle_psl_slice_error(ctx, dsisr,
						irq_info->errstat);
	अगर (dsisr & CXL_PSL_DSISR_An_AE) अणु
		pr_devel("CXL interrupt: AFU Error 0x%016llx\n", irq_info->afu_err);

		अगर (ctx->pending_afu_err) अणु
			/*
			 * This shouldn't happen - the PSL treats these errors
			 * as fatal and will have reset the AFU, so there's not
			 * much poपूर्णांक buffering multiple AFU errors.
			 * OTOH अगर we DO ever see a storm of these come in it's
			 * probably best that we log them somewhere:
			 */
			dev_err_ratelimited(&ctx->afu->dev, "CXL AFU Error "
					    "undelivered to pe %i: 0x%016llx\n",
					    ctx->pe, irq_info->afu_err);
		पूर्ण अन्यथा अणु
			spin_lock(&ctx->lock);
			ctx->afu_err = irq_info->afu_err;
			ctx->pending_afu_err = true;
			spin_unlock(&ctx->lock);

			wake_up_all(&ctx->wq);
		पूर्ण

		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_A, 0);
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (dsisr & CXL_PSL_DSISR_An_OC)
		pr_devel("CXL interrupt: OS Context Warning\n");

	WARN(1, "Unhandled CXL PSL IRQ\n");
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cxl_irq_afu(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl_context *ctx = data;
	irq_hw_number_t hwirq = irqd_to_hwirq(irq_get_irq_data(irq));
	पूर्णांक irq_off, afu_irq = 0;
	__u16 range;
	पूर्णांक r;

	/*
	 * Look क्रम the पूर्णांकerrupt number.
	 * On bare-metal, we know range 0 only contains the PSL
	 * पूर्णांकerrupt so we could start counting at range 1 and initialize
	 * afu_irq at 1.
	 * In a guest, range 0 also contains AFU पूर्णांकerrupts, so it must
	 * be counted क्रम. Thereक्रमe we initialize afu_irq at 0 to take पूर्णांकo
	 * account the PSL पूर्णांकerrupt.
	 *
	 * For code-पढ़ोability, it just seems easier to go over all
	 * the ranges on bare-metal and guest. The end result is the same.
	 */
	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		irq_off = hwirq - ctx->irqs.offset[r];
		range = ctx->irqs.range[r];
		अगर (irq_off >= 0 && irq_off < range) अणु
			afu_irq += irq_off;
			अवरोध;
		पूर्ण
		afu_irq += range;
	पूर्ण
	अगर (unlikely(r >= CXL_IRQ_RANGES)) अणु
		WARN(1, "Received AFU IRQ out of range for pe %i (virq %i hwirq %lx)\n",
		     ctx->pe, irq, hwirq);
		वापस IRQ_HANDLED;
	पूर्ण

	trace_cxl_afu_irq(ctx, afu_irq, irq, hwirq);
	pr_devel("Received AFU interrupt %i for pe: %i (virq %i hwirq %lx)\n",
	       afu_irq, ctx->pe, irq, hwirq);

	अगर (unlikely(!ctx->irq_biपंचांगap)) अणु
		WARN(1, "Received AFU IRQ for context with no IRQ bitmap\n");
		वापस IRQ_HANDLED;
	पूर्ण
	spin_lock(&ctx->lock);
	set_bit(afu_irq - 1, ctx->irq_biपंचांगap);
	ctx->pending_irq = true;
	spin_unlock(&ctx->lock);

	wake_up_all(&ctx->wq);

	वापस IRQ_HANDLED;
पूर्ण

अचिन्हित पूर्णांक cxl_map_irq(काष्ठा cxl *adapter, irq_hw_number_t hwirq,
			 irq_handler_t handler, व्योम *cookie, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक virq;
	पूर्णांक result;

	/* IRQ Doमुख्य? */
	virq = irq_create_mapping(शून्य, hwirq);
	अगर (!virq) अणु
		dev_warn(&adapter->dev, "cxl_map_irq: irq_create_mapping failed\n");
		वापस 0;
	पूर्ण

	अगर (cxl_ops->setup_irq)
		cxl_ops->setup_irq(adapter, hwirq, virq);

	pr_devel("hwirq %#lx mapped to virq %u\n", hwirq, virq);

	result = request_irq(virq, handler, 0, name, cookie);
	अगर (result) अणु
		dev_warn(&adapter->dev, "cxl_map_irq: request_irq failed: %i\n", result);
		वापस 0;
	पूर्ण

	वापस virq;
पूर्ण

व्योम cxl_unmap_irq(अचिन्हित पूर्णांक virq, व्योम *cookie)
अणु
	मुक्त_irq(virq, cookie);
पूर्ण

पूर्णांक cxl_रेजिस्टर_one_irq(काष्ठा cxl *adapter,
			irq_handler_t handler,
			व्योम *cookie,
			irq_hw_number_t *dest_hwirq,
			अचिन्हित पूर्णांक *dest_virq,
			स्थिर अक्षर *name)
अणु
	पूर्णांक hwirq, virq;

	अगर ((hwirq = cxl_ops->alloc_one_irq(adapter)) < 0)
		वापस hwirq;

	अगर (!(virq = cxl_map_irq(adapter, hwirq, handler, cookie, name)))
		जाओ err;

	*dest_hwirq = hwirq;
	*dest_virq = virq;

	वापस 0;

err:
	cxl_ops->release_one_irq(adapter, hwirq);
	वापस -ENOMEM;
पूर्ण

व्योम afu_irq_name_मुक्त(काष्ठा cxl_context *ctx)
अणु
	काष्ठा cxl_irq_name *irq_name, *पंचांगp;

	list_क्रम_each_entry_safe(irq_name, पंचांगp, &ctx->irq_names, list) अणु
		kमुक्त(irq_name->name);
		list_del(&irq_name->list);
		kमुक्त(irq_name);
	पूर्ण
पूर्ण

पूर्णांक afu_allocate_irqs(काष्ठा cxl_context *ctx, u32 count)
अणु
	पूर्णांक rc, r, i, j = 1;
	काष्ठा cxl_irq_name *irq_name;
	पूर्णांक alloc_count;

	/*
	 * In native mode, range 0 is reserved क्रम the multiplexed
	 * PSL पूर्णांकerrupt. It has been allocated when the AFU was initialized.
	 *
	 * In a guest, the PSL पूर्णांकerrupt is not mutliplexed, but per-context,
	 * and is the first पूर्णांकerrupt from range 0. It still needs to be
	 * allocated, so bump the count by one.
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		alloc_count = count;
	अन्यथा
		alloc_count = count + 1;

	अगर ((rc = cxl_ops->alloc_irq_ranges(&ctx->irqs, ctx->afu->adapter,
							alloc_count)))
		वापस rc;

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		/* Multiplexed PSL Interrupt */
		ctx->irqs.offset[0] = ctx->afu->native->psl_hwirq;
		ctx->irqs.range[0] = 1;
	पूर्ण

	ctx->irq_count = count;
	ctx->irq_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(count),
				  माप(*ctx->irq_biपंचांगap), GFP_KERNEL);
	अगर (!ctx->irq_biपंचांगap)
		जाओ out;

	/*
	 * Allocate names first.  If any fail, bail out beक्रमe allocating
	 * actual hardware IRQs.
	 */
	क्रम (r = afu_irq_range_start(); r < CXL_IRQ_RANGES; r++) अणु
		क्रम (i = 0; i < ctx->irqs.range[r]; i++) अणु
			irq_name = kदो_स्मृति(माप(काष्ठा cxl_irq_name),
					   GFP_KERNEL);
			अगर (!irq_name)
				जाओ out;
			irq_name->name = kaप्र_लिखो(GFP_KERNEL, "cxl-%s-pe%i-%i",
						   dev_name(&ctx->afu->dev),
						   ctx->pe, j);
			अगर (!irq_name->name) अणु
				kमुक्त(irq_name);
				जाओ out;
			पूर्ण
			/* Add to tail so next look get the correct order */
			list_add_tail(&irq_name->list, &ctx->irq_names);
			j++;
		पूर्ण
	पूर्ण
	वापस 0;

out:
	cxl_ops->release_irq_ranges(&ctx->irqs, ctx->afu->adapter);
	afu_irq_name_मुक्त(ctx);
	वापस -ENOMEM;
पूर्ण

अटल व्योम afu_रेजिस्टर_hwirqs(काष्ठा cxl_context *ctx)
अणु
	irq_hw_number_t hwirq;
	काष्ठा cxl_irq_name *irq_name;
	पूर्णांक r, i;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *data);

	/* We've allocated all memory now, so let's करो the irq allocations */
	irq_name = list_first_entry(&ctx->irq_names, काष्ठा cxl_irq_name, list);
	क्रम (r = afu_irq_range_start(); r < CXL_IRQ_RANGES; r++) अणु
		hwirq = ctx->irqs.offset[r];
		क्रम (i = 0; i < ctx->irqs.range[r]; hwirq++, i++) अणु
			अगर (r == 0 && i == 0)
				/*
				 * The very first पूर्णांकerrupt of range 0 is
				 * always the PSL पूर्णांकerrupt, but we only
				 * need to connect a handler क्रम guests,
				 * because there's one PSL पूर्णांकerrupt per
				 * context.
				 * On bare-metal, the PSL पूर्णांकerrupt is
				 * multiplexed and was setup when the AFU
				 * was configured.
				 */
				handler = cxl_ops->psl_पूर्णांकerrupt;
			अन्यथा
				handler = cxl_irq_afu;
			cxl_map_irq(ctx->afu->adapter, hwirq, handler, ctx,
				irq_name->name);
			irq_name = list_next_entry(irq_name, list);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक afu_रेजिस्टर_irqs(काष्ठा cxl_context *ctx, u32 count)
अणु
	पूर्णांक rc;

	rc = afu_allocate_irqs(ctx, count);
	अगर (rc)
		वापस rc;

	afu_रेजिस्टर_hwirqs(ctx);
	वापस 0;
पूर्ण

व्योम afu_release_irqs(काष्ठा cxl_context *ctx, व्योम *cookie)
अणु
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक virq;
	पूर्णांक r, i;

	क्रम (r = afu_irq_range_start(); r < CXL_IRQ_RANGES; r++) अणु
		hwirq = ctx->irqs.offset[r];
		क्रम (i = 0; i < ctx->irqs.range[r]; hwirq++, i++) अणु
			virq = irq_find_mapping(शून्य, hwirq);
			अगर (virq)
				cxl_unmap_irq(virq, cookie);
		पूर्ण
	पूर्ण

	afu_irq_name_मुक्त(ctx);
	cxl_ops->release_irq_ranges(&ctx->irqs, ctx->afu->adapter);

	ctx->irq_count = 0;
पूर्ण

व्योम cxl_afu_decode_psl_serr(काष्ठा cxl_afu *afu, u64 serr)
अणु
	dev_crit(&afu->dev,
		 "PSL Slice error received. Check AFU for root cause.\n");
	dev_crit(&afu->dev, "PSL_SERR_An: 0x%016llx\n", serr);
	अगर (serr & CXL_PSL_SERR_An_afuto)
		dev_crit(&afu->dev, "AFU MMIO Timeout\n");
	अगर (serr & CXL_PSL_SERR_An_afudis)
		dev_crit(&afu->dev,
			 "MMIO targeted Accelerator that was not enabled\n");
	अगर (serr & CXL_PSL_SERR_An_afuov)
		dev_crit(&afu->dev, "AFU CTAG Overflow\n");
	अगर (serr & CXL_PSL_SERR_An_badsrc)
		dev_crit(&afu->dev, "Bad Interrupt Source\n");
	अगर (serr & CXL_PSL_SERR_An_badctx)
		dev_crit(&afu->dev, "Bad Context Handle\n");
	अगर (serr & CXL_PSL_SERR_An_llcmdis)
		dev_crit(&afu->dev, "LLCMD to Disabled AFU\n");
	अगर (serr & CXL_PSL_SERR_An_llcmdto)
		dev_crit(&afu->dev, "LLCMD Timeout to AFU\n");
	अगर (serr & CXL_PSL_SERR_An_afupar)
		dev_crit(&afu->dev, "AFU MMIO Parity Error\n");
	अगर (serr & CXL_PSL_SERR_An_afudup)
		dev_crit(&afu->dev, "AFU MMIO Duplicate CTAG Error\n");
	अगर (serr & CXL_PSL_SERR_An_AE)
		dev_crit(&afu->dev,
			 "AFU asserted JDONE with JERROR in AFU Directed Mode\n");
पूर्ण
