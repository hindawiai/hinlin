<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SLOB Allocator: Simple List Of Blocks
 *
 * Matt Mackall <mpm@selenic.com> 12/30/03
 *
 * NUMA support by Paul Mundt, 2007.
 *
 * How SLOB works:
 *
 * The core of SLOB is a traditional K&R style heap allocator, with
 * support क्रम वापसing aligned objects. The granularity of this
 * allocator is as little as 2 bytes, however typically most architectures
 * will require 4 bytes on 32-bit and 8 bytes on 64-bit.
 *
 * The slob heap is a set of linked list of pages from alloc_pages(),
 * and within each page, there is a singly-linked list of मुक्त blocks
 * (slob_t). The heap is grown on demand. To reduce fragmentation,
 * heap pages are segregated पूर्णांकo three lists, with objects less than
 * 256 bytes, objects less than 1024 bytes, and all other objects.
 *
 * Allocation from heap involves first searching क्रम a page with
 * sufficient मुक्त blocks (using a next-fit-like approach) followed by
 * a first-fit scan of the page. Deallocation inserts objects back
 * पूर्णांकo the मुक्त list in address order, so this is effectively an
 * address-ordered first fit.
 *
 * Above this is an implementation of kदो_स्मृति/kमुक्त. Blocks वापसed
 * from kदो_स्मृति are prepended with a 4-byte header with the kदो_स्मृति size.
 * If kदो_स्मृति is asked क्रम objects of PAGE_SIZE or larger, it calls
 * alloc_pages() directly, allocating compound pages so the page order
 * करोes not have to be separately tracked.
 * These objects are detected in kमुक्त() because PageSlab()
 * is false क्रम them.
 *
 * SLAB is emulated on top of SLOB by simply calling स्थिरructors and
 * deकाष्ठाors क्रम every SLAB allocation. Objects are वापसed with the
 * 4-byte alignment unless the SLAB_HWCACHE_ALIGN flag is set, in which
 * हाल the low-level allocator will fragment blocks to create the proper
 * alignment. Again, objects of page-size or greater are allocated by
 * calling alloc_pages(). As SLAB objects know their size, no separate
 * size bookkeeping is necessary and there is essentially no allocation
 * space overhead, and compound pages aren't needed क्रम multi-page
 * allocations.
 *
 * NUMA support in SLOB is fairly simplistic, pushing most of the real
 * logic करोwn to the page allocator, and simply करोing the node accounting
 * on the upper levels. In the event that a node id is explicitly
 * provided, __alloc_pages_node() with the specअगरied node id is used
 * instead. The common हाल (or when the node id isn't explicitly provided)
 * will शेष to the current node, as per numa_node_id().
 *
 * Node aware pages are still inserted in to the global मुक्तlist, and
 * these are scanned क्रम by matching against the node id encoded in the
 * page flags. As a result, block allocations that can be satisfied from
 * the मुक्तlist will only be करोne so on pages residing on the same node,
 * in order to prevent अक्रमom node placement.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <linux/mm.h>
#समावेश <linux/swap.h> /* काष्ठा reclaim_state */
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/kmemleak.h>

#समावेश <trace/events/kस्मृति.स>

#समावेश <linux/atomic.h>

#समावेश "slab.h"
/*
 * slob_block has a field 'units', which indicates size of block अगर +ve,
 * or offset of next block अगर -ve (in SLOB_UNITs).
 *
 * Free blocks of size 1 unit simply contain the offset of the next block.
 * Those with larger size contain their size in the first SLOB_UNIT of
 * memory, and the offset of the next मुक्त block in the second SLOB_UNIT.
 */
#अगर PAGE_SIZE <= (32767 * 2)
प्रकार s16 slobidx_t;
#अन्यथा
प्रकार s32 slobidx_t;
#पूर्ण_अगर

काष्ठा slob_block अणु
	slobidx_t units;
पूर्ण;
प्रकार काष्ठा slob_block slob_t;

/*
 * All partially मुक्त slob pages go on these lists.
 */
#घोषणा SLOB_BREAK1 256
#घोषणा SLOB_BREAK2 1024
अटल LIST_HEAD(मुक्त_slob_small);
अटल LIST_HEAD(मुक्त_slob_medium);
अटल LIST_HEAD(मुक्त_slob_large);

/*
 * slob_page_मुक्त: true क्रम pages on मुक्त_slob_pages list.
 */
अटल अंतरभूत पूर्णांक slob_page_मुक्त(काष्ठा page *sp)
अणु
	वापस PageSlobFree(sp);
पूर्ण

अटल व्योम set_slob_page_मुक्त(काष्ठा page *sp, काष्ठा list_head *list)
अणु
	list_add(&sp->slab_list, list);
	__SetPageSlobFree(sp);
पूर्ण

अटल अंतरभूत व्योम clear_slob_page_मुक्त(काष्ठा page *sp)
अणु
	list_del(&sp->slab_list);
	__ClearPageSlobFree(sp);
पूर्ण

#घोषणा SLOB_UNIT माप(slob_t)
#घोषणा SLOB_UNITS(size) DIV_ROUND_UP(size, SLOB_UNIT)

/*
 * काष्ठा slob_rcu is inserted at the tail of allocated slob blocks, which
 * were created with a SLAB_TYPESAFE_BY_RCU slab. slob_rcu is used to मुक्त
 * the block using call_rcu.
 */
काष्ठा slob_rcu अणु
	काष्ठा rcu_head head;
	पूर्णांक size;
पूर्ण;

/*
 * slob_lock protects all slob allocator काष्ठाures.
 */
अटल DEFINE_SPINLOCK(slob_lock);

/*
 * Encode the given size and next info पूर्णांकo a मुक्त slob block s.
 */
अटल व्योम set_slob(slob_t *s, slobidx_t size, slob_t *next)
अणु
	slob_t *base = (slob_t *)((अचिन्हित दीर्घ)s & PAGE_MASK);
	slobidx_t offset = next - base;

	अगर (size > 1) अणु
		s[0].units = size;
		s[1].units = offset;
	पूर्ण अन्यथा
		s[0].units = -offset;
पूर्ण

/*
 * Return the size of a slob block.
 */
अटल slobidx_t slob_units(slob_t *s)
अणु
	अगर (s->units > 0)
		वापस s->units;
	वापस 1;
पूर्ण

/*
 * Return the next मुक्त slob block poपूर्णांकer after this one.
 */
अटल slob_t *slob_next(slob_t *s)
अणु
	slob_t *base = (slob_t *)((अचिन्हित दीर्घ)s & PAGE_MASK);
	slobidx_t next;

	अगर (s[0].units < 0)
		next = -s[0].units;
	अन्यथा
		next = s[1].units;
	वापस base+next;
पूर्ण

/*
 * Returns true अगर s is the last मुक्त block in its page.
 */
अटल पूर्णांक slob_last(slob_t *s)
अणु
	वापस !((अचिन्हित दीर्घ)slob_next(s) & ~PAGE_MASK);
पूर्ण

अटल व्योम *slob_new_pages(gfp_t gfp, पूर्णांक order, पूर्णांक node)
अणु
	काष्ठा page *page;

#अगर_घोषित CONFIG_NUMA
	अगर (node != NUMA_NO_NODE)
		page = __alloc_pages_node(node, gfp, order);
	अन्यथा
#पूर्ण_अगर
		page = alloc_pages(gfp, order);

	अगर (!page)
		वापस शून्य;

	mod_node_page_state(page_pgdat(page), NR_SLAB_UNRECLAIMABLE_B,
			    PAGE_SIZE << order);
	वापस page_address(page);
पूर्ण

अटल व्योम slob_मुक्त_pages(व्योम *b, पूर्णांक order)
अणु
	काष्ठा page *sp = virt_to_page(b);

	अगर (current->reclaim_state)
		current->reclaim_state->reclaimed_slab += 1 << order;

	mod_node_page_state(page_pgdat(sp), NR_SLAB_UNRECLAIMABLE_B,
			    -(PAGE_SIZE << order));
	__मुक्त_pages(sp, order);
पूर्ण

/*
 * slob_page_alloc() - Allocate a slob block within a given slob_page sp.
 * @sp: Page to look in.
 * @size: Size of the allocation.
 * @align: Allocation alignment.
 * @align_offset: Offset in the allocated block that will be aligned.
 * @page_हटाओd_from_list: Return parameter.
 *
 * Tries to find a chunk of memory at least @size bytes big within @page.
 *
 * Return: Poपूर्णांकer to memory अगर allocated, %शून्य otherwise.  If the
 *         allocation fills up @page then the page is हटाओd from the
 *         मुक्तlist, in this हाल @page_हटाओd_from_list will be set to
 *         true (set to false otherwise).
 */
अटल व्योम *slob_page_alloc(काष्ठा page *sp, माप_प्रकार size, पूर्णांक align,
			      पूर्णांक align_offset, bool *page_हटाओd_from_list)
अणु
	slob_t *prev, *cur, *aligned = शून्य;
	पूर्णांक delta = 0, units = SLOB_UNITS(size);

	*page_हटाओd_from_list = false;
	क्रम (prev = शून्य, cur = sp->मुक्तlist; ; prev = cur, cur = slob_next(cur)) अणु
		slobidx_t avail = slob_units(cur);

		/*
		 * 'aligned' will hold the address of the slob block so that the
		 * address 'aligned'+'align_offset' is aligned according to the
		 * 'align' parameter. This is क्रम kदो_स्मृति() which prepends the
		 * allocated block with its size, so that the block itself is
		 * aligned when needed.
		 */
		अगर (align) अणु
			aligned = (slob_t *)
				(ALIGN((अचिन्हित दीर्घ)cur + align_offset, align)
				 - align_offset);
			delta = aligned - cur;
		पूर्ण
		अगर (avail >= units + delta) अणु /* room enough? */
			slob_t *next;

			अगर (delta) अणु /* need to fragment head to align? */
				next = slob_next(cur);
				set_slob(aligned, avail - delta, next);
				set_slob(cur, delta, aligned);
				prev = cur;
				cur = aligned;
				avail = slob_units(cur);
			पूर्ण

			next = slob_next(cur);
			अगर (avail == units) अणु /* exact fit? unlink. */
				अगर (prev)
					set_slob(prev, slob_units(prev), next);
				अन्यथा
					sp->मुक्तlist = next;
			पूर्ण अन्यथा अणु /* fragment */
				अगर (prev)
					set_slob(prev, slob_units(prev), cur + units);
				अन्यथा
					sp->मुक्तlist = cur + units;
				set_slob(cur + units, avail - units, next);
			पूर्ण

			sp->units -= units;
			अगर (!sp->units) अणु
				clear_slob_page_मुक्त(sp);
				*page_हटाओd_from_list = true;
			पूर्ण
			वापस cur;
		पूर्ण
		अगर (slob_last(cur))
			वापस शून्य;
	पूर्ण
पूर्ण

/*
 * slob_alloc: entry poपूर्णांक पूर्णांकo the slob allocator.
 */
अटल व्योम *slob_alloc(माप_प्रकार size, gfp_t gfp, पूर्णांक align, पूर्णांक node,
							पूर्णांक align_offset)
अणु
	काष्ठा page *sp;
	काष्ठा list_head *slob_list;
	slob_t *b = शून्य;
	अचिन्हित दीर्घ flags;
	bool _unused;

	अगर (size < SLOB_BREAK1)
		slob_list = &मुक्त_slob_small;
	अन्यथा अगर (size < SLOB_BREAK2)
		slob_list = &मुक्त_slob_medium;
	अन्यथा
		slob_list = &मुक्त_slob_large;

	spin_lock_irqsave(&slob_lock, flags);
	/* Iterate through each partially मुक्त page, try to find room */
	list_क्रम_each_entry(sp, slob_list, slab_list) अणु
		bool page_हटाओd_from_list = false;
#अगर_घोषित CONFIG_NUMA
		/*
		 * If there's a node specअगरication, search क्रम a partial
		 * page with a matching node id in the मुक्तlist.
		 */
		अगर (node != NUMA_NO_NODE && page_to_nid(sp) != node)
			जारी;
#पूर्ण_अगर
		/* Enough room on this page? */
		अगर (sp->units < SLOB_UNITS(size))
			जारी;

		b = slob_page_alloc(sp, size, align, align_offset, &page_हटाओd_from_list);
		अगर (!b)
			जारी;

		/*
		 * If slob_page_alloc() हटाओd sp from the list then we
		 * cannot call list functions on sp.  If so allocation
		 * did not fragment the page anyway so optimisation is
		 * unnecessary.
		 */
		अगर (!page_हटाओd_from_list) अणु
			/*
			 * Improve fragment distribution and reduce our average
			 * search समय by starting our next search here. (see
			 * Knuth vol 1, sec 2.5, pg 449)
			 */
			अगर (!list_is_first(&sp->slab_list, slob_list))
				list_rotate_to_front(&sp->slab_list, slob_list);
		पूर्ण
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&slob_lock, flags);

	/* Not enough space: must allocate a new page */
	अगर (!b) अणु
		b = slob_new_pages(gfp & ~__GFP_ZERO, 0, node);
		अगर (!b)
			वापस शून्य;
		sp = virt_to_page(b);
		__SetPageSlab(sp);

		spin_lock_irqsave(&slob_lock, flags);
		sp->units = SLOB_UNITS(PAGE_SIZE);
		sp->मुक्तlist = b;
		INIT_LIST_HEAD(&sp->slab_list);
		set_slob(b, SLOB_UNITS(PAGE_SIZE), b + SLOB_UNITS(PAGE_SIZE));
		set_slob_page_मुक्त(sp, slob_list);
		b = slob_page_alloc(sp, size, align, align_offset, &_unused);
		BUG_ON(!b);
		spin_unlock_irqrestore(&slob_lock, flags);
	पूर्ण
	अगर (unlikely(gfp & __GFP_ZERO))
		स_रखो(b, 0, size);
	वापस b;
पूर्ण

/*
 * slob_मुक्त: entry poपूर्णांक पूर्णांकo the slob allocator.
 */
अटल व्योम slob_मुक्त(व्योम *block, पूर्णांक size)
अणु
	काष्ठा page *sp;
	slob_t *prev, *next, *b = (slob_t *)block;
	slobidx_t units;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *slob_list;

	अगर (unlikely(ZERO_OR_शून्य_PTR(block)))
		वापस;
	BUG_ON(!size);

	sp = virt_to_page(block);
	units = SLOB_UNITS(size);

	spin_lock_irqsave(&slob_lock, flags);

	अगर (sp->units + units == SLOB_UNITS(PAGE_SIZE)) अणु
		/* Go directly to page allocator. Do not pass slob allocator */
		अगर (slob_page_मुक्त(sp))
			clear_slob_page_मुक्त(sp);
		spin_unlock_irqrestore(&slob_lock, flags);
		__ClearPageSlab(sp);
		page_mapcount_reset(sp);
		slob_मुक्त_pages(b, 0);
		वापस;
	पूर्ण

	अगर (!slob_page_मुक्त(sp)) अणु
		/* This slob page is about to become partially मुक्त. Easy! */
		sp->units = units;
		sp->मुक्तlist = b;
		set_slob(b, units,
			(व्योम *)((अचिन्हित दीर्घ)(b +
					SLOB_UNITS(PAGE_SIZE)) & PAGE_MASK));
		अगर (size < SLOB_BREAK1)
			slob_list = &मुक्त_slob_small;
		अन्यथा अगर (size < SLOB_BREAK2)
			slob_list = &मुक्त_slob_medium;
		अन्यथा
			slob_list = &मुक्त_slob_large;
		set_slob_page_मुक्त(sp, slob_list);
		जाओ out;
	पूर्ण

	/*
	 * Otherwise the page is alपढ़ोy partially मुक्त, so find reinsertion
	 * poपूर्णांक.
	 */
	sp->units += units;

	अगर (b < (slob_t *)sp->मुक्तlist) अणु
		अगर (b + units == sp->मुक्तlist) अणु
			units += slob_units(sp->मुक्तlist);
			sp->मुक्तlist = slob_next(sp->मुक्तlist);
		पूर्ण
		set_slob(b, units, sp->मुक्तlist);
		sp->मुक्तlist = b;
	पूर्ण अन्यथा अणु
		prev = sp->मुक्तlist;
		next = slob_next(prev);
		जबतक (b > next) अणु
			prev = next;
			next = slob_next(prev);
		पूर्ण

		अगर (!slob_last(prev) && b + units == next) अणु
			units += slob_units(next);
			set_slob(b, units, slob_next(next));
		पूर्ण अन्यथा
			set_slob(b, units, next);

		अगर (prev + slob_units(prev) == b) अणु
			units = slob_units(b) + slob_units(prev);
			set_slob(prev, units, slob_next(b));
		पूर्ण अन्यथा
			set_slob(prev, slob_units(prev), b);
	पूर्ण
out:
	spin_unlock_irqrestore(&slob_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PRINTK
व्योम kmem_obj_info(काष्ठा kmem_obj_info *kpp, व्योम *object, काष्ठा page *page)
अणु
	kpp->kp_ptr = object;
	kpp->kp_page = page;
पूर्ण
#पूर्ण_अगर

/*
 * End of slob allocator proper. Begin kmem_cache_alloc and kदो_स्मृति frontend.
 */

अटल __always_अंतरभूत व्योम *
__करो_kदो_स्मृति_node(माप_प्रकार size, gfp_t gfp, पूर्णांक node, अचिन्हित दीर्घ caller)
अणु
	अचिन्हित पूर्णांक *m;
	पूर्णांक minalign = max_t(माप_प्रकार, ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
	व्योम *ret;

	gfp &= gfp_allowed_mask;

	might_alloc(gfp);

	अगर (size < PAGE_SIZE - minalign) अणु
		पूर्णांक align = minalign;

		/*
		 * For घातer of two sizes, guarantee natural alignment क्रम
		 * kदो_स्मृति()'d objects.
		 */
		अगर (is_घातer_of_2(size))
			align = max(minalign, (पूर्णांक) size);

		अगर (!size)
			वापस ZERO_SIZE_PTR;

		m = slob_alloc(size + minalign, gfp, align, node, minalign);

		अगर (!m)
			वापस शून्य;
		*m = size;
		ret = (व्योम *)m + minalign;

		trace_kदो_स्मृति_node(caller, ret,
				   size, size + minalign, gfp, node);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक order = get_order(size);

		अगर (likely(order))
			gfp |= __GFP_COMP;
		ret = slob_new_pages(gfp, order, node);

		trace_kदो_स्मृति_node(caller, ret,
				   size, PAGE_SIZE << order, gfp, node);
	पूर्ण

	kmemleak_alloc(ret, size, 1, gfp);
	वापस ret;
पूर्ण

व्योम *__kदो_स्मृति(माप_प्रकार size, gfp_t gfp)
अणु
	वापस __करो_kदो_स्मृति_node(size, gfp, NUMA_NO_NODE, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति);

व्योम *__kदो_स्मृति_track_caller(माप_प्रकार size, gfp_t gfp, अचिन्हित दीर्घ caller)
अणु
	वापस __करो_kदो_स्मृति_node(size, gfp, NUMA_NO_NODE, caller);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_track_caller);

#अगर_घोषित CONFIG_NUMA
व्योम *__kदो_स्मृति_node_track_caller(माप_प्रकार size, gfp_t gfp,
					पूर्णांक node, अचिन्हित दीर्घ caller)
अणु
	वापस __करो_kदो_स्मृति_node(size, gfp, node, caller);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node_track_caller);
#पूर्ण_अगर

व्योम kमुक्त(स्थिर व्योम *block)
अणु
	काष्ठा page *sp;

	trace_kमुक्त(_RET_IP_, block);

	अगर (unlikely(ZERO_OR_शून्य_PTR(block)))
		वापस;
	kmemleak_मुक्त(block);

	sp = virt_to_page(block);
	अगर (PageSlab(sp)) अणु
		पूर्णांक align = max_t(माप_प्रकार, ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
		अचिन्हित पूर्णांक *m = (अचिन्हित पूर्णांक *)(block - align);
		slob_मुक्त(m, *m + align);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक order = compound_order(sp);
		mod_node_page_state(page_pgdat(sp), NR_SLAB_UNRECLAIMABLE_B,
				    -(PAGE_SIZE << order));
		__मुक्त_pages(sp, order);

	पूर्ण
पूर्ण
EXPORT_SYMBOL(kमुक्त);

/* can't use ksize क्रम kmem_cache_alloc memory, only kदो_स्मृति */
माप_प्रकार __ksize(स्थिर व्योम *block)
अणु
	काष्ठा page *sp;
	पूर्णांक align;
	अचिन्हित पूर्णांक *m;

	BUG_ON(!block);
	अगर (unlikely(block == ZERO_SIZE_PTR))
		वापस 0;

	sp = virt_to_page(block);
	अगर (unlikely(!PageSlab(sp)))
		वापस page_size(sp);

	align = max_t(माप_प्रकार, ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
	m = (अचिन्हित पूर्णांक *)(block - align);
	वापस SLOB_UNITS(*m) * SLOB_UNIT;
पूर्ण
EXPORT_SYMBOL(__ksize);

पूर्णांक __kmem_cache_create(काष्ठा kmem_cache *c, slab_flags_t flags)
अणु
	अगर (flags & SLAB_TYPESAFE_BY_RCU) अणु
		/* leave room क्रम rcu footer at the end of object */
		c->size += माप(काष्ठा slob_rcu);
	पूर्ण
	c->flags = flags;
	वापस 0;
पूर्ण

अटल व्योम *slob_alloc_node(काष्ठा kmem_cache *c, gfp_t flags, पूर्णांक node)
अणु
	व्योम *b;

	flags &= gfp_allowed_mask;

	might_alloc(flags);

	अगर (c->size < PAGE_SIZE) अणु
		b = slob_alloc(c->size, flags, c->align, node, 0);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->object_size,
					    SLOB_UNITS(c->size) * SLOB_UNIT,
					    flags, node);
	पूर्ण अन्यथा अणु
		b = slob_new_pages(flags, get_order(c->size), node);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->object_size,
					    PAGE_SIZE << get_order(c->size),
					    flags, node);
	पूर्ण

	अगर (b && c->ctor) अणु
		WARN_ON_ONCE(flags & __GFP_ZERO);
		c->ctor(b);
	पूर्ण

	kmemleak_alloc_recursive(b, c->size, 1, c->flags, flags);
	वापस b;
पूर्ण

व्योम *kmem_cache_alloc(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	वापस slob_alloc_node(cachep, flags, NUMA_NO_NODE);
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc);

#अगर_घोषित CONFIG_NUMA
व्योम *__kदो_स्मृति_node(माप_प्रकार size, gfp_t gfp, पूर्णांक node)
अणु
	वापस __करो_kदो_स्मृति_node(size, gfp, node, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node);

व्योम *kmem_cache_alloc_node(काष्ठा kmem_cache *cachep, gfp_t gfp, पूर्णांक node)
अणु
	वापस slob_alloc_node(cachep, gfp, node);
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_node);
#पूर्ण_अगर

अटल व्योम __kmem_cache_मुक्त(व्योम *b, पूर्णांक size)
अणु
	अगर (size < PAGE_SIZE)
		slob_मुक्त(b, size);
	अन्यथा
		slob_मुक्त_pages(b, get_order(size));
पूर्ण

अटल व्योम kmem_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा slob_rcu *slob_rcu = (काष्ठा slob_rcu *)head;
	व्योम *b = (व्योम *)slob_rcu - (slob_rcu->size - माप(काष्ठा slob_rcu));

	__kmem_cache_मुक्त(b, slob_rcu->size);
पूर्ण

व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *c, व्योम *b)
अणु
	kmemleak_मुक्त_recursive(b, c->flags);
	अगर (unlikely(c->flags & SLAB_TYPESAFE_BY_RCU)) अणु
		काष्ठा slob_rcu *slob_rcu;
		slob_rcu = b + (c->size - माप(काष्ठा slob_rcu));
		slob_rcu->size = c->size;
		call_rcu(&slob_rcu->head, kmem_rcu_मुक्त);
	पूर्ण अन्यथा अणु
		__kmem_cache_मुक्त(b, c->size);
	पूर्ण

	trace_kmem_cache_मुक्त(_RET_IP_, b, c->name);
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त);

व्योम kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *s, माप_प्रकार size, व्योम **p)
अणु
	__kmem_cache_मुक्त_bulk(s, size, p);
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त_bulk);

पूर्णांक kmem_cache_alloc_bulk(काष्ठा kmem_cache *s, gfp_t flags, माप_प्रकार size,
								व्योम **p)
अणु
	वापस __kmem_cache_alloc_bulk(s, flags, size, p);
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_bulk);

पूर्णांक __kmem_cache_shutकरोwn(काष्ठा kmem_cache *c)
अणु
	/* No way to check क्रम reमुख्यing objects */
	वापस 0;
पूर्ण

व्योम __kmem_cache_release(काष्ठा kmem_cache *c)
अणु
पूर्ण

पूर्णांक __kmem_cache_shrink(काष्ठा kmem_cache *d)
अणु
	वापस 0;
पूर्ण

काष्ठा kmem_cache kmem_cache_boot = अणु
	.name = "kmem_cache",
	.size = माप(काष्ठा kmem_cache),
	.flags = SLAB_PANIC,
	.align = ARCH_KMALLOC_MINALIGN,
पूर्ण;

व्योम __init kmem_cache_init(व्योम)
अणु
	kmem_cache = &kmem_cache_boot;
	slab_state = UP;
पूर्ण

व्योम __init kmem_cache_init_late(व्योम)
अणु
	slab_state = FULL;
पूर्ण
