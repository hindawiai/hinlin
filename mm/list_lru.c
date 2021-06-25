<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Red Hat, Inc. and Parallels Inc. All rights reserved.
 * Authors: David Chinner and Glauber Costa
 *
 * Generic LRU infraकाष्ठाure
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/memcontrol.h>
#समावेश "slab.h"

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल LIST_HEAD(list_lrus);
अटल DEFINE_MUTEX(list_lrus_mutex);

अटल व्योम list_lru_रेजिस्टर(काष्ठा list_lru *lru)
अणु
	mutex_lock(&list_lrus_mutex);
	list_add(&lru->list, &list_lrus);
	mutex_unlock(&list_lrus_mutex);
पूर्ण

अटल व्योम list_lru_unरेजिस्टर(काष्ठा list_lru *lru)
अणु
	mutex_lock(&list_lrus_mutex);
	list_del(&lru->list);
	mutex_unlock(&list_lrus_mutex);
पूर्ण

अटल पूर्णांक lru_shrinker_id(काष्ठा list_lru *lru)
अणु
	वापस lru->shrinker_id;
पूर्ण

अटल अंतरभूत bool list_lru_memcg_aware(काष्ठा list_lru *lru)
अणु
	वापस lru->memcg_aware;
पूर्ण

अटल अंतरभूत काष्ठा list_lru_one *
list_lru_from_memcg_idx(काष्ठा list_lru_node *nlru, पूर्णांक idx)
अणु
	काष्ठा list_lru_memcg *memcg_lrus;
	/*
	 * Either lock or RCU protects the array of per cgroup lists
	 * from relocation (see memcg_update_list_lru_node).
	 */
	memcg_lrus = rcu_dereference_check(nlru->memcg_lrus,
					   lockdep_is_held(&nlru->lock));
	अगर (memcg_lrus && idx >= 0)
		वापस memcg_lrus->lru[idx];
	वापस &nlru->lru;
पूर्ण

अटल अंतरभूत काष्ठा list_lru_one *
list_lru_from_kmem(काष्ठा list_lru_node *nlru, व्योम *ptr,
		   काष्ठा mem_cgroup **memcg_ptr)
अणु
	काष्ठा list_lru_one *l = &nlru->lru;
	काष्ठा mem_cgroup *memcg = शून्य;

	अगर (!nlru->memcg_lrus)
		जाओ out;

	memcg = mem_cgroup_from_obj(ptr);
	अगर (!memcg)
		जाओ out;

	l = list_lru_from_memcg_idx(nlru, memcg_cache_id(memcg));
out:
	अगर (memcg_ptr)
		*memcg_ptr = memcg;
	वापस l;
पूर्ण
#अन्यथा
अटल व्योम list_lru_रेजिस्टर(काष्ठा list_lru *lru)
अणु
पूर्ण

अटल व्योम list_lru_unरेजिस्टर(काष्ठा list_lru *lru)
अणु
पूर्ण

अटल पूर्णांक lru_shrinker_id(काष्ठा list_lru *lru)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत bool list_lru_memcg_aware(काष्ठा list_lru *lru)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा list_lru_one *
list_lru_from_memcg_idx(काष्ठा list_lru_node *nlru, पूर्णांक idx)
अणु
	वापस &nlru->lru;
पूर्ण

अटल अंतरभूत काष्ठा list_lru_one *
list_lru_from_kmem(काष्ठा list_lru_node *nlru, व्योम *ptr,
		   काष्ठा mem_cgroup **memcg_ptr)
अणु
	अगर (memcg_ptr)
		*memcg_ptr = शून्य;
	वापस &nlru->lru;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

bool list_lru_add(काष्ठा list_lru *lru, काष्ठा list_head *item)
अणु
	पूर्णांक nid = page_to_nid(virt_to_page(item));
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	काष्ठा mem_cgroup *memcg;
	काष्ठा list_lru_one *l;

	spin_lock(&nlru->lock);
	अगर (list_empty(item)) अणु
		l = list_lru_from_kmem(nlru, item, &memcg);
		list_add_tail(item, &l->list);
		/* Set shrinker bit अगर the first element was added */
		अगर (!l->nr_items++)
			set_shrinker_bit(memcg, nid,
					 lru_shrinker_id(lru));
		nlru->nr_items++;
		spin_unlock(&nlru->lock);
		वापस true;
	पूर्ण
	spin_unlock(&nlru->lock);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_add);

bool list_lru_del(काष्ठा list_lru *lru, काष्ठा list_head *item)
अणु
	पूर्णांक nid = page_to_nid(virt_to_page(item));
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	काष्ठा list_lru_one *l;

	spin_lock(&nlru->lock);
	अगर (!list_empty(item)) अणु
		l = list_lru_from_kmem(nlru, item, शून्य);
		list_del_init(item);
		l->nr_items--;
		nlru->nr_items--;
		spin_unlock(&nlru->lock);
		वापस true;
	पूर्ण
	spin_unlock(&nlru->lock);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_del);

व्योम list_lru_isolate(काष्ठा list_lru_one *list, काष्ठा list_head *item)
अणु
	list_del_init(item);
	list->nr_items--;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_isolate);

व्योम list_lru_isolate_move(काष्ठा list_lru_one *list, काष्ठा list_head *item,
			   काष्ठा list_head *head)
अणु
	list_move(item, head);
	list->nr_items--;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_isolate_move);

अचिन्हित दीर्घ list_lru_count_one(काष्ठा list_lru *lru,
				 पूर्णांक nid, काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	काष्ठा list_lru_one *l;
	अचिन्हित दीर्घ count;

	rcu_पढ़ो_lock();
	l = list_lru_from_memcg_idx(nlru, memcg_cache_id(memcg));
	count = READ_ONCE(l->nr_items);
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_count_one);

अचिन्हित दीर्घ list_lru_count_node(काष्ठा list_lru *lru, पूर्णांक nid)
अणु
	काष्ठा list_lru_node *nlru;

	nlru = &lru->node[nid];
	वापस nlru->nr_items;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_count_node);

अटल अचिन्हित दीर्घ
__list_lru_walk_one(काष्ठा list_lru_node *nlru, पूर्णांक memcg_idx,
		    list_lru_walk_cb isolate, व्योम *cb_arg,
		    अचिन्हित दीर्घ *nr_to_walk)
अणु

	काष्ठा list_lru_one *l;
	काष्ठा list_head *item, *n;
	अचिन्हित दीर्घ isolated = 0;

	l = list_lru_from_memcg_idx(nlru, memcg_idx);
restart:
	list_क्रम_each_safe(item, n, &l->list) अणु
		क्रमागत lru_status ret;

		/*
		 * decrement nr_to_walk first so that we करोn't livelock अगर we
		 * get stuck on large numbers of LRU_RETRY items
		 */
		अगर (!*nr_to_walk)
			अवरोध;
		--*nr_to_walk;

		ret = isolate(item, l, &nlru->lock, cb_arg);
		चयन (ret) अणु
		हाल LRU_REMOVED_RETRY:
			निश्चित_spin_locked(&nlru->lock);
			fallthrough;
		हाल LRU_REMOVED:
			isolated++;
			nlru->nr_items--;
			/*
			 * If the lru lock has been dropped, our list
			 * traversal is now invalid and so we have to
			 * restart from scratch.
			 */
			अगर (ret == LRU_REMOVED_RETRY)
				जाओ restart;
			अवरोध;
		हाल LRU_ROTATE:
			list_move_tail(item, &l->list);
			अवरोध;
		हाल LRU_SKIP:
			अवरोध;
		हाल LRU_RETRY:
			/*
			 * The lru lock has been dropped, our list traversal is
			 * now invalid and so we have to restart from scratch.
			 */
			निश्चित_spin_locked(&nlru->lock);
			जाओ restart;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
	वापस isolated;
पूर्ण

अचिन्हित दीर्घ
list_lru_walk_one(काष्ठा list_lru *lru, पूर्णांक nid, काष्ठा mem_cgroup *memcg,
		  list_lru_walk_cb isolate, व्योम *cb_arg,
		  अचिन्हित दीर्घ *nr_to_walk)
अणु
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	अचिन्हित दीर्घ ret;

	spin_lock(&nlru->lock);
	ret = __list_lru_walk_one(nlru, memcg_cache_id(memcg), isolate, cb_arg,
				  nr_to_walk);
	spin_unlock(&nlru->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_walk_one);

अचिन्हित दीर्घ
list_lru_walk_one_irq(काष्ठा list_lru *lru, पूर्णांक nid, काष्ठा mem_cgroup *memcg,
		      list_lru_walk_cb isolate, व्योम *cb_arg,
		      अचिन्हित दीर्घ *nr_to_walk)
अणु
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	अचिन्हित दीर्घ ret;

	spin_lock_irq(&nlru->lock);
	ret = __list_lru_walk_one(nlru, memcg_cache_id(memcg), isolate, cb_arg,
				  nr_to_walk);
	spin_unlock_irq(&nlru->lock);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ list_lru_walk_node(काष्ठा list_lru *lru, पूर्णांक nid,
				 list_lru_walk_cb isolate, व्योम *cb_arg,
				 अचिन्हित दीर्घ *nr_to_walk)
अणु
	दीर्घ isolated = 0;
	पूर्णांक memcg_idx;

	isolated += list_lru_walk_one(lru, nid, शून्य, isolate, cb_arg,
				      nr_to_walk);
	अगर (*nr_to_walk > 0 && list_lru_memcg_aware(lru)) अणु
		क्रम_each_memcg_cache_index(memcg_idx) अणु
			काष्ठा list_lru_node *nlru = &lru->node[nid];

			spin_lock(&nlru->lock);
			isolated += __list_lru_walk_one(nlru, memcg_idx,
							isolate, cb_arg,
							nr_to_walk);
			spin_unlock(&nlru->lock);

			अगर (*nr_to_walk <= 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस isolated;
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_walk_node);

अटल व्योम init_one_lru(काष्ठा list_lru_one *l)
अणु
	INIT_LIST_HEAD(&l->list);
	l->nr_items = 0;
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल व्योम __memcg_destroy_list_lru_node(काष्ठा list_lru_memcg *memcg_lrus,
					  पूर्णांक begin, पूर्णांक end)
अणु
	पूर्णांक i;

	क्रम (i = begin; i < end; i++)
		kमुक्त(memcg_lrus->lru[i]);
पूर्ण

अटल पूर्णांक __memcg_init_list_lru_node(काष्ठा list_lru_memcg *memcg_lrus,
				      पूर्णांक begin, पूर्णांक end)
अणु
	पूर्णांक i;

	क्रम (i = begin; i < end; i++) अणु
		काष्ठा list_lru_one *l;

		l = kदो_स्मृति(माप(काष्ठा list_lru_one), GFP_KERNEL);
		अगर (!l)
			जाओ fail;

		init_one_lru(l);
		memcg_lrus->lru[i] = l;
	पूर्ण
	वापस 0;
fail:
	__memcg_destroy_list_lru_node(memcg_lrus, begin, i);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक memcg_init_list_lru_node(काष्ठा list_lru_node *nlru)
अणु
	काष्ठा list_lru_memcg *memcg_lrus;
	पूर्णांक size = memcg_nr_cache_ids;

	memcg_lrus = kvदो_स्मृति(माप(*memcg_lrus) +
			      size * माप(व्योम *), GFP_KERNEL);
	अगर (!memcg_lrus)
		वापस -ENOMEM;

	अगर (__memcg_init_list_lru_node(memcg_lrus, 0, size)) अणु
		kvमुक्त(memcg_lrus);
		वापस -ENOMEM;
	पूर्ण
	RCU_INIT_POINTER(nlru->memcg_lrus, memcg_lrus);

	वापस 0;
पूर्ण

अटल व्योम memcg_destroy_list_lru_node(काष्ठा list_lru_node *nlru)
अणु
	काष्ठा list_lru_memcg *memcg_lrus;
	/*
	 * This is called when shrinker has alपढ़ोy been unरेजिस्टरed,
	 * and nobody can use it. So, there is no need to use kvमुक्त_rcu().
	 */
	memcg_lrus = rcu_dereference_रक्षित(nlru->memcg_lrus, true);
	__memcg_destroy_list_lru_node(memcg_lrus, 0, memcg_nr_cache_ids);
	kvमुक्त(memcg_lrus);
पूर्ण

अटल पूर्णांक memcg_update_list_lru_node(काष्ठा list_lru_node *nlru,
				      पूर्णांक old_size, पूर्णांक new_size)
अणु
	काष्ठा list_lru_memcg *old, *new;

	BUG_ON(old_size > new_size);

	old = rcu_dereference_रक्षित(nlru->memcg_lrus,
					lockdep_is_held(&list_lrus_mutex));
	new = kvदो_स्मृति(माप(*new) + new_size * माप(व्योम *), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	अगर (__memcg_init_list_lru_node(new, old_size, new_size)) अणु
		kvमुक्त(new);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&new->lru, &old->lru, old_size * माप(व्योम *));

	/*
	 * The locking below allows पढ़ोers that hold nlru->lock aव्योम taking
	 * rcu_पढ़ो_lock (see list_lru_from_memcg_idx).
	 *
	 * Since list_lru_अणुadd,delपूर्ण may be called under an IRQ-safe lock,
	 * we have to use IRQ-safe primitives here to aव्योम deadlock.
	 */
	spin_lock_irq(&nlru->lock);
	rcu_assign_poपूर्णांकer(nlru->memcg_lrus, new);
	spin_unlock_irq(&nlru->lock);

	kvमुक्त_rcu(old, rcu);
	वापस 0;
पूर्ण

अटल व्योम memcg_cancel_update_list_lru_node(काष्ठा list_lru_node *nlru,
					      पूर्णांक old_size, पूर्णांक new_size)
अणु
	काष्ठा list_lru_memcg *memcg_lrus;

	memcg_lrus = rcu_dereference_रक्षित(nlru->memcg_lrus,
					       lockdep_is_held(&list_lrus_mutex));
	/* करो not bother shrinking the array back to the old size, because we
	 * cannot handle allocation failures here */
	__memcg_destroy_list_lru_node(memcg_lrus, old_size, new_size);
पूर्ण

अटल पूर्णांक memcg_init_list_lru(काष्ठा list_lru *lru, bool memcg_aware)
अणु
	पूर्णांक i;

	lru->memcg_aware = memcg_aware;

	अगर (!memcg_aware)
		वापस 0;

	क्रम_each_node(i) अणु
		अगर (memcg_init_list_lru_node(&lru->node[i]))
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	क्रम (i = i - 1; i >= 0; i--) अणु
		अगर (!lru->node[i].memcg_lrus)
			जारी;
		memcg_destroy_list_lru_node(&lru->node[i]);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम memcg_destroy_list_lru(काष्ठा list_lru *lru)
अणु
	पूर्णांक i;

	अगर (!list_lru_memcg_aware(lru))
		वापस;

	क्रम_each_node(i)
		memcg_destroy_list_lru_node(&lru->node[i]);
पूर्ण

अटल पूर्णांक memcg_update_list_lru(काष्ठा list_lru *lru,
				 पूर्णांक old_size, पूर्णांक new_size)
अणु
	पूर्णांक i;

	अगर (!list_lru_memcg_aware(lru))
		वापस 0;

	क्रम_each_node(i) अणु
		अगर (memcg_update_list_lru_node(&lru->node[i],
					       old_size, new_size))
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	क्रम (i = i - 1; i >= 0; i--) अणु
		अगर (!lru->node[i].memcg_lrus)
			जारी;

		memcg_cancel_update_list_lru_node(&lru->node[i],
						  old_size, new_size);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम memcg_cancel_update_list_lru(काष्ठा list_lru *lru,
					 पूर्णांक old_size, पूर्णांक new_size)
अणु
	पूर्णांक i;

	अगर (!list_lru_memcg_aware(lru))
		वापस;

	क्रम_each_node(i)
		memcg_cancel_update_list_lru_node(&lru->node[i],
						  old_size, new_size);
पूर्ण

पूर्णांक memcg_update_all_list_lrus(पूर्णांक new_size)
अणु
	पूर्णांक ret = 0;
	काष्ठा list_lru *lru;
	पूर्णांक old_size = memcg_nr_cache_ids;

	mutex_lock(&list_lrus_mutex);
	list_क्रम_each_entry(lru, &list_lrus, list) अणु
		ret = memcg_update_list_lru(lru, old_size, new_size);
		अगर (ret)
			जाओ fail;
	पूर्ण
out:
	mutex_unlock(&list_lrus_mutex);
	वापस ret;
fail:
	list_क्रम_each_entry_जारी_reverse(lru, &list_lrus, list)
		memcg_cancel_update_list_lru(lru, old_size, new_size);
	जाओ out;
पूर्ण

अटल व्योम memcg_drain_list_lru_node(काष्ठा list_lru *lru, पूर्णांक nid,
				      पूर्णांक src_idx, काष्ठा mem_cgroup *dst_memcg)
अणु
	काष्ठा list_lru_node *nlru = &lru->node[nid];
	पूर्णांक dst_idx = dst_memcg->kmemcg_id;
	काष्ठा list_lru_one *src, *dst;

	/*
	 * Since list_lru_अणुadd,delपूर्ण may be called under an IRQ-safe lock,
	 * we have to use IRQ-safe primitives here to aव्योम deadlock.
	 */
	spin_lock_irq(&nlru->lock);

	src = list_lru_from_memcg_idx(nlru, src_idx);
	dst = list_lru_from_memcg_idx(nlru, dst_idx);

	list_splice_init(&src->list, &dst->list);

	अगर (src->nr_items) अणु
		dst->nr_items += src->nr_items;
		set_shrinker_bit(dst_memcg, nid, lru_shrinker_id(lru));
		src->nr_items = 0;
	पूर्ण

	spin_unlock_irq(&nlru->lock);
पूर्ण

अटल व्योम memcg_drain_list_lru(काष्ठा list_lru *lru,
				 पूर्णांक src_idx, काष्ठा mem_cgroup *dst_memcg)
अणु
	पूर्णांक i;

	अगर (!list_lru_memcg_aware(lru))
		वापस;

	क्रम_each_node(i)
		memcg_drain_list_lru_node(lru, i, src_idx, dst_memcg);
पूर्ण

व्योम memcg_drain_all_list_lrus(पूर्णांक src_idx, काष्ठा mem_cgroup *dst_memcg)
अणु
	काष्ठा list_lru *lru;

	mutex_lock(&list_lrus_mutex);
	list_क्रम_each_entry(lru, &list_lrus, list)
		memcg_drain_list_lru(lru, src_idx, dst_memcg);
	mutex_unlock(&list_lrus_mutex);
पूर्ण
#अन्यथा
अटल पूर्णांक memcg_init_list_lru(काष्ठा list_lru *lru, bool memcg_aware)
अणु
	वापस 0;
पूर्ण

अटल व्योम memcg_destroy_list_lru(काष्ठा list_lru *lru)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

पूर्णांक __list_lru_init(काष्ठा list_lru *lru, bool memcg_aware,
		    काष्ठा lock_class_key *key, काष्ठा shrinker *shrinker)
अणु
	पूर्णांक i;
	पूर्णांक err = -ENOMEM;

#अगर_घोषित CONFIG_MEMCG_KMEM
	अगर (shrinker)
		lru->shrinker_id = shrinker->id;
	अन्यथा
		lru->shrinker_id = -1;
#पूर्ण_अगर
	memcg_get_cache_ids();

	lru->node = kसुस्मृति(nr_node_ids, माप(*lru->node), GFP_KERNEL);
	अगर (!lru->node)
		जाओ out;

	क्रम_each_node(i) अणु
		spin_lock_init(&lru->node[i].lock);
		अगर (key)
			lockdep_set_class(&lru->node[i].lock, key);
		init_one_lru(&lru->node[i].lru);
	पूर्ण

	err = memcg_init_list_lru(lru, memcg_aware);
	अगर (err) अणु
		kमुक्त(lru->node);
		/* Do this so a list_lru_destroy() करोesn't crash: */
		lru->node = शून्य;
		जाओ out;
	पूर्ण

	list_lru_रेजिस्टर(lru);
out:
	memcg_put_cache_ids();
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__list_lru_init);

व्योम list_lru_destroy(काष्ठा list_lru *lru)
अणु
	/* Alपढ़ोy destroyed or not yet initialized? */
	अगर (!lru->node)
		वापस;

	memcg_get_cache_ids();

	list_lru_unरेजिस्टर(lru);

	memcg_destroy_list_lru(lru);
	kमुक्त(lru->node);
	lru->node = शून्य;

#अगर_घोषित CONFIG_MEMCG_KMEM
	lru->shrinker_id = -1;
#पूर्ण_अगर
	memcg_put_cache_ids();
पूर्ण
EXPORT_SYMBOL_GPL(list_lru_destroy);
