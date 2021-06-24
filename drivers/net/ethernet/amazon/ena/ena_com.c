<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश "ena_com.h"

/*****************************************************************************/
/*****************************************************************************/

/* Timeout in micro-sec */
#घोषणा ADMIN_CMD_TIMEOUT_US (3000000)

#घोषणा ENA_ASYNC_QUEUE_DEPTH 16
#घोषणा ENA_ADMIN_QUEUE_DEPTH 32


#घोषणा ENA_CTRL_MAJOR		0
#घोषणा ENA_CTRL_MINOR		0
#घोषणा ENA_CTRL_SUB_MINOR	1

#घोषणा MIN_ENA_CTRL_VER \
	(((ENA_CTRL_MAJOR) << \
	(ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT)) | \
	((ENA_CTRL_MINOR) << \
	(ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT)) | \
	(ENA_CTRL_SUB_MINOR))

#घोषणा ENA_DMA_ADDR_TO_UINT32_LOW(x)	((u32)((u64)(x)))
#घोषणा ENA_DMA_ADDR_TO_UINT32_HIGH(x)	((u32)(((u64)(x)) >> 32))

#घोषणा ENA_MMIO_READ_TIMEOUT 0xFFFFFFFF

#घोषणा ENA_COM_BOUNCE_BUFFER_CNTRL_CNT	4

#घोषणा ENA_REGS_ADMIN_INTR_MASK 1

#घोषणा ENA_MIN_ADMIN_POLL_US 100

#घोषणा ENA_MAX_ADMIN_POLL_US 5000

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

क्रमागत ena_cmd_status अणु
	ENA_CMD_SUBMITTED,
	ENA_CMD_COMPLETED,
	/* Abort - canceled by the driver */
	ENA_CMD_ABORTED,
पूर्ण;

काष्ठा ena_comp_ctx अणु
	काष्ठा completion रुको_event;
	काष्ठा ena_admin_acq_entry *user_cqe;
	u32 comp_size;
	क्रमागत ena_cmd_status status;
	/* status from the device */
	u8 comp_status;
	u8 cmd_opcode;
	bool occupied;
पूर्ण;

काष्ठा ena_com_stats_ctx अणु
	काष्ठा ena_admin_aq_get_stats_cmd get_cmd;
	काष्ठा ena_admin_acq_get_stats_resp get_resp;
पूर्ण;

अटल पूर्णांक ena_com_mem_addr_set(काष्ठा ena_com_dev *ena_dev,
				       काष्ठा ena_common_mem_addr *ena_addr,
				       dma_addr_t addr)
अणु
	अगर ((addr & GENMASK_ULL(ena_dev->dma_addr_bits - 1, 0)) != addr) अणु
		netdev_err(ena_dev->net_device,
			   "DMA address has more bits that the device supports\n");
		वापस -EINVAL;
	पूर्ण

	ena_addr->mem_addr_low = lower_32_bits(addr);
	ena_addr->mem_addr_high = (u16)upper_32_bits(addr);

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_admin_init_sq(काष्ठा ena_com_admin_queue *admin_queue)
अणु
	काष्ठा ena_com_dev *ena_dev = admin_queue->ena_dev;
	काष्ठा ena_com_admin_sq *sq = &admin_queue->sq;
	u16 size = ADMIN_SQ_SIZE(admin_queue->q_depth);

	sq->entries = dma_alloc_coherent(admin_queue->q_dmadev, size,
					 &sq->dma_addr, GFP_KERNEL);

	अगर (!sq->entries) अणु
		netdev_err(ena_dev->net_device, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	sq->head = 0;
	sq->tail = 0;
	sq->phase = 1;

	sq->db_addr = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_admin_init_cq(काष्ठा ena_com_admin_queue *admin_queue)
अणु
	काष्ठा ena_com_dev *ena_dev = admin_queue->ena_dev;
	काष्ठा ena_com_admin_cq *cq = &admin_queue->cq;
	u16 size = ADMIN_CQ_SIZE(admin_queue->q_depth);

	cq->entries = dma_alloc_coherent(admin_queue->q_dmadev, size,
					 &cq->dma_addr, GFP_KERNEL);

	अगर (!cq->entries) अणु
		netdev_err(ena_dev->net_device, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	cq->head = 0;
	cq->phase = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_admin_init_aenq(काष्ठा ena_com_dev *ena_dev,
				   काष्ठा ena_aenq_handlers *aenq_handlers)
अणु
	काष्ठा ena_com_aenq *aenq = &ena_dev->aenq;
	u32 addr_low, addr_high, aenq_caps;
	u16 size;

	ena_dev->aenq.q_depth = ENA_ASYNC_QUEUE_DEPTH;
	size = ADMIN_AENQ_SIZE(ENA_ASYNC_QUEUE_DEPTH);
	aenq->entries = dma_alloc_coherent(ena_dev->dmadev, size,
					   &aenq->dma_addr, GFP_KERNEL);

	अगर (!aenq->entries) अणु
		netdev_err(ena_dev->net_device, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	aenq->head = aenq->q_depth;
	aenq->phase = 1;

	addr_low = ENA_DMA_ADDR_TO_UINT32_LOW(aenq->dma_addr);
	addr_high = ENA_DMA_ADDR_TO_UINT32_HIGH(aenq->dma_addr);

	ग_लिखोl(addr_low, ena_dev->reg_bar + ENA_REGS_AENQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, ena_dev->reg_bar + ENA_REGS_AENQ_BASE_HI_OFF);

	aenq_caps = 0;
	aenq_caps |= ena_dev->aenq.q_depth & ENA_REGS_AENQ_CAPS_AENQ_DEPTH_MASK;
	aenq_caps |= (माप(काष्ठा ena_admin_aenq_entry)
		      << ENA_REGS_AENQ_CAPS_AENQ_ENTRY_SIZE_SHIFT) &
		     ENA_REGS_AENQ_CAPS_AENQ_ENTRY_SIZE_MASK;
	ग_लिखोl(aenq_caps, ena_dev->reg_bar + ENA_REGS_AENQ_CAPS_OFF);

	अगर (unlikely(!aenq_handlers)) अणु
		netdev_err(ena_dev->net_device,
			   "AENQ handlers pointer is NULL\n");
		वापस -EINVAL;
	पूर्ण

	aenq->aenq_handlers = aenq_handlers;

	वापस 0;
पूर्ण

अटल व्योम comp_ctxt_release(काष्ठा ena_com_admin_queue *queue,
				     काष्ठा ena_comp_ctx *comp_ctx)
अणु
	comp_ctx->occupied = false;
	atomic_dec(&queue->outstanding_cmds);
पूर्ण

अटल काष्ठा ena_comp_ctx *get_comp_ctxt(काष्ठा ena_com_admin_queue *admin_queue,
					  u16 command_id, bool capture)
अणु
	अगर (unlikely(command_id >= admin_queue->q_depth)) अणु
		netdev_err(admin_queue->ena_dev->net_device,
			   "Command id is larger than the queue size. cmd_id: %u queue size %d\n",
			   command_id, admin_queue->q_depth);
		वापस शून्य;
	पूर्ण

	अगर (unlikely(!admin_queue->comp_ctx)) अणु
		netdev_err(admin_queue->ena_dev->net_device,
			   "Completion context is NULL\n");
		वापस शून्य;
	पूर्ण

	अगर (unlikely(admin_queue->comp_ctx[command_id].occupied && capture)) अणु
		netdev_err(admin_queue->ena_dev->net_device,
			   "Completion context is occupied\n");
		वापस शून्य;
	पूर्ण

	अगर (capture) अणु
		atomic_inc(&admin_queue->outstanding_cmds);
		admin_queue->comp_ctx[command_id].occupied = true;
	पूर्ण

	वापस &admin_queue->comp_ctx[command_id];
पूर्ण

अटल काष्ठा ena_comp_ctx *__ena_com_submit_admin_cmd(काष्ठा ena_com_admin_queue *admin_queue,
						       काष्ठा ena_admin_aq_entry *cmd,
						       माप_प्रकार cmd_size_in_bytes,
						       काष्ठा ena_admin_acq_entry *comp,
						       माप_प्रकार comp_size_in_bytes)
अणु
	काष्ठा ena_comp_ctx *comp_ctx;
	u16 tail_masked, cmd_id;
	u16 queue_size_mask;
	u16 cnt;

	queue_size_mask = admin_queue->q_depth - 1;

	tail_masked = admin_queue->sq.tail & queue_size_mask;

	/* In हाल of queue FULL */
	cnt = (u16)atomic_पढ़ो(&admin_queue->outstanding_cmds);
	अगर (cnt >= admin_queue->q_depth) अणु
		netdev_dbg(admin_queue->ena_dev->net_device,
			   "Admin queue is full.\n");
		admin_queue->stats.out_of_space++;
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	cmd_id = admin_queue->curr_cmd_id;

	cmd->aq_common_descriptor.flags |= admin_queue->sq.phase &
		ENA_ADMIN_AQ_COMMON_DESC_PHASE_MASK;

	cmd->aq_common_descriptor.command_id |= cmd_id &
		ENA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK;

	comp_ctx = get_comp_ctxt(admin_queue, cmd_id, true);
	अगर (unlikely(!comp_ctx))
		वापस ERR_PTR(-EINVAL);

	comp_ctx->status = ENA_CMD_SUBMITTED;
	comp_ctx->comp_size = (u32)comp_size_in_bytes;
	comp_ctx->user_cqe = comp;
	comp_ctx->cmd_opcode = cmd->aq_common_descriptor.opcode;

	reinit_completion(&comp_ctx->रुको_event);

	स_नकल(&admin_queue->sq.entries[tail_masked], cmd, cmd_size_in_bytes);

	admin_queue->curr_cmd_id = (admin_queue->curr_cmd_id + 1) &
		queue_size_mask;

	admin_queue->sq.tail++;
	admin_queue->stats.submitted_cmd++;

	अगर (unlikely((admin_queue->sq.tail & queue_size_mask) == 0))
		admin_queue->sq.phase = !admin_queue->sq.phase;

	ग_लिखोl(admin_queue->sq.tail, admin_queue->sq.db_addr);

	वापस comp_ctx;
पूर्ण

अटल पूर्णांक ena_com_init_comp_ctxt(काष्ठा ena_com_admin_queue *admin_queue)
अणु
	काष्ठा ena_com_dev *ena_dev = admin_queue->ena_dev;
	माप_प्रकार size = admin_queue->q_depth * माप(काष्ठा ena_comp_ctx);
	काष्ठा ena_comp_ctx *comp_ctx;
	u16 i;

	admin_queue->comp_ctx =
		devm_kzalloc(admin_queue->q_dmadev, size, GFP_KERNEL);
	अगर (unlikely(!admin_queue->comp_ctx)) अणु
		netdev_err(ena_dev->net_device, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < admin_queue->q_depth; i++) अणु
		comp_ctx = get_comp_ctxt(admin_queue, i, false);
		अगर (comp_ctx)
			init_completion(&comp_ctx->रुको_event);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ena_comp_ctx *ena_com_submit_admin_cmd(काष्ठा ena_com_admin_queue *admin_queue,
						     काष्ठा ena_admin_aq_entry *cmd,
						     माप_प्रकार cmd_size_in_bytes,
						     काष्ठा ena_admin_acq_entry *comp,
						     माप_प्रकार comp_size_in_bytes)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ena_comp_ctx *comp_ctx;

	spin_lock_irqsave(&admin_queue->q_lock, flags);
	अगर (unlikely(!admin_queue->running_state)) अणु
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	comp_ctx = __ena_com_submit_admin_cmd(admin_queue, cmd,
					      cmd_size_in_bytes,
					      comp,
					      comp_size_in_bytes);
	अगर (IS_ERR(comp_ctx))
		admin_queue->running_state = false;
	spin_unlock_irqrestore(&admin_queue->q_lock, flags);

	वापस comp_ctx;
पूर्ण

अटल पूर्णांक ena_com_init_io_sq(काष्ठा ena_com_dev *ena_dev,
			      काष्ठा ena_com_create_io_ctx *ctx,
			      काष्ठा ena_com_io_sq *io_sq)
अणु
	माप_प्रकार size;
	पूर्णांक dev_node = 0;

	स_रखो(&io_sq->desc_addr, 0x0, माप(io_sq->desc_addr));

	io_sq->dma_addr_bits = (u8)ena_dev->dma_addr_bits;
	io_sq->desc_entry_size =
		(io_sq->direction == ENA_COM_IO_QUEUE_सूचीECTION_TX) ?
		माप(काष्ठा ena_eth_io_tx_desc) :
		माप(काष्ठा ena_eth_io_rx_desc);

	size = io_sq->desc_entry_size * io_sq->q_depth;

	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST) अणु
		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->desc_addr.virt_addr =
			dma_alloc_coherent(ena_dev->dmadev, size,
					   &io_sq->desc_addr.phys_addr,
					   GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		अगर (!io_sq->desc_addr.virt_addr) अणु
			io_sq->desc_addr.virt_addr =
				dma_alloc_coherent(ena_dev->dmadev, size,
						   &io_sq->desc_addr.phys_addr,
						   GFP_KERNEL);
		पूर्ण

		अगर (!io_sq->desc_addr.virt_addr) अणु
			netdev_err(ena_dev->net_device,
				   "Memory allocation failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) अणु
		/* Allocate bounce buffers */
		io_sq->bounce_buf_ctrl.buffer_size =
			ena_dev->llq_info.desc_list_entry_size;
		io_sq->bounce_buf_ctrl.buffers_num =
			ENA_COM_BOUNCE_BUFFER_CNTRL_CNT;
		io_sq->bounce_buf_ctrl.next_to_use = 0;

		size = io_sq->bounce_buf_ctrl.buffer_size *
			io_sq->bounce_buf_ctrl.buffers_num;

		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->bounce_buf_ctrl.base_buffer =
			devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		अगर (!io_sq->bounce_buf_ctrl.base_buffer)
			io_sq->bounce_buf_ctrl.base_buffer =
				devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);

		अगर (!io_sq->bounce_buf_ctrl.base_buffer) अणु
			netdev_err(ena_dev->net_device,
				   "Bounce buffer memory allocation failed\n");
			वापस -ENOMEM;
		पूर्ण

		स_नकल(&io_sq->llq_info, &ena_dev->llq_info,
		       माप(io_sq->llq_info));

		/* Initiate the first bounce buffer */
		io_sq->llq_buf_ctrl.curr_bounce_buf =
			ena_com_get_next_bounce_buffer(&io_sq->bounce_buf_ctrl);
		स_रखो(io_sq->llq_buf_ctrl.curr_bounce_buf,
		       0x0, io_sq->llq_info.desc_list_entry_size);
		io_sq->llq_buf_ctrl.descs_left_in_line =
			io_sq->llq_info.descs_num_beक्रमe_header;
		io_sq->disable_meta_caching =
			io_sq->llq_info.disable_meta_caching;

		अगर (io_sq->llq_info.max_entries_in_tx_burst > 0)
			io_sq->entries_in_tx_burst_left =
				io_sq->llq_info.max_entries_in_tx_burst;
	पूर्ण

	io_sq->tail = 0;
	io_sq->next_to_comp = 0;
	io_sq->phase = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_com_init_io_cq(काष्ठा ena_com_dev *ena_dev,
			      काष्ठा ena_com_create_io_ctx *ctx,
			      काष्ठा ena_com_io_cq *io_cq)
अणु
	माप_प्रकार size;
	पूर्णांक prev_node = 0;

	स_रखो(&io_cq->cdesc_addr, 0x0, माप(io_cq->cdesc_addr));

	/* Use the basic completion descriptor क्रम Rx */
	io_cq->cdesc_entry_size_in_bytes =
		(io_cq->direction == ENA_COM_IO_QUEUE_सूचीECTION_TX) ?
		माप(काष्ठा ena_eth_io_tx_cdesc) :
		माप(काष्ठा ena_eth_io_rx_cdesc_base);

	size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;

	prev_node = dev_to_node(ena_dev->dmadev);
	set_dev_node(ena_dev->dmadev, ctx->numa_node);
	io_cq->cdesc_addr.virt_addr =
		dma_alloc_coherent(ena_dev->dmadev, size,
				   &io_cq->cdesc_addr.phys_addr, GFP_KERNEL);
	set_dev_node(ena_dev->dmadev, prev_node);
	अगर (!io_cq->cdesc_addr.virt_addr) अणु
		io_cq->cdesc_addr.virt_addr =
			dma_alloc_coherent(ena_dev->dmadev, size,
					   &io_cq->cdesc_addr.phys_addr,
					   GFP_KERNEL);
	पूर्ण

	अगर (!io_cq->cdesc_addr.virt_addr) अणु
		netdev_err(ena_dev->net_device, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	io_cq->phase = 1;
	io_cq->head = 0;

	वापस 0;
पूर्ण

अटल व्योम ena_com_handle_single_admin_completion(काष्ठा ena_com_admin_queue *admin_queue,
						   काष्ठा ena_admin_acq_entry *cqe)
अणु
	काष्ठा ena_comp_ctx *comp_ctx;
	u16 cmd_id;

	cmd_id = cqe->acq_common_descriptor.command &
		ENA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK;

	comp_ctx = get_comp_ctxt(admin_queue, cmd_id, false);
	अगर (unlikely(!comp_ctx)) अणु
		netdev_err(admin_queue->ena_dev->net_device,
			   "comp_ctx is NULL. Changing the admin queue running state\n");
		admin_queue->running_state = false;
		वापस;
	पूर्ण

	comp_ctx->status = ENA_CMD_COMPLETED;
	comp_ctx->comp_status = cqe->acq_common_descriptor.status;

	अगर (comp_ctx->user_cqe)
		स_नकल(comp_ctx->user_cqe, (व्योम *)cqe, comp_ctx->comp_size);

	अगर (!admin_queue->polling)
		complete(&comp_ctx->रुको_event);
पूर्ण

अटल व्योम ena_com_handle_admin_completion(काष्ठा ena_com_admin_queue *admin_queue)
अणु
	काष्ठा ena_admin_acq_entry *cqe = शून्य;
	u16 comp_num = 0;
	u16 head_masked;
	u8 phase;

	head_masked = admin_queue->cq.head & (admin_queue->q_depth - 1);
	phase = admin_queue->cq.phase;

	cqe = &admin_queue->cq.entries[head_masked];

	/* Go over all the completions */
	जबतक ((READ_ONCE(cqe->acq_common_descriptor.flags) &
		ENA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK) == phase) अणु
		/* Do not पढ़ो the rest of the completion entry beक्रमe the
		 * phase bit was validated
		 */
		dma_rmb();
		ena_com_handle_single_admin_completion(admin_queue, cqe);

		head_masked++;
		comp_num++;
		अगर (unlikely(head_masked == admin_queue->q_depth)) अणु
			head_masked = 0;
			phase = !phase;
		पूर्ण

		cqe = &admin_queue->cq.entries[head_masked];
	पूर्ण

	admin_queue->cq.head += comp_num;
	admin_queue->cq.phase = phase;
	admin_queue->sq.head += comp_num;
	admin_queue->stats.completed_cmd += comp_num;
पूर्ण

अटल पूर्णांक ena_com_comp_status_to_त्रुटि_सं(काष्ठा ena_com_admin_queue *admin_queue,
					u8 comp_status)
अणु
	अगर (unlikely(comp_status != 0))
		netdev_err(admin_queue->ena_dev->net_device,
			   "Admin command failed[%u]\n", comp_status);

	चयन (comp_status) अणु
	हाल ENA_ADMIN_SUCCESS:
		वापस 0;
	हाल ENA_ADMIN_RESOURCE_ALLOCATION_FAILURE:
		वापस -ENOMEM;
	हाल ENA_ADMIN_UNSUPPORTED_OPCODE:
		वापस -EOPNOTSUPP;
	हाल ENA_ADMIN_BAD_OPCODE:
	हाल ENA_ADMIN_MALFORMED_REQUEST:
	हाल ENA_ADMIN_ILLEGAL_PARAMETER:
	हाल ENA_ADMIN_UNKNOWN_ERROR:
		वापस -EINVAL;
	हाल ENA_ADMIN_RESOURCE_BUSY:
		वापस -EAGAIN;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ena_delay_exponential_backoff_us(u32 exp, u32 delay_us)
अणु
	delay_us = max_t(u32, ENA_MIN_ADMIN_POLL_US, delay_us);
	delay_us = min_t(u32, delay_us * (1U << exp), ENA_MAX_ADMIN_POLL_US);
	usleep_range(delay_us, 2 * delay_us);
पूर्ण

अटल पूर्णांक ena_com_रुको_and_process_admin_cq_polling(काष्ठा ena_comp_ctx *comp_ctx,
						     काष्ठा ena_com_admin_queue *admin_queue)
अणु
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;
	u32 exp = 0;

	समयout = jअगरfies + usecs_to_jअगरfies(admin_queue->completion_समयout);

	जबतक (1) अणु
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);

		अगर (comp_ctx->status != ENA_CMD_SUBMITTED)
			अवरोध;

		अगर (समय_is_beक्रमe_jअगरfies(समयout)) अणु
			netdev_err(admin_queue->ena_dev->net_device,
				   "Wait for completion (polling) timeout\n");
			/* ENA didn't have any completion */
			spin_lock_irqsave(&admin_queue->q_lock, flags);
			admin_queue->stats.no_completion++;
			admin_queue->running_state = false;
			spin_unlock_irqrestore(&admin_queue->q_lock, flags);

			ret = -ETIME;
			जाओ err;
		पूर्ण

		ena_delay_exponential_backoff_us(exp++,
						 admin_queue->ena_dev->ena_min_poll_delay_us);
	पूर्ण

	अगर (unlikely(comp_ctx->status == ENA_CMD_ABORTED)) अणु
		netdev_err(admin_queue->ena_dev->net_device,
			   "Command was aborted\n");
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		admin_queue->stats.पातed_cmd++;
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	WARN(comp_ctx->status != ENA_CMD_COMPLETED, "Invalid comp status %d\n",
	     comp_ctx->status);

	ret = ena_com_comp_status_to_त्रुटि_सं(admin_queue, comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	वापस ret;
पूर्ण

/*
 * Set the LLQ configurations of the firmware
 *
 * The driver provides only the enabled feature values to the device,
 * which in turn, checks अगर they are supported.
 */
अटल पूर्णांक ena_com_set_llq(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	काष्ठा ena_com_llq_info *llq_info = &ena_dev->llq_info;
	पूर्णांक ret;

	स_रखो(&cmd, 0x0, माप(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.feat_common.feature_id = ENA_ADMIN_LLQ;

	cmd.u.llq.header_location_ctrl_enabled = llq_info->header_location_ctrl;
	cmd.u.llq.entry_size_ctrl_enabled = llq_info->desc_list_entry_size_ctrl;
	cmd.u.llq.desc_num_beक्रमe_header_enabled = llq_info->descs_num_beक्रमe_header;
	cmd.u.llq.descriptors_stride_ctrl_enabled = llq_info->desc_stride_ctrl;

	cmd.u.llq.accel_mode.u.set.enabled_flags =
		BIT(ENA_ADMIN_DISABLE_META_CACHING) |
		BIT(ENA_ADMIN_LIMIT_TX_BURST);

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to set LLQ configurations: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ena_com_config_llq_info(काष्ठा ena_com_dev *ena_dev,
				   काष्ठा ena_admin_feature_llq_desc *llq_features,
				   काष्ठा ena_llq_configurations *llq_शेष_cfg)
अणु
	काष्ठा ena_com_llq_info *llq_info = &ena_dev->llq_info;
	काष्ठा ena_admin_accel_mode_get llq_accel_mode_get;
	u16 supported_feat;
	पूर्णांक rc;

	स_रखो(llq_info, 0, माप(*llq_info));

	supported_feat = llq_features->header_location_ctrl_supported;

	अगर (likely(supported_feat & llq_शेष_cfg->llq_header_location)) अणु
		llq_info->header_location_ctrl =
			llq_शेष_cfg->llq_header_location;
	पूर्ण अन्यथा अणु
		netdev_err(ena_dev->net_device,
			   "Invalid header location control, supported: 0x%x\n",
			   supported_feat);
		वापस -EINVAL;
	पूर्ण

	अगर (likely(llq_info->header_location_ctrl == ENA_ADMIN_INLINE_HEADER)) अणु
		supported_feat = llq_features->descriptors_stride_ctrl_supported;
		अगर (likely(supported_feat & llq_शेष_cfg->llq_stride_ctrl)) अणु
			llq_info->desc_stride_ctrl = llq_शेष_cfg->llq_stride_ctrl;
		पूर्ण अन्यथा	अणु
			अगर (supported_feat & ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY) अणु
				llq_info->desc_stride_ctrl = ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY;
			पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_SINGLE_DESC_PER_ENTRY) अणु
				llq_info->desc_stride_ctrl = ENA_ADMIN_SINGLE_DESC_PER_ENTRY;
			पूर्ण अन्यथा अणु
				netdev_err(ena_dev->net_device,
					   "Invalid desc_stride_ctrl, supported: 0x%x\n",
					   supported_feat);
				वापस -EINVAL;
			पूर्ण

			netdev_err(ena_dev->net_device,
				   "Default llq stride ctrl is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
				   llq_शेष_cfg->llq_stride_ctrl,
				   supported_feat, llq_info->desc_stride_ctrl);
		पूर्ण
	पूर्ण अन्यथा अणु
		llq_info->desc_stride_ctrl = 0;
	पूर्ण

	supported_feat = llq_features->entry_size_ctrl_supported;
	अगर (likely(supported_feat & llq_शेष_cfg->llq_ring_entry_size)) अणु
		llq_info->desc_list_entry_size_ctrl = llq_शेष_cfg->llq_ring_entry_size;
		llq_info->desc_list_entry_size = llq_शेष_cfg->llq_ring_entry_size_value;
	पूर्ण अन्यथा अणु
		अगर (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_128B) अणु
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_128B;
			llq_info->desc_list_entry_size = 128;
		पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_192B) अणु
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_192B;
			llq_info->desc_list_entry_size = 192;
		पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_256B) अणु
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_256B;
			llq_info->desc_list_entry_size = 256;
		पूर्ण अन्यथा अणु
			netdev_err(ena_dev->net_device,
				   "Invalid entry_size_ctrl, supported: 0x%x\n",
				   supported_feat);
			वापस -EINVAL;
		पूर्ण

		netdev_err(ena_dev->net_device,
			   "Default llq ring entry size is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
			   llq_शेष_cfg->llq_ring_entry_size, supported_feat,
			   llq_info->desc_list_entry_size);
	पूर्ण
	अगर (unlikely(llq_info->desc_list_entry_size & 0x7)) अणु
		/* The desc list entry size should be whole multiply of 8
		 * This requirement comes from __ioग_लिखो64_copy()
		 */
		netdev_err(ena_dev->net_device, "Illegal entry size %d\n",
			   llq_info->desc_list_entry_size);
		वापस -EINVAL;
	पूर्ण

	अगर (llq_info->desc_stride_ctrl == ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY)
		llq_info->descs_per_entry = llq_info->desc_list_entry_size /
			माप(काष्ठा ena_eth_io_tx_desc);
	अन्यथा
		llq_info->descs_per_entry = 1;

	supported_feat = llq_features->desc_num_beक्रमe_header_supported;
	अगर (likely(supported_feat & llq_शेष_cfg->llq_num_decs_beक्रमe_header)) अणु
		llq_info->descs_num_beक्रमe_header = llq_शेष_cfg->llq_num_decs_beक्रमe_header;
	पूर्ण अन्यथा अणु
		अगर (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2) अणु
			llq_info->descs_num_beक्रमe_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2;
		पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1) अणु
			llq_info->descs_num_beक्रमe_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1;
		पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4) अणु
			llq_info->descs_num_beक्रमe_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4;
		पूर्ण अन्यथा अगर (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8) अणु
			llq_info->descs_num_beक्रमe_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8;
		पूर्ण अन्यथा अणु
			netdev_err(ena_dev->net_device,
				   "Invalid descs_num_before_header, supported: 0x%x\n",
				   supported_feat);
			वापस -EINVAL;
		पूर्ण

		netdev_err(ena_dev->net_device,
			   "Default llq num descs before header is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
			   llq_शेष_cfg->llq_num_decs_beक्रमe_header,
			   supported_feat, llq_info->descs_num_beक्रमe_header);
	पूर्ण
	/* Check क्रम accelerated queue supported */
	llq_accel_mode_get = llq_features->accel_mode.u.get;

	llq_info->disable_meta_caching =
		!!(llq_accel_mode_get.supported_flags &
		   BIT(ENA_ADMIN_DISABLE_META_CACHING));

	अगर (llq_accel_mode_get.supported_flags & BIT(ENA_ADMIN_LIMIT_TX_BURST))
		llq_info->max_entries_in_tx_burst =
			llq_accel_mode_get.max_tx_burst_size /
			llq_शेष_cfg->llq_ring_entry_size_value;

	rc = ena_com_set_llq(ena_dev);
	अगर (rc)
		netdev_err(ena_dev->net_device,
			   "Cannot set LLQ configuration: %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक ena_com_रुको_and_process_admin_cq_पूर्णांकerrupts(काष्ठा ena_comp_ctx *comp_ctx,
							काष्ठा ena_com_admin_queue *admin_queue)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	रुको_क्रम_completion_समयout(&comp_ctx->रुको_event,
				    usecs_to_jअगरfies(
					    admin_queue->completion_समयout));

	/* In हाल the command wasn't completed find out the root cause.
	 * There might be 2 kinds of errors
	 * 1) No completion (समयout reached)
	 * 2) There is completion but the device didn't get any msi-x पूर्णांकerrupt.
	 */
	अगर (unlikely(comp_ctx->status == ENA_CMD_SUBMITTED)) अणु
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		admin_queue->stats.no_completion++;
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);

		अगर (comp_ctx->status == ENA_CMD_COMPLETED) अणु
			netdev_err(admin_queue->ena_dev->net_device,
				   "The ena device sent a completion but the driver didn't receive a MSI-X interrupt (cmd %d), autopolling mode is %s\n",
				   comp_ctx->cmd_opcode,
				   admin_queue->स्वतः_polling ? "ON" : "OFF");
			/* Check अगर fallback to polling is enabled */
			अगर (admin_queue->स्वतः_polling)
				admin_queue->polling = true;
		पूर्ण अन्यथा अणु
			netdev_err(admin_queue->ena_dev->net_device,
				   "The ena device didn't send a completion for the admin cmd %d status %d\n",
				   comp_ctx->cmd_opcode, comp_ctx->status);
		पूर्ण
		/* Check अगर shअगरted to polling mode.
		 * This will happen अगर there is a completion without an पूर्णांकerrupt
		 * and स्वतःpolling mode is enabled. Continuing normal execution in such हाल
		 */
		अगर (!admin_queue->polling) अणु
			admin_queue->running_state = false;
			ret = -ETIME;
			जाओ err;
		पूर्ण
	पूर्ण

	ret = ena_com_comp_status_to_त्रुटि_सं(admin_queue, comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	वापस ret;
पूर्ण

/* This method पढ़ो the hardware device रेजिस्टर through posting ग_लिखोs
 * and रुकोing क्रम response
 * On समयout the function will वापस ENA_MMIO_READ_TIMEOUT
 */
अटल u32 ena_com_reg_bar_पढ़ो32(काष्ठा ena_com_dev *ena_dev, u16 offset)
अणु
	काष्ठा ena_com_mmio_पढ़ो *mmio_पढ़ो = &ena_dev->mmio_पढ़ो;
	अस्थिर काष्ठा ena_admin_ena_mmio_req_पढ़ो_less_resp *पढ़ो_resp =
		mmio_पढ़ो->पढ़ो_resp;
	u32 mmio_पढ़ो_reg, ret, i;
	अचिन्हित दीर्घ flags = 0;
	u32 समयout = mmio_पढ़ो->reg_पढ़ो_to;

	might_sleep();

	अगर (समयout == 0)
		समयout = ENA_REG_READ_TIMEOUT;

	/* If पढ़ोless is disabled, perक्रमm regular पढ़ो */
	अगर (!mmio_पढ़ो->पढ़ोless_supported)
		वापस पढ़ोl(ena_dev->reg_bar + offset);

	spin_lock_irqsave(&mmio_पढ़ो->lock, flags);
	mmio_पढ़ो->seq_num++;

	पढ़ो_resp->req_id = mmio_पढ़ो->seq_num + 0xDEAD;
	mmio_पढ़ो_reg = (offset << ENA_REGS_MMIO_REG_READ_REG_OFF_SHIFT) &
			ENA_REGS_MMIO_REG_READ_REG_OFF_MASK;
	mmio_पढ़ो_reg |= mmio_पढ़ो->seq_num &
			ENA_REGS_MMIO_REG_READ_REQ_ID_MASK;

	ग_लिखोl(mmio_पढ़ो_reg, ena_dev->reg_bar + ENA_REGS_MMIO_REG_READ_OFF);

	क्रम (i = 0; i < समयout; i++) अणु
		अगर (READ_ONCE(पढ़ो_resp->req_id) == mmio_पढ़ो->seq_num)
			अवरोध;

		udelay(1);
	पूर्ण

	अगर (unlikely(i == समयout)) अणु
		netdev_err(ena_dev->net_device,
			   "Reading reg failed for timeout. expected: req id[%u] offset[%u] actual: req id[%u] offset[%u]\n",
			   mmio_पढ़ो->seq_num, offset, पढ़ो_resp->req_id,
			   पढ़ो_resp->reg_off);
		ret = ENA_MMIO_READ_TIMEOUT;
		जाओ err;
	पूर्ण

	अगर (पढ़ो_resp->reg_off != offset) अणु
		netdev_err(ena_dev->net_device,
			   "Read failure: wrong offset provided\n");
		ret = ENA_MMIO_READ_TIMEOUT;
	पूर्ण अन्यथा अणु
		ret = पढ़ो_resp->reg_val;
	पूर्ण
err:
	spin_unlock_irqrestore(&mmio_पढ़ो->lock, flags);

	वापस ret;
पूर्ण

/* There are two types to रुको क्रम completion.
 * Polling mode - रुको until the completion is available.
 * Async mode - रुको on रुको queue until the completion is पढ़ोy
 * (or the समयout expired).
 * It is expected that the IRQ called ena_com_handle_admin_completion
 * to mark the completions.
 */
अटल पूर्णांक ena_com_रुको_and_process_admin_cq(काष्ठा ena_comp_ctx *comp_ctx,
					     काष्ठा ena_com_admin_queue *admin_queue)
अणु
	अगर (admin_queue->polling)
		वापस ena_com_रुको_and_process_admin_cq_polling(comp_ctx,
								 admin_queue);

	वापस ena_com_रुको_and_process_admin_cq_पूर्णांकerrupts(comp_ctx,
							    admin_queue);
पूर्ण

अटल पूर्णांक ena_com_destroy_io_sq(काष्ठा ena_com_dev *ena_dev,
				 काष्ठा ena_com_io_sq *io_sq)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_admin_aq_destroy_sq_cmd destroy_cmd;
	काष्ठा ena_admin_acq_destroy_sq_resp_desc destroy_resp;
	u8 direction;
	पूर्णांक ret;

	स_रखो(&destroy_cmd, 0x0, माप(destroy_cmd));

	अगर (io_sq->direction == ENA_COM_IO_QUEUE_सूचीECTION_TX)
		direction = ENA_ADMIN_SQ_सूचीECTION_TX;
	अन्यथा
		direction = ENA_ADMIN_SQ_सूचीECTION_RX;

	destroy_cmd.sq.sq_identity |= (direction <<
		ENA_ADMIN_SQ_SQ_सूचीECTION_SHIFT) &
		ENA_ADMIN_SQ_SQ_सूचीECTION_MASK;

	destroy_cmd.sq.sq_idx = io_sq->idx;
	destroy_cmd.aq_common_descriptor.opcode = ENA_ADMIN_DESTROY_SQ;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&destroy_cmd,
					    माप(destroy_cmd),
					    (काष्ठा ena_admin_acq_entry *)&destroy_resp,
					    माप(destroy_resp));

	अगर (unlikely(ret && (ret != -ENODEV)))
		netdev_err(ena_dev->net_device,
			   "Failed to destroy io sq error: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम ena_com_io_queue_मुक्त(काष्ठा ena_com_dev *ena_dev,
				  काष्ठा ena_com_io_sq *io_sq,
				  काष्ठा ena_com_io_cq *io_cq)
अणु
	माप_प्रकार size;

	अगर (io_cq->cdesc_addr.virt_addr) अणु
		size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;

		dma_मुक्त_coherent(ena_dev->dmadev, size,
				  io_cq->cdesc_addr.virt_addr,
				  io_cq->cdesc_addr.phys_addr);

		io_cq->cdesc_addr.virt_addr = शून्य;
	पूर्ण

	अगर (io_sq->desc_addr.virt_addr) अणु
		size = io_sq->desc_entry_size * io_sq->q_depth;

		dma_मुक्त_coherent(ena_dev->dmadev, size,
				  io_sq->desc_addr.virt_addr,
				  io_sq->desc_addr.phys_addr);

		io_sq->desc_addr.virt_addr = शून्य;
	पूर्ण

	अगर (io_sq->bounce_buf_ctrl.base_buffer) अणु
		devm_kमुक्त(ena_dev->dmadev, io_sq->bounce_buf_ctrl.base_buffer);
		io_sq->bounce_buf_ctrl.base_buffer = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक रुको_क्रम_reset_state(काष्ठा ena_com_dev *ena_dev, u32 समयout,
				u16 exp_state)
अणु
	u32 val, exp = 0;
	अचिन्हित दीर्घ समयout_stamp;

	/* Convert समयout from resolution of 100ms to us resolution. */
	समयout_stamp = jअगरfies + usecs_to_jअगरfies(100 * 1000 * समयout);

	जबतक (1) अणु
		val = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_DEV_STS_OFF);

		अगर (unlikely(val == ENA_MMIO_READ_TIMEOUT)) अणु
			netdev_err(ena_dev->net_device,
				   "Reg read timeout occurred\n");
			वापस -ETIME;
		पूर्ण

		अगर ((val & ENA_REGS_DEV_STS_RESET_IN_PROGRESS_MASK) ==
			exp_state)
			वापस 0;

		अगर (समय_is_beक्रमe_jअगरfies(समयout_stamp))
			वापस -ETIME;

		ena_delay_exponential_backoff_us(exp++, ena_dev->ena_min_poll_delay_us);
	पूर्ण
पूर्ण

अटल bool ena_com_check_supported_feature_id(काष्ठा ena_com_dev *ena_dev,
					       क्रमागत ena_admin_aq_feature_id feature_id)
अणु
	u32 feature_mask = 1 << feature_id;

	/* Device attributes is always supported */
	अगर ((feature_id != ENA_ADMIN_DEVICE_ATTRIBUTES) &&
	    !(ena_dev->supported_features & feature_mask))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ena_com_get_feature_ex(काष्ठा ena_com_dev *ena_dev,
				  काष्ठा ena_admin_get_feat_resp *get_resp,
				  क्रमागत ena_admin_aq_feature_id feature_id,
				  dma_addr_t control_buf_dma_addr,
				  u32 control_buff_size,
				  u8 feature_ver)
अणु
	काष्ठा ena_com_admin_queue *admin_queue;
	काष्ठा ena_admin_get_feat_cmd get_cmd;
	पूर्णांक ret;

	अगर (!ena_com_check_supported_feature_id(ena_dev, feature_id)) अणु
		netdev_dbg(ena_dev->net_device, "Feature %d isn't supported\n",
			   feature_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&get_cmd, 0x0, माप(get_cmd));
	admin_queue = &ena_dev->admin_queue;

	get_cmd.aq_common_descriptor.opcode = ENA_ADMIN_GET_FEATURE;

	अगर (control_buff_size)
		get_cmd.aq_common_descriptor.flags =
			ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK;
	अन्यथा
		get_cmd.aq_common_descriptor.flags = 0;

	ret = ena_com_mem_addr_set(ena_dev,
				   &get_cmd.control_buffer.address,
				   control_buf_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	get_cmd.control_buffer.length = control_buff_size;
	get_cmd.feat_common.feature_version = feature_ver;
	get_cmd.feat_common.feature_id = feature_id;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)
					    &get_cmd,
					    माप(get_cmd),
					    (काष्ठा ena_admin_acq_entry *)
					    get_resp,
					    माप(*get_resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to submit get_feature command %d error: %d\n",
			   feature_id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ena_com_get_feature(काष्ठा ena_com_dev *ena_dev,
			       काष्ठा ena_admin_get_feat_resp *get_resp,
			       क्रमागत ena_admin_aq_feature_id feature_id,
			       u8 feature_ver)
अणु
	वापस ena_com_get_feature_ex(ena_dev,
				      get_resp,
				      feature_id,
				      0,
				      0,
				      feature_ver);
पूर्ण

पूर्णांक ena_com_get_current_hash_function(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_dev->rss.hash_func;
पूर्ण

अटल व्योम ena_com_hash_key_fill_शेष_key(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_admin_feature_rss_flow_hash_control *hash_key =
		(ena_dev->rss).hash_key;

	netdev_rss_key_fill(&hash_key->key, माप(hash_key->key));
	/* The key buffer is stored in the device in an array of
	 * uपूर्णांक32 elements.
	 */
	hash_key->key_parts = ENA_ADMIN_RSS_KEY_PARTS;
पूर्ण

अटल पूर्णांक ena_com_hash_key_allocate(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;

	अगर (!ena_com_check_supported_feature_id(ena_dev,
						ENA_ADMIN_RSS_HASH_FUNCTION))
		वापस -EOPNOTSUPP;

	rss->hash_key =
		dma_alloc_coherent(ena_dev->dmadev, माप(*rss->hash_key),
				   &rss->hash_key_dma_addr, GFP_KERNEL);

	अगर (unlikely(!rss->hash_key))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ena_com_hash_key_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;

	अगर (rss->hash_key)
		dma_मुक्त_coherent(ena_dev->dmadev, माप(*rss->hash_key),
				  rss->hash_key, rss->hash_key_dma_addr);
	rss->hash_key = शून्य;
पूर्ण

अटल पूर्णांक ena_com_hash_ctrl_init(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;

	rss->hash_ctrl =
		dma_alloc_coherent(ena_dev->dmadev, माप(*rss->hash_ctrl),
				   &rss->hash_ctrl_dma_addr, GFP_KERNEL);

	अगर (unlikely(!rss->hash_ctrl))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ena_com_hash_ctrl_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;

	अगर (rss->hash_ctrl)
		dma_मुक्त_coherent(ena_dev->dmadev, माप(*rss->hash_ctrl),
				  rss->hash_ctrl, rss->hash_ctrl_dma_addr);
	rss->hash_ctrl = शून्य;
पूर्ण

अटल पूर्णांक ena_com_indirect_table_allocate(काष्ठा ena_com_dev *ena_dev,
					   u16 log_size)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_get_feat_resp get_resp;
	माप_प्रकार tbl_size;
	पूर्णांक ret;

	ret = ena_com_get_feature(ena_dev, &get_resp,
				  ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG, 0);
	अगर (unlikely(ret))
		वापस ret;

	अगर ((get_resp.u.ind_table.min_size > log_size) ||
	    (get_resp.u.ind_table.max_size < log_size)) अणु
		netdev_err(ena_dev->net_device,
			   "Indirect table size doesn't fit. requested size: %d while min is:%d and max %d\n",
			   1 << log_size, 1 << get_resp.u.ind_table.min_size,
			   1 << get_resp.u.ind_table.max_size);
		वापस -EINVAL;
	पूर्ण

	tbl_size = (1ULL << log_size) *
		माप(काष्ठा ena_admin_rss_ind_table_entry);

	rss->rss_ind_tbl =
		dma_alloc_coherent(ena_dev->dmadev, tbl_size,
				   &rss->rss_ind_tbl_dma_addr, GFP_KERNEL);
	अगर (unlikely(!rss->rss_ind_tbl))
		जाओ mem_err1;

	tbl_size = (1ULL << log_size) * माप(u16);
	rss->host_rss_ind_tbl =
		devm_kzalloc(ena_dev->dmadev, tbl_size, GFP_KERNEL);
	अगर (unlikely(!rss->host_rss_ind_tbl))
		जाओ mem_err2;

	rss->tbl_log_size = log_size;

	वापस 0;

mem_err2:
	tbl_size = (1ULL << log_size) *
		माप(काष्ठा ena_admin_rss_ind_table_entry);

	dma_मुक्त_coherent(ena_dev->dmadev, tbl_size, rss->rss_ind_tbl,
			  rss->rss_ind_tbl_dma_addr);
	rss->rss_ind_tbl = शून्य;
mem_err1:
	rss->tbl_log_size = 0;
	वापस -ENOMEM;
पूर्ण

अटल व्योम ena_com_indirect_table_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	माप_प्रकार tbl_size = (1ULL << rss->tbl_log_size) *
		माप(काष्ठा ena_admin_rss_ind_table_entry);

	अगर (rss->rss_ind_tbl)
		dma_मुक्त_coherent(ena_dev->dmadev, tbl_size, rss->rss_ind_tbl,
				  rss->rss_ind_tbl_dma_addr);
	rss->rss_ind_tbl = शून्य;

	अगर (rss->host_rss_ind_tbl)
		devm_kमुक्त(ena_dev->dmadev, rss->host_rss_ind_tbl);
	rss->host_rss_ind_tbl = शून्य;
पूर्ण

अटल पूर्णांक ena_com_create_io_sq(काष्ठा ena_com_dev *ena_dev,
				काष्ठा ena_com_io_sq *io_sq, u16 cq_idx)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_admin_aq_create_sq_cmd create_cmd;
	काष्ठा ena_admin_acq_create_sq_resp_desc cmd_completion;
	u8 direction;
	पूर्णांक ret;

	स_रखो(&create_cmd, 0x0, माप(create_cmd));

	create_cmd.aq_common_descriptor.opcode = ENA_ADMIN_CREATE_SQ;

	अगर (io_sq->direction == ENA_COM_IO_QUEUE_सूचीECTION_TX)
		direction = ENA_ADMIN_SQ_सूचीECTION_TX;
	अन्यथा
		direction = ENA_ADMIN_SQ_सूचीECTION_RX;

	create_cmd.sq_identity |= (direction <<
		ENA_ADMIN_AQ_CREATE_SQ_CMD_SQ_सूचीECTION_SHIFT) &
		ENA_ADMIN_AQ_CREATE_SQ_CMD_SQ_सूचीECTION_MASK;

	create_cmd.sq_caps_2 |= io_sq->mem_queue_type &
		ENA_ADMIN_AQ_CREATE_SQ_CMD_PLACEMENT_POLICY_MASK;

	create_cmd.sq_caps_2 |= (ENA_ADMIN_COMPLETION_POLICY_DESC <<
		ENA_ADMIN_AQ_CREATE_SQ_CMD_COMPLETION_POLICY_SHIFT) &
		ENA_ADMIN_AQ_CREATE_SQ_CMD_COMPLETION_POLICY_MASK;

	create_cmd.sq_caps_3 |=
		ENA_ADMIN_AQ_CREATE_SQ_CMD_IS_PHYSICALLY_CONTIGUOUS_MASK;

	create_cmd.cq_idx = cq_idx;
	create_cmd.sq_depth = io_sq->q_depth;

	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST) अणु
		ret = ena_com_mem_addr_set(ena_dev,
					   &create_cmd.sq_ba,
					   io_sq->desc_addr.phys_addr);
		अगर (unlikely(ret)) अणु
			netdev_err(ena_dev->net_device,
				   "Memory address set failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&create_cmd,
					    माप(create_cmd),
					    (काष्ठा ena_admin_acq_entry *)&cmd_completion,
					    माप(cmd_completion));
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device,
			   "Failed to create IO SQ. error: %d\n", ret);
		वापस ret;
	पूर्ण

	io_sq->idx = cmd_completion.sq_idx;

	io_sq->db_addr = (u32 __iomem *)((uपूर्णांकptr_t)ena_dev->reg_bar +
		(uपूर्णांकptr_t)cmd_completion.sq_करोorbell_offset);

	अगर (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) अणु
		io_sq->header_addr = (u8 __iomem *)((uपूर्णांकptr_t)ena_dev->mem_bar
				+ cmd_completion.llq_headers_offset);

		io_sq->desc_addr.pbuf_dev_addr =
			(u8 __iomem *)((uपूर्णांकptr_t)ena_dev->mem_bar +
			cmd_completion.llq_descriptors_offset);
	पूर्ण

	netdev_dbg(ena_dev->net_device, "Created sq[%u], depth[%u]\n",
		   io_sq->idx, io_sq->q_depth);

	वापस ret;
पूर्ण

अटल पूर्णांक ena_com_ind_tbl_convert_to_device(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_com_io_sq *io_sq;
	u16 qid;
	पूर्णांक i;

	क्रम (i = 0; i < 1 << rss->tbl_log_size; i++) अणु
		qid = rss->host_rss_ind_tbl[i];
		अगर (qid >= ENA_TOTAL_NUM_QUEUES)
			वापस -EINVAL;

		io_sq = &ena_dev->io_sq_queues[qid];

		अगर (io_sq->direction != ENA_COM_IO_QUEUE_सूचीECTION_RX)
			वापस -EINVAL;

		rss->rss_ind_tbl[i].cq_idx = io_sq->idx;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ena_com_update_पूर्णांकr_delay_resolution(काष्ठा ena_com_dev *ena_dev,
						 u16 पूर्णांकr_delay_resolution)
अणु
	u16 prev_पूर्णांकr_delay_resolution = ena_dev->पूर्णांकr_delay_resolution;

	अगर (unlikely(!पूर्णांकr_delay_resolution)) अणु
		netdev_err(ena_dev->net_device,
			   "Illegal intr_delay_resolution provided. Going to use default 1 usec resolution\n");
		पूर्णांकr_delay_resolution = ENA_DEFAULT_INTR_DELAY_RESOLUTION;
	पूर्ण

	/* update Rx */
	ena_dev->पूर्णांकr_moder_rx_पूर्णांकerval =
		ena_dev->पूर्णांकr_moder_rx_पूर्णांकerval *
		prev_पूर्णांकr_delay_resolution /
		पूर्णांकr_delay_resolution;

	/* update Tx */
	ena_dev->पूर्णांकr_moder_tx_पूर्णांकerval =
		ena_dev->पूर्णांकr_moder_tx_पूर्णांकerval *
		prev_पूर्णांकr_delay_resolution /
		पूर्णांकr_delay_resolution;

	ena_dev->पूर्णांकr_delay_resolution = पूर्णांकr_delay_resolution;
पूर्ण

/*****************************************************************************/
/*******************************      API       ******************************/
/*****************************************************************************/

पूर्णांक ena_com_execute_admin_command(काष्ठा ena_com_admin_queue *admin_queue,
				  काष्ठा ena_admin_aq_entry *cmd,
				  माप_प्रकार cmd_size,
				  काष्ठा ena_admin_acq_entry *comp,
				  माप_प्रकार comp_size)
अणु
	काष्ठा ena_comp_ctx *comp_ctx;
	पूर्णांक ret;

	comp_ctx = ena_com_submit_admin_cmd(admin_queue, cmd, cmd_size,
					    comp, comp_size);
	अगर (IS_ERR(comp_ctx)) अणु
		ret = PTR_ERR(comp_ctx);
		अगर (ret == -ENODEV)
			netdev_dbg(admin_queue->ena_dev->net_device,
				   "Failed to submit command [%d]\n", ret);
		अन्यथा
			netdev_err(admin_queue->ena_dev->net_device,
				   "Failed to submit command [%d]\n", ret);

		वापस ret;
	पूर्ण

	ret = ena_com_रुको_and_process_admin_cq(comp_ctx, admin_queue);
	अगर (unlikely(ret)) अणु
		अगर (admin_queue->running_state)
			netdev_err(admin_queue->ena_dev->net_device,
				   "Failed to process command. ret = %d\n", ret);
		अन्यथा
			netdev_dbg(admin_queue->ena_dev->net_device,
				   "Failed to process command. ret = %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ena_com_create_io_cq(काष्ठा ena_com_dev *ena_dev,
			 काष्ठा ena_com_io_cq *io_cq)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_admin_aq_create_cq_cmd create_cmd;
	काष्ठा ena_admin_acq_create_cq_resp_desc cmd_completion;
	पूर्णांक ret;

	स_रखो(&create_cmd, 0x0, माप(create_cmd));

	create_cmd.aq_common_descriptor.opcode = ENA_ADMIN_CREATE_CQ;

	create_cmd.cq_caps_2 |= (io_cq->cdesc_entry_size_in_bytes / 4) &
		ENA_ADMIN_AQ_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS_MASK;
	create_cmd.cq_caps_1 |=
		ENA_ADMIN_AQ_CREATE_CQ_CMD_INTERRUPT_MODE_ENABLED_MASK;

	create_cmd.msix_vector = io_cq->msix_vector;
	create_cmd.cq_depth = io_cq->q_depth;

	ret = ena_com_mem_addr_set(ena_dev,
				   &create_cmd.cq_ba,
				   io_cq->cdesc_addr.phys_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&create_cmd,
					    माप(create_cmd),
					    (काष्ठा ena_admin_acq_entry *)&cmd_completion,
					    माप(cmd_completion));
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device,
			   "Failed to create IO CQ. error: %d\n", ret);
		वापस ret;
	पूर्ण

	io_cq->idx = cmd_completion.cq_idx;

	io_cq->unmask_reg = (u32 __iomem *)((uपूर्णांकptr_t)ena_dev->reg_bar +
		cmd_completion.cq_पूर्णांकerrupt_unmask_रेजिस्टर_offset);

	अगर (cmd_completion.cq_head_db_रेजिस्टर_offset)
		io_cq->cq_head_db_reg =
			(u32 __iomem *)((uपूर्णांकptr_t)ena_dev->reg_bar +
			cmd_completion.cq_head_db_रेजिस्टर_offset);

	अगर (cmd_completion.numa_node_रेजिस्टर_offset)
		io_cq->numa_node_cfg_reg =
			(u32 __iomem *)((uपूर्णांकptr_t)ena_dev->reg_bar +
			cmd_completion.numa_node_रेजिस्टर_offset);

	netdev_dbg(ena_dev->net_device, "Created cq[%u], depth[%u]\n",
		   io_cq->idx, io_cq->q_depth);

	वापस ret;
पूर्ण

पूर्णांक ena_com_get_io_handlers(काष्ठा ena_com_dev *ena_dev, u16 qid,
			    काष्ठा ena_com_io_sq **io_sq,
			    काष्ठा ena_com_io_cq **io_cq)
अणु
	अगर (qid >= ENA_TOTAL_NUM_QUEUES) अणु
		netdev_err(ena_dev->net_device,
			   "Invalid queue number %d but the max is %d\n", qid,
			   ENA_TOTAL_NUM_QUEUES);
		वापस -EINVAL;
	पूर्ण

	*io_sq = &ena_dev->io_sq_queues[qid];
	*io_cq = &ena_dev->io_cq_queues[qid];

	वापस 0;
पूर्ण

व्योम ena_com_पात_admin_commands(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_comp_ctx *comp_ctx;
	u16 i;

	अगर (!admin_queue->comp_ctx)
		वापस;

	क्रम (i = 0; i < admin_queue->q_depth; i++) अणु
		comp_ctx = get_comp_ctxt(admin_queue, i, false);
		अगर (unlikely(!comp_ctx))
			अवरोध;

		comp_ctx->status = ENA_CMD_ABORTED;

		complete(&comp_ctx->रुको_event);
	पूर्ण
पूर्ण

व्योम ena_com_रुको_क्रम_पात_completion(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	अचिन्हित दीर्घ flags = 0;
	u32 exp = 0;

	spin_lock_irqsave(&admin_queue->q_lock, flags);
	जबतक (atomic_पढ़ो(&admin_queue->outstanding_cmds) != 0) अणु
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		ena_delay_exponential_backoff_us(exp++,
						 ena_dev->ena_min_poll_delay_us);
		spin_lock_irqsave(&admin_queue->q_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&admin_queue->q_lock, flags);
पूर्ण

पूर्णांक ena_com_destroy_io_cq(काष्ठा ena_com_dev *ena_dev,
			  काष्ठा ena_com_io_cq *io_cq)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_admin_aq_destroy_cq_cmd destroy_cmd;
	काष्ठा ena_admin_acq_destroy_cq_resp_desc destroy_resp;
	पूर्णांक ret;

	स_रखो(&destroy_cmd, 0x0, माप(destroy_cmd));

	destroy_cmd.cq_idx = io_cq->idx;
	destroy_cmd.aq_common_descriptor.opcode = ENA_ADMIN_DESTROY_CQ;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&destroy_cmd,
					    माप(destroy_cmd),
					    (काष्ठा ena_admin_acq_entry *)&destroy_resp,
					    माप(destroy_resp));

	अगर (unlikely(ret && (ret != -ENODEV)))
		netdev_err(ena_dev->net_device,
			   "Failed to destroy IO CQ. error: %d\n", ret);

	वापस ret;
पूर्ण

bool ena_com_get_admin_running_state(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_dev->admin_queue.running_state;
पूर्ण

व्योम ena_com_set_admin_running_state(काष्ठा ena_com_dev *ena_dev, bool state)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&admin_queue->q_lock, flags);
	ena_dev->admin_queue.running_state = state;
	spin_unlock_irqrestore(&admin_queue->q_lock, flags);
पूर्ण

व्योम ena_com_admin_aenq_enable(काष्ठा ena_com_dev *ena_dev)
अणु
	u16 depth = ena_dev->aenq.q_depth;

	WARN(ena_dev->aenq.head != depth, "Invalid AENQ state\n");

	/* Init head_db to mark that all entries in the queue
	 * are initially available
	 */
	ग_लिखोl(depth, ena_dev->reg_bar + ENA_REGS_AENQ_HEAD_DB_OFF);
पूर्ण

पूर्णांक ena_com_set_aenq_config(काष्ठा ena_com_dev *ena_dev, u32 groups_flag)
अणु
	काष्ठा ena_com_admin_queue *admin_queue;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	काष्ठा ena_admin_get_feat_resp get_resp;
	पूर्णांक ret;

	ret = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_AENQ_CONFIG, 0);
	अगर (ret) अणु
		dev_info(ena_dev->dmadev, "Can't get aenq configuration\n");
		वापस ret;
	पूर्ण

	अगर ((get_resp.u.aenq.supported_groups & groups_flag) != groups_flag) अणु
		netdev_warn(ena_dev->net_device,
			    "Trying to set unsupported aenq events. supported flag: 0x%x asked flag: 0x%x\n",
			    get_resp.u.aenq.supported_groups, groups_flag);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&cmd, 0x0, माप(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags = 0;
	cmd.feat_common.feature_id = ENA_ADMIN_AENQ_CONFIG;
	cmd.u.aenq.enabled_groups = groups_flag;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to config AENQ ret: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ena_com_get_dma_width(काष्ठा ena_com_dev *ena_dev)
अणु
	u32 caps = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_CAPS_OFF);
	u32 width;

	अगर (unlikely(caps == ENA_MMIO_READ_TIMEOUT)) अणु
		netdev_err(ena_dev->net_device, "Reg read timeout occurred\n");
		वापस -ETIME;
	पूर्ण

	width = (caps & ENA_REGS_CAPS_DMA_ADDR_WIDTH_MASK) >>
		ENA_REGS_CAPS_DMA_ADDR_WIDTH_SHIFT;

	netdev_dbg(ena_dev->net_device, "ENA dma width: %d\n", width);

	अगर ((width < 32) || width > ENA_MAX_PHYS_ADDR_SIZE_BITS) अणु
		netdev_err(ena_dev->net_device, "DMA width illegal value: %d\n",
			   width);
		वापस -EINVAL;
	पूर्ण

	ena_dev->dma_addr_bits = width;

	वापस width;
पूर्ण

पूर्णांक ena_com_validate_version(काष्ठा ena_com_dev *ena_dev)
अणु
	u32 ver;
	u32 ctrl_ver;
	u32 ctrl_ver_masked;

	/* Make sure the ENA version and the controller version are at least
	 * as the driver expects
	 */
	ver = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_VERSION_OFF);
	ctrl_ver = ena_com_reg_bar_पढ़ो32(ena_dev,
					  ENA_REGS_CONTROLLER_VERSION_OFF);

	अगर (unlikely((ver == ENA_MMIO_READ_TIMEOUT) ||
		     (ctrl_ver == ENA_MMIO_READ_TIMEOUT))) अणु
		netdev_err(ena_dev->net_device, "Reg read timeout occurred\n");
		वापस -ETIME;
	पूर्ण

	dev_info(ena_dev->dmadev, "ENA device version: %d.%d\n",
		 (ver & ENA_REGS_VERSION_MAJOR_VERSION_MASK) >>
			 ENA_REGS_VERSION_MAJOR_VERSION_SHIFT,
		 ver & ENA_REGS_VERSION_MINOR_VERSION_MASK);

	dev_info(ena_dev->dmadev,
		 "ENA controller version: %d.%d.%d implementation version %d\n",
		 (ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) >>
			 ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT,
		 (ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) >>
			 ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT,
		 (ctrl_ver & ENA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK),
		 (ctrl_ver & ENA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK) >>
			 ENA_REGS_CONTROLLER_VERSION_IMPL_ID_SHIFT);

	ctrl_ver_masked =
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) |
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) |
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK);

	/* Validate the ctrl version without the implementation ID */
	अगर (ctrl_ver_masked < MIN_ENA_CTRL_VER) अणु
		netdev_err(ena_dev->net_device,
			   "ENA ctrl version is lower than the minimal ctrl version the driver supports\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ena_com_मुक्त_ena_admin_queue_comp_ctx(काष्ठा ena_com_dev *ena_dev,
				      काष्ठा ena_com_admin_queue *admin_queue)

अणु
	अगर (!admin_queue->comp_ctx)
		वापस;

	devm_kमुक्त(ena_dev->dmadev, admin_queue->comp_ctx);

	admin_queue->comp_ctx = शून्य;
पूर्ण

व्योम ena_com_admin_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_com_admin_cq *cq = &admin_queue->cq;
	काष्ठा ena_com_admin_sq *sq = &admin_queue->sq;
	काष्ठा ena_com_aenq *aenq = &ena_dev->aenq;
	u16 size;

	ena_com_मुक्त_ena_admin_queue_comp_ctx(ena_dev, admin_queue);

	size = ADMIN_SQ_SIZE(admin_queue->q_depth);
	अगर (sq->entries)
		dma_मुक्त_coherent(ena_dev->dmadev, size, sq->entries,
				  sq->dma_addr);
	sq->entries = शून्य;

	size = ADMIN_CQ_SIZE(admin_queue->q_depth);
	अगर (cq->entries)
		dma_मुक्त_coherent(ena_dev->dmadev, size, cq->entries,
				  cq->dma_addr);
	cq->entries = शून्य;

	size = ADMIN_AENQ_SIZE(aenq->q_depth);
	अगर (ena_dev->aenq.entries)
		dma_मुक्त_coherent(ena_dev->dmadev, size, aenq->entries,
				  aenq->dma_addr);
	aenq->entries = शून्य;
पूर्ण

व्योम ena_com_set_admin_polling_mode(काष्ठा ena_com_dev *ena_dev, bool polling)
अणु
	u32 mask_value = 0;

	अगर (polling)
		mask_value = ENA_REGS_ADMIN_INTR_MASK;

	ग_लिखोl(mask_value, ena_dev->reg_bar + ENA_REGS_INTR_MASK_OFF);
	ena_dev->admin_queue.polling = polling;
पूर्ण

व्योम ena_com_set_admin_स्वतः_polling_mode(काष्ठा ena_com_dev *ena_dev,
					 bool polling)
अणु
	ena_dev->admin_queue.स्वतः_polling = polling;
पूर्ण

पूर्णांक ena_com_mmio_reg_पढ़ो_request_init(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_mmio_पढ़ो *mmio_पढ़ो = &ena_dev->mmio_पढ़ो;

	spin_lock_init(&mmio_पढ़ो->lock);
	mmio_पढ़ो->पढ़ो_resp =
		dma_alloc_coherent(ena_dev->dmadev,
				   माप(*mmio_पढ़ो->पढ़ो_resp),
				   &mmio_पढ़ो->पढ़ो_resp_dma_addr, GFP_KERNEL);
	अगर (unlikely(!mmio_पढ़ो->पढ़ो_resp))
		जाओ err;

	ena_com_mmio_reg_पढ़ो_request_ग_लिखो_dev_addr(ena_dev);

	mmio_पढ़ो->पढ़ो_resp->req_id = 0x0;
	mmio_पढ़ो->seq_num = 0x0;
	mmio_पढ़ो->पढ़ोless_supported = true;

	वापस 0;

err:

	वापस -ENOMEM;
पूर्ण

व्योम ena_com_set_mmio_पढ़ो_mode(काष्ठा ena_com_dev *ena_dev, bool पढ़ोless_supported)
अणु
	काष्ठा ena_com_mmio_पढ़ो *mmio_पढ़ो = &ena_dev->mmio_पढ़ो;

	mmio_पढ़ो->पढ़ोless_supported = पढ़ोless_supported;
पूर्ण

व्योम ena_com_mmio_reg_पढ़ो_request_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_mmio_पढ़ो *mmio_पढ़ो = &ena_dev->mmio_पढ़ो;

	ग_लिखोl(0x0, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_LO_OFF);
	ग_लिखोl(0x0, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_HI_OFF);

	dma_मुक्त_coherent(ena_dev->dmadev, माप(*mmio_पढ़ो->पढ़ो_resp),
			  mmio_पढ़ो->पढ़ो_resp, mmio_पढ़ो->पढ़ो_resp_dma_addr);

	mmio_पढ़ो->पढ़ो_resp = शून्य;
पूर्ण

व्योम ena_com_mmio_reg_पढ़ो_request_ग_लिखो_dev_addr(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_mmio_पढ़ो *mmio_पढ़ो = &ena_dev->mmio_पढ़ो;
	u32 addr_low, addr_high;

	addr_low = ENA_DMA_ADDR_TO_UINT32_LOW(mmio_पढ़ो->पढ़ो_resp_dma_addr);
	addr_high = ENA_DMA_ADDR_TO_UINT32_HIGH(mmio_पढ़ो->पढ़ो_resp_dma_addr);

	ग_लिखोl(addr_low, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_LO_OFF);
	ग_लिखोl(addr_high, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_HI_OFF);
पूर्ण

पूर्णांक ena_com_admin_init(काष्ठा ena_com_dev *ena_dev,
		       काष्ठा ena_aenq_handlers *aenq_handlers)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	u32 aq_caps, acq_caps, dev_sts, addr_low, addr_high;
	पूर्णांक ret;

	dev_sts = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_DEV_STS_OFF);

	अगर (unlikely(dev_sts == ENA_MMIO_READ_TIMEOUT)) अणु
		netdev_err(ena_dev->net_device, "Reg read timeout occurred\n");
		वापस -ETIME;
	पूर्ण

	अगर (!(dev_sts & ENA_REGS_DEV_STS_READY_MASK)) अणु
		netdev_err(ena_dev->net_device,
			   "Device isn't ready, abort com init\n");
		वापस -ENODEV;
	पूर्ण

	admin_queue->q_depth = ENA_ADMIN_QUEUE_DEPTH;

	admin_queue->q_dmadev = ena_dev->dmadev;
	admin_queue->polling = false;
	admin_queue->curr_cmd_id = 0;

	atomic_set(&admin_queue->outstanding_cmds, 0);

	spin_lock_init(&admin_queue->q_lock);

	ret = ena_com_init_comp_ctxt(admin_queue);
	अगर (ret)
		जाओ error;

	ret = ena_com_admin_init_sq(admin_queue);
	अगर (ret)
		जाओ error;

	ret = ena_com_admin_init_cq(admin_queue);
	अगर (ret)
		जाओ error;

	admin_queue->sq.db_addr = (u32 __iomem *)((uपूर्णांकptr_t)ena_dev->reg_bar +
		ENA_REGS_AQ_DB_OFF);

	addr_low = ENA_DMA_ADDR_TO_UINT32_LOW(admin_queue->sq.dma_addr);
	addr_high = ENA_DMA_ADDR_TO_UINT32_HIGH(admin_queue->sq.dma_addr);

	ग_लिखोl(addr_low, ena_dev->reg_bar + ENA_REGS_AQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, ena_dev->reg_bar + ENA_REGS_AQ_BASE_HI_OFF);

	addr_low = ENA_DMA_ADDR_TO_UINT32_LOW(admin_queue->cq.dma_addr);
	addr_high = ENA_DMA_ADDR_TO_UINT32_HIGH(admin_queue->cq.dma_addr);

	ग_लिखोl(addr_low, ena_dev->reg_bar + ENA_REGS_ACQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, ena_dev->reg_bar + ENA_REGS_ACQ_BASE_HI_OFF);

	aq_caps = 0;
	aq_caps |= admin_queue->q_depth & ENA_REGS_AQ_CAPS_AQ_DEPTH_MASK;
	aq_caps |= (माप(काष्ठा ena_admin_aq_entry) <<
			ENA_REGS_AQ_CAPS_AQ_ENTRY_SIZE_SHIFT) &
			ENA_REGS_AQ_CAPS_AQ_ENTRY_SIZE_MASK;

	acq_caps = 0;
	acq_caps |= admin_queue->q_depth & ENA_REGS_ACQ_CAPS_ACQ_DEPTH_MASK;
	acq_caps |= (माप(काष्ठा ena_admin_acq_entry) <<
		ENA_REGS_ACQ_CAPS_ACQ_ENTRY_SIZE_SHIFT) &
		ENA_REGS_ACQ_CAPS_ACQ_ENTRY_SIZE_MASK;

	ग_लिखोl(aq_caps, ena_dev->reg_bar + ENA_REGS_AQ_CAPS_OFF);
	ग_लिखोl(acq_caps, ena_dev->reg_bar + ENA_REGS_ACQ_CAPS_OFF);
	ret = ena_com_admin_init_aenq(ena_dev, aenq_handlers);
	अगर (ret)
		जाओ error;

	admin_queue->ena_dev = ena_dev;
	admin_queue->running_state = true;

	वापस 0;
error:
	ena_com_admin_destroy(ena_dev);

	वापस ret;
पूर्ण

पूर्णांक ena_com_create_io_queue(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_com_create_io_ctx *ctx)
अणु
	काष्ठा ena_com_io_sq *io_sq;
	काष्ठा ena_com_io_cq *io_cq;
	पूर्णांक ret;

	अगर (ctx->qid >= ENA_TOTAL_NUM_QUEUES) अणु
		netdev_err(ena_dev->net_device,
			   "Qid (%d) is bigger than max num of queues (%d)\n",
			   ctx->qid, ENA_TOTAL_NUM_QUEUES);
		वापस -EINVAL;
	पूर्ण

	io_sq = &ena_dev->io_sq_queues[ctx->qid];
	io_cq = &ena_dev->io_cq_queues[ctx->qid];

	स_रखो(io_sq, 0x0, माप(*io_sq));
	स_रखो(io_cq, 0x0, माप(*io_cq));

	/* Init CQ */
	io_cq->q_depth = ctx->queue_size;
	io_cq->direction = ctx->direction;
	io_cq->qid = ctx->qid;

	io_cq->msix_vector = ctx->msix_vector;

	io_sq->q_depth = ctx->queue_size;
	io_sq->direction = ctx->direction;
	io_sq->qid = ctx->qid;

	io_sq->mem_queue_type = ctx->mem_queue_type;

	अगर (ctx->direction == ENA_COM_IO_QUEUE_सूचीECTION_TX)
		/* header length is limited to 8 bits */
		io_sq->tx_max_header_size =
			min_t(u32, ena_dev->tx_max_header_size, SZ_256);

	ret = ena_com_init_io_sq(ena_dev, ctx, io_sq);
	अगर (ret)
		जाओ error;
	ret = ena_com_init_io_cq(ena_dev, ctx, io_cq);
	अगर (ret)
		जाओ error;

	ret = ena_com_create_io_cq(ena_dev, io_cq);
	अगर (ret)
		जाओ error;

	ret = ena_com_create_io_sq(ena_dev, io_sq, io_cq->idx);
	अगर (ret)
		जाओ destroy_io_cq;

	वापस 0;

destroy_io_cq:
	ena_com_destroy_io_cq(ena_dev, io_cq);
error:
	ena_com_io_queue_मुक्त(ena_dev, io_sq, io_cq);
	वापस ret;
पूर्ण

व्योम ena_com_destroy_io_queue(काष्ठा ena_com_dev *ena_dev, u16 qid)
अणु
	काष्ठा ena_com_io_sq *io_sq;
	काष्ठा ena_com_io_cq *io_cq;

	अगर (qid >= ENA_TOTAL_NUM_QUEUES) अणु
		netdev_err(ena_dev->net_device,
			   "Qid (%d) is bigger than max num of queues (%d)\n",
			   qid, ENA_TOTAL_NUM_QUEUES);
		वापस;
	पूर्ण

	io_sq = &ena_dev->io_sq_queues[qid];
	io_cq = &ena_dev->io_cq_queues[qid];

	ena_com_destroy_io_sq(ena_dev, io_sq);
	ena_com_destroy_io_cq(ena_dev, io_cq);

	ena_com_io_queue_मुक्त(ena_dev, io_sq, io_cq);
पूर्ण

पूर्णांक ena_com_get_link_params(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_admin_get_feat_resp *resp)
अणु
	वापस ena_com_get_feature(ena_dev, resp, ENA_ADMIN_LINK_CONFIG, 0);
पूर्ण

पूर्णांक ena_com_get_dev_attr_feat(काष्ठा ena_com_dev *ena_dev,
			      काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx)
अणु
	काष्ठा ena_admin_get_feat_resp get_resp;
	पूर्णांक rc;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_DEVICE_ATTRIBUTES, 0);
	अगर (rc)
		वापस rc;

	स_नकल(&get_feat_ctx->dev_attr, &get_resp.u.dev_attr,
	       माप(get_resp.u.dev_attr));

	ena_dev->supported_features = get_resp.u.dev_attr.supported_features;

	अगर (ena_dev->supported_features & BIT(ENA_ADMIN_MAX_QUEUES_EXT)) अणु
		rc = ena_com_get_feature(ena_dev, &get_resp,
					 ENA_ADMIN_MAX_QUEUES_EXT,
					 ENA_FEATURE_MAX_QUEUE_EXT_VER);
		अगर (rc)
			वापस rc;

		अगर (get_resp.u.max_queue_ext.version != ENA_FEATURE_MAX_QUEUE_EXT_VER)
			वापस -EINVAL;

		स_नकल(&get_feat_ctx->max_queue_ext, &get_resp.u.max_queue_ext,
		       माप(get_resp.u.max_queue_ext));
		ena_dev->tx_max_header_size =
			get_resp.u.max_queue_ext.max_queue_ext.max_tx_header_size;
	पूर्ण अन्यथा अणु
		rc = ena_com_get_feature(ena_dev, &get_resp,
					 ENA_ADMIN_MAX_QUEUES_NUM, 0);
		स_नकल(&get_feat_ctx->max_queues, &get_resp.u.max_queue,
		       माप(get_resp.u.max_queue));
		ena_dev->tx_max_header_size =
			get_resp.u.max_queue.max_header_size;

		अगर (rc)
			वापस rc;
	पूर्ण

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_AENQ_CONFIG, 0);
	अगर (rc)
		वापस rc;

	स_नकल(&get_feat_ctx->aenq, &get_resp.u.aenq,
	       माप(get_resp.u.aenq));

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_STATELESS_OFFLOAD_CONFIG, 0);
	अगर (rc)
		वापस rc;

	स_नकल(&get_feat_ctx->offload, &get_resp.u.offload,
	       माप(get_resp.u.offload));

	/* Driver hपूर्णांकs isn't mandatory admin command. So in हाल the
	 * command isn't supported set driver hपूर्णांकs to 0
	 */
	rc = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_HW_HINTS, 0);

	अगर (!rc)
		स_नकल(&get_feat_ctx->hw_hपूर्णांकs, &get_resp.u.hw_hपूर्णांकs,
		       माप(get_resp.u.hw_hपूर्णांकs));
	अन्यथा अगर (rc == -EOPNOTSUPP)
		स_रखो(&get_feat_ctx->hw_hपूर्णांकs, 0x0,
		       माप(get_feat_ctx->hw_hपूर्णांकs));
	अन्यथा
		वापस rc;

	rc = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_LLQ, 0);
	अगर (!rc)
		स_नकल(&get_feat_ctx->llq, &get_resp.u.llq,
		       माप(get_resp.u.llq));
	अन्यथा अगर (rc == -EOPNOTSUPP)
		स_रखो(&get_feat_ctx->llq, 0x0, माप(get_feat_ctx->llq));
	अन्यथा
		वापस rc;

	वापस 0;
पूर्ण

व्योम ena_com_admin_q_comp_पूर्णांकr_handler(काष्ठा ena_com_dev *ena_dev)
अणु
	ena_com_handle_admin_completion(&ena_dev->admin_queue);
पूर्ण

/* ena_handle_specअगरic_aenq_event:
 * वापस the handler that is relevant to the specअगरic event group
 */
अटल ena_aenq_handler ena_com_get_specअगरic_aenq_cb(काष्ठा ena_com_dev *ena_dev,
						     u16 group)
अणु
	काष्ठा ena_aenq_handlers *aenq_handlers = ena_dev->aenq.aenq_handlers;

	अगर ((group < ENA_MAX_HANDLERS) && aenq_handlers->handlers[group])
		वापस aenq_handlers->handlers[group];

	वापस aenq_handlers->unimplemented_handler;
पूर्ण

/* ena_aenq_पूर्णांकr_handler:
 * handles the aenq incoming events.
 * pop events from the queue and apply the specअगरic handler
 */
व्योम ena_com_aenq_पूर्णांकr_handler(काष्ठा ena_com_dev *ena_dev, व्योम *data)
अणु
	काष्ठा ena_admin_aenq_entry *aenq_e;
	काष्ठा ena_admin_aenq_common_desc *aenq_common;
	काष्ठा ena_com_aenq *aenq  = &ena_dev->aenq;
	u64 बारtamp;
	ena_aenq_handler handler_cb;
	u16 masked_head, processed = 0;
	u8 phase;

	masked_head = aenq->head & (aenq->q_depth - 1);
	phase = aenq->phase;
	aenq_e = &aenq->entries[masked_head]; /* Get first entry */
	aenq_common = &aenq_e->aenq_common_desc;

	/* Go over all the events */
	जबतक ((READ_ONCE(aenq_common->flags) &
		ENA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK) == phase) अणु
		/* Make sure the phase bit (ownership) is as expected beक्रमe
		 * पढ़ोing the rest of the descriptor.
		 */
		dma_rmb();

		बारtamp = (u64)aenq_common->बारtamp_low |
			((u64)aenq_common->बारtamp_high << 32);

		netdev_dbg(ena_dev->net_device,
			   "AENQ! Group[%x] Syndrome[%x] timestamp: [%llus]\n",
			   aenq_common->group, aenq_common->syndrome, बारtamp);

		/* Handle specअगरic event*/
		handler_cb = ena_com_get_specअगरic_aenq_cb(ena_dev,
							  aenq_common->group);
		handler_cb(data, aenq_e); /* call the actual event handler*/

		/* Get next event entry */
		masked_head++;
		processed++;

		अगर (unlikely(masked_head == aenq->q_depth)) अणु
			masked_head = 0;
			phase = !phase;
		पूर्ण
		aenq_e = &aenq->entries[masked_head];
		aenq_common = &aenq_e->aenq_common_desc;
	पूर्ण

	aenq->head += processed;
	aenq->phase = phase;

	/* Don't update aenq doorbell if there weren't any processed events */
	अगर (!processed)
		वापस;

	/* ग_लिखो the aenq करोorbell after all AENQ descriptors were पढ़ो */
	mb();
	ग_लिखोl_relaxed((u32)aenq->head,
		       ena_dev->reg_bar + ENA_REGS_AENQ_HEAD_DB_OFF);
पूर्ण

पूर्णांक ena_com_dev_reset(काष्ठा ena_com_dev *ena_dev,
		      क्रमागत ena_regs_reset_reason_types reset_reason)
अणु
	u32 stat, समयout, cap, reset_val;
	पूर्णांक rc;

	stat = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_DEV_STS_OFF);
	cap = ena_com_reg_bar_पढ़ो32(ena_dev, ENA_REGS_CAPS_OFF);

	अगर (unlikely((stat == ENA_MMIO_READ_TIMEOUT) ||
		     (cap == ENA_MMIO_READ_TIMEOUT))) अणु
		netdev_err(ena_dev->net_device, "Reg read32 timeout occurred\n");
		वापस -ETIME;
	पूर्ण

	अगर ((stat & ENA_REGS_DEV_STS_READY_MASK) == 0) अणु
		netdev_err(ena_dev->net_device,
			   "Device isn't ready, can't reset device\n");
		वापस -EINVAL;
	पूर्ण

	समयout = (cap & ENA_REGS_CAPS_RESET_TIMEOUT_MASK) >>
			ENA_REGS_CAPS_RESET_TIMEOUT_SHIFT;
	अगर (समयout == 0) अणु
		netdev_err(ena_dev->net_device, "Invalid timeout value\n");
		वापस -EINVAL;
	पूर्ण

	/* start reset */
	reset_val = ENA_REGS_DEV_CTL_DEV_RESET_MASK;
	reset_val |= (reset_reason << ENA_REGS_DEV_CTL_RESET_REASON_SHIFT) &
		     ENA_REGS_DEV_CTL_RESET_REASON_MASK;
	ग_लिखोl(reset_val, ena_dev->reg_bar + ENA_REGS_DEV_CTL_OFF);

	/* Write again the MMIO पढ़ो request address */
	ena_com_mmio_reg_पढ़ो_request_ग_लिखो_dev_addr(ena_dev);

	rc = रुको_क्रम_reset_state(ena_dev, समयout,
				  ENA_REGS_DEV_STS_RESET_IN_PROGRESS_MASK);
	अगर (rc != 0) अणु
		netdev_err(ena_dev->net_device,
			   "Reset indication didn't turn on\n");
		वापस rc;
	पूर्ण

	/* reset करोne */
	ग_लिखोl(0, ena_dev->reg_bar + ENA_REGS_DEV_CTL_OFF);
	rc = रुको_क्रम_reset_state(ena_dev, समयout, 0);
	अगर (rc != 0) अणु
		netdev_err(ena_dev->net_device,
			   "Reset indication didn't turn off\n");
		वापस rc;
	पूर्ण

	समयout = (cap & ENA_REGS_CAPS_ADMIN_CMD_TO_MASK) >>
		ENA_REGS_CAPS_ADMIN_CMD_TO_SHIFT;
	अगर (समयout)
		/* the resolution of समयout reg is 100ms */
		ena_dev->admin_queue.completion_समयout = समयout * 100000;
	अन्यथा
		ena_dev->admin_queue.completion_समयout = ADMIN_CMD_TIMEOUT_US;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_get_dev_stats(काष्ठा ena_com_dev *ena_dev,
			     काष्ठा ena_com_stats_ctx *ctx,
			     क्रमागत ena_admin_get_stats_type type)
अणु
	काष्ठा ena_admin_aq_get_stats_cmd *get_cmd = &ctx->get_cmd;
	काष्ठा ena_admin_acq_get_stats_resp *get_resp = &ctx->get_resp;
	काष्ठा ena_com_admin_queue *admin_queue;
	पूर्णांक ret;

	admin_queue = &ena_dev->admin_queue;

	get_cmd->aq_common_descriptor.opcode = ENA_ADMIN_GET_STATS;
	get_cmd->aq_common_descriptor.flags = 0;
	get_cmd->type = type;

	ret =  ena_com_execute_admin_command(admin_queue,
					     (काष्ठा ena_admin_aq_entry *)get_cmd,
					     माप(*get_cmd),
					     (काष्ठा ena_admin_acq_entry *)get_resp,
					     माप(*get_resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to get stats. error: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ena_com_get_eni_stats(काष्ठा ena_com_dev *ena_dev,
			  काष्ठा ena_admin_eni_stats *stats)
अणु
	काष्ठा ena_com_stats_ctx ctx;
	पूर्णांक ret;

	स_रखो(&ctx, 0x0, माप(ctx));
	ret = ena_get_dev_stats(ena_dev, &ctx, ENA_ADMIN_GET_STATS_TYPE_ENI);
	अगर (likely(ret == 0))
		स_नकल(stats, &ctx.get_resp.u.eni_stats,
		       माप(ctx.get_resp.u.eni_stats));

	वापस ret;
पूर्ण

पूर्णांक ena_com_get_dev_basic_stats(काष्ठा ena_com_dev *ena_dev,
				काष्ठा ena_admin_basic_stats *stats)
अणु
	काष्ठा ena_com_stats_ctx ctx;
	पूर्णांक ret;

	स_रखो(&ctx, 0x0, माप(ctx));
	ret = ena_get_dev_stats(ena_dev, &ctx, ENA_ADMIN_GET_STATS_TYPE_BASIC);
	अगर (likely(ret == 0))
		स_नकल(stats, &ctx.get_resp.u.basic_stats,
		       माप(ctx.get_resp.u.basic_stats));

	वापस ret;
पूर्ण

पूर्णांक ena_com_set_dev_mtu(काष्ठा ena_com_dev *ena_dev, u32 mtu)
अणु
	काष्ठा ena_com_admin_queue *admin_queue;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	पूर्णांक ret;

	अगर (!ena_com_check_supported_feature_id(ena_dev, ENA_ADMIN_MTU)) अणु
		netdev_dbg(ena_dev->net_device, "Feature %d isn't supported\n",
			   ENA_ADMIN_MTU);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&cmd, 0x0, माप(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags = 0;
	cmd.feat_common.feature_id = ENA_ADMIN_MTU;
	cmd.u.mtu.mtu = mtu;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to set mtu %d. error: %d\n", mtu, ret);

	वापस ret;
पूर्ण

पूर्णांक ena_com_get_offload_settings(काष्ठा ena_com_dev *ena_dev,
				 काष्ठा ena_admin_feature_offload_desc *offload)
अणु
	पूर्णांक ret;
	काष्ठा ena_admin_get_feat_resp resp;

	ret = ena_com_get_feature(ena_dev, &resp,
				  ENA_ADMIN_STATELESS_OFFLOAD_CONFIG, 0);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device,
			   "Failed to get offload capabilities %d\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(offload, &resp.u.offload, माप(resp.u.offload));

	वापस 0;
पूर्ण

पूर्णांक ena_com_set_hash_function(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	काष्ठा ena_admin_get_feat_resp get_resp;
	पूर्णांक ret;

	अगर (!ena_com_check_supported_feature_id(ena_dev,
						ENA_ADMIN_RSS_HASH_FUNCTION)) अणु
		netdev_dbg(ena_dev->net_device, "Feature %d isn't supported\n",
			   ENA_ADMIN_RSS_HASH_FUNCTION);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Validate hash function is supported */
	ret = ena_com_get_feature(ena_dev, &get_resp,
				  ENA_ADMIN_RSS_HASH_FUNCTION, 0);
	अगर (unlikely(ret))
		वापस ret;

	अगर (!(get_resp.u.flow_hash_func.supported_func & BIT(rss->hash_func))) अणु
		netdev_err(ena_dev->net_device,
			   "Func hash %d isn't supported by device, abort\n",
			   rss->hash_func);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&cmd, 0x0, माप(cmd));

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags =
		ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK;
	cmd.feat_common.feature_id = ENA_ADMIN_RSS_HASH_FUNCTION;
	cmd.u.flow_hash_func.init_val = rss->hash_init_val;
	cmd.u.flow_hash_func.selected_func = 1 << rss->hash_func;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.control_buffer.address,
				   rss->hash_key_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	cmd.control_buffer.length = माप(*rss->hash_key);

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device,
			   "Failed to set hash function %d. error: %d\n",
			   rss->hash_func, ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ena_com_fill_hash_function(काष्ठा ena_com_dev *ena_dev,
			       क्रमागत ena_admin_hash_functions func,
			       स्थिर u8 *key, u16 key_len, u32 init_val)
अणु
	काष्ठा ena_admin_feature_rss_flow_hash_control *hash_key;
	काष्ठा ena_admin_get_feat_resp get_resp;
	क्रमागत ena_admin_hash_functions old_func;
	काष्ठा ena_rss *rss = &ena_dev->rss;
	पूर्णांक rc;

	hash_key = rss->hash_key;

	/* Make sure size is a mult of DWs */
	अगर (unlikely(key_len & 0x3))
		वापस -EINVAL;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_FUNCTION,
				    rss->hash_key_dma_addr,
				    माप(*rss->hash_key), 0);
	अगर (unlikely(rc))
		वापस rc;

	अगर (!(BIT(func) & get_resp.u.flow_hash_func.supported_func)) अणु
		netdev_err(ena_dev->net_device,
			   "Flow hash function %d isn't supported\n", func);
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (func) अणु
	हाल ENA_ADMIN_TOEPLITZ:
		अगर (key) अणु
			अगर (key_len != माप(hash_key->key)) अणु
				netdev_err(ena_dev->net_device,
					   "key len (%u) doesn't equal the supported size (%zu)\n",
					   key_len, माप(hash_key->key));
				वापस -EINVAL;
			पूर्ण
			स_नकल(hash_key->key, key, key_len);
			rss->hash_init_val = init_val;
			hash_key->key_parts = key_len / माप(hash_key->key[0]);
		पूर्ण
		अवरोध;
	हाल ENA_ADMIN_CRC32:
		rss->hash_init_val = init_val;
		अवरोध;
	शेष:
		netdev_err(ena_dev->net_device, "Invalid hash function (%d)\n",
			   func);
		वापस -EINVAL;
	पूर्ण

	old_func = rss->hash_func;
	rss->hash_func = func;
	rc = ena_com_set_hash_function(ena_dev);

	/* Restore the old function */
	अगर (unlikely(rc))
		rss->hash_func = old_func;

	वापस rc;
पूर्ण

पूर्णांक ena_com_get_hash_function(काष्ठा ena_com_dev *ena_dev,
			      क्रमागत ena_admin_hash_functions *func)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_get_feat_resp get_resp;
	पूर्णांक rc;

	अगर (unlikely(!func))
		वापस -EINVAL;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_FUNCTION,
				    rss->hash_key_dma_addr,
				    माप(*rss->hash_key), 0);
	अगर (unlikely(rc))
		वापस rc;

	/* ffs() वापसs 1 in हाल the lsb is set */
	rss->hash_func = ffs(get_resp.u.flow_hash_func.selected_func);
	अगर (rss->hash_func)
		rss->hash_func--;

	*func = rss->hash_func;

	वापस 0;
पूर्ण

पूर्णांक ena_com_get_hash_key(काष्ठा ena_com_dev *ena_dev, u8 *key)
अणु
	काष्ठा ena_admin_feature_rss_flow_hash_control *hash_key =
		ena_dev->rss.hash_key;

	अगर (key)
		स_नकल(key, hash_key->key,
		       (माप_प्रकार)(hash_key->key_parts) * माप(hash_key->key[0]));

	वापस 0;
पूर्ण

पूर्णांक ena_com_get_hash_ctrl(काष्ठा ena_com_dev *ena_dev,
			  क्रमागत ena_admin_flow_hash_proto proto,
			  u16 *fields)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_get_feat_resp get_resp;
	पूर्णांक rc;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_INPUT,
				    rss->hash_ctrl_dma_addr,
				    माप(*rss->hash_ctrl), 0);
	अगर (unlikely(rc))
		वापस rc;

	अगर (fields)
		*fields = rss->hash_ctrl->selected_fields[proto].fields;

	वापस 0;
पूर्ण

पूर्णांक ena_com_set_hash_ctrl(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_feature_rss_hash_control *hash_ctrl = rss->hash_ctrl;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	पूर्णांक ret;

	अगर (!ena_com_check_supported_feature_id(ena_dev,
						ENA_ADMIN_RSS_HASH_INPUT)) अणु
		netdev_dbg(ena_dev->net_device, "Feature %d isn't supported\n",
			   ENA_ADMIN_RSS_HASH_INPUT);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&cmd, 0x0, माप(cmd));

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags =
		ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK;
	cmd.feat_common.feature_id = ENA_ADMIN_RSS_HASH_INPUT;
	cmd.u.flow_hash_input.enabled_input_sort =
		ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L3_SORT_MASK |
		ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L4_SORT_MASK;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.control_buffer.address,
				   rss->hash_ctrl_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण
	cmd.control_buffer.length = माप(*hash_ctrl);

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));
	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to set hash input. error: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ena_com_set_शेष_hash_ctrl(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_feature_rss_hash_control *hash_ctrl =
		rss->hash_ctrl;
	u16 available_fields = 0;
	पूर्णांक rc, i;

	/* Get the supported hash input */
	rc = ena_com_get_hash_ctrl(ena_dev, 0, शून्य);
	अगर (unlikely(rc))
		वापस rc;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_TCP4].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA |
		ENA_ADMIN_RSS_L4_DP | ENA_ADMIN_RSS_L4_SP;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_UDP4].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA |
		ENA_ADMIN_RSS_L4_DP | ENA_ADMIN_RSS_L4_SP;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_TCP6].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA |
		ENA_ADMIN_RSS_L4_DP | ENA_ADMIN_RSS_L4_SP;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_UDP6].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA |
		ENA_ADMIN_RSS_L4_DP | ENA_ADMIN_RSS_L4_SP;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_IP4].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_IP6].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_IP4_FRAG].fields =
		ENA_ADMIN_RSS_L3_SA | ENA_ADMIN_RSS_L3_DA;

	hash_ctrl->selected_fields[ENA_ADMIN_RSS_NOT_IP].fields =
		ENA_ADMIN_RSS_L2_DA | ENA_ADMIN_RSS_L2_SA;

	क्रम (i = 0; i < ENA_ADMIN_RSS_PROTO_NUM; i++) अणु
		available_fields = hash_ctrl->selected_fields[i].fields &
				hash_ctrl->supported_fields[i].fields;
		अगर (available_fields != hash_ctrl->selected_fields[i].fields) अणु
			netdev_err(ena_dev->net_device,
				   "Hash control doesn't support all the desire configuration. proto %x supported %x selected %x\n",
				   i, hash_ctrl->supported_fields[i].fields,
				   hash_ctrl->selected_fields[i].fields);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	rc = ena_com_set_hash_ctrl(ena_dev);

	/* In हाल of failure, restore the old hash ctrl */
	अगर (unlikely(rc))
		ena_com_get_hash_ctrl(ena_dev, 0, शून्य);

	वापस rc;
पूर्ण

पूर्णांक ena_com_fill_hash_ctrl(काष्ठा ena_com_dev *ena_dev,
			   क्रमागत ena_admin_flow_hash_proto proto,
			   u16 hash_fields)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_feature_rss_hash_control *hash_ctrl = rss->hash_ctrl;
	u16 supported_fields;
	पूर्णांक rc;

	अगर (proto >= ENA_ADMIN_RSS_PROTO_NUM) अणु
		netdev_err(ena_dev->net_device, "Invalid proto num (%u)\n",
			   proto);
		वापस -EINVAL;
	पूर्ण

	/* Get the ctrl table */
	rc = ena_com_get_hash_ctrl(ena_dev, proto, शून्य);
	अगर (unlikely(rc))
		वापस rc;

	/* Make sure all the fields are supported */
	supported_fields = hash_ctrl->supported_fields[proto].fields;
	अगर ((hash_fields & supported_fields) != hash_fields) अणु
		netdev_err(ena_dev->net_device,
			   "Proto %d doesn't support the required fields %x. supports only: %x\n",
			   proto, hash_fields, supported_fields);
	पूर्ण

	hash_ctrl->selected_fields[proto].fields = hash_fields;

	rc = ena_com_set_hash_ctrl(ena_dev);

	/* In हाल of failure, restore the old hash ctrl */
	अगर (unlikely(rc))
		ena_com_get_hash_ctrl(ena_dev, 0, शून्य);

	वापस 0;
पूर्ण

पूर्णांक ena_com_indirect_table_fill_entry(काष्ठा ena_com_dev *ena_dev,
				      u16 entry_idx, u16 entry_value)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;

	अगर (unlikely(entry_idx >= (1 << rss->tbl_log_size)))
		वापस -EINVAL;

	अगर (unlikely((entry_value > ENA_TOTAL_NUM_QUEUES)))
		वापस -EINVAL;

	rss->host_rss_ind_tbl[entry_idx] = entry_value;

	वापस 0;
पूर्ण

पूर्णांक ena_com_indirect_table_set(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;
	पूर्णांक ret;

	अगर (!ena_com_check_supported_feature_id(
		    ena_dev, ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG)) अणु
		netdev_dbg(ena_dev->net_device, "Feature %d isn't supported\n",
			   ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG);
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = ena_com_ind_tbl_convert_to_device(ena_dev);
	अगर (ret) अणु
		netdev_err(ena_dev->net_device,
			   "Failed to convert host indirection table to device table\n");
		वापस ret;
	पूर्ण

	स_रखो(&cmd, 0x0, माप(cmd));

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags =
		ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK;
	cmd.feat_common.feature_id = ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG;
	cmd.u.ind_table.size = rss->tbl_log_size;
	cmd.u.ind_table.अंतरभूत_index = 0xFFFFFFFF;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.control_buffer.address,
				   rss->rss_ind_tbl_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	cmd.control_buffer.length = (1ULL << rss->tbl_log_size) *
		माप(काष्ठा ena_admin_rss_ind_table_entry);

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to set indirect table. error: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ena_com_indirect_table_get(काष्ठा ena_com_dev *ena_dev, u32 *ind_tbl)
अणु
	काष्ठा ena_rss *rss = &ena_dev->rss;
	काष्ठा ena_admin_get_feat_resp get_resp;
	u32 tbl_size;
	पूर्णांक i, rc;

	tbl_size = (1ULL << rss->tbl_log_size) *
		माप(काष्ठा ena_admin_rss_ind_table_entry);

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG,
				    rss->rss_ind_tbl_dma_addr,
				    tbl_size, 0);
	अगर (unlikely(rc))
		वापस rc;

	अगर (!ind_tbl)
		वापस 0;

	क्रम (i = 0; i < (1 << rss->tbl_log_size); i++)
		ind_tbl[i] = rss->host_rss_ind_tbl[i];

	वापस 0;
पूर्ण

पूर्णांक ena_com_rss_init(काष्ठा ena_com_dev *ena_dev, u16 indr_tbl_log_size)
अणु
	पूर्णांक rc;

	स_रखो(&ena_dev->rss, 0x0, माप(ena_dev->rss));

	rc = ena_com_indirect_table_allocate(ena_dev, indr_tbl_log_size);
	अगर (unlikely(rc))
		जाओ err_indr_tbl;

	/* The following function might वापस unsupported in हाल the
	 * device करोesn't support setting the key / hash function. We can safely
	 * ignore this error and have indirection table support only.
	 */
	rc = ena_com_hash_key_allocate(ena_dev);
	अगर (likely(!rc))
		ena_com_hash_key_fill_शेष_key(ena_dev);
	अन्यथा अगर (rc != -EOPNOTSUPP)
		जाओ err_hash_key;

	rc = ena_com_hash_ctrl_init(ena_dev);
	अगर (unlikely(rc))
		जाओ err_hash_ctrl;

	वापस 0;

err_hash_ctrl:
	ena_com_hash_key_destroy(ena_dev);
err_hash_key:
	ena_com_indirect_table_destroy(ena_dev);
err_indr_tbl:

	वापस rc;
पूर्ण

व्योम ena_com_rss_destroy(काष्ठा ena_com_dev *ena_dev)
अणु
	ena_com_indirect_table_destroy(ena_dev);
	ena_com_hash_key_destroy(ena_dev);
	ena_com_hash_ctrl_destroy(ena_dev);

	स_रखो(&ena_dev->rss, 0x0, माप(ena_dev->rss));
पूर्ण

पूर्णांक ena_com_allocate_host_info(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_host_attribute *host_attr = &ena_dev->host_attr;

	host_attr->host_info =
		dma_alloc_coherent(ena_dev->dmadev, SZ_4K,
				   &host_attr->host_info_dma_addr, GFP_KERNEL);
	अगर (unlikely(!host_attr->host_info))
		वापस -ENOMEM;

	host_attr->host_info->ena_spec_version = ((ENA_COMMON_SPEC_VERSION_MAJOR <<
		ENA_REGS_VERSION_MAJOR_VERSION_SHIFT) |
		(ENA_COMMON_SPEC_VERSION_MINOR));

	वापस 0;
पूर्ण

पूर्णांक ena_com_allocate_debug_area(काष्ठा ena_com_dev *ena_dev,
				u32 debug_area_size)
अणु
	काष्ठा ena_host_attribute *host_attr = &ena_dev->host_attr;

	host_attr->debug_area_virt_addr =
		dma_alloc_coherent(ena_dev->dmadev, debug_area_size,
				   &host_attr->debug_area_dma_addr, GFP_KERNEL);
	अगर (unlikely(!host_attr->debug_area_virt_addr)) अणु
		host_attr->debug_area_size = 0;
		वापस -ENOMEM;
	पूर्ण

	host_attr->debug_area_size = debug_area_size;

	वापस 0;
पूर्ण

व्योम ena_com_delete_host_info(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_host_attribute *host_attr = &ena_dev->host_attr;

	अगर (host_attr->host_info) अणु
		dma_मुक्त_coherent(ena_dev->dmadev, SZ_4K, host_attr->host_info,
				  host_attr->host_info_dma_addr);
		host_attr->host_info = शून्य;
	पूर्ण
पूर्ण

व्योम ena_com_delete_debug_area(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_host_attribute *host_attr = &ena_dev->host_attr;

	अगर (host_attr->debug_area_virt_addr) अणु
		dma_मुक्त_coherent(ena_dev->dmadev, host_attr->debug_area_size,
				  host_attr->debug_area_virt_addr,
				  host_attr->debug_area_dma_addr);
		host_attr->debug_area_virt_addr = शून्य;
	पूर्ण
पूर्ण

पूर्णांक ena_com_set_host_attributes(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_host_attribute *host_attr = &ena_dev->host_attr;
	काष्ठा ena_com_admin_queue *admin_queue;
	काष्ठा ena_admin_set_feat_cmd cmd;
	काष्ठा ena_admin_set_feat_resp resp;

	पूर्णांक ret;

	/* Host attribute config is called beक्रमe ena_com_get_dev_attr_feat
	 * so ena_com can't check अगर the feature is supported.
	 */

	स_रखो(&cmd, 0x0, माप(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.feat_common.feature_id = ENA_ADMIN_HOST_ATTR_CONFIG;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.u.host_attr.debug_ba,
				   host_attr->debug_area_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.u.host_attr.os_info_ba,
				   host_attr->host_info_dma_addr);
	अगर (unlikely(ret)) अणु
		netdev_err(ena_dev->net_device, "Memory address set failed\n");
		वापस ret;
	पूर्ण

	cmd.u.host_attr.debug_area_size = host_attr->debug_area_size;

	ret = ena_com_execute_admin_command(admin_queue,
					    (काष्ठा ena_admin_aq_entry *)&cmd,
					    माप(cmd),
					    (काष्ठा ena_admin_acq_entry *)&resp,
					    माप(resp));

	अगर (unlikely(ret))
		netdev_err(ena_dev->net_device,
			   "Failed to set host attributes: %d\n", ret);

	वापस ret;
पूर्ण

/* Interrupt moderation */
bool ena_com_पूर्णांकerrupt_moderation_supported(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_com_check_supported_feature_id(ena_dev,
						  ENA_ADMIN_INTERRUPT_MODERATION);
पूर्ण

अटल पूर्णांक ena_com_update_nonadaptive_moderation_पूर्णांकerval(काष्ठा ena_com_dev *ena_dev,
							  u32 coalesce_usecs,
							  u32 पूर्णांकr_delay_resolution,
							  u32 *पूर्णांकr_moder_पूर्णांकerval)
अणु
	अगर (!पूर्णांकr_delay_resolution) अणु
		netdev_err(ena_dev->net_device,
			   "Illegal interrupt delay granularity value\n");
		वापस -EFAULT;
	पूर्ण

	*पूर्णांकr_moder_पूर्णांकerval = coalesce_usecs / पूर्णांकr_delay_resolution;

	वापस 0;
पूर्ण

पूर्णांक ena_com_update_nonadaptive_moderation_पूर्णांकerval_tx(काष्ठा ena_com_dev *ena_dev,
						      u32 tx_coalesce_usecs)
अणु
	वापस ena_com_update_nonadaptive_moderation_पूर्णांकerval(ena_dev,
							      tx_coalesce_usecs,
							      ena_dev->पूर्णांकr_delay_resolution,
							      &ena_dev->पूर्णांकr_moder_tx_पूर्णांकerval);
पूर्ण

पूर्णांक ena_com_update_nonadaptive_moderation_पूर्णांकerval_rx(काष्ठा ena_com_dev *ena_dev,
						      u32 rx_coalesce_usecs)
अणु
	वापस ena_com_update_nonadaptive_moderation_पूर्णांकerval(ena_dev,
							      rx_coalesce_usecs,
							      ena_dev->पूर्णांकr_delay_resolution,
							      &ena_dev->पूर्णांकr_moder_rx_पूर्णांकerval);
पूर्ण

पूर्णांक ena_com_init_पूर्णांकerrupt_moderation(काष्ठा ena_com_dev *ena_dev)
अणु
	काष्ठा ena_admin_get_feat_resp get_resp;
	u16 delay_resolution;
	पूर्णांक rc;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_INTERRUPT_MODERATION, 0);

	अगर (rc) अणु
		अगर (rc == -EOPNOTSUPP) अणु
			netdev_dbg(ena_dev->net_device,
				   "Feature %d isn't supported\n",
				   ENA_ADMIN_INTERRUPT_MODERATION);
			rc = 0;
		पूर्ण अन्यथा अणु
			netdev_err(ena_dev->net_device,
				   "Failed to get interrupt moderation admin cmd. rc: %d\n",
				   rc);
		पूर्ण

		/* no moderation supported, disable adaptive support */
		ena_com_disable_adaptive_moderation(ena_dev);
		वापस rc;
	पूर्ण

	/* अगर moderation is supported by device we set adaptive moderation */
	delay_resolution = get_resp.u.पूर्णांकr_moderation.पूर्णांकr_delay_resolution;
	ena_com_update_पूर्णांकr_delay_resolution(ena_dev, delay_resolution);

	/* Disable adaptive moderation by शेष - can be enabled later */
	ena_com_disable_adaptive_moderation(ena_dev);

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_dev->पूर्णांकr_moder_tx_पूर्णांकerval;
पूर्ण

अचिन्हित पूर्णांक ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_dev->पूर्णांकr_moder_rx_पूर्णांकerval;
पूर्ण

पूर्णांक ena_com_config_dev_mode(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_admin_feature_llq_desc *llq_features,
			    काष्ठा ena_llq_configurations *llq_शेष_cfg)
अणु
	काष्ठा ena_com_llq_info *llq_info = &ena_dev->llq_info;
	पूर्णांक rc;

	अगर (!llq_features->max_llq_num) अणु
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		वापस 0;
	पूर्ण

	rc = ena_com_config_llq_info(ena_dev, llq_features, llq_शेष_cfg);
	अगर (rc)
		वापस rc;

	ena_dev->tx_max_header_size = llq_info->desc_list_entry_size -
		(llq_info->descs_num_beक्रमe_header * माप(काष्ठा ena_eth_io_tx_desc));

	अगर (unlikely(ena_dev->tx_max_header_size == 0)) अणु
		netdev_err(ena_dev->net_device,
			   "The size of the LLQ entry is smaller than needed\n");
		वापस -EINVAL;
	पूर्ण

	ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_DEV;

	वापस 0;
पूर्ण
