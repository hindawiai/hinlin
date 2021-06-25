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

#समावेश "otx_cptvf.h"
#समावेश "otx_cptvf_algs.h"

/* Completion code size and initial value */
#घोषणा COMPLETION_CODE_SIZE	8
#घोषणा COMPLETION_CODE_INIT	0

/* SG list header size in bytes */
#घोषणा SG_LIST_HDR_SIZE	8

/* Default समयout when रुकोing क्रम मुक्त pending entry in us */
#घोषणा CPT_PENTRY_TIMEOUT	1000
#घोषणा CPT_PENTRY_STEP		50

/* Default threshold क्रम stopping and resuming sender requests */
#घोषणा CPT_IQ_STOP_MARGIN	128
#घोषणा CPT_IQ_RESUME_MARGIN	512

#घोषणा CPT_DMA_ALIGN		128

व्योम otx_cpt_dump_sg_list(काष्ठा pci_dev *pdev, काष्ठा otx_cpt_req_info *req)
अणु
	पूर्णांक i;

	pr_debug("Gather list size %d\n", req->incnt);
	क्रम (i = 0; i < req->incnt; i++) अणु
		pr_debug("Buffer %d size %d, vptr 0x%p, dmaptr 0x%p\n", i,
			 req->in[i].size, req->in[i].vptr,
			 (व्योम *) req->in[i].dma_addr);
		pr_debug("Buffer hexdump (%d bytes)\n",
			 req->in[i].size);
		prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_NONE, 16, 1,
				     req->in[i].vptr, req->in[i].size, false);
	पूर्ण

	pr_debug("Scatter list size %d\n", req->outcnt);
	क्रम (i = 0; i < req->outcnt; i++) अणु
		pr_debug("Buffer %d size %d, vptr 0x%p, dmaptr 0x%p\n", i,
			 req->out[i].size, req->out[i].vptr,
			 (व्योम *) req->out[i].dma_addr);
		pr_debug("Buffer hexdump (%d bytes)\n", req->out[i].size);
		prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_NONE, 16, 1,
				     req->out[i].vptr, req->out[i].size, false);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा otx_cpt_pending_entry *get_मुक्त_pending_entry(
						काष्ठा otx_cpt_pending_queue *q,
						पूर्णांक qlen)
अणु
	काष्ठा otx_cpt_pending_entry *ent = शून्य;

	ent = &q->head[q->rear];
	अगर (unlikely(ent->busy))
		वापस शून्य;

	q->rear++;
	अगर (unlikely(q->rear == qlen))
		q->rear = 0;

	वापस ent;
पूर्ण

अटल अंतरभूत u32 modulo_inc(u32 index, u32 length, u32 inc)
अणु
	अगर (WARN_ON(inc > length))
		inc = length;

	index += inc;
	अगर (unlikely(index >= length))
		index -= length;

	वापस index;
पूर्ण

अटल अंतरभूत व्योम मुक्त_pentry(काष्ठा otx_cpt_pending_entry *pentry)
अणु
	pentry->completion_addr = शून्य;
	pentry->info = शून्य;
	pentry->callback = शून्य;
	pentry->areq = शून्य;
	pentry->resume_sender = false;
	pentry->busy = false;
पूर्ण

अटल अंतरभूत पूर्णांक setup_sgio_components(काष्ठा pci_dev *pdev,
					काष्ठा otx_cpt_buf_ptr *list,
					पूर्णांक buf_count, u8 *buffer)
अणु
	काष्ठा otx_cpt_sglist_component *sg_ptr = शून्य;
	पूर्णांक ret = 0, i, j;
	पूर्णांक components;

	अगर (unlikely(!list)) अणु
		dev_err(&pdev->dev, "Input list pointer is NULL\n");
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
				dev_err(&pdev->dev, "Dma mapping failed\n");
				ret = -EIO;
				जाओ sg_cleanup;
			पूर्ण
		पूर्ण
	पूर्ण

	components = buf_count / 4;
	sg_ptr = (काष्ठा otx_cpt_sglist_component *)buffer;
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

अटल अंतरभूत पूर्णांक setup_sgio_list(काष्ठा pci_dev *pdev,
				  काष्ठा otx_cpt_info_buffer **pinfo,
				  काष्ठा otx_cpt_req_info *req, gfp_t gfp)
अणु
	u32 dlen, align_dlen, info_len, rlen;
	काष्ठा otx_cpt_info_buffer *info;
	u16 g_sz_bytes, s_sz_bytes;
	पूर्णांक align = CPT_DMA_ALIGN;
	u32 total_mem_len;

	अगर (unlikely(req->incnt > OTX_CPT_MAX_SG_IN_CNT ||
		     req->outcnt > OTX_CPT_MAX_SG_OUT_CNT)) अणु
		dev_err(&pdev->dev, "Error too many sg components\n");
		वापस -EINVAL;
	पूर्ण

	g_sz_bytes = ((req->incnt + 3) / 4) *
		      माप(काष्ठा otx_cpt_sglist_component);
	s_sz_bytes = ((req->outcnt + 3) / 4) *
		      माप(काष्ठा otx_cpt_sglist_component);

	dlen = g_sz_bytes + s_sz_bytes + SG_LIST_HDR_SIZE;
	align_dlen = ALIGN(dlen, align);
	info_len = ALIGN(माप(*info), align);
	rlen = ALIGN(माप(जोड़ otx_cpt_res_s), align);
	total_mem_len = align_dlen + info_len + rlen + COMPLETION_CODE_SIZE;

	info = kzalloc(total_mem_len, gfp);
	अगर (unlikely(!info)) अणु
		dev_err(&pdev->dev, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	*pinfo = info;
	info->dlen = dlen;
	info->in_buffer = (u8 *)info + info_len;

	((__be16 *)info->in_buffer)[0] = cpu_to_be16(req->outcnt);
	((__be16 *)info->in_buffer)[1] = cpu_to_be16(req->incnt);
	((u16 *)info->in_buffer)[2] = 0;
	((u16 *)info->in_buffer)[3] = 0;

	/* Setup gather (input) components */
	अगर (setup_sgio_components(pdev, req->in, req->incnt,
				  &info->in_buffer[8])) अणु
		dev_err(&pdev->dev, "Failed to setup gather list\n");
		वापस -EFAULT;
	पूर्ण

	अगर (setup_sgio_components(pdev, req->out, req->outcnt,
				  &info->in_buffer[8 + g_sz_bytes])) अणु
		dev_err(&pdev->dev, "Failed to setup scatter list\n");
		वापस -EFAULT;
	पूर्ण

	info->dma_len = total_mem_len - info_len;
	info->dptr_baddr = dma_map_single(&pdev->dev, (व्योम *)info->in_buffer,
					  info->dma_len, DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(&pdev->dev, info->dptr_baddr))) अणु
		dev_err(&pdev->dev, "DMA Mapping failed for cpt req\n");
		वापस -EIO;
	पूर्ण
	/*
	 * Get buffer क्रम जोड़ otx_cpt_res_s response
	 * काष्ठाure and its physical address
	 */
	info->completion_addr = (u64 *)(info->in_buffer + align_dlen);
	info->comp_baddr = info->dptr_baddr + align_dlen;

	/* Create and initialize RPTR */
	info->out_buffer = (u8 *)info->completion_addr + rlen;
	info->rptr_baddr = info->comp_baddr + rlen;

	*((u64 *) info->out_buffer) = ~((u64) COMPLETION_CODE_INIT);

	वापस 0;
पूर्ण


अटल व्योम cpt_fill_inst(जोड़ otx_cpt_inst_s *inst,
			  काष्ठा otx_cpt_info_buffer *info,
			  काष्ठा otx_cpt_iq_cmd *cmd)
अणु
	inst->u[0] = 0x0;
	inst->s.करोneपूर्णांक = true;
	inst->s.res_addr = (u64)info->comp_baddr;
	inst->u[2] = 0x0;
	inst->s.wq_ptr = 0;
	inst->s.ei0 = cmd->cmd.u64;
	inst->s.ei1 = cmd->dptr;
	inst->s.ei2 = cmd->rptr;
	inst->s.ei3 = cmd->cptr.u64;
पूर्ण

/*
 * On OcteonTX platक्रमm the parameter db_count is used as a count क्रम ringing
 * करोor bell. The valid values क्रम db_count are:
 * 0 - 1 CPT inकाष्ठाion will be enqueued however CPT will not be inक्रमmed
 * 1 - 1 CPT inकाष्ठाion will be enqueued and CPT will be inक्रमmed
 */
अटल व्योम cpt_send_cmd(जोड़ otx_cpt_inst_s *cptinst, काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_cmd_qinfo *qinfo = &cptvf->cqinfo;
	काष्ठा otx_cpt_cmd_queue *queue;
	काष्ठा otx_cpt_cmd_chunk *curr;
	u8 *ent;

	queue = &qinfo->queue[0];
	/*
	 * cpt_send_cmd is currently called only from critical section
	 * thereक्रमe no locking is required क्रम accessing inकाष्ठाion queue
	 */
	ent = &queue->qhead->head[queue->idx * OTX_CPT_INST_SIZE];
	स_नकल(ent, (व्योम *) cptinst, OTX_CPT_INST_SIZE);

	अगर (++queue->idx >= queue->qhead->size / 64) अणु
		curr = queue->qhead;

		अगर (list_is_last(&curr->nextchunk, &queue->chead))
			queue->qhead = queue->base;
		अन्यथा
			queue->qhead = list_next_entry(queue->qhead, nextchunk);
		queue->idx = 0;
	पूर्ण
	/* make sure all memory stores are करोne beक्रमe ringing करोorbell */
	smp_wmb();
	otx_cptvf_ग_लिखो_vq_करोorbell(cptvf, 1);
पूर्ण

अटल पूर्णांक process_request(काष्ठा pci_dev *pdev, काष्ठा otx_cpt_req_info *req,
			   काष्ठा otx_cpt_pending_queue *pqueue,
			   काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cptvf_request *cpt_req = &req->req;
	काष्ठा otx_cpt_pending_entry *pentry = शून्य;
	जोड़ otx_cpt_ctrl_info *ctrl = &req->ctrl;
	काष्ठा otx_cpt_info_buffer *info = शून्य;
	जोड़ otx_cpt_res_s *result = शून्य;
	काष्ठा otx_cpt_iq_cmd iq_cmd;
	जोड़ otx_cpt_inst_s cptinst;
	पूर्णांक retry, ret = 0;
	u8 resume_sender;
	gfp_t gfp;

	gfp = (req->areq->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							      GFP_ATOMIC;
	ret = setup_sgio_list(pdev, &info, req, gfp);
	अगर (unlikely(ret)) अणु
		dev_err(&pdev->dev, "Setting up SG list failed\n");
		जाओ request_cleanup;
	पूर्ण
	cpt_req->dlen = info->dlen;

	result = (जोड़ otx_cpt_res_s *) info->completion_addr;
	result->s.compcode = COMPLETION_CODE_INIT;

	spin_lock_bh(&pqueue->lock);
	pentry = get_मुक्त_pending_entry(pqueue, pqueue->qlen);
	retry = CPT_PENTRY_TIMEOUT / CPT_PENTRY_STEP;
	जबतक (unlikely(!pentry) && retry--) अणु
		spin_unlock_bh(&pqueue->lock);
		udelay(CPT_PENTRY_STEP);
		spin_lock_bh(&pqueue->lock);
		pentry = get_मुक्त_pending_entry(pqueue, pqueue->qlen);
	पूर्ण

	अगर (unlikely(!pentry)) अणु
		ret = -ENOSPC;
		spin_unlock_bh(&pqueue->lock);
		जाओ request_cleanup;
	पूर्ण

	/*
	 * Check अगर we are बंद to filling in entire pending queue,
	 * अगर so then tell the sender to stop/sleep by वापसing -EBUSY
	 * We करो it only क्रम context which can sleep (GFP_KERNEL)
	 */
	अगर (gfp == GFP_KERNEL &&
	    pqueue->pending_count > (pqueue->qlen - CPT_IQ_STOP_MARGIN)) अणु
		pentry->resume_sender = true;
	पूर्ण अन्यथा
		pentry->resume_sender = false;
	resume_sender = pentry->resume_sender;
	pqueue->pending_count++;

	pentry->completion_addr = info->completion_addr;
	pentry->info = info;
	pentry->callback = req->callback;
	pentry->areq = req->areq;
	pentry->busy = true;
	info->pentry = pentry;
	info->समय_in = jअगरfies;
	info->req = req;

	/* Fill in the command */
	iq_cmd.cmd.u64 = 0;
	iq_cmd.cmd.s.opcode = cpu_to_be16(cpt_req->opcode.flags);
	iq_cmd.cmd.s.param1 = cpu_to_be16(cpt_req->param1);
	iq_cmd.cmd.s.param2 = cpu_to_be16(cpt_req->param2);
	iq_cmd.cmd.s.dlen   = cpu_to_be16(cpt_req->dlen);

	iq_cmd.dptr = info->dptr_baddr;
	iq_cmd.rptr = info->rptr_baddr;
	iq_cmd.cptr.u64 = 0;
	iq_cmd.cptr.s.grp = ctrl->s.grp;

	/* Fill in the CPT_INST_S type command क्रम HW पूर्णांकerpretation */
	cpt_fill_inst(&cptinst, info, &iq_cmd);

	/* Prपूर्णांक debug info अगर enabled */
	otx_cpt_dump_sg_list(pdev, req);
	pr_debug("Cpt_inst_s hexdump (%d bytes)\n", OTX_CPT_INST_SIZE);
	prपूर्णांक_hex_dump_debug("", 0, 16, 1, &cptinst, OTX_CPT_INST_SIZE, false);
	pr_debug("Dptr hexdump (%d bytes)\n", cpt_req->dlen);
	prपूर्णांक_hex_dump_debug("", 0, 16, 1, info->in_buffer,
			     cpt_req->dlen, false);

	/* Send CPT command */
	cpt_send_cmd(&cptinst, cptvf);

	/*
	 * We allocate and prepare pending queue entry in critical section
	 * together with submitting CPT inकाष्ठाion to CPT inकाष्ठाion queue
	 * to make sure that order of CPT requests is the same in both
	 * pending and inकाष्ठाion queues
	 */
	spin_unlock_bh(&pqueue->lock);

	ret = resume_sender ? -EBUSY : -EINPROGRESS;
	वापस ret;

request_cleanup:
	करो_request_cleanup(pdev, info);
	वापस ret;
पूर्ण

पूर्णांक otx_cpt_करो_request(काष्ठा pci_dev *pdev, काष्ठा otx_cpt_req_info *req,
		       पूर्णांक cpu_num)
अणु
	काष्ठा otx_cptvf *cptvf = pci_get_drvdata(pdev);

	अगर (!otx_cpt_device_पढ़ोy(cptvf)) अणु
		dev_err(&pdev->dev, "CPT Device is not ready\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((cptvf->vftype == OTX_CPT_SE_TYPES) && (!req->ctrl.s.se_req)) अणु
		dev_err(&pdev->dev, "CPTVF-%d of SE TYPE got AE request\n",
			cptvf->vfid);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((cptvf->vftype == OTX_CPT_AE_TYPES) &&
		   (req->ctrl.s.se_req)) अणु
		dev_err(&pdev->dev, "CPTVF-%d of AE TYPE got SE request\n",
			cptvf->vfid);
		वापस -EINVAL;
	पूर्ण

	वापस process_request(pdev, req, &cptvf->pqinfo.queue[0], cptvf);
पूर्ण

अटल पूर्णांक cpt_process_ccode(काष्ठा pci_dev *pdev,
			     जोड़ otx_cpt_res_s *cpt_status,
			     काष्ठा otx_cpt_info_buffer *cpt_info,
			     काष्ठा otx_cpt_req_info *req, u32 *res_code)
अणु
	u8 ccode = cpt_status->s.compcode;
	जोड़ otx_cpt_error_code ecode;

	ecode.u = be64_to_cpup((__be64 *)cpt_info->out_buffer);
	चयन (ccode) अणु
	हाल CPT_COMP_E_FAULT:
		dev_err(&pdev->dev,
			"Request failed with DMA fault\n");
		otx_cpt_dump_sg_list(pdev, req);
		अवरोध;

	हाल CPT_COMP_E_SWERR:
		dev_err(&pdev->dev,
			"Request failed with software error code %d\n",
			ecode.s.ccode);
		otx_cpt_dump_sg_list(pdev, req);
		अवरोध;

	हाल CPT_COMP_E_HWERR:
		dev_err(&pdev->dev,
			"Request failed with hardware error\n");
		otx_cpt_dump_sg_list(pdev, req);
		अवरोध;

	हाल COMPLETION_CODE_INIT:
		/* check क्रम समयout */
		अगर (समय_after_eq(jअगरfies, cpt_info->समय_in +
				  OTX_CPT_COMMAND_TIMEOUT * HZ))
			dev_warn(&pdev->dev, "Request timed out 0x%p\n", req);
		अन्यथा अगर (cpt_info->extra_समय < OTX_CPT_TIME_IN_RESET_COUNT) अणु
			cpt_info->समय_in = jअगरfies;
			cpt_info->extra_समय++;
		पूर्ण
		वापस 1;

	हाल CPT_COMP_E_GOOD:
		/* Check microcode completion code */
		अगर (ecode.s.ccode) अणु
			/*
			 * If requested hmac is truncated and ucode वापसs
			 * s/g ग_लिखो length error then we report success
			 * because ucode ग_लिखोs as many bytes of calculated
			 * hmac as available in gather buffer and reports
			 * s/g ग_लिखो length error अगर number of bytes in gather
			 * buffer is less than full hmac size.
			 */
			अगर (req->is_trunc_hmac &&
			    ecode.s.ccode == ERR_SCATTER_GATHER_WRITE_LENGTH) अणु
				*res_code = 0;
				अवरोध;
			पूर्ण

			dev_err(&pdev->dev,
				"Request failed with software error code 0x%x\n",
				ecode.s.ccode);
			otx_cpt_dump_sg_list(pdev, req);
			अवरोध;
		पूर्ण

		/* Request has been processed with success */
		*res_code = 0;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Request returned invalid status\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम process_pending_queue(काष्ठा pci_dev *pdev,
					 काष्ठा otx_cpt_pending_queue *pqueue)
अणु
	व्योम (*callback)(पूर्णांक status, व्योम *arg1, व्योम *arg2);
	काष्ठा otx_cpt_pending_entry *resume_pentry = शून्य;
	काष्ठा otx_cpt_pending_entry *pentry = शून्य;
	काष्ठा otx_cpt_info_buffer *cpt_info = शून्य;
	जोड़ otx_cpt_res_s *cpt_status = शून्य;
	काष्ठा otx_cpt_req_info *req = शून्य;
	काष्ठा crypto_async_request *areq;
	u32 res_code, resume_index;

	जबतक (1) अणु
		spin_lock_bh(&pqueue->lock);
		pentry = &pqueue->head[pqueue->front];

		अगर (WARN_ON(!pentry)) अणु
			spin_unlock_bh(&pqueue->lock);
			अवरोध;
		पूर्ण

		res_code = -EINVAL;
		अगर (unlikely(!pentry->busy)) अणु
			spin_unlock_bh(&pqueue->lock);
			अवरोध;
		पूर्ण

		अगर (unlikely(!pentry->callback)) अणु
			dev_err(&pdev->dev, "Callback NULL\n");
			जाओ process_pentry;
		पूर्ण

		cpt_info = pentry->info;
		अगर (unlikely(!cpt_info)) अणु
			dev_err(&pdev->dev, "Pending entry post arg NULL\n");
			जाओ process_pentry;
		पूर्ण

		req = cpt_info->req;
		अगर (unlikely(!req)) अणु
			dev_err(&pdev->dev, "Request NULL\n");
			जाओ process_pentry;
		पूर्ण

		cpt_status = (जोड़ otx_cpt_res_s *) pentry->completion_addr;
		अगर (unlikely(!cpt_status)) अणु
			dev_err(&pdev->dev, "Completion address NULL\n");
			जाओ process_pentry;
		पूर्ण

		अगर (cpt_process_ccode(pdev, cpt_status, cpt_info, req,
				      &res_code)) अणु
			spin_unlock_bh(&pqueue->lock);
			वापस;
		पूर्ण
		cpt_info->pdev = pdev;

process_pentry:
		/*
		 * Check अगर we should inक्रमm sending side to resume
		 * We करो it CPT_IQ_RESUME_MARGIN elements in advance beक्रमe
		 * pending queue becomes empty
		 */
		resume_index = modulo_inc(pqueue->front, pqueue->qlen,
					  CPT_IQ_RESUME_MARGIN);
		resume_pentry = &pqueue->head[resume_index];
		अगर (resume_pentry &&
		    resume_pentry->resume_sender) अणु
			resume_pentry->resume_sender = false;
			callback = resume_pentry->callback;
			areq = resume_pentry->areq;

			अगर (callback) अणु
				spin_unlock_bh(&pqueue->lock);

				/*
				 * EINPROGRESS is an indication क्रम sending
				 * side that it can resume sending requests
				 */
				callback(-EINPROGRESS, areq, cpt_info);
				spin_lock_bh(&pqueue->lock);
			पूर्ण
		पूर्ण

		callback = pentry->callback;
		areq = pentry->areq;
		मुक्त_pentry(pentry);

		pqueue->pending_count--;
		pqueue->front = modulo_inc(pqueue->front, pqueue->qlen, 1);
		spin_unlock_bh(&pqueue->lock);

		/*
		 * Call callback after current pending entry has been
		 * processed, we करोn't करो it अगर the callback poपूर्णांकer is
		 * invalid.
		 */
		अगर (callback)
			callback(res_code, areq, cpt_info);
	पूर्ण
पूर्ण

व्योम otx_cpt_post_process(काष्ठा otx_cptvf_wqe *wqe)
अणु
	process_pending_queue(wqe->cptvf->pdev, &wqe->cptvf->pqinfo.queue[0]);
पूर्ण
