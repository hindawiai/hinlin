<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा DEBUG

#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unistd.h>

#समावेश "spufs.h"

/* पूर्णांकerrupt-level stop callback function. */
व्योम spufs_stop_callback(काष्ठा spu *spu, पूर्णांक irq)
अणु
	काष्ठा spu_context *ctx = spu->ctx;

	/*
	 * It should be impossible to preempt a context जबतक an exception
	 * is being processed, since the context चयन code is specially
	 * coded to deal with पूर्णांकerrupts ... But, just in हाल, sanity check
	 * the context poपूर्णांकer.  It is OK to वापस करोing nothing since
	 * the exception will be regenerated when the context is resumed.
	 */
	अगर (ctx) अणु
		/* Copy exception arguments पूर्णांकo module specअगरic काष्ठाure */
		चयन(irq) अणु
		हाल 0 :
			ctx->csa.class_0_pending = spu->class_0_pending;
			ctx->csa.class_0_dar = spu->class_0_dar;
			अवरोध;
		हाल 1 :
			ctx->csa.class_1_dsisr = spu->class_1_dsisr;
			ctx->csa.class_1_dar = spu->class_1_dar;
			अवरोध;
		हाल 2 :
			अवरोध;
		पूर्ण

		/* ensure that the exception status has hit memory beक्रमe a
		 * thपढ़ो रुकोing on the context's stop queue is woken */
		smp_wmb();

		wake_up_all(&ctx->stop_wq);
	पूर्ण
पूर्ण

पूर्णांक spu_stopped(काष्ठा spu_context *ctx, u32 *stat)
अणु
	u64 dsisr;
	u32 stopped;

	stopped = SPU_STATUS_INVALID_INSTR | SPU_STATUS_SINGLE_STEP |
		SPU_STATUS_STOPPED_BY_HALT | SPU_STATUS_STOPPED_BY_STOP;

top:
	*stat = ctx->ops->status_पढ़ो(ctx);
	अगर (*stat & stopped) अणु
		/*
		 * If the spu hasn't finished stopping, we need to
		 * re-पढ़ो the रेजिस्टर to get the stopped value.
		 */
		अगर (*stat & SPU_STATUS_RUNNING)
			जाओ top;
		वापस 1;
	पूर्ण

	अगर (test_bit(SPU_SCHED_NOTIFY_ACTIVE, &ctx->sched_flags))
		वापस 1;

	dsisr = ctx->csa.class_1_dsisr;
	अगर (dsisr & (MFC_DSISR_PTE_NOT_FOUND | MFC_DSISR_ACCESS_DENIED))
		वापस 1;

	अगर (ctx->csa.class_0_pending)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक spu_setup_isolated(काष्ठा spu_context *ctx)
अणु
	पूर्णांक ret;
	u64 __iomem *mfc_cntl;
	u64 sr1;
	u32 status;
	अचिन्हित दीर्घ समयout;
	स्थिर u32 status_loading = SPU_STATUS_RUNNING
		| SPU_STATUS_ISOLATED_STATE | SPU_STATUS_ISOLATED_LOAD_STATUS;

	ret = -ENODEV;
	अगर (!isolated_loader)
		जाओ out;

	/*
	 * We need to exclude userspace access to the context.
	 *
	 * To protect against memory access we invalidate all ptes
	 * and make sure the pagefault handlers block on the mutex.
	 */
	spu_unmap_mappings(ctx);

	mfc_cntl = &ctx->spu->priv2->mfc_control_RW;

	/* purge the MFC DMA queue to ensure no spurious accesses beक्रमe we
	 * enter kernel mode */
	समयout = jअगरfies + HZ;
	out_be64(mfc_cntl, MFC_CNTL_PURGE_DMA_REQUEST);
	जबतक ((in_be64(mfc_cntl) & MFC_CNTL_PURGE_DMA_STATUS_MASK)
			!= MFC_CNTL_PURGE_DMA_COMPLETE) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout flushing MFC DMA queue\n",
					__func__);
			ret = -EIO;
			जाओ out;
		पूर्ण
		cond_resched();
	पूर्ण

	/* clear purge status */
	out_be64(mfc_cntl, 0);

	/* put the SPE in kernel mode to allow access to the loader */
	sr1 = spu_mfc_sr1_get(ctx->spu);
	sr1 &= ~MFC_STATE1_PROBLEM_STATE_MASK;
	spu_mfc_sr1_set(ctx->spu, sr1);

	/* start the loader */
	ctx->ops->संकेत1_ग_लिखो(ctx, (अचिन्हित दीर्घ)isolated_loader >> 32);
	ctx->ops->संकेत2_ग_लिखो(ctx,
			(अचिन्हित दीर्घ)isolated_loader & 0xffffffff);

	ctx->ops->runcntl_ग_लिखो(ctx,
			SPU_RUNCNTL_RUNNABLE | SPU_RUNCNTL_ISOLATE);

	ret = 0;
	समयout = jअगरfies + HZ;
	जबतक (((status = ctx->ops->status_पढ़ो(ctx)) & status_loading) ==
				status_loading) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout waiting for loader\n",
					__func__);
			ret = -EIO;
			जाओ out_drop_priv;
		पूर्ण
		cond_resched();
	पूर्ण

	अगर (!(status & SPU_STATUS_RUNNING)) अणु
		/* If isolated LOAD has failed: run SPU, we will get a stop-and
		 * संकेत later. */
		pr_debug("%s: isolated LOAD failed\n", __func__);
		ctx->ops->runcntl_ग_लिखो(ctx, SPU_RUNCNTL_RUNNABLE);
		ret = -EACCES;
		जाओ out_drop_priv;
	पूर्ण

	अगर (!(status & SPU_STATUS_ISOLATED_STATE)) अणु
		/* This isn't allowed by the CBEA, but check anyway */
		pr_debug("%s: SPU fell out of isolated mode?\n", __func__);
		ctx->ops->runcntl_ग_लिखो(ctx, SPU_RUNCNTL_STOP);
		ret = -EINVAL;
		जाओ out_drop_priv;
	पूर्ण

out_drop_priv:
	/* Finished accessing the loader. Drop kernel mode */
	sr1 |= MFC_STATE1_PROBLEM_STATE_MASK;
	spu_mfc_sr1_set(ctx->spu, sr1);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक spu_run_init(काष्ठा spu_context *ctx, u32 *npc)
अणु
	अचिन्हित दीर्घ runcntl = SPU_RUNCNTL_RUNNABLE;
	पूर्णांक ret;

	spuctx_चयन_state(ctx, SPU_UTIL_SYSTEM);

	/*
	 * NOSCHED is synchronous scheduling with respect to the caller.
	 * The caller रुकोs क्रम the context to be loaded.
	 */
	अगर (ctx->flags & SPU_CREATE_NOSCHED) अणु
		अगर (ctx->state == SPU_STATE_SAVED) अणु
			ret = spu_activate(ctx, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Apply special setup as required.
	 */
	अगर (ctx->flags & SPU_CREATE_ISOLATE) अणु
		अगर (!(ctx->ops->status_पढ़ो(ctx) & SPU_STATUS_ISOLATED_STATE)) अणु
			ret = spu_setup_isolated(ctx);
			अगर (ret)
				वापस ret;
		पूर्ण

		/*
		 * If userspace has set the runcntrl रेजिस्टर (eg, to
		 * issue an isolated निकास), we need to re-set it here
		 */
		runcntl = ctx->ops->runcntl_पढ़ो(ctx) &
			(SPU_RUNCNTL_RUNNABLE | SPU_RUNCNTL_ISOLATE);
		अगर (runcntl == 0)
			runcntl = SPU_RUNCNTL_RUNNABLE;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ privcntl;

		अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
			privcntl = SPU_PRIVCNTL_MODE_SINGLE_STEP;
		अन्यथा
			privcntl = SPU_PRIVCNTL_MODE_NORMAL;

		ctx->ops->privcntl_ग_लिखो(ctx, privcntl);
		ctx->ops->npc_ग_लिखो(ctx, *npc);
	पूर्ण

	ctx->ops->runcntl_ग_लिखो(ctx, runcntl);

	अगर (ctx->flags & SPU_CREATE_NOSCHED) अणु
		spuctx_चयन_state(ctx, SPU_UTIL_USER);
	पूर्ण अन्यथा अणु

		अगर (ctx->state == SPU_STATE_SAVED) अणु
			ret = spu_activate(ctx, 0);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			spuctx_चयन_state(ctx, SPU_UTIL_USER);
		पूर्ण
	पूर्ण

	set_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक spu_run_fini(काष्ठा spu_context *ctx, u32 *npc,
			       u32 *status)
अणु
	पूर्णांक ret = 0;

	spu_del_from_rq(ctx);

	*status = ctx->ops->status_पढ़ो(ctx);
	*npc = ctx->ops->npc_पढ़ो(ctx);

	spuctx_चयन_state(ctx, SPU_UTIL_IDLE_LOADED);
	clear_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags);
	spu_चयन_log_notअगरy(शून्य, ctx, SWITCH_LOG_EXIT, *status);
	spu_release(ctx);

	अगर (संकेत_pending(current))
		ret = -ERESTARTSYS;

	वापस ret;
पूर्ण

/*
 * SPU syscall restarting is tricky because we violate the basic
 * assumption that the संकेत handler is running on the पूर्णांकerrupted
 * thपढ़ो. Here instead, the handler runs on PowerPC user space code,
 * जबतक the syscall was called from the SPU.
 * This means we can only करो a very rough approximation of POSIX
 * संकेत semantics.
 */
अटल पूर्णांक spu_handle_restartsys(काष्ठा spu_context *ctx, दीर्घ *spu_ret,
			  अचिन्हित पूर्णांक *npc)
अणु
	पूर्णांक ret;

	चयन (*spu_ret) अणु
	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
		/*
		 * Enter the regular syscall restarting क्रम
		 * sys_spu_run, then restart the SPU syscall
		 * callback.
		 */
		*npc -= 8;
		ret = -ERESTARTSYS;
		अवरोध;
	हाल -ERESTARTNOHAND:
	हाल -ERESTART_RESTARTBLOCK:
		/*
		 * Restart block is too hard क्रम now, just वापस -EINTR
		 * to the SPU.
		 * ERESTARTNOHAND comes from sys_छोड़ो, we also वापस
		 * -EINTR from there.
		 * Assume that we need to be restarted ourselves though.
		 */
		*spu_ret = -EINTR;
		ret = -ERESTARTSYS;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unexpected return code %ld\n",
			__func__, *spu_ret);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक spu_process_callback(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_syscall_block s;
	u32 ls_poपूर्णांकer, npc;
	व्योम __iomem *ls;
	दीर्घ spu_ret;
	पूर्णांक ret;

	/* get syscall block from local store */
	npc = ctx->ops->npc_पढ़ो(ctx) & ~3;
	ls = (व्योम __iomem *)ctx->ops->get_ls(ctx);
	ls_poपूर्णांकer = in_be32(ls + npc);
	अगर (ls_poपूर्णांकer > (LS_SIZE - माप(s)))
		वापस -EFAULT;
	स_नकल_fromio(&s, ls + ls_poपूर्णांकer, माप(s));

	/* करो actual syscall without pinning the spu */
	ret = 0;
	spu_ret = -ENOSYS;
	npc += 4;

	अगर (s.nr_ret < NR_syscalls) अणु
		spu_release(ctx);
		/* करो actual प्रणाली call from here */
		spu_ret = spu_sys_callback(&s);
		अगर (spu_ret <= -ERESTARTSYS) अणु
			ret = spu_handle_restartsys(ctx, &spu_ret, &npc);
		पूर्ण
		mutex_lock(&ctx->state_mutex);
		अगर (ret == -ERESTARTSYS)
			वापस ret;
	पूर्ण

	/* need to re-get the ls, as it may have changed when we released the
	 * spu */
	ls = (व्योम __iomem *)ctx->ops->get_ls(ctx);

	/* ग_लिखो result, jump over indirect poपूर्णांकer */
	स_नकल_toio(ls + ls_poपूर्णांकer, &spu_ret, माप(spu_ret));
	ctx->ops->npc_ग_लिखो(ctx, npc);
	ctx->ops->runcntl_ग_लिखो(ctx, SPU_RUNCNTL_RUNNABLE);
	वापस ret;
पूर्ण

दीर्घ spufs_run_spu(काष्ठा spu_context *ctx, u32 *npc, u32 *event)
अणु
	पूर्णांक ret;
	u32 status;

	अगर (mutex_lock_पूर्णांकerruptible(&ctx->run_mutex))
		वापस -ERESTARTSYS;

	ctx->event_वापस = 0;

	ret = spu_acquire(ctx);
	अगर (ret)
		जाओ out_unlock;

	spu_enable_spu(ctx);

	spu_update_sched_info(ctx);

	ret = spu_run_init(ctx, npc);
	अगर (ret) अणु
		spu_release(ctx);
		जाओ out;
	पूर्ण

	करो अणु
		ret = spufs_रुको(ctx->stop_wq, spu_stopped(ctx, &status));
		अगर (unlikely(ret)) अणु
			/*
			 * This is nasty: we need the state_mutex क्रम all the
			 * bookkeeping even अगर the syscall was पूर्णांकerrupted by
			 * a संकेत. ewww.
			 */
			mutex_lock(&ctx->state_mutex);
			अवरोध;
		पूर्ण
		अगर (unlikely(test_and_clear_bit(SPU_SCHED_NOTIFY_ACTIVE,
						&ctx->sched_flags))) अणु
			अगर (!(status & SPU_STATUS_STOPPED_BY_STOP))
				जारी;
		पूर्ण

		spuctx_चयन_state(ctx, SPU_UTIL_SYSTEM);

		अगर ((status & SPU_STATUS_STOPPED_BY_STOP) &&
		    (status >> SPU_STOP_STATUS_SHIFT == 0x2104)) अणु
			ret = spu_process_callback(ctx);
			अगर (ret)
				अवरोध;
			status &= ~SPU_STATUS_STOPPED_BY_STOP;
		पूर्ण
		ret = spufs_handle_class1(ctx);
		अगर (ret)
			अवरोध;

		ret = spufs_handle_class0(ctx);
		अगर (ret)
			अवरोध;

		अगर (संकेत_pending(current))
			ret = -ERESTARTSYS;
	पूर्ण जबतक (!ret && !(status & (SPU_STATUS_STOPPED_BY_STOP |
				      SPU_STATUS_STOPPED_BY_HALT |
				       SPU_STATUS_SINGLE_STEP)));

	spu_disable_spu(ctx);
	ret = spu_run_fini(ctx, npc, &status);
	spu_yield(ctx);

	अगर ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	    (((status >> SPU_STOP_STATUS_SHIFT) & 0x3f00) == 0x2100))
		ctx->stats.libassist++;

	अगर ((ret == 0) ||
	    ((ret == -ERESTARTSYS) &&
	     ((status & SPU_STATUS_STOPPED_BY_HALT) ||
	      (status & SPU_STATUS_SINGLE_STEP) ||
	      ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	       (status >> SPU_STOP_STATUS_SHIFT != 0x2104)))))
		ret = status;

	/* Note: we करोn't need to क्रमce_sig SIGTRAP on single-step
	 * since we have TIF_SINGLESTEP set, thus the kernel will करो
	 * it upon वापस from the syscall anyway.
	 */
	अगर (unlikely(status & SPU_STATUS_SINGLE_STEP))
		ret = -ERESTARTSYS;

	अन्यथा अगर (unlikely((status & SPU_STATUS_STOPPED_BY_STOP)
	    && (status >> SPU_STOP_STATUS_SHIFT) == 0x3fff)) अणु
		क्रमce_sig(SIGTRAP);
		ret = -ERESTARTSYS;
	पूर्ण

out:
	*event = ctx->event_वापस;
out_unlock:
	mutex_unlock(&ctx->run_mutex);
	वापस ret;
पूर्ण
