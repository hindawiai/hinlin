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
#समावेश <linux/mempool.h>

#समावेश <scsi/scsi_tcq.h>

#समावेश "snic_disc.h"
#समावेश "snic.h"
#समावेश "snic_io.h"


/* snic target types */
अटल स्थिर अक्षर * स्थिर snic_tgt_type_str[] = अणु
	[SNIC_TGT_DAS] = "DAS",
	[SNIC_TGT_SAN] = "SAN",
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *
snic_tgt_type_to_str(पूर्णांक typ)
अणु
	वापस ((typ > SNIC_TGT_NONE && typ <= SNIC_TGT_SAN) ?
		 snic_tgt_type_str[typ] : "Unknown");
पूर्ण

अटल स्थिर अक्षर * स्थिर snic_tgt_state_str[] = अणु
	[SNIC_TGT_STAT_INIT]	= "INIT",
	[SNIC_TGT_STAT_ONLINE]	= "ONLINE",
	[SNIC_TGT_STAT_OFFLINE]	= "OFFLINE",
	[SNIC_TGT_STAT_DEL]	= "DELETION IN PROGRESS",
पूर्ण;

स्थिर अक्षर *
snic_tgt_state_to_str(पूर्णांक state)
अणु
	वापस ((state >= SNIC_TGT_STAT_INIT && state <= SNIC_TGT_STAT_DEL) ?
		snic_tgt_state_str[state] : "UNKNOWN");
पूर्ण

/*
 * Initiate report_tgt req desc
 */
अटल व्योम
snic_report_tgt_init(काष्ठा snic_host_req *req, u32 hid, u8 *buf, u32 len,
		     dma_addr_t rsp_buf_pa, uदीर्घ ctx)
अणु
	काष्ठा snic_sg_desc *sgd = शून्य;


	snic_io_hdr_enc(&req->hdr, SNIC_REQ_REPORT_TGTS, 0, SCSI_NO_TAG, hid,
			1, ctx);

	req->u.rpt_tgts.sg_cnt = cpu_to_le16(1);
	sgd = req_to_sgl(req);
	sgd[0].addr = cpu_to_le64(rsp_buf_pa);
	sgd[0].len = cpu_to_le32(len);
	sgd[0]._resvd = 0;
	req->u.rpt_tgts.sg_addr = cpu_to_le64((uदीर्घ)sgd);
पूर्ण

/*
 * snic_queue_report_tgt_req: Queues report target request.
 */
अटल पूर्णांक
snic_queue_report_tgt_req(काष्ठा snic *snic)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	u32 ntgts, buf_len = 0;
	u8 *buf = शून्य;
	dma_addr_t pa = 0;
	पूर्णांक ret = 0;

	rqi = snic_req_init(snic, 1);
	अगर (!rqi) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (snic->fwinfo.max_tgts)
		ntgts = min_t(u32, snic->fwinfo.max_tgts, snic->shost->max_id);
	अन्यथा
		ntgts = snic->shost->max_id;

	/* Allocate Response Buffer */
	SNIC_BUG_ON(ntgts == 0);
	buf_len = ntgts * माप(काष्ठा snic_tgt_id) + SNIC_SG_DESC_ALIGN;

	buf = kzalloc(buf_len, GFP_KERNEL|GFP_DMA);
	अगर (!buf) अणु
		snic_req_मुक्त(snic, rqi);
		SNIC_HOST_ERR(snic->shost, "Resp Buf Alloc Failed.\n");

		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	SNIC_BUG_ON((((अचिन्हित दीर्घ)buf) % SNIC_SG_DESC_ALIGN) != 0);

	pa = dma_map_single(&snic->pdev->dev, buf, buf_len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&snic->pdev->dev, pa)) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Rpt-tgt rspbuf %p: PCI DMA Mapping Failed\n",
			      buf);
		kमुक्त(buf);
		snic_req_मुक्त(snic, rqi);
		ret = -EINVAL;

		जाओ error;
	पूर्ण


	SNIC_BUG_ON(pa == 0);
	rqi->sge_va = (uदीर्घ) buf;

	snic_report_tgt_init(rqi->req,
			     snic->config.hid,
			     buf,
			     buf_len,
			     pa,
			     (uदीर्घ)rqi);

	snic_handle_untagged_req(snic, rqi);

	ret = snic_queue_wq_desc(snic, rqi->req, rqi->req_len);
	अगर (ret) अणु
		dma_unmap_single(&snic->pdev->dev, pa, buf_len,
				 DMA_FROM_DEVICE);
		kमुक्त(buf);
		rqi->sge_va = 0;
		snic_release_untagged_req(snic, rqi);
		SNIC_HOST_ERR(snic->shost, "Queuing Report Tgts Failed.\n");

		जाओ error;
	पूर्ण

	SNIC_DISC_DBG(snic->shost, "Report Targets Issued.\n");

	वापस ret;

error:
	SNIC_HOST_ERR(snic->shost,
		      "Queuing Report Targets Failed, err = %d\n",
		      ret);
	वापस ret;
पूर्ण /* end of snic_queue_report_tgt_req */

/* call पूर्णांकo SML */
अटल व्योम
snic_scsi_scan_tgt(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snic_tgt *tgt = container_of(work, काष्ठा snic_tgt, scan_work);
	काष्ठा Scsi_Host *shost = dev_to_shost(&tgt->dev);
	अचिन्हित दीर्घ flags;

	SNIC_HOST_INFO(shost, "Scanning Target id 0x%x\n", tgt->id);
	scsi_scan_target(&tgt->dev,
			 tgt->channel,
			 tgt->scsi_tgt_id,
			 SCAN_WILD_CARD,
			 SCSI_SCAN_RESCAN);

	spin_lock_irqsave(shost->host_lock, flags);
	tgt->flags &= ~SNIC_TGT_SCAN_PENDING;
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण /* end of snic_scsi_scan_tgt */

/*
 * snic_tgt_lookup :
 */
अटल काष्ठा snic_tgt *
snic_tgt_lookup(काष्ठा snic *snic, काष्ठा snic_tgt_id *tgtid)
अणु
	काष्ठा list_head *cur, *nxt;
	काष्ठा snic_tgt *tgt = शून्य;

	list_क्रम_each_safe(cur, nxt, &snic->disc.tgt_list) अणु
		tgt = list_entry(cur, काष्ठा snic_tgt, list);
		अगर (tgt->id == le32_to_cpu(tgtid->tgt_id))
			वापस tgt;
		tgt = शून्य;
	पूर्ण

	वापस tgt;
पूर्ण /* end of snic_tgt_lookup */

/*
 * snic_tgt_dev_release : Called on dropping last ref क्रम snic_tgt object
 */
व्योम
snic_tgt_dev_release(काष्ठा device *dev)
अणु
	काष्ठा snic_tgt *tgt = dev_to_tgt(dev);

	SNIC_HOST_INFO(snic_tgt_to_shost(tgt),
		       "Target Device ID %d (%s) Permanently Deleted.\n",
		       tgt->id,
		       dev_name(dev));

	SNIC_BUG_ON(!list_empty(&tgt->list));
	kमुक्त(tgt);
पूर्ण

/*
 * snic_tgt_del : work function to delete snic_tgt
 */
अटल व्योम
snic_tgt_del(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snic_tgt *tgt = container_of(work, काष्ठा snic_tgt, del_work);
	काष्ठा Scsi_Host *shost = snic_tgt_to_shost(tgt);

	अगर (tgt->flags & SNIC_TGT_SCAN_PENDING)
		scsi_flush_work(shost);

	/* Block IOs on child devices, stops new IOs */
	scsi_target_block(&tgt->dev);

	/* Cleanup IOs */
	snic_tgt_scsi_पात_io(tgt);

	/* Unblock IOs now, to flush अगर there are any. */
	scsi_target_unblock(&tgt->dev, SDEV_TRANSPORT_OFFLINE);

	/* Delete SCSI Target and sdevs */
	scsi_हटाओ_target(&tgt->dev);  /* ?? */
	device_del(&tgt->dev);
	put_device(&tgt->dev);
पूर्ण /* end of snic_tgt_del */

/* snic_tgt_create: checks क्रम existence of snic_tgt, अगर it करोesn't
 * it creates one.
 */
अटल काष्ठा snic_tgt *
snic_tgt_create(काष्ठा snic *snic, काष्ठा snic_tgt_id *tgtid)
अणु
	काष्ठा snic_tgt *tgt = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	tgt = snic_tgt_lookup(snic, tgtid);
	अगर (tgt) अणु
		/* update the inक्रमmation अगर required */
		वापस tgt;
	पूर्ण

	tgt = kzalloc(माप(*tgt), GFP_KERNEL);
	अगर (!tgt) अणु
		SNIC_HOST_ERR(snic->shost, "Failure to allocate snic_tgt.\n");
		ret = -ENOMEM;

		वापस tgt;
	पूर्ण

	INIT_LIST_HEAD(&tgt->list);
	tgt->id = le32_to_cpu(tgtid->tgt_id);
	tgt->channel = 0;

	SNIC_BUG_ON(le16_to_cpu(tgtid->tgt_type) > SNIC_TGT_SAN);
	tgt->tdata.typ = le16_to_cpu(tgtid->tgt_type);

	/*
	 * Plugging पूर्णांकo SML Device Tree
	 */
	tgt->tdata.disc_id = 0;
	tgt->state = SNIC_TGT_STAT_INIT;
	device_initialize(&tgt->dev);
	tgt->dev.parent = get_device(&snic->shost->shost_gendev);
	tgt->dev.release = snic_tgt_dev_release;
	INIT_WORK(&tgt->scan_work, snic_scsi_scan_tgt);
	INIT_WORK(&tgt->del_work, snic_tgt_del);
	चयन (tgt->tdata.typ) अणु
	हाल SNIC_TGT_DAS:
		dev_set_name(&tgt->dev, "snic_das_tgt:%d:%d-%d",
			     snic->shost->host_no, tgt->channel, tgt->id);
		अवरोध;

	हाल SNIC_TGT_SAN:
		dev_set_name(&tgt->dev, "snic_san_tgt:%d:%d-%d",
			     snic->shost->host_no, tgt->channel, tgt->id);
		अवरोध;

	शेष:
		SNIC_HOST_INFO(snic->shost, "Target type Unknown Detected.\n");
		dev_set_name(&tgt->dev, "snic_das_tgt:%d:%d-%d",
			     snic->shost->host_no, tgt->channel, tgt->id);
		अवरोध;
	पूर्ण

	spin_lock_irqsave(snic->shost->host_lock, flags);
	list_add_tail(&tgt->list, &snic->disc.tgt_list);
	tgt->scsi_tgt_id = snic->disc.nxt_tgt_id++;
	tgt->state = SNIC_TGT_STAT_ONLINE;
	spin_unlock_irqrestore(snic->shost->host_lock, flags);

	SNIC_HOST_INFO(snic->shost,
		       "Tgt %d, type = %s detected. Adding..\n",
		       tgt->id, snic_tgt_type_to_str(tgt->tdata.typ));

	ret = device_add(&tgt->dev);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Snic Tgt: device_add, with err = %d\n",
			      ret);

		put_device(&snic->shost->shost_gendev);
		kमुक्त(tgt);
		tgt = शून्य;

		वापस tgt;
	पूर्ण

	SNIC_HOST_INFO(snic->shost, "Scanning %s.\n", dev_name(&tgt->dev));

	scsi_queue_work(snic->shost, &tgt->scan_work);

	वापस tgt;
पूर्ण /* end of snic_tgt_create */

/* Handler क्रम discovery */
व्योम
snic_handle_tgt_disc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snic *snic = container_of(work, काष्ठा snic, tgt_work);
	काष्ठा snic_tgt_id *tgtid = शून्य;
	काष्ठा snic_tgt *tgt = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&snic->snic_lock, flags);
	अगर (snic->in_हटाओ) अणु
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		kमुक्त(snic->disc.rtgt_info);

		वापस;
	पूर्ण
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	mutex_lock(&snic->disc.mutex);
	/* Discover triggered during disc in progress */
	अगर (snic->disc.req_cnt) अणु
		snic->disc.state = SNIC_DISC_DONE;
		snic->disc.req_cnt = 0;
		mutex_unlock(&snic->disc.mutex);
		kमुक्त(snic->disc.rtgt_info);
		snic->disc.rtgt_info = शून्य;

		SNIC_HOST_INFO(snic->shost, "tgt_disc: Discovery restart.\n");
		/* Start Discovery Again */
		snic_disc_start(snic);

		वापस;
	पूर्ण

	tgtid = (काष्ठा snic_tgt_id *)snic->disc.rtgt_info;

	SNIC_BUG_ON(snic->disc.rtgt_cnt == 0 || tgtid == शून्य);

	क्रम (i = 0; i < snic->disc.rtgt_cnt; i++) अणु
		tgt = snic_tgt_create(snic, &tgtid[i]);
		अगर (!tgt) अणु
			पूर्णांक buf_sz = snic->disc.rtgt_cnt * माप(*tgtid);

			SNIC_HOST_ERR(snic->shost, "Failed to create tgt.\n");
			snic_hex_dump("rpt_tgt_rsp", (अक्षर *)tgtid, buf_sz);
			अवरोध;
		पूर्ण
	पूर्ण

	snic->disc.rtgt_info = शून्य;
	snic->disc.state = SNIC_DISC_DONE;
	mutex_unlock(&snic->disc.mutex);

	SNIC_HOST_INFO(snic->shost, "Discovery Completed.\n");

	kमुक्त(tgtid);
पूर्ण /* end of snic_handle_tgt_disc */


पूर्णांक
snic_report_tgt_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु

	u8 typ, cmpl_stat;
	u32 cmnd_id, hid, tgt_cnt = 0;
	uदीर्घ ctx;
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_tgt_id *tgtid;
	पूर्णांक i, ret = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &cmpl_stat, &cmnd_id, &hid, &ctx);
	rqi = (काष्ठा snic_req_info *) ctx;
	tgtid = (काष्ठा snic_tgt_id *) rqi->sge_va;

	tgt_cnt = le32_to_cpu(fwreq->u.rpt_tgts_cmpl.tgt_cnt);
	अगर (tgt_cnt == 0) अणु
		SNIC_HOST_ERR(snic->shost, "No Targets Found on this host.\n");
		ret = 1;

		जाओ end;
	पूर्ण

	/* prपूर्णांकing list of tarमाला_लो here */
	SNIC_HOST_INFO(snic->shost, "Target Count = %d\n", tgt_cnt);

	SNIC_BUG_ON(tgt_cnt > snic->fwinfo.max_tgts);

	क्रम (i = 0; i < tgt_cnt; i++)
		SNIC_HOST_INFO(snic->shost,
			       "Tgt id = 0x%x\n",
			       le32_to_cpu(tgtid[i].tgt_id));

	/*
	 * Queue work क्रम further processing,
	 * Response Buffer Memory is मुक्तd after creating tarमाला_लो
	 */
	snic->disc.rtgt_cnt = tgt_cnt;
	snic->disc.rtgt_info = (u8 *) tgtid;
	queue_work(snic_glob->event_q, &snic->tgt_work);
	ret = 0;

end:
	/* Unmap Response Buffer */
	snic_pci_unmap_rsp_buf(snic, rqi);
	अगर (ret)
		kमुक्त(tgtid);

	rqi->sge_va = 0;
	snic_release_untagged_req(snic, rqi);

	वापस ret;
पूर्ण /* end of snic_report_tgt_cmpl_handler */

/* Discovery init fn */
व्योम
snic_disc_init(काष्ठा snic_disc *disc)
अणु
	INIT_LIST_HEAD(&disc->tgt_list);
	mutex_init(&disc->mutex);
	disc->disc_id = 0;
	disc->nxt_tgt_id = 0;
	disc->state = SNIC_DISC_INIT;
	disc->req_cnt = 0;
	disc->rtgt_cnt = 0;
	disc->rtgt_info = शून्य;
	disc->cb = शून्य;
पूर्ण /* end of snic_disc_init */

/* Discovery, uninit fn */
व्योम
snic_disc_term(काष्ठा snic *snic)
अणु
	काष्ठा snic_disc *disc = &snic->disc;

	mutex_lock(&disc->mutex);
	अगर (disc->req_cnt) अणु
		disc->req_cnt = 0;
		SNIC_SCSI_DBG(snic->shost, "Terminating Discovery.\n");
	पूर्ण
	mutex_unlock(&disc->mutex);
पूर्ण

/*
 * snic_disc_start: Discovery Start ...
 */
पूर्णांक
snic_disc_start(काष्ठा snic *snic)
अणु
	काष्ठा snic_disc *disc = &snic->disc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	SNIC_SCSI_DBG(snic->shost, "Discovery Start.\n");

	spin_lock_irqsave(&snic->snic_lock, flags);
	अगर (snic->in_हटाओ) अणु
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		SNIC_ERR("snic driver removal in progress ...\n");
		ret = 0;

		वापस ret;
	पूर्ण
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	mutex_lock(&disc->mutex);
	अगर (disc->state == SNIC_DISC_PENDING) अणु
		disc->req_cnt++;
		mutex_unlock(&disc->mutex);

		वापस ret;
	पूर्ण
	disc->state = SNIC_DISC_PENDING;
	mutex_unlock(&disc->mutex);

	ret = snic_queue_report_tgt_req(snic);
	अगर (ret)
		SNIC_HOST_INFO(snic->shost, "Discovery Failed, err=%d.\n", ret);

	वापस ret;
पूर्ण /* end of snic_disc_start */

/*
 * snic_disc_work :
 */
व्योम
snic_handle_disc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snic *snic = container_of(work, काष्ठा snic, disc_work);
	पूर्णांक ret = 0;

	SNIC_HOST_INFO(snic->shost, "disc_work: Discovery\n");

	ret = snic_disc_start(snic);
	अगर (ret)
		जाओ disc_err;

disc_err:
	SNIC_HOST_ERR(snic->shost,
		      "disc_work: Discovery Failed w/ err = %d\n",
		      ret);
पूर्ण /* end of snic_disc_work */

/*
 * snic_tgt_del_all : cleanup all snic tarमाला_लो
 * Called on unbinding the पूर्णांकerface
 */
व्योम
snic_tgt_del_all(काष्ठा snic *snic)
अणु
	काष्ठा snic_tgt *tgt = शून्य;
	काष्ठा list_head *cur, *nxt;
	अचिन्हित दीर्घ flags;

	scsi_flush_work(snic->shost);

	mutex_lock(&snic->disc.mutex);
	spin_lock_irqsave(snic->shost->host_lock, flags);

	list_क्रम_each_safe(cur, nxt, &snic->disc.tgt_list) अणु
		tgt = list_entry(cur, काष्ठा snic_tgt, list);
		tgt->state = SNIC_TGT_STAT_DEL;
		list_del_init(&tgt->list);
		SNIC_HOST_INFO(snic->shost, "Tgt %d q'ing for del\n", tgt->id);
		queue_work(snic_glob->event_q, &tgt->del_work);
		tgt = शून्य;
	पूर्ण
	spin_unlock_irqrestore(snic->shost->host_lock, flags);
	mutex_unlock(&snic->disc.mutex);

	flush_workqueue(snic_glob->event_q);
पूर्ण /* end of snic_tgt_del_all */
