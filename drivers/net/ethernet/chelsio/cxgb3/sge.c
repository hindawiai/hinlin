<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
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
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश <net/arp.h>
#समावेश "common.h"
#समावेश "regs.h"
#समावेश "sge_defs.h"
#समावेश "t3_cpl.h"
#समावेश "firmware_exports.h"
#समावेश "cxgb3_offload.h"

#घोषणा USE_GTS 0

#घोषणा SGE_RX_SM_BUF_SIZE 1536

#घोषणा SGE_RX_COPY_THRES  256
#घोषणा SGE_RX_PULL_LEN    128

#घोषणा SGE_PG_RSVD SMP_CACHE_BYTES
/*
 * Page chunk size क्रम FL0 buffers अगर FL0 is to be populated with page chunks.
 * It must be a भागisor of PAGE_SIZE.  If set to 0 FL0 will use sk_buffs
 * directly.
 */
#घोषणा FL0_PG_CHUNK_SIZE  2048
#घोषणा FL0_PG_ORDER 0
#घोषणा FL0_PG_ALLOC_SIZE (PAGE_SIZE << FL0_PG_ORDER)
#घोषणा FL1_PG_CHUNK_SIZE (PAGE_SIZE > 8192 ? 16384 : 8192)
#घोषणा FL1_PG_ORDER (PAGE_SIZE > 8192 ? 0 : 1)
#घोषणा FL1_PG_ALLOC_SIZE (PAGE_SIZE << FL1_PG_ORDER)

#घोषणा SGE_RX_DROP_THRES 16
#घोषणा RX_RECLAIM_PERIOD (HZ/4)

/*
 * Max number of Rx buffers we replenish at a समय.
 */
#घोषणा MAX_RX_REFILL 16U
/*
 * Period of the Tx buffer reclaim समयr.  This समयr करोes not need to run
 * frequently as Tx buffers are usually reclaimed by new Tx packets.
 */
#घोषणा TX_RECLAIM_PERIOD (HZ / 4)
#घोषणा TX_RECLAIM_TIMER_CHUNK 64U
#घोषणा TX_RECLAIM_CHUNK 16U

/* WR size in bytes */
#घोषणा WR_LEN (WR_FLITS * 8)

/*
 * Types of Tx queues in each queue set.  Order here matters, करो not change.
 */
क्रमागत अणु TXQ_ETH, TXQ_OFLD, TXQ_CTRL पूर्ण;

/* Values क्रम sge_txq.flags */
क्रमागत अणु
	TXQ_RUNNING = 1 << 0,	/* fetch engine is running */
	TXQ_LAST_PKT_DB = 1 << 1,	/* last packet rang the करोorbell */
पूर्ण;

काष्ठा tx_desc अणु
	__be64 flit[TX_DESC_FLITS];
पूर्ण;

काष्ठा rx_desc अणु
	__be32 addr_lo;
	__be32 len_gen;
	__be32 gen2;
	__be32 addr_hi;
पूर्ण;

काष्ठा tx_sw_desc अणु		/* SW state per Tx descriptor */
	काष्ठा sk_buff *skb;
	u8 eop;       /* set अगर last descriptor क्रम packet */
	u8 addr_idx;  /* buffer index of first SGL entry in descriptor */
	u8 fragidx;   /* first page fragment associated with descriptor */
	s8 sflit;     /* start flit of first SGL entry in descriptor */
पूर्ण;

काष्ठा rx_sw_desc अणु                /* SW state per Rx descriptor */
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा fl_pg_chunk pg_chunk;
	पूर्ण;
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
पूर्ण;

काष्ठा rsp_desc अणु		/* response queue descriptor */
	काष्ठा rss_header rss_hdr;
	__be32 flags;
	__be32 len_cq;
	u8 imm_data[47];
	u8 पूर्णांकr_gen;
पूर्ण;

/*
 * Holds unmapping inक्रमmation क्रम Tx packets that need deferred unmapping.
 * This काष्ठाure lives at skb->head and must be allocated by callers.
 */
काष्ठा deferred_unmap_info अणु
	काष्ठा pci_dev *pdev;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
पूर्ण;

/*
 * Maps a number of flits to the number of Tx descriptors that can hold them.
 * The क्रमmula is
 *
 * desc = 1 + (flits - 2) / (WR_FLITS - 1).
 *
 * HW allows up to 4 descriptors to be combined पूर्णांकo a WR.
 */
अटल u8 flit_desc_map[] = अणु
	0,
#अगर SGE_NUM_GENBITS == 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
#या_अगर SGE_NUM_GENBITS == 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
#अन्यथा
# error "SGE_NUM_GENBITS must be 1 or 2"
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा sge_qset *fl_to_qset(स्थिर काष्ठा sge_fl *q, पूर्णांक qidx)
अणु
	वापस container_of(q, काष्ठा sge_qset, fl[qidx]);
पूर्ण

अटल अंतरभूत काष्ठा sge_qset *rspq_to_qset(स्थिर काष्ठा sge_rspq *q)
अणु
	वापस container_of(q, काष्ठा sge_qset, rspq);
पूर्ण

अटल अंतरभूत काष्ठा sge_qset *txq_to_qset(स्थिर काष्ठा sge_txq *q, पूर्णांक qidx)
अणु
	वापस container_of(q, काष्ठा sge_qset, txq[qidx]);
पूर्ण

/**
 *	refill_rspq - replenish an SGE response queue
 *	@adapter: the adapter
 *	@q: the response queue to replenish
 *	@credits: how many new responses to make available
 *
 *	Replenishes a response queue by making the supplied number of responses
 *	available to HW.
 */
अटल अंतरभूत व्योम refill_rspq(काष्ठा adapter *adapter,
			       स्थिर काष्ठा sge_rspq *q, अचिन्हित पूर्णांक credits)
अणु
	rmb();
	t3_ग_लिखो_reg(adapter, A_SG_RSPQ_CREDIT_RETURN,
		     V_RSPQ(q->cntxt_id) | V_CREDITS(credits));
पूर्ण

/**
 *	need_skb_unmap - करोes the platक्रमm need unmapping of sk_buffs?
 *
 *	Returns true अगर the platक्रमm needs sk_buff unmapping.  The compiler
 *	optimizes away unnecessary code अगर this वापसs true.
 */
अटल अंतरभूत पूर्णांक need_skb_unmap(व्योम)
अणु
#अगर_घोषित CONFIG_NEED_DMA_MAP_STATE
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 *	unmap_skb - unmap a packet मुख्य body and its page fragments
 *	@skb: the packet
 *	@q: the Tx queue containing Tx descriptors क्रम the packet
 *	@cidx: index of Tx descriptor
 *	@pdev: the PCI device
 *
 *	Unmap the मुख्य body of an sk_buff and its page fragments, अगर any.
 *	Because of the fairly complicated काष्ठाure of our SGLs and the desire
 *	to conserve space क्रम metadata, the inक्रमmation necessary to unmap an
 *	sk_buff is spपढ़ो across the sk_buff itself (buffer lengths), the HW Tx
 *	descriptors (the physical addresses of the various data buffers), and
 *	the SW descriptor state (assorted indices).  The send functions
 *	initialize the indices क्रम the first packet descriptor so we can unmap
 *	the buffers held in the first Tx descriptor here, and we have enough
 *	inक्रमmation at this poपूर्णांक to set the state क्रम the next Tx descriptor.
 *
 *	Note that it is possible to clean up the first descriptor of a packet
 *	beक्रमe the send routines have written the next descriptors, but this
 *	race करोes not cause any problem.  We just end up writing the unmapping
 *	info क्रम the descriptor first.
 */
अटल अंतरभूत व्योम unmap_skb(काष्ठा sk_buff *skb, काष्ठा sge_txq *q,
			     अचिन्हित पूर्णांक cidx, काष्ठा pci_dev *pdev)
अणु
	स्थिर काष्ठा sg_ent *sgp;
	काष्ठा tx_sw_desc *d = &q->sdesc[cidx];
	पूर्णांक nfrags, frag_idx, curflit, j = d->addr_idx;

	sgp = (काष्ठा sg_ent *)&q->desc[cidx].flit[d->sflit];
	frag_idx = d->fragidx;

	अगर (frag_idx == 0 && skb_headlen(skb)) अणु
		pci_unmap_single(pdev, be64_to_cpu(sgp->addr[0]),
				 skb_headlen(skb), PCI_DMA_TODEVICE);
		j = 1;
	पूर्ण

	curflit = d->sflit + 1 + j;
	nfrags = skb_shinfo(skb)->nr_frags;

	जबतक (frag_idx < nfrags && curflit < WR_FLITS) अणु
		pci_unmap_page(pdev, be64_to_cpu(sgp->addr[j]),
			       skb_frag_size(&skb_shinfo(skb)->frags[frag_idx]),
			       PCI_DMA_TODEVICE);
		j ^= 1;
		अगर (j == 0) अणु
			sgp++;
			curflit++;
		पूर्ण
		curflit++;
		frag_idx++;
	पूर्ण

	अगर (frag_idx < nfrags) अणु   /* SGL जारीs पूर्णांकo next Tx descriptor */
		d = cidx + 1 == q->size ? q->sdesc : d + 1;
		d->fragidx = frag_idx;
		d->addr_idx = j;
		d->sflit = curflit - WR_FLITS - j; /* sflit can be -1 */
	पूर्ण
पूर्ण

/**
 *	मुक्त_tx_desc - reclaims Tx descriptors and their buffers
 *	@adapter: the adapter
 *	@q: the Tx queue to reclaim descriptors from
 *	@n: the number of descriptors to reclaim
 *
 *	Reclaims Tx descriptors from an SGE Tx queue and मुक्तs the associated
 *	Tx buffers.  Called with the Tx queue lock held.
 */
अटल व्योम मुक्त_tx_desc(काष्ठा adapter *adapter, काष्ठा sge_txq *q,
			 अचिन्हित पूर्णांक n)
अणु
	काष्ठा tx_sw_desc *d;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक cidx = q->cidx;

	स्थिर पूर्णांक need_unmap = need_skb_unmap() &&
			       q->cntxt_id >= FW_TUNNEL_SGEEC_START;

	d = &q->sdesc[cidx];
	जबतक (n--) अणु
		अगर (d->skb) अणु	/* an SGL is present */
			अगर (need_unmap)
				unmap_skb(d->skb, q, cidx, pdev);
			अगर (d->eop) अणु
				dev_consume_skb_any(d->skb);
				d->skb = शून्य;
			पूर्ण
		पूर्ण
		++d;
		अगर (++cidx == q->size) अणु
			cidx = 0;
			d = q->sdesc;
		पूर्ण
	पूर्ण
	q->cidx = cidx;
पूर्ण

/**
 *	reclaim_completed_tx - reclaims completed Tx descriptors
 *	@adapter: the adapter
 *	@q: the Tx queue to reclaim completed descriptors from
 *	@chunk: maximum number of descriptors to reclaim
 *
 *	Reclaims Tx descriptors that the SGE has indicated it has processed,
 *	and मुक्तs the associated buffers अगर possible.  Called with the Tx
 *	queue's lock held.
 */
अटल अंतरभूत अचिन्हित पूर्णांक reclaim_completed_tx(काष्ठा adapter *adapter,
						काष्ठा sge_txq *q,
						अचिन्हित पूर्णांक chunk)
अणु
	अचिन्हित पूर्णांक reclaim = q->processed - q->cleaned;

	reclaim = min(chunk, reclaim);
	अगर (reclaim) अणु
		मुक्त_tx_desc(adapter, q, reclaim);
		q->cleaned += reclaim;
		q->in_use -= reclaim;
	पूर्ण
	वापस q->processed - q->cleaned;
पूर्ण

/**
 *	should_restart_tx - are there enough resources to restart a Tx queue?
 *	@q: the Tx queue
 *
 *	Checks अगर there are enough descriptors to restart a suspended Tx queue.
 */
अटल अंतरभूत पूर्णांक should_restart_tx(स्थिर काष्ठा sge_txq *q)
अणु
	अचिन्हित पूर्णांक r = q->processed - q->cleaned;

	वापस q->in_use - r < (q->size >> 1);
पूर्ण

अटल व्योम clear_rx_desc(काष्ठा pci_dev *pdev, स्थिर काष्ठा sge_fl *q,
			  काष्ठा rx_sw_desc *d)
अणु
	अगर (q->use_pages && d->pg_chunk.page) अणु
		(*d->pg_chunk.p_cnt)--;
		अगर (!*d->pg_chunk.p_cnt)
			pci_unmap_page(pdev,
				       d->pg_chunk.mapping,
				       q->alloc_size, PCI_DMA_FROMDEVICE);

		put_page(d->pg_chunk.page);
		d->pg_chunk.page = शून्य;
	पूर्ण अन्यथा अणु
		pci_unmap_single(pdev, dma_unmap_addr(d, dma_addr),
				 q->buf_size, PCI_DMA_FROMDEVICE);
		kमुक्त_skb(d->skb);
		d->skb = शून्य;
	पूर्ण
पूर्ण

/**
 *	मुक्त_rx_bufs - मुक्त the Rx buffers on an SGE मुक्त list
 *	@pdev: the PCI device associated with the adapter
 *	@q: the SGE मुक्त list to clean up
 *
 *	Release the buffers on an SGE मुक्त-buffer Rx queue.  HW fetching from
 *	this queue should be stopped beक्रमe calling this function.
 */
अटल व्योम मुक्त_rx_bufs(काष्ठा pci_dev *pdev, काष्ठा sge_fl *q)
अणु
	अचिन्हित पूर्णांक cidx = q->cidx;

	जबतक (q->credits--) अणु
		काष्ठा rx_sw_desc *d = &q->sdesc[cidx];


		clear_rx_desc(pdev, q, d);
		अगर (++cidx == q->size)
			cidx = 0;
	पूर्ण

	अगर (q->pg_chunk.page) अणु
		__मुक्त_pages(q->pg_chunk.page, q->order);
		q->pg_chunk.page = शून्य;
	पूर्ण
पूर्ण

/**
 *	add_one_rx_buf - add a packet buffer to a मुक्त-buffer list
 *	@va:  buffer start VA
 *	@len: the buffer length
 *	@d: the HW Rx descriptor to ग_लिखो
 *	@sd: the SW Rx descriptor to ग_लिखो
 *	@gen: the generation bit value
 *	@pdev: the PCI device associated with the adapter
 *
 *	Add a buffer of the given length to the supplied HW and SW Rx
 *	descriptors.
 */
अटल अंतरभूत पूर्णांक add_one_rx_buf(व्योम *va, अचिन्हित पूर्णांक len,
				 काष्ठा rx_desc *d, काष्ठा rx_sw_desc *sd,
				 अचिन्हित पूर्णांक gen, काष्ठा pci_dev *pdev)
अणु
	dma_addr_t mapping;

	mapping = pci_map_single(pdev, va, len, PCI_DMA_FROMDEVICE);
	अगर (unlikely(pci_dma_mapping_error(pdev, mapping)))
		वापस -ENOMEM;

	dma_unmap_addr_set(sd, dma_addr, mapping);

	d->addr_lo = cpu_to_be32(mapping);
	d->addr_hi = cpu_to_be32((u64) mapping >> 32);
	dma_wmb();
	d->len_gen = cpu_to_be32(V_FLD_GEN1(gen));
	d->gen2 = cpu_to_be32(V_FLD_GEN2(gen));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक add_one_rx_chunk(dma_addr_t mapping, काष्ठा rx_desc *d,
				   अचिन्हित पूर्णांक gen)
अणु
	d->addr_lo = cpu_to_be32(mapping);
	d->addr_hi = cpu_to_be32((u64) mapping >> 32);
	dma_wmb();
	d->len_gen = cpu_to_be32(V_FLD_GEN1(gen));
	d->gen2 = cpu_to_be32(V_FLD_GEN2(gen));
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_pg_chunk(काष्ठा adapter *adapter, काष्ठा sge_fl *q,
			  काष्ठा rx_sw_desc *sd, gfp_t gfp,
			  अचिन्हित पूर्णांक order)
अणु
	अगर (!q->pg_chunk.page) अणु
		dma_addr_t mapping;

		q->pg_chunk.page = alloc_pages(gfp, order);
		अगर (unlikely(!q->pg_chunk.page))
			वापस -ENOMEM;
		q->pg_chunk.va = page_address(q->pg_chunk.page);
		q->pg_chunk.p_cnt = q->pg_chunk.va + (PAGE_SIZE << order) -
				    SGE_PG_RSVD;
		q->pg_chunk.offset = 0;
		mapping = pci_map_page(adapter->pdev, q->pg_chunk.page,
				       0, q->alloc_size, PCI_DMA_FROMDEVICE);
		अगर (unlikely(pci_dma_mapping_error(adapter->pdev, mapping))) अणु
			__मुक्त_pages(q->pg_chunk.page, order);
			q->pg_chunk.page = शून्य;
			वापस -EIO;
		पूर्ण
		q->pg_chunk.mapping = mapping;
	पूर्ण
	sd->pg_chunk = q->pg_chunk;

	prefetch(sd->pg_chunk.p_cnt);

	q->pg_chunk.offset += q->buf_size;
	अगर (q->pg_chunk.offset == (PAGE_SIZE << order))
		q->pg_chunk.page = शून्य;
	अन्यथा अणु
		q->pg_chunk.va += q->buf_size;
		get_page(q->pg_chunk.page);
	पूर्ण

	अगर (sd->pg_chunk.offset == 0)
		*sd->pg_chunk.p_cnt = 1;
	अन्यथा
		*sd->pg_chunk.p_cnt += 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ring_fl_db(काष्ठा adapter *adap, काष्ठा sge_fl *q)
अणु
	अगर (q->pend_cred >= q->credits / 4) अणु
		q->pend_cred = 0;
		wmb();
		t3_ग_लिखो_reg(adap, A_SG_KDOORBELL, V_EGRCNTX(q->cntxt_id));
	पूर्ण
पूर्ण

/**
 *	refill_fl - refill an SGE मुक्त-buffer list
 *	@adap: the adapter
 *	@q: the मुक्त-list to refill
 *	@n: the number of new buffers to allocate
 *	@gfp: the gfp flags क्रम allocating new buffers
 *
 *	(Re)populate an SGE मुक्त-buffer list with up to @n new packet buffers,
 *	allocated with the supplied gfp flags.  The caller must assure that
 *	@n करोes not exceed the queue's capacity.
 */
अटल पूर्णांक refill_fl(काष्ठा adapter *adap, काष्ठा sge_fl *q, पूर्णांक n, gfp_t gfp)
अणु
	काष्ठा rx_sw_desc *sd = &q->sdesc[q->pidx];
	काष्ठा rx_desc *d = &q->desc[q->pidx];
	अचिन्हित पूर्णांक count = 0;

	जबतक (n--) अणु
		dma_addr_t mapping;
		पूर्णांक err;

		अगर (q->use_pages) अणु
			अगर (unlikely(alloc_pg_chunk(adap, q, sd, gfp,
						    q->order))) अणु
nomem:				q->alloc_failed++;
				अवरोध;
			पूर्ण
			mapping = sd->pg_chunk.mapping + sd->pg_chunk.offset;
			dma_unmap_addr_set(sd, dma_addr, mapping);

			add_one_rx_chunk(mapping, d, q->gen);
			pci_dma_sync_single_क्रम_device(adap->pdev, mapping,
						q->buf_size - SGE_PG_RSVD,
						PCI_DMA_FROMDEVICE);
		पूर्ण अन्यथा अणु
			व्योम *buf_start;

			काष्ठा sk_buff *skb = alloc_skb(q->buf_size, gfp);
			अगर (!skb)
				जाओ nomem;

			sd->skb = skb;
			buf_start = skb->data;
			err = add_one_rx_buf(buf_start, q->buf_size, d, sd,
					     q->gen, adap->pdev);
			अगर (unlikely(err)) अणु
				clear_rx_desc(adap->pdev, q, sd);
				अवरोध;
			पूर्ण
		पूर्ण

		d++;
		sd++;
		अगर (++q->pidx == q->size) अणु
			q->pidx = 0;
			q->gen ^= 1;
			sd = q->sdesc;
			d = q->desc;
		पूर्ण
		count++;
	पूर्ण

	q->credits += count;
	q->pend_cred += count;
	ring_fl_db(adap, q);

	वापस count;
पूर्ण

अटल अंतरभूत व्योम __refill_fl(काष्ठा adapter *adap, काष्ठा sge_fl *fl)
अणु
	refill_fl(adap, fl, min(MAX_RX_REFILL, fl->size - fl->credits),
		  GFP_ATOMIC | __GFP_COMP);
पूर्ण

/**
 *	recycle_rx_buf - recycle a receive buffer
 *	@adap: the adapter
 *	@q: the SGE मुक्त list
 *	@idx: index of buffer to recycle
 *
 *	Recycles the specअगरied buffer on the given मुक्त list by adding it at
 *	the next available slot on the list.
 */
अटल व्योम recycle_rx_buf(काष्ठा adapter *adap, काष्ठा sge_fl *q,
			   अचिन्हित पूर्णांक idx)
अणु
	काष्ठा rx_desc *from = &q->desc[idx];
	काष्ठा rx_desc *to = &q->desc[q->pidx];

	q->sdesc[q->pidx] = q->sdesc[idx];
	to->addr_lo = from->addr_lo;	/* alपढ़ोy big endian */
	to->addr_hi = from->addr_hi;	/* likewise */
	dma_wmb();
	to->len_gen = cpu_to_be32(V_FLD_GEN1(q->gen));
	to->gen2 = cpu_to_be32(V_FLD_GEN2(q->gen));

	अगर (++q->pidx == q->size) अणु
		q->pidx = 0;
		q->gen ^= 1;
	पूर्ण

	q->credits++;
	q->pend_cred++;
	ring_fl_db(adap, q);
पूर्ण

/**
 *	alloc_ring - allocate resources क्रम an SGE descriptor ring
 *	@pdev: the PCI device
 *	@nelem: the number of descriptors
 *	@elem_size: the size of each descriptor
 *	@sw_size: the size of the SW state associated with each ring element
 *	@phys: the physical address of the allocated ring
 *	@metadata: address of the array holding the SW state क्रम the ring
 *
 *	Allocates resources क्रम an SGE descriptor ring, such as Tx queues,
 *	मुक्त buffer lists, or response queues.  Each SGE ring requires
 *	space क्रम its HW descriptors plus, optionally, space क्रम the SW state
 *	associated with each HW entry (the metadata).  The function वापसs
 *	three values: the भव address क्रम the HW ring (the वापस value
 *	of the function), the physical address of the HW ring, and the address
 *	of the SW ring.
 */
अटल व्योम *alloc_ring(काष्ठा pci_dev *pdev, माप_प्रकार nelem, माप_प्रकार elem_size,
			माप_प्रकार sw_size, dma_addr_t * phys, व्योम *metadata)
अणु
	माप_प्रकार len = nelem * elem_size;
	व्योम *s = शून्य;
	व्योम *p = dma_alloc_coherent(&pdev->dev, len, phys, GFP_KERNEL);

	अगर (!p)
		वापस शून्य;
	अगर (sw_size && metadata) अणु
		s = kसुस्मृति(nelem, sw_size, GFP_KERNEL);

		अगर (!s) अणु
			dma_मुक्त_coherent(&pdev->dev, len, p, *phys);
			वापस शून्य;
		पूर्ण
		*(व्योम **)metadata = s;
	पूर्ण
	वापस p;
पूर्ण

/**
 *	t3_reset_qset - reset a sge qset
 *	@q: the queue set
 *
 *	Reset the qset काष्ठाure.
 *	the NAPI काष्ठाure is preserved in the event of
 *	the qset's reincarnation, क्रम example during EEH recovery.
 */
अटल व्योम t3_reset_qset(काष्ठा sge_qset *q)
अणु
	अगर (q->adap &&
	    !(q->adap->flags & NAPI_INIT)) अणु
		स_रखो(q, 0, माप(*q));
		वापस;
	पूर्ण

	q->adap = शून्य;
	स_रखो(&q->rspq, 0, माप(q->rspq));
	स_रखो(q->fl, 0, माप(काष्ठा sge_fl) * SGE_RXQ_PER_SET);
	स_रखो(q->txq, 0, माप(काष्ठा sge_txq) * SGE_TXQ_PER_SET);
	q->txq_stopped = 0;
	q->tx_reclaim_समयr.function = शून्य; /* क्रम t3_stop_sge_समयrs() */
	q->rx_reclaim_समयr.function = शून्य;
	q->nomem = 0;
	napi_मुक्त_frags(&q->napi);
पूर्ण


/**
 *	मुक्त_qset - मुक्त the resources of an SGE queue set
 *	@adapter: the adapter owning the queue set
 *	@q: the queue set
 *
 *	Release the HW and SW resources associated with an SGE queue set, such
 *	as HW contexts, packet buffers, and descriptor rings.  Traffic to the
 *	queue set must be quiesced prior to calling this.
 */
अटल व्योम t3_मुक्त_qset(काष्ठा adapter *adapter, काष्ठा sge_qset *q)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = adapter->pdev;

	क्रम (i = 0; i < SGE_RXQ_PER_SET; ++i)
		अगर (q->fl[i].desc) अणु
			spin_lock_irq(&adapter->sge.reg_lock);
			t3_sge_disable_fl(adapter, q->fl[i].cntxt_id);
			spin_unlock_irq(&adapter->sge.reg_lock);
			मुक्त_rx_bufs(pdev, &q->fl[i]);
			kमुक्त(q->fl[i].sdesc);
			dma_मुक्त_coherent(&pdev->dev,
					  q->fl[i].size *
					  माप(काष्ठा rx_desc), q->fl[i].desc,
					  q->fl[i].phys_addr);
		पूर्ण

	क्रम (i = 0; i < SGE_TXQ_PER_SET; ++i)
		अगर (q->txq[i].desc) अणु
			spin_lock_irq(&adapter->sge.reg_lock);
			t3_sge_enable_ecntxt(adapter, q->txq[i].cntxt_id, 0);
			spin_unlock_irq(&adapter->sge.reg_lock);
			अगर (q->txq[i].sdesc) अणु
				मुक्त_tx_desc(adapter, &q->txq[i],
					     q->txq[i].in_use);
				kमुक्त(q->txq[i].sdesc);
			पूर्ण
			dma_मुक्त_coherent(&pdev->dev,
					  q->txq[i].size *
					  माप(काष्ठा tx_desc),
					  q->txq[i].desc, q->txq[i].phys_addr);
			__skb_queue_purge(&q->txq[i].sendq);
		पूर्ण

	अगर (q->rspq.desc) अणु
		spin_lock_irq(&adapter->sge.reg_lock);
		t3_sge_disable_rspcntxt(adapter, q->rspq.cntxt_id);
		spin_unlock_irq(&adapter->sge.reg_lock);
		dma_मुक्त_coherent(&pdev->dev,
				  q->rspq.size * माप(काष्ठा rsp_desc),
				  q->rspq.desc, q->rspq.phys_addr);
	पूर्ण

	t3_reset_qset(q);
पूर्ण

/**
 *	init_qset_cntxt - initialize an SGE queue set context info
 *	@qs: the queue set
 *	@id: the queue set id
 *
 *	Initializes the TIDs and context ids क्रम the queues of a queue set.
 */
अटल व्योम init_qset_cntxt(काष्ठा sge_qset *qs, अचिन्हित पूर्णांक id)
अणु
	qs->rspq.cntxt_id = id;
	qs->fl[0].cntxt_id = 2 * id;
	qs->fl[1].cntxt_id = 2 * id + 1;
	qs->txq[TXQ_ETH].cntxt_id = FW_TUNNEL_SGEEC_START + id;
	qs->txq[TXQ_ETH].token = FW_TUNNEL_TID_START + id;
	qs->txq[TXQ_OFLD].cntxt_id = FW_OFLD_SGEEC_START + id;
	qs->txq[TXQ_CTRL].cntxt_id = FW_CTRL_SGEEC_START + id;
	qs->txq[TXQ_CTRL].token = FW_CTRL_TID_START + id;
पूर्ण

/**
 *	sgl_len - calculates the size of an SGL of the given capacity
 *	@n: the number of SGL entries
 *
 *	Calculates the number of flits needed क्रम a scatter/gather list that
 *	can hold the given number of entries.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sgl_len(अचिन्हित पूर्णांक n)
अणु
	/* alternatively: 3 * (n / 2) + 2 * (n & 1) */
	वापस (3 * n) / 2 + (n & 1);
पूर्ण

/**
 *	flits_to_desc - वापसs the num of Tx descriptors क्रम the given flits
 *	@n: the number of flits
 *
 *	Calculates the number of Tx descriptors needed क्रम the supplied number
 *	of flits.
 */
अटल अंतरभूत अचिन्हित पूर्णांक flits_to_desc(अचिन्हित पूर्णांक n)
अणु
	BUG_ON(n >= ARRAY_SIZE(flit_desc_map));
	वापस flit_desc_map[n];
पूर्ण

/**
 *	get_packet - वापस the next ingress packet buffer from a मुक्त list
 *	@adap: the adapter that received the packet
 *	@fl: the SGE मुक्त list holding the packet
 *	@len: the packet length including any SGE padding
 *	@drop_thres: # of reमुख्यing buffers beक्रमe we start dropping packets
 *
 *	Get the next packet from a मुक्त list and complete setup of the
 *	sk_buff.  If the packet is small we make a copy and recycle the
 *	original buffer, otherwise we use the original buffer itself.  If a
 *	positive drop threshold is supplied packets are dropped and their
 *	buffers recycled अगर (a) the number of reमुख्यing buffers is under the
 *	threshold and the packet is too big to copy, or (b) the packet should
 *	be copied but there is no memory क्रम the copy.
 */
अटल काष्ठा sk_buff *get_packet(काष्ठा adapter *adap, काष्ठा sge_fl *fl,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक drop_thres)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rx_sw_desc *sd = &fl->sdesc[fl->cidx];

	prefetch(sd->skb->data);
	fl->credits--;

	अगर (len <= SGE_RX_COPY_THRES) अणु
		skb = alloc_skb(len, GFP_ATOMIC);
		अगर (likely(skb != शून्य)) अणु
			__skb_put(skb, len);
			pci_dma_sync_single_क्रम_cpu(adap->pdev,
					    dma_unmap_addr(sd, dma_addr), len,
					    PCI_DMA_FROMDEVICE);
			स_नकल(skb->data, sd->skb->data, len);
			pci_dma_sync_single_क्रम_device(adap->pdev,
					    dma_unmap_addr(sd, dma_addr), len,
					    PCI_DMA_FROMDEVICE);
		पूर्ण अन्यथा अगर (!drop_thres)
			जाओ use_orig_buf;
recycle:
		recycle_rx_buf(adap, fl, fl->cidx);
		वापस skb;
	पूर्ण

	अगर (unlikely(fl->credits < drop_thres) &&
	    refill_fl(adap, fl, min(MAX_RX_REFILL, fl->size - fl->credits - 1),
		      GFP_ATOMIC | __GFP_COMP) == 0)
		जाओ recycle;

use_orig_buf:
	pci_unmap_single(adap->pdev, dma_unmap_addr(sd, dma_addr),
			 fl->buf_size, PCI_DMA_FROMDEVICE);
	skb = sd->skb;
	skb_put(skb, len);
	__refill_fl(adap, fl);
	वापस skb;
पूर्ण

/**
 *	get_packet_pg - वापस the next ingress packet buffer from a मुक्त list
 *	@adap: the adapter that received the packet
 *	@fl: the SGE मुक्त list holding the packet
 *	@q: the queue
 *	@len: the packet length including any SGE padding
 *	@drop_thres: # of reमुख्यing buffers beक्रमe we start dropping packets
 *
 *	Get the next packet from a मुक्त list populated with page chunks.
 *	If the packet is small we make a copy and recycle the original buffer,
 *	otherwise we attach the original buffer as a page fragment to a fresh
 *	sk_buff.  If a positive drop threshold is supplied packets are dropped
 *	and their buffers recycled अगर (a) the number of reमुख्यing buffers is
 *	under the threshold and the packet is too big to copy, or (b) there's
 *	no प्रणाली memory.
 *
 * 	Note: this function is similar to @get_packet but deals with Rx buffers
 * 	that are page chunks rather than sk_buffs.
 */
अटल काष्ठा sk_buff *get_packet_pg(काष्ठा adapter *adap, काष्ठा sge_fl *fl,
				     काष्ठा sge_rspq *q, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक drop_thres)
अणु
	काष्ठा sk_buff *newskb, *skb;
	काष्ठा rx_sw_desc *sd = &fl->sdesc[fl->cidx];

	dma_addr_t dma_addr = dma_unmap_addr(sd, dma_addr);

	newskb = skb = q->pg_skb;
	अगर (!skb && (len <= SGE_RX_COPY_THRES)) अणु
		newskb = alloc_skb(len, GFP_ATOMIC);
		अगर (likely(newskb != शून्य)) अणु
			__skb_put(newskb, len);
			pci_dma_sync_single_क्रम_cpu(adap->pdev, dma_addr, len,
					    PCI_DMA_FROMDEVICE);
			स_नकल(newskb->data, sd->pg_chunk.va, len);
			pci_dma_sync_single_क्रम_device(adap->pdev, dma_addr,
						       len,
						       PCI_DMA_FROMDEVICE);
		पूर्ण अन्यथा अगर (!drop_thres)
			वापस शून्य;
recycle:
		fl->credits--;
		recycle_rx_buf(adap, fl, fl->cidx);
		q->rx_recycle_buf++;
		वापस newskb;
	पूर्ण

	अगर (unlikely(q->rx_recycle_buf || (!skb && fl->credits <= drop_thres)))
		जाओ recycle;

	prefetch(sd->pg_chunk.p_cnt);

	अगर (!skb)
		newskb = alloc_skb(SGE_RX_PULL_LEN, GFP_ATOMIC);

	अगर (unlikely(!newskb)) अणु
		अगर (!drop_thres)
			वापस शून्य;
		जाओ recycle;
	पूर्ण

	pci_dma_sync_single_क्रम_cpu(adap->pdev, dma_addr, len,
				    PCI_DMA_FROMDEVICE);
	(*sd->pg_chunk.p_cnt)--;
	अगर (!*sd->pg_chunk.p_cnt && sd->pg_chunk.page != fl->pg_chunk.page)
		pci_unmap_page(adap->pdev,
			       sd->pg_chunk.mapping,
			       fl->alloc_size,
			       PCI_DMA_FROMDEVICE);
	अगर (!skb) अणु
		__skb_put(newskb, SGE_RX_PULL_LEN);
		स_नकल(newskb->data, sd->pg_chunk.va, SGE_RX_PULL_LEN);
		skb_fill_page_desc(newskb, 0, sd->pg_chunk.page,
				   sd->pg_chunk.offset + SGE_RX_PULL_LEN,
				   len - SGE_RX_PULL_LEN);
		newskb->len = len;
		newskb->data_len = len - SGE_RX_PULL_LEN;
		newskb->truesize += newskb->data_len;
	पूर्ण अन्यथा अणु
		skb_fill_page_desc(newskb, skb_shinfo(newskb)->nr_frags,
				   sd->pg_chunk.page,
				   sd->pg_chunk.offset, len);
		newskb->len += len;
		newskb->data_len += len;
		newskb->truesize += len;
	पूर्ण

	fl->credits--;
	/*
	 * We करो not refill FLs here, we let the caller करो it to overlap a
	 * prefetch.
	 */
	वापस newskb;
पूर्ण

/**
 *	get_imm_packet - वापस the next ingress packet buffer from a response
 *	@resp: the response descriptor containing the packet data
 *
 *	Return a packet containing the immediate data of the given response.
 */
अटल अंतरभूत काष्ठा sk_buff *get_imm_packet(स्थिर काष्ठा rsp_desc *resp)
अणु
	काष्ठा sk_buff *skb = alloc_skb(IMMED_PKT_SIZE, GFP_ATOMIC);

	अगर (skb) अणु
		__skb_put(skb, IMMED_PKT_SIZE);
		skb_copy_to_linear_data(skb, resp->imm_data, IMMED_PKT_SIZE);
	पूर्ण
	वापस skb;
पूर्ण

/**
 *	calc_tx_descs - calculate the number of Tx descriptors क्रम a packet
 *	@skb: the packet
 *
 * 	Returns the number of Tx descriptors needed क्रम the given Ethernet
 * 	packet.  Ethernet packets require addition of WR and CPL headers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_descs(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits;

	अगर (skb->len <= WR_LEN - माप(काष्ठा cpl_tx_pkt))
		वापस 1;

	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1) + 2;
	अगर (skb_shinfo(skb)->gso_size)
		flits++;
	वापस flits_to_desc(flits);
पूर्ण

/*	map_skb - map a packet मुख्य body and its page fragments
 *	@pdev: the PCI device
 *	@skb: the packet
 *	@addr: placeholder to save the mapped addresses
 *
 *	map the मुख्य body of an sk_buff and its page fragments, अगर any.
 */
अटल पूर्णांक map_skb(काष्ठा pci_dev *pdev, स्थिर काष्ठा sk_buff *skb,
		   dma_addr_t *addr)
अणु
	स्थिर skb_frag_t *fp, *end;
	स्थिर काष्ठा skb_shared_info *si;

	अगर (skb_headlen(skb)) अणु
		*addr = pci_map_single(pdev, skb->data, skb_headlen(skb),
				       PCI_DMA_TODEVICE);
		अगर (pci_dma_mapping_error(pdev, *addr))
			जाओ out_err;
		addr++;
	पूर्ण

	si = skb_shinfo(skb);
	end = &si->frags[si->nr_frags];

	क्रम (fp = si->frags; fp < end; fp++) अणु
		*addr = skb_frag_dma_map(&pdev->dev, fp, 0, skb_frag_size(fp),
					 DMA_TO_DEVICE);
		अगर (pci_dma_mapping_error(pdev, *addr))
			जाओ unwind;
		addr++;
	पूर्ण
	वापस 0;

unwind:
	जबतक (fp-- > si->frags)
		dma_unmap_page(&pdev->dev, *--addr, skb_frag_size(fp),
			       DMA_TO_DEVICE);

	pci_unmap_single(pdev, addr[-1], skb_headlen(skb), PCI_DMA_TODEVICE);
out_err:
	वापस -ENOMEM;
पूर्ण

/**
 *	ग_लिखो_sgl - populate a scatter/gather list क्रम a packet
 *	@skb: the packet
 *	@sgp: the SGL to populate
 *	@start: start address of skb मुख्य body data to include in the SGL
 *	@len: length of skb मुख्य body data to include in the SGL
 *	@addr: the list of the mapped addresses
 *
 *	Copies the scatter/gather list क्रम the buffers that make up a packet
 *	and वापसs the SGL size in 8-byte words.  The caller must size the SGL
 *	appropriately.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ग_लिखो_sgl(स्थिर काष्ठा sk_buff *skb,
				     काष्ठा sg_ent *sgp, अचिन्हित अक्षर *start,
				     अचिन्हित पूर्णांक len, स्थिर dma_addr_t *addr)
अणु
	अचिन्हित पूर्णांक i, j = 0, k = 0, nfrags;

	अगर (len) अणु
		sgp->len[0] = cpu_to_be32(len);
		sgp->addr[j++] = cpu_to_be64(addr[k++]);
	पूर्ण

	nfrags = skb_shinfo(skb)->nr_frags;
	क्रम (i = 0; i < nfrags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		sgp->len[j] = cpu_to_be32(skb_frag_size(frag));
		sgp->addr[j] = cpu_to_be64(addr[k++]);
		j ^= 1;
		अगर (j == 0)
			++sgp;
	पूर्ण
	अगर (j)
		sgp->len[j] = 0;
	वापस ((nfrags + (len != 0)) * 3) / 2 + j;
पूर्ण

/**
 *	check_ring_tx_db - check and potentially ring a Tx queue's करोorbell
 *	@adap: the adapter
 *	@q: the Tx queue
 *
 *	Ring the करोorbel अगर a Tx queue is asleep.  There is a natural race,
 *	where the HW is going to sleep just after we checked, however,
 *	then the पूर्णांकerrupt handler will detect the outstanding TX packet
 *	and ring the करोorbell क्रम us.
 *
 *	When GTS is disabled we unconditionally ring the करोorbell.
 */
अटल अंतरभूत व्योम check_ring_tx_db(काष्ठा adapter *adap, काष्ठा sge_txq *q)
अणु
#अगर USE_GTS
	clear_bit(TXQ_LAST_PKT_DB, &q->flags);
	अगर (test_and_set_bit(TXQ_RUNNING, &q->flags) == 0) अणु
		set_bit(TXQ_LAST_PKT_DB, &q->flags);
		t3_ग_लिखो_reg(adap, A_SG_KDOORBELL,
			     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
	पूर्ण
#अन्यथा
	wmb();			/* ग_लिखो descriptors beक्रमe telling HW */
	t3_ग_लिखो_reg(adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम wr_gen2(काष्ठा tx_desc *d, अचिन्हित पूर्णांक gen)
अणु
#अगर SGE_NUM_GENBITS == 2
	d->flit[TX_DESC_FLITS - 1] = cpu_to_be64(gen);
#पूर्ण_अगर
पूर्ण

/**
 *	ग_लिखो_wr_hdr_sgl - ग_लिखो a WR header and, optionally, SGL
 *	@ndesc: number of Tx descriptors spanned by the SGL
 *	@skb: the packet corresponding to the WR
 *	@d: first Tx descriptor to be written
 *	@pidx: index of above descriptors
 *	@q: the SGE Tx queue
 *	@sgl: the SGL
 *	@flits: number of flits to the start of the SGL in the first descriptor
 *	@sgl_flits: the SGL size in flits
 *	@gen: the Tx descriptor generation
 *	@wr_hi: top 32 bits of WR header based on WR type (big endian)
 *	@wr_lo: low 32 bits of WR header based on WR type (big endian)
 *
 *	Write a work request header and an associated SGL.  If the SGL is
 *	small enough to fit पूर्णांकo one Tx descriptor it has alपढ़ोy been written
 *	and we just need to ग_लिखो the WR header.  Otherwise we distribute the
 *	SGL across the number of descriptors it spans.
 */
अटल व्योम ग_लिखो_wr_hdr_sgl(अचिन्हित पूर्णांक ndesc, काष्ठा sk_buff *skb,
			     काष्ठा tx_desc *d, अचिन्हित पूर्णांक pidx,
			     स्थिर काष्ठा sge_txq *q,
			     स्थिर काष्ठा sg_ent *sgl,
			     अचिन्हित पूर्णांक flits, अचिन्हित पूर्णांक sgl_flits,
			     अचिन्हित पूर्णांक gen, __be32 wr_hi,
			     __be32 wr_lo)
अणु
	काष्ठा work_request_hdr *wrp = (काष्ठा work_request_hdr *)d;
	काष्ठा tx_sw_desc *sd = &q->sdesc[pidx];

	sd->skb = skb;
	अगर (need_skb_unmap()) अणु
		sd->fragidx = 0;
		sd->addr_idx = 0;
		sd->sflit = flits;
	पूर्ण

	अगर (likely(ndesc == 1)) अणु
		sd->eop = 1;
		wrp->wr_hi = htonl(F_WR_SOP | F_WR_EOP | V_WR_DATATYPE(1) |
				   V_WR_SGLSFLT(flits)) | wr_hi;
		dma_wmb();
		wrp->wr_lo = htonl(V_WR_LEN(flits + sgl_flits) |
				   V_WR_GEN(gen)) | wr_lo;
		wr_gen2(d, gen);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ogen = gen;
		स्थिर u64 *fp = (स्थिर u64 *)sgl;
		काष्ठा work_request_hdr *wp = wrp;

		wrp->wr_hi = htonl(F_WR_SOP | V_WR_DATATYPE(1) |
				   V_WR_SGLSFLT(flits)) | wr_hi;

		जबतक (sgl_flits) अणु
			अचिन्हित पूर्णांक avail = WR_FLITS - flits;

			अगर (avail > sgl_flits)
				avail = sgl_flits;
			स_नकल(&d->flit[flits], fp, avail * माप(*fp));
			sgl_flits -= avail;
			ndesc--;
			अगर (!sgl_flits)
				अवरोध;

			fp += avail;
			d++;
			sd->eop = 0;
			sd++;
			अगर (++pidx == q->size) अणु
				pidx = 0;
				gen ^= 1;
				d = q->desc;
				sd = q->sdesc;
			पूर्ण

			sd->skb = skb;
			wrp = (काष्ठा work_request_hdr *)d;
			wrp->wr_hi = htonl(V_WR_DATATYPE(1) |
					   V_WR_SGLSFLT(1)) | wr_hi;
			wrp->wr_lo = htonl(V_WR_LEN(min(WR_FLITS,
							sgl_flits + 1)) |
					   V_WR_GEN(gen)) | wr_lo;
			wr_gen2(d, gen);
			flits = 1;
		पूर्ण
		sd->eop = 1;
		wrp->wr_hi |= htonl(F_WR_EOP);
		dma_wmb();
		wp->wr_lo = htonl(V_WR_LEN(WR_FLITS) | V_WR_GEN(ogen)) | wr_lo;
		wr_gen2((काष्ठा tx_desc *)wp, ogen);
		WARN_ON(ndesc != 0);
	पूर्ण
पूर्ण

/**
 *	ग_लिखो_tx_pkt_wr - ग_लिखो a TX_PKT work request
 *	@adap: the adapter
 *	@skb: the packet to send
 *	@pi: the egress पूर्णांकerface
 *	@pidx: index of the first Tx descriptor to ग_लिखो
 *	@gen: the generation value to use
 *	@q: the Tx queue
 *	@ndesc: number of descriptors the packet will occupy
 *	@compl: the value of the COMPL bit to use
 *	@addr: address
 *
 *	Generate a TX_PKT work request to send the supplied packet.
 */
अटल व्योम ग_लिखो_tx_pkt_wr(काष्ठा adapter *adap, काष्ठा sk_buff *skb,
			    स्थिर काष्ठा port_info *pi,
			    अचिन्हित पूर्णांक pidx, अचिन्हित पूर्णांक gen,
			    काष्ठा sge_txq *q, अचिन्हित पूर्णांक ndesc,
			    अचिन्हित पूर्णांक compl, स्थिर dma_addr_t *addr)
अणु
	अचिन्हित पूर्णांक flits, sgl_flits, cntrl, tso_info;
	काष्ठा sg_ent *sgp, sgl[MAX_SKB_FRAGS / 2 + 1];
	काष्ठा tx_desc *d = &q->desc[pidx];
	काष्ठा cpl_tx_pkt *cpl = (काष्ठा cpl_tx_pkt *)d;

	cpl->len = htonl(skb->len);
	cntrl = V_TXPKT_INTF(pi->port_id);

	अगर (skb_vlan_tag_present(skb))
		cntrl |= F_TXPKT_VLAN_VLD | V_TXPKT_VLAN(skb_vlan_tag_get(skb));

	tso_info = V_LSO_MSS(skb_shinfo(skb)->gso_size);
	अगर (tso_info) अणु
		पूर्णांक eth_type;
		काष्ठा cpl_tx_pkt_lso *hdr = (काष्ठा cpl_tx_pkt_lso *)cpl;

		d->flit[2] = 0;
		cntrl |= V_TXPKT_OPCODE(CPL_TX_PKT_LSO);
		hdr->cntrl = htonl(cntrl);
		eth_type = skb_network_offset(skb) == ETH_HLEN ?
		    CPL_ETH_II : CPL_ETH_II_VLAN;
		tso_info |= V_LSO_ETH_TYPE(eth_type) |
		    V_LSO_IPHDR_WORDS(ip_hdr(skb)->ihl) |
		    V_LSO_TCPHDR_WORDS(tcp_hdr(skb)->करोff);
		hdr->lso_info = htonl(tso_info);
		flits = 3;
	पूर्ण अन्यथा अणु
		cntrl |= V_TXPKT_OPCODE(CPL_TX_PKT);
		cntrl |= F_TXPKT_IPCSUM_DIS;	/* SW calculates IP csum */
		cntrl |= V_TXPKT_L4CSUM_DIS(skb->ip_summed != CHECKSUM_PARTIAL);
		cpl->cntrl = htonl(cntrl);

		अगर (skb->len <= WR_LEN - माप(*cpl)) अणु
			q->sdesc[pidx].skb = शून्य;
			अगर (!skb->data_len)
				skb_copy_from_linear_data(skb, &d->flit[2],
							  skb->len);
			अन्यथा
				skb_copy_bits(skb, 0, &d->flit[2], skb->len);

			flits = (skb->len + 7) / 8 + 2;
			cpl->wr.wr_hi = htonl(V_WR_BCNTLFLT(skb->len & 7) |
					      V_WR_OP(FW_WROPCODE_TUNNEL_TX_PKT)
					      | F_WR_SOP | F_WR_EOP | compl);
			dma_wmb();
			cpl->wr.wr_lo = htonl(V_WR_LEN(flits) | V_WR_GEN(gen) |
					      V_WR_TID(q->token));
			wr_gen2(d, gen);
			dev_consume_skb_any(skb);
			वापस;
		पूर्ण

		flits = 2;
	पूर्ण

	sgp = ndesc == 1 ? (काष्ठा sg_ent *)&d->flit[flits] : sgl;
	sgl_flits = ग_लिखो_sgl(skb, sgp, skb->data, skb_headlen(skb), addr);

	ग_लिखो_wr_hdr_sgl(ndesc, skb, d, pidx, q, sgl, flits, sgl_flits, gen,
			 htonl(V_WR_OP(FW_WROPCODE_TUNNEL_TX_PKT) | compl),
			 htonl(V_WR_TID(q->token)));
पूर्ण

अटल अंतरभूत व्योम t3_stop_tx_queue(काष्ठा netdev_queue *txq,
				    काष्ठा sge_qset *qs, काष्ठा sge_txq *q)
अणु
	netअगर_tx_stop_queue(txq);
	set_bit(TXQ_ETH, &qs->txq_stopped);
	q->stops++;
पूर्ण

/**
 *	eth_xmit - add a packet to the Ethernet Tx queue
 *	@skb: the packet
 *	@dev: the egress net device
 *
 *	Add a packet to an SGE Tx queue.  Runs with softirqs disabled.
 */
netdev_tx_t t3_eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक qidx;
	अचिन्हित पूर्णांक ndesc, pidx, credits, gen, compl;
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा netdev_queue *txq;
	काष्ठा sge_qset *qs;
	काष्ठा sge_txq *q;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];

	/*
	 * The chip min packet length is 9 octets but play safe and reject
	 * anything लघुer than an Ethernet header.
	 */
	अगर (unlikely(skb->len < ETH_HLEN)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	qidx = skb_get_queue_mapping(skb);
	qs = &pi->qs[qidx];
	q = &qs->txq[TXQ_ETH];
	txq = netdev_get_tx_queue(dev, qidx);

	reclaim_completed_tx(adap, q, TX_RECLAIM_CHUNK);

	credits = q->size - q->in_use;
	ndesc = calc_tx_descs(skb);

	अगर (unlikely(credits < ndesc)) अणु
		t3_stop_tx_queue(txq, qs, q);
		dev_err(&adap->pdev->dev,
			"%s: Tx ring %u full while queue awake!\n",
			dev->name, q->cntxt_id & 7);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Check अगर ethernet packet can't be sent as immediate data */
	अगर (skb->len > (WR_LEN - माप(काष्ठा cpl_tx_pkt))) अणु
		अगर (unlikely(map_skb(adap->pdev, skb, addr) < 0)) अणु
			dev_kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	q->in_use += ndesc;
	अगर (unlikely(credits - ndesc < q->stop_thres)) अणु
		t3_stop_tx_queue(txq, qs, q);

		अगर (should_restart_tx(q) &&
		    test_and_clear_bit(TXQ_ETH, &qs->txq_stopped)) अणु
			q->restarts++;
			netअगर_tx_start_queue(txq);
		पूर्ण
	पूर्ण

	gen = q->gen;
	q->unacked += ndesc;
	compl = (q->unacked & 8) << (S_WR_COMPL - 3);
	q->unacked &= 7;
	pidx = q->pidx;
	q->pidx += ndesc;
	अगर (q->pidx >= q->size) अणु
		q->pidx -= q->size;
		q->gen ^= 1;
	पूर्ण

	/* update port statistics */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		qs->port_stats[SGE_PSTAT_TX_CSUM]++;
	अगर (skb_shinfo(skb)->gso_size)
		qs->port_stats[SGE_PSTAT_TSO]++;
	अगर (skb_vlan_tag_present(skb))
		qs->port_stats[SGE_PSTAT_VLANINS]++;

	/*
	 * We करो not use Tx completion पूर्णांकerrupts to मुक्त DMAd Tx packets.
	 * This is good क्रम perक्रमmance but means that we rely on new Tx
	 * packets arriving to run the deकाष्ठाors of completed packets,
	 * which खोलो up space in their sockets' send queues.  Someबार
	 * we करो not get such new packets causing Tx to stall.  A single
	 * UDP transmitter is a good example of this situation.  We have
	 * a clean up समयr that periodically reclaims completed packets
	 * but it करोesn't run often enough (nor करो we want it to) to prevent
	 * lengthy stalls.  A solution to this problem is to run the
	 * deकाष्ठाor early, after the packet is queued but beक्रमe it's DMAd.
	 * A cons is that we lie to socket memory accounting, but the amount
	 * of extra memory is reasonable (limited by the number of Tx
	 * descriptors), the packets करो actually get मुक्तd quickly by new
	 * packets almost always, and क्रम protocols like TCP that रुको क्रम
	 * acks to really मुक्त up the data the extra memory is even less.
	 * On the positive side we run the deकाष्ठाors on the sending CPU
	 * rather than on a potentially dअगरferent completing CPU, usually a
	 * good thing.  We also run them without holding our Tx queue lock,
	 * unlike what reclaim_completed_tx() would otherwise करो.
	 *
	 * Run the deकाष्ठाor beक्रमe telling the DMA engine about the packet
	 * to make sure it करोesn't complete and get मुक्तd prematurely.
	 */
	अगर (likely(!skb_shared(skb)))
		skb_orphan(skb);

	ग_लिखो_tx_pkt_wr(adap, skb, pi, pidx, gen, q, ndesc, compl, addr);
	check_ring_tx_db(adap, q);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 *	ग_लिखो_imm - ग_लिखो a packet पूर्णांकo a Tx descriptor as immediate data
 *	@d: the Tx descriptor to ग_लिखो
 *	@skb: the packet
 *	@len: the length of packet data to ग_लिखो as immediate data
 *	@gen: the generation bit value to ग_लिखो
 *
 *	Writes a packet as immediate data पूर्णांकo a Tx descriptor.  The packet
 *	contains a work request at its beginning.  We must ग_लिखो the packet
 *	carefully so the SGE करोesn't read it accidentally before it's written
 *	in its entirety.
 */
अटल अंतरभूत व्योम ग_लिखो_imm(काष्ठा tx_desc *d, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक gen)
अणु
	काष्ठा work_request_hdr *from = (काष्ठा work_request_hdr *)skb->data;
	काष्ठा work_request_hdr *to = (काष्ठा work_request_hdr *)d;

	अगर (likely(!skb->data_len))
		स_नकल(&to[1], &from[1], len - माप(*from));
	अन्यथा
		skb_copy_bits(skb, माप(*from), &to[1], len - माप(*from));

	to->wr_hi = from->wr_hi | htonl(F_WR_SOP | F_WR_EOP |
					V_WR_BCNTLFLT(len & 7));
	dma_wmb();
	to->wr_lo = from->wr_lo | htonl(V_WR_GEN(gen) |
					V_WR_LEN((len + 7) / 8));
	wr_gen2(d, gen);
	kमुक्त_skb(skb);
पूर्ण

/**
 *	check_desc_avail - check descriptor availability on a send queue
 *	@adap: the adapter
 *	@q: the send queue
 *	@skb: the packet needing the descriptors
 *	@ndesc: the number of Tx descriptors needed
 *	@qid: the Tx queue number in its queue set (TXQ_OFLD or TXQ_CTRL)
 *
 *	Checks अगर the requested number of Tx descriptors is available on an
 *	SGE send queue.  If the queue is alपढ़ोy suspended or not enough
 *	descriptors are available the packet is queued क्रम later transmission.
 *	Must be called with the Tx queue locked.
 *
 *	Returns 0 अगर enough descriptors are available, 1 अगर there aren't
 *	enough descriptors and the packet has been queued, and 2 अगर the caller
 *	needs to retry because there weren't enough descriptors at the
 *	beginning of the call but some मुक्तd up in the mean समय.
 */
अटल अंतरभूत पूर्णांक check_desc_avail(काष्ठा adapter *adap, काष्ठा sge_txq *q,
				   काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ndesc,
				   अचिन्हित पूर्णांक qid)
अणु
	अगर (unlikely(!skb_queue_empty(&q->sendq))) अणु
	      addq_निकास:__skb_queue_tail(&q->sendq, skb);
		वापस 1;
	पूर्ण
	अगर (unlikely(q->size - q->in_use < ndesc)) अणु
		काष्ठा sge_qset *qs = txq_to_qset(q, qid);

		set_bit(qid, &qs->txq_stopped);
		smp_mb__after_atomic();

		अगर (should_restart_tx(q) &&
		    test_and_clear_bit(qid, &qs->txq_stopped))
			वापस 2;

		q->stops++;
		जाओ addq_निकास;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	reclaim_completed_tx_imm - reclaim completed control-queue Tx descs
 *	@q: the SGE control Tx queue
 *
 *	This is a variant of reclaim_completed_tx() that is used क्रम Tx queues
 *	that send only immediate data (presently just the control queues) and
 *	thus करो not have any sk_buffs to release.
 */
अटल अंतरभूत व्योम reclaim_completed_tx_imm(काष्ठा sge_txq *q)
अणु
	अचिन्हित पूर्णांक reclaim = q->processed - q->cleaned;

	q->in_use -= reclaim;
	q->cleaned += reclaim;
पूर्ण

अटल अंतरभूत पूर्णांक immediate(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len <= WR_LEN;
पूर्ण

/**
 *	ctrl_xmit - send a packet through an SGE control Tx queue
 *	@adap: the adapter
 *	@q: the control queue
 *	@skb: the packet
 *
 *	Send a packet through an SGE control Tx queue.  Packets sent through
 *	a control queue must fit entirely as immediate data in a single Tx
 *	descriptor and have no page fragments.
 */
अटल पूर्णांक ctrl_xmit(काष्ठा adapter *adap, काष्ठा sge_txq *q,
		     काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा work_request_hdr *wrp = (काष्ठा work_request_hdr *)skb->data;

	अगर (unlikely(!immediate(skb))) अणु
		WARN_ON(1);
		dev_kमुक्त_skb(skb);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	wrp->wr_hi |= htonl(F_WR_SOP | F_WR_EOP);
	wrp->wr_lo = htonl(V_WR_TID(q->token));

	spin_lock(&q->lock);
      again:reclaim_completed_tx_imm(q);

	ret = check_desc_avail(adap, q, skb, 1, TXQ_CTRL);
	अगर (unlikely(ret)) अणु
		अगर (ret == 1) अणु
			spin_unlock(&q->lock);
			वापस NET_XMIT_CN;
		पूर्ण
		जाओ again;
	पूर्ण

	ग_लिखो_imm(&q->desc[q->pidx], skb, skb->len, q->gen);

	q->in_use++;
	अगर (++q->pidx >= q->size) अणु
		q->pidx = 0;
		q->gen ^= 1;
	पूर्ण
	spin_unlock(&q->lock);
	wmb();
	t3_ग_लिखो_reg(adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
	वापस NET_XMIT_SUCCESS;
पूर्ण

/**
 *	restart_ctrlq - restart a suspended control queue
 *	@t: poपूर्णांकer to the tasklet associated with this handler
 *
 *	Resumes transmission on a suspended Tx control queue.
 */
अटल व्योम restart_ctrlq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sge_qset *qs = from_tasklet(qs, t, txq[TXQ_CTRL].qresume_tsk);
	काष्ठा sge_txq *q = &qs->txq[TXQ_CTRL];

	spin_lock(&q->lock);
      again:reclaim_completed_tx_imm(q);

	जबतक (q->in_use < q->size &&
	       (skb = __skb_dequeue(&q->sendq)) != शून्य) अणु

		ग_लिखो_imm(&q->desc[q->pidx], skb, skb->len, q->gen);

		अगर (++q->pidx >= q->size) अणु
			q->pidx = 0;
			q->gen ^= 1;
		पूर्ण
		q->in_use++;
	पूर्ण

	अगर (!skb_queue_empty(&q->sendq)) अणु
		set_bit(TXQ_CTRL, &qs->txq_stopped);
		smp_mb__after_atomic();

		अगर (should_restart_tx(q) &&
		    test_and_clear_bit(TXQ_CTRL, &qs->txq_stopped))
			जाओ again;
		q->stops++;
	पूर्ण

	spin_unlock(&q->lock);
	wmb();
	t3_ग_लिखो_reg(qs->adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
पूर्ण

/*
 * Send a management message through control queue 0
 */
पूर्णांक t3_mgmt_tx(काष्ठा adapter *adap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	local_bh_disable();
	ret = ctrl_xmit(adap, &adap->sge.qs[0].txq[TXQ_CTRL], skb);
	local_bh_enable();

	वापस ret;
पूर्ण

/**
 *	deferred_unmap_deकाष्ठाor - unmap a packet when it is मुक्तd
 *	@skb: the packet
 *
 *	This is the packet deकाष्ठाor used क्रम Tx packets that need to reमुख्य
 *	mapped until they are मुक्तd rather than until their Tx descriptors are
 *	मुक्तd.
 */
अटल व्योम deferred_unmap_deकाष्ठाor(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;
	स्थिर dma_addr_t *p;
	स्थिर काष्ठा skb_shared_info *si;
	स्थिर काष्ठा deferred_unmap_info *dui;

	dui = (काष्ठा deferred_unmap_info *)skb->head;
	p = dui->addr;

	अगर (skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb))
		pci_unmap_single(dui->pdev, *p++, skb_tail_poपूर्णांकer(skb) -
				 skb_transport_header(skb), PCI_DMA_TODEVICE);

	si = skb_shinfo(skb);
	क्रम (i = 0; i < si->nr_frags; i++)
		pci_unmap_page(dui->pdev, *p++, skb_frag_size(&si->frags[i]),
			       PCI_DMA_TODEVICE);
पूर्ण

अटल व्योम setup_deferred_unmapping(काष्ठा sk_buff *skb, काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा sg_ent *sgl, पूर्णांक sgl_flits)
अणु
	dma_addr_t *p;
	काष्ठा deferred_unmap_info *dui;

	dui = (काष्ठा deferred_unmap_info *)skb->head;
	dui->pdev = pdev;
	क्रम (p = dui->addr; sgl_flits >= 3; sgl++, sgl_flits -= 3) अणु
		*p++ = be64_to_cpu(sgl->addr[0]);
		*p++ = be64_to_cpu(sgl->addr[1]);
	पूर्ण
	अगर (sgl_flits)
		*p = be64_to_cpu(sgl->addr[0]);
पूर्ण

/**
 *	ग_लिखो_ofld_wr - ग_लिखो an offload work request
 *	@adap: the adapter
 *	@skb: the packet to send
 *	@q: the Tx queue
 *	@pidx: index of the first Tx descriptor to ग_लिखो
 *	@gen: the generation value to use
 *	@ndesc: number of descriptors the packet will occupy
 *	@addr: the address
 *
 *	Write an offload work request to send the supplied packet.  The packet
 *	data alपढ़ोy carry the work request with most fields populated.
 */
अटल व्योम ग_लिखो_ofld_wr(काष्ठा adapter *adap, काष्ठा sk_buff *skb,
			  काष्ठा sge_txq *q, अचिन्हित पूर्णांक pidx,
			  अचिन्हित पूर्णांक gen, अचिन्हित पूर्णांक ndesc,
			  स्थिर dma_addr_t *addr)
अणु
	अचिन्हित पूर्णांक sgl_flits, flits;
	काष्ठा work_request_hdr *from;
	काष्ठा sg_ent *sgp, sgl[MAX_SKB_FRAGS / 2 + 1];
	काष्ठा tx_desc *d = &q->desc[pidx];

	अगर (immediate(skb)) अणु
		q->sdesc[pidx].skb = शून्य;
		ग_लिखो_imm(d, skb, skb->len, gen);
		वापस;
	पूर्ण

	/* Only TX_DATA builds SGLs */

	from = (काष्ठा work_request_hdr *)skb->data;
	स_नकल(&d->flit[1], &from[1],
	       skb_transport_offset(skb) - माप(*from));

	flits = skb_transport_offset(skb) / 8;
	sgp = ndesc == 1 ? (काष्ठा sg_ent *)&d->flit[flits] : sgl;
	sgl_flits = ग_लिखो_sgl(skb, sgp, skb_transport_header(skb),
			      skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb),
			      addr);
	अगर (need_skb_unmap()) अणु
		setup_deferred_unmapping(skb, adap->pdev, sgp, sgl_flits);
		skb->deकाष्ठाor = deferred_unmap_deकाष्ठाor;
	पूर्ण

	ग_लिखो_wr_hdr_sgl(ndesc, skb, d, pidx, q, sgl, flits, sgl_flits,
			 gen, from->wr_hi, from->wr_lo);
पूर्ण

/**
 *	calc_tx_descs_ofld - calculate # of Tx descriptors क्रम an offload packet
 *	@skb: the packet
 *
 * 	Returns the number of Tx descriptors needed क्रम the given offload
 * 	packet.  These packets are alपढ़ोy fully स्थिरructed.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_descs_ofld(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits, cnt;

	अगर (skb->len <= WR_LEN)
		वापस 1;	/* packet fits as immediate data */

	flits = skb_transport_offset(skb) / 8;	/* headers */
	cnt = skb_shinfo(skb)->nr_frags;
	अगर (skb_tail_poपूर्णांकer(skb) != skb_transport_header(skb))
		cnt++;
	वापस flits_to_desc(flits + sgl_len(cnt));
पूर्ण

/**
 *	ofld_xmit - send a packet through an offload queue
 *	@adap: the adapter
 *	@q: the Tx offload queue
 *	@skb: the packet
 *
 *	Send an offload packet through an SGE offload queue.
 */
अटल पूर्णांक ofld_xmit(काष्ठा adapter *adap, काष्ठा sge_txq *q,
		     काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ndesc = calc_tx_descs_ofld(skb), pidx, gen;

	spin_lock(&q->lock);
again:	reclaim_completed_tx(adap, q, TX_RECLAIM_CHUNK);

	ret = check_desc_avail(adap, q, skb, ndesc, TXQ_OFLD);
	अगर (unlikely(ret)) अणु
		अगर (ret == 1) अणु
			skb->priority = ndesc;	/* save क्रम restart */
			spin_unlock(&q->lock);
			वापस NET_XMIT_CN;
		पूर्ण
		जाओ again;
	पूर्ण

	अगर (!immediate(skb) &&
	    map_skb(adap->pdev, skb, (dma_addr_t *)skb->head)) अणु
		spin_unlock(&q->lock);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	gen = q->gen;
	q->in_use += ndesc;
	pidx = q->pidx;
	q->pidx += ndesc;
	अगर (q->pidx >= q->size) अणु
		q->pidx -= q->size;
		q->gen ^= 1;
	पूर्ण
	spin_unlock(&q->lock);

	ग_लिखो_ofld_wr(adap, skb, q, pidx, gen, ndesc, (dma_addr_t *)skb->head);
	check_ring_tx_db(adap, q);
	वापस NET_XMIT_SUCCESS;
पूर्ण

/**
 *	restart_offloadq - restart a suspended offload queue
 *	@t: poपूर्णांकer to the tasklet associated with this handler
 *
 *	Resumes transmission on a suspended Tx offload queue.
 */
अटल व्योम restart_offloadq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sge_qset *qs = from_tasklet(qs, t, txq[TXQ_OFLD].qresume_tsk);
	काष्ठा sge_txq *q = &qs->txq[TXQ_OFLD];
	स्थिर काष्ठा port_info *pi = netdev_priv(qs->netdev);
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक written = 0;

	spin_lock(&q->lock);
again:	reclaim_completed_tx(adap, q, TX_RECLAIM_CHUNK);

	जबतक ((skb = skb_peek(&q->sendq)) != शून्य) अणु
		अचिन्हित पूर्णांक gen, pidx;
		अचिन्हित पूर्णांक ndesc = skb->priority;

		अगर (unlikely(q->size - q->in_use < ndesc)) अणु
			set_bit(TXQ_OFLD, &qs->txq_stopped);
			smp_mb__after_atomic();

			अगर (should_restart_tx(q) &&
			    test_and_clear_bit(TXQ_OFLD, &qs->txq_stopped))
				जाओ again;
			q->stops++;
			अवरोध;
		पूर्ण

		अगर (!immediate(skb) &&
		    map_skb(adap->pdev, skb, (dma_addr_t *)skb->head))
			अवरोध;

		gen = q->gen;
		q->in_use += ndesc;
		pidx = q->pidx;
		q->pidx += ndesc;
		written += ndesc;
		अगर (q->pidx >= q->size) अणु
			q->pidx -= q->size;
			q->gen ^= 1;
		पूर्ण
		__skb_unlink(skb, &q->sendq);
		spin_unlock(&q->lock);

		ग_लिखो_ofld_wr(adap, skb, q, pidx, gen, ndesc,
			      (dma_addr_t *)skb->head);
		spin_lock(&q->lock);
	पूर्ण
	spin_unlock(&q->lock);

#अगर USE_GTS
	set_bit(TXQ_RUNNING, &q->flags);
	set_bit(TXQ_LAST_PKT_DB, &q->flags);
#पूर्ण_अगर
	wmb();
	अगर (likely(written))
		t3_ग_लिखो_reg(adap, A_SG_KDOORBELL,
			     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
पूर्ण

/**
 *	queue_set - वापस the queue set a packet should use
 *	@skb: the packet
 *
 *	Maps a packet to the SGE queue set it should use.  The desired queue
 *	set is carried in bits 1-3 in the packet's priority.
 */
अटल अंतरभूत पूर्णांक queue_set(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->priority >> 1;
पूर्ण

/**
 *	is_ctrl_pkt - वापस whether an offload packet is a control packet
 *	@skb: the packet
 *
 *	Determines whether an offload packet should use an OFLD or a CTRL
 *	Tx queue.  This is indicated by bit 0 in the packet's priority.
 */
अटल अंतरभूत पूर्णांक is_ctrl_pkt(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->priority & 1;
पूर्ण

/**
 *	t3_offload_tx - send an offload packet
 *	@tdev: the offload device to send to
 *	@skb: the packet
 *
 *	Sends an offload packet.  We use the packet priority to select the
 *	appropriate Tx queue as follows: bit 0 indicates whether the packet
 *	should be sent as regular or control, bits 1-3 select the queue set.
 */
पूर्णांक t3_offload_tx(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा adapter *adap = tdev2adap(tdev);
	काष्ठा sge_qset *qs = &adap->sge.qs[queue_set(skb)];

	अगर (unlikely(is_ctrl_pkt(skb)))
		वापस ctrl_xmit(adap, &qs->txq[TXQ_CTRL], skb);

	वापस ofld_xmit(adap, &qs->txq[TXQ_OFLD], skb);
पूर्ण

/**
 *	offload_enqueue - add an offload packet to an SGE offload receive queue
 *	@q: the SGE response queue
 *	@skb: the packet
 *
 *	Add a new offload packet to an SGE response queue's offload packet
 *	queue.  If the packet is the first on the queue it schedules the RX
 *	softirq to process the queue.
 */
अटल अंतरभूत व्योम offload_enqueue(काष्ठा sge_rspq *q, काष्ठा sk_buff *skb)
अणु
	पूर्णांक was_empty = skb_queue_empty(&q->rx_queue);

	__skb_queue_tail(&q->rx_queue, skb);

	अगर (was_empty) अणु
		काष्ठा sge_qset *qs = rspq_to_qset(q);

		napi_schedule(&qs->napi);
	पूर्ण
पूर्ण

/**
 *	deliver_partial_bundle - deliver a (partial) bundle of Rx offload pkts
 *	@tdev: the offload device that will be receiving the packets
 *	@q: the SGE response queue that assembled the bundle
 *	@skbs: the partial bundle
 *	@n: the number of packets in the bundle
 *
 *	Delivers a (partial) bundle of Rx offload packets to an offload device.
 */
अटल अंतरभूत व्योम deliver_partial_bundle(काष्ठा t3cdev *tdev,
					  काष्ठा sge_rspq *q,
					  काष्ठा sk_buff *skbs[], पूर्णांक n)
अणु
	अगर (n) अणु
		q->offload_bundles++;
		tdev->recv(tdev, skbs, n);
	पूर्ण
पूर्ण

/**
 *	ofld_poll - NAPI handler क्रम offload packets in पूर्णांकerrupt mode
 *	@napi: the network device करोing the polling
 *	@budget: polling budget
 *
 *	The NAPI handler क्रम offload packets when a response queue is serviced
 *	by the hard पूर्णांकerrupt handler, i.e., when it's operating in non-polling
 *	mode.  Creates small packet batches and sends them through the offload
 *	receive handler.  Batches need to be of modest size as we करो prefetches
 *	on the packets in each.
 */
अटल पूर्णांक ofld_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sge_qset *qs = container_of(napi, काष्ठा sge_qset, napi);
	काष्ठा sge_rspq *q = &qs->rspq;
	काष्ठा adapter *adapter = qs->adap;
	पूर्णांक work_करोne = 0;

	जबतक (work_करोne < budget) अणु
		काष्ठा sk_buff *skb, *पंचांगp, *skbs[RX_BUNDLE_SIZE];
		काष्ठा sk_buff_head queue;
		पूर्णांक ngathered;

		spin_lock_irq(&q->lock);
		__skb_queue_head_init(&queue);
		skb_queue_splice_init(&q->rx_queue, &queue);
		अगर (skb_queue_empty(&queue)) अणु
			napi_complete_करोne(napi, work_करोne);
			spin_unlock_irq(&q->lock);
			वापस work_करोne;
		पूर्ण
		spin_unlock_irq(&q->lock);

		ngathered = 0;
		skb_queue_walk_safe(&queue, skb, पंचांगp) अणु
			अगर (work_करोne >= budget)
				अवरोध;
			work_करोne++;

			__skb_unlink(skb, &queue);
			prefetch(skb->data);
			skbs[ngathered] = skb;
			अगर (++ngathered == RX_BUNDLE_SIZE) अणु
				q->offload_bundles++;
				adapter->tdev.recv(&adapter->tdev, skbs,
						   ngathered);
				ngathered = 0;
			पूर्ण
		पूर्ण
		अगर (!skb_queue_empty(&queue)) अणु
			/* splice reमुख्यing packets back onto Rx queue */
			spin_lock_irq(&q->lock);
			skb_queue_splice(&queue, &q->rx_queue);
			spin_unlock_irq(&q->lock);
		पूर्ण
		deliver_partial_bundle(&adapter->tdev, q, skbs, ngathered);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 *	rx_offload - process a received offload packet
 *	@tdev: the offload device receiving the packet
 *	@rq: the response queue that received the packet
 *	@skb: the packet
 *	@rx_gather: a gather list of packets अगर we are building a bundle
 *	@gather_idx: index of the next available slot in the bundle
 *
 *	Process an ingress offload pakcet and add it to the offload ingress
 *	queue. 	Returns the index of the next available slot in the bundle.
 */
अटल अंतरभूत पूर्णांक rx_offload(काष्ठा t3cdev *tdev, काष्ठा sge_rspq *rq,
			     काष्ठा sk_buff *skb, काष्ठा sk_buff *rx_gather[],
			     अचिन्हित पूर्णांक gather_idx)
अणु
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	अगर (rq->polling) अणु
		rx_gather[gather_idx++] = skb;
		अगर (gather_idx == RX_BUNDLE_SIZE) अणु
			tdev->recv(tdev, rx_gather, RX_BUNDLE_SIZE);
			gather_idx = 0;
			rq->offload_bundles++;
		पूर्ण
	पूर्ण अन्यथा
		offload_enqueue(rq, skb);

	वापस gather_idx;
पूर्ण

/**
 *	restart_tx - check whether to restart suspended Tx queues
 *	@qs: the queue set to resume
 *
 *	Restarts suspended Tx queues of an SGE queue set अगर they have enough
 *	मुक्त resources to resume operation.
 */
अटल व्योम restart_tx(काष्ठा sge_qset *qs)
अणु
	अगर (test_bit(TXQ_ETH, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_ETH]) &&
	    test_and_clear_bit(TXQ_ETH, &qs->txq_stopped)) अणु
		qs->txq[TXQ_ETH].restarts++;
		अगर (netअगर_running(qs->netdev))
			netअगर_tx_wake_queue(qs->tx_q);
	पूर्ण

	अगर (test_bit(TXQ_OFLD, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_OFLD]) &&
	    test_and_clear_bit(TXQ_OFLD, &qs->txq_stopped)) अणु
		qs->txq[TXQ_OFLD].restarts++;
		tasklet_schedule(&qs->txq[TXQ_OFLD].qresume_tsk);
	पूर्ण
	अगर (test_bit(TXQ_CTRL, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_CTRL]) &&
	    test_and_clear_bit(TXQ_CTRL, &qs->txq_stopped)) अणु
		qs->txq[TXQ_CTRL].restarts++;
		tasklet_schedule(&qs->txq[TXQ_CTRL].qresume_tsk);
	पूर्ण
पूर्ण

/**
 *	cxgb3_arp_process - process an ARP request probing a निजी IP address
 *	@pi: the port info
 *	@skb: the skbuff containing the ARP request
 *
 *	Check अगर the ARP request is probing the निजी IP address
 *	dedicated to iSCSI, generate an ARP reply अगर so.
 */
अटल व्योम cxgb3_arp_process(काष्ठा port_info *pi, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा arphdr *arp;
	अचिन्हित अक्षर *arp_ptr;
	अचिन्हित अक्षर *sha;
	__be32 sip, tip;

	अगर (!dev)
		वापस;

	skb_reset_network_header(skb);
	arp = arp_hdr(skb);

	अगर (arp->ar_op != htons(ARPOP_REQUEST))
		वापस;

	arp_ptr = (अचिन्हित अक्षर *)(arp + 1);
	sha = arp_ptr;
	arp_ptr += dev->addr_len;
	स_नकल(&sip, arp_ptr, माप(sip));
	arp_ptr += माप(sip);
	arp_ptr += dev->addr_len;
	स_नकल(&tip, arp_ptr, माप(tip));

	अगर (tip != pi->iscsi_ipv4addr)
		वापस;

	arp_send(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip, sha,
		 pi->iscsic.mac_addr, sha);

पूर्ण

अटल अंतरभूत पूर्णांक is_arp(काष्ठा sk_buff *skb)
अणु
	वापस skb->protocol == htons(ETH_P_ARP);
पूर्ण

अटल व्योम cxgb3_process_iscsi_prov_pack(काष्ठा port_info *pi,
					काष्ठा sk_buff *skb)
अणु
	अगर (is_arp(skb)) अणु
		cxgb3_arp_process(pi, skb);
		वापस;
	पूर्ण

	अगर (pi->iscsic.recv)
		pi->iscsic.recv(pi, skb);

पूर्ण

/**
 *	rx_eth - process an ingress ethernet packet
 *	@adap: the adapter
 *	@rq: the response queue that received the packet
 *	@skb: the packet
 *	@pad: padding
 *	@lro: large receive offload
 *
 *	Process an ingress ethernet pakcet and deliver it to the stack.
 *	The padding is 2 अगर the packet was delivered in an Rx buffer and 0
 *	अगर it was immediate data in a response.
 */
अटल व्योम rx_eth(काष्ठा adapter *adap, काष्ठा sge_rspq *rq,
		   काष्ठा sk_buff *skb, पूर्णांक pad, पूर्णांक lro)
अणु
	काष्ठा cpl_rx_pkt *p = (काष्ठा cpl_rx_pkt *)(skb->data + pad);
	काष्ठा sge_qset *qs = rspq_to_qset(rq);
	काष्ठा port_info *pi;

	skb_pull(skb, माप(*p) + pad);
	skb->protocol = eth_type_trans(skb, adap->port[p->अगरf]);
	pi = netdev_priv(skb->dev);
	अगर ((skb->dev->features & NETIF_F_RXCSUM) && p->csum_valid &&
	    p->csum == htons(0xffff) && !p->fragment) अणु
		qs->port_stats[SGE_PSTAT_RX_CSUM_GOOD]++;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);
	skb_record_rx_queue(skb, qs - &adap->sge.qs[pi->first_qset]);

	अगर (p->vlan_valid) अणु
		qs->port_stats[SGE_PSTAT_VLANEX]++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vlan));
	पूर्ण
	अगर (rq->polling) अणु
		अगर (lro)
			napi_gro_receive(&qs->napi, skb);
		अन्यथा अणु
			अगर (unlikely(pi->iscsic.flags))
				cxgb3_process_iscsi_prov_pack(pi, skb);
			netअगर_receive_skb(skb);
		पूर्ण
	पूर्ण अन्यथा
		netअगर_rx(skb);
पूर्ण

अटल अंतरभूत पूर्णांक is_eth_tcp(u32 rss)
अणु
	वापस G_HASHTYPE(ntohl(rss)) == RSS_HASH_4_TUPLE;
पूर्ण

/**
 *	lro_add_page - add a page chunk to an LRO session
 *	@adap: the adapter
 *	@qs: the associated queue set
 *	@fl: the मुक्त list containing the page chunk to add
 *	@len: packet length
 *	@complete: Indicates the last fragment of a frame
 *
 *	Add a received packet contained in a page chunk to an existing LRO
 *	session.
 */
अटल व्योम lro_add_page(काष्ठा adapter *adap, काष्ठा sge_qset *qs,
			 काष्ठा sge_fl *fl, पूर्णांक len, पूर्णांक complete)
अणु
	काष्ठा rx_sw_desc *sd = &fl->sdesc[fl->cidx];
	काष्ठा port_info *pi = netdev_priv(qs->netdev);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा cpl_rx_pkt *cpl;
	skb_frag_t *rx_frag;
	पूर्णांक nr_frags;
	पूर्णांक offset = 0;

	अगर (!qs->nomem) अणु
		skb = napi_get_frags(&qs->napi);
		qs->nomem = !skb;
	पूर्ण

	fl->credits--;

	pci_dma_sync_single_क्रम_cpu(adap->pdev,
				    dma_unmap_addr(sd, dma_addr),
				    fl->buf_size - SGE_PG_RSVD,
				    PCI_DMA_FROMDEVICE);

	(*sd->pg_chunk.p_cnt)--;
	अगर (!*sd->pg_chunk.p_cnt && sd->pg_chunk.page != fl->pg_chunk.page)
		pci_unmap_page(adap->pdev,
			       sd->pg_chunk.mapping,
			       fl->alloc_size,
			       PCI_DMA_FROMDEVICE);

	अगर (!skb) अणु
		put_page(sd->pg_chunk.page);
		अगर (complete)
			qs->nomem = 0;
		वापस;
	पूर्ण

	rx_frag = skb_shinfo(skb)->frags;
	nr_frags = skb_shinfo(skb)->nr_frags;

	अगर (!nr_frags) अणु
		offset = 2 + माप(काष्ठा cpl_rx_pkt);
		cpl = qs->lro_va = sd->pg_chunk.va + 2;

		अगर ((qs->netdev->features & NETIF_F_RXCSUM) &&
		     cpl->csum_valid && cpl->csum == htons(0xffff)) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			qs->port_stats[SGE_PSTAT_RX_CSUM_GOOD]++;
		पूर्ण अन्यथा
			skb->ip_summed = CHECKSUM_NONE;
	पूर्ण अन्यथा
		cpl = qs->lro_va;

	len -= offset;

	rx_frag += nr_frags;
	__skb_frag_set_page(rx_frag, sd->pg_chunk.page);
	skb_frag_off_set(rx_frag, sd->pg_chunk.offset + offset);
	skb_frag_size_set(rx_frag, len);

	skb->len += len;
	skb->data_len += len;
	skb->truesize += len;
	skb_shinfo(skb)->nr_frags++;

	अगर (!complete)
		वापस;

	skb_record_rx_queue(skb, qs - &adap->sge.qs[pi->first_qset]);

	अगर (cpl->vlan_valid) अणु
		qs->port_stats[SGE_PSTAT_VLANEX]++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(cpl->vlan));
	पूर्ण
	napi_gro_frags(&qs->napi);
पूर्ण

/**
 *	handle_rsp_cntrl_info - handles control inक्रमmation in a response
 *	@qs: the queue set corresponding to the response
 *	@flags: the response control flags
 *
 *	Handles the control inक्रमmation of an SGE response, such as GTS
 *	indications and completion credits क्रम the queue set's Tx queues.
 *	HW coalesces credits, we करोn't करो any extra SW coalescing.
 */
अटल अंतरभूत व्योम handle_rsp_cntrl_info(काष्ठा sge_qset *qs, u32 flags)
अणु
	अचिन्हित पूर्णांक credits;

#अगर USE_GTS
	अगर (flags & F_RSPD_TXQ0_GTS)
		clear_bit(TXQ_RUNNING, &qs->txq[TXQ_ETH].flags);
#पूर्ण_अगर

	credits = G_RSPD_TXQ0_CR(flags);
	अगर (credits)
		qs->txq[TXQ_ETH].processed += credits;

	credits = G_RSPD_TXQ2_CR(flags);
	अगर (credits)
		qs->txq[TXQ_CTRL].processed += credits;

# अगर USE_GTS
	अगर (flags & F_RSPD_TXQ1_GTS)
		clear_bit(TXQ_RUNNING, &qs->txq[TXQ_OFLD].flags);
# endअगर
	credits = G_RSPD_TXQ1_CR(flags);
	अगर (credits)
		qs->txq[TXQ_OFLD].processed += credits;
पूर्ण

/**
 *	check_ring_db - check अगर we need to ring any करोorbells
 *	@adap: the adapter
 *	@qs: the queue set whose Tx queues are to be examined
 *	@sleeping: indicates which Tx queue sent GTS
 *
 *	Checks अगर some of a queue set's Tx queues need to ring their करोorbells
 *	to resume transmission after idling जबतक they still have unprocessed
 *	descriptors.
 */
अटल व्योम check_ring_db(काष्ठा adapter *adap, काष्ठा sge_qset *qs,
			  अचिन्हित पूर्णांक sleeping)
अणु
	अगर (sleeping & F_RSPD_TXQ0_GTS) अणु
		काष्ठा sge_txq *txq = &qs->txq[TXQ_ETH];

		अगर (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) अणु
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_ग_लिखो_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		पूर्ण
	पूर्ण

	अगर (sleeping & F_RSPD_TXQ1_GTS) अणु
		काष्ठा sge_txq *txq = &qs->txq[TXQ_OFLD];

		अगर (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) अणु
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_ग_लिखो_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	is_new_response - check अगर a response is newly written
 *	@r: the response descriptor
 *	@q: the response queue
 *
 *	Returns true अगर a response descriptor contains a yet unprocessed
 *	response.
 */
अटल अंतरभूत पूर्णांक is_new_response(स्थिर काष्ठा rsp_desc *r,
				  स्थिर काष्ठा sge_rspq *q)
अणु
	वापस (r->पूर्णांकr_gen & F_RSPD_GEN2) == q->gen;
पूर्ण

अटल अंतरभूत व्योम clear_rspq_buख_स्थितिe(काष्ठा sge_rspq * स्थिर q)
अणु
	q->pg_skb = शून्य;
	q->rx_recycle_buf = 0;
पूर्ण

#घोषणा RSPD_GTS_MASK  (F_RSPD_TXQ0_GTS | F_RSPD_TXQ1_GTS)
#घोषणा RSPD_CTRL_MASK (RSPD_GTS_MASK | \
			V_RSPD_TXQ0_CR(M_RSPD_TXQ0_CR) | \
			V_RSPD_TXQ1_CR(M_RSPD_TXQ1_CR) | \
			V_RSPD_TXQ2_CR(M_RSPD_TXQ2_CR))

/* How दीर्घ to delay the next पूर्णांकerrupt in हाल of memory लघुage, in 0.1us. */
#घोषणा NOMEM_INTR_DELAY 2500

/**
 *	process_responses - process responses from an SGE response queue
 *	@adap: the adapter
 *	@qs: the queue set to which the response queue beदीर्घs
 *	@budget: how many responses can be processed in this round
 *
 *	Process responses from an SGE response queue up to the supplied budget.
 *	Responses include received packets as well as credits and other events
 *	क्रम the queues that beदीर्घ to the response queue's queue set.
 *	A negative budget is effectively unlimited.
 *
 *	Additionally choose the पूर्णांकerrupt holकरोff समय क्रम the next पूर्णांकerrupt
 *	on this queue.  If the प्रणाली is under memory लघुage use a fairly
 *	दीर्घ delay to help recovery.
 */
अटल पूर्णांक process_responses(काष्ठा adapter *adap, काष्ठा sge_qset *qs,
			     पूर्णांक budget)
अणु
	काष्ठा sge_rspq *q = &qs->rspq;
	काष्ठा rsp_desc *r = &q->desc[q->cidx];
	पूर्णांक budget_left = budget;
	अचिन्हित पूर्णांक sleeping = 0;
	काष्ठा sk_buff *offload_skbs[RX_BUNDLE_SIZE];
	पूर्णांक ngathered = 0;

	q->next_holकरोff = q->holकरोff_पंचांगr;

	जबतक (likely(budget_left && is_new_response(r, q))) अणु
		पूर्णांक packet_complete, eth, ethpad = 2;
		पूर्णांक lro = !!(qs->netdev->features & NETIF_F_GRO);
		काष्ठा sk_buff *skb = शून्य;
		u32 len, flags;
		__be32 rss_hi, rss_lo;

		dma_rmb();
		eth = r->rss_hdr.opcode == CPL_RX_PKT;
		rss_hi = *(स्थिर __be32 *)r;
		rss_lo = r->rss_hdr.rss_hash_val;
		flags = ntohl(r->flags);

		अगर (unlikely(flags & F_RSPD_ASYNC_NOTIF)) अणु
			skb = alloc_skb(AN_PKT_SIZE, GFP_ATOMIC);
			अगर (!skb)
				जाओ no_mem;

			__skb_put_data(skb, r, AN_PKT_SIZE);
			skb->data[0] = CPL_ASYNC_NOTIF;
			rss_hi = htonl(CPL_ASYNC_NOTIF << 24);
			q->async_notअगर++;
		पूर्ण अन्यथा अगर (flags & F_RSPD_IMM_DATA_VALID) अणु
			skb = get_imm_packet(r);
			अगर (unlikely(!skb)) अणु
no_mem:
				q->next_holकरोff = NOMEM_INTR_DELAY;
				q->nomem++;
				/* consume one credit since we tried */
				budget_left--;
				अवरोध;
			पूर्ण
			q->imm_data++;
			ethpad = 0;
		पूर्ण अन्यथा अगर ((len = ntohl(r->len_cq)) != 0) अणु
			काष्ठा sge_fl *fl;

			lro &= eth && is_eth_tcp(rss_hi);

			fl = (len & F_RSPD_FLQ) ? &qs->fl[1] : &qs->fl[0];
			अगर (fl->use_pages) अणु
				व्योम *addr = fl->sdesc[fl->cidx].pg_chunk.va;

				net_prefetch(addr);
				__refill_fl(adap, fl);
				अगर (lro > 0) अणु
					lro_add_page(adap, qs, fl,
						     G_RSPD_LEN(len),
						     flags & F_RSPD_EOP);
					जाओ next_fl;
				पूर्ण

				skb = get_packet_pg(adap, fl, q,
						    G_RSPD_LEN(len),
						    eth ?
						    SGE_RX_DROP_THRES : 0);
				q->pg_skb = skb;
			पूर्ण अन्यथा
				skb = get_packet(adap, fl, G_RSPD_LEN(len),
						 eth ? SGE_RX_DROP_THRES : 0);
			अगर (unlikely(!skb)) अणु
				अगर (!eth)
					जाओ no_mem;
				q->rx_drops++;
			पूर्ण अन्यथा अगर (unlikely(r->rss_hdr.opcode == CPL_TRACE_PKT))
				__skb_pull(skb, 2);
next_fl:
			अगर (++fl->cidx == fl->size)
				fl->cidx = 0;
		पूर्ण अन्यथा
			q->pure_rsps++;

		अगर (flags & RSPD_CTRL_MASK) अणु
			sleeping |= flags & RSPD_GTS_MASK;
			handle_rsp_cntrl_info(qs, flags);
		पूर्ण

		r++;
		अगर (unlikely(++q->cidx == q->size)) अणु
			q->cidx = 0;
			q->gen ^= 1;
			r = q->desc;
		पूर्ण
		prefetch(r);

		अगर (++q->credits >= (q->size / 4)) अणु
			refill_rspq(adap, q, q->credits);
			q->credits = 0;
		पूर्ण

		packet_complete = flags &
				  (F_RSPD_EOP | F_RSPD_IMM_DATA_VALID |
				   F_RSPD_ASYNC_NOTIF);

		अगर (skb != शून्य && packet_complete) अणु
			अगर (eth)
				rx_eth(adap, q, skb, ethpad, lro);
			अन्यथा अणु
				q->offload_pkts++;
				/* Preserve the RSS info in csum & priority */
				skb->csum = rss_hi;
				skb->priority = rss_lo;
				ngathered = rx_offload(&adap->tdev, q, skb,
						       offload_skbs,
						       ngathered);
			पूर्ण

			अगर (flags & F_RSPD_EOP)
				clear_rspq_buख_स्थितिe(q);
		पूर्ण
		--budget_left;
	पूर्ण

	deliver_partial_bundle(&adap->tdev, q, offload_skbs, ngathered);

	अगर (sleeping)
		check_ring_db(adap, qs, sleeping);

	smp_mb();		/* commit Tx queue .processed updates */
	अगर (unlikely(qs->txq_stopped != 0))
		restart_tx(qs);

	budget -= budget_left;
	वापस budget;
पूर्ण

अटल अंतरभूत पूर्णांक is_pure_response(स्थिर काष्ठा rsp_desc *r)
अणु
	__be32 n = r->flags & htonl(F_RSPD_ASYNC_NOTIF | F_RSPD_IMM_DATA_VALID);

	वापस (n | r->len_cq) == 0;
पूर्ण

/**
 *	napi_rx_handler - the NAPI handler क्रम Rx processing
 *	@napi: the napi instance
 *	@budget: how many packets we can process in this round
 *
 *	Handler क्रम new data events when using NAPI.
 */
अटल पूर्णांक napi_rx_handler(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sge_qset *qs = container_of(napi, काष्ठा sge_qset, napi);
	काष्ठा adapter *adap = qs->adap;
	पूर्णांक work_करोne = process_responses(adap, qs, budget);

	अगर (likely(work_करोne < budget)) अणु
		napi_complete_करोne(napi, work_करोne);

		/*
		 * Because we करोn't atomically flush the following
		 * ग_लिखो it is possible that in very rare हालs it can
		 * reach the device in a way that races with a new
		 * response being written plus an error पूर्णांकerrupt
		 * causing the NAPI पूर्णांकerrupt handler below to वापस
		 * unhandled status to the OS.  To protect against
		 * this would require flushing the ग_लिखो and करोing
		 * both the ग_लिखो and the flush with पूर्णांकerrupts off.
		 * Way too expensive and unjustअगरiable given the
		 * rarity of the race.
		 *
		 * The race cannot happen at all with MSI-X.
		 */
		t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(qs->rspq.cntxt_id) |
			     V_NEWTIMER(qs->rspq.next_holकरोff) |
			     V_NEWINDEX(qs->rspq.cidx));
	पूर्ण
	वापस work_करोne;
पूर्ण

/*
 * Returns true अगर the device is alपढ़ोy scheduled क्रम polling.
 */
अटल अंतरभूत पूर्णांक napi_is_scheduled(काष्ठा napi_काष्ठा *napi)
अणु
	वापस test_bit(NAPI_STATE_SCHED, &napi->state);
पूर्ण

/**
 *	process_pure_responses - process pure responses from a response queue
 *	@adap: the adapter
 *	@qs: the queue set owning the response queue
 *	@r: the first pure response to process
 *
 *	A simpler version of process_responses() that handles only pure (i.e.,
 *	non data-carrying) responses.  Such respones are too light-weight to
 *	justअगरy calling a softirq under NAPI, so we handle them specially in
 *	the पूर्णांकerrupt handler.  The function is called with a poपूर्णांकer to a
 *	response, which the caller must ensure is a valid pure response.
 *
 *	Returns 1 अगर it encounters a valid data-carrying response, 0 otherwise.
 */
अटल पूर्णांक process_pure_responses(काष्ठा adapter *adap, काष्ठा sge_qset *qs,
				  काष्ठा rsp_desc *r)
अणु
	काष्ठा sge_rspq *q = &qs->rspq;
	अचिन्हित पूर्णांक sleeping = 0;

	करो अणु
		u32 flags = ntohl(r->flags);

		r++;
		अगर (unlikely(++q->cidx == q->size)) अणु
			q->cidx = 0;
			q->gen ^= 1;
			r = q->desc;
		पूर्ण
		prefetch(r);

		अगर (flags & RSPD_CTRL_MASK) अणु
			sleeping |= flags & RSPD_GTS_MASK;
			handle_rsp_cntrl_info(qs, flags);
		पूर्ण

		q->pure_rsps++;
		अगर (++q->credits >= (q->size / 4)) अणु
			refill_rspq(adap, q, q->credits);
			q->credits = 0;
		पूर्ण
		अगर (!is_new_response(r, q))
			अवरोध;
		dma_rmb();
	पूर्ण जबतक (is_pure_response(r));

	अगर (sleeping)
		check_ring_db(adap, qs, sleeping);

	smp_mb();		/* commit Tx queue .processed updates */
	अगर (unlikely(qs->txq_stopped != 0))
		restart_tx(qs);

	वापस is_new_response(r, q);
पूर्ण

/**
 *	handle_responses - decide what to करो with new responses in NAPI mode
 *	@adap: the adapter
 *	@q: the response queue
 *
 *	This is used by the NAPI पूर्णांकerrupt handlers to decide what to करो with
 *	new SGE responses.  If there are no new responses it वापसs -1.  If
 *	there are new responses and they are pure (i.e., non-data carrying)
 *	it handles them straight in hard पूर्णांकerrupt context as they are very
 *	cheap and करोn't deliver any packets.  Finally, अगर there are any data
 *	संकेतing responses it schedules the NAPI handler.  Returns 1 अगर it
 *	schedules NAPI, 0 अगर all new responses were pure.
 *
 *	The caller must ascertain NAPI is not alपढ़ोy running.
 */
अटल अंतरभूत पूर्णांक handle_responses(काष्ठा adapter *adap, काष्ठा sge_rspq *q)
अणु
	काष्ठा sge_qset *qs = rspq_to_qset(q);
	काष्ठा rsp_desc *r = &q->desc[q->cidx];

	अगर (!is_new_response(r, q))
		वापस -1;
	dma_rmb();
	अगर (is_pure_response(r) && process_pure_responses(adap, qs, r) == 0) अणु
		t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
			     V_NEWTIMER(q->holकरोff_पंचांगr) | V_NEWINDEX(q->cidx));
		वापस 0;
	पूर्ण
	napi_schedule(&qs->napi);
	वापस 1;
पूर्ण

/*
 * The MSI-X पूर्णांकerrupt handler क्रम an SGE response queue क्रम the non-NAPI हाल
 * (i.e., response queue serviced in hard पूर्णांकerrupt).
 */
अटल irqवापस_t t3_sge_पूर्णांकr_msix(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा sge_qset *qs = cookie;
	काष्ठा adapter *adap = qs->adap;
	काष्ठा sge_rspq *q = &qs->rspq;

	spin_lock(&q->lock);
	अगर (process_responses(adap, qs, -1) == 0)
		q->unhandled_irqs++;
	t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
		     V_NEWTIMER(q->next_holकरोff) | V_NEWINDEX(q->cidx));
	spin_unlock(&q->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * The MSI-X पूर्णांकerrupt handler क्रम an SGE response queue क्रम the NAPI हाल
 * (i.e., response queue serviced by NAPI polling).
 */
अटल irqवापस_t t3_sge_पूर्णांकr_msix_napi(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा sge_qset *qs = cookie;
	काष्ठा sge_rspq *q = &qs->rspq;

	spin_lock(&q->lock);

	अगर (handle_responses(qs->adap, q) < 0)
		q->unhandled_irqs++;
	spin_unlock(&q->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * The non-NAPI MSI पूर्णांकerrupt handler.  This needs to handle data events from
 * SGE response queues as well as error and other async events as they all use
 * the same MSI vector.  We use one SGE response queue per port in this mode
 * and protect all response queues with queue 0's lock.
 */
अटल irqवापस_t t3_पूर्णांकr_msi(पूर्णांक irq, व्योम *cookie)
अणु
	पूर्णांक new_packets = 0;
	काष्ठा adapter *adap = cookie;
	काष्ठा sge_rspq *q = &adap->sge.qs[0].rspq;

	spin_lock(&q->lock);

	अगर (process_responses(adap, &adap->sge.qs[0], -1)) अणु
		t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
			     V_NEWTIMER(q->next_holकरोff) | V_NEWINDEX(q->cidx));
		new_packets = 1;
	पूर्ण

	अगर (adap->params.nports == 2 &&
	    process_responses(adap, &adap->sge.qs[1], -1)) अणु
		काष्ठा sge_rspq *q1 = &adap->sge.qs[1].rspq;

		t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(q1->cntxt_id) |
			     V_NEWTIMER(q1->next_holकरोff) |
			     V_NEWINDEX(q1->cidx));
		new_packets = 1;
	पूर्ण

	अगर (!new_packets && t3_slow_पूर्णांकr_handler(adap) == 0)
		q->unhandled_irqs++;

	spin_unlock(&q->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rspq_check_napi(काष्ठा sge_qset *qs)
अणु
	काष्ठा sge_rspq *q = &qs->rspq;

	अगर (!napi_is_scheduled(&qs->napi) &&
	    is_new_response(&q->desc[q->cidx], q)) अणु
		napi_schedule(&qs->napi);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The MSI पूर्णांकerrupt handler क्रम the NAPI हाल (i.e., response queues serviced
 * by NAPI polling).  Handles data events from SGE response queues as well as
 * error and other async events as they all use the same MSI vector.  We use
 * one SGE response queue per port in this mode and protect all response
 * queues with queue 0's lock.
 */
अटल irqवापस_t t3_पूर्णांकr_msi_napi(पूर्णांक irq, व्योम *cookie)
अणु
	पूर्णांक new_packets;
	काष्ठा adapter *adap = cookie;
	काष्ठा sge_rspq *q = &adap->sge.qs[0].rspq;

	spin_lock(&q->lock);

	new_packets = rspq_check_napi(&adap->sge.qs[0]);
	अगर (adap->params.nports == 2)
		new_packets += rspq_check_napi(&adap->sge.qs[1]);
	अगर (!new_packets && t3_slow_पूर्णांकr_handler(adap) == 0)
		q->unhandled_irqs++;

	spin_unlock(&q->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * A helper function that processes responses and issues GTS.
 */
अटल अंतरभूत पूर्णांक process_responses_gts(काष्ठा adapter *adap,
					काष्ठा sge_rspq *rq)
अणु
	पूर्णांक work;

	work = process_responses(adap, rspq_to_qset(rq), -1);
	t3_ग_लिखो_reg(adap, A_SG_GTS, V_RSPQ(rq->cntxt_id) |
		     V_NEWTIMER(rq->next_holकरोff) | V_NEWINDEX(rq->cidx));
	वापस work;
पूर्ण

/*
 * The legacy INTx पूर्णांकerrupt handler.  This needs to handle data events from
 * SGE response queues as well as error and other async events as they all use
 * the same पूर्णांकerrupt pin.  We use one SGE response queue per port in this mode
 * and protect all response queues with queue 0's lock.
 */
अटल irqवापस_t t3_पूर्णांकr(पूर्णांक irq, व्योम *cookie)
अणु
	पूर्णांक work_करोne, w0, w1;
	काष्ठा adapter *adap = cookie;
	काष्ठा sge_rspq *q0 = &adap->sge.qs[0].rspq;
	काष्ठा sge_rspq *q1 = &adap->sge.qs[1].rspq;

	spin_lock(&q0->lock);

	w0 = is_new_response(&q0->desc[q0->cidx], q0);
	w1 = adap->params.nports == 2 &&
	    is_new_response(&q1->desc[q1->cidx], q1);

	अगर (likely(w0 | w1)) अणु
		t3_ग_लिखो_reg(adap, A_PL_CLI, 0);
		t3_पढ़ो_reg(adap, A_PL_CLI);	/* flush */

		अगर (likely(w0))
			process_responses_gts(adap, q0);

		अगर (w1)
			process_responses_gts(adap, q1);

		work_करोne = w0 | w1;
	पूर्ण अन्यथा
		work_करोne = t3_slow_पूर्णांकr_handler(adap);

	spin_unlock(&q0->lock);
	वापस IRQ_RETVAL(work_करोne != 0);
पूर्ण

/*
 * Interrupt handler क्रम legacy INTx पूर्णांकerrupts क्रम T3B-based cards.
 * Handles data events from SGE response queues as well as error and other
 * async events as they all use the same पूर्णांकerrupt pin.  We use one SGE
 * response queue per port in this mode and protect all response queues with
 * queue 0's lock.
 */
अटल irqवापस_t t3b_पूर्णांकr(पूर्णांक irq, व्योम *cookie)
अणु
	u32 map;
	काष्ठा adapter *adap = cookie;
	काष्ठा sge_rspq *q0 = &adap->sge.qs[0].rspq;

	t3_ग_लिखो_reg(adap, A_PL_CLI, 0);
	map = t3_पढ़ो_reg(adap, A_SG_DATA_INTR);

	अगर (unlikely(!map))	/* shared पूर्णांकerrupt, most likely */
		वापस IRQ_NONE;

	spin_lock(&q0->lock);

	अगर (unlikely(map & F_ERRINTR))
		t3_slow_पूर्णांकr_handler(adap);

	अगर (likely(map & 1))
		process_responses_gts(adap, q0);

	अगर (map & 2)
		process_responses_gts(adap, &adap->sge.qs[1].rspq);

	spin_unlock(&q0->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * NAPI पूर्णांकerrupt handler क्रम legacy INTx पूर्णांकerrupts क्रम T3B-based cards.
 * Handles data events from SGE response queues as well as error and other
 * async events as they all use the same पूर्णांकerrupt pin.  We use one SGE
 * response queue per port in this mode and protect all response queues with
 * queue 0's lock.
 */
अटल irqवापस_t t3b_पूर्णांकr_napi(पूर्णांक irq, व्योम *cookie)
अणु
	u32 map;
	काष्ठा adapter *adap = cookie;
	काष्ठा sge_qset *qs0 = &adap->sge.qs[0];
	काष्ठा sge_rspq *q0 = &qs0->rspq;

	t3_ग_लिखो_reg(adap, A_PL_CLI, 0);
	map = t3_पढ़ो_reg(adap, A_SG_DATA_INTR);

	अगर (unlikely(!map))	/* shared पूर्णांकerrupt, most likely */
		वापस IRQ_NONE;

	spin_lock(&q0->lock);

	अगर (unlikely(map & F_ERRINTR))
		t3_slow_पूर्णांकr_handler(adap);

	अगर (likely(map & 1))
		napi_schedule(&qs0->napi);

	अगर (map & 2)
		napi_schedule(&adap->sge.qs[1].napi);

	spin_unlock(&q0->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 *	t3_पूर्णांकr_handler - select the top-level पूर्णांकerrupt handler
 *	@adap: the adapter
 *	@polling: whether using NAPI to service response queues
 *
 *	Selects the top-level पूर्णांकerrupt handler based on the type of पूर्णांकerrupts
 *	(MSI-X, MSI, or legacy) and whether NAPI will be used to service the
 *	response queues.
 */
irq_handler_t t3_पूर्णांकr_handler(काष्ठा adapter *adap, पूर्णांक polling)
अणु
	अगर (adap->flags & USING_MSIX)
		वापस polling ? t3_sge_पूर्णांकr_msix_napi : t3_sge_पूर्णांकr_msix;
	अगर (adap->flags & USING_MSI)
		वापस polling ? t3_पूर्णांकr_msi_napi : t3_पूर्णांकr_msi;
	अगर (adap->params.rev > 0)
		वापस polling ? t3b_पूर्णांकr_napi : t3b_पूर्णांकr;
	वापस t3_पूर्णांकr;
पूर्ण

#घोषणा SGE_PARERR (F_CPPARITYERROR | F_OCPARITYERROR | F_RCPARITYERROR | \
		    F_IRPARITYERROR | V_ITPARITYERROR(M_ITPARITYERROR) | \
		    V_FLPARITYERROR(M_FLPARITYERROR) | F_LODRBPARITYERROR | \
		    F_HIDRBPARITYERROR | F_LORCQPARITYERROR | \
		    F_HIRCQPARITYERROR)
#घोषणा SGE_FRAMINGERR (F_UC_REQ_FRAMINGERROR | F_R_REQ_FRAMINGERROR)
#घोषणा SGE_FATALERR (SGE_PARERR | SGE_FRAMINGERR | F_RSPQCREDITOVERFOW | \
		      F_RSPQDISABLED)

/**
 *	t3_sge_err_पूर्णांकr_handler - SGE async event पूर्णांकerrupt handler
 *	@adapter: the adapter
 *
 *	Interrupt handler क्रम SGE asynchronous (non-data) events.
 */
व्योम t3_sge_err_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक v, status = t3_पढ़ो_reg(adapter, A_SG_INT_CAUSE) &
				 ~F_FLEMPTY;

	अगर (status & SGE_PARERR)
		CH_ALERT(adapter, "SGE parity error (0x%x)\n",
			 status & SGE_PARERR);
	अगर (status & SGE_FRAMINGERR)
		CH_ALERT(adapter, "SGE framing error (0x%x)\n",
			 status & SGE_FRAMINGERR);

	अगर (status & F_RSPQCREDITOVERFOW)
		CH_ALERT(adapter, "SGE response queue credit overflow\n");

	अगर (status & F_RSPQDISABLED) अणु
		v = t3_पढ़ो_reg(adapter, A_SG_RSPQ_FL_STATUS);

		CH_ALERT(adapter,
			 "packet delivered to disabled response queue "
			 "(0x%x)\n", (v >> S_RSPQ0DISABLED) & 0xff);
	पूर्ण

	अगर (status & (F_HIPIODRBDROPERR | F_LOPIODRBDROPERR))
		queue_work(cxgb3_wq, &adapter->db_drop_task);

	अगर (status & (F_HIPRIORITYDBFULL | F_LOPRIORITYDBFULL))
		queue_work(cxgb3_wq, &adapter->db_full_task);

	अगर (status & (F_HIPRIORITYDBEMPTY | F_LOPRIORITYDBEMPTY))
		queue_work(cxgb3_wq, &adapter->db_empty_task);

	t3_ग_लिखो_reg(adapter, A_SG_INT_CAUSE, status);
	अगर (status &  SGE_FATALERR)
		t3_fatal_err(adapter);
पूर्ण

/**
 *	sge_समयr_tx - perक्रमm periodic मुख्यtenance of an SGE qset
 *	@t: a समयr list containing the SGE queue set to मुख्यtain
 *
 *	Runs periodically from a समयr to perक्रमm मुख्यtenance of an SGE queue
 *	set.  It perक्रमms two tasks:
 *
 *	Cleans up any completed Tx descriptors that may still be pending.
 *	Normal descriptor cleanup happens when new packets are added to a Tx
 *	queue so this समयr is relatively infrequent and करोes any cleanup only
 *	अगर the Tx queue has not seen any new packets in a जबतक.  We make a
 *	best efक्रमt attempt to reclaim descriptors, in that we करोn't रुको
 *	around अगर we cannot get a queue's lock (which most likely is because
 *	someone अन्यथा is queueing new packets and so will also handle the clean
 *	up).  Since control queues use immediate data exclusively we करोn't
 *	bother cleaning them up here.
 *
 */
अटल व्योम sge_समयr_tx(काष्ठा समयr_list *t)
अणु
	काष्ठा sge_qset *qs = from_समयr(qs, t, tx_reclaim_समयr);
	काष्ठा port_info *pi = netdev_priv(qs->netdev);
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक tbd[SGE_TXQ_PER_SET] = अणु0, 0पूर्ण;
	अचिन्हित दीर्घ next_period;

	अगर (__netअगर_tx_trylock(qs->tx_q)) अणु
                tbd[TXQ_ETH] = reclaim_completed_tx(adap, &qs->txq[TXQ_ETH],
                                                     TX_RECLAIM_TIMER_CHUNK);
		__netअगर_tx_unlock(qs->tx_q);
	पूर्ण

	अगर (spin_trylock(&qs->txq[TXQ_OFLD].lock)) अणु
		tbd[TXQ_OFLD] = reclaim_completed_tx(adap, &qs->txq[TXQ_OFLD],
						     TX_RECLAIM_TIMER_CHUNK);
		spin_unlock(&qs->txq[TXQ_OFLD].lock);
	पूर्ण

	next_period = TX_RECLAIM_PERIOD >>
                      (max(tbd[TXQ_ETH], tbd[TXQ_OFLD]) /
                      TX_RECLAIM_TIMER_CHUNK);
	mod_समयr(&qs->tx_reclaim_समयr, jअगरfies + next_period);
पूर्ण

/**
 *	sge_समयr_rx - perक्रमm periodic मुख्यtenance of an SGE qset
 *	@t: the समयr list containing the SGE queue set to मुख्यtain
 *
 *	a) Replenishes Rx queues that have run out due to memory लघुage.
 *	Normally new Rx buffers are added when existing ones are consumed but
 *	when out of memory a queue can become empty.  We try to add only a few
 *	buffers here, the queue will be replenished fully as these new buffers
 *	are used up अगर memory लघुage has subsided.
 *
 *	b) Return coalesced response queue credits in हाल a response queue is
 *	starved.
 *
 */
अटल व्योम sge_समयr_rx(काष्ठा समयr_list *t)
अणु
	spinlock_t *lock;
	काष्ठा sge_qset *qs = from_समयr(qs, t, rx_reclaim_समयr);
	काष्ठा port_info *pi = netdev_priv(qs->netdev);
	काष्ठा adapter *adap = pi->adapter;
	u32 status;

	lock = adap->params.rev > 0 ?
	       &qs->rspq.lock : &adap->sge.qs[0].rspq.lock;

	अगर (!spin_trylock_irq(lock))
		जाओ out;

	अगर (napi_is_scheduled(&qs->napi))
		जाओ unlock;

	अगर (adap->params.rev < 4) अणु
		status = t3_पढ़ो_reg(adap, A_SG_RSPQ_FL_STATUS);

		अगर (status & (1 << qs->rspq.cntxt_id)) अणु
			qs->rspq.starved++;
			अगर (qs->rspq.credits) अणु
				qs->rspq.credits--;
				refill_rspq(adap, &qs->rspq, 1);
				qs->rspq.restarted++;
				t3_ग_लिखो_reg(adap, A_SG_RSPQ_FL_STATUS,
					     1 << qs->rspq.cntxt_id);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (qs->fl[0].credits < qs->fl[0].size)
		__refill_fl(adap, &qs->fl[0]);
	अगर (qs->fl[1].credits < qs->fl[1].size)
		__refill_fl(adap, &qs->fl[1]);

unlock:
	spin_unlock_irq(lock);
out:
	mod_समयr(&qs->rx_reclaim_समयr, jअगरfies + RX_RECLAIM_PERIOD);
पूर्ण

/**
 *	t3_update_qset_coalesce - update coalescing settings क्रम a queue set
 *	@qs: the SGE queue set
 *	@p: new queue set parameters
 *
 *	Update the coalescing settings क्रम an SGE queue set.  Nothing is करोne
 *	अगर the queue set is not initialized yet.
 */
व्योम t3_update_qset_coalesce(काष्ठा sge_qset *qs, स्थिर काष्ठा qset_params *p)
अणु
	qs->rspq.holकरोff_पंचांगr = max(p->coalesce_usecs * 10, 1U);/* can't be 0 */
	qs->rspq.polling = p->polling;
	qs->napi.poll = p->polling ? napi_rx_handler : ofld_poll;
पूर्ण

/**
 *	t3_sge_alloc_qset - initialize an SGE queue set
 *	@adapter: the adapter
 *	@id: the queue set id
 *	@nports: how many Ethernet ports will be using this queue set
 *	@irq_vec_idx: the IRQ vector index क्रम response queue पूर्णांकerrupts
 *	@p: configuration parameters क्रम this queue set
 *	@ntxq: number of Tx queues क्रम the queue set
 *	@dev: net device associated with this queue set
 *	@netdevq: net device TX queue associated with this queue set
 *
 *	Allocate resources and initialize an SGE queue set.  A queue set
 *	comprises a response queue, two Rx मुक्त-buffer queues, and up to 3
 *	Tx queues.  The Tx queues are asचिन्हित roles in the order Ethernet
 *	queue, offload queue, and control queue.
 */
पूर्णांक t3_sge_alloc_qset(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक nports,
		      पूर्णांक irq_vec_idx, स्थिर काष्ठा qset_params *p,
		      पूर्णांक ntxq, काष्ठा net_device *dev,
		      काष्ठा netdev_queue *netdevq)
अणु
	पूर्णांक i, avail, ret = -ENOMEM;
	काष्ठा sge_qset *q = &adapter->sge.qs[id];

	init_qset_cntxt(q, id);
	समयr_setup(&q->tx_reclaim_समयr, sge_समयr_tx, 0);
	समयr_setup(&q->rx_reclaim_समयr, sge_समयr_rx, 0);

	q->fl[0].desc = alloc_ring(adapter->pdev, p->fl_size,
				   माप(काष्ठा rx_desc),
				   माप(काष्ठा rx_sw_desc),
				   &q->fl[0].phys_addr, &q->fl[0].sdesc);
	अगर (!q->fl[0].desc)
		जाओ err;

	q->fl[1].desc = alloc_ring(adapter->pdev, p->jumbo_size,
				   माप(काष्ठा rx_desc),
				   माप(काष्ठा rx_sw_desc),
				   &q->fl[1].phys_addr, &q->fl[1].sdesc);
	अगर (!q->fl[1].desc)
		जाओ err;

	q->rspq.desc = alloc_ring(adapter->pdev, p->rspq_size,
				  माप(काष्ठा rsp_desc), 0,
				  &q->rspq.phys_addr, शून्य);
	अगर (!q->rspq.desc)
		जाओ err;

	क्रम (i = 0; i < ntxq; ++i) अणु
		/*
		 * The control queue always uses immediate data so करोes not
		 * need to keep track of any sk_buffs.
		 */
		माप_प्रकार sz = i == TXQ_CTRL ? 0 : माप(काष्ठा tx_sw_desc);

		q->txq[i].desc = alloc_ring(adapter->pdev, p->txq_size[i],
					    माप(काष्ठा tx_desc), sz,
					    &q->txq[i].phys_addr,
					    &q->txq[i].sdesc);
		अगर (!q->txq[i].desc)
			जाओ err;

		q->txq[i].gen = 1;
		q->txq[i].size = p->txq_size[i];
		spin_lock_init(&q->txq[i].lock);
		skb_queue_head_init(&q->txq[i].sendq);
	पूर्ण

	tasklet_setup(&q->txq[TXQ_OFLD].qresume_tsk, restart_offloadq);
	tasklet_setup(&q->txq[TXQ_CTRL].qresume_tsk, restart_ctrlq);

	q->fl[0].gen = q->fl[1].gen = 1;
	q->fl[0].size = p->fl_size;
	q->fl[1].size = p->jumbo_size;

	q->rspq.gen = 1;
	q->rspq.size = p->rspq_size;
	spin_lock_init(&q->rspq.lock);
	skb_queue_head_init(&q->rspq.rx_queue);

	q->txq[TXQ_ETH].stop_thres = nports *
	    flits_to_desc(sgl_len(MAX_SKB_FRAGS + 1) + 3);

#अगर FL0_PG_CHUNK_SIZE > 0
	q->fl[0].buf_size = FL0_PG_CHUNK_SIZE;
#अन्यथा
	q->fl[0].buf_size = SGE_RX_SM_BUF_SIZE + माप(काष्ठा cpl_rx_data);
#पूर्ण_अगर
#अगर FL1_PG_CHUNK_SIZE > 0
	q->fl[1].buf_size = FL1_PG_CHUNK_SIZE;
#अन्यथा
	q->fl[1].buf_size = is_offload(adapter) ?
		(16 * 1024) - SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		MAX_FRAME_SIZE + 2 + माप(काष्ठा cpl_rx_pkt);
#पूर्ण_अगर

	q->fl[0].use_pages = FL0_PG_CHUNK_SIZE > 0;
	q->fl[1].use_pages = FL1_PG_CHUNK_SIZE > 0;
	q->fl[0].order = FL0_PG_ORDER;
	q->fl[1].order = FL1_PG_ORDER;
	q->fl[0].alloc_size = FL0_PG_ALLOC_SIZE;
	q->fl[1].alloc_size = FL1_PG_ALLOC_SIZE;

	spin_lock_irq(&adapter->sge.reg_lock);

	/* FL threshold comparison uses < */
	ret = t3_sge_init_rspcntxt(adapter, q->rspq.cntxt_id, irq_vec_idx,
				   q->rspq.phys_addr, q->rspq.size,
				   q->fl[0].buf_size - SGE_PG_RSVD, 1, 0);
	अगर (ret)
		जाओ err_unlock;

	क्रम (i = 0; i < SGE_RXQ_PER_SET; ++i) अणु
		ret = t3_sge_init_flcntxt(adapter, q->fl[i].cntxt_id, 0,
					  q->fl[i].phys_addr, q->fl[i].size,
					  q->fl[i].buf_size - SGE_PG_RSVD,
					  p->cong_thres, 1, 0);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_ETH].cntxt_id, USE_GTS,
				 SGE_CNTXT_ETH, id, q->txq[TXQ_ETH].phys_addr,
				 q->txq[TXQ_ETH].size, q->txq[TXQ_ETH].token,
				 1, 0);
	अगर (ret)
		जाओ err_unlock;

	अगर (ntxq > 1) अणु
		ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_OFLD].cntxt_id,
					 USE_GTS, SGE_CNTXT_OFLD, id,
					 q->txq[TXQ_OFLD].phys_addr,
					 q->txq[TXQ_OFLD].size, 0, 1, 0);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	अगर (ntxq > 2) अणु
		ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_CTRL].cntxt_id, 0,
					 SGE_CNTXT_CTRL, id,
					 q->txq[TXQ_CTRL].phys_addr,
					 q->txq[TXQ_CTRL].size,
					 q->txq[TXQ_CTRL].token, 1, 0);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	spin_unlock_irq(&adapter->sge.reg_lock);

	q->adap = adapter;
	q->netdev = dev;
	q->tx_q = netdevq;
	t3_update_qset_coalesce(q, p);

	avail = refill_fl(adapter, &q->fl[0], q->fl[0].size,
			  GFP_KERNEL | __GFP_COMP);
	अगर (!avail) अणु
		CH_ALERT(adapter, "free list queue 0 initialization failed\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	अगर (avail < q->fl[0].size)
		CH_WARN(adapter, "free list queue 0 enabled with %d credits\n",
			avail);

	avail = refill_fl(adapter, &q->fl[1], q->fl[1].size,
			  GFP_KERNEL | __GFP_COMP);
	अगर (avail < q->fl[1].size)
		CH_WARN(adapter, "free list queue 1 enabled with %d credits\n",
			avail);
	refill_rspq(adapter, &q->rspq, q->rspq.size - 1);

	t3_ग_लिखो_reg(adapter, A_SG_GTS, V_RSPQ(q->rspq.cntxt_id) |
		     V_NEWTIMER(q->rspq.holकरोff_पंचांगr));

	वापस 0;

err_unlock:
	spin_unlock_irq(&adapter->sge.reg_lock);
err:
	t3_मुक्त_qset(adapter, q);
	वापस ret;
पूर्ण

/**
 *      t3_start_sge_समयrs - start SGE समयr call backs
 *      @adap: the adapter
 *
 *      Starts each SGE queue set's समयr call back
 */
व्योम t3_start_sge_समयrs(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SGE_QSETS; ++i) अणु
		काष्ठा sge_qset *q = &adap->sge.qs[i];

		अगर (q->tx_reclaim_समयr.function)
			mod_समयr(&q->tx_reclaim_समयr,
				  jअगरfies + TX_RECLAIM_PERIOD);

		अगर (q->rx_reclaim_समयr.function)
			mod_समयr(&q->rx_reclaim_समयr,
				  jअगरfies + RX_RECLAIM_PERIOD);
	पूर्ण
पूर्ण

/**
 *	t3_stop_sge_समयrs - stop SGE समयr call backs
 *	@adap: the adapter
 *
 *	Stops each SGE queue set's समयr call back
 */
व्योम t3_stop_sge_समयrs(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SGE_QSETS; ++i) अणु
		काष्ठा sge_qset *q = &adap->sge.qs[i];

		अगर (q->tx_reclaim_समयr.function)
			del_समयr_sync(&q->tx_reclaim_समयr);
		अगर (q->rx_reclaim_समयr.function)
			del_समयr_sync(&q->rx_reclaim_समयr);
	पूर्ण
पूर्ण

/**
 *	t3_मुक्त_sge_resources - मुक्त SGE resources
 *	@adap: the adapter
 *
 *	Frees resources used by the SGE queue sets.
 */
व्योम t3_मुक्त_sge_resources(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SGE_QSETS; ++i)
		t3_मुक्त_qset(adap, &adap->sge.qs[i]);
पूर्ण

/**
 *	t3_sge_start - enable SGE
 *	@adap: the adapter
 *
 *	Enables the SGE क्रम DMAs.  This is the last step in starting packet
 *	transfers.
 */
व्योम t3_sge_start(काष्ठा adapter *adap)
अणु
	t3_set_reg_field(adap, A_SG_CONTROL, F_GLOBALENABLE, F_GLOBALENABLE);
पूर्ण

/**
 *	t3_sge_stop_dma - Disable SGE DMA engine operation
 *	@adap: the adapter
 *
 *	Can be invoked from पूर्णांकerrupt context e.g.  error handler.
 *
 *	Note that this function cannot disable the restart of tasklets as
 *	it cannot रुको अगर called from पूर्णांकerrupt context, however the
 *	tasklets will have no effect since the करोorbells are disabled. The
 *	driver will call tg3_sge_stop() later from process context, at
 *	which समय the tasklets will be stopped अगर they are still running.
 */
व्योम t3_sge_stop_dma(काष्ठा adapter *adap)
अणु
	t3_set_reg_field(adap, A_SG_CONTROL, F_GLOBALENABLE, 0);
पूर्ण

/**
 *	t3_sge_stop - disable SGE operation completly
 *	@adap: the adapter
 *
 *	Called from process context. Disables the DMA engine and any
 *	pending queue restart tasklets.
 */
व्योम t3_sge_stop(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	t3_sge_stop_dma(adap);

	क्रम (i = 0; i < SGE_QSETS; ++i) अणु
		काष्ठा sge_qset *qs = &adap->sge.qs[i];

		tasklet_समाप्त(&qs->txq[TXQ_OFLD].qresume_tsk);
		tasklet_समाप्त(&qs->txq[TXQ_CTRL].qresume_tsk);
	पूर्ण
पूर्ण

/**
 *	t3_sge_init - initialize SGE
 *	@adap: the adapter
 *	@p: the SGE parameters
 *
 *	Perक्रमms SGE initialization needed every समय after a chip reset.
 *	We करो not initialize any of the queue sets here, instead the driver
 *	top-level must request those inभागidually.  We also करो not enable DMA
 *	here, that should be करोne after the queues have been set up.
 */
व्योम t3_sge_init(काष्ठा adapter *adap, काष्ठा sge_params *p)
अणु
	अचिन्हित पूर्णांक ctrl, ups = ffs(pci_resource_len(adap->pdev, 2) >> 12);

	ctrl = F_DROPPKT | V_PKTSHIFT(2) | F_FLMODE | F_AVOIDCQOVFL |
	    F_CQCRDTCTRL | F_CONGMODE | F_TNLFLMODE | F_FATLPERREN |
	    V_HOSTPAGESIZE(PAGE_SHIFT - 11) | F_BIGENDIANINGRESS |
	    V_USERSPACESIZE(ups ? ups - 1 : 0) | F_ISCSICOALESCING;
#अगर SGE_NUM_GENBITS == 1
	ctrl |= F_EGRGENCTRL;
#पूर्ण_अगर
	अगर (adap->params.rev > 0) अणु
		अगर (!(adap->flags & (USING_MSIX | USING_MSI)))
			ctrl |= F_ONEINTMULTQ | F_OPTONEINTMULTQ;
	पूर्ण
	t3_ग_लिखो_reg(adap, A_SG_CONTROL, ctrl);
	t3_ग_लिखो_reg(adap, A_SG_EGR_RCQ_DRB_THRSH, V_HIRCQDRBTHRSH(512) |
		     V_LORCQDRBTHRSH(512));
	t3_ग_लिखो_reg(adap, A_SG_TIMER_TICK, core_ticks_per_usec(adap) / 10);
	t3_ग_लिखो_reg(adap, A_SG_CMDQ_CREDIT_TH, V_THRESHOLD(32) |
		     V_TIMEOUT(200 * core_ticks_per_usec(adap)));
	t3_ग_लिखो_reg(adap, A_SG_HI_DRB_HI_THRSH,
		     adap->params.rev < T3_REV_C ? 1000 : 500);
	t3_ग_लिखो_reg(adap, A_SG_HI_DRB_LO_THRSH, 256);
	t3_ग_लिखो_reg(adap, A_SG_LO_DRB_HI_THRSH, 1000);
	t3_ग_लिखो_reg(adap, A_SG_LO_DRB_LO_THRSH, 256);
	t3_ग_लिखो_reg(adap, A_SG_OCO_BASE, V_BASE1(0xfff));
	t3_ग_लिखो_reg(adap, A_SG_DRB_PRI_THRESH, 63 * 1024);
पूर्ण

/**
 *	t3_sge_prep - one-समय SGE initialization
 *	@adap: the associated adapter
 *	@p: SGE parameters
 *
 *	Perक्रमms one-समय initialization of SGE SW state.  Includes determining
 *	शेषs क्रम the assorted SGE parameters, which admins can change until
 *	they are used to initialize the SGE.
 */
व्योम t3_sge_prep(काष्ठा adapter *adap, काष्ठा sge_params *p)
अणु
	पूर्णांक i;

	p->max_pkt_size = (16 * 1024) - माप(काष्ठा cpl_rx_data) -
	    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	क्रम (i = 0; i < SGE_QSETS; ++i) अणु
		काष्ठा qset_params *q = p->qset + i;

		q->polling = adap->params.rev > 0;
		q->coalesce_usecs = 5;
		q->rspq_size = 1024;
		q->fl_size = 1024;
 		q->jumbo_size = 512;
		q->txq_size[TXQ_ETH] = 1024;
		q->txq_size[TXQ_OFLD] = 1024;
		q->txq_size[TXQ_CTRL] = 256;
		q->cong_thres = 0;
	पूर्ण

	spin_lock_init(&adap->sge.reg_lock);
पूर्ण
