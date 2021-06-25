<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "dp_rx.h"
#समावेश "debug.h"
#समावेश "hif.h"

स्थिर काष्ठा ce_attr ath11k_host_ce_config_ipq8074[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 16,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE3: host->target WMI (mac0) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 2048,
		.src_sz_max = 256,
		.dest_nentries = 0,
	पूर्ण,

	/* CE5: target->host pktlog */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_dp_htt_htc_t2h_msg_handler,
	पूर्ण,

	/* CE6: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE7: host->target WMI (mac1) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE8: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE9: host->target WMI (mac2) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE10: target->host HTT */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE11: Not used */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा ce_attr ath11k_host_ce_config_qca6390[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 16,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE3: host->target WMI (mac0) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 2048,
		.src_sz_max = 256,
		.dest_nentries = 0,
	पूर्ण,

	/* CE5: target->host pktlog */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_dp_htt_htc_t2h_msg_handler,
	पूर्ण,

	/* CE6: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE7: host->target WMI (mac1) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE8: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

पूर्ण;

स्थिर काष्ठा ce_attr ath11k_host_ce_config_qcn9074[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 16,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 32,
		.recv_cb = ath11k_htc_rx_completion_handler,
	पूर्ण,

	/* CE3: host->target WMI (mac0) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 2048,
		.src_sz_max = 256,
		.dest_nentries = 0,
	पूर्ण,

	/* CE5: target->host pktlog */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath11k_dp_htt_htc_t2h_msg_handler,
	पूर्ण,
पूर्ण;

अटल bool ath11k_ce_need_shaकरोw_fix(पूर्णांक ce_id)
अणु
	/* only ce4 needs shaकरोw workaroud*/
	अगर (ce_id == 4)
		वापस true;
	वापस false;
पूर्ण

व्योम ath11k_ce_stop_shaकरोw_समयrs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++)
		अगर (ath11k_ce_need_shaकरोw_fix(i))
			ath11k_dp_shaकरोw_stop_समयr(ab, &ab->ce.hp_समयr[i]);
पूर्ण

अटल पूर्णांक ath11k_ce_rx_buf_enqueue_pipe(काष्ठा ath11k_ce_pipe *pipe,
					 काष्ठा sk_buff *skb, dma_addr_t paddr)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा ath11k_ce_ring *ring = pipe->dest_ring;
	काष्ठा hal_srng *srng;
	अचिन्हित पूर्णांक ग_लिखो_index;
	अचिन्हित पूर्णांक nentries_mask = ring->nentries_mask;
	u32 *desc;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ab->ce.ce_lock);

	ग_लिखो_index = ring->ग_लिखो_index;

	srng = &ab->hal.srng_list[ring->hal_ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	अगर (unlikely(ath11k_hal_srng_src_num_मुक्त(ab, srng, false) < 1)) अणु
		ret = -ENOSPC;
		जाओ निकास;
	पूर्ण

	desc = ath11k_hal_srng_src_get_next_entry(ab, srng);
	अगर (!desc) अणु
		ret = -ENOSPC;
		जाओ निकास;
	पूर्ण

	ath11k_hal_ce_dst_set_desc(desc, paddr);

	ring->skb[ग_लिखो_index] = skb;
	ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask, ग_लिखो_index);
	ring->ग_लिखो_index = ग_लिखो_index;

	pipe->rx_buf_needed--;

	ret = 0;
निकास:
	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_ce_rx_post_pipe(काष्ठा ath11k_ce_pipe *pipe)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret = 0;

	अगर (!(pipe->dest_ring || pipe->status_ring))
		वापस 0;

	spin_lock_bh(&ab->ce.ce_lock);
	जबतक (pipe->rx_buf_needed) अणु
		skb = dev_alloc_skb(pipe->buf_sz);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण

		WARN_ON_ONCE(!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4));

		paddr = dma_map_single(ab->dev, skb->data,
				       skb->len + skb_tailroom(skb),
				       DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(ab->dev, paddr))) अणु
			ath11k_warn(ab, "failed to dma map ce rx buf\n");
			dev_kमुक्त_skb_any(skb);
			ret = -EIO;
			जाओ निकास;
		पूर्ण

		ATH11K_SKB_RXCB(skb)->paddr = paddr;

		ret = ath11k_ce_rx_buf_enqueue_pipe(pipe, skb, paddr);

		अगर (ret) अणु
			ath11k_warn(ab, "failed to enqueue rx buf: %d\n", ret);
			dma_unmap_single(ab->dev, paddr,
					 skb->len + skb_tailroom(skb),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	spin_unlock_bh(&ab->ce.ce_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_ce_completed_recv_next(काष्ठा ath11k_ce_pipe *pipe,
					 काष्ठा sk_buff **skb, पूर्णांक *nbytes)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा hal_srng *srng;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक nentries_mask;
	u32 *desc;
	पूर्णांक ret = 0;

	spin_lock_bh(&ab->ce.ce_lock);

	sw_index = pipe->dest_ring->sw_index;
	nentries_mask = pipe->dest_ring->nentries_mask;

	srng = &ab->hal.srng_list[pipe->status_ring->hal_ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	desc = ath11k_hal_srng_dst_get_next_entry(ab, srng);
	अगर (!desc) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	*nbytes = ath11k_hal_ce_dst_status_get_length(desc);
	अगर (*nbytes == 0) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	*skb = pipe->dest_ring->skb[sw_index];
	pipe->dest_ring->skb[sw_index] = शून्य;

	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	pipe->dest_ring->sw_index = sw_index;

	pipe->rx_buf_needed++;
err:
	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	spin_unlock_bh(&ab->ce.ce_lock);

	वापस ret;
पूर्ण

अटल व्योम ath11k_ce_recv_process_cb(काष्ठा ath11k_ce_pipe *pipe)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head list;
	अचिन्हित पूर्णांक nbytes, max_nbytes;
	पूर्णांक ret;

	__skb_queue_head_init(&list);
	जबतक (ath11k_ce_completed_recv_next(pipe, &skb, &nbytes) == 0) अणु
		max_nbytes = skb->len + skb_tailroom(skb);
		dma_unmap_single(ab->dev, ATH11K_SKB_RXCB(skb)->paddr,
				 max_nbytes, DMA_FROM_DEVICE);

		अगर (unlikely(max_nbytes < nbytes)) अणु
			ath11k_warn(ab, "rxed more than expected (nbytes %d, max %d)",
				    nbytes, max_nbytes);
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		skb_put(skb, nbytes);
		__skb_queue_tail(&list, skb);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&list))) अणु
		ath11k_dbg(ab, ATH11K_DBG_AHB, "rx ce pipe %d len %d\n",
			   pipe->pipe_num, skb->len);
		pipe->recv_cb(ab, skb);
	पूर्ण

	ret = ath11k_ce_rx_post_pipe(pipe);
	अगर (ret && ret != -ENOSPC) अणु
		ath11k_warn(ab, "failed to post rx buf to pipe: %d err: %d\n",
			    pipe->pipe_num, ret);
		mod_समयr(&ab->rx_replenish_retry,
			  jअगरfies + ATH11K_CE_RX_POST_RETRY_JIFFIES);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *ath11k_ce_completed_send_next(काष्ठा ath11k_ce_pipe *pipe)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा hal_srng *srng;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक nentries_mask;
	काष्ठा sk_buff *skb;
	u32 *desc;

	spin_lock_bh(&ab->ce.ce_lock);

	sw_index = pipe->src_ring->sw_index;
	nentries_mask = pipe->src_ring->nentries_mask;

	srng = &ab->hal.srng_list[pipe->src_ring->hal_ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	desc = ath11k_hal_srng_src_reap_next(ab, srng);
	अगर (!desc) अणु
		skb = ERR_PTR(-EIO);
		जाओ err_unlock;
	पूर्ण

	skb = pipe->src_ring->skb[sw_index];

	pipe->src_ring->skb[sw_index] = शून्य;

	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	pipe->src_ring->sw_index = sw_index;

err_unlock:
	spin_unlock_bh(&srng->lock);

	spin_unlock_bh(&ab->ce.ce_lock);

	वापस skb;
पूर्ण

अटल व्योम ath11k_ce_send_करोne_cb(काष्ठा ath11k_ce_pipe *pipe)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा sk_buff *skb;

	जबतक (!IS_ERR(skb = ath11k_ce_completed_send_next(pipe))) अणु
		अगर (!skb)
			जारी;

		dma_unmap_single(ab->dev, ATH11K_SKB_CB(skb)->paddr, skb->len,
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ce_srng_msi_ring_params_setup(काष्ठा ath11k_base *ab, u32 ce_id,
						 काष्ठा hal_srng_params *ring_params)
अणु
	u32 msi_data_start;
	u32 msi_data_count, msi_data_idx;
	u32 msi_irq_start;
	u32 addr_lo;
	u32 addr_hi;
	पूर्णांक ret;

	ret = ath11k_get_user_msi_vector(ab, "CE",
					 &msi_data_count, &msi_data_start,
					 &msi_irq_start);

	अगर (ret)
		वापस;

	ath11k_get_msi_address(ab, &addr_lo, &addr_hi);
	ath11k_get_ce_msi_idx(ab, ce_id, &msi_data_idx);

	ring_params->msi_addr = addr_lo;
	ring_params->msi_addr |= (dma_addr_t)(((uपूर्णांक64_t)addr_hi) << 32);
	ring_params->msi_data = (msi_data_idx % msi_data_count) + msi_data_start;
	ring_params->flags |= HAL_SRNG_FLAGS_MSI_INTR;
पूर्ण

अटल पूर्णांक ath11k_ce_init_ring(काष्ठा ath11k_base *ab,
			       काष्ठा ath11k_ce_ring *ce_ring,
			       पूर्णांक ce_id, क्रमागत hal_ring_type type)
अणु
	काष्ठा hal_srng_params params = अणु 0 पूर्ण;
	पूर्णांक ret;

	params.ring_base_paddr = ce_ring->base_addr_ce_space;
	params.ring_base_vaddr = ce_ring->base_addr_owner_space;
	params.num_entries = ce_ring->nentries;

	अगर (!(CE_ATTR_DIS_INTR & ab->hw_params.host_ce_config[ce_id].flags))
		ath11k_ce_srng_msi_ring_params_setup(ab, ce_id, &params);

	चयन (type) अणु
	हाल HAL_CE_SRC:
		अगर (!(CE_ATTR_DIS_INTR & ab->hw_params.host_ce_config[ce_id].flags))
			params.पूर्णांकr_batch_cntr_thres_entries = 1;
		अवरोध;
	हाल HAL_CE_DST:
		params.max_buffer_len = ab->hw_params.host_ce_config[ce_id].src_sz_max;
		अगर (!(ab->hw_params.host_ce_config[ce_id].flags & CE_ATTR_DIS_INTR)) अणु
			params.पूर्णांकr_समयr_thres_us = 1024;
			params.flags |= HAL_SRNG_FLAGS_LOW_THRESH_INTR_EN;
			params.low_threshold = ce_ring->nentries - 3;
		पूर्ण
		अवरोध;
	हाल HAL_CE_DST_STATUS:
		अगर (!(ab->hw_params.host_ce_config[ce_id].flags & CE_ATTR_DIS_INTR)) अणु
			params.पूर्णांकr_batch_cntr_thres_entries = 1;
			params.पूर्णांकr_समयr_thres_us = 0x1000;
		पूर्ण
		अवरोध;
	शेष:
		ath11k_warn(ab, "Invalid CE ring type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	/* TODO: Init other params needed by HAL to init the ring */

	ret = ath11k_hal_srng_setup(ab, type, ce_id, 0, &params);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to setup srng: %d ring_id %d\n",
			    ret, ce_id);
		वापस ret;
	पूर्ण

	ce_ring->hal_ring_id = ret;

	अगर (ab->hw_params.supports_shaकरोw_regs &&
	    ath11k_ce_need_shaकरोw_fix(ce_id))
		ath11k_dp_shaकरोw_init_समयr(ab, &ab->ce.hp_समयr[ce_id],
					    ATH11K_SHADOW_CTRL_TIMER_INTERVAL,
					    ce_ring->hal_ring_id);

	वापस 0;
पूर्ण

अटल काष्ठा ath11k_ce_ring *
ath11k_ce_alloc_ring(काष्ठा ath11k_base *ab, पूर्णांक nentries, पूर्णांक desc_sz)
अणु
	काष्ठा ath11k_ce_ring *ce_ring;
	dma_addr_t base_addr;

	ce_ring = kzalloc(काष्ठा_size(ce_ring, skb, nentries), GFP_KERNEL);
	अगर (ce_ring == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ce_ring->nentries = nentries;
	ce_ring->nentries_mask = nentries - 1;

	/* Legacy platक्रमms that करो not support cache
	 * coherent DMA are unsupported
	 */
	ce_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ab->dev,
				   nentries * desc_sz + CE_DESC_RING_ALIGN,
				   &base_addr, GFP_KERNEL);
	अगर (!ce_ring->base_addr_owner_space_unaligned) अणु
		kमुक्त(ce_ring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ce_ring->base_addr_ce_space_unaligned = base_addr;

	ce_ring->base_addr_owner_space = PTR_ALIGN(
			ce_ring->base_addr_owner_space_unaligned,
			CE_DESC_RING_ALIGN);
	ce_ring->base_addr_ce_space = ALIGN(
			ce_ring->base_addr_ce_space_unaligned,
			CE_DESC_RING_ALIGN);

	वापस ce_ring;
पूर्ण

अटल पूर्णांक ath11k_ce_alloc_pipe(काष्ठा ath11k_base *ab, पूर्णांक ce_id)
अणु
	काष्ठा ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[ce_id];
	स्थिर काष्ठा ce_attr *attr = &ab->hw_params.host_ce_config[ce_id];
	काष्ठा ath11k_ce_ring *ring;
	पूर्णांक nentries;
	पूर्णांक desc_sz;

	pipe->attr_flags = attr->flags;

	अगर (attr->src_nentries) अणु
		pipe->send_cb = ath11k_ce_send_करोne_cb;
		nentries = roundup_घात_of_two(attr->src_nentries);
		desc_sz = ath11k_hal_ce_get_desc_size(HAL_CE_DESC_SRC);
		ring = ath11k_ce_alloc_ring(ab, nentries, desc_sz);
		अगर (IS_ERR(ring))
			वापस PTR_ERR(ring);
		pipe->src_ring = ring;
	पूर्ण

	अगर (attr->dest_nentries) अणु
		pipe->recv_cb = attr->recv_cb;
		nentries = roundup_घात_of_two(attr->dest_nentries);
		desc_sz = ath11k_hal_ce_get_desc_size(HAL_CE_DESC_DST);
		ring = ath11k_ce_alloc_ring(ab, nentries, desc_sz);
		अगर (IS_ERR(ring))
			वापस PTR_ERR(ring);
		pipe->dest_ring = ring;

		desc_sz = ath11k_hal_ce_get_desc_size(HAL_CE_DESC_DST_STATUS);
		ring = ath11k_ce_alloc_ring(ab, nentries, desc_sz);
		अगर (IS_ERR(ring))
			वापस PTR_ERR(ring);
		pipe->status_ring = ring;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_ce_per_engine_service(काष्ठा ath11k_base *ab, u16 ce_id)
अणु
	काष्ठा ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[ce_id];

	अगर (pipe->send_cb)
		pipe->send_cb(pipe);

	अगर (pipe->recv_cb)
		ath11k_ce_recv_process_cb(pipe);
पूर्ण

व्योम ath11k_ce_poll_send_completed(काष्ठा ath11k_base *ab, u8 pipe_id)
अणु
	काष्ठा ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[pipe_id];

	अगर ((pipe->attr_flags & CE_ATTR_DIS_INTR) && pipe->send_cb)
		pipe->send_cb(pipe);
पूर्ण
EXPORT_SYMBOL(ath11k_ce_per_engine_service);

पूर्णांक ath11k_ce_send(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb, u8 pipe_id,
		   u16 transfer_id)
अणु
	काष्ठा ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[pipe_id];
	काष्ठा hal_srng *srng;
	u32 *desc;
	अचिन्हित पूर्णांक ग_लिखो_index, sw_index;
	अचिन्हित पूर्णांक nentries_mask;
	पूर्णांक ret = 0;
	u8 byte_swap_data = 0;
	पूर्णांक num_used;

	/* Check अगर some entries could be regained by handling tx completion अगर
	 * the CE has पूर्णांकerrupts disabled and the used entries is more than the
	 * defined usage threshold.
	 */
	अगर (pipe->attr_flags & CE_ATTR_DIS_INTR) अणु
		spin_lock_bh(&ab->ce.ce_lock);
		ग_लिखो_index = pipe->src_ring->ग_लिखो_index;

		sw_index = pipe->src_ring->sw_index;

		अगर (ग_लिखो_index >= sw_index)
			num_used = ग_लिखो_index - sw_index;
		अन्यथा
			num_used = pipe->src_ring->nentries - sw_index +
				   ग_लिखो_index;

		spin_unlock_bh(&ab->ce.ce_lock);

		अगर (num_used > ATH11K_CE_USAGE_THRESHOLD)
			ath11k_ce_poll_send_completed(ab, pipe->pipe_num);
	पूर्ण

	अगर (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags))
		वापस -ESHUTDOWN;

	spin_lock_bh(&ab->ce.ce_lock);

	ग_लिखो_index = pipe->src_ring->ग_लिखो_index;
	nentries_mask = pipe->src_ring->nentries_mask;

	srng = &ab->hal.srng_list[pipe->src_ring->hal_ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	अगर (unlikely(ath11k_hal_srng_src_num_मुक्त(ab, srng, false) < 1)) अणु
		ath11k_hal_srng_access_end(ab, srng);
		ret = -ENOBUFS;
		जाओ err_unlock;
	पूर्ण

	desc = ath11k_hal_srng_src_get_next_reaped(ab, srng);
	अगर (!desc) अणु
		ath11k_hal_srng_access_end(ab, srng);
		ret = -ENOBUFS;
		जाओ err_unlock;
	पूर्ण

	अगर (pipe->attr_flags & CE_ATTR_BYTE_SWAP_DATA)
		byte_swap_data = 1;

	ath11k_hal_ce_src_set_desc(desc, ATH11K_SKB_CB(skb)->paddr,
				   skb->len, transfer_id, byte_swap_data);

	pipe->src_ring->skb[ग_लिखो_index] = skb;
	pipe->src_ring->ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask,
						       ग_लिखो_index);

	ath11k_hal_srng_access_end(ab, srng);

	अगर (ath11k_ce_need_shaकरोw_fix(pipe_id))
		ath11k_dp_shaकरोw_start_समयr(ab, srng, &ab->ce.hp_समयr[pipe_id]);

	spin_unlock_bh(&srng->lock);

	spin_unlock_bh(&ab->ce.ce_lock);

	वापस 0;

err_unlock:
	spin_unlock_bh(&srng->lock);

	spin_unlock_bh(&ab->ce.ce_lock);

	वापस ret;
पूर्ण

अटल व्योम ath11k_ce_rx_pipe_cleanup(काष्ठा ath11k_ce_pipe *pipe)
अणु
	काष्ठा ath11k_base *ab = pipe->ab;
	काष्ठा ath11k_ce_ring *ring = pipe->dest_ring;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	अगर (!(ring && pipe->buf_sz))
		वापस;

	क्रम (i = 0; i < ring->nentries; i++) अणु
		skb = ring->skb[i];
		अगर (!skb)
			जारी;

		ring->skb[i] = शून्य;
		dma_unmap_single(ab->dev, ATH11K_SKB_RXCB(skb)->paddr,
				 skb->len + skb_tailroom(skb), DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ce_shaकरोw_config(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ab->hw_params.host_ce_config[i].src_nentries)
			ath11k_hal_srng_update_shaकरोw_config(ab,
							     HAL_CE_SRC, i);

		अगर (ab->hw_params.host_ce_config[i].dest_nentries) अणु
			ath11k_hal_srng_update_shaकरोw_config(ab,
							     HAL_CE_DST, i);

			ath11k_hal_srng_update_shaकरोw_config(ab,
							     HAL_CE_DST_STATUS, i);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath11k_ce_get_shaकरोw_config(काष्ठा ath11k_base *ab,
				 u32 **shaकरोw_cfg, u32 *shaकरोw_cfg_len)
अणु
	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	ath11k_hal_srng_get_shaकरोw_config(ab, shaकरोw_cfg, shaकरोw_cfg_len);

	/* shaकरोw is alपढ़ोy configured */
	अगर (*shaकरोw_cfg_len)
		वापस;

	/* shaकरोw isn't configured yet, configure now.
	 * non-CE srngs are configured firstly, then
	 * all CE srngs.
	 */
	ath11k_hal_srng_shaकरोw_config(ab);
	ath11k_ce_shaकरोw_config(ab);

	/* get the shaकरोw configuration */
	ath11k_hal_srng_get_shaकरोw_config(ab, shaकरोw_cfg, shaकरोw_cfg_len);
पूर्ण
EXPORT_SYMBOL(ath11k_ce_get_shaकरोw_config);

व्योम ath11k_ce_cleanup_pipes(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *pipe;
	पूर्णांक pipe_num;

	ath11k_ce_stop_shaकरोw_समयrs(ab);

	क्रम (pipe_num = 0; pipe_num < ab->hw_params.ce_count; pipe_num++) अणु
		pipe = &ab->ce.ce_pipe[pipe_num];
		ath11k_ce_rx_pipe_cleanup(pipe);

		/* Cleanup any src CE's which have पूर्णांकerrupts disabled */
		ath11k_ce_poll_send_completed(ab, pipe_num);

		/* NOTE: Should we also clean up tx buffer in all pipes? */
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath11k_ce_cleanup_pipes);

व्योम ath11k_ce_rx_post_buf(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *pipe;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		pipe = &ab->ce.ce_pipe[i];
		ret = ath11k_ce_rx_post_pipe(pipe);
		अगर (ret) अणु
			अगर (ret == -ENOSPC)
				जारी;

			ath11k_warn(ab, "failed to post rx buf to pipe: %d err: %d\n",
				    i, ret);
			mod_समयr(&ab->rx_replenish_retry,
				  jअगरfies + ATH11K_CE_RX_POST_RETRY_JIFFIES);

			वापस;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath11k_ce_rx_post_buf);

व्योम ath11k_ce_rx_replenish_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा ath11k_base *ab = from_समयr(ab, t, rx_replenish_retry);

	ath11k_ce_rx_post_buf(ab);
पूर्ण

पूर्णांक ath11k_ce_init_pipes(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *pipe;
	पूर्णांक i;
	पूर्णांक ret;

	ath11k_ce_get_shaकरोw_config(ab, &ab->qmi.ce_cfg.shaकरोw_reg_v2,
				    &ab->qmi.ce_cfg.shaकरोw_reg_v2_len);

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		pipe = &ab->ce.ce_pipe[i];

		अगर (pipe->src_ring) अणु
			ret = ath11k_ce_init_ring(ab, pipe->src_ring, i,
						  HAL_CE_SRC);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to init src ring: %d\n",
					    ret);
				/* Should we clear any partial init */
				वापस ret;
			पूर्ण

			pipe->src_ring->ग_लिखो_index = 0;
			pipe->src_ring->sw_index = 0;
		पूर्ण

		अगर (pipe->dest_ring) अणु
			ret = ath11k_ce_init_ring(ab, pipe->dest_ring, i,
						  HAL_CE_DST);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to init dest ring: %d\n",
					    ret);
				/* Should we clear any partial init */
				वापस ret;
			पूर्ण

			pipe->rx_buf_needed = pipe->dest_ring->nentries ?
					      pipe->dest_ring->nentries - 2 : 0;

			pipe->dest_ring->ग_लिखो_index = 0;
			pipe->dest_ring->sw_index = 0;
		पूर्ण

		अगर (pipe->status_ring) अणु
			ret = ath11k_ce_init_ring(ab, pipe->status_ring, i,
						  HAL_CE_DST_STATUS);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to init dest status ing: %d\n",
					    ret);
				/* Should we clear any partial init */
				वापस ret;
			पूर्ण

			pipe->status_ring->ग_लिखो_index = 0;
			pipe->status_ring->sw_index = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_ce_मुक्त_pipes(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *pipe;
	पूर्णांक desc_sz;
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		pipe = &ab->ce.ce_pipe[i];

		अगर (ath11k_ce_need_shaकरोw_fix(i))
			ath11k_dp_shaकरोw_stop_समयr(ab, &ab->ce.hp_समयr[i]);

		अगर (pipe->src_ring) अणु
			desc_sz = ath11k_hal_ce_get_desc_size(HAL_CE_DESC_SRC);
			dma_मुक्त_coherent(ab->dev,
					  pipe->src_ring->nentries * desc_sz +
					  CE_DESC_RING_ALIGN,
					  pipe->src_ring->base_addr_owner_space,
					  pipe->src_ring->base_addr_ce_space);
			kमुक्त(pipe->src_ring);
			pipe->src_ring = शून्य;
		पूर्ण

		अगर (pipe->dest_ring) अणु
			desc_sz = ath11k_hal_ce_get_desc_size(HAL_CE_DESC_DST);
			dma_मुक्त_coherent(ab->dev,
					  pipe->dest_ring->nentries * desc_sz +
					  CE_DESC_RING_ALIGN,
					  pipe->dest_ring->base_addr_owner_space,
					  pipe->dest_ring->base_addr_ce_space);
			kमुक्त(pipe->dest_ring);
			pipe->dest_ring = शून्य;
		पूर्ण

		अगर (pipe->status_ring) अणु
			desc_sz =
			  ath11k_hal_ce_get_desc_size(HAL_CE_DESC_DST_STATUS);
			dma_मुक्त_coherent(ab->dev,
					  pipe->status_ring->nentries * desc_sz +
					  CE_DESC_RING_ALIGN,
					  pipe->status_ring->base_addr_owner_space,
					  pipe->status_ring->base_addr_ce_space);
			kमुक्त(pipe->status_ring);
			pipe->status_ring = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath11k_ce_मुक्त_pipes);

पूर्णांक ath11k_ce_alloc_pipes(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *pipe;
	पूर्णांक i;
	पूर्णांक ret;
	स्थिर काष्ठा ce_attr *attr;

	spin_lock_init(&ab->ce.ce_lock);

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		attr = &ab->hw_params.host_ce_config[i];
		pipe = &ab->ce.ce_pipe[i];
		pipe->pipe_num = i;
		pipe->ab = ab;
		pipe->buf_sz = attr->src_sz_max;

		ret = ath11k_ce_alloc_pipe(ab, i);
		अगर (ret) अणु
			/* Free any parial successful allocation */
			ath11k_ce_मुक्त_pipes(ab);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath11k_ce_alloc_pipes);

/* For Big Endian Host, Copy Engine byte_swap is enabled
 * When Copy Engine करोes byte_swap, need to byte swap again क्रम the
 * Host to get/put buffer content in the correct byte order
 */
व्योम ath11k_ce_byte_swap(व्योम *mem, u32 len)
अणु
	पूर्णांक i;

	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)) अणु
		अगर (!mem)
			वापस;

		क्रम (i = 0; i < (len / 4); i++) अणु
			*(u32 *)mem = swab32(*(u32 *)mem);
			mem += 4;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ath11k_ce_get_attr_flags(काष्ठा ath11k_base *ab, पूर्णांक ce_id)
अणु
	अगर (ce_id >= ab->hw_params.ce_count)
		वापस -EINVAL;

	वापस ab->hw_params.host_ce_config[ce_id].flags;
पूर्ण
EXPORT_SYMBOL(ath11k_ce_get_attr_flags);
