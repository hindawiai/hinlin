<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश "cptvf.h"

#घोषणा DRV_NAME	"thunder-cptvf"
#घोषणा DRV_VERSION	"1.0"

काष्ठा cptvf_wqe अणु
	काष्ठा tasklet_काष्ठा twork;
	व्योम *cptvf;
	u32 qno;
पूर्ण;

काष्ठा cptvf_wqe_info अणु
	काष्ठा cptvf_wqe vq_wqe[CPT_NUM_QS_PER_VF];
पूर्ण;

अटल व्योम vq_work_handler(अचिन्हित दीर्घ data)
अणु
	काष्ठा cptvf_wqe_info *cwqe_info = (काष्ठा cptvf_wqe_info *)data;
	काष्ठा cptvf_wqe *cwqe = &cwqe_info->vq_wqe[0];

	vq_post_process(cwqe->cptvf, cwqe->qno);
पूर्ण

अटल पूर्णांक init_worker_thपढ़ोs(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cptvf_wqe_info *cwqe_info;
	पूर्णांक i;

	cwqe_info = kzalloc(माप(*cwqe_info), GFP_KERNEL);
	अगर (!cwqe_info)
		वापस -ENOMEM;

	अगर (cptvf->nr_queues) अणु
		dev_info(&pdev->dev, "Creating VQ worker threads (%d)\n",
			 cptvf->nr_queues);
	पूर्ण

	क्रम (i = 0; i < cptvf->nr_queues; i++) अणु
		tasklet_init(&cwqe_info->vq_wqe[i].twork, vq_work_handler,
			     (u64)cwqe_info);
		cwqe_info->vq_wqe[i].qno = i;
		cwqe_info->vq_wqe[i].cptvf = cptvf;
	पूर्ण

	cptvf->wqe_info = cwqe_info;

	वापस 0;
पूर्ण

अटल व्योम cleanup_worker_thपढ़ोs(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा cptvf_wqe_info *cwqe_info;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक i;

	cwqe_info = (काष्ठा cptvf_wqe_info *)cptvf->wqe_info;
	अगर (!cwqe_info)
		वापस;

	अगर (cptvf->nr_queues) अणु
		dev_info(&pdev->dev, "Cleaning VQ worker threads (%u)\n",
			 cptvf->nr_queues);
	पूर्ण

	क्रम (i = 0; i < cptvf->nr_queues; i++)
		tasklet_समाप्त(&cwqe_info->vq_wqe[i].twork);

	kमुक्त_sensitive(cwqe_info);
	cptvf->wqe_info = शून्य;
पूर्ण

अटल व्योम मुक्त_pending_queues(काष्ठा pending_qinfo *pqinfo)
अणु
	पूर्णांक i;
	काष्ठा pending_queue *queue;

	क्रम_each_pending_queue(pqinfo, queue, i) अणु
		अगर (!queue->head)
			जारी;

		/* मुक्त single queue */
		kमुक्त_sensitive((queue->head));

		queue->front = 0;
		queue->rear = 0;

		वापस;
	पूर्ण

	pqinfo->qlen = 0;
	pqinfo->nr_queues = 0;
पूर्ण

अटल पूर्णांक alloc_pending_queues(काष्ठा pending_qinfo *pqinfo, u32 qlen,
				u32 nr_queues)
अणु
	u32 i;
	माप_प्रकार size;
	पूर्णांक ret;
	काष्ठा pending_queue *queue = शून्य;

	pqinfo->nr_queues = nr_queues;
	pqinfo->qlen = qlen;

	size = (qlen * माप(काष्ठा pending_entry));

	क्रम_each_pending_queue(pqinfo, queue, i) अणु
		queue->head = kzalloc((size), GFP_KERNEL);
		अगर (!queue->head) अणु
			ret = -ENOMEM;
			जाओ pending_qfail;
		पूर्ण

		queue->front = 0;
		queue->rear = 0;
		atomic64_set((&queue->pending_count), (0));

		/* init queue spin lock */
		spin_lock_init(&queue->lock);
	पूर्ण

	वापस 0;

pending_qfail:
	मुक्त_pending_queues(pqinfo);

	वापस ret;
पूर्ण

अटल पूर्णांक init_pending_queues(काष्ठा cpt_vf *cptvf, u32 qlen, u32 nr_queues)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक ret;

	अगर (!nr_queues)
		वापस 0;

	ret = alloc_pending_queues(&cptvf->pqinfo, qlen, nr_queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup pending queues (%u)\n",
			nr_queues);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cleanup_pending_queues(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!cptvf->nr_queues)
		वापस;

	dev_info(&pdev->dev, "Cleaning VQ pending queue (%u)\n",
		 cptvf->nr_queues);
	मुक्त_pending_queues(&cptvf->pqinfo);
पूर्ण

अटल व्योम मुक्त_command_queues(काष्ठा cpt_vf *cptvf,
				काष्ठा command_qinfo *cqinfo)
अणु
	पूर्णांक i;
	काष्ठा command_queue *queue = शून्य;
	काष्ठा command_chunk *chunk = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा hlist_node *node;

	/* clean up क्रम each queue */
	क्रम (i = 0; i < cptvf->nr_queues; i++) अणु
		queue = &cqinfo->queue[i];
		अगर (hlist_empty(&cqinfo->queue[i].chead))
			जारी;

		hlist_क्रम_each_entry_safe(chunk, node, &cqinfo->queue[i].chead,
					  nextchunk) अणु
			dma_मुक्त_coherent(&pdev->dev, chunk->size,
					  chunk->head,
					  chunk->dma_addr);
			chunk->head = शून्य;
			chunk->dma_addr = 0;
			hlist_del(&chunk->nextchunk);
			kमुक्त_sensitive(chunk);
		पूर्ण

		queue->nchunks = 0;
		queue->idx = 0;
	पूर्ण

	/* common cleanup */
	cqinfo->cmd_size = 0;
पूर्ण

अटल पूर्णांक alloc_command_queues(काष्ठा cpt_vf *cptvf,
				काष्ठा command_qinfo *cqinfo, माप_प्रकार cmd_size,
				u32 qlen)
अणु
	पूर्णांक i;
	माप_प्रकार q_size;
	काष्ठा command_queue *queue = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;

	/* common init */
	cqinfo->cmd_size = cmd_size;
	/* Qsize in dwords, needed क्रम SADDR config, 1-next chunk poपूर्णांकer */
	cptvf->qsize = min(qlen, cqinfo->qchunksize) *
			CPT_NEXT_CHUNK_PTR_SIZE + 1;
	/* Qsize in bytes to create space क्रम alignment */
	q_size = qlen * cqinfo->cmd_size;

	/* per queue initialization */
	क्रम (i = 0; i < cptvf->nr_queues; i++) अणु
		माप_प्रकार c_size = 0;
		माप_प्रकार rem_q_size = q_size;
		काष्ठा command_chunk *curr = शून्य, *first = शून्य, *last = शून्य;
		u32 qcsize_bytes = cqinfo->qchunksize * cqinfo->cmd_size;

		queue = &cqinfo->queue[i];
		INIT_HLIST_HEAD(&cqinfo->queue[i].chead);
		करो अणु
			curr = kzalloc(माप(*curr), GFP_KERNEL);
			अगर (!curr)
				जाओ cmd_qfail;

			c_size = (rem_q_size > qcsize_bytes) ? qcsize_bytes :
					rem_q_size;
			curr->head = dma_alloc_coherent(&pdev->dev,
							c_size + CPT_NEXT_CHUNK_PTR_SIZE,
							&curr->dma_addr,
							GFP_KERNEL);
			अगर (!curr->head) अणु
				dev_err(&pdev->dev, "Command Q (%d) chunk (%d) allocation failed\n",
					i, queue->nchunks);
				kमुक्त(curr);
				जाओ cmd_qfail;
			पूर्ण

			curr->size = c_size;
			अगर (queue->nchunks == 0) अणु
				hlist_add_head(&curr->nextchunk,
					       &cqinfo->queue[i].chead);
				first = curr;
			पूर्ण अन्यथा अणु
				hlist_add_behind(&curr->nextchunk,
						 &last->nextchunk);
			पूर्ण

			queue->nchunks++;
			rem_q_size -= c_size;
			अगर (last)
				*((u64 *)(&last->head[last->size])) = (u64)curr->dma_addr;

			last = curr;
		पूर्ण जबतक (rem_q_size);

		/* Make the queue circular */
		/* Tie back last chunk entry to head */
		curr = first;
		*((u64 *)(&last->head[last->size])) = (u64)curr->dma_addr;
		queue->qhead = curr;
		spin_lock_init(&queue->lock);
	पूर्ण
	वापस 0;

cmd_qfail:
	मुक्त_command_queues(cptvf, cqinfo);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक init_command_queues(काष्ठा cpt_vf *cptvf, u32 qlen)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक ret;

	/* setup AE command queues */
	ret = alloc_command_queues(cptvf, &cptvf->cqinfo, CPT_INST_SIZE,
				   qlen);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to allocate AE command queues (%u)\n",
			cptvf->nr_queues);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cleanup_command_queues(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!cptvf->nr_queues)
		वापस;

	dev_info(&pdev->dev, "Cleaning VQ command queue (%u)\n",
		 cptvf->nr_queues);
	मुक्त_command_queues(cptvf, &cptvf->cqinfo);
पूर्ण

अटल व्योम cptvf_sw_cleanup(काष्ठा cpt_vf *cptvf)
अणु
	cleanup_worker_thपढ़ोs(cptvf);
	cleanup_pending_queues(cptvf);
	cleanup_command_queues(cptvf);
पूर्ण

अटल पूर्णांक cptvf_sw_init(काष्ठा cpt_vf *cptvf, u32 qlen, u32 nr_queues)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक ret = 0;
	u32 max_dev_queues = 0;

	max_dev_queues = CPT_NUM_QS_PER_VF;
	/* possible cpus */
	nr_queues = min_t(u32, nr_queues, max_dev_queues);
	cptvf->nr_queues = nr_queues;

	ret = init_command_queues(cptvf, qlen);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup command queues (%u)\n",
			nr_queues);
		वापस ret;
	पूर्ण

	ret = init_pending_queues(cptvf, qlen, nr_queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup pending queues (%u)\n",
			nr_queues);
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

अटल व्योम cptvf_मुक्त_irq_affinity(काष्ठा cpt_vf *cptvf, पूर्णांक vec)
अणु
	irq_set_affinity_hपूर्णांक(pci_irq_vector(cptvf->pdev, vec), शून्य);
	मुक्त_cpumask_var(cptvf->affinity_mask[vec]);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_ctl(काष्ठा cpt_vf *cptvf, bool val)
अणु
	जोड़ cptx_vqx_ctl vqx_ctl;

	vqx_ctl.u = cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VQX_CTL(0, 0));
	vqx_ctl.s.ena = val;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_CTL(0, 0), vqx_ctl.u);
पूर्ण

व्योम cptvf_ग_लिखो_vq_करोorbell(काष्ठा cpt_vf *cptvf, u32 val)
अणु
	जोड़ cptx_vqx_करोorbell vqx_dbell;

	vqx_dbell.u = cpt_पढ़ो_csr64(cptvf->reg_base,
				     CPTX_VQX_DOORBELL(0, 0));
	vqx_dbell.s.dbell_cnt = val * 8; /* Num of Inकाष्ठाions * 8 words */
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_DOORBELL(0, 0),
			vqx_dbell.u);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_inprog(काष्ठा cpt_vf *cptvf, u8 val)
अणु
	जोड़ cptx_vqx_inprog vqx_inprg;

	vqx_inprg.u = cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VQX_INPROG(0, 0));
	vqx_inprg.s.inflight = val;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_INPROG(0, 0), vqx_inprg.u);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_करोne_numरुको(काष्ठा cpt_vf *cptvf, u32 val)
अणु
	जोड़ cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = cpt_पढ़ो_csr64(cptvf->reg_base,
				     CPTX_VQX_DONE_WAIT(0, 0));
	vqx_dरुको.s.num_रुको = val;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_DONE_WAIT(0, 0),
			vqx_dरुको.u);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_करोne_समयरुको(काष्ठा cpt_vf *cptvf, u16 समय)
अणु
	जोड़ cptx_vqx_करोne_रुको vqx_dरुको;

	vqx_dरुको.u = cpt_पढ़ो_csr64(cptvf->reg_base,
				     CPTX_VQX_DONE_WAIT(0, 0));
	vqx_dरुको.s.समय_रुको = समय;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_DONE_WAIT(0, 0),
			vqx_dरुको.u);
पूर्ण

अटल व्योम cptvf_enable_swerr_पूर्णांकerrupts(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_ENA_W1S(0, 0));
	/* Set mbox(0) पूर्णांकerupts क्रम the requested vf */
	vqx_misc_ena.s.swerr = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_ENA_W1S(0, 0),
			vqx_misc_ena.u);
पूर्ण

अटल व्योम cptvf_enable_mbox_पूर्णांकerrupts(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_ENA_W1S(0, 0));
	/* Set mbox(0) पूर्णांकerupts क्रम the requested vf */
	vqx_misc_ena.s.mbox = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_ENA_W1S(0, 0),
			vqx_misc_ena.u);
पूर्ण

अटल व्योम cptvf_enable_करोne_पूर्णांकerrupts(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_करोne_ena_w1s vqx_करोne_ena;

	vqx_करोne_ena.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_DONE_ENA_W1S(0, 0));
	/* Set DONE पूर्णांकerrupt क्रम the requested vf */
	vqx_करोne_ena.s.करोne = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_DONE_ENA_W1S(0, 0),
			vqx_करोne_ena.u);
पूर्ण

अटल व्योम cptvf_clear_करोvf_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.करोvf = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_पूर्णांक.u);
पूर्ण

अटल व्योम cptvf_clear_irde_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.irde = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_पूर्णांक.u);
पूर्ण

अटल व्योम cptvf_clear_nwrp_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.nwrp = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base,
			CPTX_VQX_MISC_INT(0, 0), vqx_misc_पूर्णांक.u);
पूर्ण

अटल व्योम cptvf_clear_mbox_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.mbox = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_पूर्णांक.u);
पूर्ण

अटल व्योम cptvf_clear_swerr_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_misc_पूर्णांक vqx_misc_पूर्णांक;

	vqx_misc_पूर्णांक.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C क्रम the VF */
	vqx_misc_पूर्णांक.s.swerr = 1;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_पूर्णांक.u);
पूर्ण

अटल u64 cptvf_पढ़ो_vf_misc_पूर्णांकr_status(काष्ठा cpt_vf *cptvf)
अणु
	वापस cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0));
पूर्ण

अटल irqवापस_t cptvf_misc_पूर्णांकr_handler(पूर्णांक irq, व्योम *cptvf_irq)
अणु
	काष्ठा cpt_vf *cptvf = (काष्ठा cpt_vf *)cptvf_irq;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	u64 पूर्णांकr;

	पूर्णांकr = cptvf_पढ़ो_vf_misc_पूर्णांकr_status(cptvf);
	/*Check क्रम MISC पूर्णांकerrupt types*/
	अगर (likely(पूर्णांकr & CPT_VF_INTR_MBOX_MASK)) अणु
		dev_dbg(&pdev->dev, "Mailbox interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
		cptvf_handle_mbox_पूर्णांकr(cptvf);
		cptvf_clear_mbox_पूर्णांकr(cptvf);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & CPT_VF_INTR_DOVF_MASK)) अणु
		cptvf_clear_करोvf_पूर्णांकr(cptvf);
		/*Clear करोorbell count*/
		cptvf_ग_लिखो_vq_करोorbell(cptvf, 0);
		dev_err(&pdev->dev, "Doorbell overflow error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & CPT_VF_INTR_IRDE_MASK)) अणु
		cptvf_clear_irde_पूर्णांकr(cptvf);
		dev_err(&pdev->dev, "Instruction NCB read error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & CPT_VF_INTR_NWRP_MASK)) अणु
		cptvf_clear_nwrp_पूर्णांकr(cptvf);
		dev_err(&pdev->dev, "NCB response write error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अगर (unlikely(पूर्णांकr & CPT_VF_INTR_SERR_MASK)) अणु
		cptvf_clear_swerr_पूर्णांकr(cptvf);
		dev_err(&pdev->dev, "Software error interrupt 0x%llx on CPT VF %d\n",
			पूर्णांकr, cptvf->vfid);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Unhandled interrupt in CPT VF %d\n",
			cptvf->vfid);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा cptvf_wqe *get_cptvf_vq_wqe(काष्ठा cpt_vf *cptvf,
						 पूर्णांक qno)
अणु
	काष्ठा cptvf_wqe_info *nwqe_info;

	अगर (unlikely(qno >= cptvf->nr_queues))
		वापस शून्य;
	nwqe_info = (काष्ठा cptvf_wqe_info *)cptvf->wqe_info;

	वापस &nwqe_info->vq_wqe[qno];
पूर्ण

अटल अंतरभूत u32 cptvf_पढ़ो_vq_करोne_count(काष्ठा cpt_vf *cptvf)
अणु
	जोड़ cptx_vqx_करोne vqx_करोne;

	vqx_करोne.u = cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VQX_DONE(0, 0));
	वापस vqx_करोne.s.करोne;
पूर्ण

अटल अंतरभूत व्योम cptvf_ग_लिखो_vq_करोne_ack(काष्ठा cpt_vf *cptvf,
					   u32 ackcnt)
अणु
	जोड़ cptx_vqx_करोne_ack vqx_dack_cnt;

	vqx_dack_cnt.u = cpt_पढ़ो_csr64(cptvf->reg_base,
					CPTX_VQX_DONE_ACK(0, 0));
	vqx_dack_cnt.s.करोne_ack = ackcnt;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_DONE_ACK(0, 0),
			vqx_dack_cnt.u);
पूर्ण

अटल irqवापस_t cptvf_करोne_पूर्णांकr_handler(पूर्णांक irq, व्योम *cptvf_irq)
अणु
	काष्ठा cpt_vf *cptvf = (काष्ठा cpt_vf *)cptvf_irq;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	/* Read the number of completions */
	u32 पूर्णांकr = cptvf_पढ़ो_vq_करोne_count(cptvf);

	अगर (पूर्णांकr) अणु
		काष्ठा cptvf_wqe *wqe;

		/* Acknowledge the number of
		 * scheduled completions क्रम processing
		 */
		cptvf_ग_लिखो_vq_करोne_ack(cptvf, पूर्णांकr);
		wqe = get_cptvf_vq_wqe(cptvf, 0);
		अगर (unlikely(!wqe)) अणु
			dev_err(&pdev->dev, "No work to schedule for VF (%d)",
				cptvf->vfid);
			वापस IRQ_NONE;
		पूर्ण
		tasklet_hi_schedule(&wqe->twork);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cptvf_set_irq_affinity(काष्ठा cpt_vf *cptvf, पूर्णांक vec)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	पूर्णांक cpu;

	अगर (!zalloc_cpumask_var(&cptvf->affinity_mask[vec],
				GFP_KERNEL)) अणु
		dev_err(&pdev->dev, "Allocation failed for affinity_mask for VF %d",
			cptvf->vfid);
		वापस;
	पूर्ण

	cpu = cptvf->vfid % num_online_cpus();
	cpumask_set_cpu(cpumask_local_spपढ़ो(cpu, cptvf->node),
			cptvf->affinity_mask[vec]);
	irq_set_affinity_hपूर्णांक(pci_irq_vector(pdev, vec),
			cptvf->affinity_mask[vec]);
पूर्ण

अटल व्योम cptvf_ग_लिखो_vq_saddr(काष्ठा cpt_vf *cptvf, u64 val)
अणु
	जोड़ cptx_vqx_saddr vqx_saddr;

	vqx_saddr.u = val;
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VQX_SADDR(0, 0), vqx_saddr.u);
पूर्ण

अटल व्योम cptvf_device_init(काष्ठा cpt_vf *cptvf)
अणु
	u64 base_addr = 0;

	/* Disable the VQ */
	cptvf_ग_लिखो_vq_ctl(cptvf, 0);
	/* Reset the करोorbell */
	cptvf_ग_लिखो_vq_करोorbell(cptvf, 0);
	/* Clear inflight */
	cptvf_ग_लिखो_vq_inprog(cptvf, 0);
	/* Write VQ SADDR */
	/* TODO: क्रम now only one queue, so hard coded */
	base_addr = (u64)(cptvf->cqinfo.queue[0].qhead->dma_addr);
	cptvf_ग_लिखो_vq_saddr(cptvf, base_addr);
	/* Configure समयrhold / coalescence */
	cptvf_ग_लिखो_vq_करोne_समयरुको(cptvf, CPT_TIMER_THOLD);
	cptvf_ग_लिखो_vq_करोne_numरुको(cptvf, 1);
	/* Enable the VQ */
	cptvf_ग_लिखो_vq_ctl(cptvf, 1);
	/* Flag the VF पढ़ोy */
	cptvf->flags |= CPT_FLAG_DEVICE_READY;
पूर्ण

अटल पूर्णांक cptvf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cpt_vf *cptvf;
	पूर्णांक    err;

	cptvf = devm_kzalloc(dev, माप(*cptvf), GFP_KERNEL);
	अगर (!cptvf)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, cptvf);
	cptvf->pdev = pdev;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, शून्य);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ cptvf_err_disable_device;
	पूर्ण
	/* Mark as VF driver */
	cptvf->flags |= CPT_FLAG_VF_DRIVER;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable 48-bit DMA configuration\n");
		जाओ cptvf_err_release_regions;
	पूर्ण

	/* MAP PF's configuration रेजिस्टरs */
	cptvf->reg_base = pcim_iomap(pdev, 0, 0);
	अगर (!cptvf->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ cptvf_err_release_regions;
	पूर्ण

	cptvf->node = dev_to_node(&pdev->dev);
	err = pci_alloc_irq_vectors(pdev, CPT_VF_MSIX_VECTORS,
			CPT_VF_MSIX_VECTORS, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(dev, "Request for #%d msix vectors failed\n",
			CPT_VF_MSIX_VECTORS);
		जाओ cptvf_err_release_regions;
	पूर्ण

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC),
			  cptvf_misc_पूर्णांकr_handler, 0, "CPT VF misc intr",
			  cptvf);
	अगर (err) अणु
		dev_err(dev, "Request misc irq failed");
		जाओ cptvf_मुक्त_vectors;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt */
	cptvf_enable_mbox_पूर्णांकerrupts(cptvf);
	cptvf_enable_swerr_पूर्णांकerrupts(cptvf);

	/* Check पढ़ोy with PF */
	/* Gets chip ID / device Id from PF अगर पढ़ोy */
	err = cptvf_check_pf_पढ़ोy(cptvf);
	अगर (err) अणु
		dev_err(dev, "PF not responding to READY msg");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण

	/* CPT VF software resources initialization */
	cptvf->cqinfo.qchunksize = CPT_CMD_QCHUNK_SIZE;
	err = cptvf_sw_init(cptvf, CPT_CMD_QLEN, CPT_NUM_QS_PER_VF);
	अगर (err) अणु
		dev_err(dev, "cptvf_sw_init() failed");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण
	/* Convey VQ LEN to PF */
	err = cptvf_send_vq_size_msg(cptvf);
	अगर (err) अणु
		dev_err(dev, "PF not responding to QLEN msg");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण

	/* CPT VF device initialization */
	cptvf_device_init(cptvf);
	/* Send msg to PF to assign currnet Q to required group */
	cptvf->vfgrp = 1;
	err = cptvf_send_vf_to_grp_msg(cptvf);
	अगर (err) अणु
		dev_err(dev, "PF not responding to VF_GRP msg");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण

	cptvf->priority = 1;
	err = cptvf_send_vf_priority_msg(cptvf);
	अगर (err) अणु
		dev_err(dev, "PF not responding to VF_PRIO msg");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE),
			  cptvf_करोne_पूर्णांकr_handler, 0, "CPT VF done intr",
			  cptvf);
	अगर (err) अणु
		dev_err(dev, "Request done irq failed\n");
		जाओ cptvf_मुक्त_misc_irq;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt */
	cptvf_enable_करोne_पूर्णांकerrupts(cptvf);

	/* Set irq affinity masks */
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);

	err = cptvf_send_vf_up(cptvf);
	अगर (err) अणु
		dev_err(dev, "PF not responding to UP msg");
		जाओ cptvf_मुक्त_irq_affinity;
	पूर्ण
	err = cvm_crypto_init(cptvf);
	अगर (err) अणु
		dev_err(dev, "Algorithm register failed\n");
		जाओ cptvf_मुक्त_irq_affinity;
	पूर्ण
	वापस 0;

cptvf_मुक्त_irq_affinity:
	cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
	cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
cptvf_मुक्त_misc_irq:
	मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
cptvf_मुक्त_vectors:
	pci_मुक्त_irq_vectors(cptvf->pdev);
cptvf_err_release_regions:
	pci_release_regions(pdev);
cptvf_err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);

	वापस err;
पूर्ण

अटल व्योम cptvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cpt_vf *cptvf = pci_get_drvdata(pdev);

	अगर (!cptvf) अणु
		dev_err(&pdev->dev, "Invalid CPT-VF device\n");
		वापस;
	पूर्ण

	/* Convey DOWN to PF */
	अगर (cptvf_send_vf_करोwn(cptvf)) अणु
		dev_err(&pdev->dev, "PF not responding to DOWN msg");
	पूर्ण अन्यथा अणु
		cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
		cptvf_मुक्त_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
		मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE), cptvf);
		मुक्त_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
		pci_मुक्त_irq_vectors(cptvf->pdev);
		cptvf_sw_cleanup(cptvf);
		pci_set_drvdata(pdev, शून्य);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		cvm_crypto_निकास();
	पूर्ण
पूर्ण

अटल व्योम cptvf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	cptvf_हटाओ(pdev);
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id cptvf_id_table[] = अणु
	अणुPCI_VDEVICE(CAVIUM, CPT_81XX_PCI_VF_DEVICE_ID), 0पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver cptvf_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = cptvf_id_table,
	.probe = cptvf_probe,
	.हटाओ = cptvf_हटाओ,
	.shutकरोwn = cptvf_shutकरोwn,
पूर्ण;

module_pci_driver(cptvf_pci_driver);

MODULE_AUTHOR("George Cherian <george.cherian@cavium.com>");
MODULE_DESCRIPTION("Cavium Thunder CPT Virtual Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, cptvf_id_table);
