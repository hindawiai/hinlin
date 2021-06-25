<शैली गुरु>
/* bnx2fc_tgt.c: QLogic Linux FCoE offload driver.
 * Handles operations such as session offload/upload etc, and manages
 * session resources such as connection id and qp resources.
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
अटल व्योम bnx2fc_upld_समयr(काष्ठा समयr_list *t);
अटल व्योम bnx2fc_ofld_समयr(काष्ठा समयr_list *t);
अटल पूर्णांक bnx2fc_init_tgt(काष्ठा bnx2fc_rport *tgt,
			   काष्ठा fcoe_port *port,
			   काष्ठा fc_rport_priv *rdata);
अटल u32 bnx2fc_alloc_conn_id(काष्ठा bnx2fc_hba *hba,
				काष्ठा bnx2fc_rport *tgt);
अटल पूर्णांक bnx2fc_alloc_session_resc(काष्ठा bnx2fc_hba *hba,
			      काष्ठा bnx2fc_rport *tgt);
अटल व्योम bnx2fc_मुक्त_session_resc(काष्ठा bnx2fc_hba *hba,
			      काष्ठा bnx2fc_rport *tgt);
अटल व्योम bnx2fc_मुक्त_conn_id(काष्ठा bnx2fc_hba *hba, u32 conn_id);

अटल व्योम bnx2fc_upld_समयr(काष्ठा समयr_list *t)
अणु

	काष्ठा bnx2fc_rport *tgt = from_समयr(tgt, t, upld_समयr);

	BNX2FC_TGT_DBG(tgt, "upld_timer - Upload compl not received!!\n");
	/* fake upload completion */
	clear_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
	clear_bit(BNX2FC_FLAG_ENABLED, &tgt->flags);
	set_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
	wake_up_पूर्णांकerruptible(&tgt->upld_रुको);
पूर्ण

अटल व्योम bnx2fc_ofld_समयr(काष्ठा समयr_list *t)
अणु

	काष्ठा bnx2fc_rport *tgt = from_समयr(tgt, t, ofld_समयr);

	BNX2FC_TGT_DBG(tgt, "entered bnx2fc_ofld_timer\n");
	/* NOTE: This function should never be called, as
	 * offload should never समयout
	 */
	/*
	 * If the समयr has expired, this session is dead
	 * Clear offloaded flag and logout of this device.
	 * Since OFFLOADED flag is cleared, this हाल
	 * will be considered as offload error and the
	 * port will be logged off, and conn_id, session
	 * resources are मुक्तd up in bnx2fc_offload_session
	 */
	clear_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
	clear_bit(BNX2FC_FLAG_ENABLED, &tgt->flags);
	set_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	wake_up_पूर्णांकerruptible(&tgt->ofld_रुको);
पूर्ण

अटल व्योम bnx2fc_ofld_रुको(काष्ठा bnx2fc_rport *tgt)
अणु
	समयr_setup(&tgt->ofld_समयr, bnx2fc_ofld_समयr, 0);
	mod_समयr(&tgt->ofld_समयr, jअगरfies + BNX2FC_FW_TIMEOUT);

	रुको_event_पूर्णांकerruptible(tgt->ofld_रुको,
				 (test_bit(
				  BNX2FC_FLAG_OFLD_REQ_CMPL,
				  &tgt->flags)));
	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&tgt->ofld_समयr);
पूर्ण

अटल व्योम bnx2fc_offload_session(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt,
					काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_rport *rport = rdata->rport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	पूर्णांक rval;
	पूर्णांक i = 0;

	/* Initialize bnx2fc_rport */
	/* NOTE: tgt is alपढ़ोy bzero'd */
	rval = bnx2fc_init_tgt(tgt, port, rdata);
	अगर (rval) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to allocate conn id for "
			"port_id (%6x)\n", rport->port_id);
		जाओ tgt_init_err;
	पूर्ण

	/* Allocate session resources */
	rval = bnx2fc_alloc_session_resc(hba, tgt);
	अगर (rval) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to allocate resources\n");
		जाओ ofld_err;
	पूर्ण

	/*
	 * Initialize FCoE session offload process.
	 * Upon completion of offload process add
	 * rport to list of rports
	 */
retry_ofld:
	clear_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	rval = bnx2fc_send_session_ofld_req(port, tgt);
	अगर (rval) अणु
		prपूर्णांकk(KERN_ERR PFX "ofld_req failed\n");
		जाओ ofld_err;
	पूर्ण

	/*
	 * रुको क्रम the session is offloaded and enabled. 3 Secs
	 * should be ample समय क्रम this process to complete.
	 */
	bnx2fc_ofld_रुको(tgt);

	अगर (!(test_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags))) अणु
		अगर (test_and_clear_bit(BNX2FC_FLAG_CTX_ALLOC_FAILURE,
				       &tgt->flags)) अणु
			BNX2FC_TGT_DBG(tgt, "ctx_alloc_failure, "
				"retry ofld..%d\n", i++);
			msleep_पूर्णांकerruptible(1000);
			अगर (i > 3) अणु
				i = 0;
				जाओ ofld_err;
			पूर्ण
			जाओ retry_ofld;
		पूर्ण
		जाओ ofld_err;
	पूर्ण
	अगर (bnx2fc_map_करोorbell(tgt)) अणु
		prपूर्णांकk(KERN_ERR PFX "map doorbell failed - no mem\n");
		जाओ ofld_err;
	पूर्ण
	clear_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	rval = bnx2fc_send_session_enable_req(port, tgt);
	अगर (rval) अणु
		pr_err(PFX "enable session failed\n");
		जाओ ofld_err;
	पूर्ण
	bnx2fc_ofld_रुको(tgt);
	अगर (!(test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags)))
		जाओ ofld_err;
	वापस;

ofld_err:
	/* couldn't offload the session. log off from this rport */
	BNX2FC_TGT_DBG(tgt, "bnx2fc_offload_session - offload error\n");
	clear_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
	/* Free session resources */
	bnx2fc_मुक्त_session_resc(hba, tgt);
tgt_init_err:
	अगर (tgt->fcoe_conn_id != -1)
		bnx2fc_मुक्त_conn_id(hba, tgt->fcoe_conn_id);
	fc_rport_logoff(rdata);
पूर्ण

व्योम bnx2fc_flush_active_ios(काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा bnx2fc_cmd *पंचांगp;
	पूर्णांक rc;
	पूर्णांक i = 0;
	BNX2FC_TGT_DBG(tgt, "Entered flush_active_ios - %d\n",
		       tgt->num_active_ios.counter);

	spin_lock_bh(&tgt->tgt_lock);
	tgt->flush_in_prog = 1;

	list_क्रम_each_entry_safe(io_req, पंचांगp, &tgt->active_cmd_queue, link) अणु
		i++;
		list_del_init(&io_req->link);
		io_req->on_active_queue = 0;
		BNX2FC_IO_DBG(io_req, "cmd_queue cleanup\n");

		अगर (cancel_delayed_work(&io_req->समयout_work)) अणु
			अगर (test_and_clear_bit(BNX2FC_FLAG_EH_ABORT,
						&io_req->req_flags)) अणु
				/* Handle eh_पात समयout */
				BNX2FC_IO_DBG(io_req, "eh_abort for IO "
					      "cleaned up\n");
				complete(&io_req->abts_करोne);
			पूर्ण
			kref_put(&io_req->refcount,
				 bnx2fc_cmd_release); /* drop समयr hold */
		पूर्ण

		set_bit(BNX2FC_FLAG_IO_COMPL, &io_req->req_flags);
		set_bit(BNX2FC_FLAG_IO_CLEANUP, &io_req->req_flags);

		/* Do not issue cleanup when disable request failed */
		अगर (test_bit(BNX2FC_FLAG_DISABLE_FAILED, &tgt->flags))
			bnx2fc_process_cleanup_compl(io_req, io_req->task, 0);
		अन्यथा अणु
			rc = bnx2fc_initiate_cleanup(io_req);
			BUG_ON(rc);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(io_req, पंचांगp, &tgt->active_पंचांग_queue, link) अणु
		i++;
		list_del_init(&io_req->link);
		io_req->on_पंचांगf_queue = 0;
		BNX2FC_IO_DBG(io_req, "tm_queue cleanup\n");
		अगर (io_req->रुको_क्रम_abts_comp)
			complete(&io_req->abts_करोne);
	पूर्ण

	list_क्रम_each_entry_safe(io_req, पंचांगp, &tgt->els_queue, link) अणु
		i++;
		list_del_init(&io_req->link);
		io_req->on_active_queue = 0;

		BNX2FC_IO_DBG(io_req, "els_queue cleanup\n");

		अगर (cancel_delayed_work(&io_req->समयout_work))
			kref_put(&io_req->refcount,
				 bnx2fc_cmd_release); /* drop समयr hold */

		अगर ((io_req->cb_func) && (io_req->cb_arg)) अणु
			io_req->cb_func(io_req->cb_arg);
			io_req->cb_arg = शून्य;
		पूर्ण

		/* Do not issue cleanup when disable request failed */
		अगर (test_bit(BNX2FC_FLAG_DISABLE_FAILED, &tgt->flags))
			bnx2fc_process_cleanup_compl(io_req, io_req->task, 0);
		अन्यथा अणु
			rc = bnx2fc_initiate_cleanup(io_req);
			BUG_ON(rc);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(io_req, पंचांगp, &tgt->io_retire_queue, link) अणु
		i++;
		list_del_init(&io_req->link);

		BNX2FC_IO_DBG(io_req, "retire_queue flush\n");

		अगर (cancel_delayed_work(&io_req->समयout_work)) अणु
			अगर (test_and_clear_bit(BNX2FC_FLAG_EH_ABORT,
						&io_req->req_flags)) अणु
				/* Handle eh_पात समयout */
				BNX2FC_IO_DBG(io_req, "eh_abort for IO "
					      "in retire_q\n");
				अगर (io_req->रुको_क्रम_abts_comp)
					complete(&io_req->abts_करोne);
			पूर्ण
			kref_put(&io_req->refcount, bnx2fc_cmd_release);
		पूर्ण

		clear_bit(BNX2FC_FLAG_ISSUE_RRQ, &io_req->req_flags);
	पूर्ण

	BNX2FC_TGT_DBG(tgt, "IOs flushed = %d\n", i);
	i = 0;
	spin_unlock_bh(&tgt->tgt_lock);
	/* रुको क्रम active_ios to go to 0 */
	जबतक ((tgt->num_active_ios.counter != 0) && (i++ < BNX2FC_WAIT_CNT))
		msleep(25);
	अगर (tgt->num_active_ios.counter != 0)
		prपूर्णांकk(KERN_ERR PFX "CLEANUP on port 0x%x:"
				    " active_ios = %d\n",
			tgt->rdata->ids.port_id, tgt->num_active_ios.counter);
	spin_lock_bh(&tgt->tgt_lock);
	tgt->flush_in_prog = 0;
	spin_unlock_bh(&tgt->tgt_lock);
पूर्ण

अटल व्योम bnx2fc_upld_रुको(काष्ठा bnx2fc_rport *tgt)
अणु
	समयr_setup(&tgt->upld_समयr, bnx2fc_upld_समयr, 0);
	mod_समयr(&tgt->upld_समयr, jअगरfies + BNX2FC_FW_TIMEOUT);
	रुको_event_पूर्णांकerruptible(tgt->upld_रुको,
				 (test_bit(
				  BNX2FC_FLAG_UPLD_REQ_COMPL,
				  &tgt->flags)));
	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&tgt->upld_समयr);
पूर्ण

अटल व्योम bnx2fc_upload_session(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;

	BNX2FC_TGT_DBG(tgt, "upload_session: active_ios = %d\n",
		tgt->num_active_ios.counter);

	/*
	 * Called with hba->hba_mutex held.
	 * This is a blocking call
	 */
	clear_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
	bnx2fc_send_session_disable_req(port, tgt);

	/*
	 * रुको क्रम upload to complete. 3 Secs
	 * should be sufficient समय क्रम this process to complete.
	 */
	BNX2FC_TGT_DBG(tgt, "waiting for disable compl\n");
	bnx2fc_upld_रुको(tgt);

	/*
	 * traverse thru the active_q and पंचांगf_q and cleanup
	 * IOs in these lists
	 */
	BNX2FC_TGT_DBG(tgt, "flush/upload - disable wait flags = 0x%lx\n",
		       tgt->flags);
	bnx2fc_flush_active_ios(tgt);

	/* Issue destroy KWQE */
	अगर (test_bit(BNX2FC_FLAG_DISABLED, &tgt->flags)) अणु
		BNX2FC_TGT_DBG(tgt, "send destroy req\n");
		clear_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
		bnx2fc_send_session_destroy_req(hba, tgt);

		/* रुको क्रम destroy to complete */
		bnx2fc_upld_रुको(tgt);

		अगर (!(test_bit(BNX2FC_FLAG_DESTROYED, &tgt->flags)))
			prपूर्णांकk(KERN_ERR PFX "ERROR!! destroy timed out\n");

		BNX2FC_TGT_DBG(tgt, "destroy wait complete flags = 0x%lx\n",
			tgt->flags);

	पूर्ण अन्यथा अगर (test_bit(BNX2FC_FLAG_DISABLE_FAILED, &tgt->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR!! DISABLE req failed, destroy"
				" not sent to FW\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR!! DISABLE req timed out, destroy"
				" not sent to FW\n");
	पूर्ण

	/* Free session resources */
	bnx2fc_मुक्त_session_resc(hba, tgt);
	bnx2fc_मुक्त_conn_id(hba, tgt->fcoe_conn_id);
पूर्ण

अटल पूर्णांक bnx2fc_init_tgt(काष्ठा bnx2fc_rport *tgt,
			   काष्ठा fcoe_port *port,
			   काष्ठा fc_rport_priv *rdata)
अणु

	काष्ठा fc_rport *rport = rdata->rport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा b577xx_करोorbell_set_prod *sq_db = &tgt->sq_db;
	काष्ठा b577xx_fcoe_rx_करोorbell *rx_db = &tgt->rx_db;

	tgt->rport = rport;
	tgt->rdata = rdata;
	tgt->port = port;

	अगर (hba->num_ofld_sess >= BNX2FC_NUM_MAX_SESS) अणु
		BNX2FC_TGT_DBG(tgt, "exceeded max sessions. logoff this tgt\n");
		tgt->fcoe_conn_id = -1;
		वापस -1;
	पूर्ण

	tgt->fcoe_conn_id = bnx2fc_alloc_conn_id(hba, tgt);
	अगर (tgt->fcoe_conn_id == -1)
		वापस -1;

	BNX2FC_TGT_DBG(tgt, "init_tgt - conn_id = 0x%x\n", tgt->fcoe_conn_id);

	tgt->max_sqes = BNX2FC_SQ_WQES_MAX;
	tgt->max_rqes = BNX2FC_RQ_WQES_MAX;
	tgt->max_cqes = BNX2FC_CQ_WQES_MAX;
	atomic_set(&tgt->मुक्त_sqes, BNX2FC_SQ_WQES_MAX);

	/* Initialize the toggle bit */
	tgt->sq_curr_toggle_bit = 1;
	tgt->cq_curr_toggle_bit = 1;
	tgt->sq_prod_idx = 0;
	tgt->cq_cons_idx = 0;
	tgt->rq_prod_idx = 0x8000;
	tgt->rq_cons_idx = 0;
	atomic_set(&tgt->num_active_ios, 0);
	tgt->retry_delay_बारtamp = 0;

	अगर (rdata->flags & FC_RP_FLAGS_RETRY &&
	    rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET &&
	    !(rdata->ids.roles & FC_RPORT_ROLE_FCP_INITIATOR)) अणु
		tgt->dev_type = TYPE_TAPE;
		tgt->io_समयout = 0; /* use शेष ULP समयout */
	पूर्ण अन्यथा अणु
		tgt->dev_type = TYPE_DISK;
		tgt->io_समयout = BNX2FC_IO_TIMEOUT;
	पूर्ण

	/* initialize sq करोorbell */
	sq_db->header.header = B577XX_DOORBELL_HDR_DB_TYPE;
	sq_db->header.header |= B577XX_FCOE_CONNECTION_TYPE <<
					B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT;
	/* initialize rx करोorbell */
	rx_db->hdr.header = ((0x1 << B577XX_DOORBELL_HDR_RX_SHIFT) |
			  (0x1 << B577XX_DOORBELL_HDR_DB_TYPE_SHIFT) |
			  (B577XX_FCOE_CONNECTION_TYPE <<
				B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT));
	rx_db->params = (0x2 << B577XX_FCOE_RX_DOORBELL_NEGATIVE_ARM_SHIFT) |
		     (0x3 << B577XX_FCOE_RX_DOORBELL_OPCODE_SHIFT);

	spin_lock_init(&tgt->tgt_lock);
	spin_lock_init(&tgt->cq_lock);

	/* Initialize active_cmd_queue list */
	INIT_LIST_HEAD(&tgt->active_cmd_queue);

	/* Initialize IO retire queue */
	INIT_LIST_HEAD(&tgt->io_retire_queue);

	INIT_LIST_HEAD(&tgt->els_queue);

	/* Initialize active_पंचांग_queue list */
	INIT_LIST_HEAD(&tgt->active_पंचांग_queue);

	init_रुकोqueue_head(&tgt->ofld_रुको);
	init_रुकोqueue_head(&tgt->upld_रुको);

	वापस 0;
पूर्ण

/*
 * This event_callback is called after successful completion of libfc
 * initiated target login. bnx2fc can proceed with initiating the session
 * establishment.
 */
व्योम bnx2fc_rport_event_handler(काष्ठा fc_lport *lport,
				काष्ठा fc_rport_priv *rdata,
				क्रमागत fc_rport_event event)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा fc_rport *rport = rdata->rport;
	काष्ठा fc_rport_libfc_priv *rp;
	काष्ठा bnx2fc_rport *tgt;
	u32 port_id;

	BNX2FC_HBA_DBG(lport, "rport_event_hdlr: event = %d, port_id = 0x%x\n",
		event, rdata->ids.port_id);
	चयन (event) अणु
	हाल RPORT_EV_READY:
		अगर (!rport) अणु
			prपूर्णांकk(KERN_ERR PFX "rport is NULL: ERROR!\n");
			अवरोध;
		पूर्ण

		rp = rport->dd_data;
		अगर (rport->port_id == FC_FID_सूची_SERV) अणु
			/*
			 * bnx2fc_rport काष्ठाure करोesn't exist क्रम
			 * directory server.
			 * We should not come here, as lport will
			 * take care of fabric login
			 */
			prपूर्णांकk(KERN_ERR PFX "%x - rport_event_handler ERROR\n",
				rdata->ids.port_id);
			अवरोध;
		पूर्ण

		अगर (rdata->spp_type != FC_TYPE_FCP) अणु
			BNX2FC_HBA_DBG(lport, "not FCP type target."
				   " not offloading\n");
			अवरोध;
		पूर्ण
		अगर (!(rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET)) अणु
			BNX2FC_HBA_DBG(lport, "not FCP_TARGET"
				   " not offloading\n");
			अवरोध;
		पूर्ण

		/*
		 * Offlaod process is रक्षित with hba mutex.
		 * Use the same mutex_lock क्रम upload process too
		 */
		mutex_lock(&hba->hba_mutex);
		tgt = (काष्ठा bnx2fc_rport *)&rp[1];

		/* This can happen when ADISC finds the same target */
		अगर (test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags)) अणु
			BNX2FC_TGT_DBG(tgt, "already offloaded\n");
			mutex_unlock(&hba->hba_mutex);
			वापस;
		पूर्ण

		/*
		 * Offload the session. This is a blocking call, and will
		 * रुको until the session is offloaded.
		 */
		bnx2fc_offload_session(port, tgt, rdata);

		BNX2FC_TGT_DBG(tgt, "OFFLOAD num_ofld_sess = %d\n",
			hba->num_ofld_sess);

		अगर (test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags)) अणु
			/* Session is offloaded and enabled.  */
			BNX2FC_TGT_DBG(tgt, "sess offloaded\n");
			/* This counter is रक्षित with hba mutex */
			hba->num_ofld_sess++;

			set_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags);
		पूर्ण अन्यथा अणु
			/*
			 * Offload or enable would have failed.
			 * In offload/enable completion path, the
			 * rport would have alपढ़ोy been हटाओd
			 */
			BNX2FC_TGT_DBG(tgt, "Port is being logged off as "
				   "offloaded flag not set\n");
		पूर्ण
		mutex_unlock(&hba->hba_mutex);
		अवरोध;
	हाल RPORT_EV_LOGO:
	हाल RPORT_EV_FAILED:
	हाल RPORT_EV_STOP:
		port_id = rdata->ids.port_id;
		अगर (port_id == FC_FID_सूची_SERV)
			अवरोध;

		अगर (!rport) अणु
			prपूर्णांकk(KERN_INFO PFX "%x - rport not created Yet!!\n",
				port_id);
			अवरोध;
		पूर्ण
		rp = rport->dd_data;
		mutex_lock(&hba->hba_mutex);
		/*
		 * Perक्रमm session upload. Note that rdata->peers is alपढ़ोy
		 * हटाओd from disc->rports list beक्रमe we get this event.
		 */
		tgt = (काष्ठा bnx2fc_rport *)&rp[1];

		अगर (!(test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags))) अणु
			mutex_unlock(&hba->hba_mutex);
			अवरोध;
		पूर्ण
		clear_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags);

		bnx2fc_upload_session(port, tgt);
		hba->num_ofld_sess--;
		BNX2FC_TGT_DBG(tgt, "UPLOAD num_ofld_sess = %d\n",
			hba->num_ofld_sess);
		/*
		 * Try to wake up the linkकरोwn रुको thपढ़ो. If num_ofld_sess
		 * is 0, the रुकोing therad wakes up
		 */
		अगर ((hba->रुको_क्रम_link_करोwn) &&
		    (hba->num_ofld_sess == 0)) अणु
			wake_up_पूर्णांकerruptible(&hba->shutकरोwn_रुको);
		पूर्ण
		mutex_unlock(&hba->hba_mutex);

		अवरोध;

	हाल RPORT_EV_NONE:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * bnx2fc_tgt_lookup() - Lookup a bnx2fc_rport by port_id
 *
 * @port:  fcoe_port काष्ठा to lookup the target port on
 * @port_id: The remote port ID to look up
 */
काष्ठा bnx2fc_rport *bnx2fc_tgt_lookup(काष्ठा fcoe_port *port,
					     u32 port_id)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा fc_rport_priv *rdata;
	पूर्णांक i;

	क्रम (i = 0; i < BNX2FC_NUM_MAX_SESS; i++) अणु
		tgt = hba->tgt_ofld_list[i];
		अगर ((tgt) && (tgt->port == port)) अणु
			rdata = tgt->rdata;
			अगर (rdata->ids.port_id == port_id) अणु
				अगर (rdata->rp_state != RPORT_ST_DELETE) अणु
					BNX2FC_TGT_DBG(tgt, "rport "
						"obtained\n");
					वापस tgt;
				पूर्ण अन्यथा अणु
					BNX2FC_TGT_DBG(tgt, "rport 0x%x "
						"is in DELETED state\n",
						rdata->ids.port_id);
					वापस शून्य;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण


/**
 * bnx2fc_alloc_conn_id - allocates FCOE Connection id
 *
 * @hba:	poपूर्णांकer to adapter काष्ठाure
 * @tgt:	poपूर्णांकer to bnx2fc_rport काष्ठाure
 */
अटल u32 bnx2fc_alloc_conn_id(काष्ठा bnx2fc_hba *hba,
				काष्ठा bnx2fc_rport *tgt)
अणु
	u32 conn_id, next;

	/* called with hba mutex held */

	/*
	 * tgt_ofld_list access is synchronized using
	 * both hba mutex and hba lock. Atleast hba mutex or
	 * hba lock needs to be held क्रम पढ़ो access.
	 */

	spin_lock_bh(&hba->hba_lock);
	next = hba->next_conn_id;
	conn_id = hba->next_conn_id++;
	अगर (hba->next_conn_id == BNX2FC_NUM_MAX_SESS)
		hba->next_conn_id = 0;

	जबतक (hba->tgt_ofld_list[conn_id] != शून्य) अणु
		conn_id++;
		अगर (conn_id == BNX2FC_NUM_MAX_SESS)
			conn_id = 0;

		अगर (conn_id == next) अणु
			/* No मुक्त conn_ids are available */
			spin_unlock_bh(&hba->hba_lock);
			वापस -1;
		पूर्ण
	पूर्ण
	hba->tgt_ofld_list[conn_id] = tgt;
	tgt->fcoe_conn_id = conn_id;
	spin_unlock_bh(&hba->hba_lock);
	वापस conn_id;
पूर्ण

अटल व्योम bnx2fc_मुक्त_conn_id(काष्ठा bnx2fc_hba *hba, u32 conn_id)
अणु
	/* called with hba mutex held */
	spin_lock_bh(&hba->hba_lock);
	hba->tgt_ofld_list[conn_id] = शून्य;
	spin_unlock_bh(&hba->hba_lock);
पूर्ण

/*
 * bnx2fc_alloc_session_resc - Allocate qp resources क्रम the session
 */
अटल पूर्णांक bnx2fc_alloc_session_resc(काष्ठा bnx2fc_hba *hba,
					काष्ठा bnx2fc_rport *tgt)
अणु
	dma_addr_t page;
	पूर्णांक num_pages;
	u32 *pbl;

	/* Allocate and map SQ */
	tgt->sq_mem_size = tgt->max_sqes * BNX2FC_SQ_WQE_SIZE;
	tgt->sq_mem_size = (tgt->sq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			   CNIC_PAGE_MASK;

	tgt->sq = dma_alloc_coherent(&hba->pcidev->dev, tgt->sq_mem_size,
				     &tgt->sq_dma, GFP_KERNEL);
	अगर (!tgt->sq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate SQ memory %d\n",
			tgt->sq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	/* Allocate and map CQ */
	tgt->cq_mem_size = tgt->max_cqes * BNX2FC_CQ_WQE_SIZE;
	tgt->cq_mem_size = (tgt->cq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			   CNIC_PAGE_MASK;

	tgt->cq = dma_alloc_coherent(&hba->pcidev->dev, tgt->cq_mem_size,
				     &tgt->cq_dma, GFP_KERNEL);
	अगर (!tgt->cq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate CQ memory %d\n",
			tgt->cq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	/* Allocate and map RQ and RQ PBL */
	tgt->rq_mem_size = tgt->max_rqes * BNX2FC_RQ_WQE_SIZE;
	tgt->rq_mem_size = (tgt->rq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			   CNIC_PAGE_MASK;

	tgt->rq = dma_alloc_coherent(&hba->pcidev->dev, tgt->rq_mem_size,
				     &tgt->rq_dma, GFP_KERNEL);
	अगर (!tgt->rq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate RQ memory %d\n",
			tgt->rq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	tgt->rq_pbl_size = (tgt->rq_mem_size / CNIC_PAGE_SIZE) * माप(व्योम *);
	tgt->rq_pbl_size = (tgt->rq_pbl_size + (CNIC_PAGE_SIZE - 1)) &
			   CNIC_PAGE_MASK;

	tgt->rq_pbl = dma_alloc_coherent(&hba->pcidev->dev, tgt->rq_pbl_size,
					 &tgt->rq_pbl_dma, GFP_KERNEL);
	अगर (!tgt->rq_pbl) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate RQ PBL %d\n",
			tgt->rq_pbl_size);
		जाओ mem_alloc_failure;
	पूर्ण

	num_pages = tgt->rq_mem_size / CNIC_PAGE_SIZE;
	page = tgt->rq_dma;
	pbl = (u32 *)tgt->rq_pbl;

	जबतक (num_pages--) अणु
		*pbl = (u32)page;
		pbl++;
		*pbl = (u32)((u64)page >> 32);
		pbl++;
		page += CNIC_PAGE_SIZE;
	पूर्ण

	/* Allocate and map XFERQ */
	tgt->xferq_mem_size = tgt->max_sqes * BNX2FC_XFERQ_WQE_SIZE;
	tgt->xferq_mem_size = (tgt->xferq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			       CNIC_PAGE_MASK;

	tgt->xferq = dma_alloc_coherent(&hba->pcidev->dev,
					tgt->xferq_mem_size, &tgt->xferq_dma,
					GFP_KERNEL);
	अगर (!tgt->xferq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate XFERQ %d\n",
			tgt->xferq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	/* Allocate and map CONFQ & CONFQ PBL */
	tgt->confq_mem_size = tgt->max_sqes * BNX2FC_CONFQ_WQE_SIZE;
	tgt->confq_mem_size = (tgt->confq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			       CNIC_PAGE_MASK;

	tgt->confq = dma_alloc_coherent(&hba->pcidev->dev,
					tgt->confq_mem_size, &tgt->confq_dma,
					GFP_KERNEL);
	अगर (!tgt->confq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate CONFQ %d\n",
			tgt->confq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	tgt->confq_pbl_size =
		(tgt->confq_mem_size / CNIC_PAGE_SIZE) * माप(व्योम *);
	tgt->confq_pbl_size =
		(tgt->confq_pbl_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	tgt->confq_pbl = dma_alloc_coherent(&hba->pcidev->dev,
					    tgt->confq_pbl_size,
					    &tgt->confq_pbl_dma, GFP_KERNEL);
	अगर (!tgt->confq_pbl) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate CONFQ PBL %d\n",
			tgt->confq_pbl_size);
		जाओ mem_alloc_failure;
	पूर्ण

	num_pages = tgt->confq_mem_size / CNIC_PAGE_SIZE;
	page = tgt->confq_dma;
	pbl = (u32 *)tgt->confq_pbl;

	जबतक (num_pages--) अणु
		*pbl = (u32)page;
		pbl++;
		*pbl = (u32)((u64)page >> 32);
		pbl++;
		page += CNIC_PAGE_SIZE;
	पूर्ण

	/* Allocate and map ConnDB */
	tgt->conn_db_mem_size = माप(काष्ठा fcoe_conn_db);

	tgt->conn_db = dma_alloc_coherent(&hba->pcidev->dev,
					  tgt->conn_db_mem_size,
					  &tgt->conn_db_dma, GFP_KERNEL);
	अगर (!tgt->conn_db) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate conn_db %d\n",
						tgt->conn_db_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण


	/* Allocate and map LCQ */
	tgt->lcq_mem_size = (tgt->max_sqes + 8) * BNX2FC_SQ_WQE_SIZE;
	tgt->lcq_mem_size = (tgt->lcq_mem_size + (CNIC_PAGE_SIZE - 1)) &
			     CNIC_PAGE_MASK;

	tgt->lcq = dma_alloc_coherent(&hba->pcidev->dev, tgt->lcq_mem_size,
				      &tgt->lcq_dma, GFP_KERNEL);

	अगर (!tgt->lcq) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate lcq %d\n",
		       tgt->lcq_mem_size);
		जाओ mem_alloc_failure;
	पूर्ण

	tgt->conn_db->rq_prod = 0x8000;

	वापस 0;

mem_alloc_failure:
	वापस -ENOMEM;
पूर्ण

/**
 * bnx2fc_मुक्त_session_resc - मुक्त qp resources क्रम the session
 *
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @tgt:	bnx2fc_rport काष्ठाure poपूर्णांकer
 *
 * Free QP resources - SQ/RQ/CQ/XFERQ memory and PBL
 */
अटल व्योम bnx2fc_मुक्त_session_resc(काष्ठा bnx2fc_hba *hba,
						काष्ठा bnx2fc_rport *tgt)
अणु
	व्योम __iomem *ctx_base_ptr;

	BNX2FC_TGT_DBG(tgt, "Freeing up session resources\n");

	spin_lock_bh(&tgt->cq_lock);
	ctx_base_ptr = tgt->ctx_base;
	tgt->ctx_base = शून्य;

	/* Free LCQ */
	अगर (tgt->lcq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->lcq_mem_size,
				    tgt->lcq, tgt->lcq_dma);
		tgt->lcq = शून्य;
	पूर्ण
	/* Free connDB */
	अगर (tgt->conn_db) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->conn_db_mem_size,
				    tgt->conn_db, tgt->conn_db_dma);
		tgt->conn_db = शून्य;
	पूर्ण
	/* Free confq  and confq pbl */
	अगर (tgt->confq_pbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->confq_pbl_size,
				    tgt->confq_pbl, tgt->confq_pbl_dma);
		tgt->confq_pbl = शून्य;
	पूर्ण
	अगर (tgt->confq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->confq_mem_size,
				    tgt->confq, tgt->confq_dma);
		tgt->confq = शून्य;
	पूर्ण
	/* Free XFERQ */
	अगर (tgt->xferq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->xferq_mem_size,
				    tgt->xferq, tgt->xferq_dma);
		tgt->xferq = शून्य;
	पूर्ण
	/* Free RQ PBL and RQ */
	अगर (tgt->rq_pbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->rq_pbl_size,
				    tgt->rq_pbl, tgt->rq_pbl_dma);
		tgt->rq_pbl = शून्य;
	पूर्ण
	अगर (tgt->rq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->rq_mem_size,
				    tgt->rq, tgt->rq_dma);
		tgt->rq = शून्य;
	पूर्ण
	/* Free CQ */
	अगर (tgt->cq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->cq_mem_size,
				    tgt->cq, tgt->cq_dma);
		tgt->cq = शून्य;
	पूर्ण
	/* Free SQ */
	अगर (tgt->sq) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, tgt->sq_mem_size,
				    tgt->sq, tgt->sq_dma);
		tgt->sq = शून्य;
	पूर्ण
	spin_unlock_bh(&tgt->cq_lock);

	अगर (ctx_base_ptr)
		iounmap(ctx_base_ptr);
पूर्ण
