<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause
/*
 * Copyright 2018-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश "efa_com.h"
#समावेश "efa_regs_defs.h"

#घोषणा ADMIN_CMD_TIMEOUT_US 30000000 /* usecs */

#घोषणा EFA_REG_READ_TIMEOUT_US 50000 /* usecs */
#घोषणा EFA_MMIO_READ_INVALID 0xffffffff

#घोषणा EFA_POLL_INTERVAL_MS 100 /* msecs */

#घोषणा EFA_ASYNC_QUEUE_DEPTH 16
#घोषणा EFA_ADMIN_QUEUE_DEPTH 32

#घोषणा EFA_CTRL_MAJOR          0
#घोषणा EFA_CTRL_MINOR          0
#घोषणा EFA_CTRL_SUB_MINOR      1

क्रमागत efa_cmd_status अणु
	EFA_CMD_SUBMITTED,
	EFA_CMD_COMPLETED,
पूर्ण;

काष्ठा efa_comp_ctx अणु
	काष्ठा completion रुको_event;
	काष्ठा efa_admin_acq_entry *user_cqe;
	u32 comp_size;
	क्रमागत efa_cmd_status status;
	u8 cmd_opcode;
	u8 occupied;
पूर्ण;

अटल स्थिर अक्षर *efa_com_cmd_str(u8 cmd)
अणु
#घोषणा EFA_CMD_STR_CASE(_cmd) हाल EFA_ADMIN_##_cmd: वापस #_cmd

	चयन (cmd) अणु
	EFA_CMD_STR_CASE(CREATE_QP);
	EFA_CMD_STR_CASE(MODIFY_QP);
	EFA_CMD_STR_CASE(QUERY_QP);
	EFA_CMD_STR_CASE(DESTROY_QP);
	EFA_CMD_STR_CASE(CREATE_AH);
	EFA_CMD_STR_CASE(DESTROY_AH);
	EFA_CMD_STR_CASE(REG_MR);
	EFA_CMD_STR_CASE(DEREG_MR);
	EFA_CMD_STR_CASE(CREATE_CQ);
	EFA_CMD_STR_CASE(DESTROY_CQ);
	EFA_CMD_STR_CASE(GET_FEATURE);
	EFA_CMD_STR_CASE(SET_FEATURE);
	EFA_CMD_STR_CASE(GET_STATS);
	EFA_CMD_STR_CASE(ALLOC_PD);
	EFA_CMD_STR_CASE(DEALLOC_PD);
	EFA_CMD_STR_CASE(ALLOC_UAR);
	EFA_CMD_STR_CASE(DEALLOC_UAR);
	शेष: वापस "unknown command opcode";
	पूर्ण
#अघोषित EFA_CMD_STR_CASE
पूर्ण

अटल u32 efa_com_reg_पढ़ो32(काष्ठा efa_com_dev *edev, u16 offset)
अणु
	काष्ठा efa_com_mmio_पढ़ो *mmio_पढ़ो = &edev->mmio_पढ़ो;
	काष्ठा efa_admin_mmio_req_पढ़ो_less_resp *पढ़ो_resp;
	अचिन्हित दीर्घ exp_समय;
	u32 mmio_पढ़ो_reg = 0;
	u32 err;

	पढ़ो_resp = mmio_पढ़ो->पढ़ो_resp;

	spin_lock(&mmio_पढ़ो->lock);
	mmio_पढ़ो->seq_num++;

	/* trash DMA req_id to identअगरy when hardware is करोne */
	पढ़ो_resp->req_id = mmio_पढ़ो->seq_num + 0x9aL;
	EFA_SET(&mmio_पढ़ो_reg, EFA_REGS_MMIO_REG_READ_REG_OFF, offset);
	EFA_SET(&mmio_पढ़ो_reg, EFA_REGS_MMIO_REG_READ_REQ_ID,
		mmio_पढ़ो->seq_num);

	ग_लिखोl(mmio_पढ़ो_reg, edev->reg_bar + EFA_REGS_MMIO_REG_READ_OFF);

	exp_समय = jअगरfies + usecs_to_jअगरfies(mmio_पढ़ो->mmio_पढ़ो_समयout);
	करो अणु
		अगर (READ_ONCE(पढ़ो_resp->req_id) == mmio_पढ़ो->seq_num)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (समय_is_after_jअगरfies(exp_समय));

	अगर (पढ़ो_resp->req_id != mmio_पढ़ो->seq_num) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Reading register timed out. expected: req id[%u] offset[%#x] actual: req id[%u] offset[%#x]\n",
			mmio_पढ़ो->seq_num, offset, पढ़ो_resp->req_id,
			पढ़ो_resp->reg_off);
		err = EFA_MMIO_READ_INVALID;
		जाओ out;
	पूर्ण

	अगर (पढ़ो_resp->reg_off != offset) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Reading register failed: wrong offset provided\n");
		err = EFA_MMIO_READ_INVALID;
		जाओ out;
	पूर्ण

	err = पढ़ो_resp->reg_val;
out:
	spin_unlock(&mmio_पढ़ो->lock);
	वापस err;
पूर्ण

अटल पूर्णांक efa_com_admin_init_sq(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_com_admin_sq *sq = &aq->sq;
	u16 size = aq->depth * माप(*sq->entries);
	u32 aq_caps = 0;
	u32 addr_high;
	u32 addr_low;

	sq->entries =
		dma_alloc_coherent(aq->dmadev, size, &sq->dma_addr, GFP_KERNEL);
	अगर (!sq->entries)
		वापस -ENOMEM;

	spin_lock_init(&sq->lock);

	sq->cc = 0;
	sq->pc = 0;
	sq->phase = 1;

	sq->db_addr = (u32 __iomem *)(edev->reg_bar + EFA_REGS_AQ_PROD_DB_OFF);

	addr_high = upper_32_bits(sq->dma_addr);
	addr_low = lower_32_bits(sq->dma_addr);

	ग_लिखोl(addr_low, edev->reg_bar + EFA_REGS_AQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, edev->reg_bar + EFA_REGS_AQ_BASE_HI_OFF);

	EFA_SET(&aq_caps, EFA_REGS_AQ_CAPS_AQ_DEPTH, aq->depth);
	EFA_SET(&aq_caps, EFA_REGS_AQ_CAPS_AQ_ENTRY_SIZE,
		माप(काष्ठा efa_admin_aq_entry));

	ग_लिखोl(aq_caps, edev->reg_bar + EFA_REGS_AQ_CAPS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक efa_com_admin_init_cq(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_com_admin_cq *cq = &aq->cq;
	u16 size = aq->depth * माप(*cq->entries);
	u32 acq_caps = 0;
	u32 addr_high;
	u32 addr_low;

	cq->entries =
		dma_alloc_coherent(aq->dmadev, size, &cq->dma_addr, GFP_KERNEL);
	अगर (!cq->entries)
		वापस -ENOMEM;

	spin_lock_init(&cq->lock);

	cq->cc = 0;
	cq->phase = 1;

	addr_high = upper_32_bits(cq->dma_addr);
	addr_low = lower_32_bits(cq->dma_addr);

	ग_लिखोl(addr_low, edev->reg_bar + EFA_REGS_ACQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, edev->reg_bar + EFA_REGS_ACQ_BASE_HI_OFF);

	EFA_SET(&acq_caps, EFA_REGS_ACQ_CAPS_ACQ_DEPTH, aq->depth);
	EFA_SET(&acq_caps, EFA_REGS_ACQ_CAPS_ACQ_ENTRY_SIZE,
		माप(काष्ठा efa_admin_acq_entry));
	EFA_SET(&acq_caps, EFA_REGS_ACQ_CAPS_ACQ_MSIX_VECTOR,
		aq->msix_vector_idx);

	ग_लिखोl(acq_caps, edev->reg_bar + EFA_REGS_ACQ_CAPS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक efa_com_admin_init_aenq(काष्ठा efa_com_dev *edev,
				   काष्ठा efa_aenq_handlers *aenq_handlers)
अणु
	काष्ठा efa_com_aenq *aenq = &edev->aenq;
	u32 addr_low, addr_high;
	u32 aenq_caps = 0;
	u16 size;

	अगर (!aenq_handlers) अणु
		ibdev_err(edev->efa_dev, "aenq handlers pointer is NULL\n");
		वापस -EINVAL;
	पूर्ण

	size = EFA_ASYNC_QUEUE_DEPTH * माप(*aenq->entries);
	aenq->entries = dma_alloc_coherent(edev->dmadev, size, &aenq->dma_addr,
					   GFP_KERNEL);
	अगर (!aenq->entries)
		वापस -ENOMEM;

	aenq->aenq_handlers = aenq_handlers;
	aenq->depth = EFA_ASYNC_QUEUE_DEPTH;
	aenq->cc = 0;
	aenq->phase = 1;

	addr_low = lower_32_bits(aenq->dma_addr);
	addr_high = upper_32_bits(aenq->dma_addr);

	ग_लिखोl(addr_low, edev->reg_bar + EFA_REGS_AENQ_BASE_LO_OFF);
	ग_लिखोl(addr_high, edev->reg_bar + EFA_REGS_AENQ_BASE_HI_OFF);

	EFA_SET(&aenq_caps, EFA_REGS_AENQ_CAPS_AENQ_DEPTH, aenq->depth);
	EFA_SET(&aenq_caps, EFA_REGS_AENQ_CAPS_AENQ_ENTRY_SIZE,
		माप(काष्ठा efa_admin_aenq_entry));
	EFA_SET(&aenq_caps, EFA_REGS_AENQ_CAPS_AENQ_MSIX_VECTOR,
		aenq->msix_vector_idx);
	ग_लिखोl(aenq_caps, edev->reg_bar + EFA_REGS_AENQ_CAPS_OFF);

	/*
	 * Init cons_db to mark that all entries in the queue
	 * are initially available
	 */
	ग_लिखोl(edev->aenq.cc, edev->reg_bar + EFA_REGS_AENQ_CONS_DB_OFF);

	वापस 0;
पूर्ण

/* ID to be used with efa_com_get_comp_ctx */
अटल u16 efa_com_alloc_ctx_id(काष्ठा efa_com_admin_queue *aq)
अणु
	u16 ctx_id;

	spin_lock(&aq->comp_ctx_lock);
	ctx_id = aq->comp_ctx_pool[aq->comp_ctx_pool_next];
	aq->comp_ctx_pool_next++;
	spin_unlock(&aq->comp_ctx_lock);

	वापस ctx_id;
पूर्ण

अटल व्योम efa_com_dealloc_ctx_id(काष्ठा efa_com_admin_queue *aq,
				   u16 ctx_id)
अणु
	spin_lock(&aq->comp_ctx_lock);
	aq->comp_ctx_pool_next--;
	aq->comp_ctx_pool[aq->comp_ctx_pool_next] = ctx_id;
	spin_unlock(&aq->comp_ctx_lock);
पूर्ण

अटल अंतरभूत व्योम efa_com_put_comp_ctx(काष्ठा efa_com_admin_queue *aq,
					काष्ठा efa_comp_ctx *comp_ctx)
अणु
	u16 cmd_id = EFA_GET(&comp_ctx->user_cqe->acq_common_descriptor.command,
			     EFA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID);
	u16 ctx_id = cmd_id & (aq->depth - 1);

	ibdev_dbg(aq->efa_dev, "Put completion command_id %#x\n", cmd_id);
	comp_ctx->occupied = 0;
	efa_com_dealloc_ctx_id(aq, ctx_id);
पूर्ण

अटल काष्ठा efa_comp_ctx *efa_com_get_comp_ctx(काष्ठा efa_com_admin_queue *aq,
						 u16 cmd_id, bool capture)
अणु
	u16 ctx_id = cmd_id & (aq->depth - 1);

	अगर (aq->comp_ctx[ctx_id].occupied && capture) अणु
		ibdev_err_ratelimited(
			aq->efa_dev,
			"Completion context for command_id %#x is occupied\n",
			cmd_id);
		वापस शून्य;
	पूर्ण

	अगर (capture) अणु
		aq->comp_ctx[ctx_id].occupied = 1;
		ibdev_dbg(aq->efa_dev,
			  "Take completion ctxt for command_id %#x\n", cmd_id);
	पूर्ण

	वापस &aq->comp_ctx[ctx_id];
पूर्ण

अटल काष्ठा efa_comp_ctx *__efa_com_submit_admin_cmd(काष्ठा efa_com_admin_queue *aq,
						       काष्ठा efa_admin_aq_entry *cmd,
						       माप_प्रकार cmd_size_in_bytes,
						       काष्ठा efa_admin_acq_entry *comp,
						       माप_प्रकार comp_size_in_bytes)
अणु
	काष्ठा efa_admin_aq_entry *aqe;
	काष्ठा efa_comp_ctx *comp_ctx;
	u16 queue_size_mask;
	u16 cmd_id;
	u16 ctx_id;
	u16 pi;

	queue_size_mask = aq->depth - 1;
	pi = aq->sq.pc & queue_size_mask;

	ctx_id = efa_com_alloc_ctx_id(aq);

	/* cmd_id LSBs are the ctx_id and MSBs are entropy bits from pc */
	cmd_id = ctx_id & queue_size_mask;
	cmd_id |= aq->sq.pc & ~queue_size_mask;
	cmd_id &= EFA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK;

	cmd->aq_common_descriptor.command_id = cmd_id;
	EFA_SET(&cmd->aq_common_descriptor.flags,
		EFA_ADMIN_AQ_COMMON_DESC_PHASE, aq->sq.phase);

	comp_ctx = efa_com_get_comp_ctx(aq, cmd_id, true);
	अगर (!comp_ctx) अणु
		efa_com_dealloc_ctx_id(aq, ctx_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	comp_ctx->status = EFA_CMD_SUBMITTED;
	comp_ctx->comp_size = comp_size_in_bytes;
	comp_ctx->user_cqe = comp;
	comp_ctx->cmd_opcode = cmd->aq_common_descriptor.opcode;

	reinit_completion(&comp_ctx->रुको_event);

	aqe = &aq->sq.entries[pi];
	स_रखो(aqe, 0, माप(*aqe));
	स_नकल(aqe, cmd, cmd_size_in_bytes);

	aq->sq.pc++;
	atomic64_inc(&aq->stats.submitted_cmd);

	अगर ((aq->sq.pc & queue_size_mask) == 0)
		aq->sq.phase = !aq->sq.phase;

	/* barrier not needed in हाल of ग_लिखोl */
	ग_लिखोl(aq->sq.pc, aq->sq.db_addr);

	वापस comp_ctx;
पूर्ण

अटल अंतरभूत पूर्णांक efa_com_init_comp_ctxt(काष्ठा efa_com_admin_queue *aq)
अणु
	माप_प्रकार pool_size = aq->depth * माप(*aq->comp_ctx_pool);
	माप_प्रकार size = aq->depth * माप(काष्ठा efa_comp_ctx);
	काष्ठा efa_comp_ctx *comp_ctx;
	u16 i;

	aq->comp_ctx = devm_kzalloc(aq->dmadev, size, GFP_KERNEL);
	aq->comp_ctx_pool = devm_kzalloc(aq->dmadev, pool_size, GFP_KERNEL);
	अगर (!aq->comp_ctx || !aq->comp_ctx_pool) अणु
		devm_kमुक्त(aq->dmadev, aq->comp_ctx_pool);
		devm_kमुक्त(aq->dmadev, aq->comp_ctx);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < aq->depth; i++) अणु
		comp_ctx = efa_com_get_comp_ctx(aq, i, false);
		अगर (comp_ctx)
			init_completion(&comp_ctx->रुको_event);

		aq->comp_ctx_pool[i] = i;
	पूर्ण

	spin_lock_init(&aq->comp_ctx_lock);

	aq->comp_ctx_pool_next = 0;

	वापस 0;
पूर्ण

अटल काष्ठा efa_comp_ctx *efa_com_submit_admin_cmd(काष्ठा efa_com_admin_queue *aq,
						     काष्ठा efa_admin_aq_entry *cmd,
						     माप_प्रकार cmd_size_in_bytes,
						     काष्ठा efa_admin_acq_entry *comp,
						     माप_प्रकार comp_size_in_bytes)
अणु
	काष्ठा efa_comp_ctx *comp_ctx;

	spin_lock(&aq->sq.lock);
	अगर (!test_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state)) अणु
		ibdev_err_ratelimited(aq->efa_dev, "Admin queue is closed\n");
		spin_unlock(&aq->sq.lock);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	comp_ctx = __efa_com_submit_admin_cmd(aq, cmd, cmd_size_in_bytes, comp,
					      comp_size_in_bytes);
	spin_unlock(&aq->sq.lock);
	अगर (IS_ERR(comp_ctx))
		clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);

	वापस comp_ctx;
पूर्ण

अटल व्योम efa_com_handle_single_admin_completion(काष्ठा efa_com_admin_queue *aq,
						   काष्ठा efa_admin_acq_entry *cqe)
अणु
	काष्ठा efa_comp_ctx *comp_ctx;
	u16 cmd_id;

	cmd_id = EFA_GET(&cqe->acq_common_descriptor.command,
			 EFA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID);

	comp_ctx = efa_com_get_comp_ctx(aq, cmd_id, false);
	अगर (!comp_ctx) अणु
		ibdev_err(aq->efa_dev,
			  "comp_ctx is NULL. Changing the admin queue running state\n");
		clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);
		वापस;
	पूर्ण

	comp_ctx->status = EFA_CMD_COMPLETED;
	स_नकल(comp_ctx->user_cqe, cqe, comp_ctx->comp_size);

	अगर (!test_bit(EFA_AQ_STATE_POLLING_BIT, &aq->state))
		complete(&comp_ctx->रुको_event);
पूर्ण

अटल व्योम efa_com_handle_admin_completion(काष्ठा efa_com_admin_queue *aq)
अणु
	काष्ठा efa_admin_acq_entry *cqe;
	u16 queue_size_mask;
	u16 comp_num = 0;
	u8 phase;
	u16 ci;

	queue_size_mask = aq->depth - 1;

	ci = aq->cq.cc & queue_size_mask;
	phase = aq->cq.phase;

	cqe = &aq->cq.entries[ci];

	/* Go over all the completions */
	जबतक ((READ_ONCE(cqe->acq_common_descriptor.flags) &
		EFA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK) == phase) अणु
		/*
		 * Do not पढ़ो the rest of the completion entry beक्रमe the
		 * phase bit was validated
		 */
		dma_rmb();
		efa_com_handle_single_admin_completion(aq, cqe);

		ci++;
		comp_num++;
		अगर (ci == aq->depth) अणु
			ci = 0;
			phase = !phase;
		पूर्ण

		cqe = &aq->cq.entries[ci];
	पूर्ण

	aq->cq.cc += comp_num;
	aq->cq.phase = phase;
	aq->sq.cc += comp_num;
	atomic64_add(comp_num, &aq->stats.completed_cmd);
पूर्ण

अटल पूर्णांक efa_com_comp_status_to_त्रुटि_सं(u8 comp_status)
अणु
	चयन (comp_status) अणु
	हाल EFA_ADMIN_SUCCESS:
		वापस 0;
	हाल EFA_ADMIN_RESOURCE_ALLOCATION_FAILURE:
		वापस -ENOMEM;
	हाल EFA_ADMIN_UNSUPPORTED_OPCODE:
		वापस -EOPNOTSUPP;
	हाल EFA_ADMIN_BAD_OPCODE:
	हाल EFA_ADMIN_MALFORMED_REQUEST:
	हाल EFA_ADMIN_ILLEGAL_PARAMETER:
	हाल EFA_ADMIN_UNKNOWN_ERROR:
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक efa_com_रुको_and_process_admin_cq_polling(काष्ठा efa_comp_ctx *comp_ctx,
						     काष्ठा efa_com_admin_queue *aq)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	समयout = jअगरfies + usecs_to_jअगरfies(aq->completion_समयout);

	जबतक (1) अणु
		spin_lock_irqsave(&aq->cq.lock, flags);
		efa_com_handle_admin_completion(aq);
		spin_unlock_irqrestore(&aq->cq.lock, flags);

		अगर (comp_ctx->status != EFA_CMD_SUBMITTED)
			अवरोध;

		अगर (समय_is_beक्रमe_jअगरfies(समयout)) अणु
			ibdev_err_ratelimited(
				aq->efa_dev,
				"Wait for completion (polling) timeout\n");
			/* EFA didn't have any completion */
			atomic64_inc(&aq->stats.no_completion);

			clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);
			err = -ETIME;
			जाओ out;
		पूर्ण

		msleep(aq->poll_पूर्णांकerval);
	पूर्ण

	err = efa_com_comp_status_to_त्रुटि_सं(comp_ctx->user_cqe->acq_common_descriptor.status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक efa_com_रुको_and_process_admin_cq_पूर्णांकerrupts(काष्ठा efa_comp_ctx *comp_ctx,
							काष्ठा efa_com_admin_queue *aq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	रुको_क्रम_completion_समयout(&comp_ctx->रुको_event,
				    usecs_to_jअगरfies(aq->completion_समयout));

	/*
	 * In हाल the command wasn't completed find out the root cause.
	 * There might be 2 kinds of errors
	 * 1) No completion (समयout reached)
	 * 2) There is completion but the device didn't get any msi-x पूर्णांकerrupt.
	 */
	अगर (comp_ctx->status == EFA_CMD_SUBMITTED) अणु
		spin_lock_irqsave(&aq->cq.lock, flags);
		efa_com_handle_admin_completion(aq);
		spin_unlock_irqrestore(&aq->cq.lock, flags);

		atomic64_inc(&aq->stats.no_completion);

		अगर (comp_ctx->status == EFA_CMD_COMPLETED)
			ibdev_err_ratelimited(
				aq->efa_dev,
				"The device sent a completion but the driver didn't receive any MSI-X interrupt for admin cmd %s(%d) status %d (ctx: 0x%p, sq producer: %d, sq consumer: %d, cq consumer: %d)\n",
				efa_com_cmd_str(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);
		अन्यथा
			ibdev_err_ratelimited(
				aq->efa_dev,
				"The device didn't send any completion for admin cmd %s(%d) status %d (ctx 0x%p, sq producer: %d, sq consumer: %d, cq consumer: %d)\n",
				efa_com_cmd_str(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);

		clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);
		err = -ETIME;
		जाओ out;
	पूर्ण

	err = efa_com_comp_status_to_त्रुटि_सं(comp_ctx->user_cqe->acq_common_descriptor.status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	वापस err;
पूर्ण

/*
 * There are two types to रुको क्रम completion.
 * Polling mode - रुको until the completion is available.
 * Async mode - रुको on रुको queue until the completion is पढ़ोy
 * (or the समयout expired).
 * It is expected that the IRQ called efa_com_handle_admin_completion
 * to mark the completions.
 */
अटल पूर्णांक efa_com_रुको_and_process_admin_cq(काष्ठा efa_comp_ctx *comp_ctx,
					     काष्ठा efa_com_admin_queue *aq)
अणु
	अगर (test_bit(EFA_AQ_STATE_POLLING_BIT, &aq->state))
		वापस efa_com_रुको_and_process_admin_cq_polling(comp_ctx, aq);

	वापस efa_com_रुको_and_process_admin_cq_पूर्णांकerrupts(comp_ctx, aq);
पूर्ण

/**
 * efa_com_cmd_exec - Execute admin command
 * @aq: admin queue.
 * @cmd: the admin command to execute.
 * @cmd_size: the command size.
 * @comp: command completion वापस entry.
 * @comp_size: command completion size.
 * Submit an admin command and then रुको until the device will वापस a
 * completion.
 * The completion will be copied पूर्णांकo comp.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक efa_com_cmd_exec(काष्ठा efa_com_admin_queue *aq,
		     काष्ठा efa_admin_aq_entry *cmd,
		     माप_प्रकार cmd_size,
		     काष्ठा efa_admin_acq_entry *comp,
		     माप_प्रकार comp_size)
अणु
	काष्ठा efa_comp_ctx *comp_ctx;
	पूर्णांक err;

	might_sleep();

	/* In हाल of queue FULL */
	करोwn(&aq->avail_cmds);

	ibdev_dbg(aq->efa_dev, "%s (opcode %d)\n",
		  efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
		  cmd->aq_common_descriptor.opcode);
	comp_ctx = efa_com_submit_admin_cmd(aq, cmd, cmd_size, comp, comp_size);
	अगर (IS_ERR(comp_ctx)) अणु
		ibdev_err_ratelimited(
			aq->efa_dev,
			"Failed to submit command %s (opcode %u) err %ld\n",
			efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
			cmd->aq_common_descriptor.opcode, PTR_ERR(comp_ctx));

		up(&aq->avail_cmds);
		atomic64_inc(&aq->stats.cmd_err);
		वापस PTR_ERR(comp_ctx);
	पूर्ण

	err = efa_com_रुको_and_process_admin_cq(comp_ctx, aq);
	अगर (err) अणु
		ibdev_err_ratelimited(
			aq->efa_dev,
			"Failed to process command %s (opcode %u) comp_status %d err %d\n",
			efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
			cmd->aq_common_descriptor.opcode,
			comp_ctx->user_cqe->acq_common_descriptor.status, err);
		atomic64_inc(&aq->stats.cmd_err);
	पूर्ण

	up(&aq->avail_cmds);

	वापस err;
पूर्ण

/**
 * efa_com_admin_destroy - Destroy the admin and the async events queues.
 * @edev: EFA communication layer काष्ठा
 */
व्योम efa_com_admin_destroy(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_com_aenq *aenq = &edev->aenq;
	काष्ठा efa_com_admin_cq *cq = &aq->cq;
	काष्ठा efa_com_admin_sq *sq = &aq->sq;
	u16 size;

	clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);

	devm_kमुक्त(edev->dmadev, aq->comp_ctx_pool);
	devm_kमुक्त(edev->dmadev, aq->comp_ctx);

	size = aq->depth * माप(*sq->entries);
	dma_मुक्त_coherent(edev->dmadev, size, sq->entries, sq->dma_addr);

	size = aq->depth * माप(*cq->entries);
	dma_मुक्त_coherent(edev->dmadev, size, cq->entries, cq->dma_addr);

	size = aenq->depth * माप(*aenq->entries);
	dma_मुक्त_coherent(edev->dmadev, size, aenq->entries, aenq->dma_addr);
पूर्ण

/**
 * efa_com_set_admin_polling_mode - Set the admin completion queue polling mode
 * @edev: EFA communication layer काष्ठा
 * @polling: Enable/Disable polling mode
 *
 * Set the admin completion mode.
 */
व्योम efa_com_set_admin_polling_mode(काष्ठा efa_com_dev *edev, bool polling)
अणु
	u32 mask_value = 0;

	अगर (polling)
		EFA_SET(&mask_value, EFA_REGS_INTR_MASK_EN, 1);

	ग_लिखोl(mask_value, edev->reg_bar + EFA_REGS_INTR_MASK_OFF);
	अगर (polling)
		set_bit(EFA_AQ_STATE_POLLING_BIT, &edev->aq.state);
	अन्यथा
		clear_bit(EFA_AQ_STATE_POLLING_BIT, &edev->aq.state);
पूर्ण

अटल व्योम efa_com_stats_init(काष्ठा efa_com_dev *edev)
अणु
	atomic64_t *s = (atomic64_t *)&edev->aq.stats;
	पूर्णांक i;

	क्रम (i = 0; i < माप(edev->aq.stats) / माप(*s); i++, s++)
		atomic64_set(s, 0);
पूर्ण

/**
 * efa_com_admin_init - Init the admin and the async queues
 * @edev: EFA communication layer काष्ठा
 * @aenq_handlers: Those handlers to be called upon event.
 *
 * Initialize the admin submission and completion queues.
 * Initialize the asynchronous events notअगरication queues.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक efa_com_admin_init(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_aenq_handlers *aenq_handlers)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	u32 समयout;
	u32 dev_sts;
	u32 cap;
	पूर्णांक err;

	dev_sts = efa_com_reg_पढ़ो32(edev, EFA_REGS_DEV_STS_OFF);
	अगर (!EFA_GET(&dev_sts, EFA_REGS_DEV_STS_READY)) अणु
		ibdev_err(edev->efa_dev,
			  "Device isn't ready, abort com init %#x\n", dev_sts);
		वापस -ENODEV;
	पूर्ण

	aq->depth = EFA_ADMIN_QUEUE_DEPTH;

	aq->dmadev = edev->dmadev;
	aq->efa_dev = edev->efa_dev;
	set_bit(EFA_AQ_STATE_POLLING_BIT, &aq->state);

	sema_init(&aq->avail_cmds, aq->depth);

	efa_com_stats_init(edev);

	err = efa_com_init_comp_ctxt(aq);
	अगर (err)
		वापस err;

	err = efa_com_admin_init_sq(edev);
	अगर (err)
		जाओ err_destroy_comp_ctxt;

	err = efa_com_admin_init_cq(edev);
	अगर (err)
		जाओ err_destroy_sq;

	efa_com_set_admin_polling_mode(edev, false);

	err = efa_com_admin_init_aenq(edev, aenq_handlers);
	अगर (err)
		जाओ err_destroy_cq;

	cap = efa_com_reg_पढ़ो32(edev, EFA_REGS_CAPS_OFF);
	समयout = EFA_GET(&cap, EFA_REGS_CAPS_ADMIN_CMD_TO);
	अगर (समयout)
		/* the resolution of समयout reg is 100ms */
		aq->completion_समयout = समयout * 100000;
	अन्यथा
		aq->completion_समयout = ADMIN_CMD_TIMEOUT_US;

	aq->poll_पूर्णांकerval = EFA_POLL_INTERVAL_MS;

	set_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);

	वापस 0;

err_destroy_cq:
	dma_मुक्त_coherent(edev->dmadev, aq->depth * माप(*aq->cq.entries),
			  aq->cq.entries, aq->cq.dma_addr);
err_destroy_sq:
	dma_मुक्त_coherent(edev->dmadev, aq->depth * माप(*aq->sq.entries),
			  aq->sq.entries, aq->sq.dma_addr);
err_destroy_comp_ctxt:
	devm_kमुक्त(edev->dmadev, aq->comp_ctx);

	वापस err;
पूर्ण

/**
 * efa_com_admin_q_comp_पूर्णांकr_handler - admin queue पूर्णांकerrupt handler
 * @edev: EFA communication layer काष्ठा
 *
 * This method goes over the admin completion queue and wakes up
 * all the pending thपढ़ोs that रुको on the commands रुको event.
 *
 * Note: Should be called after MSI-X पूर्णांकerrupt.
 */
व्योम efa_com_admin_q_comp_पूर्णांकr_handler(काष्ठा efa_com_dev *edev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edev->aq.cq.lock, flags);
	efa_com_handle_admin_completion(&edev->aq);
	spin_unlock_irqrestore(&edev->aq.cq.lock, flags);
पूर्ण

/*
 * efa_handle_specअगरic_aenq_event:
 * वापस the handler that is relevant to the specअगरic event group
 */
अटल efa_aenq_handler efa_com_get_specअगरic_aenq_cb(काष्ठा efa_com_dev *edev,
						     u16 group)
अणु
	काष्ठा efa_aenq_handlers *aenq_handlers = edev->aenq.aenq_handlers;

	अगर (group < EFA_MAX_HANDLERS && aenq_handlers->handlers[group])
		वापस aenq_handlers->handlers[group];

	वापस aenq_handlers->unimplemented_handler;
पूर्ण

/**
 * efa_com_aenq_पूर्णांकr_handler - AENQ पूर्णांकerrupt handler
 * @edev: EFA communication layer काष्ठा
 * @data: Data of पूर्णांकerrupt handler.
 *
 * Go over the async event notअगरication queue and call the proper aenq handler.
 */
व्योम efa_com_aenq_पूर्णांकr_handler(काष्ठा efa_com_dev *edev, व्योम *data)
अणु
	काष्ठा efa_admin_aenq_common_desc *aenq_common;
	काष्ठा efa_com_aenq *aenq = &edev->aenq;
	काष्ठा efa_admin_aenq_entry *aenq_e;
	efa_aenq_handler handler_cb;
	u32 processed = 0;
	u8 phase;
	u32 ci;

	ci = aenq->cc & (aenq->depth - 1);
	phase = aenq->phase;
	aenq_e = &aenq->entries[ci]; /* Get first entry */
	aenq_common = &aenq_e->aenq_common_desc;

	/* Go over all the events */
	जबतक ((READ_ONCE(aenq_common->flags) &
		EFA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK) == phase) अणु
		/*
		 * Do not पढ़ो the rest of the completion entry beक्रमe the
		 * phase bit was validated
		 */
		dma_rmb();

		/* Handle specअगरic event*/
		handler_cb = efa_com_get_specअगरic_aenq_cb(edev,
							  aenq_common->group);
		handler_cb(data, aenq_e); /* call the actual event handler*/

		/* Get next event entry */
		ci++;
		processed++;

		अगर (ci == aenq->depth) अणु
			ci = 0;
			phase = !phase;
		पूर्ण
		aenq_e = &aenq->entries[ci];
		aenq_common = &aenq_e->aenq_common_desc;
	पूर्ण

	aenq->cc += processed;
	aenq->phase = phase;

	/* Don't update aenq doorbell if there weren't any processed events */
	अगर (!processed)
		वापस;

	/* barrier not needed in हाल of ग_लिखोl */
	ग_लिखोl(aenq->cc, edev->reg_bar + EFA_REGS_AENQ_CONS_DB_OFF);
पूर्ण

अटल व्योम efa_com_mmio_reg_पढ़ो_resp_addr_init(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_mmio_पढ़ो *mmio_पढ़ो = &edev->mmio_पढ़ो;
	u32 addr_high;
	u32 addr_low;

	/* dma_addr_bits is unknown at this poपूर्णांक */
	addr_high = (mmio_पढ़ो->पढ़ो_resp_dma_addr >> 32) & GENMASK(31, 0);
	addr_low = mmio_पढ़ो->पढ़ो_resp_dma_addr & GENMASK(31, 0);

	ग_लिखोl(addr_high, edev->reg_bar + EFA_REGS_MMIO_RESP_HI_OFF);
	ग_लिखोl(addr_low, edev->reg_bar + EFA_REGS_MMIO_RESP_LO_OFF);
पूर्ण

पूर्णांक efa_com_mmio_reg_पढ़ो_init(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_mmio_पढ़ो *mmio_पढ़ो = &edev->mmio_पढ़ो;

	spin_lock_init(&mmio_पढ़ो->lock);
	mmio_पढ़ो->पढ़ो_resp =
		dma_alloc_coherent(edev->dmadev, माप(*mmio_पढ़ो->पढ़ो_resp),
				   &mmio_पढ़ो->पढ़ो_resp_dma_addr, GFP_KERNEL);
	अगर (!mmio_पढ़ो->पढ़ो_resp)
		वापस -ENOMEM;

	efa_com_mmio_reg_पढ़ो_resp_addr_init(edev);

	mmio_पढ़ो->पढ़ो_resp->req_id = 0;
	mmio_पढ़ो->seq_num = 0;
	mmio_पढ़ो->mmio_पढ़ो_समयout = EFA_REG_READ_TIMEOUT_US;

	वापस 0;
पूर्ण

व्योम efa_com_mmio_reg_पढ़ो_destroy(काष्ठा efa_com_dev *edev)
अणु
	काष्ठा efa_com_mmio_पढ़ो *mmio_पढ़ो = &edev->mmio_पढ़ो;

	dma_मुक्त_coherent(edev->dmadev, माप(*mmio_पढ़ो->पढ़ो_resp),
			  mmio_पढ़ो->पढ़ो_resp, mmio_पढ़ो->पढ़ो_resp_dma_addr);
पूर्ण

पूर्णांक efa_com_validate_version(काष्ठा efa_com_dev *edev)
अणु
	u32 min_ctrl_ver = 0;
	u32 ctrl_ver_masked;
	u32 min_ver = 0;
	u32 ctrl_ver;
	u32 ver;

	/*
	 * Make sure the EFA version and the controller version are at least
	 * as the driver expects
	 */
	ver = efa_com_reg_पढ़ो32(edev, EFA_REGS_VERSION_OFF);
	ctrl_ver = efa_com_reg_पढ़ो32(edev,
				      EFA_REGS_CONTROLLER_VERSION_OFF);

	ibdev_dbg(edev->efa_dev, "efa device version: %d.%d\n",
		  EFA_GET(&ver, EFA_REGS_VERSION_MAJOR_VERSION),
		  EFA_GET(&ver, EFA_REGS_VERSION_MINOR_VERSION));

	EFA_SET(&min_ver, EFA_REGS_VERSION_MAJOR_VERSION,
		EFA_ADMIN_API_VERSION_MAJOR);
	EFA_SET(&min_ver, EFA_REGS_VERSION_MINOR_VERSION,
		EFA_ADMIN_API_VERSION_MINOR);
	अगर (ver < min_ver) अणु
		ibdev_err(edev->efa_dev,
			  "EFA version is lower than the minimal version the driver supports\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ibdev_dbg(
		edev->efa_dev,
		"efa controller version: %d.%d.%d implementation version %d\n",
		EFA_GET(&ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION),
		EFA_GET(&ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION),
		EFA_GET(&ctrl_ver,
			EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION),
		EFA_GET(&ctrl_ver, EFA_REGS_CONTROLLER_VERSION_IMPL_ID));

	ctrl_ver_masked =
		EFA_GET(&ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION) |
		EFA_GET(&ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION) |
		EFA_GET(&ctrl_ver,
			EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION);

	EFA_SET(&min_ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION,
		EFA_CTRL_MAJOR);
	EFA_SET(&min_ctrl_ver, EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION,
		EFA_CTRL_MINOR);
	EFA_SET(&min_ctrl_ver, EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION,
		EFA_CTRL_SUB_MINOR);
	/* Validate the ctrl version without the implementation ID */
	अगर (ctrl_ver_masked < min_ctrl_ver) अणु
		ibdev_err(edev->efa_dev,
			  "EFA ctrl version is lower than the minimal ctrl version the driver supports\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * efa_com_get_dma_width - Retrieve physical dma address width the device
 * supports.
 * @edev: EFA communication layer काष्ठा
 *
 * Retrieve the maximum physical address bits the device can handle.
 *
 * @वापस: > 0 on Success and negative value otherwise.
 */
पूर्णांक efa_com_get_dma_width(काष्ठा efa_com_dev *edev)
अणु
	u32 caps = efa_com_reg_पढ़ो32(edev, EFA_REGS_CAPS_OFF);
	पूर्णांक width;

	width = EFA_GET(&caps, EFA_REGS_CAPS_DMA_ADDR_WIDTH);

	ibdev_dbg(edev->efa_dev, "DMA width: %d\n", width);

	अगर (width < 32 || width > 64) अणु
		ibdev_err(edev->efa_dev, "DMA width illegal value: %d\n", width);
		वापस -EINVAL;
	पूर्ण

	edev->dma_addr_bits = width;

	वापस width;
पूर्ण

अटल पूर्णांक रुको_क्रम_reset_state(काष्ठा efa_com_dev *edev, u32 समयout, पूर्णांक on)
अणु
	u32 val, i;

	क्रम (i = 0; i < समयout; i++) अणु
		val = efa_com_reg_पढ़ो32(edev, EFA_REGS_DEV_STS_OFF);

		अगर (EFA_GET(&val, EFA_REGS_DEV_STS_RESET_IN_PROGRESS) == on)
			वापस 0;

		ibdev_dbg(edev->efa_dev, "Reset indication val %d\n", val);
		msleep(EFA_POLL_INTERVAL_MS);
	पूर्ण

	वापस -ETIME;
पूर्ण

/**
 * efa_com_dev_reset - Perक्रमm device FLR to the device.
 * @edev: EFA communication layer काष्ठा
 * @reset_reason: Specअगरy what is the trigger क्रम the reset in हाल of an error.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक efa_com_dev_reset(काष्ठा efa_com_dev *edev,
		      क्रमागत efa_regs_reset_reason_types reset_reason)
अणु
	u32 stat, समयout, cap;
	u32 reset_val = 0;
	पूर्णांक err;

	stat = efa_com_reg_पढ़ो32(edev, EFA_REGS_DEV_STS_OFF);
	cap = efa_com_reg_पढ़ो32(edev, EFA_REGS_CAPS_OFF);

	अगर (!EFA_GET(&stat, EFA_REGS_DEV_STS_READY)) अणु
		ibdev_err(edev->efa_dev,
			  "Device isn't ready, can't reset device\n");
		वापस -EINVAL;
	पूर्ण

	समयout = EFA_GET(&cap, EFA_REGS_CAPS_RESET_TIMEOUT);
	अगर (!समयout) अणु
		ibdev_err(edev->efa_dev, "Invalid timeout value\n");
		वापस -EINVAL;
	पूर्ण

	/* start reset */
	EFA_SET(&reset_val, EFA_REGS_DEV_CTL_DEV_RESET, 1);
	EFA_SET(&reset_val, EFA_REGS_DEV_CTL_RESET_REASON, reset_reason);
	ग_लिखोl(reset_val, edev->reg_bar + EFA_REGS_DEV_CTL_OFF);

	/* reset clears the mmio पढ़ोless address, restore it */
	efa_com_mmio_reg_पढ़ो_resp_addr_init(edev);

	err = रुको_क्रम_reset_state(edev, समयout, 1);
	अगर (err) अणु
		ibdev_err(edev->efa_dev, "Reset indication didn't turn on\n");
		वापस err;
	पूर्ण

	/* reset करोne */
	ग_लिखोl(0, edev->reg_bar + EFA_REGS_DEV_CTL_OFF);
	err = रुको_क्रम_reset_state(edev, समयout, 0);
	अगर (err) अणु
		ibdev_err(edev->efa_dev, "Reset indication didn't turn off\n");
		वापस err;
	पूर्ण

	समयout = EFA_GET(&cap, EFA_REGS_CAPS_ADMIN_CMD_TO);
	अगर (समयout)
		/* the resolution of समयout reg is 100ms */
		edev->aq.completion_समयout = समयout * 100000;
	अन्यथा
		edev->aq.completion_समयout = ADMIN_CMD_TIMEOUT_US;

	वापस 0;
पूर्ण
