<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cptvf.h"
#समावेश "otx2_cpt_common.h"

/* SG list header size in bytes */
#घोषणा SG_LIST_HDR_SIZE	8

/* Default समयout when रुकोing क्रम मुक्त pending entry in us */
#घोषणा CPT_PENTRY_TIMEOUT	1000
#घोषणा CPT_PENTRY_STEP		50

/* Default threshold क्रम stopping and resuming sender requests */
#घोषणा CPT_IQ_STOP_MARGIN	128
#घोषणा CPT_IQ_RESUME_MARGIN	512

/* Default command समयout in seconds */
#घोषणा CPT_COMMAND_TIMEOUT	4
#घोषणा CPT_TIME_IN_RESET_COUNT 5

अटल व्योम otx2_cpt_dump_sg_list(काष्ठा pci_dev *pdev,
				  काष्ठा otx2_cpt_req_info *req)
अणु
	पूर्णांक i;

	pr_debug("Gather list size %d\n", req->in_cnt);
	क्रम (i = 0; i < req->in_cnt; i++) अणु
		pr_debug("Buffer %d size %d, vptr 0x%p, dmaptr 0x%p\n", i,
			 req->in[i].size, req->in[i].vptr,
			 (व्योम *) req->in[i].dma_addr);
		pr_debug("Buffer hexdump (%d bytes)\n",
			 req->in[i].size);
		prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_NONE, 16, 1,
				     req->in[i].vptr, req->in[i].size, false);
	पूर्ण
	pr_debug("Scatter list size %d\n", req->out_cnt);
	क्रम (i = 0; i < req->out_cnt; i++) अणु
		pr_debug("Buffer %d size %d, vptr 0x%p, dmaptr 0x%p\n", i,
			 req->out[i].size, req->out[i].vptr,
			 (व्योम *) req->out[i].dma_addr);
		pr_debug("Buffer hexdump (%d bytes)\n", req->out[i].size);
		prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_NONE, 16, 1,
				     req->out[i].vptr, req->out[i].size, false);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा otx2_cpt_pending_entry *get_मुक्त_pending_entry(
					काष्ठा otx2_cpt_pending_queue *q,
					पूर्णांक qlen)
अणु
	काष्ठा otx2_cpt_pending_entry *ent = शून्य;

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

अटल अंतरभूत व्योम मुक्त_pentry(काष्ठा otx2_cpt_pending_entry *pentry)
अणु
	pentry->completion_addr = शून्य;
	pentry->info = शून्य;
	pentry->callback = शून्य;
	pentry->areq = शून्य;
	pentry->resume_sender = false;
	pentry->busy = false;
पूर्ण

अटल अंतरभूत पूर्णांक setup_sgio_components(काष्ठा pci_dev *pdev,
					काष्ठा otx2_cpt_buf_ptr *list,
					पूर्णांक buf_count, u8 *buffer)
अणु
	काष्ठा otx2_cpt_sglist_component *sg_ptr = शून्य;
	पूर्णांक ret = 0, i, j;
	पूर्णांक components;

	अगर (unlikely(!list)) अणु
		dev_err(&pdev->dev, "Input list pointer is NULL\n");
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < buf_count; i++) अणु
		अगर (unlikely(!list[i].vptr))
			जारी;
		list[i].dma_addr = dma_map_single(&pdev->dev, list[i].vptr,
						  list[i].size,
						  DMA_BIसूचीECTIONAL);
		अगर (unlikely(dma_mapping_error(&pdev->dev, list[i].dma_addr))) अणु
			dev_err(&pdev->dev, "Dma mapping failed\n");
			ret = -EIO;
			जाओ sg_cleanup;
		पूर्ण
	पूर्ण
	components = buf_count / 4;
	sg_ptr = (काष्ठा otx2_cpt_sglist_component *)buffer;
	क्रम (i = 0; i < components; i++) अणु
		sg_ptr->len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->len3 = cpu_to_be16(list[i * 4 + 3].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		sg_ptr->ptr3 = cpu_to_be64(list[i * 4 + 3].dma_addr);
		sg_ptr++;
	पूर्ण
	components = buf_count % 4;

	चयन (components) अणु
	हाल 3:
		sg_ptr->len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		fallthrough;
	हाल 2:
		sg_ptr->len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		fallthrough;
	हाल 1:
		sg_ptr->len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;

sg_cleanup:
	क्रम (j = 0; j < i; j++) अणु
		अगर (list[j].dma_addr) अणु
			dma_unmap_single(&pdev->dev, list[j].dma_addr,
					 list[j].size, DMA_BIसूचीECTIONAL);
		पूर्ण

		list[j].dma_addr = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा otx2_cpt_inst_info *info_create(काष्ठा pci_dev *pdev,
					      काष्ठा otx2_cpt_req_info *req,
					      gfp_t gfp)
अणु
	पूर्णांक align = OTX2_CPT_DMA_MINALIGN;
	काष्ठा otx2_cpt_inst_info *info;
	u32 dlen, align_dlen, info_len;
	u16 g_sz_bytes, s_sz_bytes;
	u32 total_mem_len;

	अगर (unlikely(req->in_cnt > OTX2_CPT_MAX_SG_IN_CNT ||
		     req->out_cnt > OTX2_CPT_MAX_SG_OUT_CNT)) अणु
		dev_err(&pdev->dev, "Error too many sg components\n");
		वापस शून्य;
	पूर्ण

	g_sz_bytes = ((req->in_cnt + 3) / 4) *
		      माप(काष्ठा otx2_cpt_sglist_component);
	s_sz_bytes = ((req->out_cnt + 3) / 4) *
		      माप(काष्ठा otx2_cpt_sglist_component);

	dlen = g_sz_bytes + s_sz_bytes + SG_LIST_HDR_SIZE;
	align_dlen = ALIGN(dlen, align);
	info_len = ALIGN(माप(*info), align);
	total_mem_len = align_dlen + info_len + माप(जोड़ otx2_cpt_res_s);

	info = kzalloc(total_mem_len, gfp);
	अगर (unlikely(!info))
		वापस शून्य;

	info->dlen = dlen;
	info->in_buffer = (u8 *)info + info_len;

	((u16 *)info->in_buffer)[0] = req->out_cnt;
	((u16 *)info->in_buffer)[1] = req->in_cnt;
	((u16 *)info->in_buffer)[2] = 0;
	((u16 *)info->in_buffer)[3] = 0;
	cpu_to_be64s((u64 *)info->in_buffer);

	/* Setup gather (input) components */
	अगर (setup_sgio_components(pdev, req->in, req->in_cnt,
				  &info->in_buffer[8])) अणु
		dev_err(&pdev->dev, "Failed to setup gather list\n");
		जाओ destroy_info;
	पूर्ण

	अगर (setup_sgio_components(pdev, req->out, req->out_cnt,
				  &info->in_buffer[8 + g_sz_bytes])) अणु
		dev_err(&pdev->dev, "Failed to setup scatter list\n");
		जाओ destroy_info;
	पूर्ण

	info->dma_len = total_mem_len - info_len;
	info->dptr_baddr = dma_map_single(&pdev->dev, info->in_buffer,
					  info->dma_len, DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(&pdev->dev, info->dptr_baddr))) अणु
		dev_err(&pdev->dev, "DMA Mapping failed for cpt req\n");
		जाओ destroy_info;
	पूर्ण
	/*
	 * Get buffer क्रम जोड़ otx2_cpt_res_s response
	 * काष्ठाure and its physical address
	 */
	info->completion_addr = info->in_buffer + align_dlen;
	info->comp_baddr = info->dptr_baddr + align_dlen;

	वापस info;

destroy_info:
	otx2_cpt_info_destroy(pdev, info);
	वापस शून्य;
पूर्ण

अटल पूर्णांक process_request(काष्ठा pci_dev *pdev, काष्ठा otx2_cpt_req_info *req,
			   काष्ठा otx2_cpt_pending_queue *pqueue,
			   काष्ठा otx2_cptlf_info *lf)
अणु
	काष्ठा otx2_cptvf_request *cpt_req = &req->req;
	काष्ठा otx2_cpt_pending_entry *pentry = शून्य;
	जोड़ otx2_cpt_ctrl_info *ctrl = &req->ctrl;
	काष्ठा otx2_cpt_inst_info *info = शून्य;
	जोड़ otx2_cpt_res_s *result = शून्य;
	काष्ठा otx2_cpt_iq_command iq_cmd;
	जोड़ otx2_cpt_inst_s cptinst;
	पूर्णांक retry, ret = 0;
	u8 resume_sender;
	gfp_t gfp;

	gfp = (req->areq->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							      GFP_ATOMIC;
	अगर (unlikely(!otx2_cptlf_started(lf->lfs)))
		वापस -ENODEV;

	info = info_create(pdev, req, gfp);
	अगर (unlikely(!info)) अणु
		dev_err(&pdev->dev, "Setting up cpt inst info failed");
		वापस -ENOMEM;
	पूर्ण
	cpt_req->dlen = info->dlen;

	result = info->completion_addr;
	result->s.compcode = OTX2_CPT_COMPLETION_CODE_INIT;

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
		जाओ destroy_info;
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
	iq_cmd.cmd.u = 0;
	iq_cmd.cmd.s.opcode = cpu_to_be16(cpt_req->opcode.flags);
	iq_cmd.cmd.s.param1 = cpu_to_be16(cpt_req->param1);
	iq_cmd.cmd.s.param2 = cpu_to_be16(cpt_req->param2);
	iq_cmd.cmd.s.dlen   = cpu_to_be16(cpt_req->dlen);

	/* 64-bit swap क्रम microcode data पढ़ोs, not needed क्रम addresses*/
	cpu_to_be64s(&iq_cmd.cmd.u);
	iq_cmd.dptr = info->dptr_baddr;
	iq_cmd.rptr = 0;
	iq_cmd.cptr.u = 0;
	iq_cmd.cptr.s.grp = ctrl->s.grp;

	/* Fill in the CPT_INST_S type command क्रम HW पूर्णांकerpretation */
	otx2_cpt_fill_inst(&cptinst, &iq_cmd, info->comp_baddr);

	/* Prपूर्णांक debug info अगर enabled */
	otx2_cpt_dump_sg_list(pdev, req);
	pr_debug("Cpt_inst_s hexdump (%d bytes)\n", OTX2_CPT_INST_SIZE);
	prपूर्णांक_hex_dump_debug("", 0, 16, 1, &cptinst, OTX2_CPT_INST_SIZE, false);
	pr_debug("Dptr hexdump (%d bytes)\n", cpt_req->dlen);
	prपूर्णांक_hex_dump_debug("", 0, 16, 1, info->in_buffer,
			     cpt_req->dlen, false);

	/* Send CPT command */
	otx2_cpt_send_cmd(&cptinst, 1, lf);

	/*
	 * We allocate and prepare pending queue entry in critical section
	 * together with submitting CPT inकाष्ठाion to CPT inकाष्ठाion queue
	 * to make sure that order of CPT requests is the same in both
	 * pending and inकाष्ठाion queues
	 */
	spin_unlock_bh(&pqueue->lock);

	ret = resume_sender ? -EBUSY : -EINPROGRESS;
	वापस ret;

destroy_info:
	spin_unlock_bh(&pqueue->lock);
	otx2_cpt_info_destroy(pdev, info);
	वापस ret;
पूर्ण

पूर्णांक otx2_cpt_करो_request(काष्ठा pci_dev *pdev, काष्ठा otx2_cpt_req_info *req,
			पूर्णांक cpu_num)
अणु
	काष्ठा otx2_cptvf_dev *cptvf = pci_get_drvdata(pdev);
	काष्ठा otx2_cptlfs_info *lfs = &cptvf->lfs;

	वापस process_request(lfs->pdev, req, &lfs->lf[cpu_num].pqueue,
			       &lfs->lf[cpu_num]);
पूर्ण

अटल पूर्णांक cpt_process_ccode(काष्ठा pci_dev *pdev,
			     जोड़ otx2_cpt_res_s *cpt_status,
			     काष्ठा otx2_cpt_inst_info *info,
			     u32 *res_code)
अणु
	u8 uc_ccode = cpt_status->s.uc_compcode;
	u8 ccode = cpt_status->s.compcode;

	चयन (ccode) अणु
	हाल OTX2_CPT_COMP_E_FAULT:
		dev_err(&pdev->dev,
			"Request failed with DMA fault\n");
		otx2_cpt_dump_sg_list(pdev, info->req);
		अवरोध;

	हाल OTX2_CPT_COMP_E_HWERR:
		dev_err(&pdev->dev,
			"Request failed with hardware error\n");
		otx2_cpt_dump_sg_list(pdev, info->req);
		अवरोध;

	हाल OTX2_CPT_COMP_E_INSTERR:
		dev_err(&pdev->dev,
			"Request failed with instruction error\n");
		otx2_cpt_dump_sg_list(pdev, info->req);
		अवरोध;

	हाल OTX2_CPT_COMP_E_NOTDONE:
		/* check क्रम समयout */
		अगर (समय_after_eq(jअगरfies, info->समय_in +
				  CPT_COMMAND_TIMEOUT * HZ))
			dev_warn(&pdev->dev,
				 "Request timed out 0x%p", info->req);
		अन्यथा अगर (info->extra_समय < CPT_TIME_IN_RESET_COUNT) अणु
			info->समय_in = jअगरfies;
			info->extra_समय++;
		पूर्ण
		वापस 1;

	हाल OTX2_CPT_COMP_E_GOOD:
		/*
		 * Check microcode completion code, it is only valid
		 * when completion code is CPT_COMP_E::GOOD
		 */
		अगर (uc_ccode != OTX2_CPT_UCC_SUCCESS) अणु
			/*
			 * If requested hmac is truncated and ucode वापसs
			 * s/g ग_लिखो length error then we report success
			 * because ucode ग_लिखोs as many bytes of calculated
			 * hmac as available in gather buffer and reports
			 * s/g ग_लिखो length error अगर number of bytes in gather
			 * buffer is less than full hmac size.
			 */
			अगर (info->req->is_trunc_hmac &&
			    uc_ccode == OTX2_CPT_UCC_SG_WRITE_LENGTH) अणु
				*res_code = 0;
				अवरोध;
			पूर्ण

			dev_err(&pdev->dev,
				"Request failed with software error code 0x%x\n",
				cpt_status->s.uc_compcode);
			otx2_cpt_dump_sg_list(pdev, info->req);
			अवरोध;
		पूर्ण
		/* Request has been processed with success */
		*res_code = 0;
		अवरोध;

	शेष:
		dev_err(&pdev->dev,
			"Request returned invalid status %d\n", ccode);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम process_pending_queue(काष्ठा pci_dev *pdev,
					 काष्ठा otx2_cpt_pending_queue *pqueue)
अणु
	काष्ठा otx2_cpt_pending_entry *resume_pentry = शून्य;
	व्योम (*callback)(पूर्णांक status, व्योम *arg, व्योम *req);
	काष्ठा otx2_cpt_pending_entry *pentry = शून्य;
	जोड़ otx2_cpt_res_s *cpt_status = शून्य;
	काष्ठा otx2_cpt_inst_info *info = शून्य;
	काष्ठा otx2_cpt_req_info *req = शून्य;
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

		info = pentry->info;
		अगर (unlikely(!info)) अणु
			dev_err(&pdev->dev, "Pending entry post arg NULL\n");
			जाओ process_pentry;
		पूर्ण

		req = info->req;
		अगर (unlikely(!req)) अणु
			dev_err(&pdev->dev, "Request NULL\n");
			जाओ process_pentry;
		पूर्ण

		cpt_status = pentry->completion_addr;
		अगर (unlikely(!cpt_status)) अणु
			dev_err(&pdev->dev, "Completion address NULL\n");
			जाओ process_pentry;
		पूर्ण

		अगर (cpt_process_ccode(pdev, cpt_status, info, &res_code)) अणु
			spin_unlock_bh(&pqueue->lock);
			वापस;
		पूर्ण
		info->pdev = pdev;

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
				callback(-EINPROGRESS, areq, info);
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
			callback(res_code, areq, info);
	पूर्ण
पूर्ण

व्योम otx2_cpt_post_process(काष्ठा otx2_cptlf_wqe *wqe)
अणु
	process_pending_queue(wqe->lfs->pdev,
			      &wqe->lfs->lf[wqe->lf_num].pqueue);
पूर्ण

पूर्णांक otx2_cpt_get_kcrypto_eng_grp_num(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx2_cptvf_dev *cptvf = pci_get_drvdata(pdev);

	वापस cptvf->lfs.kcrypto_eng_grp_num;
पूर्ण
