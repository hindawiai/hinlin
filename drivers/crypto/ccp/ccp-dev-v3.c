<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"

अटल u32 ccp_alloc_ksb(काष्ठा ccp_cmd_queue *cmd_q, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक start;
	काष्ठा ccp_device *ccp = cmd_q->ccp;

	क्रम (;;) अणु
		mutex_lock(&ccp->sb_mutex);

		start = (u32)biपंचांगap_find_next_zero_area(ccp->sb,
							ccp->sb_count,
							ccp->sb_start,
							count, 0);
		अगर (start <= ccp->sb_count) अणु
			biपंचांगap_set(ccp->sb, start, count);

			mutex_unlock(&ccp->sb_mutex);
			अवरोध;
		पूर्ण

		ccp->sb_avail = 0;

		mutex_unlock(&ccp->sb_mutex);

		/* Wait क्रम KSB entries to become available */
		अगर (रुको_event_पूर्णांकerruptible(ccp->sb_queue, ccp->sb_avail))
			वापस 0;
	पूर्ण

	वापस KSB_START + start;
पूर्ण

अटल व्योम ccp_मुक्त_ksb(काष्ठा ccp_cmd_queue *cmd_q, अचिन्हित पूर्णांक start,
			 अचिन्हित पूर्णांक count)
अणु
	काष्ठा ccp_device *ccp = cmd_q->ccp;

	अगर (!start)
		वापस;

	mutex_lock(&ccp->sb_mutex);

	biपंचांगap_clear(ccp->sb, start - KSB_START, count);

	ccp->sb_avail = 1;

	mutex_unlock(&ccp->sb_mutex);

	wake_up_पूर्णांकerruptible_all(&ccp->sb_queue);
पूर्ण

अटल अचिन्हित पूर्णांक ccp_get_मुक्त_slots(काष्ठा ccp_cmd_queue *cmd_q)
अणु
	वापस CMD_Q_DEPTH(ioपढ़ो32(cmd_q->reg_status));
पूर्ण

अटल पूर्णांक ccp_करो_cmd(काष्ठा ccp_op *op, u32 *cr, अचिन्हित पूर्णांक cr_count)
अणु
	काष्ठा ccp_cmd_queue *cmd_q = op->cmd_q;
	काष्ठा ccp_device *ccp = cmd_q->ccp;
	व्योम __iomem *cr_addr;
	u32 cr0, cmd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	/* We could पढ़ो a status रेजिस्टर to see how many मुक्त slots
	 * are actually available, but पढ़ोing that रेजिस्टर resets it
	 * and you could lose some error inक्रमmation.
	 */
	cmd_q->मुक्त_slots--;

	cr0 = (cmd_q->id << REQ0_CMD_Q_SHIFT)
	      | (op->jobid << REQ0_JOBID_SHIFT)
	      | REQ0_WAIT_FOR_WRITE;

	अगर (op->soc)
		cr0 |= REQ0_STOP_ON_COMPLETE
		       | REQ0_INT_ON_COMPLETE;

	अगर (op->ioc || !cmd_q->मुक्त_slots)
		cr0 |= REQ0_INT_ON_COMPLETE;

	/* Start at CMD_REQ1 */
	cr_addr = ccp->io_regs + CMD_REQ0 + CMD_REQ_INCR;

	mutex_lock(&ccp->req_mutex);

	/* Write CMD_REQ1 through CMD_REQx first */
	क्रम (i = 0; i < cr_count; i++, cr_addr += CMD_REQ_INCR)
		ioग_लिखो32(*(cr + i), cr_addr);

	/* Tell the CCP to start */
	wmb();
	ioग_लिखो32(cr0, ccp->io_regs + CMD_REQ0);

	mutex_unlock(&ccp->req_mutex);

	अगर (cr0 & REQ0_INT_ON_COMPLETE) अणु
		/* Wait क्रम the job to complete */
		ret = रुको_event_पूर्णांकerruptible(cmd_q->पूर्णांक_queue,
					       cmd_q->पूर्णांक_rcvd);
		अगर (ret || cmd_q->cmd_error) अणु
			/* On error delete all related jobs from the queue */
			cmd = (cmd_q->id << DEL_Q_ID_SHIFT)
			      | op->jobid;
			अगर (cmd_q->cmd_error)
				ccp_log_error(cmd_q->ccp,
					      cmd_q->cmd_error);

			ioग_लिखो32(cmd, ccp->io_regs + DEL_CMD_Q_JOB);

			अगर (!ret)
				ret = -EIO;
		पूर्ण अन्यथा अगर (op->soc) अणु
			/* Delete just head job from the queue on SoC */
			cmd = DEL_Q_ACTIVE
			      | (cmd_q->id << DEL_Q_ID_SHIFT)
			      | op->jobid;

			ioग_लिखो32(cmd, ccp->io_regs + DEL_CMD_Q_JOB);
		पूर्ण

		cmd_q->मुक्त_slots = CMD_Q_DEPTH(cmd_q->q_status);

		cmd_q->पूर्णांक_rcvd = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_perक्रमm_aes(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_AES << REQ1_ENGINE_SHIFT)
		| (op->u.aes.type << REQ1_AES_TYPE_SHIFT)
		| (op->u.aes.mode << REQ1_AES_MODE_SHIFT)
		| (op->u.aes.action << REQ1_AES_ACTION_SHIFT)
		| (op->sb_key << REQ1_KEY_KSB_SHIFT);
	cr[1] = op->src.u.dma.length - 1;
	cr[2] = ccp_addr_lo(&op->src.u.dma);
	cr[3] = (op->sb_ctx << REQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->src.u.dma);
	cr[4] = ccp_addr_lo(&op->dst.u.dma);
	cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->dst.u.dma);

	अगर (op->u.aes.mode == CCP_AES_MODE_CFB)
		cr[0] |= ((0x7f) << REQ1_AES_CFB_SIZE_SHIFT);

	अगर (op->eom)
		cr[0] |= REQ1_EOM;

	अगर (op->init)
		cr[0] |= REQ1_INIT;

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल पूर्णांक ccp_perक्रमm_xts_aes(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_XTS_AES_128 << REQ1_ENGINE_SHIFT)
		| (op->u.xts.action << REQ1_AES_ACTION_SHIFT)
		| (op->u.xts.unit_size << REQ1_XTS_AES_SIZE_SHIFT)
		| (op->sb_key << REQ1_KEY_KSB_SHIFT);
	cr[1] = op->src.u.dma.length - 1;
	cr[2] = ccp_addr_lo(&op->src.u.dma);
	cr[3] = (op->sb_ctx << REQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->src.u.dma);
	cr[4] = ccp_addr_lo(&op->dst.u.dma);
	cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->dst.u.dma);

	अगर (op->eom)
		cr[0] |= REQ1_EOM;

	अगर (op->init)
		cr[0] |= REQ1_INIT;

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल पूर्णांक ccp_perक्रमm_sha(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_SHA << REQ1_ENGINE_SHIFT)
		| (op->u.sha.type << REQ1_SHA_TYPE_SHIFT)
		| REQ1_INIT;
	cr[1] = op->src.u.dma.length - 1;
	cr[2] = ccp_addr_lo(&op->src.u.dma);
	cr[3] = (op->sb_ctx << REQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->src.u.dma);

	अगर (op->eom) अणु
		cr[0] |= REQ1_EOM;
		cr[4] = lower_32_bits(op->u.sha.msg_bits);
		cr[5] = upper_32_bits(op->u.sha.msg_bits);
	पूर्ण अन्यथा अणु
		cr[4] = 0;
		cr[5] = 0;
	पूर्ण

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल पूर्णांक ccp_perक्रमm_rsa(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_RSA << REQ1_ENGINE_SHIFT)
		| (op->u.rsa.mod_size << REQ1_RSA_MOD_SIZE_SHIFT)
		| (op->sb_key << REQ1_KEY_KSB_SHIFT)
		| REQ1_EOM;
	cr[1] = op->u.rsa.input_len - 1;
	cr[2] = ccp_addr_lo(&op->src.u.dma);
	cr[3] = (op->sb_ctx << REQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->src.u.dma);
	cr[4] = ccp_addr_lo(&op->dst.u.dma);
	cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->dst.u.dma);

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल पूर्णांक ccp_perक्रमm_passthru(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_PASSTHRU << REQ1_ENGINE_SHIFT)
		| (op->u.passthru.bit_mod << REQ1_PT_BW_SHIFT)
		| (op->u.passthru.byte_swap << REQ1_PT_BS_SHIFT);

	अगर (op->src.type == CCP_MEMTYPE_SYSTEM)
		cr[1] = op->src.u.dma.length - 1;
	अन्यथा
		cr[1] = op->dst.u.dma.length - 1;

	अगर (op->src.type == CCP_MEMTYPE_SYSTEM) अणु
		cr[2] = ccp_addr_lo(&op->src.u.dma);
		cr[3] = (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
			| ccp_addr_hi(&op->src.u.dma);

		अगर (op->u.passthru.bit_mod != CCP_PASSTHRU_BITWISE_NOOP)
			cr[3] |= (op->sb_key << REQ4_KSB_SHIFT);
	पूर्ण अन्यथा अणु
		cr[2] = op->src.u.sb * CCP_SB_BYTES;
		cr[3] = (CCP_MEMTYPE_SB << REQ4_MEMTYPE_SHIFT);
	पूर्ण

	अगर (op->dst.type == CCP_MEMTYPE_SYSTEM) अणु
		cr[4] = ccp_addr_lo(&op->dst.u.dma);
		cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
			| ccp_addr_hi(&op->dst.u.dma);
	पूर्ण अन्यथा अणु
		cr[4] = op->dst.u.sb * CCP_SB_BYTES;
		cr[5] = (CCP_MEMTYPE_SB << REQ6_MEMTYPE_SHIFT);
	पूर्ण

	अगर (op->eom)
		cr[0] |= REQ1_EOM;

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल पूर्णांक ccp_perक्रमm_ecc(काष्ठा ccp_op *op)
अणु
	u32 cr[6];

	/* Fill out the रेजिस्टर contents क्रम REQ1 through REQ6 */
	cr[0] = REQ1_ECC_AFFINE_CONVERT
		| (CCP_ENGINE_ECC << REQ1_ENGINE_SHIFT)
		| (op->u.ecc.function << REQ1_ECC_FUNCTION_SHIFT)
		| REQ1_EOM;
	cr[1] = op->src.u.dma.length - 1;
	cr[2] = ccp_addr_lo(&op->src.u.dma);
	cr[3] = (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->src.u.dma);
	cr[4] = ccp_addr_lo(&op->dst.u.dma);
	cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
		| ccp_addr_hi(&op->dst.u.dma);

	वापस ccp_करो_cmd(op, cr, ARRAY_SIZE(cr));
पूर्ण

अटल व्योम ccp_disable_queue_पूर्णांकerrupts(काष्ठा ccp_device *ccp)
अणु
	ioग_लिखो32(0x00, ccp->io_regs + IRQ_MASK_REG);
पूर्ण

अटल व्योम ccp_enable_queue_पूर्णांकerrupts(काष्ठा ccp_device *ccp)
अणु
	ioग_लिखो32(ccp->qim, ccp->io_regs + IRQ_MASK_REG);
पूर्ण

अटल व्योम ccp_irq_bh(अचिन्हित दीर्घ data)
अणु
	काष्ठा ccp_device *ccp = (काष्ठा ccp_device *)data;
	काष्ठा ccp_cmd_queue *cmd_q;
	u32 q_पूर्णांक, status;
	अचिन्हित पूर्णांक i;

	status = ioपढ़ो32(ccp->io_regs + IRQ_STATUS_REG);

	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		q_पूर्णांक = status & (cmd_q->पूर्णांक_ok | cmd_q->पूर्णांक_err);
		अगर (q_पूर्णांक) अणु
			cmd_q->पूर्णांक_status = status;
			cmd_q->q_status = ioपढ़ो32(cmd_q->reg_status);
			cmd_q->q_पूर्णांक_status = ioपढ़ो32(cmd_q->reg_पूर्णांक_status);

			/* On error, only save the first error value */
			अगर ((q_पूर्णांक & cmd_q->पूर्णांक_err) && !cmd_q->cmd_error)
				cmd_q->cmd_error = CMD_Q_ERROR(cmd_q->q_status);

			cmd_q->पूर्णांक_rcvd = 1;

			/* Acknowledge the पूर्णांकerrupt and wake the kthपढ़ो */
			ioग_लिखो32(q_पूर्णांक, ccp->io_regs + IRQ_STATUS_REG);
			wake_up_पूर्णांकerruptible(&cmd_q->पूर्णांक_queue);
		पूर्ण
	पूर्ण
	ccp_enable_queue_पूर्णांकerrupts(ccp);
पूर्ण

अटल irqवापस_t ccp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ccp_device *ccp = (काष्ठा ccp_device *)data;

	ccp_disable_queue_पूर्णांकerrupts(ccp);
	अगर (ccp->use_tasklet)
		tasklet_schedule(&ccp->irq_tasklet);
	अन्यथा
		ccp_irq_bh((अचिन्हित दीर्घ)ccp);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ccp_init(काष्ठा ccp_device *ccp)
अणु
	काष्ठा device *dev = ccp->dev;
	काष्ठा ccp_cmd_queue *cmd_q;
	काष्ठा dma_pool *dma_pool;
	अक्षर dma_pool_name[MAX_DMAPOOL_NAME_LEN];
	अचिन्हित पूर्णांक qmr, i;
	पूर्णांक ret;

	/* Find available queues */
	ccp->qim = 0;
	qmr = ioपढ़ो32(ccp->io_regs + Q_MASK_REG);
	क्रम (i = 0; (i < MAX_HW_QUEUES) && (ccp->cmd_q_count < ccp->max_q_count); i++) अणु
		अगर (!(qmr & (1 << i)))
			जारी;

		/* Allocate a dma pool क्रम this queue */
		snम_लिखो(dma_pool_name, माप(dma_pool_name), "%s_q%d",
			 ccp->name, i);
		dma_pool = dma_pool_create(dma_pool_name, dev,
					   CCP_DMAPOOL_MAX_SIZE,
					   CCP_DMAPOOL_ALIGN, 0);
		अगर (!dma_pool) अणु
			dev_err(dev, "unable to allocate dma pool\n");
			ret = -ENOMEM;
			जाओ e_pool;
		पूर्ण

		cmd_q = &ccp->cmd_q[ccp->cmd_q_count];
		ccp->cmd_q_count++;

		cmd_q->ccp = ccp;
		cmd_q->id = i;
		cmd_q->dma_pool = dma_pool;

		/* Reserve 2 KSB regions क्रम the queue */
		cmd_q->sb_key = KSB_START + ccp->sb_start++;
		cmd_q->sb_ctx = KSB_START + ccp->sb_start++;
		ccp->sb_count -= 2;

		/* Preset some रेजिस्टर values and masks that are queue
		 * number dependent
		 */
		cmd_q->reg_status = ccp->io_regs + CMD_Q_STATUS_BASE +
				    (CMD_Q_STATUS_INCR * i);
		cmd_q->reg_पूर्णांक_status = ccp->io_regs + CMD_Q_INT_STATUS_BASE +
					(CMD_Q_STATUS_INCR * i);
		cmd_q->पूर्णांक_ok = 1 << (i * 2);
		cmd_q->पूर्णांक_err = 1 << ((i * 2) + 1);

		cmd_q->मुक्त_slots = ccp_get_मुक्त_slots(cmd_q);

		init_रुकोqueue_head(&cmd_q->पूर्णांक_queue);

		/* Build queue पूर्णांकerrupt mask (two पूर्णांकerrupts per queue) */
		ccp->qim |= cmd_q->पूर्णांक_ok | cmd_q->पूर्णांक_err;

#अगर_घोषित CONFIG_ARM64
		/* For arm64 set the recommended queue cache settings */
		ioग_लिखो32(ccp->axcache, ccp->io_regs + CMD_Q_CACHE_BASE +
			  (CMD_Q_CACHE_INC * i));
#पूर्ण_अगर

		dev_dbg(dev, "queue #%u available\n", i);
	पूर्ण
	अगर (ccp->cmd_q_count == 0) अणु
		dev_notice(dev, "no command queues available\n");
		ret = -EIO;
		जाओ e_pool;
	पूर्ण
	dev_notice(dev, "%u command queues available\n", ccp->cmd_q_count);

	/* Disable and clear पूर्णांकerrupts until पढ़ोy */
	ccp_disable_queue_पूर्णांकerrupts(ccp);
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		ioपढ़ो32(cmd_q->reg_पूर्णांक_status);
		ioपढ़ो32(cmd_q->reg_status);
	पूर्ण
	ioग_लिखो32(ccp->qim, ccp->io_regs + IRQ_STATUS_REG);

	/* Request an irq */
	ret = sp_request_ccp_irq(ccp->sp, ccp_irq_handler, ccp->name, ccp);
	अगर (ret) अणु
		dev_err(dev, "unable to allocate an IRQ\n");
		जाओ e_pool;
	पूर्ण

	/* Initialize the ISR tasklet? */
	अगर (ccp->use_tasklet)
		tasklet_init(&ccp->irq_tasklet, ccp_irq_bh,
			     (अचिन्हित दीर्घ)ccp);

	dev_dbg(dev, "Starting threads...\n");
	/* Create a kthपढ़ो क्रम each queue */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		काष्ठा task_काष्ठा *kthपढ़ो;

		cmd_q = &ccp->cmd_q[i];

		kthपढ़ो = kthपढ़ो_create(ccp_cmd_queue_thपढ़ो, cmd_q,
					 "%s-q%u", ccp->name, cmd_q->id);
		अगर (IS_ERR(kthपढ़ो)) अणु
			dev_err(dev, "error creating queue thread (%ld)\n",
				PTR_ERR(kthपढ़ो));
			ret = PTR_ERR(kthपढ़ो);
			जाओ e_kthपढ़ो;
		पूर्ण

		cmd_q->kthपढ़ो = kthपढ़ो;
		wake_up_process(kthपढ़ो);
	पूर्ण

	dev_dbg(dev, "Enabling interrupts...\n");
	/* Enable पूर्णांकerrupts */
	ccp_enable_queue_पूर्णांकerrupts(ccp);

	dev_dbg(dev, "Registering device...\n");
	ccp_add_device(ccp);

	ret = ccp_रेजिस्टर_rng(ccp);
	अगर (ret)
		जाओ e_kthपढ़ो;

	/* Register the DMA engine support */
	ret = ccp_dmaengine_रेजिस्टर(ccp);
	अगर (ret)
		जाओ e_hwrng;

	वापस 0;

e_hwrng:
	ccp_unरेजिस्टर_rng(ccp);

e_kthपढ़ो:
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		अगर (ccp->cmd_q[i].kthपढ़ो)
			kthपढ़ो_stop(ccp->cmd_q[i].kthपढ़ो);

	sp_मुक्त_ccp_irq(ccp->sp, ccp);

e_pool:
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		dma_pool_destroy(ccp->cmd_q[i].dma_pool);

	वापस ret;
पूर्ण

अटल व्योम ccp_destroy(काष्ठा ccp_device *ccp)
अणु
	काष्ठा ccp_cmd_queue *cmd_q;
	काष्ठा ccp_cmd *cmd;
	अचिन्हित पूर्णांक i;

	/* Unरेजिस्टर the DMA engine */
	ccp_dmaengine_unरेजिस्टर(ccp);

	/* Unरेजिस्टर the RNG */
	ccp_unरेजिस्टर_rng(ccp);

	/* Remove this device from the list of available units */
	ccp_del_device(ccp);

	/* Disable and clear पूर्णांकerrupts */
	ccp_disable_queue_पूर्णांकerrupts(ccp);
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		ioपढ़ो32(cmd_q->reg_पूर्णांक_status);
		ioपढ़ो32(cmd_q->reg_status);
	पूर्ण
	ioग_लिखो32(ccp->qim, ccp->io_regs + IRQ_STATUS_REG);

	/* Stop the queue kthपढ़ोs */
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		अगर (ccp->cmd_q[i].kthपढ़ो)
			kthपढ़ो_stop(ccp->cmd_q[i].kthपढ़ो);

	sp_मुक्त_ccp_irq(ccp->sp, ccp);

	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		dma_pool_destroy(ccp->cmd_q[i].dma_pool);

	/* Flush the cmd and backlog queue */
	जबतक (!list_empty(&ccp->cmd)) अणु
		/* Invoke the callback directly with an error code */
		cmd = list_first_entry(&ccp->cmd, काष्ठा ccp_cmd, entry);
		list_del(&cmd->entry);
		cmd->callback(cmd->data, -ENODEV);
	पूर्ण
	जबतक (!list_empty(&ccp->backlog)) अणु
		/* Invoke the callback directly with an error code */
		cmd = list_first_entry(&ccp->backlog, काष्ठा ccp_cmd, entry);
		list_del(&cmd->entry);
		cmd->callback(cmd->data, -ENODEV);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ccp_actions ccp3_actions = अणु
	.aes = ccp_perक्रमm_aes,
	.xts_aes = ccp_perक्रमm_xts_aes,
	.des3 = शून्य,
	.sha = ccp_perक्रमm_sha,
	.rsa = ccp_perक्रमm_rsa,
	.passthru = ccp_perक्रमm_passthru,
	.ecc = ccp_perक्रमm_ecc,
	.sballoc = ccp_alloc_ksb,
	.sbमुक्त = ccp_मुक्त_ksb,
	.init = ccp_init,
	.destroy = ccp_destroy,
	.get_मुक्त_slots = ccp_get_मुक्त_slots,
	.irqhandler = ccp_irq_handler,
पूर्ण;

स्थिर काष्ठा ccp_vdata ccpv3_platक्रमm = अणु
	.version = CCP_VERSION(3, 0),
	.setup = शून्य,
	.perक्रमm = &ccp3_actions,
	.offset = 0,
	.rsamax = CCP_RSA_MAX_WIDTH,
पूर्ण;

स्थिर काष्ठा ccp_vdata ccpv3 = अणु
	.version = CCP_VERSION(3, 0),
	.setup = शून्य,
	.perक्रमm = &ccp3_actions,
	.offset = 0x20000,
	.rsamax = CCP_RSA_MAX_WIDTH,
पूर्ण;
