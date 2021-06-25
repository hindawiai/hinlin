<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Low-level SPU handling
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>

#समावेश "spufs.h"

/**
 * Handle an SPE event, depending on context SPU_CREATE_EVENTS_ENABLED flag.
 *
 * If the context was created with events, we just set the वापस event.
 * Otherwise, send an appropriate संकेत to the process.
 */
अटल व्योम spufs_handle_event(काष्ठा spu_context *ctx,
				अचिन्हित दीर्घ ea, पूर्णांक type)
अणु
	अगर (ctx->flags & SPU_CREATE_EVENTS_ENABLED) अणु
		ctx->event_वापस |= type;
		wake_up_all(&ctx->stop_wq);
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल SPE_EVENT_INVALID_DMA:
		क्रमce_sig_fault(SIGBUS, BUS_OBJERR, शून्य);
		अवरोध;
	हाल SPE_EVENT_SPE_DATA_STORAGE:
		ctx->ops->restart_dma(ctx);
		क्रमce_sig_fault(संक_अंश, SEGV_ACCERR, (व्योम __user *)ea);
		अवरोध;
	हाल SPE_EVENT_DMA_ALIGNMENT:
		/* DAR isn't set क्रम an alignment fault :( */
		क्रमce_sig_fault(SIGBUS, BUS_ADRALN, शून्य);
		अवरोध;
	हाल SPE_EVENT_SPE_ERROR:
		क्रमce_sig_fault(
			संक_अवैध, ILL_ILLOPC,
			(व्योम __user *)(अचिन्हित दीर्घ)
			ctx->ops->npc_पढ़ो(ctx) - 4);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक spufs_handle_class0(काष्ठा spu_context *ctx)
अणु
	अचिन्हित दीर्घ stat = ctx->csa.class_0_pending & CLASS0_INTR_MASK;

	अगर (likely(!stat))
		वापस 0;

	अगर (stat & CLASS0_DMA_ALIGNMENT_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_DMA_ALIGNMENT);

	अगर (stat & CLASS0_INVALID_DMA_COMMAND_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_INVALID_DMA);

	अगर (stat & CLASS0_SPU_ERROR_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_SPE_ERROR);

	ctx->csa.class_0_pending = 0;

	वापस -EIO;
पूर्ण

/*
 * bottom half handler क्रम page faults, we can't करो this from
 * पूर्णांकerrupt context, since we might need to sleep.
 * we also need to give up the mutex so we can get scheduled
 * out जबतक रुकोing क्रम the backing store.
 *
 * TODO: try calling hash_page from the पूर्णांकerrupt handler first
 *       in order to speed up the easy हाल.
 */
पूर्णांक spufs_handle_class1(काष्ठा spu_context *ctx)
अणु
	u64 ea, dsisr, access;
	अचिन्हित दीर्घ flags;
	vm_fault_t flt = 0;
	पूर्णांक ret;

	/*
	 * dar and dsisr get passed from the रेजिस्टरs
	 * to the spu_context, to this function, but not
	 * back to the spu अगर it माला_लो scheduled again.
	 *
	 * अगर we करोn't handle the fault क्रम a saved context
	 * in समय, we can still expect to get the same fault
	 * the immediately after the context restore.
	 */
	ea = ctx->csa.class_1_dar;
	dsisr = ctx->csa.class_1_dsisr;

	अगर (!(dsisr & (MFC_DSISR_PTE_NOT_FOUND | MFC_DSISR_ACCESS_DENIED)))
		वापस 0;

	spuctx_चयन_state(ctx, SPU_UTIL_IOWAIT);

	pr_debug("ctx %p: ea %016llx, dsisr %016llx state %d\n", ctx, ea,
		dsisr, ctx->state);

	ctx->stats.hash_flt++;
	अगर (ctx->state == SPU_STATE_RUNNABLE)
		ctx->spu->stats.hash_flt++;

	/* we must not hold the lock when entering copro_handle_mm_fault */
	spu_release(ctx);

	access = (_PAGE_PRESENT | _PAGE_READ);
	access |= (dsisr & MFC_DSISR_ACCESS_PUT) ? _PAGE_WRITE : 0UL;
	local_irq_save(flags);
	ret = hash_page(ea, access, 0x300, dsisr);
	local_irq_restore(flags);

	/* hashing failed, so try the actual fault handler */
	अगर (ret)
		ret = copro_handle_mm_fault(current->mm, ea, dsisr, &flt);

	/*
	 * This is nasty: we need the state_mutex क्रम all the bookkeeping even
	 * अगर the syscall was पूर्णांकerrupted by a संकेत. ewww.
	 */
	mutex_lock(&ctx->state_mutex);

	/*
	 * Clear dsisr under ctxt lock after handling the fault, so that
	 * समय slicing will not preempt the context जबतक the page fault
	 * handler is running. Context चयन code हटाओs mappings.
	 */
	ctx->csa.class_1_dar = ctx->csa.class_1_dsisr = 0;

	/*
	 * If we handled the fault successfully and are in runnable
	 * state, restart the DMA.
	 * In हाल of unhandled error report the problem to user space.
	 */
	अगर (!ret) अणु
		अगर (flt & VM_FAULT_MAJOR)
			ctx->stats.maj_flt++;
		अन्यथा
			ctx->stats.min_flt++;
		अगर (ctx->state == SPU_STATE_RUNNABLE) अणु
			अगर (flt & VM_FAULT_MAJOR)
				ctx->spu->stats.maj_flt++;
			अन्यथा
				ctx->spu->stats.min_flt++;
		पूर्ण

		अगर (ctx->spu)
			ctx->ops->restart_dma(ctx);
	पूर्ण अन्यथा
		spufs_handle_event(ctx, ea, SPE_EVENT_SPE_DATA_STORAGE);

	spuctx_चयन_state(ctx, SPU_UTIL_SYSTEM);
	वापस ret;
पूर्ण
