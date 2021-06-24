<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश <linux/backing-dev.h>

#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"

अटल kmem_zone_t *xfs_buf_zone;

#घोषणा xb_to_gfp(flags) \
	((((flags) & XBF_READ_AHEAD) ? __GFP_NORETRY : GFP_NOFS) | __GFP_NOWARN)

/*
 * Locking orders
 *
 * xfs_buf_ioacct_inc:
 * xfs_buf_ioacct_dec:
 *	b_sema (caller holds)
 *	  b_lock
 *
 * xfs_buf_stale:
 *	b_sema (caller holds)
 *	  b_lock
 *	    lru_lock
 *
 * xfs_buf_rele:
 *	b_lock
 *	  pag_buf_lock
 *	    lru_lock
 *
 * xfs_buftarg_drain_rele
 *	lru_lock
 *	  b_lock (trylock due to inversion)
 *
 * xfs_buftarg_isolate
 *	lru_lock
 *	  b_lock (trylock due to inversion)
 */

अटल पूर्णांक __xfs_buf_submit(काष्ठा xfs_buf *bp, bool रुको);

अटल अंतरभूत पूर्णांक
xfs_buf_submit(
	काष्ठा xfs_buf		*bp)
अणु
	वापस __xfs_buf_submit(bp, !(bp->b_flags & XBF_ASYNC));
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_buf_is_vmapped(
	काष्ठा xfs_buf	*bp)
अणु
	/*
	 * Return true अगर the buffer is vmapped.
	 *
	 * b_addr is null अगर the buffer is not mapped, but the code is clever
	 * enough to know it करोesn't have to map a single page, so the check has
	 * to be both क्रम b_addr and bp->b_page_count > 1.
	 */
	वापस bp->b_addr && bp->b_page_count > 1;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_buf_vmap_len(
	काष्ठा xfs_buf	*bp)
अणु
	वापस (bp->b_page_count * PAGE_SIZE) - bp->b_offset;
पूर्ण

/*
 * Bump the I/O in flight count on the buftarg अगर we haven't yet करोne so क्रम
 * this buffer. The count is incremented once per buffer (per hold cycle)
 * because the corresponding decrement is deferred to buffer release. Buffers
 * can undergo I/O multiple बार in a hold-release cycle and per buffer I/O
 * tracking adds unnecessary overhead. This is used क्रम sychronization purposes
 * with unmount (see xfs_buftarg_drain()), so all we really need is a count of
 * in-flight buffers.
 *
 * Buffers that are never released (e.g., superblock, iclog buffers) must set
 * the XBF_NO_IOACCT flag beक्रमe I/O submission. Otherwise, the buftarg count
 * never reaches zero and unmount hangs indefinitely.
 */
अटल अंतरभूत व्योम
xfs_buf_ioacct_inc(
	काष्ठा xfs_buf	*bp)
अणु
	अगर (bp->b_flags & XBF_NO_IOACCT)
		वापस;

	ASSERT(bp->b_flags & XBF_ASYNC);
	spin_lock(&bp->b_lock);
	अगर (!(bp->b_state & XFS_BSTATE_IN_FLIGHT)) अणु
		bp->b_state |= XFS_BSTATE_IN_FLIGHT;
		percpu_counter_inc(&bp->b_target->bt_io_count);
	पूर्ण
	spin_unlock(&bp->b_lock);
पूर्ण

/*
 * Clear the in-flight state on a buffer about to be released to the LRU or
 * मुक्तd and unaccount from the buftarg.
 */
अटल अंतरभूत व्योम
__xfs_buf_ioacct_dec(
	काष्ठा xfs_buf	*bp)
अणु
	lockdep_निश्चित_held(&bp->b_lock);

	अगर (bp->b_state & XFS_BSTATE_IN_FLIGHT) अणु
		bp->b_state &= ~XFS_BSTATE_IN_FLIGHT;
		percpu_counter_dec(&bp->b_target->bt_io_count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
xfs_buf_ioacct_dec(
	काष्ठा xfs_buf	*bp)
अणु
	spin_lock(&bp->b_lock);
	__xfs_buf_ioacct_dec(bp);
	spin_unlock(&bp->b_lock);
पूर्ण

/*
 * When we mark a buffer stale, we हटाओ the buffer from the LRU and clear the
 * b_lru_ref count so that the buffer is मुक्तd immediately when the buffer
 * reference count falls to zero. If the buffer is alपढ़ोy on the LRU, we need
 * to हटाओ the reference that LRU holds on the buffer.
 *
 * This prevents build-up of stale buffers on the LRU.
 */
व्योम
xfs_buf_stale(
	काष्ठा xfs_buf	*bp)
अणु
	ASSERT(xfs_buf_islocked(bp));

	bp->b_flags |= XBF_STALE;

	/*
	 * Clear the delwri status so that a delwri queue walker will not
	 * flush this buffer to disk now that it is stale. The delwri queue has
	 * a reference to the buffer, so this is safe to करो.
	 */
	bp->b_flags &= ~_XBF_DELWRI_Q;

	/*
	 * Once the buffer is marked stale and unlocked, a subsequent lookup
	 * could reset b_flags. There is no guarantee that the buffer is
	 * unaccounted (released to LRU) beक्रमe that occurs. Drop in-flight
	 * status now to preserve accounting consistency.
	 */
	spin_lock(&bp->b_lock);
	__xfs_buf_ioacct_dec(bp);

	atomic_set(&bp->b_lru_ref, 0);
	अगर (!(bp->b_state & XFS_BSTATE_DISPOSE) &&
	    (list_lru_del(&bp->b_target->bt_lru, &bp->b_lru)))
		atomic_dec(&bp->b_hold);

	ASSERT(atomic_पढ़ो(&bp->b_hold) >= 1);
	spin_unlock(&bp->b_lock);
पूर्ण

अटल पूर्णांक
xfs_buf_get_maps(
	काष्ठा xfs_buf		*bp,
	पूर्णांक			map_count)
अणु
	ASSERT(bp->b_maps == शून्य);
	bp->b_map_count = map_count;

	अगर (map_count == 1) अणु
		bp->b_maps = &bp->__b_map;
		वापस 0;
	पूर्ण

	bp->b_maps = kmem_zalloc(map_count * माप(काष्ठा xfs_buf_map),
				KM_NOFS);
	अगर (!bp->b_maps)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 *	Frees b_pages अगर it was allocated.
 */
अटल व्योम
xfs_buf_मुक्त_maps(
	काष्ठा xfs_buf	*bp)
अणु
	अगर (bp->b_maps != &bp->__b_map) अणु
		kmem_मुक्त(bp->b_maps);
		bp->b_maps = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
_xfs_buf_alloc(
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	पूर्णांक			i;

	*bpp = शून्य;
	bp = kmem_cache_zalloc(xfs_buf_zone, GFP_NOFS | __GFP_NOFAIL);

	/*
	 * We करोn't want certain flags to appear in b_flags unless they are
	 * specअगरically set by later operations on the buffer.
	 */
	flags &= ~(XBF_UNMAPPED | XBF_TRYLOCK | XBF_ASYNC | XBF_READ_AHEAD);

	atomic_set(&bp->b_hold, 1);
	atomic_set(&bp->b_lru_ref, 1);
	init_completion(&bp->b_ioरुको);
	INIT_LIST_HEAD(&bp->b_lru);
	INIT_LIST_HEAD(&bp->b_list);
	INIT_LIST_HEAD(&bp->b_li_list);
	sema_init(&bp->b_sema, 0); /* held, no रुकोers */
	spin_lock_init(&bp->b_lock);
	bp->b_target = target;
	bp->b_mount = target->bt_mount;
	bp->b_flags = flags;

	/*
	 * Set length and io_length to the same value initially.
	 * I/O routines should use io_length, which will be the same in
	 * most हालs but may be reset (e.g. XFS recovery).
	 */
	error = xfs_buf_get_maps(bp, nmaps);
	अगर (error)  अणु
		kmem_cache_मुक्त(xfs_buf_zone, bp);
		वापस error;
	पूर्ण

	bp->b_bn = map[0].bm_bn;
	bp->b_length = 0;
	क्रम (i = 0; i < nmaps; i++) अणु
		bp->b_maps[i].bm_bn = map[i].bm_bn;
		bp->b_maps[i].bm_len = map[i].bm_len;
		bp->b_length += map[i].bm_len;
	पूर्ण

	atomic_set(&bp->b_pin_count, 0);
	init_रुकोqueue_head(&bp->b_रुकोers);

	XFS_STATS_INC(bp->b_mount, xb_create);
	trace_xfs_buf_init(bp, _RET_IP_);

	*bpp = bp;
	वापस 0;
पूर्ण

/*
 *	Allocate a page array capable of holding a specअगरied number
 *	of pages, and poपूर्णांक the page buf at it.
 */
STATIC पूर्णांक
_xfs_buf_get_pages(
	काष्ठा xfs_buf		*bp,
	पूर्णांक			page_count)
अणु
	/* Make sure that we have a page list */
	अगर (bp->b_pages == शून्य) अणु
		bp->b_page_count = page_count;
		अगर (page_count <= XB_PAGES) अणु
			bp->b_pages = bp->b_page_array;
		पूर्ण अन्यथा अणु
			bp->b_pages = kmem_alloc(माप(काष्ठा page *) *
						 page_count, KM_NOFS);
			अगर (bp->b_pages == शून्य)
				वापस -ENOMEM;
		पूर्ण
		स_रखो(bp->b_pages, 0, माप(काष्ठा page *) * page_count);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Frees b_pages अगर it was allocated.
 */
STATIC व्योम
_xfs_buf_मुक्त_pages(
	काष्ठा xfs_buf	*bp)
अणु
	अगर (bp->b_pages != bp->b_page_array) अणु
		kmem_मुक्त(bp->b_pages);
		bp->b_pages = शून्य;
	पूर्ण
पूर्ण

/*
 *	Releases the specअगरied buffer.
 *
 * 	The modअगरication state of any associated pages is left unchanged.
 * 	The buffer must not be on any hash - use xfs_buf_rele instead क्रम
 * 	hashed and refcounted buffers
 */
अटल व्योम
xfs_buf_मुक्त(
	काष्ठा xfs_buf		*bp)
अणु
	trace_xfs_buf_मुक्त(bp, _RET_IP_);

	ASSERT(list_empty(&bp->b_lru));

	अगर (bp->b_flags & _XBF_PAGES) अणु
		uपूर्णांक		i;

		अगर (xfs_buf_is_vmapped(bp))
			vm_unmap_ram(bp->b_addr - bp->b_offset,
					bp->b_page_count);

		क्रम (i = 0; i < bp->b_page_count; i++) अणु
			काष्ठा page	*page = bp->b_pages[i];

			__मुक्त_page(page);
		पूर्ण
		अगर (current->reclaim_state)
			current->reclaim_state->reclaimed_slab +=
							bp->b_page_count;
	पूर्ण अन्यथा अगर (bp->b_flags & _XBF_KMEM)
		kmem_मुक्त(bp->b_addr);
	_xfs_buf_मुक्त_pages(bp);
	xfs_buf_मुक्त_maps(bp);
	kmem_cache_मुक्त(xfs_buf_zone, bp);
पूर्ण

/*
 * Allocates all the pages क्रम buffer in question and builds it's page list.
 */
STATIC पूर्णांक
xfs_buf_allocate_memory(
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			flags)
अणु
	माप_प्रकार			size;
	माप_प्रकार			nbytes, offset;
	gfp_t			gfp_mask = xb_to_gfp(flags);
	अचिन्हित लघु		page_count, i;
	xfs_off_t		start, end;
	पूर्णांक			error;
	xfs_km_flags_t		kmflag_mask = 0;

	/*
	 * assure zeroed buffer क्रम non-पढ़ो हालs.
	 */
	अगर (!(flags & XBF_READ)) अणु
		kmflag_mask |= KM_ZERO;
		gfp_mask |= __GFP_ZERO;
	पूर्ण

	/*
	 * क्रम buffers that are contained within a single page, just allocate
	 * the memory from the heap - there's no need क्रम the complनिकासy of
	 * page arrays to keep allocation करोwn to order 0.
	 */
	size = BBTOB(bp->b_length);
	अगर (size < PAGE_SIZE) अणु
		पूर्णांक align_mask = xfs_buftarg_dma_alignment(bp->b_target);
		bp->b_addr = kmem_alloc_io(size, align_mask,
					   KM_NOFS | kmflag_mask);
		अगर (!bp->b_addr) अणु
			/* low memory - use alloc_page loop instead */
			जाओ use_alloc_page;
		पूर्ण

		अगर (((अचिन्हित दीर्घ)(bp->b_addr + size - 1) & PAGE_MASK) !=
		    ((अचिन्हित दीर्घ)bp->b_addr & PAGE_MASK)) अणु
			/* b_addr spans two pages - use alloc_page instead */
			kmem_मुक्त(bp->b_addr);
			bp->b_addr = शून्य;
			जाओ use_alloc_page;
		पूर्ण
		bp->b_offset = offset_in_page(bp->b_addr);
		bp->b_pages = bp->b_page_array;
		bp->b_pages[0] = kmem_to_page(bp->b_addr);
		bp->b_page_count = 1;
		bp->b_flags |= _XBF_KMEM;
		वापस 0;
	पूर्ण

use_alloc_page:
	start = BBTOB(bp->b_maps[0].bm_bn) >> PAGE_SHIFT;
	end = (BBTOB(bp->b_maps[0].bm_bn + bp->b_length) + PAGE_SIZE - 1)
								>> PAGE_SHIFT;
	page_count = end - start;
	error = _xfs_buf_get_pages(bp, page_count);
	अगर (unlikely(error))
		वापस error;

	offset = bp->b_offset;
	bp->b_flags |= _XBF_PAGES;

	क्रम (i = 0; i < bp->b_page_count; i++) अणु
		काष्ठा page	*page;
		uपूर्णांक		retries = 0;
retry:
		page = alloc_page(gfp_mask);
		अगर (unlikely(page == शून्य)) अणु
			अगर (flags & XBF_READ_AHEAD) अणु
				bp->b_page_count = i;
				error = -ENOMEM;
				जाओ out_मुक्त_pages;
			पूर्ण

			/*
			 * This could deadlock.
			 *
			 * But until all the XFS lowlevel code is revamped to
			 * handle buffer allocation failures we can't करो much.
			 */
			अगर (!(++retries % 100))
				xfs_err(शून्य,
		"%s(%u) possible memory allocation deadlock in %s (mode:0x%x)",
					current->comm, current->pid,
					__func__, gfp_mask);

			XFS_STATS_INC(bp->b_mount, xb_page_retries);
			congestion_रुको(BLK_RW_ASYNC, HZ/50);
			जाओ retry;
		पूर्ण

		XFS_STATS_INC(bp->b_mount, xb_page_found);

		nbytes = min_t(माप_प्रकार, size, PAGE_SIZE - offset);
		size -= nbytes;
		bp->b_pages[i] = page;
		offset = 0;
	पूर्ण
	वापस 0;

out_मुक्त_pages:
	क्रम (i = 0; i < bp->b_page_count; i++)
		__मुक्त_page(bp->b_pages[i]);
	bp->b_flags &= ~_XBF_PAGES;
	वापस error;
पूर्ण

/*
 *	Map buffer पूर्णांकo kernel address-space अगर necessary.
 */
STATIC पूर्णांक
_xfs_buf_map_pages(
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			flags)
अणु
	ASSERT(bp->b_flags & _XBF_PAGES);
	अगर (bp->b_page_count == 1) अणु
		/* A single page buffer is always mappable */
		bp->b_addr = page_address(bp->b_pages[0]) + bp->b_offset;
	पूर्ण अन्यथा अगर (flags & XBF_UNMAPPED) अणु
		bp->b_addr = शून्य;
	पूर्ण अन्यथा अणु
		पूर्णांक retried = 0;
		अचिन्हित nofs_flag;

		/*
		 * vm_map_ram() will allocate auxiliary काष्ठाures (e.g.
		 * pagetables) with GFP_KERNEL, yet we are likely to be under
		 * GFP_NOFS context here. Hence we need to tell memory reclaim
		 * that we are in such a context via PF_MEMALLOC_NOFS to prevent
		 * memory reclaim re-entering the fileप्रणाली here and
		 * potentially deadlocking.
		 */
		nofs_flag = meदो_स्मृति_nofs_save();
		करो अणु
			bp->b_addr = vm_map_ram(bp->b_pages, bp->b_page_count,
						-1);
			अगर (bp->b_addr)
				अवरोध;
			vm_unmap_aliases();
		पूर्ण जबतक (retried++ <= 1);
		meदो_स्मृति_nofs_restore(nofs_flag);

		अगर (!bp->b_addr)
			वापस -ENOMEM;
		bp->b_addr += bp->b_offset;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Finding and Reading Buffers
 */
अटल पूर्णांक
_xfs_buf_obj_cmp(
	काष्ठा rhashtable_compare_arg	*arg,
	स्थिर व्योम			*obj)
अणु
	स्थिर काष्ठा xfs_buf_map	*map = arg->key;
	स्थिर काष्ठा xfs_buf		*bp = obj;

	/*
	 * The key hashing in the lookup path depends on the key being the
	 * first element of the compare_arg, make sure to निश्चित this.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा xfs_buf_map, bm_bn) != 0);

	अगर (bp->b_bn != map->bm_bn)
		वापस 1;

	अगर (unlikely(bp->b_length != map->bm_len)) अणु
		/*
		 * found a block number match. If the range करोesn't
		 * match, the only way this is allowed is अगर the buffer
		 * in the cache is stale and the transaction that made
		 * it stale has not yet committed. i.e. we are
		 * पुनः_स्मृतिating a busy extent. Skip this buffer and
		 * जारी searching क्रम an exact match.
		 */
		ASSERT(bp->b_flags & XBF_STALE);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params xfs_buf_hash_params = अणु
	.min_size		= 32,	/* empty AGs have minimal footprपूर्णांक */
	.nelem_hपूर्णांक		= 16,
	.key_len		= माप(xfs_daddr_t),
	.key_offset		= दुरत्व(काष्ठा xfs_buf, b_bn),
	.head_offset		= दुरत्व(काष्ठा xfs_buf, b_rhash_head),
	.स्वतःmatic_shrinking	= true,
	.obj_cmpfn		= _xfs_buf_obj_cmp,
पूर्ण;

पूर्णांक
xfs_buf_hash_init(
	काष्ठा xfs_perag	*pag)
अणु
	spin_lock_init(&pag->pag_buf_lock);
	वापस rhashtable_init(&pag->pag_buf_hash, &xfs_buf_hash_params);
पूर्ण

व्योम
xfs_buf_hash_destroy(
	काष्ठा xfs_perag	*pag)
अणु
	rhashtable_destroy(&pag->pag_buf_hash);
पूर्ण

/*
 * Look up a buffer in the buffer cache and वापस it referenced and locked
 * in @found_bp.
 *
 * If @new_bp is supplied and we have a lookup miss, insert @new_bp पूर्णांकo the
 * cache.
 *
 * If XBF_TRYLOCK is set in @flags, only try to lock the buffer and वापस
 * -EAGAIN अगर we fail to lock it.
 *
 * Return values are:
 *	-EFSCORRUPTED अगर have been supplied with an invalid address
 *	-EAGAIN on trylock failure
 *	-ENOENT अगर we fail to find a match and @new_bp was शून्य
 *	0, with @found_bp:
 *		- @new_bp अगर we inserted it पूर्णांकo the cache
 *		- the buffer we found and locked.
 */
अटल पूर्णांक
xfs_buf_find(
	काष्ठा xfs_buftarg	*btp,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		*new_bp,
	काष्ठा xfs_buf		**found_bp)
अणु
	काष्ठा xfs_perag	*pag;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_buf_map	cmap = अणु .bm_bn = map[0].bm_bn पूर्ण;
	xfs_daddr_t		eofs;
	पूर्णांक			i;

	*found_bp = शून्य;

	क्रम (i = 0; i < nmaps; i++)
		cmap.bm_len += map[i].bm_len;

	/* Check क्रम IOs smaller than the sector size / not sector aligned */
	ASSERT(!(BBTOB(cmap.bm_len) < btp->bt_meta_sectorsize));
	ASSERT(!(BBTOB(cmap.bm_bn) & (xfs_off_t)btp->bt_meta_sectormask));

	/*
	 * Corrupted block numbers can get through to here, unक्रमtunately, so we
	 * have to check that the buffer falls within the fileप्रणाली bounds.
	 */
	eofs = XFS_FSB_TO_BB(btp->bt_mount, btp->bt_mount->m_sb.sb_dblocks);
	अगर (cmap.bm_bn < 0 || cmap.bm_bn >= eofs) अणु
		xfs_alert(btp->bt_mount,
			  "%s: daddr 0x%llx out of range, EOFS 0x%llx",
			  __func__, cmap.bm_bn, eofs);
		WARN_ON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	pag = xfs_perag_get(btp->bt_mount,
			    xfs_daddr_to_agno(btp->bt_mount, cmap.bm_bn));

	spin_lock(&pag->pag_buf_lock);
	bp = rhashtable_lookup_fast(&pag->pag_buf_hash, &cmap,
				    xfs_buf_hash_params);
	अगर (bp) अणु
		atomic_inc(&bp->b_hold);
		जाओ found;
	पूर्ण

	/* No match found */
	अगर (!new_bp) अणु
		XFS_STATS_INC(btp->bt_mount, xb_miss_locked);
		spin_unlock(&pag->pag_buf_lock);
		xfs_perag_put(pag);
		वापस -ENOENT;
	पूर्ण

	/* the buffer keeps the perag reference until it is मुक्तd */
	new_bp->b_pag = pag;
	rhashtable_insert_fast(&pag->pag_buf_hash, &new_bp->b_rhash_head,
			       xfs_buf_hash_params);
	spin_unlock(&pag->pag_buf_lock);
	*found_bp = new_bp;
	वापस 0;

found:
	spin_unlock(&pag->pag_buf_lock);
	xfs_perag_put(pag);

	अगर (!xfs_buf_trylock(bp)) अणु
		अगर (flags & XBF_TRYLOCK) अणु
			xfs_buf_rele(bp);
			XFS_STATS_INC(btp->bt_mount, xb_busy_locked);
			वापस -EAGAIN;
		पूर्ण
		xfs_buf_lock(bp);
		XFS_STATS_INC(btp->bt_mount, xb_get_locked_रुकोed);
	पूर्ण

	/*
	 * अगर the buffer is stale, clear all the बाह्यal state associated with
	 * it. We need to keep flags such as how we allocated the buffer memory
	 * पूर्णांकact here.
	 */
	अगर (bp->b_flags & XBF_STALE) अणु
		ASSERT((bp->b_flags & _XBF_DELWRI_Q) == 0);
		bp->b_flags &= _XBF_KMEM | _XBF_PAGES;
		bp->b_ops = शून्य;
	पूर्ण

	trace_xfs_buf_find(bp, flags, _RET_IP_);
	XFS_STATS_INC(btp->bt_mount, xb_get_locked);
	*found_bp = bp;
	वापस 0;
पूर्ण

काष्ठा xfs_buf *
xfs_buf_incore(
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	माप_प्रकार			numblks,
	xfs_buf_flags_t		flags)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);

	error = xfs_buf_find(target, &map, 1, flags, शून्य, &bp);
	अगर (error)
		वापस शून्य;
	वापस bp;
पूर्ण

/*
 * Assembles a buffer covering the specअगरied range. The code is optimised क्रम
 * cache hits, as metadata पूर्णांकensive workloads will see 3 orders of magnitude
 * more hits than misses.
 */
पूर्णांक
xfs_buf_get_map(
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_buf		*new_bp;
	पूर्णांक			error = 0;

	*bpp = शून्य;
	error = xfs_buf_find(target, map, nmaps, flags, शून्य, &bp);
	अगर (!error)
		जाओ found;
	अगर (error != -ENOENT)
		वापस error;

	error = _xfs_buf_alloc(target, map, nmaps, flags, &new_bp);
	अगर (error)
		वापस error;

	error = xfs_buf_allocate_memory(new_bp, flags);
	अगर (error) अणु
		xfs_buf_मुक्त(new_bp);
		वापस error;
	पूर्ण

	error = xfs_buf_find(target, map, nmaps, flags, new_bp, &bp);
	अगर (error) अणु
		xfs_buf_मुक्त(new_bp);
		वापस error;
	पूर्ण

	अगर (bp != new_bp)
		xfs_buf_मुक्त(new_bp);

found:
	अगर (!bp->b_addr) अणु
		error = _xfs_buf_map_pages(bp, flags);
		अगर (unlikely(error)) अणु
			xfs_warn_ratelimited(target->bt_mount,
				"%s: failed to map %u pages", __func__,
				bp->b_page_count);
			xfs_buf_rअन्यथा(bp);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Clear b_error अगर this is a lookup from a caller that करोesn't expect
	 * valid data to be found in the buffer.
	 */
	अगर (!(flags & XBF_READ))
		xfs_buf_ioerror(bp, 0);

	XFS_STATS_INC(target->bt_mount, xb_get);
	trace_xfs_buf_get(bp, flags, _RET_IP_);
	*bpp = bp;
	वापस 0;
पूर्ण

पूर्णांक
_xfs_buf_पढ़ो(
	काष्ठा xfs_buf		*bp,
	xfs_buf_flags_t		flags)
अणु
	ASSERT(!(flags & XBF_WRITE));
	ASSERT(bp->b_maps[0].bm_bn != XFS_BUF_DADDR_शून्य);

	bp->b_flags &= ~(XBF_WRITE | XBF_ASYNC | XBF_READ_AHEAD | XBF_DONE);
	bp->b_flags |= flags & (XBF_READ | XBF_ASYNC | XBF_READ_AHEAD);

	वापस xfs_buf_submit(bp);
पूर्ण

/*
 * Reverअगरy a buffer found in cache without an attached ->b_ops.
 *
 * If the caller passed an ops काष्ठाure and the buffer करोesn't have ops
 * asचिन्हित, set the ops and use it to verअगरy the contents. If verअगरication
 * fails, clear XBF_DONE. We assume the buffer has no recorded errors and is
 * alपढ़ोy in XBF_DONE state on entry.
 *
 * Under normal operations, every in-core buffer is verअगरied on पढ़ो I/O
 * completion. There are two scenarios that can lead to in-core buffers without
 * an asचिन्हित ->b_ops. The first is during log recovery of buffers on a V4
 * fileप्रणाली, though these buffers are purged at the end of recovery. The
 * other is online repair, which पूर्णांकentionally पढ़ोs with a शून्य buffer ops to
 * run several verअगरiers across an in-core buffer in order to establish buffer
 * type.  If repair can't establish that, the buffer will be left in memory
 * with शून्य buffer ops.
 */
पूर्णांक
xfs_buf_reverअगरy(
	काष्ठा xfs_buf		*bp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	ASSERT(bp->b_flags & XBF_DONE);
	ASSERT(bp->b_error == 0);

	अगर (!ops || bp->b_ops)
		वापस 0;

	bp->b_ops = ops;
	bp->b_ops->verअगरy_पढ़ो(bp);
	अगर (bp->b_error)
		bp->b_flags &= ~XBF_DONE;
	वापस bp->b_error;
पूर्ण

पूर्णांक
xfs_buf_पढ़ो_map(
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops,
	xfs_failaddr_t		fa)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	flags |= XBF_READ;
	*bpp = शून्य;

	error = xfs_buf_get_map(target, map, nmaps, flags, &bp);
	अगर (error)
		वापस error;

	trace_xfs_buf_पढ़ो(bp, flags, _RET_IP_);

	अगर (!(bp->b_flags & XBF_DONE)) अणु
		/* Initiate the buffer पढ़ो and रुको. */
		XFS_STATS_INC(target->bt_mount, xb_get_पढ़ो);
		bp->b_ops = ops;
		error = _xfs_buf_पढ़ो(bp, flags);

		/* Readahead ioकरोne alपढ़ोy dropped the buffer, so निकास. */
		अगर (flags & XBF_ASYNC)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Buffer alपढ़ोy पढ़ो; all we need to करो is check it. */
		error = xfs_buf_reverअगरy(bp, ops);

		/* Readahead alपढ़ोy finished; drop the buffer and निकास. */
		अगर (flags & XBF_ASYNC) अणु
			xfs_buf_rअन्यथा(bp);
			वापस 0;
		पूर्ण

		/* We करो not want पढ़ो in the flags */
		bp->b_flags &= ~XBF_READ;
		ASSERT(bp->b_ops != शून्य || ops == शून्य);
	पूर्ण

	/*
	 * If we've had a पढ़ो error, then the contents of the buffer are
	 * invalid and should not be used. To ensure that a followup पढ़ो tries
	 * to pull the buffer from disk again, we clear the XBF_DONE flag and
	 * mark the buffer stale. This ensures that anyone who has a current
	 * reference to the buffer will पूर्णांकerpret it's contents correctly and
	 * future cache lookups will also treat it as an empty, uninitialised
	 * buffer.
	 */
	अगर (error) अणु
		अगर (!XFS_FORCED_SHUTDOWN(target->bt_mount))
			xfs_buf_ioerror_alert(bp, fa);

		bp->b_flags &= ~XBF_DONE;
		xfs_buf_stale(bp);
		xfs_buf_rअन्यथा(bp);

		/* bad CRC means corrupted metadata */
		अगर (error == -EFSBADCRC)
			error = -EFSCORRUPTED;
		वापस error;
	पूर्ण

	*bpp = bp;
	वापस 0;
पूर्ण

/*
 *	If we are not low on memory then करो the पढ़ोahead in a deadlock
 *	safe manner.
 */
व्योम
xfs_buf_पढ़ोahead_map(
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp;

	अगर (bdi_पढ़ो_congested(target->bt_bdev->bd_bdi))
		वापस;

	xfs_buf_पढ़ो_map(target, map, nmaps,
		     XBF_TRYLOCK | XBF_ASYNC | XBF_READ_AHEAD, &bp, ops,
		     __this_address);
पूर्ण

/*
 * Read an uncached buffer from disk. Allocates and वापसs a locked
 * buffer containing the disk contents or nothing.
 */
पूर्णांक
xfs_buf_पढ़ो_uncached(
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		daddr,
	माप_प्रकार			numblks,
	पूर्णांक			flags,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	*bpp = शून्य;

	error = xfs_buf_get_uncached(target, numblks, flags, &bp);
	अगर (error)
		वापस error;

	/* set up the buffer क्रम a पढ़ो IO */
	ASSERT(bp->b_map_count == 1);
	bp->b_bn = XFS_BUF_DADDR_शून्य;  /* always null क्रम uncached buffers */
	bp->b_maps[0].bm_bn = daddr;
	bp->b_flags |= XBF_READ;
	bp->b_ops = ops;

	xfs_buf_submit(bp);
	अगर (bp->b_error) अणु
		error = bp->b_error;
		xfs_buf_rअन्यथा(bp);
		वापस error;
	पूर्ण

	*bpp = bp;
	वापस 0;
पूर्ण

पूर्णांक
xfs_buf_get_uncached(
	काष्ठा xfs_buftarg	*target,
	माप_प्रकार			numblks,
	पूर्णांक			flags,
	काष्ठा xfs_buf		**bpp)
अणु
	अचिन्हित दीर्घ		page_count;
	पूर्णांक			error, i;
	काष्ठा xfs_buf		*bp;
	DEFINE_SINGLE_BUF_MAP(map, XFS_BUF_DADDR_शून्य, numblks);

	*bpp = शून्य;

	/* flags might contain irrelevant bits, pass only what we care about */
	error = _xfs_buf_alloc(target, &map, 1, flags & XBF_NO_IOACCT, &bp);
	अगर (error)
		जाओ fail;

	page_count = PAGE_ALIGN(numblks << BBSHIFT) >> PAGE_SHIFT;
	error = _xfs_buf_get_pages(bp, page_count);
	अगर (error)
		जाओ fail_मुक्त_buf;

	क्रम (i = 0; i < page_count; i++) अणु
		bp->b_pages[i] = alloc_page(xb_to_gfp(flags));
		अगर (!bp->b_pages[i]) अणु
			error = -ENOMEM;
			जाओ fail_मुक्त_mem;
		पूर्ण
	पूर्ण
	bp->b_flags |= _XBF_PAGES;

	error = _xfs_buf_map_pages(bp, 0);
	अगर (unlikely(error)) अणु
		xfs_warn(target->bt_mount,
			"%s: failed to map pages", __func__);
		जाओ fail_मुक्त_mem;
	पूर्ण

	trace_xfs_buf_get_uncached(bp, _RET_IP_);
	*bpp = bp;
	वापस 0;

 fail_मुक्त_mem:
	जबतक (--i >= 0)
		__मुक्त_page(bp->b_pages[i]);
	_xfs_buf_मुक्त_pages(bp);
 fail_मुक्त_buf:
	xfs_buf_मुक्त_maps(bp);
	kmem_cache_मुक्त(xfs_buf_zone, bp);
 fail:
	वापस error;
पूर्ण

/*
 *	Increment reference count on buffer, to hold the buffer concurrently
 *	with another thपढ़ो which may release (मुक्त) the buffer asynchronously.
 *	Must hold the buffer alपढ़ोy to call this function.
 */
व्योम
xfs_buf_hold(
	काष्ठा xfs_buf		*bp)
अणु
	trace_xfs_buf_hold(bp, _RET_IP_);
	atomic_inc(&bp->b_hold);
पूर्ण

/*
 * Release a hold on the specअगरied buffer. If the hold count is 1, the buffer is
 * placed on LRU or मुक्तd (depending on b_lru_ref).
 */
व्योम
xfs_buf_rele(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_perag	*pag = bp->b_pag;
	bool			release;
	bool			मुक्तbuf = false;

	trace_xfs_buf_rele(bp, _RET_IP_);

	अगर (!pag) अणु
		ASSERT(list_empty(&bp->b_lru));
		अगर (atomic_dec_and_test(&bp->b_hold)) अणु
			xfs_buf_ioacct_dec(bp);
			xfs_buf_मुक्त(bp);
		पूर्ण
		वापस;
	पूर्ण

	ASSERT(atomic_पढ़ो(&bp->b_hold) > 0);

	/*
	 * We grab the b_lock here first to serialise racing xfs_buf_rele()
	 * calls. The pag_buf_lock being taken on the last reference only
	 * serialises against racing lookups in xfs_buf_find(). IOWs, the second
	 * to last reference we drop here is not serialised against the last
	 * reference until we take bp->b_lock. Hence अगर we करोn't grab b_lock
	 * first, the last "release" reference can win the race to the lock and
	 * मुक्त the buffer beक्रमe the second-to-last reference is processed,
	 * leading to a use-after-मुक्त scenario.
	 */
	spin_lock(&bp->b_lock);
	release = atomic_dec_and_lock(&bp->b_hold, &pag->pag_buf_lock);
	अगर (!release) अणु
		/*
		 * Drop the in-flight state अगर the buffer is alपढ़ोy on the LRU
		 * and it holds the only reference. This is racy because we
		 * haven't acquired the pag lock, but the use of _XBF_IN_FLIGHT
		 * ensures the decrement occurs only once per-buf.
		 */
		अगर ((atomic_पढ़ो(&bp->b_hold) == 1) && !list_empty(&bp->b_lru))
			__xfs_buf_ioacct_dec(bp);
		जाओ out_unlock;
	पूर्ण

	/* the last reference has been dropped ... */
	__xfs_buf_ioacct_dec(bp);
	अगर (!(bp->b_flags & XBF_STALE) && atomic_पढ़ो(&bp->b_lru_ref)) अणु
		/*
		 * If the buffer is added to the LRU take a new reference to the
		 * buffer क्रम the LRU and clear the (now stale) dispose list
		 * state flag
		 */
		अगर (list_lru_add(&bp->b_target->bt_lru, &bp->b_lru)) अणु
			bp->b_state &= ~XFS_BSTATE_DISPOSE;
			atomic_inc(&bp->b_hold);
		पूर्ण
		spin_unlock(&pag->pag_buf_lock);
	पूर्ण अन्यथा अणु
		/*
		 * most of the समय buffers will alपढ़ोy be हटाओd from the
		 * LRU, so optimise that हाल by checking क्रम the
		 * XFS_BSTATE_DISPOSE flag indicating the last list the buffer
		 * was on was the disposal list
		 */
		अगर (!(bp->b_state & XFS_BSTATE_DISPOSE)) अणु
			list_lru_del(&bp->b_target->bt_lru, &bp->b_lru);
		पूर्ण अन्यथा अणु
			ASSERT(list_empty(&bp->b_lru));
		पूर्ण

		ASSERT(!(bp->b_flags & _XBF_DELWRI_Q));
		rhashtable_हटाओ_fast(&pag->pag_buf_hash, &bp->b_rhash_head,
				       xfs_buf_hash_params);
		spin_unlock(&pag->pag_buf_lock);
		xfs_perag_put(pag);
		मुक्तbuf = true;
	पूर्ण

out_unlock:
	spin_unlock(&bp->b_lock);

	अगर (मुक्तbuf)
		xfs_buf_मुक्त(bp);
पूर्ण


/*
 *	Lock a buffer object, अगर it is not alपढ़ोy locked.
 *
 *	If we come across a stale, pinned, locked buffer, we know that we are
 *	being asked to lock a buffer that has been पुनः_स्मृतिated. Because it is
 *	pinned, we know that the log has not been pushed to disk and hence it
 *	will still be locked.  Rather than continuing to have trylock attempts
 *	fail until someone अन्यथा pushes the log, push it ourselves beक्रमe
 *	वापसing.  This means that the xfsaild will not get stuck trying
 *	to push on stale inode buffers.
 */
पूर्णांक
xfs_buf_trylock(
	काष्ठा xfs_buf		*bp)
अणु
	पूर्णांक			locked;

	locked = करोwn_trylock(&bp->b_sema) == 0;
	अगर (locked)
		trace_xfs_buf_trylock(bp, _RET_IP_);
	अन्यथा
		trace_xfs_buf_trylock_fail(bp, _RET_IP_);
	वापस locked;
पूर्ण

/*
 *	Lock a buffer object.
 *
 *	If we come across a stale, pinned, locked buffer, we know that we
 *	are being asked to lock a buffer that has been पुनः_स्मृतिated. Because
 *	it is pinned, we know that the log has not been pushed to disk and
 *	hence it will still be locked. Rather than sleeping until someone
 *	अन्यथा pushes the log, push it ourselves beक्रमe trying to get the lock.
 */
व्योम
xfs_buf_lock(
	काष्ठा xfs_buf		*bp)
अणु
	trace_xfs_buf_lock(bp, _RET_IP_);

	अगर (atomic_पढ़ो(&bp->b_pin_count) && (bp->b_flags & XBF_STALE))
		xfs_log_क्रमce(bp->b_mount, 0);
	करोwn(&bp->b_sema);

	trace_xfs_buf_lock_करोne(bp, _RET_IP_);
पूर्ण

व्योम
xfs_buf_unlock(
	काष्ठा xfs_buf		*bp)
अणु
	ASSERT(xfs_buf_islocked(bp));

	up(&bp->b_sema);
	trace_xfs_buf_unlock(bp, _RET_IP_);
पूर्ण

STATIC व्योम
xfs_buf_रुको_unpin(
	काष्ठा xfs_buf		*bp)
अणु
	DECLARE_WAITQUEUE	(रुको, current);

	अगर (atomic_पढ़ो(&bp->b_pin_count) == 0)
		वापस;

	add_रुको_queue(&bp->b_रुकोers, &रुको);
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (atomic_पढ़ो(&bp->b_pin_count) == 0)
			अवरोध;
		io_schedule();
	पूर्ण
	हटाओ_रुको_queue(&bp->b_रुकोers, &रुको);
	set_current_state(TASK_RUNNING);
पूर्ण

अटल व्योम
xfs_buf_ioerror_alert_ratelimited(
	काष्ठा xfs_buf		*bp)
अणु
	अटल अचिन्हित दीर्घ	lastसमय;
	अटल काष्ठा xfs_buftarg *lasttarg;

	अगर (bp->b_target != lasttarg ||
	    समय_after(jअगरfies, (lastसमय + 5*HZ))) अणु
		lastसमय = jअगरfies;
		xfs_buf_ioerror_alert(bp, __this_address);
	पूर्ण
	lasttarg = bp->b_target;
पूर्ण

/*
 * Account क्रम this latest trip around the retry handler, and decide अगर
 * we've failed enough बार to स्थिरitute a permanent failure.
 */
अटल bool
xfs_buf_ioerror_permanent(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_error_cfg	*cfg)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	अगर (cfg->max_retries != XFS_ERR_RETRY_FOREVER &&
	    ++bp->b_retries > cfg->max_retries)
		वापस true;
	अगर (cfg->retry_समयout != XFS_ERR_RETRY_FOREVER &&
	    समय_after(jअगरfies, cfg->retry_समयout + bp->b_first_retry_समय))
		वापस true;

	/* At unmount we may treat errors dअगरferently */
	अगर ((mp->m_flags & XFS_MOUNT_UNMOUNTING) && mp->m_fail_unmount)
		वापस true;

	वापस false;
पूर्ण

/*
 * On a sync ग_लिखो or shutकरोwn we just want to stale the buffer and let the
 * caller handle the error in bp->b_error appropriately.
 *
 * If the ग_लिखो was asynchronous then no one will be looking क्रम the error.  If
 * this is the first failure of this type, clear the error state and ग_लिखो the
 * buffer out again. This means we always retry an async ग_लिखो failure at least
 * once, but we also need to set the buffer up to behave correctly now क्रम
 * repeated failures.
 *
 * If we get repeated async ग_लिखो failures, then we take action according to the
 * error configuration we have been set up to use.
 *
 * Returns true अगर this function took care of error handling and the caller must
 * not touch the buffer again.  Return false अगर the caller should proceed with
 * normal I/O completion handling.
 */
अटल bool
xfs_buf_ioend_handle_error(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_error_cfg	*cfg;

	/*
	 * If we've alपढ़ोy decided to shutकरोwn the fileप्रणाली because of I/O
	 * errors, there's no poपूर्णांक in giving this a retry.
	 */
	अगर (XFS_FORCED_SHUTDOWN(mp))
		जाओ out_stale;

	xfs_buf_ioerror_alert_ratelimited(bp);

	/*
	 * We're not going to bother about retrying this during recovery.
	 * One strike!
	 */
	अगर (bp->b_flags & _XBF_LOGRECOVERY) अणु
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_META_IO_ERROR);
		वापस false;
	पूर्ण

	/*
	 * Synchronous ग_लिखोs will have callers process the error.
	 */
	अगर (!(bp->b_flags & XBF_ASYNC))
		जाओ out_stale;

	trace_xfs_buf_ioकरोne_async(bp, _RET_IP_);

	cfg = xfs_error_get_cfg(mp, XFS_ERR_METADATA, bp->b_error);
	अगर (bp->b_last_error != bp->b_error ||
	    !(bp->b_flags & (XBF_STALE | XBF_WRITE_FAIL))) अणु
		bp->b_last_error = bp->b_error;
		अगर (cfg->retry_समयout != XFS_ERR_RETRY_FOREVER &&
		    !bp->b_first_retry_समय)
			bp->b_first_retry_समय = jअगरfies;
		जाओ resubmit;
	पूर्ण

	/*
	 * Permanent error - we need to trigger a shutकरोwn अगर we haven't alपढ़ोy
	 * to indicate that inconsistency will result from this action.
	 */
	अगर (xfs_buf_ioerror_permanent(bp, cfg)) अणु
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_META_IO_ERROR);
		जाओ out_stale;
	पूर्ण

	/* Still considered a transient error. Caller will schedule retries. */
	अगर (bp->b_flags & _XBF_INODES)
		xfs_buf_inode_io_fail(bp);
	अन्यथा अगर (bp->b_flags & _XBF_DQUOTS)
		xfs_buf_dquot_io_fail(bp);
	अन्यथा
		ASSERT(list_empty(&bp->b_li_list));
	xfs_buf_ioerror(bp, 0);
	xfs_buf_rअन्यथा(bp);
	वापस true;

resubmit:
	xfs_buf_ioerror(bp, 0);
	bp->b_flags |= (XBF_DONE | XBF_WRITE_FAIL);
	xfs_buf_submit(bp);
	वापस true;
out_stale:
	xfs_buf_stale(bp);
	bp->b_flags |= XBF_DONE;
	bp->b_flags &= ~XBF_WRITE;
	trace_xfs_buf_error_rअन्यथा(bp, _RET_IP_);
	वापस false;
पूर्ण

अटल व्योम
xfs_buf_ioend(
	काष्ठा xfs_buf	*bp)
अणु
	trace_xfs_buf_ioकरोne(bp, _RET_IP_);

	/*
	 * Pull in IO completion errors now. We are guaranteed to be running
	 * single thपढ़ोed, so we करोn't need the lock to पढ़ो b_io_error.
	 */
	अगर (!bp->b_error && bp->b_io_error)
		xfs_buf_ioerror(bp, bp->b_io_error);

	अगर (bp->b_flags & XBF_READ) अणु
		अगर (!bp->b_error && bp->b_ops)
			bp->b_ops->verअगरy_पढ़ो(bp);
		अगर (!bp->b_error)
			bp->b_flags |= XBF_DONE;
	पूर्ण अन्यथा अणु
		अगर (!bp->b_error) अणु
			bp->b_flags &= ~XBF_WRITE_FAIL;
			bp->b_flags |= XBF_DONE;
		पूर्ण

		अगर (unlikely(bp->b_error) && xfs_buf_ioend_handle_error(bp))
			वापस;

		/* clear the retry state */
		bp->b_last_error = 0;
		bp->b_retries = 0;
		bp->b_first_retry_समय = 0;

		/*
		 * Note that क्रम things like remote attribute buffers, there may
		 * not be a buffer log item here, so processing the buffer log
		 * item must reमुख्य optional.
		 */
		अगर (bp->b_log_item)
			xfs_buf_item_करोne(bp);

		अगर (bp->b_flags & _XBF_INODES)
			xfs_buf_inode_ioकरोne(bp);
		अन्यथा अगर (bp->b_flags & _XBF_DQUOTS)
			xfs_buf_dquot_ioकरोne(bp);

	पूर्ण

	bp->b_flags &= ~(XBF_READ | XBF_WRITE | XBF_READ_AHEAD |
			 _XBF_LOGRECOVERY);

	अगर (bp->b_flags & XBF_ASYNC)
		xfs_buf_rअन्यथा(bp);
	अन्यथा
		complete(&bp->b_ioरुको);
पूर्ण

अटल व्योम
xfs_buf_ioend_work(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_buf		*bp =
		container_of(work, काष्ठा xfs_buf, b_ioend_work);

	xfs_buf_ioend(bp);
पूर्ण

अटल व्योम
xfs_buf_ioend_async(
	काष्ठा xfs_buf	*bp)
अणु
	INIT_WORK(&bp->b_ioend_work, xfs_buf_ioend_work);
	queue_work(bp->b_mount->m_buf_workqueue, &bp->b_ioend_work);
पूर्ण

व्योम
__xfs_buf_ioerror(
	काष्ठा xfs_buf		*bp,
	पूर्णांक			error,
	xfs_failaddr_t		failaddr)
अणु
	ASSERT(error <= 0 && error >= -1000);
	bp->b_error = error;
	trace_xfs_buf_ioerror(bp, error, failaddr);
पूर्ण

व्योम
xfs_buf_ioerror_alert(
	काष्ठा xfs_buf		*bp,
	xfs_failaddr_t		func)
अणु
	xfs_buf_alert_ratelimited(bp, "XFS: metadata IO error",
		"metadata I/O error in \"%pS\" at daddr 0x%llx len %d error %d",
				  func, (uपूर्णांक64_t)XFS_BUF_ADDR(bp),
				  bp->b_length, -bp->b_error);
पूर्ण

/*
 * To simulate an I/O failure, the buffer must be locked and held with at least
 * three references. The LRU reference is dropped by the stale call. The buf
 * item reference is dropped via ioend processing. The third reference is owned
 * by the caller and is dropped on I/O completion अगर the buffer is XBF_ASYNC.
 */
व्योम
xfs_buf_ioend_fail(
	काष्ठा xfs_buf	*bp)
अणु
	bp->b_flags &= ~XBF_DONE;
	xfs_buf_stale(bp);
	xfs_buf_ioerror(bp, -EIO);
	xfs_buf_ioend(bp);
पूर्ण

पूर्णांक
xfs_bग_लिखो(
	काष्ठा xfs_buf		*bp)
अणु
	पूर्णांक			error;

	ASSERT(xfs_buf_islocked(bp));

	bp->b_flags |= XBF_WRITE;
	bp->b_flags &= ~(XBF_ASYNC | XBF_READ | _XBF_DELWRI_Q |
			 XBF_DONE);

	error = xfs_buf_submit(bp);
	अगर (error)
		xfs_क्रमce_shutकरोwn(bp->b_mount, SHUTDOWN_META_IO_ERROR);
	वापस error;
पूर्ण

अटल व्योम
xfs_buf_bio_end_io(
	काष्ठा bio		*bio)
अणु
	काष्ठा xfs_buf		*bp = (काष्ठा xfs_buf *)bio->bi_निजी;

	अगर (!bio->bi_status &&
	    (bp->b_flags & XBF_WRITE) && (bp->b_flags & XBF_ASYNC) &&
	    XFS_TEST_ERROR(false, bp->b_mount, XFS_ERRTAG_BUF_IOERROR))
		bio->bi_status = BLK_STS_IOERR;

	/*
	 * करोn't overग_लिखो existing errors - otherwise we can lose errors on
	 * buffers that require multiple bios to complete.
	 */
	अगर (bio->bi_status) अणु
		पूर्णांक error = blk_status_to_त्रुटि_सं(bio->bi_status);

		cmpxchg(&bp->b_io_error, 0, error);
	पूर्ण

	अगर (!bp->b_error && xfs_buf_is_vmapped(bp) && (bp->b_flags & XBF_READ))
		invalidate_kernel_vmap_range(bp->b_addr, xfs_buf_vmap_len(bp));

	अगर (atomic_dec_and_test(&bp->b_io_reमुख्यing) == 1)
		xfs_buf_ioend_async(bp);
	bio_put(bio);
पूर्ण

अटल व्योम
xfs_buf_ioapply_map(
	काष्ठा xfs_buf	*bp,
	पूर्णांक		map,
	पूर्णांक		*buf_offset,
	पूर्णांक		*count,
	पूर्णांक		op)
अणु
	पूर्णांक		page_index;
	अचिन्हित पूर्णांक	total_nr_pages = bp->b_page_count;
	पूर्णांक		nr_pages;
	काष्ठा bio	*bio;
	sector_t	sector =  bp->b_maps[map].bm_bn;
	पूर्णांक		size;
	पूर्णांक		offset;

	/* skip the pages in the buffer beक्रमe the start offset */
	page_index = 0;
	offset = *buf_offset;
	जबतक (offset >= PAGE_SIZE) अणु
		page_index++;
		offset -= PAGE_SIZE;
	पूर्ण

	/*
	 * Limit the IO size to the length of the current vector, and update the
	 * reमुख्यing IO count क्रम the next समय around.
	 */
	size = min_t(पूर्णांक, BBTOB(bp->b_maps[map].bm_len), *count);
	*count -= size;
	*buf_offset += size;

next_chunk:
	atomic_inc(&bp->b_io_reमुख्यing);
	nr_pages = bio_max_segs(total_nr_pages);

	bio = bio_alloc(GFP_NOIO, nr_pages);
	bio_set_dev(bio, bp->b_target->bt_bdev);
	bio->bi_iter.bi_sector = sector;
	bio->bi_end_io = xfs_buf_bio_end_io;
	bio->bi_निजी = bp;
	bio->bi_opf = op;

	क्रम (; size && nr_pages; nr_pages--, page_index++) अणु
		पूर्णांक	rbytes, nbytes = PAGE_SIZE - offset;

		अगर (nbytes > size)
			nbytes = size;

		rbytes = bio_add_page(bio, bp->b_pages[page_index], nbytes,
				      offset);
		अगर (rbytes < nbytes)
			अवरोध;

		offset = 0;
		sector += BTOBB(nbytes);
		size -= nbytes;
		total_nr_pages--;
	पूर्ण

	अगर (likely(bio->bi_iter.bi_size)) अणु
		अगर (xfs_buf_is_vmapped(bp)) अणु
			flush_kernel_vmap_range(bp->b_addr,
						xfs_buf_vmap_len(bp));
		पूर्ण
		submit_bio(bio);
		अगर (size)
			जाओ next_chunk;
	पूर्ण अन्यथा अणु
		/*
		 * This is guaranteed not to be the last io reference count
		 * because the caller (xfs_buf_submit) holds a count itself.
		 */
		atomic_dec(&bp->b_io_reमुख्यing);
		xfs_buf_ioerror(bp, -EIO);
		bio_put(bio);
	पूर्ण

पूर्ण

STATIC व्योम
_xfs_buf_ioapply(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा blk_plug	plug;
	पूर्णांक		op;
	पूर्णांक		offset;
	पूर्णांक		size;
	पूर्णांक		i;

	/*
	 * Make sure we capture only current IO errors rather than stale errors
	 * left over from previous use of the buffer (e.g. failed पढ़ोahead).
	 */
	bp->b_error = 0;

	अगर (bp->b_flags & XBF_WRITE) अणु
		op = REQ_OP_WRITE;

		/*
		 * Run the ग_लिखो verअगरier callback function अगर it exists. If
		 * this function fails it will mark the buffer with an error and
		 * the IO should not be dispatched.
		 */
		अगर (bp->b_ops) अणु
			bp->b_ops->verअगरy_ग_लिखो(bp);
			अगर (bp->b_error) अणु
				xfs_क्रमce_shutकरोwn(bp->b_mount,
						   SHUTDOWN_CORRUPT_INCORE);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (bp->b_bn != XFS_BUF_DADDR_शून्य) अणु
			काष्ठा xfs_mount *mp = bp->b_mount;

			/*
			 * non-crc fileप्रणालीs करोn't attach verअगरiers during
			 * log recovery, so करोn't warn क्रम such fileप्रणालीs.
			 */
			अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
				xfs_warn(mp,
					"%s: no buf ops on daddr 0x%llx len %d",
					__func__, bp->b_bn, bp->b_length);
				xfs_hex_dump(bp->b_addr,
						XFS_CORRUPTION_DUMP_LEN);
				dump_stack();
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		op = REQ_OP_READ;
		अगर (bp->b_flags & XBF_READ_AHEAD)
			op |= REQ_RAHEAD;
	पूर्ण

	/* we only use the buffer cache क्रम meta-data */
	op |= REQ_META;

	/*
	 * Walk all the vectors issuing IO on them. Set up the initial offset
	 * पूर्णांकo the buffer and the desired IO size beक्रमe we start -
	 * _xfs_buf_ioapply_vec() will modअगरy them appropriately क्रम each
	 * subsequent call.
	 */
	offset = bp->b_offset;
	size = BBTOB(bp->b_length);
	blk_start_plug(&plug);
	क्रम (i = 0; i < bp->b_map_count; i++) अणु
		xfs_buf_ioapply_map(bp, i, &offset, &size, op);
		अगर (bp->b_error)
			अवरोध;
		अगर (size <= 0)
			अवरोध;	/* all करोne */
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/*
 * Wait क्रम I/O completion of a sync buffer and वापस the I/O error code.
 */
अटल पूर्णांक
xfs_buf_ioरुको(
	काष्ठा xfs_buf	*bp)
अणु
	ASSERT(!(bp->b_flags & XBF_ASYNC));

	trace_xfs_buf_ioरुको(bp, _RET_IP_);
	रुको_क्रम_completion(&bp->b_ioरुको);
	trace_xfs_buf_ioरुको_करोne(bp, _RET_IP_);

	वापस bp->b_error;
पूर्ण

/*
 * Buffer I/O submission path, पढ़ो or ग_लिखो. Asynchronous submission transfers
 * the buffer lock ownership and the current reference to the IO. It is not
 * safe to reference the buffer after a call to this function unless the caller
 * holds an additional reference itself.
 */
अटल पूर्णांक
__xfs_buf_submit(
	काष्ठा xfs_buf	*bp,
	bool		रुको)
अणु
	पूर्णांक		error = 0;

	trace_xfs_buf_submit(bp, _RET_IP_);

	ASSERT(!(bp->b_flags & _XBF_DELWRI_Q));

	/* on shutकरोwn we stale and complete the buffer immediately */
	अगर (XFS_FORCED_SHUTDOWN(bp->b_mount)) अणु
		xfs_buf_ioend_fail(bp);
		वापस -EIO;
	पूर्ण

	/*
	 * Grab a reference so the buffer करोes not go away underneath us. For
	 * async buffers, I/O completion drops the callers reference, which
	 * could occur beक्रमe submission वापसs.
	 */
	xfs_buf_hold(bp);

	अगर (bp->b_flags & XBF_WRITE)
		xfs_buf_रुको_unpin(bp);

	/* clear the पूर्णांकernal error state to aव्योम spurious errors */
	bp->b_io_error = 0;

	/*
	 * Set the count to 1 initially, this will stop an I/O completion
	 * callout which happens beक्रमe we have started all the I/O from calling
	 * xfs_buf_ioend too early.
	 */
	atomic_set(&bp->b_io_reमुख्यing, 1);
	अगर (bp->b_flags & XBF_ASYNC)
		xfs_buf_ioacct_inc(bp);
	_xfs_buf_ioapply(bp);

	/*
	 * If _xfs_buf_ioapply failed, we can get back here with only the IO
	 * reference we took above. If we drop it to zero, run completion so
	 * that we करोn't वापस to the caller with completion still pending.
	 */
	अगर (atomic_dec_and_test(&bp->b_io_reमुख्यing) == 1) अणु
		अगर (bp->b_error || !(bp->b_flags & XBF_ASYNC))
			xfs_buf_ioend(bp);
		अन्यथा
			xfs_buf_ioend_async(bp);
	पूर्ण

	अगर (रुको)
		error = xfs_buf_ioरुको(bp);

	/*
	 * Release the hold that keeps the buffer referenced क्रम the entire
	 * I/O. Note that अगर the buffer is async, it is not safe to reference
	 * after this release.
	 */
	xfs_buf_rele(bp);
	वापस error;
पूर्ण

व्योम *
xfs_buf_offset(
	काष्ठा xfs_buf		*bp,
	माप_प्रकार			offset)
अणु
	काष्ठा page		*page;

	अगर (bp->b_addr)
		वापस bp->b_addr + offset;

	offset += bp->b_offset;
	page = bp->b_pages[offset >> PAGE_SHIFT];
	वापस page_address(page) + (offset & (PAGE_SIZE-1));
पूर्ण

व्योम
xfs_buf_zero(
	काष्ठा xfs_buf		*bp,
	माप_प्रकार			boff,
	माप_प्रकार			bsize)
अणु
	माप_प्रकार			bend;

	bend = boff + bsize;
	जबतक (boff < bend) अणु
		काष्ठा page	*page;
		पूर्णांक		page_index, page_offset, csize;

		page_index = (boff + bp->b_offset) >> PAGE_SHIFT;
		page_offset = (boff + bp->b_offset) & ~PAGE_MASK;
		page = bp->b_pages[page_index];
		csize = min_t(माप_प्रकार, PAGE_SIZE - page_offset,
				      BBTOB(bp->b_length) - boff);

		ASSERT((csize + page_offset) <= PAGE_SIZE);

		स_रखो(page_address(page) + page_offset, 0, csize);

		boff += csize;
	पूर्ण
पूर्ण

/*
 * Log a message about and stale a buffer that a caller has decided is corrupt.
 *
 * This function should be called क्रम the kinds of metadata corruption that
 * cannot be detect from a verअगरier, such as incorrect पूर्णांकer-block relationship
 * data.  Do /not/ call this function from a verअगरier function.
 *
 * The buffer must be XBF_DONE prior to the call.  Afterwards, the buffer will
 * be marked stale, but b_error will not be set.  The caller is responsible क्रम
 * releasing the buffer or fixing it.
 */
व्योम
__xfs_buf_mark_corrupt(
	काष्ठा xfs_buf		*bp,
	xfs_failaddr_t		fa)
अणु
	ASSERT(bp->b_flags & XBF_DONE);

	xfs_buf_corruption_error(bp, fa);
	xfs_buf_stale(bp);
पूर्ण

/*
 *	Handling of buffer tarमाला_लो (buftargs).
 */

/*
 * Wait क्रम any bufs with callbacks that have been submitted but have not yet
 * वापसed. These buffers will have an elevated hold count, so रुको on those
 * जबतक मुक्तing all the buffers only held by the LRU.
 */
अटल क्रमागत lru_status
xfs_buftarg_drain_rele(
	काष्ठा list_head	*item,
	काष्ठा list_lru_one	*lru,
	spinlock_t		*lru_lock,
	व्योम			*arg)

अणु
	काष्ठा xfs_buf		*bp = container_of(item, काष्ठा xfs_buf, b_lru);
	काष्ठा list_head	*dispose = arg;

	अगर (atomic_पढ़ो(&bp->b_hold) > 1) अणु
		/* need to रुको, so skip it this pass */
		trace_xfs_buf_drain_buftarg(bp, _RET_IP_);
		वापस LRU_SKIP;
	पूर्ण
	अगर (!spin_trylock(&bp->b_lock))
		वापस LRU_SKIP;

	/*
	 * clear the LRU reference count so the buffer करोesn't get
	 * ignored in xfs_buf_rele().
	 */
	atomic_set(&bp->b_lru_ref, 0);
	bp->b_state |= XFS_BSTATE_DISPOSE;
	list_lru_isolate_move(lru, item, dispose);
	spin_unlock(&bp->b_lock);
	वापस LRU_REMOVED;
पूर्ण

/*
 * Wait क्रम outstanding I/O on the buftarg to complete.
 */
व्योम
xfs_buftarg_रुको(
	काष्ठा xfs_buftarg	*btp)
अणु
	/*
	 * First रुको on the buftarg I/O count क्रम all in-flight buffers to be
	 * released. This is critical as new buffers करो not make the LRU until
	 * they are released.
	 *
	 * Next, flush the buffer workqueue to ensure all completion processing
	 * has finished. Just रुकोing on buffer locks is not sufficient क्रम
	 * async IO as the reference count held over IO is not released until
	 * after the buffer lock is dropped. Hence we need to ensure here that
	 * all reference counts have been dropped beक्रमe we start walking the
	 * LRU list.
	 */
	जबतक (percpu_counter_sum(&btp->bt_io_count))
		delay(100);
	flush_workqueue(btp->bt_mount->m_buf_workqueue);
पूर्ण

व्योम
xfs_buftarg_drain(
	काष्ठा xfs_buftarg	*btp)
अणु
	LIST_HEAD(dispose);
	पूर्णांक			loop = 0;
	bool			ग_लिखो_fail = false;

	xfs_buftarg_रुको(btp);

	/* loop until there is nothing left on the lru list. */
	जबतक (list_lru_count(&btp->bt_lru)) अणु
		list_lru_walk(&btp->bt_lru, xfs_buftarg_drain_rele,
			      &dispose, दीर्घ_उच्च);

		जबतक (!list_empty(&dispose)) अणु
			काष्ठा xfs_buf *bp;
			bp = list_first_entry(&dispose, काष्ठा xfs_buf, b_lru);
			list_del_init(&bp->b_lru);
			अगर (bp->b_flags & XBF_WRITE_FAIL) अणु
				ग_लिखो_fail = true;
				xfs_buf_alert_ratelimited(bp,
					"XFS: Corruption Alert",
"Corruption Alert: Buffer at daddr 0x%llx had permanent write failures!",
					(दीर्घ दीर्घ)bp->b_bn);
			पूर्ण
			xfs_buf_rele(bp);
		पूर्ण
		अगर (loop++ != 0)
			delay(100);
	पूर्ण

	/*
	 * If one or more failed buffers were मुक्तd, that means dirty metadata
	 * was thrown away. This should only ever happen after I/O completion
	 * handling has elevated I/O error(s) to permanent failures and shuts
	 * करोwn the fs.
	 */
	अगर (ग_लिखो_fail) अणु
		ASSERT(XFS_FORCED_SHUTDOWN(btp->bt_mount));
		xfs_alert(btp->bt_mount,
	      "Please run xfs_repair to determine the extent of the problem.");
	पूर्ण
पूर्ण

अटल क्रमागत lru_status
xfs_buftarg_isolate(
	काष्ठा list_head	*item,
	काष्ठा list_lru_one	*lru,
	spinlock_t		*lru_lock,
	व्योम			*arg)
अणु
	काष्ठा xfs_buf		*bp = container_of(item, काष्ठा xfs_buf, b_lru);
	काष्ठा list_head	*dispose = arg;

	/*
	 * we are inverting the lru lock/bp->b_lock here, so use a trylock.
	 * If we fail to get the lock, just skip it.
	 */
	अगर (!spin_trylock(&bp->b_lock))
		वापस LRU_SKIP;
	/*
	 * Decrement the b_lru_ref count unless the value is alपढ़ोy
	 * zero. If the value is alपढ़ोy zero, we need to reclaim the
	 * buffer, otherwise it माला_लो another trip through the LRU.
	 */
	अगर (atomic_add_unless(&bp->b_lru_ref, -1, 0)) अणु
		spin_unlock(&bp->b_lock);
		वापस LRU_ROTATE;
	पूर्ण

	bp->b_state |= XFS_BSTATE_DISPOSE;
	list_lru_isolate_move(lru, item, dispose);
	spin_unlock(&bp->b_lock);
	वापस LRU_REMOVED;
पूर्ण

अटल अचिन्हित दीर्घ
xfs_buftarg_shrink_scan(
	काष्ठा shrinker		*shrink,
	काष्ठा shrink_control	*sc)
अणु
	काष्ठा xfs_buftarg	*btp = container_of(shrink,
					काष्ठा xfs_buftarg, bt_shrinker);
	LIST_HEAD(dispose);
	अचिन्हित दीर्घ		मुक्तd;

	मुक्तd = list_lru_shrink_walk(&btp->bt_lru, sc,
				     xfs_buftarg_isolate, &dispose);

	जबतक (!list_empty(&dispose)) अणु
		काष्ठा xfs_buf *bp;
		bp = list_first_entry(&dispose, काष्ठा xfs_buf, b_lru);
		list_del_init(&bp->b_lru);
		xfs_buf_rele(bp);
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
xfs_buftarg_shrink_count(
	काष्ठा shrinker		*shrink,
	काष्ठा shrink_control	*sc)
अणु
	काष्ठा xfs_buftarg	*btp = container_of(shrink,
					काष्ठा xfs_buftarg, bt_shrinker);
	वापस list_lru_shrink_count(&btp->bt_lru, sc);
पूर्ण

व्योम
xfs_मुक्त_buftarg(
	काष्ठा xfs_buftarg	*btp)
अणु
	unरेजिस्टर_shrinker(&btp->bt_shrinker);
	ASSERT(percpu_counter_sum(&btp->bt_io_count) == 0);
	percpu_counter_destroy(&btp->bt_io_count);
	list_lru_destroy(&btp->bt_lru);

	xfs_blkdev_issue_flush(btp);

	kmem_मुक्त(btp);
पूर्ण

पूर्णांक
xfs_setsize_buftarg(
	xfs_buftarg_t		*btp,
	अचिन्हित पूर्णांक		sectorsize)
अणु
	/* Set up metadata sector size info */
	btp->bt_meta_sectorsize = sectorsize;
	btp->bt_meta_sectormask = sectorsize - 1;

	अगर (set_blocksize(btp->bt_bdev, sectorsize)) अणु
		xfs_warn(btp->bt_mount,
			"Cannot set_blocksize to %u on device %pg",
			sectorsize, btp->bt_bdev);
		वापस -EINVAL;
	पूर्ण

	/* Set up device logical sector size mask */
	btp->bt_logical_sectorsize = bdev_logical_block_size(btp->bt_bdev);
	btp->bt_logical_sectormask = bdev_logical_block_size(btp->bt_bdev) - 1;

	वापस 0;
पूर्ण

/*
 * When allocating the initial buffer target we have not yet
 * पढ़ो in the superblock, so करोn't know what sized sectors
 * are being used at this early stage.  Play safe.
 */
STATIC पूर्णांक
xfs_setsize_buftarg_early(
	xfs_buftarg_t		*btp,
	काष्ठा block_device	*bdev)
अणु
	वापस xfs_setsize_buftarg(btp, bdev_logical_block_size(bdev));
पूर्ण

xfs_buftarg_t *
xfs_alloc_buftarg(
	काष्ठा xfs_mount	*mp,
	काष्ठा block_device	*bdev,
	काष्ठा dax_device	*dax_dev)
अणु
	xfs_buftarg_t		*btp;

	btp = kmem_zalloc(माप(*btp), KM_NOFS);

	btp->bt_mount = mp;
	btp->bt_dev =  bdev->bd_dev;
	btp->bt_bdev = bdev;
	btp->bt_daxdev = dax_dev;

	/*
	 * Buffer IO error rate limiting. Limit it to no more than 10 messages
	 * per 30 seconds so as to not spam logs too much on repeated errors.
	 */
	ratelimit_state_init(&btp->bt_ioerror_rl, 30 * HZ,
			     DEFAULT_RATELIMIT_BURST);

	अगर (xfs_setsize_buftarg_early(btp, bdev))
		जाओ error_मुक्त;

	अगर (list_lru_init(&btp->bt_lru))
		जाओ error_मुक्त;

	अगर (percpu_counter_init(&btp->bt_io_count, 0, GFP_KERNEL))
		जाओ error_lru;

	btp->bt_shrinker.count_objects = xfs_buftarg_shrink_count;
	btp->bt_shrinker.scan_objects = xfs_buftarg_shrink_scan;
	btp->bt_shrinker.seeks = DEFAULT_SEEKS;
	btp->bt_shrinker.flags = SHRINKER_NUMA_AWARE;
	अगर (रेजिस्टर_shrinker(&btp->bt_shrinker))
		जाओ error_pcpu;
	वापस btp;

error_pcpu:
	percpu_counter_destroy(&btp->bt_io_count);
error_lru:
	list_lru_destroy(&btp->bt_lru);
error_मुक्त:
	kmem_मुक्त(btp);
	वापस शून्य;
पूर्ण

/*
 * Cancel a delayed ग_लिखो list.
 *
 * Remove each buffer from the list, clear the delwri queue flag and drop the
 * associated buffer reference.
 */
व्योम
xfs_buf_delwri_cancel(
	काष्ठा list_head	*list)
अणु
	काष्ठा xfs_buf		*bp;

	जबतक (!list_empty(list)) अणु
		bp = list_first_entry(list, काष्ठा xfs_buf, b_list);

		xfs_buf_lock(bp);
		bp->b_flags &= ~_XBF_DELWRI_Q;
		list_del_init(&bp->b_list);
		xfs_buf_rअन्यथा(bp);
	पूर्ण
पूर्ण

/*
 * Add a buffer to the delayed ग_लिखो list.
 *
 * This queues a buffer क्रम ग_लिखोout अगर it hasn't alपढ़ोy been.  Note that
 * neither this routine nor the buffer list submission functions perक्रमm
 * any पूर्णांकernal synchronization.  It is expected that the lists are thपढ़ो-local
 * to the callers.
 *
 * Returns true अगर we queued up the buffer, or false अगर it alपढ़ोy had
 * been on the buffer list.
 */
bool
xfs_buf_delwri_queue(
	काष्ठा xfs_buf		*bp,
	काष्ठा list_head	*list)
अणु
	ASSERT(xfs_buf_islocked(bp));
	ASSERT(!(bp->b_flags & XBF_READ));

	/*
	 * If the buffer is alपढ़ोy marked delwri it alपढ़ोy is queued up
	 * by someone अन्यथा क्रम imediate ग_लिखोout.  Just ignore it in that
	 * हाल.
	 */
	अगर (bp->b_flags & _XBF_DELWRI_Q) अणु
		trace_xfs_buf_delwri_queued(bp, _RET_IP_);
		वापस false;
	पूर्ण

	trace_xfs_buf_delwri_queue(bp, _RET_IP_);

	/*
	 * If a buffer माला_लो written out synchronously or marked stale जबतक it
	 * is on a delwri list we lazily हटाओ it. To करो this, the other party
	 * clears the  _XBF_DELWRI_Q flag but otherwise leaves the buffer alone.
	 * It reमुख्यs referenced and on the list.  In a rare corner हाल it
	 * might get पढ़ोded to a delwri list after the synchronous ग_लिखोout, in
	 * which हाल we need just need to re-add the flag here.
	 */
	bp->b_flags |= _XBF_DELWRI_Q;
	अगर (list_empty(&bp->b_list)) अणु
		atomic_inc(&bp->b_hold);
		list_add_tail(&bp->b_list, list);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Compare function is more complex than it needs to be because
 * the वापस value is only 32 bits and we are करोing comparisons
 * on 64 bit values
 */
अटल पूर्णांक
xfs_buf_cmp(
	व्योम			*priv,
	स्थिर काष्ठा list_head	*a,
	स्थिर काष्ठा list_head	*b)
अणु
	काष्ठा xfs_buf	*ap = container_of(a, काष्ठा xfs_buf, b_list);
	काष्ठा xfs_buf	*bp = container_of(b, काष्ठा xfs_buf, b_list);
	xfs_daddr_t		dअगरf;

	dअगरf = ap->b_maps[0].bm_bn - bp->b_maps[0].bm_bn;
	अगर (dअगरf < 0)
		वापस -1;
	अगर (dअगरf > 0)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Submit buffers क्रम ग_लिखो. If रुको_list is specअगरied, the buffers are
 * submitted using sync I/O and placed on the रुको list such that the caller can
 * ioरुको each buffer. Otherwise async I/O is used and the buffers are released
 * at I/O completion समय. In either हाल, buffers reमुख्य locked until I/O
 * completes and the buffer is released from the queue.
 */
अटल पूर्णांक
xfs_buf_delwri_submit_buffers(
	काष्ठा list_head	*buffer_list,
	काष्ठा list_head	*रुको_list)
अणु
	काष्ठा xfs_buf		*bp, *n;
	पूर्णांक			pinned = 0;
	काष्ठा blk_plug		plug;

	list_sort(शून्य, buffer_list, xfs_buf_cmp);

	blk_start_plug(&plug);
	list_क्रम_each_entry_safe(bp, n, buffer_list, b_list) अणु
		अगर (!रुको_list) अणु
			अगर (xfs_buf_ispinned(bp)) अणु
				pinned++;
				जारी;
			पूर्ण
			अगर (!xfs_buf_trylock(bp))
				जारी;
		पूर्ण अन्यथा अणु
			xfs_buf_lock(bp);
		पूर्ण

		/*
		 * Someone अन्यथा might have written the buffer synchronously or
		 * marked it stale in the meanसमय.  In that हाल only the
		 * _XBF_DELWRI_Q flag got cleared, and we have to drop the
		 * reference and हटाओ it from the list here.
		 */
		अगर (!(bp->b_flags & _XBF_DELWRI_Q)) अणु
			list_del_init(&bp->b_list);
			xfs_buf_rअन्यथा(bp);
			जारी;
		पूर्ण

		trace_xfs_buf_delwri_split(bp, _RET_IP_);

		/*
		 * If we have a रुको list, each buffer (and associated delwri
		 * queue reference) transfers to it and is submitted
		 * synchronously. Otherwise, drop the buffer from the delwri
		 * queue and submit async.
		 */
		bp->b_flags &= ~_XBF_DELWRI_Q;
		bp->b_flags |= XBF_WRITE;
		अगर (रुको_list) अणु
			bp->b_flags &= ~XBF_ASYNC;
			list_move_tail(&bp->b_list, रुको_list);
		पूर्ण अन्यथा अणु
			bp->b_flags |= XBF_ASYNC;
			list_del_init(&bp->b_list);
		पूर्ण
		__xfs_buf_submit(bp, false);
	पूर्ण
	blk_finish_plug(&plug);

	वापस pinned;
पूर्ण

/*
 * Write out a buffer list asynchronously.
 *
 * This will take the @buffer_list, ग_लिखो all non-locked and non-pinned buffers
 * out and not रुको क्रम I/O completion on any of the buffers.  This पूर्णांकerface
 * is only safely useable क्रम callers that can track I/O completion by higher
 * level means, e.g. AIL pushing as the @buffer_list is consumed in this
 * function.
 *
 * Note: this function will skip buffers it would block on, and in करोing so
 * leaves them on @buffer_list so they can be retried on a later pass. As such,
 * it is up to the caller to ensure that the buffer list is fully submitted or
 * cancelled appropriately when they are finished with the list. Failure to
 * cancel or resubmit the list until it is empty will result in leaked buffers
 * at unmount समय.
 */
पूर्णांक
xfs_buf_delwri_submit_noरुको(
	काष्ठा list_head	*buffer_list)
अणु
	वापस xfs_buf_delwri_submit_buffers(buffer_list, शून्य);
पूर्ण

/*
 * Write out a buffer list synchronously.
 *
 * This will take the @buffer_list, ग_लिखो all buffers out and रुको क्रम I/O
 * completion on all of the buffers. @buffer_list is consumed by the function,
 * so callers must have some other way of tracking buffers अगर they require such
 * functionality.
 */
पूर्णांक
xfs_buf_delwri_submit(
	काष्ठा list_head	*buffer_list)
अणु
	LIST_HEAD		(रुको_list);
	पूर्णांक			error = 0, error2;
	काष्ठा xfs_buf		*bp;

	xfs_buf_delwri_submit_buffers(buffer_list, &रुको_list);

	/* Wait क्रम IO to complete. */
	जबतक (!list_empty(&रुको_list)) अणु
		bp = list_first_entry(&रुको_list, काष्ठा xfs_buf, b_list);

		list_del_init(&bp->b_list);

		/*
		 * Wait on the locked buffer, check क्रम errors and unlock and
		 * release the delwri queue reference.
		 */
		error2 = xfs_buf_ioरुको(bp);
		xfs_buf_rअन्यथा(bp);
		अगर (!error)
			error = error2;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Push a single buffer on a delwri queue.
 *
 * The purpose of this function is to submit a single buffer of a delwri queue
 * and वापस with the buffer still on the original queue. The रुकोing delwri
 * buffer submission infraकाष्ठाure guarantees transfer of the delwri queue
 * buffer reference to a temporary रुको list. We reuse this infraकाष्ठाure to
 * transfer the buffer back to the original queue.
 *
 * Note the buffer transitions from the queued state, to the submitted and रुको
 * listed state and back to the queued state during this call. The buffer
 * locking and queue management logic between _delwri_pushbuf() and
 * _delwri_queue() guarantee that the buffer cannot be queued to another list
 * beक्रमe वापसing.
 */
पूर्णांक
xfs_buf_delwri_pushbuf(
	काष्ठा xfs_buf		*bp,
	काष्ठा list_head	*buffer_list)
अणु
	LIST_HEAD		(submit_list);
	पूर्णांक			error;

	ASSERT(bp->b_flags & _XBF_DELWRI_Q);

	trace_xfs_buf_delwri_pushbuf(bp, _RET_IP_);

	/*
	 * Isolate the buffer to a new local list so we can submit it क्रम I/O
	 * independently from the rest of the original list.
	 */
	xfs_buf_lock(bp);
	list_move(&bp->b_list, &submit_list);
	xfs_buf_unlock(bp);

	/*
	 * Delwri submission clears the DELWRI_Q buffer flag and वापसs with
	 * the buffer on the रुको list with the original reference. Rather than
	 * bounce the buffer from a local रुको list back to the original list
	 * after I/O completion, reuse the original list as the रुको list.
	 */
	xfs_buf_delwri_submit_buffers(&submit_list, buffer_list);

	/*
	 * The buffer is now locked, under I/O and रुको listed on the original
	 * delwri queue. Wait क्रम I/O completion, restore the DELWRI_Q flag and
	 * वापस with the buffer unlocked and on the original queue.
	 */
	error = xfs_buf_ioरुको(bp);
	bp->b_flags |= _XBF_DELWRI_Q;
	xfs_buf_unlock(bp);

	वापस error;
पूर्ण

पूर्णांक __init
xfs_buf_init(व्योम)
अणु
	xfs_buf_zone = kmem_cache_create("xfs_buf", माप(काष्ठा xfs_buf), 0,
					 SLAB_HWCACHE_ALIGN |
					 SLAB_RECLAIM_ACCOUNT |
					 SLAB_MEM_SPREAD,
					 शून्य);
	अगर (!xfs_buf_zone)
		जाओ out;

	वापस 0;

 out:
	वापस -ENOMEM;
पूर्ण

व्योम
xfs_buf_terminate(व्योम)
अणु
	kmem_cache_destroy(xfs_buf_zone);
पूर्ण

व्योम xfs_buf_set_ref(काष्ठा xfs_buf *bp, पूर्णांक lru_ref)
अणु
	/*
	 * Set the lru reference count to 0 based on the error injection tag.
	 * This allows userspace to disrupt buffer caching क्रम debug/testing
	 * purposes.
	 */
	अगर (XFS_TEST_ERROR(false, bp->b_mount, XFS_ERRTAG_BUF_LRU_REF))
		lru_ref = 0;

	atomic_set(&bp->b_lru_ref, lru_ref);
पूर्ण

/*
 * Verअगरy an on-disk magic value against the magic value specअगरied in the
 * verअगरier काष्ठाure. The verअगरier magic is in disk byte order so the caller is
 * expected to pass the value directly from disk.
 */
bool
xfs_verअगरy_magic(
	काष्ठा xfs_buf		*bp,
	__be32			dmagic)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	पूर्णांक			idx;

	idx = xfs_sb_version_hascrc(&mp->m_sb);
	अगर (WARN_ON(!bp->b_ops || !bp->b_ops->magic[idx]))
		वापस false;
	वापस dmagic == bp->b_ops->magic[idx];
पूर्ण
/*
 * Verअगरy an on-disk magic value against the magic value specअगरied in the
 * verअगरier काष्ठाure. The verअगरier magic is in disk byte order so the caller is
 * expected to pass the value directly from disk.
 */
bool
xfs_verअगरy_magic16(
	काष्ठा xfs_buf		*bp,
	__be16			dmagic)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	पूर्णांक			idx;

	idx = xfs_sb_version_hascrc(&mp->m_sb);
	अगर (WARN_ON(!bp->b_ops || !bp->b_ops->magic16[idx]))
		वापस false;
	वापस dmagic == bp->b_ops->magic16[idx];
पूर्ण
