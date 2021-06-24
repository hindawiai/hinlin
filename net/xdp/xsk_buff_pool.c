<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <net/xsk_buff_pool.h>
#समावेश <net/xdp_sock.h>
#समावेश <net/xdp_sock_drv.h>

#समावेश "xsk_queue.h"
#समावेश "xdp_umem.h"
#समावेश "xsk.h"

व्योम xp_add_xsk(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_sock *xs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!xs->tx)
		वापस;

	spin_lock_irqsave(&pool->xsk_tx_list_lock, flags);
	list_add_rcu(&xs->tx_list, &pool->xsk_tx_list);
	spin_unlock_irqrestore(&pool->xsk_tx_list_lock, flags);
पूर्ण

व्योम xp_del_xsk(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_sock *xs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!xs->tx)
		वापस;

	spin_lock_irqsave(&pool->xsk_tx_list_lock, flags);
	list_del_rcu(&xs->tx_list);
	spin_unlock_irqrestore(&pool->xsk_tx_list_lock, flags);
पूर्ण

व्योम xp_destroy(काष्ठा xsk_buff_pool *pool)
अणु
	अगर (!pool)
		वापस;

	kvमुक्त(pool->heads);
	kvमुक्त(pool);
पूर्ण

काष्ठा xsk_buff_pool *xp_create_and_assign_umem(काष्ठा xdp_sock *xs,
						काष्ठा xdp_umem *umem)
अणु
	काष्ठा xsk_buff_pool *pool;
	काष्ठा xdp_buff_xsk *xskb;
	u32 i;

	pool = kvzalloc(काष्ठा_size(pool, मुक्त_heads, umem->chunks),
			GFP_KERNEL);
	अगर (!pool)
		जाओ out;

	pool->heads = kvसुस्मृति(umem->chunks, माप(*pool->heads), GFP_KERNEL);
	अगर (!pool->heads)
		जाओ out;

	pool->chunk_mask = ~((u64)umem->chunk_size - 1);
	pool->addrs_cnt = umem->size;
	pool->heads_cnt = umem->chunks;
	pool->मुक्त_heads_cnt = umem->chunks;
	pool->headroom = umem->headroom;
	pool->chunk_size = umem->chunk_size;
	pool->unaligned = umem->flags & XDP_UMEM_UNALIGNED_CHUNK_FLAG;
	pool->frame_len = umem->chunk_size - umem->headroom -
		XDP_PACKET_HEADROOM;
	pool->umem = umem;
	pool->addrs = umem->addrs;
	INIT_LIST_HEAD(&pool->मुक्त_list);
	INIT_LIST_HEAD(&pool->xsk_tx_list);
	spin_lock_init(&pool->xsk_tx_list_lock);
	spin_lock_init(&pool->cq_lock);
	refcount_set(&pool->users, 1);

	pool->fq = xs->fq_पंचांगp;
	pool->cq = xs->cq_पंचांगp;

	क्रम (i = 0; i < pool->मुक्त_heads_cnt; i++) अणु
		xskb = &pool->heads[i];
		xskb->pool = pool;
		xskb->xdp.frame_sz = umem->chunk_size - umem->headroom;
		pool->मुक्त_heads[i] = xskb;
	पूर्ण

	वापस pool;

out:
	xp_destroy(pool);
	वापस शून्य;
पूर्ण

व्योम xp_set_rxq_info(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_rxq_info *rxq)
अणु
	u32 i;

	क्रम (i = 0; i < pool->heads_cnt; i++)
		pool->heads[i].xdp.rxq = rxq;
पूर्ण
EXPORT_SYMBOL(xp_set_rxq_info);

अटल व्योम xp_disable_drv_zc(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा netdev_bpf bpf;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (pool->umem->zc) अणु
		bpf.command = XDP_SETUP_XSK_POOL;
		bpf.xsk.pool = शून्य;
		bpf.xsk.queue_id = pool->queue_id;

		err = pool->netdev->netdev_ops->nकरो_bpf(pool->netdev, &bpf);

		अगर (err)
			WARN(1, "Failed to disable zero-copy!\n");
	पूर्ण
पूर्ण

पूर्णांक xp_assign_dev(काष्ठा xsk_buff_pool *pool,
		  काष्ठा net_device *netdev, u16 queue_id, u16 flags)
अणु
	bool क्रमce_zc, क्रमce_copy;
	काष्ठा netdev_bpf bpf;
	पूर्णांक err = 0;

	ASSERT_RTNL();

	क्रमce_zc = flags & XDP_ZEROCOPY;
	क्रमce_copy = flags & XDP_COPY;

	अगर (क्रमce_zc && क्रमce_copy)
		वापस -EINVAL;

	अगर (xsk_get_pool_from_qid(netdev, queue_id))
		वापस -EBUSY;

	pool->netdev = netdev;
	pool->queue_id = queue_id;
	err = xsk_reg_pool_at_qid(netdev, pool, queue_id);
	अगर (err)
		वापस err;

	अगर (flags & XDP_USE_NEED_WAKEUP)
		pool->uses_need_wakeup = true;
	/* Tx needs to be explicitly woken up the first समय.  Also
	 * क्रम supporting drivers that करो not implement this
	 * feature. They will always have to call sendto() or poll().
	 */
	pool->cached_need_wakeup = XDP_WAKEUP_TX;

	dev_hold(netdev);

	अगर (क्रमce_copy)
		/* For copy-mode, we are करोne. */
		वापस 0;

	अगर (!netdev->netdev_ops->nकरो_bpf ||
	    !netdev->netdev_ops->nकरो_xsk_wakeup) अणु
		err = -EOPNOTSUPP;
		जाओ err_unreg_pool;
	पूर्ण

	bpf.command = XDP_SETUP_XSK_POOL;
	bpf.xsk.pool = pool;
	bpf.xsk.queue_id = queue_id;

	err = netdev->netdev_ops->nकरो_bpf(netdev, &bpf);
	अगर (err)
		जाओ err_unreg_pool;

	अगर (!pool->dma_pages) अणु
		WARN(1, "Driver did not DMA map zero-copy buffers");
		err = -EINVAL;
		जाओ err_unreg_xsk;
	पूर्ण
	pool->umem->zc = true;
	वापस 0;

err_unreg_xsk:
	xp_disable_drv_zc(pool);
err_unreg_pool:
	अगर (!क्रमce_zc)
		err = 0; /* fallback to copy mode */
	अगर (err) अणु
		xsk_clear_pool_at_qid(netdev, queue_id);
		dev_put(netdev);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक xp_assign_dev_shared(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_umem *umem,
			 काष्ठा net_device *dev, u16 queue_id)
अणु
	u16 flags;

	/* One fill and completion ring required क्रम each queue id. */
	अगर (!pool->fq || !pool->cq)
		वापस -EINVAL;

	flags = umem->zc ? XDP_ZEROCOPY : XDP_COPY;
	अगर (pool->uses_need_wakeup)
		flags |= XDP_USE_NEED_WAKEUP;

	वापस xp_assign_dev(pool, dev, queue_id, flags);
पूर्ण

व्योम xp_clear_dev(काष्ठा xsk_buff_pool *pool)
अणु
	अगर (!pool->netdev)
		वापस;

	xp_disable_drv_zc(pool);
	xsk_clear_pool_at_qid(pool->netdev, pool->queue_id);
	dev_put(pool->netdev);
	pool->netdev = शून्य;
पूर्ण

अटल व्योम xp_release_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xsk_buff_pool *pool = container_of(work, काष्ठा xsk_buff_pool,
						  work);

	rtnl_lock();
	xp_clear_dev(pool);
	rtnl_unlock();

	अगर (pool->fq) अणु
		xskq_destroy(pool->fq);
		pool->fq = शून्य;
	पूर्ण

	अगर (pool->cq) अणु
		xskq_destroy(pool->cq);
		pool->cq = शून्य;
	पूर्ण

	xdp_put_umem(pool->umem, false);
	xp_destroy(pool);
पूर्ण

व्योम xp_get_pool(काष्ठा xsk_buff_pool *pool)
अणु
	refcount_inc(&pool->users);
पूर्ण

bool xp_put_pool(काष्ठा xsk_buff_pool *pool)
अणु
	अगर (!pool)
		वापस false;

	अगर (refcount_dec_and_test(&pool->users)) अणु
		INIT_WORK(&pool->work, xp_release_deferred);
		schedule_work(&pool->work);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा xsk_dma_map *xp_find_dma_map(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xsk_dma_map *dma_map;

	list_क्रम_each_entry(dma_map, &pool->umem->xsk_dma_list, list) अणु
		अगर (dma_map->netdev == pool->netdev)
			वापस dma_map;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा xsk_dma_map *xp_create_dma_map(काष्ठा device *dev, काष्ठा net_device *netdev,
					     u32 nr_pages, काष्ठा xdp_umem *umem)
अणु
	काष्ठा xsk_dma_map *dma_map;

	dma_map = kzalloc(माप(*dma_map), GFP_KERNEL);
	अगर (!dma_map)
		वापस शून्य;

	dma_map->dma_pages = kvसुस्मृति(nr_pages, माप(*dma_map->dma_pages), GFP_KERNEL);
	अगर (!dma_map->dma_pages) अणु
		kमुक्त(dma_map);
		वापस शून्य;
	पूर्ण

	dma_map->netdev = netdev;
	dma_map->dev = dev;
	dma_map->dma_need_sync = false;
	dma_map->dma_pages_cnt = nr_pages;
	refcount_set(&dma_map->users, 1);
	list_add(&dma_map->list, &umem->xsk_dma_list);
	वापस dma_map;
पूर्ण

अटल व्योम xp_destroy_dma_map(काष्ठा xsk_dma_map *dma_map)
अणु
	list_del(&dma_map->list);
	kvमुक्त(dma_map->dma_pages);
	kमुक्त(dma_map);
पूर्ण

अटल व्योम __xp_dma_unmap(काष्ठा xsk_dma_map *dma_map, अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t *dma;
	u32 i;

	क्रम (i = 0; i < dma_map->dma_pages_cnt; i++) अणु
		dma = &dma_map->dma_pages[i];
		अगर (*dma) अणु
			dma_unmap_page_attrs(dma_map->dev, *dma, PAGE_SIZE,
					     DMA_BIसूचीECTIONAL, attrs);
			*dma = 0;
		पूर्ण
	पूर्ण

	xp_destroy_dma_map(dma_map);
पूर्ण

व्योम xp_dma_unmap(काष्ठा xsk_buff_pool *pool, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा xsk_dma_map *dma_map;

	अगर (pool->dma_pages_cnt == 0)
		वापस;

	dma_map = xp_find_dma_map(pool);
	अगर (!dma_map) अणु
		WARN(1, "Could not find dma_map for device");
		वापस;
	पूर्ण

	अगर (!refcount_dec_and_test(&dma_map->users))
		वापस;

	__xp_dma_unmap(dma_map, attrs);
	kvमुक्त(pool->dma_pages);
	pool->dma_pages_cnt = 0;
	pool->dev = शून्य;
पूर्ण
EXPORT_SYMBOL(xp_dma_unmap);

अटल व्योम xp_check_dma_contiguity(काष्ठा xsk_dma_map *dma_map)
अणु
	u32 i;

	क्रम (i = 0; i < dma_map->dma_pages_cnt - 1; i++) अणु
		अगर (dma_map->dma_pages[i] + PAGE_SIZE == dma_map->dma_pages[i + 1])
			dma_map->dma_pages[i] |= XSK_NEXT_PG_CONTIG_MASK;
		अन्यथा
			dma_map->dma_pages[i] &= ~XSK_NEXT_PG_CONTIG_MASK;
	पूर्ण
पूर्ण

अटल पूर्णांक xp_init_dma_info(काष्ठा xsk_buff_pool *pool, काष्ठा xsk_dma_map *dma_map)
अणु
	pool->dma_pages = kvसुस्मृति(dma_map->dma_pages_cnt, माप(*pool->dma_pages), GFP_KERNEL);
	अगर (!pool->dma_pages)
		वापस -ENOMEM;

	pool->dev = dma_map->dev;
	pool->dma_pages_cnt = dma_map->dma_pages_cnt;
	pool->dma_need_sync = dma_map->dma_need_sync;
	स_नकल(pool->dma_pages, dma_map->dma_pages,
	       pool->dma_pages_cnt * माप(*pool->dma_pages));

	वापस 0;
पूर्ण

पूर्णांक xp_dma_map(काष्ठा xsk_buff_pool *pool, काष्ठा device *dev,
	       अचिन्हित दीर्घ attrs, काष्ठा page **pages, u32 nr_pages)
अणु
	काष्ठा xsk_dma_map *dma_map;
	dma_addr_t dma;
	पूर्णांक err;
	u32 i;

	dma_map = xp_find_dma_map(pool);
	अगर (dma_map) अणु
		err = xp_init_dma_info(pool, dma_map);
		अगर (err)
			वापस err;

		refcount_inc(&dma_map->users);
		वापस 0;
	पूर्ण

	dma_map = xp_create_dma_map(dev, pool->netdev, nr_pages, pool->umem);
	अगर (!dma_map)
		वापस -ENOMEM;

	क्रम (i = 0; i < dma_map->dma_pages_cnt; i++) अणु
		dma = dma_map_page_attrs(dev, pages[i], 0, PAGE_SIZE,
					 DMA_BIसूचीECTIONAL, attrs);
		अगर (dma_mapping_error(dev, dma)) अणु
			__xp_dma_unmap(dma_map, attrs);
			वापस -ENOMEM;
		पूर्ण
		अगर (dma_need_sync(dev, dma))
			dma_map->dma_need_sync = true;
		dma_map->dma_pages[i] = dma;
	पूर्ण

	अगर (pool->unaligned)
		xp_check_dma_contiguity(dma_map);

	err = xp_init_dma_info(pool, dma_map);
	अगर (err) अणु
		__xp_dma_unmap(dma_map, attrs);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xp_dma_map);

अटल bool xp_addr_crosses_non_contig_pg(काष्ठा xsk_buff_pool *pool,
					  u64 addr)
अणु
	वापस xp_desc_crosses_non_contig_pg(pool, addr, pool->chunk_size);
पूर्ण

अटल bool xp_check_unaligned(काष्ठा xsk_buff_pool *pool, u64 *addr)
अणु
	*addr = xp_unaligned_extract_addr(*addr);
	अगर (*addr >= pool->addrs_cnt ||
	    *addr + pool->chunk_size > pool->addrs_cnt ||
	    xp_addr_crosses_non_contig_pg(pool, *addr))
		वापस false;
	वापस true;
पूर्ण

अटल bool xp_check_aligned(काष्ठा xsk_buff_pool *pool, u64 *addr)
अणु
	*addr = xp_aligned_extract_addr(pool, *addr);
	वापस *addr < pool->addrs_cnt;
पूर्ण

अटल काष्ठा xdp_buff_xsk *__xp_alloc(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_buff_xsk *xskb;
	u64 addr;
	bool ok;

	अगर (pool->मुक्त_heads_cnt == 0)
		वापस शून्य;

	xskb = pool->मुक्त_heads[--pool->मुक्त_heads_cnt];

	क्रम (;;) अणु
		अगर (!xskq_cons_peek_addr_unchecked(pool->fq, &addr)) अणु
			pool->fq->queue_empty_descs++;
			xp_release(xskb);
			वापस शून्य;
		पूर्ण

		ok = pool->unaligned ? xp_check_unaligned(pool, &addr) :
		     xp_check_aligned(pool, &addr);
		अगर (!ok) अणु
			pool->fq->invalid_descs++;
			xskq_cons_release(pool->fq);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	xskq_cons_release(pool->fq);

	xskb->orig_addr = addr;
	xskb->xdp.data_hard_start = pool->addrs + addr + pool->headroom;
	अगर (pool->dma_pages_cnt) अणु
		xskb->frame_dma = (pool->dma_pages[addr >> PAGE_SHIFT] &
				   ~XSK_NEXT_PG_CONTIG_MASK) +
				  (addr & ~PAGE_MASK);
		xskb->dma = xskb->frame_dma + pool->headroom +
			    XDP_PACKET_HEADROOM;
	पूर्ण
	वापस xskb;
पूर्ण

काष्ठा xdp_buff *xp_alloc(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_buff_xsk *xskb;

	अगर (!pool->मुक्त_list_cnt) अणु
		xskb = __xp_alloc(pool);
		अगर (!xskb)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		pool->मुक्त_list_cnt--;
		xskb = list_first_entry(&pool->मुक्त_list, काष्ठा xdp_buff_xsk,
					मुक्त_list_node);
		list_del(&xskb->मुक्त_list_node);
	पूर्ण

	xskb->xdp.data = xskb->xdp.data_hard_start + XDP_PACKET_HEADROOM;
	xskb->xdp.data_meta = xskb->xdp.data;

	अगर (pool->dma_need_sync) अणु
		dma_sync_single_range_क्रम_device(pool->dev, xskb->dma, 0,
						 pool->frame_len,
						 DMA_BIसूचीECTIONAL);
	पूर्ण
	वापस &xskb->xdp;
पूर्ण
EXPORT_SYMBOL(xp_alloc);

bool xp_can_alloc(काष्ठा xsk_buff_pool *pool, u32 count)
अणु
	अगर (pool->मुक्त_list_cnt >= count)
		वापस true;
	वापस xskq_cons_has_entries(pool->fq, count - pool->मुक्त_list_cnt);
पूर्ण
EXPORT_SYMBOL(xp_can_alloc);

व्योम xp_मुक्त(काष्ठा xdp_buff_xsk *xskb)
अणु
	xskb->pool->मुक्त_list_cnt++;
	list_add(&xskb->मुक्त_list_node, &xskb->pool->मुक्त_list);
पूर्ण
EXPORT_SYMBOL(xp_मुक्त);

व्योम *xp_raw_get_data(काष्ठा xsk_buff_pool *pool, u64 addr)
अणु
	addr = pool->unaligned ? xp_unaligned_add_offset_to_addr(addr) : addr;
	वापस pool->addrs + addr;
पूर्ण
EXPORT_SYMBOL(xp_raw_get_data);

dma_addr_t xp_raw_get_dma(काष्ठा xsk_buff_pool *pool, u64 addr)
अणु
	addr = pool->unaligned ? xp_unaligned_add_offset_to_addr(addr) : addr;
	वापस (pool->dma_pages[addr >> PAGE_SHIFT] &
		~XSK_NEXT_PG_CONTIG_MASK) +
		(addr & ~PAGE_MASK);
पूर्ण
EXPORT_SYMBOL(xp_raw_get_dma);

व्योम xp_dma_sync_क्रम_cpu_slow(काष्ठा xdp_buff_xsk *xskb)
अणु
	dma_sync_single_range_क्रम_cpu(xskb->pool->dev, xskb->dma, 0,
				      xskb->pool->frame_len, DMA_BIसूचीECTIONAL);
पूर्ण
EXPORT_SYMBOL(xp_dma_sync_क्रम_cpu_slow);

व्योम xp_dma_sync_क्रम_device_slow(काष्ठा xsk_buff_pool *pool, dma_addr_t dma,
				 माप_प्रकार size)
अणु
	dma_sync_single_range_क्रम_device(pool->dev, dma, 0,
					 size, DMA_BIसूचीECTIONAL);
पूर्ण
EXPORT_SYMBOL(xp_dma_sync_क्रम_device_slow);
