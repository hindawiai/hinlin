<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Routines having to करो with the 'struct sk_buff' memory handlers.
 *
 *	Authors:	Alan Cox <alan@lxorguk.ukuu.org.uk>
 *			Florian La Roche <rzsfl@rz.uni-sb.de>
 *
 *	Fixes:
 *		Alan Cox	:	Fixed the worst of the load
 *					balancer bugs.
 *		Dave Platt	:	Interrupt stacking fix.
 *	Riअक्षरd Kooijman	:	Timestamp fixes.
 *		Alan Cox	:	Changed buffer क्रमmat.
 *		Alan Cox	:	deकाष्ठाor hook क्रम AF_UNIX etc.
 *		Linus Torvalds	:	Better skb_clone.
 *		Alan Cox	:	Added skb_copy.
 *		Alan Cox	:	Added all the changed routines Linus
 *					only put in the headers
 *		Ray VanTassle	:	Fixed --skb->lock in मुक्त
 *		Alan Cox	:	skb_copy copy arp field
 *		Andi Kleen	:	slabअगरied it.
 *		Robert Olsson	:	Removed skb_head_pool
 *
 *	NOTE:
 *		The __skb_ routines should be called with पूर्णांकerrupts
 *	disabled, or you better be *real* sure that the operation is atomic
 *	with respect to whatever list is being frobbed (e.g. via lock_sock()
 *	or via disabling bottom half handlers, etc).
 */

/*
 *	The functions in this file will not compile correctly with gcc 2.4.x
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/netdevice.h>
#अगर_घोषित CONFIG_NET_CLS_ACT
#समावेश <net/pkt_sched.h>
#पूर्ण_अगर
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/splice.h>
#समावेश <linux/cache.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mpls.h>
#समावेश <linux/kcov.h>

#समावेश <net/protocol.h>
#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/xfrm.h>
#समावेश <net/mpls.h>
#समावेश <net/mptcp.h>

#समावेश <linux/uaccess.h>
#समावेश <trace/events/skb.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/capability.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश "datagram.h"

काष्ठा kmem_cache *skbuff_head_cache __ro_after_init;
अटल काष्ठा kmem_cache *skbuff_fclone_cache __ro_after_init;
#अगर_घोषित CONFIG_SKB_EXTENSIONS
अटल काष्ठा kmem_cache *skbuff_ext_cache __ro_after_init;
#पूर्ण_अगर
पूर्णांक sysctl_max_skb_frags __पढ़ो_mostly = MAX_SKB_FRAGS;
EXPORT_SYMBOL(sysctl_max_skb_frags);

/**
 *	skb_panic - निजी function क्रम out-of-line support
 *	@skb:	buffer
 *	@sz:	size
 *	@addr:	address
 *	@msg:	skb_over_panic or skb_under_panic
 *
 *	Out-of-line support क्रम skb_put() and skb_push().
 *	Called via the wrapper skb_over_panic() or skb_under_panic().
 *	Keep out of line to prevent kernel bloat.
 *	__builtin_वापस_address is not used because it is not always reliable.
 */
अटल व्योम skb_panic(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक sz, व्योम *addr,
		      स्थिर अक्षर msg[])
अणु
	pr_emerg("%s: text:%px len:%d put:%d head:%px data:%px tail:%#lx end:%#lx dev:%s\n",
		 msg, addr, skb->len, sz, skb->head, skb->data,
		 (अचिन्हित दीर्घ)skb->tail, (अचिन्हित दीर्घ)skb->end,
		 skb->dev ? skb->dev->name : "<NULL>");
	BUG();
पूर्ण

अटल व्योम skb_over_panic(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक sz, व्योम *addr)
अणु
	skb_panic(skb, sz, addr, __func__);
पूर्ण

अटल व्योम skb_under_panic(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक sz, व्योम *addr)
अणु
	skb_panic(skb, sz, addr, __func__);
पूर्ण

#घोषणा NAPI_SKB_CACHE_SIZE	64
#घोषणा NAPI_SKB_CACHE_BULK	16
#घोषणा NAPI_SKB_CACHE_HALF	(NAPI_SKB_CACHE_SIZE / 2)

काष्ठा napi_alloc_cache अणु
	काष्ठा page_frag_cache page;
	अचिन्हित पूर्णांक skb_count;
	व्योम *skb_cache[NAPI_SKB_CACHE_SIZE];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा page_frag_cache, netdev_alloc_cache);
अटल DEFINE_PER_CPU(काष्ठा napi_alloc_cache, napi_alloc_cache);

अटल व्योम *__alloc_frag_align(अचिन्हित पूर्णांक fragsz, gfp_t gfp_mask,
				अचिन्हित पूर्णांक align_mask)
अणु
	काष्ठा napi_alloc_cache *nc = this_cpu_ptr(&napi_alloc_cache);

	वापस page_frag_alloc_align(&nc->page, fragsz, gfp_mask, align_mask);
पूर्ण

व्योम *__napi_alloc_frag_align(अचिन्हित पूर्णांक fragsz, अचिन्हित पूर्णांक align_mask)
अणु
	fragsz = SKB_DATA_ALIGN(fragsz);

	वापस __alloc_frag_align(fragsz, GFP_ATOMIC, align_mask);
पूर्ण
EXPORT_SYMBOL(__napi_alloc_frag_align);

व्योम *__netdev_alloc_frag_align(अचिन्हित पूर्णांक fragsz, अचिन्हित पूर्णांक align_mask)
अणु
	काष्ठा page_frag_cache *nc;
	व्योम *data;

	fragsz = SKB_DATA_ALIGN(fragsz);
	अगर (in_irq() || irqs_disabled()) अणु
		nc = this_cpu_ptr(&netdev_alloc_cache);
		data = page_frag_alloc_align(nc, fragsz, GFP_ATOMIC, align_mask);
	पूर्ण अन्यथा अणु
		local_bh_disable();
		data = __alloc_frag_align(fragsz, GFP_ATOMIC, align_mask);
		local_bh_enable();
	पूर्ण
	वापस data;
पूर्ण
EXPORT_SYMBOL(__netdev_alloc_frag_align);

अटल काष्ठा sk_buff *napi_skb_cache_get(व्योम)
अणु
	काष्ठा napi_alloc_cache *nc = this_cpu_ptr(&napi_alloc_cache);
	काष्ठा sk_buff *skb;

	अगर (unlikely(!nc->skb_count))
		nc->skb_count = kmem_cache_alloc_bulk(skbuff_head_cache,
						      GFP_ATOMIC,
						      NAPI_SKB_CACHE_BULK,
						      nc->skb_cache);
	अगर (unlikely(!nc->skb_count))
		वापस शून्य;

	skb = nc->skb_cache[--nc->skb_count];
	kasan_unpoison_object_data(skbuff_head_cache, skb);

	वापस skb;
पूर्ण

/* Caller must provide SKB that is स_रखो cleared */
अटल व्योम __build_skb_around(काष्ठा sk_buff *skb, व्योम *data,
			       अचिन्हित पूर्णांक frag_size)
अणु
	काष्ठा skb_shared_info *shinfo;
	अचिन्हित पूर्णांक size = frag_size ? : ksize(data);

	size -= SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	/* Assumes caller स_रखो cleared SKB */
	skb->truesize = SKB_TRUESIZE(size);
	refcount_set(&skb->users, 1);
	skb->head = data;
	skb->data = data;
	skb_reset_tail_poपूर्णांकer(skb);
	skb->end = skb->tail + size;
	skb->mac_header = (typeof(skb->mac_header))~0U;
	skb->transport_header = (typeof(skb->transport_header))~0U;

	/* make sure we initialize shinfo sequentially */
	shinfo = skb_shinfo(skb);
	स_रखो(shinfo, 0, दुरत्व(काष्ठा skb_shared_info, dataref));
	atomic_set(&shinfo->dataref, 1);

	skb_set_kcov_handle(skb, kcov_common_handle());
पूर्ण

/**
 * __build_skb - build a network buffer
 * @data: data buffer provided by caller
 * @frag_size: size of data, or 0 अगर head was kदो_स्मृतिed
 *
 * Allocate a new &sk_buff. Caller provides space holding head and
 * skb_shared_info. @data must have been allocated by kदो_स्मृति() only अगर
 * @frag_size is 0, otherwise data should come from the page allocator
 *  or vदो_स्मृति()
 * The वापस is the new skb buffer.
 * On a failure the वापस is %शून्य, and @data is not मुक्तd.
 * Notes :
 *  Beक्रमe IO, driver allocates only data buffer where NIC put incoming frame
 *  Driver should add room at head (NET_SKB_PAD) and
 *  MUST add room at tail (SKB_DATA_ALIGN(skb_shared_info))
 *  After IO, driver calls build_skb(), to allocate sk_buff and populate it
 *  beक्रमe giving packet to stack.
 *  RX rings only contains data buffers, not full skbs.
 */
काष्ठा sk_buff *__build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size)
अणु
	काष्ठा sk_buff *skb;

	skb = kmem_cache_alloc(skbuff_head_cache, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस शून्य;

	स_रखो(skb, 0, दुरत्व(काष्ठा sk_buff, tail));
	__build_skb_around(skb, data, frag_size);

	वापस skb;
पूर्ण

/* build_skb() is wrapper over __build_skb(), that specअगरically
 * takes care of skb->head and skb->pfmeदो_स्मृति
 * This means that अगर @frag_size is not zero, then @data must be backed
 * by a page fragment, not kदो_स्मृति() or vदो_स्मृति()
 */
काष्ठा sk_buff *build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size)
अणु
	काष्ठा sk_buff *skb = __build_skb(data, frag_size);

	अगर (skb && frag_size) अणु
		skb->head_frag = 1;
		अगर (page_is_pfmeदो_स्मृति(virt_to_head_page(data)))
			skb->pfmeदो_स्मृति = 1;
	पूर्ण
	वापस skb;
पूर्ण
EXPORT_SYMBOL(build_skb);

/**
 * build_skb_around - build a network buffer around provided skb
 * @skb: sk_buff provide by caller, must be स_रखो cleared
 * @data: data buffer provided by caller
 * @frag_size: size of data, or 0 अगर head was kदो_स्मृतिed
 */
काष्ठा sk_buff *build_skb_around(काष्ठा sk_buff *skb,
				 व्योम *data, अचिन्हित पूर्णांक frag_size)
अणु
	अगर (unlikely(!skb))
		वापस शून्य;

	__build_skb_around(skb, data, frag_size);

	अगर (frag_size) अणु
		skb->head_frag = 1;
		अगर (page_is_pfmeदो_स्मृति(virt_to_head_page(data)))
			skb->pfmeदो_स्मृति = 1;
	पूर्ण
	वापस skb;
पूर्ण
EXPORT_SYMBOL(build_skb_around);

/**
 * __napi_build_skb - build a network buffer
 * @data: data buffer provided by caller
 * @frag_size: size of data, or 0 अगर head was kदो_स्मृतिed
 *
 * Version of __build_skb() that uses NAPI percpu caches to obtain
 * skbuff_head instead of inplace allocation.
 *
 * Returns a new &sk_buff on success, %शून्य on allocation failure.
 */
अटल काष्ठा sk_buff *__napi_build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size)
अणु
	काष्ठा sk_buff *skb;

	skb = napi_skb_cache_get();
	अगर (unlikely(!skb))
		वापस शून्य;

	स_रखो(skb, 0, दुरत्व(काष्ठा sk_buff, tail));
	__build_skb_around(skb, data, frag_size);

	वापस skb;
पूर्ण

/**
 * napi_build_skb - build a network buffer
 * @data: data buffer provided by caller
 * @frag_size: size of data, or 0 अगर head was kदो_स्मृतिed
 *
 * Version of __napi_build_skb() that takes care of skb->head_frag
 * and skb->pfmeदो_स्मृति when the data is a page or page fragment.
 *
 * Returns a new &sk_buff on success, %शून्य on allocation failure.
 */
काष्ठा sk_buff *napi_build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size)
अणु
	काष्ठा sk_buff *skb = __napi_build_skb(data, frag_size);

	अगर (likely(skb) && frag_size) अणु
		skb->head_frag = 1;
		skb_propagate_pfmeदो_स्मृति(virt_to_head_page(data), skb);
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL(napi_build_skb);

/*
 * kदो_स्मृति_reserve is a wrapper around kदो_स्मृति_node_track_caller that tells
 * the caller अगर emergency pfmeदो_स्मृति reserves are being used. If it is and
 * the socket is later found to be SOCK_MEMALLOC then PFMEMALLOC reserves
 * may be used. Otherwise, the packet data may be discarded until enough
 * memory is मुक्त
 */
अटल व्योम *kदो_स्मृति_reserve(माप_प्रकार size, gfp_t flags, पूर्णांक node,
			     bool *pfmeदो_स्मृति)
अणु
	व्योम *obj;
	bool ret_pfmeदो_स्मृति = false;

	/*
	 * Try a regular allocation, when that fails and we're not entitled
	 * to the reserves, fail.
	 */
	obj = kदो_स्मृति_node_track_caller(size,
					flags | __GFP_NOMEMALLOC | __GFP_NOWARN,
					node);
	अगर (obj || !(gfp_pfmeदो_स्मृति_allowed(flags)))
		जाओ out;

	/* Try again but now we are using pfmeदो_स्मृति reserves */
	ret_pfmeदो_स्मृति = true;
	obj = kदो_स्मृति_node_track_caller(size, flags, node);

out:
	अगर (pfmeदो_स्मृति)
		*pfmeदो_स्मृति = ret_pfmeदो_स्मृति;

	वापस obj;
पूर्ण

/* 	Allocate a new skbuff. We करो this ourselves so we can fill in a few
 *	'private' fields and also करो memory statistics to find all the
 *	[BEEP] leaks.
 *
 */

/**
 *	__alloc_skb	-	allocate a network buffer
 *	@size: size to allocate
 *	@gfp_mask: allocation mask
 *	@flags: If SKB_ALLOC_FCLONE is set, allocate from fclone cache
 *		instead of head cache and allocate a cloned (child) skb.
 *		If SKB_ALLOC_RX is set, __GFP_MEMALLOC will be used क्रम
 *		allocations in हाल the data is required क्रम ग_लिखोback
 *	@node: numa node to allocate memory on
 *
 *	Allocate a new &sk_buff. The वापसed buffer has no headroom and a
 *	tail room of at least size bytes. The object has a reference count
 *	of one. The वापस is the buffer. On a failure the वापस is %शून्य.
 *
 *	Buffers may only be allocated from पूर्णांकerrupts using a @gfp_mask of
 *	%GFP_ATOMIC.
 */
काष्ठा sk_buff *__alloc_skb(अचिन्हित पूर्णांक size, gfp_t gfp_mask,
			    पूर्णांक flags, पूर्णांक node)
अणु
	काष्ठा kmem_cache *cache;
	काष्ठा sk_buff *skb;
	u8 *data;
	bool pfmeदो_स्मृति;

	cache = (flags & SKB_ALLOC_FCLONE)
		? skbuff_fclone_cache : skbuff_head_cache;

	अगर (sk_meदो_स्मृति_socks() && (flags & SKB_ALLOC_RX))
		gfp_mask |= __GFP_MEMALLOC;

	/* Get the HEAD */
	अगर ((flags & (SKB_ALLOC_FCLONE | SKB_ALLOC_NAPI)) == SKB_ALLOC_NAPI &&
	    likely(node == NUMA_NO_NODE || node == numa_mem_id()))
		skb = napi_skb_cache_get();
	अन्यथा
		skb = kmem_cache_alloc_node(cache, gfp_mask & ~GFP_DMA, node);
	अगर (unlikely(!skb))
		वापस शून्य;
	prefetchw(skb);

	/* We करो our best to align skb_shared_info on a separate cache
	 * line. It usually works because kदो_स्मृति(X > SMP_CACHE_BYTES) gives
	 * aligned memory blocks, unless SLUB/SLAB debug is enabled.
	 * Both skb->head and skb_shared_info are cache line aligned.
	 */
	size = SKB_DATA_ALIGN(size);
	size += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	data = kदो_स्मृति_reserve(size, gfp_mask, node, &pfmeदो_स्मृति);
	अगर (unlikely(!data))
		जाओ nodata;
	/* kदो_स्मृति(size) might give us more room than requested.
	 * Put skb_shared_info exactly at the end of allocated zone,
	 * to allow max possible filling beक्रमe पुनः_स्मृतिation.
	 */
	size = SKB_WITH_OVERHEAD(ksize(data));
	prefetchw(data + size);

	/*
	 * Only clear those fields we need to clear, not those that we will
	 * actually initialise below. Hence, करोn't put any more fields after
	 * the tail poपूर्णांकer in काष्ठा sk_buff!
	 */
	स_रखो(skb, 0, दुरत्व(काष्ठा sk_buff, tail));
	__build_skb_around(skb, data, 0);
	skb->pfmeदो_स्मृति = pfmeदो_स्मृति;

	अगर (flags & SKB_ALLOC_FCLONE) अणु
		काष्ठा sk_buff_fclones *fclones;

		fclones = container_of(skb, काष्ठा sk_buff_fclones, skb1);

		skb->fclone = SKB_FCLONE_ORIG;
		refcount_set(&fclones->fclone_ref, 1);

		fclones->skb2.fclone = SKB_FCLONE_CLONE;
	पूर्ण

	वापस skb;

nodata:
	kmem_cache_मुक्त(cache, skb);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__alloc_skb);

/**
 *	__netdev_alloc_skb - allocate an skbuff क्रम rx on a specअगरic device
 *	@dev: network device to receive on
 *	@len: length to allocate
 *	@gfp_mask: get_मुक्त_pages mask, passed to alloc_skb
 *
 *	Allocate a new &sk_buff and assign it a usage count of one. The
 *	buffer has NET_SKB_PAD headroom built in. Users should allocate
 *	the headroom they think they need without accounting क्रम the
 *	built in space. The built in space is used क्रम optimisations.
 *
 *	%शून्य is वापसed अगर there is no मुक्त memory.
 */
काष्ठा sk_buff *__netdev_alloc_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक len,
				   gfp_t gfp_mask)
अणु
	काष्ठा page_frag_cache *nc;
	काष्ठा sk_buff *skb;
	bool pfmeदो_स्मृति;
	व्योम *data;

	len += NET_SKB_PAD;

	/* If requested length is either too small or too big,
	 * we use kदो_स्मृति() क्रम skb->head allocation.
	 */
	अगर (len <= SKB_WITH_OVERHEAD(1024) ||
	    len > SKB_WITH_OVERHEAD(PAGE_SIZE) ||
	    (gfp_mask & (__GFP_सूचीECT_RECLAIM | GFP_DMA))) अणु
		skb = __alloc_skb(len, gfp_mask, SKB_ALLOC_RX, NUMA_NO_NODE);
		अगर (!skb)
			जाओ skb_fail;
		जाओ skb_success;
	पूर्ण

	len += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	len = SKB_DATA_ALIGN(len);

	अगर (sk_meदो_स्मृति_socks())
		gfp_mask |= __GFP_MEMALLOC;

	अगर (in_irq() || irqs_disabled()) अणु
		nc = this_cpu_ptr(&netdev_alloc_cache);
		data = page_frag_alloc(nc, len, gfp_mask);
		pfmeदो_स्मृति = nc->pfmeदो_स्मृति;
	पूर्ण अन्यथा अणु
		local_bh_disable();
		nc = this_cpu_ptr(&napi_alloc_cache.page);
		data = page_frag_alloc(nc, len, gfp_mask);
		pfmeदो_स्मृति = nc->pfmeदो_स्मृति;
		local_bh_enable();
	पूर्ण

	अगर (unlikely(!data))
		वापस शून्य;

	skb = __build_skb(data, len);
	अगर (unlikely(!skb)) अणु
		skb_मुक्त_frag(data);
		वापस शून्य;
	पूर्ण

	अगर (pfmeदो_स्मृति)
		skb->pfmeदो_स्मृति = 1;
	skb->head_frag = 1;

skb_success:
	skb_reserve(skb, NET_SKB_PAD);
	skb->dev = dev;

skb_fail:
	वापस skb;
पूर्ण
EXPORT_SYMBOL(__netdev_alloc_skb);

/**
 *	__napi_alloc_skb - allocate skbuff क्रम rx in a specअगरic NAPI instance
 *	@napi: napi instance this buffer was allocated क्रम
 *	@len: length to allocate
 *	@gfp_mask: get_मुक्त_pages mask, passed to alloc_skb and alloc_pages
 *
 *	Allocate a new sk_buff क्रम use in NAPI receive.  This buffer will
 *	attempt to allocate the head from a special reserved region used
 *	only क्रम NAPI Rx allocation.  By करोing this we can save several
 *	CPU cycles by aव्योमing having to disable and re-enable IRQs.
 *
 *	%शून्य is वापसed अगर there is no मुक्त memory.
 */
काष्ठा sk_buff *__napi_alloc_skb(काष्ठा napi_काष्ठा *napi, अचिन्हित पूर्णांक len,
				 gfp_t gfp_mask)
अणु
	काष्ठा napi_alloc_cache *nc;
	काष्ठा sk_buff *skb;
	व्योम *data;

	len += NET_SKB_PAD + NET_IP_ALIGN;

	/* If requested length is either too small or too big,
	 * we use kदो_स्मृति() क्रम skb->head allocation.
	 */
	अगर (len <= SKB_WITH_OVERHEAD(1024) ||
	    len > SKB_WITH_OVERHEAD(PAGE_SIZE) ||
	    (gfp_mask & (__GFP_सूचीECT_RECLAIM | GFP_DMA))) अणु
		skb = __alloc_skb(len, gfp_mask, SKB_ALLOC_RX | SKB_ALLOC_NAPI,
				  NUMA_NO_NODE);
		अगर (!skb)
			जाओ skb_fail;
		जाओ skb_success;
	पूर्ण

	nc = this_cpu_ptr(&napi_alloc_cache);
	len += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	len = SKB_DATA_ALIGN(len);

	अगर (sk_meदो_स्मृति_socks())
		gfp_mask |= __GFP_MEMALLOC;

	data = page_frag_alloc(&nc->page, len, gfp_mask);
	अगर (unlikely(!data))
		वापस शून्य;

	skb = __napi_build_skb(data, len);
	अगर (unlikely(!skb)) अणु
		skb_मुक्त_frag(data);
		वापस शून्य;
	पूर्ण

	अगर (nc->page.pfmeदो_स्मृति)
		skb->pfmeदो_स्मृति = 1;
	skb->head_frag = 1;

skb_success:
	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);
	skb->dev = napi->dev;

skb_fail:
	वापस skb;
पूर्ण
EXPORT_SYMBOL(__napi_alloc_skb);

व्योम skb_add_rx_frag(काष्ठा sk_buff *skb, पूर्णांक i, काष्ठा page *page, पूर्णांक off,
		     पूर्णांक size, अचिन्हित पूर्णांक truesize)
अणु
	skb_fill_page_desc(skb, i, page, off, size);
	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
पूर्ण
EXPORT_SYMBOL(skb_add_rx_frag);

व्योम skb_coalesce_rx_frag(काष्ठा sk_buff *skb, पूर्णांक i, पूर्णांक size,
			  अचिन्हित पूर्णांक truesize)
अणु
	skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

	skb_frag_size_add(frag, size);
	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
पूर्ण
EXPORT_SYMBOL(skb_coalesce_rx_frag);

अटल व्योम skb_drop_list(काष्ठा sk_buff **listp)
अणु
	kमुक्त_skb_list(*listp);
	*listp = शून्य;
पूर्ण

अटल अंतरभूत व्योम skb_drop_fraglist(काष्ठा sk_buff *skb)
अणु
	skb_drop_list(&skb_shinfo(skb)->frag_list);
पूर्ण

अटल व्योम skb_clone_fraglist(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *list;

	skb_walk_frags(skb, list)
		skb_get(list);
पूर्ण

अटल व्योम skb_मुक्त_head(काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *head = skb->head;

	अगर (skb->head_frag)
		skb_मुक्त_frag(head);
	अन्यथा
		kमुक्त(head);
पूर्ण

अटल व्योम skb_release_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	पूर्णांक i;

	अगर (skb->cloned &&
	    atomic_sub_वापस(skb->nohdr ? (1 << SKB_DATAREF_SHIFT) + 1 : 1,
			      &shinfo->dataref))
		वापस;

	skb_zcopy_clear(skb, true);

	क्रम (i = 0; i < shinfo->nr_frags; i++)
		__skb_frag_unref(&shinfo->frags[i]);

	अगर (shinfo->frag_list)
		kमुक्त_skb_list(shinfo->frag_list);

	skb_मुक्त_head(skb);
पूर्ण

/*
 *	Free an skbuff by memory without cleaning the state.
 */
अटल व्योम kमुक्त_skbmem(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff_fclones *fclones;

	चयन (skb->fclone) अणु
	हाल SKB_FCLONE_UNAVAILABLE:
		kmem_cache_मुक्त(skbuff_head_cache, skb);
		वापस;

	हाल SKB_FCLONE_ORIG:
		fclones = container_of(skb, काष्ठा sk_buff_fclones, skb1);

		/* We usually मुक्त the clone (TX completion) beक्रमe original skb
		 * This test would have no chance to be true क्रम the clone,
		 * जबतक here, branch prediction will be good.
		 */
		अगर (refcount_पढ़ो(&fclones->fclone_ref) == 1)
			जाओ fastpath;
		अवरोध;

	शेष: /* SKB_FCLONE_CLONE */
		fclones = container_of(skb, काष्ठा sk_buff_fclones, skb2);
		अवरोध;
	पूर्ण
	अगर (!refcount_dec_and_test(&fclones->fclone_ref))
		वापस;
fastpath:
	kmem_cache_मुक्त(skbuff_fclone_cache, fclones);
पूर्ण

व्योम skb_release_head_state(काष्ठा sk_buff *skb)
अणु
	skb_dst_drop(skb);
	अगर (skb->deकाष्ठाor) अणु
		WARN_ON(in_irq());
		skb->deकाष्ठाor(skb);
	पूर्ण
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	nf_conntrack_put(skb_nfct(skb));
#पूर्ण_अगर
	skb_ext_put(skb);
पूर्ण

/* Free everything but the sk_buff shell. */
अटल व्योम skb_release_all(काष्ठा sk_buff *skb)
अणु
	skb_release_head_state(skb);
	अगर (likely(skb->head))
		skb_release_data(skb);
पूर्ण

/**
 *	__kमुक्त_skb - निजी function
 *	@skb: buffer
 *
 *	Free an sk_buff. Release anything attached to the buffer.
 *	Clean the state. This is an पूर्णांकernal helper function. Users should
 *	always call kमुक्त_skb
 */

व्योम __kमुक्त_skb(काष्ठा sk_buff *skb)
अणु
	skb_release_all(skb);
	kमुक्त_skbmem(skb);
पूर्ण
EXPORT_SYMBOL(__kमुक्त_skb);

/**
 *	kमुक्त_skb - मुक्त an sk_buff
 *	@skb: buffer to मुक्त
 *
 *	Drop a reference to the buffer and मुक्त it अगर the usage count has
 *	hit zero.
 */
व्योम kमुक्त_skb(काष्ठा sk_buff *skb)
अणु
	अगर (!skb_unref(skb))
		वापस;

	trace_kमुक्त_skb(skb, __builtin_वापस_address(0));
	__kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(kमुक्त_skb);

व्योम kमुक्त_skb_list(काष्ठा sk_buff *segs)
अणु
	जबतक (segs) अणु
		काष्ठा sk_buff *next = segs->next;

		kमुक्त_skb(segs);
		segs = next;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kमुक्त_skb_list);

/* Dump skb inक्रमmation and contents.
 *
 * Must only be called from net_ratelimit()-ed paths.
 *
 * Dumps whole packets अगर full_pkt, only headers otherwise.
 */
व्योम skb_dump(स्थिर अक्षर *level, स्थिर काष्ठा sk_buff *skb, bool full_pkt)
अणु
	काष्ठा skb_shared_info *sh = skb_shinfo(skb);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा sock *sk = skb->sk;
	काष्ठा sk_buff *list_skb;
	bool has_mac, has_trans;
	पूर्णांक headroom, tailroom;
	पूर्णांक i, len, seg_len;

	अगर (full_pkt)
		len = skb->len;
	अन्यथा
		len = min_t(पूर्णांक, skb->len, MAX_HEADER + 128);

	headroom = skb_headroom(skb);
	tailroom = skb_tailroom(skb);

	has_mac = skb_mac_header_was_set(skb);
	has_trans = skb_transport_header_was_set(skb);

	prपूर्णांकk("%sskb len=%u headroom=%u headlen=%u tailroom=%u\n"
	       "mac=(%d,%d) net=(%d,%d) trans=%d\n"
	       "shinfo(txflags=%u nr_frags=%u gso(size=%hu type=%u segs=%hu))\n"
	       "csum(0x%x ip_summed=%u complete_sw=%u valid=%u level=%u)\n"
	       "hash(0x%x sw=%u l4=%u) proto=0x%04x pkttype=%u iif=%d\n",
	       level, skb->len, headroom, skb_headlen(skb), tailroom,
	       has_mac ? skb->mac_header : -1,
	       has_mac ? skb_mac_header_len(skb) : -1,
	       skb->network_header,
	       has_trans ? skb_network_header_len(skb) : -1,
	       has_trans ? skb->transport_header : -1,
	       sh->tx_flags, sh->nr_frags,
	       sh->gso_size, sh->gso_type, sh->gso_segs,
	       skb->csum, skb->ip_summed, skb->csum_complete_sw,
	       skb->csum_valid, skb->csum_level,
	       skb->hash, skb->sw_hash, skb->l4_hash,
	       ntohs(skb->protocol), skb->pkt_type, skb->skb_iअगर);

	अगर (dev)
		prपूर्णांकk("%sdev name=%s feat=0x%pNF\n",
		       level, dev->name, &dev->features);
	अगर (sk)
		prपूर्णांकk("%ssk family=%hu type=%u proto=%u\n",
		       level, sk->sk_family, sk->sk_type, sk->sk_protocol);

	अगर (full_pkt && headroom)
		prपूर्णांक_hex_dump(level, "skb headroom: ", DUMP_PREFIX_OFFSET,
			       16, 1, skb->head, headroom, false);

	seg_len = min_t(पूर्णांक, skb_headlen(skb), len);
	अगर (seg_len)
		prपूर्णांक_hex_dump(level, "skb linear:   ", DUMP_PREFIX_OFFSET,
			       16, 1, skb->data, seg_len, false);
	len -= seg_len;

	अगर (full_pkt && tailroom)
		prपूर्णांक_hex_dump(level, "skb tailroom: ", DUMP_PREFIX_OFFSET,
			       16, 1, skb_tail_poपूर्णांकer(skb), tailroom, false);

	क्रम (i = 0; len && i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 p_off, p_len, copied;
		काष्ठा page *p;
		u8 *vaddr;

		skb_frag_क्रमeach_page(frag, skb_frag_off(frag),
				      skb_frag_size(frag), p, p_off, p_len,
				      copied) अणु
			seg_len = min_t(पूर्णांक, p_len, len);
			vaddr = kmap_atomic(p);
			prपूर्णांक_hex_dump(level, "skb frag:     ",
				       DUMP_PREFIX_OFFSET,
				       16, 1, vaddr + p_off, seg_len, false);
			kunmap_atomic(vaddr);
			len -= seg_len;
			अगर (!len)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (full_pkt && skb_has_frag_list(skb)) अणु
		prपूर्णांकk("skb fraglist:\n");
		skb_walk_frags(skb, list_skb)
			skb_dump(level, list_skb, true);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(skb_dump);

/**
 *	skb_tx_error - report an sk_buff xmit error
 *	@skb: buffer that triggered an error
 *
 *	Report xmit error अगर a device callback is tracking this skb.
 *	skb must be मुक्तd afterwards.
 */
व्योम skb_tx_error(काष्ठा sk_buff *skb)
अणु
	skb_zcopy_clear(skb, true);
पूर्ण
EXPORT_SYMBOL(skb_tx_error);

#अगर_घोषित CONFIG_TRACEPOINTS
/**
 *	consume_skb - मुक्त an skbuff
 *	@skb: buffer to मुक्त
 *
 *	Drop a ref to the buffer and मुक्त it अगर the usage count has hit zero
 *	Functions identically to kमुक्त_skb, but kमुक्त_skb assumes that the frame
 *	is being dropped after a failure and notes that
 */
व्योम consume_skb(काष्ठा sk_buff *skb)
अणु
	अगर (!skb_unref(skb))
		वापस;

	trace_consume_skb(skb);
	__kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(consume_skb);
#पूर्ण_अगर

/**
 *	__consume_stateless_skb - मुक्त an skbuff, assuming it is stateless
 *	@skb: buffer to मुक्त
 *
 *	Alike consume_skb(), but this variant assumes that this is the last
 *	skb reference and all the head states have been alपढ़ोy dropped
 */
व्योम __consume_stateless_skb(काष्ठा sk_buff *skb)
अणु
	trace_consume_skb(skb);
	skb_release_data(skb);
	kमुक्त_skbmem(skb);
पूर्ण

अटल व्योम napi_skb_cache_put(काष्ठा sk_buff *skb)
अणु
	काष्ठा napi_alloc_cache *nc = this_cpu_ptr(&napi_alloc_cache);
	u32 i;

	kasan_poison_object_data(skbuff_head_cache, skb);
	nc->skb_cache[nc->skb_count++] = skb;

	अगर (unlikely(nc->skb_count == NAPI_SKB_CACHE_SIZE)) अणु
		क्रम (i = NAPI_SKB_CACHE_HALF; i < NAPI_SKB_CACHE_SIZE; i++)
			kasan_unpoison_object_data(skbuff_head_cache,
						   nc->skb_cache[i]);

		kmem_cache_मुक्त_bulk(skbuff_head_cache, NAPI_SKB_CACHE_HALF,
				     nc->skb_cache + NAPI_SKB_CACHE_HALF);
		nc->skb_count = NAPI_SKB_CACHE_HALF;
	पूर्ण
पूर्ण

व्योम __kमुक्त_skb_defer(काष्ठा sk_buff *skb)
अणु
	skb_release_all(skb);
	napi_skb_cache_put(skb);
पूर्ण

व्योम napi_skb_मुक्त_stolen_head(काष्ठा sk_buff *skb)
अणु
	skb_dst_drop(skb);
	skb_ext_put(skb);
	napi_skb_cache_put(skb);
पूर्ण

व्योम napi_consume_skb(काष्ठा sk_buff *skb, पूर्णांक budget)
अणु
	/* Zero budget indicate non-NAPI context called us, like netpoll */
	अगर (unlikely(!budget)) अणु
		dev_consume_skb_any(skb);
		वापस;
	पूर्ण

	lockdep_निश्चित_in_softirq();

	अगर (!skb_unref(skb))
		वापस;

	/* अगर reaching here SKB is पढ़ोy to मुक्त */
	trace_consume_skb(skb);

	/* अगर SKB is a clone, करोn't handle this हाल */
	अगर (skb->fclone != SKB_FCLONE_UNAVAILABLE) अणु
		__kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_release_all(skb);
	napi_skb_cache_put(skb);
पूर्ण
EXPORT_SYMBOL(napi_consume_skb);

/* Make sure a field is enबंदd inside headers_start/headers_end section */
#घोषणा CHECK_SKB_FIELD(field) \
	BUILD_BUG_ON(दुरत्व(काष्ठा sk_buff, field) <		\
		     दुरत्व(काष्ठा sk_buff, headers_start));	\
	BUILD_BUG_ON(दुरत्व(काष्ठा sk_buff, field) >		\
		     दुरत्व(काष्ठा sk_buff, headers_end));	\

अटल व्योम __copy_skb_header(काष्ठा sk_buff *new, स्थिर काष्ठा sk_buff *old)
अणु
	new->tstamp		= old->tstamp;
	/* We करो not copy old->sk */
	new->dev		= old->dev;
	स_नकल(new->cb, old->cb, माप(old->cb));
	skb_dst_copy(new, old);
	__skb_ext_copy(new, old);
	__nf_copy(new, old, false);

	/* Note : this field could be in headers_start/headers_end section
	 * It is not yet because we करो not want to have a 16 bit hole
	 */
	new->queue_mapping = old->queue_mapping;

	स_नकल(&new->headers_start, &old->headers_start,
	       दुरत्व(काष्ठा sk_buff, headers_end) -
	       दुरत्व(काष्ठा sk_buff, headers_start));
	CHECK_SKB_FIELD(protocol);
	CHECK_SKB_FIELD(csum);
	CHECK_SKB_FIELD(hash);
	CHECK_SKB_FIELD(priority);
	CHECK_SKB_FIELD(skb_iअगर);
	CHECK_SKB_FIELD(vlan_proto);
	CHECK_SKB_FIELD(vlan_tci);
	CHECK_SKB_FIELD(transport_header);
	CHECK_SKB_FIELD(network_header);
	CHECK_SKB_FIELD(mac_header);
	CHECK_SKB_FIELD(inner_protocol);
	CHECK_SKB_FIELD(inner_transport_header);
	CHECK_SKB_FIELD(inner_network_header);
	CHECK_SKB_FIELD(inner_mac_header);
	CHECK_SKB_FIELD(mark);
#अगर_घोषित CONFIG_NETWORK_SECMARK
	CHECK_SKB_FIELD(secmark);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	CHECK_SKB_FIELD(napi_id);
#पूर्ण_अगर
#अगर_घोषित CONFIG_XPS
	CHECK_SKB_FIELD(sender_cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_SCHED
	CHECK_SKB_FIELD(tc_index);
#पूर्ण_अगर

पूर्ण

/*
 * You should not add any new code to this function.  Add it to
 * __copy_skb_header above instead.
 */
अटल काष्ठा sk_buff *__skb_clone(काष्ठा sk_buff *n, काष्ठा sk_buff *skb)
अणु
#घोषणा C(x) n->x = skb->x

	n->next = n->prev = शून्य;
	n->sk = शून्य;
	__copy_skb_header(n, skb);

	C(len);
	C(data_len);
	C(mac_len);
	n->hdr_len = skb->nohdr ? skb_headroom(skb) : skb->hdr_len;
	n->cloned = 1;
	n->nohdr = 0;
	n->peeked = 0;
	C(pfmeदो_स्मृति);
	n->deकाष्ठाor = शून्य;
	C(tail);
	C(end);
	C(head);
	C(head_frag);
	C(data);
	C(truesize);
	refcount_set(&n->users, 1);

	atomic_inc(&(skb_shinfo(skb)->dataref));
	skb->cloned = 1;

	वापस n;
#अघोषित C
पूर्ण

/**
 * alloc_skb_क्रम_msg() - allocate sk_buff to wrap frag list क्रमming a msg
 * @first: first sk_buff of the msg
 */
काष्ठा sk_buff *alloc_skb_क्रम_msg(काष्ठा sk_buff *first)
अणु
	काष्ठा sk_buff *n;

	n = alloc_skb(0, GFP_ATOMIC);
	अगर (!n)
		वापस शून्य;

	n->len = first->len;
	n->data_len = first->len;
	n->truesize = first->truesize;

	skb_shinfo(n)->frag_list = first;

	__copy_skb_header(n, first);
	n->deकाष्ठाor = शून्य;

	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_skb_क्रम_msg);

/**
 *	skb_morph	-	morph one skb पूर्णांकo another
 *	@dst: the skb to receive the contents
 *	@src: the skb to supply the contents
 *
 *	This is identical to skb_clone except that the target skb is
 *	supplied by the user.
 *
 *	The target skb is वापसed upon निकास.
 */
काष्ठा sk_buff *skb_morph(काष्ठा sk_buff *dst, काष्ठा sk_buff *src)
अणु
	skb_release_all(dst);
	वापस __skb_clone(dst, src);
पूर्ण
EXPORT_SYMBOL_GPL(skb_morph);

पूर्णांक mm_account_pinned_pages(काष्ठा mmpin *mmp, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ max_pg, num_pg, new_pg, old_pg;
	काष्ठा user_काष्ठा *user;

	अगर (capable(CAP_IPC_LOCK) || !size)
		वापस 0;

	num_pg = (size >> PAGE_SHIFT) + 2;	/* worst हाल */
	max_pg = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	user = mmp->user ? : current_user();

	करो अणु
		old_pg = atomic_दीर्घ_पढ़ो(&user->locked_vm);
		new_pg = old_pg + num_pg;
		अगर (new_pg > max_pg)
			वापस -ENOBUFS;
	पूर्ण जबतक (atomic_दीर्घ_cmpxchg(&user->locked_vm, old_pg, new_pg) !=
		 old_pg);

	अगर (!mmp->user) अणु
		mmp->user = get_uid(user);
		mmp->num_pg = num_pg;
	पूर्ण अन्यथा अणु
		mmp->num_pg += num_pg;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mm_account_pinned_pages);

व्योम mm_unaccount_pinned_pages(काष्ठा mmpin *mmp)
अणु
	अगर (mmp->user) अणु
		atomic_दीर्घ_sub(mmp->num_pg, &mmp->user->locked_vm);
		मुक्त_uid(mmp->user);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mm_unaccount_pinned_pages);

काष्ठा ubuf_info *msg_zerocopy_alloc(काष्ठा sock *sk, माप_प्रकार size)
अणु
	काष्ठा ubuf_info *uarg;
	काष्ठा sk_buff *skb;

	WARN_ON_ONCE(!in_task());

	skb = sock_oदो_स्मृति(sk, 0, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	BUILD_BUG_ON(माप(*uarg) > माप(skb->cb));
	uarg = (व्योम *)skb->cb;
	uarg->mmp.user = शून्य;

	अगर (mm_account_pinned_pages(&uarg->mmp, size)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	uarg->callback = msg_zerocopy_callback;
	uarg->id = ((u32)atomic_inc_वापस(&sk->sk_zckey)) - 1;
	uarg->len = 1;
	uarg->bytelen = size;
	uarg->zerocopy = 1;
	uarg->flags = SKBFL_ZEROCOPY_FRAG;
	refcount_set(&uarg->refcnt, 1);
	sock_hold(sk);

	वापस uarg;
पूर्ण
EXPORT_SYMBOL_GPL(msg_zerocopy_alloc);

अटल अंतरभूत काष्ठा sk_buff *skb_from_uarg(काष्ठा ubuf_info *uarg)
अणु
	वापस container_of((व्योम *)uarg, काष्ठा sk_buff, cb);
पूर्ण

काष्ठा ubuf_info *msg_zerocopy_पुनः_स्मृति(काष्ठा sock *sk, माप_प्रकार size,
				       काष्ठा ubuf_info *uarg)
अणु
	अगर (uarg) अणु
		स्थिर u32 byte_limit = 1 << 19;		/* limit to a few TSO */
		u32 bytelen, next;

		/* पुनः_स्मृति only when socket is locked (TCP, UDP cork),
		 * so uarg->len and sk_zckey access is serialized
		 */
		अगर (!sock_owned_by_user(sk)) अणु
			WARN_ON_ONCE(1);
			वापस शून्य;
		पूर्ण

		bytelen = uarg->bytelen + size;
		अगर (uarg->len == अच_लघु_उच्च - 1 || bytelen > byte_limit) अणु
			/* TCP can create new skb to attach new uarg */
			अगर (sk->sk_type == SOCK_STREAM)
				जाओ new_alloc;
			वापस शून्य;
		पूर्ण

		next = (u32)atomic_पढ़ो(&sk->sk_zckey);
		अगर ((u32)(uarg->id + uarg->len) == next) अणु
			अगर (mm_account_pinned_pages(&uarg->mmp, size))
				वापस शून्य;
			uarg->len++;
			uarg->bytelen = bytelen;
			atomic_set(&sk->sk_zckey, ++next);

			/* no extra ref when appending to datagram (MSG_MORE) */
			अगर (sk->sk_type == SOCK_STREAM)
				net_zcopy_get(uarg);

			वापस uarg;
		पूर्ण
	पूर्ण

new_alloc:
	वापस msg_zerocopy_alloc(sk, size);
पूर्ण
EXPORT_SYMBOL_GPL(msg_zerocopy_पुनः_स्मृति);

अटल bool skb_zerocopy_notअगरy_extend(काष्ठा sk_buff *skb, u32 lo, u16 len)
अणु
	काष्ठा sock_exterr_skb *serr = SKB_EXT_ERR(skb);
	u32 old_lo, old_hi;
	u64 sum_len;

	old_lo = serr->ee.ee_info;
	old_hi = serr->ee.ee_data;
	sum_len = old_hi - old_lo + 1ULL + len;

	अगर (sum_len >= (1ULL << 32))
		वापस false;

	अगर (lo != old_hi + 1)
		वापस false;

	serr->ee.ee_data += len;
	वापस true;
पूर्ण

अटल व्योम __msg_zerocopy_callback(काष्ठा ubuf_info *uarg)
अणु
	काष्ठा sk_buff *tail, *skb = skb_from_uarg(uarg);
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sock *sk = skb->sk;
	काष्ठा sk_buff_head *q;
	अचिन्हित दीर्घ flags;
	bool is_zerocopy;
	u32 lo, hi;
	u16 len;

	mm_unaccount_pinned_pages(&uarg->mmp);

	/* अगर !len, there was only 1 call, and it was पातed
	 * so करो not queue a completion notअगरication
	 */
	अगर (!uarg->len || sock_flag(sk, SOCK_DEAD))
		जाओ release;

	len = uarg->len;
	lo = uarg->id;
	hi = uarg->id + len - 1;
	is_zerocopy = uarg->zerocopy;

	serr = SKB_EXT_ERR(skb);
	स_रखो(serr, 0, माप(*serr));
	serr->ee.ee_त्रुटि_सं = 0;
	serr->ee.ee_origin = SO_EE_ORIGIN_ZEROCOPY;
	serr->ee.ee_data = hi;
	serr->ee.ee_info = lo;
	अगर (!is_zerocopy)
		serr->ee.ee_code |= SO_EE_CODE_ZEROCOPY_COPIED;

	q = &sk->sk_error_queue;
	spin_lock_irqsave(&q->lock, flags);
	tail = skb_peek_tail(q);
	अगर (!tail || SKB_EXT_ERR(tail)->ee.ee_origin != SO_EE_ORIGIN_ZEROCOPY ||
	    !skb_zerocopy_notअगरy_extend(tail, lo, len)) अणु
		__skb_queue_tail(q, skb);
		skb = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);

	sk->sk_error_report(sk);

release:
	consume_skb(skb);
	sock_put(sk);
पूर्ण

व्योम msg_zerocopy_callback(काष्ठा sk_buff *skb, काष्ठा ubuf_info *uarg,
			   bool success)
अणु
	uarg->zerocopy = uarg->zerocopy & success;

	अगर (refcount_dec_and_test(&uarg->refcnt))
		__msg_zerocopy_callback(uarg);
पूर्ण
EXPORT_SYMBOL_GPL(msg_zerocopy_callback);

व्योम msg_zerocopy_put_पात(काष्ठा ubuf_info *uarg, bool have_uref)
अणु
	काष्ठा sock *sk = skb_from_uarg(uarg)->sk;

	atomic_dec(&sk->sk_zckey);
	uarg->len--;

	अगर (have_uref)
		msg_zerocopy_callback(शून्य, uarg, true);
पूर्ण
EXPORT_SYMBOL_GPL(msg_zerocopy_put_पात);

पूर्णांक skb_zerocopy_iter_dgram(काष्ठा sk_buff *skb, काष्ठा msghdr *msg, पूर्णांक len)
अणु
	वापस __zerocopy_sg_from_iter(skb->sk, skb, &msg->msg_iter, len);
पूर्ण
EXPORT_SYMBOL_GPL(skb_zerocopy_iter_dgram);

पूर्णांक skb_zerocopy_iter_stream(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     काष्ठा msghdr *msg, पूर्णांक len,
			     काष्ठा ubuf_info *uarg)
अणु
	काष्ठा ubuf_info *orig_uarg = skb_zcopy(skb);
	काष्ठा iov_iter orig_iter = msg->msg_iter;
	पूर्णांक err, orig_len = skb->len;

	/* An skb can only poपूर्णांक to one uarg. This edge हाल happens when
	 * TCP appends to an skb, but zerocopy_पुनः_स्मृति triggered a new alloc.
	 */
	अगर (orig_uarg && uarg != orig_uarg)
		वापस -EEXIST;

	err = __zerocopy_sg_from_iter(sk, skb, &msg->msg_iter, len);
	अगर (err == -EFAULT || (err == -EMSGSIZE && skb->len == orig_len)) अणु
		काष्ठा sock *save_sk = skb->sk;

		/* Streams करो not मुक्त skb on error. Reset to prev state. */
		msg->msg_iter = orig_iter;
		skb->sk = sk;
		___pskb_trim(skb, orig_len);
		skb->sk = save_sk;
		वापस err;
	पूर्ण

	skb_zcopy_set(skb, uarg, शून्य);
	वापस skb->len - orig_len;
पूर्ण
EXPORT_SYMBOL_GPL(skb_zerocopy_iter_stream);

अटल पूर्णांक skb_zerocopy_clone(काष्ठा sk_buff *nskb, काष्ठा sk_buff *orig,
			      gfp_t gfp_mask)
अणु
	अगर (skb_zcopy(orig)) अणु
		अगर (skb_zcopy(nskb)) अणु
			/* !gfp_mask callers are verअगरied to !skb_zcopy(nskb) */
			अगर (!gfp_mask) अणु
				WARN_ON_ONCE(1);
				वापस -ENOMEM;
			पूर्ण
			अगर (skb_uarg(nskb) == skb_uarg(orig))
				वापस 0;
			अगर (skb_copy_ubufs(nskb, GFP_ATOMIC))
				वापस -EIO;
		पूर्ण
		skb_zcopy_set(nskb, skb_uarg(orig), शून्य);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	skb_copy_ubufs	-	copy userspace skb frags buffers to kernel
 *	@skb: the skb to modअगरy
 *	@gfp_mask: allocation priority
 *
 *	This must be called on skb with SKBFL_ZEROCOPY_ENABLE.
 *	It will copy all frags पूर्णांकo kernel and drop the reference
 *	to userspace pages.
 *
 *	If this function is called from an पूर्णांकerrupt gfp_mask() must be
 *	%GFP_ATOMIC.
 *
 *	Returns 0 on success or a negative error code on failure
 *	to allocate kernel memory to copy to.
 */
पूर्णांक skb_copy_ubufs(काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	पूर्णांक num_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा page *page, *head = शून्य;
	पूर्णांक i, new_frags;
	u32 d_off;

	अगर (skb_shared(skb) || skb_unclone(skb, gfp_mask))
		वापस -EINVAL;

	अगर (!num_frags)
		जाओ release;

	new_frags = (__skb_pagelen(skb) + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < new_frags; i++) अणु
		page = alloc_page(gfp_mask);
		अगर (!page) अणु
			जबतक (head) अणु
				काष्ठा page *next = (काष्ठा page *)page_निजी(head);
				put_page(head);
				head = next;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		set_page_निजी(page, (अचिन्हित दीर्घ)head);
		head = page;
	पूर्ण

	page = head;
	d_off = 0;
	क्रम (i = 0; i < num_frags; i++) अणु
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];
		u32 p_off, p_len, copied;
		काष्ठा page *p;
		u8 *vaddr;

		skb_frag_क्रमeach_page(f, skb_frag_off(f), skb_frag_size(f),
				      p, p_off, p_len, copied) अणु
			u32 copy, करोne = 0;
			vaddr = kmap_atomic(p);

			जबतक (करोne < p_len) अणु
				अगर (d_off == PAGE_SIZE) अणु
					d_off = 0;
					page = (काष्ठा page *)page_निजी(page);
				पूर्ण
				copy = min_t(u32, PAGE_SIZE - d_off, p_len - करोne);
				स_नकल(page_address(page) + d_off,
				       vaddr + p_off + करोne, copy);
				करोne += copy;
				d_off += copy;
			पूर्ण
			kunmap_atomic(vaddr);
		पूर्ण
	पूर्ण

	/* skb frags release userspace buffers */
	क्रम (i = 0; i < num_frags; i++)
		skb_frag_unref(skb, i);

	/* skb frags poपूर्णांक to kernel buffers */
	क्रम (i = 0; i < new_frags - 1; i++) अणु
		__skb_fill_page_desc(skb, i, head, 0, PAGE_SIZE);
		head = (काष्ठा page *)page_निजी(head);
	पूर्ण
	__skb_fill_page_desc(skb, new_frags - 1, head, 0, d_off);
	skb_shinfo(skb)->nr_frags = new_frags;

release:
	skb_zcopy_clear(skb, false);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_copy_ubufs);

/**
 *	skb_clone	-	duplicate an sk_buff
 *	@skb: buffer to clone
 *	@gfp_mask: allocation priority
 *
 *	Duplicate an &sk_buff. The new one is not owned by a socket. Both
 *	copies share the same packet data but not काष्ठाure. The new
 *	buffer has a reference count of 1. If the allocation fails the
 *	function वापसs %शून्य otherwise the new buffer is वापसed.
 *
 *	If this function is called from an पूर्णांकerrupt gfp_mask() must be
 *	%GFP_ATOMIC.
 */

काष्ठा sk_buff *skb_clone(काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff_fclones *fclones = container_of(skb,
						       काष्ठा sk_buff_fclones,
						       skb1);
	काष्ठा sk_buff *n;

	अगर (skb_orphan_frags(skb, gfp_mask))
		वापस शून्य;

	अगर (skb->fclone == SKB_FCLONE_ORIG &&
	    refcount_पढ़ो(&fclones->fclone_ref) == 1) अणु
		n = &fclones->skb2;
		refcount_set(&fclones->fclone_ref, 2);
	पूर्ण अन्यथा अणु
		अगर (skb_pfmeदो_स्मृति(skb))
			gfp_mask |= __GFP_MEMALLOC;

		n = kmem_cache_alloc(skbuff_head_cache, gfp_mask);
		अगर (!n)
			वापस शून्य;

		n->fclone = SKB_FCLONE_UNAVAILABLE;
	पूर्ण

	वापस __skb_clone(n, skb);
पूर्ण
EXPORT_SYMBOL(skb_clone);

व्योम skb_headers_offset_update(काष्ठा sk_buff *skb, पूर्णांक off)
अणु
	/* Only adjust this अगर it actually is csum_start rather than csum */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start += off;
	/* अणुtransport,network,macपूर्ण_header and tail are relative to skb->head */
	skb->transport_header += off;
	skb->network_header   += off;
	अगर (skb_mac_header_was_set(skb))
		skb->mac_header += off;
	skb->inner_transport_header += off;
	skb->inner_network_header += off;
	skb->inner_mac_header += off;
पूर्ण
EXPORT_SYMBOL(skb_headers_offset_update);

व्योम skb_copy_header(काष्ठा sk_buff *new, स्थिर काष्ठा sk_buff *old)
अणु
	__copy_skb_header(new, old);

	skb_shinfo(new)->gso_size = skb_shinfo(old)->gso_size;
	skb_shinfo(new)->gso_segs = skb_shinfo(old)->gso_segs;
	skb_shinfo(new)->gso_type = skb_shinfo(old)->gso_type;
पूर्ण
EXPORT_SYMBOL(skb_copy_header);

अटल अंतरभूत पूर्णांक skb_alloc_rx_flag(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb_pfmeदो_स्मृति(skb))
		वापस SKB_ALLOC_RX;
	वापस 0;
पूर्ण

/**
 *	skb_copy	-	create निजी copy of an sk_buff
 *	@skb: buffer to copy
 *	@gfp_mask: allocation priority
 *
 *	Make a copy of both an &sk_buff and its data. This is used when the
 *	caller wishes to modअगरy the data and needs a निजी copy of the
 *	data to alter. Returns %शून्य on failure or the poपूर्णांकer to the buffer
 *	on success. The वापसed buffer has a reference count of 1.
 *
 *	As by-product this function converts non-linear &sk_buff to linear
 *	one, so that &sk_buff becomes completely निजी and caller is allowed
 *	to modअगरy all the data of वापसed buffer. This means that this
 *	function is not recommended क्रम use in circumstances when only
 *	header is going to be modअगरied. Use pskb_copy() instead.
 */

काष्ठा sk_buff *skb_copy(स्थिर काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	पूर्णांक headerlen = skb_headroom(skb);
	अचिन्हित पूर्णांक size = skb_end_offset(skb) + skb->data_len;
	काष्ठा sk_buff *n = __alloc_skb(size, gfp_mask,
					skb_alloc_rx_flag(skb), NUMA_NO_NODE);

	अगर (!n)
		वापस शून्य;

	/* Set the data poपूर्णांकer */
	skb_reserve(n, headerlen);
	/* Set the tail poपूर्णांकer and length */
	skb_put(n, skb->len);

	BUG_ON(skb_copy_bits(skb, -headerlen, n->head, headerlen + skb->len));

	skb_copy_header(n, skb);
	वापस n;
पूर्ण
EXPORT_SYMBOL(skb_copy);

/**
 *	__pskb_copy_fclone	-  create copy of an sk_buff with निजी head.
 *	@skb: buffer to copy
 *	@headroom: headroom of new skb
 *	@gfp_mask: allocation priority
 *	@fclone: अगर true allocate the copy of the skb from the fclone
 *	cache instead of the head cache; it is recommended to set this
 *	to true क्रम the हालs where the copy will likely be cloned
 *
 *	Make a copy of both an &sk_buff and part of its data, located
 *	in header. Fragmented data reमुख्य shared. This is used when
 *	the caller wishes to modअगरy only header of &sk_buff and needs
 *	निजी copy of the header to alter. Returns %शून्य on failure
 *	or the poपूर्णांकer to the buffer on success.
 *	The वापसed buffer has a reference count of 1.
 */

काष्ठा sk_buff *__pskb_copy_fclone(काष्ठा sk_buff *skb, पूर्णांक headroom,
				   gfp_t gfp_mask, bool fclone)
अणु
	अचिन्हित पूर्णांक size = skb_headlen(skb) + headroom;
	पूर्णांक flags = skb_alloc_rx_flag(skb) | (fclone ? SKB_ALLOC_FCLONE : 0);
	काष्ठा sk_buff *n = __alloc_skb(size, gfp_mask, flags, NUMA_NO_NODE);

	अगर (!n)
		जाओ out;

	/* Set the data poपूर्णांकer */
	skb_reserve(n, headroom);
	/* Set the tail poपूर्णांकer and length */
	skb_put(n, skb_headlen(skb));
	/* Copy the bytes */
	skb_copy_from_linear_data(skb, n->data, n->len);

	n->truesize += skb->data_len;
	n->data_len  = skb->data_len;
	n->len	     = skb->len;

	अगर (skb_shinfo(skb)->nr_frags) अणु
		पूर्णांक i;

		अगर (skb_orphan_frags(skb, gfp_mask) ||
		    skb_zerocopy_clone(n, skb, gfp_mask)) अणु
			kमुक्त_skb(n);
			n = शून्य;
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			skb_shinfo(n)->frags[i] = skb_shinfo(skb)->frags[i];
			skb_frag_ref(skb, i);
		पूर्ण
		skb_shinfo(n)->nr_frags = i;
	पूर्ण

	अगर (skb_has_frag_list(skb)) अणु
		skb_shinfo(n)->frag_list = skb_shinfo(skb)->frag_list;
		skb_clone_fraglist(n);
	पूर्ण

	skb_copy_header(n, skb);
out:
	वापस n;
पूर्ण
EXPORT_SYMBOL(__pskb_copy_fclone);

/**
 *	pskb_expand_head - पुनः_स्मृतिate header of &sk_buff
 *	@skb: buffer to पुनः_स्मृतिate
 *	@nhead: room to add at head
 *	@ntail: room to add at tail
 *	@gfp_mask: allocation priority
 *
 *	Expands (or creates identical copy, अगर @nhead and @ntail are zero)
 *	header of @skb. &sk_buff itself is not changed. &sk_buff MUST have
 *	reference count of 1. Returns zero in the हाल of success or error,
 *	अगर expansion failed. In the last हाल, &sk_buff is not changed.
 *
 *	All the poपूर्णांकers poपूर्णांकing पूर्णांकo skb header may change and must be
 *	reloaded after call to this function.
 */

पूर्णांक pskb_expand_head(काष्ठा sk_buff *skb, पूर्णांक nhead, पूर्णांक ntail,
		     gfp_t gfp_mask)
अणु
	पूर्णांक i, osize = skb_end_offset(skb);
	पूर्णांक size = osize + nhead + ntail;
	दीर्घ off;
	u8 *data;

	BUG_ON(nhead < 0);

	BUG_ON(skb_shared(skb));

	size = SKB_DATA_ALIGN(size);

	अगर (skb_pfmeदो_स्मृति(skb))
		gfp_mask |= __GFP_MEMALLOC;
	data = kदो_स्मृति_reserve(size + SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)),
			       gfp_mask, NUMA_NO_NODE, शून्य);
	अगर (!data)
		जाओ nodata;
	size = SKB_WITH_OVERHEAD(ksize(data));

	/* Copy only real data... and, alas, header. This should be
	 * optimized क्रम the हालs when header is व्योम.
	 */
	स_नकल(data + nhead, skb->head, skb_tail_poपूर्णांकer(skb) - skb->head);

	स_नकल((काष्ठा skb_shared_info *)(data + size),
	       skb_shinfo(skb),
	       दुरत्व(काष्ठा skb_shared_info, frags[skb_shinfo(skb)->nr_frags]));

	/*
	 * अगर shinfo is shared we must drop the old head gracefully, but अगर it
	 * is not we can just drop the old head and let the existing refcount
	 * be since all we did is relocate the values
	 */
	अगर (skb_cloned(skb)) अणु
		अगर (skb_orphan_frags(skb, gfp_mask))
			जाओ nofrags;
		अगर (skb_zcopy(skb))
			refcount_inc(&skb_uarg(skb)->refcnt);
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
			skb_frag_ref(skb, i);

		अगर (skb_has_frag_list(skb))
			skb_clone_fraglist(skb);

		skb_release_data(skb);
	पूर्ण अन्यथा अणु
		skb_मुक्त_head(skb);
	पूर्ण
	off = (data + nhead) - skb->head;

	skb->head     = data;
	skb->head_frag = 0;
	skb->data    += off;
#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
	skb->end      = size;
	off           = nhead;
#अन्यथा
	skb->end      = skb->head + size;
#पूर्ण_अगर
	skb->tail	      += off;
	skb_headers_offset_update(skb, nhead);
	skb->cloned   = 0;
	skb->hdr_len  = 0;
	skb->nohdr    = 0;
	atomic_set(&skb_shinfo(skb)->dataref, 1);

	skb_metadata_clear(skb);

	/* It is not generally safe to change skb->truesize.
	 * For the moment, we really care of rx path, or
	 * when skb is orphaned (not attached to a socket).
	 */
	अगर (!skb->sk || skb->deकाष्ठाor == sock_edemux)
		skb->truesize += size - osize;

	वापस 0;

nofrags:
	kमुक्त(data);
nodata:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(pskb_expand_head);

/* Make निजी copy of skb with writable head and some headroom */

काष्ठा sk_buff *skb_पुनः_स्मृति_headroom(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक headroom)
अणु
	काष्ठा sk_buff *skb2;
	पूर्णांक delta = headroom - skb_headroom(skb);

	अगर (delta <= 0)
		skb2 = pskb_copy(skb, GFP_ATOMIC);
	अन्यथा अणु
		skb2 = skb_clone(skb, GFP_ATOMIC);
		अगर (skb2 && pskb_expand_head(skb2, SKB_DATA_ALIGN(delta), 0,
					     GFP_ATOMIC)) अणु
			kमुक्त_skb(skb2);
			skb2 = शून्य;
		पूर्ण
	पूर्ण
	वापस skb2;
पूर्ण
EXPORT_SYMBOL(skb_पुनः_स्मृति_headroom);

/**
 *	skb_copy_expand	-	copy and expand sk_buff
 *	@skb: buffer to copy
 *	@newheadroom: new मुक्त bytes at head
 *	@newtailroom: new मुक्त bytes at tail
 *	@gfp_mask: allocation priority
 *
 *	Make a copy of both an &sk_buff and its data and जबतक करोing so
 *	allocate additional space.
 *
 *	This is used when the caller wishes to modअगरy the data and needs a
 *	निजी copy of the data to alter as well as more space क्रम new fields.
 *	Returns %शून्य on failure or the poपूर्णांकer to the buffer
 *	on success. The वापसed buffer has a reference count of 1.
 *
 *	You must pass %GFP_ATOMIC as the allocation priority अगर this function
 *	is called from an पूर्णांकerrupt.
 */
काष्ठा sk_buff *skb_copy_expand(स्थिर काष्ठा sk_buff *skb,
				पूर्णांक newheadroom, पूर्णांक newtailroom,
				gfp_t gfp_mask)
अणु
	/*
	 *	Allocate the copy buffer
	 */
	काष्ठा sk_buff *n = __alloc_skb(newheadroom + skb->len + newtailroom,
					gfp_mask, skb_alloc_rx_flag(skb),
					NUMA_NO_NODE);
	पूर्णांक oldheadroom = skb_headroom(skb);
	पूर्णांक head_copy_len, head_copy_off;

	अगर (!n)
		वापस शून्य;

	skb_reserve(n, newheadroom);

	/* Set the tail poपूर्णांकer and length */
	skb_put(n, skb->len);

	head_copy_len = oldheadroom;
	head_copy_off = 0;
	अगर (newheadroom <= head_copy_len)
		head_copy_len = newheadroom;
	अन्यथा
		head_copy_off = newheadroom - head_copy_len;

	/* Copy the linear header and data. */
	BUG_ON(skb_copy_bits(skb, -head_copy_len, n->head + head_copy_off,
			     skb->len + head_copy_len));

	skb_copy_header(n, skb);

	skb_headers_offset_update(n, newheadroom - oldheadroom);

	वापस n;
पूर्ण
EXPORT_SYMBOL(skb_copy_expand);

/**
 *	__skb_pad		-	zero pad the tail of an skb
 *	@skb: buffer to pad
 *	@pad: space to pad
 *	@मुक्त_on_error: मुक्त buffer on error
 *
 *	Ensure that a buffer is followed by a padding area that is zero
 *	filled. Used by network drivers which may DMA or transfer data
 *	beyond the buffer end onto the wire.
 *
 *	May वापस error in out of memory हालs. The skb is मुक्तd on error
 *	अगर @मुक्त_on_error is true.
 */

पूर्णांक __skb_pad(काष्ठा sk_buff *skb, पूर्णांक pad, bool मुक्त_on_error)
अणु
	पूर्णांक err;
	पूर्णांक ntail;

	/* If the skbuff is non linear tailroom is always zero.. */
	अगर (!skb_cloned(skb) && skb_tailroom(skb) >= pad) अणु
		स_रखो(skb->data+skb->len, 0, pad);
		वापस 0;
	पूर्ण

	ntail = skb->data_len + pad - (skb->end - skb->tail);
	अगर (likely(skb_cloned(skb) || ntail > 0)) अणु
		err = pskb_expand_head(skb, 0, ntail, GFP_ATOMIC);
		अगर (unlikely(err))
			जाओ मुक्त_skb;
	पूर्ण

	/* FIXME: The use of this function with non-linear skb's really needs
	 * to be audited.
	 */
	err = skb_linearize(skb);
	अगर (unlikely(err))
		जाओ मुक्त_skb;

	स_रखो(skb->data + skb->len, 0, pad);
	वापस 0;

मुक्त_skb:
	अगर (मुक्त_on_error)
		kमुक्त_skb(skb);
	वापस err;
पूर्ण
EXPORT_SYMBOL(__skb_pad);

/**
 *	pskb_put - add data to the tail of a potentially fragmented buffer
 *	@skb: start of the buffer to use
 *	@tail: tail fragment of the buffer to use
 *	@len: amount of data to add
 *
 *	This function extends the used data area of the potentially
 *	fragmented buffer. @tail must be the last fragment of @skb -- or
 *	@skb itself. If this would exceed the total buffer size the kernel
 *	will panic. A poपूर्णांकer to the first byte of the extra data is
 *	वापसed.
 */

व्योम *pskb_put(काष्ठा sk_buff *skb, काष्ठा sk_buff *tail, पूर्णांक len)
अणु
	अगर (tail != skb) अणु
		skb->data_len += len;
		skb->len += len;
	पूर्ण
	वापस skb_put(tail, len);
पूर्ण
EXPORT_SYMBOL_GPL(pskb_put);

/**
 *	skb_put - add data to a buffer
 *	@skb: buffer to use
 *	@len: amount of data to add
 *
 *	This function extends the used data area of the buffer. If this would
 *	exceed the total buffer size the kernel will panic. A poपूर्णांकer to the
 *	first byte of the extra data is वापसed.
 */
व्योम *skb_put(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = skb_tail_poपूर्णांकer(skb);
	SKB_LINEAR_ASSERT(skb);
	skb->tail += len;
	skb->len  += len;
	अगर (unlikely(skb->tail > skb->end))
		skb_over_panic(skb, len, __builtin_वापस_address(0));
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(skb_put);

/**
 *	skb_push - add data to the start of a buffer
 *	@skb: buffer to use
 *	@len: amount of data to add
 *
 *	This function extends the used data area of the buffer at the buffer
 *	start. If this would exceed the total buffer headroom the kernel will
 *	panic. A poपूर्णांकer to the first byte of the extra data is वापसed.
 */
व्योम *skb_push(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	skb->data -= len;
	skb->len  += len;
	अगर (unlikely(skb->data < skb->head))
		skb_under_panic(skb, len, __builtin_वापस_address(0));
	वापस skb->data;
पूर्ण
EXPORT_SYMBOL(skb_push);

/**
 *	skb_pull - हटाओ data from the start of a buffer
 *	@skb: buffer to use
 *	@len: amount of data to हटाओ
 *
 *	This function हटाओs data from the start of a buffer, वापसing
 *	the memory to the headroom. A poपूर्णांकer to the next data in the buffer
 *	is वापसed. Once the data has been pulled future pushes will overग_लिखो
 *	the old data.
 */
व्योम *skb_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस skb_pull_अंतरभूत(skb, len);
पूर्ण
EXPORT_SYMBOL(skb_pull);

/**
 *	skb_trim - हटाओ end from a buffer
 *	@skb: buffer to alter
 *	@len: new length
 *
 *	Cut the length of a buffer करोwn by removing data from the tail. If
 *	the buffer is alपढ़ोy under the length specअगरied it is not modअगरied.
 *	The skb must be linear.
 */
व्योम skb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb->len > len)
		__skb_trim(skb, len);
पूर्ण
EXPORT_SYMBOL(skb_trim);

/* Trims skb to length len. It can change skb poपूर्णांकers.
 */

पूर्णांक ___pskb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sk_buff **fragp;
	काष्ठा sk_buff *frag;
	पूर्णांक offset = skb_headlen(skb);
	पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	पूर्णांक i;
	पूर्णांक err;

	अगर (skb_cloned(skb) &&
	    unlikely((err = pskb_expand_head(skb, 0, 0, GFP_ATOMIC))))
		वापस err;

	i = 0;
	अगर (offset >= len)
		जाओ drop_pages;

	क्रम (; i < nfrags; i++) अणु
		पूर्णांक end = offset + skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (end < len) अणु
			offset = end;
			जारी;
		पूर्ण

		skb_frag_size_set(&skb_shinfo(skb)->frags[i++], len - offset);

drop_pages:
		skb_shinfo(skb)->nr_frags = i;

		क्रम (; i < nfrags; i++)
			skb_frag_unref(skb, i);

		अगर (skb_has_frag_list(skb))
			skb_drop_fraglist(skb);
		जाओ करोne;
	पूर्ण

	क्रम (fragp = &skb_shinfo(skb)->frag_list; (frag = *fragp);
	     fragp = &frag->next) अणु
		पूर्णांक end = offset + frag->len;

		अगर (skb_shared(frag)) अणु
			काष्ठा sk_buff *nfrag;

			nfrag = skb_clone(frag, GFP_ATOMIC);
			अगर (unlikely(!nfrag))
				वापस -ENOMEM;

			nfrag->next = frag->next;
			consume_skb(frag);
			frag = nfrag;
			*fragp = frag;
		पूर्ण

		अगर (end < len) अणु
			offset = end;
			जारी;
		पूर्ण

		अगर (end > len &&
		    unlikely((err = pskb_trim(frag, len - offset))))
			वापस err;

		अगर (frag->next)
			skb_drop_list(&frag->next);
		अवरोध;
	पूर्ण

करोne:
	अगर (len > skb_headlen(skb)) अणु
		skb->data_len -= skb->len - len;
		skb->len       = len;
	पूर्ण अन्यथा अणु
		skb->len       = len;
		skb->data_len  = 0;
		skb_set_tail_poपूर्णांकer(skb, len);
	पूर्ण

	अगर (!skb->sk || skb->deकाष्ठाor == sock_edemux)
		skb_condense(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(___pskb_trim);

/* Note : use pskb_trim_rcsum() instead of calling this directly
 */
पूर्णांक pskb_trim_rcsum_slow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		पूर्णांक delta = skb->len - len;

		skb->csum = csum_block_sub(skb->csum,
					   skb_checksum(skb, len, delta, 0),
					   len);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		पूर्णांक hdlen = (len > skb_headlen(skb)) ? skb_headlen(skb) : len;
		पूर्णांक offset = skb_checksum_start_offset(skb) + skb->csum_offset;

		अगर (offset + माप(__sum16) > hdlen)
			वापस -EINVAL;
	पूर्ण
	वापस __pskb_trim(skb, len);
पूर्ण
EXPORT_SYMBOL(pskb_trim_rcsum_slow);

/**
 *	__pskb_pull_tail - advance tail of skb header
 *	@skb: buffer to पुनः_स्मृतिate
 *	@delta: number of bytes to advance tail
 *
 *	The function makes a sense only on a fragmented &sk_buff,
 *	it expands header moving its tail क्रमward and copying necessary
 *	data from fragmented part.
 *
 *	&sk_buff MUST have reference count of 1.
 *
 *	Returns %शून्य (and &sk_buff करोes not change) अगर pull failed
 *	or value of new tail of skb in the हाल of success.
 *
 *	All the poपूर्णांकers poपूर्णांकing पूर्णांकo skb header may change and must be
 *	reloaded after call to this function.
 */

/* Moves tail of skb head क्रमward, copying data from fragmented part,
 * when it is necessary.
 * 1. It may fail due to दो_स्मृति failure.
 * 2. It may change skb poपूर्णांकers.
 *
 * It is pretty complicated. Luckily, it is called only in exceptional हालs.
 */
व्योम *__pskb_pull_tail(काष्ठा sk_buff *skb, पूर्णांक delta)
अणु
	/* If skb has not enough मुक्त space at tail, get new one
	 * plus 128 bytes क्रम future expansions. If we have enough
	 * room at tail, पुनः_स्मृतिate without expansion only अगर skb is cloned.
	 */
	पूर्णांक i, k, eat = (skb->tail + delta) - skb->end;

	अगर (eat > 0 || skb_cloned(skb)) अणु
		अगर (pskb_expand_head(skb, 0, eat > 0 ? eat + 128 : 0,
				     GFP_ATOMIC))
			वापस शून्य;
	पूर्ण

	BUG_ON(skb_copy_bits(skb, skb_headlen(skb),
			     skb_tail_poपूर्णांकer(skb), delta));

	/* Optimization: no fragments, no reasons to preestimate
	 * size of pulled pages. Superb.
	 */
	अगर (!skb_has_frag_list(skb))
		जाओ pull_pages;

	/* Estimate size of pulled pages. */
	eat = delta;
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (size >= eat)
			जाओ pull_pages;
		eat -= size;
	पूर्ण

	/* If we need update frag list, we are in troubles.
	 * Certainly, it is possible to add an offset to skb data,
	 * but taking पूर्णांकo account that pulling is expected to
	 * be very rare operation, it is worth to fight against
	 * further bloating skb head and crucअगरy ourselves here instead.
	 * Pure masohism, indeed. 8)8)
	 */
	अगर (eat) अणु
		काष्ठा sk_buff *list = skb_shinfo(skb)->frag_list;
		काष्ठा sk_buff *clone = शून्य;
		काष्ठा sk_buff *insp = शून्य;

		करो अणु
			अगर (list->len <= eat) अणु
				/* Eaten as whole. */
				eat -= list->len;
				list = list->next;
				insp = list;
			पूर्ण अन्यथा अणु
				/* Eaten partially. */

				अगर (skb_shared(list)) अणु
					/* Sucks! We need to विभाजन list. :-( */
					clone = skb_clone(list, GFP_ATOMIC);
					अगर (!clone)
						वापस शून्य;
					insp = list->next;
					list = clone;
				पूर्ण अन्यथा अणु
					/* This may be pulled without
					 * problems. */
					insp = list;
				पूर्ण
				अगर (!pskb_pull(list, eat)) अणु
					kमुक्त_skb(clone);
					वापस शून्य;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण जबतक (eat);

		/* Free pulled out fragments. */
		जबतक ((list = skb_shinfo(skb)->frag_list) != insp) अणु
			skb_shinfo(skb)->frag_list = list->next;
			kमुक्त_skb(list);
		पूर्ण
		/* And insert new clone at head. */
		अगर (clone) अणु
			clone->next = list;
			skb_shinfo(skb)->frag_list = clone;
		पूर्ण
	पूर्ण
	/* Success! Now we may commit changes to skb data. */

pull_pages:
	eat = delta;
	k = 0;
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (size <= eat) अणु
			skb_frag_unref(skb, i);
			eat -= size;
		पूर्ण अन्यथा अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[k];

			*frag = skb_shinfo(skb)->frags[i];
			अगर (eat) अणु
				skb_frag_off_add(frag, eat);
				skb_frag_size_sub(frag, eat);
				अगर (!i)
					जाओ end;
				eat = 0;
			पूर्ण
			k++;
		पूर्ण
	पूर्ण
	skb_shinfo(skb)->nr_frags = k;

end:
	skb->tail     += delta;
	skb->data_len -= delta;

	अगर (!skb->data_len)
		skb_zcopy_clear(skb, false);

	वापस skb_tail_poपूर्णांकer(skb);
पूर्ण
EXPORT_SYMBOL(__pskb_pull_tail);

/**
 *	skb_copy_bits - copy bits from skb to kernel buffer
 *	@skb: source skb
 *	@offset: offset in source
 *	@to: destination buffer
 *	@len: number of bytes to copy
 *
 *	Copy the specअगरied number of bytes from the source skb to the
 *	destination buffer.
 *
 *	CAUTION ! :
 *		If its prototype is ever changed,
 *		check arch/अणु*पूर्ण/net/अणु*पूर्ण.S files,
 *		since it is called from BPF assembly code.
 */
पूर्णांक skb_copy_bits(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, व्योम *to, पूर्णांक len)
अणु
	पूर्णांक start = skb_headlen(skb);
	काष्ठा sk_buff *frag_iter;
	पूर्णांक i, copy;

	अगर (offset > (पूर्णांक)skb->len - len)
		जाओ fault;

	/* Copy header. */
	अगर ((copy = start - offset) > 0) अणु
		अगर (copy > len)
			copy = len;
		skb_copy_from_linear_data_offset(skb, offset, to, copy);
		अगर ((len -= copy) == 0)
			वापस 0;
		offset += copy;
		to     += copy;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(f);
		अगर ((copy = end - offset) > 0) अणु
			u32 p_off, p_len, copied;
			काष्ठा page *p;
			u8 *vaddr;

			अगर (copy > len)
				copy = len;

			skb_frag_क्रमeach_page(f,
					      skb_frag_off(f) + offset - start,
					      copy, p, p_off, p_len, copied) अणु
				vaddr = kmap_atomic(p);
				स_नकल(to + copied, vaddr + p_off, p_len);
				kunmap_atomic(vaddr);
			पूर्ण

			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
			to     += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			अगर (skb_copy_bits(frag_iter, offset - start, to, copy))
				जाओ fault;
			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
			to     += copy;
		पूर्ण
		start = end;
	पूर्ण

	अगर (!len)
		वापस 0;

fault:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(skb_copy_bits);

/*
 * Callback from splice_to_pipe(), अगर we need to release some pages
 * at the end of the spd in हाल we error'ed out in filling the pipe.
 */
अटल व्योम sock_spd_release(काष्ठा splice_pipe_desc *spd, अचिन्हित पूर्णांक i)
अणु
	put_page(spd->pages[i]);
पूर्ण

अटल काष्ठा page *linear_to_page(काष्ठा page *page, अचिन्हित पूर्णांक *len,
				   अचिन्हित पूर्णांक *offset,
				   काष्ठा sock *sk)
अणु
	काष्ठा page_frag *pfrag = sk_page_frag(sk);

	अगर (!sk_page_frag_refill(sk, pfrag))
		वापस शून्य;

	*len = min_t(अचिन्हित पूर्णांक, *len, pfrag->size - pfrag->offset);

	स_नकल(page_address(pfrag->page) + pfrag->offset,
	       page_address(page) + *offset, *len);
	*offset = pfrag->offset;
	pfrag->offset += *len;

	वापस pfrag->page;
पूर्ण

अटल bool spd_can_coalesce(स्थिर काष्ठा splice_pipe_desc *spd,
			     काष्ठा page *page,
			     अचिन्हित पूर्णांक offset)
अणु
	वापस	spd->nr_pages &&
		spd->pages[spd->nr_pages - 1] == page &&
		(spd->partial[spd->nr_pages - 1].offset +
		 spd->partial[spd->nr_pages - 1].len == offset);
पूर्ण

/*
 * Fill page/offset/length पूर्णांकo spd, अगर it can hold more pages.
 */
अटल bool spd_fill_page(काष्ठा splice_pipe_desc *spd,
			  काष्ठा pipe_inode_info *pipe, काष्ठा page *page,
			  अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक offset,
			  bool linear,
			  काष्ठा sock *sk)
अणु
	अगर (unlikely(spd->nr_pages == MAX_SKB_FRAGS))
		वापस true;

	अगर (linear) अणु
		page = linear_to_page(page, len, &offset, sk);
		अगर (!page)
			वापस true;
	पूर्ण
	अगर (spd_can_coalesce(spd, page, offset)) अणु
		spd->partial[spd->nr_pages - 1].len += *len;
		वापस false;
	पूर्ण
	get_page(page);
	spd->pages[spd->nr_pages] = page;
	spd->partial[spd->nr_pages].len = *len;
	spd->partial[spd->nr_pages].offset = offset;
	spd->nr_pages++;

	वापस false;
पूर्ण

अटल bool __splice_segment(काष्ठा page *page, अचिन्हित पूर्णांक poff,
			     अचिन्हित पूर्णांक plen, अचिन्हित पूर्णांक *off,
			     अचिन्हित पूर्णांक *len,
			     काष्ठा splice_pipe_desc *spd, bool linear,
			     काष्ठा sock *sk,
			     काष्ठा pipe_inode_info *pipe)
अणु
	अगर (!*len)
		वापस true;

	/* skip this segment अगर alपढ़ोy processed */
	अगर (*off >= plen) अणु
		*off -= plen;
		वापस false;
	पूर्ण

	/* ignore any bits we alपढ़ोy processed */
	poff += *off;
	plen -= *off;
	*off = 0;

	करो अणु
		अचिन्हित पूर्णांक flen = min(*len, plen);

		अगर (spd_fill_page(spd, pipe, page, &flen, poff,
				  linear, sk))
			वापस true;
		poff += flen;
		plen -= flen;
		*len -= flen;
	पूर्ण जबतक (*len && plen);

	वापस false;
पूर्ण

/*
 * Map linear and fragment data from the skb to spd. It reports true अगर the
 * pipe is full or अगर we alपढ़ोy spliced the requested length.
 */
अटल bool __skb_splice_bits(काष्ठा sk_buff *skb, काष्ठा pipe_inode_info *pipe,
			      अचिन्हित पूर्णांक *offset, अचिन्हित पूर्णांक *len,
			      काष्ठा splice_pipe_desc *spd, काष्ठा sock *sk)
अणु
	पूर्णांक seg;
	काष्ठा sk_buff *iter;

	/* map the linear part :
	 * If skb->head_frag is set, this 'linear' part is backed by a
	 * fragment, and अगर the head is not shared with any clones then
	 * we can aव्योम a copy since we own the head portion of this page.
	 */
	अगर (__splice_segment(virt_to_page(skb->data),
			     (अचिन्हित दीर्घ) skb->data & (PAGE_SIZE - 1),
			     skb_headlen(skb),
			     offset, len, spd,
			     skb_head_is_locked(skb),
			     sk, pipe))
		वापस true;

	/*
	 * then map the fragments
	 */
	क्रम (seg = 0; seg < skb_shinfo(skb)->nr_frags; seg++) अणु
		स्थिर skb_frag_t *f = &skb_shinfo(skb)->frags[seg];

		अगर (__splice_segment(skb_frag_page(f),
				     skb_frag_off(f), skb_frag_size(f),
				     offset, len, spd, false, sk, pipe))
			वापस true;
	पूर्ण

	skb_walk_frags(skb, iter) अणु
		अगर (*offset >= iter->len) अणु
			*offset -= iter->len;
			जारी;
		पूर्ण
		/* __skb_splice_bits() only fails अगर the output has no room
		 * left, so no poपूर्णांक in going over the frag_list क्रम the error
		 * हाल.
		 */
		अगर (__skb_splice_bits(iter, pipe, offset, len, spd, sk))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Map data from the skb to a pipe. Should handle both the linear part,
 * the fragments, and the frag list.
 */
पूर्णांक skb_splice_bits(काष्ठा sk_buff *skb, काष्ठा sock *sk, अचिन्हित पूर्णांक offset,
		    काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक tlen,
		    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा partial_page partial[MAX_SKB_FRAGS];
	काष्ठा page *pages[MAX_SKB_FRAGS];
	काष्ठा splice_pipe_desc spd = अणु
		.pages = pages,
		.partial = partial,
		.nr_pages_max = MAX_SKB_FRAGS,
		.ops = &nosteal_pipe_buf_ops,
		.spd_release = sock_spd_release,
	पूर्ण;
	पूर्णांक ret = 0;

	__skb_splice_bits(skb, pipe, &offset, &tlen, &spd, sk);

	अगर (spd.nr_pages)
		ret = splice_to_pipe(pipe, &spd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skb_splice_bits);

अटल पूर्णांक sendmsg_unlocked(काष्ठा sock *sk, काष्ठा msghdr *msg,
			    काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार size)
अणु
	काष्ठा socket *sock = sk->sk_socket;

	अगर (!sock)
		वापस -EINVAL;
	वापस kernel_sendmsg(sock, msg, vec, num, size);
पूर्ण

अटल पूर्णांक sendpage_unlocked(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			     माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा socket *sock = sk->sk_socket;

	अगर (!sock)
		वापस -EINVAL;
	वापस kernel_sendpage(sock, page, offset, size, flags);
पूर्ण

प्रकार पूर्णांक (*sendmsg_func)(काष्ठा sock *sk, काष्ठा msghdr *msg,
			    काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार size);
प्रकार पूर्णांक (*sendpage_func)(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			     माप_प्रकार size, पूर्णांक flags);
अटल पूर्णांक __skb_send_sock(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक offset,
			   पूर्णांक len, sendmsg_func sendmsg, sendpage_func sendpage)
अणु
	अचिन्हित पूर्णांक orig_len = len;
	काष्ठा sk_buff *head = skb;
	अचिन्हित लघु fragidx;
	पूर्णांक slen, ret;

करो_frag_list:

	/* Deal with head data */
	जबतक (offset < skb_headlen(skb) && len) अणु
		काष्ठा kvec kv;
		काष्ठा msghdr msg;

		slen = min_t(पूर्णांक, len, skb_headlen(skb) - offset);
		kv.iov_base = skb->data + offset;
		kv.iov_len = slen;
		स_रखो(&msg, 0, माप(msg));
		msg.msg_flags = MSG_DONTWAIT;

		ret = INसूचीECT_CALL_2(sendmsg, kernel_sendmsg_locked,
				      sendmsg_unlocked, sk, &msg, &kv, 1, slen);
		अगर (ret <= 0)
			जाओ error;

		offset += ret;
		len -= ret;
	पूर्ण

	/* All the data was skb head? */
	अगर (!len)
		जाओ out;

	/* Make offset relative to start of frags */
	offset -= skb_headlen(skb);

	/* Find where we are in frag list */
	क्रम (fragidx = 0; fragidx < skb_shinfo(skb)->nr_frags; fragidx++) अणु
		skb_frag_t *frag  = &skb_shinfo(skb)->frags[fragidx];

		अगर (offset < skb_frag_size(frag))
			अवरोध;

		offset -= skb_frag_size(frag);
	पूर्ण

	क्रम (; len && fragidx < skb_shinfo(skb)->nr_frags; fragidx++) अणु
		skb_frag_t *frag  = &skb_shinfo(skb)->frags[fragidx];

		slen = min_t(माप_प्रकार, len, skb_frag_size(frag) - offset);

		जबतक (slen) अणु
			ret = INसूचीECT_CALL_2(sendpage, kernel_sendpage_locked,
					      sendpage_unlocked, sk,
					      skb_frag_page(frag),
					      skb_frag_off(frag) + offset,
					      slen, MSG_DONTWAIT);
			अगर (ret <= 0)
				जाओ error;

			len -= ret;
			offset += ret;
			slen -= ret;
		पूर्ण

		offset = 0;
	पूर्ण

	अगर (len) अणु
		/* Process any frag lists */

		अगर (skb == head) अणु
			अगर (skb_has_frag_list(skb)) अणु
				skb = skb_shinfo(skb)->frag_list;
				जाओ करो_frag_list;
			पूर्ण
		पूर्ण अन्यथा अगर (skb->next) अणु
			skb = skb->next;
			जाओ करो_frag_list;
		पूर्ण
	पूर्ण

out:
	वापस orig_len - len;

error:
	वापस orig_len == len ? ret : orig_len - len;
पूर्ण

/* Send skb data on a socket. Socket must be locked. */
पूर्णांक skb_send_sock_locked(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक offset,
			 पूर्णांक len)
अणु
	वापस __skb_send_sock(sk, skb, offset, len, kernel_sendmsg_locked,
			       kernel_sendpage_locked);
पूर्ण
EXPORT_SYMBOL_GPL(skb_send_sock_locked);

/* Send skb data on a socket. Socket must be unlocked. */
पूर्णांक skb_send_sock(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len)
अणु
	वापस __skb_send_sock(sk, skb, offset, len, sendmsg_unlocked,
			       sendpage_unlocked);
पूर्ण

/**
 *	skb_store_bits - store bits from kernel buffer to skb
 *	@skb: destination buffer
 *	@offset: offset in destination
 *	@from: source buffer
 *	@len: number of bytes to copy
 *
 *	Copy the specअगरied number of bytes from the source buffer to the
 *	destination skb.  This function handles all the messy bits of
 *	traversing fragment lists and such.
 */

पूर्णांक skb_store_bits(काष्ठा sk_buff *skb, पूर्णांक offset, स्थिर व्योम *from, पूर्णांक len)
अणु
	पूर्णांक start = skb_headlen(skb);
	काष्ठा sk_buff *frag_iter;
	पूर्णांक i, copy;

	अगर (offset > (पूर्णांक)skb->len - len)
		जाओ fault;

	अगर ((copy = start - offset) > 0) अणु
		अगर (copy > len)
			copy = len;
		skb_copy_to_linear_data_offset(skb, offset, from, copy);
		अगर ((len -= copy) == 0)
			वापस 0;
		offset += copy;
		from += copy;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(frag);
		अगर ((copy = end - offset) > 0) अणु
			u32 p_off, p_len, copied;
			काष्ठा page *p;
			u8 *vaddr;

			अगर (copy > len)
				copy = len;

			skb_frag_क्रमeach_page(frag,
					      skb_frag_off(frag) + offset - start,
					      copy, p, p_off, p_len, copied) अणु
				vaddr = kmap_atomic(p);
				स_नकल(vaddr + p_off, from + copied, p_len);
				kunmap_atomic(vaddr);
			पूर्ण

			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
			from += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			अगर (skb_store_bits(frag_iter, offset - start,
					   from, copy))
				जाओ fault;
			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
			from += copy;
		पूर्ण
		start = end;
	पूर्ण
	अगर (!len)
		वापस 0;

fault:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(skb_store_bits);

/* Checksum skb data. */
__wsum __skb_checksum(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
		      __wsum csum, स्थिर काष्ठा skb_checksum_ops *ops)
अणु
	पूर्णांक start = skb_headlen(skb);
	पूर्णांक i, copy = start - offset;
	काष्ठा sk_buff *frag_iter;
	पूर्णांक pos = 0;

	/* Checksum header. */
	अगर (copy > 0) अणु
		अगर (copy > len)
			copy = len;
		csum = INसूचीECT_CALL_1(ops->update, csum_partial_ext,
				       skb->data + offset, copy, csum);
		अगर ((len -= copy) == 0)
			वापस csum;
		offset += copy;
		pos	= copy;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(frag);
		अगर ((copy = end - offset) > 0) अणु
			u32 p_off, p_len, copied;
			काष्ठा page *p;
			__wsum csum2;
			u8 *vaddr;

			अगर (copy > len)
				copy = len;

			skb_frag_क्रमeach_page(frag,
					      skb_frag_off(frag) + offset - start,
					      copy, p, p_off, p_len, copied) अणु
				vaddr = kmap_atomic(p);
				csum2 = INसूचीECT_CALL_1(ops->update,
							csum_partial_ext,
							vaddr + p_off, p_len, 0);
				kunmap_atomic(vaddr);
				csum = INसूचीECT_CALL_1(ops->combine,
						       csum_block_add_ext, csum,
						       csum2, pos, p_len);
				pos += p_len;
			पूर्ण

			अगर (!(len -= copy))
				वापस csum;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			__wsum csum2;
			अगर (copy > len)
				copy = len;
			csum2 = __skb_checksum(frag_iter, offset - start,
					       copy, 0, ops);
			csum = INसूचीECT_CALL_1(ops->combine, csum_block_add_ext,
					       csum, csum2, pos, copy);
			अगर ((len -= copy) == 0)
				वापस csum;
			offset += copy;
			pos    += copy;
		पूर्ण
		start = end;
	पूर्ण
	BUG_ON(len);

	वापस csum;
पूर्ण
EXPORT_SYMBOL(__skb_checksum);

__wsum skb_checksum(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
		    पूर्णांक len, __wsum csum)
अणु
	स्थिर काष्ठा skb_checksum_ops ops = अणु
		.update  = csum_partial_ext,
		.combine = csum_block_add_ext,
	पूर्ण;

	वापस __skb_checksum(skb, offset, len, csum, &ops);
पूर्ण
EXPORT_SYMBOL(skb_checksum);

/* Both of above in one bottle. */

__wsum skb_copy_and_csum_bits(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
				    u8 *to, पूर्णांक len)
अणु
	पूर्णांक start = skb_headlen(skb);
	पूर्णांक i, copy = start - offset;
	काष्ठा sk_buff *frag_iter;
	पूर्णांक pos = 0;
	__wsum csum = 0;

	/* Copy header. */
	अगर (copy > 0) अणु
		अगर (copy > len)
			copy = len;
		csum = csum_partial_copy_nocheck(skb->data + offset, to,
						 copy);
		अगर ((len -= copy) == 0)
			वापस csum;
		offset += copy;
		to     += copy;
		pos	= copy;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(&skb_shinfo(skb)->frags[i]);
		अगर ((copy = end - offset) > 0) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			u32 p_off, p_len, copied;
			काष्ठा page *p;
			__wsum csum2;
			u8 *vaddr;

			अगर (copy > len)
				copy = len;

			skb_frag_क्रमeach_page(frag,
					      skb_frag_off(frag) + offset - start,
					      copy, p, p_off, p_len, copied) अणु
				vaddr = kmap_atomic(p);
				csum2 = csum_partial_copy_nocheck(vaddr + p_off,
								  to + copied,
								  p_len);
				kunmap_atomic(vaddr);
				csum = csum_block_add(csum, csum2, pos);
				pos += p_len;
			पूर्ण

			अगर (!(len -= copy))
				वापस csum;
			offset += copy;
			to     += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		__wsum csum2;
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			csum2 = skb_copy_and_csum_bits(frag_iter,
						       offset - start,
						       to, copy);
			csum = csum_block_add(csum, csum2, pos);
			अगर ((len -= copy) == 0)
				वापस csum;
			offset += copy;
			to     += copy;
			pos    += copy;
		पूर्ण
		start = end;
	पूर्ण
	BUG_ON(len);
	वापस csum;
पूर्ण
EXPORT_SYMBOL(skb_copy_and_csum_bits);

__sum16 __skb_checksum_complete_head(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	__sum16 sum;

	sum = csum_fold(skb_checksum(skb, 0, len, skb->csum));
	/* See comments in __skb_checksum_complete(). */
	अगर (likely(!sum)) अणु
		अगर (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	पूर्ण
	अगर (!skb_shared(skb))
		skb->csum_valid = !sum;
	वापस sum;
पूर्ण
EXPORT_SYMBOL(__skb_checksum_complete_head);

/* This function assumes skb->csum alपढ़ोy holds pseuकरो header's checksum,
 * which has been changed from the hardware checksum, क्रम example, by
 * __skb_checksum_validate_complete(). And, the original skb->csum must
 * have been validated unsuccessfully क्रम CHECKSUM_COMPLETE हाल.
 *
 * It वापसs non-zero अगर the recomputed checksum is still invalid, otherwise
 * zero. The new checksum is stored back पूर्णांकo skb->csum unless the skb is
 * shared.
 */
__sum16 __skb_checksum_complete(काष्ठा sk_buff *skb)
अणु
	__wsum csum;
	__sum16 sum;

	csum = skb_checksum(skb, 0, skb->len, 0);

	sum = csum_fold(csum_add(skb->csum, csum));
	/* This check is inverted, because we alपढ़ोy knew the hardware
	 * checksum is invalid beक्रमe calling this function. So, अगर the
	 * re-computed checksum is valid instead, then we have a mismatch
	 * between the original skb->csum and skb_checksum(). This means either
	 * the original hardware checksum is incorrect or we screw up skb->csum
	 * when moving skb->data around.
	 */
	अगर (likely(!sum)) अणु
		अगर (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	पूर्ण

	अगर (!skb_shared(skb)) अणु
		/* Save full packet checksum */
		skb->csum = csum;
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum_complete_sw = 1;
		skb->csum_valid = !sum;
	पूर्ण

	वापस sum;
पूर्ण
EXPORT_SYMBOL(__skb_checksum_complete);

अटल __wsum warn_crc32c_csum_update(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	net_warn_ratelimited(
		"%s: attempt to compute crc32c without libcrc32c.ko\n",
		__func__);
	वापस 0;
पूर्ण

अटल __wsum warn_crc32c_csum_combine(__wsum csum, __wsum csum2,
				       पूर्णांक offset, पूर्णांक len)
अणु
	net_warn_ratelimited(
		"%s: attempt to compute crc32c without libcrc32c.ko\n",
		__func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा skb_checksum_ops शेष_crc32c_ops = अणु
	.update  = warn_crc32c_csum_update,
	.combine = warn_crc32c_csum_combine,
पूर्ण;

स्थिर काष्ठा skb_checksum_ops *crc32c_csum_stub __पढ़ो_mostly =
	&शेष_crc32c_ops;
EXPORT_SYMBOL(crc32c_csum_stub);

 /**
 *	skb_zerocopy_headlen - Calculate headroom needed क्रम skb_zerocopy()
 *	@from: source buffer
 *
 *	Calculates the amount of linear headroom needed in the 'to' skb passed
 *	पूर्णांकo skb_zerocopy().
 */
अचिन्हित पूर्णांक
skb_zerocopy_headlen(स्थिर काष्ठा sk_buff *from)
अणु
	अचिन्हित पूर्णांक hlen = 0;

	अगर (!from->head_frag ||
	    skb_headlen(from) < L1_CACHE_BYTES ||
	    skb_shinfo(from)->nr_frags >= MAX_SKB_FRAGS)
		hlen = skb_headlen(from);

	अगर (skb_has_frag_list(from))
		hlen = from->len;

	वापस hlen;
पूर्ण
EXPORT_SYMBOL_GPL(skb_zerocopy_headlen);

/**
 *	skb_zerocopy - Zero copy skb to skb
 *	@to: destination buffer
 *	@from: source buffer
 *	@len: number of bytes to copy from source buffer
 *	@hlen: size of linear headroom in destination buffer
 *
 *	Copies up to `len` bytes from `from` to `to` by creating references
 *	to the frags in the source buffer.
 *
 *	The `hlen` as calculated by skb_zerocopy_headlen() specअगरies the
 *	headroom in the `to` buffer.
 *
 *	Return value:
 *	0: everything is OK
 *	-ENOMEM: couldn't orphan frags of @from due to lack of memory
 *	-EFAULT: skb_copy_bits() found some problem with skb geometry
 */
पूर्णांक
skb_zerocopy(काष्ठा sk_buff *to, काष्ठा sk_buff *from, पूर्णांक len, पूर्णांक hlen)
अणु
	पूर्णांक i, j = 0;
	पूर्णांक plen = 0; /* length of skb->head fragment */
	पूर्णांक ret;
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset;

	BUG_ON(!from->head_frag && !hlen);

	/* करोnt bother with small payloads */
	अगर (len <= skb_tailroom(to))
		वापस skb_copy_bits(from, 0, skb_put(to, len), len);

	अगर (hlen) अणु
		ret = skb_copy_bits(from, 0, skb_put(to, hlen), hlen);
		अगर (unlikely(ret))
			वापस ret;
		len -= hlen;
	पूर्ण अन्यथा अणु
		plen = min_t(पूर्णांक, skb_headlen(from), len);
		अगर (plen) अणु
			page = virt_to_head_page(from->head);
			offset = from->data - (अचिन्हित अक्षर *)page_address(page);
			__skb_fill_page_desc(to, 0, page, offset, plen);
			get_page(page);
			j = 1;
			len -= plen;
		पूर्ण
	पूर्ण

	to->truesize += len + plen;
	to->len += len + plen;
	to->data_len += len + plen;

	अगर (unlikely(skb_orphan_frags(from, GFP_ATOMIC))) अणु
		skb_tx_error(from);
		वापस -ENOMEM;
	पूर्ण
	skb_zerocopy_clone(to, from, GFP_ATOMIC);

	क्रम (i = 0; i < skb_shinfo(from)->nr_frags; i++) अणु
		पूर्णांक size;

		अगर (!len)
			अवरोध;
		skb_shinfo(to)->frags[j] = skb_shinfo(from)->frags[i];
		size = min_t(पूर्णांक, skb_frag_size(&skb_shinfo(to)->frags[j]),
					len);
		skb_frag_size_set(&skb_shinfo(to)->frags[j], size);
		len -= size;
		skb_frag_ref(to, j);
		j++;
	पूर्ण
	skb_shinfo(to)->nr_frags = j;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_zerocopy);

व्योम skb_copy_and_csum_dev(स्थिर काष्ठा sk_buff *skb, u8 *to)
अणु
	__wsum csum;
	दीर्घ csstart;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		csstart = skb_checksum_start_offset(skb);
	अन्यथा
		csstart = skb_headlen(skb);

	BUG_ON(csstart > skb_headlen(skb));

	skb_copy_from_linear_data(skb, to, csstart);

	csum = 0;
	अगर (csstart != skb->len)
		csum = skb_copy_and_csum_bits(skb, csstart, to + csstart,
					      skb->len - csstart);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		दीर्घ csstuff = csstart + skb->csum_offset;

		*((__sum16 *)(to + csstuff)) = csum_fold(csum);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(skb_copy_and_csum_dev);

/**
 *	skb_dequeue - हटाओ from the head of the queue
 *	@list: list to dequeue from
 *
 *	Remove the head of the list. The list lock is taken so the function
 *	may be used safely with other locking list functions. The head item is
 *	वापसed or %शून्य अगर the list is empty.
 */

काष्ठा sk_buff *skb_dequeue(काष्ठा sk_buff_head *list)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *result;

	spin_lock_irqsave(&list->lock, flags);
	result = __skb_dequeue(list);
	spin_unlock_irqrestore(&list->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(skb_dequeue);

/**
 *	skb_dequeue_tail - हटाओ from the tail of the queue
 *	@list: list to dequeue from
 *
 *	Remove the tail of the list. The list lock is taken so the function
 *	may be used safely with other locking list functions. The tail item is
 *	वापसed or %शून्य अगर the list is empty.
 */
काष्ठा sk_buff *skb_dequeue_tail(काष्ठा sk_buff_head *list)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *result;

	spin_lock_irqsave(&list->lock, flags);
	result = __skb_dequeue_tail(list);
	spin_unlock_irqrestore(&list->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(skb_dequeue_tail);

/**
 *	skb_queue_purge - empty a list
 *	@list: list to empty
 *
 *	Delete all buffers on an &sk_buff list. Each buffer is हटाओd from
 *	the list and one reference dropped. This function takes the list
 *	lock and is atomic with respect to other list locking functions.
 */
व्योम skb_queue_purge(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;
	जबतक ((skb = skb_dequeue(list)) != शून्य)
		kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(skb_queue_purge);

/**
 *	skb_rbtree_purge - empty a skb rbtree
 *	@root: root of the rbtree to empty
 *	Return value: the sum of truesizes of all purged skbs.
 *
 *	Delete all buffers on an &sk_buff rbtree. Each buffer is हटाओd from
 *	the list and one reference dropped. This function करोes not take
 *	any lock. Synchronization should be handled by the caller (e.g., TCP
 *	out-of-order queue is रक्षित by the socket lock).
 */
अचिन्हित पूर्णांक skb_rbtree_purge(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *p = rb_first(root);
	अचिन्हित पूर्णांक sum = 0;

	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_entry(p, काष्ठा sk_buff, rbnode);

		p = rb_next(p);
		rb_erase(&skb->rbnode, root);
		sum += skb->truesize;
		kमुक्त_skb(skb);
	पूर्ण
	वापस sum;
पूर्ण

/**
 *	skb_queue_head - queue a buffer at the list head
 *	@list: list to use
 *	@newsk: buffer to queue
 *
 *	Queue a buffer at the start of the list. This function takes the
 *	list lock and can be used safely with other locking &sk_buff functions
 *	safely.
 *
 *	A buffer cannot be placed on two lists at the same समय.
 */
व्योम skb_queue_head(काष्ठा sk_buff_head *list, काष्ठा sk_buff *newsk)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	__skb_queue_head(list, newsk);
	spin_unlock_irqrestore(&list->lock, flags);
पूर्ण
EXPORT_SYMBOL(skb_queue_head);

/**
 *	skb_queue_tail - queue a buffer at the list tail
 *	@list: list to use
 *	@newsk: buffer to queue
 *
 *	Queue a buffer at the tail of the list. This function takes the
 *	list lock and can be used safely with other locking &sk_buff functions
 *	safely.
 *
 *	A buffer cannot be placed on two lists at the same समय.
 */
व्योम skb_queue_tail(काष्ठा sk_buff_head *list, काष्ठा sk_buff *newsk)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	__skb_queue_tail(list, newsk);
	spin_unlock_irqrestore(&list->lock, flags);
पूर्ण
EXPORT_SYMBOL(skb_queue_tail);

/**
 *	skb_unlink	-	हटाओ a buffer from a list
 *	@skb: buffer to हटाओ
 *	@list: list to use
 *
 *	Remove a packet from a list. The list locks are taken and this
 *	function is atomic with respect to other list locked calls
 *
 *	You must know what list the SKB is on.
 */
व्योम skb_unlink(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	__skb_unlink(skb, list);
	spin_unlock_irqrestore(&list->lock, flags);
पूर्ण
EXPORT_SYMBOL(skb_unlink);

/**
 *	skb_append	-	append a buffer
 *	@old: buffer to insert after
 *	@newsk: buffer to insert
 *	@list: list to use
 *
 *	Place a packet after a given packet in a list. The list locks are taken
 *	and this function is atomic with respect to other list locked calls.
 *	A buffer cannot be placed on two lists at the same समय.
 */
व्योम skb_append(काष्ठा sk_buff *old, काष्ठा sk_buff *newsk, काष्ठा sk_buff_head *list)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	__skb_queue_after(list, old, newsk);
	spin_unlock_irqrestore(&list->lock, flags);
पूर्ण
EXPORT_SYMBOL(skb_append);

अटल अंतरभूत व्योम skb_split_inside_header(काष्ठा sk_buff *skb,
					   काष्ठा sk_buff* skb1,
					   स्थिर u32 len, स्थिर पूर्णांक pos)
अणु
	पूर्णांक i;

	skb_copy_from_linear_data_offset(skb, len, skb_put(skb1, pos - len),
					 pos - len);
	/* And move data appendix as is. */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
		skb_shinfo(skb1)->frags[i] = skb_shinfo(skb)->frags[i];

	skb_shinfo(skb1)->nr_frags = skb_shinfo(skb)->nr_frags;
	skb_shinfo(skb)->nr_frags  = 0;
	skb1->data_len		   = skb->data_len;
	skb1->len		   += skb1->data_len;
	skb->data_len		   = 0;
	skb->len		   = len;
	skb_set_tail_poपूर्णांकer(skb, len);
पूर्ण

अटल अंतरभूत व्योम skb_split_no_header(काष्ठा sk_buff *skb,
				       काष्ठा sk_buff* skb1,
				       स्थिर u32 len, पूर्णांक pos)
अणु
	पूर्णांक i, k = 0;
	स्थिर पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;

	skb_shinfo(skb)->nr_frags = 0;
	skb1->len		  = skb1->data_len = skb->len - len;
	skb->len		  = len;
	skb->data_len		  = len - pos;

	क्रम (i = 0; i < nfrags; i++) अणु
		पूर्णांक size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (pos + size > len) अणु
			skb_shinfo(skb1)->frags[k] = skb_shinfo(skb)->frags[i];

			अगर (pos < len) अणु
				/* Split frag.
				 * We have two variants in this हाल:
				 * 1. Move all the frag to the second
				 *    part, अगर it is possible. F.e.
				 *    this approach is mandatory क्रम TUX,
				 *    where splitting is expensive.
				 * 2. Split is accurately. We make this.
				 */
				skb_frag_ref(skb, i);
				skb_frag_off_add(&skb_shinfo(skb1)->frags[0], len - pos);
				skb_frag_size_sub(&skb_shinfo(skb1)->frags[0], len - pos);
				skb_frag_size_set(&skb_shinfo(skb)->frags[i], len - pos);
				skb_shinfo(skb)->nr_frags++;
			पूर्ण
			k++;
		पूर्ण अन्यथा
			skb_shinfo(skb)->nr_frags++;
		pos += size;
	पूर्ण
	skb_shinfo(skb1)->nr_frags = k;
पूर्ण

/**
 * skb_split - Split fragmented skb to two parts at length len.
 * @skb: the buffer to split
 * @skb1: the buffer to receive the second part
 * @len: new length क्रम skb
 */
व्योम skb_split(काष्ठा sk_buff *skb, काष्ठा sk_buff *skb1, स्थिर u32 len)
अणु
	पूर्णांक pos = skb_headlen(skb);

	skb_shinfo(skb1)->flags |= skb_shinfo(skb)->flags & SKBFL_SHARED_FRAG;
	skb_zerocopy_clone(skb1, skb, 0);
	अगर (len < pos)	/* Split line is inside header. */
		skb_split_inside_header(skb, skb1, len, pos);
	अन्यथा		/* Second chunk has no header, nothing to copy. */
		skb_split_no_header(skb, skb1, len, pos);
पूर्ण
EXPORT_SYMBOL(skb_split);

/* Shअगरting from/to a cloned skb is a no-go.
 *
 * Caller cannot keep skb_shinfo related poपूर्णांकers past calling here!
 */
अटल पूर्णांक skb_prepare_क्रम_shअगरt(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;

	अगर (skb_cloned(skb)) अणु
		/* Save and restore truesize: pskb_expand_head() may पुनः_स्मृतिate
		 * memory where ksize(kदो_स्मृति(S)) != ksize(kदो_स्मृति(S)), but we
		 * cannot change truesize at this poपूर्णांक.
		 */
		अचिन्हित पूर्णांक save_truesize = skb->truesize;

		ret = pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
		skb->truesize = save_truesize;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * skb_shअगरt - Shअगरts paged data partially from skb to another
 * @tgt: buffer पूर्णांकo which tail data माला_लो added
 * @skb: buffer from which the paged data comes from
 * @shअगरtlen: shअगरt up to this many bytes
 *
 * Attempts to shअगरt up to shअगरtlen worth of bytes, which may be less than
 * the length of the skb, from skb to tgt. Returns number bytes shअगरted.
 * It's up to caller to मुक्त skb अगर everything was shअगरted.
 *
 * If @tgt runs out of frags, the whole operation is पातed.
 *
 * Skb cannot include anything अन्यथा but paged data जबतक tgt is allowed
 * to have non-paged data as well.
 *
 * TODO: full sized shअगरt could be optimized but that would need
 * specialized skb मुक्त'er to handle frags without up-to-date nr_frags.
 */
पूर्णांक skb_shअगरt(काष्ठा sk_buff *tgt, काष्ठा sk_buff *skb, पूर्णांक shअगरtlen)
अणु
	पूर्णांक from, to, merge, toकरो;
	skb_frag_t *fragfrom, *fragto;

	BUG_ON(shअगरtlen > skb->len);

	अगर (skb_headlen(skb))
		वापस 0;
	अगर (skb_zcopy(tgt) || skb_zcopy(skb))
		वापस 0;

	toकरो = shअगरtlen;
	from = 0;
	to = skb_shinfo(tgt)->nr_frags;
	fragfrom = &skb_shinfo(skb)->frags[from];

	/* Actual merge is delayed until the poपूर्णांक when we know we can
	 * commit all, so that we करोn't have to unकरो partial changes
	 */
	अगर (!to ||
	    !skb_can_coalesce(tgt, to, skb_frag_page(fragfrom),
			      skb_frag_off(fragfrom))) अणु
		merge = -1;
	पूर्ण अन्यथा अणु
		merge = to - 1;

		toकरो -= skb_frag_size(fragfrom);
		अगर (toकरो < 0) अणु
			अगर (skb_prepare_क्रम_shअगरt(skb) ||
			    skb_prepare_क्रम_shअगरt(tgt))
				वापस 0;

			/* All previous frag poपूर्णांकers might be stale! */
			fragfrom = &skb_shinfo(skb)->frags[from];
			fragto = &skb_shinfo(tgt)->frags[merge];

			skb_frag_size_add(fragto, shअगरtlen);
			skb_frag_size_sub(fragfrom, shअगरtlen);
			skb_frag_off_add(fragfrom, shअगरtlen);

			जाओ onlymerged;
		पूर्ण

		from++;
	पूर्ण

	/* Skip full, not-fitting skb to aव्योम expensive operations */
	अगर ((shअगरtlen == skb->len) &&
	    (skb_shinfo(skb)->nr_frags - from) > (MAX_SKB_FRAGS - to))
		वापस 0;

	अगर (skb_prepare_क्रम_shअगरt(skb) || skb_prepare_क्रम_shअगरt(tgt))
		वापस 0;

	जबतक ((toकरो > 0) && (from < skb_shinfo(skb)->nr_frags)) अणु
		अगर (to == MAX_SKB_FRAGS)
			वापस 0;

		fragfrom = &skb_shinfo(skb)->frags[from];
		fragto = &skb_shinfo(tgt)->frags[to];

		अगर (toकरो >= skb_frag_size(fragfrom)) अणु
			*fragto = *fragfrom;
			toकरो -= skb_frag_size(fragfrom);
			from++;
			to++;

		पूर्ण अन्यथा अणु
			__skb_frag_ref(fragfrom);
			skb_frag_page_copy(fragto, fragfrom);
			skb_frag_off_copy(fragto, fragfrom);
			skb_frag_size_set(fragto, toकरो);

			skb_frag_off_add(fragfrom, toकरो);
			skb_frag_size_sub(fragfrom, toकरो);
			toकरो = 0;

			to++;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ready to "commit" this state change to tgt */
	skb_shinfo(tgt)->nr_frags = to;

	अगर (merge >= 0) अणु
		fragfrom = &skb_shinfo(skb)->frags[0];
		fragto = &skb_shinfo(tgt)->frags[merge];

		skb_frag_size_add(fragto, skb_frag_size(fragfrom));
		__skb_frag_unref(fragfrom);
	पूर्ण

	/* Reposition in the original skb */
	to = 0;
	जबतक (from < skb_shinfo(skb)->nr_frags)
		skb_shinfo(skb)->frags[to++] = skb_shinfo(skb)->frags[from++];
	skb_shinfo(skb)->nr_frags = to;

	BUG_ON(toकरो > 0 && !skb_shinfo(skb)->nr_frags);

onlymerged:
	/* Most likely the tgt won't ever need its checksum anymore, skb on
	 * the other hand might need it अगर it needs to be resent
	 */
	tgt->ip_summed = CHECKSUM_PARTIAL;
	skb->ip_summed = CHECKSUM_PARTIAL;

	/* Yak, is it really working this way? Some helper please? */
	skb->len -= shअगरtlen;
	skb->data_len -= shअगरtlen;
	skb->truesize -= shअगरtlen;
	tgt->len += shअगरtlen;
	tgt->data_len += shअगरtlen;
	tgt->truesize += shअगरtlen;

	वापस shअगरtlen;
पूर्ण

/**
 * skb_prepare_seq_पढ़ो - Prepare a sequential पढ़ो of skb data
 * @skb: the buffer to पढ़ो
 * @from: lower offset of data to be पढ़ो
 * @to: upper offset of data to be पढ़ो
 * @st: state variable
 *
 * Initializes the specअगरied state variable. Must be called beक्रमe
 * invoking skb_seq_पढ़ो() क्रम the first समय.
 */
व्योम skb_prepare_seq_पढ़ो(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक from,
			  अचिन्हित पूर्णांक to, काष्ठा skb_seq_state *st)
अणु
	st->lower_offset = from;
	st->upper_offset = to;
	st->root_skb = st->cur_skb = skb;
	st->frag_idx = st->stepped_offset = 0;
	st->frag_data = शून्य;
	st->frag_off = 0;
पूर्ण
EXPORT_SYMBOL(skb_prepare_seq_पढ़ो);

/**
 * skb_seq_पढ़ो - Sequentially पढ़ो skb data
 * @consumed: number of bytes consumed by the caller so far
 * @data: destination poपूर्णांकer क्रम data to be वापसed
 * @st: state variable
 *
 * Reads a block of skb data at @consumed relative to the
 * lower offset specअगरied to skb_prepare_seq_पढ़ो(). Assigns
 * the head of the data block to @data and वापसs the length
 * of the block or 0 अगर the end of the skb data or the upper
 * offset has been reached.
 *
 * The caller is not required to consume all of the data
 * वापसed, i.e. @consumed is typically set to the number
 * of bytes alपढ़ोy consumed and the next call to
 * skb_seq_पढ़ो() will वापस the reमुख्यing part of the block.
 *
 * Note 1: The size of each block of data वापसed can be arbitrary,
 *       this limitation is the cost क्रम zerocopy sequential
 *       पढ़ोs of potentially non linear data.
 *
 * Note 2: Fragment lists within fragments are not implemented
 *       at the moment, state->root_skb could be replaced with
 *       a stack क्रम this purpose.
 */
अचिन्हित पूर्णांक skb_seq_पढ़ो(अचिन्हित पूर्णांक consumed, स्थिर u8 **data,
			  काष्ठा skb_seq_state *st)
अणु
	अचिन्हित पूर्णांक block_limit, असल_offset = consumed + st->lower_offset;
	skb_frag_t *frag;

	अगर (unlikely(असल_offset >= st->upper_offset)) अणु
		अगर (st->frag_data) अणु
			kunmap_atomic(st->frag_data);
			st->frag_data = शून्य;
		पूर्ण
		वापस 0;
	पूर्ण

next_skb:
	block_limit = skb_headlen(st->cur_skb) + st->stepped_offset;

	अगर (असल_offset < block_limit && !st->frag_data) अणु
		*data = st->cur_skb->data + (असल_offset - st->stepped_offset);
		वापस block_limit - असल_offset;
	पूर्ण

	अगर (st->frag_idx == 0 && !st->frag_data)
		st->stepped_offset += skb_headlen(st->cur_skb);

	जबतक (st->frag_idx < skb_shinfo(st->cur_skb)->nr_frags) अणु
		अचिन्हित पूर्णांक pg_idx, pg_off, pg_sz;

		frag = &skb_shinfo(st->cur_skb)->frags[st->frag_idx];

		pg_idx = 0;
		pg_off = skb_frag_off(frag);
		pg_sz = skb_frag_size(frag);

		अगर (skb_frag_must_loop(skb_frag_page(frag))) अणु
			pg_idx = (pg_off + st->frag_off) >> PAGE_SHIFT;
			pg_off = offset_in_page(pg_off + st->frag_off);
			pg_sz = min_t(अचिन्हित पूर्णांक, pg_sz - st->frag_off,
						    PAGE_SIZE - pg_off);
		पूर्ण

		block_limit = pg_sz + st->stepped_offset;
		अगर (असल_offset < block_limit) अणु
			अगर (!st->frag_data)
				st->frag_data = kmap_atomic(skb_frag_page(frag) + pg_idx);

			*data = (u8 *)st->frag_data + pg_off +
				(असल_offset - st->stepped_offset);

			वापस block_limit - असल_offset;
		पूर्ण

		अगर (st->frag_data) अणु
			kunmap_atomic(st->frag_data);
			st->frag_data = शून्य;
		पूर्ण

		st->stepped_offset += pg_sz;
		st->frag_off += pg_sz;
		अगर (st->frag_off == skb_frag_size(frag)) अणु
			st->frag_off = 0;
			st->frag_idx++;
		पूर्ण
	पूर्ण

	अगर (st->frag_data) अणु
		kunmap_atomic(st->frag_data);
		st->frag_data = शून्य;
	पूर्ण

	अगर (st->root_skb == st->cur_skb && skb_has_frag_list(st->root_skb)) अणु
		st->cur_skb = skb_shinfo(st->root_skb)->frag_list;
		st->frag_idx = 0;
		जाओ next_skb;
	पूर्ण अन्यथा अगर (st->cur_skb->next) अणु
		st->cur_skb = st->cur_skb->next;
		st->frag_idx = 0;
		जाओ next_skb;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_seq_पढ़ो);

/**
 * skb_पात_seq_पढ़ो - Abort a sequential पढ़ो of skb data
 * @st: state variable
 *
 * Must be called अगर skb_seq_पढ़ो() was not called until it
 * वापसed 0.
 */
व्योम skb_पात_seq_पढ़ो(काष्ठा skb_seq_state *st)
अणु
	अगर (st->frag_data)
		kunmap_atomic(st->frag_data);
पूर्ण
EXPORT_SYMBOL(skb_पात_seq_पढ़ो);

#घोषणा TS_SKB_CB(state)	((काष्ठा skb_seq_state *) &((state)->cb))

अटल अचिन्हित पूर्णांक skb_ts_get_next_block(अचिन्हित पूर्णांक offset, स्थिर u8 **text,
					  काष्ठा ts_config *conf,
					  काष्ठा ts_state *state)
अणु
	वापस skb_seq_पढ़ो(offset, text, TS_SKB_CB(state));
पूर्ण

अटल व्योम skb_ts_finish(काष्ठा ts_config *conf, काष्ठा ts_state *state)
अणु
	skb_पात_seq_पढ़ो(TS_SKB_CB(state));
पूर्ण

/**
 * skb_find_text - Find a text pattern in skb data
 * @skb: the buffer to look in
 * @from: search offset
 * @to: search limit
 * @config: textsearch configuration
 *
 * Finds a pattern in the skb data according to the specअगरied
 * textsearch configuration. Use textsearch_next() to retrieve
 * subsequent occurrences of the pattern. Returns the offset
 * to the first occurrence or अच_पूर्णांक_उच्च अगर no match was found.
 */
अचिन्हित पूर्णांक skb_find_text(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक from,
			   अचिन्हित पूर्णांक to, काष्ठा ts_config *config)
अणु
	काष्ठा ts_state state;
	अचिन्हित पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा skb_seq_state) > माप(state.cb));

	config->get_next_block = skb_ts_get_next_block;
	config->finish = skb_ts_finish;

	skb_prepare_seq_पढ़ो(skb, from, to, TS_SKB_CB(&state));

	ret = textsearch_find(config, &state);
	वापस (ret <= to - from ? ret : अच_पूर्णांक_उच्च);
पूर्ण
EXPORT_SYMBOL(skb_find_text);

पूर्णांक skb_append_pagefrags(काष्ठा sk_buff *skb, काष्ठा page *page,
			 पूर्णांक offset, माप_प्रकार size)
अणु
	पूर्णांक i = skb_shinfo(skb)->nr_frags;

	अगर (skb_can_coalesce(skb, i, page, offset)) अणु
		skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], size);
	पूर्ण अन्यथा अगर (i < MAX_SKB_FRAGS) अणु
		get_page(page);
		skb_fill_page_desc(skb, i, page, offset, size);
	पूर्ण अन्यथा अणु
		वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_append_pagefrags);

/**
 *	skb_pull_rcsum - pull skb and update receive checksum
 *	@skb: buffer to update
 *	@len: length of data pulled
 *
 *	This function perक्रमms an skb_pull on the packet and updates
 *	the CHECKSUM_COMPLETE checksum.  It should be used on
 *	receive path processing instead of skb_pull unless you know
 *	that the checksum dअगरference is zero (e.g., a valid IP header)
 *	or you are setting ip_summed to CHECKSUM_NONE.
 */
व्योम *skb_pull_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *data = skb->data;

	BUG_ON(len > skb->len);
	__skb_pull(skb, len);
	skb_postpull_rcsum(skb, data, len);
	वापस skb->data;
पूर्ण
EXPORT_SYMBOL_GPL(skb_pull_rcsum);

अटल अंतरभूत skb_frag_t skb_head_frag_to_page_desc(काष्ठा sk_buff *frag_skb)
अणु
	skb_frag_t head_frag;
	काष्ठा page *page;

	page = virt_to_head_page(frag_skb->head);
	__skb_frag_set_page(&head_frag, page);
	skb_frag_off_set(&head_frag, frag_skb->data -
			 (अचिन्हित अक्षर *)page_address(page));
	skb_frag_size_set(&head_frag, skb_headlen(frag_skb));
	वापस head_frag;
पूर्ण

काष्ठा sk_buff *skb_segment_list(काष्ठा sk_buff *skb,
				 netdev_features_t features,
				 अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sk_buff *list_skb = skb_shinfo(skb)->frag_list;
	अचिन्हित पूर्णांक tnl_hlen = skb_tnl_header_len(skb);
	अचिन्हित पूर्णांक delta_truesize = 0;
	अचिन्हित पूर्णांक delta_len = 0;
	काष्ठा sk_buff *tail = शून्य;
	काष्ठा sk_buff *nskb, *पंचांगp;
	पूर्णांक err;

	skb_push(skb, -skb_network_offset(skb) + offset);

	skb_shinfo(skb)->frag_list = शून्य;

	करो अणु
		nskb = list_skb;
		list_skb = list_skb->next;

		err = 0;
		अगर (skb_shared(nskb)) अणु
			पंचांगp = skb_clone(nskb, GFP_ATOMIC);
			अगर (पंचांगp) अणु
				consume_skb(nskb);
				nskb = पंचांगp;
				err = skb_unclone(nskb, GFP_ATOMIC);
			पूर्ण अन्यथा अणु
				err = -ENOMEM;
			पूर्ण
		पूर्ण

		अगर (!tail)
			skb->next = nskb;
		अन्यथा
			tail->next = nskb;

		अगर (unlikely(err)) अणु
			nskb->next = list_skb;
			जाओ err_linearize;
		पूर्ण

		tail = nskb;

		delta_len += nskb->len;
		delta_truesize += nskb->truesize;

		skb_push(nskb, -skb_network_offset(nskb) + offset);

		skb_release_head_state(nskb);
		 __copy_skb_header(nskb, skb);

		skb_headers_offset_update(nskb, skb_headroom(nskb) - skb_headroom(skb));
		skb_copy_from_linear_data_offset(skb, -tnl_hlen,
						 nskb->data - tnl_hlen,
						 offset + tnl_hlen);

		अगर (skb_needs_linearize(nskb, features) &&
		    __skb_linearize(nskb))
			जाओ err_linearize;

	पूर्ण जबतक (list_skb);

	skb->truesize = skb->truesize - delta_truesize;
	skb->data_len = skb->data_len - delta_len;
	skb->len = skb->len - delta_len;

	skb_gso_reset(skb);

	skb->prev = tail;

	अगर (skb_needs_linearize(skb, features) &&
	    __skb_linearize(skb))
		जाओ err_linearize;

	skb_get(skb);

	वापस skb;

err_linearize:
	kमुक्त_skb_list(skb->next);
	skb->next = शून्य;
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(skb_segment_list);

पूर्णांक skb_gro_receive_list(काष्ठा sk_buff *p, काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(p->len + skb->len >= 65536))
		वापस -E2BIG;

	अगर (NAPI_GRO_CB(p)->last == p)
		skb_shinfo(p)->frag_list = skb;
	अन्यथा
		NAPI_GRO_CB(p)->last->next = skb;

	skb_pull(skb, skb_gro_offset(skb));

	NAPI_GRO_CB(p)->last = skb;
	NAPI_GRO_CB(p)->count++;
	p->data_len += skb->len;
	p->truesize += skb->truesize;
	p->len += skb->len;

	NAPI_GRO_CB(skb)->same_flow = 1;

	वापस 0;
पूर्ण

/**
 *	skb_segment - Perक्रमm protocol segmentation on skb.
 *	@head_skb: buffer to segment
 *	@features: features क्रम the output path (see dev->features)
 *
 *	This function perक्रमms segmentation on the given skb.  It वापसs
 *	a poपूर्णांकer to the first in a list of new skbs क्रम the segments.
 *	In हाल of error it वापसs ERR_PTR(err).
 */
काष्ठा sk_buff *skb_segment(काष्ठा sk_buff *head_skb,
			    netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = शून्य;
	काष्ठा sk_buff *tail = शून्य;
	काष्ठा sk_buff *list_skb = skb_shinfo(head_skb)->frag_list;
	skb_frag_t *frag = skb_shinfo(head_skb)->frags;
	अचिन्हित पूर्णांक mss = skb_shinfo(head_skb)->gso_size;
	अचिन्हित पूर्णांक करोffset = head_skb->data - skb_mac_header(head_skb);
	काष्ठा sk_buff *frag_skb = head_skb;
	अचिन्हित पूर्णांक offset = करोffset;
	अचिन्हित पूर्णांक tnl_hlen = skb_tnl_header_len(head_skb);
	अचिन्हित पूर्णांक partial_segs = 0;
	अचिन्हित पूर्णांक headroom;
	अचिन्हित पूर्णांक len = head_skb->len;
	__be16 proto;
	bool csum, sg;
	पूर्णांक nfrags = skb_shinfo(head_skb)->nr_frags;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i = 0;
	पूर्णांक pos;

	अगर (list_skb && !list_skb->head_frag && skb_headlen(list_skb) &&
	    (skb_shinfo(head_skb)->gso_type & SKB_GSO_DODGY)) अणु
		/* gso_size is untrusted, and we have a frag_list with a linear
		 * non head_frag head.
		 *
		 * (we assume checking the first list_skb member suffices;
		 * i.e अगर either of the list_skb members have non head_frag
		 * head, then the first one has too).
		 *
		 * If head_skb's headlen करोes not fit requested gso_size, it
		 * means that the frag_list members करो NOT terminate on exact
		 * gso_size boundaries. Hence we cannot perक्रमm skb_frag_t page
		 * sharing. Thereक्रमe we must fallback to copying the frag_list
		 * skbs; we करो so by disabling SG.
		 */
		अगर (mss != GSO_BY_FRAGS && mss != skb_headlen(head_skb))
			features &= ~NETIF_F_SG;
	पूर्ण

	__skb_push(head_skb, करोffset);
	proto = skb_network_protocol(head_skb, शून्य);
	अगर (unlikely(!proto))
		वापस ERR_PTR(-EINVAL);

	sg = !!(features & NETIF_F_SG);
	csum = !!can_checksum_protocol(features, proto);

	अगर (sg && csum && (mss != GSO_BY_FRAGS))  अणु
		अगर (!(features & NETIF_F_GSO_PARTIAL)) अणु
			काष्ठा sk_buff *iter;
			अचिन्हित पूर्णांक frag_len;

			अगर (!list_skb ||
			    !net_gso_ok(features, skb_shinfo(head_skb)->gso_type))
				जाओ normal;

			/* If we get here then all the required
			 * GSO features except frag_list are supported.
			 * Try to split the SKB to multiple GSO SKBs
			 * with no frag_list.
			 * Currently we can करो that only when the buffers करोn't
			 * have a linear part and all the buffers except
			 * the last are of the same length.
			 */
			frag_len = list_skb->len;
			skb_walk_frags(head_skb, iter) अणु
				अगर (frag_len != iter->len && iter->next)
					जाओ normal;
				अगर (skb_headlen(iter) && !iter->head_frag)
					जाओ normal;

				len -= iter->len;
			पूर्ण

			अगर (len != frag_len)
				जाओ normal;
		पूर्ण

		/* GSO partial only requires that we trim off any excess that
		 * करोesn't fit पूर्णांकo an MSS sized block, so take care of that
		 * now.
		 */
		partial_segs = len / mss;
		अगर (partial_segs > 1)
			mss *= partial_segs;
		अन्यथा
			partial_segs = 0;
	पूर्ण

normal:
	headroom = skb_headroom(head_skb);
	pos = skb_headlen(head_skb);

	करो अणु
		काष्ठा sk_buff *nskb;
		skb_frag_t *nskb_frag;
		पूर्णांक hsize;
		पूर्णांक size;

		अगर (unlikely(mss == GSO_BY_FRAGS)) अणु
			len = list_skb->len;
		पूर्ण अन्यथा अणु
			len = head_skb->len - offset;
			अगर (len > mss)
				len = mss;
		पूर्ण

		hsize = skb_headlen(head_skb) - offset;

		अगर (hsize <= 0 && i >= nfrags && skb_headlen(list_skb) &&
		    (skb_headlen(list_skb) == len || sg)) अणु
			BUG_ON(skb_headlen(list_skb) > len);

			i = 0;
			nfrags = skb_shinfo(list_skb)->nr_frags;
			frag = skb_shinfo(list_skb)->frags;
			frag_skb = list_skb;
			pos += skb_headlen(list_skb);

			जबतक (pos < offset + len) अणु
				BUG_ON(i >= nfrags);

				size = skb_frag_size(frag);
				अगर (pos + size > offset + len)
					अवरोध;

				i++;
				pos += size;
				frag++;
			पूर्ण

			nskb = skb_clone(list_skb, GFP_ATOMIC);
			list_skb = list_skb->next;

			अगर (unlikely(!nskb))
				जाओ err;

			अगर (unlikely(pskb_trim(nskb, len))) अणु
				kमुक्त_skb(nskb);
				जाओ err;
			पूर्ण

			hsize = skb_end_offset(nskb);
			अगर (skb_cow_head(nskb, करोffset + headroom)) अणु
				kमुक्त_skb(nskb);
				जाओ err;
			पूर्ण

			nskb->truesize += skb_end_offset(nskb) - hsize;
			skb_release_head_state(nskb);
			__skb_push(nskb, करोffset);
		पूर्ण अन्यथा अणु
			अगर (hsize < 0)
				hsize = 0;
			अगर (hsize > len || !sg)
				hsize = len;

			nskb = __alloc_skb(hsize + करोffset + headroom,
					   GFP_ATOMIC, skb_alloc_rx_flag(head_skb),
					   NUMA_NO_NODE);

			अगर (unlikely(!nskb))
				जाओ err;

			skb_reserve(nskb, headroom);
			__skb_put(nskb, करोffset);
		पूर्ण

		अगर (segs)
			tail->next = nskb;
		अन्यथा
			segs = nskb;
		tail = nskb;

		__copy_skb_header(nskb, head_skb);

		skb_headers_offset_update(nskb, skb_headroom(nskb) - headroom);
		skb_reset_mac_len(nskb);

		skb_copy_from_linear_data_offset(head_skb, -tnl_hlen,
						 nskb->data - tnl_hlen,
						 करोffset + tnl_hlen);

		अगर (nskb->len == len + करोffset)
			जाओ perक्रमm_csum_check;

		अगर (!sg) अणु
			अगर (!csum) अणु
				अगर (!nskb->remcsum_offload)
					nskb->ip_summed = CHECKSUM_NONE;
				SKB_GSO_CB(nskb)->csum =
					skb_copy_and_csum_bits(head_skb, offset,
							       skb_put(nskb,
								       len),
							       len);
				SKB_GSO_CB(nskb)->csum_start =
					skb_headroom(nskb) + करोffset;
			पूर्ण अन्यथा अणु
				skb_copy_bits(head_skb, offset,
					      skb_put(nskb, len),
					      len);
			पूर्ण
			जारी;
		पूर्ण

		nskb_frag = skb_shinfo(nskb)->frags;

		skb_copy_from_linear_data_offset(head_skb, offset,
						 skb_put(nskb, hsize), hsize);

		skb_shinfo(nskb)->flags |= skb_shinfo(head_skb)->flags &
					   SKBFL_SHARED_FRAG;

		अगर (skb_orphan_frags(frag_skb, GFP_ATOMIC) ||
		    skb_zerocopy_clone(nskb, frag_skb, GFP_ATOMIC))
			जाओ err;

		जबतक (pos < offset + len) अणु
			अगर (i >= nfrags) अणु
				i = 0;
				nfrags = skb_shinfo(list_skb)->nr_frags;
				frag = skb_shinfo(list_skb)->frags;
				frag_skb = list_skb;
				अगर (!skb_headlen(list_skb)) अणु
					BUG_ON(!nfrags);
				पूर्ण अन्यथा अणु
					BUG_ON(!list_skb->head_frag);

					/* to make room क्रम head_frag. */
					i--;
					frag--;
				पूर्ण
				अगर (skb_orphan_frags(frag_skb, GFP_ATOMIC) ||
				    skb_zerocopy_clone(nskb, frag_skb,
						       GFP_ATOMIC))
					जाओ err;

				list_skb = list_skb->next;
			पूर्ण

			अगर (unlikely(skb_shinfo(nskb)->nr_frags >=
				     MAX_SKB_FRAGS)) अणु
				net_warn_ratelimited(
					"skb_segment: too many frags: %u %u\n",
					pos, mss);
				err = -EINVAL;
				जाओ err;
			पूर्ण

			*nskb_frag = (i < 0) ? skb_head_frag_to_page_desc(frag_skb) : *frag;
			__skb_frag_ref(nskb_frag);
			size = skb_frag_size(nskb_frag);

			अगर (pos < offset) अणु
				skb_frag_off_add(nskb_frag, offset - pos);
				skb_frag_size_sub(nskb_frag, offset - pos);
			पूर्ण

			skb_shinfo(nskb)->nr_frags++;

			अगर (pos + size <= offset + len) अणु
				i++;
				frag++;
				pos += size;
			पूर्ण अन्यथा अणु
				skb_frag_size_sub(nskb_frag, pos + size - (offset + len));
				जाओ skip_fraglist;
			पूर्ण

			nskb_frag++;
		पूर्ण

skip_fraglist:
		nskb->data_len = len - hsize;
		nskb->len += nskb->data_len;
		nskb->truesize += nskb->data_len;

perक्रमm_csum_check:
		अगर (!csum) अणु
			अगर (skb_has_shared_frag(nskb) &&
			    __skb_linearize(nskb))
				जाओ err;

			अगर (!nskb->remcsum_offload)
				nskb->ip_summed = CHECKSUM_NONE;
			SKB_GSO_CB(nskb)->csum =
				skb_checksum(nskb, करोffset,
					     nskb->len - करोffset, 0);
			SKB_GSO_CB(nskb)->csum_start =
				skb_headroom(nskb) + करोffset;
		पूर्ण
	पूर्ण जबतक ((offset += len) < head_skb->len);

	/* Some callers want to get the end of the list.
	 * Put it in segs->prev to aव्योम walking the list.
	 * (see validate_xmit_skb_list() क्रम example)
	 */
	segs->prev = tail;

	अगर (partial_segs) अणु
		काष्ठा sk_buff *iter;
		पूर्णांक type = skb_shinfo(head_skb)->gso_type;
		अचिन्हित लघु gso_size = skb_shinfo(head_skb)->gso_size;

		/* Update type to add partial and then हटाओ करोdgy अगर set */
		type |= (features & NETIF_F_GSO_PARTIAL) / NETIF_F_GSO_PARTIAL * SKB_GSO_PARTIAL;
		type &= ~SKB_GSO_DODGY;

		/* Update GSO info and prepare to start updating headers on
		 * our way back करोwn the stack of protocols.
		 */
		क्रम (iter = segs; iter; iter = iter->next) अणु
			skb_shinfo(iter)->gso_size = gso_size;
			skb_shinfo(iter)->gso_segs = partial_segs;
			skb_shinfo(iter)->gso_type = type;
			SKB_GSO_CB(iter)->data_offset = skb_headroom(iter) + करोffset;
		पूर्ण

		अगर (tail->len - करोffset <= gso_size)
			skb_shinfo(tail)->gso_size = 0;
		अन्यथा अगर (tail != segs)
			skb_shinfo(tail)->gso_segs = DIV_ROUND_UP(tail->len - करोffset, gso_size);
	पूर्ण

	/* Following permits correct backpressure, क्रम protocols
	 * using skb_set_owner_w().
	 * Idea is to tranfert ownership from head_skb to last segment.
	 */
	अगर (head_skb->deकाष्ठाor == sock_wमुक्त) अणु
		swap(tail->truesize, head_skb->truesize);
		swap(tail->deकाष्ठाor, head_skb->deकाष्ठाor);
		swap(tail->sk, head_skb->sk);
	पूर्ण
	वापस segs;

err:
	kमुक्त_skb_list(segs);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(skb_segment);

पूर्णांक skb_gro_receive(काष्ठा sk_buff *p, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *pinfo, *skbinfo = skb_shinfo(skb);
	अचिन्हित पूर्णांक offset = skb_gro_offset(skb);
	अचिन्हित पूर्णांक headlen = skb_headlen(skb);
	अचिन्हित पूर्णांक len = skb_gro_len(skb);
	अचिन्हित पूर्णांक delta_truesize;
	काष्ठा sk_buff *lp;

	अगर (unlikely(p->len + len >= 65536 || NAPI_GRO_CB(skb)->flush))
		वापस -E2BIG;

	lp = NAPI_GRO_CB(p)->last;
	pinfo = skb_shinfo(lp);

	अगर (headlen <= offset) अणु
		skb_frag_t *frag;
		skb_frag_t *frag2;
		पूर्णांक i = skbinfo->nr_frags;
		पूर्णांक nr_frags = pinfo->nr_frags + i;

		अगर (nr_frags > MAX_SKB_FRAGS)
			जाओ merge;

		offset -= headlen;
		pinfo->nr_frags = nr_frags;
		skbinfo->nr_frags = 0;

		frag = pinfo->frags + nr_frags;
		frag2 = skbinfo->frags + i;
		करो अणु
			*--frag = *--frag2;
		पूर्ण जबतक (--i);

		skb_frag_off_add(frag, offset);
		skb_frag_size_sub(frag, offset);

		/* all fragments truesize : हटाओ (head size + sk_buff) */
		delta_truesize = skb->truesize -
				 SKB_TRUESIZE(skb_end_offset(skb));

		skb->truesize -= skb->data_len;
		skb->len -= skb->data_len;
		skb->data_len = 0;

		NAPI_GRO_CB(skb)->मुक्त = NAPI_GRO_FREE;
		जाओ करोne;
	पूर्ण अन्यथा अगर (skb->head_frag) अणु
		पूर्णांक nr_frags = pinfo->nr_frags;
		skb_frag_t *frag = pinfo->frags + nr_frags;
		काष्ठा page *page = virt_to_head_page(skb->head);
		अचिन्हित पूर्णांक first_size = headlen - offset;
		अचिन्हित पूर्णांक first_offset;

		अगर (nr_frags + 1 + skbinfo->nr_frags > MAX_SKB_FRAGS)
			जाओ merge;

		first_offset = skb->data -
			       (अचिन्हित अक्षर *)page_address(page) +
			       offset;

		pinfo->nr_frags = nr_frags + 1 + skbinfo->nr_frags;

		__skb_frag_set_page(frag, page);
		skb_frag_off_set(frag, first_offset);
		skb_frag_size_set(frag, first_size);

		स_नकल(frag + 1, skbinfo->frags, माप(*frag) * skbinfo->nr_frags);
		/* We करोnt need to clear skbinfo->nr_frags here */

		delta_truesize = skb->truesize - SKB_DATA_ALIGN(माप(काष्ठा sk_buff));
		NAPI_GRO_CB(skb)->मुक्त = NAPI_GRO_FREE_STOLEN_HEAD;
		जाओ करोne;
	पूर्ण

merge:
	delta_truesize = skb->truesize;
	अगर (offset > headlen) अणु
		अचिन्हित पूर्णांक eat = offset - headlen;

		skb_frag_off_add(&skbinfo->frags[0], eat);
		skb_frag_size_sub(&skbinfo->frags[0], eat);
		skb->data_len -= eat;
		skb->len -= eat;
		offset = headlen;
	पूर्ण

	__skb_pull(skb, offset);

	अगर (NAPI_GRO_CB(p)->last == p)
		skb_shinfo(p)->frag_list = skb;
	अन्यथा
		NAPI_GRO_CB(p)->last->next = skb;
	NAPI_GRO_CB(p)->last = skb;
	__skb_header_release(skb);
	lp = p;

करोne:
	NAPI_GRO_CB(p)->count++;
	p->data_len += len;
	p->truesize += delta_truesize;
	p->len += len;
	अगर (lp != p) अणु
		lp->data_len += len;
		lp->truesize += delta_truesize;
		lp->len += len;
	पूर्ण
	NAPI_GRO_CB(skb)->same_flow = 1;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SKB_EXTENSIONS
#घोषणा SKB_EXT_ALIGN_VALUE	8
#घोषणा SKB_EXT_CHUNKSIZखातापूर्ण(x)	(ALIGN((माप(x)), SKB_EXT_ALIGN_VALUE) / SKB_EXT_ALIGN_VALUE)

अटल स्थिर u8 skb_ext_type_len[] = अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	[SKB_EXT_BRIDGE_NF] = SKB_EXT_CHUNKSIZखातापूर्ण(काष्ठा nf_bridge_info),
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFRM
	[SKB_EXT_SEC_PATH] = SKB_EXT_CHUNKSIZखातापूर्ण(काष्ठा sec_path),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	[TC_SKB_EXT] = SKB_EXT_CHUNKSIZखातापूर्ण(काष्ठा tc_skb_ext),
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPTCP)
	[SKB_EXT_MPTCP] = SKB_EXT_CHUNKSIZखातापूर्ण(काष्ठा mptcp_ext),
#पूर्ण_अगर
पूर्ण;

अटल __always_अंतरभूत अचिन्हित पूर्णांक skb_ext_total_length(व्योम)
अणु
	वापस SKB_EXT_CHUNKSIZखातापूर्ण(काष्ठा skb_ext) +
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		skb_ext_type_len[SKB_EXT_BRIDGE_NF] +
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFRM
		skb_ext_type_len[SKB_EXT_SEC_PATH] +
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
		skb_ext_type_len[TC_SKB_EXT] +
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPTCP)
		skb_ext_type_len[SKB_EXT_MPTCP] +
#पूर्ण_अगर
		0;
पूर्ण

अटल व्योम skb_extensions_init(व्योम)
अणु
	BUILD_BUG_ON(SKB_EXT_NUM >= 8);
	BUILD_BUG_ON(skb_ext_total_length() > 255);

	skbuff_ext_cache = kmem_cache_create("skbuff_ext_cache",
					     SKB_EXT_ALIGN_VALUE * skb_ext_total_length(),
					     0,
					     SLAB_HWCACHE_ALIGN|SLAB_PANIC,
					     शून्य);
पूर्ण
#अन्यथा
अटल व्योम skb_extensions_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init skb_init(व्योम)
अणु
	skbuff_head_cache = kmem_cache_create_usercopy("skbuff_head_cache",
					      माप(काष्ठा sk_buff),
					      0,
					      SLAB_HWCACHE_ALIGN|SLAB_PANIC,
					      दुरत्व(काष्ठा sk_buff, cb),
					      माप_field(काष्ठा sk_buff, cb),
					      शून्य);
	skbuff_fclone_cache = kmem_cache_create("skbuff_fclone_cache",
						माप(काष्ठा sk_buff_fclones),
						0,
						SLAB_HWCACHE_ALIGN|SLAB_PANIC,
						शून्य);
	skb_extensions_init();
पूर्ण

अटल पूर्णांक
__skb_to_sgvec(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg, पूर्णांक offset, पूर्णांक len,
	       अचिन्हित पूर्णांक recursion_level)
अणु
	पूर्णांक start = skb_headlen(skb);
	पूर्णांक i, copy = start - offset;
	काष्ठा sk_buff *frag_iter;
	पूर्णांक elt = 0;

	अगर (unlikely(recursion_level >= 24))
		वापस -EMSGSIZE;

	अगर (copy > 0) अणु
		अगर (copy > len)
			copy = len;
		sg_set_buf(sg, skb->data + offset, copy);
		elt++;
		अगर ((len -= copy) == 0)
			वापस elt;
		offset += copy;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(&skb_shinfo(skb)->frags[i]);
		अगर ((copy = end - offset) > 0) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			अगर (unlikely(elt && sg_is_last(&sg[elt - 1])))
				वापस -EMSGSIZE;

			अगर (copy > len)
				copy = len;
			sg_set_page(&sg[elt], skb_frag_page(frag), copy,
				    skb_frag_off(frag) + offset - start);
			elt++;
			अगर (!(len -= copy))
				वापस elt;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end, ret;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (unlikely(elt && sg_is_last(&sg[elt - 1])))
				वापस -EMSGSIZE;

			अगर (copy > len)
				copy = len;
			ret = __skb_to_sgvec(frag_iter, sg+elt, offset - start,
					      copy, recursion_level + 1);
			अगर (unlikely(ret < 0))
				वापस ret;
			elt += ret;
			अगर ((len -= copy) == 0)
				वापस elt;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण
	BUG_ON(len);
	वापस elt;
पूर्ण

/**
 *	skb_to_sgvec - Fill a scatter-gather list from a socket buffer
 *	@skb: Socket buffer containing the buffers to be mapped
 *	@sg: The scatter-gather list to map पूर्णांकo
 *	@offset: The offset पूर्णांकo the buffer's contents to start mapping
 *	@len: Length of buffer space to be mapped
 *
 *	Fill the specअगरied scatter-gather list with mappings/poपूर्णांकers पूर्णांकo a
 *	region of the buffer space attached to a socket buffer. Returns either
 *	the number of scatterlist items used, or -EMSGSIZE अगर the contents
 *	could not fit.
 */
पूर्णांक skb_to_sgvec(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg, पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक nsg = __skb_to_sgvec(skb, sg, offset, len, 0);

	अगर (nsg <= 0)
		वापस nsg;

	sg_mark_end(&sg[nsg - 1]);

	वापस nsg;
पूर्ण
EXPORT_SYMBOL_GPL(skb_to_sgvec);

/* As compared with skb_to_sgvec, skb_to_sgvec_nomark only map skb to given
 * sglist without mark the sg which contain last skb data as the end.
 * So the caller can mannipulate sg list as will when padding new data after
 * the first call without calling sg_unmark_end to expend sg list.
 *
 * Scenario to use skb_to_sgvec_nomark:
 * 1. sg_init_table
 * 2. skb_to_sgvec_nomark(payload1)
 * 3. skb_to_sgvec_nomark(payload2)
 *
 * This is equivalent to:
 * 1. sg_init_table
 * 2. skb_to_sgvec(payload1)
 * 3. sg_unmark_end
 * 4. skb_to_sgvec(payload2)
 *
 * When mapping mutilple payload conditionally, skb_to_sgvec_nomark
 * is more preferable.
 */
पूर्णांक skb_to_sgvec_nomark(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg,
			पूर्णांक offset, पूर्णांक len)
अणु
	वापस __skb_to_sgvec(skb, sg, offset, len, 0);
पूर्ण
EXPORT_SYMBOL_GPL(skb_to_sgvec_nomark);



/**
 *	skb_cow_data - Check that a socket buffer's data buffers are writable
 *	@skb: The socket buffer to check.
 *	@tailbits: Amount of trailing space to be added
 *	@trailer: Returned poपूर्णांकer to the skb where the @tailbits space begins
 *
 *	Make sure that the data buffers attached to a socket buffer are
 *	writable. If they are not, निजी copies are made of the data buffers
 *	and the socket buffer is set to use these instead.
 *
 *	If @tailbits is given, make sure that there is space to ग_लिखो @tailbits
 *	bytes of data beyond current end of socket buffer.  @trailer will be
 *	set to poपूर्णांक to the skb in which this space begins.
 *
 *	The number of scatterlist elements required to completely map the
 *	COW'd and extended socket buffer will be वापसed.
 */
पूर्णांक skb_cow_data(काष्ठा sk_buff *skb, पूर्णांक tailbits, काष्ठा sk_buff **trailer)
अणु
	पूर्णांक copyflag;
	पूर्णांक elt;
	काष्ठा sk_buff *skb1, **skb_p;

	/* If skb is cloned or its head is paged, पुनः_स्मृतिate
	 * head pulling out all the pages (pages are considered not writable
	 * at the moment even अगर they are anonymous).
	 */
	अगर ((skb_cloned(skb) || skb_shinfo(skb)->nr_frags) &&
	    !__pskb_pull_tail(skb, __skb_pagelen(skb)))
		वापस -ENOMEM;

	/* Easy हाल. Most of packets will go this way. */
	अगर (!skb_has_frag_list(skb)) अणु
		/* A little of trouble, not enough of space क्रम trailer.
		 * This should not happen, when stack is tuned to generate
		 * good frames. OK, on miss we पुनः_स्मृतिate and reserve even more
		 * space, 128 bytes is fair. */

		अगर (skb_tailroom(skb) < tailbits &&
		    pskb_expand_head(skb, 0, tailbits-skb_tailroom(skb)+128, GFP_ATOMIC))
			वापस -ENOMEM;

		/* Voila! */
		*trailer = skb;
		वापस 1;
	पूर्ण

	/* Misery. We are in troubles, going to mincer fragments... */

	elt = 1;
	skb_p = &skb_shinfo(skb)->frag_list;
	copyflag = 0;

	जबतक ((skb1 = *skb_p) != शून्य) अणु
		पूर्णांक ntail = 0;

		/* The fragment is partially pulled by someone,
		 * this can happen on input. Copy it and everything
		 * after it. */

		अगर (skb_shared(skb1))
			copyflag = 1;

		/* If the skb is the last, worry about trailer. */

		अगर (skb1->next == शून्य && tailbits) अणु
			अगर (skb_shinfo(skb1)->nr_frags ||
			    skb_has_frag_list(skb1) ||
			    skb_tailroom(skb1) < tailbits)
				ntail = tailbits + 128;
		पूर्ण

		अगर (copyflag ||
		    skb_cloned(skb1) ||
		    ntail ||
		    skb_shinfo(skb1)->nr_frags ||
		    skb_has_frag_list(skb1)) अणु
			काष्ठा sk_buff *skb2;

			/* Fuck, we are miserable poor guys... */
			अगर (ntail == 0)
				skb2 = skb_copy(skb1, GFP_ATOMIC);
			अन्यथा
				skb2 = skb_copy_expand(skb1,
						       skb_headroom(skb1),
						       ntail,
						       GFP_ATOMIC);
			अगर (unlikely(skb2 == शून्य))
				वापस -ENOMEM;

			अगर (skb1->sk)
				skb_set_owner_w(skb2, skb1->sk);

			/* Looking around. Are we still alive?
			 * OK, link new skb, drop old one */

			skb2->next = skb1->next;
			*skb_p = skb2;
			kमुक्त_skb(skb1);
			skb1 = skb2;
		पूर्ण
		elt++;
		*trailer = skb1;
		skb_p = &skb1->next;
	पूर्ण

	वापस elt;
पूर्ण
EXPORT_SYMBOL_GPL(skb_cow_data);

अटल व्योम sock_rmem_मुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;

	atomic_sub(skb->truesize, &sk->sk_rmem_alloc);
पूर्ण

अटल व्योम skb_set_err_queue(काष्ठा sk_buff *skb)
अणु
	/* pkt_type of skbs received on local sockets is never PACKET_OUTGOING.
	 * So, it is safe to (mis)use it to mark skbs on the error queue.
	 */
	skb->pkt_type = PACKET_OUTGOING;
	BUILD_BUG_ON(PACKET_OUTGOING == 0);
पूर्ण

/*
 * Note: We करोnt mem अक्षरge error packets (no sk_क्रमward_alloc changes)
 */
पूर्णांक sock_queue_err_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) + skb->truesize >=
	    (अचिन्हित पूर्णांक)READ_ONCE(sk->sk_rcvbuf))
		वापस -ENOMEM;

	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_rmem_मुक्त;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	skb_set_err_queue(skb);

	/* beक्रमe निकासing rcu section, make sure dst is refcounted */
	skb_dst_क्रमce(skb);

	skb_queue_tail(&sk->sk_error_queue, skb);
	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_error_report(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sock_queue_err_skb);

अटल bool is_icmp_err_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb && (SKB_EXT_ERR(skb)->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
		       SKB_EXT_ERR(skb)->ee.ee_origin == SO_EE_ORIGIN_ICMP6);
पूर्ण

काष्ठा sk_buff *sock_dequeue_err_skb(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff_head *q = &sk->sk_error_queue;
	काष्ठा sk_buff *skb, *skb_next = शून्य;
	bool icmp_next = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->lock, flags);
	skb = __skb_dequeue(q);
	अगर (skb && (skb_next = skb_peek(q))) अणु
		icmp_next = is_icmp_err_skb(skb_next);
		अगर (icmp_next)
			sk->sk_err = SKB_EXT_ERR(skb_next)->ee.ee_त्रुटि_सं;
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);

	अगर (is_icmp_err_skb(skb) && !icmp_next)
		sk->sk_err = 0;

	अगर (skb_next)
		sk->sk_error_report(sk);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(sock_dequeue_err_skb);

/**
 * skb_clone_sk - create clone of skb, and take reference to socket
 * @skb: the skb to clone
 *
 * This function creates a clone of a buffer that holds a reference on
 * sk_refcnt.  Buffers created via this function are meant to be
 * वापसed using sock_queue_err_skb, or मुक्त via kमुक्त_skb.
 *
 * When passing buffers allocated with this function to sock_queue_err_skb
 * it is necessary to wrap the call with sock_hold/sock_put in order to
 * prevent the socket from being released prior to being enqueued on
 * the sk_error_queue.
 */
काष्ठा sk_buff *skb_clone_sk(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा sk_buff *clone;

	अगर (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		वापस शून्य;

	clone = skb_clone(skb, GFP_ATOMIC);
	अगर (!clone) अणु
		sock_put(sk);
		वापस शून्य;
	पूर्ण

	clone->sk = sk;
	clone->deकाष्ठाor = sock_eमुक्त;

	वापस clone;
पूर्ण
EXPORT_SYMBOL(skb_clone_sk);

अटल व्योम __skb_complete_tx_बारtamp(काष्ठा sk_buff *skb,
					काष्ठा sock *sk,
					पूर्णांक tstype,
					bool opt_stats)
अणु
	काष्ठा sock_exterr_skb *serr;
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा sock_exterr_skb) > माप(skb->cb));

	serr = SKB_EXT_ERR(skb);
	स_रखो(serr, 0, माप(*serr));
	serr->ee.ee_त्रुटि_सं = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TIMESTAMPING;
	serr->ee.ee_info = tstype;
	serr->opt_stats = opt_stats;
	serr->header.h4.iअगर = skb->dev ? skb->dev->अगरindex : 0;
	अगर (sk->sk_tsflags & SOF_TIMESTAMPING_OPT_ID) अणु
		serr->ee.ee_data = skb_shinfo(skb)->tskey;
		अगर (sk->sk_protocol == IPPROTO_TCP &&
		    sk->sk_type == SOCK_STREAM)
			serr->ee.ee_data -= sk->sk_tskey;
	पूर्ण

	err = sock_queue_err_skb(sk, skb);

	अगर (err)
		kमुक्त_skb(skb);
पूर्ण

अटल bool skb_may_tx_बारtamp(काष्ठा sock *sk, bool tsonly)
अणु
	bool ret;

	अगर (likely(sysctl_tstamp_allow_data || tsonly))
		वापस true;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	ret = sk->sk_socket && sk->sk_socket->file &&
	      file_ns_capable(sk->sk_socket->file, &init_user_ns, CAP_NET_RAW);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस ret;
पूर्ण

व्योम skb_complete_tx_बारtamp(काष्ठा sk_buff *skb,
			       काष्ठा skb_shared_hwtstamps *hwtstamps)
अणु
	काष्ठा sock *sk = skb->sk;

	अगर (!skb_may_tx_बारtamp(sk, false))
		जाओ err;

	/* Take a reference to prevent skb_orphan() from मुक्तing the socket,
	 * but only अगर the socket refcount is not zero.
	 */
	अगर (likely(refcount_inc_not_zero(&sk->sk_refcnt))) अणु
		*skb_hwtstamps(skb) = *hwtstamps;
		__skb_complete_tx_बारtamp(skb, sk, SCM_TSTAMP_SND, false);
		sock_put(sk);
		वापस;
	पूर्ण

err:
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(skb_complete_tx_बारtamp);

व्योम __skb_tstamp_tx(काष्ठा sk_buff *orig_skb,
		     स्थिर काष्ठा sk_buff *ack_skb,
		     काष्ठा skb_shared_hwtstamps *hwtstamps,
		     काष्ठा sock *sk, पूर्णांक tstype)
अणु
	काष्ठा sk_buff *skb;
	bool tsonly, opt_stats = false;

	अगर (!sk)
		वापस;

	अगर (!hwtstamps && !(sk->sk_tsflags & SOF_TIMESTAMPING_OPT_TX_SWHW) &&
	    skb_shinfo(orig_skb)->tx_flags & SKBTX_IN_PROGRESS)
		वापस;

	tsonly = sk->sk_tsflags & SOF_TIMESTAMPING_OPT_TSONLY;
	अगर (!skb_may_tx_बारtamp(sk, tsonly))
		वापस;

	अगर (tsonly) अणु
#अगर_घोषित CONFIG_INET
		अगर ((sk->sk_tsflags & SOF_TIMESTAMPING_OPT_STATS) &&
		    sk->sk_protocol == IPPROTO_TCP &&
		    sk->sk_type == SOCK_STREAM) अणु
			skb = tcp_get_बारtamping_opt_stats(sk, orig_skb,
							     ack_skb);
			opt_stats = true;
		पूर्ण अन्यथा
#पूर्ण_अगर
			skb = alloc_skb(0, GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		skb = skb_clone(orig_skb, GFP_ATOMIC);
	पूर्ण
	अगर (!skb)
		वापस;

	अगर (tsonly) अणु
		skb_shinfo(skb)->tx_flags |= skb_shinfo(orig_skb)->tx_flags &
					     SKBTX_ANY_TSTAMP;
		skb_shinfo(skb)->tskey = skb_shinfo(orig_skb)->tskey;
	पूर्ण

	अगर (hwtstamps)
		*skb_hwtstamps(skb) = *hwtstamps;
	अन्यथा
		skb->tstamp = kसमय_get_real();

	__skb_complete_tx_बारtamp(skb, sk, tstype, opt_stats);
पूर्ण
EXPORT_SYMBOL_GPL(__skb_tstamp_tx);

व्योम skb_tstamp_tx(काष्ठा sk_buff *orig_skb,
		   काष्ठा skb_shared_hwtstamps *hwtstamps)
अणु
	वापस __skb_tstamp_tx(orig_skb, शून्य, hwtstamps, orig_skb->sk,
			       SCM_TSTAMP_SND);
पूर्ण
EXPORT_SYMBOL_GPL(skb_tstamp_tx);

व्योम skb_complete_wअगरi_ack(काष्ठा sk_buff *skb, bool acked)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा sock_exterr_skb *serr;
	पूर्णांक err = 1;

	skb->wअगरi_acked_valid = 1;
	skb->wअगरi_acked = acked;

	serr = SKB_EXT_ERR(skb);
	स_रखो(serr, 0, माप(*serr));
	serr->ee.ee_त्रुटि_सं = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXSTATUS;

	/* Take a reference to prevent skb_orphan() from मुक्तing the socket,
	 * but only अगर the socket refcount is not zero.
	 */
	अगर (likely(refcount_inc_not_zero(&sk->sk_refcnt))) अणु
		err = sock_queue_err_skb(sk, skb);
		sock_put(sk);
	पूर्ण
	अगर (err)
		kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(skb_complete_wअगरi_ack);

/**
 * skb_partial_csum_set - set up and verअगरy partial csum values क्रम packet
 * @skb: the skb to set
 * @start: the number of bytes after skb->data to start checksumming.
 * @off: the offset from start to place the checksum.
 *
 * For untrusted partially-checksummed packets, we need to make sure the values
 * क्रम skb->csum_start and skb->csum_offset are valid so we करोn't oops.
 *
 * This function checks and sets those values and skb->ip_summed: अगर this
 * वापसs false you should drop the packet.
 */
bool skb_partial_csum_set(काष्ठा sk_buff *skb, u16 start, u16 off)
अणु
	u32 csum_end = (u32)start + (u32)off + माप(__sum16);
	u32 csum_start = skb_headroom(skb) + (u32)start;

	अगर (unlikely(csum_start > U16_MAX || csum_end > skb_headlen(skb))) अणु
		net_warn_ratelimited("bad partial csum: csum=%u/%u headroom=%u headlen=%u\n",
				     start, off, skb_headroom(skb), skb_headlen(skb));
		वापस false;
	पूर्ण
	skb->ip_summed = CHECKSUM_PARTIAL;
	skb->csum_start = csum_start;
	skb->csum_offset = off;
	skb_set_transport_header(skb, start);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(skb_partial_csum_set);

अटल पूर्णांक skb_maybe_pull_tail(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len,
			       अचिन्हित पूर्णांक max)
अणु
	अगर (skb_headlen(skb) >= len)
		वापस 0;

	/* If we need to pullup then pullup to the max, so we
	 * won't need to करो it again.
	 */
	अगर (max > skb->len)
		max = skb->len;

	अगर (__pskb_pull_tail(skb, max - skb_headlen(skb)) == शून्य)
		वापस -ENOMEM;

	अगर (skb_headlen(skb) < len)
		वापस -EPROTO;

	वापस 0;
पूर्ण

#घोषणा MAX_TCP_HDR_LEN (15 * 4)

अटल __sum16 *skb_checksum_setup_ip(काष्ठा sk_buff *skb,
				      typeof(IPPROTO_IP) proto,
				      अचिन्हित पूर्णांक off)
अणु
	पूर्णांक err;

	चयन (proto) अणु
	हाल IPPROTO_TCP:
		err = skb_maybe_pull_tail(skb, off + माप(काष्ठा tcphdr),
					  off + MAX_TCP_HDR_LEN);
		अगर (!err && !skb_partial_csum_set(skb, off,
						  दुरत्व(काष्ठा tcphdr,
							   check)))
			err = -EPROTO;
		वापस err ? ERR_PTR(err) : &tcp_hdr(skb)->check;

	हाल IPPROTO_UDP:
		err = skb_maybe_pull_tail(skb, off + माप(काष्ठा udphdr),
					  off + माप(काष्ठा udphdr));
		अगर (!err && !skb_partial_csum_set(skb, off,
						  दुरत्व(काष्ठा udphdr,
							   check)))
			err = -EPROTO;
		वापस err ? ERR_PTR(err) : &udp_hdr(skb)->check;
	पूर्ण

	वापस ERR_PTR(-EPROTO);
पूर्ण

/* This value should be large enough to cover a tagged ethernet header plus
 * maximally sized IP and TCP or UDP headers.
 */
#घोषणा MAX_IP_HDR_LEN 128

अटल पूर्णांक skb_checksum_setup_ipv4(काष्ठा sk_buff *skb, bool recalculate)
अणु
	अचिन्हित पूर्णांक off;
	bool fragment;
	__sum16 *csum;
	पूर्णांक err;

	fragment = false;

	err = skb_maybe_pull_tail(skb,
				  माप(काष्ठा iphdr),
				  MAX_IP_HDR_LEN);
	अगर (err < 0)
		जाओ out;

	अगर (ip_is_fragment(ip_hdr(skb)))
		fragment = true;

	off = ip_hdrlen(skb);

	err = -EPROTO;

	अगर (fragment)
		जाओ out;

	csum = skb_checksum_setup_ip(skb, ip_hdr(skb)->protocol, off);
	अगर (IS_ERR(csum))
		वापस PTR_ERR(csum);

	अगर (recalculate)
		*csum = ~csum_tcpudp_magic(ip_hdr(skb)->saddr,
					   ip_hdr(skb)->daddr,
					   skb->len - off,
					   ip_hdr(skb)->protocol, 0);
	err = 0;

out:
	वापस err;
पूर्ण

/* This value should be large enough to cover a tagged ethernet header plus
 * an IPv6 header, all options, and a maximal TCP or UDP header.
 */
#घोषणा MAX_IPV6_HDR_LEN 256

#घोषणा OPT_HDR(type, skb, off) \
	(type *)(skb_network_header(skb) + (off))

अटल पूर्णांक skb_checksum_setup_ipv6(काष्ठा sk_buff *skb, bool recalculate)
अणु
	पूर्णांक err;
	u8 nexthdr;
	अचिन्हित पूर्णांक off;
	अचिन्हित पूर्णांक len;
	bool fragment;
	bool करोne;
	__sum16 *csum;

	fragment = false;
	करोne = false;

	off = माप(काष्ठा ipv6hdr);

	err = skb_maybe_pull_tail(skb, off, MAX_IPV6_HDR_LEN);
	अगर (err < 0)
		जाओ out;

	nexthdr = ipv6_hdr(skb)->nexthdr;

	len = माप(काष्ठा ipv6hdr) + ntohs(ipv6_hdr(skb)->payload_len);
	जबतक (off <= len && !करोne) अणु
		चयन (nexthdr) अणु
		हाल IPPROTO_DSTOPTS:
		हाल IPPROTO_HOPOPTS:
		हाल IPPROTO_ROUTING: अणु
			काष्ठा ipv6_opt_hdr *hp;

			err = skb_maybe_pull_tail(skb,
						  off +
						  माप(काष्ठा ipv6_opt_hdr),
						  MAX_IPV6_HDR_LEN);
			अगर (err < 0)
				जाओ out;

			hp = OPT_HDR(काष्ठा ipv6_opt_hdr, skb, off);
			nexthdr = hp->nexthdr;
			off += ipv6_optlen(hp);
			अवरोध;
		पूर्ण
		हाल IPPROTO_AH: अणु
			काष्ठा ip_auth_hdr *hp;

			err = skb_maybe_pull_tail(skb,
						  off +
						  माप(काष्ठा ip_auth_hdr),
						  MAX_IPV6_HDR_LEN);
			अगर (err < 0)
				जाओ out;

			hp = OPT_HDR(काष्ठा ip_auth_hdr, skb, off);
			nexthdr = hp->nexthdr;
			off += ipv6_authlen(hp);
			अवरोध;
		पूर्ण
		हाल IPPROTO_FRAGMENT: अणु
			काष्ठा frag_hdr *hp;

			err = skb_maybe_pull_tail(skb,
						  off +
						  माप(काष्ठा frag_hdr),
						  MAX_IPV6_HDR_LEN);
			अगर (err < 0)
				जाओ out;

			hp = OPT_HDR(काष्ठा frag_hdr, skb, off);

			अगर (hp->frag_off & htons(IP6_OFFSET | IP6_MF))
				fragment = true;

			nexthdr = hp->nexthdr;
			off += माप(काष्ठा frag_hdr);
			अवरोध;
		पूर्ण
		शेष:
			करोne = true;
			अवरोध;
		पूर्ण
	पूर्ण

	err = -EPROTO;

	अगर (!करोne || fragment)
		जाओ out;

	csum = skb_checksum_setup_ip(skb, nexthdr, off);
	अगर (IS_ERR(csum))
		वापस PTR_ERR(csum);

	अगर (recalculate)
		*csum = ~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
					 &ipv6_hdr(skb)->daddr,
					 skb->len - off, nexthdr, 0);
	err = 0;

out:
	वापस err;
पूर्ण

/**
 * skb_checksum_setup - set up partial checksum offset
 * @skb: the skb to set up
 * @recalculate: अगर true the pseuकरो-header checksum will be recalculated
 */
पूर्णांक skb_checksum_setup(काष्ठा sk_buff *skb, bool recalculate)
अणु
	पूर्णांक err;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		err = skb_checksum_setup_ipv4(skb, recalculate);
		अवरोध;

	हाल htons(ETH_P_IPV6):
		err = skb_checksum_setup_ipv6(skb, recalculate);
		अवरोध;

	शेष:
		err = -EPROTO;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(skb_checksum_setup);

/**
 * skb_checksum_maybe_trim - maybe trims the given skb
 * @skb: the skb to check
 * @transport_len: the data length beyond the network header
 *
 * Checks whether the given skb has data beyond the given transport length.
 * If so, वापसs a cloned skb trimmed to this transport length.
 * Otherwise वापसs the provided skb. Returns शून्य in error हालs
 * (e.g. transport_len exceeds skb length or out-of-memory).
 *
 * Caller needs to set the skb transport header and मुक्त any वापसed skb अगर it
 * dअगरfers from the provided skb.
 */
अटल काष्ठा sk_buff *skb_checksum_maybe_trim(काष्ठा sk_buff *skb,
					       अचिन्हित पूर्णांक transport_len)
अणु
	काष्ठा sk_buff *skb_chk;
	अचिन्हित पूर्णांक len = skb_transport_offset(skb) + transport_len;
	पूर्णांक ret;

	अगर (skb->len < len)
		वापस शून्य;
	अन्यथा अगर (skb->len == len)
		वापस skb;

	skb_chk = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb_chk)
		वापस शून्य;

	ret = pskb_trim_rcsum(skb_chk, len);
	अगर (ret) अणु
		kमुक्त_skb(skb_chk);
		वापस शून्य;
	पूर्ण

	वापस skb_chk;
पूर्ण

/**
 * skb_checksum_trimmed - validate checksum of an skb
 * @skb: the skb to check
 * @transport_len: the data length beyond the network header
 * @skb_chkf: checksum function to use
 *
 * Applies the given checksum function skb_chkf to the provided skb.
 * Returns a checked and maybe trimmed skb. Returns शून्य on error.
 *
 * If the skb has data beyond the given transport length, then a
 * trimmed & cloned skb is checked and वापसed.
 *
 * Caller needs to set the skb transport header and मुक्त any वापसed skb अगर it
 * dअगरfers from the provided skb.
 */
काष्ठा sk_buff *skb_checksum_trimmed(काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक transport_len,
				     __sum16(*skb_chkf)(काष्ठा sk_buff *skb))
अणु
	काष्ठा sk_buff *skb_chk;
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb);
	__sum16 ret;

	skb_chk = skb_checksum_maybe_trim(skb, transport_len);
	अगर (!skb_chk)
		जाओ err;

	अगर (!pskb_may_pull(skb_chk, offset))
		जाओ err;

	skb_pull_rcsum(skb_chk, offset);
	ret = skb_chkf(skb_chk);
	skb_push_rcsum(skb_chk, offset);

	अगर (ret)
		जाओ err;

	वापस skb_chk;

err:
	अगर (skb_chk && skb_chk != skb)
		kमुक्त_skb(skb_chk);

	वापस शून्य;

पूर्ण
EXPORT_SYMBOL(skb_checksum_trimmed);

व्योम __skb_warn_lro_क्रमwarding(स्थिर काष्ठा sk_buff *skb)
अणु
	net_warn_ratelimited("%s: received packets cannot be forwarded while LRO is enabled\n",
			     skb->dev->name);
पूर्ण
EXPORT_SYMBOL(__skb_warn_lro_क्रमwarding);

व्योम kमुक्त_skb_partial(काष्ठा sk_buff *skb, bool head_stolen)
अणु
	अगर (head_stolen) अणु
		skb_release_head_state(skb);
		kmem_cache_मुक्त(skbuff_head_cache, skb);
	पूर्ण अन्यथा अणु
		__kमुक्त_skb(skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kमुक्त_skb_partial);

/**
 * skb_try_coalesce - try to merge skb to prior one
 * @to: prior buffer
 * @from: buffer to add
 * @fragstolen: poपूर्णांकer to boolean
 * @delta_truesize: how much more was allocated than was requested
 */
bool skb_try_coalesce(काष्ठा sk_buff *to, काष्ठा sk_buff *from,
		      bool *fragstolen, पूर्णांक *delta_truesize)
अणु
	काष्ठा skb_shared_info *to_shinfo, *from_shinfo;
	पूर्णांक i, delta, len = from->len;

	*fragstolen = false;

	अगर (skb_cloned(to))
		वापस false;

	अगर (len <= skb_tailroom(to)) अणु
		अगर (len)
			BUG_ON(skb_copy_bits(from, 0, skb_put(to, len), len));
		*delta_truesize = 0;
		वापस true;
	पूर्ण

	to_shinfo = skb_shinfo(to);
	from_shinfo = skb_shinfo(from);
	अगर (to_shinfo->frag_list || from_shinfo->frag_list)
		वापस false;
	अगर (skb_zcopy(to) || skb_zcopy(from))
		वापस false;

	अगर (skb_headlen(from) != 0) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक offset;

		अगर (to_shinfo->nr_frags +
		    from_shinfo->nr_frags >= MAX_SKB_FRAGS)
			वापस false;

		अगर (skb_head_is_locked(from))
			वापस false;

		delta = from->truesize - SKB_DATA_ALIGN(माप(काष्ठा sk_buff));

		page = virt_to_head_page(from->head);
		offset = from->data - (अचिन्हित अक्षर *)page_address(page);

		skb_fill_page_desc(to, to_shinfo->nr_frags,
				   page, offset, skb_headlen(from));
		*fragstolen = true;
	पूर्ण अन्यथा अणु
		अगर (to_shinfo->nr_frags +
		    from_shinfo->nr_frags > MAX_SKB_FRAGS)
			वापस false;

		delta = from->truesize - SKB_TRUESIZE(skb_end_offset(from));
	पूर्ण

	WARN_ON_ONCE(delta < len);

	स_नकल(to_shinfo->frags + to_shinfo->nr_frags,
	       from_shinfo->frags,
	       from_shinfo->nr_frags * माप(skb_frag_t));
	to_shinfo->nr_frags += from_shinfo->nr_frags;

	अगर (!skb_cloned(from))
		from_shinfo->nr_frags = 0;

	/* अगर the skb is not cloned this करोes nothing
	 * since we set nr_frags to 0.
	 */
	क्रम (i = 0; i < from_shinfo->nr_frags; i++)
		__skb_frag_ref(&from_shinfo->frags[i]);

	to->truesize += delta;
	to->len += len;
	to->data_len += len;

	*delta_truesize = delta;
	वापस true;
पूर्ण
EXPORT_SYMBOL(skb_try_coalesce);

/**
 * skb_scrub_packet - scrub an skb
 *
 * @skb: buffer to clean
 * @xnet: packet is crossing netns
 *
 * skb_scrub_packet can be used after encapsulating or decapsulting a packet
 * पूर्णांकo/from a tunnel. Some inक्रमmation have to be cleared during these
 * operations.
 * skb_scrub_packet can also be used to clean a skb beक्रमe injecting it in
 * another namespace (@xnet == true). We have to clear all inक्रमmation in the
 * skb that could impact namespace isolation.
 */
व्योम skb_scrub_packet(काष्ठा sk_buff *skb, bool xnet)
अणु
	skb->pkt_type = PACKET_HOST;
	skb->skb_iअगर = 0;
	skb->ignore_df = 0;
	skb_dst_drop(skb);
	skb_ext_reset(skb);
	nf_reset_ct(skb);
	nf_reset_trace(skb);

#अगर_घोषित CONFIG_NET_SWITCHDEV
	skb->offload_fwd_mark = 0;
	skb->offload_l3_fwd_mark = 0;
#पूर्ण_अगर

	अगर (!xnet)
		वापस;

	ipvs_reset(skb);
	skb->mark = 0;
	skb->tstamp = 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_scrub_packet);

/**
 * skb_gso_transport_seglen - Return length of inभागidual segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_transport_seglen is used to determine the real size of the
 * inभागidual segments, including Layer4 headers (TCP/UDP).
 *
 * The MAC/L2 or network (IP, IPv6) headers are not accounted क्रम.
 */
अटल अचिन्हित पूर्णांक skb_gso_transport_seglen(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	अचिन्हित पूर्णांक thlen = 0;

	अगर (skb->encapsulation) अणु
		thlen = skb_inner_transport_header(skb) -
			skb_transport_header(skb);

		अगर (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
			thlen += inner_tcp_hdrlen(skb);
	पूर्ण अन्यथा अगर (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))) अणु
		thlen = tcp_hdrlen(skb);
	पूर्ण अन्यथा अगर (unlikely(skb_is_gso_sctp(skb))) अणु
		thlen = माप(काष्ठा sctphdr);
	पूर्ण अन्यथा अगर (shinfo->gso_type & SKB_GSO_UDP_L4) अणु
		thlen = माप(काष्ठा udphdr);
	पूर्ण
	/* UFO sets gso_size to the size of the fragmentation
	 * payload, i.e. the size of the L4 (UDP) header is alपढ़ोy
	 * accounted क्रम.
	 */
	वापस thlen + shinfo->gso_size;
पूर्ण

/**
 * skb_gso_network_seglen - Return length of inभागidual segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_network_seglen is used to determine the real size of the
 * inभागidual segments, including Layer3 (IP, IPv6) and L4 headers (TCP/UDP).
 *
 * The MAC/L2 header is not accounted क्रम.
 */
अटल अचिन्हित पूर्णांक skb_gso_network_seglen(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hdr_len = skb_transport_header(skb) -
			       skb_network_header(skb);

	वापस hdr_len + skb_gso_transport_seglen(skb);
पूर्ण

/**
 * skb_gso_mac_seglen - Return length of inभागidual segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_mac_seglen is used to determine the real size of the
 * inभागidual segments, including MAC/L2, Layer3 (IP, IPv6) and L4
 * headers (TCP/UDP).
 */
अटल अचिन्हित पूर्णांक skb_gso_mac_seglen(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hdr_len = skb_transport_header(skb) - skb_mac_header(skb);

	वापस hdr_len + skb_gso_transport_seglen(skb);
पूर्ण

/**
 * skb_gso_size_check - check the skb size, considering GSO_BY_FRAGS
 *
 * There are a couple of instances where we have a GSO skb, and we
 * want to determine what size it would be after it is segmented.
 *
 * We might want to check:
 * -    L3+L4+payload size (e.g. IP क्रमwarding)
 * - L2+L3+L4+payload size (e.g. sanity check beक्रमe passing to driver)
 *
 * This is a helper to करो that correctly considering GSO_BY_FRAGS.
 *
 * @skb: GSO skb
 *
 * @seg_len: The segmented length (from skb_gso_*_seglen). In the
 *           GSO_BY_FRAGS हाल this will be [header sizes + GSO_BY_FRAGS].
 *
 * @max_len: The maximum permissible length.
 *
 * Returns true अगर the segmented length <= max length.
 */
अटल अंतरभूत bool skb_gso_size_check(स्थिर काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक seg_len,
				      अचिन्हित पूर्णांक max_len) अणु
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	स्थिर काष्ठा sk_buff *iter;

	अगर (shinfo->gso_size != GSO_BY_FRAGS)
		वापस seg_len <= max_len;

	/* Unकरो this so we can re-use header sizes */
	seg_len -= GSO_BY_FRAGS;

	skb_walk_frags(skb, iter) अणु
		अगर (seg_len + skb_headlen(iter) > max_len)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * skb_gso_validate_network_len - Will a split GSO skb fit पूर्णांकo a given MTU?
 *
 * @skb: GSO skb
 * @mtu: MTU to validate against
 *
 * skb_gso_validate_network_len validates अगर a given skb will fit a
 * wanted MTU once split. It considers L3 headers, L4 headers, and the
 * payload.
 */
bool skb_gso_validate_network_len(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	वापस skb_gso_size_check(skb, skb_gso_network_seglen(skb), mtu);
पूर्ण
EXPORT_SYMBOL_GPL(skb_gso_validate_network_len);

/**
 * skb_gso_validate_mac_len - Will a split GSO skb fit in a given length?
 *
 * @skb: GSO skb
 * @len: length to validate against
 *
 * skb_gso_validate_mac_len validates अगर a given skb will fit a wanted
 * length once split, including L2, L3 and L4 headers and the payload.
 */
bool skb_gso_validate_mac_len(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस skb_gso_size_check(skb, skb_gso_mac_seglen(skb), len);
पूर्ण
EXPORT_SYMBOL_GPL(skb_gso_validate_mac_len);

अटल काष्ठा sk_buff *skb_reorder_vlan_header(काष्ठा sk_buff *skb)
अणु
	पूर्णांक mac_len, meta_len;
	व्योम *meta;

	अगर (skb_cow(skb, skb_headroom(skb)) < 0) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	mac_len = skb->data - skb_mac_header(skb);
	अगर (likely(mac_len > VLAN_HLEN + ETH_TLEN)) अणु
		स_हटाओ(skb_mac_header(skb) + VLAN_HLEN, skb_mac_header(skb),
			mac_len - VLAN_HLEN - ETH_TLEN);
	पूर्ण

	meta_len = skb_metadata_len(skb);
	अगर (meta_len) अणु
		meta = skb_metadata_end(skb) - meta_len;
		स_हटाओ(meta + VLAN_HLEN, meta, meta_len);
	पूर्ण

	skb->mac_header += VLAN_HLEN;
	वापस skb;
पूर्ण

काष्ठा sk_buff *skb_vlan_untag(काष्ठा sk_buff *skb)
अणु
	काष्ठा vlan_hdr *vhdr;
	u16 vlan_tci;

	अगर (unlikely(skb_vlan_tag_present(skb))) अणु
		/* vlan_tci is alपढ़ोy set-up so leave this क्रम another समय */
		वापस skb;
	पूर्ण

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		जाओ err_मुक्त;
	/* We may access the two bytes after vlan_hdr in vlan_set_encap_proto(). */
	अगर (unlikely(!pskb_may_pull(skb, VLAN_HLEN + माप(अचिन्हित लघु))))
		जाओ err_मुक्त;

	vhdr = (काष्ठा vlan_hdr *)skb->data;
	vlan_tci = ntohs(vhdr->h_vlan_TCI);
	__vlan_hwaccel_put_tag(skb, skb->protocol, vlan_tci);

	skb_pull_rcsum(skb, VLAN_HLEN);
	vlan_set_encap_proto(skb, vhdr);

	skb = skb_reorder_vlan_header(skb);
	अगर (unlikely(!skb))
		जाओ err_मुक्त;

	skb_reset_network_header(skb);
	अगर (!skb_transport_header_was_set(skb))
		skb_reset_transport_header(skb);
	skb_reset_mac_len(skb);

	वापस skb;

err_मुक्त:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(skb_vlan_untag);

पूर्णांक skb_ensure_writable(काष्ठा sk_buff *skb, पूर्णांक ग_लिखो_len)
अणु
	अगर (!pskb_may_pull(skb, ग_लिखो_len))
		वापस -ENOMEM;

	अगर (!skb_cloned(skb) || skb_clone_writable(skb, ग_लिखो_len))
		वापस 0;

	वापस pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL(skb_ensure_writable);

/* हटाओ VLAN header from packet and update csum accordingly.
 * expects a non skb_vlan_tag_present skb with a vlan tag payload
 */
पूर्णांक __skb_vlan_pop(काष्ठा sk_buff *skb, u16 *vlan_tci)
अणु
	काष्ठा vlan_hdr *vhdr;
	पूर्णांक offset = skb->data - skb_mac_header(skb);
	पूर्णांक err;

	अगर (WARN_ONCE(offset,
		      "__skb_vlan_pop got skb with skb->data not at mac header (offset %d)\n",
		      offset)) अणु
		वापस -EINVAL;
	पूर्ण

	err = skb_ensure_writable(skb, VLAN_ETH_HLEN);
	अगर (unlikely(err))
		वापस err;

	skb_postpull_rcsum(skb, skb->data + (2 * ETH_ALEN), VLAN_HLEN);

	vhdr = (काष्ठा vlan_hdr *)(skb->data + ETH_HLEN);
	*vlan_tci = ntohs(vhdr->h_vlan_TCI);

	स_हटाओ(skb->data + VLAN_HLEN, skb->data, 2 * ETH_ALEN);
	__skb_pull(skb, VLAN_HLEN);

	vlan_set_encap_proto(skb, vhdr);
	skb->mac_header += VLAN_HLEN;

	अगर (skb_network_offset(skb) < ETH_HLEN)
		skb_set_network_header(skb, ETH_HLEN);

	skb_reset_mac_len(skb);

	वापस err;
पूर्ण
EXPORT_SYMBOL(__skb_vlan_pop);

/* Pop a vlan tag either from hwaccel or from payload.
 * Expects skb->data at mac header.
 */
पूर्णांक skb_vlan_pop(काष्ठा sk_buff *skb)
अणु
	u16 vlan_tci;
	__be16 vlan_proto;
	पूर्णांक err;

	अगर (likely(skb_vlan_tag_present(skb))) अणु
		__vlan_hwaccel_clear_tag(skb);
	पूर्ण अन्यथा अणु
		अगर (unlikely(!eth_type_vlan(skb->protocol)))
			वापस 0;

		err = __skb_vlan_pop(skb, &vlan_tci);
		अगर (err)
			वापस err;
	पूर्ण
	/* move next vlan tag to hw accel tag */
	अगर (likely(!eth_type_vlan(skb->protocol)))
		वापस 0;

	vlan_proto = skb->protocol;
	err = __skb_vlan_pop(skb, &vlan_tci);
	अगर (unlikely(err))
		वापस err;

	__vlan_hwaccel_put_tag(skb, vlan_proto, vlan_tci);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_vlan_pop);

/* Push a vlan tag either पूर्णांकo hwaccel or पूर्णांकo payload (अगर hwaccel tag present).
 * Expects skb->data at mac header.
 */
पूर्णांक skb_vlan_push(काष्ठा sk_buff *skb, __be16 vlan_proto, u16 vlan_tci)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		पूर्णांक offset = skb->data - skb_mac_header(skb);
		पूर्णांक err;

		अगर (WARN_ONCE(offset,
			      "skb_vlan_push got skb with skb->data not at mac header (offset %d)\n",
			      offset)) अणु
			वापस -EINVAL;
		पूर्ण

		err = __vlan_insert_tag(skb, skb->vlan_proto,
					skb_vlan_tag_get(skb));
		अगर (err)
			वापस err;

		skb->protocol = skb->vlan_proto;
		skb->mac_len += VLAN_HLEN;

		skb_postpush_rcsum(skb, skb->data + (2 * ETH_ALEN), VLAN_HLEN);
	पूर्ण
	__vlan_hwaccel_put_tag(skb, vlan_proto, vlan_tci);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_vlan_push);

/**
 * skb_eth_pop() - Drop the Ethernet header at the head of a packet
 *
 * @skb: Socket buffer to modअगरy
 *
 * Drop the Ethernet header of @skb.
 *
 * Expects that skb->data poपूर्णांकs to the mac header and that no VLAN tags are
 * present.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_eth_pop(काष्ठा sk_buff *skb)
अणु
	अगर (!pskb_may_pull(skb, ETH_HLEN) || skb_vlan_tagged(skb) ||
	    skb_network_offset(skb) < ETH_HLEN)
		वापस -EPROTO;

	skb_pull_rcsum(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_eth_pop);

/**
 * skb_eth_push() - Add a new Ethernet header at the head of a packet
 *
 * @skb: Socket buffer to modअगरy
 * @dst: Destination MAC address of the new header
 * @src: Source MAC address of the new header
 *
 * Prepend @skb with a new Ethernet header.
 *
 * Expects that skb->data poपूर्णांकs to the mac header, which must be empty.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_eth_push(काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *dst,
		 स्थिर अचिन्हित अक्षर *src)
अणु
	काष्ठा ethhdr *eth;
	पूर्णांक err;

	अगर (skb_network_offset(skb) || skb_vlan_tag_present(skb))
		वापस -EPROTO;

	err = skb_cow_head(skb, माप(*eth));
	अगर (err < 0)
		वापस err;

	skb_push(skb, माप(*eth));
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	eth = eth_hdr(skb);
	ether_addr_copy(eth->h_dest, dst);
	ether_addr_copy(eth->h_source, src);
	eth->h_proto = skb->protocol;

	skb_postpush_rcsum(skb, eth, माप(*eth));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(skb_eth_push);

/* Update the ethertype of hdr and the skb csum value अगर required. */
अटल व्योम skb_mod_eth_type(काष्ठा sk_buff *skb, काष्ठा ethhdr *hdr,
			     __be16 ethertype)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		__be16 dअगरf[] = अणु ~hdr->h_proto, ethertype पूर्ण;

		skb->csum = csum_partial((अक्षर *)dअगरf, माप(dअगरf), skb->csum);
	पूर्ण

	hdr->h_proto = ethertype;
पूर्ण

/**
 * skb_mpls_push() - push a new MPLS header after mac_len bytes from start of
 *                   the packet
 *
 * @skb: buffer
 * @mpls_lse: MPLS label stack entry to push
 * @mpls_proto: ethertype of the new MPLS header (expects 0x8847 or 0x8848)
 * @mac_len: length of the MAC header
 * @ethernet: flag to indicate अगर the resulting packet after skb_mpls_push is
 *            ethernet
 *
 * Expects skb->data at mac header.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_mpls_push(काष्ठा sk_buff *skb, __be32 mpls_lse, __be16 mpls_proto,
		  पूर्णांक mac_len, bool ethernet)
अणु
	काष्ठा mpls_shim_hdr *lse;
	पूर्णांक err;

	अगर (unlikely(!eth_p_mpls(mpls_proto)))
		वापस -EINVAL;

	/* Networking stack करोes not allow simultaneous Tunnel and MPLS GSO. */
	अगर (skb->encapsulation)
		वापस -EINVAL;

	err = skb_cow_head(skb, MPLS_HLEN);
	अगर (unlikely(err))
		वापस err;

	अगर (!skb->inner_protocol) अणु
		skb_set_inner_network_header(skb, skb_network_offset(skb));
		skb_set_inner_protocol(skb, skb->protocol);
	पूर्ण

	skb_push(skb, MPLS_HLEN);
	स_हटाओ(skb_mac_header(skb) - MPLS_HLEN, skb_mac_header(skb),
		mac_len);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, mac_len);
	skb_reset_mac_len(skb);

	lse = mpls_hdr(skb);
	lse->label_stack_entry = mpls_lse;
	skb_postpush_rcsum(skb, lse, MPLS_HLEN);

	अगर (ethernet && mac_len >= ETH_HLEN)
		skb_mod_eth_type(skb, eth_hdr(skb), mpls_proto);
	skb->protocol = mpls_proto;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_mpls_push);

/**
 * skb_mpls_pop() - pop the outermost MPLS header
 *
 * @skb: buffer
 * @next_proto: ethertype of header after popped MPLS header
 * @mac_len: length of the MAC header
 * @ethernet: flag to indicate अगर the packet is ethernet
 *
 * Expects skb->data at mac header.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_mpls_pop(काष्ठा sk_buff *skb, __be16 next_proto, पूर्णांक mac_len,
		 bool ethernet)
अणु
	पूर्णांक err;

	अगर (unlikely(!eth_p_mpls(skb->protocol)))
		वापस 0;

	err = skb_ensure_writable(skb, mac_len + MPLS_HLEN);
	अगर (unlikely(err))
		वापस err;

	skb_postpull_rcsum(skb, mpls_hdr(skb), MPLS_HLEN);
	स_हटाओ(skb_mac_header(skb) + MPLS_HLEN, skb_mac_header(skb),
		mac_len);

	__skb_pull(skb, MPLS_HLEN);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, mac_len);

	अगर (ethernet && mac_len >= ETH_HLEN) अणु
		काष्ठा ethhdr *hdr;

		/* use mpls_hdr() to get ethertype to account क्रम VLANs. */
		hdr = (काष्ठा ethhdr *)((व्योम *)mpls_hdr(skb) - ETH_HLEN);
		skb_mod_eth_type(skb, hdr, next_proto);
	पूर्ण
	skb->protocol = next_proto;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_mpls_pop);

/**
 * skb_mpls_update_lse() - modअगरy outermost MPLS header and update csum
 *
 * @skb: buffer
 * @mpls_lse: new MPLS label stack entry to update to
 *
 * Expects skb->data at mac header.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_mpls_update_lse(काष्ठा sk_buff *skb, __be32 mpls_lse)
अणु
	पूर्णांक err;

	अगर (unlikely(!eth_p_mpls(skb->protocol)))
		वापस -EINVAL;

	err = skb_ensure_writable(skb, skb->mac_len + MPLS_HLEN);
	अगर (unlikely(err))
		वापस err;

	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		__be32 dअगरf[] = अणु ~mpls_hdr(skb)->label_stack_entry, mpls_lse पूर्ण;

		skb->csum = csum_partial((अक्षर *)dअगरf, माप(dअगरf), skb->csum);
	पूर्ण

	mpls_hdr(skb)->label_stack_entry = mpls_lse;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skb_mpls_update_lse);

/**
 * skb_mpls_dec_ttl() - decrement the TTL of the outermost MPLS header
 *
 * @skb: buffer
 *
 * Expects skb->data at mac header.
 *
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक skb_mpls_dec_ttl(काष्ठा sk_buff *skb)
अणु
	u32 lse;
	u8 ttl;

	अगर (unlikely(!eth_p_mpls(skb->protocol)))
		वापस -EINVAL;

	अगर (!pskb_may_pull(skb, skb_network_offset(skb) + MPLS_HLEN))
		वापस -ENOMEM;

	lse = be32_to_cpu(mpls_hdr(skb)->label_stack_entry);
	ttl = (lse & MPLS_LS_TTL_MASK) >> MPLS_LS_TTL_SHIFT;
	अगर (!--ttl)
		वापस -EINVAL;

	lse &= ~MPLS_LS_TTL_MASK;
	lse |= ttl << MPLS_LS_TTL_SHIFT;

	वापस skb_mpls_update_lse(skb, cpu_to_be32(lse));
पूर्ण
EXPORT_SYMBOL_GPL(skb_mpls_dec_ttl);

/**
 * alloc_skb_with_frags - allocate skb with page frags
 *
 * @header_len: size of linear part
 * @data_len: needed length in frags
 * @max_page_order: max page order desired.
 * @errcode: poपूर्णांकer to error code अगर any
 * @gfp_mask: allocation mask
 *
 * This can be used to allocate a paged skb, given a maximal order क्रम frags.
 */
काष्ठा sk_buff *alloc_skb_with_frags(अचिन्हित दीर्घ header_len,
				     अचिन्हित दीर्घ data_len,
				     पूर्णांक max_page_order,
				     पूर्णांक *errcode,
				     gfp_t gfp_mask)
अणु
	पूर्णांक npages = (data_len + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	अचिन्हित दीर्घ chunk;
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	पूर्णांक i;

	*errcode = -EMSGSIZE;
	/* Note this test could be relaxed, अगर we succeed to allocate
	 * high order pages...
	 */
	अगर (npages > MAX_SKB_FRAGS)
		वापस शून्य;

	*errcode = -ENOBUFS;
	skb = alloc_skb(header_len, gfp_mask);
	अगर (!skb)
		वापस शून्य;

	skb->truesize += npages << PAGE_SHIFT;

	क्रम (i = 0; npages > 0; i++) अणु
		पूर्णांक order = max_page_order;

		जबतक (order) अणु
			अगर (npages >= 1 << order) अणु
				page = alloc_pages((gfp_mask & ~__GFP_सूचीECT_RECLAIM) |
						   __GFP_COMP |
						   __GFP_NOWARN,
						   order);
				अगर (page)
					जाओ fill_page;
				/* Do not retry other high order allocations */
				order = 1;
				max_page_order = 0;
			पूर्ण
			order--;
		पूर्ण
		page = alloc_page(gfp_mask);
		अगर (!page)
			जाओ failure;
fill_page:
		chunk = min_t(अचिन्हित दीर्घ, data_len,
			      PAGE_SIZE << order);
		skb_fill_page_desc(skb, i, page, 0, chunk);
		data_len -= chunk;
		npages -= 1 << order;
	पूर्ण
	वापस skb;

failure:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(alloc_skb_with_frags);

/* carve out the first off bytes from skb when off < headlen */
अटल पूर्णांक pskb_carve_inside_header(काष्ठा sk_buff *skb, स्थिर u32 off,
				    स्थिर पूर्णांक headlen, gfp_t gfp_mask)
अणु
	पूर्णांक i;
	पूर्णांक size = skb_end_offset(skb);
	पूर्णांक new_hlen = headlen - off;
	u8 *data;

	size = SKB_DATA_ALIGN(size);

	अगर (skb_pfmeदो_स्मृति(skb))
		gfp_mask |= __GFP_MEMALLOC;
	data = kदो_स्मृति_reserve(size +
			       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)),
			       gfp_mask, NUMA_NO_NODE, शून्य);
	अगर (!data)
		वापस -ENOMEM;

	size = SKB_WITH_OVERHEAD(ksize(data));

	/* Copy real data, and all frags */
	skb_copy_from_linear_data_offset(skb, off, data, new_hlen);
	skb->len -= off;

	स_नकल((काष्ठा skb_shared_info *)(data + size),
	       skb_shinfo(skb),
	       दुरत्व(काष्ठा skb_shared_info,
			frags[skb_shinfo(skb)->nr_frags]));
	अगर (skb_cloned(skb)) अणु
		/* drop the old head gracefully */
		अगर (skb_orphan_frags(skb, gfp_mask)) अणु
			kमुक्त(data);
			वापस -ENOMEM;
		पूर्ण
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
			skb_frag_ref(skb, i);
		अगर (skb_has_frag_list(skb))
			skb_clone_fraglist(skb);
		skb_release_data(skb);
	पूर्ण अन्यथा अणु
		/* we can reuse existing recount- all we did was
		 * relocate values
		 */
		skb_मुक्त_head(skb);
	पूर्ण

	skb->head = data;
	skb->data = data;
	skb->head_frag = 0;
#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
	skb->end = size;
#अन्यथा
	skb->end = skb->head + size;
#पूर्ण_अगर
	skb_set_tail_poपूर्णांकer(skb, skb_headlen(skb));
	skb_headers_offset_update(skb, 0);
	skb->cloned = 0;
	skb->hdr_len = 0;
	skb->nohdr = 0;
	atomic_set(&skb_shinfo(skb)->dataref, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक pskb_carve(काष्ठा sk_buff *skb, स्थिर u32 off, gfp_t gfp);

/* carve out the first eat bytes from skb's frag_list. May recurse पूर्णांकo
 * pskb_carve()
 */
अटल पूर्णांक pskb_carve_frag_list(काष्ठा sk_buff *skb,
				काष्ठा skb_shared_info *shinfo, पूर्णांक eat,
				gfp_t gfp_mask)
अणु
	काष्ठा sk_buff *list = shinfo->frag_list;
	काष्ठा sk_buff *clone = शून्य;
	काष्ठा sk_buff *insp = शून्य;

	करो अणु
		अगर (!list) अणु
			pr_err("Not enough bytes to eat. Want %d\n", eat);
			वापस -EFAULT;
		पूर्ण
		अगर (list->len <= eat) अणु
			/* Eaten as whole. */
			eat -= list->len;
			list = list->next;
			insp = list;
		पूर्ण अन्यथा अणु
			/* Eaten partially. */
			अगर (skb_shared(list)) अणु
				clone = skb_clone(list, gfp_mask);
				अगर (!clone)
					वापस -ENOMEM;
				insp = list->next;
				list = clone;
			पूर्ण अन्यथा अणु
				/* This may be pulled without problems. */
				insp = list;
			पूर्ण
			अगर (pskb_carve(list, eat, gfp_mask) < 0) अणु
				kमुक्त_skb(clone);
				वापस -ENOMEM;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण जबतक (eat);

	/* Free pulled out fragments. */
	जबतक ((list = shinfo->frag_list) != insp) अणु
		shinfo->frag_list = list->next;
		kमुक्त_skb(list);
	पूर्ण
	/* And insert new clone at head. */
	अगर (clone) अणु
		clone->next = list;
		shinfo->frag_list = clone;
	पूर्ण
	वापस 0;
पूर्ण

/* carve off first len bytes from skb. Split line (off) is in the
 * non-linear part of skb
 */
अटल पूर्णांक pskb_carve_inside_nonlinear(काष्ठा sk_buff *skb, स्थिर u32 off,
				       पूर्णांक pos, gfp_t gfp_mask)
अणु
	पूर्णांक i, k = 0;
	पूर्णांक size = skb_end_offset(skb);
	u8 *data;
	स्थिर पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	काष्ठा skb_shared_info *shinfo;

	size = SKB_DATA_ALIGN(size);

	अगर (skb_pfmeदो_स्मृति(skb))
		gfp_mask |= __GFP_MEMALLOC;
	data = kदो_स्मृति_reserve(size +
			       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)),
			       gfp_mask, NUMA_NO_NODE, शून्य);
	अगर (!data)
		वापस -ENOMEM;

	size = SKB_WITH_OVERHEAD(ksize(data));

	स_नकल((काष्ठा skb_shared_info *)(data + size),
	       skb_shinfo(skb), दुरत्व(काष्ठा skb_shared_info, frags[0]));
	अगर (skb_orphan_frags(skb, gfp_mask)) अणु
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण
	shinfo = (काष्ठा skb_shared_info *)(data + size);
	क्रम (i = 0; i < nfrags; i++) अणु
		पूर्णांक fsize = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (pos + fsize > off) अणु
			shinfo->frags[k] = skb_shinfo(skb)->frags[i];

			अगर (pos < off) अणु
				/* Split frag.
				 * We have two variants in this हाल:
				 * 1. Move all the frag to the second
				 *    part, अगर it is possible. F.e.
				 *    this approach is mandatory क्रम TUX,
				 *    where splitting is expensive.
				 * 2. Split is accurately. We make this.
				 */
				skb_frag_off_add(&shinfo->frags[0], off - pos);
				skb_frag_size_sub(&shinfo->frags[0], off - pos);
			पूर्ण
			skb_frag_ref(skb, i);
			k++;
		पूर्ण
		pos += fsize;
	पूर्ण
	shinfo->nr_frags = k;
	अगर (skb_has_frag_list(skb))
		skb_clone_fraglist(skb);

	/* split line is in frag list */
	अगर (k == 0 && pskb_carve_frag_list(skb, shinfo, off - pos, gfp_mask)) अणु
		/* skb_frag_unref() is not needed here as shinfo->nr_frags = 0. */
		अगर (skb_has_frag_list(skb))
			kमुक्त_skb_list(skb_shinfo(skb)->frag_list);
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण
	skb_release_data(skb);

	skb->head = data;
	skb->head_frag = 0;
	skb->data = data;
#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
	skb->end = size;
#अन्यथा
	skb->end = skb->head + size;
#पूर्ण_अगर
	skb_reset_tail_poपूर्णांकer(skb);
	skb_headers_offset_update(skb, 0);
	skb->cloned   = 0;
	skb->hdr_len  = 0;
	skb->nohdr    = 0;
	skb->len -= off;
	skb->data_len = skb->len;
	atomic_set(&skb_shinfo(skb)->dataref, 1);
	वापस 0;
पूर्ण

/* हटाओ len bytes from the beginning of the skb */
अटल पूर्णांक pskb_carve(काष्ठा sk_buff *skb, स्थिर u32 len, gfp_t gfp)
अणु
	पूर्णांक headlen = skb_headlen(skb);

	अगर (len < headlen)
		वापस pskb_carve_inside_header(skb, len, headlen, gfp);
	अन्यथा
		वापस pskb_carve_inside_nonlinear(skb, len, headlen, gfp);
पूर्ण

/* Extract to_copy bytes starting at off from skb, and वापस this in
 * a new skb
 */
काष्ठा sk_buff *pskb_extract(काष्ठा sk_buff *skb, पूर्णांक off,
			     पूर्णांक to_copy, gfp_t gfp)
अणु
	काष्ठा sk_buff  *clone = skb_clone(skb, gfp);

	अगर (!clone)
		वापस शून्य;

	अगर (pskb_carve(clone, off, gfp) < 0 ||
	    pskb_trim(clone, to_copy)) अणु
		kमुक्त_skb(clone);
		वापस शून्य;
	पूर्ण
	वापस clone;
पूर्ण
EXPORT_SYMBOL(pskb_extract);

/**
 * skb_condense - try to get rid of fragments/frag_list अगर possible
 * @skb: buffer
 *
 * Can be used to save memory beक्रमe skb is added to a busy queue.
 * If packet has bytes in frags and enough tail room in skb->head,
 * pull all of them, so that we can मुक्त the frags right now and adjust
 * truesize.
 * Notes:
 *	We करो not पुनः_स्मृतिate skb->head thus can not fail.
 *	Caller must re-evaluate skb->truesize अगर needed.
 */
व्योम skb_condense(काष्ठा sk_buff *skb)
अणु
	अगर (skb->data_len) अणु
		अगर (skb->data_len > skb->end - skb->tail ||
		    skb_cloned(skb))
			वापस;

		/* Nice, we can मुक्त page frag(s) right now */
		__pskb_pull_tail(skb, skb->data_len);
	पूर्ण
	/* At this poपूर्णांक, skb->truesize might be over estimated,
	 * because skb had a fragment, and fragments करो not tell
	 * their truesize.
	 * When we pulled its content पूर्णांकo skb->head, fragment
	 * was मुक्तd, but __pskb_pull_tail() could not possibly
	 * adjust skb->truesize, not knowing the frag truesize.
	 */
	skb->truesize = SKB_TRUESIZE(skb_end_offset(skb));
पूर्ण

#अगर_घोषित CONFIG_SKB_EXTENSIONS
अटल व्योम *skb_ext_get_ptr(काष्ठा skb_ext *ext, क्रमागत skb_ext_id id)
अणु
	वापस (व्योम *)ext + (ext->offset[id] * SKB_EXT_ALIGN_VALUE);
पूर्ण

/**
 * __skb_ext_alloc - allocate a new skb extensions storage
 *
 * @flags: See kदो_स्मृति().
 *
 * Returns the newly allocated poपूर्णांकer. The poपूर्णांकer can later attached to a
 * skb via __skb_ext_set().
 * Note: caller must handle the skb_ext as an opaque data.
 */
काष्ठा skb_ext *__skb_ext_alloc(gfp_t flags)
अणु
	काष्ठा skb_ext *new = kmem_cache_alloc(skbuff_ext_cache, flags);

	अगर (new) अणु
		स_रखो(new->offset, 0, माप(new->offset));
		refcount_set(&new->refcnt, 1);
	पूर्ण

	वापस new;
पूर्ण

अटल काष्ठा skb_ext *skb_ext_maybe_cow(काष्ठा skb_ext *old,
					 अचिन्हित पूर्णांक old_active)
अणु
	काष्ठा skb_ext *new;

	अगर (refcount_पढ़ो(&old->refcnt) == 1)
		वापस old;

	new = kmem_cache_alloc(skbuff_ext_cache, GFP_ATOMIC);
	अगर (!new)
		वापस शून्य;

	स_नकल(new, old, old->chunks * SKB_EXT_ALIGN_VALUE);
	refcount_set(&new->refcnt, 1);

#अगर_घोषित CONFIG_XFRM
	अगर (old_active & (1 << SKB_EXT_SEC_PATH)) अणु
		काष्ठा sec_path *sp = skb_ext_get_ptr(old, SKB_EXT_SEC_PATH);
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < sp->len; i++)
			xfrm_state_hold(sp->xvec[i]);
	पूर्ण
#पूर्ण_अगर
	__skb_ext_put(old);
	वापस new;
पूर्ण

/**
 * __skb_ext_set - attach the specअगरied extension storage to this skb
 * @skb: buffer
 * @id: extension id
 * @ext: extension storage previously allocated via __skb_ext_alloc()
 *
 * Existing extensions, अगर any, are cleared.
 *
 * Returns the poपूर्णांकer to the extension.
 */
व्योम *__skb_ext_set(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id,
		    काष्ठा skb_ext *ext)
अणु
	अचिन्हित पूर्णांक newlen, newoff = SKB_EXT_CHUNKSIZखातापूर्ण(*ext);

	skb_ext_put(skb);
	newlen = newoff + skb_ext_type_len[id];
	ext->chunks = newlen;
	ext->offset[id] = newoff;
	skb->extensions = ext;
	skb->active_extensions = 1 << id;
	वापस skb_ext_get_ptr(ext, id);
पूर्ण

/**
 * skb_ext_add - allocate space क्रम given extension, COW अगर needed
 * @skb: buffer
 * @id: extension to allocate space क्रम
 *
 * Allocates enough space क्रम the given extension.
 * If the extension is alपढ़ोy present, a poपूर्णांकer to that extension
 * is वापसed.
 *
 * If the skb was cloned, COW applies and the वापसed memory can be
 * modअगरied without changing the extension space of clones buffers.
 *
 * Returns poपूर्णांकer to the extension or शून्य on allocation failure.
 */
व्योम *skb_ext_add(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id)
अणु
	काष्ठा skb_ext *new, *old = शून्य;
	अचिन्हित पूर्णांक newlen, newoff;

	अगर (skb->active_extensions) अणु
		old = skb->extensions;

		new = skb_ext_maybe_cow(old, skb->active_extensions);
		अगर (!new)
			वापस शून्य;

		अगर (__skb_ext_exist(new, id))
			जाओ set_active;

		newoff = new->chunks;
	पूर्ण अन्यथा अणु
		newoff = SKB_EXT_CHUNKSIZखातापूर्ण(*new);

		new = __skb_ext_alloc(GFP_ATOMIC);
		अगर (!new)
			वापस शून्य;
	पूर्ण

	newlen = newoff + skb_ext_type_len[id];
	new->chunks = newlen;
	new->offset[id] = newoff;
set_active:
	skb->extensions = new;
	skb->active_extensions |= 1 << id;
	वापस skb_ext_get_ptr(new, id);
पूर्ण
EXPORT_SYMBOL(skb_ext_add);

#अगर_घोषित CONFIG_XFRM
अटल व्योम skb_ext_put_sp(काष्ठा sec_path *sp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sp->len; i++)
		xfrm_state_put(sp->xvec[i]);
पूर्ण
#पूर्ण_अगर

व्योम __skb_ext_del(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id)
अणु
	काष्ठा skb_ext *ext = skb->extensions;

	skb->active_extensions &= ~(1 << id);
	अगर (skb->active_extensions == 0) अणु
		skb->extensions = शून्य;
		__skb_ext_put(ext);
#अगर_घोषित CONFIG_XFRM
	पूर्ण अन्यथा अगर (id == SKB_EXT_SEC_PATH &&
		   refcount_पढ़ो(&ext->refcnt) == 1) अणु
		काष्ठा sec_path *sp = skb_ext_get_ptr(ext, SKB_EXT_SEC_PATH);

		skb_ext_put_sp(sp);
		sp->len = 0;
#पूर्ण_अगर
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__skb_ext_del);

व्योम __skb_ext_put(काष्ठा skb_ext *ext)
अणु
	/* If this is last clone, nothing can increment
	 * it after check passes.  Aव्योमs one atomic op.
	 */
	अगर (refcount_पढ़ो(&ext->refcnt) == 1)
		जाओ मुक्त_now;

	अगर (!refcount_dec_and_test(&ext->refcnt))
		वापस;
मुक्त_now:
#अगर_घोषित CONFIG_XFRM
	अगर (__skb_ext_exist(ext, SKB_EXT_SEC_PATH))
		skb_ext_put_sp(skb_ext_get_ptr(ext, SKB_EXT_SEC_PATH));
#पूर्ण_अगर

	kmem_cache_मुक्त(skbuff_ext_cache, ext);
पूर्ण
EXPORT_SYMBOL(__skb_ext_put);
#पूर्ण_अगर /* CONFIG_SKB_EXTENSIONS */
