<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Red Hat, Inc. and Parallels Inc. All rights reserved.
 * Authors: David Chinner and Glauber Costa
 *
 * Generic LRU infraकाष्ठाure
 */
#अगर_अघोषित _LRU_LIST_H
#घोषणा _LRU_LIST_H

#समावेश <linux/list.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/shrinker.h>

काष्ठा mem_cgroup;

/* list_lru_walk_cb has to always वापस one of those */
क्रमागत lru_status अणु
	LRU_REMOVED,		/* item हटाओd from list */
	LRU_REMOVED_RETRY,	/* item हटाओd, but lock has been
				   dropped and reacquired */
	LRU_ROTATE,		/* item referenced, give another pass */
	LRU_SKIP,		/* item cannot be locked, skip */
	LRU_RETRY,		/* item not मुक्तable. May drop the lock
				   पूर्णांकernally, but has to वापस locked. */
पूर्ण;

काष्ठा list_lru_one अणु
	काष्ठा list_head	list;
	/* may become negative during memcg reparenting */
	दीर्घ			nr_items;
पूर्ण;

काष्ठा list_lru_memcg अणु
	काष्ठा rcu_head		rcu;
	/* array of per cgroup lists, indexed by memcg_cache_id */
	काष्ठा list_lru_one	*lru[];
पूर्ण;

काष्ठा list_lru_node अणु
	/* protects all lists on the node, including per cgroup */
	spinlock_t		lock;
	/* global list, used क्रम the root cgroup in cgroup aware lrus */
	काष्ठा list_lru_one	lru;
#अगर_घोषित CONFIG_MEMCG_KMEM
	/* क्रम cgroup aware lrus poपूर्णांकs to per cgroup lists, otherwise शून्य */
	काष्ठा list_lru_memcg	__rcu *memcg_lrus;
#पूर्ण_अगर
	दीर्घ nr_items;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा list_lru अणु
	काष्ठा list_lru_node	*node;
#अगर_घोषित CONFIG_MEMCG_KMEM
	काष्ठा list_head	list;
	पूर्णांक			shrinker_id;
	bool			memcg_aware;
#पूर्ण_अगर
पूर्ण;

व्योम list_lru_destroy(काष्ठा list_lru *lru);
पूर्णांक __list_lru_init(काष्ठा list_lru *lru, bool memcg_aware,
		    काष्ठा lock_class_key *key, काष्ठा shrinker *shrinker);

#घोषणा list_lru_init(lru)				\
	__list_lru_init((lru), false, शून्य, शून्य)
#घोषणा list_lru_init_key(lru, key)			\
	__list_lru_init((lru), false, (key), शून्य)
#घोषणा list_lru_init_memcg(lru, shrinker)		\
	__list_lru_init((lru), true, शून्य, shrinker)

पूर्णांक memcg_update_all_list_lrus(पूर्णांक num_memcgs);
व्योम memcg_drain_all_list_lrus(पूर्णांक src_idx, काष्ठा mem_cgroup *dst_memcg);

/**
 * list_lru_add: add an element to the lru list's tail
 * @list_lru: the lru poपूर्णांकer
 * @item: the item to be added.
 *
 * If the element is alपढ़ोy part of a list, this function वापसs करोing
 * nothing. Thereक्रमe the caller करोes not need to keep state about whether or
 * not the element alपढ़ोy beदीर्घs in the list and is allowed to lazy update
 * it. Note however that this is valid क्रम *a* list, not *this* list. If
 * the caller organize itself in a way that elements can be in more than
 * one type of list, it is up to the caller to fully हटाओ the item from
 * the previous list (with list_lru_del() क्रम instance) beक्रमe moving it
 * to @list_lru
 *
 * Return value: true अगर the list was updated, false otherwise
 */
bool list_lru_add(काष्ठा list_lru *lru, काष्ठा list_head *item);

/**
 * list_lru_del: delete an element to the lru list
 * @list_lru: the lru poपूर्णांकer
 * @item: the item to be deleted.
 *
 * This function works analogously as list_lru_add in terms of list
 * manipulation. The comments about an element alपढ़ोy pertaining to
 * a list are also valid क्रम list_lru_del.
 *
 * Return value: true अगर the list was updated, false otherwise
 */
bool list_lru_del(काष्ठा list_lru *lru, काष्ठा list_head *item);

/**
 * list_lru_count_one: वापस the number of objects currently held by @lru
 * @lru: the lru poपूर्णांकer.
 * @nid: the node id to count from.
 * @memcg: the cgroup to count from.
 *
 * Always वापस a non-negative number, 0 क्रम empty lists. There is no
 * guarantee that the list is not updated जबतक the count is being computed.
 * Callers that want such a guarantee need to provide an outer lock.
 */
अचिन्हित दीर्घ list_lru_count_one(काष्ठा list_lru *lru,
				 पूर्णांक nid, काष्ठा mem_cgroup *memcg);
अचिन्हित दीर्घ list_lru_count_node(काष्ठा list_lru *lru, पूर्णांक nid);

अटल अंतरभूत अचिन्हित दीर्घ list_lru_shrink_count(काष्ठा list_lru *lru,
						  काष्ठा shrink_control *sc)
अणु
	वापस list_lru_count_one(lru, sc->nid, sc->memcg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ list_lru_count(काष्ठा list_lru *lru)
अणु
	दीर्घ count = 0;
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_NORMAL_MEMORY)
		count += list_lru_count_node(lru, nid);

	वापस count;
पूर्ण

व्योम list_lru_isolate(काष्ठा list_lru_one *list, काष्ठा list_head *item);
व्योम list_lru_isolate_move(काष्ठा list_lru_one *list, काष्ठा list_head *item,
			   काष्ठा list_head *head);

प्रकार क्रमागत lru_status (*list_lru_walk_cb)(काष्ठा list_head *item,
		काष्ठा list_lru_one *list, spinlock_t *lock, व्योम *cb_arg);

/**
 * list_lru_walk_one: walk a list_lru, isolating and disposing मुक्तable items.
 * @lru: the lru poपूर्णांकer.
 * @nid: the node id to scan from.
 * @memcg: the cgroup to scan from.
 * @isolate: callback function that is resposible क्रम deciding what to करो with
 *  the item currently being scanned
 * @cb_arg: opaque type that will be passed to @isolate
 * @nr_to_walk: how many items to scan.
 *
 * This function will scan all elements in a particular list_lru, calling the
 * @isolate callback क्रम each of those items, aदीर्घ with the current list
 * spinlock and a caller-provided opaque. The @isolate callback can choose to
 * drop the lock पूर्णांकernally, but *must* वापस with the lock held. The callback
 * will वापस an क्रमागत lru_status telling the list_lru infraकाष्ठाure what to
 * करो with the object being scanned.
 *
 * Please note that nr_to_walk करोes not mean how many objects will be मुक्तd,
 * just how many objects will be scanned.
 *
 * Return value: the number of objects effectively हटाओd from the LRU.
 */
अचिन्हित दीर्घ list_lru_walk_one(काष्ठा list_lru *lru,
				पूर्णांक nid, काष्ठा mem_cgroup *memcg,
				list_lru_walk_cb isolate, व्योम *cb_arg,
				अचिन्हित दीर्घ *nr_to_walk);
/**
 * list_lru_walk_one_irq: walk a list_lru, isolating and disposing मुक्तable items.
 * @lru: the lru poपूर्णांकer.
 * @nid: the node id to scan from.
 * @memcg: the cgroup to scan from.
 * @isolate: callback function that is resposible क्रम deciding what to करो with
 *  the item currently being scanned
 * @cb_arg: opaque type that will be passed to @isolate
 * @nr_to_walk: how many items to scan.
 *
 * Same as @list_lru_walk_one except that the spinlock is acquired with
 * spin_lock_irq().
 */
अचिन्हित दीर्घ list_lru_walk_one_irq(काष्ठा list_lru *lru,
				    पूर्णांक nid, काष्ठा mem_cgroup *memcg,
				    list_lru_walk_cb isolate, व्योम *cb_arg,
				    अचिन्हित दीर्घ *nr_to_walk);
अचिन्हित दीर्घ list_lru_walk_node(काष्ठा list_lru *lru, पूर्णांक nid,
				 list_lru_walk_cb isolate, व्योम *cb_arg,
				 अचिन्हित दीर्घ *nr_to_walk);

अटल अंतरभूत अचिन्हित दीर्घ
list_lru_shrink_walk(काष्ठा list_lru *lru, काष्ठा shrink_control *sc,
		     list_lru_walk_cb isolate, व्योम *cb_arg)
अणु
	वापस list_lru_walk_one(lru, sc->nid, sc->memcg, isolate, cb_arg,
				 &sc->nr_to_scan);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
list_lru_shrink_walk_irq(काष्ठा list_lru *lru, काष्ठा shrink_control *sc,
			 list_lru_walk_cb isolate, व्योम *cb_arg)
अणु
	वापस list_lru_walk_one_irq(lru, sc->nid, sc->memcg, isolate, cb_arg,
				     &sc->nr_to_scan);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
list_lru_walk(काष्ठा list_lru *lru, list_lru_walk_cb isolate,
	      व्योम *cb_arg, अचिन्हित दीर्घ nr_to_walk)
अणु
	दीर्घ isolated = 0;
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_NORMAL_MEMORY) अणु
		isolated += list_lru_walk_node(lru, nid, isolate,
					       cb_arg, &nr_to_walk);
		अगर (nr_to_walk <= 0)
			अवरोध;
	पूर्ण
	वापस isolated;
पूर्ण
#पूर्ण_अगर /* _LRU_LIST_H */
