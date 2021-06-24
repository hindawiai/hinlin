<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश "otx_cptvf.h"
#समावेश "otx_cptvf_algs.h"
#समावेश "otx_cptvf_reqmgr.h"

#घोषणा DRV_NAME	"octeontx-cptvf"
#घोषणा DRV_VERSION	"1.0"

अटल व्योम vq_work_handler(अचिन्हित दीर्घ data)
अणु
	काष्ठा otx_cptvf_wqe_info *cwqe_info =
					(काष्ठा otx_cptvf_wqe_info *) data;

	otx_cpt_post_process(&cwqe_info->vq_wqe[0]);
पूर्ण

अटल पूर्णांक init_worker_thपढ़ोs(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा otx_cptvf_wqe_info *cwqe_info;
	पूर्णांक i;

	cwqe_info = kzalloc(माप(*cwqe_info), GFP_KERNEL);
	अगर (!cwqe_info)
		वापस -ENOMEM;

	अगर (cptvf->num_queues) अणु
		dev_dbg(&pdev->dev, "Creating VQ worker threads (%d)\n",
			cptvf->num_queues);
	पूर्ण

	क्रम (i = 0; i < cptvf->num_queues; i++) अणु
		tasklet_init(&cwqe_info->vq_wqe[i].twork, vq_work_handler,
			     (u64)cwqe_info);
		cwqe_info->vq_wqe[i].cptvf = cptvf;
	पूर्ण
	cptvf->wqe_info = cwqe_info;

	वापस 0;
पूर्ण

अटल व्योम cleanup_worker_thपढ़ोs(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा otx_cptvf_wqe_info *cwqe_info;
	पूर्णांक i;

	cwqe_info = (काष्ठा otx_cptvf_wqe_info *)cptvf->wqe_info;
	अगर (!cwqe_info)
		वापस;

	अगर (cptvf->num_queues) अणु
		dev_dbg(&pdev->dev, "Cleaning VQ worker threads (%u)\n",
			cptvf->num_queues);
	पूर्ण

	क्रम (i = 0; i < cptvf->num_queues; i++)
		tasklet_समाप्त(&cwqe_info->vq_wqe[i].twork);

	kमुक्त_sensitive(cwqe_info);
	cptvf->wqe_info = शून्य;
पूर्ण

अटल व्योम मुक्त_pending_queues(काष्ठा otx_cpt_pending_qinfo *pqinfo)
अणु
	काष्ठा otx_cpt_pending_queue *queue;
	पूर्णांक i;

	क्रम_each_pending_queue(pqinfo, queue, i) अणु
		अगर (!queue->head)
			जारी;

		/* मुक्त single queue */
		kमुक्त_sensitive((queue->head));
		queue->front = 0;
		queue->rear = 0;
		queue->qlen = 0;
	पूर्ण
	pqinfo->num_queues = 0;
पूर्ण

अटल पूर्णांक alloc_pending_queues(काष्ठा otx_cpt_pending_qinfo *pqinfo, u32 qlen,
				u32 num_queues)
अणु
	काष्ठा otx_cpt_pending_queue *queue = शून्य;
	माप_प्रकार size;
	पूर्णांक ret;
	u32 i;

	pqinfo->num_queues = num_queues;
	size = (qlen * माप(काष्ठा otx_cpt_pending_entry));

	क्रम_each_pending_queue(pqinfo, queue, i) अणु
		queue->head = kzalloc((size), GFP_KERNEL);
		अगर (!queue->head) अणु
			ret = -ENOMEM;
			जाओ pending_qfail;
		पूर्ण

		queue->pending_count = 0;
		queue->front = 0;
		queue->rear = 0;
		queue->qlen = qlen;

		/* init queue spin lock */
		spin_lock_init(&queue->lock);
	पूर्ण
	वापस 0;

pending_qfail:
	मुक्त_pending_queues(pqinfo);

	वापस ret;
पूर्ण

अटल पूर्णांक init_pending_queues(काष्ठा otx_cptvf *cptvf, u32 qlen,
			       u32 num_queues)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक ret;

	अगर (!num_queues)
		वापस 0;

	ret = alloc_pending_queues(&cptvf->pqinfo, qlen, num_queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup pending queues (%u)\n",
			num_queues);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cleanup_pending_queues(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!cptvf->num_queues)
		वापस;

	dev_dbg(&pdev->dev, "Cleaning VQ pending queue (%u)\n",
		cptvf->num_queues);
	मुक्त_pending_queues(&cptvf->pqinfo);
पूर्ण

अटल व्योम मुक्त_command_queues(काष्ठा otx_cptvf *cptvf,
				काष्ठा otx_cpt_cmd_qinfo *cqinfo)
अणु
	काष्ठा otx_cpt_cmd_queue *queue = शून्य;
	काष्ठा otx_cpt_cmd_chunk *chunk = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक i;

	/* clean up क्रम each queue */
	क्रम (i = 0; i < cptvf->num_queues; i++) अणु
		queue = &cqinfo->queue[i];

		जबतक (!list_empty(&cqinfo->queue[i].chead)) अणु
			chunk = list_first_entry(&cqinfo->queue[i].chead,
					काष्ठा otx_cpt_cmd_chunk, nextchunk);

			dma_मुक्त_coherent(&pdev->dev, chunk->size,
					  chunk->head,
					  chunk->dma_addr);
			chunk->head = शून्य;
			chunk->dma_addr = 0;
			list_del(&chunk->nextchunk);
			kमुक्त_sensitive(chunk);
		पूर्ण
		queue->num_chunks = 0;
		queue->idx = 0;

	पूर्ण
पूर्ण

अटल पूर्णांक alloc_command_queues(काष्ठा otx_cptvf *cptvf,
				काष्ठा otx_cpt_cmd_qinfo *cqinfo,
				u32 qlen)
अणु
	काष्ठा otx_cpt_cmd_chunk *curr, *first, *last;
	काष्ठा otx_cpt_cmd_queue *queue = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	माप_प्रकार q_size, c_size, rem_q_size;
	u32 qcsize_bytes;
	पूर्णांक i;


	/* Qsize in dwords, needed क्रम SADDR config, 1-next chunk poपूर्णांकer */
	cptvf->qsize = min(qlen, cqinfo->qchunksize) *
		       OTX_CPT_NEXT_CHUNK_PTR_SIZE + 1;
	/* Qsize in bytes to create space क्रम alignment */
	q_size = qlen * OTX_CPT_INST_SIZE;

	qcsize_bytes = cqinfo->qchunksize * OTX_CPT_INST_SIZE;

	/* per queue initialization */
	क्रम (i = 0; i < cptvf->num_queues; i++) अणु
		c_size = 0;
		rem_q_size = q_size;
		first = शून्य;
		last = शून्य;

		queue = &cqinfo->queue[i];
		INIT_LIST_HEAD(&queue->chead);
		करो अणु
			curr = kzalloc(माप(*curr), GFP_KERNEL);
			अगर (!curr)
				जाओ cmd_qfail;

			c_size = (rem_q_size > qcsize_bytes) ? qcsize_bytes :
					rem_q_size;
			curr->head = dma_alloc_coherent(&pdev->dev,
					   c_size + OTX_CPT_NEXT_CHUNK_PTR_SIZE,
					   &curr->dma_addr, GFP_KERNEL);
			अगर (!curr->head) अणु
				dev_err(&pdev->dev,
				"Command Q (%d) chunk (%d) allocation failed\n",
					i, queue->num_chunks);
				जाओ मुक्त_curr;
			पूर्ण
			curr->size = c_size;

			अगर (queue->num_chunks == 0) अणु
				first = curr;
				queue->base  = first;
			पूर्ण
			list_add_tail(&curr->nextchunk,
				      &cqinfo->queue[i].chead);

			queue->num_chunks++;
			rem_q_size -= c_size;
			अगर (last)
				*((u64 *)(&last->head[last->size])) =
					(u64)curr->dma_addr;

			last = curr;
		पूर्ण जबतक (rem_q_size);

		/*
		 * Make the queue circular, tie back last chunk entry to head
		 */
		curr = first;
		*((u64 *)(&last->head[last->size])) = (u64)curr->dma_addr;
		queue->qhead = curr;
	पूर्ण
	वापस 0;
मुक्त_curr:
	kमुक्त(curr);
cmd_qfail:
	मुक्त_command_queues(cptvf, cqinfo);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक init_command_queues(काष्ठा otx_cptvf *cptvf, u32 qlen)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक ret;

	/* setup command queues */
	ret = alloc_command_queues(cptvf, &cptvf->cqinfo, qlen);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to allocate command queues (%u)\n",
			cptvf->num_queues);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cleanup_command_queues(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!cptvf->num_queues)
		वापस;

	dev_dbg(&pdev->dev, "Cleaning VQ command queue (%u)\n",
		cptvf->num_queues);
	मुक्त_command_queues(cptvf, &cptvf->cqinfo);
पूर्ण

अटल व्योम cptvf_sw_cleanup(काष्ठा otx_cptvf *cptvf)
अणु
	cleanup_worker_thपढ़ोs(cptvf);
	cleanup_pending_queues(cptvf);
	cleanup_command_queues(cptvf);
पूर्ण

अटल पूर्णांक cptvf_sw_init(काष्ठा otx_cptvf *cptvf, u32 qlen, u32 num_queues)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	u32 max_dev_queues = 0;
	पूर्णांक ret;

	max_dev_queues = OTX_CPT_NUM_QS_PER_VF;
	/* possible cpus */
	num_queues = min_t(u32, num_queues, max_dev_queues);
	cptvf->num_queues = num_queues;

	ret = init_command_queues(cptvf, qlen);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup command queues (%u)\n",
			num_queues);
		वापस ret;
	पूर्ण

	ret = init_pending_queues(cptvf, qlen, num_queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup pending queues (%u)\n",
			num_queues);
		जाओ setup_pqfail;
	पूर्ण

	/* Create worker thपढ़ोs क्रम BH processing */
	ret = init_worker_thपढ़ोs(cptvf);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup worker threads\n");
		जाओ init_work_fail;
	पूर्ण
	वापस 0;

init_work_fail:
	cleanup_worker_thपढ़ोs(cptvf);
	cleanup_pending_queues(cptvf);

setup_pqfail:
	cleanup_command_queues(cptvf);

	वापस ret;
पूर्ण

अटल व्योम cptvf_मुक्त_irq_affinity(काष्ठा otx_cptvf *cptvf, पूर्णांक vec)
अणु
	irq_set_affinity_hपूर्णांक(pci_irq_vector(cptvf->pdev, vec), शून्य);
	मुक्त_cpumask_var(cptvf->affinity_mask[vec]);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_ctl(काष्ठा otx_cptvf *cptvf, bool val)
अणु
	जोड़ otx_cptx_vqx_ctl vqx_ctl;

	vqx_ctl.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_CTL(0));
	vqx_ctl.s.ena = val;
	ग_लिखोq(vqx_ctl.u, cptvf->reg_base + OTX_CPT_VQX_CTL(0));
पूर्ण

व्योम otx_cptvf_ग_लिखो_vq_करोorbell(काष्ठा otx_cptvf *cptvf, u32 val)
अणु
	जोड़ otx_cptx_vqx_करोorbell vqx_dbell;

	vqx_dbell.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DOORBELL(0));
	vqx_dbell.s.dbell_cnt = val * 8; /* Num of Inकाष्ठाions * 8 words */
	ग_लिखोq(vqx_dbell.u, cptvf->reg_base + OTX_CPT_VQX_DOORBELL(0));
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_inprog(काष्ठा otx_cptvf *cptvf, u8 val)
अणु
	जोड़ otx_cptx_vqx_inprog vqx_inprg;

	vqx_inprg.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_INPROG(0));
	vqx_inprg.s.inflight = val;
	ग_लिखोq(vqx_inprg.u, cptvf->reg_base + OTX_CPT_VQX_INPROG(0));
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_करोne_numरुको(काष्ठा otx_cptvf *cptvf, u32 val)
अणु
	जोड़ otx_cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
	vqx_dरुको.s.num_रुको = val;
	ग_लिखोq(vqx_dरुको.u, cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
पूर्ण

अटल u32 cptvf_पढ़ो_vq_करोne_numरुको(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
	वापस vqx_dरुको.s.num_रुको;
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_करोne_समयरुको(काष्ठा otx_cptvf *cptvf, u16 समय)
अणु
	जोड़ otx_cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
	vqx_dरुको.s.समय_रुको = समय;
	ग_लिखोq(vqx_dरुको.u, cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
पूर्ण


अटल u16 cptvf_पढ़ो_vq_करोne_समयरुको(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_WAIT(0));
	वापस vqx_dरुको.s.समय_रुको;
पूर्ण

अटल व्योम cptvf_enable_swerr_पूर्णांकerrupts(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_ENA_W1S(0));
	/* Enable SWERR पूर्णांकerrupts क्रम the requested VF */
	vqx_misc_ena.s.swerr = 1;
	ग_लिखोq(vqx_misc_ena.u, cptvf->reg_base + OTX_CPT_VQX_MISC_ENA_W1S(0));
पूर्ण

अटल व्योम cptvf_enable_mbox_पूर्णांकerrupts(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_ENA_W1S(0));
	/* Enable MBOX पूर्णांकerrupt क्रम the requested VF */
	vqx_misc_ena.s.mbox = 1;
	ग_लिखोq(vqx_misc_ena.u, cptvf->reg_base + OTX_CPT_VQX_MISC_ENA_W1S(0));
पूर्ण

अटल व्योम cptvf_enable_करोne_पूर्णांकerrupts(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_करोne_ena_w1s vqx_करोne_ena;

	vqx_करोne_ena.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_ENA_W1S(0));
	/* Enable DONE पूर्णांकerrupt क्रम the requested VF */
	vqx_करोne_ena.s.करोne = 1;
	ग_लिखोq(vqx_करोne_ena.u, cptvf->reg_base + OTX_CPT_VQX_DONE_ENA_W1S(0));
पूर्ण

अटल व्योम cptvf_clear_करोvf_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.करोvf = 1;
	ग_लिखोq(vqx_misc_पूर्णांक.u, cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल व्योम cptvf_clear_irde_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.irde = 1;
	ग_लिखोq(vqx_misc_पूर्णांक.u, cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल व्योम cptvf_clear_nwrp_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.nwrp = 1;
	ग_लिखोq(vqx_misc_पूर्णांक.u, cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल व्योम cptvf_clear_mbox_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.mbox = 1;
	ग_लिखोq(vqx_misc_पूर्णांक.u, cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल व्योम cptvf_clear_swerr_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.swerr = 1;
	ग_लिखोq(vqx_misc_पूर्णांक.u, cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल u64 cptvf_पढ़ो_vf_misc_पूर्णांकr_status(काष्ठा otx_cptvf *cptvf)
अणु
	वापस पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_MISC_INT(0));
पूर्ण

अटल irqवापस_t cptvf_misc_पूर्णांकr_handler(पूर्णांक __always_unused irq,
					   व्योम *arg)
अणु
	काष्ठा otx_cptvf *cptvf = arg;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	u64 पूर्णांकr;

	पूर्णांकr = cptvf_पढ़ो_vf_misc_पूर्णांकr_status(cptvf);
	/* Check क्रम MISC पूर्णांकerrupt types */
	अगर (likely(पूर्णांकr & OTX_CPT_VF_INTR_MBOX_MASK)) अणु
		dev_dbg(&pdev->dev, "Mailbox interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
		otx_cptvf_handle_mbox_पूर्णांकr(cptvf);
		cptvf_clear_mbox_पूर्णांकr(cptvf);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & OTX_CPT_VF_INTR_DOVF_MASK)) अणु
		cptvf_clear_करोvf_पूर्णांकr(cptvf);
		/* Clear करोorbell count */
		otx_cptvf_ग_लिखो_vq_करोorbell(cptvf, 0);
		dev_err(&pdev->dev,
		"Doorbell overflow error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & OTX_CPT_VF_INTR_IRDE_MASK)) अणु
		cptvf_clear_irde_पूर्णांकr(cptvf);
		dev_err(&pdev->dev,
		"Instruction NCB read error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & OTX_CPT_VF_INTR_NWRP_MASK)) अणु
		cptvf_clear_nwrp_पूर्णांकr(cptvf);
		dev_err(&pdev->dev,
		"NCB response write error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & OTX_CPT_VF_INTR_SERR_MASK)) अणु
		cptvf_clear_swerr_पूर्णांकr(cptvf);
		dev_err(&pdev->dev,
			"Software error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Unhandled interrupt in OTX_CPT VF %d\n",
			cptvf->vfid);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा otx_cptvf_wqe *get_cptvf_vq_wqe(काष्ठा otx_cptvf *cptvf,
						     पूर्णांक qno)
अणु
	काष्ठा otx_cptvf_wqe_info *nwqe_info;

	अगर (unlikely(qno >= cptvf->num_queues))
		वापस शून्य;
	nwqe_info = (काष्ठा otx_cptvf_wqe_info *)cptvf->wqe_info;

	वापस &nwqe_info->vq_wqe[qno];
पूर्ण

अटल अंतरभूत u32 cptvf_पढ़ो_vq_करोne_count(काष्ठा otx_cptvf *cptvf)
अणु
	जोड़ otx_cptx_vqx_करोne vqx_करोne;

	vqx_करोne.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE(0));
	वापस vqx_करोne.s.करोne;
पूर्ण

अटल अंतरभूत व्योम cptvf_ग_लिखो_vq_करोne_ack(काष्ठा otx_cptvf *cptvf,
					   u32 ackcnt)
अणु
	जोड़ otx_cptx_vqx_करोne_ack vqx_dack_cnt;

	vqx_dack_cnt.u = पढ़ोq(cptvf->reg_base + OTX_CPT_VQX_DONE_ACK(0));
	vqx_dack_cnt.s.करोne_ack = ackcnt;
	ग_लिखोq(vqx_dack_cnt.u, cptvf->reg_base + OTX_CPT_VQX_DONE_ACK(0));
पूर्ण

अटल irqवापस_t cptvf_करोne_पूर्णांकr_handler(पूर्णांक __always_unused irq,
					   व्योम *cptvf_dev)
अणु
	काष्ठा otx_cptvf *cptvf = (काष्ठा otx_cptvf *)cptvf_dev;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	/* Read the number of completions */
	u32 पूर्णांकr = cptvf_पढ़ो_vq_करोne_count(cptvf);

	अगर (पूर्णांकr) अणु
		काष्ठा otx_cptvf_wqe *wqe;

		/*
		 * Acknowledge the number of scheduled completions क्रम
		 * processing
		 */
		cptvf_ग_लिखो_vq_करोne_ack(cptvf, पूर्णांकr);
		wqe = get_cptvf_vq_wqe(cptvf, 0);
		अगर (unlikely(!wqe)) अणु
			dev_err(&pdev->dev, "No work to schedule for VF (%d)\n",
				cptvf->vfid);
			वापस IRQ_NONE;
		पूर्ण
		tasklet_hi_schedule(&wqe->twork);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cptvf_set_irq_affinity(काष्ठा otx_cptvf *cptvf, पूर्णांक vec)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक cpu;

	अगर (!zalloc_cpumask_var(&cptvf->affinity_mask[vec],
				GFP_KERNEL)) अणु
		dev_err(&pdev->dev,
			"Allocation failed for affinity_mask for VF %d\n",
			cptvf->vfid);
		वापस;
	पूर्ण

	cpu = cptvf->vfid % num_online_cpus();
	cpumask_set_cpu(cpumask_local_spपढ़ो(cpu, cptvf->node),
			cptvf->affinity_mask[vec]);
	irq_set_affinity_hपूर्णांक(pci_irq_vector(pdev, vec),
			      cptvf->affinity_mask[vec]);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_saddr(काष्ठा otx_cptvf *cptvf, u64 val)
अणु
	जोड़ otx_cptx_vqx_saddr vqx_saddr;

	vqx_saddr.u = val;
	ग_लिखोq(vqx_saddr.u, cptvf->reg_base + OTX_CPT_VQX_SADDR(0));
पूर्ण

अटल व्योम cptvf_device_init(काष्ठा otx_cptvf *cptvf)
अणु
	u64 base_addr = 0;

	/* Disable the VQ */
	cptvf_ग_लिखो_vq_ctl(cptvf, 0);
	/* Reset the करोorbell */
	otx_cptvf_ग_लिखो_vq_करोorbell(cptvf, 0);
	/* Clear inflight */
	cptvf_ग_लिखो_vq_inprog(cptvf, 0);
	/* Write VQ SADDR */
	base_addr = (u64)(cptvf->cqinfo.queue[0].qhead->dma_addr);
	cptvf_ग_लिखो_vq_saddr(cptvf, base_addr);
	/* Configure समयrhold / coalescence */
	cptvf_ग_लिखो_vq_करोne_समयरुको(cptvf, OTX_CPT_TIMER_HOLD);
	cptvf_ग_लिखो_vq_करोne_numरुको(cptvf, OTX_CPT_COUNT_HOLD);
	/* Enable the VQ */
	cptvf_ग_लिखो_vq_ctl(cptvf, 1);
	/* Flag the VF पढ़ोy */
	cptvf->flags |= OTX_CPT_FLAG_DEVICE_READY;
पूर्ण

अटल sमाप_प्रकार vf_type_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);
	अक्षर *msg;

	चयन (cptvf->vftype) अणु
	हाल OTX_CPT_AE_TYPES:
		msg = "AE";
		अवरोध;

	हाल OTX_CPT_SE_TYPES:
		msg = "SE";
		अवरोध;

	शेष:
		msg = "Invalid";
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", msg);
पूर्ण

अटल sमाप_प्रकार vf_engine_group_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", cptvf->vfgrp);
पूर्ण

अटल sमाप_प्रकार vf_engine_group_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);
	पूर्णांक val, ret;

	ret = kstrtoपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val < 0)
		वापस -EINVAL;

	अगर (val >= OTX_CPT_MAX_ENGINE_GROUPS) अणु
		dev_err(dev, "Engine group >= than max available groups %d\n",
			OTX_CPT_MAX_ENGINE_GROUPS);
		वापस -EINVAL;
	पूर्ण

	ret = otx_cptvf_send_vf_to_grp_msg(cptvf, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार vf_coalesc_समय_रुको_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 cptvf_पढ़ो_vq_करोne_समयरुको(cptvf));
पूर्ण

अटल sमाप_प्रकार vf_coalesc_num_रुको_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 cptvf_पढ़ो_vq_करोne_numरुको(cptvf));
पूर्ण

अटल sमाप_प्रकार vf_coalesc_समय_रुको_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret != 0)
		वापस ret;

	अगर (val < OTX_CPT_COALESC_MIN_TIME_WAIT ||
	    val > OTX_CPT_COALESC_MAX_TIME_WAIT)
		वापस -EINVAL;

	cptvf_ग_लिखो_vq_करोne_समयरुको(cptvf, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार vf_coalesc_num_रुको_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा otx_cptvf *cptvf = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret != 0)
		वापस ret;

	अगर (val < OTX_CPT_COALESC_MIN_NUM_WAIT ||
	    val > OTX_CPT_COALESC_MAX_NUM_WAIT)
		वापस -EINVAL;

	cptvf_ग_लिखो_vq_करोne_numरुको(cptvf, val);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(vf_type);
अटल DEVICE_ATTR_RW(vf_engine_group);
अटल DEVICE_ATTR_RW(vf_coalesc_समय_रुको);
अटल DEVICE_ATTR_RW(vf_coalesc_num_रुको);

अटल काष्ठा attribute *otx_cptvf_attrs[] = अणु
	&dev_attr_vf_type.attr,
	&dev_attr_vf_engine_group.attr,
	&dev_attr_vf_coalesc_समय_रुको.attr,
	&dev_attr_vf_coalesc_num_रुको.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group otx_cptvf_sysfs_group = अणु
	.attrs = otx_cptvf_attrs,
पूर्ण;

अटल पूर्णांक otx_cptvf_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा otx_cptvf *cptvf;
	पूर्णांक err;

	cptvf = devm_kzalloc(dev, माप(*cptvf), GFP_KERNEL);
	अगर (!cptvf)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, cptvf);
	cptvf->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ clear_drvdata;
	पूर्ण
	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ disable_device;
	पूर्ण
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable 48-bit DMA configuration\n");
		जाओ release_regions;
	पूर्ण

	/* MAP PF's configuration रेजिस्टरs */
	cptvf->reg_base = pci_iomap(pdev, OTX_CPT_VF_PCI_CFG_BAR, 0);
	अगर (!cptvf->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ release_regions;
	पूर्ण

	cptvf->node = dev_to_node(&pdev->dev);
	err = pci_alloc_irq_vectors(pdev, OTX_CPT_VF_MSIX_VECTORS,
				    OTX_CPT_VF_MSIX_VECTORS, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(dev, "Request for #%d msix vectors failed\n",
			OTX_CPT_VF_MSIX_VECTORS);
		जाओ unmap_region;
	पूर्ण

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC),
			  cptvf_misc_पूर्णांकr_handler, 0, "CPT VF misc intr",
			  cptvf);
	अगर (err) अणु
		dev_err(dev, "Failed to request misc irq\n");
		जाओ मुक्त_vectors;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt */
	cptvf_enable_mbox_पूर्णांकerrupts(cptvf);
	cptvf_enable_swerr_पूर्णांकerrupts(cptvf);

	/* Check cpt pf status, माला_लो chip ID / device Id from PF अगर पढ़ोy */
	err = otx_cptvf_check_pf_पढ़ोy(cptvf);
	अगर (err)
		जाओ मुक्त_misc_irq;

	/* CPT VF software resources initialization */
	cptvf->cqinfo.qchunksize = OTX_CPT_CMD_QCHUNK_SIZE;
	err = cptvf_sw_init(cptvf, OTX_CPT_CMD_QLEN, OTX_CPT_NUM_QS_PER_VF);
	अगर (err) अणु
		dev_err(dev, "cptvf_sw_init() failed\n");
		जाओ मुक्त_misc_irq;
	पूर्ण
	/* Convey VQ LEN to PF */
	err = otx_cptvf_send_vq_size_msg(cptvf);
	अगर (err)
		जाओ sw_cleanup;

	/* CPT VF device initialization */
	cptvf_device_init(cptvf);
	/* Send msg to PF to assign currnet Q to required group */
	err = otx_cptvf_send_vf_to_grp_msg(cptvf, cptvf->vfgrp);
	अगर (err)
		जाओ sw_cleanup;

	cptvf->priority = 1;
	err = otx_cptvf_send_vf_priority_msg(cptvf);
	अगर (err)
		जाओ sw_cleanup;

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE),
			  cptvf_करोne_पूर्णांकr_handler, 0, "CPT VF done intr",
			  cptvf);
	अगर (err) अणु
		dev_err(dev, "Failed to request done irq\n");
		जाओ मुक्त_करोne_irq;
	पूर्ण

	/* Enable करोne पूर्णांकerrupt */
	cptvf_enable_करोne_पूर्णांकerrupts(cptvf);

	/* Set irq affinity masks */
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);

	err = otx_cptvf_send_vf_up(cptvf);
	अगर (err)
		जाओ मुक्त_irq_affinity;

	/* Initialize algorithms and set ops */
	err = otx_cpt_crypto_init(pdev, THIS_MODULE,
		    cptvf->vftype == OTX_CPT_SE_TYPES ? OTX_CPT_SE : OTX_CPT_AE,
		    cptvf->vftype, 1, cptvf->num_vfs);
	अगर (err) अणु
		dev_err(dev, "Failed to register crypto algs\n");
		जाओ मुक्त_irq_affinity;
	पूर्ण

	err = sysfs_create_group(&dev->kobj, &otx_cptvf_sysfs_group);
	अगर (err) अणु
		dev_err(dev, "Creating sysfs entries failed\n");
		जाओ crypto_निकास;
	पूर्ण

	वापस 0;

crypto_निकास:
	otx_cpt_crypto_निकास(pdev, THIS_MODULE, cptvf->vftype);
मुक्त_irq_affinity:
	cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
	cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
मुक्त_करोne_irq:
	मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE), cptvf);
sw_cleanup:
	cptvf_sw_cleanup(cptvf);
मुक्त_misc_irq:
	मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
मुक्त_vectors:
	pci_मुक्त_irq_vectors(cptvf->pdev);
unmap_region:
	pci_iounmap(pdev, cptvf->reg_base);
release_regions:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
clear_drvdata:
	pci_set_drvdata(pdev, शून्य);

	वापस err;
पूर्ण

अटल व्योम otx_cptvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx_cptvf *cptvf = pci_get_drvdata(pdev);

	अगर (!cptvf) अणु
		dev_err(&pdev->dev, "Invalid CPT-VF device\n");
		वापस;
	पूर्ण

	/* Convey DOWN to PF */
	अगर (otx_cptvf_send_vf_करोwn(cptvf)) अणु
		dev_err(&pdev->dev, "PF not responding to DOWN msg\n");
	पूर्ण अन्यथा अणु
		sysfs_हटाओ_group(&pdev->dev.kobj, &otx_cptvf_sysfs_group);
		otx_cpt_crypto_निकास(pdev, THIS_MODULE, cptvf->vftype);
		cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
		cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
		मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE), cptvf);
		मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
		cptvf_sw_cleanup(cptvf);
		pci_मुक्त_irq_vectors(cptvf->pdev);
		pci_iounmap(pdev, cptvf->reg_base);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		pci_set_drvdata(pdev, शून्य);
	पूर्ण
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id otx_cptvf_id_table[] = अणु
	अणुPCI_VDEVICE(CAVIUM, OTX_CPT_PCI_VF_DEVICE_ID), 0पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver otx_cptvf_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = otx_cptvf_id_table,
	.probe = otx_cptvf_probe,
	.हटाओ = otx_cptvf_हटाओ,
पूर्ण;

module_pci_driver(otx_cptvf_pci_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell OcteonTX CPT Virtual Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, otx_cptvf_id_table);
