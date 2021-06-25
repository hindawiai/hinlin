<शैली गुरु>
/* bnx2i_hwi.c: QLogic NetXtreme II iSCSI driver.
 *
 * Copyright (c) 2006 - 2013 Broadcom Corporation
 * Copyright (c) 2007, 2008 Red Hat, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mike Christie
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */

#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/libiscsi.h>
#समावेश "bnx2i.h"

DECLARE_PER_CPU(काष्ठा bnx2i_percpu_s, bnx2i_percpu);

/**
 * bnx2i_get_cid_num - get cid from ep
 * @ep: 	endpoपूर्णांक poपूर्णांकer
 *
 * Only applicable to 57710 family of devices
 */
अटल u32 bnx2i_get_cid_num(काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	u32 cid;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		cid = ep->ep_cid;
	अन्यथा
		cid = GET_CID_NUM(ep->ep_cid);
	वापस cid;
पूर्ण


/**
 * bnx2i_adjust_qp_size - Adjust SQ/RQ/CQ size क्रम 57710 device type
 * @hba: 		Adapter क्रम which adjusपंचांगents is to be made
 *
 * Only applicable to 57710 family of devices
 */
अटल व्योम bnx2i_adjust_qp_size(काष्ठा bnx2i_hba *hba)
अणु
	u32 num_elements_per_pg;

	अगर (test_bit(BNX2I_NX2_DEV_5706, &hba->cnic_dev_type) ||
	    test_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type) ||
	    test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type)) अणु
		अगर (!is_घातer_of_2(hba->max_sqes))
			hba->max_sqes = roundकरोwn_घात_of_two(hba->max_sqes);

		अगर (!is_घातer_of_2(hba->max_rqes))
			hba->max_rqes = roundकरोwn_घात_of_two(hba->max_rqes);
	पूर्ण

	/* Adjust each queue size अगर the user selection करोes not
	 * yield पूर्णांकegral num of page buffers
	 */
	/* adjust SQ */
	num_elements_per_pg = CNIC_PAGE_SIZE / BNX2I_SQ_WQE_SIZE;
	अगर (hba->max_sqes < num_elements_per_pg)
		hba->max_sqes = num_elements_per_pg;
	अन्यथा अगर (hba->max_sqes % num_elements_per_pg)
		hba->max_sqes = (hba->max_sqes + num_elements_per_pg - 1) &
				 ~(num_elements_per_pg - 1);

	/* adjust CQ */
	num_elements_per_pg = CNIC_PAGE_SIZE / BNX2I_CQE_SIZE;
	अगर (hba->max_cqes < num_elements_per_pg)
		hba->max_cqes = num_elements_per_pg;
	अन्यथा अगर (hba->max_cqes % num_elements_per_pg)
		hba->max_cqes = (hba->max_cqes + num_elements_per_pg - 1) &
				 ~(num_elements_per_pg - 1);

	/* adjust RQ */
	num_elements_per_pg = CNIC_PAGE_SIZE / BNX2I_RQ_WQE_SIZE;
	अगर (hba->max_rqes < num_elements_per_pg)
		hba->max_rqes = num_elements_per_pg;
	अन्यथा अगर (hba->max_rqes % num_elements_per_pg)
		hba->max_rqes = (hba->max_rqes + num_elements_per_pg - 1) &
				 ~(num_elements_per_pg - 1);
पूर्ण


/**
 * bnx2i_get_link_state - get network पूर्णांकerface link state
 * @hba:	adapter instance poपूर्णांकer
 *
 * updates adapter काष्ठाure flag based on netdev state
 */
अटल व्योम bnx2i_get_link_state(काष्ठा bnx2i_hba *hba)
अणु
	अगर (test_bit(__LINK_STATE_NOCARRIER, &hba->netdev->state))
		set_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
	अन्यथा
		clear_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
पूर्ण


/**
 * bnx2i_iscsi_license_error - displays iscsi license related error message
 * @hba:		adapter instance poपूर्णांकer
 * @error_code:		error classअगरication
 *
 * Puts out an error log when driver is unable to offload iscsi connection
 *	due to license restrictions
 */
अटल व्योम bnx2i_iscsi_license_error(काष्ठा bnx2i_hba *hba, u32 error_code)
अणु
	अगर (error_code == ISCSI_KCQE_COMPLETION_STATUS_ISCSI_NOT_SUPPORTED)
		/* iSCSI offload not supported on this device */
		prपूर्णांकk(KERN_ERR "bnx2i: iSCSI not supported, dev=%s\n",
				hba->netdev->name);
	अगर (error_code == ISCSI_KCQE_COMPLETION_STATUS_LOM_ISCSI_NOT_ENABLED)
		/* iSCSI offload not supported on this LOM device */
		prपूर्णांकk(KERN_ERR "bnx2i: LOM is not enable to "
				"offload iSCSI connections, dev=%s\n",
				hba->netdev->name);
	set_bit(ADAPTER_STATE_INIT_FAILED, &hba->adapter_state);
पूर्ण


/**
 * bnx2i_arm_cq_event_coalescing - arms CQ to enable EQ notअगरication
 * @ep:		endpoपूर्णांक (transport identअगरier) काष्ठाure
 * @action:	action, ARM or DISARM. For now only ARM_CQE is used
 *
 * Arm'ing CQ will enable chip to generate global EQ events inorder to पूर्णांकerrupt
 *	the driver. EQ event is generated CQ index is hit or at least 1 CQ is
 *	outstanding and on chip समयr expires
 */
पूर्णांक bnx2i_arm_cq_event_coalescing(काष्ठा bnx2i_endpoपूर्णांक *ep, u8 action)
अणु
	काष्ठा bnx2i_5771x_cq_db *cq_db;
	u16 cq_index;
	u16 next_index = 0;
	u32 num_active_cmds;

	/* Coalesce CQ entries only on 10G devices */
	अगर (!test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		वापस 0;

	/* Do not update CQ DB multiple बार beक्रमe firmware ग_लिखोs
	 * '0xFFFF' to CQDB->SQN field. Deviation may cause spurious
	 * पूर्णांकerrupts and other unwanted results
	 */
	cq_db = (काष्ठा bnx2i_5771x_cq_db *) ep->qp.cq_pgtbl_virt;

	अगर (action != CNIC_ARM_CQE_FP)
		अगर (cq_db->sqn[0] && cq_db->sqn[0] != 0xFFFF)
			वापस 0;

	अगर (action == CNIC_ARM_CQE || action == CNIC_ARM_CQE_FP) अणु
		num_active_cmds = atomic_पढ़ो(&ep->num_active_cmds);
		अगर (num_active_cmds <= event_coal_min)
			next_index = 1;
		अन्यथा अणु
			next_index = num_active_cmds >> ep->ec_shअगरt;
			अगर (next_index > num_active_cmds - event_coal_min)
				next_index = num_active_cmds - event_coal_min;
		पूर्ण
		अगर (!next_index)
			next_index = 1;
		cq_index = ep->qp.cqe_exp_seq_sn + next_index - 1;
		अगर (cq_index > ep->qp.cqe_size * 2)
			cq_index -= ep->qp.cqe_size * 2;
		अगर (!cq_index)
			cq_index = 1;

		cq_db->sqn[0] = cq_index;
	पूर्ण
	वापस next_index;
पूर्ण


/**
 * bnx2i_get_rq_buf - copy RQ buffer contents to driver buffer
 * @bnx2i_conn:		iscsi connection on which RQ event occurred
 * @ptr:		driver buffer to which RQ buffer contents is to
 *			be copied
 * @len:		length of valid data inside RQ buf
 *
 * Copies RQ buffer contents from shared (DMA'able) memory region to
 *	driver buffer. RQ is used to DMA unsolicitated iscsi pdu's and
 *	scsi sense info
 */
व्योम bnx2i_get_rq_buf(काष्ठा bnx2i_conn *bnx2i_conn, अक्षर *ptr, पूर्णांक len)
अणु
	अगर (!bnx2i_conn->ep->qp.rqe_left)
		वापस;

	bnx2i_conn->ep->qp.rqe_left--;
	स_नकल(ptr, (u8 *) bnx2i_conn->ep->qp.rq_cons_qe, len);
	अगर (bnx2i_conn->ep->qp.rq_cons_qe == bnx2i_conn->ep->qp.rq_last_qe) अणु
		bnx2i_conn->ep->qp.rq_cons_qe = bnx2i_conn->ep->qp.rq_first_qe;
		bnx2i_conn->ep->qp.rq_cons_idx = 0;
	पूर्ण अन्यथा अणु
		bnx2i_conn->ep->qp.rq_cons_qe++;
		bnx2i_conn->ep->qp.rq_cons_idx++;
	पूर्ण
पूर्ण


अटल व्योम bnx2i_ring_577xx_करोorbell(काष्ठा bnx2i_conn *conn)
अणु
	काष्ठा bnx2i_5771x_dbell dbell;
	u32 msg;

	स_रखो(&dbell, 0, माप(dbell));
	dbell.dbell.header = (B577XX_ISCSI_CONNECTION_TYPE <<
			      B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT);
	msg = *((u32 *)&dbell);
	/* TODO : get करोorbell रेजिस्टर mapping */
	ग_लिखोl(cpu_to_le32(msg), conn->ep->qp.ctx_base);
पूर्ण


/**
 * bnx2i_put_rq_buf - Replenish RQ buffer, अगर required ring on chip करोorbell
 * @bnx2i_conn:	iscsi connection on which event to post
 * @count:	number of RQ buffer being posted to chip
 *
 * No need to ring hardware करोorbell क्रम 57710 family of devices
 */
व्योम bnx2i_put_rq_buf(काष्ठा bnx2i_conn *bnx2i_conn, पूर्णांक count)
अणु
	काष्ठा bnx2i_5771x_sq_rq_db *rq_db;
	u16 hi_bit = (bnx2i_conn->ep->qp.rq_prod_idx & 0x8000);
	काष्ठा bnx2i_endpoपूर्णांक *ep = bnx2i_conn->ep;

	ep->qp.rqe_left += count;
	ep->qp.rq_prod_idx &= 0x7FFF;
	ep->qp.rq_prod_idx += count;

	अगर (ep->qp.rq_prod_idx > bnx2i_conn->hba->max_rqes) अणु
		ep->qp.rq_prod_idx %= bnx2i_conn->hba->max_rqes;
		अगर (!hi_bit)
			ep->qp.rq_prod_idx |= 0x8000;
	पूर्ण अन्यथा
		ep->qp.rq_prod_idx |= hi_bit;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) अणु
		rq_db = (काष्ठा bnx2i_5771x_sq_rq_db *) ep->qp.rq_pgtbl_virt;
		rq_db->prod_idx = ep->qp.rq_prod_idx;
		/* no need to ring hardware करोorbell क्रम 57710 */
	पूर्ण अन्यथा अणु
		ग_लिखोw(ep->qp.rq_prod_idx,
		       ep->qp.ctx_base + CNIC_RECV_DOORBELL);
	पूर्ण
पूर्ण


/**
 * bnx2i_ring_sq_dbell - Ring SQ करोorbell to wake-up the processing engine
 * @bnx2i_conn:		iscsi connection to which new SQ entries beदीर्घ
 * @count: 		number of SQ WQEs to post
 *
 * SQ DB is updated in host memory and TX Doorbell is rung क्रम 57710 family
 *	of devices. For 5706/5708/5709 new SQ WQE count is written पूर्णांकo the
 *	करोorbell रेजिस्टर
 */
अटल व्योम bnx2i_ring_sq_dbell(काष्ठा bnx2i_conn *bnx2i_conn, पूर्णांक count)
अणु
	काष्ठा bnx2i_5771x_sq_rq_db *sq_db;
	काष्ठा bnx2i_endpoपूर्णांक *ep = bnx2i_conn->ep;

	atomic_inc(&ep->num_active_cmds);
	wmb();	/* flush SQ WQE memory beक्रमe the करोorbell is rung */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) अणु
		sq_db = (काष्ठा bnx2i_5771x_sq_rq_db *) ep->qp.sq_pgtbl_virt;
		sq_db->prod_idx = ep->qp.sq_prod_idx;
		bnx2i_ring_577xx_करोorbell(bnx2i_conn);
	पूर्ण अन्यथा
		ग_लिखोw(count, ep->qp.ctx_base + CNIC_SEND_DOORBELL);
पूर्ण


/**
 * bnx2i_ring_dbell_update_sq_params - update SQ driver parameters
 * @bnx2i_conn:	iscsi connection to which new SQ entries beदीर्घ
 * @count:	number of SQ WQEs to post
 *
 * this routine will update SQ driver parameters and ring the करोorbell
 */
अटल व्योम bnx2i_ring_dbell_update_sq_params(काष्ठा bnx2i_conn *bnx2i_conn,
					      पूर्णांक count)
अणु
	पूर्णांक पंचांगp_cnt;

	अगर (count == 1) अणु
		अगर (bnx2i_conn->ep->qp.sq_prod_qe ==
		    bnx2i_conn->ep->qp.sq_last_qe)
			bnx2i_conn->ep->qp.sq_prod_qe =
						bnx2i_conn->ep->qp.sq_first_qe;
		अन्यथा
			bnx2i_conn->ep->qp.sq_prod_qe++;
	पूर्ण अन्यथा अणु
		अगर ((bnx2i_conn->ep->qp.sq_prod_qe + count) <=
		    bnx2i_conn->ep->qp.sq_last_qe)
			bnx2i_conn->ep->qp.sq_prod_qe += count;
		अन्यथा अणु
			पंचांगp_cnt = bnx2i_conn->ep->qp.sq_last_qe -
				bnx2i_conn->ep->qp.sq_prod_qe;
			bnx2i_conn->ep->qp.sq_prod_qe =
				&bnx2i_conn->ep->qp.sq_first_qe[count -
								(पंचांगp_cnt + 1)];
		पूर्ण
	पूर्ण
	bnx2i_conn->ep->qp.sq_prod_idx += count;
	/* Ring the करोorbell */
	bnx2i_ring_sq_dbell(bnx2i_conn, bnx2i_conn->ep->qp.sq_prod_idx);
पूर्ण


/**
 * bnx2i_send_iscsi_login - post iSCSI login request MP WQE to hardware
 * @bnx2i_conn:	iscsi connection
 * @task: transport layer's command काष्ठाure poपूर्णांकer which is requesting
 *	  a WQE to sent to chip क्रम further processing
 *
 * prepare and post an iSCSI Login request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_login(काष्ठा bnx2i_conn *bnx2i_conn,
			   काष्ठा iscsi_task *task)
अणु
	काष्ठा bnx2i_login_request *login_wqe;
	काष्ठा iscsi_login_req *login_hdr;
	u32 dword;

	login_hdr = (काष्ठा iscsi_login_req *)task->hdr;
	login_wqe = (काष्ठा bnx2i_login_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;

	login_wqe->op_code = login_hdr->opcode;
	login_wqe->op_attr = login_hdr->flags;
	login_wqe->version_max = login_hdr->max_version;
	login_wqe->version_min = login_hdr->min_version;
	login_wqe->data_length = ntoh24(login_hdr->dlength);
	login_wqe->isid_lo = *((u32 *) login_hdr->isid);
	login_wqe->isid_hi = *((u16 *) login_hdr->isid + 2);
	login_wqe->tsih = login_hdr->tsih;
	login_wqe->itt = task->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_LOGIN_REQUEST_TYPE_SHIFT);
	login_wqe->cid = login_hdr->cid;

	login_wqe->cmd_sn = be32_to_cpu(login_hdr->cmdsn);
	login_wqe->exp_stat_sn = be32_to_cpu(login_hdr->exp_statsn);
	login_wqe->flags = ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN;

	login_wqe->resp_bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.resp_bd_dma;
	login_wqe->resp_bd_list_addr_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.resp_bd_dma >> 32);

	dword = ((1 << ISCSI_LOGIN_REQUEST_NUM_RESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.resp_buf_size <<
		  ISCSI_LOGIN_REQUEST_RESP_BUFFER_LENGTH_SHIFT));
	login_wqe->resp_buffer = dword;
	login_wqe->bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.req_bd_dma;
	login_wqe->bd_list_addr_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.req_bd_dma >> 32);
	login_wqe->num_bds = 1;
	login_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण

/**
 * bnx2i_send_iscsi_पंचांगf - post iSCSI task management request MP WQE to hardware
 * @bnx2i_conn:	iscsi connection
 * @mtask:	driver command काष्ठाure which is requesting
 *		a WQE to sent to chip क्रम further processing
 *
 * prepare and post an iSCSI Login request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_पंचांगf(काष्ठा bnx2i_conn *bnx2i_conn,
			 काष्ठा iscsi_task *mtask)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_पंचांग *पंचांगfपात_hdr;
	काष्ठा scsi_cmnd *ref_sc;
	काष्ठा iscsi_task *ctask;
	काष्ठा bnx2i_पंचांगf_request *पंचांगfपात_wqe;
	u32 dword;
	u32 scsi_lun[2];

	पंचांगfपात_hdr = (काष्ठा iscsi_पंचांग *)mtask->hdr;
	पंचांगfपात_wqe = (काष्ठा bnx2i_पंचांगf_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;

	पंचांगfपात_wqe->op_code = पंचांगfपात_hdr->opcode;
	पंचांगfपात_wqe->op_attr = पंचांगfपात_hdr->flags;

	पंचांगfपात_wqe->itt = (mtask->itt | (ISCSI_TASK_TYPE_MPATH << 14));
	पंचांगfपात_wqe->reserved2 = 0;
	पंचांगfपात_wqe->cmd_sn = be32_to_cpu(पंचांगfपात_hdr->cmdsn);

	चयन (पंचांगfपात_hdr->flags & ISCSI_FLAG_TM_FUNC_MASK) अणु
	हाल ISCSI_TM_FUNC_ABORT_TASK:
	हाल ISCSI_TM_FUNC_TASK_REASSIGN:
		ctask = iscsi_itt_to_task(conn, पंचांगfपात_hdr->rtt);
		अगर (!ctask || !ctask->sc)
			/*
			 * the iscsi layer must have completed the cmd जबतक
			 * was starting up.
			 *
			 * Note: In the हाल of a SCSI cmd समयout, the task's
			 *       sc is still active; hence ctask->sc != 0
			 *       In this हाल, the task must be पातed
			 */
			वापस 0;

		ref_sc = ctask->sc;
		अगर (ref_sc->sc_data_direction == DMA_TO_DEVICE)
			dword = (ISCSI_TASK_TYPE_WRITE <<
				 ISCSI_CMD_REQUEST_TYPE_SHIFT);
		अन्यथा
			dword = (ISCSI_TASK_TYPE_READ <<
				 ISCSI_CMD_REQUEST_TYPE_SHIFT);
		पंचांगfपात_wqe->ref_itt = (dword |
					(पंचांगfपात_hdr->rtt & ISCSI_ITT_MASK));
		अवरोध;
	शेष:
		पंचांगfपात_wqe->ref_itt = RESERVED_ITT;
	पूर्ण
	स_नकल(scsi_lun, &पंचांगfपात_hdr->lun, माप(काष्ठा scsi_lun));
	पंचांगfपात_wqe->lun[0] = be32_to_cpu(scsi_lun[0]);
	पंचांगfपात_wqe->lun[1] = be32_to_cpu(scsi_lun[1]);

	पंचांगfपात_wqe->ref_cmd_sn = be32_to_cpu(पंचांगfपात_hdr->refcmdsn);

	पंचांगfपात_wqe->bd_list_addr_lo = (u32) bnx2i_conn->hba->mp_bd_dma;
	पंचांगfपात_wqe->bd_list_addr_hi = (u32)
				((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
	पंचांगfपात_wqe->num_bds = 1;
	पंचांगfपात_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण

/**
 * bnx2i_send_iscsi_text - post iSCSI text WQE to hardware
 * @bnx2i_conn:	iscsi connection
 * @mtask:	driver command काष्ठाure which is requesting
 *		a WQE to sent to chip क्रम further processing
 *
 * prepare and post an iSCSI Text request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_text(काष्ठा bnx2i_conn *bnx2i_conn,
			  काष्ठा iscsi_task *mtask)
अणु
	काष्ठा bnx2i_text_request *text_wqe;
	काष्ठा iscsi_text *text_hdr;
	u32 dword;

	text_hdr = (काष्ठा iscsi_text *)mtask->hdr;
	text_wqe = (काष्ठा bnx2i_text_request *) bnx2i_conn->ep->qp.sq_prod_qe;

	स_रखो(text_wqe, 0, माप(काष्ठा bnx2i_text_request));

	text_wqe->op_code = text_hdr->opcode;
	text_wqe->op_attr = text_hdr->flags;
	text_wqe->data_length = ntoh24(text_hdr->dlength);
	text_wqe->itt = mtask->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_TEXT_REQUEST_TYPE_SHIFT);
	text_wqe->ttt = be32_to_cpu(text_hdr->ttt);

	text_wqe->cmd_sn = be32_to_cpu(text_hdr->cmdsn);

	text_wqe->resp_bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.resp_bd_dma;
	text_wqe->resp_bd_list_addr_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.resp_bd_dma >> 32);

	dword = ((1 << ISCSI_TEXT_REQUEST_NUM_RESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.resp_buf_size <<
		  ISCSI_TEXT_REQUEST_RESP_BUFFER_LENGTH_SHIFT));
	text_wqe->resp_buffer = dword;
	text_wqe->bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.req_bd_dma;
	text_wqe->bd_list_addr_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.req_bd_dma >> 32);
	text_wqe->num_bds = 1;
	text_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण


/**
 * bnx2i_send_iscsi_scsicmd - post iSCSI scsicmd request WQE to hardware
 * @bnx2i_conn:	iscsi connection
 * @cmd:	driver command काष्ठाure which is requesting
 *		a WQE to sent to chip क्रम further processing
 *
 * prepare and post an iSCSI SCSI-CMD request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_scsicmd(काष्ठा bnx2i_conn *bnx2i_conn,
			     काष्ठा bnx2i_cmd *cmd)
अणु
	काष्ठा bnx2i_cmd_request *scsi_cmd_wqe;

	scsi_cmd_wqe = (काष्ठा bnx2i_cmd_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;
	स_नकल(scsi_cmd_wqe, &cmd->req, माप(काष्ठा bnx2i_cmd_request));
	scsi_cmd_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण

/**
 * bnx2i_send_iscsi_nopout - post iSCSI NOPOUT request WQE to hardware
 * @bnx2i_conn:		iscsi connection
 * @task:		transport layer's command काष्ठाure poपूर्णांकer which is
 *                      requesting a WQE to sent to chip क्रम further processing
 * @datap:		payload buffer poपूर्णांकer
 * @data_len:		payload data length
 * @unsol:		indicated whether nopout pdu is unsolicited pdu or
 *			in response to target's NOPIN w/ TTT != FFFFFFFF
 *
 * prepare and post a nopout request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_nopout(काष्ठा bnx2i_conn *bnx2i_conn,
			    काष्ठा iscsi_task *task,
			    अक्षर *datap, पूर्णांक data_len, पूर्णांक unsol)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = bnx2i_conn->ep;
	काष्ठा bnx2i_nop_out_request *nopout_wqe;
	काष्ठा iscsi_nopout *nopout_hdr;

	nopout_hdr = (काष्ठा iscsi_nopout *)task->hdr;
	nopout_wqe = (काष्ठा bnx2i_nop_out_request *)ep->qp.sq_prod_qe;

	स_रखो(nopout_wqe, 0x00, माप(काष्ठा bnx2i_nop_out_request));

	nopout_wqe->op_code = nopout_hdr->opcode;
	nopout_wqe->op_attr = ISCSI_FLAG_CMD_FINAL;
	स_नकल(nopout_wqe->lun, &nopout_hdr->lun, 8);

	/* 57710 requires LUN field to be swapped */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		swap(nopout_wqe->lun[0], nopout_wqe->lun[1]);

	nopout_wqe->itt = ((u16)task->itt |
			   (ISCSI_TASK_TYPE_MPATH <<
			    ISCSI_TMF_REQUEST_TYPE_SHIFT));
	nopout_wqe->ttt = be32_to_cpu(nopout_hdr->ttt);
	nopout_wqe->flags = 0;
	अगर (!unsol)
		nopout_wqe->flags = ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION;
	अन्यथा अगर (nopout_hdr->itt == RESERVED_ITT)
		nopout_wqe->flags = ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION;

	nopout_wqe->cmd_sn = be32_to_cpu(nopout_hdr->cmdsn);
	nopout_wqe->data_length = data_len;
	अगर (data_len) अणु
		/* handle payload data, not required in first release */
		prपूर्णांकk(KERN_ALERT "NOPOUT: WARNING!! payload len != 0\n");
	पूर्ण अन्यथा अणु
		nopout_wqe->bd_list_addr_lo = (u32)
					bnx2i_conn->hba->mp_bd_dma;
		nopout_wqe->bd_list_addr_hi =
			(u32) ((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
		nopout_wqe->num_bds = 1;
	पूर्ण
	nopout_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण


/**
 * bnx2i_send_iscsi_logout - post iSCSI logout request WQE to hardware
 * @bnx2i_conn:	iscsi connection
 * @task:	transport layer's command काष्ठाure poपूर्णांकer which is
 *		requesting a WQE to sent to chip क्रम further processing
 *
 * prepare and post logout request WQE to CNIC firmware
 */
पूर्णांक bnx2i_send_iscsi_logout(काष्ठा bnx2i_conn *bnx2i_conn,
			    काष्ठा iscsi_task *task)
अणु
	काष्ठा bnx2i_logout_request *logout_wqe;
	काष्ठा iscsi_logout *logout_hdr;

	logout_hdr = (काष्ठा iscsi_logout *)task->hdr;

	logout_wqe = (काष्ठा bnx2i_logout_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;
	स_रखो(logout_wqe, 0x00, माप(काष्ठा bnx2i_logout_request));

	logout_wqe->op_code = logout_hdr->opcode;
	logout_wqe->cmd_sn = be32_to_cpu(logout_hdr->cmdsn);
	logout_wqe->op_attr =
			logout_hdr->flags | ISCSI_LOGOUT_REQUEST_ALWAYS_ONE;
	logout_wqe->itt = ((u16)task->itt |
			   (ISCSI_TASK_TYPE_MPATH <<
			    ISCSI_LOGOUT_REQUEST_TYPE_SHIFT));
	logout_wqe->data_length = 0;
	logout_wqe->cid = 0;

	logout_wqe->bd_list_addr_lo = (u32) bnx2i_conn->hba->mp_bd_dma;
	logout_wqe->bd_list_addr_hi = (u32)
				((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
	logout_wqe->num_bds = 1;
	logout_wqe->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_conn->ep->state = EP_STATE_LOGOUT_SENT;

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	वापस 0;
पूर्ण


/**
 * bnx2i_update_iscsi_conn - post iSCSI logout request WQE to hardware
 * @conn:	iscsi connection which requires iscsi parameter update
 *
 * sends करोwn iSCSI Conn Update request to move iSCSI conn to FFP
 */
व्योम bnx2i_update_iscsi_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा bnx2i_hba *hba = bnx2i_conn->hba;
	काष्ठा kwqe *kwqe_arr[2];
	काष्ठा iscsi_kwqe_conn_update *update_wqe;
	काष्ठा iscsi_kwqe_conn_update conn_update_kwqe;

	update_wqe = &conn_update_kwqe;

	update_wqe->hdr.op_code = ISCSI_KWQE_OPCODE_UPDATE_CONN;
	update_wqe->hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	/* 5771x requires conn context id to be passed as is */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_conn->ep->hba->cnic_dev_type))
		update_wqe->context_id = bnx2i_conn->ep->ep_cid;
	अन्यथा
		update_wqe->context_id = (bnx2i_conn->ep->ep_cid >> 7);
	update_wqe->conn_flags = 0;
	अगर (conn->hdrdgst_en)
		update_wqe->conn_flags |= ISCSI_KWQE_CONN_UPDATE_HEADER_DIGEST;
	अगर (conn->datadgst_en)
		update_wqe->conn_flags |= ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST;
	अगर (conn->session->initial_r2t_en)
		update_wqe->conn_flags |= ISCSI_KWQE_CONN_UPDATE_INITIAL_R2T;
	अगर (conn->session->imm_data_en)
		update_wqe->conn_flags |= ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA;

	update_wqe->max_send_pdu_length = conn->max_xmit_dlength;
	update_wqe->max_recv_pdu_length = conn->max_recv_dlength;
	update_wqe->first_burst_length = conn->session->first_burst;
	update_wqe->max_burst_length = conn->session->max_burst;
	update_wqe->exp_stat_sn = conn->exp_statsn;
	update_wqe->max_outstanding_r2ts = conn->session->max_r2t;
	update_wqe->session_error_recovery_level = conn->session->erl;
	iscsi_conn_prपूर्णांकk(KERN_ALERT, conn,
			  "bnx2i: conn update - MBL 0x%x FBL 0x%x"
			  "MRDSL_I 0x%x MRDSL_T 0x%x \n",
			  update_wqe->max_burst_length,
			  update_wqe->first_burst_length,
			  update_wqe->max_recv_pdu_length,
			  update_wqe->max_send_pdu_length);

	kwqe_arr[0] = (काष्ठा kwqe *) update_wqe;
	अगर (hba->cnic && hba->cnic->submit_kwqes)
		hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, 1);
पूर्ण


/**
 * bnx2i_ep_ofld_समयr - post iSCSI logout request WQE to hardware
 * @t:	समयr context used to fetch the endpoपूर्णांक (transport
 *	handle) काष्ठाure poपूर्णांकer
 *
 * routine to handle connection offload/destroy request समयout
 */
व्योम bnx2i_ep_ofld_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = from_समयr(ep, t, ofld_समयr);

	अगर (ep->state == EP_STATE_OFLD_START) अणु
		prपूर्णांकk(KERN_ALERT "ofld_timer: CONN_OFLD timeout\n");
		ep->state = EP_STATE_OFLD_FAILED;
	पूर्ण अन्यथा अगर (ep->state == EP_STATE_DISCONN_START) अणु
		prपूर्णांकk(KERN_ALERT "ofld_timer: CONN_DISCON timeout\n");
		ep->state = EP_STATE_DISCONN_TIMEDOUT;
	पूर्ण अन्यथा अगर (ep->state == EP_STATE_CLEANUP_START) अणु
		prपूर्णांकk(KERN_ALERT "ofld_timer: CONN_CLEANUP timeout\n");
		ep->state = EP_STATE_CLEANUP_FAILED;
	पूर्ण

	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण


अटल पूर्णांक bnx2i_घातer_of2(u32 val)
अणु
	u32 घातer = 0;
	अगर (val & (val - 1))
		वापस घातer;
	val--;
	जबतक (val) अणु
		val = val >> 1;
		घातer++;
	पूर्ण
	वापस घातer;
पूर्ण


/**
 * bnx2i_send_cmd_cleanup_req - send iscsi cmd context clean-up request
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @cmd:	driver command काष्ठाure which is requesting
 *		a WQE to sent to chip क्रम further processing
 *
 * prepares and posts CONN_OFLD_REQ1/2 KWQE
 */
व्योम bnx2i_send_cmd_cleanup_req(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_cmd *cmd)
अणु
	काष्ठा bnx2i_cleanup_request *cmd_cleanup;

	cmd_cleanup =
		(काष्ठा bnx2i_cleanup_request *)cmd->conn->ep->qp.sq_prod_qe;
	स_रखो(cmd_cleanup, 0x00, माप(काष्ठा bnx2i_cleanup_request));

	cmd_cleanup->op_code = ISCSI_OPCODE_CLEANUP_REQUEST;
	cmd_cleanup->itt = cmd->req.itt;
	cmd_cleanup->cq_index = 0; /* CQ# used क्रम completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(cmd->conn, 1);
पूर्ण


/**
 * bnx2i_send_conn_destroy - initiates iscsi connection tearकरोwn process
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @ep:		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * this routine prepares and posts CONN_OFLD_REQ1/2 KWQE to initiate
 * 	iscsi connection context clean-up process
 */
पूर्णांक bnx2i_send_conn_destroy(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	काष्ठा kwqe *kwqe_arr[2];
	काष्ठा iscsi_kwqe_conn_destroy conn_cleanup;
	पूर्णांक rc = -EINVAL;

	स_रखो(&conn_cleanup, 0x00, माप(काष्ठा iscsi_kwqe_conn_destroy));

	conn_cleanup.hdr.op_code = ISCSI_KWQE_OPCODE_DESTROY_CONN;
	conn_cleanup.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);
	/* 5771x requires conn context id to be passed as is */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		conn_cleanup.context_id = ep->ep_cid;
	अन्यथा
		conn_cleanup.context_id = (ep->ep_cid >> 7);

	conn_cleanup.reserved0 = (u16)ep->ep_iscsi_cid;

	kwqe_arr[0] = (काष्ठा kwqe *) &conn_cleanup;
	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, 1);

	वापस rc;
पूर्ण


/**
 * bnx2i_570x_send_conn_ofld_req - initiates iscsi conn context setup process
 * @hba: 		adapter काष्ठाure poपूर्णांकer
 * @ep: 		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * 5706/5708/5709 specअगरic - prepares and posts CONN_OFLD_REQ1/2 KWQE
 */
अटल पूर्णांक bnx2i_570x_send_conn_ofld_req(काष्ठा bnx2i_hba *hba,
					 काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	काष्ठा kwqe *kwqe_arr[2];
	काष्ठा iscsi_kwqe_conn_offload1 ofld_req1;
	काष्ठा iscsi_kwqe_conn_offload2 ofld_req2;
	dma_addr_t dma_addr;
	पूर्णांक num_kwqes = 2;
	u32 *ptbl;
	पूर्णांक rc = -EINVAL;

	ofld_req1.hdr.op_code = ISCSI_KWQE_OPCODE_OFFLOAD_CONN1;
	ofld_req1.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	ofld_req1.iscsi_conn_id = (u16) ep->ep_iscsi_cid;

	dma_addr = ep->qp.sq_pgtbl_phys;
	ofld_req1.sq_page_table_addr_lo = (u32) dma_addr;
	ofld_req1.sq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	dma_addr = ep->qp.cq_pgtbl_phys;
	ofld_req1.cq_page_table_addr_lo = (u32) dma_addr;
	ofld_req1.cq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	ofld_req2.hdr.op_code = ISCSI_KWQE_OPCODE_OFFLOAD_CONN2;
	ofld_req2.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	dma_addr = ep->qp.rq_pgtbl_phys;
	ofld_req2.rq_page_table_addr_lo = (u32) dma_addr;
	ofld_req2.rq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	ptbl = (u32 *) ep->qp.sq_pgtbl_virt;

	ofld_req2.sq_first_pte.hi = *ptbl++;
	ofld_req2.sq_first_pte.lo = *ptbl;

	ptbl = (u32 *) ep->qp.cq_pgtbl_virt;
	ofld_req2.cq_first_pte.hi = *ptbl++;
	ofld_req2.cq_first_pte.lo = *ptbl;

	kwqe_arr[0] = (काष्ठा kwqe *) &ofld_req1;
	kwqe_arr[1] = (काष्ठा kwqe *) &ofld_req2;
	ofld_req2.num_additional_wqes = 0;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण


/**
 * bnx2i_5771x_send_conn_ofld_req - initiates iscsi connection context creation
 * @hba: 		adapter काष्ठाure poपूर्णांकer
 * @ep: 		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * 57710 specअगरic - prepares and posts CONN_OFLD_REQ1/2 KWQE
 */
अटल पूर्णांक bnx2i_5771x_send_conn_ofld_req(काष्ठा bnx2i_hba *hba,
					  काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	काष्ठा kwqe *kwqe_arr[5];
	काष्ठा iscsi_kwqe_conn_offload1 ofld_req1;
	काष्ठा iscsi_kwqe_conn_offload2 ofld_req2;
	काष्ठा iscsi_kwqe_conn_offload3 ofld_req3[1];
	dma_addr_t dma_addr;
	पूर्णांक num_kwqes = 2;
	u32 *ptbl;
	पूर्णांक rc = -EINVAL;

	ofld_req1.hdr.op_code = ISCSI_KWQE_OPCODE_OFFLOAD_CONN1;
	ofld_req1.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	ofld_req1.iscsi_conn_id = (u16) ep->ep_iscsi_cid;

	dma_addr = ep->qp.sq_pgtbl_phys + ISCSI_SQ_DB_SIZE;
	ofld_req1.sq_page_table_addr_lo = (u32) dma_addr;
	ofld_req1.sq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	dma_addr = ep->qp.cq_pgtbl_phys + ISCSI_CQ_DB_SIZE;
	ofld_req1.cq_page_table_addr_lo = (u32) dma_addr;
	ofld_req1.cq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	ofld_req2.hdr.op_code = ISCSI_KWQE_OPCODE_OFFLOAD_CONN2;
	ofld_req2.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	dma_addr = ep->qp.rq_pgtbl_phys + ISCSI_RQ_DB_SIZE;
	ofld_req2.rq_page_table_addr_lo = (u32) dma_addr;
	ofld_req2.rq_page_table_addr_hi = (u32) ((u64) dma_addr >> 32);

	ptbl = (u32 *)((u8 *)ep->qp.sq_pgtbl_virt + ISCSI_SQ_DB_SIZE);
	ofld_req2.sq_first_pte.hi = *ptbl++;
	ofld_req2.sq_first_pte.lo = *ptbl;

	ptbl = (u32 *)((u8 *)ep->qp.cq_pgtbl_virt + ISCSI_CQ_DB_SIZE);
	ofld_req2.cq_first_pte.hi = *ptbl++;
	ofld_req2.cq_first_pte.lo = *ptbl;

	kwqe_arr[0] = (काष्ठा kwqe *) &ofld_req1;
	kwqe_arr[1] = (काष्ठा kwqe *) &ofld_req2;

	ofld_req2.num_additional_wqes = 1;
	स_रखो(ofld_req3, 0x00, माप(ofld_req3[0]));
	ptbl = (u32 *)((u8 *)ep->qp.rq_pgtbl_virt + ISCSI_RQ_DB_SIZE);
	ofld_req3[0].qp_first_pte[0].hi = *ptbl++;
	ofld_req3[0].qp_first_pte[0].lo = *ptbl;

	kwqe_arr[2] = (काष्ठा kwqe *) ofld_req3;
	/* need अगर we decide to go with multiple KCQE's per conn */
	num_kwqes += 1;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण

/**
 * bnx2i_send_conn_ofld_req - initiates iscsi connection context setup process
 *
 * @hba: 		adapter काष्ठाure poपूर्णांकer
 * @ep: 		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * this routine prepares and posts CONN_OFLD_REQ1/2 KWQE
 */
पूर्णांक bnx2i_send_conn_ofld_req(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	पूर्णांक rc;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		rc = bnx2i_5771x_send_conn_ofld_req(hba, ep);
	अन्यथा
		rc = bnx2i_570x_send_conn_ofld_req(hba, ep);

	वापस rc;
पूर्ण


/**
 * setup_qp_page_tables - iscsi QP page table setup function
 * @ep:		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * Sets up page tables क्रम SQ/RQ/CQ, 1G/sec (5706/5708/5709) devices requires
 * 	64-bit address in big endian क्रमmat. Whereas 10G/sec (57710) requires
 * 	PT in little endian क्रमmat
 */
अटल व्योम setup_qp_page_tables(काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	पूर्णांक num_pages;
	u32 *ptbl;
	dma_addr_t page;
	पूर्णांक cnic_dev_10g;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		cnic_dev_10g = 1;
	अन्यथा
		cnic_dev_10g = 0;

	/* SQ page table */
	स_रखो(ep->qp.sq_pgtbl_virt, 0, ep->qp.sq_pgtbl_size);
	num_pages = ep->qp.sq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.sq_phys;

	अगर (cnic_dev_10g)
		ptbl = (u32 *)((u8 *)ep->qp.sq_pgtbl_virt + ISCSI_SQ_DB_SIZE);
	अन्यथा
		ptbl = (u32 *) ep->qp.sq_pgtbl_virt;
	जबतक (num_pages--) अणु
		अगर (cnic_dev_10g) अणु
			/* PTE is written in little endian क्रमmat क्रम 57710 */
			*ptbl = (u32) page;
			ptbl++;
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण अन्यथा अणु
			/* PTE is written in big endian क्रमmat क्रम
			 * 5706/5708/5709 devices */
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			*ptbl = (u32) page;
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण
	पूर्ण

	/* RQ page table */
	स_रखो(ep->qp.rq_pgtbl_virt, 0, ep->qp.rq_pgtbl_size);
	num_pages = ep->qp.rq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.rq_phys;

	अगर (cnic_dev_10g)
		ptbl = (u32 *)((u8 *)ep->qp.rq_pgtbl_virt + ISCSI_RQ_DB_SIZE);
	अन्यथा
		ptbl = (u32 *) ep->qp.rq_pgtbl_virt;
	जबतक (num_pages--) अणु
		अगर (cnic_dev_10g) अणु
			/* PTE is written in little endian क्रमmat क्रम 57710 */
			*ptbl = (u32) page;
			ptbl++;
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण अन्यथा अणु
			/* PTE is written in big endian क्रमmat क्रम
			 * 5706/5708/5709 devices */
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			*ptbl = (u32) page;
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण
	पूर्ण

	/* CQ page table */
	स_रखो(ep->qp.cq_pgtbl_virt, 0, ep->qp.cq_pgtbl_size);
	num_pages = ep->qp.cq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.cq_phys;

	अगर (cnic_dev_10g)
		ptbl = (u32 *)((u8 *)ep->qp.cq_pgtbl_virt + ISCSI_CQ_DB_SIZE);
	अन्यथा
		ptbl = (u32 *) ep->qp.cq_pgtbl_virt;
	जबतक (num_pages--) अणु
		अगर (cnic_dev_10g) अणु
			/* PTE is written in little endian क्रमmat क्रम 57710 */
			*ptbl = (u32) page;
			ptbl++;
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण अन्यथा अणु
			/* PTE is written in big endian क्रमmat क्रम
			 * 5706/5708/5709 devices */
			*ptbl = (u32) ((u64) page >> 32);
			ptbl++;
			*ptbl = (u32) page;
			ptbl++;
			page += CNIC_PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण


/**
 * bnx2i_alloc_qp_resc - allocates required resources क्रम QP.
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @ep:		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * Allocate QP (transport layer क्रम iSCSI connection) resources, DMA'able
 *	memory क्रम SQ/RQ/CQ and page tables. EP काष्ठाure elements such
 *	as producer/consumer indexes/poपूर्णांकers, queue sizes and page table
 *	contents are setup
 */
पूर्णांक bnx2i_alloc_qp_resc(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	काष्ठा bnx2i_5771x_cq_db *cq_db;

	ep->hba = hba;
	ep->conn = शून्य;
	ep->ep_cid = ep->ep_iscsi_cid = ep->ep_pg_cid = 0;

	/* Allocate page table memory क्रम SQ which is page aligned */
	ep->qp.sq_mem_size = hba->max_sqes * BNX2I_SQ_WQE_SIZE;
	ep->qp.sq_mem_size =
		(ep->qp.sq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.sq_pgtbl_size =
		(ep->qp.sq_mem_size / CNIC_PAGE_SIZE) * माप(व्योम *);
	ep->qp.sq_pgtbl_size =
		(ep->qp.sq_pgtbl_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.sq_pgtbl_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.sq_pgtbl_size,
				   &ep->qp.sq_pgtbl_phys, GFP_KERNEL);
	अगर (!ep->qp.sq_pgtbl_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc SQ PT mem (%d)\n",
				  ep->qp.sq_pgtbl_size);
		जाओ mem_alloc_err;
	पूर्ण

	/* Allocate memory area क्रम actual SQ element */
	ep->qp.sq_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.sq_mem_size,
				   &ep->qp.sq_phys, GFP_KERNEL);
	अगर (!ep->qp.sq_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc SQ BD memory %d\n",
				  ep->qp.sq_mem_size);
		जाओ mem_alloc_err;
	पूर्ण

	ep->qp.sq_first_qe = ep->qp.sq_virt;
	ep->qp.sq_prod_qe = ep->qp.sq_first_qe;
	ep->qp.sq_cons_qe = ep->qp.sq_first_qe;
	ep->qp.sq_last_qe = &ep->qp.sq_first_qe[hba->max_sqes - 1];
	ep->qp.sq_prod_idx = 0;
	ep->qp.sq_cons_idx = 0;
	ep->qp.sqe_left = hba->max_sqes;

	/* Allocate page table memory क्रम CQ which is page aligned */
	ep->qp.cq_mem_size = hba->max_cqes * BNX2I_CQE_SIZE;
	ep->qp.cq_mem_size =
		(ep->qp.cq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.cq_pgtbl_size =
		(ep->qp.cq_mem_size / CNIC_PAGE_SIZE) * माप(व्योम *);
	ep->qp.cq_pgtbl_size =
		(ep->qp.cq_pgtbl_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.cq_pgtbl_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.cq_pgtbl_size,
				   &ep->qp.cq_pgtbl_phys, GFP_KERNEL);
	अगर (!ep->qp.cq_pgtbl_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc CQ PT memory %d\n",
				  ep->qp.cq_pgtbl_size);
		जाओ mem_alloc_err;
	पूर्ण

	/* Allocate memory area क्रम actual CQ element */
	ep->qp.cq_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.cq_mem_size,
				   &ep->qp.cq_phys, GFP_KERNEL);
	अगर (!ep->qp.cq_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc CQ BD memory %d\n",
				  ep->qp.cq_mem_size);
		जाओ mem_alloc_err;
	पूर्ण

	ep->qp.cq_first_qe = ep->qp.cq_virt;
	ep->qp.cq_prod_qe = ep->qp.cq_first_qe;
	ep->qp.cq_cons_qe = ep->qp.cq_first_qe;
	ep->qp.cq_last_qe = &ep->qp.cq_first_qe[hba->max_cqes - 1];
	ep->qp.cq_prod_idx = 0;
	ep->qp.cq_cons_idx = 0;
	ep->qp.cqe_left = hba->max_cqes;
	ep->qp.cqe_exp_seq_sn = ISCSI_INITIAL_SN;
	ep->qp.cqe_size = hba->max_cqes;

	/* Invalidate all EQ CQE index, req only क्रम 57710 */
	cq_db = (काष्ठा bnx2i_5771x_cq_db *) ep->qp.cq_pgtbl_virt;
	स_रखो(cq_db->sqn, 0xFF, माप(cq_db->sqn[0]) * BNX2X_MAX_CQS);

	/* Allocate page table memory क्रम RQ which is page aligned */
	ep->qp.rq_mem_size = hba->max_rqes * BNX2I_RQ_WQE_SIZE;
	ep->qp.rq_mem_size =
		(ep->qp.rq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.rq_pgtbl_size =
		(ep->qp.rq_mem_size / CNIC_PAGE_SIZE) * माप(व्योम *);
	ep->qp.rq_pgtbl_size =
		(ep->qp.rq_pgtbl_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.rq_pgtbl_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.rq_pgtbl_size,
				   &ep->qp.rq_pgtbl_phys, GFP_KERNEL);
	अगर (!ep->qp.rq_pgtbl_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc RQ PT mem %d\n",
				  ep->qp.rq_pgtbl_size);
		जाओ mem_alloc_err;
	पूर्ण

	/* Allocate memory area क्रम actual RQ element */
	ep->qp.rq_virt =
		dma_alloc_coherent(&hba->pcidev->dev, ep->qp.rq_mem_size,
				   &ep->qp.rq_phys, GFP_KERNEL);
	अगर (!ep->qp.rq_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unable to alloc RQ BD memory %d\n",
				  ep->qp.rq_mem_size);
		जाओ mem_alloc_err;
	पूर्ण

	ep->qp.rq_first_qe = ep->qp.rq_virt;
	ep->qp.rq_prod_qe = ep->qp.rq_first_qe;
	ep->qp.rq_cons_qe = ep->qp.rq_first_qe;
	ep->qp.rq_last_qe = &ep->qp.rq_first_qe[hba->max_rqes - 1];
	ep->qp.rq_prod_idx = 0x8000;
	ep->qp.rq_cons_idx = 0;
	ep->qp.rqe_left = hba->max_rqes;

	setup_qp_page_tables(ep);

	वापस 0;

mem_alloc_err:
	bnx2i_मुक्त_qp_resc(hba, ep);
	वापस -ENOMEM;
पूर्ण



/**
 * bnx2i_मुक्त_qp_resc - मुक्त memory resources held by QP
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @ep:	endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * Free QP resources - SQ/RQ/CQ memory and page tables.
 */
व्योम bnx2i_मुक्त_qp_resc(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	अगर (ep->qp.ctx_base) अणु
		iounmap(ep->qp.ctx_base);
		ep->qp.ctx_base = शून्य;
	पूर्ण
	/* Free SQ mem */
	अगर (ep->qp.sq_pgtbl_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.sq_pgtbl_size,
				  ep->qp.sq_pgtbl_virt, ep->qp.sq_pgtbl_phys);
		ep->qp.sq_pgtbl_virt = शून्य;
		ep->qp.sq_pgtbl_phys = 0;
	पूर्ण
	अगर (ep->qp.sq_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.sq_mem_size,
				  ep->qp.sq_virt, ep->qp.sq_phys);
		ep->qp.sq_virt = शून्य;
		ep->qp.sq_phys = 0;
	पूर्ण

	/* Free RQ mem */
	अगर (ep->qp.rq_pgtbl_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.rq_pgtbl_size,
				  ep->qp.rq_pgtbl_virt, ep->qp.rq_pgtbl_phys);
		ep->qp.rq_pgtbl_virt = शून्य;
		ep->qp.rq_pgtbl_phys = 0;
	पूर्ण
	अगर (ep->qp.rq_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.rq_mem_size,
				  ep->qp.rq_virt, ep->qp.rq_phys);
		ep->qp.rq_virt = शून्य;
		ep->qp.rq_phys = 0;
	पूर्ण

	/* Free CQ mem */
	अगर (ep->qp.cq_pgtbl_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.cq_pgtbl_size,
				  ep->qp.cq_pgtbl_virt, ep->qp.cq_pgtbl_phys);
		ep->qp.cq_pgtbl_virt = शून्य;
		ep->qp.cq_pgtbl_phys = 0;
	पूर्ण
	अगर (ep->qp.cq_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, ep->qp.cq_mem_size,
				  ep->qp.cq_virt, ep->qp.cq_phys);
		ep->qp.cq_virt = शून्य;
		ep->qp.cq_phys = 0;
	पूर्ण
पूर्ण


/**
 * bnx2i_send_fw_iscsi_init_msg - initiates initial handshake with iscsi f/w
 * @hba:	adapter काष्ठाure poपूर्णांकer
 *
 * Send करोwn iscsi_init KWQEs which initiates the initial handshake with the f/w
 * 	This results in iSCSi support validation and on-chip context manager
 * 	initialization.  Firmware completes this handshake with a CQE carrying
 * 	the result of iscsi support validation. Parameter carried by
 * 	iscsi init request determines the number of offloaded connection and
 * 	tolerance level क्रम iscsi protocol violation this hba/chip can support
 */
पूर्णांक bnx2i_send_fw_iscsi_init_msg(काष्ठा bnx2i_hba *hba)
अणु
	काष्ठा kwqe *kwqe_arr[3];
	काष्ठा iscsi_kwqe_init1 iscsi_init;
	काष्ठा iscsi_kwqe_init2 iscsi_init2;
	पूर्णांक rc = 0;
	u64 mask64;

	स_रखो(&iscsi_init, 0x00, माप(काष्ठा iscsi_kwqe_init1));
	स_रखो(&iscsi_init2, 0x00, माप(काष्ठा iscsi_kwqe_init2));

	bnx2i_adjust_qp_size(hba);

	iscsi_init.flags =
		(CNIC_PAGE_BITS - 8) << ISCSI_KWQE_INIT1_PAGE_SIZE_SHIFT;
	अगर (en_tcp_dack)
		iscsi_init.flags |= ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE;
	iscsi_init.reserved0 = 0;
	iscsi_init.num_cqs = 1;
	iscsi_init.hdr.op_code = ISCSI_KWQE_OPCODE_INIT1;
	iscsi_init.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);

	iscsi_init.dummy_buffer_addr_lo = (u32) hba->dummy_buf_dma;
	iscsi_init.dummy_buffer_addr_hi =
		(u32) ((u64) hba->dummy_buf_dma >> 32);

	hba->num_ccell = hba->max_sqes >> 1;
	hba->ctx_ccell_tasks =
			((hba->num_ccell & 0xFFFF) | (hba->max_sqes << 16));
	iscsi_init.num_ccells_per_conn = hba->num_ccell;
	iscsi_init.num_tasks_per_conn = hba->max_sqes;
	iscsi_init.sq_wqes_per_page = CNIC_PAGE_SIZE / BNX2I_SQ_WQE_SIZE;
	iscsi_init.sq_num_wqes = hba->max_sqes;
	iscsi_init.cq_log_wqes_per_page =
		(u8) bnx2i_घातer_of2(CNIC_PAGE_SIZE / BNX2I_CQE_SIZE);
	iscsi_init.cq_num_wqes = hba->max_cqes;
	iscsi_init.cq_num_pages = (hba->max_cqes * BNX2I_CQE_SIZE +
				   (CNIC_PAGE_SIZE - 1)) / CNIC_PAGE_SIZE;
	iscsi_init.sq_num_pages = (hba->max_sqes * BNX2I_SQ_WQE_SIZE +
				   (CNIC_PAGE_SIZE - 1)) / CNIC_PAGE_SIZE;
	iscsi_init.rq_buffer_size = BNX2I_RQ_WQE_SIZE;
	iscsi_init.rq_num_wqes = hba->max_rqes;


	iscsi_init2.hdr.op_code = ISCSI_KWQE_OPCODE_INIT2;
	iscsi_init2.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);
	iscsi_init2.max_cq_sqn = hba->max_cqes * 2 + 1;
	mask64 = 0x0ULL;
	mask64 |= (
		/* CISCO MDS */
		(1UL <<
		  ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_TTT_NOT_RSRV) |
		/* HP MSA1510i */
		(1UL <<
		  ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_EXP_DATASN) |
		/* EMC */
		(1ULL << ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_LUN));
	अगर (error_mask1) अणु
		iscsi_init2.error_bit_map[0] = error_mask1;
		mask64 ^= (u32)(mask64);
		mask64 |= error_mask1;
	पूर्ण अन्यथा
		iscsi_init2.error_bit_map[0] = (u32) mask64;

	अगर (error_mask2) अणु
		iscsi_init2.error_bit_map[1] = error_mask2;
		mask64 &= 0xffffffff;
		mask64 |= ((u64)error_mask2 << 32);
	पूर्ण अन्यथा
		iscsi_init2.error_bit_map[1] = (u32) (mask64 >> 32);

	iscsi_error_mask = mask64;

	kwqe_arr[0] = (काष्ठा kwqe *) &iscsi_init;
	kwqe_arr[1] = (काष्ठा kwqe *) &iscsi_init2;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, 2);
	वापस rc;
पूर्ण


/**
 * bnx2i_process_scsi_cmd_resp - this function handles scsi cmd completion.
 * @session:	iscsi session
 * @bnx2i_conn:	bnx2i connection
 * @cqe:	poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process SCSI CMD Response CQE & complete the request to SCSI-ML
 */
पूर्णांक bnx2i_process_scsi_cmd_resp(काष्ठा iscsi_session *session,
				काष्ठा bnx2i_conn *bnx2i_conn,
				काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा bnx2i_hba *hba = bnx2i_conn->hba;
	काष्ठा bnx2i_cmd_response *resp_cqe;
	काष्ठा bnx2i_cmd *bnx2i_cmd;
	काष्ठा iscsi_task *task;
	काष्ठा iscsi_scsi_rsp *hdr;
	u32 datalen = 0;

	resp_cqe = (काष्ठा bnx2i_cmd_response *)cqe;
	spin_lock_bh(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 resp_cqe->itt & ISCSI_CMD_RESPONSE_INDEX);
	अगर (!task)
		जाओ fail;

	bnx2i_cmd = task->dd_data;

	अगर (bnx2i_cmd->req.op_attr & ISCSI_CMD_REQUEST_READ) अणु
		conn->datain_pdus_cnt +=
			resp_cqe->task_stat.पढ़ो_stat.num_data_ins;
		conn->rxdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.पढ़ो_stat.num_data_ins);
		ADD_STATS_64(hba, rx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
	पूर्ण अन्यथा अणु
		conn->dataout_pdus_cnt +=
			resp_cqe->task_stat.ग_लिखो_stat.num_data_outs;
		conn->r2t_pdus_cnt +=
			resp_cqe->task_stat.ग_लिखो_stat.num_r2ts;
		conn->txdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, tx_pdus,
			     resp_cqe->task_stat.ग_लिखो_stat.num_data_outs);
		ADD_STATS_64(hba, tx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.ग_लिखो_stat.num_r2ts);
	पूर्ण
	bnx2i_iscsi_unmap_sg_list(bnx2i_cmd);

	hdr = (काष्ठा iscsi_scsi_rsp *)task->hdr;
	resp_cqe = (काष्ठा bnx2i_cmd_response *)cqe;
	hdr->opcode = resp_cqe->op_code;
	hdr->max_cmdsn = cpu_to_be32(resp_cqe->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(resp_cqe->exp_cmd_sn);
	hdr->response = resp_cqe->response;
	hdr->cmd_status = resp_cqe->status;
	hdr->flags = resp_cqe->response_flags;
	hdr->residual_count = cpu_to_be32(resp_cqe->residual_count);

	अगर (resp_cqe->op_code == ISCSI_OP_SCSI_DATA_IN)
		जाओ करोne;

	अगर (resp_cqe->status == SAM_STAT_CHECK_CONDITION) अणु
		datalen = resp_cqe->data_length;
		अगर (datalen < 2)
			जाओ करोne;

		अगर (datalen > BNX2I_RQ_WQE_SIZE) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
					  "sense data len %d > RQ sz\n",
					  datalen);
			datalen = BNX2I_RQ_WQE_SIZE;
		पूर्ण अन्यथा अगर (datalen > ISCSI_DEF_MAX_RECV_SEG_LEN) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
					  "sense data len %d > conn data\n",
					  datalen);
			datalen = ISCSI_DEF_MAX_RECV_SEG_LEN;
		पूर्ण

		bnx2i_get_rq_buf(bnx2i_cmd->conn, conn->data, datalen);
		bnx2i_put_rq_buf(bnx2i_cmd->conn, 1);
	पूर्ण

करोne:
	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)hdr,
			     conn->data, datalen);
fail:
	spin_unlock_bh(&session->back_lock);
	वापस 0;
पूर्ण


/**
 * bnx2i_process_login_resp - this function handles iscsi login response
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process Login Response CQE & complete it to खोलो-iscsi user daemon
 */
अटल पूर्णांक bnx2i_process_login_resp(काष्ठा iscsi_session *session,
				    काष्ठा bnx2i_conn *bnx2i_conn,
				    काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;
	काष्ठा bnx2i_login_response *login;
	काष्ठा iscsi_login_rsp *resp_hdr;
	पूर्णांक pld_len;
	पूर्णांक pad_len;

	login = (काष्ठा bnx2i_login_response *) cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 login->itt & ISCSI_LOGIN_RESPONSE_INDEX);
	अगर (!task)
		जाओ करोne;

	resp_hdr = (काष्ठा iscsi_login_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(resp_hdr, 0, माप(काष्ठा iscsi_hdr));
	resp_hdr->opcode = login->op_code;
	resp_hdr->flags = login->response_flags;
	resp_hdr->max_version = login->version_max;
	resp_hdr->active_version = login->version_active;
	resp_hdr->hlength = 0;

	hton24(resp_hdr->dlength, login->data_length);
	स_नकल(resp_hdr->isid, &login->isid_lo, 6);
	resp_hdr->tsih = cpu_to_be16(login->tsih);
	resp_hdr->itt = task->hdr->itt;
	resp_hdr->statsn = cpu_to_be32(login->stat_sn);
	resp_hdr->exp_cmdsn = cpu_to_be32(login->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(login->max_cmd_sn);
	resp_hdr->status_class = login->status_class;
	resp_hdr->status_detail = login->status_detail;
	pld_len = login->data_length;
	bnx2i_conn->gen_pdu.resp_wr_ptr =
					bnx2i_conn->gen_pdu.resp_buf + pld_len;

	pad_len = 0;
	अगर (pld_len & 0x3)
		pad_len = 4 - (pld_len % 4);

	अगर (pad_len) अणु
		पूर्णांक i = 0;
		क्रम (i = 0; i < pad_len; i++) अणु
			bnx2i_conn->gen_pdu.resp_wr_ptr[0] = 0;
			bnx2i_conn->gen_pdu.resp_wr_ptr++;
		पूर्ण
	पूर्ण

	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)resp_hdr,
		bnx2i_conn->gen_pdu.resp_buf,
		bnx2i_conn->gen_pdu.resp_wr_ptr - bnx2i_conn->gen_pdu.resp_buf);
करोne:
	spin_unlock(&session->back_lock);
	वापस 0;
पूर्ण


/**
 * bnx2i_process_text_resp - this function handles iscsi text response
 * @session:	iscsi session poपूर्णांकer
 * @bnx2i_conn:	iscsi connection poपूर्णांकer
 * @cqe:	poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI Text Response CQE&  complete it to खोलो-iscsi user daemon
 */
अटल पूर्णांक bnx2i_process_text_resp(काष्ठा iscsi_session *session,
				   काष्ठा bnx2i_conn *bnx2i_conn,
				   काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;
	काष्ठा bnx2i_text_response *text;
	काष्ठा iscsi_text_rsp *resp_hdr;
	पूर्णांक pld_len;
	पूर्णांक pad_len;

	text = (काष्ठा bnx2i_text_response *) cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn, text->itt & ISCSI_LOGIN_RESPONSE_INDEX);
	अगर (!task)
		जाओ करोne;

	resp_hdr = (काष्ठा iscsi_text_rsp *)&bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(resp_hdr, 0, माप(काष्ठा iscsi_hdr));
	resp_hdr->opcode = text->op_code;
	resp_hdr->flags = text->response_flags;
	resp_hdr->hlength = 0;

	hton24(resp_hdr->dlength, text->data_length);
	resp_hdr->itt = task->hdr->itt;
	resp_hdr->ttt = cpu_to_be32(text->ttt);
	resp_hdr->statsn = task->hdr->exp_statsn;
	resp_hdr->exp_cmdsn = cpu_to_be32(text->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(text->max_cmd_sn);
	pld_len = text->data_length;
	bnx2i_conn->gen_pdu.resp_wr_ptr = bnx2i_conn->gen_pdu.resp_buf +
					  pld_len;
	pad_len = 0;
	अगर (pld_len & 0x3)
		pad_len = 4 - (pld_len % 4);

	अगर (pad_len) अणु
		पूर्णांक i = 0;
		क्रम (i = 0; i < pad_len; i++) अणु
			bnx2i_conn->gen_pdu.resp_wr_ptr[0] = 0;
			bnx2i_conn->gen_pdu.resp_wr_ptr++;
		पूर्ण
	पूर्ण
	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)resp_hdr,
			     bnx2i_conn->gen_pdu.resp_buf,
			     bnx2i_conn->gen_pdu.resp_wr_ptr -
			     bnx2i_conn->gen_pdu.resp_buf);
करोne:
	spin_unlock(&session->back_lock);
	वापस 0;
पूर्ण


/**
 * bnx2i_process_पंचांगf_resp - this function handles iscsi TMF response
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI TMF Response CQE and wake up the driver eh thपढ़ो.
 */
अटल पूर्णांक bnx2i_process_पंचांगf_resp(काष्ठा iscsi_session *session,
				  काष्ठा bnx2i_conn *bnx2i_conn,
				  काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;
	काष्ठा bnx2i_पंचांगf_response *पंचांगf_cqe;
	काष्ठा iscsi_पंचांग_rsp *resp_hdr;

	पंचांगf_cqe = (काष्ठा bnx2i_पंचांगf_response *)cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 पंचांगf_cqe->itt & ISCSI_TMF_RESPONSE_INDEX);
	अगर (!task)
		जाओ करोne;

	resp_hdr = (काष्ठा iscsi_पंचांग_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(resp_hdr, 0, माप(काष्ठा iscsi_hdr));
	resp_hdr->opcode = पंचांगf_cqe->op_code;
	resp_hdr->max_cmdsn = cpu_to_be32(पंचांगf_cqe->max_cmd_sn);
	resp_hdr->exp_cmdsn = cpu_to_be32(पंचांगf_cqe->exp_cmd_sn);
	resp_hdr->itt = task->hdr->itt;
	resp_hdr->response = पंचांगf_cqe->response;

	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)resp_hdr, शून्य, 0);
करोne:
	spin_unlock(&session->back_lock);
	वापस 0;
पूर्ण

/**
 * bnx2i_process_logout_resp - this function handles iscsi logout response
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI Logout Response CQE & make function call to
 * notअगरy the user daemon.
 */
अटल पूर्णांक bnx2i_process_logout_resp(काष्ठा iscsi_session *session,
				     काष्ठा bnx2i_conn *bnx2i_conn,
				     काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;
	काष्ठा bnx2i_logout_response *logout;
	काष्ठा iscsi_logout_rsp *resp_hdr;

	logout = (काष्ठा bnx2i_logout_response *) cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 logout->itt & ISCSI_LOGOUT_RESPONSE_INDEX);
	अगर (!task)
		जाओ करोne;

	resp_hdr = (काष्ठा iscsi_logout_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(resp_hdr, 0, माप(काष्ठा iscsi_hdr));
	resp_hdr->opcode = logout->op_code;
	resp_hdr->flags = logout->response;
	resp_hdr->hlength = 0;

	resp_hdr->itt = task->hdr->itt;
	resp_hdr->statsn = task->hdr->exp_statsn;
	resp_hdr->exp_cmdsn = cpu_to_be32(logout->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(logout->max_cmd_sn);

	resp_hdr->t2रुको = cpu_to_be32(logout->समय_प्रकारo_रुको);
	resp_hdr->t2retain = cpu_to_be32(logout->समय_प्रकारo_retain);

	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)resp_hdr, शून्य, 0);

	bnx2i_conn->ep->state = EP_STATE_LOGOUT_RESP_RCVD;
करोne:
	spin_unlock(&session->back_lock);
	वापस 0;
पूर्ण

/**
 * bnx2i_process_nopin_local_cmpl - this function handles iscsi nopin CQE
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI NOPIN local completion CQE, मुक्तs IIT and command काष्ठाures
 */
अटल व्योम bnx2i_process_nopin_local_cmpl(काष्ठा iscsi_session *session,
					   काष्ठा bnx2i_conn *bnx2i_conn,
					   काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा bnx2i_nop_in_msg *nop_in;
	काष्ठा iscsi_task *task;

	nop_in = (काष्ठा bnx2i_nop_in_msg *)cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 nop_in->itt & ISCSI_NOP_IN_MSG_INDEX);
	अगर (task)
		__iscsi_put_task(task);
	spin_unlock(&session->back_lock);
पूर्ण

/**
 * bnx2i_unsol_pdu_adjust_rq - makes adjusपंचांगents to RQ after unsol pdu is recvd
 * @bnx2i_conn:	iscsi connection
 *
 * Firmware advances RQ producer index क्रम every unsolicited PDU even अगर
 *	payload data length is '0'. This function makes corresponding
 *	adjusपंचांगents on the driver side to match this f/w behavior
 */
अटल व्योम bnx2i_unsol_pdu_adjust_rq(काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	अक्षर dummy_rq_data[2];
	bnx2i_get_rq_buf(bnx2i_conn, dummy_rq_data, 1);
	bnx2i_put_rq_buf(bnx2i_conn, 1);
पूर्ण


/**
 * bnx2i_process_nopin_mesg - this function handles iscsi nopin CQE
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI target's proactive iSCSI NOPIN request
 */
अटल पूर्णांक bnx2i_process_nopin_mesg(काष्ठा iscsi_session *session,
				     काष्ठा bnx2i_conn *bnx2i_conn,
				     काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;
	काष्ठा bnx2i_nop_in_msg *nop_in;
	काष्ठा iscsi_nopin *hdr;
	पूर्णांक tgt_async_nop = 0;

	nop_in = (काष्ठा bnx2i_nop_in_msg *)cqe;

	spin_lock(&session->back_lock);
	hdr = (काष्ठा iscsi_nopin *)&bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(hdr, 0, माप(काष्ठा iscsi_hdr));
	hdr->opcode = nop_in->op_code;
	hdr->max_cmdsn = cpu_to_be32(nop_in->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(nop_in->exp_cmd_sn);
	hdr->ttt = cpu_to_be32(nop_in->ttt);

	अगर (nop_in->itt == (u16) RESERVED_ITT) अणु
		bnx2i_unsol_pdu_adjust_rq(bnx2i_conn);
		hdr->itt = RESERVED_ITT;
		tgt_async_nop = 1;
		जाओ करोne;
	पूर्ण

	/* this is a response to one of our nop-outs */
	task = iscsi_itt_to_task(conn,
			 (itt_t) (nop_in->itt & ISCSI_NOP_IN_MSG_INDEX));
	अगर (task) अणु
		hdr->flags = ISCSI_FLAG_CMD_FINAL;
		hdr->itt = task->hdr->itt;
		hdr->ttt = cpu_to_be32(nop_in->ttt);
		स_नकल(&hdr->lun, nop_in->lun, 8);
	पूर्ण
करोne:
	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)hdr, शून्य, 0);
	spin_unlock(&session->back_lock);

	वापस tgt_async_nop;
पूर्ण


/**
 * bnx2i_process_async_mesg - this function handles iscsi async message
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI ASYNC Message
 */
अटल व्योम bnx2i_process_async_mesg(काष्ठा iscsi_session *session,
				     काष्ठा bnx2i_conn *bnx2i_conn,
				     काष्ठा cqe *cqe)
अणु
	काष्ठा bnx2i_async_msg *async_cqe;
	काष्ठा iscsi_async *resp_hdr;
	u8 async_event;

	bnx2i_unsol_pdu_adjust_rq(bnx2i_conn);

	async_cqe = (काष्ठा bnx2i_async_msg *)cqe;
	async_event = async_cqe->async_event;

	अगर (async_event == ISCSI_ASYNC_MSG_SCSI_EVENT) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, bnx2i_conn->cls_conn->dd_data,
				  "async: scsi events not supported\n");
		वापस;
	पूर्ण

	spin_lock(&session->back_lock);
	resp_hdr = (काष्ठा iscsi_async *) &bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(resp_hdr, 0, माप(काष्ठा iscsi_hdr));
	resp_hdr->opcode = async_cqe->op_code;
	resp_hdr->flags = 0x80;

	स_नकल(&resp_hdr->lun, async_cqe->lun, 8);
	resp_hdr->exp_cmdsn = cpu_to_be32(async_cqe->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(async_cqe->max_cmd_sn);

	resp_hdr->async_event = async_cqe->async_event;
	resp_hdr->async_vcode = async_cqe->async_vcode;

	resp_hdr->param1 = cpu_to_be16(async_cqe->param1);
	resp_hdr->param2 = cpu_to_be16(async_cqe->param2);
	resp_hdr->param3 = cpu_to_be16(async_cqe->param3);

	__iscsi_complete_pdu(bnx2i_conn->cls_conn->dd_data,
			     (काष्ठा iscsi_hdr *)resp_hdr, शून्य, 0);
	spin_unlock(&session->back_lock);
पूर्ण


/**
 * bnx2i_process_reject_mesg - process iscsi reject pdu
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process iSCSI REJECT message
 */
अटल व्योम bnx2i_process_reject_mesg(काष्ठा iscsi_session *session,
				      काष्ठा bnx2i_conn *bnx2i_conn,
				      काष्ठा cqe *cqe)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा bnx2i_reject_msg *reject;
	काष्ठा iscsi_reject *hdr;

	reject = (काष्ठा bnx2i_reject_msg *) cqe;
	अगर (reject->data_length) अणु
		bnx2i_get_rq_buf(bnx2i_conn, conn->data, reject->data_length);
		bnx2i_put_rq_buf(bnx2i_conn, 1);
	पूर्ण अन्यथा
		bnx2i_unsol_pdu_adjust_rq(bnx2i_conn);

	spin_lock(&session->back_lock);
	hdr = (काष्ठा iscsi_reject *) &bnx2i_conn->gen_pdu.resp_hdr;
	स_रखो(hdr, 0, माप(काष्ठा iscsi_hdr));
	hdr->opcode = reject->op_code;
	hdr->reason = reject->reason;
	hton24(hdr->dlength, reject->data_length);
	hdr->max_cmdsn = cpu_to_be32(reject->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(reject->exp_cmd_sn);
	hdr->ffffffff = cpu_to_be32(RESERVED_ITT);
	__iscsi_complete_pdu(conn, (काष्ठा iscsi_hdr *)hdr, conn->data,
			     reject->data_length);
	spin_unlock(&session->back_lock);
पूर्ण

/**
 * bnx2i_process_cmd_cleanup_resp - process scsi command clean-up completion
 * @session:		iscsi session poपूर्णांकer
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * process command cleanup response CQE during conn shutकरोwn or error recovery
 */
अटल व्योम bnx2i_process_cmd_cleanup_resp(काष्ठा iscsi_session *session,
					   काष्ठा bnx2i_conn *bnx2i_conn,
					   काष्ठा cqe *cqe)
अणु
	काष्ठा bnx2i_cleanup_response *cmd_clean_rsp;
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_task *task;

	cmd_clean_rsp = (काष्ठा bnx2i_cleanup_response *)cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
			cmd_clean_rsp->itt & ISCSI_CLEANUP_RESPONSE_INDEX);
	अगर (!task)
		prपूर्णांकk(KERN_ALERT "bnx2i: cmd clean ITT %x not active\n",
			cmd_clean_rsp->itt & ISCSI_CLEANUP_RESPONSE_INDEX);
	spin_unlock(&session->back_lock);
	complete(&bnx2i_conn->cmd_cleanup_cmpl);
पूर्ण


/**
 * bnx2i_percpu_io_thपढ़ो - thपढ़ो per cpu क्रम ios
 *
 * @arg:	ptr to bnx2i_percpu_info काष्ठाure
 */
पूर्णांक bnx2i_percpu_io_thपढ़ो(व्योम *arg)
अणु
	काष्ठा bnx2i_percpu_s *p = arg;
	काष्ठा bnx2i_work *work, *पंचांगp;
	LIST_HEAD(work_list);

	set_user_nice(current, MIN_NICE);

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_bh(&p->p_work_lock);
		जबतक (!list_empty(&p->work_list)) अणु
			list_splice_init(&p->work_list, &work_list);
			spin_unlock_bh(&p->p_work_lock);

			list_क्रम_each_entry_safe(work, पंचांगp, &work_list, list) अणु
				list_del_init(&work->list);
				/* work allocated in the bh, मुक्तd here */
				bnx2i_process_scsi_cmd_resp(work->session,
							    work->bnx2i_conn,
							    &work->cqe);
				atomic_dec(&work->bnx2i_conn->work_cnt);
				kमुक्त(work);
			पूर्ण
			spin_lock_bh(&p->p_work_lock);
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_bh(&p->p_work_lock);
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण


/**
 * bnx2i_queue_scsi_cmd_resp - queue cmd completion to the percpu thपढ़ो
 * @session:		iscsi session
 * @bnx2i_conn:		bnx2i connection
 * @cqe:		poपूर्णांकer to newly DMA'ed CQE entry क्रम processing
 *
 * this function is called by generic KCQ handler to queue all pending cmd
 * completion CQEs
 *
 * The implementation is to queue the cmd response based on the
 * last recorded command क्रम the given connection.  The
 * cpu_id माला_लो recorded upon task_xmit.  No out-of-order completion!
 */
अटल पूर्णांक bnx2i_queue_scsi_cmd_resp(काष्ठा iscsi_session *session,
				     काष्ठा bnx2i_conn *bnx2i_conn,
				     काष्ठा bnx2i_nop_in_msg *cqe)
अणु
	काष्ठा bnx2i_work *bnx2i_work = शून्य;
	काष्ठा bnx2i_percpu_s *p = शून्य;
	काष्ठा iscsi_task *task;
	काष्ठा scsi_cmnd *sc;
	पूर्णांक rc = 0;

	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(bnx2i_conn->cls_conn->dd_data,
				 cqe->itt & ISCSI_CMD_RESPONSE_INDEX);
	अगर (!task || !task->sc) अणु
		spin_unlock(&session->back_lock);
		वापस -EINVAL;
	पूर्ण
	sc = task->sc;

	spin_unlock(&session->back_lock);

	p = &per_cpu(bnx2i_percpu, blk_mq_rq_cpu(sc->request));
	spin_lock(&p->p_work_lock);
	अगर (unlikely(!p->iothपढ़ो)) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण
	/* Alloc and copy to the cqe */
	bnx2i_work = kzalloc(माप(काष्ठा bnx2i_work), GFP_ATOMIC);
	अगर (bnx2i_work) अणु
		INIT_LIST_HEAD(&bnx2i_work->list);
		bnx2i_work->session = session;
		bnx2i_work->bnx2i_conn = bnx2i_conn;
		स_नकल(&bnx2i_work->cqe, cqe, माप(काष्ठा cqe));
		list_add_tail(&bnx2i_work->list, &p->work_list);
		atomic_inc(&bnx2i_conn->work_cnt);
		wake_up_process(p->iothपढ़ो);
		spin_unlock(&p->p_work_lock);
		जाओ करोne;
	पूर्ण अन्यथा
		rc = -ENOMEM;
err:
	spin_unlock(&p->p_work_lock);
	bnx2i_process_scsi_cmd_resp(session, bnx2i_conn, (काष्ठा cqe *)cqe);
करोne:
	वापस rc;
पूर्ण


/**
 * bnx2i_process_new_cqes - process newly DMA'ed CQE's
 * @bnx2i_conn:		bnx2i connection
 *
 * this function is called by generic KCQ handler to process all pending CQE's
 */
अटल पूर्णांक bnx2i_process_new_cqes(काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	काष्ठा iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा bnx2i_hba *hba = bnx2i_conn->hba;
	काष्ठा qp_info *qp;
	काष्ठा bnx2i_nop_in_msg *nopin;
	पूर्णांक tgt_async_msg;
	पूर्णांक cqe_cnt = 0;

	अगर (bnx2i_conn->ep == शून्य)
		वापस 0;

	qp = &bnx2i_conn->ep->qp;

	अगर (!qp->cq_virt) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): cq resr freed in bh execution!",
		       hba->netdev->name);
		जाओ out;
	पूर्ण
	जबतक (1) अणु
		nopin = (काष्ठा bnx2i_nop_in_msg *) qp->cq_cons_qe;
		अगर (nopin->cq_req_sn != qp->cqe_exp_seq_sn)
			अवरोध;

		अगर (unlikely(test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx))) अणु
			अगर (nopin->op_code == ISCSI_OP_NOOP_IN &&
			    nopin->itt == (u16) RESERVED_ITT) अणु
				prपूर्णांकk(KERN_ALERT "bnx2i: Unsolicited "
				       "NOP-In detected for suspended "
				       "connection dev=%s!\n",
				       hba->netdev->name);
				bnx2i_unsol_pdu_adjust_rq(bnx2i_conn);
				जाओ cqe_out;
			पूर्ण
			अवरोध;
		पूर्ण
		tgt_async_msg = 0;

		चयन (nopin->op_code) अणु
		हाल ISCSI_OP_SCSI_CMD_RSP:
		हाल ISCSI_OP_SCSI_DATA_IN:
			/* Run the kthपढ़ो engine only क्रम data cmds
			   All other cmds will be completed in this bh! */
			bnx2i_queue_scsi_cmd_resp(session, bnx2i_conn, nopin);
			जाओ करोne;
		हाल ISCSI_OP_LOGIN_RSP:
			bnx2i_process_login_resp(session, bnx2i_conn,
						 qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OP_SCSI_TMFUNC_RSP:
			bnx2i_process_पंचांगf_resp(session, bnx2i_conn,
					       qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OP_TEXT_RSP:
			bnx2i_process_text_resp(session, bnx2i_conn,
						qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OP_LOGOUT_RSP:
			bnx2i_process_logout_resp(session, bnx2i_conn,
						  qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OP_NOOP_IN:
			अगर (bnx2i_process_nopin_mesg(session, bnx2i_conn,
						     qp->cq_cons_qe))
				tgt_async_msg = 1;
			अवरोध;
		हाल ISCSI_OPCODE_NOPOUT_LOCAL_COMPLETION:
			bnx2i_process_nopin_local_cmpl(session, bnx2i_conn,
						       qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OP_ASYNC_EVENT:
			bnx2i_process_async_mesg(session, bnx2i_conn,
						 qp->cq_cons_qe);
			tgt_async_msg = 1;
			अवरोध;
		हाल ISCSI_OP_REJECT:
			bnx2i_process_reject_mesg(session, bnx2i_conn,
						  qp->cq_cons_qe);
			अवरोध;
		हाल ISCSI_OPCODE_CLEANUP_RESPONSE:
			bnx2i_process_cmd_cleanup_resp(session, bnx2i_conn,
						       qp->cq_cons_qe);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ALERT "bnx2i: unknown opcode 0x%x\n",
					  nopin->op_code);
		पूर्ण

		ADD_STATS_64(hba, rx_pdus, 1);
		ADD_STATS_64(hba, rx_bytes, nopin->data_length);
करोne:
		अगर (!tgt_async_msg) अणु
			अगर (!atomic_पढ़ो(&bnx2i_conn->ep->num_active_cmds))
				prपूर्णांकk(KERN_ALERT "bnx2i (%s): no active cmd! "
				       "op 0x%x\n",
				       hba->netdev->name,
				       nopin->op_code);
			अन्यथा
				atomic_dec(&bnx2i_conn->ep->num_active_cmds);
		पूर्ण
cqe_out:
		/* clear out in production version only, till beta keep opcode
		 * field पूर्णांकact, will be helpful in debugging (context dump)
		 * nopin->op_code = 0;
		 */
		cqe_cnt++;
		qp->cqe_exp_seq_sn++;
		अगर (qp->cqe_exp_seq_sn == (qp->cqe_size * 2 + 1))
			qp->cqe_exp_seq_sn = ISCSI_INITIAL_SN;

		अगर (qp->cq_cons_qe == qp->cq_last_qe) अणु
			qp->cq_cons_qe = qp->cq_first_qe;
			qp->cq_cons_idx = 0;
		पूर्ण अन्यथा अणु
			qp->cq_cons_qe++;
			qp->cq_cons_idx++;
		पूर्ण
	पूर्ण
out:
	वापस cqe_cnt;
पूर्ण

/**
 * bnx2i_fastpath_notअगरication - process global event queue (KCQ)
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @new_cqe_kcqe:	poपूर्णांकer to newly DMA'ed KCQE entry
 *
 * Fast path event notअगरication handler, KCQ entry carries context id
 *	of the connection that has 1 or more pending CQ entries
 */
अटल व्योम bnx2i_fastpath_notअगरication(काष्ठा bnx2i_hba *hba,
					काष्ठा iscsi_kcqe *new_cqe_kcqe)
अणु
	काष्ठा bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;
	पूर्णांक nxt_idx;

	iscsi_cid = new_cqe_kcqe->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_from_id(hba, iscsi_cid);

	अगर (!bnx2i_conn) अणु
		prपूर्णांकk(KERN_ALERT "cid #%x not valid\n", iscsi_cid);
		वापस;
	पूर्ण
	अगर (!bnx2i_conn->ep) अणु
		prपूर्णांकk(KERN_ALERT "cid #%x - ep not bound\n", iscsi_cid);
		वापस;
	पूर्ण

	bnx2i_process_new_cqes(bnx2i_conn);
	nxt_idx = bnx2i_arm_cq_event_coalescing(bnx2i_conn->ep,
						CNIC_ARM_CQE_FP);
	अगर (nxt_idx && nxt_idx == bnx2i_process_new_cqes(bnx2i_conn))
		bnx2i_arm_cq_event_coalescing(bnx2i_conn->ep, CNIC_ARM_CQE_FP);
पूर्ण


/**
 * bnx2i_process_update_conn_cmpl - process iscsi conn update completion KCQE
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @update_kcqe:	kcqe poपूर्णांकer
 *
 * CONN_UPDATE completion handler, this completes iSCSI connection FFP migration
 */
अटल व्योम bnx2i_process_update_conn_cmpl(काष्ठा bnx2i_hba *hba,
					   काष्ठा iscsi_kcqe *update_kcqe)
अणु
	काष्ठा bnx2i_conn *conn;
	u32 iscsi_cid;

	iscsi_cid = update_kcqe->iscsi_conn_id;
	conn = bnx2i_get_conn_from_id(hba, iscsi_cid);

	अगर (!conn) अणु
		prपूर्णांकk(KERN_ALERT "conn_update: cid %x not valid\n", iscsi_cid);
		वापस;
	पूर्ण
	अगर (!conn->ep) अणु
		prपूर्णांकk(KERN_ALERT "cid %x does not have ep bound\n", iscsi_cid);
		वापस;
	पूर्ण

	अगर (update_kcqe->completion_status) अणु
		prपूर्णांकk(KERN_ALERT "request failed cid %x\n", iscsi_cid);
		conn->ep->state = EP_STATE_ULP_UPDATE_FAILED;
	पूर्ण अन्यथा
		conn->ep->state = EP_STATE_ULP_UPDATE_COMPL;

	wake_up_पूर्णांकerruptible(&conn->ep->ofld_रुको);
पूर्ण


/**
 * bnx2i_recovery_que_add_conn - add connection to recovery queue
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @bnx2i_conn:		iscsi connection
 *
 * Add connection to recovery queue and schedule adapter eh worker
 */
अटल व्योम bnx2i_recovery_que_add_conn(काष्ठा bnx2i_hba *hba,
					काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	iscsi_conn_failure(bnx2i_conn->cls_conn->dd_data,
			   ISCSI_ERR_CONN_FAILED);
पूर्ण


/**
 * bnx2i_process_tcp_error - process error notअगरication on a given connection
 *
 * @hba: 		adapter काष्ठाure poपूर्णांकer
 * @tcp_err: 		tcp error kcqe poपूर्णांकer
 *
 * handles tcp level error notअगरications from FW.
 */
अटल व्योम bnx2i_process_tcp_error(काष्ठा bnx2i_hba *hba,
				    काष्ठा iscsi_kcqe *tcp_err)
अणु
	काष्ठा bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;

	iscsi_cid = tcp_err->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_from_id(hba, iscsi_cid);

	अगर (!bnx2i_conn) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i - cid 0x%x not valid\n", iscsi_cid);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_ALERT "bnx2i - cid 0x%x had TCP errors, error code 0x%x\n",
			  iscsi_cid, tcp_err->completion_status);
	bnx2i_recovery_que_add_conn(bnx2i_conn->hba, bnx2i_conn);
पूर्ण


/**
 * bnx2i_process_iscsi_error - process error notअगरication on a given connection
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @iscsi_err:		iscsi error kcqe poपूर्णांकer
 *
 * handles iscsi error notअगरications from the FW. Firmware based in initial
 *	handshake classअगरies iscsi protocol / TCP rfc violation पूर्णांकo either
 *	warning or error indications. If indication is of "Error" type, driver
 *	will initiate session recovery क्रम that connection/session. For
 *	"Warning" type indication, driver will put out a प्रणाली log message
 *	(there will be only one message क्रम each type क्रम the lअगरe of the
 *	session, this is to aव्योम un-necessarily overloading the प्रणाली)
 */
अटल व्योम bnx2i_process_iscsi_error(काष्ठा bnx2i_hba *hba,
				      काष्ठा iscsi_kcqe *iscsi_err)
अणु
	काष्ठा bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;
	स्थिर अक्षर *additional_notice = "";
	स्थिर अक्षर *message;
	पूर्णांक need_recovery;
	u64 err_mask64;

	iscsi_cid = iscsi_err->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_from_id(hba, iscsi_cid);
	अगर (!bnx2i_conn) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i - cid 0x%x not valid\n", iscsi_cid);
		वापस;
	पूर्ण

	err_mask64 = (0x1ULL << iscsi_err->completion_status);

	अगर (err_mask64 & iscsi_error_mask) अणु
		need_recovery = 0;
		message = "iscsi_warning";
	पूर्ण अन्यथा अणु
		need_recovery = 1;
		message = "iscsi_error";
	पूर्ण

	चयन (iscsi_err->completion_status) अणु
	हाल ISCSI_KCQE_COMPLETION_STATUS_HDR_DIG_ERR:
		additional_notice = "hdr digest err";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_DATA_DIG_ERR:
		additional_notice = "data digest err";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_OPCODE:
		additional_notice = "wrong opcode rcvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_AHS_LEN:
		additional_notice = "AHS len > 0 rcvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_ITT:
		additional_notice = "invalid ITT rcvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_STATSN:
		additional_notice = "wrong StatSN rcvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_EXP_DATASN:
		additional_notice = "wrong DataSN rcvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T:
		additional_notice = "pend R2T violation";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_0:
		additional_notice = "ERL0, UO";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_1:
		additional_notice = "ERL0, U1";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_2:
		additional_notice = "ERL0, U2";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_3:
		additional_notice = "ERL0, U3";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_4:
		additional_notice = "ERL0, U4";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_5:
		additional_notice = "ERL0, U5";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_6:
		additional_notice = "ERL0, U6";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REMAIN_RCV_LEN:
		additional_notice = "invalid resi len";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_MAX_RCV_PDU_LEN:
		additional_notice = "MRDSL violation";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_F_BIT_ZERO:
		additional_notice = "F-bit not set";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_TTT_NOT_RSRV:
		additional_notice = "invalid TTT";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATASN:
		additional_notice = "invalid DataSN";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REMAIN_BURST_LEN:
		additional_notice = "burst len violation";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_BUFFER_OFF:
		additional_notice = "buf offset violation";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_LUN:
		additional_notice = "invalid LUN field";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_R2TSN:
		additional_notice = "invalid R2TSN field";
		अवरोध;
#घोषणा BNX2I_ERR_DESIRED_DATA_TRNS_LEN_0 	\
	ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_0
	हाल BNX2I_ERR_DESIRED_DATA_TRNS_LEN_0:
		additional_notice = "invalid cmd len1";
		अवरोध;
#घोषणा BNX2I_ERR_DESIRED_DATA_TRNS_LEN_1 	\
	ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_1
	हाल BNX2I_ERR_DESIRED_DATA_TRNS_LEN_1:
		additional_notice = "invalid cmd len2";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T_EXCEED:
		additional_notice = "pend r2t exceeds MaxOutstandingR2T value";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_TTT_IS_RSRV:
		additional_notice = "TTT is rsvd";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_MAX_BURST_LEN:
		additional_notice = "MBL violation";
		अवरोध;
#घोषणा BNX2I_ERR_DATA_SEG_LEN_NOT_ZERO 	\
	ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATA_SEG_LEN_NOT_ZERO
	हाल BNX2I_ERR_DATA_SEG_LEN_NOT_ZERO:
		additional_notice = "data seg len != 0";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REJECT_PDU_LEN:
		additional_notice = "reject pdu len error";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_ASYNC_PDU_LEN:
		additional_notice = "async pdu len error";
		अवरोध;
	हाल ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_NOPIN_PDU_LEN:
		additional_notice = "nopin pdu len error";
		अवरोध;
#घोषणा BNX2_ERR_PEND_R2T_IN_CLEANUP			\
	ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T_IN_CLEANUP
	हाल BNX2_ERR_PEND_R2T_IN_CLEANUP:
		additional_notice = "pend r2t in cleanup";
		अवरोध;

	हाल ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_IP_FRAGMENT:
		additional_notice = "IP fragments rcvd";
		अवरोध;
	हाल ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_IP_OPTIONS:
		additional_notice = "IP options error";
		अवरोध;
	हाल ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_URGENT_FLAG:
		additional_notice = "urgent flag error";
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ALERT "iscsi_err - unknown err %x\n",
				  iscsi_err->completion_status);
	पूर्ण

	अगर (need_recovery) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT,
				  bnx2i_conn->cls_conn->dd_data,
				  "bnx2i: %s - %s\n",
				  message, additional_notice);

		iscsi_conn_prपूर्णांकk(KERN_ALERT,
				  bnx2i_conn->cls_conn->dd_data,
				  "conn_err - hostno %d conn %p, "
				  "iscsi_cid %x cid %x\n",
				  bnx2i_conn->hba->shost->host_no,
				  bnx2i_conn, bnx2i_conn->ep->ep_iscsi_cid,
				  bnx2i_conn->ep->ep_cid);
		bnx2i_recovery_que_add_conn(bnx2i_conn->hba, bnx2i_conn);
	पूर्ण अन्यथा
		अगर (!test_and_set_bit(iscsi_err->completion_status,
				      (व्योम *) &bnx2i_conn->violation_notअगरied))
			iscsi_conn_prपूर्णांकk(KERN_ALERT,
					  bnx2i_conn->cls_conn->dd_data,
					  "bnx2i: %s - %s\n",
					  message, additional_notice);
पूर्ण


/**
 * bnx2i_process_conn_destroy_cmpl - process iscsi conn destroy completion
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @conn_destroy:	conn destroy kcqe poपूर्णांकer
 *
 * handles connection destroy completion request.
 */
अटल व्योम bnx2i_process_conn_destroy_cmpl(काष्ठा bnx2i_hba *hba,
					    काष्ठा iscsi_kcqe *conn_destroy)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep;

	ep = bnx2i_find_ep_in_destroy_list(hba, conn_destroy->iscsi_conn_id);
	अगर (!ep) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i_conn_destroy_cmpl: no pending "
				  "offload request, unexpected completion\n");
		वापस;
	पूर्ण

	अगर (hba != ep->hba) अणु
		prपूर्णांकk(KERN_ALERT "conn destroy- error hba mis-match\n");
		वापस;
	पूर्ण

	अगर (conn_destroy->completion_status) अणु
		prपूर्णांकk(KERN_ALERT "conn_destroy_cmpl: op failed\n");
		ep->state = EP_STATE_CLEANUP_FAILED;
	पूर्ण अन्यथा
		ep->state = EP_STATE_CLEANUP_CMPL;
	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण


/**
 * bnx2i_process_ofld_cmpl - process initial iscsi conn offload completion
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @ofld_kcqe:		conn offload kcqe poपूर्णांकer
 *
 * handles initial connection offload completion, ep_connect() thपढ़ो is
 *	woken-up to जारी with LLP connect process
 */
अटल व्योम bnx2i_process_ofld_cmpl(काष्ठा bnx2i_hba *hba,
				    काष्ठा iscsi_kcqe *ofld_kcqe)
अणु
	u32 cid_addr;
	काष्ठा bnx2i_endpoपूर्णांक *ep;

	ep = bnx2i_find_ep_in_ofld_list(hba, ofld_kcqe->iscsi_conn_id);
	अगर (!ep) अणु
		prपूर्णांकk(KERN_ALERT "ofld_cmpl: no pend offload request\n");
		वापस;
	पूर्ण

	अगर (hba != ep->hba) अणु
		prपूर्णांकk(KERN_ALERT "ofld_cmpl: error hba mis-match\n");
		वापस;
	पूर्ण

	अगर (ofld_kcqe->completion_status) अणु
		ep->state = EP_STATE_OFLD_FAILED;
		अगर (ofld_kcqe->completion_status ==
		    ISCSI_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE)
			prपूर्णांकk(KERN_ALERT "bnx2i (%s): ofld1 cmpl - unable "
				"to allocate iSCSI context resources\n",
				hba->netdev->name);
		अन्यथा अगर (ofld_kcqe->completion_status ==
			 ISCSI_KCQE_COMPLETION_STATUS_INVALID_OPCODE)
			prपूर्णांकk(KERN_ALERT "bnx2i (%s): ofld1 cmpl - invalid "
				"opcode\n", hba->netdev->name);
		अन्यथा अगर (ofld_kcqe->completion_status ==
			 ISCSI_KCQE_COMPLETION_STATUS_CID_BUSY)
			/* error status code valid only क्रम 5771x chipset */
			ep->state = EP_STATE_OFLD_FAILED_CID_BUSY;
		अन्यथा
			prपूर्णांकk(KERN_ALERT "bnx2i (%s): ofld1 cmpl - invalid "
				"error code %d\n", hba->netdev->name,
				ofld_kcqe->completion_status);
	पूर्ण अन्यथा अणु
		ep->state = EP_STATE_OFLD_COMPL;
		cid_addr = ofld_kcqe->iscsi_conn_context_id;
		ep->ep_cid = cid_addr;
		ep->qp.ctx_base = शून्य;
	पूर्ण
	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण

/**
 * bnx2i_indicate_kcqe - process iscsi conn update completion KCQE
 * @context:		adapter काष्ठाure poपूर्णांकer
 * @kcqe:		kcqe poपूर्णांकer
 * @num_cqe:		number of kcqes to process
 *
 * Generic KCQ event handler/dispatcher
 */
अटल व्योम bnx2i_indicate_kcqe(व्योम *context, काष्ठा kcqe *kcqe[],
				u32 num_cqe)
अणु
	काष्ठा bnx2i_hba *hba = context;
	पूर्णांक i = 0;
	काष्ठा iscsi_kcqe *ikcqe = शून्य;

	जबतक (i < num_cqe) अणु
		ikcqe = (काष्ठा iscsi_kcqe *) kcqe[i++];

		अगर (ikcqe->op_code ==
		    ISCSI_KCQE_OPCODE_CQ_EVENT_NOTIFICATION)
			bnx2i_fastpath_notअगरication(hba, ikcqe);
		अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_OFFLOAD_CONN)
			bnx2i_process_ofld_cmpl(hba, ikcqe);
		अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_UPDATE_CONN)
			bnx2i_process_update_conn_cmpl(hba, ikcqe);
		अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_INIT) अणु
			अगर (ikcqe->completion_status !=
			    ISCSI_KCQE_COMPLETION_STATUS_SUCCESS)
				bnx2i_iscsi_license_error(hba, ikcqe->\
							  completion_status);
			अन्यथा अणु
				set_bit(ADAPTER_STATE_UP, &hba->adapter_state);
				bnx2i_get_link_state(hba);
				prपूर्णांकk(KERN_INFO "bnx2i [%.2x:%.2x.%.2x]: "
						 "ISCSI_INIT passed\n",
						 (u8)hba->pcidev->bus->number,
						 hba->pci_devno,
						 (u8)hba->pci_func);


			पूर्ण
		पूर्ण अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_DESTROY_CONN)
			bnx2i_process_conn_destroy_cmpl(hba, ikcqe);
		अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_ISCSI_ERROR)
			bnx2i_process_iscsi_error(hba, ikcqe);
		अन्यथा अगर (ikcqe->op_code == ISCSI_KCQE_OPCODE_TCP_ERROR)
			bnx2i_process_tcp_error(hba, ikcqe);
		अन्यथा
			prपूर्णांकk(KERN_ALERT "bnx2i: unknown opcode 0x%x\n",
					  ikcqe->op_code);
	पूर्ण
पूर्ण


/**
 * bnx2i_indicate_netevent - Generic netdev event handler
 * @context:	adapter काष्ठाure poपूर्णांकer
 * @event:	event type
 * @vlan_id:	vlans id - associated vlan id with this event
 *
 * Handles four netdev events, NETDEV_UP, NETDEV_DOWN,
 *	NETDEV_GOING_DOWN and NETDEV_CHANGE
 */
अटल व्योम bnx2i_indicate_netevent(व्योम *context, अचिन्हित दीर्घ event,
				    u16 vlan_id)
अणु
	काष्ठा bnx2i_hba *hba = context;

	/* Ignore all netevent coming from vlans */
	अगर (vlan_id != 0)
		वापस;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state))
			bnx2i_send_fw_iscsi_init_msg(hba);
		अवरोध;
	हाल NETDEV_DOWN:
		clear_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
		अवरोध;
	हाल NETDEV_GOING_DOWN:
		set_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		iscsi_host_क्रम_each_session(hba->shost,
					    bnx2i_drop_session);
		अवरोध;
	हाल NETDEV_CHANGE:
		bnx2i_get_link_state(hba);
		अवरोध;
	शेष:
		;
	पूर्ण
पूर्ण


/**
 * bnx2i_cm_connect_cmpl - process iscsi conn establishment completion
 * @cm_sk: 		cnic sock काष्ठाure poपूर्णांकer
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to
 *	indicate completion of option-2 TCP connect request.
 */
अटल व्योम bnx2i_cm_connect_cmpl(काष्ठा cnic_sock *cm_sk)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = (काष्ठा bnx2i_endpoपूर्णांक *) cm_sk->context;

	अगर (test_bit(ADAPTER_STATE_GOING_DOWN, &ep->hba->adapter_state))
		ep->state = EP_STATE_CONNECT_FAILED;
	अन्यथा अगर (test_bit(SK_F_OFFLD_COMPLETE, &cm_sk->flags))
		ep->state = EP_STATE_CONNECT_COMPL;
	अन्यथा
		ep->state = EP_STATE_CONNECT_FAILED;

	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण


/**
 * bnx2i_cm_बंद_cmpl - process tcp conn बंद completion
 * @cm_sk:	cnic sock काष्ठाure poपूर्णांकer
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to
 *	indicate completion of option-2 graceful TCP connect shutकरोwn
 */
अटल व्योम bnx2i_cm_बंद_cmpl(काष्ठा cnic_sock *cm_sk)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = (काष्ठा bnx2i_endpoपूर्णांक *) cm_sk->context;

	ep->state = EP_STATE_DISCONN_COMPL;
	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण


/**
 * bnx2i_cm_पात_cmpl - process पातive tcp conn tearकरोwn completion
 * @cm_sk:	cnic sock काष्ठाure poपूर्णांकer
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to
 *	indicate completion of option-2 पातive TCP connect termination
 */
अटल व्योम bnx2i_cm_पात_cmpl(काष्ठा cnic_sock *cm_sk)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = (काष्ठा bnx2i_endpoपूर्णांक *) cm_sk->context;

	ep->state = EP_STATE_DISCONN_COMPL;
	wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
पूर्ण


/**
 * bnx2i_cm_remote_बंद - process received TCP FIN
 * @cm_sk:	cnic sock काष्ठाure poपूर्णांकer
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to indicate
 *	async TCP events such as FIN
 */
अटल व्योम bnx2i_cm_remote_बंद(काष्ठा cnic_sock *cm_sk)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = (काष्ठा bnx2i_endpoपूर्णांक *) cm_sk->context;

	ep->state = EP_STATE_TCP_FIN_RCVD;
	अगर (ep->conn)
		bnx2i_recovery_que_add_conn(ep->hba, ep->conn);
पूर्ण

/**
 * bnx2i_cm_remote_पात - process TCP RST and start conn cleanup
 * @cm_sk:	cnic sock काष्ठाure poपूर्णांकer
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to
 *	indicate async TCP events (RST) sent by the peer.
 */
अटल व्योम bnx2i_cm_remote_पात(काष्ठा cnic_sock *cm_sk)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *ep = (काष्ठा bnx2i_endpoपूर्णांक *) cm_sk->context;
	u32 old_state = ep->state;

	ep->state = EP_STATE_TCP_RST_RCVD;
	अगर (old_state == EP_STATE_DISCONN_START)
		wake_up_पूर्णांकerruptible(&ep->ofld_रुको);
	अन्यथा
		अगर (ep->conn)
			bnx2i_recovery_que_add_conn(ep->hba, ep->conn);
पूर्ण


अटल पूर्णांक bnx2i_send_nl_mesg(व्योम *context, u32 msg_type,
			      अक्षर *buf, u16 buflen)
अणु
	काष्ठा bnx2i_hba *hba = context;
	पूर्णांक rc;

	अगर (!hba)
		वापस -ENODEV;

	rc = iscsi_offload_mesg(hba->shost, &bnx2i_iscsi_transport,
				msg_type, buf, buflen);
	अगर (rc)
		prपूर्णांकk(KERN_ALERT "bnx2i: private nl message send error\n");

	वापस rc;
पूर्ण


/*
 * bnx2i_cnic_cb - global ढाँचा of bnx2i - cnic driver पूर्णांकerface काष्ठाure
 *			carrying callback function poपूर्णांकers
 */
काष्ठा cnic_ulp_ops bnx2i_cnic_cb = अणु
	.cnic_init = bnx2i_ulp_init,
	.cnic_निकास = bnx2i_ulp_निकास,
	.cnic_start = bnx2i_start,
	.cnic_stop = bnx2i_stop,
	.indicate_kcqes = bnx2i_indicate_kcqe,
	.indicate_netevent = bnx2i_indicate_netevent,
	.cm_connect_complete = bnx2i_cm_connect_cmpl,
	.cm_बंद_complete = bnx2i_cm_बंद_cmpl,
	.cm_पात_complete = bnx2i_cm_पात_cmpl,
	.cm_remote_बंद = bnx2i_cm_remote_बंद,
	.cm_remote_पात = bnx2i_cm_remote_पात,
	.iscsi_nl_send_msg = bnx2i_send_nl_mesg,
	.cnic_get_stats = bnx2i_get_stats,
	.owner = THIS_MODULE
पूर्ण;


/**
 * bnx2i_map_ep_dbell_regs - map connection करोorbell रेजिस्टरs
 * @ep: bnx2i endpoपूर्णांक
 *
 * maps connection's SQ and RQ करोorbell रेजिस्टरs, 5706/5708/5709 hosts these
 *	रेजिस्टर in BAR #0. Whereas in 57710 these रेजिस्टर are accessed by
 *	mapping BAR #1
 */
पूर्णांक bnx2i_map_ep_dbell_regs(काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	u32 cid_num;
	u32 reg_off;
	u32 first_l4l5;
	u32 ctx_sz;
	u32 config2;
	resource_माप_प्रकार reg_base;

	cid_num = bnx2i_get_cid_num(ep);

	अगर (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) अणु
		reg_base = pci_resource_start(ep->hba->pcidev,
					      BNX2X_DOORBELL_PCI_BAR);
		reg_off = (1 << BNX2X_DB_SHIFT) * (cid_num & 0x1FFFF);
		ep->qp.ctx_base = ioremap(reg_base + reg_off, 4);
		अगर (!ep->qp.ctx_base)
			वापस -ENOMEM;
		जाओ arm_cq;
	पूर्ण

	अगर ((test_bit(BNX2I_NX2_DEV_5709, &ep->hba->cnic_dev_type)) &&
	    (ep->hba->mail_queue_access == BNX2I_MQ_BIN_MODE)) अणु
		config2 = REG_RD(ep->hba, BNX2_MQ_CONFIG2);
		first_l4l5 = config2 & BNX2_MQ_CONFIG2_FIRST_L4L5;
		ctx_sz = (config2 & BNX2_MQ_CONFIG2_CONT_SZ) >> 3;
		अगर (ctx_sz)
			reg_off = CTX_OFFSET + MAX_CID_CNT * MB_KERNEL_CTX_SIZE
				  + BNX2I_570X_PAGE_SIZE_DEFAULT *
				  (((cid_num - first_l4l5) / ctx_sz) + 256);
		अन्यथा
			reg_off = CTX_OFFSET + (MB_KERNEL_CTX_SIZE * cid_num);
	पूर्ण अन्यथा
		/* 5709 device in normal node and 5706/5708 devices */
		reg_off = CTX_OFFSET + (MB_KERNEL_CTX_SIZE * cid_num);

	ep->qp.ctx_base = ioremap(ep->hba->reg_base + reg_off,
					  MB_KERNEL_CTX_SIZE);
	अगर (!ep->qp.ctx_base)
		वापस -ENOMEM;

arm_cq:
	bnx2i_arm_cq_event_coalescing(ep, CNIC_ARM_CQE);
	वापस 0;
पूर्ण
