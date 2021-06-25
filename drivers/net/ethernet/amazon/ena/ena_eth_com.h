<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित ENA_ETH_COM_H_
#घोषणा ENA_ETH_COM_H_

#समावेश "ena_com.h"

/* head update threshold in units of (queue size / ENA_COMP_HEAD_THRESH) */
#घोषणा ENA_COMP_HEAD_THRESH 4

काष्ठा ena_com_tx_ctx अणु
	काष्ठा ena_com_tx_meta ena_meta;
	काष्ठा ena_com_buf *ena_bufs;
	/* For LLQ, header buffer - pushed to the device mem space */
	व्योम *push_header;

	क्रमागत ena_eth_io_l3_proto_index l3_proto;
	क्रमागत ena_eth_io_l4_proto_index l4_proto;
	u16 num_bufs;
	u16 req_id;
	/* For regular queue, indicate the size of the header
	 * For LLQ, indicate the size of the pushed buffer
	 */
	u16 header_len;

	u8 meta_valid;
	u8 tso_enable;
	u8 l3_csum_enable;
	u8 l4_csum_enable;
	u8 l4_csum_partial;
	u8 df; /* Don't fragment */
पूर्ण;

काष्ठा ena_com_rx_ctx अणु
	काष्ठा ena_com_rx_buf_info *ena_bufs;
	क्रमागत ena_eth_io_l3_proto_index l3_proto;
	क्रमागत ena_eth_io_l4_proto_index l4_proto;
	bool l3_csum_err;
	bool l4_csum_err;
	u8 l4_csum_checked;
	/* fragmented packet */
	bool frag;
	u32 hash;
	u16 descs;
	पूर्णांक max_bufs;
	u8 pkt_offset;
पूर्ण;

पूर्णांक ena_com_prepare_tx(काष्ठा ena_com_io_sq *io_sq,
		       काष्ठा ena_com_tx_ctx *ena_tx_ctx,
		       पूर्णांक *nb_hw_desc);

पूर्णांक ena_com_rx_pkt(काष्ठा ena_com_io_cq *io_cq,
		   काष्ठा ena_com_io_sq *io_sq,
		   काष्ठा ena_com_rx_ctx *ena_rx_ctx);

पूर्णांक ena_com_add_single_rx_desc(काष्ठा ena_com_io_sq *io_sq,
			       काष्ठा ena_com_buf *ena_buf,
			       u16 req_id);

bool ena_com_cq_empty(काष्ठा ena_com_io_cq *io_cq);

अटल अंतरभूत व्योम ena_com_unmask_पूर्णांकr(काष्ठा ena_com_io_cq *io_cq,
				       काष्ठा ena_eth_io_पूर्णांकr_reg *पूर्णांकr_reg)
अणु
	ग_लिखोl(पूर्णांकr_reg->पूर्णांकr_control, io_cq->unmask_reg);
पूर्ण

अटल अंतरभूत पूर्णांक ena_com_मुक्त_q_entries(काष्ठा ena_com_io_sq *io_sq)
अणु
	u16 tail, next_to_comp, cnt;

	next_to_comp = io_sq->next_to_comp;
	tail = io_sq->tail;
	cnt = tail - next_to_comp;

	वापस io_sq->q_depth - 1 - cnt;
पूर्ण

/* Check अगर the submission queue has enough space to hold required_buffers */
अटल अंतरभूत bool ena_com_sq_have_enough_space(काष्ठा ena_com_io_sq *io_sq,
						u16 required_buffers)
अणु
	पूर्णांक temp;

	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST)
		वापस ena_com_मुक्त_q_entries(io_sq) >= required_buffers;

	/* This calculation करोesn't need to be 100% accurate. So to reduce
	 * the calculation overhead just Subtract 2 lines from the मुक्त descs
	 * (one क्रम the header line and one to compensate the devision
	 * करोwn calculation.
	 */
	temp = required_buffers / io_sq->llq_info.descs_per_entry + 2;

	वापस ena_com_मुक्त_q_entries(io_sq) > temp;
पूर्ण

अटल अंतरभूत bool ena_com_meta_desc_changed(काष्ठा ena_com_io_sq *io_sq,
					     काष्ठा ena_com_tx_ctx *ena_tx_ctx)
अणु
	अगर (!ena_tx_ctx->meta_valid)
		वापस false;

	वापस !!स_भेद(&io_sq->cached_tx_meta,
			&ena_tx_ctx->ena_meta,
			माप(काष्ठा ena_com_tx_meta));
पूर्ण

अटल अंतरभूत bool is_llq_max_tx_burst_exists(काष्ठा ena_com_io_sq *io_sq)
अणु
	वापस (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) &&
	       io_sq->llq_info.max_entries_in_tx_burst > 0;
पूर्ण

अटल अंतरभूत bool ena_com_is_करोorbell_needed(काष्ठा ena_com_io_sq *io_sq,
					      काष्ठा ena_com_tx_ctx *ena_tx_ctx)
अणु
	काष्ठा ena_com_llq_info *llq_info;
	पूर्णांक descs_after_first_entry;
	पूर्णांक num_entries_needed = 1;
	u16 num_descs;

	अगर (!is_llq_max_tx_burst_exists(io_sq))
		वापस false;

	llq_info = &io_sq->llq_info;
	num_descs = ena_tx_ctx->num_bufs;

	अगर (llq_info->disable_meta_caching ||
	    unlikely(ena_com_meta_desc_changed(io_sq, ena_tx_ctx)))
		++num_descs;

	अगर (num_descs > llq_info->descs_num_beक्रमe_header) अणु
		descs_after_first_entry = num_descs - llq_info->descs_num_beक्रमe_header;
		num_entries_needed += DIV_ROUND_UP(descs_after_first_entry,
						   llq_info->descs_per_entry);
	पूर्ण

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "Queue: %d num_descs: %d num_entries_needed: %d\n",
		   io_sq->qid, num_descs, num_entries_needed);

	वापस num_entries_needed > io_sq->entries_in_tx_burst_left;
पूर्ण

अटल अंतरभूत पूर्णांक ena_com_ग_लिखो_sq_करोorbell(काष्ठा ena_com_io_sq *io_sq)
अणु
	u16 max_entries_in_tx_burst = io_sq->llq_info.max_entries_in_tx_burst;
	u16 tail = io_sq->tail;

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "Write submission queue doorbell for queue: %d tail: %d\n",
		   io_sq->qid, tail);

	ग_लिखोl(tail, io_sq->db_addr);

	अगर (is_llq_max_tx_burst_exists(io_sq)) अणु
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Reset available entries in tx burst for queue %d to %d\n",
			   io_sq->qid, max_entries_in_tx_burst);
		io_sq->entries_in_tx_burst_left = max_entries_in_tx_burst;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ena_com_update_dev_comp_head(काष्ठा ena_com_io_cq *io_cq)
अणु
	u16 unreported_comp, head;
	bool need_update;

	अगर (unlikely(io_cq->cq_head_db_reg)) अणु
		head = io_cq->head;
		unreported_comp = head - io_cq->last_head_update;
		need_update = unreported_comp > (io_cq->q_depth / ENA_COMP_HEAD_THRESH);

		अगर (unlikely(need_update)) अणु
			netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
				   "Write completion queue doorbell for queue %d: head: %d\n",
				   io_cq->qid, head);
			ग_लिखोl(head, io_cq->cq_head_db_reg);
			io_cq->last_head_update = head;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ena_com_update_numa_node(काष्ठा ena_com_io_cq *io_cq,
					    u8 numa_node)
अणु
	काष्ठा ena_eth_io_numa_node_cfg_reg numa_cfg;

	अगर (!io_cq->numa_node_cfg_reg)
		वापस;

	numa_cfg.numa_cfg = (numa_node & ENA_ETH_IO_NUMA_NODE_CFG_REG_NUMA_MASK)
		| ENA_ETH_IO_NUMA_NODE_CFG_REG_ENABLED_MASK;

	ग_लिखोl(numa_cfg.numa_cfg, io_cq->numa_node_cfg_reg);
पूर्ण

अटल अंतरभूत व्योम ena_com_comp_ack(काष्ठा ena_com_io_sq *io_sq, u16 elem)
अणु
	io_sq->next_to_comp += elem;
पूर्ण

अटल अंतरभूत व्योम ena_com_cq_inc_head(काष्ठा ena_com_io_cq *io_cq)
अणु
	io_cq->head++;

	/* Switch phase bit in हाल of wrap around */
	अगर (unlikely((io_cq->head & (io_cq->q_depth - 1)) == 0))
		io_cq->phase ^= 1;
पूर्ण

अटल अंतरभूत पूर्णांक ena_com_tx_comp_req_id_get(काष्ठा ena_com_io_cq *io_cq,
					     u16 *req_id)
अणु
	u8 expected_phase, cdesc_phase;
	काष्ठा ena_eth_io_tx_cdesc *cdesc;
	u16 masked_head;

	masked_head = io_cq->head & (io_cq->q_depth - 1);
	expected_phase = io_cq->phase;

	cdesc = (काष्ठा ena_eth_io_tx_cdesc *)
		((uपूर्णांकptr_t)io_cq->cdesc_addr.virt_addr +
		(masked_head * io_cq->cdesc_entry_size_in_bytes));

	/* When the current completion descriptor phase isn't the same as the
	 * expected, it mean that the device still didn't update
	 * this completion.
	 */
	cdesc_phase = READ_ONCE(cdesc->flags) & ENA_ETH_IO_TX_CDESC_PHASE_MASK;
	अगर (cdesc_phase != expected_phase)
		वापस -EAGAIN;

	dma_rmb();

	*req_id = READ_ONCE(cdesc->req_id);
	अगर (unlikely(*req_id >= io_cq->q_depth)) अणु
		netdev_err(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "Invalid req id %d\n", cdesc->req_id);
		वापस -EINVAL;
	पूर्ण

	ena_com_cq_inc_head(io_cq);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* ENA_ETH_COM_H_ */
