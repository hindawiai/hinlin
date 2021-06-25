<शैली गुरु>
/*
 * This file is part of the Chelsio T4 PCI-E SR-IOV Virtual Function Ethernet
 * driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
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
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/prefetch.h>

#समावेश "t4vf_common.h"
#समावेश "t4vf_defs.h"

#समावेश "../cxgb4/t4_regs.h"
#समावेश "../cxgb4/t4_values.h"
#समावेश "../cxgb4/t4fw_api.h"
#समावेश "../cxgb4/t4_msg.h"

/*
 * Constants ...
 */
क्रमागत अणु
	/*
	 * Egress Queue sizes, producer and consumer indices are all in units
	 * of Egress Context Units bytes.  Note that as far as the hardware is
	 * concerned, the मुक्त list is an Egress Queue (the host produces मुक्त
	 * buffers which the hardware consumes) and मुक्त list entries are
	 * 64-bit PCI DMA addresses.
	 */
	EQ_UNIT = SGE_EQ_IDXSIZE,
	FL_PER_EQ_UNIT = EQ_UNIT / माप(__be64),
	TXD_PER_EQ_UNIT = EQ_UNIT / माप(__be64),

	/*
	 * Max number of TX descriptors we clean up at a समय.  Should be
	 * modest as मुक्तing skbs isn't cheap and it happens जबतक holding
	 * locks.  We just need to मुक्त packets faster than they arrive, we
	 * eventually catch up and keep the amortized cost reasonable.
	 */
	MAX_TX_RECLAIM = 16,

	/*
	 * Max number of Rx buffers we replenish at a समय.  Again keep this
	 * modest, allocating buffers isn't cheap either.
	 */
	MAX_RX_REFILL = 16,

	/*
	 * Period of the Rx queue check समयr.  This समयr is infrequent as it
	 * has something to करो only when the प्रणाली experiences severe memory
	 * लघुage.
	 */
	RX_QCHECK_PERIOD = (HZ / 2),

	/*
	 * Period of the TX queue check समयr and the maximum number of TX
	 * descriptors to be reclaimed by the TX समयr.
	 */
	TX_QCHECK_PERIOD = (HZ / 2),
	MAX_TIMER_TX_RECLAIM = 100,

	/*
	 * Suspend an Ethernet TX queue with fewer available descriptors than
	 * this.  We always want to have room क्रम a maximum sized packet:
	 * अंतरभूत immediate data + MAX_SKB_FRAGS. This is the same as
	 * calc_tx_flits() क्रम a TSO packet with nr_frags == MAX_SKB_FRAGS
	 * (see that function and its helpers क्रम a description of the
	 * calculation).
	 */
	ETHTXQ_MAX_FRAGS = MAX_SKB_FRAGS + 1,
	ETHTXQ_MAX_SGL_LEN = ((3 * (ETHTXQ_MAX_FRAGS-1))/2 +
				   ((ETHTXQ_MAX_FRAGS-1) & 1) +
				   2),
	ETHTXQ_MAX_HDR = (माप(काष्ठा fw_eth_tx_pkt_vm_wr) +
			  माप(काष्ठा cpl_tx_pkt_lso_core) +
			  माप(काष्ठा cpl_tx_pkt_core)) / माप(__be64),
	ETHTXQ_MAX_FLITS = ETHTXQ_MAX_SGL_LEN + ETHTXQ_MAX_HDR,

	ETHTXQ_STOP_THRES = 1 + DIV_ROUND_UP(ETHTXQ_MAX_FLITS, TXD_PER_EQ_UNIT),

	/*
	 * Max TX descriptor space we allow क्रम an Ethernet packet to be
	 * अंतरभूतd पूर्णांकo a WR.  This is limited by the maximum value which
	 * we can specअगरy क्रम immediate data in the firmware Ethernet TX
	 * Work Request.
	 */
	MAX_IMM_TX_PKT_LEN = FW_WR_IMMDLEN_M,

	/*
	 * Max size of a WR sent through a control TX queue.
	 */
	MAX_CTRL_WR_LEN = 256,

	/*
	 * Maximum amount of data which we'll ever need to अंतरभूत पूर्णांकo a
	 * TX ring: max(MAX_IMM_TX_PKT_LEN, MAX_CTRL_WR_LEN).
	 */
	MAX_IMM_TX_LEN = (MAX_IMM_TX_PKT_LEN > MAX_CTRL_WR_LEN
			  ? MAX_IMM_TX_PKT_LEN
			  : MAX_CTRL_WR_LEN),

	/*
	 * For incoming packets less than RX_COPY_THRES, we copy the data पूर्णांकo
	 * an skb rather than referencing the data.  We allocate enough
	 * in-line room in skb's to accommodate pulling in RX_PULL_LEN bytes
	 * of the data (header).
	 */
	RX_COPY_THRES = 256,
	RX_PULL_LEN = 128,

	/*
	 * Main body length क्रम sk_buffs used क्रम RX Ethernet packets with
	 * fragments.  Should be >= RX_PULL_LEN but possibly bigger to give
	 * pskb_may_pull() some room.
	 */
	RX_SKB_LEN = 512,
पूर्ण;

/*
 * Software state per TX descriptor.
 */
काष्ठा tx_sw_desc अणु
	काष्ठा sk_buff *skb;		/* socket buffer of TX data source */
	काष्ठा ulptx_sgl *sgl;		/* scatter/gather list in TX Queue */
पूर्ण;

/*
 * Software state per RX Free List descriptor.  We keep track of the allocated
 * FL page, its size, and its PCI DMA address (अगर the page is mapped).  The FL
 * page size and its PCI DMA mapped state are stored in the low bits of the
 * PCI DMA address as per below.
 */
काष्ठा rx_sw_desc अणु
	काष्ठा page *page;		/* Free List page buffer */
	dma_addr_t dma_addr;		/* PCI DMA address (अगर mapped) */
					/*   and flags (see below) */
पूर्ण;

/*
 * The low bits of rx_sw_desc.dma_addr have special meaning.  Note that the
 * SGE also uses the low 4 bits to determine the size of the buffer.  It uses
 * those bits to index पूर्णांकo the SGE_FL_BUFFER_SIZE[index] रेजिस्टर array.
 * Since we only use SGE_FL_BUFFER_SIZE0 and SGE_FL_BUFFER_SIZE1, these low 4
 * bits can only contain a 0 or a 1 to indicate which size buffer we're giving
 * to the SGE.  Thus, our software state of "is the buffer mapped for DMA" is
 * मुख्यtained in an inverse sense so the hardware never sees that bit high.
 */
क्रमागत अणु
	RX_LARGE_BUF    = 1 << 0,	/* buffer is SGE_FL_BUFFER_SIZE[1] */
	RX_UNMAPPED_BUF = 1 << 1,	/* buffer is not mapped */
पूर्ण;

/**
 *	get_buf_addr - वापस DMA buffer address of software descriptor
 *	@sdesc: poपूर्णांकer to the software buffer descriptor
 *
 *	Return the DMA buffer address of a software descriptor (stripping out
 *	our low-order flag bits).
 */
अटल अंतरभूत dma_addr_t get_buf_addr(स्थिर काष्ठा rx_sw_desc *sdesc)
अणु
	वापस sdesc->dma_addr & ~(dma_addr_t)(RX_LARGE_BUF | RX_UNMAPPED_BUF);
पूर्ण

/**
 *	is_buf_mapped - is buffer mapped क्रम DMA?
 *	@sdesc: poपूर्णांकer to the software buffer descriptor
 *
 *	Determine whether the buffer associated with a software descriptor in
 *	mapped क्रम DMA or not.
 */
अटल अंतरभूत bool is_buf_mapped(स्थिर काष्ठा rx_sw_desc *sdesc)
अणु
	वापस !(sdesc->dma_addr & RX_UNMAPPED_BUF);
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
 *	txq_avail - वापस the number of available slots in a TX queue
 *	@tq: the TX queue
 *
 *	Returns the number of available descriptors in a TX queue.
 */
अटल अंतरभूत अचिन्हित पूर्णांक txq_avail(स्थिर काष्ठा sge_txq *tq)
अणु
	वापस tq->size - 1 - tq->in_use;
पूर्ण

/**
 *	fl_cap - वापस the capacity of a Free List
 *	@fl: the Free List
 *
 *	Returns the capacity of a Free List.  The capacity is less than the
 *	size because an Egress Queue Index Unit worth of descriptors needs to
 *	be left unpopulated, otherwise the Producer and Consumer indices PIDX
 *	and CIDX will match and the hardware will think the FL is empty.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fl_cap(स्थिर काष्ठा sge_fl *fl)
अणु
	वापस fl->size - FL_PER_EQ_UNIT;
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

/**
 *	map_skb -  map an skb क्रम DMA to the device
 *	@dev: the egress net device
 *	@skb: the packet to map
 *	@addr: a poपूर्णांकer to the base of the DMA mapping array
 *
 *	Map an skb क्रम DMA to the device and वापस an array of DMA addresses.
 */
अटल पूर्णांक map_skb(काष्ठा device *dev, स्थिर काष्ठा sk_buff *skb,
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

अटल व्योम unmap_sgl(काष्ठा device *dev, स्थिर काष्ठा sk_buff *skb,
		      स्थिर काष्ठा ulptx_sgl *sgl, स्थिर काष्ठा sge_txq *tq)
अणु
	स्थिर काष्ठा ulptx_sge_pair *p;
	अचिन्हित पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;

	अगर (likely(skb_headlen(skb)))
		dma_unmap_single(dev, be64_to_cpu(sgl->addr0),
				 be32_to_cpu(sgl->len0), DMA_TO_DEVICE);
	अन्यथा अणु
		dma_unmap_page(dev, be64_to_cpu(sgl->addr0),
			       be32_to_cpu(sgl->len0), DMA_TO_DEVICE);
		nfrags--;
	पूर्ण

	/*
	 * the complनिकासy below is because of the possibility of a wrap-around
	 * in the middle of an SGL
	 */
	क्रम (p = sgl->sge; nfrags >= 2; nfrags -= 2) अणु
		अगर (likely((u8 *)(p + 1) <= (u8 *)tq->stat)) अणु
unmap:
			dma_unmap_page(dev, be64_to_cpu(p->addr[0]),
				       be32_to_cpu(p->len[0]), DMA_TO_DEVICE);
			dma_unmap_page(dev, be64_to_cpu(p->addr[1]),
				       be32_to_cpu(p->len[1]), DMA_TO_DEVICE);
			p++;
		पूर्ण अन्यथा अगर ((u8 *)p == (u8 *)tq->stat) अणु
			p = (स्थिर काष्ठा ulptx_sge_pair *)tq->desc;
			जाओ unmap;
		पूर्ण अन्यथा अगर ((u8 *)p + 8 == (u8 *)tq->stat) अणु
			स्थिर __be64 *addr = (स्थिर __be64 *)tq->desc;

			dma_unmap_page(dev, be64_to_cpu(addr[0]),
				       be32_to_cpu(p->len[0]), DMA_TO_DEVICE);
			dma_unmap_page(dev, be64_to_cpu(addr[1]),
				       be32_to_cpu(p->len[1]), DMA_TO_DEVICE);
			p = (स्थिर काष्ठा ulptx_sge_pair *)&addr[2];
		पूर्ण अन्यथा अणु
			स्थिर __be64 *addr = (स्थिर __be64 *)tq->desc;

			dma_unmap_page(dev, be64_to_cpu(p->addr[0]),
				       be32_to_cpu(p->len[0]), DMA_TO_DEVICE);
			dma_unmap_page(dev, be64_to_cpu(addr[0]),
				       be32_to_cpu(p->len[1]), DMA_TO_DEVICE);
			p = (स्थिर काष्ठा ulptx_sge_pair *)&addr[1];
		पूर्ण
	पूर्ण
	अगर (nfrags) अणु
		__be64 addr;

		अगर ((u8 *)p == (u8 *)tq->stat)
			p = (स्थिर काष्ठा ulptx_sge_pair *)tq->desc;
		addr = ((u8 *)p + 16 <= (u8 *)tq->stat
			? p->addr[0]
			: *(स्थिर __be64 *)tq->desc);
		dma_unmap_page(dev, be64_to_cpu(addr), be32_to_cpu(p->len[0]),
			       DMA_TO_DEVICE);
	पूर्ण
पूर्ण

/**
 *	मुक्त_tx_desc - reclaims TX descriptors and their buffers
 *	@adapter: the adapter
 *	@tq: the TX queue to reclaim descriptors from
 *	@n: the number of descriptors to reclaim
 *	@unmap: whether the buffers should be unmapped क्रम DMA
 *
 *	Reclaims TX descriptors from an SGE TX queue and मुक्तs the associated
 *	TX buffers.  Called with the TX queue lock held.
 */
अटल व्योम मुक्त_tx_desc(काष्ठा adapter *adapter, काष्ठा sge_txq *tq,
			 अचिन्हित पूर्णांक n, bool unmap)
अणु
	काष्ठा tx_sw_desc *sdesc;
	अचिन्हित पूर्णांक cidx = tq->cidx;
	काष्ठा device *dev = adapter->pdev_dev;

	स्थिर पूर्णांक need_unmap = need_skb_unmap() && unmap;

	sdesc = &tq->sdesc[cidx];
	जबतक (n--) अणु
		/*
		 * If we kept a reference to the original TX skb, we need to
		 * unmap it from PCI DMA space (अगर required) and मुक्त it.
		 */
		अगर (sdesc->skb) अणु
			अगर (need_unmap)
				unmap_sgl(dev, sdesc->skb, sdesc->sgl, tq);
			dev_consume_skb_any(sdesc->skb);
			sdesc->skb = शून्य;
		पूर्ण

		sdesc++;
		अगर (++cidx == tq->size) अणु
			cidx = 0;
			sdesc = tq->sdesc;
		पूर्ण
	पूर्ण
	tq->cidx = cidx;
पूर्ण

/*
 * Return the number of reclaimable descriptors in a TX queue.
 */
अटल अंतरभूत पूर्णांक reclaimable(स्थिर काष्ठा sge_txq *tq)
अणु
	पूर्णांक hw_cidx = be16_to_cpu(tq->stat->cidx);
	पूर्णांक reclaimable = hw_cidx - tq->cidx;
	अगर (reclaimable < 0)
		reclaimable += tq->size;
	वापस reclaimable;
पूर्ण

/**
 *	reclaim_completed_tx - reclaims completed TX descriptors
 *	@adapter: the adapter
 *	@tq: the TX queue to reclaim completed descriptors from
 *	@unmap: whether the buffers should be unmapped क्रम DMA
 *
 *	Reclaims TX descriptors that the SGE has indicated it has processed,
 *	and मुक्तs the associated buffers अगर possible.  Called with the TX
 *	queue locked.
 */
अटल अंतरभूत व्योम reclaim_completed_tx(काष्ठा adapter *adapter,
					काष्ठा sge_txq *tq,
					bool unmap)
अणु
	पूर्णांक avail = reclaimable(tq);

	अगर (avail) अणु
		/*
		 * Limit the amount of clean up work we करो at a समय to keep
		 * the TX lock hold समय O(1).
		 */
		अगर (avail > MAX_TX_RECLAIM)
			avail = MAX_TX_RECLAIM;

		मुक्त_tx_desc(adapter, tq, avail, unmap);
		tq->in_use -= avail;
	पूर्ण
पूर्ण

/**
 *	get_buf_size - वापस the size of an RX Free List buffer.
 *	@adapter: poपूर्णांकer to the associated adapter
 *	@sdesc: poपूर्णांकer to the software buffer descriptor
 */
अटल अंतरभूत पूर्णांक get_buf_size(स्थिर काष्ठा adapter *adapter,
			       स्थिर काष्ठा rx_sw_desc *sdesc)
अणु
	स्थिर काष्ठा sge *s = &adapter->sge;

	वापस (s->fl_pg_order > 0 && (sdesc->dma_addr & RX_LARGE_BUF)
		? (PAGE_SIZE << s->fl_pg_order) : PAGE_SIZE);
पूर्ण

/**
 *	मुक्त_rx_bufs - मुक्त RX buffers on an SGE Free List
 *	@adapter: the adapter
 *	@fl: the SGE Free List to मुक्त buffers from
 *	@n: how many buffers to मुक्त
 *
 *	Release the next @n buffers on an SGE Free List RX queue.   The
 *	buffers must be made inaccessible to hardware beक्रमe calling this
 *	function.
 */
अटल व्योम मुक्त_rx_bufs(काष्ठा adapter *adapter, काष्ठा sge_fl *fl, पूर्णांक n)
अणु
	जबतक (n--) अणु
		काष्ठा rx_sw_desc *sdesc = &fl->sdesc[fl->cidx];

		अगर (is_buf_mapped(sdesc))
			dma_unmap_page(adapter->pdev_dev, get_buf_addr(sdesc),
				       get_buf_size(adapter, sdesc),
				       PCI_DMA_FROMDEVICE);
		put_page(sdesc->page);
		sdesc->page = शून्य;
		अगर (++fl->cidx == fl->size)
			fl->cidx = 0;
		fl->avail--;
	पूर्ण
पूर्ण

/**
 *	unmap_rx_buf - unmap the current RX buffer on an SGE Free List
 *	@adapter: the adapter
 *	@fl: the SGE Free List
 *
 *	Unmap the current buffer on an SGE Free List RX queue.   The
 *	buffer must be made inaccessible to HW beक्रमe calling this function.
 *
 *	This is similar to @मुक्त_rx_bufs above but करोes not मुक्त the buffer.
 *	Do note that the FL still loses any further access to the buffer.
 *	This is used preकरोminantly to "transfer ownership" of an FL buffer
 *	to another entity (typically an skb's fragment list).
 */
अटल व्योम unmap_rx_buf(काष्ठा adapter *adapter, काष्ठा sge_fl *fl)
अणु
	काष्ठा rx_sw_desc *sdesc = &fl->sdesc[fl->cidx];

	अगर (is_buf_mapped(sdesc))
		dma_unmap_page(adapter->pdev_dev, get_buf_addr(sdesc),
			       get_buf_size(adapter, sdesc),
			       PCI_DMA_FROMDEVICE);
	sdesc->page = शून्य;
	अगर (++fl->cidx == fl->size)
		fl->cidx = 0;
	fl->avail--;
पूर्ण

/**
 *	ring_fl_db - righ करोorbell on मुक्त list
 *	@adapter: the adapter
 *	@fl: the Free List whose करोorbell should be rung ...
 *
 *	Tell the Scatter Gather Engine that there are new मुक्त list entries
 *	available.
 */
अटल अंतरभूत व्योम ring_fl_db(काष्ठा adapter *adapter, काष्ठा sge_fl *fl)
अणु
	u32 val = adapter->params.arch.sge_fl_db;

	/* The SGE keeps track of its Producer and Consumer Indices in terms
	 * of Egress Queue Units so we can only tell it about पूर्णांकegral numbers
	 * of multiples of Free List Entries per Egress Queue Units ...
	 */
	अगर (fl->pend_cred >= FL_PER_EQ_UNIT) अणु
		अगर (is_t4(adapter->params.chip))
			val |= PIDX_V(fl->pend_cred / FL_PER_EQ_UNIT);
		अन्यथा
			val |= PIDX_T5_V(fl->pend_cred / FL_PER_EQ_UNIT);

		/* Make sure all memory ग_लिखोs to the Free List queue are
		 * committed beक्रमe we tell the hardware about them.
		 */
		wmb();

		/* If we करोn't have access to the new User Doorbell (T5+), use
		 * the old करोorbell mechanism; otherwise use the new BAR2
		 * mechanism.
		 */
		अगर (unlikely(fl->bar2_addr == शून्य)) अणु
			t4_ग_लिखो_reg(adapter,
				     T4VF_SGE_BASE_ADDR + SGE_VF_KDOORBELL,
				     QID_V(fl->cntxt_id) | val);
		पूर्ण अन्यथा अणु
			ग_लिखोl(val | QID_V(fl->bar2_qid),
			       fl->bar2_addr + SGE_UDB_KDOORBELL);

			/* This Write memory Barrier will क्रमce the ग_लिखो to
			 * the User Doorbell area to be flushed.
			 */
			wmb();
		पूर्ण
		fl->pend_cred %= FL_PER_EQ_UNIT;
	पूर्ण
पूर्ण

/**
 *	set_rx_sw_desc - initialize software RX buffer descriptor
 *	@sdesc: poपूर्णांकer to the softwore RX buffer descriptor
 *	@page: poपूर्णांकer to the page data काष्ठाure backing the RX buffer
 *	@dma_addr: PCI DMA address (possibly with low-bit flags)
 */
अटल अंतरभूत व्योम set_rx_sw_desc(काष्ठा rx_sw_desc *sdesc, काष्ठा page *page,
				  dma_addr_t dma_addr)
अणु
	sdesc->page = page;
	sdesc->dma_addr = dma_addr;
पूर्ण

/*
 * Support क्रम poisoning RX buffers ...
 */
#घोषणा POISON_BUF_VAL -1

अटल अंतरभूत व्योम poison_buf(काष्ठा page *page, माप_प्रकार sz)
अणु
#अगर POISON_BUF_VAL >= 0
	स_रखो(page_address(page), POISON_BUF_VAL, sz);
#पूर्ण_अगर
पूर्ण

/**
 *	refill_fl - refill an SGE RX buffer ring
 *	@adapter: the adapter
 *	@fl: the Free List ring to refill
 *	@n: the number of new buffers to allocate
 *	@gfp: the gfp flags क्रम the allocations
 *
 *	(Re)populate an SGE मुक्त-buffer queue with up to @n new packet buffers,
 *	allocated with the supplied gfp flags.  The caller must assure that
 *	@n करोes not exceed the queue's capacity -- i.e. (cidx == pidx) _IN
 *	EGRESS QUEUE UNITS_ indicates an empty Free List!  Returns the number
 *	of buffers allocated.  If afterwards the queue is found critically low,
 *	mark it as starving in the biपंचांगap of starving FLs.
 */
अटल अचिन्हित पूर्णांक refill_fl(काष्ठा adapter *adapter, काष्ठा sge_fl *fl,
			      पूर्णांक n, gfp_t gfp)
अणु
	काष्ठा sge *s = &adapter->sge;
	काष्ठा page *page;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक cred = fl->avail;
	__be64 *d = &fl->desc[fl->pidx];
	काष्ठा rx_sw_desc *sdesc = &fl->sdesc[fl->pidx];

	/*
	 * Sanity: ensure that the result of adding n Free List buffers
	 * won't result in wrapping the SGE's Producer Index around to
	 * it's Consumer Index thereby indicating an empty Free List ...
	 */
	BUG_ON(fl->avail + n > fl->size - FL_PER_EQ_UNIT);

	gfp |= __GFP_NOWARN;

	/*
	 * If we support large pages, prefer large buffers and fail over to
	 * small pages अगर we can't allocate large pages to satisfy the refill.
	 * If we करोn't support large pages, drop directly पूर्णांकo the small page
	 * allocation code.
	 */
	अगर (s->fl_pg_order == 0)
		जाओ alloc_small_pages;

	जबतक (n) अणु
		page = __dev_alloc_pages(gfp, s->fl_pg_order);
		अगर (unlikely(!page)) अणु
			/*
			 * We've failed inour attempt to allocate a "large
			 * page".  Fail over to the "small page" allocation
			 * below.
			 */
			fl->large_alloc_failed++;
			अवरोध;
		पूर्ण
		poison_buf(page, PAGE_SIZE << s->fl_pg_order);

		dma_addr = dma_map_page(adapter->pdev_dev, page, 0,
					PAGE_SIZE << s->fl_pg_order,
					PCI_DMA_FROMDEVICE);
		अगर (unlikely(dma_mapping_error(adapter->pdev_dev, dma_addr))) अणु
			/*
			 * We've run out of DMA mapping space.  Free up the
			 * buffer and वापस with what we've managed to put
			 * पूर्णांकo the मुक्त list.  We करोn't want to fail over to
			 * the small page allocation below in this हाल
			 * because DMA mapping resources are typically
			 * critical resources once they become scarse.
			 */
			__मुक्त_pages(page, s->fl_pg_order);
			जाओ out;
		पूर्ण
		dma_addr |= RX_LARGE_BUF;
		*d++ = cpu_to_be64(dma_addr);

		set_rx_sw_desc(sdesc, page, dma_addr);
		sdesc++;

		fl->avail++;
		अगर (++fl->pidx == fl->size) अणु
			fl->pidx = 0;
			sdesc = fl->sdesc;
			d = fl->desc;
		पूर्ण
		n--;
	पूर्ण

alloc_small_pages:
	जबतक (n--) अणु
		page = __dev_alloc_page(gfp);
		अगर (unlikely(!page)) अणु
			fl->alloc_failed++;
			अवरोध;
		पूर्ण
		poison_buf(page, PAGE_SIZE);

		dma_addr = dma_map_page(adapter->pdev_dev, page, 0, PAGE_SIZE,
				       PCI_DMA_FROMDEVICE);
		अगर (unlikely(dma_mapping_error(adapter->pdev_dev, dma_addr))) अणु
			put_page(page);
			अवरोध;
		पूर्ण
		*d++ = cpu_to_be64(dma_addr);

		set_rx_sw_desc(sdesc, page, dma_addr);
		sdesc++;

		fl->avail++;
		अगर (++fl->pidx == fl->size) अणु
			fl->pidx = 0;
			sdesc = fl->sdesc;
			d = fl->desc;
		पूर्ण
	पूर्ण

out:
	/*
	 * Update our accounting state to incorporate the new Free List
	 * buffers, tell the hardware about them and वापस the number of
	 * buffers which we were able to allocate.
	 */
	cred = fl->avail - cred;
	fl->pend_cred += cred;
	ring_fl_db(adapter, fl);

	अगर (unlikely(fl_starving(adapter, fl))) अणु
		smp_wmb();
		set_bit(fl->cntxt_id, adapter->sge.starving_fl);
	पूर्ण

	वापस cred;
पूर्ण

/*
 * Refill a Free List to its capacity or the Maximum Refill Increment,
 * whichever is smaller ...
 */
अटल अंतरभूत व्योम __refill_fl(काष्ठा adapter *adapter, काष्ठा sge_fl *fl)
अणु
	refill_fl(adapter, fl,
		  min((अचिन्हित पूर्णांक)MAX_RX_REFILL, fl_cap(fl) - fl->avail),
		  GFP_ATOMIC);
पूर्ण

/**
 *	alloc_ring - allocate resources क्रम an SGE descriptor ring
 *	@dev: the PCI device's core device
 *	@nelem: the number of descriptors
 *	@hwsize: the size of each hardware descriptor
 *	@swsize: the size of each software descriptor
 *	@busaddrp: the physical PCI bus address of the allocated ring
 *	@swringp: वापस address poपूर्णांकer क्रम software ring
 *	@stat_size: extra space in hardware ring क्रम status inक्रमmation
 *
 *	Allocates resources क्रम an SGE descriptor ring, such as TX queues,
 *	मुक्त buffer lists, response queues, etc.  Each SGE ring requires
 *	space क्रम its hardware descriptors plus, optionally, space क्रम software
 *	state associated with each hardware entry (the metadata).  The function
 *	वापसs three values: the भव address क्रम the hardware ring (the
 *	वापस value of the function), the PCI bus address of the hardware
 *	ring (in *busaddrp), and the address of the software ring (in swringp).
 *	Both the hardware and software rings are वापसed zeroed out.
 */
अटल व्योम *alloc_ring(काष्ठा device *dev, माप_प्रकार nelem, माप_प्रकार hwsize,
			माप_प्रकार swsize, dma_addr_t *busaddrp, व्योम *swringp,
			माप_प्रकार stat_size)
अणु
	/*
	 * Allocate the hardware ring and PCI DMA bus address space क्रम said.
	 */
	माप_प्रकार hwlen = nelem * hwsize + stat_size;
	व्योम *hwring = dma_alloc_coherent(dev, hwlen, busaddrp, GFP_KERNEL);

	अगर (!hwring)
		वापस शून्य;

	/*
	 * If the caller wants a software ring, allocate it and वापस a
	 * poपूर्णांकer to it in *swringp.
	 */
	BUG_ON((swsize != 0) != (swringp != शून्य));
	अगर (swsize) अणु
		व्योम *swring = kसुस्मृति(nelem, swsize, GFP_KERNEL);

		अगर (!swring) अणु
			dma_मुक्त_coherent(dev, hwlen, hwring, *busaddrp);
			वापस शून्य;
		पूर्ण
		*(व्योम **)swringp = swring;
	पूर्ण

	वापस hwring;
पूर्ण

/**
 *	sgl_len - calculates the size of an SGL of the given capacity
 *	@n: the number of SGL entries
 *
 *	Calculates the number of flits (8-byte units) needed क्रम a Direct
 *	Scatter/Gather List that can hold the given number of entries.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sgl_len(अचिन्हित पूर्णांक n)
अणु
	/*
	 * A Direct Scatter Gather List uses 32-bit lengths and 64-bit PCI DMA
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
 *	flits_to_desc - वापसs the num of TX descriptors क्रम the given flits
 *	@flits: the number of flits
 *
 *	Returns the number of TX descriptors needed क्रम the supplied number
 *	of flits.
 */
अटल अंतरभूत अचिन्हित पूर्णांक flits_to_desc(अचिन्हित पूर्णांक flits)
अणु
	BUG_ON(flits > SGE_MAX_WR_LEN / माप(__be64));
	वापस DIV_ROUND_UP(flits, TXD_PER_EQ_UNIT);
पूर्ण

/**
 *	is_eth_imm - can an Ethernet packet be sent as immediate data?
 *	@skb: the packet
 *
 *	Returns whether an Ethernet packet is small enough to fit completely as
 *	immediate data.
 */
अटल अंतरभूत पूर्णांक is_eth_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	/*
	 * The VF Driver uses the FW_ETH_TX_PKT_VM_WR firmware Work Request
	 * which करोes not accommodate immediate data.  We could dike out all
	 * of the support code क्रम immediate data but that would tie our hands
	 * too much अगर we ever want to enhace the firmware.  It would also
	 * create more dअगरferences between the PF and VF Drivers.
	 */
	वापस false;
पूर्ण

/**
 *	calc_tx_flits - calculate the number of flits क्रम a packet TX WR
 *	@skb: the packet
 *
 *	Returns the number of flits needed क्रम a TX Work Request क्रम the
 *	given Ethernet packet, including the needed WR and CPL headers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_flits(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits;

	/*
	 * If the skb is small enough, we can pump it out as a work request
	 * with only immediate data.  In that हाल we just have to have the
	 * TX Packet header plus the skb data in the Work Request.
	 */
	अगर (is_eth_imm(skb))
		वापस DIV_ROUND_UP(skb->len + माप(काष्ठा cpl_tx_pkt),
				    माप(__be64));

	/*
	 * Otherwise, we're going to have to स्थिरruct a Scatter gather list
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
 *	ग_लिखो_sgl - populate a Scatter/Gather List क्रम a packet
 *	@skb: the packet
 *	@tq: the TX queue we are writing पूर्णांकo
 *	@sgl: starting location क्रम writing the SGL
 *	@end: poपूर्णांकs right after the end of the SGL
 *	@start: start offset पूर्णांकo skb मुख्य-body data to include in the SGL
 *	@addr: the list of DMA bus addresses क्रम the SGL elements
 *
 *	Generates a Scatter/Gather List क्रम the buffers that make up a packet.
 *	The caller must provide adequate space क्रम the SGL that will be written.
 *	The SGL includes all of the packet's page fragments and the data in its
 *	मुख्य body except क्रम the first @start bytes.  @pos must be 16-byte
 *	aligned and within a TX descriptor with available space.  @end poपूर्णांकs
 *	ग_लिखो after the end of the SGL but करोes not account क्रम any potential
 *	wrap around, i.e., @end > @tq->stat.
 */
अटल व्योम ग_लिखो_sgl(स्थिर काष्ठा sk_buff *skb, काष्ठा sge_txq *tq,
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
	to = (u8 *)end > (u8 *)tq->stat ? buf : sgl->sge;

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
	अगर (unlikely((u8 *)end > (u8 *)tq->stat)) अणु
		अचिन्हित पूर्णांक part0 = (u8 *)tq->stat - (u8 *)sgl->sge, part1;

		अगर (likely(part0))
			स_नकल(sgl->sge, buf, part0);
		part1 = (u8 *)end - (u8 *)tq->stat;
		स_नकल(tq->desc, (u8 *)buf + part0, part1);
		end = (व्योम *)tq->desc + part1;
	पूर्ण
	अगर ((uपूर्णांकptr_t)end & 8)           /* 0-pad to multiple of 16 */
		*end = 0;
पूर्ण

/**
 *	check_ring_tx_db - check and potentially ring a TX queue's करोorbell
 *	@adapter: the adapter
 *	@tq: the TX queue
 *	@n: number of new descriptors to give to HW
 *
 *	Ring the करोorbel क्रम a TX queue.
 */
अटल अंतरभूत व्योम ring_tx_db(काष्ठा adapter *adapter, काष्ठा sge_txq *tq,
			      पूर्णांक n)
अणु
	/* Make sure that all ग_लिखोs to the TX Descriptors are committed
	 * beक्रमe we tell the hardware about them.
	 */
	wmb();

	/* If we करोn't have access to the new User Doorbell (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(tq->bar2_addr == शून्य)) अणु
		u32 val = PIDX_V(n);

		t4_ग_लिखो_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_KDOORBELL,
			     QID_V(tq->cntxt_id) | val);
	पूर्ण अन्यथा अणु
		u32 val = PIDX_T5_V(n);

		/* T4 and later chips share the same PIDX field offset within
		 * the करोorbell, but T5 and later shrank the field in order to
		 * gain a bit क्रम Doorbell Priority.  The field was असलurdly
		 * large in the first place (14 bits) so we just use the T5
		 * and later limits and warn अगर a Queue ID is too large.
		 */
		WARN_ON(val & DBPRIO_F);

		/* If we're only writing a single Egress Unit and the BAR2
		 * Queue ID is 0, we can use the Write Combining Doorbell
		 * Gather Buffer; otherwise we use the simple करोorbell.
		 */
		अगर (n == 1 && tq->bar2_qid == 0) अणु
			अचिन्हित पूर्णांक index = (tq->pidx
					      ? (tq->pidx - 1)
					      : (tq->size - 1));
			__be64 *src = (__be64 *)&tq->desc[index];
			__be64 __iomem *dst = (__be64 __iomem *)(tq->bar2_addr +
							 SGE_UDB_WCDOORBELL);
			अचिन्हित पूर्णांक count = EQ_UNIT / माप(__be64);

			/* Copy the TX Descriptor in a tight loop in order to
			 * try to get it to the adapter in a single Write
			 * Combined transfer on the PCI-E Bus.  If the Write
			 * Combine fails (say because of an पूर्णांकerrupt, etc.)
			 * the hardware will simply take the last ग_लिखो as a
			 * simple करोorbell ग_लिखो with a PIDX Increment of 1
			 * and will fetch the TX Descriptor from memory via
			 * DMA.
			 */
			जबतक (count) अणु
				/* the (__क्रमce u64) is because the compiler
				 * करोesn't understand the endian swizzling
				 * going on
				 */
				ग_लिखोq((__क्रमce u64)*src, dst);
				src++;
				dst++;
				count--;
			पूर्ण
		पूर्ण अन्यथा
			ग_लिखोl(val | QID_V(tq->bar2_qid),
			       tq->bar2_addr + SGE_UDB_KDOORBELL);

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

/**
 *	अंतरभूत_tx_skb - अंतरभूत a packet's data पूर्णांकo TX descriptors
 *	@skb: the packet
 *	@tq: the TX queue where the packet will be अंतरभूतd
 *	@pos: starting position in the TX queue to अंतरभूत the packet
 *
 *	Inline a packet's contents directly पूर्णांकo TX descriptors, starting at
 *	the given position within the TX DMA ring.
 *	Most of the complनिकासy of this operation is dealing with wrap arounds
 *	in the middle of the packet we want to अंतरभूत.
 */
अटल व्योम अंतरभूत_tx_skb(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा sge_txq *tq,
			  व्योम *pos)
अणु
	u64 *p;
	पूर्णांक left = (व्योम *)tq->stat - pos;

	अगर (likely(skb->len <= left)) अणु
		अगर (likely(!skb->data_len))
			skb_copy_from_linear_data(skb, pos, skb->len);
		अन्यथा
			skb_copy_bits(skb, 0, pos, skb->len);
		pos += skb->len;
	पूर्ण अन्यथा अणु
		skb_copy_bits(skb, 0, pos, left);
		skb_copy_bits(skb, left, tq->desc, skb->len - left);
		pos = (व्योम *)tq->desc + (skb->len - left);
	पूर्ण

	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	अगर ((uपूर्णांकptr_t)p & 8)
		*p = 0;
पूर्ण

/*
 * Figure out what HW csum a packet wants and वापस the appropriate control
 * bits.
 */
अटल u64 hwcsum(क्रमागत chip_type chip, स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक csum_type;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	अगर (iph->version == 4) अणु
		अगर (iph->protocol == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP;
		अन्यथा अगर (iph->protocol == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP;
		अन्यथा अणु
nocsum:
			/*
			 * unknown protocol, disable HW csum
			 * and hope a bad packet is detected
			 */
			वापस TXPKT_L4CSUM_DIS_F;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * this करोesn't work with extension headers
		 */
		स्थिर काष्ठा ipv6hdr *ip6h = (स्थिर काष्ठा ipv6hdr *)iph;

		अगर (ip6h->nexthdr == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP6;
		अन्यथा अगर (ip6h->nexthdr == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP6;
		अन्यथा
			जाओ nocsum;
	पूर्ण

	अगर (likely(csum_type >= TX_CSUM_TCPIP)) अणु
		u64 hdr_len = TXPKT_IPHDR_LEN_V(skb_network_header_len(skb));
		पूर्णांक eth_hdr_len = skb_network_offset(skb) - ETH_HLEN;

		अगर (chip <= CHELSIO_T5)
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

/*
 * Stop an Ethernet TX queue and record that state change.
 */
अटल व्योम txq_stop(काष्ठा sge_eth_txq *txq)
अणु
	netअगर_tx_stop_queue(txq->txq);
	txq->q.stops++;
पूर्ण

/*
 * Advance our software state क्रम a TX queue by adding n in use descriptors.
 */
अटल अंतरभूत व्योम txq_advance(काष्ठा sge_txq *tq, अचिन्हित पूर्णांक n)
अणु
	tq->in_use += n;
	tq->pidx += n;
	अगर (tq->pidx >= tq->size)
		tq->pidx -= tq->size;
पूर्ण

/**
 *	t4vf_eth_xmit - add a packet to an Ethernet TX queue
 *	@skb: the packet
 *	@dev: the egress net device
 *
 *	Add a packet to an SGE Ethernet TX queue.  Runs with softirqs disabled.
 */
netdev_tx_t t4vf_eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	u32 wr_mid;
	u64 cntrl, *end;
	पूर्णांक qidx, credits, max_pkt_len;
	अचिन्हित पूर्णांक flits, ndesc;
	काष्ठा adapter *adapter;
	काष्ठा sge_eth_txq *txq;
	स्थिर काष्ठा port_info *pi;
	काष्ठा fw_eth_tx_pkt_vm_wr *wr;
	काष्ठा cpl_tx_pkt_core *cpl;
	स्थिर काष्ठा skb_shared_info *ssi;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
	स्थिर माप_प्रकार fw_hdr_copy_len = (माप(wr->ethmacdst) +
					माप(wr->ethmacsrc) +
					माप(wr->ethtype) +
					माप(wr->vlantci));

	/*
	 * The chip minimum packet length is 10 octets but the firmware
	 * command that we are using requires that we copy the Ethernet header
	 * (including the VLAN tag) पूर्णांकo the header so we reject anything
	 * smaller than that ...
	 */
	अगर (unlikely(skb->len < fw_hdr_copy_len))
		जाओ out_मुक्त;

	/* Discard the packet अगर the length is greater than mtu */
	max_pkt_len = ETH_HLEN + dev->mtu;
	अगर (skb_vlan_tagged(skb))
		max_pkt_len += VLAN_HLEN;
	अगर (!skb_shinfo(skb)->gso_size && (unlikely(skb->len > max_pkt_len)))
		जाओ out_मुक्त;

	/*
	 * Figure out which TX Queue we're going to use.
	 */
	pi = netdev_priv(dev);
	adapter = pi->adapter;
	qidx = skb_get_queue_mapping(skb);
	BUG_ON(qidx >= pi->nqsets);
	txq = &adapter->sge.ethtxq[pi->first_qset + qidx];

	अगर (pi->vlan_id && !skb_vlan_tag_present(skb))
		__vlan_hwaccel_put_tag(skb, cpu_to_be16(ETH_P_8021Q),
				       pi->vlan_id);

	/*
	 * Take this opportunity to reclaim any TX Descriptors whose DMA
	 * transfers have completed.
	 */
	reclaim_completed_tx(adapter, &txq->q, true);

	/*
	 * Calculate the number of flits and TX Descriptors we're going to
	 * need aदीर्घ with how many TX Descriptors will be left over after
	 * we inject our Work Request.
	 */
	flits = calc_tx_flits(skb);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&txq->q) - ndesc;

	अगर (unlikely(credits < 0)) अणु
		/*
		 * Not enough room क्रम this packet's Work Request.  Stop the
		 * TX Queue and वापस a "busy" condition.  The queue will get
		 * started later on when the firmware inक्रमms us that space
		 * has खोलोed up.
		 */
		txq_stop(txq);
		dev_err(adapter->pdev_dev,
			"%s: TX ring %u full while queue awake!\n",
			dev->name, qidx);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (!is_eth_imm(skb) &&
	    unlikely(map_skb(adapter->pdev_dev, skb, addr) < 0)) अणु
		/*
		 * We need to map the skb पूर्णांकo PCI DMA space (because it can't
		 * be in-lined directly पूर्णांकo the Work Request) and the mapping
		 * operation failed.  Record the error and drop the packet.
		 */
		txq->mapping_err++;
		जाओ out_मुक्त;
	पूर्ण

	wr_mid = FW_WR_LEN16_V(DIV_ROUND_UP(flits, 2));
	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		/*
		 * After we're करोne injecting the Work Request क्रम this
		 * packet, we'll be below our "stop threshold" so stop the TX
		 * Queue now and schedule a request क्रम an SGE Egress Queue
		 * Update message.  The queue will get started later on when
		 * the firmware processes this Work Request and sends us an
		 * Egress Queue Status Update message indicating that space
		 * has खोलोed up.
		 */
		txq_stop(txq);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	/*
	 * Start filling in our Work Request.  Note that we करो _not_ handle
	 * the WR Header wrapping around the TX Descriptor Ring.  If our
	 * maximum header size ever exceeds one TX Descriptor, we'll need to
	 * करो something अन्यथा here.
	 */
	BUG_ON(DIV_ROUND_UP(ETHTXQ_MAX_HDR, TXD_PER_EQ_UNIT) > 1);
	wr = (व्योम *)&txq->q.desc[txq->q.pidx];
	wr->equiq_to_len16 = cpu_to_be32(wr_mid);
	wr->r3[0] = cpu_to_be32(0);
	wr->r3[1] = cpu_to_be32(0);
	skb_copy_from_linear_data(skb, (व्योम *)wr->ethmacdst, fw_hdr_copy_len);
	end = (u64 *)wr + flits;

	/*
	 * If this is a Large Send Offload packet we'll put in an LSO CPL
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
		/*
		 * Fill in the LSO CPL message.
		 */
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

		/*
		 * Set up TX Packet CPL poपूर्णांकer, control word and perक्रमm
		 * accounting.
		 */
		cpl = (व्योम *)(lso + 1);

		अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
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

		len = is_eth_imm(skb) ? skb->len + माप(*cpl) : माप(*cpl);
		wr->op_immdlen =
			cpu_to_be32(FW_WR_OP_V(FW_ETH_TX_PKT_VM_WR) |
				    FW_WR_IMMDLEN_V(len));

		/*
		 * Set up TX Packet CPL poपूर्णांकer, control word and perक्रमm
		 * accounting.
		 */
		cpl = (व्योम *)(wr + 1);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			cntrl = hwcsum(adapter->params.chip, skb) |
				TXPKT_IPCSUM_DIS_F;
			txq->tx_cso++;
		पूर्ण अन्यथा
			cntrl = TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F;
	पूर्ण

	/*
	 * If there's a VLAN tag present, add that to the list of things to
	 * करो in this Work Request.
	 */
	अगर (skb_vlan_tag_present(skb)) अणु
		txq->vlan_ins++;
		cntrl |= TXPKT_VLAN_VLD_F | TXPKT_VLAN_V(skb_vlan_tag_get(skb));
	पूर्ण

	/*
	 * Fill in the TX Packet CPL message header.
	 */
	cpl->ctrl0 = cpu_to_be32(TXPKT_OPCODE_V(CPL_TX_PKT_XT) |
				 TXPKT_INTF_V(pi->port_id) |
				 TXPKT_PF_V(0));
	cpl->pack = cpu_to_be16(0);
	cpl->len = cpu_to_be16(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

#अगर_घोषित T4_TRACE
	T4_TRACE5(adapter->tb[txq->q.cntxt_id & 7],
		  "eth_xmit: ndesc %u, credits %u, pidx %u, len %u, frags %u",
		  ndesc, credits, txq->q.pidx, skb->len, ssi->nr_frags);
#पूर्ण_अगर

	/*
	 * Fill in the body of the TX Packet CPL message with either in-lined
	 * data or a Scatter/Gather List.
	 */
	अगर (is_eth_imm(skb)) अणु
		/*
		 * In-line the packet's data and free the skb since we don't
		 * need it any दीर्घer.
		 */
		अंतरभूत_tx_skb(skb, &txq->q, cpl + 1);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अणु
		/*
		 * Write the skb's Scatter/Gather list पूर्णांकo the TX Packet CPL
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
		पूर्णांक last_desc;

		/*
		 * If the Work Request header was an exact multiple of our TX
		 * Descriptor length, then it's possible that the starting SGL
		 * poपूर्णांकer lines up exactly with the end of our TX Descriptor
		 * ring.  If that's the हाल, wrap around to the beginning
		 * here ...
		 */
		अगर (unlikely((व्योम *)sgl == (व्योम *)tq->stat)) अणु
			sgl = (व्योम *)tq->desc;
			end = ((व्योम *)tq->desc + ((व्योम *)end - (व्योम *)tq->stat));
		पूर्ण

		ग_लिखो_sgl(skb, tq, sgl, end, 0, addr);
		skb_orphan(skb);

		last_desc = tq->pidx + ndesc - 1;
		अगर (last_desc >= tq->size)
			last_desc -= tq->size;
		tq->sdesc[last_desc].skb = skb;
		tq->sdesc[last_desc].sgl = sgl;
	पूर्ण

	/*
	 * Advance our पूर्णांकernal TX Queue state, tell the hardware about
	 * the new TX descriptors and वापस success.
	 */
	txq_advance(&txq->q, ndesc);
	netअगर_trans_update(dev);
	ring_tx_db(adapter, &txq->q, ndesc);
	वापस NETDEV_TX_OK;

out_मुक्त:
	/*
	 * An error of some sort happened.  Free the TX skb and tell the
	 * OS that we've "dealt" with the packet ...
	 */
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 *	copy_frags - copy fragments from gather list पूर्णांकo skb_shared_info
 *	@skb: destination skb
 *	@gl: source पूर्णांकernal packet gather list
 *	@offset: packet start offset in first page
 *
 *	Copy an पूर्णांकernal packet gather list पूर्णांकo a Linux skb_shared_info
 *	काष्ठाure.
 */
अटल अंतरभूत व्योम copy_frags(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा pkt_gl *gl,
			      अचिन्हित पूर्णांक offset)
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
 *	t4vf_pktgl_to_skb - build an sk_buff from a packet gather list
 *	@gl: the gather list
 *	@skb_len: size of sk_buff मुख्य body अगर it carries fragments
 *	@pull_len: amount of data to move to the sk_buff's मुख्य body
 *
 *	Builds an sk_buff from the given packet gather list.  Returns the
 *	sk_buff or %शून्य अगर sk_buff allocation failed.
 */
अटल काष्ठा sk_buff *t4vf_pktgl_to_skb(स्थिर काष्ठा pkt_gl *gl,
					 अचिन्हित पूर्णांक skb_len,
					 अचिन्हित पूर्णांक pull_len)
अणु
	काष्ठा sk_buff *skb;

	/*
	 * If the ingress packet is small enough, allocate an skb large enough
	 * क्रम all of the data and copy it अंतरभूत.  Otherwise, allocate an skb
	 * with enough room to pull in the header and reference the rest of
	 * the data via the skb fragment list.
	 *
	 * Below we rely on RX_COPY_THRES being less than the smallest Rx
	 * buff!  size, which is expected since buffers are at least
	 * PAGE_SIZEd.  In this हाल packets up to RX_COPY_THRES have only one
	 * fragment.
	 */
	अगर (gl->tot_len <= RX_COPY_THRES) अणु
		/* small packets have only one fragment */
		skb = alloc_skb(gl->tot_len, GFP_ATOMIC);
		अगर (unlikely(!skb))
			जाओ out;
		__skb_put(skb, gl->tot_len);
		skb_copy_to_linear_data(skb, gl->va, gl->tot_len);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(skb_len, GFP_ATOMIC);
		अगर (unlikely(!skb))
			जाओ out;
		__skb_put(skb, pull_len);
		skb_copy_to_linear_data(skb, gl->va, pull_len);

		copy_frags(skb, gl, pull_len);
		skb->len = gl->tot_len;
		skb->data_len = skb->len - pull_len;
		skb->truesize += skb->data_len;
	पूर्ण

out:
	वापस skb;
पूर्ण

/**
 *	t4vf_pktgl_मुक्त - मुक्त a packet gather list
 *	@gl: the gather list
 *
 *	Releases the pages of a packet gather list.  We करो not own the last
 *	page on the list and करो not मुक्त it.
 */
अटल व्योम t4vf_pktgl_मुक्त(स्थिर काष्ठा pkt_gl *gl)
अणु
	पूर्णांक frag;

	frag = gl->nfrags - 1;
	जबतक (frag--)
		put_page(gl->frags[frag].page);
पूर्ण

/**
 *	करो_gro - perक्रमm Generic Receive Offload ingress packet processing
 *	@rxq: ingress RX Ethernet Queue
 *	@gl: gather list क्रम ingress packet
 *	@pkt: CPL header क्रम last packet fragment
 *
 *	Perक्रमm Generic Receive Offload (GRO) ingress packet processing.
 *	We use the standard Linux GRO पूर्णांकerfaces क्रम this.
 */
अटल व्योम करो_gro(काष्ठा sge_eth_rxq *rxq, स्थिर काष्ठा pkt_gl *gl,
		   स्थिर काष्ठा cpl_rx_pkt *pkt)
अणु
	काष्ठा adapter *adapter = rxq->rspq.adapter;
	काष्ठा sge *s = &adapter->sge;
	काष्ठा port_info *pi;
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	skb = napi_get_frags(&rxq->rspq.napi);
	अगर (unlikely(!skb)) अणु
		t4vf_pktgl_मुक्त(gl);
		rxq->stats.rx_drops++;
		वापस;
	पूर्ण

	copy_frags(skb, gl, s->pktshअगरt);
	skb->len = gl->tot_len - s->pktshअगरt;
	skb->data_len = skb->len;
	skb->truesize += skb->data_len;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rxq->rspq.idx);
	pi = netdev_priv(skb->dev);

	अगर (pkt->vlan_ex && !pi->vlan_id) अणु
		__vlan_hwaccel_put_tag(skb, cpu_to_be16(ETH_P_8021Q),
					be16_to_cpu(pkt->vlan));
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

/**
 *	t4vf_ethrx_handler - process an ingress ethernet packet
 *	@rspq: the response queue that received the packet
 *	@rsp: the response queue descriptor holding the RX_PKT message
 *	@gl: the gather list of packet fragments
 *
 *	Process an ingress ethernet packet and deliver it to the stack.
 */
पूर्णांक t4vf_ethrx_handler(काष्ठा sge_rspq *rspq, स्थिर __be64 *rsp,
		       स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा cpl_rx_pkt *pkt = (व्योम *)rsp;
	bool csum_ok = pkt->csum_calc && !pkt->err_vec &&
		       (rspq->netdev->features & NETIF_F_RXCSUM);
	काष्ठा sge_eth_rxq *rxq = container_of(rspq, काष्ठा sge_eth_rxq, rspq);
	काष्ठा adapter *adapter = rspq->adapter;
	काष्ठा sge *s = &adapter->sge;
	काष्ठा port_info *pi;

	/*
	 * If this is a good TCP packet and we have Generic Receive Offload
	 * enabled, handle the packet in the GRO path.
	 */
	अगर ((pkt->l2info & cpu_to_be32(RXF_TCP_F)) &&
	    (rspq->netdev->features & NETIF_F_GRO) && csum_ok &&
	    !pkt->ip_frag) अणु
		करो_gro(rxq, gl, pkt);
		वापस 0;
	पूर्ण

	/*
	 * Convert the Packet Gather List पूर्णांकo an skb.
	 */
	skb = t4vf_pktgl_to_skb(gl, RX_SKB_LEN, RX_PULL_LEN);
	अगर (unlikely(!skb)) अणु
		t4vf_pktgl_मुक्त(gl);
		rxq->stats.rx_drops++;
		वापस 0;
	पूर्ण
	__skb_pull(skb, s->pktshअगरt);
	skb->protocol = eth_type_trans(skb, rspq->netdev);
	skb_record_rx_queue(skb, rspq->idx);
	pi = netdev_priv(skb->dev);
	rxq->stats.pkts++;

	अगर (csum_ok && !pkt->err_vec &&
	    (be32_to_cpu(pkt->l2info) & (RXF_UDP_F | RXF_TCP_F))) अणु
		अगर (!pkt->ip_frag) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			rxq->stats.rx_cso++;
		पूर्ण अन्यथा अगर (pkt->l2info & htonl(RXF_IP_F)) अणु
			__sum16 c = (__क्रमce __sum16)pkt->csum;
			skb->csum = csum_unfold(c);
			skb->ip_summed = CHECKSUM_COMPLETE;
			rxq->stats.rx_cso++;
		पूर्ण
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);

	अगर (pkt->vlan_ex && !pi->vlan_id) अणु
		rxq->stats.vlan_ex++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(pkt->vlan));
	पूर्ण

	netअगर_receive_skb(skb);

	वापस 0;
पूर्ण

/**
 *	is_new_response - check अगर a response is newly written
 *	@rc: the response control descriptor
 *	@rspq: the response queue
 *
 *	Returns true अगर a response descriptor contains a yet unprocessed
 *	response.
 */
अटल अंतरभूत bool is_new_response(स्थिर काष्ठा rsp_ctrl *rc,
				   स्थिर काष्ठा sge_rspq *rspq)
अणु
	वापस ((rc->type_gen >> RSPD_GEN_S) & 0x1) == rspq->gen;
पूर्ण

/**
 *	restore_rx_bufs - put back a packet's RX buffers
 *	@gl: the packet gather list
 *	@fl: the SGE Free List
 *	@frags: how many fragments in @si
 *
 *	Called when we find out that the current packet, @si, can't be
 *	processed right away क्रम some reason.  This is a very rare event and
 *	there's no efक्रमt to make this suspension/resumption process
 *	particularly efficient.
 *
 *	We implement the suspension by putting all of the RX buffers associated
 *	with the current packet back on the original Free List.  The buffers
 *	have alपढ़ोy been unmapped and are left unmapped, we mark them as
 *	unmapped in order to prevent further unmapping attempts.  (Effectively
 *	this function unकरोes the series of @unmap_rx_buf calls which were करोne
 *	to create the current packet's gather list.)  This leaves us पढ़ोy to
 *	restart processing of the packet the next समय we start processing the
 *	RX Queue ...
 */
अटल व्योम restore_rx_bufs(स्थिर काष्ठा pkt_gl *gl, काष्ठा sge_fl *fl,
			    पूर्णांक frags)
अणु
	काष्ठा rx_sw_desc *sdesc;

	जबतक (frags--) अणु
		अगर (fl->cidx == 0)
			fl->cidx = fl->size - 1;
		अन्यथा
			fl->cidx--;
		sdesc = &fl->sdesc[fl->cidx];
		sdesc->page = gl->frags[frags].page;
		sdesc->dma_addr |= RX_UNMAPPED_BUF;
		fl->avail++;
	पूर्ण
पूर्ण

/**
 *	rspq_next - advance to the next entry in a response queue
 *	@rspq: the queue
 *
 *	Updates the state of a response queue to advance it to the next entry.
 */
अटल अंतरभूत व्योम rspq_next(काष्ठा sge_rspq *rspq)
अणु
	rspq->cur_desc = (व्योम *)rspq->cur_desc + rspq->iqe_len;
	अगर (unlikely(++rspq->cidx == rspq->size)) अणु
		rspq->cidx = 0;
		rspq->gen ^= 1;
		rspq->cur_desc = rspq->desc;
	पूर्ण
पूर्ण

/**
 *	process_responses - process responses from an SGE response queue
 *	@rspq: the ingress response queue to process
 *	@budget: how many responses can be processed in this round
 *
 *	Process responses from a Scatter Gather Engine response queue up to
 *	the supplied budget.  Responses include received packets as well as
 *	control messages from firmware or hardware.
 *
 *	Additionally choose the पूर्णांकerrupt holकरोff समय क्रम the next पूर्णांकerrupt
 *	on this queue.  If the प्रणाली is under memory लघुage use a fairly
 *	दीर्घ delay to help recovery.
 */
अटल पूर्णांक process_responses(काष्ठा sge_rspq *rspq, पूर्णांक budget)
अणु
	काष्ठा sge_eth_rxq *rxq = container_of(rspq, काष्ठा sge_eth_rxq, rspq);
	काष्ठा adapter *adapter = rspq->adapter;
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक budget_left = budget;

	जबतक (likely(budget_left)) अणु
		पूर्णांक ret, rsp_type;
		स्थिर काष्ठा rsp_ctrl *rc;

		rc = (व्योम *)rspq->cur_desc + (rspq->iqe_len - माप(*rc));
		अगर (!is_new_response(rc, rspq))
			अवरोध;

		/*
		 * Figure out what kind of response we've received from the
		 * SGE.
		 */
		dma_rmb();
		rsp_type = RSPD_TYPE_G(rc->type_gen);
		अगर (likely(rsp_type == RSPD_TYPE_FLBUF_X)) अणु
			काष्ठा page_frag *fp;
			काष्ठा pkt_gl gl;
			स्थिर काष्ठा rx_sw_desc *sdesc;
			u32 bufsz, frag;
			u32 len = be32_to_cpu(rc->pldbuflen_qid);

			/*
			 * If we get a "new buffer" message from the SGE we
			 * need to move on to the next Free List buffer.
			 */
			अगर (len & RSPD_NEWBUF_F) अणु
				/*
				 * We get one "new buffer" message when we
				 * first start up a queue so we need to ignore
				 * it when our offset पूर्णांकo the buffer is 0.
				 */
				अगर (likely(rspq->offset > 0)) अणु
					मुक्त_rx_bufs(rspq->adapter, &rxq->fl,
						     1);
					rspq->offset = 0;
				पूर्ण
				len = RSPD_LEN_G(len);
			पूर्ण
			gl.tot_len = len;

			/*
			 * Gather packet fragments.
			 */
			क्रम (frag = 0, fp = gl.frags; /**/; frag++, fp++) अणु
				BUG_ON(frag >= MAX_SKB_FRAGS);
				BUG_ON(rxq->fl.avail == 0);
				sdesc = &rxq->fl.sdesc[rxq->fl.cidx];
				bufsz = get_buf_size(adapter, sdesc);
				fp->page = sdesc->page;
				fp->offset = rspq->offset;
				fp->size = min(bufsz, len);
				len -= fp->size;
				अगर (!len)
					अवरोध;
				unmap_rx_buf(rspq->adapter, &rxq->fl);
			पूर्ण
			gl.nfrags = frag+1;

			/*
			 * Last buffer reमुख्यs mapped so explicitly make it
			 * coherent क्रम CPU access and start preloading first
			 * cache line ...
			 */
			dma_sync_single_क्रम_cpu(rspq->adapter->pdev_dev,
						get_buf_addr(sdesc),
						fp->size, DMA_FROM_DEVICE);
			gl.va = (page_address(gl.frags[0].page) +
				 gl.frags[0].offset);
			prefetch(gl.va);

			/*
			 * Hand the new ingress packet to the handler क्रम
			 * this Response Queue.
			 */
			ret = rspq->handler(rspq, rspq->cur_desc, &gl);
			अगर (likely(ret == 0))
				rspq->offset += ALIGN(fp->size, s->fl_align);
			अन्यथा
				restore_rx_bufs(&gl, &rxq->fl, frag);
		पूर्ण अन्यथा अगर (likely(rsp_type == RSPD_TYPE_CPL_X)) अणु
			ret = rspq->handler(rspq, rspq->cur_desc, शून्य);
		पूर्ण अन्यथा अणु
			WARN_ON(rsp_type > RSPD_TYPE_CPL_X);
			ret = 0;
		पूर्ण

		अगर (unlikely(ret)) अणु
			/*
			 * Couldn't process descriptor, back off क्रम recovery.
			 * We use the SGE's last समयr which has the दीर्घest
			 * पूर्णांकerrupt coalescing value ...
			 */
			स्थिर पूर्णांक NOMEM_TIMER_IDX = SGE_NTIMERS-1;
			rspq->next_पूर्णांकr_params =
				QINTR_TIMER_IDX_V(NOMEM_TIMER_IDX);
			अवरोध;
		पूर्ण

		rspq_next(rspq);
		budget_left--;
	पूर्ण

	/*
	 * If this is a Response Queue with an associated Free List and
	 * at least two Egress Queue units available in the Free List
	 * क्रम new buffer poपूर्णांकers, refill the Free List.
	 */
	अगर (rspq->offset >= 0 &&
	    fl_cap(&rxq->fl) - rxq->fl.avail >= 2*FL_PER_EQ_UNIT)
		__refill_fl(rspq->adapter, &rxq->fl);
	वापस budget - budget_left;
पूर्ण

/**
 *	napi_rx_handler - the NAPI handler क्रम RX processing
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
	अचिन्हित पूर्णांक पूर्णांकr_params;
	काष्ठा sge_rspq *rspq = container_of(napi, काष्ठा sge_rspq, napi);
	पूर्णांक work_करोne = process_responses(rspq, budget);
	u32 val;

	अगर (likely(work_करोne < budget)) अणु
		napi_complete_करोne(napi, work_करोne);
		पूर्णांकr_params = rspq->next_पूर्णांकr_params;
		rspq->next_पूर्णांकr_params = rspq->पूर्णांकr_params;
	पूर्ण अन्यथा
		पूर्णांकr_params = QINTR_TIMER_IDX_V(SGE_TIMER_UPD_CIDX);

	अगर (unlikely(work_करोne == 0))
		rspq->unhandled_irqs++;

	val = CIDXINC_V(work_करोne) | SEINTARM_V(पूर्णांकr_params);
	/* If we करोn't have access to the new User GTS (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(!rspq->bar2_addr)) अणु
		t4_ग_लिखो_reg(rspq->adapter,
			     T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     val | INGRESSQID_V((u32)rspq->cntxt_id));
	पूर्ण अन्यथा अणु
		ग_लिखोl(val | INGRESSQID_V(rspq->bar2_qid),
		       rspq->bar2_addr + SGE_UDB_GTS);
		wmb();
	पूर्ण
	वापस work_करोne;
पूर्ण

/*
 * The MSI-X पूर्णांकerrupt handler क्रम an SGE response queue क्रम the NAPI हाल
 * (i.e., response queue serviced by NAPI polling).
 */
irqवापस_t t4vf_sge_पूर्णांकr_msix(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा sge_rspq *rspq = cookie;

	napi_schedule(&rspq->napi);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Process the indirect पूर्णांकerrupt entries in the पूर्णांकerrupt queue and kick off
 * NAPI क्रम each queue that has generated an entry.
 */
अटल अचिन्हित पूर्णांक process_पूर्णांकrq(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	काष्ठा sge_rspq *पूर्णांकrq = &s->पूर्णांकrq;
	अचिन्हित पूर्णांक work_करोne;
	u32 val;

	spin_lock(&adapter->sge.पूर्णांकrq_lock);
	क्रम (work_करोne = 0; ; work_करोne++) अणु
		स्थिर काष्ठा rsp_ctrl *rc;
		अचिन्हित पूर्णांक qid, iq_idx;
		काष्ठा sge_rspq *rspq;

		/*
		 * Grab the next response from the पूर्णांकerrupt queue and bail
		 * out अगर it's not a new response.
		 */
		rc = (व्योम *)पूर्णांकrq->cur_desc + (पूर्णांकrq->iqe_len - माप(*rc));
		अगर (!is_new_response(rc, पूर्णांकrq))
			अवरोध;

		/*
		 * If the response isn't a क्रमwarded पूर्णांकerrupt message issue a
		 * error and go on to the next response message.  This should
		 * never happen ...
		 */
		dma_rmb();
		अगर (unlikely(RSPD_TYPE_G(rc->type_gen) != RSPD_TYPE_INTR_X)) अणु
			dev_err(adapter->pdev_dev,
				"Unexpected INTRQ response type %d\n",
				RSPD_TYPE_G(rc->type_gen));
			जारी;
		पूर्ण

		/*
		 * Extract the Queue ID from the पूर्णांकerrupt message and perक्रमm
		 * sanity checking to make sure it really refers to one of our
		 * Ingress Queues which is active and matches the queue's ID.
		 * None of these error conditions should ever happen so we may
		 * want to either make them fatal and/or conditionalized under
		 * DEBUG.
		 */
		qid = RSPD_QID_G(be32_to_cpu(rc->pldbuflen_qid));
		iq_idx = IQ_IDX(s, qid);
		अगर (unlikely(iq_idx >= MAX_INGQ)) अणु
			dev_err(adapter->pdev_dev,
				"Ingress QID %d out of range\n", qid);
			जारी;
		पूर्ण
		rspq = s->ingr_map[iq_idx];
		अगर (unlikely(rspq == शून्य)) अणु
			dev_err(adapter->pdev_dev,
				"Ingress QID %d RSPQ=NULL\n", qid);
			जारी;
		पूर्ण
		अगर (unlikely(rspq->असल_id != qid)) अणु
			dev_err(adapter->pdev_dev,
				"Ingress QID %d refers to RSPQ %d\n",
				qid, rspq->असल_id);
			जारी;
		पूर्ण

		/*
		 * Schedule NAPI processing on the indicated Response Queue
		 * and move on to the next entry in the Forwarded Interrupt
		 * Queue.
		 */
		napi_schedule(&rspq->napi);
		rspq_next(पूर्णांकrq);
	पूर्ण

	val = CIDXINC_V(work_करोne) | SEINTARM_V(पूर्णांकrq->पूर्णांकr_params);
	/* If we करोn't have access to the new User GTS (T5+), use the old
	 * करोorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	अगर (unlikely(!पूर्णांकrq->bar2_addr)) अणु
		t4_ग_लिखो_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     val | INGRESSQID_V(पूर्णांकrq->cntxt_id));
	पूर्ण अन्यथा अणु
		ग_लिखोl(val | INGRESSQID_V(पूर्णांकrq->bar2_qid),
		       पूर्णांकrq->bar2_addr + SGE_UDB_GTS);
		wmb();
	पूर्ण

	spin_unlock(&adapter->sge.पूर्णांकrq_lock);

	वापस work_करोne;
पूर्ण

/*
 * The MSI पूर्णांकerrupt handler handles data events from SGE response queues as
 * well as error and other async events as they all use the same MSI vector.
 */
अटल irqवापस_t t4vf_पूर्णांकr_msi(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा adapter *adapter = cookie;

	process_पूर्णांकrq(adapter);
	वापस IRQ_HANDLED;
पूर्ण

/**
 *	t4vf_पूर्णांकr_handler - select the top-level पूर्णांकerrupt handler
 *	@adapter: the adapter
 *
 *	Selects the top-level पूर्णांकerrupt handler based on the type of पूर्णांकerrupts
 *	(MSI-X or MSI).
 */
irq_handler_t t4vf_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	BUG_ON((adapter->flags &
	       (CXGB4VF_USING_MSIX | CXGB4VF_USING_MSI)) == 0);
	अगर (adapter->flags & CXGB4VF_USING_MSIX)
		वापस t4vf_sge_पूर्णांकr_msix;
	अन्यथा
		वापस t4vf_पूर्णांकr_msi;
पूर्ण

/**
 *	sge_rx_समयr_cb - perक्रमm periodic मुख्यtenance of SGE RX queues
 *	@t: Rx समयr
 *
 *	Runs periodically from a समयr to perक्रमm मुख्यtenance of SGE RX queues.
 *
 *	a) Replenishes RX queues that have run out due to memory लघुage.
 *	Normally new RX buffers are added when existing ones are consumed but
 *	when out of memory a queue can become empty.  We schedule NAPI to करो
 *	the actual refill.
 */
अटल व्योम sge_rx_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t, sge.rx_समयr);
	काष्ठा sge *s = &adapter->sge;
	अचिन्हित पूर्णांक i;

	/*
	 * Scan the "Starving Free Lists" flag array looking क्रम any Free
	 * Lists in need of more मुक्त buffers.  If we find one and it's not
	 * being actively polled, then bump its "starving" counter and attempt
	 * to refill it.  If we're successful in adding enough buffers to push
	 * the Free List over the starving threshold, then we can clear its
	 * "starving" status.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(s->starving_fl); i++) अणु
		अचिन्हित दीर्घ m;

		क्रम (m = s->starving_fl[i]; m; m &= m - 1) अणु
			अचिन्हित पूर्णांक id = __ffs(m) + i * BITS_PER_LONG;
			काष्ठा sge_fl *fl = s->egr_map[id];

			clear_bit(id, s->starving_fl);
			smp_mb__after_atomic();

			/*
			 * Since we are accessing fl without a lock there's a
			 * small probability of a false positive where we
			 * schedule napi but the FL is no दीर्घer starving.
			 * No biggie.
			 */
			अगर (fl_starving(adapter, fl)) अणु
				काष्ठा sge_eth_rxq *rxq;

				rxq = container_of(fl, काष्ठा sge_eth_rxq, fl);
				अगर (napi_reschedule(&rxq->rspq.napi))
					fl->starving++;
				अन्यथा
					set_bit(id, s->starving_fl);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Reschedule the next scan क्रम starving Free Lists ...
	 */
	mod_समयr(&s->rx_समयr, jअगरfies + RX_QCHECK_PERIOD);
पूर्ण

/**
 *	sge_tx_समयr_cb - perक्रमm periodic मुख्यtenance of SGE Tx queues
 *	@t: Tx समयr
 *
 *	Runs periodically from a समयr to perक्रमm मुख्यtenance of SGE TX queues.
 *
 *	b) Reclaims completed Tx packets क्रम the Ethernet queues.  Normally
 *	packets are cleaned up by new Tx packets, this समयr cleans up packets
 *	when no new packets are being submitted.  This is essential क्रम pktgen,
 *	at least.
 */
अटल व्योम sge_tx_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t, sge.tx_समयr);
	काष्ठा sge *s = &adapter->sge;
	अचिन्हित पूर्णांक i, budget;

	budget = MAX_TIMER_TX_RECLAIM;
	i = s->ethtxq_rover;
	करो अणु
		काष्ठा sge_eth_txq *txq = &s->ethtxq[i];

		अगर (reclaimable(&txq->q) && __netअगर_tx_trylock(txq->txq)) अणु
			पूर्णांक avail = reclaimable(&txq->q);

			अगर (avail > budget)
				avail = budget;

			मुक्त_tx_desc(adapter, &txq->q, avail, true);
			txq->q.in_use -= avail;
			__netअगर_tx_unlock(txq->txq);

			budget -= avail;
			अगर (!budget)
				अवरोध;
		पूर्ण

		i++;
		अगर (i >= s->ethqsets)
			i = 0;
	पूर्ण जबतक (i != s->ethtxq_rover);
	s->ethtxq_rover = i;

	/*
	 * If we found too many reclaimable packets schedule a समयr in the
	 * near future to जारी where we left off.  Otherwise the next समयr
	 * will be at its normal पूर्णांकerval.
	 */
	mod_समयr(&s->tx_समयr, jअगरfies + (budget ? TX_QCHECK_PERIOD : 2));
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

	ret = t4vf_bar2_sge_qregs(adapter, qid, qtype,
				  &bar2_qoffset, pbar2_qid);
	अगर (ret)
		वापस शून्य;

	वापस adapter->bar2 + bar2_qoffset;
पूर्ण

/**
 *	t4vf_sge_alloc_rxq - allocate an SGE RX Queue
 *	@adapter: the adapter
 *	@rspq: poपूर्णांकer to to the new rxq's Response Queue to be filled in
 *	@iqasynch: अगर 0, a normal rspq; अगर 1, an asynchronous event queue
 *	@dev: the network device associated with the new rspq
 *	@पूर्णांकr_dest: MSI-X vector index (overriden in MSI mode)
 *	@fl: poपूर्णांकer to the new rxq's Free List to be filled in
 *	@hnd: the पूर्णांकerrupt handler to invoke क्रम the rspq
 */
पूर्णांक t4vf_sge_alloc_rxq(काष्ठा adapter *adapter, काष्ठा sge_rspq *rspq,
		       bool iqasynch, काष्ठा net_device *dev,
		       पूर्णांक पूर्णांकr_dest,
		       काष्ठा sge_fl *fl, rspq_handler_t hnd)
अणु
	काष्ठा sge *s = &adapter->sge;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा fw_iq_cmd cmd, rpl;
	पूर्णांक ret, iqandst, flsz = 0;
	पूर्णांक relaxed = !(adapter->flags & CXGB4VF_ROOT_NO_RELAXED_ORDERING);

	/*
	 * If we're using MSI interrupts and we're not initializing the
	 * Forwarded Interrupt Queue itself, then set up this queue क्रम
	 * indirect पूर्णांकerrupts to the Forwarded Interrupt Queue.  Obviously
	 * the Forwarded Interrupt Queue must be set up beक्रमe any other
	 * ingress queue ...
	 */
	अगर ((adapter->flags & CXGB4VF_USING_MSI) &&
	    rspq != &adapter->sge.पूर्णांकrq) अणु
		iqandst = SGE_INTRDST_IQ;
		पूर्णांकr_dest = adapter->sge.पूर्णांकrq.असल_id;
	पूर्ण अन्यथा
		iqandst = SGE_INTRDST_PCI;

	/*
	 * Allocate the hardware ring क्रम the Response Queue.  The size needs
	 * to be a multiple of 16 which includes the mandatory status entry
	 * (regardless of whether the Status Page capabilities are enabled or
	 * not).
	 */
	rspq->size = roundup(rspq->size, 16);
	rspq->desc = alloc_ring(adapter->pdev_dev, rspq->size, rspq->iqe_len,
				0, &rspq->phys_addr, शून्य, 0);
	अगर (!rspq->desc)
		वापस -ENOMEM;

	/*
	 * Fill in the Ingress Queue Command.  Note: Ideally this code would
	 * be in t4vf_hw.c but there are so many parameters and dependencies
	 * on our Linux SGE state that we would end up having to pass tons of
	 * parameters.  We'll have to think about how this might be migrated
	 * पूर्णांकo OS-independent common code ...
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_IQ_CMD_ALLOC_F |
					 FW_IQ_CMD_IQSTART_F |
					 FW_LEN16(cmd));
	cmd.type_to_iqandstindex =
		cpu_to_be32(FW_IQ_CMD_TYPE_V(FW_IQ_TYPE_FL_INT_CAP) |
			    FW_IQ_CMD_IQASYNCH_V(iqasynch) |
			    FW_IQ_CMD_VIID_V(pi->viid) |
			    FW_IQ_CMD_IQANDST_V(iqandst) |
			    FW_IQ_CMD_IQANUS_V(1) |
			    FW_IQ_CMD_IQANUD_V(SGE_UPDATEDEL_INTR) |
			    FW_IQ_CMD_IQANDSTINDEX_V(पूर्णांकr_dest));
	cmd.iqdroprss_to_iqesize =
		cpu_to_be16(FW_IQ_CMD_IQPCIECH_V(pi->port_id) |
			    FW_IQ_CMD_IQGTSMODE_F |
			    FW_IQ_CMD_IQINTCNTTHRESH_V(rspq->pktcnt_idx) |
			    FW_IQ_CMD_IQESIZE_V(ilog2(rspq->iqe_len) - 4));
	cmd.iqsize = cpu_to_be16(rspq->size);
	cmd.iqaddr = cpu_to_be64(rspq->phys_addr);

	अगर (fl) अणु
		अचिन्हित पूर्णांक chip_ver =
			CHELSIO_CHIP_VERSION(adapter->params.chip);
		/*
		 * Allocate the ring क्रम the hardware मुक्त list (with space
		 * क्रम its status page) aदीर्घ with the associated software
		 * descriptor ring.  The मुक्त list size needs to be a multiple
		 * of the Egress Queue Unit and at least 2 Egress Units larger
		 * than the SGE's Egress Congrestion Threshold
		 * (fl_starve_thres - 1).
		 */
		अगर (fl->size < s->fl_starve_thres - 1 + 2 * FL_PER_EQ_UNIT)
			fl->size = s->fl_starve_thres - 1 + 2 * FL_PER_EQ_UNIT;
		fl->size = roundup(fl->size, FL_PER_EQ_UNIT);
		fl->desc = alloc_ring(adapter->pdev_dev, fl->size,
				      माप(__be64), माप(काष्ठा rx_sw_desc),
				      &fl->addr, &fl->sdesc, s->stat_len);
		अगर (!fl->desc) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		/*
		 * Calculate the size of the hardware मुक्त list ring plus
		 * Status Page (which the SGE will place after the end of the
		 * मुक्त list ring) in Egress Queue Units.
		 */
		flsz = (fl->size / FL_PER_EQ_UNIT +
			s->stat_len / EQ_UNIT);

		/*
		 * Fill in all the relevant firmware Ingress Queue Command
		 * fields क्रम the मुक्त list.
		 */
		cmd.iqns_to_fl0congen =
			cpu_to_be32(
				FW_IQ_CMD_FL0HOSTFCMODE_V(SGE_HOSTFCMODE_NONE) |
				FW_IQ_CMD_FL0PACKEN_F |
				FW_IQ_CMD_FL0FETCHRO_V(relaxed) |
				FW_IQ_CMD_FL0DATARO_V(relaxed) |
				FW_IQ_CMD_FL0PADEN_F);

		/* In T6, क्रम egress queue type FL there is पूर्णांकernal overhead
		 * of 16B क्रम header going पूर्णांकo FLM module.  Hence the maximum
		 * allowed burst size is 448 bytes.  For T4/T5, the hardware
		 * करोesn't coalesce fetch requests अगर more than 64 bytes of
		 * Free List poपूर्णांकers are provided, so we use a 128-byte Fetch
		 * Burst Minimum there (T6 implements coalescing so we can use
		 * the smaller 64-byte value there).
		 */
		cmd.fl0dcaen_to_fl0cidxfthresh =
			cpu_to_be16(
				FW_IQ_CMD_FL0FBMIN_V(chip_ver <= CHELSIO_T5
						     ? FETCHBURSTMIN_128B_X
						     : FETCHBURSTMIN_64B_T6_X) |
				FW_IQ_CMD_FL0FBMAX_V((chip_ver <= CHELSIO_T5) ?
						     FETCHBURSTMAX_512B_X :
						     FETCHBURSTMAX_256B_X));
		cmd.fl0size = cpu_to_be16(flsz);
		cmd.fl0addr = cpu_to_be64(fl->addr);
	पूर्ण

	/*
	 * Issue the firmware Ingress Queue Command and extract the results अगर
	 * it completes successfully.
	 */
	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (ret)
		जाओ err;

	netअगर_napi_add(dev, &rspq->napi, napi_rx_handler, 64);
	rspq->cur_desc = rspq->desc;
	rspq->cidx = 0;
	rspq->gen = 1;
	rspq->next_पूर्णांकr_params = rspq->पूर्णांकr_params;
	rspq->cntxt_id = be16_to_cpu(rpl.iqid);
	rspq->bar2_addr = bar2_address(adapter,
				       rspq->cntxt_id,
				       T4_BAR2_QTYPE_INGRESS,
				       &rspq->bar2_qid);
	rspq->असल_id = be16_to_cpu(rpl.physiqid);
	rspq->size--;			/* subtract status entry */
	rspq->adapter = adapter;
	rspq->netdev = dev;
	rspq->handler = hnd;

	/* set offset to -1 to distinguish ingress queues without FL */
	rspq->offset = fl ? 0 : -1;

	अगर (fl) अणु
		fl->cntxt_id = be16_to_cpu(rpl.fl0id);
		fl->avail = 0;
		fl->pend_cred = 0;
		fl->pidx = 0;
		fl->cidx = 0;
		fl->alloc_failed = 0;
		fl->large_alloc_failed = 0;
		fl->starving = 0;

		/* Note, we must initialize the BAR2 Free List User Doorbell
		 * inक्रमmation beक्रमe refilling the Free List!
		 */
		fl->bar2_addr = bar2_address(adapter,
					     fl->cntxt_id,
					     T4_BAR2_QTYPE_EGRESS,
					     &fl->bar2_qid);

		refill_fl(adapter, fl, fl_cap(fl), GFP_KERNEL);
	पूर्ण

	वापस 0;

err:
	/*
	 * An error occurred.  Clean up our partial allocation state and
	 * वापस the error.
	 */
	अगर (rspq->desc) अणु
		dma_मुक्त_coherent(adapter->pdev_dev, rspq->size * rspq->iqe_len,
				  rspq->desc, rspq->phys_addr);
		rspq->desc = शून्य;
	पूर्ण
	अगर (fl && fl->desc) अणु
		kमुक्त(fl->sdesc);
		fl->sdesc = शून्य;
		dma_मुक्त_coherent(adapter->pdev_dev, flsz * EQ_UNIT,
				  fl->desc, fl->addr);
		fl->desc = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t4vf_sge_alloc_eth_txq - allocate an SGE Ethernet TX Queue
 *	@adapter: the adapter
 *	@txq: poपूर्णांकer to the new txq to be filled in
 *	@dev: the network device
 *	@devq: the network TX queue associated with the new txq
 *	@iqid: the relative ingress queue ID to which events relating to
 *		the new txq should be directed
 */
पूर्णांक t4vf_sge_alloc_eth_txq(काष्ठा adapter *adapter, काष्ठा sge_eth_txq *txq,
			   काष्ठा net_device *dev, काष्ठा netdev_queue *devq,
			   अचिन्हित पूर्णांक iqid)
अणु
	अचिन्हित पूर्णांक chip_ver = CHELSIO_CHIP_VERSION(adapter->params.chip);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा fw_eq_eth_cmd cmd, rpl;
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक ret, nentries;

	/*
	 * Calculate the size of the hardware TX Queue (including the Status
	 * Page on the end of the TX Queue) in units of TX Descriptors.
	 */
	nentries = txq->q.size + s->stat_len / माप(काष्ठा tx_desc);

	/*
	 * Allocate the hardware ring क्रम the TX ring (with space क्रम its
	 * status page) aदीर्घ with the associated software descriptor ring.
	 */
	txq->q.desc = alloc_ring(adapter->pdev_dev, txq->q.size,
				 माप(काष्ठा tx_desc),
				 माप(काष्ठा tx_sw_desc),
				 &txq->q.phys_addr, &txq->q.sdesc, s->stat_len);
	अगर (!txq->q.desc)
		वापस -ENOMEM;

	/*
	 * Fill in the Egress Queue Command.  Note: As with the direct use of
	 * the firmware Ingress Queue COmmand above in our RXQ allocation
	 * routine, ideally, this code would be in t4vf_hw.c.  Again, we'll
	 * have to see अगर there's some reasonable way to parameterize it
	 * पूर्णांकo the common code ...
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_ETH_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_EQ_ETH_CMD_ALLOC_F |
					 FW_EQ_ETH_CMD_EQSTART_F |
					 FW_LEN16(cmd));
	cmd.स्वतःequiqe_to_viid = cpu_to_be32(FW_EQ_ETH_CMD_AUTOEQUEQE_F |
					     FW_EQ_ETH_CMD_VIID_V(pi->viid));
	cmd.fetchszm_to_iqid =
		cpu_to_be32(FW_EQ_ETH_CMD_HOSTFCMODE_V(SGE_HOSTFCMODE_STPG) |
			    FW_EQ_ETH_CMD_PCIECHN_V(pi->port_id) |
			    FW_EQ_ETH_CMD_IQID_V(iqid));
	cmd.dcaen_to_eqsize =
		cpu_to_be32(FW_EQ_ETH_CMD_FBMIN_V(chip_ver <= CHELSIO_T5
						  ? FETCHBURSTMIN_64B_X
						  : FETCHBURSTMIN_64B_T6_X) |
			    FW_EQ_ETH_CMD_FBMAX_V(FETCHBURSTMAX_512B_X) |
			    FW_EQ_ETH_CMD_CIDXFTHRESH_V(
						CIDXFLUSHTHRESH_32_X) |
			    FW_EQ_ETH_CMD_EQSIZE_V(nentries));
	cmd.eqaddr = cpu_to_be64(txq->q.phys_addr);

	/*
	 * Issue the firmware Egress Queue Command and extract the results अगर
	 * it completes successfully.
	 */
	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (ret) अणु
		/*
		 * The girmware Ingress Queue Command failed क्रम some reason.
		 * Free up our partial allocation state and वापस the error.
		 */
		kमुक्त(txq->q.sdesc);
		txq->q.sdesc = शून्य;
		dma_मुक्त_coherent(adapter->pdev_dev,
				  nentries * माप(काष्ठा tx_desc),
				  txq->q.desc, txq->q.phys_addr);
		txq->q.desc = शून्य;
		वापस ret;
	पूर्ण

	txq->q.in_use = 0;
	txq->q.cidx = 0;
	txq->q.pidx = 0;
	txq->q.stat = (व्योम *)&txq->q.desc[txq->q.size];
	txq->q.cntxt_id = FW_EQ_ETH_CMD_EQID_G(be32_to_cpu(rpl.eqid_pkd));
	txq->q.bar2_addr = bar2_address(adapter,
					txq->q.cntxt_id,
					T4_BAR2_QTYPE_EGRESS,
					&txq->q.bar2_qid);
	txq->q.असल_id =
		FW_EQ_ETH_CMD_PHYSEQID_G(be32_to_cpu(rpl.physeqid_pkd));
	txq->txq = devq;
	txq->tso = 0;
	txq->tx_cso = 0;
	txq->vlan_ins = 0;
	txq->q.stops = 0;
	txq->q.restarts = 0;
	txq->mapping_err = 0;
	वापस 0;
पूर्ण

/*
 * Free the DMA map resources associated with a TX queue.
 */
अटल व्योम मुक्त_txq(काष्ठा adapter *adapter, काष्ठा sge_txq *tq)
अणु
	काष्ठा sge *s = &adapter->sge;

	dma_मुक्त_coherent(adapter->pdev_dev,
			  tq->size * माप(*tq->desc) + s->stat_len,
			  tq->desc, tq->phys_addr);
	tq->cntxt_id = 0;
	tq->sdesc = शून्य;
	tq->desc = शून्य;
पूर्ण

/*
 * Free the resources associated with a response queue (possibly including a
 * मुक्त list).
 */
अटल व्योम मुक्त_rspq_fl(काष्ठा adapter *adapter, काष्ठा sge_rspq *rspq,
			 काष्ठा sge_fl *fl)
अणु
	काष्ठा sge *s = &adapter->sge;
	अचिन्हित पूर्णांक flid = fl ? fl->cntxt_id : 0xffff;

	t4vf_iq_मुक्त(adapter, FW_IQ_TYPE_FL_INT_CAP,
		     rspq->cntxt_id, flid, 0xffff);
	dma_मुक्त_coherent(adapter->pdev_dev, (rspq->size + 1) * rspq->iqe_len,
			  rspq->desc, rspq->phys_addr);
	netअगर_napi_del(&rspq->napi);
	rspq->netdev = शून्य;
	rspq->cntxt_id = 0;
	rspq->असल_id = 0;
	rspq->desc = शून्य;

	अगर (fl) अणु
		मुक्त_rx_bufs(adapter, fl, fl->avail);
		dma_मुक्त_coherent(adapter->pdev_dev,
				  fl->size * माप(*fl->desc) + s->stat_len,
				  fl->desc, fl->addr);
		kमुक्त(fl->sdesc);
		fl->sdesc = शून्य;
		fl->cntxt_id = 0;
		fl->desc = शून्य;
	पूर्ण
पूर्ण

/**
 *	t4vf_मुक्त_sge_resources - मुक्त SGE resources
 *	@adapter: the adapter
 *
 *	Frees resources used by the SGE queue sets.
 */
व्योम t4vf_मुक्त_sge_resources(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	काष्ठा sge_eth_rxq *rxq = s->ethrxq;
	काष्ठा sge_eth_txq *txq = s->ethtxq;
	काष्ठा sge_rspq *evtq = &s->fw_evtq;
	काष्ठा sge_rspq *पूर्णांकrq = &s->पूर्णांकrq;
	पूर्णांक qs;

	क्रम (qs = 0; qs < adapter->sge.ethqsets; qs++, rxq++, txq++) अणु
		अगर (rxq->rspq.desc)
			मुक्त_rspq_fl(adapter, &rxq->rspq, &rxq->fl);
		अगर (txq->q.desc) अणु
			t4vf_eth_eq_मुक्त(adapter, txq->q.cntxt_id);
			मुक्त_tx_desc(adapter, &txq->q, txq->q.in_use, true);
			kमुक्त(txq->q.sdesc);
			मुक्त_txq(adapter, &txq->q);
		पूर्ण
	पूर्ण
	अगर (evtq->desc)
		मुक्त_rspq_fl(adapter, evtq, शून्य);
	अगर (पूर्णांकrq->desc)
		मुक्त_rspq_fl(adapter, पूर्णांकrq, शून्य);
पूर्ण

/**
 *	t4vf_sge_start - enable SGE operation
 *	@adapter: the adapter
 *
 *	Start tasklets and समयrs associated with the DMA engine.
 */
व्योम t4vf_sge_start(काष्ठा adapter *adapter)
अणु
	adapter->sge.ethtxq_rover = 0;
	mod_समयr(&adapter->sge.rx_समयr, jअगरfies + RX_QCHECK_PERIOD);
	mod_समयr(&adapter->sge.tx_समयr, jअगरfies + TX_QCHECK_PERIOD);
पूर्ण

/**
 *	t4vf_sge_stop - disable SGE operation
 *	@adapter: the adapter
 *
 *	Stop tasklets and समयrs associated with the DMA engine.  Note that
 *	this is effective only अगर measures have been taken to disable any HW
 *	events that may restart them.
 */
व्योम t4vf_sge_stop(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;

	अगर (s->rx_समयr.function)
		del_समयr_sync(&s->rx_समयr);
	अगर (s->tx_समयr.function)
		del_समयr_sync(&s->tx_समयr);
पूर्ण

/**
 *	t4vf_sge_init - initialize SGE
 *	@adapter: the adapter
 *
 *	Perक्रमms SGE initialization needed every समय after a chip reset.
 *	We करो not initialize any of the queue sets here, instead the driver
 *	top-level must request those inभागidually.  We also करो not enable DMA
 *	here, that should be करोne after the queues have been set up.
 */
पूर्णांक t4vf_sge_init(काष्ठा adapter *adapter)
अणु
	काष्ठा sge_params *sge_params = &adapter->params.sge;
	u32 fl_small_pg = sge_params->sge_fl_buffer_size[0];
	u32 fl_large_pg = sge_params->sge_fl_buffer_size[1];
	काष्ठा sge *s = &adapter->sge;

	/*
	 * Start by vetting the basic SGE parameters which have been set up by
	 * the Physical Function Driver.  Ideally we should be able to deal
	 * with _any_ configuration.  Practice is dअगरferent ...
	 */

	/* We only bother using the Large Page logic अगर the Large Page Buffer
	 * is larger than our Page Size Buffer.
	 */
	अगर (fl_large_pg <= fl_small_pg)
		fl_large_pg = 0;

	/* The Page Size Buffer must be exactly equal to our Page Size and the
	 * Large Page Size Buffer should be 0 (per above) or a घातer of 2.
	 */
	अगर (fl_small_pg != PAGE_SIZE ||
	    (fl_large_pg & (fl_large_pg - 1)) != 0) अणु
		dev_err(adapter->pdev_dev, "bad SGE FL buffer sizes [%d, %d]\n",
			fl_small_pg, fl_large_pg);
		वापस -EINVAL;
	पूर्ण
	अगर ((sge_params->sge_control & RXPKTCPLMODE_F) !=
	    RXPKTCPLMODE_V(RXPKTCPLMODE_SPLIT_X)) अणु
		dev_err(adapter->pdev_dev, "bad SGE CPL MODE\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now translate the adapter parameters पूर्णांकo our पूर्णांकernal क्रमms.
	 */
	अगर (fl_large_pg)
		s->fl_pg_order = ilog2(fl_large_pg) - PAGE_SHIFT;
	s->stat_len = ((sge_params->sge_control & EGRSTATUSPAGESIZE_F)
			? 128 : 64);
	s->pktshअगरt = PKTSHIFT_G(sge_params->sge_control);
	s->fl_align = t4vf_fl_pkt_align(adapter);

	/* A FL with <= fl_starve_thres buffers is starving and a periodic
	 * समयr will attempt to refill it.  This needs to be larger than the
	 * SGE's Egress Congestion Threshold.  If it isn't, then we can get
	 * stuck रुकोing क्रम new packets जबतक the SGE is रुकोing क्रम us to
	 * give it more Free List entries.  (Note that the SGE's Egress
	 * Congestion Threshold is in units of 2 Free List poपूर्णांकers.)
	 */
	चयन (CHELSIO_CHIP_VERSION(adapter->params.chip)) अणु
	हाल CHELSIO_T4:
		s->fl_starve_thres =
		   EGRTHRESHOLD_G(sge_params->sge_congestion_control);
		अवरोध;
	हाल CHELSIO_T5:
		s->fl_starve_thres =
		   EGRTHRESHOLDPACKING_G(sge_params->sge_congestion_control);
		अवरोध;
	हाल CHELSIO_T6:
	शेष:
		s->fl_starve_thres =
		   T6_EGRTHRESHOLDPACKING_G(sge_params->sge_congestion_control);
		अवरोध;
	पूर्ण
	s->fl_starve_thres = s->fl_starve_thres * 2 + 1;

	/*
	 * Set up tasklet समयrs.
	 */
	समयr_setup(&s->rx_समयr, sge_rx_समयr_cb, 0);
	समयr_setup(&s->tx_समयr, sge_tx_समयr_cb, 0);

	/*
	 * Initialize Forwarded Interrupt Queue lock.
	 */
	spin_lock_init(&s->पूर्णांकrq_lock);

	वापस 0;
पूर्ण
