<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/core/xdp.c
 *
 * Copyright (c) 2017 Jesper Dangaard Brouer, Red Hat Inc.
 */
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/bug.h>
#समावेश <net/page_pool.h>

#समावेश <net/xdp.h>
#समावेश <net/xdp_priv.h> /* काष्ठा xdp_mem_allocator */
#समावेश <trace/events/xdp.h>
#समावेश <net/xdp_sock_drv.h>

#घोषणा REG_STATE_NEW		0x0
#घोषणा REG_STATE_REGISTERED	0x1
#घोषणा REG_STATE_UNREGISTERED	0x2
#घोषणा REG_STATE_UNUSED	0x3

अटल DEFINE_IDA(mem_id_pool);
अटल DEFINE_MUTEX(mem_id_lock);
#घोषणा MEM_ID_MAX 0xFFFE
#घोषणा MEM_ID_MIN 1
अटल पूर्णांक mem_id_next = MEM_ID_MIN;

अटल bool mem_id_init; /* false */
अटल काष्ठा rhashtable *mem_id_ht;

अटल u32 xdp_mem_id_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर u32 *k = data;
	स्थिर u32 key = *k;

	BUILD_BUG_ON(माप_field(काष्ठा xdp_mem_allocator, mem.id)
		     != माप(u32));

	/* Use cyclic increasing ID as direct hash key */
	वापस key;
पूर्ण

अटल पूर्णांक xdp_mem_id_cmp(काष्ठा rhashtable_compare_arg *arg,
			  स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा xdp_mem_allocator *xa = ptr;
	u32 mem_id = *(u32 *)arg->key;

	वापस xa->mem.id != mem_id;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mem_id_rht_params = अणु
	.nelem_hपूर्णांक = 64,
	.head_offset = दुरत्व(काष्ठा xdp_mem_allocator, node),
	.key_offset  = दुरत्व(काष्ठा xdp_mem_allocator, mem.id),
	.key_len = माप_field(काष्ठा xdp_mem_allocator, mem.id),
	.max_size = MEM_ID_MAX,
	.min_size = 8,
	.स्वतःmatic_shrinking = true,
	.hashfn    = xdp_mem_id_hashfn,
	.obj_cmpfn = xdp_mem_id_cmp,
पूर्ण;

अटल व्योम __xdp_mem_allocator_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा xdp_mem_allocator *xa;

	xa = container_of(rcu, काष्ठा xdp_mem_allocator, rcu);

	/* Allow this ID to be reused */
	ida_simple_हटाओ(&mem_id_pool, xa->mem.id);

	kमुक्त(xa);
पूर्ण

अटल व्योम mem_xa_हटाओ(काष्ठा xdp_mem_allocator *xa)
अणु
	trace_mem_disconnect(xa);

	अगर (!rhashtable_हटाओ_fast(mem_id_ht, &xa->node, mem_id_rht_params))
		call_rcu(&xa->rcu, __xdp_mem_allocator_rcu_मुक्त);
पूर्ण

अटल व्योम mem_allocator_disconnect(व्योम *allocator)
अणु
	काष्ठा xdp_mem_allocator *xa;
	काष्ठा rhashtable_iter iter;

	mutex_lock(&mem_id_lock);

	rhashtable_walk_enter(mem_id_ht, &iter);
	करो अणु
		rhashtable_walk_start(&iter);

		जबतक ((xa = rhashtable_walk_next(&iter)) && !IS_ERR(xa)) अणु
			अगर (xa->allocator == allocator)
				mem_xa_हटाओ(xa);
		पूर्ण

		rhashtable_walk_stop(&iter);

	पूर्ण जबतक (xa == ERR_PTR(-EAGAIN));
	rhashtable_walk_निकास(&iter);

	mutex_unlock(&mem_id_lock);
पूर्ण

व्योम xdp_rxq_info_unreg_mem_model(काष्ठा xdp_rxq_info *xdp_rxq)
अणु
	काष्ठा xdp_mem_allocator *xa;
	पूर्णांक id = xdp_rxq->mem.id;

	अगर (xdp_rxq->reg_state != REG_STATE_REGISTERED) अणु
		WARN(1, "Missing register, driver bug");
		वापस;
	पूर्ण

	अगर (id == 0)
		वापस;

	अगर (xdp_rxq->mem.type == MEM_TYPE_PAGE_POOL) अणु
		rcu_पढ़ो_lock();
		xa = rhashtable_lookup(mem_id_ht, &id, mem_id_rht_params);
		page_pool_destroy(xa->page_pool);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_unreg_mem_model);

व्योम xdp_rxq_info_unreg(काष्ठा xdp_rxq_info *xdp_rxq)
अणु
	/* Simplअगरy driver cleanup code paths, allow unreg "unused" */
	अगर (xdp_rxq->reg_state == REG_STATE_UNUSED)
		वापस;

	WARN(!(xdp_rxq->reg_state == REG_STATE_REGISTERED), "Driver BUG");

	xdp_rxq_info_unreg_mem_model(xdp_rxq);

	xdp_rxq->reg_state = REG_STATE_UNREGISTERED;
	xdp_rxq->dev = शून्य;

	/* Reset mem info to शेषs */
	xdp_rxq->mem.id = 0;
	xdp_rxq->mem.type = 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_unreg);

अटल व्योम xdp_rxq_info_init(काष्ठा xdp_rxq_info *xdp_rxq)
अणु
	स_रखो(xdp_rxq, 0, माप(*xdp_rxq));
पूर्ण

/* Returns 0 on success, negative on failure */
पूर्णांक xdp_rxq_info_reg(काष्ठा xdp_rxq_info *xdp_rxq,
		     काष्ठा net_device *dev, u32 queue_index, अचिन्हित पूर्णांक napi_id)
अणु
	अगर (xdp_rxq->reg_state == REG_STATE_UNUSED) अणु
		WARN(1, "Driver promised not to register this");
		वापस -EINVAL;
	पूर्ण

	अगर (xdp_rxq->reg_state == REG_STATE_REGISTERED) अणु
		WARN(1, "Missing unregister, handled but fix driver");
		xdp_rxq_info_unreg(xdp_rxq);
	पूर्ण

	अगर (!dev) अणु
		WARN(1, "Missing net_device from driver");
		वापस -ENODEV;
	पूर्ण

	/* State either UNREGISTERED or NEW */
	xdp_rxq_info_init(xdp_rxq);
	xdp_rxq->dev = dev;
	xdp_rxq->queue_index = queue_index;
	xdp_rxq->napi_id = napi_id;

	xdp_rxq->reg_state = REG_STATE_REGISTERED;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_reg);

व्योम xdp_rxq_info_unused(काष्ठा xdp_rxq_info *xdp_rxq)
अणु
	xdp_rxq->reg_state = REG_STATE_UNUSED;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_unused);

bool xdp_rxq_info_is_reg(काष्ठा xdp_rxq_info *xdp_rxq)
अणु
	वापस (xdp_rxq->reg_state == REG_STATE_REGISTERED);
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_is_reg);

अटल पूर्णांक __mem_id_init_hash_table(व्योम)
अणु
	काष्ठा rhashtable *rht;
	पूर्णांक ret;

	अगर (unlikely(mem_id_init))
		वापस 0;

	rht = kzalloc(माप(*rht), GFP_KERNEL);
	अगर (!rht)
		वापस -ENOMEM;

	ret = rhashtable_init(rht, &mem_id_rht_params);
	अगर (ret < 0) अणु
		kमुक्त(rht);
		वापस ret;
	पूर्ण
	mem_id_ht = rht;
	smp_mb(); /* mutex lock should provide enough pairing */
	mem_id_init = true;

	वापस 0;
पूर्ण

/* Allocate a cyclic ID that maps to allocator poपूर्णांकer.
 * See: https://www.kernel.org/करोc/hपंचांगl/latest/core-api/idr.hपंचांगl
 *
 * Caller must lock mem_id_lock.
 */
अटल पूर्णांक __mem_id_cyclic_get(gfp_t gfp)
अणु
	पूर्णांक retries = 1;
	पूर्णांक id;

again:
	id = ida_simple_get(&mem_id_pool, mem_id_next, MEM_ID_MAX, gfp);
	अगर (id < 0) अणु
		अगर (id == -ENOSPC) अणु
			/* Cyclic allocator, reset next id */
			अगर (retries--) अणु
				mem_id_next = MEM_ID_MIN;
				जाओ again;
			पूर्ण
		पूर्ण
		वापस id; /* त्रुटि_सं */
	पूर्ण
	mem_id_next = id + 1;

	वापस id;
पूर्ण

अटल bool __is_supported_mem_type(क्रमागत xdp_mem_type type)
अणु
	अगर (type == MEM_TYPE_PAGE_POOL)
		वापस is_page_pool_compiled_in();

	अगर (type >= MEM_TYPE_MAX)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक xdp_rxq_info_reg_mem_model(काष्ठा xdp_rxq_info *xdp_rxq,
			       क्रमागत xdp_mem_type type, व्योम *allocator)
अणु
	काष्ठा xdp_mem_allocator *xdp_alloc;
	gfp_t gfp = GFP_KERNEL;
	पूर्णांक id, त्रुटि_सं, ret;
	व्योम *ptr;

	अगर (xdp_rxq->reg_state != REG_STATE_REGISTERED) अणु
		WARN(1, "Missing register, driver bug");
		वापस -EFAULT;
	पूर्ण

	अगर (!__is_supported_mem_type(type))
		वापस -EOPNOTSUPP;

	xdp_rxq->mem.type = type;

	अगर (!allocator) अणु
		अगर (type == MEM_TYPE_PAGE_POOL)
			वापस -EINVAL; /* Setup समय check page_pool req */
		वापस 0;
	पूर्ण

	/* Delay init of rhashtable to save memory अगर feature isn't used */
	अगर (!mem_id_init) अणु
		mutex_lock(&mem_id_lock);
		ret = __mem_id_init_hash_table();
		mutex_unlock(&mem_id_lock);
		अगर (ret < 0) अणु
			WARN_ON(1);
			वापस ret;
		पूर्ण
	पूर्ण

	xdp_alloc = kzalloc(माप(*xdp_alloc), gfp);
	अगर (!xdp_alloc)
		वापस -ENOMEM;

	mutex_lock(&mem_id_lock);
	id = __mem_id_cyclic_get(gfp);
	अगर (id < 0) अणु
		त्रुटि_सं = id;
		जाओ err;
	पूर्ण
	xdp_rxq->mem.id = id;
	xdp_alloc->mem  = xdp_rxq->mem;
	xdp_alloc->allocator = allocator;

	/* Insert allocator पूर्णांकo ID lookup table */
	ptr = rhashtable_insert_slow(mem_id_ht, &id, &xdp_alloc->node);
	अगर (IS_ERR(ptr)) अणु
		ida_simple_हटाओ(&mem_id_pool, xdp_rxq->mem.id);
		xdp_rxq->mem.id = 0;
		त्रुटि_सं = PTR_ERR(ptr);
		जाओ err;
	पूर्ण

	अगर (type == MEM_TYPE_PAGE_POOL)
		page_pool_use_xdp_mem(allocator, mem_allocator_disconnect);

	mutex_unlock(&mem_id_lock);

	trace_mem_connect(xdp_alloc, xdp_rxq);
	वापस 0;
err:
	mutex_unlock(&mem_id_lock);
	kमुक्त(xdp_alloc);
	वापस त्रुटि_सं;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_rxq_info_reg_mem_model);

/* XDP RX runs under NAPI protection, and in dअगरferent delivery error
 * scenarios (e.g. queue full), it is possible to वापस the xdp_frame
 * जबतक still leveraging this protection.  The @napi_direct boolean
 * is used क्रम those calls sites.  Thus, allowing क्रम faster recycling
 * of xdp_frames/pages in those हालs.
 */
अटल व्योम __xdp_वापस(व्योम *data, काष्ठा xdp_mem_info *mem, bool napi_direct,
			 काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_mem_allocator *xa;
	काष्ठा page *page;

	चयन (mem->type) अणु
	हाल MEM_TYPE_PAGE_POOL:
		rcu_पढ़ो_lock();
		/* mem->id is valid, checked in xdp_rxq_info_reg_mem_model() */
		xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
		page = virt_to_head_page(data);
		अगर (napi_direct && xdp_वापस_frame_no_direct())
			napi_direct = false;
		page_pool_put_full_page(xa->page_pool, page, napi_direct);
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल MEM_TYPE_PAGE_SHARED:
		page_frag_मुक्त(data);
		अवरोध;
	हाल MEM_TYPE_PAGE_ORDER0:
		page = virt_to_page(data); /* Assumes order0 page*/
		put_page(page);
		अवरोध;
	हाल MEM_TYPE_XSK_BUFF_POOL:
		/* NB! Only valid from an xdp_buff! */
		xsk_buff_मुक्त(xdp);
		अवरोध;
	शेष:
		/* Not possible, checked in xdp_rxq_info_reg_mem_model() */
		WARN(1, "Incorrect XDP memory type (%d) usage", mem->type);
		अवरोध;
	पूर्ण
पूर्ण

व्योम xdp_वापस_frame(काष्ठा xdp_frame *xdpf)
अणु
	__xdp_वापस(xdpf->data, &xdpf->mem, false, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(xdp_वापस_frame);

व्योम xdp_वापस_frame_rx_napi(काष्ठा xdp_frame *xdpf)
अणु
	__xdp_वापस(xdpf->data, &xdpf->mem, true, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(xdp_वापस_frame_rx_napi);

/* XDP bulk APIs पूर्णांकroduce a defer/flush mechanism to वापस
 * pages beदीर्घing to the same xdp_mem_allocator object
 * (identअगरied via the mem.id field) in bulk to optimize
 * I-cache and D-cache.
 * The bulk queue size is set to 16 to be aligned to how
 * XDP_REसूचीECT bulking works. The bulk is flushed when
 * it is full or when mem.id changes.
 * xdp_frame_bulk is usually stored/allocated on the function
 * call-stack to aव्योम locking penalties.
 */
व्योम xdp_flush_frame_bulk(काष्ठा xdp_frame_bulk *bq)
अणु
	काष्ठा xdp_mem_allocator *xa = bq->xa;

	अगर (unlikely(!xa || !bq->count))
		वापस;

	page_pool_put_page_bulk(xa->page_pool, bq->q, bq->count);
	/* bq->xa is not cleared to save lookup, अगर mem.id same in next bulk */
	bq->count = 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_flush_frame_bulk);

/* Must be called with rcu_पढ़ो_lock held */
व्योम xdp_वापस_frame_bulk(काष्ठा xdp_frame *xdpf,
			   काष्ठा xdp_frame_bulk *bq)
अणु
	काष्ठा xdp_mem_info *mem = &xdpf->mem;
	काष्ठा xdp_mem_allocator *xa;

	अगर (mem->type != MEM_TYPE_PAGE_POOL) अणु
		__xdp_वापस(xdpf->data, &xdpf->mem, false, शून्य);
		वापस;
	पूर्ण

	xa = bq->xa;
	अगर (unlikely(!xa)) अणु
		xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
		bq->count = 0;
		bq->xa = xa;
	पूर्ण

	अगर (bq->count == XDP_BULK_QUEUE_SIZE)
		xdp_flush_frame_bulk(bq);

	अगर (unlikely(mem->id != xa->mem.id)) अणु
		xdp_flush_frame_bulk(bq);
		bq->xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
	पूर्ण

	bq->q[bq->count++] = xdpf->data;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_वापस_frame_bulk);

व्योम xdp_वापस_buff(काष्ठा xdp_buff *xdp)
अणु
	__xdp_वापस(xdp->data, &xdp->rxq->mem, true, xdp);
पूर्ण

/* Only called क्रम MEM_TYPE_PAGE_POOL see xdp.h */
व्योम __xdp_release_frame(व्योम *data, काष्ठा xdp_mem_info *mem)
अणु
	काष्ठा xdp_mem_allocator *xa;
	काष्ठा page *page;

	rcu_पढ़ो_lock();
	xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
	page = virt_to_head_page(data);
	अगर (xa)
		page_pool_release_page(xa->page_pool, page);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(__xdp_release_frame);

व्योम xdp_attachment_setup(काष्ठा xdp_attachment_info *info,
			  काष्ठा netdev_bpf *bpf)
अणु
	अगर (info->prog)
		bpf_prog_put(info->prog);
	info->prog = bpf->prog;
	info->flags = bpf->flags;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_attachment_setup);

काष्ठा xdp_frame *xdp_convert_zc_to_xdp_frame(काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक metasize, totsize;
	व्योम *addr, *data_to_copy;
	काष्ठा xdp_frame *xdpf;
	काष्ठा page *page;

	/* Clone पूर्णांकo a MEM_TYPE_PAGE_ORDER0 xdp_frame. */
	metasize = xdp_data_meta_unsupported(xdp) ? 0 :
		   xdp->data - xdp->data_meta;
	totsize = xdp->data_end - xdp->data + metasize;

	अगर (माप(*xdpf) + totsize > PAGE_SIZE)
		वापस शून्य;

	page = dev_alloc_page();
	अगर (!page)
		वापस शून्य;

	addr = page_to_virt(page);
	xdpf = addr;
	स_रखो(xdpf, 0, माप(*xdpf));

	addr += माप(*xdpf);
	data_to_copy = metasize ? xdp->data_meta : xdp->data;
	स_नकल(addr, data_to_copy, totsize);

	xdpf->data = addr + metasize;
	xdpf->len = totsize - metasize;
	xdpf->headroom = 0;
	xdpf->metasize = metasize;
	xdpf->frame_sz = PAGE_SIZE;
	xdpf->mem.type = MEM_TYPE_PAGE_ORDER0;

	xsk_buff_मुक्त(xdp);
	वापस xdpf;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_convert_zc_to_xdp_frame);

/* Used by XDP_WARN macro, to aव्योम inlining WARN() in fast-path */
व्योम xdp_warn(स्थिर अक्षर *msg, स्थिर अक्षर *func, स्थिर पूर्णांक line)
अणु
	WARN(1, "XDP_WARN: %s(line:%d): %s\n", func, line, msg);
पूर्ण;
EXPORT_SYMBOL_GPL(xdp_warn);

पूर्णांक xdp_alloc_skb_bulk(व्योम **skbs, पूर्णांक n_skb, gfp_t gfp)
अणु
	n_skb = kmem_cache_alloc_bulk(skbuff_head_cache, gfp,
				      n_skb, skbs);
	अगर (unlikely(!n_skb))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_alloc_skb_bulk);

काष्ठा sk_buff *__xdp_build_skb_from_frame(काष्ठा xdp_frame *xdpf,
					   काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक headroom, frame_size;
	व्योम *hard_start;

	/* Part of headroom was reserved to xdpf */
	headroom = माप(*xdpf) + xdpf->headroom;

	/* Memory size backing xdp_frame data alपढ़ोy have reserved
	 * room क्रम build_skb to place skb_shared_info in tailroom.
	 */
	frame_size = xdpf->frame_sz;

	hard_start = xdpf->data - headroom;
	skb = build_skb_around(skb, hard_start, frame_size);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_reserve(skb, headroom);
	__skb_put(skb, xdpf->len);
	अगर (xdpf->metasize)
		skb_metadata_set(skb, xdpf->metasize);

	/* Essential SKB info: protocol and skb->dev */
	skb->protocol = eth_type_trans(skb, dev);

	/* Optional SKB info, currently missing:
	 * - HW checksum info		(skb->ip_summed)
	 * - HW RX hash			(skb_set_hash)
	 * - RX ring dev queue index	(skb_record_rx_queue)
	 */

	/* Until page_pool get SKB वापस path, release DMA here */
	xdp_release_frame(xdpf);

	/* Allow SKB to reuse area used by xdp_frame */
	xdp_scrub_frame(xdpf);

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(__xdp_build_skb_from_frame);

काष्ठा sk_buff *xdp_build_skb_from_frame(काष्ठा xdp_frame *xdpf,
					 काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb;

	skb = kmem_cache_alloc(skbuff_head_cache, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस शून्य;

	स_रखो(skb, 0, दुरत्व(काष्ठा sk_buff, tail));

	वापस __xdp_build_skb_from_frame(xdpf, skb, dev);
पूर्ण
EXPORT_SYMBOL_GPL(xdp_build_skb_from_frame);
