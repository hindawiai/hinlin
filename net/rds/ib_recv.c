<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <rdma/rdma_cm.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "ib.h"

अटल काष्ठा kmem_cache *rds_ib_incoming_slab;
अटल काष्ठा kmem_cache *rds_ib_frag_slab;
अटल atomic_t	rds_ib_allocation = ATOMIC_INIT(0);

व्योम rds_ib_recv_init_ring(काष्ठा rds_ib_connection *ic)
अणु
	काष्ठा rds_ib_recv_work *recv;
	u32 i;

	क्रम (i = 0, recv = ic->i_recvs; i < ic->i_recv_ring.w_nr; i++, recv++) अणु
		काष्ठा ib_sge *sge;

		recv->r_ibinc = शून्य;
		recv->r_frag = शून्य;

		recv->r_wr.next = शून्य;
		recv->r_wr.wr_id = i;
		recv->r_wr.sg_list = recv->r_sge;
		recv->r_wr.num_sge = RDS_IB_RECV_SGE;

		sge = &recv->r_sge[0];
		sge->addr = ic->i_recv_hdrs_dma[i];
		sge->length = माप(काष्ठा rds_header);
		sge->lkey = ic->i_pd->local_dma_lkey;

		sge = &recv->r_sge[1];
		sge->addr = 0;
		sge->length = RDS_FRAG_SIZE;
		sge->lkey = ic->i_pd->local_dma_lkey;
	पूर्ण
पूर्ण

/*
 * The entire 'from' list, including the from element itself, is put on
 * to the tail of the 'to' list.
 */
अटल व्योम list_splice_entire_tail(काष्ठा list_head *from,
				    काष्ठा list_head *to)
अणु
	काष्ठा list_head *from_last = from->prev;

	list_splice_tail(from_last, to);
	list_add_tail(from_last, to);
पूर्ण

अटल व्योम rds_ib_cache_xfer_to_पढ़ोy(काष्ठा rds_ib_refill_cache *cache)
अणु
	काष्ठा list_head *पंचांगp;

	पंचांगp = xchg(&cache->xfer, शून्य);
	अगर (पंचांगp) अणु
		अगर (cache->पढ़ोy)
			list_splice_entire_tail(पंचांगp, cache->पढ़ोy);
		अन्यथा
			cache->पढ़ोy = पंचांगp;
	पूर्ण
पूर्ण

अटल पूर्णांक rds_ib_recv_alloc_cache(काष्ठा rds_ib_refill_cache *cache, gfp_t gfp)
अणु
	काष्ठा rds_ib_cache_head *head;
	पूर्णांक cpu;

	cache->percpu = alloc_percpu_gfp(काष्ठा rds_ib_cache_head, gfp);
	अगर (!cache->percpu)
	       वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		head = per_cpu_ptr(cache->percpu, cpu);
		head->first = शून्य;
		head->count = 0;
	पूर्ण
	cache->xfer = शून्य;
	cache->पढ़ोy = शून्य;

	वापस 0;
पूर्ण

पूर्णांक rds_ib_recv_alloc_caches(काष्ठा rds_ib_connection *ic, gfp_t gfp)
अणु
	पूर्णांक ret;

	ret = rds_ib_recv_alloc_cache(&ic->i_cache_incs, gfp);
	अगर (!ret) अणु
		ret = rds_ib_recv_alloc_cache(&ic->i_cache_frags, gfp);
		अगर (ret)
			मुक्त_percpu(ic->i_cache_incs.percpu);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rds_ib_cache_splice_all_lists(काष्ठा rds_ib_refill_cache *cache,
					  काष्ठा list_head *caller_list)
अणु
	काष्ठा rds_ib_cache_head *head;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		head = per_cpu_ptr(cache->percpu, cpu);
		अगर (head->first) अणु
			list_splice_entire_tail(head->first, caller_list);
			head->first = शून्य;
		पूर्ण
	पूर्ण

	अगर (cache->पढ़ोy) अणु
		list_splice_entire_tail(cache->पढ़ोy, caller_list);
		cache->पढ़ोy = शून्य;
	पूर्ण
पूर्ण

व्योम rds_ib_recv_मुक्त_caches(काष्ठा rds_ib_connection *ic)
अणु
	काष्ठा rds_ib_incoming *inc;
	काष्ठा rds_ib_incoming *inc_पंचांगp;
	काष्ठा rds_page_frag *frag;
	काष्ठा rds_page_frag *frag_पंचांगp;
	LIST_HEAD(list);

	rds_ib_cache_xfer_to_पढ़ोy(&ic->i_cache_incs);
	rds_ib_cache_splice_all_lists(&ic->i_cache_incs, &list);
	मुक्त_percpu(ic->i_cache_incs.percpu);

	list_क्रम_each_entry_safe(inc, inc_पंचांगp, &list, ii_cache_entry) अणु
		list_del(&inc->ii_cache_entry);
		WARN_ON(!list_empty(&inc->ii_frags));
		kmem_cache_मुक्त(rds_ib_incoming_slab, inc);
		atomic_dec(&rds_ib_allocation);
	पूर्ण

	rds_ib_cache_xfer_to_पढ़ोy(&ic->i_cache_frags);
	rds_ib_cache_splice_all_lists(&ic->i_cache_frags, &list);
	मुक्त_percpu(ic->i_cache_frags.percpu);

	list_क्रम_each_entry_safe(frag, frag_पंचांगp, &list, f_cache_entry) अणु
		list_del(&frag->f_cache_entry);
		WARN_ON(!list_empty(&frag->f_item));
		kmem_cache_मुक्त(rds_ib_frag_slab, frag);
	पूर्ण
पूर्ण

/* fwd decl */
अटल व्योम rds_ib_recv_cache_put(काष्ठा list_head *new_item,
				  काष्ठा rds_ib_refill_cache *cache);
अटल काष्ठा list_head *rds_ib_recv_cache_get(काष्ठा rds_ib_refill_cache *cache);


/* Recycle frag and attached recv buffer f_sg */
अटल व्योम rds_ib_frag_मुक्त(काष्ठा rds_ib_connection *ic,
			     काष्ठा rds_page_frag *frag)
अणु
	rdsdebug("frag %p page %p\n", frag, sg_page(&frag->f_sg));

	rds_ib_recv_cache_put(&frag->f_cache_entry, &ic->i_cache_frags);
	atomic_add(RDS_FRAG_SIZE / SZ_1K, &ic->i_cache_allocs);
	rds_ib_stats_add(s_ib_recv_added_to_cache, RDS_FRAG_SIZE);
पूर्ण

/* Recycle inc after मुक्तing attached frags */
व्योम rds_ib_inc_मुक्त(काष्ठा rds_incoming *inc)
अणु
	काष्ठा rds_ib_incoming *ibinc;
	काष्ठा rds_page_frag *frag;
	काष्ठा rds_page_frag *pos;
	काष्ठा rds_ib_connection *ic = inc->i_conn->c_transport_data;

	ibinc = container_of(inc, काष्ठा rds_ib_incoming, ii_inc);

	/* Free attached frags */
	list_क्रम_each_entry_safe(frag, pos, &ibinc->ii_frags, f_item) अणु
		list_del_init(&frag->f_item);
		rds_ib_frag_मुक्त(ic, frag);
	पूर्ण
	BUG_ON(!list_empty(&ibinc->ii_frags));

	rdsdebug("freeing ibinc %p inc %p\n", ibinc, inc);
	rds_ib_recv_cache_put(&ibinc->ii_cache_entry, &ic->i_cache_incs);
पूर्ण

अटल व्योम rds_ib_recv_clear_one(काष्ठा rds_ib_connection *ic,
				  काष्ठा rds_ib_recv_work *recv)
अणु
	अगर (recv->r_ibinc) अणु
		rds_inc_put(&recv->r_ibinc->ii_inc);
		recv->r_ibinc = शून्य;
	पूर्ण
	अगर (recv->r_frag) अणु
		ib_dma_unmap_sg(ic->i_cm_id->device, &recv->r_frag->f_sg, 1, DMA_FROM_DEVICE);
		rds_ib_frag_मुक्त(ic, recv->r_frag);
		recv->r_frag = शून्य;
	पूर्ण
पूर्ण

व्योम rds_ib_recv_clear_ring(काष्ठा rds_ib_connection *ic)
अणु
	u32 i;

	क्रम (i = 0; i < ic->i_recv_ring.w_nr; i++)
		rds_ib_recv_clear_one(ic, &ic->i_recvs[i]);
पूर्ण

अटल काष्ठा rds_ib_incoming *rds_ib_refill_one_inc(काष्ठा rds_ib_connection *ic,
						     gfp_t slab_mask)
अणु
	काष्ठा rds_ib_incoming *ibinc;
	काष्ठा list_head *cache_item;
	पूर्णांक avail_allocs;

	cache_item = rds_ib_recv_cache_get(&ic->i_cache_incs);
	अगर (cache_item) अणु
		ibinc = container_of(cache_item, काष्ठा rds_ib_incoming, ii_cache_entry);
	पूर्ण अन्यथा अणु
		avail_allocs = atomic_add_unless(&rds_ib_allocation,
						 1, rds_ib_sysctl_max_recv_allocation);
		अगर (!avail_allocs) अणु
			rds_ib_stats_inc(s_ib_rx_alloc_limit);
			वापस शून्य;
		पूर्ण
		ibinc = kmem_cache_alloc(rds_ib_incoming_slab, slab_mask);
		अगर (!ibinc) अणु
			atomic_dec(&rds_ib_allocation);
			वापस शून्य;
		पूर्ण
		rds_ib_stats_inc(s_ib_rx_total_incs);
	पूर्ण
	INIT_LIST_HEAD(&ibinc->ii_frags);
	rds_inc_init(&ibinc->ii_inc, ic->conn, &ic->conn->c_faddr);

	वापस ibinc;
पूर्ण

अटल काष्ठा rds_page_frag *rds_ib_refill_one_frag(काष्ठा rds_ib_connection *ic,
						    gfp_t slab_mask, gfp_t page_mask)
अणु
	काष्ठा rds_page_frag *frag;
	काष्ठा list_head *cache_item;
	पूर्णांक ret;

	cache_item = rds_ib_recv_cache_get(&ic->i_cache_frags);
	अगर (cache_item) अणु
		frag = container_of(cache_item, काष्ठा rds_page_frag, f_cache_entry);
		atomic_sub(RDS_FRAG_SIZE / SZ_1K, &ic->i_cache_allocs);
		rds_ib_stats_add(s_ib_recv_added_to_cache, RDS_FRAG_SIZE);
	पूर्ण अन्यथा अणु
		frag = kmem_cache_alloc(rds_ib_frag_slab, slab_mask);
		अगर (!frag)
			वापस शून्य;

		sg_init_table(&frag->f_sg, 1);
		ret = rds_page_reमुख्यder_alloc(&frag->f_sg,
					       RDS_FRAG_SIZE, page_mask);
		अगर (ret) अणु
			kmem_cache_मुक्त(rds_ib_frag_slab, frag);
			वापस शून्य;
		पूर्ण
		rds_ib_stats_inc(s_ib_rx_total_frags);
	पूर्ण

	INIT_LIST_HEAD(&frag->f_item);

	वापस frag;
पूर्ण

अटल पूर्णांक rds_ib_recv_refill_one(काष्ठा rds_connection *conn,
				  काष्ठा rds_ib_recv_work *recv, gfp_t gfp)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा ib_sge *sge;
	पूर्णांक ret = -ENOMEM;
	gfp_t slab_mask = gfp;
	gfp_t page_mask = gfp;

	अगर (gfp & __GFP_सूचीECT_RECLAIM) अणु
		slab_mask = GFP_KERNEL;
		page_mask = GFP_HIGHUSER;
	पूर्ण

	अगर (!ic->i_cache_incs.पढ़ोy)
		rds_ib_cache_xfer_to_पढ़ोy(&ic->i_cache_incs);
	अगर (!ic->i_cache_frags.पढ़ोy)
		rds_ib_cache_xfer_to_पढ़ोy(&ic->i_cache_frags);

	/*
	 * ibinc was taken from recv अगर recv contained the start of a message.
	 * recvs that were continuations will still have this allocated.
	 */
	अगर (!recv->r_ibinc) अणु
		recv->r_ibinc = rds_ib_refill_one_inc(ic, slab_mask);
		अगर (!recv->r_ibinc)
			जाओ out;
	पूर्ण

	WARN_ON(recv->r_frag); /* leak! */
	recv->r_frag = rds_ib_refill_one_frag(ic, slab_mask, page_mask);
	अगर (!recv->r_frag)
		जाओ out;

	ret = ib_dma_map_sg(ic->i_cm_id->device, &recv->r_frag->f_sg,
			    1, DMA_FROM_DEVICE);
	WARN_ON(ret != 1);

	sge = &recv->r_sge[0];
	sge->addr = ic->i_recv_hdrs_dma[recv - ic->i_recvs];
	sge->length = माप(काष्ठा rds_header);

	sge = &recv->r_sge[1];
	sge->addr = sg_dma_address(&recv->r_frag->f_sg);
	sge->length = sg_dma_len(&recv->r_frag->f_sg);

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक acquire_refill(काष्ठा rds_connection *conn)
अणु
	वापस test_and_set_bit(RDS_RECV_REFILL, &conn->c_flags) == 0;
पूर्ण

अटल व्योम release_refill(काष्ठा rds_connection *conn)
अणु
	clear_bit(RDS_RECV_REFILL, &conn->c_flags);

	/* We करोn't use रुको_on_bit()/wake_up_bit() because our waking is in a
	 * hot path and finding रुकोers is very rare.  We करोn't want to walk
	 * the प्रणाली-wide hashed रुकोqueue buckets in the fast path only to
	 * almost never find रुकोers.
	 */
	अगर (रुकोqueue_active(&conn->c_रुकोq))
		wake_up_all(&conn->c_रुकोq);
पूर्ण

/*
 * This tries to allocate and post unused work requests after making sure that
 * they have all the allocations they need to queue received fragments पूर्णांकo
 * sockets.
 */
व्योम rds_ib_recv_refill(काष्ठा rds_connection *conn, पूर्णांक prefill, gfp_t gfp)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rds_ib_recv_work *recv;
	अचिन्हित पूर्णांक posted = 0;
	पूर्णांक ret = 0;
	bool can_रुको = !!(gfp & __GFP_सूचीECT_RECLAIM);
	bool must_wake = false;
	u32 pos;

	/* the goal here is to just make sure that someone, somewhere
	 * is posting buffers.  If we can't get the refill lock,
	 * let them करो their thing
	 */
	अगर (!acquire_refill(conn))
		वापस;

	जबतक ((prefill || rds_conn_up(conn)) &&
	       rds_ib_ring_alloc(&ic->i_recv_ring, 1, &pos)) अणु
		अगर (pos >= ic->i_recv_ring.w_nr) अणु
			prपूर्णांकk(KERN_NOTICE "Argh - ring alloc returned pos=%u\n",
					pos);
			अवरोध;
		पूर्ण

		recv = &ic->i_recvs[pos];
		ret = rds_ib_recv_refill_one(conn, recv, gfp);
		अगर (ret) अणु
			must_wake = true;
			अवरोध;
		पूर्ण

		rdsdebug("recv %p ibinc %p page %p addr %lu\n", recv,
			 recv->r_ibinc, sg_page(&recv->r_frag->f_sg),
			 (दीर्घ)sg_dma_address(&recv->r_frag->f_sg));

		/* XXX when can this fail? */
		ret = ib_post_recv(ic->i_cm_id->qp, &recv->r_wr, शून्य);
		अगर (ret) अणु
			rds_ib_conn_error(conn, "recv post on "
			       "%pI6c returned %d, disconnecting and "
			       "reconnecting\n", &conn->c_faddr,
			       ret);
			अवरोध;
		पूर्ण

		posted++;

		अगर ((posted > 128 && need_resched()) || posted > 8192) अणु
			must_wake = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* We're करोing flow control - update the winकरोw. */
	अगर (ic->i_flowctl && posted)
		rds_ib_advertise_credits(conn, posted);

	अगर (ret)
		rds_ib_ring_unalloc(&ic->i_recv_ring, 1);

	release_refill(conn);

	/* अगर we're called from the softirq handler, we'll be GFP_NOWAIT.
	 * in this हाल the ring being low is going to lead to more पूर्णांकerrupts
	 * and we can safely let the softirq code take care of it unless the
	 * ring is completely empty.
	 *
	 * अगर we're called from krdsd, we'll be GFP_KERNEL.  In this हाल
	 * we might have raced with the softirq code जबतक we had the refill
	 * lock held.  Use rds_ib_ring_low() instead of ring_empty to decide
	 * अगर we should requeue.
	 */
	अगर (rds_conn_up(conn) &&
	    (must_wake ||
	    (can_रुको && rds_ib_ring_low(&ic->i_recv_ring)) ||
	    rds_ib_ring_empty(&ic->i_recv_ring))) अणु
		queue_delayed_work(rds_wq, &conn->c_recv_w, 1);
	पूर्ण
	अगर (can_रुको)
		cond_resched();
पूर्ण

/*
 * We want to recycle several types of recv allocations, like incs and frags.
 * To use this, the *_मुक्त() function passes in the ptr to a list_head within
 * the recyclee, as well as the cache to put it on.
 *
 * First, we put the memory on a percpu list. When this reaches a certain size,
 * We move it to an पूर्णांकermediate non-percpu list in a lockless manner, with some
 * xchg/compxchg wizardry.
 *
 * N.B. Instead of a list_head as the anchor, we use a single poपूर्णांकer, which can
 * be शून्य and xchg'd. The list is actually empty when the poपूर्णांकer is शून्य, and
 * list_empty() will वापस true with one element is actually present.
 */
अटल व्योम rds_ib_recv_cache_put(काष्ठा list_head *new_item,
				 काष्ठा rds_ib_refill_cache *cache)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *old, *chpfirst;

	local_irq_save(flags);

	chpfirst = __this_cpu_पढ़ो(cache->percpu->first);
	अगर (!chpfirst)
		INIT_LIST_HEAD(new_item);
	अन्यथा /* put on front */
		list_add_tail(new_item, chpfirst);

	__this_cpu_ग_लिखो(cache->percpu->first, new_item);
	__this_cpu_inc(cache->percpu->count);

	अगर (__this_cpu_पढ़ो(cache->percpu->count) < RDS_IB_RECYCLE_BATCH_COUNT)
		जाओ end;

	/*
	 * Return our per-cpu first list to the cache's xfer by atomically
	 * grabbing the current xfer list, appending it to our per-cpu list,
	 * and then atomically वापसing that entire list back to the
	 * cache's xfer list as long as it's still empty.
	 */
	करो अणु
		old = xchg(&cache->xfer, शून्य);
		अगर (old)
			list_splice_entire_tail(old, chpfirst);
		old = cmpxchg(&cache->xfer, शून्य, chpfirst);
	पूर्ण जबतक (old);


	__this_cpu_ग_लिखो(cache->percpu->first, शून्य);
	__this_cpu_ग_लिखो(cache->percpu->count, 0);
end:
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा list_head *rds_ib_recv_cache_get(काष्ठा rds_ib_refill_cache *cache)
अणु
	काष्ठा list_head *head = cache->पढ़ोy;

	अगर (head) अणु
		अगर (!list_empty(head)) अणु
			cache->पढ़ोy = head->next;
			list_del_init(head);
		पूर्ण अन्यथा
			cache->पढ़ोy = शून्य;
	पूर्ण

	वापस head;
पूर्ण

पूर्णांक rds_ib_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to)
अणु
	काष्ठा rds_ib_incoming *ibinc;
	काष्ठा rds_page_frag *frag;
	अचिन्हित दीर्घ to_copy;
	अचिन्हित दीर्घ frag_off = 0;
	पूर्णांक copied = 0;
	पूर्णांक ret;
	u32 len;

	ibinc = container_of(inc, काष्ठा rds_ib_incoming, ii_inc);
	frag = list_entry(ibinc->ii_frags.next, काष्ठा rds_page_frag, f_item);
	len = be32_to_cpu(inc->i_hdr.h_len);

	जबतक (iov_iter_count(to) && copied < len) अणु
		अगर (frag_off == RDS_FRAG_SIZE) अणु
			frag = list_entry(frag->f_item.next,
					  काष्ठा rds_page_frag, f_item);
			frag_off = 0;
		पूर्ण
		to_copy = min_t(अचिन्हित दीर्घ, iov_iter_count(to),
				RDS_FRAG_SIZE - frag_off);
		to_copy = min_t(अचिन्हित दीर्घ, to_copy, len - copied);

		/* XXX needs + offset क्रम multiple recvs per page */
		rds_stats_add(s_copy_to_user, to_copy);
		ret = copy_page_to_iter(sg_page(&frag->f_sg),
					frag->f_sg.offset + frag_off,
					to_copy,
					to);
		अगर (ret != to_copy)
			वापस -EFAULT;

		frag_off += to_copy;
		copied += to_copy;
	पूर्ण

	वापस copied;
पूर्ण

/* ic starts out kzalloc()ed */
व्योम rds_ib_recv_init_ack(काष्ठा rds_ib_connection *ic)
अणु
	काष्ठा ib_send_wr *wr = &ic->i_ack_wr;
	काष्ठा ib_sge *sge = &ic->i_ack_sge;

	sge->addr = ic->i_ack_dma;
	sge->length = माप(काष्ठा rds_header);
	sge->lkey = ic->i_pd->local_dma_lkey;

	wr->sg_list = sge;
	wr->num_sge = 1;
	wr->opcode = IB_WR_SEND;
	wr->wr_id = RDS_IB_ACK_WR_ID;
	wr->send_flags = IB_SEND_SIGNALED | IB_SEND_SOLICITED;
पूर्ण

/*
 * You'd think that with reliable IB connections you wouldn't need to ack
 * messages that have been received.  The problem is that IB hardware generates
 * an ack message beक्रमe it has DMAed the message पूर्णांकo memory.  This creates a
 * potential message loss अगर the HCA is disabled क्रम any reason between when it
 * sends the ack and beक्रमe the message is DMAed and processed.  This is only a
 * potential issue अगर another HCA is available क्रम fail-over.
 *
 * When the remote host receives our ack they'll मुक्त the sent message from
 * their send queue.  To decrease the latency of this we always send an ack
 * immediately after we've received messages.
 *
 * For simplicity, we only have one ack in flight at a समय.  This माला_दो
 * pressure on senders to have deep enough send queues to असलorb the latency of
 * a single ack frame being in flight.  This might not be good enough.
 *
 * This is implemented by have a दीर्घ-lived send_wr and sge which poपूर्णांक to a
 * अटलally allocated ack frame.  This ack wr करोes not fall under the ring
 * accounting that the tx and rx wrs करो.  The QP attribute specअगरically makes
 * room क्रम it beyond the ring size.  Send completion notices its special
 * wr_id and aव्योमs working with the ring in that हाल.
 */
#अगर_अघोषित KERNEL_HAS_ATOMIC64
व्योम rds_ib_set_ack(काष्ठा rds_ib_connection *ic, u64 seq, पूर्णांक ack_required)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ic->i_ack_lock, flags);
	ic->i_ack_next = seq;
	अगर (ack_required)
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	spin_unlock_irqrestore(&ic->i_ack_lock, flags);
पूर्ण

अटल u64 rds_ib_get_ack(काष्ठा rds_ib_connection *ic)
अणु
	अचिन्हित दीर्घ flags;
	u64 seq;

	clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);

	spin_lock_irqsave(&ic->i_ack_lock, flags);
	seq = ic->i_ack_next;
	spin_unlock_irqrestore(&ic->i_ack_lock, flags);

	वापस seq;
पूर्ण
#अन्यथा
व्योम rds_ib_set_ack(काष्ठा rds_ib_connection *ic, u64 seq, पूर्णांक ack_required)
अणु
	atomic64_set(&ic->i_ack_next, seq);
	अगर (ack_required) अणु
		smp_mb__beक्रमe_atomic();
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	पूर्ण
पूर्ण

अटल u64 rds_ib_get_ack(काष्ठा rds_ib_connection *ic)
अणु
	clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	smp_mb__after_atomic();

	वापस atomic64_पढ़ो(&ic->i_ack_next);
पूर्ण
#पूर्ण_अगर


अटल व्योम rds_ib_send_ack(काष्ठा rds_ib_connection *ic, अचिन्हित पूर्णांक adv_credits)
अणु
	काष्ठा rds_header *hdr = ic->i_ack;
	u64 seq;
	पूर्णांक ret;

	seq = rds_ib_get_ack(ic);

	rdsdebug("send_ack: ic %p ack %llu\n", ic, (अचिन्हित दीर्घ दीर्घ) seq);

	ib_dma_sync_single_क्रम_cpu(ic->rds_ibdev->dev, ic->i_ack_dma,
				   माप(*hdr), DMA_TO_DEVICE);
	rds_message_populate_header(hdr, 0, 0, 0);
	hdr->h_ack = cpu_to_be64(seq);
	hdr->h_credit = adv_credits;
	rds_message_make_checksum(hdr);
	ib_dma_sync_single_क्रम_device(ic->rds_ibdev->dev, ic->i_ack_dma,
				      माप(*hdr), DMA_TO_DEVICE);

	ic->i_ack_queued = jअगरfies;

	ret = ib_post_send(ic->i_cm_id->qp, &ic->i_ack_wr, शून्य);
	अगर (unlikely(ret)) अणु
		/* Failed to send. Release the WR, and
		 * क्रमce another ACK.
		 */
		clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);

		rds_ib_stats_inc(s_ib_ack_send_failure);

		rds_ib_conn_error(ic->conn, "sending ack failed\n");
	पूर्ण अन्यथा
		rds_ib_stats_inc(s_ib_ack_sent);
पूर्ण

/*
 * There are 3 ways of getting acknowledgements to the peer:
 *  1.	We call rds_ib_attempt_ack from the recv completion handler
 *	to send an ACK-only frame.
 *	However, there can be only one such frame in the send queue
 *	at any समय, so we may have to postpone it.
 *  2.	When another (data) packet is transmitted जबतक there's
 *	an ACK in the queue, we piggyback the ACK sequence number
 *	on the data packet.
 *  3.	If the ACK WR is करोne sending, we get called from the
 *	send queue completion handler, and check whether there's
 *	another ACK pending (postponed because the WR was on the
 *	queue). If so, we transmit it.
 *
 * We मुख्यtain 2 variables:
 *  -	i_ack_flags, which keeps track of whether the ACK WR
 *	is currently in the send queue or not (IB_ACK_IN_FLIGHT)
 *  -	i_ack_next, which is the last sequence number we received
 *
 * Potentially, send queue and receive queue handlers can run concurrently.
 * It would be nice to not have to use a spinlock to synchronize things,
 * but the one problem that rules this out is that 64bit updates are
 * not atomic on all platक्रमms. Things would be a lot simpler अगर
 * we had atomic64 or maybe cmpxchg64 everywhere.
 *
 * Reconnecting complicates this picture just slightly. When we
 * reconnect, we may be seeing duplicate packets. The peer
 * is retransmitting them, because it hasn't seen an ACK क्रम
 * them. It is important that we ACK these.
 *
 * ACK mitigation adds a header flag "ACK_REQUIRED"; any packet with
 * this flag set *MUST* be acknowledged immediately.
 */

/*
 * When we get here, we're called from the recv queue handler.
 * Check whether we ought to transmit an ACK.
 */
व्योम rds_ib_attempt_ack(काष्ठा rds_ib_connection *ic)
अणु
	अचिन्हित पूर्णांक adv_credits;

	अगर (!test_bit(IB_ACK_REQUESTED, &ic->i_ack_flags))
		वापस;

	अगर (test_and_set_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags)) अणु
		rds_ib_stats_inc(s_ib_ack_send_delayed);
		वापस;
	पूर्ण

	/* Can we get a send credit? */
	अगर (!rds_ib_send_grab_credits(ic, 1, &adv_credits, 0, RDS_MAX_ADV_CREDIT)) अणु
		rds_ib_stats_inc(s_ib_tx_throttle);
		clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
		वापस;
	पूर्ण

	clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	rds_ib_send_ack(ic, adv_credits);
पूर्ण

/*
 * We get here from the send completion handler, when the
 * adapter tells us the ACK frame was sent.
 */
व्योम rds_ib_ack_send_complete(काष्ठा rds_ib_connection *ic)
अणु
	clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
	rds_ib_attempt_ack(ic);
पूर्ण

/*
 * This is called by the regular xmit code when it wants to piggyback
 * an ACK on an outgoing frame.
 */
u64 rds_ib_piggyb_ack(काष्ठा rds_ib_connection *ic)
अणु
	अगर (test_and_clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags))
		rds_ib_stats_inc(s_ib_ack_send_piggybacked);
	वापस rds_ib_get_ack(ic);
पूर्ण

/*
 * It's kind of lame that we're copying from the posted receive pages पूर्णांकo
 * दीर्घ-lived biपंचांगaps.  We could have posted the biपंचांगaps and rdma written पूर्णांकo
 * them.  But receiving new congestion biपंचांगaps should be a *rare* event, so
 * hopefully we won't need to invest that complनिकासy in making it more
 * efficient.  By copying we can share a simpler core with TCP which has to
 * copy.
 */
अटल व्योम rds_ib_cong_recv(काष्ठा rds_connection *conn,
			      काष्ठा rds_ib_incoming *ibinc)
अणु
	काष्ठा rds_cong_map *map;
	अचिन्हित पूर्णांक map_off;
	अचिन्हित पूर्णांक map_page;
	काष्ठा rds_page_frag *frag;
	अचिन्हित दीर्घ frag_off;
	अचिन्हित दीर्घ to_copy;
	अचिन्हित दीर्घ copied;
	__le64 uncongested = 0;
	व्योम *addr;

	/* catch completely corrupt packets */
	अगर (be32_to_cpu(ibinc->ii_inc.i_hdr.h_len) != RDS_CONG_MAP_BYTES)
		वापस;

	map = conn->c_fcong;
	map_page = 0;
	map_off = 0;

	frag = list_entry(ibinc->ii_frags.next, काष्ठा rds_page_frag, f_item);
	frag_off = 0;

	copied = 0;

	जबतक (copied < RDS_CONG_MAP_BYTES) अणु
		__le64 *src, *dst;
		अचिन्हित पूर्णांक k;

		to_copy = min(RDS_FRAG_SIZE - frag_off, PAGE_SIZE - map_off);
		BUG_ON(to_copy & 7); /* Must be 64bit aligned. */

		addr = kmap_atomic(sg_page(&frag->f_sg));

		src = addr + frag->f_sg.offset + frag_off;
		dst = (व्योम *)map->m_page_addrs[map_page] + map_off;
		क्रम (k = 0; k < to_copy; k += 8) अणु
			/* Record ports that became uncongested, ie
			 * bits that changed from 0 to 1. */
			uncongested |= ~(*src) & *dst;
			*dst++ = *src++;
		पूर्ण
		kunmap_atomic(addr);

		copied += to_copy;

		map_off += to_copy;
		अगर (map_off == PAGE_SIZE) अणु
			map_off = 0;
			map_page++;
		पूर्ण

		frag_off += to_copy;
		अगर (frag_off == RDS_FRAG_SIZE) अणु
			frag = list_entry(frag->f_item.next,
					  काष्ठा rds_page_frag, f_item);
			frag_off = 0;
		पूर्ण
	पूर्ण

	/* the congestion map is in little endian order */
	rds_cong_map_updated(map, le64_to_cpu(uncongested));
पूर्ण

अटल व्योम rds_ib_process_recv(काष्ठा rds_connection *conn,
				काष्ठा rds_ib_recv_work *recv, u32 data_len,
				काष्ठा rds_ib_ack_state *state)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rds_ib_incoming *ibinc = ic->i_ibinc;
	काष्ठा rds_header *ihdr, *hdr;
	dma_addr_t dma_addr = ic->i_recv_hdrs_dma[recv - ic->i_recvs];

	/* XXX shut करोwn the connection अगर port 0,0 are seen? */

	rdsdebug("ic %p ibinc %p recv %p byte len %u\n", ic, ibinc, recv,
		 data_len);

	अगर (data_len < माप(काष्ठा rds_header)) अणु
		rds_ib_conn_error(conn, "incoming message "
		       "from %pI6c didn't include a "
		       "header, disconnecting and "
		       "reconnecting\n",
		       &conn->c_faddr);
		वापस;
	पूर्ण
	data_len -= माप(काष्ठा rds_header);

	ihdr = ic->i_recv_hdrs[recv - ic->i_recvs];

	ib_dma_sync_single_क्रम_cpu(ic->rds_ibdev->dev, dma_addr,
				   माप(*ihdr), DMA_FROM_DEVICE);
	/* Validate the checksum. */
	अगर (!rds_message_verअगरy_checksum(ihdr)) अणु
		rds_ib_conn_error(conn, "incoming message "
		       "from %pI6c has corrupted header - "
		       "forcing a reconnect\n",
		       &conn->c_faddr);
		rds_stats_inc(s_recv_drop_bad_checksum);
		जाओ करोne;
	पूर्ण

	/* Process the ACK sequence which comes with every packet */
	state->ack_recv = be64_to_cpu(ihdr->h_ack);
	state->ack_recv_valid = 1;

	/* Process the credits update अगर there was one */
	अगर (ihdr->h_credit)
		rds_ib_send_add_credits(conn, ihdr->h_credit);

	अगर (ihdr->h_sport == 0 && ihdr->h_dport == 0 && data_len == 0) अणु
		/* This is an ACK-only packet. The fact that it माला_लो
		 * special treaपंचांगent here is that historically, ACKs
		 * were rather special beasts.
		 */
		rds_ib_stats_inc(s_ib_ack_received);

		/*
		 * Usually the frags make their way on to incs and are then मुक्तd as
		 * the inc is मुक्तd.  We करोn't go that route, so we have to drop the
		 * page ref ourselves.  We can't just leave the page on the recv
		 * because that confuses the dma mapping of pages and each recv's use
		 * of a partial page.
		 *
		 * FIXME: Fold this पूर्णांकo the code path below.
		 */
		rds_ib_frag_मुक्त(ic, recv->r_frag);
		recv->r_frag = शून्य;
		जाओ करोne;
	पूर्ण

	/*
	 * If we करोn't alपढ़ोy have an inc on the connection then this
	 * fragment has a header and starts a message.. copy its header
	 * पूर्णांकo the inc and save the inc so we can hang upcoming fragments
	 * off its list.
	 */
	अगर (!ibinc) अणु
		ibinc = recv->r_ibinc;
		recv->r_ibinc = शून्य;
		ic->i_ibinc = ibinc;

		hdr = &ibinc->ii_inc.i_hdr;
		ibinc->ii_inc.i_rx_lat_trace[RDS_MSG_RX_HDR] =
				local_घड़ी();
		स_नकल(hdr, ihdr, माप(*hdr));
		ic->i_recv_data_rem = be32_to_cpu(hdr->h_len);
		ibinc->ii_inc.i_rx_lat_trace[RDS_MSG_RX_START] =
				local_घड़ी();

		rdsdebug("ic %p ibinc %p rem %u flag 0x%x\n", ic, ibinc,
			 ic->i_recv_data_rem, hdr->h_flags);
	पूर्ण अन्यथा अणु
		hdr = &ibinc->ii_inc.i_hdr;
		/* We can't just use स_भेद here; fragments of a
		 * single message may carry dअगरferent ACKs */
		अगर (hdr->h_sequence != ihdr->h_sequence ||
		    hdr->h_len != ihdr->h_len ||
		    hdr->h_sport != ihdr->h_sport ||
		    hdr->h_dport != ihdr->h_dport) अणु
			rds_ib_conn_error(conn,
				"fragment header mismatch; forcing reconnect\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	list_add_tail(&recv->r_frag->f_item, &ibinc->ii_frags);
	recv->r_frag = शून्य;

	अगर (ic->i_recv_data_rem > RDS_FRAG_SIZE)
		ic->i_recv_data_rem -= RDS_FRAG_SIZE;
	अन्यथा अणु
		ic->i_recv_data_rem = 0;
		ic->i_ibinc = शून्य;

		अगर (ibinc->ii_inc.i_hdr.h_flags == RDS_FLAG_CONG_BITMAP) अणु
			rds_ib_cong_recv(conn, ibinc);
		पूर्ण अन्यथा अणु
			rds_recv_incoming(conn, &conn->c_faddr, &conn->c_laddr,
					  &ibinc->ii_inc, GFP_ATOMIC);
			state->ack_next = be64_to_cpu(hdr->h_sequence);
			state->ack_next_valid = 1;
		पूर्ण

		/* Evaluate the ACK_REQUIRED flag *after* we received
		 * the complete frame, and after bumping the next_rx
		 * sequence. */
		अगर (hdr->h_flags & RDS_FLAG_ACK_REQUIRED) अणु
			rds_stats_inc(s_recv_ack_required);
			state->ack_required = 1;
		पूर्ण

		rds_inc_put(&ibinc->ii_inc);
	पूर्ण
करोne:
	ib_dma_sync_single_क्रम_device(ic->rds_ibdev->dev, dma_addr,
				      माप(*ihdr), DMA_FROM_DEVICE);
पूर्ण

व्योम rds_ib_recv_cqe_handler(काष्ठा rds_ib_connection *ic,
			     काष्ठा ib_wc *wc,
			     काष्ठा rds_ib_ack_state *state)
अणु
	काष्ठा rds_connection *conn = ic->conn;
	काष्ठा rds_ib_recv_work *recv;

	rdsdebug("wc wr_id 0x%llx status %u (%s) byte_len %u imm_data %u\n",
		 (अचिन्हित दीर्घ दीर्घ)wc->wr_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_len,
		 be32_to_cpu(wc->ex.imm_data));

	rds_ib_stats_inc(s_ib_rx_cq_event);
	recv = &ic->i_recvs[rds_ib_ring_oldest(&ic->i_recv_ring)];
	ib_dma_unmap_sg(ic->i_cm_id->device, &recv->r_frag->f_sg, 1,
			DMA_FROM_DEVICE);

	/* Also process recvs in connecting state because it is possible
	 * to get a recv completion _beक्रमe_ the rdmacm ESTABLISHED
	 * event is processed.
	 */
	अगर (wc->status == IB_WC_SUCCESS) अणु
		rds_ib_process_recv(conn, recv, wc->byte_len, state);
	पूर्ण अन्यथा अणु
		/* We expect errors as the qp is drained during shutकरोwn */
		अगर (rds_conn_up(conn) || rds_conn_connecting(conn))
			rds_ib_conn_error(conn, "recv completion on <%pI6c,%pI6c, %d> had status %u (%s), vendor err 0x%x, disconnecting and reconnecting\n",
					  &conn->c_laddr, &conn->c_faddr,
					  conn->c_tos, wc->status,
					  ib_wc_status_msg(wc->status),
					  wc->venकरोr_err);
	पूर्ण

	/* rds_ib_process_recv() करोesn't always consume the frag, and
	 * we might not have called it at all अगर the wc didn't indicate
	 * success. We alपढ़ोy unmapped the frag's pages, though, and
	 * the following rds_ib_ring_मुक्त() call tells the refill path
	 * that it will not find an allocated frag here. Make sure we
	 * keep that promise by मुक्तing a frag that's still on the ring.
	 */
	अगर (recv->r_frag) अणु
		rds_ib_frag_मुक्त(ic, recv->r_frag);
		recv->r_frag = शून्य;
	पूर्ण
	rds_ib_ring_मुक्त(&ic->i_recv_ring, 1);

	/* If we ever end up with a really empty receive ring, we're
	 * in deep trouble, as the sender will definitely see RNR
	 * समयouts. */
	अगर (rds_ib_ring_empty(&ic->i_recv_ring))
		rds_ib_stats_inc(s_ib_rx_ring_empty);

	अगर (rds_ib_ring_low(&ic->i_recv_ring)) अणु
		rds_ib_recv_refill(conn, 0, GFP_NOWAIT | __GFP_NOWARN);
		rds_ib_stats_inc(s_ib_rx_refill_from_cq);
	पूर्ण
पूर्ण

पूर्णांक rds_ib_recv_path(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p\n", conn);
	अगर (rds_conn_up(conn)) अणु
		rds_ib_attempt_ack(ic);
		rds_ib_recv_refill(conn, 0, GFP_KERNEL);
		rds_ib_stats_inc(s_ib_rx_refill_from_thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rds_ib_recv_init(व्योम)
अणु
	काष्ठा sysinfo si;
	पूर्णांक ret = -ENOMEM;

	/* Default to 30% of all available RAM क्रम recv memory */
	si_meminfo(&si);
	rds_ib_sysctl_max_recv_allocation = si.totalram / 3 * PAGE_SIZE / RDS_FRAG_SIZE;

	rds_ib_incoming_slab =
		kmem_cache_create_usercopy("rds_ib_incoming",
					   माप(काष्ठा rds_ib_incoming),
					   0, SLAB_HWCACHE_ALIGN,
					   दुरत्व(काष्ठा rds_ib_incoming,
						    ii_inc.i_usercopy),
					   माप(काष्ठा rds_inc_usercopy),
					   शून्य);
	अगर (!rds_ib_incoming_slab)
		जाओ out;

	rds_ib_frag_slab = kmem_cache_create("rds_ib_frag",
					माप(काष्ठा rds_page_frag),
					0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!rds_ib_frag_slab) अणु
		kmem_cache_destroy(rds_ib_incoming_slab);
		rds_ib_incoming_slab = शून्य;
	पूर्ण अन्यथा
		ret = 0;
out:
	वापस ret;
पूर्ण

व्योम rds_ib_recv_निकास(व्योम)
अणु
	WARN_ON(atomic_पढ़ो(&rds_ib_allocation));

	kmem_cache_destroy(rds_ib_incoming_slab);
	kmem_cache_destroy(rds_ib_frag_slab);
पूर्ण
