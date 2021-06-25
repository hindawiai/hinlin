<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BLK_CGROUP_H
#घोषणा _BLK_CGROUP_H
/*
 * Common Block IO controller cgroup पूर्णांकerface
 *
 * Based on ideas and code from CFQ, CFS and BFQ:
 * Copyright (C) 2003 Jens Axboe <axboe@kernel.dk>
 *
 * Copyright (C) 2008 Fabio Checconi <fabio@gandalf.sssup.it>
 *		      Paolo Valente <paolo.valente@unimore.it>
 *
 * Copyright (C) 2009 Vivek Goyal <vgoyal@redhat.com>
 * 	              Nauman Rafique <nauman@google.com>
 */

#समावेश <linux/cgroup.h>
#समावेश <linux/percpu.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/fs.h>

/* percpu_counter batch क्रम blkg_[rw]stats, per-cpu drअगरt करोesn't matter */
#घोषणा BLKG_STAT_CPU_BATCH	(पूर्णांक_उच्च / 2)

/* Max limits क्रम throttle policy */
#घोषणा THROTL_IOPS_MAX		अच_पूर्णांक_उच्च

#अगर_घोषित CONFIG_BLK_CGROUP

क्रमागत blkg_iostat_type अणु
	BLKG_IOSTAT_READ,
	BLKG_IOSTAT_WRITE,
	BLKG_IOSTAT_DISCARD,

	BLKG_IOSTAT_NR,
पूर्ण;

काष्ठा blkcg_gq;

काष्ठा blkcg अणु
	काष्ठा cgroup_subsys_state	css;
	spinlock_t			lock;
	refcount_t			online_pin;

	काष्ठा radix_tree_root		blkg_tree;
	काष्ठा blkcg_gq	__rcu		*blkg_hपूर्णांक;
	काष्ठा hlist_head		blkg_list;

	काष्ठा blkcg_policy_data	*cpd[BLKCG_MAX_POLS];

	काष्ठा list_head		all_blkcgs_node;
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा list_head		cgwb_list;
#पूर्ण_अगर
पूर्ण;

काष्ठा blkg_iostat अणु
	u64				bytes[BLKG_IOSTAT_NR];
	u64				ios[BLKG_IOSTAT_NR];
पूर्ण;

काष्ठा blkg_iostat_set अणु
	काष्ठा u64_stats_sync		sync;
	काष्ठा blkg_iostat		cur;
	काष्ठा blkg_iostat		last;
पूर्ण;

/*
 * A blkcg_gq (blkg) is association between a block cgroup (blkcg) and a
 * request_queue (q).  This is used by blkcg policies which need to track
 * inक्रमmation per blkcg - q pair.
 *
 * There can be multiple active blkcg policies and each blkg:policy pair is
 * represented by a blkg_policy_data which is allocated and मुक्तd by each
 * policy's pd_alloc/मुक्त_fn() methods.  A policy can allocate निजी data
 * area by allocating larger data काष्ठाure which embeds blkg_policy_data
 * at the beginning.
 */
काष्ठा blkg_policy_data अणु
	/* the blkg and policy id this per-policy data beदीर्घs to */
	काष्ठा blkcg_gq			*blkg;
	पूर्णांक				plid;
पूर्ण;

/*
 * Policies that need to keep per-blkcg data which is independent from any
 * request_queue associated to it should implement cpd_alloc/मुक्त_fn()
 * methods.  A policy can allocate निजी data area by allocating larger
 * data काष्ठाure which embeds blkcg_policy_data at the beginning.
 * cpd_init() is invoked to let each policy handle per-blkcg data.
 */
काष्ठा blkcg_policy_data अणु
	/* the blkcg and policy id this per-policy data beदीर्घs to */
	काष्ठा blkcg			*blkcg;
	पूर्णांक				plid;
पूर्ण;

/* association between a blk cgroup and a request queue */
काष्ठा blkcg_gq अणु
	/* Poपूर्णांकer to the associated request_queue */
	काष्ठा request_queue		*q;
	काष्ठा list_head		q_node;
	काष्ठा hlist_node		blkcg_node;
	काष्ठा blkcg			*blkcg;

	/* all non-root blkcg_gq's are guaranteed to have access to parent */
	काष्ठा blkcg_gq			*parent;

	/* reference count */
	काष्ठा percpu_ref		refcnt;

	/* is this blkg online? रक्षित by both blkcg and q locks */
	bool				online;

	काष्ठा blkg_iostat_set __percpu	*iostat_cpu;
	काष्ठा blkg_iostat_set		iostat;

	काष्ठा blkg_policy_data		*pd[BLKCG_MAX_POLS];

	spinlock_t			async_bio_lock;
	काष्ठा bio_list			async_bios;
	काष्ठा work_काष्ठा		async_bio_work;

	atomic_t			use_delay;
	atomic64_t			delay_nsec;
	atomic64_t			delay_start;
	u64				last_delay;
	पूर्णांक				last_use;

	काष्ठा rcu_head			rcu_head;
पूर्ण;

प्रकार काष्ठा blkcg_policy_data *(blkcg_pol_alloc_cpd_fn)(gfp_t gfp);
प्रकार व्योम (blkcg_pol_init_cpd_fn)(काष्ठा blkcg_policy_data *cpd);
प्रकार व्योम (blkcg_pol_मुक्त_cpd_fn)(काष्ठा blkcg_policy_data *cpd);
प्रकार व्योम (blkcg_pol_bind_cpd_fn)(काष्ठा blkcg_policy_data *cpd);
प्रकार काष्ठा blkg_policy_data *(blkcg_pol_alloc_pd_fn)(gfp_t gfp,
				काष्ठा request_queue *q, काष्ठा blkcg *blkcg);
प्रकार व्योम (blkcg_pol_init_pd_fn)(काष्ठा blkg_policy_data *pd);
प्रकार व्योम (blkcg_pol_online_pd_fn)(काष्ठा blkg_policy_data *pd);
प्रकार व्योम (blkcg_pol_offline_pd_fn)(काष्ठा blkg_policy_data *pd);
प्रकार व्योम (blkcg_pol_मुक्त_pd_fn)(काष्ठा blkg_policy_data *pd);
प्रकार व्योम (blkcg_pol_reset_pd_stats_fn)(काष्ठा blkg_policy_data *pd);
प्रकार माप_प्रकार (blkcg_pol_stat_pd_fn)(काष्ठा blkg_policy_data *pd, अक्षर *buf,
				      माप_प्रकार size);

काष्ठा blkcg_policy अणु
	पूर्णांक				plid;
	/* cgroup files क्रम the policy */
	काष्ठा cftype			*dfl_cftypes;
	काष्ठा cftype			*legacy_cftypes;

	/* operations */
	blkcg_pol_alloc_cpd_fn		*cpd_alloc_fn;
	blkcg_pol_init_cpd_fn		*cpd_init_fn;
	blkcg_pol_मुक्त_cpd_fn		*cpd_मुक्त_fn;
	blkcg_pol_bind_cpd_fn		*cpd_bind_fn;

	blkcg_pol_alloc_pd_fn		*pd_alloc_fn;
	blkcg_pol_init_pd_fn		*pd_init_fn;
	blkcg_pol_online_pd_fn		*pd_online_fn;
	blkcg_pol_offline_pd_fn		*pd_offline_fn;
	blkcg_pol_मुक्त_pd_fn		*pd_मुक्त_fn;
	blkcg_pol_reset_pd_stats_fn	*pd_reset_stats_fn;
	blkcg_pol_stat_pd_fn		*pd_stat_fn;
पूर्ण;

बाह्य काष्ठा blkcg blkcg_root;
बाह्य काष्ठा cgroup_subsys_state * स्थिर blkcg_root_css;
बाह्य bool blkcg_debug_stats;

काष्ठा blkcg_gq *blkg_lookup_slowpath(काष्ठा blkcg *blkcg,
				      काष्ठा request_queue *q, bool update_hपूर्णांक);
पूर्णांक blkcg_init_queue(काष्ठा request_queue *q);
व्योम blkcg_निकास_queue(काष्ठा request_queue *q);

/* Blkio controller policy registration */
पूर्णांक blkcg_policy_रेजिस्टर(काष्ठा blkcg_policy *pol);
व्योम blkcg_policy_unरेजिस्टर(काष्ठा blkcg_policy *pol);
पूर्णांक blkcg_activate_policy(काष्ठा request_queue *q,
			  स्थिर काष्ठा blkcg_policy *pol);
व्योम blkcg_deactivate_policy(काष्ठा request_queue *q,
			     स्थिर काष्ठा blkcg_policy *pol);

स्थिर अक्षर *blkg_dev_name(काष्ठा blkcg_gq *blkg);
व्योम blkcg_prपूर्णांक_blkgs(काष्ठा seq_file *sf, काष्ठा blkcg *blkcg,
		       u64 (*prfill)(काष्ठा seq_file *,
				     काष्ठा blkg_policy_data *, पूर्णांक),
		       स्थिर काष्ठा blkcg_policy *pol, पूर्णांक data,
		       bool show_total);
u64 __blkg_prfill_u64(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd, u64 v);

काष्ठा blkg_conf_ctx अणु
	काष्ठा block_device		*bdev;
	काष्ठा blkcg_gq			*blkg;
	अक्षर				*body;
पूर्ण;

काष्ठा block_device *blkcg_conf_खोलो_bdev(अक्षर **inputp);
पूर्णांक blkg_conf_prep(काष्ठा blkcg *blkcg, स्थिर काष्ठा blkcg_policy *pol,
		   अक्षर *input, काष्ठा blkg_conf_ctx *ctx);
व्योम blkg_conf_finish(काष्ठा blkg_conf_ctx *ctx);

/**
 * blkcg_css - find the current css
 *
 * Find the css associated with either the kthपढ़ो or the current task.
 * This may वापस a dying css, so it is up to the caller to use tryget logic
 * to confirm it is alive and well.
 */
अटल अंतरभूत काष्ठा cgroup_subsys_state *blkcg_css(व्योम)
अणु
	काष्ठा cgroup_subsys_state *css;

	css = kthपढ़ो_blkcg();
	अगर (css)
		वापस css;
	वापस task_css(current, io_cgrp_id);
पूर्ण

अटल अंतरभूत काष्ठा blkcg *css_to_blkcg(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा blkcg, css) : शून्य;
पूर्ण

/**
 * __bio_blkcg - पूर्णांकernal, inconsistent version to get blkcg
 *
 * DO NOT USE.
 * This function is inconsistent and consequently is dangerous to use.  The
 * first part of the function वापसs a blkcg where a reference is owned by the
 * bio.  This means it करोes not need to be rcu रक्षित as it cannot go away
 * with the bio owning a reference to it.  However, the latter potentially माला_लो
 * it from task_css().  This can race against task migration and the cgroup
 * dying.  It is also semantically dअगरferent as it must be called rcu रक्षित
 * and is susceptible to failure when trying to get a reference to it.
 * Thereक्रमe, it is not ok to assume that *_get() will always succeed on the
 * blkcg वापसed here.
 */
अटल अंतरभूत काष्ठा blkcg *__bio_blkcg(काष्ठा bio *bio)
अणु
	अगर (bio && bio->bi_blkg)
		वापस bio->bi_blkg->blkcg;
	वापस css_to_blkcg(blkcg_css());
पूर्ण

/**
 * bio_blkcg - grab the blkcg associated with a bio
 * @bio: target bio
 *
 * This वापसs the blkcg associated with a bio, %शून्य अगर not associated.
 * Callers are expected to either handle %शून्य or know association has been
 * करोne prior to calling this.
 */
अटल अंतरभूत काष्ठा blkcg *bio_blkcg(काष्ठा bio *bio)
अणु
	अगर (bio && bio->bi_blkg)
		वापस bio->bi_blkg->blkcg;
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool blk_cgroup_congested(व्योम)
अणु
	काष्ठा cgroup_subsys_state *css;
	bool ret = false;

	rcu_पढ़ो_lock();
	css = kthपढ़ो_blkcg();
	अगर (!css)
		css = task_css(current, io_cgrp_id);
	जबतक (css) अणु
		अगर (atomic_पढ़ो(&css->cgroup->congestion_count)) अणु
			ret = true;
			अवरोध;
		पूर्ण
		css = css->parent;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * bio_issue_as_root_blkg - see अगर this bio needs to be issued as root blkg
 * @वापस: true अगर this bio needs to be submitted with the root blkg context.
 *
 * In order to aव्योम priority inversions we someबार need to issue a bio as अगर
 * it were attached to the root blkg, and then backअक्षरge to the actual owning
 * blkg.  The idea is we करो bio_blkcg() to look up the actual context क्रम the
 * bio and attach the appropriate blkg to the bio.  Then we call this helper and
 * अगर it is true run with the root blkg क्रम that queue and then करो any
 * backअक्षरging to the originating cgroup once the io is complete.
 */
अटल अंतरभूत bool bio_issue_as_root_blkg(काष्ठा bio *bio)
अणु
	वापस (bio->bi_opf & (REQ_META | REQ_SWAP)) != 0;
पूर्ण

/**
 * blkcg_parent - get the parent of a blkcg
 * @blkcg: blkcg of पूर्णांकerest
 *
 * Return the parent blkcg of @blkcg.  Can be called anyसमय.
 */
अटल अंतरभूत काष्ठा blkcg *blkcg_parent(काष्ठा blkcg *blkcg)
अणु
	वापस css_to_blkcg(blkcg->css.parent);
पूर्ण

/**
 * __blkg_lookup - पूर्णांकernal version of blkg_lookup()
 * @blkcg: blkcg of पूर्णांकerest
 * @q: request_queue of पूर्णांकerest
 * @update_hपूर्णांक: whether to update lookup hपूर्णांक with the result or not
 *
 * This is पूर्णांकernal version and shouldn't be used by policy
 * implementations.  Looks up blkgs क्रम the @blkcg - @q pair regardless of
 * @q's bypass state.  If @update_hपूर्णांक is %true, the caller should be
 * holding @q->queue_lock and lookup hपूर्णांक is updated on success.
 */
अटल अंतरभूत काष्ठा blkcg_gq *__blkg_lookup(काष्ठा blkcg *blkcg,
					     काष्ठा request_queue *q,
					     bool update_hपूर्णांक)
अणु
	काष्ठा blkcg_gq *blkg;

	अगर (blkcg == &blkcg_root)
		वापस q->root_blkg;

	blkg = rcu_dereference(blkcg->blkg_hपूर्णांक);
	अगर (blkg && blkg->q == q)
		वापस blkg;

	वापस blkg_lookup_slowpath(blkcg, q, update_hपूर्णांक);
पूर्ण

/**
 * blkg_lookup - lookup blkg क्रम the specअगरied blkcg - q pair
 * @blkcg: blkcg of पूर्णांकerest
 * @q: request_queue of पूर्णांकerest
 *
 * Lookup blkg क्रम the @blkcg - @q pair.  This function should be called
 * under RCU पढ़ो lock.
 */
अटल अंतरभूत काष्ठा blkcg_gq *blkg_lookup(काष्ठा blkcg *blkcg,
					   काष्ठा request_queue *q)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस __blkg_lookup(blkcg, q, false);
पूर्ण

/**
 * blk_queue_root_blkg - वापस blkg क्रम the (blkcg_root, @q) pair
 * @q: request_queue of पूर्णांकerest
 *
 * Lookup blkg क्रम @q at the root level. See also blkg_lookup().
 */
अटल अंतरभूत काष्ठा blkcg_gq *blk_queue_root_blkg(काष्ठा request_queue *q)
अणु
	वापस q->root_blkg;
पूर्ण

/**
 * blkg_to_pdata - get policy निजी data
 * @blkg: blkg of पूर्णांकerest
 * @pol: policy of पूर्णांकerest
 *
 * Return poपूर्णांकer to निजी data associated with the @blkg-@pol pair.
 */
अटल अंतरभूत काष्ठा blkg_policy_data *blkg_to_pd(काष्ठा blkcg_gq *blkg,
						  काष्ठा blkcg_policy *pol)
अणु
	वापस blkg ? blkg->pd[pol->plid] : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा blkcg_policy_data *blkcg_to_cpd(काष्ठा blkcg *blkcg,
						     काष्ठा blkcg_policy *pol)
अणु
	वापस blkcg ? blkcg->cpd[pol->plid] : शून्य;
पूर्ण

/**
 * pdata_to_blkg - get blkg associated with policy निजी data
 * @pd: policy निजी data of पूर्णांकerest
 *
 * @pd is policy निजी data.  Determine the blkg it's associated with.
 */
अटल अंतरभूत काष्ठा blkcg_gq *pd_to_blkg(काष्ठा blkg_policy_data *pd)
अणु
	वापस pd ? pd->blkg : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा blkcg *cpd_to_blkcg(काष्ठा blkcg_policy_data *cpd)
अणु
	वापस cpd ? cpd->blkcg : शून्य;
पूर्ण

बाह्य व्योम blkcg_destroy_blkgs(काष्ठा blkcg *blkcg);

/**
 * blkcg_pin_online - pin online state
 * @blkcg: blkcg of पूर्णांकerest
 *
 * While pinned, a blkcg is kept online.  This is primarily used to
 * impedance-match blkg and cgwb lअगरeबार so that blkg करोesn't go offline
 * जबतक an associated cgwb is still active.
 */
अटल अंतरभूत व्योम blkcg_pin_online(काष्ठा blkcg *blkcg)
अणु
	refcount_inc(&blkcg->online_pin);
पूर्ण

/**
 * blkcg_unpin_online - unpin online state
 * @blkcg: blkcg of पूर्णांकerest
 *
 * This is primarily used to impedance-match blkg and cgwb lअगरeबार so
 * that blkg करोesn't go offline जबतक an associated cgwb is still active.
 * When this count goes to zero, all active cgwbs have finished so the
 * blkcg can जारी deकाष्ठाion by calling blkcg_destroy_blkgs().
 */
अटल अंतरभूत व्योम blkcg_unpin_online(काष्ठा blkcg *blkcg)
अणु
	करो अणु
		अगर (!refcount_dec_and_test(&blkcg->online_pin))
			अवरोध;
		blkcg_destroy_blkgs(blkcg);
		blkcg = blkcg_parent(blkcg);
	पूर्ण जबतक (blkcg);
पूर्ण

/**
 * blkg_path - क्रमmat cgroup path of blkg
 * @blkg: blkg of पूर्णांकerest
 * @buf: target buffer
 * @buflen: target buffer length
 *
 * Format the path of the cgroup of @blkg पूर्णांकo @buf.
 */
अटल अंतरभूत पूर्णांक blkg_path(काष्ठा blkcg_gq *blkg, अक्षर *buf, पूर्णांक buflen)
अणु
	वापस cgroup_path(blkg->blkcg->css.cgroup, buf, buflen);
पूर्ण

/**
 * blkg_get - get a blkg reference
 * @blkg: blkg to get
 *
 * The caller should be holding an existing reference.
 */
अटल अंतरभूत व्योम blkg_get(काष्ठा blkcg_gq *blkg)
अणु
	percpu_ref_get(&blkg->refcnt);
पूर्ण

/**
 * blkg_tryget - try and get a blkg reference
 * @blkg: blkg to get
 *
 * This is क्रम use when करोing an RCU lookup of the blkg.  We may be in the midst
 * of मुक्तing this blkg, so we can only use it अगर the refcnt is not zero.
 */
अटल अंतरभूत bool blkg_tryget(काष्ठा blkcg_gq *blkg)
अणु
	वापस blkg && percpu_ref_tryget(&blkg->refcnt);
पूर्ण

/**
 * blkg_put - put a blkg reference
 * @blkg: blkg to put
 */
अटल अंतरभूत व्योम blkg_put(काष्ठा blkcg_gq *blkg)
अणु
	percpu_ref_put(&blkg->refcnt);
पूर्ण

/**
 * blkg_क्रम_each_descendant_pre - pre-order walk of a blkg's descendants
 * @d_blkg: loop cursor poपूर्णांकing to the current descendant
 * @pos_css: used क्रम iteration
 * @p_blkg: target blkg to walk descendants of
 *
 * Walk @c_blkg through the descendants of @p_blkg.  Must be used with RCU
 * पढ़ो locked.  If called under either blkcg or queue lock, the iteration
 * is guaranteed to include all and only online blkgs.  The caller may
 * update @pos_css by calling css_righपंचांगost_descendant() to skip subtree.
 * @p_blkg is included in the iteration and the first node to be visited.
 */
#घोषणा blkg_क्रम_each_descendant_pre(d_blkg, pos_css, p_blkg)		\
	css_क्रम_each_descendant_pre((pos_css), &(p_blkg)->blkcg->css)	\
		अगर (((d_blkg) = __blkg_lookup(css_to_blkcg(pos_css),	\
					      (p_blkg)->q, false)))

/**
 * blkg_क्रम_each_descendant_post - post-order walk of a blkg's descendants
 * @d_blkg: loop cursor poपूर्णांकing to the current descendant
 * @pos_css: used क्रम iteration
 * @p_blkg: target blkg to walk descendants of
 *
 * Similar to blkg_क्रम_each_descendant_pre() but perक्रमms post-order
 * traversal instead.  Synchronization rules are the same.  @p_blkg is
 * included in the iteration and the last node to be visited.
 */
#घोषणा blkg_क्रम_each_descendant_post(d_blkg, pos_css, p_blkg)		\
	css_क्रम_each_descendant_post((pos_css), &(p_blkg)->blkcg->css)	\
		अगर (((d_blkg) = __blkg_lookup(css_to_blkcg(pos_css),	\
					      (p_blkg)->q, false)))

bool __blkcg_punt_bio_submit(काष्ठा bio *bio);

अटल अंतरभूत bool blkcg_punt_bio_submit(काष्ठा bio *bio)
अणु
	अगर (bio->bi_opf & REQ_CGROUP_PUNT)
		वापस __blkcg_punt_bio_submit(bio);
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत व्योम blkcg_bio_issue_init(काष्ठा bio *bio)
अणु
	bio_issue_init(&bio->bi_issue, bio_sectors(bio));
पूर्ण

अटल अंतरभूत व्योम blkcg_use_delay(काष्ठा blkcg_gq *blkg)
अणु
	अगर (WARN_ON_ONCE(atomic_पढ़ो(&blkg->use_delay) < 0))
		वापस;
	अगर (atomic_add_वापस(1, &blkg->use_delay) == 1)
		atomic_inc(&blkg->blkcg->css.cgroup->congestion_count);
पूर्ण

अटल अंतरभूत पूर्णांक blkcg_unuse_delay(काष्ठा blkcg_gq *blkg)
अणु
	पूर्णांक old = atomic_पढ़ो(&blkg->use_delay);

	अगर (WARN_ON_ONCE(old < 0))
		वापस 0;
	अगर (old == 0)
		वापस 0;

	/*
	 * We करो this song and dance because we can race with somebody अन्यथा
	 * adding or removing delay.  If we just did an atomic_dec we'd end up
	 * negative and we'd alपढ़ोy be in trouble.  We need to subtract 1 and
	 * then check to see अगर we were the last delay so we can drop the
	 * congestion count on the cgroup.
	 */
	जबतक (old) अणु
		पूर्णांक cur = atomic_cmpxchg(&blkg->use_delay, old, old - 1);
		अगर (cur == old)
			अवरोध;
		old = cur;
	पूर्ण

	अगर (old == 0)
		वापस 0;
	अगर (old == 1)
		atomic_dec(&blkg->blkcg->css.cgroup->congestion_count);
	वापस 1;
पूर्ण

/**
 * blkcg_set_delay - Enable allocator delay mechanism with the specअगरied delay amount
 * @blkg: target blkg
 * @delay: delay duration in nsecs
 *
 * When enabled with this function, the delay is not decayed and must be
 * explicitly cleared with blkcg_clear_delay(). Must not be mixed with
 * blkcg_[un]use_delay() and blkcg_add_delay() usages.
 */
अटल अंतरभूत व्योम blkcg_set_delay(काष्ठा blkcg_gq *blkg, u64 delay)
अणु
	पूर्णांक old = atomic_पढ़ो(&blkg->use_delay);

	/* We only want 1 person setting the congestion count क्रम this blkg. */
	अगर (!old && atomic_cmpxchg(&blkg->use_delay, old, -1) == old)
		atomic_inc(&blkg->blkcg->css.cgroup->congestion_count);

	atomic64_set(&blkg->delay_nsec, delay);
पूर्ण

/**
 * blkcg_clear_delay - Disable allocator delay mechanism
 * @blkg: target blkg
 *
 * Disable use_delay mechanism. See blkcg_set_delay().
 */
अटल अंतरभूत व्योम blkcg_clear_delay(काष्ठा blkcg_gq *blkg)
अणु
	पूर्णांक old = atomic_पढ़ो(&blkg->use_delay);

	/* We only want 1 person clearing the congestion count क्रम this blkg. */
	अगर (old && atomic_cmpxchg(&blkg->use_delay, old, 0) == old)
		atomic_dec(&blkg->blkcg->css.cgroup->congestion_count);
पूर्ण

व्योम blk_cgroup_bio_start(काष्ठा bio *bio);
व्योम blkcg_add_delay(काष्ठा blkcg_gq *blkg, u64 now, u64 delta);
व्योम blkcg_schedule_throttle(काष्ठा request_queue *q, bool use_memdelay);
व्योम blkcg_maybe_throttle_current(व्योम);
#अन्यथा	/* CONFIG_BLK_CGROUP */

काष्ठा blkcg अणु
पूर्ण;

काष्ठा blkg_policy_data अणु
पूर्ण;

काष्ठा blkcg_policy_data अणु
पूर्ण;

काष्ठा blkcg_gq अणु
पूर्ण;

काष्ठा blkcg_policy अणु
पूर्ण;

#घोषणा blkcg_root_css	((काष्ठा cgroup_subsys_state *)ERR_PTR(-EINVAL))

अटल अंतरभूत व्योम blkcg_maybe_throttle_current(व्योम) अणु पूर्ण
अटल अंतरभूत bool blk_cgroup_congested(व्योम) अणु वापस false; पूर्ण

#अगर_घोषित CONFIG_BLOCK

अटल अंतरभूत व्योम blkcg_schedule_throttle(काष्ठा request_queue *q, bool use_memdelay) अणु पूर्ण

अटल अंतरभूत काष्ठा blkcg_gq *blkg_lookup(काष्ठा blkcg *blkcg, व्योम *key) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा blkcg_gq *blk_queue_root_blkg(काष्ठा request_queue *q)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक blkcg_init_queue(काष्ठा request_queue *q) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम blkcg_निकास_queue(काष्ठा request_queue *q) अणु पूर्ण
अटल अंतरभूत पूर्णांक blkcg_policy_रेजिस्टर(काष्ठा blkcg_policy *pol) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम blkcg_policy_unरेजिस्टर(काष्ठा blkcg_policy *pol) अणु पूर्ण
अटल अंतरभूत पूर्णांक blkcg_activate_policy(काष्ठा request_queue *q,
					स्थिर काष्ठा blkcg_policy *pol) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम blkcg_deactivate_policy(काष्ठा request_queue *q,
					   स्थिर काष्ठा blkcg_policy *pol) अणु पूर्ण

अटल अंतरभूत काष्ठा blkcg *__bio_blkcg(काष्ठा bio *bio) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा blkcg *bio_blkcg(काष्ठा bio *bio) अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा blkg_policy_data *blkg_to_pd(काष्ठा blkcg_gq *blkg,
						  काष्ठा blkcg_policy *pol) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा blkcg_gq *pd_to_blkg(काष्ठा blkg_policy_data *pd) अणु वापस शून्य; पूर्ण
अटल अंतरभूत अक्षर *blkg_path(काष्ठा blkcg_gq *blkg) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम blkg_get(काष्ठा blkcg_gq *blkg) अणु पूर्ण
अटल अंतरभूत व्योम blkg_put(काष्ठा blkcg_gq *blkg) अणु पूर्ण

अटल अंतरभूत bool blkcg_punt_bio_submit(काष्ठा bio *bio) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम blkcg_bio_issue_init(काष्ठा bio *bio) अणु पूर्ण
अटल अंतरभूत व्योम blk_cgroup_bio_start(काष्ठा bio *bio) अणु पूर्ण

#घोषणा blk_queue_क्रम_each_rl(rl, q)	\
	क्रम ((rl) = &(q)->root_rl; (rl); (rl) = शून्य)

#पूर्ण_अगर	/* CONFIG_BLOCK */
#पूर्ण_अगर	/* CONFIG_BLK_CGROUP */
#पूर्ण_अगर	/* _BLK_CGROUP_H */
