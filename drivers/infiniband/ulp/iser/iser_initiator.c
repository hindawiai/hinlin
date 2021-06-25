<शैली गुरु>
/*
 * Copyright (c) 2004, 2005, 2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2013-2014 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kfअगरo.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>

#समावेश "iscsi_iser.h"

/* Register user buffer memory and initialize passive rdma
 *  dto descriptor. Data size is stored in
 *  task->data[ISER_सूची_IN].data_len, Protection size
 *  os stored in task->prot[ISER_सूची_IN].data_len
 */
अटल पूर्णांक iser_prepare_पढ़ो_cmd(काष्ठा iscsi_task *task)

अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	काष्ठा iser_mem_reg *mem_reg;
	पूर्णांक err;
	काष्ठा iser_ctrl *hdr = &iser_task->desc.iser_header;
	काष्ठा iser_data_buf *buf_in = &iser_task->data[ISER_सूची_IN];

	err = iser_dma_map_task_data(iser_task,
				     buf_in,
				     ISER_सूची_IN,
				     DMA_FROM_DEVICE);
	अगर (err)
		वापस err;

	अगर (scsi_prot_sg_count(iser_task->sc)) अणु
		काष्ठा iser_data_buf *pbuf_in = &iser_task->prot[ISER_सूची_IN];

		err = iser_dma_map_task_data(iser_task,
					     pbuf_in,
					     ISER_सूची_IN,
					     DMA_FROM_DEVICE);
		अगर (err)
			वापस err;
	पूर्ण

	err = iser_reg_mem_fastreg(iser_task, ISER_सूची_IN, false);
	अगर (err) अणु
		iser_err("Failed to set up Data-IN RDMA\n");
		वापस err;
	पूर्ण
	mem_reg = &iser_task->rdma_reg[ISER_सूची_IN];

	hdr->flags    |= ISER_RSV;
	hdr->पढ़ो_stag = cpu_to_be32(mem_reg->rkey);
	hdr->पढ़ो_va   = cpu_to_be64(mem_reg->sge.addr);

	iser_dbg("Cmd itt:%d READ tags RKEY:%#.4X VA:%#llX\n",
		 task->itt, mem_reg->rkey,
		 (अचिन्हित दीर्घ दीर्घ)mem_reg->sge.addr);

	वापस 0;
पूर्ण

/* Register user buffer memory and initialize passive rdma
 *  dto descriptor. Data size is stored in
 *  task->data[ISER_सूची_OUT].data_len, Protection size
 *  is stored at task->prot[ISER_सूची_OUT].data_len
 */
अटल पूर्णांक
iser_prepare_ग_लिखो_cmd(काष्ठा iscsi_task *task,
		       अचिन्हित पूर्णांक imm_sz,
		       अचिन्हित पूर्णांक unsol_sz,
		       अचिन्हित पूर्णांक edtl)
अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	काष्ठा iser_mem_reg *mem_reg;
	पूर्णांक err;
	काष्ठा iser_ctrl *hdr = &iser_task->desc.iser_header;
	काष्ठा iser_data_buf *buf_out = &iser_task->data[ISER_सूची_OUT];
	काष्ठा ib_sge *tx_dsg = &iser_task->desc.tx_sg[1];

	err = iser_dma_map_task_data(iser_task,
				     buf_out,
				     ISER_सूची_OUT,
				     DMA_TO_DEVICE);
	अगर (err)
		वापस err;

	अगर (scsi_prot_sg_count(iser_task->sc)) अणु
		काष्ठा iser_data_buf *pbuf_out = &iser_task->prot[ISER_सूची_OUT];

		err = iser_dma_map_task_data(iser_task,
					     pbuf_out,
					     ISER_सूची_OUT,
					     DMA_TO_DEVICE);
		अगर (err)
			वापस err;
	पूर्ण

	err = iser_reg_mem_fastreg(iser_task, ISER_सूची_OUT,
				   buf_out->data_len == imm_sz);
	अगर (err != 0) अणु
		iser_err("Failed to register write cmd RDMA mem\n");
		वापस err;
	पूर्ण

	mem_reg = &iser_task->rdma_reg[ISER_सूची_OUT];

	अगर (unsol_sz < edtl) अणु
		hdr->flags     |= ISER_WSV;
		अगर (buf_out->data_len > imm_sz) अणु
			hdr->ग_लिखो_stag = cpu_to_be32(mem_reg->rkey);
			hdr->ग_लिखो_va = cpu_to_be64(mem_reg->sge.addr + unsol_sz);
		पूर्ण

		iser_dbg("Cmd itt:%d, WRITE tags, RKEY:%#.4X VA:%#llX + unsol:%d\n",
			 task->itt, mem_reg->rkey,
			 (अचिन्हित दीर्घ दीर्घ)mem_reg->sge.addr, unsol_sz);
	पूर्ण

	अगर (imm_sz > 0) अणु
		iser_dbg("Cmd itt:%d, WRITE, adding imm.data sz: %d\n",
			 task->itt, imm_sz);
		tx_dsg->addr = mem_reg->sge.addr;
		tx_dsg->length = imm_sz;
		tx_dsg->lkey = mem_reg->sge.lkey;
		iser_task->desc.num_sge = 2;
	पूर्ण

	वापस 0;
पूर्ण

/* creates a new tx descriptor and adds header regd buffer */
अटल व्योम iser_create_send_desc(काष्ठा iser_conn	*iser_conn,
				  काष्ठा iser_tx_desc	*tx_desc)
अणु
	काष्ठा iser_device *device = iser_conn->ib_conn.device;

	ib_dma_sync_single_क्रम_cpu(device->ib_device,
		tx_desc->dma_addr, ISER_HEADERS_LEN, DMA_TO_DEVICE);

	स_रखो(&tx_desc->iser_header, 0, माप(काष्ठा iser_ctrl));
	tx_desc->iser_header.flags = ISER_VER;
	tx_desc->num_sge = 1;
पूर्ण

अटल व्योम iser_मुक्त_login_buf(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा iser_device *device = iser_conn->ib_conn.device;
	काष्ठा iser_login_desc *desc = &iser_conn->login_desc;

	अगर (!desc->req)
		वापस;

	ib_dma_unmap_single(device->ib_device, desc->req_dma,
			    ISCSI_DEF_MAX_RECV_SEG_LEN, DMA_TO_DEVICE);

	ib_dma_unmap_single(device->ib_device, desc->rsp_dma,
			    ISER_RX_LOGIN_SIZE, DMA_FROM_DEVICE);

	kमुक्त(desc->req);
	kमुक्त(desc->rsp);

	/* make sure we never reकरो any unmapping */
	desc->req = शून्य;
	desc->rsp = शून्य;
पूर्ण

अटल पूर्णांक iser_alloc_login_buf(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा iser_device *device = iser_conn->ib_conn.device;
	काष्ठा iser_login_desc *desc = &iser_conn->login_desc;

	desc->req = kदो_स्मृति(ISCSI_DEF_MAX_RECV_SEG_LEN, GFP_KERNEL);
	अगर (!desc->req)
		वापस -ENOMEM;

	desc->req_dma = ib_dma_map_single(device->ib_device, desc->req,
					  ISCSI_DEF_MAX_RECV_SEG_LEN,
					  DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(device->ib_device,
				desc->req_dma))
		जाओ मुक्त_req;

	desc->rsp = kदो_स्मृति(ISER_RX_LOGIN_SIZE, GFP_KERNEL);
	अगर (!desc->rsp)
		जाओ unmap_req;

	desc->rsp_dma = ib_dma_map_single(device->ib_device, desc->rsp,
					   ISER_RX_LOGIN_SIZE,
					   DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(device->ib_device,
				desc->rsp_dma))
		जाओ मुक्त_rsp;

	वापस 0;

मुक्त_rsp:
	kमुक्त(desc->rsp);
unmap_req:
	ib_dma_unmap_single(device->ib_device, desc->req_dma,
			    ISCSI_DEF_MAX_RECV_SEG_LEN,
			    DMA_TO_DEVICE);
मुक्त_req:
	kमुक्त(desc->req);

	वापस -ENOMEM;
पूर्ण

पूर्णांक iser_alloc_rx_descriptors(काष्ठा iser_conn *iser_conn,
			      काष्ठा iscsi_session *session)
अणु
	पूर्णांक i, j;
	u64 dma_addr;
	काष्ठा iser_rx_desc *rx_desc;
	काष्ठा ib_sge       *rx_sg;
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा iser_device *device = ib_conn->device;

	iser_conn->qp_max_recv_dtos = session->cmds_max;
	iser_conn->qp_max_recv_dtos_mask = session->cmds_max - 1; /* cmds_max is 2^N */
	iser_conn->min_posted_rx = iser_conn->qp_max_recv_dtos >> 2;

	अगर (iser_alloc_fastreg_pool(ib_conn, session->scsi_cmds_max,
				    iser_conn->pages_per_mr))
		जाओ create_rdma_reg_res_failed;

	अगर (iser_alloc_login_buf(iser_conn))
		जाओ alloc_login_buf_fail;

	iser_conn->num_rx_descs = session->cmds_max;
	iser_conn->rx_descs = kदो_स्मृति_array(iser_conn->num_rx_descs,
					    माप(काष्ठा iser_rx_desc),
					    GFP_KERNEL);
	अगर (!iser_conn->rx_descs)
		जाओ rx_desc_alloc_fail;

	rx_desc = iser_conn->rx_descs;

	क्रम (i = 0; i < iser_conn->qp_max_recv_dtos; i++, rx_desc++)  अणु
		dma_addr = ib_dma_map_single(device->ib_device, (व्योम *)rx_desc,
					ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
		अगर (ib_dma_mapping_error(device->ib_device, dma_addr))
			जाओ rx_desc_dma_map_failed;

		rx_desc->dma_addr = dma_addr;
		rx_desc->cqe.करोne = iser_task_rsp;
		rx_sg = &rx_desc->rx_sg;
		rx_sg->addr = rx_desc->dma_addr;
		rx_sg->length = ISER_RX_PAYLOAD_SIZE;
		rx_sg->lkey = device->pd->local_dma_lkey;
	पूर्ण

	iser_conn->rx_desc_head = 0;
	वापस 0;

rx_desc_dma_map_failed:
	rx_desc = iser_conn->rx_descs;
	क्रम (j = 0; j < i; j++, rx_desc++)
		ib_dma_unmap_single(device->ib_device, rx_desc->dma_addr,
				    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	kमुक्त(iser_conn->rx_descs);
	iser_conn->rx_descs = शून्य;
rx_desc_alloc_fail:
	iser_मुक्त_login_buf(iser_conn);
alloc_login_buf_fail:
	iser_मुक्त_fastreg_pool(ib_conn);
create_rdma_reg_res_failed:
	iser_err("failed allocating rx descriptors / data buffers\n");
	वापस -ENOMEM;
पूर्ण

व्योम iser_मुक्त_rx_descriptors(काष्ठा iser_conn *iser_conn)
अणु
	पूर्णांक i;
	काष्ठा iser_rx_desc *rx_desc;
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा iser_device *device = ib_conn->device;

	iser_मुक्त_fastreg_pool(ib_conn);

	rx_desc = iser_conn->rx_descs;
	क्रम (i = 0; i < iser_conn->qp_max_recv_dtos; i++, rx_desc++)
		ib_dma_unmap_single(device->ib_device, rx_desc->dma_addr,
				    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	kमुक्त(iser_conn->rx_descs);
	/* make sure we never reकरो any unmapping */
	iser_conn->rx_descs = शून्य;

	iser_मुक्त_login_buf(iser_conn);
पूर्ण

अटल पूर्णांक iser_post_rx_bufs(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *req)
अणु
	काष्ठा iser_conn *iser_conn = conn->dd_data;
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा iscsi_session *session = conn->session;

	iser_dbg("req op %x flags %x\n", req->opcode, req->flags);
	/* check अगर this is the last login - going to full feature phase */
	अगर ((req->flags & ISCSI_FULL_FEATURE_PHASE) != ISCSI_FULL_FEATURE_PHASE)
		वापस 0;

	/*
	 * Check that there is one posted recv buffer
	 * (क्रम the last login response).
	 */
	WARN_ON(ib_conn->post_recv_buf_count != 1);

	अगर (session->discovery_sess) अणु
		iser_info("Discovery session, re-using login RX buffer\n");
		वापस 0;
	पूर्ण अन्यथा
		iser_info("Normal session, posting batch of RX %d buffers\n",
			  iser_conn->min_posted_rx);

	/* Initial post receive buffers */
	अगर (iser_post_recvm(iser_conn, iser_conn->min_posted_rx))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत bool iser_संकेत_comp(u8 sig_count)
अणु
	वापस ((sig_count % ISER_SIGNAL_CMD_COUNT) == 0);
पूर्ण

/**
 * iser_send_command - send command PDU
 * @conn: link to matching iscsi connection
 * @task: SCSI command task
 */
पूर्णांक iser_send_command(काष्ठा iscsi_conn *conn,
		      काष्ठा iscsi_task *task)
अणु
	काष्ठा iser_conn *iser_conn = conn->dd_data;
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	अचिन्हित दीर्घ edtl;
	पूर्णांक err;
	काष्ठा iser_data_buf *data_buf, *prot_buf;
	काष्ठा iscsi_scsi_req *hdr = (काष्ठा iscsi_scsi_req *)task->hdr;
	काष्ठा scsi_cmnd *sc  =  task->sc;
	काष्ठा iser_tx_desc *tx_desc = &iser_task->desc;
	u8 sig_count = ++iser_conn->ib_conn.sig_count;

	edtl = ntohl(hdr->data_length);

	/* build the tx desc regd header and add it to the tx desc dto */
	tx_desc->type = ISCSI_TX_SCSI_COMMAND;
	tx_desc->cqe.करोne = iser_cmd_comp;
	iser_create_send_desc(iser_conn, tx_desc);

	अगर (hdr->flags & ISCSI_FLAG_CMD_READ) अणु
		data_buf = &iser_task->data[ISER_सूची_IN];
		prot_buf = &iser_task->prot[ISER_सूची_IN];
	पूर्ण अन्यथा अणु
		data_buf = &iser_task->data[ISER_सूची_OUT];
		prot_buf = &iser_task->prot[ISER_सूची_OUT];
	पूर्ण

	अगर (scsi_sg_count(sc)) अणु /* using a scatter list */
		data_buf->sg = scsi_sglist(sc);
		data_buf->size = scsi_sg_count(sc);
	पूर्ण
	data_buf->data_len = scsi_bufflen(sc);

	अगर (scsi_prot_sg_count(sc)) अणु
		prot_buf->sg  = scsi_prot_sglist(sc);
		prot_buf->size = scsi_prot_sg_count(sc);
		prot_buf->data_len = (data_buf->data_len >>
				     ilog2(sc->device->sector_size)) * 8;
	पूर्ण

	अगर (hdr->flags & ISCSI_FLAG_CMD_READ) अणु
		err = iser_prepare_पढ़ो_cmd(task);
		अगर (err)
			जाओ send_command_error;
	पूर्ण
	अगर (hdr->flags & ISCSI_FLAG_CMD_WRITE) अणु
		err = iser_prepare_ग_लिखो_cmd(task,
					     task->imm_count,
				             task->imm_count +
					     task->unsol_r2t.data_length,
					     edtl);
		अगर (err)
			जाओ send_command_error;
	पूर्ण

	iser_task->status = ISER_TASK_STATUS_STARTED;

	err = iser_post_send(&iser_conn->ib_conn, tx_desc,
			     iser_संकेत_comp(sig_count));
	अगर (!err)
		वापस 0;

send_command_error:
	iser_err("conn %p failed task->itt %d err %d\n",conn, task->itt, err);
	वापस err;
पूर्ण

/**
 * iser_send_data_out - send data out PDU
 * @conn: link to matching iscsi connection
 * @task: SCSI command task
 * @hdr: poपूर्णांकer to the LLD's iSCSI message header
 */
पूर्णांक iser_send_data_out(काष्ठा iscsi_conn *conn,
		       काष्ठा iscsi_task *task,
		       काष्ठा iscsi_data *hdr)
अणु
	काष्ठा iser_conn *iser_conn = conn->dd_data;
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	काष्ठा iser_tx_desc *tx_desc;
	काष्ठा iser_mem_reg *mem_reg;
	अचिन्हित दीर्घ buf_offset;
	अचिन्हित दीर्घ data_seg_len;
	uपूर्णांक32_t itt;
	पूर्णांक err;
	काष्ठा ib_sge *tx_dsg;

	itt = (__क्रमce uपूर्णांक32_t)hdr->itt;
	data_seg_len = ntoh24(hdr->dlength);
	buf_offset   = ntohl(hdr->offset);

	iser_dbg("%s itt %d dseg_len %d offset %d\n",
		 __func__,(पूर्णांक)itt,(पूर्णांक)data_seg_len,(पूर्णांक)buf_offset);

	tx_desc = kmem_cache_zalloc(ig.desc_cache, GFP_ATOMIC);
	अगर (!tx_desc)
		वापस -ENOMEM;

	tx_desc->type = ISCSI_TX_DATAOUT;
	tx_desc->cqe.करोne = iser_dataout_comp;
	tx_desc->iser_header.flags = ISER_VER;
	स_नकल(&tx_desc->iscsi_header, hdr, माप(काष्ठा iscsi_hdr));

	/* build the tx desc */
	err = iser_initialize_task_headers(task, tx_desc);
	अगर (err)
		जाओ send_data_out_error;

	mem_reg = &iser_task->rdma_reg[ISER_सूची_OUT];
	tx_dsg = &tx_desc->tx_sg[1];
	tx_dsg->addr = mem_reg->sge.addr + buf_offset;
	tx_dsg->length = data_seg_len;
	tx_dsg->lkey = mem_reg->sge.lkey;
	tx_desc->num_sge = 2;

	अगर (buf_offset + data_seg_len > iser_task->data[ISER_सूची_OUT].data_len) अणु
		iser_err("Offset:%ld & DSL:%ld in Data-Out inconsistent with total len:%ld, itt:%d\n",
			 buf_offset, data_seg_len,
			 iser_task->data[ISER_सूची_OUT].data_len, itt);
		err = -EINVAL;
		जाओ send_data_out_error;
	पूर्ण
	iser_dbg("data-out itt: %d, offset: %ld, sz: %ld\n",
		 itt, buf_offset, data_seg_len);


	err = iser_post_send(&iser_conn->ib_conn, tx_desc, true);
	अगर (!err)
		वापस 0;

send_data_out_error:
	kmem_cache_मुक्त(ig.desc_cache, tx_desc);
	iser_err("conn %p failed err %d\n", conn, err);
	वापस err;
पूर्ण

पूर्णांक iser_send_control(काष्ठा iscsi_conn *conn,
		      काष्ठा iscsi_task *task)
अणु
	काष्ठा iser_conn *iser_conn = conn->dd_data;
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	काष्ठा iser_tx_desc *mdesc = &iser_task->desc;
	अचिन्हित दीर्घ data_seg_len;
	पूर्णांक err = 0;
	काष्ठा iser_device *device;

	/* build the tx desc regd header and add it to the tx desc dto */
	mdesc->type = ISCSI_TX_CONTROL;
	mdesc->cqe.करोne = iser_ctrl_comp;
	iser_create_send_desc(iser_conn, mdesc);

	device = iser_conn->ib_conn.device;

	data_seg_len = ntoh24(task->hdr->dlength);

	अगर (data_seg_len > 0) अणु
		काष्ठा iser_login_desc *desc = &iser_conn->login_desc;
		काष्ठा ib_sge *tx_dsg = &mdesc->tx_sg[1];

		अगर (task != conn->login_task) अणु
			iser_err("data present on non login task!!!\n");
			जाओ send_control_error;
		पूर्ण

		ib_dma_sync_single_क्रम_cpu(device->ib_device, desc->req_dma,
					   task->data_count, DMA_TO_DEVICE);

		स_नकल(desc->req, task->data, task->data_count);

		ib_dma_sync_single_क्रम_device(device->ib_device, desc->req_dma,
					      task->data_count, DMA_TO_DEVICE);

		tx_dsg->addr = desc->req_dma;
		tx_dsg->length = task->data_count;
		tx_dsg->lkey = device->pd->local_dma_lkey;
		mdesc->num_sge = 2;
	पूर्ण

	अगर (task == conn->login_task) अणु
		iser_dbg("op %x dsl %lx, posting login rx buffer\n",
			 task->hdr->opcode, data_seg_len);
		err = iser_post_recvl(iser_conn);
		अगर (err)
			जाओ send_control_error;
		err = iser_post_rx_bufs(conn, task->hdr);
		अगर (err)
			जाओ send_control_error;
	पूर्ण

	err = iser_post_send(&iser_conn->ib_conn, mdesc, true);
	अगर (!err)
		वापस 0;

send_control_error:
	iser_err("conn %p failed err %d\n",conn, err);
	वापस err;
पूर्ण

व्योम iser_login_rsp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_conn *ib_conn = wc->qp->qp_context;
	काष्ठा iser_conn *iser_conn = to_iser_conn(ib_conn);
	काष्ठा iser_login_desc *desc = iser_login(wc->wr_cqe);
	काष्ठा iscsi_hdr *hdr;
	अक्षर *data;
	पूर्णांक length;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		iser_err_comp(wc, "login_rsp");
		वापस;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(ib_conn->device->ib_device,
				   desc->rsp_dma, ISER_RX_LOGIN_SIZE,
				   DMA_FROM_DEVICE);

	hdr = desc->rsp + माप(काष्ठा iser_ctrl);
	data = desc->rsp + ISER_HEADERS_LEN;
	length = wc->byte_len - ISER_HEADERS_LEN;

	iser_dbg("op 0x%x itt 0x%x dlen %d\n", hdr->opcode,
		 hdr->itt, length);

	iscsi_iser_recv(iser_conn->iscsi_conn, hdr, data, length);

	ib_dma_sync_single_क्रम_device(ib_conn->device->ib_device,
				      desc->rsp_dma, ISER_RX_LOGIN_SIZE,
				      DMA_FROM_DEVICE);

	ib_conn->post_recv_buf_count--;
पूर्ण

अटल अंतरभूत पूर्णांक
iser_inv_desc(काष्ठा iser_fr_desc *desc, u32 rkey)
अणु
	अगर (unlikely((!desc->sig_रक्षित && rkey != desc->rsc.mr->rkey) ||
		     (desc->sig_रक्षित && rkey != desc->rsc.sig_mr->rkey))) अणु
		iser_err("Bogus remote invalidation for rkey %#x\n", rkey);
		वापस -EINVAL;
	पूर्ण

	desc->rsc.mr_valid = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
iser_check_remote_inv(काष्ठा iser_conn *iser_conn,
		      काष्ठा ib_wc *wc,
		      काष्ठा iscsi_hdr *hdr)
अणु
	अगर (wc->wc_flags & IB_WC_WITH_INVALIDATE) अणु
		काष्ठा iscsi_task *task;
		u32 rkey = wc->ex.invalidate_rkey;

		iser_dbg("conn %p: remote invalidation for rkey %#x\n",
			 iser_conn, rkey);

		अगर (unlikely(!iser_conn->snd_w_inv)) अणु
			iser_err("conn %p: unexpected remote invalidation, terminating connection\n",
				 iser_conn);
			वापस -EPROTO;
		पूर्ण

		task = iscsi_itt_to_ctask(iser_conn->iscsi_conn, hdr->itt);
		अगर (likely(task)) अणु
			काष्ठा iscsi_iser_task *iser_task = task->dd_data;
			काष्ठा iser_fr_desc *desc;

			अगर (iser_task->dir[ISER_सूची_IN]) अणु
				desc = iser_task->rdma_reg[ISER_सूची_IN].mem_h;
				अगर (unlikely(iser_inv_desc(desc, rkey)))
					वापस -EINVAL;
			पूर्ण

			अगर (iser_task->dir[ISER_सूची_OUT]) अणु
				desc = iser_task->rdma_reg[ISER_सूची_OUT].mem_h;
				अगर (unlikely(iser_inv_desc(desc, rkey)))
					वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			iser_err("failed to get task for itt=%d\n", hdr->itt);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


व्योम iser_task_rsp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_conn *ib_conn = wc->qp->qp_context;
	काष्ठा iser_conn *iser_conn = to_iser_conn(ib_conn);
	काष्ठा iser_rx_desc *desc = iser_rx(wc->wr_cqe);
	काष्ठा iscsi_hdr *hdr;
	पूर्णांक length;
	पूर्णांक outstanding, count, err;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		iser_err_comp(wc, "task_rsp");
		वापस;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(ib_conn->device->ib_device,
				   desc->dma_addr, ISER_RX_PAYLOAD_SIZE,
				   DMA_FROM_DEVICE);

	hdr = &desc->iscsi_header;
	length = wc->byte_len - ISER_HEADERS_LEN;

	iser_dbg("op 0x%x itt 0x%x dlen %d\n", hdr->opcode,
		 hdr->itt, length);

	अगर (iser_check_remote_inv(iser_conn, wc, hdr)) अणु
		iscsi_conn_failure(iser_conn->iscsi_conn,
				   ISCSI_ERR_CONN_FAILED);
		वापस;
	पूर्ण

	iscsi_iser_recv(iser_conn->iscsi_conn, hdr, desc->data, length);

	ib_dma_sync_single_क्रम_device(ib_conn->device->ib_device,
				      desc->dma_addr, ISER_RX_PAYLOAD_SIZE,
				      DMA_FROM_DEVICE);

	/* decrementing conn->post_recv_buf_count only --after-- मुक्तing the   *
	 * task eliminates the need to worry on tasks which are completed in   *
	 * parallel to the execution of iser_conn_term. So the code that रुकोs *
	 * क्रम the posted rx bufs refcount to become zero handles everything   */
	ib_conn->post_recv_buf_count--;

	outstanding = ib_conn->post_recv_buf_count;
	अगर (outstanding + iser_conn->min_posted_rx <= iser_conn->qp_max_recv_dtos) अणु
		count = min(iser_conn->qp_max_recv_dtos - outstanding,
			    iser_conn->min_posted_rx);
		err = iser_post_recvm(iser_conn, count);
		अगर (err)
			iser_err("posting %d rx bufs err %d\n", count, err);
	पूर्ण
पूर्ण

व्योम iser_cmd_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		iser_err_comp(wc, "command");
पूर्ण

व्योम iser_ctrl_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा iser_tx_desc *desc = iser_tx(wc->wr_cqe);
	काष्ठा iscsi_task *task;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		iser_err_comp(wc, "control");
		वापस;
	पूर्ण

	/* this arithmetic is legal by libiscsi dd_data allocation */
	task = (व्योम *)desc - माप(काष्ठा iscsi_task);
	अगर (task->hdr->itt == RESERVED_ITT)
		iscsi_put_task(task);
पूर्ण

व्योम iser_dataout_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा iser_tx_desc *desc = iser_tx(wc->wr_cqe);
	काष्ठा ib_conn *ib_conn = wc->qp->qp_context;
	काष्ठा iser_device *device = ib_conn->device;

	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		iser_err_comp(wc, "dataout");

	ib_dma_unmap_single(device->ib_device, desc->dma_addr,
			    ISER_HEADERS_LEN, DMA_TO_DEVICE);
	kmem_cache_मुक्त(ig.desc_cache, desc);
पूर्ण

व्योम iser_task_rdma_init(काष्ठा iscsi_iser_task *iser_task)

अणु
	iser_task->status = ISER_TASK_STATUS_INIT;

	iser_task->dir[ISER_सूची_IN] = 0;
	iser_task->dir[ISER_सूची_OUT] = 0;

	iser_task->data[ISER_सूची_IN].data_len  = 0;
	iser_task->data[ISER_सूची_OUT].data_len = 0;

	iser_task->prot[ISER_सूची_IN].data_len  = 0;
	iser_task->prot[ISER_सूची_OUT].data_len = 0;

	iser_task->prot[ISER_सूची_IN].dma_nents = 0;
	iser_task->prot[ISER_सूची_OUT].dma_nents = 0;

	स_रखो(&iser_task->rdma_reg[ISER_सूची_IN], 0,
	       माप(काष्ठा iser_mem_reg));
	स_रखो(&iser_task->rdma_reg[ISER_सूची_OUT], 0,
	       माप(काष्ठा iser_mem_reg));
पूर्ण

व्योम iser_task_rdma_finalize(काष्ठा iscsi_iser_task *iser_task)
अणु
	पूर्णांक prot_count = scsi_prot_sg_count(iser_task->sc);

	अगर (iser_task->dir[ISER_सूची_IN]) अणु
		iser_unreg_mem_fastreg(iser_task, ISER_सूची_IN);
		iser_dma_unmap_task_data(iser_task,
					 &iser_task->data[ISER_सूची_IN],
					 DMA_FROM_DEVICE);
		अगर (prot_count)
			iser_dma_unmap_task_data(iser_task,
						 &iser_task->prot[ISER_सूची_IN],
						 DMA_FROM_DEVICE);
	पूर्ण

	अगर (iser_task->dir[ISER_सूची_OUT]) अणु
		iser_unreg_mem_fastreg(iser_task, ISER_सूची_OUT);
		iser_dma_unmap_task_data(iser_task,
					 &iser_task->data[ISER_सूची_OUT],
					 DMA_TO_DEVICE);
		अगर (prot_count)
			iser_dma_unmap_task_data(iser_task,
						 &iser_task->prot[ISER_सूची_OUT],
						 DMA_TO_DEVICE);
	पूर्ण
पूर्ण
