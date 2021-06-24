<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cpumask.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pci.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_req.h"
#समावेश "nitrox_csr.h"

#घोषणा CRYPTO_CTX_SIZE	256

/* packet inuput ring alignments */
#घोषणा PKTIN_Q_ALIGN_BYTES 16
/* AQM Queue input alignments */
#घोषणा AQM_Q_ALIGN_BYTES 32

अटल पूर्णांक nitrox_cmdq_init(काष्ठा nitrox_cmdq *cmdq, पूर्णांक align_bytes)
अणु
	काष्ठा nitrox_device *ndev = cmdq->ndev;

	cmdq->qsize = (ndev->qlen * cmdq->instr_size) + align_bytes;
	cmdq->unalign_base = dma_alloc_coherent(DEV(ndev), cmdq->qsize,
						&cmdq->unalign_dma,
						GFP_KERNEL);
	अगर (!cmdq->unalign_base)
		वापस -ENOMEM;

	cmdq->dma = PTR_ALIGN(cmdq->unalign_dma, align_bytes);
	cmdq->base = cmdq->unalign_base + (cmdq->dma - cmdq->unalign_dma);
	cmdq->ग_लिखो_idx = 0;

	spin_lock_init(&cmdq->cmd_qlock);
	spin_lock_init(&cmdq->resp_qlock);
	spin_lock_init(&cmdq->backlog_qlock);

	INIT_LIST_HEAD(&cmdq->response_head);
	INIT_LIST_HEAD(&cmdq->backlog_head);
	INIT_WORK(&cmdq->backlog_qflush, backlog_qflush_work);

	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backlog_count, 0);
	वापस 0;
पूर्ण

अटल व्योम nitrox_cmdq_reset(काष्ठा nitrox_cmdq *cmdq)
अणु
	cmdq->ग_लिखो_idx = 0;
	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backlog_count, 0);
पूर्ण

अटल व्योम nitrox_cmdq_cleanup(काष्ठा nitrox_cmdq *cmdq)
अणु
	काष्ठा nitrox_device *ndev;

	अगर (!cmdq)
		वापस;

	अगर (!cmdq->unalign_base)
		वापस;

	ndev = cmdq->ndev;
	cancel_work_sync(&cmdq->backlog_qflush);

	dma_मुक्त_coherent(DEV(ndev), cmdq->qsize,
			  cmdq->unalign_base, cmdq->unalign_dma);
	nitrox_cmdq_reset(cmdq);

	cmdq->dbell_csr_addr = शून्य;
	cmdq->compl_cnt_csr_addr = शून्य;
	cmdq->unalign_base = शून्य;
	cmdq->base = शून्य;
	cmdq->unalign_dma = 0;
	cmdq->dma = 0;
	cmdq->qsize = 0;
	cmdq->instr_size = 0;
पूर्ण

अटल व्योम nitrox_मुक्त_aqm_queues(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->nr_queues; i++) अणु
		nitrox_cmdq_cleanup(ndev->aqmq[i]);
		kमुक्त_sensitive(ndev->aqmq[i]);
		ndev->aqmq[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक nitrox_alloc_aqm_queues(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ndev->nr_queues; i++) अणु
		काष्ठा nitrox_cmdq *cmdq;
		u64 offset;

		cmdq = kzalloc_node(माप(*cmdq), GFP_KERNEL, ndev->node);
		अगर (!cmdq) अणु
			err = -ENOMEM;
			जाओ aqmq_fail;
		पूर्ण

		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instr_size = माप(काष्ठा aqmq_command_s);

		/* AQM Queue Doorbell Counter Register Address */
		offset = AQMQ_DRBLX(i);
		cmdq->dbell_csr_addr = NITROX_CSR_ADDR(ndev, offset);
		/* AQM Queue Commands Completed Count Register Address */
		offset = AQMQ_CMD_CNTX(i);
		cmdq->compl_cnt_csr_addr = NITROX_CSR_ADDR(ndev, offset);

		err = nitrox_cmdq_init(cmdq, AQM_Q_ALIGN_BYTES);
		अगर (err) अणु
			kमुक्त_sensitive(cmdq);
			जाओ aqmq_fail;
		पूर्ण
		ndev->aqmq[i] = cmdq;
	पूर्ण

	वापस 0;

aqmq_fail:
	nitrox_मुक्त_aqm_queues(ndev);
	वापस err;
पूर्ण

अटल व्योम nitrox_मुक्त_pktin_queues(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->nr_queues; i++) अणु
		काष्ठा nitrox_cmdq *cmdq = &ndev->pkt_inq[i];

		nitrox_cmdq_cleanup(cmdq);
	पूर्ण
	kमुक्त(ndev->pkt_inq);
	ndev->pkt_inq = शून्य;
पूर्ण

अटल पूर्णांक nitrox_alloc_pktin_queues(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i, err;

	ndev->pkt_inq = kसुस्मृति_node(ndev->nr_queues,
				     माप(काष्ठा nitrox_cmdq),
				     GFP_KERNEL, ndev->node);
	अगर (!ndev->pkt_inq)
		वापस -ENOMEM;

	क्रम (i = 0; i < ndev->nr_queues; i++) अणु
		काष्ठा nitrox_cmdq *cmdq;
		u64 offset;

		cmdq = &ndev->pkt_inq[i];
		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instr_size = माप(काष्ठा nps_pkt_instr);

		/* packet input ring करोorbell address */
		offset = NPS_PKT_IN_INSTR_BAOFF_DBELLX(i);
		cmdq->dbell_csr_addr = NITROX_CSR_ADDR(ndev, offset);
		/* packet solicit port completion count address */
		offset = NPS_PKT_SLC_CNTSX(i);
		cmdq->compl_cnt_csr_addr = NITROX_CSR_ADDR(ndev, offset);

		err = nitrox_cmdq_init(cmdq, PKTIN_Q_ALIGN_BYTES);
		अगर (err)
			जाओ pktq_fail;
	पूर्ण
	वापस 0;

pktq_fail:
	nitrox_मुक्त_pktin_queues(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक create_crypto_dma_pool(काष्ठा nitrox_device *ndev)
अणु
	माप_प्रकार size;

	/* Crypto context pool, 16 byte aligned */
	size = CRYPTO_CTX_SIZE + माप(काष्ठा ctx_hdr);
	ndev->ctx_pool = dma_pool_create("nitrox-context",
					 DEV(ndev), size, 16, 0);
	अगर (!ndev->ctx_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम destroy_crypto_dma_pool(काष्ठा nitrox_device *ndev)
अणु
	अगर (!ndev->ctx_pool)
		वापस;

	dma_pool_destroy(ndev->ctx_pool);
	ndev->ctx_pool = शून्य;
पूर्ण

/*
 * crypto_alloc_context - Allocate crypto context from pool
 * @ndev: NITROX Device
 */
व्योम *crypto_alloc_context(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा ctx_hdr *ctx;
	काष्ठा crypto_ctx_hdr *chdr;
	व्योम *vaddr;
	dma_addr_t dma;

	chdr = kदो_स्मृति(माप(*chdr), GFP_KERNEL);
	अगर (!chdr)
		वापस शून्य;

	vaddr = dma_pool_zalloc(ndev->ctx_pool, GFP_KERNEL, &dma);
	अगर (!vaddr) अणु
		kमुक्त(chdr);
		वापस शून्य;
	पूर्ण

	/* fill meta data */
	ctx = vaddr;
	ctx->pool = ndev->ctx_pool;
	ctx->dma = dma;
	ctx->ctx_dma = dma + माप(काष्ठा ctx_hdr);

	chdr->pool = ndev->ctx_pool;
	chdr->dma = dma;
	chdr->vaddr = vaddr;

	वापस chdr;
पूर्ण

/**
 * crypto_मुक्त_context - Free crypto context to pool
 * @ctx: context to मुक्त
 */
व्योम crypto_मुक्त_context(व्योम *ctx)
अणु
	काष्ठा crypto_ctx_hdr *ctxp;

	अगर (!ctx)
		वापस;

	ctxp = ctx;
	dma_pool_मुक्त(ctxp->pool, ctxp->vaddr, ctxp->dma);
	kमुक्त(ctxp);
पूर्ण

/**
 * nitrox_common_sw_init - allocate software resources.
 * @ndev: NITROX device
 *
 * Allocates crypto context pools and command queues etc.
 *
 * Return: 0 on success, or a negative error code on error.
 */
पूर्णांक nitrox_common_sw_init(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक err = 0;

	/* per device crypto context pool */
	err = create_crypto_dma_pool(ndev);
	अगर (err)
		वापस err;

	err = nitrox_alloc_pktin_queues(ndev);
	अगर (err)
		destroy_crypto_dma_pool(ndev);

	err = nitrox_alloc_aqm_queues(ndev);
	अगर (err) अणु
		nitrox_मुक्त_pktin_queues(ndev);
		destroy_crypto_dma_pool(ndev);
	पूर्ण

	वापस err;
पूर्ण

/**
 * nitrox_common_sw_cleanup - मुक्त software resources.
 * @ndev: NITROX device
 */
व्योम nitrox_common_sw_cleanup(काष्ठा nitrox_device *ndev)
अणु
	nitrox_मुक्त_aqm_queues(ndev);
	nitrox_मुक्त_pktin_queues(ndev);
	destroy_crypto_dma_pool(ndev);
पूर्ण
