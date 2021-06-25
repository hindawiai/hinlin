<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश "ena_eth_com.h"

अटल काष्ठा ena_eth_io_rx_cdesc_base *ena_com_get_next_rx_cdesc(
	काष्ठा ena_com_io_cq *io_cq)
अणु
	काष्ठा ena_eth_io_rx_cdesc_base *cdesc;
	u16 expected_phase, head_masked;
	u16 desc_phase;

	head_masked = io_cq->head & (io_cq->q_depth - 1);
	expected_phase = io_cq->phase;

	cdesc = (काष्ठा ena_eth_io_rx_cdesc_base *)(io_cq->cdesc_addr.virt_addr
			+ (head_masked * io_cq->cdesc_entry_size_in_bytes));

	desc_phase = (READ_ONCE(cdesc->status) &
		      ENA_ETH_IO_RX_CDESC_BASE_PHASE_MASK) >>
		     ENA_ETH_IO_RX_CDESC_BASE_PHASE_SHIFT;

	अगर (desc_phase != expected_phase)
		वापस शून्य;

	/* Make sure we पढ़ो the rest of the descriptor after the phase bit
	 * has been पढ़ो
	 */
	dma_rmb();

	वापस cdesc;
पूर्ण

अटल व्योम *get_sq_desc_regular_queue(काष्ठा ena_com_io_sq *io_sq)
अणु
	u16 tail_masked;
	u32 offset;

	tail_masked = io_sq->tail & (io_sq->q_depth - 1);

	offset = tail_masked * io_sq->desc_entry_size;

	वापस (व्योम *)((uपूर्णांकptr_t)io_sq->desc_addr.virt_addr + offset);
पूर्ण

अटल पूर्णांक ena_com_ग_लिखो_bounce_buffer_to_dev(काष्ठा ena_com_io_sq *io_sq,
						     u8 *bounce_buffer)
अणु
	काष्ठा ena_com_llq_info *llq_info = &io_sq->llq_info;

	u16 dst_tail_mask;
	u32 dst_offset;

	dst_tail_mask = io_sq->tail & (io_sq->q_depth - 1);
	dst_offset = dst_tail_mask * llq_info->desc_list_entry_size;

	अगर (is_llq_max_tx_burst_exists(io_sq)) अणु
		अगर (unlikely(!io_sq->entries_in_tx_burst_left)) अणु
			netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
				   "Error: trying to send more packets than tx burst allows\n");
			वापस -ENOSPC;
		पूर्ण

		io_sq->entries_in_tx_burst_left--;
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Decreasing entries_in_tx_burst_left of queue %d to %d\n",
			   io_sq->qid, io_sq->entries_in_tx_burst_left);
	पूर्ण

	/* Make sure everything was written पूर्णांकo the bounce buffer beक्रमe
	 * writing the bounce buffer to the device
	 */
	wmb();

	/* The line is completed. Copy it to dev */
	__ioग_लिखो64_copy(io_sq->desc_addr.pbuf_dev_addr + dst_offset,
			 bounce_buffer, (llq_info->desc_list_entry_size) / 8);

	io_sq->tail++;

	/* Switch phase bit in हाल of wrap around */
	अगर (unlikely((io_sq->tail & (io_sq->q_depth - 1)) == 0))
		io_sq->phase ^= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_ग_लिखो_header_to_bounce(काष्ठा ena_com_io_sq *io_sq,
						 u8 *header_src,
						 u16 header_len)
अणु
	काष्ठा ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	काष्ठा ena_com_llq_info *llq_info = &io_sq->llq_info;
	u8 *bounce_buffer = pkt_ctrl->curr_bounce_buf;
	u16 header_offset;

	अगर (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST))
		वापस 0;

	header_offset =
		llq_info->descs_num_beक्रमe_header * io_sq->desc_entry_size;

	अगर (unlikely((header_offset + header_len) >
		     llq_info->desc_list_entry_size)) अणु
		netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Trying to write header larger than llq entry can accommodate\n");
		वापस -EFAULT;
	पूर्ण

	अगर (unlikely(!bounce_buffer)) अणु
		netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Bounce buffer is NULL\n");
		वापस -EFAULT;
	पूर्ण

	स_नकल(bounce_buffer + header_offset, header_src, header_len);

	वापस 0;
पूर्ण

अटल व्योम *get_sq_desc_llq(काष्ठा ena_com_io_sq *io_sq)
अणु
	काष्ठा ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	u8 *bounce_buffer;
	व्योम *sq_desc;

	bounce_buffer = pkt_ctrl->curr_bounce_buf;

	अगर (unlikely(!bounce_buffer)) अणु
		netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Bounce buffer is NULL\n");
		वापस शून्य;
	पूर्ण

	sq_desc = bounce_buffer + pkt_ctrl->idx * io_sq->desc_entry_size;
	pkt_ctrl->idx++;
	pkt_ctrl->descs_left_in_line--;

	वापस sq_desc;
पूर्ण

अटल पूर्णांक ena_com_बंद_bounce_buffer(काष्ठा ena_com_io_sq *io_sq)
अणु
	काष्ठा ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	काष्ठा ena_com_llq_info *llq_info = &io_sq->llq_info;
	पूर्णांक rc;

	अगर (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST))
		वापस 0;

	/* bounce buffer was used, so ग_लिखो it and get a new one */
	अगर (pkt_ctrl->idx) अणु
		rc = ena_com_ग_लिखो_bounce_buffer_to_dev(io_sq,
							pkt_ctrl->curr_bounce_buf);
		अगर (unlikely(rc))
			वापस rc;

		pkt_ctrl->curr_bounce_buf =
			ena_com_get_next_bounce_buffer(&io_sq->bounce_buf_ctrl);
		स_रखो(io_sq->llq_buf_ctrl.curr_bounce_buf,
		       0x0, llq_info->desc_list_entry_size);
	पूर्ण

	pkt_ctrl->idx = 0;
	pkt_ctrl->descs_left_in_line = llq_info->descs_num_beक्रमe_header;
	वापस 0;
पूर्ण

अटल व्योम *get_sq_desc(काष्ठा ena_com_io_sq *io_sq)
अणु
	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		वापस get_sq_desc_llq(io_sq);

	वापस get_sq_desc_regular_queue(io_sq);
पूर्ण

अटल पूर्णांक ena_com_sq_update_llq_tail(काष्ठा ena_com_io_sq *io_sq)
अणु
	काष्ठा ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	काष्ठा ena_com_llq_info *llq_info = &io_sq->llq_info;
	पूर्णांक rc;

	अगर (!pkt_ctrl->descs_left_in_line) अणु
		rc = ena_com_ग_लिखो_bounce_buffer_to_dev(io_sq,
							pkt_ctrl->curr_bounce_buf);
		अगर (unlikely(rc))
			वापस rc;

		pkt_ctrl->curr_bounce_buf =
			ena_com_get_next_bounce_buffer(&io_sq->bounce_buf_ctrl);
		स_रखो(io_sq->llq_buf_ctrl.curr_bounce_buf,
		       0x0, llq_info->desc_list_entry_size);

		pkt_ctrl->idx = 0;
		अगर (unlikely(llq_info->desc_stride_ctrl == ENA_ADMIN_SINGLE_DESC_PER_ENTRY))
			pkt_ctrl->descs_left_in_line = 1;
		अन्यथा
			pkt_ctrl->descs_left_in_line =
			llq_info->desc_list_entry_size / io_sq->desc_entry_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_sq_update_tail(काष्ठा ena_com_io_sq *io_sq)
अणु
	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		वापस ena_com_sq_update_llq_tail(io_sq);

	io_sq->tail++;

	/* Switch phase bit in हाल of wrap around */
	अगर (unlikely((io_sq->tail & (io_sq->q_depth - 1)) == 0))
		io_sq->phase ^= 1;

	वापस 0;
पूर्ण

अटल काष्ठा ena_eth_io_rx_cdesc_base *
	ena_com_rx_cdesc_idx_to_ptr(काष्ठा ena_com_io_cq *io_cq, u16 idx)
अणु
	idx &= (io_cq->q_depth - 1);
	वापस (काष्ठा ena_eth_io_rx_cdesc_base *)
		((uपूर्णांकptr_t)io_cq->cdesc_addr.virt_addr +
		idx * io_cq->cdesc_entry_size_in_bytes);
पूर्ण

अटल u16 ena_com_cdesc_rx_pkt_get(काष्ठा ena_com_io_cq *io_cq,
					   u16 *first_cdesc_idx)
अणु
	काष्ठा ena_eth_io_rx_cdesc_base *cdesc;
	u16 count = 0, head_masked;
	u32 last = 0;

	करो अणु
		cdesc = ena_com_get_next_rx_cdesc(io_cq);
		अगर (!cdesc)
			अवरोध;

		ena_com_cq_inc_head(io_cq);
		count++;
		last = (READ_ONCE(cdesc->status) &
			ENA_ETH_IO_RX_CDESC_BASE_LAST_MASK) >>
		       ENA_ETH_IO_RX_CDESC_BASE_LAST_SHIFT;
	पूर्ण जबतक (!last);

	अगर (last) अणु
		*first_cdesc_idx = io_cq->cur_rx_pkt_cdesc_start_idx;
		count += io_cq->cur_rx_pkt_cdesc_count;

		head_masked = io_cq->head & (io_cq->q_depth - 1);

		io_cq->cur_rx_pkt_cdesc_count = 0;
		io_cq->cur_rx_pkt_cdesc_start_idx = head_masked;

		netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "ENA q_id: %d packets were completed. first desc idx %u descs# %d\n",
			   io_cq->qid, *first_cdesc_idx, count);
	पूर्ण अन्यथा अणु
		io_cq->cur_rx_pkt_cdesc_count += count;
		count = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक ena_com_create_meta(काष्ठा ena_com_io_sq *io_sq,
			       काष्ठा ena_com_tx_meta *ena_meta)
अणु
	काष्ठा ena_eth_io_tx_meta_desc *meta_desc = शून्य;

	meta_desc = get_sq_desc(io_sq);
	अगर (unlikely(!meta_desc))
		वापस -EFAULT;

	स_रखो(meta_desc, 0x0, माप(काष्ठा ena_eth_io_tx_meta_desc));

	meta_desc->len_ctrl |= ENA_ETH_IO_TX_META_DESC_META_DESC_MASK;

	meta_desc->len_ctrl |= ENA_ETH_IO_TX_META_DESC_EXT_VALID_MASK;

	/* bits 0-9 of the mss */
	meta_desc->word2 |= ((u32)ena_meta->mss <<
		ENA_ETH_IO_TX_META_DESC_MSS_LO_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_MSS_LO_MASK;
	/* bits 10-13 of the mss */
	meta_desc->len_ctrl |= ((ena_meta->mss >> 10) <<
		ENA_ETH_IO_TX_META_DESC_MSS_HI_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_MSS_HI_MASK;

	/* Extended meta desc */
	meta_desc->len_ctrl |= ENA_ETH_IO_TX_META_DESC_ETH_META_TYPE_MASK;
	meta_desc->len_ctrl |= ((u32)io_sq->phase <<
		ENA_ETH_IO_TX_META_DESC_PHASE_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_PHASE_MASK;

	meta_desc->len_ctrl |= ENA_ETH_IO_TX_META_DESC_FIRST_MASK;
	meta_desc->len_ctrl |= ENA_ETH_IO_TX_META_DESC_META_STORE_MASK;

	meta_desc->word2 |= ena_meta->l3_hdr_len &
		ENA_ETH_IO_TX_META_DESC_L3_HDR_LEN_MASK;
	meta_desc->word2 |= (ena_meta->l3_hdr_offset <<
		ENA_ETH_IO_TX_META_DESC_L3_HDR_OFF_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_L3_HDR_OFF_MASK;

	meta_desc->word2 |= ((u32)ena_meta->l4_hdr_len <<
		ENA_ETH_IO_TX_META_DESC_L4_HDR_LEN_IN_WORDS_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_L4_HDR_LEN_IN_WORDS_MASK;

	वापस ena_com_sq_update_tail(io_sq);
पूर्ण

अटल पूर्णांक ena_com_create_and_store_tx_meta_desc(काष्ठा ena_com_io_sq *io_sq,
						 काष्ठा ena_com_tx_ctx *ena_tx_ctx,
						 bool *have_meta)
अणु
	काष्ठा ena_com_tx_meta *ena_meta = &ena_tx_ctx->ena_meta;

	/* When disable meta caching is set, करोn't bother to save the meta and
	 * compare it to the stored version, just create the meta
	 */
	अगर (io_sq->disable_meta_caching) अणु
		अगर (unlikely(!ena_tx_ctx->meta_valid))
			वापस -EINVAL;

		*have_meta = true;
		वापस ena_com_create_meta(io_sq, ena_meta);
	पूर्ण

	अगर (ena_com_meta_desc_changed(io_sq, ena_tx_ctx)) अणु
		*have_meta = true;
		/* Cache the meta desc */
		स_नकल(&io_sq->cached_tx_meta, ena_meta,
		       माप(काष्ठा ena_com_tx_meta));
		वापस ena_com_create_meta(io_sq, ena_meta);
	पूर्ण

	*have_meta = false;
	वापस 0;
पूर्ण

अटल व्योम ena_com_rx_set_flags(काष्ठा ena_com_io_cq *io_cq,
				 काष्ठा ena_com_rx_ctx *ena_rx_ctx,
				 काष्ठा ena_eth_io_rx_cdesc_base *cdesc)
अणु
	ena_rx_ctx->l3_proto = cdesc->status &
		ENA_ETH_IO_RX_CDESC_BASE_L3_PROTO_IDX_MASK;
	ena_rx_ctx->l4_proto =
		(cdesc->status & ENA_ETH_IO_RX_CDESC_BASE_L4_PROTO_IDX_MASK) >>
		ENA_ETH_IO_RX_CDESC_BASE_L4_PROTO_IDX_SHIFT;
	ena_rx_ctx->l3_csum_err =
		!!((cdesc->status & ENA_ETH_IO_RX_CDESC_BASE_L3_CSUM_ERR_MASK) >>
		ENA_ETH_IO_RX_CDESC_BASE_L3_CSUM_ERR_SHIFT);
	ena_rx_ctx->l4_csum_err =
		!!((cdesc->status & ENA_ETH_IO_RX_CDESC_BASE_L4_CSUM_ERR_MASK) >>
		ENA_ETH_IO_RX_CDESC_BASE_L4_CSUM_ERR_SHIFT);
	ena_rx_ctx->l4_csum_checked =
		!!((cdesc->status & ENA_ETH_IO_RX_CDESC_BASE_L4_CSUM_CHECKED_MASK) >>
		ENA_ETH_IO_RX_CDESC_BASE_L4_CSUM_CHECKED_SHIFT);
	ena_rx_ctx->hash = cdesc->hash;
	ena_rx_ctx->frag =
		(cdesc->status & ENA_ETH_IO_RX_CDESC_BASE_IPV4_FRAG_MASK) >>
		ENA_ETH_IO_RX_CDESC_BASE_IPV4_FRAG_SHIFT;

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "l3_proto %d l4_proto %d l3_csum_err %d l4_csum_err %d hash %d frag %d cdesc_status %x\n",
		   ena_rx_ctx->l3_proto, ena_rx_ctx->l4_proto,
		   ena_rx_ctx->l3_csum_err, ena_rx_ctx->l4_csum_err,
		   ena_rx_ctx->hash, ena_rx_ctx->frag, cdesc->status);
पूर्ण

/*****************************************************************************/
/*****************************     API      **********************************/
/*****************************************************************************/

पूर्णांक ena_com_prepare_tx(काष्ठा ena_com_io_sq *io_sq,
		       काष्ठा ena_com_tx_ctx *ena_tx_ctx,
		       पूर्णांक *nb_hw_desc)
अणु
	काष्ठा ena_eth_io_tx_desc *desc = शून्य;
	काष्ठा ena_com_buf *ena_bufs = ena_tx_ctx->ena_bufs;
	व्योम *buffer_to_push = ena_tx_ctx->push_header;
	u16 header_len = ena_tx_ctx->header_len;
	u16 num_bufs = ena_tx_ctx->num_bufs;
	u16 start_tail = io_sq->tail;
	पूर्णांक i, rc;
	bool have_meta;
	u64 addr_hi;

	WARN(io_sq->direction != ENA_COM_IO_QUEUE_सूचीECTION_TX, "wrong Q type");

	/* num_bufs +1 क्रम potential meta desc */
	अगर (unlikely(!ena_com_sq_have_enough_space(io_sq, num_bufs + 1))) अणु
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Not enough space in the tx queue\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (unlikely(header_len > io_sq->tx_max_header_size)) अणु
		netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Header size is too large %d max header: %d\n",
			   header_len, io_sq->tx_max_header_size);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV &&
		     !buffer_to_push))
		वापस -EINVAL;

	rc = ena_com_ग_लिखो_header_to_bounce(io_sq, buffer_to_push, header_len);
	अगर (unlikely(rc))
		वापस rc;

	rc = ena_com_create_and_store_tx_meta_desc(io_sq, ena_tx_ctx, &have_meta);
	अगर (unlikely(rc)) अणु
		netdev_err(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Failed to create and store tx meta desc\n");
		वापस rc;
	पूर्ण

	/* If the caller करोesn't want to send packets */
	अगर (unlikely(!num_bufs && !header_len)) अणु
		rc = ena_com_बंद_bounce_buffer(io_sq);
		*nb_hw_desc = io_sq->tail - start_tail;
		वापस rc;
	पूर्ण

	desc = get_sq_desc(io_sq);
	अगर (unlikely(!desc))
		वापस -EFAULT;
	स_रखो(desc, 0x0, माप(काष्ठा ena_eth_io_tx_desc));

	/* Set first desc when we करोn't have meta descriptor */
	अगर (!have_meta)
		desc->len_ctrl |= ENA_ETH_IO_TX_DESC_FIRST_MASK;

	desc->buff_addr_hi_hdr_sz |= ((u32)header_len <<
		ENA_ETH_IO_TX_DESC_HEADER_LENGTH_SHIFT) &
		ENA_ETH_IO_TX_DESC_HEADER_LENGTH_MASK;
	desc->len_ctrl |= ((u32)io_sq->phase << ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
		ENA_ETH_IO_TX_DESC_PHASE_MASK;

	desc->len_ctrl |= ENA_ETH_IO_TX_DESC_COMP_REQ_MASK;

	/* Bits 0-9 */
	desc->meta_ctrl |= ((u32)ena_tx_ctx->req_id <<
		ENA_ETH_IO_TX_DESC_REQ_ID_LO_SHIFT) &
		ENA_ETH_IO_TX_DESC_REQ_ID_LO_MASK;

	desc->meta_ctrl |= (ena_tx_ctx->df <<
		ENA_ETH_IO_TX_DESC_DF_SHIFT) &
		ENA_ETH_IO_TX_DESC_DF_MASK;

	/* Bits 10-15 */
	desc->len_ctrl |= ((ena_tx_ctx->req_id >> 10) <<
		ENA_ETH_IO_TX_DESC_REQ_ID_HI_SHIFT) &
		ENA_ETH_IO_TX_DESC_REQ_ID_HI_MASK;

	अगर (ena_tx_ctx->meta_valid) अणु
		desc->meta_ctrl |= (ena_tx_ctx->tso_enable <<
			ENA_ETH_IO_TX_DESC_TSO_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_TSO_EN_MASK;
		desc->meta_ctrl |= ena_tx_ctx->l3_proto &
			ENA_ETH_IO_TX_DESC_L3_PROTO_IDX_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_proto <<
			ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l3_csum_enable <<
			ENA_ETH_IO_TX_DESC_L3_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_L3_CSUM_EN_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_csum_enable <<
			ENA_ETH_IO_TX_DESC_L4_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_CSUM_EN_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_csum_partial <<
			ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_MASK;
	पूर्ण

	क्रम (i = 0; i < num_bufs; i++) अणु
		/* The first desc share the same desc as the header */
		अगर (likely(i != 0)) अणु
			rc = ena_com_sq_update_tail(io_sq);
			अगर (unlikely(rc))
				वापस rc;

			desc = get_sq_desc(io_sq);
			अगर (unlikely(!desc))
				वापस -EFAULT;

			स_रखो(desc, 0x0, माप(काष्ठा ena_eth_io_tx_desc));

			desc->len_ctrl |= ((u32)io_sq->phase <<
				ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
				ENA_ETH_IO_TX_DESC_PHASE_MASK;
		पूर्ण

		desc->len_ctrl |= ena_bufs->len &
			ENA_ETH_IO_TX_DESC_LENGTH_MASK;

		addr_hi = ((ena_bufs->paddr &
			GENMASK_ULL(io_sq->dma_addr_bits - 1, 32)) >> 32);

		desc->buff_addr_lo = (u32)ena_bufs->paddr;
		desc->buff_addr_hi_hdr_sz |= addr_hi &
			ENA_ETH_IO_TX_DESC_ADDR_HI_MASK;
		ena_bufs++;
	पूर्ण

	/* set the last desc indicator */
	desc->len_ctrl |= ENA_ETH_IO_TX_DESC_LAST_MASK;

	rc = ena_com_sq_update_tail(io_sq);
	अगर (unlikely(rc))
		वापस rc;

	rc = ena_com_बंद_bounce_buffer(io_sq);

	*nb_hw_desc = io_sq->tail - start_tail;
	वापस rc;
पूर्ण

पूर्णांक ena_com_rx_pkt(काष्ठा ena_com_io_cq *io_cq,
		   काष्ठा ena_com_io_sq *io_sq,
		   काष्ठा ena_com_rx_ctx *ena_rx_ctx)
अणु
	काष्ठा ena_com_rx_buf_info *ena_buf = &ena_rx_ctx->ena_bufs[0];
	काष्ठा ena_eth_io_rx_cdesc_base *cdesc = शून्य;
	u16 q_depth = io_cq->q_depth;
	u16 cdesc_idx = 0;
	u16 nb_hw_desc;
	u16 i = 0;

	WARN(io_cq->direction != ENA_COM_IO_QUEUE_सूचीECTION_RX, "wrong Q type");

	nb_hw_desc = ena_com_cdesc_rx_pkt_get(io_cq, &cdesc_idx);
	अगर (nb_hw_desc == 0) अणु
		ena_rx_ctx->descs = nb_hw_desc;
		वापस 0;
	पूर्ण

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "Fetch rx packet: queue %d completed desc: %d\n", io_cq->qid,
		   nb_hw_desc);

	अगर (unlikely(nb_hw_desc > ena_rx_ctx->max_bufs)) अणु
		netdev_err(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "Too many RX cdescs (%d) > MAX(%d)\n", nb_hw_desc,
			   ena_rx_ctx->max_bufs);
		वापस -ENOSPC;
	पूर्ण

	cdesc = ena_com_rx_cdesc_idx_to_ptr(io_cq, cdesc_idx);
	ena_rx_ctx->pkt_offset = cdesc->offset;

	करो अणु
		ena_buf[i].len = cdesc->length;
		ena_buf[i].req_id = cdesc->req_id;
		अगर (unlikely(ena_buf[i].req_id >= q_depth))
			वापस -EIO;

		अगर (++i >= nb_hw_desc)
			अवरोध;

		cdesc = ena_com_rx_cdesc_idx_to_ptr(io_cq, cdesc_idx + i);

	पूर्ण जबतक (1);

	/* Update SQ head ptr */
	io_sq->next_to_comp += nb_hw_desc;

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "[%s][QID#%d] Updating SQ head to: %d\n", __func__,
		   io_sq->qid, io_sq->next_to_comp);

	/* Get rx flags from the last pkt */
	ena_com_rx_set_flags(io_cq, ena_rx_ctx, cdesc);

	ena_rx_ctx->descs = nb_hw_desc;

	वापस 0;
पूर्ण

पूर्णांक ena_com_add_single_rx_desc(काष्ठा ena_com_io_sq *io_sq,
			       काष्ठा ena_com_buf *ena_buf,
			       u16 req_id)
अणु
	काष्ठा ena_eth_io_rx_desc *desc;

	WARN(io_sq->direction != ENA_COM_IO_QUEUE_सूचीECTION_RX, "wrong Q type");

	अगर (unlikely(!ena_com_sq_have_enough_space(io_sq, 1)))
		वापस -ENOSPC;

	desc = get_sq_desc(io_sq);
	अगर (unlikely(!desc))
		वापस -EFAULT;

	स_रखो(desc, 0x0, माप(काष्ठा ena_eth_io_rx_desc));

	desc->length = ena_buf->len;

	desc->ctrl = ENA_ETH_IO_RX_DESC_FIRST_MASK |
		     ENA_ETH_IO_RX_DESC_LAST_MASK |
		     ENA_ETH_IO_RX_DESC_COMP_REQ_MASK |
		     (io_sq->phase & ENA_ETH_IO_RX_DESC_PHASE_MASK);

	desc->req_id = req_id;

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "[%s] Adding single RX desc, Queue: %u, req_id: %u\n",
		   __func__, io_sq->qid, req_id);

	desc->buff_addr_lo = (u32)ena_buf->paddr;
	desc->buff_addr_hi =
		((ena_buf->paddr & GENMASK_ULL(io_sq->dma_addr_bits - 1, 32)) >> 32);

	वापस ena_com_sq_update_tail(io_sq);
पूर्ण

bool ena_com_cq_empty(काष्ठा ena_com_io_cq *io_cq)
अणु
	काष्ठा ena_eth_io_rx_cdesc_base *cdesc;

	cdesc = ena_com_get_next_rx_cdesc(io_cq);
	अगर (cdesc)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण
