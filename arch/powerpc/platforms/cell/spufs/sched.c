<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* sched.c - SPU scheduler.
 *
 * Copyright (C) IBM 2005
 * Author: Mark Nutter <mnutter@us.ibm.com>
 *
 * 2006-03-31	NUMA करोमुख्यs added.
 */

#अघोषित DEBUG

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/numa.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश "spufs.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "sputrace.h"

काष्ठा spu_prio_array अणु
	DECLARE_BITMAP(biपंचांगap, MAX_PRIO);
	काष्ठा list_head runq[MAX_PRIO];
	spinlock_t runq_lock;
	पूर्णांक nr_रुकोing;
पूर्ण;

अटल अचिन्हित दीर्घ spu_avenrun[3];
अटल काष्ठा spu_prio_array *spu_prio;
अटल काष्ठा task_काष्ठा *spusched_task;
अटल काष्ठा समयr_list spusched_समयr;
अटल काष्ठा समयr_list spuloadavg_समयr;

/*
 * Priority of a normal, non-rt, non-niced'd process (aka nice level 0).
 */
#घोषणा NORMAL_PRIO		120

/*
 * Frequency of the spu scheduler tick.  By शेष we करो one SPU scheduler
 * tick क्रम every 10 CPU scheduler ticks.
 */
#घोषणा SPUSCHED_TICK		(10)

/*
 * These are the 'tuning knobs' of the scheduler:
 *
 * Minimum बारlice is 5 msecs (or 1 spu scheduler tick, whichever is
 * larger), शेष बारlice is 100 msecs, maximum बारlice is 800 msecs.
 */
#घोषणा MIN_SPU_TIMESLICE	max(5 * HZ / (1000 * SPUSCHED_TICK), 1)
#घोषणा DEF_SPU_TIMESLICE	(100 * HZ / (1000 * SPUSCHED_TICK))

#घोषणा SCALE_PRIO(x, prio) \
	max(x * (MAX_PRIO - prio) / (NICE_WIDTH / 2), MIN_SPU_TIMESLICE)

/*
 * scale user-nice values [ -20 ... 0 ... 19 ] to समय slice values:
 * [800ms ... 100ms ... 5ms]
 *
 * The higher a thपढ़ो's priority, the bigger बारlices
 * it माला_लो during one round of execution. But even the lowest
 * priority thपढ़ो माला_लो MIN_TIMESLICE worth of execution समय.
 */
व्योम spu_set_बारlice(काष्ठा spu_context *ctx)
अणु
	अगर (ctx->prio < NORMAL_PRIO)
		ctx->समय_slice = SCALE_PRIO(DEF_SPU_TIMESLICE * 4, ctx->prio);
	अन्यथा
		ctx->समय_slice = SCALE_PRIO(DEF_SPU_TIMESLICE, ctx->prio);
पूर्ण

/*
 * Update scheduling inक्रमmation from the owning thपढ़ो.
 */
व्योम __spu_update_sched_info(काष्ठा spu_context *ctx)
अणु
	/*
	 * निश्चित that the context is not on the runqueue, so it is safe
	 * to change its scheduling parameters.
	 */
	BUG_ON(!list_empty(&ctx->rq));

	/*
	 * 32-Bit assignments are atomic on घातerpc, and we करोn't care about
	 * memory ordering here because retrieving the controlling thपढ़ो is
	 * per definition racy.
	 */
	ctx->tid = current->pid;

	/*
	 * We करो our own priority calculations, so we normally want
	 * ->अटल_prio to start with. Unक्रमtunately this field
	 * contains junk क्रम thपढ़ोs with a realसमय scheduling
	 * policy so we have to look at ->prio in this हाल.
	 */
	अगर (rt_prio(current->prio))
		ctx->prio = current->prio;
	अन्यथा
		ctx->prio = current->अटल_prio;
	ctx->policy = current->policy;

	/*
	 * TO DO: the context may be loaded, so we may need to activate
	 * it again on a dअगरferent node. But it shouldn't hurt anything
	 * to update its parameters, because we know that the scheduler
	 * is not actively looking at this field, since it is not on the
	 * runqueue. The context will be rescheduled on the proper node
	 * अगर it is बारliced or preempted.
	 */
	cpumask_copy(&ctx->cpus_allowed, current->cpus_ptr);

	/* Save the current cpu id क्रम spu पूर्णांकerrupt routing. */
	ctx->last_ran = raw_smp_processor_id();
पूर्ण

व्योम spu_update_sched_info(काष्ठा spu_context *ctx)
अणु
	पूर्णांक node;

	अगर (ctx->state == SPU_STATE_RUNNABLE) अणु
		node = ctx->spu->node;

		/*
		 * Take list_mutex to sync with find_victim().
		 */
		mutex_lock(&cbe_spu_info[node].list_mutex);
		__spu_update_sched_info(ctx);
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	पूर्ण अन्यथा अणु
		__spu_update_sched_info(ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक __node_allowed(काष्ठा spu_context *ctx, पूर्णांक node)
अणु
	अगर (nr_cpus_node(node)) अणु
		स्थिर काष्ठा cpumask *mask = cpumask_of_node(node);

		अगर (cpumask_पूर्णांकersects(mask, &ctx->cpus_allowed))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक node_allowed(काष्ठा spu_context *ctx, पूर्णांक node)
अणु
	पूर्णांक rval;

	spin_lock(&spu_prio->runq_lock);
	rval = __node_allowed(ctx, node);
	spin_unlock(&spu_prio->runq_lock);

	वापस rval;
पूर्ण

व्योम करो_notअगरy_spus_active(व्योम)
अणु
	पूर्णांक node;

	/*
	 * Wake up the active spu_contexts.
	 */
	क्रम_each_online_node(node) अणु
		काष्ठा spu *spu;

		mutex_lock(&cbe_spu_info[node].list_mutex);
		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
			अगर (spu->alloc_state != SPU_FREE) अणु
				काष्ठा spu_context *ctx = spu->ctx;
				set_bit(SPU_SCHED_NOTIFY_ACTIVE,
					&ctx->sched_flags);
				mb();
				wake_up_all(&ctx->stop_wq);
			पूर्ण
		पूर्ण
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	पूर्ण
पूर्ण

/**
 * spu_bind_context - bind spu context to physical spu
 * @spu:	physical spu to bind to
 * @ctx:	context to bind
 */
अटल व्योम spu_bind_context(काष्ठा spu *spu, काष्ठा spu_context *ctx)
अणु
	spu_context_trace(spu_bind_context__enter, ctx, spu);

	spuctx_चयन_state(ctx, SPU_UTIL_SYSTEM);

	अगर (ctx->flags & SPU_CREATE_NOSCHED)
		atomic_inc(&cbe_spu_info[spu->node].reserved_spus);

	ctx->stats.slb_flt_base = spu->stats.slb_flt;
	ctx->stats.class2_पूर्णांकr_base = spu->stats.class2_पूर्णांकr;

	spu_associate_mm(spu, ctx->owner);

	spin_lock_irq(&spu->रेजिस्टर_lock);
	spu->ctx = ctx;
	spu->flags = 0;
	ctx->spu = spu;
	ctx->ops = &spu_hw_ops;
	spu->pid = current->pid;
	spu->tgid = current->tgid;
	spu->ibox_callback = spufs_ibox_callback;
	spu->wbox_callback = spufs_wbox_callback;
	spu->stop_callback = spufs_stop_callback;
	spu->mfc_callback = spufs_mfc_callback;
	spin_unlock_irq(&spu->रेजिस्टर_lock);

	spu_unmap_mappings(ctx);

	spu_चयन_log_notअगरy(spu, ctx, SWITCH_LOG_START, 0);
	spu_restore(&ctx->csa, spu);
	spu->बारtamp = jअगरfies;
	ctx->state = SPU_STATE_RUNNABLE;

	spuctx_चयन_state(ctx, SPU_UTIL_USER);
पूर्ण

/*
 * Must be used with the list_mutex held.
 */
अटल अंतरभूत पूर्णांक sched_spu(काष्ठा spu *spu)
अणु
	BUG_ON(!mutex_is_locked(&cbe_spu_info[spu->node].list_mutex));

	वापस (!spu->ctx || !(spu->ctx->flags & SPU_CREATE_NOSCHED));
पूर्ण

अटल व्योम aff_merge_reमुख्यing_ctxs(काष्ठा spu_gang *gang)
अणु
	काष्ठा spu_context *ctx;

	list_क्रम_each_entry(ctx, &gang->aff_list_head, aff_list) अणु
		अगर (list_empty(&ctx->aff_list))
			list_add(&ctx->aff_list, &gang->aff_list_head);
	पूर्ण
	gang->aff_flags |= AFF_MERGED;
पूर्ण

अटल व्योम aff_set_offsets(काष्ठा spu_gang *gang)
अणु
	काष्ठा spu_context *ctx;
	पूर्णांक offset;

	offset = -1;
	list_क्रम_each_entry_reverse(ctx, &gang->aff_ref_ctx->aff_list,
								aff_list) अणु
		अगर (&ctx->aff_list == &gang->aff_list_head)
			अवरोध;
		ctx->aff_offset = offset--;
	पूर्ण

	offset = 0;
	list_क्रम_each_entry(ctx, gang->aff_ref_ctx->aff_list.prev, aff_list) अणु
		अगर (&ctx->aff_list == &gang->aff_list_head)
			अवरोध;
		ctx->aff_offset = offset++;
	पूर्ण

	gang->aff_flags |= AFF_OFFSETS_SET;
पूर्ण

अटल काष्ठा spu *aff_ref_location(काष्ठा spu_context *ctx, पूर्णांक mem_aff,
		 पूर्णांक group_size, पूर्णांक lowest_offset)
अणु
	काष्ठा spu *spu;
	पूर्णांक node, n;

	/*
	 * TODO: A better algorithm could be used to find a good spu to be
	 *       used as reference location क्रम the ctxs chain.
	 */
	node = cpu_to_node(raw_smp_processor_id());
	क्रम (n = 0; n < MAX_NUMNODES; n++, node++) अणु
		/*
		 * "available_spus" counts how many spus are not potentially
		 * going to be used by other affinity gangs whose reference
		 * context is alपढ़ोy in place. Although this code seeks to
		 * aव्योम having affinity gangs with a summed amount of
		 * contexts bigger than the amount of spus in the node,
		 * this may happen sporadically. In this हाल, available_spus
		 * becomes negative, which is harmless.
		 */
		पूर्णांक available_spus;

		node = (node < MAX_NUMNODES) ? node : 0;
		अगर (!node_allowed(ctx, node))
			जारी;

		available_spus = 0;
		mutex_lock(&cbe_spu_info[node].list_mutex);
		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
			अगर (spu->ctx && spu->ctx->gang && !spu->ctx->aff_offset
					&& spu->ctx->gang->aff_ref_spu)
				available_spus -= spu->ctx->gang->contexts;
			available_spus++;
		पूर्ण
		अगर (available_spus < ctx->gang->contexts) अणु
			mutex_unlock(&cbe_spu_info[node].list_mutex);
			जारी;
		पूर्ण

		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
			अगर ((!mem_aff || spu->has_mem_affinity) &&
							sched_spu(spu)) अणु
				mutex_unlock(&cbe_spu_info[node].list_mutex);
				वापस spu;
			पूर्ण
		पूर्ण
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम aff_set_ref_poपूर्णांक_location(काष्ठा spu_gang *gang)
अणु
	पूर्णांक mem_aff, gs, lowest_offset;
	काष्ठा spu_context *ctx;
	काष्ठा spu *पंचांगp;

	mem_aff = gang->aff_ref_ctx->flags & SPU_CREATE_AFFINITY_MEM;
	lowest_offset = 0;
	gs = 0;

	list_क्रम_each_entry(पंचांगp, &gang->aff_list_head, aff_list)
		gs++;

	list_क्रम_each_entry_reverse(ctx, &gang->aff_ref_ctx->aff_list,
								aff_list) अणु
		अगर (&ctx->aff_list == &gang->aff_list_head)
			अवरोध;
		lowest_offset = ctx->aff_offset;
	पूर्ण

	gang->aff_ref_spu = aff_ref_location(gang->aff_ref_ctx, mem_aff, gs,
							lowest_offset);
पूर्ण

अटल काष्ठा spu *ctx_location(काष्ठा spu *ref, पूर्णांक offset, पूर्णांक node)
अणु
	काष्ठा spu *spu;

	spu = शून्य;
	अगर (offset >= 0) अणु
		list_क्रम_each_entry(spu, ref->aff_list.prev, aff_list) अणु
			BUG_ON(spu->node != node);
			अगर (offset == 0)
				अवरोध;
			अगर (sched_spu(spu))
				offset--;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_reverse(spu, ref->aff_list.next, aff_list) अणु
			BUG_ON(spu->node != node);
			अगर (offset == 0)
				अवरोध;
			अगर (sched_spu(spu))
				offset++;
		पूर्ण
	पूर्ण

	वापस spu;
पूर्ण

/*
 * affinity_check is called each समय a context is going to be scheduled.
 * It वापसs the spu ptr on which the context must run.
 */
अटल पूर्णांक has_affinity(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_gang *gang = ctx->gang;

	अगर (list_empty(&ctx->aff_list))
		वापस 0;

	अगर (atomic_पढ़ो(&ctx->gang->aff_sched_count) == 0)
		ctx->gang->aff_ref_spu = शून्य;

	अगर (!gang->aff_ref_spu) अणु
		अगर (!(gang->aff_flags & AFF_MERGED))
			aff_merge_reमुख्यing_ctxs(gang);
		अगर (!(gang->aff_flags & AFF_OFFSETS_SET))
			aff_set_offsets(gang);
		aff_set_ref_poपूर्णांक_location(gang);
	पूर्ण

	वापस gang->aff_ref_spu != शून्य;
पूर्ण

/**
 * spu_unbind_context - unbind spu context from physical spu
 * @spu:	physical spu to unbind from
 * @ctx:	context to unbind
 */
अटल व्योम spu_unbind_context(काष्ठा spu *spu, काष्ठा spu_context *ctx)
अणु
	u32 status;

	spu_context_trace(spu_unbind_context__enter, ctx, spu);

	spuctx_चयन_state(ctx, SPU_UTIL_SYSTEM);

 	अगर (spu->ctx->flags & SPU_CREATE_NOSCHED)
		atomic_dec(&cbe_spu_info[spu->node].reserved_spus);

	अगर (ctx->gang)
		/*
		 * If ctx->gang->aff_sched_count is positive, SPU affinity is
		 * being considered in this gang. Using atomic_dec_अगर_positive
		 * allow us to skip an explicit check क्रम affinity in this gang
		 */
		atomic_dec_अगर_positive(&ctx->gang->aff_sched_count);

	spu_unmap_mappings(ctx);
	spu_save(&ctx->csa, spu);
	spu_चयन_log_notअगरy(spu, ctx, SWITCH_LOG_STOP, 0);

	spin_lock_irq(&spu->रेजिस्टर_lock);
	spu->बारtamp = jअगरfies;
	ctx->state = SPU_STATE_SAVED;
	spu->ibox_callback = शून्य;
	spu->wbox_callback = शून्य;
	spu->stop_callback = शून्य;
	spu->mfc_callback = शून्य;
	spu->pid = 0;
	spu->tgid = 0;
	ctx->ops = &spu_backing_ops;
	spu->flags = 0;
	spu->ctx = शून्य;
	spin_unlock_irq(&spu->रेजिस्टर_lock);

	spu_associate_mm(spu, शून्य);

	ctx->stats.slb_flt +=
		(spu->stats.slb_flt - ctx->stats.slb_flt_base);
	ctx->stats.class2_पूर्णांकr +=
		(spu->stats.class2_पूर्णांकr - ctx->stats.class2_पूर्णांकr_base);

	/* This maps the underlying spu state to idle */
	spuctx_चयन_state(ctx, SPU_UTIL_IDLE_LOADED);
	ctx->spu = शून्य;

	अगर (spu_stopped(ctx, &status))
		wake_up_all(&ctx->stop_wq);
पूर्ण

/**
 * spu_add_to_rq - add a context to the runqueue
 * @ctx:       context to add
 */
अटल व्योम __spu_add_to_rq(काष्ठा spu_context *ctx)
अणु
	/*
	 * Unक्रमtunately this code path can be called from multiple thपढ़ोs
	 * on behalf of a single context due to the way the problem state
	 * mmap support works.
	 *
	 * Fortunately we need to wake up all these thपढ़ोs at the same समय
	 * and can simply skip the runqueue addition क्रम every but the first
	 * thपढ़ो getting पूर्णांकo this codepath.
	 *
	 * It's still quite hacky, and दीर्घ-term we should proxy all other
	 * thपढ़ोs through the owner thपढ़ो so that spu_run is in control
	 * of all the scheduling activity क्रम a given context.
	 */
	अगर (list_empty(&ctx->rq)) अणु
		list_add_tail(&ctx->rq, &spu_prio->runq[ctx->prio]);
		set_bit(ctx->prio, spu_prio->biपंचांगap);
		अगर (!spu_prio->nr_रुकोing++)
			mod_समयr(&spusched_समयr, jअगरfies + SPUSCHED_TICK);
	पूर्ण
पूर्ण

अटल व्योम spu_add_to_rq(काष्ठा spu_context *ctx)
अणु
	spin_lock(&spu_prio->runq_lock);
	__spu_add_to_rq(ctx);
	spin_unlock(&spu_prio->runq_lock);
पूर्ण

अटल व्योम __spu_del_from_rq(काष्ठा spu_context *ctx)
अणु
	पूर्णांक prio = ctx->prio;

	अगर (!list_empty(&ctx->rq)) अणु
		अगर (!--spu_prio->nr_रुकोing)
			del_समयr(&spusched_समयr);
		list_del_init(&ctx->rq);

		अगर (list_empty(&spu_prio->runq[prio]))
			clear_bit(prio, spu_prio->biपंचांगap);
	पूर्ण
पूर्ण

व्योम spu_del_from_rq(काष्ठा spu_context *ctx)
अणु
	spin_lock(&spu_prio->runq_lock);
	__spu_del_from_rq(ctx);
	spin_unlock(&spu_prio->runq_lock);
पूर्ण

अटल व्योम spu_prio_रुको(काष्ठा spu_context *ctx)
अणु
	DEFINE_WAIT(रुको);

	/*
	 * The caller must explicitly रुको क्रम a context to be loaded
	 * अगर the nosched flag is set.  If NOSCHED is not set, the caller
	 * queues the context and रुकोs क्रम an spu event or error.
	 */
	BUG_ON(!(ctx->flags & SPU_CREATE_NOSCHED));

	spin_lock(&spu_prio->runq_lock);
	prepare_to_रुको_exclusive(&ctx->stop_wq, &रुको, TASK_INTERRUPTIBLE);
	अगर (!संकेत_pending(current)) अणु
		__spu_add_to_rq(ctx);
		spin_unlock(&spu_prio->runq_lock);
		mutex_unlock(&ctx->state_mutex);
		schedule();
		mutex_lock(&ctx->state_mutex);
		spin_lock(&spu_prio->runq_lock);
		__spu_del_from_rq(ctx);
	पूर्ण
	spin_unlock(&spu_prio->runq_lock);
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&ctx->stop_wq, &रुको);
पूर्ण

अटल काष्ठा spu *spu_get_idle(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu *spu, *aff_ref_spu;
	पूर्णांक node, n;

	spu_context_nospu_trace(spu_get_idle__enter, ctx);

	अगर (ctx->gang) अणु
		mutex_lock(&ctx->gang->aff_mutex);
		अगर (has_affinity(ctx)) अणु
			aff_ref_spu = ctx->gang->aff_ref_spu;
			atomic_inc(&ctx->gang->aff_sched_count);
			mutex_unlock(&ctx->gang->aff_mutex);
			node = aff_ref_spu->node;

			mutex_lock(&cbe_spu_info[node].list_mutex);
			spu = ctx_location(aff_ref_spu, ctx->aff_offset, node);
			अगर (spu && spu->alloc_state == SPU_FREE)
				जाओ found;
			mutex_unlock(&cbe_spu_info[node].list_mutex);

			atomic_dec(&ctx->gang->aff_sched_count);
			जाओ not_found;
		पूर्ण
		mutex_unlock(&ctx->gang->aff_mutex);
	पूर्ण
	node = cpu_to_node(raw_smp_processor_id());
	क्रम (n = 0; n < MAX_NUMNODES; n++, node++) अणु
		node = (node < MAX_NUMNODES) ? node : 0;
		अगर (!node_allowed(ctx, node))
			जारी;

		mutex_lock(&cbe_spu_info[node].list_mutex);
		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
			अगर (spu->alloc_state == SPU_FREE)
				जाओ found;
		पूर्ण
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	पूर्ण

 not_found:
	spu_context_nospu_trace(spu_get_idle__not_found, ctx);
	वापस शून्य;

 found:
	spu->alloc_state = SPU_USED;
	mutex_unlock(&cbe_spu_info[node].list_mutex);
	spu_context_trace(spu_get_idle__found, ctx, spu);
	spu_init_channels(spu);
	वापस spu;
पूर्ण

/**
 * find_victim - find a lower priority context to preempt
 * @ctx:	candidate context क्रम running
 *
 * Returns the मुक्तd physical spu to run the new context on.
 */
अटल काष्ठा spu *find_victim(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_context *victim = शून्य;
	काष्ठा spu *spu;
	पूर्णांक node, n;

	spu_context_nospu_trace(spu_find_victim__enter, ctx);

	/*
	 * Look क्रम a possible preemption candidate on the local node first.
	 * If there is no candidate look at the other nodes.  This isn't
	 * exactly fair, but so far the whole spu scheduler tries to keep
	 * a strong node affinity.  We might want to fine-tune this in
	 * the future.
	 */
 restart:
	node = cpu_to_node(raw_smp_processor_id());
	क्रम (n = 0; n < MAX_NUMNODES; n++, node++) अणु
		node = (node < MAX_NUMNODES) ? node : 0;
		अगर (!node_allowed(ctx, node))
			जारी;

		mutex_lock(&cbe_spu_info[node].list_mutex);
		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
			काष्ठा spu_context *पंचांगp = spu->ctx;

			अगर (पंचांगp && पंचांगp->prio > ctx->prio &&
			    !(पंचांगp->flags & SPU_CREATE_NOSCHED) &&
			    (!victim || पंचांगp->prio > victim->prio)) अणु
				victim = spu->ctx;
			पूर्ण
		पूर्ण
		अगर (victim)
			get_spu_context(victim);
		mutex_unlock(&cbe_spu_info[node].list_mutex);

		अगर (victim) अणु
			/*
			 * This nests ctx->state_mutex, but we always lock
			 * higher priority contexts beक्रमe lower priority
			 * ones, so this is safe until we पूर्णांकroduce
			 * priority inheritance schemes.
			 *
			 * XXX अगर the highest priority context is locked,
			 * this can loop a दीर्घ समय.  Might be better to
			 * look at another context or give up after X retries.
			 */
			अगर (!mutex_trylock(&victim->state_mutex)) अणु
				put_spu_context(victim);
				victim = शून्य;
				जाओ restart;
			पूर्ण

			spu = victim->spu;
			अगर (!spu || victim->prio <= ctx->prio) अणु
				/*
				 * This race can happen because we've dropped
				 * the active list mutex.  Not a problem, just
				 * restart the search.
				 */
				mutex_unlock(&victim->state_mutex);
				put_spu_context(victim);
				victim = शून्य;
				जाओ restart;
			पूर्ण

			spu_context_trace(__spu_deactivate__unload, ctx, spu);

			mutex_lock(&cbe_spu_info[node].list_mutex);
			cbe_spu_info[node].nr_active--;
			spu_unbind_context(spu, victim);
			mutex_unlock(&cbe_spu_info[node].list_mutex);

			victim->stats.invol_ctx_चयन++;
			spu->stats.invol_ctx_चयन++;
			अगर (test_bit(SPU_SCHED_SPU_RUN, &victim->sched_flags))
				spu_add_to_rq(victim);

			mutex_unlock(&victim->state_mutex);
			put_spu_context(victim);

			वापस spu;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __spu_schedule(काष्ठा spu *spu, काष्ठा spu_context *ctx)
अणु
	पूर्णांक node = spu->node;
	पूर्णांक success = 0;

	spu_set_बारlice(ctx);

	mutex_lock(&cbe_spu_info[node].list_mutex);
	अगर (spu->ctx == शून्य) अणु
		spu_bind_context(spu, ctx);
		cbe_spu_info[node].nr_active++;
		spu->alloc_state = SPU_USED;
		success = 1;
	पूर्ण
	mutex_unlock(&cbe_spu_info[node].list_mutex);

	अगर (success)
		wake_up_all(&ctx->run_wq);
	अन्यथा
		spu_add_to_rq(ctx);
पूर्ण

अटल व्योम spu_schedule(काष्ठा spu *spu, काष्ठा spu_context *ctx)
अणु
	/* not a candidate क्रम पूर्णांकerruptible because it's called either
	   from the scheduler thपढ़ो or from spu_deactivate */
	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state == SPU_STATE_SAVED)
		__spu_schedule(spu, ctx);
	spu_release(ctx);
पूर्ण

/**
 * spu_unschedule - हटाओ a context from a spu, and possibly release it.
 * @spu:	The SPU to unschedule from
 * @ctx:	The context currently scheduled on the SPU
 * @मुक्त_spu	Whether to मुक्त the SPU क्रम other contexts
 *
 * Unbinds the context @ctx from the SPU @spu. If @मुक्त_spu is non-zero, the
 * SPU is made available क्रम other contexts (ie, may be वापसed by
 * spu_get_idle). If this is zero, the caller is expected to schedule another
 * context to this spu.
 *
 * Should be called with ctx->state_mutex held.
 */
अटल व्योम spu_unschedule(काष्ठा spu *spu, काष्ठा spu_context *ctx,
		पूर्णांक मुक्त_spu)
अणु
	पूर्णांक node = spu->node;

	mutex_lock(&cbe_spu_info[node].list_mutex);
	cbe_spu_info[node].nr_active--;
	अगर (मुक्त_spu)
		spu->alloc_state = SPU_FREE;
	spu_unbind_context(spu, ctx);
	ctx->stats.invol_ctx_चयन++;
	spu->stats.invol_ctx_चयन++;
	mutex_unlock(&cbe_spu_info[node].list_mutex);
पूर्ण

/**
 * spu_activate - find a मुक्त spu क्रम a context and execute it
 * @ctx:	spu context to schedule
 * @flags:	flags (currently ignored)
 *
 * Tries to find a मुक्त spu to run @ctx.  If no मुक्त spu is available
 * add the context to the runqueue so it माला_लो woken up once an spu
 * is available.
 */
पूर्णांक spu_activate(काष्ठा spu_context *ctx, अचिन्हित दीर्घ flags)
अणु
	काष्ठा spu *spu;

	/*
	 * If there are multiple thपढ़ोs रुकोing क्रम a single context
	 * only one actually binds the context जबतक the others will
	 * only be able to acquire the state_mutex once the context
	 * alपढ़ोy is in runnable state.
	 */
	अगर (ctx->spu)
		वापस 0;

spu_activate_top:
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;

	spu = spu_get_idle(ctx);
	/*
	 * If this is a realसमय thपढ़ो we try to get it running by
	 * preempting a lower priority thपढ़ो.
	 */
	अगर (!spu && rt_prio(ctx->prio))
		spu = find_victim(ctx);
	अगर (spu) अणु
		अचिन्हित दीर्घ runcntl;

		runcntl = ctx->ops->runcntl_पढ़ो(ctx);
		__spu_schedule(spu, ctx);
		अगर (runcntl & SPU_RUNCNTL_RUNNABLE)
			spuctx_चयन_state(ctx, SPU_UTIL_USER);

		वापस 0;
	पूर्ण

	अगर (ctx->flags & SPU_CREATE_NOSCHED) अणु
		spu_prio_रुको(ctx);
		जाओ spu_activate_top;
	पूर्ण

	spu_add_to_rq(ctx);

	वापस 0;
पूर्ण

/**
 * grab_runnable_context - try to find a runnable context
 *
 * Remove the highest priority context on the runqueue and वापस it
 * to the caller.  Returns %शून्य अगर no runnable context was found.
 */
अटल काष्ठा spu_context *grab_runnable_context(पूर्णांक prio, पूर्णांक node)
अणु
	काष्ठा spu_context *ctx;
	पूर्णांक best;

	spin_lock(&spu_prio->runq_lock);
	best = find_first_bit(spu_prio->biपंचांगap, prio);
	जबतक (best < prio) अणु
		काष्ठा list_head *rq = &spu_prio->runq[best];

		list_क्रम_each_entry(ctx, rq, rq) अणु
			/* XXX(hch): check क्रम affinity here as well */
			अगर (__node_allowed(ctx, node)) अणु
				__spu_del_from_rq(ctx);
				जाओ found;
			पूर्ण
		पूर्ण
		best++;
	पूर्ण
	ctx = शून्य;
 found:
	spin_unlock(&spu_prio->runq_lock);
	वापस ctx;
पूर्ण

अटल पूर्णांक __spu_deactivate(काष्ठा spu_context *ctx, पूर्णांक क्रमce, पूर्णांक max_prio)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_context *new = शून्य;

	अगर (spu) अणु
		new = grab_runnable_context(max_prio, spu->node);
		अगर (new || क्रमce) अणु
			spu_unschedule(spu, ctx, new == शून्य);
			अगर (new) अणु
				अगर (new->flags & SPU_CREATE_NOSCHED)
					wake_up(&new->stop_wq);
				अन्यथा अणु
					spu_release(ctx);
					spu_schedule(spu, new);
					/* this one can't easily be made
					   पूर्णांकerruptible */
					mutex_lock(&ctx->state_mutex);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस new != शून्य;
पूर्ण

/**
 * spu_deactivate - unbind a context from it's physical spu
 * @ctx:	spu context to unbind
 *
 * Unbind @ctx from the physical spu it is running on and schedule
 * the highest priority context to run on the मुक्तd physical spu.
 */
व्योम spu_deactivate(काष्ठा spu_context *ctx)
अणु
	spu_context_nospu_trace(spu_deactivate__enter, ctx);
	__spu_deactivate(ctx, 1, MAX_PRIO);
पूर्ण

/**
 * spu_yield -	yield a physical spu अगर others are रुकोing
 * @ctx:	spu context to yield
 *
 * Check अगर there is a higher priority context रुकोing and अगर yes
 * unbind @ctx from the physical spu and schedule the highest
 * priority context to run on the मुक्तd physical spu instead.
 */
व्योम spu_yield(काष्ठा spu_context *ctx)
अणु
	spu_context_nospu_trace(spu_yield__enter, ctx);
	अगर (!(ctx->flags & SPU_CREATE_NOSCHED)) अणु
		mutex_lock(&ctx->state_mutex);
		__spu_deactivate(ctx, 0, MAX_PRIO);
		mutex_unlock(&ctx->state_mutex);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम spusched_tick(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_context *new = शून्य;
	काष्ठा spu *spu = शून्य;

	अगर (spu_acquire(ctx))
		BUG();	/* a kernel thपढ़ो never has संकेतs pending */

	अगर (ctx->state != SPU_STATE_RUNNABLE)
		जाओ out;
	अगर (ctx->flags & SPU_CREATE_NOSCHED)
		जाओ out;
	अगर (ctx->policy == SCHED_FIFO)
		जाओ out;

	अगर (--ctx->समय_slice && test_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags))
		जाओ out;

	spu = ctx->spu;

	spu_context_trace(spusched_tick__preempt, ctx, spu);

	new = grab_runnable_context(ctx->prio + 1, spu->node);
	अगर (new) अणु
		spu_unschedule(spu, ctx, 0);
		अगर (test_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags))
			spu_add_to_rq(ctx);
	पूर्ण अन्यथा अणु
		spu_context_nospu_trace(spusched_tick__newslice, ctx);
		अगर (!ctx->समय_slice)
			ctx->समय_slice++;
	पूर्ण
out:
	spu_release(ctx);

	अगर (new)
		spu_schedule(spu, new);
पूर्ण

/**
 * count_active_contexts - count nr of active tasks
 *
 * Return the number of tasks currently running or रुकोing to run.
 *
 * Note that we करोn't take runq_lock / list_mutex here.  Reading
 * a single 32bit value is atomic on घातerpc, and we करोn't care
 * about memory ordering issues here.
 */
अटल अचिन्हित दीर्घ count_active_contexts(व्योम)
अणु
	पूर्णांक nr_active = 0, node;

	क्रम (node = 0; node < MAX_NUMNODES; node++)
		nr_active += cbe_spu_info[node].nr_active;
	nr_active += spu_prio->nr_रुकोing;

	वापस nr_active;
पूर्ण

/**
 * spu_calc_load - update the avenrun load estimates.
 *
 * No locking against पढ़ोing these values from userspace, as क्रम
 * the CPU loadavg code.
 */
अटल व्योम spu_calc_load(व्योम)
अणु
	अचिन्हित दीर्घ active_tasks; /* fixed-poपूर्णांक */

	active_tasks = count_active_contexts() * FIXED_1;
	spu_avenrun[0] = calc_load(spu_avenrun[0], EXP_1, active_tasks);
	spu_avenrun[1] = calc_load(spu_avenrun[1], EXP_5, active_tasks);
	spu_avenrun[2] = calc_load(spu_avenrun[2], EXP_15, active_tasks);
पूर्ण

अटल व्योम spusched_wake(काष्ठा समयr_list *unused)
अणु
	mod_समयr(&spusched_समयr, jअगरfies + SPUSCHED_TICK);
	wake_up_process(spusched_task);
पूर्ण

अटल व्योम spuloadavg_wake(काष्ठा समयr_list *unused)
अणु
	mod_समयr(&spuloadavg_समयr, jअगरfies + LOAD_FREQ);
	spu_calc_load();
पूर्ण

अटल पूर्णांक spusched_thपढ़ो(व्योम *unused)
अणु
	काष्ठा spu *spu;
	पूर्णांक node;

	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
		क्रम (node = 0; node < MAX_NUMNODES; node++) अणु
			काष्ठा mutex *mtx = &cbe_spu_info[node].list_mutex;

			mutex_lock(mtx);
			list_क्रम_each_entry(spu, &cbe_spu_info[node].spus,
					cbe_list) अणु
				काष्ठा spu_context *ctx = spu->ctx;

				अगर (ctx) अणु
					get_spu_context(ctx);
					mutex_unlock(mtx);
					spusched_tick(ctx);
					mutex_lock(mtx);
					put_spu_context(ctx);
				पूर्ण
			पूर्ण
			mutex_unlock(mtx);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम spuctx_चयन_state(काष्ठा spu_context *ctx,
		क्रमागत spu_utilization_state new_state)
अणु
	अचिन्हित दीर्घ दीर्घ curसमय;
	चिन्हित दीर्घ दीर्घ delta;
	काष्ठा spu *spu;
	क्रमागत spu_utilization_state old_state;
	पूर्णांक node;

	curसमय = kसमय_get_ns();
	delta = curसमय - ctx->stats.tstamp;

	WARN_ON(!mutex_is_locked(&ctx->state_mutex));
	WARN_ON(delta < 0);

	spu = ctx->spu;
	old_state = ctx->stats.util_state;
	ctx->stats.util_state = new_state;
	ctx->stats.tstamp = curसमय;

	/*
	 * Update the physical SPU utilization statistics.
	 */
	अगर (spu) अणु
		ctx->stats.बार[old_state] += delta;
		spu->stats.बार[old_state] += delta;
		spu->stats.util_state = new_state;
		spu->stats.tstamp = curसमय;
		node = spu->node;
		अगर (old_state == SPU_UTIL_USER)
			atomic_dec(&cbe_spu_info[node].busy_spus);
		अगर (new_state == SPU_UTIL_USER)
			atomic_inc(&cbe_spu_info[node].busy_spus);
	पूर्ण
पूर्ण

अटल पूर्णांक show_spu_loadavg(काष्ठा seq_file *s, व्योम *निजी)
अणु
	पूर्णांक a, b, c;

	a = spu_avenrun[0] + (FIXED_1/200);
	b = spu_avenrun[1] + (FIXED_1/200);
	c = spu_avenrun[2] + (FIXED_1/200);

	/*
	 * Note that last_pid करोesn't really make much sense क्रम the
	 * SPU loadavg (it even seems very odd on the CPU side...),
	 * but we include it here to have a 100% compatible पूर्णांकerface.
	 */
	seq_म_लिखो(s, "%d.%02d %d.%02d %d.%02d %ld/%d %d\n",
		LOAD_INT(a), LOAD_FRAC(a),
		LOAD_INT(b), LOAD_FRAC(b),
		LOAD_INT(c), LOAD_FRAC(c),
		count_active_contexts(),
		atomic_पढ़ो(&nr_spu_contexts),
		idr_get_cursor(&task_active_pid_ns(current)->idr) - 1);
	वापस 0;
पूर्ण;

पूर्णांक __init spu_sched_init(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;
	पूर्णांक err = -ENOMEM, i;

	spu_prio = kzalloc(माप(काष्ठा spu_prio_array), GFP_KERNEL);
	अगर (!spu_prio)
		जाओ out;

	क्रम (i = 0; i < MAX_PRIO; i++) अणु
		INIT_LIST_HEAD(&spu_prio->runq[i]);
		__clear_bit(i, spu_prio->biपंचांगap);
	पूर्ण
	spin_lock_init(&spu_prio->runq_lock);

	समयr_setup(&spusched_समयr, spusched_wake, 0);
	समयr_setup(&spuloadavg_समयr, spuloadavg_wake, 0);

	spusched_task = kthपढ़ो_run(spusched_thपढ़ो, शून्य, "spusched");
	अगर (IS_ERR(spusched_task)) अणु
		err = PTR_ERR(spusched_task);
		जाओ out_मुक्त_spu_prio;
	पूर्ण

	mod_समयr(&spuloadavg_समयr, 0);

	entry = proc_create_single("spu_loadavg", 0, शून्य, show_spu_loadavg);
	अगर (!entry)
		जाओ out_stop_kthपढ़ो;

	pr_debug("spusched: tick: %d, min ticks: %d, default ticks: %d\n",
			SPUSCHED_TICK, MIN_SPU_TIMESLICE, DEF_SPU_TIMESLICE);
	वापस 0;

 out_stop_kthपढ़ो:
	kthपढ़ो_stop(spusched_task);
 out_मुक्त_spu_prio:
	kमुक्त(spu_prio);
 out:
	वापस err;
पूर्ण

व्योम spu_sched_निकास(व्योम)
अणु
	काष्ठा spu *spu;
	पूर्णांक node;

	हटाओ_proc_entry("spu_loadavg", शून्य);

	del_समयr_sync(&spusched_समयr);
	del_समयr_sync(&spuloadavg_समयr);
	kthपढ़ो_stop(spusched_task);

	क्रम (node = 0; node < MAX_NUMNODES; node++) अणु
		mutex_lock(&cbe_spu_info[node].list_mutex);
		list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list)
			अगर (spu->alloc_state != SPU_FREE)
				spu->alloc_state = SPU_FREE;
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	पूर्ण
	kमुक्त(spu_prio);
पूर्ण
