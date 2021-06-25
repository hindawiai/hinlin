<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश "cptvf.h"
#समावेश "cptvf_algs.h"
#समावेश "request_manager.h"

/**
 * get_मुक्त_pending_entry - get मुक्त entry from pending queue
 * @param pqinfo: pending_qinfo काष्ठाure
 * @param qno: queue number
 */
अटल काष्ठा pending_entry *get_मुक्त_pending_entry(काष्ठा pending_queue *q,
						    पूर्णांक qlen)
अणु
	काष्ठा pending_entry *ent = शून्य;

	ent = &q->head[q->rear];
	अगर (unlikely(ent->busy)) अणु
		ent = शून्य;
		जाओ no_मुक्त_entry;
	पूर्ण

	q->rear++;
	अगर (unlikely(q->rear == qlen))
		q->rear = 0;

no_मुक्त_entry:
	वापस ent;
पूर्ण

अटल अंतरभूत व्योम pending_queue_inc_front(काष्ठा pending_qinfo *pqinfo,
					   पूर्णांक qno)
अणु
	काष्ठा pending_queue *queue = &pqinfo->queue[qno];

	queue->front++;
	अगर (unlikely(queue->front == pqinfo->qlen))
		queue->front = 0;
पूर्ण

अटल पूर्णांक setup_sgio_components(काष्ठा cpt_vf *cptvf, काष्ठा buf_ptr *list,
				 पूर्णांक buf_count, u8 *buffer)
अणु
	पूर्णांक ret = 0, i, j;
	पूर्णांक components;
	काष्ठा sglist_component *sg_ptr = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (unlikely(!list)) अणु
		dev_err(&pdev->dev, "Input List pointer is NULL\n");
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < buf_count; i++) अणु
		अगर (likely(list[i].vptr)) अणु
			list[i].dma_addr = dma_map_single(&pdev->dev,
							  list[i].vptr,
							  list[i].size,
							  DMA_BIसूचीECTIONAL);
			अगर (unlikely(dma_mapping_error(&pdev->dev,
						       list[i].dma_addr))) अणु
				dev_err(&pdev->dev, "DMA map kernel buffer failed for component: %d\n",
					i);
				ret = -EIO;
				जाओ sg_cleanup;
			पूर्ण
		पूर्ण
	पूर्ण

	components = buf_count / 4;
	sg_ptr = (काष्ठा sglist_component *)buffer;
	क्रम (i = 0; i < components; i++) अणु
		sg_ptr->u.s.len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->u.s.len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->u.s.len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->u.s.len3 = cpu_to_be16(list[i * 4 + 3].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		sg_ptr->ptr3 = cpu_to_be64(list[i * 4 + 3].dma_addr);
		sg_ptr++;
	पूर्ण

	components = buf_count % 4;

	चयन (components) अणु
	हाल 3:
		sg_ptr->u.s.len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		fallthrough;
	हाल 2:
		sg_ptr->u.s.len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		fallthrough;
	हाल 1:
		sg_ptr->u.s.len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;

sg_cleanup:
	क्रम (j = 0; j < i; j++) अणु
		अगर (list[j].dma_addr) अणु
			dma_unmap_single(&pdev->dev, list[i].dma_addr,
					 list[i].size, DMA_BIसूचीECTIONAL);
		पूर्ण

		list[j].dma_addr = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक setup_sgio_list(काष्ठा cpt_vf *cptvf,
				  काष्ठा cpt_info_buffer *info,
				  काष्ठा cpt_request_info *req)
अणु
	u16 g_sz_bytes = 0, s_sz_bytes = 0;
	पूर्णांक ret = 0;
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (req->incnt > MAX_SG_IN_CNT || req->outcnt > MAX_SG_OUT_CNT) अणु
		dev_err(&pdev->dev, "Request SG components are higher than supported\n");
		ret = -EINVAL;
		जाओ  scatter_gather_clean;
	पूर्ण

	/* Setup gather (input) components */
	g_sz_bytes = ((req->incnt + 3) / 4) * माप(काष्ठा sglist_component);
	info->gather_components = kzalloc(g_sz_bytes, req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (!info->gather_components) अणु
		ret = -ENOMEM;
		जाओ  scatter_gather_clean;
	पूर्ण

	ret = setup_sgio_components(cptvf, req->in,
				    req->incnt,
				    info->gather_components);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup gather list\n");
		ret = -EFAULT;
		जाओ  scatter_gather_clean;
	पूर्ण

	/* Setup scatter (output) components */
	s_sz_bytes = ((req->outcnt + 3) / 4) * माप(काष्ठा sglist_component);
	info->scatter_components = kzalloc(s_sz_bytes, req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (!info->scatter_components) अणु
		ret = -ENOMEM;
		जाओ  scatter_gather_clean;
	पूर्ण

	ret = setup_sgio_components(cptvf, req->out,
				    req->outcnt,
				    info->scatter_components);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to setup gather list\n");
		ret = -EFAULT;
		जाओ  scatter_gather_clean;
	पूर्ण

	/* Create and initialize DPTR */
	info->dlen = g_sz_bytes + s_sz_bytes + SG_LIST_HDR_SIZE;
	info->in_buffer = kzalloc(info->dlen, req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (!info->in_buffer) अणु
		ret = -ENOMEM;
		जाओ  scatter_gather_clean;
	पूर्ण

	((__be16 *)info->in_buffer)[0] = cpu_to_be16(req->outcnt);
	((__be16 *)info->in_buffer)[1] = cpu_to_be16(req->incnt);
	((__be16 *)info->in_buffer)[2] = 0;
	((__be16 *)info->in_buffer)[3] = 0;

	स_नकल(&info->in_buffer[8], info->gather_components,
	       g_sz_bytes);
	स_नकल(&info->in_buffer[8 + g_sz_bytes],
	       info->scatter_components, s_sz_bytes);

	info->dptr_baddr = dma_map_single(&pdev->dev,
					  (व्योम *)info->in_buffer,
					  info->dlen,
					  DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&pdev->dev, info->dptr_baddr)) अणु
		dev_err(&pdev->dev, "Mapping DPTR Failed %d\n", info->dlen);
		ret = -EIO;
		जाओ  scatter_gather_clean;
	पूर्ण

	/* Create and initialize RPTR */
	info->out_buffer = kzalloc(COMPLETION_CODE_SIZE, req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (!info->out_buffer) अणु
		ret = -ENOMEM;
		जाओ scatter_gather_clean;
	पूर्ण

	*((u64 *)info->out_buffer) = ~((u64)COMPLETION_CODE_INIT);
	info->alternate_caddr = (u64 *)info->out_buffer;
	info->rptr_baddr = dma_map_single(&pdev->dev,
					  (व्योम *)info->out_buffer,
					  COMPLETION_CODE_SIZE,
					  DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&pdev->dev, info->rptr_baddr)) अणु
		dev_err(&pdev->dev, "Mapping RPTR Failed %d\n",
			COMPLETION_CODE_SIZE);
		ret = -EIO;
		जाओ  scatter_gather_clean;
	पूर्ण

	वापस 0;

scatter_gather_clean:
	वापस ret;
पूर्ण

अटल पूर्णांक send_cpt_command(काष्ठा cpt_vf *cptvf, जोड़ cpt_inst_s *cmd,
		     u32 qno)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा command_qinfo *qinfo = शून्य;
	काष्ठा command_queue *queue;
	काष्ठा command_chunk *chunk;
	u8 *ent;
	पूर्णांक ret = 0;

	अगर (unlikely(qno >= cptvf->nr_queues)) अणु
		dev_err(&pdev->dev, "Invalid queue (qno: %d, nr_queues: %d)\n",
			qno, cptvf->nr_queues);
		वापस -EINVAL;
	पूर्ण

	qinfo = &cptvf->cqinfo;
	queue = &qinfo->queue[qno];
	/* lock commad queue */
	spin_lock(&queue->lock);
	ent = &queue->qhead->head[queue->idx * qinfo->cmd_size];
	स_नकल(ent, (व्योम *)cmd, qinfo->cmd_size);

	अगर (++queue->idx >= queue->qhead->size / 64) अणु
		काष्ठा hlist_node *node;

		hlist_क्रम_each(node, &queue->chead) अणु
			chunk = hlist_entry(node, काष्ठा command_chunk,
					    nextchunk);
			अगर (chunk == queue->qhead) अणु
				जारी;
			पूर्ण अन्यथा अणु
				queue->qhead = chunk;
				अवरोध;
			पूर्ण
		पूर्ण
		queue->idx = 0;
	पूर्ण
	/* make sure all memory stores are करोne beक्रमe ringing करोorbell */
	smp_wmb();
	cptvf_ग_लिखो_vq_करोorbell(cptvf, 1);
	/* unlock command queue */
	spin_unlock(&queue->lock);

	वापस ret;
पूर्ण

अटल व्योम करो_request_cleanup(काष्ठा cpt_vf *cptvf,
			काष्ठा cpt_info_buffer *info)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_request_info *req;

	अगर (info->dptr_baddr)
		dma_unmap_single(&pdev->dev, info->dptr_baddr,
				 info->dlen, DMA_BIसूचीECTIONAL);

	अगर (info->rptr_baddr)
		dma_unmap_single(&pdev->dev, info->rptr_baddr,
				 COMPLETION_CODE_SIZE, DMA_BIसूचीECTIONAL);

	अगर (info->comp_baddr)
		dma_unmap_single(&pdev->dev, info->comp_baddr,
				 माप(जोड़ cpt_res_s), DMA_BIसूचीECTIONAL);

	अगर (info->req) अणु
		req = info->req;
		क्रम (i = 0; i < req->outcnt; i++) अणु
			अगर (req->out[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->out[i].dma_addr,
						 req->out[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण

		क्रम (i = 0; i < req->incnt; i++) अणु
			अगर (req->in[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->in[i].dma_addr,
						 req->in[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण
	पूर्ण

	kमुक्त_sensitive(info->scatter_components);
	kमुक्त_sensitive(info->gather_components);
	kमुक्त_sensitive(info->out_buffer);
	kमुक्त_sensitive(info->in_buffer);
	kमुक्त_sensitive((व्योम *)info->completion_addr);
	kमुक्त_sensitive(info);
पूर्ण

अटल व्योम करो_post_process(काष्ठा cpt_vf *cptvf, काष्ठा cpt_info_buffer *info)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!info) अणु
		dev_err(&pdev->dev, "incorrect cpt_info_buffer for post processing\n");
		वापस;
	पूर्ण

	करो_request_cleanup(cptvf, info);
पूर्ण

अटल अंतरभूत व्योम process_pending_queue(काष्ठा cpt_vf *cptvf,
					 काष्ठा pending_qinfo *pqinfo,
					 पूर्णांक qno)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा pending_queue *pqueue = &pqinfo->queue[qno];
	काष्ठा pending_entry *pentry = शून्य;
	काष्ठा cpt_info_buffer *info = शून्य;
	जोड़ cpt_res_s *status = शून्य;
	अचिन्हित अक्षर ccode;

	जबतक (1) अणु
		spin_lock_bh(&pqueue->lock);
		pentry = &pqueue->head[pqueue->front];
		अगर (unlikely(!pentry->busy)) अणु
			spin_unlock_bh(&pqueue->lock);
			अवरोध;
		पूर्ण

		info = (काष्ठा cpt_info_buffer *)pentry->post_arg;
		अगर (unlikely(!info)) अणु
			dev_err(&pdev->dev, "Pending Entry post arg NULL\n");
			pending_queue_inc_front(pqinfo, qno);
			spin_unlock_bh(&pqueue->lock);
			जारी;
		पूर्ण

		status = (जोड़ cpt_res_s *)pentry->completion_addr;
		ccode = status->s.compcode;
		अगर ((status->s.compcode == CPT_COMP_E_FAULT) ||
		    (status->s.compcode == CPT_COMP_E_SWERR)) अणु
			dev_err(&pdev->dev, "Request failed with %s\n",
				(status->s.compcode == CPT_COMP_E_FAULT) ?
				"DMA Fault" : "Software error");
			pentry->completion_addr = शून्य;
			pentry->busy = false;
			atomic64_dec((&pqueue->pending_count));
			pentry->post_arg = शून्य;
			pending_queue_inc_front(pqinfo, qno);
			करो_request_cleanup(cptvf, info);
			spin_unlock_bh(&pqueue->lock);
			अवरोध;
		पूर्ण अन्यथा अगर (status->s.compcode == COMPLETION_CODE_INIT) अणु
			/* check क्रम समयout */
			अगर (समय_after_eq(jअगरfies,
					  (info->समय_in +
					  (CPT_COMMAND_TIMEOUT * HZ)))) अणु
				dev_err(&pdev->dev, "Request timed out");
				pentry->completion_addr = शून्य;
				pentry->busy = false;
				atomic64_dec((&pqueue->pending_count));
				pentry->post_arg = शून्य;
				pending_queue_inc_front(pqinfo, qno);
				करो_request_cleanup(cptvf, info);
				spin_unlock_bh(&pqueue->lock);
				अवरोध;
			पूर्ण अन्यथा अगर ((*info->alternate_caddr ==
				(~COMPLETION_CODE_INIT)) &&
				(info->extra_समय < TIME_IN_RESET_COUNT)) अणु
				info->समय_in = jअगरfies;
				info->extra_समय++;
				spin_unlock_bh(&pqueue->lock);
				अवरोध;
			पूर्ण
		पूर्ण

		pentry->completion_addr = शून्य;
		pentry->busy = false;
		pentry->post_arg = शून्य;
		atomic64_dec((&pqueue->pending_count));
		pending_queue_inc_front(pqinfo, qno);
		spin_unlock_bh(&pqueue->lock);

		करो_post_process(info->cptvf, info);
		/*
		 * Calling callback after we find
		 * that the request has been serviced
		 */
		pentry->callback(ccode, pentry->callback_arg);
	पूर्ण
पूर्ण

पूर्णांक process_request(काष्ठा cpt_vf *cptvf, काष्ठा cpt_request_info *req)
अणु
	पूर्णांक ret = 0, clear = 0, queue = 0;
	काष्ठा cpt_info_buffer *info = शून्य;
	काष्ठा cptvf_request *cpt_req = शून्य;
	जोड़ ctrl_info *ctrl = शून्य;
	जोड़ cpt_res_s *result = शून्य;
	काष्ठा pending_entry *pentry = शून्य;
	काष्ठा pending_queue *pqueue = शून्य;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	u8 group = 0;
	काष्ठा cpt_vq_command vq_cmd;
	जोड़ cpt_inst_s cptinst;

	info = kzalloc(माप(*info), req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (unlikely(!info)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for info_buffer\n");
		वापस -ENOMEM;
	पूर्ण

	cpt_req = (काष्ठा cptvf_request *)&req->req;
	ctrl = (जोड़ ctrl_info *)&req->ctrl;

	info->cptvf = cptvf;
	group = ctrl->s.grp;
	ret = setup_sgio_list(cptvf, info, req);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Setting up SG list failed");
		जाओ request_cleanup;
	पूर्ण

	cpt_req->dlen = info->dlen;
	/*
	 * Get buffer क्रम जोड़ cpt_res_s response
	 * काष्ठाure and its physical address
	 */
	info->completion_addr = kzalloc(माप(जोड़ cpt_res_s), req->may_sleep ? GFP_KERNEL : GFP_ATOMIC);
	अगर (unlikely(!info->completion_addr)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for completion_addr\n");
		ret = -ENOMEM;
		जाओ request_cleanup;
	पूर्ण

	result = (जोड़ cpt_res_s *)info->completion_addr;
	result->s.compcode = COMPLETION_CODE_INIT;
	info->comp_baddr = dma_map_single(&pdev->dev,
					       (व्योम *)info->completion_addr,
					       माप(जोड़ cpt_res_s),
					       DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&pdev->dev, info->comp_baddr)) अणु
		dev_err(&pdev->dev, "mapping compptr Failed %lu\n",
			माप(जोड़ cpt_res_s));
		ret = -EFAULT;
		जाओ  request_cleanup;
	पूर्ण

	/* Fill the VQ command */
	vq_cmd.cmd.u64 = 0;
	vq_cmd.cmd.s.opcode = cpu_to_be16(cpt_req->opcode.flags);
	vq_cmd.cmd.s.param1 = cpu_to_be16(cpt_req->param1);
	vq_cmd.cmd.s.param2 = cpu_to_be16(cpt_req->param2);
	vq_cmd.cmd.s.dlen   = cpu_to_be16(cpt_req->dlen);

	vq_cmd.dptr = info->dptr_baddr;
	vq_cmd.rptr = info->rptr_baddr;
	vq_cmd.cptr.u64 = 0;
	vq_cmd.cptr.s.grp = group;
	/* Get Pending Entry to submit command */
	/* Always queue 0, because 1 queue per VF */
	queue = 0;
	pqueue = &cptvf->pqinfo.queue[queue];

	अगर (atomic64_पढ़ो(&pqueue->pending_count) > PENDING_THOLD) अणु
		dev_err(&pdev->dev, "pending threshold reached\n");
		process_pending_queue(cptvf, &cptvf->pqinfo, queue);
	पूर्ण

get_pending_entry:
	spin_lock_bh(&pqueue->lock);
	pentry = get_मुक्त_pending_entry(pqueue, cptvf->pqinfo.qlen);
	अगर (unlikely(!pentry)) अणु
		spin_unlock_bh(&pqueue->lock);
		अगर (clear == 0) अणु
			process_pending_queue(cptvf, &cptvf->pqinfo, queue);
			clear = 1;
			जाओ get_pending_entry;
		पूर्ण
		dev_err(&pdev->dev, "Get free entry failed\n");
		dev_err(&pdev->dev, "queue: %d, rear: %d, front: %d\n",
			queue, pqueue->rear, pqueue->front);
		ret = -EFAULT;
		जाओ request_cleanup;
	पूर्ण

	pentry->completion_addr = info->completion_addr;
	pentry->post_arg = (व्योम *)info;
	pentry->callback = req->callback;
	pentry->callback_arg = req->callback_arg;
	info->pentry = pentry;
	pentry->busy = true;
	atomic64_inc(&pqueue->pending_count);

	/* Send CPT command */
	info->pentry = pentry;
	info->समय_in = jअगरfies;
	info->req = req;

	/* Create the CPT_INST_S type command क्रम HW पूर्णांकrepretation */
	cptinst.s.करोneपूर्णांक = true;
	cptinst.s.res_addr = (u64)info->comp_baddr;
	cptinst.s.tag = 0;
	cptinst.s.grp = 0;
	cptinst.s.wq_ptr = 0;
	cptinst.s.ei0 = vq_cmd.cmd.u64;
	cptinst.s.ei1 = vq_cmd.dptr;
	cptinst.s.ei2 = vq_cmd.rptr;
	cptinst.s.ei3 = vq_cmd.cptr.u64;

	ret = send_cpt_command(cptvf, &cptinst, queue);
	spin_unlock_bh(&pqueue->lock);
	अगर (unlikely(ret)) अणु
		dev_err(&pdev->dev, "Send command failed for AE\n");
		ret = -EFAULT;
		जाओ request_cleanup;
	पूर्ण

	वापस 0;

request_cleanup:
	dev_dbg(&pdev->dev, "Failed to submit CPT command\n");
	करो_request_cleanup(cptvf, info);

	वापस ret;
पूर्ण

व्योम vq_post_process(काष्ठा cpt_vf *cptvf, u32 qno)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (unlikely(qno > cptvf->nr_queues)) अणु
		dev_err(&pdev->dev, "Request for post processing on invalid pending queue: %u\n",
			qno);
		वापस;
	पूर्ण

	process_pending_queue(cptvf, &cptvf->pqinfo, qno);
पूर्ण

पूर्णांक cptvf_करो_request(व्योम *vfdev, काष्ठा cpt_request_info *req)
अणु
	काष्ठा cpt_vf *cptvf = (काष्ठा cpt_vf *)vfdev;
	काष्ठा pci_dev *pdev = cptvf->pdev;

	अगर (!cpt_device_पढ़ोy(cptvf)) अणु
		dev_err(&pdev->dev, "CPT Device is not ready");
		वापस -ENODEV;
	पूर्ण

	अगर ((cptvf->vftype == SE_TYPES) && (!req->ctrl.s.se_req)) अणु
		dev_err(&pdev->dev, "CPTVF-%d of SE TYPE got AE request",
			cptvf->vfid);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((cptvf->vftype == AE_TYPES) && (req->ctrl.s.se_req)) अणु
		dev_err(&pdev->dev, "CPTVF-%d of AE TYPE got SE request",
			cptvf->vfid);
		वापस -EINVAL;
	पूर्ण

	वापस process_request(cptvf, req);
पूर्ण
