<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cgroups support क्रम the BFQ I/O scheduler.
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/elevator.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/delay.h>

#समावेश "bfq-iosched.h"

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
अटल पूर्णांक bfq_stat_init(काष्ठा bfq_stat *stat, gfp_t gfp)
अणु
	पूर्णांक ret;

	ret = percpu_counter_init(&stat->cpu_cnt, 0, gfp);
	अगर (ret)
		वापस ret;

	atomic64_set(&stat->aux_cnt, 0);
	वापस 0;
पूर्ण

अटल व्योम bfq_stat_निकास(काष्ठा bfq_stat *stat)
अणु
	percpu_counter_destroy(&stat->cpu_cnt);
पूर्ण

/**
 * bfq_stat_add - add a value to a bfq_stat
 * @stat: target bfq_stat
 * @val: value to add
 *
 * Add @val to @stat.  The caller must ensure that IRQ on the same CPU
 * करोn't re-enter this function क्रम the same counter.
 */
अटल अंतरभूत व्योम bfq_stat_add(काष्ठा bfq_stat *stat, uपूर्णांक64_t val)
अणु
	percpu_counter_add_batch(&stat->cpu_cnt, val, BLKG_STAT_CPU_BATCH);
पूर्ण

/**
 * bfq_stat_पढ़ो - पढ़ो the current value of a bfq_stat
 * @stat: bfq_stat to पढ़ो
 */
अटल अंतरभूत uपूर्णांक64_t bfq_stat_पढ़ो(काष्ठा bfq_stat *stat)
अणु
	वापस percpu_counter_sum_positive(&stat->cpu_cnt);
पूर्ण

/**
 * bfq_stat_reset - reset a bfq_stat
 * @stat: bfq_stat to reset
 */
अटल अंतरभूत व्योम bfq_stat_reset(काष्ठा bfq_stat *stat)
अणु
	percpu_counter_set(&stat->cpu_cnt, 0);
	atomic64_set(&stat->aux_cnt, 0);
पूर्ण

/**
 * bfq_stat_add_aux - add a bfq_stat पूर्णांकo another's aux count
 * @to: the destination bfq_stat
 * @from: the source
 *
 * Add @from's count including the aux one to @to's aux count.
 */
अटल अंतरभूत व्योम bfq_stat_add_aux(काष्ठा bfq_stat *to,
				     काष्ठा bfq_stat *from)
अणु
	atomic64_add(bfq_stat_पढ़ो(from) + atomic64_पढ़ो(&from->aux_cnt),
		     &to->aux_cnt);
पूर्ण

/**
 * blkg_prfill_stat - prfill callback क्रम bfq_stat
 * @sf: seq_file to prपूर्णांक to
 * @pd: policy निजी data of पूर्णांकerest
 * @off: offset to the bfq_stat in @pd
 *
 * prfill callback क्रम prपूर्णांकing a bfq_stat.
 */
अटल u64 blkg_prfill_stat(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
		पूर्णांक off)
अणु
	वापस __blkg_prfill_u64(sf, pd, bfq_stat_पढ़ो((व्योम *)pd + off));
पूर्ण

/* bfqg stats flags */
क्रमागत bfqg_stats_flags अणु
	BFQG_stats_रुकोing = 0,
	BFQG_stats_idling,
	BFQG_stats_empty,
पूर्ण;

#घोषणा BFQG_FLAG_FNS(name)						\
अटल व्योम bfqg_stats_mark_##name(काष्ठा bfqg_stats *stats)	\
अणु									\
	stats->flags |= (1 << BFQG_stats_##name);			\
पूर्ण									\
अटल व्योम bfqg_stats_clear_##name(काष्ठा bfqg_stats *stats)	\
अणु									\
	stats->flags &= ~(1 << BFQG_stats_##name);			\
पूर्ण									\
अटल पूर्णांक bfqg_stats_##name(काष्ठा bfqg_stats *stats)		\
अणु									\
	वापस (stats->flags & (1 << BFQG_stats_##name)) != 0;		\
पूर्ण									\

BFQG_FLAG_FNS(रुकोing)
BFQG_FLAG_FNS(idling)
BFQG_FLAG_FNS(empty)
#अघोषित BFQG_FLAG_FNS

/* This should be called with the scheduler lock held. */
अटल व्योम bfqg_stats_update_group_रुको_समय(काष्ठा bfqg_stats *stats)
अणु
	u64 now;

	अगर (!bfqg_stats_रुकोing(stats))
		वापस;

	now = kसमय_get_ns();
	अगर (now > stats->start_group_रुको_समय)
		bfq_stat_add(&stats->group_रुको_समय,
			      now - stats->start_group_रुको_समय);
	bfqg_stats_clear_रुकोing(stats);
पूर्ण

/* This should be called with the scheduler lock held. */
अटल व्योम bfqg_stats_set_start_group_रुको_समय(काष्ठा bfq_group *bfqg,
						 काष्ठा bfq_group *curr_bfqg)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;

	अगर (bfqg_stats_रुकोing(stats))
		वापस;
	अगर (bfqg == curr_bfqg)
		वापस;
	stats->start_group_रुको_समय = kसमय_get_ns();
	bfqg_stats_mark_रुकोing(stats);
पूर्ण

/* This should be called with the scheduler lock held. */
अटल व्योम bfqg_stats_end_empty_समय(काष्ठा bfqg_stats *stats)
अणु
	u64 now;

	अगर (!bfqg_stats_empty(stats))
		वापस;

	now = kसमय_get_ns();
	अगर (now > stats->start_empty_समय)
		bfq_stat_add(&stats->empty_समय,
			      now - stats->start_empty_समय);
	bfqg_stats_clear_empty(stats);
पूर्ण

व्योम bfqg_stats_update_dequeue(काष्ठा bfq_group *bfqg)
अणु
	bfq_stat_add(&bfqg->stats.dequeue, 1);
पूर्ण

व्योम bfqg_stats_set_start_empty_समय(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;

	अगर (blkg_rwstat_total(&stats->queued))
		वापस;

	/*
	 * group is alपढ़ोy marked empty. This can happen अगर bfqq got new
	 * request in parent group and moved to this group जबतक being added
	 * to service tree. Just ignore the event and move on.
	 */
	अगर (bfqg_stats_empty(stats))
		वापस;

	stats->start_empty_समय = kसमय_get_ns();
	bfqg_stats_mark_empty(stats);
पूर्ण

व्योम bfqg_stats_update_idle_समय(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;

	अगर (bfqg_stats_idling(stats)) अणु
		u64 now = kसमय_get_ns();

		अगर (now > stats->start_idle_समय)
			bfq_stat_add(&stats->idle_समय,
				      now - stats->start_idle_समय);
		bfqg_stats_clear_idling(stats);
	पूर्ण
पूर्ण

व्योम bfqg_stats_set_start_idle_समय(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;

	stats->start_idle_समय = kसमय_get_ns();
	bfqg_stats_mark_idling(stats);
पूर्ण

व्योम bfqg_stats_update_avg_queue_size(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;

	bfq_stat_add(&stats->avg_queue_size_sum,
		      blkg_rwstat_total(&stats->queued));
	bfq_stat_add(&stats->avg_queue_size_samples, 1);
	bfqg_stats_update_group_रुको_समय(stats);
पूर्ण

व्योम bfqg_stats_update_io_add(काष्ठा bfq_group *bfqg, काष्ठा bfq_queue *bfqq,
			      अचिन्हित पूर्णांक op)
अणु
	blkg_rwstat_add(&bfqg->stats.queued, op, 1);
	bfqg_stats_end_empty_समय(&bfqg->stats);
	अगर (!(bfqq == ((काष्ठा bfq_data *)bfqg->bfqd)->in_service_queue))
		bfqg_stats_set_start_group_रुको_समय(bfqg, bfqq_group(bfqq));
पूर्ण

व्योम bfqg_stats_update_io_हटाओ(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op)
अणु
	blkg_rwstat_add(&bfqg->stats.queued, op, -1);
पूर्ण

व्योम bfqg_stats_update_io_merged(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op)
अणु
	blkg_rwstat_add(&bfqg->stats.merged, op, 1);
पूर्ण

व्योम bfqg_stats_update_completion(काष्ठा bfq_group *bfqg, u64 start_समय_ns,
				  u64 io_start_समय_ns, अचिन्हित पूर्णांक op)
अणु
	काष्ठा bfqg_stats *stats = &bfqg->stats;
	u64 now = kसमय_get_ns();

	अगर (now > io_start_समय_ns)
		blkg_rwstat_add(&stats->service_समय, op,
				now - io_start_समय_ns);
	अगर (io_start_समय_ns > start_समय_ns)
		blkg_rwstat_add(&stats->रुको_समय, op,
				io_start_समय_ns - start_समय_ns);
पूर्ण

#अन्यथा /* CONFIG_BFQ_CGROUP_DEBUG */

व्योम bfqg_stats_update_io_add(काष्ठा bfq_group *bfqg, काष्ठा bfq_queue *bfqq,
			      अचिन्हित पूर्णांक op) अणु पूर्ण
व्योम bfqg_stats_update_io_हटाओ(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op) अणु पूर्ण
व्योम bfqg_stats_update_io_merged(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op) अणु पूर्ण
व्योम bfqg_stats_update_completion(काष्ठा bfq_group *bfqg, u64 start_समय_ns,
				  u64 io_start_समय_ns, अचिन्हित पूर्णांक op) अणु पूर्ण
व्योम bfqg_stats_update_dequeue(काष्ठा bfq_group *bfqg) अणु पूर्ण
व्योम bfqg_stats_set_start_empty_समय(काष्ठा bfq_group *bfqg) अणु पूर्ण
व्योम bfqg_stats_update_idle_समय(काष्ठा bfq_group *bfqg) अणु पूर्ण
व्योम bfqg_stats_set_start_idle_समय(काष्ठा bfq_group *bfqg) अणु पूर्ण
व्योम bfqg_stats_update_avg_queue_size(काष्ठा bfq_group *bfqg) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED

/*
 * blk-cgroup policy-related handlers
 * The following functions help in converting between blk-cgroup
 * पूर्णांकernal काष्ठाures and BFQ-specअगरic काष्ठाures.
 */

अटल काष्ठा bfq_group *pd_to_bfqg(काष्ठा blkg_policy_data *pd)
अणु
	वापस pd ? container_of(pd, काष्ठा bfq_group, pd) : शून्य;
पूर्ण

काष्ठा blkcg_gq *bfqg_to_blkg(काष्ठा bfq_group *bfqg)
अणु
	वापस pd_to_blkg(&bfqg->pd);
पूर्ण

अटल काष्ठा bfq_group *blkg_to_bfqg(काष्ठा blkcg_gq *blkg)
अणु
	वापस pd_to_bfqg(blkg_to_pd(blkg, &blkcg_policy_bfq));
पूर्ण

/*
 * bfq_group handlers
 * The following functions help in navigating the bfq_group hierarchy
 * by allowing to find the parent of a bfq_group or the bfq_group
 * associated to a bfq_queue.
 */

अटल काष्ठा bfq_group *bfqg_parent(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा blkcg_gq *pblkg = bfqg_to_blkg(bfqg)->parent;

	वापस pblkg ? blkg_to_bfqg(pblkg) : शून्य;
पूर्ण

काष्ठा bfq_group *bfqq_group(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *group_entity = bfqq->entity.parent;

	वापस group_entity ? container_of(group_entity, काष्ठा bfq_group,
					   entity) :
			      bfqq->bfqd->root_group;
पूर्ण

/*
 * The following two functions handle get and put of a bfq_group by
 * wrapping the related blk-cgroup hooks.
 */

अटल व्योम bfqg_get(काष्ठा bfq_group *bfqg)
अणु
	bfqg->ref++;
पूर्ण

अटल व्योम bfqg_put(काष्ठा bfq_group *bfqg)
अणु
	bfqg->ref--;

	अगर (bfqg->ref == 0)
		kमुक्त(bfqg);
पूर्ण

अटल व्योम bfqg_and_blkg_get(काष्ठा bfq_group *bfqg)
अणु
	/* see comments in bfq_bic_update_cgroup क्रम why refcounting bfqg */
	bfqg_get(bfqg);

	blkg_get(bfqg_to_blkg(bfqg));
पूर्ण

व्योम bfqg_and_blkg_put(काष्ठा bfq_group *bfqg)
अणु
	blkg_put(bfqg_to_blkg(bfqg));

	bfqg_put(bfqg);
पूर्ण

व्योम bfqg_stats_update_legacy_io(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा bfq_group *bfqg = blkg_to_bfqg(rq->bio->bi_blkg);

	अगर (!bfqg)
		वापस;

	blkg_rwstat_add(&bfqg->stats.bytes, rq->cmd_flags, blk_rq_bytes(rq));
	blkg_rwstat_add(&bfqg->stats.ios, rq->cmd_flags, 1);
पूर्ण

/* @stats = 0 */
अटल व्योम bfqg_stats_reset(काष्ठा bfqg_stats *stats)
अणु
#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	/* queued stats shouldn't be cleared */
	blkg_rwstat_reset(&stats->merged);
	blkg_rwstat_reset(&stats->service_समय);
	blkg_rwstat_reset(&stats->रुको_समय);
	bfq_stat_reset(&stats->समय);
	bfq_stat_reset(&stats->avg_queue_size_sum);
	bfq_stat_reset(&stats->avg_queue_size_samples);
	bfq_stat_reset(&stats->dequeue);
	bfq_stat_reset(&stats->group_रुको_समय);
	bfq_stat_reset(&stats->idle_समय);
	bfq_stat_reset(&stats->empty_समय);
#पूर्ण_अगर
पूर्ण

/* @to += @from */
अटल व्योम bfqg_stats_add_aux(काष्ठा bfqg_stats *to, काष्ठा bfqg_stats *from)
अणु
	अगर (!to || !from)
		वापस;

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	/* queued stats shouldn't be cleared */
	blkg_rwstat_add_aux(&to->merged, &from->merged);
	blkg_rwstat_add_aux(&to->service_समय, &from->service_समय);
	blkg_rwstat_add_aux(&to->रुको_समय, &from->रुको_समय);
	bfq_stat_add_aux(&from->समय, &from->समय);
	bfq_stat_add_aux(&to->avg_queue_size_sum, &from->avg_queue_size_sum);
	bfq_stat_add_aux(&to->avg_queue_size_samples,
			  &from->avg_queue_size_samples);
	bfq_stat_add_aux(&to->dequeue, &from->dequeue);
	bfq_stat_add_aux(&to->group_रुको_समय, &from->group_रुको_समय);
	bfq_stat_add_aux(&to->idle_समय, &from->idle_समय);
	bfq_stat_add_aux(&to->empty_समय, &from->empty_समय);
#पूर्ण_अगर
पूर्ण

/*
 * Transfer @bfqg's stats to its parent's aux counts so that the ancestors'
 * recursive stats can still account क्रम the amount used by this bfqg after
 * it's gone.
 */
अटल व्योम bfqg_stats_xfer_dead(काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfq_group *parent;

	अगर (!bfqg) /* root_group */
		वापस;

	parent = bfqg_parent(bfqg);

	lockdep_निश्चित_held(&bfqg_to_blkg(bfqg)->q->queue_lock);

	अगर (unlikely(!parent))
		वापस;

	bfqg_stats_add_aux(&parent->stats, &bfqg->stats);
	bfqg_stats_reset(&bfqg->stats);
पूर्ण

व्योम bfq_init_entity(काष्ठा bfq_entity *entity, काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->weight = entity->new_weight;
	entity->orig_weight = entity->new_weight;
	अगर (bfqq) अणु
		bfqq->ioprio = bfqq->new_ioprio;
		bfqq->ioprio_class = bfqq->new_ioprio_class;
		/*
		 * Make sure that bfqg and its associated blkg करो not
		 * disappear beक्रमe entity.
		 */
		bfqg_and_blkg_get(bfqg);
	पूर्ण
	entity->parent = bfqg->my_entity; /* शून्य क्रम root group */
	entity->sched_data = &bfqg->sched_data;
पूर्ण

अटल व्योम bfqg_stats_निकास(काष्ठा bfqg_stats *stats)
अणु
	blkg_rwstat_निकास(&stats->bytes);
	blkg_rwstat_निकास(&stats->ios);
#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	blkg_rwstat_निकास(&stats->merged);
	blkg_rwstat_निकास(&stats->service_समय);
	blkg_rwstat_निकास(&stats->रुको_समय);
	blkg_rwstat_निकास(&stats->queued);
	bfq_stat_निकास(&stats->समय);
	bfq_stat_निकास(&stats->avg_queue_size_sum);
	bfq_stat_निकास(&stats->avg_queue_size_samples);
	bfq_stat_निकास(&stats->dequeue);
	bfq_stat_निकास(&stats->group_रुको_समय);
	bfq_stat_निकास(&stats->idle_समय);
	bfq_stat_निकास(&stats->empty_समय);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bfqg_stats_init(काष्ठा bfqg_stats *stats, gfp_t gfp)
अणु
	अगर (blkg_rwstat_init(&stats->bytes, gfp) ||
	    blkg_rwstat_init(&stats->ios, gfp))
		वापस -ENOMEM;

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	अगर (blkg_rwstat_init(&stats->merged, gfp) ||
	    blkg_rwstat_init(&stats->service_समय, gfp) ||
	    blkg_rwstat_init(&stats->रुको_समय, gfp) ||
	    blkg_rwstat_init(&stats->queued, gfp) ||
	    bfq_stat_init(&stats->समय, gfp) ||
	    bfq_stat_init(&stats->avg_queue_size_sum, gfp) ||
	    bfq_stat_init(&stats->avg_queue_size_samples, gfp) ||
	    bfq_stat_init(&stats->dequeue, gfp) ||
	    bfq_stat_init(&stats->group_रुको_समय, gfp) ||
	    bfq_stat_init(&stats->idle_समय, gfp) ||
	    bfq_stat_init(&stats->empty_समय, gfp)) अणु
		bfqg_stats_निकास(stats);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा bfq_group_data *cpd_to_bfqgd(काष्ठा blkcg_policy_data *cpd)
अणु
	वापस cpd ? container_of(cpd, काष्ठा bfq_group_data, pd) : शून्य;
पूर्ण

अटल काष्ठा bfq_group_data *blkcg_to_bfqgd(काष्ठा blkcg *blkcg)
अणु
	वापस cpd_to_bfqgd(blkcg_to_cpd(blkcg, &blkcg_policy_bfq));
पूर्ण

अटल काष्ठा blkcg_policy_data *bfq_cpd_alloc(gfp_t gfp)
अणु
	काष्ठा bfq_group_data *bgd;

	bgd = kzalloc(माप(*bgd), gfp);
	अगर (!bgd)
		वापस शून्य;
	वापस &bgd->pd;
पूर्ण

अटल व्योम bfq_cpd_init(काष्ठा blkcg_policy_data *cpd)
अणु
	काष्ठा bfq_group_data *d = cpd_to_bfqgd(cpd);

	d->weight = cgroup_subsys_on_dfl(io_cgrp_subsys) ?
		CGROUP_WEIGHT_DFL : BFQ_WEIGHT_LEGACY_DFL;
पूर्ण

अटल व्योम bfq_cpd_मुक्त(काष्ठा blkcg_policy_data *cpd)
अणु
	kमुक्त(cpd_to_bfqgd(cpd));
पूर्ण

अटल काष्ठा blkg_policy_data *bfq_pd_alloc(gfp_t gfp, काष्ठा request_queue *q,
					     काष्ठा blkcg *blkcg)
अणु
	काष्ठा bfq_group *bfqg;

	bfqg = kzalloc_node(माप(*bfqg), gfp, q->node);
	अगर (!bfqg)
		वापस शून्य;

	अगर (bfqg_stats_init(&bfqg->stats, gfp)) अणु
		kमुक्त(bfqg);
		वापस शून्य;
	पूर्ण

	/* see comments in bfq_bic_update_cgroup क्रम why refcounting */
	bfqg_get(bfqg);
	वापस &bfqg->pd;
पूर्ण

अटल व्योम bfq_pd_init(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा blkcg_gq *blkg = pd_to_blkg(pd);
	काष्ठा bfq_group *bfqg = blkg_to_bfqg(blkg);
	काष्ठा bfq_data *bfqd = blkg->q->elevator->elevator_data;
	काष्ठा bfq_entity *entity = &bfqg->entity;
	काष्ठा bfq_group_data *d = blkcg_to_bfqgd(blkg->blkcg);

	entity->orig_weight = entity->weight = entity->new_weight = d->weight;
	entity->my_sched_data = &bfqg->sched_data;
	entity->last_bfqq_created = शून्य;

	bfqg->my_entity = entity; /*
				   * the root_group's will be set to शून्य
				   * in bfq_init_queue()
				   */
	bfqg->bfqd = bfqd;
	bfqg->active_entities = 0;
	bfqg->rq_pos_tree = RB_ROOT;
पूर्ण

अटल व्योम bfq_pd_मुक्त(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा bfq_group *bfqg = pd_to_bfqg(pd);

	bfqg_stats_निकास(&bfqg->stats);
	bfqg_put(bfqg);
पूर्ण

अटल व्योम bfq_pd_reset_stats(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा bfq_group *bfqg = pd_to_bfqg(pd);

	bfqg_stats_reset(&bfqg->stats);
पूर्ण

अटल व्योम bfq_group_set_parent(काष्ठा bfq_group *bfqg,
					काष्ठा bfq_group *parent)
अणु
	काष्ठा bfq_entity *entity;

	entity = &bfqg->entity;
	entity->parent = parent->my_entity;
	entity->sched_data = &parent->sched_data;
पूर्ण

अटल काष्ठा bfq_group *bfq_lookup_bfqg(काष्ठा bfq_data *bfqd,
					 काष्ठा blkcg *blkcg)
अणु
	काष्ठा blkcg_gq *blkg;

	blkg = blkg_lookup(blkcg, bfqd->queue);
	अगर (likely(blkg))
		वापस blkg_to_bfqg(blkg);
	वापस शून्य;
पूर्ण

काष्ठा bfq_group *bfq_find_set_group(काष्ठा bfq_data *bfqd,
				     काष्ठा blkcg *blkcg)
अणु
	काष्ठा bfq_group *bfqg, *parent;
	काष्ठा bfq_entity *entity;

	bfqg = bfq_lookup_bfqg(bfqd, blkcg);

	अगर (unlikely(!bfqg))
		वापस शून्य;

	/*
	 * Update chain of bfq_groups as we might be handling a leaf group
	 * which, aदीर्घ with some of its relatives, has not been hooked yet
	 * to the निजी hierarchy of BFQ.
	 */
	entity = &bfqg->entity;
	क्रम_each_entity(entity) अणु
		काष्ठा bfq_group *curr_bfqg = container_of(entity,
						काष्ठा bfq_group, entity);
		अगर (curr_bfqg != bfqd->root_group) अणु
			parent = bfqg_parent(curr_bfqg);
			अगर (!parent)
				parent = bfqd->root_group;
			bfq_group_set_parent(curr_bfqg, parent);
		पूर्ण
	पूर्ण

	वापस bfqg;
पूर्ण

/**
 * bfq_bfqq_move - migrate @bfqq to @bfqg.
 * @bfqd: queue descriptor.
 * @bfqq: the queue to move.
 * @bfqg: the group to move to.
 *
 * Move @bfqq to @bfqg, deactivating it from its old group and reactivating
 * it on the new one.  Aव्योम putting the entity on the old group idle tree.
 *
 * Must be called under the scheduler lock, to make sure that the blkg
 * owning @bfqg करोes not disappear (see comments in
 * bfq_bic_update_cgroup on guaranteeing the consistency of blkg
 * objects).
 */
व्योम bfq_bfqq_move(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		   काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	/*
	 * Get extra reference to prevent bfqq from being मुक्तd in
	 * next possible expire or deactivate.
	 */
	bfqq->ref++;

	/* If bfqq is empty, then bfq_bfqq_expire also invokes
	 * bfq_del_bfqq_busy, thereby removing bfqq and its entity
	 * from data काष्ठाures related to current group. Otherwise we
	 * need to हटाओ bfqq explicitly with bfq_deactivate_bfqq, as
	 * we करो below.
	 */
	अगर (bfqq == bfqd->in_service_queue)
		bfq_bfqq_expire(bfqd, bfqd->in_service_queue,
				false, BFQQE_PREEMPTED);

	अगर (bfq_bfqq_busy(bfqq))
		bfq_deactivate_bfqq(bfqd, bfqq, false, false);
	अन्यथा अगर (entity->on_st_or_in_serv)
		bfq_put_idle_entity(bfq_entity_service_tree(entity), entity);
	bfqg_and_blkg_put(bfqq_group(bfqq));

	entity->parent = bfqg->my_entity;
	entity->sched_data = &bfqg->sched_data;
	/* pin करोwn bfqg and its associated blkg  */
	bfqg_and_blkg_get(bfqg);

	अगर (bfq_bfqq_busy(bfqq)) अणु
		अगर (unlikely(!bfqd->nonrot_with_queueing))
			bfq_pos_tree_add_move(bfqd, bfqq);
		bfq_activate_bfqq(bfqd, bfqq);
	पूर्ण

	अगर (!bfqd->in_service_queue && !bfqd->rq_in_driver)
		bfq_schedule_dispatch(bfqd);
	/* release extra ref taken above, bfqq may happen to be मुक्तd now */
	bfq_put_queue(bfqq);
पूर्ण

/**
 * __bfq_bic_change_cgroup - move @bic to @cgroup.
 * @bfqd: the queue descriptor.
 * @bic: the bic to move.
 * @blkcg: the blk-cgroup to move to.
 *
 * Move bic to blkcg, assuming that bfqd->lock is held; which makes
 * sure that the reference to cgroup is valid across the call (see
 * comments in bfq_bic_update_cgroup on this issue)
 *
 * NOTE: an alternative approach might have been to store the current
 * cgroup in bfqq and getting a reference to it, reducing the lookup
 * समय here, at the price of slightly more complex code.
 */
अटल काष्ठा bfq_group *__bfq_bic_change_cgroup(काष्ठा bfq_data *bfqd,
						काष्ठा bfq_io_cq *bic,
						काष्ठा blkcg *blkcg)
अणु
	काष्ठा bfq_queue *async_bfqq = bic_to_bfqq(bic, 0);
	काष्ठा bfq_queue *sync_bfqq = bic_to_bfqq(bic, 1);
	काष्ठा bfq_group *bfqg;
	काष्ठा bfq_entity *entity;

	bfqg = bfq_find_set_group(bfqd, blkcg);

	अगर (unlikely(!bfqg))
		bfqg = bfqd->root_group;

	अगर (async_bfqq) अणु
		entity = &async_bfqq->entity;

		अगर (entity->sched_data != &bfqg->sched_data) अणु
			bic_set_bfqq(bic, शून्य, 0);
			bfq_release_process_ref(bfqd, async_bfqq);
		पूर्ण
	पूर्ण

	अगर (sync_bfqq) अणु
		entity = &sync_bfqq->entity;
		अगर (entity->sched_data != &bfqg->sched_data)
			bfq_bfqq_move(bfqd, sync_bfqq, bfqg);
	पूर्ण

	वापस bfqg;
पूर्ण

व्योम bfq_bic_update_cgroup(काष्ठा bfq_io_cq *bic, काष्ठा bio *bio)
अणु
	काष्ठा bfq_data *bfqd = bic_to_bfqd(bic);
	काष्ठा bfq_group *bfqg = शून्य;
	uपूर्णांक64_t serial_nr;

	rcu_पढ़ो_lock();
	serial_nr = __bio_blkcg(bio)->css.serial_nr;

	/*
	 * Check whether blkcg has changed.  The condition may trigger
	 * spuriously on a newly created cic but there's no harm.
	 */
	अगर (unlikely(!bfqd) || likely(bic->blkcg_serial_nr == serial_nr))
		जाओ out;

	bfqg = __bfq_bic_change_cgroup(bfqd, bic, __bio_blkcg(bio));
	/*
	 * Update blkg_path क्रम bfq_log_* functions. We cache this
	 * path, and update it here, क्रम the following
	 * reasons. Operations on blkg objects in blk-cgroup are
	 * रक्षित with the request_queue lock, and not with the
	 * lock that protects the instances of this scheduler
	 * (bfqd->lock). This exposes BFQ to the following sort of
	 * race.
	 *
	 * The blkg_lookup perक्रमmed in bfq_get_queue, रक्षित
	 * through rcu, may happen to वापस the address of a copy of
	 * the original blkg. If this is the हाल, then the
	 * bfqg_and_blkg_get perक्रमmed in bfq_get_queue, to pin करोwn
	 * the blkg, is useless: it करोes not prevent blk-cgroup code
	 * from destroying both the original blkg and all objects
	 * directly or indirectly referred by the copy of the
	 * blkg.
	 *
	 * On the bright side, destroy operations on a blkg invoke, as
	 * a first step, hooks of the scheduler associated with the
	 * blkg. And these hooks are executed with bfqd->lock held क्रम
	 * BFQ. As a consequence, क्रम any blkg associated with the
	 * request queue this instance of the scheduler is attached
	 * to, we are guaranteed that such a blkg is not destroyed, and
	 * that all the poपूर्णांकers it contains are consistent, जबतक we
	 * are holding bfqd->lock. A blkg_lookup perक्रमmed with
	 * bfqd->lock held then वापसs a fully consistent blkg, which
	 * reमुख्यs consistent until this lock is held.
	 *
	 * Thanks to the last fact, and to the fact that: (1) bfqg has
	 * been obtained through a blkg_lookup in the above
	 * assignment, and (2) bfqd->lock is being held, here we can
	 * safely use the policy data क्रम the involved blkg (i.e., the
	 * field bfqg->pd) to get to the blkg associated with bfqg,
	 * and then we can safely use any field of blkg. After we
	 * release bfqd->lock, even just getting blkg through this
	 * bfqg may cause dangling references to be traversed, as
	 * bfqg->pd may not exist any more.
	 *
	 * In view of the above facts, here we cache, in the bfqg, any
	 * blkg data we may need क्रम this bic, and क्रम its associated
	 * bfq_queue. As of now, we need to cache only the path of the
	 * blkg, which is used in the bfq_log_* functions.
	 *
	 * Finally, note that bfqg itself needs to be रक्षित from
	 * deकाष्ठाion on the blkg_मुक्त of the original blkg (which
	 * invokes bfq_pd_मुक्त). We use an additional निजी
	 * refcounter क्रम bfqg, to let it disappear only after no
	 * bfq_queue refers to it any दीर्घer.
	 */
	blkg_path(bfqg_to_blkg(bfqg), bfqg->blkg_path, माप(bfqg->blkg_path));
	bic->blkcg_serial_nr = serial_nr;
out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * bfq_flush_idle_tree - deactivate any entity on the idle tree of @st.
 * @st: the service tree being flushed.
 */
अटल व्योम bfq_flush_idle_tree(काष्ठा bfq_service_tree *st)
अणु
	काष्ठा bfq_entity *entity = st->first_idle;

	क्रम (; entity ; entity = st->first_idle)
		__bfq_deactivate_entity(entity, false);
पूर्ण

/**
 * bfq_reparent_leaf_entity - move leaf entity to the root_group.
 * @bfqd: the device data काष्ठाure with the root group.
 * @entity: the entity to move, अगर entity is a leaf; or the parent entity
 *	    of an active leaf entity to move, अगर entity is not a leaf.
 */
अटल व्योम bfq_reparent_leaf_entity(काष्ठा bfq_data *bfqd,
				     काष्ठा bfq_entity *entity,
				     पूर्णांक ioprio_class)
अणु
	काष्ठा bfq_queue *bfqq;
	काष्ठा bfq_entity *child_entity = entity;

	जबतक (child_entity->my_sched_data) अणु /* leaf not reached yet */
		काष्ठा bfq_sched_data *child_sd = child_entity->my_sched_data;
		काष्ठा bfq_service_tree *child_st = child_sd->service_tree +
			ioprio_class;
		काष्ठा rb_root *child_active = &child_st->active;

		child_entity = bfq_entity_of(rb_first(child_active));

		अगर (!child_entity)
			child_entity = child_sd->in_service_entity;
	पूर्ण

	bfqq = bfq_entity_to_bfqq(child_entity);
	bfq_bfqq_move(bfqd, bfqq, bfqd->root_group);
पूर्ण

/**
 * bfq_reparent_active_queues - move to the root group all active queues.
 * @bfqd: the device data काष्ठाure with the root group.
 * @bfqg: the group to move from.
 * @st: the service tree to start the search from.
 */
अटल व्योम bfq_reparent_active_queues(काष्ठा bfq_data *bfqd,
				       काष्ठा bfq_group *bfqg,
				       काष्ठा bfq_service_tree *st,
				       पूर्णांक ioprio_class)
अणु
	काष्ठा rb_root *active = &st->active;
	काष्ठा bfq_entity *entity;

	जबतक ((entity = bfq_entity_of(rb_first(active))))
		bfq_reparent_leaf_entity(bfqd, entity, ioprio_class);

	अगर (bfqg->sched_data.in_service_entity)
		bfq_reparent_leaf_entity(bfqd,
					 bfqg->sched_data.in_service_entity,
					 ioprio_class);
पूर्ण

/**
 * bfq_pd_offline - deactivate the entity associated with @pd,
 *		    and reparent its children entities.
 * @pd: descriptor of the policy going offline.
 *
 * blkio alपढ़ोy grअसल the queue_lock क्रम us, so no need to use
 * RCU-based magic
 */
अटल व्योम bfq_pd_offline(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा bfq_service_tree *st;
	काष्ठा bfq_group *bfqg = pd_to_bfqg(pd);
	काष्ठा bfq_data *bfqd = bfqg->bfqd;
	काष्ठा bfq_entity *entity = bfqg->my_entity;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&bfqd->lock, flags);

	अगर (!entity) /* root group */
		जाओ put_async_queues;

	/*
	 * Empty all service_trees beदीर्घing to this group beक्रमe
	 * deactivating the group itself.
	 */
	क्रम (i = 0; i < BFQ_IOPRIO_CLASSES; i++) अणु
		st = bfqg->sched_data.service_tree + i;

		/*
		 * It may happen that some queues are still active
		 * (busy) upon group deकाष्ठाion (अगर the corresponding
		 * processes have been क्रमced to terminate). We move
		 * all the leaf entities corresponding to these queues
		 * to the root_group.
		 * Also, it may happen that the group has an entity
		 * in service, which is disconnected from the active
		 * tree: it must be moved, too.
		 * There is no need to put the sync queues, as the
		 * scheduler has taken no reference.
		 */
		bfq_reparent_active_queues(bfqd, bfqg, st, i);

		/*
		 * The idle tree may still contain bfq_queues
		 * beदीर्घing to निकासed task because they never
		 * migrated to a dअगरferent cgroup from the one being
		 * destroyed now. In addition, even
		 * bfq_reparent_active_queues() may happen to add some
		 * entities to the idle tree. It happens अगर, in some
		 * of the calls to bfq_bfqq_move() perक्रमmed by
		 * bfq_reparent_active_queues(), the queue to move is
		 * empty and माला_लो expired.
		 */
		bfq_flush_idle_tree(st);
	पूर्ण

	__bfq_deactivate_entity(entity, false);

put_async_queues:
	bfq_put_async_queues(bfqd, bfqg);

	spin_unlock_irqrestore(&bfqd->lock, flags);
	/*
	 * @blkg is going offline and will be ignored by
	 * blkg_[rw]stat_recursive_sum().  Transfer stats to the parent so
	 * that they करोn't get lost.  If IOs complete after this poपूर्णांक, the
	 * stats क्रम them will be lost.  Oh well...
	 */
	bfqg_stats_xfer_dead(bfqg);
पूर्ण

व्योम bfq_end_wr_async(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा blkcg_gq *blkg;

	list_क्रम_each_entry(blkg, &bfqd->queue->blkg_list, q_node) अणु
		काष्ठा bfq_group *bfqg = blkg_to_bfqg(blkg);

		bfq_end_wr_async_queues(bfqd, bfqg);
	पूर्ण
	bfq_end_wr_async_queues(bfqd, bfqd->root_group);
पूर्ण

अटल पूर्णांक bfq_io_show_weight_legacy(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));
	काष्ठा bfq_group_data *bfqgd = blkcg_to_bfqgd(blkcg);
	अचिन्हित पूर्णांक val = 0;

	अगर (bfqgd)
		val = bfqgd->weight;

	seq_म_लिखो(sf, "%u\n", val);

	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_weight_device(काष्ठा seq_file *sf,
				     काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा bfq_group *bfqg = pd_to_bfqg(pd);

	अगर (!bfqg->entity.dev_weight)
		वापस 0;
	वापस __blkg_prfill_u64(sf, pd, bfqg->entity.dev_weight);
पूर्ण

अटल पूर्णांक bfq_io_show_weight(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));
	काष्ठा bfq_group_data *bfqgd = blkcg_to_bfqgd(blkcg);

	seq_म_लिखो(sf, "default %u\n", bfqgd->weight);
	blkcg_prपूर्णांक_blkgs(sf, blkcg, bfqg_prfill_weight_device,
			  &blkcg_policy_bfq, 0, false);
	वापस 0;
पूर्ण

अटल व्योम bfq_group_set_weight(काष्ठा bfq_group *bfqg, u64 weight, u64 dev_weight)
अणु
	weight = dev_weight ?: weight;

	bfqg->entity.dev_weight = dev_weight;
	/*
	 * Setting the prio_changed flag of the entity
	 * to 1 with new_weight == weight would re-set
	 * the value of the weight to its ioprio mapping.
	 * Set the flag only अगर necessary.
	 */
	अगर ((अचिन्हित लघु)weight != bfqg->entity.new_weight) अणु
		bfqg->entity.new_weight = (अचिन्हित लघु)weight;
		/*
		 * Make sure that the above new value has been
		 * stored in bfqg->entity.new_weight beक्रमe
		 * setting the prio_changed flag. In fact,
		 * this flag may be पढ़ो asynchronously (in
		 * critical sections रक्षित by a dअगरferent
		 * lock than that held here), and finding this
		 * flag set may cause the execution of the code
		 * क्रम updating parameters whose value may
		 * depend also on bfqg->entity.new_weight (in
		 * __bfq_entity_update_weight_prio).
		 * This barrier makes sure that the new value
		 * of bfqg->entity.new_weight is correctly
		 * seen in that code.
		 */
		smp_wmb();
		bfqg->entity.prio_changed = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक bfq_io_set_weight_legacy(काष्ठा cgroup_subsys_state *css,
				    काष्ठा cftype *cftype,
				    u64 val)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);
	काष्ठा bfq_group_data *bfqgd = blkcg_to_bfqgd(blkcg);
	काष्ठा blkcg_gq *blkg;
	पूर्णांक ret = -दुस्फल;

	अगर (val < BFQ_MIN_WEIGHT || val > BFQ_MAX_WEIGHT)
		वापस ret;

	ret = 0;
	spin_lock_irq(&blkcg->lock);
	bfqgd->weight = (अचिन्हित लघु)val;
	hlist_क्रम_each_entry(blkg, &blkcg->blkg_list, blkcg_node) अणु
		काष्ठा bfq_group *bfqg = blkg_to_bfqg(blkg);

		अगर (bfqg)
			bfq_group_set_weight(bfqg, val, 0);
	पूर्ण
	spin_unlock_irq(&blkcg->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार bfq_io_set_device_weight(काष्ठा kernfs_खोलो_file *of,
					अक्षर *buf, माप_प्रकार nbytes,
					loff_t off)
अणु
	पूर्णांक ret;
	काष्ठा blkg_conf_ctx ctx;
	काष्ठा blkcg *blkcg = css_to_blkcg(of_css(of));
	काष्ठा bfq_group *bfqg;
	u64 v;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_bfq, buf, &ctx);
	अगर (ret)
		वापस ret;

	अगर (माला_पूछो(ctx.body, "%llu", &v) == 1) अणु
		/* require "default" on dfl */
		ret = -दुस्फल;
		अगर (!v)
			जाओ out;
	पूर्ण अन्यथा अगर (!म_भेद(strim(ctx.body), "default")) अणु
		v = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	bfqg = blkg_to_bfqg(ctx.blkg);

	ret = -दुस्फल;
	अगर (!v || (v >= BFQ_MIN_WEIGHT && v <= BFQ_MAX_WEIGHT)) अणु
		bfq_group_set_weight(bfqg, bfqg->entity.weight, v);
		ret = 0;
	पूर्ण
out:
	blkg_conf_finish(&ctx);
	वापस ret ?: nbytes;
पूर्ण

अटल sमाप_प्रकार bfq_io_set_weight(काष्ठा kernfs_खोलो_file *of,
				 अक्षर *buf, माप_प्रकार nbytes,
				 loff_t off)
अणु
	अक्षर *endp;
	पूर्णांक ret;
	u64 v;

	buf = strim(buf);

	/* "WEIGHT" or "default WEIGHT" sets the शेष weight */
	v = simple_म_से_अदीर्घl(buf, &endp, 0);
	अगर (*endp == '\0' || माला_पूछो(buf, "default %llu", &v) == 1) अणु
		ret = bfq_io_set_weight_legacy(of_css(of), शून्य, v);
		वापस ret ?: nbytes;
	पूर्ण

	वापस bfq_io_set_device_weight(of, buf, nbytes, off);
पूर्ण

अटल पूर्णांक bfqg_prपूर्णांक_rwstat(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)), blkg_prfill_rwstat,
			  &blkcg_policy_bfq, seq_cft(sf)->निजी, true);
	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_rwstat_recursive(काष्ठा seq_file *sf,
					काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा blkg_rwstat_sample sum;

	blkg_rwstat_recursive_sum(pd_to_blkg(pd), &blkcg_policy_bfq, off, &sum);
	वापस __blkg_prfill_rwstat(sf, pd, &sum);
पूर्ण

अटल पूर्णांक bfqg_prपूर्णांक_rwstat_recursive(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  bfqg_prfill_rwstat_recursive, &blkcg_policy_bfq,
			  seq_cft(sf)->निजी, true);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
अटल पूर्णांक bfqg_prपूर्णांक_stat(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)), blkg_prfill_stat,
			  &blkcg_policy_bfq, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_stat_recursive(काष्ठा seq_file *sf,
				      काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा blkcg_gq *blkg = pd_to_blkg(pd);
	काष्ठा blkcg_gq *pos_blkg;
	काष्ठा cgroup_subsys_state *pos_css;
	u64 sum = 0;

	lockdep_निश्चित_held(&blkg->q->queue_lock);

	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_pre(pos_blkg, pos_css, blkg) अणु
		काष्ठा bfq_stat *stat;

		अगर (!pos_blkg->online)
			जारी;

		stat = (व्योम *)blkg_to_pd(pos_blkg, &blkcg_policy_bfq) + off;
		sum += bfq_stat_पढ़ो(stat) + atomic64_पढ़ो(&stat->aux_cnt);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस __blkg_prfill_u64(sf, pd, sum);
पूर्ण

अटल पूर्णांक bfqg_prपूर्णांक_stat_recursive(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  bfqg_prfill_stat_recursive, &blkcg_policy_bfq,
			  seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_sectors(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			       पूर्णांक off)
अणु
	काष्ठा bfq_group *bfqg = blkg_to_bfqg(pd->blkg);
	u64 sum = blkg_rwstat_total(&bfqg->stats.bytes);

	वापस __blkg_prfill_u64(sf, pd, sum >> 9);
पूर्ण

अटल पूर्णांक bfqg_prपूर्णांक_stat_sectors(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  bfqg_prfill_sectors, &blkcg_policy_bfq, 0, false);
	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_sectors_recursive(काष्ठा seq_file *sf,
					 काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा blkg_rwstat_sample पंचांगp;

	blkg_rwstat_recursive_sum(pd->blkg, &blkcg_policy_bfq,
			दुरत्व(काष्ठा bfq_group, stats.bytes), &पंचांगp);

	वापस __blkg_prfill_u64(sf, pd,
		(पंचांगp.cnt[BLKG_RWSTAT_READ] + पंचांगp.cnt[BLKG_RWSTAT_WRITE]) >> 9);
पूर्ण

अटल पूर्णांक bfqg_prपूर्णांक_stat_sectors_recursive(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  bfqg_prfill_sectors_recursive, &blkcg_policy_bfq, 0,
			  false);
	वापस 0;
पूर्ण

अटल u64 bfqg_prfill_avg_queue_size(काष्ठा seq_file *sf,
				      काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा bfq_group *bfqg = pd_to_bfqg(pd);
	u64 samples = bfq_stat_पढ़ो(&bfqg->stats.avg_queue_size_samples);
	u64 v = 0;

	अगर (samples) अणु
		v = bfq_stat_पढ़ो(&bfqg->stats.avg_queue_size_sum);
		v = भाग64_u64(v, samples);
	पूर्ण
	__blkg_prfill_u64(sf, pd, v);
	वापस 0;
पूर्ण

/* prपूर्णांक avg_queue_size */
अटल पूर्णांक bfqg_prपूर्णांक_avg_queue_size(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  bfqg_prfill_avg_queue_size, &blkcg_policy_bfq,
			  0, false);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */

काष्ठा bfq_group *bfq_create_group_hierarchy(काष्ठा bfq_data *bfqd, पूर्णांक node)
अणु
	पूर्णांक ret;

	ret = blkcg_activate_policy(bfqd->queue, &blkcg_policy_bfq);
	अगर (ret)
		वापस शून्य;

	वापस blkg_to_bfqg(bfqd->queue->root_blkg);
पूर्ण

काष्ठा blkcg_policy blkcg_policy_bfq = अणु
	.dfl_cftypes		= bfq_blkg_files,
	.legacy_cftypes		= bfq_blkcg_legacy_files,

	.cpd_alloc_fn		= bfq_cpd_alloc,
	.cpd_init_fn		= bfq_cpd_init,
	.cpd_bind_fn	        = bfq_cpd_init,
	.cpd_मुक्त_fn		= bfq_cpd_मुक्त,

	.pd_alloc_fn		= bfq_pd_alloc,
	.pd_init_fn		= bfq_pd_init,
	.pd_offline_fn		= bfq_pd_offline,
	.pd_मुक्त_fn		= bfq_pd_मुक्त,
	.pd_reset_stats_fn	= bfq_pd_reset_stats,
पूर्ण;

काष्ठा cftype bfq_blkcg_legacy_files[] = अणु
	अणु
		.name = "bfq.weight",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = bfq_io_show_weight_legacy,
		.ग_लिखो_u64 = bfq_io_set_weight_legacy,
	पूर्ण,
	अणु
		.name = "bfq.weight_device",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = bfq_io_show_weight,
		.ग_लिखो = bfq_io_set_weight,
	पूर्ण,

	/* statistics, covers only the tasks in the bfqg */
	अणु
		.name = "bfq.io_service_bytes",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.bytes),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "bfq.io_serviced",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.ios),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	अणु
		.name = "bfq.time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.समय),
		.seq_show = bfqg_prपूर्णांक_stat,
	पूर्ण,
	अणु
		.name = "bfq.sectors",
		.seq_show = bfqg_prपूर्णांक_stat_sectors,
	पूर्ण,
	अणु
		.name = "bfq.io_service_time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.service_समय),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "bfq.io_wait_time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.रुको_समय),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "bfq.io_merged",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.merged),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "bfq.io_queued",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.queued),
		.seq_show = bfqg_prपूर्णांक_rwstat,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */

	/* the same statistics which cover the bfqg and its descendants */
	अणु
		.name = "bfq.io_service_bytes_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.bytes),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.io_serviced_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.ios),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	अणु
		.name = "bfq.time_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.समय),
		.seq_show = bfqg_prपूर्णांक_stat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.sectors_recursive",
		.seq_show = bfqg_prपूर्णांक_stat_sectors_recursive,
	पूर्ण,
	अणु
		.name = "bfq.io_service_time_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.service_समय),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.io_wait_time_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.रुको_समय),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.io_merged_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.merged),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.io_queued_recursive",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.queued),
		.seq_show = bfqg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "bfq.avg_queue_size",
		.seq_show = bfqg_prपूर्णांक_avg_queue_size,
	पूर्ण,
	अणु
		.name = "bfq.group_wait_time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.group_रुको_समय),
		.seq_show = bfqg_prपूर्णांक_stat,
	पूर्ण,
	अणु
		.name = "bfq.idle_time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.idle_समय),
		.seq_show = bfqg_prपूर्णांक_stat,
	पूर्ण,
	अणु
		.name = "bfq.empty_time",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.empty_समय),
		.seq_show = bfqg_prपूर्णांक_stat,
	पूर्ण,
	अणु
		.name = "bfq.dequeue",
		.निजी = दुरत्व(काष्ठा bfq_group, stats.dequeue),
		.seq_show = bfqg_prपूर्णांक_stat,
	पूर्ण,
#पूर्ण_अगर	/* CONFIG_BFQ_CGROUP_DEBUG */
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cftype bfq_blkg_files[] = अणु
	अणु
		.name = "bfq.weight",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = bfq_io_show_weight,
		.ग_लिखो = bfq_io_set_weight,
	पूर्ण,
	अणुपूर्ण /* terminate */
पूर्ण;

#अन्यथा	/* CONFIG_BFQ_GROUP_IOSCHED */

व्योम bfq_bfqq_move(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		   काष्ठा bfq_group *bfqg) अणुपूर्ण

व्योम bfq_init_entity(काष्ठा bfq_entity *entity, काष्ठा bfq_group *bfqg)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->weight = entity->new_weight;
	entity->orig_weight = entity->new_weight;
	अगर (bfqq) अणु
		bfqq->ioprio = bfqq->new_ioprio;
		bfqq->ioprio_class = bfqq->new_ioprio_class;
	पूर्ण
	entity->sched_data = &bfqg->sched_data;
पूर्ण

व्योम bfq_bic_update_cgroup(काष्ठा bfq_io_cq *bic, काष्ठा bio *bio) अणुपूर्ण

व्योम bfq_end_wr_async(काष्ठा bfq_data *bfqd)
अणु
	bfq_end_wr_async_queues(bfqd, bfqd->root_group);
पूर्ण

काष्ठा bfq_group *bfq_find_set_group(काष्ठा bfq_data *bfqd, काष्ठा blkcg *blkcg)
अणु
	वापस bfqd->root_group;
पूर्ण

काष्ठा bfq_group *bfqq_group(काष्ठा bfq_queue *bfqq)
अणु
	वापस bfqq->bfqd->root_group;
पूर्ण

व्योम bfqg_and_blkg_get(काष्ठा bfq_group *bfqg) अणुपूर्ण

व्योम bfqg_and_blkg_put(काष्ठा bfq_group *bfqg) अणुपूर्ण

काष्ठा bfq_group *bfq_create_group_hierarchy(काष्ठा bfq_data *bfqd, पूर्णांक node)
अणु
	काष्ठा bfq_group *bfqg;
	पूर्णांक i;

	bfqg = kदो_स्मृति_node(माप(*bfqg), GFP_KERNEL | __GFP_ZERO, node);
	अगर (!bfqg)
		वापस शून्य;

	क्रम (i = 0; i < BFQ_IOPRIO_CLASSES; i++)
		bfqg->sched_data.service_tree[i] = BFQ_SERVICE_TREE_INIT;

	वापस bfqg;
पूर्ण
#पूर्ण_अगर	/* CONFIG_BFQ_GROUP_IOSCHED */
