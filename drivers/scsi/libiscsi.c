<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * iSCSI lib functions
 *
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2004 - 2006 Mike Christie
 * Copyright (C) 2004 - 2005 Dmitry Yusupov
 * Copyright (C) 2004 - 2005 Alex Aizman
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 */
#समावेश <linux/types.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/libiscsi.h>
#समावेश <trace/events/iscsi.h>

अटल पूर्णांक iscsi_dbg_lib_conn;
module_param_named(debug_libiscsi_conn, iscsi_dbg_lib_conn, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_libiscsi_conn,
		 "Turn on debugging for connections in libiscsi module. "
		 "Set to 1 to turn on, and zero to turn off. Default is off.");

अटल पूर्णांक iscsi_dbg_lib_session;
module_param_named(debug_libiscsi_session, iscsi_dbg_lib_session, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_libiscsi_session,
		 "Turn on debugging for sessions in libiscsi module. "
		 "Set to 1 to turn on, and zero to turn off. Default is off.");

अटल पूर्णांक iscsi_dbg_lib_eh;
module_param_named(debug_libiscsi_eh, iscsi_dbg_lib_eh, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_libiscsi_eh,
		 "Turn on debugging for error handling in libiscsi module. "
		 "Set to 1 to turn on, and zero to turn off. Default is off.");

#घोषणा ISCSI_DBG_CONN(_conn, dbg_fmt, arg...)			\
	करो अणु							\
		अगर (iscsi_dbg_lib_conn)				\
			iscsi_conn_prपूर्णांकk(KERN_INFO, _conn,	\
					     "%s " dbg_fmt,	\
					     __func__, ##arg);	\
		iscsi_dbg_trace(trace_iscsi_dbg_conn,		\
				&(_conn)->cls_conn->dev,	\
				"%s " dbg_fmt, __func__, ##arg);\
	पूर्ण जबतक (0);

#घोषणा ISCSI_DBG_SESSION(_session, dbg_fmt, arg...)			\
	करो अणु								\
		अगर (iscsi_dbg_lib_session)				\
			iscsi_session_prपूर्णांकk(KERN_INFO, _session,	\
					     "%s " dbg_fmt,		\
					     __func__, ##arg);		\
		iscsi_dbg_trace(trace_iscsi_dbg_session, 		\
				&(_session)->cls_session->dev,		\
				"%s " dbg_fmt, __func__, ##arg);	\
	पूर्ण जबतक (0);

#घोषणा ISCSI_DBG_EH(_session, dbg_fmt, arg...)				\
	करो अणु								\
		अगर (iscsi_dbg_lib_eh)					\
			iscsi_session_prपूर्णांकk(KERN_INFO, _session,	\
					     "%s " dbg_fmt,		\
					     __func__, ##arg);		\
		iscsi_dbg_trace(trace_iscsi_dbg_eh,			\
				&(_session)->cls_session->dev,		\
				"%s " dbg_fmt, __func__, ##arg);	\
	पूर्ण जबतक (0);

अंतरभूत व्योम iscsi_conn_queue_work(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा Scsi_Host *shost = conn->session->host;
	काष्ठा iscsi_host *ihost = shost_priv(shost);

	अगर (ihost->workq)
		queue_work(ihost->workq, &conn->xmitwork);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_queue_work);

अटल व्योम __iscsi_update_cmdsn(काष्ठा iscsi_session *session,
				 uपूर्णांक32_t exp_cmdsn, uपूर्णांक32_t max_cmdsn)
अणु
	/*
	 * standard specअगरies this check क्रम when to update expected and
	 * max sequence numbers
	 */
	अगर (iscsi_sna_lt(max_cmdsn, exp_cmdsn - 1))
		वापस;

	अगर (exp_cmdsn != session->exp_cmdsn &&
	    !iscsi_sna_lt(exp_cmdsn, session->exp_cmdsn))
		session->exp_cmdsn = exp_cmdsn;

	अगर (max_cmdsn != session->max_cmdsn &&
	    !iscsi_sna_lt(max_cmdsn, session->max_cmdsn))
		session->max_cmdsn = max_cmdsn;
पूर्ण

व्योम iscsi_update_cmdsn(काष्ठा iscsi_session *session, काष्ठा iscsi_nopin *hdr)
अणु
	__iscsi_update_cmdsn(session, be32_to_cpu(hdr->exp_cmdsn),
			     be32_to_cpu(hdr->max_cmdsn));
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_update_cmdsn);

/**
 * iscsi_prep_data_out_pdu - initialize Data-Out
 * @task: scsi command task
 * @r2t: R2T info
 * @hdr: iscsi data in pdu
 *
 * Notes:
 *	Initialize Data-Out within this R2T sequence and finds
 *	proper data_offset within this SCSI command.
 *
 *	This function is called with connection lock taken.
 **/
व्योम iscsi_prep_data_out_pdu(काष्ठा iscsi_task *task, काष्ठा iscsi_r2t_info *r2t,
			   काष्ठा iscsi_data *hdr)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	अचिन्हित पूर्णांक left = r2t->data_length - r2t->sent;

	task->hdr_len = माप(काष्ठा iscsi_data);

	स_रखो(hdr, 0, माप(काष्ठा iscsi_data));
	hdr->ttt = r2t->ttt;
	hdr->datasn = cpu_to_be32(r2t->datasn);
	r2t->datasn++;
	hdr->opcode = ISCSI_OP_SCSI_DATA_OUT;
	hdr->lun = task->lun;
	hdr->itt = task->hdr_itt;
	hdr->exp_statsn = r2t->exp_statsn;
	hdr->offset = cpu_to_be32(r2t->data_offset + r2t->sent);
	अगर (left > conn->max_xmit_dlength) अणु
		hton24(hdr->dlength, conn->max_xmit_dlength);
		r2t->data_count = conn->max_xmit_dlength;
		hdr->flags = 0;
	पूर्ण अन्यथा अणु
		hton24(hdr->dlength, left);
		r2t->data_count = left;
		hdr->flags = ISCSI_FLAG_CMD_FINAL;
	पूर्ण
	conn->dataout_pdus_cnt++;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_prep_data_out_pdu);

अटल पूर्णांक iscsi_add_hdr(काष्ठा iscsi_task *task, अचिन्हित len)
अणु
	अचिन्हित exp_len = task->hdr_len + len;

	अगर (exp_len > task->hdr_max) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(len & (ISCSI_PAD_LEN - 1)); /* caller must pad the AHS */
	task->hdr_len = exp_len;
	वापस 0;
पूर्ण

/*
 * make an extended cdb AHS
 */
अटल पूर्णांक iscsi_prep_ecdb_ahs(काष्ठा iscsi_task *task)
अणु
	काष्ठा scsi_cmnd *cmd = task->sc;
	अचिन्हित rlen, pad_len;
	अचिन्हित लघु ahslength;
	काष्ठा iscsi_ecdb_ahdr *ecdb_ahdr;
	पूर्णांक rc;

	ecdb_ahdr = iscsi_next_hdr(task);
	rlen = cmd->cmd_len - ISCSI_CDB_SIZE;

	BUG_ON(rlen > माप(ecdb_ahdr->ecdb));
	ahslength = rlen + माप(ecdb_ahdr->reserved);

	pad_len = iscsi_padding(rlen);

	rc = iscsi_add_hdr(task, माप(ecdb_ahdr->ahslength) +
	                   माप(ecdb_ahdr->ahstype) + ahslength + pad_len);
	अगर (rc)
		वापस rc;

	अगर (pad_len)
		स_रखो(&ecdb_ahdr->ecdb[rlen], 0, pad_len);

	ecdb_ahdr->ahslength = cpu_to_be16(ahslength);
	ecdb_ahdr->ahstype = ISCSI_AHSTYPE_CDB;
	ecdb_ahdr->reserved = 0;
	स_नकल(ecdb_ahdr->ecdb, cmd->cmnd + ISCSI_CDB_SIZE, rlen);

	ISCSI_DBG_SESSION(task->conn->session,
			  "iscsi_prep_ecdb_ahs: varlen_cdb_len %d "
		          "rlen %d pad_len %d ahs_length %d iscsi_headers_size "
		          "%u\n", cmd->cmd_len, rlen, pad_len, ahslength,
		          task->hdr_len);
	वापस 0;
पूर्ण

/**
 * iscsi_check_पंचांगf_restrictions - check अगर a task is affected by TMF
 * @task: iscsi task
 * @opcode: opcode to check क्रम
 *
 * During TMF a task has to be checked अगर it's affected.
 * All unrelated I/O can be passed through, but I/O to the
 * affected LUN should be restricted.
 * If 'fast_abort' is set we won't be sending any I/O to the
 * affected LUN.
 * Otherwise the target is रुकोing क्रम all TTTs to be completed,
 * so we have to send all outstanding Data-Out PDUs to the target.
 */
अटल पूर्णांक iscsi_check_पंचांगf_restrictions(काष्ठा iscsi_task *task, पूर्णांक opcode)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_पंचांग *पंचांगf = &conn->पंचांगhdr;
	u64 hdr_lun;

	अगर (conn->पंचांगf_state == TMF_INITIAL)
		वापस 0;

	अगर ((पंचांगf->opcode & ISCSI_OPCODE_MASK) != ISCSI_OP_SCSI_TMFUNC)
		वापस 0;

	चयन (ISCSI_TM_FUNC_VALUE(पंचांगf)) अणु
	हाल ISCSI_TM_FUNC_LOGICAL_UNIT_RESET:
		/*
		 * Allow PDUs क्रम unrelated LUNs
		 */
		hdr_lun = scsilun_to_पूर्णांक(&पंचांगf->lun);
		अगर (hdr_lun != task->sc->device->lun)
			वापस 0;
		fallthrough;
	हाल ISCSI_TM_FUNC_TARGET_WARM_RESET:
		/*
		 * Fail all SCSI cmd PDUs
		 */
		अगर (opcode != ISCSI_OP_SCSI_DATA_OUT) अणु
			iscsi_conn_prपूर्णांकk(KERN_INFO, conn,
					  "task [op %x itt "
					  "0x%x/0x%x] "
					  "rejected.\n",
					  opcode, task->itt,
					  task->hdr_itt);
			वापस -EACCES;
		पूर्ण
		/*
		 * And also all data-out PDUs in response to R2T
		 * अगर fast_पात is set.
		 */
		अगर (conn->session->fast_पात) अणु
			iscsi_conn_prपूर्णांकk(KERN_INFO, conn,
					  "task [op %x itt "
					  "0x%x/0x%x] fast abort.\n",
					  opcode, task->itt,
					  task->hdr_itt);
			वापस -EACCES;
		पूर्ण
		अवरोध;
	हाल ISCSI_TM_FUNC_ABORT_TASK:
		/*
		 * the caller has alपढ़ोy checked अगर the task
		 * they want to पात was in the pending queue so अगर
		 * we are here the cmd pdu has gone out alपढ़ोy, and
		 * we will only hit this क्रम data-outs
		 */
		अगर (opcode == ISCSI_OP_SCSI_DATA_OUT &&
		    task->hdr_itt == पंचांगf->rtt) अणु
			ISCSI_DBG_SESSION(conn->session,
					  "Preventing task %x/%x from sending "
					  "data-out due to abort task in "
					  "progress\n", task->itt,
					  task->hdr_itt);
			वापस -EACCES;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iscsi_prep_scsi_cmd_pdu - prep iscsi scsi cmd pdu
 * @task: iscsi task
 *
 * Prep basic iSCSI PDU fields क्रम a scsi cmd pdu. The LLD should set
 * fields like dlength or final based on how much data it sends
 */
अटल पूर्णांक iscsi_prep_scsi_cmd_pdu(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा iscsi_scsi_req *hdr;
	अचिन्हित hdrlength, cmd_len, transfer_length;
	itt_t itt;
	पूर्णांक rc;

	rc = iscsi_check_पंचांगf_restrictions(task, ISCSI_OP_SCSI_CMD);
	अगर (rc)
		वापस rc;

	अगर (conn->session->tt->alloc_pdu) अणु
		rc = conn->session->tt->alloc_pdu(task, ISCSI_OP_SCSI_CMD);
		अगर (rc)
			वापस rc;
	पूर्ण
	hdr = (काष्ठा iscsi_scsi_req *)task->hdr;
	itt = hdr->itt;
	स_रखो(hdr, 0, माप(*hdr));

	अगर (session->tt->parse_pdu_itt)
		hdr->itt = task->hdr_itt = itt;
	अन्यथा
		hdr->itt = task->hdr_itt = build_itt(task->itt,
						     task->conn->session->age);
	task->hdr_len = 0;
	rc = iscsi_add_hdr(task, माप(*hdr));
	अगर (rc)
		वापस rc;
	hdr->opcode = ISCSI_OP_SCSI_CMD;
	hdr->flags = ISCSI_ATTR_SIMPLE;
	पूर्णांक_to_scsilun(sc->device->lun, &hdr->lun);
	task->lun = hdr->lun;
	hdr->exp_statsn = cpu_to_be32(conn->exp_statsn);
	cmd_len = sc->cmd_len;
	अगर (cmd_len < ISCSI_CDB_SIZE)
		स_रखो(&hdr->cdb[cmd_len], 0, ISCSI_CDB_SIZE - cmd_len);
	अन्यथा अगर (cmd_len > ISCSI_CDB_SIZE) अणु
		rc = iscsi_prep_ecdb_ahs(task);
		अगर (rc)
			वापस rc;
		cmd_len = ISCSI_CDB_SIZE;
	पूर्ण
	स_नकल(hdr->cdb, sc->cmnd, cmd_len);

	task->imm_count = 0;
	अगर (scsi_get_prot_op(sc) != SCSI_PROT_NORMAL)
		task->रक्षित = true;

	transfer_length = scsi_transfer_length(sc);
	hdr->data_length = cpu_to_be32(transfer_length);
	अगर (sc->sc_data_direction == DMA_TO_DEVICE) अणु
		काष्ठा iscsi_r2t_info *r2t = &task->unsol_r2t;

		hdr->flags |= ISCSI_FLAG_CMD_WRITE;
		/*
		 * Write counters:
		 *
		 *	imm_count	bytes to be sent right after
		 *			SCSI PDU Header
		 *
		 *	unsol_count	bytes(as Data-Out) to be sent
		 *			without	R2T ack right after
		 *			immediate data
		 *
		 *	r2t data_length bytes to be sent via R2T ack's
		 *
		 *      pad_count       bytes to be sent as zero-padding
		 */
		स_रखो(r2t, 0, माप(*r2t));

		अगर (session->imm_data_en) अणु
			अगर (transfer_length >= session->first_burst)
				task->imm_count = min(session->first_burst,
							conn->max_xmit_dlength);
			अन्यथा
				task->imm_count = min(transfer_length,
						      conn->max_xmit_dlength);
			hton24(hdr->dlength, task->imm_count);
		पूर्ण अन्यथा
			zero_data(hdr->dlength);

		अगर (!session->initial_r2t_en) अणु
			r2t->data_length = min(session->first_burst,
					       transfer_length) -
					       task->imm_count;
			r2t->data_offset = task->imm_count;
			r2t->ttt = cpu_to_be32(ISCSI_RESERVED_TAG);
			r2t->exp_statsn = cpu_to_be32(conn->exp_statsn);
		पूर्ण

		अगर (!task->unsol_r2t.data_length)
			/* No unsolicit Data-Out's */
			hdr->flags |= ISCSI_FLAG_CMD_FINAL;
	पूर्ण अन्यथा अणु
		hdr->flags |= ISCSI_FLAG_CMD_FINAL;
		zero_data(hdr->dlength);

		अगर (sc->sc_data_direction == DMA_FROM_DEVICE)
			hdr->flags |= ISCSI_FLAG_CMD_READ;
	पूर्ण

	/* calculate size of additional header segments (AHSs) */
	hdrlength = task->hdr_len - माप(*hdr);

	WARN_ON(hdrlength & (ISCSI_PAD_LEN-1));
	hdrlength /= ISCSI_PAD_LEN;

	WARN_ON(hdrlength >= 256);
	hdr->hlength = hdrlength & 0xFF;
	hdr->cmdsn = task->cmdsn = cpu_to_be32(session->cmdsn);

	अगर (session->tt->init_task && session->tt->init_task(task))
		वापस -EIO;

	task->state = ISCSI_TASK_RUNNING;
	session->cmdsn++;

	conn->scsicmd_pdus_cnt++;
	ISCSI_DBG_SESSION(session, "iscsi prep [%s cid %d sc %p cdb 0x%x "
			  "itt 0x%x len %d cmdsn %d win %d]\n",
			  sc->sc_data_direction == DMA_TO_DEVICE ?
			  "write" : "read", conn->id, sc, sc->cmnd[0],
			  task->itt, transfer_length,
			  session->cmdsn,
			  session->max_cmdsn - session->exp_cmdsn + 1);
	वापस 0;
पूर्ण

/**
 * iscsi_मुक्त_task - मुक्त a task
 * @task: iscsi cmd task
 *
 * Must be called with session back_lock.
 * This function वापसs the scsi command to scsi-ml or cleans
 * up mgmt tasks then वापसs the task to the pool.
 */
अटल व्योम iscsi_मुक्त_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा scsi_cmnd *sc = task->sc;
	पूर्णांक oldstate = task->state;

	ISCSI_DBG_SESSION(session, "freeing task itt 0x%x state %d sc %p\n",
			  task->itt, task->state, task->sc);

	session->tt->cleanup_task(task);
	task->state = ISCSI_TASK_FREE;
	task->sc = शून्य;
	/*
	 * login task is pपुनः_स्मृतिated so करो not मुक्त
	 */
	अगर (conn->login_task == task)
		वापस;

	kfअगरo_in(&session->cmdpool.queue, (व्योम*)&task, माप(व्योम*));

	अगर (sc) अणु
		/* SCSI eh reuses commands to verअगरy us */
		sc->SCp.ptr = शून्य;
		/*
		 * queue command may call this to मुक्त the task, so
		 * it will decide how to वापस sc to scsi-ml.
		 */
		अगर (oldstate != ISCSI_TASK_REQUEUE_SCSIQ)
			sc->scsi_करोne(sc);
	पूर्ण
पूर्ण

व्योम __iscsi_get_task(काष्ठा iscsi_task *task)
अणु
	refcount_inc(&task->refcount);
पूर्ण
EXPORT_SYMBOL_GPL(__iscsi_get_task);

व्योम __iscsi_put_task(काष्ठा iscsi_task *task)
अणु
	अगर (refcount_dec_and_test(&task->refcount))
		iscsi_मुक्त_task(task);
पूर्ण
EXPORT_SYMBOL_GPL(__iscsi_put_task);

व्योम iscsi_put_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_session *session = task->conn->session;

	/* regular RX path uses back_lock */
	spin_lock_bh(&session->back_lock);
	__iscsi_put_task(task);
	spin_unlock_bh(&session->back_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_put_task);

/**
 * iscsi_complete_task - finish a task
 * @task: iscsi cmd task
 * @state: state to complete task with
 *
 * Must be called with session back_lock.
 */
अटल व्योम iscsi_complete_task(काष्ठा iscsi_task *task, पूर्णांक state)
अणु
	काष्ठा iscsi_conn *conn = task->conn;

	ISCSI_DBG_SESSION(conn->session,
			  "complete task itt 0x%x state %d sc %p\n",
			  task->itt, task->state, task->sc);
	अगर (task->state == ISCSI_TASK_COMPLETED ||
	    task->state == ISCSI_TASK_ABRT_TMF ||
	    task->state == ISCSI_TASK_ABRT_SESS_RECOV ||
	    task->state == ISCSI_TASK_REQUEUE_SCSIQ)
		वापस;
	WARN_ON_ONCE(task->state == ISCSI_TASK_FREE);
	task->state = state;

	अगर (READ_ONCE(conn->ping_task) == task)
		WRITE_ONCE(conn->ping_task, शून्य);

	/* release get from queueing */
	__iscsi_put_task(task);
पूर्ण

/**
 * iscsi_complete_scsi_task - finish scsi task normally
 * @task: iscsi task क्रम scsi cmd
 * @exp_cmdsn: expected cmd sn in cpu क्रमmat
 * @max_cmdsn: max cmd sn in cpu क्रमmat
 *
 * This is used when drivers करो not need or cannot perक्रमm
 * lower level pdu processing.
 *
 * Called with session back_lock
 */
व्योम iscsi_complete_scsi_task(काष्ठा iscsi_task *task,
			      uपूर्णांक32_t exp_cmdsn, uपूर्णांक32_t max_cmdsn)
अणु
	काष्ठा iscsi_conn *conn = task->conn;

	ISCSI_DBG_SESSION(conn->session, "[itt 0x%x]\n", task->itt);

	conn->last_recv = jअगरfies;
	__iscsi_update_cmdsn(conn->session, exp_cmdsn, max_cmdsn);
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_complete_scsi_task);

/*
 * Must be called with back and frwd lock
 */
अटल bool cleanup_queued_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	bool early_complete = false;

	/* Bad target might have completed task जबतक it was still running */
	अगर (task->state == ISCSI_TASK_COMPLETED)
		early_complete = true;

	अगर (!list_empty(&task->running)) अणु
		list_del_init(&task->running);
		/*
		 * If it's on a list but still running, this could be from
		 * a bad target sending a rsp early, cleanup from a TMF, or
		 * session recovery.
		 */
		अगर (task->state == ISCSI_TASK_RUNNING ||
		    task->state == ISCSI_TASK_COMPLETED)
			__iscsi_put_task(task);
	पूर्ण

	अगर (conn->task == task) अणु
		conn->task = शून्य;
		__iscsi_put_task(task);
	पूर्ण

	वापस early_complete;
पूर्ण

/*
 * session frwd lock must be held and अगर not called क्रम a task that is still
 * pending or from the xmit thपढ़ो, then xmit thपढ़ो must be suspended
 */
अटल व्योम fail_scsi_task(काष्ठा iscsi_task *task, पूर्णांक err)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा scsi_cmnd *sc;
	पूर्णांक state;

	spin_lock_bh(&conn->session->back_lock);
	अगर (cleanup_queued_task(task)) अणु
		spin_unlock_bh(&conn->session->back_lock);
		वापस;
	पूर्ण

	अगर (task->state == ISCSI_TASK_PENDING) अणु
		/*
		 * cmd never made it to the xmit thपढ़ो, so we should not count
		 * the cmd in the sequencing
		 */
		conn->session->queued_cmdsn--;
		/* it was never sent so just complete like normal */
		state = ISCSI_TASK_COMPLETED;
	पूर्ण अन्यथा अगर (err == DID_TRANSPORT_DISRUPTED)
		state = ISCSI_TASK_ABRT_SESS_RECOV;
	अन्यथा
		state = ISCSI_TASK_ABRT_TMF;

	sc = task->sc;
	sc->result = err << 16;
	scsi_set_resid(sc, scsi_bufflen(sc));
	iscsi_complete_task(task, state);
	spin_unlock_bh(&conn->session->back_lock);
पूर्ण

अटल पूर्णांक iscsi_prep_mgmt_task(काष्ठा iscsi_conn *conn,
				काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_hdr *hdr = task->hdr;
	काष्ठा iscsi_nopout *nop = (काष्ठा iscsi_nopout *)hdr;
	uपूर्णांक8_t opcode = hdr->opcode & ISCSI_OPCODE_MASK;

	अगर (conn->session->state == ISCSI_STATE_LOGGING_OUT)
		वापस -ENOTCONN;

	अगर (opcode != ISCSI_OP_LOGIN && opcode != ISCSI_OP_TEXT)
		nop->exp_statsn = cpu_to_be32(conn->exp_statsn);
	/*
	 * pre-क्रमmat CmdSN क्रम outgoing PDU.
	 */
	nop->cmdsn = cpu_to_be32(session->cmdsn);
	अगर (hdr->itt != RESERVED_ITT) अणु
		/*
		 * TODO: We always use immediate क्रम normal session pdus.
		 * If we start to send पंचांगfs or nops as non-immediate then
		 * we should start checking the cmdsn numbers क्रम mgmt tasks.
		 *
		 * During discovery sessions iscsid sends TEXT as non immediate,
		 * but we always only send one PDU at a समय.
		 */
		अगर (conn->c_stage == ISCSI_CONN_STARTED &&
		    !(hdr->opcode & ISCSI_OP_IMMEDIATE)) अणु
			session->queued_cmdsn++;
			session->cmdsn++;
		पूर्ण
	पूर्ण

	अगर (session->tt->init_task && session->tt->init_task(task))
		वापस -EIO;

	अगर ((hdr->opcode & ISCSI_OPCODE_MASK) == ISCSI_OP_LOGOUT)
		session->state = ISCSI_STATE_LOGGING_OUT;

	task->state = ISCSI_TASK_RUNNING;
	ISCSI_DBG_SESSION(session, "mgmtpdu [op 0x%x hdr->itt 0x%x "
			  "datalen %d]\n", hdr->opcode & ISCSI_OPCODE_MASK,
			  hdr->itt, task->data_count);
	वापस 0;
पूर्ण

अटल काष्ठा iscsi_task *
__iscsi_conn_send_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
		      अक्षर *data, uपूर्णांक32_t data_size)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_host *ihost = shost_priv(session->host);
	uपूर्णांक8_t opcode = hdr->opcode & ISCSI_OPCODE_MASK;
	काष्ठा iscsi_task *task;
	itt_t itt;

	अगर (session->state == ISCSI_STATE_TERMINATE)
		वापस शून्य;

	अगर (opcode == ISCSI_OP_LOGIN || opcode == ISCSI_OP_TEXT) अणु
		/*
		 * Login and Text are sent serially, in
		 * request-followed-by-response sequence.
		 * Same task can be used. Same ITT must be used.
		 * Note that login_task is pपुनः_स्मृतिated at conn_create().
		 */
		अगर (conn->login_task->state != ISCSI_TASK_FREE) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Login/Text in "
					  "progress. Cannot start new task.\n");
			वापस शून्य;
		पूर्ण

		अगर (data_size > ISCSI_DEF_MAX_RECV_SEG_LEN) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Invalid buffer len of %u for login task. Max len is %u\n", data_size, ISCSI_DEF_MAX_RECV_SEG_LEN);
			वापस शून्य;
		पूर्ण

		task = conn->login_task;
	पूर्ण अन्यथा अणु
		अगर (session->state != ISCSI_STATE_LOGGED_IN)
			वापस शून्य;

		अगर (data_size != 0) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Can not send data buffer of len %u for op 0x%x\n", data_size, opcode);
			वापस शून्य;
		पूर्ण

		BUG_ON(conn->c_stage == ISCSI_CONN_INITIAL_STAGE);
		BUG_ON(conn->c_stage == ISCSI_CONN_STOPPED);

		अगर (!kfअगरo_out(&session->cmdpool.queue,
				 (व्योम*)&task, माप(व्योम*)))
			वापस शून्य;
	पूर्ण
	/*
	 * released in complete pdu क्रम task we expect a response क्रम, and
	 * released by the lld when it has transmitted the task क्रम
	 * pdus we करो not expect a response क्रम.
	 */
	refcount_set(&task->refcount, 1);
	task->conn = conn;
	task->sc = शून्य;
	INIT_LIST_HEAD(&task->running);
	task->state = ISCSI_TASK_PENDING;

	अगर (data_size) अणु
		स_नकल(task->data, data, data_size);
		task->data_count = data_size;
	पूर्ण अन्यथा
		task->data_count = 0;

	अगर (conn->session->tt->alloc_pdu) अणु
		अगर (conn->session->tt->alloc_pdu(task, hdr->opcode)) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Could not allocate "
					 "pdu for mgmt task.\n");
			जाओ मुक्त_task;
		पूर्ण
	पूर्ण

	itt = task->hdr->itt;
	task->hdr_len = माप(काष्ठा iscsi_hdr);
	स_नकल(task->hdr, hdr, माप(काष्ठा iscsi_hdr));

	अगर (hdr->itt != RESERVED_ITT) अणु
		अगर (session->tt->parse_pdu_itt)
			task->hdr->itt = itt;
		अन्यथा
			task->hdr->itt = build_itt(task->itt,
						   task->conn->session->age);
	पूर्ण

	अगर (unlikely(READ_ONCE(conn->ping_task) == INVALID_SCSI_TASK))
		WRITE_ONCE(conn->ping_task, task);

	अगर (!ihost->workq) अणु
		अगर (iscsi_prep_mgmt_task(conn, task))
			जाओ मुक्त_task;

		अगर (session->tt->xmit_task(task))
			जाओ मुक्त_task;
	पूर्ण अन्यथा अणु
		list_add_tail(&task->running, &conn->mgmtqueue);
		iscsi_conn_queue_work(conn);
	पूर्ण

	वापस task;

मुक्त_task:
	/* regular RX path uses back_lock */
	spin_lock(&session->back_lock);
	__iscsi_put_task(task);
	spin_unlock(&session->back_lock);
	वापस शून्य;
पूर्ण

पूर्णांक iscsi_conn_send_pdu(काष्ठा iscsi_cls_conn *cls_conn, काष्ठा iscsi_hdr *hdr,
			अक्षर *data, uपूर्णांक32_t data_size)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक err = 0;

	spin_lock_bh(&session->frwd_lock);
	अगर (!__iscsi_conn_send_pdu(conn, hdr, data, data_size))
		err = -EPERM;
	spin_unlock_bh(&session->frwd_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_send_pdu);

/**
 * iscsi_scsi_cmd_rsp - SCSI Command Response processing
 * @conn: iscsi connection
 * @hdr: iscsi header
 * @task: scsi command task
 * @data: cmd data buffer
 * @datalen: len of buffer
 *
 * iscsi_cmd_rsp sets up the scsi_cmnd fields based on the PDU and
 * then completes the command and task. called under back_lock
 **/
अटल व्योम iscsi_scsi_cmd_rsp(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
			       काष्ठा iscsi_task *task, अक्षर *data,
			       पूर्णांक datalen)
अणु
	काष्ठा iscsi_scsi_rsp *rhdr = (काष्ठा iscsi_scsi_rsp *)hdr;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा scsi_cmnd *sc = task->sc;

	iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)rhdr);
	conn->exp_statsn = be32_to_cpu(rhdr->statsn) + 1;

	sc->result = (DID_OK << 16) | rhdr->cmd_status;

	अगर (task->रक्षित) अणु
		sector_t sector;
		u8 ascq;

		/**
		 * Transports that didn't implement check_protection
		 * callback but still published T10-PI support to scsi-mid
		 * deserve this BUG_ON.
		 **/
		BUG_ON(!session->tt->check_protection);

		ascq = session->tt->check_protection(task, &sector);
		अगर (ascq) अणु
			sc->result = DRIVER_SENSE << 24 |
				     SAM_STAT_CHECK_CONDITION;
			scsi_build_sense_buffer(1, sc->sense_buffer,
						ILLEGAL_REQUEST, 0x10, ascq);
			scsi_set_sense_inक्रमmation(sc->sense_buffer,
						   SCSI_SENSE_BUFFERSIZE,
						   sector);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rhdr->response != ISCSI_STATUS_CMD_COMPLETED) अणु
		sc->result = DID_ERROR << 16;
		जाओ out;
	पूर्ण

	अगर (rhdr->cmd_status == SAM_STAT_CHECK_CONDITION) अणु
		uपूर्णांक16_t senselen;

		अगर (datalen < 2) अणु
invalid_datalen:
			iscsi_conn_prपूर्णांकk(KERN_ERR,  conn,
					 "Got CHECK_CONDITION but invalid data "
					 "buffer size of %d\n", datalen);
			sc->result = DID_BAD_TARGET << 16;
			जाओ out;
		पूर्ण

		senselen = get_unaligned_be16(data);
		अगर (datalen < senselen)
			जाओ invalid_datalen;

		स_नकल(sc->sense_buffer, data + 2,
		       min_t(uपूर्णांक16_t, senselen, SCSI_SENSE_BUFFERSIZE));
		ISCSI_DBG_SESSION(session, "copied %d bytes of sense\n",
				  min_t(uपूर्णांक16_t, senselen,
				  SCSI_SENSE_BUFFERSIZE));
	पूर्ण

	अगर (rhdr->flags & (ISCSI_FLAG_CMD_BIDI_UNDERFLOW |
			   ISCSI_FLAG_CMD_BIDI_OVERFLOW)) अणु
		sc->result = (DID_BAD_TARGET << 16) | rhdr->cmd_status;
	पूर्ण

	अगर (rhdr->flags & (ISCSI_FLAG_CMD_UNDERFLOW |
	                   ISCSI_FLAG_CMD_OVERFLOW)) अणु
		पूर्णांक res_count = be32_to_cpu(rhdr->residual_count);

		अगर (res_count > 0 &&
		    (rhdr->flags & ISCSI_FLAG_CMD_OVERFLOW ||
		     res_count <= scsi_bufflen(sc)))
			/* ग_लिखो side क्रम bidi or uni-io set_resid */
			scsi_set_resid(sc, res_count);
		अन्यथा
			sc->result = (DID_BAD_TARGET << 16) | rhdr->cmd_status;
	पूर्ण
out:
	ISCSI_DBG_SESSION(session, "cmd rsp done [sc %p res %d itt 0x%x]\n",
			  sc, sc->result, task->itt);
	conn->scsirsp_pdus_cnt++;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
पूर्ण

/**
 * iscsi_data_in_rsp - SCSI Data-In Response processing
 * @conn: iscsi connection
 * @hdr:  iscsi pdu
 * @task: scsi command task
 *
 * iscsi_data_in_rsp sets up the scsi_cmnd fields based on the data received
 * then completes the command and task. called under back_lock
 **/
अटल व्योम
iscsi_data_in_rsp(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
		  काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_data_rsp *rhdr = (काष्ठा iscsi_data_rsp *)hdr;
	काष्ठा scsi_cmnd *sc = task->sc;

	अगर (!(rhdr->flags & ISCSI_FLAG_DATA_STATUS))
		वापस;

	iscsi_update_cmdsn(conn->session, (काष्ठा iscsi_nopin *)hdr);
	sc->result = (DID_OK << 16) | rhdr->cmd_status;
	conn->exp_statsn = be32_to_cpu(rhdr->statsn) + 1;
	अगर (rhdr->flags & (ISCSI_FLAG_DATA_UNDERFLOW |
	                   ISCSI_FLAG_DATA_OVERFLOW)) अणु
		पूर्णांक res_count = be32_to_cpu(rhdr->residual_count);

		अगर (res_count > 0 &&
		    (rhdr->flags & ISCSI_FLAG_CMD_OVERFLOW ||
		     res_count <= sc->sdb.length))
			scsi_set_resid(sc, res_count);
		अन्यथा
			sc->result = (DID_BAD_TARGET << 16) | rhdr->cmd_status;
	पूर्ण

	ISCSI_DBG_SESSION(conn->session, "data in with status done "
			  "[sc %p res %d itt 0x%x]\n",
			  sc, sc->result, task->itt);
	conn->scsirsp_pdus_cnt++;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
पूर्ण

अटल व्योम iscsi_पंचांगf_rsp(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr)
अणु
	काष्ठा iscsi_पंचांग_rsp *पंचांगf = (काष्ठा iscsi_पंचांग_rsp *)hdr;

	conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;
	conn->पंचांगfrsp_pdus_cnt++;

	अगर (conn->पंचांगf_state != TMF_QUEUED)
		वापस;

	अगर (पंचांगf->response == ISCSI_TMF_RSP_COMPLETE)
		conn->पंचांगf_state = TMF_SUCCESS;
	अन्यथा अगर (पंचांगf->response == ISCSI_TMF_RSP_NO_TASK)
		conn->पंचांगf_state = TMF_NOT_FOUND;
	अन्यथा
		conn->पंचांगf_state = TMF_FAILED;
	wake_up(&conn->ehरुको);
पूर्ण

अटल पूर्णांक iscsi_send_nopout(काष्ठा iscsi_conn *conn, काष्ठा iscsi_nopin *rhdr)
अणु
        काष्ठा iscsi_nopout hdr;
	काष्ठा iscsi_task *task;

	अगर (!rhdr) अणु
		अगर (READ_ONCE(conn->ping_task))
			वापस -EINVAL;
		WRITE_ONCE(conn->ping_task, INVALID_SCSI_TASK);
	पूर्ण

	स_रखो(&hdr, 0, माप(काष्ठा iscsi_nopout));
	hdr.opcode = ISCSI_OP_NOOP_OUT | ISCSI_OP_IMMEDIATE;
	hdr.flags = ISCSI_FLAG_CMD_FINAL;

	अगर (rhdr) अणु
		hdr.lun = rhdr->lun;
		hdr.ttt = rhdr->ttt;
		hdr.itt = RESERVED_ITT;
	पूर्ण अन्यथा
		hdr.ttt = RESERVED_ITT;

	task = __iscsi_conn_send_pdu(conn, (काष्ठा iscsi_hdr *)&hdr, शून्य, 0);
	अगर (!task) अणु
		अगर (!rhdr)
			WRITE_ONCE(conn->ping_task, शून्य);
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Could not send nopout\n");
		वापस -EIO;
	पूर्ण अन्यथा अगर (!rhdr) अणु
		/* only track our nops */
		conn->last_ping = jअगरfies;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iscsi_nop_out_rsp - SCSI NOP Response processing
 * @task: scsi command task
 * @nop: the nop काष्ठाure
 * @data: where to put the data
 * @datalen: length of data
 *
 * iscsi_nop_out_rsp handles nop response from use or
 * from user space. called under back_lock
 **/
अटल पूर्णांक iscsi_nop_out_rsp(काष्ठा iscsi_task *task,
			     काष्ठा iscsi_nopin *nop, अक्षर *data, पूर्णांक datalen)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	पूर्णांक rc = 0;

	अगर (READ_ONCE(conn->ping_task) != task) अणु
		/*
		 * If this is not in response to one of our
		 * nops then it must be from userspace.
		 */
		अगर (iscsi_recv_pdu(conn->cls_conn, (काष्ठा iscsi_hdr *)nop,
				   data, datalen))
			rc = ISCSI_ERR_CONN_FAILED;
	पूर्ण अन्यथा
		mod_समयr(&conn->transport_समयr, jअगरfies + conn->recv_समयout);
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
	वापस rc;
पूर्ण

अटल पूर्णांक iscsi_handle_reject(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
			       अक्षर *data, पूर्णांक datalen)
अणु
	काष्ठा iscsi_reject *reject = (काष्ठा iscsi_reject *)hdr;
	काष्ठा iscsi_hdr rejected_pdu;
	पूर्णांक opcode, rc = 0;

	conn->exp_statsn = be32_to_cpu(reject->statsn) + 1;

	अगर (ntoh24(reject->dlength) > datalen ||
	    ntoh24(reject->dlength) < माप(काष्ठा iscsi_hdr)) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Cannot handle rejected "
				  "pdu. Invalid data length (pdu dlength "
				  "%u, datalen %d\n", ntoh24(reject->dlength),
				  datalen);
		वापस ISCSI_ERR_PROTO;
	पूर्ण
	स_नकल(&rejected_pdu, data, माप(काष्ठा iscsi_hdr));
	opcode = rejected_pdu.opcode & ISCSI_OPCODE_MASK;

	चयन (reject->reason) अणु
	हाल ISCSI_REASON_DATA_DIGEST_ERROR:
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected "
				  "due to DataDigest error.\n",
				  opcode, rejected_pdu.itt);
		अवरोध;
	हाल ISCSI_REASON_IMM_CMD_REJECT:
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected. Too many "
				  "immediate commands.\n",
				  opcode, rejected_pdu.itt);
		/*
		 * We only send one TMF at a समय so अगर the target could not
		 * handle it, then it should get fixed (RFC mandates that
		 * a target can handle one immediate TMF per conn).
		 *
		 * For nops-outs, we could have sent more than one अगर
		 * the target is sending us lots of nop-ins
		 */
		अगर (opcode != ISCSI_OP_NOOP_OUT)
			वापस 0;

		अगर (rejected_pdu.itt == cpu_to_be32(ISCSI_RESERVED_TAG)) अणु
			/*
			 * nop-out in response to target's nop-out rejected.
			 * Just resend.
			 */
			/* In RX path we are under back lock */
			spin_unlock(&conn->session->back_lock);
			spin_lock(&conn->session->frwd_lock);
			iscsi_send_nopout(conn,
					  (काष्ठा iscsi_nopin*)&rejected_pdu);
			spin_unlock(&conn->session->frwd_lock);
			spin_lock(&conn->session->back_lock);
		पूर्ण अन्यथा अणु
			काष्ठा iscsi_task *task;
			/*
			 * Our nop as ping got dropped. We know the target
			 * and transport are ok so just clean up
			 */
			task = iscsi_itt_to_task(conn, rejected_pdu.itt);
			अगर (!task) अणु
				iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
						 "Invalid pdu reject. Could "
						 "not lookup rejected task.\n");
				rc = ISCSI_ERR_BAD_ITT;
			पूर्ण अन्यथा
				rc = iscsi_nop_out_rsp(task,
					(काष्ठा iscsi_nopin*)&rejected_pdu,
					शून्य, 0);
		पूर्ण
		अवरोध;
	शेष:
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected. Reason "
				  "code 0x%x\n", rejected_pdu.opcode,
				  rejected_pdu.itt, reject->reason);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * iscsi_itt_to_task - look up task by itt
 * @conn: iscsi connection
 * @itt: itt
 *
 * This should be used क्रम mgmt tasks like login and nops, or अगर
 * the LDD's itt space करोes not include the session age.
 *
 * The session back_lock must be held.
 */
काष्ठा iscsi_task *iscsi_itt_to_task(काष्ठा iscsi_conn *conn, itt_t itt)
अणु
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक i;

	अगर (itt == RESERVED_ITT)
		वापस शून्य;

	अगर (session->tt->parse_pdu_itt)
		session->tt->parse_pdu_itt(conn, itt, &i, शून्य);
	अन्यथा
		i = get_itt(itt);
	अगर (i >= session->cmds_max)
		वापस शून्य;

	वापस session->cmds[i];
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_itt_to_task);

/**
 * __iscsi_complete_pdu - complete pdu
 * @conn: iscsi conn
 * @hdr: iscsi header
 * @data: data buffer
 * @datalen: len of data buffer
 *
 * Completes pdu processing by मुक्तing any resources allocated at
 * queuecommand or send generic. session back_lock must be held and verअगरy
 * itt must have been called.
 */
पूर्णांक __iscsi_complete_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
			 अक्षर *data, पूर्णांक datalen)
अणु
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक opcode = hdr->opcode & ISCSI_OPCODE_MASK, rc = 0;
	काष्ठा iscsi_task *task;
	uपूर्णांक32_t itt;

	conn->last_recv = jअगरfies;
	rc = iscsi_verअगरy_itt(conn, hdr->itt);
	अगर (rc)
		वापस rc;

	अगर (hdr->itt != RESERVED_ITT)
		itt = get_itt(hdr->itt);
	अन्यथा
		itt = ~0U;

	ISCSI_DBG_SESSION(session, "[op 0x%x cid %d itt 0x%x len %d]\n",
			  opcode, conn->id, itt, datalen);

	अगर (itt == ~0U) अणु
		iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)hdr);

		चयन(opcode) अणु
		हाल ISCSI_OP_NOOP_IN:
			अगर (datalen) अणु
				rc = ISCSI_ERR_PROTO;
				अवरोध;
			पूर्ण

			अगर (hdr->ttt == cpu_to_be32(ISCSI_RESERVED_TAG))
				अवरोध;

			/* In RX path we are under back lock */
			spin_unlock(&session->back_lock);
			spin_lock(&session->frwd_lock);
			iscsi_send_nopout(conn, (काष्ठा iscsi_nopin*)hdr);
			spin_unlock(&session->frwd_lock);
			spin_lock(&session->back_lock);
			अवरोध;
		हाल ISCSI_OP_REJECT:
			rc = iscsi_handle_reject(conn, hdr, data, datalen);
			अवरोध;
		हाल ISCSI_OP_ASYNC_EVENT:
			conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;
			अगर (iscsi_recv_pdu(conn->cls_conn, hdr, data, datalen))
				rc = ISCSI_ERR_CONN_FAILED;
			अवरोध;
		शेष:
			rc = ISCSI_ERR_BAD_OPCODE;
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	चयन(opcode) अणु
	हाल ISCSI_OP_SCSI_CMD_RSP:
	हाल ISCSI_OP_SCSI_DATA_IN:
		task = iscsi_itt_to_ctask(conn, hdr->itt);
		अगर (!task)
			वापस ISCSI_ERR_BAD_ITT;
		task->last_xfer = jअगरfies;
		अवरोध;
	हाल ISCSI_OP_R2T:
		/*
		 * LLD handles R2Ts अगर they need to.
		 */
		वापस 0;
	हाल ISCSI_OP_LOGOUT_RSP:
	हाल ISCSI_OP_LOGIN_RSP:
	हाल ISCSI_OP_TEXT_RSP:
	हाल ISCSI_OP_SCSI_TMFUNC_RSP:
	हाल ISCSI_OP_NOOP_IN:
		task = iscsi_itt_to_task(conn, hdr->itt);
		अगर (!task)
			वापस ISCSI_ERR_BAD_ITT;
		अवरोध;
	शेष:
		वापस ISCSI_ERR_BAD_OPCODE;
	पूर्ण

	चयन(opcode) अणु
	हाल ISCSI_OP_SCSI_CMD_RSP:
		iscsi_scsi_cmd_rsp(conn, hdr, task, data, datalen);
		अवरोध;
	हाल ISCSI_OP_SCSI_DATA_IN:
		iscsi_data_in_rsp(conn, hdr, task);
		अवरोध;
	हाल ISCSI_OP_LOGOUT_RSP:
		iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)hdr);
		अगर (datalen) अणु
			rc = ISCSI_ERR_PROTO;
			अवरोध;
		पूर्ण
		conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;
		जाओ recv_pdu;
	हाल ISCSI_OP_LOGIN_RSP:
	हाल ISCSI_OP_TEXT_RSP:
		iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)hdr);
		/*
		 * login related PDU's exp_statsn is handled in
		 * userspace
		 */
		जाओ recv_pdu;
	हाल ISCSI_OP_SCSI_TMFUNC_RSP:
		iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)hdr);
		अगर (datalen) अणु
			rc = ISCSI_ERR_PROTO;
			अवरोध;
		पूर्ण

		iscsi_पंचांगf_rsp(conn, hdr);
		iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
		अवरोध;
	हाल ISCSI_OP_NOOP_IN:
		iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin*)hdr);
		अगर (hdr->ttt != cpu_to_be32(ISCSI_RESERVED_TAG) || datalen) अणु
			rc = ISCSI_ERR_PROTO;
			अवरोध;
		पूर्ण
		conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;

		rc = iscsi_nop_out_rsp(task, (काष्ठा iscsi_nopin*)hdr,
				       data, datalen);
		अवरोध;
	शेष:
		rc = ISCSI_ERR_BAD_OPCODE;
		अवरोध;
	पूर्ण

out:
	वापस rc;
recv_pdu:
	अगर (iscsi_recv_pdu(conn->cls_conn, hdr, data, datalen))
		rc = ISCSI_ERR_CONN_FAILED;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(__iscsi_complete_pdu);

पूर्णांक iscsi_complete_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
		       अक्षर *data, पूर्णांक datalen)
अणु
	पूर्णांक rc;

	spin_lock(&conn->session->back_lock);
	rc = __iscsi_complete_pdu(conn, hdr, data, datalen);
	spin_unlock(&conn->session->back_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_complete_pdu);

पूर्णांक iscsi_verअगरy_itt(काष्ठा iscsi_conn *conn, itt_t itt)
अणु
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक age = 0, i = 0;

	अगर (itt == RESERVED_ITT)
		वापस 0;

	अगर (session->tt->parse_pdu_itt)
		session->tt->parse_pdu_itt(conn, itt, &i, &age);
	अन्यथा अणु
		i = get_itt(itt);
		age = ((__क्रमce u32)itt >> ISCSI_AGE_SHIFT) & ISCSI_AGE_MASK;
	पूर्ण

	अगर (age != session->age) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "received itt %x expected session age (%x)\n",
				  (__क्रमce u32)itt, session->age);
		वापस ISCSI_ERR_BAD_ITT;
	पूर्ण

	अगर (i >= session->cmds_max) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "received invalid itt index %u (max cmds "
				   "%u.\n", i, session->cmds_max);
		वापस ISCSI_ERR_BAD_ITT;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_verअगरy_itt);

/**
 * iscsi_itt_to_ctask - look up ctask by itt
 * @conn: iscsi connection
 * @itt: itt
 *
 * This should be used क्रम cmd tasks.
 *
 * The session back_lock must be held.
 */
काष्ठा iscsi_task *iscsi_itt_to_ctask(काष्ठा iscsi_conn *conn, itt_t itt)
अणु
	काष्ठा iscsi_task *task;

	अगर (iscsi_verअगरy_itt(conn, itt))
		वापस शून्य;

	task = iscsi_itt_to_task(conn, itt);
	अगर (!task || !task->sc)
		वापस शून्य;

	अगर (task->sc->SCp.phase != conn->session->age) अणु
		iscsi_session_prपूर्णांकk(KERN_ERR, conn->session,
				  "task's session age %d, expected %d\n",
				  task->sc->SCp.phase, conn->session->age);
		वापस शून्य;
	पूर्ण

	वापस task;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_itt_to_ctask);

व्योम iscsi_session_failure(काष्ठा iscsi_session *session,
			   क्रमागत iscsi_err err)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा device *dev;

	spin_lock_bh(&session->frwd_lock);
	conn = session->leadconn;
	अगर (session->state == ISCSI_STATE_TERMINATE || !conn) अणु
		spin_unlock_bh(&session->frwd_lock);
		वापस;
	पूर्ण

	dev = get_device(&conn->cls_conn->dev);
	spin_unlock_bh(&session->frwd_lock);
	अगर (!dev)
	        वापस;
	/*
	 * अगर the host is being हटाओd bypass the connection
	 * recovery initialization because we are going to समाप्त
	 * the session.
	 */
	अगर (err == ISCSI_ERR_INVALID_HOST)
		iscsi_conn_error_event(conn->cls_conn, err);
	अन्यथा
		iscsi_conn_failure(conn, err);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_failure);

व्योम iscsi_conn_failure(काष्ठा iscsi_conn *conn, क्रमागत iscsi_err err)
अणु
	काष्ठा iscsi_session *session = conn->session;

	spin_lock_bh(&session->frwd_lock);
	अगर (session->state == ISCSI_STATE_FAILED) अणु
		spin_unlock_bh(&session->frwd_lock);
		वापस;
	पूर्ण

	अगर (conn->stop_stage == 0)
		session->state = ISCSI_STATE_FAILED;
	spin_unlock_bh(&session->frwd_lock);

	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
	iscsi_conn_error_event(conn->cls_conn, err);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_failure);

अटल पूर्णांक iscsi_check_cmdsn_winकरोw_बंदd(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *session = conn->session;

	/*
	 * Check क्रम iSCSI winकरोw and take care of CmdSN wrap-around
	 */
	अगर (!iscsi_sna_lte(session->queued_cmdsn, session->max_cmdsn)) अणु
		ISCSI_DBG_SESSION(session, "iSCSI CmdSN closed. ExpCmdSn "
				  "%u MaxCmdSN %u CmdSN %u/%u\n",
				  session->exp_cmdsn, session->max_cmdsn,
				  session->cmdsn, session->queued_cmdsn);
		वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_xmit_task(काष्ठा iscsi_conn *conn, काष्ठा iscsi_task *task,
			   bool was_requeue)
अणु
	पूर्णांक rc;

	spin_lock_bh(&conn->session->back_lock);

	अगर (!conn->task) अणु
		/* Take a ref so we can access it after xmit_task() */
		__iscsi_get_task(task);
	पूर्ण अन्यथा अणु
		/* Alपढ़ोy have a ref from when we failed to send it last call */
		conn->task = शून्य;
	पूर्ण

	/*
	 * If this was a requeue क्रम a R2T we have an extra ref on the task in
	 * हाल a bad target sends a cmd rsp beक्रमe we have handled the task.
	 */
	अगर (was_requeue)
		__iscsi_put_task(task);

	/*
	 * Do this after dropping the extra ref because अगर this was a requeue
	 * it's हटाओd from that list and cleanup_queued_task would miss it.
	 */
	अगर (test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx)) अणु
		/*
		 * Save the task and ref in हाल we weren't cleaning up this
		 * task and get woken up again.
		 */
		conn->task = task;
		spin_unlock_bh(&conn->session->back_lock);
		वापस -ENODATA;
	पूर्ण
	spin_unlock_bh(&conn->session->back_lock);

	spin_unlock_bh(&conn->session->frwd_lock);
	rc = conn->session->tt->xmit_task(task);
	spin_lock_bh(&conn->session->frwd_lock);
	अगर (!rc) अणु
		/* करोne with this task */
		task->last_xfer = jअगरfies;
	पूर्ण
	/* regular RX path uses back_lock */
	spin_lock(&conn->session->back_lock);
	अगर (rc && task->state == ISCSI_TASK_RUNNING) अणु
		/*
		 * get an extra ref that is released next समय we access it
		 * as conn->task above.
		 */
		__iscsi_get_task(task);
		conn->task = task;
	पूर्ण

	__iscsi_put_task(task);
	spin_unlock(&conn->session->back_lock);
	वापस rc;
पूर्ण

/**
 * iscsi_requeue_task - requeue task to run from session workqueue
 * @task: task to requeue
 *
 * Callers must have taken a ref to the task that is going to be requeued.
 */
व्योम iscsi_requeue_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;

	/*
	 * this may be on the requeue list alपढ़ोy अगर the xmit_task callout
	 * is handling the r2ts जबतक we are adding new ones
	 */
	spin_lock_bh(&conn->session->frwd_lock);
	अगर (list_empty(&task->running)) अणु
		list_add_tail(&task->running, &conn->requeue);
	पूर्ण अन्यथा अणु
		/*
		 * Don't need the extra ref since it's alपढ़ोy requeued and
		 * has a ref.
		 */
		iscsi_put_task(task);
	पूर्ण
	iscsi_conn_queue_work(conn);
	spin_unlock_bh(&conn->session->frwd_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_requeue_task);

/**
 * iscsi_data_xmit - xmit any command पूर्णांकo the scheduled connection
 * @conn: iscsi connection
 *
 * Notes:
 *	The function can वापस -EAGAIN in which हाल the caller must
 *	re-schedule it again later or recover. '0' वापस code means
 *	successful xmit.
 **/
अटल पूर्णांक iscsi_data_xmit(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_task *task;
	पूर्णांक rc = 0;

	spin_lock_bh(&conn->session->frwd_lock);
	अगर (test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx)) अणु
		ISCSI_DBG_SESSION(conn->session, "Tx suspended!\n");
		spin_unlock_bh(&conn->session->frwd_lock);
		वापस -ENODATA;
	पूर्ण

	अगर (conn->task) अणु
		rc = iscsi_xmit_task(conn, conn->task, false);
	        अगर (rc)
		        जाओ करोne;
	पूर्ण

	/*
	 * process mgmt pdus like nops beक्रमe commands since we should
	 * only have one nop-out as a ping from us and tarमाला_लो should not
	 * overflow us with nop-ins
	 */
check_mgmt:
	जबतक (!list_empty(&conn->mgmtqueue)) अणु
		task = list_entry(conn->mgmtqueue.next, काष्ठा iscsi_task,
				  running);
		list_del_init(&task->running);
		अगर (iscsi_prep_mgmt_task(conn, task)) अणु
			/* regular RX path uses back_lock */
			spin_lock_bh(&conn->session->back_lock);
			__iscsi_put_task(task);
			spin_unlock_bh(&conn->session->back_lock);
			जारी;
		पूर्ण
		rc = iscsi_xmit_task(conn, task, false);
		अगर (rc)
			जाओ करोne;
	पूर्ण

	/* process pending command queue */
	जबतक (!list_empty(&conn->cmdqueue)) अणु
		task = list_entry(conn->cmdqueue.next, काष्ठा iscsi_task,
				  running);
		list_del_init(&task->running);
		अगर (conn->session->state == ISCSI_STATE_LOGGING_OUT) अणु
			fail_scsi_task(task, DID_IMM_RETRY);
			जारी;
		पूर्ण
		rc = iscsi_prep_scsi_cmd_pdu(task);
		अगर (rc) अणु
			अगर (rc == -ENOMEM || rc == -EACCES)
				fail_scsi_task(task, DID_IMM_RETRY);
			अन्यथा
				fail_scsi_task(task, DID_ABORT);
			जारी;
		पूर्ण
		rc = iscsi_xmit_task(conn, task, false);
		अगर (rc)
			जाओ करोne;
		/*
		 * we could continuously get new task requests so
		 * we need to check the mgmt queue क्रम nops that need to
		 * be sent to aviod starvation
		 */
		अगर (!list_empty(&conn->mgmtqueue))
			जाओ check_mgmt;
	पूर्ण

	जबतक (!list_empty(&conn->requeue)) अणु
		/*
		 * we always करो fastlogout - conn stop code will clean up.
		 */
		अगर (conn->session->state == ISCSI_STATE_LOGGING_OUT)
			अवरोध;

		task = list_entry(conn->requeue.next, काष्ठा iscsi_task,
				  running);

		अगर (iscsi_check_पंचांगf_restrictions(task, ISCSI_OP_SCSI_DATA_OUT))
			अवरोध;

		list_del_init(&task->running);
		rc = iscsi_xmit_task(conn, task, true);
		अगर (rc)
			जाओ करोne;
		अगर (!list_empty(&conn->mgmtqueue))
			जाओ check_mgmt;
	पूर्ण
	spin_unlock_bh(&conn->session->frwd_lock);
	वापस -ENODATA;

करोne:
	spin_unlock_bh(&conn->session->frwd_lock);
	वापस rc;
पूर्ण

अटल व्योम iscsi_xmitworker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_conn *conn =
		container_of(work, काष्ठा iscsi_conn, xmitwork);
	पूर्णांक rc;
	/*
	 * serialize Xmit worker on a per-connection basis.
	 */
	करो अणु
		rc = iscsi_data_xmit(conn);
	पूर्ण जबतक (rc >= 0 || rc == -EAGAIN);
पूर्ण

अटल अंतरभूत काष्ठा iscsi_task *iscsi_alloc_task(काष्ठा iscsi_conn *conn,
						  काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_task *task;

	अगर (!kfअगरo_out(&conn->session->cmdpool.queue,
			 (व्योम *) &task, माप(व्योम *)))
		वापस शून्य;

	sc->SCp.phase = conn->session->age;
	sc->SCp.ptr = (अक्षर *) task;

	refcount_set(&task->refcount, 1);
	task->state = ISCSI_TASK_PENDING;
	task->conn = conn;
	task->sc = sc;
	task->have_checked_conn = false;
	task->last_समयout = jअगरfies;
	task->last_xfer = jअगरfies;
	task->रक्षित = false;
	INIT_LIST_HEAD(&task->running);
	वापस task;
पूर्ण

क्रमागत अणु
	FAILURE_BAD_HOST = 1,
	FAILURE_SESSION_FAILED,
	FAILURE_SESSION_FREED,
	FAILURE_WINDOW_CLOSED,
	FAILURE_OOM,
	FAILURE_SESSION_TERMINATE,
	FAILURE_SESSION_IN_RECOVERY,
	FAILURE_SESSION_RECOVERY_TIMEOUT,
	FAILURE_SESSION_LOGGING_OUT,
	FAILURE_SESSION_NOT_READY,
पूर्ण;

पूर्णांक iscsi_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_host *ihost;
	पूर्णांक reason = 0;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_task *task = शून्य;

	sc->result = 0;
	sc->SCp.ptr = शून्य;

	ihost = shost_priv(host);

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;
	spin_lock_bh(&session->frwd_lock);

	reason = iscsi_session_chkपढ़ोy(cls_session);
	अगर (reason) अणु
		sc->result = reason;
		जाओ fault;
	पूर्ण

	अगर (session->state != ISCSI_STATE_LOGGED_IN) अणु
		/*
		 * to handle the race between when we set the recovery state
		 * and block the session we requeue here (commands could
		 * be entering our queuecommand जबतक a block is starting
		 * up because the block code is not locked)
		 */
		चयन (session->state) अणु
		हाल ISCSI_STATE_FAILED:
			/*
			 * cmds should fail during shutकरोwn, अगर the session
			 * state is bad, allowing completion to happen
			 */
			अगर (unlikely(प्रणाली_state != SYSTEM_RUNNING)) अणु
				reason = FAILURE_SESSION_FAILED;
				sc->result = DID_NO_CONNECT << 16;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल ISCSI_STATE_IN_RECOVERY:
			reason = FAILURE_SESSION_IN_RECOVERY;
			sc->result = DID_IMM_RETRY << 16;
			अवरोध;
		हाल ISCSI_STATE_LOGGING_OUT:
			reason = FAILURE_SESSION_LOGGING_OUT;
			sc->result = DID_IMM_RETRY << 16;
			अवरोध;
		हाल ISCSI_STATE_RECOVERY_FAILED:
			reason = FAILURE_SESSION_RECOVERY_TIMEOUT;
			sc->result = DID_TRANSPORT_FAILFAST << 16;
			अवरोध;
		हाल ISCSI_STATE_TERMINATE:
			reason = FAILURE_SESSION_TERMINATE;
			sc->result = DID_NO_CONNECT << 16;
			अवरोध;
		शेष:
			reason = FAILURE_SESSION_FREED;
			sc->result = DID_NO_CONNECT << 16;
		पूर्ण
		जाओ fault;
	पूर्ण

	conn = session->leadconn;
	अगर (!conn) अणु
		reason = FAILURE_SESSION_FREED;
		sc->result = DID_NO_CONNECT << 16;
		जाओ fault;
	पूर्ण

	अगर (test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx)) अणु
		reason = FAILURE_SESSION_IN_RECOVERY;
		sc->result = DID_REQUEUE << 16;
		जाओ fault;
	पूर्ण

	अगर (iscsi_check_cmdsn_winकरोw_बंदd(conn)) अणु
		reason = FAILURE_WINDOW_CLOSED;
		जाओ reject;
	पूर्ण

	task = iscsi_alloc_task(conn, sc);
	अगर (!task) अणु
		reason = FAILURE_OOM;
		जाओ reject;
	पूर्ण

	अगर (!ihost->workq) अणु
		reason = iscsi_prep_scsi_cmd_pdu(task);
		अगर (reason) अणु
			अगर (reason == -ENOMEM ||  reason == -EACCES) अणु
				reason = FAILURE_OOM;
				जाओ prepd_reject;
			पूर्ण अन्यथा अणु
				sc->result = DID_ABORT << 16;
				जाओ prepd_fault;
			पूर्ण
		पूर्ण
		अगर (session->tt->xmit_task(task)) अणु
			session->cmdsn--;
			reason = FAILURE_SESSION_NOT_READY;
			जाओ prepd_reject;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_add_tail(&task->running, &conn->cmdqueue);
		iscsi_conn_queue_work(conn);
	पूर्ण

	session->queued_cmdsn++;
	spin_unlock_bh(&session->frwd_lock);
	वापस 0;

prepd_reject:
	spin_lock_bh(&session->back_lock);
	iscsi_complete_task(task, ISCSI_TASK_REQUEUE_SCSIQ);
	spin_unlock_bh(&session->back_lock);
reject:
	spin_unlock_bh(&session->frwd_lock);
	ISCSI_DBG_SESSION(session, "cmd 0x%x rejected (%d)\n",
			  sc->cmnd[0], reason);
	वापस SCSI_MLQUEUE_TARGET_BUSY;

prepd_fault:
	spin_lock_bh(&session->back_lock);
	iscsi_complete_task(task, ISCSI_TASK_REQUEUE_SCSIQ);
	spin_unlock_bh(&session->back_lock);
fault:
	spin_unlock_bh(&session->frwd_lock);
	ISCSI_DBG_SESSION(session, "iscsi: cmd 0x%x is not queued (%d)\n",
			  sc->cmnd[0], reason);
	scsi_set_resid(sc, scsi_bufflen(sc));
	sc->scsi_करोne(sc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_queuecommand);

पूर्णांक iscsi_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा iscsi_cls_session *cls_session = starget_to_session(starget);
	काष्ठा iscsi_session *session = cls_session->dd_data;

	starget->can_queue = session->scsi_cmds_max;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_target_alloc);

अटल व्योम iscsi_पंचांगf_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_conn *conn = from_समयr(conn, t, पंचांगf_समयr);
	काष्ठा iscsi_session *session = conn->session;

	spin_lock(&session->frwd_lock);
	अगर (conn->पंचांगf_state == TMF_QUEUED) अणु
		conn->पंचांगf_state = TMF_TIMEDOUT;
		ISCSI_DBG_EH(session, "tmf timedout\n");
		/* unblock eh_पात() */
		wake_up(&conn->ehरुको);
	पूर्ण
	spin_unlock(&session->frwd_lock);
पूर्ण

अटल पूर्णांक iscsi_exec_task_mgmt_fn(काष्ठा iscsi_conn *conn,
				   काष्ठा iscsi_पंचांग *hdr, पूर्णांक age,
				   पूर्णांक समयout)
	__must_hold(&session->frwd_lock)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_task *task;

	task = __iscsi_conn_send_pdu(conn, (काष्ठा iscsi_hdr *)hdr,
				      शून्य, 0);
	अगर (!task) अणु
		spin_unlock_bh(&session->frwd_lock);
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Could not send TMF.\n");
		iscsi_conn_failure(conn, ISCSI_ERR_CONN_FAILED);
		spin_lock_bh(&session->frwd_lock);
		वापस -EPERM;
	पूर्ण
	conn->पंचांगfcmd_pdus_cnt++;
	conn->पंचांगf_समयr.expires = समयout * HZ + jअगरfies;
	add_समयr(&conn->पंचांगf_समयr);
	ISCSI_DBG_EH(session, "tmf set timeout\n");

	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);

	/*
	 * block eh thपढ़ो until:
	 *
	 * 1) पंचांगf response
	 * 2) पंचांगf समयout
	 * 3) session is terminated or restarted or userspace has
	 * given up on recovery
	 */
	रुको_event_पूर्णांकerruptible(conn->ehरुको, age != session->age ||
				 session->state != ISCSI_STATE_LOGGED_IN ||
				 conn->पंचांगf_state != TMF_QUEUED);
	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&conn->पंचांगf_समयr);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	/* अगर the session drops it will clean up the task */
	अगर (age != session->age ||
	    session->state != ISCSI_STATE_LOGGED_IN)
		वापस -ENOTCONN;
	वापस 0;
पूर्ण

/*
 * Fail commands. session frwd lock held and xmit thपढ़ो flushed.
 */
अटल व्योम fail_scsi_tasks(काष्ठा iscsi_conn *conn, u64 lun, पूर्णांक error)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_task *task;
	पूर्णांक i;

	spin_lock_bh(&session->back_lock);
	क्रम (i = 0; i < session->cmds_max; i++) अणु
		task = session->cmds[i];
		अगर (!task->sc || task->state == ISCSI_TASK_FREE)
			जारी;

		अगर (lun != -1 && lun != task->sc->device->lun)
			जारी;

		__iscsi_get_task(task);
		spin_unlock_bh(&session->back_lock);

		ISCSI_DBG_SESSION(session,
				  "failing sc %p itt 0x%x state %d\n",
				  task->sc, task->itt, task->state);
		fail_scsi_task(task, error);

		spin_unlock_bh(&session->frwd_lock);
		iscsi_put_task(task);
		spin_lock_bh(&session->frwd_lock);

		spin_lock_bh(&session->back_lock);
	पूर्ण

	spin_unlock_bh(&session->back_lock);
पूर्ण

/**
 * iscsi_suspend_queue - suspend iscsi_queuecommand
 * @conn: iscsi conn to stop queueing IO on
 *
 * This grअसल the session frwd_lock to make sure no one is in
 * xmit_task/queuecommand, and then sets suspend to prevent
 * new commands from being queued. This only needs to be called
 * by offload drivers that need to sync a path like ep disconnect
 * with the iscsi_queuecommand/xmit_task. To start IO again libiscsi
 * will call iscsi_start_tx and iscsi_unblock_session when in FFP.
 */
व्योम iscsi_suspend_queue(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->session->frwd_lock);
	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	spin_unlock_bh(&conn->session->frwd_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_suspend_queue);

/**
 * iscsi_suspend_tx - suspend iscsi_data_xmit
 * @conn: iscsi conn tp stop processing IO on.
 *
 * This function sets the suspend bit to prevent iscsi_data_xmit
 * from sending new IO, and अगर work is queued on the xmit thपढ़ो
 * it will रुको क्रम it to be completed.
 */
व्योम iscsi_suspend_tx(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा Scsi_Host *shost = conn->session->host;
	काष्ठा iscsi_host *ihost = shost_priv(shost);

	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	अगर (ihost->workq)
		flush_workqueue(ihost->workq);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_suspend_tx);

अटल व्योम iscsi_start_tx(काष्ठा iscsi_conn *conn)
अणु
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	iscsi_conn_queue_work(conn);
पूर्ण

/*
 * We want to make sure a ping is in flight. It has समयd out.
 * And we are not busy processing a pdu that is making
 * progress but got started beक्रमe the ping and is taking a जबतक
 * to complete so the ping is just stuck behind it in a queue.
 */
अटल पूर्णांक iscsi_has_ping_समयd_out(काष्ठा iscsi_conn *conn)
अणु
	अगर (READ_ONCE(conn->ping_task) &&
	    समय_beक्रमe_eq(conn->last_recv + (conn->recv_समयout * HZ) +
			   (conn->ping_समयout * HZ), jअगरfies))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

क्रमागत blk_eh_समयr_वापस iscsi_eh_cmd_समयd_out(काष्ठा scsi_cmnd *sc)
अणु
	क्रमागत blk_eh_समयr_वापस rc = BLK_EH_DONE;
	काष्ठा iscsi_task *task = शून्य, *running_task;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;
	पूर्णांक i;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;

	ISCSI_DBG_EH(session, "scsi cmd %p timedout\n", sc);

	spin_lock_bh(&session->frwd_lock);
	spin_lock(&session->back_lock);
	task = (काष्ठा iscsi_task *)sc->SCp.ptr;
	अगर (!task) अणु
		/*
		 * Raced with completion. Blk layer has taken ownership
		 * so let समयout code complete it now.
		 */
		rc = BLK_EH_DONE;
		spin_unlock(&session->back_lock);
		जाओ करोne;
	पूर्ण
	__iscsi_get_task(task);
	spin_unlock(&session->back_lock);

	अगर (session->state != ISCSI_STATE_LOGGED_IN) अणु
		/*
		 * During shutकरोwn, अगर session is prematurely disconnected,
		 * recovery won't happen and there will be hung cmds. Not
		 * handling cmds would trigger EH, also bad in this हाल.
		 * Instead, handle cmd, allow completion to happen and let
		 * upper layer to deal with the result.
		 */
		अगर (unlikely(प्रणाली_state != SYSTEM_RUNNING)) अणु
			sc->result = DID_NO_CONNECT << 16;
			ISCSI_DBG_EH(session, "sc on shutdown, handled\n");
			rc = BLK_EH_DONE;
			जाओ करोne;
		पूर्ण
		/*
		 * We are probably in the middle of iscsi recovery so let
		 * that complete and handle the error.
		 */
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

	conn = session->leadconn;
	अगर (!conn) अणु
		/* In the middle of shuting करोwn */
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

	/*
	 * If we have sent (at least queued to the network layer) a pdu or
	 * recvd one क्रम the task since the last समयout ask क्रम
	 * more समय. If on the next समयout we have not made progress
	 * we can check अगर it is the task or connection when we send the
	 * nop as a ping.
	 */
	अगर (समय_after(task->last_xfer, task->last_समयout)) अणु
		ISCSI_DBG_EH(session, "Command making progress. Asking "
			     "scsi-ml for more time to complete. "
			     "Last data xfer at %lu. Last timeout was at "
			     "%lu\n.", task->last_xfer, task->last_समयout);
		task->have_checked_conn = false;
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

	अगर (!conn->recv_समयout && !conn->ping_समयout)
		जाओ करोne;
	/*
	 * अगर the ping समयकरोut then we are in the middle of cleaning up
	 * and can let the iscsi eh handle it
	 */
	अगर (iscsi_has_ping_समयd_out(conn)) अणु
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

	spin_lock(&session->back_lock);
	क्रम (i = 0; i < conn->session->cmds_max; i++) अणु
		running_task = conn->session->cmds[i];
		अगर (!running_task->sc || running_task == task ||
		     running_task->state != ISCSI_TASK_RUNNING)
			जारी;

		/*
		 * Only check अगर cmds started beक्रमe this one have made
		 * progress, or this could never fail
		 */
		अगर (समय_after(running_task->sc->jअगरfies_at_alloc,
			       task->sc->jअगरfies_at_alloc))
			जारी;

		अगर (समय_after(running_task->last_xfer, task->last_समयout)) अणु
			/*
			 * This task has not made progress, but a task
			 * started beक्रमe us has transferred data since
			 * we started/last-checked. We could be queueing
			 * too many tasks or the LU is bad.
			 *
			 * If the device is bad the cmds ahead of us on
			 * other devs will complete, and this loop will
			 * eventually fail starting the scsi eh.
			 */
			ISCSI_DBG_EH(session, "Command has not made progress "
				     "but commands ahead of it have. "
				     "Asking scsi-ml for more time to "
				     "complete. Our last xfer vs running task "
				     "last xfer %lu/%lu. Last check %lu.\n",
				     task->last_xfer, running_task->last_xfer,
				     task->last_समयout);
			spin_unlock(&session->back_lock);
			rc = BLK_EH_RESET_TIMER;
			जाओ करोne;
		पूर्ण
	पूर्ण
	spin_unlock(&session->back_lock);

	/* Assumes nop समयout is लघुer than scsi cmd समयout */
	अगर (task->have_checked_conn)
		जाओ करोne;

	/*
	 * Checking the transport alपढ़ोy or nop from a cmd समयout still
	 * running
	 */
	अगर (READ_ONCE(conn->ping_task)) अणु
		task->have_checked_conn = true;
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

	/* Make sure there is a transport check करोne */
	iscsi_send_nopout(conn, शून्य);
	task->have_checked_conn = true;
	rc = BLK_EH_RESET_TIMER;

करोne:
	spin_unlock_bh(&session->frwd_lock);

	अगर (task) अणु
		task->last_समयout = jअगरfies;
		iscsi_put_task(task);
	पूर्ण
	ISCSI_DBG_EH(session, "return %s\n", rc == BLK_EH_RESET_TIMER ?
		     "timer reset" : "shutdown or nh");
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_eh_cmd_समयd_out);

अटल व्योम iscsi_check_transport_समयouts(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_conn *conn = from_समयr(conn, t, transport_समयr);
	काष्ठा iscsi_session *session = conn->session;
	अचिन्हित दीर्घ recv_समयout, next_समयout = 0, last_recv;

	spin_lock(&session->frwd_lock);
	अगर (session->state != ISCSI_STATE_LOGGED_IN)
		जाओ करोne;

	recv_समयout = conn->recv_समयout;
	अगर (!recv_समयout)
		जाओ करोne;

	recv_समयout *= HZ;
	last_recv = conn->last_recv;

	अगर (iscsi_has_ping_समयd_out(conn)) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "ping timeout of %d secs "
				  "expired, recv timeout %d, last rx %lu, "
				  "last ping %lu, now %lu\n",
				  conn->ping_समयout, conn->recv_समयout,
				  last_recv, conn->last_ping, jअगरfies);
		spin_unlock(&session->frwd_lock);
		iscsi_conn_failure(conn, ISCSI_ERR_NOP_TIMEDOUT);
		वापस;
	पूर्ण

	अगर (समय_beक्रमe_eq(last_recv + recv_समयout, jअगरfies)) अणु
		/* send a ping to try to provoke some traffic */
		ISCSI_DBG_CONN(conn, "Sending nopout as ping\n");
		अगर (iscsi_send_nopout(conn, शून्य))
			next_समयout = jअगरfies + (1 * HZ);
		अन्यथा
			next_समयout = conn->last_ping + (conn->ping_समयout * HZ);
	पूर्ण अन्यथा
		next_समयout = last_recv + recv_समयout;

	ISCSI_DBG_CONN(conn, "Setting next tmo %lu\n", next_समयout);
	mod_समयr(&conn->transport_समयr, next_समयout);
करोne:
	spin_unlock(&session->frwd_lock);
पूर्ण

अटल व्योम iscsi_prep_पात_task_pdu(काष्ठा iscsi_task *task,
				      काष्ठा iscsi_पंचांग *hdr)
अणु
	स_रखो(hdr, 0, माप(*hdr));
	hdr->opcode = ISCSI_OP_SCSI_TMFUNC | ISCSI_OP_IMMEDIATE;
	hdr->flags = ISCSI_TM_FUNC_ABORT_TASK & ISCSI_FLAG_TM_FUNC_MASK;
	hdr->flags |= ISCSI_FLAG_CMD_FINAL;
	hdr->lun = task->lun;
	hdr->rtt = task->hdr_itt;
	hdr->refcmdsn = task->cmdsn;
पूर्ण

पूर्णांक iscsi_eh_पात(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_task *task;
	काष्ठा iscsi_पंचांग *hdr;
	पूर्णांक age;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;

	ISCSI_DBG_EH(session, "aborting sc %p\n", sc);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	/*
	 * अगर session was ISCSI_STATE_IN_RECOVERY then we may not have
	 * got the command.
	 */
	अगर (!sc->SCp.ptr) अणु
		ISCSI_DBG_EH(session, "sc never reached iscsi layer or "
				      "it completed.\n");
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		वापस SUCCESS;
	पूर्ण

	/*
	 * If we are not logged in or we have started a new session
	 * then let the host reset code handle this
	 */
	अगर (!session->leadconn || session->state != ISCSI_STATE_LOGGED_IN ||
	    sc->SCp.phase != session->age) अणु
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		ISCSI_DBG_EH(session, "failing abort due to dropped "
				  "session.\n");
		वापस FAILED;
	पूर्ण

	conn = session->leadconn;
	conn->eh_पात_cnt++;
	age = session->age;

	spin_lock(&session->back_lock);
	task = (काष्ठा iscsi_task *)sc->SCp.ptr;
	अगर (!task || !task->sc) अणु
		/* task completed beक्रमe समय out */
		ISCSI_DBG_EH(session, "sc completed while abort in progress\n");

		spin_unlock(&session->back_lock);
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		वापस SUCCESS;
	पूर्ण
	ISCSI_DBG_EH(session, "aborting [sc %p itt 0x%x]\n", sc, task->itt);
	__iscsi_get_task(task);
	spin_unlock(&session->back_lock);

	अगर (task->state == ISCSI_TASK_PENDING) अणु
		fail_scsi_task(task, DID_ABORT);
		जाओ success;
	पूर्ण

	/* only have one पंचांगf outstanding at a समय */
	अगर (conn->पंचांगf_state != TMF_INITIAL)
		जाओ failed;
	conn->पंचांगf_state = TMF_QUEUED;

	hdr = &conn->पंचांगhdr;
	iscsi_prep_पात_task_pdu(task, hdr);

	अगर (iscsi_exec_task_mgmt_fn(conn, hdr, age, session->पात_समयout))
		जाओ failed;

	चयन (conn->पंचांगf_state) अणु
	हाल TMF_SUCCESS:
		spin_unlock_bh(&session->frwd_lock);
		/*
		 * stop tx side inहाल the target had sent a पात rsp but
		 * the initiator was still writing out data.
		 */
		iscsi_suspend_tx(conn);
		/*
		 * we करो not stop the recv side because tarमाला_लो have been
		 * good and have never sent us a successful पंचांगf response
		 * then sent more data क्रम the cmd.
		 */
		spin_lock_bh(&session->frwd_lock);
		fail_scsi_task(task, DID_ABORT);
		conn->पंचांगf_state = TMF_INITIAL;
		स_रखो(hdr, 0, माप(*hdr));
		spin_unlock_bh(&session->frwd_lock);
		iscsi_start_tx(conn);
		जाओ success_unlocked;
	हाल TMF_TIMEDOUT:
		spin_unlock_bh(&session->frwd_lock);
		iscsi_conn_failure(conn, ISCSI_ERR_SCSI_EH_SESSION_RST);
		जाओ failed_unlocked;
	हाल TMF_NOT_FOUND:
		अगर (!sc->SCp.ptr) अणु
			conn->पंचांगf_state = TMF_INITIAL;
			स_रखो(hdr, 0, माप(*hdr));
			/* task completed beक्रमe पंचांगf पात response */
			ISCSI_DBG_EH(session, "sc completed while abort	in "
					      "progress\n");
			जाओ success;
		पूर्ण
		fallthrough;
	शेष:
		conn->पंचांगf_state = TMF_INITIAL;
		जाओ failed;
	पूर्ण

success:
	spin_unlock_bh(&session->frwd_lock);
success_unlocked:
	ISCSI_DBG_EH(session, "abort success [sc %p itt 0x%x]\n",
		     sc, task->itt);
	iscsi_put_task(task);
	mutex_unlock(&session->eh_mutex);
	वापस SUCCESS;

failed:
	spin_unlock_bh(&session->frwd_lock);
failed_unlocked:
	ISCSI_DBG_EH(session, "abort failed [sc %p itt 0x%x]\n", sc,
		     task ? task->itt : 0);
	iscsi_put_task(task);
	mutex_unlock(&session->eh_mutex);
	वापस FAILED;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_eh_पात);

अटल व्योम iscsi_prep_lun_reset_pdu(काष्ठा scsi_cmnd *sc, काष्ठा iscsi_पंचांग *hdr)
अणु
	स_रखो(hdr, 0, माप(*hdr));
	hdr->opcode = ISCSI_OP_SCSI_TMFUNC | ISCSI_OP_IMMEDIATE;
	hdr->flags = ISCSI_TM_FUNC_LOGICAL_UNIT_RESET & ISCSI_FLAG_TM_FUNC_MASK;
	hdr->flags |= ISCSI_FLAG_CMD_FINAL;
	पूर्णांक_to_scsilun(sc->device->lun, &hdr->lun);
	hdr->rtt = RESERVED_ITT;
पूर्ण

पूर्णांक iscsi_eh_device_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_पंचांग *hdr;
	पूर्णांक rc = FAILED;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;

	ISCSI_DBG_EH(session, "LU Reset [sc %p lun %llu]\n", sc,
		     sc->device->lun);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	/*
	 * Just check अगर we are not logged in. We cannot check क्रम
	 * the phase because the reset could come from a ioctl.
	 */
	अगर (!session->leadconn || session->state != ISCSI_STATE_LOGGED_IN)
		जाओ unlock;
	conn = session->leadconn;

	/* only have one पंचांगf outstanding at a समय */
	अगर (conn->पंचांगf_state != TMF_INITIAL)
		जाओ unlock;
	conn->पंचांगf_state = TMF_QUEUED;

	hdr = &conn->पंचांगhdr;
	iscsi_prep_lun_reset_pdu(sc, hdr);

	अगर (iscsi_exec_task_mgmt_fn(conn, hdr, session->age,
				    session->lu_reset_समयout)) अणु
		rc = FAILED;
		जाओ unlock;
	पूर्ण

	चयन (conn->पंचांगf_state) अणु
	हाल TMF_SUCCESS:
		अवरोध;
	हाल TMF_TIMEDOUT:
		spin_unlock_bh(&session->frwd_lock);
		iscsi_conn_failure(conn, ISCSI_ERR_SCSI_EH_SESSION_RST);
		जाओ करोne;
	शेष:
		conn->पंचांगf_state = TMF_INITIAL;
		जाओ unlock;
	पूर्ण

	rc = SUCCESS;
	spin_unlock_bh(&session->frwd_lock);

	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->frwd_lock);
	स_रखो(hdr, 0, माप(*hdr));
	fail_scsi_tasks(conn, sc->device->lun, DID_ERROR);
	conn->पंचांगf_state = TMF_INITIAL;
	spin_unlock_bh(&session->frwd_lock);

	iscsi_start_tx(conn);
	जाओ करोne;

unlock:
	spin_unlock_bh(&session->frwd_lock);
करोne:
	ISCSI_DBG_EH(session, "dev reset result = %s\n",
		     rc == SUCCESS ? "SUCCESS" : "FAILED");
	mutex_unlock(&session->eh_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_eh_device_reset);

व्योम iscsi_session_recovery_समयकरोut(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;

	spin_lock_bh(&session->frwd_lock);
	अगर (session->state != ISCSI_STATE_LOGGED_IN) अणु
		session->state = ISCSI_STATE_RECOVERY_FAILED;
		अगर (session->leadconn)
			wake_up(&session->leadconn->ehरुको);
	पूर्ण
	spin_unlock_bh(&session->frwd_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_recovery_समयकरोut);

/**
 * iscsi_eh_session_reset - drop session and attempt relogin
 * @sc: scsi command
 *
 * This function will रुको क्रम a relogin, session termination from
 * userspace, or a recovery/replacement समयout.
 */
पूर्णांक iscsi_eh_session_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;
	conn = session->leadconn;

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	अगर (session->state == ISCSI_STATE_TERMINATE) अणु
failed:
		ISCSI_DBG_EH(session,
			     "failing session reset: Could not log back into "
			     "%s [age %d]\n", session->targetname,
			     session->age);
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		वापस FAILED;
	पूर्ण

	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);
	/*
	 * we drop the lock here but the leadconn cannot be destoyed जबतक
	 * we are in the scsi eh
	 */
	iscsi_conn_failure(conn, ISCSI_ERR_SCSI_EH_SESSION_RST);

	ISCSI_DBG_EH(session, "wait for relogin\n");
	रुको_event_पूर्णांकerruptible(conn->ehरुको,
				 session->state == ISCSI_STATE_TERMINATE ||
				 session->state == ISCSI_STATE_LOGGED_IN ||
				 session->state == ISCSI_STATE_RECOVERY_FAILED);
	अगर (संकेत_pending(current))
		flush_संकेतs(current);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	अगर (session->state == ISCSI_STATE_LOGGED_IN) अणु
		ISCSI_DBG_EH(session,
			     "session reset succeeded for %s,%s\n",
			     session->targetname, conn->persistent_address);
	पूर्ण अन्यथा
		जाओ failed;
	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);
	वापस SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_eh_session_reset);

अटल व्योम iscsi_prep_tgt_reset_pdu(काष्ठा scsi_cmnd *sc, काष्ठा iscsi_पंचांग *hdr)
अणु
	स_रखो(hdr, 0, माप(*hdr));
	hdr->opcode = ISCSI_OP_SCSI_TMFUNC | ISCSI_OP_IMMEDIATE;
	hdr->flags = ISCSI_TM_FUNC_TARGET_WARM_RESET & ISCSI_FLAG_TM_FUNC_MASK;
	hdr->flags |= ISCSI_FLAG_CMD_FINAL;
	hdr->rtt = RESERVED_ITT;
पूर्ण

/**
 * iscsi_eh_target_reset - reset target
 * @sc: scsi command
 *
 * This will attempt to send a warm target reset.
 */
अटल पूर्णांक iscsi_eh_target_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_पंचांग *hdr;
	पूर्णांक rc = FAILED;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;

	ISCSI_DBG_EH(session, "tgt Reset [sc %p tgt %s]\n", sc,
		     session->targetname);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	/*
	 * Just check अगर we are not logged in. We cannot check क्रम
	 * the phase because the reset could come from a ioctl.
	 */
	अगर (!session->leadconn || session->state != ISCSI_STATE_LOGGED_IN)
		जाओ unlock;
	conn = session->leadconn;

	/* only have one पंचांगf outstanding at a समय */
	अगर (conn->पंचांगf_state != TMF_INITIAL)
		जाओ unlock;
	conn->पंचांगf_state = TMF_QUEUED;

	hdr = &conn->पंचांगhdr;
	iscsi_prep_tgt_reset_pdu(sc, hdr);

	अगर (iscsi_exec_task_mgmt_fn(conn, hdr, session->age,
				    session->tgt_reset_समयout)) अणु
		rc = FAILED;
		जाओ unlock;
	पूर्ण

	चयन (conn->पंचांगf_state) अणु
	हाल TMF_SUCCESS:
		अवरोध;
	हाल TMF_TIMEDOUT:
		spin_unlock_bh(&session->frwd_lock);
		iscsi_conn_failure(conn, ISCSI_ERR_SCSI_EH_SESSION_RST);
		जाओ करोne;
	शेष:
		conn->पंचांगf_state = TMF_INITIAL;
		जाओ unlock;
	पूर्ण

	rc = SUCCESS;
	spin_unlock_bh(&session->frwd_lock);

	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->frwd_lock);
	स_रखो(hdr, 0, माप(*hdr));
	fail_scsi_tasks(conn, -1, DID_ERROR);
	conn->पंचांगf_state = TMF_INITIAL;
	spin_unlock_bh(&session->frwd_lock);

	iscsi_start_tx(conn);
	जाओ करोne;

unlock:
	spin_unlock_bh(&session->frwd_lock);
करोne:
	ISCSI_DBG_EH(session, "tgt %s reset result = %s\n", session->targetname,
		     rc == SUCCESS ? "SUCCESS" : "FAILED");
	mutex_unlock(&session->eh_mutex);
	वापस rc;
पूर्ण

/**
 * iscsi_eh_recover_target - reset target and possibly the session
 * @sc: scsi command
 *
 * This will attempt to send a warm target reset. If that fails,
 * we will escalate to ERL0 session recovery.
 */
पूर्णांक iscsi_eh_recover_target(काष्ठा scsi_cmnd *sc)
अणु
	पूर्णांक rc;

	rc = iscsi_eh_target_reset(sc);
	अगर (rc == FAILED)
		rc = iscsi_eh_session_reset(sc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_eh_recover_target);

/*
 * Pre-allocate a pool of @max items of @item_size. By शेष, the pool
 * should be accessed via kfअगरo_अणुget,putपूर्ण on q->queue.
 * Optionally, the caller can obtain the array of object poपूर्णांकers
 * by passing in a non-शून्य @items poपूर्णांकer
 */
पूर्णांक
iscsi_pool_init(काष्ठा iscsi_pool *q, पूर्णांक max, व्योम ***items, पूर्णांक item_size)
अणु
	पूर्णांक i, num_arrays = 1;

	स_रखो(q, 0, माप(*q));

	q->max = max;

	/* If the user passed an items poपूर्णांकer, he wants a copy of
	 * the array. */
	अगर (items)
		num_arrays++;
	q->pool = kvसुस्मृति(num_arrays * max, माप(व्योम *), GFP_KERNEL);
	अगर (q->pool == शून्य)
		वापस -ENOMEM;

	kfअगरo_init(&q->queue, (व्योम*)q->pool, max * माप(व्योम*));

	क्रम (i = 0; i < max; i++) अणु
		q->pool[i] = kzalloc(item_size, GFP_KERNEL);
		अगर (q->pool[i] == शून्य) अणु
			q->max = i;
			जाओ enomem;
		पूर्ण
		kfअगरo_in(&q->queue, (व्योम*)&q->pool[i], माप(व्योम*));
	पूर्ण

	अगर (items) अणु
		*items = q->pool + max;
		स_नकल(*items, q->pool, max * माप(व्योम *));
	पूर्ण

	वापस 0;

enomem:
	iscsi_pool_मुक्त(q);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_pool_init);

व्योम iscsi_pool_मुक्त(काष्ठा iscsi_pool *q)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < q->max; i++)
		kमुक्त(q->pool[i]);
	kvमुक्त(q->pool);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_pool_मुक्त);

पूर्णांक iscsi_host_get_max_scsi_cmds(काष्ठा Scsi_Host *shost,
				 uपूर्णांक16_t requested_cmds_max)
अणु
	पूर्णांक scsi_cmds, total_cmds = requested_cmds_max;

check:
	अगर (!total_cmds)
		total_cmds = ISCSI_DEF_XMIT_CMDS_MAX;
	/*
	 * The iscsi layer needs some tasks क्रम nop handling and पंचांगfs,
	 * so the cmds_max must at least be greater than ISCSI_MGMT_CMDS_MAX
	 * + 1 command क्रम scsi IO.
	 */
	अगर (total_cmds < ISCSI_TOTAL_CMDS_MIN) अणु
		prपूर्णांकk(KERN_ERR "iscsi: invalid max cmds of %d. Must be a power of two that is at least %d.\n",
		       total_cmds, ISCSI_TOTAL_CMDS_MIN);
		वापस -EINVAL;
	पूर्ण

	अगर (total_cmds > ISCSI_TOTAL_CMDS_MAX) अणु
		prपूर्णांकk(KERN_INFO "iscsi: invalid max cmds of %d. Must be a power of 2 less than or equal to %d. Using %d.\n",
		       requested_cmds_max, ISCSI_TOTAL_CMDS_MAX,
		       ISCSI_TOTAL_CMDS_MAX);
		total_cmds = ISCSI_TOTAL_CMDS_MAX;
	पूर्ण

	अगर (!is_घातer_of_2(total_cmds)) अणु
		total_cmds = roundकरोwn_घात_of_two(total_cmds);
		अगर (total_cmds < ISCSI_TOTAL_CMDS_MIN) अणु
			prपूर्णांकk(KERN_ERR "iscsi: invalid max cmds of %d. Must be a power of 2 greater than %d.\n", requested_cmds_max, ISCSI_TOTAL_CMDS_MIN);
			वापस -EINVAL;
		पूर्ण

		prपूर्णांकk(KERN_INFO "iscsi: invalid max cmds %d. Must be a power of 2. Rounding max cmds down to %d.\n",
		       requested_cmds_max, total_cmds);
	पूर्ण

	scsi_cmds = total_cmds - ISCSI_MGMT_CMDS_MAX;
	अगर (shost->can_queue && scsi_cmds > shost->can_queue) अणु
		total_cmds = shost->can_queue;

		prपूर्णांकk(KERN_INFO "iscsi: requested max cmds %u is higher than driver limit. Using driver limit %u\n",
		       requested_cmds_max, shost->can_queue);
		जाओ check;
	पूर्ण

	वापस scsi_cmds;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_get_max_scsi_cmds);

/**
 * iscsi_host_add - add host to प्रणाली
 * @shost: scsi host
 * @pdev: parent device
 *
 * This should be called by partial offload and software iscsi drivers
 * to add a host to the प्रणाली.
 */
पूर्णांक iscsi_host_add(काष्ठा Scsi_Host *shost, काष्ठा device *pdev)
अणु
	अगर (!shost->can_queue)
		shost->can_queue = ISCSI_DEF_XMIT_CMDS_MAX;

	अगर (!shost->cmd_per_lun)
		shost->cmd_per_lun = ISCSI_DEF_CMD_PER_LUN;

	वापस scsi_add_host(shost, pdev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_add);

/**
 * iscsi_host_alloc - allocate a host and driver data
 * @sht: scsi host ढाँचा
 * @dd_data_size: driver host data size
 * @xmit_can_sleep: bool indicating अगर LLD will queue IO from a work queue
 *
 * This should be called by partial offload and software iscsi drivers.
 * To access the driver specअगरic memory use the iscsi_host_priv() macro.
 */
काष्ठा Scsi_Host *iscsi_host_alloc(काष्ठा scsi_host_ढाँचा *sht,
				   पूर्णांक dd_data_size, bool xmit_can_sleep)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_host *ihost;

	shost = scsi_host_alloc(sht, माप(काष्ठा iscsi_host) + dd_data_size);
	अगर (!shost)
		वापस शून्य;
	ihost = shost_priv(shost);

	अगर (xmit_can_sleep) अणु
		snम_लिखो(ihost->workq_name, माप(ihost->workq_name),
			"iscsi_q_%d", shost->host_no);
		ihost->workq = alloc_workqueue("%s",
			WQ_SYSFS | __WQ_LEGACY | WQ_MEM_RECLAIM | WQ_UNBOUND,
			1, ihost->workq_name);
		अगर (!ihost->workq)
			जाओ मुक्त_host;
	पूर्ण

	spin_lock_init(&ihost->lock);
	ihost->state = ISCSI_HOST_SETUP;
	ihost->num_sessions = 0;
	init_रुकोqueue_head(&ihost->session_removal_wq);
	वापस shost;

मुक्त_host:
	scsi_host_put(shost);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_alloc);

अटल व्योम iscsi_notअगरy_host_हटाओd(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_session_failure(cls_session->dd_data, ISCSI_ERR_INVALID_HOST);
पूर्ण

/**
 * iscsi_host_हटाओ - हटाओ host and sessions
 * @shost: scsi host
 *
 * If there are any sessions left, this will initiate the removal and रुको
 * क्रम the completion.
 */
व्योम iscsi_host_हटाओ(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ihost->lock, flags);
	ihost->state = ISCSI_HOST_REMOVED;
	spin_unlock_irqrestore(&ihost->lock, flags);

	iscsi_host_क्रम_each_session(shost, iscsi_notअगरy_host_हटाओd);
	रुको_event_पूर्णांकerruptible(ihost->session_removal_wq,
				 ihost->num_sessions == 0);
	अगर (संकेत_pending(current))
		flush_संकेतs(current);

	scsi_हटाओ_host(shost);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_हटाओ);

व्योम iscsi_host_मुक्त(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);

	अगर (ihost->workq)
		destroy_workqueue(ihost->workq);

	kमुक्त(ihost->netdev);
	kमुक्त(ihost->hwaddress);
	kमुक्त(ihost->initiatorname);
	scsi_host_put(shost);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_मुक्त);

अटल व्योम iscsi_host_dec_session_cnt(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);
	अचिन्हित दीर्घ flags;

	shost = scsi_host_get(shost);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "Invalid state. Cannot notify host removal "
		      "of session teardown event because host already "
		      "removed.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&ihost->lock, flags);
	ihost->num_sessions--;
	अगर (ihost->num_sessions == 0)
		wake_up(&ihost->session_removal_wq);
	spin_unlock_irqrestore(&ihost->lock, flags);
	scsi_host_put(shost);
पूर्ण

/**
 * iscsi_session_setup - create iscsi cls session and host and session
 * @iscsit: iscsi transport ढाँचा
 * @shost: scsi host
 * @cmds_max: session can queue
 * @dd_size: निजी driver data size, added to session allocation size
 * @cmd_task_size: LLD task निजी data size
 * @initial_cmdsn: initial CmdSN
 * @id: target ID to add to this session
 *
 * This can be used by software iscsi_transports that allocate
 * a session per scsi host.
 *
 * Callers should set cmds_max to the largest total numer (mgmt + scsi) of
 * tasks they support. The iscsi layer reserves ISCSI_MGMT_CMDS_MAX tasks
 * क्रम nop handling and login/logout requests.
 */
काष्ठा iscsi_cls_session *
iscsi_session_setup(काष्ठा iscsi_transport *iscsit, काष्ठा Scsi_Host *shost,
		    uपूर्णांक16_t cmds_max, पूर्णांक dd_size, पूर्णांक cmd_task_size,
		    uपूर्णांक32_t initial_cmdsn, अचिन्हित पूर्णांक id)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_cls_session *cls_session;
	पूर्णांक cmd_i, scsi_cmds;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ihost->lock, flags);
	अगर (ihost->state == ISCSI_HOST_REMOVED) अणु
		spin_unlock_irqrestore(&ihost->lock, flags);
		वापस शून्य;
	पूर्ण
	ihost->num_sessions++;
	spin_unlock_irqrestore(&ihost->lock, flags);

	scsi_cmds = iscsi_host_get_max_scsi_cmds(shost, cmds_max);
	अगर (scsi_cmds < 0)
		जाओ dec_session_count;

	cls_session = iscsi_alloc_session(shost, iscsit,
					  माप(काष्ठा iscsi_session) +
					  dd_size);
	अगर (!cls_session)
		जाओ dec_session_count;
	session = cls_session->dd_data;
	session->cls_session = cls_session;
	session->host = shost;
	session->state = ISCSI_STATE_FREE;
	session->fast_पात = 1;
	session->tgt_reset_समयout = 30;
	session->lu_reset_समयout = 15;
	session->पात_समयout = 10;
	session->scsi_cmds_max = scsi_cmds;
	session->cmds_max = scsi_cmds + ISCSI_MGMT_CMDS_MAX;
	session->queued_cmdsn = session->cmdsn = initial_cmdsn;
	session->exp_cmdsn = initial_cmdsn + 1;
	session->max_cmdsn = initial_cmdsn + 1;
	session->max_r2t = 1;
	session->tt = iscsit;
	session->dd_data = cls_session->dd_data + माप(*session);

	mutex_init(&session->eh_mutex);
	spin_lock_init(&session->frwd_lock);
	spin_lock_init(&session->back_lock);

	/* initialize SCSI PDU commands pool */
	अगर (iscsi_pool_init(&session->cmdpool, session->cmds_max,
			    (व्योम***)&session->cmds,
			    cmd_task_size + माप(काष्ठा iscsi_task)))
		जाओ cmdpool_alloc_fail;

	/* pre-क्रमmat cmds pool with ITT */
	क्रम (cmd_i = 0; cmd_i < session->cmds_max; cmd_i++) अणु
		काष्ठा iscsi_task *task = session->cmds[cmd_i];

		अगर (cmd_task_size)
			task->dd_data = &task[1];
		task->itt = cmd_i;
		task->state = ISCSI_TASK_FREE;
		INIT_LIST_HEAD(&task->running);
	पूर्ण

	अगर (!try_module_get(iscsit->owner))
		जाओ module_get_fail;

	अगर (iscsi_add_session(cls_session, id))
		जाओ cls_session_fail;

	वापस cls_session;

cls_session_fail:
	module_put(iscsit->owner);
module_get_fail:
	iscsi_pool_मुक्त(&session->cmdpool);
cmdpool_alloc_fail:
	iscsi_मुक्त_session(cls_session);
dec_session_count:
	iscsi_host_dec_session_cnt(shost);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_setup);

/**
 * iscsi_session_tearकरोwn - destroy session, host, and cls_session
 * @cls_session: iscsi session
 */
व्योम iscsi_session_tearकरोwn(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा module *owner = cls_session->transport->owner;
	काष्ठा Scsi_Host *shost = session->host;

	iscsi_pool_मुक्त(&session->cmdpool);

	iscsi_हटाओ_session(cls_session);

	kमुक्त(session->password);
	kमुक्त(session->password_in);
	kमुक्त(session->username);
	kमुक्त(session->username_in);
	kमुक्त(session->targetname);
	kमुक्त(session->targetalias);
	kमुक्त(session->initiatorname);
	kमुक्त(session->boot_root);
	kमुक्त(session->boot_nic);
	kमुक्त(session->boot_target);
	kमुक्त(session->अगरacename);
	kमुक्त(session->portal_type);
	kमुक्त(session->discovery_parent_type);

	iscsi_मुक्त_session(cls_session);

	iscsi_host_dec_session_cnt(shost);
	module_put(owner);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_tearकरोwn);

/**
 * iscsi_conn_setup - create iscsi_cls_conn and iscsi_conn
 * @cls_session: iscsi_cls_session
 * @dd_size: निजी driver data size
 * @conn_idx: cid
 */
काष्ठा iscsi_cls_conn *
iscsi_conn_setup(काष्ठा iscsi_cls_session *cls_session, पूर्णांक dd_size,
		 uपूर्णांक32_t conn_idx)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_cls_conn *cls_conn;
	अक्षर *data;

	cls_conn = iscsi_create_conn(cls_session, माप(*conn) + dd_size,
				     conn_idx);
	अगर (!cls_conn)
		वापस शून्य;
	conn = cls_conn->dd_data;
	स_रखो(conn, 0, माप(*conn) + dd_size);

	conn->dd_data = cls_conn->dd_data + माप(*conn);
	conn->session = session;
	conn->cls_conn = cls_conn;
	conn->c_stage = ISCSI_CONN_INITIAL_STAGE;
	conn->id = conn_idx;
	conn->exp_statsn = 0;
	conn->पंचांगf_state = TMF_INITIAL;

	समयr_setup(&conn->transport_समयr, iscsi_check_transport_समयouts, 0);

	INIT_LIST_HEAD(&conn->mgmtqueue);
	INIT_LIST_HEAD(&conn->cmdqueue);
	INIT_LIST_HEAD(&conn->requeue);
	INIT_WORK(&conn->xmitwork, iscsi_xmitworker);

	/* allocate login_task used क्रम the login/text sequences */
	spin_lock_bh(&session->frwd_lock);
	अगर (!kfअगरo_out(&session->cmdpool.queue,
                         (व्योम*)&conn->login_task,
			 माप(व्योम*))) अणु
		spin_unlock_bh(&session->frwd_lock);
		जाओ login_task_alloc_fail;
	पूर्ण
	spin_unlock_bh(&session->frwd_lock);

	data = (अक्षर *) __get_मुक्त_pages(GFP_KERNEL,
					 get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	अगर (!data)
		जाओ login_task_data_alloc_fail;
	conn->login_task->data = conn->data = data;

	समयr_setup(&conn->पंचांगf_समयr, iscsi_पंचांगf_समयकरोut, 0);
	init_रुकोqueue_head(&conn->ehरुको);

	वापस cls_conn;

login_task_data_alloc_fail:
	kfअगरo_in(&session->cmdpool.queue, (व्योम*)&conn->login_task,
		    माप(व्योम*));
login_task_alloc_fail:
	iscsi_destroy_conn(cls_conn);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_setup);

/**
 * iscsi_conn_tearकरोwn - tearकरोwn iscsi connection
 * @cls_conn: iscsi class connection
 *
 * TODO: we may need to make this पूर्णांकo a two step process
 * like scsi-mls हटाओ + put host
 */
व्योम iscsi_conn_tearकरोwn(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;

	del_समयr_sync(&conn->transport_समयr);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	conn->c_stage = ISCSI_CONN_CLEANUP_WAIT;
	अगर (session->leadconn == conn) अणु
		/*
		 * leading connection? then give up on recovery.
		 */
		session->state = ISCSI_STATE_TERMINATE;
		wake_up(&conn->ehरुको);
	पूर्ण
	spin_unlock_bh(&session->frwd_lock);

	/* flush queued up work because we मुक्त the connection below */
	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->frwd_lock);
	मुक्त_pages((अचिन्हित दीर्घ) conn->data,
		   get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	kमुक्त(conn->persistent_address);
	kमुक्त(conn->local_ipaddr);
	/* regular RX path uses back_lock */
	spin_lock_bh(&session->back_lock);
	kfअगरo_in(&session->cmdpool.queue, (व्योम*)&conn->login_task,
		    माप(व्योम*));
	spin_unlock_bh(&session->back_lock);
	अगर (session->leadconn == conn)
		session->leadconn = शून्य;
	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);

	iscsi_destroy_conn(cls_conn);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_tearकरोwn);

पूर्णांक iscsi_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;

	अगर (!session) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "can't start unbound connection\n");
		वापस -EPERM;
	पूर्ण

	अगर ((session->imm_data_en || !session->initial_r2t_en) &&
	     session->first_burst > session->max_burst) अणु
		iscsi_conn_prपूर्णांकk(KERN_INFO, conn, "invalid burst lengths: "
				  "first_burst %d max_burst %d\n",
				  session->first_burst, session->max_burst);
		वापस -EINVAL;
	पूर्ण

	अगर (conn->ping_समयout && !conn->recv_समयout) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "invalid recv timeout of "
				  "zero. Using 5 seconds\n.");
		conn->recv_समयout = 5;
	पूर्ण

	अगर (conn->recv_समयout && !conn->ping_समयout) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "invalid ping timeout of "
				  "zero. Using 5 seconds.\n");
		conn->ping_समयout = 5;
	पूर्ण

	spin_lock_bh(&session->frwd_lock);
	conn->c_stage = ISCSI_CONN_STARTED;
	session->state = ISCSI_STATE_LOGGED_IN;
	session->queued_cmdsn = session->cmdsn;

	conn->last_recv = jअगरfies;
	conn->last_ping = jअगरfies;
	अगर (conn->recv_समयout && conn->ping_समयout)
		mod_समयr(&conn->transport_समयr,
			  jअगरfies + (conn->recv_समयout * HZ));

	चयन(conn->stop_stage) अणु
	हाल STOP_CONN_RECOVER:
		/*
		 * unblock eh_पात() अगर it is blocked. re-try all
		 * commands after successful recovery
		 */
		conn->stop_stage = 0;
		conn->पंचांगf_state = TMF_INITIAL;
		session->age++;
		अगर (session->age == 16)
			session->age = 0;
		अवरोध;
	हाल STOP_CONN_TERM:
		conn->stop_stage = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_bh(&session->frwd_lock);

	iscsi_unblock_session(session->cls_session);
	wake_up(&conn->ehरुको);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_start);

अटल व्योम
fail_mgmt_tasks(काष्ठा iscsi_session *session, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_task *task;
	पूर्णांक i, state;

	क्रम (i = 0; i < conn->session->cmds_max; i++) अणु
		task = conn->session->cmds[i];
		अगर (task->sc)
			जारी;

		अगर (task->state == ISCSI_TASK_FREE)
			जारी;

		ISCSI_DBG_SESSION(conn->session,
				  "failing mgmt itt 0x%x state %d\n",
				  task->itt, task->state);

		spin_lock_bh(&session->back_lock);
		अगर (cleanup_queued_task(task)) अणु
			spin_unlock_bh(&session->back_lock);
			जारी;
		पूर्ण

		state = ISCSI_TASK_ABRT_SESS_RECOV;
		अगर (task->state == ISCSI_TASK_PENDING)
			state = ISCSI_TASK_COMPLETED;
		iscsi_complete_task(task, state);
		spin_unlock_bh(&session->back_lock);
	पूर्ण
पूर्ण

व्योम iscsi_conn_stop(काष्ठा iscsi_cls_conn *cls_conn, पूर्णांक flag)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक old_stop_stage;

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	अगर (conn->stop_stage == STOP_CONN_TERM) अणु
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		वापस;
	पूर्ण

	/*
	 * When this is called क्रम the in_login state, we only want to clean
	 * up the login task and connection. We करो not need to block and set
	 * the recovery state again
	 */
	अगर (flag == STOP_CONN_TERM)
		session->state = ISCSI_STATE_TERMINATE;
	अन्यथा अगर (conn->stop_stage != STOP_CONN_RECOVER)
		session->state = ISCSI_STATE_IN_RECOVERY;

	old_stop_stage = conn->stop_stage;
	conn->stop_stage = flag;
	spin_unlock_bh(&session->frwd_lock);

	del_समयr_sync(&conn->transport_समयr);
	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->frwd_lock);
	conn->c_stage = ISCSI_CONN_STOPPED;
	spin_unlock_bh(&session->frwd_lock);

	/*
	 * क्रम connection level recovery we should not calculate
	 * header digest. conn->hdr_size used क्रम optimization
	 * in hdr_extract() and will be re-negotiated at
	 * set_param() समय.
	 */
	अगर (flag == STOP_CONN_RECOVER) अणु
		conn->hdrdgst_en = 0;
		conn->datadgst_en = 0;
		अगर (session->state == ISCSI_STATE_IN_RECOVERY &&
		    old_stop_stage != STOP_CONN_RECOVER) अणु
			ISCSI_DBG_SESSION(session, "blocking session\n");
			iscsi_block_session(session->cls_session);
		पूर्ण
	पूर्ण

	/*
	 * flush queues.
	 */
	spin_lock_bh(&session->frwd_lock);
	fail_scsi_tasks(conn, -1, DID_TRANSPORT_DISRUPTED);
	fail_mgmt_tasks(session, conn);
	स_रखो(&conn->पंचांगhdr, 0, माप(conn->पंचांगhdr));
	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_stop);

पूर्णांक iscsi_conn_bind(काष्ठा iscsi_cls_session *cls_session,
		    काष्ठा iscsi_cls_conn *cls_conn, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;

	spin_lock_bh(&session->frwd_lock);
	अगर (is_leading)
		session->leadconn = conn;
	spin_unlock_bh(&session->frwd_lock);

	/*
	 * The target could have reduced it's winकरोw size between logins, so
	 * we have to reset max/exp cmdsn so we can see the new values.
	 */
	spin_lock_bh(&session->back_lock);
	session->max_cmdsn = session->exp_cmdsn = session->cmdsn + 1;
	spin_unlock_bh(&session->back_lock);
	/*
	 * Unblock xmitworker(), Login Phase will pass through.
	 */
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_bind);

पूर्णांक iscsi_चयन_str_param(अक्षर **param, अक्षर *new_val_buf)
अणु
	अक्षर *new_val;

	अगर (*param) अणु
		अगर (!म_भेद(*param, new_val_buf))
			वापस 0;
	पूर्ण

	new_val = kstrdup(new_val_buf, GFP_NOIO);
	अगर (!new_val)
		वापस -ENOMEM;

	kमुक्त(*param);
	*param = new_val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_चयन_str_param);

पूर्णांक iscsi_set_param(काष्ठा iscsi_cls_conn *cls_conn,
		    क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;
	पूर्णांक val;

	चयन(param) अणु
	हाल ISCSI_PARAM_FAST_ABORT:
		माला_पूछो(buf, "%d", &session->fast_पात);
		अवरोध;
	हाल ISCSI_PARAM_ABORT_TMO:
		माला_पूछो(buf, "%d", &session->पात_समयout);
		अवरोध;
	हाल ISCSI_PARAM_LU_RESET_TMO:
		माला_पूछो(buf, "%d", &session->lu_reset_समयout);
		अवरोध;
	हाल ISCSI_PARAM_TGT_RESET_TMO:
		माला_पूछो(buf, "%d", &session->tgt_reset_समयout);
		अवरोध;
	हाल ISCSI_PARAM_PING_TMO:
		माला_पूछो(buf, "%d", &conn->ping_समयout);
		अवरोध;
	हाल ISCSI_PARAM_RECV_TMO:
		माला_पूछो(buf, "%d", &conn->recv_समयout);
		अवरोध;
	हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		माला_पूछो(buf, "%d", &conn->max_recv_dlength);
		अवरोध;
	हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		माला_पूछो(buf, "%d", &conn->max_xmit_dlength);
		अवरोध;
	हाल ISCSI_PARAM_HDRDGST_EN:
		माला_पूछो(buf, "%d", &conn->hdrdgst_en);
		अवरोध;
	हाल ISCSI_PARAM_DATADGST_EN:
		माला_पूछो(buf, "%d", &conn->datadgst_en);
		अवरोध;
	हाल ISCSI_PARAM_INITIAL_R2T_EN:
		माला_पूछो(buf, "%d", &session->initial_r2t_en);
		अवरोध;
	हाल ISCSI_PARAM_MAX_R2T:
		माला_पूछो(buf, "%hu", &session->max_r2t);
		अवरोध;
	हाल ISCSI_PARAM_IMM_DATA_EN:
		माला_पूछो(buf, "%d", &session->imm_data_en);
		अवरोध;
	हाल ISCSI_PARAM_FIRST_BURST:
		माला_पूछो(buf, "%d", &session->first_burst);
		अवरोध;
	हाल ISCSI_PARAM_MAX_BURST:
		माला_पूछो(buf, "%d", &session->max_burst);
		अवरोध;
	हाल ISCSI_PARAM_PDU_INORDER_EN:
		माला_पूछो(buf, "%d", &session->pdu_inorder_en);
		अवरोध;
	हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		माला_पूछो(buf, "%d", &session->dataseq_inorder_en);
		अवरोध;
	हाल ISCSI_PARAM_ERL:
		माला_पूछो(buf, "%d", &session->erl);
		अवरोध;
	हाल ISCSI_PARAM_EXP_STATSN:
		माला_पूछो(buf, "%u", &conn->exp_statsn);
		अवरोध;
	हाल ISCSI_PARAM_USERNAME:
		वापस iscsi_चयन_str_param(&session->username, buf);
	हाल ISCSI_PARAM_USERNAME_IN:
		वापस iscsi_चयन_str_param(&session->username_in, buf);
	हाल ISCSI_PARAM_PASSWORD:
		वापस iscsi_चयन_str_param(&session->password, buf);
	हाल ISCSI_PARAM_PASSWORD_IN:
		वापस iscsi_चयन_str_param(&session->password_in, buf);
	हाल ISCSI_PARAM_TARGET_NAME:
		वापस iscsi_चयन_str_param(&session->targetname, buf);
	हाल ISCSI_PARAM_TARGET_ALIAS:
		वापस iscsi_चयन_str_param(&session->targetalias, buf);
	हाल ISCSI_PARAM_TPGT:
		माला_पूछो(buf, "%d", &session->tpgt);
		अवरोध;
	हाल ISCSI_PARAM_PERSISTENT_PORT:
		माला_पूछो(buf, "%d", &conn->persistent_port);
		अवरोध;
	हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		वापस iscsi_चयन_str_param(&conn->persistent_address, buf);
	हाल ISCSI_PARAM_IFACE_NAME:
		वापस iscsi_चयन_str_param(&session->अगरacename, buf);
	हाल ISCSI_PARAM_INITIATOR_NAME:
		वापस iscsi_चयन_str_param(&session->initiatorname, buf);
	हाल ISCSI_PARAM_BOOT_ROOT:
		वापस iscsi_चयन_str_param(&session->boot_root, buf);
	हाल ISCSI_PARAM_BOOT_NIC:
		वापस iscsi_चयन_str_param(&session->boot_nic, buf);
	हाल ISCSI_PARAM_BOOT_TARGET:
		वापस iscsi_चयन_str_param(&session->boot_target, buf);
	हाल ISCSI_PARAM_PORTAL_TYPE:
		वापस iscsi_चयन_str_param(&session->portal_type, buf);
	हाल ISCSI_PARAM_DISCOVERY_PARENT_TYPE:
		वापस iscsi_चयन_str_param(&session->discovery_parent_type,
					      buf);
	हाल ISCSI_PARAM_DISCOVERY_SESS:
		माला_पूछो(buf, "%d", &val);
		session->discovery_sess = !!val;
		अवरोध;
	हाल ISCSI_PARAM_LOCAL_IPADDR:
		वापस iscsi_चयन_str_param(&conn->local_ipaddr, buf);
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_set_param);

पूर्णांक iscsi_session_get_param(काष्ठा iscsi_cls_session *cls_session,
			    क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	पूर्णांक len;

	चयन(param) अणु
	हाल ISCSI_PARAM_FAST_ABORT:
		len = sysfs_emit(buf, "%d\n", session->fast_पात);
		अवरोध;
	हाल ISCSI_PARAM_ABORT_TMO:
		len = sysfs_emit(buf, "%d\n", session->पात_समयout);
		अवरोध;
	हाल ISCSI_PARAM_LU_RESET_TMO:
		len = sysfs_emit(buf, "%d\n", session->lu_reset_समयout);
		अवरोध;
	हाल ISCSI_PARAM_TGT_RESET_TMO:
		len = sysfs_emit(buf, "%d\n", session->tgt_reset_समयout);
		अवरोध;
	हाल ISCSI_PARAM_INITIAL_R2T_EN:
		len = sysfs_emit(buf, "%d\n", session->initial_r2t_en);
		अवरोध;
	हाल ISCSI_PARAM_MAX_R2T:
		len = sysfs_emit(buf, "%hu\n", session->max_r2t);
		अवरोध;
	हाल ISCSI_PARAM_IMM_DATA_EN:
		len = sysfs_emit(buf, "%d\n", session->imm_data_en);
		अवरोध;
	हाल ISCSI_PARAM_FIRST_BURST:
		len = sysfs_emit(buf, "%u\n", session->first_burst);
		अवरोध;
	हाल ISCSI_PARAM_MAX_BURST:
		len = sysfs_emit(buf, "%u\n", session->max_burst);
		अवरोध;
	हाल ISCSI_PARAM_PDU_INORDER_EN:
		len = sysfs_emit(buf, "%d\n", session->pdu_inorder_en);
		अवरोध;
	हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		len = sysfs_emit(buf, "%d\n", session->dataseq_inorder_en);
		अवरोध;
	हाल ISCSI_PARAM_DEF_TASKMGMT_TMO:
		len = sysfs_emit(buf, "%d\n", session->def_taskmgmt_पंचांगo);
		अवरोध;
	हाल ISCSI_PARAM_ERL:
		len = sysfs_emit(buf, "%d\n", session->erl);
		अवरोध;
	हाल ISCSI_PARAM_TARGET_NAME:
		len = sysfs_emit(buf, "%s\n", session->targetname);
		अवरोध;
	हाल ISCSI_PARAM_TARGET_ALIAS:
		len = sysfs_emit(buf, "%s\n", session->targetalias);
		अवरोध;
	हाल ISCSI_PARAM_TPGT:
		len = sysfs_emit(buf, "%d\n", session->tpgt);
		अवरोध;
	हाल ISCSI_PARAM_USERNAME:
		len = sysfs_emit(buf, "%s\n", session->username);
		अवरोध;
	हाल ISCSI_PARAM_USERNAME_IN:
		len = sysfs_emit(buf, "%s\n", session->username_in);
		अवरोध;
	हाल ISCSI_PARAM_PASSWORD:
		len = sysfs_emit(buf, "%s\n", session->password);
		अवरोध;
	हाल ISCSI_PARAM_PASSWORD_IN:
		len = sysfs_emit(buf, "%s\n", session->password_in);
		अवरोध;
	हाल ISCSI_PARAM_IFACE_NAME:
		len = sysfs_emit(buf, "%s\n", session->अगरacename);
		अवरोध;
	हाल ISCSI_PARAM_INITIATOR_NAME:
		len = sysfs_emit(buf, "%s\n", session->initiatorname);
		अवरोध;
	हाल ISCSI_PARAM_BOOT_ROOT:
		len = sysfs_emit(buf, "%s\n", session->boot_root);
		अवरोध;
	हाल ISCSI_PARAM_BOOT_NIC:
		len = sysfs_emit(buf, "%s\n", session->boot_nic);
		अवरोध;
	हाल ISCSI_PARAM_BOOT_TARGET:
		len = sysfs_emit(buf, "%s\n", session->boot_target);
		अवरोध;
	हाल ISCSI_PARAM_AUTO_SND_TGT_DISABLE:
		len = sysfs_emit(buf, "%u\n", session->स्वतः_snd_tgt_disable);
		अवरोध;
	हाल ISCSI_PARAM_DISCOVERY_SESS:
		len = sysfs_emit(buf, "%u\n", session->discovery_sess);
		अवरोध;
	हाल ISCSI_PARAM_PORTAL_TYPE:
		len = sysfs_emit(buf, "%s\n", session->portal_type);
		अवरोध;
	हाल ISCSI_PARAM_CHAP_AUTH_EN:
		len = sysfs_emit(buf, "%u\n", session->chap_auth_en);
		अवरोध;
	हाल ISCSI_PARAM_DISCOVERY_LOGOUT_EN:
		len = sysfs_emit(buf, "%u\n", session->discovery_logout_en);
		अवरोध;
	हाल ISCSI_PARAM_BIDI_CHAP_EN:
		len = sysfs_emit(buf, "%u\n", session->bidi_chap_en);
		अवरोध;
	हाल ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL:
		len = sysfs_emit(buf, "%u\n", session->discovery_auth_optional);
		अवरोध;
	हाल ISCSI_PARAM_DEF_TIME2WAIT:
		len = sysfs_emit(buf, "%d\n", session->समय2रुको);
		अवरोध;
	हाल ISCSI_PARAM_DEF_TIME2RETAIN:
		len = sysfs_emit(buf, "%d\n", session->समय2retain);
		अवरोध;
	हाल ISCSI_PARAM_TSID:
		len = sysfs_emit(buf, "%u\n", session->tsid);
		अवरोध;
	हाल ISCSI_PARAM_ISID:
		len = sysfs_emit(buf, "%02x%02x%02x%02x%02x%02x\n",
			      session->isid[0], session->isid[1],
			      session->isid[2], session->isid[3],
			      session->isid[4], session->isid[5]);
		अवरोध;
	हाल ISCSI_PARAM_DISCOVERY_PARENT_IDX:
		len = sysfs_emit(buf, "%u\n", session->discovery_parent_idx);
		अवरोध;
	हाल ISCSI_PARAM_DISCOVERY_PARENT_TYPE:
		अगर (session->discovery_parent_type)
			len = sysfs_emit(buf, "%s\n",
				      session->discovery_parent_type);
		अन्यथा
			len = sysfs_emit(buf, "\n");
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_get_param);

पूर्णांक iscsi_conn_get_addr_param(काष्ठा sockaddr_storage *addr,
			      क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा sockaddr_in6 *sin6 = शून्य;
	काष्ठा sockaddr_in *sin = शून्य;
	पूर्णांक len;

	चयन (addr->ss_family) अणु
	हाल AF_INET:
		sin = (काष्ठा sockaddr_in *)addr;
		अवरोध;
	हाल AF_INET6:
		sin6 = (काष्ठा sockaddr_in6 *)addr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_ADDRESS:
	हाल ISCSI_HOST_PARAM_IPADDRESS:
		अगर (sin)
			len = sysfs_emit(buf, "%pI4\n", &sin->sin_addr.s_addr);
		अन्यथा
			len = sysfs_emit(buf, "%pI6\n", &sin6->sin6_addr);
		अवरोध;
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_LOCAL_PORT:
		अगर (sin)
			len = sysfs_emit(buf, "%hu\n", be16_to_cpu(sin->sin_port));
		अन्यथा
			len = sysfs_emit(buf, "%hu\n",
				      be16_to_cpu(sin6->sin6_port));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_get_addr_param);

पूर्णांक iscsi_conn_get_param(काष्ठा iscsi_cls_conn *cls_conn,
			 क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	पूर्णांक len;

	चयन(param) अणु
	हाल ISCSI_PARAM_PING_TMO:
		len = sysfs_emit(buf, "%u\n", conn->ping_समयout);
		अवरोध;
	हाल ISCSI_PARAM_RECV_TMO:
		len = sysfs_emit(buf, "%u\n", conn->recv_समयout);
		अवरोध;
	हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		len = sysfs_emit(buf, "%u\n", conn->max_recv_dlength);
		अवरोध;
	हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		len = sysfs_emit(buf, "%u\n", conn->max_xmit_dlength);
		अवरोध;
	हाल ISCSI_PARAM_HDRDGST_EN:
		len = sysfs_emit(buf, "%d\n", conn->hdrdgst_en);
		अवरोध;
	हाल ISCSI_PARAM_DATADGST_EN:
		len = sysfs_emit(buf, "%d\n", conn->datadgst_en);
		अवरोध;
	हाल ISCSI_PARAM_IFMARKER_EN:
		len = sysfs_emit(buf, "%d\n", conn->अगरmarker_en);
		अवरोध;
	हाल ISCSI_PARAM_OFMARKER_EN:
		len = sysfs_emit(buf, "%d\n", conn->ofmarker_en);
		अवरोध;
	हाल ISCSI_PARAM_EXP_STATSN:
		len = sysfs_emit(buf, "%u\n", conn->exp_statsn);
		अवरोध;
	हाल ISCSI_PARAM_PERSISTENT_PORT:
		len = sysfs_emit(buf, "%d\n", conn->persistent_port);
		अवरोध;
	हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		len = sysfs_emit(buf, "%s\n", conn->persistent_address);
		अवरोध;
	हाल ISCSI_PARAM_STATSN:
		len = sysfs_emit(buf, "%u\n", conn->statsn);
		अवरोध;
	हाल ISCSI_PARAM_MAX_SEGMENT_SIZE:
		len = sysfs_emit(buf, "%u\n", conn->max_segment_size);
		अवरोध;
	हाल ISCSI_PARAM_KEEPALIVE_TMO:
		len = sysfs_emit(buf, "%u\n", conn->keepalive_पंचांगo);
		अवरोध;
	हाल ISCSI_PARAM_LOCAL_PORT:
		len = sysfs_emit(buf, "%u\n", conn->local_port);
		अवरोध;
	हाल ISCSI_PARAM_TCP_TIMESTAMP_STAT:
		len = sysfs_emit(buf, "%u\n", conn->tcp_बारtamp_stat);
		अवरोध;
	हाल ISCSI_PARAM_TCP_NAGLE_DISABLE:
		len = sysfs_emit(buf, "%u\n", conn->tcp_nagle_disable);
		अवरोध;
	हाल ISCSI_PARAM_TCP_WSF_DISABLE:
		len = sysfs_emit(buf, "%u\n", conn->tcp_wsf_disable);
		अवरोध;
	हाल ISCSI_PARAM_TCP_TIMER_SCALE:
		len = sysfs_emit(buf, "%u\n", conn->tcp_समयr_scale);
		अवरोध;
	हाल ISCSI_PARAM_TCP_TIMESTAMP_EN:
		len = sysfs_emit(buf, "%u\n", conn->tcp_बारtamp_en);
		अवरोध;
	हाल ISCSI_PARAM_IP_FRAGMENT_DISABLE:
		len = sysfs_emit(buf, "%u\n", conn->fragment_disable);
		अवरोध;
	हाल ISCSI_PARAM_IPV4_TOS:
		len = sysfs_emit(buf, "%u\n", conn->ipv4_tos);
		अवरोध;
	हाल ISCSI_PARAM_IPV6_TC:
		len = sysfs_emit(buf, "%u\n", conn->ipv6_traffic_class);
		अवरोध;
	हाल ISCSI_PARAM_IPV6_FLOW_LABEL:
		len = sysfs_emit(buf, "%u\n", conn->ipv6_flow_label);
		अवरोध;
	हाल ISCSI_PARAM_IS_FW_ASSIGNED_IPV6:
		len = sysfs_emit(buf, "%u\n", conn->is_fw_asचिन्हित_ipv6);
		अवरोध;
	हाल ISCSI_PARAM_TCP_XMIT_WSF:
		len = sysfs_emit(buf, "%u\n", conn->tcp_xmit_wsf);
		अवरोध;
	हाल ISCSI_PARAM_TCP_RECV_WSF:
		len = sysfs_emit(buf, "%u\n", conn->tcp_recv_wsf);
		अवरोध;
	हाल ISCSI_PARAM_LOCAL_IPADDR:
		len = sysfs_emit(buf, "%s\n", conn->local_ipaddr);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_get_param);

पूर्णांक iscsi_host_get_param(काष्ठा Scsi_Host *shost, क्रमागत iscsi_host_param param,
			 अक्षर *buf)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);
	पूर्णांक len;

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		len = sysfs_emit(buf, "%s\n", ihost->netdev);
		अवरोध;
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_emit(buf, "%s\n", ihost->hwaddress);
		अवरोध;
	हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		len = sysfs_emit(buf, "%s\n", ihost->initiatorname);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_get_param);

पूर्णांक iscsi_host_set_param(काष्ठा Scsi_Host *shost, क्रमागत iscsi_host_param param,
			 अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा iscsi_host *ihost = shost_priv(shost);

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		वापस iscsi_चयन_str_param(&ihost->netdev, buf);
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		वापस iscsi_चयन_str_param(&ihost->hwaddress, buf);
	हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		वापस iscsi_चयन_str_param(&ihost->initiatorname, buf);
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_set_param);

MODULE_AUTHOR("Mike Christie");
MODULE_DESCRIPTION("iSCSI library functions");
MODULE_LICENSE("GPL");
