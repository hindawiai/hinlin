<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/iommu.h>
#समावेश <net/ip.h>
#समावेश <net/tso.h>

#समावेश "nic_reg.h"
#समावेश "nic.h"
#समावेश "q_struct.h"
#समावेश "nicvf_queues.h"

अटल अंतरभूत व्योम nicvf_sq_add_gather_subdesc(काष्ठा snd_queue *sq, पूर्णांक qentry,
					       पूर्णांक size, u64 data);
अटल व्योम nicvf_get_page(काष्ठा nicvf *nic)
अणु
	अगर (!nic->rb_pageref || !nic->rb_page)
		वापस;

	page_ref_add(nic->rb_page, nic->rb_pageref);
	nic->rb_pageref = 0;
पूर्ण

/* Poll a रेजिस्टर क्रम a specअगरic value */
अटल पूर्णांक nicvf_poll_reg(काष्ठा nicvf *nic, पूर्णांक qidx,
			  u64 reg, पूर्णांक bit_pos, पूर्णांक bits, पूर्णांक val)
अणु
	u64 bit_mask;
	u64 reg_val;
	पूर्णांक समयout = 10;

	bit_mask = (1ULL << bits) - 1;
	bit_mask = (bit_mask << bit_pos);

	जबतक (समयout) अणु
		reg_val = nicvf_queue_reg_पढ़ो(nic, reg, qidx);
		अगर (((reg_val & bit_mask) >> bit_pos) == val)
			वापस 0;
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण
	netdev_err(nic->netdev, "Poll on reg 0x%llx failed\n", reg);
	वापस 1;
पूर्ण

/* Allocate memory क्रम a queue's descriptors */
अटल पूर्णांक nicvf_alloc_q_desc_mem(काष्ठा nicvf *nic, काष्ठा q_desc_mem *dmem,
				  पूर्णांक q_len, पूर्णांक desc_size, पूर्णांक align_bytes)
अणु
	dmem->q_len = q_len;
	dmem->size = (desc_size * q_len) + align_bytes;
	/* Save address, need it जबतक मुक्तing */
	dmem->unalign_base = dma_alloc_coherent(&nic->pdev->dev, dmem->size,
						&dmem->dma, GFP_KERNEL);
	अगर (!dmem->unalign_base)
		वापस -ENOMEM;

	/* Align memory address क्रम 'align_bytes' */
	dmem->phys_base = NICVF_ALIGNED_ADDR((u64)dmem->dma, align_bytes);
	dmem->base = dmem->unalign_base + (dmem->phys_base - dmem->dma);
	वापस 0;
पूर्ण

/* Free queue's descriptor memory */
अटल व्योम nicvf_मुक्त_q_desc_mem(काष्ठा nicvf *nic, काष्ठा q_desc_mem *dmem)
अणु
	अगर (!dmem)
		वापस;

	dma_मुक्त_coherent(&nic->pdev->dev, dmem->size,
			  dmem->unalign_base, dmem->dma);
	dmem->unalign_base = शून्य;
	dmem->base = शून्य;
पूर्ण

#घोषणा XDP_PAGE_REFCNT_REFILL 256

/* Allocate a new page or recycle one अगर possible
 *
 * We cannot optimize dma mapping here, since
 * 1. It's only one RBDR ring क्रम 8 Rx queues.
 * 2. CQE_RX gives address of the buffer where pkt has been DMA'ed
 *    and not idx पूर्णांकo RBDR ring, so can't refer to saved info.
 * 3. There are multiple receive buffers per page
 */
अटल अंतरभूत काष्ठा pgcache *nicvf_alloc_page(काष्ठा nicvf *nic,
					       काष्ठा rbdr *rbdr, gfp_t gfp)
अणु
	पूर्णांक ref_count;
	काष्ठा page *page = शून्य;
	काष्ठा pgcache *pgcache, *next;

	/* Check अगर page is alपढ़ोy allocated */
	pgcache = &rbdr->pgcache[rbdr->pgidx];
	page = pgcache->page;
	/* Check अगर page can be recycled */
	अगर (page) अणु
		ref_count = page_ref_count(page);
		/* This page can be recycled अगर पूर्णांकernal ref_count and page's
		 * ref_count are equal, indicating that the page has been used
		 * once क्रम packet transmission. For non-XDP mode, पूर्णांकernal
		 * ref_count is always '1'.
		 */
		अगर (rbdr->is_xdp) अणु
			अगर (ref_count == pgcache->ref_count)
				pgcache->ref_count--;
			अन्यथा
				page = शून्य;
		पूर्ण अन्यथा अगर (ref_count != 1) अणु
			page = शून्य;
		पूर्ण
	पूर्ण

	अगर (!page) अणु
		page = alloc_pages(gfp | __GFP_COMP | __GFP_NOWARN, 0);
		अगर (!page)
			वापस शून्य;

		this_cpu_inc(nic->pnicvf->drv_stats->page_alloc);

		/* Check क्रम space */
		अगर (rbdr->pgalloc >= rbdr->pgcnt) अणु
			/* Page can still be used */
			nic->rb_page = page;
			वापस शून्य;
		पूर्ण

		/* Save the page in page cache */
		pgcache->page = page;
		pgcache->dma_addr = 0;
		pgcache->ref_count = 0;
		rbdr->pgalloc++;
	पूर्ण

	/* Take additional page references क्रम recycling */
	अगर (rbdr->is_xdp) अणु
		/* Since there is single RBDR (i.e single core करोing
		 * page recycling) per 8 Rx queues, in XDP mode adjusting
		 * page references atomically is the biggest bottleneck, so
		 * take bunch of references at a समय.
		 *
		 * So here, below reference counts defer by '1'.
		 */
		अगर (!pgcache->ref_count) अणु
			pgcache->ref_count = XDP_PAGE_REFCNT_REFILL;
			page_ref_add(page, XDP_PAGE_REFCNT_REFILL);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In non-XDP हाल, single 64K page is भागided across multiple
		 * receive buffers, so cost of recycling is less anyway.
		 * So we can करो with just one extra reference.
		 */
		page_ref_add(page, 1);
	पूर्ण

	rbdr->pgidx++;
	rbdr->pgidx &= (rbdr->pgcnt - 1);

	/* Prefetch refcount of next page in page cache */
	next = &rbdr->pgcache[rbdr->pgidx];
	page = next->page;
	अगर (page)
		prefetch(&page->_refcount);

	वापस pgcache;
पूर्ण

/* Allocate buffer क्रम packet reception */
अटल अंतरभूत पूर्णांक nicvf_alloc_rcv_buffer(काष्ठा nicvf *nic, काष्ठा rbdr *rbdr,
					 gfp_t gfp, u32 buf_len, u64 *rbuf)
अणु
	काष्ठा pgcache *pgcache = शून्य;

	/* Check अगर request can be accomodated in previous allocated page.
	 * But in XDP mode only one buffer per page is permitted.
	 */
	अगर (!rbdr->is_xdp && nic->rb_page &&
	    ((nic->rb_page_offset + buf_len) <= PAGE_SIZE)) अणु
		nic->rb_pageref++;
		जाओ ret;
	पूर्ण

	nicvf_get_page(nic);
	nic->rb_page = शून्य;

	/* Get new page, either recycled or new one */
	pgcache = nicvf_alloc_page(nic, rbdr, gfp);
	अगर (!pgcache && !nic->rb_page) अणु
		this_cpu_inc(nic->pnicvf->drv_stats->rcv_buffer_alloc_failures);
		वापस -ENOMEM;
	पूर्ण

	nic->rb_page_offset = 0;

	/* Reserve space क्रम header modअगरications by BPF program */
	अगर (rbdr->is_xdp)
		buf_len += XDP_PACKET_HEADROOM;

	/* Check अगर it's recycled */
	अगर (pgcache)
		nic->rb_page = pgcache->page;
ret:
	अगर (rbdr->is_xdp && pgcache && pgcache->dma_addr) अणु
		*rbuf = pgcache->dma_addr;
	पूर्ण अन्यथा अणु
		/* HW will ensure data coherency, CPU sync not required */
		*rbuf = (u64)dma_map_page_attrs(&nic->pdev->dev, nic->rb_page,
						nic->rb_page_offset, buf_len,
						DMA_FROM_DEVICE,
						DMA_ATTR_SKIP_CPU_SYNC);
		अगर (dma_mapping_error(&nic->pdev->dev, (dma_addr_t)*rbuf)) अणु
			अगर (!nic->rb_page_offset)
				__मुक्त_pages(nic->rb_page, 0);
			nic->rb_page = शून्य;
			वापस -ENOMEM;
		पूर्ण
		अगर (pgcache)
			pgcache->dma_addr = *rbuf + XDP_PACKET_HEADROOM;
		nic->rb_page_offset += buf_len;
	पूर्ण

	वापस 0;
पूर्ण

/* Build skb around receive buffer */
अटल काष्ठा sk_buff *nicvf_rb_ptr_to_skb(काष्ठा nicvf *nic,
					   u64 rb_ptr, पूर्णांक len)
अणु
	व्योम *data;
	काष्ठा sk_buff *skb;

	data = phys_to_virt(rb_ptr);

	/* Now build an skb to give to stack */
	skb = build_skb(data, RCV_FRAG_LEN);
	अगर (!skb) अणु
		put_page(virt_to_page(data));
		वापस शून्य;
	पूर्ण

	prefetch(skb->data);
	वापस skb;
पूर्ण

/* Allocate RBDR ring and populate receive buffers */
अटल पूर्णांक  nicvf_init_rbdr(काष्ठा nicvf *nic, काष्ठा rbdr *rbdr,
			    पूर्णांक ring_len, पूर्णांक buf_size)
अणु
	पूर्णांक idx;
	u64 rbuf;
	काष्ठा rbdr_entry_t *desc;
	पूर्णांक err;

	err = nicvf_alloc_q_desc_mem(nic, &rbdr->dmem, ring_len,
				     माप(काष्ठा rbdr_entry_t),
				     NICVF_RCV_BUF_ALIGN_BYTES);
	अगर (err)
		वापस err;

	rbdr->desc = rbdr->dmem.base;
	/* Buffer size has to be in multiples of 128 bytes */
	rbdr->dma_size = buf_size;
	rbdr->enable = true;
	rbdr->thresh = RBDR_THRESH;
	rbdr->head = 0;
	rbdr->tail = 0;

	/* Initialize page recycling stuff.
	 *
	 * Can't use single buffer per page especially with 64K pages.
	 * On embedded platक्रमms i.e 81xx/83xx available memory itself
	 * is low and minimum ring size of RBDR is 8K, that takes away
	 * lots of memory.
	 *
	 * But क्रम XDP it has to be a single buffer per page.
	 */
	अगर (!nic->pnicvf->xdp_prog) अणु
		rbdr->pgcnt = ring_len / (PAGE_SIZE / buf_size);
		rbdr->is_xdp = false;
	पूर्ण अन्यथा अणु
		rbdr->pgcnt = ring_len;
		rbdr->is_xdp = true;
	पूर्ण
	rbdr->pgcnt = roundup_घात_of_two(rbdr->pgcnt);
	rbdr->pgcache = kसुस्मृति(rbdr->pgcnt, माप(*rbdr->pgcache),
				GFP_KERNEL);
	अगर (!rbdr->pgcache)
		वापस -ENOMEM;
	rbdr->pgidx = 0;
	rbdr->pgalloc = 0;

	nic->rb_page = शून्य;
	क्रम (idx = 0; idx < ring_len; idx++) अणु
		err = nicvf_alloc_rcv_buffer(nic, rbdr, GFP_KERNEL,
					     RCV_FRAG_LEN, &rbuf);
		अगर (err) अणु
			/* To मुक्त alपढ़ोy allocated and mapped ones */
			rbdr->tail = idx - 1;
			वापस err;
		पूर्ण

		desc = GET_RBDR_DESC(rbdr, idx);
		desc->buf_addr = rbuf & ~(NICVF_RCV_BUF_ALIGN_BYTES - 1);
	पूर्ण

	nicvf_get_page(nic);

	वापस 0;
पूर्ण

/* Free RBDR ring and its receive buffers */
अटल व्योम nicvf_मुक्त_rbdr(काष्ठा nicvf *nic, काष्ठा rbdr *rbdr)
अणु
	पूर्णांक head, tail;
	u64 buf_addr, phys_addr;
	काष्ठा pgcache *pgcache;
	काष्ठा rbdr_entry_t *desc;

	अगर (!rbdr)
		वापस;

	rbdr->enable = false;
	अगर (!rbdr->dmem.base)
		वापस;

	head = rbdr->head;
	tail = rbdr->tail;

	/* Release page references */
	जबतक (head != tail) अणु
		desc = GET_RBDR_DESC(rbdr, head);
		buf_addr = desc->buf_addr;
		phys_addr = nicvf_iova_to_phys(nic, buf_addr);
		dma_unmap_page_attrs(&nic->pdev->dev, buf_addr, RCV_FRAG_LEN,
				     DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
		अगर (phys_addr)
			put_page(virt_to_page(phys_to_virt(phys_addr)));
		head++;
		head &= (rbdr->dmem.q_len - 1);
	पूर्ण
	/* Release buffer of tail desc */
	desc = GET_RBDR_DESC(rbdr, tail);
	buf_addr = desc->buf_addr;
	phys_addr = nicvf_iova_to_phys(nic, buf_addr);
	dma_unmap_page_attrs(&nic->pdev->dev, buf_addr, RCV_FRAG_LEN,
			     DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (phys_addr)
		put_page(virt_to_page(phys_to_virt(phys_addr)));

	/* Sync page cache info */
	smp_rmb();

	/* Release additional page references held क्रम recycling */
	head = 0;
	जबतक (head < rbdr->pgcnt) अणु
		pgcache = &rbdr->pgcache[head];
		अगर (pgcache->page && page_ref_count(pgcache->page) != 0) अणु
			अगर (rbdr->is_xdp) अणु
				page_ref_sub(pgcache->page,
					     pgcache->ref_count - 1);
			पूर्ण
			put_page(pgcache->page);
		पूर्ण
		head++;
	पूर्ण

	/* Free RBDR ring */
	nicvf_मुक्त_q_desc_mem(nic, &rbdr->dmem);
पूर्ण

/* Refill receive buffer descriptors with new buffers.
 */
अटल व्योम nicvf_refill_rbdr(काष्ठा nicvf *nic, gfp_t gfp)
अणु
	काष्ठा queue_set *qs = nic->qs;
	पूर्णांक rbdr_idx = qs->rbdr_cnt;
	पूर्णांक tail, qcount;
	पूर्णांक refill_rb_cnt;
	काष्ठा rbdr *rbdr;
	काष्ठा rbdr_entry_t *desc;
	u64 rbuf;
	पूर्णांक new_rb = 0;

refill:
	अगर (!rbdr_idx)
		वापस;
	rbdr_idx--;
	rbdr = &qs->rbdr[rbdr_idx];
	/* Check अगर it's enabled */
	अगर (!rbdr->enable)
		जाओ next_rbdr;

	/* Get no of desc's to be refilled */
	qcount = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_STATUS0, rbdr_idx);
	qcount &= 0x7FFFF;
	/* Doorbell can be ringed with a max of ring size minus 1 */
	अगर (qcount >= (qs->rbdr_len - 1))
		जाओ next_rbdr;
	अन्यथा
		refill_rb_cnt = qs->rbdr_len - qcount - 1;

	/* Sync page cache info */
	smp_rmb();

	/* Start filling descs from tail */
	tail = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_TAIL, rbdr_idx) >> 3;
	जबतक (refill_rb_cnt) अणु
		tail++;
		tail &= (rbdr->dmem.q_len - 1);

		अगर (nicvf_alloc_rcv_buffer(nic, rbdr, gfp, RCV_FRAG_LEN, &rbuf))
			अवरोध;

		desc = GET_RBDR_DESC(rbdr, tail);
		desc->buf_addr = rbuf & ~(NICVF_RCV_BUF_ALIGN_BYTES - 1);
		refill_rb_cnt--;
		new_rb++;
	पूर्ण

	nicvf_get_page(nic);

	/* make sure all memory stores are करोne beक्रमe ringing करोorbell */
	smp_wmb();

	/* Check अगर buffer allocation failed */
	अगर (refill_rb_cnt)
		nic->rb_alloc_fail = true;
	अन्यथा
		nic->rb_alloc_fail = false;

	/* Notअगरy HW */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_DOOR,
			      rbdr_idx, new_rb);
next_rbdr:
	/* Re-enable RBDR पूर्णांकerrupts only अगर buffer allocation is success */
	अगर (!nic->rb_alloc_fail && rbdr->enable &&
	    netअगर_running(nic->pnicvf->netdev))
		nicvf_enable_पूर्णांकr(nic, NICVF_INTR_RBDR, rbdr_idx);

	अगर (rbdr_idx)
		जाओ refill;
पूर्ण

/* Alloc rcv buffers in non-atomic mode क्रम better success */
व्योम nicvf_rbdr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nicvf *nic = container_of(work, काष्ठा nicvf, rbdr_work.work);

	nicvf_refill_rbdr(nic, GFP_KERNEL);
	अगर (nic->rb_alloc_fail)
		schedule_delayed_work(&nic->rbdr_work, msecs_to_jअगरfies(10));
	अन्यथा
		nic->rb_work_scheduled = false;
पूर्ण

/* In Softirq context, alloc rcv buffers in atomic mode */
व्योम nicvf_rbdr_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा nicvf *nic = from_tasklet(nic, t, rbdr_task);

	nicvf_refill_rbdr(nic, GFP_ATOMIC);
	अगर (nic->rb_alloc_fail) अणु
		nic->rb_work_scheduled = true;
		schedule_delayed_work(&nic->rbdr_work, msecs_to_jअगरfies(10));
	पूर्ण
पूर्ण

/* Initialize completion queue */
अटल पूर्णांक nicvf_init_cmp_queue(काष्ठा nicvf *nic,
				काष्ठा cmp_queue *cq, पूर्णांक q_len)
अणु
	पूर्णांक err;

	err = nicvf_alloc_q_desc_mem(nic, &cq->dmem, q_len, CMP_QUEUE_DESC_SIZE,
				     NICVF_CQ_BASE_ALIGN_BYTES);
	अगर (err)
		वापस err;

	cq->desc = cq->dmem.base;
	cq->thresh = pass1_silicon(nic->pdev) ? 0 : CMP_QUEUE_CQE_THRESH;
	nic->cq_coalesce_usecs = (CMP_QUEUE_TIMER_THRESH * 0.05) - 1;

	वापस 0;
पूर्ण

अटल व्योम nicvf_मुक्त_cmp_queue(काष्ठा nicvf *nic, काष्ठा cmp_queue *cq)
अणु
	अगर (!cq)
		वापस;
	अगर (!cq->dmem.base)
		वापस;

	nicvf_मुक्त_q_desc_mem(nic, &cq->dmem);
पूर्ण

/* Initialize transmit queue */
अटल पूर्णांक nicvf_init_snd_queue(काष्ठा nicvf *nic,
				काष्ठा snd_queue *sq, पूर्णांक q_len, पूर्णांक qidx)
अणु
	पूर्णांक err;

	err = nicvf_alloc_q_desc_mem(nic, &sq->dmem, q_len, SND_QUEUE_DESC_SIZE,
				     NICVF_SQ_BASE_ALIGN_BYTES);
	अगर (err)
		वापस err;

	sq->desc = sq->dmem.base;
	sq->skbuff = kसुस्मृति(q_len, माप(u64), GFP_KERNEL);
	अगर (!sq->skbuff)
		वापस -ENOMEM;

	sq->head = 0;
	sq->tail = 0;
	sq->thresh = SND_QUEUE_THRESH;

	/* Check अगर this SQ is a XDP TX queue */
	अगर (nic->sqs_mode)
		qidx += ((nic->sqs_id + 1) * MAX_SND_QUEUES_PER_QS);
	अगर (qidx < nic->pnicvf->xdp_tx_queues) अणु
		/* Alloc memory to save page poपूर्णांकers क्रम XDP_TX */
		sq->xdp_page = kसुस्मृति(q_len, माप(u64), GFP_KERNEL);
		अगर (!sq->xdp_page)
			वापस -ENOMEM;
		sq->xdp_desc_cnt = 0;
		sq->xdp_मुक्त_cnt = q_len - 1;
		sq->is_xdp = true;
	पूर्ण अन्यथा अणु
		sq->xdp_page = शून्य;
		sq->xdp_desc_cnt = 0;
		sq->xdp_मुक्त_cnt = 0;
		sq->is_xdp = false;

		atomic_set(&sq->मुक्त_cnt, q_len - 1);

		/* Pपुनः_स्मृतिate memory क्रम TSO segment's header */
		sq->tso_hdrs = dma_alloc_coherent(&nic->pdev->dev,
						  q_len * TSO_HEADER_SIZE,
						  &sq->tso_hdrs_phys,
						  GFP_KERNEL);
		अगर (!sq->tso_hdrs)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nicvf_unmap_sndq_buffers(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			      पूर्णांक hdr_sqe, u8 subdesc_cnt)
अणु
	u8 idx;
	काष्ठा sq_gather_subdesc *gather;

	/* Unmap DMA mapped skb data buffers */
	क्रम (idx = 0; idx < subdesc_cnt; idx++) अणु
		hdr_sqe++;
		hdr_sqe &= (sq->dmem.q_len - 1);
		gather = (काष्ठा sq_gather_subdesc *)GET_SQ_DESC(sq, hdr_sqe);
		/* HW will ensure data coherency, CPU sync not required */
		dma_unmap_page_attrs(&nic->pdev->dev, gather->addr,
				     gather->size, DMA_TO_DEVICE,
				     DMA_ATTR_SKIP_CPU_SYNC);
	पूर्ण
पूर्ण

अटल व्योम nicvf_मुक्त_snd_queue(काष्ठा nicvf *nic, काष्ठा snd_queue *sq)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	काष्ठा sq_hdr_subdesc *hdr;
	काष्ठा sq_hdr_subdesc *tso_sqe;

	अगर (!sq)
		वापस;
	अगर (!sq->dmem.base)
		वापस;

	अगर (sq->tso_hdrs) अणु
		dma_मुक्त_coherent(&nic->pdev->dev,
				  sq->dmem.q_len * TSO_HEADER_SIZE,
				  sq->tso_hdrs, sq->tso_hdrs_phys);
		sq->tso_hdrs = शून्य;
	पूर्ण

	/* Free pending skbs in the queue */
	smp_rmb();
	जबतक (sq->head != sq->tail) अणु
		skb = (काष्ठा sk_buff *)sq->skbuff[sq->head];
		अगर (!skb || !sq->xdp_page)
			जाओ next;

		page = (काष्ठा page *)sq->xdp_page[sq->head];
		अगर (!page)
			जाओ next;
		अन्यथा
			put_page(page);

		hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, sq->head);
		/* Check क्रम dummy descriptor used क्रम HW TSO offload on 88xx */
		अगर (hdr->करोnt_send) अणु
			/* Get actual TSO descriptors and unmap them */
			tso_sqe =
			 (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, hdr->rsvd2);
			nicvf_unmap_sndq_buffers(nic, sq, hdr->rsvd2,
						 tso_sqe->subdesc_cnt);
		पूर्ण अन्यथा अणु
			nicvf_unmap_sndq_buffers(nic, sq, sq->head,
						 hdr->subdesc_cnt);
		पूर्ण
		अगर (skb)
			dev_kमुक्त_skb_any(skb);
next:
		sq->head++;
		sq->head &= (sq->dmem.q_len - 1);
	पूर्ण
	kमुक्त(sq->skbuff);
	kमुक्त(sq->xdp_page);
	nicvf_मुक्त_q_desc_mem(nic, &sq->dmem);
पूर्ण

अटल व्योम nicvf_reclaim_snd_queue(काष्ठा nicvf *nic,
				    काष्ठा queue_set *qs, पूर्णांक qidx)
अणु
	/* Disable send queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, 0);
	/* Check अगर SQ is stopped */
	अगर (nicvf_poll_reg(nic, qidx, NIC_QSET_SQ_0_7_STATUS, 21, 1, 0x01))
		वापस;
	/* Reset send queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, NICVF_SQ_RESET);
पूर्ण

अटल व्योम nicvf_reclaim_rcv_queue(काष्ठा nicvf *nic,
				    काष्ठा queue_set *qs, पूर्णांक qidx)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	/* Make sure all packets in the pipeline are written back पूर्णांकo mem */
	mbx.msg.msg = NIC_MBOX_MSG_RQ_SW_SYNC;
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_reclaim_cmp_queue(काष्ठा nicvf *nic,
				    काष्ठा queue_set *qs, पूर्णांक qidx)
अणु
	/* Disable समयr threshold (करोesn't get reset upon CQ reset */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG2, qidx, 0);
	/* Disable completion queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG, qidx, 0);
	/* Reset completion queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG, qidx, NICVF_CQ_RESET);
पूर्ण

अटल व्योम nicvf_reclaim_rbdr(काष्ठा nicvf *nic,
			       काष्ठा rbdr *rbdr, पूर्णांक qidx)
अणु
	u64 पंचांगp, fअगरo_state;
	पूर्णांक समयout = 10;

	/* Save head and tail poपूर्णांकers क्रम feeing up buffers */
	rbdr->head = nicvf_queue_reg_पढ़ो(nic,
					  NIC_QSET_RBDR_0_1_HEAD,
					  qidx) >> 3;
	rbdr->tail = nicvf_queue_reg_पढ़ो(nic,
					  NIC_QSET_RBDR_0_1_TAIL,
					  qidx) >> 3;

	/* If RBDR FIFO is in 'FAIL' state then करो a reset first
	 * beक्रमe relaiming.
	 */
	fअगरo_state = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_STATUS0, qidx);
	अगर (((fअगरo_state >> 62) & 0x03) == 0x3)
		nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_CFG,
				      qidx, NICVF_RBDR_RESET);

	/* Disable RBDR */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_CFG, qidx, 0);
	अगर (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x00))
		वापस;
	जबतक (1) अणु
		पंचांगp = nicvf_queue_reg_पढ़ो(nic,
					   NIC_QSET_RBDR_0_1_PREFETCH_STATUS,
					   qidx);
		अगर ((पंचांगp & 0xFFFFFFFF) == ((पंचांगp >> 32) & 0xFFFFFFFF))
			अवरोध;
		usleep_range(1000, 2000);
		समयout--;
		अगर (!समयout) अणु
			netdev_err(nic->netdev,
				   "Failed polling on prefetch status\n");
			वापस;
		पूर्ण
	पूर्ण
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_CFG,
			      qidx, NICVF_RBDR_RESET);

	अगर (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x02))
		वापस;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_CFG, qidx, 0x00);
	अगर (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x00))
		वापस;
पूर्ण

व्योम nicvf_config_vlan_stripping(काष्ठा nicvf *nic, netdev_features_t features)
अणु
	u64 rq_cfg;
	पूर्णांक sqs;

	rq_cfg = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RQ_GEN_CFG, 0);

	/* Enable first VLAN stripping */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		rq_cfg |= (1ULL << 25);
	अन्यथा
		rq_cfg &= ~(1ULL << 25);
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RQ_GEN_CFG, 0, rq_cfg);

	/* Configure Secondary Qsets, अगर any */
	क्रम (sqs = 0; sqs < nic->sqs_count; sqs++)
		अगर (nic->snicvf[sqs])
			nicvf_queue_reg_ग_लिखो(nic->snicvf[sqs],
					      NIC_QSET_RQ_GEN_CFG, 0, rq_cfg);
पूर्ण

अटल व्योम nicvf_reset_rcv_queue_stats(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	/* Reset all RQ/SQ and VF stats */
	mbx.reset_stat.msg = NIC_MBOX_MSG_RESET_STAT_COUNTER;
	mbx.reset_stat.rx_stat_mask = 0x3FFF;
	mbx.reset_stat.tx_stat_mask = 0x1F;
	mbx.reset_stat.rq_stat_mask = 0xFFFF;
	mbx.reset_stat.sq_stat_mask = 0xFFFF;
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

/* Configures receive queue */
अटल व्योम nicvf_rcv_queue_config(काष्ठा nicvf *nic, काष्ठा queue_set *qs,
				   पूर्णांक qidx, bool enable)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	काष्ठा rcv_queue *rq;
	काष्ठा rq_cfg rq_cfg;

	rq = &qs->rq[qidx];
	rq->enable = enable;

	/* Disable receive queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RQ_0_7_CFG, qidx, 0);

	अगर (!rq->enable) अणु
		nicvf_reclaim_rcv_queue(nic, qs, qidx);
		xdp_rxq_info_unreg(&rq->xdp_rxq);
		वापस;
	पूर्ण

	rq->cq_qs = qs->vnic_id;
	rq->cq_idx = qidx;
	rq->start_rbdr_qs = qs->vnic_id;
	rq->start_qs_rbdr_idx = qs->rbdr_cnt - 1;
	rq->cont_rbdr_qs = qs->vnic_id;
	rq->cont_qs_rbdr_idx = qs->rbdr_cnt - 1;
	/* all ग_लिखोs of RBDR data to be loaded पूर्णांकo L2 Cache as well*/
	rq->caching = 1;

	/* Driver have no proper error path क्रम failed XDP RX-queue info reg */
	WARN_ON(xdp_rxq_info_reg(&rq->xdp_rxq, nic->netdev, qidx, 0) < 0);

	/* Send a mailbox msg to PF to config RQ */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_CFG;
	mbx.rq.qs_num = qs->vnic_id;
	mbx.rq.rq_num = qidx;
	mbx.rq.cfg = ((u64)rq->caching << 26) | (rq->cq_qs << 19) |
			  (rq->cq_idx << 16) | (rq->cont_rbdr_qs << 9) |
			  (rq->cont_qs_rbdr_idx << 8) |
			  (rq->start_rbdr_qs << 1) | (rq->start_qs_rbdr_idx);
	nicvf_send_msg_to_pf(nic, &mbx);

	mbx.rq.msg = NIC_MBOX_MSG_RQ_BP_CFG;
	mbx.rq.cfg = BIT_ULL(63) | BIT_ULL(62) |
		     (RQ_PASS_RBDR_LVL << 16) | (RQ_PASS_CQ_LVL << 8) |
		     (qs->vnic_id << 0);
	nicvf_send_msg_to_pf(nic, &mbx);

	/* RQ drop config
	 * Enable CQ drop to reserve sufficient CQEs क्रम all tx packets
	 */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_DROP_CFG;
	mbx.rq.cfg = BIT_ULL(63) | BIT_ULL(62) |
		     (RQ_PASS_RBDR_LVL << 40) | (RQ_DROP_RBDR_LVL << 32) |
		     (RQ_PASS_CQ_LVL << 16) | (RQ_DROP_CQ_LVL << 8);
	nicvf_send_msg_to_pf(nic, &mbx);

	अगर (!nic->sqs_mode && (qidx == 0)) अणु
		/* Enable checking L3/L4 length and TCP/UDP checksums
		 * Also allow IPv6 pkts with zero UDP checksum.
		 */
		nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RQ_GEN_CFG, 0,
				      (BIT(24) | BIT(23) | BIT(21) | BIT(20)));
		nicvf_config_vlan_stripping(nic, nic->netdev->features);
	पूर्ण

	/* Enable Receive queue */
	स_रखो(&rq_cfg, 0, माप(काष्ठा rq_cfg));
	rq_cfg.ena = 1;
	rq_cfg.tcp_ena = 0;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RQ_0_7_CFG, qidx, *(u64 *)&rq_cfg);
पूर्ण

/* Configures completion queue */
व्योम nicvf_cmp_queue_config(काष्ठा nicvf *nic, काष्ठा queue_set *qs,
			    पूर्णांक qidx, bool enable)
अणु
	काष्ठा cmp_queue *cq;
	काष्ठा cq_cfg cq_cfg;

	cq = &qs->cq[qidx];
	cq->enable = enable;

	अगर (!cq->enable) अणु
		nicvf_reclaim_cmp_queue(nic, qs, qidx);
		वापस;
	पूर्ण

	/* Reset completion queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG, qidx, NICVF_CQ_RESET);

	अगर (!cq->enable)
		वापस;

	spin_lock_init(&cq->lock);
	/* Set completion queue base address */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_BASE,
			      qidx, (u64)(cq->dmem.phys_base));

	/* Enable Completion queue */
	स_रखो(&cq_cfg, 0, माप(काष्ठा cq_cfg));
	cq_cfg.ena = 1;
	cq_cfg.reset = 0;
	cq_cfg.caching = 0;
	cq_cfg.qsize = ilog2(qs->cq_len >> 10);
	cq_cfg.avg_con = 0;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG, qidx, *(u64 *)&cq_cfg);

	/* Set threshold value क्रम पूर्णांकerrupt generation */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_THRESH, qidx, cq->thresh);
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_CFG2,
			      qidx, CMP_QUEUE_TIMER_THRESH);
पूर्ण

/* Configures transmit queue */
अटल व्योम nicvf_snd_queue_config(काष्ठा nicvf *nic, काष्ठा queue_set *qs,
				   पूर्णांक qidx, bool enable)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	काष्ठा snd_queue *sq;
	काष्ठा sq_cfg sq_cfg;

	sq = &qs->sq[qidx];
	sq->enable = enable;

	अगर (!sq->enable) अणु
		nicvf_reclaim_snd_queue(nic, qs, qidx);
		वापस;
	पूर्ण

	/* Reset send queue */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, NICVF_SQ_RESET);

	sq->cq_qs = qs->vnic_id;
	sq->cq_idx = qidx;

	/* Send a mailbox msg to PF to config SQ */
	mbx.sq.msg = NIC_MBOX_MSG_SQ_CFG;
	mbx.sq.qs_num = qs->vnic_id;
	mbx.sq.sq_num = qidx;
	mbx.sq.sqs_mode = nic->sqs_mode;
	mbx.sq.cfg = (sq->cq_qs << 3) | sq->cq_idx;
	nicvf_send_msg_to_pf(nic, &mbx);

	/* Set queue base address */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_BASE,
			      qidx, (u64)(sq->dmem.phys_base));

	/* Enable send queue  & set queue size */
	स_रखो(&sq_cfg, 0, माप(काष्ठा sq_cfg));
	sq_cfg.ena = 1;
	sq_cfg.reset = 0;
	sq_cfg.ldwb = 0;
	sq_cfg.qsize = ilog2(qs->sq_len >> 10);
	sq_cfg.tsपंचांगp_bgx_पूर्णांकf = 0;
	/* CQ's level at which HW will stop processing SQEs to aव्योम
	 * transmitting a pkt with no space in CQ to post CQE_TX.
	 */
	sq_cfg.cq_limit = (CMP_QUEUE_PIPELINE_RSVD * 256) / qs->cq_len;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, *(u64 *)&sq_cfg);

	/* Set threshold value क्रम पूर्णांकerrupt generation */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_THRESH, qidx, sq->thresh);

	/* Set queue:cpu affinity क्रम better load distribution */
	अगर (cpu_online(qidx)) अणु
		cpumask_set_cpu(qidx, &sq->affinity_mask);
		netअगर_set_xps_queue(nic->netdev,
				    &sq->affinity_mask, qidx);
	पूर्ण
पूर्ण

/* Configures receive buffer descriptor ring */
अटल व्योम nicvf_rbdr_config(काष्ठा nicvf *nic, काष्ठा queue_set *qs,
			      पूर्णांक qidx, bool enable)
अणु
	काष्ठा rbdr *rbdr;
	काष्ठा rbdr_cfg rbdr_cfg;

	rbdr = &qs->rbdr[qidx];
	nicvf_reclaim_rbdr(nic, rbdr, qidx);
	अगर (!enable)
		वापस;

	/* Set descriptor base address */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_BASE,
			      qidx, (u64)(rbdr->dmem.phys_base));

	/* Enable RBDR  & set queue size */
	/* Buffer size should be in multiples of 128 bytes */
	स_रखो(&rbdr_cfg, 0, माप(काष्ठा rbdr_cfg));
	rbdr_cfg.ena = 1;
	rbdr_cfg.reset = 0;
	rbdr_cfg.ldwb = 0;
	rbdr_cfg.qsize = RBDR_SIZE;
	rbdr_cfg.avg_con = 0;
	rbdr_cfg.lines = rbdr->dma_size / 128;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_CFG,
			      qidx, *(u64 *)&rbdr_cfg);

	/* Notअगरy HW */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_DOOR,
			      qidx, qs->rbdr_len - 1);

	/* Set threshold value क्रम पूर्णांकerrupt generation */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_RBDR_0_1_THRESH,
			      qidx, rbdr->thresh - 1);
पूर्ण

/* Requests PF to assign and enable Qset */
व्योम nicvf_qset_config(काष्ठा nicvf *nic, bool enable)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	काष्ठा queue_set *qs = nic->qs;
	काष्ठा qs_cfg *qs_cfg;

	अगर (!qs) अणु
		netdev_warn(nic->netdev,
			    "Qset is still not allocated, don't init queues\n");
		वापस;
	पूर्ण

	qs->enable = enable;
	qs->vnic_id = nic->vf_id;

	/* Send a mailbox msg to PF to config Qset */
	mbx.qs.msg = NIC_MBOX_MSG_QS_CFG;
	mbx.qs.num = qs->vnic_id;
	mbx.qs.sqs_count = nic->sqs_count;

	mbx.qs.cfg = 0;
	qs_cfg = (काष्ठा qs_cfg *)&mbx.qs.cfg;
	अगर (qs->enable) अणु
		qs_cfg->ena = 1;
#अगर_घोषित __BIG_ENDIAN
		qs_cfg->be = 1;
#पूर्ण_अगर
		qs_cfg->vnic = qs->vnic_id;
		/* Enable Tx बारtamping capability */
		अगर (nic->ptp_घड़ी)
			qs_cfg->send_tsपंचांगp_ena = 1;
	पूर्ण
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_मुक्त_resources(काष्ठा nicvf *nic)
अणु
	पूर्णांक qidx;
	काष्ठा queue_set *qs = nic->qs;

	/* Free receive buffer descriptor ring */
	क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
		nicvf_मुक्त_rbdr(nic, &qs->rbdr[qidx]);

	/* Free completion queue */
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++)
		nicvf_मुक्त_cmp_queue(nic, &qs->cq[qidx]);

	/* Free send queue */
	क्रम (qidx = 0; qidx < qs->sq_cnt; qidx++)
		nicvf_मुक्त_snd_queue(nic, &qs->sq[qidx]);
पूर्ण

अटल पूर्णांक nicvf_alloc_resources(काष्ठा nicvf *nic)
अणु
	पूर्णांक qidx;
	काष्ठा queue_set *qs = nic->qs;

	/* Alloc receive buffer descriptor ring */
	क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++) अणु
		अगर (nicvf_init_rbdr(nic, &qs->rbdr[qidx], qs->rbdr_len,
				    DMA_BUFFER_LEN))
			जाओ alloc_fail;
	पूर्ण

	/* Alloc send queue */
	क्रम (qidx = 0; qidx < qs->sq_cnt; qidx++) अणु
		अगर (nicvf_init_snd_queue(nic, &qs->sq[qidx], qs->sq_len, qidx))
			जाओ alloc_fail;
	पूर्ण

	/* Alloc completion queue */
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++) अणु
		अगर (nicvf_init_cmp_queue(nic, &qs->cq[qidx], qs->cq_len))
			जाओ alloc_fail;
	पूर्ण

	वापस 0;
alloc_fail:
	nicvf_मुक्त_resources(nic);
	वापस -ENOMEM;
पूर्ण

पूर्णांक nicvf_set_qset_resources(काष्ठा nicvf *nic)
अणु
	काष्ठा queue_set *qs;

	qs = devm_kzalloc(&nic->pdev->dev, माप(*qs), GFP_KERNEL);
	अगर (!qs)
		वापस -ENOMEM;
	nic->qs = qs;

	/* Set count of each queue */
	qs->rbdr_cnt = DEFAULT_RBDR_CNT;
	qs->rq_cnt = min_t(u8, MAX_RCV_QUEUES_PER_QS, num_online_cpus());
	qs->sq_cnt = min_t(u8, MAX_SND_QUEUES_PER_QS, num_online_cpus());
	qs->cq_cnt = max_t(u8, qs->rq_cnt, qs->sq_cnt);

	/* Set queue lengths */
	qs->rbdr_len = RCV_BUF_COUNT;
	qs->sq_len = SND_QUEUE_LEN;
	qs->cq_len = CMP_QUEUE_LEN;

	nic->rx_queues = qs->rq_cnt;
	nic->tx_queues = qs->sq_cnt;
	nic->xdp_tx_queues = 0;

	वापस 0;
पूर्ण

पूर्णांक nicvf_config_data_transfer(काष्ठा nicvf *nic, bool enable)
अणु
	bool disable = false;
	काष्ठा queue_set *qs = nic->qs;
	काष्ठा queue_set *pqs = nic->pnicvf->qs;
	पूर्णांक qidx;

	अगर (!qs)
		वापस 0;

	/* Take primary VF's queue lengths.
	 * This is needed to take queue lengths set from ethtool
	 * पूर्णांकo consideration.
	 */
	अगर (nic->sqs_mode && pqs) अणु
		qs->cq_len = pqs->cq_len;
		qs->sq_len = pqs->sq_len;
	पूर्ण

	अगर (enable) अणु
		अगर (nicvf_alloc_resources(nic))
			वापस -ENOMEM;

		क्रम (qidx = 0; qidx < qs->sq_cnt; qidx++)
			nicvf_snd_queue_config(nic, qs, qidx, enable);
		क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++)
			nicvf_cmp_queue_config(nic, qs, qidx, enable);
		क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
			nicvf_rbdr_config(nic, qs, qidx, enable);
		क्रम (qidx = 0; qidx < qs->rq_cnt; qidx++)
			nicvf_rcv_queue_config(nic, qs, qidx, enable);
	पूर्ण अन्यथा अणु
		क्रम (qidx = 0; qidx < qs->rq_cnt; qidx++)
			nicvf_rcv_queue_config(nic, qs, qidx, disable);
		क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
			nicvf_rbdr_config(nic, qs, qidx, disable);
		क्रम (qidx = 0; qidx < qs->sq_cnt; qidx++)
			nicvf_snd_queue_config(nic, qs, qidx, disable);
		क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++)
			nicvf_cmp_queue_config(nic, qs, qidx, disable);

		nicvf_मुक्त_resources(nic);
	पूर्ण

	/* Reset RXQ's stats.
	 * SQ's stats will get reset स्वतःmatically once SQ is reset.
	 */
	nicvf_reset_rcv_queue_stats(nic);

	वापस 0;
पूर्ण

/* Get a मुक्त desc from SQ
 * वापसs descriptor ponter & descriptor number
 */
अटल अंतरभूत पूर्णांक nicvf_get_sq_desc(काष्ठा snd_queue *sq, पूर्णांक desc_cnt)
अणु
	पूर्णांक qentry;

	qentry = sq->tail;
	अगर (!sq->is_xdp)
		atomic_sub(desc_cnt, &sq->मुक्त_cnt);
	अन्यथा
		sq->xdp_मुक्त_cnt -= desc_cnt;
	sq->tail += desc_cnt;
	sq->tail &= (sq->dmem.q_len - 1);

	वापस qentry;
पूर्ण

/* Rollback to previous tail poपूर्णांकer when descriptors not used */
अटल अंतरभूत व्योम nicvf_rollback_sq_desc(काष्ठा snd_queue *sq,
					  पूर्णांक qentry, पूर्णांक desc_cnt)
अणु
	sq->tail = qentry;
	atomic_add(desc_cnt, &sq->मुक्त_cnt);
पूर्ण

/* Free descriptor back to SQ क्रम future use */
व्योम nicvf_put_sq_desc(काष्ठा snd_queue *sq, पूर्णांक desc_cnt)
अणु
	अगर (!sq->is_xdp)
		atomic_add(desc_cnt, &sq->मुक्त_cnt);
	अन्यथा
		sq->xdp_मुक्त_cnt += desc_cnt;
	sq->head += desc_cnt;
	sq->head &= (sq->dmem.q_len - 1);
पूर्ण

अटल अंतरभूत पूर्णांक nicvf_get_nxt_sqentry(काष्ठा snd_queue *sq, पूर्णांक qentry)
अणु
	qentry++;
	qentry &= (sq->dmem.q_len - 1);
	वापस qentry;
पूर्ण

व्योम nicvf_sq_enable(काष्ठा nicvf *nic, काष्ठा snd_queue *sq, पूर्णांक qidx)
अणु
	u64 sq_cfg;

	sq_cfg = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_CFG, qidx);
	sq_cfg |= NICVF_SQ_EN;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, sq_cfg);
	/* Ring करोorbell so that H/W restarts processing SQEs */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_DOOR, qidx, 0);
पूर्ण

व्योम nicvf_sq_disable(काष्ठा nicvf *nic, पूर्णांक qidx)
अणु
	u64 sq_cfg;

	sq_cfg = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_CFG, qidx);
	sq_cfg &= ~NICVF_SQ_EN;
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_CFG, qidx, sq_cfg);
पूर्ण

व्योम nicvf_sq_मुक्त_used_descs(काष्ठा net_device *netdev, काष्ठा snd_queue *sq,
			      पूर्णांक qidx)
अणु
	u64 head;
	काष्ठा sk_buff *skb;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा sq_hdr_subdesc *hdr;

	head = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_HEAD, qidx) >> 4;
	जबतक (sq->head != head) अणु
		hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, sq->head);
		अगर (hdr->subdesc_type != SQ_DESC_TYPE_HEADER) अणु
			nicvf_put_sq_desc(sq, 1);
			जारी;
		पूर्ण
		skb = (काष्ठा sk_buff *)sq->skbuff[sq->head];
		अगर (skb)
			dev_kमुक्त_skb_any(skb);
		atomic64_add(1, (atomic64_t *)&netdev->stats.tx_packets);
		atomic64_add(hdr->tot_len,
			     (atomic64_t *)&netdev->stats.tx_bytes);
		nicvf_put_sq_desc(sq, hdr->subdesc_cnt + 1);
	पूर्ण
पूर्ण

/* XDP Transmit APIs */
व्योम nicvf_xdp_sq_करोorbell(काष्ठा nicvf *nic,
			   काष्ठा snd_queue *sq, पूर्णांक sq_num)
अणु
	अगर (!sq->xdp_desc_cnt)
		वापस;

	/* make sure all memory stores are करोne beक्रमe ringing करोorbell */
	wmb();

	/* Inक्रमm HW to xmit all TSO segments */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_DOOR,
			      sq_num, sq->xdp_desc_cnt);
	sq->xdp_desc_cnt = 0;
पूर्ण

अटल अंतरभूत व्योम
nicvf_xdp_sq_add_hdr_subdesc(काष्ठा snd_queue *sq, पूर्णांक qentry,
			     पूर्णांक subdesc_cnt, u64 data, पूर्णांक len)
अणु
	काष्ठा sq_hdr_subdesc *hdr;

	hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, qentry);
	स_रखो(hdr, 0, SND_QUEUE_DESC_SIZE);
	hdr->subdesc_type = SQ_DESC_TYPE_HEADER;
	hdr->subdesc_cnt = subdesc_cnt;
	hdr->tot_len = len;
	hdr->post_cqe = 1;
	sq->xdp_page[qentry] = (u64)virt_to_page((व्योम *)data);
पूर्ण

पूर्णांक nicvf_xdp_sq_append_pkt(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			    u64 bufaddr, u64 dma_addr, u16 len)
अणु
	पूर्णांक subdesc_cnt = MIN_SQ_DESC_PER_PKT_XMIT;
	पूर्णांक qentry;

	अगर (subdesc_cnt > sq->xdp_मुक्त_cnt)
		वापस 0;

	qentry = nicvf_get_sq_desc(sq, subdesc_cnt);

	nicvf_xdp_sq_add_hdr_subdesc(sq, qentry, subdesc_cnt - 1, bufaddr, len);

	qentry = nicvf_get_nxt_sqentry(sq, qentry);
	nicvf_sq_add_gather_subdesc(sq, qentry, len, dma_addr);

	sq->xdp_desc_cnt += subdesc_cnt;

	वापस 1;
पूर्ण

/* Calculate no of SQ subdescriptors needed to transmit all
 * segments of this TSO packet.
 * Taken from 'Tilera network driver' with a minor modअगरication.
 */
अटल पूर्णांक nicvf_tso_count_subdescs(काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *sh = skb_shinfo(skb);
	अचिन्हित पूर्णांक sh_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	अचिन्हित पूर्णांक data_len = skb->len - sh_len;
	अचिन्हित पूर्णांक p_len = sh->gso_size;
	दीर्घ f_id = -1;    /* id of the current fragment */
	दीर्घ f_size = skb_headlen(skb) - sh_len;  /* current fragment size */
	दीर्घ f_used = 0;  /* bytes used from the current fragment */
	दीर्घ n;            /* size of the current piece of payload */
	पूर्णांक num_edescs = 0;
	पूर्णांक segment;

	क्रम (segment = 0; segment < sh->gso_segs; segment++) अणु
		अचिन्हित पूर्णांक p_used = 0;

		/* One edesc क्रम header and क्रम each piece of the payload. */
		क्रम (num_edescs++; p_used < p_len; num_edescs++) अणु
			/* Advance as needed. */
			जबतक (f_used >= f_size) अणु
				f_id++;
				f_size = skb_frag_size(&sh->frags[f_id]);
				f_used = 0;
			पूर्ण

			/* Use bytes from the current fragment. */
			n = p_len - p_used;
			अगर (n > f_size - f_used)
				n = f_size - f_used;
			f_used += n;
			p_used += n;
		पूर्ण

		/* The last segment may be less than gso_size. */
		data_len -= p_len;
		अगर (data_len < p_len)
			p_len = data_len;
	पूर्ण

	/* '+ gso_segs' क्रम SQ_HDR_SUDESCs क्रम each segment */
	वापस num_edescs + sh->gso_segs;
पूर्ण

#घोषणा POST_CQE_DESC_COUNT 2

/* Get the number of SQ descriptors needed to xmit this skb */
अटल पूर्णांक nicvf_sq_subdesc_required(काष्ठा nicvf *nic, काष्ठा sk_buff *skb)
अणु
	पूर्णांक subdesc_cnt = MIN_SQ_DESC_PER_PKT_XMIT;

	अगर (skb_shinfo(skb)->gso_size && !nic->hw_tso) अणु
		subdesc_cnt = nicvf_tso_count_subdescs(skb);
		वापस subdesc_cnt;
	पूर्ण

	/* Dummy descriptors to get TSO pkt completion notअगरication */
	अगर (nic->t88 && nic->hw_tso && skb_shinfo(skb)->gso_size)
		subdesc_cnt += POST_CQE_DESC_COUNT;

	अगर (skb_shinfo(skb)->nr_frags)
		subdesc_cnt += skb_shinfo(skb)->nr_frags;

	वापस subdesc_cnt;
पूर्ण

/* Add SQ HEADER subdescriptor.
 * First subdescriptor क्रम every send descriptor.
 */
अटल अंतरभूत व्योम
nicvf_sq_add_hdr_subdesc(काष्ठा nicvf *nic, काष्ठा snd_queue *sq, पूर्णांक qentry,
			 पूर्णांक subdesc_cnt, काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	पूर्णांक proto;
	काष्ठा sq_hdr_subdesc *hdr;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;

	ip.hdr = skb_network_header(skb);
	hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, qentry);
	स_रखो(hdr, 0, SND_QUEUE_DESC_SIZE);
	hdr->subdesc_type = SQ_DESC_TYPE_HEADER;

	अगर (nic->t88 && nic->hw_tso && skb_shinfo(skb)->gso_size) अणु
		/* post_cqe = 0, to aव्योम HW posting a CQE क्रम every TSO
		 * segment transmitted on 88xx.
		 */
		hdr->subdesc_cnt = subdesc_cnt - POST_CQE_DESC_COUNT;
	पूर्ण अन्यथा अणु
		sq->skbuff[qentry] = (u64)skb;
		/* Enable notअगरication via CQE after processing SQE */
		hdr->post_cqe = 1;
		/* No of subdescriptors following this */
		hdr->subdesc_cnt = subdesc_cnt;
	पूर्ण
	hdr->tot_len = len;

	/* Offload checksum calculation to HW */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (ip.v4->version == 4)
			hdr->csum_l3 = 1; /* Enable IP csum calculation */
		hdr->l3_offset = skb_network_offset(skb);
		hdr->l4_offset = skb_transport_offset(skb);

		proto = (ip.v4->version == 4) ? ip.v4->protocol :
			ip.v6->nexthdr;

		चयन (proto) अणु
		हाल IPPROTO_TCP:
			hdr->csum_l4 = SEND_L4_CSUM_TCP;
			अवरोध;
		हाल IPPROTO_UDP:
			hdr->csum_l4 = SEND_L4_CSUM_UDP;
			अवरोध;
		हाल IPPROTO_SCTP:
			hdr->csum_l4 = SEND_L4_CSUM_SCTP;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nic->hw_tso && skb_shinfo(skb)->gso_size) अणु
		hdr->tso = 1;
		hdr->tso_start = skb_transport_offset(skb) + tcp_hdrlen(skb);
		hdr->tso_max_paysize = skb_shinfo(skb)->gso_size;
		/* For non-tunneled pkts, poपूर्णांक this to L2 ethertype */
		hdr->inner_l3_offset = skb_network_offset(skb) - 2;
		this_cpu_inc(nic->pnicvf->drv_stats->tx_tso);
	पूर्ण

	/* Check अगर बारtamp is requested */
	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		skb_tx_बारtamp(skb);
		वापस;
	पूर्ण

	/* Tx बारtamping not supported aदीर्घ with TSO, so ignore request */
	अगर (skb_shinfo(skb)->gso_size)
		वापस;

	/* HW supports only a single outstanding packet to बारtamp */
	अगर (!atomic_add_unless(&nic->pnicvf->tx_ptp_skbs, 1, 1))
		वापस;

	/* Mark the SKB क्रम later reference */
	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	/* Finally enable बारtamp generation
	 * Since 'post_cqe' is also set, two CQEs will be posted
	 * क्रम this packet i.e CQE_TYPE_SEND and CQE_TYPE_SEND_PTP.
	 */
	hdr->tsपंचांगp = 1;
पूर्ण

/* SQ GATHER subdescriptor
 * Must follow HDR descriptor
 */
अटल अंतरभूत व्योम nicvf_sq_add_gather_subdesc(काष्ठा snd_queue *sq, पूर्णांक qentry,
					       पूर्णांक size, u64 data)
अणु
	काष्ठा sq_gather_subdesc *gather;

	qentry &= (sq->dmem.q_len - 1);
	gather = (काष्ठा sq_gather_subdesc *)GET_SQ_DESC(sq, qentry);

	स_रखो(gather, 0, SND_QUEUE_DESC_SIZE);
	gather->subdesc_type = SQ_DESC_TYPE_GATHER;
	gather->ld_type = NIC_SEND_LD_TYPE_E_LDD;
	gather->size = size;
	gather->addr = data;
पूर्ण

/* Add HDR + IMMEDIATE subdescriptors right after descriptors of a TSO
 * packet so that a CQE is posted as a notअगरation क्रम transmission of
 * TSO packet.
 */
अटल अंतरभूत व्योम nicvf_sq_add_cqe_subdesc(काष्ठा snd_queue *sq, पूर्णांक qentry,
					    पूर्णांक tso_sqe, काष्ठा sk_buff *skb)
अणु
	काष्ठा sq_imm_subdesc *imm;
	काष्ठा sq_hdr_subdesc *hdr;

	sq->skbuff[qentry] = (u64)skb;

	hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, qentry);
	स_रखो(hdr, 0, SND_QUEUE_DESC_SIZE);
	hdr->subdesc_type = SQ_DESC_TYPE_HEADER;
	/* Enable notअगरication via CQE after processing SQE */
	hdr->post_cqe = 1;
	/* There is no packet to transmit here */
	hdr->करोnt_send = 1;
	hdr->subdesc_cnt = POST_CQE_DESC_COUNT - 1;
	hdr->tot_len = 1;
	/* Actual TSO header SQE index, needed क्रम cleanup */
	hdr->rsvd2 = tso_sqe;

	qentry = nicvf_get_nxt_sqentry(sq, qentry);
	imm = (काष्ठा sq_imm_subdesc *)GET_SQ_DESC(sq, qentry);
	स_रखो(imm, 0, SND_QUEUE_DESC_SIZE);
	imm->subdesc_type = SQ_DESC_TYPE_IMMEDIATE;
	imm->len = 1;
पूर्ण

अटल अंतरभूत व्योम nicvf_sq_करोorbell(काष्ठा nicvf *nic, काष्ठा sk_buff *skb,
				     पूर्णांक sq_num, पूर्णांक desc_cnt)
अणु
	काष्ठा netdev_queue *txq;

	txq = netdev_get_tx_queue(nic->pnicvf->netdev,
				  skb_get_queue_mapping(skb));

	netdev_tx_sent_queue(txq, skb->len);

	/* make sure all memory stores are करोne beक्रमe ringing करोorbell */
	smp_wmb();

	/* Inक्रमm HW to xmit all TSO segments */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_SQ_0_7_DOOR,
			      sq_num, desc_cnt);
पूर्ण

/* Segment a TSO packet पूर्णांकo 'gso_size' segments and append
 * them to SQ क्रम transfer
 */
अटल पूर्णांक nicvf_sq_append_tso(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			       पूर्णांक sq_num, पूर्णांक qentry, काष्ठा sk_buff *skb)
अणु
	काष्ठा tso_t tso;
	पूर्णांक seg_subdescs = 0, desc_cnt = 0;
	पूर्णांक seg_len, total_len, data_left;
	पूर्णांक hdr_qentry = qentry;
	पूर्णांक hdr_len;

	hdr_len = tso_start(skb, &tso);

	total_len = skb->len - hdr_len;
	जबतक (total_len > 0) अणु
		अक्षर *hdr;

		/* Save Qentry क्रम adding HDR_SUBDESC at the end */
		hdr_qentry = qentry;

		data_left = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, total_len);
		total_len -= data_left;

		/* Add segment's header */
		qentry = nicvf_get_nxt_sqentry(sq, qentry);
		hdr = sq->tso_hdrs + qentry * TSO_HEADER_SIZE;
		tso_build_hdr(skb, hdr, &tso, data_left, total_len == 0);
		nicvf_sq_add_gather_subdesc(sq, qentry, hdr_len,
					    sq->tso_hdrs_phys +
					    qentry * TSO_HEADER_SIZE);
		/* HDR_SUDESC + GATHER */
		seg_subdescs = 2;
		seg_len = hdr_len;

		/* Add segment's payload fragments */
		जबतक (data_left > 0) अणु
			पूर्णांक size;

			size = min_t(पूर्णांक, tso.size, data_left);

			qentry = nicvf_get_nxt_sqentry(sq, qentry);
			nicvf_sq_add_gather_subdesc(sq, qentry, size,
						    virt_to_phys(tso.data));
			seg_subdescs++;
			seg_len += size;

			data_left -= size;
			tso_build_data(skb, &tso, size);
		पूर्ण
		nicvf_sq_add_hdr_subdesc(nic, sq, hdr_qentry,
					 seg_subdescs - 1, skb, seg_len);
		sq->skbuff[hdr_qentry] = (u64)शून्य;
		qentry = nicvf_get_nxt_sqentry(sq, qentry);

		desc_cnt += seg_subdescs;
	पूर्ण
	/* Save SKB in the last segment क्रम मुक्तing */
	sq->skbuff[hdr_qentry] = (u64)skb;

	nicvf_sq_करोorbell(nic, skb, sq_num, desc_cnt);

	this_cpu_inc(nic->pnicvf->drv_stats->tx_tso);
	वापस 1;
पूर्ण

/* Append an skb to a SQ क्रम packet transfer. */
पूर्णांक nicvf_sq_append_skb(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			काष्ठा sk_buff *skb, u8 sq_num)
अणु
	पूर्णांक i, size;
	पूर्णांक subdesc_cnt, hdr_sqe = 0;
	पूर्णांक qentry;
	u64 dma_addr;

	subdesc_cnt = nicvf_sq_subdesc_required(nic, skb);
	अगर (subdesc_cnt > atomic_पढ़ो(&sq->मुक्त_cnt))
		जाओ append_fail;

	qentry = nicvf_get_sq_desc(sq, subdesc_cnt);

	/* Check अगर its a TSO packet */
	अगर (skb_shinfo(skb)->gso_size && !nic->hw_tso)
		वापस nicvf_sq_append_tso(nic, sq, sq_num, qentry, skb);

	/* Add SQ header subdesc */
	nicvf_sq_add_hdr_subdesc(nic, sq, qentry, subdesc_cnt - 1,
				 skb, skb->len);
	hdr_sqe = qentry;

	/* Add SQ gather subdescs */
	qentry = nicvf_get_nxt_sqentry(sq, qentry);
	size = skb_is_nonlinear(skb) ? skb_headlen(skb) : skb->len;
	/* HW will ensure data coherency, CPU sync not required */
	dma_addr = dma_map_page_attrs(&nic->pdev->dev, virt_to_page(skb->data),
				      offset_in_page(skb->data), size,
				      DMA_TO_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(&nic->pdev->dev, dma_addr)) अणु
		nicvf_rollback_sq_desc(sq, qentry, subdesc_cnt);
		वापस 0;
	पूर्ण

	nicvf_sq_add_gather_subdesc(sq, qentry, size, dma_addr);

	/* Check क्रम scattered buffer */
	अगर (!skb_is_nonlinear(skb))
		जाओ करोorbell;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		qentry = nicvf_get_nxt_sqentry(sq, qentry);
		size = skb_frag_size(frag);
		dma_addr = dma_map_page_attrs(&nic->pdev->dev,
					      skb_frag_page(frag),
					      skb_frag_off(frag), size,
					      DMA_TO_DEVICE,
					      DMA_ATTR_SKIP_CPU_SYNC);
		अगर (dma_mapping_error(&nic->pdev->dev, dma_addr)) अणु
			/* Free entire chain of mapped buffers
			 * here 'i' = frags mapped + above mapped skb->data
			 */
			nicvf_unmap_sndq_buffers(nic, sq, hdr_sqe, i);
			nicvf_rollback_sq_desc(sq, qentry, subdesc_cnt);
			वापस 0;
		पूर्ण
		nicvf_sq_add_gather_subdesc(sq, qentry, size, dma_addr);
	पूर्ण

करोorbell:
	अगर (nic->t88 && skb_shinfo(skb)->gso_size) अणु
		qentry = nicvf_get_nxt_sqentry(sq, qentry);
		nicvf_sq_add_cqe_subdesc(sq, qentry, hdr_sqe, skb);
	पूर्ण

	nicvf_sq_करोorbell(nic, skb, sq_num, subdesc_cnt);

	वापस 1;

append_fail:
	/* Use original PCI dev क्रम debug log */
	nic = nic->pnicvf;
	netdev_dbg(nic->netdev, "Not enough SQ descriptors to xmit pkt\n");
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित frag_num(अचिन्हित i)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (i & ~3) + 3 - (i & 3);
#अन्यथा
	वापस i;
#पूर्ण_अगर
पूर्ण

अटल व्योम nicvf_unmap_rcv_buffer(काष्ठा nicvf *nic, u64 dma_addr,
				   u64 buf_addr, bool xdp)
अणु
	काष्ठा page *page = शून्य;
	पूर्णांक len = RCV_FRAG_LEN;

	अगर (xdp) अणु
		page = virt_to_page(phys_to_virt(buf_addr));
		/* Check अगर it's a recycled page, अगर not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		अगर (page_ref_count(page) != 1)
			वापस;

		len += XDP_PACKET_HEADROOM;
		/* Receive buffers in XDP mode are mapped from page start */
		dma_addr &= PAGE_MASK;
	पूर्ण
	dma_unmap_page_attrs(&nic->pdev->dev, dma_addr, len,
			     DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

/* Returns SKB क्रम a received packet */
काष्ठा sk_buff *nicvf_get_rcv_skb(काष्ठा nicvf *nic,
				  काष्ठा cqe_rx_t *cqe_rx, bool xdp)
अणु
	पूर्णांक frag;
	पूर्णांक payload_len = 0;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा page *page;
	पूर्णांक offset;
	u16 *rb_lens = शून्य;
	u64 *rb_ptrs = शून्य;
	u64 phys_addr;

	rb_lens = (व्योम *)cqe_rx + (3 * माप(u64));
	/* Except 88xx pass1 on all other chips CQE_RX2_S is added to
	 * CQE_RX at word6, hence buffer poपूर्णांकers move by word
	 *
	 * Use existing 'hw_tso' flag which will be set क्रम all chips
	 * except 88xx pass1 instead of a additional cache line
	 * access (or miss) by using pci dev's revision.
	 */
	अगर (!nic->hw_tso)
		rb_ptrs = (व्योम *)cqe_rx + (6 * माप(u64));
	अन्यथा
		rb_ptrs = (व्योम *)cqe_rx + (7 * माप(u64));

	क्रम (frag = 0; frag < cqe_rx->rb_cnt; frag++) अणु
		payload_len = rb_lens[frag_num(frag)];
		phys_addr = nicvf_iova_to_phys(nic, *rb_ptrs);
		अगर (!phys_addr) अणु
			अगर (skb)
				dev_kमुक्त_skb_any(skb);
			वापस शून्य;
		पूर्ण

		अगर (!frag) अणु
			/* First fragment */
			nicvf_unmap_rcv_buffer(nic,
					       *rb_ptrs - cqe_rx->align_pad,
					       phys_addr, xdp);
			skb = nicvf_rb_ptr_to_skb(nic,
						  phys_addr - cqe_rx->align_pad,
						  payload_len);
			अगर (!skb)
				वापस शून्य;
			skb_reserve(skb, cqe_rx->align_pad);
			skb_put(skb, payload_len);
		पूर्ण अन्यथा अणु
			/* Add fragments */
			nicvf_unmap_rcv_buffer(nic, *rb_ptrs, phys_addr, xdp);
			page = virt_to_page(phys_to_virt(phys_addr));
			offset = phys_to_virt(phys_addr) - page_address(page);
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
					offset, payload_len, RCV_FRAG_LEN);
		पूर्ण
		/* Next buffer poपूर्णांकer */
		rb_ptrs++;
	पूर्ण
	वापस skb;
पूर्ण

अटल u64 nicvf_पूर्णांक_type_to_mask(पूर्णांक पूर्णांक_type, पूर्णांक q_idx)
अणु
	u64 reg_val;

	चयन (पूर्णांक_type) अणु
	हाल NICVF_INTR_CQ:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_CQ_SHIFT);
		अवरोध;
	हाल NICVF_INTR_SQ:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_SQ_SHIFT);
		अवरोध;
	हाल NICVF_INTR_RBDR:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_RBDR_SHIFT);
		अवरोध;
	हाल NICVF_INTR_PKT_DROP:
		reg_val = (1ULL << NICVF_INTR_PKT_DROP_SHIFT);
		अवरोध;
	हाल NICVF_INTR_TCP_TIMER:
		reg_val = (1ULL << NICVF_INTR_TCP_TIMER_SHIFT);
		अवरोध;
	हाल NICVF_INTR_MBOX:
		reg_val = (1ULL << NICVF_INTR_MBOX_SHIFT);
		अवरोध;
	हाल NICVF_INTR_QS_ERR:
		reg_val = (1ULL << NICVF_INTR_QS_ERR_SHIFT);
		अवरोध;
	शेष:
		reg_val = 0;
	पूर्ण

	वापस reg_val;
पूर्ण

/* Enable पूर्णांकerrupt */
व्योम nicvf_enable_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx)
अणु
	u64 mask = nicvf_पूर्णांक_type_to_mask(पूर्णांक_type, q_idx);

	अगर (!mask) अणु
		netdev_dbg(nic->netdev,
			   "Failed to enable interrupt: unknown type\n");
		वापस;
	पूर्ण
	nicvf_reg_ग_लिखो(nic, NIC_VF_ENA_W1S,
			nicvf_reg_पढ़ो(nic, NIC_VF_ENA_W1S) | mask);
पूर्ण

/* Disable पूर्णांकerrupt */
व्योम nicvf_disable_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx)
अणु
	u64 mask = nicvf_पूर्णांक_type_to_mask(पूर्णांक_type, q_idx);

	अगर (!mask) अणु
		netdev_dbg(nic->netdev,
			   "Failed to disable interrupt: unknown type\n");
		वापस;
	पूर्ण

	nicvf_reg_ग_लिखो(nic, NIC_VF_ENA_W1C, mask);
पूर्ण

/* Clear पूर्णांकerrupt */
व्योम nicvf_clear_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx)
अणु
	u64 mask = nicvf_पूर्णांक_type_to_mask(पूर्णांक_type, q_idx);

	अगर (!mask) अणु
		netdev_dbg(nic->netdev,
			   "Failed to clear interrupt: unknown type\n");
		वापस;
	पूर्ण

	nicvf_reg_ग_लिखो(nic, NIC_VF_INT, mask);
पूर्ण

/* Check अगर पूर्णांकerrupt is enabled */
पूर्णांक nicvf_is_पूर्णांकr_enabled(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx)
अणु
	u64 mask = nicvf_पूर्णांक_type_to_mask(पूर्णांक_type, q_idx);
	/* If पूर्णांकerrupt type is unknown, we treat it disabled. */
	अगर (!mask) अणु
		netdev_dbg(nic->netdev,
			   "Failed to check interrupt enable: unknown type\n");
		वापस 0;
	पूर्ण

	वापस mask & nicvf_reg_पढ़ो(nic, NIC_VF_ENA_W1S);
पूर्ण

व्योम nicvf_update_rq_stats(काष्ठा nicvf *nic, पूर्णांक rq_idx)
अणु
	काष्ठा rcv_queue *rq;

#घोषणा GET_RQ_STATS(reg) \
	nicvf_reg_पढ़ो(nic, NIC_QSET_RQ_0_7_STAT_0_1 |\
			    (rq_idx << NIC_Q_NUM_SHIFT) | (reg << 3))

	rq = &nic->qs->rq[rq_idx];
	rq->stats.bytes = GET_RQ_STATS(RQ_SQ_STATS_OCTS);
	rq->stats.pkts = GET_RQ_STATS(RQ_SQ_STATS_PKTS);
पूर्ण

व्योम nicvf_update_sq_stats(काष्ठा nicvf *nic, पूर्णांक sq_idx)
अणु
	काष्ठा snd_queue *sq;

#घोषणा GET_SQ_STATS(reg) \
	nicvf_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_STAT_0_1 |\
			    (sq_idx << NIC_Q_NUM_SHIFT) | (reg << 3))

	sq = &nic->qs->sq[sq_idx];
	sq->stats.bytes = GET_SQ_STATS(RQ_SQ_STATS_OCTS);
	sq->stats.pkts = GET_SQ_STATS(RQ_SQ_STATS_PKTS);
पूर्ण

/* Check क्रम errors in the receive cmp.queue entry */
पूर्णांक nicvf_check_cqe_rx_errs(काष्ठा nicvf *nic, काष्ठा cqe_rx_t *cqe_rx)
अणु
	netअगर_err(nic, rx_err, nic->netdev,
		  "RX error CQE err_level 0x%x err_opcode 0x%x\n",
		  cqe_rx->err_level, cqe_rx->err_opcode);

	चयन (cqe_rx->err_opcode) अणु
	हाल CQ_RX_ERROP_RE_PARTIAL:
		this_cpu_inc(nic->drv_stats->rx_bgx_truncated_pkts);
		अवरोध;
	हाल CQ_RX_ERROP_RE_JABBER:
		this_cpu_inc(nic->drv_stats->rx_jabber_errs);
		अवरोध;
	हाल CQ_RX_ERROP_RE_FCS:
		this_cpu_inc(nic->drv_stats->rx_fcs_errs);
		अवरोध;
	हाल CQ_RX_ERROP_RE_RX_CTL:
		this_cpu_inc(nic->drv_stats->rx_bgx_errs);
		अवरोध;
	हाल CQ_RX_ERROP_PREL2_ERR:
		this_cpu_inc(nic->drv_stats->rx_prel2_errs);
		अवरोध;
	हाल CQ_RX_ERROP_L2_MAL:
		this_cpu_inc(nic->drv_stats->rx_l2_hdr_malक्रमmed);
		अवरोध;
	हाल CQ_RX_ERROP_L2_OVERSIZE:
		this_cpu_inc(nic->drv_stats->rx_oversize);
		अवरोध;
	हाल CQ_RX_ERROP_L2_UNDERSIZE:
		this_cpu_inc(nic->drv_stats->rx_undersize);
		अवरोध;
	हाल CQ_RX_ERROP_L2_LENMISM:
		this_cpu_inc(nic->drv_stats->rx_l2_len_mismatch);
		अवरोध;
	हाल CQ_RX_ERROP_L2_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l2_pclp);
		अवरोध;
	हाल CQ_RX_ERROP_IP_NOT:
		this_cpu_inc(nic->drv_stats->rx_ip_ver_errs);
		अवरोध;
	हाल CQ_RX_ERROP_IP_CSUM_ERR:
		this_cpu_inc(nic->drv_stats->rx_ip_csum_errs);
		अवरोध;
	हाल CQ_RX_ERROP_IP_MAL:
		this_cpu_inc(nic->drv_stats->rx_ip_hdr_malक्रमmed);
		अवरोध;
	हाल CQ_RX_ERROP_IP_MALD:
		this_cpu_inc(nic->drv_stats->rx_ip_payload_malक्रमmed);
		अवरोध;
	हाल CQ_RX_ERROP_IP_HOP:
		this_cpu_inc(nic->drv_stats->rx_ip_ttl_errs);
		अवरोध;
	हाल CQ_RX_ERROP_L3_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l3_pclp);
		अवरोध;
	हाल CQ_RX_ERROP_L4_MAL:
		this_cpu_inc(nic->drv_stats->rx_l4_malक्रमmed);
		अवरोध;
	हाल CQ_RX_ERROP_L4_CHK:
		this_cpu_inc(nic->drv_stats->rx_l4_csum_errs);
		अवरोध;
	हाल CQ_RX_ERROP_UDP_LEN:
		this_cpu_inc(nic->drv_stats->rx_udp_len_errs);
		अवरोध;
	हाल CQ_RX_ERROP_L4_PORT:
		this_cpu_inc(nic->drv_stats->rx_l4_port_errs);
		अवरोध;
	हाल CQ_RX_ERROP_TCP_FLAG:
		this_cpu_inc(nic->drv_stats->rx_tcp_flag_errs);
		अवरोध;
	हाल CQ_RX_ERROP_TCP_OFFSET:
		this_cpu_inc(nic->drv_stats->rx_tcp_offset_errs);
		अवरोध;
	हाल CQ_RX_ERROP_L4_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l4_pclp);
		अवरोध;
	हाल CQ_RX_ERROP_RBDR_TRUNC:
		this_cpu_inc(nic->drv_stats->rx_truncated_pkts);
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/* Check क्रम errors in the send cmp.queue entry */
पूर्णांक nicvf_check_cqe_tx_errs(काष्ठा nicvf *nic, काष्ठा cqe_send_t *cqe_tx)
अणु
	चयन (cqe_tx->send_status) अणु
	हाल CQ_TX_ERROP_DESC_FAULT:
		this_cpu_inc(nic->drv_stats->tx_desc_fault);
		अवरोध;
	हाल CQ_TX_ERROP_HDR_CONS_ERR:
		this_cpu_inc(nic->drv_stats->tx_hdr_cons_err);
		अवरोध;
	हाल CQ_TX_ERROP_SUBDC_ERR:
		this_cpu_inc(nic->drv_stats->tx_subdesc_err);
		अवरोध;
	हाल CQ_TX_ERROP_MAX_SIZE_VIOL:
		this_cpu_inc(nic->drv_stats->tx_max_size_exceeded);
		अवरोध;
	हाल CQ_TX_ERROP_IMM_SIZE_OFLOW:
		this_cpu_inc(nic->drv_stats->tx_imm_size_oflow);
		अवरोध;
	हाल CQ_TX_ERROP_DATA_SEQUENCE_ERR:
		this_cpu_inc(nic->drv_stats->tx_data_seq_err);
		अवरोध;
	हाल CQ_TX_ERROP_MEM_SEQUENCE_ERR:
		this_cpu_inc(nic->drv_stats->tx_mem_seq_err);
		अवरोध;
	हाल CQ_TX_ERROP_LOCK_VIOL:
		this_cpu_inc(nic->drv_stats->tx_lock_viol);
		अवरोध;
	हाल CQ_TX_ERROP_DATA_FAULT:
		this_cpu_inc(nic->drv_stats->tx_data_fault);
		अवरोध;
	हाल CQ_TX_ERROP_TSTMP_CONFLICT:
		this_cpu_inc(nic->drv_stats->tx_tsपंचांगp_conflict);
		अवरोध;
	हाल CQ_TX_ERROP_TSTMP_TIMEOUT:
		this_cpu_inc(nic->drv_stats->tx_tsपंचांगp_समयout);
		अवरोध;
	हाल CQ_TX_ERROP_MEM_FAULT:
		this_cpu_inc(nic->drv_stats->tx_mem_fault);
		अवरोध;
	हाल CQ_TX_ERROP_CK_OVERLAP:
		this_cpu_inc(nic->drv_stats->tx_csum_overlap);
		अवरोध;
	हाल CQ_TX_ERROP_CK_OFLOW:
		this_cpu_inc(nic->drv_stats->tx_csum_overflow);
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण
