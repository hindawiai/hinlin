<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Block device elevator/IO-scheduler.
 *
 *  Copyright (C) 2000 Andrea Arcangeli <andrea@suse.de> SuSE
 *
 * 30042000 Jens Axboe <axboe@kernel.dk> :
 *
 * Split the elevator a bit so that it is possible to choose a dअगरferent
 * one or even ग_लिखो a new "plug in". There are three pieces:
 * - elevator_fn, inserts a new request in the queue list
 * - elevator_merge_fn, decides whether a new buffer can be merged with
 *   an existing request
 * - elevator_dequeue_fn, called when a request is taken off the active list
 *
 * 20082000 Dave Jones <davej@suse.de> :
 * Removed tests क्रम max-bomb-segments, which was अवरोधing elvtune
 *  when run without -bN
 *
 * Jens:
 * - Rework again to work with bio instead of buffer_heads
 * - loose bi_dev comparisons, partition handling is right now
 * - completely modularize elevator setup and tearकरोwn
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/elevator.h>
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/compiler.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/hash.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/blk-cgroup.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq-sched.h"
#समावेश "blk-pm.h"
#समावेश "blk-wbt.h"

अटल DEFINE_SPINLOCK(elv_list_lock);
अटल LIST_HEAD(elv_list);

/*
 * Merge hash stuff.
 */
#घोषणा rq_hash_key(rq)		(blk_rq_pos(rq) + blk_rq_sectors(rq))

/*
 * Query io scheduler to see अगर the current process issuing bio may be
 * merged with rq.
 */
अटल पूर्णांक elv_iosched_allow_bio_merge(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e->type->ops.allow_merge)
		वापस e->type->ops.allow_merge(q, rq, bio);

	वापस 1;
पूर्ण

/*
 * can we safely merge with this request?
 */
bool elv_bio_merge_ok(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	अगर (!blk_rq_merge_ok(rq, bio))
		वापस false;

	अगर (!elv_iosched_allow_bio_merge(rq, bio))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(elv_bio_merge_ok);

अटल अंतरभूत bool elv_support_features(अचिन्हित पूर्णांक elv_features,
					अचिन्हित पूर्णांक required_features)
अणु
	वापस (required_features & elv_features) == required_features;
पूर्ण

/**
 * elevator_match - Test an elevator name and features
 * @e: Scheduler to test
 * @name: Elevator name to test
 * @required_features: Features that the elevator must provide
 *
 * Return true अगर the elevator @e name matches @name and अगर @e provides all
 * the features specअगरied by @required_features.
 */
अटल bool elevator_match(स्थिर काष्ठा elevator_type *e, स्थिर अक्षर *name,
			   अचिन्हित पूर्णांक required_features)
अणु
	अगर (!elv_support_features(e->elevator_features, required_features))
		वापस false;
	अगर (!म_भेद(e->elevator_name, name))
		वापस true;
	अगर (e->elevator_alias && !म_भेद(e->elevator_alias, name))
		वापस true;

	वापस false;
पूर्ण

/**
 * elevator_find - Find an elevator
 * @name: Name of the elevator to find
 * @required_features: Features that the elevator must provide
 *
 * Return the first रेजिस्टरed scheduler with name @name and supporting the
 * features @required_features and शून्य otherwise.
 */
अटल काष्ठा elevator_type *elevator_find(स्थिर अक्षर *name,
					   अचिन्हित पूर्णांक required_features)
अणु
	काष्ठा elevator_type *e;

	list_क्रम_each_entry(e, &elv_list, list) अणु
		अगर (elevator_match(e, name, required_features))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम elevator_put(काष्ठा elevator_type *e)
अणु
	module_put(e->elevator_owner);
पूर्ण

अटल काष्ठा elevator_type *elevator_get(काष्ठा request_queue *q,
					  स्थिर अक्षर *name, bool try_loading)
अणु
	काष्ठा elevator_type *e;

	spin_lock(&elv_list_lock);

	e = elevator_find(name, q->required_elevator_features);
	अगर (!e && try_loading) अणु
		spin_unlock(&elv_list_lock);
		request_module("%s-iosched", name);
		spin_lock(&elv_list_lock);
		e = elevator_find(name, q->required_elevator_features);
	पूर्ण

	अगर (e && !try_module_get(e->elevator_owner))
		e = शून्य;

	spin_unlock(&elv_list_lock);
	वापस e;
पूर्ण

अटल काष्ठा kobj_type elv_ktype;

काष्ठा elevator_queue *elevator_alloc(काष्ठा request_queue *q,
				  काष्ठा elevator_type *e)
अणु
	काष्ठा elevator_queue *eq;

	eq = kzalloc_node(माप(*eq), GFP_KERNEL, q->node);
	अगर (unlikely(!eq))
		वापस शून्य;

	eq->type = e;
	kobject_init(&eq->kobj, &elv_ktype);
	mutex_init(&eq->sysfs_lock);
	hash_init(eq->hash);

	वापस eq;
पूर्ण
EXPORT_SYMBOL(elevator_alloc);

अटल व्योम elevator_release(काष्ठा kobject *kobj)
अणु
	काष्ठा elevator_queue *e;

	e = container_of(kobj, काष्ठा elevator_queue, kobj);
	elevator_put(e->type);
	kमुक्त(e);
पूर्ण

व्योम __elevator_निकास(काष्ठा request_queue *q, काष्ठा elevator_queue *e)
अणु
	mutex_lock(&e->sysfs_lock);
	blk_mq_निकास_sched(q, e);
	mutex_unlock(&e->sysfs_lock);

	kobject_put(&e->kobj);
पूर्ण

अटल अंतरभूत व्योम __elv_rqhash_del(काष्ठा request *rq)
अणु
	hash_del(&rq->hash);
	rq->rq_flags &= ~RQF_HASHED;
पूर्ण

व्योम elv_rqhash_del(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	अगर (ELV_ON_HASH(rq))
		__elv_rqhash_del(rq);
पूर्ण
EXPORT_SYMBOL_GPL(elv_rqhash_del);

व्योम elv_rqhash_add(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	BUG_ON(ELV_ON_HASH(rq));
	hash_add(e->hash, &rq->hash, rq_hash_key(rq));
	rq->rq_flags |= RQF_HASHED;
पूर्ण
EXPORT_SYMBOL_GPL(elv_rqhash_add);

व्योम elv_rqhash_reposition(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	__elv_rqhash_del(rq);
	elv_rqhash_add(q, rq);
पूर्ण

काष्ठा request *elv_rqhash_find(काष्ठा request_queue *q, sector_t offset)
अणु
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा hlist_node *next;
	काष्ठा request *rq;

	hash_क्रम_each_possible_safe(e->hash, rq, next, hash, offset) अणु
		BUG_ON(!ELV_ON_HASH(rq));

		अगर (unlikely(!rq_mergeable(rq))) अणु
			__elv_rqhash_del(rq);
			जारी;
		पूर्ण

		अगर (rq_hash_key(rq) == offset)
			वापस rq;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * RB-tree support functions क्रम inserting/lookup/removal of requests
 * in a sorted RB tree.
 */
व्योम elv_rb_add(काष्ठा rb_root *root, काष्ठा request *rq)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा request *__rq;

	जबतक (*p) अणु
		parent = *p;
		__rq = rb_entry(parent, काष्ठा request, rb_node);

		अगर (blk_rq_pos(rq) < blk_rq_pos(__rq))
			p = &(*p)->rb_left;
		अन्यथा अगर (blk_rq_pos(rq) >= blk_rq_pos(__rq))
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&rq->rb_node, parent, p);
	rb_insert_color(&rq->rb_node, root);
पूर्ण
EXPORT_SYMBOL(elv_rb_add);

व्योम elv_rb_del(काष्ठा rb_root *root, काष्ठा request *rq)
अणु
	BUG_ON(RB_EMPTY_NODE(&rq->rb_node));
	rb_erase(&rq->rb_node, root);
	RB_CLEAR_NODE(&rq->rb_node);
पूर्ण
EXPORT_SYMBOL(elv_rb_del);

काष्ठा request *elv_rb_find(काष्ठा rb_root *root, sector_t sector)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा request *rq;

	जबतक (n) अणु
		rq = rb_entry(n, काष्ठा request, rb_node);

		अगर (sector < blk_rq_pos(rq))
			n = n->rb_left;
		अन्यथा अगर (sector > blk_rq_pos(rq))
			n = n->rb_right;
		अन्यथा
			वापस rq;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(elv_rb_find);

क्रमागत elv_merge elv_merge(काष्ठा request_queue *q, काष्ठा request **req,
		काष्ठा bio *bio)
अणु
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा request *__rq;

	/*
	 * Levels of merges:
	 * 	nomerges:  No merges at all attempted
	 * 	noxmerges: Only simple one-hit cache try
	 * 	merges:	   All merge tries attempted
	 */
	अगर (blk_queue_nomerges(q) || !bio_mergeable(bio))
		वापस ELEVATOR_NO_MERGE;

	/*
	 * First try one-hit cache.
	 */
	अगर (q->last_merge && elv_bio_merge_ok(q->last_merge, bio)) अणु
		क्रमागत elv_merge ret = blk_try_merge(q->last_merge, bio);

		अगर (ret != ELEVATOR_NO_MERGE) अणु
			*req = q->last_merge;
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (blk_queue_noxmerges(q))
		वापस ELEVATOR_NO_MERGE;

	/*
	 * See अगर our hash lookup can find a potential backmerge.
	 */
	__rq = elv_rqhash_find(q, bio->bi_iter.bi_sector);
	अगर (__rq && elv_bio_merge_ok(__rq, bio)) अणु
		*req = __rq;
		वापस ELEVATOR_BACK_MERGE;
	पूर्ण

	अगर (e->type->ops.request_merge)
		वापस e->type->ops.request_merge(q, req, bio);

	वापस ELEVATOR_NO_MERGE;
पूर्ण

/*
 * Attempt to करो an insertion back merge. Only check क्रम the हाल where
 * we can append 'rq' to an existing request, so we can throw 'rq' away
 * afterwards.
 *
 * Returns true अगर we merged, false otherwise
 */
bool elv_attempt_insert_merge(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा request *__rq;
	bool ret;

	अगर (blk_queue_nomerges(q))
		वापस false;

	/*
	 * First try one-hit cache.
	 */
	अगर (q->last_merge && blk_attempt_req_merge(q, q->last_merge, rq))
		वापस true;

	अगर (blk_queue_noxmerges(q))
		वापस false;

	ret = false;
	/*
	 * See अगर our hash lookup can find a potential backmerge.
	 */
	जबतक (1) अणु
		__rq = elv_rqhash_find(q, blk_rq_pos(rq));
		अगर (!__rq || !blk_attempt_req_merge(q, __rq, rq))
			अवरोध;

		/* The merged request could be merged with others, try again */
		ret = true;
		rq = __rq;
	पूर्ण

	वापस ret;
पूर्ण

व्योम elv_merged_request(काष्ठा request_queue *q, काष्ठा request *rq,
		क्रमागत elv_merge type)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e->type->ops.request_merged)
		e->type->ops.request_merged(q, rq, type);

	अगर (type == ELEVATOR_BACK_MERGE)
		elv_rqhash_reposition(q, rq);

	q->last_merge = rq;
पूर्ण

व्योम elv_merge_requests(काष्ठा request_queue *q, काष्ठा request *rq,
			     काष्ठा request *next)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e->type->ops.requests_merged)
		e->type->ops.requests_merged(q, rq, next);

	elv_rqhash_reposition(q, rq);
	q->last_merge = rq;
पूर्ण

काष्ठा request *elv_latter_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e->type->ops.next_request)
		वापस e->type->ops.next_request(q, rq);

	वापस शून्य;
पूर्ण

काष्ठा request *elv_क्रमmer_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e->type->ops.क्रमmer_request)
		वापस e->type->ops.क्रमmer_request(q, rq);

	वापस शून्य;
पूर्ण

#घोषणा to_elv(atr) container_of((atr), काष्ठा elv_fs_entry, attr)

अटल sमाप_प्रकार
elv_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा elv_fs_entry *entry = to_elv(attr);
	काष्ठा elevator_queue *e;
	sमाप_प्रकार error;

	अगर (!entry->show)
		वापस -EIO;

	e = container_of(kobj, काष्ठा elevator_queue, kobj);
	mutex_lock(&e->sysfs_lock);
	error = e->type ? entry->show(e, page) : -ENOENT;
	mutex_unlock(&e->sysfs_lock);
	वापस error;
पूर्ण

अटल sमाप_प्रकार
elv_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
	       स्थिर अक्षर *page, माप_प्रकार length)
अणु
	काष्ठा elv_fs_entry *entry = to_elv(attr);
	काष्ठा elevator_queue *e;
	sमाप_प्रकार error;

	अगर (!entry->store)
		वापस -EIO;

	e = container_of(kobj, काष्ठा elevator_queue, kobj);
	mutex_lock(&e->sysfs_lock);
	error = e->type ? entry->store(e, page, length) : -ENOENT;
	mutex_unlock(&e->sysfs_lock);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops elv_sysfs_ops = अणु
	.show	= elv_attr_show,
	.store	= elv_attr_store,
पूर्ण;

अटल काष्ठा kobj_type elv_ktype = अणु
	.sysfs_ops	= &elv_sysfs_ops,
	.release	= elevator_release,
पूर्ण;

पूर्णांक elv_रेजिस्टर_queue(काष्ठा request_queue *q, bool uevent)
अणु
	काष्ठा elevator_queue *e = q->elevator;
	पूर्णांक error;

	lockdep_निश्चित_held(&q->sysfs_lock);

	error = kobject_add(&e->kobj, &q->kobj, "%s", "iosched");
	अगर (!error) अणु
		काष्ठा elv_fs_entry *attr = e->type->elevator_attrs;
		अगर (attr) अणु
			जबतक (attr->attr.name) अणु
				अगर (sysfs_create_file(&e->kobj, &attr->attr))
					अवरोध;
				attr++;
			पूर्ण
		पूर्ण
		अगर (uevent)
			kobject_uevent(&e->kobj, KOBJ_ADD);

		e->रेजिस्टरed = 1;
	पूर्ण
	वापस error;
पूर्ण

व्योम elv_unरेजिस्टर_queue(काष्ठा request_queue *q)
अणु
	lockdep_निश्चित_held(&q->sysfs_lock);

	अगर (q) अणु
		काष्ठा elevator_queue *e = q->elevator;

		kobject_uevent(&e->kobj, KOBJ_REMOVE);
		kobject_del(&e->kobj);

		e->रेजिस्टरed = 0;
		/* Re-enable throttling in हाल elevator disabled it */
		wbt_enable_शेष(q);
	पूर्ण
पूर्ण

पूर्णांक elv_रेजिस्टर(काष्ठा elevator_type *e)
अणु
	/* create icq_cache अगर requested */
	अगर (e->icq_size) अणु
		अगर (WARN_ON(e->icq_size < माप(काष्ठा io_cq)) ||
		    WARN_ON(e->icq_align < __alignof__(काष्ठा io_cq)))
			वापस -EINVAL;

		snम_लिखो(e->icq_cache_name, माप(e->icq_cache_name),
			 "%s_io_cq", e->elevator_name);
		e->icq_cache = kmem_cache_create(e->icq_cache_name, e->icq_size,
						 e->icq_align, 0, शून्य);
		अगर (!e->icq_cache)
			वापस -ENOMEM;
	पूर्ण

	/* रेजिस्टर, करोn't allow duplicate names */
	spin_lock(&elv_list_lock);
	अगर (elevator_find(e->elevator_name, 0)) अणु
		spin_unlock(&elv_list_lock);
		kmem_cache_destroy(e->icq_cache);
		वापस -EBUSY;
	पूर्ण
	list_add_tail(&e->list, &elv_list);
	spin_unlock(&elv_list_lock);

	prपूर्णांकk(KERN_INFO "io scheduler %s registered\n", e->elevator_name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(elv_रेजिस्टर);

व्योम elv_unरेजिस्टर(काष्ठा elevator_type *e)
अणु
	/* unरेजिस्टर */
	spin_lock(&elv_list_lock);
	list_del_init(&e->list);
	spin_unlock(&elv_list_lock);

	/*
	 * Destroy icq_cache अगर it exists.  icq's are RCU managed.  Make
	 * sure all RCU operations are complete beक्रमe proceeding.
	 */
	अगर (e->icq_cache) अणु
		rcu_barrier();
		kmem_cache_destroy(e->icq_cache);
		e->icq_cache = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(elv_unरेजिस्टर);

पूर्णांक elevator_चयन_mq(काष्ठा request_queue *q,
			      काष्ठा elevator_type *new_e)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&q->sysfs_lock);

	अगर (q->elevator) अणु
		अगर (q->elevator->रेजिस्टरed)
			elv_unरेजिस्टर_queue(q);

		ioc_clear_queue(q);
		elevator_निकास(q, q->elevator);
	पूर्ण

	ret = blk_mq_init_sched(q, new_e);
	अगर (ret)
		जाओ out;

	अगर (new_e) अणु
		ret = elv_रेजिस्टर_queue(q, true);
		अगर (ret) अणु
			elevator_निकास(q, q->elevator);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (new_e)
		blk_add_trace_msg(q, "elv switch: %s", new_e->elevator_name);
	अन्यथा
		blk_add_trace_msg(q, "elv switch: none");

out:
	वापस ret;
पूर्ण

अटल अंतरभूत bool elv_support_iosched(काष्ठा request_queue *q)
अणु
	अगर (!queue_is_mq(q) ||
	    (q->tag_set && (q->tag_set->flags & BLK_MQ_F_NO_SCHED)))
		वापस false;
	वापस true;
पूर्ण

/*
 * For single queue devices, शेष to using mq-deadline. If we have multiple
 * queues or mq-deadline is not available, शेष to "none".
 */
अटल काष्ठा elevator_type *elevator_get_शेष(काष्ठा request_queue *q)
अणु
	अगर (q->nr_hw_queues != 1 &&
			!blk_mq_is_sbiपंचांगap_shared(q->tag_set->flags))
		वापस शून्य;

	वापस elevator_get(q, "mq-deadline", false);
पूर्ण

/*
 * Get the first elevator providing the features required by the request queue.
 * Default to "none" अगर no matching elevator is found.
 */
अटल काष्ठा elevator_type *elevator_get_by_features(काष्ठा request_queue *q)
अणु
	काष्ठा elevator_type *e, *found = शून्य;

	spin_lock(&elv_list_lock);

	list_क्रम_each_entry(e, &elv_list, list) अणु
		अगर (elv_support_features(e->elevator_features,
					 q->required_elevator_features)) अणु
			found = e;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found && !try_module_get(found->elevator_owner))
		found = शून्य;

	spin_unlock(&elv_list_lock);
	वापस found;
पूर्ण

/*
 * For a device queue that has no required features, use the शेष elevator
 * settings. Otherwise, use the first elevator available matching the required
 * features. If no suitable elevator is find or अगर the chosen elevator
 * initialization fails, fall back to the "none" elevator (no elevator).
 */
व्योम elevator_init_mq(काष्ठा request_queue *q)
अणु
	काष्ठा elevator_type *e;
	पूर्णांक err;

	अगर (!elv_support_iosched(q))
		वापस;

	WARN_ON_ONCE(blk_queue_रेजिस्टरed(q));

	अगर (unlikely(q->elevator))
		वापस;

	अगर (!q->required_elevator_features)
		e = elevator_get_शेष(q);
	अन्यथा
		e = elevator_get_by_features(q);
	अगर (!e)
		वापस;

	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	err = blk_mq_init_sched(q, e);

	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);

	अगर (err) अणु
		pr_warn("\"%s\" elevator initialization failed, "
			"falling back to \"none\"\n", e->elevator_name);
		elevator_put(e);
	पूर्ण
पूर्ण


/*
 * चयन to new_e io scheduler. be careful not to पूर्णांकroduce deadlocks -
 * we करोn't मुक्त the old io scheduler, beक्रमe we have allocated what we
 * need क्रम the new one. this way we have a chance of going back to the old
 * one, अगर the new one fails init क्रम some reason.
 */
अटल पूर्णांक elevator_चयन(काष्ठा request_queue *q, काष्ठा elevator_type *new_e)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held(&q->sysfs_lock);

	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	err = elevator_चयन_mq(q, new_e);

	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);

	वापस err;
पूर्ण

/*
 * Switch this queue to the given IO scheduler.
 */
अटल पूर्णांक __elevator_change(काष्ठा request_queue *q, स्थिर अक्षर *name)
अणु
	अक्षर elevator_name[ELV_NAME_MAX];
	काष्ठा elevator_type *e;

	/* Make sure queue is not in the middle of being हटाओd */
	अगर (!blk_queue_रेजिस्टरed(q))
		वापस -ENOENT;

	/*
	 * Special हाल क्रम mq, turn off scheduling
	 */
	अगर (!म_भेदन(name, "none", 4)) अणु
		अगर (!q->elevator)
			वापस 0;
		वापस elevator_चयन(q, शून्य);
	पूर्ण

	strlcpy(elevator_name, name, माप(elevator_name));
	e = elevator_get(q, म_मालाip(elevator_name), true);
	अगर (!e)
		वापस -EINVAL;

	अगर (q->elevator &&
	    elevator_match(q->elevator->type, elevator_name, 0)) अणु
		elevator_put(e);
		वापस 0;
	पूर्ण

	वापस elevator_चयन(q, e);
पूर्ण

sमाप_प्रकार elv_iosched_store(काष्ठा request_queue *q, स्थिर अक्षर *name,
			  माप_प्रकार count)
अणु
	पूर्णांक ret;

	अगर (!elv_support_iosched(q))
		वापस count;

	ret = __elevator_change(q, name);
	अगर (!ret)
		वापस count;

	वापस ret;
पूर्ण

sमाप_प्रकार elv_iosched_show(काष्ठा request_queue *q, अक्षर *name)
अणु
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा elevator_type *elv = शून्य;
	काष्ठा elevator_type *__e;
	पूर्णांक len = 0;

	अगर (!queue_is_mq(q))
		वापस प्र_लिखो(name, "none\n");

	अगर (!q->elevator)
		len += प्र_लिखो(name+len, "[none] ");
	अन्यथा
		elv = e->type;

	spin_lock(&elv_list_lock);
	list_क्रम_each_entry(__e, &elv_list, list) अणु
		अगर (elv && elevator_match(elv, __e->elevator_name, 0)) अणु
			len += प्र_लिखो(name+len, "[%s] ", elv->elevator_name);
			जारी;
		पूर्ण
		अगर (elv_support_iosched(q) &&
		    elevator_match(__e, __e->elevator_name,
				   q->required_elevator_features))
			len += प्र_लिखो(name+len, "%s ", __e->elevator_name);
	पूर्ण
	spin_unlock(&elv_list_lock);

	अगर (q->elevator)
		len += प्र_लिखो(name+len, "none");

	len += प्र_लिखो(len+name, "\n");
	वापस len;
पूर्ण

काष्ठा request *elv_rb_क्रमmer_request(काष्ठा request_queue *q,
				      काष्ठा request *rq)
अणु
	काष्ठा rb_node *rbprev = rb_prev(&rq->rb_node);

	अगर (rbprev)
		वापस rb_entry_rq(rbprev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(elv_rb_क्रमmer_request);

काष्ठा request *elv_rb_latter_request(काष्ठा request_queue *q,
				      काष्ठा request *rq)
अणु
	काष्ठा rb_node *rbnext = rb_next(&rq->rb_node);

	अगर (rbnext)
		वापस rb_entry_rq(rbnext);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(elv_rb_latter_request);

अटल पूर्णांक __init elevator_setup(अक्षर *str)
अणु
	pr_warn("Kernel parameter elevator= does not have any effect anymore.\n"
		"Please use sysfs to set IO scheduler for individual devices.\n");
	वापस 1;
पूर्ण

__setup("elevator=", elevator_setup);
