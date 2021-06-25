<शैली गुरु>
/*
 * bnx2i_iscsi.c: QLogic NetXtreme II iSCSI driver.
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

#समावेश <linux/slab.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/libiscsi.h>
#समावेश "bnx2i.h"

काष्ठा scsi_transport_ढाँचा *bnx2i_scsi_xport_ढाँचा;
काष्ठा iscsi_transport bnx2i_iscsi_transport;
अटल काष्ठा scsi_host_ढाँचा bnx2i_host_ढाँचा;

/*
 * Global endpoपूर्णांक resource info
 */
अटल DEFINE_SPINLOCK(bnx2i_resc_lock); /* protects global resources */

DECLARE_PER_CPU(काष्ठा bnx2i_percpu_s, bnx2i_percpu);

अटल पूर्णांक bnx2i_adapter_पढ़ोy(काष्ठा bnx2i_hba *hba)
अणु
	पूर्णांक retval = 0;

	अगर (!hba || !test_bit(ADAPTER_STATE_UP, &hba->adapter_state) ||
	    test_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state) ||
	    test_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state))
		retval = -EPERM;
	वापस retval;
पूर्ण

/**
 * bnx2i_get_ग_लिखो_cmd_bd_idx - identअगरies various BD bookmarks
 * @cmd:		iscsi cmd काष्ठा poपूर्णांकer
 * @buf_off:		असलolute buffer offset
 * @start_bd_off:	u32 poपूर्णांकer to वापस the offset within the BD
 *			indicated by 'start_bd_idx' on which 'buf_off' falls
 * @start_bd_idx:	index of the BD on which 'buf_off' falls
 *
 * identअगरies & marks various bd info क्रम scsi command's imm data,
 * unsolicited data and the first solicited data seq.
 */
अटल व्योम bnx2i_get_ग_लिखो_cmd_bd_idx(काष्ठा bnx2i_cmd *cmd, u32 buf_off,
				       u32 *start_bd_off, u32 *start_bd_idx)
अणु
	काष्ठा iscsi_bd *bd_tbl = cmd->io_tbl.bd_tbl;
	u32 cur_offset = 0;
	u32 cur_bd_idx = 0;

	अगर (buf_off) अणु
		जबतक (buf_off >= (cur_offset + bd_tbl->buffer_length)) अणु
			cur_offset += bd_tbl->buffer_length;
			cur_bd_idx++;
			bd_tbl++;
		पूर्ण
	पूर्ण

	*start_bd_off = buf_off - cur_offset;
	*start_bd_idx = cur_bd_idx;
पूर्ण

/**
 * bnx2i_setup_ग_लिखो_cmd_bd_info - sets up BD various inक्रमmation
 * @task:	transport layer's cmd काष्ठा poपूर्णांकer
 *
 * identअगरies & marks various bd info क्रम scsi command's immediate data,
 * unsolicited data and first solicited data seq which includes BD start
 * index & BD buf off. his function takes पूर्णांकo account iscsi parameter such
 * as immediate data and unsolicited data is support on this connection.
 */
अटल व्योम bnx2i_setup_ग_लिखो_cmd_bd_info(काष्ठा iscsi_task *task)
अणु
	काष्ठा bnx2i_cmd *cmd = task->dd_data;
	u32 start_bd_offset;
	u32 start_bd_idx;
	u32 buffer_offset = 0;
	u32 cmd_len = cmd->req.total_data_transfer_length;

	/* अगर ImmediateData is turned off & IntialR2T is turned on,
	 * there will be no immediate or unsolicited data, just वापस.
	 */
	अगर (!iscsi_task_has_unsol_data(task) && !task->imm_count)
		वापस;

	/* Immediate data */
	buffer_offset += task->imm_count;
	अगर (task->imm_count == cmd_len)
		वापस;

	अगर (iscsi_task_has_unsol_data(task)) अणु
		bnx2i_get_ग_लिखो_cmd_bd_idx(cmd, buffer_offset,
					   &start_bd_offset, &start_bd_idx);
		cmd->req.ud_buffer_offset = start_bd_offset;
		cmd->req.ud_start_bd_index = start_bd_idx;
		buffer_offset += task->unsol_r2t.data_length;
	पूर्ण

	अगर (buffer_offset != cmd_len) अणु
		bnx2i_get_ग_लिखो_cmd_bd_idx(cmd, buffer_offset,
					   &start_bd_offset, &start_bd_idx);
		अगर ((start_bd_offset > task->conn->session->first_burst) ||
		    (start_bd_idx > scsi_sg_count(cmd->scsi_cmd))) अणु
			पूर्णांक i = 0;

			iscsi_conn_prपूर्णांकk(KERN_ALERT, task->conn,
					  "bnx2i- error, buf offset 0x%x "
					  "bd_valid %d use_sg %d\n",
					  buffer_offset, cmd->io_tbl.bd_valid,
					  scsi_sg_count(cmd->scsi_cmd));
			क्रम (i = 0; i < cmd->io_tbl.bd_valid; i++)
				iscsi_conn_prपूर्णांकk(KERN_ALERT, task->conn,
						  "bnx2i err, bd[%d]: len %x\n",
						  i, cmd->io_tbl.bd_tbl[i].\
						  buffer_length);
		पूर्ण
		cmd->req.sd_buffer_offset = start_bd_offset;
		cmd->req.sd_start_bd_index = start_bd_idx;
	पूर्ण
पूर्ण



/**
 * bnx2i_map_scsi_sg - maps IO buffer and prepares the BD table
 * @hba:	adapter instance
 * @cmd:	iscsi cmd काष्ठा poपूर्णांकer
 *
 * map SG list
 */
अटल पूर्णांक bnx2i_map_scsi_sg(काष्ठा bnx2i_hba *hba, काष्ठा bnx2i_cmd *cmd)
अणु
	काष्ठा scsi_cmnd *sc = cmd->scsi_cmd;
	काष्ठा iscsi_bd *bd = cmd->io_tbl.bd_tbl;
	काष्ठा scatterlist *sg;
	पूर्णांक byte_count = 0;
	पूर्णांक bd_count = 0;
	पूर्णांक sg_count;
	पूर्णांक sg_len;
	u64 addr;
	पूर्णांक i;

	BUG_ON(scsi_sg_count(sc) > ISCSI_MAX_BDS_PER_CMD);

	sg_count = scsi_dma_map(sc);

	scsi_क्रम_each_sg(sc, sg, sg_count, i) अणु
		sg_len = sg_dma_len(sg);
		addr = (u64) sg_dma_address(sg);
		bd[bd_count].buffer_addr_lo = addr & 0xffffffff;
		bd[bd_count].buffer_addr_hi = addr >> 32;
		bd[bd_count].buffer_length = sg_len;
		bd[bd_count].flags = 0;
		अगर (bd_count == 0)
			bd[bd_count].flags = ISCSI_BD_FIRST_IN_BD_CHAIN;

		byte_count += sg_len;
		bd_count++;
	पूर्ण

	अगर (bd_count)
		bd[bd_count - 1].flags |= ISCSI_BD_LAST_IN_BD_CHAIN;

	BUG_ON(byte_count != scsi_bufflen(sc));
	वापस bd_count;
पूर्ण

/**
 * bnx2i_iscsi_map_sg_list - maps SG list
 * @cmd:	iscsi cmd काष्ठा poपूर्णांकer
 *
 * creates BD list table क्रम the command
 */
अटल व्योम bnx2i_iscsi_map_sg_list(काष्ठा bnx2i_cmd *cmd)
अणु
	पूर्णांक bd_count;

	bd_count  = bnx2i_map_scsi_sg(cmd->conn->hba, cmd);
	अगर (!bd_count) अणु
		काष्ठा iscsi_bd *bd = cmd->io_tbl.bd_tbl;

		bd[0].buffer_addr_lo = bd[0].buffer_addr_hi = 0;
		bd[0].buffer_length = bd[0].flags = 0;
	पूर्ण
	cmd->io_tbl.bd_valid = bd_count;
पूर्ण


/**
 * bnx2i_iscsi_unmap_sg_list - unmaps SG list
 * @cmd:	iscsi cmd काष्ठा poपूर्णांकer
 *
 * unmap IO buffers and invalidate the BD table
 */
व्योम bnx2i_iscsi_unmap_sg_list(काष्ठा bnx2i_cmd *cmd)
अणु
	काष्ठा scsi_cmnd *sc = cmd->scsi_cmd;

	अगर (cmd->io_tbl.bd_valid && sc) अणु
		scsi_dma_unmap(sc);
		cmd->io_tbl.bd_valid = 0;
	पूर्ण
पूर्ण

अटल व्योम bnx2i_setup_cmd_wqe_ढाँचा(काष्ठा bnx2i_cmd *cmd)
अणु
	स_रखो(&cmd->req, 0x00, माप(cmd->req));
	cmd->req.op_code = 0xFF;
	cmd->req.bd_list_addr_lo = (u32) cmd->io_tbl.bd_tbl_dma;
	cmd->req.bd_list_addr_hi =
		(u32) ((u64) cmd->io_tbl.bd_tbl_dma >> 32);

पूर्ण


/**
 * bnx2i_bind_conn_to_iscsi_cid - bind conn काष्ठाure to 'iscsi_cid'
 * @hba:	poपूर्णांकer to adapter instance
 * @bnx2i_conn:	poपूर्णांकer to iscsi connection
 * @iscsi_cid:	iscsi context ID, range 0 - (MAX_CONN - 1)
 *
 * update iscsi cid table entry with connection poपूर्णांकer. This enables
 *	driver to quickly get hold of connection काष्ठाure poपूर्णांकer in
 *	completion/पूर्णांकerrupt thपढ़ो using iscsi context ID
 */
अटल पूर्णांक bnx2i_bind_conn_to_iscsi_cid(काष्ठा bnx2i_hba *hba,
					काष्ठा bnx2i_conn *bnx2i_conn,
					u32 iscsi_cid)
अणु
	अगर (hba && hba->cid_que.conn_cid_tbl[iscsi_cid]) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, bnx2i_conn->cls_conn->dd_data,
				 "conn bind - entry #%d not free\n", iscsi_cid);
		वापस -EBUSY;
	पूर्ण

	hba->cid_que.conn_cid_tbl[iscsi_cid] = bnx2i_conn;
	वापस 0;
पूर्ण


/**
 * bnx2i_get_conn_from_id - maps an iscsi cid to corresponding conn ptr
 * @hba:	poपूर्णांकer to adapter instance
 * @iscsi_cid:	iscsi context ID, range 0 - (MAX_CONN - 1)
 */
काष्ठा bnx2i_conn *bnx2i_get_conn_from_id(काष्ठा bnx2i_hba *hba,
					  u16 iscsi_cid)
अणु
	अगर (!hba->cid_que.conn_cid_tbl) अणु
		prपूर्णांकk(KERN_ERR "bnx2i: ERROR - missing conn<->cid table\n");
		वापस शून्य;

	पूर्ण अन्यथा अगर (iscsi_cid >= hba->max_active_conns) अणु
		prपूर्णांकk(KERN_ERR "bnx2i: wrong cid #%d\n", iscsi_cid);
		वापस शून्य;
	पूर्ण
	वापस hba->cid_que.conn_cid_tbl[iscsi_cid];
पूर्ण


/**
 * bnx2i_alloc_iscsi_cid - allocates a iscsi_cid from मुक्त pool
 * @hba:	poपूर्णांकer to adapter instance
 */
अटल u32 bnx2i_alloc_iscsi_cid(काष्ठा bnx2i_hba *hba)
अणु
	पूर्णांक idx;

	अगर (!hba->cid_que.cid_मुक्त_cnt)
		वापस -1;

	idx = hba->cid_que.cid_q_cons_idx;
	hba->cid_que.cid_q_cons_idx++;
	अगर (hba->cid_que.cid_q_cons_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_cons_idx = 0;

	hba->cid_que.cid_मुक्त_cnt--;
	वापस hba->cid_que.cid_que[idx];
पूर्ण


/**
 * bnx2i_मुक्त_iscsi_cid - वापसs tcp port to मुक्त list
 * @hba: 		poपूर्णांकer to adapter instance
 * @iscsi_cid:		iscsi context ID to मुक्त
 */
अटल व्योम bnx2i_मुक्त_iscsi_cid(काष्ठा bnx2i_hba *hba, u16 iscsi_cid)
अणु
	पूर्णांक idx;

	अगर (iscsi_cid == (u16) -1)
		वापस;

	hba->cid_que.cid_मुक्त_cnt++;

	idx = hba->cid_que.cid_q_prod_idx;
	hba->cid_que.cid_que[idx] = iscsi_cid;
	hba->cid_que.conn_cid_tbl[iscsi_cid] = शून्य;
	hba->cid_que.cid_q_prod_idx++;
	अगर (hba->cid_que.cid_q_prod_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_prod_idx = 0;
पूर्ण


/**
 * bnx2i_setup_मुक्त_cid_que - sets up मुक्त iscsi cid queue
 * @hba:	poपूर्णांकer to adapter instance
 *
 * allocates memory क्रम iscsi cid queue & 'cid - conn ptr' mapping table,
 * 	and initialize table attributes
 */
अटल पूर्णांक bnx2i_setup_मुक्त_cid_que(काष्ठा bnx2i_hba *hba)
अणु
	पूर्णांक mem_size;
	पूर्णांक i;

	mem_size = hba->max_active_conns * माप(u32);
	mem_size = (mem_size + (PAGE_SIZE - 1)) & PAGE_MASK;

	hba->cid_que.cid_que_base = kदो_स्मृति(mem_size, GFP_KERNEL);
	अगर (!hba->cid_que.cid_que_base)
		वापस -ENOMEM;

	mem_size = hba->max_active_conns * माप(काष्ठा bnx2i_conn *);
	mem_size = (mem_size + (PAGE_SIZE - 1)) & PAGE_MASK;
	hba->cid_que.conn_cid_tbl = kदो_स्मृति(mem_size, GFP_KERNEL);
	अगर (!hba->cid_que.conn_cid_tbl) अणु
		kमुक्त(hba->cid_que.cid_que_base);
		hba->cid_que.cid_que_base = शून्य;
		वापस -ENOMEM;
	पूर्ण

	hba->cid_que.cid_que = (u32 *)hba->cid_que.cid_que_base;
	hba->cid_que.cid_q_prod_idx = 0;
	hba->cid_que.cid_q_cons_idx = 0;
	hba->cid_que.cid_q_max_idx = hba->max_active_conns;
	hba->cid_que.cid_मुक्त_cnt = hba->max_active_conns;

	क्रम (i = 0; i < hba->max_active_conns; i++) अणु
		hba->cid_que.cid_que[i] = i;
		hba->cid_que.conn_cid_tbl[i] = शून्य;
	पूर्ण
	वापस 0;
पूर्ण


/**
 * bnx2i_release_मुक्त_cid_que - releases 'iscsi_cid' queue resources
 * @hba:	poपूर्णांकer to adapter instance
 */
अटल व्योम bnx2i_release_मुक्त_cid_que(काष्ठा bnx2i_hba *hba)
अणु
	kमुक्त(hba->cid_que.cid_que_base);
	hba->cid_que.cid_que_base = शून्य;

	kमुक्त(hba->cid_que.conn_cid_tbl);
	hba->cid_que.conn_cid_tbl = शून्य;
पूर्ण


/**
 * bnx2i_alloc_ep - allocates ep काष्ठाure from global pool
 * @hba:	poपूर्णांकer to adapter instance
 *
 * routine allocates a मुक्त endpoपूर्णांक काष्ठाure from global pool and
 *	a tcp port to be used क्रम this connection.  Global resource lock,
 *	'bnx2i_resc_lock' is held जबतक accessing shared global data काष्ठाures
 */
अटल काष्ठा iscsi_endpoपूर्णांक *bnx2i_alloc_ep(काष्ठा bnx2i_hba *hba)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	u32 ec_भाग;

	ep = iscsi_create_endpoपूर्णांक(माप(*bnx2i_ep));
	अगर (!ep) अणु
		prपूर्णांकk(KERN_ERR "bnx2i: Could not allocate ep\n");
		वापस शून्य;
	पूर्ण

	bnx2i_ep = ep->dd_data;
	bnx2i_ep->cls_ep = ep;
	INIT_LIST_HEAD(&bnx2i_ep->link);
	bnx2i_ep->state = EP_STATE_IDLE;
	bnx2i_ep->ep_iscsi_cid = (u16) -1;
	bnx2i_ep->hba = hba;
	bnx2i_ep->hba_age = hba->age;

	ec_भाग = event_coal_भाग;
	जबतक (ec_भाग >>= 1)
		bnx2i_ep->ec_shअगरt += 1;

	hba->ofld_conns_active++;
	init_रुकोqueue_head(&bnx2i_ep->ofld_रुको);
	वापस ep;
पूर्ण


/**
 * bnx2i_मुक्त_ep - मुक्त endpoपूर्णांक
 * @ep:		poपूर्णांकer to iscsi endpoपूर्णांक काष्ठाure
 */
अटल व्योम bnx2i_मुक्त_ep(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep = ep->dd_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnx2i_resc_lock, flags);
	bnx2i_ep->state = EP_STATE_IDLE;
	bnx2i_ep->hba->ofld_conns_active--;

	अगर (bnx2i_ep->ep_iscsi_cid != (u16) -1)
		bnx2i_मुक्त_iscsi_cid(bnx2i_ep->hba, bnx2i_ep->ep_iscsi_cid);

	अगर (bnx2i_ep->conn) अणु
		bnx2i_ep->conn->ep = शून्य;
		bnx2i_ep->conn = शून्य;
	पूर्ण

	bnx2i_ep->hba = शून्य;
	spin_unlock_irqrestore(&bnx2i_resc_lock, flags);
	iscsi_destroy_endpoपूर्णांक(ep);
पूर्ण


/**
 * bnx2i_alloc_bdt - allocates buffer descriptor (BD) table क्रम the command
 * @hba:	adapter instance poपूर्णांकer
 * @session:	iscsi session poपूर्णांकer
 * @cmd:	iscsi command काष्ठाure
 */
अटल पूर्णांक bnx2i_alloc_bdt(काष्ठा bnx2i_hba *hba, काष्ठा iscsi_session *session,
			   काष्ठा bnx2i_cmd *cmd)
अणु
	काष्ठा io_bdt *io = &cmd->io_tbl;
	काष्ठा iscsi_bd *bd;

	io->bd_tbl = dma_alloc_coherent(&hba->pcidev->dev,
					ISCSI_MAX_BDS_PER_CMD * माप(*bd),
					&io->bd_tbl_dma, GFP_KERNEL);
	अगर (!io->bd_tbl) अणु
		iscsi_session_prपूर्णांकk(KERN_ERR, session, "Could not "
				     "allocate bdt.\n");
		वापस -ENOMEM;
	पूर्ण
	io->bd_valid = 0;
	वापस 0;
पूर्ण

/**
 * bnx2i_destroy_cmd_pool - destroys iscsi command pool and release BD table
 * @hba:	adapter instance poपूर्णांकer
 * @session:	iscsi session poपूर्णांकer
 */
अटल व्योम bnx2i_destroy_cmd_pool(काष्ठा bnx2i_hba *hba,
				   काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < session->cmds_max; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा bnx2i_cmd *cmd = task->dd_data;

		अगर (cmd->io_tbl.bd_tbl)
			dma_मुक्त_coherent(&hba->pcidev->dev,
					  ISCSI_MAX_BDS_PER_CMD *
					  माप(काष्ठा iscsi_bd),
					  cmd->io_tbl.bd_tbl,
					  cmd->io_tbl.bd_tbl_dma);
	पूर्ण

पूर्ण


/**
 * bnx2i_setup_cmd_pool - sets up iscsi command pool क्रम the session
 * @hba:	adapter instance poपूर्णांकer
 * @session:	iscsi session poपूर्णांकer
 */
अटल पूर्णांक bnx2i_setup_cmd_pool(काष्ठा bnx2i_hba *hba,
				काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < session->cmds_max; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा bnx2i_cmd *cmd = task->dd_data;

		task->hdr = &cmd->hdr;
		task->hdr_max = माप(काष्ठा iscsi_hdr);

		अगर (bnx2i_alloc_bdt(hba, session, cmd))
			जाओ मुक्त_bdts;
	पूर्ण

	वापस 0;

मुक्त_bdts:
	bnx2i_destroy_cmd_pool(hba, session);
	वापस -ENOMEM;
पूर्ण


/**
 * bnx2i_setup_mp_bdt - allocate BD table resources
 * @hba:	poपूर्णांकer to adapter काष्ठाure
 *
 * Allocate memory क्रम dummy buffer and associated BD
 * table to be used by middle path (MP) requests
 */
अटल पूर्णांक bnx2i_setup_mp_bdt(काष्ठा bnx2i_hba *hba)
अणु
	पूर्णांक rc = 0;
	काष्ठा iscsi_bd *mp_bdt;
	u64 addr;

	hba->mp_bd_tbl = dma_alloc_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					    &hba->mp_bd_dma, GFP_KERNEL);
	अगर (!hba->mp_bd_tbl) अणु
		prपूर्णांकk(KERN_ERR "unable to allocate Middle Path BDT\n");
		rc = -1;
		जाओ out;
	पूर्ण

	hba->dummy_buffer = dma_alloc_coherent(&hba->pcidev->dev,
					       CNIC_PAGE_SIZE,
					       &hba->dummy_buf_dma, GFP_KERNEL);
	अगर (!hba->dummy_buffer) अणु
		prपूर्णांकk(KERN_ERR "unable to alloc Middle Path Dummy Buffer\n");
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->mp_bd_tbl, hba->mp_bd_dma);
		hba->mp_bd_tbl = शून्य;
		rc = -1;
		जाओ out;
	पूर्ण

	mp_bdt = (काष्ठा iscsi_bd *) hba->mp_bd_tbl;
	addr = (अचिन्हित दीर्घ) hba->dummy_buf_dma;
	mp_bdt->buffer_addr_lo = addr & 0xffffffff;
	mp_bdt->buffer_addr_hi = addr >> 32;
	mp_bdt->buffer_length = CNIC_PAGE_SIZE;
	mp_bdt->flags = ISCSI_BD_LAST_IN_BD_CHAIN |
			ISCSI_BD_FIRST_IN_BD_CHAIN;
out:
	वापस rc;
पूर्ण


/**
 * bnx2i_मुक्त_mp_bdt - releases ITT back to मुक्त pool
 * @hba:	poपूर्णांकer to adapter instance
 *
 * मुक्त MP dummy buffer and associated BD table
 */
अटल व्योम bnx2i_मुक्त_mp_bdt(काष्ठा bnx2i_hba *hba)
अणु
	अगर (hba->mp_bd_tbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->mp_bd_tbl, hba->mp_bd_dma);
		hba->mp_bd_tbl = शून्य;
	पूर्ण
	अगर (hba->dummy_buffer) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->dummy_buffer, hba->dummy_buf_dma);
		hba->dummy_buffer = शून्य;
	पूर्ण
	वापस;
पूर्ण

/**
 * bnx2i_drop_session - notअगरies iscsid of connection error.
 * @cls_session:	iscsi cls session poपूर्णांकer
 *
 * This notअगरies iscsid that there is a error, so it can initiate
 * recovery.
 *
 * This relies on caller using the iscsi class iterator so the object
 * is refcounted and करोes not disapper from under us.
 */
व्योम bnx2i_drop_session(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_session_failure(cls_session->dd_data, ISCSI_ERR_CONN_FAILED);
पूर्ण

/**
 * bnx2i_ep_destroy_list_add - add an entry to EP destroy list
 * @hba:	poपूर्णांकer to adapter instance
 * @ep:		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * EP destroy queue manager
 */
अटल पूर्णांक bnx2i_ep_destroy_list_add(काष्ठा bnx2i_hba *hba,
				     काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_add_tail(&ep->link, &hba->ep_destroy_list);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);
	वापस 0;
पूर्ण

/**
 * bnx2i_ep_destroy_list_del - add an entry to EP destroy list
 *
 * @hba: 		poपूर्णांकer to adapter instance
 * @ep: 		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * EP destroy queue manager
 */
अटल पूर्णांक bnx2i_ep_destroy_list_del(काष्ठा bnx2i_hba *hba,
				     काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_del_init(&ep->link);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);

	वापस 0;
पूर्ण

/**
 * bnx2i_ep_ofld_list_add - add an entry to ep offload pending list
 * @hba:	poपूर्णांकer to adapter instance
 * @ep:		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * pending conn offload completion queue manager
 */
अटल पूर्णांक bnx2i_ep_ofld_list_add(काष्ठा bnx2i_hba *hba,
				  काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_add_tail(&ep->link, &hba->ep_ofld_list);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);
	वापस 0;
पूर्ण

/**
 * bnx2i_ep_ofld_list_del - add an entry to ep offload pending list
 * @hba: 		poपूर्णांकer to adapter instance
 * @ep: 		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * pending conn offload completion queue manager
 */
अटल पूर्णांक bnx2i_ep_ofld_list_del(काष्ठा bnx2i_hba *hba,
				  काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_del_init(&ep->link);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);
	वापस 0;
पूर्ण


/**
 * bnx2i_find_ep_in_ofld_list - find iscsi_cid in pending list of endpoपूर्णांकs
 *
 * @hba: 		poपूर्णांकer to adapter instance
 * @iscsi_cid:		iscsi context ID to find
 *
 */
काष्ठा bnx2i_endpoपूर्णांक *
bnx2i_find_ep_in_ofld_list(काष्ठा bnx2i_hba *hba, u32 iscsi_cid)
अणु
	काष्ठा list_head *list;
	काष्ठा list_head *पंचांगp;
	काष्ठा bnx2i_endpoपूर्णांक *ep = शून्य;

	पढ़ो_lock_bh(&hba->ep_rdwr_lock);
	list_क्रम_each_safe(list, पंचांगp, &hba->ep_ofld_list) अणु
		ep = (काष्ठा bnx2i_endpoपूर्णांक *)list;

		अगर (ep->ep_iscsi_cid == iscsi_cid)
			अवरोध;
		ep = शून्य;
	पूर्ण
	पढ़ो_unlock_bh(&hba->ep_rdwr_lock);

	अगर (!ep)
		prपूर्णांकk(KERN_ERR "l5 cid %d not found\n", iscsi_cid);
	वापस ep;
पूर्ण

/**
 * bnx2i_find_ep_in_destroy_list - find iscsi_cid in destroy list
 * @hba: 		poपूर्णांकer to adapter instance
 * @iscsi_cid:		iscsi context ID to find
 *
 */
काष्ठा bnx2i_endpoपूर्णांक *
bnx2i_find_ep_in_destroy_list(काष्ठा bnx2i_hba *hba, u32 iscsi_cid)
अणु
	काष्ठा list_head *list;
	काष्ठा list_head *पंचांगp;
	काष्ठा bnx2i_endpoपूर्णांक *ep = शून्य;

	पढ़ो_lock_bh(&hba->ep_rdwr_lock);
	list_क्रम_each_safe(list, पंचांगp, &hba->ep_destroy_list) अणु
		ep = (काष्ठा bnx2i_endpoपूर्णांक *)list;

		अगर (ep->ep_iscsi_cid == iscsi_cid)
			अवरोध;
		ep = शून्य;
	पूर्ण
	पढ़ो_unlock_bh(&hba->ep_rdwr_lock);

	अगर (!ep)
		prपूर्णांकk(KERN_ERR "l5 cid %d not found\n", iscsi_cid);

	वापस ep;
पूर्ण

/**
 * bnx2i_ep_active_list_add - add an entry to ep active list
 * @hba:	poपूर्णांकer to adapter instance
 * @ep:		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * current active conn queue manager
 */
अटल व्योम bnx2i_ep_active_list_add(काष्ठा bnx2i_hba *hba,
				     काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_add_tail(&ep->link, &hba->ep_active_list);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);
पूर्ण


/**
 * bnx2i_ep_active_list_del - deletes an entry to ep active list
 * @hba:	poपूर्णांकer to adapter instance
 * @ep:		poपूर्णांकer to endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * current active conn queue manager
 */
अटल व्योम bnx2i_ep_active_list_del(काष्ठा bnx2i_hba *hba,
				     काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	ग_लिखो_lock_bh(&hba->ep_rdwr_lock);
	list_del_init(&ep->link);
	ग_लिखो_unlock_bh(&hba->ep_rdwr_lock);
पूर्ण


/**
 * bnx2i_setup_host_queue_size - assigns shost->can_queue param
 * @hba:	poपूर्णांकer to adapter instance
 * @shost:	scsi host poपूर्णांकer
 *
 * Initializes 'can_queue' parameter based on how many outstanding commands
 * 	the device can handle. Each device 5708/5709/57710 has dअगरferent
 *	capabilities
 */
अटल व्योम bnx2i_setup_host_queue_size(काष्ठा bnx2i_hba *hba,
					काष्ठा Scsi_Host *shost)
अणु
	अगर (test_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5708;
	अन्यथा अगर (test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5709;
	अन्यथा अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_57710;
	अन्यथा
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5708;
पूर्ण


/**
 * bnx2i_alloc_hba - allocate and init adapter instance
 * @cnic:	cnic device poपूर्णांकer
 *
 * allocate & initialize adapter काष्ठाure and call other
 *	support routines to करो per adapter initialization
 */
काष्ठा bnx2i_hba *bnx2i_alloc_hba(काष्ठा cnic_dev *cnic)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा bnx2i_hba *hba;

	shost = iscsi_host_alloc(&bnx2i_host_ढाँचा, माप(*hba), 0);
	अगर (!shost)
		वापस शून्य;
	shost->dma_boundary = cnic->pcidev->dma_mask;
	shost->transportt = bnx2i_scsi_xport_ढाँचा;
	shost->max_id = ISCSI_MAX_CONNS_PER_HBA;
	shost->max_channel = 0;
	shost->max_lun = 512;
	shost->max_cmd_len = 16;

	hba = iscsi_host_priv(shost);
	hba->shost = shost;
	hba->netdev = cnic->netdev;
	/* Get PCI related inक्रमmation and update hba काष्ठा members */
	hba->pcidev = cnic->pcidev;
	pci_dev_get(hba->pcidev);
	hba->pci_did = hba->pcidev->device;
	hba->pci_vid = hba->pcidev->venकरोr;
	hba->pci_sdid = hba->pcidev->subप्रणाली_device;
	hba->pci_svid = hba->pcidev->subप्रणाली_venकरोr;
	hba->pci_func = PCI_FUNC(hba->pcidev->devfn);
	hba->pci_devno = PCI_SLOT(hba->pcidev->devfn);

	bnx2i_identअगरy_device(hba, cnic);
	bnx2i_setup_host_queue_size(hba, shost);

	hba->reg_base = pci_resource_start(hba->pcidev, 0);
	अगर (test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type)) अणु
		hba->regview = pci_iomap(hba->pcidev, 0, BNX2_MQ_CONFIG2);
		अगर (!hba->regview)
			जाओ ioreg_map_err;
	पूर्ण अन्यथा अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) अणु
		hba->regview = pci_iomap(hba->pcidev, 0, 4096);
		अगर (!hba->regview)
			जाओ ioreg_map_err;
	पूर्ण

	अगर (bnx2i_setup_mp_bdt(hba))
		जाओ mp_bdt_mem_err;

	INIT_LIST_HEAD(&hba->ep_ofld_list);
	INIT_LIST_HEAD(&hba->ep_active_list);
	INIT_LIST_HEAD(&hba->ep_destroy_list);
	rwlock_init(&hba->ep_rdwr_lock);

	hba->mtu_supported = BNX2I_MAX_MTU_SUPPORTED;

	/* dअगरferent values क्रम 5708/5709/57710 */
	hba->max_active_conns = ISCSI_MAX_CONNS_PER_HBA;

	अगर (bnx2i_setup_मुक्त_cid_que(hba))
		जाओ cid_que_err;

	/* SQ/RQ/CQ size can be changed via sysfx पूर्णांकerface */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) अणु
		अगर (sq_size && sq_size <= BNX2I_5770X_SQ_WQES_MAX)
			hba->max_sqes = sq_size;
		अन्यथा
			hba->max_sqes = BNX2I_5770X_SQ_WQES_DEFAULT;
	पूर्ण अन्यथा अणु	/* 5706/5708/5709 */
		अगर (sq_size && sq_size <= BNX2I_570X_SQ_WQES_MAX)
			hba->max_sqes = sq_size;
		अन्यथा
			hba->max_sqes = BNX2I_570X_SQ_WQES_DEFAULT;
	पूर्ण

	hba->max_rqes = rq_size;
	hba->max_cqes = hba->max_sqes + rq_size;
	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) अणु
		अगर (hba->max_cqes > BNX2I_5770X_CQ_WQES_MAX)
			hba->max_cqes = BNX2I_5770X_CQ_WQES_MAX;
	पूर्ण अन्यथा अगर (hba->max_cqes > BNX2I_570X_CQ_WQES_MAX)
		hba->max_cqes = BNX2I_570X_CQ_WQES_MAX;

	hba->num_ccell = hba->max_sqes / 2;

	spin_lock_init(&hba->lock);
	mutex_init(&hba->net_dev_lock);
	init_रुकोqueue_head(&hba->eh_रुको);
	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) अणु
		hba->hba_shutकरोwn_पंचांगo = 30 * HZ;
		hba->conn_tearकरोwn_पंचांगo = 20 * HZ;
		hba->conn_ctx_destroy_पंचांगo = 6 * HZ;
	पूर्ण अन्यथा अणु	/* 5706/5708/5709 */
		hba->hba_shutकरोwn_पंचांगo = 20 * HZ;
		hba->conn_tearकरोwn_पंचांगo = 10 * HZ;
		hba->conn_ctx_destroy_पंचांगo = 2 * HZ;
	पूर्ण

#अगर_घोषित CONFIG_32BIT
	spin_lock_init(&hba->stat_lock);
#पूर्ण_अगर
	स_रखो(&hba->stats, 0, माप(काष्ठा iscsi_stats_info));

	अगर (iscsi_host_add(shost, &hba->pcidev->dev))
		जाओ मुक्त_dump_mem;
	वापस hba;

मुक्त_dump_mem:
	bnx2i_release_मुक्त_cid_que(hba);
cid_que_err:
	bnx2i_मुक्त_mp_bdt(hba);
mp_bdt_mem_err:
	अगर (hba->regview) अणु
		pci_iounmap(hba->pcidev, hba->regview);
		hba->regview = शून्य;
	पूर्ण
ioreg_map_err:
	pci_dev_put(hba->pcidev);
	scsi_host_put(shost);
	वापस शून्य;
पूर्ण

/**
 * bnx2i_मुक्त_hba- releases hba काष्ठाure and resources held by the adapter
 * @hba:	poपूर्णांकer to adapter instance
 *
 * मुक्त adapter काष्ठाure and call various cleanup routines.
 */
व्योम bnx2i_मुक्त_hba(काष्ठा bnx2i_hba *hba)
अणु
	काष्ठा Scsi_Host *shost = hba->shost;

	iscsi_host_हटाओ(shost);
	INIT_LIST_HEAD(&hba->ep_ofld_list);
	INIT_LIST_HEAD(&hba->ep_active_list);
	INIT_LIST_HEAD(&hba->ep_destroy_list);

	अगर (hba->regview) अणु
		pci_iounmap(hba->pcidev, hba->regview);
		hba->regview = शून्य;
	पूर्ण
	pci_dev_put(hba->pcidev);
	bnx2i_मुक्त_mp_bdt(hba);
	bnx2i_release_मुक्त_cid_que(hba);
	iscsi_host_मुक्त(shost);
पूर्ण

/**
 * bnx2i_conn_मुक्त_login_resources - मुक्त DMA resources used क्रम login process
 * @hba:		poपूर्णांकer to adapter instance
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 *
 * Login related resources, mostly BDT & payload DMA memory is मुक्तd
 */
अटल व्योम bnx2i_conn_मुक्त_login_resources(काष्ठा bnx2i_hba *hba,
					    काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	अगर (bnx2i_conn->gen_pdu.resp_bd_tbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  bnx2i_conn->gen_pdu.resp_bd_tbl,
				  bnx2i_conn->gen_pdu.resp_bd_dma);
		bnx2i_conn->gen_pdu.resp_bd_tbl = शून्य;
	पूर्ण

	अगर (bnx2i_conn->gen_pdu.req_bd_tbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  bnx2i_conn->gen_pdu.req_bd_tbl,
				  bnx2i_conn->gen_pdu.req_bd_dma);
		bnx2i_conn->gen_pdu.req_bd_tbl = शून्य;
	पूर्ण

	अगर (bnx2i_conn->gen_pdu.resp_buf) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  bnx2i_conn->gen_pdu.resp_buf,
				  bnx2i_conn->gen_pdu.resp_dma_addr);
		bnx2i_conn->gen_pdu.resp_buf = शून्य;
	पूर्ण

	अगर (bnx2i_conn->gen_pdu.req_buf) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  bnx2i_conn->gen_pdu.req_buf,
				  bnx2i_conn->gen_pdu.req_dma_addr);
		bnx2i_conn->gen_pdu.req_buf = शून्य;
	पूर्ण
पूर्ण

/**
 * bnx2i_conn_alloc_login_resources - alloc DMA resources क्रम login/nop.
 * @hba:		poपूर्णांकer to adapter instance
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 *
 * Mgmt task DNA resources are allocated in this routine.
 */
अटल पूर्णांक bnx2i_conn_alloc_login_resources(काष्ठा bnx2i_hba *hba,
					    काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	/* Allocate memory क्रम login request/response buffers */
	bnx2i_conn->gen_pdu.req_buf =
		dma_alloc_coherent(&hba->pcidev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &bnx2i_conn->gen_pdu.req_dma_addr,
				   GFP_KERNEL);
	अगर (bnx2i_conn->gen_pdu.req_buf == शून्य)
		जाओ login_req_buf_failure;

	bnx2i_conn->gen_pdu.req_buf_size = 0;
	bnx2i_conn->gen_pdu.req_wr_ptr = bnx2i_conn->gen_pdu.req_buf;

	bnx2i_conn->gen_pdu.resp_buf =
		dma_alloc_coherent(&hba->pcidev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &bnx2i_conn->gen_pdu.resp_dma_addr,
				   GFP_KERNEL);
	अगर (bnx2i_conn->gen_pdu.resp_buf == शून्य)
		जाओ login_resp_buf_failure;

	bnx2i_conn->gen_pdu.resp_buf_size = ISCSI_DEF_MAX_RECV_SEG_LEN;
	bnx2i_conn->gen_pdu.resp_wr_ptr = bnx2i_conn->gen_pdu.resp_buf;

	bnx2i_conn->gen_pdu.req_bd_tbl =
		dma_alloc_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				   &bnx2i_conn->gen_pdu.req_bd_dma, GFP_KERNEL);
	अगर (bnx2i_conn->gen_pdu.req_bd_tbl == शून्य)
		जाओ login_req_bd_tbl_failure;

	bnx2i_conn->gen_pdu.resp_bd_tbl =
		dma_alloc_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				   &bnx2i_conn->gen_pdu.resp_bd_dma,
				   GFP_KERNEL);
	अगर (bnx2i_conn->gen_pdu.resp_bd_tbl == शून्य)
		जाओ login_resp_bd_tbl_failure;

	वापस 0;

login_resp_bd_tbl_failure:
	dma_मुक्त_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
			  bnx2i_conn->gen_pdu.req_bd_tbl,
			  bnx2i_conn->gen_pdu.req_bd_dma);
	bnx2i_conn->gen_pdu.req_bd_tbl = शून्य;

login_req_bd_tbl_failure:
	dma_मुक्त_coherent(&hba->pcidev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  bnx2i_conn->gen_pdu.resp_buf,
			  bnx2i_conn->gen_pdu.resp_dma_addr);
	bnx2i_conn->gen_pdu.resp_buf = शून्य;
login_resp_buf_failure:
	dma_मुक्त_coherent(&hba->pcidev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  bnx2i_conn->gen_pdu.req_buf,
			  bnx2i_conn->gen_pdu.req_dma_addr);
	bnx2i_conn->gen_pdu.req_buf = शून्य;
login_req_buf_failure:
	iscsi_conn_prपूर्णांकk(KERN_ERR, bnx2i_conn->cls_conn->dd_data,
			  "login resource alloc failed!!\n");
	वापस -ENOMEM;

पूर्ण


/**
 * bnx2i_iscsi_prep_generic_pdu_bd - prepares BD table.
 * @bnx2i_conn:		iscsi connection poपूर्णांकer
 *
 * Allocates buffers and BD tables beक्रमe shipping requests to cnic
 *	क्रम PDUs prepared by 'iscsid' daemon
 */
अटल व्योम bnx2i_iscsi_prep_generic_pdu_bd(काष्ठा bnx2i_conn *bnx2i_conn)
अणु
	काष्ठा iscsi_bd *bd_tbl;

	bd_tbl = (काष्ठा iscsi_bd *) bnx2i_conn->gen_pdu.req_bd_tbl;

	bd_tbl->buffer_addr_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.req_dma_addr >> 32);
	bd_tbl->buffer_addr_lo = (u32) bnx2i_conn->gen_pdu.req_dma_addr;
	bd_tbl->buffer_length = bnx2i_conn->gen_pdu.req_wr_ptr -
				bnx2i_conn->gen_pdu.req_buf;
	bd_tbl->reserved0 = 0;
	bd_tbl->flags = ISCSI_BD_LAST_IN_BD_CHAIN |
			ISCSI_BD_FIRST_IN_BD_CHAIN;

	bd_tbl = (काष्ठा iscsi_bd  *) bnx2i_conn->gen_pdu.resp_bd_tbl;
	bd_tbl->buffer_addr_hi = (u64) bnx2i_conn->gen_pdu.resp_dma_addr >> 32;
	bd_tbl->buffer_addr_lo = (u32) bnx2i_conn->gen_pdu.resp_dma_addr;
	bd_tbl->buffer_length = ISCSI_DEF_MAX_RECV_SEG_LEN;
	bd_tbl->reserved0 = 0;
	bd_tbl->flags = ISCSI_BD_LAST_IN_BD_CHAIN |
			ISCSI_BD_FIRST_IN_BD_CHAIN;
पूर्ण


/**
 * bnx2i_iscsi_send_generic_request - called to send mgmt tasks.
 * @task:	transport layer task poपूर्णांकer
 *
 * called to transmit PDUs prepared by the 'iscsid' daemon. iSCSI login,
 *	Nop-out and Logout requests flow through this path.
 */
अटल पूर्णांक bnx2i_iscsi_send_generic_request(काष्ठा iscsi_task *task)
अणु
	काष्ठा bnx2i_cmd *cmd = task->dd_data;
	काष्ठा bnx2i_conn *bnx2i_conn = cmd->conn;
	पूर्णांक rc = 0;
	अक्षर *buf;
	पूर्णांक data_len;

	bnx2i_iscsi_prep_generic_pdu_bd(bnx2i_conn);
	चयन (task->hdr->opcode & ISCSI_OPCODE_MASK) अणु
	हाल ISCSI_OP_LOGIN:
		bnx2i_send_iscsi_login(bnx2i_conn, task);
		अवरोध;
	हाल ISCSI_OP_NOOP_OUT:
		data_len = bnx2i_conn->gen_pdu.req_buf_size;
		buf = bnx2i_conn->gen_pdu.req_buf;
		अगर (data_len)
			rc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     buf, data_len, 1);
		अन्यथा
			rc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     शून्य, 0, 1);
		अवरोध;
	हाल ISCSI_OP_LOGOUT:
		rc = bnx2i_send_iscsi_logout(bnx2i_conn, task);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		rc = bnx2i_send_iscsi_पंचांगf(bnx2i_conn, task);
		अवरोध;
	हाल ISCSI_OP_TEXT:
		rc = bnx2i_send_iscsi_text(bnx2i_conn, task);
		अवरोध;
	शेष:
		iscsi_conn_prपूर्णांकk(KERN_ALERT, bnx2i_conn->cls_conn->dd_data,
				  "send_gen: unsupported op 0x%x\n",
				  task->hdr->opcode);
	पूर्ण
	वापस rc;
पूर्ण


/**********************************************************************
 *		SCSI-ML Interface
 **********************************************************************/

/**
 * bnx2i_cpy_scsi_cdb - copies LUN & CDB fields in required क्रमmat to sq wqe
 * @sc:		SCSI-ML command poपूर्णांकer
 * @cmd:	iscsi cmd poपूर्णांकer
 */
अटल व्योम bnx2i_cpy_scsi_cdb(काष्ठा scsi_cmnd *sc, काष्ठा bnx2i_cmd *cmd)
अणु
	u32 dword;
	पूर्णांक lpcnt;
	u8 *srcp;
	u32 *dstp;
	u32 scsi_lun[2];

	पूर्णांक_to_scsilun(sc->device->lun, (काष्ठा scsi_lun *) scsi_lun);
	cmd->req.lun[0] = be32_to_cpu(scsi_lun[0]);
	cmd->req.lun[1] = be32_to_cpu(scsi_lun[1]);

	lpcnt = cmd->scsi_cmd->cmd_len / माप(dword);
	srcp = (u8 *) sc->cmnd;
	dstp = (u32 *) cmd->req.cdb;
	जबतक (lpcnt--) अणु
		स_नकल(&dword, (स्थिर व्योम *) srcp, 4);
		*dstp = cpu_to_be32(dword);
		srcp += 4;
		dstp++;
	पूर्ण
	अगर (sc->cmd_len & 0x3) अणु
		dword = (u32) srcp[0] | ((u32) srcp[1] << 8);
		*dstp = cpu_to_be32(dword);
	पूर्ण
पूर्ण

अटल व्योम bnx2i_cleanup_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा bnx2i_hba *hba = bnx2i_conn->hba;

	/*
	 * mgmt task or cmd was never sent to us to transmit.
	 */
	अगर (!task->sc || task->state == ISCSI_TASK_PENDING)
		वापस;
	/*
	 * need to clean-up task context to claim dma buffers
	 */
	अगर (task->state == ISCSI_TASK_ABRT_TMF) अणु
		bnx2i_send_cmd_cleanup_req(hba, task->dd_data);

		spin_unlock_bh(&conn->session->back_lock);
		रुको_क्रम_completion_समयout(&bnx2i_conn->cmd_cleanup_cmpl,
				msecs_to_jअगरfies(ISCSI_CMD_CLEANUP_TIMEOUT));
		spin_lock_bh(&conn->session->back_lock);
	पूर्ण
	bnx2i_iscsi_unmap_sg_list(task->dd_data);
पूर्ण

/**
 * bnx2i_mtask_xmit - transmit mtask to chip क्रम further processing
 * @conn:	transport layer conn काष्ठाure poपूर्णांकer
 * @task:	transport layer command काष्ठाure poपूर्णांकer
 */
अटल पूर्णांक
bnx2i_mtask_xmit(काष्ठा iscsi_conn *conn, काष्ठा iscsi_task *task)
अणु
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा bnx2i_hba *hba = bnx2i_conn->hba;
	काष्ठा bnx2i_cmd *cmd = task->dd_data;

	स_रखो(bnx2i_conn->gen_pdu.req_buf, 0, ISCSI_DEF_MAX_RECV_SEG_LEN);

	bnx2i_setup_cmd_wqe_ढाँचा(cmd);
	bnx2i_conn->gen_pdu.req_buf_size = task->data_count;

	/* Tx PDU/data length count */
	ADD_STATS_64(hba, tx_pdus, 1);
	ADD_STATS_64(hba, tx_bytes, task->data_count);

	अगर (task->data_count) अणु
		स_नकल(bnx2i_conn->gen_pdu.req_buf, task->data,
		       task->data_count);
		bnx2i_conn->gen_pdu.req_wr_ptr =
			bnx2i_conn->gen_pdu.req_buf + task->data_count;
	पूर्ण
	cmd->conn = conn->dd_data;
	cmd->scsi_cmd = शून्य;
	वापस bnx2i_iscsi_send_generic_request(task);
पूर्ण

/**
 * bnx2i_task_xmit - transmit iscsi command to chip क्रम further processing
 * @task:	transport layer command काष्ठाure poपूर्णांकer
 *
 * maps SG buffers and send request to chip/firmware in the क्रमm of SQ WQE
 */
अटल पूर्णांक bnx2i_task_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(session->cls_session);
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा bnx2i_cmd *cmd = task->dd_data;
	काष्ठा iscsi_scsi_req *hdr = (काष्ठा iscsi_scsi_req *)task->hdr;

	अगर (atomic_पढ़ो(&bnx2i_conn->ep->num_active_cmds) + 1  >
	    hba->max_sqes)
		वापस -ENOMEM;

	/*
	 * If there is no scsi_cmnd this must be a mgmt task
	 */
	अगर (!sc)
		वापस bnx2i_mtask_xmit(conn, task);

	bnx2i_setup_cmd_wqe_ढाँचा(cmd);
	cmd->req.op_code = ISCSI_OP_SCSI_CMD;
	cmd->conn = bnx2i_conn;
	cmd->scsi_cmd = sc;
	cmd->req.total_data_transfer_length = scsi_bufflen(sc);
	cmd->req.cmd_sn = be32_to_cpu(hdr->cmdsn);

	bnx2i_iscsi_map_sg_list(cmd);
	bnx2i_cpy_scsi_cdb(sc, cmd);

	cmd->req.op_attr = ISCSI_ATTR_SIMPLE;
	अगर (sc->sc_data_direction == DMA_TO_DEVICE) अणु
		cmd->req.op_attr |= ISCSI_CMD_REQUEST_WRITE;
		cmd->req.itt = task->itt |
			(ISCSI_TASK_TYPE_WRITE << ISCSI_CMD_REQUEST_TYPE_SHIFT);
		bnx2i_setup_ग_लिखो_cmd_bd_info(task);
	पूर्ण अन्यथा अणु
		अगर (scsi_bufflen(sc))
			cmd->req.op_attr |= ISCSI_CMD_REQUEST_READ;
		cmd->req.itt = task->itt |
			(ISCSI_TASK_TYPE_READ << ISCSI_CMD_REQUEST_TYPE_SHIFT);
	पूर्ण

	cmd->req.num_bds = cmd->io_tbl.bd_valid;
	अगर (!cmd->io_tbl.bd_valid) अणु
		cmd->req.bd_list_addr_lo = (u32) hba->mp_bd_dma;
		cmd->req.bd_list_addr_hi = (u32) ((u64) hba->mp_bd_dma >> 32);
		cmd->req.num_bds = 1;
	पूर्ण

	bnx2i_send_iscsi_scsicmd(bnx2i_conn, cmd);
	वापस 0;
पूर्ण

/**
 * bnx2i_session_create - create a new iscsi session
 * @ep:		poपूर्णांकer to iscsi endpoपूर्णांक
 * @cmds_max:		user specअगरied maximum commands
 * @qdepth:		scsi queue depth to support
 * @initial_cmdsn:	initial iscsi CMDSN to be used क्रम this session
 *
 * Creates a new iSCSI session instance on given device.
 */
अटल काष्ठा iscsi_cls_session *
bnx2i_session_create(काष्ठा iscsi_endpoपूर्णांक *ep,
		     uपूर्णांक16_t cmds_max, uपूर्णांक16_t qdepth,
		     uपूर्णांक32_t initial_cmdsn)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा bnx2i_hba *hba;
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;

	अगर (!ep) अणु
		prपूर्णांकk(KERN_ERR "bnx2i: missing ep.\n");
		वापस शून्य;
	पूर्ण

	bnx2i_ep = ep->dd_data;
	shost = bnx2i_ep->hba->shost;
	hba = iscsi_host_priv(shost);
	अगर (bnx2i_adapter_पढ़ोy(hba))
		वापस शून्य;

	/*
	 * user can override hw limit as दीर्घ as it is within
	 * the min/max.
	 */
	अगर (cmds_max > hba->max_sqes)
		cmds_max = hba->max_sqes;
	अन्यथा अगर (cmds_max < BNX2I_SQ_WQES_MIN)
		cmds_max = BNX2I_SQ_WQES_MIN;

	cls_session = iscsi_session_setup(&bnx2i_iscsi_transport, shost,
					  cmds_max, 0, माप(काष्ठा bnx2i_cmd),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	अगर (!cls_session)
		वापस शून्य;

	अगर (bnx2i_setup_cmd_pool(hba, cls_session->dd_data))
		जाओ session_tearकरोwn;
	वापस cls_session;

session_tearकरोwn:
	iscsi_session_tearकरोwn(cls_session);
	वापस शून्य;
पूर्ण


/**
 * bnx2i_session_destroy - destroys iscsi session
 * @cls_session:	poपूर्णांकer to iscsi cls session
 *
 * Destroys previously created iSCSI session instance and releases
 *	all resources held by it
 */
अटल व्योम bnx2i_session_destroy(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);

	bnx2i_destroy_cmd_pool(hba, session);
	iscsi_session_tearकरोwn(cls_session);
पूर्ण


/**
 * bnx2i_conn_create - create iscsi connection instance
 * @cls_session:	poपूर्णांकer to iscsi cls session
 * @cid:		iscsi cid as per rfc (not NX2's CID terminology)
 *
 * Creates a new iSCSI connection instance क्रम a given session
 */
अटल काष्ठा iscsi_cls_conn *
bnx2i_conn_create(काष्ठा iscsi_cls_session *cls_session, uपूर्णांक32_t cid)
अणु
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);
	काष्ठा bnx2i_conn *bnx2i_conn;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_conn *conn;

	cls_conn = iscsi_conn_setup(cls_session, माप(*bnx2i_conn),
				    cid);
	अगर (!cls_conn)
		वापस शून्य;
	conn = cls_conn->dd_data;

	bnx2i_conn = conn->dd_data;
	bnx2i_conn->cls_conn = cls_conn;
	bnx2i_conn->hba = hba;

	atomic_set(&bnx2i_conn->work_cnt, 0);

	/* 'ep' ptr will be asचिन्हित in bind() call */
	bnx2i_conn->ep = शून्य;
	init_completion(&bnx2i_conn->cmd_cleanup_cmpl);

	अगर (bnx2i_conn_alloc_login_resources(hba, bnx2i_conn)) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, conn,
				  "conn_new: login resc alloc failed!!\n");
		जाओ मुक्त_conn;
	पूर्ण

	वापस cls_conn;

मुक्त_conn:
	iscsi_conn_tearकरोwn(cls_conn);
	वापस शून्य;
पूर्ण

/**
 * bnx2i_conn_bind - binds iscsi sess, conn and ep objects together
 * @cls_session:	poपूर्णांकer to iscsi cls session
 * @cls_conn:		poपूर्णांकer to iscsi cls conn
 * @transport_fd:	64-bit EP handle
 * @is_leading:		leading connection on this session?
 *
 * Binds together iSCSI session instance, iSCSI connection instance
 *	and the TCP connection. This routine वापसs error code अगर
 *	TCP connection करोes not beदीर्घ on the device iSCSI sess/conn
 *	is bound
 */
अटल पूर्णांक bnx2i_conn_bind(काष्ठा iscsi_cls_session *cls_session,
			   काष्ठा iscsi_cls_conn *cls_conn,
			   uपूर्णांक64_t transport_fd, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	पूर्णांक ret_code;

	ep = iscsi_lookup_endpoपूर्णांक(transport_fd);
	अगर (!ep)
		वापस -EINVAL;
	/*
	 * Forcefully terminate all in progress connection recovery at the
	 * earliest, either in bind(), send_pdu(LOGIN), or conn_start()
	 */
	अगर (bnx2i_adapter_पढ़ोy(hba))
		वापस -EIO;

	bnx2i_ep = ep->dd_data;
	अगर ((bnx2i_ep->state == EP_STATE_TCP_FIN_RCVD) ||
	    (bnx2i_ep->state == EP_STATE_TCP_RST_RCVD))
		/* Peer disconnect via' FIN or RST */
		वापस -EINVAL;

	अगर (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		वापस -EINVAL;

	अगर (bnx2i_ep->hba != hba) अणु
		/* Error - TCP connection करोes not beदीर्घ to this device
		 */
		iscsi_conn_prपूर्णांकk(KERN_ALERT, cls_conn->dd_data,
				  "conn bind, ep=0x%p (%s) does not",
				  bnx2i_ep, bnx2i_ep->hba->netdev->name);
		iscsi_conn_prपूर्णांकk(KERN_ALERT, cls_conn->dd_data,
				  "belong to hba (%s)\n",
				  hba->netdev->name);
		वापस -EEXIST;
	पूर्ण
	bnx2i_ep->conn = bnx2i_conn;
	bnx2i_conn->ep = bnx2i_ep;
	bnx2i_conn->iscsi_conn_cid = bnx2i_ep->ep_iscsi_cid;
	bnx2i_conn->fw_cid = bnx2i_ep->ep_cid;

	ret_code = bnx2i_bind_conn_to_iscsi_cid(hba, bnx2i_conn,
						bnx2i_ep->ep_iscsi_cid);

	/* 5706/5708/5709 FW takes RQ as full when initiated, but क्रम 57710
	 * driver needs to explicitly replenish RQ index during setup.
	 */
	अगर (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		bnx2i_put_rq_buf(bnx2i_conn, 0);

	bnx2i_arm_cq_event_coalescing(bnx2i_conn->ep, CNIC_ARM_CQE);
	वापस ret_code;
पूर्ण


/**
 * bnx2i_conn_destroy - destroy iscsi connection instance & release resources
 * @cls_conn:	poपूर्णांकer to iscsi cls conn
 *
 * Destroy an iSCSI connection instance and release memory resources held by
 *	this connection
 */
अटल व्योम bnx2i_conn_destroy(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;
	काष्ठा Scsi_Host *shost;
	काष्ठा bnx2i_hba *hba;
	काष्ठा bnx2i_work *work, *पंचांगp;
	अचिन्हित cpu = 0;
	काष्ठा bnx2i_percpu_s *p;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cls_conn));
	hba = iscsi_host_priv(shost);

	bnx2i_conn_मुक्त_login_resources(hba, bnx2i_conn);

	अगर (atomic_पढ़ो(&bnx2i_conn->work_cnt)) अणु
		क्रम_each_online_cpu(cpu) अणु
			p = &per_cpu(bnx2i_percpu, cpu);
			spin_lock_bh(&p->p_work_lock);
			list_क्रम_each_entry_safe(work, पंचांगp,
						 &p->work_list, list) अणु
				अगर (work->session == conn->session &&
				    work->bnx2i_conn == bnx2i_conn) अणु
					list_del_init(&work->list);
					kमुक्त(work);
					अगर (!atomic_dec_and_test(
							&bnx2i_conn->work_cnt))
						अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_bh(&p->p_work_lock);
		पूर्ण
	पूर्ण

	iscsi_conn_tearकरोwn(cls_conn);
पूर्ण


/**
 * bnx2i_ep_get_param - वापस iscsi ep parameter to caller
 * @ep:		poपूर्णांकer to iscsi endpoपूर्णांक
 * @param:	parameter type identअगरier
 * @buf: 	buffer poपूर्णांकer
 *
 * वापसs iSCSI ep parameters
 */
अटल पूर्णांक bnx2i_ep_get_param(काष्ठा iscsi_endpoपूर्णांक *ep,
			      क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep = ep->dd_data;
	काष्ठा bnx2i_hba *hba = bnx2i_ep->hba;
	पूर्णांक len = -ENOTCONN;

	अगर (!hba)
		वापस -ENOTCONN;

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
		mutex_lock(&hba->net_dev_lock);
		अगर (bnx2i_ep->cm_sk)
			len = प्र_लिखो(buf, "%hu\n", bnx2i_ep->cm_sk->dst_port);
		mutex_unlock(&hba->net_dev_lock);
		अवरोध;
	हाल ISCSI_PARAM_CONN_ADDRESS:
		mutex_lock(&hba->net_dev_lock);
		अगर (bnx2i_ep->cm_sk)
			len = प्र_लिखो(buf, "%pI4\n", &bnx2i_ep->cm_sk->dst_ip);
		mutex_unlock(&hba->net_dev_lock);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस len;
पूर्ण

/**
 * bnx2i_host_get_param - वापसs host (adapter) related parameters
 * @shost:	scsi host poपूर्णांकer
 * @param:	parameter type identअगरier
 * @buf:	buffer poपूर्णांकer
 */
अटल पूर्णांक bnx2i_host_get_param(काष्ठा Scsi_Host *shost,
				क्रमागत iscsi_host_param param, अक्षर *buf)
अणु
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);
	पूर्णांक len = 0;

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_क्रमmat_mac(buf, hba->cnic->mac_addr, 6);
		अवरोध;
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		len = प्र_लिखो(buf, "%s\n", hba->netdev->name);
		अवरोध;
	हाल ISCSI_HOST_PARAM_IPADDRESS: अणु
		काष्ठा list_head *active_list = &hba->ep_active_list;

		पढ़ो_lock_bh(&hba->ep_rdwr_lock);
		अगर (!list_empty(&hba->ep_active_list)) अणु
			काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
			काष्ठा cnic_sock *csk;

			bnx2i_ep = list_first_entry(active_list,
						    काष्ठा bnx2i_endpoपूर्णांक,
						    link);
			csk = bnx2i_ep->cm_sk;
			अगर (test_bit(SK_F_IPV6, &csk->flags))
				len = प्र_लिखो(buf, "%pI6\n", csk->src_ip);
			अन्यथा
				len = प्र_लिखो(buf, "%pI4\n", csk->src_ip);
		पूर्ण
		पढ़ो_unlock_bh(&hba->ep_rdwr_lock);
		अवरोध;
	पूर्ण
	शेष:
		वापस iscsi_host_get_param(shost, param, buf);
	पूर्ण
	वापस len;
पूर्ण

/**
 * bnx2i_conn_start - completes iscsi connection migration to FFP
 * @cls_conn:	poपूर्णांकer to iscsi cls conn
 *
 * last call in FFP migration to hanकरोver iscsi conn to the driver
 */
अटल पूर्णांक bnx2i_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा bnx2i_conn *bnx2i_conn = conn->dd_data;

	bnx2i_conn->ep->state = EP_STATE_ULP_UPDATE_START;
	bnx2i_update_iscsi_conn(conn);

	/*
	 * this should normally not sleep क्रम a दीर्घ समय so it should
	 * not disrupt the caller.
	 */
	समयr_setup(&bnx2i_conn->ep->ofld_समयr, bnx2i_ep_ofld_समयr, 0);
	bnx2i_conn->ep->ofld_समयr.expires = 1 * HZ + jअगरfies;
	add_समयr(&bnx2i_conn->ep->ofld_समयr);
	/* update iSCSI context क्रम this conn, रुको क्रम CNIC to complete */
	रुको_event_पूर्णांकerruptible(bnx2i_conn->ep->ofld_रुको,
			bnx2i_conn->ep->state != EP_STATE_ULP_UPDATE_START);

	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&bnx2i_conn->ep->ofld_समयr);

	iscsi_conn_start(cls_conn);
	वापस 0;
पूर्ण


/**
 * bnx2i_conn_get_stats - वापसs iSCSI stats
 * @cls_conn:	poपूर्णांकer to iscsi cls conn
 * @stats:	poपूर्णांकer to iscsi statistic काष्ठा
 */
अटल व्योम bnx2i_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
				 काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
	stats->digest_err = 0;
	stats->समयout_err = 0;
	म_नकल(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_पात_cnt;
	stats->custom_length = 1;
पूर्ण


/**
 * bnx2i_check_route - checks अगर target IP route beदीर्घs to one of NX2 devices
 * @dst_addr:	target IP address
 *
 * check अगर route resolves to BNX2 device
 */
अटल काष्ठा bnx2i_hba *bnx2i_check_route(काष्ठा sockaddr *dst_addr)
अणु
	काष्ठा sockaddr_in *desti = (काष्ठा sockaddr_in *) dst_addr;
	काष्ठा bnx2i_hba *hba;
	काष्ठा cnic_dev *cnic = शून्य;

	hba = get_adapter_list_head();
	अगर (hba && hba->cnic)
		cnic = hba->cnic->cm_select_dev(desti, CNIC_ULP_ISCSI);
	अगर (!cnic) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: no route,"
		       "can't connect using cnic\n");
		जाओ no_nx2_route;
	पूर्ण
	hba = bnx2i_find_hba_क्रम_cnic(cnic);
	अगर (!hba)
		जाओ no_nx2_route;

	अगर (bnx2i_adapter_पढ़ोy(hba)) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: check route, hba not found\n");
		जाओ no_nx2_route;
	पूर्ण
	अगर (hba->netdev->mtu > hba->mtu_supported) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: %s network i/f mtu is set to %d\n",
				  hba->netdev->name, hba->netdev->mtu);
		prपूर्णांकk(KERN_ALERT "bnx2i: iSCSI HBA can support mtu of %d\n",
				  hba->mtu_supported);
		जाओ no_nx2_route;
	पूर्ण
	वापस hba;
no_nx2_route:
	वापस शून्य;
पूर्ण


/**
 * bnx2i_tear_करोwn_conn - tear करोwn iscsi/tcp connection and मुक्त resources
 * @hba:	poपूर्णांकer to adapter instance
 * @ep:		endpoपूर्णांक (transport identअगरier) काष्ठाure
 *
 * destroys cm_sock काष्ठाure and on chip iscsi context
 */
अटल पूर्णांक bnx2i_tear_करोwn_conn(काष्ठा bnx2i_hba *hba,
				 काष्ठा bnx2i_endpoपूर्णांक *ep)
अणु
	अगर (test_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic) && ep->cm_sk)
		hba->cnic->cm_destroy(ep->cm_sk);

	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type) &&
	    ep->state == EP_STATE_DISCONN_TIMEDOUT) अणु
		अगर (ep->conn && ep->conn->cls_conn &&
		    ep->conn->cls_conn->dd_data) अणु
			काष्ठा iscsi_conn *conn = ep->conn->cls_conn->dd_data;

			/* Must suspend all rx queue activity क्रम this ep */
			set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
		पूर्ण
		/* CONN_DISCONNECT समयout may or may not be an issue depending
		 * on what transcribed in TCP layer, dअगरferent tarमाला_लो behave
		 * dअगरferently
		 */
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): - WARN - CONN_DISCON timed out, "
				  "please submit GRC Dump, NW/PCIe trace, "
				  "driver msgs to developers for analysis\n",
				  hba->netdev->name);
	पूर्ण

	ep->state = EP_STATE_CLEANUP_START;
	समयr_setup(&ep->ofld_समयr, bnx2i_ep_ofld_समयr, 0);
	ep->ofld_समयr.expires = hba->conn_ctx_destroy_पंचांगo + jअगरfies;
	add_समयr(&ep->ofld_समयr);

	bnx2i_ep_destroy_list_add(hba, ep);

	/* destroy iSCSI context, रुको क्रम it to complete */
	अगर (bnx2i_send_conn_destroy(hba, ep))
		ep->state = EP_STATE_CLEANUP_CMPL;

	रुको_event_पूर्णांकerruptible(ep->ofld_रुको,
				 (ep->state != EP_STATE_CLEANUP_START));

	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&ep->ofld_समयr);

	bnx2i_ep_destroy_list_del(hba, ep);

	अगर (ep->state != EP_STATE_CLEANUP_CMPL)
		/* should never happen */
		prपूर्णांकk(KERN_ALERT "bnx2i - conn destroy failed\n");

	वापस 0;
पूर्ण


/**
 * bnx2i_ep_connect - establish TCP connection to target portal
 * @shost:		scsi host
 * @dst_addr:		target IP address
 * @non_blocking:	blocking or non-blocking call
 *
 * this routine initiates the TCP/IP connection by invoking Option-2 i/f
 *	with l5_core and the CNIC. This is a multi-step process of resolving
 *	route to target, create a iscsi connection context, handshaking with
 *	CNIC module to create/initialize the socket काष्ठा and finally
 *	sending करोwn option-2 request to complete TCP 3-way handshake
 */
अटल काष्ठा iscsi_endpoपूर्णांक *bnx2i_ep_connect(काष्ठा Scsi_Host *shost,
					       काष्ठा sockaddr *dst_addr,
					       पूर्णांक non_blocking)
अणु
	u32 iscsi_cid = BNX2I_CID_RESERVED;
	काष्ठा sockaddr_in *desti = (काष्ठा sockaddr_in *) dst_addr;
	काष्ठा sockaddr_in6 *desti6;
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	काष्ठा bnx2i_hba *hba;
	काष्ठा cnic_dev *cnic;
	काष्ठा cnic_sockaddr saddr;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	पूर्णांक rc = 0;

	अगर (shost) अणु
		/* driver is given scsi host to work with */
		hba = iscsi_host_priv(shost);
	पूर्ण अन्यथा
		/*
		 * check अगर the given destination can be reached through
		 * a iscsi capable NetXtreme2 device
		 */
		hba = bnx2i_check_route(dst_addr);

	अगर (!hba) अणु
		rc = -EINVAL;
		जाओ nohba;
	पूर्ण
	mutex_lock(&hba->net_dev_lock);

	अगर (bnx2i_adapter_पढ़ोy(hba) || !hba->cid_que.cid_मुक्त_cnt) अणु
		rc = -EPERM;
		जाओ check_busy;
	पूर्ण
	cnic = hba->cnic;
	ep = bnx2i_alloc_ep(hba);
	अगर (!ep) अणु
		rc = -ENOMEM;
		जाओ check_busy;
	पूर्ण
	bnx2i_ep = ep->dd_data;

	atomic_set(&bnx2i_ep->num_active_cmds, 0);
	iscsi_cid = bnx2i_alloc_iscsi_cid(hba);
	अगर (iscsi_cid == -1) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): alloc_ep - unable to allocate "
			"iscsi cid\n", hba->netdev->name);
		rc = -ENOMEM;
		bnx2i_मुक्त_ep(ep);
		जाओ check_busy;
	पूर्ण
	bnx2i_ep->hba_age = hba->age;

	rc = bnx2i_alloc_qp_resc(hba, bnx2i_ep);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): ep_conn - alloc QP resc error"
			"\n", hba->netdev->name);
		rc = -ENOMEM;
		जाओ qp_resc_err;
	पूर्ण

	bnx2i_ep->ep_iscsi_cid = (u16)iscsi_cid;
	bnx2i_ep->state = EP_STATE_OFLD_START;
	bnx2i_ep_ofld_list_add(hba, bnx2i_ep);

	समयr_setup(&bnx2i_ep->ofld_समयr, bnx2i_ep_ofld_समयr, 0);
	bnx2i_ep->ofld_समयr.expires = 2 * HZ + jअगरfies;
	add_समयr(&bnx2i_ep->ofld_समयr);

	अगर (bnx2i_send_conn_ofld_req(hba, bnx2i_ep)) अणु
		अगर (bnx2i_ep->state == EP_STATE_OFLD_FAILED_CID_BUSY) अणु
			prपूर्णांकk(KERN_ALERT "bnx2i (%s): iscsi cid %d is busy\n",
				hba->netdev->name, bnx2i_ep->ep_iscsi_cid);
			rc = -EBUSY;
		पूर्ण अन्यथा
			rc = -ENOSPC;
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): unable to send conn offld kwqe"
			"\n", hba->netdev->name);
		bnx2i_ep_ofld_list_del(hba, bnx2i_ep);
		जाओ conn_failed;
	पूर्ण

	/* Wait क्रम CNIC hardware to setup conn context and वापस 'cid' */
	रुको_event_पूर्णांकerruptible(bnx2i_ep->ofld_रुको,
				 bnx2i_ep->state != EP_STATE_OFLD_START);

	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&bnx2i_ep->ofld_समयr);

	bnx2i_ep_ofld_list_del(hba, bnx2i_ep);

	अगर (bnx2i_ep->state != EP_STATE_OFLD_COMPL) अणु
		अगर (bnx2i_ep->state == EP_STATE_OFLD_FAILED_CID_BUSY) अणु
			prपूर्णांकk(KERN_ALERT "bnx2i (%s): iscsi cid %d is busy\n",
				hba->netdev->name, bnx2i_ep->ep_iscsi_cid);
			rc = -EBUSY;
		पूर्ण अन्यथा
			rc = -ENOSPC;
		जाओ conn_failed;
	पूर्ण

	rc = cnic->cm_create(cnic, CNIC_ULP_ISCSI, bnx2i_ep->ep_cid,
			     iscsi_cid, &bnx2i_ep->cm_sk, bnx2i_ep);
	अगर (rc) अणु
		rc = -EINVAL;
		/* Need to terminate and cleanup the connection */
		जाओ release_ep;
	पूर्ण

	bnx2i_ep->cm_sk->rcv_buf = 256 * 1024;
	bnx2i_ep->cm_sk->snd_buf = 256 * 1024;
	clear_bit(SK_TCP_TIMESTAMP, &bnx2i_ep->cm_sk->tcp_flags);

	स_रखो(&saddr, 0, माप(saddr));
	अगर (dst_addr->sa_family == AF_INET) अणु
		desti = (काष्ठा sockaddr_in *) dst_addr;
		saddr.remote.v4 = *desti;
		saddr.local.v4.sin_family = desti->sin_family;
	पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_INET6) अणु
		desti6 = (काष्ठा sockaddr_in6 *) dst_addr;
		saddr.remote.v6 = *desti6;
		saddr.local.v6.sin6_family = desti6->sin6_family;
	पूर्ण

	bnx2i_ep->बारtamp = jअगरfies;
	bnx2i_ep->state = EP_STATE_CONNECT_START;
	अगर (!test_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic)) अणु
		rc = -EINVAL;
		जाओ conn_failed;
	पूर्ण अन्यथा
		rc = cnic->cm_connect(bnx2i_ep->cm_sk, &saddr);
	अगर (rc)
		जाओ release_ep;

	bnx2i_ep_active_list_add(hba, bnx2i_ep);

	rc = bnx2i_map_ep_dbell_regs(bnx2i_ep);
	अगर (rc)
		जाओ del_active_ep;

	mutex_unlock(&hba->net_dev_lock);
	वापस ep;

del_active_ep:
	bnx2i_ep_active_list_del(hba, bnx2i_ep);
release_ep:
	अगर (bnx2i_tear_करोwn_conn(hba, bnx2i_ep)) अणु
		mutex_unlock(&hba->net_dev_lock);
		वापस ERR_PTR(rc);
	पूर्ण
conn_failed:
	bnx2i_मुक्त_qp_resc(hba, bnx2i_ep);
qp_resc_err:
	bnx2i_मुक्त_ep(ep);
check_busy:
	mutex_unlock(&hba->net_dev_lock);
nohba:
	वापस ERR_PTR(rc);
पूर्ण


/**
 * bnx2i_ep_poll - polls क्रम TCP connection establishement
 * @ep:			TCP connection (endpoपूर्णांक) handle
 * @समयout_ms:		समयout value in milli secs
 *
 * polls क्रम TCP connect request to complete
 */
अटल पूर्णांक bnx2i_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	पूर्णांक rc = 0;

	bnx2i_ep = ep->dd_data;
	अगर ((bnx2i_ep->state == EP_STATE_IDLE) ||
	    (bnx2i_ep->state == EP_STATE_CONNECT_FAILED) ||
	    (bnx2i_ep->state == EP_STATE_OFLD_FAILED))
		वापस -1;
	अगर (bnx2i_ep->state == EP_STATE_CONNECT_COMPL)
		वापस 1;

	rc = रुको_event_पूर्णांकerruptible_समयout(bnx2i_ep->ofld_रुको,
					      ((bnx2i_ep->state ==
						EP_STATE_OFLD_FAILED) ||
					       (bnx2i_ep->state ==
						EP_STATE_CONNECT_FAILED) ||
					       (bnx2i_ep->state ==
						EP_STATE_CONNECT_COMPL)),
					      msecs_to_jअगरfies(समयout_ms));
	अगर (bnx2i_ep->state == EP_STATE_OFLD_FAILED)
		rc = -1;

	अगर (rc > 0)
		वापस 1;
	अन्यथा अगर (!rc)
		वापस 0;	/* समयout */
	अन्यथा
		वापस rc;
पूर्ण


/**
 * bnx2i_ep_tcp_conn_active - check EP state transition
 * @bnx2i_ep:		endpoपूर्णांक poपूर्णांकer
 *
 * check अगर underlying TCP connection is active
 */
अटल पूर्णांक bnx2i_ep_tcp_conn_active(काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep)
अणु
	पूर्णांक ret;
	पूर्णांक cnic_dev_10g = 0;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		cnic_dev_10g = 1;

	चयन (bnx2i_ep->state) अणु
	हाल EP_STATE_CLEANUP_FAILED:
	हाल EP_STATE_OFLD_FAILED:
	हाल EP_STATE_DISCONN_TIMEDOUT:
		ret = 0;
		अवरोध;
	हाल EP_STATE_CONNECT_START:
	हाल EP_STATE_CONNECT_FAILED:
	हाल EP_STATE_CONNECT_COMPL:
	हाल EP_STATE_ULP_UPDATE_START:
	हाल EP_STATE_ULP_UPDATE_COMPL:
	हाल EP_STATE_TCP_FIN_RCVD:
	हाल EP_STATE_LOGOUT_SENT:
	हाल EP_STATE_LOGOUT_RESP_RCVD:
	हाल EP_STATE_ULP_UPDATE_FAILED:
		ret = 1;
		अवरोध;
	हाल EP_STATE_TCP_RST_RCVD:
		अगर (cnic_dev_10g)
			ret = 0;
		अन्यथा
			ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण


/**
 * bnx2i_hw_ep_disconnect - executes TCP connection tearकरोwn process in the hw
 * @bnx2i_ep:		TCP connection (bnx2i endpoपूर्णांक) handle
 *
 * executes  TCP connection tearकरोwn process
 */
पूर्णांक bnx2i_hw_ep_disconnect(काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep)
अणु
	काष्ठा bnx2i_hba *hba = bnx2i_ep->hba;
	काष्ठा cnic_dev *cnic;
	काष्ठा iscsi_session *session = शून्य;
	काष्ठा iscsi_conn *conn = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक बंद = 0;
	पूर्णांक बंद_ret = 0;

	अगर (!hba)
		वापस 0;

	cnic = hba->cnic;
	अगर (!cnic)
		वापस 0;

	अगर (bnx2i_ep->state == EP_STATE_IDLE ||
	    bnx2i_ep->state == EP_STATE_DISCONN_TIMEDOUT)
		वापस 0;

	अगर (!bnx2i_ep_tcp_conn_active(bnx2i_ep))
		जाओ destroy_conn;

	अगर (bnx2i_ep->conn) अणु
		conn = bnx2i_ep->conn->cls_conn->dd_data;
		session = conn->session;
	पूर्ण

	समयr_setup(&bnx2i_ep->ofld_समयr, bnx2i_ep_ofld_समयr, 0);
	bnx2i_ep->ofld_समयr.expires = hba->conn_tearकरोwn_पंचांगo + jअगरfies;
	add_समयr(&bnx2i_ep->ofld_समयr);

	अगर (!test_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic))
		जाओ out;

	अगर (session) अणु
		spin_lock_bh(&session->frwd_lock);
		अगर (bnx2i_ep->state != EP_STATE_TCP_FIN_RCVD) अणु
			अगर (session->state == ISCSI_STATE_LOGGING_OUT) अणु
				अगर (bnx2i_ep->state == EP_STATE_LOGOUT_SENT) अणु
					/* Logout sent, but no resp */
					prपूर्णांकk(KERN_ALERT "bnx2i (%s): WARNING"
						" logout response was not "
						"received!\n",
						bnx2i_ep->hba->netdev->name);
				पूर्ण अन्यथा अगर (bnx2i_ep->state ==
					   EP_STATE_LOGOUT_RESP_RCVD)
					बंद = 1;
			पूर्ण
		पूर्ण अन्यथा
			बंद = 1;

		spin_unlock_bh(&session->frwd_lock);
	पूर्ण

	bnx2i_ep->state = EP_STATE_DISCONN_START;

	अगर (बंद)
		बंद_ret = cnic->cm_बंद(bnx2i_ep->cm_sk);
	अन्यथा
		बंद_ret = cnic->cm_पात(bnx2i_ep->cm_sk);

	अगर (बंद_ret)
		prपूर्णांकk(KERN_ALERT "bnx2i (%s): close/abort(%d) returned %d\n",
			bnx2i_ep->hba->netdev->name, बंद, बंद_ret);
	अन्यथा
		/* रुको क्रम option-2 conn tearकरोwn */
		रुको_event_पूर्णांकerruptible(bnx2i_ep->ofld_रुको,
				((bnx2i_ep->state != EP_STATE_DISCONN_START)
				&& (bnx2i_ep->state != EP_STATE_TCP_FIN_RCVD)));

	अगर (संकेत_pending(current))
		flush_संकेतs(current);
	del_समयr_sync(&bnx2i_ep->ofld_समयr);

destroy_conn:
	bnx2i_ep_active_list_del(hba, bnx2i_ep);
	अगर (bnx2i_tear_करोwn_conn(hba, bnx2i_ep))
		वापस -EINVAL;
out:
	bnx2i_ep->state = EP_STATE_IDLE;
	वापस ret;
पूर्ण


/**
 * bnx2i_ep_disconnect - executes TCP connection tearकरोwn process
 * @ep:		TCP connection (iscsi endpoपूर्णांक) handle
 *
 * executes  TCP connection tearकरोwn process
 */
अटल व्योम bnx2i_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	काष्ठा bnx2i_conn *bnx2i_conn = शून्य;
	काष्ठा iscsi_conn *conn = शून्य;
	काष्ठा bnx2i_hba *hba;

	bnx2i_ep = ep->dd_data;

	/* driver should not attempt connection cleanup until TCP_CONNECT
	 * completes either successfully or fails. Timeout is 9-secs, so
	 * रुको क्रम it to complete
	 */
	जबतक ((bnx2i_ep->state == EP_STATE_CONNECT_START) &&
		!समय_after(jअगरfies, bnx2i_ep->बारtamp + (12 * HZ)))
		msleep(250);

	अगर (bnx2i_ep->conn) अणु
		bnx2i_conn = bnx2i_ep->conn;
		conn = bnx2i_conn->cls_conn->dd_data;
		iscsi_suspend_queue(conn);
	पूर्ण
	hba = bnx2i_ep->hba;

	mutex_lock(&hba->net_dev_lock);

	अगर (bnx2i_ep->state == EP_STATE_DISCONN_TIMEDOUT)
		जाओ out;

	अगर (bnx2i_ep->state == EP_STATE_IDLE)
		जाओ मुक्त_resc;

	अगर (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state) ||
	    (bnx2i_ep->hba_age != hba->age)) अणु
		bnx2i_ep_active_list_del(hba, bnx2i_ep);
		जाओ मुक्त_resc;
	पूर्ण

	/* Do all chip cleanup here */
	अगर (bnx2i_hw_ep_disconnect(bnx2i_ep)) अणु
		mutex_unlock(&hba->net_dev_lock);
		वापस;
	पूर्ण
मुक्त_resc:
	bnx2i_मुक्त_qp_resc(hba, bnx2i_ep);

	अगर (bnx2i_conn)
		bnx2i_conn->ep = शून्य;

	bnx2i_मुक्त_ep(ep);
out:
	mutex_unlock(&hba->net_dev_lock);

	wake_up_पूर्णांकerruptible(&hba->eh_रुको);
पूर्ण


/**
 * bnx2i_nl_set_path - ISCSI_UEVENT_PATH_UPDATE user message handler
 * @shost:	scsi host poपूर्णांकer
 * @params:	poपूर्णांकer to buffer containing iscsi path message
 */
अटल पूर्णांक bnx2i_nl_set_path(काष्ठा Scsi_Host *shost, काष्ठा iscsi_path *params)
अणु
	काष्ठा bnx2i_hba *hba = iscsi_host_priv(shost);
	अक्षर *buf = (अक्षर *) params;
	u16 len = माप(*params);

	/* handled by cnic driver */
	hba->cnic->iscsi_nl_msg_recv(hba->cnic, ISCSI_UEVENT_PATH_UPDATE, buf,
				     len);

	वापस 0;
पूर्ण

अटल umode_t bnx2i_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_IPADDRESS:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_PING_TMO:
		हाल ISCSI_PARAM_RECV_TMO:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_FAST_ABORT:
		हाल ISCSI_PARAM_ABORT_TMO:
		हाल ISCSI_PARAM_LU_RESET_TMO:
		हाल ISCSI_PARAM_TGT_RESET_TMO:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_INITIATOR_NAME:
		हाल ISCSI_PARAM_BOOT_ROOT:
		हाल ISCSI_PARAM_BOOT_NIC:
		हाल ISCSI_PARAM_BOOT_TARGET:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * 'Scsi_Host_Template' structure and 'iscsi_tranport' काष्ठाure ढाँचा
 * used जबतक रेजिस्टरing with the scsi host and iSCSI transport module.
 */
अटल काष्ठा scsi_host_ढाँचा bnx2i_host_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "QLogic Offload iSCSI Initiator",
	.proc_name		= "bnx2i",
	.queuecommand		= iscsi_queuecommand,
	.eh_समयd_out		= iscsi_eh_cmd_समयd_out,
	.eh_पात_handler	= iscsi_eh_पात,
	.eh_device_reset_handler = iscsi_eh_device_reset,
	.eh_target_reset_handler = iscsi_eh_recover_target,
	.change_queue_depth	= scsi_change_queue_depth,
	.target_alloc		= iscsi_target_alloc,
	.can_queue		= 2048,
	.max_sectors		= 127,
	.cmd_per_lun		= 128,
	.this_id		= -1,
	.sg_tablesize		= ISCSI_MAX_BDS_PER_CMD,
	.shost_attrs		= bnx2i_dev_attributes,
	.track_queue_depth	= 1,
पूर्ण;

काष्ठा iscsi_transport bnx2i_iscsi_transport = अणु
	.owner			= THIS_MODULE,
	.name			= "bnx2i",
	.caps			= CAP_RECOVERY_L0 | CAP_HDRDGST |
				  CAP_MULTI_R2T | CAP_DATADGST |
				  CAP_DATA_PATH_OFFLOAD |
				  CAP_TEXT_NEGO,
	.create_session		= bnx2i_session_create,
	.destroy_session	= bnx2i_session_destroy,
	.create_conn		= bnx2i_conn_create,
	.bind_conn		= bnx2i_conn_bind,
	.destroy_conn		= bnx2i_conn_destroy,
	.attr_is_visible	= bnx2i_attr_is_visible,
	.set_param		= iscsi_set_param,
	.get_conn_param		= iscsi_conn_get_param,
	.get_session_param	= iscsi_session_get_param,
	.get_host_param		= bnx2i_host_get_param,
	.start_conn		= bnx2i_conn_start,
	.stop_conn		= iscsi_conn_stop,
	.send_pdu		= iscsi_conn_send_pdu,
	.xmit_task		= bnx2i_task_xmit,
	.get_stats		= bnx2i_conn_get_stats,
	/* TCP connect - disconnect - option-2 पूर्णांकerface calls */
	.get_ep_param		= bnx2i_ep_get_param,
	.ep_connect		= bnx2i_ep_connect,
	.ep_poll		= bnx2i_ep_poll,
	.ep_disconnect		= bnx2i_ep_disconnect,
	.set_path		= bnx2i_nl_set_path,
	/* Error recovery समयout call */
	.session_recovery_समयकरोut = iscsi_session_recovery_समयकरोut,
	.cleanup_task		= bnx2i_cleanup_task,
पूर्ण;
