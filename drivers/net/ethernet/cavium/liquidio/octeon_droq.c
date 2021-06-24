<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn66xx_regs.h"
#समावेश "cn66xx_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "cn23xx_vf_device.h"

काष्ठा niclist अणु
	काष्ठा list_head list;
	व्योम *ptr;
पूर्ण;

काष्ठा __dispatch अणु
	काष्ठा list_head list;
	काष्ठा octeon_recv_info *rinfo;
	octeon_dispatch_fn_t disp_fn;
पूर्ण;

/** Get the argument that the user set when रेजिस्टरing dispatch
 *  function क्रम a given opcode/subcode.
 *  @param  octeon_dev - the octeon device poपूर्णांकer.
 *  @param  opcode     - the opcode क्रम which the dispatch argument
 *                       is to be checked.
 *  @param  subcode    - the subcode क्रम which the dispatch argument
 *                       is to be checked.
 *  @वापस  Success: व्योम * (argument to the dispatch function)
 *  @वापस  Failure: शून्य
 *
 */
व्योम *octeon_get_dispatch_arg(काष्ठा octeon_device *octeon_dev,
			      u16 opcode, u16 subcode)
अणु
	पूर्णांक idx;
	काष्ठा list_head *dispatch;
	व्योम *fn_arg = शून्य;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_lock_bh(&octeon_dev->dispatch.lock);

	अगर (octeon_dev->dispatch.count == 0) अणु
		spin_unlock_bh(&octeon_dev->dispatch.lock);
		वापस शून्य;
	पूर्ण

	अगर (octeon_dev->dispatch.dlist[idx].opcode == combined_opcode) अणु
		fn_arg = octeon_dev->dispatch.dlist[idx].arg;
	पूर्ण अन्यथा अणु
		list_क्रम_each(dispatch,
			      &octeon_dev->dispatch.dlist[idx].list) अणु
			अगर (((काष्ठा octeon_dispatch *)dispatch)->opcode ==
			    combined_opcode) अणु
				fn_arg = ((काष्ठा octeon_dispatch *)
					  dispatch)->arg;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&octeon_dev->dispatch.lock);
	वापस fn_arg;
पूर्ण

/** Check क्रम packets on Droq. This function should be called with lock held.
 *  @param  droq - Droq on which count is checked.
 *  @वापस Returns packet count.
 */
u32 octeon_droq_check_hw_क्रम_pkts(काष्ठा octeon_droq *droq)
अणु
	u32 pkt_count = 0;
	u32 last_count;

	pkt_count = पढ़ोl(droq->pkts_sent_reg);

	last_count = pkt_count - droq->pkt_count;
	droq->pkt_count = pkt_count;

	/* we shall ग_लिखो to cnts  at napi irq enable or end of droq tasklet */
	अगर (last_count)
		atomic_add(last_count, &droq->pkts_pending);

	वापस last_count;
पूर्ण

अटल व्योम octeon_droq_compute_max_packet_bufs(काष्ठा octeon_droq *droq)
अणु
	u32 count = 0;

	/* max_empty_descs is the max. no. of descs that can have no buffers.
	 * If the empty desc count goes beyond this value, we cannot safely
	 * पढ़ो in a 64K packet sent by Octeon
	 * (64K is max pkt size from Octeon)
	 */
	droq->max_empty_descs = 0;

	करो अणु
		droq->max_empty_descs++;
		count += droq->buffer_size;
	पूर्ण जबतक (count < (64 * 1024));

	droq->max_empty_descs = droq->max_count - droq->max_empty_descs;
पूर्ण

अटल व्योम octeon_droq_reset_indices(काष्ठा octeon_droq *droq)
अणु
	droq->पढ़ो_idx = 0;
	droq->ग_लिखो_idx = 0;
	droq->refill_idx = 0;
	droq->refill_count = 0;
	atomic_set(&droq->pkts_pending, 0);
पूर्ण

अटल व्योम
octeon_droq_destroy_ring_buffers(काष्ठा octeon_device *oct,
				 काष्ठा octeon_droq *droq)
अणु
	u32 i;
	काष्ठा octeon_skb_page_info *pg_info;

	क्रम (i = 0; i < droq->max_count; i++) अणु
		pg_info = &droq->recv_buf_list[i].pg_info;
		अगर (!pg_info)
			जारी;

		अगर (pg_info->dma)
			lio_unmap_ring(oct->pci_dev,
				       (u64)pg_info->dma);
		pg_info->dma = 0;

		अगर (pg_info->page)
			recv_buffer_destroy(droq->recv_buf_list[i].buffer,
					    pg_info);

		droq->recv_buf_list[i].buffer = शून्य;
	पूर्ण

	octeon_droq_reset_indices(droq);
पूर्ण

अटल पूर्णांक
octeon_droq_setup_ring_buffers(काष्ठा octeon_device *oct,
			       काष्ठा octeon_droq *droq)
अणु
	u32 i;
	व्योम *buf;
	काष्ठा octeon_droq_desc *desc_ring = droq->desc_ring;

	क्रम (i = 0; i < droq->max_count; i++) अणु
		buf = recv_buffer_alloc(oct, &droq->recv_buf_list[i].pg_info);

		अगर (!buf) अणु
			dev_err(&oct->pci_dev->dev, "%s buffer alloc failed\n",
				__func__);
			droq->stats.rx_alloc_failure++;
			वापस -ENOMEM;
		पूर्ण

		droq->recv_buf_list[i].buffer = buf;
		droq->recv_buf_list[i].data = get_rbd(buf);
		desc_ring[i].info_ptr = 0;
		desc_ring[i].buffer_ptr =
			lio_map_ring(droq->recv_buf_list[i].buffer);
	पूर्ण

	octeon_droq_reset_indices(droq);

	octeon_droq_compute_max_packet_bufs(droq);

	वापस 0;
पूर्ण

पूर्णांक octeon_delete_droq(काष्ठा octeon_device *oct, u32 q_no)
अणु
	काष्ठा octeon_droq *droq = oct->droq[q_no];

	dev_dbg(&oct->pci_dev->dev, "%s[%d]\n", __func__, q_no);

	octeon_droq_destroy_ring_buffers(oct, droq);
	vमुक्त(droq->recv_buf_list);

	अगर (droq->desc_ring)
		lio_dma_मुक्त(oct, (droq->max_count * OCT_DROQ_DESC_SIZE),
			     droq->desc_ring, droq->desc_ring_dma);

	स_रखो(droq, 0, OCT_DROQ_SIZE);
	oct->io_qmask.oq &= ~(1ULL << q_no);
	vमुक्त(oct->droq[q_no]);
	oct->droq[q_no] = शून्य;
	oct->num_oqs--;

	वापस 0;
पूर्ण

पूर्णांक octeon_init_droq(काष्ठा octeon_device *oct,
		     u32 q_no,
		     u32 num_descs,
		     u32 desc_size,
		     व्योम *app_ctx)
अणु
	काष्ठा octeon_droq *droq;
	u32 desc_ring_size = 0, c_num_descs = 0, c_buf_size = 0;
	u32 c_pkts_per_पूर्णांकr = 0, c_refill_threshold = 0;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	dev_dbg(&oct->pci_dev->dev, "%s[%d]\n", __func__, q_no);

	droq = oct->droq[q_no];
	स_रखो(droq, 0, OCT_DROQ_SIZE);

	droq->oct_dev = oct;
	droq->q_no = q_no;
	अगर (app_ctx)
		droq->app_ctx = app_ctx;
	अन्यथा
		droq->app_ctx = (व्योम *)(माप_प्रकार)q_no;

	c_num_descs = num_descs;
	c_buf_size = desc_size;
	अगर (OCTEON_CN6XXX(oct)) अणु
		काष्ठा octeon_config *conf6x = CHIP_CONF(oct, cn6xxx);

		c_pkts_per_पूर्णांकr = (u32)CFG_GET_OQ_PKTS_PER_INTR(conf6x);
		c_refill_threshold =
			(u32)CFG_GET_OQ_REFILL_THRESHOLD(conf6x);
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(oct)) अणु
		काष्ठा octeon_config *conf23 = CHIP_CONF(oct, cn23xx_pf);

		c_pkts_per_पूर्णांकr = (u32)CFG_GET_OQ_PKTS_PER_INTR(conf23);
		c_refill_threshold = (u32)CFG_GET_OQ_REFILL_THRESHOLD(conf23);
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
		काष्ठा octeon_config *conf23 = CHIP_CONF(oct, cn23xx_vf);

		c_pkts_per_पूर्णांकr = (u32)CFG_GET_OQ_PKTS_PER_INTR(conf23);
		c_refill_threshold = (u32)CFG_GET_OQ_REFILL_THRESHOLD(conf23);
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण

	droq->max_count = c_num_descs;
	droq->buffer_size = c_buf_size;

	desc_ring_size = droq->max_count * OCT_DROQ_DESC_SIZE;
	droq->desc_ring = lio_dma_alloc(oct, desc_ring_size,
					(dma_addr_t *)&droq->desc_ring_dma);

	अगर (!droq->desc_ring) अणु
		dev_err(&oct->pci_dev->dev,
			"Output queue %d ring alloc failed\n", q_no);
		वापस 1;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "droq[%d]: desc_ring: virt: 0x%p, dma: %lx\n",
		q_no, droq->desc_ring, droq->desc_ring_dma);
	dev_dbg(&oct->pci_dev->dev, "droq[%d]: num_desc: %d\n", q_no,
		droq->max_count);

	droq->recv_buf_list = vzalloc_node(array_size(droq->max_count, OCT_DROQ_RECVBUF_SIZE),
					   numa_node);
	अगर (!droq->recv_buf_list)
		droq->recv_buf_list = vzalloc(array_size(droq->max_count, OCT_DROQ_RECVBUF_SIZE));
	अगर (!droq->recv_buf_list) अणु
		dev_err(&oct->pci_dev->dev, "Output queue recv buf list alloc failed\n");
		जाओ init_droq_fail;
	पूर्ण

	अगर (octeon_droq_setup_ring_buffers(oct, droq))
		जाओ init_droq_fail;

	droq->pkts_per_पूर्णांकr = c_pkts_per_पूर्णांकr;
	droq->refill_threshold = c_refill_threshold;

	dev_dbg(&oct->pci_dev->dev, "DROQ INIT: max_empty_descs: %d\n",
		droq->max_empty_descs);

	INIT_LIST_HEAD(&droq->dispatch_list);

	/* For 56xx Pass1, this function won't be called, so no checks. */
	oct->fn_list.setup_oq_regs(oct, q_no);

	oct->io_qmask.oq |= BIT_ULL(q_no);

	वापस 0;

init_droq_fail:
	octeon_delete_droq(oct, q_no);
	वापस 1;
पूर्ण

/* octeon_create_recv_info
 * Parameters:
 *  octeon_dev - poपूर्णांकer to the octeon device काष्ठाure
 *  droq       - droq in which the packet arrived.
 *  buf_cnt    - no. of buffers used by the packet.
 *  idx        - index in the descriptor क्रम the first buffer in the packet.
 * Description:
 *  Allocates a recv_info_t and copies the buffer addresses क्रम packet data
 *  पूर्णांकo the recv_pkt space which starts at an 8B offset from recv_info_t.
 *  Flags the descriptors क्रम refill later. If available descriptors go
 *  below the threshold to receive a 64K pkt, new buffers are first allocated
 *  beक्रमe the recv_pkt_t is created.
 *  This routine will be called in पूर्णांकerrupt context.
 * Returns:
 *  Success: Poपूर्णांकer to recv_info_t
 *  Failure: शून्य.
 */
अटल अंतरभूत काष्ठा octeon_recv_info *octeon_create_recv_info(
		काष्ठा octeon_device *octeon_dev,
		काष्ठा octeon_droq *droq,
		u32 buf_cnt,
		u32 idx)
अणु
	काष्ठा octeon_droq_info *info;
	काष्ठा octeon_recv_pkt *recv_pkt;
	काष्ठा octeon_recv_info *recv_info;
	u32 i, bytes_left;
	काष्ठा octeon_skb_page_info *pg_info;

	info = (काष्ठा octeon_droq_info *)droq->recv_buf_list[idx].data;

	recv_info = octeon_alloc_recv_info(माप(काष्ठा __dispatch));
	अगर (!recv_info)
		वापस शून्य;

	recv_pkt = recv_info->recv_pkt;
	recv_pkt->rh = info->rh;
	recv_pkt->length = (u32)info->length;
	recv_pkt->buffer_count = (u16)buf_cnt;
	recv_pkt->octeon_id = (u16)octeon_dev->octeon_id;

	i = 0;
	bytes_left = (u32)info->length;

	जबतक (buf_cnt) अणु
		अणु
			pg_info = &droq->recv_buf_list[idx].pg_info;

			lio_unmap_ring(octeon_dev->pci_dev,
				       (u64)pg_info->dma);
			pg_info->page = शून्य;
			pg_info->dma = 0;
		पूर्ण

		recv_pkt->buffer_size[i] =
			(bytes_left >=
			 droq->buffer_size) ? droq->buffer_size : bytes_left;

		recv_pkt->buffer_ptr[i] = droq->recv_buf_list[idx].buffer;
		droq->recv_buf_list[idx].buffer = शून्य;

		idx = incr_index(idx, 1, droq->max_count);
		bytes_left -= droq->buffer_size;
		i++;
		buf_cnt--;
	पूर्ण

	वापस recv_info;
पूर्ण

/* If we were not able to refill all buffers, try to move around
 * the buffers that were not dispatched.
 */
अटल अंतरभूत u32
octeon_droq_refill_pullup_descs(काष्ठा octeon_droq *droq,
				काष्ठा octeon_droq_desc *desc_ring)
अणु
	u32 desc_refilled = 0;

	u32 refill_index = droq->refill_idx;

	जबतक (refill_index != droq->पढ़ो_idx) अणु
		अगर (droq->recv_buf_list[refill_index].buffer) अणु
			droq->recv_buf_list[droq->refill_idx].buffer =
				droq->recv_buf_list[refill_index].buffer;
			droq->recv_buf_list[droq->refill_idx].data =
				droq->recv_buf_list[refill_index].data;
			desc_ring[droq->refill_idx].buffer_ptr =
				desc_ring[refill_index].buffer_ptr;
			droq->recv_buf_list[refill_index].buffer = शून्य;
			desc_ring[refill_index].buffer_ptr = 0;
			करो अणु
				droq->refill_idx = incr_index(droq->refill_idx,
							      1,
							      droq->max_count);
				desc_refilled++;
				droq->refill_count--;
			पूर्ण जबतक (droq->recv_buf_list[droq->refill_idx].buffer);
		पूर्ण
		refill_index = incr_index(refill_index, 1, droq->max_count);
	पूर्ण                       /* जबतक */
	वापस desc_refilled;
पूर्ण

/* octeon_droq_refill
 * Parameters:
 *  droq       - droq in which descriptors require new buffers.
 * Description:
 *  Called during normal DROQ processing in पूर्णांकerrupt mode or by the poll
 *  thपढ़ो to refill the descriptors from which buffers were dispatched
 *  to upper layers. Attempts to allocate new buffers. If that fails, moves
 *  up buffers (that were not dispatched) to क्रमm a contiguous ring.
 * Returns:
 *  No of descriptors refilled.
 */
अटल u32
octeon_droq_refill(काष्ठा octeon_device *octeon_dev, काष्ठा octeon_droq *droq)
अणु
	काष्ठा octeon_droq_desc *desc_ring;
	व्योम *buf = शून्य;
	u8 *data;
	u32 desc_refilled = 0;
	काष्ठा octeon_skb_page_info *pg_info;

	desc_ring = droq->desc_ring;

	जबतक (droq->refill_count && (desc_refilled < droq->max_count)) अणु
		/* If a valid buffer exists (happens अगर there is no dispatch),
		 * reuse the buffer, अन्यथा allocate.
		 */
		अगर (!droq->recv_buf_list[droq->refill_idx].buffer) अणु
			pg_info =
				&droq->recv_buf_list[droq->refill_idx].pg_info;
			/* Either recycle the existing pages or go क्रम
			 * new page alloc
			 */
			अगर (pg_info->page)
				buf = recv_buffer_reuse(octeon_dev, pg_info);
			अन्यथा
				buf = recv_buffer_alloc(octeon_dev, pg_info);
			/* If a buffer could not be allocated, no poपूर्णांक in
			 * continuing
			 */
			अगर (!buf) अणु
				droq->stats.rx_alloc_failure++;
				अवरोध;
			पूर्ण
			droq->recv_buf_list[droq->refill_idx].buffer =
				buf;
			data = get_rbd(buf);
		पूर्ण अन्यथा अणु
			data = get_rbd(droq->recv_buf_list
				       [droq->refill_idx].buffer);
		पूर्ण

		droq->recv_buf_list[droq->refill_idx].data = data;

		desc_ring[droq->refill_idx].buffer_ptr =
			lio_map_ring(droq->recv_buf_list[
				     droq->refill_idx].buffer);

		droq->refill_idx = incr_index(droq->refill_idx, 1,
					      droq->max_count);
		desc_refilled++;
		droq->refill_count--;
	पूर्ण

	अगर (droq->refill_count)
		desc_refilled +=
			octeon_droq_refill_pullup_descs(droq, desc_ring);

	/* अगर droq->refill_count
	 * The refill count would not change in pass two. We only moved buffers
	 * to बंद the gap in the ring, but we would still have the same no. of
	 * buffers to refill.
	 */
	वापस desc_refilled;
पूर्ण

/** check अगर we can allocate packets to get out of oom.
 *  @param  droq - Droq being checked.
 *  @वापस 1 अगर fails to refill minimum
 */
पूर्णांक octeon_retry_droq_refill(काष्ठा octeon_droq *droq)
अणु
	काष्ठा octeon_device *oct = droq->oct_dev;
	पूर्णांक desc_refilled, reschedule = 1;
	u32 pkts_credit;

	pkts_credit = पढ़ोl(droq->pkts_credit_reg);
	desc_refilled = octeon_droq_refill(oct, droq);
	अगर (desc_refilled) अणु
		/* Flush the droq descriptor data to memory to be sure
		 * that when we update the credits the data in memory
		 * is accurate.
		 */
		wmb();
		ग_लिखोl(desc_refilled, droq->pkts_credit_reg);

		अगर (pkts_credit + desc_refilled >= CN23XX_SLI_DEF_BP)
			reschedule = 0;
	पूर्ण

	वापस reschedule;
पूर्ण

अटल अंतरभूत u32
octeon_droq_get_bufcount(u32 buf_size, u32 total_len)
अणु
	वापस DIV_ROUND_UP(total_len, buf_size);
पूर्ण

अटल पूर्णांक
octeon_droq_dispatch_pkt(काष्ठा octeon_device *oct,
			 काष्ठा octeon_droq *droq,
			 जोड़ octeon_rh *rh,
			 काष्ठा octeon_droq_info *info)
अणु
	u32 cnt;
	octeon_dispatch_fn_t disp_fn;
	काष्ठा octeon_recv_info *rinfo;

	cnt = octeon_droq_get_bufcount(droq->buffer_size, (u32)info->length);

	disp_fn = octeon_get_dispatch(oct, (u16)rh->r.opcode,
				      (u16)rh->r.subcode);
	अगर (disp_fn) अणु
		rinfo = octeon_create_recv_info(oct, droq, cnt, droq->पढ़ो_idx);
		अगर (rinfo) अणु
			काष्ठा __dispatch *rdisp = rinfo->rsvd;

			rdisp->rinfo = rinfo;
			rdisp->disp_fn = disp_fn;
			rinfo->recv_pkt->rh = *rh;
			list_add_tail(&rdisp->list,
				      &droq->dispatch_list);
		पूर्ण अन्यथा अणु
			droq->stats.dropped_nomem++;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&oct->pci_dev->dev, "DROQ: No dispatch function (opcode %u/%u)\n",
			(अचिन्हित पूर्णांक)rh->r.opcode,
			(अचिन्हित पूर्णांक)rh->r.subcode);
		droq->stats.dropped_nodispatch++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल अंतरभूत व्योम octeon_droq_drop_packets(काष्ठा octeon_device *oct,
					    काष्ठा octeon_droq *droq,
					    u32 cnt)
अणु
	u32 i = 0, buf_cnt;
	काष्ठा octeon_droq_info *info;

	क्रम (i = 0; i < cnt; i++) अणु
		info = (काष्ठा octeon_droq_info *)
			droq->recv_buf_list[droq->पढ़ो_idx].data;
		octeon_swap_8B_data((u64 *)info, 2);

		अगर (info->length) अणु
			info->length += OCTNET_FRM_LENGTH_SIZE;
			droq->stats.bytes_received += info->length;
			buf_cnt = octeon_droq_get_bufcount(droq->buffer_size,
							   (u32)info->length);
		पूर्ण अन्यथा अणु
			dev_err(&oct->pci_dev->dev, "DROQ: In drop: pkt with len 0\n");
			buf_cnt = 1;
		पूर्ण

		droq->पढ़ो_idx = incr_index(droq->पढ़ो_idx, buf_cnt,
					    droq->max_count);
		droq->refill_count += buf_cnt;
	पूर्ण
पूर्ण

अटल u32
octeon_droq_fast_process_packets(काष्ठा octeon_device *oct,
				 काष्ठा octeon_droq *droq,
				 u32 pkts_to_process)
अणु
	u32 pkt, total_len = 0, pkt_count, retval;
	काष्ठा octeon_droq_info *info;
	जोड़ octeon_rh *rh;

	pkt_count = pkts_to_process;

	क्रम (pkt = 0; pkt < pkt_count; pkt++) अणु
		u32 pkt_len = 0;
		काष्ठा sk_buff *nicbuf = शून्य;
		काष्ठा octeon_skb_page_info *pg_info;
		व्योम *buf;

		info = (काष्ठा octeon_droq_info *)
			droq->recv_buf_list[droq->पढ़ो_idx].data;
		octeon_swap_8B_data((u64 *)info, 2);

		अगर (!info->length) अणु
			dev_err(&oct->pci_dev->dev,
				"DROQ[%d] idx: %d len:0, pkt_cnt: %d\n",
				droq->q_no, droq->पढ़ो_idx, pkt_count);
			prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_ADDRESS,
					     (u8 *)info,
					     OCT_DROQ_INFO_SIZE);
			अवरोध;
		पूर्ण

		/* Len of resp hdr in included in the received data len. */
		rh = &info->rh;

		info->length += OCTNET_FRM_LENGTH_SIZE;
		rh->r_dh.len += (ROUNDUP8(OCT_DROQ_INFO_SIZE) / माप(u64));
		total_len += (u32)info->length;
		अगर (opcode_slow_path(rh)) अणु
			u32 buf_cnt;

			buf_cnt = octeon_droq_dispatch_pkt(oct, droq, rh, info);
			droq->पढ़ो_idx = incr_index(droq->पढ़ो_idx,
						    buf_cnt, droq->max_count);
			droq->refill_count += buf_cnt;
		पूर्ण अन्यथा अणु
			अगर (info->length <= droq->buffer_size) अणु
				pkt_len = (u32)info->length;
				nicbuf = droq->recv_buf_list[
					droq->पढ़ो_idx].buffer;
				pg_info = &droq->recv_buf_list[
					droq->पढ़ो_idx].pg_info;
				अगर (recv_buffer_recycle(oct, pg_info))
					pg_info->page = शून्य;
				droq->recv_buf_list[droq->पढ़ो_idx].buffer =
					शून्य;

				droq->पढ़ो_idx = incr_index(droq->पढ़ो_idx, 1,
							    droq->max_count);
				droq->refill_count++;
			पूर्ण अन्यथा अणु
				nicbuf = octeon_fast_packet_alloc((u32)
								  info->length);
				pkt_len = 0;
				/* nicbuf allocation can fail. We'll handle it
				 * inside the loop.
				 */
				जबतक (pkt_len < info->length) अणु
					पूर्णांक cpy_len, idx = droq->पढ़ो_idx;

					cpy_len = ((pkt_len + droq->buffer_size)
						   > info->length) ?
						((u32)info->length - pkt_len) :
						droq->buffer_size;

					अगर (nicbuf) अणु
						octeon_fast_packet_next(droq,
									nicbuf,
									cpy_len,
									idx);
						buf = droq->recv_buf_list[
							idx].buffer;
						recv_buffer_fast_मुक्त(buf);
						droq->recv_buf_list[idx].buffer
							= शून्य;
					पूर्ण अन्यथा अणु
						droq->stats.rx_alloc_failure++;
					पूर्ण

					pkt_len += cpy_len;
					droq->पढ़ो_idx =
						incr_index(droq->पढ़ो_idx, 1,
							   droq->max_count);
					droq->refill_count++;
				पूर्ण
			पूर्ण

			अगर (nicbuf) अणु
				अगर (droq->ops.fptr) अणु
					droq->ops.fptr(oct->octeon_id,
						       nicbuf, pkt_len,
						       rh, &droq->napi,
						       droq->ops.farg);
				पूर्ण अन्यथा अणु
					recv_buffer_मुक्त(nicbuf);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (droq->refill_count >= droq->refill_threshold) अणु
			पूर्णांक desc_refilled = octeon_droq_refill(oct, droq);

			अगर (desc_refilled) अणु
				/* Flush the droq descriptor data to memory to
				 * be sure that when we update the credits the
				 * data in memory is accurate.
				 */
				wmb();
				ग_लिखोl(desc_refilled, droq->pkts_credit_reg);
			पूर्ण
		पूर्ण
	पूर्ण                       /* क्रम (each packet)... */

	/* Increment refill_count by the number of buffers processed. */
	droq->stats.pkts_received += pkt;
	droq->stats.bytes_received += total_len;

	retval = pkt;
	अगर ((droq->ops.drop_on_max) && (pkts_to_process - pkt)) अणु
		octeon_droq_drop_packets(oct, droq, (pkts_to_process - pkt));

		droq->stats.dropped_toomany += (pkts_to_process - pkt);
		retval = pkts_to_process;
	पूर्ण

	atomic_sub(retval, &droq->pkts_pending);

	अगर (droq->refill_count >= droq->refill_threshold &&
	    पढ़ोl(droq->pkts_credit_reg) < CN23XX_SLI_DEF_BP) अणु
		octeon_droq_check_hw_क्रम_pkts(droq);

		/* Make sure there are no pkts_pending */
		अगर (!atomic_पढ़ो(&droq->pkts_pending))
			octeon_schedule_rxq_oom_work(oct, droq);
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक
octeon_droq_process_packets(काष्ठा octeon_device *oct,
			    काष्ठा octeon_droq *droq,
			    u32 budget)
अणु
	u32 pkt_count = 0;
	काष्ठा list_head *पंचांगp, *पंचांगp2;

	octeon_droq_check_hw_क्रम_pkts(droq);
	pkt_count = atomic_पढ़ो(&droq->pkts_pending);

	अगर (!pkt_count)
		वापस 0;

	अगर (pkt_count > budget)
		pkt_count = budget;

	octeon_droq_fast_process_packets(oct, droq, pkt_count);

	list_क्रम_each_safe(पंचांगp, पंचांगp2, &droq->dispatch_list) अणु
		काष्ठा __dispatch *rdisp = (काष्ठा __dispatch *)पंचांगp;

		list_del(पंचांगp);
		rdisp->disp_fn(rdisp->rinfo,
			       octeon_get_dispatch_arg
			       (oct,
				(u16)rdisp->rinfo->recv_pkt->rh.r.opcode,
				(u16)rdisp->rinfo->recv_pkt->rh.r.subcode));
	पूर्ण

	/* If there are packets pending. schedule tasklet again */
	अगर (atomic_पढ़ो(&droq->pkts_pending))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Utility function to poll क्रम packets. check_hw_क्रम_packets must be
 * called beक्रमe calling this routine.
 */

पूर्णांक
octeon_droq_process_poll_pkts(काष्ठा octeon_device *oct,
			      काष्ठा octeon_droq *droq, u32 budget)
अणु
	काष्ठा list_head *पंचांगp, *पंचांगp2;
	u32 pkts_available = 0, pkts_processed = 0;
	u32 total_pkts_processed = 0;

	अगर (budget > droq->max_count)
		budget = droq->max_count;

	जबतक (total_pkts_processed < budget) अणु
		octeon_droq_check_hw_क्रम_pkts(droq);

		pkts_available = min((budget - total_pkts_processed),
				     (u32)(atomic_पढ़ो(&droq->pkts_pending)));

		अगर (pkts_available == 0)
			अवरोध;

		pkts_processed =
			octeon_droq_fast_process_packets(oct, droq,
							 pkts_available);

		total_pkts_processed += pkts_processed;
	पूर्ण

	list_क्रम_each_safe(पंचांगp, पंचांगp2, &droq->dispatch_list) अणु
		काष्ठा __dispatch *rdisp = (काष्ठा __dispatch *)पंचांगp;

		list_del(पंचांगp);
		rdisp->disp_fn(rdisp->rinfo,
			       octeon_get_dispatch_arg
			       (oct,
				(u16)rdisp->rinfo->recv_pkt->rh.r.opcode,
				(u16)rdisp->rinfo->recv_pkt->rh.r.subcode));
	पूर्ण

	वापस total_pkts_processed;
पूर्ण

/* Enable Pkt Interrupt */
पूर्णांक
octeon_enable_irq(काष्ठा octeon_device *oct, u32 q_no)
अणु
	चयन (oct->chip_id) अणु
	हाल OCTEON_CN66XX:
	हाल OCTEON_CN68XX: अणु
		काष्ठा octeon_cn6xxx *cn6xxx =
			(काष्ठा octeon_cn6xxx *)oct->chip;
		अचिन्हित दीर्घ flags;
		u32 value;

		spin_lock_irqsave
			(&cn6xxx->lock_क्रम_droq_पूर्णांक_enb_reg, flags);
		value = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB);
		value |= (1 << q_no);
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB, value);
		value = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB);
		value |= (1 << q_no);
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB, value);

		/* करोn't bother flushing the enables */

		spin_unlock_irqrestore
			(&cn6xxx->lock_क्रम_droq_पूर्णांक_enb_reg, flags);
	पूर्ण
		अवरोध;
	हाल OCTEON_CN23XX_PF_VID:
		lio_enable_irq(oct->droq[q_no], oct->instr_queue[q_no]);
		अवरोध;

	हाल OCTEON_CN23XX_VF_VID:
		lio_enable_irq(oct->droq[q_no], oct->instr_queue[q_no]);
		अवरोध;
	शेष:
		dev_err(&oct->pci_dev->dev, "%s Unknown Chip\n", __func__);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक octeon_रेजिस्टर_droq_ops(काष्ठा octeon_device *oct, u32 q_no,
			     काष्ठा octeon_droq_ops *ops)
अणु
	काष्ठा octeon_config *oct_cfg = शून्य;
	काष्ठा octeon_droq *droq;

	oct_cfg = octeon_get_conf(oct);

	अगर (!oct_cfg)
		वापस -EINVAL;

	अगर (!(ops)) अणु
		dev_err(&oct->pci_dev->dev, "%s: droq_ops pointer is NULL\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (q_no >= CFG_GET_OQ_MAX_Q(oct_cfg)) अणु
		dev_err(&oct->pci_dev->dev, "%s: droq id (%d) exceeds MAX (%d)\n",
			__func__, q_no, (oct->num_oqs - 1));
		वापस -EINVAL;
	पूर्ण

	droq = oct->droq[q_no];
	स_नकल(&droq->ops, ops, माप(काष्ठा octeon_droq_ops));

	वापस 0;
पूर्ण

पूर्णांक octeon_unरेजिस्टर_droq_ops(काष्ठा octeon_device *oct, u32 q_no)
अणु
	काष्ठा octeon_config *oct_cfg = शून्य;
	काष्ठा octeon_droq *droq;

	oct_cfg = octeon_get_conf(oct);

	अगर (!oct_cfg)
		वापस -EINVAL;

	अगर (q_no >= CFG_GET_OQ_MAX_Q(oct_cfg)) अणु
		dev_err(&oct->pci_dev->dev, "%s: droq id (%d) exceeds MAX (%d)\n",
			__func__, q_no, oct->num_oqs - 1);
		वापस -EINVAL;
	पूर्ण

	droq = oct->droq[q_no];

	अगर (!droq) अणु
		dev_info(&oct->pci_dev->dev,
			 "Droq id (%d) not available.\n", q_no);
		वापस 0;
	पूर्ण

	droq->ops.fptr = शून्य;
	droq->ops.farg = शून्य;
	droq->ops.drop_on_max = 0;

	वापस 0;
पूर्ण

पूर्णांक octeon_create_droq(काष्ठा octeon_device *oct,
		       u32 q_no, u32 num_descs,
		       u32 desc_size, व्योम *app_ctx)
अणु
	काष्ठा octeon_droq *droq;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	अगर (oct->droq[q_no]) अणु
		dev_dbg(&oct->pci_dev->dev, "Droq already in use. Cannot create droq %d again\n",
			q_no);
		वापस 1;
	पूर्ण

	/* Allocate the DS क्रम the new droq. */
	droq = vदो_स्मृति_node(माप(*droq), numa_node);
	अगर (!droq)
		droq = vदो_स्मृति(माप(*droq));
	अगर (!droq)
		वापस -1;

	स_रखो(droq, 0, माप(काष्ठा octeon_droq));

	/*Disable the pkt o/p क्रम this Q  */
	octeon_set_droq_pkt_op(oct, q_no, 0);
	oct->droq[q_no] = droq;

	/* Initialize the Droq */
	अगर (octeon_init_droq(oct, q_no, num_descs, desc_size, app_ctx)) अणु
		vमुक्त(oct->droq[q_no]);
		oct->droq[q_no] = शून्य;
		वापस -1;
	पूर्ण

	oct->num_oqs++;

	dev_dbg(&oct->pci_dev->dev, "%s: Total number of OQ: %d\n", __func__,
		oct->num_oqs);

	/* Global Droq रेजिस्टर settings */

	/* As of now not required, as setting are करोne क्रम all 32 Droqs at
	 * the same समय.
	 */
	वापस 0;
पूर्ण
