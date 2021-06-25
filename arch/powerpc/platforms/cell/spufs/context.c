<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU file प्रणाली -- SPU context management
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश "spufs.h"
#समावेश "sputrace.h"


atomic_t nr_spu_contexts = ATOMIC_INIT(0);

काष्ठा spu_context *alloc_spu_context(काष्ठा spu_gang *gang)
अणु
	काष्ठा spu_context *ctx;

	ctx = kzalloc(माप *ctx, GFP_KERNEL);
	अगर (!ctx)
		जाओ out;
	/* Binding to physical processor deferred
	 * until spu_activate().
	 */
	अगर (spu_init_csa(&ctx->csa))
		जाओ out_मुक्त;
	spin_lock_init(&ctx->mmio_lock);
	mutex_init(&ctx->mapping_lock);
	kref_init(&ctx->kref);
	mutex_init(&ctx->state_mutex);
	mutex_init(&ctx->run_mutex);
	init_रुकोqueue_head(&ctx->ibox_wq);
	init_रुकोqueue_head(&ctx->wbox_wq);
	init_रुकोqueue_head(&ctx->stop_wq);
	init_रुकोqueue_head(&ctx->mfc_wq);
	init_रुकोqueue_head(&ctx->run_wq);
	ctx->state = SPU_STATE_SAVED;
	ctx->ops = &spu_backing_ops;
	ctx->owner = get_task_mm(current);
	INIT_LIST_HEAD(&ctx->rq);
	INIT_LIST_HEAD(&ctx->aff_list);
	अगर (gang)
		spu_gang_add_ctx(gang, ctx);

	__spu_update_sched_info(ctx);
	spu_set_बारlice(ctx);
	ctx->stats.util_state = SPU_UTIL_IDLE_LOADED;
	ctx->stats.tstamp = kसमय_get_ns();

	atomic_inc(&nr_spu_contexts);
	जाओ out;
out_मुक्त:
	kमुक्त(ctx);
	ctx = शून्य;
out:
	वापस ctx;
पूर्ण

व्योम destroy_spu_context(काष्ठा kref *kref)
अणु
	काष्ठा spu_context *ctx;
	ctx = container_of(kref, काष्ठा spu_context, kref);
	spu_context_nospu_trace(destroy_spu_context__enter, ctx);
	mutex_lock(&ctx->state_mutex);
	spu_deactivate(ctx);
	mutex_unlock(&ctx->state_mutex);
	spu_fini_csa(&ctx->csa);
	अगर (ctx->gang)
		spu_gang_हटाओ_ctx(ctx->gang, ctx);
	अगर (ctx->prof_priv_kref)
		kref_put(ctx->prof_priv_kref, ctx->prof_priv_release);
	BUG_ON(!list_empty(&ctx->rq));
	atomic_dec(&nr_spu_contexts);
	kमुक्त(ctx->चयन_log);
	kमुक्त(ctx);
पूर्ण

काष्ठा spu_context * get_spu_context(काष्ठा spu_context *ctx)
अणु
	kref_get(&ctx->kref);
	वापस ctx;
पूर्ण

पूर्णांक put_spu_context(काष्ठा spu_context *ctx)
अणु
	वापस kref_put(&ctx->kref, &destroy_spu_context);
पूर्ण

/* give up the mm reference when the context is about to be destroyed */
व्योम spu_क्रमget(काष्ठा spu_context *ctx)
अणु
	काष्ठा mm_काष्ठा *mm;

	/*
	 * This is basically an खोलो-coded spu_acquire_saved, except that
	 * we करोn't acquire the state mutex interruptible, and we don't
	 * want this context to be rescheduled on release.
	 */
	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state != SPU_STATE_SAVED)
		spu_deactivate(ctx);

	mm = ctx->owner;
	ctx->owner = शून्य;
	mmput(mm);
	spu_release(ctx);
पूर्ण

व्योम spu_unmap_mappings(काष्ठा spu_context *ctx)
अणु
	mutex_lock(&ctx->mapping_lock);
	अगर (ctx->local_store)
		unmap_mapping_range(ctx->local_store, 0, LS_SIZE, 1);
	अगर (ctx->mfc)
		unmap_mapping_range(ctx->mfc, 0, SPUFS_MFC_MAP_SIZE, 1);
	अगर (ctx->cntl)
		unmap_mapping_range(ctx->cntl, 0, SPUFS_CNTL_MAP_SIZE, 1);
	अगर (ctx->संकेत1)
		unmap_mapping_range(ctx->संकेत1, 0, SPUFS_SIGNAL_MAP_SIZE, 1);
	अगर (ctx->संकेत2)
		unmap_mapping_range(ctx->संकेत2, 0, SPUFS_SIGNAL_MAP_SIZE, 1);
	अगर (ctx->mss)
		unmap_mapping_range(ctx->mss, 0, SPUFS_MSS_MAP_SIZE, 1);
	अगर (ctx->psmap)
		unmap_mapping_range(ctx->psmap, 0, SPUFS_PS_MAP_SIZE, 1);
	mutex_unlock(&ctx->mapping_lock);
पूर्ण

/**
 * spu_acquire_saved - lock spu contex and make sure it is in saved state
 * @ctx:	spu contex to lock
 */
पूर्णांक spu_acquire_saved(काष्ठा spu_context *ctx)
अणु
	पूर्णांक ret;

	spu_context_nospu_trace(spu_acquire_saved__enter, ctx);

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;

	अगर (ctx->state != SPU_STATE_SAVED) अणु
		set_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_flags);
		spu_deactivate(ctx);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spu_release_saved - unlock spu context and वापस it to the runqueue
 * @ctx:	context to unlock
 */
व्योम spu_release_saved(काष्ठा spu_context *ctx)
अणु
	BUG_ON(ctx->state != SPU_STATE_SAVED);

	अगर (test_and_clear_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_flags) &&
			test_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags))
		spu_activate(ctx, 0);

	spu_release(ctx);
पूर्ण

