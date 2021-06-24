<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* XDP user-space ring काष्ठाure
 * Copyright(c) 2018 Intel Corporation.
 */

#अगर_अघोषित _LINUX_XSK_QUEUE_H
#घोषणा _LINUX_XSK_QUEUE_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_xdp.h>
#समावेश <net/xdp_sock.h>
#समावेश <net/xsk_buff_pool.h>

#समावेश "xsk.h"

काष्ठा xdp_ring अणु
	u32 producer ____cacheline_aligned_in_smp;
	/* Hinder the adjacent cache prefetcher to prefetch the consumer
	 * poपूर्णांकer अगर the producer poपूर्णांकer is touched and vice versa.
	 */
	u32 pad1 ____cacheline_aligned_in_smp;
	u32 consumer ____cacheline_aligned_in_smp;
	u32 pad2 ____cacheline_aligned_in_smp;
	u32 flags;
	u32 pad3 ____cacheline_aligned_in_smp;
पूर्ण;

/* Used क्रम the RX and TX queues क्रम packets */
काष्ठा xdp_rxtx_ring अणु
	काष्ठा xdp_ring ptrs;
	काष्ठा xdp_desc desc[] ____cacheline_aligned_in_smp;
पूर्ण;

/* Used क्रम the fill and completion queues क्रम buffers */
काष्ठा xdp_umem_ring अणु
	काष्ठा xdp_ring ptrs;
	u64 desc[] ____cacheline_aligned_in_smp;
पूर्ण;

काष्ठा xsk_queue अणु
	u32 ring_mask;
	u32 nentries;
	u32 cached_prod;
	u32 cached_cons;
	काष्ठा xdp_ring *ring;
	u64 invalid_descs;
	u64 queue_empty_descs;
पूर्ण;

/* The काष्ठाure of the shared state of the rings are a simple
 * circular buffer, as outlined in
 * Documentation/core-api/circular-buffers.rst. For the Rx and
 * completion ring, the kernel is the producer and user space is the
 * consumer. For the Tx and fill rings, the kernel is the consumer and
 * user space is the producer.
 *
 * producer                         consumer
 *
 * अगर (LOAD ->consumer) अणु  (A)      LOAD.acq ->producer  (C)
 *    STORE $data                   LOAD $data
 *    STORE.rel ->producer (B)      STORE.rel ->consumer (D)
 * पूर्ण
 *
 * (A) pairs with (D), and (B) pairs with (C).
 *
 * Starting with (B), it protects the data from being written after
 * the producer poपूर्णांकer. If this barrier was missing, the consumer
 * could observe the producer poपूर्णांकer being set and thus load the data
 * beक्रमe the producer has written the new data. The consumer would in
 * this हाल load the old data.
 *
 * (C) protects the consumer from speculatively loading the data beक्रमe
 * the producer poपूर्णांकer actually has been पढ़ो. If we करो not have this
 * barrier, some architectures could load old data as speculative loads
 * are not discarded as the CPU करोes not know there is a dependency
 * between ->producer and data.
 *
 * (A) is a control dependency that separates the load of ->consumer
 * from the stores of $data. In हाल ->consumer indicates there is no
 * room in the buffer to store $data we करो not. The dependency will
 * order both of the stores after the loads. So no barrier is needed.
 *
 * (D) protects the load of the data to be observed to happen after the
 * store of the consumer poपूर्णांकer. If we did not have this memory
 * barrier, the producer could observe the consumer poपूर्णांकer being set
 * and overग_लिखो the data with a new value beक्रमe the consumer got the
 * chance to पढ़ो the old value. The consumer would thus miss पढ़ोing
 * the old entry and very likely पढ़ो the new entry twice, once right
 * now and again after circling through the ring.
 */

/* The operations on the rings are the following:
 *
 * producer                           consumer
 *
 * RESERVE entries                    PEEK in the ring क्रम entries
 * WRITE data पूर्णांकo the ring           READ data from the ring
 * SUBMIT entries                     RELEASE entries
 *
 * The producer reserves one or more entries in the ring. It can then
 * fill in these entries and finally submit them so that they can be
 * seen and पढ़ो by the consumer.
 *
 * The consumer peeks पूर्णांकo the ring to see अगर the producer has written
 * any new entries. If so, the consumer can then पढ़ो these entries
 * and when it is करोne पढ़ोing them release them back to the producer
 * so that the producer can use these slots to fill in new entries.
 *
 * The function names below reflect these operations.
 */

/* Functions that पढ़ो and validate content from consumer rings. */

अटल अंतरभूत bool xskq_cons_पढ़ो_addr_unchecked(काष्ठा xsk_queue *q, u64 *addr)
अणु
	काष्ठा xdp_umem_ring *ring = (काष्ठा xdp_umem_ring *)q->ring;

	अगर (q->cached_cons != q->cached_prod) अणु
		u32 idx = q->cached_cons & q->ring_mask;

		*addr = ring->desc[idx];
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool xp_aligned_validate_desc(काष्ठा xsk_buff_pool *pool,
					    काष्ठा xdp_desc *desc)
अणु
	u64 chunk;

	अगर (desc->len > pool->chunk_size)
		वापस false;

	chunk = xp_aligned_extract_addr(pool, desc->addr);
	अगर (chunk >= pool->addrs_cnt)
		वापस false;

	अगर (desc->options)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool xp_unaligned_validate_desc(काष्ठा xsk_buff_pool *pool,
					      काष्ठा xdp_desc *desc)
अणु
	u64 addr, base_addr;

	base_addr = xp_unaligned_extract_addr(desc->addr);
	addr = xp_unaligned_add_offset_to_addr(desc->addr);

	अगर (desc->len > pool->chunk_size)
		वापस false;

	अगर (base_addr >= pool->addrs_cnt || addr >= pool->addrs_cnt ||
	    xp_desc_crosses_non_contig_pg(pool, addr, desc->len))
		वापस false;

	अगर (desc->options)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool xp_validate_desc(काष्ठा xsk_buff_pool *pool,
				    काष्ठा xdp_desc *desc)
अणु
	वापस pool->unaligned ? xp_unaligned_validate_desc(pool, desc) :
		xp_aligned_validate_desc(pool, desc);
पूर्ण

अटल अंतरभूत bool xskq_cons_is_valid_desc(काष्ठा xsk_queue *q,
					   काष्ठा xdp_desc *d,
					   काष्ठा xsk_buff_pool *pool)
अणु
	अगर (!xp_validate_desc(pool, d)) अणु
		q->invalid_descs++;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool xskq_cons_पढ़ो_desc(काष्ठा xsk_queue *q,
				       काष्ठा xdp_desc *desc,
				       काष्ठा xsk_buff_pool *pool)
अणु
	जबतक (q->cached_cons != q->cached_prod) अणु
		काष्ठा xdp_rxtx_ring *ring = (काष्ठा xdp_rxtx_ring *)q->ring;
		u32 idx = q->cached_cons & q->ring_mask;

		*desc = ring->desc[idx];
		अगर (xskq_cons_is_valid_desc(q, desc, pool))
			वापस true;

		q->cached_cons++;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत u32 xskq_cons_पढ़ो_desc_batch(काष्ठा xsk_queue *q,
					    काष्ठा xdp_desc *descs,
					    काष्ठा xsk_buff_pool *pool, u32 max)
अणु
	u32 cached_cons = q->cached_cons, nb_entries = 0;

	जबतक (cached_cons != q->cached_prod && nb_entries < max) अणु
		काष्ठा xdp_rxtx_ring *ring = (काष्ठा xdp_rxtx_ring *)q->ring;
		u32 idx = cached_cons & q->ring_mask;

		descs[nb_entries] = ring->desc[idx];
		अगर (unlikely(!xskq_cons_is_valid_desc(q, &descs[nb_entries], pool))) अणु
			/* Skip the entry */
			cached_cons++;
			जारी;
		पूर्ण

		nb_entries++;
		cached_cons++;
	पूर्ण

	वापस nb_entries;
पूर्ण

/* Functions क्रम consumers */

अटल अंतरभूत व्योम __xskq_cons_release(काष्ठा xsk_queue *q)
अणु
	smp_store_release(&q->ring->consumer, q->cached_cons); /* D, matchees A */
पूर्ण

अटल अंतरभूत व्योम __xskq_cons_peek(काष्ठा xsk_queue *q)
अणु
	/* Refresh the local poपूर्णांकer */
	q->cached_prod = smp_load_acquire(&q->ring->producer);  /* C, matches B */
पूर्ण

अटल अंतरभूत व्योम xskq_cons_get_entries(काष्ठा xsk_queue *q)
अणु
	__xskq_cons_release(q);
	__xskq_cons_peek(q);
पूर्ण

अटल अंतरभूत u32 xskq_cons_nb_entries(काष्ठा xsk_queue *q, u32 max)
अणु
	u32 entries = q->cached_prod - q->cached_cons;

	अगर (entries >= max)
		वापस max;

	__xskq_cons_peek(q);
	entries = q->cached_prod - q->cached_cons;

	वापस entries >= max ? max : entries;
पूर्ण

अटल अंतरभूत bool xskq_cons_has_entries(काष्ठा xsk_queue *q, u32 cnt)
अणु
	वापस xskq_cons_nb_entries(q, cnt) >= cnt ? true : false;
पूर्ण

अटल अंतरभूत bool xskq_cons_peek_addr_unchecked(काष्ठा xsk_queue *q, u64 *addr)
अणु
	अगर (q->cached_prod == q->cached_cons)
		xskq_cons_get_entries(q);
	वापस xskq_cons_पढ़ो_addr_unchecked(q, addr);
पूर्ण

अटल अंतरभूत bool xskq_cons_peek_desc(काष्ठा xsk_queue *q,
				       काष्ठा xdp_desc *desc,
				       काष्ठा xsk_buff_pool *pool)
अणु
	अगर (q->cached_prod == q->cached_cons)
		xskq_cons_get_entries(q);
	वापस xskq_cons_पढ़ो_desc(q, desc, pool);
पूर्ण

अटल अंतरभूत u32 xskq_cons_peek_desc_batch(काष्ठा xsk_queue *q, काष्ठा xdp_desc *descs,
					    काष्ठा xsk_buff_pool *pool, u32 max)
अणु
	u32 entries = xskq_cons_nb_entries(q, max);

	वापस xskq_cons_पढ़ो_desc_batch(q, descs, pool, entries);
पूर्ण

/* To improve perक्रमmance in the xskq_cons_release functions, only update local state here.
 * Reflect this to global state when we get new entries from the ring in
 * xskq_cons_get_entries() and whenever Rx or Tx processing are completed in the NAPI loop.
 */
अटल अंतरभूत व्योम xskq_cons_release(काष्ठा xsk_queue *q)
अणु
	q->cached_cons++;
पूर्ण

अटल अंतरभूत व्योम xskq_cons_release_n(काष्ठा xsk_queue *q, u32 cnt)
अणु
	q->cached_cons += cnt;
पूर्ण

अटल अंतरभूत bool xskq_cons_is_full(काष्ठा xsk_queue *q)
अणु
	/* No barriers needed since data is not accessed */
	वापस READ_ONCE(q->ring->producer) - READ_ONCE(q->ring->consumer) ==
		q->nentries;
पूर्ण

अटल अंतरभूत u32 xskq_cons_present_entries(काष्ठा xsk_queue *q)
अणु
	/* No barriers needed since data is not accessed */
	वापस READ_ONCE(q->ring->producer) - READ_ONCE(q->ring->consumer);
पूर्ण

/* Functions क्रम producers */

अटल अंतरभूत u32 xskq_prod_nb_मुक्त(काष्ठा xsk_queue *q, u32 max)
अणु
	u32 मुक्त_entries = q->nentries - (q->cached_prod - q->cached_cons);

	अगर (मुक्त_entries >= max)
		वापस max;

	/* Refresh the local tail poपूर्णांकer */
	q->cached_cons = READ_ONCE(q->ring->consumer);
	मुक्त_entries = q->nentries - (q->cached_prod - q->cached_cons);

	वापस मुक्त_entries >= max ? max : मुक्त_entries;
पूर्ण

अटल अंतरभूत bool xskq_prod_is_full(काष्ठा xsk_queue *q)
अणु
	वापस xskq_prod_nb_मुक्त(q, 1) ? false : true;
पूर्ण

अटल अंतरभूत व्योम xskq_prod_cancel(काष्ठा xsk_queue *q)
अणु
	q->cached_prod--;
पूर्ण

अटल अंतरभूत पूर्णांक xskq_prod_reserve(काष्ठा xsk_queue *q)
अणु
	अगर (xskq_prod_is_full(q))
		वापस -ENOSPC;

	/* A, matches D */
	q->cached_prod++;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xskq_prod_reserve_addr(काष्ठा xsk_queue *q, u64 addr)
अणु
	काष्ठा xdp_umem_ring *ring = (काष्ठा xdp_umem_ring *)q->ring;

	अगर (xskq_prod_is_full(q))
		वापस -ENOSPC;

	/* A, matches D */
	ring->desc[q->cached_prod++ & q->ring_mask] = addr;
	वापस 0;
पूर्ण

अटल अंतरभूत u32 xskq_prod_reserve_addr_batch(काष्ठा xsk_queue *q, काष्ठा xdp_desc *descs,
					       u32 max)
अणु
	काष्ठा xdp_umem_ring *ring = (काष्ठा xdp_umem_ring *)q->ring;
	u32 nb_entries, i, cached_prod;

	nb_entries = xskq_prod_nb_मुक्त(q, max);

	/* A, matches D */
	cached_prod = q->cached_prod;
	क्रम (i = 0; i < nb_entries; i++)
		ring->desc[cached_prod++ & q->ring_mask] = descs[i].addr;
	q->cached_prod = cached_prod;

	वापस nb_entries;
पूर्ण

अटल अंतरभूत पूर्णांक xskq_prod_reserve_desc(काष्ठा xsk_queue *q,
					 u64 addr, u32 len)
अणु
	काष्ठा xdp_rxtx_ring *ring = (काष्ठा xdp_rxtx_ring *)q->ring;
	u32 idx;

	अगर (xskq_prod_is_full(q))
		वापस -ENOSPC;

	/* A, matches D */
	idx = q->cached_prod++ & q->ring_mask;
	ring->desc[idx].addr = addr;
	ring->desc[idx].len = len;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __xskq_prod_submit(काष्ठा xsk_queue *q, u32 idx)
अणु
	smp_store_release(&q->ring->producer, idx); /* B, matches C */
पूर्ण

अटल अंतरभूत व्योम xskq_prod_submit(काष्ठा xsk_queue *q)
अणु
	__xskq_prod_submit(q, q->cached_prod);
पूर्ण

अटल अंतरभूत व्योम xskq_prod_submit_addr(काष्ठा xsk_queue *q, u64 addr)
अणु
	काष्ठा xdp_umem_ring *ring = (काष्ठा xdp_umem_ring *)q->ring;
	u32 idx = q->ring->producer;

	ring->desc[idx++ & q->ring_mask] = addr;

	__xskq_prod_submit(q, idx);
पूर्ण

अटल अंतरभूत व्योम xskq_prod_submit_n(काष्ठा xsk_queue *q, u32 nb_entries)
अणु
	__xskq_prod_submit(q, q->ring->producer + nb_entries);
पूर्ण

अटल अंतरभूत bool xskq_prod_is_empty(काष्ठा xsk_queue *q)
अणु
	/* No barriers needed since data is not accessed */
	वापस READ_ONCE(q->ring->consumer) == READ_ONCE(q->ring->producer);
पूर्ण

/* For both producers and consumers */

अटल अंतरभूत u64 xskq_nb_invalid_descs(काष्ठा xsk_queue *q)
अणु
	वापस q ? q->invalid_descs : 0;
पूर्ण

अटल अंतरभूत u64 xskq_nb_queue_empty_descs(काष्ठा xsk_queue *q)
अणु
	वापस q ? q->queue_empty_descs : 0;
पूर्ण

काष्ठा xsk_queue *xskq_create(u32 nentries, bool umem_queue);
व्योम xskq_destroy(काष्ठा xsk_queue *q_ops);

#पूर्ण_अगर /* _LINUX_XSK_QUEUE_H */
