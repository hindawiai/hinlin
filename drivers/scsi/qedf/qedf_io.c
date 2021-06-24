<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "qedf.h"
#समावेश <scsi/scsi_tcq.h>

व्योम qedf_cmd_समयr_set(काष्ठा qedf_ctx *qedf, काष्ठा qedf_ioreq *io_req,
	अचिन्हित पूर्णांक समयr_msec)
अणु
	queue_delayed_work(qedf->समयr_work_queue, &io_req->समयout_work,
	    msecs_to_jअगरfies(समयr_msec));
पूर्ण

अटल व्योम qedf_cmd_समयout(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा qedf_ioreq *io_req =
	    container_of(work, काष्ठा qedf_ioreq, समयout_work.work);
	काष्ठा qedf_ctx *qedf;
	काष्ठा qedf_rport *fcport;

	अगर (io_req == शून्य) अणु
		QEDF_INFO(शून्य, QEDF_LOG_IO, "io_req is NULL.\n");
		वापस;
	पूर्ण

	fcport = io_req->fcport;
	अगर (io_req->fcport == शून्य) अणु
		QEDF_INFO(शून्य, QEDF_LOG_IO,  "fcport is NULL.\n");
		वापस;
	पूर्ण

	qedf = fcport->qedf;

	चयन (io_req->cmd_type) अणु
	हाल QEDF_ABTS:
		अगर (qedf == शून्य) अणु
			QEDF_INFO(शून्य, QEDF_LOG_IO,
				  "qedf is NULL for ABTS xid=0x%x.\n",
				  io_req->xid);
			वापस;
		पूर्ण

		QEDF_ERR((&qedf->dbg_ctx), "ABTS timeout, xid=0x%x.\n",
		    io_req->xid);
		/* Cleanup समयd out ABTS */
		qedf_initiate_cleanup(io_req, true);
		complete(&io_req->abts_करोne);

		/*
		 * Need to call kref_put क्रम reference taken when initiate_abts
		 * was called since abts_compl won't be called now that we've
		 * cleaned up the task.
		 */
		kref_put(&io_req->refcount, qedf_release_cmd);

		/* Clear in पात bit now that we're करोne with the command */
		clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);

		/*
		 * Now that the original I/O and the ABTS are complete see
		 * अगर we need to reconnect to the target.
		 */
		qedf_restart_rport(fcport);
		अवरोध;
	हाल QEDF_ELS:
		अगर (!qedf) अणु
			QEDF_INFO(शून्य, QEDF_LOG_IO,
				  "qedf is NULL for ELS xid=0x%x.\n",
				  io_req->xid);
			वापस;
		पूर्ण
		/* ELS request no दीर्घer outstanding since it समयd out */
		clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

		kref_get(&io_req->refcount);
		/*
		 * Don't attempt to clean an ELS समयout as any subseqeunt
		 * ABTS or cleanup requests just hang.  For now just मुक्त
		 * the resources of the original I/O and the RRQ
		 */
		QEDF_ERR(&(qedf->dbg_ctx), "ELS timeout, xid=0x%x.\n",
			  io_req->xid);
		qedf_initiate_cleanup(io_req, true);
		io_req->event = QEDF_IOREQ_EV_ELS_TMO;
		/* Call callback function to complete command */
		अगर (io_req->cb_func && io_req->cb_arg) अणु
			io_req->cb_func(io_req->cb_arg);
			io_req->cb_arg = शून्य;
		पूर्ण
		kref_put(&io_req->refcount, qedf_release_cmd);
		अवरोध;
	हाल QEDF_SEQ_CLEANUP:
		QEDF_ERR(&(qedf->dbg_ctx), "Sequence cleanup timeout, "
		    "xid=0x%x.\n", io_req->xid);
		qedf_initiate_cleanup(io_req, true);
		io_req->event = QEDF_IOREQ_EV_ELS_TMO;
		qedf_process_seq_cleanup_compl(qedf, शून्य, io_req);
		अवरोध;
	शेष:
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Hit default case, xid=0x%x.\n", io_req->xid);
		अवरोध;
	पूर्ण
पूर्ण

व्योम qedf_cmd_mgr_मुक्त(काष्ठा qedf_cmd_mgr *cmgr)
अणु
	काष्ठा io_bdt *bdt_info;
	काष्ठा qedf_ctx *qedf = cmgr->qedf;
	माप_प्रकार bd_tbl_sz;
	u16 min_xid = 0;
	u16 max_xid = (FCOE_PARAMS_NUM_TASKS - 1);
	पूर्णांक num_ios;
	पूर्णांक i;
	काष्ठा qedf_ioreq *io_req;

	num_ios = max_xid - min_xid + 1;

	/* Free fcoe_bdt_ctx काष्ठाures */
	अगर (!cmgr->io_bdt_pool) अणु
		QEDF_ERR(&qedf->dbg_ctx, "io_bdt_pool is NULL.\n");
		जाओ मुक्त_cmd_pool;
	पूर्ण

	bd_tbl_sz = QEDF_MAX_BDS_PER_CMD * माप(काष्ठा scsi_sge);
	क्रम (i = 0; i < num_ios; i++) अणु
		bdt_info = cmgr->io_bdt_pool[i];
		अगर (bdt_info->bd_tbl) अणु
			dma_मुक्त_coherent(&qedf->pdev->dev, bd_tbl_sz,
			    bdt_info->bd_tbl, bdt_info->bd_tbl_dma);
			bdt_info->bd_tbl = शून्य;
		पूर्ण
	पूर्ण

	/* Destroy io_bdt pool */
	क्रम (i = 0; i < num_ios; i++) अणु
		kमुक्त(cmgr->io_bdt_pool[i]);
		cmgr->io_bdt_pool[i] = शून्य;
	पूर्ण

	kमुक्त(cmgr->io_bdt_pool);
	cmgr->io_bdt_pool = शून्य;

मुक्त_cmd_pool:

	क्रम (i = 0; i < num_ios; i++) अणु
		io_req = &cmgr->cmds[i];
		kमुक्त(io_req->sgl_task_params);
		kमुक्त(io_req->task_params);
		/* Make sure we मुक्त per command sense buffer */
		अगर (io_req->sense_buffer)
			dma_मुक्त_coherent(&qedf->pdev->dev,
			    QEDF_SCSI_SENSE_BUFFERSIZE, io_req->sense_buffer,
			    io_req->sense_buffer_dma);
		cancel_delayed_work_sync(&io_req->rrq_work);
	पूर्ण

	/* Free command manager itself */
	vमुक्त(cmgr);
पूर्ण

अटल व्योम qedf_handle_rrq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ioreq *io_req =
	    container_of(work, काष्ठा qedf_ioreq, rrq_work.work);

	atomic_set(&io_req->state, QEDFC_CMD_ST_RRQ_ACTIVE);
	qedf_send_rrq(io_req);

पूर्ण

काष्ठा qedf_cmd_mgr *qedf_cmd_mgr_alloc(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा qedf_cmd_mgr *cmgr;
	काष्ठा io_bdt *bdt_info;
	काष्ठा qedf_ioreq *io_req;
	u16 xid;
	पूर्णांक i;
	पूर्णांक num_ios;
	u16 min_xid = 0;
	u16 max_xid = (FCOE_PARAMS_NUM_TASKS - 1);

	/* Make sure num_queues is alपढ़ोy set beक्रमe calling this function */
	अगर (!qedf->num_queues) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "num_queues is not set.\n");
		वापस शून्य;
	पूर्ण

	अगर (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Invalid min_xid 0x%x and "
			   "max_xid 0x%x.\n", min_xid, max_xid);
		वापस शून्य;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "min xid 0x%x, max xid "
		   "0x%x.\n", min_xid, max_xid);

	num_ios = max_xid - min_xid + 1;

	cmgr = vzalloc(माप(काष्ठा qedf_cmd_mgr));
	अगर (!cmgr) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Failed to alloc cmd mgr.\n");
		वापस शून्य;
	पूर्ण

	cmgr->qedf = qedf;
	spin_lock_init(&cmgr->lock);

	/*
	 * Initialize I/O request fields.
	 */
	xid = 0;

	क्रम (i = 0; i < num_ios; i++) अणु
		io_req = &cmgr->cmds[i];
		INIT_DELAYED_WORK(&io_req->समयout_work, qedf_cmd_समयout);

		io_req->xid = xid++;

		INIT_DELAYED_WORK(&io_req->rrq_work, qedf_handle_rrq);

		/* Allocate DMA memory to hold sense buffer */
		io_req->sense_buffer = dma_alloc_coherent(&qedf->pdev->dev,
		    QEDF_SCSI_SENSE_BUFFERSIZE, &io_req->sense_buffer_dma,
		    GFP_KERNEL);
		अगर (!io_req->sense_buffer) अणु
			QEDF_ERR(&qedf->dbg_ctx,
				 "Failed to alloc sense buffer.\n");
			जाओ mem_err;
		पूर्ण

		/* Allocate task parameters to pass to f/w init funcions */
		io_req->task_params = kzalloc(माप(*io_req->task_params),
					      GFP_KERNEL);
		अगर (!io_req->task_params) अणु
			QEDF_ERR(&(qedf->dbg_ctx),
				 "Failed to allocate task_params for xid=0x%x\n",
				 i);
			जाओ mem_err;
		पूर्ण

		/*
		 * Allocate scatter/gather list info to pass to f/w init
		 * functions.
		 */
		io_req->sgl_task_params = kzalloc(
		    माप(काष्ठा scsi_sgl_task_params), GFP_KERNEL);
		अगर (!io_req->sgl_task_params) अणु
			QEDF_ERR(&(qedf->dbg_ctx),
				 "Failed to allocate sgl_task_params for xid=0x%x\n",
				 i);
			जाओ mem_err;
		पूर्ण
	पूर्ण

	/* Allocate pool of io_bdts - one क्रम each qedf_ioreq */
	cmgr->io_bdt_pool = kदो_स्मृति_array(num_ios, माप(काष्ठा io_bdt *),
	    GFP_KERNEL);

	अगर (!cmgr->io_bdt_pool) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Failed to alloc io_bdt_pool.\n");
		जाओ mem_err;
	पूर्ण

	क्रम (i = 0; i < num_ios; i++) अणु
		cmgr->io_bdt_pool[i] = kदो_स्मृति(माप(काष्ठा io_bdt),
		    GFP_KERNEL);
		अगर (!cmgr->io_bdt_pool[i]) अणु
			QEDF_WARN(&(qedf->dbg_ctx),
				  "Failed to alloc io_bdt_pool[%d].\n", i);
			जाओ mem_err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_ios; i++) अणु
		bdt_info = cmgr->io_bdt_pool[i];
		bdt_info->bd_tbl = dma_alloc_coherent(&qedf->pdev->dev,
		    QEDF_MAX_BDS_PER_CMD * माप(काष्ठा scsi_sge),
		    &bdt_info->bd_tbl_dma, GFP_KERNEL);
		अगर (!bdt_info->bd_tbl) अणु
			QEDF_WARN(&(qedf->dbg_ctx),
				  "Failed to alloc bdt_tbl[%d].\n", i);
			जाओ mem_err;
		पूर्ण
	पूर्ण
	atomic_set(&cmgr->मुक्त_list_cnt, num_ios);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
	    "cmgr->free_list_cnt=%d.\n",
	    atomic_पढ़ो(&cmgr->मुक्त_list_cnt));

	वापस cmgr;

mem_err:
	qedf_cmd_mgr_मुक्त(cmgr);
	वापस शून्य;
पूर्ण

काष्ठा qedf_ioreq *qedf_alloc_cmd(काष्ठा qedf_rport *fcport, u8 cmd_type)
अणु
	काष्ठा qedf_ctx *qedf = fcport->qedf;
	काष्ठा qedf_cmd_mgr *cmd_mgr = qedf->cmd_mgr;
	काष्ठा qedf_ioreq *io_req = शून्य;
	काष्ठा io_bdt *bd_tbl;
	u16 xid;
	uपूर्णांक32_t मुक्त_sqes;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	मुक्त_sqes = atomic_पढ़ो(&fcport->मुक्त_sqes);

	अगर (!मुक्त_sqes) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, free_sqes=%d.\n ",
		    मुक्त_sqes);
		जाओ out_failed;
	पूर्ण

	/* Limit the number of outstanding R/W tasks */
	अगर ((atomic_पढ़ो(&fcport->num_active_ios) >=
	    NUM_RW_TASKS_PER_CONNECTION)) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, num_active_ios=%d.\n",
		    atomic_पढ़ो(&fcport->num_active_ios));
		जाओ out_failed;
	पूर्ण

	/* Limit global TIDs certain tasks */
	अगर (atomic_पढ़ो(&cmd_mgr->मुक्त_list_cnt) <= GBL_RSVD_TASKS) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, free_list_cnt=%d.\n",
		    atomic_पढ़ो(&cmd_mgr->मुक्त_list_cnt));
		जाओ out_failed;
	पूर्ण

	spin_lock_irqsave(&cmd_mgr->lock, flags);
	क्रम (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) अणु
		io_req = &cmd_mgr->cmds[cmd_mgr->idx];
		cmd_mgr->idx++;
		अगर (cmd_mgr->idx == FCOE_PARAMS_NUM_TASKS)
			cmd_mgr->idx = 0;

		/* Check to make sure command was previously मुक्तd */
		अगर (!io_req->alloc)
			अवरोध;
	पूर्ण

	अगर (i == FCOE_PARAMS_NUM_TASKS) अणु
		spin_unlock_irqrestore(&cmd_mgr->lock, flags);
		जाओ out_failed;
	पूर्ण

	अगर (test_bit(QEDF_CMD_सूचीTY, &io_req->flags))
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req found to be dirty ox_id = 0x%x.\n",
			 io_req->xid);

	/* Clear any flags now that we've पुनः_स्मृतिated the xid */
	io_req->flags = 0;
	io_req->alloc = 1;
	spin_unlock_irqrestore(&cmd_mgr->lock, flags);

	atomic_inc(&fcport->num_active_ios);
	atomic_dec(&fcport->मुक्त_sqes);
	xid = io_req->xid;
	atomic_dec(&cmd_mgr->मुक्त_list_cnt);

	io_req->cmd_mgr = cmd_mgr;
	io_req->fcport = fcport;

	/* Clear any stale sc_cmd back poपूर्णांकer */
	io_req->sc_cmd = शून्य;
	io_req->lun = -1;

	/* Hold the io_req against deletion */
	kref_init(&io_req->refcount);	/* ID: 001 */
	atomic_set(&io_req->state, QEDFC_CMD_ST_IO_ACTIVE);

	/* Bind io_bdt क्रम this io_req */
	/* Have a अटल link between io_req and io_bdt_pool */
	bd_tbl = io_req->bd_tbl = cmd_mgr->io_bdt_pool[xid];
	अगर (bd_tbl == शून्य) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "bd_tbl is NULL, xid=%x.\n", xid);
		kref_put(&io_req->refcount, qedf_release_cmd);
		जाओ out_failed;
	पूर्ण
	bd_tbl->io_req = io_req;
	io_req->cmd_type = cmd_type;
	io_req->पंचांग_flags = 0;

	/* Reset sequence offset data */
	io_req->rx_buf_off = 0;
	io_req->tx_buf_off = 0;
	io_req->rx_id = 0xffff; /* No OX_ID */

	वापस io_req;

out_failed:
	/* Record failure क्रम stats and वापस शून्य to caller */
	qedf->alloc_failures++;
	वापस शून्य;
पूर्ण

अटल व्योम qedf_मुक्त_mp_resc(काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा qedf_mp_req *mp_req = &(io_req->mp_req);
	काष्ठा qedf_ctx *qedf = io_req->fcport->qedf;
	uपूर्णांक64_t sz = माप(काष्ठा scsi_sge);

	/* clear पंचांग flags */
	अगर (mp_req->mp_req_bd) अणु
		dma_मुक्त_coherent(&qedf->pdev->dev, sz,
		    mp_req->mp_req_bd, mp_req->mp_req_bd_dma);
		mp_req->mp_req_bd = शून्य;
	पूर्ण
	अगर (mp_req->mp_resp_bd) अणु
		dma_मुक्त_coherent(&qedf->pdev->dev, sz,
		    mp_req->mp_resp_bd, mp_req->mp_resp_bd_dma);
		mp_req->mp_resp_bd = शून्य;
	पूर्ण
	अगर (mp_req->req_buf) अणु
		dma_मुक्त_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_req->req_buf, mp_req->req_buf_dma);
		mp_req->req_buf = शून्य;
	पूर्ण
	अगर (mp_req->resp_buf) अणु
		dma_मुक्त_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_req->resp_buf, mp_req->resp_buf_dma);
		mp_req->resp_buf = शून्य;
	पूर्ण
पूर्ण

व्योम qedf_release_cmd(काष्ठा kref *ref)
अणु
	काष्ठा qedf_ioreq *io_req =
	    container_of(ref, काष्ठा qedf_ioreq, refcount);
	काष्ठा qedf_cmd_mgr *cmd_mgr = io_req->cmd_mgr;
	काष्ठा qedf_rport *fcport = io_req->fcport;
	अचिन्हित दीर्घ flags;

	अगर (io_req->cmd_type == QEDF_SCSI_CMD) अणु
		QEDF_WARN(&fcport->qedf->dbg_ctx,
			  "Cmd released called without scsi_done called, io_req %p xid=0x%x.\n",
			  io_req, io_req->xid);
		WARN_ON(io_req->sc_cmd);
	पूर्ण

	अगर (io_req->cmd_type == QEDF_ELS ||
	    io_req->cmd_type == QEDF_TASK_MGMT_CMD)
		qedf_मुक्त_mp_resc(io_req);

	atomic_inc(&cmd_mgr->मुक्त_list_cnt);
	atomic_dec(&fcport->num_active_ios);
	atomic_set(&io_req->state, QEDF_CMD_ST_INACTIVE);
	अगर (atomic_पढ़ो(&fcport->num_active_ios) < 0) अणु
		QEDF_WARN(&(fcport->qedf->dbg_ctx), "active_ios < 0.\n");
		WARN_ON(1);
	पूर्ण

	/* Increment task retry identअगरier now that the request is released */
	io_req->task_retry_identअगरier++;
	io_req->fcport = शून्य;

	clear_bit(QEDF_CMD_सूचीTY, &io_req->flags);
	io_req->cpu = 0;
	spin_lock_irqsave(&cmd_mgr->lock, flags);
	io_req->fcport = शून्य;
	io_req->alloc = 0;
	spin_unlock_irqrestore(&cmd_mgr->lock, flags);
पूर्ण

अटल पूर्णांक qedf_map_sg(काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;
	काष्ठा Scsi_Host *host = sc->device->host;
	काष्ठा fc_lport *lport = shost_priv(host);
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	काष्ठा scsi_sge *bd = io_req->bd_tbl->bd_tbl;
	काष्ठा scatterlist *sg;
	पूर्णांक byte_count = 0;
	पूर्णांक sg_count = 0;
	पूर्णांक bd_count = 0;
	u32 sg_len;
	u64 addr;
	पूर्णांक i = 0;

	sg_count = dma_map_sg(&qedf->pdev->dev, scsi_sglist(sc),
	    scsi_sg_count(sc), sc->sc_data_direction);
	sg = scsi_sglist(sc);

	io_req->sge_type = QEDF_IOREQ_UNKNOWN_SGE;

	अगर (sg_count <= 8 || io_req->io_req_flags == QEDF_READ)
		io_req->sge_type = QEDF_IOREQ_FAST_SGE;

	scsi_क्रम_each_sg(sc, sg, sg_count, i) अणु
		sg_len = (u32)sg_dma_len(sg);
		addr = (u64)sg_dma_address(sg);

		/*
		 * Intermediate s/g element so check अगर start address
		 * is page aligned.  Only required क्रम ग_लिखोs and only अगर the
		 * number of scatter/gather elements is 8 or more.
		 */
		अगर (io_req->sge_type == QEDF_IOREQ_UNKNOWN_SGE && (i) &&
		    (i != (sg_count - 1)) && sg_len < QEDF_PAGE_SIZE)
			io_req->sge_type = QEDF_IOREQ_SLOW_SGE;

		bd[bd_count].sge_addr.lo = cpu_to_le32(U64_LO(addr));
		bd[bd_count].sge_addr.hi  = cpu_to_le32(U64_HI(addr));
		bd[bd_count].sge_len = cpu_to_le32(sg_len);

		bd_count++;
		byte_count += sg_len;
	पूर्ण

	/* To catch a हाल where FAST and SLOW nothing is set, set FAST */
	अगर (io_req->sge_type == QEDF_IOREQ_UNKNOWN_SGE)
		io_req->sge_type = QEDF_IOREQ_FAST_SGE;

	अगर (byte_count != scsi_bufflen(sc))
		QEDF_ERR(&(qedf->dbg_ctx), "byte_count = %d != "
			  "scsi_bufflen = %d, task_id = 0x%x.\n", byte_count,
			   scsi_bufflen(sc), io_req->xid);

	वापस bd_count;
पूर्ण

अटल पूर्णांक qedf_build_bd_list_from_sg(काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;
	काष्ठा scsi_sge *bd = io_req->bd_tbl->bd_tbl;
	पूर्णांक bd_count;

	अगर (scsi_sg_count(sc)) अणु
		bd_count = qedf_map_sg(io_req);
		अगर (bd_count == 0)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		bd_count = 0;
		bd[0].sge_addr.lo = bd[0].sge_addr.hi = 0;
		bd[0].sge_len = 0;
	पूर्ण
	io_req->bd_tbl->bd_valid = bd_count;

	वापस 0;
पूर्ण

अटल व्योम qedf_build_fcp_cmnd(काष्ठा qedf_ioreq *io_req,
				  काष्ठा fcp_cmnd *fcp_cmnd)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;

	/* fcp_cmnd is 32 bytes */
	स_रखो(fcp_cmnd, 0, FCP_CMND_LEN);

	/* 8 bytes: SCSI LUN info */
	पूर्णांक_to_scsilun(sc_cmd->device->lun,
			(काष्ठा scsi_lun *)&fcp_cmnd->fc_lun);

	/* 4 bytes: flag info */
	fcp_cmnd->fc_pri_ta = 0;
	fcp_cmnd->fc_पंचांग_flags = io_req->पंचांग_flags;
	fcp_cmnd->fc_flags = io_req->io_req_flags;
	fcp_cmnd->fc_cmdref = 0;

	/* Populate data direction */
	अगर (io_req->cmd_type == QEDF_TASK_MGMT_CMD) अणु
		fcp_cmnd->fc_flags |= FCP_CFL_RDDATA;
	पूर्ण अन्यथा अणु
		अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE)
			fcp_cmnd->fc_flags |= FCP_CFL_WRDATA;
		अन्यथा अगर (sc_cmd->sc_data_direction == DMA_FROM_DEVICE)
			fcp_cmnd->fc_flags |= FCP_CFL_RDDATA;
	पूर्ण

	fcp_cmnd->fc_pri_ta = FCP_PTA_SIMPLE;

	/* 16 bytes: CDB inक्रमmation */
	अगर (io_req->cmd_type != QEDF_TASK_MGMT_CMD)
		स_नकल(fcp_cmnd->fc_cdb, sc_cmd->cmnd, sc_cmd->cmd_len);

	/* 4 bytes: FCP data length */
	fcp_cmnd->fc_dl = htonl(io_req->data_xfer_len);
पूर्ण

अटल व्योम  qedf_init_task(काष्ठा qedf_rport *fcport, काष्ठा fc_lport *lport,
	काष्ठा qedf_ioreq *io_req, काष्ठा e4_fcoe_task_context *task_ctx,
	काष्ठा fcoe_wqe *sqe)
अणु
	क्रमागत fcoe_task_type task_type;
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा io_bdt *bd_tbl = io_req->bd_tbl;
	u8 fcp_cmnd[32];
	u32 पंचांगp_fcp_cmnd[8];
	पूर्णांक bd_count = 0;
	काष्ठा qedf_ctx *qedf = fcport->qedf;
	uपूर्णांक16_t cq_idx = smp_processor_id() % qedf->num_queues;
	काष्ठा regpair sense_data_buffer_phys_addr;
	u32 tx_io_size = 0;
	u32 rx_io_size = 0;
	पूर्णांक i, cnt;

	/* Note init_initiator_rw_fcoe_task स_रखोs the task context */
	io_req->task = task_ctx;
	स_रखो(task_ctx, 0, माप(काष्ठा e4_fcoe_task_context));
	स_रखो(io_req->task_params, 0, माप(काष्ठा fcoe_task_params));
	स_रखो(io_req->sgl_task_params, 0, माप(काष्ठा scsi_sgl_task_params));

	/* Set task type bassed on DMA directio of command */
	अगर (io_req->cmd_type == QEDF_TASK_MGMT_CMD) अणु
		task_type = FCOE_TASK_TYPE_READ_INITIATOR;
	पूर्ण अन्यथा अणु
		अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
			task_type = FCOE_TASK_TYPE_WRITE_INITIATOR;
			tx_io_size = io_req->data_xfer_len;
		पूर्ण अन्यथा अणु
			task_type = FCOE_TASK_TYPE_READ_INITIATOR;
			rx_io_size = io_req->data_xfer_len;
		पूर्ण
	पूर्ण

	/* Setup the fields क्रम fcoe_task_params */
	io_req->task_params->context = task_ctx;
	io_req->task_params->sqe = sqe;
	io_req->task_params->task_type = task_type;
	io_req->task_params->tx_io_size = tx_io_size;
	io_req->task_params->rx_io_size = rx_io_size;
	io_req->task_params->conn_cid = fcport->fw_cid;
	io_req->task_params->itid = io_req->xid;
	io_req->task_params->cq_rss_number = cq_idx;
	io_req->task_params->is_tape_device = fcport->dev_type;

	/* Fill in inक्रमmation क्रम scatter/gather list */
	अगर (io_req->cmd_type != QEDF_TASK_MGMT_CMD) अणु
		bd_count = bd_tbl->bd_valid;
		io_req->sgl_task_params->sgl = bd_tbl->bd_tbl;
		io_req->sgl_task_params->sgl_phys_addr.lo =
			U64_LO(bd_tbl->bd_tbl_dma);
		io_req->sgl_task_params->sgl_phys_addr.hi =
			U64_HI(bd_tbl->bd_tbl_dma);
		io_req->sgl_task_params->num_sges = bd_count;
		io_req->sgl_task_params->total_buffer_size =
		    scsi_bufflen(io_req->sc_cmd);
		अगर (io_req->sge_type == QEDF_IOREQ_SLOW_SGE)
			io_req->sgl_task_params->small_mid_sge = 1;
		अन्यथा
			io_req->sgl_task_params->small_mid_sge = 0;
	पूर्ण

	/* Fill in physical address of sense buffer */
	sense_data_buffer_phys_addr.lo = U64_LO(io_req->sense_buffer_dma);
	sense_data_buffer_phys_addr.hi = U64_HI(io_req->sense_buffer_dma);

	/* fill FCP_CMND IU */
	qedf_build_fcp_cmnd(io_req, (काष्ठा fcp_cmnd *)पंचांगp_fcp_cmnd);

	/* Swap fcp_cmnd since FC is big endian */
	cnt = माप(काष्ठा fcp_cmnd) / माप(u32);
	क्रम (i = 0; i < cnt; i++) अणु
		पंचांगp_fcp_cmnd[i] = cpu_to_be32(पंचांगp_fcp_cmnd[i]);
	पूर्ण
	स_नकल(fcp_cmnd, पंचांगp_fcp_cmnd, माप(काष्ठा fcp_cmnd));

	init_initiator_rw_fcoe_task(io_req->task_params,
				    io_req->sgl_task_params,
				    sense_data_buffer_phys_addr,
				    io_req->task_retry_identअगरier, fcp_cmnd);

	/* Increment SGL type counters */
	अगर (io_req->sge_type == QEDF_IOREQ_SLOW_SGE)
		qedf->slow_sge_ios++;
	अन्यथा
		qedf->fast_sge_ios++;
पूर्ण

व्योम qedf_init_mp_task(काष्ठा qedf_ioreq *io_req,
	काष्ठा e4_fcoe_task_context *task_ctx, काष्ठा fcoe_wqe *sqe)
अणु
	काष्ठा qedf_mp_req *mp_req = &(io_req->mp_req);
	काष्ठा qedf_rport *fcport = io_req->fcport;
	काष्ठा qedf_ctx *qedf = io_req->fcport->qedf;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा fcoe_tx_mid_path_params task_fc_hdr;
	काष्ठा scsi_sgl_task_params tx_sgl_task_params;
	काष्ठा scsi_sgl_task_params rx_sgl_task_params;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		  "Initializing MP task for cmd_type=%d\n",
		  io_req->cmd_type);

	qedf->control_requests++;

	स_रखो(&tx_sgl_task_params, 0, माप(काष्ठा scsi_sgl_task_params));
	स_रखो(&rx_sgl_task_params, 0, माप(काष्ठा scsi_sgl_task_params));
	स_रखो(task_ctx, 0, माप(काष्ठा e4_fcoe_task_context));
	स_रखो(&task_fc_hdr, 0, माप(काष्ठा fcoe_tx_mid_path_params));

	/* Setup the task from io_req क्रम easy reference */
	io_req->task = task_ctx;

	/* Setup the fields क्रम fcoe_task_params */
	io_req->task_params->context = task_ctx;
	io_req->task_params->sqe = sqe;
	io_req->task_params->task_type = FCOE_TASK_TYPE_MIDPATH;
	io_req->task_params->tx_io_size = io_req->data_xfer_len;
	/* rx_io_size tells the f/w how large a response buffer we have */
	io_req->task_params->rx_io_size = PAGE_SIZE;
	io_req->task_params->conn_cid = fcport->fw_cid;
	io_req->task_params->itid = io_req->xid;
	/* Return middle path commands on CQ 0 */
	io_req->task_params->cq_rss_number = 0;
	io_req->task_params->is_tape_device = fcport->dev_type;

	fc_hdr = &(mp_req->req_fc_hdr);
	/* Set OX_ID and RX_ID based on driver task id */
	fc_hdr->fh_ox_id = io_req->xid;
	fc_hdr->fh_rx_id = htons(0xffff);

	/* Set up FC header inक्रमmation */
	task_fc_hdr.parameter = fc_hdr->fh_parm_offset;
	task_fc_hdr.r_ctl = fc_hdr->fh_r_ctl;
	task_fc_hdr.type = fc_hdr->fh_type;
	task_fc_hdr.cs_ctl = fc_hdr->fh_cs_ctl;
	task_fc_hdr.df_ctl = fc_hdr->fh_df_ctl;
	task_fc_hdr.rx_id = fc_hdr->fh_rx_id;
	task_fc_hdr.ox_id = fc_hdr->fh_ox_id;

	/* Set up s/g list parameters क्रम request buffer */
	tx_sgl_task_params.sgl = mp_req->mp_req_bd;
	tx_sgl_task_params.sgl_phys_addr.lo = U64_LO(mp_req->mp_req_bd_dma);
	tx_sgl_task_params.sgl_phys_addr.hi = U64_HI(mp_req->mp_req_bd_dma);
	tx_sgl_task_params.num_sges = 1;
	/* Set PAGE_SIZE क्रम now since sg element is that size ??? */
	tx_sgl_task_params.total_buffer_size = io_req->data_xfer_len;
	tx_sgl_task_params.small_mid_sge = 0;

	/* Set up s/g list parameters क्रम request buffer */
	rx_sgl_task_params.sgl = mp_req->mp_resp_bd;
	rx_sgl_task_params.sgl_phys_addr.lo = U64_LO(mp_req->mp_resp_bd_dma);
	rx_sgl_task_params.sgl_phys_addr.hi = U64_HI(mp_req->mp_resp_bd_dma);
	rx_sgl_task_params.num_sges = 1;
	/* Set PAGE_SIZE क्रम now since sg element is that size ??? */
	rx_sgl_task_params.total_buffer_size = PAGE_SIZE;
	rx_sgl_task_params.small_mid_sge = 0;


	/*
	 * Last arg is 0 as previous code did not set that we wanted the
	 * fc header inक्रमmation.
	 */
	init_initiator_midpath_unsolicited_fcoe_task(io_req->task_params,
						     &task_fc_hdr,
						     &tx_sgl_task_params,
						     &rx_sgl_task_params, 0);
पूर्ण

/* Presumed that fcport->rport_lock is held */
u16 qedf_get_sqe_idx(काष्ठा qedf_rport *fcport)
अणु
	uपूर्णांक16_t total_sqe = (fcport->sq_mem_size)/(माप(काष्ठा fcoe_wqe));
	u16 rval;

	rval = fcport->sq_prod_idx;

	/* Adjust ring index */
	fcport->sq_prod_idx++;
	fcport->fw_sq_prod_idx++;
	अगर (fcport->sq_prod_idx == total_sqe)
		fcport->sq_prod_idx = 0;

	वापस rval;
पूर्ण

व्योम qedf_ring_करोorbell(काष्ठा qedf_rport *fcport)
अणु
	काष्ठा fcoe_db_data dbell = अणु 0 पूर्ण;

	dbell.agg_flags = 0;

	dbell.params |= DB_DEST_XCM << FCOE_DB_DATA_DEST_SHIFT;
	dbell.params |= DB_AGG_CMD_SET << FCOE_DB_DATA_AGG_CMD_SHIFT;
	dbell.params |= DQ_XCM_FCOE_SQ_PROD_CMD <<
	    FCOE_DB_DATA_AGG_VAL_SEL_SHIFT;

	dbell.sq_prod = fcport->fw_sq_prod_idx;
	/* wmb makes sure that the BDs data is updated beक्रमe updating the
	 * producer, otherwise FW may पढ़ो old data from the BDs.
	 */
	wmb();
	barrier();
	ग_लिखोl(*(u32 *)&dbell, fcport->p_करोorbell);
	/*
	 * Fence required to flush the ग_लिखो combined buffer, since another
	 * CPU may ग_लिखो to the same करोorbell address and data may be lost
	 * due to relaxed order nature of ग_लिखो combined bar.
	 */
	wmb();
पूर्ण

अटल व्योम qedf_trace_io(काष्ठा qedf_rport *fcport, काष्ठा qedf_ioreq *io_req,
			  पूर्णांक8_t direction)
अणु
	काष्ठा qedf_ctx *qedf = fcport->qedf;
	काष्ठा qedf_io_log *io_log;
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t op;

	spin_lock_irqsave(&qedf->io_trace_lock, flags);

	io_log = &qedf->io_trace_buf[qedf->io_trace_idx];
	io_log->direction = direction;
	io_log->task_id = io_req->xid;
	io_log->port_id = fcport->rdata->ids.port_id;
	io_log->lun = sc_cmd->device->lun;
	io_log->op = op = sc_cmd->cmnd[0];
	io_log->lba[0] = sc_cmd->cmnd[2];
	io_log->lba[1] = sc_cmd->cmnd[3];
	io_log->lba[2] = sc_cmd->cmnd[4];
	io_log->lba[3] = sc_cmd->cmnd[5];
	io_log->bufflen = scsi_bufflen(sc_cmd);
	io_log->sg_count = scsi_sg_count(sc_cmd);
	io_log->result = sc_cmd->result;
	io_log->jअगरfies = jअगरfies;
	io_log->refcount = kref_पढ़ो(&io_req->refcount);

	अगर (direction == QEDF_IO_TRACE_REQ) अणु
		/* For requests we only care abot the submission CPU */
		io_log->req_cpu = io_req->cpu;
		io_log->पूर्णांक_cpu = 0;
		io_log->rsp_cpu = 0;
	पूर्ण अन्यथा अगर (direction == QEDF_IO_TRACE_RSP) अणु
		io_log->req_cpu = io_req->cpu;
		io_log->पूर्णांक_cpu = io_req->पूर्णांक_cpu;
		io_log->rsp_cpu = smp_processor_id();
	पूर्ण

	io_log->sge_type = io_req->sge_type;

	qedf->io_trace_idx++;
	अगर (qedf->io_trace_idx == QEDF_IO_TRACE_SIZE)
		qedf->io_trace_idx = 0;

	spin_unlock_irqrestore(&qedf->io_trace_lock, flags);
पूर्ण

पूर्णांक qedf_post_io_req(काष्ठा qedf_rport *fcport, काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा Scsi_Host *host = sc_cmd->device->host;
	काष्ठा fc_lport *lport = shost_priv(host);
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	काष्ठा e4_fcoe_task_context *task_ctx;
	u16 xid;
	काष्ठा fcoe_wqe *sqe;
	u16 sqe_idx;

	/* Initialize rest of io_req fileds */
	io_req->data_xfer_len = scsi_bufflen(sc_cmd);
	sc_cmd->SCp.ptr = (अक्षर *)io_req;
	io_req->sge_type = QEDF_IOREQ_FAST_SGE; /* Assume fast SGL by शेष */

	/* Record which cpu this request is associated with */
	io_req->cpu = smp_processor_id();

	अगर (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		io_req->io_req_flags = QEDF_READ;
		qedf->input_requests++;
	पूर्ण अन्यथा अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		io_req->io_req_flags = QEDF_WRITE;
		qedf->output_requests++;
	पूर्ण अन्यथा अणु
		io_req->io_req_flags = 0;
		qedf->control_requests++;
	पूर्ण

	xid = io_req->xid;

	/* Build buffer descriptor list क्रम firmware from sg list */
	अगर (qedf_build_bd_list_from_sg(io_req)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "BD list creation failed.\n");
		/* Release cmd will release io_req, but sc_cmd is asचिन्हित */
		io_req->sc_cmd = शून्य;
		kref_put(&io_req->refcount, qedf_release_cmd);
		वापस -EAGAIN;
	पूर्ण

	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Session not offloaded yet.\n");
		/* Release cmd will release io_req, but sc_cmd is asचिन्हित */
		io_req->sc_cmd = शून्य;
		kref_put(&io_req->refcount, qedf_release_cmd);
		वापस -EINVAL;
	पूर्ण

	/* Record LUN number क्रम later use अगर we neeed them */
	io_req->lun = (पूर्णांक)sc_cmd->device->lun;

	/* Obtain मुक्त SQE */
	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));

	/* Get the task context */
	task_ctx = qedf_get_task_mem(&qedf->tasks, xid);
	अगर (!task_ctx) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "task_ctx is NULL, xid=%d.\n",
			   xid);
		/* Release cmd will release io_req, but sc_cmd is asचिन्हित */
		io_req->sc_cmd = शून्य;
		kref_put(&io_req->refcount, qedf_release_cmd);
		वापस -EINVAL;
	पूर्ण

	qedf_init_task(fcport, lport, io_req, task_ctx, sqe);

	/* Ring करोorbell */
	qedf_ring_करोorbell(fcport);

	/* Set that command is with the firmware now */
	set_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	अगर (qedf_io_tracing && io_req->sc_cmd)
		qedf_trace_io(fcport, io_req, QEDF_IO_TRACE_REQ);

	वापस false;
पूर्ण

पूर्णांक
qedf_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_lport *lport = shost_priv(host);
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा qedf_rport *fcport;
	काष्ठा qedf_ioreq *io_req;
	पूर्णांक rc = 0;
	पूर्णांक rval;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक num_sgs = 0;

	num_sgs = scsi_sg_count(sc_cmd);
	अगर (scsi_sg_count(sc_cmd) > QEDF_MAX_BDS_PER_CMD) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Number of SG elements %d exceeds what hardware limitation of %d.\n",
			 num_sgs, QEDF_MAX_BDS_PER_CMD);
		sc_cmd->result = DID_ERROR;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	अगर (test_bit(QEDF_UNLOADING, &qedf->flags) ||
	    test_bit(QEDF_DBG_STOP_IO, &qedf->flags)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Returning DNC as unloading or stop io, flags 0x%lx.\n",
			  qedf->flags);
		sc_cmd->result = DID_NO_CONNECT << 16;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	अगर (!qedf->pdev->msix_enabled) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Completing sc_cmd=%p DID_NO_CONNECT as MSI-X is not enabled.\n",
		    sc_cmd);
		sc_cmd->result = DID_NO_CONNECT << 16;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	rval = fc_remote_port_chkपढ़ोy(rport);
	अगर (rval) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "fc_remote_port_chkready failed=0x%x for port_id=0x%06x.\n",
			  rval, rport->port_id);
		sc_cmd->result = rval;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	/* Retry command अगर we are करोing a qed drain operation */
	अगर (test_bit(QEDF_DRAIN_ACTIVE, &qedf->flags)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Drain active.\n");
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ निकास_qcmd;
	पूर्ण

	अगर (lport->state != LPORT_ST_READY ||
	    atomic_पढ़ो(&qedf->link_state) != QEDF_LINK_UP) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Link down.\n");
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ निकास_qcmd;
	पूर्ण

	/* rport and tgt are allocated together, so tgt should be non-शून्य */
	fcport = (काष्ठा qedf_rport *)&rp[1];

	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		/*
		 * Session is not offloaded yet. Let SCSI-ml retry
		 * the command.
		 */
		rc = SCSI_MLQUEUE_TARGET_BUSY;
		जाओ निकास_qcmd;
	पूर्ण

	atomic_inc(&fcport->ios_to_queue);

	अगर (fcport->retry_delay_बारtamp) अणु
		/* Take fcport->rport_lock क्रम resetting the delay_बारtamp */
		spin_lock_irqsave(&fcport->rport_lock, flags);
		अगर (समय_after(jअगरfies, fcport->retry_delay_बारtamp)) अणु
			fcport->retry_delay_बारtamp = 0;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&fcport->rport_lock, flags);
			/* If retry_delay समयr is active, flow off the ML */
			rc = SCSI_MLQUEUE_TARGET_BUSY;
			atomic_dec(&fcport->ios_to_queue);
			जाओ निकास_qcmd;
		पूर्ण
		spin_unlock_irqrestore(&fcport->rport_lock, flags);
	पूर्ण

	io_req = qedf_alloc_cmd(fcport, QEDF_SCSI_CMD);
	अगर (!io_req) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		atomic_dec(&fcport->ios_to_queue);
		जाओ निकास_qcmd;
	पूर्ण

	io_req->sc_cmd = sc_cmd;

	/* Take fcport->rport_lock क्रम posting to fcport send queue */
	spin_lock_irqsave(&fcport->rport_lock, flags);
	अगर (qedf_post_io_req(fcport, io_req)) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Unable to post io_req\n");
		/* Return SQE to pool */
		atomic_inc(&fcport->मुक्त_sqes);
		rc = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	spin_unlock_irqrestore(&fcport->rport_lock, flags);
	atomic_dec(&fcport->ios_to_queue);

निकास_qcmd:
	वापस rc;
पूर्ण

अटल व्योम qedf_parse_fcp_rsp(काष्ठा qedf_ioreq *io_req,
				 काष्ठा fcoe_cqe_rsp_info *fcp_rsp)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा qedf_ctx *qedf = io_req->fcport->qedf;
	u8 rsp_flags = fcp_rsp->rsp_flags.flags;
	पूर्णांक fcp_sns_len = 0;
	पूर्णांक fcp_rsp_len = 0;
	uपूर्णांक8_t *rsp_info, *sense_data;

	io_req->fcp_status = FC_GOOD;
	io_req->fcp_resid = 0;
	अगर (rsp_flags & (FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER |
	    FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER))
		io_req->fcp_resid = fcp_rsp->fcp_resid;

	io_req->scsi_comp_flags = rsp_flags;
	CMD_SCSI_STATUS(sc_cmd) = io_req->cdb_status =
	    fcp_rsp->scsi_status_code;

	अगर (rsp_flags &
	    FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID)
		fcp_rsp_len = fcp_rsp->fcp_rsp_len;

	अगर (rsp_flags &
	    FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID)
		fcp_sns_len = fcp_rsp->fcp_sns_len;

	io_req->fcp_rsp_len = fcp_rsp_len;
	io_req->fcp_sns_len = fcp_sns_len;
	rsp_info = sense_data = io_req->sense_buffer;

	/* fetch fcp_rsp_code */
	अगर ((fcp_rsp_len == 4) || (fcp_rsp_len == 8)) अणु
		/* Only क्रम task management function */
		io_req->fcp_rsp_code = rsp_info[3];
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "fcp_rsp_code = %d\n", io_req->fcp_rsp_code);
		/* Adjust sense-data location. */
		sense_data += fcp_rsp_len;
	पूर्ण

	अगर (fcp_sns_len > SCSI_SENSE_BUFFERSIZE) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Truncating sense buffer\n");
		fcp_sns_len = SCSI_SENSE_BUFFERSIZE;
	पूर्ण

	/* The sense buffer can be शून्य क्रम TMF commands */
	अगर (sc_cmd->sense_buffer) अणु
		स_रखो(sc_cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		अगर (fcp_sns_len)
			स_नकल(sc_cmd->sense_buffer, sense_data,
			    fcp_sns_len);
	पूर्ण
पूर्ण

अटल व्योम qedf_unmap_sg_list(काष्ठा qedf_ctx *qedf, काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;

	अगर (io_req->bd_tbl->bd_valid && sc && scsi_sg_count(sc)) अणु
		dma_unmap_sg(&qedf->pdev->dev, scsi_sglist(sc),
		    scsi_sg_count(sc), sc->sc_data_direction);
		io_req->bd_tbl->bd_valid = 0;
	पूर्ण
पूर्ण

व्योम qedf_scsi_completion(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा scsi_cmnd *sc_cmd;
	काष्ठा fcoe_cqe_rsp_info *fcp_rsp;
	काष्ठा qedf_rport *fcport;
	पूर्णांक refcount;
	u16 scope, qualअगरier = 0;
	u8 fw_residual_flag = 0;
	अचिन्हित दीर्घ flags = 0;
	u16 chk_scope = 0;

	अगर (!io_req)
		वापस;
	अगर (!cqe)
		वापस;

	अगर (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_ABORT, &io_req->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req xid=0x%x already in cleanup or abort processing or already completed.\n",
			 io_req->xid);
		वापस;
	पूर्ण

	sc_cmd = io_req->sc_cmd;
	fcp_rsp = &cqe->cqe_info.rsp_info;

	अगर (!sc_cmd) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd is NULL!\n");
		वापस;
	पूर्ण

	अगर (!sc_cmd->SCp.ptr) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "SCp.ptr is NULL, returned in "
		    "another context.\n");
		वापस;
	पूर्ण

	अगर (!sc_cmd->device) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Device for sc_cmd %p is NULL.\n", sc_cmd);
		वापस;
	पूर्ण

	अगर (!sc_cmd->request) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd->request is NULL, "
		    "sc_cmd=%p.\n", sc_cmd);
		वापस;
	पूर्ण

	अगर (!sc_cmd->request->q) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "request->q is NULL so request "
		   "is not valid, sc_cmd=%p.\n", sc_cmd);
		वापस;
	पूर्ण

	fcport = io_req->fcport;

	/*
	 * When flush is active, let the cmds be completed from the cleanup
	 * context
	 */
	अगर (test_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags) ||
	    (test_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags) &&
	     sc_cmd->device->lun == (u64)fcport->lun_reset_lun)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Dropping good completion xid=0x%x as fcport is flushing",
			  io_req->xid);
		वापस;
	पूर्ण

	qedf_parse_fcp_rsp(io_req, fcp_rsp);

	qedf_unmap_sg_list(qedf, io_req);

	/* Check क्रम FCP transport error */
	अगर (io_req->fcp_rsp_len > 3 && io_req->fcp_rsp_code) अणु
		QEDF_ERR(&(qedf->dbg_ctx),
		    "FCP I/O protocol failure xid=0x%x fcp_rsp_len=%d "
		    "fcp_rsp_code=%d.\n", io_req->xid, io_req->fcp_rsp_len,
		    io_req->fcp_rsp_code);
		sc_cmd->result = DID_BUS_BUSY << 16;
		जाओ out;
	पूर्ण

	fw_residual_flag = GET_FIELD(cqe->cqe_info.rsp_info.fw_error_flags,
	    FCOE_CQE_RSP_INFO_FW_UNDERRUN);
	अगर (fw_residual_flag) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Firmware detected underrun: xid=0x%x fcp_rsp.flags=0x%02x fcp_resid=%d fw_residual=0x%x lba=%02x%02x%02x%02x.\n",
			 io_req->xid, fcp_rsp->rsp_flags.flags,
			 io_req->fcp_resid,
			 cqe->cqe_info.rsp_info.fw_residual, sc_cmd->cmnd[2],
			 sc_cmd->cmnd[3], sc_cmd->cmnd[4], sc_cmd->cmnd[5]);

		अगर (io_req->cdb_status == 0)
			sc_cmd->result = (DID_ERROR << 16) | io_req->cdb_status;
		अन्यथा
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;

		/*
		 * Set resid to the whole buffer length so we won't try to resue
		 * any previously data.
		 */
		scsi_set_resid(sc_cmd, scsi_bufflen(sc_cmd));
		जाओ out;
	पूर्ण

	चयन (io_req->fcp_status) अणु
	हाल FC_GOOD:
		अगर (io_req->cdb_status == 0) अणु
			/* Good I/O completion */
			sc_cmd->result = DID_OK << 16;
		पूर्ण अन्यथा अणु
			refcount = kref_पढ़ो(&io_req->refcount);
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
			    "%d:0:%d:%lld xid=0x%0x op=0x%02x "
			    "lba=%02x%02x%02x%02x cdb_status=%d "
			    "fcp_resid=0x%x refcount=%d.\n",
			    qedf->lport->host->host_no, sc_cmd->device->id,
			    sc_cmd->device->lun, io_req->xid,
			    sc_cmd->cmnd[0], sc_cmd->cmnd[2], sc_cmd->cmnd[3],
			    sc_cmd->cmnd[4], sc_cmd->cmnd[5],
			    io_req->cdb_status, io_req->fcp_resid,
			    refcount);
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;

			अगर (io_req->cdb_status == SAM_STAT_TASK_SET_FULL ||
			    io_req->cdb_status == SAM_STAT_BUSY) अणु
				/*
				 * Check whether we need to set retry_delay at
				 * all based on retry_delay module parameter
				 * and the status qualअगरier.
				 */

				/* Upper 2 bits */
				scope = fcp_rsp->retry_delay_समयr & 0xC000;
				/* Lower 14 bits */
				qualअगरier = fcp_rsp->retry_delay_समयr & 0x3FFF;

				अगर (qedf_retry_delay)
					chk_scope = 1;
				/* Record stats */
				अगर (io_req->cdb_status ==
				    SAM_STAT_TASK_SET_FULL)
					qedf->task_set_fulls++;
				अन्यथा
					qedf->busy++;
			पूर्ण
		पूर्ण
		अगर (io_req->fcp_resid)
			scsi_set_resid(sc_cmd, io_req->fcp_resid);

		अगर (chk_scope == 1) अणु
			अगर ((scope == 1 || scope == 2) &&
			    (qualअगरier > 0 && qualअगरier <= 0x3FEF)) अणु
				/* Check we करोn't go over the max */
				अगर (qualअगरier > QEDF_RETRY_DELAY_MAX) अणु
					qualअगरier = QEDF_RETRY_DELAY_MAX;
					QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
						  "qualifier = %d\n",
						  (fcp_rsp->retry_delay_समयr &
						  0x3FFF));
				पूर्ण
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "Scope = %d and qualifier = %d",
					  scope, qualअगरier);
				/*  Take fcport->rport_lock to
				 *  update the retry_delay_बारtamp
				 */
				spin_lock_irqsave(&fcport->rport_lock, flags);
				fcport->retry_delay_बारtamp =
					jअगरfies + (qualअगरier * HZ / 10);
				spin_unlock_irqrestore(&fcport->rport_lock,
						       flags);

			पूर्ण अन्यथा अणु
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "combination of scope = %d and qualifier = %d is not handled in qedf.\n",
					  scope, qualअगरier);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "fcp_status=%d.\n",
			   io_req->fcp_status);
		अवरोध;
	पूर्ण

out:
	अगर (qedf_io_tracing)
		qedf_trace_io(fcport, io_req, QEDF_IO_TRACE_RSP);

	/*
	 * We रुको till the end of the function to clear the
	 * outstanding bit in हाल we need to send an पात
	 */
	clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	io_req->sc_cmd = शून्य;
	sc_cmd->SCp.ptr =  शून्य;
	sc_cmd->scsi_करोne(sc_cmd);
	kref_put(&io_req->refcount, qedf_release_cmd);
पूर्ण

/* Return a SCSI command in some other context besides a normal completion */
व्योम qedf_scsi_करोne(काष्ठा qedf_ctx *qedf, काष्ठा qedf_ioreq *io_req,
	पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *sc_cmd;
	पूर्णांक refcount;

	अगर (!io_req) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "io_req is NULL\n");
		वापस;
	पूर्ण

	अगर (test_and_set_bit(QEDF_CMD_ERR_SCSI_DONE, &io_req->flags)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "io_req:%p scsi_done handling already done\n",
			  io_req);
		वापस;
	पूर्ण

	/*
	 * We will be करोne with this command after this call so clear the
	 * outstanding bit.
	 */
	clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	sc_cmd = io_req->sc_cmd;

	अगर (!sc_cmd) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd is NULL!\n");
		वापस;
	पूर्ण

	अगर (!virt_addr_valid(sc_cmd)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "sc_cmd=%p is not valid.", sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	अगर (!sc_cmd->SCp.ptr) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "SCp.ptr is NULL, returned in "
		    "another context.\n");
		वापस;
	पूर्ण

	अगर (!sc_cmd->device) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Device for sc_cmd %p is NULL.\n",
			 sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	अगर (!virt_addr_valid(sc_cmd->device)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Device pointer for sc_cmd %p is bad.\n", sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	अगर (!sc_cmd->sense_buffer) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "sc_cmd->sense_buffer for sc_cmd %p is NULL.\n",
			 sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	अगर (!virt_addr_valid(sc_cmd->sense_buffer)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "sc_cmd->sense_buffer for sc_cmd %p is bad.\n",
			 sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	अगर (!sc_cmd->scsi_करोne) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "sc_cmd->scsi_done for sc_cmd %p is NULL.\n",
			 sc_cmd);
		जाओ bad_scsi_ptr;
	पूर्ण

	qedf_unmap_sg_list(qedf, io_req);

	sc_cmd->result = result << 16;
	refcount = kref_पढ़ो(&io_req->refcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "%d:0:%d:%lld: Completing "
	    "sc_cmd=%p result=0x%08x op=0x%02x lba=0x%02x%02x%02x%02x, "
	    "allowed=%d retries=%d refcount=%d.\n",
	    qedf->lport->host->host_no, sc_cmd->device->id,
	    sc_cmd->device->lun, sc_cmd, sc_cmd->result, sc_cmd->cmnd[0],
	    sc_cmd->cmnd[2], sc_cmd->cmnd[3], sc_cmd->cmnd[4],
	    sc_cmd->cmnd[5], sc_cmd->allowed, sc_cmd->retries,
	    refcount);

	/*
	 * Set resid to the whole buffer length so we won't try to resue any
	 * previously पढ़ो data
	 */
	scsi_set_resid(sc_cmd, scsi_bufflen(sc_cmd));

	अगर (qedf_io_tracing)
		qedf_trace_io(io_req->fcport, io_req, QEDF_IO_TRACE_RSP);

	io_req->sc_cmd = शून्य;
	sc_cmd->SCp.ptr = शून्य;
	sc_cmd->scsi_करोne(sc_cmd);
	kref_put(&io_req->refcount, qedf_release_cmd);
	वापस;

bad_scsi_ptr:
	/*
	 * Clear the io_req->sc_cmd backpoपूर्णांकer so we करोn't try to process
	 * this again
	 */
	io_req->sc_cmd = शून्य;
	kref_put(&io_req->refcount, qedf_release_cmd);  /* ID: 001 */
पूर्ण

/*
 * Handle warning type CQE completions. This is मुख्यly used क्रम REC समयr
 * popping.
 */
व्योम qedf_process_warning_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	पूर्णांक rval, i;
	काष्ठा qedf_rport *fcport = io_req->fcport;
	u64 err_warn_bit_map;
	u8 err_warn = 0xff;

	अगर (!cqe) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "cqe is NULL for io_req %p xid=0x%x\n",
			  io_req, io_req->xid);
		वापस;
	पूर्ण

	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "Warning CQE, "
		  "xid=0x%x\n", io_req->xid);
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx),
		  "err_warn_bitmap=%08x:%08x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_biपंचांगap_hi),
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_biपंचांगap_lo));
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "tx_buff_off=%08x, "
		  "rx_buff_off=%08x, rx_id=%04x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.tx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_id));

	/* Normalize the error biपंचांगap value to an just an अचिन्हित पूर्णांक */
	err_warn_bit_map = (u64)
	    ((u64)cqe->cqe_info.err_info.err_warn_biपंचांगap_hi << 32) |
	    (u64)cqe->cqe_info.err_info.err_warn_biपंचांगap_lo;
	क्रम (i = 0; i < 64; i++) अणु
		अगर (err_warn_bit_map & (u64)((u64)1 << i)) अणु
			err_warn = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check अगर REC TOV expired अगर this is a tape device */
	अगर (fcport->dev_type == QEDF_RPORT_TYPE_TAPE) अणु
		अगर (err_warn ==
		    FCOE_WARNING_CODE_REC_TOV_TIMER_EXPIRATION) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "REC timer expired.\n");
			अगर (!test_bit(QEDF_CMD_SRR_SENT, &io_req->flags)) अणु
				io_req->rx_buf_off =
				    cqe->cqe_info.err_info.rx_buf_off;
				io_req->tx_buf_off =
				    cqe->cqe_info.err_info.tx_buf_off;
				io_req->rx_id = cqe->cqe_info.err_info.rx_id;
				rval = qedf_send_rec(io_req);
				/*
				 * We only want to पात the io_req अगर we
				 * can't queue the REC command as we want to
				 * keep the exchange खोलो क्रम recovery.
				 */
				अगर (rval)
					जाओ send_पात;
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

send_पात:
	init_completion(&io_req->abts_करोne);
	rval = qedf_initiate_abts(io_req, true);
	अगर (rval)
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
पूर्ण

/* Cleanup a command when we receive an error detection completion */
व्योम qedf_process_error_detect(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	पूर्णांक rval;

	अगर (!cqe) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "cqe is NULL for io_req %p\n", io_req);
		वापस;
	पूर्ण

	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "Error detection CQE, "
		  "xid=0x%x\n", io_req->xid);
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx),
		  "err_warn_bitmap=%08x:%08x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_biपंचांगap_hi),
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_biपंचांगap_lo));
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "tx_buff_off=%08x, "
		  "rx_buff_off=%08x, rx_id=%04x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.tx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_id));

	अगर (qedf->stop_io_on_error) अणु
		qedf_stop_all_io(qedf);
		वापस;
	पूर्ण

	init_completion(&io_req->abts_करोne);
	rval = qedf_initiate_abts(io_req, true);
	अगर (rval)
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
पूर्ण

अटल व्योम qedf_flush_els_req(काष्ठा qedf_ctx *qedf,
	काष्ठा qedf_ioreq *els_req)
अणु
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
	    "Flushing ELS request xid=0x%x refcount=%d.\n", els_req->xid,
	    kref_पढ़ो(&els_req->refcount));

	/*
	 * Need to distinguish this from a समयout when calling the
	 * els_req->cb_func.
	 */
	els_req->event = QEDF_IOREQ_EV_ELS_FLUSH;

	clear_bit(QEDF_CMD_OUTSTANDING, &els_req->flags);

	/* Cancel the समयr */
	cancel_delayed_work_sync(&els_req->समयout_work);

	/* Call callback function to complete command */
	अगर (els_req->cb_func && els_req->cb_arg) अणु
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = शून्य;
	पूर्ण

	/* Release kref क्रम original initiate_els */
	kref_put(&els_req->refcount, qedf_release_cmd);
पूर्ण

/* A value of -1 क्रम lun is a wild card that means flush all
 * active SCSI I/Os क्रम the target.
 */
व्योम qedf_flush_active_ios(काष्ठा qedf_rport *fcport, पूर्णांक lun)
अणु
	काष्ठा qedf_ioreq *io_req;
	काष्ठा qedf_ctx *qedf;
	काष्ठा qedf_cmd_mgr *cmd_mgr;
	पूर्णांक i, rc;
	अचिन्हित दीर्घ flags;
	पूर्णांक flush_cnt = 0;
	पूर्णांक रुको_cnt = 100;
	पूर्णांक refcount = 0;

	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "fcport is NULL\n");
		वापस;
	पूर्ण

	/* Check that fcport is still offloaded */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "fcport is no longer offloaded.\n");
		वापस;
	पूर्ण

	qedf = fcport->qedf;

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL.\n");
		वापस;
	पूर्ण

	/* Only रुको क्रम all commands to be queued in the Upload context */
	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags) &&
	    (lun == -1)) अणु
		जबतक (atomic_पढ़ो(&fcport->ios_to_queue)) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Waiting for %d I/Os to be queued\n",
				  atomic_पढ़ो(&fcport->ios_to_queue));
			अगर (रुको_cnt == 0) अणु
				QEDF_ERR(शून्य,
					 "%d IOs request could not be queued\n",
					 atomic_पढ़ो(&fcport->ios_to_queue));
			पूर्ण
			msleep(20);
			रुको_cnt--;
		पूर्ण
	पूर्ण

	cmd_mgr = qedf->cmd_mgr;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
		  "Flush active i/o's num=0x%x fcport=0x%p port_id=0x%06x scsi_id=%d.\n",
		  atomic_पढ़ो(&fcport->num_active_ios), fcport,
		  fcport->rdata->ids.port_id, fcport->rport->scsi_target_id);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Locking flush mutex.\n");

	mutex_lock(&qedf->flush_mutex);
	अगर (lun == -1) अणु
		set_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags);
	पूर्ण अन्यथा अणु
		set_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags);
		fcport->lun_reset_lun = lun;
	पूर्ण

	क्रम (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) अणु
		io_req = &cmd_mgr->cmds[i];

		अगर (!io_req)
			जारी;
		अगर (!io_req->fcport)
			जारी;

		spin_lock_irqsave(&cmd_mgr->lock, flags);

		अगर (io_req->alloc) अणु
			अगर (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags)) अणु
				अगर (io_req->cmd_type == QEDF_SCSI_CMD)
					QEDF_ERR(&qedf->dbg_ctx,
						 "Allocated but not queued, xid=0x%x\n",
						 io_req->xid);
			पूर्ण
			spin_unlock_irqrestore(&cmd_mgr->lock, flags);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&cmd_mgr->lock, flags);
			जारी;
		पूर्ण

		अगर (io_req->fcport != fcport)
			जारी;

		/* In हाल of ABTS, CMD_OUTSTANDING is cleared on ABTS response,
		 * but RRQ is still pending.
		 * Workaround: Within qedf_send_rrq, we check अगर the fcport is
		 * शून्य, and we drop the ref on the io_req to clean it up.
		 */
		अगर (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags)) अणु
			refcount = kref_पढ़ो(&io_req->refcount);
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Not outstanding, xid=0x%x, cmd_type=%d refcount=%d.\n",
				  io_req->xid, io_req->cmd_type, refcount);
			/* If RRQ work has been queue, try to cancel it and
			 * मुक्त the io_req
			 */
			अगर (atomic_पढ़ो(&io_req->state) ==
			    QEDFC_CMD_ST_RRQ_WAIT) अणु
				अगर (cancel_delayed_work_sync
				    (&io_req->rrq_work)) अणु
					QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
						  "Putting reference for pending RRQ work xid=0x%x.\n",
						  io_req->xid);
					/* ID: 003 */
					kref_put(&io_req->refcount,
						 qedf_release_cmd);
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण

		/* Only consider flushing ELS during target reset */
		अगर (io_req->cmd_type == QEDF_ELS &&
		    lun == -1) अणु
			rc = kref_get_unless_zero(&io_req->refcount);
			अगर (!rc) अणु
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for ELS io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				जारी;
			पूर्ण
			qedf_initiate_cleanup(io_req, false);
			flush_cnt++;
			qedf_flush_els_req(qedf, io_req);

			/*
			 * Release the kref and go back to the top of the
			 * loop.
			 */
			जाओ मुक्त_cmd;
		पूर्ण

		अगर (io_req->cmd_type == QEDF_ABTS) अणु
			/* ID: 004 */
			rc = kref_get_unless_zero(&io_req->refcount);
			अगर (!rc) अणु
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for abort io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				जारी;
			पूर्ण
			अगर (lun != -1 && io_req->lun != lun)
				जाओ मुक्त_cmd;

			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			    "Flushing abort xid=0x%x.\n", io_req->xid);

			अगर (cancel_delayed_work_sync(&io_req->rrq_work)) अणु
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "Putting ref for cancelled RRQ work xid=0x%x.\n",
					  io_req->xid);
				kref_put(&io_req->refcount, qedf_release_cmd);
			पूर्ण

			अगर (cancel_delayed_work_sync(&io_req->समयout_work)) अणु
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "Putting ref for cancelled tmo work xid=0x%x.\n",
					  io_req->xid);
				qedf_initiate_cleanup(io_req, true);
				/* Notअगरy eh_पात handler that ABTS is
				 * complete
				 */
				complete(&io_req->abts_करोne);
				clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);
				/* ID: 002 */
				kref_put(&io_req->refcount, qedf_release_cmd);
			पूर्ण
			flush_cnt++;
			जाओ मुक्त_cmd;
		पूर्ण

		अगर (!io_req->sc_cmd)
			जारी;
		अगर (!io_req->sc_cmd->device) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Device backpointer NULL for sc_cmd=%p.\n",
				  io_req->sc_cmd);
			/* Put reference क्रम non-existent scsi_cmnd */
			io_req->sc_cmd = शून्य;
			qedf_initiate_cleanup(io_req, false);
			kref_put(&io_req->refcount, qedf_release_cmd);
			जारी;
		पूर्ण
		अगर (lun > -1) अणु
			अगर (io_req->lun != lun)
				जारी;
		पूर्ण

		/*
		 * Use kref_get_unless_zero in the unlikely हाल the command
		 * we're about to flush was completed in the normal SCSI path
		 */
		rc = kref_get_unless_zero(&io_req->refcount);
		अगर (!rc) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "Could not get kref for "
			    "io_req=0x%p xid=0x%x\n", io_req, io_req->xid);
			जारी;
		पूर्ण

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Cleanup xid=0x%x.\n", io_req->xid);
		flush_cnt++;

		/* Cleanup task and वापस I/O mid-layer */
		qedf_initiate_cleanup(io_req, true);

मुक्त_cmd:
		kref_put(&io_req->refcount, qedf_release_cmd);	/* ID: 004 */
	पूर्ण

	रुको_cnt = 60;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
		  "Flushed 0x%x I/Os, active=0x%x.\n",
		  flush_cnt, atomic_पढ़ो(&fcport->num_active_ios));
	/* Only रुको क्रम all commands to complete in the Upload context */
	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags) &&
	    (lun == -1)) अणु
		जबतक (atomic_पढ़ो(&fcport->num_active_ios)) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Flushed 0x%x I/Os, active=0x%x cnt=%d.\n",
				  flush_cnt,
				  atomic_पढ़ो(&fcport->num_active_ios),
				  रुको_cnt);
			अगर (रुको_cnt == 0) अणु
				QEDF_ERR(&qedf->dbg_ctx,
					 "Flushed %d I/Os, active=%d.\n",
					 flush_cnt,
					 atomic_पढ़ो(&fcport->num_active_ios));
				क्रम (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) अणु
					io_req = &cmd_mgr->cmds[i];
					अगर (io_req->fcport &&
					    io_req->fcport == fcport) अणु
						refcount =
						kref_पढ़ो(&io_req->refcount);
						set_bit(QEDF_CMD_सूचीTY,
							&io_req->flags);
						QEDF_ERR(&qedf->dbg_ctx,
							 "Outstanding io_req =%p xid=0x%x flags=0x%lx, sc_cmd=%p refcount=%d cmd_type=%d.\n",
							 io_req, io_req->xid,
							 io_req->flags,
							 io_req->sc_cmd,
							 refcount,
							 io_req->cmd_type);
					पूर्ण
				पूर्ण
				WARN_ON(1);
				अवरोध;
			पूर्ण
			msleep(500);
			रुको_cnt--;
		पूर्ण
	पूर्ण

	clear_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags);
	clear_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Unlocking flush mutex.\n");
	mutex_unlock(&qedf->flush_mutex);
पूर्ण

/*
 * Initiate a ABTS middle path command. Note that we करोn't have to initialize
 * the task context क्रम an ABTS task.
 */
पूर्णांक qedf_initiate_abts(काष्ठा qedf_ioreq *io_req, bool वापस_scsi_cmd_on_abts)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा qedf_rport *fcport = io_req->fcport;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा qedf_ctx *qedf;
	u16 xid;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_wqe *sqe;
	u16 sqe_idx;
	पूर्णांक refcount = 0;

	/* Sanity check qedf_rport beक्रमe dereferencing any poपूर्णांकers */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "tgt not offloaded\n");
		rc = 1;
		जाओ out;
	पूर्ण

	qedf = fcport->qedf;
	rdata = fcport->rdata;

	अगर (!rdata || !kref_get_unless_zero(&rdata->kref)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "stale rport\n");
		rc = 1;
		जाओ out;
	पूर्ण

	lport = qedf->lport;

	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "link is not ready\n");
		rc = 1;
		जाओ drop_rdata_kref;
	पूर्ण

	अगर (atomic_पढ़ो(&qedf->link_करोwn_पंचांगo_valid) > 0) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "link_down_tmo active.\n");
		rc = 1;
		जाओ drop_rdata_kref;
	पूर्ण

	/* Ensure room on SQ */
	अगर (!atomic_पढ़ो(&fcport->मुक्त_sqes)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "No SQ entries available\n");
		rc = 1;
		जाओ drop_rdata_kref;
	पूर्ण

	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "fcport is uploading.\n");
		rc = 1;
		जाओ drop_rdata_kref;
	पूर्ण

	अगर (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_ABORT, &io_req->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req xid=0x%x sc_cmd=%p already in cleanup or abort processing or already completed.\n",
			 io_req->xid, io_req->sc_cmd);
		rc = 1;
		जाओ drop_rdata_kref;
	पूर्ण

	kref_get(&io_req->refcount);

	xid = io_req->xid;
	qedf->control_requests++;
	qedf->packet_पातs++;

	/* Set the command type to पात */
	io_req->cmd_type = QEDF_ABTS;
	io_req->वापस_scsi_cmd_on_abts = वापस_scsi_cmd_on_abts;

	set_bit(QEDF_CMD_IN_ABORT, &io_req->flags);
	refcount = kref_पढ़ो(&io_req->refcount);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_SCSI_TM,
		  "ABTS io_req xid = 0x%x refcount=%d\n",
		  xid, refcount);

	qedf_cmd_समयr_set(qedf, io_req, QEDF_ABORT_TIMEOUT);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));
	io_req->task_params->sqe = sqe;

	init_initiator_पात_fcoe_task(io_req->task_params);
	qedf_ring_करोorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);

drop_rdata_kref:
	kref_put(&rdata->kref, fc_rport_destroy);
out:
	वापस rc;
पूर्ण

व्योम qedf_process_abts_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	uपूर्णांक32_t r_ctl;
	पूर्णांक rc;
	काष्ठा qedf_rport *fcport = io_req->fcport;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM, "Entered with xid = "
		   "0x%x cmd_type = %d\n", io_req->xid, io_req->cmd_type);

	r_ctl = cqe->cqe_info.abts_info.r_ctl;

	/* This was added at a poपूर्णांक when we were scheduling abts_compl &
	 * cleanup_compl on dअगरferent CPUs and there was a possibility of
	 * the io_req to be मुक्तd from the other context beक्रमe we got here.
	 */
	अगर (!fcport) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Dropping ABTS completion xid=0x%x as fcport is NULL",
			  io_req->xid);
		वापस;
	पूर्ण

	/*
	 * When flush is active, let the cmds be completed from the cleanup
	 * context
	 */
	अगर (test_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags) ||
	    test_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Dropping ABTS completion xid=0x%x as fcport is flushing",
			  io_req->xid);
		वापस;
	पूर्ण

	अगर (!cancel_delayed_work(&io_req->समयout_work)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Wasn't able to cancel abts timeout work.\n");
	पूर्ण

	चयन (r_ctl) अणु
	हाल FC_RCTL_BA_ACC:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM,
		    "ABTS response - ACC Send RRQ after R_A_TOV\n");
		io_req->event = QEDF_IOREQ_EV_ABORT_SUCCESS;
		rc = kref_get_unless_zero(&io_req->refcount);	/* ID: 003 */
		अगर (!rc) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_SCSI_TM,
				  "kref is already zero so ABTS was already completed or flushed xid=0x%x.\n",
				  io_req->xid);
			वापस;
		पूर्ण
		/*
		 * Dont release this cmd yet. It will be relesed
		 * after we get RRQ response
		 */
		queue_delayed_work(qedf->dpc_wq, &io_req->rrq_work,
		    msecs_to_jअगरfies(qedf->lport->r_a_tov));
		atomic_set(&io_req->state, QEDFC_CMD_ST_RRQ_WAIT);
		अवरोध;
	/* For error हालs let the cleanup वापस the command */
	हाल FC_RCTL_BA_RJT:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM,
		   "ABTS response - RJT\n");
		io_req->event = QEDF_IOREQ_EV_ABORT_FAILED;
		अवरोध;
	शेष:
		QEDF_ERR(&(qedf->dbg_ctx), "Unknown ABTS response\n");
		अवरोध;
	पूर्ण

	clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);

	अगर (io_req->sc_cmd) अणु
		अगर (!io_req->वापस_scsi_cmd_on_abts)
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_SCSI_TM,
				  "Not call scsi_done for xid=0x%x.\n",
				  io_req->xid);
		अगर (io_req->वापस_scsi_cmd_on_abts)
			qedf_scsi_करोne(qedf, io_req, DID_ERROR);
	पूर्ण

	/* Notअगरy eh_पात handler that ABTS is complete */
	complete(&io_req->abts_करोne);

	kref_put(&io_req->refcount, qedf_release_cmd);
पूर्ण

पूर्णांक qedf_init_mp_req(काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा qedf_mp_req *mp_req;
	काष्ठा scsi_sge *mp_req_bd;
	काष्ठा scsi_sge *mp_resp_bd;
	काष्ठा qedf_ctx *qedf = io_req->fcport->qedf;
	dma_addr_t addr;
	uपूर्णांक64_t sz;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_MP_REQ, "Entered.\n");

	mp_req = (काष्ठा qedf_mp_req *)&(io_req->mp_req);
	स_रखो(mp_req, 0, माप(काष्ठा qedf_mp_req));

	अगर (io_req->cmd_type != QEDF_ELS) अणु
		mp_req->req_len = माप(काष्ठा fcp_cmnd);
		io_req->data_xfer_len = mp_req->req_len;
	पूर्ण अन्यथा
		mp_req->req_len = io_req->data_xfer_len;

	mp_req->req_buf = dma_alloc_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
	    &mp_req->req_buf_dma, GFP_KERNEL);
	अगर (!mp_req->req_buf) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP req buffer\n");
		qedf_मुक्त_mp_resc(io_req);
		वापस -ENOMEM;
	पूर्ण

	mp_req->resp_buf = dma_alloc_coherent(&qedf->pdev->dev,
	    QEDF_PAGE_SIZE, &mp_req->resp_buf_dma, GFP_KERNEL);
	अगर (!mp_req->resp_buf) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc TM resp "
			  "buffer\n");
		qedf_मुक्त_mp_resc(io_req);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate and map mp_req_bd and mp_resp_bd */
	sz = माप(काष्ठा scsi_sge);
	mp_req->mp_req_bd = dma_alloc_coherent(&qedf->pdev->dev, sz,
	    &mp_req->mp_req_bd_dma, GFP_KERNEL);
	अगर (!mp_req->mp_req_bd) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP req bd\n");
		qedf_मुक्त_mp_resc(io_req);
		वापस -ENOMEM;
	पूर्ण

	mp_req->mp_resp_bd = dma_alloc_coherent(&qedf->pdev->dev, sz,
	    &mp_req->mp_resp_bd_dma, GFP_KERNEL);
	अगर (!mp_req->mp_resp_bd) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP resp bd\n");
		qedf_मुक्त_mp_resc(io_req);
		वापस -ENOMEM;
	पूर्ण

	/* Fill bd table */
	addr = mp_req->req_buf_dma;
	mp_req_bd = mp_req->mp_req_bd;
	mp_req_bd->sge_addr.lo = U64_LO(addr);
	mp_req_bd->sge_addr.hi = U64_HI(addr);
	mp_req_bd->sge_len = QEDF_PAGE_SIZE;

	/*
	 * MP buffer is either a task mgmt command or an ELS.
	 * So the assumption is that it consumes a single bd
	 * entry in the bd table
	 */
	mp_resp_bd = mp_req->mp_resp_bd;
	addr = mp_req->resp_buf_dma;
	mp_resp_bd->sge_addr.lo = U64_LO(addr);
	mp_resp_bd->sge_addr.hi = U64_HI(addr);
	mp_resp_bd->sge_len = QEDF_PAGE_SIZE;

	वापस 0;
पूर्ण

/*
 * Last ditch efक्रमt to clear the port अगर it's stuck. Used only after a
 * cleanup task बार out.
 */
अटल व्योम qedf_drain_request(काष्ठा qedf_ctx *qedf)
अणु
	अगर (test_bit(QEDF_DRAIN_ACTIVE, &qedf->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "MCP drain already active.\n");
		वापस;
	पूर्ण

	/* Set bit to वापस all queuecommand requests as busy */
	set_bit(QEDF_DRAIN_ACTIVE, &qedf->flags);

	/* Call qed drain request क्रम function. Should be synchronous */
	qed_ops->common->drain(qedf->cdev);

	/* Settle समय क्रम CQEs to be वापसed */
	msleep(100);

	/* Unplug and जारी */
	clear_bit(QEDF_DRAIN_ACTIVE, &qedf->flags);
पूर्ण

/*
 * Returns SUCCESS अगर the cleanup task करोes not समयout, otherwise वापस
 * FAILURE.
 */
पूर्णांक qedf_initiate_cleanup(काष्ठा qedf_ioreq *io_req,
	bool वापस_scsi_cmd_on_abts)
अणु
	काष्ठा qedf_rport *fcport;
	काष्ठा qedf_ctx *qedf;
	पूर्णांक पंचांगo = 0;
	पूर्णांक rc = SUCCESS;
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_wqe *sqe;
	u16 sqe_idx;
	पूर्णांक refcount = 0;

	fcport = io_req->fcport;
	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "fcport is NULL.\n");
		वापस SUCCESS;
	पूर्ण

	/* Sanity check qedf_rport beक्रमe dereferencing any poपूर्णांकers */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "tgt not offloaded\n");
		वापस SUCCESS;
	पूर्ण

	qedf = fcport->qedf;
	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL.\n");
		वापस SUCCESS;
	पूर्ण

	अगर (io_req->cmd_type == QEDF_ELS) अणु
		जाओ process_els;
	पूर्ण

	अगर (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags) ||
	    test_and_set_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "io_req xid=0x%x already in "
			  "cleanup processing or already completed.\n",
			  io_req->xid);
		वापस SUCCESS;
	पूर्ण
	set_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);

process_els:
	/* Ensure room on SQ */
	अगर (!atomic_पढ़ो(&fcport->मुक्त_sqes)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "No SQ entries available\n");
		/* Need to make sure we clear the flag since it was set */
		clear_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);
		वापस FAILED;
	पूर्ण

	अगर (io_req->cmd_type == QEDF_CLEANUP) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req=0x%x is already a cleanup command cmd_type=%d.\n",
			 io_req->xid, io_req->cmd_type);
		clear_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);
		वापस SUCCESS;
	पूर्ण

	refcount = kref_पढ़ो(&io_req->refcount);

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
		  "Entered xid=0x%x sc_cmd=%p cmd_type=%d flags=0x%lx refcount=%d fcport=%p port_id=0x%06x\n",
		  io_req->xid, io_req->sc_cmd, io_req->cmd_type, io_req->flags,
		  refcount, fcport, fcport->rdata->ids.port_id);

	/* Cleanup cmds re-use the same TID as the original I/O */
	io_req->cmd_type = QEDF_CLEANUP;
	io_req->वापस_scsi_cmd_on_abts = वापस_scsi_cmd_on_abts;

	init_completion(&io_req->cleanup_करोne);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));
	io_req->task_params->sqe = sqe;

	init_initiator_cleanup_fcoe_task(io_req->task_params);
	qedf_ring_करोorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);

	पंचांगo = रुको_क्रम_completion_समयout(&io_req->cleanup_करोne,
					  QEDF_CLEANUP_TIMEOUT * HZ);

	अगर (!पंचांगo) अणु
		rc = FAILED;
		/* Timeout हाल */
		QEDF_ERR(&(qedf->dbg_ctx), "Cleanup command timeout, "
			  "xid=%x.\n", io_req->xid);
		clear_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);
		/* Issue a drain request अगर cleanup task बार out */
		QEDF_ERR(&(qedf->dbg_ctx), "Issuing MCP drain request.\n");
		qedf_drain_request(qedf);
	पूर्ण

	/* If it TASK MGMT handle it, reference will be decreased
	 * in qedf_execute_पंचांगf
	 */
	अगर (io_req->पंचांग_flags  == FCP_TMF_LUN_RESET ||
	    io_req->पंचांग_flags == FCP_TMF_TGT_RESET) अणु
		clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);
		io_req->sc_cmd = शून्य;
		complete(&io_req->पंचांग_करोne);
	पूर्ण

	अगर (io_req->sc_cmd) अणु
		अगर (!io_req->वापस_scsi_cmd_on_abts)
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_SCSI_TM,
				  "Not call scsi_done for xid=0x%x.\n",
				  io_req->xid);
		अगर (io_req->वापस_scsi_cmd_on_abts)
			qedf_scsi_करोne(qedf, io_req, DID_ERROR);
	पूर्ण

	अगर (rc == SUCCESS)
		io_req->event = QEDF_IOREQ_EV_CLEANUP_SUCCESS;
	अन्यथा
		io_req->event = QEDF_IOREQ_EV_CLEANUP_FAILED;

	वापस rc;
पूर्ण

व्योम qedf_process_cleanup_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "Entered xid = 0x%x\n",
		   io_req->xid);

	clear_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);

	/* Complete so we can finish cleaning up the I/O */
	complete(&io_req->cleanup_करोne);
पूर्ण

अटल पूर्णांक qedf_execute_पंचांगf(काष्ठा qedf_rport *fcport, काष्ठा scsi_cmnd *sc_cmd,
	uपूर्णांक8_t पंचांग_flags)
अणु
	काष्ठा qedf_ioreq *io_req;
	काष्ठा e4_fcoe_task_context *task;
	काष्ठा qedf_ctx *qedf = fcport->qedf;
	काष्ठा fc_lport *lport = qedf->lport;
	पूर्णांक rc = 0;
	uपूर्णांक16_t xid;
	पूर्णांक पंचांगo = 0;
	पूर्णांक lun = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_wqe *sqe;
	u16 sqe_idx;

	अगर (!sc_cmd) अणु
		QEDF_ERR(&qedf->dbg_ctx, "sc_cmd is NULL\n");
		वापस FAILED;
	पूर्ण

	lun = (पूर्णांक)sc_cmd->device->lun;
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "fcport not offloaded\n");
		rc = FAILED;
		जाओ no_flush;
	पूर्ण

	io_req = qedf_alloc_cmd(fcport, QEDF_TASK_MGMT_CMD);
	अगर (!io_req) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed TMF");
		rc = -EAGAIN;
		जाओ no_flush;
	पूर्ण

	अगर (पंचांग_flags == FCP_TMF_LUN_RESET)
		qedf->lun_resets++;
	अन्यथा अगर (पंचांग_flags == FCP_TMF_TGT_RESET)
		qedf->target_resets++;

	/* Initialize rest of io_req fields */
	io_req->sc_cmd = sc_cmd;
	io_req->fcport = fcport;
	io_req->cmd_type = QEDF_TASK_MGMT_CMD;

	/* Record which cpu this request is associated with */
	io_req->cpu = smp_processor_id();

	/* Set TM flags */
	io_req->io_req_flags = QEDF_READ;
	io_req->data_xfer_len = 0;
	io_req->पंचांग_flags = पंचांग_flags;

	/* Default is to वापस a SCSI command when an error occurs */
	io_req->वापस_scsi_cmd_on_abts = false;

	/* Obtain exchange id */
	xid = io_req->xid;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM, "TMF io_req xid = "
		   "0x%x\n", xid);

	/* Initialize task context क्रम this IO request */
	task = qedf_get_task_mem(&qedf->tasks, xid);

	init_completion(&io_req->पंचांग_करोne);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));

	qedf_init_task(fcport, lport, io_req, task, sqe);
	qedf_ring_करोorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);

	set_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);
	पंचांगo = रुको_क्रम_completion_समयout(&io_req->पंचांग_करोne,
	    QEDF_TM_TIMEOUT * HZ);

	अगर (!पंचांगo) अणु
		rc = FAILED;
		QEDF_ERR(&(qedf->dbg_ctx), "wait for tm_cmpl timeout!\n");
		/* Clear outstanding bit since command समयd out */
		clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);
		io_req->sc_cmd = शून्य;
	पूर्ण अन्यथा अणु
		/* Check TMF response code */
		अगर (io_req->fcp_rsp_code == 0)
			rc = SUCCESS;
		अन्यथा
			rc = FAILED;
	पूर्ण
	/*
	 * Double check that fcport has not gone पूर्णांकo an uploading state beक्रमe
	 * executing the command flush क्रम the LUN/target.
	 */
	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "fcport is uploading, not executing flush.\n");
		जाओ no_flush;
	पूर्ण
	/* We करो not need this io_req any more */
	kref_put(&io_req->refcount, qedf_release_cmd);


	अगर (पंचांग_flags == FCP_TMF_LUN_RESET)
		qedf_flush_active_ios(fcport, lun);
	अन्यथा
		qedf_flush_active_ios(fcport, -1);

no_flush:
	अगर (rc != SUCCESS) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "task mgmt command failed...\n");
		rc = FAILED;
	पूर्ण अन्यथा अणु
		QEDF_ERR(&(qedf->dbg_ctx), "task mgmt command success...\n");
		rc = SUCCESS;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक qedf_initiate_पंचांगf(काष्ठा scsi_cmnd *sc_cmd, u8 पंचांग_flags)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा qedf_rport *fcport = (काष्ठा qedf_rport *)&rp[1];
	काष्ठा qedf_ctx *qedf;
	काष्ठा fc_lport *lport = shost_priv(sc_cmd->device->host);
	पूर्णांक rc = SUCCESS;
	पूर्णांक rval;
	काष्ठा qedf_ioreq *io_req = शून्य;
	पूर्णांक ref_cnt = 0;
	काष्ठा fc_rport_priv *rdata = fcport->rdata;

	QEDF_ERR(शून्य,
		 "tm_flags 0x%x sc_cmd %p op = 0x%02x target_id = 0x%x lun=%d\n",
		 पंचांग_flags, sc_cmd, sc_cmd->cmd_len ? sc_cmd->cmnd[0] : 0xff,
		 rport->scsi_target_id, (पूर्णांक)sc_cmd->device->lun);

	अगर (!rdata || !kref_get_unless_zero(&rdata->kref)) अणु
		QEDF_ERR(शून्य, "stale rport\n");
		वापस FAILED;
	पूर्ण

	QEDF_ERR(शून्य, "portid=%06x tm_flags =%s\n", rdata->ids.port_id,
		 (पंचांग_flags == FCP_TMF_TGT_RESET) ? "TARGET RESET" :
		 "LUN RESET");

	अगर (sc_cmd->SCp.ptr) अणु
		io_req = (काष्ठा qedf_ioreq *)sc_cmd->SCp.ptr;
		ref_cnt = kref_पढ़ो(&io_req->refcount);
		QEDF_ERR(शून्य,
			 "orig io_req = %p xid = 0x%x ref_cnt = %d.\n",
			 io_req, io_req->xid, ref_cnt);
	पूर्ण

	rval = fc_remote_port_chkपढ़ोy(rport);
	अगर (rval) अणु
		QEDF_ERR(शून्य, "device_reset rport not ready\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण

	rc = fc_block_scsi_eh(sc_cmd);
	अगर (rc)
		जाओ पंचांगf_err;

	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "device_reset: rport is NULL\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण

	qedf = fcport->qedf;

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL.\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण

	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Connection is getting uploaded.\n");
		rc = SUCCESS;
		जाओ पंचांगf_err;
	पूर्ण

	अगर (test_bit(QEDF_UNLOADING, &qedf->flags) ||
	    test_bit(QEDF_DBG_STOP_IO, &qedf->flags)) अणु
		rc = SUCCESS;
		जाओ पंचांगf_err;
	पूर्ण

	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "link is not ready\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण

	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		अगर (!fcport->rdata)
			QEDF_ERR(&qedf->dbg_ctx, "fcport %p is uploading.\n",
				 fcport);
		अन्यथा
			QEDF_ERR(&qedf->dbg_ctx,
				 "fcport %p port_id=%06x is uploading.\n",
				 fcport, fcport->rdata->ids.port_id);
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण

	rc = qedf_execute_पंचांगf(fcport, sc_cmd, पंचांग_flags);

पंचांगf_err:
	kref_put(&rdata->kref, fc_rport_destroy);
	वापस rc;
पूर्ण

व्योम qedf_process_पंचांगf_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req)
अणु
	काष्ठा fcoe_cqe_rsp_info *fcp_rsp;

	clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	fcp_rsp = &cqe->cqe_info.rsp_info;
	qedf_parse_fcp_rsp(io_req, fcp_rsp);

	io_req->sc_cmd = शून्य;
	complete(&io_req->पंचांग_करोne);
पूर्ण

व्योम qedf_process_unsol_compl(काष्ठा qedf_ctx *qedf, uपूर्णांक16_t que_idx,
	काष्ठा fcoe_cqe *cqe)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t pktlen = cqe->cqe_info.unsolic_info.pkt_len;
	u32 payload_len, crc;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_frame *fp;
	काष्ठा qedf_io_work *io_work;
	u32 bdq_idx;
	व्योम *bdq_addr;
	काष्ठा scsi_bd *p_bd_info;

	p_bd_info = &cqe->cqe_info.unsolic_info.bd_info;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_UNSOL,
		  "address.hi=%x, address.lo=%x, opaque_data.hi=%x, opaque_data.lo=%x, bdq_prod_idx=%u, len=%u\n",
		  le32_to_cpu(p_bd_info->address.hi),
		  le32_to_cpu(p_bd_info->address.lo),
		  le32_to_cpu(p_bd_info->opaque.fcoe_opaque.hi),
		  le32_to_cpu(p_bd_info->opaque.fcoe_opaque.lo),
		  qedf->bdq_prod_idx, pktlen);

	bdq_idx = le32_to_cpu(p_bd_info->opaque.fcoe_opaque.lo);
	अगर (bdq_idx >= QEDF_BDQ_SIZE) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "bdq_idx is out of range %d.\n",
		    bdq_idx);
		जाओ increment_prod;
	पूर्ण

	bdq_addr = qedf->bdq[bdq_idx].buf_addr;
	अगर (!bdq_addr) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "bdq_addr is NULL, dropping "
		    "unsolicited packet.\n");
		जाओ increment_prod;
	पूर्ण

	अगर (qedf_dump_frames) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_UNSOL,
		    "BDQ frame is at addr=%p.\n", bdq_addr);
		prपूर्णांक_hex_dump(KERN_WARNING, "bdq ", DUMP_PREFIX_OFFSET, 16, 1,
		    (व्योम *)bdq_addr, pktlen, false);
	पूर्ण

	/* Allocate frame */
	payload_len = pktlen - माप(काष्ठा fc_frame_header);
	fp = fc_frame_alloc(qedf->lport, payload_len);
	अगर (!fp) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate fp.\n");
		जाओ increment_prod;
	पूर्ण

	/* Copy data from BDQ buffer पूर्णांकo fc_frame काष्ठा */
	fh = (काष्ठा fc_frame_header *)fc_frame_header_get(fp);
	स_नकल(fh, (व्योम *)bdq_addr, pktlen);

	QEDF_WARN(&qedf->dbg_ctx,
		  "Processing Unsolicated frame, src=%06x dest=%06x r_ctl=0x%x type=0x%x cmd=%02x\n",
		  ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id), fh->fh_r_ctl,
		  fh->fh_type, fc_frame_payload_op(fp));

	/* Initialize the frame so libfc sees it as a valid frame */
	crc = fcoe_fc_crc(fp);
	fc_frame_init(fp);
	fr_dev(fp) = qedf->lport;
	fr_sof(fp) = FC_SOF_I3;
	fr_eof(fp) = FC_खातापूर्ण_T;
	fr_crc(fp) = cpu_to_le32(~crc);

	/*
	 * We need to वापस the frame back up to libfc in a non-atomic
	 * context
	 */
	io_work = mempool_alloc(qedf->io_mempool, GFP_ATOMIC);
	अगर (!io_work) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate "
			   "work for I/O completion.\n");
		fc_frame_मुक्त(fp);
		जाओ increment_prod;
	पूर्ण
	स_रखो(io_work, 0, माप(काष्ठा qedf_io_work));

	INIT_WORK(&io_work->work, qedf_fp_io_handler);

	/* Copy contents of CQE क्रम deferred processing */
	स_नकल(&io_work->cqe, cqe, माप(काष्ठा fcoe_cqe));

	io_work->qedf = qedf;
	io_work->fp = fp;

	queue_work_on(smp_processor_id(), qedf_io_wq, &io_work->work);
increment_prod:
	spin_lock_irqsave(&qedf->hba_lock, flags);

	/* Increment producer to let f/w know we've handled the frame */
	qedf->bdq_prod_idx++;

	/* Producer index wraps at uपूर्णांक16_t boundary */
	अगर (qedf->bdq_prod_idx == 0xffff)
		qedf->bdq_prod_idx = 0;

	ग_लिखोw(qedf->bdq_prod_idx, qedf->bdq_primary_prod);
	पढ़ोw(qedf->bdq_primary_prod);
	ग_लिखोw(qedf->bdq_prod_idx, qedf->bdq_secondary_prod);
	पढ़ोw(qedf->bdq_secondary_prod);

	spin_unlock_irqrestore(&qedf->hba_lock, flags);
पूर्ण
