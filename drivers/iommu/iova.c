<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2009, Intel Corporation.
 *
 * Author: Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 */

#समावेश <linux/iova.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpu.h>

/* The anchor node sits above the top of the usable address space */
#घोषणा IOVA_ANCHOR	~0UL

अटल bool iova_rcache_insert(काष्ठा iova_करोमुख्य *iovad,
			       अचिन्हित दीर्घ pfn,
			       अचिन्हित दीर्घ size);
अटल अचिन्हित दीर्घ iova_rcache_get(काष्ठा iova_करोमुख्य *iovad,
				     अचिन्हित दीर्घ size,
				     अचिन्हित दीर्घ limit_pfn);
अटल व्योम init_iova_rcaches(काष्ठा iova_करोमुख्य *iovad);
अटल व्योम मुक्त_cpu_cached_iovas(अचिन्हित पूर्णांक cpu, काष्ठा iova_करोमुख्य *iovad);
अटल व्योम मुक्त_iova_rcaches(काष्ठा iova_करोमुख्य *iovad);
अटल व्योम fq_destroy_all_entries(काष्ठा iova_करोमुख्य *iovad);
अटल व्योम fq_flush_समयout(काष्ठा समयr_list *t);

अटल पूर्णांक iova_cpuhp_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा iova_करोमुख्य *iovad;

	iovad = hlist_entry_safe(node, काष्ठा iova_करोमुख्य, cpuhp_dead);

	मुक्त_cpu_cached_iovas(cpu, iovad);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_global_cached_iovas(काष्ठा iova_करोमुख्य *iovad);

अटल काष्ठा iova *to_iova(काष्ठा rb_node *node)
अणु
	वापस rb_entry(node, काष्ठा iova, node);
पूर्ण

व्योम
init_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ granule,
	अचिन्हित दीर्घ start_pfn)
अणु
	/*
	 * IOVA granularity will normally be equal to the smallest
	 * supported IOMMU page size; both *must* be capable of
	 * representing inभागidual CPU pages exactly.
	 */
	BUG_ON((granule > PAGE_SIZE) || !is_घातer_of_2(granule));

	spin_lock_init(&iovad->iova_rbtree_lock);
	iovad->rbroot = RB_ROOT;
	iovad->cached_node = &iovad->anchor.node;
	iovad->cached32_node = &iovad->anchor.node;
	iovad->granule = granule;
	iovad->start_pfn = start_pfn;
	iovad->dma_32bit_pfn = 1UL << (32 - iova_shअगरt(iovad));
	iovad->max32_alloc_size = iovad->dma_32bit_pfn;
	iovad->flush_cb = शून्य;
	iovad->fq = शून्य;
	iovad->anchor.pfn_lo = iovad->anchor.pfn_hi = IOVA_ANCHOR;
	rb_link_node(&iovad->anchor.node, शून्य, &iovad->rbroot.rb_node);
	rb_insert_color(&iovad->anchor.node, &iovad->rbroot);
	cpuhp_state_add_instance_nocalls(CPUHP_IOMMU_IOVA_DEAD, &iovad->cpuhp_dead);
	init_iova_rcaches(iovad);
पूर्ण
EXPORT_SYMBOL_GPL(init_iova_करोमुख्य);

अटल bool has_iova_flush_queue(काष्ठा iova_करोमुख्य *iovad)
अणु
	वापस !!iovad->fq;
पूर्ण

अटल व्योम मुक्त_iova_flush_queue(काष्ठा iova_करोमुख्य *iovad)
अणु
	अगर (!has_iova_flush_queue(iovad))
		वापस;

	अगर (समयr_pending(&iovad->fq_समयr))
		del_समयr(&iovad->fq_समयr);

	fq_destroy_all_entries(iovad);

	मुक्त_percpu(iovad->fq);

	iovad->fq         = शून्य;
	iovad->flush_cb   = शून्य;
	iovad->entry_dtor = शून्य;
पूर्ण

पूर्णांक init_iova_flush_queue(काष्ठा iova_करोमुख्य *iovad,
			  iova_flush_cb flush_cb, iova_entry_dtor entry_dtor)
अणु
	काष्ठा iova_fq __percpu *queue;
	पूर्णांक cpu;

	atomic64_set(&iovad->fq_flush_start_cnt,  0);
	atomic64_set(&iovad->fq_flush_finish_cnt, 0);

	queue = alloc_percpu(काष्ठा iova_fq);
	अगर (!queue)
		वापस -ENOMEM;

	iovad->flush_cb   = flush_cb;
	iovad->entry_dtor = entry_dtor;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा iova_fq *fq;

		fq = per_cpu_ptr(queue, cpu);
		fq->head = 0;
		fq->tail = 0;

		spin_lock_init(&fq->lock);
	पूर्ण

	smp_wmb();

	iovad->fq = queue;

	समयr_setup(&iovad->fq_समयr, fq_flush_समयout, 0);
	atomic_set(&iovad->fq_समयr_on, 0);

	वापस 0;
पूर्ण

अटल काष्ठा rb_node *
__get_cached_rbnode(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ limit_pfn)
अणु
	अगर (limit_pfn <= iovad->dma_32bit_pfn)
		वापस iovad->cached32_node;

	वापस iovad->cached_node;
पूर्ण

अटल व्योम
__cached_rbnode_insert_update(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *new)
अणु
	अगर (new->pfn_hi < iovad->dma_32bit_pfn)
		iovad->cached32_node = &new->node;
	अन्यथा
		iovad->cached_node = &new->node;
पूर्ण

अटल व्योम
__cached_rbnode_delete_update(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *मुक्त)
अणु
	काष्ठा iova *cached_iova;

	cached_iova = to_iova(iovad->cached32_node);
	अगर (मुक्त == cached_iova ||
	    (मुक्त->pfn_hi < iovad->dma_32bit_pfn &&
	     मुक्त->pfn_lo >= cached_iova->pfn_lo)) अणु
		iovad->cached32_node = rb_next(&मुक्त->node);
		iovad->max32_alloc_size = iovad->dma_32bit_pfn;
	पूर्ण

	cached_iova = to_iova(iovad->cached_node);
	अगर (मुक्त->pfn_lo >= cached_iova->pfn_lo)
		iovad->cached_node = rb_next(&मुक्त->node);
पूर्ण

अटल काष्ठा rb_node *iova_find_limit(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ limit_pfn)
अणु
	काष्ठा rb_node *node, *next;
	/*
	 * Ideally what we'd like to judge here is whether limit_pfn is बंद
	 * enough to the highest-allocated IOVA that starting the allocation
	 * walk from the anchor node will be quicker than this initial work to
	 * find an exact starting poपूर्णांक (especially अगर that ends up being the
	 * anchor node anyway). This is an incredibly crude approximation which
	 * only really helps the most likely हाल, but is at least trivially easy.
	 */
	अगर (limit_pfn > iovad->dma_32bit_pfn)
		वापस &iovad->anchor.node;

	node = iovad->rbroot.rb_node;
	जबतक (to_iova(node)->pfn_hi < limit_pfn)
		node = node->rb_right;

search_left:
	जबतक (node->rb_left && to_iova(node->rb_left)->pfn_lo >= limit_pfn)
		node = node->rb_left;

	अगर (!node->rb_left)
		वापस node;

	next = node->rb_left;
	जबतक (next->rb_right) अणु
		next = next->rb_right;
		अगर (to_iova(next)->pfn_lo >= limit_pfn) अणु
			node = next;
			जाओ search_left;
		पूर्ण
	पूर्ण

	वापस node;
पूर्ण

/* Insert the iova पूर्णांकo करोमुख्य rbtree by holding ग_लिखोr lock */
अटल व्योम
iova_insert_rbtree(काष्ठा rb_root *root, काष्ठा iova *iova,
		   काष्ठा rb_node *start)
अणु
	काष्ठा rb_node **new, *parent = शून्य;

	new = (start) ? &start : &(root->rb_node);
	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा iova *this = to_iova(*new);

		parent = *new;

		अगर (iova->pfn_lo < this->pfn_lo)
			new = &((*new)->rb_left);
		अन्यथा अगर (iova->pfn_lo > this->pfn_lo)
			new = &((*new)->rb_right);
		अन्यथा अणु
			WARN_ON(1); /* this should not happen */
			वापस;
		पूर्ण
	पूर्ण
	/* Add new node and rebalance tree. */
	rb_link_node(&iova->node, parent, new);
	rb_insert_color(&iova->node, root);
पूर्ण

अटल पूर्णांक __alloc_and_insert_iova_range(काष्ठा iova_करोमुख्य *iovad,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ limit_pfn,
			काष्ठा iova *new, bool size_aligned)
अणु
	काष्ठा rb_node *curr, *prev;
	काष्ठा iova *curr_iova;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ new_pfn, retry_pfn;
	अचिन्हित दीर्घ align_mask = ~0UL;
	अचिन्हित दीर्घ high_pfn = limit_pfn, low_pfn = iovad->start_pfn;

	अगर (size_aligned)
		align_mask <<= fls_दीर्घ(size - 1);

	/* Walk the tree backwards */
	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	अगर (limit_pfn <= iovad->dma_32bit_pfn &&
			size >= iovad->max32_alloc_size)
		जाओ iova32_full;

	curr = __get_cached_rbnode(iovad, limit_pfn);
	curr_iova = to_iova(curr);
	retry_pfn = curr_iova->pfn_hi + 1;

retry:
	करो अणु
		high_pfn = min(high_pfn, curr_iova->pfn_lo);
		new_pfn = (high_pfn - size) & align_mask;
		prev = curr;
		curr = rb_prev(curr);
		curr_iova = to_iova(curr);
	पूर्ण जबतक (curr && new_pfn <= curr_iova->pfn_hi && new_pfn >= low_pfn);

	अगर (high_pfn < size || new_pfn < low_pfn) अणु
		अगर (low_pfn == iovad->start_pfn && retry_pfn < limit_pfn) अणु
			high_pfn = limit_pfn;
			low_pfn = retry_pfn;
			curr = iova_find_limit(iovad, limit_pfn);
			curr_iova = to_iova(curr);
			जाओ retry;
		पूर्ण
		iovad->max32_alloc_size = size;
		जाओ iova32_full;
	पूर्ण

	/* pfn_lo will poपूर्णांक to size aligned address अगर size_aligned is set */
	new->pfn_lo = new_pfn;
	new->pfn_hi = new->pfn_lo + size - 1;

	/* If we have 'prev', it's a valid place to start the insertion. */
	iova_insert_rbtree(&iovad->rbroot, new, prev);
	__cached_rbnode_insert_update(iovad, new);

	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	वापस 0;

iova32_full:
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा kmem_cache *iova_cache;
अटल अचिन्हित पूर्णांक iova_cache_users;
अटल DEFINE_MUTEX(iova_cache_mutex);

अटल काष्ठा iova *alloc_iova_mem(व्योम)
अणु
	वापस kmem_cache_zalloc(iova_cache, GFP_ATOMIC | __GFP_NOWARN);
पूर्ण

अटल व्योम मुक्त_iova_mem(काष्ठा iova *iova)
अणु
	अगर (iova->pfn_lo != IOVA_ANCHOR)
		kmem_cache_मुक्त(iova_cache, iova);
पूर्ण

पूर्णांक iova_cache_get(व्योम)
अणु
	mutex_lock(&iova_cache_mutex);
	अगर (!iova_cache_users) अणु
		पूर्णांक ret;

		ret = cpuhp_setup_state_multi(CPUHP_IOMMU_IOVA_DEAD, "iommu/iova:dead", शून्य,
					iova_cpuhp_dead);
		अगर (ret) अणु
			mutex_unlock(&iova_cache_mutex);
			pr_err("Couldn't register cpuhp handler\n");
			वापस ret;
		पूर्ण

		iova_cache = kmem_cache_create(
			"iommu_iova", माप(काष्ठा iova), 0,
			SLAB_HWCACHE_ALIGN, शून्य);
		अगर (!iova_cache) अणु
			cpuhp_हटाओ_multi_state(CPUHP_IOMMU_IOVA_DEAD);
			mutex_unlock(&iova_cache_mutex);
			pr_err("Couldn't create iova cache\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	iova_cache_users++;
	mutex_unlock(&iova_cache_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iova_cache_get);

व्योम iova_cache_put(व्योम)
अणु
	mutex_lock(&iova_cache_mutex);
	अगर (WARN_ON(!iova_cache_users)) अणु
		mutex_unlock(&iova_cache_mutex);
		वापस;
	पूर्ण
	iova_cache_users--;
	अगर (!iova_cache_users) अणु
		cpuhp_हटाओ_multi_state(CPUHP_IOMMU_IOVA_DEAD);
		kmem_cache_destroy(iova_cache);
	पूर्ण
	mutex_unlock(&iova_cache_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(iova_cache_put);

/**
 * alloc_iova - allocates an iova
 * @iovad: - iova करोमुख्य in question
 * @size: - size of page frames to allocate
 * @limit_pfn: - max limit address
 * @size_aligned: - set अगर size_aligned address range is required
 * This function allocates an iova in the range iovad->start_pfn to limit_pfn,
 * searching top-करोwn from limit_pfn to iovad->start_pfn. If the size_aligned
 * flag is set then the allocated address iova->pfn_lo will be naturally
 * aligned on roundup_घातer_of_two(size).
 */
काष्ठा iova *
alloc_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ limit_pfn,
	bool size_aligned)
अणु
	काष्ठा iova *new_iova;
	पूर्णांक ret;

	new_iova = alloc_iova_mem();
	अगर (!new_iova)
		वापस शून्य;

	ret = __alloc_and_insert_iova_range(iovad, size, limit_pfn + 1,
			new_iova, size_aligned);

	अगर (ret) अणु
		मुक्त_iova_mem(new_iova);
		वापस शून्य;
	पूर्ण

	वापस new_iova;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_iova);

अटल काष्ठा iova *
निजी_find_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा rb_node *node = iovad->rbroot.rb_node;

	निश्चित_spin_locked(&iovad->iova_rbtree_lock);

	जबतक (node) अणु
		काष्ठा iova *iova = to_iova(node);

		अगर (pfn < iova->pfn_lo)
			node = node->rb_left;
		अन्यथा अगर (pfn > iova->pfn_hi)
			node = node->rb_right;
		अन्यथा
			वापस iova;	/* pfn falls within iova's range */
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम निजी_मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *iova)
अणु
	निश्चित_spin_locked(&iovad->iova_rbtree_lock);
	__cached_rbnode_delete_update(iovad, iova);
	rb_erase(&iova->node, &iovad->rbroot);
	मुक्त_iova_mem(iova);
पूर्ण

/**
 * find_iova - finds an iova क्रम a given pfn
 * @iovad: - iova करोमुख्य in question.
 * @pfn: - page frame number
 * This function finds and वापसs an iova beदीर्घing to the
 * given करोमुख्य which matches the given pfn.
 */
काष्ठा iova *find_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iova *iova;

	/* Take the lock so that no other thपढ़ो is manipulating the rbtree */
	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	iova = निजी_find_iova(iovad, pfn);
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	वापस iova;
पूर्ण
EXPORT_SYMBOL_GPL(find_iova);

/**
 * __मुक्त_iova - मुक्तs the given iova
 * @iovad: iova करोमुख्य in question.
 * @iova: iova in question.
 * Frees the given iova beदीर्घing to the giving करोमुख्य
 */
व्योम
__मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova *iova)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	निजी_मुक्त_iova(iovad, iova);
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(__मुक्त_iova);

/**
 * मुक्त_iova - finds and मुक्तs the iova क्रम a given pfn
 * @iovad: - iova करोमुख्य in question.
 * @pfn: - pfn that is allocated previously
 * This functions finds an iova क्रम a given pfn and then
 * मुक्तs the iova from that करोमुख्य.
 */
व्योम
मुक्त_iova(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iova *iova;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	iova = निजी_find_iova(iovad, pfn);
	अगर (iova)
		निजी_मुक्त_iova(iovad, iova);
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);

पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_iova);

/**
 * alloc_iova_fast - allocates an iova from rcache
 * @iovad: - iova करोमुख्य in question
 * @size: - size of page frames to allocate
 * @limit_pfn: - max limit address
 * @flush_rcache: - set to flush rcache on regular allocation failure
 * This function tries to satisfy an iova allocation from the rcache,
 * and falls back to regular allocation on failure. If regular allocation
 * fails too and the flush_rcache flag is set then the rcache will be flushed.
*/
अचिन्हित दीर्घ
alloc_iova_fast(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ limit_pfn, bool flush_rcache)
अणु
	अचिन्हित दीर्घ iova_pfn;
	काष्ठा iova *new_iova;

	iova_pfn = iova_rcache_get(iovad, size, limit_pfn + 1);
	अगर (iova_pfn)
		वापस iova_pfn;

retry:
	new_iova = alloc_iova(iovad, size, limit_pfn, true);
	अगर (!new_iova) अणु
		अचिन्हित पूर्णांक cpu;

		अगर (!flush_rcache)
			वापस 0;

		/* Try replenishing IOVAs by flushing rcache. */
		flush_rcache = false;
		क्रम_each_online_cpu(cpu)
			मुक्त_cpu_cached_iovas(cpu, iovad);
		मुक्त_global_cached_iovas(iovad);
		जाओ retry;
	पूर्ण

	वापस new_iova->pfn_lo;
पूर्ण

/**
 * मुक्त_iova_fast - मुक्त iova pfn range पूर्णांकo rcache
 * @iovad: - iova करोमुख्य in question.
 * @pfn: - pfn that is allocated previously
 * @size: - # of pages in range
 * This functions मुक्तs an iova range by trying to put it पूर्णांकo the rcache,
 * falling back to regular iova deallocation via मुक्त_iova() अगर this fails.
 */
व्योम
मुक्त_iova_fast(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	अगर (iova_rcache_insert(iovad, pfn, size))
		वापस;

	मुक्त_iova(iovad, pfn);
पूर्ण

#घोषणा fq_ring_क्रम_each(i, fq) \
	क्रम ((i) = (fq)->head; (i) != (fq)->tail; (i) = ((i) + 1) % IOVA_FQ_SIZE)

अटल अंतरभूत bool fq_full(काष्ठा iova_fq *fq)
अणु
	निश्चित_spin_locked(&fq->lock);
	वापस (((fq->tail + 1) % IOVA_FQ_SIZE) == fq->head);
पूर्ण

अटल अंतरभूत अचिन्हित fq_ring_add(काष्ठा iova_fq *fq)
अणु
	अचिन्हित idx = fq->tail;

	निश्चित_spin_locked(&fq->lock);

	fq->tail = (idx + 1) % IOVA_FQ_SIZE;

	वापस idx;
पूर्ण

अटल व्योम fq_ring_मुक्त(काष्ठा iova_करोमुख्य *iovad, काष्ठा iova_fq *fq)
अणु
	u64 counter = atomic64_पढ़ो(&iovad->fq_flush_finish_cnt);
	अचिन्हित idx;

	निश्चित_spin_locked(&fq->lock);

	fq_ring_क्रम_each(idx, fq) अणु

		अगर (fq->entries[idx].counter >= counter)
			अवरोध;

		अगर (iovad->entry_dtor)
			iovad->entry_dtor(fq->entries[idx].data);

		मुक्त_iova_fast(iovad,
			       fq->entries[idx].iova_pfn,
			       fq->entries[idx].pages);

		fq->head = (fq->head + 1) % IOVA_FQ_SIZE;
	पूर्ण
पूर्ण

अटल व्योम iova_करोमुख्य_flush(काष्ठा iova_करोमुख्य *iovad)
अणु
	atomic64_inc(&iovad->fq_flush_start_cnt);
	iovad->flush_cb(iovad);
	atomic64_inc(&iovad->fq_flush_finish_cnt);
पूर्ण

अटल व्योम fq_destroy_all_entries(काष्ठा iova_करोमुख्य *iovad)
अणु
	पूर्णांक cpu;

	/*
	 * This code runs when the iova_करोमुख्य is being detroyed, so करोn't
	 * bother to मुक्त iovas, just call the entry_dtor on all reमुख्यing
	 * entries.
	 */
	अगर (!iovad->entry_dtor)
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा iova_fq *fq = per_cpu_ptr(iovad->fq, cpu);
		पूर्णांक idx;

		fq_ring_क्रम_each(idx, fq)
			iovad->entry_dtor(fq->entries[idx].data);
	पूर्ण
पूर्ण

अटल व्योम fq_flush_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा iova_करोमुख्य *iovad = from_समयr(iovad, t, fq_समयr);
	पूर्णांक cpu;

	atomic_set(&iovad->fq_समयr_on, 0);
	iova_करोमुख्य_flush(iovad);

	क्रम_each_possible_cpu(cpu) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा iova_fq *fq;

		fq = per_cpu_ptr(iovad->fq, cpu);
		spin_lock_irqsave(&fq->lock, flags);
		fq_ring_मुक्त(iovad, fq);
		spin_unlock_irqrestore(&fq->lock, flags);
	पूर्ण
पूर्ण

व्योम queue_iova(काष्ठा iova_करोमुख्य *iovad,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ pages,
		अचिन्हित दीर्घ data)
अणु
	काष्ठा iova_fq *fq = raw_cpu_ptr(iovad->fq);
	अचिन्हित दीर्घ flags;
	अचिन्हित idx;

	spin_lock_irqsave(&fq->lock, flags);

	/*
	 * First हटाओ all entries from the flush queue that have alपढ़ोy been
	 * flushed out on another CPU. This makes the fq_full() check below less
	 * likely to be true.
	 */
	fq_ring_मुक्त(iovad, fq);

	अगर (fq_full(fq)) अणु
		iova_करोमुख्य_flush(iovad);
		fq_ring_मुक्त(iovad, fq);
	पूर्ण

	idx = fq_ring_add(fq);

	fq->entries[idx].iova_pfn = pfn;
	fq->entries[idx].pages    = pages;
	fq->entries[idx].data     = data;
	fq->entries[idx].counter  = atomic64_पढ़ो(&iovad->fq_flush_start_cnt);

	spin_unlock_irqrestore(&fq->lock, flags);

	/* Aव्योम false sharing as much as possible. */
	अगर (!atomic_पढ़ो(&iovad->fq_समयr_on) &&
	    !atomic_xchg(&iovad->fq_समयr_on, 1))
		mod_समयr(&iovad->fq_समयr,
			  jअगरfies + msecs_to_jअगरfies(IOVA_FQ_TIMEOUT));
पूर्ण

/**
 * put_iova_करोमुख्य - destroys the iova करोमुख्य
 * @iovad: - iova करोमुख्य in question.
 * All the iova's in that करोमुख्य are destroyed.
 */
व्योम put_iova_करोमुख्य(काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iova *iova, *पंचांगp;

	cpuhp_state_हटाओ_instance_nocalls(CPUHP_IOMMU_IOVA_DEAD,
					    &iovad->cpuhp_dead);

	मुक्त_iova_flush_queue(iovad);
	मुक्त_iova_rcaches(iovad);
	rbtree_postorder_क्रम_each_entry_safe(iova, पंचांगp, &iovad->rbroot, node)
		मुक्त_iova_mem(iova);
पूर्ण
EXPORT_SYMBOL_GPL(put_iova_करोमुख्य);

अटल पूर्णांक
__is_range_overlap(काष्ठा rb_node *node,
	अचिन्हित दीर्घ pfn_lo, अचिन्हित दीर्घ pfn_hi)
अणु
	काष्ठा iova *iova = to_iova(node);

	अगर ((pfn_lo <= iova->pfn_hi) && (pfn_hi >= iova->pfn_lo))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा iova *
alloc_and_init_iova(अचिन्हित दीर्घ pfn_lo, अचिन्हित दीर्घ pfn_hi)
अणु
	काष्ठा iova *iova;

	iova = alloc_iova_mem();
	अगर (iova) अणु
		iova->pfn_lo = pfn_lo;
		iova->pfn_hi = pfn_hi;
	पूर्ण

	वापस iova;
पूर्ण

अटल काष्ठा iova *
__insert_new_range(काष्ठा iova_करोमुख्य *iovad,
	अचिन्हित दीर्घ pfn_lo, अचिन्हित दीर्घ pfn_hi)
अणु
	काष्ठा iova *iova;

	iova = alloc_and_init_iova(pfn_lo, pfn_hi);
	अगर (iova)
		iova_insert_rbtree(&iovad->rbroot, iova, शून्य);

	वापस iova;
पूर्ण

अटल व्योम
__adjust_overlap_range(काष्ठा iova *iova,
	अचिन्हित दीर्घ *pfn_lo, अचिन्हित दीर्घ *pfn_hi)
अणु
	अगर (*pfn_lo < iova->pfn_lo)
		iova->pfn_lo = *pfn_lo;
	अगर (*pfn_hi > iova->pfn_hi)
		*pfn_lo = iova->pfn_hi + 1;
पूर्ण

/**
 * reserve_iova - reserves an iova in the given range
 * @iovad: - iova करोमुख्य poपूर्णांकer
 * @pfn_lo: - lower page frame address
 * @pfn_hi:- higher pfn adderss
 * This function allocates reserves the address range from pfn_lo to pfn_hi so
 * that this address is not dished out as part of alloc_iova.
 */
काष्ठा iova *
reserve_iova(काष्ठा iova_करोमुख्य *iovad,
	अचिन्हित दीर्घ pfn_lo, अचिन्हित दीर्घ pfn_hi)
अणु
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;
	काष्ठा iova *iova;
	अचिन्हित पूर्णांक overlap = 0;

	/* Don't allow nonsensical pfns */
	अगर (WARN_ON((pfn_hi | pfn_lo) > (ULदीर्घ_उच्च >> iova_shअगरt(iovad))))
		वापस शून्य;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	क्रम (node = rb_first(&iovad->rbroot); node; node = rb_next(node)) अणु
		अगर (__is_range_overlap(node, pfn_lo, pfn_hi)) अणु
			iova = to_iova(node);
			__adjust_overlap_range(iova, &pfn_lo, &pfn_hi);
			अगर ((pfn_lo >= iova->pfn_lo) &&
				(pfn_hi <= iova->pfn_hi))
				जाओ finish;
			overlap = 1;

		पूर्ण अन्यथा अगर (overlap)
				अवरोध;
	पूर्ण

	/* We are here either because this is the first reserver node
	 * or need to insert reमुख्यing non overlap addr range
	 */
	iova = __insert_new_range(iovad, pfn_lo, pfn_hi);
finish:

	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	वापस iova;
पूर्ण
EXPORT_SYMBOL_GPL(reserve_iova);

/*
 * Magazine caches क्रम IOVA ranges.  For an पूर्णांकroduction to magazines,
 * see the USENIX 2001 paper "Magazines and Vmem: Extending the Slab
 * Allocator to Many CPUs and Arbitrary Resources" by Bonwick and Adams.
 * For simplicity, we use a अटल magazine size and करोn't implement the
 * dynamic size tuning described in the paper.
 */

#घोषणा IOVA_MAG_SIZE 128

काष्ठा iova_magazine अणु
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ pfns[IOVA_MAG_SIZE];
पूर्ण;

काष्ठा iova_cpu_rcache अणु
	spinlock_t lock;
	काष्ठा iova_magazine *loaded;
	काष्ठा iova_magazine *prev;
पूर्ण;

अटल काष्ठा iova_magazine *iova_magazine_alloc(gfp_t flags)
अणु
	वापस kzalloc(माप(काष्ठा iova_magazine), flags);
पूर्ण

अटल व्योम iova_magazine_मुक्त(काष्ठा iova_magazine *mag)
अणु
	kमुक्त(mag);
पूर्ण

अटल व्योम
iova_magazine_मुक्त_pfns(काष्ठा iova_magazine *mag, काष्ठा iova_करोमुख्य *iovad)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!mag)
		वापस;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);

	क्रम (i = 0 ; i < mag->size; ++i) अणु
		काष्ठा iova *iova = निजी_find_iova(iovad, mag->pfns[i]);

		अगर (WARN_ON(!iova))
			जारी;

		निजी_मुक्त_iova(iovad, iova);
	पूर्ण

	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);

	mag->size = 0;
पूर्ण

अटल bool iova_magazine_full(काष्ठा iova_magazine *mag)
अणु
	वापस (mag && mag->size == IOVA_MAG_SIZE);
पूर्ण

अटल bool iova_magazine_empty(काष्ठा iova_magazine *mag)
अणु
	वापस (!mag || mag->size == 0);
पूर्ण

अटल अचिन्हित दीर्घ iova_magazine_pop(काष्ठा iova_magazine *mag,
				       अचिन्हित दीर्घ limit_pfn)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ pfn;

	BUG_ON(iova_magazine_empty(mag));

	/* Only fall back to the rbtree अगर we have no suitable pfns at all */
	क्रम (i = mag->size - 1; mag->pfns[i] > limit_pfn; i--)
		अगर (i == 0)
			वापस 0;

	/* Swap it to pop it */
	pfn = mag->pfns[i];
	mag->pfns[i] = mag->pfns[--mag->size];

	वापस pfn;
पूर्ण

अटल व्योम iova_magazine_push(काष्ठा iova_magazine *mag, अचिन्हित दीर्घ pfn)
अणु
	BUG_ON(iova_magazine_full(mag));

	mag->pfns[mag->size++] = pfn;
पूर्ण

अटल व्योम init_iova_rcaches(काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iova_cpu_rcache *cpu_rcache;
	काष्ठा iova_rcache *rcache;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i;

	क्रम (i = 0; i < IOVA_RANGE_CACHE_MAX_SIZE; ++i) अणु
		rcache = &iovad->rcaches[i];
		spin_lock_init(&rcache->lock);
		rcache->depot_size = 0;
		rcache->cpu_rcaches = __alloc_percpu(माप(*cpu_rcache), cache_line_size());
		अगर (WARN_ON(!rcache->cpu_rcaches))
			जारी;
		क्रम_each_possible_cpu(cpu) अणु
			cpu_rcache = per_cpu_ptr(rcache->cpu_rcaches, cpu);
			spin_lock_init(&cpu_rcache->lock);
			cpu_rcache->loaded = iova_magazine_alloc(GFP_KERNEL);
			cpu_rcache->prev = iova_magazine_alloc(GFP_KERNEL);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Try inserting IOVA range starting with 'iova_pfn' into 'rcache', and
 * वापस true on success.  Can fail अगर rcache is full and we can't मुक्त
 * space, and मुक्त_iova() (our only caller) will then वापस the IOVA
 * range to the rbtree instead.
 */
अटल bool __iova_rcache_insert(काष्ठा iova_करोमुख्य *iovad,
				 काष्ठा iova_rcache *rcache,
				 अचिन्हित दीर्घ iova_pfn)
अणु
	काष्ठा iova_magazine *mag_to_मुक्त = शून्य;
	काष्ठा iova_cpu_rcache *cpu_rcache;
	bool can_insert = false;
	अचिन्हित दीर्घ flags;

	cpu_rcache = raw_cpu_ptr(rcache->cpu_rcaches);
	spin_lock_irqsave(&cpu_rcache->lock, flags);

	अगर (!iova_magazine_full(cpu_rcache->loaded)) अणु
		can_insert = true;
	पूर्ण अन्यथा अगर (!iova_magazine_full(cpu_rcache->prev)) अणु
		swap(cpu_rcache->prev, cpu_rcache->loaded);
		can_insert = true;
	पूर्ण अन्यथा अणु
		काष्ठा iova_magazine *new_mag = iova_magazine_alloc(GFP_ATOMIC);

		अगर (new_mag) अणु
			spin_lock(&rcache->lock);
			अगर (rcache->depot_size < MAX_GLOBAL_MAGS) अणु
				rcache->depot[rcache->depot_size++] =
						cpu_rcache->loaded;
			पूर्ण अन्यथा अणु
				mag_to_मुक्त = cpu_rcache->loaded;
			पूर्ण
			spin_unlock(&rcache->lock);

			cpu_rcache->loaded = new_mag;
			can_insert = true;
		पूर्ण
	पूर्ण

	अगर (can_insert)
		iova_magazine_push(cpu_rcache->loaded, iova_pfn);

	spin_unlock_irqrestore(&cpu_rcache->lock, flags);

	अगर (mag_to_मुक्त) अणु
		iova_magazine_मुक्त_pfns(mag_to_मुक्त, iovad);
		iova_magazine_मुक्त(mag_to_मुक्त);
	पूर्ण

	वापस can_insert;
पूर्ण

अटल bool iova_rcache_insert(काष्ठा iova_करोमुख्य *iovad, अचिन्हित दीर्घ pfn,
			       अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक log_size = order_base_2(size);

	अगर (log_size >= IOVA_RANGE_CACHE_MAX_SIZE)
		वापस false;

	वापस __iova_rcache_insert(iovad, &iovad->rcaches[log_size], pfn);
पूर्ण

/*
 * Caller wants to allocate a new IOVA range from 'rcache'.  If we can
 * satisfy the request, वापस a matching non-शून्य range and हटाओ
 * it from the 'rcache'.
 */
अटल अचिन्हित दीर्घ __iova_rcache_get(काष्ठा iova_rcache *rcache,
				       अचिन्हित दीर्घ limit_pfn)
अणु
	काष्ठा iova_cpu_rcache *cpu_rcache;
	अचिन्हित दीर्घ iova_pfn = 0;
	bool has_pfn = false;
	अचिन्हित दीर्घ flags;

	cpu_rcache = raw_cpu_ptr(rcache->cpu_rcaches);
	spin_lock_irqsave(&cpu_rcache->lock, flags);

	अगर (!iova_magazine_empty(cpu_rcache->loaded)) अणु
		has_pfn = true;
	पूर्ण अन्यथा अगर (!iova_magazine_empty(cpu_rcache->prev)) अणु
		swap(cpu_rcache->prev, cpu_rcache->loaded);
		has_pfn = true;
	पूर्ण अन्यथा अणु
		spin_lock(&rcache->lock);
		अगर (rcache->depot_size > 0) अणु
			iova_magazine_मुक्त(cpu_rcache->loaded);
			cpu_rcache->loaded = rcache->depot[--rcache->depot_size];
			has_pfn = true;
		पूर्ण
		spin_unlock(&rcache->lock);
	पूर्ण

	अगर (has_pfn)
		iova_pfn = iova_magazine_pop(cpu_rcache->loaded, limit_pfn);

	spin_unlock_irqrestore(&cpu_rcache->lock, flags);

	वापस iova_pfn;
पूर्ण

/*
 * Try to satisfy IOVA allocation range from rcache.  Fail अगर requested
 * size is too big or the DMA limit we are given isn't satisfied by the
 * top element in the magazine.
 */
अटल अचिन्हित दीर्घ iova_rcache_get(काष्ठा iova_करोमुख्य *iovad,
				     अचिन्हित दीर्घ size,
				     अचिन्हित दीर्घ limit_pfn)
अणु
	अचिन्हित पूर्णांक log_size = order_base_2(size);

	अगर (log_size >= IOVA_RANGE_CACHE_MAX_SIZE)
		वापस 0;

	वापस __iova_rcache_get(&iovad->rcaches[log_size], limit_pfn - size);
पूर्ण

/*
 * मुक्त rcache data काष्ठाures.
 */
अटल व्योम मुक्त_iova_rcaches(काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iova_rcache *rcache;
	काष्ठा iova_cpu_rcache *cpu_rcache;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i, j;

	क्रम (i = 0; i < IOVA_RANGE_CACHE_MAX_SIZE; ++i) अणु
		rcache = &iovad->rcaches[i];
		क्रम_each_possible_cpu(cpu) अणु
			cpu_rcache = per_cpu_ptr(rcache->cpu_rcaches, cpu);
			iova_magazine_मुक्त(cpu_rcache->loaded);
			iova_magazine_मुक्त(cpu_rcache->prev);
		पूर्ण
		मुक्त_percpu(rcache->cpu_rcaches);
		क्रम (j = 0; j < rcache->depot_size; ++j)
			iova_magazine_मुक्त(rcache->depot[j]);
	पूर्ण
पूर्ण

/*
 * मुक्त all the IOVA ranges cached by a cpu (used when cpu is unplugged)
 */
अटल व्योम मुक्त_cpu_cached_iovas(अचिन्हित पूर्णांक cpu, काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iova_cpu_rcache *cpu_rcache;
	काष्ठा iova_rcache *rcache;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < IOVA_RANGE_CACHE_MAX_SIZE; ++i) अणु
		rcache = &iovad->rcaches[i];
		cpu_rcache = per_cpu_ptr(rcache->cpu_rcaches, cpu);
		spin_lock_irqsave(&cpu_rcache->lock, flags);
		iova_magazine_मुक्त_pfns(cpu_rcache->loaded, iovad);
		iova_magazine_मुक्त_pfns(cpu_rcache->prev, iovad);
		spin_unlock_irqrestore(&cpu_rcache->lock, flags);
	पूर्ण
पूर्ण

/*
 * मुक्त all the IOVA ranges of global cache
 */
अटल व्योम मुक्त_global_cached_iovas(काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iova_rcache *rcache;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j;

	क्रम (i = 0; i < IOVA_RANGE_CACHE_MAX_SIZE; ++i) अणु
		rcache = &iovad->rcaches[i];
		spin_lock_irqsave(&rcache->lock, flags);
		क्रम (j = 0; j < rcache->depot_size; ++j) अणु
			iova_magazine_मुक्त_pfns(rcache->depot[j], iovad);
			iova_magazine_मुक्त(rcache->depot[j]);
		पूर्ण
		rcache->depot_size = 0;
		spin_unlock_irqrestore(&rcache->lock, flags);
	पूर्ण
पूर्ण
MODULE_AUTHOR("Anil S Keshavamurthy <anil.s.keshavamurthy@intel.com>");
MODULE_LICENSE("GPL");
