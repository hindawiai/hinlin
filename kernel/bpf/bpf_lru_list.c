<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu.h>

#समावेश "bpf_lru_list.h"

#घोषणा LOCAL_FREE_TARGET		(128)
#घोषणा LOCAL_NR_SCANS			LOCAL_FREE_TARGET

#घोषणा PERCPU_FREE_TARGET		(4)
#घोषणा PERCPU_NR_SCANS			PERCPU_FREE_TARGET

/* Helpers to get the local list index */
#घोषणा LOCAL_LIST_IDX(t)	((t) - BPF_LOCAL_LIST_T_OFFSET)
#घोषणा LOCAL_FREE_LIST_IDX	LOCAL_LIST_IDX(BPF_LRU_LOCAL_LIST_T_FREE)
#घोषणा LOCAL_PENDING_LIST_IDX	LOCAL_LIST_IDX(BPF_LRU_LOCAL_LIST_T_PENDING)
#घोषणा IS_LOCAL_LIST_TYPE(t)	((t) >= BPF_LOCAL_LIST_T_OFFSET)

अटल पूर्णांक get_next_cpu(पूर्णांक cpu)
अणु
	cpu = cpumask_next(cpu, cpu_possible_mask);
	अगर (cpu >= nr_cpu_ids)
		cpu = cpumask_first(cpu_possible_mask);
	वापस cpu;
पूर्ण

/* Local list helpers */
अटल काष्ठा list_head *local_मुक्त_list(काष्ठा bpf_lru_locallist *loc_l)
अणु
	वापस &loc_l->lists[LOCAL_FREE_LIST_IDX];
पूर्ण

अटल काष्ठा list_head *local_pending_list(काष्ठा bpf_lru_locallist *loc_l)
अणु
	वापस &loc_l->lists[LOCAL_PENDING_LIST_IDX];
पूर्ण

/* bpf_lru_node helpers */
अटल bool bpf_lru_node_is_ref(स्थिर काष्ठा bpf_lru_node *node)
अणु
	वापस node->ref;
पूर्ण

अटल व्योम bpf_lru_list_count_inc(काष्ठा bpf_lru_list *l,
				   क्रमागत bpf_lru_list_type type)
अणु
	अगर (type < NR_BPF_LRU_LIST_COUNT)
		l->counts[type]++;
पूर्ण

अटल व्योम bpf_lru_list_count_dec(काष्ठा bpf_lru_list *l,
				   क्रमागत bpf_lru_list_type type)
अणु
	अगर (type < NR_BPF_LRU_LIST_COUNT)
		l->counts[type]--;
पूर्ण

अटल व्योम __bpf_lru_node_move_to_मुक्त(काष्ठा bpf_lru_list *l,
					काष्ठा bpf_lru_node *node,
					काष्ठा list_head *मुक्त_list,
					क्रमागत bpf_lru_list_type tgt_मुक्त_type)
अणु
	अगर (WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(node->type)))
		वापस;

	/* If the removing node is the next_inactive_rotation candidate,
	 * move the next_inactive_rotation poपूर्णांकer also.
	 */
	अगर (&node->list == l->next_inactive_rotation)
		l->next_inactive_rotation = l->next_inactive_rotation->prev;

	bpf_lru_list_count_dec(l, node->type);

	node->type = tgt_मुक्त_type;
	list_move(&node->list, मुक्त_list);
पूर्ण

/* Move nodes from local list to the LRU list */
अटल व्योम __bpf_lru_node_move_in(काष्ठा bpf_lru_list *l,
				   काष्ठा bpf_lru_node *node,
				   क्रमागत bpf_lru_list_type tgt_type)
अणु
	अगर (WARN_ON_ONCE(!IS_LOCAL_LIST_TYPE(node->type)) ||
	    WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(tgt_type)))
		वापस;

	bpf_lru_list_count_inc(l, tgt_type);
	node->type = tgt_type;
	node->ref = 0;
	list_move(&node->list, &l->lists[tgt_type]);
पूर्ण

/* Move nodes between or within active and inactive list (like
 * active to inactive, inactive to active or tail of active back to
 * the head of active).
 */
अटल व्योम __bpf_lru_node_move(काष्ठा bpf_lru_list *l,
				काष्ठा bpf_lru_node *node,
				क्रमागत bpf_lru_list_type tgt_type)
अणु
	अगर (WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(node->type)) ||
	    WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(tgt_type)))
		वापस;

	अगर (node->type != tgt_type) अणु
		bpf_lru_list_count_dec(l, node->type);
		bpf_lru_list_count_inc(l, tgt_type);
		node->type = tgt_type;
	पूर्ण
	node->ref = 0;

	/* If the moving node is the next_inactive_rotation candidate,
	 * move the next_inactive_rotation poपूर्णांकer also.
	 */
	अगर (&node->list == l->next_inactive_rotation)
		l->next_inactive_rotation = l->next_inactive_rotation->prev;

	list_move(&node->list, &l->lists[tgt_type]);
पूर्ण

अटल bool bpf_lru_list_inactive_low(स्थिर काष्ठा bpf_lru_list *l)
अणु
	वापस l->counts[BPF_LRU_LIST_T_INACTIVE] <
		l->counts[BPF_LRU_LIST_T_ACTIVE];
पूर्ण

/* Rotate the active list:
 * 1. Start from tail
 * 2. If the node has the ref bit set, it will be rotated
 *    back to the head of active list with the ref bit cleared.
 *    Give this node one more chance to survive in the active list.
 * 3. If the ref bit is not set, move it to the head of the
 *    inactive list.
 * 4. It will at most scan nr_scans nodes
 */
अटल व्योम __bpf_lru_list_rotate_active(काष्ठा bpf_lru *lru,
					 काष्ठा bpf_lru_list *l)
अणु
	काष्ठा list_head *active = &l->lists[BPF_LRU_LIST_T_ACTIVE];
	काष्ठा bpf_lru_node *node, *पंचांगp_node, *first_node;
	अचिन्हित पूर्णांक i = 0;

	first_node = list_first_entry(active, काष्ठा bpf_lru_node, list);
	list_क्रम_each_entry_safe_reverse(node, पंचांगp_node, active, list) अणु
		अगर (bpf_lru_node_is_ref(node))
			__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_ACTIVE);
		अन्यथा
			__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_INACTIVE);

		अगर (++i == lru->nr_scans || node == first_node)
			अवरोध;
	पूर्ण
पूर्ण

/* Rotate the inactive list.  It starts from the next_inactive_rotation
 * 1. If the node has ref bit set, it will be moved to the head
 *    of active list with the ref bit cleared.
 * 2. If the node करोes not have ref bit set, it will leave it
 *    at its current location (i.e. करो nothing) so that it can
 *    be considered during the next inactive_shrink.
 * 3. It will at most scan nr_scans nodes
 */
अटल व्योम __bpf_lru_list_rotate_inactive(काष्ठा bpf_lru *lru,
					   काष्ठा bpf_lru_list *l)
अणु
	काष्ठा list_head *inactive = &l->lists[BPF_LRU_LIST_T_INACTIVE];
	काष्ठा list_head *cur, *last, *next = inactive;
	काष्ठा bpf_lru_node *node;
	अचिन्हित पूर्णांक i = 0;

	अगर (list_empty(inactive))
		वापस;

	last = l->next_inactive_rotation->next;
	अगर (last == inactive)
		last = last->next;

	cur = l->next_inactive_rotation;
	जबतक (i < lru->nr_scans) अणु
		अगर (cur == inactive) अणु
			cur = cur->prev;
			जारी;
		पूर्ण

		node = list_entry(cur, काष्ठा bpf_lru_node, list);
		next = cur->prev;
		अगर (bpf_lru_node_is_ref(node))
			__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_ACTIVE);
		अगर (cur == last)
			अवरोध;
		cur = next;
		i++;
	पूर्ण

	l->next_inactive_rotation = next;
पूर्ण

/* Shrink the inactive list.  It starts from the tail of the
 * inactive list and only move the nodes without the ref bit
 * set to the designated मुक्त list.
 */
अटल अचिन्हित पूर्णांक
__bpf_lru_list_shrink_inactive(काष्ठा bpf_lru *lru,
			       काष्ठा bpf_lru_list *l,
			       अचिन्हित पूर्णांक tgt_nshrink,
			       काष्ठा list_head *मुक्त_list,
			       क्रमागत bpf_lru_list_type tgt_मुक्त_type)
अणु
	काष्ठा list_head *inactive = &l->lists[BPF_LRU_LIST_T_INACTIVE];
	काष्ठा bpf_lru_node *node, *पंचांगp_node;
	अचिन्हित पूर्णांक nshrinked = 0;
	अचिन्हित पूर्णांक i = 0;

	list_क्रम_each_entry_safe_reverse(node, पंचांगp_node, inactive, list) अणु
		अगर (bpf_lru_node_is_ref(node)) अणु
			__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_ACTIVE);
		पूर्ण अन्यथा अगर (lru->del_from_htab(lru->del_arg, node)) अणु
			__bpf_lru_node_move_to_मुक्त(l, node, मुक्त_list,
						    tgt_मुक्त_type);
			अगर (++nshrinked == tgt_nshrink)
				अवरोध;
		पूर्ण

		अगर (++i == lru->nr_scans)
			अवरोध;
	पूर्ण

	वापस nshrinked;
पूर्ण

/* 1. Rotate the active list (अगर needed)
 * 2. Always rotate the inactive list
 */
अटल व्योम __bpf_lru_list_rotate(काष्ठा bpf_lru *lru, काष्ठा bpf_lru_list *l)
अणु
	अगर (bpf_lru_list_inactive_low(l))
		__bpf_lru_list_rotate_active(lru, l);

	__bpf_lru_list_rotate_inactive(lru, l);
पूर्ण

/* Calls __bpf_lru_list_shrink_inactive() to shrink some
 * ref-bit-cleared nodes and move them to the designated
 * मुक्त list.
 *
 * If it cannot get a मुक्त node after calling
 * __bpf_lru_list_shrink_inactive().  It will just हटाओ
 * one node from either inactive or active list without
 * honoring the ref-bit.  It prefers inactive list to active
 * list in this situation.
 */
अटल अचिन्हित पूर्णांक __bpf_lru_list_shrink(काष्ठा bpf_lru *lru,
					  काष्ठा bpf_lru_list *l,
					  अचिन्हित पूर्णांक tgt_nshrink,
					  काष्ठा list_head *मुक्त_list,
					  क्रमागत bpf_lru_list_type tgt_मुक्त_type)

अणु
	काष्ठा bpf_lru_node *node, *पंचांगp_node;
	काष्ठा list_head *क्रमce_shrink_list;
	अचिन्हित पूर्णांक nshrinked;

	nshrinked = __bpf_lru_list_shrink_inactive(lru, l, tgt_nshrink,
						   मुक्त_list, tgt_मुक्त_type);
	अगर (nshrinked)
		वापस nshrinked;

	/* Do a क्रमce shrink by ignoring the reference bit */
	अगर (!list_empty(&l->lists[BPF_LRU_LIST_T_INACTIVE]))
		क्रमce_shrink_list = &l->lists[BPF_LRU_LIST_T_INACTIVE];
	अन्यथा
		क्रमce_shrink_list = &l->lists[BPF_LRU_LIST_T_ACTIVE];

	list_क्रम_each_entry_safe_reverse(node, पंचांगp_node, क्रमce_shrink_list,
					 list) अणु
		अगर (lru->del_from_htab(lru->del_arg, node)) अणु
			__bpf_lru_node_move_to_मुक्त(l, node, मुक्त_list,
						    tgt_मुक्त_type);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Flush the nodes from the local pending list to the LRU list */
अटल व्योम __local_list_flush(काष्ठा bpf_lru_list *l,
			       काष्ठा bpf_lru_locallist *loc_l)
अणु
	काष्ठा bpf_lru_node *node, *पंचांगp_node;

	list_क्रम_each_entry_safe_reverse(node, पंचांगp_node,
					 local_pending_list(loc_l), list) अणु
		अगर (bpf_lru_node_is_ref(node))
			__bpf_lru_node_move_in(l, node, BPF_LRU_LIST_T_ACTIVE);
		अन्यथा
			__bpf_lru_node_move_in(l, node,
					       BPF_LRU_LIST_T_INACTIVE);
	पूर्ण
पूर्ण

अटल व्योम bpf_lru_list_push_मुक्त(काष्ठा bpf_lru_list *l,
				   काष्ठा bpf_lru_node *node)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(node->type)))
		वापस;

	raw_spin_lock_irqsave(&l->lock, flags);
	__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_FREE);
	raw_spin_unlock_irqrestore(&l->lock, flags);
पूर्ण

अटल व्योम bpf_lru_list_pop_मुक्त_to_local(काष्ठा bpf_lru *lru,
					   काष्ठा bpf_lru_locallist *loc_l)
अणु
	काष्ठा bpf_lru_list *l = &lru->common_lru.lru_list;
	काष्ठा bpf_lru_node *node, *पंचांगp_node;
	अचिन्हित पूर्णांक nमुक्त = 0;

	raw_spin_lock(&l->lock);

	__local_list_flush(l, loc_l);

	__bpf_lru_list_rotate(lru, l);

	list_क्रम_each_entry_safe(node, पंचांगp_node, &l->lists[BPF_LRU_LIST_T_FREE],
				 list) अणु
		__bpf_lru_node_move_to_मुक्त(l, node, local_मुक्त_list(loc_l),
					    BPF_LRU_LOCAL_LIST_T_FREE);
		अगर (++nमुक्त == LOCAL_FREE_TARGET)
			अवरोध;
	पूर्ण

	अगर (nमुक्त < LOCAL_FREE_TARGET)
		__bpf_lru_list_shrink(lru, l, LOCAL_FREE_TARGET - nमुक्त,
				      local_मुक्त_list(loc_l),
				      BPF_LRU_LOCAL_LIST_T_FREE);

	raw_spin_unlock(&l->lock);
पूर्ण

अटल व्योम __local_list_add_pending(काष्ठा bpf_lru *lru,
				     काष्ठा bpf_lru_locallist *loc_l,
				     पूर्णांक cpu,
				     काष्ठा bpf_lru_node *node,
				     u32 hash)
अणु
	*(u32 *)((व्योम *)node + lru->hash_offset) = hash;
	node->cpu = cpu;
	node->type = BPF_LRU_LOCAL_LIST_T_PENDING;
	node->ref = 0;
	list_add(&node->list, local_pending_list(loc_l));
पूर्ण

अटल काष्ठा bpf_lru_node *
__local_list_pop_मुक्त(काष्ठा bpf_lru_locallist *loc_l)
अणु
	काष्ठा bpf_lru_node *node;

	node = list_first_entry_or_null(local_मुक्त_list(loc_l),
					काष्ठा bpf_lru_node,
					list);
	अगर (node)
		list_del(&node->list);

	वापस node;
पूर्ण

अटल काष्ठा bpf_lru_node *
__local_list_pop_pending(काष्ठा bpf_lru *lru, काष्ठा bpf_lru_locallist *loc_l)
अणु
	काष्ठा bpf_lru_node *node;
	bool क्रमce = false;

ignore_ref:
	/* Get from the tail (i.e. older element) of the pending list. */
	list_क्रम_each_entry_reverse(node, local_pending_list(loc_l),
				    list) अणु
		अगर ((!bpf_lru_node_is_ref(node) || क्रमce) &&
		    lru->del_from_htab(lru->del_arg, node)) अणु
			list_del(&node->list);
			वापस node;
		पूर्ण
	पूर्ण

	अगर (!क्रमce) अणु
		क्रमce = true;
		जाओ ignore_ref;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा bpf_lru_node *bpf_percpu_lru_pop_मुक्त(काष्ठा bpf_lru *lru,
						    u32 hash)
अणु
	काष्ठा list_head *मुक्त_list;
	काष्ठा bpf_lru_node *node = शून्य;
	काष्ठा bpf_lru_list *l;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu = raw_smp_processor_id();

	l = per_cpu_ptr(lru->percpu_lru, cpu);

	raw_spin_lock_irqsave(&l->lock, flags);

	__bpf_lru_list_rotate(lru, l);

	मुक्त_list = &l->lists[BPF_LRU_LIST_T_FREE];
	अगर (list_empty(मुक्त_list))
		__bpf_lru_list_shrink(lru, l, PERCPU_FREE_TARGET, मुक्त_list,
				      BPF_LRU_LIST_T_FREE);

	अगर (!list_empty(मुक्त_list)) अणु
		node = list_first_entry(मुक्त_list, काष्ठा bpf_lru_node, list);
		*(u32 *)((व्योम *)node + lru->hash_offset) = hash;
		node->ref = 0;
		__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_INACTIVE);
	पूर्ण

	raw_spin_unlock_irqrestore(&l->lock, flags);

	वापस node;
पूर्ण

अटल काष्ठा bpf_lru_node *bpf_common_lru_pop_मुक्त(काष्ठा bpf_lru *lru,
						    u32 hash)
अणु
	काष्ठा bpf_lru_locallist *loc_l, *steal_loc_l;
	काष्ठा bpf_common_lru *clru = &lru->common_lru;
	काष्ठा bpf_lru_node *node;
	पूर्णांक steal, first_steal;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu = raw_smp_processor_id();

	loc_l = per_cpu_ptr(clru->local_list, cpu);

	raw_spin_lock_irqsave(&loc_l->lock, flags);

	node = __local_list_pop_मुक्त(loc_l);
	अगर (!node) अणु
		bpf_lru_list_pop_मुक्त_to_local(lru, loc_l);
		node = __local_list_pop_मुक्त(loc_l);
	पूर्ण

	अगर (node)
		__local_list_add_pending(lru, loc_l, cpu, node, hash);

	raw_spin_unlock_irqrestore(&loc_l->lock, flags);

	अगर (node)
		वापस node;

	/* No मुक्त nodes found from the local मुक्त list and
	 * the global LRU list.
	 *
	 * Steal from the local मुक्त/pending list of the
	 * current CPU and remote CPU in RR.  It starts
	 * with the loc_l->next_steal CPU.
	 */

	first_steal = loc_l->next_steal;
	steal = first_steal;
	करो अणु
		steal_loc_l = per_cpu_ptr(clru->local_list, steal);

		raw_spin_lock_irqsave(&steal_loc_l->lock, flags);

		node = __local_list_pop_मुक्त(steal_loc_l);
		अगर (!node)
			node = __local_list_pop_pending(lru, steal_loc_l);

		raw_spin_unlock_irqrestore(&steal_loc_l->lock, flags);

		steal = get_next_cpu(steal);
	पूर्ण जबतक (!node && steal != first_steal);

	loc_l->next_steal = steal;

	अगर (node) अणु
		raw_spin_lock_irqsave(&loc_l->lock, flags);
		__local_list_add_pending(lru, loc_l, cpu, node, hash);
		raw_spin_unlock_irqrestore(&loc_l->lock, flags);
	पूर्ण

	वापस node;
पूर्ण

काष्ठा bpf_lru_node *bpf_lru_pop_मुक्त(काष्ठा bpf_lru *lru, u32 hash)
अणु
	अगर (lru->percpu)
		वापस bpf_percpu_lru_pop_मुक्त(lru, hash);
	अन्यथा
		वापस bpf_common_lru_pop_मुक्त(lru, hash);
पूर्ण

अटल व्योम bpf_common_lru_push_मुक्त(काष्ठा bpf_lru *lru,
				     काष्ठा bpf_lru_node *node)
अणु
	u8 node_type = READ_ONCE(node->type);
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(node_type == BPF_LRU_LIST_T_FREE) ||
	    WARN_ON_ONCE(node_type == BPF_LRU_LOCAL_LIST_T_FREE))
		वापस;

	अगर (node_type == BPF_LRU_LOCAL_LIST_T_PENDING) अणु
		काष्ठा bpf_lru_locallist *loc_l;

		loc_l = per_cpu_ptr(lru->common_lru.local_list, node->cpu);

		raw_spin_lock_irqsave(&loc_l->lock, flags);

		अगर (unlikely(node->type != BPF_LRU_LOCAL_LIST_T_PENDING)) अणु
			raw_spin_unlock_irqrestore(&loc_l->lock, flags);
			जाओ check_lru_list;
		पूर्ण

		node->type = BPF_LRU_LOCAL_LIST_T_FREE;
		node->ref = 0;
		list_move(&node->list, local_मुक्त_list(loc_l));

		raw_spin_unlock_irqrestore(&loc_l->lock, flags);
		वापस;
	पूर्ण

check_lru_list:
	bpf_lru_list_push_मुक्त(&lru->common_lru.lru_list, node);
पूर्ण

अटल व्योम bpf_percpu_lru_push_मुक्त(काष्ठा bpf_lru *lru,
				     काष्ठा bpf_lru_node *node)
अणु
	काष्ठा bpf_lru_list *l;
	अचिन्हित दीर्घ flags;

	l = per_cpu_ptr(lru->percpu_lru, node->cpu);

	raw_spin_lock_irqsave(&l->lock, flags);

	__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_FREE);

	raw_spin_unlock_irqrestore(&l->lock, flags);
पूर्ण

व्योम bpf_lru_push_मुक्त(काष्ठा bpf_lru *lru, काष्ठा bpf_lru_node *node)
अणु
	अगर (lru->percpu)
		bpf_percpu_lru_push_मुक्त(lru, node);
	अन्यथा
		bpf_common_lru_push_मुक्त(lru, node);
पूर्ण

अटल व्योम bpf_common_lru_populate(काष्ठा bpf_lru *lru, व्योम *buf,
				    u32 node_offset, u32 elem_size,
				    u32 nr_elems)
अणु
	काष्ठा bpf_lru_list *l = &lru->common_lru.lru_list;
	u32 i;

	क्रम (i = 0; i < nr_elems; i++) अणु
		काष्ठा bpf_lru_node *node;

		node = (काष्ठा bpf_lru_node *)(buf + node_offset);
		node->type = BPF_LRU_LIST_T_FREE;
		node->ref = 0;
		list_add(&node->list, &l->lists[BPF_LRU_LIST_T_FREE]);
		buf += elem_size;
	पूर्ण
पूर्ण

अटल व्योम bpf_percpu_lru_populate(काष्ठा bpf_lru *lru, व्योम *buf,
				    u32 node_offset, u32 elem_size,
				    u32 nr_elems)
अणु
	u32 i, pcpu_entries;
	पूर्णांक cpu;
	काष्ठा bpf_lru_list *l;

	pcpu_entries = nr_elems / num_possible_cpus();

	i = 0;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा bpf_lru_node *node;

		l = per_cpu_ptr(lru->percpu_lru, cpu);
again:
		node = (काष्ठा bpf_lru_node *)(buf + node_offset);
		node->cpu = cpu;
		node->type = BPF_LRU_LIST_T_FREE;
		node->ref = 0;
		list_add(&node->list, &l->lists[BPF_LRU_LIST_T_FREE]);
		i++;
		buf += elem_size;
		अगर (i == nr_elems)
			अवरोध;
		अगर (i % pcpu_entries)
			जाओ again;
	पूर्ण
पूर्ण

व्योम bpf_lru_populate(काष्ठा bpf_lru *lru, व्योम *buf, u32 node_offset,
		      u32 elem_size, u32 nr_elems)
अणु
	अगर (lru->percpu)
		bpf_percpu_lru_populate(lru, buf, node_offset, elem_size,
					nr_elems);
	अन्यथा
		bpf_common_lru_populate(lru, buf, node_offset, elem_size,
					nr_elems);
पूर्ण

अटल व्योम bpf_lru_locallist_init(काष्ठा bpf_lru_locallist *loc_l, पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_BPF_LRU_LOCAL_LIST_T; i++)
		INIT_LIST_HEAD(&loc_l->lists[i]);

	loc_l->next_steal = cpu;

	raw_spin_lock_init(&loc_l->lock);
पूर्ण

अटल व्योम bpf_lru_list_init(काष्ठा bpf_lru_list *l)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_BPF_LRU_LIST_T; i++)
		INIT_LIST_HEAD(&l->lists[i]);

	क्रम (i = 0; i < NR_BPF_LRU_LIST_COUNT; i++)
		l->counts[i] = 0;

	l->next_inactive_rotation = &l->lists[BPF_LRU_LIST_T_INACTIVE];

	raw_spin_lock_init(&l->lock);
पूर्ण

पूर्णांक bpf_lru_init(काष्ठा bpf_lru *lru, bool percpu, u32 hash_offset,
		 del_from_htab_func del_from_htab, व्योम *del_arg)
अणु
	पूर्णांक cpu;

	अगर (percpu) अणु
		lru->percpu_lru = alloc_percpu(काष्ठा bpf_lru_list);
		अगर (!lru->percpu_lru)
			वापस -ENOMEM;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा bpf_lru_list *l;

			l = per_cpu_ptr(lru->percpu_lru, cpu);
			bpf_lru_list_init(l);
		पूर्ण
		lru->nr_scans = PERCPU_NR_SCANS;
	पूर्ण अन्यथा अणु
		काष्ठा bpf_common_lru *clru = &lru->common_lru;

		clru->local_list = alloc_percpu(काष्ठा bpf_lru_locallist);
		अगर (!clru->local_list)
			वापस -ENOMEM;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा bpf_lru_locallist *loc_l;

			loc_l = per_cpu_ptr(clru->local_list, cpu);
			bpf_lru_locallist_init(loc_l, cpu);
		पूर्ण

		bpf_lru_list_init(&clru->lru_list);
		lru->nr_scans = LOCAL_NR_SCANS;
	पूर्ण

	lru->percpu = percpu;
	lru->del_from_htab = del_from_htab;
	lru->del_arg = del_arg;
	lru->hash_offset = hash_offset;

	वापस 0;
पूर्ण

व्योम bpf_lru_destroy(काष्ठा bpf_lru *lru)
अणु
	अगर (lru->percpu)
		मुक्त_percpu(lru->percpu_lru);
	अन्यथा
		मुक्त_percpu(lru->common_lru.local_list);
पूर्ण
