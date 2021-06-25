<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
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
#समावेश <linux/dma-mapping.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/export.h>
#समावेश <net/xfrm.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <net/busy_poll.h>
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
#समावेश <scsi/fc/fc_fcoe.h>
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
#समावेश "cxgb4.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"
#समावेश "t4_msg.h"
#समावेश "t4fw_api.h"
#समावेश "cxgb4_ptp.h"
#समावेश "cxgb4_uld.h"
#समावेश "cxgb4_tc_mqprio.h"
#समावेश "sched.h"

/*
 * Rx buffer size.  We use largish buffers अगर possible but settle क्रम single
 * pages under memory लघुage.
 */
#अगर PAGE_SHIFT >= 16
# define FL_PG_ORDER 0
#अन्यथा
# define FL_PG_ORDER (16 - PAGE_SHIFT)
#पूर्ण_अगर

/* RX_PULL_LEN should be <= RX_COPY_THRES */
#घोषणा RX_COPY_THRES    256
#घोषणा RX_PULL_LEN      128

/*
 * Main body length क्रम sk_buffs used क्रम Rx Ethernet packets with fragments.
 * Should be >= RX_PULL_LEN but possibly bigger to give pskb_may_pull some room.
 */
#घोषणा RX_PKT_SKB_LEN   512

/*
 * Max number of Tx descriptors we clean up at a समय.  Should be modest as
 * मुक्तing skbs isn't cheap and it happens जबतक holding locks.  We just need
 * to मुक्त packets faster than they arrive, we eventually catch up and keep
 * the amortized cost reasonable.  Must be >= 2 * TXQ_STOP_THRES.  It should
 * also match the CIDX Flush Threshold.
 */
#घोषणा MAX_TX_RECLAIM 32

/*
 * Max number of Rx buffers we replenish at a समय.  Again keep this modest,
 * allocating buffers isn't cheap either.
 */
#घोषणा MAX_RX_REFILL 16U

/*
 * Period of the Rx queue check समयr.  This समयr is infrequent as it has
 * something to करो only when the प्रणाली experiences severe memory लघुage.
 */
#घोषणा RX_QCHECK_PERIOD (HZ / 2)

/*
 * Period of the Tx queue check समयr.
 */
#घोषणा TX_QCHECK_PERIOD (HZ / 2)

/*
 * Max number of Tx descriptors to be reclaimed by the Tx समयr.
 */
#घोषणा MAX_TIMER_TX_RECLAIM 100

/*
 * Timer index used when backing off due to memory लघुage.
 */
#घोषणा NOMEM_TMR_IDX (SGE_NTIMERS - 1)

/*
 * Suspension threshold क्रम non-Ethernet Tx queues.  We require enough room
 * क्रम a full sized WR.
 */
#घोषणा TXQ_STOP_THRES (SGE_MAX_WR_LEN / माप(काष्ठा tx_desc))

/*
 * Max Tx descriptor space we allow क्रम an Ethernet packet to be अंतरभूतd
 * पूर्णांकo a WR.
 */
#घोषणा MAX_IMM_TX_PKT_LEN 256

/*
 * Max size of a WR sent through a control Tx queue.
 */
#घोषणा MAX_CTRL_WR_LEN SGE_MAX_WR_LEN

काष्ठा rx_sw_desc अणु                /* SW state per Rx descriptor */
	काष्ठा page *page;
	dma_addr_t dma_addr;
पूर्ण;

/*
 * Rx buffer sizes क्रम "useskbs" Free List buffers (one ingress packet pe skb
 * buffer).  We currently only support two sizes क्रम 1500- and 9000-byte MTUs.
 * We could easily support more but there करोesn't seem to be much need क्रम
 * that ...
 */
#घोषणा FL_MTU_SMALL 1500
#घोषणा FL_MTU_LARGE 9000

अटल अंतरभूत अचिन्हित पूर्णांक fl_mtu_bufsize(काष्ठा adapter *adapter,
					  अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा sge *s = &adapter->sge;

	वापस ALIGN(s->pktshअगरt + ETH_HLEN + VLAN_HLEN + mtu, s->fl_align);
पूर्ण

#घोषणा FL_MTU_SMALL_बफ_मानE(adapter) fl_mtu_bufsize(adapter, FL_MTU_SMALL)
#घोषणा FL_MTU_LARGE_बफ_मानE(adapter) fl_mtu_bufsize(adapter, FL_MTU_LARGE)

/*
 * Bits 0..3 of rx_sw_desc.dma_addr have special meaning.  The hardware uses
 * these to specअगरy the buffer size as an index पूर्णांकo the SGE Free List Buffer
 * Size रेजिस्टर array.  We also use bit 4, when the buffer has been unmapped
 * क्रम DMA, but this is of course never sent to the hardware and is only used
 * to prevent द्विगुन unmappings.  All of the above requires that the Free List
 * Buffers which we allocate have the bottom 5 bits मुक्त (0) -- i.e. are
 * 32-byte or or a घातer of 2 greater in alignment.  Since the SGE's minimal
 * Free List Buffer alignment is 32 bytes, this works out क्रम us ...
 */
क्रमागत अणु
	RX_BUF_FLAGS     = 0x1f,   /* bottom five bits are special */
	RX_BUF_SIZE      = 0x0f,   /* bottom three bits are क्रम buf sizes */
	RX_UNMAPPED_BUF  = 0x10,   /* buffer is not mapped */

	/*
	 * XXX We shouldn't depend on being able to use these indices.
	 * XXX Especially when some other Master PF has initialized the
	 * XXX adapter or we use the Firmware Configuration File.  We
	 * XXX should really search through the Host Buffer Size रेजिस्टर
	 * XXX array क्रम the appropriately sized buffer indices.
	 */
	RX_SMALL_PG_BUF  = 0x0,   /* small (PAGE_SIZE) page buffer */
	RX_LARGE_PG_BUF  = 0x1,   /* buffer large (FL_PG_ORDER) page buffer */

	RX_SMALL_MTU_BUF = 0x2,   /* small MTU buffer */
	RX_LARGE_MTU_BUF = 0x3,   /* large MTU buffer */
पूर्ण;

अटल पूर्णांक समयr_pkt_quota[] = अणु1, 1, 2, 3, 4, 5पूर्ण;
#घोषणा MIN_NAPI_WORK  1

अटल अंतरभूत dma_addr_t get_buf_addr(स्थिर काष्ठा rx_sw_desc *d)
अणु
	वापस d->dma_addr & ~(dma_addr_t)RX_BUF_FLAGS;
पूर्ण

अटल अंतरभूत bool is_buf_mapped(स्थिर काष्ठा rx_sw_desc *d)
अणु
	वापस !(d->dma_addr & RX_UNMAPPED_BUF);
पूर्ण

/**
 *	txq_avail - वापस the number of available slots in a Tx queue
 *	@q: the Tx queue
 *
 *	Returns the number of descriptors in a Tx queue available to ग_लिखो new
 *	packets.
 */
अटल अंतरभूत अचिन्हित पूर्णांक txq_avail(स्थिर काष्ठा sge_txq *q)
अणु
	वापस q->size - 1 - q->in_use;
पूर्ण

/**
 *	fl_cap - वापस the capacity of a मुक्त-buffer list
 *	@fl: the FL
 *
 *	Returns the capacity of a मुक्त-buffer list.  The capacity is less than
 *	the size because one descriptor needs to be left unpopulated, otherwise
 *	HW will think the FL is empty.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fl_cap(स्थिर काष्ठा sge_fl *fl)
अणु
	वापस fl->size - 8;   /* 1 descriptor = 8 buffers */
पूर्ण

/**
 *	fl_starving - वापस whether a Free List is starving.
 *	@adapter: poपूर्णांकer to the adapter
 *	@fl: the Free List
 *
 *	Tests specअगरied Free List to see whether the number of buffers
 *	available to the hardware has falled below our "starvation"
 *	threshold.
 */
अटल अंतरभूत bool fl_starving(स्थिर काष्ठा adapter *adapter,
			       स्थिर काष्ठा sge_fl *fl)
अणु
	स्थिर काष्ठा sge *s = &adapter->sge;

	वापस fl->avail - fl->pend_cred <= s->fl_starve_thres;
पूर्ण

पूर्णांक cxgb4_map_skb(काष्ठा device *dev, स्थिर काष्ठा sk_buff *skb,
		  dma_addr_t *addr)
अणु
	स्थिर skb_frag_t *fp, *end;
	स्थिर काष्ठा skb_shared_info *si;

	*addr = dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, *addr))
		जाओ out_err;

	si = skb_shinfo(skb);
	end = &si->frags[si->nr_frags];

	क्रम (fp = si->frags; fp < end; fp++) अणु
		*++addr = skb_frag_dma_map(dev, fp, 0, skb_frag_size(fp),
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, *addr))
			जाओ unwind;
	पूर्ण
	वापस 0;

unwind:
	जबतक (fp-- > si->frags)
		dma_unmap_page(dev, *--addr, skb_frag_size(fp), DMA_TO_DEVICE);

	dma_unmap_single(dev, addr[-1], skb_headlen(skb), DMA_TO_DEVICE);
out_err:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(cxgb4_map_skb);

अटल व्योम unmap_skb(काष्ठा device *dev, स्थिर काष्ठा sk_buff *skb,
		      स्थिर dma_addr_t *addr)
अणु
	स्थिर skb_frag_t *fp, *end;
	स्थिर काष्ठा skb_shared_info *si;

	dma_unmap_single(dev, *addr++, skb_headlen(skb), DMA_TO_DEVICE);

	si = skb_shinfo(skb);
	end = &si->frags[si->nr_frags];
	क्रम (fp = si->frags; fp < end; fp++)
		dma_unmap_page(dev, *addr++, skb_frag_size(fp), DMA_TO_DEVICE);
पूर्ण

#अगर_घोषित CONFIG_NEED_DMA_MAP_STATE
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
	unmap_skb(skb->dev->dev.parent, skb, (dma_addr_t *)skb->head);
पूर्ण
#पूर्ण_अगर

/**
 *	मुक्त_tx_desc - reclaims Tx descriptors and their buffers
 *	@adap: the adapter
 *	@q: the Tx queue to reclaim descriptors from
 *	@n: the number of descriptors to reclaim
 *	@unmap: whether the buffers should be unmapped क्रम DMA
 *
 *	Reclaims Tx descriptors from an SGE Tx queue and मुक्तs the associated
 *	Tx buffers.  Called with the Tx queue lock held.
 */
व्योम मुक्त_tx_desc(काष्ठा adapter *adap, काष्ठा sge_txq *q,
		  अचिन्हित पूर्णांक n, bool unmap)
अणु
	अचिन्हित पूर्णांक cidx = q->cidx;
	काष्ठा tx_sw_desc *d;

	d = &q->sdesc[cidx];
	जबतक (n--) अणु
		अगर (d->skb) अणु                       /* an SGL is present */
			अगर (unmap && d->addr[0]) अणु
				unmap_skb(adap->pdev_dev, d->skb, d->addr);
				स_रखो(d->addr, 0, माप(d->addr));
			पूर्ण
			dev_consume_skb_any(d->skb);
			d->skb = शून्य;
		पूर्ण
		++d;
		अगर (++cidx == q->size) अणु
			cidx = 0;
			d = q->sdesc;
		पूर्ण
	पूर्ण
	q->cidx = cidx;
पूर्ण

/*
 * Return the number of reclaimable descriptors in a Tx queue.
 */
अटल अंतरभूत पूर्णांक reclaimable(स्थिर काष्ठा sge_txq *q)
अणु
	पूर्णांक hw_cidx = ntohs(READ_ONCE(q->stat->cidx));
	hw_cidx -= q->cidx;
	वापस hw_cidx < 0 ? hw_cidx + q->size : hw_cidx;
पूर्ण

/**
 *	reclaim_completed_tx - reclaims completed TX Descriptors
 *	@adap: the adapter
 *	@q: the Tx queue to reclaim completed descriptors from
 *	@maxreclaim: the maximum number of TX Descriptors to reclaim or -1
 *	@unmap: whether the buffers should be unmapped क्रम DMA
 *
 *	Reclaims Tx Descriptors that the SGE has indicated it has processed,
 *	and मुक्तs the associated buffers अगर possible.  If @max == -1, then
 *	we'll use a defaiult maximum.  Called with the TX Queue locked.
 */
अटल अंतरभूत पूर्णांक reclaim_completed_tx(काष्ठा adapter *adap, काष्ठा sge_txq *q,
				       पूर्णांक maxreclaim, bool unmap)
अणु
	पूर्णांक reclaim = reclaimable(q);

	अगर (reclaim) अणु
		/*
		 * Limit the amount of clean up work we करो at a समय to keep
		 * the Tx lock hold समय O(1).
		 */
		अगर (maxreclaim < 0)
			maxreclaim = MAX_TX_RECLAIM;
		अगर (reclaim > maxreclaim)
			reclaim = maxreclaim;

		मुक्त_tx_desc(adap, q, reclaim, unmap);
		q->in_use -= reclaim;
	पूर्ण

	वापस reclaim;
पूर्ण

/**
 *	cxgb4_reclaim_completed_tx - reclaims completed Tx descriptors
 *	@adap: the adapter
 *	@q: the Tx queue to reclaim completed descriptors from
 *	@unmap: whether the buffers should be unmapped क्रम DMA
 *
 *	Reclaims Tx descriptors that the SGE has indicated it has processed,
 *	and मुक्तs the associated buffers अगर possible.  Called with the Tx
 *	queue locked.
 */
व्योम cxgb4_reclaim_completed_tx(काष्ठा adapter *adap, काष्ठा sge_txq *q,
				bool unmap)
अणु
	(व्योम)reclaim_completed_tx(adap, q, -1, unmap);
पूर्ण
EXPORT_SYMBOL(cxgb4_reclaim_completed_tx);

अटल अंतरभूत पूर्णांक get_buf_size(काष्ठा adapter *adapter,
			       स्थिर काष्ठा rx_sw_desc *d)
अणु
	काष्ठा sge *s = &adapter->sge;
	अचिन्हित पूर्णांक rx_buf_size_idx = d->dma_addr & RX_BUF_SIZE;
	पूर्णांक buf_size;

	चयन (rx_buf_size_idx) अणु
	हाल RX_SMALL_PG_BUF:
		buf_size = PAGE_SIZE;
		अवरोध;

	हाल RX_LARGE_PG_BUF:
		buf_size = PAGE_SIZE << s->fl_pg_order;
		अवरोध;

	हाल RX_SMALL_MTU_BUF:
		buf_size = FL_MTU_SMALL_बफ_मानE(adapter);
		अवरोध;

	हाल RX_LARGE_MTU_BUF:
		buf_size = FL_MTU_LARGE_बफ_मानE(adapter);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस buf_size;
पूर्ण

/**
 *	मुक्त_rx_bufs - मुक्त the Rx buffers on an SGE मुक्त list
 *	@adap: the adapter
 *	@q: the SGE मुक्त list to मुक्त buffers from
 *	@n: how many buffers to मुक्त
 *
 *	Release the next @n buffers on an SGE मुक्त-buffer Rx queue.   The
 *	buffers must be made inaccessible to HW beक्रमe calling this function.
 */
अटल व्योम मुक्त_rx_bufs(काष्ठा adapter *adap, काष्ठा sge_fl *q, पूर्णांक n)
अणु
	जबतक (n--) अणु
		काष्ठा rx_sw_desc *d = &q->sdesc[q->cidx];

		अगर (is_buf_mapped(d))
			dma_unmap_page(adap->pdev_dev, get_buf_addr(d),
				       get_buf_size(adap, d),
				       PCI_DMA_FROMDEVICE);
		put_page(d->page);
		d->page = शून्य;
		अगर (++q->cidx == q->size)
			q->cidx = 0;
		q->avail--;
	पूर्ण
पूर्ण

/**
 *	unmap_rx_buf - unmap the current Rx buffer on an SGE मुक्त list
 *	@adap: the adapter
 *	@q: the SGE मुक्त list
 *
 *	Unmap the current buffer on an SGE मुक्त-buffer Rx queue.   The
 *	buffer must be made inaccessible to HW beक्रमe calling this function.
 *
 *	This is similar to @मुक्त_rx_bufs above but करोes not मुक्त the buffer.
 *	Do note that the FL still loses any further access to the buffer.
 */
अटल व्योम unmap_rx_buf(काष्ठा adapter *adap, काष्ठा sge_fl *q)
अणु
	काष्ठा rx_sw_desc *d = &q->sdesc[q->cidx];

	अगर (is_buf_mapped(d))
		dma_unmap_page(adap->pdev_dev, get_buf_addr(d),
			       get_buf_size(adap, d), PCI_DMA_FROMDEVICE);
	d->page = शून्य;
	अगर (++q->cidx == q->size)
		q->cidx = 0;
	q->avail--;
पूर्ण

अटल अंतरभूत व्योम ring_fl_db(काष्ठा adapter *adap, काष्ठा sge_fl *q)
अणु
	अगर (q->pend_cred >= 8) अणु
		u32 val = adap->params.arch.sge_fl_db;

		अगर (is_t4(adap->params.chip))
			val |= PIDX_V(q->pend_cred / 8);
		अन्यथा
			val |= PIDX_T5_V(q->pend_cred / 8);

		/* Make sure all memory ग_लिखोs to the Free List queue are
		 * committed beक्रमe we tell the hardware about them.
		 */
		wmb();

		/* If we करोn't have access to the new User Doorbell (T5+), use
		 * the old करोorbell mechanism; otherwise use the new BAR2
		 * mechanism.
		 */
		अगर (unlikely(q->bar2_addr == शून्य)) अणु
			t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
				     val | QID_V(q->cntxt_id));
		पूर्ण अन्यथा अणु
			ग_लिखोl(val | QID_V(q->bar2_qid),
			       q->bar2_addr + SGE_UDB_KDOORBELL);

			/* This Write memory Barrier will क्रमce the ग_लिखो to
			 * the User Doorbell area to be flushed.
			 */
			wmb();
		पूर्ण
		q->pend_cred &= 7;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम set_rx_sw_desc(काष्ठा rx_sw_desc *sd, काष्ठा page *pg,
				  dma_addr_t mapping)
अणु
	sd->page = pg;
	sd->dma_addr = mapping;      /* includes size low bits */
पूर्ण

/**
 *	refill_fl - refill an SGE Rx buffer ring
 *	@adap: the adapter
 *	@q: the ring to refill
 *	@n: the number of new buffers to allocate
 *	@gfp: the gfp flags क्रम the allocations
 *
 *	(Re)populate an SGE मुक्त-buffer queue with up to @n new packet buffers,
 *	allocated with the supplied gfp flags.  The caller must assure that
 *	@n करोes not exceed the queue's capacity.  If afterwards the queue is
 *	found critically low mark it as starving in the biपंचांगap of starving FLs.
 *
 *	Returns the number of buffers allocated.
 */
अटल अचिन्हित पूर्णांक refill_fl(काष्ठा adapter *adap, काष्ठा sge_fl *q, पूर्णांक n,
			      gfp_t gfp)
अणु
	काष्ठा sge *s = &adap->sge;
	काष्ठा page *pg;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक cred = q->avail;
	__be64 *d = &q->desc[q->pidx];
	काष्ठा rx_sw_desc *sd = &q->sdesc[q->pidx];
	पूर्णांक node;

#अगर_घोषित CONFIG_DEBUG_FS
	अगर (test_bit(q->cntxt_id - adap->sge.egr_start, adap->sge.blocked_fl))
		जाओ out;
#पूर्ण_अगर

	gfp |= __GFP_NOWARN;
	node = dev_to_node(adap->pdev_dev);

	अगर (s->fl_pg_order == 0)
		जाओ alloc_small_pages;

	/*
	 * Prefer large buffers
	 */
	जबतक (n) अणु
		pg = alloc_pages_node(node, gfp | __GFP_COMP, s->fl_pg_order);
		अगर (unlikely(!pg)) अणु
			q->large_alloc_failed++;
			अवरोध;       /* fall back to single pages */
		पूर्ण

		mapping = dma_map_page(adap->pdev_dev, pg, 0,
				       PAGE_SIZE << s->fl_pg_order,
				       PCI_DMA_FROMDEVICE);
		अगर (unlikely(dma_mapping_error(adap->pdev_dev, mapping))) अणु
			__मुक्त_pages(pg, s->fl_pg_order);
			q->mapping_err++;
			जाओ out;   /* करो not try small pages क्रम this error */
		पूर्ण
		mapping |= RX_LARGE_PG_BUF;
		*d++ = cpu_to_be64(mapping);

		set_rx_sw_desc(sd, pg, mapping);
		sd++;

		q->avail++;
		अगर (++q->pidx == q->size) अणु
			q->pidx = 0;
			sd = q->sdesc;
			d = q->desc;
		पूर्ण
		n--;
	पूर्ण

alloc_small_pages:
	जबतक (n--) अणु
		pg = alloc_pages_node(node, gfp, 0);
		अगर (unlikely(!pg)) अणु
			q->alloc_failed++;
			अवरोध;
		पूर्ण

		mapping = dma_map_page(adap->pdev_dev, pg, 0, PAGE_SIZE,
				       PCI_DMA_FROMDEVICE);
		अगर (unlikely(dma_mapping_error(adap->pdev_dev, mapping))) अणु
			put_page(pg);
			q->mapping_err++;
			जाओ out;
		पूर्ण
		*d++ = cpu_to_be64(mapping);

		set_rx_sw_desc(sd, pg, mapping);
		sd++;

		q->avail++;
		अगर (++q->pidx == q->size) अणु
			q->pidx = 0;
			sd = q->sdesc;
			d = q->desc;
		पूर्ण
	पूर्ण

out:	cred = q->avail - cred;
	q->pend_cred += cred;
	ring_fl_db(adap, q);

	अगर (unlikely(fl_starving(adap, q))) अणु
		smp_wmb();
		q->low++;
		set_bit(q->cntxt_id - adap->sge.egr_start,
			adap->sge.starving_fl);
	पूर्ण

	वापस cred;
पूर्ण

अटल अंतरभूत व्योम __refill_fl(काष्ठा adapter *adap, काष्ठा sge_fl *fl)
अणु
	refill_fl(adap, fl, min(MAX_RX_REFILL, fl_cap(fl) - fl->avail),
		  GFP_ATOMIC);
पूर्ण

/**
 *	alloc_ring - allocate resources क्रम an SGE descriptor ring
 *	@dev: the PCI device's core device
 *	@nelem: the number of descriptors
 *	@elem_size: the size of each descriptor
 *	@sw_size: the size of the SW state associated with each ring element
 *	@phys: the physical address of the allocated ring
 *	@metadata: address of the array holding the SW state क्रम the ring
 *	@stat_size: extra space in HW ring क्रम status inक्रमmation
 *	@node: preferred node क्रम memory allocations
 *
 *	Allocates resources क्रम an SGE descriptor ring, such as Tx queues,
 *	मुक्त buffer lists, or response queues.  Each SGE ring requires
 *	space क्रम its HW descriptors plus, optionally, space क्रम the SW state
 *	associated with each HW entry (the metadata).  The function वापसs
 *	three values: the भव address क्रम the HW ring (the वापस value
 *	of the function), the bus address of the HW ring, and the address
 *	of the SW ring.
 */
अटल व्योम *alloc_ring(काष्ठा device *dev, माप_प्रकार nelem, माप_प्रकार elem_size,
			माप_प्रकार sw_size, dma_addr_t *phys, व्योम *metadata,
			माप_प्रकार stat_size, पूर्णांक node)
अणु
	माप_प्रकार len = nelem * elem_size + stat_size;
	व्योम *s = शून्य;
	व्योम *p = dma_alloc_coherent(dev, len, phys, GFP_KERNEL);

	अगर (!p)
		वापस शून्य;
	अगर (sw_size) अणु
		s = kसुस्मृति_node(sw_size, nelem, GFP_KERNEL, node);

		अगर (!s) अणु
			dma_मुक्त_coherent(dev, len, p, *phys);
			वापस शून्य;
		पूर्ण
	पूर्ण
	अगर (metadata)
		*(व्योम **)metadata = s;
	वापस p;
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
	/* A Direct Scatter Gather List uses 32-bit lengths and 64-bit PCI DMA
	 * addresses.  The DSGL Work Request starts off with a 32-bit DSGL
	 * ULPTX header, then Length0, then Address0, then, क्रम 1 <= i <= N,
	 * repeated sequences of अणु Length[i], Length[i+1], Address[i],
	 * Address[i+1] पूर्ण (this ensures that all addresses are on 64-bit
	 * boundaries).  If N is even, then Length[N+1] should be set to 0 and
	 * Address[N+1] is omitted.
	 *
	 * The following calculation incorporates all of the above.  It's
	 * somewhat hard to follow but, briefly: the "+2" accounts क्रम the
	 * first two flits which include the DSGL header, Length0 and
	 * Address0; the "(3*(n-1))/2" covers the मुख्य body of list entries (3
	 * flits क्रम every pair of the reमुख्यing N) +1 अगर (n-1) is odd; and
	 * finally the "+((n-1)&1)" adds the one reमुख्यing flit needed अगर
	 * (n-1) is odd ...
	 */
	n--;
	वापस (3 * n) / 2 + (n & 1) + 2;
पूर्ण

/**
 *	flits_to_desc - वापसs the num of Tx descriptors क्रम the given flits
 *	@n: the number of flits
 *
 *	Returns the number of Tx descriptors needed क्रम the supplied number
 *	of flits.
 */
अटल अंतरभूत अचिन्हित पूर्णांक flits_to_desc(अचिन्हित पूर्णांक n)
अणु
	BUG_ON(n > SGE_MAX_WR_LEN / 8);
	वापस DIV_ROUND_UP(n, 8);
पूर्ण

/**
 *	is_eth_imm - can an Ethernet packet be sent as immediate data?
 *	@skb: the packet
 *	@chip_ver: chip version
 *
 *	Returns whether an Ethernet packet is small enough to fit as
 *	immediate data. Return value corresponds to headroom required.
 */
अटल अंतरभूत पूर्णांक is_eth_imm(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक chip_ver)
अणु
	पूर्णांक hdrlen = 0;

	अगर (skb->encapsulation && skb_shinfo(skb)->gso_size &&
	    chip_ver > CHELSIO_T5) अणु
		hdrlen = माप(काष्ठा cpl_tx_tnl_lso);
		hdrlen += माप(काष्ठा cpl_tx_pkt_core);
	पूर्ण अन्यथा अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		hdrlen = skb_shinfo(skb)->gso_size ?
			 माप(काष्ठा cpl_tx_pkt_lso_core) : 0;
		hdrlen += माप(काष्ठा cpl_tx_pkt);
	पूर्ण
	अगर (skb->len <= MAX_IMM_TX_PKT_LEN - hdrlen)
		वापस hdrlen;
	वापस 0;
पूर्ण

/**
 *	calc_tx_flits - calculate the number of flits क्रम a packet Tx WR
 *	@skb: the packet
 *	@chip_ver: chip version
 *
 *	Returns the number of flits needed क्रम a Tx WR क्रम the given Ethernet
 *	packet, including the needed WR and CPL headers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_flits(स्थिर काष्ठा sk_buff *skb,
					 अचिन्हित पूर्णांक chip_ver)
अणु
	अचिन्हित पूर्णांक flits;
	पूर्णांक hdrlen = is_eth_imm(skb, chip_ver);

	/* If the skb is small enough, we can pump it out as a work request
	 * with only immediate data.  In that हाल we just have to have the
	 * TX Packet header plus the skb data in the Work Request.
	 */

	अगर (hdrlen)
		वापस DIV_ROUND_UP(skb->len + hdrlen, माप(__be64));

	/* Otherwise, we're going to have to स्थिरruct a Scatter gather list
	 * of the skb body and fragments.  We also include the flits necessary
	 * क्रम the TX Packet Work Request and CPL.  We always have a firmware
	 * Write Header (incorporated as part of the cpl_tx_pkt_lso and
	 * cpl_tx_pkt काष्ठाures), followed by either a TX Packet Write CPL
	 * message or, अगर we're करोing a Large Send Offload, an LSO CPL message
	 * with an embedded TX Packet Write CPL message.
	 */
	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1);
	अगर (skb_shinfo(skb)->gso_size) अणु
		अगर (skb->encapsulation && chip_ver > CHELSIO_T5) अणु
			hdrlen = माप(काष्ठा fw_eth_tx_pkt_wr) +
				 माप(काष्ठा cpl_tx_tnl_lso);
		पूर्ण अन्यथा अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
			u32 pkt_hdrlen;

			pkt_hdrlen = eth_get_headlen(skb->dev, skb->data,
						     skb_headlen(skb));
			hdrlen = माप(काष्ठा fw_eth_tx_eo_wr) +
				 round_up(pkt_hdrlen, 16);
		पूर्ण अन्यथा अणु
			hdrlen = माप(काष्ठा fw_eth_tx_pkt_wr) +
				 माप(काष्ठा cpl_tx_pkt_lso_core);
		पूर्ण

		hdrlen += माप(काष्ठा cpl_tx_pkt_core);
		flits += (hdrlen / माप(__be64));
	पूर्ण अन्यथा अणु
		flits += (माप(काष्ठा fw_eth_tx_pkt_wr) +
			  माप(काष्ठा cpl_tx_pkt_core)) / माप(__be64);
	पूर्ण
	वापस flits;
पूर्ण

/**
 *	calc_tx_descs - calculate the number of Tx descriptors क्रम a packet
 *	@skb: the packet
 *	@chip_ver: chip version
 *
 *	Returns the number of Tx descriptors needed क्रम the given Ethernet
 *	packet, including the needed WR and CPL headers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_descs(स्थिर काष्ठा sk_buff *skb,
					 अचिन्हित पूर्णांक chip_ver)
अणु
	वापस flits_to_desc(calc_tx_flits(skb, chip_ver));
पूर्ण

/**
 *	cxgb4_ग_लिखो_sgl - populate a scatter/gather list क्रम a packet
 *	@skb: the packet
 *	@q: the Tx queue we are writing पूर्णांकo
 *	@sgl: starting location क्रम writing the SGL
 *	@end: poपूर्णांकs right after the end of the SGL
 *	@start: start offset पूर्णांकo skb मुख्य-body data to include in the SGL
 *	@addr: the list of bus addresses क्रम the SGL elements
 *
 *	Generates a gather list क्रम the buffers that make up a packet.
 *	The caller must provide adequate space क्रम the SGL that will be written.
 *	The SGL includes all of the packet's page fragments and the data in its
 *	मुख्य body except क्रम the first @start bytes.  @sgl must be 16-byte
 *	aligned and within a Tx descriptor with available space.  @end poपूर्णांकs
 *	right after the end of the SGL but करोes not account क्रम any potential
 *	wrap around, i.e., @end > @sgl.
 */
व्योम cxgb4_ग_लिखो_sgl(स्थिर काष्ठा sk_buff *skb, काष्ठा sge_txq *q,
		     काष्ठा ulptx_sgl *sgl, u64 *end, अचिन्हित पूर्णांक start,
		     स्थिर dma_addr_t *addr)
अणु
	अचिन्हित पूर्णांक i, len;
	काष्ठा ulptx_sge_pair *to;
	स्थिर काष्ठा skb_shared_info *si = skb_shinfo(skb);
	अचिन्हित पूर्णांक nfrags = si->nr_frags;
	काष्ठा ulptx_sge_pair buf[MAX_SKB_FRAGS / 2 + 1];

	len = skb_headlen(skb) - start;
	अगर (likely(len)) अणु
		sgl->len0 = htonl(len);
		sgl->addr0 = cpu_to_be64(addr[0] + start);
		nfrags++;
	पूर्ण अन्यथा अणु
		sgl->len0 = htonl(skb_frag_size(&si->frags[0]));
		sgl->addr0 = cpu_to_be64(addr[1]);
	पूर्ण

	sgl->cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
			      ULPTX_NSGE_V(nfrags));
	अगर (likely(--nfrags == 0))
		वापस;
	/*
	 * Most of the complनिकासy below deals with the possibility we hit the
	 * end of the queue in the middle of writing the SGL.  For this हाल
	 * only we create the SGL in a temporary buffer and then copy it.
	 */
	to = (u8 *)end > (u8 *)q->stat ? buf : sgl->sge;

	क्रम (i = (nfrags != si->nr_frags); nfrags >= 2; nfrags -= 2, to++) अणु
		to->len[0] = cpu_to_be32(skb_frag_size(&si->frags[i]));
		to->len[1] = cpu_to_be32(skb_frag_size(&si->frags[++i]));
		to->addr[0] = cpu_to_be64(addr[i]);
		to->addr[1] = cpu_to_be64(addr[++i]);
	पूर्ण
	अगर (nfrags) अणु
		to->len[0] = cpu_to_be32(skb_frag_size(&si->frags[i]));
		to->len[1] = cpu_to_be32(0);
		to->addr[0] = cpu_to_be64(addr[i + 1]);
	पूर्ण
	अगर (unlikely((u8 *)end > (u8 *)q->stat)) अणु
		अचिन्हित पूर्णांक part0 = (u8 *)q->stat - (u8 *)sgl->sge, part1;

		अगर (likely(part0))
			स_नकल(sgl->sge, buf, part0);
		part1 = (u8 *)end - (u8 *)q->stat;
		स_नकल(q->desc, (u8 *)buf + part0, part1);
		end = (व्योम *)q->desc + part1;
	पूर्ण
	अगर ((uपूर्णांकptr_t)end & 8)           /* 0-pad to multiple of 16 */
		*end = 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_ग_लिखो_sgl);

/*	cxgb4_ग_लिखो_partial_sgl - populate SGL क्रम partial packet
 *	@skb: the packet
 *	@q: the Tx queue we are writing पूर्णांकo
 *	@sgl: starting location क्रम writing the SGL
 *	@end: poपूर्णांकs right after the end of the SGL
 *	@addr: the list of bus addresses क्रम the SGL elements
 *	@start: start offset in the SKB where partial data starts
 *	@len: length of data from @start to send out
 *
 *	This API will handle sending out partial data of a skb अगर required.
 *	Unlike cxgb4_ग_लिखो_sgl, @start can be any offset पूर्णांकo the skb data,
 *	and @len will decide how much data after @start offset to send out.
 */
व्योम cxgb4_ग_लिखो_partial_sgl(स्थिर काष्ठा sk_buff *skb, काष्ठा sge_txq *q,
			     काष्ठा ulptx_sgl *sgl, u64 *end,
			     स्थिर dma_addr_t *addr, u32 start, u32 len)
अणु
	काष्ठा ulptx_sge_pair buf[MAX_SKB_FRAGS / 2 + 1] = अणु0पूर्ण, *to;
	u32 frag_size, skb_linear_data_len = skb_headlen(skb);
	काष्ठा skb_shared_info *si = skb_shinfo(skb);
	u8 i = 0, frag_idx = 0, nfrags = 0;
	skb_frag_t *frag;

	/* Fill the first SGL either from linear data or from partial
	 * frag based on @start.
	 */
	अगर (unlikely(start < skb_linear_data_len)) अणु
		frag_size = min(len, skb_linear_data_len - start);
		sgl->len0 = htonl(frag_size);
		sgl->addr0 = cpu_to_be64(addr[0] + start);
		len -= frag_size;
		nfrags++;
	पूर्ण अन्यथा अणु
		start -= skb_linear_data_len;
		frag = &si->frags[frag_idx];
		frag_size = skb_frag_size(frag);
		/* find the first frag */
		जबतक (start >= frag_size) अणु
			start -= frag_size;
			frag_idx++;
			frag = &si->frags[frag_idx];
			frag_size = skb_frag_size(frag);
		पूर्ण

		frag_size = min(len, skb_frag_size(frag) - start);
		sgl->len0 = cpu_to_be32(frag_size);
		sgl->addr0 = cpu_to_be64(addr[frag_idx + 1] + start);
		len -= frag_size;
		nfrags++;
		frag_idx++;
	पूर्ण

	/* If the entire partial data fit in one SGL, then send it out
	 * now.
	 */
	अगर (!len)
		जाओ करोne;

	/* Most of the complनिकासy below deals with the possibility we hit the
	 * end of the queue in the middle of writing the SGL.  For this हाल
	 * only we create the SGL in a temporary buffer and then copy it.
	 */
	to = (u8 *)end > (u8 *)q->stat ? buf : sgl->sge;

	/* If the skb couldn't fit in first SGL completely, fill the
	 * rest of the frags in subsequent SGLs. Note that each SGL
	 * pair can store 2 frags.
	 */
	जबतक (len) अणु
		frag_size = min(len, skb_frag_size(&si->frags[frag_idx]));
		to->len[i & 1] = cpu_to_be32(frag_size);
		to->addr[i & 1] = cpu_to_be64(addr[frag_idx + 1]);
		अगर (i && (i & 1))
			to++;
		nfrags++;
		frag_idx++;
		i++;
		len -= frag_size;
	पूर्ण

	/* If we ended in an odd boundary, then set the second SGL's
	 * length in the pair to 0.
	 */
	अगर (i & 1)
		to->len[1] = cpu_to_be32(0);

	/* Copy from temporary buffer to Tx ring, in हाल we hit the
	 * end of the queue in the middle of writing the SGL.
	 */
	अगर (unlikely((u8 *)end > (u8 *)q->stat)) अणु
		u32 part0 = (u8 *)q->stat - (u8 *)sgl->sge, part1;

		अगर (likely(part0))
			स_नकल(sgl->sge, buf, part0);
		part1 = (u8 *)end - (u8 *)q->stat;
		स_नकल(q->desc, (u8 *)buf + part0, part1);
		end = (व्योम *)q->desc + part1;
	पूर्ण

	/* 0-pad to multiple of 16 */
	अगर ((uपूर्णांकptr_t)end & 8)
		*end = 0;
करोne:
	sgl->cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
			ULPTX_NSGE_V(nfrags));
पूर्ण
EXPORT_SYMBOL(cxgb4_ग_लिखो_partial_sgl);

/* This function copies 64 byte coalesced work request to
 * memory mapped BAR2 space. For coalesced WR SGE fetches
 * data from the FIFO instead of from Host.
 */
अटल व्योम cxgb_pio_copy(u64 __iomem *dst, u64 *src)
अणु
	पूर्णांक count = 8;

	जबतक (count) अणु
		ग_लिखोq(*src, dst);
		src++;
		dst++;
		count--;
	पूर्ण
पूर्ण

/**
 *	cxgb4_ring_tx_db - check and potentially ring a Tx queue's करोorbell
 *	@adap: the adapter
 *	@q: the Tx queue
 *	@n: number of new descriptors to give to HW
 *
 *	Ring the करोorbel क्रम a Tx queue.
 */
अंतरभूत व्योम cxgb4_ring_tx_db(काष्ठा adapter *adap, काष्ठा sge_txq *q, पूर्णांक n)
अणु
	/* Make sure that all ग_लिखोs to the TX Descriptors are committed
	 * beक्रमe we tell the hardware about them.
	 */
	wmb();

	/* If we करोn't have access to the new User Doorbell (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(q->bar2_addr == शून्य)) अणु
		u32 val = PIDX_V(n);
		अचिन्हित दीर्घ flags;

		/* For T4 we need to participate in the Doorbell Recovery
		 * mechanism.
		 */
		spin_lock_irqsave(&q->db_lock, flags);
		अगर (!q->db_disabled)
			t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
				     QID_V(q->cntxt_id) | val);
		अन्यथा
			q->db_pidx_inc += n;
		q->db_pidx = q->pidx;
		spin_unlock_irqrestore(&q->db_lock, flags);
	पूर्ण अन्यथा अणु
		u32 val = PIDX_T5_V(n);

		/* T4 and later chips share the same PIDX field offset within
		 * the करोorbell, but T5 and later shrank the field in order to
		 * gain a bit क्रम Doorbell Priority.  The field was असलurdly
		 * large in the first place (14 bits) so we just use the T5
		 * and later limits and warn अगर a Queue ID is too large.
		 */
		WARN_ON(val & DBPRIO_F);

		/* If we're only writing a single TX Descriptor and we can use
		 * Inferred QID रेजिस्टरs, we can use the Write Combining
		 * Gather Buffer; otherwise we use the simple करोorbell.
		 */
		अगर (n == 1 && q->bar2_qid == 0) अणु
			पूर्णांक index = (q->pidx
				     ? (q->pidx - 1)
				     : (q->size - 1));
			u64 *wr = (u64 *)&q->desc[index];

			cxgb_pio_copy((u64 __iomem *)
				      (q->bar2_addr + SGE_UDB_WCDOORBELL),
				      wr);
		पूर्ण अन्यथा अणु
			ग_लिखोl(val | QID_V(q->bar2_qid),
			       q->bar2_addr + SGE_UDB_KDOORBELL);
		पूर्ण

		/* This Write Memory Barrier will क्रमce the ग_लिखो to the User
		 * Doorbell area to be flushed.  This is needed to prevent
		 * ग_लिखोs on dअगरferent CPUs क्रम the same queue from hitting
		 * the adapter out of order.  This is required when some Work
		 * Requests take the Write Combine Gather Buffer path (user
		 * करोorbell area offset [SGE_UDB_WCDOORBELL..+63]) and some
		 * take the traditional path where we simply increment the
		 * PIDX (User Doorbell area SGE_UDB_KDOORBELL) and have the
		 * hardware DMA पढ़ो the actual Work Request.
		 */
		wmb();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cxgb4_ring_tx_db);

/**
 *	cxgb4_अंतरभूत_tx_skb - अंतरभूत a packet's data पूर्णांकo Tx descriptors
 *	@skb: the packet
 *	@q: the Tx queue where the packet will be अंतरभूतd
 *	@pos: starting position in the Tx queue where to अंतरभूत the packet
 *
 *	Inline a packet's contents directly पूर्णांकo Tx descriptors, starting at
 *	the given position within the Tx DMA ring.
 *	Most of the complनिकासy of this operation is dealing with wrap arounds
 *	in the middle of the packet we want to अंतरभूत.
 */
व्योम cxgb4_अंतरभूत_tx_skb(स्थिर काष्ठा sk_buff *skb,
			 स्थिर काष्ठा sge_txq *q, व्योम *pos)
अणु
	पूर्णांक left = (व्योम *)q->stat - pos;
	u64 *p;

	अगर (likely(skb->len <= left)) अणु
		अगर (likely(!skb->data_len))
			skb_copy_from_linear_data(skb, pos, skb->len);
		अन्यथा
			skb_copy_bits(skb, 0, pos, skb->len);
		pos += skb->len;
	पूर्ण अन्यथा अणु
		skb_copy_bits(skb, 0, pos, left);
		skb_copy_bits(skb, left, q->desc, skb->len - left);
		pos = (व्योम *)q->desc + (skb->len - left);
	पूर्ण

	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	अगर ((uपूर्णांकptr_t)p & 8)
		*p = 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_अंतरभूत_tx_skb);

अटल व्योम *अंतरभूत_tx_skb_header(स्थिर काष्ठा sk_buff *skb,
				  स्थिर काष्ठा sge_txq *q,  व्योम *pos,
				  पूर्णांक length)
अणु
	u64 *p;
	पूर्णांक left = (व्योम *)q->stat - pos;

	अगर (likely(length <= left)) अणु
		स_नकल(pos, skb->data, length);
		pos += length;
	पूर्ण अन्यथा अणु
		स_नकल(pos, skb->data, left);
		स_नकल(q->desc, skb->data + left, length - left);
		pos = (व्योम *)q->desc + (length - left);
	पूर्ण
	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	अगर ((uपूर्णांकptr_t)p & 8) अणु
		*p = 0;
		वापस p + 1;
	पूर्ण
	वापस p;
पूर्ण

/*
 * Figure out what HW csum a packet wants and वापस the appropriate control
 * bits.
 */
अटल u64 hwcsum(क्रमागत chip_type chip, स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक csum_type;
	bool inner_hdr_csum = false;
	u16 proto, ver;

	अगर (skb->encapsulation &&
	    (CHELSIO_CHIP_VERSION(chip) > CHELSIO_T5))
		inner_hdr_csum = true;

	अगर (inner_hdr_csum) अणु
		ver = inner_ip_hdr(skb)->version;
		proto = (ver == 4) ? inner_ip_hdr(skb)->protocol :
			inner_ipv6_hdr(skb)->nexthdr;
	पूर्ण अन्यथा अणु
		ver = ip_hdr(skb)->version;
		proto = (ver == 4) ? ip_hdr(skb)->protocol :
			ipv6_hdr(skb)->nexthdr;
	पूर्ण

	अगर (ver == 4) अणु
		अगर (proto == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP;
		अन्यथा अगर (proto == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP;
		अन्यथा अणु
nocsum:			/*
			 * unknown protocol, disable HW csum
			 * and hope a bad packet is detected
			 */
			वापस TXPKT_L4CSUM_DIS_F;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * this करोesn't work with extension headers
		 */
		अगर (proto == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP6;
		अन्यथा अगर (proto == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP6;
		अन्यथा
			जाओ nocsum;
	पूर्ण

	अगर (likely(csum_type >= TX_CSUM_TCPIP)) अणु
		पूर्णांक eth_hdr_len, l4_len;
		u64 hdr_len;

		अगर (inner_hdr_csum) अणु
			/* This allows checksum offload क्रम all encapsulated
			 * packets like GRE etc..
			 */
			l4_len = skb_inner_network_header_len(skb);
			eth_hdr_len = skb_inner_network_offset(skb) - ETH_HLEN;
		पूर्ण अन्यथा अणु
			l4_len = skb_network_header_len(skb);
			eth_hdr_len = skb_network_offset(skb) - ETH_HLEN;
		पूर्ण
		hdr_len = TXPKT_IPHDR_LEN_V(l4_len);

		अगर (CHELSIO_CHIP_VERSION(chip) <= CHELSIO_T5)
			hdr_len |= TXPKT_ETHHDR_LEN_V(eth_hdr_len);
		अन्यथा
			hdr_len |= T6_TXPKT_ETHHDR_LEN_V(eth_hdr_len);
		वापस TXPKT_CSUM_TYPE_V(csum_type) | hdr_len;
	पूर्ण अन्यथा अणु
		पूर्णांक start = skb_transport_offset(skb);

		वापस TXPKT_CSUM_TYPE_V(csum_type) |
			TXPKT_CSUM_START_V(start) |
			TXPKT_CSUM_LOC_V(start + skb->csum_offset);
	पूर्ण
पूर्ण

अटल व्योम eth_txq_stop(काष्ठा sge_eth_txq *q)
अणु
	netअगर_tx_stop_queue(q->txq);
	q->q.stops++;
पूर्ण

अटल अंतरभूत व्योम txq_advance(काष्ठा sge_txq *q, अचिन्हित पूर्णांक n)
अणु
	q->in_use += n;
	q->pidx += n;
	अगर (q->pidx >= q->size)
		q->pidx -= q->size;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
अटल अंतरभूत पूर्णांक
cxgb_fcoe_offload(काष्ठा sk_buff *skb, काष्ठा adapter *adap,
		  स्थिर काष्ठा port_info *pi, u64 *cntrl)
अणु
	स्थिर काष्ठा cxgb_fcoe *fcoe = &pi->fcoe;

	अगर (!(fcoe->flags & CXGB_FCOE_ENABLED))
		वापस 0;

	अगर (skb->protocol != htons(ETH_P_FCOE))
		वापस 0;

	skb_reset_mac_header(skb);
	skb->mac_len = माप(काष्ठा ethhdr);

	skb_set_network_header(skb, skb->mac_len);
	skb_set_transport_header(skb, skb->mac_len + माप(काष्ठा fcoe_hdr));

	अगर (!cxgb_fcoe_sof_eof_supported(adap, skb))
		वापस -ENOTSUPP;

	/* FC CRC offload */
	*cntrl = TXPKT_CSUM_TYPE_V(TX_CSUM_FCOE) |
		     TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F |
		     TXPKT_CSUM_START_V(CXGB_FCOE_TXPKT_CSUM_START) |
		     TXPKT_CSUM_END_V(CXGB_FCOE_TXPKT_CSUM_END) |
		     TXPKT_CSUM_LOC_V(CXGB_FCOE_TXPKT_CSUM_END);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */

/* Returns tunnel type अगर hardware supports offloading of the same.
 * It is called only क्रम T5 and onwards.
 */
क्रमागत cpl_tx_tnl_lso_type cxgb_encap_offload_supported(काष्ठा sk_buff *skb)
अणु
	u8 l4_hdr = 0;
	क्रमागत cpl_tx_tnl_lso_type tnl_type = TX_TNL_TYPE_OPAQUE;
	काष्ठा port_info *pi = netdev_priv(skb->dev);
	काष्ठा adapter *adapter = pi->adapter;

	अगर (skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	    skb->inner_protocol != htons(ETH_P_TEB))
		वापस tnl_type;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस tnl_type;
	पूर्ण

	चयन (l4_hdr) अणु
	हाल IPPROTO_UDP:
		अगर (adapter->vxlan_port == udp_hdr(skb)->dest)
			tnl_type = TX_TNL_TYPE_VXLAN;
		अन्यथा अगर (adapter->geneve_port == udp_hdr(skb)->dest)
			tnl_type = TX_TNL_TYPE_GENEVE;
		अवरोध;
	शेष:
		वापस tnl_type;
	पूर्ण

	वापस tnl_type;
पूर्ण

अटल अंतरभूत व्योम t6_fill_tnl_lso(काष्ठा sk_buff *skb,
				   काष्ठा cpl_tx_tnl_lso *tnl_lso,
				   क्रमागत cpl_tx_tnl_lso_type tnl_type)
अणु
	u32 val;
	पूर्णांक in_eth_xtra_len;
	पूर्णांक l3hdr_len = skb_network_header_len(skb);
	पूर्णांक eth_xtra_len = skb_network_offset(skb) - ETH_HLEN;
	स्थिर काष्ठा skb_shared_info *ssi = skb_shinfo(skb);
	bool v6 = (ip_hdr(skb)->version == 6);

	val = CPL_TX_TNL_LSO_OPCODE_V(CPL_TX_TNL_LSO) |
	      CPL_TX_TNL_LSO_FIRST_F |
	      CPL_TX_TNL_LSO_LAST_F |
	      (v6 ? CPL_TX_TNL_LSO_IPV6OUT_F : 0) |
	      CPL_TX_TNL_LSO_ETHHDRLENOUT_V(eth_xtra_len / 4) |
	      CPL_TX_TNL_LSO_IPHDRLENOUT_V(l3hdr_len / 4) |
	      (v6 ? 0 : CPL_TX_TNL_LSO_IPHDRCHKOUT_F) |
	      CPL_TX_TNL_LSO_IPLENSETOUT_F |
	      (v6 ? 0 : CPL_TX_TNL_LSO_IPIDINCOUT_F);
	tnl_lso->op_to_IpIdSplitOut = htonl(val);

	tnl_lso->IpIdOffsetOut = 0;

	/* Get the tunnel header length */
	val = skb_inner_mac_header(skb) - skb_mac_header(skb);
	in_eth_xtra_len = skb_inner_network_header(skb) -
			  skb_inner_mac_header(skb) - ETH_HLEN;

	चयन (tnl_type) अणु
	हाल TX_TNL_TYPE_VXLAN:
	हाल TX_TNL_TYPE_GENEVE:
		tnl_lso->UdpLenSetOut_to_TnlHdrLen =
			htons(CPL_TX_TNL_LSO_UDPCHKCLROUT_F |
			CPL_TX_TNL_LSO_UDPLENSETOUT_F);
		अवरोध;
	शेष:
		tnl_lso->UdpLenSetOut_to_TnlHdrLen = 0;
		अवरोध;
	पूर्ण

	tnl_lso->UdpLenSetOut_to_TnlHdrLen |=
		 htons(CPL_TX_TNL_LSO_TNLHDRLEN_V(val) |
		       CPL_TX_TNL_LSO_TNLTYPE_V(tnl_type));

	tnl_lso->r1 = 0;

	val = CPL_TX_TNL_LSO_ETHHDRLEN_V(in_eth_xtra_len / 4) |
	      CPL_TX_TNL_LSO_IPV6_V(inner_ip_hdr(skb)->version == 6) |
	      CPL_TX_TNL_LSO_IPHDRLEN_V(skb_inner_network_header_len(skb) / 4) |
	      CPL_TX_TNL_LSO_TCPHDRLEN_V(inner_tcp_hdrlen(skb) / 4);
	tnl_lso->Flow_to_TcpHdrLen = htonl(val);

	tnl_lso->IpIdOffset = htons(0);

	tnl_lso->IpIdSplit_to_Mss = htons(CPL_TX_TNL_LSO_MSS_V(ssi->gso_size));
	tnl_lso->TCPSeqOffset = htonl(0);
	tnl_lso->EthLenOffset_Size = htonl(CPL_TX_TNL_LSO_SIZE_V(skb->len));
पूर्ण

अटल अंतरभूत व्योम *ग_लिखो_tso_wr(काष्ठा adapter *adap, काष्ठा sk_buff *skb,
				 काष्ठा cpl_tx_pkt_lso_core *lso)
अणु
	पूर्णांक eth_xtra_len = skb_network_offset(skb) - ETH_HLEN;
	पूर्णांक l3hdr_len = skb_network_header_len(skb);
	स्थिर काष्ठा skb_shared_info *ssi;
	bool ipv6 = false;

	ssi = skb_shinfo(skb);
	अगर (ssi->gso_type & SKB_GSO_TCPV6)
		ipv6 = true;

	lso->lso_ctrl = htonl(LSO_OPCODE_V(CPL_TX_PKT_LSO) |
			      LSO_FIRST_SLICE_F | LSO_LAST_SLICE_F |
			      LSO_IPV6_V(ipv6) |
			      LSO_ETHHDR_LEN_V(eth_xtra_len / 4) |
			      LSO_IPHDR_LEN_V(l3hdr_len / 4) |
			      LSO_TCPHDR_LEN_V(tcp_hdr(skb)->करोff));
	lso->ipid_ofst = htons(0);
	lso->mss = htons(ssi->gso_size);
	lso->seqno_offset = htonl(0);
	अगर (is_t4(adap->params.chip))
		lso->len = htonl(skb->len);
	अन्यथा
		lso->len = htonl(LSO_T5_XFER_SIZE_V(skb->len));

	वापस (व्योम *)(lso + 1);
पूर्ण

/**
 *	t4_sge_eth_txq_egress_update - handle Ethernet TX Queue update
 *	@adap: the adapter
 *	@eq: the Ethernet TX Queue
 *	@maxreclaim: the maximum number of TX Descriptors to reclaim or -1
 *
 *	We're typically called here to update the state of an Ethernet TX
 *	Queue with respect to the hardware's progress in consuming the TX
 *	Work Requests that we've put on that Egress Queue.  This happens
 *	when we get Egress Queue Update messages and also prophylactically
 *	in regular समयr-based Ethernet TX Queue मुख्यtenance.
 */
पूर्णांक t4_sge_eth_txq_egress_update(काष्ठा adapter *adap, काष्ठा sge_eth_txq *eq,
				 पूर्णांक maxreclaim)
अणु
	अचिन्हित पूर्णांक reclaimed, hw_cidx;
	काष्ठा sge_txq *q = &eq->q;
	पूर्णांक hw_in_use;

	अगर (!q->in_use || !__netअगर_tx_trylock(eq->txq))
		वापस 0;

	/* Reclaim pending completed TX Descriptors. */
	reclaimed = reclaim_completed_tx(adap, &eq->q, maxreclaim, true);

	hw_cidx = ntohs(READ_ONCE(q->stat->cidx));
	hw_in_use = q->pidx - hw_cidx;
	अगर (hw_in_use < 0)
		hw_in_use += q->size;

	/* If the TX Queue is currently stopped and there's now more than half
	 * the queue available, restart it.  Otherwise bail out since the rest
	 * of what we want करो here is with the possibility of shipping any
	 * currently buffered Coalesced TX Work Request.
	 */
	अगर (netअगर_tx_queue_stopped(eq->txq) && hw_in_use < (q->size / 2)) अणु
		netअगर_tx_wake_queue(eq->txq);
		eq->q.restarts++;
	पूर्ण

	__netअगर_tx_unlock(eq->txq);
	वापस reclaimed;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_validate_skb(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     u32 min_pkt_len)
अणु
	u32 max_pkt_len;

	/* The chip min packet length is 10 octets but some firmware
	 * commands have a minimum packet length requirement. So, play
	 * safe and reject anything लघुer than @min_pkt_len.
	 */
	अगर (unlikely(skb->len < min_pkt_len))
		वापस -EINVAL;

	/* Discard the packet अगर the length is greater than mtu */
	max_pkt_len = ETH_HLEN + dev->mtu;

	अगर (skb_vlan_tagged(skb))
		max_pkt_len += VLAN_HLEN;

	अगर (!skb_shinfo(skb)->gso_size && (unlikely(skb->len > max_pkt_len)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम *ग_लिखो_eo_udp_wr(काष्ठा sk_buff *skb, काष्ठा fw_eth_tx_eo_wr *wr,
			     u32 hdr_len)
अणु
	wr->u.udpseg.type = FW_ETH_TX_EO_TYPE_UDPSEG;
	wr->u.udpseg.ethlen = skb_network_offset(skb);
	wr->u.udpseg.iplen = cpu_to_be16(skb_network_header_len(skb));
	wr->u.udpseg.udplen = माप(काष्ठा udphdr);
	wr->u.udpseg.rtplen = 0;
	wr->u.udpseg.r4 = 0;
	अगर (skb_shinfo(skb)->gso_size)
		wr->u.udpseg.mss = cpu_to_be16(skb_shinfo(skb)->gso_size);
	अन्यथा
		wr->u.udpseg.mss = cpu_to_be16(skb->len - hdr_len);
	wr->u.udpseg.schedpktsize = wr->u.udpseg.mss;
	wr->u.udpseg.plen = cpu_to_be32(skb->len - hdr_len);

	वापस (व्योम *)(wr + 1);
पूर्ण

/**
 *	cxgb4_eth_xmit - add a packet to an Ethernet Tx queue
 *	@skb: the packet
 *	@dev: the egress net device
 *
 *	Add a packet to an SGE Ethernet Tx queue.  Runs with softirqs disabled.
 */
अटल netdev_tx_t cxgb4_eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	क्रमागत cpl_tx_tnl_lso_type tnl_type = TX_TNL_TYPE_OPAQUE;
	bool ptp_enabled = is_ptp_enabled(skb, dev);
	अचिन्हित पूर्णांक last_desc, flits, ndesc;
	u32 wr_mid, ctrl0, op, sgl_off = 0;
	स्थिर काष्ठा skb_shared_info *ssi;
	पूर्णांक len, qidx, credits, ret, left;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा fw_eth_tx_eo_wr *eowr;
	काष्ठा fw_eth_tx_pkt_wr *wr;
	काष्ठा cpl_tx_pkt_core *cpl;
	स्थिर काष्ठा port_info *pi;
	bool immediate = false;
	u64 cntrl, *end, *sgl;
	काष्ठा sge_eth_txq *q;
	अचिन्हित पूर्णांक chip_ver;
	काष्ठा adapter *adap;

	ret = cxgb4_validate_skb(skb, dev, ETH_HLEN);
	अगर (ret)
		जाओ out_मुक्त;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	ssi = skb_shinfo(skb);
#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
	अगर (xfrm_offload(skb) && !ssi->gso_size)
		वापस adap->uld[CXGB4_ULD_IPSEC].tx_handler(skb, dev);
#पूर्ण_अगर /* CHELSIO_IPSEC_INLINE */

#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	अगर (cxgb4_is_ktls_skb(skb) &&
	    (skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb))))
		वापस adap->uld[CXGB4_ULD_KTLS].tx_handler(skb, dev);
#पूर्ण_अगर /* CHELSIO_TLS_DEVICE */

	qidx = skb_get_queue_mapping(skb);
	अगर (ptp_enabled) अणु
		अगर (!(adap->ptp_tx_skb)) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			adap->ptp_tx_skb = skb_get(skb);
		पूर्ण अन्यथा अणु
			जाओ out_मुक्त;
		पूर्ण
		q = &adap->sge.ptptxq;
	पूर्ण अन्यथा अणु
		q = &adap->sge.ethtxq[qidx + pi->first_qset];
	पूर्ण
	skb_tx_बारtamp(skb);

	reclaim_completed_tx(adap, &q->q, -1, true);
	cntrl = TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F;

#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
	ret = cxgb_fcoe_offload(skb, adap, pi, &cntrl);
	अगर (unlikely(ret == -EOPNOTSUPP))
		जाओ out_मुक्त;
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */

	chip_ver = CHELSIO_CHIP_VERSION(adap->params.chip);
	flits = calc_tx_flits(skb, chip_ver);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&q->q) - ndesc;

	अगर (unlikely(credits < 0)) अणु
		eth_txq_stop(q);
		dev_err(adap->pdev_dev,
			"%s: Tx ring %u full while queue awake!\n",
			dev->name, qidx);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (is_eth_imm(skb, chip_ver))
		immediate = true;

	अगर (skb->encapsulation && chip_ver > CHELSIO_T5)
		tnl_type = cxgb_encap_offload_supported(skb);

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (!immediate &&
	    unlikely(cxgb4_map_skb(adap->pdev_dev, skb, sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		जाओ out_मुक्त;
	पूर्ण

	wr_mid = FW_WR_LEN16_V(DIV_ROUND_UP(flits, 2));
	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		/* After we're करोne injecting the Work Request क्रम this
		 * packet, we'll be below our "stop threshold" so stop the TX
		 * Queue now and schedule a request क्रम an SGE Egress Queue
		 * Update message. The queue will get started later on when
		 * the firmware processes this Work Request and sends us an
		 * Egress Queue Status Update message indicating that space
		 * has खोलोed up.
		 */
		eth_txq_stop(q);
		अगर (chip_ver > CHELSIO_T5)
			wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	wr = (व्योम *)&q->q.desc[q->q.pidx];
	eowr = (व्योम *)&q->q.desc[q->q.pidx];
	wr->equiq_to_len16 = htonl(wr_mid);
	wr->r3 = cpu_to_be64(0);
	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		end = (u64 *)eowr + flits;
	अन्यथा
		end = (u64 *)wr + flits;

	len = immediate ? skb->len : 0;
	len += माप(*cpl);
	अगर (ssi->gso_size && !(ssi->gso_type & SKB_GSO_UDP_L4)) अणु
		काष्ठा cpl_tx_pkt_lso_core *lso = (व्योम *)(wr + 1);
		काष्ठा cpl_tx_tnl_lso *tnl_lso = (व्योम *)(wr + 1);

		अगर (tnl_type)
			len += माप(*tnl_lso);
		अन्यथा
			len += माप(*lso);

		wr->op_immdlen = htonl(FW_WR_OP_V(FW_ETH_TX_PKT_WR) |
				       FW_WR_IMMDLEN_V(len));
		अगर (tnl_type) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);

			t6_fill_tnl_lso(skb, tnl_lso, tnl_type);
			cpl = (व्योम *)(tnl_lso + 1);
			/* Driver is expected to compute partial checksum that
			 * करोes not include the IP Total Length.
			 */
			अगर (iph->version == 4) अणु
				iph->check = 0;
				iph->tot_len = 0;
				iph->check = ~ip_fast_csum((u8 *)iph, iph->ihl);
			पूर्ण
			अगर (skb->ip_summed == CHECKSUM_PARTIAL)
				cntrl = hwcsum(adap->params.chip, skb);
		पूर्ण अन्यथा अणु
			cpl = ग_लिखो_tso_wr(adap, skb, lso);
			cntrl = hwcsum(adap->params.chip, skb);
		पूर्ण
		sgl = (u64 *)(cpl + 1); /* sgl start here */
		q->tso++;
		q->tx_cso += ssi->gso_segs;
	पूर्ण अन्यथा अगर (ssi->gso_size) अणु
		u64 *start;
		u32 hdrlen;

		hdrlen = eth_get_headlen(dev, skb->data, skb_headlen(skb));
		len += hdrlen;
		wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_ETH_TX_EO_WR) |
					     FW_ETH_TX_EO_WR_IMMDLEN_V(len));
		cpl = ग_लिखो_eo_udp_wr(skb, eowr, hdrlen);
		cntrl = hwcsum(adap->params.chip, skb);

		start = (u64 *)(cpl + 1);
		sgl = (u64 *)अंतरभूत_tx_skb_header(skb, &q->q, (व्योम *)start,
						  hdrlen);
		अगर (unlikely(start > sgl)) अणु
			left = (u8 *)end - (u8 *)q->q.stat;
			end = (व्योम *)q->q.desc + left;
		पूर्ण
		sgl_off = hdrlen;
		q->uso++;
		q->tx_cso += ssi->gso_segs;
	पूर्ण अन्यथा अणु
		अगर (ptp_enabled)
			op = FW_PTP_TX_PKT_WR;
		अन्यथा
			op = FW_ETH_TX_PKT_WR;
		wr->op_immdlen = htonl(FW_WR_OP_V(op) |
				       FW_WR_IMMDLEN_V(len));
		cpl = (व्योम *)(wr + 1);
		sgl = (u64 *)(cpl + 1);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			cntrl = hwcsum(adap->params.chip, skb) |
				TXPKT_IPCSUM_DIS_F;
			q->tx_cso++;
		पूर्ण
	पूर्ण

	अगर (unlikely((u8 *)sgl >= (u8 *)q->q.stat)) अणु
		/* If current position is alपढ़ोy at the end of the
		 * txq, reset the current to poपूर्णांक to start of the queue
		 * and update the end ptr as well.
		 */
		left = (u8 *)end - (u8 *)q->q.stat;
		end = (व्योम *)q->q.desc + left;
		sgl = (व्योम *)q->q.desc;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		q->vlan_ins++;
		cntrl |= TXPKT_VLAN_VLD_F | TXPKT_VLAN_V(skb_vlan_tag_get(skb));
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
		अगर (skb->protocol == htons(ETH_P_FCOE))
			cntrl |= TXPKT_VLAN_V(
				 ((skb->priority & 0x7) << VLAN_PRIO_SHIFT));
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
	पूर्ण

	ctrl0 = TXPKT_OPCODE_V(CPL_TX_PKT_XT) | TXPKT_INTF_V(pi->tx_chan) |
		TXPKT_PF_V(adap->pf);
	अगर (ptp_enabled)
		ctrl0 |= TXPKT_TSTAMP_F;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	अगर (is_t4(adap->params.chip))
		ctrl0 |= TXPKT_OVLAN_IDX_V(q->dcb_prio);
	अन्यथा
		ctrl0 |= TXPKT_T5_OVLAN_IDX_V(q->dcb_prio);
#पूर्ण_अगर
	cpl->ctrl0 = htonl(ctrl0);
	cpl->pack = htons(0);
	cpl->len = htons(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

	अगर (immediate) अणु
		cxgb4_अंतरभूत_tx_skb(skb, &q->q, sgl);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अणु
		cxgb4_ग_लिखो_sgl(skb, &q->q, (व्योम *)sgl, end, sgl_off,
				sgl_sdesc->addr);
		skb_orphan(skb);
		sgl_sdesc->skb = skb;
	पूर्ण

	txq_advance(&q->q, ndesc);

	cxgb4_ring_tx_db(adap, &q->q, ndesc);
	वापस NETDEV_TX_OK;

out_मुक्त:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* Constants ... */
क्रमागत अणु
	/* Egress Queue sizes, producer and consumer indices are all in units
	 * of Egress Context Units bytes.  Note that as far as the hardware is
	 * concerned, the मुक्त list is an Egress Queue (the host produces मुक्त
	 * buffers which the hardware consumes) and मुक्त list entries are
	 * 64-bit PCI DMA addresses.
	 */
	EQ_UNIT = SGE_EQ_IDXSIZE,
	FL_PER_EQ_UNIT = EQ_UNIT / माप(__be64),
	TXD_PER_EQ_UNIT = EQ_UNIT / माप(__be64),

	T4VF_ETHTXQ_MAX_HDR = (माप(काष्ठा fw_eth_tx_pkt_vm_wr) +
			       माप(काष्ठा cpl_tx_pkt_lso_core) +
			       माप(काष्ठा cpl_tx_pkt_core)) / माप(__be64),
पूर्ण;

/**
 *	t4vf_is_eth_imm - can an Ethernet packet be sent as immediate data?
 *	@skb: the packet
 *
 *	Returns whether an Ethernet packet is small enough to fit completely as
 *	immediate data.
 */
अटल अंतरभूत पूर्णांक t4vf_is_eth_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	/* The VF Driver uses the FW_ETH_TX_PKT_VM_WR firmware Work Request
	 * which करोes not accommodate immediate data.  We could dike out all
	 * of the support code क्रम immediate data but that would tie our hands
	 * too much अगर we ever want to enhace the firmware.  It would also
	 * create more dअगरferences between the PF and VF Drivers.
	 */
	वापस false;
पूर्ण

/**
 *	t4vf_calc_tx_flits - calculate the number of flits क्रम a packet TX WR
 *	@skb: the packet
 *
 *	Returns the number of flits needed क्रम a TX Work Request क्रम the
 *	given Ethernet packet, including the needed WR and CPL headers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक t4vf_calc_tx_flits(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits;

	/* If the skb is small enough, we can pump it out as a work request
	 * with only immediate data.  In that हाल we just have to have the
	 * TX Packet header plus the skb data in the Work Request.
	 */
	अगर (t4vf_is_eth_imm(skb))
		वापस DIV_ROUND_UP(skb->len + माप(काष्ठा cpl_tx_pkt),
				    माप(__be64));

	/* Otherwise, we're going to have to स्थिरruct a Scatter gather list
	 * of the skb body and fragments.  We also include the flits necessary
	 * क्रम the TX Packet Work Request and CPL.  We always have a firmware
	 * Write Header (incorporated as part of the cpl_tx_pkt_lso and
	 * cpl_tx_pkt काष्ठाures), followed by either a TX Packet Write CPL
	 * message or, अगर we're करोing a Large Send Offload, an LSO CPL message
	 * with an embedded TX Packet Write CPL message.
	 */
	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1);
	अगर (skb_shinfo(skb)->gso_size)
		flits += (माप(काष्ठा fw_eth_tx_pkt_vm_wr) +
			  माप(काष्ठा cpl_tx_pkt_lso_core) +
			  माप(काष्ठा cpl_tx_pkt_core)) / माप(__be64);
	अन्यथा
		flits += (माप(काष्ठा fw_eth_tx_pkt_vm_wr) +
			  माप(काष्ठा cpl_tx_pkt_core)) / माप(__be64);
	वापस flits;
पूर्ण

/**
 *	cxgb4_vf_eth_xmit - add a packet to an Ethernet TX queue
 *	@skb: the packet
 *	@dev: the egress net device
 *
 *	Add a packet to an SGE Ethernet TX queue.  Runs with softirqs disabled.
 */
अटल netdev_tx_t cxgb4_vf_eth_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक last_desc, flits, ndesc;
	स्थिर काष्ठा skb_shared_info *ssi;
	काष्ठा fw_eth_tx_pkt_vm_wr *wr;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा cpl_tx_pkt_core *cpl;
	स्थिर काष्ठा port_info *pi;
	काष्ठा sge_eth_txq *txq;
	काष्ठा adapter *adapter;
	पूर्णांक qidx, credits, ret;
	माप_प्रकार fw_hdr_copy_len;
	अचिन्हित पूर्णांक chip_ver;
	u64 cntrl, *end;
	u32 wr_mid;

	/* The chip minimum packet length is 10 octets but the firmware
	 * command that we are using requires that we copy the Ethernet header
	 * (including the VLAN tag) पूर्णांकo the header so we reject anything
	 * smaller than that ...
	 */
	fw_hdr_copy_len = माप(wr->ethmacdst) + माप(wr->ethmacsrc) +
			  माप(wr->ethtype) + माप(wr->vlantci);
	ret = cxgb4_validate_skb(skb, dev, fw_hdr_copy_len);
	अगर (ret)
		जाओ out_मुक्त;

	/* Figure out which TX Queue we're going to use. */
	pi = netdev_priv(dev);
	adapter = pi->adapter;
	qidx = skb_get_queue_mapping(skb);
	WARN_ON(qidx >= pi->nqsets);
	txq = &adapter->sge.ethtxq[pi->first_qset + qidx];

	/* Take this opportunity to reclaim any TX Descriptors whose DMA
	 * transfers have completed.
	 */
	reclaim_completed_tx(adapter, &txq->q, -1, true);

	/* Calculate the number of flits and TX Descriptors we're going to
	 * need aदीर्घ with how many TX Descriptors will be left over after
	 * we inject our Work Request.
	 */
	flits = t4vf_calc_tx_flits(skb);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&txq->q) - ndesc;

	अगर (unlikely(credits < 0)) अणु
		/* Not enough room क्रम this packet's Work Request.  Stop the
		 * TX Queue and वापस a "busy" condition.  The queue will get
		 * started later on when the firmware inक्रमms us that space
		 * has खोलोed up.
		 */
		eth_txq_stop(txq);
		dev_err(adapter->pdev_dev,
			"%s: TX ring %u full while queue awake!\n",
			dev->name, qidx);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	last_desc = txq->q.pidx + ndesc - 1;
	अगर (last_desc >= txq->q.size)
		last_desc -= txq->q.size;
	sgl_sdesc = &txq->q.sdesc[last_desc];

	अगर (!t4vf_is_eth_imm(skb) &&
	    unlikely(cxgb4_map_skb(adapter->pdev_dev, skb,
				   sgl_sdesc->addr) < 0)) अणु
		/* We need to map the skb पूर्णांकo PCI DMA space (because it can't
		 * be in-lined directly पूर्णांकo the Work Request) and the mapping
		 * operation failed.  Record the error and drop the packet.
		 */
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		txq->mapping_err++;
		जाओ out_मुक्त;
	पूर्ण

	chip_ver = CHELSIO_CHIP_VERSION(adapter->params.chip);
	wr_mid = FW_WR_LEN16_V(DIV_ROUND_UP(flits, 2));
	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		/* After we're करोne injecting the Work Request क्रम this
		 * packet, we'll be below our "stop threshold" so stop the TX
		 * Queue now and schedule a request क्रम an SGE Egress Queue
		 * Update message.  The queue will get started later on when
		 * the firmware processes this Work Request and sends us an
		 * Egress Queue Status Update message indicating that space
		 * has खोलोed up.
		 */
		eth_txq_stop(txq);
		अगर (chip_ver > CHELSIO_T5)
			wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	/* Start filling in our Work Request.  Note that we करो _not_ handle
	 * the WR Header wrapping around the TX Descriptor Ring.  If our
	 * maximum header size ever exceeds one TX Descriptor, we'll need to
	 * करो something अन्यथा here.
	 */
	WARN_ON(DIV_ROUND_UP(T4VF_ETHTXQ_MAX_HDR, TXD_PER_EQ_UNIT) > 1);
	wr = (व्योम *)&txq->q.desc[txq->q.pidx];
	wr->equiq_to_len16 = cpu_to_be32(wr_mid);
	wr->r3[0] = cpu_to_be32(0);
	wr->r3[1] = cpu_to_be32(0);
	skb_copy_from_linear_data(skb, (व्योम *)wr->ethmacdst, fw_hdr_copy_len);
	end = (u64 *)wr + flits;

	/* If this is a Large Send Offload packet we'll put in an LSO CPL
	 * message with an encapsulated TX Packet CPL message.  Otherwise we
	 * just use a TX Packet CPL message.
	 */
	ssi = skb_shinfo(skb);
	अगर (ssi->gso_size) अणु
		काष्ठा cpl_tx_pkt_lso_core *lso = (व्योम *)(wr + 1);
		bool v6 = (ssi->gso_type & SKB_GSO_TCPV6) != 0;
		पूर्णांक l3hdr_len = skb_network_header_len(skb);
		पूर्णांक eth_xtra_len = skb_network_offset(skb) - ETH_HLEN;

		wr->op_immdlen =
			cpu_to_be32(FW_WR_OP_V(FW_ETH_TX_PKT_VM_WR) |
				    FW_WR_IMMDLEN_V(माप(*lso) +
						    माप(*cpl)));
		 /* Fill in the LSO CPL message. */
		lso->lso_ctrl =
			cpu_to_be32(LSO_OPCODE_V(CPL_TX_PKT_LSO) |
				    LSO_FIRST_SLICE_F |
				    LSO_LAST_SLICE_F |
				    LSO_IPV6_V(v6) |
				    LSO_ETHHDR_LEN_V(eth_xtra_len / 4) |
				    LSO_IPHDR_LEN_V(l3hdr_len / 4) |
				    LSO_TCPHDR_LEN_V(tcp_hdr(skb)->करोff));
		lso->ipid_ofst = cpu_to_be16(0);
		lso->mss = cpu_to_be16(ssi->gso_size);
		lso->seqno_offset = cpu_to_be32(0);
		अगर (is_t4(adapter->params.chip))
			lso->len = cpu_to_be32(skb->len);
		अन्यथा
			lso->len = cpu_to_be32(LSO_T5_XFER_SIZE_V(skb->len));

		/* Set up TX Packet CPL poपूर्णांकer, control word and perक्रमm
		 * accounting.
		 */
		cpl = (व्योम *)(lso + 1);

		अगर (chip_ver <= CHELSIO_T5)
			cntrl = TXPKT_ETHHDR_LEN_V(eth_xtra_len);
		अन्यथा
			cntrl = T6_TXPKT_ETHHDR_LEN_V(eth_xtra_len);

		cntrl |= TXPKT_CSUM_TYPE_V(v6 ?
					   TX_CSUM_TCPIP6 : TX_CSUM_TCPIP) |
			 TXPKT_IPHDR_LEN_V(l3hdr_len);
		txq->tso++;
		txq->tx_cso += ssi->gso_segs;
	पूर्ण अन्यथा अणु
		पूर्णांक len;

		len = (t4vf_is_eth_imm(skb)
		       ? skb->len + माप(*cpl)
		       : माप(*cpl));
		wr->op_immdlen =
			cpu_to_be32(FW_WR_OP_V(FW_ETH_TX_PKT_VM_WR) |
				    FW_WR_IMMDLEN_V(len));

		/* Set up TX Packet CPL poपूर्णांकer, control word and perक्रमm
		 * accounting.
		 */
		cpl = (व्योम *)(wr + 1);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			cntrl = hwcsum(adapter->params.chip, skb) |
				TXPKT_IPCSUM_DIS_F;
			txq->tx_cso++;
		पूर्ण अन्यथा अणु
			cntrl = TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F;
		पूर्ण
	पूर्ण

	/* If there's a VLAN tag present, add that to the list of things to
	 * करो in this Work Request.
	 */
	अगर (skb_vlan_tag_present(skb)) अणु
		txq->vlan_ins++;
		cntrl |= TXPKT_VLAN_VLD_F | TXPKT_VLAN_V(skb_vlan_tag_get(skb));
	पूर्ण

	 /* Fill in the TX Packet CPL message header. */
	cpl->ctrl0 = cpu_to_be32(TXPKT_OPCODE_V(CPL_TX_PKT_XT) |
				 TXPKT_INTF_V(pi->port_id) |
				 TXPKT_PF_V(0));
	cpl->pack = cpu_to_be16(0);
	cpl->len = cpu_to_be16(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

	/* Fill in the body of the TX Packet CPL message with either in-lined
	 * data or a Scatter/Gather List.
	 */
	अगर (t4vf_is_eth_imm(skb)) अणु
		/* In-line the packet's data and free the skb since we don't
		 * need it any दीर्घer.
		 */
		cxgb4_अंतरभूत_tx_skb(skb, &txq->q, cpl + 1);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अणु
		/* Write the skb's Scatter/Gather list पूर्णांकo the TX Packet CPL
		 * message and retain a poपूर्णांकer to the skb so we can मुक्त it
		 * later when its DMA completes.  (We store the skb poपूर्णांकer
		 * in the Software Descriptor corresponding to the last TX
		 * Descriptor used by the Work Request.)
		 *
		 * The retained skb will be मुक्तd when the corresponding TX
		 * Descriptors are reclaimed after their DMAs complete.
		 * However, this could take quite a जबतक since, in general,
		 * the hardware is set up to be lazy about sending DMA
		 * completion notअगरications to us and we mostly perक्रमm TX
		 * reclaims in the transmit routine.
		 *
		 * This is good क्रम perक्रमmamce but means that we rely on new
		 * TX packets arriving to run the deकाष्ठाors of completed
		 * packets, which खोलो up space in their sockets' send queues.
		 * Someबार we करो not get such new packets causing TX to
		 * stall.  A single UDP transmitter is a good example of this
		 * situation.  We have a clean up समयr that periodically
		 * reclaims completed packets but it करोesn't run often enough
		 * (nor करो we want it to) to prevent lengthy stalls.  A
		 * solution to this problem is to run the deकाष्ठाor early,
		 * after the packet is queued but beक्रमe it's DMAd.  A con is
		 * that we lie to socket memory accounting, but the amount of
		 * extra memory is reasonable (limited by the number of TX
		 * descriptors), the packets करो actually get मुक्तd quickly by
		 * new packets almost always, and क्रम protocols like TCP that
		 * रुको क्रम acks to really मुक्त up the data the extra memory
		 * is even less.  On the positive side we run the deकाष्ठाors
		 * on the sending CPU rather than on a potentially dअगरferent
		 * completing CPU, usually a good thing.
		 *
		 * Run the deकाष्ठाor beक्रमe telling the DMA engine about the
		 * packet to make sure it करोesn't complete and get मुक्तd
		 * prematurely.
		 */
		काष्ठा ulptx_sgl *sgl = (काष्ठा ulptx_sgl *)(cpl + 1);
		काष्ठा sge_txq *tq = &txq->q;

		/* If the Work Request header was an exact multiple of our TX
		 * Descriptor length, then it's possible that the starting SGL
		 * poपूर्णांकer lines up exactly with the end of our TX Descriptor
		 * ring.  If that's the हाल, wrap around to the beginning
		 * here ...
		 */
		अगर (unlikely((व्योम *)sgl == (व्योम *)tq->stat)) अणु
			sgl = (व्योम *)tq->desc;
			end = (व्योम *)((व्योम *)tq->desc +
				       ((व्योम *)end - (व्योम *)tq->stat));
		पूर्ण

		cxgb4_ग_लिखो_sgl(skb, tq, sgl, end, 0, sgl_sdesc->addr);
		skb_orphan(skb);
		sgl_sdesc->skb = skb;
	पूर्ण

	/* Advance our पूर्णांकernal TX Queue state, tell the hardware about
	 * the new TX descriptors and वापस success.
	 */
	txq_advance(&txq->q, ndesc);

	cxgb4_ring_tx_db(adapter, &txq->q, ndesc);
	वापस NETDEV_TX_OK;

out_मुक्त:
	/* An error of some sort happened.  Free the TX skb and tell the
	 * OS that we've "dealt" with the packet ...
	 */
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * reclaim_completed_tx_imm - reclaim completed control-queue Tx descs
 * @q: the SGE control Tx queue
 *
 * This is a variant of cxgb4_reclaim_completed_tx() that is used
 * क्रम Tx queues that send only immediate data (presently just
 * the control queues) and	thus करो not have any sk_buffs to release.
 */
अटल अंतरभूत व्योम reclaim_completed_tx_imm(काष्ठा sge_txq *q)
अणु
	पूर्णांक hw_cidx = ntohs(READ_ONCE(q->stat->cidx));
	पूर्णांक reclaim = hw_cidx - q->cidx;

	अगर (reclaim < 0)
		reclaim += q->size;

	q->in_use -= reclaim;
	q->cidx = hw_cidx;
पूर्ण

अटल अंतरभूत व्योम eosw_txq_advance_index(u32 *idx, u32 n, u32 max)
अणु
	u32 val = *idx + n;

	अगर (val >= max)
		val -= max;

	*idx = val;
पूर्ण

व्योम cxgb4_eosw_txq_मुक्त_desc(काष्ठा adapter *adap,
			      काष्ठा sge_eosw_txq *eosw_txq, u32 ndesc)
अणु
	काष्ठा tx_sw_desc *d;

	d = &eosw_txq->desc[eosw_txq->last_cidx];
	जबतक (ndesc--) अणु
		अगर (d->skb) अणु
			अगर (d->addr[0]) अणु
				unmap_skb(adap->pdev_dev, d->skb, d->addr);
				स_रखो(d->addr, 0, माप(d->addr));
			पूर्ण
			dev_consume_skb_any(d->skb);
			d->skb = शून्य;
		पूर्ण
		eosw_txq_advance_index(&eosw_txq->last_cidx, 1,
				       eosw_txq->ndesc);
		d = &eosw_txq->desc[eosw_txq->last_cidx];
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम eosw_txq_advance(काष्ठा sge_eosw_txq *eosw_txq, u32 n)
अणु
	eosw_txq_advance_index(&eosw_txq->pidx, n, eosw_txq->ndesc);
	eosw_txq->inuse += n;
पूर्ण

अटल अंतरभूत पूर्णांक eosw_txq_enqueue(काष्ठा sge_eosw_txq *eosw_txq,
				   काष्ठा sk_buff *skb)
अणु
	अगर (eosw_txq->inuse == eosw_txq->ndesc)
		वापस -ENOMEM;

	eosw_txq->desc[eosw_txq->pidx].skb = skb;
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *eosw_txq_peek(काष्ठा sge_eosw_txq *eosw_txq)
अणु
	वापस eosw_txq->desc[eosw_txq->last_pidx].skb;
पूर्ण

अटल अंतरभूत u8 ethofld_calc_tx_flits(काष्ठा adapter *adap,
				       काष्ठा sk_buff *skb, u32 hdr_len)
अणु
	u8 flits, nsgl = 0;
	u32 wrlen;

	wrlen = माप(काष्ठा fw_eth_tx_eo_wr) + माप(काष्ठा cpl_tx_pkt_core);
	अगर (skb_shinfo(skb)->gso_size &&
	    !(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4))
		wrlen += माप(काष्ठा cpl_tx_pkt_lso_core);

	wrlen += roundup(hdr_len, 16);

	/* Packet headers + WR + CPLs */
	flits = DIV_ROUND_UP(wrlen, 8);

	अगर (skb_shinfo(skb)->nr_frags > 0) अणु
		अगर (skb_headlen(skb) - hdr_len)
			nsgl = sgl_len(skb_shinfo(skb)->nr_frags + 1);
		अन्यथा
			nsgl = sgl_len(skb_shinfo(skb)->nr_frags);
	पूर्ण अन्यथा अगर (skb->len - hdr_len) अणु
		nsgl = sgl_len(1);
	पूर्ण

	वापस flits + nsgl;
पूर्ण

अटल व्योम *ग_लिखो_eo_wr(काष्ठा adapter *adap, काष्ठा sge_eosw_txq *eosw_txq,
			 काष्ठा sk_buff *skb, काष्ठा fw_eth_tx_eo_wr *wr,
			 u32 hdr_len, u32 wrlen)
अणु
	स्थिर काष्ठा skb_shared_info *ssi = skb_shinfo(skb);
	काष्ठा cpl_tx_pkt_core *cpl;
	u32 immd_len, wrlen16;
	bool compl = false;
	u8 ver, proto;

	ver = ip_hdr(skb)->version;
	proto = (ver == 6) ? ipv6_hdr(skb)->nexthdr : ip_hdr(skb)->protocol;

	wrlen16 = DIV_ROUND_UP(wrlen, 16);
	immd_len = माप(काष्ठा cpl_tx_pkt_core);
	अगर (skb_shinfo(skb)->gso_size &&
	    !(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4))
		immd_len += माप(काष्ठा cpl_tx_pkt_lso_core);
	immd_len += hdr_len;

	अगर (!eosw_txq->ncompl ||
	    (eosw_txq->last_compl + wrlen16) >=
	    (adap->params.ofldq_wr_cred / 2)) अणु
		compl = true;
		eosw_txq->ncompl++;
		eosw_txq->last_compl = 0;
	पूर्ण

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_ETH_TX_EO_WR) |
				     FW_ETH_TX_EO_WR_IMMDLEN_V(immd_len) |
				     FW_WR_COMPL_V(compl));
	wr->equiq_to_len16 = cpu_to_be32(FW_WR_LEN16_V(wrlen16) |
					 FW_WR_FLOWID_V(eosw_txq->hwtid));
	wr->r3 = 0;
	अगर (proto == IPPROTO_UDP) अणु
		cpl = ग_लिखो_eo_udp_wr(skb, wr, hdr_len);
	पूर्ण अन्यथा अणु
		wr->u.tcpseg.type = FW_ETH_TX_EO_TYPE_TCPSEG;
		wr->u.tcpseg.ethlen = skb_network_offset(skb);
		wr->u.tcpseg.iplen = cpu_to_be16(skb_network_header_len(skb));
		wr->u.tcpseg.tcplen = tcp_hdrlen(skb);
		wr->u.tcpseg.tsclk_tsoff = 0;
		wr->u.tcpseg.r4 = 0;
		wr->u.tcpseg.r5 = 0;
		wr->u.tcpseg.plen = cpu_to_be32(skb->len - hdr_len);

		अगर (ssi->gso_size) अणु
			काष्ठा cpl_tx_pkt_lso_core *lso = (व्योम *)(wr + 1);

			wr->u.tcpseg.mss = cpu_to_be16(ssi->gso_size);
			cpl = ग_लिखो_tso_wr(adap, skb, lso);
		पूर्ण अन्यथा अणु
			wr->u.tcpseg.mss = cpu_to_be16(0xffff);
			cpl = (व्योम *)(wr + 1);
		पूर्ण
	पूर्ण

	eosw_txq->cred -= wrlen16;
	eosw_txq->last_compl += wrlen16;
	वापस cpl;
पूर्ण

अटल पूर्णांक ethofld_hard_xmit(काष्ठा net_device *dev,
			     काष्ठा sge_eosw_txq *eosw_txq)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	u32 wrlen, wrlen16, hdr_len, data_len;
	क्रमागत sge_eosw_state next_state;
	u64 cntrl, *start, *end, *sgl;
	काष्ठा sge_eohw_txq *eohw_txq;
	काष्ठा cpl_tx_pkt_core *cpl;
	काष्ठा fw_eth_tx_eo_wr *wr;
	bool skip_eotx_wr = false;
	काष्ठा tx_sw_desc *d;
	काष्ठा sk_buff *skb;
	पूर्णांक left, ret = 0;
	u8 flits, ndesc;

	eohw_txq = &adap->sge.eohw_txq[eosw_txq->hwqid];
	spin_lock(&eohw_txq->lock);
	reclaim_completed_tx_imm(&eohw_txq->q);

	d = &eosw_txq->desc[eosw_txq->last_pidx];
	skb = d->skb;
	skb_tx_बारtamp(skb);

	wr = (काष्ठा fw_eth_tx_eo_wr *)&eohw_txq->q.desc[eohw_txq->q.pidx];
	अगर (unlikely(eosw_txq->state != CXGB4_EO_STATE_ACTIVE &&
		     eosw_txq->last_pidx == eosw_txq->flowc_idx)) अणु
		hdr_len = skb->len;
		data_len = 0;
		flits = DIV_ROUND_UP(hdr_len, 8);
		अगर (eosw_txq->state == CXGB4_EO_STATE_FLOWC_OPEN_SEND)
			next_state = CXGB4_EO_STATE_FLOWC_OPEN_REPLY;
		अन्यथा
			next_state = CXGB4_EO_STATE_FLOWC_CLOSE_REPLY;
		skip_eotx_wr = true;
	पूर्ण अन्यथा अणु
		hdr_len = eth_get_headlen(dev, skb->data, skb_headlen(skb));
		data_len = skb->len - hdr_len;
		flits = ethofld_calc_tx_flits(adap, skb, hdr_len);
	पूर्ण
	ndesc = flits_to_desc(flits);
	wrlen = flits * 8;
	wrlen16 = DIV_ROUND_UP(wrlen, 16);

	left = txq_avail(&eohw_txq->q) - ndesc;

	/* If there are no descriptors left in hardware queues or no
	 * CPL credits left in software queues, then रुको क्रम them
	 * to come back and retry again. Note that we always request
	 * क्रम credits update via पूर्णांकerrupt क्रम every half credits
	 * consumed. So, the पूर्णांकerrupt will eventually restore the
	 * credits and invoke the Tx path again.
	 */
	अगर (unlikely(left < 0 || wrlen16 > eosw_txq->cred)) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	अगर (unlikely(skip_eotx_wr)) अणु
		start = (u64 *)wr;
		eosw_txq->state = next_state;
		eosw_txq->cred -= wrlen16;
		eosw_txq->ncompl++;
		eosw_txq->last_compl = 0;
		जाओ ग_लिखो_wr_headers;
	पूर्ण

	cpl = ग_लिखो_eo_wr(adap, eosw_txq, skb, wr, hdr_len, wrlen);
	cntrl = hwcsum(adap->params.chip, skb);
	अगर (skb_vlan_tag_present(skb))
		cntrl |= TXPKT_VLAN_VLD_F | TXPKT_VLAN_V(skb_vlan_tag_get(skb));

	cpl->ctrl0 = cpu_to_be32(TXPKT_OPCODE_V(CPL_TX_PKT_XT) |
				 TXPKT_INTF_V(pi->tx_chan) |
				 TXPKT_PF_V(adap->pf));
	cpl->pack = 0;
	cpl->len = cpu_to_be16(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

	start = (u64 *)(cpl + 1);

ग_लिखो_wr_headers:
	sgl = (u64 *)अंतरभूत_tx_skb_header(skb, &eohw_txq->q, (व्योम *)start,
					  hdr_len);
	अगर (data_len) अणु
		ret = cxgb4_map_skb(adap->pdev_dev, skb, d->addr);
		अगर (unlikely(ret)) अणु
			स_रखो(d->addr, 0, माप(d->addr));
			eohw_txq->mapping_err++;
			जाओ out_unlock;
		पूर्ण

		end = (u64 *)wr + flits;
		अगर (unlikely(start > sgl)) अणु
			left = (u8 *)end - (u8 *)eohw_txq->q.stat;
			end = (व्योम *)eohw_txq->q.desc + left;
		पूर्ण

		अगर (unlikely((u8 *)sgl >= (u8 *)eohw_txq->q.stat)) अणु
			/* If current position is alपढ़ोy at the end of the
			 * txq, reset the current to poपूर्णांक to start of the queue
			 * and update the end ptr as well.
			 */
			left = (u8 *)end - (u8 *)eohw_txq->q.stat;

			end = (व्योम *)eohw_txq->q.desc + left;
			sgl = (व्योम *)eohw_txq->q.desc;
		पूर्ण

		cxgb4_ग_लिखो_sgl(skb, &eohw_txq->q, (व्योम *)sgl, end, hdr_len,
				d->addr);
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size) अणु
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
			eohw_txq->uso++;
		अन्यथा
			eohw_txq->tso++;
		eohw_txq->tx_cso += skb_shinfo(skb)->gso_segs;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		eohw_txq->tx_cso++;
	पूर्ण

	अगर (skb_vlan_tag_present(skb))
		eohw_txq->vlan_ins++;

	txq_advance(&eohw_txq->q, ndesc);
	cxgb4_ring_tx_db(adap, &eohw_txq->q, ndesc);
	eosw_txq_advance_index(&eosw_txq->last_pidx, 1, eosw_txq->ndesc);

out_unlock:
	spin_unlock(&eohw_txq->lock);
	वापस ret;
पूर्ण

अटल व्योम ethofld_xmit(काष्ठा net_device *dev, काष्ठा sge_eosw_txq *eosw_txq)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक pktcount, ret;

	चयन (eosw_txq->state) अणु
	हाल CXGB4_EO_STATE_ACTIVE:
	हाल CXGB4_EO_STATE_FLOWC_OPEN_SEND:
	हाल CXGB4_EO_STATE_FLOWC_CLOSE_SEND:
		pktcount = eosw_txq->pidx - eosw_txq->last_pidx;
		अगर (pktcount < 0)
			pktcount += eosw_txq->ndesc;
		अवरोध;
	हाल CXGB4_EO_STATE_FLOWC_OPEN_REPLY:
	हाल CXGB4_EO_STATE_FLOWC_CLOSE_REPLY:
	हाल CXGB4_EO_STATE_CLOSED:
	शेष:
		वापस;
	पूर्ण

	जबतक (pktcount--) अणु
		skb = eosw_txq_peek(eosw_txq);
		अगर (!skb) अणु
			eosw_txq_advance_index(&eosw_txq->last_pidx, 1,
					       eosw_txq->ndesc);
			जारी;
		पूर्ण

		ret = ethofld_hard_xmit(dev, eosw_txq);
		अगर (ret)
			अवरोध;
	पूर्ण
पूर्ण

अटल netdev_tx_t cxgb4_ethofld_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_eosw_txq *eosw_txq;
	u32 qid;
	पूर्णांक ret;

	ret = cxgb4_validate_skb(skb, dev, ETH_HLEN);
	अगर (ret)
		जाओ out_मुक्त;

	tc_port_mqprio = &adap->tc_mqprio->port_mqprio[pi->port_id];
	qid = skb_get_queue_mapping(skb) - pi->nqsets;
	eosw_txq = &tc_port_mqprio->eosw_txq[qid];
	spin_lock_bh(&eosw_txq->lock);
	अगर (eosw_txq->state != CXGB4_EO_STATE_ACTIVE)
		जाओ out_unlock;

	ret = eosw_txq_enqueue(eosw_txq, skb);
	अगर (ret)
		जाओ out_unlock;

	/* SKB is queued क्रम processing until credits are available.
	 * So, call the deकाष्ठाor now and we'll मुक्त the skb later
	 * after it has been successfully transmitted.
	 */
	skb_orphan(skb);

	eosw_txq_advance(eosw_txq, 1);
	ethofld_xmit(dev, eosw_txq);
	spin_unlock_bh(&eosw_txq->lock);
	वापस NETDEV_TX_OK;

out_unlock:
	spin_unlock_bh(&eosw_txq->lock);
out_मुक्त:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t t4_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	u16 qid = skb_get_queue_mapping(skb);

	अगर (unlikely(pi->eth_flags & PRIV_FLAG_PORT_TX_VM))
		वापस cxgb4_vf_eth_xmit(skb, dev);

	अगर (unlikely(qid >= pi->nqsets))
		वापस cxgb4_ethofld_xmit(skb, dev);

	अगर (is_ptp_enabled(skb, dev)) अणु
		काष्ठा adapter *adap = netdev2adap(dev);
		netdev_tx_t ret;

		spin_lock(&adap->ptp_lock);
		ret = cxgb4_eth_xmit(skb, dev);
		spin_unlock(&adap->ptp_lock);
		वापस ret;
	पूर्ण

	वापस cxgb4_eth_xmit(skb, dev);
पूर्ण

अटल व्योम eosw_txq_flush_pending_skbs(काष्ठा sge_eosw_txq *eosw_txq)
अणु
	पूर्णांक pktcount = eosw_txq->pidx - eosw_txq->last_pidx;
	पूर्णांक pidx = eosw_txq->pidx;
	काष्ठा sk_buff *skb;

	अगर (!pktcount)
		वापस;

	अगर (pktcount < 0)
		pktcount += eosw_txq->ndesc;

	जबतक (pktcount--) अणु
		pidx--;
		अगर (pidx < 0)
			pidx += eosw_txq->ndesc;

		skb = eosw_txq->desc[pidx].skb;
		अगर (skb) अणु
			dev_consume_skb_any(skb);
			eosw_txq->desc[pidx].skb = शून्य;
			eosw_txq->inuse--;
		पूर्ण
	पूर्ण

	eosw_txq->pidx = eosw_txq->last_pidx + 1;
पूर्ण

/**
 * cxgb4_ethofld_send_flowc - Send ETHOFLD flowc request to bind eotid to tc.
 * @dev: netdevice
 * @eotid: ETHOFLD tid to bind/unbind
 * @tc: traffic class. If set to FW_SCHED_CLS_NONE, then unbinds the @eotid
 *
 * Send a FLOWC work request to bind an ETHOFLD TID to a traffic class.
 * If @tc is set to FW_SCHED_CLS_NONE, then the @eotid is unbound from
 * a traffic class.
 */
पूर्णांक cxgb4_ethofld_send_flowc(काष्ठा net_device *dev, u32 eotid, u32 tc)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	क्रमागत sge_eosw_state next_state;
	काष्ठा sge_eosw_txq *eosw_txq;
	u32 len, len16, nparams = 6;
	काष्ठा fw_flowc_wr *flowc;
	काष्ठा eotid_entry *entry;
	काष्ठा sge_ofld_rxq *rxq;
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;

	len = काष्ठा_size(flowc, mnemval, nparams);
	len16 = DIV_ROUND_UP(len, 16);

	entry = cxgb4_lookup_eotid(&adap->tids, eotid);
	अगर (!entry)
		वापस -ENOMEM;

	eosw_txq = (काष्ठा sge_eosw_txq *)entry->data;
	अगर (!eosw_txq)
		वापस -ENOMEM;

	अगर (!(adap->flags & CXGB4_FW_OK)) अणु
		/* Don't stall caller when access to FW is lost */
		complete(&eosw_txq->completion);
		वापस -EIO;
	पूर्ण

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	spin_lock_bh(&eosw_txq->lock);
	अगर (tc != FW_SCHED_CLS_NONE) अणु
		अगर (eosw_txq->state != CXGB4_EO_STATE_CLOSED)
			जाओ out_मुक्त_skb;

		next_state = CXGB4_EO_STATE_FLOWC_OPEN_SEND;
	पूर्ण अन्यथा अणु
		अगर (eosw_txq->state != CXGB4_EO_STATE_ACTIVE)
			जाओ out_मुक्त_skb;

		next_state = CXGB4_EO_STATE_FLOWC_CLOSE_SEND;
	पूर्ण

	flowc = __skb_put(skb, len);
	स_रखो(flowc, 0, len);

	rxq = &adap->sge.eohw_rxq[eosw_txq->hwqid];
	flowc->flowid_len16 = cpu_to_be32(FW_WR_LEN16_V(len16) |
					  FW_WR_FLOWID_V(eosw_txq->hwtid));
	flowc->op_to_nparams = cpu_to_be32(FW_WR_OP_V(FW_FLOWC_WR) |
					   FW_FLOWC_WR_NPARAMS_V(nparams) |
					   FW_WR_COMPL_V(1));
	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = cpu_to_be32(FW_PFVF_CMD_PFN_V(adap->pf));
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = cpu_to_be32(pi->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = cpu_to_be32(pi->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = cpu_to_be32(rxq->rspq.असल_id);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SCHEDCLASS;
	flowc->mnemval[4].val = cpu_to_be32(tc);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_EOSTATE;
	flowc->mnemval[5].val = cpu_to_be32(tc == FW_SCHED_CLS_NONE ?
					    FW_FLOWC_MNEM_EOSTATE_CLOSING :
					    FW_FLOWC_MNEM_EOSTATE_ESTABLISHED);

	/* Free up any pending skbs to ensure there's room क्रम
	 * termination FLOWC.
	 */
	अगर (tc == FW_SCHED_CLS_NONE)
		eosw_txq_flush_pending_skbs(eosw_txq);

	ret = eosw_txq_enqueue(eosw_txq, skb);
	अगर (ret)
		जाओ out_मुक्त_skb;

	eosw_txq->state = next_state;
	eosw_txq->flowc_idx = eosw_txq->pidx;
	eosw_txq_advance(eosw_txq, 1);
	ethofld_xmit(dev, eosw_txq);

	spin_unlock_bh(&eosw_txq->lock);
	वापस 0;

out_मुक्त_skb:
	dev_consume_skb_any(skb);
	spin_unlock_bh(&eosw_txq->lock);
	वापस ret;
पूर्ण

/**
 *	is_imm - check whether a packet can be sent as immediate data
 *	@skb: the packet
 *
 *	Returns true अगर a packet can be sent as a WR with immediate data.
 */
अटल अंतरभूत पूर्णांक is_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len <= MAX_CTRL_WR_LEN;
पूर्ण

/**
 *	ctrlq_check_stop - check अगर a control queue is full and should stop
 *	@q: the queue
 *	@wr: most recent WR written to the queue
 *
 *	Check अगर a control queue has become full and should be stopped.
 *	We clean up control queue descriptors very lazily, only when we are out.
 *	If the queue is still full after reclaiming any completed descriptors
 *	we suspend it and have the last WR wake it up.
 */
अटल व्योम ctrlq_check_stop(काष्ठा sge_ctrl_txq *q, काष्ठा fw_wr_hdr *wr)
अणु
	reclaim_completed_tx_imm(&q->q);
	अगर (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES)) अणु
		wr->lo |= htonl(FW_WR_EQUEQ_F | FW_WR_EQUIQ_F);
		q->q.stops++;
		q->full = 1;
	पूर्ण
पूर्ण

#घोषणा CXGB4_SELFTEST_LB_STR "CHELSIO_SELFTEST"

पूर्णांक cxgb4_selftest_lb_pkt(काष्ठा net_device *netdev)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा cxgb4_ethtool_lb_test *lb;
	पूर्णांक ret, i = 0, pkt_len, credits;
	काष्ठा fw_eth_tx_pkt_wr *wr;
	काष्ठा cpl_tx_pkt_core *cpl;
	u32 ctrl0, ndesc, flits;
	काष्ठा sge_eth_txq *q;
	u8 *sgl;

	pkt_len = ETH_HLEN + माप(CXGB4_SELFTEST_LB_STR);

	flits = DIV_ROUND_UP(pkt_len + माप(*cpl) + माप(*wr),
			     माप(__be64));
	ndesc = flits_to_desc(flits);

	lb = &pi->ethtool_lb;
	lb->loopback = 1;

	q = &adap->sge.ethtxq[pi->first_qset];
	__netअगर_tx_lock(q->txq, smp_processor_id());

	reclaim_completed_tx(adap, &q->q, -1, true);
	credits = txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		__netअगर_tx_unlock(q->txq);
		वापस -ENOMEM;
	पूर्ण

	wr = (व्योम *)&q->q.desc[q->q.pidx];
	स_रखो(wr, 0, माप(काष्ठा tx_desc));

	wr->op_immdlen = htonl(FW_WR_OP_V(FW_ETH_TX_PKT_WR) |
			       FW_WR_IMMDLEN_V(pkt_len +
			       माप(*cpl)));
	wr->equiq_to_len16 = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(flits, 2)));
	wr->r3 = cpu_to_be64(0);

	cpl = (व्योम *)(wr + 1);
	sgl = (u8 *)(cpl + 1);

	ctrl0 = TXPKT_OPCODE_V(CPL_TX_PKT_XT) | TXPKT_PF_V(adap->pf) |
		TXPKT_INTF_V(pi->tx_chan + 4);

	cpl->ctrl0 = htonl(ctrl0);
	cpl->pack = htons(0);
	cpl->len = htons(pkt_len);
	cpl->ctrl1 = cpu_to_be64(TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F);

	eth_broadcast_addr(sgl);
	i += ETH_ALEN;
	ether_addr_copy(&sgl[i], netdev->dev_addr);
	i += ETH_ALEN;

	snम_लिखो(&sgl[i], माप(CXGB4_SELFTEST_LB_STR), "%s",
		 CXGB4_SELFTEST_LB_STR);

	init_completion(&lb->completion);
	txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(adap, &q->q, ndesc);
	__netअगर_tx_unlock(q->txq);

	/* रुको क्रम the pkt to वापस */
	ret = रुको_क्रम_completion_समयout(&lb->completion, 10 * HZ);
	अगर (!ret)
		ret = -ETIMEDOUT;
	अन्यथा
		ret = lb->result;

	lb->loopback = 0;

	वापस ret;
पूर्ण

/**
 *	ctrl_xmit - send a packet through an SGE control Tx queue
 *	@q: the control queue
 *	@skb: the packet
 *
 *	Send a packet through an SGE control Tx queue.  Packets sent through
 *	a control queue must fit entirely as immediate data.
 */
अटल पूर्णांक ctrl_xmit(काष्ठा sge_ctrl_txq *q, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक ndesc;
	काष्ठा fw_wr_hdr *wr;

	अगर (unlikely(!is_imm(skb))) अणु
		WARN_ON(1);
		dev_kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	ndesc = DIV_ROUND_UP(skb->len, माप(काष्ठा tx_desc));
	spin_lock(&q->sendq.lock);

	अगर (unlikely(q->full)) अणु
		skb->priority = ndesc;                  /* save क्रम restart */
		__skb_queue_tail(&q->sendq, skb);
		spin_unlock(&q->sendq.lock);
		वापस NET_XMIT_CN;
	पूर्ण

	wr = (काष्ठा fw_wr_hdr *)&q->q.desc[q->q.pidx];
	cxgb4_अंतरभूत_tx_skb(skb, &q->q, wr);

	txq_advance(&q->q, ndesc);
	अगर (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES))
		ctrlq_check_stop(q, wr);

	cxgb4_ring_tx_db(q->adap, &q->q, ndesc);
	spin_unlock(&q->sendq.lock);

	kमुक्त_skb(skb);
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
	अचिन्हित पूर्णांक written = 0;
	काष्ठा sge_ctrl_txq *q = from_tasklet(q, t, qresume_tsk);

	spin_lock(&q->sendq.lock);
	reclaim_completed_tx_imm(&q->q);
	BUG_ON(txq_avail(&q->q) < TXQ_STOP_THRES);  /* q should be empty */

	जबतक ((skb = __skb_dequeue(&q->sendq)) != शून्य) अणु
		काष्ठा fw_wr_hdr *wr;
		अचिन्हित पूर्णांक ndesc = skb->priority;     /* previously saved */

		written += ndesc;
		/* Write descriptors and मुक्त skbs outside the lock to limit
		 * रुको बार.  q->full is still set so new skbs will be queued.
		 */
		wr = (काष्ठा fw_wr_hdr *)&q->q.desc[q->q.pidx];
		txq_advance(&q->q, ndesc);
		spin_unlock(&q->sendq.lock);

		cxgb4_अंतरभूत_tx_skb(skb, &q->q, wr);
		kमुक्त_skb(skb);

		अगर (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES)) अणु
			अचिन्हित दीर्घ old = q->q.stops;

			ctrlq_check_stop(q, wr);
			अगर (q->q.stops != old) अणु          /* suspended anew */
				spin_lock(&q->sendq.lock);
				जाओ ringdb;
			पूर्ण
		पूर्ण
		अगर (written > 16) अणु
			cxgb4_ring_tx_db(q->adap, &q->q, written);
			written = 0;
		पूर्ण
		spin_lock(&q->sendq.lock);
	पूर्ण
	q->full = 0;
ringdb:
	अगर (written)
		cxgb4_ring_tx_db(q->adap, &q->q, written);
	spin_unlock(&q->sendq.lock);
पूर्ण

/**
 *	t4_mgmt_tx - send a management message
 *	@adap: the adapter
 *	@skb: the packet containing the management message
 *
 *	Send a management message through control queue 0.
 */
पूर्णांक t4_mgmt_tx(काष्ठा adapter *adap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = ctrl_xmit(&adap->sge.ctrlq[0], skb);
	local_bh_enable();
	वापस ret;
पूर्ण

/**
 *	is_ofld_imm - check whether a packet can be sent as immediate data
 *	@skb: the packet
 *
 *	Returns true अगर a packet can be sent as an offload WR with immediate
 *	data.
 *	FW_OFLD_TX_DATA_WR limits the payload to 255 bytes due to 8-bit field.
 *      However, FW_ULPTX_WR commands have a 256 byte immediate only
 *      payload limit.
 */
अटल अंतरभूत पूर्णांक is_ofld_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा work_request_hdr *req = (काष्ठा work_request_hdr *)skb->data;
	अचिन्हित दीर्घ opcode = FW_WR_OP_G(ntohl(req->wr_hi));

	अगर (unlikely(opcode == FW_ULPTX_WR))
		वापस skb->len <= MAX_IMM_ULPTX_WR_LEN;
	अन्यथा अगर (opcode == FW_CRYPTO_LOOKASIDE_WR)
		वापस skb->len <= SGE_MAX_WR_LEN;
	अन्यथा
		वापस skb->len <= MAX_IMM_OFLD_TX_DATA_WR_LEN;
पूर्ण

/**
 *	calc_tx_flits_ofld - calculate # of flits क्रम an offload packet
 *	@skb: the packet
 *
 *	Returns the number of flits needed क्रम the given offload packet.
 *	These packets are alपढ़ोy fully स्थिरructed and no additional headers
 *	will be added.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_flits_ofld(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits, cnt;

	अगर (is_ofld_imm(skb))
		वापस DIV_ROUND_UP(skb->len, 8);

	flits = skb_transport_offset(skb) / 8U;   /* headers */
	cnt = skb_shinfo(skb)->nr_frags;
	अगर (skb_tail_poपूर्णांकer(skb) != skb_transport_header(skb))
		cnt++;
	वापस flits + sgl_len(cnt);
पूर्ण

/**
 *	txq_stop_maperr - stop a Tx queue due to I/O MMU exhaustion
 *	@q: the queue to stop
 *
 *	Mark a Tx queue stopped due to I/O MMU exhaustion and resulting
 *	inability to map packets.  A periodic समयr attempts to restart
 *	queues so marked.
 */
अटल व्योम txq_stop_maperr(काष्ठा sge_uld_txq *q)
अणु
	q->mapping_err++;
	q->q.stops++;
	set_bit(q->q.cntxt_id - q->adap->sge.egr_start,
		q->adap->sge.txq_maperr);
पूर्ण

/**
 *	ofldtxq_stop - stop an offload Tx queue that has become full
 *	@q: the queue to stop
 *	@wr: the Work Request causing the queue to become full
 *
 *	Stops an offload Tx queue that has become full and modअगरies the packet
 *	being written to request a wakeup.
 */
अटल व्योम ofldtxq_stop(काष्ठा sge_uld_txq *q, काष्ठा fw_wr_hdr *wr)
अणु
	wr->lo |= htonl(FW_WR_EQUEQ_F | FW_WR_EQUIQ_F);
	q->q.stops++;
	q->full = 1;
पूर्ण

/**
 *	service_ofldq - service/restart a suspended offload queue
 *	@q: the offload queue
 *
 *	Services an offload Tx queue by moving packets from its Pending Send
 *	Queue to the Hardware TX ring.  The function starts and ends with the
 *	Send Queue locked, but drops the lock जबतक putting the skb at the
 *	head of the Send Queue onto the Hardware TX Ring.  Dropping the lock
 *	allows more skbs to be added to the Send Queue by other thपढ़ोs.
 *	The packet being processed at the head of the Pending Send Queue is
 *	left on the queue in हाल we experience DMA Mapping errors, etc.
 *	and need to give up and restart later.
 *
 *	service_ofldq() can be thought of as a task which opportunistically
 *	uses other thपढ़ोs execution contexts.  We use the Offload Queue
 *	boolean "service_ofldq_running" to make sure that only one instance
 *	is ever running at a समय ...
 */
अटल व्योम service_ofldq(काष्ठा sge_uld_txq *q)
	__must_hold(&q->sendq.lock)
अणु
	u64 *pos, *beक्रमe, *end;
	पूर्णांक credits;
	काष्ठा sk_buff *skb;
	काष्ठा sge_txq *txq;
	अचिन्हित पूर्णांक left;
	अचिन्हित पूर्णांक written = 0;
	अचिन्हित पूर्णांक flits, ndesc;

	/* If another thपढ़ो is currently in service_ofldq() processing the
	 * Pending Send Queue then there's nothing to करो. Otherwise, flag
	 * that we're करोing the work and जारी.  Examining/modअगरying
	 * the Offload Queue boolean "service_ofldq_running" must be करोne
	 * जबतक holding the Pending Send Queue Lock.
	 */
	अगर (q->service_ofldq_running)
		वापस;
	q->service_ofldq_running = true;

	जबतक ((skb = skb_peek(&q->sendq)) != शून्य && !q->full) अणु
		/* We drop the lock जबतक we're working with the skb at the
		 * head of the Pending Send Queue.  This allows more skbs to
		 * be added to the Pending Send Queue जबतक we're working on
		 * this one.  We करोn't need to lock to guard the TX Ring
		 * updates because only one thपढ़ो of execution is ever
		 * allowed पूर्णांकo service_ofldq() at a समय.
		 */
		spin_unlock(&q->sendq.lock);

		cxgb4_reclaim_completed_tx(q->adap, &q->q, false);

		flits = skb->priority;                /* previously saved */
		ndesc = flits_to_desc(flits);
		credits = txq_avail(&q->q) - ndesc;
		BUG_ON(credits < 0);
		अगर (unlikely(credits < TXQ_STOP_THRES))
			ofldtxq_stop(q, (काष्ठा fw_wr_hdr *)skb->data);

		pos = (u64 *)&q->q.desc[q->q.pidx];
		अगर (is_ofld_imm(skb))
			cxgb4_अंतरभूत_tx_skb(skb, &q->q, pos);
		अन्यथा अगर (cxgb4_map_skb(q->adap->pdev_dev, skb,
				       (dma_addr_t *)skb->head)) अणु
			txq_stop_maperr(q);
			spin_lock(&q->sendq.lock);
			अवरोध;
		पूर्ण अन्यथा अणु
			पूर्णांक last_desc, hdr_len = skb_transport_offset(skb);

			/* The WR headers  may not fit within one descriptor.
			 * So we need to deal with wrap-around here.
			 */
			beक्रमe = (u64 *)pos;
			end = (u64 *)pos + flits;
			txq = &q->q;
			pos = (व्योम *)अंतरभूत_tx_skb_header(skb, &q->q,
							   (व्योम *)pos,
							   hdr_len);
			अगर (beक्रमe > (u64 *)pos) अणु
				left = (u8 *)end - (u8 *)txq->stat;
				end = (व्योम *)txq->desc + left;
			पूर्ण

			/* If current position is alपढ़ोy at the end of the
			 * ofld queue, reset the current to poपूर्णांक to
			 * start of the queue and update the end ptr as well.
			 */
			अगर (pos == (u64 *)txq->stat) अणु
				left = (u8 *)end - (u8 *)txq->stat;
				end = (व्योम *)txq->desc + left;
				pos = (व्योम *)txq->desc;
			पूर्ण

			cxgb4_ग_लिखो_sgl(skb, &q->q, (व्योम *)pos,
					end, hdr_len,
					(dma_addr_t *)skb->head);
#अगर_घोषित CONFIG_NEED_DMA_MAP_STATE
			skb->dev = q->adap->port[0];
			skb->deकाष्ठाor = deferred_unmap_deकाष्ठाor;
#पूर्ण_अगर
			last_desc = q->q.pidx + ndesc - 1;
			अगर (last_desc >= q->q.size)
				last_desc -= q->q.size;
			q->q.sdesc[last_desc].skb = skb;
		पूर्ण

		txq_advance(&q->q, ndesc);
		written += ndesc;
		अगर (unlikely(written > 32)) अणु
			cxgb4_ring_tx_db(q->adap, &q->q, written);
			written = 0;
		पूर्ण

		/* Reacquire the Pending Send Queue Lock so we can unlink the
		 * skb we've just successfully transferred to the TX Ring and
		 * loop क्रम the next skb which may be at the head of the
		 * Pending Send Queue.
		 */
		spin_lock(&q->sendq.lock);
		__skb_unlink(skb, &q->sendq);
		अगर (is_ofld_imm(skb))
			kमुक्त_skb(skb);
	पूर्ण
	अगर (likely(written))
		cxgb4_ring_tx_db(q->adap, &q->q, written);

	/*Indicate that no thपढ़ो is processing the Pending Send Queue
	 * currently.
	 */
	q->service_ofldq_running = false;
पूर्ण

/**
 *	ofld_xmit - send a packet through an offload queue
 *	@q: the Tx offload queue
 *	@skb: the packet
 *
 *	Send an offload packet through an SGE offload queue.
 */
अटल पूर्णांक ofld_xmit(काष्ठा sge_uld_txq *q, काष्ठा sk_buff *skb)
अणु
	skb->priority = calc_tx_flits_ofld(skb);       /* save क्रम restart */
	spin_lock(&q->sendq.lock);

	/* Queue the new skb onto the Offload Queue's Pending Send Queue.  If
	 * that results in this new skb being the only one on the queue, start
	 * servicing it.  If there are other skbs alपढ़ोy on the list, then
	 * either the queue is currently being processed or it's been stopped
	 * क्रम some reason and it'll be restarted at a later समय.  Restart
	 * paths are triggered by events like experiencing a DMA Mapping Error
	 * or filling the Hardware TX Ring.
	 */
	__skb_queue_tail(&q->sendq, skb);
	अगर (q->sendq.qlen == 1)
		service_ofldq(q);

	spin_unlock(&q->sendq.lock);
	वापस NET_XMIT_SUCCESS;
पूर्ण

/**
 *	restart_ofldq - restart a suspended offload queue
 *	@t: poपूर्णांकer to the tasklet associated with this handler
 *
 *	Resumes transmission on a suspended Tx offload queue.
 */
अटल व्योम restart_ofldq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sge_uld_txq *q = from_tasklet(q, t, qresume_tsk);

	spin_lock(&q->sendq.lock);
	q->full = 0;            /* the queue actually is completely empty now */
	service_ofldq(q);
	spin_unlock(&q->sendq.lock);
पूर्ण

/**
 *	skb_txq - वापस the Tx queue an offload packet should use
 *	@skb: the packet
 *
 *	Returns the Tx queue an offload packet should use as indicated by bits
 *	1-15 in the packet's queue_mapping.
 */
अटल अंतरभूत अचिन्हित पूर्णांक skb_txq(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping >> 1;
पूर्ण

/**
 *	is_ctrl_pkt - वापस whether an offload packet is a control packet
 *	@skb: the packet
 *
 *	Returns whether an offload packet should use an OFLD or a CTRL
 *	Tx queue as indicated by bit 0 in the packet's queue_mapping.
 */
अटल अंतरभूत अचिन्हित पूर्णांक is_ctrl_pkt(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping & 1;
पूर्ण

अटल अंतरभूत पूर्णांक uld_send(काष्ठा adapter *adap, काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक tx_uld_type)
अणु
	काष्ठा sge_uld_txq_info *txq_info;
	काष्ठा sge_uld_txq *txq;
	अचिन्हित पूर्णांक idx = skb_txq(skb);

	अगर (unlikely(is_ctrl_pkt(skb))) अणु
		/* Single ctrl queue is a requirement क्रम LE workaround path */
		अगर (adap->tids.nsftids)
			idx = 0;
		वापस ctrl_xmit(&adap->sge.ctrlq[idx], skb);
	पूर्ण

	txq_info = adap->sge.uld_txq_info[tx_uld_type];
	अगर (unlikely(!txq_info)) अणु
		WARN_ON(true);
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	txq = &txq_info->uldtxq[idx];
	वापस ofld_xmit(txq, skb);
पूर्ण

/**
 *	t4_ofld_send - send an offload packet
 *	@adap: the adapter
 *	@skb: the packet
 *
 *	Sends an offload packet.  We use the packet queue_mapping to select the
 *	appropriate Tx queue as follows: bit 0 indicates whether the packet
 *	should be sent as regular or control, bits 1-15 select the queue.
 */
पूर्णांक t4_ofld_send(काष्ठा adapter *adap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = uld_send(adap, skb, CXGB4_TX_OFLD);
	local_bh_enable();
	वापस ret;
पूर्ण

/**
 *	cxgb4_ofld_send - send an offload packet
 *	@dev: the net device
 *	@skb: the packet
 *
 *	Sends an offload packet.  This is an exported version of @t4_ofld_send,
 *	पूर्णांकended क्रम ULDs.
 */
पूर्णांक cxgb4_ofld_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस t4_ofld_send(netdev2adap(dev), skb);
पूर्ण
EXPORT_SYMBOL(cxgb4_ofld_send);

अटल व्योम *अंतरभूत_tx_header(स्थिर व्योम *src,
			      स्थिर काष्ठा sge_txq *q,
			      व्योम *pos, पूर्णांक length)
अणु
	पूर्णांक left = (व्योम *)q->stat - pos;
	u64 *p;

	अगर (likely(length <= left)) अणु
		स_नकल(pos, src, length);
		pos += length;
	पूर्ण अन्यथा अणु
		स_नकल(pos, src, left);
		स_नकल(q->desc, src + left, length - left);
		pos = (व्योम *)q->desc + (length - left);
	पूर्ण
	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	अगर ((uपूर्णांकptr_t)p & 8) अणु
		*p = 0;
		वापस p + 1;
	पूर्ण
	वापस p;
पूर्ण

/**
 *      ofld_xmit_direct - copy a WR पूर्णांकo offload queue
 *      @q: the Tx offload queue
 *      @src: location of WR
 *      @len: WR length
 *
 *      Copy an immediate WR पूर्णांकo an uncontended SGE offload queue.
 */
अटल पूर्णांक ofld_xmit_direct(काष्ठा sge_uld_txq *q, स्थिर व्योम *src,
			    अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक ndesc;
	पूर्णांक credits;
	u64 *pos;

	/* Use the lower limit as the cut-off */
	अगर (len > MAX_IMM_OFLD_TX_DATA_WR_LEN) अणु
		WARN_ON(1);
		वापस NET_XMIT_DROP;
	पूर्ण

	/* Don't वापस NET_XMIT_CN here as the current
	 * implementation करोesn't queue the request
	 * using an skb when the following conditions not met
	 */
	अगर (!spin_trylock(&q->sendq.lock))
		वापस NET_XMIT_DROP;

	अगर (q->full || !skb_queue_empty(&q->sendq) ||
	    q->service_ofldq_running) अणु
		spin_unlock(&q->sendq.lock);
		वापस NET_XMIT_DROP;
	पूर्ण
	ndesc = flits_to_desc(DIV_ROUND_UP(len, 8));
	credits = txq_avail(&q->q) - ndesc;
	pos = (u64 *)&q->q.desc[q->q.pidx];

	/* ofldtxq_stop modअगरies WR header in-situ */
	अंतरभूत_tx_header(src, &q->q, pos, len);
	अगर (unlikely(credits < TXQ_STOP_THRES))
		ofldtxq_stop(q, (काष्ठा fw_wr_hdr *)pos);
	txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(q->adap, &q->q, ndesc);

	spin_unlock(&q->sendq.lock);
	वापस NET_XMIT_SUCCESS;
पूर्ण

पूर्णांक cxgb4_immdata_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
		       स्थिर व्योम *src, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sge_uld_txq_info *txq_info;
	काष्ठा sge_uld_txq *txq;
	काष्ठा adapter *adap;
	पूर्णांक ret;

	adap = netdev2adap(dev);

	local_bh_disable();
	txq_info = adap->sge.uld_txq_info[CXGB4_TX_OFLD];
	अगर (unlikely(!txq_info)) अणु
		WARN_ON(true);
		local_bh_enable();
		वापस NET_XMIT_DROP;
	पूर्ण
	txq = &txq_info->uldtxq[idx];

	ret = ofld_xmit_direct(txq, src, len);
	local_bh_enable();
	वापस net_xmit_eval(ret);
पूर्ण
EXPORT_SYMBOL(cxgb4_immdata_send);

/**
 *	t4_crypto_send - send crypto packet
 *	@adap: the adapter
 *	@skb: the packet
 *
 *	Sends crypto packet.  We use the packet queue_mapping to select the
 *	appropriate Tx queue as follows: bit 0 indicates whether the packet
 *	should be sent as regular or control, bits 1-15 select the queue.
 */
अटल पूर्णांक t4_crypto_send(काष्ठा adapter *adap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = uld_send(adap, skb, CXGB4_TX_CRYPTO);
	local_bh_enable();
	वापस ret;
पूर्ण

/**
 *	cxgb4_crypto_send - send crypto packet
 *	@dev: the net device
 *	@skb: the packet
 *
 *	Sends crypto packet.  This is an exported version of @t4_crypto_send,
 *	पूर्णांकended क्रम ULDs.
 */
पूर्णांक cxgb4_crypto_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस t4_crypto_send(netdev2adap(dev), skb);
पूर्ण
EXPORT_SYMBOL(cxgb4_crypto_send);

अटल अंतरभूत व्योम copy_frags(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा pkt_gl *gl, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i;

	/* usually there's just one frag */
	__skb_fill_page_desc(skb, 0, gl->frags[0].page,
			     gl->frags[0].offset + offset,
			     gl->frags[0].size - offset);
	skb_shinfo(skb)->nr_frags = gl->nfrags;
	क्रम (i = 1; i < gl->nfrags; i++)
		__skb_fill_page_desc(skb, i, gl->frags[i].page,
				     gl->frags[i].offset,
				     gl->frags[i].size);

	/* get a reference to the last page, we करोn't own it */
	get_page(gl->frags[gl->nfrags - 1].page);
पूर्ण

/**
 *	cxgb4_pktgl_to_skb - build an sk_buff from a packet gather list
 *	@gl: the gather list
 *	@skb_len: size of sk_buff मुख्य body अगर it carries fragments
 *	@pull_len: amount of data to move to the sk_buff's मुख्य body
 *
 *	Builds an sk_buff from the given packet gather list.  Returns the
 *	sk_buff or %शून्य अगर sk_buff allocation failed.
 */
काष्ठा sk_buff *cxgb4_pktgl_to_skb(स्थिर काष्ठा pkt_gl *gl,
				   अचिन्हित पूर्णांक skb_len, अचिन्हित पूर्णांक pull_len)
अणु
	काष्ठा sk_buff *skb;

	/*
	 * Below we rely on RX_COPY_THRES being less than the smallest Rx buffer
	 * size, which is expected since buffers are at least PAGE_SIZEd.
	 * In this हाल packets up to RX_COPY_THRES have only one fragment.
	 */
	अगर (gl->tot_len <= RX_COPY_THRES) अणु
		skb = dev_alloc_skb(gl->tot_len);
		अगर (unlikely(!skb))
			जाओ out;
		__skb_put(skb, gl->tot_len);
		skb_copy_to_linear_data(skb, gl->va, gl->tot_len);
	पूर्ण अन्यथा अणु
		skb = dev_alloc_skb(skb_len);
		अगर (unlikely(!skb))
			जाओ out;
		__skb_put(skb, pull_len);
		skb_copy_to_linear_data(skb, gl->va, pull_len);

		copy_frags(skb, gl, pull_len);
		skb->len = gl->tot_len;
		skb->data_len = skb->len - pull_len;
		skb->truesize += skb->data_len;
	पूर्ण
out:	वापस skb;
पूर्ण
EXPORT_SYMBOL(cxgb4_pktgl_to_skb);

/**
 *	t4_pktgl_मुक्त - मुक्त a packet gather list
 *	@gl: the gather list
 *
 *	Releases the pages of a packet gather list.  We करो not own the last
 *	page on the list and करो not मुक्त it.
 */
अटल व्योम t4_pktgl_मुक्त(स्थिर काष्ठा pkt_gl *gl)
अणु
	पूर्णांक n;
	स्थिर काष्ठा page_frag *p;

	क्रम (p = gl->frags, n = gl->nfrags - 1; n--; p++)
		put_page(p->page);
पूर्ण

/*
 * Process an MPS trace packet.  Give it an unused protocol number so it won't
 * be delivered to anyone and send it to the stack क्रम capture.
 */
अटल noअंतरभूत पूर्णांक handle_trace_pkt(काष्ठा adapter *adap,
				     स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा sk_buff *skb;

	skb = cxgb4_pktgl_to_skb(gl, RX_PULL_LEN, RX_PULL_LEN);
	अगर (unlikely(!skb)) अणु
		t4_pktgl_मुक्त(gl);
		वापस 0;
	पूर्ण

	अगर (is_t4(adap->params.chip))
		__skb_pull(skb, माप(काष्ठा cpl_trace_pkt));
	अन्यथा
		__skb_pull(skb, माप(काष्ठा cpl_t5_trace_pkt));

	skb_reset_mac_header(skb);
	skb->protocol = htons(0xffff);
	skb->dev = adap->port[0];
	netअगर_receive_skb(skb);
	वापस 0;
पूर्ण

/**
 * cxgb4_sgetim_to_hwtstamp - convert sge समय stamp to hw समय stamp
 * @adap: the adapter
 * @hwtstamps: समय stamp काष्ठाure to update
 * @sमाला_लोtamp: 60bit iqe बारtamp
 *
 * Every ingress queue entry has the 60-bit बारtamp, convert that बारtamp
 * which is in Core Clock ticks पूर्णांकo kसमय_प्रकार and assign it
 **/
अटल व्योम cxgb4_sgetim_to_hwtstamp(काष्ठा adapter *adap,
				     काष्ठा skb_shared_hwtstamps *hwtstamps,
				     u64 sमाला_लोtamp)
अणु
	u64 ns;
	u64 पंचांगp = (sमाला_लोtamp * 1000 * 1000 + adap->params.vpd.cclk / 2);

	ns = भाग_u64(पंचांगp, adap->params.vpd.cclk);

	स_रखो(hwtstamps, 0, माप(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_kसमय(ns);
पूर्ण

अटल व्योम करो_gro(काष्ठा sge_eth_rxq *rxq, स्थिर काष्ठा pkt_gl *gl,
		   स्थिर काष्ठा cpl_rx_pkt *pkt, अचिन्हित दीर्घ tnl_hdr_len)
अणु
	काष्ठा adapter *adapter = rxq->rspq.adap;
	काष्ठा sge *s = &adapter->sge;
	काष्ठा port_info *pi;
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	skb = napi_get_frags(&rxq->rspq.napi);
	अगर (unlikely(!skb)) अणु
		t4_pktgl_मुक्त(gl);
		rxq->stats.rx_drops++;
		वापस;
	पूर्ण

	copy_frags(skb, gl, s->pktshअगरt);
	अगर (tnl_hdr_len)
		skb->csum_level = 1;
	skb->len = gl->tot_len - s->pktshअगरt;
	skb->data_len = skb->len;
	skb->truesize += skb->data_len;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rxq->rspq.idx);
	pi = netdev_priv(skb->dev);
	अगर (pi->rxtstamp)
		cxgb4_sgetim_to_hwtstamp(adapter, skb_hwtstamps(skb),
					 gl->sमाला_लोtamp);
	अगर (rxq->rspq.netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, (__क्रमce u32)pkt->rsshdr.hash_val,
			     PKT_HASH_TYPE_L3);

	अगर (unlikely(pkt->vlan_ex)) अणु
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(pkt->vlan));
		rxq->stats.vlan_ex++;
	पूर्ण
	ret = napi_gro_frags(&rxq->rspq.napi);
	अगर (ret == GRO_HELD)
		rxq->stats.lro_pkts++;
	अन्यथा अगर (ret == GRO_MERGED || ret == GRO_MERGED_FREE)
		rxq->stats.lro_merged++;
	rxq->stats.pkts++;
	rxq->stats.rx_cso++;
पूर्ण

क्रमागत अणु
	RX_NON_PTP_PKT = 0,
	RX_PTP_PKT_SUC = 1,
	RX_PTP_PKT_ERR = 2
पूर्ण;

/**
 *     t4_systim_to_hwstamp - पढ़ो hardware समय stamp
 *     @adapter: the adapter
 *     @skb: the packet
 *
 *     Read Time Stamp from MPS packet and insert in skb which
 *     is क्रमwarded to PTP application
 */
अटल noअंतरभूत पूर्णांक t4_systim_to_hwstamp(काष्ठा adapter *adapter,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps *hwtstamps;
	काष्ठा cpl_rx_mps_pkt *cpl = शून्य;
	अचिन्हित अक्षर *data;
	पूर्णांक offset;

	cpl = (काष्ठा cpl_rx_mps_pkt *)skb->data;
	अगर (!(CPL_RX_MPS_PKT_TYPE_G(ntohl(cpl->op_to_r1_hi)) &
	     X_CPL_RX_MPS_PKT_TYPE_PTP))
		वापस RX_PTP_PKT_ERR;

	data = skb->data + माप(*cpl);
	skb_pull(skb, 2 * माप(u64) + माप(काष्ठा cpl_rx_mps_pkt));
	offset = ETH_HLEN + IPV4_HLEN(skb->data) + UDP_HLEN;
	अगर (skb->len < offset + OFF_PTP_SEQUENCE_ID + माप(लघु))
		वापस RX_PTP_PKT_ERR;

	hwtstamps = skb_hwtstamps(skb);
	स_रखो(hwtstamps, 0, माप(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_kसमय(get_unaligned_be64(data));

	वापस RX_PTP_PKT_SUC;
पूर्ण

/**
 *     t4_rx_hststamp - Recv PTP Event Message
 *     @adapter: the adapter
 *     @rsp: the response queue descriptor holding the RX_PKT message
 *     @rxq: the response queue holding the RX_PKT message
 *     @skb: the packet
 *
 *     PTP enabled and MPS packet, पढ़ो HW बारtamp
 */
अटल पूर्णांक t4_rx_hststamp(काष्ठा adapter *adapter, स्थिर __be64 *rsp,
			  काष्ठा sge_eth_rxq *rxq, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (unlikely((*(u8 *)rsp == CPL_RX_MPS_PKT) &&
		     !is_t4(adapter->params.chip))) अणु
		ret = t4_systim_to_hwstamp(adapter, skb);
		अगर (ret == RX_PTP_PKT_ERR) अणु
			kमुक्त_skb(skb);
			rxq->stats.rx_drops++;
		पूर्ण
		वापस ret;
	पूर्ण
	वापस RX_NON_PTP_PKT;
पूर्ण

/**
 *      t4_tx_hststamp - Loopback PTP Transmit Event Message
 *      @adapter: the adapter
 *      @skb: the packet
 *      @dev: the ingress net device
 *
 *      Read hardware बारtamp क्रम the loopback PTP Tx event message
 */
अटल पूर्णांक t4_tx_hststamp(काष्ठा adapter *adapter, काष्ठा sk_buff *skb,
			  काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (!is_t4(adapter->params.chip) && adapter->ptp_tx_skb) अणु
		cxgb4_ptp_पढ़ो_hwstamp(adapter, pi);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	t4_tx_completion_handler - handle CPL_SGE_EGR_UPDATE messages
 *	@rspq: Ethernet RX Response Queue associated with Ethernet TX Queue
 *	@rsp: Response Entry poपूर्णांकer पूर्णांकo Response Queue
 *	@gl: Gather List poपूर्णांकer
 *
 *	For adapters which support the SGE Doorbell Queue Timer facility,
 *	we configure the Ethernet TX Queues to send CIDX Updates to the
 *	Associated Ethernet RX Response Queue with CPL_SGE_EGR_UPDATE
 *	messages.  This adds a small load to PCIe Link RX bandwidth and,
 *	potentially, higher CPU Interrupt load, but allows us to respond
 *	much more quickly to the CIDX Updates.  This is important क्रम
 *	Upper Layer Software which isn't willing to have a large amount
 *	of TX Data outstanding beक्रमe receiving DMA Completions.
 */
अटल व्योम t4_tx_completion_handler(काष्ठा sge_rspq *rspq,
				     स्थिर __be64 *rsp,
				     स्थिर काष्ठा pkt_gl *gl)
अणु
	u8 opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;
	काष्ठा port_info *pi = netdev_priv(rspq->netdev);
	काष्ठा adapter *adapter = rspq->adap;
	काष्ठा sge *s = &adapter->sge;
	काष्ठा sge_eth_txq *txq;

	/* skip RSS header */
	rsp++;

	/* FW can send EGR_UPDATEs encapsulated in a CPL_FW4_MSG.
	 */
	अगर (unlikely(opcode == CPL_FW4_MSG &&
		     ((स्थिर काष्ठा cpl_fw4_msg *)rsp)->type ==
							FW_TYPE_RSSCPL)) अणु
		rsp++;
		opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;
		rsp++;
	पूर्ण

	अगर (unlikely(opcode != CPL_SGE_EGR_UPDATE)) अणु
		pr_info("%s: unexpected FW4/CPL %#x on Rx queue\n",
			__func__, opcode);
		वापस;
	पूर्ण

	txq = &s->ethtxq[pi->first_qset + rspq->idx];

	/* We've got the Hardware Consumer Index Update in the Egress Update
	 * message. These Egress Update messages will be our sole CIDX Updates
	 * we get since we करोn't want to chew up PCIe bandwidth क्रम both Ingress
	 * Messages and Status Page ग_लिखोs.  However, The code which manages
	 * reclaiming successfully DMA'ed TX Work Requests uses the CIDX value
	 * stored in the Status Page at the end of the TX Queue.  It's easiest
	 * to simply copy the CIDX Update value from the Egress Update message
	 * to the Status Page.  Also note that no Endian issues need to be
	 * considered here since both are Big Endian and we're just copying
	 * bytes consistently ...
	 */
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5) अणु
		काष्ठा cpl_sge_egr_update *egr;

		egr = (काष्ठा cpl_sge_egr_update *)rsp;
		WRITE_ONCE(txq->q.stat->cidx, egr->cidx);
	पूर्ण

	t4_sge_eth_txq_egress_update(adapter, txq, -1);
पूर्ण

अटल पूर्णांक cxgb4_validate_lb_pkt(काष्ठा port_info *pi, स्थिर काष्ठा pkt_gl *si)
अणु
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा cxgb4_ethtool_lb_test *lb;
	काष्ठा sge *s = &adap->sge;
	काष्ठा net_device *netdev;
	u8 *data;
	पूर्णांक i;

	netdev = adap->port[pi->port_id];
	lb = &pi->ethtool_lb;
	data = si->va + s->pktshअगरt;

	i = ETH_ALEN;
	अगर (!ether_addr_equal(data + i, netdev->dev_addr))
		वापस -1;

	i += ETH_ALEN;
	अगर (म_भेद(&data[i], CXGB4_SELFTEST_LB_STR))
		lb->result = -EIO;

	complete(&lb->completion);
	वापस 0;
पूर्ण

/**
 *	t4_ethrx_handler - process an ingress ethernet packet
 *	@q: the response queue that received the packet
 *	@rsp: the response queue descriptor holding the RX_PKT message
 *	@si: the gather list of packet fragments
 *
 *	Process an ingress ethernet packet and deliver it to the stack.
 */
पूर्णांक t4_ethrx_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
		     स्थिर काष्ठा pkt_gl *si)
अणु
	bool csum_ok;
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा cpl_rx_pkt *pkt;
	काष्ठा sge_eth_rxq *rxq = container_of(q, काष्ठा sge_eth_rxq, rspq);
	काष्ठा adapter *adapter = q->adap;
	काष्ठा sge *s = &q->adap->sge;
	पूर्णांक cpl_trace_pkt = is_t4(q->adap->params.chip) ?
			    CPL_TRACE_PKT : CPL_TRACE_PKT_T5;
	u16 err_vec, tnl_hdr_len = 0;
	काष्ठा port_info *pi;
	पूर्णांक ret = 0;

	pi = netdev_priv(q->netdev);
	/* If we're looking at TX Queue CIDX Update, handle that separately
	 * and वापस.
	 */
	अगर (unlikely((*(u8 *)rsp == CPL_FW4_MSG) ||
		     (*(u8 *)rsp == CPL_SGE_EGR_UPDATE))) अणु
		t4_tx_completion_handler(q, rsp, si);
		वापस 0;
	पूर्ण

	अगर (unlikely(*(u8 *)rsp == cpl_trace_pkt))
		वापस handle_trace_pkt(q->adap, si);

	pkt = (स्थिर काष्ठा cpl_rx_pkt *)rsp;
	/* Compressed error vector is enabled क्रम T6 only */
	अगर (q->adap->params.tp.rx_pkt_encap) अणु
		err_vec = T6_COMPR_RXERR_VEC_G(be16_to_cpu(pkt->err_vec));
		tnl_hdr_len = T6_RX_TNLHDR_LEN_G(ntohs(pkt->err_vec));
	पूर्ण अन्यथा अणु
		err_vec = be16_to_cpu(pkt->err_vec);
	पूर्ण

	csum_ok = pkt->csum_calc && !err_vec &&
		  (q->netdev->features & NETIF_F_RXCSUM);

	अगर (err_vec)
		rxq->stats.bad_rx_pkts++;

	अगर (unlikely(pi->ethtool_lb.loopback && pkt->अगरf >= NCHAN)) अणु
		ret = cxgb4_validate_lb_pkt(pi, si);
		अगर (!ret)
			वापस 0;
	पूर्ण

	अगर (((pkt->l2info & htonl(RXF_TCP_F)) ||
	     tnl_hdr_len) &&
	    (q->netdev->features & NETIF_F_GRO) && csum_ok && !pkt->ip_frag) अणु
		करो_gro(rxq, si, pkt, tnl_hdr_len);
		वापस 0;
	पूर्ण

	skb = cxgb4_pktgl_to_skb(si, RX_PKT_SKB_LEN, RX_PULL_LEN);
	अगर (unlikely(!skb)) अणु
		t4_pktgl_मुक्त(si);
		rxq->stats.rx_drops++;
		वापस 0;
	पूर्ण

	/* Handle PTP Event Rx packet */
	अगर (unlikely(pi->ptp_enable)) अणु
		ret = t4_rx_hststamp(adapter, rsp, rxq, skb);
		अगर (ret == RX_PTP_PKT_ERR)
			वापस 0;
	पूर्ण
	अगर (likely(!ret))
		__skb_pull(skb, s->pktshअगरt); /* हटाओ ethernet header pad */

	/* Handle the PTP Event Tx Loopback packet */
	अगर (unlikely(pi->ptp_enable && !ret &&
		     (pkt->l2info & htonl(RXF_UDP_F)) &&
		     cxgb4_ptp_is_ptp_rx(skb))) अणु
		अगर (!t4_tx_hststamp(adapter, skb, q->netdev))
			वापस 0;
	पूर्ण

	skb->protocol = eth_type_trans(skb, q->netdev);
	skb_record_rx_queue(skb, q->idx);
	अगर (skb->dev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, (__क्रमce u32)pkt->rsshdr.hash_val,
			     PKT_HASH_TYPE_L3);

	rxq->stats.pkts++;

	अगर (pi->rxtstamp)
		cxgb4_sgetim_to_hwtstamp(q->adap, skb_hwtstamps(skb),
					 si->sमाला_लोtamp);
	अगर (csum_ok && (pkt->l2info & htonl(RXF_UDP_F | RXF_TCP_F))) अणु
		अगर (!pkt->ip_frag) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			rxq->stats.rx_cso++;
		पूर्ण अन्यथा अगर (pkt->l2info & htonl(RXF_IP_F)) अणु
			__sum16 c = (__क्रमce __sum16)pkt->csum;
			skb->csum = csum_unfold(c);

			अगर (tnl_hdr_len) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				skb->csum_level = 1;
			पूर्ण अन्यथा अणु
				skb->ip_summed = CHECKSUM_COMPLETE;
			पूर्ण
			rxq->stats.rx_cso++;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_checksum_none_निश्चित(skb);
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
#घोषणा CPL_RX_PKT_FLAGS (RXF_PSH_F | RXF_SYN_F | RXF_UDP_F | \
			  RXF_TCP_F | RXF_IP_F | RXF_IP6_F | RXF_LRO_F)

		अगर (!(pkt->l2info & cpu_to_be32(CPL_RX_PKT_FLAGS))) अणु
			अगर ((pkt->l2info & cpu_to_be32(RXF_FCOE_F)) &&
			    (pi->fcoe.flags & CXGB_FCOE_ENABLED)) अणु
				अगर (q->adap->params.tp.rx_pkt_encap)
					csum_ok = err_vec &
						  T6_COMPR_RXERR_SUM_F;
				अन्यथा
					csum_ok = err_vec & RXERR_CSUM_F;
				अगर (!csum_ok)
					skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण
		पूर्ण

#अघोषित CPL_RX_PKT_FLAGS
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
	पूर्ण

	अगर (unlikely(pkt->vlan_ex)) अणु
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(pkt->vlan));
		rxq->stats.vlan_ex++;
	पूर्ण
	skb_mark_napi_id(skb, &q->napi);
	netअगर_receive_skb(skb);
	वापस 0;
पूर्ण

/**
 *	restore_rx_bufs - put back a packet's Rx buffers
 *	@si: the packet gather list
 *	@q: the SGE मुक्त list
 *	@frags: number of FL buffers to restore
 *
 *	Puts back on an FL the Rx buffers associated with @si.  The buffers
 *	have alपढ़ोy been unmapped and are left unmapped, we mark them so to
 *	prevent further unmapping attempts.
 *
 *	This function unकरोes a series of @unmap_rx_buf calls when we find out
 *	that the current packet can't be processed right away afterall and we
 *	need to come back to it later.  This is a very rare event and there's
 *	no efक्रमt to make this particularly efficient.
 */
अटल व्योम restore_rx_bufs(स्थिर काष्ठा pkt_gl *si, काष्ठा sge_fl *q,
			    पूर्णांक frags)
अणु
	काष्ठा rx_sw_desc *d;

	जबतक (frags--) अणु
		अगर (q->cidx == 0)
			q->cidx = q->size - 1;
		अन्यथा
			q->cidx--;
		d = &q->sdesc[q->cidx];
		d->page = si->frags[frags].page;
		d->dma_addr |= RX_UNMAPPED_BUF;
		q->avail++;
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
अटल अंतरभूत bool is_new_response(स्थिर काष्ठा rsp_ctrl *r,
				   स्थिर काष्ठा sge_rspq *q)
अणु
	वापस (r->type_gen >> RSPD_GEN_S) == q->gen;
पूर्ण

/**
 *	rspq_next - advance to the next entry in a response queue
 *	@q: the queue
 *
 *	Updates the state of a response queue to advance it to the next entry.
 */
अटल अंतरभूत व्योम rspq_next(काष्ठा sge_rspq *q)
अणु
	q->cur_desc = (व्योम *)q->cur_desc + q->iqe_len;
	अगर (unlikely(++q->cidx == q->size)) अणु
		q->cidx = 0;
		q->gen ^= 1;
		q->cur_desc = q->desc;
	पूर्ण
पूर्ण

/**
 *	process_responses - process responses from an SGE response queue
 *	@q: the ingress queue to process
 *	@budget: how many responses can be processed in this round
 *
 *	Process responses from an SGE response queue up to the supplied budget.
 *	Responses include received packets as well as control messages from FW
 *	or HW.
 *
 *	Additionally choose the पूर्णांकerrupt holकरोff समय क्रम the next पूर्णांकerrupt
 *	on this queue.  If the प्रणाली is under memory लघुage use a fairly
 *	दीर्घ delay to help recovery.
 */
अटल पूर्णांक process_responses(काष्ठा sge_rspq *q, पूर्णांक budget)
अणु
	पूर्णांक ret, rsp_type;
	पूर्णांक budget_left = budget;
	स्थिर काष्ठा rsp_ctrl *rc;
	काष्ठा sge_eth_rxq *rxq = container_of(q, काष्ठा sge_eth_rxq, rspq);
	काष्ठा adapter *adapter = q->adap;
	काष्ठा sge *s = &adapter->sge;

	जबतक (likely(budget_left)) अणु
		rc = (व्योम *)q->cur_desc + (q->iqe_len - माप(*rc));
		अगर (!is_new_response(rc, q)) अणु
			अगर (q->flush_handler)
				q->flush_handler(q);
			अवरोध;
		पूर्ण

		dma_rmb();
		rsp_type = RSPD_TYPE_G(rc->type_gen);
		अगर (likely(rsp_type == RSPD_TYPE_FLBUF_X)) अणु
			काष्ठा page_frag *fp;
			काष्ठा pkt_gl si;
			स्थिर काष्ठा rx_sw_desc *rsd;
			u32 len = ntohl(rc->pldbuflen_qid), bufsz, frags;

			अगर (len & RSPD_NEWBUF_F) अणु
				अगर (likely(q->offset > 0)) अणु
					मुक्त_rx_bufs(q->adap, &rxq->fl, 1);
					q->offset = 0;
				पूर्ण
				len = RSPD_LEN_G(len);
			पूर्ण
			si.tot_len = len;

			/* gather packet fragments */
			क्रम (frags = 0, fp = si.frags; ; frags++, fp++) अणु
				rsd = &rxq->fl.sdesc[rxq->fl.cidx];
				bufsz = get_buf_size(adapter, rsd);
				fp->page = rsd->page;
				fp->offset = q->offset;
				fp->size = min(bufsz, len);
				len -= fp->size;
				अगर (!len)
					अवरोध;
				unmap_rx_buf(q->adap, &rxq->fl);
			पूर्ण

			si.sमाला_लोtamp = SGE_TIMESTAMP_G(
					be64_to_cpu(rc->last_flit));
			/*
			 * Last buffer reमुख्यs mapped so explicitly make it
			 * coherent क्रम CPU access.
			 */
			dma_sync_single_क्रम_cpu(q->adap->pdev_dev,
						get_buf_addr(rsd),
						fp->size, DMA_FROM_DEVICE);

			si.va = page_address(si.frags[0].page) +
				si.frags[0].offset;
			prefetch(si.va);

			si.nfrags = frags + 1;
			ret = q->handler(q, q->cur_desc, &si);
			अगर (likely(ret == 0))
				q->offset += ALIGN(fp->size, s->fl_align);
			अन्यथा
				restore_rx_bufs(&si, &rxq->fl, frags);
		पूर्ण अन्यथा अगर (likely(rsp_type == RSPD_TYPE_CPL_X)) अणु
			ret = q->handler(q, q->cur_desc, शून्य);
		पूर्ण अन्यथा अणु
			ret = q->handler(q, (स्थिर __be64 *)rc, CXGB4_MSG_AN);
		पूर्ण

		अगर (unlikely(ret)) अणु
			/* couldn't process descriptor, back off क्रम recovery */
			q->next_पूर्णांकr_params = QINTR_TIMER_IDX_V(NOMEM_TMR_IDX);
			अवरोध;
		पूर्ण

		rspq_next(q);
		budget_left--;
	पूर्ण

	अगर (q->offset >= 0 && fl_cap(&rxq->fl) - rxq->fl.avail >= 16)
		__refill_fl(q->adap, &rxq->fl);
	वापस budget - budget_left;
पूर्ण

/**
 *	napi_rx_handler - the NAPI handler क्रम Rx processing
 *	@napi: the napi instance
 *	@budget: how many packets we can process in this round
 *
 *	Handler क्रम new data events when using NAPI.  This करोes not need any
 *	locking or protection from पूर्णांकerrupts as data पूर्णांकerrupts are off at
 *	this poपूर्णांक and other adapter पूर्णांकerrupts करो not पूर्णांकerfere (the latter
 *	in not a concern at all with MSI-X as non-data पूर्णांकerrupts then have
 *	a separate handler).
 */
अटल पूर्णांक napi_rx_handler(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक params;
	काष्ठा sge_rspq *q = container_of(napi, काष्ठा sge_rspq, napi);
	पूर्णांक work_करोne;
	u32 val;

	work_करोne = process_responses(q, budget);
	अगर (likely(work_करोne < budget)) अणु
		पूर्णांक समयr_index;

		napi_complete_करोne(napi, work_करोne);
		समयr_index = QINTR_TIMER_IDX_G(q->next_पूर्णांकr_params);

		अगर (q->adaptive_rx) अणु
			अगर (work_करोne > max(समयr_pkt_quota[समयr_index],
					    MIN_NAPI_WORK))
				समयr_index = (समयr_index + 1);
			अन्यथा
				समयr_index = समयr_index - 1;

			समयr_index = clamp(समयr_index, 0, SGE_TIMERREGS - 1);
			q->next_पूर्णांकr_params =
					QINTR_TIMER_IDX_V(समयr_index) |
					QINTR_CNT_EN_V(0);
			params = q->next_पूर्णांकr_params;
		पूर्ण अन्यथा अणु
			params = q->next_पूर्णांकr_params;
			q->next_पूर्णांकr_params = q->पूर्णांकr_params;
		पूर्ण
	पूर्ण अन्यथा
		params = QINTR_TIMER_IDX_V(7);

	val = CIDXINC_V(work_करोne) | SEINTARM_V(params);

	/* If we करोn't have access to the new User GTS (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(q->bar2_addr == शून्य)) अणु
		t4_ग_लिखो_reg(q->adap, MYPF_REG(SGE_PF_GTS_A),
			     val | INGRESSQID_V((u32)q->cntxt_id));
	पूर्ण अन्यथा अणु
		ग_लिखोl(val | INGRESSQID_V(q->bar2_qid),
		       q->bar2_addr + SGE_UDB_GTS);
		wmb();
	पूर्ण
	वापस work_करोne;
पूर्ण

व्योम cxgb4_ethofld_restart(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sge_eosw_txq *eosw_txq = from_tasklet(eosw_txq, t,
						     qresume_tsk);
	पूर्णांक pktcount;

	spin_lock(&eosw_txq->lock);
	pktcount = eosw_txq->cidx - eosw_txq->last_cidx;
	अगर (pktcount < 0)
		pktcount += eosw_txq->ndesc;

	अगर (pktcount) अणु
		cxgb4_eosw_txq_मुक्त_desc(netdev2adap(eosw_txq->netdev),
					 eosw_txq, pktcount);
		eosw_txq->inuse -= pktcount;
	पूर्ण

	/* There may be some packets रुकोing क्रम completions. So,
	 * attempt to send these packets now.
	 */
	ethofld_xmit(eosw_txq->netdev, eosw_txq);
	spin_unlock(&eosw_txq->lock);
पूर्ण

/* cxgb4_ethofld_rx_handler - Process ETHOFLD Tx completions
 * @q: the response queue that received the packet
 * @rsp: the response queue descriptor holding the CPL message
 * @si: the gather list of packet fragments
 *
 * Process a ETHOFLD Tx completion. Increment the cidx here, but
 * मुक्त up the descriptors in a tasklet later.
 */
पूर्णांक cxgb4_ethofld_rx_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
			     स्थिर काष्ठा pkt_gl *si)
अणु
	u8 opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;

	/* skip RSS header */
	rsp++;

	अगर (opcode == CPL_FW4_ACK) अणु
		स्थिर काष्ठा cpl_fw4_ack *cpl;
		काष्ठा sge_eosw_txq *eosw_txq;
		काष्ठा eotid_entry *entry;
		काष्ठा sk_buff *skb;
		u32 hdr_len, eotid;
		u8 flits, wrlen16;
		पूर्णांक credits;

		cpl = (स्थिर काष्ठा cpl_fw4_ack *)rsp;
		eotid = CPL_FW4_ACK_FLOWID_G(ntohl(OPCODE_TID(cpl))) -
			q->adap->tids.eotid_base;
		entry = cxgb4_lookup_eotid(&q->adap->tids, eotid);
		अगर (!entry)
			जाओ out_करोne;

		eosw_txq = (काष्ठा sge_eosw_txq *)entry->data;
		अगर (!eosw_txq)
			जाओ out_करोne;

		spin_lock(&eosw_txq->lock);
		credits = cpl->credits;
		जबतक (credits > 0) अणु
			skb = eosw_txq->desc[eosw_txq->cidx].skb;
			अगर (!skb)
				अवरोध;

			अगर (unlikely((eosw_txq->state ==
				      CXGB4_EO_STATE_FLOWC_OPEN_REPLY ||
				      eosw_txq->state ==
				      CXGB4_EO_STATE_FLOWC_CLOSE_REPLY) &&
				     eosw_txq->cidx == eosw_txq->flowc_idx)) अणु
				flits = DIV_ROUND_UP(skb->len, 8);
				अगर (eosw_txq->state ==
				    CXGB4_EO_STATE_FLOWC_OPEN_REPLY)
					eosw_txq->state = CXGB4_EO_STATE_ACTIVE;
				अन्यथा
					eosw_txq->state = CXGB4_EO_STATE_CLOSED;
				complete(&eosw_txq->completion);
			पूर्ण अन्यथा अणु
				hdr_len = eth_get_headlen(eosw_txq->netdev,
							  skb->data,
							  skb_headlen(skb));
				flits = ethofld_calc_tx_flits(q->adap, skb,
							      hdr_len);
			पूर्ण
			eosw_txq_advance_index(&eosw_txq->cidx, 1,
					       eosw_txq->ndesc);
			wrlen16 = DIV_ROUND_UP(flits * 8, 16);
			credits -= wrlen16;
		पूर्ण

		eosw_txq->cred += cpl->credits;
		eosw_txq->ncompl--;

		spin_unlock(&eosw_txq->lock);

		/* Schedule a tasklet to reclaim SKBs and restart ETHOFLD Tx,
		 * अगर there were packets रुकोing क्रम completion.
		 */
		tasklet_schedule(&eosw_txq->qresume_tsk);
	पूर्ण

out_करोne:
	वापस 0;
पूर्ण

/*
 * The MSI-X पूर्णांकerrupt handler क्रम an SGE response queue.
 */
irqवापस_t t4_sge_पूर्णांकr_msix(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा sge_rspq *q = cookie;

	napi_schedule(&q->napi);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Process the indirect पूर्णांकerrupt entries in the पूर्णांकerrupt queue and kick off
 * NAPI क्रम each queue that has generated an entry.
 */
अटल अचिन्हित पूर्णांक process_पूर्णांकrq(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक credits;
	स्थिर काष्ठा rsp_ctrl *rc;
	काष्ठा sge_rspq *q = &adap->sge.पूर्णांकrq;
	u32 val;

	spin_lock(&adap->sge.पूर्णांकrq_lock);
	क्रम (credits = 0; ; credits++) अणु
		rc = (व्योम *)q->cur_desc + (q->iqe_len - माप(*rc));
		अगर (!is_new_response(rc, q))
			अवरोध;

		dma_rmb();
		अगर (RSPD_TYPE_G(rc->type_gen) == RSPD_TYPE_INTR_X) अणु
			अचिन्हित पूर्णांक qid = ntohl(rc->pldbuflen_qid);

			qid -= adap->sge.ingr_start;
			napi_schedule(&adap->sge.ingr_map[qid]->napi);
		पूर्ण

		rspq_next(q);
	पूर्ण

	val =  CIDXINC_V(credits) | SEINTARM_V(q->पूर्णांकr_params);

	/* If we करोn't have access to the new User GTS (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(q->bar2_addr == शून्य)) अणु
		t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_GTS_A),
			     val | INGRESSQID_V(q->cntxt_id));
	पूर्ण अन्यथा अणु
		ग_लिखोl(val | INGRESSQID_V(q->bar2_qid),
		       q->bar2_addr + SGE_UDB_GTS);
		wmb();
	पूर्ण
	spin_unlock(&adap->sge.पूर्णांकrq_lock);
	वापस credits;
पूर्ण

/*
 * The MSI पूर्णांकerrupt handler, which handles data events from SGE response queues
 * as well as error and other async events as they all use the same MSI vector.
 */
अटल irqवापस_t t4_पूर्णांकr_msi(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा adapter *adap = cookie;

	अगर (adap->flags & CXGB4_MASTER_PF)
		t4_slow_पूर्णांकr_handler(adap);
	process_पूर्णांकrq(adap);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Interrupt handler क्रम legacy INTx पूर्णांकerrupts.
 * Handles data events from SGE response queues as well as error and other
 * async events as they all use the same पूर्णांकerrupt line.
 */
अटल irqवापस_t t4_पूर्णांकr_पूर्णांकx(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा adapter *adap = cookie;

	t4_ग_लिखो_reg(adap, MYPF_REG(PCIE_PF_CLI_A), 0);
	अगर (((adap->flags & CXGB4_MASTER_PF) && t4_slow_पूर्णांकr_handler(adap)) |
	    process_पूर्णांकrq(adap))
		वापस IRQ_HANDLED;
	वापस IRQ_NONE;             /* probably shared पूर्णांकerrupt */
पूर्ण

/**
 *	t4_पूर्णांकr_handler - select the top-level पूर्णांकerrupt handler
 *	@adap: the adapter
 *
 *	Selects the top-level पूर्णांकerrupt handler based on the type of पूर्णांकerrupts
 *	(MSI-X, MSI, or INTx).
 */
irq_handler_t t4_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	अगर (adap->flags & CXGB4_USING_MSIX)
		वापस t4_sge_पूर्णांकr_msix;
	अगर (adap->flags & CXGB4_USING_MSI)
		वापस t4_पूर्णांकr_msi;
	वापस t4_पूर्णांकr_पूर्णांकx;
पूर्ण

अटल व्योम sge_rx_समयr_cb(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ m;
	अचिन्हित पूर्णांक i;
	काष्ठा adapter *adap = from_समयr(adap, t, sge.rx_समयr);
	काष्ठा sge *s = &adap->sge;

	क्रम (i = 0; i < BITS_TO_LONGS(s->egr_sz); i++)
		क्रम (m = s->starving_fl[i]; m; m &= m - 1) अणु
			काष्ठा sge_eth_rxq *rxq;
			अचिन्हित पूर्णांक id = __ffs(m) + i * BITS_PER_LONG;
			काष्ठा sge_fl *fl = s->egr_map[id];

			clear_bit(id, s->starving_fl);
			smp_mb__after_atomic();

			अगर (fl_starving(adap, fl)) अणु
				rxq = container_of(fl, काष्ठा sge_eth_rxq, fl);
				अगर (napi_reschedule(&rxq->rspq.napi))
					fl->starving++;
				अन्यथा
					set_bit(id, s->starving_fl);
			पूर्ण
		पूर्ण
	/* The reमुख्यder of the SGE RX Timer Callback routine is dedicated to
	 * global Master PF activities like checking क्रम chip ingress stalls,
	 * etc.
	 */
	अगर (!(adap->flags & CXGB4_MASTER_PF))
		जाओ करोne;

	t4_idma_monitor(adap, &s->idma_monitor, HZ, RX_QCHECK_PERIOD);

करोne:
	mod_समयr(&s->rx_समयr, jअगरfies + RX_QCHECK_PERIOD);
पूर्ण

अटल व्योम sge_tx_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adap = from_समयr(adap, t, sge.tx_समयr);
	काष्ठा sge *s = &adap->sge;
	अचिन्हित दीर्घ m, period;
	अचिन्हित पूर्णांक i, budget;

	क्रम (i = 0; i < BITS_TO_LONGS(s->egr_sz); i++)
		क्रम (m = s->txq_maperr[i]; m; m &= m - 1) अणु
			अचिन्हित दीर्घ id = __ffs(m) + i * BITS_PER_LONG;
			काष्ठा sge_uld_txq *txq = s->egr_map[id];

			clear_bit(id, s->txq_maperr);
			tasklet_schedule(&txq->qresume_tsk);
		पूर्ण

	अगर (!is_t4(adap->params.chip)) अणु
		काष्ठा sge_eth_txq *q = &s->ptptxq;
		पूर्णांक avail;

		spin_lock(&adap->ptp_lock);
		avail = reclaimable(&q->q);

		अगर (avail) अणु
			मुक्त_tx_desc(adap, &q->q, avail, false);
			q->q.in_use -= avail;
		पूर्ण
		spin_unlock(&adap->ptp_lock);
	पूर्ण

	budget = MAX_TIMER_TX_RECLAIM;
	i = s->ethtxq_rover;
	करो अणु
		budget -= t4_sge_eth_txq_egress_update(adap, &s->ethtxq[i],
						       budget);
		अगर (!budget)
			अवरोध;

		अगर (++i >= s->ethqsets)
			i = 0;
	पूर्ण जबतक (i != s->ethtxq_rover);
	s->ethtxq_rover = i;

	अगर (budget == 0) अणु
		/* If we found too many reclaimable packets schedule a समयr
		 * in the near future to जारी where we left off.
		 */
		period = 2;
	पूर्ण अन्यथा अणु
		/* We reclaimed all reclaimable TX Descriptors, so reschedule
		 * at the normal period.
		 */
		period = TX_QCHECK_PERIOD;
	पूर्ण

	mod_समयr(&s->tx_समयr, jअगरfies + period);
पूर्ण

/**
 *	bar2_address - वापस the BAR2 address क्रम an SGE Queue's Registers
 *	@adapter: the adapter
 *	@qid: the SGE Queue ID
 *	@qtype: the SGE Queue Type (Egress or Ingress)
 *	@pbar2_qid: BAR2 Queue ID or 0 क्रम Queue ID inferred SGE Queues
 *
 *	Returns the BAR2 address क्रम the SGE Queue Registers associated with
 *	@qid.  If BAR2 SGE Registers aren't available, वापसs शून्य.  Also
 *	वापसs the BAR2 Queue ID to be used with ग_लिखोs to the BAR2 SGE
 *	Queue Registers.  If the BAR2 Queue ID is 0, then "Inferred Queue ID"
 *	Registers are supported (e.g. the Write Combining Doorbell Buffer).
 */
अटल व्योम __iomem *bar2_address(काष्ठा adapter *adapter,
				  अचिन्हित पूर्णांक qid,
				  क्रमागत t4_bar2_qtype qtype,
				  अचिन्हित पूर्णांक *pbar2_qid)
अणु
	u64 bar2_qoffset;
	पूर्णांक ret;

	ret = t4_bar2_sge_qregs(adapter, qid, qtype, 0,
				&bar2_qoffset, pbar2_qid);
	अगर (ret)
		वापस शून्य;

	वापस adapter->bar2 + bar2_qoffset;
पूर्ण

/* @पूर्णांकr_idx: MSI/MSI-X vector अगर >=0, -(असलolute qid + 1) अगर < 0
 * @cong: < 0 -> no congestion feedback, >= 0 -> congestion channel map
 */
पूर्णांक t4_sge_alloc_rxq(काष्ठा adapter *adap, काष्ठा sge_rspq *iq, bool fwevtq,
		     काष्ठा net_device *dev, पूर्णांक पूर्णांकr_idx,
		     काष्ठा sge_fl *fl, rspq_handler_t hnd,
		     rspq_flush_handler_t flush_hnd, पूर्णांक cong)
अणु
	पूर्णांक ret, flsz = 0;
	काष्ठा fw_iq_cmd c;
	काष्ठा sge *s = &adap->sge;
	काष्ठा port_info *pi = netdev_priv(dev);
	पूर्णांक relaxed = !(adap->flags & CXGB4_ROOT_NO_RELAXED_ORDERING);

	/* Size needs to be multiple of 16, including status entry. */
	iq->size = roundup(iq->size, 16);

	iq->desc = alloc_ring(adap->pdev_dev, iq->size, iq->iqe_len, 0,
			      &iq->phys_addr, शून्य, 0,
			      dev_to_node(adap->pdev_dev));
	अगर (!iq->desc)
		वापस -ENOMEM;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = htonl(FW_CMD_OP_V(FW_IQ_CMD) | FW_CMD_REQUEST_F |
			    FW_CMD_WRITE_F | FW_CMD_EXEC_F |
			    FW_IQ_CMD_PFN_V(adap->pf) | FW_IQ_CMD_VFN_V(0));
	c.alloc_to_len16 = htonl(FW_IQ_CMD_ALLOC_F | FW_IQ_CMD_IQSTART_F |
				 FW_LEN16(c));
	c.type_to_iqandstindex = htonl(FW_IQ_CMD_TYPE_V(FW_IQ_TYPE_FL_INT_CAP) |
		FW_IQ_CMD_IQASYNCH_V(fwevtq) | FW_IQ_CMD_VIID_V(pi->viid) |
		FW_IQ_CMD_IQANDST_V(पूर्णांकr_idx < 0) |
		FW_IQ_CMD_IQANUD_V(UPDATEDELIVERY_INTERRUPT_X) |
		FW_IQ_CMD_IQANDSTINDEX_V(पूर्णांकr_idx >= 0 ? पूर्णांकr_idx :
							-पूर्णांकr_idx - 1));
	c.iqdroprss_to_iqesize = htons(FW_IQ_CMD_IQPCIECH_V(pi->tx_chan) |
		FW_IQ_CMD_IQGTSMODE_F |
		FW_IQ_CMD_IQINTCNTTHRESH_V(iq->pktcnt_idx) |
		FW_IQ_CMD_IQESIZE_V(ilog2(iq->iqe_len) - 4));
	c.iqsize = htons(iq->size);
	c.iqaddr = cpu_to_be64(iq->phys_addr);
	अगर (cong >= 0)
		c.iqns_to_fl0congen = htonl(FW_IQ_CMD_IQFLINTCONGEN_F |
				FW_IQ_CMD_IQTYPE_V(cong ? FW_IQ_IQTYPE_NIC
							:  FW_IQ_IQTYPE_OFLD));

	अगर (fl) अणु
		अचिन्हित पूर्णांक chip_ver =
			CHELSIO_CHIP_VERSION(adap->params.chip);

		/* Allocate the ring क्रम the hardware मुक्त list (with space
		 * क्रम its status page) aदीर्घ with the associated software
		 * descriptor ring.  The मुक्त list size needs to be a multiple
		 * of the Egress Queue Unit and at least 2 Egress Units larger
		 * than the SGE's Egress Congrestion Threshold
		 * (fl_starve_thres - 1).
		 */
		अगर (fl->size < s->fl_starve_thres - 1 + 2 * 8)
			fl->size = s->fl_starve_thres - 1 + 2 * 8;
		fl->size = roundup(fl->size, 8);
		fl->desc = alloc_ring(adap->pdev_dev, fl->size, माप(__be64),
				      माप(काष्ठा rx_sw_desc), &fl->addr,
				      &fl->sdesc, s->stat_len,
				      dev_to_node(adap->pdev_dev));
		अगर (!fl->desc)
			जाओ fl_nomem;

		flsz = fl->size / 8 + s->stat_len / माप(काष्ठा tx_desc);
		c.iqns_to_fl0congen |= htonl(FW_IQ_CMD_FL0PACKEN_F |
					     FW_IQ_CMD_FL0FETCHRO_V(relaxed) |
					     FW_IQ_CMD_FL0DATARO_V(relaxed) |
					     FW_IQ_CMD_FL0PADEN_F);
		अगर (cong >= 0)
			c.iqns_to_fl0congen |=
				htonl(FW_IQ_CMD_FL0CNGCHMAP_V(cong) |
				      FW_IQ_CMD_FL0CONGCIF_F |
				      FW_IQ_CMD_FL0CONGEN_F);
		/* In T6, क्रम egress queue type FL there is पूर्णांकernal overhead
		 * of 16B क्रम header going पूर्णांकo FLM module.  Hence the maximum
		 * allowed burst size is 448 bytes.  For T4/T5, the hardware
		 * करोesn't coalesce fetch requests अगर more than 64 bytes of
		 * Free List poपूर्णांकers are provided, so we use a 128-byte Fetch
		 * Burst Minimum there (T6 implements coalescing so we can use
		 * the smaller 64-byte value there).
		 */
		c.fl0dcaen_to_fl0cidxfthresh =
			htons(FW_IQ_CMD_FL0FBMIN_V(chip_ver <= CHELSIO_T5 ?
						   FETCHBURSTMIN_128B_X :
						   FETCHBURSTMIN_64B_T6_X) |
			      FW_IQ_CMD_FL0FBMAX_V((chip_ver <= CHELSIO_T5) ?
						   FETCHBURSTMAX_512B_X :
						   FETCHBURSTMAX_256B_X));
		c.fl0size = htons(flsz);
		c.fl0addr = cpu_to_be64(fl->addr);
	पूर्ण

	ret = t4_wr_mbox(adap, adap->mbox, &c, माप(c), &c);
	अगर (ret)
		जाओ err;

	netअगर_napi_add(dev, &iq->napi, napi_rx_handler, 64);
	iq->cur_desc = iq->desc;
	iq->cidx = 0;
	iq->gen = 1;
	iq->next_पूर्णांकr_params = iq->पूर्णांकr_params;
	iq->cntxt_id = ntohs(c.iqid);
	iq->असल_id = ntohs(c.physiqid);
	iq->bar2_addr = bar2_address(adap,
				     iq->cntxt_id,
				     T4_BAR2_QTYPE_INGRESS,
				     &iq->bar2_qid);
	iq->size--;                           /* subtract status entry */
	iq->netdev = dev;
	iq->handler = hnd;
	iq->flush_handler = flush_hnd;

	स_रखो(&iq->lro_mgr, 0, माप(काष्ठा t4_lro_mgr));
	skb_queue_head_init(&iq->lro_mgr.lroq);

	/* set offset to -1 to distinguish ingress queues without FL */
	iq->offset = fl ? 0 : -1;

	adap->sge.ingr_map[iq->cntxt_id - adap->sge.ingr_start] = iq;

	अगर (fl) अणु
		fl->cntxt_id = ntohs(c.fl0id);
		fl->avail = fl->pend_cred = 0;
		fl->pidx = fl->cidx = 0;
		fl->alloc_failed = fl->large_alloc_failed = fl->starving = 0;
		adap->sge.egr_map[fl->cntxt_id - adap->sge.egr_start] = fl;

		/* Note, we must initialize the BAR2 Free List User Doorbell
		 * inक्रमmation beक्रमe refilling the Free List!
		 */
		fl->bar2_addr = bar2_address(adap,
					     fl->cntxt_id,
					     T4_BAR2_QTYPE_EGRESS,
					     &fl->bar2_qid);
		refill_fl(adap, fl, fl_cap(fl), GFP_KERNEL);
	पूर्ण

	/* For T5 and later we attempt to set up the Congestion Manager values
	 * of the new RX Ethernet Queue.  This should really be handled by
	 * firmware because it's more complex than any host driver wants to
	 * get involved with and it's dअगरferent per chip and this is almost
	 * certainly wrong.  Firmware would be wrong as well, but it would be
	 * a lot easier to fix in one place ...  For now we करो something very
	 * simple (and hopefully less wrong).
	 */
	अगर (!is_t4(adap->params.chip) && cong >= 0) अणु
		u32 param, val, ch_map = 0;
		पूर्णांक i;
		u16 cng_ch_bits_log = adap->params.arch.cng_ch_bits_log;

		param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DMAQ_CONM_CTXT) |
			 FW_PARAMS_PARAM_YZ_V(iq->cntxt_id));
		अगर (cong == 0) अणु
			val = CONMCTXT_CNGTPMODE_V(CONMCTXT_CNGTPMODE_QUEUE_X);
		पूर्ण अन्यथा अणु
			val =
			    CONMCTXT_CNGTPMODE_V(CONMCTXT_CNGTPMODE_CHANNEL_X);
			क्रम (i = 0; i < 4; i++) अणु
				अगर (cong & (1 << i))
					ch_map |= 1 << (i << cng_ch_bits_log);
			पूर्ण
			val |= CONMCTXT_CNGCHMAP_V(ch_map);
		पूर्ण
		ret = t4_set_params(adap, adap->mbox, adap->pf, 0, 1,
				    &param, &val);
		अगर (ret)
			dev_warn(adap->pdev_dev, "Failed to set Congestion"
				 " Manager Context for Ingress Queue %d: %d\n",
				 iq->cntxt_id, -ret);
	पूर्ण

	वापस 0;

fl_nomem:
	ret = -ENOMEM;
err:
	अगर (iq->desc) अणु
		dma_मुक्त_coherent(adap->pdev_dev, iq->size * iq->iqe_len,
				  iq->desc, iq->phys_addr);
		iq->desc = शून्य;
	पूर्ण
	अगर (fl && fl->desc) अणु
		kमुक्त(fl->sdesc);
		fl->sdesc = शून्य;
		dma_मुक्त_coherent(adap->pdev_dev, flsz * माप(काष्ठा tx_desc),
				  fl->desc, fl->addr);
		fl->desc = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम init_txq(काष्ठा adapter *adap, काष्ठा sge_txq *q, अचिन्हित पूर्णांक id)
अणु
	q->cntxt_id = id;
	q->bar2_addr = bar2_address(adap,
				    q->cntxt_id,
				    T4_BAR2_QTYPE_EGRESS,
				    &q->bar2_qid);
	q->in_use = 0;
	q->cidx = q->pidx = 0;
	q->stops = q->restarts = 0;
	q->stat = (व्योम *)&q->desc[q->size];
	spin_lock_init(&q->db_lock);
	adap->sge.egr_map[id - adap->sge.egr_start] = q;
पूर्ण

/**
 *	t4_sge_alloc_eth_txq - allocate an Ethernet TX Queue
 *	@adap: the adapter
 *	@txq: the SGE Ethernet TX Queue to initialize
 *	@dev: the Linux Network Device
 *	@netdevq: the corresponding Linux TX Queue
 *	@iqid: the Ingress Queue to which to deliver CIDX Update messages
 *	@dbqt: whether this TX Queue will use the SGE Doorbell Queue Timers
 */
पूर्णांक t4_sge_alloc_eth_txq(काष्ठा adapter *adap, काष्ठा sge_eth_txq *txq,
			 काष्ठा net_device *dev, काष्ठा netdev_queue *netdevq,
			 अचिन्हित पूर्णांक iqid, u8 dbqt)
अणु
	अचिन्हित पूर्णांक chip_ver = CHELSIO_CHIP_VERSION(adap->params.chip);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा sge *s = &adap->sge;
	काष्ठा fw_eq_eth_cmd c;
	पूर्णांक ret, nentries;

	/* Add status entries */
	nentries = txq->q.size + s->stat_len / माप(काष्ठा tx_desc);

	txq->q.desc = alloc_ring(adap->pdev_dev, txq->q.size,
			माप(काष्ठा tx_desc), माप(काष्ठा tx_sw_desc),
			&txq->q.phys_addr, &txq->q.sdesc, s->stat_len,
			netdev_queue_numa_node_पढ़ो(netdevq));
	अगर (!txq->q.desc)
		वापस -ENOMEM;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = htonl(FW_CMD_OP_V(FW_EQ_ETH_CMD) | FW_CMD_REQUEST_F |
			    FW_CMD_WRITE_F | FW_CMD_EXEC_F |
			    FW_EQ_ETH_CMD_PFN_V(adap->pf) |
			    FW_EQ_ETH_CMD_VFN_V(0));
	c.alloc_to_len16 = htonl(FW_EQ_ETH_CMD_ALLOC_F |
				 FW_EQ_ETH_CMD_EQSTART_F | FW_LEN16(c));

	/* For TX Ethernet Queues using the SGE Doorbell Queue Timer
	 * mechanism, we use Ingress Queue messages क्रम Hardware Consumer
	 * Index Updates on the TX Queue.  Otherwise we have the Hardware
	 * ग_लिखो the CIDX Updates पूर्णांकo the Status Page at the end of the
	 * TX Queue.
	 */
	c.स्वतःequiqe_to_viid = htonl(((chip_ver <= CHELSIO_T5) ?
				      FW_EQ_ETH_CMD_AUTOEQUIQE_F :
				      FW_EQ_ETH_CMD_AUTOEQUEQE_F) |
				     FW_EQ_ETH_CMD_VIID_V(pi->viid));

	c.fetchszm_to_iqid =
		htonl(FW_EQ_ETH_CMD_HOSTFCMODE_V((chip_ver <= CHELSIO_T5) ?
						 HOSTFCMODE_INGRESS_QUEUE_X :
						 HOSTFCMODE_STATUS_PAGE_X) |
		      FW_EQ_ETH_CMD_PCIECHN_V(pi->tx_chan) |
		      FW_EQ_ETH_CMD_FETCHRO_F | FW_EQ_ETH_CMD_IQID_V(iqid));

	/* Note that the CIDX Flush Threshold should match MAX_TX_RECLAIM. */
	c.dcaen_to_eqsize =
		htonl(FW_EQ_ETH_CMD_FBMIN_V(chip_ver <= CHELSIO_T5
					    ? FETCHBURSTMIN_64B_X
					    : FETCHBURSTMIN_64B_T6_X) |
		      FW_EQ_ETH_CMD_FBMAX_V(FETCHBURSTMAX_512B_X) |
		      FW_EQ_ETH_CMD_CIDXFTHRESH_V(CIDXFLUSHTHRESH_32_X) |
		      FW_EQ_ETH_CMD_CIDXFTHRESHO_V(chip_ver == CHELSIO_T5) |
		      FW_EQ_ETH_CMD_EQSIZE_V(nentries));

	c.eqaddr = cpu_to_be64(txq->q.phys_addr);

	/* If we're using the SGE Doorbell Queue Timer mechanism, pass in the
	 * currently configured Timer Index.  THis can be changed later via an
	 * ethtool -C tx-usecs अणुTimer Valपूर्ण command.  Note that the SGE
	 * Doorbell Queue mode is currently स्वतःmatically enabled in the
	 * Firmware by setting either AUTOEQUEQE or AUTOEQUIQE ...
	 */
	अगर (dbqt)
		c.समयren_समयrix =
			cpu_to_be32(FW_EQ_ETH_CMD_TIMEREN_F |
				    FW_EQ_ETH_CMD_TIMERIX_V(txq->dbqसमयrix));

	ret = t4_wr_mbox(adap, adap->mbox, &c, माप(c), &c);
	अगर (ret) अणु
		kमुक्त(txq->q.sdesc);
		txq->q.sdesc = शून्य;
		dma_मुक्त_coherent(adap->pdev_dev,
				  nentries * माप(काष्ठा tx_desc),
				  txq->q.desc, txq->q.phys_addr);
		txq->q.desc = शून्य;
		वापस ret;
	पूर्ण

	txq->q.q_type = CXGB4_TXQ_ETH;
	init_txq(adap, &txq->q, FW_EQ_ETH_CMD_EQID_G(ntohl(c.eqid_pkd)));
	txq->txq = netdevq;
	txq->tso = 0;
	txq->uso = 0;
	txq->tx_cso = 0;
	txq->vlan_ins = 0;
	txq->mapping_err = 0;
	txq->dbqt = dbqt;

	वापस 0;
पूर्ण

पूर्णांक t4_sge_alloc_ctrl_txq(काष्ठा adapter *adap, काष्ठा sge_ctrl_txq *txq,
			  काष्ठा net_device *dev, अचिन्हित पूर्णांक iqid,
			  अचिन्हित पूर्णांक cmplqid)
अणु
	अचिन्हित पूर्णांक chip_ver = CHELSIO_CHIP_VERSION(adap->params.chip);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा sge *s = &adap->sge;
	काष्ठा fw_eq_ctrl_cmd c;
	पूर्णांक ret, nentries;

	/* Add status entries */
	nentries = txq->q.size + s->stat_len / माप(काष्ठा tx_desc);

	txq->q.desc = alloc_ring(adap->pdev_dev, nentries,
				 माप(काष्ठा tx_desc), 0, &txq->q.phys_addr,
				 शून्य, 0, dev_to_node(adap->pdev_dev));
	अगर (!txq->q.desc)
		वापस -ENOMEM;

	c.op_to_vfn = htonl(FW_CMD_OP_V(FW_EQ_CTRL_CMD) | FW_CMD_REQUEST_F |
			    FW_CMD_WRITE_F | FW_CMD_EXEC_F |
			    FW_EQ_CTRL_CMD_PFN_V(adap->pf) |
			    FW_EQ_CTRL_CMD_VFN_V(0));
	c.alloc_to_len16 = htonl(FW_EQ_CTRL_CMD_ALLOC_F |
				 FW_EQ_CTRL_CMD_EQSTART_F | FW_LEN16(c));
	c.cmpliqid_eqid = htonl(FW_EQ_CTRL_CMD_CMPLIQID_V(cmplqid));
	c.physeqid_pkd = htonl(0);
	c.fetchszm_to_iqid =
		htonl(FW_EQ_CTRL_CMD_HOSTFCMODE_V(HOSTFCMODE_STATUS_PAGE_X) |
		      FW_EQ_CTRL_CMD_PCIECHN_V(pi->tx_chan) |
		      FW_EQ_CTRL_CMD_FETCHRO_F | FW_EQ_CTRL_CMD_IQID_V(iqid));
	c.dcaen_to_eqsize =
		htonl(FW_EQ_CTRL_CMD_FBMIN_V(chip_ver <= CHELSIO_T5
					     ? FETCHBURSTMIN_64B_X
					     : FETCHBURSTMIN_64B_T6_X) |
		      FW_EQ_CTRL_CMD_FBMAX_V(FETCHBURSTMAX_512B_X) |
		      FW_EQ_CTRL_CMD_CIDXFTHRESH_V(CIDXFLUSHTHRESH_32_X) |
		      FW_EQ_CTRL_CMD_EQSIZE_V(nentries));
	c.eqaddr = cpu_to_be64(txq->q.phys_addr);

	ret = t4_wr_mbox(adap, adap->mbox, &c, माप(c), &c);
	अगर (ret) अणु
		dma_मुक्त_coherent(adap->pdev_dev,
				  nentries * माप(काष्ठा tx_desc),
				  txq->q.desc, txq->q.phys_addr);
		txq->q.desc = शून्य;
		वापस ret;
	पूर्ण

	txq->q.q_type = CXGB4_TXQ_CTRL;
	init_txq(adap, &txq->q, FW_EQ_CTRL_CMD_EQID_G(ntohl(c.cmpliqid_eqid)));
	txq->adap = adap;
	skb_queue_head_init(&txq->sendq);
	tasklet_setup(&txq->qresume_tsk, restart_ctrlq);
	txq->full = 0;
	वापस 0;
पूर्ण

पूर्णांक t4_sge_mod_ctrl_txq(काष्ठा adapter *adap, अचिन्हित पूर्णांक eqid,
			अचिन्हित पूर्णांक cmplqid)
अणु
	u32 param, val;

	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DMAQ_EQ_CMPLIQID_CTRL) |
		 FW_PARAMS_PARAM_YZ_V(eqid));
	val = cmplqid;
	वापस t4_set_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
पूर्ण

अटल पूर्णांक t4_sge_alloc_ofld_txq(काष्ठा adapter *adap, काष्ठा sge_txq *q,
				 काष्ठा net_device *dev, u32 cmd, u32 iqid)
अणु
	अचिन्हित पूर्णांक chip_ver = CHELSIO_CHIP_VERSION(adap->params.chip);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा sge *s = &adap->sge;
	काष्ठा fw_eq_ofld_cmd c;
	u32 fb_min, nentries;
	पूर्णांक ret;

	/* Add status entries */
	nentries = q->size + s->stat_len / माप(काष्ठा tx_desc);
	q->desc = alloc_ring(adap->pdev_dev, q->size, माप(काष्ठा tx_desc),
			     माप(काष्ठा tx_sw_desc), &q->phys_addr,
			     &q->sdesc, s->stat_len, NUMA_NO_NODE);
	अगर (!q->desc)
		वापस -ENOMEM;

	अगर (chip_ver <= CHELSIO_T5)
		fb_min = FETCHBURSTMIN_64B_X;
	अन्यथा
		fb_min = FETCHBURSTMIN_64B_T6_X;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = htonl(FW_CMD_OP_V(cmd) | FW_CMD_REQUEST_F |
			    FW_CMD_WRITE_F | FW_CMD_EXEC_F |
			    FW_EQ_OFLD_CMD_PFN_V(adap->pf) |
			    FW_EQ_OFLD_CMD_VFN_V(0));
	c.alloc_to_len16 = htonl(FW_EQ_OFLD_CMD_ALLOC_F |
				 FW_EQ_OFLD_CMD_EQSTART_F | FW_LEN16(c));
	c.fetchszm_to_iqid =
		htonl(FW_EQ_OFLD_CMD_HOSTFCMODE_V(HOSTFCMODE_STATUS_PAGE_X) |
		      FW_EQ_OFLD_CMD_PCIECHN_V(pi->tx_chan) |
		      FW_EQ_OFLD_CMD_FETCHRO_F | FW_EQ_OFLD_CMD_IQID_V(iqid));
	c.dcaen_to_eqsize =
		htonl(FW_EQ_OFLD_CMD_FBMIN_V(fb_min) |
		      FW_EQ_OFLD_CMD_FBMAX_V(FETCHBURSTMAX_512B_X) |
		      FW_EQ_OFLD_CMD_CIDXFTHRESH_V(CIDXFLUSHTHRESH_32_X) |
		      FW_EQ_OFLD_CMD_EQSIZE_V(nentries));
	c.eqaddr = cpu_to_be64(q->phys_addr);

	ret = t4_wr_mbox(adap, adap->mbox, &c, माप(c), &c);
	अगर (ret) अणु
		kमुक्त(q->sdesc);
		q->sdesc = शून्य;
		dma_मुक्त_coherent(adap->pdev_dev,
				  nentries * माप(काष्ठा tx_desc),
				  q->desc, q->phys_addr);
		q->desc = शून्य;
		वापस ret;
	पूर्ण

	init_txq(adap, q, FW_EQ_OFLD_CMD_EQID_G(ntohl(c.eqid_pkd)));
	वापस 0;
पूर्ण

पूर्णांक t4_sge_alloc_uld_txq(काष्ठा adapter *adap, काष्ठा sge_uld_txq *txq,
			 काष्ठा net_device *dev, अचिन्हित पूर्णांक iqid,
			 अचिन्हित पूर्णांक uld_type)
अणु
	u32 cmd = FW_EQ_OFLD_CMD;
	पूर्णांक ret;

	अगर (unlikely(uld_type == CXGB4_TX_CRYPTO))
		cmd = FW_EQ_CTRL_CMD;

	ret = t4_sge_alloc_ofld_txq(adap, &txq->q, dev, cmd, iqid);
	अगर (ret)
		वापस ret;

	txq->q.q_type = CXGB4_TXQ_ULD;
	txq->adap = adap;
	skb_queue_head_init(&txq->sendq);
	tasklet_setup(&txq->qresume_tsk, restart_ofldq);
	txq->full = 0;
	txq->mapping_err = 0;
	वापस 0;
पूर्ण

पूर्णांक t4_sge_alloc_ethofld_txq(काष्ठा adapter *adap, काष्ठा sge_eohw_txq *txq,
			     काष्ठा net_device *dev, u32 iqid)
अणु
	पूर्णांक ret;

	ret = t4_sge_alloc_ofld_txq(adap, &txq->q, dev, FW_EQ_OFLD_CMD, iqid);
	अगर (ret)
		वापस ret;

	txq->q.q_type = CXGB4_TXQ_ULD;
	spin_lock_init(&txq->lock);
	txq->adap = adap;
	txq->tso = 0;
	txq->uso = 0;
	txq->tx_cso = 0;
	txq->vlan_ins = 0;
	txq->mapping_err = 0;
	वापस 0;
पूर्ण

व्योम मुक्त_txq(काष्ठा adapter *adap, काष्ठा sge_txq *q)
अणु
	काष्ठा sge *s = &adap->sge;

	dma_मुक्त_coherent(adap->pdev_dev,
			  q->size * माप(काष्ठा tx_desc) + s->stat_len,
			  q->desc, q->phys_addr);
	q->cntxt_id = 0;
	q->sdesc = शून्य;
	q->desc = शून्य;
पूर्ण

व्योम मुक्त_rspq_fl(काष्ठा adapter *adap, काष्ठा sge_rspq *rq,
		  काष्ठा sge_fl *fl)
अणु
	काष्ठा sge *s = &adap->sge;
	अचिन्हित पूर्णांक fl_id = fl ? fl->cntxt_id : 0xffff;

	adap->sge.ingr_map[rq->cntxt_id - adap->sge.ingr_start] = शून्य;
	t4_iq_मुक्त(adap, adap->mbox, adap->pf, 0, FW_IQ_TYPE_FL_INT_CAP,
		   rq->cntxt_id, fl_id, 0xffff);
	dma_मुक्त_coherent(adap->pdev_dev, (rq->size + 1) * rq->iqe_len,
			  rq->desc, rq->phys_addr);
	netअगर_napi_del(&rq->napi);
	rq->netdev = शून्य;
	rq->cntxt_id = rq->असल_id = 0;
	rq->desc = शून्य;

	अगर (fl) अणु
		मुक्त_rx_bufs(adap, fl, fl->avail);
		dma_मुक्त_coherent(adap->pdev_dev, fl->size * 8 + s->stat_len,
				  fl->desc, fl->addr);
		kमुक्त(fl->sdesc);
		fl->sdesc = शून्य;
		fl->cntxt_id = 0;
		fl->desc = शून्य;
	पूर्ण
पूर्ण

/**
 *      t4_मुक्त_ofld_rxqs - मुक्त a block of consecutive Rx queues
 *      @adap: the adapter
 *      @n: number of queues
 *      @q: poपूर्णांकer to first queue
 *
 *      Release the resources of a consecutive block of offload Rx queues.
 */
व्योम t4_मुक्त_ofld_rxqs(काष्ठा adapter *adap, पूर्णांक n, काष्ठा sge_ofld_rxq *q)
अणु
	क्रम ( ; n; n--, q++)
		अगर (q->rspq.desc)
			मुक्त_rspq_fl(adap, &q->rspq,
				     q->fl.size ? &q->fl : शून्य);
पूर्ण

व्योम t4_sge_मुक्त_ethofld_txq(काष्ठा adapter *adap, काष्ठा sge_eohw_txq *txq)
अणु
	अगर (txq->q.desc) अणु
		t4_ofld_eq_मुक्त(adap, adap->mbox, adap->pf, 0,
				txq->q.cntxt_id);
		मुक्त_tx_desc(adap, &txq->q, txq->q.in_use, false);
		kमुक्त(txq->q.sdesc);
		मुक्त_txq(adap, &txq->q);
	पूर्ण
पूर्ण

/**
 *	t4_मुक्त_sge_resources - मुक्त SGE resources
 *	@adap: the adapter
 *
 *	Frees resources used by the SGE queue sets.
 */
व्योम t4_मुक्त_sge_resources(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	काष्ठा sge_eth_rxq *eq;
	काष्ठा sge_eth_txq *etq;

	/* stop all Rx queues in order to start them draining */
	क्रम (i = 0; i < adap->sge.ethqsets; i++) अणु
		eq = &adap->sge.ethrxq[i];
		अगर (eq->rspq.desc)
			t4_iq_stop(adap, adap->mbox, adap->pf, 0,
				   FW_IQ_TYPE_FL_INT_CAP,
				   eq->rspq.cntxt_id,
				   eq->fl.size ? eq->fl.cntxt_id : 0xffff,
				   0xffff);
	पूर्ण

	/* clean up Ethernet Tx/Rx queues */
	क्रम (i = 0; i < adap->sge.ethqsets; i++) अणु
		eq = &adap->sge.ethrxq[i];
		अगर (eq->rspq.desc)
			मुक्त_rspq_fl(adap, &eq->rspq,
				     eq->fl.size ? &eq->fl : शून्य);
		अगर (eq->msix) अणु
			cxgb4_मुक्त_msix_idx_in_bmap(adap, eq->msix->idx);
			eq->msix = शून्य;
		पूर्ण

		etq = &adap->sge.ethtxq[i];
		अगर (etq->q.desc) अणु
			t4_eth_eq_मुक्त(adap, adap->mbox, adap->pf, 0,
				       etq->q.cntxt_id);
			__netअगर_tx_lock_bh(etq->txq);
			मुक्त_tx_desc(adap, &etq->q, etq->q.in_use, true);
			__netअगर_tx_unlock_bh(etq->txq);
			kमुक्त(etq->q.sdesc);
			मुक्त_txq(adap, &etq->q);
		पूर्ण
	पूर्ण

	/* clean up control Tx queues */
	क्रम (i = 0; i < ARRAY_SIZE(adap->sge.ctrlq); i++) अणु
		काष्ठा sge_ctrl_txq *cq = &adap->sge.ctrlq[i];

		अगर (cq->q.desc) अणु
			tasklet_समाप्त(&cq->qresume_tsk);
			t4_ctrl_eq_मुक्त(adap, adap->mbox, adap->pf, 0,
					cq->q.cntxt_id);
			__skb_queue_purge(&cq->sendq);
			मुक्त_txq(adap, &cq->q);
		पूर्ण
	पूर्ण

	अगर (adap->sge.fw_evtq.desc) अणु
		मुक्त_rspq_fl(adap, &adap->sge.fw_evtq, शून्य);
		अगर (adap->sge.fwevtq_msix_idx >= 0)
			cxgb4_मुक्त_msix_idx_in_bmap(adap,
						    adap->sge.fwevtq_msix_idx);
	पूर्ण

	अगर (adap->sge.nd_msix_idx >= 0)
		cxgb4_मुक्त_msix_idx_in_bmap(adap, adap->sge.nd_msix_idx);

	अगर (adap->sge.पूर्णांकrq.desc)
		मुक्त_rspq_fl(adap, &adap->sge.पूर्णांकrq, शून्य);

	अगर (!is_t4(adap->params.chip)) अणु
		etq = &adap->sge.ptptxq;
		अगर (etq->q.desc) अणु
			t4_eth_eq_मुक्त(adap, adap->mbox, adap->pf, 0,
				       etq->q.cntxt_id);
			spin_lock_bh(&adap->ptp_lock);
			मुक्त_tx_desc(adap, &etq->q, etq->q.in_use, true);
			spin_unlock_bh(&adap->ptp_lock);
			kमुक्त(etq->q.sdesc);
			मुक्त_txq(adap, &etq->q);
		पूर्ण
	पूर्ण

	/* clear the reverse egress queue map */
	स_रखो(adap->sge.egr_map, 0,
	       adap->sge.egr_sz * माप(*adap->sge.egr_map));
पूर्ण

व्योम t4_sge_start(काष्ठा adapter *adap)
अणु
	adap->sge.ethtxq_rover = 0;
	mod_समयr(&adap->sge.rx_समयr, jअगरfies + RX_QCHECK_PERIOD);
	mod_समयr(&adap->sge.tx_समयr, jअगरfies + TX_QCHECK_PERIOD);
पूर्ण

/**
 *	t4_sge_stop - disable SGE operation
 *	@adap: the adapter
 *
 *	Stop tasklets and समयrs associated with the DMA engine.  Note that
 *	this is effective only अगर measures have been taken to disable any HW
 *	events that may restart them.
 */
व्योम t4_sge_stop(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	काष्ठा sge *s = &adap->sge;

	अगर (s->rx_समयr.function)
		del_समयr_sync(&s->rx_समयr);
	अगर (s->tx_समयr.function)
		del_समयr_sync(&s->tx_समयr);

	अगर (is_offload(adap)) अणु
		काष्ठा sge_uld_txq_info *txq_info;

		txq_info = adap->sge.uld_txq_info[CXGB4_TX_OFLD];
		अगर (txq_info) अणु
			काष्ठा sge_uld_txq *txq = txq_info->uldtxq;

			क्रम_each_ofldtxq(&adap->sge, i) अणु
				अगर (txq->q.desc)
					tasklet_समाप्त(&txq->qresume_tsk);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_pci_uld(adap)) अणु
		काष्ठा sge_uld_txq_info *txq_info;

		txq_info = adap->sge.uld_txq_info[CXGB4_TX_CRYPTO];
		अगर (txq_info) अणु
			काष्ठा sge_uld_txq *txq = txq_info->uldtxq;

			क्रम_each_ofldtxq(&adap->sge, i) अणु
				अगर (txq->q.desc)
					tasklet_समाप्त(&txq->qresume_tsk);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(s->ctrlq); i++) अणु
		काष्ठा sge_ctrl_txq *cq = &s->ctrlq[i];

		अगर (cq->q.desc)
			tasklet_समाप्त(&cq->qresume_tsk);
	पूर्ण
पूर्ण

/**
 *	t4_sge_init_soft - grab core SGE values needed by SGE code
 *	@adap: the adapter
 *
 *	We need to grab the SGE operating parameters that we need to have
 *	in order to करो our job and make sure we can live with them.
 */

अटल पूर्णांक t4_sge_init_soft(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;
	u32 fl_small_pg, fl_large_pg, fl_small_mtu, fl_large_mtu;
	u32 समयr_value_0_and_1, समयr_value_2_and_3, समयr_value_4_and_5;
	u32 ingress_rx_threshold;

	/*
	 * Verअगरy that CPL messages are going to the Ingress Queue क्रम
	 * process_responses() and that only packet data is going to the
	 * Free Lists.
	 */
	अगर ((t4_पढ़ो_reg(adap, SGE_CONTROL_A) & RXPKTCPLMODE_F) !=
	    RXPKTCPLMODE_V(RXPKTCPLMODE_SPLIT_X)) अणु
		dev_err(adap->pdev_dev, "bad SGE CPL MODE\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Validate the Host Buffer Register Array indices that we want to
	 * use ...
	 *
	 * XXX Note that we should really पढ़ो through the Host Buffer Size
	 * XXX रेजिस्टर array and find the indices of the Buffer Sizes which
	 * XXX meet our needs!
	 */
	#घोषणा READ_FL_BUF(x) \
		t4_पढ़ो_reg(adap, SGE_FL_BUFFER_SIZE0_A+(x)*माप(u32))

	fl_small_pg = READ_FL_BUF(RX_SMALL_PG_BUF);
	fl_large_pg = READ_FL_BUF(RX_LARGE_PG_BUF);
	fl_small_mtu = READ_FL_BUF(RX_SMALL_MTU_BUF);
	fl_large_mtu = READ_FL_BUF(RX_LARGE_MTU_BUF);

	/* We only bother using the Large Page logic अगर the Large Page Buffer
	 * is larger than our Page Size Buffer.
	 */
	अगर (fl_large_pg <= fl_small_pg)
		fl_large_pg = 0;

	#अघोषित READ_FL_BUF

	/* The Page Size Buffer must be exactly equal to our Page Size and the
	 * Large Page Size Buffer should be 0 (per above) or a घातer of 2.
	 */
	अगर (fl_small_pg != PAGE_SIZE ||
	    (fl_large_pg & (fl_large_pg-1)) != 0) अणु
		dev_err(adap->pdev_dev, "bad SGE FL page buffer sizes [%d, %d]\n",
			fl_small_pg, fl_large_pg);
		वापस -EINVAL;
	पूर्ण
	अगर (fl_large_pg)
		s->fl_pg_order = ilog2(fl_large_pg) - PAGE_SHIFT;

	अगर (fl_small_mtu < FL_MTU_SMALL_बफ_मानE(adap) ||
	    fl_large_mtu < FL_MTU_LARGE_बफ_मानE(adap)) अणु
		dev_err(adap->pdev_dev, "bad SGE FL MTU sizes [%d, %d]\n",
			fl_small_mtu, fl_large_mtu);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Retrieve our RX पूर्णांकerrupt holकरोff समयr values and counter
	 * threshold values from the SGE parameters.
	 */
	समयr_value_0_and_1 = t4_पढ़ो_reg(adap, SGE_TIMER_VALUE_0_AND_1_A);
	समयr_value_2_and_3 = t4_पढ़ो_reg(adap, SGE_TIMER_VALUE_2_AND_3_A);
	समयr_value_4_and_5 = t4_पढ़ो_reg(adap, SGE_TIMER_VALUE_4_AND_5_A);
	s->समयr_val[0] = core_ticks_to_us(adap,
		TIMERVALUE0_G(समयr_value_0_and_1));
	s->समयr_val[1] = core_ticks_to_us(adap,
		TIMERVALUE1_G(समयr_value_0_and_1));
	s->समयr_val[2] = core_ticks_to_us(adap,
		TIMERVALUE2_G(समयr_value_2_and_3));
	s->समयr_val[3] = core_ticks_to_us(adap,
		TIMERVALUE3_G(समयr_value_2_and_3));
	s->समयr_val[4] = core_ticks_to_us(adap,
		TIMERVALUE4_G(समयr_value_4_and_5));
	s->समयr_val[5] = core_ticks_to_us(adap,
		TIMERVALUE5_G(समयr_value_4_and_5));

	ingress_rx_threshold = t4_पढ़ो_reg(adap, SGE_INGRESS_RX_THRESHOLD_A);
	s->counter_val[0] = THRESHOLD_0_G(ingress_rx_threshold);
	s->counter_val[1] = THRESHOLD_1_G(ingress_rx_threshold);
	s->counter_val[2] = THRESHOLD_2_G(ingress_rx_threshold);
	s->counter_val[3] = THRESHOLD_3_G(ingress_rx_threshold);

	वापस 0;
पूर्ण

/**
 *     t4_sge_init - initialize SGE
 *     @adap: the adapter
 *
 *     Perक्रमm low-level SGE code initialization needed every समय after a
 *     chip reset.
 */
पूर्णांक t4_sge_init(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;
	u32 sge_control, sge_conm_ctrl;
	पूर्णांक ret, egress_threshold;

	/*
	 * Ingress Padding Boundary and Egress Status Page Size are set up by
	 * t4_fixup_host_params().
	 */
	sge_control = t4_पढ़ो_reg(adap, SGE_CONTROL_A);
	s->pktshअगरt = PKTSHIFT_G(sge_control);
	s->stat_len = (sge_control & EGRSTATUSPAGESIZE_F) ? 128 : 64;

	s->fl_align = t4_fl_pkt_align(adap);
	ret = t4_sge_init_soft(adap);
	अगर (ret < 0)
		वापस ret;

	/*
	 * A FL with <= fl_starve_thres buffers is starving and a periodic
	 * समयr will attempt to refill it.  This needs to be larger than the
	 * SGE's Egress Congestion Threshold.  If it isn't, then we can get
	 * stuck रुकोing क्रम new packets जबतक the SGE is रुकोing क्रम us to
	 * give it more Free List entries.  (Note that the SGE's Egress
	 * Congestion Threshold is in units of 2 Free List poपूर्णांकers.) For T4,
	 * there was only a single field to control this.  For T5 there's the
	 * original field which now only applies to Unpacked Mode Free List
	 * buffers and a new field which only applies to Packed Mode Free List
	 * buffers.
	 */
	sge_conm_ctrl = t4_पढ़ो_reg(adap, SGE_CONM_CTRL_A);
	चयन (CHELSIO_CHIP_VERSION(adap->params.chip)) अणु
	हाल CHELSIO_T4:
		egress_threshold = EGRTHRESHOLD_G(sge_conm_ctrl);
		अवरोध;
	हाल CHELSIO_T5:
		egress_threshold = EGRTHRESHOLDPACKING_G(sge_conm_ctrl);
		अवरोध;
	हाल CHELSIO_T6:
		egress_threshold = T6_EGRTHRESHOLDPACKING_G(sge_conm_ctrl);
		अवरोध;
	शेष:
		dev_err(adap->pdev_dev, "Unsupported Chip version %d\n",
			CHELSIO_CHIP_VERSION(adap->params.chip));
		वापस -EINVAL;
	पूर्ण
	s->fl_starve_thres = 2*egress_threshold + 1;

	t4_idma_monitor_init(adap, &s->idma_monitor);

	/* Set up समयrs used क्रम recuring callbacks to process RX and TX
	 * administrative tasks.
	 */
	समयr_setup(&s->rx_समयr, sge_rx_समयr_cb, 0);
	समयr_setup(&s->tx_समयr, sge_tx_समयr_cb, 0);

	spin_lock_init(&s->पूर्णांकrq_lock);

	वापस 0;
पूर्ण
