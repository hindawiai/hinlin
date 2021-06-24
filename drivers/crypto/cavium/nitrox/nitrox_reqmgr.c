<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/gfp.h>
#समावेश <linux/workqueue.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "nitrox_common.h"
#समावेश "nitrox_dev.h"
#समावेश "nitrox_req.h"
#समावेश "nitrox_csr.h"

/* SLC_STORE_INFO */
#घोषणा MIN_UDD_LEN 16
/* PKT_IN_HDR + SLC_STORE_INFO */
#घोषणा FDATA_SIZE 32
/* Base destination port क्रम the solicited requests */
#घोषणा SOLICIT_BASE_DPORT 256

#घोषणा REQ_NOT_POSTED 1
#घोषणा REQ_BACKLOG    2
#घोषणा REQ_POSTED     3

/**
 * Response codes from SE microcode
 * 0x00 - Success
 *   Completion with no error
 * 0x43 - ERR_GC_DATA_LEN_INVALID
 *   Invalid Data length अगर Encryption Data length is
 *   less than 16 bytes क्रम AES-XTS and AES-CTS.
 * 0x45 - ERR_GC_CTX_LEN_INVALID
 *   Invalid context length: CTXL != 23 words.
 * 0x4F - ERR_GC_DOCSIS_CIPHER_INVALID
 *   DOCSIS support is enabled with other than
 *   AES/DES-CBC mode encryption.
 * 0x50 - ERR_GC_DOCSIS_OFFSET_INVALID
 *   Authentication offset is other than 0 with
 *   Encryption IV source = 0.
 *   Authentication offset is other than 8 (DES)/16 (AES)
 *   with Encryption IV source = 1
 * 0x51 - ERR_GC_CRC32_INVALID_SELECTION
 *   CRC32 is enabled क्रम other than DOCSIS encryption.
 * 0x52 - ERR_GC_AES_CCM_FLAG_INVALID
 *   Invalid flag options in AES-CCM IV.
 */

अटल अंतरभूत पूर्णांक incr_index(पूर्णांक index, पूर्णांक count, पूर्णांक max)
अणु
	अगर ((index + count) >= max)
		index = index + count - max;
	अन्यथा
		index += count;

	वापस index;
पूर्ण

अटल व्योम softreq_unmap_sgbufs(काष्ठा nitrox_softreq *sr)
अणु
	काष्ठा nitrox_device *ndev = sr->ndev;
	काष्ठा device *dev = DEV(ndev);


	dma_unmap_sg(dev, sr->in.sg, sg_nents(sr->in.sg),
		     DMA_BIसूचीECTIONAL);
	dma_unmap_single(dev, sr->in.sgcomp_dma, sr->in.sgcomp_len,
			 DMA_TO_DEVICE);
	kमुक्त(sr->in.sgcomp);
	sr->in.sg = शून्य;
	sr->in.sgmap_cnt = 0;

	dma_unmap_sg(dev, sr->out.sg, sg_nents(sr->out.sg),
		     DMA_BIसूचीECTIONAL);
	dma_unmap_single(dev, sr->out.sgcomp_dma, sr->out.sgcomp_len,
			 DMA_TO_DEVICE);
	kमुक्त(sr->out.sgcomp);
	sr->out.sg = शून्य;
	sr->out.sgmap_cnt = 0;
पूर्ण

अटल व्योम softreq_destroy(काष्ठा nitrox_softreq *sr)
अणु
	softreq_unmap_sgbufs(sr);
	kमुक्त(sr);
पूर्ण

/**
 * create_sg_component - create SG componets क्रम N5 device.
 * @sr: Request काष्ठाure
 * @sgtbl: SG table
 * @map_nents: number of dma mapped entries
 *
 * Component काष्ठाure
 *
 *   63     48 47     32 31    16 15      0
 *   --------------------------------------
 *   |   LEN0  |  LEN1  |  LEN2  |  LEN3  |
 *   |-------------------------------------
 *   |               PTR0                 |
 *   --------------------------------------
 *   |               PTR1                 |
 *   --------------------------------------
 *   |               PTR2                 |
 *   --------------------------------------
 *   |               PTR3                 |
 *   --------------------------------------
 *
 *   Returns 0 अगर success or a negative त्रुटि_सं code on error.
 */
अटल पूर्णांक create_sg_component(काष्ठा nitrox_softreq *sr,
			       काष्ठा nitrox_sgtable *sgtbl, पूर्णांक map_nents)
अणु
	काष्ठा nitrox_device *ndev = sr->ndev;
	काष्ठा nitrox_sgcomp *sgcomp;
	काष्ठा scatterlist *sg;
	dma_addr_t dma;
	माप_प्रकार sz_comp;
	पूर्णांक i, j, nr_sgcomp;

	nr_sgcomp = roundup(map_nents, 4) / 4;

	/* each component holds 4 dma poपूर्णांकers */
	sz_comp = nr_sgcomp * माप(*sgcomp);
	sgcomp = kzalloc(sz_comp, sr->gfp);
	अगर (!sgcomp)
		वापस -ENOMEM;

	sgtbl->sgcomp = sgcomp;

	sg = sgtbl->sg;
	/* populate device sg component */
	क्रम (i = 0; i < nr_sgcomp; i++) अणु
		क्रम (j = 0; j < 4 && sg; j++) अणु
			sgcomp[i].len[j] = cpu_to_be16(sg_dma_len(sg));
			sgcomp[i].dma[j] = cpu_to_be64(sg_dma_address(sg));
			sg = sg_next(sg);
		पूर्ण
	पूर्ण
	/* map the device sg component */
	dma = dma_map_single(DEV(ndev), sgtbl->sgcomp, sz_comp, DMA_TO_DEVICE);
	अगर (dma_mapping_error(DEV(ndev), dma)) अणु
		kमुक्त(sgtbl->sgcomp);
		sgtbl->sgcomp = शून्य;
		वापस -ENOMEM;
	पूर्ण

	sgtbl->sgcomp_dma = dma;
	sgtbl->sgcomp_len = sz_comp;

	वापस 0;
पूर्ण

/**
 * dma_map_inbufs - DMA map input sglist and creates sglist component
 *                  क्रम N5 device.
 * @sr: Request काष्ठाure
 * @req: Crypto request काष्ठाre
 *
 * Returns 0 अगर successful or a negative त्रुटि_सं code on error.
 */
अटल पूर्णांक dma_map_inbufs(काष्ठा nitrox_softreq *sr,
			  काष्ठा se_crypto_request *req)
अणु
	काष्ठा device *dev = DEV(sr->ndev);
	काष्ठा scatterlist *sg = req->src;
	पूर्णांक i, nents, ret = 0;

	nents = dma_map_sg(dev, req->src, sg_nents(req->src),
			   DMA_BIसूचीECTIONAL);
	अगर (!nents)
		वापस -EINVAL;

	क्रम_each_sg(req->src, sg, nents, i)
		sr->in.total_bytes += sg_dma_len(sg);

	sr->in.sg = req->src;
	sr->in.sgmap_cnt = nents;
	ret = create_sg_component(sr, &sr->in, sr->in.sgmap_cnt);
	अगर (ret)
		जाओ incomp_err;

	वापस 0;

incomp_err:
	dma_unmap_sg(dev, req->src, sg_nents(req->src), DMA_BIसूचीECTIONAL);
	sr->in.sgmap_cnt = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक dma_map_outbufs(काष्ठा nitrox_softreq *sr,
			   काष्ठा se_crypto_request *req)
अणु
	काष्ठा device *dev = DEV(sr->ndev);
	पूर्णांक nents, ret = 0;

	nents = dma_map_sg(dev, req->dst, sg_nents(req->dst),
			   DMA_BIसूचीECTIONAL);
	अगर (!nents)
		वापस -EINVAL;

	sr->out.sg = req->dst;
	sr->out.sgmap_cnt = nents;
	ret = create_sg_component(sr, &sr->out, sr->out.sgmap_cnt);
	अगर (ret)
		जाओ outcomp_map_err;

	वापस 0;

outcomp_map_err:
	dma_unmap_sg(dev, req->dst, sg_nents(req->dst), DMA_BIसूचीECTIONAL);
	sr->out.sgmap_cnt = 0;
	sr->out.sg = शून्य;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक softreq_map_iobuf(काष्ठा nitrox_softreq *sr,
				    काष्ठा se_crypto_request *creq)
अणु
	पूर्णांक ret;

	ret = dma_map_inbufs(sr, creq);
	अगर (ret)
		वापस ret;

	ret = dma_map_outbufs(sr, creq);
	अगर (ret)
		softreq_unmap_sgbufs(sr);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम backlog_list_add(काष्ठा nitrox_softreq *sr,
				    काष्ठा nitrox_cmdq *cmdq)
अणु
	INIT_LIST_HEAD(&sr->backlog);

	spin_lock_bh(&cmdq->backlog_qlock);
	list_add_tail(&sr->backlog, &cmdq->backlog_head);
	atomic_inc(&cmdq->backlog_count);
	atomic_set(&sr->status, REQ_BACKLOG);
	spin_unlock_bh(&cmdq->backlog_qlock);
पूर्ण

अटल अंतरभूत व्योम response_list_add(काष्ठा nitrox_softreq *sr,
				     काष्ठा nitrox_cmdq *cmdq)
अणु
	INIT_LIST_HEAD(&sr->response);

	spin_lock_bh(&cmdq->resp_qlock);
	list_add_tail(&sr->response, &cmdq->response_head);
	spin_unlock_bh(&cmdq->resp_qlock);
पूर्ण

अटल अंतरभूत व्योम response_list_del(काष्ठा nitrox_softreq *sr,
				     काष्ठा nitrox_cmdq *cmdq)
अणु
	spin_lock_bh(&cmdq->resp_qlock);
	list_del(&sr->response);
	spin_unlock_bh(&cmdq->resp_qlock);
पूर्ण

अटल काष्ठा nitrox_softreq *
get_first_response_entry(काष्ठा nitrox_cmdq *cmdq)
अणु
	वापस list_first_entry_or_null(&cmdq->response_head,
					काष्ठा nitrox_softreq, response);
पूर्ण

अटल अंतरभूत bool cmdq_full(काष्ठा nitrox_cmdq *cmdq, पूर्णांक qlen)
अणु
	अगर (atomic_inc_वापस(&cmdq->pending_count) > qlen) अणु
		atomic_dec(&cmdq->pending_count);
		/* sync with other cpus */
		smp_mb__after_atomic();
		वापस true;
	पूर्ण
	/* sync with other cpus */
	smp_mb__after_atomic();
	वापस false;
पूर्ण

/**
 * post_se_instr - Post SE inकाष्ठाion to Packet Input ring
 * @sr: Request काष्ठाure
 *
 * Returns 0 अगर successful or a negative error code,
 * अगर no space in ring.
 */
अटल व्योम post_se_instr(काष्ठा nitrox_softreq *sr,
			  काष्ठा nitrox_cmdq *cmdq)
अणु
	काष्ठा nitrox_device *ndev = sr->ndev;
	पूर्णांक idx;
	u8 *ent;

	spin_lock_bh(&cmdq->cmd_qlock);

	idx = cmdq->ग_लिखो_idx;
	/* copy the inकाष्ठाion */
	ent = cmdq->base + (idx * cmdq->instr_size);
	स_नकल(ent, &sr->instr, cmdq->instr_size);

	atomic_set(&sr->status, REQ_POSTED);
	response_list_add(sr, cmdq);
	sr->tstamp = jअगरfies;
	/* flush the command queue updates */
	dma_wmb();

	/* Ring करोorbell with count 1 */
	ग_लिखोq(1, cmdq->dbell_csr_addr);

	cmdq->ग_लिखो_idx = incr_index(idx, 1, ndev->qlen);

	spin_unlock_bh(&cmdq->cmd_qlock);

	/* increment the posted command count */
	atomic64_inc(&ndev->stats.posted);
पूर्ण

अटल पूर्णांक post_backlog_cmds(काष्ठा nitrox_cmdq *cmdq)
अणु
	काष्ठा nitrox_device *ndev = cmdq->ndev;
	काष्ठा nitrox_softreq *sr, *पंचांगp;
	पूर्णांक ret = 0;

	अगर (!atomic_पढ़ो(&cmdq->backlog_count))
		वापस 0;

	spin_lock_bh(&cmdq->backlog_qlock);

	list_क्रम_each_entry_safe(sr, पंचांगp, &cmdq->backlog_head, backlog) अणु
		/* submit until space available */
		अगर (unlikely(cmdq_full(cmdq, ndev->qlen))) अणु
			ret = -ENOSPC;
			अवरोध;
		पूर्ण
		/* delete from backlog list */
		list_del(&sr->backlog);
		atomic_dec(&cmdq->backlog_count);
		/* sync with other cpus */
		smp_mb__after_atomic();

		/* post the command */
		post_se_instr(sr, cmdq);
	पूर्ण
	spin_unlock_bh(&cmdq->backlog_qlock);

	वापस ret;
पूर्ण

अटल पूर्णांक nitrox_enqueue_request(काष्ठा nitrox_softreq *sr)
अणु
	काष्ठा nitrox_cmdq *cmdq = sr->cmdq;
	काष्ठा nitrox_device *ndev = sr->ndev;

	/* try to post backlog requests */
	post_backlog_cmds(cmdq);

	अगर (unlikely(cmdq_full(cmdq, ndev->qlen))) अणु
		अगर (!(sr->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
			/* increment drop count */
			atomic64_inc(&ndev->stats.dropped);
			वापस -ENOSPC;
		पूर्ण
		/* add to backlog list */
		backlog_list_add(sr, cmdq);
		वापस -EINPROGRESS;
	पूर्ण
	post_se_instr(sr, cmdq);

	वापस -EINPROGRESS;
पूर्ण

/**
 * nitrox_se_request - Send request to SE core
 * @ndev: NITROX device
 * @req: Crypto request
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक nitrox_process_se_request(काष्ठा nitrox_device *ndev,
			      काष्ठा se_crypto_request *req,
			      completion_t callback,
			      व्योम *cb_arg)
अणु
	काष्ठा nitrox_softreq *sr;
	dma_addr_t ctx_handle = 0;
	पूर्णांक qno, ret = 0;

	अगर (!nitrox_पढ़ोy(ndev))
		वापस -ENODEV;

	sr = kzalloc(माप(*sr), req->gfp);
	अगर (!sr)
		वापस -ENOMEM;

	sr->ndev = ndev;
	sr->flags = req->flags;
	sr->gfp = req->gfp;
	sr->callback = callback;
	sr->cb_arg = cb_arg;

	atomic_set(&sr->status, REQ_NOT_POSTED);

	sr->resp.orh = req->orh;
	sr->resp.completion = req->comp;

	ret = softreq_map_iobuf(sr, req);
	अगर (ret) अणु
		kमुक्त(sr);
		वापस ret;
	पूर्ण

	/* get the context handle */
	अगर (req->ctx_handle) अणु
		काष्ठा ctx_hdr *hdr;
		u8 *ctx_ptr;

		ctx_ptr = (u8 *)(uपूर्णांकptr_t)req->ctx_handle;
		hdr = (काष्ठा ctx_hdr *)(ctx_ptr - माप(काष्ठा ctx_hdr));
		ctx_handle = hdr->ctx_dma;
	पूर्ण

	/* select the queue */
	qno = smp_processor_id() % ndev->nr_queues;

	sr->cmdq = &ndev->pkt_inq[qno];

	/*
	 * 64-Byte Inकाष्ठाion Format
	 *
	 *  ----------------------
	 *  |      DPTR0         | 8 bytes
	 *  ----------------------
	 *  |  PKT_IN_INSTR_HDR  | 8 bytes
	 *  ----------------------
	 *  |    PKT_IN_HDR      | 16 bytes
	 *  ----------------------
	 *  |    SLC_INFO        | 16 bytes
	 *  ----------------------
	 *  |   Front data       | 16 bytes
	 *  ----------------------
	 */

	/* fill the packet inकाष्ठाion */
	/* word 0 */
	sr->instr.dptr0 = cpu_to_be64(sr->in.sgcomp_dma);

	/* word 1 */
	sr->instr.ih.value = 0;
	sr->instr.ih.s.g = 1;
	sr->instr.ih.s.gsz = sr->in.sgmap_cnt;
	sr->instr.ih.s.ssz = sr->out.sgmap_cnt;
	sr->instr.ih.s.fsz = FDATA_SIZE + माप(काष्ठा gphdr);
	sr->instr.ih.s.tlen = sr->instr.ih.s.fsz + sr->in.total_bytes;
	sr->instr.ih.bev = cpu_to_be64(sr->instr.ih.value);

	/* word 2 */
	sr->instr.irh.value[0] = 0;
	sr->instr.irh.s.uddl = MIN_UDD_LEN;
	/* context length in 64-bit words */
	sr->instr.irh.s.ctxl = (req->ctrl.s.ctxl / 8);
	/* offset from solicit base port 256 */
	sr->instr.irh.s.destport = SOLICIT_BASE_DPORT + qno;
	sr->instr.irh.s.ctxc = req->ctrl.s.ctxc;
	sr->instr.irh.s.arg = req->ctrl.s.arg;
	sr->instr.irh.s.opcode = req->opcode;
	sr->instr.irh.bev[0] = cpu_to_be64(sr->instr.irh.value[0]);

	/* word 3 */
	sr->instr.irh.s.ctxp = cpu_to_be64(ctx_handle);

	/* word 4 */
	sr->instr.slc.value[0] = 0;
	sr->instr.slc.s.ssz = sr->out.sgmap_cnt;
	sr->instr.slc.bev[0] = cpu_to_be64(sr->instr.slc.value[0]);

	/* word 5 */
	sr->instr.slc.s.rptr = cpu_to_be64(sr->out.sgcomp_dma);

	/*
	 * No conversion क्रम front data,
	 * It goes पूर्णांकo payload
	 * put GP Header in front data
	 */
	sr->instr.fdata[0] = *((u64 *)&req->gph);
	sr->instr.fdata[1] = 0;

	ret = nitrox_enqueue_request(sr);
	अगर (ret == -ENOSPC)
		जाओ send_fail;

	वापस ret;

send_fail:
	softreq_destroy(sr);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक cmd_समयout(अचिन्हित दीर्घ tstamp, अचिन्हित दीर्घ समयout)
अणु
	वापस समय_after_eq(jअगरfies, (tstamp + समयout));
पूर्ण

व्योम backlog_qflush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nitrox_cmdq *cmdq;

	cmdq = container_of(work, काष्ठा nitrox_cmdq, backlog_qflush);
	post_backlog_cmds(cmdq);
पूर्ण

अटल bool sr_completed(काष्ठा nitrox_softreq *sr)
अणु
	u64 orh = READ_ONCE(*sr->resp.orh);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);

	अगर ((orh != PENDING_SIG) && (orh & 0xff))
		वापस true;

	जबतक (READ_ONCE(*sr->resp.completion) == PENDING_SIG) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_err("comp not done\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * process_request_list - process completed requests
 * @ndev: N5 device
 * @qno: queue to operate
 *
 * Returns the number of responses processed.
 */
अटल व्योम process_response_list(काष्ठा nitrox_cmdq *cmdq)
अणु
	काष्ठा nitrox_device *ndev = cmdq->ndev;
	काष्ठा nitrox_softreq *sr;
	पूर्णांक req_completed = 0, err = 0, budget;
	completion_t callback;
	व्योम *cb_arg;

	/* check all pending requests */
	budget = atomic_पढ़ो(&cmdq->pending_count);

	जबतक (req_completed < budget) अणु
		sr = get_first_response_entry(cmdq);
		अगर (!sr)
			अवरोध;

		अगर (atomic_पढ़ो(&sr->status) != REQ_POSTED)
			अवरोध;

		/* check orh and completion bytes updates */
		अगर (!sr_completed(sr)) अणु
			/* request not completed, check क्रम समयout */
			अगर (!cmd_समयout(sr->tstamp, ndev->समयout))
				अवरोध;
			dev_err_ratelimited(DEV(ndev),
					    "Request timeout, orh 0x%016llx\n",
					    READ_ONCE(*sr->resp.orh));
		पूर्ण
		atomic_dec(&cmdq->pending_count);
		atomic64_inc(&ndev->stats.completed);
		/* sync with other cpus */
		smp_mb__after_atomic();
		/* हटाओ from response list */
		response_list_del(sr, cmdq);
		/* ORH error code */
		err = READ_ONCE(*sr->resp.orh) & 0xff;
		callback = sr->callback;
		cb_arg = sr->cb_arg;
		softreq_destroy(sr);
		अगर (callback)
			callback(cb_arg, err);

		req_completed++;
	पूर्ण
पूर्ण

/**
 * pkt_slc_resp_tasklet - post processing of SE responses
 */
व्योम pkt_slc_resp_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा nitrox_q_vector *qvec = (व्योम *)(uपूर्णांकptr_t)(data);
	काष्ठा nitrox_cmdq *cmdq = qvec->cmdq;
	जोड़ nps_pkt_slc_cnts slc_cnts;

	/* पढ़ो completion count */
	slc_cnts.value = पढ़ोq(cmdq->compl_cnt_csr_addr);
	/* resend the पूर्णांकerrupt अगर more work to करो */
	slc_cnts.s.resend = 1;

	process_response_list(cmdq);

	/*
	 * clear the पूर्णांकerrupt with resend bit enabled,
	 * MSI-X पूर्णांकerrupt generates अगर Completion count > Threshold
	 */
	ग_लिखोq(slc_cnts.value, cmdq->compl_cnt_csr_addr);

	अगर (atomic_पढ़ो(&cmdq->backlog_count))
		schedule_work(&cmdq->backlog_qflush);
पूर्ण
