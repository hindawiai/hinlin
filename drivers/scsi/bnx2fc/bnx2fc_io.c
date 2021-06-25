<शैली गुरु>
/* bnx2fc_io.c: QLogic Linux FCoE offload driver.
 * IO manager and SCSI IO processing.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Bhanu Prakash Gollapudi (bprakash@broadcom.com)
 */

#समावेश "bnx2fc.h"

#घोषणा RESERVE_FREE_LIST_INDEX num_possible_cpus()

अटल पूर्णांक bnx2fc_split_bd(काष्ठा bnx2fc_cmd *io_req, u64 addr, पूर्णांक sg_len,
			   पूर्णांक bd_index);
अटल पूर्णांक bnx2fc_map_sg(काष्ठा bnx2fc_cmd *io_req);
अटल पूर्णांक bnx2fc_build_bd_list_from_sg(काष्ठा bnx2fc_cmd *io_req);
अटल व्योम bnx2fc_unmap_sg_list(काष्ठा bnx2fc_cmd *io_req);
अटल व्योम bnx2fc_मुक्त_mp_resc(काष्ठा bnx2fc_cmd *io_req);
अटल व्योम bnx2fc_parse_fcp_rsp(काष्ठा bnx2fc_cmd *io_req,
				 काष्ठा fcoe_fcp_rsp_payload *fcp_rsp,
				 u8 num_rq, अचिन्हित अक्षर *rq_data);

व्योम bnx2fc_cmd_समयr_set(काष्ठा bnx2fc_cmd *io_req,
			  अचिन्हित पूर्णांक समयr_msec)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = io_req->port->priv;

	अगर (queue_delayed_work(पूर्णांकerface->समयr_work_queue,
			       &io_req->समयout_work,
			       msecs_to_jअगरfies(समयr_msec)))
		kref_get(&io_req->refcount);
पूर्ण

अटल व्योम bnx2fc_cmd_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2fc_cmd *io_req = container_of(work, काष्ठा bnx2fc_cmd,
						 समयout_work.work);
	u8 cmd_type = io_req->cmd_type;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	पूर्णांक rc;

	BNX2FC_IO_DBG(io_req, "cmd_timeout, cmd_type = %d,"
		      "req_flags = %lx\n", cmd_type, io_req->req_flags);

	spin_lock_bh(&tgt->tgt_lock);
	अगर (test_and_clear_bit(BNX2FC_FLAG_ISSUE_RRQ, &io_req->req_flags)) अणु
		clear_bit(BNX2FC_FLAG_RETIRE_OXID, &io_req->req_flags);
		/*
		 * ideally we should hold the io_req until RRQ complets,
		 * and release io_req from समयout hold.
		 */
		spin_unlock_bh(&tgt->tgt_lock);
		bnx2fc_send_rrq(io_req);
		वापस;
	पूर्ण
	अगर (test_and_clear_bit(BNX2FC_FLAG_RETIRE_OXID, &io_req->req_flags)) अणु
		BNX2FC_IO_DBG(io_req, "IO ready for reuse now\n");
		जाओ करोne;
	पूर्ण

	चयन (cmd_type) अणु
	हाल BNX2FC_SCSI_CMD:
		अगर (test_and_clear_bit(BNX2FC_FLAG_EH_ABORT,
							&io_req->req_flags)) अणु
			/* Handle eh_पात समयout */
			BNX2FC_IO_DBG(io_req, "eh_abort timed out\n");
			complete(&io_req->abts_करोne);
		पूर्ण अन्यथा अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS,
				    &io_req->req_flags)) अणु
			/* Handle पूर्णांकernally generated ABTS समयout */
			BNX2FC_IO_DBG(io_req, "ABTS timed out refcnt = %d\n",
					kref_पढ़ो(&io_req->refcount));
			अगर (!(test_and_set_bit(BNX2FC_FLAG_ABTS_DONE,
					       &io_req->req_flags))) अणु
				/*
				 * Cleanup and वापस original command to
				 * mid-layer.
				 */
				bnx2fc_initiate_cleanup(io_req);
				kref_put(&io_req->refcount, bnx2fc_cmd_release);
				spin_unlock_bh(&tgt->tgt_lock);

				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Hanlde IO समयout */
			BNX2FC_IO_DBG(io_req, "IO timed out. issue ABTS\n");
			अगर (test_and_set_bit(BNX2FC_FLAG_IO_COMPL,
					     &io_req->req_flags)) अणु
				BNX2FC_IO_DBG(io_req, "IO completed before "
							   " timer expiry\n");
				जाओ करोne;
			पूर्ण

			अगर (!test_and_set_bit(BNX2FC_FLAG_ISSUE_ABTS,
					      &io_req->req_flags)) अणु
				rc = bnx2fc_initiate_abts(io_req);
				अगर (rc == SUCCESS)
					जाओ करोne;

				kref_put(&io_req->refcount, bnx2fc_cmd_release);
				spin_unlock_bh(&tgt->tgt_lock);

				वापस;
			पूर्ण अन्यथा अणु
				BNX2FC_IO_DBG(io_req, "IO already in "
						      "ABTS processing\n");
			पूर्ण
		पूर्ण
		अवरोध;
	हाल BNX2FC_ELS:

		अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags)) अणु
			BNX2FC_IO_DBG(io_req, "ABTS for ELS timed out\n");

			अगर (!test_and_set_bit(BNX2FC_FLAG_ABTS_DONE,
					      &io_req->req_flags)) अणु
				kref_put(&io_req->refcount, bnx2fc_cmd_release);
				spin_unlock_bh(&tgt->tgt_lock);

				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Handle ELS समयout.
			 * tgt_lock is used to sync compl path and समयout
			 * path. If els compl path is processing this IO, we
			 * have nothing to करो here, just release the समयr hold
			 */
			BNX2FC_IO_DBG(io_req, "ELS timed out\n");
			अगर (test_and_set_bit(BNX2FC_FLAG_ELS_DONE,
					       &io_req->req_flags))
				जाओ करोne;

			/* Indicate the cb_func that this ELS is समयd out */
			set_bit(BNX2FC_FLAG_ELS_TIMEOUT, &io_req->req_flags);

			अगर ((io_req->cb_func) && (io_req->cb_arg)) अणु
				io_req->cb_func(io_req->cb_arg);
				io_req->cb_arg = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "cmd_timeout: invalid cmd_type %d\n",
			cmd_type);
		अवरोध;
	पूर्ण

करोne:
	/* release the cmd that was held when समयr was set */
	kref_put(&io_req->refcount, bnx2fc_cmd_release);
	spin_unlock_bh(&tgt->tgt_lock);
पूर्ण

अटल व्योम bnx2fc_scsi_करोne(काष्ठा bnx2fc_cmd *io_req, पूर्णांक err_code)
अणु
	/* Called with host lock held */
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;

	/*
	 * active_cmd_queue may have other command types as well,
	 * and during flush operation,  we want to error back only
	 * scsi commands.
	 */
	अगर (io_req->cmd_type != BNX2FC_SCSI_CMD)
		वापस;

	BNX2FC_IO_DBG(io_req, "scsi_done. err_code = 0x%x\n", err_code);
	अगर (test_bit(BNX2FC_FLAG_CMD_LOST, &io_req->req_flags)) अणु
		/* Do not call scsi करोne क्रम this IO */
		वापस;
	पूर्ण

	bnx2fc_unmap_sg_list(io_req);
	io_req->sc_cmd = शून्य;

	/* Sanity checks beक्रमe वापसing command to mid-layer */
	अगर (!sc_cmd) अणु
		prपूर्णांकk(KERN_ERR PFX "scsi_done - sc_cmd NULL. "
				    "IO(0x%x) already cleaned up\n",
		       io_req->xid);
		वापस;
	पूर्ण
	अगर (!sc_cmd->device) अणु
		pr_err(PFX "0x%x: sc_cmd->device is NULL.\n", io_req->xid);
		वापस;
	पूर्ण
	अगर (!sc_cmd->device->host) अणु
		pr_err(PFX "0x%x: sc_cmd->device->host is NULL.\n",
		    io_req->xid);
		वापस;
	पूर्ण

	sc_cmd->result = err_code << 16;

	BNX2FC_IO_DBG(io_req, "sc=%p, result=0x%x, retries=%d, allowed=%d\n",
		sc_cmd, host_byte(sc_cmd->result), sc_cmd->retries,
		sc_cmd->allowed);
	scsi_set_resid(sc_cmd, scsi_bufflen(sc_cmd));
	sc_cmd->SCp.ptr = शून्य;
	sc_cmd->scsi_करोne(sc_cmd);
पूर्ण

काष्ठा bnx2fc_cmd_mgr *bnx2fc_cmd_mgr_alloc(काष्ठा bnx2fc_hba *hba)
अणु
	काष्ठा bnx2fc_cmd_mgr *cmgr;
	काष्ठा io_bdt *bdt_info;
	काष्ठा bnx2fc_cmd *io_req;
	माप_प्रकार len;
	u32 mem_size;
	u16 xid;
	पूर्णांक i;
	पूर्णांक num_ios, num_pri_ios;
	माप_प्रकार bd_tbl_sz;
	पूर्णांक arr_sz = num_possible_cpus() + 1;
	u16 min_xid = BNX2FC_MIN_XID;
	u16 max_xid = hba->max_xid;

	अगर (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN) अणु
		prपूर्णांकk(KERN_ERR PFX "cmd_mgr_alloc: Invalid min_xid 0x%x \
					and max_xid 0x%x\न", min_xid, max_xid);
		वापस शून्य;
	पूर्ण
	BNX2FC_MISC_DBG("min xid 0x%x, max xid 0x%x\n", min_xid, max_xid);

	num_ios = max_xid - min_xid + 1;
	len = (num_ios * (माप(काष्ठा bnx2fc_cmd *)));
	len += माप(काष्ठा bnx2fc_cmd_mgr);

	cmgr = kzalloc(len, GFP_KERNEL);
	अगर (!cmgr) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to alloc cmgr\n");
		वापस शून्य;
	पूर्ण

	cmgr->hba = hba;
	cmgr->मुक्त_list = kसुस्मृति(arr_sz, माप(*cmgr->मुक्त_list),
				  GFP_KERNEL);
	अगर (!cmgr->मुक्त_list) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to alloc free_list\n");
		जाओ mem_err;
	पूर्ण

	cmgr->मुक्त_list_lock = kसुस्मृति(arr_sz, माप(*cmgr->मुक्त_list_lock),
				       GFP_KERNEL);
	अगर (!cmgr->मुक्त_list_lock) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to alloc free_list_lock\n");
		kमुक्त(cmgr->मुक्त_list);
		cmgr->मुक्त_list = शून्य;
		जाओ mem_err;
	पूर्ण

	cmgr->cmds = (काष्ठा bnx2fc_cmd **)(cmgr + 1);

	क्रम (i = 0; i < arr_sz; i++)  अणु
		INIT_LIST_HEAD(&cmgr->मुक्त_list[i]);
		spin_lock_init(&cmgr->मुक्त_list_lock[i]);
	पूर्ण

	/*
	 * Pre-allocated pool of bnx2fc_cmds.
	 * Last entry in the मुक्त list array is the मुक्त list
	 * of slow path requests.
	 */
	xid = BNX2FC_MIN_XID;
	num_pri_ios = num_ios - hba->elsपंचांग_xids;
	क्रम (i = 0; i < num_ios; i++) अणु
		io_req = kzalloc(माप(*io_req), GFP_KERNEL);

		अगर (!io_req) अणु
			prपूर्णांकk(KERN_ERR PFX "failed to alloc io_req\n");
			जाओ mem_err;
		पूर्ण

		INIT_LIST_HEAD(&io_req->link);
		INIT_DELAYED_WORK(&io_req->समयout_work, bnx2fc_cmd_समयout);

		io_req->xid = xid++;
		अगर (i < num_pri_ios)
			list_add_tail(&io_req->link,
				&cmgr->मुक्त_list[io_req->xid %
						 num_possible_cpus()]);
		अन्यथा
			list_add_tail(&io_req->link,
				&cmgr->मुक्त_list[num_possible_cpus()]);
		io_req++;
	पूर्ण

	/* Allocate pool of io_bdts - one क्रम each bnx2fc_cmd */
	mem_size = num_ios * माप(काष्ठा io_bdt *);
	cmgr->io_bdt_pool = kzalloc(mem_size, GFP_KERNEL);
	अगर (!cmgr->io_bdt_pool) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to alloc io_bdt_pool\n");
		जाओ mem_err;
	पूर्ण

	mem_size = माप(काष्ठा io_bdt);
	क्रम (i = 0; i < num_ios; i++) अणु
		cmgr->io_bdt_pool[i] = kदो_स्मृति(mem_size, GFP_KERNEL);
		अगर (!cmgr->io_bdt_pool[i]) अणु
			prपूर्णांकk(KERN_ERR PFX "failed to alloc "
				"io_bdt_pool[%d]\n", i);
			जाओ mem_err;
		पूर्ण
	पूर्ण

	/* Allocate an map fcoe_bdt_ctx काष्ठाures */
	bd_tbl_sz = BNX2FC_MAX_BDS_PER_CMD * माप(काष्ठा fcoe_bd_ctx);
	क्रम (i = 0; i < num_ios; i++) अणु
		bdt_info = cmgr->io_bdt_pool[i];
		bdt_info->bd_tbl = dma_alloc_coherent(&hba->pcidev->dev,
						      bd_tbl_sz,
						      &bdt_info->bd_tbl_dma,
						      GFP_KERNEL);
		अगर (!bdt_info->bd_tbl) अणु
			prपूर्णांकk(KERN_ERR PFX "failed to alloc "
				"bdt_tbl[%d]\n", i);
			जाओ mem_err;
		पूर्ण
	पूर्ण

	वापस cmgr;

mem_err:
	bnx2fc_cmd_mgr_मुक्त(cmgr);
	वापस शून्य;
पूर्ण

व्योम bnx2fc_cmd_mgr_मुक्त(काष्ठा bnx2fc_cmd_mgr *cmgr)
अणु
	काष्ठा io_bdt *bdt_info;
	काष्ठा bnx2fc_hba *hba = cmgr->hba;
	माप_प्रकार bd_tbl_sz;
	u16 min_xid = BNX2FC_MIN_XID;
	u16 max_xid = hba->max_xid;
	पूर्णांक num_ios;
	पूर्णांक i;

	num_ios = max_xid - min_xid + 1;

	/* Free fcoe_bdt_ctx काष्ठाures */
	अगर (!cmgr->io_bdt_pool)
		जाओ मुक्त_cmd_pool;

	bd_tbl_sz = BNX2FC_MAX_BDS_PER_CMD * माप(काष्ठा fcoe_bd_ctx);
	क्रम (i = 0; i < num_ios; i++) अणु
		bdt_info = cmgr->io_bdt_pool[i];
		अगर (bdt_info->bd_tbl) अणु
			dma_मुक्त_coherent(&hba->pcidev->dev, bd_tbl_sz,
					    bdt_info->bd_tbl,
					    bdt_info->bd_tbl_dma);
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
	kमुक्त(cmgr->मुक्त_list_lock);

	/* Destroy cmd pool */
	अगर (!cmgr->मुक्त_list)
		जाओ मुक्त_cmgr;

	क्रम (i = 0; i < num_possible_cpus() + 1; i++)  अणु
		काष्ठा bnx2fc_cmd *पंचांगp, *io_req;

		list_क्रम_each_entry_safe(io_req, पंचांगp,
					 &cmgr->मुक्त_list[i], link) अणु
			list_del(&io_req->link);
			kमुक्त(io_req);
		पूर्ण
	पूर्ण
	kमुक्त(cmgr->मुक्त_list);
मुक्त_cmgr:
	/* Free command manager itself */
	kमुक्त(cmgr);
पूर्ण

काष्ठा bnx2fc_cmd *bnx2fc_elsपंचांग_alloc(काष्ठा bnx2fc_rport *tgt, पूर्णांक type)
अणु
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_cmd_mgr *cmd_mgr = पूर्णांकerface->hba->cmd_mgr;
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा list_head *listp;
	काष्ठा io_bdt *bd_tbl;
	पूर्णांक index = RESERVE_FREE_LIST_INDEX;
	u32 मुक्त_sqes;
	u32 max_sqes;
	u16 xid;

	max_sqes = tgt->max_sqes;
	चयन (type) अणु
	हाल BNX2FC_TASK_MGMT_CMD:
		max_sqes = BNX2FC_TM_MAX_SQES;
		अवरोध;
	हाल BNX2FC_ELS:
		max_sqes = BNX2FC_ELS_MAX_SQES;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * NOTE: Free list insertions and deletions are रक्षित with
	 * cmgr lock
	 */
	spin_lock_bh(&cmd_mgr->मुक्त_list_lock[index]);
	मुक्त_sqes = atomic_पढ़ो(&tgt->मुक्त_sqes);
	अगर ((list_empty(&(cmd_mgr->मुक्त_list[index]))) ||
	    (tgt->num_active_ios.counter  >= max_sqes) ||
	    (मुक्त_sqes + max_sqes <= BNX2FC_SQ_WQES_MAX)) अणु
		BNX2FC_TGT_DBG(tgt, "No free els_tm cmds available "
			"ios(%d):sqes(%d)\n",
			tgt->num_active_ios.counter, tgt->max_sqes);
		अगर (list_empty(&(cmd_mgr->मुक्त_list[index])))
			prपूर्णांकk(KERN_ERR PFX "elstm_alloc: list_empty\n");
		spin_unlock_bh(&cmd_mgr->मुक्त_list_lock[index]);
		वापस शून्य;
	पूर्ण

	listp = (काष्ठा list_head *)
			cmd_mgr->मुक्त_list[index].next;
	list_del_init(listp);
	io_req = (काष्ठा bnx2fc_cmd *) listp;
	xid = io_req->xid;
	cmd_mgr->cmds[xid] = io_req;
	atomic_inc(&tgt->num_active_ios);
	atomic_dec(&tgt->मुक्त_sqes);
	spin_unlock_bh(&cmd_mgr->मुक्त_list_lock[index]);

	INIT_LIST_HEAD(&io_req->link);

	io_req->port = port;
	io_req->cmd_mgr = cmd_mgr;
	io_req->req_flags = 0;
	io_req->cmd_type = type;

	/* Bind io_bdt क्रम this io_req */
	/* Have a अटल link between io_req and io_bdt_pool */
	bd_tbl = io_req->bd_tbl = cmd_mgr->io_bdt_pool[xid];
	bd_tbl->io_req = io_req;

	/* Hold the io_req  against deletion */
	kref_init(&io_req->refcount);
	वापस io_req;
पूर्ण

काष्ठा bnx2fc_cmd *bnx2fc_cmd_alloc(काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_cmd_mgr *cmd_mgr = पूर्णांकerface->hba->cmd_mgr;
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा list_head *listp;
	काष्ठा io_bdt *bd_tbl;
	u32 मुक्त_sqes;
	u32 max_sqes;
	u16 xid;
	पूर्णांक index = get_cpu();

	max_sqes = BNX2FC_SCSI_MAX_SQES;
	/*
	 * NOTE: Free list insertions and deletions are रक्षित with
	 * cmgr lock
	 */
	spin_lock_bh(&cmd_mgr->मुक्त_list_lock[index]);
	मुक्त_sqes = atomic_पढ़ो(&tgt->मुक्त_sqes);
	अगर ((list_empty(&cmd_mgr->मुक्त_list[index])) ||
	    (tgt->num_active_ios.counter  >= max_sqes) ||
	    (मुक्त_sqes + max_sqes <= BNX2FC_SQ_WQES_MAX)) अणु
		spin_unlock_bh(&cmd_mgr->मुक्त_list_lock[index]);
		put_cpu();
		वापस शून्य;
	पूर्ण

	listp = (काष्ठा list_head *)
		cmd_mgr->मुक्त_list[index].next;
	list_del_init(listp);
	io_req = (काष्ठा bnx2fc_cmd *) listp;
	xid = io_req->xid;
	cmd_mgr->cmds[xid] = io_req;
	atomic_inc(&tgt->num_active_ios);
	atomic_dec(&tgt->मुक्त_sqes);
	spin_unlock_bh(&cmd_mgr->मुक्त_list_lock[index]);
	put_cpu();

	INIT_LIST_HEAD(&io_req->link);

	io_req->port = port;
	io_req->cmd_mgr = cmd_mgr;
	io_req->req_flags = 0;

	/* Bind io_bdt क्रम this io_req */
	/* Have a अटल link between io_req and io_bdt_pool */
	bd_tbl = io_req->bd_tbl = cmd_mgr->io_bdt_pool[xid];
	bd_tbl->io_req = io_req;

	/* Hold the io_req  against deletion */
	kref_init(&io_req->refcount);
	वापस io_req;
पूर्ण

व्योम bnx2fc_cmd_release(काष्ठा kref *ref)
अणु
	काष्ठा bnx2fc_cmd *io_req = container_of(ref,
						काष्ठा bnx2fc_cmd, refcount);
	काष्ठा bnx2fc_cmd_mgr *cmd_mgr = io_req->cmd_mgr;
	पूर्णांक index;

	अगर (io_req->cmd_type == BNX2FC_SCSI_CMD)
		index = io_req->xid % num_possible_cpus();
	अन्यथा
		index = RESERVE_FREE_LIST_INDEX;


	spin_lock_bh(&cmd_mgr->मुक्त_list_lock[index]);
	अगर (io_req->cmd_type != BNX2FC_SCSI_CMD)
		bnx2fc_मुक्त_mp_resc(io_req);
	cmd_mgr->cmds[io_req->xid] = शून्य;
	/* Delete IO from retire queue */
	list_del_init(&io_req->link);
	/* Add it to the मुक्त list */
	list_add(&io_req->link,
			&cmd_mgr->मुक्त_list[index]);
	atomic_dec(&io_req->tgt->num_active_ios);
	spin_unlock_bh(&cmd_mgr->मुक्त_list_lock[index]);

पूर्ण

अटल व्योम bnx2fc_मुक्त_mp_resc(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा bnx2fc_mp_req *mp_req = &(io_req->mp_req);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = io_req->port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	माप_प्रकार sz = माप(काष्ठा fcoe_bd_ctx);

	/* clear पंचांग flags */
	mp_req->पंचांग_flags = 0;
	अगर (mp_req->mp_req_bd) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, sz,
				     mp_req->mp_req_bd,
				     mp_req->mp_req_bd_dma);
		mp_req->mp_req_bd = शून्य;
	पूर्ण
	अगर (mp_req->mp_resp_bd) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, sz,
				     mp_req->mp_resp_bd,
				     mp_req->mp_resp_bd_dma);
		mp_req->mp_resp_bd = शून्य;
	पूर्ण
	अगर (mp_req->req_buf) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				     mp_req->req_buf,
				     mp_req->req_buf_dma);
		mp_req->req_buf = शून्य;
	पूर्ण
	अगर (mp_req->resp_buf) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				     mp_req->resp_buf,
				     mp_req->resp_buf_dma);
		mp_req->resp_buf = शून्य;
	पूर्ण
पूर्ण

पूर्णांक bnx2fc_init_mp_req(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fcoe_bd_ctx *mp_req_bd;
	काष्ठा fcoe_bd_ctx *mp_resp_bd;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = io_req->port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	dma_addr_t addr;
	माप_प्रकार sz;

	mp_req = (काष्ठा bnx2fc_mp_req *)&(io_req->mp_req);
	स_रखो(mp_req, 0, माप(काष्ठा bnx2fc_mp_req));

	अगर (io_req->cmd_type != BNX2FC_ELS) अणु
		mp_req->req_len = माप(काष्ठा fcp_cmnd);
		io_req->data_xfer_len = mp_req->req_len;
	पूर्ण अन्यथा
		mp_req->req_len = io_req->data_xfer_len;

	mp_req->req_buf = dma_alloc_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					     &mp_req->req_buf_dma,
					     GFP_ATOMIC);
	अगर (!mp_req->req_buf) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc MP req buffer\n");
		bnx2fc_मुक्त_mp_resc(io_req);
		वापस FAILED;
	पूर्ण

	mp_req->resp_buf = dma_alloc_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					      &mp_req->resp_buf_dma,
					      GFP_ATOMIC);
	अगर (!mp_req->resp_buf) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc TM resp buffer\n");
		bnx2fc_मुक्त_mp_resc(io_req);
		वापस FAILED;
	पूर्ण
	स_रखो(mp_req->req_buf, 0, CNIC_PAGE_SIZE);
	स_रखो(mp_req->resp_buf, 0, CNIC_PAGE_SIZE);

	/* Allocate and map mp_req_bd and mp_resp_bd */
	sz = माप(काष्ठा fcoe_bd_ctx);
	mp_req->mp_req_bd = dma_alloc_coherent(&hba->pcidev->dev, sz,
						 &mp_req->mp_req_bd_dma,
						 GFP_ATOMIC);
	अगर (!mp_req->mp_req_bd) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc MP req bd\n");
		bnx2fc_मुक्त_mp_resc(io_req);
		वापस FAILED;
	पूर्ण
	mp_req->mp_resp_bd = dma_alloc_coherent(&hba->pcidev->dev, sz,
						 &mp_req->mp_resp_bd_dma,
						 GFP_ATOMIC);
	अगर (!mp_req->mp_resp_bd) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc MP resp bd\n");
		bnx2fc_मुक्त_mp_resc(io_req);
		वापस FAILED;
	पूर्ण
	/* Fill bd table */
	addr = mp_req->req_buf_dma;
	mp_req_bd = mp_req->mp_req_bd;
	mp_req_bd->buf_addr_lo = (u32)addr & 0xffffffff;
	mp_req_bd->buf_addr_hi = (u32)((u64)addr >> 32);
	mp_req_bd->buf_len = CNIC_PAGE_SIZE;
	mp_req_bd->flags = 0;

	/*
	 * MP buffer is either a task mgmt command or an ELS.
	 * So the assumption is that it consumes a single bd
	 * entry in the bd table
	 */
	mp_resp_bd = mp_req->mp_resp_bd;
	addr = mp_req->resp_buf_dma;
	mp_resp_bd->buf_addr_lo = (u32)addr & 0xffffffff;
	mp_resp_bd->buf_addr_hi = (u32)((u64)addr >> 32);
	mp_resp_bd->buf_len = CNIC_PAGE_SIZE;
	mp_resp_bd->flags = 0;

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक bnx2fc_initiate_पंचांगf(काष्ठा scsi_cmnd *sc_cmd, u8 पंचांग_flags)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_libfc_priv *rp;
	काष्ठा fcoe_port *port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा bnx2fc_mp_req *पंचांग_req;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	काष्ठा Scsi_Host *host = sc_cmd->device->host;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा fcp_cmnd *fcp_cmnd;
	पूर्णांक task_idx, index;
	पूर्णांक rc = SUCCESS;
	u16 xid;
	u32 sid, did;
	अचिन्हित दीर्घ start = jअगरfies;

	lport = shost_priv(host);
	rport = starget_to_rport(scsi_target(sc_cmd->device));
	port = lport_priv(lport);
	पूर्णांकerface = port->priv;

	अगर (rport == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "device_reset: rport is NULL\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण
	rp = rport->dd_data;

	rc = fc_block_scsi_eh(sc_cmd);
	अगर (rc)
		वापस rc;

	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		prपूर्णांकk(KERN_ERR PFX "device_reset: link is not ready\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण
	/* rport and tgt are allocated together, so tgt should be non-शून्य */
	tgt = (काष्ठा bnx2fc_rport *)&rp[1];

	अगर (!(test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags))) अणु
		prपूर्णांकk(KERN_ERR PFX "device_reset: tgt not offloaded\n");
		rc = FAILED;
		जाओ पंचांगf_err;
	पूर्ण
retry_पंचांगf:
	io_req = bnx2fc_elsपंचांग_alloc(tgt, BNX2FC_TASK_MGMT_CMD);
	अगर (!io_req) अणु
		अगर (समय_after(jअगरfies, start + HZ)) अणु
			prपूर्णांकk(KERN_ERR PFX "tmf: Failed TMF");
			rc = FAILED;
			जाओ पंचांगf_err;
		पूर्ण
		msleep(20);
		जाओ retry_पंचांगf;
	पूर्ण
	/* Initialize rest of io_req fields */
	io_req->sc_cmd = sc_cmd;
	io_req->port = port;
	io_req->tgt = tgt;

	पंचांग_req = (काष्ठा bnx2fc_mp_req *)&(io_req->mp_req);

	rc = bnx2fc_init_mp_req(io_req);
	अगर (rc == FAILED) अणु
		prपूर्णांकk(KERN_ERR PFX "Task mgmt MP request init failed\n");
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		जाओ पंचांगf_err;
	पूर्ण

	/* Set TM flags */
	io_req->io_req_flags = 0;
	पंचांग_req->पंचांग_flags = पंचांग_flags;

	/* Fill FCP_CMND */
	bnx2fc_build_fcp_cmnd(io_req, (काष्ठा fcp_cmnd *)पंचांग_req->req_buf);
	fcp_cmnd = (काष्ठा fcp_cmnd *)पंचांग_req->req_buf;
	स_रखो(fcp_cmnd->fc_cdb, 0,  sc_cmd->cmd_len);
	fcp_cmnd->fc_dl = 0;

	/* Fill FC header */
	fc_hdr = &(पंचांग_req->req_fc_hdr);
	sid = tgt->sid;
	did = rport->port_id;
	__fc_fill_fc_hdr(fc_hdr, FC_RCTL_DD_UNSOL_CMD, did, sid,
			   FC_TYPE_FCP, FC_FC_FIRST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);
	/* Obtain exchange id */
	xid = io_req->xid;

	BNX2FC_TGT_DBG(tgt, "Initiate TMF - xid = 0x%x\n", xid);
	task_idx = xid/BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *)
			पूर्णांकerface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_mp_task(io_req, task);

	sc_cmd->SCp.ptr = (अक्षर *)io_req;

	/* Obtain मुक्त SQ entry */
	spin_lock_bh(&tgt->tgt_lock);
	bnx2fc_add_2_sq(tgt, xid);

	/* Enqueue the io_req to active_पंचांग_queue */
	io_req->on_पंचांगf_queue = 1;
	list_add_tail(&io_req->link, &tgt->active_पंचांग_queue);

	init_completion(&io_req->abts_करोne);
	io_req->रुको_क्रम_abts_comp = 1;

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);
	spin_unlock_bh(&tgt->tgt_lock);

	rc = रुको_क्रम_completion_समयout(&io_req->abts_करोne,
					 पूर्णांकerface->पंचांग_समयout * HZ);
	spin_lock_bh(&tgt->tgt_lock);

	io_req->रुको_क्रम_abts_comp = 0;
	अगर (!(test_bit(BNX2FC_FLAG_TM_COMPL, &io_req->req_flags))) अणु
		set_bit(BNX2FC_FLAG_TM_TIMEOUT, &io_req->req_flags);
		अगर (io_req->on_पंचांगf_queue) अणु
			list_del_init(&io_req->link);
			io_req->on_पंचांगf_queue = 0;
		पूर्ण
		io_req->रुको_क्रम_cleanup_comp = 1;
		init_completion(&io_req->cleanup_करोne);
		bnx2fc_initiate_cleanup(io_req);
		spin_unlock_bh(&tgt->tgt_lock);
		rc = रुको_क्रम_completion_समयout(&io_req->cleanup_करोne,
						 BNX2FC_FW_TIMEOUT);
		spin_lock_bh(&tgt->tgt_lock);
		io_req->रुको_क्रम_cleanup_comp = 0;
		अगर (!rc)
			kref_put(&io_req->refcount, bnx2fc_cmd_release);
	पूर्ण

	spin_unlock_bh(&tgt->tgt_lock);

	अगर (!rc) अणु
		BNX2FC_TGT_DBG(tgt, "task mgmt command failed...\n");
		rc = FAILED;
	पूर्ण अन्यथा अणु
		BNX2FC_TGT_DBG(tgt, "task mgmt command success...\n");
		rc = SUCCESS;
	पूर्ण
पंचांगf_err:
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_initiate_abts(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा fc_rport *rport = tgt->rport;
	काष्ठा fc_rport_priv *rdata = tgt->rdata;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_port *port;
	काष्ठा bnx2fc_cmd *abts_io_req;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा bnx2fc_mp_req *abts_req;
	पूर्णांक task_idx, index;
	u32 sid, did;
	u16 xid;
	पूर्णांक rc = SUCCESS;
	u32 r_a_tov = rdata->r_a_tov;

	/* called with tgt_lock held */
	BNX2FC_IO_DBG(io_req, "Entered bnx2fc_initiate_abts\n");

	port = io_req->port;
	पूर्णांकerface = port->priv;
	lport = port->lport;

	अगर (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "initiate_abts: tgt not offloaded\n");
		rc = FAILED;
		जाओ abts_err;
	पूर्ण

	अगर (rport == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "initiate_abts: rport is NULL\n");
		rc = FAILED;
		जाओ abts_err;
	पूर्ण

	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		prपूर्णांकk(KERN_ERR PFX "initiate_abts: link is not ready\n");
		rc = FAILED;
		जाओ abts_err;
	पूर्ण

	abts_io_req = bnx2fc_elsपंचांग_alloc(tgt, BNX2FC_ABTS);
	अगर (!abts_io_req) अणु
		prपूर्णांकk(KERN_ERR PFX "abts: couldn't allocate cmd\n");
		rc = FAILED;
		जाओ abts_err;
	पूर्ण

	/* Initialize rest of io_req fields */
	abts_io_req->sc_cmd = शून्य;
	abts_io_req->port = port;
	abts_io_req->tgt = tgt;
	abts_io_req->data_xfer_len = 0; /* No data transfer क्रम ABTS */

	abts_req = (काष्ठा bnx2fc_mp_req *)&(abts_io_req->mp_req);
	स_रखो(abts_req, 0, माप(काष्ठा bnx2fc_mp_req));

	/* Fill FC header */
	fc_hdr = &(abts_req->req_fc_hdr);

	/* Obtain oxid and rxid क्रम the original exchange to be पातed */
	fc_hdr->fh_ox_id = htons(io_req->xid);
	fc_hdr->fh_rx_id = htons(io_req->task->rxwr_txrd.var_ctx.rx_id);

	sid = tgt->sid;
	did = rport->port_id;

	__fc_fill_fc_hdr(fc_hdr, FC_RCTL_BA_ABTS, did, sid,
			   FC_TYPE_BLS, FC_FC_FIRST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);

	xid = abts_io_req->xid;
	BNX2FC_IO_DBG(abts_io_req, "ABTS io_req\n");
	task_idx = xid/BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *)
			पूर्णांकerface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_mp_task(abts_io_req, task);

	/*
	 * ABTS task is a temporary task that will be cleaned up
	 * irrespective of ABTS response. We need to start the समयr
	 * क्रम the original exchange, as the CQE is posted क्रम the original
	 * IO request.
	 *
	 * Timer क्रम ABTS is started only when it is originated by a
	 * TM request. For the ABTS issued as part of ULP समयout,
	 * scsi-ml मुख्यtains the समयrs.
	 */

	/* अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags))*/
	bnx2fc_cmd_समयr_set(io_req, 2 * r_a_tov);

	/* Obtain मुक्त SQ entry */
	bnx2fc_add_2_sq(tgt, xid);

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);

abts_err:
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_initiate_seq_cleanup(काष्ठा bnx2fc_cmd *orig_io_req, u32 offset,
				क्रमागत fc_rctl r_ctl)
अणु
	काष्ठा bnx2fc_rport *tgt = orig_io_req->tgt;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_port *port;
	काष्ठा bnx2fc_cmd *seq_clnp_req;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	काष्ठा bnx2fc_els_cb_arg *cb_arg = शून्य;
	पूर्णांक task_idx, index;
	u16 xid;
	पूर्णांक rc = 0;

	BNX2FC_IO_DBG(orig_io_req, "bnx2fc_initiate_seq_cleanup xid = 0x%x\n",
		   orig_io_req->xid);
	kref_get(&orig_io_req->refcount);

	port = orig_io_req->port;
	पूर्णांकerface = port->priv;

	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to alloc cb_arg for seq clnup\n");
		rc = -ENOMEM;
		जाओ cleanup_err;
	पूर्ण

	seq_clnp_req = bnx2fc_elsपंचांग_alloc(tgt, BNX2FC_SEQ_CLEANUP);
	अगर (!seq_clnp_req) अणु
		prपूर्णांकk(KERN_ERR PFX "cleanup: couldn't allocate cmd\n");
		rc = -ENOMEM;
		kमुक्त(cb_arg);
		जाओ cleanup_err;
	पूर्ण
	/* Initialize rest of io_req fields */
	seq_clnp_req->sc_cmd = शून्य;
	seq_clnp_req->port = port;
	seq_clnp_req->tgt = tgt;
	seq_clnp_req->data_xfer_len = 0; /* No data transfer क्रम cleanup */

	xid = seq_clnp_req->xid;

	task_idx = xid/BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *)
		     पूर्णांकerface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	cb_arg->पातed_io_req = orig_io_req;
	cb_arg->io_req = seq_clnp_req;
	cb_arg->r_ctl = r_ctl;
	cb_arg->offset = offset;
	seq_clnp_req->cb_arg = cb_arg;

	prपूर्णांकk(KERN_ERR PFX "call init_seq_cleanup_task\n");
	bnx2fc_init_seq_cleanup_task(seq_clnp_req, task, orig_io_req, offset);

	/* Obtain मुक्त SQ entry */
	bnx2fc_add_2_sq(tgt, xid);

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);
cleanup_err:
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_initiate_cleanup(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_port *port;
	काष्ठा bnx2fc_cmd *cleanup_io_req;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	पूर्णांक task_idx, index;
	u16 xid, orig_xid;
	पूर्णांक rc = 0;

	/* ASSUMPTION: called with tgt_lock held */
	BNX2FC_IO_DBG(io_req, "Entered bnx2fc_initiate_cleanup\n");

	port = io_req->port;
	पूर्णांकerface = port->priv;

	cleanup_io_req = bnx2fc_elsपंचांग_alloc(tgt, BNX2FC_CLEANUP);
	अगर (!cleanup_io_req) अणु
		prपूर्णांकk(KERN_ERR PFX "cleanup: couldn't allocate cmd\n");
		rc = -1;
		जाओ cleanup_err;
	पूर्ण

	/* Initialize rest of io_req fields */
	cleanup_io_req->sc_cmd = शून्य;
	cleanup_io_req->port = port;
	cleanup_io_req->tgt = tgt;
	cleanup_io_req->data_xfer_len = 0; /* No data transfer क्रम cleanup */

	xid = cleanup_io_req->xid;

	task_idx = xid/BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *)
			पूर्णांकerface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	orig_xid = io_req->xid;

	BNX2FC_IO_DBG(io_req, "CLEANUP io_req xid = 0x%x\n", xid);

	bnx2fc_init_cleanup_task(cleanup_io_req, task, orig_xid);

	/* Obtain मुक्त SQ entry */
	bnx2fc_add_2_sq(tgt, xid);

	/* Set flag that cleanup request is pending with the firmware */
	set_bit(BNX2FC_FLAG_ISSUE_CLEANUP_REQ, &io_req->req_flags);

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);

cleanup_err:
	वापस rc;
पूर्ण

/**
 * bnx2fc_eh_target_reset: Reset a target
 *
 * @sc_cmd:	SCSI command
 *
 * Set from SCSI host ढाँचा to send task mgmt command to the target
 *	and रुको क्रम the response
 */
पूर्णांक bnx2fc_eh_target_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	वापस bnx2fc_initiate_पंचांगf(sc_cmd, FCP_TMF_TGT_RESET);
पूर्ण

/**
 * bnx2fc_eh_device_reset - Reset a single LUN
 *
 * @sc_cmd:	SCSI command
 *
 * Set from SCSI host ढाँचा to send task mgmt command to the target
 *	and रुको क्रम the response
 */
पूर्णांक bnx2fc_eh_device_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	वापस bnx2fc_initiate_पंचांगf(sc_cmd, FCP_TMF_LUN_RESET);
पूर्ण

अटल पूर्णांक bnx2fc_abts_cleanup(काष्ठा bnx2fc_cmd *io_req)
	__must_hold(&tgt->tgt_lock)
अणु
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	अचिन्हित पूर्णांक समय_left;

	init_completion(&io_req->cleanup_करोne);
	io_req->रुको_क्रम_cleanup_comp = 1;
	bnx2fc_initiate_cleanup(io_req);

	spin_unlock_bh(&tgt->tgt_lock);

	/*
	 * Can't रुको क्रमever on cleanup response lest we let the SCSI error
	 * handler रुको क्रमever
	 */
	समय_left = रुको_क्रम_completion_समयout(&io_req->cleanup_करोne,
						BNX2FC_FW_TIMEOUT);
	अगर (!समय_left) अणु
		BNX2FC_IO_DBG(io_req, "%s(): Wait for cleanup timed out.\n",
			      __func__);

		/*
		 * Put the extra reference to the SCSI command since it would
		 * not have been वापसed in this हाल.
		 */
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
	पूर्ण

	spin_lock_bh(&tgt->tgt_lock);
	io_req->रुको_क्रम_cleanup_comp = 0;
	वापस SUCCESS;
पूर्ण

/**
 * bnx2fc_eh_पात - eh_पात_handler api to पात an outstanding
 *			SCSI command
 *
 * @sc_cmd:	SCSI_ML command poपूर्णांकer
 *
 * SCSI पात request handler
 */
पूर्णांक bnx2fc_eh_पात(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा fc_lport *lport;
	काष्ठा bnx2fc_rport *tgt;
	पूर्णांक rc;
	अचिन्हित पूर्णांक समय_left;

	rc = fc_block_scsi_eh(sc_cmd);
	अगर (rc)
		वापस rc;

	lport = shost_priv(sc_cmd->device->host);
	अगर ((lport->state != LPORT_ST_READY) || !(lport->link_up)) अणु
		prपूर्णांकk(KERN_ERR PFX "eh_abort: link not ready\n");
		वापस FAILED;
	पूर्ण

	tgt = (काष्ठा bnx2fc_rport *)&rp[1];

	BNX2FC_TGT_DBG(tgt, "Entered bnx2fc_eh_abort\n");

	spin_lock_bh(&tgt->tgt_lock);
	io_req = (काष्ठा bnx2fc_cmd *)sc_cmd->SCp.ptr;
	अगर (!io_req) अणु
		/* Command might have just completed */
		prपूर्णांकk(KERN_ERR PFX "eh_abort: io_req is NULL\n");
		spin_unlock_bh(&tgt->tgt_lock);
		वापस SUCCESS;
	पूर्ण
	BNX2FC_IO_DBG(io_req, "eh_abort - refcnt = %d\n",
		      kref_पढ़ो(&io_req->refcount));

	/* Hold IO request across पात processing */
	kref_get(&io_req->refcount);

	BUG_ON(tgt != io_req->tgt);

	/* Remove the io_req from the active_q. */
	/*
	 * Task Mgmt functions (LUN RESET & TGT RESET) will not
	 * issue an ABTS on this particular IO req, as the
	 * io_req is no दीर्घer in the active_q.
	 */
	अगर (tgt->flush_in_prog) अणु
		prपूर्णांकk(KERN_ERR PFX "eh_abort: io_req (xid = 0x%x) "
			"flush in progress\n", io_req->xid);
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		वापस SUCCESS;
	पूर्ण

	अगर (io_req->on_active_queue == 0) अणु
		prपूर्णांकk(KERN_ERR PFX "eh_abort: io_req (xid = 0x%x) "
				"not on active_q\n", io_req->xid);
		/*
		 * The IO is still with the FW.
		 * Return failure and let SCSI-ml retry eh_पात.
		 */
		spin_unlock_bh(&tgt->tgt_lock);
		वापस FAILED;
	पूर्ण

	/*
	 * Only eh_पात processing will हटाओ the IO from
	 * active_cmd_q beक्रमe processing the request. this is
	 * करोne to aव्योम race conditions between IOs पातed
	 * as part of task management completion and eh_पात
	 * processing
	 */
	list_del_init(&io_req->link);
	io_req->on_active_queue = 0;
	/* Move IO req to retire queue */
	list_add_tail(&io_req->link, &tgt->io_retire_queue);

	init_completion(&io_req->abts_करोne);
	init_completion(&io_req->cleanup_करोne);

	अगर (test_and_set_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "eh_abort: io_req (xid = 0x%x) "
				"already in abts processing\n", io_req->xid);
		अगर (cancel_delayed_work(&io_req->समयout_work))
			kref_put(&io_req->refcount,
				 bnx2fc_cmd_release); /* drop समयr hold */
		/*
		 * We करोn't want to hold off the upper layer समयr so simply
		 * cleanup the command and वापस that I/O was successfully
		 * पातed.
		 */
		rc = bnx2fc_abts_cleanup(io_req);
		/* This only occurs when an task पात was requested जबतक ABTS
		   is in progress.  Setting the IO_CLEANUP flag will skip the
		   RRQ process in the हाल when the fw generated SCSI_CMD cmpl
		   was a result from the ABTS request rather than the CLEANUP
		   request */
		set_bit(BNX2FC_FLAG_IO_CLEANUP,	&io_req->req_flags);
		rc = FAILED;
		जाओ करोne;
	पूर्ण

	/* Cancel the current समयr running on this io_req */
	अगर (cancel_delayed_work(&io_req->समयout_work))
		kref_put(&io_req->refcount,
			 bnx2fc_cmd_release); /* drop समयr hold */
	set_bit(BNX2FC_FLAG_EH_ABORT, &io_req->req_flags);
	io_req->रुको_क्रम_abts_comp = 1;
	rc = bnx2fc_initiate_abts(io_req);
	अगर (rc == FAILED) अणु
		io_req->रुको_क्रम_cleanup_comp = 1;
		bnx2fc_initiate_cleanup(io_req);
		spin_unlock_bh(&tgt->tgt_lock);
		रुको_क्रम_completion(&io_req->cleanup_करोne);
		spin_lock_bh(&tgt->tgt_lock);
		io_req->रुको_क्रम_cleanup_comp = 0;
		जाओ करोne;
	पूर्ण
	spin_unlock_bh(&tgt->tgt_lock);

	/* Wait 2 * RA_TOV + 1 to be sure समयout function hasn't fired */
	समय_left = रुको_क्रम_completion_समयout(&io_req->abts_करोne,
					msecs_to_jअगरfies(2 * rp->r_a_tov + 1));
	अगर (समय_left)
		BNX2FC_IO_DBG(io_req,
			      "Timed out in eh_abort waiting for abts_done");

	spin_lock_bh(&tgt->tgt_lock);
	io_req->रुको_क्रम_abts_comp = 0;
	अगर (test_bit(BNX2FC_FLAG_IO_COMPL, &io_req->req_flags)) अणु
		BNX2FC_IO_DBG(io_req, "IO completed in a different context\n");
		rc = SUCCESS;
	पूर्ण अन्यथा अगर (!(test_and_set_bit(BNX2FC_FLAG_ABTS_DONE,
				      &io_req->req_flags))) अणु
		/* Let the scsi-ml try to recover this command */
		prपूर्णांकk(KERN_ERR PFX "abort failed, xid = 0x%x\n",
		       io_req->xid);
		/*
		 * Cleanup firmware residuals beक्रमe वापसing control back
		 * to SCSI ML.
		 */
		rc = bnx2fc_abts_cleanup(io_req);
		जाओ करोne;
	पूर्ण अन्यथा अणु
		/*
		 * We come here even when there was a race condition
		 * between समयout and abts completion, and abts
		 * completion happens just in समय.
		 */
		BNX2FC_IO_DBG(io_req, "abort succeeded\n");
		rc = SUCCESS;
		bnx2fc_scsi_करोne(io_req, DID_ABORT);
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
	पूर्ण
करोne:
	/* release the reference taken in eh_पात */
	kref_put(&io_req->refcount, bnx2fc_cmd_release);
	spin_unlock_bh(&tgt->tgt_lock);
	वापस rc;
पूर्ण

व्योम bnx2fc_process_seq_cleanup_compl(काष्ठा bnx2fc_cmd *seq_clnp_req,
				      काष्ठा fcoe_task_ctx_entry *task,
				      u8 rx_state)
अणु
	काष्ठा bnx2fc_els_cb_arg *cb_arg = seq_clnp_req->cb_arg;
	काष्ठा bnx2fc_cmd *orig_io_req = cb_arg->पातed_io_req;
	u32 offset = cb_arg->offset;
	क्रमागत fc_rctl r_ctl = cb_arg->r_ctl;
	पूर्णांक rc = 0;
	काष्ठा bnx2fc_rport *tgt = orig_io_req->tgt;

	BNX2FC_IO_DBG(orig_io_req, "Entered process_cleanup_compl xid = 0x%x"
			      "cmd_type = %d\n",
		   seq_clnp_req->xid, seq_clnp_req->cmd_type);

	अगर (rx_state == FCOE_TASK_RX_STATE_IGNORED_SEQUENCE_CLEANUP) अणु
		prपूर्णांकk(KERN_ERR PFX "seq cleanup ignored - xid = 0x%x\n",
			seq_clnp_req->xid);
		जाओ मुक्त_cb_arg;
	पूर्ण

	spin_unlock_bh(&tgt->tgt_lock);
	rc = bnx2fc_send_srr(orig_io_req, offset, r_ctl);
	spin_lock_bh(&tgt->tgt_lock);

	अगर (rc)
		prपूर्णांकk(KERN_ERR PFX "clnup_compl: Unable to send SRR"
			" IO will abort\n");
	seq_clnp_req->cb_arg = शून्य;
	kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
मुक्त_cb_arg:
	kमुक्त(cb_arg);
	वापस;
पूर्ण

व्योम bnx2fc_process_cleanup_compl(काष्ठा bnx2fc_cmd *io_req,
				  काष्ठा fcoe_task_ctx_entry *task,
				  u8 num_rq)
अणु
	BNX2FC_IO_DBG(io_req, "Entered process_cleanup_compl "
			      "refcnt = %d, cmd_type = %d\n",
		   kref_पढ़ो(&io_req->refcount), io_req->cmd_type);
	/*
	 * Test whether there is a cleanup request pending. If not just
	 * निकास.
	 */
	अगर (!test_and_clear_bit(BNX2FC_FLAG_ISSUE_CLEANUP_REQ,
				&io_req->req_flags))
		वापस;
	/*
	 * If we receive a cleanup completion क्रम this request then the
	 * firmware will not give us an पात completion क्रम this request
	 * so clear any ABTS pending flags.
	 */
	अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags) &&
	    !test_bit(BNX2FC_FLAG_ABTS_DONE, &io_req->req_flags)) अणु
		set_bit(BNX2FC_FLAG_ABTS_DONE, &io_req->req_flags);
		अगर (io_req->रुको_क्रम_abts_comp)
			complete(&io_req->abts_करोne);
	पूर्ण

	bnx2fc_scsi_करोne(io_req, DID_ERROR);
	kref_put(&io_req->refcount, bnx2fc_cmd_release);
	अगर (io_req->रुको_क्रम_cleanup_comp)
		complete(&io_req->cleanup_करोne);
पूर्ण

व्योम bnx2fc_process_abts_compl(काष्ठा bnx2fc_cmd *io_req,
			       काष्ठा fcoe_task_ctx_entry *task,
			       u8 num_rq)
अणु
	u32 r_ctl;
	u32 r_a_tov = FC_DEF_R_A_TOV;
	u8 issue_rrq = 0;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;

	BNX2FC_IO_DBG(io_req, "Entered process_abts_compl xid = 0x%x"
			      "refcnt = %d, cmd_type = %d\n",
		   io_req->xid,
		   kref_पढ़ो(&io_req->refcount), io_req->cmd_type);

	अगर (test_and_set_bit(BNX2FC_FLAG_ABTS_DONE,
				       &io_req->req_flags)) अणु
		BNX2FC_IO_DBG(io_req, "Timer context finished processing"
				" this io\n");
		वापस;
	पूर्ण

	/*
	 * If we receive an ABTS completion here then we will not receive
	 * a cleanup completion so clear any cleanup pending flags.
	 */
	अगर (test_bit(BNX2FC_FLAG_ISSUE_CLEANUP_REQ, &io_req->req_flags)) अणु
		clear_bit(BNX2FC_FLAG_ISSUE_CLEANUP_REQ, &io_req->req_flags);
		अगर (io_req->रुको_क्रम_cleanup_comp)
			complete(&io_req->cleanup_करोne);
	पूर्ण

	/* Do not issue RRQ as this IO is alपढ़ोy cleanedup */
	अगर (test_and_set_bit(BNX2FC_FLAG_IO_CLEANUP,
				&io_req->req_flags))
		जाओ io_compl;

	/*
	 * For ABTS issued due to SCSI eh_पात_handler, समयout
	 * values are मुख्यtained by scsi-ml itself. Cancel समयout
	 * in हाल ABTS issued as part of task management function
	 * or due to FW error.
	 */
	अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags))
		अगर (cancel_delayed_work(&io_req->समयout_work))
			kref_put(&io_req->refcount,
				 bnx2fc_cmd_release); /* drop समयr hold */

	r_ctl = (u8)task->rxwr_only.जोड़_ctx.comp_info.abts_rsp.r_ctl;

	चयन (r_ctl) अणु
	हाल FC_RCTL_BA_ACC:
		/*
		 * Dont release this cmd yet. It will be relesed
		 * after we get RRQ response
		 */
		BNX2FC_IO_DBG(io_req, "ABTS response - ACC Send RRQ\n");
		issue_rrq = 1;
		अवरोध;

	हाल FC_RCTL_BA_RJT:
		BNX2FC_IO_DBG(io_req, "ABTS response - RJT\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "Unknown ABTS response\n");
		अवरोध;
	पूर्ण

	अगर (issue_rrq) अणु
		BNX2FC_IO_DBG(io_req, "Issue RRQ after R_A_TOV\n");
		set_bit(BNX2FC_FLAG_ISSUE_RRQ, &io_req->req_flags);
	पूर्ण
	set_bit(BNX2FC_FLAG_RETIRE_OXID, &io_req->req_flags);
	bnx2fc_cmd_समयr_set(io_req, r_a_tov);

io_compl:
	अगर (io_req->रुको_क्रम_abts_comp) अणु
		अगर (test_and_clear_bit(BNX2FC_FLAG_EH_ABORT,
				       &io_req->req_flags))
			complete(&io_req->abts_करोne);
	पूर्ण अन्यथा अणु
		/*
		 * We end up here when ABTS is issued as
		 * in asynchronous context, i.e., as part
		 * of task management completion, or
		 * when FW error is received or when the
		 * ABTS is issued when the IO is समयd
		 * out.
		 */

		अगर (io_req->on_active_queue) अणु
			list_del_init(&io_req->link);
			io_req->on_active_queue = 0;
			/* Move IO req to retire queue */
			list_add_tail(&io_req->link, &tgt->io_retire_queue);
		पूर्ण
		bnx2fc_scsi_करोne(io_req, DID_ERROR);
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
	पूर्ण
पूर्ण

अटल व्योम bnx2fc_lun_reset_cmpl(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा bnx2fc_cmd *cmd, *पंचांगp;
	u64 पंचांग_lun = sc_cmd->device->lun;
	u64 lun;
	पूर्णांक rc = 0;

	/* called with tgt_lock held */
	BNX2FC_IO_DBG(io_req, "Entered bnx2fc_lun_reset_cmpl\n");
	/*
	 * Walk thru the active_ios queue and ABORT the IO
	 * that matches with the LUN that was reset
	 */
	list_क्रम_each_entry_safe(cmd, पंचांगp, &tgt->active_cmd_queue, link) अणु
		BNX2FC_TGT_DBG(tgt, "LUN RST cmpl: scan for pending IOs\n");
		lun = cmd->sc_cmd->device->lun;
		अगर (lun == पंचांग_lun) अणु
			/* Initiate ABTS on this cmd */
			अगर (!test_and_set_bit(BNX2FC_FLAG_ISSUE_ABTS,
					      &cmd->req_flags)) अणु
				/* cancel the IO समयout */
				अगर (cancel_delayed_work(&io_req->समयout_work))
					kref_put(&io_req->refcount,
						 bnx2fc_cmd_release);
							/* समयr hold */
				rc = bnx2fc_initiate_abts(cmd);
				/* abts shouldn't fail in this context */
				WARN_ON(rc != SUCCESS);
			पूर्ण अन्यथा
				prपूर्णांकk(KERN_ERR PFX "lun_rst: abts already in"
					" progress for this IO 0x%x\n",
					cmd->xid);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2fc_tgt_reset_cmpl(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा bnx2fc_cmd *cmd, *पंचांगp;
	पूर्णांक rc = 0;

	/* called with tgt_lock held */
	BNX2FC_IO_DBG(io_req, "Entered bnx2fc_tgt_reset_cmpl\n");
	/*
	 * Walk thru the active_ios queue and ABORT the IO
	 * that matches with the LUN that was reset
	 */
	list_क्रम_each_entry_safe(cmd, पंचांगp, &tgt->active_cmd_queue, link) अणु
		BNX2FC_TGT_DBG(tgt, "TGT RST cmpl: scan for pending IOs\n");
		/* Initiate ABTS */
		अगर (!test_and_set_bit(BNX2FC_FLAG_ISSUE_ABTS,
							&cmd->req_flags)) अणु
			/* cancel the IO समयout */
			अगर (cancel_delayed_work(&io_req->समयout_work))
				kref_put(&io_req->refcount,
					 bnx2fc_cmd_release); /* समयr hold */
			rc = bnx2fc_initiate_abts(cmd);
			/* abts shouldn't fail in this context */
			WARN_ON(rc != SUCCESS);

		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR PFX "tgt_rst: abts already in progress"
				" for this IO 0x%x\n", cmd->xid);
	पूर्ण
पूर्ण

व्योम bnx2fc_process_पंचांग_compl(काष्ठा bnx2fc_cmd *io_req,
			     काष्ठा fcoe_task_ctx_entry *task, u8 num_rq,
				  अचिन्हित अक्षर *rq_data)
अणु
	काष्ठा bnx2fc_mp_req *पंचांग_req;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	u64 *hdr;
	u64 *temp_hdr;
	व्योम *rsp_buf;

	/* Called with tgt_lock held */
	BNX2FC_IO_DBG(io_req, "Entered process_tm_compl\n");

	अगर (!(test_bit(BNX2FC_FLAG_TM_TIMEOUT, &io_req->req_flags)))
		set_bit(BNX2FC_FLAG_TM_COMPL, &io_req->req_flags);
	अन्यथा अणु
		/* TM has alपढ़ोy समयd out and we got
		 * delayed completion. Ignore completion
		 * processing.
		 */
		वापस;
	पूर्ण

	पंचांग_req = &(io_req->mp_req);
	fc_hdr = &(पंचांग_req->resp_fc_hdr);
	hdr = (u64 *)fc_hdr;
	temp_hdr = (u64 *)
		&task->rxwr_only.जोड़_ctx.comp_info.mp_rsp.fc_hdr;
	hdr[0] = cpu_to_be64(temp_hdr[0]);
	hdr[1] = cpu_to_be64(temp_hdr[1]);
	hdr[2] = cpu_to_be64(temp_hdr[2]);

	पंचांग_req->resp_len =
		task->rxwr_only.जोड़_ctx.comp_info.mp_rsp.mp_payload_len;

	rsp_buf = पंचांग_req->resp_buf;

	अगर (fc_hdr->fh_r_ctl == FC_RCTL_DD_CMD_STATUS) अणु
		bnx2fc_parse_fcp_rsp(io_req,
				     (काष्ठा fcoe_fcp_rsp_payload *)
				     rsp_buf, num_rq, rq_data);
		अगर (io_req->fcp_rsp_code == 0) अणु
			/* TM successful */
			अगर (पंचांग_req->पंचांग_flags & FCP_TMF_LUN_RESET)
				bnx2fc_lun_reset_cmpl(io_req);
			अन्यथा अगर (पंचांग_req->पंचांग_flags & FCP_TMF_TGT_RESET)
				bnx2fc_tgt_reset_cmpl(io_req);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "tmf's fc_hdr r_ctl = 0x%x\n",
			fc_hdr->fh_r_ctl);
	पूर्ण
	अगर (!sc_cmd->SCp.ptr) अणु
		prपूर्णांकk(KERN_ERR PFX "tm_compl: SCp.ptr is NULL\n");
		वापस;
	पूर्ण
	चयन (io_req->fcp_status) अणु
	हाल FC_GOOD:
		अगर (io_req->cdb_status == 0) अणु
			/* Good IO completion */
			sc_cmd->result = DID_OK << 16;
		पूर्ण अन्यथा अणु
			/* Transport status is good, SCSI status not good */
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;
		पूर्ण
		अगर (io_req->fcp_resid)
			scsi_set_resid(sc_cmd, io_req->fcp_resid);
		अवरोध;

	शेष:
		BNX2FC_IO_DBG(io_req, "process_tm_compl: fcp_status = %d\n",
			   io_req->fcp_status);
		अवरोध;
	पूर्ण

	sc_cmd = io_req->sc_cmd;
	io_req->sc_cmd = शून्य;

	/* check अगर the io_req exists in tgt's पंचांगf_q */
	अगर (io_req->on_पंचांगf_queue) अणु

		list_del_init(&io_req->link);
		io_req->on_पंचांगf_queue = 0;
	पूर्ण अन्यथा अणु

		prपूर्णांकk(KERN_ERR PFX "Command not on active_cmd_queue!\n");
		वापस;
	पूर्ण

	sc_cmd->SCp.ptr = शून्य;
	sc_cmd->scsi_करोne(sc_cmd);

	kref_put(&io_req->refcount, bnx2fc_cmd_release);
	अगर (io_req->रुको_क्रम_abts_comp) अणु
		BNX2FC_IO_DBG(io_req, "tm_compl - wake up the waiter\n");
		complete(&io_req->abts_करोne);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2fc_split_bd(काष्ठा bnx2fc_cmd *io_req, u64 addr, पूर्णांक sg_len,
			   पूर्णांक bd_index)
अणु
	काष्ठा fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	पूर्णांक frag_size, sg_frags;

	sg_frags = 0;
	जबतक (sg_len) अणु
		अगर (sg_len >= BNX2FC_BD_SPLIT_SZ)
			frag_size = BNX2FC_BD_SPLIT_SZ;
		अन्यथा
			frag_size = sg_len;
		bd[bd_index + sg_frags].buf_addr_lo = addr & 0xffffffff;
		bd[bd_index + sg_frags].buf_addr_hi  = addr >> 32;
		bd[bd_index + sg_frags].buf_len = (u16)frag_size;
		bd[bd_index + sg_frags].flags = 0;

		addr += (u64) frag_size;
		sg_frags++;
		sg_len -= frag_size;
	पूर्ण
	वापस sg_frags;

पूर्ण

अटल पूर्णांक bnx2fc_map_sg(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = io_req->port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;
	काष्ठा fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	काष्ठा scatterlist *sg;
	पूर्णांक byte_count = 0;
	पूर्णांक sg_count = 0;
	पूर्णांक bd_count = 0;
	पूर्णांक sg_frags;
	अचिन्हित पूर्णांक sg_len;
	u64 addr;
	पूर्णांक i;

	WARN_ON(scsi_sg_count(sc) > BNX2FC_MAX_BDS_PER_CMD);
	/*
	 * Use dma_map_sg directly to ensure we're using the correct
	 * dev काष्ठा off of pcidev.
	 */
	sg_count = dma_map_sg(&hba->pcidev->dev, scsi_sglist(sc),
			      scsi_sg_count(sc), sc->sc_data_direction);
	scsi_क्रम_each_sg(sc, sg, sg_count, i) अणु
		sg_len = sg_dma_len(sg);
		addr = sg_dma_address(sg);
		अगर (sg_len > BNX2FC_MAX_BD_LEN) अणु
			sg_frags = bnx2fc_split_bd(io_req, addr, sg_len,
						   bd_count);
		पूर्ण अन्यथा अणु

			sg_frags = 1;
			bd[bd_count].buf_addr_lo = addr & 0xffffffff;
			bd[bd_count].buf_addr_hi  = addr >> 32;
			bd[bd_count].buf_len = (u16)sg_len;
			bd[bd_count].flags = 0;
		पूर्ण
		bd_count += sg_frags;
		byte_count += sg_len;
	पूर्ण
	अगर (byte_count != scsi_bufflen(sc))
		prपूर्णांकk(KERN_ERR PFX "byte_count = %d != scsi_bufflen = %d, "
			"task_id = 0x%x\n", byte_count, scsi_bufflen(sc),
			io_req->xid);
	वापस bd_count;
पूर्ण

अटल पूर्णांक bnx2fc_build_bd_list_from_sg(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;
	काष्ठा fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	पूर्णांक bd_count;

	अगर (scsi_sg_count(sc)) अणु
		bd_count = bnx2fc_map_sg(io_req);
		अगर (bd_count == 0)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		bd_count = 0;
		bd[0].buf_addr_lo = bd[0].buf_addr_hi = 0;
		bd[0].buf_len = bd[0].flags = 0;
	पूर्ण
	io_req->bd_tbl->bd_valid = bd_count;

	/*
	 * Return the command to ML अगर BD count exceeds the max number
	 * that can be handled by FW.
	 */
	अगर (bd_count > BNX2FC_FW_MAX_BDS_PER_CMD) अणु
		pr_err("bd_count = %d exceeded FW supported max BD(255), task_id = 0x%x\n",
		       bd_count, io_req->xid);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2fc_unmap_sg_list(काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा scsi_cmnd *sc = io_req->sc_cmd;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = io_req->port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;

	/*
	 * Use dma_unmap_sg directly to ensure we're using the correct
	 * dev काष्ठा off of pcidev.
	 */
	अगर (io_req->bd_tbl->bd_valid && sc && scsi_sg_count(sc)) अणु
		dma_unmap_sg(&hba->pcidev->dev, scsi_sglist(sc),
		    scsi_sg_count(sc), sc->sc_data_direction);
		io_req->bd_tbl->bd_valid = 0;
	पूर्ण
पूर्ण

व्योम bnx2fc_build_fcp_cmnd(काष्ठा bnx2fc_cmd *io_req,
				  काष्ठा fcp_cmnd *fcp_cmnd)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;

	स_रखो(fcp_cmnd, 0, माप(काष्ठा fcp_cmnd));

	पूर्णांक_to_scsilun(sc_cmd->device->lun, &fcp_cmnd->fc_lun);

	fcp_cmnd->fc_dl = htonl(io_req->data_xfer_len);
	स_नकल(fcp_cmnd->fc_cdb, sc_cmd->cmnd, sc_cmd->cmd_len);

	fcp_cmnd->fc_cmdref = 0;
	fcp_cmnd->fc_pri_ta = 0;
	fcp_cmnd->fc_पंचांग_flags = io_req->mp_req.पंचांग_flags;
	fcp_cmnd->fc_flags = io_req->io_req_flags;
	fcp_cmnd->fc_pri_ta = FCP_PTA_SIMPLE;
पूर्ण

अटल व्योम bnx2fc_parse_fcp_rsp(काष्ठा bnx2fc_cmd *io_req,
				 काष्ठा fcoe_fcp_rsp_payload *fcp_rsp,
				 u8 num_rq, अचिन्हित अक्षर *rq_data)
अणु
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	u8 rsp_flags = fcp_rsp->fcp_flags.flags;
	u32 rq_buff_len = 0;
	पूर्णांक fcp_sns_len = 0;
	पूर्णांक fcp_rsp_len = 0;

	io_req->fcp_status = FC_GOOD;
	io_req->fcp_resid = 0;
	अगर (rsp_flags & (FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER |
	    FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER))
		io_req->fcp_resid = fcp_rsp->fcp_resid;

	io_req->scsi_comp_flags = rsp_flags;
	CMD_SCSI_STATUS(sc_cmd) = io_req->cdb_status =
				fcp_rsp->scsi_status_code;

	/* Fetch fcp_rsp_info and fcp_sns_info अगर available */
	अगर (num_rq) अणु

		/*
		 * We करो not anticipate num_rq >1, as the linux defined
		 * SCSI_SENSE_BUFFERSIZE is 96 bytes + 8 bytes of FCP_RSP_INFO
		 * 256 bytes of single rq buffer is good enough to hold this.
		 */

		अगर (rsp_flags &
		    FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID) अणु
			fcp_rsp_len = rq_buff_len
					= fcp_rsp->fcp_rsp_len;
		पूर्ण

		अगर (rsp_flags &
		    FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID) अणु
			fcp_sns_len = fcp_rsp->fcp_sns_len;
			rq_buff_len += fcp_rsp->fcp_sns_len;
		पूर्ण

		io_req->fcp_rsp_len = fcp_rsp_len;
		io_req->fcp_sns_len = fcp_sns_len;

		अगर (rq_buff_len > num_rq * BNX2FC_RQ_BUF_SZ) अणु
			/* Invalid sense sense length. */
			prपूर्णांकk(KERN_ERR PFX "invalid sns length %d\n",
				rq_buff_len);
			/* reset rq_buff_len */
			rq_buff_len =  num_rq * BNX2FC_RQ_BUF_SZ;
		पूर्ण

		/* fetch fcp_rsp_code */
		अगर ((fcp_rsp_len == 4) || (fcp_rsp_len == 8)) अणु
			/* Only क्रम task management function */
			io_req->fcp_rsp_code = rq_data[3];
			BNX2FC_IO_DBG(io_req, "fcp_rsp_code = %d\n",
				io_req->fcp_rsp_code);
		पूर्ण

		/* fetch sense data */
		rq_data += fcp_rsp_len;

		अगर (fcp_sns_len > SCSI_SENSE_BUFFERSIZE) अणु
			prपूर्णांकk(KERN_ERR PFX "Truncating sense buffer\n");
			fcp_sns_len = SCSI_SENSE_BUFFERSIZE;
		पूर्ण

		स_रखो(sc_cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		अगर (fcp_sns_len)
			स_नकल(sc_cmd->sense_buffer, rq_data, fcp_sns_len);

	पूर्ण
पूर्ण

/**
 * bnx2fc_queuecommand - Queuecommand function of the scsi ढाँचा
 *
 * @host:	The Scsi_Host the command was issued to
 * @sc_cmd:	काष्ठा scsi_cmnd to be executed
 *
 * This is the IO strategy routine, called by SCSI-ML
 **/
पूर्णांक bnx2fc_queuecommand(काष्ठा Scsi_Host *host,
			काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_lport *lport = shost_priv(host);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा bnx2fc_cmd *io_req;
	पूर्णांक rc = 0;
	पूर्णांक rval;

	rval = fc_remote_port_chkपढ़ोy(rport);
	अगर (rval) अणु
		sc_cmd->result = rval;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	अगर ((lport->state != LPORT_ST_READY) || !(lport->link_up)) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ निकास_qcmd;
	पूर्ण

	/* rport and tgt are allocated together, so tgt should be non-शून्य */
	tgt = (काष्ठा bnx2fc_rport *)&rp[1];

	अगर (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags)) अणु
		/*
		 * Session is not offloaded yet. Let SCSI-ml retry
		 * the command.
		 */
		rc = SCSI_MLQUEUE_TARGET_BUSY;
		जाओ निकास_qcmd;
	पूर्ण
	अगर (tgt->retry_delay_बारtamp) अणु
		अगर (समय_after(jअगरfies, tgt->retry_delay_बारtamp)) अणु
			tgt->retry_delay_बारtamp = 0;
		पूर्ण अन्यथा अणु
			/* If retry_delay समयr is active, flow off the ML */
			rc = SCSI_MLQUEUE_TARGET_BUSY;
			जाओ निकास_qcmd;
		पूर्ण
	पूर्ण

	spin_lock_bh(&tgt->tgt_lock);

	io_req = bnx2fc_cmd_alloc(tgt);
	अगर (!io_req) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ निकास_qcmd_tgtlock;
	पूर्ण
	io_req->sc_cmd = sc_cmd;

	अगर (bnx2fc_post_io_req(tgt, io_req)) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to post io_req\n");
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ निकास_qcmd_tgtlock;
	पूर्ण

निकास_qcmd_tgtlock:
	spin_unlock_bh(&tgt->tgt_lock);
निकास_qcmd:
	वापस rc;
पूर्ण

व्योम bnx2fc_process_scsi_cmd_compl(काष्ठा bnx2fc_cmd *io_req,
				   काष्ठा fcoe_task_ctx_entry *task,
				   u8 num_rq, अचिन्हित अक्षर *rq_data)
अणु
	काष्ठा fcoe_fcp_rsp_payload *fcp_rsp;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा scsi_cmnd *sc_cmd;
	u16 scope = 0, qualअगरier = 0;

	/* scsi_cmd_cmpl is called with tgt lock held */

	अगर (test_and_set_bit(BNX2FC_FLAG_IO_COMPL, &io_req->req_flags)) अणु
		/* we will not receive ABTS response क्रम this IO */
		BNX2FC_IO_DBG(io_req, "Timer context finished processing "
			   "this scsi cmd\n");
		अगर (test_and_clear_bit(BNX2FC_FLAG_IO_CLEANUP,
				       &io_req->req_flags)) अणु
			BNX2FC_IO_DBG(io_req,
				      "Actual completion after cleanup request cleaning up\n");
			bnx2fc_process_cleanup_compl(io_req, task, num_rq);
		पूर्ण
		वापस;
	पूर्ण

	/* Cancel the समयout_work, as we received IO completion */
	अगर (cancel_delayed_work(&io_req->समयout_work))
		kref_put(&io_req->refcount,
			 bnx2fc_cmd_release); /* drop समयr hold */

	sc_cmd = io_req->sc_cmd;
	अगर (sc_cmd == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "scsi_cmd_compl - sc_cmd is NULL\n");
		वापस;
	पूर्ण

	/* Fetch fcp_rsp from task context and perक्रमm cmd completion */
	fcp_rsp = (काष्ठा fcoe_fcp_rsp_payload *)
		   &(task->rxwr_only.जोड़_ctx.comp_info.fcp_rsp.payload);

	/* parse fcp_rsp and obtain sense data from RQ अगर available */
	bnx2fc_parse_fcp_rsp(io_req, fcp_rsp, num_rq, rq_data);

	अगर (!sc_cmd->SCp.ptr) अणु
		prपूर्णांकk(KERN_ERR PFX "SCp.ptr is NULL\n");
		वापस;
	पूर्ण

	अगर (io_req->on_active_queue) अणु
		list_del_init(&io_req->link);
		io_req->on_active_queue = 0;
		/* Move IO req to retire queue */
		list_add_tail(&io_req->link, &tgt->io_retire_queue);
	पूर्ण अन्यथा अणु
		/* This should not happen, but could have been pulled
		 * by bnx2fc_flush_active_ios(), or during a race
		 * between command पात and (late) completion.
		 */
		BNX2FC_IO_DBG(io_req, "xid not on active_cmd_queue\n");
		अगर (io_req->रुको_क्रम_abts_comp)
			अगर (test_and_clear_bit(BNX2FC_FLAG_EH_ABORT,
					       &io_req->req_flags))
				complete(&io_req->abts_करोne);
	पूर्ण

	bnx2fc_unmap_sg_list(io_req);
	io_req->sc_cmd = शून्य;

	चयन (io_req->fcp_status) अणु
	हाल FC_GOOD:
		अगर (io_req->cdb_status == 0) अणु
			/* Good IO completion */
			sc_cmd->result = DID_OK << 16;
		पूर्ण अन्यथा अणु
			/* Transport status is good, SCSI status not good */
			BNX2FC_IO_DBG(io_req, "scsi_cmpl: cdb_status = %d"
				 " fcp_resid = 0x%x\n",
				io_req->cdb_status, io_req->fcp_resid);
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;

			अगर (io_req->cdb_status == SAM_STAT_TASK_SET_FULL ||
			    io_req->cdb_status == SAM_STAT_BUSY) अणु
				/* Newer array firmware with BUSY or
				 * TASK_SET_FULL may वापस a status that needs
				 * the scope bits masked.
				 * Or a huge delay बारtamp up to 27 minutes
				 * can result.
				 */
				अगर (fcp_rsp->retry_delay_समयr) अणु
					/* Upper 2 bits */
					scope = fcp_rsp->retry_delay_समयr
						& 0xC000;
					/* Lower 14 bits */
					qualअगरier = fcp_rsp->retry_delay_समयr
						& 0x3FFF;
				पूर्ण
				अगर (scope > 0 && qualअगरier > 0 &&
					qualअगरier <= 0x3FEF) अणु
					/* Set the jअगरfies +
					 * retry_delay_समयr * 100ms
					 * क्रम the rport/tgt
					 */
					tgt->retry_delay_बारtamp = jअगरfies +
						(qualअगरier * HZ / 10);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (io_req->fcp_resid)
			scsi_set_resid(sc_cmd, io_req->fcp_resid);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "scsi_cmd_compl: fcp_status = %d\n",
			io_req->fcp_status);
		अवरोध;
	पूर्ण
	sc_cmd->SCp.ptr = शून्य;
	sc_cmd->scsi_करोne(sc_cmd);
	kref_put(&io_req->refcount, bnx2fc_cmd_release);
पूर्ण

पूर्णांक bnx2fc_post_io_req(काष्ठा bnx2fc_rport *tgt,
			       काष्ठा bnx2fc_cmd *io_req)
अणु
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा fc_lport *lport = port->lport;
	काष्ठा fc_stats *stats;
	पूर्णांक task_idx, index;
	u16 xid;

	/* bnx2fc_post_io_req() is called with the tgt_lock held */

	/* Initialize rest of io_req fields */
	io_req->cmd_type = BNX2FC_SCSI_CMD;
	io_req->port = port;
	io_req->tgt = tgt;
	io_req->data_xfer_len = scsi_bufflen(sc_cmd);
	sc_cmd->SCp.ptr = (अक्षर *)io_req;

	stats = per_cpu_ptr(lport->stats, get_cpu());
	अगर (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		io_req->io_req_flags = BNX2FC_READ;
		stats->InputRequests++;
		stats->InputBytes += io_req->data_xfer_len;
	पूर्ण अन्यथा अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		io_req->io_req_flags = BNX2FC_WRITE;
		stats->OutputRequests++;
		stats->OutputBytes += io_req->data_xfer_len;
	पूर्ण अन्यथा अणु
		io_req->io_req_flags = 0;
		stats->ControlRequests++;
	पूर्ण
	put_cpu();

	xid = io_req->xid;

	/* Build buffer descriptor list क्रम firmware from sg list */
	अगर (bnx2fc_build_bd_list_from_sg(io_req)) अणु
		prपूर्णांकk(KERN_ERR PFX "BD list creation failed\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		वापस -EAGAIN;
	पूर्ण

	task_idx = xid / BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *) hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_task(io_req, task);

	अगर (tgt->flush_in_prog) अणु
		prपूर्णांकk(KERN_ERR PFX "Flush in progress..Host Busy\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		वापस -EAGAIN;
	पूर्ण

	अगर (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "Session not ready...post_io\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		वापस -EAGAIN;
	पूर्ण

	/* Time IO req */
	अगर (tgt->io_समयout)
		bnx2fc_cmd_समयr_set(io_req, BNX2FC_IO_TIMEOUT);
	/* Obtain मुक्त SQ entry */
	bnx2fc_add_2_sq(tgt, xid);

	/* Enqueue the io_req to active_cmd_queue */

	io_req->on_active_queue = 1;
	/* move io_req from pending_queue to active_queue */
	list_add_tail(&io_req->link, &tgt->active_cmd_queue);

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);
	वापस 0;
पूर्ण
