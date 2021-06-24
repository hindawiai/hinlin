<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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
 *
 * For policy-specअगरic per-blkcg data:
 * Copyright (C) 2015 Paolo Valente <paolo.valente@unimore.it>
 *                    Arianna Avanzini <avanzini.arianna@gmail.com>
 */
#समावेश <linux/ioprपन.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/err.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/slab.h>
#समावेश <linux/genhd.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/psi.h>
#समावेश "blk.h"

/*
 * blkcg_pol_mutex protects blkcg_policy[] and policy [de]activation.
 * blkcg_pol_रेजिस्टर_mutex nests outside of it and synchronizes entire
 * policy [un]रेजिस्टर operations including cgroup file additions /
 * removals.  Putting cgroup file registration outside blkcg_pol_mutex
 * allows grabbing it from cgroup callbacks.
 */
अटल DEFINE_MUTEX(blkcg_pol_रेजिस्टर_mutex);
अटल DEFINE_MUTEX(blkcg_pol_mutex);

काष्ठा blkcg blkcg_root;
EXPORT_SYMBOL_GPL(blkcg_root);

काष्ठा cgroup_subsys_state * स्थिर blkcg_root_css = &blkcg_root.css;
EXPORT_SYMBOL_GPL(blkcg_root_css);

अटल काष्ठा blkcg_policy *blkcg_policy[BLKCG_MAX_POLS];

अटल LIST_HEAD(all_blkcgs);		/* रक्षित by blkcg_pol_mutex */

bool blkcg_debug_stats = false;
अटल काष्ठा workqueue_काष्ठा *blkcg_punt_bio_wq;

अटल bool blkcg_policy_enabled(काष्ठा request_queue *q,
				 स्थिर काष्ठा blkcg_policy *pol)
अणु
	वापस pol && test_bit(pol->plid, q->blkcg_pols);
पूर्ण

/**
 * blkg_मुक्त - मुक्त a blkg
 * @blkg: blkg to मुक्त
 *
 * Free @blkg which may be partially allocated.
 */
अटल व्योम blkg_मुक्त(काष्ठा blkcg_gq *blkg)
अणु
	पूर्णांक i;

	अगर (!blkg)
		वापस;

	क्रम (i = 0; i < BLKCG_MAX_POLS; i++)
		अगर (blkg->pd[i])
			blkcg_policy[i]->pd_मुक्त_fn(blkg->pd[i]);

	मुक्त_percpu(blkg->iostat_cpu);
	percpu_ref_निकास(&blkg->refcnt);
	kमुक्त(blkg);
पूर्ण

अटल व्योम __blkg_release(काष्ठा rcu_head *rcu)
अणु
	काष्ठा blkcg_gq *blkg = container_of(rcu, काष्ठा blkcg_gq, rcu_head);

	WARN_ON(!bio_list_empty(&blkg->async_bios));

	/* release the blkcg and parent blkg refs this blkg has been holding */
	css_put(&blkg->blkcg->css);
	अगर (blkg->parent)
		blkg_put(blkg->parent);
	blkg_मुक्त(blkg);
पूर्ण

/*
 * A group is RCU रक्षित, but having an rcu lock करोes not mean that one
 * can access all the fields of blkg and assume these are valid.  For
 * example, करोn't try to follow throtl_data and request queue links.
 *
 * Having a reference to blkg under an rcu allows accesses to only values
 * local to groups like group stats and group rate limits.
 */
अटल व्योम blkg_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा blkcg_gq *blkg = container_of(ref, काष्ठा blkcg_gq, refcnt);

	call_rcu(&blkg->rcu_head, __blkg_release);
पूर्ण

अटल व्योम blkg_async_bio_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा blkcg_gq *blkg = container_of(work, काष्ठा blkcg_gq,
					     async_bio_work);
	काष्ठा bio_list bios = BIO_EMPTY_LIST;
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;
	bool need_plug = false;

	/* as दीर्घ as there are pending bios, @blkg can't go away */
	spin_lock_bh(&blkg->async_bio_lock);
	bio_list_merge(&bios, &blkg->async_bios);
	bio_list_init(&blkg->async_bios);
	spin_unlock_bh(&blkg->async_bio_lock);

	/* start plug only when bio_list contains at least 2 bios */
	अगर (मूलप्रण.सead && मूलप्रण.सead->bi_next) अणु
		need_plug = true;
		blk_start_plug(&plug);
	पूर्ण
	जबतक ((bio = bio_list_pop(&bios)))
		submit_bio(bio);
	अगर (need_plug)
		blk_finish_plug(&plug);
पूर्ण

/**
 * blkg_alloc - allocate a blkg
 * @blkcg: block cgroup the new blkg is associated with
 * @q: request_queue the new blkg is associated with
 * @gfp_mask: allocation mask to use
 *
 * Allocate a new blkg assocating @blkcg and @q.
 */
अटल काष्ठा blkcg_gq *blkg_alloc(काष्ठा blkcg *blkcg, काष्ठा request_queue *q,
				   gfp_t gfp_mask)
अणु
	काष्ठा blkcg_gq *blkg;
	पूर्णांक i, cpu;

	/* alloc and init base part */
	blkg = kzalloc_node(माप(*blkg), gfp_mask, q->node);
	अगर (!blkg)
		वापस शून्य;

	अगर (percpu_ref_init(&blkg->refcnt, blkg_release, 0, gfp_mask))
		जाओ err_मुक्त;

	blkg->iostat_cpu = alloc_percpu_gfp(काष्ठा blkg_iostat_set, gfp_mask);
	अगर (!blkg->iostat_cpu)
		जाओ err_मुक्त;

	blkg->q = q;
	INIT_LIST_HEAD(&blkg->q_node);
	spin_lock_init(&blkg->async_bio_lock);
	bio_list_init(&blkg->async_bios);
	INIT_WORK(&blkg->async_bio_work, blkg_async_bio_workfn);
	blkg->blkcg = blkcg;

	u64_stats_init(&blkg->iostat.sync);
	क्रम_each_possible_cpu(cpu)
		u64_stats_init(&per_cpu_ptr(blkg->iostat_cpu, cpu)->sync);

	क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
		काष्ठा blkcg_policy *pol = blkcg_policy[i];
		काष्ठा blkg_policy_data *pd;

		अगर (!blkcg_policy_enabled(q, pol))
			जारी;

		/* alloc per-policy data and attach it to blkg */
		pd = pol->pd_alloc_fn(gfp_mask, q, blkcg);
		अगर (!pd)
			जाओ err_मुक्त;

		blkg->pd[i] = pd;
		pd->blkg = blkg;
		pd->plid = i;
	पूर्ण

	वापस blkg;

err_मुक्त:
	blkg_मुक्त(blkg);
	वापस शून्य;
पूर्ण

काष्ठा blkcg_gq *blkg_lookup_slowpath(काष्ठा blkcg *blkcg,
				      काष्ठा request_queue *q, bool update_hपूर्णांक)
अणु
	काष्ठा blkcg_gq *blkg;

	/*
	 * Hपूर्णांक didn't match.  Look up from the radix tree.  Note that the
	 * hपूर्णांक can only be updated under queue_lock as otherwise @blkg
	 * could have alपढ़ोy been हटाओd from blkg_tree.  The caller is
	 * responsible क्रम grabbing queue_lock अगर @update_hपूर्णांक.
	 */
	blkg = radix_tree_lookup(&blkcg->blkg_tree, q->id);
	अगर (blkg && blkg->q == q) अणु
		अगर (update_hपूर्णांक) अणु
			lockdep_निश्चित_held(&q->queue_lock);
			rcu_assign_poपूर्णांकer(blkcg->blkg_hपूर्णांक, blkg);
		पूर्ण
		वापस blkg;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(blkg_lookup_slowpath);

/*
 * If @new_blkg is %शून्य, this function tries to allocate a new one as
 * necessary using %GFP_NOWAIT.  @new_blkg is always consumed on वापस.
 */
अटल काष्ठा blkcg_gq *blkg_create(काष्ठा blkcg *blkcg,
				    काष्ठा request_queue *q,
				    काष्ठा blkcg_gq *new_blkg)
अणु
	काष्ठा blkcg_gq *blkg;
	पूर्णांक i, ret;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	lockdep_निश्चित_held(&q->queue_lock);

	/* request_queue is dying, करो not create/recreate a blkg */
	अगर (blk_queue_dying(q)) अणु
		ret = -ENODEV;
		जाओ err_मुक्त_blkg;
	पूर्ण

	/* blkg holds a reference to blkcg */
	अगर (!css_tryget_online(&blkcg->css)) अणु
		ret = -ENODEV;
		जाओ err_मुक्त_blkg;
	पूर्ण

	/* allocate */
	अगर (!new_blkg) अणु
		new_blkg = blkg_alloc(blkcg, q, GFP_NOWAIT | __GFP_NOWARN);
		अगर (unlikely(!new_blkg)) अणु
			ret = -ENOMEM;
			जाओ err_put_css;
		पूर्ण
	पूर्ण
	blkg = new_blkg;

	/* link parent */
	अगर (blkcg_parent(blkcg)) अणु
		blkg->parent = __blkg_lookup(blkcg_parent(blkcg), q, false);
		अगर (WARN_ON_ONCE(!blkg->parent)) अणु
			ret = -ENODEV;
			जाओ err_put_css;
		पूर्ण
		blkg_get(blkg->parent);
	पूर्ण

	/* invoke per-policy init */
	क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
		काष्ठा blkcg_policy *pol = blkcg_policy[i];

		अगर (blkg->pd[i] && pol->pd_init_fn)
			pol->pd_init_fn(blkg->pd[i]);
	पूर्ण

	/* insert */
	spin_lock(&blkcg->lock);
	ret = radix_tree_insert(&blkcg->blkg_tree, q->id, blkg);
	अगर (likely(!ret)) अणु
		hlist_add_head_rcu(&blkg->blkcg_node, &blkcg->blkg_list);
		list_add(&blkg->q_node, &q->blkg_list);

		क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
			काष्ठा blkcg_policy *pol = blkcg_policy[i];

			अगर (blkg->pd[i] && pol->pd_online_fn)
				pol->pd_online_fn(blkg->pd[i]);
		पूर्ण
	पूर्ण
	blkg->online = true;
	spin_unlock(&blkcg->lock);

	अगर (!ret)
		वापस blkg;

	/* @blkg failed fully initialized, use the usual release path */
	blkg_put(blkg);
	वापस ERR_PTR(ret);

err_put_css:
	css_put(&blkcg->css);
err_मुक्त_blkg:
	blkg_मुक्त(new_blkg);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * blkg_lookup_create - lookup blkg, try to create one अगर not there
 * @blkcg: blkcg of पूर्णांकerest
 * @q: request_queue of पूर्णांकerest
 *
 * Lookup blkg क्रम the @blkcg - @q pair.  If it करोesn't exist, try to
 * create one.  blkg creation is perक्रमmed recursively from blkcg_root such
 * that all non-root blkg's have access to the parent blkg.  This function
 * should be called under RCU पढ़ो lock and takes @q->queue_lock.
 *
 * Returns the blkg or the बंदst blkg अगर blkg_create() fails as it walks
 * करोwn from root.
 */
अटल काष्ठा blkcg_gq *blkg_lookup_create(काष्ठा blkcg *blkcg,
		काष्ठा request_queue *q)
अणु
	काष्ठा blkcg_gq *blkg;
	अचिन्हित दीर्घ flags;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	blkg = blkg_lookup(blkcg, q);
	अगर (blkg)
		वापस blkg;

	spin_lock_irqsave(&q->queue_lock, flags);
	blkg = __blkg_lookup(blkcg, q, true);
	अगर (blkg)
		जाओ found;

	/*
	 * Create blkgs walking करोwn from blkcg_root to @blkcg, so that all
	 * non-root blkgs have access to their parents.  Returns the बंदst
	 * blkg to the पूर्णांकended blkg should blkg_create() fail.
	 */
	जबतक (true) अणु
		काष्ठा blkcg *pos = blkcg;
		काष्ठा blkcg *parent = blkcg_parent(blkcg);
		काष्ठा blkcg_gq *ret_blkg = q->root_blkg;

		जबतक (parent) अणु
			blkg = __blkg_lookup(parent, q, false);
			अगर (blkg) अणु
				/* remember बंदst blkg */
				ret_blkg = blkg;
				अवरोध;
			पूर्ण
			pos = parent;
			parent = blkcg_parent(parent);
		पूर्ण

		blkg = blkg_create(pos, q, शून्य);
		अगर (IS_ERR(blkg)) अणु
			blkg = ret_blkg;
			अवरोध;
		पूर्ण
		अगर (pos == blkcg)
			अवरोध;
	पूर्ण

found:
	spin_unlock_irqrestore(&q->queue_lock, flags);
	वापस blkg;
पूर्ण

अटल व्योम blkg_destroy(काष्ठा blkcg_gq *blkg)
अणु
	काष्ठा blkcg *blkcg = blkg->blkcg;
	पूर्णांक i;

	lockdep_निश्चित_held(&blkg->q->queue_lock);
	lockdep_निश्चित_held(&blkcg->lock);

	/* Something wrong अगर we are trying to हटाओ same group twice */
	WARN_ON_ONCE(list_empty(&blkg->q_node));
	WARN_ON_ONCE(hlist_unhashed(&blkg->blkcg_node));

	क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
		काष्ठा blkcg_policy *pol = blkcg_policy[i];

		अगर (blkg->pd[i] && pol->pd_offline_fn)
			pol->pd_offline_fn(blkg->pd[i]);
	पूर्ण

	blkg->online = false;

	radix_tree_delete(&blkcg->blkg_tree, blkg->q->id);
	list_del_init(&blkg->q_node);
	hlist_del_init_rcu(&blkg->blkcg_node);

	/*
	 * Both setting lookup hपूर्णांक to and clearing it from @blkg are करोne
	 * under queue_lock.  If it's not poपूर्णांकing to @blkg now, it never
	 * will.  Hपूर्णांक assignment itself can race safely.
	 */
	अगर (rcu_access_poपूर्णांकer(blkcg->blkg_hपूर्णांक) == blkg)
		rcu_assign_poपूर्णांकer(blkcg->blkg_hपूर्णांक, शून्य);

	/*
	 * Put the reference taken at the समय of creation so that when all
	 * queues are gone, group can be destroyed.
	 */
	percpu_ref_समाप्त(&blkg->refcnt);
पूर्ण

/**
 * blkg_destroy_all - destroy all blkgs associated with a request_queue
 * @q: request_queue of पूर्णांकerest
 *
 * Destroy all blkgs associated with @q.
 */
अटल व्योम blkg_destroy_all(काष्ठा request_queue *q)
अणु
	काष्ठा blkcg_gq *blkg, *n;

	spin_lock_irq(&q->queue_lock);
	list_क्रम_each_entry_safe(blkg, n, &q->blkg_list, q_node) अणु
		काष्ठा blkcg *blkcg = blkg->blkcg;

		spin_lock(&blkcg->lock);
		blkg_destroy(blkg);
		spin_unlock(&blkcg->lock);
	पूर्ण

	q->root_blkg = शून्य;
	spin_unlock_irq(&q->queue_lock);
पूर्ण

अटल पूर्णांक blkcg_reset_stats(काष्ठा cgroup_subsys_state *css,
			     काष्ठा cftype *cftype, u64 val)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);
	काष्ठा blkcg_gq *blkg;
	पूर्णांक i, cpu;

	mutex_lock(&blkcg_pol_mutex);
	spin_lock_irq(&blkcg->lock);

	/*
	 * Note that stat reset is racy - it करोesn't synchronize against
	 * stat updates.  This is a debug feature which shouldn't exist
	 * anyway.  If you get hit by a race, retry.
	 */
	hlist_क्रम_each_entry(blkg, &blkcg->blkg_list, blkcg_node) अणु
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा blkg_iostat_set *bis =
				per_cpu_ptr(blkg->iostat_cpu, cpu);
			स_रखो(bis, 0, माप(*bis));
		पूर्ण
		स_रखो(&blkg->iostat, 0, माप(blkg->iostat));

		क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
			काष्ठा blkcg_policy *pol = blkcg_policy[i];

			अगर (blkg->pd[i] && pol->pd_reset_stats_fn)
				pol->pd_reset_stats_fn(blkg->pd[i]);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&blkcg->lock);
	mutex_unlock(&blkcg_pol_mutex);
	वापस 0;
पूर्ण

स्थिर अक्षर *blkg_dev_name(काष्ठा blkcg_gq *blkg)
अणु
	/* some drivers (floppy) instantiate a queue w/o disk रेजिस्टरed */
	अगर (blkg->q->backing_dev_info->dev)
		वापस bdi_dev_name(blkg->q->backing_dev_info);
	वापस शून्य;
पूर्ण

/**
 * blkcg_prपूर्णांक_blkgs - helper क्रम prपूर्णांकing per-blkg data
 * @sf: seq_file to prपूर्णांक to
 * @blkcg: blkcg of पूर्णांकerest
 * @prfill: fill function to prपूर्णांक out a blkg
 * @pol: policy in question
 * @data: data to be passed to @prfill
 * @show_total: to prपूर्णांक out sum of prfill वापस values or not
 *
 * This function invokes @prfill on each blkg of @blkcg अगर pd क्रम the
 * policy specअगरied by @pol exists.  @prfill is invoked with @sf, the
 * policy data and @data and the matching queue lock held.  If @show_total
 * is %true, the sum of the वापस values from @prfill is prपूर्णांकed with
 * "Total" label at the end.
 *
 * This is to be used to स्थिरruct prपूर्णांक functions क्रम
 * cftype->पढ़ो_seq_string method.
 */
व्योम blkcg_prपूर्णांक_blkgs(काष्ठा seq_file *sf, काष्ठा blkcg *blkcg,
		       u64 (*prfill)(काष्ठा seq_file *,
				     काष्ठा blkg_policy_data *, पूर्णांक),
		       स्थिर काष्ठा blkcg_policy *pol, पूर्णांक data,
		       bool show_total)
अणु
	काष्ठा blkcg_gq *blkg;
	u64 total = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(blkg, &blkcg->blkg_list, blkcg_node) अणु
		spin_lock_irq(&blkg->q->queue_lock);
		अगर (blkcg_policy_enabled(blkg->q, pol))
			total += prfill(sf, blkg->pd[pol->plid], data);
		spin_unlock_irq(&blkg->q->queue_lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (show_total)
		seq_म_लिखो(sf, "Total %llu\n", (अचिन्हित दीर्घ दीर्घ)total);
पूर्ण
EXPORT_SYMBOL_GPL(blkcg_prपूर्णांक_blkgs);

/**
 * __blkg_prfill_u64 - prfill helper क्रम a single u64 value
 * @sf: seq_file to prपूर्णांक to
 * @pd: policy निजी data of पूर्णांकerest
 * @v: value to prपूर्णांक
 *
 * Prपूर्णांक @v to @sf क्रम the device assocaited with @pd.
 */
u64 __blkg_prfill_u64(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd, u64 v)
अणु
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);

	अगर (!dname)
		वापस 0;

	seq_म_लिखो(sf, "%s %llu\n", dname, (अचिन्हित दीर्घ दीर्घ)v);
	वापस v;
पूर्ण
EXPORT_SYMBOL_GPL(__blkg_prfill_u64);

/* Perक्रमms queue bypass and policy enabled checks then looks up blkg. */
अटल काष्ठा blkcg_gq *blkg_lookup_check(काष्ठा blkcg *blkcg,
					  स्थिर काष्ठा blkcg_policy *pol,
					  काष्ठा request_queue *q)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	lockdep_निश्चित_held(&q->queue_lock);

	अगर (!blkcg_policy_enabled(q, pol))
		वापस ERR_PTR(-EOPNOTSUPP);
	वापस __blkg_lookup(blkcg, q, true /* update_hपूर्णांक */);
पूर्ण

/**
 * blkcg_conf_खोलो_bdev - parse and खोलो bdev क्रम per-blkg config update
 * @inputp: input string poपूर्णांकer
 *
 * Parse the device node prefix part, MAJ:MIN, of per-blkg config update
 * from @input and get and वापस the matching bdev.  *@inputp is
 * updated to poपूर्णांक past the device node prefix.  Returns an ERR_PTR()
 * value on error.
 *
 * Use this function अगरf blkg_conf_prep() can't be used क्रम some reason.
 */
काष्ठा block_device *blkcg_conf_खोलो_bdev(अक्षर **inputp)
अणु
	अक्षर *input = *inputp;
	अचिन्हित पूर्णांक major, minor;
	काष्ठा block_device *bdev;
	पूर्णांक key_len;

	अगर (माला_पूछो(input, "%u:%u%n", &major, &minor, &key_len) != 2)
		वापस ERR_PTR(-EINVAL);

	input += key_len;
	अगर (!है_खाली(*input))
		वापस ERR_PTR(-EINVAL);
	input = skip_spaces(input);

	bdev = blkdev_get_no_खोलो(MKDEV(major, minor));
	अगर (!bdev)
		वापस ERR_PTR(-ENODEV);
	अगर (bdev_is_partition(bdev)) अणु
		blkdev_put_no_खोलो(bdev);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	*inputp = input;
	वापस bdev;
पूर्ण

/**
 * blkg_conf_prep - parse and prepare क्रम per-blkg config update
 * @blkcg: target block cgroup
 * @pol: target policy
 * @input: input string
 * @ctx: blkg_conf_ctx to be filled
 *
 * Parse per-blkg config update from @input and initialize @ctx with the
 * result.  @ctx->blkg poपूर्णांकs to the blkg to be updated and @ctx->body the
 * part of @input following MAJ:MIN.  This function वापसs with RCU पढ़ो
 * lock and queue lock held and must be paired with blkg_conf_finish().
 */
पूर्णांक blkg_conf_prep(काष्ठा blkcg *blkcg, स्थिर काष्ठा blkcg_policy *pol,
		   अक्षर *input, काष्ठा blkg_conf_ctx *ctx)
	__acquires(rcu) __acquires(&bdev->bd_disk->queue->queue_lock)
अणु
	काष्ठा block_device *bdev;
	काष्ठा request_queue *q;
	काष्ठा blkcg_gq *blkg;
	पूर्णांक ret;

	bdev = blkcg_conf_खोलो_bdev(&input);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);

	q = bdev->bd_disk->queue;

	rcu_पढ़ो_lock();
	spin_lock_irq(&q->queue_lock);

	blkg = blkg_lookup_check(blkcg, pol, q);
	अगर (IS_ERR(blkg)) अणु
		ret = PTR_ERR(blkg);
		जाओ fail_unlock;
	पूर्ण

	अगर (blkg)
		जाओ success;

	/*
	 * Create blkgs walking करोwn from blkcg_root to @blkcg, so that all
	 * non-root blkgs have access to their parents.
	 */
	जबतक (true) अणु
		काष्ठा blkcg *pos = blkcg;
		काष्ठा blkcg *parent;
		काष्ठा blkcg_gq *new_blkg;

		parent = blkcg_parent(blkcg);
		जबतक (parent && !__blkg_lookup(parent, q, false)) अणु
			pos = parent;
			parent = blkcg_parent(parent);
		पूर्ण

		/* Drop locks to करो new blkg allocation with GFP_KERNEL. */
		spin_unlock_irq(&q->queue_lock);
		rcu_पढ़ो_unlock();

		new_blkg = blkg_alloc(pos, q, GFP_KERNEL);
		अगर (unlikely(!new_blkg)) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		अगर (radix_tree_preload(GFP_KERNEL)) अणु
			blkg_मुक्त(new_blkg);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		rcu_पढ़ो_lock();
		spin_lock_irq(&q->queue_lock);

		blkg = blkg_lookup_check(pos, pol, q);
		अगर (IS_ERR(blkg)) अणु
			ret = PTR_ERR(blkg);
			blkg_मुक्त(new_blkg);
			जाओ fail_preloaded;
		पूर्ण

		अगर (blkg) अणु
			blkg_मुक्त(new_blkg);
		पूर्ण अन्यथा अणु
			blkg = blkg_create(pos, q, new_blkg);
			अगर (IS_ERR(blkg)) अणु
				ret = PTR_ERR(blkg);
				जाओ fail_preloaded;
			पूर्ण
		पूर्ण

		radix_tree_preload_end();

		अगर (pos == blkcg)
			जाओ success;
	पूर्ण
success:
	ctx->bdev = bdev;
	ctx->blkg = blkg;
	ctx->body = input;
	वापस 0;

fail_preloaded:
	radix_tree_preload_end();
fail_unlock:
	spin_unlock_irq(&q->queue_lock);
	rcu_पढ़ो_unlock();
fail:
	blkdev_put_no_खोलो(bdev);
	/*
	 * If queue was bypassing, we should retry.  Do so after a
	 * लघु msleep().  It isn't strictly necessary but queue
	 * can be bypassing क्रम some समय and it's always nice to
	 * aव्योम busy looping.
	 */
	अगर (ret == -EBUSY) अणु
		msleep(10);
		ret = restart_syscall();
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blkg_conf_prep);

/**
 * blkg_conf_finish - finish up per-blkg config update
 * @ctx: blkg_conf_ctx पूर्णांकiailized by blkg_conf_prep()
 *
 * Finish up after per-blkg config update.  This function must be paired
 * with blkg_conf_prep().
 */
व्योम blkg_conf_finish(काष्ठा blkg_conf_ctx *ctx)
	__releases(&ctx->bdev->bd_disk->queue->queue_lock) __releases(rcu)
अणु
	spin_unlock_irq(&ctx->bdev->bd_disk->queue->queue_lock);
	rcu_पढ़ो_unlock();
	blkdev_put_no_खोलो(ctx->bdev);
पूर्ण
EXPORT_SYMBOL_GPL(blkg_conf_finish);

अटल व्योम blkg_iostat_set(काष्ठा blkg_iostat *dst, काष्ठा blkg_iostat *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_IOSTAT_NR; i++) अणु
		dst->bytes[i] = src->bytes[i];
		dst->ios[i] = src->ios[i];
	पूर्ण
पूर्ण

अटल व्योम blkg_iostat_add(काष्ठा blkg_iostat *dst, काष्ठा blkg_iostat *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_IOSTAT_NR; i++) अणु
		dst->bytes[i] += src->bytes[i];
		dst->ios[i] += src->ios[i];
	पूर्ण
पूर्ण

अटल व्योम blkg_iostat_sub(काष्ठा blkg_iostat *dst, काष्ठा blkg_iostat *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_IOSTAT_NR; i++) अणु
		dst->bytes[i] -= src->bytes[i];
		dst->ios[i] -= src->ios[i];
	पूर्ण
पूर्ण

अटल व्योम blkcg_rstat_flush(काष्ठा cgroup_subsys_state *css, पूर्णांक cpu)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);
	काष्ठा blkcg_gq *blkg;

	/* Root-level stats are sourced from प्रणाली-wide IO stats */
	अगर (!cgroup_parent(css->cgroup))
		वापस;

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(blkg, &blkcg->blkg_list, blkcg_node) अणु
		काष्ठा blkcg_gq *parent = blkg->parent;
		काष्ठा blkg_iostat_set *bisc = per_cpu_ptr(blkg->iostat_cpu, cpu);
		काष्ठा blkg_iostat cur, delta;
		अचिन्हित पूर्णांक seq;

		/* fetch the current per-cpu values */
		करो अणु
			seq = u64_stats_fetch_begin(&bisc->sync);
			blkg_iostat_set(&cur, &bisc->cur);
		पूर्ण जबतक (u64_stats_fetch_retry(&bisc->sync, seq));

		/* propagate percpu delta to global */
		u64_stats_update_begin(&blkg->iostat.sync);
		blkg_iostat_set(&delta, &cur);
		blkg_iostat_sub(&delta, &bisc->last);
		blkg_iostat_add(&blkg->iostat.cur, &delta);
		blkg_iostat_add(&bisc->last, &delta);
		u64_stats_update_end(&blkg->iostat.sync);

		/* propagate global delta to parent (unless that's root) */
		अगर (parent && parent->parent) अणु
			u64_stats_update_begin(&parent->iostat.sync);
			blkg_iostat_set(&delta, &blkg->iostat.cur);
			blkg_iostat_sub(&delta, &blkg->iostat.last);
			blkg_iostat_add(&parent->iostat.cur, &delta);
			blkg_iostat_add(&blkg->iostat.last, &delta);
			u64_stats_update_end(&parent->iostat.sync);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * We source root cgroup stats from the प्रणाली-wide stats to aव्योम
 * tracking the same inक्रमmation twice and incurring overhead when no
 * cgroups are defined. For that reason, cgroup_rstat_flush in
 * blkcg_prपूर्णांक_stat करोes not actually fill out the iostat in the root
 * cgroup's blkcg_gq.
 *
 * However, we would like to re-use the prपूर्णांकing code between the root and
 * non-root cgroups to the extent possible. For that reason, we simulate
 * flushing the root cgroup's stats by explicitly filling in the iostat
 * with disk level statistics.
 */
अटल व्योम blkcg_fill_root_iostats(व्योम)
अणु
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	class_dev_iter_init(&iter, &block_class, शून्य, &disk_type);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		काष्ठा block_device *bdev = dev_to_bdev(dev);
		काष्ठा blkcg_gq *blkg =
			blk_queue_root_blkg(bdev->bd_disk->queue);
		काष्ठा blkg_iostat पंचांगp;
		पूर्णांक cpu;

		स_रखो(&पंचांगp, 0, माप(पंचांगp));
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा disk_stats *cpu_dkstats;

			cpu_dkstats = per_cpu_ptr(bdev->bd_stats, cpu);
			पंचांगp.ios[BLKG_IOSTAT_READ] +=
				cpu_dkstats->ios[STAT_READ];
			पंचांगp.ios[BLKG_IOSTAT_WRITE] +=
				cpu_dkstats->ios[STAT_WRITE];
			पंचांगp.ios[BLKG_IOSTAT_DISCARD] +=
				cpu_dkstats->ios[STAT_DISCARD];
			// convert sectors to bytes
			पंचांगp.bytes[BLKG_IOSTAT_READ] +=
				cpu_dkstats->sectors[STAT_READ] << 9;
			पंचांगp.bytes[BLKG_IOSTAT_WRITE] +=
				cpu_dkstats->sectors[STAT_WRITE] << 9;
			पंचांगp.bytes[BLKG_IOSTAT_DISCARD] +=
				cpu_dkstats->sectors[STAT_DISCARD] << 9;

			u64_stats_update_begin(&blkg->iostat.sync);
			blkg_iostat_set(&blkg->iostat.cur, &पंचांगp);
			u64_stats_update_end(&blkg->iostat.sync);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक blkcg_prपूर्णांक_stat(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));
	काष्ठा blkcg_gq *blkg;

	अगर (!seq_css(sf)->parent)
		blkcg_fill_root_iostats();
	अन्यथा
		cgroup_rstat_flush(blkcg->css.cgroup);

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(blkg, &blkcg->blkg_list, blkcg_node) अणु
		काष्ठा blkg_iostat_set *bis = &blkg->iostat;
		स्थिर अक्षर *dname;
		अक्षर *buf;
		u64 rbytes, wbytes, rios, wios, dbytes, dios;
		माप_प्रकार size = seq_get_buf(sf, &buf), off = 0;
		पूर्णांक i;
		bool has_stats = false;
		अचिन्हित seq;

		spin_lock_irq(&blkg->q->queue_lock);

		अगर (!blkg->online)
			जाओ skip;

		dname = blkg_dev_name(blkg);
		अगर (!dname)
			जाओ skip;

		/*
		 * Hooray string manipulation, count is the size written NOT
		 * INCLUDING THE \0, so size is now count+1 less than what we
		 * had beक्रमe, but we want to start writing the next bit from
		 * the \0 so we only add count to buf.
		 */
		off += scnम_लिखो(buf+off, size-off, "%s ", dname);

		करो अणु
			seq = u64_stats_fetch_begin(&bis->sync);

			rbytes = bis->cur.bytes[BLKG_IOSTAT_READ];
			wbytes = bis->cur.bytes[BLKG_IOSTAT_WRITE];
			dbytes = bis->cur.bytes[BLKG_IOSTAT_DISCARD];
			rios = bis->cur.ios[BLKG_IOSTAT_READ];
			wios = bis->cur.ios[BLKG_IOSTAT_WRITE];
			dios = bis->cur.ios[BLKG_IOSTAT_DISCARD];
		पूर्ण जबतक (u64_stats_fetch_retry(&bis->sync, seq));

		अगर (rbytes || wbytes || rios || wios) अणु
			has_stats = true;
			off += scnम_लिखो(buf+off, size-off,
					 "rbytes=%llu wbytes=%llu rios=%llu wios=%llu dbytes=%llu dios=%llu",
					 rbytes, wbytes, rios, wios,
					 dbytes, dios);
		पूर्ण

		अगर (blkcg_debug_stats && atomic_पढ़ो(&blkg->use_delay)) अणु
			has_stats = true;
			off += scnम_लिखो(buf+off, size-off,
					 " use_delay=%d delay_nsec=%llu",
					 atomic_पढ़ो(&blkg->use_delay),
					(अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&blkg->delay_nsec));
		पूर्ण

		क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
			काष्ठा blkcg_policy *pol = blkcg_policy[i];
			माप_प्रकार written;

			अगर (!blkg->pd[i] || !pol->pd_stat_fn)
				जारी;

			written = pol->pd_stat_fn(blkg->pd[i], buf+off, size-off);
			अगर (written)
				has_stats = true;
			off += written;
		पूर्ण

		अगर (has_stats) अणु
			अगर (off < size - 1) अणु
				off += scnम_लिखो(buf+off, size-off, "\n");
				seq_commit(sf, off);
			पूर्ण अन्यथा अणु
				seq_commit(sf, -1);
			पूर्ण
		पूर्ण
	skip:
		spin_unlock_irq(&blkg->q->queue_lock);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल काष्ठा cftype blkcg_files[] = अणु
	अणु
		.name = "stat",
		.seq_show = blkcg_prपूर्णांक_stat,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

अटल काष्ठा cftype blkcg_legacy_files[] = अणु
	अणु
		.name = "reset_stats",
		.ग_लिखो_u64 = blkcg_reset_stats,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

/*
 * blkcg deकाष्ठाion is a three-stage process.
 *
 * 1. Deकाष्ठाion starts.  The blkcg_css_offline() callback is invoked
 *    which offlines ग_लिखोback.  Here we tie the next stage of blkg deकाष्ठाion
 *    to the completion of ग_लिखोback associated with the blkcg.  This lets us
 *    aव्योम punting potentially large amounts of outstanding ग_लिखोback to root
 *    जबतक मुख्यtaining any ongoing policies.  The next stage is triggered when
 *    the nr_cgwbs count goes to zero.
 *
 * 2. When the nr_cgwbs count goes to zero, blkcg_destroy_blkgs() is called
 *    and handles the deकाष्ठाion of blkgs.  Here the css reference held by
 *    the blkg is put back eventually allowing blkcg_css_मुक्त() to be called.
 *    This work may occur in cgwb_release_workfn() on the cgwb_release
 *    workqueue.  Any submitted ios that fail to get the blkg ref will be
 *    punted to the root_blkg.
 *
 * 3. Once the blkcg ref count goes to zero, blkcg_css_मुक्त() is called.
 *    This finally मुक्तs the blkcg.
 */

/**
 * blkcg_css_offline - cgroup css_offline callback
 * @css: css of पूर्णांकerest
 *
 * This function is called when @css is about to go away.  Here the cgwbs are
 * offlined first and only once ग_लिखोback associated with the blkcg has
 * finished करो we start step 2 (see above).
 */
अटल व्योम blkcg_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);

	/* this prevents anyone from attaching or migrating to this blkcg */
	wb_blkcg_offline(blkcg);

	/* put the base online pin allowing step 2 to be triggered */
	blkcg_unpin_online(blkcg);
पूर्ण

/**
 * blkcg_destroy_blkgs - responsible क्रम shooting करोwn blkgs
 * @blkcg: blkcg of पूर्णांकerest
 *
 * blkgs should be हटाओd जबतक holding both q and blkcg locks.  As blkcg lock
 * is nested inside q lock, this function perक्रमms reverse द्विगुन lock dancing.
 * Destroying the blkgs releases the reference held on the blkcg's css allowing
 * blkcg_css_मुक्त to eventually be called.
 *
 * This is the blkcg counterpart of ioc_release_fn().
 */
व्योम blkcg_destroy_blkgs(काष्ठा blkcg *blkcg)
अणु
	might_sleep();

	spin_lock_irq(&blkcg->lock);

	जबतक (!hlist_empty(&blkcg->blkg_list)) अणु
		काष्ठा blkcg_gq *blkg = hlist_entry(blkcg->blkg_list.first,
						काष्ठा blkcg_gq, blkcg_node);
		काष्ठा request_queue *q = blkg->q;

		अगर (need_resched() || !spin_trylock(&q->queue_lock)) अणु
			/*
			 * Given that the प्रणाली can accumulate a huge number
			 * of blkgs in pathological हालs, check to see अगर we
			 * need to rescheduling to aव्योम softlockup.
			 */
			spin_unlock_irq(&blkcg->lock);
			cond_resched();
			spin_lock_irq(&blkcg->lock);
			जारी;
		पूर्ण

		blkg_destroy(blkg);
		spin_unlock(&q->queue_lock);
	पूर्ण

	spin_unlock_irq(&blkcg->lock);
पूर्ण

अटल व्योम blkcg_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);
	पूर्णांक i;

	mutex_lock(&blkcg_pol_mutex);

	list_del(&blkcg->all_blkcgs_node);

	क्रम (i = 0; i < BLKCG_MAX_POLS; i++)
		अगर (blkcg->cpd[i])
			blkcg_policy[i]->cpd_मुक्त_fn(blkcg->cpd[i]);

	mutex_unlock(&blkcg_pol_mutex);

	kमुक्त(blkcg);
पूर्ण

अटल काष्ठा cgroup_subsys_state *
blkcg_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा blkcg *blkcg;
	काष्ठा cgroup_subsys_state *ret;
	पूर्णांक i;

	mutex_lock(&blkcg_pol_mutex);

	अगर (!parent_css) अणु
		blkcg = &blkcg_root;
	पूर्ण अन्यथा अणु
		blkcg = kzalloc(माप(*blkcg), GFP_KERNEL);
		अगर (!blkcg) अणु
			ret = ERR_PTR(-ENOMEM);
			जाओ unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < BLKCG_MAX_POLS ; i++) अणु
		काष्ठा blkcg_policy *pol = blkcg_policy[i];
		काष्ठा blkcg_policy_data *cpd;

		/*
		 * If the policy hasn't been attached yet, रुको क्रम it
		 * to be attached beक्रमe करोing anything अन्यथा. Otherwise,
		 * check अगर the policy requires any specअगरic per-cgroup
		 * data: अगर it करोes, allocate and initialize it.
		 */
		अगर (!pol || !pol->cpd_alloc_fn)
			जारी;

		cpd = pol->cpd_alloc_fn(GFP_KERNEL);
		अगर (!cpd) अणु
			ret = ERR_PTR(-ENOMEM);
			जाओ मुक्त_pd_blkcg;
		पूर्ण
		blkcg->cpd[i] = cpd;
		cpd->blkcg = blkcg;
		cpd->plid = i;
		अगर (pol->cpd_init_fn)
			pol->cpd_init_fn(cpd);
	पूर्ण

	spin_lock_init(&blkcg->lock);
	refcount_set(&blkcg->online_pin, 1);
	INIT_RADIX_TREE(&blkcg->blkg_tree, GFP_NOWAIT | __GFP_NOWARN);
	INIT_HLIST_HEAD(&blkcg->blkg_list);
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	INIT_LIST_HEAD(&blkcg->cgwb_list);
#पूर्ण_अगर
	list_add_tail(&blkcg->all_blkcgs_node, &all_blkcgs);

	mutex_unlock(&blkcg_pol_mutex);
	वापस &blkcg->css;

मुक्त_pd_blkcg:
	क्रम (i--; i >= 0; i--)
		अगर (blkcg->cpd[i])
			blkcg_policy[i]->cpd_मुक्त_fn(blkcg->cpd[i]);

	अगर (blkcg != &blkcg_root)
		kमुक्त(blkcg);
unlock:
	mutex_unlock(&blkcg_pol_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक blkcg_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(css);
	काष्ठा blkcg *parent = blkcg_parent(blkcg);

	/*
	 * blkcg_pin_online() is used to delay blkcg offline so that blkgs
	 * करोn't go offline जबतक cgwbs are still active on them.  Pin the
	 * parent so that offline always happens towards the root.
	 */
	अगर (parent)
		blkcg_pin_online(parent);
	वापस 0;
पूर्ण

/**
 * blkcg_init_queue - initialize blkcg part of request queue
 * @q: request_queue to initialize
 *
 * Called from blk_alloc_queue(). Responsible क्रम initializing blkcg
 * part of new request_queue @q.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक blkcg_init_queue(काष्ठा request_queue *q)
अणु
	काष्ठा blkcg_gq *new_blkg, *blkg;
	bool preloaded;
	पूर्णांक ret;

	new_blkg = blkg_alloc(&blkcg_root, q, GFP_KERNEL);
	अगर (!new_blkg)
		वापस -ENOMEM;

	preloaded = !radix_tree_preload(GFP_KERNEL);

	/* Make sure the root blkg exists. */
	rcu_पढ़ो_lock();
	spin_lock_irq(&q->queue_lock);
	blkg = blkg_create(&blkcg_root, q, new_blkg);
	अगर (IS_ERR(blkg))
		जाओ err_unlock;
	q->root_blkg = blkg;
	spin_unlock_irq(&q->queue_lock);
	rcu_पढ़ो_unlock();

	अगर (preloaded)
		radix_tree_preload_end();

	ret = blk_throtl_init(q);
	अगर (ret)
		जाओ err_destroy_all;

	ret = blk_iolatency_init(q);
	अगर (ret) अणु
		blk_throtl_निकास(q);
		जाओ err_destroy_all;
	पूर्ण
	वापस 0;

err_destroy_all:
	blkg_destroy_all(q);
	वापस ret;
err_unlock:
	spin_unlock_irq(&q->queue_lock);
	rcu_पढ़ो_unlock();
	अगर (preloaded)
		radix_tree_preload_end();
	वापस PTR_ERR(blkg);
पूर्ण

/**
 * blkcg_निकास_queue - निकास and release blkcg part of request_queue
 * @q: request_queue being released
 *
 * Called from blk_निकास_queue().  Responsible क्रम निकासing blkcg part.
 */
व्योम blkcg_निकास_queue(काष्ठा request_queue *q)
अणु
	blkg_destroy_all(q);
	blk_throtl_निकास(q);
पूर्ण

/*
 * We cannot support shared io contexts, as we have no mean to support
 * two tasks with the same ioc in two dअगरferent groups without major rework
 * of the मुख्य cic data काष्ठाures.  For now we allow a task to change
 * its cgroup only अगर it's the only owner of its ioc.
 */
अटल पूर्णांक blkcg_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *dst_css;
	काष्ठा io_context *ioc;
	पूर्णांक ret = 0;

	/* task_lock() is needed to aव्योम races with निकास_io_context() */
	cgroup_taskset_क्रम_each(task, dst_css, tset) अणु
		task_lock(task);
		ioc = task->io_context;
		अगर (ioc && atomic_पढ़ो(&ioc->nr_tasks) > 1)
			ret = -EINVAL;
		task_unlock(task);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम blkcg_bind(काष्ठा cgroup_subsys_state *root_css)
अणु
	पूर्णांक i;

	mutex_lock(&blkcg_pol_mutex);

	क्रम (i = 0; i < BLKCG_MAX_POLS; i++) अणु
		काष्ठा blkcg_policy *pol = blkcg_policy[i];
		काष्ठा blkcg *blkcg;

		अगर (!pol || !pol->cpd_bind_fn)
			जारी;

		list_क्रम_each_entry(blkcg, &all_blkcgs, all_blkcgs_node)
			अगर (blkcg->cpd[pol->plid])
				pol->cpd_bind_fn(blkcg->cpd[pol->plid]);
	पूर्ण
	mutex_unlock(&blkcg_pol_mutex);
पूर्ण

अटल व्योम blkcg_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->throttle_queue)
		blk_put_queue(tsk->throttle_queue);
	tsk->throttle_queue = शून्य;
पूर्ण

काष्ठा cgroup_subsys io_cgrp_subsys = अणु
	.css_alloc = blkcg_css_alloc,
	.css_online = blkcg_css_online,
	.css_offline = blkcg_css_offline,
	.css_मुक्त = blkcg_css_मुक्त,
	.can_attach = blkcg_can_attach,
	.css_rstat_flush = blkcg_rstat_flush,
	.bind = blkcg_bind,
	.dfl_cftypes = blkcg_files,
	.legacy_cftypes = blkcg_legacy_files,
	.legacy_name = "blkio",
	.निकास = blkcg_निकास,
#अगर_घोषित CONFIG_MEMCG
	/*
	 * This ensures that, अगर available, memcg is स्वतःmatically enabled
	 * together on the शेष hierarchy so that the owner cgroup can
	 * be retrieved from ग_लिखोback pages.
	 */
	.depends_on = 1 << memory_cgrp_id,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(io_cgrp_subsys);

/**
 * blkcg_activate_policy - activate a blkcg policy on a request_queue
 * @q: request_queue of पूर्णांकerest
 * @pol: blkcg policy to activate
 *
 * Activate @pol on @q.  Requires %GFP_KERNEL context.  @q goes through
 * bypass mode to populate its blkgs with policy_data क्रम @pol.
 *
 * Activation happens with @q bypassed, so nobody would be accessing blkgs
 * from IO path.  Update of each blkg is रक्षित by both queue and blkcg
 * locks so that holding either lock and testing blkcg_policy_enabled() is
 * always enough क्रम dereferencing policy data.
 *
 * The caller is responsible क्रम synchronizing [de]activations and policy
 * [un]रेजिस्टरations.  Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक blkcg_activate_policy(काष्ठा request_queue *q,
			  स्थिर काष्ठा blkcg_policy *pol)
अणु
	काष्ठा blkg_policy_data *pd_pपुनः_स्मृति = शून्य;
	काष्ठा blkcg_gq *blkg, *pinned_blkg = शून्य;
	पूर्णांक ret;

	अगर (blkcg_policy_enabled(q, pol))
		वापस 0;

	अगर (queue_is_mq(q))
		blk_mq_मुक्तze_queue(q);
retry:
	spin_lock_irq(&q->queue_lock);

	/* blkg_list is pushed at the head, reverse walk to allocate parents first */
	list_क्रम_each_entry_reverse(blkg, &q->blkg_list, q_node) अणु
		काष्ठा blkg_policy_data *pd;

		अगर (blkg->pd[pol->plid])
			जारी;

		/* If pपुनः_स्मृति matches, use it; otherwise try GFP_NOWAIT */
		अगर (blkg == pinned_blkg) अणु
			pd = pd_pपुनः_स्मृति;
			pd_pपुनः_स्मृति = शून्य;
		पूर्ण अन्यथा अणु
			pd = pol->pd_alloc_fn(GFP_NOWAIT | __GFP_NOWARN, q,
					      blkg->blkcg);
		पूर्ण

		अगर (!pd) अणु
			/*
			 * GFP_NOWAIT failed.  Free the existing one and
			 * pपुनः_स्मृति क्रम @blkg w/ GFP_KERNEL.
			 */
			अगर (pinned_blkg)
				blkg_put(pinned_blkg);
			blkg_get(blkg);
			pinned_blkg = blkg;

			spin_unlock_irq(&q->queue_lock);

			अगर (pd_pपुनः_स्मृति)
				pol->pd_मुक्त_fn(pd_pपुनः_स्मृति);
			pd_pपुनः_स्मृति = pol->pd_alloc_fn(GFP_KERNEL, q,
						       blkg->blkcg);
			अगर (pd_pपुनः_स्मृति)
				जाओ retry;
			अन्यथा
				जाओ enomem;
		पूर्ण

		blkg->pd[pol->plid] = pd;
		pd->blkg = blkg;
		pd->plid = pol->plid;
	पूर्ण

	/* all allocated, init in the same order */
	अगर (pol->pd_init_fn)
		list_क्रम_each_entry_reverse(blkg, &q->blkg_list, q_node)
			pol->pd_init_fn(blkg->pd[pol->plid]);

	__set_bit(pol->plid, q->blkcg_pols);
	ret = 0;

	spin_unlock_irq(&q->queue_lock);
out:
	अगर (queue_is_mq(q))
		blk_mq_unमुक्तze_queue(q);
	अगर (pinned_blkg)
		blkg_put(pinned_blkg);
	अगर (pd_pपुनः_स्मृति)
		pol->pd_मुक्त_fn(pd_pपुनः_स्मृति);
	वापस ret;

enomem:
	/* alloc failed, nothing's initialized yet, मुक्त everything */
	spin_lock_irq(&q->queue_lock);
	list_क्रम_each_entry(blkg, &q->blkg_list, q_node) अणु
		अगर (blkg->pd[pol->plid]) अणु
			pol->pd_मुक्त_fn(blkg->pd[pol->plid]);
			blkg->pd[pol->plid] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&q->queue_lock);
	ret = -ENOMEM;
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(blkcg_activate_policy);

/**
 * blkcg_deactivate_policy - deactivate a blkcg policy on a request_queue
 * @q: request_queue of पूर्णांकerest
 * @pol: blkcg policy to deactivate
 *
 * Deactivate @pol on @q.  Follows the same synchronization rules as
 * blkcg_activate_policy().
 */
व्योम blkcg_deactivate_policy(काष्ठा request_queue *q,
			     स्थिर काष्ठा blkcg_policy *pol)
अणु
	काष्ठा blkcg_gq *blkg;

	अगर (!blkcg_policy_enabled(q, pol))
		वापस;

	अगर (queue_is_mq(q))
		blk_mq_मुक्तze_queue(q);

	spin_lock_irq(&q->queue_lock);

	__clear_bit(pol->plid, q->blkcg_pols);

	list_क्रम_each_entry(blkg, &q->blkg_list, q_node) अणु
		अगर (blkg->pd[pol->plid]) अणु
			अगर (pol->pd_offline_fn)
				pol->pd_offline_fn(blkg->pd[pol->plid]);
			pol->pd_मुक्त_fn(blkg->pd[pol->plid]);
			blkg->pd[pol->plid] = शून्य;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&q->queue_lock);

	अगर (queue_is_mq(q))
		blk_mq_unमुक्तze_queue(q);
पूर्ण
EXPORT_SYMBOL_GPL(blkcg_deactivate_policy);

/**
 * blkcg_policy_रेजिस्टर - रेजिस्टर a blkcg policy
 * @pol: blkcg policy to रेजिस्टर
 *
 * Register @pol with blkcg core.  Might sleep and @pol may be modअगरied on
 * successful registration.  Returns 0 on success and -त्रुटि_सं on failure.
 */
पूर्णांक blkcg_policy_रेजिस्टर(काष्ठा blkcg_policy *pol)
अणु
	काष्ठा blkcg *blkcg;
	पूर्णांक i, ret;

	mutex_lock(&blkcg_pol_रेजिस्टर_mutex);
	mutex_lock(&blkcg_pol_mutex);

	/* find an empty slot */
	ret = -ENOSPC;
	क्रम (i = 0; i < BLKCG_MAX_POLS; i++)
		अगर (!blkcg_policy[i])
			अवरोध;
	अगर (i >= BLKCG_MAX_POLS) अणु
		pr_warn("blkcg_policy_register: BLKCG_MAX_POLS too small\n");
		जाओ err_unlock;
	पूर्ण

	/* Make sure cpd/pd_alloc_fn and cpd/pd_मुक्त_fn in pairs */
	अगर ((!pol->cpd_alloc_fn ^ !pol->cpd_मुक्त_fn) ||
		(!pol->pd_alloc_fn ^ !pol->pd_मुक्त_fn))
		जाओ err_unlock;

	/* रेजिस्टर @pol */
	pol->plid = i;
	blkcg_policy[pol->plid] = pol;

	/* allocate and install cpd's */
	अगर (pol->cpd_alloc_fn) अणु
		list_क्रम_each_entry(blkcg, &all_blkcgs, all_blkcgs_node) अणु
			काष्ठा blkcg_policy_data *cpd;

			cpd = pol->cpd_alloc_fn(GFP_KERNEL);
			अगर (!cpd)
				जाओ err_मुक्त_cpds;

			blkcg->cpd[pol->plid] = cpd;
			cpd->blkcg = blkcg;
			cpd->plid = pol->plid;
			अगर (pol->cpd_init_fn)
				pol->cpd_init_fn(cpd);
		पूर्ण
	पूर्ण

	mutex_unlock(&blkcg_pol_mutex);

	/* everything is in place, add पूर्णांकf files क्रम the new policy */
	अगर (pol->dfl_cftypes)
		WARN_ON(cgroup_add_dfl_cftypes(&io_cgrp_subsys,
					       pol->dfl_cftypes));
	अगर (pol->legacy_cftypes)
		WARN_ON(cgroup_add_legacy_cftypes(&io_cgrp_subsys,
						  pol->legacy_cftypes));
	mutex_unlock(&blkcg_pol_रेजिस्टर_mutex);
	वापस 0;

err_मुक्त_cpds:
	अगर (pol->cpd_मुक्त_fn) अणु
		list_क्रम_each_entry(blkcg, &all_blkcgs, all_blkcgs_node) अणु
			अगर (blkcg->cpd[pol->plid]) अणु
				pol->cpd_मुक्त_fn(blkcg->cpd[pol->plid]);
				blkcg->cpd[pol->plid] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	blkcg_policy[pol->plid] = शून्य;
err_unlock:
	mutex_unlock(&blkcg_pol_mutex);
	mutex_unlock(&blkcg_pol_रेजिस्टर_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blkcg_policy_रेजिस्टर);

/**
 * blkcg_policy_unरेजिस्टर - unरेजिस्टर a blkcg policy
 * @pol: blkcg policy to unरेजिस्टर
 *
 * Unकरो blkcg_policy_रेजिस्टर(@pol).  Might sleep.
 */
व्योम blkcg_policy_unरेजिस्टर(काष्ठा blkcg_policy *pol)
अणु
	काष्ठा blkcg *blkcg;

	mutex_lock(&blkcg_pol_रेजिस्टर_mutex);

	अगर (WARN_ON(blkcg_policy[pol->plid] != pol))
		जाओ out_unlock;

	/* समाप्त the पूर्णांकf files first */
	अगर (pol->dfl_cftypes)
		cgroup_rm_cftypes(pol->dfl_cftypes);
	अगर (pol->legacy_cftypes)
		cgroup_rm_cftypes(pol->legacy_cftypes);

	/* हटाओ cpds and unरेजिस्टर */
	mutex_lock(&blkcg_pol_mutex);

	अगर (pol->cpd_मुक्त_fn) अणु
		list_क्रम_each_entry(blkcg, &all_blkcgs, all_blkcgs_node) अणु
			अगर (blkcg->cpd[pol->plid]) अणु
				pol->cpd_मुक्त_fn(blkcg->cpd[pol->plid]);
				blkcg->cpd[pol->plid] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	blkcg_policy[pol->plid] = शून्य;

	mutex_unlock(&blkcg_pol_mutex);
out_unlock:
	mutex_unlock(&blkcg_pol_रेजिस्टर_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(blkcg_policy_unरेजिस्टर);

bool __blkcg_punt_bio_submit(काष्ठा bio *bio)
अणु
	काष्ठा blkcg_gq *blkg = bio->bi_blkg;

	/* consume the flag first */
	bio->bi_opf &= ~REQ_CGROUP_PUNT;

	/* never bounce क्रम the root cgroup */
	अगर (!blkg->parent)
		वापस false;

	spin_lock_bh(&blkg->async_bio_lock);
	bio_list_add(&blkg->async_bios, bio);
	spin_unlock_bh(&blkg->async_bio_lock);

	queue_work(blkcg_punt_bio_wq, &blkg->async_bio_work);
	वापस true;
पूर्ण

/*
 * Scale the accumulated delay based on how दीर्घ it has been since we updated
 * the delay.  We only call this when we are adding delay, in हाल it's been a
 * जबतक since we added delay, and when we are checking to see अगर we need to
 * delay a task, to account क्रम any delays that may have occurred.
 */
अटल व्योम blkcg_scale_delay(काष्ठा blkcg_gq *blkg, u64 now)
अणु
	u64 old = atomic64_पढ़ो(&blkg->delay_start);

	/* negative use_delay means no scaling, see blkcg_set_delay() */
	अगर (atomic_पढ़ो(&blkg->use_delay) < 0)
		वापस;

	/*
	 * We only want to scale करोwn every second.  The idea here is that we
	 * want to delay people क्रम min(delay_nsec, NSEC_PER_SEC) in a certain
	 * समय winकरोw.  We only want to throttle tasks क्रम recent delay that
	 * has occurred, in 1 second समय winकरोws since that's the maximum
	 * things can be throttled.  We save the current delay winकरोw in
	 * blkg->last_delay so we know what amount is still left to be अक्षरged
	 * to the blkg from this poपूर्णांक onward.  blkg->last_use keeps track of
	 * the use_delay counter.  The idea is अगर we're unthrottling the blkg we
	 * are ok with whatever is happening now, and we can take away more of
	 * the accumulated delay as we've alपढ़ोy throttled enough that
	 * everybody is happy with their IO latencies.
	 */
	अगर (समय_beक्रमe64(old + NSEC_PER_SEC, now) &&
	    atomic64_cmpxchg(&blkg->delay_start, old, now) == old) अणु
		u64 cur = atomic64_पढ़ो(&blkg->delay_nsec);
		u64 sub = min_t(u64, blkg->last_delay, now - old);
		पूर्णांक cur_use = atomic_पढ़ो(&blkg->use_delay);

		/*
		 * We've been unthrottled, subtract a larger chunk of our
		 * accumulated delay.
		 */
		अगर (cur_use < blkg->last_use)
			sub = max_t(u64, sub, blkg->last_delay >> 1);

		/*
		 * This shouldn't happen, but handle it anyway.  Our delay_nsec
		 * should only ever be growing except here where we subtract out
		 * min(last_delay, 1 second), but lord knows bugs happen and I'd
		 * rather not end up with negative numbers.
		 */
		अगर (unlikely(cur < sub)) अणु
			atomic64_set(&blkg->delay_nsec, 0);
			blkg->last_delay = 0;
		पूर्ण अन्यथा अणु
			atomic64_sub(sub, &blkg->delay_nsec);
			blkg->last_delay = cur - sub;
		पूर्ण
		blkg->last_use = cur_use;
	पूर्ण
पूर्ण

/*
 * This is called when we want to actually walk up the hierarchy and check to
 * see अगर we need to throttle, and then actually throttle अगर there is some
 * accumulated delay.  This should only be called upon वापस to user space so
 * we're not holding some lock that would induce a priority inversion.
 */
अटल व्योम blkcg_maybe_throttle_blkg(काष्ठा blkcg_gq *blkg, bool use_memdelay)
अणु
	अचिन्हित दीर्घ pflags;
	bool clamp;
	u64 now = kसमय_प्रकारo_ns(kसमय_get());
	u64 exp;
	u64 delay_nsec = 0;
	पूर्णांक tok;

	जबतक (blkg->parent) अणु
		पूर्णांक use_delay = atomic_पढ़ो(&blkg->use_delay);

		अगर (use_delay) अणु
			u64 this_delay;

			blkcg_scale_delay(blkg, now);
			this_delay = atomic64_पढ़ो(&blkg->delay_nsec);
			अगर (this_delay > delay_nsec) अणु
				delay_nsec = this_delay;
				clamp = use_delay > 0;
			पूर्ण
		पूर्ण
		blkg = blkg->parent;
	पूर्ण

	अगर (!delay_nsec)
		वापस;

	/*
	 * Let's not sleep for all eternity if we've amassed a huge delay.
	 * Swapping or metadata IO can accumulate 10's of seconds worth of
	 * delay, and we want userspace to be able to करो _something_ so cap the
	 * delays at 0.25s. If there's 10's of seconds worth of delay then the
	 * tasks will be delayed क्रम 0.25 second क्रम every syscall. If
	 * blkcg_set_delay() was used as indicated by negative use_delay, the
	 * caller is responsible क्रम regulating the range.
	 */
	अगर (clamp)
		delay_nsec = min_t(u64, delay_nsec, 250 * NSEC_PER_MSEC);

	अगर (use_memdelay)
		psi_memstall_enter(&pflags);

	exp = kसमय_add_ns(now, delay_nsec);
	tok = io_schedule_prepare();
	करो अणु
		__set_current_state(TASK_KILLABLE);
		अगर (!schedule_hrसमयout(&exp, HRTIMER_MODE_ABS))
			अवरोध;
	पूर्ण जबतक (!fatal_संकेत_pending(current));
	io_schedule_finish(tok);

	अगर (use_memdelay)
		psi_memstall_leave(&pflags);
पूर्ण

/**
 * blkcg_maybe_throttle_current - throttle the current task अगर it has been marked
 *
 * This is only called अगर we've been marked with set_notअगरy_resume().  Obviously
 * we can be set_notअगरy_resume() क्रम reasons other than blkcg throttling, so we
 * check to see अगर current->throttle_queue is set and अगर not this करोesn't करो
 * anything.  This should only ever be called by the resume code, it's not meant
 * to be called by people willy-nilly as it will actually करो the work to
 * throttle the task अगर it is setup क्रम throttling.
 */
व्योम blkcg_maybe_throttle_current(व्योम)
अणु
	काष्ठा request_queue *q = current->throttle_queue;
	काष्ठा cgroup_subsys_state *css;
	काष्ठा blkcg *blkcg;
	काष्ठा blkcg_gq *blkg;
	bool use_memdelay = current->use_memdelay;

	अगर (!q)
		वापस;

	current->throttle_queue = शून्य;
	current->use_memdelay = false;

	rcu_पढ़ो_lock();
	css = kthपढ़ो_blkcg();
	अगर (css)
		blkcg = css_to_blkcg(css);
	अन्यथा
		blkcg = css_to_blkcg(task_css(current, io_cgrp_id));

	अगर (!blkcg)
		जाओ out;
	blkg = blkg_lookup(blkcg, q);
	अगर (!blkg)
		जाओ out;
	अगर (!blkg_tryget(blkg))
		जाओ out;
	rcu_पढ़ो_unlock();

	blkcg_maybe_throttle_blkg(blkg, use_memdelay);
	blkg_put(blkg);
	blk_put_queue(q);
	वापस;
out:
	rcu_पढ़ो_unlock();
	blk_put_queue(q);
पूर्ण

/**
 * blkcg_schedule_throttle - this task needs to check क्रम throttling
 * @q: the request queue IO was submitted on
 * @use_memdelay: करो we अक्षरge this to memory delay क्रम PSI
 *
 * This is called by the IO controller when we know there's delay accumulated
 * क्रम the blkg क्रम this task.  We करो not pass the blkg because there are places
 * we call this that may not have that inक्रमmation, the swapping code क्रम
 * instance will only have a request_queue at that poपूर्णांक.  This set's the
 * notअगरy_resume क्रम the task to check and see अगर it requires throttling beक्रमe
 * वापसing to user space.
 *
 * We will only schedule once per syscall.  You can call this over and over
 * again and it will only करो the check once upon वापस to user space, and only
 * throttle once.  If the task needs to be throttled again it'll need to be
 * re-set at the next समय we see the task.
 */
व्योम blkcg_schedule_throttle(काष्ठा request_queue *q, bool use_memdelay)
अणु
	अगर (unlikely(current->flags & PF_KTHREAD))
		वापस;

	अगर (current->throttle_queue != q) अणु
		अगर (!blk_get_queue(q))
			वापस;

		अगर (current->throttle_queue)
			blk_put_queue(current->throttle_queue);
		current->throttle_queue = q;
	पूर्ण

	अगर (use_memdelay)
		current->use_memdelay = use_memdelay;
	set_notअगरy_resume(current);
पूर्ण

/**
 * blkcg_add_delay - add delay to this blkg
 * @blkg: blkg of पूर्णांकerest
 * @now: the current समय in nanoseconds
 * @delta: how many nanoseconds of delay to add
 *
 * Charge @delta to the blkg's current delay accumulation.  This is used to
 * throttle tasks अगर an IO controller thinks we need more throttling.
 */
व्योम blkcg_add_delay(काष्ठा blkcg_gq *blkg, u64 now, u64 delta)
अणु
	अगर (WARN_ON_ONCE(atomic_पढ़ो(&blkg->use_delay) < 0))
		वापस;
	blkcg_scale_delay(blkg, now);
	atomic64_add(delta, &blkg->delay_nsec);
पूर्ण

/**
 * blkg_tryget_बंदst - try and get a blkg ref on the बंदt blkg
 * @bio: target bio
 * @css: target css
 *
 * As the failure mode here is to walk up the blkg tree, this ensure that the
 * blkg->parent poपूर्णांकers are always valid.  This वापसs the blkg that it ended
 * up taking a reference on or %शून्य अगर no reference was taken.
 */
अटल अंतरभूत काष्ठा blkcg_gq *blkg_tryget_बंदst(काष्ठा bio *bio,
		काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा blkcg_gq *blkg, *ret_blkg = शून्य;

	rcu_पढ़ो_lock();
	blkg = blkg_lookup_create(css_to_blkcg(css),
				  bio->bi_bdev->bd_disk->queue);
	जबतक (blkg) अणु
		अगर (blkg_tryget(blkg)) अणु
			ret_blkg = blkg;
			अवरोध;
		पूर्ण
		blkg = blkg->parent;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret_blkg;
पूर्ण

/**
 * bio_associate_blkg_from_css - associate a bio with a specअगरied css
 * @bio: target bio
 * @css: target css
 *
 * Associate @bio with the blkg found by combining the css's blkg and the
 * request_queue of the @bio.  An association failure is handled by walking up
 * the blkg tree.  Thereक्रमe, the blkg associated can be anything between @blkg
 * and q->root_blkg.  This situation only happens when a cgroup is dying and
 * then the reमुख्यing bios will spill to the बंदst alive blkg.
 *
 * A reference will be taken on the blkg and will be released when @bio is
 * मुक्तd.
 */
व्योम bio_associate_blkg_from_css(काष्ठा bio *bio,
				 काष्ठा cgroup_subsys_state *css)
अणु
	अगर (bio->bi_blkg)
		blkg_put(bio->bi_blkg);

	अगर (css && css->parent) अणु
		bio->bi_blkg = blkg_tryget_बंदst(bio, css);
	पूर्ण अन्यथा अणु
		blkg_get(bio->bi_bdev->bd_disk->queue->root_blkg);
		bio->bi_blkg = bio->bi_bdev->bd_disk->queue->root_blkg;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bio_associate_blkg_from_css);

/**
 * bio_associate_blkg - associate a bio with a blkg
 * @bio: target bio
 *
 * Associate @bio with the blkg found from the bio's css and request_queue.
 * If one is not found, bio_lookup_blkg() creates the blkg.  If a blkg is
 * alपढ़ोy associated, the css is reused and association reकरोne as the
 * request_queue may have changed.
 */
व्योम bio_associate_blkg(काष्ठा bio *bio)
अणु
	काष्ठा cgroup_subsys_state *css;

	rcu_पढ़ो_lock();

	अगर (bio->bi_blkg)
		css = &bio_blkcg(bio)->css;
	अन्यथा
		css = blkcg_css();

	bio_associate_blkg_from_css(bio, css);

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(bio_associate_blkg);

/**
 * bio_clone_blkg_association - clone blkg association from src to dst bio
 * @dst: destination bio
 * @src: source bio
 */
व्योम bio_clone_blkg_association(काष्ठा bio *dst, काष्ठा bio *src)
अणु
	अगर (src->bi_blkg) अणु
		अगर (dst->bi_blkg)
			blkg_put(dst->bi_blkg);
		blkg_get(src->bi_blkg);
		dst->bi_blkg = src->bi_blkg;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bio_clone_blkg_association);

अटल पूर्णांक blk_cgroup_io_type(काष्ठा bio *bio)
अणु
	अगर (op_is_discard(bio->bi_opf))
		वापस BLKG_IOSTAT_DISCARD;
	अगर (op_is_ग_लिखो(bio->bi_opf))
		वापस BLKG_IOSTAT_WRITE;
	वापस BLKG_IOSTAT_READ;
पूर्ण

व्योम blk_cgroup_bio_start(काष्ठा bio *bio)
अणु
	पूर्णांक rwd = blk_cgroup_io_type(bio), cpu;
	काष्ठा blkg_iostat_set *bis;

	cpu = get_cpu();
	bis = per_cpu_ptr(bio->bi_blkg->iostat_cpu, cpu);
	u64_stats_update_begin(&bis->sync);

	/*
	 * If the bio is flagged with BIO_CGROUP_ACCT it means this is a split
	 * bio and we would have alपढ़ोy accounted क्रम the size of the bio.
	 */
	अगर (!bio_flagged(bio, BIO_CGROUP_ACCT)) अणु
		bio_set_flag(bio, BIO_CGROUP_ACCT);
		bis->cur.bytes[rwd] += bio->bi_iter.bi_size;
	पूर्ण
	bis->cur.ios[rwd]++;

	u64_stats_update_end(&bis->sync);
	अगर (cgroup_subsys_on_dfl(io_cgrp_subsys))
		cgroup_rstat_updated(bio->bi_blkg->blkcg->css.cgroup, cpu);
	put_cpu();
पूर्ण

अटल पूर्णांक __init blkcg_init(व्योम)
अणु
	blkcg_punt_bio_wq = alloc_workqueue("blkcg_punt_bio",
					    WQ_MEM_RECLAIM | WQ_FREEZABLE |
					    WQ_UNBOUND | WQ_SYSFS, 0);
	अगर (!blkcg_punt_bio_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
subsys_initcall(blkcg_init);

module_param(blkcg_debug_stats, bool, 0644);
MODULE_PARM_DESC(blkcg_debug_stats, "True if you want debug stats, false if not");
