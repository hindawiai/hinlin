<शैली गुरु>
/*
 * Copyright (C) 2017 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-cache-background-tracker.h"

/*----------------------------------------------------------------*/

#घोषणा DM_MSG_PREFIX "dm-background-tracker"

काष्ठा bt_work अणु
	काष्ठा list_head list;
	काष्ठा rb_node node;
	काष्ठा policy_work work;
पूर्ण;

काष्ठा background_tracker अणु
	अचिन्हित max_work;
	atomic_t pending_promotes;
	atomic_t pending_ग_लिखोbacks;
	atomic_t pending_demotes;

	काष्ठा list_head issued;
	काष्ठा list_head queued;
	काष्ठा rb_root pending;

	काष्ठा kmem_cache *work_cache;
पूर्ण;

काष्ठा background_tracker *btracker_create(अचिन्हित max_work)
अणु
	काष्ठा background_tracker *b = kदो_स्मृति(माप(*b), GFP_KERNEL);

	अगर (!b) अणु
		DMERR("couldn't create background_tracker");
		वापस शून्य;
	पूर्ण

	b->max_work = max_work;
	atomic_set(&b->pending_promotes, 0);
	atomic_set(&b->pending_ग_लिखोbacks, 0);
	atomic_set(&b->pending_demotes, 0);

	INIT_LIST_HEAD(&b->issued);
	INIT_LIST_HEAD(&b->queued);

	b->pending = RB_ROOT;
	b->work_cache = KMEM_CACHE(bt_work, 0);
	अगर (!b->work_cache) अणु
		DMERR("couldn't create mempool for background work items");
		kमुक्त(b);
		b = शून्य;
	पूर्ण

	वापस b;
पूर्ण
EXPORT_SYMBOL_GPL(btracker_create);

व्योम btracker_destroy(काष्ठा background_tracker *b)
अणु
	kmem_cache_destroy(b->work_cache);
	kमुक्त(b);
पूर्ण
EXPORT_SYMBOL_GPL(btracker_destroy);

अटल पूर्णांक cmp_oblock(dm_oblock_t lhs, dm_oblock_t rhs)
अणु
	अगर (from_oblock(lhs) < from_oblock(rhs))
		वापस -1;

	अगर (from_oblock(rhs) < from_oblock(lhs))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool __insert_pending(काष्ठा background_tracker *b,
			     काष्ठा bt_work *nw)
अणु
	पूर्णांक cmp;
	काष्ठा bt_work *w;
	काष्ठा rb_node **new = &b->pending.rb_node, *parent = शून्य;

	जबतक (*new) अणु
		w = container_of(*new, काष्ठा bt_work, node);

		parent = *new;
		cmp = cmp_oblock(w->work.oblock, nw->work.oblock);
		अगर (cmp < 0)
			new = &((*new)->rb_left);

		अन्यथा अगर (cmp > 0)
			new = &((*new)->rb_right);

		अन्यथा
			/* alपढ़ोy present */
			वापस false;
	पूर्ण

	rb_link_node(&nw->node, parent, new);
	rb_insert_color(&nw->node, &b->pending);

	वापस true;
पूर्ण

अटल काष्ठा bt_work *__find_pending(काष्ठा background_tracker *b,
				      dm_oblock_t oblock)
अणु
	पूर्णांक cmp;
	काष्ठा bt_work *w;
	काष्ठा rb_node **new = &b->pending.rb_node;

	जबतक (*new) अणु
		w = container_of(*new, काष्ठा bt_work, node);

		cmp = cmp_oblock(w->work.oblock, oblock);
		अगर (cmp < 0)
			new = &((*new)->rb_left);

		अन्यथा अगर (cmp > 0)
			new = &((*new)->rb_right);

		अन्यथा
			अवरोध;
	पूर्ण

	वापस *new ? w : शून्य;
पूर्ण


अटल व्योम update_stats(काष्ठा background_tracker *b, काष्ठा policy_work *w, पूर्णांक delta)
अणु
	चयन (w->op) अणु
	हाल POLICY_PROMOTE:
		atomic_add(delta, &b->pending_promotes);
		अवरोध;

	हाल POLICY_DEMOTE:
		atomic_add(delta, &b->pending_demotes);
		अवरोध;

	हाल POLICY_WRITEBACK:
		atomic_add(delta, &b->pending_ग_लिखोbacks);
		अवरोध;
	पूर्ण
पूर्ण

अचिन्हित btracker_nr_ग_लिखोbacks_queued(काष्ठा background_tracker *b)
अणु
	वापस atomic_पढ़ो(&b->pending_ग_लिखोbacks);
पूर्ण
EXPORT_SYMBOL_GPL(btracker_nr_ग_लिखोbacks_queued);

अचिन्हित btracker_nr_demotions_queued(काष्ठा background_tracker *b)
अणु
	वापस atomic_पढ़ो(&b->pending_demotes);
पूर्ण
EXPORT_SYMBOL_GPL(btracker_nr_demotions_queued);

अटल bool max_work_reached(काष्ठा background_tracker *b)
अणु
	वापस atomic_पढ़ो(&b->pending_promotes) +
		atomic_पढ़ो(&b->pending_ग_लिखोbacks) +
		atomic_पढ़ो(&b->pending_demotes) >= b->max_work;
पूर्ण

अटल काष्ठा bt_work *alloc_work(काष्ठा background_tracker *b)
अणु
	अगर (max_work_reached(b))
		वापस शून्य;

	वापस kmem_cache_alloc(b->work_cache, GFP_NOWAIT);
पूर्ण

पूर्णांक btracker_queue(काष्ठा background_tracker *b,
		   काष्ठा policy_work *work,
		   काष्ठा policy_work **pwork)
अणु
	काष्ठा bt_work *w;

	अगर (pwork)
		*pwork = शून्य;

	w = alloc_work(b);
	अगर (!w)
		वापस -ENOMEM;

	स_नकल(&w->work, work, माप(*work));

	अगर (!__insert_pending(b, w)) अणु
		/*
		 * There was a race, we'll just ignore this second
		 * bit of work क्रम the same oblock.
		 */
		kmem_cache_मुक्त(b->work_cache, w);
		वापस -EINVAL;
	पूर्ण

	अगर (pwork) अणु
		*pwork = &w->work;
		list_add(&w->list, &b->issued);
	पूर्ण अन्यथा
		list_add(&w->list, &b->queued);
	update_stats(b, &w->work, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btracker_queue);

/*
 * Returns -ENODATA अगर there's no work.
 */
पूर्णांक btracker_issue(काष्ठा background_tracker *b, काष्ठा policy_work **work)
अणु
	काष्ठा bt_work *w;

	अगर (list_empty(&b->queued))
		वापस -ENODATA;

	w = list_first_entry(&b->queued, काष्ठा bt_work, list);
	list_move(&w->list, &b->issued);
	*work = &w->work;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btracker_issue);

व्योम btracker_complete(काष्ठा background_tracker *b,
		       काष्ठा policy_work *op)
अणु
	काष्ठा bt_work *w = container_of(op, काष्ठा bt_work, work);

	update_stats(b, &w->work, -1);
	rb_erase(&w->node, &b->pending);
	list_del(&w->list);
	kmem_cache_मुक्त(b->work_cache, w);
पूर्ण
EXPORT_SYMBOL_GPL(btracker_complete);

bool btracker_promotion_alपढ़ोy_present(काष्ठा background_tracker *b,
					dm_oblock_t oblock)
अणु
	वापस __find_pending(b, oblock) != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(btracker_promotion_alपढ़ोy_present);

/*----------------------------------------------------------------*/
