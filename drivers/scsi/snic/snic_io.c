<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mempool.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "snic_io.h"
#समावेश "snic.h"
#समावेश "cq_enet_desc.h"
#समावेश "snic_fwint.h"

अटल व्योम
snic_wq_cmpl_frame_send(काष्ठा vnic_wq *wq,
			    काष्ठा cq_desc *cq_desc,
			    काष्ठा vnic_wq_buf *buf,
			    व्योम *opaque)
अणु
	काष्ठा snic *snic = svnic_dev_priv(wq->vdev);

	SNIC_BUG_ON(buf->os_buf == शून्य);

	अगर (snic_log_level & SNIC_DESC_LOGGING)
		SNIC_HOST_INFO(snic->shost,
			       "Ack received for snic_host_req %p.\n",
			       buf->os_buf);

	SNIC_TRC(snic->shost->host_no, 0, 0,
		 ((uदीर्घ)(buf->os_buf) - माप(काष्ठा snic_req_info)), 0, 0,
		 0);

	buf->os_buf = शून्य;
पूर्ण

अटल पूर्णांक
snic_wq_cmpl_handler_cont(काष्ठा vnic_dev *vdev,
			  काष्ठा cq_desc *cq_desc,
			  u8 type,
			  u16 q_num,
			  u16 cmpl_idx,
			  व्योम *opaque)
अणु
	काष्ठा snic *snic = svnic_dev_priv(vdev);
	अचिन्हित दीर्घ flags;

	SNIC_BUG_ON(q_num != 0);

	spin_lock_irqsave(&snic->wq_lock[q_num], flags);
	svnic_wq_service(&snic->wq[q_num],
			 cq_desc,
			 cmpl_idx,
			 snic_wq_cmpl_frame_send,
			 शून्य);
	spin_unlock_irqrestore(&snic->wq_lock[q_num], flags);

	वापस 0;
पूर्ण /* end of snic_cmpl_handler_cont */

पूर्णांक
snic_wq_cmpl_handler(काष्ठा snic *snic, पूर्णांक work_to_करो)
अणु
	अचिन्हित पूर्णांक work_करोne = 0;
	अचिन्हित पूर्णांक i;

	snic->s_stats.misc.last_ack_समय = jअगरfies;
	क्रम (i = 0; i < snic->wq_count; i++) अणु
		work_करोne += svnic_cq_service(&snic->cq[i],
					      work_to_करो,
					      snic_wq_cmpl_handler_cont,
					      शून्य);
	पूर्ण

	वापस work_करोne;
पूर्ण /* end of snic_wq_cmpl_handler */

व्योम
snic_मुक्त_wq_buf(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf)
अणु

	काष्ठा snic_host_req *req = buf->os_buf;
	काष्ठा snic *snic = svnic_dev_priv(wq->vdev);
	काष्ठा snic_req_info *rqi = शून्य;
	अचिन्हित दीर्घ flags;

	dma_unmap_single(&snic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_TO_DEVICE);

	rqi = req_to_rqi(req);
	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	अगर (list_empty(&rqi->list)) अणु
		spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
		जाओ end;
	पूर्ण

	SNIC_BUG_ON(rqi->list.next == शून्य); /* अगर not added to spl_cmd_list */
	list_del_init(&rqi->list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);

	अगर (rqi->sge_va) अणु
		snic_pci_unmap_rsp_buf(snic, rqi);
		kमुक्त((व्योम *)rqi->sge_va);
		rqi->sge_va = 0;
	पूर्ण
	snic_req_मुक्त(snic, rqi);
	SNIC_HOST_INFO(snic->shost, "snic_free_wq_buf .. freed.\n");

end:
	वापस;
पूर्ण

/* Criteria to select work queue in multi queue mode */
अटल पूर्णांक
snic_select_wq(काष्ठा snic *snic)
अणु
	/* No multi queue support क्रम now */
	BUILD_BUG_ON(SNIC_WQ_MAX > 1);

	वापस 0;
पूर्ण

अटल पूर्णांक
snic_wqdesc_avail(काष्ठा snic *snic, पूर्णांक q_num, पूर्णांक req_type)
अणु
	पूर्णांक nr_wqdesc = snic->config.wq_enet_desc_count;

	अगर (q_num > 0) अणु
		/*
		 * Multi Queue हाल, additional care is required.
		 * Per WQ active requests need to be मुख्यtained.
		 */
		SNIC_HOST_INFO(snic->shost, "desc_avail: Multi Queue case.\n");
		SNIC_BUG_ON(q_num > 0);

		वापस -1;
	पूर्ण

	nr_wqdesc -= atomic64_पढ़ो(&snic->s_stats.fw.actv_reqs);

	वापस ((req_type == SNIC_REQ_HBA_RESET) ? nr_wqdesc : nr_wqdesc - 1);
पूर्ण

पूर्णांक
snic_queue_wq_desc(काष्ठा snic *snic, व्योम *os_buf, u16 len)
अणु
	dma_addr_t pa = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा snic_fw_stats *fwstats = &snic->s_stats.fw;
	काष्ठा snic_host_req *req = (काष्ठा snic_host_req *) os_buf;
	दीर्घ act_reqs;
	दीर्घ desc_avail = 0;
	पूर्णांक q_num = 0;

	snic_prपूर्णांक_desc(__func__, os_buf, len);

	/* Map request buffer */
	pa = dma_map_single(&snic->pdev->dev, os_buf, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&snic->pdev->dev, pa)) अणु
		SNIC_HOST_ERR(snic->shost, "qdesc: PCI DMA Mapping Fail.\n");

		वापस -ENOMEM;
	पूर्ण

	req->req_pa = (uदीर्घ)pa;

	q_num = snic_select_wq(snic);

	spin_lock_irqsave(&snic->wq_lock[q_num], flags);
	desc_avail = snic_wqdesc_avail(snic, q_num, req->hdr.type);
	अगर (desc_avail <= 0) अणु
		dma_unmap_single(&snic->pdev->dev, pa, len, DMA_TO_DEVICE);
		req->req_pa = 0;
		spin_unlock_irqrestore(&snic->wq_lock[q_num], flags);
		atomic64_inc(&snic->s_stats.misc.wq_alloc_fail);
		SNIC_DBG("host = %d, WQ is Full\n", snic->shost->host_no);

		वापस -ENOMEM;
	पूर्ण

	snic_queue_wq_eth_desc(&snic->wq[q_num], os_buf, pa, len, 0, 0, 1);
	/*
	 * Update stats
	 * note: when multi queue enabled, fw actv_reqs should be per queue.
	 */
	act_reqs = atomic64_inc_वापस(&fwstats->actv_reqs);
	spin_unlock_irqrestore(&snic->wq_lock[q_num], flags);

	अगर (act_reqs > atomic64_पढ़ो(&fwstats->max_actv_reqs))
		atomic64_set(&fwstats->max_actv_reqs, act_reqs);

	वापस 0;
पूर्ण /* end of snic_queue_wq_desc() */

/*
 * snic_handle_untagged_req: Adds snic specअगरic requests to spl_cmd_list.
 * Purpose : Used during driver unload to clean up the requests.
 */
व्योम
snic_handle_untagged_req(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&rqi->list);

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	list_add_tail(&rqi->list, &snic->spl_cmd_list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
पूर्ण

/*
 * snic_req_init:
 * Allocates snic_req_info + snic_host_req + sgl data, and initializes.
 */
काष्ठा snic_req_info *
snic_req_init(काष्ठा snic *snic, पूर्णांक sg_cnt)
अणु
	u8 typ;
	काष्ठा snic_req_info *rqi = शून्य;

	typ = (sg_cnt <= SNIC_REQ_CACHE_DFLT_SGL) ?
		SNIC_REQ_CACHE_DFLT_SGL : SNIC_REQ_CACHE_MAX_SGL;

	rqi = mempool_alloc(snic->req_pool[typ], GFP_ATOMIC);
	अगर (!rqi) अणु
		atomic64_inc(&snic->s_stats.io.alloc_fail);
		SNIC_HOST_ERR(snic->shost,
			      "Failed to allocate memory from snic req pool id = %d\n",
			      typ);
		वापस rqi;
	पूर्ण

	स_रखो(rqi, 0, माप(*rqi));
	rqi->rq_pool_type = typ;
	rqi->start_समय = jअगरfies;
	rqi->req = (काष्ठा snic_host_req *) (rqi + 1);
	rqi->req_len = माप(काष्ठा snic_host_req);
	rqi->snic = snic;

	rqi->req = (काष्ठा snic_host_req *)(rqi + 1);

	अगर (sg_cnt == 0)
		जाओ end;

	rqi->req_len += (sg_cnt * माप(काष्ठा snic_sg_desc));

	अगर (sg_cnt > atomic64_पढ़ो(&snic->s_stats.io.max_sgl))
		atomic64_set(&snic->s_stats.io.max_sgl, sg_cnt);

	SNIC_BUG_ON(sg_cnt > SNIC_MAX_SG_DESC_CNT);
	atomic64_inc(&snic->s_stats.io.sgl_cnt[sg_cnt - 1]);

end:
	स_रखो(rqi->req, 0, rqi->req_len);

	/* pre initialization of init_ctx to support req_to_rqi */
	rqi->req->hdr.init_ctx = (uदीर्घ) rqi;

	SNIC_SCSI_DBG(snic->shost, "Req_alloc:rqi = %p allocatd.\n", rqi);

	वापस rqi;
पूर्ण /* end of snic_req_init */

/*
 * snic_पात_req_init : Inits पात request.
 */
काष्ठा snic_host_req *
snic_पात_req_init(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	काष्ठा snic_host_req *req = शून्य;

	SNIC_BUG_ON(!rqi);

	/* If पात to be issued second समय, then reuse */
	अगर (rqi->पात_req)
		वापस rqi->पात_req;


	req = mempool_alloc(snic->req_pool[SNIC_REQ_TM_CACHE], GFP_ATOMIC);
	अगर (!req) अणु
		SNIC_HOST_ERR(snic->shost, "abts:Failed to alloc tm req.\n");
		WARN_ON_ONCE(1);

		वापस शून्य;
	पूर्ण

	rqi->पात_req = req;
	स_रखो(req, 0, माप(काष्ठा snic_host_req));
	/* pre initialization of init_ctx to support req_to_rqi */
	req->hdr.init_ctx = (uदीर्घ) rqi;

	वापस req;
पूर्ण /* end of snic_पात_req_init */

/*
 * snic_dr_req_init : Inits device reset req
 */
काष्ठा snic_host_req *
snic_dr_req_init(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	काष्ठा snic_host_req *req = शून्य;

	SNIC_BUG_ON(!rqi);

	req = mempool_alloc(snic->req_pool[SNIC_REQ_TM_CACHE], GFP_ATOMIC);
	अगर (!req) अणु
		SNIC_HOST_ERR(snic->shost, "dr:Failed to alloc tm req.\n");
		WARN_ON_ONCE(1);

		वापस शून्य;
	पूर्ण

	SNIC_BUG_ON(rqi->dr_req != शून्य);
	rqi->dr_req = req;
	स_रखो(req, 0, माप(काष्ठा snic_host_req));
	/* pre initialization of init_ctx to support req_to_rqi */
	req->hdr.init_ctx = (uदीर्घ) rqi;

	वापस req;
पूर्ण /* end of snic_dr_req_init */

/* मुक्तs snic_req_info and snic_host_req */
व्योम
snic_req_मुक्त(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	SNIC_BUG_ON(rqi->req == rqi->पात_req);
	SNIC_BUG_ON(rqi->req == rqi->dr_req);
	SNIC_BUG_ON(rqi->sge_va != 0);

	SNIC_SCSI_DBG(snic->shost,
		      "Req_free:rqi %p:ioreq %p:abt %p:dr %p\n",
		      rqi, rqi->req, rqi->पात_req, rqi->dr_req);

	अगर (rqi->पात_req) अणु
		अगर (rqi->पात_req->req_pa)
			dma_unmap_single(&snic->pdev->dev,
					 rqi->पात_req->req_pa,
					 माप(काष्ठा snic_host_req),
					 DMA_TO_DEVICE);

		mempool_मुक्त(rqi->पात_req, snic->req_pool[SNIC_REQ_TM_CACHE]);
	पूर्ण

	अगर (rqi->dr_req) अणु
		अगर (rqi->dr_req->req_pa)
			dma_unmap_single(&snic->pdev->dev,
					 rqi->dr_req->req_pa,
					 माप(काष्ठा snic_host_req),
					 DMA_TO_DEVICE);

		mempool_मुक्त(rqi->dr_req, snic->req_pool[SNIC_REQ_TM_CACHE]);
	पूर्ण

	अगर (rqi->req->req_pa)
		dma_unmap_single(&snic->pdev->dev,
				 rqi->req->req_pa,
				 rqi->req_len,
				 DMA_TO_DEVICE);

	mempool_मुक्त(rqi, snic->req_pool[rqi->rq_pool_type]);
पूर्ण

व्योम
snic_pci_unmap_rsp_buf(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	काष्ठा snic_sg_desc *sgd;

	sgd = req_to_sgl(rqi_to_req(rqi));
	SNIC_BUG_ON(sgd[0].addr == 0);
	dma_unmap_single(&snic->pdev->dev,
			 le64_to_cpu(sgd[0].addr),
			 le32_to_cpu(sgd[0].len),
			 DMA_FROM_DEVICE);
पूर्ण

/*
 * snic_मुक्त_all_untagged_reqs: Walks through untagged reqs and मुक्तs them.
 */
व्योम
snic_मुक्त_all_untagged_reqs(काष्ठा snic *snic)
अणु
	काष्ठा snic_req_info *rqi;
	काष्ठा list_head *cur, *nxt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	list_क्रम_each_safe(cur, nxt, &snic->spl_cmd_list) अणु
		rqi = list_entry(cur, काष्ठा snic_req_info, list);
		list_del_init(&rqi->list);
		अगर (rqi->sge_va) अणु
			snic_pci_unmap_rsp_buf(snic, rqi);
			kमुक्त((व्योम *)rqi->sge_va);
			rqi->sge_va = 0;
		पूर्ण

		snic_req_मुक्त(snic, rqi);
	पूर्ण
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
पूर्ण

/*
 * snic_release_untagged_req : Unlinks the untagged req and मुक्तs it.
 */
व्योम
snic_release_untagged_req(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&snic->snic_lock, flags);
	अगर (snic->in_हटाओ) अणु
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		जाओ end;
	पूर्ण
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	अगर (list_empty(&rqi->list)) अणु
		spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
		जाओ end;
	पूर्ण
	list_del_init(&rqi->list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
	snic_req_मुक्त(snic, rqi);

end:
	वापस;
पूर्ण

/* dump buf in hex fmt */
व्योम
snic_hex_dump(अक्षर *pfx, अक्षर *data, पूर्णांक len)
अणु
	SNIC_INFO("%s Dumping Data of Len = %d\n", pfx, len);
	prपूर्णांक_hex_dump_bytes(pfx, DUMP_PREFIX_NONE, data, len);
पूर्ण

#घोषणा	LINE_BUFSZ	128	/* क्रम snic_prपूर्णांक_desc fn */
अटल व्योम
snic_dump_desc(स्थिर अक्षर *fn, अक्षर *os_buf, पूर्णांक len)
अणु
	काष्ठा snic_host_req *req = (काष्ठा snic_host_req *) os_buf;
	काष्ठा snic_fw_req *fwreq = (काष्ठा snic_fw_req *) os_buf;
	काष्ठा snic_req_info *rqi = शून्य;
	अक्षर line[LINE_BUFSZ] = अणु '\0' पूर्ण;
	अक्षर *cmd_str = शून्य;

	अगर (req->hdr.type >= SNIC_RSP_REPORT_TGTS_CMPL)
		rqi = (काष्ठा snic_req_info *) fwreq->hdr.init_ctx;
	अन्यथा
		rqi = (काष्ठा snic_req_info *) req->hdr.init_ctx;

	SNIC_BUG_ON(rqi == शून्य || rqi->req == शून्य);
	चयन (req->hdr.type) अणु
	हाल SNIC_REQ_REPORT_TGTS:
		cmd_str = "report-tgt : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_REQ_REPORT_TGTS :");
		अवरोध;

	हाल SNIC_REQ_ICMND:
		cmd_str = "icmnd : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_REQ_ICMND : 0x%x :",
			 req->u.icmnd.cdb[0]);
		अवरोध;

	हाल SNIC_REQ_ITMF:
		cmd_str = "itmf : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_REQ_ITMF :");
		अवरोध;

	हाल SNIC_REQ_HBA_RESET:
		cmd_str = "hba reset :";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_REQ_HBA_RESET :");
		अवरोध;

	हाल SNIC_REQ_EXCH_VER:
		cmd_str = "exch ver : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_REQ_EXCH_VER :");
		अवरोध;

	हाल SNIC_REQ_TGT_INFO:
		cmd_str = "tgt info : ";
		अवरोध;

	हाल SNIC_RSP_REPORT_TGTS_CMPL:
		cmd_str = "report tgt cmpl : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_RSP_REPORT_TGTS_CMPL :");
		अवरोध;

	हाल SNIC_RSP_ICMND_CMPL:
		cmd_str = "icmnd_cmpl : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_RSP_ICMND_CMPL : 0x%x :",
			 rqi->req->u.icmnd.cdb[0]);
		अवरोध;

	हाल SNIC_RSP_ITMF_CMPL:
		cmd_str = "itmf_cmpl : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_RSP_ITMF_CMPL :");
		अवरोध;

	हाल SNIC_RSP_HBA_RESET_CMPL:
		cmd_str = "hba_reset_cmpl : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_RSP_HBA_RESET_CMPL :");
		अवरोध;

	हाल SNIC_RSP_EXCH_VER_CMPL:
		cmd_str = "exch_ver_cmpl : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_RSP_EXCH_VER_CMPL :");
		अवरोध;

	हाल SNIC_MSG_ACK:
		cmd_str = "msg ack : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_MSG_ACK :");
		अवरोध;

	हाल SNIC_MSG_ASYNC_EVNOTIFY:
		cmd_str = "async notify : ";
		snम_लिखो(line, LINE_BUFSZ, "SNIC_MSG_ASYNC_EVNOTIFY :");
		अवरोध;

	शेष:
		cmd_str = "unknown : ";
		SNIC_BUG_ON(1);
		अवरोध;
	पूर्ण

	SNIC_INFO("%s:%s >>cmndid=%x:sg_cnt = %x:status = %x:ctx = %lx.\n",
		  fn, line, req->hdr.cmnd_id, req->hdr.sg_cnt, req->hdr.status,
		  req->hdr.init_ctx);

	/* Enable it, to dump byte stream */
	अगर (snic_log_level & 0x20)
		snic_hex_dump(cmd_str, os_buf, len);
पूर्ण /* end of __snic_prपूर्णांक_desc */

व्योम
snic_prपूर्णांक_desc(स्थिर अक्षर *fn, अक्षर *os_buf, पूर्णांक len)
अणु
	अगर (snic_log_level & SNIC_DESC_LOGGING)
		snic_dump_desc(fn, os_buf, len);
पूर्ण

व्योम
snic_calc_io_process_समय(काष्ठा snic *snic, काष्ठा snic_req_info *rqi)
अणु
	u64 duration;

	duration = jअगरfies - rqi->start_समय;

	अगर (duration > atomic64_पढ़ो(&snic->s_stats.io.max_समय))
		atomic64_set(&snic->s_stats.io.max_समय, duration);
पूर्ण
